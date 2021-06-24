<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_UACCESS_H
#घोषणा __ALPHA_UACCESS_H

/*
 * The fs value determines whether argument validity checking should be
 * perक्रमmed or not.  If get_fs() == USER_DS, checking is perक्रमmed, with
 * get_fs() == KERNEL_DS, checking is bypassed.
 *
 * Or at least it did once upon a समय.  Nowadays it is a mask that
 * defines which bits of the address space are off limits.  This is a
 * wee bit faster than the above.
 *
 * For historical reasons, these macros are grossly misnamed.
 */

#घोषणा KERNEL_DS	((mm_segment_t) अणु 0UL पूर्ण)
#घोषणा USER_DS		((mm_segment_t) अणु -0x40000000000UL पूर्ण)

#घोषणा get_fs()  (current_thपढ़ो_info()->addr_limit)
#घोषणा set_fs(x) (current_thपढ़ो_info()->addr_limit = (x))

#घोषणा uaccess_kernel()	(get_fs().seg == KERNEL_DS.seg)

/*
 * Is a address valid? This करोes a straightक्रमward calculation rather
 * than tests.
 *
 * Address valid अगर:
 *  - "addr" करोesn't have any high-bits set
 *  - AND "size" करोesn't have any high-bits set
 *  - AND "addr+size-(size != 0)" करोesn't have any high-bits set
 *  - OR we are in kernel mode.
 */
#घोषणा __access_ok(addr, size) (अणु				\
	अचिन्हित दीर्घ __ao_a = (addr), __ao_b = (size);		\
	अचिन्हित दीर्घ __ao_end = __ao_a + __ao_b - !!__ao_b;	\
	(get_fs().seg & (__ao_a | __ao_b | __ao_end)) == 0; पूर्ण)

#घोषणा access_ok(addr, size)				\
(अणु							\
	__chk_user_ptr(addr);				\
	__access_ok(((अचिन्हित दीर्घ)(addr)), (size));	\
पूर्ण)

/*
 * These are the मुख्य single-value transfer routines.  They स्वतःmatically
 * use the right size अगर we just have the right poपूर्णांकer type.
 *
 * As the alpha uses the same address space क्रम kernel and user
 * data, we can just करो these as direct assignments.  (Of course, the
 * exception handling means that it's no दीर्घer "just"...)
 *
 * Careful to not
 * (a) re-use the arguments क्रम side effects (माप/typeof is ok)
 * (b) require any knowledge of processes at this stage
 */
#घोषणा put_user(x, ptr) \
  __put_user_check((__typeof__(*(ptr)))(x), (ptr), माप(*(ptr)))
#घोषणा get_user(x, ptr) \
  __get_user_check((x), (ptr), माप(*(ptr)))

/*
 * The "__xxx" versions करो not करो address space checking, useful when
 * करोing multiple accesses to the same area (the programmer has to करो the
 * checks by hand with "access_ok()")
 */
#घोषणा __put_user(x, ptr) \
  __put_user_nocheck((__typeof__(*(ptr)))(x), (ptr), माप(*(ptr)))
#घोषणा __get_user(x, ptr) \
  __get_user_nocheck((x), (ptr), माप(*(ptr)))
  
/*
 * The "lda %1, 2b-1b(%0)" bits are magic to get the assembler to
 * encode the bits we need क्रम resolving the exception.  See the
 * more extensive comments with fixup_अंतरभूत_exception below क्रम
 * more inक्रमmation.
 */
#घोषणा EXC(label,cont,res,err)				\
	".section __ex_table,\"a\"\n"			\
	"	.long "#label"-.\n"			\
	"	lda "#res","#cont"-"#label"("#err")\n"	\
	".previous\n"

बाह्य व्योम __get_user_unknown(व्योम);

#घोषणा __get_user_nocheck(x, ptr, size)			\
(अणु								\
	दीर्घ __gu_err = 0;					\
	अचिन्हित दीर्घ __gu_val;					\
	__chk_user_ptr(ptr);					\
	चयन (size) अणु						\
	  हाल 1: __get_user_8(ptr); अवरोध;			\
	  हाल 2: __get_user_16(ptr); अवरोध;			\
	  हाल 4: __get_user_32(ptr); अवरोध;			\
	  हाल 8: __get_user_64(ptr); अवरोध;			\
	  शेष: __get_user_unknown(); अवरोध;			\
	पूर्ण							\
	(x) = (__क्रमce __typeof__(*(ptr))) __gu_val;		\
	__gu_err;						\
पूर्ण)

#घोषणा __get_user_check(x, ptr, size)				\
(अणु								\
	दीर्घ __gu_err = -EFAULT;				\
	अचिन्हित दीर्घ __gu_val = 0;				\
	स्थिर __typeof__(*(ptr)) __user *__gu_addr = (ptr);	\
	अगर (__access_ok((अचिन्हित दीर्घ)__gu_addr, size)) अणु	\
		__gu_err = 0;					\
		चयन (size) अणु					\
		  हाल 1: __get_user_8(__gu_addr); अवरोध;	\
		  हाल 2: __get_user_16(__gu_addr); अवरोध;	\
		  हाल 4: __get_user_32(__gu_addr); अवरोध;	\
		  हाल 8: __get_user_64(__gu_addr); अवरोध;	\
		  शेष: __get_user_unknown(); अवरोध;		\
		पूर्ण						\
	पूर्ण							\
	(x) = (__क्रमce __typeof__(*(ptr))) __gu_val;		\
	__gu_err;						\
पूर्ण)

काष्ठा __large_काष्ठा अणु अचिन्हित दीर्घ buf[100]; पूर्ण;
#घोषणा __m(x) (*(काष्ठा __large_काष्ठा __user *)(x))

#घोषणा __get_user_64(addr)				\
	__यंत्र__("1: ldq %0,%2\n"			\
	"2:\n"						\
	EXC(1b,2b,%0,%1)				\
		: "=r"(__gu_val), "=r"(__gu_err)	\
		: "m"(__m(addr)), "1"(__gu_err))

#घोषणा __get_user_32(addr)				\
	__यंत्र__("1: ldl %0,%2\n"			\
	"2:\n"						\
	EXC(1b,2b,%0,%1)				\
		: "=r"(__gu_val), "=r"(__gu_err)	\
		: "m"(__m(addr)), "1"(__gu_err))

#अगर_घोषित __alpha_bwx__
/* Those lucky bastards with ev56 and later CPUs can करो byte/word moves.  */

#घोषणा __get_user_16(addr)				\
	__यंत्र__("1: ldwu %0,%2\n"			\
	"2:\n"						\
	EXC(1b,2b,%0,%1)				\
		: "=r"(__gu_val), "=r"(__gu_err)	\
		: "m"(__m(addr)), "1"(__gu_err))

#घोषणा __get_user_8(addr)				\
	__यंत्र__("1: ldbu %0,%2\n"			\
	"2:\n"						\
	EXC(1b,2b,%0,%1)				\
		: "=r"(__gu_val), "=r"(__gu_err)	\
		: "m"(__m(addr)), "1"(__gu_err))
#अन्यथा
/* Unक्रमtunately, we can't get an unaligned access trap क्रम the sub-word
   load, so we have to करो a general unaligned operation.  */

#घोषणा __get_user_16(addr)						\
अणु									\
	दीर्घ __gu_पंचांगp;							\
	__यंत्र__("1: ldq_u %0,0(%3)\n"					\
	"2:	ldq_u %1,1(%3)\n"					\
	"	extwl %0,%3,%0\n"					\
	"	extwh %1,%3,%1\n"					\
	"	or %0,%1,%0\n"						\
	"3:\n"								\
	EXC(1b,3b,%0,%2)						\
	EXC(2b,3b,%0,%2)						\
		: "=&r"(__gu_val), "=&r"(__gu_पंचांगp), "=r"(__gu_err)	\
		: "r"(addr), "2"(__gu_err));				\
पूर्ण

#घोषणा __get_user_8(addr)						\
	__यंत्र__("1: ldq_u %0,0(%2)\n"					\
	"	extbl %0,%2,%0\n"					\
	"2:\n"								\
	EXC(1b,2b,%0,%1)						\
		: "=&r"(__gu_val), "=r"(__gu_err)			\
		: "r"(addr), "1"(__gu_err))
#पूर्ण_अगर

बाह्य व्योम __put_user_unknown(व्योम);

#घोषणा __put_user_nocheck(x, ptr, size)			\
(अणु								\
	दीर्घ __pu_err = 0;					\
	__chk_user_ptr(ptr);					\
	चयन (size) अणु						\
	  हाल 1: __put_user_8(x, ptr); अवरोध;			\
	  हाल 2: __put_user_16(x, ptr); अवरोध;			\
	  हाल 4: __put_user_32(x, ptr); अवरोध;			\
	  हाल 8: __put_user_64(x, ptr); अवरोध;			\
	  शेष: __put_user_unknown(); अवरोध;			\
	पूर्ण							\
	__pu_err;						\
पूर्ण)

#घोषणा __put_user_check(x, ptr, size)				\
(अणु								\
	दीर्घ __pu_err = -EFAULT;				\
	__typeof__(*(ptr)) __user *__pu_addr = (ptr);		\
	अगर (__access_ok((अचिन्हित दीर्घ)__pu_addr, size)) अणु	\
		__pu_err = 0;					\
		चयन (size) अणु					\
		  हाल 1: __put_user_8(x, __pu_addr); अवरोध;	\
		  हाल 2: __put_user_16(x, __pu_addr); अवरोध;	\
		  हाल 4: __put_user_32(x, __pu_addr); अवरोध;	\
		  हाल 8: __put_user_64(x, __pu_addr); अवरोध;	\
		  शेष: __put_user_unknown(); अवरोध;		\
		पूर्ण						\
	पूर्ण							\
	__pu_err;						\
पूर्ण)

/*
 * The "__put_user_xx()" macros tell gcc they पढ़ो from memory
 * instead of writing: this is because they करो not ग_लिखो to
 * any memory gcc knows about, so there are no aliasing issues
 */
#घोषणा __put_user_64(x, addr)					\
__यंत्र__ __अस्थिर__("1: stq %r2,%1\n"				\
	"2:\n"							\
	EXC(1b,2b,$31,%0)					\
		: "=r"(__pu_err)				\
		: "m" (__m(addr)), "rJ" (x), "0"(__pu_err))

#घोषणा __put_user_32(x, addr)					\
__यंत्र__ __अस्थिर__("1: stl %r2,%1\n"				\
	"2:\n"							\
	EXC(1b,2b,$31,%0)					\
		: "=r"(__pu_err)				\
		: "m"(__m(addr)), "rJ"(x), "0"(__pu_err))

#अगर_घोषित __alpha_bwx__
/* Those lucky bastards with ev56 and later CPUs can करो byte/word moves.  */

#घोषणा __put_user_16(x, addr)					\
__यंत्र__ __अस्थिर__("1: stw %r2,%1\n"				\
	"2:\n"							\
	EXC(1b,2b,$31,%0)					\
		: "=r"(__pu_err)				\
		: "m"(__m(addr)), "rJ"(x), "0"(__pu_err))

#घोषणा __put_user_8(x, addr)					\
__यंत्र__ __अस्थिर__("1: stb %r2,%1\n"				\
	"2:\n"							\
	EXC(1b,2b,$31,%0)					\
		: "=r"(__pu_err)				\
		: "m"(__m(addr)), "rJ"(x), "0"(__pu_err))
#अन्यथा
/* Unक्रमtunately, we can't get an unaligned access trap क्रम the sub-word
   ग_लिखो, so we have to करो a general unaligned operation.  */

#घोषणा __put_user_16(x, addr)					\
अणु								\
	दीर्घ __pu_पंचांगp1, __pu_पंचांगp2, __pu_पंचांगp3, __pu_पंचांगp4;	\
	__यंत्र__ __अस्थिर__(					\
	"1:	ldq_u %2,1(%5)\n"				\
	"2:	ldq_u %1,0(%5)\n"				\
	"	inswh %6,%5,%4\n"				\
	"	inswl %6,%5,%3\n"				\
	"	mskwh %2,%5,%2\n"				\
	"	mskwl %1,%5,%1\n"				\
	"	or %2,%4,%2\n"					\
	"	or %1,%3,%1\n"					\
	"3:	stq_u %2,1(%5)\n"				\
	"4:	stq_u %1,0(%5)\n"				\
	"5:\n"							\
	EXC(1b,5b,$31,%0)					\
	EXC(2b,5b,$31,%0)					\
	EXC(3b,5b,$31,%0)					\
	EXC(4b,5b,$31,%0)					\
		: "=r"(__pu_err), "=&r"(__pu_पंचांगp1), 		\
		  "=&r"(__pu_पंचांगp2), "=&r"(__pu_पंचांगp3), 		\
		  "=&r"(__pu_पंचांगp4)				\
		: "r"(addr), "r"((अचिन्हित दीर्घ)(x)), "0"(__pu_err)); \
पूर्ण

#घोषणा __put_user_8(x, addr)					\
अणु								\
	दीर्घ __pu_पंचांगp1, __pu_पंचांगp2;				\
	__यंत्र__ __अस्थिर__(					\
	"1:	ldq_u %1,0(%4)\n"				\
	"	insbl %3,%4,%2\n"				\
	"	mskbl %1,%4,%1\n"				\
	"	or %1,%2,%1\n"					\
	"2:	stq_u %1,0(%4)\n"				\
	"3:\n"							\
	EXC(1b,3b,$31,%0)					\
	EXC(2b,3b,$31,%0)					\
		: "=r"(__pu_err), 				\
	  	  "=&r"(__pu_पंचांगp1), "=&r"(__pu_पंचांगp2)		\
		: "r"((अचिन्हित दीर्घ)(x)), "r"(addr), "0"(__pu_err)); \
पूर्ण
#पूर्ण_अगर


/*
 * Complex access routines
 */

बाह्य दीर्घ __copy_user(व्योम *to, स्थिर व्योम *from, दीर्घ len);

अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ len)
अणु
	वापस __copy_user(to, (__क्रमce स्थिर व्योम *)from, len);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ len)
अणु
	वापस __copy_user((__क्रमce व्योम *)to, from, len);
पूर्ण

बाह्य दीर्घ __clear_user(व्योम __user *to, दीर्घ len);

बाह्य अंतरभूत दीर्घ
clear_user(व्योम __user *to, दीर्घ len)
अणु
	अगर (__access_ok((अचिन्हित दीर्घ)to, len))
		len = __clear_user(to, len);
	वापस len;
पूर्ण

#घोषणा user_addr_max() \
        (uaccess_kernel() ? ~0UL : TASK_SIZE)

बाह्य दीर्घ म_नकलन_from_user(अक्षर *dest, स्थिर अक्षर __user *src, दीर्घ count);
बाह्य __must_check दीर्घ strnlen_user(स्थिर अक्षर __user *str, दीर्घ n);

#समावेश <यंत्र/extable.h>

#पूर्ण_अगर /* __ALPHA_UACCESS_H */
