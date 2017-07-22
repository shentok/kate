//
// Description: Widget for configuring build targets
//
// Copyright (C) 2011-2014 Kåre Särs <kare.sars@iki.fi>
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Library General Public
//  License version 2 as published by the Free Software Foundation.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Library General Public License for more details.
//
//  You should have received a copy of the GNU Library General Public License
//  along with this library; see the file COPYING.LIB.  If not, write to
//  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
//  Boston, MA 02110-1301, USA.

#include "OutputView.h"

#include <klocalizedstring.h>
#include <QIcon>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

OutputView::OutputView(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    buildAgainButton->setVisible(true);
    cancelBuildButton->setVisible(true);
    buildStatusLabel->setVisible(true);
    buildAgainButton2->setVisible(false);
    cancelBuildButton2->setVisible(false);
    buildStatusLabel2->setVisible(false);
    extraLineLayout->setAlignment(Qt::AlignRight);
    cancelBuildButton->setEnabled(false);
    cancelBuildButton2->setEnabled(false);

    plainTextEdit->setReadOnly(true);
    slotDisplayMode(FullOutput);

    connect(displayModeSlider, SIGNAL(valueChanged(int)), this, SLOT(slotDisplayMode(int)));
}

void OutputView::slotDisplayMode(int mode)
{
    errTreeWidget->setVisible(mode != 0);
    plainTextEdit->setVisible(mode == 0);

    QString modeText;
    switch(mode)
    {
        case OnlyErrors:
            modeText = i18n("Only Errors");
            break;
        case ErrorsAndWarnings:
            modeText = i18n("Errors and Warnings");
            break;
        case ParsedOutput:
            modeText = i18n("Parsed Output");
            break;
        case FullOutput:
            modeText = i18n("Full Output");
            break;
    }
    displayModeLabel->setText(modeText);

    if (mode < 1) {
        return;
    }

    const int itemCount = errTreeWidget->topLevelItemCount();

    for (int i=0;i<itemCount;i++) {
        QTreeWidgetItem* item = errTreeWidget->topLevelItem(i);

        if ( (item->data(0, IsWarningRole).toBool()==false) &&
            (item->data(0, IsErrorRole).toBool()==false) )
        {
            item->setHidden(mode > 1);
        }

        if (item->data(0, IsWarningRole).toBool()==true) {
            item->setHidden(mode > 2);
        }

        if (item->data(0, IsErrorRole).toBool()==true) {
            item->setHidden(false);
        }
    }
}
