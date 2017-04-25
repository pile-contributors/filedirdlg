/**
 * @file filedirdlg.cc
 * @brief Definitions for FileDirDlg class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "filedirdlg.h"
#include "filedirdlg-private.h"

/**
 * @class FileDirDlg
 *
 * Detailed description.
 */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for constructor.
 */
FileDirDlg::FileDirDlg()
{
    FILEDIRDLG_TRACE_ENTRY;

    FILEDIRDLG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for destructor.
 */
FileDirDlg::~FileDirDlg()
{
    FILEDIRDLG_TRACE_ENTRY;

    FILEDIRDLG_TRACE_EXIT;
}
/* ========================================================================= */

#if 0
// was used to explore the content of the dialog

/* ------------------------------------------------------------------------- */
static void iterateSplitter (QSplitter * spl, int level)
{
    int i_max = spl->count ();
    QString padding;
    for (int i = 1; i < level; ++i) {
        padding.append (" ");
    }
    qDebug () << padding
              << "------------- splitter at level "
              << level
              << "with"
              << i_max
              << "items ------------- ";

    for (int i = 0; i < i_max; ++i) {
        QWidget *widget = spl->widget (i);
        if (widget != NULL) {
            qDebug () << padding
                      << "Level: " << level
                      << "Index: " << i
                      << " " << widget->objectName ();
        }
    }
    qDebug () << padding
              << "^^^^^^^ splitter at level "
              << level
              << " ^^^^^^^ ";
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static void iterateLayout (QGridLayout * main_layout, int level = 1)
{
    int row_index = main_layout->rowCount ();
    int column_index = main_layout->columnCount ();

    QString padding;
    for (int i = 1; i < level; ++i) {
        padding.append (" ");
    }
    qDebug () << padding
              << "------------- grid layout at level "
              << level
              << " with "
              << row_index << " rows and "
              << column_index
              << " columns ------------- ";

    for (int r = 0; r < row_index; ++r) {
        for (int c = 0; c < column_index; ++c) {
            QLayoutItem * li = main_layout->itemAtPosition (r, c);
            if (!li->isEmpty ()) {
                QLayout *lay = li->layout();
                QWidget *widget = li->widget();
                QSplitter * spl = qobject_cast<QSplitter*>(widget);
                if (spl != NULL) {
                    iterateSplitter (spl, level+1);
                } else if (lay != NULL) {
                    qDebug () << padding
                              << "Level: " << level
                              << "R: " << r
                              << "C: " << c
                              << " sub-layout";
                    QGridLayout * grinner = qobject_cast<QGridLayout *>(lay);
                    if (grinner == NULL) {
                        iterateLayout (lay, level+1);
                    } else {
                        iterateLayout (grinner, level+1);
                    }
                } else if (widget != NULL) {
                    qDebug () << padding
                              << "Level: " << level
                              << "R: " << r
                              << "C: " << c
                              << " " << widget->objectName();
                }
            }
        }
    }
    qDebug () << padding
              << "^^^^^^^ grid layout at level "
              << level
              << " ^^^^^^^ ";
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static void iterateLayout (QLayout * in_lay, int level)
{
    int i_max = in_lay->count ();
    QString padding;
    for (int i = 1; i < level; ++i) {
        padding.append (" ");
    }
    qDebug () << padding
              << "------------- layout at level "
              << level
              << "with"
              << i_max
              << "items ------------- ";

    for (int i = 0; i < i_max; ++i) {
        QLayoutItem * li = in_lay->itemAt (i);
        if (!li->isEmpty ()) {
            QLayout *lay = li->layout();
            QWidget *widget = li->widget();
            QSplitter * spl = qobject_cast<QSplitter*>(widget);
            if (spl != NULL) {
                iterateSplitter (spl, level+1);
            } else if (lay != NULL) {
                QGridLayout * grinner = qobject_cast<QGridLayout *>(lay);
                if (grinner == NULL) {
                    iterateLayout (lay, level+1);
                } else {
                    iterateLayout (grinner, level+1);
                }
            } else if (widget != NULL) {
                qDebug () << padding
                          << "Level: " << level
                          << "Index: " << i
                          << " " << widget->objectName ();
            }
        }
    }
    qDebug () << padding
              << "^^^^^^^ layout at level "
              << level
              << " ^^^^^^^ ";
}
/* ========================================================================= */
#endif
