<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_UACCESS_H
#घोषणा __ASM_SH_UACCESS_H

#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/extable.h>

#घोषणा __addr_ok(addr) \
	((अचिन्हित दीर्घ __क्रमce)(addr) < current_thपढ़ो_info()->addr_limit.seg)

/*
 * __access_ok: Check अगर address with size is OK or not.
 *
 * Uhhuh, this needs 33-bit arithmetic. We have a carry..
 *
 * sum := addr + size;  carry? --> flag = true;
 * अगर (sum >= addr_limit) flag = true;
 */
#घोषणा __access_ok(addr, size)	(अणु				\
	अचिन्हित दीर्घ __ao_a = (addr), __ao_b = (size);		\
	अचिन्हित दीर्घ __ao_end = __ao_a + __ao_b - !!__ao_b;	\
	__ao_end >= __ao_a && __addr_ok(__ao_end); पूर्ण)

#घोषणा access_ok(addr, size)	\
	(__chk_user_ptr(addr),		\
	 __access_ok((अचिन्हित दीर्घ __क्रमce)(addr), (size)))

#घोषणा user_addr_max()	(current_thपढ़ो_info()->addr_limit.seg)

/*
 * Uh, these should become the मुख्य single-value transfer routines ...
 * They स्वतःmatically use the right size अगर we just have the right
 * poपूर्णांकer type ...
 *
 * As SuperH uses the same address space क्रम kernel and user data, we
 * can just करो these as direct assignments.
 *
 * Careful to not
 * (a) re-use the arguments क्रम side effects (माप is ok)
 * (b) require any knowledge of processes at this stage
 */
#घोषणा put_user(x,ptr)		__put_user_check((x), (ptr), माप(*(ptr)))
#घोषणा get_user(x,ptr)		__get_user_check((x), (ptr), माप(*(ptr)))

/*
 * The "__xxx" versions करो not करो address space checking, useful when
 * करोing multiple accesses to the same area (the user has to करो the
 * checks by hand with "access_ok()")
 */
#घोषणा __put_user(x,ptr)	__put_user_nocheck((x), (ptr), माप(*(ptr)))
#घोषणा __get_user(x,ptr)	__get_user_nocheck((x), (ptr), माप(*(ptr)))

काष्ठा __large_काष्ठा अणु अचिन्हित दीर्घ buf[100]; पूर्ण;
#घोषणा __m(x) (*(काष्ठा __large_काष्ठा __user *)(x))

#घोषणा __get_user_nocheck(x,ptr,size)				\
(अणु								\
	दीर्घ __gu_err;						\
	अचिन्हित दीर्घ __gu_val;					\
	स्थिर __typeof__(*(ptr)) __user *__gu_addr = (ptr);	\
	__chk_user_ptr(ptr);					\
	__get_user_size(__gu_val, __gu_addr, (size), __gu_err);	\
	(x) = (__क्रमce __typeof__(*(ptr)))__gu_val;		\
	__gu_err;						\
पूर्ण)

#घोषणा __get_user_check(x,ptr,size)					\
(अणु									\
	दीर्घ __gu_err = -EFAULT;					\
	अचिन्हित दीर्घ __gu_val = 0;					\
	स्थिर __typeof__(*(ptr)) *__gu_addr = (ptr);			\
	अगर (likely(access_ok(__gu_addr, (size))))		\
		__get_user_size(__gu_val, __gu_addr, (size), __gu_err);	\
	(x) = (__क्रमce __typeof__(*(ptr)))__gu_val;			\
	__gu_err;							\
पूर्ण)

#घोषणा __put_user_nocheck(x,ptr,size)				\
(अणु								\
	दीर्घ __pu_err;						\
	__typeof__(*(ptr)) __user *__pu_addr = (ptr);		\
	__typeof__(*(ptr)) __pu_val = x;			\
	__chk_user_ptr(ptr);					\
	__put_user_size(__pu_val, __pu_addr, (size), __pu_err);	\
	__pu_err;						\
पूर्ण)

#घोषणा __put_user_check(x,ptr,size)				\
(अणु								\
	दीर्घ __pu_err = -EFAULT;				\
	__typeof__(*(ptr)) __user *__pu_addr = (ptr);		\
	__typeof__(*(ptr)) __pu_val = x;			\
	अगर (likely(access_ok(__pu_addr, size)))	\
		__put_user_size(__pu_val, __pu_addr, (size),	\
				__pu_err);			\
	__pu_err;						\
पूर्ण)

# include <यंत्र/uaccess_32.h>

बाह्य दीर्घ म_नकलन_from_user(अक्षर *dest, स्थिर अक्षर __user *src, दीर्घ count);

बाह्य __must_check दीर्घ strnlen_user(स्थिर अक्षर __user *str, दीर्घ n);

/* Generic arbitrary sized copy.  */
/* Return the number of bytes NOT copied */
__kernel_माप_प्रकार __copy_user(व्योम *to, स्थिर व्योम *from, __kernel_माप_प्रकार n);

अटल __always_अंतरभूत अचिन्हित दीर्घ
raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	वापस __copy_user(to, (__क्रमce व्योम *)from, n);
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ __must_check
raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	वापस __copy_user((__क्रमce व्योम *)to, from, n);
पूर्ण
#घोषणा INLINE_COPY_FROM_USER
#घोषणा INLINE_COPY_TO_USER

/*
 * Clear the area and वापस reमुख्यing number of bytes
 * (on failure.  Usually it's 0.)
 */
__kernel_माप_प्रकार __clear_user(व्योम *addr, __kernel_माप_प्रकार size);

#घोषणा clear_user(addr,n)						\
(अणु									\
	व्योम __user * __cl_addr = (addr);				\
	अचिन्हित दीर्घ __cl_size = (n);					\
									\
	अगर (__cl_size && access_ok(__cl_addr, __cl_size))		\
		__cl_size = __clear_user(__cl_addr, __cl_size);		\
									\
	__cl_size;							\
पूर्ण)

बाह्य व्योम *set_exception_table_vec(अचिन्हित पूर्णांक vec, व्योम *handler);

अटल अंतरभूत व्योम *set_exception_table_evt(अचिन्हित पूर्णांक evt, व्योम *handler)
अणु
	वापस set_exception_table_vec(evt >> 5, handler);
पूर्ण

काष्ठा mem_access अणु
	अचिन्हित दीर्घ (*from)(व्योम *dst, स्थिर व्योम __user *src, अचिन्हित दीर्घ cnt);
	अचिन्हित दीर्घ (*to)(व्योम __user *dst, स्थिर व्योम *src, अचिन्हित दीर्घ cnt);
पूर्ण;

पूर्णांक handle_unaligned_access(insn_माप_प्रकार inकाष्ठाion, काष्ठा pt_regs *regs,
			    काष्ठा mem_access *ma, पूर्णांक, अचिन्हित दीर्घ address);

#पूर्ण_अगर /* __ASM_SH_UACCESS_H */
