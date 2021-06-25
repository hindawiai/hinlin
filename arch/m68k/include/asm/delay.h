<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_DELAY_H
#घोषणा _M68K_DELAY_H

#समावेश <यंत्र/param.h>

/*
 * Copyright (C) 1994 Hamish Macकरोnald
 * Copyright (C) 2004 Greg Ungerer <gerg@uclinux.com>
 *
 * Delay routines, using a pre-computed "loops_per_jiffy" value.
 */

#अगर defined(CONFIG_COLDFIRE)
/*
 * The ColdFire runs the delay loop at signअगरicantly dअगरferent speeds
 * depending upon दीर्घ word alignment or not.  We'll pad it to
 * दीर्घ word alignment which is the faster version.
 * The 0x4a8e is of course a 'tstl %fp' inकाष्ठाion.  This is better
 * than using a NOP (0x4e71) inकाष्ठाion because it executes in one
 * cycle not three and करोesn't allow क्रम an arbitrary delay रुकोing
 * क्रम bus cycles to finish.  Also fp/a6 isn't likely to cause a
 * stall रुकोing क्रम the रेजिस्टर to become valid अगर such is added
 * to the coldfire at some stage.
 */
#घोषणा	DELAY_ALIGN	".balignw 4, 0x4a8e\n\t"
#अन्यथा
/*
 * No inकाष्ठाion alignment required क्रम other m68k types.
 */
#घोषणा	DELAY_ALIGN
#पूर्ण_अगर

अटल अंतरभूत व्योम __delay(अचिन्हित दीर्घ loops)
अणु
	__यंत्र__ __अस्थिर__ (
		DELAY_ALIGN
		"1: subql #1,%0\n\t"
		"jcc 1b"
		: "=d" (loops)
		: "0" (loops));
पूर्ण

बाह्य व्योम __bad_udelay(व्योम);


#अगर_घोषित CONFIG_CPU_HAS_NO_MULDIV64
/*
 * The simpler m68k and ColdFire processors करो not have a 32*32->64
 * multiply inकाष्ठाion. So we need to handle them a little dअगरferently.
 * We use a bit of shअगरting and a single 32*32->32 multiply to get बंद.
 */
#घोषणा	HZSCALE		(268435456 / (1000000 / HZ))

#घोषणा	__स्थिर_udelay(u) \
	__delay(((((u) * HZSCALE) >> 11) * (loops_per_jअगरfy >> 11)) >> 6)

#अन्यथा

अटल अंतरभूत व्योम __xdelay(अचिन्हित दीर्घ xloops)
अणु
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ ("mulul %2,%0:%1"
		: "=d" (xloops), "=d" (पंचांगp)
		: "d" (xloops), "1" (loops_per_jअगरfy));
	__delay(xloops * HZ);
पूर्ण

/*
 * The definition of __स्थिर_udelay is specअगरically made a macro so that
 * the स्थिर factor (4295 = 2**32 / 1000000) can be optimized out when
 * the delay is a स्थिर.
 */
#घोषणा	__स्थिर_udelay(n)	(__xdelay((n) * 4295))

#पूर्ण_अगर

अटल अंतरभूत व्योम __udelay(अचिन्हित दीर्घ usecs)
अणु
	__स्थिर_udelay(usecs);
पूर्ण

/*
 * Use only क्रम very small delays ( < 1 msec).  Should probably use a
 * lookup table, really, as the multiplications take much too दीर्घ with
 * लघु delays.  This is a "reasonable" implementation, though (and the
 * first स्थिरant multiplications माला_लो optimized away अगर the delay is
 * a स्थिरant)
 */
#घोषणा udelay(n) (__builtin_स्थिरant_p(n) ? \
	((n) > 20000 ? __bad_udelay() : __स्थिर_udelay(n)) : __udelay(n))

/*
 * nanosecond delay:
 *
 * ((((HZSCALE) >> 11) * (loops_per_jअगरfy >> 11)) >> 6) is the number of loops
 * per microsecond
 *
 * 1000 / ((((HZSCALE) >> 11) * (loops_per_jअगरfy >> 11)) >> 6) is the number of
 * nanoseconds per loop
 *
 * So n / ( 1000 / ((((HZSCALE) >> 11) * (loops_per_jअगरfy >> 11)) >> 6) ) would
 * be the number of loops क्रम n nanoseconds
 */

/*
 * The simpler m68k and ColdFire processors करो not have a 32*32->64
 * multiply inकाष्ठाion. So we need to handle them a little dअगरferently.
 * We use a bit of shअगरting and a single 32*32->32 multiply to get बंद.
 * This is a macro so that the स्थिर version can factor out the first
 * multiply and shअगरt.
 */
#घोषणा	HZSCALE		(268435456 / (1000000 / HZ))

अटल अंतरभूत व्योम ndelay(अचिन्हित दीर्घ nsec)
अणु
	__delay(DIV_ROUND_UP(nsec *
			     ((((HZSCALE) >> 11) *
			       (loops_per_jअगरfy >> 11)) >> 6),
			     1000));
पूर्ण
#घोषणा ndelay(n) ndelay(n)

#पूर्ण_अगर /* defined(_M68K_DELAY_H) */
