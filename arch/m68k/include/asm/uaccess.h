<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __M68K_UACCESS_H
#घोषणा __M68K_UACCESS_H

#अगर_घोषित CONFIG_MMU

/*
 * User space memory access functions
 */
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/extable.h>

/* We let the MMU करो all checking */
अटल अंतरभूत पूर्णांक access_ok(स्थिर व्योम __user *addr,
			    अचिन्हित दीर्घ size)
अणु
	वापस 1;
पूर्ण

/*
 * Not all varients of the 68k family support the notion of address spaces.
 * The traditional 680x0 parts करो, and they use the sfc/dfc रेजिस्टरs and
 * the "moves" inकाष्ठाion to access user space from kernel space. Other
 * family members like ColdFire करोn't support this, and only have a single
 * address space, and use the usual "move" inकाष्ठाion क्रम user space access.
 *
 * Outside of this dअगरference the user space access functions are the same.
 * So lets keep the code simple and just define in what we need to use.
 */
#अगर_घोषित CONFIG_CPU_HAS_ADDRESS_SPACES
#घोषणा	MOVES	"moves"
#अन्यथा
#घोषणा	MOVES	"move"
#पूर्ण_अगर

बाह्य पूर्णांक __put_user_bad(व्योम);
बाह्य पूर्णांक __get_user_bad(व्योम);

#घोषणा __put_user_यंत्र(res, x, ptr, bwl, reg, err)	\
यंत्र अस्थिर ("\n"					\
	"1:	"MOVES"."#bwl"	%2,%1\n"		\
	"2:\n"						\
	"	.section .fixup,\"ax\"\n"		\
	"	.even\n"				\
	"10:	moveq.l	%3,%0\n"			\
	"	jra 2b\n"				\
	"	.previous\n"				\
	"\n"						\
	"	.section __ex_table,\"a\"\n"		\
	"	.align	4\n"				\
	"	.long	1b,10b\n"			\
	"	.long	2b,10b\n"			\
	"	.previous"				\
	: "+d" (res), "=m" (*(ptr))			\
	: #reg (x), "i" (err))

/*
 * These are the मुख्य single-value transfer routines.  They स्वतःmatically
 * use the right size अगर we just have the right poपूर्णांकer type.
 */

#घोषणा __put_user(x, ptr)						\
(अणु									\
	typeof(*(ptr)) __pu_val = (x);					\
	पूर्णांक __pu_err = 0;						\
	__chk_user_ptr(ptr);						\
	चयन (माप (*(ptr))) अणु					\
	हाल 1:								\
		__put_user_यंत्र(__pu_err, __pu_val, ptr, b, d, -EFAULT);	\
		अवरोध;							\
	हाल 2:								\
		__put_user_यंत्र(__pu_err, __pu_val, ptr, w, r, -EFAULT);	\
		अवरोध;							\
	हाल 4:								\
		__put_user_यंत्र(__pu_err, __pu_val, ptr, l, r, -EFAULT);	\
		अवरोध;							\
	हाल 8:								\
 	    अणु								\
 		स्थिर व्योम __user *__pu_ptr = (ptr);			\
		यंत्र अस्थिर ("\n"					\
			"1:	"MOVES".l	%2,(%1)+\n"		\
			"2:	"MOVES".l	%R2,(%1)\n"		\
			"3:\n"						\
			"	.section .fixup,\"ax\"\n"		\
			"	.even\n"				\
			"10:	movel %3,%0\n"				\
			"	jra 3b\n"				\
			"	.previous\n"				\
			"\n"						\
			"	.section __ex_table,\"a\"\n"		\
			"	.align 4\n"				\
			"	.long 1b,10b\n"				\
			"	.long 2b,10b\n"				\
			"	.long 3b,10b\n"				\
			"	.previous"				\
			: "+d" (__pu_err), "+a" (__pu_ptr)		\
			: "r" (__pu_val), "i" (-EFAULT)			\
			: "memory");					\
		अवरोध;							\
	    पूर्ण								\
	शेष:							\
		__pu_err = __put_user_bad();				\
		अवरोध;							\
	पूर्ण								\
	__pu_err;							\
पूर्ण)
#घोषणा put_user(x, ptr)	__put_user(x, ptr)


#घोषणा __get_user_यंत्र(res, x, ptr, type, bwl, reg, err) (अणु		\
	type __gu_val;							\
	यंत्र अस्थिर ("\n"						\
		"1:	"MOVES"."#bwl"	%2,%1\n"			\
		"2:\n"							\
		"	.section .fixup,\"ax\"\n"			\
		"	.even\n"					\
		"10:	move.l	%3,%0\n"				\
		"	sub.l	%1,%1\n"				\
		"	jra	2b\n"					\
		"	.previous\n"					\
		"\n"							\
		"	.section __ex_table,\"a\"\n"			\
		"	.align	4\n"					\
		"	.long	1b,10b\n"				\
		"	.previous"					\
		: "+d" (res), "=&" #reg (__gu_val)			\
		: "m" (*(ptr)), "i" (err));				\
	(x) = (__क्रमce typeof(*(ptr)))(__क्रमce अचिन्हित दीर्घ)__gu_val;	\
पूर्ण)

#घोषणा __get_user(x, ptr)						\
(अणु									\
	पूर्णांक __gu_err = 0;						\
	__chk_user_ptr(ptr);						\
	चयन (माप(*(ptr))) अणु					\
	हाल 1:								\
		__get_user_यंत्र(__gu_err, x, ptr, u8, b, d, -EFAULT);	\
		अवरोध;							\
	हाल 2:								\
		__get_user_यंत्र(__gu_err, x, ptr, u16, w, r, -EFAULT);	\
		अवरोध;							\
	हाल 4:								\
		__get_user_यंत्र(__gu_err, x, ptr, u32, l, r, -EFAULT);	\
		अवरोध;							\
	हाल 8: अणु							\
		स्थिर व्योम __user *__gu_ptr = (ptr);			\
		जोड़ अणु							\
			u64 l;						\
			__typeof__(*(ptr)) t;				\
		पूर्ण __gu_val;						\
		यंत्र अस्थिर ("\n"					\
			"1:	"MOVES".l	(%2)+,%1\n"		\
			"2:	"MOVES".l	(%2),%R1\n"		\
			"3:\n"						\
			"	.section .fixup,\"ax\"\n"		\
			"	.even\n"				\
			"10:	move.l	%3,%0\n"			\
			"	sub.l	%1,%1\n"			\
			"	sub.l	%R1,%R1\n"			\
			"	jra	3b\n"				\
			"	.previous\n"				\
			"\n"						\
			"	.section __ex_table,\"a\"\n"		\
			"	.align	4\n"				\
			"	.long	1b,10b\n"			\
			"	.long	2b,10b\n"			\
			"	.previous"				\
			: "+d" (__gu_err), "=&r" (__gu_val.l),		\
			  "+a" (__gu_ptr)				\
			: "i" (-EFAULT)					\
			: "memory");					\
		(x) = __gu_val.t;					\
		अवरोध;							\
	पूर्ण								\
	शेष:							\
		__gu_err = __get_user_bad();				\
		अवरोध;							\
	पूर्ण								\
	__gu_err;							\
पूर्ण)
#घोषणा get_user(x, ptr) __get_user(x, ptr)

अचिन्हित दीर्घ __generic_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n);
अचिन्हित दीर्घ __generic_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n);

#घोषणा __suffix0
#घोषणा __suffix1 b
#घोषणा __suffix2 w
#घोषणा __suffix4 l

#घोषणा ____स्थिरant_copy_from_user_यंत्र(res, to, from, पंचांगp, n1, n2, n3, s1, s2, s3)\
	यंत्र अस्थिर ("\n"						\
		"1:	"MOVES"."#s1"	(%2)+,%3\n"			\
		"	move."#s1"	%3,(%1)+\n"			\
		"	.ifnc	\""#s2"\",\"\"\n"			\
		"2:	"MOVES"."#s2"	(%2)+,%3\n"			\
		"	move."#s2"	%3,(%1)+\n"			\
		"	.ifnc	\""#s3"\",\"\"\n"			\
		"3:	"MOVES"."#s3"	(%2)+,%3\n"			\
		"	move."#s3"	%3,(%1)+\n"			\
		"	.endif\n"					\
		"	.endif\n"					\
		"4:\n"							\
		"	.section __ex_table,\"a\"\n"			\
		"	.align	4\n"					\
		"	.long	1b,10f\n"				\
		"	.ifnc	\""#s2"\",\"\"\n"			\
		"	.long	2b,20f\n"				\
		"	.ifnc	\""#s3"\",\"\"\n"			\
		"	.long	3b,30f\n"				\
		"	.endif\n"					\
		"	.endif\n"					\
		"	.previous\n"					\
		"\n"							\
		"	.section .fixup,\"ax\"\n"			\
		"	.even\n"					\
		"10:	addq.l #"#n1",%0\n"				\
		"	.ifnc	\""#s2"\",\"\"\n"			\
		"20:	addq.l #"#n2",%0\n"				\
		"	.ifnc	\""#s3"\",\"\"\n"			\
		"30:	addq.l #"#n3",%0\n"				\
		"	.endif\n"					\
		"	.endif\n"					\
		"	jra	4b\n"					\
		"	.previous\n"					\
		: "+d" (res), "+&a" (to), "+a" (from), "=&d" (पंचांगp)	\
		: : "memory")

#घोषणा ___स्थिरant_copy_from_user_यंत्र(res, to, from, पंचांगp, n1, n2, n3, s1, s2, s3)\
	____स्थिरant_copy_from_user_यंत्र(res, to, from, पंचांगp, n1, n2, n3, s1, s2, s3)
#घोषणा __स्थिरant_copy_from_user_यंत्र(res, to, from, पंचांगp, n1, n2, n3)	\
	___स्थिरant_copy_from_user_यंत्र(res, to, from, पंचांगp, n1, n2, n3,  \
					__suffix##n1, __suffix##n2, __suffix##n3)

अटल __always_अंतरभूत अचिन्हित दीर्घ
__स्थिरant_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ res = 0, पंचांगp;

	चयन (n) अणु
	हाल 1:
		__स्थिरant_copy_from_user_यंत्र(res, to, from, पंचांगp, 1, 0, 0);
		अवरोध;
	हाल 2:
		__स्थिरant_copy_from_user_यंत्र(res, to, from, पंचांगp, 2, 0, 0);
		अवरोध;
	हाल 3:
		__स्थिरant_copy_from_user_यंत्र(res, to, from, पंचांगp, 2, 1, 0);
		अवरोध;
	हाल 4:
		__स्थिरant_copy_from_user_यंत्र(res, to, from, पंचांगp, 4, 0, 0);
		अवरोध;
	हाल 5:
		__स्थिरant_copy_from_user_यंत्र(res, to, from, पंचांगp, 4, 1, 0);
		अवरोध;
	हाल 6:
		__स्थिरant_copy_from_user_यंत्र(res, to, from, पंचांगp, 4, 2, 0);
		अवरोध;
	हाल 7:
		__स्थिरant_copy_from_user_यंत्र(res, to, from, पंचांगp, 4, 2, 1);
		अवरोध;
	हाल 8:
		__स्थिरant_copy_from_user_यंत्र(res, to, from, पंचांगp, 4, 4, 0);
		अवरोध;
	हाल 9:
		__स्थिरant_copy_from_user_यंत्र(res, to, from, पंचांगp, 4, 4, 1);
		अवरोध;
	हाल 10:
		__स्थिरant_copy_from_user_यंत्र(res, to, from, पंचांगp, 4, 4, 2);
		अवरोध;
	हाल 12:
		__स्थिरant_copy_from_user_यंत्र(res, to, from, पंचांगp, 4, 4, 4);
		अवरोध;
	शेष:
		/* we limit the अंतरभूतd version to 3 moves */
		वापस __generic_copy_from_user(to, from, n);
	पूर्ण

	वापस res;
पूर्ण

#घोषणा __स्थिरant_copy_to_user_यंत्र(res, to, from, पंचांगp, n, s1, s2, s3)	\
	यंत्र अस्थिर ("\n"						\
		"	move."#s1"	(%2)+,%3\n"			\
		"11:	"MOVES"."#s1"	%3,(%1)+\n"			\
		"12:	move."#s2"	(%2)+,%3\n"			\
		"21:	"MOVES"."#s2"	%3,(%1)+\n"			\
		"22:\n"							\
		"	.ifnc	\""#s3"\",\"\"\n"			\
		"	move."#s3"	(%2)+,%3\n"			\
		"31:	"MOVES"."#s3"	%3,(%1)+\n"			\
		"32:\n"							\
		"	.endif\n"					\
		"4:\n"							\
		"\n"							\
		"	.section __ex_table,\"a\"\n"			\
		"	.align	4\n"					\
		"	.long	11b,5f\n"				\
		"	.long	12b,5f\n"				\
		"	.long	21b,5f\n"				\
		"	.long	22b,5f\n"				\
		"	.ifnc	\""#s3"\",\"\"\n"			\
		"	.long	31b,5f\n"				\
		"	.long	32b,5f\n"				\
		"	.endif\n"					\
		"	.previous\n"					\
		"\n"							\
		"	.section .fixup,\"ax\"\n"			\
		"	.even\n"					\
		"5:	moveq.l	#"#n",%0\n"				\
		"	jra	4b\n"					\
		"	.previous\n"					\
		: "+d" (res), "+a" (to), "+a" (from), "=&d" (पंचांगp)	\
		: : "memory")

अटल __always_अंतरभूत अचिन्हित दीर्घ
__स्थिरant_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ res = 0, पंचांगp;

	चयन (n) अणु
	हाल 1:
		__put_user_यंत्र(res, *(u8 *)from, (u8 __user *)to, b, d, 1);
		अवरोध;
	हाल 2:
		__put_user_यंत्र(res, *(u16 *)from, (u16 __user *)to, w, r, 2);
		अवरोध;
	हाल 3:
		__स्थिरant_copy_to_user_यंत्र(res, to, from, पंचांगp, 3, w, b,);
		अवरोध;
	हाल 4:
		__put_user_यंत्र(res, *(u32 *)from, (u32 __user *)to, l, r, 4);
		अवरोध;
	हाल 5:
		__स्थिरant_copy_to_user_यंत्र(res, to, from, पंचांगp, 5, l, b,);
		अवरोध;
	हाल 6:
		__स्थिरant_copy_to_user_यंत्र(res, to, from, पंचांगp, 6, l, w,);
		अवरोध;
	हाल 7:
		__स्थिरant_copy_to_user_यंत्र(res, to, from, पंचांगp, 7, l, w, b);
		अवरोध;
	हाल 8:
		__स्थिरant_copy_to_user_यंत्र(res, to, from, पंचांगp, 8, l, l,);
		अवरोध;
	हाल 9:
		__स्थिरant_copy_to_user_यंत्र(res, to, from, पंचांगp, 9, l, l, b);
		अवरोध;
	हाल 10:
		__स्थिरant_copy_to_user_यंत्र(res, to, from, पंचांगp, 10, l, l, w);
		अवरोध;
	हाल 12:
		__स्थिरant_copy_to_user_यंत्र(res, to, from, पंचांगp, 12, l, l, l);
		अवरोध;
	शेष:
		/* limit the अंतरभूतd version to 3 moves */
		वापस __generic_copy_to_user(to, from, n);
	पूर्ण

	वापस res;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	अगर (__builtin_स्थिरant_p(n))
		वापस __स्थिरant_copy_from_user(to, from, n);
	वापस __generic_copy_from_user(to, from, n);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	अगर (__builtin_स्थिरant_p(n))
		वापस __स्थिरant_copy_to_user(to, from, n);
	वापस __generic_copy_to_user(to, from, n);
पूर्ण
#घोषणा INLINE_COPY_FROM_USER
#घोषणा INLINE_COPY_TO_USER

#घोषणा user_addr_max() \
	(uaccess_kernel() ? ~0UL : TASK_SIZE)

बाह्य दीर्घ म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src, दीर्घ count);
बाह्य __must_check दीर्घ strnlen_user(स्थिर अक्षर __user *str, दीर्घ n);

अचिन्हित दीर्घ __clear_user(व्योम __user *to, अचिन्हित दीर्घ n);

#घोषणा clear_user	__clear_user

#अन्यथा /* !CONFIG_MMU */
#समावेश <यंत्र-generic/uaccess.h>
#पूर्ण_अगर

#पूर्ण_अगर /* _M68K_UACCESS_H */
