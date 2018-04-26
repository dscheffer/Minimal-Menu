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

#include "ActivityEntry.hpp"
#include "ApplicationLauncher.hpp"
#include "KSMClient.hpp"
#include "PlasmoidPlugin.hpp"
#include "RecentlyUsedHandler.hpp"

#include "config.hpp"

#include <QtQml>

void PlasmoidPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<ActivityEntry>(uri, MAJOR_VERSION, MINOR_VERSION, "ActivityEntry");
    qmlRegisterSingletonType<ApplicationLauncher>(uri, MAJOR_VERSION, MINOR_VERSION, "ApplicationLauncher", [](QQmlEngine * engine, QJSEngine * scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        ApplicationLauncher *launcher = new ApplicationLauncher();
        return launcher;
    });

    qmlRegisterSingletonType<KSMClient>(uri, MAJOR_VERSION, MINOR_VERSION, "KSMClient", [](QQmlEngine * engine, QJSEngine * scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        KSMClient *client = new KSMClient();
        return client;
    });

    qmlRegisterSingletonType<RecentlyUsedHandler>(uri, MAJOR_VERSION, MINOR_VERSION, "RecentlyUsedHandler", [](QQmlEngine * engine, QJSEngine * scriptEngine) -> QObject * {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)

        RecentlyUsedHandler *handler = new RecentlyUsedHandler();
        return handler;
    });
}