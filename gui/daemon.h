//
// Created by dingjing on 11/6/24.
//

#ifndef assistant_DAEMON_H
#define assistant_DAEMON_H
#include <QObject>

#include "tray.h"
#include "3thrd/singleton/singleton-app-gui.h"


class Daemon final : public SingletonApp
{
    Q_OBJECT
public:
    explicit Daemon(int& argc, char* argv[], const char* appName="Assistant gui");

    void run();
private:
    Tray*                       mTray = nullptr;
};



#endif // assistant_DAEMON_H
