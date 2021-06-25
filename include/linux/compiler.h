<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_COMPILER_H
#घोषणा __LINUX_COMPILER_H

#समावेश <linux/compiler_types.h>

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित __KERNEL__

/*
 * Note: DISABLE_BRANCH_PROFILING can be used by special lowlevel code
 * to disable branch tracing on a per file basis.
 */
#अगर defined(CONFIG_TRACE_BRANCH_PROFILING) \
    && !defined(DISABLE_BRANCH_PROFILING) && !defined(__CHECKER__)
व्योम ftrace_likely_update(काष्ठा ftrace_likely_data *f, पूर्णांक val,
			  पूर्णांक expect, पूर्णांक is_स्थिरant);

#घोषणा likely_notrace(x)	__builtin_expect(!!(x), 1)
#घोषणा unlikely_notrace(x)	__builtin_expect(!!(x), 0)

#घोषणा __branch_check__(x, expect, is_स्थिरant) (अणु			\
			दीर्घ ______r;					\
			अटल काष्ठा ftrace_likely_data		\
				__aligned(4)				\
				__section("_ftrace_annotated_branch")	\
				______f = अणु				\
				.data.func = __func__,			\
				.data.file = __खाता__,			\
				.data.line = __LINE__,			\
			पूर्ण;						\
			______r = __builtin_expect(!!(x), expect);	\
			ftrace_likely_update(&______f, ______r,		\
					     expect, is_स्थिरant);	\
			______r;					\
		पूर्ण)

/*
 * Using __builtin_स्थिरant_p(x) to ignore हालs where the वापस
 * value is always the same.  This idea is taken from a similar patch
 * written by Daniel Walker.
 */
# अगरndef likely
#  define likely(x)	(__branch_check__(x, 1, __builtin_स्थिरant_p(x)))
# endअगर
# अगरndef unlikely
#  define unlikely(x)	(__branch_check__(x, 0, __builtin_स्थिरant_p(x)))
# endअगर

#अगर_घोषित CONFIG_PROखाता_ALL_BRANCHES
/*
 * "Define 'is'", Bill Clपूर्णांकon
 * "Define 'if'", Steven Rostedt
 */
#घोषणा अगर(cond, ...) अगर ( __trace_अगर_var( !!(cond , ## __VA_ARGS__) ) )

#घोषणा __trace_अगर_var(cond) (__builtin_स्थिरant_p(cond) ? (cond) : __trace_अगर_value(cond))

#घोषणा __trace_अगर_value(cond) (अणु			\
	अटल काष्ठा ftrace_branch_data		\
		__aligned(4)				\
		__section("_ftrace_branch")		\
		__अगर_trace = अणु				\
			.func = __func__,		\
			.file = __खाता__,		\
			.line = __LINE__,		\
		पूर्ण;					\
	(cond) ?					\
		(__अगर_trace.miss_hit[1]++,1) :		\
		(__अगर_trace.miss_hit[0]++,0);		\
पूर्ण)

#पूर्ण_अगर /* CONFIG_PROखाता_ALL_BRANCHES */

#अन्यथा
# define likely(x)	__builtin_expect(!!(x), 1)
# define unlikely(x)	__builtin_expect(!!(x), 0)
# define likely_notrace(x)	likely(x)
# define unlikely_notrace(x)	unlikely(x)
#पूर्ण_अगर

/* Optimization barrier */
#अगर_अघोषित barrier
/* The "volatile" is due to gcc bugs */
# define barrier() __यंत्र__ __अस्थिर__("": : :"memory")
#पूर्ण_अगर

#अगर_अघोषित barrier_data
/*
 * This version is i.e. to prevent dead stores elimination on @ptr
 * where gcc and llvm may behave dअगरferently when otherwise using
 * normal barrier(): जबतक gcc behavior माला_लो aदीर्घ with a normal
 * barrier(), llvm needs an explicit input variable to be assumed
 * clobbered. The issue is as follows: जबतक the अंतरभूत यंत्र might
 * access any memory it wants, the compiler could have fit all of
 * @ptr पूर्णांकo memory रेजिस्टरs instead, and since @ptr never escaped
 * from that, it proved that the अंतरभूत यंत्र wasn't touching any of
 * it. This version works well with both compilers, i.e. we're telling
 * the compiler that the अंतरभूत यंत्र असलolutely may see the contents
 * of @ptr. See also: https://llvm.org/bugs/show_bug.cgi?id=15495
 */
# define barrier_data(ptr) __यंत्र__ __अस्थिर__("": :"r"(ptr) :"memory")
#पूर्ण_अगर

/* workaround क्रम GCC PR82365 अगर needed */
#अगर_अघोषित barrier_beक्रमe_unreachable
# define barrier_beक्रमe_unreachable() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/* Unreachable code */
#अगर_घोषित CONFIG_STACK_VALIDATION
/*
 * These macros help objtool understand GCC code flow क्रम unreachable code.
 * The __COUNTER__ based labels are a hack to make each instance of the macros
 * unique, to convince GCC not to merge duplicate अंतरभूत यंत्र statements.
 */
#घोषणा annotate_reachable() (अणु						\
	यंत्र अस्थिर("%c0:\n\t"						\
		     ".pushsection .discard.reachable\n\t"		\
		     ".long %c0b - .\n\t"				\
		     ".popsection\n\t" : : "i" (__COUNTER__));		\
पूर्ण)
#घोषणा annotate_unreachable() (अणु					\
	यंत्र अस्थिर("%c0:\n\t"						\
		     ".pushsection .discard.unreachable\n\t"		\
		     ".long %c0b - .\n\t"				\
		     ".popsection\n\t" : : "i" (__COUNTER__));		\
पूर्ण)
#घोषणा ASM_UNREACHABLE							\
	"999:\n\t"							\
	".pushsection .discard.unreachable\n\t"				\
	".long 999b - .\n\t"						\
	".popsection\n\t"

/* Annotate a C jump table to allow objtool to follow the code flow */
#घोषणा __annotate_jump_table __section(".rodata..c_jump_table")

#अन्यथा
#घोषणा annotate_reachable()
#घोषणा annotate_unreachable()
#घोषणा __annotate_jump_table
#पूर्ण_अगर

#अगर_अघोषित ASM_UNREACHABLE
# define ASM_UNREACHABLE
#पूर्ण_अगर
#अगर_अघोषित unreachable
# define unreachable() करो अणु		\
	annotate_unreachable();		\
	__builtin_unreachable();	\
पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * KENTRY - kernel entry poपूर्णांक
 * This can be used to annotate symbols (functions or data) that are used
 * without their linker symbol being referenced explicitly. For example,
 * पूर्णांकerrupt vector handlers, or functions in the kernel image that are found
 * programatically.
 *
 * Not required क्रम symbols exported with EXPORT_SYMBOL, or initcalls. Those
 * are handled in their own way (with KEEP() in linker scripts).
 *
 * KENTRY can be aव्योमed अगर the symbols in question are marked as KEEP() in the
 * linker script. For example an architecture could KEEP() its entire
 * boot/exception vector code rather than annotate each function and data.
 */
#अगर_अघोषित KENTRY
# define KENTRY(sym)						\
	बाह्य typeof(sym) sym;					\
	अटल स्थिर अचिन्हित दीर्घ __kentry_##sym		\
	__used							\
	__attribute__((__section__("___kentry+" #sym)))		\
	= (अचिन्हित दीर्घ)&sym;
#पूर्ण_अगर

#अगर_अघोषित RELOC_HIDE
# define RELOC_HIDE(ptr, off)					\
  (अणु अचिन्हित दीर्घ __ptr;					\
     __ptr = (अचिन्हित दीर्घ) (ptr);				\
    (typeof(ptr)) (__ptr + (off)); पूर्ण)
#पूर्ण_अगर

#अगर_अघोषित OPTIMIZER_HIDE_VAR
/* Make the optimizer believe the variable can be manipulated arbitrarily. */
#घोषणा OPTIMIZER_HIDE_VAR(var)						\
	__यंत्र__ ("" : "=r" (var) : "0" (var))
#पूर्ण_अगर

/* Not-quite-unique ID. */
#अगर_अघोषित __UNIQUE_ID
# define __UNIQUE_ID(prefix) __PASTE(__PASTE(__UNIQUE_ID_, prefix), __LINE__)
#पूर्ण_अगर

/**
 * data_race - mark an expression as containing पूर्णांकentional data races
 *
 * This data_race() macro is useful क्रम situations in which data races
 * should be क्रमgiven.  One example is diagnostic code that accesses
 * shared variables but is not a part of the core synchronization design.
 *
 * This macro *करोes not* affect normal code generation, but is a hपूर्णांक
 * to tooling that data races here are to be ignored.
 */
#घोषणा data_race(expr)							\
(अणु									\
	__unqual_scalar_typeof((अणु expr; पूर्ण)) __v = (अणु			\
		__kcsan_disable_current();				\
		expr;							\
	पूर्ण);								\
	__kcsan_enable_current();					\
	__v;								\
पूर्ण)

#पूर्ण_अगर /* __KERNEL__ */

/*
 * Force the compiler to emit 'sym' as a symbol, so that we can reference
 * it from अंतरभूत assembler. Necessary in हाल 'sym' could be अंतरभूतd
 * otherwise, or eliminated entirely due to lack of references that are
 * visible to the compiler.
 */
#घोषणा __ADDRESSABLE(sym) \
	अटल व्योम * __section(".discard.addressable") __used \
		__UNIQUE_ID(__PASTE(__addressable_,sym)) = (व्योम *)&sym;

/**
 * offset_to_ptr - convert a relative memory offset to an असलolute poपूर्णांकer
 * @off:	the address of the 32-bit offset value
 */
अटल अंतरभूत व्योम *offset_to_ptr(स्थिर पूर्णांक *off)
अणु
	वापस (व्योम *)((अचिन्हित दीर्घ)off + *off);
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

/* &a[0] degrades to a poपूर्णांकer: a dअगरferent type from an array */
#घोषणा __must_be_array(a)	BUILD_BUG_ON_ZERO(__same_type((a), &(a)[0]))

/*
 * This is needed in functions which generate the stack canary, see
 * arch/x86/kernel/smpboot.c::start_secondary() क्रम an example.
 */
#घोषणा prevent_tail_call_optimization()	mb()

#समावेश <यंत्र/rwonce.h>

#पूर्ण_अगर /* __LINUX_COMPILER_H */
