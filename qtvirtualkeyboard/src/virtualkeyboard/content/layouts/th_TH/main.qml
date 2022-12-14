/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
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
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.VirtualKeyboard 2.3

KeyboardLayoutLoader {
    inputMode: InputEngine.InputMode.Latin
    function createInputMethod() {
        return Qt.createQmlObject('import QtQuick 2.0; import QtQuick.VirtualKeyboard.Plugins 2.3; ThaiInputMethod {}', parent, "thaiInputMethod")
    }
    sharedLayouts: [ "symbols" ]
    sourceComponent: InputContext.shiftActive ? page2 : page1
    Component {
        id: page1
        KeyboardLayout {
            keyWeight: 160
            KeyboardRow {
                Layout.preferredHeight: 3
                smallTextVisible: true
                KeyboardColumn {
                    Layout.preferredWidth: bottomRow.width - hideKeyboardKey.width
                    KeyboardRow {
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "\u0E38"
                            displayText: " \u0E38"
                            alternativeKeys: [ "\u0E38", " \u0E39" ]
                        }
                        Key {
                            text: "\u0E36"
                            displayText: " \u0E36"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                    }
                    KeyboardRow {
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: " ???"
                            alternativeKeys: " ??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "\u0E31"
                            displayText: " \u0E31"
                            alternativeKeys: "\u0E31???"
                        }
                        Key {
                            text: "\u0E35"
                            displayText: " \u0E35"
                            alternativeKeys: [ "\u0E35", " \u0E4A" ]
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                        }
                    }
                    KeyboardRow {
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "\u0E49"
                            displayText: " \u0E49"
                            alternativeKeys: [ "\u0E49", " \u0E47" ]
                        }
                        Key {
                            text: "\u0E48"
                            displayText: " \u0E48"
                            alternativeKeys: [ "\u0E48", " \u0E4B" ]
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                        }
                    }
                    KeyboardRow {
                        FillerKey {
                            weight: 80
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "\u0E34"
                            displayText: " \u0E34"
                            alternativeKeys: [ "\u0E34", " \u0E3A" ]
                        }
                        Key {
                            text: "\u0E37"
                            displayText: " \u0E37"
                            alternativeKeys: [ "\u0E37", " \u0E4C" ]
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        Key {
                            text: "???"
                            alternativeKeys: "??????"
                        }
                        FillerKey {
                            weight: 80
                        }
                    }
                }
                KeyboardColumn {
                    Layout.preferredWidth: hideKeyboardKey.width
                    KeyboardRow {
                        BackspaceKey {}
                    }
                    KeyboardRow {
                        EnterKey {}
                    }
                    KeyboardRow {
                        ShiftKey { }
                    }
                }
            }
            KeyboardRow {
                id: bottomRow
                keyWeight: 154
                SymbolModeKey {
                    weight: 217
                }
                ChangeLanguageKey {
                    weight: 154
                }
                HandwritingModeKey {
                    weight: 154
                }
                SpaceKey {
                    weight: 864
                }
                Key {
                    key: Qt.Key_Period
                    text: "."
                    alternativeKeys: "!?.,"
                    smallTextVisible: true
                }
                Key {
                    key: 0xE000
                    text: ":-)"
                    alternativeKeys: [ ";-)", ":-)", ":-D", ":-(", "<3" ]
                }
                HideKeyboardKey {
                    id: hideKeyboardKey
                    weight: 204
                }
            }
        }
    }
    Component {
        id: page2
        KeyboardLayout {
            keyWeight: 160
            KeyboardRow {
                Layout.preferredHeight: 3
                smallTextVisible: true
                KeyboardColumn {
                    Layout.preferredWidth: bottomRow.width - hideKeyboardKey.width
                    KeyboardRow {
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "\u0E39"
                            displayText: " \u0E39"
                        }
                        Key {
                            enabled: false
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                    }
                    KeyboardRow {
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "\u0E4A"
                            displayText: " \u0E4A"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            enabled: false
                        }
                    }
                    KeyboardRow {
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "\u0E47"
                            displayText: " \u0E47"
                        }
                        Key {
                            text: "\u0E4B"
                            displayText: " \u0E4B"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            enabled: false
                        }
                    }
                    KeyboardRow {
                        FillerKey {
                            weight: 80
                        }
                        Key {
                            enabled: false
                        }
                        Key {
                            enabled: false
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "\u0E3A"
                            displayText: " \u0E3A"
                        }
                        Key {
                            text: "\u0E4C"
                            displayText: " \u0E4C"
                        }
                        Key {
                            enabled: false
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        Key {
                            text: "???"
                        }
                        FillerKey {
                            weight: 80
                        }
                    }
                }
                KeyboardColumn {
                    Layout.preferredWidth: hideKeyboardKey.width
                    KeyboardRow {
                        BackspaceKey {}
                    }
                    KeyboardRow {
                        EnterKey {}
                    }
                    KeyboardRow {
                        ShiftKey { }
                    }
                }
            }
            KeyboardRow {
                id: bottomRow
                keyWeight: 154
                SymbolModeKey {
                    weight: 217
                }
                ChangeLanguageKey {
                    weight: 154
                }
                HandwritingModeKey {
                    weight: 154
                }
                SpaceKey {
                    weight: 864
                }
                Key {
                    key: Qt.Key_Comma
                    text: ","
                    alternativeKeys: "!?,"
                }
                Key {
                    key: 0xE000
                    text: ":-)"
                    alternativeKeys: [ ";-)", ":-)", ":-D", ":-(", "<3" ]
                }
                HideKeyboardKey {
                    id: hideKeyboardKey
                    weight: 204
                }
            }
        }
    }
}
