//
// Created by dingjing on 11/6/24.
//

#include "tray.h"

QIcon createTransparentIcon(int width, int height, QColor color);

Tray::Tray(QObject* parent)
    : QSystemTrayIcon(parent)
{
    online();
}

void Tray::online()
{
    setIcon(QIcon(":/online.svg"));
}

void Tray::offline()
{
    setIcon(QIcon(":/offline.svg"));
}
