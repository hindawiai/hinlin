<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_BITOPS_CAS_H
#घोषणा __ASM_SH_BITOPS_CAS_H

अटल अंतरभूत अचिन्हित __bo_cas(अस्थिर अचिन्हित *p, अचिन्हित old, अचिन्हित new)
अणु
	__यंत्र__ __अस्थिर__("cas.l %1,%0,@r0"
		: "+r"(new)
		: "r"(old), "z"(p)
		: "t", "memory" );
	वापस new;
पूर्ण

अटल अंतरभूत व्योम set_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	अचिन्हित mask, old;
	अस्थिर अचिन्हित *a = addr;

	a += nr >> 5;
	mask = 1U << (nr & 0x1f);

	करो old = *a;
	जबतक (__bo_cas(a, old, old|mask) != old);
पूर्ण

अटल अंतरभूत व्योम clear_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	अचिन्हित mask, old;
	अस्थिर अचिन्हित *a = addr;

	a += nr >> 5;
	mask = 1U << (nr & 0x1f);

	करो old = *a;
	जबतक (__bo_cas(a, old, old&~mask) != old);
पूर्ण

अटल अंतरभूत व्योम change_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	अचिन्हित mask, old;
	अस्थिर अचिन्हित *a = addr;

	a += nr >> 5;
	mask = 1U << (nr & 0x1f);

	करो old = *a;
	जबतक (__bo_cas(a, old, old^mask) != old);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_set_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	अचिन्हित mask, old;
	अस्थिर अचिन्हित *a = addr;

	a += nr >> 5;
	mask = 1U << (nr & 0x1f);

	करो old = *a;
	जबतक (__bo_cas(a, old, old|mask) != old);

	वापस !!(old & mask);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_clear_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	अचिन्हित mask, old;
	अस्थिर अचिन्हित *a = addr;

	a += nr >> 5;
	mask = 1U << (nr & 0x1f);

	करो old = *a;
	जबतक (__bo_cas(a, old, old&~mask) != old);

	वापस !!(old & mask);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_change_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	अचिन्हित mask, old;
	अस्थिर अचिन्हित *a = addr;

	a += nr >> 5;
	mask = 1U << (nr & 0x1f);

	करो old = *a;
	जबतक (__bo_cas(a, old, old^mask) != old);

	वापस !!(old & mask);
पूर्ण

#समावेश <यंत्र-generic/bitops/non-atomic.h>

#पूर्ण_अगर /* __ASM_SH_BITOPS_CAS_H */
