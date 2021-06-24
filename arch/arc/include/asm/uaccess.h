<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * vineetg: June 2010
 *    -__clear_user( ) called multiple बार during elf load was byte loop
 *    converted to करो as much word clear as possible.
 *
 * vineetg: Dec 2009
 *    -Hand crafted स्थिरant propagation क्रम "constant" copy sizes
 *    -stock kernel shrunk by 33K at -O3
 *
 * vineetg: Sept 2009
 *    -Added option to (UN)अंतरभूत copy_(to|from)_user to reduce code sz
 *    -kernel shrunk by 200K even at -O3 (gcc 4.2.1)
 *    -Enabled when करोing -Os
 *
 * Amit Bhor, Sameer Dhavale: Codito Technologies 2004
 */

#अगर_अघोषित _ASM_ARC_UACCESS_H
#घोषणा _ASM_ARC_UACCESS_H

#समावेश <linux/माला.स>	/* क्रम generic string functions */


#घोषणा __kernel_ok		(uaccess_kernel())

/*
 * Algorithmically, क्रम __user_ok() we want करो:
 * 	(start < TASK_SIZE) && (start+len < TASK_SIZE)
 * where TASK_SIZE could either be retrieved from thपढ़ो_info->addr_limit or
 * emitted directly in code.
 *
 * This can however be rewritten as follows:
 *	(len <= TASK_SIZE) && (start+len < TASK_SIZE)
 *
 * Because it essentially checks अगर buffer end is within limit and @len is
 * non-ngeative, which implies that buffer start will be within limit too.
 *
 * The reason क्रम rewriting being, क्रम majority of हालs, @len is generally
 * compile समय स्थिरant, causing first sub-expression to be compile समय
 * subsumed.
 *
 * The second part would generate weird large LIMMs e.g. (0x6000_0000 - 0x10),
 * so we check क्रम TASK_SIZE using get_fs() since the addr_limit load from mem
 * would alपढ़ोy have been करोne at this call site क्रम __kernel_ok()
 *
 */
#घोषणा __user_ok(addr, sz)	(((sz) <= TASK_SIZE) && \
				 ((addr) <= (get_fs() - (sz))))
#घोषणा __access_ok(addr, sz)	(unlikely(__kernel_ok) || \
				 likely(__user_ok((addr), (sz))))

/*********** Single byte/hword/word copies ******************/

#घोषणा __get_user_fn(sz, u, k)					\
(अणु								\
	दीर्घ __ret = 0;	/* success by शेष */	\
	चयन (sz) अणु						\
	हाल 1: __arc_get_user_one(*(k), u, "ldb", __ret); अवरोध;	\
	हाल 2: __arc_get_user_one(*(k), u, "ldw", __ret); अवरोध;	\
	हाल 4: __arc_get_user_one(*(k), u, "ld", __ret);  अवरोध;	\
	हाल 8: __arc_get_user_one_64(*(k), u, __ret);     अवरोध;	\
	पूर्ण							\
	__ret;							\
पूर्ण)

/*
 * Returns 0 on success, -EFAULT अगर not.
 * @ret alपढ़ोy contains 0 - given that errors will be less likely
 * (hence +r यंत्र स्थिरraपूर्णांक below).
 * In हाल of error, fixup code will make it -EFAULT
 */
#घोषणा __arc_get_user_one(dst, src, op, ret)	\
	__यंत्र__ __अस्थिर__(                   \
	"1:	"op"    %1,[%2]\n"		\
	"2:	;nop\n"				\
	"	.section .fixup, \"ax\"\n"	\
	"	.align 4\n"			\
	"3:	# return -EFAULT\n"		\
	"	mov %0, %3\n"			\
	"	# zero out dst ptr\n"		\
	"	mov %1,  0\n"			\
	"	j   2b\n"			\
	"	.previous\n"			\
	"	.section __ex_table, \"a\"\n"	\
	"	.align 4\n"			\
	"	.word 1b,3b\n"			\
	"	.previous\n"			\
						\
	: "+r" (ret), "=r" (dst)		\
	: "r" (src), "ir" (-EFAULT))

#घोषणा __arc_get_user_one_64(dst, src, ret)	\
	__यंत्र__ __अस्थिर__(                   \
	"1:	ld   %1,[%2]\n"			\
	"4:	ld  %R1,[%2, 4]\n"		\
	"2:	;nop\n"				\
	"	.section .fixup, \"ax\"\n"	\
	"	.align 4\n"			\
	"3:	# return -EFAULT\n"		\
	"	mov %0, %3\n"			\
	"	# zero out dst ptr\n"		\
	"	mov %1,  0\n"			\
	"	mov %R1, 0\n"			\
	"	j   2b\n"			\
	"	.previous\n"			\
	"	.section __ex_table, \"a\"\n"	\
	"	.align 4\n"			\
	"	.word 1b,3b\n"			\
	"	.word 4b,3b\n"			\
	"	.previous\n"			\
						\
	: "+r" (ret), "=r" (dst)		\
	: "r" (src), "ir" (-EFAULT))

#घोषणा __put_user_fn(sz, u, k)					\
(अणु								\
	दीर्घ __ret = 0;	/* success by शेष */	\
	चयन (sz) अणु						\
	हाल 1: __arc_put_user_one(*(k), u, "stb", __ret); अवरोध;	\
	हाल 2: __arc_put_user_one(*(k), u, "stw", __ret); अवरोध;	\
	हाल 4: __arc_put_user_one(*(k), u, "st", __ret);  अवरोध;	\
	हाल 8: __arc_put_user_one_64(*(k), u, __ret);     अवरोध;	\
	पूर्ण							\
	__ret;							\
पूर्ण)

#घोषणा __arc_put_user_one(src, dst, op, ret)	\
	__यंत्र__ __अस्थिर__(                   \
	"1:	"op"    %1,[%2]\n"		\
	"2:	;nop\n"				\
	"	.section .fixup, \"ax\"\n"	\
	"	.align 4\n"			\
	"3:	mov %0, %3\n"			\
	"	j   2b\n"			\
	"	.previous\n"			\
	"	.section __ex_table, \"a\"\n"	\
	"	.align 4\n"			\
	"	.word 1b,3b\n"			\
	"	.previous\n"			\
						\
	: "+r" (ret)				\
	: "r" (src), "r" (dst), "ir" (-EFAULT))

#घोषणा __arc_put_user_one_64(src, dst, ret)	\
	__यंत्र__ __अस्थिर__(                   \
	"1:	st   %1,[%2]\n"			\
	"4:	st  %R1,[%2, 4]\n"		\
	"2:	;nop\n"				\
	"	.section .fixup, \"ax\"\n"	\
	"	.align 4\n"			\
	"3:	mov %0, %3\n"			\
	"	j   2b\n"			\
	"	.previous\n"			\
	"	.section __ex_table, \"a\"\n"	\
	"	.align 4\n"			\
	"	.word 1b,3b\n"			\
	"	.word 4b,3b\n"			\
	"	.previous\n"			\
						\
	: "+r" (ret)				\
	: "r" (src), "r" (dst), "ir" (-EFAULT))


अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	दीर्घ res = 0;
	अक्षर val;
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2, पंचांगp3, पंचांगp4;
	अचिन्हित दीर्घ orig_n = n;

	अगर (n == 0)
		वापस 0;

	/* unaligned */
	अगर (((अचिन्हित दीर्घ)to & 0x3) || ((अचिन्हित दीर्घ)from & 0x3)) अणु

		अचिन्हित अक्षर पंचांगp;

		__यंत्र__ __अस्थिर__ (
		"	mov.f   lp_count, %0		\n"
		"	lpnz 2f				\n"
		"1:	ldb.ab  %1, [%3, 1]		\n"
		"	stb.ab  %1, [%2, 1]		\n"
		"	sub     %0,%0,1			\n"
		"2:	;nop				\n"
		"	.section .fixup, \"ax\"		\n"
		"	.align 4			\n"
		"3:	j   2b				\n"
		"	.previous			\n"
		"	.section __ex_table, \"a\"	\n"
		"	.align 4			\n"
		"	.word   1b, 3b			\n"
		"	.previous			\n"

		: "+r" (n),
		/*
		 * Note as an '&' earlyclobber opeअक्रम to make sure the
		 * temporary रेजिस्टर inside the loop is not the same as
		 *  FROM or TO.
		*/
		  "=&r" (पंचांगp), "+r" (to), "+r" (from)
		:
		: "lp_count", "memory");

		वापस n;
	पूर्ण

	/*
	 * Hand-crafted स्थिरant propagation to reduce code sz of the
	 * laddered copy 16x,8,4,2,1
	 */
	अगर (__builtin_स्थिरant_p(orig_n)) अणु
		res = orig_n;

		अगर (orig_n / 16) अणु
			orig_n = orig_n % 16;

			__यंत्र__ __अस्थिर__(
			"	lsr   lp_count, %7,4		\n"
			"	lp    3f			\n"
			"1:	ld.ab   %3, [%2, 4]		\n"
			"11:	ld.ab   %4, [%2, 4]		\n"
			"12:	ld.ab   %5, [%2, 4]		\n"
			"13:	ld.ab   %6, [%2, 4]		\n"
			"	st.ab   %3, [%1, 4]		\n"
			"	st.ab   %4, [%1, 4]		\n"
			"	st.ab   %5, [%1, 4]		\n"
			"	st.ab   %6, [%1, 4]		\n"
			"	sub     %0,%0,16		\n"
			"3:	;nop				\n"
			"	.section .fixup, \"ax\"		\n"
			"	.align 4			\n"
			"4:	j   3b				\n"
			"	.previous			\n"
			"	.section __ex_table, \"a\"	\n"
			"	.align 4			\n"
			"	.word   1b, 4b			\n"
			"	.word   11b,4b			\n"
			"	.word   12b,4b			\n"
			"	.word   13b,4b			\n"
			"	.previous			\n"
			: "+r" (res), "+r"(to), "+r"(from),
			  "=r"(पंचांगp1), "=r"(पंचांगp2), "=r"(पंचांगp3), "=r"(पंचांगp4)
			: "ir"(n)
			: "lp_count", "memory");
		पूर्ण
		अगर (orig_n / 8) अणु
			orig_n = orig_n % 8;

			__यंत्र__ __अस्थिर__(
			"14:	ld.ab   %3, [%2,4]		\n"
			"15:	ld.ab   %4, [%2,4]		\n"
			"	st.ab   %3, [%1,4]		\n"
			"	st.ab   %4, [%1,4]		\n"
			"	sub     %0,%0,8			\n"
			"31:	;nop				\n"
			"	.section .fixup, \"ax\"		\n"
			"	.align 4			\n"
			"4:	j   31b				\n"
			"	.previous			\n"
			"	.section __ex_table, \"a\"	\n"
			"	.align 4			\n"
			"	.word   14b,4b			\n"
			"	.word   15b,4b			\n"
			"	.previous			\n"
			: "+r" (res), "+r"(to), "+r"(from),
			  "=r"(पंचांगp1), "=r"(पंचांगp2)
			:
			: "memory");
		पूर्ण
		अगर (orig_n / 4) अणु
			orig_n = orig_n % 4;

			__यंत्र__ __अस्थिर__(
			"16:	ld.ab   %3, [%2,4]		\n"
			"	st.ab   %3, [%1,4]		\n"
			"	sub     %0,%0,4			\n"
			"32:	;nop				\n"
			"	.section .fixup, \"ax\"		\n"
			"	.align 4			\n"
			"4:	j   32b				\n"
			"	.previous			\n"
			"	.section __ex_table, \"a\"	\n"
			"	.align 4			\n"
			"	.word   16b,4b			\n"
			"	.previous			\n"
			: "+r" (res), "+r"(to), "+r"(from), "=r"(पंचांगp1)
			:
			: "memory");
		पूर्ण
		अगर (orig_n / 2) अणु
			orig_n = orig_n % 2;

			__यंत्र__ __अस्थिर__(
			"17:	ldw.ab   %3, [%2,2]		\n"
			"	stw.ab   %3, [%1,2]		\n"
			"	sub      %0,%0,2		\n"
			"33:	;nop				\n"
			"	.section .fixup, \"ax\"		\n"
			"	.align 4			\n"
			"4:	j   33b				\n"
			"	.previous			\n"
			"	.section __ex_table, \"a\"	\n"
			"	.align 4			\n"
			"	.word   17b,4b			\n"
			"	.previous			\n"
			: "+r" (res), "+r"(to), "+r"(from), "=r"(पंचांगp1)
			:
			: "memory");
		पूर्ण
		अगर (orig_n & 1) अणु
			__यंत्र__ __अस्थिर__(
			"18:	ldb.ab   %3, [%2,2]		\n"
			"	stb.ab   %3, [%1,2]		\n"
			"	sub      %0,%0,1		\n"
			"34:	; nop				\n"
			"	.section .fixup, \"ax\"		\n"
			"	.align 4			\n"
			"4:	j   34b				\n"
			"	.previous			\n"
			"	.section __ex_table, \"a\"	\n"
			"	.align 4			\n"
			"	.word   18b,4b			\n"
			"	.previous			\n"
			: "+r" (res), "+r"(to), "+r"(from), "=r"(पंचांगp1)
			:
			: "memory");
		पूर्ण
	पूर्ण अन्यथा अणु  /* n is NOT स्थिरant, so laddered copy of 16x,8,4,2,1  */

		__यंत्र__ __अस्थिर__(
		"	mov %0,%3			\n"
		"	lsr.f   lp_count, %3,4		\n"  /* 16x bytes */
		"	lpnz    3f			\n"
		"1:	ld.ab   %5, [%2, 4]		\n"
		"11:	ld.ab   %6, [%2, 4]		\n"
		"12:	ld.ab   %7, [%2, 4]		\n"
		"13:	ld.ab   %8, [%2, 4]		\n"
		"	st.ab   %5, [%1, 4]		\n"
		"	st.ab   %6, [%1, 4]		\n"
		"	st.ab   %7, [%1, 4]		\n"
		"	st.ab   %8, [%1, 4]		\n"
		"	sub     %0,%0,16		\n"
		"3:	and.f   %3,%3,0xf		\n"  /* stragglers */
		"	bz      34f			\n"
		"	bbit0   %3,3,31f		\n"  /* 8 bytes left */
		"14:	ld.ab   %5, [%2,4]		\n"
		"15:	ld.ab   %6, [%2,4]		\n"
		"	st.ab   %5, [%1,4]		\n"
		"	st.ab   %6, [%1,4]		\n"
		"	sub.f   %0,%0,8			\n"
		"31:	bbit0   %3,2,32f		\n"  /* 4 bytes left */
		"16:	ld.ab   %5, [%2,4]		\n"
		"	st.ab   %5, [%1,4]		\n"
		"	sub.f   %0,%0,4			\n"
		"32:	bbit0   %3,1,33f		\n"  /* 2 bytes left */
		"17:	ldw.ab  %5, [%2,2]		\n"
		"	stw.ab  %5, [%1,2]		\n"
		"	sub.f   %0,%0,2			\n"
		"33:	bbit0   %3,0,34f		\n"
		"18:	ldb.ab  %5, [%2,1]		\n"  /* 1 byte left */
		"	stb.ab  %5, [%1,1]		\n"
		"	sub.f   %0,%0,1			\n"
		"34:	;nop				\n"
		"	.section .fixup, \"ax\"		\n"
		"	.align 4			\n"
		"4:	j   34b				\n"
		"	.previous			\n"
		"	.section __ex_table, \"a\"	\n"
		"	.align 4			\n"
		"	.word   1b, 4b			\n"
		"	.word   11b,4b			\n"
		"	.word   12b,4b			\n"
		"	.word   13b,4b			\n"
		"	.word   14b,4b			\n"
		"	.word   15b,4b			\n"
		"	.word   16b,4b			\n"
		"	.word   17b,4b			\n"
		"	.word   18b,4b			\n"
		"	.previous			\n"
		: "=r" (res), "+r"(to), "+r"(from), "+r"(n), "=r"(val),
		  "=r"(पंचांगp1), "=r"(पंचांगp2), "=r"(पंचांगp3), "=r"(पंचांगp4)
		:
		: "lp_count", "memory");
	पूर्ण

	वापस res;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	दीर्घ res = 0;
	अक्षर val;
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2, पंचांगp3, पंचांगp4;
	अचिन्हित दीर्घ orig_n = n;

	अगर (n == 0)
		वापस 0;

	/* unaligned */
	अगर (((अचिन्हित दीर्घ)to & 0x3) || ((अचिन्हित दीर्घ)from & 0x3)) अणु

		अचिन्हित अक्षर पंचांगp;

		__यंत्र__ __अस्थिर__(
		"	mov.f   lp_count, %0		\n"
		"	lpnz 3f				\n"
		"	ldb.ab  %1, [%3, 1]		\n"
		"1:	stb.ab  %1, [%2, 1]		\n"
		"	sub     %0, %0, 1		\n"
		"3:	;nop				\n"
		"	.section .fixup, \"ax\"		\n"
		"	.align 4			\n"
		"4:	j   3b				\n"
		"	.previous			\n"
		"	.section __ex_table, \"a\"	\n"
		"	.align 4			\n"
		"	.word   1b, 4b			\n"
		"	.previous			\n"

		: "+r" (n),
		/* Note as an '&' earlyclobber opeअक्रम to make sure the
		 * temporary रेजिस्टर inside the loop is not the same as
		 * FROM or TO.
		 */
		  "=&r" (पंचांगp), "+r" (to), "+r" (from)
		:
		: "lp_count", "memory");

		वापस n;
	पूर्ण

	अगर (__builtin_स्थिरant_p(orig_n)) अणु
		res = orig_n;

		अगर (orig_n / 16) अणु
			orig_n = orig_n % 16;

			__यंत्र__ __अस्थिर__(
			"	lsr lp_count, %7,4		\n"
			"	lp  3f				\n"
			"	ld.ab %3, [%2, 4]		\n"
			"	ld.ab %4, [%2, 4]		\n"
			"	ld.ab %5, [%2, 4]		\n"
			"	ld.ab %6, [%2, 4]		\n"
			"1:	st.ab %3, [%1, 4]		\n"
			"11:	st.ab %4, [%1, 4]		\n"
			"12:	st.ab %5, [%1, 4]		\n"
			"13:	st.ab %6, [%1, 4]		\n"
			"	sub   %0, %0, 16		\n"
			"3:;nop					\n"
			"	.section .fixup, \"ax\"		\n"
			"	.align 4			\n"
			"4:	j   3b				\n"
			"	.previous			\n"
			"	.section __ex_table, \"a\"	\n"
			"	.align 4			\n"
			"	.word   1b, 4b			\n"
			"	.word   11b,4b			\n"
			"	.word   12b,4b			\n"
			"	.word   13b,4b			\n"
			"	.previous			\n"
			: "+r" (res), "+r"(to), "+r"(from),
			  "=r"(पंचांगp1), "=r"(पंचांगp2), "=r"(पंचांगp3), "=r"(पंचांगp4)
			: "ir"(n)
			: "lp_count", "memory");
		पूर्ण
		अगर (orig_n / 8) अणु
			orig_n = orig_n % 8;

			__यंत्र__ __अस्थिर__(
			"	ld.ab   %3, [%2,4]		\n"
			"	ld.ab   %4, [%2,4]		\n"
			"14:	st.ab   %3, [%1,4]		\n"
			"15:	st.ab   %4, [%1,4]		\n"
			"	sub     %0, %0, 8		\n"
			"31:;nop				\n"
			"	.section .fixup, \"ax\"		\n"
			"	.align 4			\n"
			"4:	j   31b				\n"
			"	.previous			\n"
			"	.section __ex_table, \"a\"	\n"
			"	.align 4			\n"
			"	.word   14b,4b			\n"
			"	.word   15b,4b			\n"
			"	.previous			\n"
			: "+r" (res), "+r"(to), "+r"(from),
			  "=r"(पंचांगp1), "=r"(पंचांगp2)
			:
			: "memory");
		पूर्ण
		अगर (orig_n / 4) अणु
			orig_n = orig_n % 4;

			__यंत्र__ __अस्थिर__(
			"	ld.ab   %3, [%2,4]		\n"
			"16:	st.ab   %3, [%1,4]		\n"
			"	sub     %0, %0, 4		\n"
			"32:;nop				\n"
			"	.section .fixup, \"ax\"		\n"
			"	.align 4			\n"
			"4:	j   32b				\n"
			"	.previous			\n"
			"	.section __ex_table, \"a\"	\n"
			"	.align 4			\n"
			"	.word   16b,4b			\n"
			"	.previous			\n"
			: "+r" (res), "+r"(to), "+r"(from), "=r"(पंचांगp1)
			:
			: "memory");
		पूर्ण
		अगर (orig_n / 2) अणु
			orig_n = orig_n % 2;

			__यंत्र__ __अस्थिर__(
			"	ldw.ab    %3, [%2,2]		\n"
			"17:	stw.ab    %3, [%1,2]		\n"
			"	sub       %0, %0, 2		\n"
			"33:;nop				\n"
			"	.section .fixup, \"ax\"		\n"
			"	.align 4			\n"
			"4:	j   33b				\n"
			"	.previous			\n"
			"	.section __ex_table, \"a\"	\n"
			"	.align 4			\n"
			"	.word   17b,4b			\n"
			"	.previous			\n"
			: "+r" (res), "+r"(to), "+r"(from), "=r"(पंचांगp1)
			:
			: "memory");
		पूर्ण
		अगर (orig_n & 1) अणु
			__यंत्र__ __अस्थिर__(
			"	ldb.ab  %3, [%2,1]		\n"
			"18:	stb.ab  %3, [%1,1]		\n"
			"	sub     %0, %0, 1		\n"
			"34:	;nop				\n"
			"	.section .fixup, \"ax\"		\n"
			"	.align 4			\n"
			"4:	j   34b				\n"
			"	.previous			\n"
			"	.section __ex_table, \"a\"	\n"
			"	.align 4			\n"
			"	.word   18b,4b			\n"
			"	.previous			\n"
			: "+r" (res), "+r"(to), "+r"(from), "=r"(पंचांगp1)
			:
			: "memory");
		पूर्ण
	पूर्ण अन्यथा अणु  /* n is NOT स्थिरant, so laddered copy of 16x,8,4,2,1  */

		__यंत्र__ __अस्थिर__(
		"	mov   %0,%3			\n"
		"	lsr.f lp_count, %3,4		\n"  /* 16x bytes */
		"	lpnz  3f			\n"
		"	ld.ab %5, [%2, 4]		\n"
		"	ld.ab %6, [%2, 4]		\n"
		"	ld.ab %7, [%2, 4]		\n"
		"	ld.ab %8, [%2, 4]		\n"
		"1:	st.ab %5, [%1, 4]		\n"
		"11:	st.ab %6, [%1, 4]		\n"
		"12:	st.ab %7, [%1, 4]		\n"
		"13:	st.ab %8, [%1, 4]		\n"
		"	sub   %0, %0, 16		\n"
		"3:	and.f %3,%3,0xf			\n" /* stragglers */
		"	bz 34f				\n"
		"	bbit0   %3,3,31f		\n" /* 8 bytes left */
		"	ld.ab   %5, [%2,4]		\n"
		"	ld.ab   %6, [%2,4]		\n"
		"14:	st.ab   %5, [%1,4]		\n"
		"15:	st.ab   %6, [%1,4]		\n"
		"	sub.f   %0, %0, 8		\n"
		"31:	bbit0   %3,2,32f		\n"  /* 4 bytes left */
		"	ld.ab   %5, [%2,4]		\n"
		"16:	st.ab   %5, [%1,4]		\n"
		"	sub.f   %0, %0, 4		\n"
		"32:	bbit0 %3,1,33f			\n"  /* 2 bytes left */
		"	ldw.ab    %5, [%2,2]		\n"
		"17:	stw.ab    %5, [%1,2]		\n"
		"	sub.f %0, %0, 2			\n"
		"33:	bbit0 %3,0,34f			\n"
		"	ldb.ab    %5, [%2,1]		\n"  /* 1 byte left */
		"18:	stb.ab  %5, [%1,1]		\n"
		"	sub.f %0, %0, 1			\n"
		"34:	;nop				\n"
		"	.section .fixup, \"ax\"		\n"
		"	.align 4			\n"
		"4:	j   34b				\n"
		"	.previous			\n"
		"	.section __ex_table, \"a\"	\n"
		"	.align 4			\n"
		"	.word   1b, 4b			\n"
		"	.word   11b,4b			\n"
		"	.word   12b,4b			\n"
		"	.word   13b,4b			\n"
		"	.word   14b,4b			\n"
		"	.word   15b,4b			\n"
		"	.word   16b,4b			\n"
		"	.word   17b,4b			\n"
		"	.word   18b,4b			\n"
		"	.previous			\n"
		: "=r" (res), "+r"(to), "+r"(from), "+r"(n), "=r"(val),
		  "=r"(पंचांगp1), "=r"(पंचांगp2), "=r"(पंचांगp3), "=r"(पंचांगp4)
		:
		: "lp_count", "memory");
	पूर्ण

	वापस res;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __arc_clear_user(व्योम __user *to, अचिन्हित दीर्घ n)
अणु
	दीर्घ res = n;
	अचिन्हित अक्षर *d_अक्षर = to;

	__यंत्र__ __अस्थिर__(
	"	bbit0   %0, 0, 1f		\n"
	"75:	stb.ab  %2, [%0,1]		\n"
	"	sub %1, %1, 1			\n"
	"1:	bbit0   %0, 1, 2f		\n"
	"76:	stw.ab  %2, [%0,2]		\n"
	"	sub %1, %1, 2			\n"
	"2:	asr.f   lp_count, %1, 2		\n"
	"	lpnz    3f			\n"
	"77:	st.ab   %2, [%0,4]		\n"
	"	sub %1, %1, 4			\n"
	"3:	bbit0   %1, 1, 4f		\n"
	"78:	stw.ab  %2, [%0,2]		\n"
	"	sub %1, %1, 2			\n"
	"4:	bbit0   %1, 0, 5f		\n"
	"79:	stb.ab  %2, [%0,1]		\n"
	"	sub %1, %1, 1			\n"
	"5:					\n"
	"	.section .fixup, \"ax\"		\n"
	"	.align 4			\n"
	"3:	j   5b				\n"
	"	.previous			\n"
	"	.section __ex_table, \"a\"	\n"
	"	.align 4			\n"
	"	.word   75b, 3b			\n"
	"	.word   76b, 3b			\n"
	"	.word   77b, 3b			\n"
	"	.word   78b, 3b			\n"
	"	.word   79b, 3b			\n"
	"	.previous			\n"
	: "+r"(d_अक्षर), "+r"(res)
	: "i"(0)
	: "lp_count", "memory");

	वापस res;
पूर्ण

अटल अंतरभूत दीर्घ
__arc_म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src, दीर्घ count)
अणु
	दीर्घ res = 0;
	अक्षर val;

	अगर (count == 0)
		वापस 0;

	__यंत्र__ __अस्थिर__(
	"	mov	lp_count, %5		\n"
	"	lp	3f			\n"
	"1:	ldb.ab  %3, [%2, 1]		\n"
	"	breq.d	%3, 0, 3f               \n"
	"	stb.ab  %3, [%1, 1]		\n"
	"	add	%0, %0, 1	# Num of NON NULL bytes copied	\n"
	"3:								\n"
	"	.section .fixup, \"ax\"		\n"
	"	.align 4			\n"
	"4:	mov %0, %4		# sets @res as -EFAULT	\n"
	"	j   3b				\n"
	"	.previous			\n"
	"	.section __ex_table, \"a\"	\n"
	"	.align 4			\n"
	"	.word   1b, 4b			\n"
	"	.previous			\n"
	: "+r"(res), "+r"(dst), "+r"(src), "=r"(val)
	: "g"(-EFAULT), "r"(count)
	: "lp_count", "memory");

	वापस res;
पूर्ण

अटल अंतरभूत दीर्घ __arc_strnlen_user(स्थिर अक्षर __user *s, दीर्घ n)
अणु
	दीर्घ res, पंचांगp1, cnt;
	अक्षर val;

	__यंत्र__ __अस्थिर__(
	"	mov %2, %1			\n"
	"1:	ldb.ab  %3, [%0, 1]		\n"
	"	breq.d  %3, 0, 2f		\n"
	"	sub.f   %2, %2, 1		\n"
	"	bnz 1b				\n"
	"	sub %2, %2, 1			\n"
	"2:	sub %0, %1, %2			\n"
	"3:	;nop				\n"
	"	.section .fixup, \"ax\"		\n"
	"	.align 4			\n"
	"4:	mov %0, 0			\n"
	"	j   3b				\n"
	"	.previous			\n"
	"	.section __ex_table, \"a\"	\n"
	"	.align 4			\n"
	"	.word 1b, 4b			\n"
	"	.previous			\n"
	: "=r"(res), "=r"(पंचांगp1), "=r"(cnt), "=r"(val)
	: "0"(s), "1"(n)
	: "memory");

	वापस res;
पूर्ण

#अगर_अघोषित CONFIG_CC_OPTIMIZE_FOR_SIZE

#घोषणा INLINE_COPY_TO_USER
#घोषणा INLINE_COPY_FROM_USER

#घोषणा __clear_user(d, n)		__arc_clear_user(d, n)
#घोषणा __म_नकलन_from_user(d, s, n)	__arc_म_नकलन_from_user(d, s, n)
#घोषणा __strnlen_user(s, n)		__arc_strnlen_user(s, n)
#अन्यथा
बाह्य अचिन्हित दीर्घ arc_clear_user_noअंतरभूत(व्योम __user *to,
		अचिन्हित दीर्घ n);
बाह्य दीर्घ arc_म_नकलन_from_user_noअंतरभूत (अक्षर *dst, स्थिर अक्षर __user *src,
		दीर्घ count);
बाह्य दीर्घ arc_strnlen_user_noअंतरभूत(स्थिर अक्षर __user *src, दीर्घ n);

#घोषणा __clear_user(d, n)		arc_clear_user_noअंतरभूत(d, n)
#घोषणा __म_नकलन_from_user(d, s, n)	arc_म_नकलन_from_user_noअंतरभूत(d, s, n)
#घोषणा __strnlen_user(s, n)		arc_strnlen_user_noअंतरभूत(s, n)

#पूर्ण_अगर

#समावेश <यंत्र/segment.h>
#समावेश <यंत्र-generic/uaccess.h>

#पूर्ण_अगर
