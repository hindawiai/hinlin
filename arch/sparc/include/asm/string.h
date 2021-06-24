<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ___ASM_SPARC_STRING_H
#घोषणा ___ASM_SPARC_STRING_H
#अगर defined(__sparc__) && defined(__arch64__)
#समावेश <यंत्र/string_64.h>
#अन्यथा
#समावेश <यंत्र/string_32.h>
#पूर्ण_अगर

/* First the mem*() things. */
#घोषणा __HAVE_ARCH_MEMMOVE
व्योम *स_हटाओ(व्योम *, स्थिर व्योम *, __kernel_माप_प्रकार);

#घोषणा __HAVE_ARCH_MEMCPY
#घोषणा स_नकल(t, f, n) __builtin_स_नकल(t, f, n)

#घोषणा __HAVE_ARCH_MEMSET
#घोषणा स_रखो(s, c, count) __builtin_स_रखो(s, c, count)

#घोषणा __HAVE_ARCH_MEMSCAN

#घोषणा memscan(__arg0, __अक्षर, __arg2)						\
(अणु										\
	व्योम *__memscan_zero(व्योम *, माप_प्रकार);					\
	व्योम *__memscan_generic(व्योम *, पूर्णांक, माप_प्रकार);				\
	व्योम *__retval, *__addr = (__arg0);					\
	माप_प्रकार __size = (__arg2);						\
										\
	अगर(__builtin_स्थिरant_p(__अक्षर) && !(__अक्षर))				\
		__retval = __memscan_zero(__addr, __size);			\
	अन्यथा									\
		__retval = __memscan_generic(__addr, (__अक्षर), __size);		\
										\
	__retval;								\
पूर्ण)

#घोषणा __HAVE_ARCH_MEMCMP
पूर्णांक स_भेद(स्थिर व्योम *,स्थिर व्योम *,__kernel_माप_प्रकार);

/* Now the str*() stuff... */
#घोषणा __HAVE_ARCH_STRLEN
__kernel_माप_प्रकार म_माप(स्थिर अक्षर *);

#घोषणा __HAVE_ARCH_STRNCMP
पूर्णांक म_भेदन(स्थिर अक्षर *, स्थिर अक्षर *, __kernel_माप_प्रकार);

#पूर्ण_अगर
