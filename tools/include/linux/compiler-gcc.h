<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_LINUX_COMPILER_H_
#त्रुटि "Please don't include <linux/compiler-gcc.h> directly, include <linux/compiler.h> instead."
#पूर्ण_अगर

/*
 * Common definitions क्रम all gcc versions go here.
 */
#अगर_अघोषित GCC_VERSION
#घोषणा GCC_VERSION (__GNUC__ * 10000		\
		     + __GNUC_MINOR__ * 100	\
		     + __GNUC_PATCHLEVEL__)
#पूर्ण_अगर

#अगर GCC_VERSION >= 70000 && !defined(__CHECKER__)
# define __fallthrough __attribute__ ((fallthrough))
#पूर्ण_अगर

#अगर GCC_VERSION >= 40300
# define __compileसमय_error(message) __attribute__((error(message)))
#पूर्ण_अगर /* GCC_VERSION >= 40300 */

/* &a[0] degrades to a poपूर्णांकer: a dअगरferent type from an array */
#घोषणा __must_be_array(a)	BUILD_BUG_ON_ZERO(__same_type((a), &(a)[0]))

#अगर_अघोषित __pure
#घोषणा  __pure		__attribute__((pure))
#पूर्ण_अगर
#घोषणा  noअंतरभूत	__attribute__((noअंतरभूत))
#अगर_अघोषित __packed
#घोषणा __packed	__attribute__((packed))
#पूर्ण_अगर
#अगर_अघोषित __noवापस
#घोषणा __noवापस	__attribute__((noवापस))
#पूर्ण_अगर
#अगर_अघोषित __aligned
#घोषणा __aligned(x)	__attribute__((aligned(x)))
#पूर्ण_अगर
#घोषणा __म_लिखो(a, b)	__attribute__((क्रमmat(म_लिखो, a, b)))
#घोषणा __म_पूछो(a, b)	__attribute__((क्रमmat(म_पूछो, a, b)))

#अगर GCC_VERSION >= 50100
#घोषणा COMPILER_HAS_GENERIC_BUILTIN_OVERFLOW 1
#पूर्ण_अगर
