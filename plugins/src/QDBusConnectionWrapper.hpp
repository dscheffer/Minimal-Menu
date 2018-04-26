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
 *   Minimal Menu is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *   
 *   You should have received a copy of the GNU General Public License
 *   along with Minimal Menu.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __QDBusConnectionWrapper_HPP_INCLUDED__  
#define __QDBusConnectionWrapper_HPP_INCLUDED__

#include <QDBusMessage>

class QDBusConnectionWrapper {    
public:
    QDBusConnectionWrapper() { };
    virtual ~QDBusConnectionWrapper() { };
    virtual bool send(const QDBusMessage message) = 0;
};

#endif //__QDBusConnectionWrapper_HPP_INCLUDED__