<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 2003 by Ralf Baechle
 * Copyright (C) 1999 Silicon Graphics, Inc.
 */
#अगर_अघोषित __UAPI_ASM_BREAK_H
#घोषणा __UAPI_ASM_BREAK_H

/*
 * The following अवरोध codes are or were in use क्रम specअगरic purposes in
 * other MIPS operating प्रणालीs.  Linux/MIPS करोesn't use all of them.  The
 * unused ones are here as placeholders; we might encounter them in
 * non-Linux/MIPS object files or make use of them in the future.
 */
#घोषणा BRK_USERBP	0	/* User bp (used by debuggers) */
#घोषणा BRK_SSTEPBP	5	/* User bp (used by debuggers) */
#घोषणा BRK_OVERFLOW	6	/* Overflow check */
#घोषणा BRK_DIVZERO	7	/* Divide by zero check */
#घोषणा BRK_RANGE	8	/* Range error check */
#घोषणा BRK_BUG		12	/* Used by BUG() */
#घोषणा BRK_UPROBE	13	/* See <यंत्र/uprobes.h> */
#घोषणा BRK_UPROBE_XOL	14	/* See <यंत्र/uprobes.h> */
#घोषणा BRK_MEMU	514	/* Used by FPU emulator */
#घोषणा BRK_KPROBE_BP	515	/* Kprobe अवरोध */
#घोषणा BRK_KPROBE_SSTEPBP 516	/* Kprobe single step software implementation */
#घोषणा BRK_MULOVF	1023	/* Multiply overflow */

#पूर्ण_अगर /* __UAPI_ASM_BREAK_H */
