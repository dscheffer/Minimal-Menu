#ifndef __KSMClient_HPP_INCLUDED__  
#define __KSMClient_HPP_INCLUDED__

#include "QDBusConnectionWrapper.hpp"

#include <memory>

#include <QObject>
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

#include <QtDBus>

class KSMClient : public QObject {

    Q_OBJECT

    int logoutType;
    std::shared_ptr<QDBusConnectionWrapper> conn;

    QDBusMessage createMessage(const QString method);
    void sendMessage(const QDBusMessage message);

public:
    KSMClient(QObject *parent = 0);
    KSMClient(int type, QObject *parent = 0);

    void setConnection(std::shared_ptr<QDBusConnectionWrapper> connection);
public Q_SLOTS:
    void switchUser();
    void logout();
    void shutdown();
    void reboot();
};

#endif //__KSMClient_HPP_INCLUDED__