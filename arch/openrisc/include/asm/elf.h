<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */
#अगर_अघोषित __ASM_OPENRISC_ELF_H
#घोषणा __ASM_OPENRISC_ELF_H


#समावेश <linux/types.h>
#समावेश <uapi/यंत्र/elf.h>

/*
 * This is used to ensure we करोn't load something क्रम the wrong architecture.
 */

#घोषणा elf_check_arch(x) \
	(((x)->e_machine == EM_OR32) || ((x)->e_machine == EM_OPENRISC))

/* This is the location that an ET_DYN program is loaded अगर exec'ed.  Typical
   use of this is to invoke "./ld.so someprog" to test out a new version of
   the loader.  We need to make sure that it is out of the way of the program
   that it will "exec", and that there is sufficient room क्रम the brk.  */

#घोषणा ELF_ET_DYN_BASE         (0x08000000)

/*
 * Enable dump using regset.
 * This covers all of general/DSP/FPU regs.
 */
#घोषणा CORE_DUMP_USE_REGSET

#घोषणा ELF_EXEC_PAGESIZE	8192

बाह्य व्योम dump_elf_thपढ़ो(elf_greg_t *dest, काष्ठा pt_regs *pt);
#घोषणा ELF_CORE_COPY_REGS(dest, regs) dump_elf_thपढ़ो(dest, regs);

/* This yields a mask that user programs can use to figure out what
   inकाष्ठाion set this cpu supports.  This could be करोne in userspace,
   but it's not easy, and we've alपढ़ोy करोne it here.  */

#घोषणा ELF_HWCAP	(0)

/* This yields a string that ld.so will use to load implementation
   specअगरic libraries क्रम optimization.  This is more specअगरic in
   पूर्णांकent than poking at uname or /proc/cpuinfo.

   For the moment, we have only optimizations क्रम the Intel generations,
   but that could change... */

#घोषणा ELF_PLATFORM	(शून्य)

#पूर्ण_अगर
