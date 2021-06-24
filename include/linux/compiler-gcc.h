<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_COMPILER_TYPES_H
#त्रुटि "Please don't include <linux/compiler-gcc.h> directly, include <linux/compiler.h> instead."
#पूर्ण_अगर

/*
 * Common definitions क्रम all gcc versions go here.
 */
#घोषणा GCC_VERSION (__GNUC__ * 10000		\
		     + __GNUC_MINOR__ * 100	\
		     + __GNUC_PATCHLEVEL__)

/*
 * This macro obfuscates arithmetic on a variable address so that gcc
 * shouldn't recognize the original var, and make assumptions about it.
 *
 * This is needed because the C standard makes it undefined to करो
 * poपूर्णांकer arithmetic on "objects" outside their boundaries and the
 * gcc optimizers assume this is the हाल. In particular they
 * assume such arithmetic करोes not wrap.
 *
 * A miscompilation has been observed because of this on PPC.
 * To work around it we hide the relationship of the poपूर्णांकer and the object
 * using this macro.
 *
 * Versions of the ppc64 compiler beक्रमe 4.1 had a bug where use of
 * RELOC_HIDE could trash r30. The bug can be worked around by changing
 * the अंतरभूत assembly स्थिरraपूर्णांक from =g to =r, in this particular
 * हाल either is valid.
 */
#घोषणा RELOC_HIDE(ptr, off)						\
(अणु									\
	अचिन्हित दीर्घ __ptr;						\
	__यंत्र__ ("" : "=r"(__ptr) : "0"(ptr));				\
	(typeof(ptr)) (__ptr + (off));					\
पूर्ण)

#अगर_घोषित CONFIG_RETPOLINE
#घोषणा __noretpoline __attribute__((__indirect_branch__("keep")))
#पूर्ण_अगर

#घोषणा __UNIQUE_ID(prefix) __PASTE(__PASTE(__UNIQUE_ID_, prefix), __COUNTER__)

#घोषणा __compileसमय_object_size(obj) __builtin_object_size(obj, 0)

#घोषणा __compileसमय_warning(message) __attribute__((__warning__(message)))
#घोषणा __compileसमय_error(message) __attribute__((__error__(message)))

#अगर defined(LATENT_ENTROPY_PLUGIN) && !defined(__CHECKER__)
#घोषणा __latent_entropy __attribute__((latent_entropy))
#पूर्ण_अगर

/*
 * calling noवापस functions, __builtin_unreachable() and __builtin_trap()
 * confuse the stack allocation in gcc, leading to overly large stack
 * frames, see https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82365
 *
 * Adding an empty अंतरभूत assembly beक्रमe it works around the problem
 */
#घोषणा barrier_beक्रमe_unreachable() यंत्र अस्थिर("")

/*
 * Mark a position in code as unreachable.  This can be used to
 * suppress control flow warnings after यंत्र blocks that transfer
 * control अन्यथाwhere.
 */
#घोषणा unreachable() \
	करो अणु					\
		annotate_unreachable();		\
		barrier_beक्रमe_unreachable();	\
		__builtin_unreachable();	\
	पूर्ण जबतक (0)

#अगर defined(RANDSTRUCT_PLUGIN) && !defined(__CHECKER__)
#घोषणा __अक्रमomize_layout __attribute__((अक्रमomize_layout))
#घोषणा __no_अक्रमomize_layout __attribute__((no_अक्रमomize_layout))
/* This anon काष्ठा can add padding, so only enable it under अक्रमकाष्ठा. */
#घोषणा अक्रमomized_काष्ठा_fields_start	काष्ठा अणु
#घोषणा अक्रमomized_काष्ठा_fields_end	पूर्ण __अक्रमomize_layout;
#पूर्ण_अगर

/*
 * GCC 'asm goto' miscompiles certain code sequences:
 *
 *   http://gcc.gnu.org/bugzilla/show_bug.cgi?id=58670
 *
 * Work it around via a compiler barrier quirk suggested by Jakub Jelinek.
 *
 * (यंत्र जाओ is स्वतःmatically अस्थिर - the naming reflects this.)
 */
#घोषणा यंत्र_अस्थिर_जाओ(x...)	करो अणु यंत्र जाओ(x); यंत्र (""); पूर्ण जबतक (0)

#अगर defined(CONFIG_ARCH_USE_BUILTIN_BSWAP)
#घोषणा __HAVE_BUILTIN_BSWAP32__
#घोषणा __HAVE_BUILTIN_BSWAP64__
#घोषणा __HAVE_BUILTIN_BSWAP16__
#पूर्ण_अगर /* CONFIG_ARCH_USE_BUILTIN_BSWAP */

#अगर GCC_VERSION >= 70000
#घोषणा KASAN_ABI_VERSION 5
#या_अगर GCC_VERSION >= 50000
#घोषणा KASAN_ABI_VERSION 4
#या_अगर GCC_VERSION >= 40902
#घोषणा KASAN_ABI_VERSION 3
#पूर्ण_अगर

#अगर __has_attribute(__no_sanitize_address__)
#घोषणा __no_sanitize_address __attribute__((no_sanitize_address))
#अन्यथा
#घोषणा __no_sanitize_address
#पूर्ण_अगर

#अगर defined(__SANITIZE_THREAD__) && __has_attribute(__no_sanitize_thपढ़ो__)
#घोषणा __no_sanitize_thपढ़ो __attribute__((no_sanitize_thपढ़ो))
#अन्यथा
#घोषणा __no_sanitize_thपढ़ो
#पूर्ण_अगर

#अगर __has_attribute(__no_sanitize_undefined__)
#घोषणा __no_sanitize_undefined __attribute__((no_sanitize_undefined))
#अन्यथा
#घोषणा __no_sanitize_undefined
#पूर्ण_अगर

#अगर GCC_VERSION >= 50100
#घोषणा COMPILER_HAS_GENERIC_BUILTIN_OVERFLOW 1
#पूर्ण_अगर

/*
 * Turn inभागidual warnings and errors on and off locally, depending
 * on version.
 */
#घोषणा __diag_GCC(version, severity, s) \
	__diag_GCC_ ## version(__diag_GCC_ ## severity s)

/* Severity used in pragma directives */
#घोषणा __diag_GCC_ignore	ignored
#घोषणा __diag_GCC_warn		warning
#घोषणा __diag_GCC_error	error

#घोषणा __diag_str1(s)		#s
#घोषणा __diag_str(s)		__diag_str1(s)
#घोषणा __diag(s)		_Pragma(__diag_str(GCC diagnostic s))

#अगर GCC_VERSION >= 80000
#घोषणा __diag_GCC_8(s)		__diag(s)
#अन्यथा
#घोषणा __diag_GCC_8(s)
#पूर्ण_अगर
