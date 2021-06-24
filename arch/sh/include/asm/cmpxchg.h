<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_CMPXCHG_H
#घोषणा __ASM_SH_CMPXCHG_H

/*
 * Atomic operations that C can't guarantee us.  Useful क्रम
 * resource counting etc..
 */

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

#अगर defined(CONFIG_GUSA_RB)
#समावेश <यंत्र/cmpxchg-grb.h>
#या_अगर defined(CONFIG_CPU_SH4A)
#समावेश <यंत्र/cmpxchg-llsc.h>
#या_अगर defined(CONFIG_CPU_J2) && defined(CONFIG_SMP)
#समावेश <यंत्र/cmpxchg-cas.h>
#अन्यथा
#समावेश <यंत्र/cmpxchg-irq.h>
#पूर्ण_अगर

बाह्य व्योम __xchg_called_with_bad_poपूर्णांकer(व्योम);

#घोषणा __xchg(ptr, x, size)				\
(अणु							\
	अचिन्हित दीर्घ __xchg__res;			\
	अस्थिर व्योम *__xchg_ptr = (ptr);		\
	चयन (size) अणु					\
	हाल 4:						\
		__xchg__res = xchg_u32(__xchg_ptr, x);	\
		अवरोध;					\
	हाल 2:						\
		__xchg__res = xchg_u16(__xchg_ptr, x);	\
		अवरोध;					\
	हाल 1:						\
		__xchg__res = xchg_u8(__xchg_ptr, x);	\
		अवरोध;					\
	शेष:					\
		__xchg_called_with_bad_poपूर्णांकer();	\
		__xchg__res = x;			\
		अवरोध;					\
	पूर्ण						\
							\
	__xchg__res;					\
पूर्ण)

#घोषणा xchg(ptr,x)	\
	((__typeof__(*(ptr)))__xchg((ptr),(अचिन्हित दीर्घ)(x), माप(*(ptr))))

/* This function करोesn't exist, so you'll get a linker error
 * अगर something tries to करो an invalid cmpxchg(). */
बाह्य व्योम __cmpxchg_called_with_bad_poपूर्णांकer(व्योम);

अटल अंतरभूत अचिन्हित दीर्घ __cmpxchg(अस्थिर व्योम * ptr, अचिन्हित दीर्घ old,
		अचिन्हित दीर्घ new, पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 4:
		वापस __cmpxchg_u32(ptr, old, new);
	पूर्ण
	__cmpxchg_called_with_bad_poपूर्णांकer();
	वापस old;
पूर्ण

#घोषणा cmpxchg(ptr,o,n)						 \
  (अणु									 \
     __typeof__(*(ptr)) _o_ = (o);					 \
     __typeof__(*(ptr)) _n_ = (n);					 \
     (__typeof__(*(ptr))) __cmpxchg((ptr), (अचिन्हित दीर्घ)_o_,		 \
				    (अचिन्हित दीर्घ)_n_, माप(*(ptr))); \
  पूर्ण)

#पूर्ण_अगर /* __ASM_SH_CMPXCHG_H */
