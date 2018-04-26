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

ActivityEntry::ActivityEntry(QObject* obj)
    : QObject(obj), resource(""), icon(""), mimetype(""), name("")
{ }

ActivityEntry::ActivityEntry(QString resource, QString icon, QString mimetype, QString name, QObject *obj)
    : resource(QString(resource)), icon(QString(icon)), mimetype(QString(mimetype)), name(QString(name)), QObject(obj)
{ }

ActivityEntry::ActivityEntry(const ActivityEntry& entry)
    : QObject(entry.parent())
{
    resource = QString(entry.resource);
    icon = QString(entry.icon);
    mimetype = QString(entry.mimetype);
    name = QString(entry.name);
}

QString ActivityEntry::getResource()
{
    return this->resource;
}

QString ActivityEntry::getIcon()
{
    return this->icon;
}

QString ActivityEntry::getMimetype()
{
    return this->mimetype;
}

QString ActivityEntry::getName()
{
    return this->name;
}

void ActivityEntry::setResource(QString resouce)
{
    this->resource = resource;
}

void ActivityEntry::setIcon(QString icon)
{
    this->icon = icon;
}

void ActivityEntry::setMimetype(QString mimetype)
{
    this->mimetype = mimetype;
}

void ActivityEntry::setName(QString name)
{
    this->name = name;
}