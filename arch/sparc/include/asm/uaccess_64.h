<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_UACCESS_H
#घोषणा _ASM_UACCESS_H

/*
 * User space memory access functions
 */

#समावेश <linux/compiler.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/asi.h>
#समावेश <यंत्र/spitfire.h>

#समावेश <यंत्र/processor.h>

/*
 * Sparc64 is segmented, though more like the M68K than the I386.
 * We use the secondary ASI to address user memory, which references a
 * completely dअगरferent VM map, thus there is zero chance of the user
 * करोing something queer and tricking us पूर्णांकo poking kernel memory.
 *
 * What is left here is basically what is needed क्रम the other parts of
 * the kernel that expect to be able to manipulate, erum, "segments".
 * Or perhaps more properly, permissions.
 *
 * "For historical reasons, these macros are grossly misnamed." -Linus
 */

#घोषणा KERNEL_DS   ((mm_segment_t) अणु ASI_P पूर्ण)
#घोषणा USER_DS     ((mm_segment_t) अणु ASI_AIUS पूर्ण)	/* har har har */

#घोषणा get_fs() ((mm_segment_t)अणु(current_thपढ़ो_info()->current_ds)पूर्ण)

#घोषणा uaccess_kernel() (get_fs().seg == KERNEL_DS.seg)

#घोषणा set_fs(val)								\
करो अणु										\
	current_thपढ़ो_info()->current_ds = (val).seg;				\
	__यंत्र__ __अस्थिर__ ("wr %%g0, %0, %%asi" : : "r" ((val).seg));	\
पूर्ण जबतक(0)

/*
 * Test whether a block of memory is a valid user space address.
 * Returns 0 अगर the range is valid, nonzero otherwise.
 */
अटल अंतरभूत bool __chk_range_not_ok(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size, अचिन्हित दीर्घ limit)
अणु
	अगर (__builtin_स्थिरant_p(size))
		वापस addr > limit - size;

	addr += size;
	अगर (addr < size)
		वापस true;

	वापस addr > limit;
पूर्ण

#घोषणा __range_not_ok(addr, size, limit)                               \
(अणु                                                                      \
	__chk_user_ptr(addr);                                           \
	__chk_range_not_ok((अचिन्हित दीर्घ __क्रमce)(addr), size, limit); \
पूर्ण)

अटल अंतरभूत पूर्णांक __access_ok(स्थिर व्योम __user * addr, अचिन्हित दीर्घ size)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक access_ok(स्थिर व्योम __user * addr, अचिन्हित दीर्घ size)
अणु
	वापस 1;
पूर्ण

व्योम __retl_efault(व्योम);

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
	__put_user_nocheck((__typeof__(*(ptr)))(x), __pu_addr, माप(*(ptr)));\
पूर्ण)

#घोषणा get_user(x, ptr) (अणु \
	अचिन्हित दीर्घ __gu_addr = (अचिन्हित दीर्घ)(ptr); \
	__chk_user_ptr(ptr); \
	__get_user_nocheck((x), __gu_addr, माप(*(ptr)), __typeof__(*(ptr)));\
पूर्ण)

#घोषणा __put_user(x, ptr) put_user(x, ptr)
#घोषणा __get_user(x, ptr) get_user(x, ptr)

काष्ठा __large_काष्ठा अणु अचिन्हित दीर्घ buf[100]; पूर्ण;
#घोषणा __m(x) ((काष्ठा __large_काष्ठा *)(x))

#घोषणा __put_user_nocheck(data, addr, size) (अणु			\
	रेजिस्टर पूर्णांक __pu_ret;					\
	चयन (size) अणु						\
	हाल 1: __put_user_यंत्र(data, b, addr, __pu_ret); अवरोध;	\
	हाल 2: __put_user_यंत्र(data, h, addr, __pu_ret); अवरोध;	\
	हाल 4: __put_user_यंत्र(data, w, addr, __pu_ret); अवरोध;	\
	हाल 8: __put_user_यंत्र(data, x, addr, __pu_ret); अवरोध;	\
	शेष: __pu_ret = __put_user_bad(); अवरोध;		\
	पूर्ण							\
	__pu_ret;						\
पूर्ण)

#घोषणा __put_user_यंत्र(x, size, addr, ret)				\
__यंत्र__ __अस्थिर__(							\
		"/* Put user asm, inline. */\n"				\
	"1:\t"	"st"#size "a %1, [%2] %%asi\n\t"			\
		"clr	%0\n"						\
	"2:\n\n\t"							\
		".section .fixup,#alloc,#execinstr\n\t"			\
		".align	4\n"						\
	"3:\n\t"							\
		"sethi	%%hi(2b), %0\n\t"				\
		"jmpl	%0 + %%lo(2b), %%g0\n\t"			\
		" mov	%3, %0\n\n\t"					\
		".previous\n\t"						\
		".section __ex_table,\"a\"\n\t"				\
		".align	4\n\t"						\
		".word	1b, 3b\n\t"					\
		".previous\n\n\t"					\
	       : "=r" (ret) : "r" (x), "r" (__m(addr)),			\
		 "i" (-EFAULT))

पूर्णांक __put_user_bad(व्योम);

#घोषणा __get_user_nocheck(data, addr, size, type) (अणु			     \
	रेजिस्टर पूर्णांक __gu_ret;						     \
	रेजिस्टर अचिन्हित दीर्घ __gu_val;				     \
	चयन (size) अणु							     \
		हाल 1: __get_user_यंत्र(__gu_val, ub, addr, __gu_ret); अवरोध; \
		हाल 2: __get_user_यंत्र(__gu_val, uh, addr, __gu_ret); अवरोध; \
		हाल 4: __get_user_यंत्र(__gu_val, uw, addr, __gu_ret); अवरोध; \
		हाल 8: __get_user_यंत्र(__gu_val, x, addr, __gu_ret); अवरोध;  \
		शेष:						     \
			__gu_val = 0;					     \
			__gu_ret = __get_user_bad();			     \
			अवरोध;						     \
	पूर्ण 								     \
	data = (__क्रमce type) __gu_val;					     \
	 __gu_ret;							     \
पूर्ण)

#घोषणा __get_user_यंत्र(x, size, addr, ret)				\
__यंत्र__ __अस्थिर__(							\
		"/* Get user asm, inline. */\n"				\
	"1:\t"	"ld"#size "a [%2] %%asi, %1\n\t"			\
		"clr	%0\n"						\
	"2:\n\n\t"							\
		".section .fixup,#alloc,#execinstr\n\t"			\
		".align	4\n"						\
	"3:\n\t"							\
		"sethi	%%hi(2b), %0\n\t"				\
		"clr	%1\n\t"						\
		"jmpl	%0 + %%lo(2b), %%g0\n\t"			\
		" mov	%3, %0\n\n\t"					\
		".previous\n\t"						\
		".section __ex_table,\"a\"\n\t"				\
		".align	4\n\t"						\
		".word	1b, 3b\n\n\t"					\
		".previous\n\t"						\
	       : "=r" (ret), "=r" (x) : "r" (__m(addr)),		\
		 "i" (-EFAULT))

पूर्णांक __get_user_bad(व्योम);

अचिन्हित दीर्घ __must_check raw_copy_from_user(व्योम *to,
					     स्थिर व्योम __user *from,
					     अचिन्हित दीर्घ size);

अचिन्हित दीर्घ __must_check raw_copy_to_user(व्योम __user *to,
					   स्थिर व्योम *from,
					   अचिन्हित दीर्घ size);
#घोषणा INLINE_COPY_FROM_USER
#घोषणा INLINE_COPY_TO_USER

अचिन्हित दीर्घ __must_check raw_copy_in_user(व्योम __user *to,
					   स्थिर व्योम __user *from,
					   अचिन्हित दीर्घ size);

अचिन्हित दीर्घ __must_check __clear_user(व्योम __user *, अचिन्हित दीर्घ);

#घोषणा clear_user __clear_user

__must_check दीर्घ strnlen_user(स्थिर अक्षर __user *str, दीर्घ n);

काष्ठा pt_regs;
अचिन्हित दीर्घ compute_effective_address(काष्ठा pt_regs *,
					अचिन्हित पूर्णांक insn,
					अचिन्हित पूर्णांक rd);

#पूर्ण_अगर /* _ASM_UACCESS_H */
