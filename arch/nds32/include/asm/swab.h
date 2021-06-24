<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित __NDS32_SWAB_H__
#घोषणा __NDS32_SWAB_H__

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>

अटल __अंतरभूत__ __attribute_स्थिर__ __u32 ___arch__swab32(__u32 x)
अणु
	__यंत्र__("wsbh   %0, %0\n\t"	/* word swap byte within halfword */
		"rotri  %0, %0, #16\n"
		:"=r"(x)
		:"0"(x));
	वापस x;
पूर्ण

अटल __अंतरभूत__ __attribute_स्थिर__ __u16 ___arch__swab16(__u16 x)
अणु
	__यंत्र__("wsbh   %0, %0\n"	/* word swap byte within halfword */
		:"=r"(x)
		:"0"(x));
	वापस x;
पूर्ण

#घोषणा __arch_swab32(x) ___arch__swab32(x)
#घोषणा __arch_swab16(x) ___arch__swab16(x)

#अगर !defined(__STRICT_ANSI__) || defined(__KERNEL__)
#घोषणा __BYTEORDER_HAS_U64__
#घोषणा __SWAB_64_THRU_32__
#पूर्ण_अगर

#पूर्ण_अगर /* __NDS32_SWAB_H__ */
