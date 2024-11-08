//
// Created by dingjing on 11/7/24.
//

#include "tip-dialog.h"

#include <QVBoxLayout>


TipDialog::TipDialog(QWidget * parent)
    : QDialog(parent), mMainLayout(nullptr)
{
    setContentsMargins(8, 8, 8, 8);

    setWindowFlags(Qt::FramelessWindowHint);

    mMainLayout = new QVBoxLayout(this);
    mMainLayout->setContentsMargins(0, 0, 0, 0);






    setLayout(mMainLayout);
}

TipDialog::~TipDialog()
{
}
