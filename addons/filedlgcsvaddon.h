/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
\file         filedlgcsvaddon.h
\date         December 2015
\author       Nicu Tofan

\brief        Contains the definition for FileDlgCsvAddon class.

*//*

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef GUARD_FILEDLG_CSV_ADDON_H_INCLUDE
#define GUARD_FILEDLG_CSV_ADDON_H_INCLUDE
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include <filedirdlg/filedlgaddon.h>

#include <QFileDialog>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

class FileDlg;

QT_BEGIN_NAMESPACE
class QTableWidgetItem;
QT_END_NAMESPACE

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */


//! Dialog for adding or editing pictures of the parcel.
class FileDlgCsvAddon : public FileDlgAddon {
    Q_OBJECT

    //
    //
    //
    //
    /*  DEFINITIONS    ----------------------------------------------------- */

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

    FileDlgCsvAddon (
            FileDlg * parent);

    virtual void
    setupUI (
            QGridLayout * main_layout);

    QTableWidgetItem *
    showErrorItem (
            const QString &s_str);

    QTableWidgetItem *
    showOneItem (
            const QString &s_str);

    void
    showItems (
            const QList<QStringList> &lsl);

    void
    clearPreview();

public slots:

    //! Reloads the preview based on current selection and options.
    void
    updateCSVPreview ();

    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //

}; /* class FileDlgCsvAddon */

/*  CLASS    =============================================================== */
//
//
//
//


#endif // GUARD_FILEDLG_CSV_ADDON_H_INCLUDE
/* ------------------------------------------------------------------------- */
/* ========================================================================= */

