<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/cmpxchg.h
 *
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_CMPXCHG_H
#घोषणा __ASM_CMPXCHG_H

#समावेश <linux/build_bug.h>
#समावेश <linux/compiler.h>

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/lse.h>

/*
 * We need separate acquire parameters क्रम ll/sc and lse, since the full
 * barrier हाल is generated as release+dmb क्रम the क्रमmer and
 * acquire+release क्रम the latter.
 */
#घोषणा __XCHG_CASE(w, sfx, name, sz, mb, nop_lse, acq, acq_lse, rel, cl)	\
अटल अंतरभूत u##sz __xchg_हाल_##name##sz(u##sz x, अस्थिर व्योम *ptr)		\
अणु										\
	u##sz ret;								\
	अचिन्हित दीर्घ पंचांगp;							\
										\
	यंत्र अस्थिर(ARM64_LSE_ATOMIC_INSN(					\
	/* LL/SC */								\
	"	prfm	pstl1strm, %2\n"					\
	"1:	ld" #acq "xr" #sfx "\t%" #w "0, %2\n"				\
	"	st" #rel "xr" #sfx "\t%w1, %" #w "3, %2\n"			\
	"	cbnz	%w1, 1b\n"						\
	"	" #mb,								\
	/* LSE atomics */							\
	"	swp" #acq_lse #rel #sfx "\t%" #w "3, %" #w "0, %2\n"		\
		__nops(3)							\
	"	" #nop_lse)							\
	: "=&r" (ret), "=&r" (पंचांगp), "+Q" (*(u##sz *)ptr)			\
	: "r" (x)								\
	: cl);									\
										\
	वापस ret;								\
पूर्ण

__XCHG_CASE(w, b,     ,  8,        ,    ,  ,  ,  ,         )
__XCHG_CASE(w, h,     , 16,        ,    ,  ,  ,  ,         )
__XCHG_CASE(w,  ,     , 32,        ,    ,  ,  ,  ,         )
__XCHG_CASE( ,  ,     , 64,        ,    ,  ,  ,  ,         )
__XCHG_CASE(w, b, acq_,  8,        ,    , a, a,  , "memory")
__XCHG_CASE(w, h, acq_, 16,        ,    , a, a,  , "memory")
__XCHG_CASE(w,  , acq_, 32,        ,    , a, a,  , "memory")
__XCHG_CASE( ,  , acq_, 64,        ,    , a, a,  , "memory")
__XCHG_CASE(w, b, rel_,  8,        ,    ,  ,  , l, "memory")
__XCHG_CASE(w, h, rel_, 16,        ,    ,  ,  , l, "memory")
__XCHG_CASE(w,  , rel_, 32,        ,    ,  ,  , l, "memory")
__XCHG_CASE( ,  , rel_, 64,        ,    ,  ,  , l, "memory")
__XCHG_CASE(w, b,  mb_,  8, dmb ish, nop,  , a, l, "memory")
__XCHG_CASE(w, h,  mb_, 16, dmb ish, nop,  , a, l, "memory")
__XCHG_CASE(w,  ,  mb_, 32, dmb ish, nop,  , a, l, "memory")
__XCHG_CASE( ,  ,  mb_, 64, dmb ish, nop,  , a, l, "memory")

#अघोषित __XCHG_CASE

#घोषणा __XCHG_GEN(sfx)							\
अटल __always_अंतरभूत  अचिन्हित दीर्घ __xchg##sfx(अचिन्हित दीर्घ x,	\
					अस्थिर व्योम *ptr,		\
					पूर्णांक size)			\
अणु									\
	चयन (size) अणु							\
	हाल 1:								\
		वापस __xchg_हाल##sfx##_8(x, ptr);			\
	हाल 2:								\
		वापस __xchg_हाल##sfx##_16(x, ptr);			\
	हाल 4:								\
		वापस __xchg_हाल##sfx##_32(x, ptr);			\
	हाल 8:								\
		वापस __xchg_हाल##sfx##_64(x, ptr);			\
	शेष:							\
		BUILD_BUG();						\
	पूर्ण								\
									\
	unreachable();							\
पूर्ण

__XCHG_GEN()
__XCHG_GEN(_acq)
__XCHG_GEN(_rel)
__XCHG_GEN(_mb)

#अघोषित __XCHG_GEN

#घोषणा __xchg_wrapper(sfx, ptr, x)					\
(अणु									\
	__typeof__(*(ptr)) __ret;					\
	__ret = (__typeof__(*(ptr)))					\
		__xchg##sfx((अचिन्हित दीर्घ)(x), (ptr), माप(*(ptr))); \
	__ret;								\
पूर्ण)

/* xchg */
#घोषणा arch_xchg_relaxed(...)	__xchg_wrapper(    , __VA_ARGS__)
#घोषणा arch_xchg_acquire(...)	__xchg_wrapper(_acq, __VA_ARGS__)
#घोषणा arch_xchg_release(...)	__xchg_wrapper(_rel, __VA_ARGS__)
#घोषणा arch_xchg(...)		__xchg_wrapper( _mb, __VA_ARGS__)

#घोषणा __CMPXCHG_CASE(name, sz)			\
अटल अंतरभूत u##sz __cmpxchg_हाल_##name##sz(अस्थिर व्योम *ptr,	\
					      u##sz old,		\
					      u##sz new)		\
अणु									\
	वापस __lse_ll_sc_body(_cmpxchg_हाल_##name##sz,		\
				ptr, old, new);				\
पूर्ण

__CMPXCHG_CASE(    ,  8)
__CMPXCHG_CASE(    , 16)
__CMPXCHG_CASE(    , 32)
__CMPXCHG_CASE(    , 64)
__CMPXCHG_CASE(acq_,  8)
__CMPXCHG_CASE(acq_, 16)
__CMPXCHG_CASE(acq_, 32)
__CMPXCHG_CASE(acq_, 64)
__CMPXCHG_CASE(rel_,  8)
__CMPXCHG_CASE(rel_, 16)
__CMPXCHG_CASE(rel_, 32)
__CMPXCHG_CASE(rel_, 64)
__CMPXCHG_CASE(mb_,  8)
__CMPXCHG_CASE(mb_, 16)
__CMPXCHG_CASE(mb_, 32)
__CMPXCHG_CASE(mb_, 64)

#अघोषित __CMPXCHG_CASE

#घोषणा __CMPXCHG_DBL(name)						\
अटल अंतरभूत दीर्घ __cmpxchg_द्विगुन##name(अचिन्हित दीर्घ old1,		\
					 अचिन्हित दीर्घ old2,		\
					 अचिन्हित दीर्घ new1,		\
					 अचिन्हित दीर्घ new2,		\
					 अस्थिर व्योम *ptr)		\
अणु									\
	वापस __lse_ll_sc_body(_cmpxchg_द्विगुन##name, 			\
				old1, old2, new1, new2, ptr);		\
पूर्ण

__CMPXCHG_DBL(   )
__CMPXCHG_DBL(_mb)

#अघोषित __CMPXCHG_DBL

#घोषणा __CMPXCHG_GEN(sfx)						\
अटल __always_अंतरभूत अचिन्हित दीर्घ __cmpxchg##sfx(अस्थिर व्योम *ptr,	\
					   अचिन्हित दीर्घ old,		\
					   अचिन्हित दीर्घ new,		\
					   पूर्णांक size)			\
अणु									\
	चयन (size) अणु							\
	हाल 1:								\
		वापस __cmpxchg_हाल##sfx##_8(ptr, old, new);		\
	हाल 2:								\
		वापस __cmpxchg_हाल##sfx##_16(ptr, old, new);		\
	हाल 4:								\
		वापस __cmpxchg_हाल##sfx##_32(ptr, old, new);		\
	हाल 8:								\
		वापस __cmpxchg_हाल##sfx##_64(ptr, old, new);		\
	शेष:							\
		BUILD_BUG();						\
	पूर्ण								\
									\
	unreachable();							\
पूर्ण

__CMPXCHG_GEN()
__CMPXCHG_GEN(_acq)
__CMPXCHG_GEN(_rel)
__CMPXCHG_GEN(_mb)

#अघोषित __CMPXCHG_GEN

#घोषणा __cmpxchg_wrapper(sfx, ptr, o, n)				\
(अणु									\
	__typeof__(*(ptr)) __ret;					\
	__ret = (__typeof__(*(ptr)))					\
		__cmpxchg##sfx((ptr), (अचिन्हित दीर्घ)(o),		\
				(अचिन्हित दीर्घ)(n), माप(*(ptr)));	\
	__ret;								\
पूर्ण)

/* cmpxchg */
#घोषणा arch_cmpxchg_relaxed(...)	__cmpxchg_wrapper(    , __VA_ARGS__)
#घोषणा arch_cmpxchg_acquire(...)	__cmpxchg_wrapper(_acq, __VA_ARGS__)
#घोषणा arch_cmpxchg_release(...)	__cmpxchg_wrapper(_rel, __VA_ARGS__)
#घोषणा arch_cmpxchg(...)		__cmpxchg_wrapper( _mb, __VA_ARGS__)
#घोषणा arch_cmpxchg_local		arch_cmpxchg_relaxed

/* cmpxchg64 */
#घोषणा arch_cmpxchg64_relaxed		arch_cmpxchg_relaxed
#घोषणा arch_cmpxchg64_acquire		arch_cmpxchg_acquire
#घोषणा arch_cmpxchg64_release		arch_cmpxchg_release
#घोषणा arch_cmpxchg64			arch_cmpxchg
#घोषणा arch_cmpxchg64_local		arch_cmpxchg_local

/* cmpxchg_द्विगुन */
#घोषणा प्रणाली_has_cmpxchg_द्विगुन()     1

#घोषणा __cmpxchg_द्विगुन_check(ptr1, ptr2)					\
(अणु										\
	अगर (माप(*(ptr1)) != 8)						\
		BUILD_BUG();							\
	VM_BUG_ON((अचिन्हित दीर्घ *)(ptr2) - (अचिन्हित दीर्घ *)(ptr1) != 1);	\
पूर्ण)

#घोषणा arch_cmpxchg_द्विगुन(ptr1, ptr2, o1, o2, n1, n2)				\
(अणु										\
	पूर्णांक __ret;								\
	__cmpxchg_द्विगुन_check(ptr1, ptr2);					\
	__ret = !__cmpxchg_द्विगुन_mb((अचिन्हित दीर्घ)(o1), (अचिन्हित दीर्घ)(o2),	\
				     (अचिन्हित दीर्घ)(n1), (अचिन्हित दीर्घ)(n2),	\
				     ptr1);					\
	__ret;									\
पूर्ण)

#घोषणा arch_cmpxchg_द्विगुन_local(ptr1, ptr2, o1, o2, n1, n2)			\
(अणु										\
	पूर्णांक __ret;								\
	__cmpxchg_द्विगुन_check(ptr1, ptr2);					\
	__ret = !__cmpxchg_द्विगुन((अचिन्हित दीर्घ)(o1), (अचिन्हित दीर्घ)(o2),	\
				  (अचिन्हित दीर्घ)(n1), (अचिन्हित दीर्घ)(n2),	\
				  ptr1);					\
	__ret;									\
पूर्ण)

#घोषणा __CMPWAIT_CASE(w, sfx, sz)					\
अटल अंतरभूत व्योम __cmpरुको_हाल_##sz(अस्थिर व्योम *ptr,		\
				       अचिन्हित दीर्घ val)		\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
									\
	यंत्र अस्थिर(							\
	"	sevl\n"							\
	"	wfe\n"							\
	"	ldxr" #sfx "\t%" #w "[tmp], %[v]\n"			\
	"	eor	%" #w "[tmp], %" #w "[tmp], %" #w "[val]\n"	\
	"	cbnz	%" #w "[tmp], 1f\n"				\
	"	wfe\n"							\
	"1:"								\
	: [पंचांगp] "=&r" (पंचांगp), [v] "+Q" (*(अचिन्हित दीर्घ *)ptr)		\
	: [val] "r" (val));						\
पूर्ण

__CMPWAIT_CASE(w, b, 8);
__CMPWAIT_CASE(w, h, 16);
__CMPWAIT_CASE(w,  , 32);
__CMPWAIT_CASE( ,  , 64);

#अघोषित __CMPWAIT_CASE

#घोषणा __CMPWAIT_GEN(sfx)						\
अटल __always_अंतरभूत व्योम __cmpरुको##sfx(अस्थिर व्योम *ptr,		\
				  अचिन्हित दीर्घ val,			\
				  पूर्णांक size)				\
अणु									\
	चयन (size) अणु							\
	हाल 1:								\
		वापस __cmpरुको_हाल##sfx##_8(ptr, (u8)val);		\
	हाल 2:								\
		वापस __cmpरुको_हाल##sfx##_16(ptr, (u16)val);		\
	हाल 4:								\
		वापस __cmpरुको_हाल##sfx##_32(ptr, val);		\
	हाल 8:								\
		वापस __cmpरुको_हाल##sfx##_64(ptr, val);		\
	शेष:							\
		BUILD_BUG();						\
	पूर्ण								\
									\
	unreachable();							\
पूर्ण

__CMPWAIT_GEN()

#अघोषित __CMPWAIT_GEN

#घोषणा __cmpरुको_relaxed(ptr, val) \
	__cmpरुको((ptr), (अचिन्हित दीर्घ)(val), माप(*(ptr)))

#पूर्ण_अगर	/* __ASM_CMPXCHG_H */
