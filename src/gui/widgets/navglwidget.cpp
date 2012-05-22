#include <QtGui/QtGui>
#include <QtCore/QDebug>
#include "../../data/datastore.h"
#include "../gl/navrendereraxial.h"
#include "../gl/navrenderercoronal.h"
#include "../gl/navrenderersagittal.h"

#include "navglwidget.h"

NavGLWidget::NavGLWidget( DataStore* dataStore, QString name, int orient, QWidget *parent, const QGLWidget *shareWidget ) :
	QGLWidget( parent, shareWidget )
{
    switch( orient )
    {
        case 0:
        {
            m_navRenderer = new NavRendererSagittal( name );
            break;
        }
        case 1:
        {
            m_navRenderer = new NavRendererCoronal( name );
            break;
        }
        case 2:
        {
            m_navRenderer = new NavRendererAxial( name );
            break;
        }
    }

    m_navRenderer->setModel( dataStore );
    connect( dataStore, SIGNAL( dataChanged( QModelIndex, QModelIndex ) ), this, SLOT( update() ) );
}

NavGLWidget::~NavGLWidget()
{
    destroy ( m_navRenderer );
}

QSize NavGLWidget::minimumSizeHint() const
{
    return QSize( 50, 50 );
}

QSize NavGLWidget::sizeHint() const
{
    return QSize( 400, 400 );
}

void NavGLWidget::initializeGL()
{
	m_navRenderer->initGL();
}

void NavGLWidget::paintGL()
{
	m_navRenderer->draw();
}

void NavGLWidget::resizeGL( int width, int height )
{
    m_navRenderer->resizeGL( width, height );
}

void NavGLWidget::mousePressEvent( QMouseEvent *event )
{
    if ( event->buttons() & Qt::LeftButton )
    {
        //m_sceneRenderer->leftMouseDown( event->x(), event->y() );
    }
    updateGL();
}

void NavGLWidget::mouseMoveEvent( QMouseEvent *event )
{
    if ( event->buttons() & Qt::LeftButton )
    {
        //m_sceneRenderer->leftMouseDrag( event->x(), event->y() );
    }
    updateGL();
}

void NavGLWidget::mouseReleaseEvent( QMouseEvent *event )
{
    updateGL();
}

void NavGLWidget::update()
{
    updateGL();
}
