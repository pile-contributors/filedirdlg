/**
 * @file filedirdlg-private.h
 * @brief Declarations for FileDirDlg class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_FILEDIRDLG_PRIVATE_H_INCLUDE
#define GUARD_FILEDIRDLG_PRIVATE_H_INCLUDE

#include <filedirdlg/filedirdlg-config.h>

#if 0
#    define FILEDIRDLG_DEBUGM printf
#else
#    define FILEDIRDLG_DEBUGM black_hole
#endif

#if 0
#    define FILEDIRDLG_TRACE_ENTRY printf("FILEDIRDLG ENTRY %s in %s[%d]\n", __func__, __FILE__, __LINE__)
#else
#    define FILEDIRDLG_TRACE_ENTRY
#endif

#if 0
#    define FILEDIRDLG_TRACE_EXIT printf("FILEDIRDLG EXIT %s in %s[%d]\n", __func__, __FILE__, __LINE__)
#else
#    define FILEDIRDLG_TRACE_EXIT
#endif


static inline void black_hole (...)
{}

#endif // GUARD_FILEDIRDLG_PRIVATE_H_INCLUDE
