/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
\file         filedlgaddon.cc
\date         December 2015
\author       Nicu Tofan

\brief        Contains the implementation for FileDlgAddon class.

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

#include "filedlgaddon.h"
#include "filedlg.h"

#include <QFile>
#include <QTextStream>

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
 * @class FileDlgAddon
 *
 *
 */

/* ------------------------------------------------------------------------- */
FileDlgAddon::FileDlgAddon (FileDlg *parent) :
    QObject (parent),
    parent_dlg_(parent)
{}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QStringList FileDlgAddon::readSomeTextlines (
        const QString &s_file, int lines_count, const QString &encoding)
{
    QStringList result;

    QFile file (s_file);
    if (!file.open (QIODevice::ReadOnly | QIODevice::Text)) {
        return result;
    }

    QTextStream in (&file);
    in.setCodec (encoding.toUtf8 ().constData ());

    int i_line = 0;
    while(!in.atEnd ()) {
        result << in.readLine ();
        ++i_line;
        if (i_line >= lines_count) {
            break;
        }
    }

    return result;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//

/* ------------------------------------------------------------------------- */
/* ========================================================================= */

