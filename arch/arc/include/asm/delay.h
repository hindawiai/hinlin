<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Delay routines using pre computed loops_per_jअगरfy value.
 *
 * vineetg: Feb 2012
 *  -Rewrote in "C" to aव्योम dealing with availability of H/w MPY
 *  -Also reduced the num of MPY operations from 3 to 2
 *
 * Amit Bhor: Codito Technologies 2004
 */

#अगर_अघोषित __ASM_ARC_UDELAY_H
#घोषणा __ASM_ARC_UDELAY_H

#समावेश <यंत्र-generic/types.h>
#समावेश <यंत्र/param.h>		/* HZ */

बाह्य अचिन्हित दीर्घ loops_per_jअगरfy;

अटल अंतरभूत व्योम __delay(अचिन्हित दीर्घ loops)
अणु
	__यंत्र__ __अस्थिर__(
	"	mov lp_count, %0	\n"
	"	lp  1f			\n"
	"	nop			\n"
	"1:				\n"
	:
        : "r"(loops)
        : "lp_count");
पूर्ण

बाह्य व्योम __bad_udelay(व्योम);

/*
 * Normal Math क्रम computing loops in "N" usecs
 *  -we have precomputed @loops_per_jअगरfy
 *  -1 sec has HZ jअगरfies
 * loops per "N" usecs = ((loops_per_jअगरfy * HZ / 1000000) * N)
 *
 * Approximate Division by multiplication:
 *  -Mathematically अगर we multiply and भागide a number by same value the
 *   result reमुख्यs unchanged:  In this हाल, we use 2^32
 *  -> (loops_per_N_usec * 2^32 ) / 2^32
 *  -> (((loops_per_jअगरfy * HZ / 1000000) * N) * 2^32) / 2^32
 *  -> (loops_per_jअगरfy * HZ * N * 4295) / 2^32
 *
 *  -Divide by 2^32 is very simply right shअगरt by 32
 *  -We simply need to ensure that the multiply per above eqn happens in
 *   64-bit precision (अगर CPU करोesn't support it - gcc can emaulate it)
 */

अटल अंतरभूत व्योम __udelay(अचिन्हित दीर्घ usecs)
अणु
	अचिन्हित दीर्घ loops;

	/* (u64) cast ensures 64 bit MPY - real or emulated
	 * HZ * 4295 is pre-evaluated by gcc - hence only 2 mpy ops
	 */
	loops = ((u64) usecs * 4295 * HZ * loops_per_jअगरfy) >> 32;

	__delay(loops);
पूर्ण

#घोषणा udelay(n) (__builtin_स्थिरant_p(n) ? ((n) > 20000 ? __bad_udelay() \
				: __udelay(n)) : __udelay(n))

#पूर्ण_अगर /* __ASM_ARC_UDELAY_H */
