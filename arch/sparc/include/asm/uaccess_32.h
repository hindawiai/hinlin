<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * uaccess.h: User space memore access functions.
 *
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 1996,1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */
#अगर_अघोषित _ASM_UACCESS_H
#घोषणा _ASM_UACCESS_H

#समावेश <linux/compiler.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/processor.h>

/* Sparc is not segmented, however we need to be able to fool access_ok()
 * when करोing प्रणाली calls from kernel mode legitimately.
 *
 * "For historical reasons, these macros are grossly misnamed." -Linus
 */

#घोषणा KERNEL_DS   ((mm_segment_t) अणु 0 पूर्ण)
#घोषणा USER_DS     ((mm_segment_t) अणु -1 पूर्ण)

#घोषणा get_fs()	(current->thपढ़ो.current_ds)
#घोषणा set_fs(val)	((current->thपढ़ो.current_ds) = (val))

#घोषणा uaccess_kernel() (get_fs().seg == KERNEL_DS.seg)

/* We have there a nice not-mapped page at PAGE_OFFSET - PAGE_SIZE, so that this test
 * can be fairly lightweight.
 * No one can पढ़ो/ग_लिखो anything from userland in the kernel space by setting
 * large size and address near to PAGE_OFFSET - a fault will अवरोध his पूर्णांकentions.
 */
#घोषणा __user_ok(addr, size) (अणु (व्योम)(size); (addr) < STACK_TOP; पूर्ण)
#घोषणा __kernel_ok (uaccess_kernel())
#घोषणा __access_ok(addr, size) (__user_ok((addr) & get_fs().seg, (size)))
#घोषणा access_ok(addr, size) __access_ok((अचिन्हित दीर्घ)(addr), size)

/* Uh, these should become the मुख्य single-value transfer routines..
 * They स्वतःmatically use the right size अगर we just have the right
 * poपूर्णांकer type..
 *
 * This माला_लो kind of ugly. We want to वापस _two_ values in "get_user()"
 * and yet we करोn't want to करो any poपूर्णांकers, because that is too much
 * of a perक्रमmance impact. Thus we have a few rather ugly macros here,
 * and hide all the ugliness from the user.
 */
#घोषणा put_user(x, ptr) (अणु \
	अचिन्हित दीर्घ __pu_addr = (अचिन्हित दीर्घ)(ptr); \
	__chk_user_ptr(ptr); \
	__put_user_check((__typeof__(*(ptr)))(x), __pu_addr, माप(*(ptr))); \
पूर्ण)

#घोषणा get_user(x, ptr) (अणु \
	अचिन्हित दीर्घ __gu_addr = (अचिन्हित दीर्घ)(ptr); \
	__chk_user_ptr(ptr); \
	__get_user_check((x), __gu_addr, माप(*(ptr)), __typeof__(*(ptr))); \
पूर्ण)

/*
 * The "__xxx" versions करो not करो address space checking, useful when
 * करोing multiple accesses to the same area (the user has to करो the
 * checks by hand with "access_ok()")
 */
#घोषणा __put_user(x, ptr) \
	__put_user_nocheck((__typeof__(*(ptr)))(x), (ptr), माप(*(ptr)))
#घोषणा __get_user(x, ptr) \
    __get_user_nocheck((x), (ptr), माप(*(ptr)), __typeof__(*(ptr)))

काष्ठा __large_काष्ठा अणु अचिन्हित दीर्घ buf[100]; पूर्ण;
#घोषणा __m(x) ((काष्ठा __large_काष्ठा __user *)(x))

#घोषणा __put_user_check(x, addr, size) (अणु \
	रेजिस्टर पूर्णांक __pu_ret; \
	अगर (__access_ok(addr, size)) अणु \
		चयन (size) अणु \
		हाल 1: \
			__put_user_यंत्र(x, b, addr, __pu_ret); \
			अवरोध; \
		हाल 2: \
			__put_user_यंत्र(x, h, addr, __pu_ret); \
			अवरोध; \
		हाल 4: \
			__put_user_यंत्र(x, , addr, __pu_ret); \
			अवरोध; \
		हाल 8: \
			__put_user_यंत्र(x, d, addr, __pu_ret); \
			अवरोध; \
		शेष: \
			__pu_ret = __put_user_bad(); \
			अवरोध; \
		पूर्ण \
	पूर्ण अन्यथा अणु \
		__pu_ret = -EFAULT; \
	पूर्ण \
	__pu_ret; \
पूर्ण)

#घोषणा __put_user_nocheck(x, addr, size) (अणु			\
	रेजिस्टर पूर्णांक __pu_ret;					\
	चयन (size) अणु						\
	हाल 1: __put_user_यंत्र(x, b, addr, __pu_ret); अवरोध;	\
	हाल 2: __put_user_यंत्र(x, h, addr, __pu_ret); अवरोध;	\
	हाल 4: __put_user_यंत्र(x, , addr, __pu_ret); अवरोध;	\
	हाल 8: __put_user_यंत्र(x, d, addr, __pu_ret); अवरोध;	\
	शेष: __pu_ret = __put_user_bad(); अवरोध;		\
	पूर्ण \
	__pu_ret; \
पूर्ण)

#घोषणा __put_user_यंत्र(x, size, addr, ret)				\
__यंत्र__ __अस्थिर__(							\
		"/* Put user asm, inline. */\n"				\
	"1:\t"	"st"#size " %1, %2\n\t"					\
		"clr	%0\n"						\
	"2:\n\n\t"							\
		".section .fixup,#alloc,#execinstr\n\t"			\
		".align	4\n"						\
	"3:\n\t"							\
		"b	2b\n\t"						\
		" mov	%3, %0\n\t"					\
		".previous\n\n\t"					\
		".section __ex_table,#alloc\n\t"			\
		".align	4\n\t"						\
		".word	1b, 3b\n\t"					\
		".previous\n\n\t"					\
	       : "=&r" (ret) : "r" (x), "m" (*__m(addr)),		\
		 "i" (-EFAULT))

पूर्णांक __put_user_bad(व्योम);

#घोषणा __get_user_check(x, addr, size, type) (अणु \
	रेजिस्टर पूर्णांक __gu_ret; \
	रेजिस्टर अचिन्हित दीर्घ __gu_val; \
	अगर (__access_ok(addr, size)) अणु \
		चयन (size) अणु \
		हाल 1: \
			 __get_user_यंत्र(__gu_val, ub, addr, __gu_ret); \
			अवरोध; \
		हाल 2: \
			__get_user_यंत्र(__gu_val, uh, addr, __gu_ret); \
			अवरोध; \
		हाल 4: \
			__get_user_यंत्र(__gu_val, , addr, __gu_ret); \
			अवरोध; \
		हाल 8: \
			__get_user_यंत्र(__gu_val, d, addr, __gu_ret); \
			अवरोध; \
		शेष: \
			__gu_val = 0; \
			__gu_ret = __get_user_bad(); \
			अवरोध; \
		पूर्ण \
	 पूर्ण अन्यथा अणु \
		 __gu_val = 0; \
		 __gu_ret = -EFAULT; \
	पूर्ण \
	x = (__क्रमce type) __gu_val; \
	__gu_ret; \
पूर्ण)

#घोषणा __get_user_nocheck(x, addr, size, type) (अणु			\
	रेजिस्टर पूर्णांक __gu_ret;						\
	रेजिस्टर अचिन्हित दीर्घ __gu_val;				\
	चयन (size) अणु							\
	हाल 1: __get_user_यंत्र(__gu_val, ub, addr, __gu_ret); अवरोध;	\
	हाल 2: __get_user_यंत्र(__gu_val, uh, addr, __gu_ret); अवरोध;	\
	हाल 4: __get_user_यंत्र(__gu_val, , addr, __gu_ret); अवरोध;	\
	हाल 8: __get_user_यंत्र(__gu_val, d, addr, __gu_ret); अवरोध;	\
	शेष:							\
		__gu_val = 0;						\
		__gu_ret = __get_user_bad();				\
		अवरोध;							\
	पूर्ण								\
	x = (__क्रमce type) __gu_val;					\
	__gu_ret;							\
पूर्ण)

#घोषणा __get_user_यंत्र(x, size, addr, ret)				\
__यंत्र__ __अस्थिर__(							\
		"/* Get user asm, inline. */\n"				\
	"1:\t"	"ld"#size " %2, %1\n\t"					\
		"clr	%0\n"						\
	"2:\n\n\t"							\
		".section .fixup,#alloc,#execinstr\n\t"			\
		".align	4\n"						\
	"3:\n\t"							\
		"clr	%1\n\t"						\
		"b	2b\n\t"						\
		" mov	%3, %0\n\n\t"					\
		".previous\n\t"						\
		".section __ex_table,#alloc\n\t"			\
		".align	4\n\t"						\
		".word	1b, 3b\n\n\t"					\
		".previous\n\t"						\
	       : "=&r" (ret), "=&r" (x) : "m" (*__m(addr)),		\
		 "i" (-EFAULT))

पूर्णांक __get_user_bad(व्योम);

अचिन्हित दीर्घ __copy_user(व्योम __user *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ size);

अटल अंतरभूत अचिन्हित दीर्घ raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	वापस __copy_user(to, (__क्रमce व्योम __user *) from, n);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	वापस __copy_user((__क्रमce व्योम __user *) to, from, n);
पूर्ण

#घोषणा INLINE_COPY_FROM_USER
#घोषणा INLINE_COPY_TO_USER

अटल अंतरभूत अचिन्हित दीर्घ __clear_user(व्योम __user *addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ ret;

	__यंत्र__ __अस्थिर__ (
		"mov %2, %%o1\n"
		"call __bzero\n\t"
		" mov %1, %%o0\n\t"
		"mov %%o0, %0\n"
		: "=r" (ret) : "r" (addr), "r" (size) :
		"o0", "o1", "o2", "o3", "o4", "o5", "o7",
		"g1", "g2", "g3", "g4", "g5", "g7", "cc");

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ clear_user(व्योम __user *addr, अचिन्हित दीर्घ n)
अणु
	अगर (n && __access_ok((अचिन्हित दीर्घ) addr, n))
		वापस __clear_user(addr, n);
	अन्यथा
		वापस n;
पूर्ण

__must_check दीर्घ strnlen_user(स्थिर अक्षर __user *str, दीर्घ n);

#पूर्ण_अगर /* _ASM_UACCESS_H */
