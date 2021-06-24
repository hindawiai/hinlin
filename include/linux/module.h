<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Dynamic loading of modules पूर्णांकo the kernel.
 *
 * Rewritten by Riअक्षरd Henderson <rth@tamu.edu> Dec 1996
 * Rewritten again by Rusty Russell, 2002
 */

#अगर_अघोषित _LINUX_MODULE_H
#घोषणा _LINUX_MODULE_H

#समावेश <linux/list.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/compiler.h>
#समावेश <linux/cache.h>
#समावेश <linux/kmod.h>
#समावेश <linux/init.h>
#समावेश <linux/elf.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/kobject.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/export.h>
#समावेश <linux/rbtree_latch.h>
#समावेश <linux/error-injection.h>
#समावेश <linux/tracepoपूर्णांक-defs.h>
#समावेश <linux/srcu.h>
#समावेश <linux/अटल_call_types.h>
#समावेश <linux/cfi.h>

#समावेश <linux/percpu.h>
#समावेश <यंत्र/module.h>

#घोषणा MODULE_NAME_LEN MAX_PARAM_PREFIX_LEN

काष्ठा modversion_info अणु
	अचिन्हित दीर्घ crc;
	अक्षर name[MODULE_NAME_LEN];
पूर्ण;

काष्ठा module;
काष्ठा exception_table_entry;

काष्ठा module_kobject अणु
	काष्ठा kobject kobj;
	काष्ठा module *mod;
	काष्ठा kobject *drivers_dir;
	काष्ठा module_param_attrs *mp;
	काष्ठा completion *kobj_completion;
पूर्ण __अक्रमomize_layout;

काष्ठा module_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा module_attribute *, काष्ठा module_kobject *,
			अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा module_attribute *, काष्ठा module_kobject *,
			 स्थिर अक्षर *, माप_प्रकार count);
	व्योम (*setup)(काष्ठा module *, स्थिर अक्षर *);
	पूर्णांक (*test)(काष्ठा module *);
	व्योम (*मुक्त)(काष्ठा module *);
पूर्ण;

काष्ठा module_version_attribute अणु
	काष्ठा module_attribute mattr;
	स्थिर अक्षर *module_name;
	स्थिर अक्षर *version;
पूर्ण;

बाह्य sमाप_प्रकार __modver_version_show(काष्ठा module_attribute *,
				     काष्ठा module_kobject *, अक्षर *);

बाह्य काष्ठा module_attribute module_uevent;

/* These are either module local, or the kernel's dummy ones. */
बाह्य पूर्णांक init_module(व्योम);
बाह्य व्योम cleanup_module(व्योम);

#अगर_अघोषित MODULE
/**
 * module_init() - driver initialization entry poपूर्णांक
 * @x: function to be run at kernel boot समय or module insertion
 *
 * module_init() will either be called during करो_initcalls() (अगर
 * builtin) or at module insertion समय (अगर a module).  There can only
 * be one per module.
 */
#घोषणा module_init(x)	__initcall(x);

/**
 * module_निकास() - driver निकास entry poपूर्णांक
 * @x: function to be run when driver is हटाओd
 *
 * module_निकास() will wrap the driver clean-up code
 * with cleanup_module() when used with rmmod when
 * the driver is a module.  If the driver is अटलally
 * compiled पूर्णांकo the kernel, module_निकास() has no effect.
 * There can only be one per module.
 */
#घोषणा module_निकास(x)	__निकासcall(x);

#अन्यथा /* MODULE */

/*
 * In most हालs loadable modules करो not need custom
 * initcall levels. There are still some valid हालs where
 * a driver may be needed early अगर built in, and करोes not
 * matter when built as a loadable module. Like bus
 * snooping debug drivers.
 */
#घोषणा early_initcall(fn)		module_init(fn)
#घोषणा core_initcall(fn)		module_init(fn)
#घोषणा core_initcall_sync(fn)		module_init(fn)
#घोषणा postcore_initcall(fn)		module_init(fn)
#घोषणा postcore_initcall_sync(fn)	module_init(fn)
#घोषणा arch_initcall(fn)		module_init(fn)
#घोषणा subsys_initcall(fn)		module_init(fn)
#घोषणा subsys_initcall_sync(fn)	module_init(fn)
#घोषणा fs_initcall(fn)			module_init(fn)
#घोषणा fs_initcall_sync(fn)		module_init(fn)
#घोषणा rootfs_initcall(fn)		module_init(fn)
#घोषणा device_initcall(fn)		module_init(fn)
#घोषणा device_initcall_sync(fn)	module_init(fn)
#घोषणा late_initcall(fn)		module_init(fn)
#घोषणा late_initcall_sync(fn)		module_init(fn)

#घोषणा console_initcall(fn)		module_init(fn)

/* Each module must use one module_init(). */
#घोषणा module_init(initfn)					\
	अटल अंतरभूत initcall_t __maybe_unused __inittest(व्योम)		\
	अणु वापस initfn; पूर्ण					\
	पूर्णांक init_module(व्योम) __copy(initfn)			\
		__attribute__((alias(#initfn)));		\
	__CFI_ADDRESSABLE(init_module, __initdata);

/* This is only required अगर you want to be unloadable. */
#घोषणा module_निकास(निकासfn)					\
	अटल अंतरभूत निकासcall_t __maybe_unused __निकासtest(व्योम)		\
	अणु वापस निकासfn; पूर्ण					\
	व्योम cleanup_module(व्योम) __copy(निकासfn)		\
		__attribute__((alias(#निकासfn)));		\
	__CFI_ADDRESSABLE(cleanup_module, __निकासdata);

#पूर्ण_अगर

/* This means "can be init अगर no module support, otherwise module load
   may call it." */
#अगर_घोषित CONFIG_MODULES
#घोषणा __init_or_module
#घोषणा __initdata_or_module
#घोषणा __initस्थिर_or_module
#घोषणा __INIT_OR_MODULE	.text
#घोषणा __INITDATA_OR_MODULE	.data
#घोषणा __INITRODATA_OR_MODULE	.section ".rodata","a",%progbits
#अन्यथा
#घोषणा __init_or_module __init
#घोषणा __initdata_or_module __initdata
#घोषणा __initस्थिर_or_module __initस्थिर
#घोषणा __INIT_OR_MODULE __INIT
#घोषणा __INITDATA_OR_MODULE __INITDATA
#घोषणा __INITRODATA_OR_MODULE __INITRODATA
#पूर्ण_अगर /*CONFIG_MODULES*/

/* Generic info of क्रमm tag = "info" */
#घोषणा MODULE_INFO(tag, info) __MODULE_INFO(tag, tag, info)

/* For userspace: you can also call me... */
#घोषणा MODULE_ALIAS(_alias) MODULE_INFO(alias, _alias)

/* Soft module dependencies. See man modprobe.d क्रम details.
 * Example: MODULE_SOFTDEP("pre: module-foo module-bar post: module-baz")
 */
#घोषणा MODULE_SOFTDEP(_softdep) MODULE_INFO(softdep, _softdep)

/*
 * MODULE_खाता is used क्रम generating modules.builtin
 * So, make it no-op when this is being built as a module
 */
#अगर_घोषित MODULE
#घोषणा MODULE_खाता
#अन्यथा
#घोषणा MODULE_खाता	MODULE_INFO(file, KBUILD_MODखाता);
#पूर्ण_अगर

/*
 * The following license idents are currently accepted as indicating मुक्त
 * software modules
 *
 *	"GPL"				[GNU Public License v2]
 *	"GPL v2"			[GNU Public License v2]
 *	"GPL and additional rights"	[GNU Public License v2 rights and more]
 *	"Dual BSD/GPL"			[GNU Public License v2
 *					 or BSD license choice]
 *	"Dual MIT/GPL"			[GNU Public License v2
 *					 or MIT license choice]
 *	"Dual MPL/GPL"			[GNU Public License v2
 *					 or Mozilla license choice]
 *
 * The following other idents are available
 *
 *	"Proprietary"			[Non मुक्त products]
 *
 * Both "GPL v2" and "GPL" (the latter also in dual licensed strings) are
 * merely stating that the module is licensed under the GPL v2, but are not
 * telling whether "GPL v2 only" or "GPL v2 or later". The reason why there
 * are two variants is a historic and failed attempt to convey more
 * inक्रमmation in the MODULE_LICENSE string. For module loading the
 * "only/or later" distinction is completely irrelevant and करोes neither
 * replace the proper license identअगरiers in the corresponding source file
 * nor amends them in any way. The sole purpose is to make the
 * 'Proprietary' flagging work and to refuse to bind symbols which are
 * exported with EXPORT_SYMBOL_GPL when a non मुक्त module is loaded.
 *
 * In the same way "BSD" is not a clear license inक्रमmation. It merely
 * states, that the module is licensed under one of the compatible BSD
 * license variants. The detailed and correct license inक्रमmation is again
 * to be found in the corresponding source files.
 *
 * There are dual licensed components, but when running with Linux it is the
 * GPL that is relevant so this is a non issue. Similarly LGPL linked with GPL
 * is a GPL combined work.
 *
 * This exists क्रम several reasons
 * 1.	So modinfo can show license info क्रम users wanting to vet their setup
 *	is मुक्त
 * 2.	So the community can ignore bug reports including proprietary modules
 * 3.	So venकरोrs can करो likewise based on their own policies
 */
#घोषणा MODULE_LICENSE(_license) MODULE_खाता MODULE_INFO(license, _license)

/*
 * Author(s), use "Name <email>" or just "Name", क्रम multiple
 * authors use multiple MODULE_AUTHOR() statements/lines.
 */
#घोषणा MODULE_AUTHOR(_author) MODULE_INFO(author, _author)

/* What your module करोes. */
#घोषणा MODULE_DESCRIPTION(_description) MODULE_INFO(description, _description)

#अगर_घोषित MODULE
/* Creates an alias so file2alias.c can find device table. */
#घोषणा MODULE_DEVICE_TABLE(type, name)					\
बाह्य typeof(name) __mod_##type##__##name##_device_table		\
  __attribute__ ((unused, alias(__stringअगरy(name))))
#अन्यथा  /* !MODULE */
#घोषणा MODULE_DEVICE_TABLE(type, name)
#पूर्ण_अगर

/* Version of क्रमm [<epoch>:]<version>[-<extra-version>].
 * Or क्रम CVS/RCS ID version, everything but the number is stripped.
 * <epoch>: A (small) अचिन्हित पूर्णांकeger which allows you to start versions
 * anew. If not mentioned, it's zero.  eg. "2:1.0" is after
 * "1:2.0".

 * <version>: The <version> may contain only alphanumerics and the
 * अक्षरacter `.'.  Ordered by numeric sort क्रम numeric parts,
 * ascii sort क्रम ascii parts (as per RPM or DEB algorithm).

 * <extraversion>: Like <version>, but inserted क्रम local
 * customizations, eg "rh3" or "rusty1".

 * Using this स्वतःmatically adds a checksum of the .c files and the
 * local headers in "srcversion".
 */

#अगर defined(MODULE) || !defined(CONFIG_SYSFS)
#घोषणा MODULE_VERSION(_version) MODULE_INFO(version, _version)
#अन्यथा
#घोषणा MODULE_VERSION(_version)					\
	MODULE_INFO(version, _version);					\
	अटल काष्ठा module_version_attribute __modver_attr		\
		__used __section("__modver")				\
		__aligned(__alignof__(काष्ठा module_version_attribute)) \
		= अणु							\
			.mattr	= अणु					\
				.attr	= अणु				\
					.name	= "version",		\
					.mode	= S_IRUGO,		\
				पूर्ण,					\
				.show	= __modver_version_show,	\
			पूर्ण,						\
			.module_name	= KBUILD_MODNAME,		\
			.version	= _version,			\
		पूर्ण
#पूर्ण_अगर

/* Optional firmware file (or files) needed by the module
 * क्रमmat is simply firmware file name.  Multiple firmware
 * files require multiple MODULE_FIRMWARE() specअगरiers */
#घोषणा MODULE_FIRMWARE(_firmware) MODULE_INFO(firmware, _firmware)

#घोषणा MODULE_IMPORT_NS(ns) MODULE_INFO(import_ns, #ns)

काष्ठा notअगरier_block;

#अगर_घोषित CONFIG_MODULES

बाह्य पूर्णांक modules_disabled; /* क्रम sysctl */
/* Get/put a kernel symbol (calls must be symmetric) */
व्योम *__symbol_get(स्थिर अक्षर *symbol);
व्योम *__symbol_get_gpl(स्थिर अक्षर *symbol);
#घोषणा symbol_get(x) ((typeof(&x))(__symbol_get(__stringअगरy(x))))

/* modules using other modules: kdb wants to see this. */
काष्ठा module_use अणु
	काष्ठा list_head source_list;
	काष्ठा list_head target_list;
	काष्ठा module *source, *target;
पूर्ण;

क्रमागत module_state अणु
	MODULE_STATE_LIVE,	/* Normal state. */
	MODULE_STATE_COMING,	/* Full क्रमmed, running module_init. */
	MODULE_STATE_GOING,	/* Going away. */
	MODULE_STATE_UNFORMED,	/* Still setting it up. */
पूर्ण;

काष्ठा mod_tree_node अणु
	काष्ठा module *mod;
	काष्ठा latch_tree_node node;
पूर्ण;

काष्ठा module_layout अणु
	/* The actual code + data. */
	व्योम *base;
	/* Total size. */
	अचिन्हित पूर्णांक size;
	/* The size of the executable code.  */
	अचिन्हित पूर्णांक text_size;
	/* Size of RO section of the module (text+rodata) */
	अचिन्हित पूर्णांक ro_size;
	/* Size of RO after init section */
	अचिन्हित पूर्णांक ro_after_init_size;

#अगर_घोषित CONFIG_MODULES_TREE_LOOKUP
	काष्ठा mod_tree_node mtn;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_MODULES_TREE_LOOKUP
/* Only touch one cacheline क्रम common rbtree-क्रम-core-layout हाल. */
#घोषणा __module_layout_align ____cacheline_aligned
#अन्यथा
#घोषणा __module_layout_align
#पूर्ण_अगर

काष्ठा mod_kallsyms अणु
	Elf_Sym *symtab;
	अचिन्हित पूर्णांक num_symtab;
	अक्षर *strtab;
	अक्षर *typetab;
पूर्ण;

#अगर_घोषित CONFIG_LIVEPATCH
काष्ठा klp_modinfo अणु
	Elf_Ehdr hdr;
	Elf_Shdr *sechdrs;
	अक्षर *secstrings;
	अचिन्हित पूर्णांक symndx;
पूर्ण;
#पूर्ण_अगर

काष्ठा module अणु
	क्रमागत module_state state;

	/* Member of list of modules */
	काष्ठा list_head list;

	/* Unique handle क्रम this module */
	अक्षर name[MODULE_NAME_LEN];

	/* Sysfs stuff. */
	काष्ठा module_kobject mkobj;
	काष्ठा module_attribute *modinfo_attrs;
	स्थिर अक्षर *version;
	स्थिर अक्षर *srcversion;
	काष्ठा kobject *holders_dir;

	/* Exported symbols */
	स्थिर काष्ठा kernel_symbol *syms;
	स्थिर s32 *crcs;
	अचिन्हित पूर्णांक num_syms;

#अगर_घोषित CONFIG_CFI_CLANG
	cfi_check_fn cfi_check;
#पूर्ण_अगर

	/* Kernel parameters. */
#अगर_घोषित CONFIG_SYSFS
	काष्ठा mutex param_lock;
#पूर्ण_अगर
	काष्ठा kernel_param *kp;
	अचिन्हित पूर्णांक num_kp;

	/* GPL-only exported symbols. */
	अचिन्हित पूर्णांक num_gpl_syms;
	स्थिर काष्ठा kernel_symbol *gpl_syms;
	स्थिर s32 *gpl_crcs;
	bool using_gplonly_symbols;

#अगर_घोषित CONFIG_MODULE_SIG
	/* Signature was verअगरied. */
	bool sig_ok;
#पूर्ण_अगर

	bool async_probe_requested;

	/* Exception table */
	अचिन्हित पूर्णांक num_exentries;
	काष्ठा exception_table_entry *extable;

	/* Startup function. */
	पूर्णांक (*init)(व्योम);

	/* Core layout: rbtree is accessed frequently, so keep together. */
	काष्ठा module_layout core_layout __module_layout_align;
	काष्ठा module_layout init_layout;

	/* Arch-specअगरic module values */
	काष्ठा mod_arch_specअगरic arch;

	अचिन्हित दीर्घ taपूर्णांकs;	/* same bits as kernel:taपूर्णांक_flags */

#अगर_घोषित CONFIG_GENERIC_BUG
	/* Support क्रम BUG */
	अचिन्हित num_bugs;
	काष्ठा list_head bug_list;
	काष्ठा bug_entry *bug_table;
#पूर्ण_अगर

#अगर_घोषित CONFIG_KALLSYMS
	/* Protected by RCU and/or module_mutex: use rcu_dereference() */
	काष्ठा mod_kallsyms __rcu *kallsyms;
	काष्ठा mod_kallsyms core_kallsyms;

	/* Section attributes */
	काष्ठा module_sect_attrs *sect_attrs;

	/* Notes attributes */
	काष्ठा module_notes_attrs *notes_attrs;
#पूर्ण_अगर

	/* The command line arguments (may be mangled).  People like
	   keeping poपूर्णांकers to this stuff */
	अक्षर *args;

#अगर_घोषित CONFIG_SMP
	/* Per-cpu data. */
	व्योम __percpu *percpu;
	अचिन्हित पूर्णांक percpu_size;
#पूर्ण_अगर
	व्योम *noinstr_text_start;
	अचिन्हित पूर्णांक noinstr_text_size;

#अगर_घोषित CONFIG_TRACEPOINTS
	अचिन्हित पूर्णांक num_tracepoपूर्णांकs;
	tracepoपूर्णांक_ptr_t *tracepoपूर्णांकs_ptrs;
#पूर्ण_अगर
#अगर_घोषित CONFIG_TREE_SRCU
	अचिन्हित पूर्णांक num_srcu_काष्ठाs;
	काष्ठा srcu_काष्ठा **srcu_काष्ठा_ptrs;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BPF_EVENTS
	अचिन्हित पूर्णांक num_bpf_raw_events;
	काष्ठा bpf_raw_event_map *bpf_raw_events;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_INFO_BTF_MODULES
	अचिन्हित पूर्णांक btf_data_size;
	व्योम *btf_data;
#पूर्ण_अगर
#अगर_घोषित CONFIG_JUMP_LABEL
	काष्ठा jump_entry *jump_entries;
	अचिन्हित पूर्णांक num_jump_entries;
#पूर्ण_अगर
#अगर_घोषित CONFIG_TRACING
	अचिन्हित पूर्णांक num_trace_bprपूर्णांकk_fmt;
	स्थिर अक्षर **trace_bprपूर्णांकk_fmt_start;
#पूर्ण_अगर
#अगर_घोषित CONFIG_EVENT_TRACING
	काष्ठा trace_event_call **trace_events;
	अचिन्हित पूर्णांक num_trace_events;
	काष्ठा trace_eval_map **trace_evals;
	अचिन्हित पूर्णांक num_trace_evals;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FTRACE_MCOUNT_RECORD
	अचिन्हित पूर्णांक num_ftrace_callsites;
	अचिन्हित दीर्घ *ftrace_callsites;
#पूर्ण_अगर
#अगर_घोषित CONFIG_KPROBES
	व्योम *kprobes_text_start;
	अचिन्हित पूर्णांक kprobes_text_size;
	अचिन्हित दीर्घ *kprobe_blacklist;
	अचिन्हित पूर्णांक num_kprobe_blacklist;
#पूर्ण_अगर
#अगर_घोषित CONFIG_HAVE_STATIC_CALL_INLINE
	पूर्णांक num_अटल_call_sites;
	काष्ठा अटल_call_site *अटल_call_sites;
#पूर्ण_अगर

#अगर_घोषित CONFIG_LIVEPATCH
	bool klp; /* Is this a livepatch module? */
	bool klp_alive;

	/* Elf inक्रमmation */
	काष्ठा klp_modinfo *klp_info;
#पूर्ण_अगर

#अगर_घोषित CONFIG_MODULE_UNLOAD
	/* What modules depend on me? */
	काष्ठा list_head source_list;
	/* What modules करो I depend on? */
	काष्ठा list_head target_list;

	/* Deकाष्ठाion function. */
	व्योम (*निकास)(व्योम);

	atomic_t refcnt;
#पूर्ण_अगर

#अगर_घोषित CONFIG_CONSTRUCTORS
	/* Conकाष्ठाor functions. */
	ctor_fn_t *ctors;
	अचिन्हित पूर्णांक num_ctors;
#पूर्ण_अगर

#अगर_घोषित CONFIG_FUNCTION_ERROR_INJECTION
	काष्ठा error_injection_entry *ei_funcs;
	अचिन्हित पूर्णांक num_ei_funcs;
#पूर्ण_अगर
पूर्ण ____cacheline_aligned __अक्रमomize_layout;
#अगर_अघोषित MODULE_ARCH_INIT
#घोषणा MODULE_ARCH_INIT अणुपूर्ण
#पूर्ण_अगर

#अगर_अघोषित HAVE_ARCH_KALLSYMS_SYMBOL_VALUE
अटल अंतरभूत अचिन्हित दीर्घ kallsyms_symbol_value(स्थिर Elf_Sym *sym)
अणु
	वापस sym->st_value;
पूर्ण
#पूर्ण_अगर

/* FIXME: It'd be nice to isolate modules during init, too, so they
   aren't used beक्रमe they (may) fail.  But presently too much code
   (IDE & SCSI) require entry पूर्णांकo the module during init.*/
अटल अंतरभूत bool module_is_live(काष्ठा module *mod)
अणु
	वापस mod->state != MODULE_STATE_GOING;
पूर्ण

काष्ठा module *__module_text_address(अचिन्हित दीर्घ addr);
काष्ठा module *__module_address(अचिन्हित दीर्घ addr);
bool is_module_address(अचिन्हित दीर्घ addr);
bool __is_module_percpu_address(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *can_addr);
bool is_module_percpu_address(अचिन्हित दीर्घ addr);
bool is_module_text_address(अचिन्हित दीर्घ addr);

अटल अंतरभूत bool within_module_core(अचिन्हित दीर्घ addr,
				      स्थिर काष्ठा module *mod)
अणु
	वापस (अचिन्हित दीर्घ)mod->core_layout.base <= addr &&
	       addr < (अचिन्हित दीर्घ)mod->core_layout.base + mod->core_layout.size;
पूर्ण

अटल अंतरभूत bool within_module_init(अचिन्हित दीर्घ addr,
				      स्थिर काष्ठा module *mod)
अणु
	वापस (अचिन्हित दीर्घ)mod->init_layout.base <= addr &&
	       addr < (अचिन्हित दीर्घ)mod->init_layout.base + mod->init_layout.size;
पूर्ण

अटल अंतरभूत bool within_module(अचिन्हित दीर्घ addr, स्थिर काष्ठा module *mod)
अणु
	वापस within_module_init(addr, mod) || within_module_core(addr, mod);
पूर्ण

/* Search क्रम module by name: must be in a RCU-sched critical section. */
काष्ठा module *find_module(स्थिर अक्षर *name);

/* Returns 0 and fills in value, defined and namebuf, or -दुस्फल अगर
   symnum out of range. */
पूर्णांक module_get_kallsym(अचिन्हित पूर्णांक symnum, अचिन्हित दीर्घ *value, अक्षर *type,
			अक्षर *name, अक्षर *module_name, पूर्णांक *exported);

/* Look क्रम this name: can be of क्रमm module:name. */
अचिन्हित दीर्घ module_kallsyms_lookup_name(स्थिर अक्षर *name);

बाह्य व्योम __noवापस __module_put_and_निकास(काष्ठा module *mod,
			दीर्घ code);
#घोषणा module_put_and_निकास(code) __module_put_and_निकास(THIS_MODULE, code)

#अगर_घोषित CONFIG_MODULE_UNLOAD
पूर्णांक module_refcount(काष्ठा module *mod);
व्योम __symbol_put(स्थिर अक्षर *symbol);
#घोषणा symbol_put(x) __symbol_put(__stringअगरy(x))
व्योम symbol_put_addr(व्योम *addr);

/* Someबार we know we alपढ़ोy have a refcount, and it's easier not
   to handle the error हाल (which only happens with rmmod --रुको). */
बाह्य व्योम __module_get(काष्ठा module *module);

/* This is the Right Way to get a module: अगर it fails, it's being हटाओd,
 * so pretend it's not there. */
बाह्य bool try_module_get(काष्ठा module *module);

बाह्य व्योम module_put(काष्ठा module *module);

#अन्यथा /*!CONFIG_MODULE_UNLOAD*/
अटल अंतरभूत bool try_module_get(काष्ठा module *module)
अणु
	वापस !module || module_is_live(module);
पूर्ण
अटल अंतरभूत व्योम module_put(काष्ठा module *module)
अणु
पूर्ण
अटल अंतरभूत व्योम __module_get(काष्ठा module *module)
अणु
पूर्ण
#घोषणा symbol_put(x) करो अणु पूर्ण जबतक (0)
#घोषणा symbol_put_addr(p) करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_MODULE_UNLOAD */

/* This is a #घोषणा so the string करोesn't get put in every .o file */
#घोषणा module_name(mod)			\
(अणु						\
	काष्ठा module *__mod = (mod);		\
	__mod ? __mod->name : "kernel";		\
पूर्ण)

/* Dereference module function descriptor */
व्योम *dereference_module_function_descriptor(काष्ठा module *mod, व्योम *ptr);

/* For kallsyms to ask क्रम address resolution.  namebuf should be at
 * least KSYM_NAME_LEN दीर्घ: a poपूर्णांकer to namebuf is वापसed अगर
 * found, otherwise शून्य. */
स्थिर अक्षर *module_address_lookup(अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ *symbolsize,
			    अचिन्हित दीर्घ *offset,
			    अक्षर **modname,
			    अक्षर *namebuf);
पूर्णांक lookup_module_symbol_name(अचिन्हित दीर्घ addr, अक्षर *symname);
पूर्णांक lookup_module_symbol_attrs(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *size, अचिन्हित दीर्घ *offset, अक्षर *modname, अक्षर *name);

पूर्णांक रेजिस्टर_module_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक unरेजिस्टर_module_notअगरier(काष्ठा notअगरier_block *nb);

बाह्य व्योम prपूर्णांक_modules(व्योम);

अटल अंतरभूत bool module_requested_async_probing(काष्ठा module *module)
अणु
	वापस module && module->async_probe_requested;
पूर्ण

#अगर_घोषित CONFIG_LIVEPATCH
अटल अंतरभूत bool is_livepatch_module(काष्ठा module *mod)
अणु
	वापस mod->klp;
पूर्ण
#अन्यथा /* !CONFIG_LIVEPATCH */
अटल अंतरभूत bool is_livepatch_module(काष्ठा module *mod)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_LIVEPATCH */

bool is_module_sig_enक्रमced(व्योम);
व्योम set_module_sig_enक्रमced(व्योम);

#अन्यथा /* !CONFIG_MODULES... */

अटल अंतरभूत काष्ठा module *__module_address(अचिन्हित दीर्घ addr)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा module *__module_text_address(अचिन्हित दीर्घ addr)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool is_module_address(अचिन्हित दीर्घ addr)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool is_module_percpu_address(अचिन्हित दीर्घ addr)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool __is_module_percpu_address(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *can_addr)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool is_module_text_address(अचिन्हित दीर्घ addr)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool within_module_core(अचिन्हित दीर्घ addr,
				      स्थिर काष्ठा module *mod)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool within_module_init(अचिन्हित दीर्घ addr,
				      स्थिर काष्ठा module *mod)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool within_module(अचिन्हित दीर्घ addr, स्थिर काष्ठा module *mod)
अणु
	वापस false;
पूर्ण

/* Get/put a kernel symbol (calls should be symmetric) */
#घोषणा symbol_get(x) (अणु बाह्य typeof(x) x __attribute__((weak,visibility("hidden"))); &(x); पूर्ण)
#घोषणा symbol_put(x) करो अणु पूर्ण जबतक (0)
#घोषणा symbol_put_addr(x) करो अणु पूर्ण जबतक (0)

अटल अंतरभूत व्योम __module_get(काष्ठा module *module)
अणु
पूर्ण

अटल अंतरभूत bool try_module_get(काष्ठा module *module)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम module_put(काष्ठा module *module)
अणु
पूर्ण

#घोषणा module_name(mod) "kernel"

/* For kallsyms to ask क्रम address resolution.  शून्य means not found. */
अटल अंतरभूत स्थिर अक्षर *module_address_lookup(अचिन्हित दीर्घ addr,
					  अचिन्हित दीर्घ *symbolsize,
					  अचिन्हित दीर्घ *offset,
					  अक्षर **modname,
					  अक्षर *namebuf)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक lookup_module_symbol_name(अचिन्हित दीर्घ addr, अक्षर *symname)
अणु
	वापस -दुस्फल;
पूर्ण

अटल अंतरभूत पूर्णांक lookup_module_symbol_attrs(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *size, अचिन्हित दीर्घ *offset, अक्षर *modname, अक्षर *name)
अणु
	वापस -दुस्फल;
पूर्ण

अटल अंतरभूत पूर्णांक module_get_kallsym(अचिन्हित पूर्णांक symnum, अचिन्हित दीर्घ *value,
					अक्षर *type, अक्षर *name,
					अक्षर *module_name, पूर्णांक *exported)
अणु
	वापस -दुस्फल;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ module_kallsyms_lookup_name(स्थिर अक्षर *name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक रेजिस्टर_module_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	/* no events will happen anyway, so this can always succeed */
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक unरेजिस्टर_module_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

#घोषणा module_put_and_निकास(code) करो_निकास(code)

अटल अंतरभूत व्योम prपूर्णांक_modules(व्योम)
अणु
पूर्ण

अटल अंतरभूत bool module_requested_async_probing(काष्ठा module *module)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool is_module_sig_enक्रमced(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम set_module_sig_enक्रमced(व्योम)
अणु
पूर्ण

/* Dereference module function descriptor */
अटल अंतरभूत
व्योम *dereference_module_function_descriptor(काष्ठा module *mod, व्योम *ptr)
अणु
	वापस ptr;
पूर्ण

#पूर्ण_अगर /* CONFIG_MODULES */

#अगर_घोषित CONFIG_SYSFS
बाह्य काष्ठा kset *module_kset;
बाह्य काष्ठा kobj_type module_ktype;
बाह्य पूर्णांक module_sysfs_initialized;
#पूर्ण_अगर /* CONFIG_SYSFS */

#घोषणा symbol_request(x) try_then_request_module(symbol_get(x), "symbol:" #x)

/* BELOW HERE ALL THESE ARE OBSOLETE AND WILL VANISH */

#घोषणा __MODULE_STRING(x) __stringअगरy(x)

#अगर_घोषित CONFIG_GENERIC_BUG
व्योम module_bug_finalize(स्थिर Elf_Ehdr *, स्थिर Elf_Shdr *,
			 काष्ठा module *);
व्योम module_bug_cleanup(काष्ठा module *);

#अन्यथा	/* !CONFIG_GENERIC_BUG */

अटल अंतरभूत व्योम module_bug_finalize(स्थिर Elf_Ehdr *hdr,
					स्थिर Elf_Shdr *sechdrs,
					काष्ठा module *mod)
अणु
पूर्ण
अटल अंतरभूत व्योम module_bug_cleanup(काष्ठा module *mod) अणुपूर्ण
#पूर्ण_अगर	/* CONFIG_GENERIC_BUG */

#अगर_घोषित CONFIG_RETPOLINE
बाह्य bool retpoline_module_ok(bool has_retpoline);
#अन्यथा
अटल अंतरभूत bool retpoline_module_ok(bool has_retpoline)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MODULE_SIG
अटल अंतरभूत bool module_sig_ok(काष्ठा module *module)
अणु
	वापस module->sig_ok;
पूर्ण
#अन्यथा	/* !CONFIG_MODULE_SIG */
अटल अंतरभूत bool module_sig_ok(काष्ठा module *module)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर	/* CONFIG_MODULE_SIG */

पूर्णांक module_kallsyms_on_each_symbol(पूर्णांक (*fn)(व्योम *, स्थिर अक्षर *,
					     काष्ठा module *, अचिन्हित दीर्घ),
				   व्योम *data);

#पूर्ण_अगर /* _LINUX_MODULE_H */
