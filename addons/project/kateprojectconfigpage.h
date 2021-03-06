/* This file is part of the KDE project

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef KATE_PROJECT_CONFIGPAGE_H
#define KATE_PROJECT_CONFIGPAGE_H

#include <ktexteditor/configpage.h>

class KateProjectPlugin;
class QWidget;
class QCheckBox;

class KateProjectConfigPage : public KTextEditor::ConfigPage
{
    Q_OBJECT
public:
    explicit KateProjectConfigPage(QWidget *parent = nullptr, KateProjectPlugin *plugin = nullptr);
    ~KateProjectConfigPage() {}

    QString name() const Q_DECL_OVERRIDE;
    QString fullName() const Q_DECL_OVERRIDE;
    QIcon icon() const Q_DECL_OVERRIDE;

public Q_SLOTS:
    void apply() Q_DECL_OVERRIDE;
    void defaults() Q_DECL_OVERRIDE;
    void reset() Q_DECL_OVERRIDE;

private Q_SLOTS:
    void slotMyChanged();

private:
    QCheckBox *m_cbAutoGit;
    QCheckBox *m_cbAutoSubversion;
    QCheckBox *m_cbAutoMercurial;
    KateProjectPlugin *m_plugin;
    bool m_changed;
};

#endif /* KATE_PROJECT_CONFIGPAGE_H */
