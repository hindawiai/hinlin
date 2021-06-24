<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This provides an optimized implementation of स_नकल, and a simplअगरied
 * implementation of स_रखो and स_हटाओ. These are used here because the
 * standard kernel runसमय versions are not yet available and we करोn't
 * trust the gcc built-in implementations as they may करो unexpected things
 * (e.g. FPU ops) in the minimal decompression stub execution environment.
 */
#समावेश "error.h"

#समावेश "../string.c"

#अगर_घोषित CONFIG_X86_32
अटल व्योम *____स_नकल(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n)
अणु
	पूर्णांक d0, d1, d2;
	यंत्र अस्थिर(
		"rep ; movsl\n\t"
		"movl %4,%%ecx\n\t"
		"rep ; movsb\n\t"
		: "=&c" (d0), "=&D" (d1), "=&S" (d2)
		: "0" (n >> 2), "g" (n & 3), "1" (dest), "2" (src)
		: "memory");

	वापस dest;
पूर्ण
#अन्यथा
अटल व्योम *____स_नकल(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n)
अणु
	दीर्घ d0, d1, d2;
	यंत्र अस्थिर(
		"rep ; movsq\n\t"
		"movq %4,%%rcx\n\t"
		"rep ; movsb\n\t"
		: "=&c" (d0), "=&D" (d1), "=&S" (d2)
		: "0" (n >> 3), "g" (n & 7), "1" (dest), "2" (src)
		: "memory");

	वापस dest;
पूर्ण
#पूर्ण_अगर

व्योम *स_रखो(व्योम *s, पूर्णांक c, माप_प्रकार n)
अणु
	पूर्णांक i;
	अक्षर *ss = s;

	क्रम (i = 0; i < n; i++)
		ss[i] = c;
	वापस s;
पूर्ण

व्योम *स_हटाओ(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n)
अणु
	अचिन्हित अक्षर *d = dest;
	स्थिर अचिन्हित अक्षर *s = src;

	अगर (d <= s || d - s >= n)
		वापस ____स_नकल(dest, src, n);

	जबतक (n-- > 0)
		d[n] = s[n];

	वापस dest;
पूर्ण

/* Detect and warn about potential overlaps, but handle them with स_हटाओ. */
व्योम *स_नकल(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n)
अणु
	अगर (dest > src && dest - src < n) अणु
		warn("Avoiding potentially unsafe overlapping memcpy()!");
		वापस स_हटाओ(dest, src, n);
	पूर्ण
	वापस ____स_नकल(dest, src, n);
पूर्ण

#अगर_घोषित CONFIG_KASAN
बाह्य व्योम *__स_रखो(व्योम *s, पूर्णांक c, माप_प्रकार n) __alias(स_रखो);
बाह्य व्योम *__स_हटाओ(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n) __alias(स_हटाओ);
बाह्य व्योम *__स_नकल(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n) __alias(स_नकल);
#पूर्ण_अगर
