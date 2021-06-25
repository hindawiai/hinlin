<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acenv.h - Host and compiler configuration
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACENV_H__
#घोषणा __ACENV_H__

/*
 * Environment configuration. The purpose of this file is to पूर्णांकerface ACPICA
 * to the local environment. This includes compiler-specअगरic, OS-specअगरic,
 * and machine-specअगरic configuration.
 */

/* Types क्रम ACPI_MUTEX_TYPE */

#घोषणा ACPI_BINARY_SEMAPHORE       0
#घोषणा ACPI_OSL_MUTEX              1

/* Types क्रम DEBUGGER_THREADING */

#घोषणा DEBUGGER_SINGLE_THREADED    0
#घोषणा DEBUGGER_MULTI_THREADED     1

/******************************************************************************
 *
 * Configuration क्रम ACPI tools and utilities
 *
 *****************************************************************************/

/* Common application configuration. All single thपढ़ोed except क्रम acpi_exec. */

#अगर (defined ACPI_ASL_COMPILER) || \
	(defined ACPI_BIN_APP)      || \
	(defined ACPI_DUMP_APP)     || \
	(defined ACPI_HELP_APP)     || \
	(defined ACPI_NAMES_APP)    || \
	(defined ACPI_SRC_APP)      || \
	(defined ACPI_XTRACT_APP)   || \
	(defined ACPI_EXAMPLE_APP)  || \
	(defined ACPI_EFI_HELLO)
#घोषणा ACPI_APPLICATION
#घोषणा ACPI_SINGLE_THREADED
#घोषणा USE_NATIVE_ALLOCATE_ZEROED
#पूर्ण_अगर

/* iASL configuration */

#अगर_घोषित ACPI_ASL_COMPILER
#घोषणा ACPI_DEBUG_OUTPUT
#घोषणा ACPI_CONSTANT_EVAL_ONLY
#घोषणा ACPI_LARGE_NAMESPACE_NODE
#घोषणा ACPI_DATA_TABLE_DISASSEMBLY
#घोषणा ACPI_32BIT_PHYSICAL_ADDRESS
#घोषणा ACPI_DISASSEMBLER 1
#पूर्ण_अगर

/* acpi_exec configuration. Multithपढ़ोed with full AML debugger */

#अगर_घोषित ACPI_EXEC_APP
#घोषणा ACPI_APPLICATION
#घोषणा ACPI_FULL_DEBUG
#घोषणा ACPI_MUTEX_DEBUG
#घोषणा ACPI_DBG_TRACK_ALLOCATIONS
#पूर्ण_अगर

/* acpi_help configuration. Error messages disabled. */

#अगर_घोषित ACPI_HELP_APP
#घोषणा ACPI_NO_ERROR_MESSAGES
#पूर्ण_अगर

/* acpi_names configuration. Debug output enabled. */

#अगर_घोषित ACPI_NAMES_APP
#घोषणा ACPI_DEBUG_OUTPUT
#पूर्ण_अगर

/* acpi_exec/acpi_names/Example configuration. Native RSDP used. */

#अगर (defined ACPI_EXEC_APP)     || \
	(defined ACPI_EXAMPLE_APP)  || \
	(defined ACPI_NAMES_APP)
#घोषणा ACPI_USE_NATIVE_RSDP_POINTER
#पूर्ण_अगर

/* acpi_dump configuration. Native mapping used अगर provided by the host */

#अगर_घोषित ACPI_DUMP_APP
#घोषणा ACPI_USE_NATIVE_MEMORY_MAPPING
#पूर्ण_अगर

/* acpi_names/Example configuration. Hardware disabled */

#अगर (defined ACPI_EXAMPLE_APP)  || \
	(defined ACPI_NAMES_APP)
#घोषणा ACPI_REDUCED_HARDWARE 1
#पूर्ण_अगर

/* Linkable ACPICA library. Two versions, one with full debug. */

#अगर_घोषित ACPI_LIBRARY
#घोषणा ACPI_USE_LOCAL_CACHE
#घोषणा ACPI_DEBUGGER 1
#घोषणा ACPI_DISASSEMBLER 1

#अगर_घोषित _DEBUG
#घोषणा ACPI_DEBUG_OUTPUT
#पूर्ण_अगर
#पूर्ण_अगर

/* Common क्रम all ACPICA applications */

#अगर_घोषित ACPI_APPLICATION
#घोषणा ACPI_USE_LOCAL_CACHE
#पूर्ण_अगर

/* Common debug/disassembler support */

#अगर_घोषित ACPI_FULL_DEBUG
#घोषणा ACPI_DEBUG_OUTPUT
#घोषणा ACPI_DEBUGGER 1
#घोषणा ACPI_DISASSEMBLER 1
#पूर्ण_अगर


/*
 * acpisrc CR\LF support
 * Unix file line endings करो not include the carriage वापस.
 * If the acpisrc utility is being built using a microsoft compiler, it means
 * that it will be running on a winकरोws machine which means that the output is
 * expected to have CR/LF newlines. If the acpisrc utility is built with
 * anything अन्यथा, it will likely run on a प्रणाली with LF newlines. This flag
 * tells the acpisrc utility that newlines will be in the LF क्रमmat.
 */
#घोषणा ACPI_SRC_OS_LF_ONLY 0

/*! [Begin] no source code translation */

/******************************************************************************
 *
 * Host configuration files. The compiler configuration files are included
 * first.
 *
 *****************************************************************************/

#अगर defined(__GNUC__) && !defined(__INTEL_COMPILER)
#समावेश <acpi/platक्रमm/acgcc.h>

#या_अगर defined(_MSC_VER)
#समावेश "acmsvc.h"

#या_अगर defined(__INTEL_COMPILER)
#समावेश <acpi/platक्रमm/acपूर्णांकel.h>

#पूर्ण_अगर

#अगर defined(_LINUX) || defined(__linux__)
#समावेश <acpi/platक्रमm/aclinux.h>

#या_अगर defined(_APPLE) || defined(__APPLE__)
#समावेश "acmacosx.h"

#या_अगर defined(__DragonFly__)
#समावेश "acdragonfly.h"

#या_अगर defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#समावेश "acfreebsd.h"

#या_अगर defined(__NetBSD__)
#समावेश "acnetbsd.h"

#या_अगर defined(__sun)
#समावेश "acsolaris.h"

#या_अगर defined(MODESTO)
#समावेश "acmodesto.h"

#या_अगर defined(NETWARE)
#समावेश "acnetware.h"

#या_अगर defined(_CYGWIN)
#समावेश "accygwin.h"

#या_अगर defined(WIN32)
#समावेश "acwin.h"

#या_अगर defined(WIN64)
#समावेश "acwin64.h"

#या_अगर defined(_WRS_LIB_BUILD)
#समावेश "acvxworks.h"

#या_अगर defined(__OS2__)
#समावेश "acos2.h"

#या_अगर defined(__HAIKU__)
#समावेश "achaiku.h"

#या_अगर defined(__QNX__)
#समावेश "acqnx.h"

/*
 * EFI applications can be built with -nostdlib, in this हाल, it must be
 * included after including all other host environmental definitions, in
 * order to override the definitions.
 */
#या_अगर defined(_AED_EFI) || defined(_GNU_EFI) || defined(_EDK2_EFI)
#समावेश "acefi.h"

#अन्यथा

/* Unknown environment */

#त्रुटि Unknown target environment
#पूर्ण_अगर

/*! [End] no source code translation !*/

/******************************************************************************
 *
 * Setup शेषs क्रम the required symbols that were not defined in one of
 * the host/compiler files above.
 *
 *****************************************************************************/

/* 64-bit data types */

#अगर_अघोषित COMPILER_DEPENDENT_INT64
#घोषणा COMPILER_DEPENDENT_INT64   दीर्घ दीर्घ
#पूर्ण_अगर

#अगर_अघोषित COMPILER_DEPENDENT_UINT64
#घोषणा COMPILER_DEPENDENT_UINT64  अचिन्हित दीर्घ दीर्घ
#पूर्ण_अगर

/* Type of mutex supported by host. Default is binary semaphores. */
#अगर_अघोषित ACPI_MUTEX_TYPE
#घोषणा ACPI_MUTEX_TYPE             ACPI_BINARY_SEMAPHORE
#पूर्ण_अगर

/* Global Lock acquire/release */

#अगर_अघोषित ACPI_ACQUIRE_GLOBAL_LOCK
#घोषणा ACPI_ACQUIRE_GLOBAL_LOCK(Glptr, acquired) acquired = 1
#पूर्ण_अगर

#अगर_अघोषित ACPI_RELEASE_GLOBAL_LOCK
#घोषणा ACPI_RELEASE_GLOBAL_LOCK(Glptr, pending) pending = 0
#पूर्ण_अगर

/* Flush CPU cache - used when going to sleep. Wbinvd or similar. */

#अगर_अघोषित ACPI_FLUSH_CPU_CACHE
#घोषणा ACPI_FLUSH_CPU_CACHE()
#पूर्ण_अगर

/* "inline" keywords - configurable since अंतरभूत is not standardized */

#अगर_अघोषित ACPI_INLINE
#घोषणा ACPI_INLINE
#पूर्ण_अगर

/* Use ordered initialization अगर compiler करोesn't support designated. */
#अगर_अघोषित ACPI_STRUCT_INIT
#घोषणा ACPI_STRUCT_INIT(field, value)  value
#पूर्ण_अगर

/*
 * Configurable calling conventions:
 *
 * ACPI_SYSTEM_XFACE        - Interfaces to host OS (handlers, thपढ़ोs)
 * ACPI_EXTERNAL_XFACE      - External ACPI पूर्णांकerfaces
 * ACPI_INTERNAL_XFACE      - Internal ACPI पूर्णांकerfaces
 * ACPI_INTERNAL_VAR_XFACE  - Internal variable-parameter list पूर्णांकerfaces
 */
#अगर_अघोषित ACPI_SYSTEM_XFACE
#घोषणा ACPI_SYSTEM_XFACE
#पूर्ण_अगर

#अगर_अघोषित ACPI_EXTERNAL_XFACE
#घोषणा ACPI_EXTERNAL_XFACE
#पूर्ण_अगर

#अगर_अघोषित ACPI_INTERNAL_XFACE
#घोषणा ACPI_INTERNAL_XFACE
#पूर्ण_अगर

#अगर_अघोषित ACPI_INTERNAL_VAR_XFACE
#घोषणा ACPI_INTERNAL_VAR_XFACE
#पूर्ण_अगर

/*
 * Debugger thपढ़ोing model
 * Use single thपढ़ोed अगर the entire subप्रणाली is contained in an application
 * Use multiple thपढ़ोed when the subप्रणाली is running in the kernel.
 *
 * By शेष the model is single thपढ़ोed अगर ACPI_APPLICATION is set,
 * multi-thपढ़ोed अगर ACPI_APPLICATION is not set.
 */
#अगर_अघोषित DEBUGGER_THREADING
#अगर !defined (ACPI_APPLICATION) || defined (ACPI_EXEC_APP)
#घोषणा DEBUGGER_THREADING          DEBUGGER_MULTI_THREADED

#अन्यथा
#घोषणा DEBUGGER_THREADING          DEBUGGER_SINGLE_THREADED
#पूर्ण_अगर
#पूर्ण_अगर				/* !DEBUGGER_THREADING */

/******************************************************************************
 *
 * C library configuration
 *
 *****************************************************************************/

/*
 * ACPI_USE_SYSTEM_CLIBRARY - Define this अगर linking to an actual C library.
 *      Otherwise, local versions of string/memory functions will be used.
 * ACPI_USE_STANDARD_HEADERS - Define this अगर linking to a C library and
 *      the standard header files may be used. Defining this implies that
 *      ACPI_USE_SYSTEM_CLIBRARY has been defined.
 *
 * The ACPICA subप्रणाली only uses low level C library functions that करो not
 * call operating प्रणाली services and may thereक्रमe be अंतरभूतd in the code.
 *
 * It may be necessary to tailor these include files to the target
 * generation environment.
 */

/* Use the standard C library headers. We want to keep these to a minimum. */

#अगर_घोषित ACPI_USE_STANDARD_HEADERS

/* Use the standard headers from the standard locations */

#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <प्रकार.स>
#अगर defined (ACPI_APPLICATION) || defined(ACPI_LIBRARY)
#समावेश <मानकपन.स>
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश <समय.स>
#समावेश <संकेत.स>
#पूर्ण_अगर

#पूर्ण_अगर				/* ACPI_USE_STANDARD_HEADERS */

#अगर_घोषित ACPI_APPLICATION
#घोषणा ACPI_खाता              खाता *
#घोषणा ACPI_खाता_OUT          मानक_निकास
#घोषणा ACPI_खाता_ERR          मानक_त्रुटि
#अन्यथा
#घोषणा ACPI_खाता              व्योम *
#घोषणा ACPI_खाता_OUT          शून्य
#घोषणा ACPI_खाता_ERR          शून्य
#पूर्ण_अगर				/* ACPI_APPLICATION */

#अगर_अघोषित ACPI_INIT_FUNCTION
#घोषणा ACPI_INIT_FUNCTION
#पूर्ण_अगर

#पूर्ण_अगर				/* __ACENV_H__ */
