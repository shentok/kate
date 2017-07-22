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

#include "targets.h"
#include <klocalizedstring.h>
#include <QIcon>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

TargetsUi::TargetsUi(QObject *view, QWidget *parent):
QWidget(parent)
{
    setupUi(this);
    targetCombo->setModel(&targetsModel);

    targetsView->setModel(&targetsModel);
    m_delegate = new TargetHtmlDelegate(view);
    targetsView->setItemDelegate(m_delegate);
    targetsView->setSelectionBehavior(QAbstractItemView::SelectItems);
    targetsView->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);

    connect(targetCombo, SIGNAL(activated(int)), this, SLOT(targetSetSelected(int)));
    connect(targetsView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(targetActivated(QModelIndex)));
    //connect(targetsView, SIGNAL(clicked(QModelIndex)), this, SLOT(targetActivated(QModelIndex)));

    targetsView->installEventFilter(this);
}

void TargetsUi::targetSetSelected(int index)
{
    //qDebug() << index;
    targetsView->collapseAll();
    QModelIndex rootItem = targetsModel.index(index, 0);

    targetsView->setExpanded(rootItem, true);
    targetsView->setCurrentIndex(rootItem.child(0,0));
}

void TargetsUi::targetActivated(const QModelIndex &index)
{
    //qDebug() << index;
    if (!index.isValid()) return;
    QModelIndex rootItem = index;
    if (rootItem.parent().isValid()) {
        rootItem = rootItem.parent();
    }

    targetCombo->setCurrentIndex(rootItem.row());
}

bool TargetsUi::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent *keyEvent=static_cast<QKeyEvent*>(event);
        if (obj==targetsView) {
            if (((keyEvent->key()==Qt::Key_Return)
                || (keyEvent->key()==Qt::Key_Enter)) && m_delegate && !m_delegate->isEditing())
            {
                emit enterPressed();
                return true;
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}
