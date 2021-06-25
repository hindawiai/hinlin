<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_INIT_H
#घोषणा _LINUX_INIT_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

/* Built-in __init functions needn't be compiled with retpoline */
#अगर defined(__noretpoline) && !defined(MODULE)
#घोषणा __noinitretpoline __noretpoline
#अन्यथा
#घोषणा __noinitretpoline
#पूर्ण_अगर

/* These macros are used to mark some functions or 
 * initialized data (करोesn't apply to uninitialized data)
 * as `initialization' functions. The kernel can take this
 * as hपूर्णांक that the function is used only during the initialization
 * phase and मुक्त up used memory resources after
 *
 * Usage:
 * For functions:
 * 
 * You should add __init immediately beक्रमe the function name, like:
 *
 * अटल व्योम __init iniपंचांगe(पूर्णांक x, पूर्णांक y)
 * अणु
 *    बाह्य पूर्णांक z; z = x * y;
 * पूर्ण
 *
 * If the function has a prototype somewhere, you can also add
 * __init between closing brace of the prototype and semicolon:
 *
 * बाह्य पूर्णांक initialize_foobar_device(पूर्णांक, पूर्णांक, पूर्णांक) __init;
 *
 * For initialized data:
 * You should insert __initdata or __initस्थिर between the variable name
 * and equal sign followed by value, e.g.:
 *
 * अटल पूर्णांक init_variable __initdata = 0;
 * अटल स्थिर अक्षर linux_logo[] __initस्थिर = अणु 0x32, 0x36, ... पूर्ण;
 *
 * Don't क्रमget to initialize data not at file scope, i.e. within a function,
 * as gcc otherwise माला_दो the data पूर्णांकo the bss section and not पूर्णांकo the init
 * section.
 */

/* These are क्रम everybody (although not all archs will actually
   discard it in modules) */
#घोषणा __init		__section(".init.text") __cold  __latent_entropy __noinitretpoline __nocfi
#घोषणा __initdata	__section(".init.data")
#घोषणा __initस्थिर	__section(".init.rodata")
#घोषणा __निकासdata	__section(".exit.data")
#घोषणा __निकास_call	__used __section(".exitcall.exit")

/*
 * modpost check क्रम section mismatches during the kernel build.
 * A section mismatch happens when there are references from a
 * code or data section to an init section (both code or data).
 * The init sections are (क्रम most archs) discarded by the kernel
 * when early init has completed so all such references are potential bugs.
 * For निकास sections the same issue exists.
 *
 * The following markers are used क्रम the हालs where the reference to
 * the *init / *निकास section (code or data) is valid and will teach
 * modpost not to issue a warning.  Intended semantics is that a code or
 * data tagged __ref* can reference code or data from init section without
 * producing a warning (of course, no warning करोes not mean code is
 * correct, so optimally करोcument why the __ref is needed and why it's OK).
 *
 * The markers follow same syntax rules as __init / __initdata.
 */
#घोषणा __ref            __section(".ref.text") noअंतरभूत
#घोषणा __refdata        __section(".ref.data")
#घोषणा __refस्थिर       __section(".ref.rodata")

#अगर_घोषित MODULE
#घोषणा __निकासused
#अन्यथा
#घोषणा __निकासused  __used
#पूर्ण_अगर

#घोषणा __निकास          __section(".exit.text") __निकासused __cold notrace

/* Used क्रम MEMORY_HOTPLUG */
#घोषणा __meminit        __section(".meminit.text") __cold notrace \
						  __latent_entropy
#घोषणा __meminitdata    __section(".meminit.data")
#घोषणा __meminitस्थिर   __section(".meminit.rodata")
#घोषणा __memनिकास        __section(".memexit.text") __निकासused __cold notrace
#घोषणा __memनिकासdata    __section(".memexit.data")
#घोषणा __memनिकासस्थिर   __section(".memexit.rodata")

/* For assembly routines */
#घोषणा __HEAD		.section	".head.text","ax"
#घोषणा __INIT		.section	".init.text","ax"
#घोषणा __FINIT		.previous

#घोषणा __INITDATA	.section	".init.data","aw",%progbits
#घोषणा __INITRODATA	.section	".init.rodata","a",%progbits
#घोषणा __FINITDATA	.previous

#घोषणा __MEMINIT        .section	".meminit.text", "ax"
#घोषणा __MEMINITDATA    .section	".meminit.data", "aw"
#घोषणा __MEMINITRODATA  .section	".meminit.rodata", "a"

/* silence warnings when references are OK */
#घोषणा __REF            .section       ".ref.text", "ax"
#घोषणा __REFDATA        .section       ".ref.data", "aw"
#घोषणा __REFCONST       .section       ".ref.rodata", "a"

#अगर_अघोषित __ASSEMBLY__
/*
 * Used क्रम initialization calls..
 */
प्रकार पूर्णांक (*initcall_t)(व्योम);
प्रकार व्योम (*निकासcall_t)(व्योम);

#अगर_घोषित CONFIG_HAVE_ARCH_PREL32_RELOCATIONS
प्रकार पूर्णांक initcall_entry_t;

अटल अंतरभूत initcall_t initcall_from_entry(initcall_entry_t *entry)
अणु
	वापस offset_to_ptr(entry);
पूर्ण
#अन्यथा
प्रकार initcall_t initcall_entry_t;

अटल अंतरभूत initcall_t initcall_from_entry(initcall_entry_t *entry)
अणु
	वापस *entry;
पूर्ण
#पूर्ण_अगर

बाह्य initcall_entry_t __con_initcall_start[], __con_initcall_end[];

/* Used क्रम contructor calls. */
प्रकार व्योम (*ctor_fn_t)(व्योम);

काष्ठा file_प्रणाली_type;

/* Defined in init/मुख्य.c */
बाह्य पूर्णांक करो_one_initcall(initcall_t fn);
बाह्य अक्षर __initdata boot_command_line[];
बाह्य अक्षर *saved_command_line;
बाह्य अचिन्हित पूर्णांक reset_devices;

/* used by init/मुख्य.c */
व्योम setup_arch(अक्षर **);
व्योम prepare_namespace(व्योम);
व्योम __init init_rootfs(व्योम);
बाह्य काष्ठा file_प्रणाली_type rootfs_fs_type;

#अगर defined(CONFIG_STRICT_KERNEL_RWX) || defined(CONFIG_STRICT_MODULE_RWX)
बाह्य bool rodata_enabled;
#पूर्ण_अगर
#अगर_घोषित CONFIG_STRICT_KERNEL_RWX
व्योम mark_rodata_ro(व्योम);
#पूर्ण_अगर

बाह्य व्योम (*late_समय_init)(व्योम);

बाह्य bool initcall_debug;

#पूर्ण_अगर
  
#अगर_अघोषित MODULE

#अगर_अघोषित __ASSEMBLY__

/*
 * initcalls are now grouped by functionality पूर्णांकo separate
 * subsections. Ordering inside the subsections is determined
 * by link order. 
 * For backwards compatibility, initcall() माला_दो the call in 
 * the device init subsection.
 *
 * The `id' arg to __define_initcall() is needed so that multiple initcalls
 * can poपूर्णांक at the same handler without causing duplicate-symbol build errors.
 *
 * Initcalls are run by placing poपूर्णांकers in initcall sections that the
 * kernel iterates at runसमय. The linker can करो dead code / data elimination
 * and हटाओ that completely, so the initcall sections have to be marked
 * as KEEP() in the linker script.
 */

/* Format: <modname>__<counter>_<line>_<fn> */
#घोषणा __initcall_id(fn)					\
	__PASTE(__KBUILD_MODNAME,				\
	__PASTE(__,						\
	__PASTE(__COUNTER__,					\
	__PASTE(_,						\
	__PASTE(__LINE__,					\
	__PASTE(_, fn))))))

/* Format: __<prefix>__<iid><id> */
#घोषणा __initcall_name(prefix, __iid, id)			\
	__PASTE(__,						\
	__PASTE(prefix,						\
	__PASTE(__,						\
	__PASTE(__iid, id))))

#अगर_घोषित CONFIG_LTO_CLANG
/*
 * With LTO, the compiler करोesn't necessarily obey link order क्रम
 * initcalls. In order to preserve the correct order, we add each
 * variable पूर्णांकo its own section and generate a linker script (in
 * scripts/link-vmlinux.sh) to specअगरy the order of the sections.
 */
#घोषणा __initcall_section(__sec, __iid)			\
	#__sec ".init.." #__iid

/*
 * With LTO, the compiler can नाम अटल functions to aव्योम
 * global naming collisions. We use a global stub function क्रम
 * initcalls to create a stable symbol name whose address can be
 * taken in अंतरभूत assembly when PREL32 relocations are used.
 */
#घोषणा __initcall_stub(fn, __iid, id)				\
	__initcall_name(initstub, __iid, id)

#घोषणा __define_initcall_stub(__stub, fn)			\
	पूर्णांक __init __cficanonical __stub(व्योम);			\
	पूर्णांक __init __cficanonical __stub(व्योम)			\
	अणु 							\
		वापस fn();					\
	पूर्ण							\
	__ADDRESSABLE(__stub)
#अन्यथा
#घोषणा __initcall_section(__sec, __iid)			\
	#__sec ".init"

#घोषणा __initcall_stub(fn, __iid, id)	fn

#घोषणा __define_initcall_stub(__stub, fn)			\
	__ADDRESSABLE(fn)
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_ARCH_PREL32_RELOCATIONS
#घोषणा ____define_initcall(fn, __stub, __name, __sec)		\
	__define_initcall_stub(__stub, fn)			\
	यंत्र(".section	\"" __sec "\", \"a\"		\n"	\
	    __stringअगरy(__name) ":			\n"	\
	    ".long	" __stringअगरy(__stub) " - .	\n"	\
	    ".previous					\n");	\
	अटल_निश्चित(__same_type(initcall_t, &fn));
#अन्यथा
#घोषणा ____define_initcall(fn, __unused, __name, __sec)	\
	अटल initcall_t __name __used 			\
		__attribute__((__section__(__sec))) = fn;
#पूर्ण_अगर

#घोषणा __unique_initcall(fn, id, __sec, __iid)			\
	____define_initcall(fn,					\
		__initcall_stub(fn, __iid, id),			\
		__initcall_name(initcall, __iid, id),		\
		__initcall_section(__sec, __iid))

#घोषणा ___define_initcall(fn, id, __sec)			\
	__unique_initcall(fn, id, __sec, __initcall_id(fn))

#घोषणा __define_initcall(fn, id) ___define_initcall(fn, id, .initcall##id)

/*
 * Early initcalls run beक्रमe initializing SMP.
 *
 * Only क्रम built-in code, not modules.
 */
#घोषणा early_initcall(fn)		__define_initcall(fn, early)

/*
 * A "pure" initcall has no dependencies on anything अन्यथा, and purely
 * initializes variables that couldn't be अटलally initialized.
 *
 * This only exists क्रम built-in code, not क्रम modules.
 * Keep मुख्य.c:initcall_level_names[] in sync.
 */
#घोषणा pure_initcall(fn)		__define_initcall(fn, 0)

#घोषणा core_initcall(fn)		__define_initcall(fn, 1)
#घोषणा core_initcall_sync(fn)		__define_initcall(fn, 1s)
#घोषणा postcore_initcall(fn)		__define_initcall(fn, 2)
#घोषणा postcore_initcall_sync(fn)	__define_initcall(fn, 2s)
#घोषणा arch_initcall(fn)		__define_initcall(fn, 3)
#घोषणा arch_initcall_sync(fn)		__define_initcall(fn, 3s)
#घोषणा subsys_initcall(fn)		__define_initcall(fn, 4)
#घोषणा subsys_initcall_sync(fn)	__define_initcall(fn, 4s)
#घोषणा fs_initcall(fn)			__define_initcall(fn, 5)
#घोषणा fs_initcall_sync(fn)		__define_initcall(fn, 5s)
#घोषणा rootfs_initcall(fn)		__define_initcall(fn, rootfs)
#घोषणा device_initcall(fn)		__define_initcall(fn, 6)
#घोषणा device_initcall_sync(fn)	__define_initcall(fn, 6s)
#घोषणा late_initcall(fn)		__define_initcall(fn, 7)
#घोषणा late_initcall_sync(fn)		__define_initcall(fn, 7s)

#घोषणा __initcall(fn) device_initcall(fn)

#घोषणा __निकासcall(fn)						\
	अटल निकासcall_t __निकासcall_##fn __निकास_call = fn

#घोषणा console_initcall(fn)	___define_initcall(fn, con, .con_initcall)

काष्ठा obs_kernel_param अणु
	स्थिर अक्षर *str;
	पूर्णांक (*setup_func)(अक्षर *);
	पूर्णांक early;
पूर्ण;

/*
 * Only क्रम really core code.  See moduleparam.h क्रम the normal way.
 *
 * Force the alignment so the compiler करोesn't space elements of the
 * obs_kernel_param "array" too far apart in .init.setup.
 */
#घोषणा __setup_param(str, unique_id, fn, early)			\
	अटल स्थिर अक्षर __setup_str_##unique_id[] __initस्थिर		\
		__aligned(1) = str; 					\
	अटल काष्ठा obs_kernel_param __setup_##unique_id		\
		__used __section(".init.setup")				\
		__aligned(__alignof__(काष्ठा obs_kernel_param))		\
		= अणु __setup_str_##unique_id, fn, early पूर्ण

#घोषणा __setup(str, fn)						\
	__setup_param(str, fn, fn, 0)

/*
 * NOTE: fn is as per module_param, not __setup!
 * Emits warning अगर fn वापसs non-zero.
 */
#घोषणा early_param(str, fn)						\
	__setup_param(str, fn, fn, 1)

#घोषणा early_param_on_off(str_on, str_off, var, config)		\
									\
	पूर्णांक var = IS_ENABLED(config);					\
									\
	अटल पूर्णांक __init parse_##var##_on(अक्षर *arg)			\
	अणु								\
		var = 1;						\
		वापस 0;						\
	पूर्ण								\
	early_param(str_on, parse_##var##_on);				\
									\
	अटल पूर्णांक __init parse_##var##_off(अक्षर *arg)			\
	अणु								\
		var = 0;						\
		वापस 0;						\
	पूर्ण								\
	early_param(str_off, parse_##var##_off)

/* Relies on boot_command_line being set */
व्योम __init parse_early_param(व्योम);
व्योम __init parse_early_options(अक्षर *cmdline);
#पूर्ण_अगर /* __ASSEMBLY__ */

#अन्यथा /* MODULE */

#घोषणा __setup_param(str, unique_id, fn)	/* nothing */
#घोषणा __setup(str, func) 			/* nothing */
#पूर्ण_अगर

/* Data marked not to be saved by software suspend */
#घोषणा __nosavedata __section(".data..nosave")

#अगर_घोषित MODULE
#घोषणा __निकास_p(x) x
#अन्यथा
#घोषणा __निकास_p(x) शून्य
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_INIT_H */
