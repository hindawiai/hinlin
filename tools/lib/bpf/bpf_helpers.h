<शैली गुरु>
/* SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause) */
#अगर_अघोषित __BPF_HELPERS__
#घोषणा __BPF_HELPERS__

/*
 * Note that bpf programs need to include either
 * vmlinux.h (स्वतः-generated from BTF) or linux/types.h
 * in advance since bpf_helper_defs.h uses such types
 * as __u64.
 */
#समावेश "bpf_helper_defs.h"

#घोषणा __uपूर्णांक(name, val) पूर्णांक (*name)[val]
#घोषणा __type(name, val) typeof(val) *name
#घोषणा __array(name, val) typeof(val) *name[]

/* Helper macro to prपूर्णांक out debug messages */
#घोषणा bpf_prपूर्णांकk(fmt, ...)				\
(अणु							\
	अक्षर ____fmt[] = fmt;				\
	bpf_trace_prपूर्णांकk(____fmt, माप(____fmt),	\
			 ##__VA_ARGS__);		\
पूर्ण)

/*
 * Helper macro to place programs, maps, license in
 * dअगरferent sections in elf_bpf file. Section names
 * are पूर्णांकerpreted by libbpf depending on the context (BPF programs, BPF maps,
 * बाह्य variables, etc).
 * To allow use of SEC() with बाह्यs (e.g., क्रम बाह्य .maps declarations),
 * make sure __attribute__((unused)) करोesn't trigger compilation warning.
 */
#घोषणा SEC(name) \
	_Pragma("GCC diagnostic push")					    \
	_Pragma("GCC diagnostic ignored \"-Wignored-attributes\"")	    \
	__attribute__((section(name), used))				    \
	_Pragma("GCC diagnostic pop")					    \

/* Aव्योम 'linux/stddef.h' definition of '__always_inline'. */
#अघोषित __always_अंतरभूत
#घोषणा __always_अंतरभूत अंतरभूत __attribute__((always_अंतरभूत))

#अगर_अघोषित __noअंतरभूत
#घोषणा __noअंतरभूत __attribute__((noअंतरभूत))
#पूर्ण_अगर
#अगर_अघोषित __weak
#घोषणा __weak __attribute__((weak))
#पूर्ण_अगर

/*
 * Use __hidden attribute to mark a non-अटल BPF subprogram effectively
 * अटल क्रम BPF verअगरier's verअगरication algorithm purposes, allowing more
 * extensive and permissive BPF verअगरication process, taking पूर्णांकo account
 * subprogram's caller context.
 */
#घोषणा __hidden __attribute__((visibility("hidden")))

/* When utilizing vmlinux.h with BPF CO-RE, user BPF programs can't include
 * any प्रणाली-level headers (such as मानकघोष.स, linux/version.h, etc), and
 * commonly-used macros like शून्य and KERNEL_VERSION aren't available through
 * vmlinux.h. This just adds unnecessary hurdles and क्रमces users to re-define
 * them on their own. So as a convenience, provide such definitions here.
 */
#अगर_अघोषित शून्य
#घोषणा शून्य ((व्योम *)0)
#पूर्ण_अगर

#अगर_अघोषित KERNEL_VERSION
#घोषणा KERNEL_VERSION(a, b, c) (((a) << 16) + ((b) << 8) + ((c) > 255 ? 255 : (c)))
#पूर्ण_अगर

/*
 * Helper macros to manipulate data काष्ठाures
 */
#अगर_अघोषित दुरत्व
#घोषणा दुरत्व(TYPE, MEMBER)	((अचिन्हित दीर्घ)&((TYPE *)0)->MEMBER)
#पूर्ण_अगर
#अगर_अघोषित container_of
#घोषणा container_of(ptr, type, member)				\
	(अणु							\
		व्योम *__mptr = (व्योम *)(ptr);			\
		((type *)(__mptr - दुरत्व(type, member)));	\
	पूर्ण)
#पूर्ण_अगर

/*
 * Helper macro to throw a compilation error अगर __bpf_unreachable() माला_लो
 * built पूर्णांकo the resulting code. This works given BPF back end करोes not
 * implement __builtin_trap(). This is useful to निश्चित that certain paths
 * of the program code are never used and hence eliminated by the compiler.
 *
 * For example, consider a चयन statement that covers known हालs used by
 * the program. __bpf_unreachable() can then reside in the शेष हाल. If
 * the program माला_लो extended such that a हाल is not covered in the चयन
 * statement, then it will throw a build error due to the शेष हाल not
 * being compiled out.
 */
#अगर_अघोषित __bpf_unreachable
# define __bpf_unreachable()	__builtin_trap()
#पूर्ण_अगर

/*
 * Helper function to perक्रमm a tail call with a स्थिरant/immediate map slot.
 */
#अगर __clang_major__ >= 8 && defined(__bpf__)
अटल __always_अंतरभूत व्योम
bpf_tail_call_अटल(व्योम *ctx, स्थिर व्योम *map, स्थिर __u32 slot)
अणु
	अगर (!__builtin_स्थिरant_p(slot))
		__bpf_unreachable();

	/*
	 * Provide a hard guarantee that LLVM won't optimize setting r2 (map
	 * poपूर्णांकer) and r3 (स्थिरant map index) from _dअगरferent paths_ ending
	 * up at the _same_ call insn as otherwise we won't be able to use the
	 * jmpq/nopl retpoline-मुक्त patching by the x86-64 JIT in the kernel
	 * given they mismatch. See also d2e4c1e6c294 ("bpf: Constant map key
	 * tracking क्रम prog array pokes") क्रम details on verअगरier tracking.
	 *
	 * Note on clobber list: we need to stay in-line with BPF calling
	 * convention, so even अगर we करोn't end up using r0, r4, r5, we need
	 * to mark them as clobber so that LLVM करोesn't end up using them
	 * beक्रमe / after the call.
	 */
	यंत्र अस्थिर("r1 = %[ctx]\n\t"
		     "r2 = %[map]\n\t"
		     "r3 = %[slot]\n\t"
		     "call 12"
		     :: [ctx]"r"(ctx), [map]"r"(map), [slot]"i"(slot)
		     : "r0", "r1", "r2", "r3", "r4", "r5");
पूर्ण
#पूर्ण_अगर

/*
 * Helper काष्ठाure used by eBPF C program
 * to describe BPF map attributes to libbpf loader
 */
काष्ठा bpf_map_def अणु
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक key_size;
	अचिन्हित पूर्णांक value_size;
	अचिन्हित पूर्णांक max_entries;
	अचिन्हित पूर्णांक map_flags;
पूर्ण;

क्रमागत libbpf_pin_type अणु
	LIBBPF_PIN_NONE,
	/* PIN_BY_NAME: pin maps by name (in /sys/fs/bpf by शेष) */
	LIBBPF_PIN_BY_NAME,
पूर्ण;

क्रमागत libbpf_tristate अणु
	TRI_NO = 0,
	TRI_YES = 1,
	TRI_MODULE = 2,
पूर्ण;

#घोषणा __kconfig __attribute__((section(".kconfig")))
#घोषणा __ksym __attribute__((section(".ksyms")))

#पूर्ण_अगर
