/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#ifndef QTEXTTABLE_P_H
#define QTEXTTABLE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/private/qtguiglobal_p.h>
#include "private/qtextobject_p.h"
#include "private/qtextdocument_p.h"

#include <vector>

QT_BEGIN_NAMESPACE

class QTextTablePrivate : public QTextFramePrivate
{
    Q_DECLARE_PUBLIC(QTextTable)
public:
    QTextTablePrivate(QTextDocument *document) : QTextFramePrivate(document), nRows(0), nCols(0), dirty(true), blockFragmentUpdates(false) {}

    static QTextTable *createTable(QTextDocumentPrivate *, int pos, int rows, int cols, const QTextTableFormat &tableFormat);
    void fragmentAdded(QChar type, uint fragment) override;
    void fragmentRemoved(QChar type, uint fragment) override;

    void update() const;

    int findCellIndex(int fragment) const;

    QVector<int> cells;
    // symmetric to cells array and maps to indecs in grid,
    // used for fast-lookup for row/column by fragment
    mutable QVector<int> cellIndices;
    mutable std::vector<int> grid;
    mutable int nRows;
    mutable int nCols;
    mutable bool dirty;
    bool blockFragmentUpdates;
};

QT_END_NAMESPACE

#endif // QTEXTTABLE_P_H
