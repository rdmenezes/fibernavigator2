/*
 * datasetmesh.h
 *
 * Created on: Jul 19, 2012
 * @author Ralph Schurade
 */

#ifndef DATASETMESH_H_
#define DATASETMESH_H_

#include "dataset.h"

#include <QString>

class TriangleMesh2;
class MeshRenderer;

class DatasetMesh: public Dataset
{
    Q_OBJECT

public:
    DatasetMesh( TriangleMesh2* mesh, QString filename = QString( "new mesh" ) );
    DatasetMesh( QString filename, Fn::DatasetType type );
    virtual ~DatasetMesh();

    virtual void draw( QMatrix4x4 pMatrix, QMatrix4x4 mvMatrix, int width, int height, int renderMode );
    QString getValueAsString( int x, int y, int z );

    void mousePick( int pickId, QVector3D pos );

    TriangleMesh2* getMesh();

protected:
    TriangleMesh2* m_mesh;
    MeshRenderer* m_renderer;

private slots:
    void paintModeChanged( int mode );

};

#endif /* DATASETMESH_H_ */
