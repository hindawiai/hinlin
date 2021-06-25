<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *    Copyright IBM Corp. 1999
 *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),
 */

#अगर_अघोषित _S390_STRING_H_
#घोषणा _S390_STRING_H_

#अगर_अघोषित _LINUX_TYPES_H
#समावेश <linux/types.h>
#पूर्ण_अगर

#घोषणा __HAVE_ARCH_MEMCPY	/* gcc builtin & arch function */
#घोषणा __HAVE_ARCH_MEMMOVE	/* gcc builtin & arch function */
#घोषणा __HAVE_ARCH_MEMSET	/* gcc builtin & arch function */
#घोषणा __HAVE_ARCH_MEMSET16	/* arch function */
#घोषणा __HAVE_ARCH_MEMSET32	/* arch function */
#घोषणा __HAVE_ARCH_MEMSET64	/* arch function */

व्योम *स_नकल(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n);
व्योम *स_रखो(व्योम *s, पूर्णांक c, माप_प्रकार n);
व्योम *स_हटाओ(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n);

#अगर_अघोषित CONFIG_KASAN
#घोषणा __HAVE_ARCH_MEMCHR	/* अंतरभूत & arch function */
#घोषणा __HAVE_ARCH_MEMCMP	/* arch function */
#घोषणा __HAVE_ARCH_MEMSCAN	/* अंतरभूत & arch function */
#घोषणा __HAVE_ARCH_STRCAT	/* अंतरभूत & arch function */
#घोषणा __HAVE_ARCH_STRCMP	/* arch function */
#घोषणा __HAVE_ARCH_STRCPY	/* अंतरभूत & arch function */
#घोषणा __HAVE_ARCH_STRLCAT	/* arch function */
#घोषणा __HAVE_ARCH_STRLCPY	/* arch function */
#घोषणा __HAVE_ARCH_STRLEN	/* अंतरभूत & arch function */
#घोषणा __HAVE_ARCH_STRNCAT	/* arch function */
#घोषणा __HAVE_ARCH_STRNCPY	/* arch function */
#घोषणा __HAVE_ARCH_STRNLEN	/* अंतरभूत & arch function */
#घोषणा __HAVE_ARCH_STRRCHR	/* arch function */
#घोषणा __HAVE_ARCH_STRSTR	/* arch function */

/* Prototypes क्रम non-अंतरभूतd arch strings functions. */
पूर्णांक स_भेद(स्थिर व्योम *s1, स्थिर व्योम *s2, माप_प्रकार n);
पूर्णांक म_भेद(स्थिर अक्षर *s1, स्थिर अक्षर *s2);
माप_प्रकार strlcat(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार n);
माप_प्रकार strlcpy(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार size);
अक्षर *म_जोड़न(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार n);
अक्षर *म_नकलन(अक्षर *dest, स्थिर अक्षर *src, माप_प्रकार n);
अक्षर *म_खोजप(स्थिर अक्षर *s, पूर्णांक c);
अक्षर *म_माला(स्थिर अक्षर *s1, स्थिर अक्षर *s2);
#पूर्ण_अगर /* !CONFIG_KASAN */

#अघोषित __HAVE_ARCH_STRCHR
#अघोषित __HAVE_ARCH_STRNCHR
#अघोषित __HAVE_ARCH_STRNCMP
#अघोषित __HAVE_ARCH_STRPBRK
#अघोषित __HAVE_ARCH_STRSEP
#अघोषित __HAVE_ARCH_STRSPN

#अगर defined(CONFIG_KASAN) && !defined(__SANITIZE_ADDRESS__)

बाह्य व्योम *__स_नकल(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n);
बाह्य व्योम *__स_रखो(व्योम *s, पूर्णांक c, माप_प्रकार n);
बाह्य व्योम *__स_हटाओ(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n);

/*
 * For files that are not instrumented (e.g. mm/slub.c) we
 * should use not instrumented version of mem* functions.
 */

#घोषणा स_नकल(dst, src, len) __स_नकल(dst, src, len)
#घोषणा स_हटाओ(dst, src, len) __स_हटाओ(dst, src, len)
#घोषणा स_रखो(s, c, n) __स_रखो(s, c, n)
#घोषणा म_माप(s) __म_माप(s)

#घोषणा __no_sanitize_prefix_strfunc(x) __##x

#अगर_अघोषित __NO_FORTIFY
#घोषणा __NO_FORTIFY /* FORTIFY_SOURCE uses __builtin_स_नकल, etc. */
#पूर्ण_अगर

#अन्यथा
#घोषणा __no_sanitize_prefix_strfunc(x) x
#पूर्ण_अगर /* defined(CONFIG_KASAN) && !defined(__SANITIZE_ADDRESS__) */

व्योम *__स_रखो16(uपूर्णांक16_t *s, uपूर्णांक16_t v, माप_प्रकार count);
व्योम *__स_रखो32(uपूर्णांक32_t *s, uपूर्णांक32_t v, माप_प्रकार count);
व्योम *__स_रखो64(uपूर्णांक64_t *s, uपूर्णांक64_t v, माप_प्रकार count);

अटल अंतरभूत व्योम *स_रखो16(uपूर्णांक16_t *s, uपूर्णांक16_t v, माप_प्रकार count)
अणु
	वापस __स_रखो16(s, v, count * माप(v));
पूर्ण

अटल अंतरभूत व्योम *स_रखो32(uपूर्णांक32_t *s, uपूर्णांक32_t v, माप_प्रकार count)
अणु
	वापस __स_रखो32(s, v, count * माप(v));
पूर्ण

अटल अंतरभूत व्योम *स_रखो64(uपूर्णांक64_t *s, uपूर्णांक64_t v, माप_प्रकार count)
अणु
	वापस __स_रखो64(s, v, count * माप(v));
पूर्ण

#अगर !defined(IN_ARCH_STRING_C) && (!defined(CONFIG_FORTIFY_SOURCE) || defined(__NO_FORTIFY))

#अगर_घोषित __HAVE_ARCH_MEMCHR
अटल अंतरभूत व्योम *स_प्रथम(स्थिर व्योम * s, पूर्णांक c, माप_प्रकार n)
अणु
	रेजिस्टर पूर्णांक r0 यंत्र("0") = (अक्षर) c;
	स्थिर व्योम *ret = s + n;

	यंत्र अस्थिर(
		"0:	srst	%0,%1\n"
		"	jo	0b\n"
		"	jl	1f\n"
		"	la	%0,0\n"
		"1:"
		: "+a" (ret), "+&a" (s) : "d" (r0) : "cc", "memory");
	वापस (व्योम *) ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित __HAVE_ARCH_MEMSCAN
अटल अंतरभूत व्योम *memscan(व्योम *s, पूर्णांक c, माप_प्रकार n)
अणु
	रेजिस्टर पूर्णांक r0 यंत्र("0") = (अक्षर) c;
	स्थिर व्योम *ret = s + n;

	यंत्र अस्थिर(
		"0:	srst	%0,%1\n"
		"	jo	0b\n"
		: "+a" (ret), "+&a" (s) : "d" (r0) : "cc", "memory");
	वापस (व्योम *) ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित __HAVE_ARCH_STRCAT
अटल अंतरभूत अक्षर *म_जोड़ो(अक्षर *dst, स्थिर अक्षर *src)
अणु
	रेजिस्टर पूर्णांक r0 यंत्र("0") = 0;
	अचिन्हित दीर्घ dummy;
	अक्षर *ret = dst;

	यंत्र अस्थिर(
		"0:	srst	%0,%1\n"
		"	jo	0b\n"
		"1:	mvst	%0,%2\n"
		"	jo	1b"
		: "=&a" (dummy), "+a" (dst), "+a" (src)
		: "d" (r0), "0" (0) : "cc", "memory" );
	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित __HAVE_ARCH_STRCPY
अटल अंतरभूत अक्षर *म_नकल(अक्षर *dst, स्थिर अक्षर *src)
अणु
	रेजिस्टर पूर्णांक r0 यंत्र("0") = 0;
	अक्षर *ret = dst;

	यंत्र अस्थिर(
		"0:	mvst	%0,%1\n"
		"	jo	0b"
		: "+&a" (dst), "+&a" (src) : "d" (r0)
		: "cc", "memory");
	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर defined(__HAVE_ARCH_STRLEN) || (defined(CONFIG_KASAN) && !defined(__SANITIZE_ADDRESS__))
अटल अंतरभूत माप_प्रकार __no_sanitize_prefix_strfunc(म_माप)(स्थिर अक्षर *s)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("0") = 0;
	स्थिर अक्षर *पंचांगp = s;

	यंत्र अस्थिर(
		"0:	srst	%0,%1\n"
		"	jo	0b"
		: "+d" (r0), "+a" (पंचांगp) :  : "cc", "memory");
	वापस r0 - (अचिन्हित दीर्घ) s;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित __HAVE_ARCH_STRNLEN
अटल अंतरभूत माप_प्रकार strnlen(स्थिर अक्षर * s, माप_प्रकार n)
अणु
	रेजिस्टर पूर्णांक r0 यंत्र("0") = 0;
	स्थिर अक्षर *पंचांगp = s;
	स्थिर अक्षर *end = s + n;

	यंत्र अस्थिर(
		"0:	srst	%0,%1\n"
		"	jo	0b"
		: "+a" (end), "+a" (पंचांगp) : "d" (r0)  : "cc", "memory");
	वापस end - s;
पूर्ण
#पूर्ण_अगर
#अन्यथा /* IN_ARCH_STRING_C */
व्योम *स_प्रथम(स्थिर व्योम * s, पूर्णांक c, माप_प्रकार n);
व्योम *memscan(व्योम *s, पूर्णांक c, माप_प्रकार n);
अक्षर *म_जोड़ो(अक्षर *dst, स्थिर अक्षर *src);
अक्षर *म_नकल(अक्षर *dst, स्थिर अक्षर *src);
माप_प्रकार म_माप(स्थिर अक्षर *s);
माप_प्रकार strnlen(स्थिर अक्षर * s, माप_प्रकार n);
#पूर्ण_अगर /* !IN_ARCH_STRING_C */

#पूर्ण_अगर /* __S390_STRING_H_ */
