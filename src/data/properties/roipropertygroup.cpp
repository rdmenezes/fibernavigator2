/*
 * roipropertygroup.cpp
 *
 * Created on: Feb 02, 2013
 * @author Ralph Schurade
 */
#include "roipropertygroup.h"

#include <QDebug>

ROIPropertyGroup::ROIPropertyGroup()
{
}

ROIPropertyGroup::~ROIPropertyGroup()
{
}

bool ROIPropertyGroup::contains( Fn::ROI name ) const
{
    return m_properties.contains( (int)name );
}

QVariant ROIPropertyGroup::get( Fn::ROI name ) const
{
    if ( m_properties.contains( (int)name ) )
    {
        return m_properties[(int)name]->getValue();
    }
    else
    {
        return QVariant();
//        qDebug() << "*** ERROR *** GET" << m_properties[int::NAME]->getValue().toString() << Property::getNameAsString( name ) << name << "doesnt exist";
//        exit( 0 );
    }
}

bool ROIPropertyGroup::set( Fn::ROI name, QVariant value )
{
    if ( m_properties.contains( (int)name ) )
    {
        m_properties[(int)name]->setValue( value );
        return true;
    }
    else
    {
        //qDebug() << "*** ERROR *** SET" << m_properties[int::NAME]->getValue().toString() << Property::getNameAsString( name ) << name << "doesnt exist";
        exit( 0 );
        return false;
    }
}

bool ROIPropertyGroup::set( Fn::ROI name, bool value, bool visible )
{
    if ( m_properties.contains( (int)name ) )
    {
        m_properties[(int)name]->setValue( value );
    }
    else
    {
        PropertyBool* prop = new PropertyBool( Fn::ROI2String::s( (Fn::ROI)name ), value );
        m_properties[(int)name] = prop;
        connect( prop, SIGNAL( valueChanged() ), this, SLOT( slotPropChanged() ) );
        if ( visible )
        {
            m_visible.append( name );
        }
    }
    return true;
}

bool ROIPropertyGroup::set( Fn::ROI name, int value, bool visible )
{
    if ( m_properties.contains( (int)name ) )
    {
        m_properties[(int)name]->setValue( value );
    }
    else
    {
        PropertyInt* prop = new PropertyInt( Fn::ROI2String::s( (Fn::ROI)name ), value );
        m_properties[(int)name] = prop;
        connect( prop, SIGNAL( valueChanged() ), this, SLOT( slotPropChanged() ) );
        if ( visible )
        {
            m_visible.append( name );
        }
    }
    return true;
}

bool ROIPropertyGroup::set( Fn::ROI name, int value, int min, int max, bool visible )
{
    if ( m_properties.contains( (int)name ) )
    {
        return false;
    }
    else
    {
        PropertyInt* prop = new PropertyInt( Fn::ROI2String::s( (Fn::ROI)name ), value, min, max );
        m_properties[(int)name] = prop;
        connect( prop, SIGNAL( valueChanged() ), this, SLOT( slotPropChanged() ) );
        if ( visible )
        {
            m_visible.append( name );
        }
    }
    return true;
}

bool ROIPropertyGroup::set( Fn::ROI name, float value, bool visible )
{
    if ( m_properties.contains( (int)name ) )
    {
        m_properties[(int)name]->setValue( value );
    }
    else
    {
        PropertyFloat* prop = new PropertyFloat( Fn::ROI2String::s( (Fn::ROI)name ), value );
        m_properties[(int)name] = prop;
        connect( prop, SIGNAL( valueChanged() ), this, SLOT( slotPropChanged() ) );
        if ( visible )
        {
            m_visible.append( name );
        }
    }
    return true;
}

bool ROIPropertyGroup::set( Fn::ROI name, float value, float min, float max, bool visible )
{
    if ( m_properties.contains( (int)name ) )
    {
        return false;
    }
    PropertyFloat* prop = new PropertyFloat( Fn::ROI2String::s( (Fn::ROI)name ), value, min, max );
    m_properties[(int)name] = prop;
    connect( prop, SIGNAL( valueChanged() ), this, SLOT( slotPropChanged() ) );
    if ( visible )
    {
        m_visible.append( name );
    }
    return true;
}

bool ROIPropertyGroup::set( Fn::ROI name, QString value, bool visible )
{
    if ( m_properties.contains( (int)name ) )
    {
        m_properties[(int)name]->setValue( value );
    }
    else
    {
        PropertyString* prop = new PropertyString( Fn::ROI2String::s( (Fn::ROI)name ), value );
        m_properties[(int)name] = prop;
        connect( prop, SIGNAL( valueChanged() ), this, SLOT( slotPropChanged() ) );
        if ( visible )
        {
            m_visible.append( name );
        }
    }
    return true;
}

bool ROIPropertyGroup::set( Fn::ROI name, const char* value, bool visible )
{
    if ( m_properties.contains( (int)name ) )
    {
        m_properties[(int)name]->setValue( QString( value ) );
    }
    else
    {
        PropertyString* prop = new PropertyString( Fn::ROI2String::s( (Fn::ROI)name ), QString( value ) );
        m_properties[(int)name] = prop;
        connect( prop, SIGNAL( valueChanged() ), this, SLOT( slotPropChanged() ) );
        if ( visible )
        {
            m_visible.append( name );
        }
    }
    return true;
}

bool ROIPropertyGroup::set( Fn::ROI name, QColor value, bool visible )
{
    if ( m_properties.contains( (int)name ) )
    {
        m_properties[(int)name]->setValue( value );
    }
    else
    {
        PropertyColor* prop = new PropertyColor( Fn::ROI2String::s( name ), value );
        m_properties[(int)name] = prop;
        connect( prop, SIGNAL( valueChanged() ), this, SLOT( slotPropChanged() ) );
        if ( visible )
        {
            m_visible.append( name );
        }
    }
    return true;
}

bool ROIPropertyGroup::set( Fn::ROI name, std::initializer_list<QString>options, int value, bool visible )
{
    if ( m_properties.contains( (int)name ) )
    {
        m_properties[(int)name]->setValue( value );
    }
    else
    {
        PropertySelection* prop = new PropertySelection( Fn::ROI2String::s( name ), options, value );
        m_properties[(int)name] = prop;
        connect( prop, SIGNAL( valueChanged() ), this, SLOT( slotPropChanged() ) );
        if ( visible )
        {
            m_visible.append( name );
        }
    }
    return true;
}

QList<Fn::ROI> ROIPropertyGroup::getVisible()
{
    return m_visible;
}

QWidget* ROIPropertyGroup::getWidget( Fn::ROI name )
{
    return m_properties[(int)name]->getWidget();
}

void ROIPropertyGroup::slotPropChanged()
{
    emit( signalPropChanged( m_properties[(int)Fn::ROI::ID]->getValue().toInt() ) );
}

int ROIPropertyGroup::size() const
{
    return m_properties.size();
}
