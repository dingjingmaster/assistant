//
// Created by dingjing on 11/7/24.
//

#ifndef assistant_TIP_DIALOG_H
#define assistant_TIP_DIALOG_H
#include <QDialog>


class TipDialog final : public QDialog
{
    Q_OBJECT
public:
    explicit TipDialog(QWidget *parent = nullptr);
    ~TipDialog() override;

private:
    QLayout*                    mMainLayout;

};



#endif // assistant_TIP_DIALOG_H
