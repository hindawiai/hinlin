<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 2003 by Ralf Baechle
 * Copyright (C) 1999 Silicon Graphics, Inc.
 */
#अगर_अघोषित __ASM_BREAK_H
#घोषणा __ASM_BREAK_H

#अगर_घोषित __UAPI_ASM_BREAK_H
#त्रुटि "Error: Do not directly include <uapi/asm/break.h>"
#पूर्ण_अगर
#समावेश <uapi/यंत्र/अवरोध.h>

/*
 * Break codes used पूर्णांकernally to the kernel.
 */
#घोषणा BRK_KDB		513	/* Used in KDB_ENTER() */
#घोषणा BRK_MEMU	514	/* Used by FPU emulator */
#घोषणा BRK_KPROBE_BP	515	/* Kprobe अवरोध */
#घोषणा BRK_KPROBE_SSTEPBP 516	/* Kprobe single step software implementation */
#घोषणा BRK_MULOVF	1023	/* Multiply overflow */

#पूर्ण_अगर /* __ASM_BREAK_H */
