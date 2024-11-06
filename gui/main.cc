//
// Created by dingjing on 11/6/24.
//
#include "daemon.h"

int main (int argc, char *argv[])
{
    Daemon::setApplicationName(Daemon::tr("Assistant gui"));
    Daemon::setApplicationVersion(PACKAGE_VERSION);
    Daemon app(argc, argv);

    app.run();

    return app.exec();
}