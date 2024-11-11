//
// Created by dingjing on 11/7/24.
//

#include "tip-dialog.h"

#include <QLabel>
#include <QVBoxLayout>

#include "daemon.h"


TipDialog::TipDialog(QWidget * parent)
    : QDialog(parent), mMainLayout(nullptr), mSrcLabel(nullptr), mDstLabel(nullptr)
{
    setContentsMargins(8, 8, 8, 8);

    setFocusPolicy(Qt::ClickFocus);
    setMaximumSize(QSize(1024, 768));
    setWindowFlags(Qt::FramelessWindowHint);

    mMainLayout = new QVBoxLayout;
    mMainLayout->setContentsMargins(0, 0, 0, 0);

    auto vLayout = new QVBoxLayout;
    auto title = new QLabel(tr("原文"));
    mSrcLabel = new QLabel;
    mSrcLabel->setWordWrap(true);

    vLayout->addWidget(title);
    vLayout->addWidget(mSrcLabel);
    mMainLayout->addItem(vLayout);

    auto vLayout2 = new QVBoxLayout;
    auto title2 = new QLabel(tr("译文"));
    mDstLabel = new QLabel;
    mDstLabel->setWordWrap(true);

    vLayout2->addWidget(title2);
    vLayout2->addWidget(mDstLabel);
    mMainLayout->addItem(vLayout2);

    setLayout(mMainLayout);
}

TipDialog::~TipDialog()
{
}

void TipDialog::setSrcLabel(const QString & label)
{
    mSrcLabel->setText(label);
}

void TipDialog::setDstLabel(const QString & label)
{
    mDstLabel->setText(label);
}

void TipDialog::focusOutEvent(QFocusEvent * event)
{
    if (isVisible()) {
        hide();
    }
}
