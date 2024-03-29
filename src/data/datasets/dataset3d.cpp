/*
 * dataset3d.cpp
 *
 * Created on: May 9, 2012
 * @author Ralph Schurade
 */
#include "dataset3d.h"
#include "../models.h"

#include "../../gui/gl/evrenderer.h"

Dataset3D::Dataset3D( QString filename, QVector<QVector3D> data, nifti_image* header ) :
        DatasetNifti( filename, Fn::DatasetType::NIFTI_VECTOR, header ), m_data( data ), m_renderer( 0 )
{
    m_properties.set( Fn::Property::COLORMAP, -1 );
    m_properties.set( Fn::Property::INTERPOLATION, false, true );
    m_properties.set( Fn::Property::ALPHA, 1.0f, 0.0, 1.0, true );
    m_properties.set( Fn::Property::DIM, 3 );

    m_properties.set( Fn::Property::RENDER_SLICE, 1, 1, 3, true );
    m_properties.set( Fn::Property::SCALING, 1.0f, 0.0f, 2.0f, true );
    m_properties.set( Fn::Property::OFFSET, 0.0f, -0.5, 0.5, true );

    m_properties.set(Fn::Property::RENDER_VECTORS_STICKS, false, true );

    m_properties.set( Fn::Property::HAS_TEXTURE, true );

    examineDataset();
}

Dataset3D::~Dataset3D()
{
    m_properties.set( Fn::Property::ACTIVE, false );
    delete m_renderer;
    m_data.clear();
}

void Dataset3D::examineDataset()
{
    int type = m_properties.get( Fn::Property::DATATYPE ).toInt();
    int nx = m_properties.get( Fn::Property::NX ).toInt();
    int ny = m_properties.get( Fn::Property::NY ).toInt();
    int nz = m_properties.get( Fn::Property::NZ ).toInt();
    int size = nx * ny * nz * 3;

    if ( type == DT_UNSIGNED_CHAR )
    {
        m_properties.set( Fn::Property::SIZE, static_cast<int>( size * sizeof(unsigned char) ) );

        m_properties.set( Fn::Property::MIN, 0 );
        m_properties.set( Fn::Property::MAX, 255 );
    }

    if ( type == DT_FLOAT )
    {
        m_properties.set( Fn::Property::SIZE, static_cast<int>( size * sizeof(float) ) );
        m_properties.set( Fn::Property::MIN, -1.0f );
        m_properties.set( Fn::Property::MAX, 1.0f );
    }
    m_properties.set( Fn::Property::LOWER_THRESHOLD, m_properties.get( Fn::Property::MIN ).toFloat() );
    m_properties.set( Fn::Property::UPPER_THRESHOLD, m_properties.get( Fn::Property::MAX ).toFloat() );

    if ( m_qform( 1, 1 ) < 0 || m_sform( 1, 1 ) < 0 )
    {
        qDebug() << m_properties.get( Fn::Property::NAME ).toString() << ": RADIOLOGICAL orientation detected. Flipping voxels on X-Axis";
        flipX();
    }
}

void Dataset3D::createTexture()
{
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    glGenTextures( 1, &m_textureGLuint );

    glBindTexture( GL_TEXTURE_3D, m_textureGLuint );

    glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP );
    glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP );

    int type = m_properties.get( Fn::Property::DATATYPE ).toInt();
    int nx = m_properties.get( Fn::Property::NX ).toInt();
    int ny = m_properties.get( Fn::Property::NY ).toInt();
    int nz = m_properties.get( Fn::Property::NZ ).toInt();

    float div = 1.0;
    if ( type == DT_UNSIGNED_CHAR )
    {
        div = 255.;
    }

    int blockSize = nx * ny * nz;
    float* data = new float[blockSize * 3];

    for ( int i = 0; i < blockSize; ++i )
    {
        data[i * 3] = fabs( m_data[i].x() ) / div;
        data[i * 3 + 1] = fabs( m_data[i].y() ) / div;
        data[i * 3 + 2] = fabs( m_data[i].z() ) / div;
    }
    glTexImage3D( GL_TEXTURE_3D, 0, GL_RGBA, nx, ny, nz, 0, GL_RGB, GL_FLOAT, data );

}

void Dataset3D::flipX()
{
    int nx = m_properties.get( Fn::Property::NX ).toInt();
    int ny = m_properties.get( Fn::Property::NY ).toInt();
    int nz = m_properties.get( Fn::Property::NZ ).toInt();

    QVector<QVector3D> newData;

    for ( int z = 0; z < nz; ++z )
    {
        for ( int y = 0; y < ny; ++y )
        {
            for ( int x = nx - 1; x >= 0; --x )
            {
                newData.push_back( m_data[x + y * nx + z * nx * ny] );
            }
        }
    }

    m_header->qto_xyz.m[0][0] = qMax( m_header->qto_xyz.m[0][0], m_header->qto_xyz.m[0][0] * -1.0f );
    m_header->sto_xyz.m[0][0] = qMax( m_header->sto_xyz.m[0][0], m_header->sto_xyz.m[0][0] * -1.0f );
    m_header->qto_xyz.m[0][3] = 0.0;
    m_header->sto_xyz.m[0][3] = 0.0;

    m_data.clear();
    m_data = newData;
}

QVector<QVector3D>* Dataset3D::getData()
{
    return &m_data;
}

void Dataset3D::draw( QMatrix4x4 pMatrix, QMatrix4x4 mvMatrix, int width, int height, int renderMode )
{
    if ( m_renderer == 0 )
    {
        m_renderer = new EVRenderer( &m_data, m_properties.get( Fn::Property::NX ).toInt(),
                                              m_properties.get( Fn::Property::NY ).toInt(),
                                              m_properties.get( Fn::Property::NZ ).toInt(),
                                              m_properties.get( Fn::Property::DX ).toFloat(),
                                              m_properties.get( Fn::Property::DY ).toFloat(),
                                              m_properties.get( Fn::Property::DZ ).toFloat() );
        m_renderer->setModel( Models::g() );
        m_renderer->init();
    }


    if ( m_properties.get( Fn::Property::RENDER_VECTORS_STICKS ).toBool() )
    {
        m_renderer->draw( pMatrix, mvMatrix, width, height, renderMode, &m_properties );
    }
}

QString Dataset3D::getValueAsString( int x, int y, int z )
{
    float dx = Models::g()->data( Models::g()->index( (int)Fn::Global::SLICE_DX, 0 ) ).toFloat();
    float dy = Models::g()->data( Models::g()->index( (int)Fn::Global::SLICE_DY, 0 ) ).toFloat();
    float dz = Models::g()->data( Models::g()->index( (int)Fn::Global::SLICE_DZ, 0 ) ).toFloat();

    x *= dx;
    y *= dy;
    z *= dz;

    QVector3D data = m_data[ getIdFromPos( x, y, z ) ];

    return QString::number( data.x() ) + ", " + QString::number( data.y() ) + ", " + QString::number( data.z() );
}
