<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: aclinux.h - OS specअगरic defines, etc. क्रम Linux
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACLINUX_H__
#घोषणा __ACLINUX_H__

#अगर_घोषित __KERNEL__

/* ACPICA बाह्यal files should not include ACPICA headers directly. */

#अगर !defined(BUILDING_ACPICA) && !defined(_LINUX_ACPI_H)
#त्रुटि "Please don't include <acpi/acpi.h> directly, include <linux/acpi.h> instead."
#पूर्ण_अगर

#पूर्ण_अगर

/* Common (in-kernel/user-space) ACPICA configuration */

#घोषणा ACPI_USE_SYSTEM_CLIBRARY
#घोषणा ACPI_USE_DO_WHILE_0
#घोषणा ACPI_IGNORE_PACKAGE_RESOLUTION_ERRORS

#अगर_घोषित __KERNEL__

#घोषणा ACPI_USE_SYSTEM_INTTYPES
#घोषणा ACPI_USE_GPE_POLLING

/* Kernel specअगरic ACPICA configuration */

#अगर_घोषित CONFIG_PCI
#घोषणा ACPI_PCI_CONFIGURED
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_REDUCED_HARDWARE_ONLY
#घोषणा ACPI_REDUCED_HARDWARE 1
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_DEBUGGER
#घोषणा ACPI_DEBUGGER
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_DEBUG
#घोषणा ACPI_MUTEX_DEBUG
#पूर्ण_अगर

#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/sched.h>
#समावेश <linux/atomic.h>
#समावेश <linux/math64.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock_types.h>
#अगर_घोषित EXPORT_ACPI_INTERFACES
#समावेश <linux/export.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_ACPI
#समावेश <यंत्र/acenv.h>
#पूर्ण_अगर

#घोषणा ACPI_INIT_FUNCTION __init

/* Use a specअगरic bugging शेष separate from ACPICA */

#अघोषित ACPI_DEBUG_DEFAULT
#घोषणा ACPI_DEBUG_DEFAULT          (ACPI_LV_INFO | ACPI_LV_REPAIR)

#अगर_अघोषित CONFIG_ACPI

/* External globals क्रम __KERNEL__, stubs is needed */

#घोषणा ACPI_GLOBAL(t,a)
#घोषणा ACPI_INIT_GLOBAL(t,a,b)

/* Generating stubs क्रम configurable ACPICA macros */

#घोषणा ACPI_NO_MEM_ALLOCATIONS

/* Generating stubs क्रम configurable ACPICA functions */

#घोषणा ACPI_NO_ERROR_MESSAGES
#अघोषित ACPI_DEBUG_OUTPUT

/* External पूर्णांकerface क्रम __KERNEL__, stub is needed */

#घोषणा ACPI_EXTERNAL_RETURN_STATUS(prototype) \
	अटल ACPI_INLINE prototype अणुवापस(AE_NOT_CONFIGURED);पूर्ण
#घोषणा ACPI_EXTERNAL_RETURN_OK(prototype) \
	अटल ACPI_INLINE prototype अणुवापस(AE_OK);पूर्ण
#घोषणा ACPI_EXTERNAL_RETURN_VOID(prototype) \
	अटल ACPI_INLINE prototype अणुवापस;पूर्ण
#घोषणा ACPI_EXTERNAL_RETURN_UINT32(prototype) \
	अटल ACPI_INLINE prototype अणुवापस(0);पूर्ण
#घोषणा ACPI_EXTERNAL_RETURN_PTR(prototype) \
	अटल ACPI_INLINE prototype अणुवापस(शून्य);पूर्ण

#पूर्ण_अगर				/* CONFIG_ACPI */

/* Host-dependent types and defines क्रम in-kernel ACPICA */

#घोषणा ACPI_MACHINE_WIDTH          BITS_PER_LONG
#घोषणा ACPI_USE_NATIVE_MATH64
#घोषणा ACPI_EXPORT_SYMBOL(symbol)  EXPORT_SYMBOL(symbol);
#घोषणा म_से_अदीर्घ                     simple_म_से_अदीर्घ

#घोषणा acpi_cache_t                        काष्ठा kmem_cache
#घोषणा acpi_spinlock                       spinlock_t *
#घोषणा acpi_raw_spinlock                   raw_spinlock_t *
#घोषणा acpi_cpu_flags                      अचिन्हित दीर्घ

/* Use native linux version of acpi_os_allocate_zeroed */

#घोषणा USE_NATIVE_ALLOCATE_ZEROED

/* Use logical addresses क्रम accessing GPE रेजिस्टरs in प्रणाली memory */

#घोषणा ACPI_GPE_USE_LOGICAL_ADDRESSES

/*
 * Overrides क्रम in-kernel ACPICA
 */
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_initialize
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_terminate
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_allocate
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_allocate_zeroed
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_मुक्त
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_acquire_object
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_get_thपढ़ो_id
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_create_lock
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_create_raw_lock
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_delete_raw_lock
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_acquire_raw_lock
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_release_raw_lock

/*
 * OSL पूर्णांकerfaces used by debugger/disassembler
 */
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_पढ़ोable
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_writable
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_initialize_debugger
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_terminate_debugger

/*
 * OSL पूर्णांकerfaces used by utilities
 */
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_redirect_output
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_get_table_by_name
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_get_table_by_index
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_get_table_by_address
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_खोलो_directory
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_get_next_filename
#घोषणा ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_बंद_directory

#घोषणा ACPI_MSG_ERROR          KERN_ERR "ACPI Error: "
#घोषणा ACPI_MSG_EXCEPTION      KERN_ERR "ACPI Exception: "
#घोषणा ACPI_MSG_WARNING        KERN_WARNING "ACPI Warning: "
#घोषणा ACPI_MSG_INFO           KERN_INFO "ACPI: "

#घोषणा ACPI_MSG_BIOS_ERROR     KERN_ERR "ACPI BIOS Error (bug): "
#घोषणा ACPI_MSG_BIOS_WARNING   KERN_WARNING "ACPI BIOS Warning (bug): "

/*
 * Linux wants to use designated initializers क्रम function poपूर्णांकer काष्ठाs.
 */
#घोषणा ACPI_STRUCT_INIT(field, value)	.field = value

#अन्यथा				/* !__KERNEL__ */

#घोषणा ACPI_USE_STANDARD_HEADERS

#अगर_घोषित ACPI_USE_STANDARD_HEADERS
#समावेश <unistd.h>
#पूर्ण_अगर

/* Define/disable kernel-specअगरic declarators */

#अगर_अघोषित __init
#घोषणा __init
#पूर्ण_अगर
#अगर_अघोषित __iomem
#घोषणा __iomem
#पूर्ण_अगर

/* Host-dependent types and defines क्रम user-space ACPICA */

#घोषणा ACPI_FLUSH_CPU_CACHE()
#घोषणा ACPI_CAST_PTHREAD_T(pthपढ़ो) ((acpi_thपढ़ो_id) (pthपढ़ो))

#अगर defined(__ia64__)    || (defined(__x86_64__) && !defined(__ILP32__)) ||\
	defined(__aarch64__) || defined(__PPC64__) ||\
	defined(__s390x__) ||\
	(defined(__riscv) && (defined(__LP64__) || defined(_LP64)))
#घोषणा ACPI_MACHINE_WIDTH          64
#घोषणा COMPILER_DEPENDENT_INT64    दीर्घ
#घोषणा COMPILER_DEPENDENT_UINT64   अचिन्हित दीर्घ
#अन्यथा
#घोषणा ACPI_MACHINE_WIDTH          32
#घोषणा COMPILER_DEPENDENT_INT64    दीर्घ दीर्घ
#घोषणा COMPILER_DEPENDENT_UINT64   अचिन्हित दीर्घ दीर्घ
#घोषणा ACPI_USE_NATIVE_DIVIDE
#घोषणा ACPI_USE_NATIVE_MATH64
#पूर्ण_अगर

#अगर_अघोषित __cdecl
#घोषणा __cdecl
#पूर्ण_अगर

#पूर्ण_अगर				/* __KERNEL__ */

#पूर्ण_अगर				/* __ACLINUX_H__ */
