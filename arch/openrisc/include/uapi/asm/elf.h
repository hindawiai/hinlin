<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
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
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#अगर_अघोषित _UAPI__ASM_OPENRISC_ELF_H
#घोषणा _UAPI__ASM_OPENRISC_ELF_H

/*
 * This files is partially exported to userspace.  This allows us to keep
 * the ELF bits in one place which should assist in keeping the kernel and
 * userspace in sync.
 */

/*
 * ELF रेजिस्टर definitions..
 */

/* क्रम काष्ठा user_regs_काष्ठा definition */
#समावेश <यंत्र/ptrace.h>

/* The OR1K relocation types... not all relevant क्रम module loader */
#घोषणा R_OR32_NONE	0
#घोषणा R_OR32_32	1
#घोषणा R_OR32_16	2
#घोषणा R_OR32_8	3
#घोषणा R_OR32_CONST	4
#घोषणा R_OR32_CONSTH	5
#घोषणा R_OR32_JUMPTARG	6
#घोषणा R_OR32_VTINHERIT 7
#घोषणा R_OR32_VTENTRY	8

प्रकार अचिन्हित दीर्घ elf_greg_t;

/*
 * Note that NGREG is defined to ELF_NGREG in include/linux/elfcore.h, and is
 * thus exposed to user-space.
 */
#घोषणा ELF_NGREG (माप(काष्ठा user_regs_काष्ठा) / माप(elf_greg_t))
प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];

/* A placeholder; OR32 करोes not have fp support yes, so no fp regs क्रम now.  */
प्रकार अचिन्हित दीर्घ elf_fpregset_t;

/* EM_OPENRISC is defined in linux/elf-em.h */
#घोषणा EM_OR32         0x8472

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_ARCH	EM_OR32
#घोषणा ELF_CLASS	ELFCLASS32
#घोषणा ELF_DATA	ELFDATA2MSB

#पूर्ण_अगर /* _UAPI__ASM_OPENRISC_ELF_H */
