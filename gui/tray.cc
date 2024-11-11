//
// Created by dingjing on 11/6/24.
//

#include "tray.h"

#include <QRegExp>
#include <QClipboard>
#include <qdatetime.h>
#include <QKeySequence>
#include <sys/socket.h>
#include <QGuiApplication>

#include "daemon.h"
#include "tip-dialog.h"
#include "common/defines.h"
#include "common/ipc-base.h"
#include "3thrd/hotkey/qhotkey.h"


class TrayPrivate
{
public:
    explicit TrayPrivate(Tray* tray);

private:
    Tray*                       q_ptr;
    TipDialog*                  mTipDialog;
    QString                     mCurrentData;
    Q_DECLARE_PUBLIC(Tray);
};

TrayPrivate::TrayPrivate(Tray * tray)
    : q_ptr(tray), mTipDialog(new TipDialog(nullptr)), mCurrentData("")
{

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

    connect(new QHotkey(QKeySequence("Ctrl+q"), true, this), &QHotkey::activated, this, &Tray::handleQuit);
    connect(new QHotkey(QKeySequence("Ctrl+t"), true, this), &QHotkey::activated, this, &Tray::handleTranslation);

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

void Tray::handleQuit()
{
    Q_D(Tray);

    if (d->mTipDialog->isVisible()) {
        d->mTipDialog->setVisible(false);
    }
}


void Tray::handleTranslation()
{
    Q_D(Tray);

    if (d->mTipDialog->isVisible()) {
        d->mTipDialog->close();
    }

    d->mTipDialog->setSrcLabel(d->mCurrentData);
    const QByteArray resp = IpcBase::sendRawAndWaitResp(ASSISTANT_SOCKET_TRANSLATOR, d->mCurrentData.toUtf8(), true);
    d->mTipDialog->setDstLabel(resp);

    d->mTipDialog->show();
}

void Tray::showToolTip(const QString & message)
{
    Q_D(Tray);
    showMessage("", message, QSystemTrayIcon::NoIcon, -1);
}
