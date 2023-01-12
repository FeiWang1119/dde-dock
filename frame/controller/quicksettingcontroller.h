/*
 * Copyright (C) 2022 ~ 2022 Deepin Technology Co., Ltd.
 *
 * Author:     donghualin <donghualin@uniontech.com>
 *
 * Maintainer:  donghualin <donghualin@uniontech.com>
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
#ifndef QUICKSETTINGCONTROLLER_H
#define QUICKSETTINGCONTROLLER_H

#include "abstractpluginscontroller.h"
#include "pluginsiteminterface.h"

class QuickSettingItem;
class PluginsItem;

class QuickSettingController : public AbstractPluginsController
{
    Q_OBJECT

public:
    enum class PluginAttribute {
        None = 0,               // 不在任何区域显示的插件
        Quick,                  // 快捷区域插件
        Tool,                   // 工具插件（回收站和窗管开发的另一套插件）
        System,                 // 系统插件（关机插件）
        Tray,                   // 托盘插件（U盘图标等）
        Fixed                   // 固定区域插件（显示桌面和多任务视图）
    };

public:
    static QuickSettingController *instance();
    QList<PluginsItemInterface *> pluginItems(const PluginAttribute &pluginClass) const;
    QJsonObject metaData(PluginsItemInterface *pluginItem);
    PluginsItem *pluginItemWidget(PluginsItemInterface *pluginItem);
    QList<PluginsItemInterface *> pluginInSettings();
    PluginAttribute pluginAttribute(PluginsItemInterface * const itemInter) const;
    QString itemKey(PluginsItemInterface *pluginItem) const;

Q_SIGNALS:
    void pluginInserted(PluginsItemInterface *itemInter, const PluginAttribute);
    void pluginRemoved(PluginsItemInterface *itemInter);
    void pluginUpdated(PluginsItemInterface *, const DockPart);
    void requestAppletVisible(PluginsItemInterface * itemInter, const QString &itemKey, bool visible);

protected:
    explicit QuickSettingController(QObject *parent = Q_NULLPTR);
    ~QuickSettingController() override;
    bool eventFilter(QObject *watched, QEvent *event) override;

    void startLoader();

protected:
    void itemAdded(PluginsItemInterface * const itemInter, const QString &itemKey) override;
    void itemUpdate(PluginsItemInterface * const itemInter, const QString &) override;
    void itemRemoved(PluginsItemInterface * const itemInter, const QString &) override;
    void requestSetAppletVisible(PluginsItemInterface * const itemInter, const QString &itemKey, const bool visible) override;

    void updateDockInfo(PluginsItemInterface * const itemInter, const DockPart &part) override;

private:
    QMap<PluginAttribute, QList<PluginsItemInterface *>> m_quickPlugins;
    QMap<PluginsItemInterface *, PluginsItem *> m_pluginItemWidgetMap;
};

#endif // CONTAINERPLUGINSCONTROLLER_H
