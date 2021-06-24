<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_COMPILER_TYPES_H
#घोषणा __LINUX_COMPILER_TYPES_H

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित __CHECKER__
/* address spaces */
# define __kernel	__attribute__((address_space(0)))
# define __user		__attribute__((noderef, address_space(__user)))
# define __iomem	__attribute__((noderef, address_space(__iomem)))
# define __percpu	__attribute__((noderef, address_space(__percpu)))
# define __rcu		__attribute__((noderef, address_space(__rcu)))
अटल अंतरभूत व्योम __chk_user_ptr(स्थिर अस्थिर व्योम __user *ptr) अणु पूर्ण
अटल अंतरभूत व्योम __chk_io_ptr(स्थिर अस्थिर व्योम __iomem *ptr) अणु पूर्ण
/* context/locking */
# define __must_hold(x)	__attribute__((context(x,1,1)))
# define __acquires(x)	__attribute__((context(x,0,1)))
# define __releases(x)	__attribute__((context(x,1,0)))
# define __acquire(x)	__context__(x,1)
# define __release(x)	__context__(x,-1)
# define __cond_lock(x,c)	((c) ? (अणु __acquire(x); 1; पूर्ण) : 0)
/* other */
# define __क्रमce	__attribute__((क्रमce))
# define __nocast	__attribute__((nocast))
# define __safe		__attribute__((safe))
# define __निजी	__attribute__((noderef))
# define ACCESS_PRIVATE(p, member) (*((typeof((p)->member) __क्रमce *) &(p)->member))
#अन्यथा /* __CHECKER__ */
/* address spaces */
# define __kernel
# अगरdef STRUCTLEAK_PLUGIN
#  define __user	__attribute__((user))
# अन्यथा
#  define __user
# endअगर
# define __iomem
# define __percpu
# define __rcu
# define __chk_user_ptr(x)	(व्योम)0
# define __chk_io_ptr(x)	(व्योम)0
/* context/locking */
# define __must_hold(x)
# define __acquires(x)
# define __releases(x)
# define __acquire(x)	(व्योम)0
# define __release(x)	(व्योम)0
# define __cond_lock(x,c) (c)
/* other */
# define __क्रमce
# define __nocast
# define __safe
# define __निजी
# define ACCESS_PRIVATE(p, member) ((p)->member)
# define __builtin_warning(x, y...) (1)
#पूर्ण_अगर /* __CHECKER__ */

/* Indirect macros required क्रम expanded argument pasting, eg. __LINE__. */
#घोषणा ___PASTE(a,b) a##b
#घोषणा __PASTE(a,b) ___PASTE(a,b)

#अगर_घोषित __KERNEL__

/* Attributes */
#समावेश <linux/compiler_attributes.h>

/* Builtins */

/*
 * __has_builtin is supported on gcc >= 10, clang >= 3 and icc >= 21.
 * In the meanसमय, to support gcc < 10, we implement __has_builtin
 * by hand.
 */
#अगर_अघोषित __has_builtin
#घोषणा __has_builtin(x) (0)
#पूर्ण_अगर

/* Compiler specअगरic macros. */
#अगर_घोषित __clang__
#समावेश <linux/compiler-clang.h>
#या_अगर defined(__INTEL_COMPILER)
#समावेश <linux/compiler-पूर्णांकel.h>
#या_अगर defined(__GNUC__)
/* The above compilers also define __GNUC__, so order is important here. */
#समावेश <linux/compiler-gcc.h>
#अन्यथा
#त्रुटि "Unknown compiler"
#पूर्ण_अगर

/*
 * Some architectures need to provide custom definitions of macros provided
 * by linux/compiler-*.h, and can करो so using यंत्र/compiler.h. We include that
 * conditionally rather than using an यंत्र-generic wrapper in order to aव्योम
 * build failures अगर any C compilation, which will include this file via an
 * -include argument in c_flags, occurs prior to the यंत्र-generic wrappers being
 * generated.
 */
#अगर_घोषित CONFIG_HAVE_ARCH_COMPILER_H
#समावेश <यंत्र/compiler.h>
#पूर्ण_अगर

काष्ठा ftrace_branch_data अणु
	स्थिर अक्षर *func;
	स्थिर अक्षर *file;
	अचिन्हित line;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ correct;
			अचिन्हित दीर्घ incorrect;
		पूर्ण;
		काष्ठा अणु
			अचिन्हित दीर्घ miss;
			अचिन्हित दीर्घ hit;
		पूर्ण;
		अचिन्हित दीर्घ miss_hit[2];
	पूर्ण;
पूर्ण;

काष्ठा ftrace_likely_data अणु
	काष्ठा ftrace_branch_data	data;
	अचिन्हित दीर्घ			स्थिरant;
पूर्ण;

#अगर defined(CC_USING_HOTPATCH)
#घोषणा notrace			__attribute__((hotpatch(0, 0)))
#या_अगर defined(CC_USING_PATCHABLE_FUNCTION_ENTRY)
#घोषणा notrace			__attribute__((patchable_function_entry(0, 0)))
#अन्यथा
#घोषणा notrace			__attribute__((__no_instrument_function__))
#पूर्ण_अगर

/*
 * it करोesn't make sense on ARM (currently the only user of __naked)
 * to trace naked functions because then mcount is called without
 * stack and frame poपूर्णांकer being set up and there is no chance to
 * restore the lr रेजिस्टर to the value beक्रमe mcount was called.
 */
#घोषणा __naked			__attribute__((__naked__)) notrace

#घोषणा __compiler_दुरत्व(a, b)	__builtin_दुरत्व(a, b)

/*
 * Prefer gnu_अंतरभूत, so that बाह्य अंतरभूत functions करो not emit an
 * बाह्यally visible function. This makes बाह्य अंतरभूत behave as per gnu89
 * semantics rather than c99. This prevents multiple symbol definition errors
 * of बाह्य अंतरभूत functions at link समय.
 * A lot of अंतरभूत functions can cause havoc with function tracing.
 */
#घोषणा अंतरभूत अंतरभूत __gnu_अंतरभूत __अंतरभूत_maybe_unused notrace

/*
 * gcc provides both __अंतरभूत__ and __अंतरभूत as alternate spellings of
 * the अंतरभूत keyword, though the latter is unकरोcumented. New kernel
 * code should only use the अंतरभूत spelling, but some existing code
 * uses __अंतरभूत__. Since we #घोषणा अंतरभूत above, to ensure
 * __अंतरभूत__ has the same semantics, we need this #घोषणा.
 *
 * However, the spelling __अंतरभूत is strictly reserved क्रम referring
 * to the bare keyword.
 */
#घोषणा __अंतरभूत__ अंतरभूत

/*
 * GCC करोes not warn about unused अटल अंतरभूत functions क्रम -Wunused-function.
 * Suppress the warning in clang as well by using __maybe_unused, but enable it
 * क्रम W=1 build. This will allow clang to find unused functions. Remove the
 * __अंतरभूत_maybe_unused entirely after fixing most of -Wunused-function warnings.
 */
#अगर_घोषित KBUILD_EXTRA_WARN1
#घोषणा __अंतरभूत_maybe_unused
#अन्यथा
#घोषणा __अंतरभूत_maybe_unused __maybe_unused
#पूर्ण_अगर

/*
 * Rather then using noअंतरभूत to prevent stack consumption, use
 * noअंतरभूत_क्रम_stack instead.  For करोcumentation reasons.
 */
#घोषणा noअंतरभूत_क्रम_stack noअंतरभूत

/*
 * Sanitizer helper attributes: Because using __always_अंतरभूत and
 * __no_sanitize_* conflict, provide helper attributes that will either expand
 * to __no_sanitize_* in compilation units where instrumentation is enabled
 * (__SANITIZE_*__), or __always_अंतरभूत in compilation units without
 * instrumentation (__SANITIZE_*__ undefined).
 */
#अगर_घोषित __SANITIZE_ADDRESS__
/*
 * We can't declare function 'inline' because __no_sanitize_address conflicts
 * with inlining. Attempt to अंतरभूत it may cause a build failure.
 *     https://gcc.gnu.org/bugzilla/show_bug.cgi?id=67368
 * '__maybe_unused' allows us to aव्योम defined-but-not-used warnings.
 */
# define __no_kasan_or_अंतरभूत __no_sanitize_address notrace __maybe_unused
# define __no_sanitize_or_अंतरभूत __no_kasan_or_अंतरभूत
#अन्यथा
# define __no_kasan_or_अंतरभूत __always_अंतरभूत
#पूर्ण_अगर

#घोषणा __no_kcsan __no_sanitize_thपढ़ो
#अगर_घोषित __SANITIZE_THREAD__
# define __no_sanitize_or_अंतरभूत __no_kcsan notrace __maybe_unused
#पूर्ण_अगर

#अगर_अघोषित __no_sanitize_or_अंतरभूत
#घोषणा __no_sanitize_or_अंतरभूत __always_अंतरभूत
#पूर्ण_अगर

/* Section क्रम code which can't be instrumented at all */
#घोषणा noinstr								\
	noअंतरभूत notrace __attribute((__section__(".noinstr.text")))	\
	__no_kcsan __no_sanitize_address

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * The below symbols may be defined क्रम one or more, but not ALL, of the above
 * compilers. We करोn't consider that to be an error, so set them to nothing.
 * For example, some of them are क्रम compiler specअगरic plugins.
 */
#अगर_अघोषित __latent_entropy
# define __latent_entropy
#पूर्ण_अगर

#अगर_अघोषित __अक्रमomize_layout
# define __अक्रमomize_layout __designated_init
#पूर्ण_अगर

#अगर_अघोषित __no_अक्रमomize_layout
# define __no_अक्रमomize_layout
#पूर्ण_अगर

#अगर_अघोषित अक्रमomized_काष्ठा_fields_start
# define अक्रमomized_काष्ठा_fields_start
# define अक्रमomized_काष्ठा_fields_end
#पूर्ण_अगर

#अगर_अघोषित __noscs
# define __noscs
#पूर्ण_अगर

#अगर_अघोषित __nocfi
# define __nocfi
#पूर्ण_अगर

#अगर_अघोषित __cficanonical
# define __cficanonical
#पूर्ण_अगर

#अगर_अघोषित यंत्र_अस्थिर_जाओ
#घोषणा यंत्र_अस्थिर_जाओ(x...) यंत्र जाओ(x)
#पूर्ण_अगर

#अगर_घोषित CONFIG_CC_HAS_ASM_INLINE
#घोषणा यंत्र_अंतरभूत यंत्र __अंतरभूत
#अन्यथा
#घोषणा यंत्र_अंतरभूत यंत्र
#पूर्ण_अगर

/* Are two types/vars the same type (ignoring qualअगरiers)? */
#घोषणा __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))

/*
 * __unqual_scalar_typeof(x) - Declare an unqualअगरied scalar type, leaving
 *			       non-scalar types unchanged.
 */
/*
 * Prefer C11 _Generic क्रम better compile-बार and simpler code. Note: 'char'
 * is not type-compatible with 'signed char', and we define a separate हाल.
 */
#घोषणा __scalar_type_to_expr_हालs(type)				\
		अचिन्हित type:	(अचिन्हित type)0,			\
		चिन्हित type:	(चिन्हित type)0

#घोषणा __unqual_scalar_typeof(x) typeof(				\
		_Generic((x),						\
			 अक्षर:	(अक्षर)0,				\
			 __scalar_type_to_expr_हालs(अक्षर),		\
			 __scalar_type_to_expr_हालs(लघु),		\
			 __scalar_type_to_expr_हालs(पूर्णांक),		\
			 __scalar_type_to_expr_हालs(दीर्घ),		\
			 __scalar_type_to_expr_हालs(दीर्घ दीर्घ),	\
			 शेष: (x)))

/* Is this type a native word size -- useful क्रम atomic operations */
#घोषणा __native_word(t) \
	(माप(t) == माप(अक्षर) || माप(t) == माप(लघु) || \
	 माप(t) == माप(पूर्णांक) || माप(t) == माप(दीर्घ))

/* Compile समय object size, -1 क्रम unknown */
#अगर_अघोषित __compileसमय_object_size
# define __compileसमय_object_size(obj) -1
#पूर्ण_अगर
#अगर_अघोषित __compileसमय_warning
# define __compileसमय_warning(message)
#पूर्ण_अगर
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

#घोषणा compileसमय_निश्चित_atomic_type(t)				\
	compileसमय_निश्चित(__native_word(t),				\
		"Need native word sized stores/loads for atomicity.")

/* Helpers क्रम emitting diagnostics in pragmas. */
#अगर_अघोषित __diag
#घोषणा __diag(string)
#पूर्ण_अगर

#अगर_अघोषित __diag_GCC
#घोषणा __diag_GCC(version, severity, string)
#पूर्ण_अगर

#घोषणा __diag_push()	__diag(push)
#घोषणा __diag_pop()	__diag(pop)

#घोषणा __diag_ignore(compiler, version, option, comment) \
	__diag_ ## compiler(version, ignore, option)
#घोषणा __diag_warn(compiler, version, option, comment) \
	__diag_ ## compiler(version, warn, option)
#घोषणा __diag_error(compiler, version, option, comment) \
	__diag_ ## compiler(version, error, option)

#पूर्ण_अगर /* __LINUX_COMPILER_TYPES_H */
