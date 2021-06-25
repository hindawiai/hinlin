<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * विभाजनed from parisc यंत्र/atomic.h which was:
 *	Copyright (C) 2000 Philipp Rumpf <prumpf@tux.org>
 *	Copyright (C) 2006 Kyle McMartin <kyle@parisc-linux.org>
 */

#अगर_अघोषित _ASM_PARISC_CMPXCHG_H_
#घोषणा _ASM_PARISC_CMPXCHG_H_

/* This should get optimized out since it's never called.
** Or get a link error अगर xchg is used "wrong".
*/
बाह्य व्योम __xchg_called_with_bad_poपूर्णांकer(व्योम);

/* __xchg32/64 defined in arch/parisc/lib/bitops.c */
बाह्य अचिन्हित दीर्घ __xchg8(अक्षर, अस्थिर अक्षर *);
बाह्य अचिन्हित दीर्घ __xchg32(पूर्णांक, अस्थिर पूर्णांक *);
#अगर_घोषित CONFIG_64BIT
बाह्य अचिन्हित दीर्घ __xchg64(अचिन्हित दीर्घ, अस्थिर अचिन्हित दीर्घ *);
#पूर्ण_अगर

/* optimizer better get rid of चयन since size is a स्थिरant */
अटल अंतरभूत अचिन्हित दीर्घ
__xchg(अचिन्हित दीर्घ x, अस्थिर व्योम *ptr, पूर्णांक size)
अणु
	चयन (size) अणु
#अगर_घोषित CONFIG_64BIT
	हाल 8: वापस __xchg64(x, (अस्थिर अचिन्हित दीर्घ *) ptr);
#पूर्ण_अगर
	हाल 4: वापस __xchg32((पूर्णांक) x, (अस्थिर पूर्णांक *) ptr);
	हाल 1: वापस __xchg8((अक्षर) x, (अस्थिर अक्षर *) ptr);
	पूर्ण
	__xchg_called_with_bad_poपूर्णांकer();
	वापस x;
पूर्ण

/*
** REVISIT - Abanकरोned use of LDCW in xchg() क्रम now:
** o need to test माप(*ptr) to aव्योम clearing adjacent bytes
** o and जबतक we are at it, could CONFIG_64BIT code use LDCD too?
**
**	अगर (__builtin_स्थिरant_p(x) && (x == शून्य))
**		अगर (((अचिन्हित दीर्घ)p & 0xf) == 0)
**			वापस __ldcw(p);
*/
#घोषणा xchg(ptr, x)							\
(अणु									\
	__typeof__(*(ptr)) __ret;					\
	__typeof__(*(ptr)) _x_ = (x);					\
	__ret = (__typeof__(*(ptr)))					\
		__xchg((अचिन्हित दीर्घ)_x_, (ptr), माप(*(ptr)));	\
	__ret;								\
पूर्ण)

/* bug catcher क्रम when unsupported size is used - won't link */
बाह्य व्योम __cmpxchg_called_with_bad_poपूर्णांकer(व्योम);

/* __cmpxchg_u32/u64 defined in arch/parisc/lib/bitops.c */
बाह्य अचिन्हित दीर्घ __cmpxchg_u32(अस्थिर अचिन्हित पूर्णांक *m, अचिन्हित पूर्णांक old,
				   अचिन्हित पूर्णांक new_);
बाह्य u64 __cmpxchg_u64(अस्थिर u64 *ptr, u64 old, u64 new_);
बाह्य u8 __cmpxchg_u8(अस्थिर u8 *ptr, u8 old, u8 new_);

/* करोn't worry...optimizer will get rid of most of this */
अटल अंतरभूत अचिन्हित दीर्घ
__cmpxchg(अस्थिर व्योम *ptr, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new_, पूर्णांक size)
अणु
	चयन (size) अणु
#अगर_घोषित CONFIG_64BIT
	हाल 8: वापस __cmpxchg_u64((u64 *)ptr, old, new_);
#पूर्ण_अगर
	हाल 4: वापस __cmpxchg_u32((अचिन्हित पूर्णांक *)ptr,
				     (अचिन्हित पूर्णांक)old, (अचिन्हित पूर्णांक)new_);
	हाल 1: वापस __cmpxchg_u8((u8 *)ptr, old & 0xff, new_ & 0xff);
	पूर्ण
	__cmpxchg_called_with_bad_poपूर्णांकer();
	वापस old;
पूर्ण

#घोषणा cmpxchg(ptr, o, n)						 \
(अणु									 \
	__typeof__(*(ptr)) _o_ = (o);					 \
	__typeof__(*(ptr)) _n_ = (n);					 \
	(__typeof__(*(ptr))) __cmpxchg((ptr), (अचिन्हित दीर्घ)_o_,	 \
				    (अचिन्हित दीर्घ)_n_, माप(*(ptr))); \
पूर्ण)

#समावेश <यंत्र-generic/cmpxchg-local.h>

अटल अंतरभूत अचिन्हित दीर्घ __cmpxchg_local(अस्थिर व्योम *ptr,
				      अचिन्हित दीर्घ old,
				      अचिन्हित दीर्घ new_, पूर्णांक size)
अणु
	चयन (size) अणु
#अगर_घोषित CONFIG_64BIT
	हाल 8:	वापस __cmpxchg_u64((u64 *)ptr, old, new_);
#पूर्ण_अगर
	हाल 4:	वापस __cmpxchg_u32(ptr, old, new_);
	शेष:
		वापस __cmpxchg_local_generic(ptr, old, new_, size);
	पूर्ण
पूर्ण

/*
 * cmpxchg_local and cmpxchg64_local are atomic wrt current CPU. Always make
 * them available.
 */
#घोषणा cmpxchg_local(ptr, o, n)					\
	((__typeof__(*(ptr)))__cmpxchg_local((ptr), (अचिन्हित दीर्घ)(o),	\
			(अचिन्हित दीर्घ)(n), माप(*(ptr))))
#अगर_घोषित CONFIG_64BIT
#घोषणा cmpxchg64_local(ptr, o, n)					\
(अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 8);				\
	cmpxchg_local((ptr), (o), (n));					\
पूर्ण)
#अन्यथा
#घोषणा cmpxchg64_local(ptr, o, n) __cmpxchg64_local_generic((ptr), (o), (n))
#पूर्ण_अगर

#घोषणा cmpxchg64(ptr, o, n) __cmpxchg_u64(ptr, o, n)

#पूर्ण_अगर /* _ASM_PARISC_CMPXCHG_H_ */
