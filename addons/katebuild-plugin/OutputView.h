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

#ifndef OutputView_H
#define OutputView_H

#include <QWidget>
#include "ui_OutputUi.h"

class OutputView: public QWidget, public Ui::OutputUi
{
    Q_OBJECT

public:
    enum TreeWidgetRoles {
        IsErrorRole = Qt::UserRole+1,
        IsWarningRole
    };

    OutputView(QWidget *parent = 0);

private Q_SLOTS:
    void slotDisplayMode(int mode);

private:
    enum ResultDetails {
        FullOutput,
        ParsedOutput,
        ErrorsAndWarnings,
        OnlyErrors
    };
};

#endif // OutputView_H
