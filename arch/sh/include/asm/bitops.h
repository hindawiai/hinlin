<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_BITOPS_H
#घोषणा __ASM_SH_BITOPS_H

#अगर_अघोषित _LINUX_BITOPS_H
#त्रुटि only <linux/bitops.h> can be included directly
#पूर्ण_अगर

/* For __swab32 */
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/barrier.h>

#अगर_घोषित CONFIG_GUSA_RB
#समावेश <यंत्र/bitops-grb.h>
#या_अगर defined(CONFIG_CPU_SH2A)
#समावेश <यंत्र-generic/bitops/atomic.h>
#समावेश <यंत्र/bitops-op32.h>
#या_अगर defined(CONFIG_CPU_SH4A)
#समावेश <यंत्र/bitops-llsc.h>
#या_अगर defined(CONFIG_CPU_J2) && defined(CONFIG_SMP)
#समावेश <यंत्र/bitops-cas.h>
#अन्यथा
#समावेश <यंत्र-generic/bitops/atomic.h>
#समावेश <यंत्र-generic/bitops/non-atomic.h>
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ ffz(अचिन्हित दीर्घ word)
अणु
	अचिन्हित दीर्घ result;

	__यंत्र__("1:\n\t"
		"shlr	%1\n\t"
		"bt/s	1b\n\t"
		" add	#1, %0"
		: "=r" (result), "=r" (word)
		: "0" (~0L), "1" (word)
		: "t");
	वापस result;
पूर्ण

/**
 * __ffs - find first bit in word.
 * @word: The word to search
 *
 * Undefined अगर no bit exists, so code should check against 0 first.
 */
अटल अंतरभूत अचिन्हित दीर्घ __ffs(अचिन्हित दीर्घ word)
अणु
	अचिन्हित दीर्घ result;

	__यंत्र__("1:\n\t"
		"shlr	%1\n\t"
		"bf/s	1b\n\t"
		" add	#1, %0"
		: "=r" (result), "=r" (word)
		: "0" (~0L), "1" (word)
		: "t");
	वापस result;
पूर्ण

#समावेश <यंत्र-generic/bitops/ffs.h>
#समावेश <यंत्र-generic/bitops/hweight.h>
#समावेश <यंत्र-generic/bitops/lock.h>
#समावेश <यंत्र-generic/bitops/sched.h>
#समावेश <यंत्र-generic/bitops/ext2-atomic.h>
#समावेश <यंत्र-generic/bitops/fls.h>
#समावेश <यंत्र-generic/bitops/__fls.h>
#समावेश <यंत्र-generic/bitops/fls64.h>

#समावेश <यंत्र-generic/bitops/le.h>
#समावेश <यंत्र-generic/bitops/find.h>

#पूर्ण_अगर /* __ASM_SH_BITOPS_H */
