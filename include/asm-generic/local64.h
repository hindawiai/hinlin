<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_LOCAL64_H
#घोषणा _ASM_GENERIC_LOCAL64_H

#समावेश <linux/percpu.h>
#समावेश <यंत्र/types.h>

/*
 * A चिन्हित दीर्घ type क्रम operations which are atomic क्रम a single CPU.
 * Usually used in combination with per-cpu variables.
 *
 * This is the शेष implementation, which uses atomic64_t.  Which is
 * rather poपूर्णांकless.  The whole poपूर्णांक behind local64_t is that some processors
 * can perक्रमm atomic adds and subtracts in a manner which is atomic wrt IRQs
 * running on this CPU.  local64_t allows exploitation of such capabilities.
 */

/* Implement in terms of atomics. */

#अगर BITS_PER_LONG == 64

#समावेश <यंत्र/local.h>

प्रकार काष्ठा अणु
	local_t a;
पूर्ण local64_t;

#घोषणा LOCAL64_INIT(i)	अणु LOCAL_INIT(i) पूर्ण

#घोषणा local64_पढ़ो(l)		local_पढ़ो(&(l)->a)
#घोषणा local64_set(l,i)	local_set((&(l)->a),(i))
#घोषणा local64_inc(l)		local_inc(&(l)->a)
#घोषणा local64_dec(l)		local_dec(&(l)->a)
#घोषणा local64_add(i,l)	local_add((i),(&(l)->a))
#घोषणा local64_sub(i,l)	local_sub((i),(&(l)->a))

#घोषणा local64_sub_and_test(i, l) local_sub_and_test((i), (&(l)->a))
#घोषणा local64_dec_and_test(l) local_dec_and_test(&(l)->a)
#घोषणा local64_inc_and_test(l) local_inc_and_test(&(l)->a)
#घोषणा local64_add_negative(i, l) local_add_negative((i), (&(l)->a))
#घोषणा local64_add_वापस(i, l) local_add_वापस((i), (&(l)->a))
#घोषणा local64_sub_वापस(i, l) local_sub_वापस((i), (&(l)->a))
#घोषणा local64_inc_वापस(l)	local_inc_वापस(&(l)->a)

#घोषणा local64_cmpxchg(l, o, n) local_cmpxchg((&(l)->a), (o), (n))
#घोषणा local64_xchg(l, n)	local_xchg((&(l)->a), (n))
#घोषणा local64_add_unless(l, _a, u) local_add_unless((&(l)->a), (_a), (u))
#घोषणा local64_inc_not_zero(l)	local_inc_not_zero(&(l)->a)

/* Non-atomic variants, ie. preemption disabled and won't be touched
 * in पूर्णांकerrupt, etc.  Some archs can optimize this हाल well. */
#घोषणा __local64_inc(l)	local64_set((l), local64_पढ़ो(l) + 1)
#घोषणा __local64_dec(l)	local64_set((l), local64_पढ़ो(l) - 1)
#घोषणा __local64_add(i,l)	local64_set((l), local64_पढ़ो(l) + (i))
#घोषणा __local64_sub(i,l)	local64_set((l), local64_पढ़ो(l) - (i))

#अन्यथा /* BITS_PER_LONG != 64 */

#समावेश <linux/atomic.h>

/* Don't use typedef: don't want them to be mixed with atomic_t's. */
प्रकार काष्ठा अणु
	atomic64_t a;
पूर्ण local64_t;

#घोषणा LOCAL64_INIT(i)	अणु ATOMIC_LONG_INIT(i) पूर्ण

#घोषणा local64_पढ़ो(l)		atomic64_पढ़ो(&(l)->a)
#घोषणा local64_set(l,i)	atomic64_set((&(l)->a),(i))
#घोषणा local64_inc(l)		atomic64_inc(&(l)->a)
#घोषणा local64_dec(l)		atomic64_dec(&(l)->a)
#घोषणा local64_add(i,l)	atomic64_add((i),(&(l)->a))
#घोषणा local64_sub(i,l)	atomic64_sub((i),(&(l)->a))

#घोषणा local64_sub_and_test(i, l) atomic64_sub_and_test((i), (&(l)->a))
#घोषणा local64_dec_and_test(l) atomic64_dec_and_test(&(l)->a)
#घोषणा local64_inc_and_test(l) atomic64_inc_and_test(&(l)->a)
#घोषणा local64_add_negative(i, l) atomic64_add_negative((i), (&(l)->a))
#घोषणा local64_add_वापस(i, l) atomic64_add_वापस((i), (&(l)->a))
#घोषणा local64_sub_वापस(i, l) atomic64_sub_वापस((i), (&(l)->a))
#घोषणा local64_inc_वापस(l)	atomic64_inc_वापस(&(l)->a)

#घोषणा local64_cmpxchg(l, o, n) atomic64_cmpxchg((&(l)->a), (o), (n))
#घोषणा local64_xchg(l, n)	atomic64_xchg((&(l)->a), (n))
#घोषणा local64_add_unless(l, _a, u) atomic64_add_unless((&(l)->a), (_a), (u))
#घोषणा local64_inc_not_zero(l)	atomic64_inc_not_zero(&(l)->a)

/* Non-atomic variants, ie. preemption disabled and won't be touched
 * in पूर्णांकerrupt, etc.  Some archs can optimize this हाल well. */
#घोषणा __local64_inc(l)	local64_set((l), local64_पढ़ो(l) + 1)
#घोषणा __local64_dec(l)	local64_set((l), local64_पढ़ो(l) - 1)
#घोषणा __local64_add(i,l)	local64_set((l), local64_पढ़ो(l) + (i))
#घोषणा __local64_sub(i,l)	local64_set((l), local64_पढ़ो(l) - (i))

#पूर्ण_अगर /* BITS_PER_LONG != 64 */

#पूर्ण_अगर /* _ASM_GENERIC_LOCAL64_H */
