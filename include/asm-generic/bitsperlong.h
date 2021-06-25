<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_BITS_PER_LONG
#घोषणा __ASM_GENERIC_BITS_PER_LONG

#समावेश <uapi/यंत्र-generic/bitsperदीर्घ.h>


#अगर_घोषित CONFIG_64BIT
#घोषणा BITS_PER_LONG 64
#अन्यथा
#घोषणा BITS_PER_LONG 32
#पूर्ण_अगर /* CONFIG_64BIT */

/*
 * FIXME: The check currently अवरोधs x86-64 build, so it's
 * temporarily disabled. Please fix x86-64 and reenable
 */
#अगर 0 && BITS_PER_LONG != __BITS_PER_LONG
#त्रुटि Inconsistent word size. Check यंत्र/bitsperदीर्घ.h
#पूर्ण_अगर

#अगर_अघोषित BITS_PER_LONG_LONG
#घोषणा BITS_PER_LONG_LONG 64
#पूर्ण_अगर

/*
 * small_स्थिर_nbits(n) is true precisely when it is known at compile-समय
 * that BITMAP_SIZE(n) is 1, i.e. 1 <= n <= BITS_PER_LONG. This allows
 * various bit/biपंचांगap APIs to provide a fast अंतरभूत implementation. Biपंचांगaps
 * of size 0 are very rare, and a compile-समय-known-size 0 is most likely
 * a sign of error. They will be handled correctly by the bit/biपंचांगap APIs,
 * but using the out-of-line functions, so that the अंतरभूत implementations
 * can unconditionally dereference the poपूर्णांकer(s).
 */
#घोषणा small_स्थिर_nbits(nbits) \
	(__builtin_स्थिरant_p(nbits) && (nbits) <= BITS_PER_LONG && (nbits) > 0)

#पूर्ण_अगर /* __ASM_GENERIC_BITS_PER_LONG */
