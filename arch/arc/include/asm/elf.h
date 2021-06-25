<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ASM_ARC_ELF_H
#घोषणा __ASM_ARC_ELF_H

#समावेश <linux/types.h>
#समावेश <linux/elf-em.h>
#समावेश <uapi/यंत्र/elf.h>

#घोषणा EM_ARC_INUSE		(IS_ENABLED(CONFIG_ISA_ARCOMPACT) ? \
					EM_ARCOMPACT : EM_ARCV2)

/* ARC Relocations (kernel Modules only) */
#घोषणा  R_ARC_32		0x4
#घोषणा  R_ARC_32_ME		0x1B
#घोषणा  R_ARC_32_PCREL		0x31

/*to set parameters in the core dumps */
#घोषणा ELF_ARCH		EM_ARC_INUSE
#घोषणा ELF_CLASS		ELFCLASS32

#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
#घोषणा ELF_DATA		ELFDATA2MSB
#अन्यथा
#घोषणा ELF_DATA		ELFDATA2LSB
#पूर्ण_अगर

/*
 * To ensure that
 *  -we करोn't load something क्रम the wrong architecture.
 *  -The userspace is using the correct syscall ABI
 */
काष्ठा elf32_hdr;
बाह्य पूर्णांक elf_check_arch(स्थिर काष्ठा elf32_hdr *);
#घोषणा elf_check_arch	elf_check_arch

#घोषणा CORE_DUMP_USE_REGSET

#घोषणा ELF_EXEC_PAGESIZE	PAGE_SIZE

/*
 * This is the location that an ET_DYN program is loaded अगर exec'ed.  Typical
 * use of this is to invoke "./ld.so someprog" to test out a new version of
 * the loader.  We need to make sure that it is out of the way of the program
 * that it will "exec", and that there is sufficient room क्रम the brk.
 */
#घोषणा ELF_ET_DYN_BASE		(2UL * TASK_SIZE / 3)

/*
 * When the program starts, a1 contains a poपूर्णांकer to a function to be
 * रेजिस्टरed with निकास_पर, as per the SVR4 ABI.  A value of 0 means we
 * have no such handler.
 */
#घोषणा ELF_PLAT_INIT(_r, load_addr)	((_r)->r0 = 0)

/*
 * This yields a mask that user programs can use to figure out what
 * inकाष्ठाion set this cpu supports.
 */
#घोषणा ELF_HWCAP	(0)

/*
 * This yields a string that ld.so will use to load implementation
 * specअगरic libraries क्रम optimization.  This is more specअगरic in
 * पूर्णांकent than poking at uname or /proc/cpuinfo.
 */
#घोषणा ELF_PLATFORM	(शून्य)

#पूर्ण_अगर
