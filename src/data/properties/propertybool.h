/*
 * propertybool.h
 *
 * Created on: Jan 17, 2013
 * @author Ralph Schurade
 */

#ifndef PROPERTYBOOL_H_
#define PROPERTYBOOL_H_

#include "property.h"

class CheckboxWithLabel;
class QWidget;

class PropertyBool : public Property
{
    Q_OBJECT

public:
    PropertyBool( QString name, bool value = false );
    virtual ~PropertyBool();

    QWidget* getWidget();

    QVariant getValue();

    void setValue( QVariant value );

private:
    int m_value;

    CheckboxWithLabel* m_widget;

private slots:
    void widgetChanged( int value, int id );

signals:
    void valueChanged();
    void valueChanged( bool state );

};

#endif /* PROPERTYINT_H_ */
