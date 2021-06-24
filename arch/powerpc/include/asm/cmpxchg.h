<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_CMPXCHG_H_
#घोषणा _ASM_POWERPC_CMPXCHG_H_

#अगर_घोषित __KERNEL__
#समावेश <linux/compiler.h>
#समावेश <यंत्र/synch.h>
#समावेश <linux/bug.h>

#अगर_घोषित __BIG_ENDIAN
#घोषणा BITOFF_CAL(size, off)	((माप(u32) - size - off) * BITS_PER_BYTE)
#अन्यथा
#घोषणा BITOFF_CAL(size, off)	(off * BITS_PER_BYTE)
#पूर्ण_अगर

#घोषणा XCHG_GEN(type, sfx, cl)				\
अटल अंतरभूत u32 __xchg_##type##sfx(अस्थिर व्योम *p, u32 val)	\
अणु								\
	अचिन्हित पूर्णांक prev, prev_mask, पंचांगp, bitoff, off;		\
								\
	off = (अचिन्हित दीर्घ)p % माप(u32);			\
	bitoff = BITOFF_CAL(माप(type), off);			\
	p -= off;						\
	val <<= bitoff;						\
	prev_mask = (u32)(type)-1 << bitoff;			\
								\
	__यंत्र__ __अस्थिर__(					\
"1:	lwarx   %0,0,%3\n"					\
"	andc	%1,%0,%5\n"					\
"	or	%1,%1,%4\n"					\
"	stwcx.	%1,0,%3\n"					\
"	bne-	1b\n"						\
	: "=&r" (prev), "=&r" (पंचांगp), "+m" (*(u32*)p)		\
	: "r" (p), "r" (val), "r" (prev_mask)			\
	: "cc", cl);						\
								\
	वापस prev >> bitoff;					\
पूर्ण

#घोषणा CMPXCHG_GEN(type, sfx, br, br2, cl)			\
अटल अंतरभूत							\
u32 __cmpxchg_##type##sfx(अस्थिर व्योम *p, u32 old, u32 new)	\
अणु								\
	अचिन्हित पूर्णांक prev, prev_mask, पंचांगp, bitoff, off;		\
								\
	off = (अचिन्हित दीर्घ)p % माप(u32);			\
	bitoff = BITOFF_CAL(माप(type), off);			\
	p -= off;						\
	old <<= bitoff;						\
	new <<= bitoff;						\
	prev_mask = (u32)(type)-1 << bitoff;			\
								\
	__यंत्र__ __अस्थिर__(					\
	br							\
"1:	lwarx   %0,0,%3\n"					\
"	and	%1,%0,%6\n"					\
"	cmpw	0,%1,%4\n"					\
"	bne-	2f\n"						\
"	andc	%1,%0,%6\n"					\
"	or	%1,%1,%5\n"					\
"	stwcx.  %1,0,%3\n"					\
"	bne-    1b\n"						\
	br2							\
	"\n"							\
"2:"								\
	: "=&r" (prev), "=&r" (पंचांगp), "+m" (*(u32*)p)		\
	: "r" (p), "r" (old), "r" (new), "r" (prev_mask)	\
	: "cc", cl);						\
								\
	वापस prev >> bitoff;					\
पूर्ण

/*
 * Atomic exchange
 *
 * Changes the memory location '*p' to be val and वापसs
 * the previous value stored there.
 */

XCHG_GEN(u8, _local, "memory");
XCHG_GEN(u8, _relaxed, "cc");
XCHG_GEN(u16, _local, "memory");
XCHG_GEN(u16, _relaxed, "cc");

अटल __always_अंतरभूत अचिन्हित दीर्घ
__xchg_u32_local(अस्थिर व्योम *p, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ prev;

	__यंत्र__ __अस्थिर__(
"1:	lwarx	%0,0,%2 \n"
"	stwcx.	%3,0,%2 \न\
	bne-	1b"
	: "=&r" (prev), "+m" (*(अस्थिर अचिन्हित पूर्णांक *)p)
	: "r" (p), "r" (val)
	: "cc", "memory");

	वापस prev;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ
__xchg_u32_relaxed(u32 *p, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ prev;

	__यंत्र__ __अस्थिर__(
"1:	lwarx	%0,0,%2\n"
"	stwcx.	%3,0,%2\n"
"	bne-	1b"
	: "=&r" (prev), "+m" (*p)
	: "r" (p), "r" (val)
	: "cc");

	वापस prev;
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल __always_अंतरभूत अचिन्हित दीर्घ
__xchg_u64_local(अस्थिर व्योम *p, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ prev;

	__यंत्र__ __अस्थिर__(
"1:	ldarx	%0,0,%2 \n"
"	stdcx.	%3,0,%2 \न\
	bne-	1b"
	: "=&r" (prev), "+m" (*(अस्थिर अचिन्हित दीर्घ *)p)
	: "r" (p), "r" (val)
	: "cc", "memory");

	वापस prev;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ
__xchg_u64_relaxed(u64 *p, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ prev;

	__यंत्र__ __अस्थिर__(
"1:	ldarx	%0,0,%2\n"
"	stdcx.	%3,0,%2\n"
"	bne-	1b"
	: "=&r" (prev), "+m" (*p)
	: "r" (p), "r" (val)
	: "cc");

	वापस prev;
पूर्ण
#पूर्ण_अगर

अटल __always_अंतरभूत अचिन्हित दीर्घ
__xchg_local(व्योम *ptr, अचिन्हित दीर्घ x, अचिन्हित पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 1:
		वापस __xchg_u8_local(ptr, x);
	हाल 2:
		वापस __xchg_u16_local(ptr, x);
	हाल 4:
		वापस __xchg_u32_local(ptr, x);
#अगर_घोषित CONFIG_PPC64
	हाल 8:
		वापस __xchg_u64_local(ptr, x);
#पूर्ण_अगर
	पूर्ण
	BUILD_BUG_ON_MSG(1, "Unsupported size for __xchg");
	वापस x;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ
__xchg_relaxed(व्योम *ptr, अचिन्हित दीर्घ x, अचिन्हित पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 1:
		वापस __xchg_u8_relaxed(ptr, x);
	हाल 2:
		वापस __xchg_u16_relaxed(ptr, x);
	हाल 4:
		वापस __xchg_u32_relaxed(ptr, x);
#अगर_घोषित CONFIG_PPC64
	हाल 8:
		वापस __xchg_u64_relaxed(ptr, x);
#पूर्ण_अगर
	पूर्ण
	BUILD_BUG_ON_MSG(1, "Unsupported size for __xchg_local");
	वापस x;
पूर्ण
#घोषणा xchg_local(ptr,x)						     \
  (अणु									     \
     __typeof__(*(ptr)) _x_ = (x);					     \
     (__typeof__(*(ptr))) __xchg_local((ptr),				     \
     		(अचिन्हित दीर्घ)_x_, माप(*(ptr))); 			     \
  पूर्ण)

#घोषणा xchg_relaxed(ptr, x)						\
(अणु									\
	__typeof__(*(ptr)) _x_ = (x);					\
	(__typeof__(*(ptr))) __xchg_relaxed((ptr),			\
			(अचिन्हित दीर्घ)_x_, माप(*(ptr)));		\
पूर्ण)
/*
 * Compare and exchange - अगर *p == old, set it to new,
 * and वापस the old value of *p.
 */

CMPXCHG_GEN(u8, , PPC_ATOMIC_ENTRY_BARRIER, PPC_ATOMIC_EXIT_BARRIER, "memory");
CMPXCHG_GEN(u8, _local, , , "memory");
CMPXCHG_GEN(u8, _acquire, , PPC_ACQUIRE_BARRIER, "memory");
CMPXCHG_GEN(u8, _relaxed, , , "cc");
CMPXCHG_GEN(u16, , PPC_ATOMIC_ENTRY_BARRIER, PPC_ATOMIC_EXIT_BARRIER, "memory");
CMPXCHG_GEN(u16, _local, , , "memory");
CMPXCHG_GEN(u16, _acquire, , PPC_ACQUIRE_BARRIER, "memory");
CMPXCHG_GEN(u16, _relaxed, , , "cc");

अटल __always_अंतरभूत अचिन्हित दीर्घ
__cmpxchg_u32(अस्थिर अचिन्हित पूर्णांक *p, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new)
अणु
	अचिन्हित पूर्णांक prev;

	__यंत्र__ __अस्थिर__ (
	PPC_ATOMIC_ENTRY_BARRIER
"1:	lwarx	%0,0,%2		# __cmpxchg_u32\न\
	cmpw	0,%0,%3\न\
	bne-	2f\न"
"	stwcx.	%4,0,%2\न\
	bne-	1b"
	PPC_ATOMIC_EXIT_BARRIER
	"\न\
2:"
	: "=&r" (prev), "+m" (*p)
	: "r" (p), "r" (old), "r" (new)
	: "cc", "memory");

	वापस prev;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ
__cmpxchg_u32_local(अस्थिर अचिन्हित पूर्णांक *p, अचिन्हित दीर्घ old,
			अचिन्हित दीर्घ new)
अणु
	अचिन्हित पूर्णांक prev;

	__यंत्र__ __अस्थिर__ (
"1:	lwarx	%0,0,%2		# __cmpxchg_u32\न\
	cmpw	0,%0,%3\न\
	bne-	2f\न"
"	stwcx.	%4,0,%2\न\
	bne-	1b"
	"\न\
2:"
	: "=&r" (prev), "+m" (*p)
	: "r" (p), "r" (old), "r" (new)
	: "cc", "memory");

	वापस prev;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ
__cmpxchg_u32_relaxed(u32 *p, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new)
अणु
	अचिन्हित दीर्घ prev;

	__यंत्र__ __अस्थिर__ (
"1:	lwarx	%0,0,%2		# __cmpxchg_u32_relaxed\n"
"	cmpw	0,%0,%3\n"
"	bne-	2f\n"
"	stwcx.	%4,0,%2\n"
"	bne-	1b\n"
"2:"
	: "=&r" (prev), "+m" (*p)
	: "r" (p), "r" (old), "r" (new)
	: "cc");

	वापस prev;
पूर्ण

/*
 * cmpxchg family करोn't have order guarantee अगर cmp part fails, thereक्रमe we
 * can aव्योम superfluous barriers अगर we use assembly code to implement
 * cmpxchg() and cmpxchg_acquire(), however we करोn't करो the similar क्रम
 * cmpxchg_release() because that will result in putting a barrier in the
 * middle of a ll/sc loop, which is probably a bad idea. For example, this
 * might cause the conditional store more likely to fail.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ
__cmpxchg_u32_acquire(u32 *p, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new)
अणु
	अचिन्हित दीर्घ prev;

	__यंत्र__ __अस्थिर__ (
"1:	lwarx	%0,0,%2		# __cmpxchg_u32_acquire\n"
"	cmpw	0,%0,%3\n"
"	bne-	2f\n"
"	stwcx.	%4,0,%2\n"
"	bne-	1b\n"
	PPC_ACQUIRE_BARRIER
	"\n"
"2:"
	: "=&r" (prev), "+m" (*p)
	: "r" (p), "r" (old), "r" (new)
	: "cc", "memory");

	वापस prev;
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल __always_अंतरभूत अचिन्हित दीर्घ
__cmpxchg_u64(अस्थिर अचिन्हित दीर्घ *p, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new)
अणु
	अचिन्हित दीर्घ prev;

	__यंत्र__ __अस्थिर__ (
	PPC_ATOMIC_ENTRY_BARRIER
"1:	ldarx	%0,0,%2		# __cmpxchg_u64\न\
	cmpd	0,%0,%3\न\
	bne-	2f\न\
	stdcx.	%4,0,%2\न\
	bne-	1b"
	PPC_ATOMIC_EXIT_BARRIER
	"\न\
2:"
	: "=&r" (prev), "+m" (*p)
	: "r" (p), "r" (old), "r" (new)
	: "cc", "memory");

	वापस prev;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ
__cmpxchg_u64_local(अस्थिर अचिन्हित दीर्घ *p, अचिन्हित दीर्घ old,
			अचिन्हित दीर्घ new)
अणु
	अचिन्हित दीर्घ prev;

	__यंत्र__ __अस्थिर__ (
"1:	ldarx	%0,0,%2		# __cmpxchg_u64\न\
	cmpd	0,%0,%3\न\
	bne-	2f\न\
	stdcx.	%4,0,%2\न\
	bne-	1b"
	"\न\
2:"
	: "=&r" (prev), "+m" (*p)
	: "r" (p), "r" (old), "r" (new)
	: "cc", "memory");

	वापस prev;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ
__cmpxchg_u64_relaxed(u64 *p, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new)
अणु
	अचिन्हित दीर्घ prev;

	__यंत्र__ __अस्थिर__ (
"1:	ldarx	%0,0,%2		# __cmpxchg_u64_relaxed\n"
"	cmpd	0,%0,%3\n"
"	bne-	2f\n"
"	stdcx.	%4,0,%2\n"
"	bne-	1b\n"
"2:"
	: "=&r" (prev), "+m" (*p)
	: "r" (p), "r" (old), "r" (new)
	: "cc");

	वापस prev;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ
__cmpxchg_u64_acquire(u64 *p, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new)
अणु
	अचिन्हित दीर्घ prev;

	__यंत्र__ __अस्थिर__ (
"1:	ldarx	%0,0,%2		# __cmpxchg_u64_acquire\n"
"	cmpd	0,%0,%3\n"
"	bne-	2f\n"
"	stdcx.	%4,0,%2\n"
"	bne-	1b\n"
	PPC_ACQUIRE_BARRIER
	"\n"
"2:"
	: "=&r" (prev), "+m" (*p)
	: "r" (p), "r" (old), "r" (new)
	: "cc", "memory");

	वापस prev;
पूर्ण
#पूर्ण_अगर

अटल __always_अंतरभूत अचिन्हित दीर्घ
__cmpxchg(अस्थिर व्योम *ptr, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new,
	  अचिन्हित पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 1:
		वापस __cmpxchg_u8(ptr, old, new);
	हाल 2:
		वापस __cmpxchg_u16(ptr, old, new);
	हाल 4:
		वापस __cmpxchg_u32(ptr, old, new);
#अगर_घोषित CONFIG_PPC64
	हाल 8:
		वापस __cmpxchg_u64(ptr, old, new);
#पूर्ण_अगर
	पूर्ण
	BUILD_BUG_ON_MSG(1, "Unsupported size for __cmpxchg");
	वापस old;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ
__cmpxchg_local(व्योम *ptr, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new,
	  अचिन्हित पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 1:
		वापस __cmpxchg_u8_local(ptr, old, new);
	हाल 2:
		वापस __cmpxchg_u16_local(ptr, old, new);
	हाल 4:
		वापस __cmpxchg_u32_local(ptr, old, new);
#अगर_घोषित CONFIG_PPC64
	हाल 8:
		वापस __cmpxchg_u64_local(ptr, old, new);
#पूर्ण_अगर
	पूर्ण
	BUILD_BUG_ON_MSG(1, "Unsupported size for __cmpxchg_local");
	वापस old;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ
__cmpxchg_relaxed(व्योम *ptr, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new,
		  अचिन्हित पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 1:
		वापस __cmpxchg_u8_relaxed(ptr, old, new);
	हाल 2:
		वापस __cmpxchg_u16_relaxed(ptr, old, new);
	हाल 4:
		वापस __cmpxchg_u32_relaxed(ptr, old, new);
#अगर_घोषित CONFIG_PPC64
	हाल 8:
		वापस __cmpxchg_u64_relaxed(ptr, old, new);
#पूर्ण_अगर
	पूर्ण
	BUILD_BUG_ON_MSG(1, "Unsupported size for __cmpxchg_relaxed");
	वापस old;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ
__cmpxchg_acquire(व्योम *ptr, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new,
		  अचिन्हित पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 1:
		वापस __cmpxchg_u8_acquire(ptr, old, new);
	हाल 2:
		वापस __cmpxchg_u16_acquire(ptr, old, new);
	हाल 4:
		वापस __cmpxchg_u32_acquire(ptr, old, new);
#अगर_घोषित CONFIG_PPC64
	हाल 8:
		वापस __cmpxchg_u64_acquire(ptr, old, new);
#पूर्ण_अगर
	पूर्ण
	BUILD_BUG_ON_MSG(1, "Unsupported size for __cmpxchg_acquire");
	वापस old;
पूर्ण
#घोषणा cmpxchg(ptr, o, n)						 \
  (अणु									 \
     __typeof__(*(ptr)) _o_ = (o);					 \
     __typeof__(*(ptr)) _n_ = (n);					 \
     (__typeof__(*(ptr))) __cmpxchg((ptr), (अचिन्हित दीर्घ)_o_,		 \
				    (अचिन्हित दीर्घ)_n_, माप(*(ptr))); \
  पूर्ण)


#घोषणा cmpxchg_local(ptr, o, n)					 \
  (अणु									 \
     __typeof__(*(ptr)) _o_ = (o);					 \
     __typeof__(*(ptr)) _n_ = (n);					 \
     (__typeof__(*(ptr))) __cmpxchg_local((ptr), (अचिन्हित दीर्घ)_o_,	 \
				    (अचिन्हित दीर्घ)_n_, माप(*(ptr))); \
  पूर्ण)

#घोषणा cmpxchg_relaxed(ptr, o, n)					\
(अणु									\
	__typeof__(*(ptr)) _o_ = (o);					\
	__typeof__(*(ptr)) _n_ = (n);					\
	(__typeof__(*(ptr))) __cmpxchg_relaxed((ptr),			\
			(अचिन्हित दीर्घ)_o_, (अचिन्हित दीर्घ)_n_,		\
			माप(*(ptr)));				\
पूर्ण)

#घोषणा cmpxchg_acquire(ptr, o, n)					\
(अणु									\
	__typeof__(*(ptr)) _o_ = (o);					\
	__typeof__(*(ptr)) _n_ = (n);					\
	(__typeof__(*(ptr))) __cmpxchg_acquire((ptr),			\
			(अचिन्हित दीर्घ)_o_, (अचिन्हित दीर्घ)_n_,		\
			माप(*(ptr)));				\
पूर्ण)
#अगर_घोषित CONFIG_PPC64
#घोषणा cmpxchg64(ptr, o, n)						\
  (अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 8);				\
	cmpxchg((ptr), (o), (n));					\
  पूर्ण)
#घोषणा cmpxchg64_local(ptr, o, n)					\
  (अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 8);				\
	cmpxchg_local((ptr), (o), (n));					\
  पूर्ण)
#घोषणा cmpxchg64_relaxed(ptr, o, n)					\
(अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 8);				\
	cmpxchg_relaxed((ptr), (o), (n));				\
पूर्ण)
#घोषणा cmpxchg64_acquire(ptr, o, n)					\
(अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 8);				\
	cmpxchg_acquire((ptr), (o), (n));				\
पूर्ण)
#अन्यथा
#समावेश <यंत्र-generic/cmpxchg-local.h>
#घोषणा cmpxchg64_local(ptr, o, n) __cmpxchg64_local_generic((ptr), (o), (n))
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_CMPXCHG_H_ */
