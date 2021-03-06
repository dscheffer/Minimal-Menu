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

#ifndef __RecentlyUsedHandler_HPP_INCLUDED__
#define __RecentlyUsedHandler_HPP_INCLUDED__

#include "ActivityEntry.hpp"

#include <KActivities/Stats/Query>
#include <KActivities/Stats/Terms>

#include <memory>

#include <QDBusConnection>
#include <QDBusInterface>

#include <QObject>
#include <QQmlListProperty>
#include <QTimer>

#include <QVector>

namespace KAStats = KActivities::Stats;

using namespace KAStats;
using namespace KAStats::Terms;

class RecentlyUsedHandler : public QObject {
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<ActivityEntry> recentlyUsedApplications READ getRecentlyUsedApplications)
    Q_PROPERTY(QQmlListProperty<ActivityEntry> recentlyUsedDocuments READ getRecentlyUsedDocuments)

    const Query query = UsedResources
        | RecentlyUsedFirst
        | Agent::any()
        | Type::any()
        | Activity::current();

    QList<ActivityEntry*> recentlyUsedApplications;
    QList<ActivityEntry*> recentlyUsedDocuments;
public:
    const int recentlyUsedCount = 10;

    RecentlyUsedHandler(QObject *obj = 0);
    virtual ~RecentlyUsedHandler();

    QQmlListProperty<ActivityEntry> getRecentlyUsedApplications();
    QQmlListProperty<ActivityEntry> getRecentlyUsedDocuments();
public Q_SLOTS:
    void update();
signals:
    void updated();
};

#endif //__RecentlyUsedHandler_HPP_INCLUDED__