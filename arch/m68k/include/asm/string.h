<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_STRING_H_
#घोषणा _M68K_STRING_H_

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>

#घोषणा __HAVE_ARCH_STRNLEN
अटल अंतरभूत माप_प्रकार strnlen(स्थिर अक्षर *s, माप_प्रकार count)
अणु
	स्थिर अक्षर *sc = s;

	यंत्र अस्थिर ("\n"
		"1:     subq.l  #1,%1\n"
		"       jcs     2f\n"
		"       tst.b   (%0)+\n"
		"       jne     1b\n"
		"       subq.l  #1,%0\n"
		"2:"
		: "+a" (sc), "+d" (count));
	वापस sc - s;
पूर्ण

#घोषणा __HAVE_ARCH_STRNCPY
अटल अंतरभूत अक्षर *म_नकलन(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार n)
अणु
	अक्षर *xdest = dest;

	यंत्र अस्थिर ("\n"
		"	jra	2f\n"
		"1:	move.b	(%1),(%0)+\n"
		"	jeq	2f\n"
		"	addq.l	#1,%1\n"
		"2:	subq.l	#1,%2\n"
		"	jcc	1b\n"
		: "+a" (dest), "+a" (src), "+d" (n)
		: : "memory");
	वापस xdest;
पूर्ण

#अगर_अघोषित CONFIG_COLDFIRE
#घोषणा __HAVE_ARCH_STRCMP
अटल अंतरभूत पूर्णांक म_भेद(स्थिर अक्षर *cs, स्थिर अक्षर *ct)
अणु
	अक्षर res;

	यंत्र ("\n"
		"1:	move.b	(%0)+,%2\n"	/* get *cs */
		"	cmp.b	(%1)+,%2\n"	/* compare a byte */
		"	jne	2f\n"		/* not equal, अवरोध out */
		"	tst.b	%2\n"		/* at end of cs? */
		"	jne	1b\n"		/* no, keep going */
		"	jra	3f\n"		/* strings are equal */
		"2:	sub.b	-(%1),%2\n"	/* *cs - *ct */
		"3:"
		: "+a" (cs), "+a" (ct), "=d" (res));
	वापस res;
पूर्ण
#पूर्ण_अगर /* CONFIG_COLDFIRE */

#घोषणा __HAVE_ARCH_MEMMOVE
बाह्य व्योम *स_हटाओ(व्योम *, स्थिर व्योम *, __kernel_माप_प्रकार);

#घोषणा स_भेद(d, s, n) __builtin_स_भेद(d, s, n)

#घोषणा __HAVE_ARCH_MEMSET
बाह्य व्योम *स_रखो(व्योम *, पूर्णांक, __kernel_माप_प्रकार);
#घोषणा स_रखो(d, c, n) __builtin_स_रखो(d, c, n)

#घोषणा __HAVE_ARCH_MEMCPY
बाह्य व्योम *स_नकल(व्योम *, स्थिर व्योम *, __kernel_माप_प्रकार);
#घोषणा स_नकल(d, s, n) __builtin_स_नकल(d, s, n)

#पूर्ण_अगर /* _M68K_STRING_H_ */
