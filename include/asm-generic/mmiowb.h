<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_MMIOWB_H
#घोषणा __ASM_GENERIC_MMIOWB_H

/*
 * Generic implementation of mmiowb() tracking क्रम spinlocks.
 *
 * If your architecture करोesn't ensure that ग_लिखोs to an I/O peripheral
 * within two spinlocked sections on two dअगरferent CPUs are seen by the
 * peripheral in the order corresponding to the lock hanकरोver, then you
 * need to follow these FIVE easy steps:
 *
 * 	1. Implement mmiowb() (and arch_mmiowb_state() अगर you're fancy)
 *	   in यंत्र/mmiowb.h, then #समावेश this file
 *	2. Ensure your I/O ग_लिखो accessors call mmiowb_set_pending()
 *	3. Select ARCH_HAS_MMIOWB
 *	4. Untangle the resulting mess of header files
 *	5. Complain to your architects
 */
#अगर_घोषित CONFIG_MMIOWB

#समावेश <linux/compiler.h>
#समावेश <यंत्र-generic/mmiowb_types.h>

#अगर_अघोषित arch_mmiowb_state
#समावेश <यंत्र/percpu.h>
#समावेश <यंत्र/smp.h>

DECLARE_PER_CPU(काष्ठा mmiowb_state, __mmiowb_state);
#घोषणा __mmiowb_state()	raw_cpu_ptr(&__mmiowb_state)
#अन्यथा
#घोषणा __mmiowb_state()	arch_mmiowb_state()
#पूर्ण_अगर	/* arch_mmiowb_state */

अटल अंतरभूत व्योम mmiowb_set_pending(व्योम)
अणु
	काष्ठा mmiowb_state *ms = __mmiowb_state();

	अगर (likely(ms->nesting_count))
		ms->mmiowb_pending = ms->nesting_count;
पूर्ण

अटल अंतरभूत व्योम mmiowb_spin_lock(व्योम)
अणु
	काष्ठा mmiowb_state *ms = __mmiowb_state();
	ms->nesting_count++;
पूर्ण

अटल अंतरभूत व्योम mmiowb_spin_unlock(व्योम)
अणु
	काष्ठा mmiowb_state *ms = __mmiowb_state();

	अगर (unlikely(ms->mmiowb_pending)) अणु
		ms->mmiowb_pending = 0;
		mmiowb();
	पूर्ण

	ms->nesting_count--;
पूर्ण
#अन्यथा
#घोषणा mmiowb_set_pending()		करो अणु पूर्ण जबतक (0)
#घोषणा mmiowb_spin_lock()		करो अणु पूर्ण जबतक (0)
#घोषणा mmiowb_spin_unlock()		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर	/* CONFIG_MMIOWB */
#पूर्ण_अगर	/* __ASM_GENERIC_MMIOWB_H */
