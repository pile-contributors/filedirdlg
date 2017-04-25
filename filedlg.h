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
QT_END_NAMESPACE

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


    /*  DEFINITIONS    ===================================================== */
    //
    //
    //
    //
    /*  DATA    ------------------------------------------------------------ */

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




    //! Useful for text files.
    bool
    insertFileEncodingAndPreview ();

    //! Useful for CSV.
    bool
    prepareForCsv ();

public slots:

    //! Reloads the preview based on current selection and options.
    void
    updateCSVPreview ();

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

