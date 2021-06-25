<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008 Michal Simek
 * Copyright (C) 2007 John Williams
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */

#अगर_अघोषित _ASM_MICROBLAZE_DELAY_H
#घोषणा _ASM_MICROBLAZE_DELAY_H

#समावेश <linux/param.h>

अटल अंतरभूत व्योम __delay(अचिन्हित दीर्घ loops)
अणु
	यंत्र अस्थिर ("# __delay		\n\t"		\
			"1: addi	%0, %0, -1\t\n"		\
			"bneid	%0, 1b		\t\n"		\
			"nop			\t\n"
			: "=r" (loops)
			: "0" (loops));
पूर्ण

/*
 * Note that 19 * 226 == 4294 ==~ 2^32 / 10^6, so
 * loops = (4294 * usecs * loops_per_jअगरfy * HZ) / 2^32.
 *
 * The mul inकाष्ठाion gives us loops = (a * b) / 2^32.
 * We choose a = usecs * 19 * HZ and b = loops_per_jअगरfy * 226
 * because this lets us support a wide range of HZ and
 * loops_per_jअगरfy values without either a or b overflowing 2^32.
 * Thus we need usecs * HZ <= (2^32 - 1) / 19 = 226050910 and
 * loops_per_jअगरfy <= (2^32 - 1) / 226 = 19004280
 * (which corresponds to ~3800 bogomips at HZ = 100).
 * -- paulus
 */
#घोषणा __MAX_UDELAY	(226050910UL/HZ)	/* maximum udelay argument */
#घोषणा __MAX_NDELAY	(4294967295UL/HZ)	/* maximum ndelay argument */

बाह्य अचिन्हित दीर्घ loops_per_jअगरfy;

अटल अंतरभूत व्योम __udelay(अचिन्हित पूर्णांक x)
अणु

	अचिन्हित दीर्घ दीर्घ पंचांगp =
		(अचिन्हित दीर्घ दीर्घ)x * (अचिन्हित दीर्घ दीर्घ)loops_per_jअगरfy \
			* 226LL;
	अचिन्हित loops = पंचांगp >> 32;

/*
	__यंत्र__("mulxuu %0,%1,%2" : "=r" (loops) :
		"r" (x), "r" (loops_per_jअगरfy * 226));
*/
	__delay(loops);
पूर्ण

बाह्य व्योम __bad_udelay(व्योम);		/* deliberately undefined */
बाह्य व्योम __bad_ndelay(व्योम);		/* deliberately undefined */

#घोषणा udelay(n)						\
	(अणु							\
		अगर (__builtin_स्थिरant_p(n)) अणु			\
			अगर ((n) / __MAX_UDELAY >= 1)		\
				__bad_udelay();			\
			अन्यथा					\
				__udelay((n) * (19 * HZ));	\
		पूर्ण अन्यथा अणु					\
			__udelay((n) * (19 * HZ));		\
		पूर्ण						\
	पूर्ण)

#घोषणा ndelay(n)						\
	(अणु							\
		अगर (__builtin_स्थिरant_p(n)) अणु			\
			अगर ((n) / __MAX_NDELAY >= 1)		\
				__bad_ndelay();			\
			अन्यथा					\
				__udelay((n) * HZ);		\
		पूर्ण अन्यथा अणु					\
			__udelay((n) * HZ);			\
		पूर्ण						\
	पूर्ण)

#घोषणा muद_भाग(a, b, c)		(((a)*(b))/(c))

#पूर्ण_अगर /* _ASM_MICROBLAZE_DELAY_H */
