<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 *
 * This file was copied from include/यंत्र-generic/uaccess.h
 */

#अगर_अघोषित _ASM_RISCV_UACCESS_H
#घोषणा _ASM_RISCV_UACCESS_H

#समावेश <यंत्र/pgtable.h>		/* क्रम TASK_SIZE */

/*
 * User space memory access functions
 */
#अगर_घोषित CONFIG_MMU
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/compiler.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/extable.h>
#समावेश <यंत्र/यंत्र.h>

#घोषणा __enable_user_access()							\
	__यंत्र__ __अस्थिर__ ("csrs sstatus, %0" : : "r" (SR_SUM) : "memory")
#घोषणा __disable_user_access()							\
	__यंत्र__ __अस्थिर__ ("csrc sstatus, %0" : : "r" (SR_SUM) : "memory")

/**
 * access_ok: - Checks अगर a user space poपूर्णांकer is valid
 * @addr: User space poपूर्णांकer to start of block to check
 * @size: Size of block to check
 *
 * Context: User context only.  This function may sleep.
 *
 * Checks अगर a poपूर्णांकer to a block of memory in user space is valid.
 *
 * Returns true (nonzero) अगर the memory block may be valid, false (zero)
 * अगर it is definitely invalid.
 *
 * Note that, depending on architecture, this function probably just
 * checks that the poपूर्णांकer is in the user space range - after calling
 * this function, memory access functions may still वापस -EFAULT.
 */
#घोषणा access_ok(addr, size) (अणु					\
	__chk_user_ptr(addr);						\
	likely(__access_ok((अचिन्हित दीर्घ __क्रमce)(addr), (size)));	\
पूर्ण)

/*
 * Ensure that the range [addr, addr+size) is within the process's
 * address space
 */
अटल अंतरभूत पूर्णांक __access_ok(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	वापस size <= TASK_SIZE && addr <= TASK_SIZE - size;
पूर्ण

/*
 * The exception table consists of pairs of addresses: the first is the
 * address of an inकाष्ठाion that is allowed to fault, and the second is
 * the address at which the program should जारी.  No रेजिस्टरs are
 * modअगरied, so it is entirely up to the continuation code to figure out
 * what to करो.
 *
 * All the routines below use bits of fixup code that are out of line
 * with the मुख्य inकाष्ठाion path.  This means when everything is well,
 * we करोn't even have to jump over them.  Further, they करो not पूर्णांकrude
 * on our cache or tlb entries.
 */

#घोषणा __LSW	0
#घोषणा __MSW	1

/*
 * The "__xxx" versions of the user access functions करो not verअगरy the address
 * space - it must have been करोne previously with a separate "access_ok()"
 * call.
 */

#घोषणा __get_user_यंत्र(insn, x, ptr, err)			\
करो अणु								\
	uपूर्णांकptr_t __पंचांगp;					\
	__typeof__(x) __x;					\
	__यंत्र__ __अस्थिर__ (					\
		"1:\n"						\
		"	" insn " %1, %3\n"			\
		"2:\n"						\
		"	.section .fixup,\"ax\"\n"		\
		"	.balign 4\n"				\
		"3:\n"						\
		"	li %0, %4\n"				\
		"	li %1, 0\n"				\
		"	jump 2b, %2\n"				\
		"	.previous\n"				\
		"	.section __ex_table,\"a\"\n"		\
		"	.balign " RISCV_SZPTR "\n"			\
		"	" RISCV_PTR " 1b, 3b\n"			\
		"	.previous"				\
		: "+r" (err), "=&r" (__x), "=r" (__पंचांगp)		\
		: "m" (*(ptr)), "i" (-EFAULT));			\
	(x) = __x;						\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_64BIT
#घोषणा __get_user_8(x, ptr, err) \
	__get_user_यंत्र("ld", x, ptr, err)
#अन्यथा /* !CONFIG_64BIT */
#घोषणा __get_user_8(x, ptr, err)				\
करो अणु								\
	u32 __user *__ptr = (u32 __user *)(ptr);		\
	u32 __lo, __hi;						\
	uपूर्णांकptr_t __पंचांगp;					\
	__यंत्र__ __अस्थिर__ (					\
		"1:\n"						\
		"	lw %1, %4\n"				\
		"2:\n"						\
		"	lw %2, %5\n"				\
		"3:\n"						\
		"	.section .fixup,\"ax\"\n"		\
		"	.balign 4\n"				\
		"4:\n"						\
		"	li %0, %6\n"				\
		"	li %1, 0\n"				\
		"	li %2, 0\n"				\
		"	jump 3b, %3\n"				\
		"	.previous\n"				\
		"	.section __ex_table,\"a\"\n"		\
		"	.balign " RISCV_SZPTR "\n"			\
		"	" RISCV_PTR " 1b, 4b\n"			\
		"	" RISCV_PTR " 2b, 4b\n"			\
		"	.previous"				\
		: "+r" (err), "=&r" (__lo), "=r" (__hi),	\
			"=r" (__पंचांगp)				\
		: "m" (__ptr[__LSW]), "m" (__ptr[__MSW]),	\
			"i" (-EFAULT));				\
	(x) = (__typeof__(x))((__typeof__((x)-(x)))(		\
		(((u64)__hi << 32) | __lo)));			\
पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_64BIT */

#घोषणा __get_user_nocheck(x, __gu_ptr, __gu_err)		\
करो अणु								\
	चयन (माप(*__gu_ptr)) अणु				\
	हाल 1:							\
		__get_user_यंत्र("lb", (x), __gu_ptr, __gu_err);	\
		अवरोध;						\
	हाल 2:							\
		__get_user_यंत्र("lh", (x), __gu_ptr, __gu_err);	\
		अवरोध;						\
	हाल 4:							\
		__get_user_यंत्र("lw", (x), __gu_ptr, __gu_err);	\
		अवरोध;						\
	हाल 8:							\
		__get_user_8((x), __gu_ptr, __gu_err);	\
		अवरोध;						\
	शेष:						\
		BUILD_BUG();					\
	पूर्ण							\
पूर्ण जबतक (0)

/**
 * __get_user: - Get a simple variable from user space, with less checking.
 * @x:   Variable to store result.
 * @ptr: Source address, in user space.
 *
 * Context: User context only.  This function may sleep.
 *
 * This macro copies a single simple variable from user space to kernel
 * space.  It supports simple types like अक्षर and पूर्णांक, but not larger
 * data types like काष्ठाures or arrays.
 *
 * @ptr must have poपूर्णांकer-to-simple-variable type, and the result of
 * dereferencing @ptr must be assignable to @x without a cast.
 *
 * Caller must check the poपूर्णांकer with access_ok() beक्रमe calling this
 * function.
 *
 * Returns zero on success, or -EFAULT on error.
 * On error, the variable @x is set to zero.
 */
#घोषणा __get_user(x, ptr)					\
(अणु								\
	स्थिर __typeof__(*(ptr)) __user *__gu_ptr = (ptr);	\
	दीर्घ __gu_err = 0;					\
								\
	__chk_user_ptr(__gu_ptr);				\
								\
	__enable_user_access();					\
	__get_user_nocheck(x, __gu_ptr, __gu_err);		\
	__disable_user_access();				\
								\
	__gu_err;						\
पूर्ण)

/**
 * get_user: - Get a simple variable from user space.
 * @x:   Variable to store result.
 * @ptr: Source address, in user space.
 *
 * Context: User context only.  This function may sleep.
 *
 * This macro copies a single simple variable from user space to kernel
 * space.  It supports simple types like अक्षर and पूर्णांक, but not larger
 * data types like काष्ठाures or arrays.
 *
 * @ptr must have poपूर्णांकer-to-simple-variable type, and the result of
 * dereferencing @ptr must be assignable to @x without a cast.
 *
 * Returns zero on success, or -EFAULT on error.
 * On error, the variable @x is set to zero.
 */
#घोषणा get_user(x, ptr)					\
(अणु								\
	स्थिर __typeof__(*(ptr)) __user *__p = (ptr);		\
	might_fault();						\
	access_ok(__p, माप(*__p)) ?		\
		__get_user((x), __p) :				\
		((x) = 0, -EFAULT);				\
पूर्ण)

#घोषणा __put_user_यंत्र(insn, x, ptr, err)			\
करो अणु								\
	uपूर्णांकptr_t __पंचांगp;					\
	__typeof__(*(ptr)) __x = x;				\
	__यंत्र__ __अस्थिर__ (					\
		"1:\n"						\
		"	" insn " %z3, %2\n"			\
		"2:\n"						\
		"	.section .fixup,\"ax\"\n"		\
		"	.balign 4\n"				\
		"3:\n"						\
		"	li %0, %4\n"				\
		"	jump 2b, %1\n"				\
		"	.previous\n"				\
		"	.section __ex_table,\"a\"\n"		\
		"	.balign " RISCV_SZPTR "\n"			\
		"	" RISCV_PTR " 1b, 3b\n"			\
		"	.previous"				\
		: "+r" (err), "=r" (__पंचांगp), "=m" (*(ptr))	\
		: "rJ" (__x), "i" (-EFAULT));			\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_64BIT
#घोषणा __put_user_8(x, ptr, err) \
	__put_user_यंत्र("sd", x, ptr, err)
#अन्यथा /* !CONFIG_64BIT */
#घोषणा __put_user_8(x, ptr, err)				\
करो अणु								\
	u32 __user *__ptr = (u32 __user *)(ptr);		\
	u64 __x = (__typeof__((x)-(x)))(x);			\
	uपूर्णांकptr_t __पंचांगp;					\
	__यंत्र__ __अस्थिर__ (					\
		"1:\n"						\
		"	sw %z4, %2\n"				\
		"2:\n"						\
		"	sw %z5, %3\n"				\
		"3:\n"						\
		"	.section .fixup,\"ax\"\n"		\
		"	.balign 4\n"				\
		"4:\n"						\
		"	li %0, %6\n"				\
		"	jump 3b, %1\n"				\
		"	.previous\n"				\
		"	.section __ex_table,\"a\"\n"		\
		"	.balign " RISCV_SZPTR "\n"			\
		"	" RISCV_PTR " 1b, 4b\n"			\
		"	" RISCV_PTR " 2b, 4b\n"			\
		"	.previous"				\
		: "+r" (err), "=r" (__पंचांगp),			\
			"=m" (__ptr[__LSW]),			\
			"=m" (__ptr[__MSW])			\
		: "rJ" (__x), "rJ" (__x >> 32), "i" (-EFAULT));	\
पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_64BIT */

#घोषणा __put_user_nocheck(x, __gu_ptr, __pu_err)					\
करो अणु								\
	चयन (माप(*__gu_ptr)) अणु				\
	हाल 1:							\
		__put_user_यंत्र("sb", (x), __gu_ptr, __pu_err);	\
		अवरोध;						\
	हाल 2:							\
		__put_user_यंत्र("sh", (x), __gu_ptr, __pu_err);	\
		अवरोध;						\
	हाल 4:							\
		__put_user_यंत्र("sw", (x), __gu_ptr, __pu_err);	\
		अवरोध;						\
	हाल 8:							\
		__put_user_8((x), __gu_ptr, __pu_err);	\
		अवरोध;						\
	शेष:						\
		BUILD_BUG();					\
	पूर्ण							\
पूर्ण जबतक (0)

/**
 * __put_user: - Write a simple value पूर्णांकo user space, with less checking.
 * @x:   Value to copy to user space.
 * @ptr: Destination address, in user space.
 *
 * Context: User context only.  This function may sleep.
 *
 * This macro copies a single simple value from kernel space to user
 * space.  It supports simple types like अक्षर and पूर्णांक, but not larger
 * data types like काष्ठाures or arrays.
 *
 * @ptr must have poपूर्णांकer-to-simple-variable type, and @x must be assignable
 * to the result of dereferencing @ptr. The value of @x is copied to aव्योम
 * re-ordering where @x is evaluated inside the block that enables user-space
 * access (thus bypassing user space protection अगर @x is a function).
 *
 * Caller must check the poपूर्णांकer with access_ok() beक्रमe calling this
 * function.
 *
 * Returns zero on success, or -EFAULT on error.
 */
#घोषणा __put_user(x, ptr)					\
(अणु								\
	__typeof__(*(ptr)) __user *__gu_ptr = (ptr);		\
	__typeof__(*__gu_ptr) __val = (x);			\
	दीर्घ __pu_err = 0;					\
								\
	__chk_user_ptr(__gu_ptr);				\
								\
	__enable_user_access();					\
	__put_user_nocheck(__val, __gu_ptr, __pu_err);		\
	__disable_user_access();				\
								\
	__pu_err;						\
पूर्ण)

/**
 * put_user: - Write a simple value पूर्णांकo user space.
 * @x:   Value to copy to user space.
 * @ptr: Destination address, in user space.
 *
 * Context: User context only.  This function may sleep.
 *
 * This macro copies a single simple value from kernel space to user
 * space.  It supports simple types like अक्षर and पूर्णांक, but not larger
 * data types like काष्ठाures or arrays.
 *
 * @ptr must have poपूर्णांकer-to-simple-variable type, and @x must be assignable
 * to the result of dereferencing @ptr.
 *
 * Returns zero on success, or -EFAULT on error.
 */
#घोषणा put_user(x, ptr)					\
(अणु								\
	__typeof__(*(ptr)) __user *__p = (ptr);			\
	might_fault();						\
	access_ok(__p, माप(*__p)) ?		\
		__put_user((x), __p) :				\
		-EFAULT;					\
पूर्ण)


अचिन्हित दीर्घ __must_check __यंत्र_copy_to_user(व्योम __user *to,
	स्थिर व्योम *from, अचिन्हित दीर्घ n);
अचिन्हित दीर्घ __must_check __यंत्र_copy_from_user(व्योम *to,
	स्थिर व्योम __user *from, अचिन्हित दीर्घ n);

अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	वापस __यंत्र_copy_from_user(to, from, n);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	वापस __यंत्र_copy_to_user(to, from, n);
पूर्ण

बाह्य दीर्घ म_नकलन_from_user(अक्षर *dest, स्थिर अक्षर __user *src, दीर्घ count);

बाह्य दीर्घ __must_check strnlen_user(स्थिर अक्षर __user *str, दीर्घ n);

बाह्य
अचिन्हित दीर्घ __must_check __clear_user(व्योम __user *addr, अचिन्हित दीर्घ n);

अटल अंतरभूत
अचिन्हित दीर्घ __must_check clear_user(व्योम __user *to, अचिन्हित दीर्घ n)
अणु
	might_fault();
	वापस access_ok(to, n) ?
		__clear_user(to, n) : n;
पूर्ण

/*
 * Atomic compare-and-exchange, but with a fixup क्रम userspace faults.  Faults
 * will set "err" to -EFAULT, जबतक successful accesses वापस the previous
 * value.
 */
#घोषणा __cmpxchg_user(ptr, old, new, err, size, lrb, scb)	\
(अणु								\
	__typeof__(ptr) __ptr = (ptr);				\
	__typeof__(*(ptr)) __old = (old);			\
	__typeof__(*(ptr)) __new = (new);			\
	__typeof__(*(ptr)) __ret;				\
	__typeof__(err) __err = 0;				\
	रेजिस्टर अचिन्हित पूर्णांक __rc;				\
	__enable_user_access();					\
	चयन (size) अणु						\
	हाल 4:							\
		__यंत्र__ __अस्थिर__ (				\
		"0:\n"						\
		"	lr.w" #scb " %[ret], %[ptr]\n"		\
		"	bne          %[ret], %z[old], 1f\n"	\
		"	sc.w" #lrb " %[rc], %z[new], %[ptr]\n"	\
		"	bnez         %[rc], 0b\n"		\
		"1:\n"						\
		".section .fixup,\"ax\"\n"			\
		".balign 4\n"					\
		"2:\n"						\
		"	li %[err], %[efault]\n"			\
		"	jump 1b, %[rc]\n"			\
		".previous\n"					\
		".section __ex_table,\"a\"\n"			\
		".balign " RISCV_SZPTR "\n"			\
		"	" RISCV_PTR " 1b, 2b\n"			\
		".previous\n"					\
			: [ret] "=&r" (__ret),			\
			  [rc]  "=&r" (__rc),			\
			  [ptr] "+A" (*__ptr),			\
			  [err] "=&r" (__err)			\
			: [old] "rJ" (__old),			\
			  [new] "rJ" (__new),			\
			  [efault] "i" (-EFAULT));		\
		अवरोध;						\
	हाल 8:							\
		__यंत्र__ __अस्थिर__ (				\
		"0:\n"						\
		"	lr.d" #scb " %[ret], %[ptr]\n"		\
		"	bne          %[ret], %z[old], 1f\n"	\
		"	sc.d" #lrb " %[rc], %z[new], %[ptr]\n"	\
		"	bnez         %[rc], 0b\n"		\
		"1:\n"						\
		".section .fixup,\"ax\"\n"			\
		".balign 4\n"					\
		"2:\n"						\
		"	li %[err], %[efault]\n"			\
		"	jump 1b, %[rc]\n"			\
		".previous\n"					\
		".section __ex_table,\"a\"\n"			\
		".balign " RISCV_SZPTR "\n"			\
		"	" RISCV_PTR " 1b, 2b\n"			\
		".previous\n"					\
			: [ret] "=&r" (__ret),			\
			  [rc]  "=&r" (__rc),			\
			  [ptr] "+A" (*__ptr),			\
			  [err] "=&r" (__err)			\
			: [old] "rJ" (__old),			\
			  [new] "rJ" (__new),			\
			  [efault] "i" (-EFAULT));		\
		अवरोध;						\
	शेष:						\
		BUILD_BUG();					\
	पूर्ण							\
	__disable_user_access();				\
	(err) = __err;						\
	__ret;							\
पूर्ण)

#घोषणा HAVE_GET_KERNEL_NOFAULT

#घोषणा __get_kernel_nofault(dst, src, type, err_label)			\
करो अणु									\
	दीर्घ __kr_err;							\
									\
	__get_user_nocheck(*((type *)(dst)), (type *)(src), __kr_err);	\
	अगर (unlikely(__kr_err))						\
		जाओ err_label;						\
पूर्ण जबतक (0)

#घोषणा __put_kernel_nofault(dst, src, type, err_label)			\
करो अणु									\
	दीर्घ __kr_err;							\
									\
	__put_user_nocheck(*((type *)(src)), (type *)(dst), __kr_err);	\
	अगर (unlikely(__kr_err))						\
		जाओ err_label;						\
पूर्ण जबतक (0)

#अन्यथा /* CONFIG_MMU */
#समावेश <यंत्र-generic/uaccess.h>
#पूर्ण_अगर /* CONFIG_MMU */
#पूर्ण_अगर /* _ASM_RISCV_UACCESS_H */
