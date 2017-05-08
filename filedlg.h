/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
\file         filedlg.h
\date         December 2015
\author       Nicu Tofan

\brief        Contains the definition for FileDlg class.

*//*

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef GUARD_FILEDLG_H_INCLUDE
#define GUARD_FILEDLG_H_INCLUDE
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include <filedirdlg/filedirdlg-config.h>

#include <QFileDialog>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

QT_BEGIN_NAMESPACE
class QComboBox;
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QListView;
class QSplitter;
class QToolButton;
class QTreeView;
class QHBoxLayout;
class QTableWidget;
class QDialogButtonBox;
QT_END_NAMESPACE

class FileDlgAddon;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */


//! Dialog for adding or editing pictures of the parcel.
class FileDlg : public QFileDialog {
    Q_OBJECT

    //
    //
    //
    //
    /*  DEFINITIONS    ----------------------------------------------------- */

public:

    //! All the components of the dialog.
    struct AllComponents {
        QComboBox * file_type_combo_;
        QComboBox * look_in_combo_;
        QDialogButtonBox * button_box_;
        QLabel * file_name_label_;
        QLabel * file_type_label_;
        QLabel * look_in_label_;
        QLineEdit * file_name_edit_;
        QListView * left_list_;
        QSplitter * main_splitter_;
        QToolButton * back_button_;
        QToolButton * detail_model_button_;
        QToolButton * forward_button_;
        QToolButton * list_mode_button_;
        QToolButton * new_folder_button_;
        QToolButton * to_parent_button_;
        QTreeView * main_tree_;
    };

    /*  DEFINITIONS    ===================================================== */
    //
    //
    //
    //
    /*  DATA    ------------------------------------------------------------ */

public:

    FileDlgAddon * addon_;

    /*  DATA    ============================================================ */
    //
    //
    //
    //
    /*  FUNCTIONS    ------------------------------------------------------- */

public:

    //! Constructor.
    explicit FileDlg (
            QWidget *parent = NULL);

    QComboBox *
    fileTypeCombo () const;

    QComboBox *
    lookInCombo () const;

    QDialogButtonBox *
    buttonBox () const;

    QLabel *
    fileNameLabel () const;

    QLabel *
    fileTypeLabel () const;

    QLabel *
    lookInLabel () const;

    QLineEdit *
    fileNameEdit () const;

    QListView *
    leftList () const;

    QSplitter *
    mainSplitter () const;

    QToolButton *
    backButton () const;

    QToolButton *
    detailModeButton () const;

    QToolButton *
    forwardButton () const;

    QToolButton *
    listModeButton () const;

    QToolButton *
    newFolderButton () const;

    QToolButton *
    toParentButton () const;

    QTreeView *
    mainTree () const;

    bool
    getAllComponents (
            AllComponents & out);


    //! Useful for text files.
    bool
    insertFileEncodingAndPreview ();

    //! The path for current selection in the main treeview.
    QString
    currentFile();


    //! Useful for CSV.
    bool
    prepareForCsv ();

    //! Extra parameters that the user may change in the dialog.
    bool
    getCsvParms (
            QString &s_codec,
            QString &separator,
            QString &quote,
            bool &b_header);

    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //

}; /* class FileDlg */

/*  CLASS    =============================================================== */
//
//
//
//


#endif // GUARD_FILEDLG_H_INCLUDE
/* ------------------------------------------------------------------------- */
/* ========================================================================= */

