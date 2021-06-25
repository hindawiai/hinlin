<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_DELAY_H
#घोषणा __ASM_GENERIC_DELAY_H

/* Undefined functions to get compile-समय errors */
बाह्य व्योम __bad_udelay(व्योम);
बाह्य व्योम __bad_ndelay(व्योम);

बाह्य व्योम __udelay(अचिन्हित दीर्घ usecs);
बाह्य व्योम __ndelay(अचिन्हित दीर्घ nsecs);
बाह्य व्योम __स्थिर_udelay(अचिन्हित दीर्घ xloops);
बाह्य व्योम __delay(अचिन्हित दीर्घ loops);

/*
 * The weird n/20000 thing suppresses a "comparison is always false due to
 * limited range of data type" warning with non-स्थिर 8-bit arguments.
 */

/* 0x10c7 is 2**32 / 1000000 (rounded up) */
#घोषणा udelay(n)							\
	(अणु								\
		अगर (__builtin_स्थिरant_p(n)) अणु				\
			अगर ((n) / 20000 >= 1)				\
				 __bad_udelay();			\
			अन्यथा						\
				__स्थिर_udelay((n) * 0x10c7ul);		\
		पूर्ण अन्यथा अणु						\
			__udelay(n);					\
		पूर्ण							\
	पूर्ण)

/* 0x5 is 2**32 / 1000000000 (rounded up) */
#घोषणा ndelay(n)							\
	(अणु								\
		अगर (__builtin_स्थिरant_p(n)) अणु				\
			अगर ((n) / 20000 >= 1)				\
				__bad_ndelay();				\
			अन्यथा						\
				__स्थिर_udelay((n) * 5ul);		\
		पूर्ण अन्यथा अणु						\
			__ndelay(n);					\
		पूर्ण							\
	पूर्ण)

#पूर्ण_अगर /* __ASM_GENERIC_DELAY_H */
