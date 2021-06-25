<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_X86_SWAB_H
#घोषणा _ASM_X86_SWAB_H

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>

अटल अंतरभूत __attribute_स्थिर__ __u32 __arch_swab32(__u32 val)
अणु
	यंत्र("bswapl %0" : "=r" (val) : "0" (val));
	वापस val;
पूर्ण
#घोषणा __arch_swab32 __arch_swab32

अटल अंतरभूत __attribute_स्थिर__ __u64 __arch_swab64(__u64 val)
अणु
#अगर_घोषित __i386__
	जोड़ अणु
		काष्ठा अणु
			__u32 a;
			__u32 b;
		पूर्ण s;
		__u64 u;
	पूर्ण v;
	v.u = val;
	यंत्र("bswapl %0 ; bswapl %1 ; xchgl %0,%1"
	    : "=r" (v.s.a), "=r" (v.s.b)
	    : "0" (v.s.a), "1" (v.s.b));
	वापस v.u;
#अन्यथा /* __i386__ */
	यंत्र("bswapq %0" : "=r" (val) : "0" (val));
	वापस val;
#पूर्ण_अगर
पूर्ण
#घोषणा __arch_swab64 __arch_swab64

#पूर्ण_अगर /* _ASM_X86_SWAB_H */
