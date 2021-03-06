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

#include "MIDIMessage.h"
#include <vector>

class MIDIMessage::Data : public QSharedData
{
public:
    Data()
        : type(MIDIMessage::UnknownEvent)
        , data1(0)
        , data2(0)
    {
    };
    Data(MIDIMessage::Type messageType, quint16 dataByte1, quint16 dataByte2)
        :type(messageType)
        ,data1(dataByte1)
        ,data2(dataByte2)
    {
    }
    Data(const Data &other)
        :type(other.type)
        ,data1(other.data1)
        ,data2(other.data2)
    {
    }
    ~Data() {}

    MIDIMessage::Type type;
    quint16 data1;
    quint16 data2;
};

MIDIMessage MIDIMessageFactory::generateMidiMessage(std::vector<unsigned char> rawMessage)
{
    quint32 nBytes = rawMessage.size();
    if ( nBytes > 0 )
    {
        //if the message is a note on/off, control change or pitch bender (control the status byte)
        int type = static_cast<int>(rawMessage[0]);

        quint16 dataByte1 = static_cast<quint16>(rawMessage[1]);
        quint16 dataByte2 = static_cast<quint16>(rawMessage[2]);

        switch (type) {
            case 128:
                return MIDINoteOffEvent(dataByte1, dataByte2);
                break;
            case 144:
                return MIDINoteOnEvent(dataByte1, dataByte2);
                break;
            case 176:
                return MIDIControlChangeEvent(dataByte1, dataByte2);
                break;
            case 224:
                return MIDIPitchBenderEvent(dataByte1, dataByte2);
                break;
            default:
                break;
        }
    } else {
        // Iddio
    }

    return MIDIMessage();
}

///// MIDI Generic Message

MIDIMessage::MIDIMessage()
        : d(new Data)
{
}

MIDIMessage::MIDIMessage(MIDIMessage::Type messageType, quint16 data1, quint16 data2)
        : d(new Data(messageType, data1, data2))
{

}

MIDIMessage::MIDIMessage(const MIDIMessage& other)
        : d(other.d)
{
}

MIDIMessage::~MIDIMessage()
{
}

bool MIDIMessage::operator==(const MIDIMessage& other) const
{
    return (d->data1 == other.d->data1) && (d->data2 == other.d->data2) && (d->type == other.d->type);
}

MIDIMessage& MIDIMessage::operator=(const MIDIMessage& rhs)
{
    if (this==&rhs) return *this;   //Protect against self-assignment
    d = rhs.d;
    return *this;
}

quint16 MIDIMessage::data1() const
{
    return d->data1;
}

quint16 MIDIMessage::data2() const
{
    return d->data2;
}

MIDIMessage::Type MIDIMessage::type() const
{
    return d->type;
}

///// Note On

MIDINoteOnEvent::MIDINoteOnEvent()
        : MIDIMessage()
{

}

MIDINoteOnEvent::MIDINoteOnEvent(const MIDIMessage& message)
        : MIDIMessage(message)
{

}

MIDINoteOnEvent::MIDINoteOnEvent(quint16 data1, quint16 data2)
        : MIDIMessage(MIDIMessage::NoteOnEvent, data1, data2)
{
}

MIDINoteOnEvent::~MIDINoteOnEvent()
{
}

quint16 MIDINoteOnEvent::note() const
{
    return data1();
}

quint16 MIDINoteOnEvent::velocity() const
{
    return data2();
}

///// Note Off

MIDINoteOffEvent::MIDINoteOffEvent()
        : MIDIMessage()
{

}

MIDINoteOffEvent::MIDINoteOffEvent(const MIDIMessage& message)
        : MIDIMessage(message)
{

}

MIDINoteOffEvent::MIDINoteOffEvent(quint16 data1, quint16 data2)
        : MIDIMessage(MIDIMessage::NoteOffEvent, data1, data2)
{
}

MIDINoteOffEvent::~MIDINoteOffEvent()
{
}

quint16 MIDINoteOffEvent::note() const
{
    return data1();
}

quint16 MIDINoteOffEvent::velocity() const
{
    return data2();
}

///// Control Change

MIDIControlChangeEvent::MIDIControlChangeEvent()
        : MIDIMessage()
{

}

MIDIControlChangeEvent::MIDIControlChangeEvent(const MIDIMessage& message)
        : MIDIMessage(message)
{

}

MIDIControlChangeEvent::MIDIControlChangeEvent(quint16 data1, quint16 data2)
        : MIDIMessage(MIDIMessage::ControlChangeEvent, data1, data2)
{
}

MIDIControlChangeEvent::~MIDIControlChangeEvent()
{
}

quint16 MIDIControlChangeEvent::number() const
{
    return data1();
}

quint16 MIDIControlChangeEvent::value() const
{
    return data2();
}

///// Pitch Bend

MIDIPitchBenderEvent::MIDIPitchBenderEvent()
        : MIDIMessage()
{

}

MIDIPitchBenderEvent::MIDIPitchBenderEvent(quint16 data1, quint16 data2)
        : MIDIMessage(MIDIMessage::PitchBendEvent, data1, data2)
{
}

MIDIPitchBenderEvent::~MIDIPitchBenderEvent()
{
}

MIDIPitchBenderEvent::MIDIPitchBenderEvent(const MIDIMessage& other)
        : MIDIMessage(other)
{

}

bool MIDIPitchBenderEvent::operator==(const MIDIPitchBenderEvent& other) const
{
    return MIDIMessage::operator==(other);
}

quint16 MIDIPitchBenderEvent::value() const
{
    return (data1() << 7) + data2();
}

