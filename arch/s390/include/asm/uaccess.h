<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *    Copyright IBM Corp. 1999, 2000
 *    Author(s): Harपंचांगut Penner (hp@de.ibm.com),
 *               Martin Schwidefsky (schwidefsky@de.ibm.com)
 *
 *  Derived from "include/asm-i386/uaccess.h"
 */
#अगर_अघोषित __S390_UACCESS_H
#घोषणा __S390_UACCESS_H

/*
 * User space memory access functions
 */
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/ctl_reg.h>
#समावेश <यंत्र/extable.h>
#समावेश <यंत्र/facility.h>

व्योम debug_user_asce(पूर्णांक निकास);

अटल अंतरभूत पूर्णांक __range_ok(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	वापस 1;
पूर्ण

#घोषणा __access_ok(addr, size)				\
(अणु							\
	__chk_user_ptr(addr);				\
	__range_ok((अचिन्हित दीर्घ)(addr), (size));	\
पूर्ण)

#घोषणा access_ok(addr, size) __access_ok(addr, size)

अचिन्हित दीर्घ __must_check
raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n);

अचिन्हित दीर्घ __must_check
raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n);

#अगर_अघोषित CONFIG_KASAN
#घोषणा INLINE_COPY_FROM_USER
#घोषणा INLINE_COPY_TO_USER
#पूर्ण_अगर

पूर्णांक __put_user_bad(व्योम) __attribute__((noवापस));
पूर्णांक __get_user_bad(व्योम) __attribute__((noवापस));

#अगर_घोषित CONFIG_HAVE_MARCH_Z10_FEATURES

#घोषणा __put_get_user_यंत्र(to, from, size, spec)		\
(अणु								\
	रेजिस्टर अचिन्हित दीर्घ __reg0 यंत्र("0") = spec;		\
	पूर्णांक __rc;						\
								\
	यंत्र अस्थिर(						\
		"0:	mvcos	%1,%3,%2\n"			\
		"1:	xr	%0,%0\n"			\
		"2:\n"						\
		".pushsection .fixup, \"ax\"\n"			\
		"3:	lhi	%0,%5\n"			\
		"	jg	2b\n"				\
		".popsection\n"					\
		EX_TABLE(0b,3b) EX_TABLE(1b,3b)			\
		: "=d" (__rc), "+Q" (*(to))			\
		: "d" (size), "Q" (*(from)),			\
		  "d" (__reg0), "K" (-EFAULT)			\
		: "cc");					\
	__rc;							\
पूर्ण)

अटल __always_अंतरभूत पूर्णांक __put_user_fn(व्योम *x, व्योम __user *ptr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ spec = 0x810000UL;
	पूर्णांक rc;

	चयन (size) अणु
	हाल 1:
		rc = __put_get_user_यंत्र((अचिन्हित अक्षर __user *)ptr,
					(अचिन्हित अक्षर *)x,
					size, spec);
		अवरोध;
	हाल 2:
		rc = __put_get_user_यंत्र((अचिन्हित लघु __user *)ptr,
					(अचिन्हित लघु *)x,
					size, spec);
		अवरोध;
	हाल 4:
		rc = __put_get_user_यंत्र((अचिन्हित पूर्णांक __user *)ptr,
					(अचिन्हित पूर्णांक *)x,
					size, spec);
		अवरोध;
	हाल 8:
		rc = __put_get_user_यंत्र((अचिन्हित दीर्घ __user *)ptr,
					(अचिन्हित दीर्घ *)x,
					size, spec);
		अवरोध;
	शेष:
		__put_user_bad();
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल __always_अंतरभूत पूर्णांक __get_user_fn(व्योम *x, स्थिर व्योम __user *ptr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ spec = 0x81UL;
	पूर्णांक rc;

	चयन (size) अणु
	हाल 1:
		rc = __put_get_user_यंत्र((अचिन्हित अक्षर *)x,
					(अचिन्हित अक्षर __user *)ptr,
					size, spec);
		अवरोध;
	हाल 2:
		rc = __put_get_user_यंत्र((अचिन्हित लघु *)x,
					(अचिन्हित लघु __user *)ptr,
					size, spec);
		अवरोध;
	हाल 4:
		rc = __put_get_user_यंत्र((अचिन्हित पूर्णांक *)x,
					(अचिन्हित पूर्णांक __user *)ptr,
					size, spec);
		अवरोध;
	हाल 8:
		rc = __put_get_user_यंत्र((अचिन्हित दीर्घ *)x,
					(अचिन्हित दीर्घ __user *)ptr,
					size, spec);
		अवरोध;
	शेष:
		__get_user_bad();
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

#अन्यथा /* CONFIG_HAVE_MARCH_Z10_FEATURES */

अटल अंतरभूत पूर्णांक __put_user_fn(व्योम *x, व्योम __user *ptr, अचिन्हित दीर्घ size)
अणु
	size = raw_copy_to_user(ptr, x, size);
	वापस size ? -EFAULT : 0;
पूर्ण

अटल अंतरभूत पूर्णांक __get_user_fn(व्योम *x, स्थिर व्योम __user *ptr, अचिन्हित दीर्घ size)
अणु
	size = raw_copy_from_user(x, ptr, size);
	वापस size ? -EFAULT : 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_HAVE_MARCH_Z10_FEATURES */

/*
 * These are the मुख्य single-value transfer routines.  They स्वतःmatically
 * use the right size अगर we just have the right poपूर्णांकer type.
 */
#घोषणा __put_user(x, ptr) \
(अणु								\
	__typeof__(*(ptr)) __x = (x);				\
	पूर्णांक __pu_err = -EFAULT;					\
        __chk_user_ptr(ptr);                                    \
	चयन (माप (*(ptr))) अणु				\
	हाल 1:							\
	हाल 2:							\
	हाल 4:							\
	हाल 8:							\
		__pu_err = __put_user_fn(&__x, ptr,		\
					 माप(*(ptr)));	\
		अवरोध;						\
	शेष:						\
		__put_user_bad();				\
		अवरोध;						\
	पूर्ण							\
	__builtin_expect(__pu_err, 0);				\
पूर्ण)

#घोषणा put_user(x, ptr)					\
(अणु								\
	might_fault();						\
	__put_user(x, ptr);					\
पूर्ण)


#घोषणा __get_user(x, ptr)					\
(अणु								\
	पूर्णांक __gu_err = -EFAULT;					\
	__chk_user_ptr(ptr);					\
	चयन (माप(*(ptr))) अणु				\
	हाल 1: अणु						\
		अचिन्हित अक्षर __x = 0;				\
		__gu_err = __get_user_fn(&__x, ptr,		\
					 माप(*(ptr)));	\
		(x) = *(__क्रमce __typeof__(*(ptr)) *) &__x;	\
		अवरोध;						\
	पूर्ण;							\
	हाल 2: अणु						\
		अचिन्हित लघु __x = 0;				\
		__gu_err = __get_user_fn(&__x, ptr,		\
					 माप(*(ptr)));	\
		(x) = *(__क्रमce __typeof__(*(ptr)) *) &__x;	\
		अवरोध;						\
	पूर्ण;							\
	हाल 4: अणु						\
		अचिन्हित पूर्णांक __x = 0;				\
		__gu_err = __get_user_fn(&__x, ptr,		\
					 माप(*(ptr)));	\
		(x) = *(__क्रमce __typeof__(*(ptr)) *) &__x;	\
		अवरोध;						\
	पूर्ण;							\
	हाल 8: अणु						\
		अचिन्हित दीर्घ दीर्घ __x = 0;			\
		__gu_err = __get_user_fn(&__x, ptr,		\
					 माप(*(ptr)));	\
		(x) = *(__क्रमce __typeof__(*(ptr)) *) &__x;	\
		अवरोध;						\
	पूर्ण;							\
	शेष:						\
		__get_user_bad();				\
		अवरोध;						\
	पूर्ण							\
	__builtin_expect(__gu_err, 0);				\
पूर्ण)

#घोषणा get_user(x, ptr)					\
(अणु								\
	might_fault();						\
	__get_user(x, ptr);					\
पूर्ण)

अचिन्हित दीर्घ __must_check
raw_copy_in_user(व्योम __user *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n);

/*
 * Copy a null terminated string from userspace.
 */

दीर्घ __म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src, दीर्घ count);

अटल अंतरभूत दीर्घ __must_check
म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src, दीर्घ count)
अणु
	might_fault();
	वापस __म_नकलन_from_user(dst, src, count);
पूर्ण

अचिन्हित दीर्घ __must_check __strnlen_user(स्थिर अक्षर __user *src, अचिन्हित दीर्घ count);

अटल अंतरभूत अचिन्हित दीर्घ strnlen_user(स्थिर अक्षर __user *src, अचिन्हित दीर्घ n)
अणु
	might_fault();
	वापस __strnlen_user(src, n);
पूर्ण

/*
 * Zero Userspace
 */
अचिन्हित दीर्घ __must_check __clear_user(व्योम __user *to, अचिन्हित दीर्घ size);

अटल अंतरभूत अचिन्हित दीर्घ __must_check clear_user(व्योम __user *to, अचिन्हित दीर्घ n)
अणु
	might_fault();
	वापस __clear_user(to, n);
पूर्ण

पूर्णांक copy_to_user_real(व्योम __user *dest, व्योम *src, अचिन्हित दीर्घ count);
व्योम *s390_kernel_ग_लिखो(व्योम *dst, स्थिर व्योम *src, माप_प्रकार size);

#घोषणा HAVE_GET_KERNEL_NOFAULT

पूर्णांक __noवापस __put_kernel_bad(व्योम);

#घोषणा __put_kernel_यंत्र(val, to, insn)					\
(अणु									\
	पूर्णांक __rc;							\
									\
	यंत्र अस्थिर(							\
		"0:   " insn "  %2,%1\n"				\
		"1:	xr	%0,%0\n"				\
		"2:\n"							\
		".pushsection .fixup, \"ax\"\n"				\
		"3:	lhi	%0,%3\n"				\
		"	jg	2b\n"					\
		".popsection\n"						\
		EX_TABLE(0b,3b) EX_TABLE(1b,3b)				\
		: "=d" (__rc), "+Q" (*(to))				\
		: "d" (val), "K" (-EFAULT)				\
		: "cc");						\
	__rc;								\
पूर्ण)

#घोषणा __put_kernel_nofault(dst, src, type, err_label)			\
करो अणु									\
	u64 __x = (u64)(*((type *)(src)));				\
	पूर्णांक __pk_err;							\
									\
	चयन (माप(type)) अणु						\
	हाल 1:								\
		__pk_err = __put_kernel_यंत्र(__x, (type *)(dst), "stc"); \
		अवरोध;							\
	हाल 2:								\
		__pk_err = __put_kernel_यंत्र(__x, (type *)(dst), "sth"); \
		अवरोध;							\
	हाल 4:								\
		__pk_err = __put_kernel_यंत्र(__x, (type *)(dst), "st");	\
		अवरोध;							\
	हाल 8:								\
		__pk_err = __put_kernel_यंत्र(__x, (type *)(dst), "stg"); \
		अवरोध;							\
	शेष:							\
		__pk_err = __put_kernel_bad();				\
		अवरोध;							\
	पूर्ण								\
	अगर (unlikely(__pk_err))						\
		जाओ err_label;						\
पूर्ण जबतक (0)

पूर्णांक __noवापस __get_kernel_bad(व्योम);

#घोषणा __get_kernel_यंत्र(val, from, insn)				\
(अणु									\
	पूर्णांक __rc;							\
									\
	यंत्र अस्थिर(							\
		"0:   " insn "  %1,%2\n"				\
		"1:	xr	%0,%0\n"				\
		"2:\n"							\
		".pushsection .fixup, \"ax\"\n"				\
		"3:	lhi	%0,%3\n"				\
		"	jg	2b\n"					\
		".popsection\n"						\
		EX_TABLE(0b,3b) EX_TABLE(1b,3b)				\
		: "=d" (__rc), "+d" (val)				\
		: "Q" (*(from)), "K" (-EFAULT)				\
		: "cc");						\
	__rc;								\
पूर्ण)

#घोषणा __get_kernel_nofault(dst, src, type, err_label)			\
करो अणु									\
	पूर्णांक __gk_err;							\
									\
	चयन (माप(type)) अणु						\
	हाल 1: अणु							\
		u8 __x = 0;						\
									\
		__gk_err = __get_kernel_यंत्र(__x, (type *)(src), "ic");	\
		*((type *)(dst)) = (type)__x;				\
		अवरोध;							\
	पूर्ण;								\
	हाल 2: अणु							\
		u16 __x = 0;						\
									\
		__gk_err = __get_kernel_यंत्र(__x, (type *)(src), "lh");	\
		*((type *)(dst)) = (type)__x;				\
		अवरोध;							\
	पूर्ण;								\
	हाल 4: अणु							\
		u32 __x = 0;						\
									\
		__gk_err = __get_kernel_यंत्र(__x, (type *)(src), "l");	\
		*((type *)(dst)) = (type)__x;				\
		अवरोध;							\
	पूर्ण;								\
	हाल 8: अणु							\
		u64 __x = 0;						\
									\
		__gk_err = __get_kernel_यंत्र(__x, (type *)(src), "lg");	\
		*((type *)(dst)) = (type)__x;				\
		अवरोध;							\
	पूर्ण;								\
	शेष:							\
		__gk_err = __get_kernel_bad();				\
		अवरोध;							\
	पूर्ण								\
	अगर (unlikely(__gk_err))						\
		जाओ err_label;						\
पूर्ण जबतक (0)

#पूर्ण_अगर /* __S390_UACCESS_H */
