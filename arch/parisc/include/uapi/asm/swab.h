<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _PARISC_SWAB_H
#घोषणा _PARISC_SWAB_H

#समावेश <यंत्र/bitsperदीर्घ.h>
#समावेश <linux/types.h>
#समावेश <linux/compiler.h>

#घोषणा __SWAB_64_THRU_32__

अटल अंतरभूत __attribute_स्थिर__ __u16 __arch_swab16(__u16 x)
अणु
	__यंत्र__("dep %0, 15, 8, %0\n\t"		/* deposit 00ab -> 0bab */
		"shd %%r0, %0, 8, %0"		/* shअगरt 000000ab -> 00ba */
		: "=r" (x)
		: "0" (x));
	वापस x;
पूर्ण
#घोषणा __arch_swab16 __arch_swab16

अटल अंतरभूत __attribute_स्थिर__ __u32 __arch_swab24(__u32 x)
अणु
	__यंत्र__("shd %0, %0, 8, %0\n\t"		/* shअगरt xabcxabc -> cxab */
		"dep %0, 15, 8, %0\n\t"		/* deposit cxab -> cbab */
		"shd %%r0, %0, 8, %0"		/* shअगरt 0000cbab -> 0cba */
		: "=r" (x)
		: "0" (x));
	वापस x;
पूर्ण

अटल अंतरभूत __attribute_स्थिर__ __u32 __arch_swab32(__u32 x)
अणु
	अचिन्हित पूर्णांक temp;
	__यंत्र__("shd %0, %0, 16, %1\n\t"	/* shअगरt abcdabcd -> cdab */
		"dep %1, 15, 8, %1\n\t"		/* deposit cdab -> cbab */
		"shd %0, %1, 8, %0"		/* shअगरt abcdcbab -> dcba */
		: "=r" (x), "=&r" (temp)
		: "0" (x));
	वापस x;
पूर्ण
#घोषणा __arch_swab32 __arch_swab32

#अगर __BITS_PER_LONG > 32
/*
** From "PA-RISC 2.0 Architecture", HP Professional Books.
** See Appendix I page 8 , "Endian Byte Swapping".
**
** Pretty cool algorithm: (* == zero'd bits)
**      PERMH   01234567 -> 67452301 पूर्णांकo %0
**      HSHL    67452301 -> 7*5*3*1* पूर्णांकo %1
**      HSHR    67452301 -> *6*4*2*0 पूर्णांकo %0
**      OR      %0 | %1  -> 76543210 पूर्णांकo %0 (all करोne!)
*/
अटल अंतरभूत __attribute_स्थिर__ __u64 __arch_swab64(__u64 x)
अणु
	__u64 temp;
	__यंत्र__("permh,3210 %0, %0\n\t"
		"hshl %0, 8, %1\n\t"
		"hshr,u %0, 8, %0\n\t"
		"or %1, %0, %0"
		: "=r" (x), "=&r" (temp)
		: "0" (x));
	वापस x;
पूर्ण
#घोषणा __arch_swab64 __arch_swab64
#पूर्ण_अगर /* __BITS_PER_LONG > 32 */

#पूर्ण_अगर /* _PARISC_SWAB_H */
