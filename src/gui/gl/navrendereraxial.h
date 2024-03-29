/*
 * scenerenderer.h
 *
 * Created on: 09.05.2012
 * @author Ralph Schurade
 */

#ifndef NAVRENDERERAXIAL_H_
#define NAVRENDERERAXIAL_H_

#include "navrenderer.h"

#include <QMatrix4x4>

class QGLShaderProgram;

class NavRendererAxial : public NavRenderer
{
public:
	NavRendererAxial( QString name );
	virtual ~NavRendererAxial();

	void draw();

	void leftMouseDown( int x, int y );

	void adjustRatios();

private:
    void initGeometry();
};

#endif /* SCENERENDERER_H_ */
