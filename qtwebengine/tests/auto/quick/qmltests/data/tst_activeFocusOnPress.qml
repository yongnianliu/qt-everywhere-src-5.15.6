/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.5
import QtTest 1.0

Item {
    id: root
    width: 300
    height: 400
    TextInput {
        id: textInput
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        focus: true
        text: "foo"
    }

    TestWebEngineView {
        id: webEngineView
        activeFocusOnPress: false
        anchors {
            top: textInput.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        TestCase {
            id: testCase
            name: "ActiveFocusOnPress"
            when:windowShown

            function test_activeFocusOnPress() {
                textInput.forceActiveFocus()
                verify(textInput.activeFocus)
                mouseClick(root, 150, 300, Qt.LeftButton)
                verify(textInput.activeFocus)
            }
        }
    }
}
