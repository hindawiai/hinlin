<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>

अचिन्हित दीर्घ __generic_copy_from_user(व्योम *to, स्थिर व्योम __user *from,
				       अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ पंचांगp, res;

	यंत्र अस्थिर ("\n"
		"	tst.l	%0\n"
		"	jeq	2f\n"
		"1:	"MOVES".l	(%1)+,%3\n"
		"	move.l	%3,(%2)+\n"
		"	subq.l	#1,%0\n"
		"	jne	1b\n"
		"2:	btst	#1,%5\n"
		"	jeq	4f\n"
		"3:	"MOVES".w	(%1)+,%3\n"
		"	move.w	%3,(%2)+\n"
		"4:	btst	#0,%5\n"
		"	jeq	6f\n"
		"5:	"MOVES".b	(%1)+,%3\n"
		"	move.b  %3,(%2)+\n"
		"6:\n"
		"	.section .fixup,\"ax\"\n"
		"	.even\n"
		"10:	lsl.l	#2,%0\n"
		"	btst	#1,%5\n"
		"	jeq	8f\n"
		"30:	addq.l	#2,%0\n"
		"8:	btst	#0,%5\n"
		"	jeq	6b\n"
		"50:	addq.l	#1,%0\n"
		"	jra	6b\n"
		"	.previous\n"
		"\n"
		"	.section __ex_table,\"a\"\n"
		"	.align	4\n"
		"	.long	1b,10b\n"
		"	.long	3b,30b\n"
		"	.long	5b,50b\n"
		"	.previous"
		: "=d" (res), "+a" (from), "+a" (to), "=&d" (पंचांगp)
		: "0" (n / 4), "d" (n & 3));

	वापस res;
पूर्ण
EXPORT_SYMBOL(__generic_copy_from_user);

अचिन्हित दीर्घ __generic_copy_to_user(व्योम __user *to, स्थिर व्योम *from,
				     अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ पंचांगp, res;

	यंत्र अस्थिर ("\n"
		"	tst.l	%0\n"
		"	jeq	4f\n"
		"1:	move.l	(%1)+,%3\n"
		"2:	"MOVES".l	%3,(%2)+\n"
		"3:	subq.l	#1,%0\n"
		"	jne	1b\n"
		"4:	btst	#1,%5\n"
		"	jeq	6f\n"
		"	move.w	(%1)+,%3\n"
		"5:	"MOVES".w	%3,(%2)+\n"
		"6:	btst	#0,%5\n"
		"	jeq	8f\n"
		"	move.b	(%1)+,%3\n"
		"7:	"MOVES".b  %3,(%2)+\n"
		"8:\n"
		"	.section .fixup,\"ax\"\n"
		"	.even\n"
		"20:	lsl.l	#2,%0\n"
		"50:	add.l	%5,%0\n"
		"	jra	8b\n"
		"	.previous\n"
		"\n"
		"	.section __ex_table,\"a\"\n"
		"	.align	4\n"
		"	.long	2b,20b\n"
		"	.long	3b,20b\n"
		"	.long	5b,50b\n"
		"	.long	6b,50b\n"
		"	.long	7b,50b\n"
		"	.long	8b,50b\n"
		"	.previous"
		: "=d" (res), "+a" (from), "+a" (to), "=&d" (पंचांगp)
		: "0" (n / 4), "d" (n & 3));

	वापस res;
पूर्ण
EXPORT_SYMBOL(__generic_copy_to_user);

/*
 * Zero Userspace
 */

अचिन्हित दीर्घ __clear_user(व्योम __user *to, अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ res;

	यंत्र अस्थिर ("\n"
		"	tst.l	%0\n"
		"	jeq	3f\n"
		"1:	"MOVES".l	%2,(%1)+\n"
		"2:	subq.l	#1,%0\n"
		"	jne	1b\n"
		"3:	btst	#1,%4\n"
		"	jeq	5f\n"
		"4:	"MOVES".w	%2,(%1)+\n"
		"5:	btst	#0,%4\n"
		"	jeq	7f\n"
		"6:	"MOVES".b	%2,(%1)\n"
		"7:\n"
		"	.section .fixup,\"ax\"\n"
		"	.even\n"
		"10:	lsl.l	#2,%0\n"
		"40:	add.l	%4,%0\n"
		"	jra	7b\n"
		"	.previous\n"
		"\n"
		"	.section __ex_table,\"a\"\n"
		"	.align	4\n"
		"	.long	1b,10b\n"
		"	.long	2b,10b\n"
		"	.long	4b,40b\n"
		"	.long	5b,40b\n"
		"	.long	6b,40b\n"
		"	.long	7b,40b\n"
		"	.previous"
		: "=d" (res), "+a" (to)
		: "d" (0), "0" (n / 4), "d" (n & 3));

    वापस res;
पूर्ण
EXPORT_SYMBOL(__clear_user);
