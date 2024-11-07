//
// Created by dingjing on 11/6/24.
//

#ifndef assistant_TRAY_H
#define assistant_TRAY_H
#include <QClipboard>
#include <QSystemTrayIcon>
#include "3thrd/hotkey/qhotkey.h"

class TrayPrivate;
class Tray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit Tray(QObject* parent = nullptr);

    void online();
    void offline();

public Q_SLOTS:
    void handleHotkey();
    void showToolTip(const QString& message);

private:
    TrayPrivate*                            d_ptr;
    Q_DECLARE_PRIVATE(Tray);
};



#endif // assistant_TRAY_H
