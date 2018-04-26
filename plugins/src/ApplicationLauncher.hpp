#ifndef __ApplicationLauncher_HPP_INCLUDED__  
#define __ApplicationLauncher_HPP_INCLUDED__

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

#include "config.hpp"
#include "QProcessWrapper.hpp"

#include <memory>

#include <QProcess>

class ApplicationLauncher : public QObject {
    Q_OBJECT

    bool fileExists(const std::string path);
    void launchAndWait(const QString application, const QStringList params);

    std::shared_ptr<QProcessWrapper> process;
    QString aptCheck = "/usr/lib/update-notifier/apt_check.py";

public:
    ApplicationLauncher(QObject *parent = 0);
    QString getUsername();
    QString getFullUsername(const QString username);
    void setAptCheck(QString aptCheck);
    void setProcess(std::shared_ptr<QProcessWrapper> p);
public Q_SLOTS:
    void launchAboutComputer();
    void launchSystemPreferences();
    void launchUpdater();
    void launch(const QString application, const QString mimetype = "");
    QString getUser();
    int getUpdateCount();
};

#endif //__ApplicationLauncher_HPP_INCLUDED__