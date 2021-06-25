<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_SH_SWAB_H
#घोषणा __ASM_SH_SWAB_H

/*
 * Copyright (C) 1999  Niibe Yutaka
 * Copyright (C) 2000, 2001  Paolo Alberelli
 */
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <यंत्र-generic/swab.h>

अटल अंतरभूत __attribute_स्थिर__ __u32 __arch_swab32(__u32 x)
अणु
	__यंत्र__(
		"swap.b		%1, %0\n\t"
		"swap.w		%0, %0\n\t"
		"swap.b		%0, %0"
		: "=r" (x)
		: "r" (x));

	वापस x;
पूर्ण
#घोषणा __arch_swab32 __arch_swab32

अटल अंतरभूत __attribute_स्थिर__ __u16 __arch_swab16(__u16 x)
अणु
	__यंत्र__(
		"swap.b		%1, %0"
		: "=r" (x)
		:  "r" (x));

	वापस x;
पूर्ण
#घोषणा __arch_swab16 __arch_swab16

अटल अंतरभूत __u64 __arch_swab64(__u64 val)
अणु
	जोड़ अणु
		काष्ठा अणु __u32 a,b; पूर्ण s;
		__u64 u;
	पूर्ण v, w;
	v.u = val;
	w.s.b = __arch_swab32(v.s.a);
	w.s.a = __arch_swab32(v.s.b);
	वापस w.u;
पूर्ण
#घोषणा __arch_swab64 __arch_swab64

#पूर्ण_अगर /* __ASM_SH_SWAB_H */
