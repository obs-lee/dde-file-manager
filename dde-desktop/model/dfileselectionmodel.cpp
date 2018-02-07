/*
 * Copyright (C) 2016 ~ 2018 Deepin Technology Co., Ltd.
 *               2016 ~ 2018 dragondjf
 *
 * Author:     dragondjf<dingjiangfeng@deepin.com>
 *
 * Maintainer: dragondjf<dingjiangfeng@deepin.com>
 *             zccrs<zhangjide@deepin.com>
 *             Tangtong<tangtong@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "dfileselectionmodel.h"

DFileSelectionModel::DFileSelectionModel(QAbstractItemModel *model)
    : QItemSelectionModel(model)
{
    m_timer.setSingleShot(true);

    connect(&m_timer, &QTimer::timeout, this, &DFileSelectionModel::updateSelecteds);
}

DFileSelectionModel::DFileSelectionModel(QAbstractItemModel *model, QObject *parent)
    : QItemSelectionModel(model, parent)
{
    m_timer.setSingleShot(true);

    connect(&m_timer, &QTimer::timeout, this, &DFileSelectionModel::updateSelecteds);
}

bool DFileSelectionModel::isSelected(const QModelIndex &index) const
{
    if (m_currentCommand != QItemSelectionModel::SelectionFlags(Current|Rows|ClearAndSelect))
        return QItemSelectionModel::isSelected(index);

    for (const QItemSelectionRange &range : m_selection) {
        if (range.contains(index))
            return true;
    }

    return false;
}

int DFileSelectionModel::selectedCount() const
{
    if (m_currentCommand != QItemSelectionModel::SelectionFlags(Current|Rows|ClearAndSelect))
        return selectedIndexes().count();

    return m_lastSelectedIndex.row() - m_firstSelectedIndex.row() + 1;
}

QModelIndexList DFileSelectionModel::selectedIndexes() const
{
    if (m_selectedList.isEmpty()) {
        if (m_currentCommand != QItemSelectionModel::SelectionFlags(Current|Rows|ClearAndSelect)) {
            m_selectedList = QItemSelectionModel::selectedIndexes();
        } else {
            for (const QItemSelectionRange &range : m_selection) {
                m_selectedList << range.indexes();
            }
        }
    }

    return m_selectedList;
}

void DFileSelectionModel::select(const QItemSelection &selection, QItemSelectionModel::SelectionFlags command)
{
    if (!command.testFlag(NoUpdate))
        m_selectedList.clear();

    if (command != QItemSelectionModel::SelectionFlags(Current|Rows|ClearAndSelect)) {
        if (m_timer.isActive()) {
            m_timer.stop();
            updateSelecteds();
        }

        m_currentCommand = command;

        QItemSelectionModel::select(selection, command);

        return;
    }


    if (selection.isEmpty()) {
        m_firstSelectedIndex = QModelIndex();
        m_lastSelectedIndex = QModelIndex();
    } else {
        m_firstSelectedIndex = selection.first().topLeft();
        m_lastSelectedIndex = selection.last().bottomRight();
    }

    QItemSelection newSelection(m_firstSelectedIndex, m_lastSelectedIndex);

    emitSelectionChanged(newSelection, m_selection);

    m_currentCommand = command;
    m_selection = newSelection;

    m_timer.start(20);
}

void DFileSelectionModel::updateSelecteds()
{
    QItemSelectionModel::select(m_selection, m_currentCommand);
}
