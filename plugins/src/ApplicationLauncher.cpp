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

#include "ApplicationLauncher.hpp"
#include "QProcessWrapperImpl.hpp"

#include <pwd.h>
#include <sys/types.h>

#include <fstream>
#include <iostream>
#include <memory>

ApplicationLauncher::ApplicationLauncher(QObject *parent)
    : QObject(parent), process(new QProcessWrapperImpl(this))
{ }

void ApplicationLauncher::setAptCheck(QString aptCheck)
{
    this->aptCheck = aptCheck;
}

void ApplicationLauncher::setProcess(std::shared_ptr<QProcessWrapper> p)
{
    process = p;
}

void ApplicationLauncher::launch(const QString application, const QString mimetype)
{
    if (application.endsWith(".desktop")) {
        QStringList params;
        params << "exec" << application;
        process->startDetached("kioclient", params);
    } else if (!mimetype.isEmpty()) {
        QStringList params;
        params << "exec" << application << mimetype;
        process->startDetached("kioclient", params);
    } else {
        process->startDetached(application);
    }
    process->close();
}

void ApplicationLauncher::launchAboutComputer()
{
    launch(ABOUT_COMPUTER);
}

void ApplicationLauncher::launchSystemPreferences()
{
    launch(SYSTEM_PREFERENCES);
}

void ApplicationLauncher::launchUpdater()
{
    launch(UPDATER);
}

void ApplicationLauncher::launchAndWait(const QString application, const QStringList params)
{
    process->start(application, params);
    process->waitForFinished();
}

QString ApplicationLauncher::getUsername()
{
    QStringList params;
    params << "-u" << "-n";
    launchAndWait("id", params);
    return QString(process->readAllStandardOutput()).trimmed();
}

QString ApplicationLauncher::getFullUsername(const QString username)
{
    QStringList gecosSplit = QString(getpwnam(username.toLocal8Bit().data())->pw_gecos).split(",");
    if (gecosSplit.length() > 0) {
        return gecosSplit[0];
    }
    return "";
}

QString ApplicationLauncher::getUser()
{
    QString username = getUsername();
    QString fullname = getFullUsername(username);

    if (!fullname.isEmpty()) {
        return fullname;
    }

    return username;
}

int ApplicationLauncher::getUpdateCount()
{
    if (!fileExists(aptCheck.toStdString())) {
        std::cerr << "apt-check does not exist or is inaccessible" << std::endl;
        return 0;
    }
    QStringList params;
    params << aptCheck;

    launchAndWait("python", params);
    QString result = QString(process->readAllStandardError()).trimmed();

    QStringList updateSplit = result.split(";");

    bool ok = false;
    int count;
    count = updateSplit[0].toInt(&ok);
    if (ok) {
        return count;
    }

    return -1;
}

bool ApplicationLauncher::fileExists(const std::string fileName)
{
    std::ifstream infile(fileName.c_str());
    return infile.good();
}
