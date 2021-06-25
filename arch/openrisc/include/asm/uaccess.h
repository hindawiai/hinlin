<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */

#अगर_अघोषित __ASM_OPENRISC_UACCESS_H
#घोषणा __ASM_OPENRISC_UACCESS_H

/*
 * User space memory access functions
 */
#समावेश <linux/prefetch.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/extable.h>

/*
 * The fs value determines whether argument validity checking should be
 * perक्रमmed or not.  If get_fs() == USER_DS, checking is perक्रमmed, with
 * get_fs() == KERNEL_DS, checking is bypassed.
 *
 * For historical reasons, these macros are grossly misnamed.
 */

/* addr_limit is the maximum accessible address क्रम the task. we misuse
 * the KERNEL_DS and USER_DS values to both assign and compare the
 * addr_limit values through the equally misnamed get/set_fs macros.
 * (see above)
 */

#घोषणा KERNEL_DS	(~0UL)

#घोषणा USER_DS		(TASK_SIZE)
#घोषणा get_fs()	(current_thपढ़ो_info()->addr_limit)
#घोषणा set_fs(x)	(current_thपढ़ो_info()->addr_limit = (x))

#घोषणा uaccess_kernel()	(get_fs() == KERNEL_DS)

/* Ensure that the range from addr to addr+size is all within the process'
 * address space
 */
अटल अंतरभूत पूर्णांक __range_ok(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	स्थिर mm_segment_t fs = get_fs();

	वापस size <= fs && addr <= (fs - size);
पूर्ण

#घोषणा access_ok(addr, size)						\
(अणु 									\
	__chk_user_ptr(addr);						\
	__range_ok((अचिन्हित दीर्घ)(addr), (size));			\
पूर्ण)

/*
 * These are the मुख्य single-value transfer routines.  They स्वतःmatically
 * use the right size अगर we just have the right poपूर्णांकer type.
 *
 * This माला_लो kind of ugly. We want to वापस _two_ values in "get_user()"
 * and yet we करोn't want to करो any poपूर्णांकers, because that is too much
 * of a perक्रमmance impact. Thus we have a few rather ugly macros here,
 * and hide all the uglyness from the user.
 *
 * The "__xxx" versions of the user access functions are versions that
 * करो not verअगरy the address space, that must have been करोne previously
 * with a separate "access_ok()" call (this is used when we करो multiple
 * accesses to the same area of user memory).
 *
 * As we use the same address space क्रम kernel and user data on the
 * PowerPC, we can just करो these as direct assignments.  (Of course, the
 * exception handling means that it's no दीर्घer "just"...)
 */
#घोषणा get_user(x, ptr) \
	__get_user_check((x), (ptr), माप(*(ptr)))
#घोषणा put_user(x, ptr) \
	__put_user_check((__typeof__(*(ptr)))(x), (ptr), माप(*(ptr)))

#घोषणा __get_user(x, ptr) \
	__get_user_nocheck((x), (ptr), माप(*(ptr)))
#घोषणा __put_user(x, ptr) \
	__put_user_nocheck((__typeof__(*(ptr)))(x), (ptr), माप(*(ptr)))

बाह्य दीर्घ __put_user_bad(व्योम);

#घोषणा __put_user_nocheck(x, ptr, size)		\
(अणु							\
	दीर्घ __pu_err;					\
	__put_user_size((x), (ptr), (size), __pu_err);	\
	__pu_err;					\
पूर्ण)

#घोषणा __put_user_check(x, ptr, size)					\
(अणु									\
	दीर्घ __pu_err = -EFAULT;					\
	__typeof__(*(ptr)) __user *__pu_addr = (ptr);			\
	अगर (access_ok(__pu_addr, size))			\
		__put_user_size((x), __pu_addr, (size), __pu_err);	\
	__pu_err;							\
पूर्ण)

#घोषणा __put_user_size(x, ptr, size, retval)				\
करो अणु									\
	retval = 0;							\
	चयन (size) अणु							\
	हाल 1: __put_user_यंत्र(x, ptr, retval, "l.sb"); अवरोध;		\
	हाल 2: __put_user_यंत्र(x, ptr, retval, "l.sh"); अवरोध;		\
	हाल 4: __put_user_यंत्र(x, ptr, retval, "l.sw"); अवरोध;		\
	हाल 8: __put_user_यंत्र2(x, ptr, retval); अवरोध;			\
	शेष: __put_user_bad();					\
	पूर्ण								\
पूर्ण जबतक (0)

काष्ठा __large_काष्ठा अणु
	अचिन्हित दीर्घ buf[100];
पूर्ण;
#घोषणा __m(x) (*(काष्ठा __large_काष्ठा *)(x))

/*
 * We करोn't tell gcc that we are accessing memory, but this is OK
 * because we करो not ग_लिखो to any memory gcc knows about, so there
 * are no aliasing issues.
 */
#घोषणा __put_user_यंत्र(x, addr, err, op)			\
	__यंत्र__ __अस्थिर__(					\
		"1:	"op" 0(%2),%1\n"			\
		"2:\n"						\
		".section .fixup,\"ax\"\n"			\
		"3:	l.addi %0,r0,%3\n"			\
		"	l.j 2b\n"				\
		"	l.nop\n"				\
		".previous\n"					\
		".section __ex_table,\"a\"\n"			\
		"	.align 2\n"				\
		"	.long 1b,3b\n"				\
		".previous"					\
		: "=r"(err)					\
		: "r"(x), "r"(addr), "i"(-EFAULT), "0"(err))

#घोषणा __put_user_यंत्र2(x, addr, err)				\
	__यंत्र__ __अस्थिर__(					\
		"1:	l.sw 0(%2),%1\n"			\
		"2:	l.sw 4(%2),%H1\n"			\
		"3:\n"						\
		".section .fixup,\"ax\"\n"			\
		"4:	l.addi %0,r0,%3\n"			\
		"	l.j 3b\n"				\
		"	l.nop\n"				\
		".previous\n"					\
		".section __ex_table,\"a\"\n"			\
		"	.align 2\n"				\
		"	.long 1b,4b\n"				\
		"	.long 2b,4b\n"				\
		".previous"					\
		: "=r"(err)					\
		: "r"(x), "r"(addr), "i"(-EFAULT), "0"(err))

#घोषणा __get_user_nocheck(x, ptr, size)			\
(अणु								\
	दीर्घ __gu_err;						\
	__get_user_size((x), (ptr), (size), __gu_err);		\
	__gu_err;						\
पूर्ण)

#घोषणा __get_user_check(x, ptr, size)					\
(अणु									\
	दीर्घ __gu_err = -EFAULT;					\
	स्थिर __typeof__(*(ptr)) __user *__gu_addr = (ptr);		\
	अगर (access_ok(__gu_addr, size))					\
		__get_user_size((x), __gu_addr, (size), __gu_err);	\
	अन्यथा								\
		(x) = (__typeof__(*(ptr))) 0;				\
	__gu_err;							\
पूर्ण)

बाह्य दीर्घ __get_user_bad(व्योम);

#घोषणा __get_user_size(x, ptr, size, retval)				\
करो अणु									\
	retval = 0;							\
	चयन (size) अणु							\
	हाल 1: __get_user_यंत्र(x, ptr, retval, "l.lbz"); अवरोध;		\
	हाल 2: __get_user_यंत्र(x, ptr, retval, "l.lhz"); अवरोध;		\
	हाल 4: __get_user_यंत्र(x, ptr, retval, "l.lwz"); अवरोध;		\
	हाल 8: __get_user_यंत्र2(x, ptr, retval); अवरोध;			\
	शेष: (x) = (__typeof__(*(ptr)))__get_user_bad();		\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा __get_user_यंत्र(x, addr, err, op)		\
अणु							\
	अचिन्हित दीर्घ __gu_पंचांगp;				\
	__यंत्र__ __अस्थिर__(				\
		"1:	"op" %1,0(%2)\n"		\
		"2:\n"					\
		".section .fixup,\"ax\"\n"		\
		"3:	l.addi %0,r0,%3\n"		\
		"	l.addi %1,r0,0\n"		\
		"	l.j 2b\n"			\
		"	l.nop\n"			\
		".previous\n"				\
		".section __ex_table,\"a\"\n"		\
		"	.align 2\n"			\
		"	.long 1b,3b\n"			\
		".previous"				\
		: "=r"(err), "=r"(__gu_पंचांगp)		\
		: "r"(addr), "i"(-EFAULT), "0"(err));	\
	(x) = (__typeof__(*(addr)))__gu_पंचांगp;		\
पूर्ण

#घोषणा __get_user_यंत्र2(x, addr, err)			\
अणु							\
	अचिन्हित दीर्घ दीर्घ __gu_पंचांगp;			\
	__यंत्र__ __अस्थिर__(				\
		"1:	l.lwz %1,0(%2)\n"		\
		"2:	l.lwz %H1,4(%2)\n"		\
		"3:\n"					\
		".section .fixup,\"ax\"\n"		\
		"4:	l.addi %0,r0,%3\n"		\
		"	l.addi %1,r0,0\n"		\
		"	l.addi %H1,r0,0\n"		\
		"	l.j 3b\n"			\
		"	l.nop\n"			\
		".previous\n"				\
		".section __ex_table,\"a\"\n"		\
		"	.align 2\n"			\
		"	.long 1b,4b\n"			\
		"	.long 2b,4b\n"			\
		".previous"				\
		: "=r"(err), "=&r"(__gu_पंचांगp)		\
		: "r"(addr), "i"(-EFAULT), "0"(err));	\
	(x) = (__typeof__(*(addr)))(			\
		(__typeof__((x)-(x)))__gu_पंचांगp);		\
पूर्ण

/* more complex routines */

बाह्य अचिन्हित दीर्घ __must_check
__copy_tofrom_user(व्योम *to, स्थिर व्योम *from, अचिन्हित दीर्घ size);
अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ size)
अणु
	वापस __copy_tofrom_user(to, (__क्रमce स्थिर व्योम *)from, size);
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ size)
अणु
	वापस __copy_tofrom_user((__क्रमce व्योम *)to, from, size);
पूर्ण
#घोषणा INLINE_COPY_FROM_USER
#घोषणा INLINE_COPY_TO_USER

बाह्य अचिन्हित दीर्घ __clear_user(व्योम __user *addr, अचिन्हित दीर्घ size);

अटल अंतरभूत __must_check अचिन्हित दीर्घ
clear_user(व्योम __user *addr, अचिन्हित दीर्घ size)
अणु
	अगर (likely(access_ok(addr, size)))
		size = __clear_user(addr, size);
	वापस size;
पूर्ण

#घोषणा user_addr_max() \
	(uaccess_kernel() ? ~0UL : TASK_SIZE)

बाह्य दीर्घ म_नकलन_from_user(अक्षर *dest, स्थिर अक्षर __user *src, दीर्घ count);

बाह्य __must_check दीर्घ strnlen_user(स्थिर अक्षर __user *str, दीर्घ n);

#पूर्ण_अगर /* __ASM_OPENRISC_UACCESS_H */
