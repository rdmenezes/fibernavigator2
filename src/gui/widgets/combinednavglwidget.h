/*
 * combinednavglwidget.h
 *
 * Created on: May 03, 2012
 * @author Ralph Schurade
 */

#ifndef COMBINEDNAVGLWIDGET_H
#define COMBINEDNAVGLWIDGET_H

#include "GL/glew.h"
#include <QtOpenGL/QGLWidget>

class CombinedNavRenderer;

class CombinedNavGLWidget: public QGLWidget
{
    Q_OBJECT

public:
    CombinedNavGLWidget( QString name, QWidget *parent = 0, const QGLWidget *shareWidget = 0 );
    ~CombinedNavGLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void update();
    void setWidgetVisible( bool visible );

signals:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL( int width, int height );
    void mousePressEvent( QMouseEvent *event );
    void mouseReleaseEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event );

private:
    CombinedNavRenderer* m_renderer;
    bool m_visible;
};

#endif
