<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_UACCESS_H
#घोषणा __ASM_GENERIC_UACCESS_H

/*
 * User space memory access functions, these should work
 * on any machine that has kernel and user data in the same
 * address space, e.g. all NOMMU machines.
 */
#समावेश <linux/माला.स>

#अगर_घोषित CONFIG_UACCESS_MEMCPY
#समावेश <यंत्र/unaligned.h>

अटल __always_अंतरभूत पूर्णांक
__get_user_fn(माप_प्रकार size, स्थिर व्योम __user *from, व्योम *to)
अणु
	BUILD_BUG_ON(!__builtin_स्थिरant_p(size));

	चयन (size) अणु
	हाल 1:
		*(u8 *)to = get_unaligned((u8 __क्रमce *)from);
		वापस 0;
	हाल 2:
		*(u16 *)to = get_unaligned((u16 __क्रमce *)from);
		वापस 0;
	हाल 4:
		*(u32 *)to = get_unaligned((u32 __क्रमce *)from);
		वापस 0;
	हाल 8:
		*(u64 *)to = get_unaligned((u64 __क्रमce *)from);
		वापस 0;
	शेष:
		BUILD_BUG();
		वापस 0;
	पूर्ण

पूर्ण
#घोषणा __get_user_fn(sz, u, k)	__get_user_fn(sz, u, k)

अटल __always_अंतरभूत पूर्णांक
__put_user_fn(माप_प्रकार size, व्योम __user *to, व्योम *from)
अणु
	BUILD_BUG_ON(!__builtin_स्थिरant_p(size));

	चयन (size) अणु
	हाल 1:
		put_unaligned(*(u8 *)from, (u8 __क्रमce *)to);
		वापस 0;
	हाल 2:
		put_unaligned(*(u16 *)from, (u16 __क्रमce *)to);
		वापस 0;
	हाल 4:
		put_unaligned(*(u32 *)from, (u32 __क्रमce *)to);
		वापस 0;
	हाल 8:
		put_unaligned(*(u64 *)from, (u64 __क्रमce *)to);
		वापस 0;
	शेष:
		BUILD_BUG();
		वापस 0;
	पूर्ण
पूर्ण
#घोषणा __put_user_fn(sz, u, k)	__put_user_fn(sz, u, k)

#घोषणा __get_kernel_nofault(dst, src, type, err_label)			\
करो अणु									\
	*((type *)dst) = get_unaligned((type *)(src));			\
	अगर (0) /* make sure the label looks used to the compiler */	\
		जाओ err_label;						\
पूर्ण जबतक (0)

#घोषणा __put_kernel_nofault(dst, src, type, err_label)			\
करो अणु									\
	put_unaligned(*((type *)src), (type *)(dst));			\
	अगर (0) /* make sure the label looks used to the compiler */	\
		जाओ err_label;						\
पूर्ण जबतक (0)

#घोषणा HAVE_GET_KERNEL_NOFAULT 1

अटल अंतरभूत __must_check अचिन्हित दीर्घ
raw_copy_from_user(व्योम *to, स्थिर व्योम __user * from, अचिन्हित दीर्घ n)
अणु
	स_नकल(to, (स्थिर व्योम __क्रमce *)from, n);
	वापस 0;
पूर्ण

अटल अंतरभूत __must_check अचिन्हित दीर्घ
raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	स_नकल((व्योम __क्रमce *)to, from, n);
	वापस 0;
पूर्ण
#घोषणा INLINE_COPY_FROM_USER
#घोषणा INLINE_COPY_TO_USER
#पूर्ण_अगर /* CONFIG_UACCESS_MEMCPY */

#अगर_घोषित CONFIG_SET_FS
#घोषणा MAKE_MM_SEG(s)	((mm_segment_t) अणु (s) पूर्ण)

#अगर_अघोषित KERNEL_DS
#घोषणा KERNEL_DS	MAKE_MM_SEG(~0UL)
#पूर्ण_अगर

#अगर_अघोषित USER_DS
#घोषणा USER_DS		MAKE_MM_SEG(TASK_SIZE - 1)
#पूर्ण_अगर

#अगर_अघोषित get_fs
#घोषणा get_fs()	(current_thपढ़ो_info()->addr_limit)

अटल अंतरभूत व्योम set_fs(mm_segment_t fs)
अणु
	current_thपढ़ो_info()->addr_limit = fs;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित uaccess_kernel
#घोषणा uaccess_kernel() (get_fs().seg == KERNEL_DS.seg)
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_SET_FS */

#घोषणा access_ok(addr, size) __access_ok((अचिन्हित दीर्घ)(addr),(size))

/*
 * The architecture should really override this अगर possible, at least
 * करोing a check on the get_fs()
 */
#अगर_अघोषित __access_ok
अटल अंतरभूत पूर्णांक __access_ok(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर

/*
 * These are the मुख्य single-value transfer routines.  They स्वतःmatically
 * use the right size अगर we just have the right poपूर्णांकer type.
 * This version just falls back to copy_अणुfrom,toपूर्ण_user, which should
 * provide a fast-path क्रम small values.
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
		__pu_err = __put_user_fn(माप (*(ptr)),	\
					 ptr, &__x);		\
		अवरोध;						\
	शेष:						\
		__put_user_bad();				\
		अवरोध;						\
	 पूर्ण							\
	__pu_err;						\
पूर्ण)

#घोषणा put_user(x, ptr)					\
(अणु								\
	व्योम __user *__p = (ptr);				\
	might_fault();						\
	access_ok(__p, माप(*ptr)) ?		\
		__put_user((x), ((__typeof__(*(ptr)) __user *)__p)) :	\
		-EFAULT;					\
पूर्ण)

#अगर_अघोषित __put_user_fn

अटल अंतरभूत पूर्णांक __put_user_fn(माप_प्रकार size, व्योम __user *ptr, व्योम *x)
अणु
	वापस unlikely(raw_copy_to_user(ptr, x, size)) ? -EFAULT : 0;
पूर्ण

#घोषणा __put_user_fn(sz, u, k)	__put_user_fn(sz, u, k)

#पूर्ण_अगर

बाह्य पूर्णांक __put_user_bad(व्योम) __attribute__((noवापस));

#घोषणा __get_user(x, ptr)					\
(अणु								\
	पूर्णांक __gu_err = -EFAULT;					\
	__chk_user_ptr(ptr);					\
	चयन (माप(*(ptr))) अणु				\
	हाल 1: अणु						\
		अचिन्हित अक्षर __x = 0;				\
		__gu_err = __get_user_fn(माप (*(ptr)),	\
					 ptr, &__x);		\
		(x) = *(__क्रमce __typeof__(*(ptr)) *) &__x;	\
		अवरोध;						\
	पूर्ण;							\
	हाल 2: अणु						\
		अचिन्हित लघु __x = 0;				\
		__gu_err = __get_user_fn(माप (*(ptr)),	\
					 ptr, &__x);		\
		(x) = *(__क्रमce __typeof__(*(ptr)) *) &__x;	\
		अवरोध;						\
	पूर्ण;							\
	हाल 4: अणु						\
		अचिन्हित पूर्णांक __x = 0;				\
		__gu_err = __get_user_fn(माप (*(ptr)),	\
					 ptr, &__x);		\
		(x) = *(__क्रमce __typeof__(*(ptr)) *) &__x;	\
		अवरोध;						\
	पूर्ण;							\
	हाल 8: अणु						\
		अचिन्हित दीर्घ दीर्घ __x = 0;			\
		__gu_err = __get_user_fn(माप (*(ptr)),	\
					 ptr, &__x);		\
		(x) = *(__क्रमce __typeof__(*(ptr)) *) &__x;	\
		अवरोध;						\
	पूर्ण;							\
	शेष:						\
		__get_user_bad();				\
		अवरोध;						\
	पूर्ण							\
	__gu_err;						\
पूर्ण)

#घोषणा get_user(x, ptr)					\
(अणु								\
	स्थिर व्योम __user *__p = (ptr);				\
	might_fault();						\
	access_ok(__p, माप(*ptr)) ?		\
		__get_user((x), (__typeof__(*(ptr)) __user *)__p) :\
		((x) = (__typeof__(*(ptr)))0,-EFAULT);		\
पूर्ण)

#अगर_अघोषित __get_user_fn
अटल अंतरभूत पूर्णांक __get_user_fn(माप_प्रकार size, स्थिर व्योम __user *ptr, व्योम *x)
अणु
	वापस unlikely(raw_copy_from_user(x, ptr, size)) ? -EFAULT : 0;
पूर्ण

#घोषणा __get_user_fn(sz, u, k)	__get_user_fn(sz, u, k)

#पूर्ण_अगर

बाह्य पूर्णांक __get_user_bad(व्योम) __attribute__((noवापस));

/*
 * Copy a null terminated string from userspace.
 */
#अगर_अघोषित __म_नकलन_from_user
अटल अंतरभूत दीर्घ
__म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src, दीर्घ count)
अणु
	अक्षर *पंचांगp;
	म_नकलन(dst, (स्थिर अक्षर __क्रमce *)src, count);
	क्रम (पंचांगp = dst; *पंचांगp && count > 0; पंचांगp++, count--)
		;
	वापस (पंचांगp - dst);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत दीर्घ
म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src, दीर्घ count)
अणु
	अगर (!access_ok(src, 1))
		वापस -EFAULT;
	वापस __म_नकलन_from_user(dst, src, count);
पूर्ण

/*
 * Return the size of a string (including the ending 0)
 *
 * Return 0 on exception, a value greater than N अगर too दीर्घ
 */
#अगर_अघोषित __strnlen_user
#घोषणा __strnlen_user(s, n) (strnlen((s), (n)) + 1)
#पूर्ण_अगर

/*
 * Unlike strnlen, strnlen_user includes the nul terminator in
 * its वापसed count. Callers should check क्रम a वापसed value
 * greater than N as an indication the string is too दीर्घ.
 */
अटल अंतरभूत दीर्घ strnlen_user(स्थिर अक्षर __user *src, दीर्घ n)
अणु
	अगर (!access_ok(src, 1))
		वापस 0;
	वापस __strnlen_user(src, n);
पूर्ण

/*
 * Zero Userspace
 */
#अगर_अघोषित __clear_user
अटल अंतरभूत __must_check अचिन्हित दीर्घ
__clear_user(व्योम __user *to, अचिन्हित दीर्घ n)
अणु
	स_रखो((व्योम __क्रमce *)to, 0, n);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत __must_check अचिन्हित दीर्घ
clear_user(व्योम __user *to, अचिन्हित दीर्घ n)
अणु
	might_fault();
	अगर (!access_ok(to, n))
		वापस n;

	वापस __clear_user(to, n);
पूर्ण

#समावेश <यंत्र/extable.h>

#पूर्ण_अगर /* __ASM_GENERIC_UACCESS_H */
