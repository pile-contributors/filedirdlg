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
#include <QCheckBox>
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
#include <QSettings>

#ifdef HAVE_QT_CSV_LIB
#  include <qtcsv/reader.h>
#endif // HAVE_QT_CSV_LIB

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
    header_check (NULL),
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
    QToolButton * d = parent_dlg_->detailModeButton ();
    int width_edit = 32;
    if (d != NULL) {
        width_edit = d->width ();
    }

    QSettings stgs;
    QString s_prev_encoding = stgs.value(
                "FileDlgCsvAddon/encoding_drop", "UTF-8").toString ();
    QString s_prev_separ = stgs.value(
                "FileDlgCsvAddon/separator_edit", ",").toString ();
    QString s_prev_quote = stgs.value(
                "FileDlgCsvAddon/quote_edit", "\"").toString ();
    QString b_prev_header = stgs.value(
                "FileDlgCsvAddon/header_check", true).toBool ();

    vbox = new QHBoxLayout (pwdg);
    {
        encoding_label = new QLabel (tr("Encoding"), pwdg);
        vbox->addWidget (encoding_label);

        encoding_drop = new QComboBox (pwdg);
        QList<QByteArray> codec_list = QTextCodec::availableCodecs ();
        qSort (codec_list);

        static const QLatin1String s_utf_8 ("UTF-8");
        static const QLatin1String s_utf_16 ("UTF-16");

        // commonly mislabeled as "ANSI".
        static const QLatin1String s_w_1252 ("windows-1252");
        static const QLatin1String s_w_1252_label ("English");

        static const QLatin1String s_gr ("ISO-8859-7");
        static const QLatin1String s_gr_label ("Modern Greek (ISO-8859-7)");

        static const QLatin1String s_win_1253 ("windows-1253");
        static const QLatin1String s_win_1253_label ("Greek (Windows-1253)");

        static const QLatin1String s_win_1250 ("windows-1250");
        static const QLatin1String s_win_1251 ("windows-1251");
        static const QLatin1String s_win_1254 ("windows-1254");
        static const QLatin1String s_win_1255 ("windows-1255");
        static const QLatin1String s_win_1256 ("windows-1256");
        static const QLatin1String s_win_1257 ("windows-1257");
        static const QLatin1String s_win_1258 ("windows-1258");

        bool have_utf_8 = false;
        bool have_utf_16 = false;
        bool have_gr = false;
        bool have_win_gr = false;
        bool have_w_1252 = false;
        foreach(const QByteArray & iter, codec_list) {
            QString s_label = QString::fromLatin1 (iter);
            if (s_label == s_utf_8) {
                have_utf_8 = true;
            } else if (s_label == s_utf_16) {
                have_utf_16 = true;
            } else if (s_label == s_gr) {
                have_gr = true;
            } else if (s_label == s_win_1253) {
                have_win_gr = true;
            } else if (s_label == s_w_1252) {
                have_w_1252 = true;
            } else {
                QString s_code = s_label;

                if (s_code == s_win_1250) {
                    s_label = "Central European (Windows-1250)";
                } else if (s_code == s_win_1251) {
                    s_label = "Cyrillic (Windows-1251)";
                } else  if (s_code == s_win_1254) {
                    s_label = "Turkish (Windows-1254)";
                } else  if (s_code == s_win_1255) {
                    s_label = "Hebrew (Windows-1255)";
                } else  if (s_code == s_win_1256) {
                    s_label = "Arabic (Windows-1256)";
                } else  if (s_code == s_win_1257) {
                    s_label = "Baltic (Windows-1257)";
                } else  if (s_code == s_win_1258) {
                    s_label = "Vietnamese (Windows-1258)";
                }

                encoding_drop->addItem (s_label);
                encoding_drop->setItemData (encoding_drop->count()-1, s_code);
            }
        }
        int inserters = 0;
        if (have_w_1252) {
            encoding_drop->insertItem (inserters++, s_w_1252_label);
            encoding_drop->setItemData (inserters-1, s_w_1252);
        }
        if (have_utf_8) {
            encoding_drop->insertItem (inserters++, s_utf_8);
            encoding_drop->setItemData (inserters-1, s_utf_8);
        }
        if (have_utf_16) {
            encoding_drop->insertItem (inserters++, s_utf_16);
            encoding_drop->setItemData (inserters-1, s_utf_16);
        }
        if (have_gr) {
            encoding_drop->insertItem (inserters++, s_gr_label);
            encoding_drop->setItemData (inserters-1, s_gr);
        }
        if (have_win_gr) {
            encoding_drop->insertItem (inserters++, s_win_1253_label);
            encoding_drop->setItemData (inserters-1, s_win_1253);
        }
        if (inserters != 0) {
            encoding_drop->insertSeparator (inserters);
        }

        int i_max = encoding_drop->count();
        for (int i = 0; i < i_max; ++i) {
            if ((encoding_drop->itemData(i)).toString() == s_prev_encoding) {
                encoding_drop->setCurrentText (encoding_drop->itemText (i));
                // encoding_drop->setCurrentIndex (i);
                break;
            }
        }
        encoding_drop->setSizePolicy (
                    QSizePolicy::Expanding, QSizePolicy::Preferred);

        vbox->addWidget (encoding_drop);

        separator_label = new QLabel (tr("Delimiter"), pwdg);
        vbox->addWidget (separator_label);
        separator_edit = new QLineEdit (tr(","), pwdg);
        separator_edit->setSizePolicy (
                    QSizePolicy::Fixed, QSizePolicy::Preferred);
        separator_edit->setMaximumWidth (width_edit);
        vbox->addWidget (separator_edit);

        quote_label = new QLabel (tr("Quote"), pwdg);
        vbox->addWidget (quote_label);
        quote_edit = new QLineEdit (tr("\""), pwdg);
        quote_edit->setSizePolicy (
                    QSizePolicy::Fixed, QSizePolicy::Preferred);
        quote_edit->setMaximumWidth (width_edit);
        vbox->addWidget (quote_edit);

        header_label = new QLabel (tr("Header"), pwdg);
        vbox->addWidget (header_label);
        header_check = new QCheckBox (QString(""), pwdg);
        vbox->addWidget (header_check);

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

    quote_edit->setText (s_prev_quote);
    separator_edit->setText (s_prev_separ);
    header_check->setText (b_prev_header);

    connect(encoding_drop, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateCSVPreview()));
    connect(quote_edit, SIGNAL(textChanged(QString)),
            this, SLOT(updateCSVPreview()));
    connect(separator_edit, SIGNAL(textChanged(QString)),
            this, SLOT(updateCSVPreview()));
    connect(header_check, SIGNAL(toggled(bool)),
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
bool FileDlgCsvAddon::getCsvParms (
        QString &s_codec, QString &separator, QString &quote, bool &b_header)
{
    s_codec = encoding_drop->currentData().toString ();

    separator = separator_edit->text ();
    if (separator.isEmpty()) {
        separator = ",";
    }

    quote = quote_edit->text ();
    if (quote.isEmpty()) {
        quote = "\"";
    }

    b_header = header_check->isChecked ();

    return true;
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
void FileDlgCsvAddon::showItems (
        const QList<QStringList> & lsl, const QStringList & header)
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
        QTableWidgetItem * tvi = new QTableWidgetItem (header.at (c));
        tbl->setHorizontalHeaderItem (c, tvi);
    }

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
class ImportFromCsv : public QtCSV::Reader::AbstractProcessor {
public:

    QList<QStringList> components_;
    QStringList header_;
    int crt_line_;
    bool b_header_;
    int max_elements_;

    //! The constructor.
    ImportFromCsv (bool b_header) :
        QtCSV::Reader::AbstractProcessor(),
        components_ (),
        header_ (),
        crt_line_ (0),
        b_header_ (b_header),
        max_elements_ (0)
    {}

    //! Process one line.
    bool operator() (const QStringList & elements) {
        ++crt_line_;
        if (b_header_ && (crt_line_ == 1)) {
            header_ = elements;
        } else {
            components_ << elements;
        }
        max_elements_ = qMax (max_elements_, elements.count ());
        return crt_line_ < 25;
    }

};
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void FileDlgCsvAddon::updateCSVPreview ()
{
    clearPreview ();

    for (;;) {
        QString s_codec;
        QString s_sep;
        QString s_quote;
        bool b_header;
        getCsvParms (s_codec, s_sep, s_quote, b_header);

        QString s__file = parent_dlg_->currentFile ();
        if (s__file.isEmpty()) {
            break;
        }

        QSettings stgs;
        stgs.setValue (
                    "FileDlgCsvAddon/encoding_drop", s_codec);
        stgs.setValue (
                    "FileDlgCsvAddon/separator_edit", s_sep);
        stgs.setValue (
                    "FileDlgCsvAddon/quote_edit", s_quote);
        stgs.setValue (
                    "FileDlgCsvAddon/header_check", b_header);
        stgs.sync ();

        QList<QStringList> components;
        QStringList header;
        int max_elements;

#     ifdef HAVE_QT_CSV_LIB

        ImportFromCsv proc (b_header);
        QtCSV::Reader::readToProcessor(
                    s__file, proc,
                    s_sep, s_quote,
                    QTextCodec::codecForName (s_codec.toLatin1().constData()));
        header = proc.header_;
        components = proc.components_;
        max_elements = proc.max_elements_;
#     else // HAVE_QT_CSV_LIB

        QStringList sl = readSomeTextlines (
                s__file, 50, s_codec);
        foreach(const QString & s_iter, sl) {
            QStringList parts = s_iter.split (s_sep);
            components.append(parts);
            max_elements = qMax (max_elements, parts.count());
        }

#     endif // HAVE_QT_CSV_LIB

        for (int i = header.count(); i < max_elements; ++i) {
            header << QString::number (i+1);
        }

        showItems (components, header);
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
