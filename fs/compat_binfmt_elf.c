<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 32-bit compatibility support क्रम ELF क्रमmat executables and core dumps.
 *
 * Copyright (C) 2007 Red Hat, Inc.  All rights reserved.
 *
 * Red Hat Author: Roland McGrath.
 *
 * This file is used in a 64-bit kernel that wants to support 32-bit ELF.
 * यंत्र/elf.h is responsible क्रम defining the compat_* and COMPAT_* macros
 * used below, with definitions appropriate क्रम 32-bit ABI compatibility.
 *
 * We use macros to नाम the ABI types and machine-dependent
 * functions used in binfmt_elf.c to compat versions.
 */

#समावेश <linux/elfcore-compat.h>
#समावेश <linux/समय.स>

#घोषणा ELF_COMPAT	1

/*
 * Rename the basic ELF layout types to refer to the 32-bit class of files.
 */
#अघोषित	ELF_CLASS
#घोषणा ELF_CLASS	ELFCLASS32

#अघोषित	elfhdr
#अघोषित	elf_phdr
#अघोषित	elf_shdr
#अघोषित	elf_note
#अघोषित	elf_addr_t
#अघोषित	ELF_GNU_PROPERTY_ALIGN
#घोषणा elfhdr		elf32_hdr
#घोषणा elf_phdr	elf32_phdr
#घोषणा elf_shdr	elf32_shdr
#घोषणा elf_note	elf32_note
#घोषणा elf_addr_t	Elf32_Addr
#घोषणा ELF_GNU_PROPERTY_ALIGN	ELF32_GNU_PROPERTY_ALIGN

/*
 * Some data types as stored in coredump.
 */
#घोषणा user_दीर्घ_t		compat_दीर्घ_t
#घोषणा user_siginfo_t		compat_siginfo_t
#घोषणा copy_siginfo_to_बाह्यal	copy_siginfo_to_बाह्यal32

/*
 * The machine-dependent core note क्रमmat types are defined in elfcore-compat.h,
 * which requires यंत्र/elf.h to define compat_elf_gregset_t et al.
 */
#घोषणा elf_prstatus	compat_elf_prstatus
#घोषणा elf_prstatus_common	compat_elf_prstatus_common
#घोषणा elf_prpsinfo	compat_elf_prpsinfo

#अघोषित ns_to_kernel_old_समयval
#घोषणा ns_to_kernel_old_समयval ns_to_old_समयval32

/*
 * To use this file, यंत्र/elf.h must define compat_elf_check_arch.
 * The other following macros can be defined अगर the compat versions
 * dअगरfer from the native ones, or omitted when they match.
 */

#अघोषित	elf_check_arch
#घोषणा	elf_check_arch	compat_elf_check_arch

#अगर_घोषित	COMPAT_ELF_PLATFORM
#अघोषित	ELF_PLATFORM
#घोषणा	ELF_PLATFORM		COMPAT_ELF_PLATFORM
#पूर्ण_अगर

#अगर_घोषित	COMPAT_ELF_HWCAP
#अघोषित	ELF_HWCAP
#घोषणा	ELF_HWCAP		COMPAT_ELF_HWCAP
#पूर्ण_अगर

#अगर_घोषित	COMPAT_ELF_HWCAP2
#अघोषित	ELF_HWCAP2
#घोषणा	ELF_HWCAP2		COMPAT_ELF_HWCAP2
#पूर्ण_अगर

#अगर_घोषित	COMPAT_ARCH_DLINFO
#अघोषित	ARCH_DLINFO
#घोषणा	ARCH_DLINFO		COMPAT_ARCH_DLINFO
#पूर्ण_अगर

#अगर_घोषित	COMPAT_ELF_ET_DYN_BASE
#अघोषित	ELF_ET_DYN_BASE
#घोषणा	ELF_ET_DYN_BASE		COMPAT_ELF_ET_DYN_BASE
#पूर्ण_अगर

#अगर_घोषित	COMPAT_ELF_PLAT_INIT
#अघोषित	ELF_PLAT_INIT
#घोषणा	ELF_PLAT_INIT		COMPAT_ELF_PLAT_INIT
#पूर्ण_अगर

#अगर_घोषित	COMPAT_SET_PERSONALITY
#अघोषित	SET_PERSONALITY
#घोषणा	SET_PERSONALITY		COMPAT_SET_PERSONALITY
#पूर्ण_अगर

#अगर_घोषित	compat_start_thपढ़ो
#घोषणा COMPAT_START_THREAD(ex, regs, new_ip, new_sp)	\
	compat_start_thपढ़ो(regs, new_ip, new_sp)
#पूर्ण_अगर

#अगर_घोषित	COMPAT_START_THREAD
#अघोषित	START_THREAD
#घोषणा START_THREAD		COMPAT_START_THREAD
#पूर्ण_अगर

#अगर_घोषित compat_arch_setup_additional_pages
#घोषणा COMPAT_ARCH_SETUP_ADDITIONAL_PAGES(bprm, ex, पूर्णांकerpreter) \
	compat_arch_setup_additional_pages(bprm, पूर्णांकerpreter)
#पूर्ण_अगर

#अगर_घोषित	COMPAT_ARCH_SETUP_ADDITIONAL_PAGES
#अघोषित	ARCH_HAS_SETUP_ADDITIONAL_PAGES
#घोषणा ARCH_HAS_SETUP_ADDITIONAL_PAGES 1
#अघोषित	ARCH_SETUP_ADDITIONAL_PAGES
#घोषणा	ARCH_SETUP_ADDITIONAL_PAGES COMPAT_ARCH_SETUP_ADDITIONAL_PAGES
#पूर्ण_अगर

#अगर_घोषित	compat_elf_पढ़ो_implies_exec
#अघोषित	elf_पढ़ो_implies_exec
#घोषणा	elf_पढ़ो_implies_exec compat_elf_पढ़ो_implies_exec
#पूर्ण_अगर

/*
 * Rename a few of the symbols that binfmt_elf.c will define.
 * These are all local so the names करोn't really matter, but it
 * might make some debugging less confusing not to duplicate them.
 */
#घोषणा elf_क्रमmat		compat_elf_क्रमmat
#घोषणा init_elf_binfmt		init_compat_elf_binfmt
#घोषणा निकास_elf_binfmt		निकास_compat_elf_binfmt

/*
 * We share all the actual code with the native (64-bit) version.
 */
#समावेश "binfmt_elf.c"
