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

#include "KSMClient.hpp"
#include "QDBusConnectionWrapperImpl.hpp"

KSMClient::KSMClient(QObject *parent)
    : QObject(parent),
      logoutType(1),
      conn(new QDBusConnectionWrapperImpl(QDBusConnection::sessionBus()))
{}

KSMClient::KSMClient(int logoutType, QObject *parent)
    : QObject(parent),
      logoutType(logoutType),
      conn(new QDBusConnectionWrapperImpl(QDBusConnection::sessionBus()))
{}

void KSMClient::setConnection(std::shared_ptr<QDBusConnectionWrapper> connection)
{
    this->conn = connection;
}

void KSMClient::logout()
{
    QDBusMessage message = createMessage("logout");
    message << logoutType << 0 << 0;
    sendMessage(message);
}

void KSMClient::shutdown()
{
    QDBusMessage message = createMessage("logout");
    message << logoutType << 2 << 0;
    sendMessage(message);
}

void KSMClient::reboot()
{
    QDBusMessage message = createMessage("logout");
    message << logoutType << 1 << 0;
    sendMessage(message);
}

void KSMClient::switchUser()
{
    sendMessage(createMessage("openSwitchUserDialog"));
}

QDBusMessage KSMClient::createMessage(const QString method)
{
    return QDBusMessage::createMethodCall(
               "org.kde.ksmserver",
               "/KSMServer",
               "",
               method
           );
}

void KSMClient::sendMessage(const QDBusMessage message)
{
    conn->send(message);
}

