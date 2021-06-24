<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित _ASMANDES_UACCESS_H
#घोषणा _ASMANDES_UACCESS_H

/*
 * User space memory access functions
 */
#समावेश <linux/sched.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/types.h>

#घोषणा __यंत्रeq(x, y)  ".ifnc " x "," y " ; .err ; .endif\n\t"

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

काष्ठा exception_table_entry अणु
	अचिन्हित दीर्घ insn, fixup;
पूर्ण;

बाह्य पूर्णांक fixup_exception(काष्ठा pt_regs *regs);

#घोषणा KERNEL_DS 	((mm_segment_t) अणु ~0UL पूर्ण)
#घोषणा USER_DS		((mm_segment_t) अणुTASK_SIZE - 1पूर्ण)

#घोषणा get_fs()	(current_thपढ़ो_info()->addr_limit)
#घोषणा user_addr_max	get_fs

अटल अंतरभूत व्योम set_fs(mm_segment_t fs)
अणु
	current_thपढ़ो_info()->addr_limit = fs;
पूर्ण

#घोषणा uaccess_kernel()	(get_fs() == KERNEL_DS)

#घोषणा __range_ok(addr, size) (size <= get_fs() && addr <= (get_fs() -size))

#घोषणा access_ok(addr, size)	\
	__range_ok((अचिन्हित दीर्घ)addr, (अचिन्हित दीर्घ)size)
/*
 * Single-value transfer routines.  They स्वतःmatically use the right
 * size अगर we just have the right poपूर्णांकer type.  Note that the functions
 * which पढ़ो from user space (*get_*) need to take care not to leak
 * kernel data even अगर the calling code is buggy and fails to check
 * the वापस value.  This means zeroing out the destination variable
 * or buffer on error.  Normally this is करोne out of line by the
 * fixup code, but there are a few places where it पूर्णांकrudes on the
 * मुख्य code path.  When we only ग_लिखो to user space, there is no
 * problem.
 *
 * The "__xxx" versions of the user access functions करो not verअगरy the
 * address space - it must have been करोne previously with a separate
 * "access_ok()" call.
 *
 * The "xxx_error" versions set the third argument to EFAULT अगर an
 * error occurs, and leave it unchanged on success.  Note that these
 * versions are व्योम (ie, करोn't वापस a value as such).
 */

#घोषणा get_user	__get_user					\

#घोषणा __get_user(x, ptr)						\
(अणु									\
	दीर्घ __gu_err = 0;						\
	__get_user_check((x), (ptr), __gu_err);				\
	__gu_err;							\
पूर्ण)

#घोषणा __get_user_error(x, ptr, err)					\
(अणु									\
	__get_user_check((x), (ptr), (err));				\
	(व्योम)0;							\
पूर्ण)

#घोषणा __get_user_check(x, ptr, err)					\
(अणु									\
	स्थिर __typeof__(*(ptr)) __user *__p = (ptr);			\
	might_fault();							\
	अगर (access_ok(__p, माप(*__p))) अणु		\
		__get_user_err((x), __p, (err));			\
	पूर्ण अन्यथा अणु							\
		(x) = 0; (err) = -EFAULT;				\
	पूर्ण								\
पूर्ण)

#घोषणा __get_user_err(x, ptr, err)					\
करो अणु									\
	अचिन्हित दीर्घ __gu_val;						\
	__chk_user_ptr(ptr);						\
	चयन (माप(*(ptr))) अणु					\
	हाल 1:								\
		__get_user_यंत्र("lbi", __gu_val, (ptr), (err));		\
		अवरोध;							\
	हाल 2:								\
		__get_user_यंत्र("lhi", __gu_val, (ptr), (err));		\
		अवरोध;							\
	हाल 4:								\
		__get_user_यंत्र("lwi", __gu_val, (ptr), (err));		\
		अवरोध;							\
	हाल 8:								\
		__get_user_यंत्र_dword(__gu_val, (ptr), (err));		\
		अवरोध;							\
	शेष:							\
		BUILD_BUG(); 						\
		अवरोध;							\
	पूर्ण								\
	(x) = (__क्रमce __typeof__(*(ptr)))__gu_val;			\
पूर्ण जबतक (0)

#घोषणा __get_user_यंत्र(inst, x, addr, err)				\
	__यंत्र__ __अस्थिर__ (						\
		"1:	"inst"	%1,[%2]\n"				\
		"2:\n"							\
		"	.section .fixup,\"ax\"\n"			\
		"	.align	2\n"					\
		"3:	move %0, %3\n"					\
		"	move %1, #0\n"					\
		"	b	2b\n"					\
		"	.previous\n"					\
		"	.section __ex_table,\"a\"\n"			\
		"	.align	3\n"					\
		"	.long	1b, 3b\n"				\
		"	.previous"					\
		: "+r" (err), "=&r" (x)					\
		: "r" (addr), "i" (-EFAULT)				\
		: "cc")

#अगर_घोषित __NDS32_EB__
#घोषणा __gu_reg_oper0 "%H1"
#घोषणा __gu_reg_oper1 "%L1"
#अन्यथा
#घोषणा __gu_reg_oper0 "%L1"
#घोषणा __gu_reg_oper1 "%H1"
#पूर्ण_अगर

#घोषणा __get_user_यंत्र_dword(x, addr, err) 				\
	__यंत्र__ __अस्थिर__ (						\
		"\n1:\tlwi " __gu_reg_oper0 ",[%2]\n"			\
		"\n2:\tlwi " __gu_reg_oper1 ",[%2+4]\n"			\
		"3:\n"							\
		"	.section .fixup,\"ax\"\n"			\
		"	.align	2\n"					\
		"4:	move	%0, %3\n"				\
		"	b	3b\n"					\
		"	.previous\n"					\
		"	.section __ex_table,\"a\"\n"			\
		"	.align	3\n"					\
		"	.long	1b, 4b\n"				\
		"	.long	2b, 4b\n"				\
		"	.previous"					\
		: "+r"(err), "=&r"(x)					\
		: "r"(addr), "i"(-EFAULT)				\
		: "cc")

#घोषणा put_user	__put_user					\

#घोषणा __put_user(x, ptr)						\
(अणु									\
	दीर्घ __pu_err = 0;						\
	__put_user_err((x), (ptr), __pu_err);				\
	__pu_err;							\
पूर्ण)

#घोषणा __put_user_error(x, ptr, err)					\
(अणु									\
	__put_user_err((x), (ptr), (err));				\
	(व्योम)0;							\
पूर्ण)

#घोषणा __put_user_check(x, ptr, err)					\
(अणु									\
	__typeof__(*(ptr)) __user *__p = (ptr);				\
	might_fault();							\
	अगर (access_ok(__p, माप(*__p))) अणु		\
		__put_user_err((x), __p, (err));			\
	पूर्ण अन्यथा	अणु							\
		(err) = -EFAULT;					\
	पूर्ण								\
पूर्ण)

#घोषणा __put_user_err(x, ptr, err)					\
करो अणु									\
	__typeof__(*(ptr)) __pu_val = (x);				\
	__chk_user_ptr(ptr);						\
	चयन (माप(*(ptr))) अणु					\
	हाल 1:								\
		__put_user_यंत्र("sbi", __pu_val, (ptr), (err));		\
		अवरोध;							\
	हाल 2: 							\
		__put_user_यंत्र("shi", __pu_val, (ptr), (err));		\
		अवरोध;							\
	हाल 4: 							\
		__put_user_यंत्र("swi", __pu_val, (ptr), (err));		\
		अवरोध;							\
	हाल 8:								\
		__put_user_यंत्र_dword(__pu_val, (ptr), (err));		\
		अवरोध;							\
	शेष:							\
		BUILD_BUG(); 						\
		अवरोध;							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा __put_user_यंत्र(inst, x, addr, err)				\
	__यंत्र__ __अस्थिर__ (						\
		"1:	"inst"	%1,[%2]\n"				\
		"2:\n"							\
		"	.section .fixup,\"ax\"\n"			\
		"	.align	2\n"					\
		"3:	move	%0, %3\n"				\
		"	b	2b\n"					\
		"	.previous\n"					\
		"	.section __ex_table,\"a\"\n"			\
		"	.align	3\n"					\
		"	.long	1b, 3b\n"				\
		"	.previous"					\
		: "+r" (err)						\
		: "r" (x), "r" (addr), "i" (-EFAULT)			\
		: "cc")

#अगर_घोषित __NDS32_EB__
#घोषणा __pu_reg_oper0 "%H2"
#घोषणा __pu_reg_oper1 "%L2"
#अन्यथा
#घोषणा __pu_reg_oper0 "%L2"
#घोषणा __pu_reg_oper1 "%H2"
#पूर्ण_अगर

#घोषणा __put_user_यंत्र_dword(x, addr, err) 				\
	__यंत्र__ __अस्थिर__ (						\
		"\n1:\tswi " __pu_reg_oper0 ",[%1]\n"			\
		"\n2:\tswi " __pu_reg_oper1 ",[%1+4]\n"			\
		"3:\n"							\
		"	.section .fixup,\"ax\"\n"			\
		"	.align	2\n"					\
		"4:	move	%0, %3\n"				\
		"	b	3b\n"					\
		"	.previous\n"					\
		"	.section __ex_table,\"a\"\n"			\
		"	.align	3\n"					\
		"	.long	1b, 4b\n"				\
		"	.long	2b, 4b\n"				\
		"	.previous"					\
		: "+r"(err)						\
		: "r"(addr), "r"(x), "i"(-EFAULT)			\
		: "cc")

बाह्य अचिन्हित दीर्घ __arch_clear_user(व्योम __user * addr, अचिन्हित दीर्घ n);
बाह्य दीर्घ म_नकलन_from_user(अक्षर *dest, स्थिर अक्षर __user * src, दीर्घ count);
बाह्य __must_check दीर्घ strnlen_user(स्थिर अक्षर __user * str, दीर्घ n);
बाह्य अचिन्हित दीर्घ __arch_copy_from_user(व्योम *to, स्थिर व्योम __user * from,
                                           अचिन्हित दीर्घ n);
बाह्य अचिन्हित दीर्घ __arch_copy_to_user(व्योम __user * to, स्थिर व्योम *from,
                                         अचिन्हित दीर्घ n);

#घोषणा raw_copy_from_user __arch_copy_from_user
#घोषणा raw_copy_to_user __arch_copy_to_user

#घोषणा INLINE_COPY_FROM_USER
#घोषणा INLINE_COPY_TO_USER
अटल अंतरभूत अचिन्हित दीर्घ clear_user(व्योम __user * to, अचिन्हित दीर्घ n)
अणु
	अगर (access_ok(to, n))
		n = __arch_clear_user(to, n);
	वापस n;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __clear_user(व्योम __user * to, अचिन्हित दीर्घ n)
अणु
	वापस __arch_clear_user(to, n);
पूर्ण

#पूर्ण_अगर /* _ASMNDS32_UACCESS_H */
