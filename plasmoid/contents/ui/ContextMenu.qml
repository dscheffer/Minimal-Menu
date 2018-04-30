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

import QtQuick 2.0
import QtQuick.Controls 1.4
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.plasma.core 2.0 as PlasmaCore

import dscheffer.minimalmenuplugin 0.1

PlasmaCore.Dialog {
    id: dialog
    property var hide

    hideOnWindowDeactivate: true
    visible: false

    backgroundHints: PlasmaCore.Types.NoBackground

    mainItem: Item {
        width: ctxMenu.width
        height: ctxMenu.height

        Component {
            id: submenuItem
            PlasmaComponents.MenuItem {
                property string name
                property string iconRes
                property string resource
                property string mimetype

                text: name
                icon: iconRes

                onClicked: {
                    ApplicationLauncher.launch(resource, mimetype);
                }
            }
        }

        Connections {
            target: RecentlyUsedHandler
            onUpdated: {
                for(var i = 0; i < RecentlyUsedHandler.recentlyUsed.length; i++) {
                    var item = RecentlyUsedHandler.recentlyUsed[i];
                    var params = {};
                    params.resource = item.resource;
                    params.name = item.name;
                    params.iconRes = item.icon;
                    params.mimetype = item.mimetype;
                    var item = submenuItem.createObject(submenu, params);
                }
            }
        }

        Component.onCompleted: {
            RecentlyUsedHandler.update();
        }

        Item {
            id: ctxMenuWrapper
            width: 300

            function open() {
                ctxMenu.open(0, 0);
            }

            function close() {
                ctxMenu.close();
            }

            Timer {
                id: updateTimer
                interval: 2000
                repeat: true
                running: true

                property int count: 0

                onTriggered: {
                    if (isClosed()) {
                        for(var i = submenu.content.length-1; i >= 0 ; i--) {
                            var item = submenu.content[i];
                            submenu.removeMenuItem(item);
                            item.destroy();
                        };
                        gc();
                        RecentlyUsedHandler.update();
                    }

                    if (count == 0) {
                        ctxMenu.updateCount = ApplicationLauncher.getUpdateCount();
                    }
                    count = (count + 1) % 30;
                }
            }

            PlasmaComponents.Menu {
                id: ctxMenu
                minimumWidth: ctxMenuWrapper.width
                
                Component.onCompleted: {
                    ctxMenu.updateCount = ApplicationLauncher.getUpdateCount();
                }

                property var updateCount: 0

                PlasmaComponents.MenuItem {
                    text: i18n("About This Computer")
                    onClicked: ApplicationLauncher.launchAboutComputer();
                }

                PlasmaComponents.MenuItem {
                    separator: true
                }

                PlasmaComponents.MenuItem {
                    text: i18n("System Preferences")
                    onClicked: ApplicationLauncher.launchSystemPreferences();
                }

                PlasmaComponents.MenuItem {
                    id: softwareUpdates
                    text: ctxMenu.updateCount <= 0 ? i18n("Software Updates") : i18n("Software Updates") + "\t " + ctxMenu.updateCount
                    onClicked: ApplicationLauncher.launchUpdater();
                }

                PlasmaComponents.MenuItem {
                    separator: true
                }

                PlasmaComponents.MenuItem {
                    id: recentActivities
                    text: i18n("Recently Used")
                    
                    PlasmaComponents.Menu {
                        id: submenu
                        visualParent: recentActivities.action
                    }
                }

                PlasmaComponents.MenuItem {
                    separator: true
                }

                PlasmaComponents.MenuItem {
                    text: i18n("Switch User...")

                    onClicked: KSMClient.switchUser();
                }

                PlasmaComponents.MenuItem {
                    text: i18n("Reboot...")

                    onClicked: KSMClient.reboot();
                }

                PlasmaComponents.MenuItem {
                    text: i18n("Shutdown...")

                    onClicked: KSMClient.shutdown();
                }

                PlasmaComponents.MenuItem {
                    separator: true
                }

                PlasmaComponents.MenuItem {
                    text: i18n("Log Out %1", ApplicationLauncher.getUser())

                    onClicked: KSMClient.logout();
                }
            }
        }
    }

    onVisibleChanged: {
        if (visible == false && isOpen()) {
            ctxMenuWrapper.close();
        }
    }

    function open(x, y) {
        var pos = menu.mapToGlobal(x, y);
        dialog.x = pos.x;
        dialog.y = pos.y;
        ctxMenuWrapper.open();
        dialog.visible = true;
    }

    function close() {
        ctxMenuWrapper.close();
        dialog.visible = false;
    }

    function isOpen() {
        return ctxMenu.status === PlasmaComponents.DialogStatus.Open;
    }

    function isClosed() {
        return ctxMenu.status === PlasmaComponents.DialogStatus.Closed;
    }
}