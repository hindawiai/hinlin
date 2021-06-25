<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_MICROBLAZE_ATOMIC_H
#घोषणा _ASM_MICROBLAZE_ATOMIC_H

#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र-generic/atomic.h>
#समावेश <यंत्र-generic/atomic64.h>

/*
 * Atomically test *v and decrement अगर it is greater than 0.
 * The function वापसs the old value of *v minus 1.
 */
अटल अंतरभूत पूर्णांक atomic_dec_अगर_positive(atomic_t *v)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक res;

	local_irq_save(flags);
	res = v->counter - 1;
	अगर (res >= 0)
		v->counter = res;
	local_irq_restore(flags);

	वापस res;
पूर्ण
#घोषणा atomic_dec_अगर_positive atomic_dec_अगर_positive

#पूर्ण_अगर /* _ASM_MICROBLAZE_ATOMIC_H */
