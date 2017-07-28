//
// Description: Widget for configuring build targets
//
// Copyright (c) 2011-2014 Kåre Särs <kare.sars@iki.fi>
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

#ifndef TARGETS_H
#define TARGETS_H

#include <QWidget>
#include "ui_TargetsUi.h"

#include <QGridLayout>
#include <QToolButton>
#include <QTreeView>
#include <QComboBox>
#include <QLabel>
#include "TargetHtmlDelegate.h"
#include "TargetModel.h"

class TargetsUi: public QWidget, public Ui::TargetsUi
{
    Q_OBJECT

public:
    TargetsUi(QObject *view, QWidget *parent = 0);

    TargetModel  targetsModel;


public Q_SLOTS:
    void targetSetSelected(int index);
    void targetActivated(const QModelIndex &index);

Q_SIGNALS:
    void enterPressed();

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;

private:
    TargetHtmlDelegate *m_delegate;
};

#endif
