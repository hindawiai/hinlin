<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/atomic.h
 *
 * Copyright (C) 1996 Russell King.
 * Copyright (C) 2002 Deep Blue Solutions Ltd.
 * Copyright (C) 2012 ARM Ltd.
 */

#अगर_अघोषित __ASM_ATOMIC_LSE_H
#घोषणा __ASM_ATOMIC_LSE_H

#घोषणा ATOMIC_OP(op, यंत्र_op)						\
अटल अंतरभूत व्योम __lse_atomic_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	यंत्र अस्थिर(							\
	__LSE_PREAMBLE							\
"	" #यंत्र_op "	%w[i], %[v]\n"					\
	: [i] "+r" (i), [v] "+Q" (v->counter)				\
	: "r" (v));							\
पूर्ण

ATOMIC_OP(andnot, stclr)
ATOMIC_OP(or, stset)
ATOMIC_OP(xor, steor)
ATOMIC_OP(add, stadd)

#अघोषित ATOMIC_OP

#घोषणा ATOMIC_FETCH_OP(name, mb, op, यंत्र_op, cl...)			\
अटल अंतरभूत पूर्णांक __lse_atomic_fetch_##op##name(पूर्णांक i, atomic_t *v)	\
अणु									\
	यंत्र अस्थिर(							\
	__LSE_PREAMBLE							\
"	" #यंत्र_op #mb "	%w[i], %w[i], %[v]"				\
	: [i] "+r" (i), [v] "+Q" (v->counter)				\
	: "r" (v)							\
	: cl);								\
									\
	वापस i;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OPS(op, यंत्र_op)					\
	ATOMIC_FETCH_OP(_relaxed,   , op, यंत्र_op)			\
	ATOMIC_FETCH_OP(_acquire,  a, op, यंत्र_op, "memory")		\
	ATOMIC_FETCH_OP(_release,  l, op, यंत्र_op, "memory")		\
	ATOMIC_FETCH_OP(        , al, op, यंत्र_op, "memory")

ATOMIC_FETCH_OPS(andnot, ldclr)
ATOMIC_FETCH_OPS(or, ldset)
ATOMIC_FETCH_OPS(xor, ldeor)
ATOMIC_FETCH_OPS(add, ldadd)

#अघोषित ATOMIC_FETCH_OP
#अघोषित ATOMIC_FETCH_OPS

#घोषणा ATOMIC_OP_ADD_RETURN(name, mb, cl...)				\
अटल अंतरभूत पूर्णांक __lse_atomic_add_वापस##name(पूर्णांक i, atomic_t *v)	\
अणु									\
	u32 पंचांगp;							\
									\
	यंत्र अस्थिर(							\
	__LSE_PREAMBLE							\
	"	ldadd" #mb "	%w[i], %w[tmp], %[v]\n"			\
	"	add	%w[i], %w[i], %w[tmp]"				\
	: [i] "+r" (i), [v] "+Q" (v->counter), [पंचांगp] "=&r" (पंचांगp)	\
	: "r" (v)							\
	: cl);								\
									\
	वापस i;							\
पूर्ण

ATOMIC_OP_ADD_RETURN(_relaxed,   )
ATOMIC_OP_ADD_RETURN(_acquire,  a, "memory")
ATOMIC_OP_ADD_RETURN(_release,  l, "memory")
ATOMIC_OP_ADD_RETURN(        , al, "memory")

#अघोषित ATOMIC_OP_ADD_RETURN

अटल अंतरभूत व्योम __lse_atomic_and(पूर्णांक i, atomic_t *v)
अणु
	यंत्र अस्थिर(
	__LSE_PREAMBLE
	"	mvn	%w[i], %w[i]\n"
	"	stclr	%w[i], %[v]"
	: [i] "+&r" (i), [v] "+Q" (v->counter)
	: "r" (v));
पूर्ण

#घोषणा ATOMIC_FETCH_OP_AND(name, mb, cl...)				\
अटल अंतरभूत पूर्णांक __lse_atomic_fetch_and##name(पूर्णांक i, atomic_t *v)	\
अणु									\
	यंत्र अस्थिर(							\
	__LSE_PREAMBLE							\
	"	mvn	%w[i], %w[i]\n"					\
	"	ldclr" #mb "	%w[i], %w[i], %[v]"			\
	: [i] "+&r" (i), [v] "+Q" (v->counter)				\
	: "r" (v)							\
	: cl);								\
									\
	वापस i;							\
पूर्ण

ATOMIC_FETCH_OP_AND(_relaxed,   )
ATOMIC_FETCH_OP_AND(_acquire,  a, "memory")
ATOMIC_FETCH_OP_AND(_release,  l, "memory")
ATOMIC_FETCH_OP_AND(        , al, "memory")

#अघोषित ATOMIC_FETCH_OP_AND

अटल अंतरभूत व्योम __lse_atomic_sub(पूर्णांक i, atomic_t *v)
अणु
	यंत्र अस्थिर(
	__LSE_PREAMBLE
	"	neg	%w[i], %w[i]\n"
	"	stadd	%w[i], %[v]"
	: [i] "+&r" (i), [v] "+Q" (v->counter)
	: "r" (v));
पूर्ण

#घोषणा ATOMIC_OP_SUB_RETURN(name, mb, cl...)				\
अटल अंतरभूत पूर्णांक __lse_atomic_sub_वापस##name(पूर्णांक i, atomic_t *v)	\
अणु									\
	u32 पंचांगp;							\
									\
	यंत्र अस्थिर(							\
	__LSE_PREAMBLE							\
	"	neg	%w[i], %w[i]\n"					\
	"	ldadd" #mb "	%w[i], %w[tmp], %[v]\n"			\
	"	add	%w[i], %w[i], %w[tmp]"				\
	: [i] "+&r" (i), [v] "+Q" (v->counter), [पंचांगp] "=&r" (पंचांगp)	\
	: "r" (v)							\
	: cl);							\
									\
	वापस i;							\
पूर्ण

ATOMIC_OP_SUB_RETURN(_relaxed,   )
ATOMIC_OP_SUB_RETURN(_acquire,  a, "memory")
ATOMIC_OP_SUB_RETURN(_release,  l, "memory")
ATOMIC_OP_SUB_RETURN(        , al, "memory")

#अघोषित ATOMIC_OP_SUB_RETURN

#घोषणा ATOMIC_FETCH_OP_SUB(name, mb, cl...)				\
अटल अंतरभूत पूर्णांक __lse_atomic_fetch_sub##name(पूर्णांक i, atomic_t *v)	\
अणु									\
	यंत्र अस्थिर(							\
	__LSE_PREAMBLE							\
	"	neg	%w[i], %w[i]\n"					\
	"	ldadd" #mb "	%w[i], %w[i], %[v]"			\
	: [i] "+&r" (i), [v] "+Q" (v->counter)				\
	: "r" (v)							\
	: cl);								\
									\
	वापस i;							\
पूर्ण

ATOMIC_FETCH_OP_SUB(_relaxed,   )
ATOMIC_FETCH_OP_SUB(_acquire,  a, "memory")
ATOMIC_FETCH_OP_SUB(_release,  l, "memory")
ATOMIC_FETCH_OP_SUB(        , al, "memory")

#अघोषित ATOMIC_FETCH_OP_SUB

#घोषणा ATOMIC64_OP(op, यंत्र_op)						\
अटल अंतरभूत व्योम __lse_atomic64_##op(s64 i, atomic64_t *v)		\
अणु									\
	यंत्र अस्थिर(							\
	__LSE_PREAMBLE							\
"	" #यंत्र_op "	%[i], %[v]\n"					\
	: [i] "+r" (i), [v] "+Q" (v->counter)				\
	: "r" (v));							\
पूर्ण

ATOMIC64_OP(andnot, stclr)
ATOMIC64_OP(or, stset)
ATOMIC64_OP(xor, steor)
ATOMIC64_OP(add, stadd)

#अघोषित ATOMIC64_OP

#घोषणा ATOMIC64_FETCH_OP(name, mb, op, यंत्र_op, cl...)			\
अटल अंतरभूत दीर्घ __lse_atomic64_fetch_##op##name(s64 i, atomic64_t *v)\
अणु									\
	यंत्र अस्थिर(							\
	__LSE_PREAMBLE							\
"	" #यंत्र_op #mb "	%[i], %[i], %[v]"				\
	: [i] "+r" (i), [v] "+Q" (v->counter)				\
	: "r" (v)							\
	: cl);								\
									\
	वापस i;							\
पूर्ण

#घोषणा ATOMIC64_FETCH_OPS(op, यंत्र_op)					\
	ATOMIC64_FETCH_OP(_relaxed,   , op, यंत्र_op)			\
	ATOMIC64_FETCH_OP(_acquire,  a, op, यंत्र_op, "memory")		\
	ATOMIC64_FETCH_OP(_release,  l, op, यंत्र_op, "memory")		\
	ATOMIC64_FETCH_OP(        , al, op, यंत्र_op, "memory")

ATOMIC64_FETCH_OPS(andnot, ldclr)
ATOMIC64_FETCH_OPS(or, ldset)
ATOMIC64_FETCH_OPS(xor, ldeor)
ATOMIC64_FETCH_OPS(add, ldadd)

#अघोषित ATOMIC64_FETCH_OP
#अघोषित ATOMIC64_FETCH_OPS

#घोषणा ATOMIC64_OP_ADD_RETURN(name, mb, cl...)				\
अटल अंतरभूत दीर्घ __lse_atomic64_add_वापस##name(s64 i, atomic64_t *v)\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
									\
	यंत्र अस्थिर(							\
	__LSE_PREAMBLE							\
	"	ldadd" #mb "	%[i], %x[tmp], %[v]\n"			\
	"	add	%[i], %[i], %x[tmp]"				\
	: [i] "+r" (i), [v] "+Q" (v->counter), [पंचांगp] "=&r" (पंचांगp)	\
	: "r" (v)							\
	: cl);								\
									\
	वापस i;							\
पूर्ण

ATOMIC64_OP_ADD_RETURN(_relaxed,   )
ATOMIC64_OP_ADD_RETURN(_acquire,  a, "memory")
ATOMIC64_OP_ADD_RETURN(_release,  l, "memory")
ATOMIC64_OP_ADD_RETURN(        , al, "memory")

#अघोषित ATOMIC64_OP_ADD_RETURN

अटल अंतरभूत व्योम __lse_atomic64_and(s64 i, atomic64_t *v)
अणु
	यंत्र अस्थिर(
	__LSE_PREAMBLE
	"	mvn	%[i], %[i]\n"
	"	stclr	%[i], %[v]"
	: [i] "+&r" (i), [v] "+Q" (v->counter)
	: "r" (v));
पूर्ण

#घोषणा ATOMIC64_FETCH_OP_AND(name, mb, cl...)				\
अटल अंतरभूत दीर्घ __lse_atomic64_fetch_and##name(s64 i, atomic64_t *v)	\
अणु									\
	यंत्र अस्थिर(							\
	__LSE_PREAMBLE							\
	"	mvn	%[i], %[i]\n"					\
	"	ldclr" #mb "	%[i], %[i], %[v]"			\
	: [i] "+&r" (i), [v] "+Q" (v->counter)				\
	: "r" (v)							\
	: cl);								\
									\
	वापस i;							\
पूर्ण

ATOMIC64_FETCH_OP_AND(_relaxed,   )
ATOMIC64_FETCH_OP_AND(_acquire,  a, "memory")
ATOMIC64_FETCH_OP_AND(_release,  l, "memory")
ATOMIC64_FETCH_OP_AND(        , al, "memory")

#अघोषित ATOMIC64_FETCH_OP_AND

अटल अंतरभूत व्योम __lse_atomic64_sub(s64 i, atomic64_t *v)
अणु
	यंत्र अस्थिर(
	__LSE_PREAMBLE
	"	neg	%[i], %[i]\n"
	"	stadd	%[i], %[v]"
	: [i] "+&r" (i), [v] "+Q" (v->counter)
	: "r" (v));
पूर्ण

#घोषणा ATOMIC64_OP_SUB_RETURN(name, mb, cl...)				\
अटल अंतरभूत दीर्घ __lse_atomic64_sub_वापस##name(s64 i, atomic64_t *v)	\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
									\
	यंत्र अस्थिर(							\
	__LSE_PREAMBLE							\
	"	neg	%[i], %[i]\n"					\
	"	ldadd" #mb "	%[i], %x[tmp], %[v]\n"			\
	"	add	%[i], %[i], %x[tmp]"				\
	: [i] "+&r" (i), [v] "+Q" (v->counter), [पंचांगp] "=&r" (पंचांगp)	\
	: "r" (v)							\
	: cl);								\
									\
	वापस i;							\
पूर्ण

ATOMIC64_OP_SUB_RETURN(_relaxed,   )
ATOMIC64_OP_SUB_RETURN(_acquire,  a, "memory")
ATOMIC64_OP_SUB_RETURN(_release,  l, "memory")
ATOMIC64_OP_SUB_RETURN(        , al, "memory")

#अघोषित ATOMIC64_OP_SUB_RETURN

#घोषणा ATOMIC64_FETCH_OP_SUB(name, mb, cl...)				\
अटल अंतरभूत दीर्घ __lse_atomic64_fetch_sub##name(s64 i, atomic64_t *v)	\
अणु									\
	यंत्र अस्थिर(							\
	__LSE_PREAMBLE							\
	"	neg	%[i], %[i]\n"					\
	"	ldadd" #mb "	%[i], %[i], %[v]"			\
	: [i] "+&r" (i), [v] "+Q" (v->counter)				\
	: "r" (v)							\
	: cl);								\
									\
	वापस i;							\
पूर्ण

ATOMIC64_FETCH_OP_SUB(_relaxed,   )
ATOMIC64_FETCH_OP_SUB(_acquire,  a, "memory")
ATOMIC64_FETCH_OP_SUB(_release,  l, "memory")
ATOMIC64_FETCH_OP_SUB(        , al, "memory")

#अघोषित ATOMIC64_FETCH_OP_SUB

अटल अंतरभूत s64 __lse_atomic64_dec_अगर_positive(atomic64_t *v)
अणु
	अचिन्हित दीर्घ पंचांगp;

	यंत्र अस्थिर(
	__LSE_PREAMBLE
	"1:	ldr	%x[tmp], %[v]\n"
	"	subs	%[ret], %x[tmp], #1\n"
	"	b.lt	2f\n"
	"	casal	%x[tmp], %[ret], %[v]\n"
	"	sub	%x[tmp], %x[tmp], #1\n"
	"	sub	%x[tmp], %x[tmp], %[ret]\n"
	"	cbnz	%x[tmp], 1b\n"
	"2:"
	: [ret] "+&r" (v), [v] "+Q" (v->counter), [पंचांगp] "=&r" (पंचांगp)
	:
	: "cc", "memory");

	वापस (दीर्घ)v;
पूर्ण

#घोषणा __CMPXCHG_CASE(w, sfx, name, sz, mb, cl...)			\
अटल __always_अंतरभूत u##sz						\
__lse__cmpxchg_हाल_##name##sz(अस्थिर व्योम *ptr,			\
					      u##sz old,		\
					      u##sz new)		\
अणु									\
	रेजिस्टर अचिन्हित दीर्घ x0 यंत्र ("x0") = (अचिन्हित दीर्घ)ptr;	\
	रेजिस्टर u##sz x1 यंत्र ("x1") = old;				\
	रेजिस्टर u##sz x2 यंत्र ("x2") = new;				\
	अचिन्हित दीर्घ पंचांगp;						\
									\
	यंत्र अस्थिर(							\
	__LSE_PREAMBLE							\
	"	mov	%" #w "[tmp], %" #w "[old]\n"			\
	"	cas" #mb #sfx "\t%" #w "[tmp], %" #w "[new], %[v]\n"	\
	"	mov	%" #w "[ret], %" #w "[tmp]"			\
	: [ret] "+r" (x0), [v] "+Q" (*(अचिन्हित दीर्घ *)ptr),		\
	  [पंचांगp] "=&r" (पंचांगp)						\
	: [old] "r" (x1), [new] "r" (x2)				\
	: cl);								\
									\
	वापस x0;							\
पूर्ण

__CMPXCHG_CASE(w, b,     ,  8,   )
__CMPXCHG_CASE(w, h,     , 16,   )
__CMPXCHG_CASE(w,  ,     , 32,   )
__CMPXCHG_CASE(x,  ,     , 64,   )
__CMPXCHG_CASE(w, b, acq_,  8,  a, "memory")
__CMPXCHG_CASE(w, h, acq_, 16,  a, "memory")
__CMPXCHG_CASE(w,  , acq_, 32,  a, "memory")
__CMPXCHG_CASE(x,  , acq_, 64,  a, "memory")
__CMPXCHG_CASE(w, b, rel_,  8,  l, "memory")
__CMPXCHG_CASE(w, h, rel_, 16,  l, "memory")
__CMPXCHG_CASE(w,  , rel_, 32,  l, "memory")
__CMPXCHG_CASE(x,  , rel_, 64,  l, "memory")
__CMPXCHG_CASE(w, b,  mb_,  8, al, "memory")
__CMPXCHG_CASE(w, h,  mb_, 16, al, "memory")
__CMPXCHG_CASE(w,  ,  mb_, 32, al, "memory")
__CMPXCHG_CASE(x,  ,  mb_, 64, al, "memory")

#अघोषित __CMPXCHG_CASE

#घोषणा __CMPXCHG_DBL(name, mb, cl...)					\
अटल __always_अंतरभूत दीर्घ						\
__lse__cmpxchg_द्विगुन##name(अचिन्हित दीर्घ old1,				\
					 अचिन्हित दीर्घ old2,		\
					 अचिन्हित दीर्घ new1,		\
					 अचिन्हित दीर्घ new2,		\
					 अस्थिर व्योम *ptr)		\
अणु									\
	अचिन्हित दीर्घ oldval1 = old1;					\
	अचिन्हित दीर्घ oldval2 = old2;					\
	रेजिस्टर अचिन्हित दीर्घ x0 यंत्र ("x0") = old1;			\
	रेजिस्टर अचिन्हित दीर्घ x1 यंत्र ("x1") = old2;			\
	रेजिस्टर अचिन्हित दीर्घ x2 यंत्र ("x2") = new1;			\
	रेजिस्टर अचिन्हित दीर्घ x3 यंत्र ("x3") = new2;			\
	रेजिस्टर अचिन्हित दीर्घ x4 यंत्र ("x4") = (अचिन्हित दीर्घ)ptr;	\
									\
	यंत्र अस्थिर(							\
	__LSE_PREAMBLE							\
	"	casp" #mb "\t%[old1], %[old2], %[new1], %[new2], %[v]\n"\
	"	eor	%[old1], %[old1], %[oldval1]\n"			\
	"	eor	%[old2], %[old2], %[oldval2]\n"			\
	"	orr	%[old1], %[old1], %[old2]"			\
	: [old1] "+&r" (x0), [old2] "+&r" (x1),				\
	  [v] "+Q" (*(अचिन्हित दीर्घ *)ptr)				\
	: [new1] "r" (x2), [new2] "r" (x3), [ptr] "r" (x4),		\
	  [oldval1] "r" (oldval1), [oldval2] "r" (oldval2)		\
	: cl);								\
									\
	वापस x0;							\
पूर्ण

__CMPXCHG_DBL(   ,   )
__CMPXCHG_DBL(_mb, al, "memory")

#अघोषित __CMPXCHG_DBL

#पूर्ण_अगर	/* __ASM_ATOMIC_LSE_H */
