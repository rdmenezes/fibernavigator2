/*
 * dataset.h
 *
 *  Created on: May 3, 2012
 *      Author: Ralph Schurade
 */

#ifndef DATASET_H_
#define DATASET_H_

#include "GL/glew.h"

#include "../enums.h"
#include "../properties/propertygroup.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtGui/QMatrix4x4>

#include <limits>

class QAbstractItemModel;

class Dataset : public QObject
{
public:
    Dataset( QDir fileName, Fn::DatasetType type );
    virtual ~Dataset();

    PropertyGroup* properties();

    GLuint getTextureGLuint();

    virtual void draw( QMatrix4x4 mvpMatrix, QMatrix4x4 mvMatrixInverse, QAbstractItemModel* globalModel, QAbstractItemModel* roiModel, QAbstractItemModel* dataModel = 0 );

    virtual QString getValueAsString( int x, int y, int z );

protected:
    virtual void createTexture();

    PropertyGroup m_properties;

    GLuint m_textureGLuint;
};

#endif /* DATASET_H_ */
