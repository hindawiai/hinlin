<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित TOOLS_ASM_X86_CMPXCHG_H
#घोषणा TOOLS_ASM_X86_CMPXCHG_H

#समावेश <linux/compiler.h>

/*
 * Non-existant functions to indicate usage errors at link समय
 * (or compile-समय अगर the compiler implements __compileसमय_error().
 */
बाह्य व्योम __cmpxchg_wrong_size(व्योम)
	__compileसमय_error("Bad argument size for cmpxchg");

/*
 * Constants क्रम operation sizes. On 32-bit, the 64-bit size it set to
 * -1 because माप will never वापस -1, thereby making those चयन
 * हाल statements guaranteeed dead code which the compiler will
 * eliminate, and allowing the "missing symbol in the default case" to
 * indicate a usage error.
 */
#घोषणा __X86_CASE_B	1
#घोषणा __X86_CASE_W	2
#घोषणा __X86_CASE_L	4
#अगर_घोषित __x86_64__
#घोषणा __X86_CASE_Q	8
#अन्यथा
#घोषणा	__X86_CASE_Q	-1		/* माप will never वापस -1 */
#पूर्ण_अगर

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

#घोषणा cmpxchg(ptr, old, new)						\
	__cmpxchg(ptr, old, new, माप(*(ptr)))


#पूर्ण_अगर	/* TOOLS_ASM_X86_CMPXCHG_H */
