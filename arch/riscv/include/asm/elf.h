<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_ELF_H
#घोषणा _ASM_RISCV_ELF_H

#समावेश <uapi/यंत्र/elf.h>
#समावेश <यंत्र/auxvec.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/cacheinfo.h>

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_ARCH	EM_RISCV

#अगर_घोषित CONFIG_64BIT
#घोषणा ELF_CLASS	ELFCLASS64
#अन्यथा
#घोषणा ELF_CLASS	ELFCLASS32
#पूर्ण_अगर

#घोषणा ELF_DATA	ELFDATA2LSB

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */
#घोषणा elf_check_arch(x) ((x)->e_machine == EM_RISCV)

#घोषणा CORE_DUMP_USE_REGSET
#घोषणा ELF_EXEC_PAGESIZE	(PAGE_SIZE)

/*
 * This is the location that an ET_DYN program is loaded अगर exec'ed.  Typical
 * use of this is to invoke "./ld.so someprog" to test out a new version of
 * the loader.  We need to make sure that it is out of the way of the program
 * that it will "exec", and that there is sufficient room क्रम the brk.
 */
#घोषणा ELF_ET_DYN_BASE		((TASK_SIZE / 3) * 2)

/*
 * This yields a mask that user programs can use to figure out what
 * inकाष्ठाion set this CPU supports.  This could be करोne in user space,
 * but it's not easy, and we've alपढ़ोy करोne it here.
 */
#घोषणा ELF_HWCAP	(elf_hwcap)
बाह्य अचिन्हित दीर्घ elf_hwcap;

/*
 * This yields a string that ld.so will use to load implementation
 * specअगरic libraries क्रम optimization.  This is more specअगरic in
 * पूर्णांकent than poking at uname or /proc/cpuinfo.
 */
#घोषणा ELF_PLATFORM	(शून्य)

#अगर_घोषित CONFIG_MMU
#घोषणा ARCH_DLINFO						\
करो अणु								\
	NEW_AUX_ENT(AT_SYSINFO_EHDR,				\
		(elf_addr_t)current->mm->context.vdso);		\
	NEW_AUX_ENT(AT_L1I_CACHESIZE,				\
		get_cache_size(1, CACHE_TYPE_INST));		\
	NEW_AUX_ENT(AT_L1I_CACHEGEOMETRY,			\
		get_cache_geometry(1, CACHE_TYPE_INST));	\
	NEW_AUX_ENT(AT_L1D_CACHESIZE,				\
		get_cache_size(1, CACHE_TYPE_DATA));		\
	NEW_AUX_ENT(AT_L1D_CACHEGEOMETRY,			\
		get_cache_geometry(1, CACHE_TYPE_DATA));	\
	NEW_AUX_ENT(AT_L2_CACHESIZE,				\
		get_cache_size(2, CACHE_TYPE_UNIFIED));		\
	NEW_AUX_ENT(AT_L2_CACHEGEOMETRY,			\
		get_cache_geometry(2, CACHE_TYPE_UNIFIED));	\
पूर्ण जबतक (0)
#घोषणा ARCH_HAS_SETUP_ADDITIONAL_PAGES
काष्ठा linux_binprm;
बाह्य पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm,
	पूर्णांक uses_पूर्णांकerp);
#पूर्ण_अगर /* CONFIG_MMU */

#घोषणा ELF_CORE_COPY_REGS(dest, regs)			\
करो अणु							\
	*(काष्ठा user_regs_काष्ठा *)&(dest) =		\
		*(काष्ठा user_regs_काष्ठा *)regs;	\
पूर्ण जबतक (0);

#पूर्ण_अगर /* _ASM_RISCV_ELF_H */
