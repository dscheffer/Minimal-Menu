/*
 *   Copyright (c) 2018 Dennis Scheffer.
 *   
 *   This file is part of Minimal Menu.
 *   
 *   Minimal Menu is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *   
 *   Foobar is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *   
 *   You should have received a copy of the GNU General Public License
 *   along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __QDBusConnectionWrapperImpl_HPP_INCLUDED__  
#define __QDBusConnectionWrapperImpl_HPP_INCLUDED__

#include "QDBusConnectionWrapper.hpp"

#include <QDBusConnection>

class QDBusConnectionWrapperImpl : public QDBusConnectionWrapper {
    QDBusConnection conn;
public:
    QDBusConnectionWrapperImpl(QDBusConnection conn);
     bool send(const QDBusMessage message) override;
};

#endif //__QDBusConnectionWrapperImpl_HPP_INCLUDED__