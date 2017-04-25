
# enable/disable cmake debug messages related to this pile
set (FILEDIRDLG_DEBUG_MSG OFF)

# make sure support code is present; no harm
# in including it twice; the user, however, should have used
# pileInclude() from pile_support.cmake module.
include(pile_support)

# initialize this module
macro    (filedirdlgInit
          ref_cnt_use_mode)

    # When set to ON the c++ file needs to be able to find the header
    # with #include <qtcsv/reader.h> and sources need to be included
    # so that the linker finds them.
    option(HAVE_QT_CSV_LIB "Set to ON if qtcsv library is available" OFF)

    # default name
    if (NOT FILEDIRDLG_INIT_NAME)
        set(FILEDIRDLG_INIT_NAME "FileDirDlg")
    endif ()

    # compose the list of headers and sources
    set(FILEDIRDLG_HEADERS
        "filedirdlg.h"
        "filedlg.h"
        "filedlgaddon.h"
        "addons/filedlgcsvaddon.cc")
    set(FILEDIRDLG_SOURCES
        "filedirdlg.cc"
        "filedlg.cc"
        "filedlgaddon.cc"
        "addons/filedlgcsvaddon.cc")

    pileSetSources(
        "${FILEDIRDLG_INIT_NAME}"
        "${FILEDIRDLG_HEADERS}"
        "${FILEDIRDLG_SOURCES}")

    pileSetCommon(
        "${FILEDIRDLG_INIT_NAME}"
        "0;0;1;d"
        "ON"
        "${ref_cnt_use_mode}"
        ""
        "category1"
        "tag1;tag2")

endmacro ()
