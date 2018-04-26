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

#ifndef __ActivityEntry_HPP_INCLUDED__  
#define __ActivityEntry_HPP_INCLUDED__

#include <QObject>

class ActivityEntry : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString resource READ getResource WRITE setResource);
    Q_PROPERTY(QString icon READ getIcon WRITE setIcon);
    Q_PROPERTY(QString mimetype READ getMimetype WRITE setMimetype);
    Q_PROPERTY(QString name READ getName WRITE setName);

    QString resource;
    QString icon;
    QString mimetype;
    QString name;
public:
    ActivityEntry(QObject *obj = 0);
    ActivityEntry(QString resource, QString icon, QString mimetype, QString name, QObject *obj = 0);
    ActivityEntry(const ActivityEntry& entry);

    QString getResource();
    QString getIcon();
    QString getMimetype();
    QString getName();

    void setResource(QString resouce);
    void setIcon(QString icon);
    void setMimetype(QString mimetype);
    void setName(QString name);
};

#endif //__ActivityEntry_HPP_INCLUDED__  