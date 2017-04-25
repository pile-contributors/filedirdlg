if (NOT FILEDIRDLG_BUILD_MODE)
    set (FILEDIRDLG_BUILD_MODE STATIC)
endif ()

include(pile_support)
pileInclude (FileDirDlg)
filedirdlgInit(${FILEDIRDLG_BUILD_MODE})
