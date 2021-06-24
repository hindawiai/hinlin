<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_STRING_H
#घोषणा __ASM_SH_STRING_H

/*
 * Copyright (C) 1999 Niibe Yutaka
 * But consider these trivial functions to be खुला करोमुख्य.
 */

#घोषणा __HAVE_ARCH_STRCPY
अटल अंतरभूत अक्षर *म_नकल(अक्षर *__dest, स्थिर अक्षर *__src)
अणु
	रेजिस्टर अक्षर *__xdest = __dest;
	अचिन्हित दीर्घ __dummy;

	__यंत्र__ __अस्थिर__("1:\n\t"
			     "mov.b	@%1+, %2\n\t"
			     "mov.b	%2, @%0\n\t"
			     "cmp/eq	#0, %2\n\t"
			     "bf/s	1b\n\t"
			     " add	#1, %0\n\t"
			     : "=r" (__dest), "=r" (__src), "=&z" (__dummy)
			     : "0" (__dest), "1" (__src)
			     : "memory", "t");

	वापस __xdest;
पूर्ण

#घोषणा __HAVE_ARCH_STRCMP
अटल अंतरभूत पूर्णांक म_भेद(स्थिर अक्षर *__cs, स्थिर अक्षर *__ct)
अणु
	रेजिस्टर पूर्णांक __res;
	अचिन्हित दीर्घ __dummy;

	__यंत्र__ __अस्थिर__(
		"mov.b	@%1+, %3\n"
		"1:\n\t"
		"mov.b	@%0+, %2\n\t"
		"cmp/eq #0, %3\n\t"
		"bt	2f\n\t"
		"cmp/eq %2, %3\n\t"
		"bt/s	1b\n\t"
		" mov.b	@%1+, %3\n\t"
		"add	#-2, %1\n\t"
		"mov.b	@%1, %3\n\t"
		"sub	%3, %2\n"
		"2:"
		: "=r" (__cs), "=r" (__ct), "=&r" (__res), "=&z" (__dummy)
		: "0" (__cs), "1" (__ct)
		: "t");

	वापस __res;
पूर्ण

#घोषणा __HAVE_ARCH_STRNCMP
अटल अंतरभूत पूर्णांक म_भेदन(स्थिर अक्षर *__cs, स्थिर अक्षर *__ct, माप_प्रकार __n)
अणु
	रेजिस्टर पूर्णांक __res;
	अचिन्हित दीर्घ __dummy;

	अगर (__n == 0)
		वापस 0;

	__यंत्र__ __अस्थिर__(
		"mov.b	@%1+, %3\n"
		"1:\n\t"
		"mov.b	@%0+, %2\n\t"
		"cmp/eq %6, %0\n\t"
		"bt/s	2f\n\t"
		" cmp/eq #0, %3\n\t"
		"bt/s	3f\n\t"
		" cmp/eq %3, %2\n\t"
		"bt/s	1b\n\t"
		" mov.b	@%1+, %3\n\t"
		"add	#-2, %1\n\t"
		"mov.b	@%1, %3\n"
		"2:\n\t"
		"sub	%3, %2\n"
		"3:"
		:"=r" (__cs), "=r" (__ct), "=&r" (__res), "=&z" (__dummy)
		: "0" (__cs), "1" (__ct), "r" (__cs+__n)
		: "t");

	वापस __res;
पूर्ण

#घोषणा __HAVE_ARCH_MEMSET
बाह्य व्योम *स_रखो(व्योम *__s, पूर्णांक __c, माप_प्रकार __count);

#घोषणा __HAVE_ARCH_MEMCPY
बाह्य व्योम *स_नकल(व्योम *__to, __स्थिर__ व्योम *__from, माप_प्रकार __n);

#घोषणा __HAVE_ARCH_MEMMOVE
बाह्य व्योम *स_हटाओ(व्योम *__dest, __स्थिर__ व्योम *__src, माप_प्रकार __n);

#घोषणा __HAVE_ARCH_MEMCHR
बाह्य व्योम *स_प्रथम(स्थिर व्योम *__s, पूर्णांक __c, माप_प्रकार __n);

#घोषणा __HAVE_ARCH_STRLEN
बाह्य माप_प्रकार म_माप(स्थिर अक्षर *);

#पूर्ण_अगर /* __ASM_SH_STRING_H */
