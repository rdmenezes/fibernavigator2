/*
 * toolbar.cpp
 *
 *  Created on: 14.06.2012
 *      Author: Ralph
 */
#include "../views/toolbarview.h"
#include "../../data/dataset.h"

#include "toolbar.h"

ToolBar::ToolBar( const QString &title, QWidget* parent ) :
    QToolBar( title, parent )
{
    setObjectName( title );
    m_toolBarView = new ToolBarView();

    connect( m_toolBarView, SIGNAL( sigSelectionChanged( int ) ), this, SLOT( slotSelectionChanged( int ) ) );

    createActions();

//    this->addAction( m_scalarAction1 );
//    this->addAction( m_vectorAction1 );
//    this->addAction( m_multiAction1 );
//    this->addAction( m_meshAction1 );
//    this->addAction( m_fiberAction1 );
}

ToolBar::~ToolBar()
{
}

void ToolBar::setModel( QAbstractItemModel* model )
{
    m_toolBarView->setModel( model );

}

void ToolBar::setSelectionModel( QItemSelectionModel* selectionModel )
{
    m_toolBarView->setSelectionModel( selectionModel );
}

void ToolBar::createActions()
{
    m_scalarAction1 = new QAction( QIcon( ":/icons/tmp1.png" ), tr( "Scalar 1" ), this );
    m_scalarAction1->setStatusTip( tr( "Scalar Action 1" ) );
    connect( m_scalarAction1, SIGNAL( triggered() ), this, SLOT( slotScalar1() ) );

    m_vectorAction1 = new QAction( QIcon( ":/icons/tmp3.png" ), tr( "Vector 1" ), this );
    m_vectorAction1->setStatusTip( tr( "Vector Action 1" ) );
    connect( m_vectorAction1, SIGNAL( triggered() ), this, SLOT( slotVector1() ) );

    m_multiAction1 = new QAction( QIcon( ":/icons/tmpx.png" ), tr( "Multi 1" ), this );
    m_multiAction1->setStatusTip( tr( "Multi Action 1" ) );
    connect( m_multiAction1, SIGNAL( triggered() ), this, SLOT( slotMulti1() ) );

    m_meshAction1 = new QAction( QIcon( ":/icons/tmpm.png" ), tr( "Mesh 1" ), this );
    m_meshAction1->setStatusTip( tr( "Mesh Action 1" ) );
    connect( m_meshAction1, SIGNAL( triggered() ), this, SLOT( slotMesh1() ) );

    m_fiberAction1 = new QAction( QIcon( ":/icons/tmpf.png" ), tr( "Fiber 1" ), this );
    m_fiberAction1->setStatusTip( tr( "Fiber Action 1" ) );
    connect( m_fiberAction1, SIGNAL( triggered() ), this, SLOT( slotFiber1() ) );
}

void ToolBar::slotScalar1()
{
    qDebug() << "scalar button pressed";
}

void ToolBar::slotVector1()
{
    qDebug() << "vector button pressed";
}

void ToolBar::slotMulti1()
{
    qDebug() << "multi button pressed";
}

void ToolBar::slotMesh1()
{
    qDebug() << "mesh button pressed";
}

void ToolBar::slotFiber1()
{
    qDebug() << "fiber button pressed";
}

void ToolBar::slotSelectionChanged( int type )
{
    this->clear();
    switch ( type )
    {
        case FNDT_NIFTI_SCALAR:
        case FNDT_NIFTI2_SCALAR:
        {
            this->addAction( m_scalarAction1 );
            break;
        }
        case FNDT_NIFTI_VECTOR:
        case FNDT_NIFTI2_VECTOR:
        {
            this->addAction( m_vectorAction1 );
            break;
        }
        case FNDT_NIFTI_DWI:
        case FNDT_NIFTI2_DWI:
        {
            this->addAction( m_multiAction1 );
            break;
        }
        default:
        {
            break;
        }
    }
}