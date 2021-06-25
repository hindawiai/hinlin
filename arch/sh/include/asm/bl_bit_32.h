<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_BL_BIT_32_H
#घोषणा __ASM_SH_BL_BIT_32_H

अटल अंतरभूत व्योम set_bl_bit(व्योम)
अणु
	अचिन्हित दीर्घ __dummy0, __dummy1;

	__यंत्र__ __अस्थिर__ (
		"stc	sr, %0\n\t"
		"or	%2, %0\n\t"
		"and	%3, %0\n\t"
		"ldc	%0, sr\n\t"
		: "=&r" (__dummy0), "=r" (__dummy1)
		: "r" (0x10000000), "r" (0xffffff0f)
		: "memory"
	);
पूर्ण

अटल अंतरभूत व्योम clear_bl_bit(व्योम)
अणु
	अचिन्हित दीर्घ __dummy0, __dummy1;

	__यंत्र__ __अस्थिर__ (
		"stc	sr, %0\n\t"
		"and	%2, %0\n\t"
		"ldc	%0, sr\n\t"
		: "=&r" (__dummy0), "=r" (__dummy1)
		: "1" (~0x10000000)
		: "memory"
	);
पूर्ण

#पूर्ण_अगर /* __ASM_SH_BL_BIT_32_H */
