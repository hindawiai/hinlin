<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_ATOMIC_H
#घोषणा _ASM_IA64_ATOMIC_H

/*
 * Atomic operations that C can't guarantee us.  Useful क्रम
 * resource counting etc..
 *
 * NOTE: करोn't mess with the types below!  The "unsigned long" and
 * "int" types were carefully placed so as to ensure proper operation
 * of the macros.
 *
 * Copyright (C) 1998, 1999, 2002-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */
#समावेश <linux/types.h>

#समावेश <यंत्र/पूर्णांकrinsics.h>
#समावेश <यंत्र/barrier.h>


#घोषणा ATOMIC64_INIT(i)	अणु (i) पूर्ण

#घोषणा atomic_पढ़ो(v)		READ_ONCE((v)->counter)
#घोषणा atomic64_पढ़ो(v)	READ_ONCE((v)->counter)

#घोषणा atomic_set(v,i)		WRITE_ONCE(((v)->counter), (i))
#घोषणा atomic64_set(v,i)	WRITE_ONCE(((v)->counter), (i))

#घोषणा ATOMIC_OP(op, c_op)						\
अटल __अंतरभूत__ पूर्णांक							\
ia64_atomic_##op (पूर्णांक i, atomic_t *v)					\
अणु									\
	__s32 old, new;							\
	CMPXCHG_BUGCHECK_DECL						\
									\
	करो अणु								\
		CMPXCHG_BUGCHECK(v);					\
		old = atomic_पढ़ो(v);					\
		new = old c_op i;					\
	पूर्ण जबतक (ia64_cmpxchg(acq, v, old, new, माप(atomic_t)) != old); \
	वापस new;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op, c_op)					\
अटल __अंतरभूत__ पूर्णांक							\
ia64_atomic_fetch_##op (पूर्णांक i, atomic_t *v)				\
अणु									\
	__s32 old, new;							\
	CMPXCHG_BUGCHECK_DECL						\
									\
	करो अणु								\
		CMPXCHG_BUGCHECK(v);					\
		old = atomic_पढ़ो(v);					\
		new = old c_op i;					\
	पूर्ण जबतक (ia64_cmpxchg(acq, v, old, new, माप(atomic_t)) != old); \
	वापस old;							\
पूर्ण

#घोषणा ATOMIC_OPS(op, c_op)						\
	ATOMIC_OP(op, c_op)						\
	ATOMIC_FETCH_OP(op, c_op)

ATOMIC_OPS(add, +)
ATOMIC_OPS(sub, -)

#अगर_घोषित __OPTIMIZE__
#घोषणा __ia64_atomic_स्थिर(i)						\
	अटल स्थिर पूर्णांक __ia64_atomic_p = __builtin_स्थिरant_p(i) ?	\
		((i) == 1 || (i) == 4 || (i) == 8 || (i) == 16 ||	\
		 (i) == -1 || (i) == -4 || (i) == -8 || (i) == -16) : 0;\
	__ia64_atomic_p
#अन्यथा
#घोषणा __ia64_atomic_स्थिर(i)	0
#पूर्ण_अगर

#घोषणा atomic_add_वापस(i,v)						\
(अणु									\
	पूर्णांक __ia64_aar_i = (i);						\
	__ia64_atomic_स्थिर(i)						\
		? ia64_fetch_and_add(__ia64_aar_i, &(v)->counter)	\
		: ia64_atomic_add(__ia64_aar_i, v);			\
पूर्ण)

#घोषणा atomic_sub_वापस(i,v)						\
(अणु									\
	पूर्णांक __ia64_asr_i = (i);						\
	__ia64_atomic_स्थिर(i)						\
		? ia64_fetch_and_add(-__ia64_asr_i, &(v)->counter)	\
		: ia64_atomic_sub(__ia64_asr_i, v);			\
पूर्ण)

#घोषणा atomic_fetch_add(i,v)						\
(अणु									\
	पूर्णांक __ia64_aar_i = (i);						\
	__ia64_atomic_स्थिर(i)						\
		? ia64_fetchadd(__ia64_aar_i, &(v)->counter, acq)	\
		: ia64_atomic_fetch_add(__ia64_aar_i, v);		\
पूर्ण)

#घोषणा atomic_fetch_sub(i,v)						\
(अणु									\
	पूर्णांक __ia64_asr_i = (i);						\
	__ia64_atomic_स्थिर(i)						\
		? ia64_fetchadd(-__ia64_asr_i, &(v)->counter, acq)	\
		: ia64_atomic_fetch_sub(__ia64_asr_i, v);		\
पूर्ण)

ATOMIC_FETCH_OP(and, &)
ATOMIC_FETCH_OP(or, |)
ATOMIC_FETCH_OP(xor, ^)

#घोषणा atomic_and(i,v)	(व्योम)ia64_atomic_fetch_and(i,v)
#घोषणा atomic_or(i,v)	(व्योम)ia64_atomic_fetch_or(i,v)
#घोषणा atomic_xor(i,v)	(व्योम)ia64_atomic_fetch_xor(i,v)

#घोषणा atomic_fetch_and(i,v)	ia64_atomic_fetch_and(i,v)
#घोषणा atomic_fetch_or(i,v)	ia64_atomic_fetch_or(i,v)
#घोषणा atomic_fetch_xor(i,v)	ia64_atomic_fetch_xor(i,v)

#अघोषित ATOMIC_OPS
#अघोषित ATOMIC_FETCH_OP
#अघोषित ATOMIC_OP

#घोषणा ATOMIC64_OP(op, c_op)						\
अटल __अंतरभूत__ s64							\
ia64_atomic64_##op (s64 i, atomic64_t *v)				\
अणु									\
	s64 old, new;							\
	CMPXCHG_BUGCHECK_DECL						\
									\
	करो अणु								\
		CMPXCHG_BUGCHECK(v);					\
		old = atomic64_पढ़ो(v);					\
		new = old c_op i;					\
	पूर्ण जबतक (ia64_cmpxchg(acq, v, old, new, माप(atomic64_t)) != old); \
	वापस new;							\
पूर्ण

#घोषणा ATOMIC64_FETCH_OP(op, c_op)					\
अटल __अंतरभूत__ s64							\
ia64_atomic64_fetch_##op (s64 i, atomic64_t *v)				\
अणु									\
	s64 old, new;							\
	CMPXCHG_BUGCHECK_DECL						\
									\
	करो अणु								\
		CMPXCHG_BUGCHECK(v);					\
		old = atomic64_पढ़ो(v);					\
		new = old c_op i;					\
	पूर्ण जबतक (ia64_cmpxchg(acq, v, old, new, माप(atomic64_t)) != old); \
	वापस old;							\
पूर्ण

#घोषणा ATOMIC64_OPS(op, c_op)						\
	ATOMIC64_OP(op, c_op)						\
	ATOMIC64_FETCH_OP(op, c_op)

ATOMIC64_OPS(add, +)
ATOMIC64_OPS(sub, -)

#घोषणा atomic64_add_वापस(i,v)					\
(अणु									\
	s64 __ia64_aar_i = (i);						\
	__ia64_atomic_स्थिर(i)						\
		? ia64_fetch_and_add(__ia64_aar_i, &(v)->counter)	\
		: ia64_atomic64_add(__ia64_aar_i, v);			\
पूर्ण)

#घोषणा atomic64_sub_वापस(i,v)					\
(अणु									\
	s64 __ia64_asr_i = (i);						\
	__ia64_atomic_स्थिर(i)						\
		? ia64_fetch_and_add(-__ia64_asr_i, &(v)->counter)	\
		: ia64_atomic64_sub(__ia64_asr_i, v);			\
पूर्ण)

#घोषणा atomic64_fetch_add(i,v)						\
(अणु									\
	s64 __ia64_aar_i = (i);						\
	__ia64_atomic_स्थिर(i)						\
		? ia64_fetchadd(__ia64_aar_i, &(v)->counter, acq)	\
		: ia64_atomic64_fetch_add(__ia64_aar_i, v);		\
पूर्ण)

#घोषणा atomic64_fetch_sub(i,v)						\
(अणु									\
	s64 __ia64_asr_i = (i);						\
	__ia64_atomic_स्थिर(i)						\
		? ia64_fetchadd(-__ia64_asr_i, &(v)->counter, acq)	\
		: ia64_atomic64_fetch_sub(__ia64_asr_i, v);		\
पूर्ण)

ATOMIC64_FETCH_OP(and, &)
ATOMIC64_FETCH_OP(or, |)
ATOMIC64_FETCH_OP(xor, ^)

#घोषणा atomic64_and(i,v)	(व्योम)ia64_atomic64_fetch_and(i,v)
#घोषणा atomic64_or(i,v)	(व्योम)ia64_atomic64_fetch_or(i,v)
#घोषणा atomic64_xor(i,v)	(व्योम)ia64_atomic64_fetch_xor(i,v)

#घोषणा atomic64_fetch_and(i,v)	ia64_atomic64_fetch_and(i,v)
#घोषणा atomic64_fetch_or(i,v)	ia64_atomic64_fetch_or(i,v)
#घोषणा atomic64_fetch_xor(i,v)	ia64_atomic64_fetch_xor(i,v)

#अघोषित ATOMIC64_OPS
#अघोषित ATOMIC64_FETCH_OP
#अघोषित ATOMIC64_OP

#घोषणा atomic_cmpxchg(v, old, new) (cmpxchg(&((v)->counter), old, new))
#घोषणा atomic_xchg(v, new) (xchg(&((v)->counter), new))

#घोषणा atomic64_cmpxchg(v, old, new) \
	(cmpxchg(&((v)->counter), old, new))
#घोषणा atomic64_xchg(v, new) (xchg(&((v)->counter), new))

#घोषणा atomic_add(i,v)			(व्योम)atomic_add_वापस((i), (v))
#घोषणा atomic_sub(i,v)			(व्योम)atomic_sub_वापस((i), (v))

#घोषणा atomic64_add(i,v)		(व्योम)atomic64_add_वापस((i), (v))
#घोषणा atomic64_sub(i,v)		(व्योम)atomic64_sub_वापस((i), (v))

#पूर्ण_अगर /* _ASM_IA64_ATOMIC_H */
