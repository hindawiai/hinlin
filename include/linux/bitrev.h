<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_BITREV_H
#घोषणा _LINUX_BITREV_H

#समावेश <linux/types.h>

#अगर_घोषित CONFIG_HAVE_ARCH_BITREVERSE
#समावेश <यंत्र/bitrev.h>

#घोषणा __bitrev32 __arch_bitrev32
#घोषणा __bitrev16 __arch_bitrev16
#घोषणा __bitrev8 __arch_bitrev8

#अन्यथा
बाह्य u8 स्थिर byte_rev_table[256];
अटल अंतरभूत u8 __bitrev8(u8 byte)
अणु
	वापस byte_rev_table[byte];
पूर्ण

अटल अंतरभूत u16 __bitrev16(u16 x)
अणु
	वापस (__bitrev8(x & 0xff) << 8) | __bitrev8(x >> 8);
पूर्ण

अटल अंतरभूत u32 __bitrev32(u32 x)
अणु
	वापस (__bitrev16(x & 0xffff) << 16) | __bitrev16(x >> 16);
पूर्ण

#पूर्ण_अगर /* CONFIG_HAVE_ARCH_BITREVERSE */

#घोषणा __bitrev8x4(x)	(__bitrev32(swab32(x)))

#घोषणा __स्थिरant_bitrev32(x)	\
(अणु					\
	u32 ___x = x;			\
	___x = (___x >> 16) | (___x << 16);	\
	___x = ((___x & (u32)0xFF00FF00UL) >> 8) | ((___x & (u32)0x00FF00FFUL) << 8);	\
	___x = ((___x & (u32)0xF0F0F0F0UL) >> 4) | ((___x & (u32)0x0F0F0F0FUL) << 4);	\
	___x = ((___x & (u32)0xCCCCCCCCUL) >> 2) | ((___x & (u32)0x33333333UL) << 2);	\
	___x = ((___x & (u32)0xAAAAAAAAUL) >> 1) | ((___x & (u32)0x55555555UL) << 1);	\
	___x;								\
पूर्ण)

#घोषणा __स्थिरant_bitrev16(x)	\
(अणु					\
	u16 ___x = x;			\
	___x = (___x >> 8) | (___x << 8);	\
	___x = ((___x & (u16)0xF0F0U) >> 4) | ((___x & (u16)0x0F0FU) << 4);	\
	___x = ((___x & (u16)0xCCCCU) >> 2) | ((___x & (u16)0x3333U) << 2);	\
	___x = ((___x & (u16)0xAAAAU) >> 1) | ((___x & (u16)0x5555U) << 1);	\
	___x;								\
पूर्ण)

#घोषणा __स्थिरant_bitrev8x4(x) \
(अणु			\
	u32 ___x = x;	\
	___x = ((___x & (u32)0xF0F0F0F0UL) >> 4) | ((___x & (u32)0x0F0F0F0FUL) << 4);	\
	___x = ((___x & (u32)0xCCCCCCCCUL) >> 2) | ((___x & (u32)0x33333333UL) << 2);	\
	___x = ((___x & (u32)0xAAAAAAAAUL) >> 1) | ((___x & (u32)0x55555555UL) << 1);	\
	___x;								\
पूर्ण)

#घोषणा __स्थिरant_bitrev8(x)	\
(अणु					\
	u8 ___x = x;			\
	___x = (___x >> 4) | (___x << 4);	\
	___x = ((___x & (u8)0xCCU) >> 2) | ((___x & (u8)0x33U) << 2);	\
	___x = ((___x & (u8)0xAAU) >> 1) | ((___x & (u8)0x55U) << 1);	\
	___x;								\
पूर्ण)

#घोषणा bitrev32(x) \
(अणु			\
	u32 __x = x;	\
	__builtin_स्थिरant_p(__x) ?	\
	__स्थिरant_bitrev32(__x) :			\
	__bitrev32(__x);				\
पूर्ण)

#घोषणा bitrev16(x) \
(अणु			\
	u16 __x = x;	\
	__builtin_स्थिरant_p(__x) ?	\
	__स्थिरant_bitrev16(__x) :			\
	__bitrev16(__x);				\
 पूर्ण)

#घोषणा bitrev8x4(x) \
(अणु			\
	u32 __x = x;	\
	__builtin_स्थिरant_p(__x) ?	\
	__स्थिरant_bitrev8x4(__x) :			\
	__bitrev8x4(__x);				\
 पूर्ण)

#घोषणा bitrev8(x) \
(अणु			\
	u8 __x = x;	\
	__builtin_स्थिरant_p(__x) ?	\
	__स्थिरant_bitrev8(__x) :			\
	__bitrev8(__x)	;			\
 पूर्ण)
#पूर्ण_अगर /* _LINUX_BITREV_H */
