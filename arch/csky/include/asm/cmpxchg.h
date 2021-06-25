<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_CMPXCHG_H
#घोषणा __ASM_CSKY_CMPXCHG_H

#अगर_घोषित CONFIG_SMP
#समावेश <यंत्र/barrier.h>

बाह्य व्योम __bad_xchg(व्योम);

#घोषणा __xchg_relaxed(new, ptr, size)				\
(अणु								\
	__typeof__(ptr) __ptr = (ptr);				\
	__typeof__(new) __new = (new);				\
	__typeof__(*(ptr)) __ret;				\
	अचिन्हित दीर्घ पंचांगp;					\
	चयन (size) अणु						\
	हाल 4:							\
		यंत्र अस्थिर (					\
		"1:	ldex.w		%0, (%3) \n"		\
		"	mov		%1, %2   \n"		\
		"	stex.w		%1, (%3) \n"		\
		"	bez		%1, 1b   \n"		\
			: "=&r" (__ret), "=&r" (पंचांगp)		\
			: "r" (__new), "r"(__ptr)		\
			:);					\
		अवरोध;						\
	शेष:						\
		__bad_xchg();					\
	पूर्ण							\
	__ret;							\
पूर्ण)

#घोषणा xchg_relaxed(ptr, x) \
		(__xchg_relaxed((x), (ptr), माप(*(ptr))))

#घोषणा __cmpxchg_relaxed(ptr, old, new, size)			\
(अणु								\
	__typeof__(ptr) __ptr = (ptr);				\
	__typeof__(new) __new = (new);				\
	__typeof__(new) __पंचांगp;					\
	__typeof__(old) __old = (old);				\
	__typeof__(*(ptr)) __ret;				\
	चयन (size) अणु						\
	हाल 4:							\
		यंत्र अस्थिर (					\
		"1:	ldex.w		%0, (%3) \n"		\
		"	cmpne		%0, %4   \n"		\
		"	bt		2f       \n"		\
		"	mov		%1, %2   \n"		\
		"	stex.w		%1, (%3) \n"		\
		"	bez		%1, 1b   \n"		\
		"2:				 \n"		\
			: "=&r" (__ret), "=&r" (__पंचांगp)		\
			: "r" (__new), "r"(__ptr), "r"(__old)	\
			:);					\
		अवरोध;						\
	शेष:						\
		__bad_xchg();					\
	पूर्ण							\
	__ret;							\
पूर्ण)

#घोषणा cmpxchg_relaxed(ptr, o, n) \
	(__cmpxchg_relaxed((ptr), (o), (n), माप(*(ptr))))

#घोषणा cmpxchg(ptr, o, n) 					\
(अणु								\
	__typeof__(*(ptr)) __ret;				\
	__smp_release_fence();					\
	__ret = cmpxchg_relaxed(ptr, o, n);			\
	__smp_acquire_fence();					\
	__ret;							\
पूर्ण)

#अन्यथा
#समावेश <यंत्र-generic/cmpxchg.h>
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_CSKY_CMPXCHG_H */
