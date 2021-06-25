<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 * Copyright (C) 2017 SiFive
 */

#अगर_अघोषित _ASM_RISCV_ATOMIC_H
#घोषणा _ASM_RISCV_ATOMIC_H

#अगर_घोषित CONFIG_GENERIC_ATOMIC64
# include <यंत्र-generic/atomic64.h>
#अन्यथा
# अगर (__riscv_xlen < 64)
#  error "64-bit atomics require XLEN to be at least 64"
# endअगर
#पूर्ण_अगर

#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/barrier.h>

#घोषणा __atomic_acquire_fence()					\
	__यंत्र__ __अस्थिर__(RISCV_ACQUIRE_BARRIER "" ::: "memory")

#घोषणा __atomic_release_fence()					\
	__यंत्र__ __अस्थिर__(RISCV_RELEASE_BARRIER "" ::: "memory");

अटल __always_अंतरभूत पूर्णांक atomic_पढ़ो(स्थिर atomic_t *v)
अणु
	वापस READ_ONCE(v->counter);
पूर्ण
अटल __always_अंतरभूत व्योम atomic_set(atomic_t *v, पूर्णांक i)
अणु
	WRITE_ONCE(v->counter, i);
पूर्ण

#अगर_अघोषित CONFIG_GENERIC_ATOMIC64
#घोषणा ATOMIC64_INIT(i) अणु (i) पूर्ण
अटल __always_अंतरभूत s64 atomic64_पढ़ो(स्थिर atomic64_t *v)
अणु
	वापस READ_ONCE(v->counter);
पूर्ण
अटल __always_अंतरभूत व्योम atomic64_set(atomic64_t *v, s64 i)
अणु
	WRITE_ONCE(v->counter, i);
पूर्ण
#पूर्ण_अगर

/*
 * First, the atomic ops that have no ordering स्थिरraपूर्णांकs and thereक्रम करोn't
 * have the AQ or RL bits set.  These करोn't return anything, so there's only
 * one version to worry about.
 */
#घोषणा ATOMIC_OP(op, यंत्र_op, I, यंत्र_type, c_type, prefix)		\
अटल __always_अंतरभूत							\
व्योम atomic##prefix##_##op(c_type i, atomic##prefix##_t *v)		\
अणु									\
	__यंत्र__ __अस्थिर__ (						\
		"	amo" #यंत्र_op "." #यंत्र_type " zero, %1, %0"	\
		: "+A" (v->counter)					\
		: "r" (I)						\
		: "memory");						\
पूर्ण									\

#अगर_घोषित CONFIG_GENERIC_ATOMIC64
#घोषणा ATOMIC_OPS(op, यंत्र_op, I)					\
        ATOMIC_OP (op, यंत्र_op, I, w, पूर्णांक,   )
#अन्यथा
#घोषणा ATOMIC_OPS(op, यंत्र_op, I)					\
        ATOMIC_OP (op, यंत्र_op, I, w, पूर्णांक,   )				\
        ATOMIC_OP (op, यंत्र_op, I, d, s64, 64)
#पूर्ण_अगर

ATOMIC_OPS(add, add,  i)
ATOMIC_OPS(sub, add, -i)
ATOMIC_OPS(and, and,  i)
ATOMIC_OPS( or,  or,  i)
ATOMIC_OPS(xor, xor,  i)

#अघोषित ATOMIC_OP
#अघोषित ATOMIC_OPS

/*
 * Atomic ops that have ordered, relaxed, acquire, and release variants.
 * There's two flavors of these: the arithmatic ops have both fetch and वापस
 * versions, जबतक the logical ops only have fetch versions.
 */
#घोषणा ATOMIC_FETCH_OP(op, यंत्र_op, I, यंत्र_type, c_type, prefix)	\
अटल __always_अंतरभूत							\
c_type atomic##prefix##_fetch_##op##_relaxed(c_type i,			\
					     atomic##prefix##_t *v)	\
अणु									\
	रेजिस्टर c_type ret;						\
	__यंत्र__ __अस्थिर__ (						\
		"	amo" #यंत्र_op "." #यंत्र_type " %1, %2, %0"	\
		: "+A" (v->counter), "=r" (ret)				\
		: "r" (I)						\
		: "memory");						\
	वापस ret;							\
पूर्ण									\
अटल __always_अंतरभूत							\
c_type atomic##prefix##_fetch_##op(c_type i, atomic##prefix##_t *v)	\
अणु									\
	रेजिस्टर c_type ret;						\
	__यंत्र__ __अस्थिर__ (						\
		"	amo" #यंत्र_op "." #यंत्र_type ".aqrl  %1, %2, %0"	\
		: "+A" (v->counter), "=r" (ret)				\
		: "r" (I)						\
		: "memory");						\
	वापस ret;							\
पूर्ण

#घोषणा ATOMIC_OP_RETURN(op, यंत्र_op, c_op, I, यंत्र_type, c_type, prefix)	\
अटल __always_अंतरभूत							\
c_type atomic##prefix##_##op##_वापस_relaxed(c_type i,			\
					      atomic##prefix##_t *v)	\
अणु									\
        वापस atomic##prefix##_fetch_##op##_relaxed(i, v) c_op I;	\
पूर्ण									\
अटल __always_अंतरभूत							\
c_type atomic##prefix##_##op##_वापस(c_type i, atomic##prefix##_t *v)	\
अणु									\
        वापस atomic##prefix##_fetch_##op(i, v) c_op I;		\
पूर्ण

#अगर_घोषित CONFIG_GENERIC_ATOMIC64
#घोषणा ATOMIC_OPS(op, यंत्र_op, c_op, I)					\
        ATOMIC_FETCH_OP( op, यंत्र_op,       I, w, पूर्णांक,   )		\
        ATOMIC_OP_RETURN(op, यंत्र_op, c_op, I, w, पूर्णांक,   )
#अन्यथा
#घोषणा ATOMIC_OPS(op, यंत्र_op, c_op, I)					\
        ATOMIC_FETCH_OP( op, यंत्र_op,       I, w, पूर्णांक,   )		\
        ATOMIC_OP_RETURN(op, यंत्र_op, c_op, I, w, पूर्णांक,   )		\
        ATOMIC_FETCH_OP( op, यंत्र_op,       I, d, s64, 64)		\
        ATOMIC_OP_RETURN(op, यंत्र_op, c_op, I, d, s64, 64)
#पूर्ण_अगर

ATOMIC_OPS(add, add, +,  i)
ATOMIC_OPS(sub, add, +, -i)

#घोषणा atomic_add_वापस_relaxed	atomic_add_वापस_relaxed
#घोषणा atomic_sub_वापस_relaxed	atomic_sub_वापस_relaxed
#घोषणा atomic_add_वापस		atomic_add_वापस
#घोषणा atomic_sub_वापस		atomic_sub_वापस

#घोषणा atomic_fetch_add_relaxed	atomic_fetch_add_relaxed
#घोषणा atomic_fetch_sub_relaxed	atomic_fetch_sub_relaxed
#घोषणा atomic_fetch_add		atomic_fetch_add
#घोषणा atomic_fetch_sub		atomic_fetch_sub

#अगर_अघोषित CONFIG_GENERIC_ATOMIC64
#घोषणा atomic64_add_वापस_relaxed	atomic64_add_वापस_relaxed
#घोषणा atomic64_sub_वापस_relaxed	atomic64_sub_वापस_relaxed
#घोषणा atomic64_add_वापस		atomic64_add_वापस
#घोषणा atomic64_sub_वापस		atomic64_sub_वापस

#घोषणा atomic64_fetch_add_relaxed	atomic64_fetch_add_relaxed
#घोषणा atomic64_fetch_sub_relaxed	atomic64_fetch_sub_relaxed
#घोषणा atomic64_fetch_add		atomic64_fetch_add
#घोषणा atomic64_fetch_sub		atomic64_fetch_sub
#पूर्ण_अगर

#अघोषित ATOMIC_OPS

#अगर_घोषित CONFIG_GENERIC_ATOMIC64
#घोषणा ATOMIC_OPS(op, यंत्र_op, I)					\
        ATOMIC_FETCH_OP(op, यंत्र_op, I, w, पूर्णांक,   )
#अन्यथा
#घोषणा ATOMIC_OPS(op, यंत्र_op, I)					\
        ATOMIC_FETCH_OP(op, यंत्र_op, I, w, पूर्णांक,   )			\
        ATOMIC_FETCH_OP(op, यंत्र_op, I, d, s64, 64)
#पूर्ण_अगर

ATOMIC_OPS(and, and, i)
ATOMIC_OPS( or,  or, i)
ATOMIC_OPS(xor, xor, i)

#घोषणा atomic_fetch_and_relaxed	atomic_fetch_and_relaxed
#घोषणा atomic_fetch_or_relaxed		atomic_fetch_or_relaxed
#घोषणा atomic_fetch_xor_relaxed	atomic_fetch_xor_relaxed
#घोषणा atomic_fetch_and		atomic_fetch_and
#घोषणा atomic_fetch_or			atomic_fetch_or
#घोषणा atomic_fetch_xor		atomic_fetch_xor

#अगर_अघोषित CONFIG_GENERIC_ATOMIC64
#घोषणा atomic64_fetch_and_relaxed	atomic64_fetch_and_relaxed
#घोषणा atomic64_fetch_or_relaxed	atomic64_fetch_or_relaxed
#घोषणा atomic64_fetch_xor_relaxed	atomic64_fetch_xor_relaxed
#घोषणा atomic64_fetch_and		atomic64_fetch_and
#घोषणा atomic64_fetch_or		atomic64_fetch_or
#घोषणा atomic64_fetch_xor		atomic64_fetch_xor
#पूर्ण_अगर

#अघोषित ATOMIC_OPS

#अघोषित ATOMIC_FETCH_OP
#अघोषित ATOMIC_OP_RETURN

/* This is required to provide a full barrier on success. */
अटल __always_अंतरभूत पूर्णांक atomic_fetch_add_unless(atomic_t *v, पूर्णांक a, पूर्णांक u)
अणु
       पूर्णांक prev, rc;

	__यंत्र__ __अस्थिर__ (
		"0:	lr.w     %[p],  %[c]\n"
		"	beq      %[p],  %[u], 1f\n"
		"	add      %[rc], %[p], %[a]\n"
		"	sc.w.rl  %[rc], %[rc], %[c]\n"
		"	bnez     %[rc], 0b\n"
		"	fence    rw, rw\n"
		"1:\n"
		: [p]"=&r" (prev), [rc]"=&r" (rc), [c]"+A" (v->counter)
		: [a]"r" (a), [u]"r" (u)
		: "memory");
	वापस prev;
पूर्ण
#घोषणा atomic_fetch_add_unless atomic_fetch_add_unless

#अगर_अघोषित CONFIG_GENERIC_ATOMIC64
अटल __always_अंतरभूत s64 atomic64_fetch_add_unless(atomic64_t *v, s64 a, s64 u)
अणु
       s64 prev;
       दीर्घ rc;

	__यंत्र__ __अस्थिर__ (
		"0:	lr.d     %[p],  %[c]\n"
		"	beq      %[p],  %[u], 1f\n"
		"	add      %[rc], %[p], %[a]\n"
		"	sc.d.rl  %[rc], %[rc], %[c]\n"
		"	bnez     %[rc], 0b\n"
		"	fence    rw, rw\n"
		"1:\n"
		: [p]"=&r" (prev), [rc]"=&r" (rc), [c]"+A" (v->counter)
		: [a]"r" (a), [u]"r" (u)
		: "memory");
	वापस prev;
पूर्ण
#घोषणा atomic64_fetch_add_unless atomic64_fetch_add_unless
#पूर्ण_अगर

/*
 * atomic_अणुcmp,पूर्णxchg is required to have exactly the same ordering semantics as
 * अणुcmp,पूर्णxchg and the operations that वापस, so they need a full barrier.
 */
#घोषणा ATOMIC_OP(c_t, prefix, size)					\
अटल __always_अंतरभूत							\
c_t atomic##prefix##_xchg_relaxed(atomic##prefix##_t *v, c_t n)		\
अणु									\
	वापस __xchg_relaxed(&(v->counter), n, size);			\
पूर्ण									\
अटल __always_अंतरभूत							\
c_t atomic##prefix##_xchg_acquire(atomic##prefix##_t *v, c_t n)		\
अणु									\
	वापस __xchg_acquire(&(v->counter), n, size);			\
पूर्ण									\
अटल __always_अंतरभूत							\
c_t atomic##prefix##_xchg_release(atomic##prefix##_t *v, c_t n)		\
अणु									\
	वापस __xchg_release(&(v->counter), n, size);			\
पूर्ण									\
अटल __always_अंतरभूत							\
c_t atomic##prefix##_xchg(atomic##prefix##_t *v, c_t n)			\
अणु									\
	वापस __xchg(&(v->counter), n, size);				\
पूर्ण									\
अटल __always_अंतरभूत							\
c_t atomic##prefix##_cmpxchg_relaxed(atomic##prefix##_t *v,		\
				     c_t o, c_t n)			\
अणु									\
	वापस __cmpxchg_relaxed(&(v->counter), o, n, size);		\
पूर्ण									\
अटल __always_अंतरभूत							\
c_t atomic##prefix##_cmpxchg_acquire(atomic##prefix##_t *v,		\
				     c_t o, c_t n)			\
अणु									\
	वापस __cmpxchg_acquire(&(v->counter), o, n, size);		\
पूर्ण									\
अटल __always_अंतरभूत							\
c_t atomic##prefix##_cmpxchg_release(atomic##prefix##_t *v,		\
				     c_t o, c_t n)			\
अणु									\
	वापस __cmpxchg_release(&(v->counter), o, n, size);		\
पूर्ण									\
अटल __always_अंतरभूत							\
c_t atomic##prefix##_cmpxchg(atomic##prefix##_t *v, c_t o, c_t n)	\
अणु									\
	वापस __cmpxchg(&(v->counter), o, n, size);			\
पूर्ण

#अगर_घोषित CONFIG_GENERIC_ATOMIC64
#घोषणा ATOMIC_OPS()							\
	ATOMIC_OP(पूर्णांक,   , 4)
#अन्यथा
#घोषणा ATOMIC_OPS()							\
	ATOMIC_OP(पूर्णांक,   , 4)						\
	ATOMIC_OP(s64, 64, 8)
#पूर्ण_अगर

ATOMIC_OPS()

#घोषणा atomic_xchg_relaxed atomic_xchg_relaxed
#घोषणा atomic_xchg_acquire atomic_xchg_acquire
#घोषणा atomic_xchg_release atomic_xchg_release
#घोषणा atomic_xchg atomic_xchg
#घोषणा atomic_cmpxchg_relaxed atomic_cmpxchg_relaxed
#घोषणा atomic_cmpxchg_acquire atomic_cmpxchg_acquire
#घोषणा atomic_cmpxchg_release atomic_cmpxchg_release
#घोषणा atomic_cmpxchg atomic_cmpxchg

#अघोषित ATOMIC_OPS
#अघोषित ATOMIC_OP

अटल __always_अंतरभूत पूर्णांक atomic_sub_अगर_positive(atomic_t *v, पूर्णांक offset)
अणु
       पूर्णांक prev, rc;

	__यंत्र__ __अस्थिर__ (
		"0:	lr.w     %[p],  %[c]\n"
		"	sub      %[rc], %[p], %[o]\n"
		"	bltz     %[rc], 1f\n"
		"	sc.w.rl  %[rc], %[rc], %[c]\n"
		"	bnez     %[rc], 0b\n"
		"	fence    rw, rw\n"
		"1:\n"
		: [p]"=&r" (prev), [rc]"=&r" (rc), [c]"+A" (v->counter)
		: [o]"r" (offset)
		: "memory");
	वापस prev - offset;
पूर्ण

#घोषणा atomic_dec_अगर_positive(v)	atomic_sub_अगर_positive(v, 1)

#अगर_अघोषित CONFIG_GENERIC_ATOMIC64
अटल __always_अंतरभूत s64 atomic64_sub_अगर_positive(atomic64_t *v, s64 offset)
अणु
       s64 prev;
       दीर्घ rc;

	__यंत्र__ __अस्थिर__ (
		"0:	lr.d     %[p],  %[c]\n"
		"	sub      %[rc], %[p], %[o]\n"
		"	bltz     %[rc], 1f\n"
		"	sc.d.rl  %[rc], %[rc], %[c]\n"
		"	bnez     %[rc], 0b\n"
		"	fence    rw, rw\n"
		"1:\n"
		: [p]"=&r" (prev), [rc]"=&r" (rc), [c]"+A" (v->counter)
		: [o]"r" (offset)
		: "memory");
	वापस prev - offset;
पूर्ण

#घोषणा atomic64_dec_अगर_positive(v)	atomic64_sub_अगर_positive(v, 1)
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_RISCV_ATOMIC_H */
