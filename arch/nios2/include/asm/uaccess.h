<शैली गुरु>
/*
 * User space memory access functions क्रम Nios II
 *
 * Copyright (C) 2010-2011, Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2009, Wind River Systems Inc
 *   Implemented by fredrik.markstrom@gmail.com and ivarholmqvist@gmail.com
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _ASM_NIOS2_UACCESS_H
#घोषणा _ASM_NIOS2_UACCESS_H

#समावेश <linux/माला.स>

#समावेश <यंत्र/page.h>

#समावेश <यंत्र/extable.h>

/*
 * Segment stuff
 */
#घोषणा MAKE_MM_SEG(s)		((mm_segment_t) अणु (s) पूर्ण)
#घोषणा USER_DS			MAKE_MM_SEG(0x80000000UL)
#घोषणा KERNEL_DS		MAKE_MM_SEG(0)


#घोषणा get_fs()		(current_thपढ़ो_info()->addr_limit)
#घोषणा set_fs(seg)		(current_thपढ़ो_info()->addr_limit = (seg))

#घोषणा uaccess_kernel() (get_fs().seg == KERNEL_DS.seg)

#घोषणा __access_ok(addr, len)			\
	(((चिन्हित दीर्घ)(((दीर्घ)get_fs().seg) &	\
		((दीर्घ)(addr) | (((दीर्घ)(addr)) + (len)) | (len)))) == 0)

#घोषणा access_ok(addr, len)		\
	likely(__access_ok((अचिन्हित दीर्घ)(addr), (अचिन्हित दीर्घ)(len)))

# define __EX_TABLE_SECTION	".section __ex_table,\"a\"\n"

#घोषणा user_addr_max() (uaccess_kernel() ? ~0UL : TASK_SIZE)

/*
 * Zero Userspace
 */

अटल अंतरभूत अचिन्हित दीर्घ __must_check __clear_user(व्योम __user *to,
						      अचिन्हित दीर्घ n)
अणु
	__यंत्र__ __अस्थिर__ (
		"1:     stb     zero, 0(%1)\n"
		"       addi    %0, %0, -1\n"
		"       addi    %1, %1, 1\n"
		"       bne     %0, zero, 1b\n"
		"2:\n"
		__EX_TABLE_SECTION
		".word  1b, 2b\n"
		".previous\n"
		: "=r" (n), "=r" (to)
		: "0" (n), "1" (to)
	);

	वापस n;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __must_check clear_user(व्योम __user *to,
						    अचिन्हित दीर्घ n)
अणु
	अगर (!access_ok(to, n))
		वापस n;
	वापस __clear_user(to, n);
पूर्ण

बाह्य अचिन्हित दीर्घ
raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n);
बाह्य अचिन्हित दीर्घ
raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n);
#घोषणा INLINE_COPY_FROM_USER
#घोषणा INLINE_COPY_TO_USER

बाह्य दीर्घ म_नकलन_from_user(अक्षर *__to, स्थिर अक्षर __user *__from,
			      दीर्घ __len);
बाह्य __must_check दीर्घ strnlen_user(स्थिर अक्षर __user *s, दीर्घ n);

/* Optimized macros */
#घोषणा __get_user_यंत्र(val, insn, addr, err)				\
अणु									\
	__यंत्र__ __अस्थिर__(						\
	"       movi    %0, %3\n"					\
	"1:   " insn " %1, 0(%2)\n"					\
	"       movi     %0, 0\n"					\
	"2:\n"								\
	"       .section __ex_table,\"a\"\n"				\
	"       .word 1b, 2b\n"						\
	"       .previous"						\
	: "=&r" (err), "=r" (val)					\
	: "r" (addr), "i" (-EFAULT));					\
पूर्ण

#घोषणा __get_user_unknown(val, size, ptr, err) करो अणु			\
	err = 0;							\
	अगर (__copy_from_user(&(val), ptr, size)) अणु			\
		err = -EFAULT;						\
	पूर्ण								\
	पूर्ण जबतक (0)

#घोषणा __get_user_common(val, size, ptr, err)				\
करो अणु									\
	चयन (size) अणु							\
	हाल 1:								\
		__get_user_यंत्र(val, "ldbu", ptr, err);			\
		अवरोध;							\
	हाल 2:								\
		__get_user_यंत्र(val, "ldhu", ptr, err);			\
		अवरोध;							\
	हाल 4:								\
		__get_user_यंत्र(val, "ldw", ptr, err);			\
		अवरोध;							\
	शेष:							\
		__get_user_unknown(val, size, ptr, err);		\
		अवरोध;							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा __get_user(x, ptr)						\
	(अणु								\
	दीर्घ __gu_err = -EFAULT;					\
	स्थिर __typeof__(*(ptr)) __user *__gu_ptr = (ptr);		\
	अचिन्हित दीर्घ __gu_val = 0;					\
	__get_user_common(__gu_val, माप(*(ptr)), __gu_ptr, __gu_err);\
	(x) = (__क्रमce __typeof__(x))__gu_val;				\
	__gu_err;							\
	पूर्ण)

#घोषणा get_user(x, ptr)						\
(अणु									\
	दीर्घ __gu_err = -EFAULT;					\
	स्थिर __typeof__(*(ptr)) __user *__gu_ptr = (ptr);		\
	अचिन्हित दीर्घ __gu_val = 0;					\
	अगर (access_ok( __gu_ptr, माप(*__gu_ptr)))	\
		__get_user_common(__gu_val, माप(*__gu_ptr),		\
			__gu_ptr, __gu_err);				\
	(x) = (__क्रमce __typeof__(x))__gu_val;				\
	__gu_err;							\
पूर्ण)

#घोषणा __put_user_यंत्र(val, insn, ptr, err)				\
अणु									\
	__यंत्र__ __अस्थिर__(						\
	"       movi    %0, %3\n"					\
	"1:   " insn " %1, 0(%2)\n"					\
	"       movi     %0, 0\n"					\
	"2:\n"								\
	"       .section __ex_table,\"a\"\n"				\
	"       .word 1b, 2b\n"						\
	"       .previous\n"						\
	: "=&r" (err)							\
	: "r" (val), "r" (ptr), "i" (-EFAULT));				\
पूर्ण

#घोषणा put_user(x, ptr)						\
(अणु									\
	दीर्घ __pu_err = -EFAULT;					\
	__typeof__(*(ptr)) __user *__pu_ptr = (ptr);			\
	__typeof__(*(ptr)) __pu_val = (__typeof(*ptr))(x);		\
	अगर (access_ok(__pu_ptr, माप(*__pu_ptr))) अणु	\
		चयन (माप(*__pu_ptr)) अणु				\
		हाल 1:							\
			__put_user_यंत्र(__pu_val, "stb", __pu_ptr, __pu_err); \
			अवरोध;						\
		हाल 2:							\
			__put_user_यंत्र(__pu_val, "sth", __pu_ptr, __pu_err); \
			अवरोध;						\
		हाल 4:							\
			__put_user_यंत्र(__pu_val, "stw", __pu_ptr, __pu_err); \
			अवरोध;						\
		शेष:						\
			/* XXX: This looks wrong... */			\
			__pu_err = 0;					\
			अगर (copy_to_user(__pu_ptr, &(__pu_val),		\
				माप(*__pu_ptr)))			\
				__pu_err = -EFAULT;			\
			अवरोध;						\
		पूर्ण							\
	पूर्ण								\
	__pu_err;							\
पूर्ण)

#घोषणा __put_user(x, ptr) put_user(x, ptr)

#पूर्ण_अगर /* _ASM_NIOS2_UACCESS_H */
