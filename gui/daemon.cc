//
// Created by dingjing on 11/6/24.
//

#include "daemon.h"

Daemon::Daemon(int & argc, char * argv[], const char* appName)
    : SingletonApp(argc, argv, appName), mTray(new Tray(this))
{

}

void Daemon::run()
{
    mTray->show();
}
