/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
\file         filedlgaddon.h
\date         December 2015
\author       Nicu Tofan

\brief        Contains the definition for FileDlgAddon class.

*//*

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef GUARD_FILEDLG_ADDON_H_INCLUDE
#define GUARD_FILEDLG_ADDON_H_INCLUDE
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include <filedirdlg/filedirdlg-config.h>
#include <QObject>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

QT_BEGIN_NAMESPACE
class QGridLayout;
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
QT_END_NAMESPACE

class FileDlg;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */


//! Base class for add-ons.
class FileDlgAddon : public QObject {
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

public:

    FileDlg * parent_dlg_;

    /*  DATA    ============================================================ */
    //
    //
    //
    //
    /*  FUNCTIONS    ------------------------------------------------------- */

public:

    //! Constructor.
    FileDlgAddon (
            FileDlg * parent);

    virtual ~FileDlgAddon ()
    {}

    virtual void
    setupUI (
            QGridLayout * main_layout) = 0;

public:

    static QStringList
    readSomeTextlines (
            const QString & s_file,
            int lines_count=25,
            const QString & encoding="UTF-8");

    /*  FUNCTIONS    ======================================================= */
    //
    //
    //
    //

}; /* class FileDlgAddon */

/*  CLASS    =============================================================== */
//
//
//
//


#endif // GUARD_FILEDLG_ADDON_H_INCLUDE
/* ------------------------------------------------------------------------- */
/* ========================================================================= */

