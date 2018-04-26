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
import org.kde.plasma.components 2.0 as PlasmaComponents                                                                    
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.plasmoid 2.0

import QtQuick.Window 2.2

Item {
    anchors.fill: parent
    MouseArea {
        id: menu
        anchors.fill: parent
        z: 2
        PlasmaCore.IconItem {
            id: buttonIcon

            anchors.fill: parent
            source: "start-here-kde"
            active: parent.containsMouse
            smooth: true
            roundToIconSize: true
        }

        ContextMenu {
            id: ctxMenu
        }
    
        onClicked: { 
            if (ctxMenu.isOpen()) {
                ctxMenu.close();
            } else if (ctxMenu.isClosed()) {
                var x = 0;
                var y = 0;
                if (plasmoid.location == PlasmaCore.Types.LeftEdge) {
                    x = menu.x + menu.width;
                    y = menu.y;
                } else if (plasmoid.location == PlasmaCore.Types.RightEdge) {
                    x = menu.x - ctxMenu.width;
                    console.log("X " + x);
                    y = menu.y;
                } else if (plasmoid.location == PlasmaCore.Types.BottomEdge) {
                    x = menu.x;
                    //y = menu.y - ctxMenu.childrenRect.height;
                    y = menu.y - (8*27) - (4*5); //8 Items and 4 seperators
                    console.log("Y " + y)
                } else {
                    x = menu.x;
                    y = menu.y + menu.height;
                }

                //Clip to screen edges
                x = (x + ctxMenu.width) > Screen.width ? Screen.width - ctxMenu.width : x;
                y = (y + ctxMenu.height) > Screen.height ? Screen.height - ctxMenu.height : y;

                ctxMenu.open(x, y);
            }
        }

    }
}