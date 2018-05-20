import QtQuick 2.6
import QtQuick.Templates 2.3 as T
import org.kde.plasma.core 2.0 as PlasmaCore

T.MenuItem {
    id: controlRoot

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             Math.max(contentItem.implicitHeight,
                                      indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    leftPadding: highlight.margins.left
    topPadding: highlight.margins.top
    rightPadding: highlight.margins.right
    bottomPadding: highlight.margins.bottom
    spacing: units.smallSpacing
    hoverEnabled: true

    contentItem: Label {
        leftPadding: !controlRoot.mirrored ? (controlRoot.indicator ? controlRoot.indicator.width : 0) + controlRoot.spacing : 0
        rightPadding: controlRoot.mirrored ? (controlRoot.indicator ? controlRoot.indicator.width : 0) + controlRoot.spacing : 0

        text: controlRoot.text
        font: controlRoot.font
        color: theme.textColor
        elide: Text.ElideRight
        visible: controlRoot.text
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    indicator: CheckIndicator {
        x: controlRoot.mirrored ? controlRoot.width - width - controlRoot.rightPadding : controlRoot.leftPadding
        y: controlRoot.topPadding + (controlRoot.availableHeight - height) / 2

        visible: controlRoot.checkable
        control: controlRoot
    }

    background: Item {
        implicitWidth: units.gridUnit * 8

        PlasmaCore.FrameSvgItem {
            id: highlight
            imagePath: "widgets/viewitem"
            prefix: "hover"
            colorGroup: PlasmaCore.ColorScope.colorGroup
            anchors.fill: parent
            opacity: controlRoot.hovered && !controlRoot.pressed ? 1 : 0
            Behavior on opacity {
                NumberAnimation {
                    duration: units.longDuration
                }
            }
        }
    }
}