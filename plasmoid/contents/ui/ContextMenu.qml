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

Item {
    id: ctxMenuWrapperWrapper
    width: ctxMenuWrapper.width
    height: ctxMenuWrapper.height

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

    Component {
        id: submenuComponent
        PlasmaComponents.ContextMenu {
            id: submenu
            visualParent: recentActivities.action
        }
    }

    Connections {
        target: RecentlyUsedHandler
        onUpdated: {
            var submenuObject = submenuComponent.createObject(recentActivities);

            submenuObject.addSection("Applications");

            for(var i = 0; i < RecentlyUsedHandler.recentlyUsedApplications.length; i++) {
                var item = RecentlyUsedHandler.recentlyUsedApplications[i];
                var params = {};
                params.resource = item.resource;
                params.name = item.name;
                params.iconRes = item.icon;
                params.mimetype = item.mimetype;
                var item = submenuItem.createObject(null, params);
                submenuObject.addMenuItem(item, null);
                ctxMenu.recentActivitiesItems.push(item);
            }

            var item = Qt.createQmlObject("import org.kde.plasma.components 2.0 as PlasmaComponents; PlasmaComponents.MenuItem {separator: true}", submenuObject);
            ctxMenu.recentActivitiesItems.push(item);
            submenuObject.addMenuItem(item, null);

            submenuObject.addSection("Documents");
            
            for(var i = 0; i < RecentlyUsedHandler.recentlyUsedDocuments.length; i++) {
                var item = RecentlyUsedHandler.recentlyUsedDocuments[i];
                var params = {};
                params.resource = item.resource;
                params.name = item.name;
                params.iconRes = item.icon;
                params.mimetype = item.mimetype;
                var item = submenuItem.createObject(null, params);
                submenuObject.addMenuItem(item, null);
                ctxMenu.recentActivitiesItems.push(item);
            }

            ctxMenu.recentActivitiesSubmenu = submenuObject;
        }
    }

    Component.onCompleted: {
        RecentlyUsedHandler.update();
    }

    Item {
        id: ctxMenuWrapper
        width: 300

        function open(x, y) {
            ctxMenuWrapper.x = x;
            ctxMenuWrapper.y = y;
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
                    for(var i = ctxMenu.recentActivitiesSubmenu.content.length-1; i >=0; i--) {
                        var item = ctxMenu.recentActivitiesSubmenu.content[i];
                        ctxMenu.recentActivitiesSubmenu.removeMenuItem(item)
                        item.destroy();
                    }

                    ctxMenu.recentActivitiesSubmenu.destroy();
                    gc();
                    RecentlyUsedHandler.update();
                }

                if (count == 0) {
                    ctxMenu.updateCount = ApplicationLauncher.getUpdateCount();
                }
                count = (count + 1) % 30;
            }
        }

        PlasmaComponents.ContextMenu {
            id: ctxMenu
            minimumWidth: ctxMenuWrapper.width

            property var recentActivitiesSubmenu
            property var recentActivitiesItems: []
            
            Component.onCompleted: {
                ctxMenu.updateCount = ApplicationLauncher.getUpdateCount();
            }

            property var updateCount: 0

            PlasmaComponents.MenuItem {
                text: i18n("About This Computer")
                onClicked: {
                    maskMouseArea.enabled = false;
                    ApplicationLauncher.launchAboutComputer();
                }
            }

            PlasmaComponents.MenuItem {
                separator: true
            }

            PlasmaComponents.MenuItem {
                text: i18n("System Preferences")
                onClicked: {
                    maskMouseArea.enabled = false;
                    ApplicationLauncher.launchSystemPreferences();
                }
            }

            PlasmaComponents.MenuItem {
                id: softwareUpdates
                text: ctxMenu.updateCount <= 0 ? i18n("Software Updates") : i18n("Software Updates") + "\t " + ctxMenu.updateCount
                onClicked: {
                    maskMouseArea.enabled = false;
                    ApplicationLauncher.launchUpdater();
                }
            }

            PlasmaComponents.MenuItem {
                separator: true
            }

            PlasmaComponents.MenuItem {
                id: recentActivities
                text: i18n("Recent Items")
            }

            PlasmaComponents.MenuItem {
                separator: true
            }

            PlasmaComponents.MenuItem {
                text: i18n("Switch User...")

                onClicked: {
                    maskMouseArea.enabled = false;
                    KSMClient.switchUser();
                }
            }

            PlasmaComponents.MenuItem {
                text: i18n("Restart...")

                onClicked: {
                    maskMouseArea.enabled = false;
                    KSMClient.reboot();
                }
            }

            PlasmaComponents.MenuItem {
                text: i18n("Shut Down...")

                onClicked: {
                    maskMouseArea.enabled = false;
                    KSMClient.shutdown();
                }
            }

            PlasmaComponents.MenuItem {
                separator: true
            }

            PlasmaComponents.MenuItem {
                text: i18n("Log Out %1", ApplicationLauncher.getUser())

                onClicked: {
                    maskMouseArea.enabled = false;
                    KSMClient.logout();
                }
            }
        }
    }
    

    MouseArea {
        id: maskMouseArea
        parent: getRootComponent(menu)
        anchors.fill: parent
        enabled: false;
        z: -1
        onClicked: {
            enabled = false;
            ctxMenu.close(); 
        }

        function getRootComponent(component) {
            var result = component;
            while (result.parent) {
                result = result.parent
            }
            return result;
        }
    }

    function open(x, y) {
        ctxMenuWrapper.open(x, y);
        maskMouseArea.enabled = true;
    }

    function close() {
        maskMouseArea.enabled = false;
        ctxMenuWrapper.close();
    }

    function isOpen() {
        return ctxMenu.status === PlasmaComponents.DialogStatus.Open;
    }

    function isClosed() {
        return ctxMenu.status === PlasmaComponents.DialogStatus.Closed;
    }
}