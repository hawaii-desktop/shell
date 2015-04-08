/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2015 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:LGPL2.1+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QtCore/QStandardPaths>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>

#include "processrunner.h"

ProcessRunner::ProcessRunner(QObject *parent)
    : QObject(parent)
{
}

bool ProcessRunner::launchApplication(const QString &name)
{
    const QString fileName = QStandardPaths::locate(QStandardPaths::ApplicationsLocation,
                                                    name + QStringLiteral(".desktop"));
    if (fileName.isEmpty())
        return false;

    const QDBusConnection bus = QDBusConnection::sessionBus();
    QDBusInterface interface("org.hawaii.session", "/HawaiiSession", "org.hawaii.launcher", bus);
    QDBusMessage msg = interface.call("launchDesktopFile", fileName);
    return msg.arguments().at(0).toBool();
}