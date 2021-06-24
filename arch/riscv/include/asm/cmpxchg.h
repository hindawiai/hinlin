<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_CMPXCHG_H
#घोषणा _ASM_RISCV_CMPXCHG_H

#समावेश <linux/bug.h>

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/fence.h>

#घोषणा __xchg_relaxed(ptr, new, size)					\
(अणु									\
	__typeof__(ptr) __ptr = (ptr);					\
	__typeof__(new) __new = (new);					\
	__typeof__(*(ptr)) __ret;					\
	चयन (size) अणु							\
	हाल 4:								\
		__यंत्र__ __अस्थिर__ (					\
			"	amoswap.w %0, %2, %1\n"			\
			: "=r" (__ret), "+A" (*__ptr)			\
			: "r" (__new)					\
			: "memory");					\
		अवरोध;							\
	हाल 8:								\
		__यंत्र__ __अस्थिर__ (					\
			"	amoswap.d %0, %2, %1\n"			\
			: "=r" (__ret), "+A" (*__ptr)			\
			: "r" (__new)					\
			: "memory");					\
		अवरोध;							\
	शेष:							\
		BUILD_BUG();						\
	पूर्ण								\
	__ret;								\
पूर्ण)

#घोषणा xchg_relaxed(ptr, x)						\
(अणु									\
	__typeof__(*(ptr)) _x_ = (x);					\
	(__typeof__(*(ptr))) __xchg_relaxed((ptr),			\
					    _x_, माप(*(ptr)));	\
पूर्ण)

#घोषणा __xchg_acquire(ptr, new, size)					\
(अणु									\
	__typeof__(ptr) __ptr = (ptr);					\
	__typeof__(new) __new = (new);					\
	__typeof__(*(ptr)) __ret;					\
	चयन (size) अणु							\
	हाल 4:								\
		__यंत्र__ __अस्थिर__ (					\
			"	amoswap.w %0, %2, %1\n"			\
			RISCV_ACQUIRE_BARRIER				\
			: "=r" (__ret), "+A" (*__ptr)			\
			: "r" (__new)					\
			: "memory");					\
		अवरोध;							\
	हाल 8:								\
		__यंत्र__ __अस्थिर__ (					\
			"	amoswap.d %0, %2, %1\n"			\
			RISCV_ACQUIRE_BARRIER				\
			: "=r" (__ret), "+A" (*__ptr)			\
			: "r" (__new)					\
			: "memory");					\
		अवरोध;							\
	शेष:							\
		BUILD_BUG();						\
	पूर्ण								\
	__ret;								\
पूर्ण)

#घोषणा xchg_acquire(ptr, x)						\
(अणु									\
	__typeof__(*(ptr)) _x_ = (x);					\
	(__typeof__(*(ptr))) __xchg_acquire((ptr),			\
					    _x_, माप(*(ptr)));	\
पूर्ण)

#घोषणा __xchg_release(ptr, new, size)					\
(अणु									\
	__typeof__(ptr) __ptr = (ptr);					\
	__typeof__(new) __new = (new);					\
	__typeof__(*(ptr)) __ret;					\
	चयन (size) अणु							\
	हाल 4:								\
		__यंत्र__ __अस्थिर__ (					\
			RISCV_RELEASE_BARRIER				\
			"	amoswap.w %0, %2, %1\n"			\
			: "=r" (__ret), "+A" (*__ptr)			\
			: "r" (__new)					\
			: "memory");					\
		अवरोध;							\
	हाल 8:								\
		__यंत्र__ __अस्थिर__ (					\
			RISCV_RELEASE_BARRIER				\
			"	amoswap.d %0, %2, %1\n"			\
			: "=r" (__ret), "+A" (*__ptr)			\
			: "r" (__new)					\
			: "memory");					\
		अवरोध;							\
	शेष:							\
		BUILD_BUG();						\
	पूर्ण								\
	__ret;								\
पूर्ण)

#घोषणा xchg_release(ptr, x)						\
(अणु									\
	__typeof__(*(ptr)) _x_ = (x);					\
	(__typeof__(*(ptr))) __xchg_release((ptr),			\
					    _x_, माप(*(ptr)));	\
पूर्ण)

#घोषणा __xchg(ptr, new, size)						\
(अणु									\
	__typeof__(ptr) __ptr = (ptr);					\
	__typeof__(new) __new = (new);					\
	__typeof__(*(ptr)) __ret;					\
	चयन (size) अणु							\
	हाल 4:								\
		__यंत्र__ __अस्थिर__ (					\
			"	amoswap.w.aqrl %0, %2, %1\n"		\
			: "=r" (__ret), "+A" (*__ptr)			\
			: "r" (__new)					\
			: "memory");					\
		अवरोध;							\
	हाल 8:								\
		__यंत्र__ __अस्थिर__ (					\
			"	amoswap.d.aqrl %0, %2, %1\n"		\
			: "=r" (__ret), "+A" (*__ptr)			\
			: "r" (__new)					\
			: "memory");					\
		अवरोध;							\
	शेष:							\
		BUILD_BUG();						\
	पूर्ण								\
	__ret;								\
पूर्ण)

#घोषणा xchg(ptr, x)							\
(अणु									\
	__typeof__(*(ptr)) _x_ = (x);					\
	(__typeof__(*(ptr))) __xchg((ptr), _x_, माप(*(ptr)));	\
पूर्ण)

#घोषणा xchg32(ptr, x)							\
(अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 4);				\
	xchg((ptr), (x));						\
पूर्ण)

#घोषणा xchg64(ptr, x)							\
(अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 8);				\
	xchg((ptr), (x));						\
पूर्ण)

/*
 * Atomic compare and exchange.  Compare OLD with MEM, अगर identical,
 * store NEW in MEM.  Return the initial value in MEM.  Success is
 * indicated by comparing RETURN with OLD.
 */
#घोषणा __cmpxchg_relaxed(ptr, old, new, size)				\
(अणु									\
	__typeof__(ptr) __ptr = (ptr);					\
	__typeof__(*(ptr)) __old = (old);				\
	__typeof__(*(ptr)) __new = (new);				\
	__typeof__(*(ptr)) __ret;					\
	रेजिस्टर अचिन्हित पूर्णांक __rc;					\
	चयन (size) अणु							\
	हाल 4:								\
		__यंत्र__ __अस्थिर__ (					\
			"0:	lr.w %0, %2\n"				\
			"	bne  %0, %z3, 1f\n"			\
			"	sc.w %1, %z4, %2\n"			\
			"	bnez %1, 0b\n"				\
			"1:\n"						\
			: "=&r" (__ret), "=&r" (__rc), "+A" (*__ptr)	\
			: "rJ" ((दीर्घ)__old), "rJ" (__new)		\
			: "memory");					\
		अवरोध;							\
	हाल 8:								\
		__यंत्र__ __अस्थिर__ (					\
			"0:	lr.d %0, %2\n"				\
			"	bne %0, %z3, 1f\n"			\
			"	sc.d %1, %z4, %2\n"			\
			"	bnez %1, 0b\n"				\
			"1:\n"						\
			: "=&r" (__ret), "=&r" (__rc), "+A" (*__ptr)	\
			: "rJ" (__old), "rJ" (__new)			\
			: "memory");					\
		अवरोध;							\
	शेष:							\
		BUILD_BUG();						\
	पूर्ण								\
	__ret;								\
पूर्ण)

#घोषणा cmpxchg_relaxed(ptr, o, n)					\
(अणु									\
	__typeof__(*(ptr)) _o_ = (o);					\
	__typeof__(*(ptr)) _n_ = (n);					\
	(__typeof__(*(ptr))) __cmpxchg_relaxed((ptr),			\
					_o_, _n_, माप(*(ptr)));	\
पूर्ण)

#घोषणा __cmpxchg_acquire(ptr, old, new, size)				\
(अणु									\
	__typeof__(ptr) __ptr = (ptr);					\
	__typeof__(*(ptr)) __old = (old);				\
	__typeof__(*(ptr)) __new = (new);				\
	__typeof__(*(ptr)) __ret;					\
	रेजिस्टर अचिन्हित पूर्णांक __rc;					\
	चयन (size) अणु							\
	हाल 4:								\
		__यंत्र__ __अस्थिर__ (					\
			"0:	lr.w %0, %2\n"				\
			"	bne  %0, %z3, 1f\n"			\
			"	sc.w %1, %z4, %2\n"			\
			"	bnez %1, 0b\n"				\
			RISCV_ACQUIRE_BARRIER				\
			"1:\n"						\
			: "=&r" (__ret), "=&r" (__rc), "+A" (*__ptr)	\
			: "rJ" ((दीर्घ)__old), "rJ" (__new)		\
			: "memory");					\
		अवरोध;							\
	हाल 8:								\
		__यंत्र__ __अस्थिर__ (					\
			"0:	lr.d %0, %2\n"				\
			"	bne %0, %z3, 1f\n"			\
			"	sc.d %1, %z4, %2\n"			\
			"	bnez %1, 0b\n"				\
			RISCV_ACQUIRE_BARRIER				\
			"1:\n"						\
			: "=&r" (__ret), "=&r" (__rc), "+A" (*__ptr)	\
			: "rJ" (__old), "rJ" (__new)			\
			: "memory");					\
		अवरोध;							\
	शेष:							\
		BUILD_BUG();						\
	पूर्ण								\
	__ret;								\
पूर्ण)

#घोषणा cmpxchg_acquire(ptr, o, n)					\
(अणु									\
	__typeof__(*(ptr)) _o_ = (o);					\
	__typeof__(*(ptr)) _n_ = (n);					\
	(__typeof__(*(ptr))) __cmpxchg_acquire((ptr),			\
					_o_, _n_, माप(*(ptr)));	\
पूर्ण)

#घोषणा __cmpxchg_release(ptr, old, new, size)				\
(अणु									\
	__typeof__(ptr) __ptr = (ptr);					\
	__typeof__(*(ptr)) __old = (old);				\
	__typeof__(*(ptr)) __new = (new);				\
	__typeof__(*(ptr)) __ret;					\
	रेजिस्टर अचिन्हित पूर्णांक __rc;					\
	चयन (size) अणु							\
	हाल 4:								\
		__यंत्र__ __अस्थिर__ (					\
			RISCV_RELEASE_BARRIER				\
			"0:	lr.w %0, %2\n"				\
			"	bne  %0, %z3, 1f\n"			\
			"	sc.w %1, %z4, %2\n"			\
			"	bnez %1, 0b\n"				\
			"1:\n"						\
			: "=&r" (__ret), "=&r" (__rc), "+A" (*__ptr)	\
			: "rJ" ((दीर्घ)__old), "rJ" (__new)		\
			: "memory");					\
		अवरोध;							\
	हाल 8:								\
		__यंत्र__ __अस्थिर__ (					\
			RISCV_RELEASE_BARRIER				\
			"0:	lr.d %0, %2\n"				\
			"	bne %0, %z3, 1f\n"			\
			"	sc.d %1, %z4, %2\n"			\
			"	bnez %1, 0b\n"				\
			"1:\n"						\
			: "=&r" (__ret), "=&r" (__rc), "+A" (*__ptr)	\
			: "rJ" (__old), "rJ" (__new)			\
			: "memory");					\
		अवरोध;							\
	शेष:							\
		BUILD_BUG();						\
	पूर्ण								\
	__ret;								\
पूर्ण)

#घोषणा cmpxchg_release(ptr, o, n)					\
(अणु									\
	__typeof__(*(ptr)) _o_ = (o);					\
	__typeof__(*(ptr)) _n_ = (n);					\
	(__typeof__(*(ptr))) __cmpxchg_release((ptr),			\
					_o_, _n_, माप(*(ptr)));	\
पूर्ण)

#घोषणा __cmpxchg(ptr, old, new, size)					\
(अणु									\
	__typeof__(ptr) __ptr = (ptr);					\
	__typeof__(*(ptr)) __old = (old);				\
	__typeof__(*(ptr)) __new = (new);				\
	__typeof__(*(ptr)) __ret;					\
	रेजिस्टर अचिन्हित पूर्णांक __rc;					\
	चयन (size) अणु							\
	हाल 4:								\
		__यंत्र__ __अस्थिर__ (					\
			"0:	lr.w %0, %2\n"				\
			"	bne  %0, %z3, 1f\n"			\
			"	sc.w.rl %1, %z4, %2\n"			\
			"	bnez %1, 0b\n"				\
			"	fence rw, rw\n"				\
			"1:\n"						\
			: "=&r" (__ret), "=&r" (__rc), "+A" (*__ptr)	\
			: "rJ" ((दीर्घ)__old), "rJ" (__new)		\
			: "memory");					\
		अवरोध;							\
	हाल 8:								\
		__यंत्र__ __अस्थिर__ (					\
			"0:	lr.d %0, %2\n"				\
			"	bne %0, %z3, 1f\n"			\
			"	sc.d.rl %1, %z4, %2\n"			\
			"	bnez %1, 0b\n"				\
			"	fence rw, rw\n"				\
			"1:\n"						\
			: "=&r" (__ret), "=&r" (__rc), "+A" (*__ptr)	\
			: "rJ" (__old), "rJ" (__new)			\
			: "memory");					\
		अवरोध;							\
	शेष:							\
		BUILD_BUG();						\
	पूर्ण								\
	__ret;								\
पूर्ण)

#घोषणा cmpxchg(ptr, o, n)						\
(अणु									\
	__typeof__(*(ptr)) _o_ = (o);					\
	__typeof__(*(ptr)) _n_ = (n);					\
	(__typeof__(*(ptr))) __cmpxchg((ptr),				\
				       _o_, _n_, माप(*(ptr)));	\
पूर्ण)

#घोषणा cmpxchg_local(ptr, o, n)					\
	(__cmpxchg_relaxed((ptr), (o), (n), माप(*(ptr))))

#घोषणा cmpxchg32(ptr, o, n)						\
(अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 4);				\
	cmpxchg((ptr), (o), (n));					\
पूर्ण)

#घोषणा cmpxchg32_local(ptr, o, n)					\
(अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 4);				\
	cmpxchg_relaxed((ptr), (o), (n))				\
पूर्ण)

#घोषणा cmpxchg64(ptr, o, n)						\
(अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 8);				\
	cmpxchg((ptr), (o), (n));					\
पूर्ण)

#घोषणा cmpxchg64_local(ptr, o, n)					\
(अणु									\
	BUILD_BUG_ON(माप(*(ptr)) != 8);				\
	cmpxchg_relaxed((ptr), (o), (n));				\
पूर्ण)

#पूर्ण_अगर /* _ASM_RISCV_CMPXCHG_H */
