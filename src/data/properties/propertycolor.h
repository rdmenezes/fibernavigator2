/*
 * propertycolor.h
 *
 * Created on: Feb 4, 2013
 * @author Ralph Schurade
 */

#ifndef PROPERTYCOLOR_H_
#define PROPERTYCOLOR_H_

#include "property.h"

#include <QColor>

class ColorWidgetWithLabel;

class PropertyColor : public Property
{
    Q_OBJECT

public:
    PropertyColor( QString name, QColor value = QColor( 0, 0, 0 ) );
    virtual ~PropertyColor();

    QWidget* getWidget();

    QVariant getValue();

    void setValue( QVariant value );
    void setValue( QColor value );

private:
    QColor m_value;

    ColorWidgetWithLabel* m_widget;

private slots:
    void widgetChanged( QColor value, int id );

signals:
    void valueChanged();
    void colorChanged( QColor color );
};

#endif /* PROPERTYCOLOR_H_ */
