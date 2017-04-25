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
#include "addons/filedlgcsvaddon.h"

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
    QFileDialog (parent),
    addon_ (NULL)
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
bool FileDlg::getAllComponents (FileDlg::AllComponents &out)
{
    out.file_type_combo_ = fileTypeCombo ();
    out.look_in_combo_ = lookInCombo ();
    out.button_box_ = buttonBox ();
    out.file_name_label_ = fileNameLabel ();
    out.file_type_label_ = fileTypeLabel ();
    out.look_in_label_ = lookInLabel ();
    out.file_name_edit_ = fileNameEdit ();
    out.left_list_ = leftList ();
    out.main_splitter_ = mainSplitter ();
    out.back_button_ = backButton ();
    out.detail_model_button_ = detailModeButton ();
    out.forward_button_ = forwardButton ();
    out.list_mode_button_ = listModeButton ();
    out.new_folder_button_ = newFolderButton ();
    out.to_parent_button_ = toParentButton ();
    out.main_tree_ = mainTree ();

    return true;
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
QString FileDlg::currentFile ()
{
    QString s_result;

    for (;;) {
        QTreeView * maintv = mainTree ();
        QItemSelectionModel * selm = maintv->selectionModel ();
        if (selm == NULL) {
            DBG_ASSERT(false);
            break;
        }

        QModelIndex mi = selm->currentIndex ();
        if (!mi.isValid()) {
            break;
        }

        QFileSystemModel* fsm =
                qobject_cast<QFileSystemModel*>(maintv->model ());
        if (fsm == NULL) {
            break;
        }

        s_result = fsm->filePath (mi);
        break;
    }
    return s_result;
}
/* ========================================================================= */


/*  CLASS    =============================================================== */
//
//
//
//

/* ------------------------------------------------------------------------- */
/* ========================================================================= */
