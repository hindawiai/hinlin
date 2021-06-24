<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		IP/TCP/UDP checksumming routines
 *
 * Authors:	Jorge Cwik, <jorge@laser.satlink.net>
 *		Arnt Gulbअक्रमsen, <agulbra@nvg.unit.no>
 *		Tom May, <ftom@netcom.com>
 *		Andreas Schwab, <schwab@issan.inक्रमmatik.uni-करोrपंचांगund.de>
 *		Lots of code moved from tcp.c and ip.c; see those files
 *		क्रम more names.
 *
 * 03/02/96	Jes Sorensen, Andreas Schwab, Roman Hodek:
 *		Fixed some nasty bugs, causing some horrible crashes.
 *		A: At some poपूर्णांकs, the sum (%0) was used as
 *		length-counter instead of the length counter
 *		(%1). Thanks to Roman Hodek क्रम poपूर्णांकing this out.
 *		B: GCC seems to mess up अगर one uses too many
 *		data-रेजिस्टरs to hold input values and one tries to
 *		specअगरy d0 and d1 as scratch रेजिस्टरs. Letting gcc
 *		choose these रेजिस्टरs itself solves the problem.
 *
 * 1998/8/31	Andreas Schwab:
 *		Zero out rest of buffer on exception in
 *		csum_partial_copy_from_user.
 */

#समावेश <linux/module.h>
#समावेश <net/checksum.h>

/*
 * computes a partial checksum, e.g. क्रम TCP/UDP fragments
 */

__wsum csum_partial(स्थिर व्योम *buff, पूर्णांक len, __wsum sum)
अणु
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2;
	  /*
	   * Experiments with ethernet and slip connections show that buff
	   * is aligned on either a 2-byte or 4-byte boundary.
	   */
	__यंत्र__("movel %2,%3\n\t"
		"btst #1,%3\n\t"	/* Check alignment */
		"jeq 2f\n\t"
		"subql #2,%1\n\t"	/* buff%4==2: treat first word */
		"jgt 1f\n\t"
		"addql #2,%1\n\t"	/* len was == 2, treat only rest */
		"jra 4f\n"
	     "1:\t"
		"addw %2@+,%0\n\t"	/* add first word to sum */
		"clrl %3\n\t"
		"addxl %3,%0\n"		/* add X bit */
	     "2:\t"
		/* unrolled loop क्रम the मुख्य part: करो 8 दीर्घs at once */
		"movel %1,%3\n\t"	/* save len in पंचांगp1 */
		"lsrl #5,%1\n\t"	/* len/32 */
		"jeq 2f\n\t"		/* not enough... */
		"subql #1,%1\n"
	     "1:\t"
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"dbra %1,1b\n\t"
		"clrl %4\n\t"
		"addxl %4,%0\n\t"	/* add X bit */
		"clrw %1\n\t"
		"subql #1,%1\n\t"
		"jcc 1b\n"
	     "2:\t"
		"movel %3,%1\n\t"	/* restore len from पंचांगp1 */
		"andw #0x1c,%3\n\t"	/* number of rest दीर्घs */
		"jeq 4f\n\t"
		"lsrw #2,%3\n\t"
		"subqw #1,%3\n"
	     "3:\t"
		/* loop क्रम rest दीर्घs */
		"movel %2@+,%4\n\t"
		"addxl %4,%0\n\t"
		"dbra %3,3b\n\t"
		"clrl %4\n\t"
		"addxl %4,%0\n"		/* add X bit */
	     "4:\t"
		/* now check क्रम rest bytes that करो not fit पूर्णांकo दीर्घs */
		"andw #3,%1\n\t"
		"jeq 7f\n\t"
		"clrl %4\n\t"		/* clear पंचांगp2 क्रम rest bytes */
		"subqw #2,%1\n\t"
		"jlt 5f\n\t"
		"movew %2@+,%4\n\t"	/* have rest >= 2: get word */
		"swap %4\n\t"		/* पूर्णांकo bits 16..31 */
		"tstw %1\n\t"		/* another byte? */
		"jeq 6f\n"
	     "5:\t"
		"moveb %2@,%4\n\t"	/* have odd rest: get byte */
		"lslw #8,%4\n\t"	/* पूर्णांकo bits 8..15; 16..31 untouched */
	     "6:\t"
		"addl %4,%0\n\t"	/* now add rest दीर्घ to sum */
		"clrl %4\n\t"
		"addxl %4,%0\n"		/* add X bit */
	     "7:\t"
		: "=d" (sum), "=d" (len), "=a" (buff),
		  "=&d" (पंचांगp1), "=&d" (पंचांगp2)
		: "0" (sum), "1" (len), "2" (buff)
	    );
	वापस(sum);
पूर्ण

EXPORT_SYMBOL(csum_partial);


/*
 * copy from user space जबतक checksumming, with exception handling.
 */

__wsum
csum_and_copy_from_user(स्थिर व्योम __user *src, व्योम *dst, पूर्णांक len)
अणु
	/*
	 * GCC करोesn't like more than 10 opeअक्रमs क्रम the यंत्र
	 * statements so we have to use पंचांगp2 क्रम the error
	 * code.
	 */
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2;
	__wsum sum = ~0U;

	__यंत्र__("movel %2,%4\n\t"
		"btst #1,%4\n\t"	/* Check alignment */
		"jeq 2f\n\t"
		"subql #2,%1\n\t"	/* buff%4==2: treat first word */
		"jgt 1f\n\t"
		"addql #2,%1\n\t"	/* len was == 2, treat only rest */
		"jra 4f\n"
	     "1:\n"
	     "10:\t"
		"movesw %2@+,%4\n\t"	/* add first word to sum */
		"addw %4,%0\n\t"
		"movew %4,%3@+\n\t"
		"clrl %4\n\t"
		"addxl %4,%0\n"		/* add X bit */
	     "2:\t"
		/* unrolled loop क्रम the मुख्य part: करो 8 दीर्घs at once */
		"movel %1,%4\n\t"	/* save len in पंचांगp1 */
		"lsrl #5,%1\n\t"	/* len/32 */
		"jeq 2f\n\t"		/* not enough... */
		"subql #1,%1\n"
	     "1:\n"
	     "11:\t"
		"movesl %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
	     "12:\t"
		"movesl %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
	     "13:\t"
		"movesl %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
	     "14:\t"
		"movesl %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
	     "15:\t"
		"movesl %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
	     "16:\t"
		"movesl %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
	     "17:\t"
		"movesl %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
	     "18:\t"
		"movesl %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
		"dbra %1,1b\n\t"
		"clrl %5\n\t"
		"addxl %5,%0\n\t"	/* add X bit */
		"clrw %1\n\t"
		"subql #1,%1\n\t"
		"jcc 1b\n"
	     "2:\t"
		"movel %4,%1\n\t"	/* restore len from पंचांगp1 */
		"andw #0x1c,%4\n\t"	/* number of rest दीर्घs */
		"jeq 4f\n\t"
		"lsrw #2,%4\n\t"
		"subqw #1,%4\n"
	     "3:\n"
		/* loop क्रम rest दीर्घs */
	     "19:\t"
		"movesl %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
		"dbra %4,3b\n\t"
		"clrl %5\n\t"
		"addxl %5,%0\n"		/* add X bit */
	     "4:\t"
		/* now check क्रम rest bytes that करो not fit पूर्णांकo दीर्घs */
		"andw #3,%1\n\t"
		"jeq 7f\n\t"
		"clrl %5\n\t"		/* clear पंचांगp2 क्रम rest bytes */
		"subqw #2,%1\n\t"
		"jlt 5f\n\t"
	     "20:\t"
		"movesw %2@+,%5\n\t"	/* have rest >= 2: get word */
		"movew %5,%3@+\n\t"
		"swap %5\n\t"		/* पूर्णांकo bits 16..31 */
		"tstw %1\n\t"		/* another byte? */
		"jeq 6f\n"
	     "5:\n"
	     "21:\t"
		"movesb %2@,%5\n\t"	/* have odd rest: get byte */
		"moveb %5,%3@+\n\t"
		"lslw #8,%5\n\t"	/* पूर्णांकo bits 8..15; 16..31 untouched */
	     "6:\t"
		"addl %5,%0\n\t"	/* now add rest दीर्घ to sum */
		"clrl %5\n\t"
		"addxl %5,%0\n\t"	/* add X bit */
	     "7:\t"
		".section .fixup,\"ax\"\n"
		".even\n"
		/* If any exception occurs, वापस 0 */
	     "90:\t"
		"clrl %0\n"
		"jra 7b\n"
		".previous\n"
		".section __ex_table,\"a\"\n"
		".long 10b,90b\n"
		".long 11b,90b\n"
		".long 12b,90b\n"
		".long 13b,90b\n"
		".long 14b,90b\n"
		".long 15b,90b\n"
		".long 16b,90b\n"
		".long 17b,90b\n"
		".long 18b,90b\n"
		".long 19b,90b\n"
		".long 20b,90b\n"
		".long 21b,90b\n"
		".previous"
		: "=d" (sum), "=d" (len), "=a" (src), "=a" (dst),
		  "=&d" (पंचांगp1), "=d" (पंचांगp2)
		: "0" (sum), "1" (len), "2" (src), "3" (dst)
	    );

	वापस sum;
पूर्ण

EXPORT_SYMBOL(csum_and_copy_from_user);


/*
 * copy from kernel space जबतक checksumming, otherwise like csum_partial
 */

__wsum
csum_partial_copy_nocheck(स्थिर व्योम *src, व्योम *dst, पूर्णांक len)
अणु
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2;
	__wsum sum = 0;
	__यंत्र__("movel %2,%4\n\t"
		"btst #1,%4\n\t"	/* Check alignment */
		"jeq 2f\n\t"
		"subql #2,%1\n\t"	/* buff%4==2: treat first word */
		"jgt 1f\n\t"
		"addql #2,%1\n\t"	/* len was == 2, treat only rest */
		"jra 4f\n"
	     "1:\t"
		"movew %2@+,%4\n\t"	/* add first word to sum */
		"addw %4,%0\n\t"
		"movew %4,%3@+\n\t"
		"clrl %4\n\t"
		"addxl %4,%0\n"		/* add X bit */
	     "2:\t"
		/* unrolled loop क्रम the मुख्य part: करो 8 दीर्घs at once */
		"movel %1,%4\n\t"	/* save len in पंचांगp1 */
		"lsrl #5,%1\n\t"	/* len/32 */
		"jeq 2f\n\t"		/* not enough... */
		"subql #1,%1\n"
	     "1:\t"
		"movel %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
		"movel %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
		"movel %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
		"movel %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
		"movel %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
		"movel %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
		"movel %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
		"movel %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
		"dbra %1,1b\n\t"
		"clrl %5\n\t"
		"addxl %5,%0\n\t"	/* add X bit */
		"clrw %1\n\t"
		"subql #1,%1\n\t"
		"jcc 1b\n"
	     "2:\t"
		"movel %4,%1\n\t"	/* restore len from पंचांगp1 */
		"andw #0x1c,%4\n\t"	/* number of rest दीर्घs */
		"jeq 4f\n\t"
		"lsrw #2,%4\n\t"
		"subqw #1,%4\n"
	     "3:\t"
		/* loop क्रम rest दीर्घs */
		"movel %2@+,%5\n\t"
		"addxl %5,%0\n\t"
		"movel %5,%3@+\n\t"
		"dbra %4,3b\n\t"
		"clrl %5\n\t"
		"addxl %5,%0\n"		/* add X bit */
	     "4:\t"
		/* now check क्रम rest bytes that करो not fit पूर्णांकo दीर्घs */
		"andw #3,%1\n\t"
		"jeq 7f\n\t"
		"clrl %5\n\t"		/* clear पंचांगp2 क्रम rest bytes */
		"subqw #2,%1\n\t"
		"jlt 5f\n\t"
		"movew %2@+,%5\n\t"	/* have rest >= 2: get word */
		"movew %5,%3@+\n\t"
		"swap %5\n\t"		/* पूर्णांकo bits 16..31 */
		"tstw %1\n\t"		/* another byte? */
		"jeq 6f\n"
	     "5:\t"
		"moveb %2@,%5\n\t"	/* have odd rest: get byte */
		"moveb %5,%3@+\n\t"
		"lslw #8,%5\n"		/* पूर्णांकo bits 8..15; 16..31 untouched */
	     "6:\t"
		"addl %5,%0\n\t"	/* now add rest दीर्घ to sum */
		"clrl %5\n\t"
		"addxl %5,%0\n"		/* add X bit */
	     "7:\t"
		: "=d" (sum), "=d" (len), "=a" (src), "=a" (dst),
		  "=&d" (पंचांगp1), "=&d" (पंचांगp2)
		: "0" (sum), "1" (len), "2" (src), "3" (dst)
	    );
    वापस(sum);
पूर्ण
EXPORT_SYMBOL(csum_partial_copy_nocheck);
