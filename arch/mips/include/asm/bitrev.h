<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MIPS_ASM_BITREV_H__
#घोषणा __MIPS_ASM_BITREV_H__

#समावेश <linux/swab.h>

अटल __always_अंतरभूत __attribute_स्थिर__ u32 __arch_bitrev32(u32 x)
अणु
	u32 ret;

	यंत्र("bitswap	%0, %1" : "=r"(ret) : "r"(__swab32(x)));
	वापस ret;
पूर्ण

अटल __always_अंतरभूत __attribute_स्थिर__ u16 __arch_bitrev16(u16 x)
अणु
	u16 ret;

	यंत्र("bitswap	%0, %1" : "=r"(ret) : "r"(__swab16(x)));
	वापस ret;
पूर्ण

अटल __always_अंतरभूत __attribute_स्थिर__ u8 __arch_bitrev8(u8 x)
अणु
	u8 ret;

	यंत्र("bitswap	%0, %1" : "=r"(ret) : "r"(x));
	वापस ret;
पूर्ण

#पूर्ण_अगर /* __MIPS_ASM_BITREV_H__ */
