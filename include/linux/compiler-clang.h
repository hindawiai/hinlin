<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_COMPILER_TYPES_H
#त्रुटि "Please don't include <linux/compiler-clang.h> directly, include <linux/compiler.h> instead."
#पूर्ण_अगर

/* Compiler specअगरic definitions क्रम Clang compiler */

/* same as gcc, this was present in clang-2.6 so we can assume it works
 * with any version that can compile the kernel
 */
#घोषणा __UNIQUE_ID(prefix) __PASTE(__PASTE(__UNIQUE_ID_, prefix), __COUNTER__)

/* all clang versions usable with the kernel support KASAN ABI version 5 */
#घोषणा KASAN_ABI_VERSION 5

#अगर __has_feature(address_sanitizer) || __has_feature(hwaddress_sanitizer)
/* Emulate GCC's __SANITIZE_ADDRESS__ flag */
#घोषणा __SANITIZE_ADDRESS__
#घोषणा __no_sanitize_address \
		__attribute__((no_sanitize("address", "hwaddress")))
#अन्यथा
#घोषणा __no_sanitize_address
#पूर्ण_अगर

#अगर __has_feature(thपढ़ो_sanitizer)
/* emulate gcc's __SANITIZE_THREAD__ flag */
#घोषणा __SANITIZE_THREAD__
#घोषणा __no_sanitize_thपढ़ो \
		__attribute__((no_sanitize("thread")))
#अन्यथा
#घोषणा __no_sanitize_thपढ़ो
#पूर्ण_अगर

#अगर defined(CONFIG_ARCH_USE_BUILTIN_BSWAP)
#घोषणा __HAVE_BUILTIN_BSWAP32__
#घोषणा __HAVE_BUILTIN_BSWAP64__
#घोषणा __HAVE_BUILTIN_BSWAP16__
#पूर्ण_अगर /* CONFIG_ARCH_USE_BUILTIN_BSWAP */

#अगर __has_feature(undefined_behavior_sanitizer)
/* GCC करोes not have __SANITIZE_UNDEFINED__ */
#घोषणा __no_sanitize_undefined \
		__attribute__((no_sanitize("undefined")))
#अन्यथा
#घोषणा __no_sanitize_undefined
#पूर्ण_अगर

/*
 * Not all versions of clang implement the type-generic versions
 * of the builtin overflow checkers. Fortunately, clang implements
 * __has_builtin allowing us to aव्योम awkward version
 * checks. Unक्रमtunately, we करोn't know which version of gcc clang
 * pretends to be, so the macro may or may not be defined.
 */
#अगर __has_builtin(__builtin_mul_overflow) && \
    __has_builtin(__builtin_add_overflow) && \
    __has_builtin(__builtin_sub_overflow)
#घोषणा COMPILER_HAS_GENERIC_BUILTIN_OVERFLOW 1
#पूर्ण_अगर

#अगर __has_feature(shaकरोw_call_stack)
# define __noscs	__attribute__((__no_sanitize__("shadow-call-stack")))
#पूर्ण_अगर

#घोषणा __nocfi		__attribute__((__no_sanitize__("cfi")))
#घोषणा __cficanonical	__attribute__((__cfi_canonical_jump_table__))
