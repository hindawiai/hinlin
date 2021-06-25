<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_ATOMIC_H_
#घोषणा _ASM_GENERIC_BITOPS_ATOMIC_H_

#समावेश <linux/atomic.h>
#समावेश <linux/compiler.h>
#समावेश <यंत्र/barrier.h>

/*
 * Implementation of atomic bitops using atomic-fetch ops.
 * See Documentation/atomic_bitops.txt क्रम details.
 */

अटल __always_अंतरभूत व्योम set_bit(अचिन्हित पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *p)
अणु
	p += BIT_WORD(nr);
	atomic_दीर्घ_or(BIT_MASK(nr), (atomic_दीर्घ_t *)p);
पूर्ण

अटल __always_अंतरभूत व्योम clear_bit(अचिन्हित पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *p)
अणु
	p += BIT_WORD(nr);
	atomic_दीर्घ_andnot(BIT_MASK(nr), (atomic_दीर्घ_t *)p);
पूर्ण

अटल __always_अंतरभूत व्योम change_bit(अचिन्हित पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *p)
अणु
	p += BIT_WORD(nr);
	atomic_दीर्घ_xor(BIT_MASK(nr), (atomic_दीर्घ_t *)p);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_set_bit(अचिन्हित पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *p)
अणु
	दीर्घ old;
	अचिन्हित दीर्घ mask = BIT_MASK(nr);

	p += BIT_WORD(nr);
	अगर (READ_ONCE(*p) & mask)
		वापस 1;

	old = atomic_दीर्घ_fetch_or(mask, (atomic_दीर्घ_t *)p);
	वापस !!(old & mask);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_clear_bit(अचिन्हित पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *p)
अणु
	दीर्घ old;
	अचिन्हित दीर्घ mask = BIT_MASK(nr);

	p += BIT_WORD(nr);
	अगर (!(READ_ONCE(*p) & mask))
		वापस 0;

	old = atomic_दीर्घ_fetch_andnot(mask, (atomic_दीर्घ_t *)p);
	वापस !!(old & mask);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_change_bit(अचिन्हित पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *p)
अणु
	दीर्घ old;
	अचिन्हित दीर्घ mask = BIT_MASK(nr);

	p += BIT_WORD(nr);
	old = atomic_दीर्घ_fetch_xor(mask, (atomic_दीर्घ_t *)p);
	वापस !!(old & mask);
पूर्ण

#पूर्ण_अगर /* _ASM_GENERIC_BITOPS_ATOMIC_H */
