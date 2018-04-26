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

#include "RecentlyUsedHandler.hpp"
#include "ApplicationLauncher.hpp"

#include <KActivities/Stats/ResultSet>
#include <KDesktopFile>

#include <QCoreApplication>
#include <QObject>

#include <iostream>

namespace KAStats = KActivities::Stats;

using namespace KAStats;
using namespace KAStats::Terms;

RecentlyUsedHandler::RecentlyUsedHandler(QObject *obj)
    : QObject(obj), recentlyUsed()
{ }

RecentlyUsedHandler::~RecentlyUsedHandler()
{
    qDeleteAll(this->recentlyUsed);
}

void RecentlyUsedHandler::update()
{
    std::unique_ptr<ResultSet> r(new ResultSet(query));
    ResultSet::const_iterator resultIt = r->begin();

    qDeleteAll(recentlyUsed);
    recentlyUsed.clear();
    while (recentlyUsed.length() < recentlyUsedCount && resultIt != r->end()) {
        QString resource = resultIt->resource();
        std::cerr << resource.toStdString() << std::endl;
        QString mimetype = resultIt->mimetype();
        if (resource.startsWith("applications:") && mimetype.isEmpty()) {
            //Try standard locations
            std::unique_ptr<KDesktopFile> desktopFile(new KDesktopFile(resource.split(":")[1]));
            QString path = QStandardPaths::locate(desktopFile->resource(), desktopFile->fileName());

            //If not present in standard locations, try kservices
            if (desktopFile->readName().isEmpty()) {
                path = "/usr/share/kservices5/" + resource.split(":")[1];
                desktopFile = std::unique_ptr<KDesktopFile>(new KDesktopFile(path));
            }

            if (!desktopFile->readName().isEmpty()) {
                this->recentlyUsed.append(new ActivityEntry(
                                              path,
                                              desktopFile->readIcon(),
                                              "",
                                              desktopFile->readName()));
            }
        } else if (!mimetype.isEmpty()) {
            QString icon = QString(mimetype);
            icon = icon.replace("/", "-");
            QString name = resource.split("/").last();
            this->recentlyUsed.append(new ActivityEntry(resource, icon, mimetype, name));
        }

        ++resultIt;
    }

    emit updated();
}

QQmlListProperty<ActivityEntry> RecentlyUsedHandler::getRecentlyUsed()
{
    return QQmlListProperty<ActivityEntry>(this, this->recentlyUsed);
}