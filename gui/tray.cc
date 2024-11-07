//
// Created by dingjing on 11/6/24.
//

#include "tray.h"

#include <QRegExp>
#include <QClipboard>
#include <QKeySequence>
#include <sys/socket.h>
#include <QGuiApplication>

#include "daemon.h"
#include "3thrd/hotkey/qhotkey.h"


class TrayPrivate
{
public:
    explicit TrayPrivate(Tray* tray);

    bool checkCurrentDataIsEnglish();

private:
    Tray*                       q_ptr;
    QString                     mCurrentData;
    Q_DECLARE_PUBLIC(Tray);
};

TrayPrivate::TrayPrivate(Tray * tray)
    : q_ptr(tray)
{
}

bool TrayPrivate::checkCurrentDataIsEnglish()
{
    static QRegExp regExp("[!@#$%^&*()_+-=,./;'[]\\{}|:\"<>?0-9a-zA-Z\r\n]?");

    if (regExp.exactMatch(mCurrentData.left(100))) {
        return true;
    }

    return false;
}

Tray::Tray(QObject* parent)
    : QSystemTrayIcon(parent), d_ptr(new TrayPrivate(this))
{
    Q_D(Tray);

    connect(QGuiApplication::clipboard(), &QClipboard::changed, this, [=] (QClipboard::Mode mode) ->void {
        switch (mode) {
            case QClipboard::Clipboard: {
                d->mCurrentData = QGuiApplication::clipboard()->text(QClipboard::Clipboard);
                break;
            }
            case QClipboard::Selection: {
                d->mCurrentData = QGuiApplication::clipboard()->text(QClipboard::Selection);
                break;
            }
            case QClipboard::FindBuffer: {
                break;
            }
            default: {
                break;
            }
        }
    });

    connect(new QHotkey(QKeySequence("Ctrl+q"), true, this), &QHotkey::activated, this, &Tray::handleHotkey);

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

void Tray::handleHotkey()
{
    Q_D(Tray);

    if (d->checkCurrentDataIsEnglish()) {
        // 英文则翻译
        QString tip = QString("%1\n\n%2").arg(d->mCurrentData).arg(d->mCurrentData);
        showToolTip(tip);
        return;
    }

    showToolTip(d->mCurrentData);
}

void Tray::showToolTip(const QString & message)
{
    Q_D(Tray);
    showMessage("", message, QSystemTrayIcon::NoIcon, -1);
}
