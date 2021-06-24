<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_CMPXCHG_CAS_H
#घोषणा __ASM_SH_CMPXCHG_CAS_H

अटल अंतरभूत अचिन्हित दीर्घ
__cmpxchg_u32(अस्थिर u32 *m, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new)
अणु
	__यंत्र__ __अस्थिर__("cas.l %1,%0,@r0"
		: "+r"(new)
		: "r"(old), "z"(m)
		: "t", "memory" );
	वापस new;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ xchg_u32(अस्थिर u32 *m, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ old;
	करो old = *m;
	जबतक (__cmpxchg_u32(m, old, val) != old);
	वापस old;
पूर्ण

#समावेश <यंत्र/cmpxchg-xchg.h>

#पूर्ण_अगर /* __ASM_SH_CMPXCHG_CAS_H */
