/*
 * Copyright (C) 2022 Uniontech Software Technology Co., Ltd.
 *
 * Author:     yanghao<yanghao@uniontech.com>
 *
 * Maintainer: zhengyouge<zhengyouge@uniontech.com>
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

#ifndef TRASHDIRITERATORPRIVATE_H
#define TRASHDIRITERATORPRIVATE_H

#include "dfmplugin_trash_global.h"
#include "dfm-base/interfaces/abstractdiriterator.h"

#include <QDirIterator>

DPTRASH_BEGIN_NAMESPACE

class TrashDirIterator;

class TrashDirIteratorPrivate
{
    friend class TrashDirIterator;

public:
    explicit TrashDirIteratorPrivate(TrashDirIterator *qq);
    ~TrashDirIteratorPrivate();

private:
    QDirIterator *iterator { nullptr };
    TrashDirIterator *q { nullptr };
};

DPTRASH_END_NAMESPACE
#endif   // TRASHDIRITERATORPRIVATE_H
