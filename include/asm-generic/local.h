<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_LOCAL_H
#घोषणा _ASM_GENERIC_LOCAL_H

#समावेश <linux/percpu.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/types.h>

/*
 * A चिन्हित दीर्घ type क्रम operations which are atomic क्रम a single CPU.
 * Usually used in combination with per-cpu variables.
 *
 * This is the शेष implementation, which uses atomic_दीर्घ_t.  Which is
 * rather poपूर्णांकless.  The whole poपूर्णांक behind local_t is that some processors
 * can perक्रमm atomic adds and subtracts in a manner which is atomic wrt IRQs
 * running on this CPU.  local_t allows exploitation of such capabilities.
 */

/* Implement in terms of atomics. */

/* Don't use typedef: don't want them to be mixed with atomic_t's. */
प्रकार काष्ठा
अणु
	atomic_दीर्घ_t a;
पूर्ण local_t;

#घोषणा LOCAL_INIT(i)	अणु ATOMIC_LONG_INIT(i) पूर्ण

#घोषणा local_पढ़ो(l)	atomic_दीर्घ_पढ़ो(&(l)->a)
#घोषणा local_set(l,i)	atomic_दीर्घ_set((&(l)->a),(i))
#घोषणा local_inc(l)	atomic_दीर्घ_inc(&(l)->a)
#घोषणा local_dec(l)	atomic_दीर्घ_dec(&(l)->a)
#घोषणा local_add(i,l)	atomic_दीर्घ_add((i),(&(l)->a))
#घोषणा local_sub(i,l)	atomic_दीर्घ_sub((i),(&(l)->a))

#घोषणा local_sub_and_test(i, l) atomic_दीर्घ_sub_and_test((i), (&(l)->a))
#घोषणा local_dec_and_test(l) atomic_दीर्घ_dec_and_test(&(l)->a)
#घोषणा local_inc_and_test(l) atomic_दीर्घ_inc_and_test(&(l)->a)
#घोषणा local_add_negative(i, l) atomic_दीर्घ_add_negative((i), (&(l)->a))
#घोषणा local_add_वापस(i, l) atomic_दीर्घ_add_वापस((i), (&(l)->a))
#घोषणा local_sub_वापस(i, l) atomic_दीर्घ_sub_वापस((i), (&(l)->a))
#घोषणा local_inc_वापस(l) atomic_दीर्घ_inc_वापस(&(l)->a)

#घोषणा local_cmpxchg(l, o, n) atomic_दीर्घ_cmpxchg((&(l)->a), (o), (n))
#घोषणा local_xchg(l, n) atomic_दीर्घ_xchg((&(l)->a), (n))
#घोषणा local_add_unless(l, _a, u) atomic_दीर्घ_add_unless((&(l)->a), (_a), (u))
#घोषणा local_inc_not_zero(l) atomic_दीर्घ_inc_not_zero(&(l)->a)

/* Non-atomic variants, ie. preemption disabled and won't be touched
 * in पूर्णांकerrupt, etc.  Some archs can optimize this हाल well. */
#घोषणा __local_inc(l)		local_set((l), local_पढ़ो(l) + 1)
#घोषणा __local_dec(l)		local_set((l), local_पढ़ो(l) - 1)
#घोषणा __local_add(i,l)	local_set((l), local_पढ़ो(l) + (i))
#घोषणा __local_sub(i,l)	local_set((l), local_पढ़ो(l) - (i))

#पूर्ण_अगर /* _ASM_GENERIC_LOCAL_H */
