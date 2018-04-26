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
import org.kde.plasma.plasmoid 2.0                                                                                                                      

Item {
    width: 64
    height: 64

    Plasmoid.fullRepresentation: MainMenu { }

    Plasmoid.preferredRepresentation: Plasmoid.fullRepresentation
}