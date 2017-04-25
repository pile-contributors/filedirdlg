/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
\file         filedlgcsvaddon.h
\date         December 2015
\author       Nicu Tofan

\brief        Contains the implementation for FileDlgCsvAddon class.

*//*

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include "filedlgcsvaddon.h"
#include "../filedlg.h"

#include <QFileInfo>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QLabel>
#include <QTextCodec>
#include <QTableWidget>
#include <QLineEdit>
#include <QSplitter>
#include <QListView>
#include <QTreeView>
#include <QToolButton>
#include <QDebug>
#include <QFileSystemModel>
#include <QHeaderView>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
 * @class FileDlgCsvAddon
 *
 *
 */

/* ------------------------------------------------------------------------- */
FileDlgCsvAddon::FileDlgCsvAddon(FileDlg *parent) :
    FileDlgAddon (parent),
    vbox (NULL),
    encoding_label (NULL),
    encoding_drop (NULL),
    separator_label (NULL),
    separator_edit (NULL),
    quote_label (NULL),
    quote_edit (NULL),
    preview_label (NULL),
    tbl (NULL)
{}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void FileDlgCsvAddon::setupUI (QGridLayout *main_layout)
{

    int row_index = main_layout->rowCount ();
    int column_index = main_layout->columnCount ();
    QWidget * pwdg = main_layout->parentWidget ();

    vbox = new QHBoxLayout (pwdg);
    {
        encoding_label = new QLabel (tr("Encoding"), pwdg);
        vbox->addWidget (encoding_label);

        encoding_drop = new QComboBox (pwdg);
        QList<QByteArray> codec_list = QTextCodec::availableCodecs ();
        qSort (codec_list);
        foreach(const QByteArray & iter, codec_list) {
            encoding_drop->addItem (QString::fromLatin1 (iter));
        }
        vbox->addWidget (encoding_drop);

        separator_label = new QLabel (tr("Delimiter"), pwdg);
        vbox->addWidget (separator_label);
        separator_edit = new QLineEdit (tr(","), pwdg);
        vbox->addWidget (separator_edit);

        quote_label = new QLabel (tr("Quote"), pwdg);
        vbox->addWidget (quote_label);
        quote_edit = new QLineEdit (tr("\""), pwdg);
        vbox->addWidget (quote_edit);
    }
    main_layout->addLayout (vbox, row_index, 0, 1, 3);

    preview_label = new QLabel (tr("Preview"), pwdg);
    preview_label->setAlignment (Qt::AlignHCenter);
    main_layout->addWidget (preview_label, 0, column_index, Qt::AlignHCenter);

    tbl = new QTableWidget (pwdg);
    tbl->setAlternatingRowColors (true);
    tbl->setHorizontalScrollMode (QAbstractItemView::ScrollPerPixel);

    QHeaderView *tbl_hdr = tbl->verticalHeader ();
    tbl_hdr->setSectionResizeMode (QHeaderView::Fixed);
    tbl_hdr->setDefaultSectionSize (20);

    main_layout->addWidget (tbl, 1, column_index, row_index, 1);

    connect(encoding_drop, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateCSVPreview()));
    connect(quote_edit, SIGNAL(textChanged(QString)),
            this, SLOT(updateCSVPreview()));
    connect(separator_edit, SIGNAL(textChanged(QString)),
            this, SLOT(updateCSVPreview()));

    QTreeView * maintv = parent_dlg_->mainTree ();
    QItemSelectionModel * selm = maintv->selectionModel();
    if (selm == NULL) {
        DBG_ASSERT(false);
        return;
    }
    connect(selm, SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(updateCSVPreview()));

    updateCSVPreview ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void FileDlgCsvAddon::clearPreview ()
{
    tbl->clear ();
    tbl->setRowCount (0);
    tbl->setColumnCount (0);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QTableWidgetItem * FileDlgCsvAddon::showOneItem (const QString & s_str)
{
    QTableWidgetItem * itm = new QTableWidgetItem (s_str);
    tbl->setRowCount (1);
    tbl->setColumnCount (1);
    tbl->setItem(0, 0, itm);
    itm->setFlags (
                Qt::ItemIsSelectable | Qt::ItemIsEnabled |
                Qt::ItemNeverHasChildren);
    return itm;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QTableWidgetItem * FileDlgCsvAddon::showErrorItem (const QString & s_str)
{
    QTableWidgetItem * itm = showOneItem (s_str);
    itm->setTextColor(Qt::red);
    return itm;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void FileDlgCsvAddon::showItems (const QList<QStringList> & lsl)
{
    tbl->setRowCount (lsl.count ());
    int crt_col_cnt = 0;
    int c = 0;
    int r = 0;
    foreach (const QStringList & iter, lsl) {
        int i_max = iter.count();
        if (i_max > crt_col_cnt) {
            tbl->setColumnCount (i_max);
            crt_col_cnt = i_max;
        }

        c = 0;
        foreach (const QString & s_cell, iter) {
            QTableWidgetItem * itm = new QTableWidgetItem (s_cell);
            itm->setFlags (
                        Qt::ItemIsSelectable | Qt::ItemIsEnabled |
                        Qt::ItemNeverHasChildren);
            tbl->setItem(r, c, itm);
            c = c + 1;
        }

        r = r + 1;
    }

    for (c = 0; c < crt_col_cnt; ++c) {
        QTableWidgetItem * tvi = new QTableWidgetItem (QString::number (c+1));
        tbl->setHorizontalHeaderItem (c, tvi);
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void FileDlgCsvAddon::updateCSVPreview ()
{
    clearPreview ();

    for (;;) {
        QString s_sep = separator_edit->text ();
        if (s_sep.isEmpty()) {
            s_sep = "\"";
        }

        QString s__file = parent_dlg_->currentFile ();
        if (s__file.isEmpty()) {
            break;
        }

        QStringList sl = readSomeTextlines (
                s__file, 50, encoding_drop->currentText ());

        QList<QStringList> components;
        foreach(const QString & s_iter, sl) {
            QStringList parts = s_iter.split (s_sep);
            components.append(parts);;
        }

        showItems (components);
        break;
    }
    tbl->resizeColumnsToContents ();
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//

/* ------------------------------------------------------------------------- */
/* ========================================================================= */
