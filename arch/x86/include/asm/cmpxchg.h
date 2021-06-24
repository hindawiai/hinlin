<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASM_X86_CMPXCHG_H
#घोषणा ASM_X86_CMPXCHG_H

#समावेश <linux/compiler.h>
#समावेश <यंत्र/cpufeatures.h>
#समावेश <यंत्र/alternative.h> /* Provides LOCK_PREFIX */

/*
 * Non-existent functions to indicate usage errors at link समय
 * (or compile-समय अगर the compiler implements __compileसमय_error().
 */
बाह्य व्योम __xchg_wrong_size(व्योम)
	__compileसमय_error("Bad argument size for xchg");
बाह्य व्योम __cmpxchg_wrong_size(व्योम)
	__compileसमय_error("Bad argument size for cmpxchg");
बाह्य व्योम __xadd_wrong_size(व्योम)
	__compileसमय_error("Bad argument size for xadd");
बाह्य व्योम __add_wrong_size(व्योम)
	__compileसमय_error("Bad argument size for add");

/*
 * Constants क्रम operation sizes. On 32-bit, the 64-bit size it set to
 * -1 because माप will never वापस -1, thereby making those चयन
 * हाल statements guaranteed dead code which the compiler will
 * eliminate, and allowing the "missing symbol in the default case" to
 * indicate a usage error.
 */
#घोषणा __X86_CASE_B	1
#घोषणा __X86_CASE_W	2
#घोषणा __X86_CASE_L	4
#अगर_घोषित CONFIG_64BIT
#घोषणा __X86_CASE_Q	8
#अन्यथा
#घोषणा	__X86_CASE_Q	-1		/* माप will never वापस -1 */
#पूर्ण_अगर

/* 
 * An exchange-type operation, which takes a value and a poपूर्णांकer, and
 * वापसs the old value.
 */
#घोषणा __xchg_op(ptr, arg, op, lock)					\
	(अणु								\
	        __typeof__ (*(ptr)) __ret = (arg);			\
		चयन (माप(*(ptr))) अणु				\
		हाल __X86_CASE_B:					\
			यंत्र अस्थिर (lock #op "b %b0, %1\n"		\
				      : "+q" (__ret), "+m" (*(ptr))	\
				      : : "memory", "cc");		\
			अवरोध;						\
		हाल __X86_CASE_W:					\
			यंत्र अस्थिर (lock #op "w %w0, %1\n"		\
				      : "+r" (__ret), "+m" (*(ptr))	\
				      : : "memory", "cc");		\
			अवरोध;						\
		हाल __X86_CASE_L:					\
			यंत्र अस्थिर (lock #op "l %0, %1\n"		\
				      : "+r" (__ret), "+m" (*(ptr))	\
				      : : "memory", "cc");		\
			अवरोध;						\
		हाल __X86_CASE_Q:					\
			यंत्र अस्थिर (lock #op "q %q0, %1\n"		\
				      : "+r" (__ret), "+m" (*(ptr))	\
				      : : "memory", "cc");		\
			अवरोध;						\
		शेष:						\
			__ ## op ## _wrong_size();			\
		पूर्ण							\
		__ret;							\
	पूर्ण)

/*
 * Note: no "lock" prefix even on SMP: xchg always implies lock anyway.
 * Since this is generally used to protect other memory inक्रमmation, we
 * use "asm volatile" and "memory" clobbers to prevent gcc from moving
 * inक्रमmation around.
 */
#घोषणा arch_xchg(ptr, v)	__xchg_op((ptr), (v), xchg, "")

/*
 * Atomic compare and exchange.  Compare OLD with MEM, अगर identical,
 * store NEW in MEM.  Return the initial value in MEM.  Success is
 * indicated by comparing RETURN with OLD.
 */
#घोषणा __raw_cmpxchg(ptr, old, new, size, lock)			\
(अणु									\
	__typeof__(*(ptr)) __ret;					\
	__typeof__(*(ptr)) __old = (old);				\
	__typeof__(*(ptr)) __new = (new);				\
	चयन (size) अणु							\
	हाल __X86_CASE_B:						\
	अणु								\
		अस्थिर u8 *__ptr = (अस्थिर u8 *)(ptr);		\
		यंत्र अस्थिर(lock "cmpxchgb %2,%1"			\
			     : "=a" (__ret), "+m" (*__ptr)		\
			     : "q" (__new), "0" (__old)			\
			     : "memory");				\
		अवरोध;							\
	पूर्ण								\
	हाल __X86_CASE_W:						\
	अणु								\
		अस्थिर u16 *__ptr = (अस्थिर u16 *)(ptr);		\
		यंत्र अस्थिर(lock "cmpxchgw %2,%1"			\
			     : "=a" (__ret), "+m" (*__ptr)		\
			     : "r" (__new), "0" (__old)			\
			     : "memory");				\
		अवरोध;							\
	पूर्ण								\
	हाल __X86_CASE_L:						\
	अणु								\
		अस्थिर u32 *__ptr = (अस्थिर u32 *)(ptr);		\
		यंत्र अस्थिर(lock "cmpxchgl %2,%1"			\
			     : "=a" (__ret), "+m" (*__ptr)		\
			     : "r" (__new), "0" (__old)			\
			     : "memory");				\
		अवरोध;							\
	पूर्ण								\
	हाल __X86_CASE_Q:						\
	अणु								\
		अस्थिर u64 *__ptr = (अस्थिर u64 *)(ptr);		\
		यंत्र अस्थिर(lock "cmpxchgq %2,%1"			\
			     : "=a" (__ret), "+m" (*__ptr)		\
			     : "r" (__new), "0" (__old)			\
			     : "memory");				\
		अवरोध;							\
	पूर्ण								\
	शेष:							\
		__cmpxchg_wrong_size();					\
	पूर्ण								\
	__ret;								\
पूर्ण)

#घोषणा __cmpxchg(ptr, old, new, size)					\
	__raw_cmpxchg((ptr), (old), (new), (size), LOCK_PREFIX)

#घोषणा __sync_cmpxchg(ptr, old, new, size)				\
	__raw_cmpxchg((ptr), (old), (new), (size), "lock; ")

#घोषणा __cmpxchg_local(ptr, old, new, size)				\
	__raw_cmpxchg((ptr), (old), (new), (size), "")

#अगर_घोषित CONFIG_X86_32
# include <यंत्र/cmpxchg_32.h>
#अन्यथा
# include <यंत्र/cmpxchg_64.h>
#पूर्ण_अगर

#घोषणा arch_cmpxchg(ptr, old, new)					\
	__cmpxchg(ptr, old, new, माप(*(ptr)))

#घोषणा arch_sync_cmpxchg(ptr, old, new)				\
	__sync_cmpxchg(ptr, old, new, माप(*(ptr)))

#घोषणा arch_cmpxchg_local(ptr, old, new)				\
	__cmpxchg_local(ptr, old, new, माप(*(ptr)))


#घोषणा __raw_try_cmpxchg(_ptr, _pold, _new, size, lock)		\
(अणु									\
	bool success;							\
	__typeof__(_ptr) _old = (__typeof__(_ptr))(_pold);		\
	__typeof__(*(_ptr)) __old = *_old;				\
	__typeof__(*(_ptr)) __new = (_new);				\
	चयन (size) अणु							\
	हाल __X86_CASE_B:						\
	अणु								\
		अस्थिर u8 *__ptr = (अस्थिर u8 *)(_ptr);		\
		यंत्र अस्थिर(lock "cmpxchgb %[new], %[ptr]"		\
			     CC_SET(z)					\
			     : CC_OUT(z) (success),			\
			       [ptr] "+m" (*__ptr),			\
			       [old] "+a" (__old)			\
			     : [new] "q" (__new)			\
			     : "memory");				\
		अवरोध;							\
	पूर्ण								\
	हाल __X86_CASE_W:						\
	अणु								\
		अस्थिर u16 *__ptr = (अस्थिर u16 *)(_ptr);		\
		यंत्र अस्थिर(lock "cmpxchgw %[new], %[ptr]"		\
			     CC_SET(z)					\
			     : CC_OUT(z) (success),			\
			       [ptr] "+m" (*__ptr),			\
			       [old] "+a" (__old)			\
			     : [new] "r" (__new)			\
			     : "memory");				\
		अवरोध;							\
	पूर्ण								\
	हाल __X86_CASE_L:						\
	अणु								\
		अस्थिर u32 *__ptr = (अस्थिर u32 *)(_ptr);		\
		यंत्र अस्थिर(lock "cmpxchgl %[new], %[ptr]"		\
			     CC_SET(z)					\
			     : CC_OUT(z) (success),			\
			       [ptr] "+m" (*__ptr),			\
			       [old] "+a" (__old)			\
			     : [new] "r" (__new)			\
			     : "memory");				\
		अवरोध;							\
	पूर्ण								\
	हाल __X86_CASE_Q:						\
	अणु								\
		अस्थिर u64 *__ptr = (अस्थिर u64 *)(_ptr);		\
		यंत्र अस्थिर(lock "cmpxchgq %[new], %[ptr]"		\
			     CC_SET(z)					\
			     : CC_OUT(z) (success),			\
			       [ptr] "+m" (*__ptr),			\
			       [old] "+a" (__old)			\
			     : [new] "r" (__new)			\
			     : "memory");				\
		अवरोध;							\
	पूर्ण								\
	शेष:							\
		__cmpxchg_wrong_size();					\
	पूर्ण								\
	अगर (unlikely(!success))						\
		*_old = __old;						\
	likely(success);						\
पूर्ण)

#घोषणा __try_cmpxchg(ptr, pold, new, size)				\
	__raw_try_cmpxchg((ptr), (pold), (new), (size), LOCK_PREFIX)

#घोषणा arch_try_cmpxchg(ptr, pold, new) 				\
	__try_cmpxchg((ptr), (pold), (new), माप(*(ptr)))

/*
 * xadd() adds "inc" to "*ptr" and atomically वापसs the previous
 * value of "*ptr".
 *
 * xadd() is locked when multiple CPUs are online
 */
#घोषणा __xadd(ptr, inc, lock)	__xchg_op((ptr), (inc), xadd, lock)
#घोषणा xadd(ptr, inc)		__xadd((ptr), (inc), LOCK_PREFIX)

#घोषणा __cmpxchg_द्विगुन(pfx, p1, p2, o1, o2, n1, n2)			\
(अणु									\
	bool __ret;							\
	__typeof__(*(p1)) __old1 = (o1), __new1 = (n1);			\
	__typeof__(*(p2)) __old2 = (o2), __new2 = (n2);			\
	BUILD_BUG_ON(माप(*(p1)) != माप(दीर्घ));			\
	BUILD_BUG_ON(माप(*(p2)) != माप(दीर्घ));			\
	VM_BUG_ON((अचिन्हित दीर्घ)(p1) % (2 * माप(दीर्घ)));		\
	VM_BUG_ON((अचिन्हित दीर्घ)((p1) + 1) != (अचिन्हित दीर्घ)(p2));	\
	यंत्र अस्थिर(pfx "cmpxchg%c5b %1"				\
		     CC_SET(e)						\
		     : CC_OUT(e) (__ret),				\
		       "+m" (*(p1)), "+m" (*(p2)),			\
		       "+a" (__old1), "+d" (__old2)			\
		     : "i" (2 * माप(दीर्घ)),				\
		       "b" (__new1), "c" (__new2));			\
	__ret;								\
पूर्ण)

#घोषणा arch_cmpxchg_द्विगुन(p1, p2, o1, o2, n1, n2) \
	__cmpxchg_द्विगुन(LOCK_PREFIX, p1, p2, o1, o2, n1, n2)

#घोषणा arch_cmpxchg_द्विगुन_local(p1, p2, o1, o2, n1, n2) \
	__cmpxchg_द्विगुन(, p1, p2, o1, o2, n1, n2)

#पूर्ण_अगर	/* ASM_X86_CMPXCHG_H */
