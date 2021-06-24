<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994 by Walकरोrf Electronics
 * Copyright (C) 1995 - 2000, 01, 03 by Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 * Copyright (C) 2007, 2014 Maciej W. Rozycki
 */
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/param.h>
#समावेश <linux/smp.h>
#समावेश <linux/stringअगरy.h>

#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/compiler.h>
#समावेश <यंत्र/war.h>

#अगर_अघोषित CONFIG_CPU_DADDI_WORKAROUNDS
#घोषणा GCC_DADDI_IMM_ASM() "I"
#अन्यथा
#घोषणा GCC_DADDI_IMM_ASM() "r"
#पूर्ण_अगर

#अगर_अघोषित CONFIG_HAVE_PLAT_DELAY

व्योम __delay(अचिन्हित दीर्घ loops)
अणु
	__यंत्र__ __अस्थिर__ (
	"	.set	noreorder				\n"
	"	.align	3					\n"
	"1:	bnez	%0, 1b					\n"
	"	 " __stringअगरy(LONG_SUBU) "	%0, %1		\n"
	"	.set	reorder					\n"
	: "=r" (loops)
	: GCC_DADDI_IMM_ASM() (1), "0" (loops));
पूर्ण
EXPORT_SYMBOL(__delay);

/*
 * Division by multiplication: you करोn't have to worry about
 * loss of precision.
 *
 * Use only क्रम very small delays ( < 1 msec).	Should probably use a
 * lookup table, really, as the multiplications take much too दीर्घ with
 * लघु delays.  This is a "reasonable" implementation, though (and the
 * first स्थिरant multiplications माला_लो optimized away अगर the delay is
 * a स्थिरant)
 */

व्योम __udelay(अचिन्हित दीर्घ us)
अणु
	अचिन्हित पूर्णांक lpj = raw_current_cpu_data.udelay_val;

	__delay((us * 0x000010c7ull * HZ * lpj) >> 32);
पूर्ण
EXPORT_SYMBOL(__udelay);

व्योम __ndelay(अचिन्हित दीर्घ ns)
अणु
	अचिन्हित पूर्णांक lpj = raw_current_cpu_data.udelay_val;

	__delay((ns * 0x00000005ull * HZ * lpj) >> 32);
पूर्ण
EXPORT_SYMBOL(__ndelay);

#पूर्ण_अगर
