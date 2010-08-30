/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) <year>  <name of author>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/

#ifndef ABSTRACTPLUGINFACTORY_H
#define ABSTRACTPLUGINFACTORY_H

#include <QtCore/QObject>

namespace KetaRoller {

/**
 * @brief Abstract factory for creating InputDevices
 *
 * This class serves as an helper for creating instances of a plugin.
 * It's an internal class and should not be reimplemented directly - please
 * read @ref create_plugins_cmake_sec "CMake's documentation on creating plugins"
 * to learn how to autogenerate plugins.
 *
 * Please refer to the project documentation to learn how plugins have been implemented internally.
 */
class AbstractPluginFactory : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractPluginFactory)
public:
    AbstractPluginFactory(QObject* parent = 0);
    virtual ~AbstractPluginFactory();
};

}

#endif // ABSTRACTPLUGINFACTORY_H
