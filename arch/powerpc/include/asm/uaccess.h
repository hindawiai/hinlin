<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ARCH_POWERPC_UACCESS_H
#घोषणा _ARCH_POWERPC_UACCESS_H

#समावेश <यंत्र/ppc_यंत्र.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/extable.h>
#समावेश <यंत्र/kup.h>

#अगर_घोषित __घातerpc64__
/* We use TASK_SIZE_USER64 as TASK_SIZE is not स्थिरant */
#घोषणा TASK_SIZE_MAX		TASK_SIZE_USER64
#अन्यथा
#घोषणा TASK_SIZE_MAX		TASK_SIZE
#पूर्ण_अगर

अटल अंतरभूत bool __access_ok(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	वापस addr < TASK_SIZE_MAX && size <= TASK_SIZE_MAX - addr;
पूर्ण

#घोषणा access_ok(addr, size)		\
	(__chk_user_ptr(addr),		\
	 __access_ok((अचिन्हित दीर्घ)(addr), (size)))

/*
 * These are the मुख्य single-value transfer routines.  They स्वतःmatically
 * use the right size अगर we just have the right poपूर्णांकer type.
 *
 * This माला_लो kind of ugly. We want to वापस _two_ values in "get_user()"
 * and yet we करोn't want to करो any poपूर्णांकers, because that is too much
 * of a perक्रमmance impact. Thus we have a few rather ugly macros here,
 * and hide all the ugliness from the user.
 *
 * The "__xxx" versions of the user access functions are versions that
 * करो not verअगरy the address space, that must have been करोne previously
 * with a separate "access_ok()" call (this is used when we करो multiple
 * accesses to the same area of user memory).
 *
 * As we use the same address space क्रम kernel and user data on the
 * PowerPC, we can just करो these as direct assignments.  (Of course, the
 * exception handling means that it's no दीर्घer "just"...)
 *
 */
#घोषणा __put_user(x, ptr)					\
(अणु								\
	दीर्घ __pu_err;						\
	__typeof__(*(ptr)) __user *__pu_addr = (ptr);		\
	__typeof__(*(ptr)) __pu_val = (__typeof__(*(ptr)))(x);	\
	__typeof__(माप(*(ptr))) __pu_size = माप(*(ptr));	\
								\
	might_fault();						\
	करो अणु							\
		__label__ __pu_failed;				\
								\
		allow_ग_लिखो_to_user(__pu_addr, __pu_size);	\
		__put_user_size_जाओ(__pu_val, __pu_addr, __pu_size, __pu_failed);	\
		prevent_ग_लिखो_to_user(__pu_addr, __pu_size);	\
		__pu_err = 0;					\
		अवरोध;						\
								\
__pu_failed:							\
		prevent_ग_लिखो_to_user(__pu_addr, __pu_size);	\
		__pu_err = -EFAULT;				\
	पूर्ण जबतक (0);						\
								\
	__pu_err;						\
पूर्ण)

#घोषणा put_user(x, ptr)						\
(अणु									\
	__typeof__(*(ptr)) __user *_pu_addr = (ptr);			\
									\
	access_ok(_pu_addr, माप(*(ptr))) ?				\
		  __put_user(x, _pu_addr) : -EFAULT;			\
पूर्ण)

/*
 * We करोn't tell gcc that we are accessing memory, but this is OK
 * because we करो not ग_लिखो to any memory gcc knows about, so there
 * are no aliasing issues.
 */
#घोषणा __put_user_यंत्र_जाओ(x, addr, label, op)			\
	यंत्र_अस्थिर_जाओ(					\
		"1:	" op "%U1%X1 %0,%1	# put_user\n"	\
		EX_TABLE(1b, %l2)				\
		:						\
		: "r" (x), "m"UPD_CONSTR (*addr)		\
		:						\
		: label)

#अगर_घोषित __घातerpc64__
#घोषणा __put_user_यंत्र2_जाओ(x, ptr, label)			\
	__put_user_यंत्र_जाओ(x, ptr, label, "std")
#अन्यथा /* __घातerpc64__ */
#घोषणा __put_user_यंत्र2_जाओ(x, addr, label)			\
	यंत्र_अस्थिर_जाओ(					\
		"1:	stw%X1 %0, %1\n"			\
		"2:	stw%X1 %L0, %L1\n"			\
		EX_TABLE(1b, %l2)				\
		EX_TABLE(2b, %l2)				\
		:						\
		: "r" (x), "m" (*addr)				\
		:						\
		: label)
#पूर्ण_अगर /* __घातerpc64__ */

#घोषणा __put_user_size_जाओ(x, ptr, size, label)		\
करो अणु								\
	__typeof__(*(ptr)) __user *__pus_addr = (ptr);		\
								\
	चयन (size) अणु						\
	हाल 1: __put_user_यंत्र_जाओ(x, __pus_addr, label, "stb"); अवरोध;	\
	हाल 2: __put_user_यंत्र_जाओ(x, __pus_addr, label, "sth"); अवरोध;	\
	हाल 4: __put_user_यंत्र_जाओ(x, __pus_addr, label, "stw"); अवरोध;	\
	हाल 8: __put_user_यंत्र2_जाओ(x, __pus_addr, label); अवरोध;		\
	शेष: BUILD_BUG();					\
	पूर्ण							\
पूर्ण जबतक (0)

/*
 * This करोes an atomic 128 byte aligned load from userspace.
 * Upto caller to करो enable_kernel_vmx() beक्रमe calling!
 */
#घोषणा __get_user_atomic_128_aligned(kaddr, uaddr, err)		\
	__यंत्र__ __अस्थिर__(				\
		"1:	lvx  0,0,%1	# get user\n"	\
		" 	stvx 0,0,%2	# put kernel\n"	\
		"2:\n"					\
		".section .fixup,\"ax\"\n"		\
		"3:	li %0,%3\n"			\
		"	b 2b\n"				\
		".previous\n"				\
		EX_TABLE(1b, 3b)			\
		: "=r" (err)			\
		: "b" (uaddr), "b" (kaddr), "i" (-EFAULT), "0" (err))

#अगर_घोषित CONFIG_CC_HAS_ASM_GOTO_OUTPUT

#घोषणा __get_user_यंत्र_जाओ(x, addr, label, op)			\
	यंत्र_अस्थिर_जाओ(					\
		"1:	"op"%U1%X1 %0, %1	# get_user\n"	\
		EX_TABLE(1b, %l2)				\
		: "=r" (x)					\
		: "m"UPD_CONSTR (*addr)				\
		:						\
		: label)

#अगर_घोषित __घातerpc64__
#घोषणा __get_user_यंत्र2_जाओ(x, addr, label)			\
	__get_user_यंत्र_जाओ(x, addr, label, "ld")
#अन्यथा /* __घातerpc64__ */
#घोषणा __get_user_यंत्र2_जाओ(x, addr, label)			\
	यंत्र_अस्थिर_जाओ(					\
		"1:	lwz%X1 %0, %1\n"			\
		"2:	lwz%X1 %L0, %L1\n"			\
		EX_TABLE(1b, %l2)				\
		EX_TABLE(2b, %l2)				\
		: "=&r" (x)					\
		: "m" (*addr)					\
		:						\
		: label)
#पूर्ण_अगर /* __घातerpc64__ */

#घोषणा __get_user_size_जाओ(x, ptr, size, label)				\
करो अणु										\
	BUILD_BUG_ON(size > माप(x));						\
	चयन (size) अणु								\
	हाल 1: __get_user_यंत्र_जाओ(x, (u8 __user *)ptr, label, "lbz"); अवरोध;	\
	हाल 2: __get_user_यंत्र_जाओ(x, (u16 __user *)ptr, label, "lhz"); अवरोध;	\
	हाल 4: __get_user_यंत्र_जाओ(x, (u32 __user *)ptr, label, "lwz"); अवरोध;	\
	हाल 8: __get_user_यंत्र2_जाओ(x, (u64 __user *)ptr, label);  अवरोध;	\
	शेष: x = 0; BUILD_BUG();						\
	पूर्ण									\
पूर्ण जबतक (0)

#घोषणा __get_user_size_allowed(x, ptr, size, retval)			\
करो अणु									\
		__label__ __gus_failed;					\
									\
		__get_user_size_जाओ(x, ptr, size, __gus_failed);	\
		retval = 0;						\
		अवरोध;							\
__gus_failed:								\
		x = 0;							\
		retval = -EFAULT;					\
पूर्ण जबतक (0)

#अन्यथा /* CONFIG_CC_HAS_ASM_GOTO_OUTPUT */

#घोषणा __get_user_यंत्र(x, addr, err, op)		\
	__यंत्र__ __अस्थिर__(				\
		"1:	"op"%U2%X2 %1, %2	# get_user\n"	\
		"2:\n"					\
		".section .fixup,\"ax\"\n"		\
		"3:	li %0,%3\n"			\
		"	li %1,0\n"			\
		"	b 2b\n"				\
		".previous\n"				\
		EX_TABLE(1b, 3b)			\
		: "=r" (err), "=r" (x)			\
		: "m"UPD_CONSTR (*addr), "i" (-EFAULT), "0" (err))

#अगर_घोषित __घातerpc64__
#घोषणा __get_user_यंत्र2(x, addr, err)			\
	__get_user_यंत्र(x, addr, err, "ld")
#अन्यथा /* __घातerpc64__ */
#घोषणा __get_user_यंत्र2(x, addr, err)			\
	__यंत्र__ __अस्थिर__(				\
		"1:	lwz%X2 %1, %2\n"			\
		"2:	lwz%X2 %L1, %L2\n"		\
		"3:\n"					\
		".section .fixup,\"ax\"\n"		\
		"4:	li %0,%3\n"			\
		"	li %1,0\n"			\
		"	li %1+1,0\n"			\
		"	b 3b\n"				\
		".previous\n"				\
		EX_TABLE(1b, 4b)			\
		EX_TABLE(2b, 4b)			\
		: "=r" (err), "=&r" (x)			\
		: "m" (*addr), "i" (-EFAULT), "0" (err))
#पूर्ण_अगर /* __घातerpc64__ */

#घोषणा __get_user_size_allowed(x, ptr, size, retval)		\
करो अणु								\
	retval = 0;						\
	BUILD_BUG_ON(size > माप(x));				\
	चयन (size) अणु						\
	हाल 1: __get_user_यंत्र(x, (u8 __user *)ptr, retval, "lbz"); अवरोध;	\
	हाल 2: __get_user_यंत्र(x, (u16 __user *)ptr, retval, "lhz"); अवरोध;	\
	हाल 4: __get_user_यंत्र(x, (u32 __user *)ptr, retval, "lwz"); अवरोध;	\
	हाल 8: __get_user_यंत्र2(x, (u64 __user *)ptr, retval);  अवरोध;	\
	शेष: x = 0; BUILD_BUG();				\
	पूर्ण							\
पूर्ण जबतक (0)

#घोषणा __get_user_size_जाओ(x, ptr, size, label)		\
करो अणु								\
	दीर्घ __gus_retval;					\
								\
	__get_user_size_allowed(x, ptr, size, __gus_retval);	\
	अगर (__gus_retval)					\
		जाओ label;					\
पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_CC_HAS_ASM_GOTO_OUTPUT */

/*
 * This is a type: either अचिन्हित दीर्घ, अगर the argument fits पूर्णांकo
 * that type, or otherwise अचिन्हित दीर्घ दीर्घ.
 */
#घोषणा __दीर्घ_type(x) \
	__typeof__(__builtin_choose_expr(माप(x) > माप(0UL), 0ULL, 0UL))

#घोषणा __get_user(x, ptr)					\
(अणु								\
	दीर्घ __gu_err;						\
	__दीर्घ_type(*(ptr)) __gu_val;				\
	__typeof__(*(ptr)) __user *__gu_addr = (ptr);	\
	__typeof__(माप(*(ptr))) __gu_size = माप(*(ptr));	\
								\
	might_fault();					\
	allow_पढ़ो_from_user(__gu_addr, __gu_size);		\
	__get_user_size_allowed(__gu_val, __gu_addr, __gu_size, __gu_err);	\
	prevent_पढ़ो_from_user(__gu_addr, __gu_size);		\
	(x) = (__typeof__(*(ptr)))__gu_val;			\
								\
	__gu_err;						\
पूर्ण)

#घोषणा get_user(x, ptr)						\
(अणु									\
	__typeof__(*(ptr)) __user *_gu_addr = (ptr);			\
									\
	access_ok(_gu_addr, माप(*(ptr))) ?				\
		  __get_user(x, _gu_addr) :				\
		  ((x) = (__क्रमce __typeof__(*(ptr)))0, -EFAULT);	\
पूर्ण)

/* more complex routines */

बाह्य अचिन्हित दीर्घ __copy_tofrom_user(व्योम __user *to,
		स्थिर व्योम __user *from, अचिन्हित दीर्घ size);

#अगर_घोषित __घातerpc64__
अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_in_user(व्योम __user *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ ret;

	allow_पढ़ो_ग_लिखो_user(to, from, n);
	ret = __copy_tofrom_user(to, from, n);
	prevent_पढ़ो_ग_लिखो_user(to, from, n);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* __घातerpc64__ */

अटल अंतरभूत अचिन्हित दीर्घ raw_copy_from_user(व्योम *to,
		स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ ret;

	allow_पढ़ो_from_user(from, n);
	ret = __copy_tofrom_user((__क्रमce व्योम __user *)to, from, n);
	prevent_पढ़ो_from_user(from, n);
	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ ret;

	allow_ग_लिखो_to_user(to, n);
	ret = __copy_tofrom_user(to, (__क्रमce स्थिर व्योम __user *)from, n);
	prevent_ग_लिखो_to_user(to, n);
	वापस ret;
पूर्ण

अचिन्हित दीर्घ __arch_clear_user(व्योम __user *addr, अचिन्हित दीर्घ size);

अटल अंतरभूत अचिन्हित दीर्घ __clear_user(व्योम __user *addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ ret;

	might_fault();
	allow_ग_लिखो_to_user(addr, size);
	ret = __arch_clear_user(addr, size);
	prevent_ग_लिखो_to_user(addr, size);
	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ clear_user(व्योम __user *addr, अचिन्हित दीर्घ size)
अणु
	वापस likely(access_ok(addr, size)) ? __clear_user(addr, size) : size;
पूर्ण

बाह्य दीर्घ म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src, दीर्घ count);
बाह्य __must_check दीर्घ strnlen_user(स्थिर अक्षर __user *str, दीर्घ n);

#अगर_घोषित CONFIG_ARCH_HAS_COPY_MC
अचिन्हित दीर्घ __must_check
copy_mc_generic(व्योम *to, स्थिर व्योम *from, अचिन्हित दीर्घ size);

अटल अंतरभूत अचिन्हित दीर्घ __must_check
copy_mc_to_kernel(व्योम *to, स्थिर व्योम *from, अचिन्हित दीर्घ size)
अणु
	वापस copy_mc_generic(to, from, size);
पूर्ण
#घोषणा copy_mc_to_kernel copy_mc_to_kernel

अटल अंतरभूत अचिन्हित दीर्घ __must_check
copy_mc_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	अगर (likely(check_copy_size(from, n, true))) अणु
		अगर (access_ok(to, n)) अणु
			allow_ग_लिखो_to_user(to, n);
			n = copy_mc_generic((व्योम *)to, from, n);
			prevent_ग_लिखो_to_user(to, n);
		पूर्ण
	पूर्ण

	वापस n;
पूर्ण
#पूर्ण_अगर

बाह्य दीर्घ __copy_from_user_flushcache(व्योम *dst, स्थिर व्योम __user *src,
		अचिन्हित size);
बाह्य व्योम स_नकल_page_flushcache(अक्षर *to, काष्ठा page *page, माप_प्रकार offset,
			   माप_प्रकार len);

अटल __must_check अंतरभूत bool user_access_begin(स्थिर व्योम __user *ptr, माप_प्रकार len)
अणु
	अगर (unlikely(!access_ok(ptr, len)))
		वापस false;

	might_fault();

	allow_पढ़ो_ग_लिखो_user((व्योम __user *)ptr, ptr, len);
	वापस true;
पूर्ण
#घोषणा user_access_begin	user_access_begin
#घोषणा user_access_end		prevent_current_access_user
#घोषणा user_access_save	prevent_user_access_वापस
#घोषणा user_access_restore	restore_user_access

अटल __must_check अंतरभूत bool
user_पढ़ो_access_begin(स्थिर व्योम __user *ptr, माप_प्रकार len)
अणु
	अगर (unlikely(!access_ok(ptr, len)))
		वापस false;

	might_fault();

	allow_पढ़ो_from_user(ptr, len);
	वापस true;
पूर्ण
#घोषणा user_पढ़ो_access_begin	user_पढ़ो_access_begin
#घोषणा user_पढ़ो_access_end		prevent_current_पढ़ो_from_user

अटल __must_check अंतरभूत bool
user_ग_लिखो_access_begin(स्थिर व्योम __user *ptr, माप_प्रकार len)
अणु
	अगर (unlikely(!access_ok(ptr, len)))
		वापस false;

	might_fault();

	allow_ग_लिखो_to_user((व्योम __user *)ptr, len);
	वापस true;
पूर्ण
#घोषणा user_ग_लिखो_access_begin	user_ग_लिखो_access_begin
#घोषणा user_ग_लिखो_access_end		prevent_current_ग_लिखो_to_user

#घोषणा unsafe_get_user(x, p, e) करो अणु					\
	__दीर्घ_type(*(p)) __gu_val;				\
	__typeof__(*(p)) __user *__gu_addr = (p);		\
								\
	__get_user_size_जाओ(__gu_val, __gu_addr, माप(*(p)), e); \
	(x) = (__typeof__(*(p)))__gu_val;			\
पूर्ण जबतक (0)

#घोषणा unsafe_put_user(x, p, e) \
	__put_user_size_जाओ((__typeof__(*(p)))(x), (p), माप(*(p)), e)

#घोषणा unsafe_copy_from_user(d, s, l, e) \
करो अणु											\
	u8 *_dst = (u8 *)(d);								\
	स्थिर u8 __user *_src = (स्थिर u8 __user *)(s);					\
	माप_प्रकार _len = (l);								\
	पूर्णांक _i;										\
											\
	क्रम (_i = 0; _i < (_len & ~(माप(u64) - 1)); _i += माप(u64))		\
		unsafe_get_user(*(u64 *)(_dst + _i), (u64 __user *)(_src + _i), e);	\
	अगर (_len & 4) अणु									\
		unsafe_get_user(*(u32 *)(_dst + _i), (u32 __user *)(_src + _i), e);	\
		_i += 4;								\
	पूर्ण										\
	अगर (_len & 2) अणु									\
		unsafe_get_user(*(u16 *)(_dst + _i), (u16 __user *)(_src + _i), e);	\
		_i += 2;								\
	पूर्ण										\
	अगर (_len & 1)									\
		unsafe_get_user(*(u8 *)(_dst + _i), (u8 __user *)(_src + _i), e);	\
पूर्ण जबतक (0)

#घोषणा unsafe_copy_to_user(d, s, l, e) \
करो अणु									\
	u8 __user *_dst = (u8 __user *)(d);				\
	स्थिर u8 *_src = (स्थिर u8 *)(s);				\
	माप_प्रकार _len = (l);						\
	पूर्णांक _i;								\
									\
	क्रम (_i = 0; _i < (_len & ~(माप(u64) - 1)); _i += माप(u64))	\
		unsafe_put_user(*(u64 *)(_src + _i), (u64 __user *)(_dst + _i), e); \
	अगर (_len & 4) अणु							\
		unsafe_put_user(*(u32*)(_src + _i), (u32 __user *)(_dst + _i), e); \
		_i += 4;						\
	पूर्ण								\
	अगर (_len & 2) अणु							\
		unsafe_put_user(*(u16*)(_src + _i), (u16 __user *)(_dst + _i), e); \
		_i += 2;						\
	पूर्ण								\
	अगर (_len & 1) \
		unsafe_put_user(*(u8*)(_src + _i), (u8 __user *)(_dst + _i), e); \
पूर्ण जबतक (0)

#घोषणा HAVE_GET_KERNEL_NOFAULT

#घोषणा __get_kernel_nofault(dst, src, type, err_label)			\
	__get_user_size_जाओ(*((type *)(dst)),				\
		(__क्रमce type __user *)(src), माप(type), err_label)

#घोषणा __put_kernel_nofault(dst, src, type, err_label)			\
	__put_user_size_जाओ(*((type *)(src)),				\
		(__क्रमce type __user *)(dst), माप(type), err_label)

#पूर्ण_अगर	/* _ARCH_POWERPC_UACCESS_H */
