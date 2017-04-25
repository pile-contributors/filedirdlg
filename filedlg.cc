/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
\file         filedlg.cc
\date         December 2015
\author       Nicu Tofan

\brief        Contains the implementation for FileDlg class.

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

#include "filedlg.h"

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
 * @class FileDlg
 *
 * The caller must manually call populateTagCombo() and setNew()
 * (in this order).
 */

/* ------------------------------------------------------------------------- */
FileDlg::FileDlg (QWidget *parent) :
    QFileDialog(parent)
{
    setOption (QFileDialog::DontUseNativeDialog, true);

#ifdef AGREECE_DEBUG
    Q_ASSERT(NULL != fileTypeCombo ());
    Q_ASSERT(NULL != lookInCombo ());
    Q_ASSERT(NULL != buttonBox ());
    Q_ASSERT(NULL != fileNameLabel ());
    Q_ASSERT(NULL != fileTypeLabel ());
    Q_ASSERT(NULL != lookInLabel ());
    Q_ASSERT(NULL != fileNameEdit ());
    Q_ASSERT(NULL != leftList ());
    Q_ASSERT(NULL != mainSplitter ());
    Q_ASSERT(NULL != backButton ());
    Q_ASSERT(NULL != detailModeButton ());
    Q_ASSERT(NULL != forwardButton ());
    Q_ASSERT(NULL != listModeButton ());
    Q_ASSERT(NULL != newFolderButton ());
    Q_ASSERT(NULL != toParentButton ());
    Q_ASSERT(NULL != mainTree ());
#endif

#if 0
    prepareForCsv ();
#endif
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QTreeView * FileDlg::mainTree () const
{
    return findChildren<QTreeView*> ("treeView").at (0);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QListView * FileDlg::leftList () const
{
    return findChildren<QListView*> ("listView").at (0);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QLabel * FileDlg::lookInLabel () const
{
    return findChildren<QLabel*> ("lookInLabel").at (0);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QComboBox * FileDlg::lookInCombo () const
{
    return findChildren<QComboBox*> ("lookInCombo").at (0);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QLabel * FileDlg::fileNameLabel () const
{
    return findChildren<QLabel*> ("fileNameLabel").at (0);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QLineEdit * FileDlg::fileNameEdit () const
{
    return findChildren<QLineEdit*> ("fileNameEdit").at (0);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QLabel * FileDlg::fileTypeLabel () const
{
    return findChildren<QLabel*> ("fileTypeLabel").at (0);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QComboBox * FileDlg::fileTypeCombo () const
{
    return findChildren<QComboBox*> ("fileTypeCombo").at (0);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QDialogButtonBox * FileDlg::buttonBox () const
{
    return findChildren<QDialogButtonBox*> ("buttonBox").at (0);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QToolButton * FileDlg::backButton () const
{
    return findChildren<QToolButton*> ("backButton").at (0);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QToolButton * FileDlg::forwardButton () const
{
    return findChildren<QToolButton*> ("forwardButton").at (0);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QToolButton * FileDlg::toParentButton () const
{
    return findChildren<QToolButton*> ("toParentButton").at (0);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QToolButton * FileDlg::newFolderButton () const
{
    return findChildren<QToolButton*> ("newFolderButton").at (0);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QToolButton * FileDlg::listModeButton () const
{
    return findChildren<QToolButton*> ("listModeButton").at (0);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QToolButton * FileDlg::detailModeButton () const
{
    return findChildren<QToolButton*> ("detailModeButton").at (0);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QSplitter * FileDlg::mainSplitter () const
{
    return findChildren<QSplitter*> ("splitter").at (0);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool FileDlg::insertFileEncodingAndPreview()
{
    bool b_ret = false;
    for (;;) {

        setFileMode (QFileDialog::ExistingFile);

        QGridLayout * main_layout = qobject_cast<QGridLayout*>(layout ());
        if (main_layout == NULL) {
            DBG_ASSERT(false);
            break;
        }

        qDebug () << main_layout->objectName();
        int row_index = main_layout->rowCount ();
        int column_index = main_layout->columnCount ();

        QLabel * encoding_label = new QLabel (tr("Encoding"), this);
        main_layout->addWidget (encoding_label, row_index, 0);

        QComboBox * encoding_drop = new QComboBox (this);
        QList<QByteArray> codec_list = QTextCodec::availableCodecs ();
        qSort (codec_list);
        foreach(const QByteArray & iter, codec_list) {
            encoding_drop->addItem (QString::fromLatin1 (iter));
        }
        main_layout->addWidget (encoding_drop, row_index, 1, 1, 2);


        QLabel * preview_label = new QLabel (tr("Preview"), this);
        main_layout->addWidget (preview_label, 0, column_index);

        QPlainTextEdit * plaintx = new QPlainTextEdit (this);
        main_layout->addWidget (plaintx, 1, column_index, row_index, 1);


        b_ret = true;
        break;
    }
    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
class FileDlgAddon : public QObject {
public:

    FileDlgAddon (QObject * parent) :
        QObject (parent)
    {}

    virtual ~FileDlgAddon ()
    {}

    virtual void
    setupUI (
            QGridLayout * main_layout) = 0;

};
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
class FileDlgCsvAddon : public FileDlgAddon {
public:
    QHBoxLayout * vbox;
    QLabel * encoding_label;
    QComboBox * encoding_drop;
    QLabel * separator_label;
    QLineEdit * separator_edit;
    QLabel * quote_label;
    QLineEdit * quote_edit;
    QLabel * preview_label;
    QTableWidget * tbl;

    FileDlgCsvAddon (QObject * parent) :
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

    virtual void
    setupUI (
            QGridLayout * main_layout)
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
        main_layout->addWidget (tbl, 1, column_index, row_index, 1);
    }

};
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool FileDlg::prepareForCsv ()
{
    bool b_ret = false;
    for (;;) {

        setFileMode (QFileDialog::ExistingFile);

        QGridLayout * main_layout = qobject_cast<QGridLayout*>(layout ());
        if (main_layout == NULL) {
            DBG_ASSERT(false);
            break;
        }

        FileDlgCsvAddon * add_on = new FileDlgCsvAddon (this);
        add_on->setupUI (main_layout);


        b_ret = true;
        break;
    }
    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void FileDlg::updateCSVPreview ()
{

}
/* ========================================================================= */


/*  CLASS    =============================================================== */
//
//
//
//

/* ------------------------------------------------------------------------- */
/* ========================================================================= */
