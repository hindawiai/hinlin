<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 ARM Ltd.
 */
#अगर_अघोषित __ASM_STRING_H
#घोषणा __ASM_STRING_H

#अगर !(defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS))
#घोषणा __HAVE_ARCH_STRRCHR
बाह्य अक्षर *म_खोजप(स्थिर अक्षर *, पूर्णांक c);

#घोषणा __HAVE_ARCH_STRCHR
बाह्य अक्षर *म_अक्षर(स्थिर अक्षर *, पूर्णांक c);

#घोषणा __HAVE_ARCH_STRCMP
बाह्य पूर्णांक म_भेद(स्थिर अक्षर *, स्थिर अक्षर *);

#घोषणा __HAVE_ARCH_STRNCMP
बाह्य पूर्णांक म_भेदन(स्थिर अक्षर *, स्थिर अक्षर *, __kernel_माप_प्रकार);

#घोषणा __HAVE_ARCH_STRLEN
बाह्य __kernel_माप_प्रकार म_माप(स्थिर अक्षर *);

#घोषणा __HAVE_ARCH_STRNLEN
बाह्य __kernel_माप_प्रकार strnlen(स्थिर अक्षर *, __kernel_माप_प्रकार);

#घोषणा __HAVE_ARCH_MEMCMP
बाह्य पूर्णांक स_भेद(स्थिर व्योम *, स्थिर व्योम *, माप_प्रकार);

#घोषणा __HAVE_ARCH_MEMCHR
बाह्य व्योम *स_प्रथम(स्थिर व्योम *, पूर्णांक, __kernel_माप_प्रकार);
#पूर्ण_अगर

#घोषणा __HAVE_ARCH_MEMCPY
बाह्य व्योम *स_नकल(व्योम *, स्थिर व्योम *, __kernel_माप_प्रकार);
बाह्य व्योम *__स_नकल(व्योम *, स्थिर व्योम *, __kernel_माप_प्रकार);

#घोषणा __HAVE_ARCH_MEMMOVE
बाह्य व्योम *स_हटाओ(व्योम *, स्थिर व्योम *, __kernel_माप_प्रकार);
बाह्य व्योम *__स_हटाओ(व्योम *, स्थिर व्योम *, __kernel_माप_प्रकार);

#घोषणा __HAVE_ARCH_MEMSET
बाह्य व्योम *स_रखो(व्योम *, पूर्णांक, __kernel_माप_प्रकार);
बाह्य व्योम *__स_रखो(व्योम *, पूर्णांक, __kernel_माप_प्रकार);

#अगर_घोषित CONFIG_ARCH_HAS_UACCESS_FLUSHCACHE
#घोषणा __HAVE_ARCH_MEMCPY_FLUSHCACHE
व्योम स_नकल_flushcache(व्योम *dst, स्थिर व्योम *src, माप_प्रकार cnt);
#पूर्ण_अगर

#अगर (defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)) && \
	!defined(__SANITIZE_ADDRESS__)

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

#पूर्ण_अगर
