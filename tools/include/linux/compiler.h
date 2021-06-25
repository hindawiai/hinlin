<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_LINUX_COMPILER_H_
#घोषणा _TOOLS_LINUX_COMPILER_H_

#समावेश <linux/compiler_types.h>

#अगर_अघोषित __compileसमय_error
# define __compileसमय_error(message)
#पूर्ण_अगर

#अगर_घोषित __OPTIMIZE__
# define __compileसमय_निश्चित(condition, msg, prefix, suffix)		\
	करो अणु								\
		बाह्य व्योम prefix ## suffix(व्योम) __compileसमय_error(msg); \
		अगर (!(condition))					\
			prefix ## suffix();				\
	पूर्ण जबतक (0)
#अन्यथा
# define __compileसमय_निश्चित(condition, msg, prefix, suffix) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा _compileसमय_निश्चित(condition, msg, prefix, suffix) \
	__compileसमय_निश्चित(condition, msg, prefix, suffix)

/**
 * compileसमय_निश्चित - अवरोध build and emit msg अगर condition is false
 * @condition: a compile-समय स्थिरant condition to check
 * @msg:       a message to emit अगर condition is false
 *
 * In tradition of POSIX निश्चित, this macro will अवरोध the build अगर the
 * supplied condition is *false*, emitting the supplied error message अगर the
 * compiler has support to करो so.
 */
#घोषणा compileसमय_निश्चित(condition, msg) \
	_compileसमय_निश्चित(condition, msg, __compileसमय_निश्चित_, __COUNTER__)

/* Optimization barrier */
/* The "volatile" is due to gcc bugs */
#घोषणा barrier() __यंत्र__ __अस्थिर__("": : :"memory")

#अगर_अघोषित __always_अंतरभूत
# define __always_अंतरभूत	अंतरभूत __attribute__((always_अंतरभूत))
#पूर्ण_अगर

#अगर_अघोषित noअंतरभूत
#घोषणा noअंतरभूत
#पूर्ण_अगर

/* Are two types/vars the same type (ignoring qualअगरiers)? */
#अगर_अघोषित __same_type
# define __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))
#पूर्ण_अगर

#अगर_घोषित __ANDROID__
/*
 * FIXME: Big hammer to get rid of tons of:
 *   "warning: always_inline function might not be inlinable"
 *
 * At least on android-ndk-r12/platक्रमms/android-24/arch-arm
 */
#अघोषित __always_अंतरभूत
#घोषणा __always_अंतरभूत	अंतरभूत
#पूर्ण_अगर

#घोषणा __user
#घोषणा __rcu
#घोषणा __पढ़ो_mostly

#अगर_अघोषित __attribute_स्थिर__
# define __attribute_स्थिर__
#पूर्ण_अगर

#अगर_अघोषित __maybe_unused
# define __maybe_unused		__attribute__((unused))
#पूर्ण_अगर

#अगर_अघोषित __used
# define __used		__attribute__((__unused__))
#पूर्ण_अगर

#अगर_अघोषित __packed
# define __packed		__attribute__((__packed__))
#पूर्ण_अगर

#अगर_अघोषित __क्रमce
# define __क्रमce
#पूर्ण_अगर

#अगर_अघोषित __weak
# define __weak			__attribute__((weak))
#पूर्ण_अगर

#अगर_अघोषित likely
# define likely(x)		__builtin_expect(!!(x), 1)
#पूर्ण_अगर

#अगर_अघोषित unlikely
# define unlikely(x)		__builtin_expect(!!(x), 0)
#पूर्ण_अगर

#अगर_अघोषित __init
# define __init
#पूर्ण_अगर

#अगर_अघोषित noअंतरभूत
# define noअंतरभूत
#पूर्ण_अगर

#समावेश <linux/types.h>

/*
 * Following functions are taken from kernel sources and
 * अवरोध aliasing rules in their original क्रमm.
 *
 * While kernel is compiled with -fno-strict-aliasing,
 * perf uses -Wstrict-aliasing=3 which makes build fail
 * under gcc 4.4.
 *
 * Using extra __may_alias__ type to allow aliasing
 * in this हाल.
 */
प्रकार __u8  __attribute__((__may_alias__))  __u8_alias_t;
प्रकार __u16 __attribute__((__may_alias__)) __u16_alias_t;
प्रकार __u32 __attribute__((__may_alias__)) __u32_alias_t;
प्रकार __u64 __attribute__((__may_alias__)) __u64_alias_t;

अटल __always_अंतरभूत व्योम __पढ़ो_once_size(स्थिर अस्थिर व्योम *p, व्योम *res, पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 1: *(__u8_alias_t  *) res = *(अस्थिर __u8_alias_t  *) p; अवरोध;
	हाल 2: *(__u16_alias_t *) res = *(अस्थिर __u16_alias_t *) p; अवरोध;
	हाल 4: *(__u32_alias_t *) res = *(अस्थिर __u32_alias_t *) p; अवरोध;
	हाल 8: *(__u64_alias_t *) res = *(अस्थिर __u64_alias_t *) p; अवरोध;
	शेष:
		barrier();
		__builtin_स_नकल((व्योम *)res, (स्थिर व्योम *)p, size);
		barrier();
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम __ग_लिखो_once_size(अस्थिर व्योम *p, व्योम *res, पूर्णांक size)
अणु
	चयन (size) अणु
	हाल 1: *(अस्थिर  __u8_alias_t *) p = *(__u8_alias_t  *) res; अवरोध;
	हाल 2: *(अस्थिर __u16_alias_t *) p = *(__u16_alias_t *) res; अवरोध;
	हाल 4: *(अस्थिर __u32_alias_t *) p = *(__u32_alias_t *) res; अवरोध;
	हाल 8: *(अस्थिर __u64_alias_t *) p = *(__u64_alias_t *) res; अवरोध;
	शेष:
		barrier();
		__builtin_स_नकल((व्योम *)p, (स्थिर व्योम *)res, size);
		barrier();
	पूर्ण
पूर्ण

/*
 * Prevent the compiler from merging or refetching पढ़ोs or ग_लिखोs. The
 * compiler is also क्रमbidden from reordering successive instances of
 * READ_ONCE and WRITE_ONCE, but only when the compiler is aware of some
 * particular ordering. One way to make the compiler aware of ordering is to
 * put the two invocations of READ_ONCE or WRITE_ONCE in dअगरferent C
 * statements.
 *
 * These two macros will also work on aggregate data types like काष्ठाs or
 * जोड़s. If the size of the accessed data type exceeds the word size of
 * the machine (e.g., 32 bits or 64 bits) READ_ONCE() and WRITE_ONCE() will
 * fall back to स_नकल and prपूर्णांक a compile-समय warning.
 *
 * Their two major use हालs are: (1) Mediating communication between
 * process-level code and irq/NMI handlers, all running on the same CPU,
 * and (2) Ensuring that the compiler करोes not fold, spindle, or otherwise
 * mutilate accesses that either करो not require ordering or that पूर्णांकeract
 * with an explicit memory barrier or atomic inकाष्ठाion that provides the
 * required ordering.
 */

#घोषणा READ_ONCE(x)					\
(अणु							\
	जोड़ अणु typeof(x) __val; अक्षर __c[1]; पूर्ण __u =	\
		अणु .__c = अणु 0 पूर्ण पूर्ण;			\
	__पढ़ो_once_size(&(x), __u.__c, माप(x));	\
	__u.__val;					\
पूर्ण)

#घोषणा WRITE_ONCE(x, val)				\
(अणु							\
	जोड़ अणु typeof(x) __val; अक्षर __c[1]; पूर्ण __u =	\
		अणु .__val = (val) पूर्ण; 			\
	__ग_लिखो_once_size(&(x), __u.__c, माप(x));	\
	__u.__val;					\
पूर्ण)


#अगर_अघोषित __fallthrough
# define __fallthrough
#पूर्ण_अगर

/* Indirect macros required क्रम expanded argument pasting, eg. __LINE__. */
#घोषणा ___PASTE(a, b) a##b
#घोषणा __PASTE(a, b) ___PASTE(a, b)

#पूर्ण_अगर /* _TOOLS_LINUX_COMPILER_H */
