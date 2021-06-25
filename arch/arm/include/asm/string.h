<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARM_STRING_H
#घोषणा __ASM_ARM_STRING_H

/*
 * We करोn't करो अंतरभूत string functions, since the
 * optimised अंतरभूत यंत्र versions are not small.
 *
 * The __underscore versions of some functions are क्रम KASan to be able
 * to replace them with instrumented versions.
 */

#घोषणा __HAVE_ARCH_STRRCHR
बाह्य अक्षर * म_खोजप(स्थिर अक्षर * s, पूर्णांक c);

#घोषणा __HAVE_ARCH_STRCHR
बाह्य अक्षर * म_अक्षर(स्थिर अक्षर * s, पूर्णांक c);

#घोषणा __HAVE_ARCH_MEMCPY
बाह्य व्योम * स_नकल(व्योम *, स्थिर व्योम *, __kernel_माप_प्रकार);
बाह्य व्योम *__स_नकल(व्योम *dest, स्थिर व्योम *src, __kernel_माप_प्रकार n);

#घोषणा __HAVE_ARCH_MEMMOVE
बाह्य व्योम * स_हटाओ(व्योम *, स्थिर व्योम *, __kernel_माप_प्रकार);
बाह्य व्योम *__स_हटाओ(व्योम *dest, स्थिर व्योम *src, __kernel_माप_प्रकार n);

#घोषणा __HAVE_ARCH_MEMCHR
बाह्य व्योम * स_प्रथम(स्थिर व्योम *, पूर्णांक, __kernel_माप_प्रकार);

#घोषणा __HAVE_ARCH_MEMSET
बाह्य व्योम * स_रखो(व्योम *, पूर्णांक, __kernel_माप_प्रकार);
बाह्य व्योम *__स_रखो(व्योम *s, पूर्णांक c, __kernel_माप_प्रकार n);

#घोषणा __HAVE_ARCH_MEMSET32
बाह्य व्योम *__स_रखो32(uपूर्णांक32_t *, uपूर्णांक32_t v, __kernel_माप_प्रकार);
अटल अंतरभूत व्योम *स_रखो32(uपूर्णांक32_t *p, uपूर्णांक32_t v, __kernel_माप_प्रकार n)
अणु
	वापस __स_रखो32(p, v, n * 4);
पूर्ण

#घोषणा __HAVE_ARCH_MEMSET64
बाह्य व्योम *__स_रखो64(uपूर्णांक64_t *, uपूर्णांक32_t low, __kernel_माप_प्रकार, uपूर्णांक32_t hi);
अटल अंतरभूत व्योम *स_रखो64(uपूर्णांक64_t *p, uपूर्णांक64_t v, __kernel_माप_प्रकार n)
अणु
	वापस __स_रखो64(p, v, n * 8, v >> 32);
पूर्ण

/*
 * For files that are not instrumented (e.g. mm/slub.c) we
 * must use non-instrumented versions of the mem*
 * functions named __स_नकल() etc. All such kernel code has
 * been tagged with KASAN_SANITIZE_file.o = n, which means
 * that the address sanitization argument isn't passed to the
 * compiler, and __SANITIZE_ADDRESS__ is not set. As a result
 * these defines kick in.
 */
#अगर defined(CONFIG_KASAN) && !defined(__SANITIZE_ADDRESS__)
#घोषणा स_नकल(dst, src, len) __स_नकल(dst, src, len)
#घोषणा स_हटाओ(dst, src, len) __स_हटाओ(dst, src, len)
#घोषणा स_रखो(s, c, n) __स_रखो(s, c, n)

#अगर_अघोषित __NO_FORTIFY
#घोषणा __NO_FORTIFY /* FORTIFY_SOURCE uses __builtin_स_नकल, etc. */
#पूर्ण_अगर

#पूर्ण_अगर

#पूर्ण_अगर
