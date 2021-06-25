<शैली गुरु>
/*
 * include/यंत्र-xtensa/माला.स
 *
 * These trivial string functions are considered part of the खुला करोमुख्य.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

/* We should optimize these. See arch/xtensa/lib/म_नकलन_user.S */

#अगर_अघोषित _XTENSA_STRING_H
#घोषणा _XTENSA_STRING_H

#घोषणा __HAVE_ARCH_STRCPY
अटल अंतरभूत अक्षर *म_नकल(अक्षर *__dest, स्थिर अक्षर *__src)
अणु
	रेजिस्टर अक्षर *__xdest = __dest;
	अचिन्हित दीर्घ __dummy;

	__यंत्र__ __अस्थिर__("1:\n\t"
		"l8ui	%2, %1, 0\n\t"
		"s8i	%2, %0, 0\n\t"
		"addi	%1, %1, 1\n\t"
		"addi	%0, %0, 1\n\t"
		"bnez	%2, 1b\n\t"
		: "=r" (__dest), "=r" (__src), "=&r" (__dummy)
		: "0" (__dest), "1" (__src)
		: "memory");

	वापस __xdest;
पूर्ण

#घोषणा __HAVE_ARCH_STRNCPY
अटल अंतरभूत अक्षर *म_नकलन(अक्षर *__dest, स्थिर अक्षर *__src, माप_प्रकार __n)
अणु
	रेजिस्टर अक्षर *__xdest = __dest;
	अचिन्हित दीर्घ __dummy;

	अगर (__n == 0)
		वापस __xdest;

	__यंत्र__ __अस्थिर__(
		"1:\n\t"
		"l8ui	%2, %1, 0\n\t"
		"s8i	%2, %0, 0\n\t"
		"addi	%1, %1, 1\n\t"
		"addi	%0, %0, 1\n\t"
		"beqz	%2, 2f\n\t"
		"bne	%1, %5, 1b\n"
		"2:"
		: "=r" (__dest), "=r" (__src), "=&r" (__dummy)
		: "0" (__dest), "1" (__src), "r" ((uपूर्णांकptr_t)__src+__n)
		: "memory");

	वापस __xdest;
पूर्ण

#घोषणा __HAVE_ARCH_STRCMP
अटल अंतरभूत पूर्णांक म_भेद(स्थिर अक्षर *__cs, स्थिर अक्षर *__ct)
अणु
	रेजिस्टर पूर्णांक __res;
	अचिन्हित दीर्घ __dummy;

	__यंत्र__ __अस्थिर__(
		"1:\n\t"
		"l8ui	%3, %1, 0\n\t"
		"addi	%1, %1, 1\n\t"
		"l8ui	%2, %0, 0\n\t"
		"addi	%0, %0, 1\n\t"
		"beqz	%2, 2f\n\t"
		"beq	%2, %3, 1b\n"
		"2:\n\t"
		"sub	%2, %2, %3"
		: "=r" (__cs), "=r" (__ct), "=&r" (__res), "=&r" (__dummy)
		: "0" (__cs), "1" (__ct));

	वापस __res;
पूर्ण

#घोषणा __HAVE_ARCH_STRNCMP
अटल अंतरभूत पूर्णांक म_भेदन(स्थिर अक्षर *__cs, स्थिर अक्षर *__ct, माप_प्रकार __n)
अणु
	रेजिस्टर पूर्णांक __res;
	अचिन्हित दीर्घ __dummy;

	__यंत्र__ __अस्थिर__(
		"mov	%2, %3\n"
		"1:\n\t"
		"beq	%0, %6, 2f\n\t"
		"l8ui	%3, %1, 0\n\t"
		"addi	%1, %1, 1\n\t"
		"l8ui	%2, %0, 0\n\t"
		"addi	%0, %0, 1\n\t"
		"beqz	%2, 2f\n\t"
		"beqz	%3, 2f\n\t"
		"beq	%2, %3, 1b\n"
		"2:\n\t"
		"sub	%2, %2, %3"
		: "=r" (__cs), "=r" (__ct), "=&r" (__res), "=&r" (__dummy)
		: "0" (__cs), "1" (__ct), "r" ((uपूर्णांकptr_t)__cs+__n));

	वापस __res;
पूर्ण

#घोषणा __HAVE_ARCH_MEMSET
बाह्य व्योम *स_रखो(व्योम *__s, पूर्णांक __c, माप_प्रकार __count);
बाह्य व्योम *__स_रखो(व्योम *__s, पूर्णांक __c, माप_प्रकार __count);

#घोषणा __HAVE_ARCH_MEMCPY
बाह्य व्योम *स_नकल(व्योम *__to, __स्थिर__ व्योम *__from, माप_प्रकार __n);
बाह्य व्योम *__स_नकल(व्योम *__to, __स्थिर__ व्योम *__from, माप_प्रकार __n);

#घोषणा __HAVE_ARCH_MEMMOVE
बाह्य व्योम *स_हटाओ(व्योम *__dest, __स्थिर__ व्योम *__src, माप_प्रकार __n);
बाह्य व्योम *__स_हटाओ(व्योम *__dest, __स्थिर__ व्योम *__src, माप_प्रकार __n);

/* Don't build bcopy at all ...  */
#घोषणा __HAVE_ARCH_BCOPY

#अगर defined(CONFIG_KASAN) && !defined(__SANITIZE_ADDRESS__)

/*
 * For files that are not instrumented (e.g. mm/slub.c) we
 * should use not instrumented version of mem* functions.
 */

#घोषणा स_नकल(dst, src, len) __स_नकल(dst, src, len)
#घोषणा स_हटाओ(dst, src, len) __स_हटाओ(dst, src, len)
#घोषणा स_रखो(s, c, n) __स_रखो(s, c, n)

#अगर_अघोषित __NO_FORTIFY
#घोषणा __NO_FORTIFY /* FORTIFY_SOURCE uses __builtin_स_नकल, etc. */
#पूर्ण_अगर
#पूर्ण_अगर

#पूर्ण_अगर	/* _XTENSA_STRING_H */
