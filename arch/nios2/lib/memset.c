<शैली गुरु>
/*
 * Copyright (C) 2011 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2004 Microtronix Datacom Ltd
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>

व्योम *स_रखो(व्योम *s, पूर्णांक c, माप_प्रकार count)
अणु
	पूर्णांक destptr, अक्षरcnt, dwordcnt, fill8reg, wrkrega;

	अगर (!count)
		वापस s;

	c &= 0xFF;

	अगर (count <= 8) अणु
		अक्षर *xs = (अक्षर *) s;

		जबतक (count--)
			*xs++ = c;
		वापस s;
	पूर्ण

	__यंत्र__ __अस्थिर__ (
		/* fill8 %3, %5 (c & 0xff) */
		"	slli	%4, %5, 8\n"
		"	or	%4, %4, %5\n"
		"	slli    %3, %4, 16\n"
		"	or	%3, %3, %4\n"
		/* Word-align %0 (s) अगर necessary */
		"	andi	%4, %0, 0x01\n"
		"	beq	%4, zero, 1f\n"
		"	addi	%1, %1, -1\n"
		"	stb	%3, 0(%0)\n"
		"	addi	%0, %0, 1\n"
		"1:	mov	%2, %1\n"
		/* Dword-align %0 (s) अगर necessary */
		"	andi	%4, %0, 0x02\n"
		"	beq	%4, zero, 2f\n"
		"	addi	%1, %1, -2\n"
		"	sth	%3, 0(%0)\n"
		"	addi	%0, %0, 2\n"
		"	mov	%2, %1\n"
		/* %1 and %2 are how many more bytes to set */
		"2:	srli	%2, %2, 2\n"
		/* %2 is how many dwords to set */
		"3:	stw	%3, 0(%0)\n"
		"	addi	%0, %0, 4\n"
		"	addi    %2, %2, -1\n"
		"	bne	%2, zero, 3b\n"
		/* store residual word and/or byte अगर necessary */
		"	andi	%4, %1, 0x02\n"
		"	beq	%4, zero, 4f\n"
		"	sth	%3, 0(%0)\n"
		"	addi	%0, %0, 2\n"
		/* store residual byte अगर necessary */
		"4:	andi	%4, %1, 0x01\n"
		"	beq	%4, zero, 5f\n"
		"	stb	%3, 0(%0)\n"
		"5:\n"
		: "=r" (destptr),	/* %0  Output */
		  "=r" (अक्षरcnt),	/* %1  Output */
		  "=r" (dwordcnt),	/* %2  Output */
		  "=r" (fill8reg),	/* %3  Output */
		  "=&r" (wrkrega)	/* %4  Output only */
		: "r" (c),		/* %5  Input */
		  "0" (s),		/* %0  Input/Output */
		  "1" (count)		/* %1  Input/Output */
		: "memory"		/* clobbered */
	);

	वापस s;
पूर्ण
