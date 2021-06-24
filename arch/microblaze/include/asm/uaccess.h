<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */

#अगर_अघोषित _ASM_MICROBLAZE_UACCESS_H
#घोषणा _ASM_MICROBLAZE_UACCESS_H

#समावेश <linux/kernel.h>

#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/page.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/extable.h>
#समावेश <linux/माला.स>

/*
 * On Microblaze the fs value is actually the top of the corresponding
 * address space.
 *
 * The fs value determines whether argument validity checking should be
 * perक्रमmed or not. If get_fs() == USER_DS, checking is perक्रमmed, with
 * get_fs() == KERNEL_DS, checking is bypassed.
 *
 * For historical reasons, these macros are grossly misnamed.
 *
 * For non-MMU arch like Microblaze, KERNEL_DS and USER_DS is equal.
 */
# define MAKE_MM_SEG(s)       ((mm_segment_t) अणु (s) पूर्ण)

#  define KERNEL_DS	MAKE_MM_SEG(0xFFFFFFFF)
#  define USER_DS	MAKE_MM_SEG(TASK_SIZE - 1)

# define get_fs()	(current_thपढ़ो_info()->addr_limit)
# define set_fs(val)	(current_thपढ़ो_info()->addr_limit = (val))

# define uaccess_kernel()	(get_fs().seg == KERNEL_DS.seg)

अटल अंतरभूत पूर्णांक access_ok(स्थिर व्योम __user *addr, अचिन्हित दीर्घ size)
अणु
	अगर (!size)
		जाओ ok;

	अगर ((get_fs().seg < ((अचिन्हित दीर्घ)addr)) ||
			(get_fs().seg < ((अचिन्हित दीर्घ)addr + size - 1))) अणु
		pr_devel("ACCESS fail at 0x%08x (size 0x%x), seg 0x%08x\n",
			(__क्रमce u32)addr, (u32)size,
			(u32)get_fs().seg);
		वापस 0;
	पूर्ण
ok:
	pr_devel("ACCESS OK at 0x%08x (size 0x%x), seg 0x%08x\n",
			(__क्रमce u32)addr, (u32)size,
			(u32)get_fs().seg);
	वापस 1;
पूर्ण

# define __FIXUP_SECTION	".section .fixup,\"ax\"\n"
# define __EX_TABLE_SECTION	".section __ex_table,\"a\"\n"

बाह्य अचिन्हित दीर्घ __copy_tofrom_user(व्योम __user *to,
		स्थिर व्योम __user *from, अचिन्हित दीर्घ size);

/* Return: number of not copied bytes, i.e. 0 अगर OK or non-zero अगर fail. */
अटल अंतरभूत अचिन्हित दीर्घ __must_check __clear_user(व्योम __user *to,
							अचिन्हित दीर्घ n)
अणु
	/* normal स_रखो with two words to __ex_table */
	__यंत्र__ __अस्थिर__ (				\
			"1:	sb	r0, %1, r0;"	\
			"	addik	%0, %0, -1;"	\
			"	bneid	%0, 1b;"	\
			"	addik	%1, %1, 1;"	\
			"2:			"	\
			__EX_TABLE_SECTION		\
			".word	1b,2b;"			\
			".previous;"			\
		: "=r"(n), "=r"(to)			\
		: "0"(n), "1"(to)
	);
	वापस n;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __must_check clear_user(व्योम __user *to,
							अचिन्हित दीर्घ n)
अणु
	might_fault();
	अगर (unlikely(!access_ok(to, n)))
		वापस n;

	वापस __clear_user(to, n);
पूर्ण

/* put_user and get_user macros */
बाह्य दीर्घ __user_bad(व्योम);

#घोषणा __get_user_यंत्र(insn, __gu_ptr, __gu_val, __gu_err)	\
(अणु								\
	__यंत्र__ __अस्थिर__ (					\
			"1:"	insn	" %1, %2, r0;"		\
			"	addk	%0, r0, r0;"		\
			"2:			"		\
			__FIXUP_SECTION				\
			"3:	brid	2b;"			\
			"	addik	%0, r0, %3;"		\
			".previous;"				\
			__EX_TABLE_SECTION			\
			".word	1b,3b;"				\
			".previous;"				\
		: "=&r"(__gu_err), "=r"(__gu_val)		\
		: "r"(__gu_ptr), "i"(-EFAULT)			\
	);							\
पूर्ण)

/**
 * get_user: - Get a simple variable from user space.
 * @x:   Variable to store result.
 * @ptr: Source address, in user space.
 *
 * Context: User context only. This function may sleep अगर pagefaults are
 *          enabled.
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
#घोषणा get_user(x, ptr) (अणु				\
	स्थिर typeof(*(ptr)) __user *__gu_ptr = (ptr);	\
	access_ok(__gu_ptr, माप(*__gu_ptr)) ?	\
		__get_user(x, __gu_ptr) : -EFAULT;	\
पूर्ण)

#घोषणा __get_user(x, ptr)						\
(अणु									\
	अचिन्हित दीर्घ __gu_val = 0;					\
	दीर्घ __gu_err;							\
	चयन (माप(*(ptr))) अणु					\
	हाल 1:								\
		__get_user_यंत्र("lbu", (ptr), __gu_val, __gu_err);	\
		अवरोध;							\
	हाल 2:								\
		__get_user_यंत्र("lhu", (ptr), __gu_val, __gu_err);	\
		अवरोध;							\
	हाल 4:								\
		__get_user_यंत्र("lw", (ptr), __gu_val, __gu_err);	\
		अवरोध;							\
	हाल 8:								\
		__gu_err = __copy_from_user(&__gu_val, ptr, 8);		\
		अगर (__gu_err)						\
			__gu_err = -EFAULT;				\
		अवरोध;							\
	शेष:							\
		/* __gu_val = 0; __gu_err = -EINVAL;*/ __gu_err = __user_bad();\
	पूर्ण								\
	x = (__क्रमce __typeof__(*(ptr))) __gu_val;			\
	__gu_err;							\
पूर्ण)


#घोषणा __put_user_यंत्र(insn, __gu_ptr, __gu_val, __gu_err)	\
(अणु								\
	__यंत्र__ __अस्थिर__ (					\
			"1:"	insn	" %1, %2, r0;"		\
			"	addk	%0, r0, r0;"		\
			"2:			"		\
			__FIXUP_SECTION				\
			"3:	brid	2b;"			\
			"	addik	%0, r0, %3;"		\
			".previous;"				\
			__EX_TABLE_SECTION			\
			".word	1b,3b;"				\
			".previous;"				\
		: "=&r"(__gu_err)				\
		: "r"(__gu_val), "r"(__gu_ptr), "i"(-EFAULT)	\
	);							\
पूर्ण)

#घोषणा __put_user_यंत्र_8(__gu_ptr, __gu_val, __gu_err)		\
(अणु								\
	__यंत्र__ __अस्थिर__ ("	lwi	%0, %1, 0;"		\
			"1:	swi	%0, %2, 0;"		\
			"	lwi	%0, %1, 4;"		\
			"2:	swi	%0, %2, 4;"		\
			"	addk	%0, r0, r0;"		\
			"3:			"		\
			__FIXUP_SECTION				\
			"4:	brid	3b;"			\
			"	addik	%0, r0, %3;"		\
			".previous;"				\
			__EX_TABLE_SECTION			\
			".word	1b,4b,2b,4b;"			\
			".previous;"				\
		: "=&r"(__gu_err)				\
		: "r"(&__gu_val), "r"(__gu_ptr), "i"(-EFAULT)	\
		);						\
पूर्ण)

/**
 * put_user: - Write a simple value पूर्णांकo user space.
 * @x:   Value to copy to user space.
 * @ptr: Destination address, in user space.
 *
 * Context: User context only. This function may sleep अगर pagefaults are
 *          enabled.
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
#घोषणा put_user(x, ptr)						\
	__put_user_check((x), (ptr), माप(*(ptr)))

#घोषणा __put_user_check(x, ptr, size)					\
(अणु									\
	typeof(*(ptr)) अस्थिर __pu_val = x;				\
	typeof(*(ptr)) __user *__pu_addr = (ptr);			\
	पूर्णांक __pu_err = 0;						\
									\
	अगर (access_ok(__pu_addr, size)) अणु			\
		चयन (size) अणु						\
		हाल 1:							\
			__put_user_यंत्र("sb", __pu_addr, __pu_val,	\
				       __pu_err);			\
			अवरोध;						\
		हाल 2:							\
			__put_user_यंत्र("sh", __pu_addr, __pu_val,	\
				       __pu_err);			\
			अवरोध;						\
		हाल 4:							\
			__put_user_यंत्र("sw", __pu_addr, __pu_val,	\
				       __pu_err);			\
			अवरोध;						\
		हाल 8:							\
			__put_user_यंत्र_8(__pu_addr, __pu_val, __pu_err);\
			अवरोध;						\
		शेष:						\
			__pu_err = __user_bad();			\
			अवरोध;						\
		पूर्ण							\
	पूर्ण अन्यथा अणु							\
		__pu_err = -EFAULT;					\
	पूर्ण								\
	__pu_err;							\
पूर्ण)

#घोषणा __put_user(x, ptr)						\
(अणु									\
	__typeof__(*(ptr)) अस्थिर __gu_val = (x);			\
	दीर्घ __gu_err = 0;						\
	चयन (माप(__gu_val)) अणु					\
	हाल 1:								\
		__put_user_यंत्र("sb", (ptr), __gu_val, __gu_err);	\
		अवरोध;							\
	हाल 2:								\
		__put_user_यंत्र("sh", (ptr), __gu_val, __gu_err);	\
		अवरोध;							\
	हाल 4:								\
		__put_user_यंत्र("sw", (ptr), __gu_val, __gu_err);	\
		अवरोध;							\
	हाल 8:								\
		__put_user_यंत्र_8((ptr), __gu_val, __gu_err);		\
		अवरोध;							\
	शेष:							\
		/*__gu_err = -EINVAL;*/	__gu_err = __user_bad();	\
	पूर्ण								\
	__gu_err;							\
पूर्ण)

अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	वापस __copy_tofrom_user((__क्रमce व्योम __user *)to, from, n);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	वापस __copy_tofrom_user(to, (__क्रमce स्थिर व्योम __user *)from, n);
पूर्ण
#घोषणा INLINE_COPY_FROM_USER
#घोषणा INLINE_COPY_TO_USER

/*
 * Copy a null terminated string from userspace.
 */
बाह्य पूर्णांक __म_नकलन_user(अक्षर *to, स्थिर अक्षर __user *from, पूर्णांक len);

अटल अंतरभूत दीर्घ
म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src, दीर्घ count)
अणु
	अगर (!access_ok(src, 1))
		वापस -EFAULT;
	वापस __म_नकलन_user(dst, src, count);
पूर्ण

/*
 * Return the size of a string (including the ending 0)
 *
 * Return 0 on exception, a value greater than N अगर too दीर्घ
 */
बाह्य पूर्णांक __strnlen_user(स्थिर अक्षर __user *sstr, पूर्णांक len);

अटल अंतरभूत दीर्घ strnlen_user(स्थिर अक्षर __user *src, दीर्घ n)
अणु
	अगर (!access_ok(src, 1))
		वापस 0;
	वापस __strnlen_user(src, n);
पूर्ण

#पूर्ण_अगर /* _ASM_MICROBLAZE_UACCESS_H */
