<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_UACCESS_H
#घोषणा _ASM_X86_UACCESS_H
/*
 * User space memory access functions
 */
#समावेश <linux/compiler.h>
#समावेश <linux/kasan-checks.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/smap.h>
#समावेश <यंत्र/extable.h>

/*
 * Test whether a block of memory is a valid user space address.
 * Returns 0 अगर the range is valid, nonzero otherwise.
 */
अटल अंतरभूत bool __chk_range_not_ok(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size, अचिन्हित दीर्घ limit)
अणु
	/*
	 * If we have used "sizeof()" क्रम the size,
	 * we know it won't overflow the limit (but
	 * it might overflow the 'addr', so it's
	 * important to subtract the size from the
	 * limit, not add it to the address).
	 */
	अगर (__builtin_स्थिरant_p(size))
		वापस unlikely(addr > limit - size);

	/* Arbitrary sizes? Be careful about overflow */
	addr += size;
	अगर (unlikely(addr < size))
		वापस true;
	वापस unlikely(addr > limit);
पूर्ण

#घोषणा __range_not_ok(addr, size, limit)				\
(अणु									\
	__chk_user_ptr(addr);						\
	__chk_range_not_ok((अचिन्हित दीर्घ __क्रमce)(addr), size, limit); \
पूर्ण)

#अगर_घोषित CONFIG_DEBUG_ATOMIC_SLEEP
अटल अंतरभूत bool pagefault_disabled(व्योम);
# define WARN_ON_IN_IRQ()	\
	WARN_ON_ONCE(!in_task() && !pagefault_disabled())
#अन्यथा
# define WARN_ON_IN_IRQ()
#पूर्ण_अगर

/**
 * access_ok - Checks अगर a user space poपूर्णांकer is valid
 * @addr: User space poपूर्णांकer to start of block to check
 * @size: Size of block to check
 *
 * Context: User context only. This function may sleep अगर pagefaults are
 *          enabled.
 *
 * Checks अगर a poपूर्णांकer to a block of memory in user space is valid.
 *
 * Note that, depending on architecture, this function probably just
 * checks that the poपूर्णांकer is in the user space range - after calling
 * this function, memory access functions may still वापस -EFAULT.
 *
 * Return: true (nonzero) अगर the memory block may be valid, false (zero)
 * अगर it is definitely invalid.
 */
#घोषणा access_ok(addr, size)					\
(अणु									\
	WARN_ON_IN_IRQ();						\
	likely(!__range_not_ok(addr, size, TASK_SIZE_MAX));		\
पूर्ण)

बाह्य पूर्णांक __get_user_1(व्योम);
बाह्य पूर्णांक __get_user_2(व्योम);
बाह्य पूर्णांक __get_user_4(व्योम);
बाह्य पूर्णांक __get_user_8(व्योम);
बाह्य पूर्णांक __get_user_nocheck_1(व्योम);
बाह्य पूर्णांक __get_user_nocheck_2(व्योम);
बाह्य पूर्णांक __get_user_nocheck_4(व्योम);
बाह्य पूर्णांक __get_user_nocheck_8(व्योम);
बाह्य पूर्णांक __get_user_bad(व्योम);

#घोषणा __uaccess_begin() stac()
#घोषणा __uaccess_end()   clac()
#घोषणा __uaccess_begin_nospec()	\
(अणु					\
	stac();				\
	barrier_nospec();		\
पूर्ण)

/*
 * This is the smallest अचिन्हित पूर्णांकeger type that can fit a value
 * (up to 'long long')
 */
#घोषणा __पूर्णांकtype(x) __typeof__(		\
	__typefits(x,अक्षर,			\
	  __typefits(x,लघु,			\
	    __typefits(x,पूर्णांक,			\
	      __typefits(x,दीर्घ,0ULL)))))

#घोषणा __typefits(x,type,not) \
	__builtin_choose_expr(माप(x)<=माप(type),(अचिन्हित type)0,not)

/*
 * This is used क्रम both get_user() and __get_user() to expand to
 * the proper special function call that has odd calling conventions
 * due to वापसing both a value and an error, and that depends on
 * the size of the poपूर्णांकer passed in.
 *
 * Careful: we have to cast the result to the type of the poपूर्णांकer
 * क्रम sign reasons.
 *
 * The use of _ASM_DX as the रेजिस्टर specअगरier is a bit of a
 * simplअगरication, as gcc only cares about it as the starting poपूर्णांक
 * and not size: क्रम a 64-bit value it will use %ecx:%edx on 32 bits
 * (%ecx being the next रेजिस्टर in gcc's x86 रेजिस्टर sequence), and
 * %rdx on 64 bits.
 *
 * Clang/LLVM cares about the size of the रेजिस्टर, but still wants
 * the base रेजिस्टर क्रम something that ends up being a pair.
 */
#घोषणा करो_get_user_call(fn,x,ptr)					\
(अणु									\
	पूर्णांक __ret_gu;							\
	रेजिस्टर __पूर्णांकtype(*(ptr)) __val_gu यंत्र("%"_ASM_DX);		\
	__chk_user_ptr(ptr);						\
	यंत्र अस्थिर("call __" #fn "_%P4"				\
		     : "=a" (__ret_gu), "=r" (__val_gu),		\
			ASM_CALL_CONSTRAINT				\
		     : "0" (ptr), "i" (माप(*(ptr))));		\
	(x) = (__क्रमce __typeof__(*(ptr))) __val_gu;			\
	__builtin_expect(__ret_gu, 0);					\
पूर्ण)

/**
 * get_user - Get a simple variable from user space.
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
 * Return: zero on success, or -EFAULT on error.
 * On error, the variable @x is set to zero.
 */
#घोषणा get_user(x,ptr) (अणु might_fault(); करो_get_user_call(get_user,x,ptr); पूर्ण)

/**
 * __get_user - Get a simple variable from user space, with less checking.
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
 * Caller must check the poपूर्णांकer with access_ok() beक्रमe calling this
 * function.
 *
 * Return: zero on success, or -EFAULT on error.
 * On error, the variable @x is set to zero.
 */
#घोषणा __get_user(x,ptr) करो_get_user_call(get_user_nocheck,x,ptr)


#अगर_घोषित CONFIG_X86_32
#घोषणा __put_user_जाओ_u64(x, addr, label)			\
	यंत्र_अस्थिर_जाओ("\n"					\
		     "1:	movl %%eax,0(%1)\n"		\
		     "2:	movl %%edx,4(%1)\n"		\
		     _ASM_EXTABLE_UA(1b, %l2)			\
		     _ASM_EXTABLE_UA(2b, %l2)			\
		     : : "A" (x), "r" (addr)			\
		     : : label)

#अन्यथा
#घोषणा __put_user_जाओ_u64(x, ptr, label) \
	__put_user_जाओ(x, ptr, "q", "er", label)
#पूर्ण_अगर

बाह्य व्योम __put_user_bad(व्योम);

/*
 * Strange magic calling convention: poपूर्णांकer in %ecx,
 * value in %eax(:%edx), वापस value in %ecx. clobbers %rbx
 */
बाह्य व्योम __put_user_1(व्योम);
बाह्य व्योम __put_user_2(व्योम);
बाह्य व्योम __put_user_4(व्योम);
बाह्य व्योम __put_user_8(व्योम);
बाह्य व्योम __put_user_nocheck_1(व्योम);
बाह्य व्योम __put_user_nocheck_2(व्योम);
बाह्य व्योम __put_user_nocheck_4(व्योम);
बाह्य व्योम __put_user_nocheck_8(व्योम);

/*
 * ptr must be evaluated and asचिन्हित to the temporary __ptr_pu beक्रमe
 * the assignment of x to __val_pu, to aव्योम any function calls
 * involved in the ptr expression (possibly implicitly generated due
 * to KASAN) from clobbering %ax.
 */
#घोषणा करो_put_user_call(fn,x,ptr)					\
(अणु									\
	पूर्णांक __ret_pu;							\
	व्योम __user *__ptr_pu;						\
	रेजिस्टर __typeof__(*(ptr)) __val_pu यंत्र("%"_ASM_AX);		\
	__chk_user_ptr(ptr);						\
	__ptr_pu = (ptr);						\
	__val_pu = (x);							\
	यंत्र अस्थिर("call __" #fn "_%P[size]"				\
		     : "=c" (__ret_pu),					\
			ASM_CALL_CONSTRAINT				\
		     : "0" (__ptr_pu),					\
		       "r" (__val_pu),					\
		       [size] "i" (माप(*(ptr)))			\
		     :"ebx");						\
	__builtin_expect(__ret_pu, 0);					\
पूर्ण)

/**
 * put_user - Write a simple value पूर्णांकo user space.
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
 * Return: zero on success, or -EFAULT on error.
 */
#घोषणा put_user(x, ptr) (अणु might_fault(); करो_put_user_call(put_user,x,ptr); पूर्ण)

/**
 * __put_user - Write a simple value पूर्णांकo user space, with less checking.
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
 * Caller must check the poपूर्णांकer with access_ok() beक्रमe calling this
 * function.
 *
 * Return: zero on success, or -EFAULT on error.
 */
#घोषणा __put_user(x, ptr) करो_put_user_call(put_user_nocheck,x,ptr)

#घोषणा __put_user_size(x, ptr, size, label)				\
करो अणु									\
	__chk_user_ptr(ptr);						\
	चयन (size) अणु							\
	हाल 1:								\
		__put_user_जाओ(x, ptr, "b", "iq", label);		\
		अवरोध;							\
	हाल 2:								\
		__put_user_जाओ(x, ptr, "w", "ir", label);		\
		अवरोध;							\
	हाल 4:								\
		__put_user_जाओ(x, ptr, "l", "ir", label);		\
		अवरोध;							\
	हाल 8:								\
		__put_user_जाओ_u64(x, ptr, label);			\
		अवरोध;							\
	शेष:							\
		__put_user_bad();					\
	पूर्ण								\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_CC_HAS_ASM_GOTO_OUTPUT

#अगर_घोषित CONFIG_X86_32
#घोषणा __get_user_यंत्र_u64(x, ptr, label) करो अणु				\
	अचिन्हित पूर्णांक __gu_low, __gu_high;				\
	स्थिर अचिन्हित पूर्णांक __user *__gu_ptr;				\
	__gu_ptr = (स्थिर व्योम __user *)(ptr);				\
	__get_user_यंत्र(__gu_low, ptr, "l", "=r", label);		\
	__get_user_यंत्र(__gu_high, ptr+1, "l", "=r", label);		\
	(x) = ((अचिन्हित दीर्घ दीर्घ)__gu_high << 32) | __gu_low;		\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा __get_user_यंत्र_u64(x, ptr, label)				\
	__get_user_यंत्र(x, ptr, "q", "=r", label)
#पूर्ण_अगर

#घोषणा __get_user_size(x, ptr, size, label)				\
करो अणु									\
	__chk_user_ptr(ptr);						\
	चयन (size) अणु							\
	अचिन्हित अक्षर x_u8__;						\
	हाल 1:								\
		__get_user_यंत्र(x_u8__, ptr, "b", "=q", label);		\
		(x) = x_u8__;						\
		अवरोध;							\
	हाल 2:								\
		__get_user_यंत्र(x, ptr, "w", "=r", label);		\
		अवरोध;							\
	हाल 4:								\
		__get_user_यंत्र(x, ptr, "l", "=r", label);		\
		अवरोध;							\
	हाल 8:								\
		__get_user_यंत्र_u64(x, ptr, label);			\
		अवरोध;							\
	शेष:							\
		(x) = __get_user_bad();					\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा __get_user_यंत्र(x, addr, itype, ltype, label)			\
	यंत्र_अस्थिर_जाओ("\n"						\
		     "1:	mov"itype" %[umem],%[output]\n"		\
		     _ASM_EXTABLE_UA(1b, %l2)				\
		     : [output] ltype(x)				\
		     : [umem] "m" (__m(addr))				\
		     : : label)

#अन्यथा // !CONFIG_CC_HAS_ASM_GOTO_OUTPUT

#अगर_घोषित CONFIG_X86_32
#घोषणा __get_user_यंत्र_u64(x, ptr, retval)				\
(अणु									\
	__typeof__(ptr) __ptr = (ptr);					\
	यंत्र अस्थिर("\n"						\
		     "1:	movl %[lowbits],%%eax\n"		\
		     "2:	movl %[highbits],%%edx\n"		\
		     "3:\n"						\
		     ".section .fixup,\"ax\"\n"				\
		     "4:	mov %[efault],%[errout]\n"		\
		     "	xorl %%eax,%%eax\n"				\
		     "	xorl %%edx,%%edx\n"				\
		     "	jmp 3b\n"					\
		     ".previous\n"					\
		     _ASM_EXTABLE_UA(1b, 4b)				\
		     _ASM_EXTABLE_UA(2b, 4b)				\
		     : [errout] "=r" (retval),				\
		       [output] "=&A"(x)				\
		     : [lowbits] "m" (__m(__ptr)),			\
		       [highbits] "m" __m(((u32 __user *)(__ptr)) + 1),	\
		       [efault] "i" (-EFAULT), "0" (retval));		\
पूर्ण)

#अन्यथा
#घोषणा __get_user_यंत्र_u64(x, ptr, retval) \
	 __get_user_यंत्र(x, ptr, retval, "q", "=r")
#पूर्ण_अगर

#घोषणा __get_user_size(x, ptr, size, retval)				\
करो अणु									\
	अचिन्हित अक्षर x_u8__;						\
									\
	retval = 0;							\
	__chk_user_ptr(ptr);						\
	चयन (size) अणु							\
	हाल 1:								\
		__get_user_यंत्र(x_u8__, ptr, retval, "b", "=q");		\
		(x) = x_u8__;						\
		अवरोध;							\
	हाल 2:								\
		__get_user_यंत्र(x, ptr, retval, "w", "=r");		\
		अवरोध;							\
	हाल 4:								\
		__get_user_यंत्र(x, ptr, retval, "l", "=r");		\
		अवरोध;							\
	हाल 8:								\
		__get_user_यंत्र_u64(x, ptr, retval);			\
		अवरोध;							\
	शेष:							\
		(x) = __get_user_bad();					\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा __get_user_यंत्र(x, addr, err, itype, ltype)			\
	यंत्र अस्थिर("\n"						\
		     "1:	mov"itype" %[umem],%[output]\n"		\
		     "2:\n"						\
		     ".section .fixup,\"ax\"\n"				\
		     "3:	mov %[efault],%[errout]\n"		\
		     "	xorl %k[output],%k[output]\n"			\
		     "	jmp 2b\n"					\
		     ".previous\n"					\
		     _ASM_EXTABLE_UA(1b, 3b)				\
		     : [errout] "=r" (err),				\
		       [output] ltype(x)				\
		     : [umem] "m" (__m(addr)),				\
		       [efault] "i" (-EFAULT), "0" (err))

#पूर्ण_अगर // CONFIG_CC_ASM_GOTO_OUTPUT

/* FIXME: this hack is definitely wrong -AK */
काष्ठा __large_काष्ठा अणु अचिन्हित दीर्घ buf[100]; पूर्ण;
#घोषणा __m(x) (*(काष्ठा __large_काष्ठा __user *)(x))

/*
 * Tell gcc we पढ़ो from memory instead of writing: this is because
 * we करो not ग_लिखो to any memory gcc knows about, so there are no
 * aliasing issues.
 */
#घोषणा __put_user_जाओ(x, addr, itype, ltype, label)			\
	यंत्र_अस्थिर_जाओ("\n"						\
		"1:	mov"itype" %0,%1\n"				\
		_ASM_EXTABLE_UA(1b, %l2)				\
		: : ltype(x), "m" (__m(addr))				\
		: : label)

बाह्य अचिन्हित दीर्घ
copy_from_user_nmi(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n);
बाह्य __must_check दीर्घ
म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src, दीर्घ count);

बाह्य __must_check दीर्घ strnlen_user(स्थिर अक्षर __user *str, दीर्घ n);

अचिन्हित दीर्घ __must_check clear_user(व्योम __user *mem, अचिन्हित दीर्घ len);
अचिन्हित दीर्घ __must_check __clear_user(व्योम __user *mem, अचिन्हित दीर्घ len);

#अगर_घोषित CONFIG_ARCH_HAS_COPY_MC
अचिन्हित दीर्घ __must_check
copy_mc_to_kernel(व्योम *to, स्थिर व्योम *from, अचिन्हित len);
#घोषणा copy_mc_to_kernel copy_mc_to_kernel

अचिन्हित दीर्घ __must_check
copy_mc_to_user(व्योम *to, स्थिर व्योम *from, अचिन्हित len);
#पूर्ण_अगर

/*
 * movsl can be slow when source and dest are not both 8-byte aligned
 */
#अगर_घोषित CONFIG_X86_INTEL_USERCOPY
बाह्य काष्ठा movsl_mask अणु
	पूर्णांक mask;
पूर्ण ____cacheline_aligned_in_smp movsl_mask;
#पूर्ण_अगर

#घोषणा ARCH_HAS_NOCACHE_UACCESS 1

#अगर_घोषित CONFIG_X86_32
# include <यंत्र/uaccess_32.h>
#अन्यथा
# include <यंत्र/uaccess_64.h>
#पूर्ण_अगर

/*
 * The "unsafe" user accesses aren't really "unsafe", but the naming
 * is a big fat warning: you have to not only करो the access_ok()
 * checking beक्रमe using them, but you have to surround them with the
 * user_access_begin/end() pair.
 */
अटल __must_check __always_अंतरभूत bool user_access_begin(स्थिर व्योम __user *ptr, माप_प्रकार len)
अणु
	अगर (unlikely(!access_ok(ptr,len)))
		वापस 0;
	__uaccess_begin_nospec();
	वापस 1;
पूर्ण
#घोषणा user_access_begin(a,b)	user_access_begin(a,b)
#घोषणा user_access_end()	__uaccess_end()

#घोषणा user_access_save()	smap_save()
#घोषणा user_access_restore(x)	smap_restore(x)

#घोषणा unsafe_put_user(x, ptr, label)	\
	__put_user_size((__typeof__(*(ptr)))(x), (ptr), माप(*(ptr)), label)

#अगर_घोषित CONFIG_CC_HAS_ASM_GOTO_OUTPUT
#घोषणा unsafe_get_user(x, ptr, err_label)					\
करो अणु										\
	__पूर्णांकtype(*(ptr)) __gu_val;						\
	__get_user_size(__gu_val, (ptr), माप(*(ptr)), err_label);		\
	(x) = (__क्रमce __typeof__(*(ptr)))__gu_val;				\
पूर्ण जबतक (0)
#अन्यथा // !CONFIG_CC_HAS_ASM_GOTO_OUTPUT
#घोषणा unsafe_get_user(x, ptr, err_label)					\
करो अणु										\
	पूर्णांक __gu_err;								\
	__पूर्णांकtype(*(ptr)) __gu_val;						\
	__get_user_size(__gu_val, (ptr), माप(*(ptr)), __gu_err);		\
	(x) = (__क्रमce __typeof__(*(ptr)))__gu_val;				\
	अगर (unlikely(__gu_err)) जाओ err_label;					\
पूर्ण जबतक (0)
#पूर्ण_अगर // CONFIG_CC_HAS_ASM_GOTO_OUTPUT

/*
 * We want the unsafe accessors to always be अंतरभूतd and use
 * the error labels - thus the macro games.
 */
#घोषणा unsafe_copy_loop(dst, src, len, type, label)				\
	जबतक (len >= माप(type)) अणु						\
		unsafe_put_user(*(type *)(src),(type __user *)(dst),label);	\
		dst += माप(type);						\
		src += माप(type);						\
		len -= माप(type);						\
	पूर्ण

#घोषणा unsafe_copy_to_user(_dst,_src,_len,label)			\
करो अणु									\
	अक्षर __user *__ucu_dst = (_dst);				\
	स्थिर अक्षर *__ucu_src = (_src);					\
	माप_प्रकार __ucu_len = (_len);					\
	unsafe_copy_loop(__ucu_dst, __ucu_src, __ucu_len, u64, label);	\
	unsafe_copy_loop(__ucu_dst, __ucu_src, __ucu_len, u32, label);	\
	unsafe_copy_loop(__ucu_dst, __ucu_src, __ucu_len, u16, label);	\
	unsafe_copy_loop(__ucu_dst, __ucu_src, __ucu_len, u8, label);	\
पूर्ण जबतक (0)

#घोषणा HAVE_GET_KERNEL_NOFAULT

#अगर_घोषित CONFIG_CC_HAS_ASM_GOTO_OUTPUT
#घोषणा __get_kernel_nofault(dst, src, type, err_label)			\
	__get_user_size(*((type *)(dst)), (__क्रमce type __user *)(src),	\
			माप(type), err_label)
#अन्यथा // !CONFIG_CC_HAS_ASM_GOTO_OUTPUT
#घोषणा __get_kernel_nofault(dst, src, type, err_label)			\
करो अणु									\
	पूर्णांक __kr_err;							\
									\
	__get_user_size(*((type *)(dst)), (__क्रमce type __user *)(src),	\
			माप(type), __kr_err);			\
	अगर (unlikely(__kr_err))						\
		जाओ err_label;						\
पूर्ण जबतक (0)
#पूर्ण_अगर // CONFIG_CC_HAS_ASM_GOTO_OUTPUT

#घोषणा __put_kernel_nofault(dst, src, type, err_label)			\
	__put_user_size(*((type *)(src)), (__क्रमce type __user *)(dst),	\
			माप(type), err_label)

#पूर्ण_अगर /* _ASM_X86_UACCESS_H */

