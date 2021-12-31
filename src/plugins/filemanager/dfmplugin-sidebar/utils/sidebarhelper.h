/*
 * Copyright (C) 2021 Uniontech Software Technology Co., Ltd.
 *
 * Author:     zhangsheng<zhangsheng@uniontech.com>
 *
 * Maintainer: max-lv<lvwujun@uniontech.com>
 *             lanxuesong<lanxuesong@uniontech.com>
 *             xushitong<xushitong@uniontech.com>
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
#ifndef SIDEBARHELPER_H
#define SIDEBARHELPER_H

#include "dfmplugin_sidebar_global.h"

#include <QMap>
#include <QMutex>
#include <QWidget>

DPSIDEBAR_BEGIN_NAMESPACE

class SideBarWidget;
class SideBarItem;
class SideBarHelper
{
public:
    static SideBarWidget *findSideBarByWindowId(quint64 windowId);
    static void addSideBar(quint64 windowId, SideBarWidget *titleBar);
    static void removeSideBar(quint64 windowId);
    static quint64 windowId(QWidget *sender);
    static SideBarItem *createItem(const QString &pathKey, const QString &group);

private:
    static QMutex &mutex();
    static QMap<quint64, SideBarWidget *> kSideBarMap;
};

DPSIDEBAR_END_NAMESPACE

#endif   // SIDEBARHELPER_H
