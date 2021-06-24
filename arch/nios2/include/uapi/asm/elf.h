<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Copyright (C) 2011 Tobias Klauser <tklauser@distanz.ch>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#अगर_अघोषित _UAPI_ASM_NIOS2_ELF_H
#घोषणा _UAPI_ASM_NIOS2_ELF_H

#समावेश <linux/ptrace.h>

/* Relocation types */
#घोषणा R_NIOS2_NONE		0
#घोषणा R_NIOS2_S16		1
#घोषणा R_NIOS2_U16		2
#घोषणा R_NIOS2_PCREL16		3
#घोषणा R_NIOS2_CALL26		4
#घोषणा R_NIOS2_IMM5		5
#घोषणा R_NIOS2_CACHE_OPX	6
#घोषणा R_NIOS2_IMM6		7
#घोषणा R_NIOS2_IMM8		8
#घोषणा R_NIOS2_HI16		9
#घोषणा R_NIOS2_LO16		10
#घोषणा R_NIOS2_HIADJ16		11
#घोषणा R_NIOS2_BFD_RELOC_32	12
#घोषणा R_NIOS2_BFD_RELOC_16	13
#घोषणा R_NIOS2_BFD_RELOC_8	14
#घोषणा R_NIOS2_GPREL		15
#घोषणा R_NIOS2_GNU_VTINHERIT	16
#घोषणा R_NIOS2_GNU_VTENTRY	17
#घोषणा R_NIOS2_UJMP		18
#घोषणा R_NIOS2_CJMP		19
#घोषणा R_NIOS2_CALLR		20
#घोषणा R_NIOS2_ALIGN		21
/* Keep this the last entry.  */
#घोषणा R_NIOS2_NUM		22

प्रकार अचिन्हित दीर्घ elf_greg_t;

#घोषणा ELF_NGREG		49
प्रकार elf_greg_t elf_gregset_t[ELF_NGREG];

प्रकार अचिन्हित दीर्घ elf_fpregset_t;

/*
 * These are used to set parameters in the core dumps.
 */
#घोषणा ELF_CLASS	ELFCLASS32
#घोषणा ELF_DATA	ELFDATA2LSB
#घोषणा ELF_ARCH	EM_ALTERA_NIOS2

#पूर्ण_अगर /* _UAPI_ASM_NIOS2_ELF_H */
