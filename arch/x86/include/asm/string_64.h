<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_STRING_64_H
#घोषणा _ASM_X86_STRING_64_H

#अगर_घोषित __KERNEL__
#समावेश <linux/jump_label.h>

/* Written 2002 by Andi Kleen */

/* Even with __builtin_ the compiler may decide to use the out of line
   function. */

#घोषणा __HAVE_ARCH_MEMCPY 1
बाह्य व्योम *स_नकल(व्योम *to, स्थिर व्योम *from, माप_प्रकार len);
बाह्य व्योम *__स_नकल(व्योम *to, स्थिर व्योम *from, माप_प्रकार len);

#घोषणा __HAVE_ARCH_MEMSET
व्योम *स_रखो(व्योम *s, पूर्णांक c, माप_प्रकार n);
व्योम *__स_रखो(व्योम *s, पूर्णांक c, माप_प्रकार n);

#घोषणा __HAVE_ARCH_MEMSET16
अटल अंतरभूत व्योम *स_रखो16(uपूर्णांक16_t *s, uपूर्णांक16_t v, माप_प्रकार n)
अणु
	दीर्घ d0, d1;
	यंत्र अस्थिर("rep\n\t"
		     "stosw"
		     : "=&c" (d0), "=&D" (d1)
		     : "a" (v), "1" (s), "0" (n)
		     : "memory");
	वापस s;
पूर्ण

#घोषणा __HAVE_ARCH_MEMSET32
अटल अंतरभूत व्योम *स_रखो32(uपूर्णांक32_t *s, uपूर्णांक32_t v, माप_प्रकार n)
अणु
	दीर्घ d0, d1;
	यंत्र अस्थिर("rep\n\t"
		     "stosl"
		     : "=&c" (d0), "=&D" (d1)
		     : "a" (v), "1" (s), "0" (n)
		     : "memory");
	वापस s;
पूर्ण

#घोषणा __HAVE_ARCH_MEMSET64
अटल अंतरभूत व्योम *स_रखो64(uपूर्णांक64_t *s, uपूर्णांक64_t v, माप_प्रकार n)
अणु
	दीर्घ d0, d1;
	यंत्र अस्थिर("rep\n\t"
		     "stosq"
		     : "=&c" (d0), "=&D" (d1)
		     : "a" (v), "1" (s), "0" (n)
		     : "memory");
	वापस s;
पूर्ण

#घोषणा __HAVE_ARCH_MEMMOVE
व्योम *स_हटाओ(व्योम *dest, स्थिर व्योम *src, माप_प्रकार count);
व्योम *__स_हटाओ(व्योम *dest, स्थिर व्योम *src, माप_प्रकार count);

पूर्णांक स_भेद(स्थिर व्योम *cs, स्थिर व्योम *ct, माप_प्रकार count);
माप_प्रकार म_माप(स्थिर अक्षर *s);
अक्षर *म_नकल(अक्षर *dest, स्थिर अक्षर *src);
अक्षर *म_जोड़ो(अक्षर *dest, स्थिर अक्षर *src);
पूर्णांक म_भेद(स्थिर अक्षर *cs, स्थिर अक्षर *ct);

#अगर defined(CONFIG_KASAN) && !defined(__SANITIZE_ADDRESS__)

/*
 * For files that not instrumented (e.g. mm/slub.c) we
 * should use not instrumented version of mem* functions.
 */

#अघोषित स_नकल
#घोषणा स_नकल(dst, src, len) __स_नकल(dst, src, len)
#घोषणा स_हटाओ(dst, src, len) __स_हटाओ(dst, src, len)
#घोषणा स_रखो(s, c, n) __स_रखो(s, c, n)

#अगर_अघोषित __NO_FORTIFY
#घोषणा __NO_FORTIFY /* FORTIFY_SOURCE uses __builtin_स_नकल, etc. */
#पूर्ण_अगर

#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_HAS_UACCESS_FLUSHCACHE
#घोषणा __HAVE_ARCH_MEMCPY_FLUSHCACHE 1
व्योम __स_नकल_flushcache(व्योम *dst, स्थिर व्योम *src, माप_प्रकार cnt);
अटल __always_अंतरभूत व्योम स_नकल_flushcache(व्योम *dst, स्थिर व्योम *src, माप_प्रकार cnt)
अणु
	अगर (__builtin_स्थिरant_p(cnt)) अणु
		चयन (cnt) अणु
			हाल 4:
				यंत्र ("movntil %1, %0" : "=m"(*(u32 *)dst) : "r"(*(u32 *)src));
				वापस;
			हाल 8:
				यंत्र ("movntiq %1, %0" : "=m"(*(u64 *)dst) : "r"(*(u64 *)src));
				वापस;
			हाल 16:
				यंत्र ("movntiq %1, %0" : "=m"(*(u64 *)dst) : "r"(*(u64 *)src));
				यंत्र ("movntiq %1, %0" : "=m"(*(u64 *)(dst + 8)) : "r"(*(u64 *)(src + 8)));
				वापस;
		पूर्ण
	पूर्ण
	__स_नकल_flushcache(dst, src, cnt);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_X86_STRING_64_H */
