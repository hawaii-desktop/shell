/****************************************************************************
 * This file is part of Hawaii Shell.
 *
 * Copyright (C) 2012-2014 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

import QtQuick 2.0
import QtCompositor 1.0
import GreenIsland 1.0
import org.kde.plasma.core 2.0 as PlasmaCore

Item {
    property var child
    property bool unresponsive: false
    property var animation: null

    id: window
    objectName: "clientWindow"
    states: [
        State {
            name: "focused"
            when: child.focus && !window.unresponsive
            PropertyChanges { target: unresponsiveEffectLoader; source: "" }
        },
        State {
            name: "unfocused"
            when: !child.focus && !window.unresponsive
            PropertyChanges { target: unresponsiveEffectLoader; source: "" }
        },
        State {
            name: "focused-unresponsive"
            when: child.focus && window.unresponsive
            PropertyChanges { target: unresponsiveEffectLoader; source: "overlays/UnresponsiveOverlay.qml" }
        },
        State {
            name: "unfocused-unresponsive"
            when: !child.focus && window.unresponsive
            PropertyChanges { target: unresponsiveEffectLoader; source: "overlays/UnresponsiveOverlay.qml" }
        }
    ]
    rotation: {
        switch (_greenisland_output.transform) {
        case WaylandOutput.Transform90:
            return 90;
        case WaylandOutput.TransformFlipped90:
            return -90;
        case WaylandOutput.Transform180:
            return 180;
        case WaylandOutput.TransformFlipped180:
            return -180;
        case WaylandOutput.Transform270:
            return 270;
        case WaylandOutput.TransformFlipped270:
            return -270;
        default:
            break;
        }

        return 0;
    }
    onVisibleChanged: {
        if (child)
            child.surface.clientRenderingEnabled = visible;
    }

    SurfaceRenderer {
        anchors.fill: parent
        source: child
        z: 1
    }

    /*
     * Connections to child or surface
     */

    Connections {
        target: child
        onSurfaceDestroyed: runDestroyAnimation()
    }

    Connections {
        target: child.surface
        onPong: pongSurface()
        onSizeChanged: setSize()
        onUnmapped: runUnmapAnimation()
    }

    /*
     * Animations
     */

    function runMapAnimation() {
        if (animation && animation.mapAnimation)
            animation.mapAnimation.start();
    }

    function runUnmapAnimation() {
        if (animation && animation.unmapAnimation)
            animation.unmapAnimation.start();
    }

    function runDestroyAnimation() {
        if (animation && animation.destroyAnimation)
            animation.destroyAnimation.start();
    }

    /*
     * Ping/pong
     */

    Loader {
        id: unresponsiveEffectLoader
        anchors.fill: parent
        z: visible ? 2 : 0
        visible: status == Loader.Ready
    }

    Timer {
        id: pingPongTimer
        interval: 200
        onTriggered: unresponsive = true
    }

    function pingSurface() {
        // Ping logic applies only to windows actually visible
        if (!visible)
            return;

        // Ping the surface to see whether it's responsive, if a pong
        // doesn't arrive before the timeout is trigger we know the
        // surface is unresponsive and raise the flag
        child.surface.ping();
        pingPongTimer.running = true;
    }

    function pongSurface() {
        // Surface replied with a pong this means it's responsive
        pingPongTimer.running = false;
        unresponsive = false;
    }

    /*
     * Miscellaneous
     */

    function setSize() {
        window.width = child.surface.size.width;
        window.height = child.surface.size.height;
    }
}