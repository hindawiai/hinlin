<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/atomic.h
 *
 * Copyright (C) 1996 Russell King.
 * Copyright (C) 2002 Deep Blue Solutions Ltd.
 * Copyright (C) 2012 ARM Ltd.
 */

#अगर_अघोषित __ASM_ATOMIC_LL_SC_H
#घोषणा __ASM_ATOMIC_LL_SC_H

#समावेश <linux/stringअगरy.h>

#अगर_घोषित CONFIG_ARM64_LSE_ATOMICS
#घोषणा __LL_SC_FALLBACK(यंत्र_ops)					\
"	b	3f\n"							\
"	.subsection	1\n"						\
"3:\n"									\
यंत्र_ops "\n"								\
"	b	4f\n"							\
"	.previous\n"							\
"4:\n"
#अन्यथा
#घोषणा __LL_SC_FALLBACK(यंत्र_ops) यंत्र_ops
#पूर्ण_अगर

#अगर_अघोषित CONFIG_CC_HAS_K_CONSTRAINT
#घोषणा K
#पूर्ण_अगर

/*
 * AArch64 UP and SMP safe atomic ops.  We use load exclusive and
 * store exclusive to ensure that these are atomic.  We may loop
 * to ensure that the update happens.
 */

#घोषणा ATOMIC_OP(op, यंत्र_op, स्थिरraपूर्णांक)				\
अटल अंतरभूत व्योम							\
__ll_sc_atomic_##op(पूर्णांक i, atomic_t *v)					\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
	पूर्णांक result;							\
									\
	यंत्र अस्थिर("// atomic_" #op "\n"				\
	__LL_SC_FALLBACK(						\
"	prfm	pstl1strm, %2\n"					\
"1:	ldxr	%w0, %2\n"						\
"	" #यंत्र_op "	%w0, %w0, %w3\n"				\
"	stxr	%w1, %w0, %2\n"						\
"	cbnz	%w1, 1b\n")						\
	: "=&r" (result), "=&r" (पंचांगp), "+Q" (v->counter)		\
	: __stringअगरy(स्थिरraपूर्णांक) "r" (i));				\
पूर्ण

#घोषणा ATOMIC_OP_RETURN(name, mb, acq, rel, cl, op, यंत्र_op, स्थिरraपूर्णांक)\
अटल अंतरभूत पूर्णांक							\
__ll_sc_atomic_##op##_वापस##name(पूर्णांक i, atomic_t *v)			\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
	पूर्णांक result;							\
									\
	यंत्र अस्थिर("// atomic_" #op "_return" #name "\n"		\
	__LL_SC_FALLBACK(						\
"	prfm	pstl1strm, %2\n"					\
"1:	ld" #acq "xr	%w0, %2\n"					\
"	" #यंत्र_op "	%w0, %w0, %w3\n"				\
"	st" #rel "xr	%w1, %w0, %2\n"					\
"	cbnz	%w1, 1b\n"						\
"	" #mb )								\
	: "=&r" (result), "=&r" (पंचांगp), "+Q" (v->counter)		\
	: __stringअगरy(स्थिरraपूर्णांक) "r" (i)				\
	: cl);								\
									\
	वापस result;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(name, mb, acq, rel, cl, op, यंत्र_op, स्थिरraपूर्णांक) \
अटल अंतरभूत पूर्णांक							\
__ll_sc_atomic_fetch_##op##name(पूर्णांक i, atomic_t *v)			\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
	पूर्णांक val, result;						\
									\
	यंत्र अस्थिर("// atomic_fetch_" #op #name "\n"			\
	__LL_SC_FALLBACK(						\
"	prfm	pstl1strm, %3\n"					\
"1:	ld" #acq "xr	%w0, %3\n"					\
"	" #यंत्र_op "	%w1, %w0, %w4\n"				\
"	st" #rel "xr	%w2, %w1, %3\n"					\
"	cbnz	%w2, 1b\n"						\
"	" #mb )								\
	: "=&r" (result), "=&r" (val), "=&r" (पंचांगp), "+Q" (v->counter)	\
	: __stringअगरy(स्थिरraपूर्णांक) "r" (i)				\
	: cl);								\
									\
	वापस result;							\
पूर्ण

#घोषणा ATOMIC_OPS(...)							\
	ATOMIC_OP(__VA_ARGS__)						\
	ATOMIC_OP_RETURN(        , dmb ish,  , l, "memory", __VA_ARGS__)\
	ATOMIC_OP_RETURN(_relaxed,        ,  ,  ,         , __VA_ARGS__)\
	ATOMIC_OP_RETURN(_acquire,        , a,  , "memory", __VA_ARGS__)\
	ATOMIC_OP_RETURN(_release,        ,  , l, "memory", __VA_ARGS__)\
	ATOMIC_FETCH_OP (        , dmb ish,  , l, "memory", __VA_ARGS__)\
	ATOMIC_FETCH_OP (_relaxed,        ,  ,  ,         , __VA_ARGS__)\
	ATOMIC_FETCH_OP (_acquire,        , a,  , "memory", __VA_ARGS__)\
	ATOMIC_FETCH_OP (_release,        ,  , l, "memory", __VA_ARGS__)

ATOMIC_OPS(add, add, I)
ATOMIC_OPS(sub, sub, J)

#अघोषित ATOMIC_OPS
#घोषणा ATOMIC_OPS(...)							\
	ATOMIC_OP(__VA_ARGS__)						\
	ATOMIC_FETCH_OP (        , dmb ish,  , l, "memory", __VA_ARGS__)\
	ATOMIC_FETCH_OP (_relaxed,        ,  ,  ,         , __VA_ARGS__)\
	ATOMIC_FETCH_OP (_acquire,        , a,  , "memory", __VA_ARGS__)\
	ATOMIC_FETCH_OP (_release,        ,  , l, "memory", __VA_ARGS__)

ATOMIC_OPS(and, and, K)
ATOMIC_OPS(or, orr, K)
ATOMIC_OPS(xor, eor, K)
/*
 * GAS converts the mysterious and unकरोcumented BIC (immediate) alias to
 * an AND (immediate) inकाष्ठाion with the immediate inverted. We करोn't
 * have a स्थिरraपूर्णांक क्रम this, so fall back to रेजिस्टर.
 */
ATOMIC_OPS(andnot, bic, )

#अघोषित ATOMIC_OPS
#अघोषित ATOMIC_FETCH_OP
#अघोषित ATOMIC_OP_RETURN
#अघोषित ATOMIC_OP

#घोषणा ATOMIC64_OP(op, यंत्र_op, स्थिरraपूर्णांक)				\
अटल अंतरभूत व्योम							\
__ll_sc_atomic64_##op(s64 i, atomic64_t *v)				\
अणु									\
	s64 result;							\
	अचिन्हित दीर्घ पंचांगp;						\
									\
	यंत्र अस्थिर("// atomic64_" #op "\n"				\
	__LL_SC_FALLBACK(						\
"	prfm	pstl1strm, %2\n"					\
"1:	ldxr	%0, %2\n"						\
"	" #यंत्र_op "	%0, %0, %3\n"					\
"	stxr	%w1, %0, %2\n"						\
"	cbnz	%w1, 1b")						\
	: "=&r" (result), "=&r" (पंचांगp), "+Q" (v->counter)		\
	: __stringअगरy(स्थिरraपूर्णांक) "r" (i));				\
पूर्ण

#घोषणा ATOMIC64_OP_RETURN(name, mb, acq, rel, cl, op, यंत्र_op, स्थिरraपूर्णांक)\
अटल अंतरभूत दीर्घ							\
__ll_sc_atomic64_##op##_वापस##name(s64 i, atomic64_t *v)		\
अणु									\
	s64 result;							\
	अचिन्हित दीर्घ पंचांगp;						\
									\
	यंत्र अस्थिर("// atomic64_" #op "_return" #name "\n"		\
	__LL_SC_FALLBACK(						\
"	prfm	pstl1strm, %2\n"					\
"1:	ld" #acq "xr	%0, %2\n"					\
"	" #यंत्र_op "	%0, %0, %3\n"					\
"	st" #rel "xr	%w1, %0, %2\n"					\
"	cbnz	%w1, 1b\n"						\
"	" #mb )								\
	: "=&r" (result), "=&r" (पंचांगp), "+Q" (v->counter)		\
	: __stringअगरy(स्थिरraपूर्णांक) "r" (i)				\
	: cl);								\
									\
	वापस result;							\
पूर्ण

#घोषणा ATOMIC64_FETCH_OP(name, mb, acq, rel, cl, op, यंत्र_op, स्थिरraपूर्णांक)\
अटल अंतरभूत दीर्घ							\
__ll_sc_atomic64_fetch_##op##name(s64 i, atomic64_t *v)		\
अणु									\
	s64 result, val;						\
	अचिन्हित दीर्घ पंचांगp;						\
									\
	यंत्र अस्थिर("// atomic64_fetch_" #op #name "\n"		\
	__LL_SC_FALLBACK(						\
"	prfm	pstl1strm, %3\n"					\
"1:	ld" #acq "xr	%0, %3\n"					\
"	" #यंत्र_op "	%1, %0, %4\n"					\
"	st" #rel "xr	%w2, %1, %3\n"					\
"	cbnz	%w2, 1b\n"						\
"	" #mb )								\
	: "=&r" (result), "=&r" (val), "=&r" (पंचांगp), "+Q" (v->counter)	\
	: __stringअगरy(स्थिरraपूर्णांक) "r" (i)				\
	: cl);								\
									\
	वापस result;							\
पूर्ण

#घोषणा ATOMIC64_OPS(...)						\
	ATOMIC64_OP(__VA_ARGS__)					\
	ATOMIC64_OP_RETURN(, dmb ish,  , l, "memory", __VA_ARGS__)	\
	ATOMIC64_OP_RETURN(_relaxed,,  ,  ,         , __VA_ARGS__)	\
	ATOMIC64_OP_RETURN(_acquire,, a,  , "memory", __VA_ARGS__)	\
	ATOMIC64_OP_RETURN(_release,,  , l, "memory", __VA_ARGS__)	\
	ATOMIC64_FETCH_OP (, dmb ish,  , l, "memory", __VA_ARGS__)	\
	ATOMIC64_FETCH_OP (_relaxed,,  ,  ,         , __VA_ARGS__)	\
	ATOMIC64_FETCH_OP (_acquire,, a,  , "memory", __VA_ARGS__)	\
	ATOMIC64_FETCH_OP (_release,,  , l, "memory", __VA_ARGS__)

ATOMIC64_OPS(add, add, I)
ATOMIC64_OPS(sub, sub, J)

#अघोषित ATOMIC64_OPS
#घोषणा ATOMIC64_OPS(...)						\
	ATOMIC64_OP(__VA_ARGS__)					\
	ATOMIC64_FETCH_OP (, dmb ish,  , l, "memory", __VA_ARGS__)	\
	ATOMIC64_FETCH_OP (_relaxed,,  ,  ,         , __VA_ARGS__)	\
	ATOMIC64_FETCH_OP (_acquire,, a,  , "memory", __VA_ARGS__)	\
	ATOMIC64_FETCH_OP (_release,,  , l, "memory", __VA_ARGS__)

ATOMIC64_OPS(and, and, L)
ATOMIC64_OPS(or, orr, L)
ATOMIC64_OPS(xor, eor, L)
/*
 * GAS converts the mysterious and unकरोcumented BIC (immediate) alias to
 * an AND (immediate) inकाष्ठाion with the immediate inverted. We करोn't
 * have a स्थिरraपूर्णांक क्रम this, so fall back to रेजिस्टर.
 */
ATOMIC64_OPS(andnot, bic, )

#अघोषित ATOMIC64_OPS
#अघोषित ATOMIC64_FETCH_OP
#अघोषित ATOMIC64_OP_RETURN
#अघोषित ATOMIC64_OP

अटल अंतरभूत s64
__ll_sc_atomic64_dec_अगर_positive(atomic64_t *v)
अणु
	s64 result;
	अचिन्हित दीर्घ पंचांगp;

	यंत्र अस्थिर("// atomic64_dec_if_positive\n"
	__LL_SC_FALLBACK(
"	prfm	pstl1strm, %2\n"
"1:	ldxr	%0, %2\n"
"	subs	%0, %0, #1\n"
"	b.lt	2f\n"
"	stlxr	%w1, %0, %2\n"
"	cbnz	%w1, 1b\n"
"	dmb	ish\n"
"2:")
	: "=&r" (result), "=&r" (पंचांगp), "+Q" (v->counter)
	:
	: "cc", "memory");

	वापस result;
पूर्ण

#घोषणा __CMPXCHG_CASE(w, sfx, name, sz, mb, acq, rel, cl, स्थिरraपूर्णांक)	\
अटल अंतरभूत u##sz							\
__ll_sc__cmpxchg_हाल_##name##sz(अस्थिर व्योम *ptr,			\
					 अचिन्हित दीर्घ old,		\
					 u##sz new)			\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
	u##sz oldval;							\
									\
	/*								\
	 * Sub-word sizes require explicit casting so that the compare  \
	 * part of the cmpxchg करोesn't end up पूर्णांकerpreting non-zero	\
	 * upper bits of the रेजिस्टर containing "old".			\
	 */								\
	अगर (sz < 32)							\
		old = (u##sz)old;					\
									\
	यंत्र अस्थिर(							\
	__LL_SC_FALLBACK(						\
	"	prfm	pstl1strm, %[v]\n"				\
	"1:	ld" #acq "xr" #sfx "\t%" #w "[oldval], %[v]\n"		\
	"	eor	%" #w "[tmp], %" #w "[oldval], %" #w "[old]\n"	\
	"	cbnz	%" #w "[tmp], 2f\n"				\
	"	st" #rel "xr" #sfx "\t%w[tmp], %" #w "[new], %[v]\n"	\
	"	cbnz	%w[tmp], 1b\n"					\
	"	" #mb "\n"						\
	"2:")								\
	: [पंचांगp] "=&r" (पंचांगp), [oldval] "=&r" (oldval),			\
	  [v] "+Q" (*(u##sz *)ptr)					\
	: [old] __stringअगरy(स्थिरraपूर्णांक) "r" (old), [new] "r" (new)	\
	: cl);								\
									\
	वापस oldval;							\
पूर्ण

/*
 * Earlier versions of GCC (no later than 8.1.0) appear to incorrectly
 * handle the 'K' स्थिरraपूर्णांक क्रम the value 4294967295 - thus we use no
 * स्थिरraपूर्णांक क्रम 32 bit operations.
 */
__CMPXCHG_CASE(w, b,     ,  8,        ,  ,  ,         , K)
__CMPXCHG_CASE(w, h,     , 16,        ,  ,  ,         , K)
__CMPXCHG_CASE(w,  ,     , 32,        ,  ,  ,         , K)
__CMPXCHG_CASE( ,  ,     , 64,        ,  ,  ,         , L)
__CMPXCHG_CASE(w, b, acq_,  8,        , a,  , "memory", K)
__CMPXCHG_CASE(w, h, acq_, 16,        , a,  , "memory", K)
__CMPXCHG_CASE(w,  , acq_, 32,        , a,  , "memory", K)
__CMPXCHG_CASE( ,  , acq_, 64,        , a,  , "memory", L)
__CMPXCHG_CASE(w, b, rel_,  8,        ,  , l, "memory", K)
__CMPXCHG_CASE(w, h, rel_, 16,        ,  , l, "memory", K)
__CMPXCHG_CASE(w,  , rel_, 32,        ,  , l, "memory", K)
__CMPXCHG_CASE( ,  , rel_, 64,        ,  , l, "memory", L)
__CMPXCHG_CASE(w, b,  mb_,  8, dmb ish,  , l, "memory", K)
__CMPXCHG_CASE(w, h,  mb_, 16, dmb ish,  , l, "memory", K)
__CMPXCHG_CASE(w,  ,  mb_, 32, dmb ish,  , l, "memory", K)
__CMPXCHG_CASE( ,  ,  mb_, 64, dmb ish,  , l, "memory", L)

#अघोषित __CMPXCHG_CASE

#घोषणा __CMPXCHG_DBL(name, mb, rel, cl)				\
अटल अंतरभूत दीर्घ							\
__ll_sc__cmpxchg_द्विगुन##name(अचिन्हित दीर्घ old1,			\
				      अचिन्हित दीर्घ old2,		\
				      अचिन्हित दीर्घ new1,		\
				      अचिन्हित दीर्घ new2,		\
				      अस्थिर व्योम *ptr)		\
अणु									\
	अचिन्हित दीर्घ पंचांगp, ret;						\
									\
	यंत्र अस्थिर("// __cmpxchg_double" #name "\n"			\
	__LL_SC_FALLBACK(						\
	"	prfm	pstl1strm, %2\n"				\
	"1:	ldxp	%0, %1, %2\n"					\
	"	eor	%0, %0, %3\n"					\
	"	eor	%1, %1, %4\n"					\
	"	orr	%1, %0, %1\n"					\
	"	cbnz	%1, 2f\n"					\
	"	st" #rel "xp	%w0, %5, %6, %2\n"			\
	"	cbnz	%w0, 1b\n"					\
	"	" #mb "\n"						\
	"2:")								\
	: "=&r" (पंचांगp), "=&r" (ret), "+Q" (*(अचिन्हित दीर्घ *)ptr)	\
	: "r" (old1), "r" (old2), "r" (new1), "r" (new2)		\
	: cl);								\
									\
	वापस ret;							\
पूर्ण

__CMPXCHG_DBL(   ,        ,  ,         )
__CMPXCHG_DBL(_mb, dmb ish, l, "memory")

#अघोषित __CMPXCHG_DBL
#अघोषित K

#पूर्ण_अगर	/* __ASM_ATOMIC_LL_SC_H */
