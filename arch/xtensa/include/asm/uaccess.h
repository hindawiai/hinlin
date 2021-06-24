<शैली गुरु>
/*
 * include/यंत्र-xtensa/uaccess.h
 *
 * User space memory access functions
 *
 * These routines provide basic accessing functions to the user memory
 * space क्रम the kernel. This header file provides functions such as:
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_UACCESS_H
#घोषणा _XTENSA_UACCESS_H

#समावेश <linux/prefetch.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/extable.h>

/*
 * The fs value determines whether argument validity checking should
 * be perक्रमmed or not.  If get_fs() == USER_DS, checking is
 * perक्रमmed, with get_fs() == KERNEL_DS, checking is bypassed.
 *
 * For historical reasons (Data Segment Register?), these macros are
 * grossly misnamed.
 */

#घोषणा KERNEL_DS	((mm_segment_t) अणु 0 पूर्ण)
#घोषणा USER_DS		((mm_segment_t) अणु 1 पूर्ण)

#घोषणा get_fs()	(current->thपढ़ो.current_ds)
#घोषणा set_fs(val)	(current->thपढ़ो.current_ds = (val))

#घोषणा uaccess_kernel() (get_fs().seg == KERNEL_DS.seg)

#घोषणा __kernel_ok (uaccess_kernel())
#घोषणा __user_ok(addr, size) \
		(((size) <= TASK_SIZE)&&((addr) <= TASK_SIZE-(size)))
#घोषणा __access_ok(addr, size) (__kernel_ok || __user_ok((addr), (size)))
#घोषणा access_ok(addr, size) __access_ok((अचिन्हित दीर्घ)(addr), (size))

#घोषणा user_addr_max() (uaccess_kernel() ? ~0UL : TASK_SIZE)

/*
 * These are the मुख्य single-value transfer routines.  They
 * स्वतःmatically use the right size अगर we just have the right poपूर्णांकer
 * type.
 *
 * This माला_लो kind of ugly. We want to वापस _two_ values in
 * "get_user()" and yet we करोn't want to करो any poपूर्णांकers, because that
 * is too much of a perक्रमmance impact. Thus we have a few rather ugly
 * macros here, and hide all the uglyness from the user.
 *
 * Careful to not
 * (a) re-use the arguments क्रम side effects (माप is ok)
 * (b) require any knowledge of processes at this stage
 */
#घोषणा put_user(x, ptr)	__put_user_check((x), (ptr), माप(*(ptr)))
#घोषणा get_user(x, ptr) __get_user_check((x), (ptr), माप(*(ptr)))

/*
 * The "__xxx" versions of the user access functions are versions that
 * करो not verअगरy the address space, that must have been करोne previously
 * with a separate "access_ok()" call (this is used when we करो multiple
 * accesses to the same area of user memory).
 */
#घोषणा __put_user(x, ptr) __put_user_nocheck((x), (ptr), माप(*(ptr)))
#घोषणा __get_user(x, ptr) __get_user_nocheck((x), (ptr), माप(*(ptr)))


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
	पूर्णांक __cb;							\
	retval = 0;							\
	चयन (size) अणु							\
	हाल 1: __put_user_यंत्र(x, ptr, retval, 1, "s8i", __cb);  अवरोध;	\
	हाल 2: __put_user_यंत्र(x, ptr, retval, 2, "s16i", __cb); अवरोध;	\
	हाल 4: __put_user_यंत्र(x, ptr, retval, 4, "s32i", __cb); अवरोध;	\
	हाल 8: अणु							\
		     __typeof__(*ptr) __v64 = x;			\
		     retval = __copy_to_user(ptr, &__v64, 8) ? -EFAULT : 0;	\
		     अवरोध;						\
	        पूर्ण							\
	शेष: __put_user_bad();					\
	पूर्ण								\
पूर्ण जबतक (0)


/*
 * Consider a हाल of a user single load/store would cause both an
 * unaligned exception and an MMU-related exception (unaligned
 * exceptions happen first):
 *
 * User code passes a bad variable ptr to a प्रणाली call.
 * Kernel tries to access the variable.
 * Unaligned exception occurs.
 * Unaligned exception handler tries to make aligned accesses.
 * Double exception occurs क्रम MMU-related cause (e.g., page not mapped).
 * करो_page_fault() thinks the fault address beदीर्घs to the kernel, not the
 * user, and panics.
 *
 * The kernel currently prohibits user unaligned accesses.  We use the
 * __check_align_* macros to check क्रम unaligned addresses beक्रमe
 * accessing user space so we करोn't crash the kernel.  Both
 * __put_user_यंत्र and __get_user_यंत्र use these alignment macros, so
 * macro-specअगरic labels such as 0f, 1f, %0, %2, and %3 must stay in
 * sync.
 */

#घोषणा __check_align_1  ""

#घोषणा __check_align_2				\
	"   _bbci.l %[mem] * 0, 1f	\n"	\
	"   movi    %[err], %[efault]	\n"	\
	"   _j      2f			\n"

#घोषणा __check_align_4				\
	"   _bbsi.l %[mem] * 0, 0f	\n"	\
	"   _bbci.l %[mem] * 0 + 1, 1f	\n"	\
	"0: movi    %[err], %[efault]	\n"	\
	"   _j      2f			\n"


/*
 * We करोn't tell gcc that we are accessing memory, but this is OK
 * because we करो not ग_लिखो to any memory gcc knows about, so there
 * are no aliasing issues.
 *
 * WARNING: If you modअगरy this macro at all, verअगरy that the
 * __check_align_* macros still work.
 */
#घोषणा __put_user_यंत्र(x_, addr_, err_, align, insn, cb)\
__यंत्र__ __अस्थिर__(					\
	__check_align_##align				\
	"1: "insn"  %[x], %[mem]	\n"		\
	"2:				\n"		\
	"   .section  .fixup,\"ax\"	\n"		\
	"   .align 4			\n"		\
	"   .literal_position		\n"		\
	"5:				\n"		\
	"   movi   %[tmp], 2b		\n"		\
	"   movi   %[err], %[efault]	\n"		\
	"   jx     %[tmp]		\n"		\
	"   .previous			\n"		\
	"   .section  __ex_table,\"a\"	\n"		\
	"   .long	1b, 5b		\n"		\
	"   .previous"					\
	:[err] "+r"(err_), [पंचांगp] "=r"(cb), [mem] "=m"(*(addr_))		\
	:[x] "r"(x_), [efault] "i"(-EFAULT))

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
		(x) = (__typeof__(*(ptr)))0;				\
	__gu_err;							\
पूर्ण)

बाह्य दीर्घ __get_user_bad(व्योम);

#घोषणा __get_user_size(x, ptr, size, retval)				\
करो अणु									\
	पूर्णांक __cb;							\
	retval = 0;							\
	चयन (size) अणु							\
	हाल 1: __get_user_यंत्र(x, ptr, retval, 1, "l8ui", __cb);  अवरोध;\
	हाल 2: __get_user_यंत्र(x, ptr, retval, 2, "l16ui", __cb); अवरोध;\
	हाल 4: __get_user_यंत्र(x, ptr, retval, 4, "l32i", __cb);  अवरोध;\
	हाल 8: अणु							\
		u64 __x;						\
		अगर (unlikely(__copy_from_user(&__x, ptr, 8))) अणु		\
			retval = -EFAULT;				\
			(x) = (__typeof__(*(ptr)))0;			\
		पूर्ण अन्यथा अणु						\
			(x) = *(__क्रमce __typeof__(*(ptr)) *)&__x;	\
		पूर्ण							\
		अवरोध;							\
	पूर्ण								\
	शेष:							\
		(x) = (__typeof__(*(ptr)))0;				\
		__get_user_bad();					\
	पूर्ण								\
पूर्ण जबतक (0)


/*
 * WARNING: If you modअगरy this macro at all, verअगरy that the
 * __check_align_* macros still work.
 */
#घोषणा __get_user_यंत्र(x_, addr_, err_, align, insn, cb) \
करो अणु							\
	u32 __x = 0;					\
	__यंत्र__ __अस्थिर__(				\
		__check_align_##align			\
		"1: "insn"  %[x], %[mem]	\n"	\
		"2:				\n"	\
		"   .section  .fixup,\"ax\"	\n"	\
		"   .align 4			\n"	\
		"   .literal_position		\n"	\
		"5:				\n"	\
		"   movi   %[tmp], 2b		\n"	\
		"   movi   %[err], %[efault]	\n"	\
		"   jx     %[tmp]		\n"	\
		"   .previous			\n"	\
		"   .section  __ex_table,\"a\"	\n"	\
		"   .long	1b, 5b		\n"	\
		"   .previous"				\
		:[err] "+r"(err_), [पंचांगp] "=r"(cb), [x] "+r"(__x) \
		:[mem] "m"(*(addr_)), [efault] "i"(-EFAULT)); \
	(x_) = (__क्रमce __typeof__(*(addr_)))__x;	\
पूर्ण जबतक (0)


/*
 * Copy to/from user space
 */

बाह्य अचिन्हित __xtensa_copy_user(व्योम *to, स्थिर व्योम *from, अचिन्हित n);

अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	prefetchw(to);
	वापस __xtensa_copy_user(to, (__क्रमce स्थिर व्योम *)from, n);
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	prefetch(from);
	वापस __xtensa_copy_user((__क्रमce व्योम *)to, from, n);
पूर्ण
#घोषणा INLINE_COPY_FROM_USER
#घोषणा INLINE_COPY_TO_USER

/*
 * We need to वापस the number of bytes not cleared.  Our स_रखो()
 * वापसs zero अगर a problem occurs जबतक accessing user-space memory.
 * In that event, वापस no memory cleared.  Otherwise, zero क्रम
 * success.
 */

अटल अंतरभूत अचिन्हित दीर्घ
__xtensa_clear_user(व्योम __user *addr, अचिन्हित दीर्घ size)
अणु
	अगर (!__स_रखो((व्योम __क्रमce *)addr, 0, size))
		वापस size;
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
clear_user(व्योम __user *addr, अचिन्हित दीर्घ size)
अणु
	अगर (access_ok(addr, size))
		वापस __xtensa_clear_user(addr, size);
	वापस size ? -EFAULT : 0;
पूर्ण

#घोषणा __clear_user  __xtensa_clear_user


#अगर_अघोषित CONFIG_GENERIC_STRNCPY_FROM_USER

बाह्य दीर्घ __म_नकलन_user(अक्षर *dst, स्थिर अक्षर __user *src, दीर्घ count);

अटल अंतरभूत दीर्घ
म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src, दीर्घ count)
अणु
	अगर (access_ok(src, 1))
		वापस __म_नकलन_user(dst, src, count);
	वापस -EFAULT;
पूर्ण
#अन्यथा
दीर्घ म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src, दीर्घ count);
#पूर्ण_अगर

/*
 * Return the size of a string (including the ending 0!)
 */
बाह्य दीर्घ __strnlen_user(स्थिर अक्षर __user *str, दीर्घ len);

अटल अंतरभूत दीर्घ strnlen_user(स्थिर अक्षर __user *str, दीर्घ len)
अणु
	अगर (!access_ok(str, 1))
		वापस 0;
	वापस __strnlen_user(str, len);
पूर्ण

#पूर्ण_अगर	/* _XTENSA_UACCESS_H */
