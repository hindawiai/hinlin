<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_BITREV_H
#घोषणा __ASM_BITREV_H
अटल __always_अंतरभूत __attribute_स्थिर__ u32 __arch_bitrev32(u32 x)
अणु
	__यंत्र__ ("rbit %w0, %w1" : "=r" (x) : "r" (x));
	वापस x;
पूर्ण

अटल __always_अंतरभूत __attribute_स्थिर__ u16 __arch_bitrev16(u16 x)
अणु
	वापस __arch_bitrev32((u32)x) >> 16;
पूर्ण

अटल __always_अंतरभूत __attribute_स्थिर__ u8 __arch_bitrev8(u8 x)
अणु
	वापस __arch_bitrev32((u32)x) >> 24;
पूर्ण

#पूर्ण_अगर
