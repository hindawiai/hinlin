<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 1997, 1998, 1999, 2000, 03, 04 by Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 * Copyright (C) 2007  Maciej W. Rozycki
 * Copyright (C) 2014, Imagination Technologies Ltd.
 */
#अगर_अघोषित _ASM_UACCESS_H
#घोषणा _ASM_UACCESS_H

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/यंत्र-eva.h>
#समावेश <यंत्र/extable.h>

#अगर_घोषित CONFIG_32BIT

#घोषणा __UA_LIMIT 0x80000000UL

#घोषणा __UA_ADDR	".word"
#घोषणा __UA_LA		"la"
#घोषणा __UA_ADDU	"addu"
#घोषणा __UA_t0		"$8"
#घोषणा __UA_t1		"$9"

#पूर्ण_अगर /* CONFIG_32BIT */

#अगर_घोषित CONFIG_64BIT

बाह्य u64 __ua_limit;

#घोषणा __UA_LIMIT	__ua_limit

#घोषणा __UA_ADDR	".dword"
#घोषणा __UA_LA		"dla"
#घोषणा __UA_ADDU	"daddu"
#घोषणा __UA_t0		"$12"
#घोषणा __UA_t1		"$13"

#पूर्ण_अगर /* CONFIG_64BIT */

/*
 * Is a address valid? This करोes a straightक्रमward calculation rather
 * than tests.
 *
 * Address valid अगर:
 *  - "addr" करोesn't have any high-bits set
 *  - AND "size" करोesn't have any high-bits set
 *  - AND "addr+size" करोesn't have any high-bits set
 *  - OR we are in kernel mode.
 *
 * __ua_size() is a trick to aव्योम runसमय checking of positive स्थिरant
 * sizes; क्रम those we alपढ़ोy know at compile समय that the size is ok.
 */
#घोषणा __ua_size(size)							\
	((__builtin_स्थिरant_p(size) && (चिन्हित दीर्घ) (size) > 0) ? 0 : (size))

/*
 * access_ok: - Checks अगर a user space poपूर्णांकer is valid
 * @addr: User space poपूर्णांकer to start of block to check
 * @size: Size of block to check
 *
 * Context: User context only. This function may sleep अगर pagefaults are
 *          enabled.
 *
 * Checks अगर a poपूर्णांकer to a block of memory in user space is valid.
 *
 * Returns true (nonzero) अगर the memory block may be valid, false (zero)
 * अगर it is definitely invalid.
 *
 * Note that, depending on architecture, this function probably just
 * checks that the poपूर्णांकer is in the user space range - after calling
 * this function, memory access functions may still वापस -EFAULT.
 */

अटल अंतरभूत पूर्णांक __access_ok(स्थिर व्योम __user *p, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)p;
	अचिन्हित दीर्घ end = addr + size - !!size;

	वापस (__UA_LIMIT & (addr | end | __ua_size(size))) == 0;
पूर्ण

#घोषणा access_ok(addr, size)					\
	likely(__access_ok((addr), (size)))

/*
 * put_user: - Write a simple value पूर्णांकo user space.
 * @x:	 Value to copy to user space.
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
(अणु									\
	__typeof__(*(ptr)) __user *__p = (ptr);				\
									\
	might_fault();							\
	access_ok(__p, माप(*__p)) ? __put_user((x), __p) : -EFAULT;	\
पूर्ण)

/*
 * get_user: - Get a simple variable from user space.
 * @x:	 Variable to store result.
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
#घोषणा get_user(x, ptr)						\
(अणु									\
	स्थिर __typeof__(*(ptr)) __user *__p = (ptr);			\
									\
	might_fault();							\
	access_ok(__p, माप(*__p)) ? __get_user((x), __p) :		\
				       ((x) = 0, -EFAULT);		\
पूर्ण)

/*
 * __put_user: - Write a simple value पूर्णांकo user space, with less checking.
 * @x:	 Value to copy to user space.
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
 * Returns zero on success, or -EFAULT on error.
 */
#घोषणा __put_user(x, ptr)						\
(अणु									\
	__typeof__(*(ptr)) __user *__pu_ptr = (ptr);			\
	__typeof__(*(ptr)) __pu_val = (x);				\
	पूर्णांक __pu_err = 0;						\
									\
	__chk_user_ptr(__pu_ptr);					\
	चयन (माप(*__pu_ptr)) अणु					\
	हाल 1:								\
		__put_data_यंत्र(user_sb, __pu_ptr);			\
		अवरोध;							\
	हाल 2:								\
		__put_data_यंत्र(user_sh, __pu_ptr);			\
		अवरोध;							\
	हाल 4:								\
		__put_data_यंत्र(user_sw, __pu_ptr);			\
		अवरोध;							\
	हाल 8:								\
		__PUT_DW(user_sd, __pu_ptr);				\
		अवरोध;							\
	शेष:							\
		BUILD_BUG();						\
	पूर्ण								\
									\
	__pu_err;							\
पूर्ण)

/*
 * __get_user: - Get a simple variable from user space, with less checking.
 * @x:	 Variable to store result.
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
 * Returns zero on success, or -EFAULT on error.
 * On error, the variable @x is set to zero.
 */
#घोषणा __get_user(x, ptr)						\
(अणु									\
	स्थिर __typeof__(*(ptr)) __user *__gu_ptr = (ptr);		\
	पूर्णांक __gu_err = 0;						\
									\
	__chk_user_ptr(__gu_ptr);					\
	चयन (माप(*__gu_ptr)) अणु					\
	हाल 1:								\
		__get_data_यंत्र((x), user_lb, __gu_ptr);			\
		अवरोध;							\
	हाल 2:								\
		__get_data_यंत्र((x), user_lh, __gu_ptr);			\
		अवरोध;							\
	हाल 4:								\
		__get_data_यंत्र((x), user_lw, __gu_ptr);			\
		अवरोध;							\
	हाल 8:								\
		__GET_DW((x), user_ld, __gu_ptr);			\
		अवरोध;							\
	शेष:							\
		BUILD_BUG();						\
	पूर्ण								\
									\
	__gu_err;							\
पूर्ण)

काष्ठा __large_काष्ठा अणु अचिन्हित दीर्घ buf[100]; पूर्ण;
#घोषणा __m(x) (*(काष्ठा __large_काष्ठा __user *)(x))

#अगर_घोषित CONFIG_32BIT
#घोषणा __GET_DW(val, insn, ptr) __get_data_यंत्र_ll32(val, insn, ptr)
#पूर्ण_अगर
#अगर_घोषित CONFIG_64BIT
#घोषणा __GET_DW(val, insn, ptr) __get_data_यंत्र(val, insn, ptr)
#पूर्ण_अगर

#घोषणा __get_data_यंत्र(val, insn, addr)					\
अणु									\
	दीर्घ __gu_पंचांगp;							\
									\
	__यंत्र__ __अस्थिर__(						\
	"1:	"insn("%1", "%3")"				\n"	\
	"2:							\n"	\
	"	.insn						\n"	\
	"	.section .fixup,\"ax\"				\n"	\
	"3:	li	%0, %4					\n"	\
	"	move	%1, $0					\n"	\
	"	j	2b					\n"	\
	"	.previous					\n"	\
	"	.section __ex_table,\"a\"			\n"	\
	"	"__UA_ADDR "\t1b, 3b				\n"	\
	"	.previous					\n"	\
	: "=r" (__gu_err), "=r" (__gu_पंचांगp)				\
	: "0" (0), "o" (__m(addr)), "i" (-EFAULT));			\
									\
	(val) = (__typeof__(*(addr))) __gu_पंचांगp;				\
पूर्ण

/*
 * Get a दीर्घ दीर्घ 64 using 32 bit रेजिस्टरs.
 */
#घोषणा __get_data_यंत्र_ll32(val, insn, addr)				\
अणु									\
	जोड़ अणु								\
		अचिन्हित दीर्घ दीर्घ	l;				\
		__typeof__(*(addr))	t;				\
	पूर्ण __gu_पंचांगp;							\
									\
	__यंत्र__ __अस्थिर__(						\
	"1:	" insn("%1", "(%3)")"				\n"	\
	"2:	" insn("%D1", "4(%3)")"				\n"	\
	"3:							\n"	\
	"	.insn						\n"	\
	"	.section	.fixup,\"ax\"			\n"	\
	"4:	li	%0, %4					\n"	\
	"	move	%1, $0					\n"	\
	"	move	%D1, $0					\n"	\
	"	j	3b					\n"	\
	"	.previous					\n"	\
	"	.section	__ex_table,\"a\"		\n"	\
	"	" __UA_ADDR "	1b, 4b				\n"	\
	"	" __UA_ADDR "	2b, 4b				\n"	\
	"	.previous					\n"	\
	: "=r" (__gu_err), "=&r" (__gu_पंचांगp.l)				\
	: "0" (0), "r" (addr), "i" (-EFAULT));				\
									\
	(val) = __gu_पंचांगp.t;						\
पूर्ण

#घोषणा HAVE_GET_KERNEL_NOFAULT

#घोषणा __get_kernel_nofault(dst, src, type, err_label)			\
करो अणु									\
	पूर्णांक __gu_err;							\
									\
	चयन (माप(type)) अणु						\
	हाल 1:								\
		__get_data_यंत्र(*(type *)(dst), kernel_lb,		\
			       (__क्रमce type *)(src));			\
		अवरोध;							\
	हाल 2:								\
		__get_data_यंत्र(*(type *)(dst), kernel_lh,		\
			       (__क्रमce type *)(src));			\
		अवरोध;							\
	हाल 4:								\
		 __get_data_यंत्र(*(type *)(dst), kernel_lw,		\
			       (__क्रमce type *)(src));			\
		अवरोध;							\
	हाल 8:								\
		__GET_DW(*(type *)(dst), kernel_ld,			\
			 (__क्रमce type *)(src));			\
		अवरोध;							\
	शेष:							\
		BUILD_BUG();						\
		अवरोध;							\
	पूर्ण								\
	अगर (unlikely(__gu_err))						\
		जाओ err_label;						\
पूर्ण जबतक (0)

/*
 * Yuck.  We need two variants, one क्रम 64bit operation and one
 * क्रम 32 bit mode and old iron.
 */
#अगर_घोषित CONFIG_32BIT
#घोषणा __PUT_DW(insn, ptr) __put_data_यंत्र_ll32(insn, ptr)
#पूर्ण_अगर
#अगर_घोषित CONFIG_64BIT
#घोषणा __PUT_DW(insn, ptr) __put_data_यंत्र(insn, ptr)
#पूर्ण_अगर

#घोषणा __put_data_यंत्र(insn, ptr)					\
अणु									\
	__यंत्र__ __अस्थिर__(						\
	"1:	"insn("%z2", "%3")"	# __put_data_asm	\n"	\
	"2:							\n"	\
	"	.insn						\n"	\
	"	.section	.fixup,\"ax\"			\n"	\
	"3:	li	%0, %4					\n"	\
	"	j	2b					\n"	\
	"	.previous					\n"	\
	"	.section	__ex_table,\"a\"		\n"	\
	"	" __UA_ADDR "	1b, 3b				\n"	\
	"	.previous					\n"	\
	: "=r" (__pu_err)						\
	: "0" (0), "Jr" (__pu_val), "o" (__m(ptr)),			\
	  "i" (-EFAULT));						\
पूर्ण

#घोषणा __put_data_यंत्र_ll32(insn, ptr)					\
अणु									\
	__यंत्र__ __अस्थिर__(						\
	"1:	"insn("%2", "(%3)")"	# __put_data_asm_ll32	\n"	\
	"2:	"insn("%D2", "4(%3)")"				\n"	\
	"3:							\n"	\
	"	.insn						\n"	\
	"	.section	.fixup,\"ax\"			\n"	\
	"4:	li	%0, %4					\n"	\
	"	j	3b					\n"	\
	"	.previous					\n"	\
	"	.section	__ex_table,\"a\"		\n"	\
	"	" __UA_ADDR "	1b, 4b				\n"	\
	"	" __UA_ADDR "	2b, 4b				\n"	\
	"	.previous"						\
	: "=r" (__pu_err)						\
	: "0" (0), "r" (__pu_val), "r" (ptr),				\
	  "i" (-EFAULT));						\
पूर्ण

#घोषणा __put_kernel_nofault(dst, src, type, err_label)			\
करो अणु									\
	type __pu_val;					\
	पूर्णांक __pu_err = 0;						\
									\
	__pu_val = *(__क्रमce type *)(src);				\
	चयन (माप(type)) अणु						\
	हाल 1:								\
		__put_data_यंत्र(kernel_sb, (type *)(dst));		\
		अवरोध;							\
	हाल 2:								\
		__put_data_यंत्र(kernel_sh, (type *)(dst));		\
		अवरोध;							\
	हाल 4:								\
		__put_data_यंत्र(kernel_sw, (type *)(dst))		\
		अवरोध;							\
	हाल 8:								\
		__PUT_DW(kernel_sd, (type *)(dst));			\
		अवरोध;							\
	शेष:							\
		BUILD_BUG();						\
		अवरोध;							\
	पूर्ण								\
	अगर (unlikely(__pu_err))						\
		जाओ err_label;						\
पूर्ण जबतक (0)


/*
 * We're generating jump to subroutines which will be outside the range of
 * jump inकाष्ठाions
 */
#अगर_घोषित MODULE
#घोषणा __MODULE_JAL(destination)					\
	".set\tnoat\n\t"						\
	__UA_LA "\t$1, " #destination "\n\t"				\
	"jalr\t$1\n\t"							\
	".set\tat\n\t"
#अन्यथा
#घोषणा __MODULE_JAL(destination)					\
	"jal\t" #destination "\n\t"
#पूर्ण_अगर

#अगर defined(CONFIG_CPU_DADDI_WORKAROUNDS) || (defined(CONFIG_EVA) &&	\
					      defined(CONFIG_CPU_HAS_PREFETCH))
#घोषणा DADDI_SCRATCH "$3"
#अन्यथा
#घोषणा DADDI_SCRATCH "$0"
#पूर्ण_अगर

बाह्य माप_प्रकार __raw_copy_from_user(व्योम *__to, स्थिर व्योम *__from, माप_प्रकार __n);
बाह्य माप_प्रकार __raw_copy_to_user(व्योम *__to, स्थिर व्योम *__from, माप_प्रकार __n);
बाह्य माप_प्रकार __raw_copy_in_user(व्योम *__to, स्थिर व्योम *__from, माप_प्रकार __n);

अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	रेजिस्टर व्योम *__cu_to_r __यंत्र__("$4");
	रेजिस्टर स्थिर व्योम __user *__cu_from_r __यंत्र__("$5");
	रेजिस्टर दीर्घ __cu_len_r __यंत्र__("$6");

	__cu_to_r = to;
	__cu_from_r = from;
	__cu_len_r = n;

	__यंत्र__ __अस्थिर__(
		".set\tnoreorder\n\t"
		__MODULE_JAL(__raw_copy_from_user)
		".set\tnoat\n\t"
		__UA_ADDU "\t$1, %1, %2\n\t"
		".set\tat\n\t"
		".set\treorder"
		: "+r" (__cu_to_r), "+r" (__cu_from_r), "+r" (__cu_len_r)
		:
		: "$8", "$9", "$10", "$11", "$12", "$14", "$15", "$24", "$31",
		  DADDI_SCRATCH, "memory");

	वापस __cu_len_r;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	रेजिस्टर व्योम __user *__cu_to_r __यंत्र__("$4");
	रेजिस्टर स्थिर व्योम *__cu_from_r __यंत्र__("$5");
	रेजिस्टर दीर्घ __cu_len_r __यंत्र__("$6");

	__cu_to_r = (to);
	__cu_from_r = (from);
	__cu_len_r = (n);

	__यंत्र__ __अस्थिर__(
		__MODULE_JAL(__raw_copy_to_user)
		: "+r" (__cu_to_r), "+r" (__cu_from_r), "+r" (__cu_len_r)
		:
		: "$8", "$9", "$10", "$11", "$12", "$14", "$15", "$24", "$31",
		  DADDI_SCRATCH, "memory");

	वापस __cu_len_r;
पूर्ण

#घोषणा INLINE_COPY_FROM_USER
#घोषणा INLINE_COPY_TO_USER

अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_in_user(व्योम __user *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	रेजिस्टर व्योम __user *__cu_to_r __यंत्र__("$4");
	रेजिस्टर स्थिर व्योम __user *__cu_from_r __यंत्र__("$5");
	रेजिस्टर दीर्घ __cu_len_r __यंत्र__("$6");

	__cu_to_r = to;
	__cu_from_r = from;
	__cu_len_r = n;

	__यंत्र__ __अस्थिर__(
		".set\tnoreorder\n\t"
		__MODULE_JAL(__raw_copy_in_user)
		".set\tnoat\n\t"
		__UA_ADDU "\t$1, %1, %2\n\t"
		".set\tat\n\t"
		".set\treorder"
		: "+r" (__cu_to_r), "+r" (__cu_from_r), "+r" (__cu_len_r)
		:
		: "$8", "$9", "$10", "$11", "$12", "$14", "$15", "$24", "$31",
		  DADDI_SCRATCH, "memory");
	वापस __cu_len_r;
पूर्ण

बाह्य __kernel_माप_प्रकार __bzero(व्योम __user *addr, __kernel_माप_प्रकार size);

/*
 * __clear_user: - Zero a block of memory in user space, with less checking.
 * @to:	  Destination address, in user space.
 * @n:	  Number of bytes to zero.
 *
 * Zero a block of memory in user space.  Caller must check
 * the specअगरied block with access_ok() beक्रमe calling this function.
 *
 * Returns number of bytes that could not be cleared.
 * On success, this will be zero.
 */
अटल अंतरभूत __kernel_माप_प्रकार
__clear_user(व्योम __user *addr, __kernel_माप_प्रकार size)
अणु
	__kernel_माप_प्रकार res;

#अगर_घोषित CONFIG_CPU_MICROMIPS
/* micromips स_रखो / bzero also clobbers t7 & t8 */
#घोषणा bzero_clobbers "$4", "$5", "$6", __UA_t0, __UA_t1, "$15", "$24", "$31"
#अन्यथा
#घोषणा bzero_clobbers "$4", "$5", "$6", __UA_t0, __UA_t1, "$31"
#पूर्ण_अगर /* CONFIG_CPU_MICROMIPS */

	might_fault();
	__यंत्र__ __अस्थिर__(
		"move\t$4, %1\n\t"
		"move\t$5, $0\n\t"
		"move\t$6, %2\n\t"
		__MODULE_JAL(__bzero)
		"move\t%0, $6"
		: "=r" (res)
		: "r" (addr), "r" (size)
		: bzero_clobbers);

	वापस res;
पूर्ण

#घोषणा clear_user(addr,n)						\
(अणु									\
	व्योम __user * __cl_addr = (addr);				\
	अचिन्हित दीर्घ __cl_size = (n);					\
	अगर (__cl_size && access_ok(__cl_addr, __cl_size))		\
		__cl_size = __clear_user(__cl_addr, __cl_size);		\
	__cl_size;							\
पूर्ण)

बाह्य दीर्घ __म_नकलन_from_user_यंत्र(अक्षर *__to, स्थिर अक्षर __user *__from, दीर्घ __len);

/*
 * म_नकलन_from_user: - Copy a NUL terminated string from userspace.
 * @dst:   Destination address, in kernel space.  This buffer must be at
 *	   least @count bytes दीर्घ.
 * @src:   Source address, in user space.
 * @count: Maximum number of bytes to copy, including the trailing NUL.
 *
 * Copies a NUL-terminated string from userspace to kernel space.
 *
 * On success, वापसs the length of the string (not including the trailing
 * NUL).
 *
 * If access to userspace fails, वापसs -EFAULT (some data may have been
 * copied).
 *
 * If @count is smaller than the length of the string, copies @count bytes
 * and वापसs @count.
 */
अटल अंतरभूत दीर्घ
म_नकलन_from_user(अक्षर *__to, स्थिर अक्षर __user *__from, दीर्घ __len)
अणु
	दीर्घ res;

	अगर (!access_ok(__from, __len))
		वापस -EFAULT;

	might_fault();
	__यंत्र__ __अस्थिर__(
		"move\t$4, %1\n\t"
		"move\t$5, %2\n\t"
		"move\t$6, %3\n\t"
		__MODULE_JAL(__म_नकलन_from_user_यंत्र)
		"move\t%0, $2"
		: "=r" (res)
		: "r" (__to), "r" (__from), "r" (__len)
		: "$2", "$3", "$4", "$5", "$6", __UA_t0, "$31", "memory");

	वापस res;
पूर्ण

बाह्य दीर्घ __strnlen_user_यंत्र(स्थिर अक्षर __user *s, दीर्घ n);

/*
 * strnlen_user: - Get the size of a string in user space.
 * @str: The string to measure.
 *
 * Context: User context only. This function may sleep अगर pagefaults are
 *          enabled.
 *
 * Get the size of a NUL-terminated string in user space.
 *
 * Returns the size of the string INCLUDING the terminating NUL.
 * On exception, वापसs 0.
 * If the string is too दीर्घ, वापसs a value greater than @n.
 */
अटल अंतरभूत दीर्घ strnlen_user(स्थिर अक्षर __user *s, दीर्घ n)
अणु
	दीर्घ res;

	अगर (!access_ok(s, 1))
		वापस 0;

	might_fault();
	__यंत्र__ __अस्थिर__(
		"move\t$4, %1\n\t"
		"move\t$5, %2\n\t"
		__MODULE_JAL(__strnlen_user_यंत्र)
		"move\t%0, $2"
		: "=r" (res)
		: "r" (s), "r" (n)
		: "$2", "$4", "$5", __UA_t0, "$31");

	वापस res;
पूर्ण

#पूर्ण_अगर /* _ASM_UACCESS_H */
