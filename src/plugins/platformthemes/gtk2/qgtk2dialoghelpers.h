/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QGTK2DIALOGHELPERS_P_H
#define QGTK2DIALOGHELPERS_P_H

#include <QtCore/qscopedpointer.h>
#include <qpa/qplatformdialoghelper.h>

typedef struct _GtkDialog GtkDialog;
typedef struct _GtkFileFilter GtkFileFilter;

QT_BEGIN_NAMESPACE

class QGtk2Dialog;

class QGtk2ColorDialogHelper : public QPlatformColorDialogHelper
{
    Q_OBJECT

public:
    QGtk2ColorDialogHelper();
    ~QGtk2ColorDialogHelper();

    virtual bool show(Qt::WindowFlags flags, Qt::WindowModality modality, QWindow *parent);
    virtual void exec();
    virtual void hide();

    virtual void setCurrentColor(const QColor &color);
    virtual QColor currentColor() const;

private Q_SLOTS:
    void onAccepted();

private:
    static void onColorChanged(QGtk2ColorDialogHelper *helper);
    void applyOptions();

    mutable QScopedPointer<QGtk2Dialog> d;
};

class QGtk2FileDialogHelper : public QPlatformFileDialogHelper
{
    Q_OBJECT

public:
    QGtk2FileDialogHelper();
    ~QGtk2FileDialogHelper();

    virtual bool show(Qt::WindowFlags flags, Qt::WindowModality modality, QWindow *parent);
    virtual void exec();
    virtual void hide();

    virtual bool defaultNameFilterDisables() const;
    virtual void setDirectory(const QString &directory);
    virtual QString directory() const;
    virtual void selectFile(const QString &filename);
    virtual QStringList selectedFiles() const;
    virtual void setFilter();
    virtual void selectNameFilter(const QString &filter);
    virtual QString selectedNameFilter() const;

private Q_SLOTS:
    void onAccepted();

private:
    static void onSelectionChanged(GtkDialog *dialog, QGtk2FileDialogHelper *helper);
    static void onCurrentFolderChanged(QGtk2FileDialogHelper *helper);
    void applyOptions();
    void setNameFilters(const QStringList &filters);

    QString _dir;
    QStringList _selection;
    QHash<QString, GtkFileFilter*> _filters;
    QHash<GtkFileFilter*, QString> _filterNames;
    mutable QScopedPointer<QGtk2Dialog> d;
};

class QGtk2FontDialogHelper : public QPlatformFontDialogHelper
{
    Q_OBJECT

public:
    QGtk2FontDialogHelper();
    ~QGtk2FontDialogHelper();

    virtual bool show(Qt::WindowFlags flags, Qt::WindowModality modality, QWindow *parent);
    virtual void exec();
    virtual void hide();

    virtual void setCurrentFont(const QFont &font);
    virtual QFont currentFont() const;

private Q_SLOTS:
    void onAccepted();

private:
    void applyOptions();

    mutable QScopedPointer<QGtk2Dialog> d;
};

QT_END_NAMESPACE

#endif // QGTK2DIALOGHELPERS_P_H