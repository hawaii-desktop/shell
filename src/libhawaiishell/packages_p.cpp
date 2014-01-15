/****************************************************************************
 * This file is part of Hawaii Shell.
 *
 * Copyright (C) 2012-2014 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
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

#include "packages_p.h"

namespace Hawaii {

namespace Shell {

void ElementPackage::initializePackage(Package *package)
{
    package->setDefaultPackageRoot(QStringLiteral("hawaii/elements/"));

    // User interface
    package->addDirectoryDefinition("ui", QStringLiteral("ui"), tr("User Interface"));
}

void ShellPackage::initializePackage(Package *package)
{
    package->setDefaultPackageRoot(QStringLiteral("hawaii/shells/"));

    // Views
    package->addDirectoryDefinition("views", QStringLiteral("views"), tr("User interface for the views"));
    package->setMimeTypes("views", QStringList() << QStringLiteral("text/x-qml"));

    // Loader
    package->addFileDefinition("loader", QStringLiteral("loader.qml"),
                               tr("Shell loader"));
    package->setMimeTypes("loader", QStringList() << QStringLiteral("text/x-qml"));

    // Default layout
    package->addFileDefinition("defaultlayout", QStringLiteral("layout.js"),
                               tr("Default layout script"));
    package->setMimeTypes("defaultlayout", QStringList() << QStringLiteral("application/javascript"));
}

void LookAndFeelPackage::initializePackage(Package *package)
{
    package->setDefaultPackageRoot(QStringLiteral("hawaii/lookandfeel/"));

    // Previews
    package->addDirectoryDefinition("previews", QStringLiteral("previews"),
                                    tr("Preview images"));
    package->addFileDefinition("lockscreenpreview", QStringLiteral("previews/lockscreen.png"),
                               tr("Preview for the Lock Screen"));

    // Lock Screen
    package->addDirectoryDefinition("lockscreen", QStringLiteral("lockscreen"),
                                    tr("Lock screen user interface"));
    package->addFileDefinition("lockscreen", QStringLiteral("lockscreen/LockScreen.qml"),
                               tr("Main lock screen user interface file"));
}

} // namespace Shell

} // namespace Hawaii