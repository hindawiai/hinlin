<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 1999, 2016
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>,
 *	      Denis Joseph Barrow,
 *	      Arnd Bergmann,
 */

#अगर_अघोषित __ARCH_S390_ATOMIC__
#घोषणा __ARCH_S390_ATOMIC__

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/atomic_ops.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/cmpxchg.h>

अटल अंतरभूत पूर्णांक arch_atomic_पढ़ो(स्थिर atomic_t *v)
अणु
	वापस __atomic_पढ़ो(v);
पूर्ण
#घोषणा arch_atomic_पढ़ो arch_atomic_पढ़ो

अटल अंतरभूत व्योम arch_atomic_set(atomic_t *v, पूर्णांक i)
अणु
	__atomic_set(v, i);
पूर्ण
#घोषणा arch_atomic_set arch_atomic_set

अटल अंतरभूत पूर्णांक arch_atomic_add_वापस(पूर्णांक i, atomic_t *v)
अणु
	वापस __atomic_add_barrier(i, &v->counter) + i;
पूर्ण
#घोषणा arch_atomic_add_वापस arch_atomic_add_वापस

अटल अंतरभूत पूर्णांक arch_atomic_fetch_add(पूर्णांक i, atomic_t *v)
अणु
	वापस __atomic_add_barrier(i, &v->counter);
पूर्ण
#घोषणा arch_atomic_fetch_add arch_atomic_fetch_add

अटल अंतरभूत व्योम arch_atomic_add(पूर्णांक i, atomic_t *v)
अणु
	__atomic_add(i, &v->counter);
पूर्ण
#घोषणा arch_atomic_add arch_atomic_add

#घोषणा arch_atomic_sub(_i, _v)		arch_atomic_add(-(पूर्णांक)(_i), _v)
#घोषणा arch_atomic_sub_वापस(_i, _v)	arch_atomic_add_वापस(-(पूर्णांक)(_i), _v)
#घोषणा arch_atomic_fetch_sub(_i, _v)	arch_atomic_fetch_add(-(पूर्णांक)(_i), _v)

#घोषणा ATOMIC_OPS(op)							\
अटल अंतरभूत व्योम arch_atomic_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	__atomic_##op(i, &v->counter);					\
पूर्ण									\
अटल अंतरभूत पूर्णांक arch_atomic_fetch_##op(पूर्णांक i, atomic_t *v)		\
अणु									\
	वापस __atomic_##op##_barrier(i, &v->counter);			\
पूर्ण

ATOMIC_OPS(and)
ATOMIC_OPS(or)
ATOMIC_OPS(xor)

#अघोषित ATOMIC_OPS

#घोषणा arch_atomic_and			arch_atomic_and
#घोषणा arch_atomic_or			arch_atomic_or
#घोषणा arch_atomic_xor			arch_atomic_xor
#घोषणा arch_atomic_fetch_and		arch_atomic_fetch_and
#घोषणा arch_atomic_fetch_or		arch_atomic_fetch_or
#घोषणा arch_atomic_fetch_xor		arch_atomic_fetch_xor

#घोषणा arch_atomic_xchg(v, new)	(arch_xchg(&((v)->counter), new))

अटल अंतरभूत पूर्णांक arch_atomic_cmpxchg(atomic_t *v, पूर्णांक old, पूर्णांक new)
अणु
	वापस __atomic_cmpxchg(&v->counter, old, new);
पूर्ण
#घोषणा arch_atomic_cmpxchg arch_atomic_cmpxchg

#घोषणा ATOMIC64_INIT(i)  अणु (i) पूर्ण

अटल अंतरभूत s64 arch_atomic64_पढ़ो(स्थिर atomic64_t *v)
अणु
	वापस __atomic64_पढ़ो(v);
पूर्ण
#घोषणा arch_atomic64_पढ़ो arch_atomic64_पढ़ो

अटल अंतरभूत व्योम arch_atomic64_set(atomic64_t *v, s64 i)
अणु
	__atomic64_set(v, i);
पूर्ण
#घोषणा arch_atomic64_set arch_atomic64_set

अटल अंतरभूत s64 arch_atomic64_add_वापस(s64 i, atomic64_t *v)
अणु
	वापस __atomic64_add_barrier(i, (दीर्घ *)&v->counter) + i;
पूर्ण
#घोषणा arch_atomic64_add_वापस arch_atomic64_add_वापस

अटल अंतरभूत s64 arch_atomic64_fetch_add(s64 i, atomic64_t *v)
अणु
	वापस __atomic64_add_barrier(i, (दीर्घ *)&v->counter);
पूर्ण
#घोषणा arch_atomic64_fetch_add arch_atomic64_fetch_add

अटल अंतरभूत व्योम arch_atomic64_add(s64 i, atomic64_t *v)
अणु
	__atomic64_add(i, (दीर्घ *)&v->counter);
पूर्ण
#घोषणा arch_atomic64_add arch_atomic64_add

#घोषणा arch_atomic64_xchg(v, new)	(arch_xchg(&((v)->counter), new))

अटल अंतरभूत s64 arch_atomic64_cmpxchg(atomic64_t *v, s64 old, s64 new)
अणु
	वापस __atomic64_cmpxchg((दीर्घ *)&v->counter, old, new);
पूर्ण
#घोषणा arch_atomic64_cmpxchg arch_atomic64_cmpxchg

#घोषणा ATOMIC64_OPS(op)						\
अटल अंतरभूत व्योम arch_atomic64_##op(s64 i, atomic64_t *v)		\
अणु									\
	__atomic64_##op(i, (दीर्घ *)&v->counter);			\
पूर्ण									\
अटल अंतरभूत दीर्घ arch_atomic64_fetch_##op(s64 i, atomic64_t *v)	\
अणु									\
	वापस __atomic64_##op##_barrier(i, (दीर्घ *)&v->counter);	\
पूर्ण

ATOMIC64_OPS(and)
ATOMIC64_OPS(or)
ATOMIC64_OPS(xor)

#अघोषित ATOMIC64_OPS

#घोषणा arch_atomic64_and		arch_atomic64_and
#घोषणा arch_atomic64_or		arch_atomic64_or
#घोषणा arch_atomic64_xor		arch_atomic64_xor
#घोषणा arch_atomic64_fetch_and		arch_atomic64_fetch_and
#घोषणा arch_atomic64_fetch_or		arch_atomic64_fetch_or
#घोषणा arch_atomic64_fetch_xor		arch_atomic64_fetch_xor

#घोषणा arch_atomic64_sub_वापस(_i, _v) arch_atomic64_add_वापस(-(s64)(_i), _v)
#घोषणा arch_atomic64_fetch_sub(_i, _v)  arch_atomic64_fetch_add(-(s64)(_i), _v)
#घोषणा arch_atomic64_sub(_i, _v)	 arch_atomic64_add(-(s64)(_i), _v)

#घोषणा ARCH_ATOMIC

#पूर्ण_अगर /* __ARCH_S390_ATOMIC__  */
