//
// Created by dingjing on 11/7/24.
//

#ifndef assistant_TIP_DIALOG_H
#define assistant_TIP_DIALOG_H
#include <QDialog>

class QLabel;
class TipDialog final : public QDialog
{
    Q_OBJECT
public:
    explicit TipDialog(QWidget *parent = nullptr);
    ~TipDialog() override;

    void setSrcLabel(const QString& label);
    void setDstLabel(const QString& label);

private:
    QLayout*                    mMainLayout;
    QLabel*                     mSrcLabel;
    QLabel*                     mDstLabel;
};



#endif // assistant_TIP_DIALOG_H
