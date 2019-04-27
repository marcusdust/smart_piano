/****************************************************************************

    Copyright (c)   2008-2009, L. J. Barman, all rights reserved

    This file is part of the PianoBooster application

    PianoBooster is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PianoBooster is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PianoBooster.  If not, see <http://www.gnu.org/licenses/>.

****************************************************************************/

#include <QApplication>
#include <QTranslator>

#include <QtOpenGL>
#include "QtWindow.h"
 
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    printf("\n\n\nwocao, hahaha\n\n");
    
    // See: http://doc.qt.nokia.com/latest/i18n-source-translation.html
    
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
        // Look for the translations file in the system's translation path
        QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    QTranslator appTranslator;
    appTranslator.load("pianobooster_" + QLocale::system().name(),
        // Look for the translations file in the specified path
        "/usr/share/games/pianobooster/translations/");
    app.installTranslator(&appTranslator);
    
    if (!QGLFormat::hasOpenGL()) {
        QMessageBox::information(0, QMessageBox::tr("OpenGL support"),
                 QMessageBox::tr("This system does not support OpenGL which is needed to run Piano Booster."));
        return -1;
    }

    QtWindow window;
    
    window.show();
    return app.exec();
}

