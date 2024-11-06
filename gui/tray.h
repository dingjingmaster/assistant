//
// Created by dingjing on 11/6/24.
//

#ifndef assistant_TRAY_H
#define assistant_TRAY_H
#include <QSystemTrayIcon>


class Tray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit Tray(QObject* parent = nullptr);

    void online();
    void offline();
private:
};



#endif // assistant_TRAY_H
