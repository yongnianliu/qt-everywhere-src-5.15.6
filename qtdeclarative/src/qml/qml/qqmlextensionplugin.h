/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtQml module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QQMLEXTENSIONPLUGIN_H
#define QQMLEXTENSIONPLUGIN_H

#include <QtCore/qplugin.h>
#include <QtCore/QUrl>
#include <QtQml/qqmlextensioninterface.h>

#if defined(Q_CC_GHS)
#  define GHS_PRAGMA(S) _Pragma(#S)
#  define GHS_KEEP_REFERENCE(S) GHS_PRAGMA(ghs reference S ##__Fv)
#else
#  define GHS_KEEP_REFERENCE(S)
#endif

QT_BEGIN_NAMESPACE

class QQmlEngine;
class QQmlExtensionPluginPrivate;

class Q_QML_EXPORT QQmlExtensionPlugin
    : public QObject
    , public QQmlExtensionInterface
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QQmlExtensionPlugin)
    Q_INTERFACES(QQmlExtensionInterface)
    Q_INTERFACES(QQmlTypesExtensionInterface)
public:
    explicit QQmlExtensionPlugin(QObject *parent = nullptr);
    ~QQmlExtensionPlugin() override;

    QUrl baseUrl() const;

    void registerTypes(const char *uri) override = 0;
    void initializeEngine(QQmlEngine *engine, const char *uri) override;

private:
    Q_DISABLE_COPY(QQmlExtensionPlugin)
};

class Q_QML_EXPORT QQmlEngineExtensionPlugin
        : public QObject
        , public QQmlEngineExtensionInterface
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(QQmlEngineExtensionPlugin)
    Q_INTERFACES(QQmlEngineExtensionInterface)
public:
    explicit QQmlEngineExtensionPlugin(QObject *parent = nullptr);
    ~QQmlEngineExtensionPlugin() override;
    void initializeEngine(QQmlEngine *engine, const char *uri) override;
};

QT_END_NAMESPACE

#endif // QQMLEXTENSIONPLUGIN_H
