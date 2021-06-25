<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1995-2004 Russell King
 *
 * Delay routines, using a pre-computed "loops_per_second" value.
 */
#अगर_अघोषित __ASM_ARM_DELAY_H
#घोषणा __ASM_ARM_DELAY_H

#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/param.h>	/* HZ */

/*
 * Loop (or tick) based delay:
 *
 * loops = loops_per_jअगरfy * jअगरfies_per_sec * delay_us / us_per_sec
 *
 * where:
 *
 * jअगरfies_per_sec = HZ
 * us_per_sec = 1000000
 *
 * Thereक्रमe the स्थिरant part is HZ / 1000000 which is a small
 * fractional number. To make this usable with पूर्णांकeger math, we
 * scale up this स्थिरant by 2^31, perक्रमm the actual multiplication,
 * and scale the result back करोwn by 2^31 with a simple shअगरt:
 *
 * loops = (loops_per_jअगरfy * delay_us * UDELAY_MULT) >> 31
 *
 * where:
 *
 * UDELAY_MULT = 2^31 * HZ / 1000000
 *             = (2^31 / 1000000) * HZ
 *             = 2147.483648 * HZ
 *             = 2147 * HZ + 483648 * HZ / 1000000
 *
 * 31 is the biggest scale shअगरt value that won't overflow 32 bits क्रम
 * delay_us * UDELAY_MULT assuming HZ <= 1000 and delay_us <= 2000.
 */
#घोषणा MAX_UDELAY_MS	2
#घोषणा UDELAY_MULT	UL(2147 * HZ + 483648 * HZ / 1000000)
#घोषणा UDELAY_SHIFT	31

#अगर_अघोषित __ASSEMBLY__

काष्ठा delay_समयr अणु
	अचिन्हित दीर्घ (*पढ़ो_current_समयr)(व्योम);
	अचिन्हित दीर्घ freq;
पूर्ण;

बाह्य काष्ठा arm_delay_ops अणु
	व्योम (*delay)(अचिन्हित दीर्घ);
	व्योम (*स्थिर_udelay)(अचिन्हित दीर्घ);
	व्योम (*udelay)(अचिन्हित दीर्घ);
	अचिन्हित दीर्घ ticks_per_jअगरfy;
पूर्ण arm_delay_ops;

#घोषणा __delay(n)		arm_delay_ops.delay(n)

/*
 * This function पूर्णांकentionally करोes not exist; अगर you see references to
 * it, it means that you're calling udelay() with an out of range value.
 *
 * With currently imposed limits, this means that we support a max delay
 * of 2000us. Further limits: HZ<=1000
 */
बाह्य व्योम __bad_udelay(व्योम);

/*
 * भागision by multiplication: you करोn't have to worry about
 * loss of precision.
 *
 * Use only क्रम very small delays ( < 2 msec).  Should probably use a
 * lookup table, really, as the multiplications take much too दीर्घ with
 * लघु delays.  This is a "reasonable" implementation, though (and the
 * first स्थिरant multiplications माला_लो optimized away अगर the delay is
 * a स्थिरant)
 */
#घोषणा __udelay(n)		arm_delay_ops.udelay(n)
#घोषणा __स्थिर_udelay(n)	arm_delay_ops.स्थिर_udelay(n)

#घोषणा udelay(n)							\
	(__builtin_स्थिरant_p(n) ?					\
	  ((n) > (MAX_UDELAY_MS * 1000) ? __bad_udelay() :		\
			__स्थिर_udelay((n) * UDELAY_MULT)) :		\
	  __udelay(n))

/* Loop-based definitions क्रम assembly code. */
बाह्य व्योम __loop_delay(अचिन्हित दीर्घ loops);
बाह्य व्योम __loop_udelay(अचिन्हित दीर्घ usecs);
बाह्य व्योम __loop_स्थिर_udelay(अचिन्हित दीर्घ);

/* Delay-loop समयr registration. */
#घोषणा ARCH_HAS_READ_CURRENT_TIMER
बाह्य व्योम रेजिस्टर_current_समयr_delay(स्थिर काष्ठा delay_समयr *समयr);

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* defined(_ARM_DELAY_H) */

