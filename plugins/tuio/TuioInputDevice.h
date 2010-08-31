/*
    KetaRoller - an advanced signal router for musical devices

    Copyright (C) 2010 Dario Freddi <drf@kde.org>
    Copyright (C) 2010 Luca Mucci <luca.mucci@4cmp.it>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef TUIOINPUTDEVICE_H
#define TUIOINPUTDEVICE_H

#include "InputDevice.h"

#include "TuioListener.h"

#include <QtCore/QThread>
#include <QtCore/QHash>

#include <QtGui/QTouchEvent>
#include <QtGui/QWidget>

namespace KetaRoller {
class InputPort;
}

namespace TUIO {
class TuioClient;
}

class Q_DECL_EXPORT GrabberWidget : public QWidget
{
    Q_OBJECT
public:
    GrabberWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~GrabberWidget();

    virtual bool event(QEvent* event);
};

/**
 * @brief Class for Tuio input devices
 *
 * TuioInputDevice is the Tuio implementation of InputDevice class.
 * <br /><br />
 * You need this kind of device in order to receive and route Tuio messages from ReacTIVision system.
 * <br /><br />
 * TuioInputDevice uses 3rd party Tuio C++ framework (developed by Martin Kaltenbrunner, MTG) to obtain
 * realtime Tuio Cursor and FiducialObject info. TuioInputDevice implements 3rd party TuioListener,
 * adding, updating and removing Tuio elements: the info are extracted internally by the 3rd party
 * Tuio framework from OSC bundle messages generated by ReacTIVision.
 * <br /><br />
 * The Tuio Cursor management is still under development (it will exploit the QtGestures facilities).
 * <br /><br />
 * Still, consider that the whole logic for handling ports is contained into the InputDevice class.
 *
 * @sa KetaRoller::InputDevice
 *
 */
class Q_DECL_EXPORT TuioInputDevice : public KetaRoller::InputDevice, public TUIO::TuioListener
{
    Q_OBJECT
    Q_INTERFACES(KetaRoller::InputDevice)
    Q_DISABLE_COPY(TuioInputDevice)

public:
    TuioInputDevice(QObject* parent = 0);
    virtual ~TuioInputDevice();

    virtual void addTuioCursor(TUIO::TuioCursor* tcur);
    virtual void addTuioObject(TUIO::TuioObject* tobj);

    virtual void refresh(TUIO::TuioTime ftime);

    virtual void removeTuioCursor(TUIO::TuioCursor* tcur);
    virtual void removeTuioObject(TUIO::TuioObject* tobj);

    virtual void updateTuioCursor(TUIO::TuioCursor* tcur);
    virtual void updateTuioObject(TUIO::TuioObject* tobj);

protected:
    /**
    * @brief Initialize the TuioInputDevice.
    *
    * This function initializes the TuioListener superclass and opens a socket with
    * reacTIVision.
    */
    virtual void init(const QVariantMap& args = QVariantMap());
    virtual bool validatePort(KetaRoller::InputPort* port);

private slots:
    void onPortAdded(KetaRoller::InputPort*);
    void onPortRemoved(KetaRoller::InputPort*);

private:
    QHash< qint64, QList< QTouchEvent::TouchPoint > > m_touchPoints;
    QHash< qint32, KetaRoller::InputPort* > m_portForSymbol;
    QHash< Qt::GestureType, KetaRoller::InputPort* > m_portForGesture;
    QWidget *m_widget;
    QRect m_screenRect;
    TUIO::TuioClient *m_tuioClient;

    QTouchEvent::TouchPoint tuioCursorToTouchPoint(TUIO::TuioCursor *tcur);
};

#endif // TUIOINPUTDEVICE_H
