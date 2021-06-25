<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/atomic.h
 *
 * Copyright (C) 1996 Russell King.
 * Copyright (C) 2002 Deep Blue Solutions Ltd.
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_ATOMIC_H
#घोषणा __ASM_ATOMIC_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/lse.h>

#घोषणा ATOMIC_OP(op)							\
अटल __always_अंतरभूत व्योम arch_##op(पूर्णांक i, atomic_t *v)		\
अणु									\
	__lse_ll_sc_body(op, i, v);					\
पूर्ण

ATOMIC_OP(atomic_andnot)
ATOMIC_OP(atomic_or)
ATOMIC_OP(atomic_xor)
ATOMIC_OP(atomic_add)
ATOMIC_OP(atomic_and)
ATOMIC_OP(atomic_sub)

#अघोषित ATOMIC_OP

#घोषणा ATOMIC_FETCH_OP(name, op)					\
अटल __always_अंतरभूत पूर्णांक arch_##op##name(पूर्णांक i, atomic_t *v)		\
अणु									\
	वापस __lse_ll_sc_body(op##name, i, v);			\
पूर्ण

#घोषणा ATOMIC_FETCH_OPS(op)						\
	ATOMIC_FETCH_OP(_relaxed, op)					\
	ATOMIC_FETCH_OP(_acquire, op)					\
	ATOMIC_FETCH_OP(_release, op)					\
	ATOMIC_FETCH_OP(        , op)

ATOMIC_FETCH_OPS(atomic_fetch_andnot)
ATOMIC_FETCH_OPS(atomic_fetch_or)
ATOMIC_FETCH_OPS(atomic_fetch_xor)
ATOMIC_FETCH_OPS(atomic_fetch_add)
ATOMIC_FETCH_OPS(atomic_fetch_and)
ATOMIC_FETCH_OPS(atomic_fetch_sub)
ATOMIC_FETCH_OPS(atomic_add_वापस)
ATOMIC_FETCH_OPS(atomic_sub_वापस)

#अघोषित ATOMIC_FETCH_OP
#अघोषित ATOMIC_FETCH_OPS

#घोषणा ATOMIC64_OP(op)							\
अटल __always_अंतरभूत व्योम arch_##op(दीर्घ i, atomic64_t *v)		\
अणु									\
	__lse_ll_sc_body(op, i, v);					\
पूर्ण

ATOMIC64_OP(atomic64_andnot)
ATOMIC64_OP(atomic64_or)
ATOMIC64_OP(atomic64_xor)
ATOMIC64_OP(atomic64_add)
ATOMIC64_OP(atomic64_and)
ATOMIC64_OP(atomic64_sub)

#अघोषित ATOMIC64_OP

#घोषणा ATOMIC64_FETCH_OP(name, op)					\
अटल __always_अंतरभूत दीर्घ arch_##op##name(दीर्घ i, atomic64_t *v)	\
अणु									\
	वापस __lse_ll_sc_body(op##name, i, v);			\
पूर्ण

#घोषणा ATOMIC64_FETCH_OPS(op)						\
	ATOMIC64_FETCH_OP(_relaxed, op)					\
	ATOMIC64_FETCH_OP(_acquire, op)					\
	ATOMIC64_FETCH_OP(_release, op)					\
	ATOMIC64_FETCH_OP(        , op)

ATOMIC64_FETCH_OPS(atomic64_fetch_andnot)
ATOMIC64_FETCH_OPS(atomic64_fetch_or)
ATOMIC64_FETCH_OPS(atomic64_fetch_xor)
ATOMIC64_FETCH_OPS(atomic64_fetch_add)
ATOMIC64_FETCH_OPS(atomic64_fetch_and)
ATOMIC64_FETCH_OPS(atomic64_fetch_sub)
ATOMIC64_FETCH_OPS(atomic64_add_वापस)
ATOMIC64_FETCH_OPS(atomic64_sub_वापस)

#अघोषित ATOMIC64_FETCH_OP
#अघोषित ATOMIC64_FETCH_OPS

अटल __always_अंतरभूत दीर्घ arch_atomic64_dec_अगर_positive(atomic64_t *v)
अणु
	वापस __lse_ll_sc_body(atomic64_dec_अगर_positive, v);
पूर्ण

#घोषणा arch_atomic_पढ़ो(v)			__READ_ONCE((v)->counter)
#घोषणा arch_atomic_set(v, i)			__WRITE_ONCE(((v)->counter), (i))

#घोषणा arch_atomic_add_वापस_relaxed		arch_atomic_add_वापस_relaxed
#घोषणा arch_atomic_add_वापस_acquire		arch_atomic_add_वापस_acquire
#घोषणा arch_atomic_add_वापस_release		arch_atomic_add_वापस_release
#घोषणा arch_atomic_add_वापस			arch_atomic_add_वापस

#घोषणा arch_atomic_sub_वापस_relaxed		arch_atomic_sub_वापस_relaxed
#घोषणा arch_atomic_sub_वापस_acquire		arch_atomic_sub_वापस_acquire
#घोषणा arch_atomic_sub_वापस_release		arch_atomic_sub_वापस_release
#घोषणा arch_atomic_sub_वापस			arch_atomic_sub_वापस

#घोषणा arch_atomic_fetch_add_relaxed		arch_atomic_fetch_add_relaxed
#घोषणा arch_atomic_fetch_add_acquire		arch_atomic_fetch_add_acquire
#घोषणा arch_atomic_fetch_add_release		arch_atomic_fetch_add_release
#घोषणा arch_atomic_fetch_add			arch_atomic_fetch_add

#घोषणा arch_atomic_fetch_sub_relaxed		arch_atomic_fetch_sub_relaxed
#घोषणा arch_atomic_fetch_sub_acquire		arch_atomic_fetch_sub_acquire
#घोषणा arch_atomic_fetch_sub_release		arch_atomic_fetch_sub_release
#घोषणा arch_atomic_fetch_sub			arch_atomic_fetch_sub

#घोषणा arch_atomic_fetch_and_relaxed		arch_atomic_fetch_and_relaxed
#घोषणा arch_atomic_fetch_and_acquire		arch_atomic_fetch_and_acquire
#घोषणा arch_atomic_fetch_and_release		arch_atomic_fetch_and_release
#घोषणा arch_atomic_fetch_and			arch_atomic_fetch_and

#घोषणा arch_atomic_fetch_andnot_relaxed	arch_atomic_fetch_andnot_relaxed
#घोषणा arch_atomic_fetch_andnot_acquire	arch_atomic_fetch_andnot_acquire
#घोषणा arch_atomic_fetch_andnot_release	arch_atomic_fetch_andnot_release
#घोषणा arch_atomic_fetch_andnot		arch_atomic_fetch_andnot

#घोषणा arch_atomic_fetch_or_relaxed		arch_atomic_fetch_or_relaxed
#घोषणा arch_atomic_fetch_or_acquire		arch_atomic_fetch_or_acquire
#घोषणा arch_atomic_fetch_or_release		arch_atomic_fetch_or_release
#घोषणा arch_atomic_fetch_or			arch_atomic_fetch_or

#घोषणा arch_atomic_fetch_xor_relaxed		arch_atomic_fetch_xor_relaxed
#घोषणा arch_atomic_fetch_xor_acquire		arch_atomic_fetch_xor_acquire
#घोषणा arch_atomic_fetch_xor_release		arch_atomic_fetch_xor_release
#घोषणा arch_atomic_fetch_xor			arch_atomic_fetch_xor

#घोषणा arch_atomic_xchg_relaxed(v, new) \
	arch_xchg_relaxed(&((v)->counter), (new))
#घोषणा arch_atomic_xchg_acquire(v, new) \
	arch_xchg_acquire(&((v)->counter), (new))
#घोषणा arch_atomic_xchg_release(v, new) \
	arch_xchg_release(&((v)->counter), (new))
#घोषणा arch_atomic_xchg(v, new) \
	arch_xchg(&((v)->counter), (new))

#घोषणा arch_atomic_cmpxchg_relaxed(v, old, new) \
	arch_cmpxchg_relaxed(&((v)->counter), (old), (new))
#घोषणा arch_atomic_cmpxchg_acquire(v, old, new) \
	arch_cmpxchg_acquire(&((v)->counter), (old), (new))
#घोषणा arch_atomic_cmpxchg_release(v, old, new) \
	arch_cmpxchg_release(&((v)->counter), (old), (new))
#घोषणा arch_atomic_cmpxchg(v, old, new) \
	arch_cmpxchg(&((v)->counter), (old), (new))

#घोषणा arch_atomic_andnot			arch_atomic_andnot

/*
 * 64-bit arch_atomic operations.
 */
#घोषणा ATOMIC64_INIT				ATOMIC_INIT
#घोषणा arch_atomic64_पढ़ो			arch_atomic_पढ़ो
#घोषणा arch_atomic64_set			arch_atomic_set

#घोषणा arch_atomic64_add_वापस_relaxed	arch_atomic64_add_वापस_relaxed
#घोषणा arch_atomic64_add_वापस_acquire	arch_atomic64_add_वापस_acquire
#घोषणा arch_atomic64_add_वापस_release	arch_atomic64_add_वापस_release
#घोषणा arch_atomic64_add_वापस		arch_atomic64_add_वापस

#घोषणा arch_atomic64_sub_वापस_relaxed	arch_atomic64_sub_वापस_relaxed
#घोषणा arch_atomic64_sub_वापस_acquire	arch_atomic64_sub_वापस_acquire
#घोषणा arch_atomic64_sub_वापस_release	arch_atomic64_sub_वापस_release
#घोषणा arch_atomic64_sub_वापस		arch_atomic64_sub_वापस

#घोषणा arch_atomic64_fetch_add_relaxed		arch_atomic64_fetch_add_relaxed
#घोषणा arch_atomic64_fetch_add_acquire		arch_atomic64_fetch_add_acquire
#घोषणा arch_atomic64_fetch_add_release		arch_atomic64_fetch_add_release
#घोषणा arch_atomic64_fetch_add			arch_atomic64_fetch_add

#घोषणा arch_atomic64_fetch_sub_relaxed		arch_atomic64_fetch_sub_relaxed
#घोषणा arch_atomic64_fetch_sub_acquire		arch_atomic64_fetch_sub_acquire
#घोषणा arch_atomic64_fetch_sub_release		arch_atomic64_fetch_sub_release
#घोषणा arch_atomic64_fetch_sub			arch_atomic64_fetch_sub

#घोषणा arch_atomic64_fetch_and_relaxed		arch_atomic64_fetch_and_relaxed
#घोषणा arch_atomic64_fetch_and_acquire		arch_atomic64_fetch_and_acquire
#घोषणा arch_atomic64_fetch_and_release		arch_atomic64_fetch_and_release
#घोषणा arch_atomic64_fetch_and			arch_atomic64_fetch_and

#घोषणा arch_atomic64_fetch_andnot_relaxed	arch_atomic64_fetch_andnot_relaxed
#घोषणा arch_atomic64_fetch_andnot_acquire	arch_atomic64_fetch_andnot_acquire
#घोषणा arch_atomic64_fetch_andnot_release	arch_atomic64_fetch_andnot_release
#घोषणा arch_atomic64_fetch_andnot		arch_atomic64_fetch_andnot

#घोषणा arch_atomic64_fetch_or_relaxed		arch_atomic64_fetch_or_relaxed
#घोषणा arch_atomic64_fetch_or_acquire		arch_atomic64_fetch_or_acquire
#घोषणा arch_atomic64_fetch_or_release		arch_atomic64_fetch_or_release
#घोषणा arch_atomic64_fetch_or			arch_atomic64_fetch_or

#घोषणा arch_atomic64_fetch_xor_relaxed		arch_atomic64_fetch_xor_relaxed
#घोषणा arch_atomic64_fetch_xor_acquire		arch_atomic64_fetch_xor_acquire
#घोषणा arch_atomic64_fetch_xor_release		arch_atomic64_fetch_xor_release
#घोषणा arch_atomic64_fetch_xor			arch_atomic64_fetch_xor

#घोषणा arch_atomic64_xchg_relaxed		arch_atomic_xchg_relaxed
#घोषणा arch_atomic64_xchg_acquire		arch_atomic_xchg_acquire
#घोषणा arch_atomic64_xchg_release		arch_atomic_xchg_release
#घोषणा arch_atomic64_xchg			arch_atomic_xchg

#घोषणा arch_atomic64_cmpxchg_relaxed		arch_atomic_cmpxchg_relaxed
#घोषणा arch_atomic64_cmpxchg_acquire		arch_atomic_cmpxchg_acquire
#घोषणा arch_atomic64_cmpxchg_release		arch_atomic_cmpxchg_release
#घोषणा arch_atomic64_cmpxchg			arch_atomic_cmpxchg

#घोषणा arch_atomic64_andnot			arch_atomic64_andnot

#घोषणा arch_atomic64_dec_अगर_positive		arch_atomic64_dec_अगर_positive

#घोषणा ARCH_ATOMIC

#पूर्ण_अगर /* __ASM_ATOMIC_H */
