<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2002 Riअक्षरd Henderson
 * Copyright (C) 2001 Rusty Russell, 2002, 2010 Rusty Russell IBM.
 */

#घोषणा INCLUDE_VERMAGIC

#समावेश <linux/export.h>
#समावेश <linux/extable.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/module_signature.h>
#समावेश <linux/trace_events.h>
#समावेश <linux/init.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kernel_पढ़ो_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/elf.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/security.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/capability.h>
#समावेश <linux/cpu.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/vermagic.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/sched.h>
#समावेश <linux/device.h>
#समावेश <linux/माला.स>
#समावेश <linux/mutex.h>
#समावेश <linux/rculist.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/set_memory.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <linux/license.h>
#समावेश <यंत्र/sections.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/livepatch.h>
#समावेश <linux/async.h>
#समावेश <linux/percpu.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/pfn.h>
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/dynamic_debug.h>
#समावेश <linux/audit.h>
#समावेश <uapi/linux/module.h>
#समावेश "module-internal.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/module.h>

#अगर_अघोषित ARCH_SHF_SMALL
#घोषणा ARCH_SHF_SMALL 0
#पूर्ण_अगर

/*
 * Modules' sections will be aligned on page boundaries
 * to ensure complete separation of code and data, but
 * only when CONFIG_ARCH_HAS_STRICT_MODULE_RWX=y
 */
#अगर_घोषित CONFIG_ARCH_HAS_STRICT_MODULE_RWX
# define debug_align(X) ALIGN(X, PAGE_SIZE)
#अन्यथा
# define debug_align(X) (X)
#पूर्ण_अगर

/* If this is set, the section beदीर्घs in the init part of the module */
#घोषणा INIT_OFFSET_MASK (1UL << (BITS_PER_LONG-1))

/*
 * Mutex protects:
 * 1) List of modules (also safely पढ़ोable with preempt_disable),
 * 2) module_use links,
 * 3) module_addr_min/module_addr_max.
 * (delete and add uses RCU list operations).
 */
अटल DEFINE_MUTEX(module_mutex);
अटल LIST_HEAD(modules);

/* Work queue क्रम मुक्तing init sections in success हाल */
अटल व्योम करो_मुक्त_init(काष्ठा work_काष्ठा *w);
अटल DECLARE_WORK(init_मुक्त_wq, करो_मुक्त_init);
अटल LLIST_HEAD(init_मुक्त_list);

#अगर_घोषित CONFIG_MODULES_TREE_LOOKUP

/*
 * Use a latched RB-tree क्रम __module_address(); this allows us to use
 * RCU-sched lookups of the address from any context.
 *
 * This is conditional on PERF_EVENTS || TRACING because those can really hit
 * __module_address() hard by करोing a lot of stack unwinding; potentially from
 * NMI context.
 */

अटल __always_अंतरभूत अचिन्हित दीर्घ __mod_tree_val(काष्ठा latch_tree_node *n)
अणु
	काष्ठा module_layout *layout = container_of(n, काष्ठा module_layout, mtn.node);

	वापस (अचिन्हित दीर्घ)layout->base;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ __mod_tree_size(काष्ठा latch_tree_node *n)
अणु
	काष्ठा module_layout *layout = container_of(n, काष्ठा module_layout, mtn.node);

	वापस (अचिन्हित दीर्घ)layout->size;
पूर्ण

अटल __always_अंतरभूत bool
mod_tree_less(काष्ठा latch_tree_node *a, काष्ठा latch_tree_node *b)
अणु
	वापस __mod_tree_val(a) < __mod_tree_val(b);
पूर्ण

अटल __always_अंतरभूत पूर्णांक
mod_tree_comp(व्योम *key, काष्ठा latch_tree_node *n)
अणु
	अचिन्हित दीर्घ val = (अचिन्हित दीर्घ)key;
	अचिन्हित दीर्घ start, end;

	start = __mod_tree_val(n);
	अगर (val < start)
		वापस -1;

	end = start + __mod_tree_size(n);
	अगर (val >= end)
		वापस 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा latch_tree_ops mod_tree_ops = अणु
	.less = mod_tree_less,
	.comp = mod_tree_comp,
पूर्ण;

अटल काष्ठा mod_tree_root अणु
	काष्ठा latch_tree_root root;
	अचिन्हित दीर्घ addr_min;
	अचिन्हित दीर्घ addr_max;
पूर्ण mod_tree __cacheline_aligned = अणु
	.addr_min = -1UL,
पूर्ण;

#घोषणा module_addr_min mod_tree.addr_min
#घोषणा module_addr_max mod_tree.addr_max

अटल noअंतरभूत व्योम __mod_tree_insert(काष्ठा mod_tree_node *node)
अणु
	latch_tree_insert(&node->node, &mod_tree.root, &mod_tree_ops);
पूर्ण

अटल व्योम __mod_tree_हटाओ(काष्ठा mod_tree_node *node)
अणु
	latch_tree_erase(&node->node, &mod_tree.root, &mod_tree_ops);
पूर्ण

/*
 * These modअगरications: insert, हटाओ_init and हटाओ; are serialized by the
 * module_mutex.
 */
अटल व्योम mod_tree_insert(काष्ठा module *mod)
अणु
	mod->core_layout.mtn.mod = mod;
	mod->init_layout.mtn.mod = mod;

	__mod_tree_insert(&mod->core_layout.mtn);
	अगर (mod->init_layout.size)
		__mod_tree_insert(&mod->init_layout.mtn);
पूर्ण

अटल व्योम mod_tree_हटाओ_init(काष्ठा module *mod)
अणु
	अगर (mod->init_layout.size)
		__mod_tree_हटाओ(&mod->init_layout.mtn);
पूर्ण

अटल व्योम mod_tree_हटाओ(काष्ठा module *mod)
अणु
	__mod_tree_हटाओ(&mod->core_layout.mtn);
	mod_tree_हटाओ_init(mod);
पूर्ण

अटल काष्ठा module *mod_find(अचिन्हित दीर्घ addr)
अणु
	काष्ठा latch_tree_node *ltn;

	ltn = latch_tree_find((व्योम *)addr, &mod_tree.root, &mod_tree_ops);
	अगर (!ltn)
		वापस शून्य;

	वापस container_of(ltn, काष्ठा mod_tree_node, node)->mod;
पूर्ण

#अन्यथा /* MODULES_TREE_LOOKUP */

अटल अचिन्हित दीर्घ module_addr_min = -1UL, module_addr_max = 0;

अटल व्योम mod_tree_insert(काष्ठा module *mod) अणु पूर्ण
अटल व्योम mod_tree_हटाओ_init(काष्ठा module *mod) अणु पूर्ण
अटल व्योम mod_tree_हटाओ(काष्ठा module *mod) अणु पूर्ण

अटल काष्ठा module *mod_find(अचिन्हित दीर्घ addr)
अणु
	काष्ठा module *mod;

	list_क्रम_each_entry_rcu(mod, &modules, list,
				lockdep_is_held(&module_mutex)) अणु
		अगर (within_module(addr, mod))
			वापस mod;
	पूर्ण

	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* MODULES_TREE_LOOKUP */

/*
 * Bounds of module text, क्रम speeding up __module_address.
 * Protected by module_mutex.
 */
अटल व्योम __mod_update_bounds(व्योम *base, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित दीर्घ min = (अचिन्हित दीर्घ)base;
	अचिन्हित दीर्घ max = min + size;

	अगर (min < module_addr_min)
		module_addr_min = min;
	अगर (max > module_addr_max)
		module_addr_max = max;
पूर्ण

अटल व्योम mod_update_bounds(काष्ठा module *mod)
अणु
	__mod_update_bounds(mod->core_layout.base, mod->core_layout.size);
	अगर (mod->init_layout.size)
		__mod_update_bounds(mod->init_layout.base, mod->init_layout.size);
पूर्ण

#अगर_घोषित CONFIG_KGDB_KDB
काष्ठा list_head *kdb_modules = &modules; /* kdb needs the list of modules */
#पूर्ण_अगर /* CONFIG_KGDB_KDB */

अटल व्योम module_निश्चित_mutex_or_preempt(व्योम)
अणु
#अगर_घोषित CONFIG_LOCKDEP
	अगर (unlikely(!debug_locks))
		वापस;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_sched_held() &&
		!lockdep_is_held(&module_mutex));
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_MODULE_SIG
अटल bool sig_enक्रमce = IS_ENABLED(CONFIG_MODULE_SIG_FORCE);
module_param(sig_enक्रमce, bool_enable_only, 0644);

व्योम set_module_sig_enक्रमced(व्योम)
अणु
	sig_enक्रमce = true;
पूर्ण
#अन्यथा
#घोषणा sig_enक्रमce false
#पूर्ण_अगर

/*
 * Export sig_enक्रमce kernel cmdline parameter to allow other subप्रणालीs rely
 * on that instead of directly to CONFIG_MODULE_SIG_FORCE config.
 */
bool is_module_sig_enक्रमced(व्योम)
अणु
	वापस sig_enक्रमce;
पूर्ण
EXPORT_SYMBOL(is_module_sig_enक्रमced);

/* Block module loading/unloading? */
पूर्णांक modules_disabled = 0;
core_param(nomodule, modules_disabled, bपूर्णांक, 0);

/* Waiting क्रम a module to finish initializing? */
अटल DECLARE_WAIT_QUEUE_HEAD(module_wq);

अटल BLOCKING_NOTIFIER_HEAD(module_notअगरy_list);

पूर्णांक रेजिस्टर_module_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&module_notअगरy_list, nb);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_module_notअगरier);

पूर्णांक unरेजिस्टर_module_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&module_notअगरy_list, nb);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_module_notअगरier);

/*
 * We require a truly strong try_module_get(): 0 means success.
 * Otherwise an error is वापसed due to ongoing or failed
 * initialization etc.
 */
अटल अंतरभूत पूर्णांक strong_try_module_get(काष्ठा module *mod)
अणु
	BUG_ON(mod && mod->state == MODULE_STATE_UNFORMED);
	अगर (mod && mod->state == MODULE_STATE_COMING)
		वापस -EBUSY;
	अगर (try_module_get(mod))
		वापस 0;
	अन्यथा
		वापस -ENOENT;
पूर्ण

अटल अंतरभूत व्योम add_taपूर्णांक_module(काष्ठा module *mod, अचिन्हित flag,
				    क्रमागत lockdep_ok lockdep_ok)
अणु
	add_taपूर्णांक(flag, lockdep_ok);
	set_bit(flag, &mod->taपूर्णांकs);
पूर्ण

/*
 * A thपढ़ो that wants to hold a reference to a module only जबतक it
 * is running can call this to safely निकास.  nfsd and lockd use this.
 */
व्योम __noवापस __module_put_and_निकास(काष्ठा module *mod, दीर्घ code)
अणु
	module_put(mod);
	करो_निकास(code);
पूर्ण
EXPORT_SYMBOL(__module_put_and_निकास);

/* Find a module section: 0 means not found. */
अटल अचिन्हित पूर्णांक find_sec(स्थिर काष्ठा load_info *info, स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 1; i < info->hdr->e_shnum; i++) अणु
		Elf_Shdr *shdr = &info->sechdrs[i];
		/* Alloc bit cleared means "ignore it." */
		अगर ((shdr->sh_flags & SHF_ALLOC)
		    && म_भेद(info->secstrings + shdr->sh_name, name) == 0)
			वापस i;
	पूर्ण
	वापस 0;
पूर्ण

/* Find a module section, or शून्य. */
अटल व्योम *section_addr(स्थिर काष्ठा load_info *info, स्थिर अक्षर *name)
अणु
	/* Section 0 has sh_addr 0. */
	वापस (व्योम *)info->sechdrs[find_sec(info, name)].sh_addr;
पूर्ण

/* Find a module section, or शून्य.  Fill in number of "objects" in section. */
अटल व्योम *section_objs(स्थिर काष्ठा load_info *info,
			  स्थिर अक्षर *name,
			  माप_प्रकार object_size,
			  अचिन्हित पूर्णांक *num)
अणु
	अचिन्हित पूर्णांक sec = find_sec(info, name);

	/* Section 0 has sh_addr 0 and sh_size 0. */
	*num = info->sechdrs[sec].sh_size / object_size;
	वापस (व्योम *)info->sechdrs[sec].sh_addr;
पूर्ण

/* Find a module section: 0 means not found. Ignores SHF_ALLOC flag. */
अटल अचिन्हित पूर्णांक find_any_sec(स्थिर काष्ठा load_info *info, स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 1; i < info->hdr->e_shnum; i++) अणु
		Elf_Shdr *shdr = &info->sechdrs[i];
		अगर (म_भेद(info->secstrings + shdr->sh_name, name) == 0)
			वापस i;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Find a module section, or शून्य. Fill in number of "objects" in section.
 * Ignores SHF_ALLOC flag.
 */
अटल __maybe_unused व्योम *any_section_objs(स्थिर काष्ठा load_info *info,
					     स्थिर अक्षर *name,
					     माप_प्रकार object_size,
					     अचिन्हित पूर्णांक *num)
अणु
	अचिन्हित पूर्णांक sec = find_any_sec(info, name);

	/* Section 0 has sh_addr 0 and sh_size 0. */
	*num = info->sechdrs[sec].sh_size / object_size;
	वापस (व्योम *)info->sechdrs[sec].sh_addr;
पूर्ण

/* Provided by the linker */
बाह्य स्थिर काष्ठा kernel_symbol __start___ksymtab[];
बाह्य स्थिर काष्ठा kernel_symbol __stop___ksymtab[];
बाह्य स्थिर काष्ठा kernel_symbol __start___ksymtab_gpl[];
बाह्य स्थिर काष्ठा kernel_symbol __stop___ksymtab_gpl[];
बाह्य स्थिर s32 __start___kcrctab[];
बाह्य स्थिर s32 __start___kcrctab_gpl[];

#अगर_अघोषित CONFIG_MODVERSIONS
#घोषणा symversion(base, idx) शून्य
#अन्यथा
#घोषणा symversion(base, idx) ((base != शून्य) ? ((base) + (idx)) : शून्य)
#पूर्ण_अगर

काष्ठा symsearch अणु
	स्थिर काष्ठा kernel_symbol *start, *stop;
	स्थिर s32 *crcs;
	क्रमागत mod_license अणु
		NOT_GPL_ONLY,
		GPL_ONLY,
	पूर्ण license;
पूर्ण;

काष्ठा find_symbol_arg अणु
	/* Input */
	स्थिर अक्षर *name;
	bool gplok;
	bool warn;

	/* Output */
	काष्ठा module *owner;
	स्थिर s32 *crc;
	स्थिर काष्ठा kernel_symbol *sym;
	क्रमागत mod_license license;
पूर्ण;

अटल bool check_exported_symbol(स्थिर काष्ठा symsearch *syms,
				  काष्ठा module *owner,
				  अचिन्हित पूर्णांक symnum, व्योम *data)
अणु
	काष्ठा find_symbol_arg *fsa = data;

	अगर (!fsa->gplok && syms->license == GPL_ONLY)
		वापस false;
	fsa->owner = owner;
	fsa->crc = symversion(syms->crcs, symnum);
	fsa->sym = &syms->start[symnum];
	fsa->license = syms->license;
	वापस true;
पूर्ण

अटल अचिन्हित दीर्घ kernel_symbol_value(स्थिर काष्ठा kernel_symbol *sym)
अणु
#अगर_घोषित CONFIG_HAVE_ARCH_PREL32_RELOCATIONS
	वापस (अचिन्हित दीर्घ)offset_to_ptr(&sym->value_offset);
#अन्यथा
	वापस sym->value;
#पूर्ण_अगर
पूर्ण

अटल स्थिर अक्षर *kernel_symbol_name(स्थिर काष्ठा kernel_symbol *sym)
अणु
#अगर_घोषित CONFIG_HAVE_ARCH_PREL32_RELOCATIONS
	वापस offset_to_ptr(&sym->name_offset);
#अन्यथा
	वापस sym->name;
#पूर्ण_अगर
पूर्ण

अटल स्थिर अक्षर *kernel_symbol_namespace(स्थिर काष्ठा kernel_symbol *sym)
अणु
#अगर_घोषित CONFIG_HAVE_ARCH_PREL32_RELOCATIONS
	अगर (!sym->namespace_offset)
		वापस शून्य;
	वापस offset_to_ptr(&sym->namespace_offset);
#अन्यथा
	वापस sym->namespace;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक cmp_name(स्थिर व्योम *name, स्थिर व्योम *sym)
अणु
	वापस म_भेद(name, kernel_symbol_name(sym));
पूर्ण

अटल bool find_exported_symbol_in_section(स्थिर काष्ठा symsearch *syms,
					    काष्ठा module *owner,
					    व्योम *data)
अणु
	काष्ठा find_symbol_arg *fsa = data;
	काष्ठा kernel_symbol *sym;

	sym = द्वा_खोज(fsa->name, syms->start, syms->stop - syms->start,
			माप(काष्ठा kernel_symbol), cmp_name);

	अगर (sym != शून्य && check_exported_symbol(syms, owner,
						 sym - syms->start, data))
		वापस true;

	वापस false;
पूर्ण

/*
 * Find an exported symbol and वापस it, aदीर्घ with, (optional) crc and
 * (optional) module which owns it.  Needs preempt disabled or module_mutex.
 */
अटल bool find_symbol(काष्ठा find_symbol_arg *fsa)
अणु
	अटल स्थिर काष्ठा symsearch arr[] = अणु
		अणु __start___ksymtab, __stop___ksymtab, __start___kcrctab,
		  NOT_GPL_ONLY पूर्ण,
		अणु __start___ksymtab_gpl, __stop___ksymtab_gpl,
		  __start___kcrctab_gpl,
		  GPL_ONLY पूर्ण,
	पूर्ण;
	काष्ठा module *mod;
	अचिन्हित पूर्णांक i;

	module_निश्चित_mutex_or_preempt();

	क्रम (i = 0; i < ARRAY_SIZE(arr); i++)
		अगर (find_exported_symbol_in_section(&arr[i], शून्य, fsa))
			वापस true;

	list_क्रम_each_entry_rcu(mod, &modules, list,
				lockdep_is_held(&module_mutex)) अणु
		काष्ठा symsearch arr[] = अणु
			अणु mod->syms, mod->syms + mod->num_syms, mod->crcs,
			  NOT_GPL_ONLY पूर्ण,
			अणु mod->gpl_syms, mod->gpl_syms + mod->num_gpl_syms,
			  mod->gpl_crcs,
			  GPL_ONLY पूर्ण,
		पूर्ण;

		अगर (mod->state == MODULE_STATE_UNFORMED)
			जारी;

		क्रम (i = 0; i < ARRAY_SIZE(arr); i++)
			अगर (find_exported_symbol_in_section(&arr[i], mod, fsa))
				वापस true;
	पूर्ण

	pr_debug("Failed to find symbol %s\n", fsa->name);
	वापस false;
पूर्ण

/*
 * Search क्रम module by name: must hold module_mutex (or preempt disabled
 * क्रम पढ़ो-only access).
 */
अटल काष्ठा module *find_module_all(स्थिर अक्षर *name, माप_प्रकार len,
				      bool even_unक्रमmed)
अणु
	काष्ठा module *mod;

	module_निश्चित_mutex_or_preempt();

	list_क्रम_each_entry_rcu(mod, &modules, list,
				lockdep_is_held(&module_mutex)) अणु
		अगर (!even_unक्रमmed && mod->state == MODULE_STATE_UNFORMED)
			जारी;
		अगर (म_माप(mod->name) == len && !स_भेद(mod->name, name, len))
			वापस mod;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा module *find_module(स्थिर अक्षर *name)
अणु
	वापस find_module_all(name, म_माप(name), false);
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल अंतरभूत व्योम __percpu *mod_percpu(काष्ठा module *mod)
अणु
	वापस mod->percpu;
पूर्ण

अटल पूर्णांक percpu_modalloc(काष्ठा module *mod, काष्ठा load_info *info)
अणु
	Elf_Shdr *pcpusec = &info->sechdrs[info->index.pcpu];
	अचिन्हित दीर्घ align = pcpusec->sh_addralign;

	अगर (!pcpusec->sh_size)
		वापस 0;

	अगर (align > PAGE_SIZE) अणु
		pr_warn("%s: per-cpu alignment %li > %li\n",
			mod->name, align, PAGE_SIZE);
		align = PAGE_SIZE;
	पूर्ण

	mod->percpu = __alloc_reserved_percpu(pcpusec->sh_size, align);
	अगर (!mod->percpu) अणु
		pr_warn("%s: Could not allocate %lu bytes percpu data\n",
			mod->name, (अचिन्हित दीर्घ)pcpusec->sh_size);
		वापस -ENOMEM;
	पूर्ण
	mod->percpu_size = pcpusec->sh_size;
	वापस 0;
पूर्ण

अटल व्योम percpu_modमुक्त(काष्ठा module *mod)
अणु
	मुक्त_percpu(mod->percpu);
पूर्ण

अटल अचिन्हित पूर्णांक find_pcpusec(काष्ठा load_info *info)
अणु
	वापस find_sec(info, ".data..percpu");
पूर्ण

अटल व्योम percpu_modcopy(काष्ठा module *mod,
			   स्थिर व्योम *from, अचिन्हित दीर्घ size)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		स_नकल(per_cpu_ptr(mod->percpu, cpu), from, size);
पूर्ण

bool __is_module_percpu_address(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *can_addr)
अणु
	काष्ठा module *mod;
	अचिन्हित पूर्णांक cpu;

	preempt_disable();

	list_क्रम_each_entry_rcu(mod, &modules, list) अणु
		अगर (mod->state == MODULE_STATE_UNFORMED)
			जारी;
		अगर (!mod->percpu_size)
			जारी;
		क्रम_each_possible_cpu(cpu) अणु
			व्योम *start = per_cpu_ptr(mod->percpu, cpu);
			व्योम *va = (व्योम *)addr;

			अगर (va >= start && va < start + mod->percpu_size) अणु
				अगर (can_addr) अणु
					*can_addr = (अचिन्हित दीर्घ) (va - start);
					*can_addr += (अचिन्हित दीर्घ)
						per_cpu_ptr(mod->percpu,
							    get_boot_cpu_id());
				पूर्ण
				preempt_enable();
				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण

	preempt_enable();
	वापस false;
पूर्ण

/**
 * is_module_percpu_address() - test whether address is from module अटल percpu
 * @addr: address to test
 *
 * Test whether @addr beदीर्घs to module अटल percpu area.
 *
 * Return: %true अगर @addr is from module अटल percpu area
 */
bool is_module_percpu_address(अचिन्हित दीर्घ addr)
अणु
	वापस __is_module_percpu_address(addr, शून्य);
पूर्ण

#अन्यथा /* ... !CONFIG_SMP */

अटल अंतरभूत व्योम __percpu *mod_percpu(काष्ठा module *mod)
अणु
	वापस शून्य;
पूर्ण
अटल पूर्णांक percpu_modalloc(काष्ठा module *mod, काष्ठा load_info *info)
अणु
	/* UP modules shouldn't have this section: ENOMEM isn't quite right */
	अगर (info->sechdrs[info->index.pcpu].sh_size != 0)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम percpu_modमुक्त(काष्ठा module *mod)
अणु
पूर्ण
अटल अचिन्हित पूर्णांक find_pcpusec(काष्ठा load_info *info)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम percpu_modcopy(काष्ठा module *mod,
				  स्थिर व्योम *from, अचिन्हित दीर्घ size)
अणु
	/* pcpusec should be 0, and size of that section should be 0. */
	BUG_ON(size != 0);
पूर्ण
bool is_module_percpu_address(अचिन्हित दीर्घ addr)
अणु
	वापस false;
पूर्ण

bool __is_module_percpu_address(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *can_addr)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

#घोषणा MODINFO_ATTR(field)	\
अटल व्योम setup_modinfo_##field(काष्ठा module *mod, स्थिर अक्षर *s)  \
अणु                                                                     \
	mod->field = kstrdup(s, GFP_KERNEL);                          \
पूर्ण                                                                     \
अटल sमाप_प्रकार show_modinfo_##field(काष्ठा module_attribute *mattr,   \
			काष्ठा module_kobject *mk, अक्षर *buffer)      \
अणु                                                                     \
	वापस scnम_लिखो(buffer, PAGE_SIZE, "%s\n", mk->mod->field);  \
पूर्ण                                                                     \
अटल पूर्णांक modinfo_##field##_exists(काष्ठा module *mod)               \
अणु                                                                     \
	वापस mod->field != शून्य;                                    \
पूर्ण                                                                     \
अटल व्योम मुक्त_modinfo_##field(काष्ठा module *mod)                  \
अणु                                                                     \
	kमुक्त(mod->field);                                            \
	mod->field = शून्य;                                            \
पूर्ण                                                                     \
अटल काष्ठा module_attribute modinfo_##field = अणु                    \
	.attr = अणु .name = __stringअगरy(field), .mode = 0444 पूर्ण,         \
	.show = show_modinfo_##field,                                 \
	.setup = setup_modinfo_##field,                               \
	.test = modinfo_##field##_exists,                             \
	.मुक्त = मुक्त_modinfo_##field,                                 \
पूर्ण;

MODINFO_ATTR(version);
MODINFO_ATTR(srcversion);

अटल अक्षर last_unloaded_module[MODULE_NAME_LEN+1];

#अगर_घोषित CONFIG_MODULE_UNLOAD

EXPORT_TRACEPOINT_SYMBOL(module_get);

/* MODULE_REF_BASE is the base reference count by kmodule loader. */
#घोषणा MODULE_REF_BASE	1

/* Init the unload section of the module. */
अटल पूर्णांक module_unload_init(काष्ठा module *mod)
अणु
	/*
	 * Initialize reference counter to MODULE_REF_BASE.
	 * refcnt == 0 means module is going.
	 */
	atomic_set(&mod->refcnt, MODULE_REF_BASE);

	INIT_LIST_HEAD(&mod->source_list);
	INIT_LIST_HEAD(&mod->target_list);

	/* Hold reference count during initialization. */
	atomic_inc(&mod->refcnt);

	वापस 0;
पूर्ण

/* Does a alपढ़ोy use b? */
अटल पूर्णांक alपढ़ोy_uses(काष्ठा module *a, काष्ठा module *b)
अणु
	काष्ठा module_use *use;

	list_क्रम_each_entry(use, &b->source_list, source_list) अणु
		अगर (use->source == a) अणु
			pr_debug("%s uses %s!\n", a->name, b->name);
			वापस 1;
		पूर्ण
	पूर्ण
	pr_debug("%s does not use %s!\n", a->name, b->name);
	वापस 0;
पूर्ण

/*
 * Module a uses b
 *  - we add 'a' as a "source", 'b' as a "target" of module use
 *  - the module_use is added to the list of 'b' sources (so
 *    'b' can walk the list to see who sourced them), and of 'a'
 *    tarमाला_लो (so 'a' can see what modules it tarमाला_लो).
 */
अटल पूर्णांक add_module_usage(काष्ठा module *a, काष्ठा module *b)
अणु
	काष्ठा module_use *use;

	pr_debug("Allocating new usage for %s.\n", a->name);
	use = kदो_स्मृति(माप(*use), GFP_ATOMIC);
	अगर (!use)
		वापस -ENOMEM;

	use->source = a;
	use->target = b;
	list_add(&use->source_list, &b->source_list);
	list_add(&use->target_list, &a->target_list);
	वापस 0;
पूर्ण

/* Module a uses b: caller needs module_mutex() */
अटल पूर्णांक ref_module(काष्ठा module *a, काष्ठा module *b)
अणु
	पूर्णांक err;

	अगर (b == शून्य || alपढ़ोy_uses(a, b))
		वापस 0;

	/* If module isn't available, we fail. */
	err = strong_try_module_get(b);
	अगर (err)
		वापस err;

	err = add_module_usage(a, b);
	अगर (err) अणु
		module_put(b);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/* Clear the unload stuff of the module. */
अटल व्योम module_unload_मुक्त(काष्ठा module *mod)
अणु
	काष्ठा module_use *use, *पंचांगp;

	mutex_lock(&module_mutex);
	list_क्रम_each_entry_safe(use, पंचांगp, &mod->target_list, target_list) अणु
		काष्ठा module *i = use->target;
		pr_debug("%s unusing %s\n", mod->name, i->name);
		module_put(i);
		list_del(&use->source_list);
		list_del(&use->target_list);
		kमुक्त(use);
	पूर्ण
	mutex_unlock(&module_mutex);
पूर्ण

#अगर_घोषित CONFIG_MODULE_FORCE_UNLOAD
अटल अंतरभूत पूर्णांक try_क्रमce_unload(अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ret = (flags & O_TRUNC);
	अगर (ret)
		add_taपूर्णांक(TAINT_FORCED_RMMOD, LOCKDEP_NOW_UNRELIABLE);
	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक try_क्रमce_unload(अचिन्हित पूर्णांक flags)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_MODULE_FORCE_UNLOAD */

/* Try to release refcount of module, 0 means success. */
अटल पूर्णांक try_release_module_ref(काष्ठा module *mod)
अणु
	पूर्णांक ret;

	/* Try to decrement refcnt which we set at loading */
	ret = atomic_sub_वापस(MODULE_REF_BASE, &mod->refcnt);
	BUG_ON(ret < 0);
	अगर (ret)
		/* Someone can put this right now, recover with checking */
		ret = atomic_add_unless(&mod->refcnt, MODULE_REF_BASE, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक try_stop_module(काष्ठा module *mod, पूर्णांक flags, पूर्णांक *क्रमced)
अणु
	/* If it's not unused, quit unless we're क्रमcing. */
	अगर (try_release_module_ref(mod) != 0) अणु
		*क्रमced = try_क्रमce_unload(flags);
		अगर (!(*क्रमced))
			वापस -EWOULDBLOCK;
	पूर्ण

	/* Mark it as dying. */
	mod->state = MODULE_STATE_GOING;

	वापस 0;
पूर्ण

/**
 * module_refcount() - वापस the refcount or -1 अगर unloading
 * @mod:	the module we're checking
 *
 * Return:
 *	-1 अगर the module is in the process of unloading
 *	otherwise the number of references in the kernel to the module
 */
पूर्णांक module_refcount(काष्ठा module *mod)
अणु
	वापस atomic_पढ़ो(&mod->refcnt) - MODULE_REF_BASE;
पूर्ण
EXPORT_SYMBOL(module_refcount);

/* This exists whether we can unload or not */
अटल व्योम मुक्त_module(काष्ठा module *mod);

SYSCALL_DEFINE2(delete_module, स्थिर अक्षर __user *, name_user,
		अचिन्हित पूर्णांक, flags)
अणु
	काष्ठा module *mod;
	अक्षर name[MODULE_NAME_LEN];
	पूर्णांक ret, क्रमced = 0;

	अगर (!capable(CAP_SYS_MODULE) || modules_disabled)
		वापस -EPERM;

	अगर (म_नकलन_from_user(name, name_user, MODULE_NAME_LEN-1) < 0)
		वापस -EFAULT;
	name[MODULE_NAME_LEN-1] = '\0';

	audit_log_kern_module(name);

	अगर (mutex_lock_पूर्णांकerruptible(&module_mutex) != 0)
		वापस -EINTR;

	mod = find_module(name);
	अगर (!mod) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (!list_empty(&mod->source_list)) अणु
		/* Other modules depend on us: get rid of them first. */
		ret = -EWOULDBLOCK;
		जाओ out;
	पूर्ण

	/* Doing init or alपढ़ोy dying? */
	अगर (mod->state != MODULE_STATE_LIVE) अणु
		/* FIXME: अगर (क्रमce), slam module count damn the torpeकरोes */
		pr_debug("%s already dying\n", mod->name);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/* If it has an init func, it must have an निकास func to unload */
	अगर (mod->init && !mod->निकास) अणु
		क्रमced = try_क्रमce_unload(flags);
		अगर (!क्रमced) अणु
			/* This module can't be हटाओd */
			ret = -EBUSY;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Stop the machine so refcounts can't move and disable module. */
	ret = try_stop_module(mod, flags, &क्रमced);
	अगर (ret != 0)
		जाओ out;

	mutex_unlock(&module_mutex);
	/* Final deकाष्ठाion now no one is using it. */
	अगर (mod->निकास != शून्य)
		mod->निकास();
	blocking_notअगरier_call_chain(&module_notअगरy_list,
				     MODULE_STATE_GOING, mod);
	klp_module_going(mod);
	ftrace_release_mod(mod);

	async_synchronize_full();

	/* Store the name of the last unloaded module क्रम diagnostic purposes */
	strlcpy(last_unloaded_module, mod->name, माप(last_unloaded_module));

	मुक्त_module(mod);
	/* someone could रुको क्रम the module in add_unक्रमmed_module() */
	wake_up_all(&module_wq);
	वापस 0;
out:
	mutex_unlock(&module_mutex);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम prपूर्णांक_unload_info(काष्ठा seq_file *m, काष्ठा module *mod)
अणु
	काष्ठा module_use *use;
	पूर्णांक prपूर्णांकed_something = 0;

	seq_म_लिखो(m, " %i ", module_refcount(mod));

	/*
	 * Always include a trailing , so userspace can dअगरferentiate
	 * between this and the old multi-field proc क्रमmat.
	 */
	list_क्रम_each_entry(use, &mod->source_list, source_list) अणु
		prपूर्णांकed_something = 1;
		seq_म_लिखो(m, "%s,", use->source->name);
	पूर्ण

	अगर (mod->init != शून्य && mod->निकास == शून्य) अणु
		prपूर्णांकed_something = 1;
		seq_माला_दो(m, "[permanent],");
	पूर्ण

	अगर (!prपूर्णांकed_something)
		seq_माला_दो(m, "-");
पूर्ण

व्योम __symbol_put(स्थिर अक्षर *symbol)
अणु
	काष्ठा find_symbol_arg fsa = अणु
		.name	= symbol,
		.gplok	= true,
	पूर्ण;

	preempt_disable();
	अगर (!find_symbol(&fsa))
		BUG();
	module_put(fsa.owner);
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(__symbol_put);

/* Note this assumes addr is a function, which it currently always is. */
व्योम symbol_put_addr(व्योम *addr)
अणु
	काष्ठा module *modaddr;
	अचिन्हित दीर्घ a = (अचिन्हित दीर्घ)dereference_function_descriptor(addr);

	अगर (core_kernel_text(a))
		वापस;

	/*
	 * Even though we hold a reference on the module; we still need to
	 * disable preemption in order to safely traverse the data काष्ठाure.
	 */
	preempt_disable();
	modaddr = __module_text_address(a);
	BUG_ON(!modaddr);
	module_put(modaddr);
	preempt_enable();
पूर्ण
EXPORT_SYMBOL_GPL(symbol_put_addr);

अटल sमाप_प्रकार show_refcnt(काष्ठा module_attribute *mattr,
			   काष्ठा module_kobject *mk, अक्षर *buffer)
अणु
	वापस प्र_लिखो(buffer, "%i\n", module_refcount(mk->mod));
पूर्ण

अटल काष्ठा module_attribute modinfo_refcnt =
	__ATTR(refcnt, 0444, show_refcnt, शून्य);

व्योम __module_get(काष्ठा module *module)
अणु
	अगर (module) अणु
		preempt_disable();
		atomic_inc(&module->refcnt);
		trace_module_get(module, _RET_IP_);
		preempt_enable();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__module_get);

bool try_module_get(काष्ठा module *module)
अणु
	bool ret = true;

	अगर (module) अणु
		preempt_disable();
		/* Note: here, we can fail to get a reference */
		अगर (likely(module_is_live(module) &&
			   atomic_inc_not_zero(&module->refcnt) != 0))
			trace_module_get(module, _RET_IP_);
		अन्यथा
			ret = false;

		preempt_enable();
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(try_module_get);

व्योम module_put(काष्ठा module *module)
अणु
	पूर्णांक ret;

	अगर (module) अणु
		preempt_disable();
		ret = atomic_dec_अगर_positive(&module->refcnt);
		WARN_ON(ret < 0);	/* Failed to put refcount */
		trace_module_put(module, _RET_IP_);
		preempt_enable();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(module_put);

#अन्यथा /* !CONFIG_MODULE_UNLOAD */
अटल अंतरभूत व्योम prपूर्णांक_unload_info(काष्ठा seq_file *m, काष्ठा module *mod)
अणु
	/* We करोn't know the usage count, or what modules are using. */
	seq_माला_दो(m, " - -");
पूर्ण

अटल अंतरभूत व्योम module_unload_मुक्त(काष्ठा module *mod)
अणु
पूर्ण

अटल पूर्णांक ref_module(काष्ठा module *a, काष्ठा module *b)
अणु
	वापस strong_try_module_get(b);
पूर्ण

अटल अंतरभूत पूर्णांक module_unload_init(काष्ठा module *mod)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_MODULE_UNLOAD */

अटल माप_प्रकार module_flags_taपूर्णांक(काष्ठा module *mod, अक्षर *buf)
अणु
	माप_प्रकार l = 0;
	पूर्णांक i;

	क्रम (i = 0; i < TAINT_FLAGS_COUNT; i++) अणु
		अगर (taपूर्णांक_flags[i].module && test_bit(i, &mod->taपूर्णांकs))
			buf[l++] = taपूर्णांक_flags[i].c_true;
	पूर्ण

	वापस l;
पूर्ण

अटल sमाप_प्रकार show_initstate(काष्ठा module_attribute *mattr,
			      काष्ठा module_kobject *mk, अक्षर *buffer)
अणु
	स्थिर अक्षर *state = "unknown";

	चयन (mk->mod->state) अणु
	हाल MODULE_STATE_LIVE:
		state = "live";
		अवरोध;
	हाल MODULE_STATE_COMING:
		state = "coming";
		अवरोध;
	हाल MODULE_STATE_GOING:
		state = "going";
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	वापस प्र_लिखो(buffer, "%s\n", state);
पूर्ण

अटल काष्ठा module_attribute modinfo_initstate =
	__ATTR(initstate, 0444, show_initstate, शून्य);

अटल sमाप_प्रकार store_uevent(काष्ठा module_attribute *mattr,
			    काष्ठा module_kobject *mk,
			    स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	पूर्णांक rc;

	rc = kobject_synth_uevent(&mk->kobj, buffer, count);
	वापस rc ? rc : count;
पूर्ण

काष्ठा module_attribute module_uevent =
	__ATTR(uevent, 0200, शून्य, store_uevent);

अटल sमाप_प्रकार show_coresize(काष्ठा module_attribute *mattr,
			     काष्ठा module_kobject *mk, अक्षर *buffer)
अणु
	वापस प्र_लिखो(buffer, "%u\n", mk->mod->core_layout.size);
पूर्ण

अटल काष्ठा module_attribute modinfo_coresize =
	__ATTR(coresize, 0444, show_coresize, शून्य);

अटल sमाप_प्रकार show_initsize(काष्ठा module_attribute *mattr,
			     काष्ठा module_kobject *mk, अक्षर *buffer)
अणु
	वापस प्र_लिखो(buffer, "%u\n", mk->mod->init_layout.size);
पूर्ण

अटल काष्ठा module_attribute modinfo_initsize =
	__ATTR(initsize, 0444, show_initsize, शून्य);

अटल sमाप_प्रकार show_taपूर्णांक(काष्ठा module_attribute *mattr,
			  काष्ठा module_kobject *mk, अक्षर *buffer)
अणु
	माप_प्रकार l;

	l = module_flags_taपूर्णांक(mk->mod, buffer);
	buffer[l++] = '\n';
	वापस l;
पूर्ण

अटल काष्ठा module_attribute modinfo_taपूर्णांक =
	__ATTR(taपूर्णांक, 0444, show_taपूर्णांक, शून्य);

अटल काष्ठा module_attribute *modinfo_attrs[] = अणु
	&module_uevent,
	&modinfo_version,
	&modinfo_srcversion,
	&modinfo_initstate,
	&modinfo_coresize,
	&modinfo_initsize,
	&modinfo_taपूर्णांक,
#अगर_घोषित CONFIG_MODULE_UNLOAD
	&modinfo_refcnt,
#पूर्ण_अगर
	शून्य,
पूर्ण;

अटल स्थिर अक्षर vermagic[] = VERMAGIC_STRING;

अटल पूर्णांक try_to_क्रमce_load(काष्ठा module *mod, स्थिर अक्षर *reason)
अणु
#अगर_घोषित CONFIG_MODULE_FORCE_LOAD
	अगर (!test_taपूर्णांक(TAINT_FORCED_MODULE))
		pr_warn("%s: %s: kernel tainted.\n", mod->name, reason);
	add_taपूर्णांक_module(mod, TAINT_FORCED_MODULE, LOCKDEP_NOW_UNRELIABLE);
	वापस 0;
#अन्यथा
	वापस -ENOEXEC;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_MODVERSIONS

अटल u32 resolve_rel_crc(स्थिर s32 *crc)
अणु
	वापस *(u32 *)((व्योम *)crc + *crc);
पूर्ण

अटल पूर्णांक check_version(स्थिर काष्ठा load_info *info,
			 स्थिर अक्षर *symname,
			 काष्ठा module *mod,
			 स्थिर s32 *crc)
अणु
	Elf_Shdr *sechdrs = info->sechdrs;
	अचिन्हित पूर्णांक versindex = info->index.vers;
	अचिन्हित पूर्णांक i, num_versions;
	काष्ठा modversion_info *versions;

	/* Exporting module didn't supply crcs?  OK, we're alपढ़ोy taपूर्णांकed. */
	अगर (!crc)
		वापस 1;

	/* No versions at all?  modprobe --क्रमce करोes this. */
	अगर (versindex == 0)
		वापस try_to_क्रमce_load(mod, symname) == 0;

	versions = (व्योम *) sechdrs[versindex].sh_addr;
	num_versions = sechdrs[versindex].sh_size
		/ माप(काष्ठा modversion_info);

	क्रम (i = 0; i < num_versions; i++) अणु
		u32 crcval;

		अगर (म_भेद(versions[i].name, symname) != 0)
			जारी;

		अगर (IS_ENABLED(CONFIG_MODULE_REL_CRCS))
			crcval = resolve_rel_crc(crc);
		अन्यथा
			crcval = *crc;
		अगर (versions[i].crc == crcval)
			वापस 1;
		pr_debug("Found checksum %X vs module %lX\n",
			 crcval, versions[i].crc);
		जाओ bad_version;
	पूर्ण

	/* Broken toolchain. Warn once, then let it go.. */
	pr_warn_once("%s: no symbol version for %s\n", info->name, symname);
	वापस 1;

bad_version:
	pr_warn("%s: disagrees about version of symbol %s\n",
	       info->name, symname);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक check_modकाष्ठा_version(स्थिर काष्ठा load_info *info,
					  काष्ठा module *mod)
अणु
	काष्ठा find_symbol_arg fsa = अणु
		.name	= "module_layout",
		.gplok	= true,
	पूर्ण;

	/*
	 * Since this should be found in kernel (which can't be हटाओd), no
	 * locking is necessary -- use preempt_disable() to placate lockdep.
	 */
	preempt_disable();
	अगर (!find_symbol(&fsa)) अणु
		preempt_enable();
		BUG();
	पूर्ण
	preempt_enable();
	वापस check_version(info, "module_layout", mod, fsa.crc);
पूर्ण

/* First part is kernel version, which we ignore अगर module has crcs. */
अटल अंतरभूत पूर्णांक same_magic(स्थिर अक्षर *amagic, स्थिर अक्षर *bmagic,
			     bool has_crcs)
अणु
	अगर (has_crcs) अणु
		amagic += म_खोज(amagic, " ");
		bmagic += म_खोज(bmagic, " ");
	पूर्ण
	वापस म_भेद(amagic, bmagic) == 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक check_version(स्थिर काष्ठा load_info *info,
				स्थिर अक्षर *symname,
				काष्ठा module *mod,
				स्थिर s32 *crc)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक check_modकाष्ठा_version(स्थिर काष्ठा load_info *info,
					  काष्ठा module *mod)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक same_magic(स्थिर अक्षर *amagic, स्थिर अक्षर *bmagic,
			     bool has_crcs)
अणु
	वापस म_भेद(amagic, bmagic) == 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_MODVERSIONS */

अटल अक्षर *get_modinfo(स्थिर काष्ठा load_info *info, स्थिर अक्षर *tag);
अटल अक्षर *get_next_modinfo(स्थिर काष्ठा load_info *info, स्थिर अक्षर *tag,
			      अक्षर *prev);

अटल पूर्णांक verअगरy_namespace_is_imported(स्थिर काष्ठा load_info *info,
					स्थिर काष्ठा kernel_symbol *sym,
					काष्ठा module *mod)
अणु
	स्थिर अक्षर *namespace;
	अक्षर *imported_namespace;

	namespace = kernel_symbol_namespace(sym);
	अगर (namespace && namespace[0]) अणु
		imported_namespace = get_modinfo(info, "import_ns");
		जबतक (imported_namespace) अणु
			अगर (म_भेद(namespace, imported_namespace) == 0)
				वापस 0;
			imported_namespace = get_next_modinfo(
				info, "import_ns", imported_namespace);
		पूर्ण
#अगर_घोषित CONFIG_MODULE_ALLOW_MISSING_NAMESPACE_IMPORTS
		pr_warn(
#अन्यथा
		pr_err(
#पूर्ण_अगर
			"%s: module uses symbol (%s) from namespace %s, but does not import it.\n",
			mod->name, kernel_symbol_name(sym), namespace);
#अगर_अघोषित CONFIG_MODULE_ALLOW_MISSING_NAMESPACE_IMPORTS
		वापस -EINVAL;
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

अटल bool inherit_taपूर्णांक(काष्ठा module *mod, काष्ठा module *owner)
अणु
	अगर (!owner || !test_bit(TAINT_PROPRIETARY_MODULE, &owner->taपूर्णांकs))
		वापस true;

	अगर (mod->using_gplonly_symbols) अणु
		pr_err("%s: module using GPL-only symbols uses symbols from proprietary module %s.\n",
			mod->name, owner->name);
		वापस false;
	पूर्ण

	अगर (!test_bit(TAINT_PROPRIETARY_MODULE, &mod->taपूर्णांकs)) अणु
		pr_warn("%s: module uses symbols from proprietary module %s, inheriting taint.\n",
			mod->name, owner->name);
		set_bit(TAINT_PROPRIETARY_MODULE, &mod->taपूर्णांकs);
	पूर्ण
	वापस true;
पूर्ण

/* Resolve a symbol क्रम this module.  I.e. अगर we find one, record usage. */
अटल स्थिर काष्ठा kernel_symbol *resolve_symbol(काष्ठा module *mod,
						  स्थिर काष्ठा load_info *info,
						  स्थिर अक्षर *name,
						  अक्षर ownername[])
अणु
	काष्ठा find_symbol_arg fsa = अणु
		.name	= name,
		.gplok	= !(mod->taपूर्णांकs & (1 << TAINT_PROPRIETARY_MODULE)),
		.warn	= true,
	पूर्ण;
	पूर्णांक err;

	/*
	 * The module_mutex should not be a heavily contended lock;
	 * अगर we get the occasional sleep here, we'll go an extra iteration
	 * in the रुको_event_पूर्णांकerruptible(), which is harmless.
	 */
	sched_annotate_sleep();
	mutex_lock(&module_mutex);
	अगर (!find_symbol(&fsa))
		जाओ unlock;

	अगर (fsa.license == GPL_ONLY)
		mod->using_gplonly_symbols = true;

	अगर (!inherit_taपूर्णांक(mod, fsa.owner)) अणु
		fsa.sym = शून्य;
		जाओ getname;
	पूर्ण

	अगर (!check_version(info, name, mod, fsa.crc)) अणु
		fsa.sym = ERR_PTR(-EINVAL);
		जाओ getname;
	पूर्ण

	err = verअगरy_namespace_is_imported(info, fsa.sym, mod);
	अगर (err) अणु
		fsa.sym = ERR_PTR(err);
		जाओ getname;
	पूर्ण

	err = ref_module(mod, fsa.owner);
	अगर (err) अणु
		fsa.sym = ERR_PTR(err);
		जाओ getname;
	पूर्ण

getname:
	/* We must make copy under the lock अगर we failed to get ref. */
	म_नकलन(ownername, module_name(fsa.owner), MODULE_NAME_LEN);
unlock:
	mutex_unlock(&module_mutex);
	वापस fsa.sym;
पूर्ण

अटल स्थिर काष्ठा kernel_symbol *
resolve_symbol_रुको(काष्ठा module *mod,
		    स्थिर काष्ठा load_info *info,
		    स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा kernel_symbol *ksym;
	अक्षर owner[MODULE_NAME_LEN];

	अगर (रुको_event_पूर्णांकerruptible_समयout(module_wq,
			!IS_ERR(ksym = resolve_symbol(mod, info, name, owner))
			|| PTR_ERR(ksym) != -EBUSY,
					     30 * HZ) <= 0) अणु
		pr_warn("%s: gave up waiting for init of module %s.\n",
			mod->name, owner);
	पूर्ण
	वापस ksym;
पूर्ण

/*
 * /sys/module/foo/sections stuff
 * J. Corbet <corbet@lwn.net>
 */
#अगर_घोषित CONFIG_SYSFS

#अगर_घोषित CONFIG_KALLSYMS
अटल अंतरभूत bool sect_empty(स्थिर Elf_Shdr *sect)
अणु
	वापस !(sect->sh_flags & SHF_ALLOC) || sect->sh_size == 0;
पूर्ण

काष्ठा module_sect_attr अणु
	काष्ठा bin_attribute battr;
	अचिन्हित दीर्घ address;
पूर्ण;

काष्ठा module_sect_attrs अणु
	काष्ठा attribute_group grp;
	अचिन्हित पूर्णांक nsections;
	काष्ठा module_sect_attr attrs[];
पूर्ण;

#घोषणा MODULE_SECT_READ_SIZE (3 /* "0x", "\n" */ + (BITS_PER_LONG / 4))
अटल sमाप_प्रकार module_sect_पढ़ो(काष्ठा file *file, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *battr,
				अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	काष्ठा module_sect_attr *sattr =
		container_of(battr, काष्ठा module_sect_attr, battr);
	अक्षर bounce[MODULE_SECT_READ_SIZE + 1];
	माप_प्रकार wrote;

	अगर (pos != 0)
		वापस -EINVAL;

	/*
	 * Since we're a binary पढ़ो handler, we must account क्रम the
	 * trailing NUL byte that प्र_लिखो will ग_लिखो: अगर "buf" is
	 * too small to hold the NUL, or the NUL is exactly the last
	 * byte, the पढ़ो will look like it got truncated by one byte.
	 * Since there is no way to ask प्र_लिखो nicely to not ग_लिखो
	 * the NUL, we have to use a bounce buffer.
	 */
	wrote = scnम_लिखो(bounce, माप(bounce), "0x%px\n",
			 kallsyms_show_value(file->f_cred)
				? (व्योम *)sattr->address : शून्य);
	count = min(count, wrote);
	स_नकल(buf, bounce, count);

	वापस count;
पूर्ण

अटल व्योम मुक्त_sect_attrs(काष्ठा module_sect_attrs *sect_attrs)
अणु
	अचिन्हित पूर्णांक section;

	क्रम (section = 0; section < sect_attrs->nsections; section++)
		kमुक्त(sect_attrs->attrs[section].battr.attr.name);
	kमुक्त(sect_attrs);
पूर्ण

अटल व्योम add_sect_attrs(काष्ठा module *mod, स्थिर काष्ठा load_info *info)
अणु
	अचिन्हित पूर्णांक nloaded = 0, i, size[2];
	काष्ठा module_sect_attrs *sect_attrs;
	काष्ठा module_sect_attr *sattr;
	काष्ठा bin_attribute **gattr;

	/* Count loaded sections and allocate काष्ठाures */
	क्रम (i = 0; i < info->hdr->e_shnum; i++)
		अगर (!sect_empty(&info->sechdrs[i]))
			nloaded++;
	size[0] = ALIGN(काष्ठा_size(sect_attrs, attrs, nloaded),
			माप(sect_attrs->grp.bin_attrs[0]));
	size[1] = (nloaded + 1) * माप(sect_attrs->grp.bin_attrs[0]);
	sect_attrs = kzalloc(size[0] + size[1], GFP_KERNEL);
	अगर (sect_attrs == शून्य)
		वापस;

	/* Setup section attributes. */
	sect_attrs->grp.name = "sections";
	sect_attrs->grp.bin_attrs = (व्योम *)sect_attrs + size[0];

	sect_attrs->nsections = 0;
	sattr = &sect_attrs->attrs[0];
	gattr = &sect_attrs->grp.bin_attrs[0];
	क्रम (i = 0; i < info->hdr->e_shnum; i++) अणु
		Elf_Shdr *sec = &info->sechdrs[i];
		अगर (sect_empty(sec))
			जारी;
		sysfs_bin_attr_init(&sattr->battr);
		sattr->address = sec->sh_addr;
		sattr->battr.attr.name =
			kstrdup(info->secstrings + sec->sh_name, GFP_KERNEL);
		अगर (sattr->battr.attr.name == शून्य)
			जाओ out;
		sect_attrs->nsections++;
		sattr->battr.पढ़ो = module_sect_पढ़ो;
		sattr->battr.size = MODULE_SECT_READ_SIZE;
		sattr->battr.attr.mode = 0400;
		*(gattr++) = &(sattr++)->battr;
	पूर्ण
	*gattr = शून्य;

	अगर (sysfs_create_group(&mod->mkobj.kobj, &sect_attrs->grp))
		जाओ out;

	mod->sect_attrs = sect_attrs;
	वापस;
  out:
	मुक्त_sect_attrs(sect_attrs);
पूर्ण

अटल व्योम हटाओ_sect_attrs(काष्ठा module *mod)
अणु
	अगर (mod->sect_attrs) अणु
		sysfs_हटाओ_group(&mod->mkobj.kobj,
				   &mod->sect_attrs->grp);
		/*
		 * We are positive that no one is using any sect attrs
		 * at this poपूर्णांक.  Deallocate immediately.
		 */
		मुक्त_sect_attrs(mod->sect_attrs);
		mod->sect_attrs = शून्य;
	पूर्ण
पूर्ण

/*
 * /sys/module/foo/notes/.section.name gives contents of SHT_NOTE sections.
 */

काष्ठा module_notes_attrs अणु
	काष्ठा kobject *dir;
	अचिन्हित पूर्णांक notes;
	काष्ठा bin_attribute attrs[];
पूर्ण;

अटल sमाप_प्रकार module_notes_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				 काष्ठा bin_attribute *bin_attr,
				 अक्षर *buf, loff_t pos, माप_प्रकार count)
अणु
	/*
	 * The caller checked the pos and count against our size.
	 */
	स_नकल(buf, bin_attr->निजी + pos, count);
	वापस count;
पूर्ण

अटल व्योम मुक्त_notes_attrs(काष्ठा module_notes_attrs *notes_attrs,
			     अचिन्हित पूर्णांक i)
अणु
	अगर (notes_attrs->dir) अणु
		जबतक (i-- > 0)
			sysfs_हटाओ_bin_file(notes_attrs->dir,
					      &notes_attrs->attrs[i]);
		kobject_put(notes_attrs->dir);
	पूर्ण
	kमुक्त(notes_attrs);
पूर्ण

अटल व्योम add_notes_attrs(काष्ठा module *mod, स्थिर काष्ठा load_info *info)
अणु
	अचिन्हित पूर्णांक notes, loaded, i;
	काष्ठा module_notes_attrs *notes_attrs;
	काष्ठा bin_attribute *nattr;

	/* failed to create section attributes, so can't create notes */
	अगर (!mod->sect_attrs)
		वापस;

	/* Count notes sections and allocate काष्ठाures.  */
	notes = 0;
	क्रम (i = 0; i < info->hdr->e_shnum; i++)
		अगर (!sect_empty(&info->sechdrs[i]) &&
		    (info->sechdrs[i].sh_type == SHT_NOTE))
			++notes;

	अगर (notes == 0)
		वापस;

	notes_attrs = kzalloc(काष्ठा_size(notes_attrs, attrs, notes),
			      GFP_KERNEL);
	अगर (notes_attrs == शून्य)
		वापस;

	notes_attrs->notes = notes;
	nattr = &notes_attrs->attrs[0];
	क्रम (loaded = i = 0; i < info->hdr->e_shnum; ++i) अणु
		अगर (sect_empty(&info->sechdrs[i]))
			जारी;
		अगर (info->sechdrs[i].sh_type == SHT_NOTE) अणु
			sysfs_bin_attr_init(nattr);
			nattr->attr.name = mod->sect_attrs->attrs[loaded].battr.attr.name;
			nattr->attr.mode = S_IRUGO;
			nattr->size = info->sechdrs[i].sh_size;
			nattr->निजी = (व्योम *) info->sechdrs[i].sh_addr;
			nattr->पढ़ो = module_notes_पढ़ो;
			++nattr;
		पूर्ण
		++loaded;
	पूर्ण

	notes_attrs->dir = kobject_create_and_add("notes", &mod->mkobj.kobj);
	अगर (!notes_attrs->dir)
		जाओ out;

	क्रम (i = 0; i < notes; ++i)
		अगर (sysfs_create_bin_file(notes_attrs->dir,
					  &notes_attrs->attrs[i]))
			जाओ out;

	mod->notes_attrs = notes_attrs;
	वापस;

  out:
	मुक्त_notes_attrs(notes_attrs, i);
पूर्ण

अटल व्योम हटाओ_notes_attrs(काष्ठा module *mod)
अणु
	अगर (mod->notes_attrs)
		मुक्त_notes_attrs(mod->notes_attrs, mod->notes_attrs->notes);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम add_sect_attrs(काष्ठा module *mod,
				  स्थिर काष्ठा load_info *info)
अणु
पूर्ण

अटल अंतरभूत व्योम हटाओ_sect_attrs(काष्ठा module *mod)
अणु
पूर्ण

अटल अंतरभूत व्योम add_notes_attrs(काष्ठा module *mod,
				   स्थिर काष्ठा load_info *info)
अणु
पूर्ण

अटल अंतरभूत व्योम हटाओ_notes_attrs(काष्ठा module *mod)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_KALLSYMS */

अटल व्योम del_usage_links(काष्ठा module *mod)
अणु
#अगर_घोषित CONFIG_MODULE_UNLOAD
	काष्ठा module_use *use;

	mutex_lock(&module_mutex);
	list_क्रम_each_entry(use, &mod->target_list, target_list)
		sysfs_हटाओ_link(use->target->holders_dir, mod->name);
	mutex_unlock(&module_mutex);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक add_usage_links(काष्ठा module *mod)
अणु
	पूर्णांक ret = 0;
#अगर_घोषित CONFIG_MODULE_UNLOAD
	काष्ठा module_use *use;

	mutex_lock(&module_mutex);
	list_क्रम_each_entry(use, &mod->target_list, target_list) अणु
		ret = sysfs_create_link(use->target->holders_dir,
					&mod->mkobj.kobj, mod->name);
		अगर (ret)
			अवरोध;
	पूर्ण
	mutex_unlock(&module_mutex);
	अगर (ret)
		del_usage_links(mod);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल व्योम module_हटाओ_modinfo_attrs(काष्ठा module *mod, पूर्णांक end);

अटल पूर्णांक module_add_modinfo_attrs(काष्ठा module *mod)
अणु
	काष्ठा module_attribute *attr;
	काष्ठा module_attribute *temp_attr;
	पूर्णांक error = 0;
	पूर्णांक i;

	mod->modinfo_attrs = kzalloc((माप(काष्ठा module_attribute) *
					(ARRAY_SIZE(modinfo_attrs) + 1)),
					GFP_KERNEL);
	अगर (!mod->modinfo_attrs)
		वापस -ENOMEM;

	temp_attr = mod->modinfo_attrs;
	क्रम (i = 0; (attr = modinfo_attrs[i]); i++) अणु
		अगर (!attr->test || attr->test(mod)) अणु
			स_नकल(temp_attr, attr, माप(*temp_attr));
			sysfs_attr_init(&temp_attr->attr);
			error = sysfs_create_file(&mod->mkobj.kobj,
					&temp_attr->attr);
			अगर (error)
				जाओ error_out;
			++temp_attr;
		पूर्ण
	पूर्ण

	वापस 0;

error_out:
	अगर (i > 0)
		module_हटाओ_modinfo_attrs(mod, --i);
	अन्यथा
		kमुक्त(mod->modinfo_attrs);
	वापस error;
पूर्ण

अटल व्योम module_हटाओ_modinfo_attrs(काष्ठा module *mod, पूर्णांक end)
अणु
	काष्ठा module_attribute *attr;
	पूर्णांक i;

	क्रम (i = 0; (attr = &mod->modinfo_attrs[i]); i++) अणु
		अगर (end >= 0 && i > end)
			अवरोध;
		/* pick a field to test क्रम end of list */
		अगर (!attr->attr.name)
			अवरोध;
		sysfs_हटाओ_file(&mod->mkobj.kobj, &attr->attr);
		अगर (attr->मुक्त)
			attr->मुक्त(mod);
	पूर्ण
	kमुक्त(mod->modinfo_attrs);
पूर्ण

अटल व्योम mod_kobject_put(काष्ठा module *mod)
अणु
	DECLARE_COMPLETION_ONSTACK(c);
	mod->mkobj.kobj_completion = &c;
	kobject_put(&mod->mkobj.kobj);
	रुको_क्रम_completion(&c);
पूर्ण

अटल पूर्णांक mod_sysfs_init(काष्ठा module *mod)
अणु
	पूर्णांक err;
	काष्ठा kobject *kobj;

	अगर (!module_sysfs_initialized) अणु
		pr_err("%s: module sysfs not initialized\n", mod->name);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	kobj = kset_find_obj(module_kset, mod->name);
	अगर (kobj) अणु
		pr_err("%s: module is already loaded\n", mod->name);
		kobject_put(kobj);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	mod->mkobj.mod = mod;

	स_रखो(&mod->mkobj.kobj, 0, माप(mod->mkobj.kobj));
	mod->mkobj.kobj.kset = module_kset;
	err = kobject_init_and_add(&mod->mkobj.kobj, &module_ktype, शून्य,
				   "%s", mod->name);
	अगर (err)
		mod_kobject_put(mod);

out:
	वापस err;
पूर्ण

अटल पूर्णांक mod_sysfs_setup(काष्ठा module *mod,
			   स्थिर काष्ठा load_info *info,
			   काष्ठा kernel_param *kparam,
			   अचिन्हित पूर्णांक num_params)
अणु
	पूर्णांक err;

	err = mod_sysfs_init(mod);
	अगर (err)
		जाओ out;

	mod->holders_dir = kobject_create_and_add("holders", &mod->mkobj.kobj);
	अगर (!mod->holders_dir) अणु
		err = -ENOMEM;
		जाओ out_unreg;
	पूर्ण

	err = module_param_sysfs_setup(mod, kparam, num_params);
	अगर (err)
		जाओ out_unreg_holders;

	err = module_add_modinfo_attrs(mod);
	अगर (err)
		जाओ out_unreg_param;

	err = add_usage_links(mod);
	अगर (err)
		जाओ out_unreg_modinfo_attrs;

	add_sect_attrs(mod, info);
	add_notes_attrs(mod, info);

	वापस 0;

out_unreg_modinfo_attrs:
	module_हटाओ_modinfo_attrs(mod, -1);
out_unreg_param:
	module_param_sysfs_हटाओ(mod);
out_unreg_holders:
	kobject_put(mod->holders_dir);
out_unreg:
	mod_kobject_put(mod);
out:
	वापस err;
पूर्ण

अटल व्योम mod_sysfs_fini(काष्ठा module *mod)
अणु
	हटाओ_notes_attrs(mod);
	हटाओ_sect_attrs(mod);
	mod_kobject_put(mod);
पूर्ण

अटल व्योम init_param_lock(काष्ठा module *mod)
अणु
	mutex_init(&mod->param_lock);
पूर्ण
#अन्यथा /* !CONFIG_SYSFS */

अटल पूर्णांक mod_sysfs_setup(काष्ठा module *mod,
			   स्थिर काष्ठा load_info *info,
			   काष्ठा kernel_param *kparam,
			   अचिन्हित पूर्णांक num_params)
अणु
	वापस 0;
पूर्ण

अटल व्योम mod_sysfs_fini(काष्ठा module *mod)
अणु
पूर्ण

अटल व्योम module_हटाओ_modinfo_attrs(काष्ठा module *mod, पूर्णांक end)
अणु
पूर्ण

अटल व्योम del_usage_links(काष्ठा module *mod)
अणु
पूर्ण

अटल व्योम init_param_lock(काष्ठा module *mod)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SYSFS */

अटल व्योम mod_sysfs_tearकरोwn(काष्ठा module *mod)
अणु
	del_usage_links(mod);
	module_हटाओ_modinfo_attrs(mod, -1);
	module_param_sysfs_हटाओ(mod);
	kobject_put(mod->mkobj.drivers_dir);
	kobject_put(mod->holders_dir);
	mod_sysfs_fini(mod);
पूर्ण

/*
 * LKM RO/NX protection: protect module's text/ro-data
 * from modअगरication and any data from execution.
 *
 * General layout of module is:
 *          [text] [पढ़ो-only-data] [ro-after-init] [writable data]
 * text_size -----^                ^               ^               ^
 * ro_size ------------------------|               |               |
 * ro_after_init_size -----------------------------|               |
 * size -----------------------------------------------------------|
 *
 * These values are always page-aligned (as is base)
 */

/*
 * Since some arches are moving towards PAGE_KERNEL module allocations instead
 * of PAGE_KERNEL_EXEC, keep frob_text() and module_enable_x() outside of the
 * CONFIG_STRICT_MODULE_RWX block below because they are needed regardless of
 * whether we are strict.
 */
#अगर_घोषित CONFIG_ARCH_HAS_STRICT_MODULE_RWX
अटल व्योम frob_text(स्थिर काष्ठा module_layout *layout,
		      पूर्णांक (*set_memory)(अचिन्हित दीर्घ start, पूर्णांक num_pages))
अणु
	BUG_ON((अचिन्हित दीर्घ)layout->base & (PAGE_SIZE-1));
	BUG_ON((अचिन्हित दीर्घ)layout->text_size & (PAGE_SIZE-1));
	set_memory((अचिन्हित दीर्घ)layout->base,
		   layout->text_size >> PAGE_SHIFT);
पूर्ण

अटल व्योम module_enable_x(स्थिर काष्ठा module *mod)
अणु
	frob_text(&mod->core_layout, set_memory_x);
	frob_text(&mod->init_layout, set_memory_x);
पूर्ण
#अन्यथा /* !CONFIG_ARCH_HAS_STRICT_MODULE_RWX */
अटल व्योम module_enable_x(स्थिर काष्ठा module *mod) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HAS_STRICT_MODULE_RWX */

#अगर_घोषित CONFIG_STRICT_MODULE_RWX
अटल व्योम frob_rodata(स्थिर काष्ठा module_layout *layout,
			पूर्णांक (*set_memory)(अचिन्हित दीर्घ start, पूर्णांक num_pages))
अणु
	BUG_ON((अचिन्हित दीर्घ)layout->base & (PAGE_SIZE-1));
	BUG_ON((अचिन्हित दीर्घ)layout->text_size & (PAGE_SIZE-1));
	BUG_ON((अचिन्हित दीर्घ)layout->ro_size & (PAGE_SIZE-1));
	set_memory((अचिन्हित दीर्घ)layout->base + layout->text_size,
		   (layout->ro_size - layout->text_size) >> PAGE_SHIFT);
पूर्ण

अटल व्योम frob_ro_after_init(स्थिर काष्ठा module_layout *layout,
				पूर्णांक (*set_memory)(अचिन्हित दीर्घ start, पूर्णांक num_pages))
अणु
	BUG_ON((अचिन्हित दीर्घ)layout->base & (PAGE_SIZE-1));
	BUG_ON((अचिन्हित दीर्घ)layout->ro_size & (PAGE_SIZE-1));
	BUG_ON((अचिन्हित दीर्घ)layout->ro_after_init_size & (PAGE_SIZE-1));
	set_memory((अचिन्हित दीर्घ)layout->base + layout->ro_size,
		   (layout->ro_after_init_size - layout->ro_size) >> PAGE_SHIFT);
पूर्ण

अटल व्योम frob_writable_data(स्थिर काष्ठा module_layout *layout,
			       पूर्णांक (*set_memory)(अचिन्हित दीर्घ start, पूर्णांक num_pages))
अणु
	BUG_ON((अचिन्हित दीर्घ)layout->base & (PAGE_SIZE-1));
	BUG_ON((अचिन्हित दीर्घ)layout->ro_after_init_size & (PAGE_SIZE-1));
	BUG_ON((अचिन्हित दीर्घ)layout->size & (PAGE_SIZE-1));
	set_memory((अचिन्हित दीर्घ)layout->base + layout->ro_after_init_size,
		   (layout->size - layout->ro_after_init_size) >> PAGE_SHIFT);
पूर्ण

अटल व्योम module_enable_ro(स्थिर काष्ठा module *mod, bool after_init)
अणु
	अगर (!rodata_enabled)
		वापस;

	set_vm_flush_reset_perms(mod->core_layout.base);
	set_vm_flush_reset_perms(mod->init_layout.base);
	frob_text(&mod->core_layout, set_memory_ro);

	frob_rodata(&mod->core_layout, set_memory_ro);
	frob_text(&mod->init_layout, set_memory_ro);
	frob_rodata(&mod->init_layout, set_memory_ro);

	अगर (after_init)
		frob_ro_after_init(&mod->core_layout, set_memory_ro);
पूर्ण

अटल व्योम module_enable_nx(स्थिर काष्ठा module *mod)
अणु
	frob_rodata(&mod->core_layout, set_memory_nx);
	frob_ro_after_init(&mod->core_layout, set_memory_nx);
	frob_writable_data(&mod->core_layout, set_memory_nx);
	frob_rodata(&mod->init_layout, set_memory_nx);
	frob_writable_data(&mod->init_layout, set_memory_nx);
पूर्ण

अटल पूर्णांक module_enक्रमce_rwx_sections(Elf_Ehdr *hdr, Elf_Shdr *sechdrs,
				       अक्षर *secstrings, काष्ठा module *mod)
अणु
	स्थिर अचिन्हित दीर्घ shf_wx = SHF_WRITE|SHF_EXECINSTR;
	पूर्णांक i;

	क्रम (i = 0; i < hdr->e_shnum; i++) अणु
		अगर ((sechdrs[i].sh_flags & shf_wx) == shf_wx) अणु
			pr_err("%s: section %s (index %d) has invalid WRITE|EXEC flags\n",
				mod->name, secstrings + sechdrs[i].sh_name, i);
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा /* !CONFIG_STRICT_MODULE_RWX */
अटल व्योम module_enable_nx(स्थिर काष्ठा module *mod) अणु पूर्ण
अटल व्योम module_enable_ro(स्थिर काष्ठा module *mod, bool after_init) अणुपूर्ण
अटल पूर्णांक module_enक्रमce_rwx_sections(Elf_Ehdr *hdr, Elf_Shdr *sechdrs,
				       अक्षर *secstrings, काष्ठा module *mod)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /*  CONFIG_STRICT_MODULE_RWX */

#अगर_घोषित CONFIG_LIVEPATCH
/*
 * Persist Elf inक्रमmation about a module. Copy the Elf header,
 * section header table, section string table, and symtab section
 * index from info to mod->klp_info.
 */
अटल पूर्णांक copy_module_elf(काष्ठा module *mod, काष्ठा load_info *info)
अणु
	अचिन्हित पूर्णांक size, symndx;
	पूर्णांक ret;

	size = माप(*mod->klp_info);
	mod->klp_info = kदो_स्मृति(size, GFP_KERNEL);
	अगर (mod->klp_info == शून्य)
		वापस -ENOMEM;

	/* Elf header */
	size = माप(mod->klp_info->hdr);
	स_नकल(&mod->klp_info->hdr, info->hdr, size);

	/* Elf section header table */
	size = माप(*info->sechdrs) * info->hdr->e_shnum;
	mod->klp_info->sechdrs = kmemdup(info->sechdrs, size, GFP_KERNEL);
	अगर (mod->klp_info->sechdrs == शून्य) अणु
		ret = -ENOMEM;
		जाओ मुक्त_info;
	पूर्ण

	/* Elf section name string table */
	size = info->sechdrs[info->hdr->e_shstrndx].sh_size;
	mod->klp_info->secstrings = kmemdup(info->secstrings, size, GFP_KERNEL);
	अगर (mod->klp_info->secstrings == शून्य) अणु
		ret = -ENOMEM;
		जाओ मुक्त_sechdrs;
	पूर्ण

	/* Elf symbol section index */
	symndx = info->index.sym;
	mod->klp_info->symndx = symndx;

	/*
	 * For livepatch modules, core_kallsyms.symtab is a complete
	 * copy of the original symbol table. Adjust sh_addr to poपूर्णांक
	 * to core_kallsyms.symtab since the copy of the symtab in module
	 * init memory is मुक्तd at the end of करो_init_module().
	 */
	mod->klp_info->sechdrs[symndx].sh_addr = \
		(अचिन्हित दीर्घ) mod->core_kallsyms.symtab;

	वापस 0;

मुक्त_sechdrs:
	kमुक्त(mod->klp_info->sechdrs);
मुक्त_info:
	kमुक्त(mod->klp_info);
	वापस ret;
पूर्ण

अटल व्योम मुक्त_module_elf(काष्ठा module *mod)
अणु
	kमुक्त(mod->klp_info->sechdrs);
	kमुक्त(mod->klp_info->secstrings);
	kमुक्त(mod->klp_info);
पूर्ण
#अन्यथा /* !CONFIG_LIVEPATCH */
अटल पूर्णांक copy_module_elf(काष्ठा module *mod, काष्ठा load_info *info)
अणु
	वापस 0;
पूर्ण

अटल व्योम मुक्त_module_elf(काष्ठा module *mod)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_LIVEPATCH */

व्योम __weak module_memमुक्त(व्योम *module_region)
अणु
	/*
	 * This memory may be RO, and मुक्तing RO memory in an पूर्णांकerrupt is not
	 * supported by vदो_स्मृति.
	 */
	WARN_ON(in_पूर्णांकerrupt());
	vमुक्त(module_region);
पूर्ण

व्योम __weak module_arch_cleanup(काष्ठा module *mod)
अणु
पूर्ण

व्योम __weak module_arch_मुक्तing_init(काष्ठा module *mod)
अणु
पूर्ण

अटल व्योम cfi_cleanup(काष्ठा module *mod);

/* Free a module, हटाओ from lists, etc. */
अटल व्योम मुक्त_module(काष्ठा module *mod)
अणु
	trace_module_मुक्त(mod);

	mod_sysfs_tearकरोwn(mod);

	/*
	 * We leave it in list to prevent duplicate loads, but make sure
	 * that noone uses it जबतक it's being deस्थिरructed.
	 */
	mutex_lock(&module_mutex);
	mod->state = MODULE_STATE_UNFORMED;
	mutex_unlock(&module_mutex);

	/* Remove dynamic debug info */
	ddebug_हटाओ_module(mod->name);

	/* Arch-specअगरic cleanup. */
	module_arch_cleanup(mod);

	/* Module unload stuff */
	module_unload_मुक्त(mod);

	/* Free any allocated parameters. */
	destroy_params(mod->kp, mod->num_kp);

	अगर (is_livepatch_module(mod))
		मुक्त_module_elf(mod);

	/* Now we can delete it from the lists */
	mutex_lock(&module_mutex);
	/* Unlink carefully: kallsyms could be walking list. */
	list_del_rcu(&mod->list);
	mod_tree_हटाओ(mod);
	/* Remove this module from bug list, this uses list_del_rcu */
	module_bug_cleanup(mod);
	/* Wait क्रम RCU-sched synchronizing beक्रमe releasing mod->list and buglist. */
	synchronize_rcu();
	mutex_unlock(&module_mutex);

	/* Clean up CFI क्रम the module. */
	cfi_cleanup(mod);

	/* This may be empty, but that's OK */
	module_arch_मुक्तing_init(mod);
	module_memमुक्त(mod->init_layout.base);
	kमुक्त(mod->args);
	percpu_modमुक्त(mod);

	/* Free lock-classes; relies on the preceding sync_rcu(). */
	lockdep_मुक्त_key_range(mod->core_layout.base, mod->core_layout.size);

	/* Finally, मुक्त the core (containing the module काष्ठाure) */
	module_memमुक्त(mod->core_layout.base);
पूर्ण

व्योम *__symbol_get(स्थिर अक्षर *symbol)
अणु
	काष्ठा find_symbol_arg fsa = अणु
		.name	= symbol,
		.gplok	= true,
		.warn	= true,
	पूर्ण;

	preempt_disable();
	अगर (!find_symbol(&fsa) || strong_try_module_get(fsa.owner)) अणु
		preempt_enable();
		वापस शून्य;
	पूर्ण
	preempt_enable();
	वापस (व्योम *)kernel_symbol_value(fsa.sym);
पूर्ण
EXPORT_SYMBOL_GPL(__symbol_get);

/*
 * Ensure that an exported symbol [global namespace] करोes not alपढ़ोy exist
 * in the kernel or in some other module's exported symbol table.
 *
 * You must hold the module_mutex.
 */
अटल पूर्णांक verअगरy_exported_symbols(काष्ठा module *mod)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर काष्ठा kernel_symbol *s;
	काष्ठा अणु
		स्थिर काष्ठा kernel_symbol *sym;
		अचिन्हित पूर्णांक num;
	पूर्ण arr[] = अणु
		अणु mod->syms, mod->num_syms पूर्ण,
		अणु mod->gpl_syms, mod->num_gpl_syms पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(arr); i++) अणु
		क्रम (s = arr[i].sym; s < arr[i].sym + arr[i].num; s++) अणु
			काष्ठा find_symbol_arg fsa = अणु
				.name	= kernel_symbol_name(s),
				.gplok	= true,
			पूर्ण;
			अगर (find_symbol(&fsa)) अणु
				pr_err("%s: exports duplicate symbol %s"
				       " (owned by %s)\n",
				       mod->name, kernel_symbol_name(s),
				       module_name(fsa.owner));
				वापस -ENOEXEC;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल bool ignore_undef_symbol(Elf_Half emachine, स्थिर अक्षर *name)
अणु
	/*
	 * On x86, PIC code and Clang non-PIC code may have call foo@PLT. GNU as
	 * beक्रमe 2.37 produces an unreferenced _GLOBAL_OFFSET_TABLE_ on x86-64.
	 * i386 has a similar problem but may not deserve a fix.
	 *
	 * If we ever have to ignore many symbols, consider refactoring the code to
	 * only warn अगर referenced by a relocation.
	 */
	अगर (emachine == EM_386 || emachine == EM_X86_64)
		वापस !म_भेद(name, "_GLOBAL_OFFSET_TABLE_");
	वापस false;
पूर्ण

/* Change all symbols so that st_value encodes the poपूर्णांकer directly. */
अटल पूर्णांक simplअगरy_symbols(काष्ठा module *mod, स्थिर काष्ठा load_info *info)
अणु
	Elf_Shdr *symsec = &info->sechdrs[info->index.sym];
	Elf_Sym *sym = (व्योम *)symsec->sh_addr;
	अचिन्हित दीर्घ secbase;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;
	स्थिर काष्ठा kernel_symbol *ksym;

	क्रम (i = 1; i < symsec->sh_size / माप(Elf_Sym); i++) अणु
		स्थिर अक्षर *name = info->strtab + sym[i].st_name;

		चयन (sym[i].st_shndx) अणु
		हाल SHN_COMMON:
			/* Ignore common symbols */
			अगर (!म_भेदन(name, "__gnu_lto", 9))
				अवरोध;

			/*
			 * We compiled with -fno-common.  These are not
			 * supposed to happen.
			 */
			pr_debug("Common symbol: %s\n", name);
			pr_warn("%s: please compile with -fno-common\n",
			       mod->name);
			ret = -ENOEXEC;
			अवरोध;

		हाल SHN_ABS:
			/* Don't need to करो anything */
			pr_debug("Absolute symbol: 0x%08lx\n",
			       (दीर्घ)sym[i].st_value);
			अवरोध;

		हाल SHN_LIVEPATCH:
			/* Livepatch symbols are resolved by livepatch */
			अवरोध;

		हाल SHN_UNDEF:
			ksym = resolve_symbol_रुको(mod, info, name);
			/* Ok अगर resolved.  */
			अगर (ksym && !IS_ERR(ksym)) अणु
				sym[i].st_value = kernel_symbol_value(ksym);
				अवरोध;
			पूर्ण

			/* Ok अगर weak or ignored.  */
			अगर (!ksym &&
			    (ELF_ST_BIND(sym[i].st_info) == STB_WEAK ||
			     ignore_undef_symbol(info->hdr->e_machine, name)))
				अवरोध;

			ret = PTR_ERR(ksym) ?: -ENOENT;
			pr_warn("%s: Unknown symbol %s (err %d)\n",
				mod->name, name, ret);
			अवरोध;

		शेष:
			/* Divert to percpu allocation अगर a percpu var. */
			अगर (sym[i].st_shndx == info->index.pcpu)
				secbase = (अचिन्हित दीर्घ)mod_percpu(mod);
			अन्यथा
				secbase = info->sechdrs[sym[i].st_shndx].sh_addr;
			sym[i].st_value += secbase;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक apply_relocations(काष्ठा module *mod, स्थिर काष्ठा load_info *info)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	/* Now करो relocations. */
	क्रम (i = 1; i < info->hdr->e_shnum; i++) अणु
		अचिन्हित पूर्णांक infosec = info->sechdrs[i].sh_info;

		/* Not a valid relocation section? */
		अगर (infosec >= info->hdr->e_shnum)
			जारी;

		/* Don't bother with non-allocated sections */
		अगर (!(info->sechdrs[infosec].sh_flags & SHF_ALLOC))
			जारी;

		अगर (info->sechdrs[i].sh_flags & SHF_RELA_LIVEPATCH)
			err = klp_apply_section_relocs(mod, info->sechdrs,
						       info->secstrings,
						       info->strtab,
						       info->index.sym, i,
						       शून्य);
		अन्यथा अगर (info->sechdrs[i].sh_type == SHT_REL)
			err = apply_relocate(info->sechdrs, info->strtab,
					     info->index.sym, i, mod);
		अन्यथा अगर (info->sechdrs[i].sh_type == SHT_RELA)
			err = apply_relocate_add(info->sechdrs, info->strtab,
						 info->index.sym, i, mod);
		अगर (err < 0)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

/* Additional bytes needed by arch in front of inभागidual sections */
अचिन्हित पूर्णांक __weak arch_mod_section_prepend(काष्ठा module *mod,
					     अचिन्हित पूर्णांक section)
अणु
	/* शेष implementation just वापसs zero */
	वापस 0;
पूर्ण

/* Update size with this section: वापस offset. */
अटल दीर्घ get_offset(काष्ठा module *mod, अचिन्हित पूर्णांक *size,
		       Elf_Shdr *sechdr, अचिन्हित पूर्णांक section)
अणु
	दीर्घ ret;

	*size += arch_mod_section_prepend(mod, section);
	ret = ALIGN(*size, sechdr->sh_addralign ?: 1);
	*size = ret + sechdr->sh_size;
	वापस ret;
पूर्ण

अटल bool module_init_layout_section(स्थिर अक्षर *sname)
अणु
#अगर_अघोषित CONFIG_MODULE_UNLOAD
	अगर (module_निकास_section(sname))
		वापस true;
#पूर्ण_अगर
	वापस module_init_section(sname);
पूर्ण

/*
 * Lay out the SHF_ALLOC sections in a way not dissimilar to how ld
 * might -- code, पढ़ो-only data, पढ़ो-ग_लिखो data, small data.  Tally
 * sizes, and place the offsets पूर्णांकo sh_entsize fields: high bit means it
 * beदीर्घs in init.
 */
अटल व्योम layout_sections(काष्ठा module *mod, काष्ठा load_info *info)
अणु
	अटल अचिन्हित दीर्घ स्थिर masks[][2] = अणु
		/*
		 * NOTE: all executable code must be the first section
		 * in this array; otherwise modअगरy the text_size
		 * finder in the two loops below
		 */
		अणु SHF_EXECINSTR | SHF_ALLOC, ARCH_SHF_SMALL पूर्ण,
		अणु SHF_ALLOC, SHF_WRITE | ARCH_SHF_SMALL पूर्ण,
		अणु SHF_RO_AFTER_INIT | SHF_ALLOC, ARCH_SHF_SMALL पूर्ण,
		अणु SHF_WRITE | SHF_ALLOC, ARCH_SHF_SMALL पूर्ण,
		अणु ARCH_SHF_SMALL | SHF_ALLOC, 0 पूर्ण
	पूर्ण;
	अचिन्हित पूर्णांक m, i;

	क्रम (i = 0; i < info->hdr->e_shnum; i++)
		info->sechdrs[i].sh_entsize = ~0UL;

	pr_debug("Core section allocation order:\n");
	क्रम (m = 0; m < ARRAY_SIZE(masks); ++m) अणु
		क्रम (i = 0; i < info->hdr->e_shnum; ++i) अणु
			Elf_Shdr *s = &info->sechdrs[i];
			स्थिर अक्षर *sname = info->secstrings + s->sh_name;

			अगर ((s->sh_flags & masks[m][0]) != masks[m][0]
			    || (s->sh_flags & masks[m][1])
			    || s->sh_entsize != ~0UL
			    || module_init_layout_section(sname))
				जारी;
			s->sh_entsize = get_offset(mod, &mod->core_layout.size, s, i);
			pr_debug("\t%s\n", sname);
		पूर्ण
		चयन (m) अणु
		हाल 0: /* executable */
			mod->core_layout.size = debug_align(mod->core_layout.size);
			mod->core_layout.text_size = mod->core_layout.size;
			अवरोध;
		हाल 1: /* RO: text and ro-data */
			mod->core_layout.size = debug_align(mod->core_layout.size);
			mod->core_layout.ro_size = mod->core_layout.size;
			अवरोध;
		हाल 2: /* RO after init */
			mod->core_layout.size = debug_align(mod->core_layout.size);
			mod->core_layout.ro_after_init_size = mod->core_layout.size;
			अवरोध;
		हाल 4: /* whole core */
			mod->core_layout.size = debug_align(mod->core_layout.size);
			अवरोध;
		पूर्ण
	पूर्ण

	pr_debug("Init section allocation order:\n");
	क्रम (m = 0; m < ARRAY_SIZE(masks); ++m) अणु
		क्रम (i = 0; i < info->hdr->e_shnum; ++i) अणु
			Elf_Shdr *s = &info->sechdrs[i];
			स्थिर अक्षर *sname = info->secstrings + s->sh_name;

			अगर ((s->sh_flags & masks[m][0]) != masks[m][0]
			    || (s->sh_flags & masks[m][1])
			    || s->sh_entsize != ~0UL
			    || !module_init_layout_section(sname))
				जारी;
			s->sh_entsize = (get_offset(mod, &mod->init_layout.size, s, i)
					 | INIT_OFFSET_MASK);
			pr_debug("\t%s\n", sname);
		पूर्ण
		चयन (m) अणु
		हाल 0: /* executable */
			mod->init_layout.size = debug_align(mod->init_layout.size);
			mod->init_layout.text_size = mod->init_layout.size;
			अवरोध;
		हाल 1: /* RO: text and ro-data */
			mod->init_layout.size = debug_align(mod->init_layout.size);
			mod->init_layout.ro_size = mod->init_layout.size;
			अवरोध;
		हाल 2:
			/*
			 * RO after init करोesn't apply to init_layout (only
			 * core_layout), so it just takes the value of ro_size.
			 */
			mod->init_layout.ro_after_init_size = mod->init_layout.ro_size;
			अवरोध;
		हाल 4: /* whole init */
			mod->init_layout.size = debug_align(mod->init_layout.size);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम set_license(काष्ठा module *mod, स्थिर अक्षर *license)
अणु
	अगर (!license)
		license = "unspecified";

	अगर (!license_is_gpl_compatible(license)) अणु
		अगर (!test_taपूर्णांक(TAINT_PROPRIETARY_MODULE))
			pr_warn("%s: module license '%s' taints kernel.\n",
				mod->name, license);
		add_taपूर्णांक_module(mod, TAINT_PROPRIETARY_MODULE,
				 LOCKDEP_NOW_UNRELIABLE);
	पूर्ण
पूर्ण

/* Parse tag=value strings from .modinfo section */
अटल अक्षर *next_string(अक्षर *string, अचिन्हित दीर्घ *secsize)
अणु
	/* Skip non-zero अक्षरs */
	जबतक (string[0]) अणु
		string++;
		अगर ((*secsize)-- <= 1)
			वापस शून्य;
	पूर्ण

	/* Skip any zero padding. */
	जबतक (!string[0]) अणु
		string++;
		अगर ((*secsize)-- <= 1)
			वापस शून्य;
	पूर्ण
	वापस string;
पूर्ण

अटल अक्षर *get_next_modinfo(स्थिर काष्ठा load_info *info, स्थिर अक्षर *tag,
			      अक्षर *prev)
अणु
	अक्षर *p;
	अचिन्हित पूर्णांक taglen = म_माप(tag);
	Elf_Shdr *infosec = &info->sechdrs[info->index.info];
	अचिन्हित दीर्घ size = infosec->sh_size;

	/*
	 * get_modinfo() calls made beक्रमe reग_लिखो_section_headers()
	 * must use sh_offset, as sh_addr isn't set!
	 */
	अक्षर *modinfo = (अक्षर *)info->hdr + infosec->sh_offset;

	अगर (prev) अणु
		size -= prev - modinfo;
		modinfo = next_string(prev, &size);
	पूर्ण

	क्रम (p = modinfo; p; p = next_string(p, &size)) अणु
		अगर (म_भेदन(p, tag, taglen) == 0 && p[taglen] == '=')
			वापस p + taglen + 1;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अक्षर *get_modinfo(स्थिर काष्ठा load_info *info, स्थिर अक्षर *tag)
अणु
	वापस get_next_modinfo(info, tag, शून्य);
पूर्ण

अटल व्योम setup_modinfo(काष्ठा module *mod, काष्ठा load_info *info)
अणु
	काष्ठा module_attribute *attr;
	पूर्णांक i;

	क्रम (i = 0; (attr = modinfo_attrs[i]); i++) अणु
		अगर (attr->setup)
			attr->setup(mod, get_modinfo(info, attr->attr.name));
	पूर्ण
पूर्ण

अटल व्योम मुक्त_modinfo(काष्ठा module *mod)
अणु
	काष्ठा module_attribute *attr;
	पूर्णांक i;

	क्रम (i = 0; (attr = modinfo_attrs[i]); i++) अणु
		अगर (attr->मुक्त)
			attr->मुक्त(mod);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_KALLSYMS

/* Lookup exported symbol in given range of kernel_symbols */
अटल स्थिर काष्ठा kernel_symbol *lookup_exported_symbol(स्थिर अक्षर *name,
							  स्थिर काष्ठा kernel_symbol *start,
							  स्थिर काष्ठा kernel_symbol *stop)
अणु
	वापस द्वा_खोज(name, start, stop - start,
			माप(काष्ठा kernel_symbol), cmp_name);
पूर्ण

अटल पूर्णांक is_exported(स्थिर अक्षर *name, अचिन्हित दीर्घ value,
		       स्थिर काष्ठा module *mod)
अणु
	स्थिर काष्ठा kernel_symbol *ks;
	अगर (!mod)
		ks = lookup_exported_symbol(name, __start___ksymtab, __stop___ksymtab);
	अन्यथा
		ks = lookup_exported_symbol(name, mod->syms, mod->syms + mod->num_syms);

	वापस ks != शून्य && kernel_symbol_value(ks) == value;
पूर्ण

/* As per nm */
अटल अक्षर elf_type(स्थिर Elf_Sym *sym, स्थिर काष्ठा load_info *info)
अणु
	स्थिर Elf_Shdr *sechdrs = info->sechdrs;

	अगर (ELF_ST_BIND(sym->st_info) == STB_WEAK) अणु
		अगर (ELF_ST_TYPE(sym->st_info) == STT_OBJECT)
			वापस 'v';
		अन्यथा
			वापस 'w';
	पूर्ण
	अगर (sym->st_shndx == SHN_UNDEF)
		वापस 'U';
	अगर (sym->st_shndx == SHN_ABS || sym->st_shndx == info->index.pcpu)
		वापस 'a';
	अगर (sym->st_shndx >= SHN_LORESERVE)
		वापस '?';
	अगर (sechdrs[sym->st_shndx].sh_flags & SHF_EXECINSTR)
		वापस 't';
	अगर (sechdrs[sym->st_shndx].sh_flags & SHF_ALLOC
	    && sechdrs[sym->st_shndx].sh_type != SHT_NOBITS) अणु
		अगर (!(sechdrs[sym->st_shndx].sh_flags & SHF_WRITE))
			वापस 'r';
		अन्यथा अगर (sechdrs[sym->st_shndx].sh_flags & ARCH_SHF_SMALL)
			वापस 'g';
		अन्यथा
			वापस 'd';
	पूर्ण
	अगर (sechdrs[sym->st_shndx].sh_type == SHT_NOBITS) अणु
		अगर (sechdrs[sym->st_shndx].sh_flags & ARCH_SHF_SMALL)
			वापस 's';
		अन्यथा
			वापस 'b';
	पूर्ण
	अगर (strstarts(info->secstrings + sechdrs[sym->st_shndx].sh_name,
		      ".debug")) अणु
		वापस 'n';
	पूर्ण
	वापस '?';
पूर्ण

अटल bool is_core_symbol(स्थिर Elf_Sym *src, स्थिर Elf_Shdr *sechdrs,
			अचिन्हित पूर्णांक shnum, अचिन्हित पूर्णांक pcpundx)
अणु
	स्थिर Elf_Shdr *sec;

	अगर (src->st_shndx == SHN_UNDEF
	    || src->st_shndx >= shnum
	    || !src->st_name)
		वापस false;

#अगर_घोषित CONFIG_KALLSYMS_ALL
	अगर (src->st_shndx == pcpundx)
		वापस true;
#पूर्ण_अगर

	sec = sechdrs + src->st_shndx;
	अगर (!(sec->sh_flags & SHF_ALLOC)
#अगर_अघोषित CONFIG_KALLSYMS_ALL
	    || !(sec->sh_flags & SHF_EXECINSTR)
#पूर्ण_अगर
	    || (sec->sh_entsize & INIT_OFFSET_MASK))
		वापस false;

	वापस true;
पूर्ण

/*
 * We only allocate and copy the strings needed by the parts of symtab
 * we keep.  This is simple, but has the effect of making multiple
 * copies of duplicates.  We could be more sophisticated, see
 * linux-kernel thपढ़ो starting with
 * <73defb5e4bca04a6431392cc341112b1@localhost>.
 */
अटल व्योम layout_symtab(काष्ठा module *mod, काष्ठा load_info *info)
अणु
	Elf_Shdr *symsect = info->sechdrs + info->index.sym;
	Elf_Shdr *strsect = info->sechdrs + info->index.str;
	स्थिर Elf_Sym *src;
	अचिन्हित पूर्णांक i, nsrc, ndst, strtab_size = 0;

	/* Put symbol section at end of init part of module. */
	symsect->sh_flags |= SHF_ALLOC;
	symsect->sh_entsize = get_offset(mod, &mod->init_layout.size, symsect,
					 info->index.sym) | INIT_OFFSET_MASK;
	pr_debug("\t%s\n", info->secstrings + symsect->sh_name);

	src = (व्योम *)info->hdr + symsect->sh_offset;
	nsrc = symsect->sh_size / माप(*src);

	/* Compute total space required क्रम the core symbols' strtab. */
	क्रम (ndst = i = 0; i < nsrc; i++) अणु
		अगर (i == 0 || is_livepatch_module(mod) ||
		    is_core_symbol(src+i, info->sechdrs, info->hdr->e_shnum,
				   info->index.pcpu)) अणु
			strtab_size += म_माप(&info->strtab[src[i].st_name])+1;
			ndst++;
		पूर्ण
	पूर्ण

	/* Append room क्रम core symbols at end of core part. */
	info->symoffs = ALIGN(mod->core_layout.size, symsect->sh_addralign ?: 1);
	info->stroffs = mod->core_layout.size = info->symoffs + ndst * माप(Elf_Sym);
	mod->core_layout.size += strtab_size;
	info->core_typeoffs = mod->core_layout.size;
	mod->core_layout.size += ndst * माप(अक्षर);
	mod->core_layout.size = debug_align(mod->core_layout.size);

	/* Put string table section at end of init part of module. */
	strsect->sh_flags |= SHF_ALLOC;
	strsect->sh_entsize = get_offset(mod, &mod->init_layout.size, strsect,
					 info->index.str) | INIT_OFFSET_MASK;
	pr_debug("\t%s\n", info->secstrings + strsect->sh_name);

	/* We'll tack temporary mod_kallsyms on the end. */
	mod->init_layout.size = ALIGN(mod->init_layout.size,
				      __alignof__(काष्ठा mod_kallsyms));
	info->mod_kallsyms_init_off = mod->init_layout.size;
	mod->init_layout.size += माप(काष्ठा mod_kallsyms);
	info->init_typeoffs = mod->init_layout.size;
	mod->init_layout.size += nsrc * माप(अक्षर);
	mod->init_layout.size = debug_align(mod->init_layout.size);
पूर्ण

/*
 * We use the full symtab and strtab which layout_symtab arranged to
 * be appended to the init section.  Later we चयन to the cut-करोwn
 * core-only ones.
 */
अटल व्योम add_kallsyms(काष्ठा module *mod, स्थिर काष्ठा load_info *info)
अणु
	अचिन्हित पूर्णांक i, ndst;
	स्थिर Elf_Sym *src;
	Elf_Sym *dst;
	अक्षर *s;
	Elf_Shdr *symsec = &info->sechdrs[info->index.sym];

	/* Set up to poपूर्णांक पूर्णांकo init section. */
	mod->kallsyms = mod->init_layout.base + info->mod_kallsyms_init_off;

	mod->kallsyms->symtab = (व्योम *)symsec->sh_addr;
	mod->kallsyms->num_symtab = symsec->sh_size / माप(Elf_Sym);
	/* Make sure we get permanent strtab: करोn't use info->strtab. */
	mod->kallsyms->strtab = (व्योम *)info->sechdrs[info->index.str].sh_addr;
	mod->kallsyms->typetab = mod->init_layout.base + info->init_typeoffs;

	/*
	 * Now populate the cut करोwn core kallsyms क्रम after init
	 * and set types up जबतक we still have access to sections.
	 */
	mod->core_kallsyms.symtab = dst = mod->core_layout.base + info->symoffs;
	mod->core_kallsyms.strtab = s = mod->core_layout.base + info->stroffs;
	mod->core_kallsyms.typetab = mod->core_layout.base + info->core_typeoffs;
	src = mod->kallsyms->symtab;
	क्रम (ndst = i = 0; i < mod->kallsyms->num_symtab; i++) अणु
		mod->kallsyms->typetab[i] = elf_type(src + i, info);
		अगर (i == 0 || is_livepatch_module(mod) ||
		    is_core_symbol(src+i, info->sechdrs, info->hdr->e_shnum,
				   info->index.pcpu)) अणु
			mod->core_kallsyms.typetab[ndst] =
			    mod->kallsyms->typetab[i];
			dst[ndst] = src[i];
			dst[ndst++].st_name = s - mod->core_kallsyms.strtab;
			s += strlcpy(s, &mod->kallsyms->strtab[src[i].st_name],
				     KSYM_NAME_LEN) + 1;
		पूर्ण
	पूर्ण
	mod->core_kallsyms.num_symtab = ndst;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम layout_symtab(काष्ठा module *mod, काष्ठा load_info *info)
अणु
पूर्ण

अटल व्योम add_kallsyms(काष्ठा module *mod, स्थिर काष्ठा load_info *info)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_KALLSYMS */

अटल व्योम dynamic_debug_setup(काष्ठा module *mod, काष्ठा _ddebug *debug, अचिन्हित पूर्णांक num)
अणु
	अगर (!debug)
		वापस;
	ddebug_add_module(debug, num, mod->name);
पूर्ण

अटल व्योम dynamic_debug_हटाओ(काष्ठा module *mod, काष्ठा _ddebug *debug)
अणु
	अगर (debug)
		ddebug_हटाओ_module(mod->name);
पूर्ण

व्योम * __weak module_alloc(अचिन्हित दीर्घ size)
अणु
	वापस __vदो_स्मृति_node_range(size, 1, VMALLOC_START, VMALLOC_END,
			GFP_KERNEL, PAGE_KERNEL_EXEC, VM_FLUSH_RESET_PERMS,
			NUMA_NO_NODE, __builtin_वापस_address(0));
पूर्ण

bool __weak module_init_section(स्थिर अक्षर *name)
अणु
	वापस strstarts(name, ".init");
पूर्ण

bool __weak module_निकास_section(स्थिर अक्षर *name)
अणु
	वापस strstarts(name, ".exit");
पूर्ण

#अगर_घोषित CONFIG_DEBUG_KMEMLEAK
अटल व्योम kmemleak_load_module(स्थिर काष्ठा module *mod,
				 स्थिर काष्ठा load_info *info)
अणु
	अचिन्हित पूर्णांक i;

	/* only scan the sections containing data */
	kmemleak_scan_area(mod, माप(काष्ठा module), GFP_KERNEL);

	क्रम (i = 1; i < info->hdr->e_shnum; i++) अणु
		/* Scan all writable sections that's not executable */
		अगर (!(info->sechdrs[i].sh_flags & SHF_ALLOC) ||
		    !(info->sechdrs[i].sh_flags & SHF_WRITE) ||
		    (info->sechdrs[i].sh_flags & SHF_EXECINSTR))
			जारी;

		kmemleak_scan_area((व्योम *)info->sechdrs[i].sh_addr,
				   info->sechdrs[i].sh_size, GFP_KERNEL);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम kmemleak_load_module(स्थिर काष्ठा module *mod,
					स्थिर काष्ठा load_info *info)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MODULE_SIG
अटल पूर्णांक module_sig_check(काष्ठा load_info *info, पूर्णांक flags)
अणु
	पूर्णांक err = -ENODATA;
	स्थिर अचिन्हित दीर्घ markerlen = माप(MODULE_SIG_STRING) - 1;
	स्थिर अक्षर *reason;
	स्थिर व्योम *mod = info->hdr;

	/*
	 * Require flags == 0, as a module with version inक्रमmation
	 * हटाओd is no दीर्घer the module that was चिन्हित
	 */
	अगर (flags == 0 &&
	    info->len > markerlen &&
	    स_भेद(mod + info->len - markerlen, MODULE_SIG_STRING, markerlen) == 0) अणु
		/* We truncate the module to discard the signature */
		info->len -= markerlen;
		err = mod_verअगरy_sig(mod, info);
		अगर (!err) अणु
			info->sig_ok = true;
			वापस 0;
		पूर्ण
	पूर्ण

	/*
	 * We करोn't permit modules to be loaded पूर्णांकo the trusted kernels
	 * without a valid signature on them, but अगर we're not enक्रमcing,
	 * certain errors are non-fatal.
	 */
	चयन (err) अणु
	हाल -ENODATA:
		reason = "unsigned module";
		अवरोध;
	हाल -ENOPKG:
		reason = "module with unsupported crypto";
		अवरोध;
	हाल -ENOKEY:
		reason = "module with unavailable key";
		अवरोध;

	शेष:
		/*
		 * All other errors are fatal, including lack of memory,
		 * unparseable signatures, and signature check failures --
		 * even अगर signatures aren't required.
		 */
		वापस err;
	पूर्ण

	अगर (is_module_sig_enक्रमced()) अणु
		pr_notice("Loading of %s is rejected\n", reason);
		वापस -EKEYREJECTED;
	पूर्ण

	वापस security_locked_करोwn(LOCKDOWN_MODULE_SIGNATURE);
पूर्ण
#अन्यथा /* !CONFIG_MODULE_SIG */
अटल पूर्णांक module_sig_check(काष्ठा load_info *info, पूर्णांक flags)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* !CONFIG_MODULE_SIG */

अटल पूर्णांक validate_section_offset(काष्ठा load_info *info, Elf_Shdr *shdr)
अणु
	अचिन्हित दीर्घ secend;

	/*
	 * Check क्रम both overflow and offset/size being
	 * too large.
	 */
	secend = shdr->sh_offset + shdr->sh_size;
	अगर (secend < shdr->sh_offset || secend > info->len)
		वापस -ENOEXEC;

	वापस 0;
पूर्ण

/*
 * Sanity checks against invalid binaries, wrong arch, weird elf version.
 *
 * Also करो basic validity checks against section offsets and sizes, the
 * section name string table, and the indices used क्रम it (sh_name).
 */
अटल पूर्णांक elf_validity_check(काष्ठा load_info *info)
अणु
	अचिन्हित पूर्णांक i;
	Elf_Shdr *shdr, *strhdr;
	पूर्णांक err;

	अगर (info->len < माप(*(info->hdr)))
		वापस -ENOEXEC;

	अगर (स_भेद(info->hdr->e_ident, ELFMAG, SELFMAG) != 0
	    || info->hdr->e_type != ET_REL
	    || !elf_check_arch(info->hdr)
	    || info->hdr->e_shentsize != माप(Elf_Shdr))
		वापस -ENOEXEC;

	/*
	 * e_shnum is 16 bits, and माप(Elf_Shdr) is
	 * known and small. So e_shnum * माप(Elf_Shdr)
	 * will not overflow अचिन्हित दीर्घ on any platक्रमm.
	 */
	अगर (info->hdr->e_shoff >= info->len
	    || (info->hdr->e_shnum * माप(Elf_Shdr) >
		info->len - info->hdr->e_shoff))
		वापस -ENOEXEC;

	info->sechdrs = (व्योम *)info->hdr + info->hdr->e_shoff;

	/*
	 * Verअगरy अगर the section name table index is valid.
	 */
	अगर (info->hdr->e_shstrndx == SHN_UNDEF
	    || info->hdr->e_shstrndx >= info->hdr->e_shnum)
		वापस -ENOEXEC;

	strhdr = &info->sechdrs[info->hdr->e_shstrndx];
	err = validate_section_offset(info, strhdr);
	अगर (err < 0)
		वापस err;

	/*
	 * The section name table must be NUL-terminated, as required
	 * by the spec. This makes म_भेद and pr_* calls that access
	 * strings in the section safe.
	 */
	info->secstrings = (व्योम *)info->hdr + strhdr->sh_offset;
	अगर (info->secstrings[strhdr->sh_size - 1] != '\0')
		वापस -ENOEXEC;

	/*
	 * The code assumes that section 0 has a length of zero and
	 * an addr of zero, so check क्रम it.
	 */
	अगर (info->sechdrs[0].sh_type != SHT_शून्य
	    || info->sechdrs[0].sh_size != 0
	    || info->sechdrs[0].sh_addr != 0)
		वापस -ENOEXEC;

	क्रम (i = 1; i < info->hdr->e_shnum; i++) अणु
		shdr = &info->sechdrs[i];
		चयन (shdr->sh_type) अणु
		हाल SHT_शून्य:
		हाल SHT_NOBITS:
			जारी;
		हाल SHT_SYMTAB:
			अगर (shdr->sh_link == SHN_UNDEF
			    || shdr->sh_link >= info->hdr->e_shnum)
				वापस -ENOEXEC;
			fallthrough;
		शेष:
			err = validate_section_offset(info, shdr);
			अगर (err < 0) अणु
				pr_err("Invalid ELF section in module (section %u type %u)\n",
					i, shdr->sh_type);
				वापस err;
			पूर्ण

			अगर (shdr->sh_flags & SHF_ALLOC) अणु
				अगर (shdr->sh_name >= strhdr->sh_size) अणु
					pr_err("Invalid ELF section name in module (section %u type %u)\n",
					       i, shdr->sh_type);
					वापस -ENOEXEC;
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा COPY_CHUNK_SIZE (16*PAGE_SIZE)

अटल पूर्णांक copy_chunked_from_user(व्योम *dst, स्थिर व्योम __user *usrc, अचिन्हित दीर्घ len)
अणु
	करो अणु
		अचिन्हित दीर्घ n = min(len, COPY_CHUNK_SIZE);

		अगर (copy_from_user(dst, usrc, n) != 0)
			वापस -EFAULT;
		cond_resched();
		dst += n;
		usrc += n;
		len -= n;
	पूर्ण जबतक (len);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_LIVEPATCH
अटल पूर्णांक check_modinfo_livepatch(काष्ठा module *mod, काष्ठा load_info *info)
अणु
	अगर (get_modinfo(info, "livepatch")) अणु
		mod->klp = true;
		add_taपूर्णांक_module(mod, TAINT_LIVEPATCH, LOCKDEP_STILL_OK);
		pr_notice_once("%s: tainting kernel with TAINT_LIVEPATCH\n",
			       mod->name);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा /* !CONFIG_LIVEPATCH */
अटल पूर्णांक check_modinfo_livepatch(काष्ठा module *mod, काष्ठा load_info *info)
अणु
	अगर (get_modinfo(info, "livepatch")) अणु
		pr_err("%s: module is marked as livepatch module, but livepatch support is disabled",
		       mod->name);
		वापस -ENOEXEC;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_LIVEPATCH */

अटल व्योम check_modinfo_retpoline(काष्ठा module *mod, काष्ठा load_info *info)
अणु
	अगर (retpoline_module_ok(get_modinfo(info, "retpoline")))
		वापस;

	pr_warn("%s: loading module not compiled with retpoline compiler.\n",
		mod->name);
पूर्ण

/* Sets info->hdr and info->len. */
अटल पूर्णांक copy_module_from_user(स्थिर व्योम __user *umod, अचिन्हित दीर्घ len,
				  काष्ठा load_info *info)
अणु
	पूर्णांक err;

	info->len = len;
	अगर (info->len < माप(*(info->hdr)))
		वापस -ENOEXEC;

	err = security_kernel_load_data(LOADING_MODULE, true);
	अगर (err)
		वापस err;

	/* Suck in entire file: we'll want most of it. */
	info->hdr = __vदो_स्मृति(info->len, GFP_KERNEL | __GFP_NOWARN);
	अगर (!info->hdr)
		वापस -ENOMEM;

	अगर (copy_chunked_from_user(info->hdr, umod, info->len) != 0) अणु
		err = -EFAULT;
		जाओ out;
	पूर्ण

	err = security_kernel_post_load_data((अक्षर *)info->hdr, info->len,
					     LOADING_MODULE, "init_module");
out:
	अगर (err)
		vमुक्त(info->hdr);

	वापस err;
पूर्ण

अटल व्योम मुक्त_copy(काष्ठा load_info *info)
अणु
	vमुक्त(info->hdr);
पूर्ण

अटल पूर्णांक reग_लिखो_section_headers(काष्ठा load_info *info, पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक i;

	/* This should always be true, but let's be sure. */
	info->sechdrs[0].sh_addr = 0;

	क्रम (i = 1; i < info->hdr->e_shnum; i++) अणु
		Elf_Shdr *shdr = &info->sechdrs[i];

		/*
		 * Mark all sections sh_addr with their address in the
		 * temporary image.
		 */
		shdr->sh_addr = (माप_प्रकार)info->hdr + shdr->sh_offset;

	पूर्ण

	/* Track but करोn't keep modinfo and version sections. */
	info->sechdrs[info->index.vers].sh_flags &= ~(अचिन्हित दीर्घ)SHF_ALLOC;
	info->sechdrs[info->index.info].sh_flags &= ~(अचिन्हित दीर्घ)SHF_ALLOC;

	वापस 0;
पूर्ण

/*
 * Set up our basic convenience variables (poपूर्णांकers to section headers,
 * search क्रम module section index etc), and करो some basic section
 * verअगरication.
 *
 * Set info->mod to the temporary copy of the module in info->hdr. The final one
 * will be allocated in move_module().
 */
अटल पूर्णांक setup_load_info(काष्ठा load_info *info, पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक i;

	/* Try to find a name early so we can log errors with a module name */
	info->index.info = find_sec(info, ".modinfo");
	अगर (info->index.info)
		info->name = get_modinfo(info, "name");

	/* Find पूर्णांकernal symbols and strings. */
	क्रम (i = 1; i < info->hdr->e_shnum; i++) अणु
		अगर (info->sechdrs[i].sh_type == SHT_SYMTAB) अणु
			info->index.sym = i;
			info->index.str = info->sechdrs[i].sh_link;
			info->strtab = (अक्षर *)info->hdr
				+ info->sechdrs[info->index.str].sh_offset;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (info->index.sym == 0) अणु
		pr_warn("%s: module has no symbols (stripped?)\n",
			info->name ?: "(missing .modinfo section or name field)");
		वापस -ENOEXEC;
	पूर्ण

	info->index.mod = find_sec(info, ".gnu.linkonce.this_module");
	अगर (!info->index.mod) अणु
		pr_warn("%s: No module found in object\n",
			info->name ?: "(missing .modinfo section or name field)");
		वापस -ENOEXEC;
	पूर्ण
	/* This is temporary: poपूर्णांक mod पूर्णांकo copy of data. */
	info->mod = (व्योम *)info->hdr + info->sechdrs[info->index.mod].sh_offset;

	/*
	 * If we didn't load the .modinfo 'name' field earlier, fall back to
	 * on-disk काष्ठा mod 'name' field.
	 */
	अगर (!info->name)
		info->name = info->mod->name;

	अगर (flags & MODULE_INIT_IGNORE_MODVERSIONS)
		info->index.vers = 0; /* Pretend no __versions section! */
	अन्यथा
		info->index.vers = find_sec(info, "__versions");

	info->index.pcpu = find_pcpusec(info);

	वापस 0;
पूर्ण

अटल पूर्णांक check_modinfo(काष्ठा module *mod, काष्ठा load_info *info, पूर्णांक flags)
अणु
	स्थिर अक्षर *modmagic = get_modinfo(info, "vermagic");
	पूर्णांक err;

	अगर (flags & MODULE_INIT_IGNORE_VERMAGIC)
		modmagic = शून्य;

	/* This is allowed: modprobe --क्रमce will invalidate it. */
	अगर (!modmagic) अणु
		err = try_to_क्रमce_load(mod, "bad vermagic");
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (!same_magic(modmagic, vermagic, info->index.vers)) अणु
		pr_err("%s: version magic '%s' should be '%s'\n",
		       info->name, modmagic, vermagic);
		वापस -ENOEXEC;
	पूर्ण

	अगर (!get_modinfo(info, "intree")) अणु
		अगर (!test_taपूर्णांक(TAINT_OOT_MODULE))
			pr_warn("%s: loading out-of-tree module taints kernel.\n",
				mod->name);
		add_taपूर्णांक_module(mod, TAINT_OOT_MODULE, LOCKDEP_STILL_OK);
	पूर्ण

	check_modinfo_retpoline(mod, info);

	अगर (get_modinfo(info, "staging")) अणु
		add_taपूर्णांक_module(mod, TAINT_CRAP, LOCKDEP_STILL_OK);
		pr_warn("%s: module is from the staging directory, the quality "
			"is unknown, you have been warned.\n", mod->name);
	पूर्ण

	err = check_modinfo_livepatch(mod, info);
	अगर (err)
		वापस err;

	/* Set up license info based on the info section */
	set_license(mod, get_modinfo(info, "license"));

	वापस 0;
पूर्ण

अटल पूर्णांक find_module_sections(काष्ठा module *mod, काष्ठा load_info *info)
अणु
	mod->kp = section_objs(info, "__param",
			       माप(*mod->kp), &mod->num_kp);
	mod->syms = section_objs(info, "__ksymtab",
				 माप(*mod->syms), &mod->num_syms);
	mod->crcs = section_addr(info, "__kcrctab");
	mod->gpl_syms = section_objs(info, "__ksymtab_gpl",
				     माप(*mod->gpl_syms),
				     &mod->num_gpl_syms);
	mod->gpl_crcs = section_addr(info, "__kcrctab_gpl");

#अगर_घोषित CONFIG_CONSTRUCTORS
	mod->ctors = section_objs(info, ".ctors",
				  माप(*mod->ctors), &mod->num_ctors);
	अगर (!mod->ctors)
		mod->ctors = section_objs(info, ".init_array",
				माप(*mod->ctors), &mod->num_ctors);
	अन्यथा अगर (find_sec(info, ".init_array")) अणु
		/*
		 * This shouldn't happen with same compiler and binutils
		 * building all parts of the module.
		 */
		pr_warn("%s: has both .ctors and .init_array.\n",
		       mod->name);
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर

	mod->noinstr_text_start = section_objs(info, ".noinstr.text", 1,
						&mod->noinstr_text_size);

#अगर_घोषित CONFIG_TRACEPOINTS
	mod->tracepoपूर्णांकs_ptrs = section_objs(info, "__tracepoints_ptrs",
					     माप(*mod->tracepoपूर्णांकs_ptrs),
					     &mod->num_tracepoपूर्णांकs);
#पूर्ण_अगर
#अगर_घोषित CONFIG_TREE_SRCU
	mod->srcu_काष्ठा_ptrs = section_objs(info, "___srcu_struct_ptrs",
					     माप(*mod->srcu_काष्ठा_ptrs),
					     &mod->num_srcu_काष्ठाs);
#पूर्ण_अगर
#अगर_घोषित CONFIG_BPF_EVENTS
	mod->bpf_raw_events = section_objs(info, "__bpf_raw_tp_map",
					   माप(*mod->bpf_raw_events),
					   &mod->num_bpf_raw_events);
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_INFO_BTF_MODULES
	mod->btf_data = any_section_objs(info, ".BTF", 1, &mod->btf_data_size);
#पूर्ण_अगर
#अगर_घोषित CONFIG_JUMP_LABEL
	mod->jump_entries = section_objs(info, "__jump_table",
					माप(*mod->jump_entries),
					&mod->num_jump_entries);
#पूर्ण_अगर
#अगर_घोषित CONFIG_EVENT_TRACING
	mod->trace_events = section_objs(info, "_ftrace_events",
					 माप(*mod->trace_events),
					 &mod->num_trace_events);
	mod->trace_evals = section_objs(info, "_ftrace_eval_map",
					माप(*mod->trace_evals),
					&mod->num_trace_evals);
#पूर्ण_अगर
#अगर_घोषित CONFIG_TRACING
	mod->trace_bprपूर्णांकk_fmt_start = section_objs(info, "__trace_printk_fmt",
					 माप(*mod->trace_bprपूर्णांकk_fmt_start),
					 &mod->num_trace_bprपूर्णांकk_fmt);
#पूर्ण_अगर
#अगर_घोषित CONFIG_FTRACE_MCOUNT_RECORD
	/* sechdrs[0].sh_size is always zero */
	mod->ftrace_callsites = section_objs(info, FTRACE_CALLSITE_SECTION,
					     माप(*mod->ftrace_callsites),
					     &mod->num_ftrace_callsites);
#पूर्ण_अगर
#अगर_घोषित CONFIG_FUNCTION_ERROR_INJECTION
	mod->ei_funcs = section_objs(info, "_error_injection_whitelist",
					    माप(*mod->ei_funcs),
					    &mod->num_ei_funcs);
#पूर्ण_अगर
#अगर_घोषित CONFIG_KPROBES
	mod->kprobes_text_start = section_objs(info, ".kprobes.text", 1,
						&mod->kprobes_text_size);
	mod->kprobe_blacklist = section_objs(info, "_kprobe_blacklist",
						माप(अचिन्हित दीर्घ),
						&mod->num_kprobe_blacklist);
#पूर्ण_अगर
#अगर_घोषित CONFIG_HAVE_STATIC_CALL_INLINE
	mod->अटल_call_sites = section_objs(info, ".static_call_sites",
					      माप(*mod->अटल_call_sites),
					      &mod->num_अटल_call_sites);
#पूर्ण_अगर
	mod->extable = section_objs(info, "__ex_table",
				    माप(*mod->extable), &mod->num_exentries);

	अगर (section_addr(info, "__obsparm"))
		pr_warn("%s: Ignoring obsolete parameters\n", mod->name);

	info->debug = section_objs(info, "__dyndbg",
				   माप(*info->debug), &info->num_debug);

	वापस 0;
पूर्ण

अटल पूर्णांक move_module(काष्ठा module *mod, काष्ठा load_info *info)
अणु
	पूर्णांक i;
	व्योम *ptr;

	/* Do the allocs. */
	ptr = module_alloc(mod->core_layout.size);
	/*
	 * The poपूर्णांकer to this block is stored in the module काष्ठाure
	 * which is inside the block. Just mark it as not being a
	 * leak.
	 */
	kmemleak_not_leak(ptr);
	अगर (!ptr)
		वापस -ENOMEM;

	स_रखो(ptr, 0, mod->core_layout.size);
	mod->core_layout.base = ptr;

	अगर (mod->init_layout.size) अणु
		ptr = module_alloc(mod->init_layout.size);
		/*
		 * The poपूर्णांकer to this block is stored in the module काष्ठाure
		 * which is inside the block. This block करोesn't need to be
		 * scanned as it contains data and code that will be मुक्तd
		 * after the module is initialized.
		 */
		kmemleak_ignore(ptr);
		अगर (!ptr) अणु
			module_memमुक्त(mod->core_layout.base);
			वापस -ENOMEM;
		पूर्ण
		स_रखो(ptr, 0, mod->init_layout.size);
		mod->init_layout.base = ptr;
	पूर्ण अन्यथा
		mod->init_layout.base = शून्य;

	/* Transfer each section which specअगरies SHF_ALLOC */
	pr_debug("final section addresses:\n");
	क्रम (i = 0; i < info->hdr->e_shnum; i++) अणु
		व्योम *dest;
		Elf_Shdr *shdr = &info->sechdrs[i];

		अगर (!(shdr->sh_flags & SHF_ALLOC))
			जारी;

		अगर (shdr->sh_entsize & INIT_OFFSET_MASK)
			dest = mod->init_layout.base
				+ (shdr->sh_entsize & ~INIT_OFFSET_MASK);
		अन्यथा
			dest = mod->core_layout.base + shdr->sh_entsize;

		अगर (shdr->sh_type != SHT_NOBITS)
			स_नकल(dest, (व्योम *)shdr->sh_addr, shdr->sh_size);
		/* Update sh_addr to poपूर्णांक to copy in image. */
		shdr->sh_addr = (अचिन्हित दीर्घ)dest;
		pr_debug("\t0x%lx %s\n",
			 (दीर्घ)shdr->sh_addr, info->secstrings + shdr->sh_name);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_module_license_and_versions(काष्ठा module *mod)
अणु
	पूर्णांक prev_taपूर्णांक = test_taपूर्णांक(TAINT_PROPRIETARY_MODULE);

	/*
	 * ndiswrapper is under GPL by itself, but loads proprietary modules.
	 * Don't use add_taपूर्णांक_module(), as it would prevent ndiswrapper from
	 * using GPL-only symbols it needs.
	 */
	अगर (म_भेद(mod->name, "ndiswrapper") == 0)
		add_taपूर्णांक(TAINT_PROPRIETARY_MODULE, LOCKDEP_NOW_UNRELIABLE);

	/* driverloader was caught wrongly pretending to be under GPL */
	अगर (म_भेद(mod->name, "driverloader") == 0)
		add_taपूर्णांक_module(mod, TAINT_PROPRIETARY_MODULE,
				 LOCKDEP_NOW_UNRELIABLE);

	/* lve claims to be GPL but upstream won't provide source */
	अगर (म_भेद(mod->name, "lve") == 0)
		add_taपूर्णांक_module(mod, TAINT_PROPRIETARY_MODULE,
				 LOCKDEP_NOW_UNRELIABLE);

	अगर (!prev_taपूर्णांक && test_taपूर्णांक(TAINT_PROPRIETARY_MODULE))
		pr_warn("%s: module license taints kernel.\n", mod->name);

#अगर_घोषित CONFIG_MODVERSIONS
	अगर ((mod->num_syms && !mod->crcs) ||
	    (mod->num_gpl_syms && !mod->gpl_crcs)) अणु
		वापस try_to_क्रमce_load(mod,
					 "no versions for exported symbols");
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम flush_module_icache(स्थिर काष्ठा module *mod)
अणु
	/*
	 * Flush the inकाष्ठाion cache, since we've played with text.
	 * Do it beक्रमe processing of module parameters, so the module
	 * can provide parameter accessor functions of its own.
	 */
	अगर (mod->init_layout.base)
		flush_icache_range((अचिन्हित दीर्घ)mod->init_layout.base,
				   (अचिन्हित दीर्घ)mod->init_layout.base
				   + mod->init_layout.size);
	flush_icache_range((अचिन्हित दीर्घ)mod->core_layout.base,
			   (अचिन्हित दीर्घ)mod->core_layout.base + mod->core_layout.size);
पूर्ण

पूर्णांक __weak module_frob_arch_sections(Elf_Ehdr *hdr,
				     Elf_Shdr *sechdrs,
				     अक्षर *secstrings,
				     काष्ठा module *mod)
अणु
	वापस 0;
पूर्ण

/* module_blacklist is a comma-separated list of module names */
अटल अक्षर *module_blacklist;
अटल bool blacklisted(स्थिर अक्षर *module_name)
अणु
	स्थिर अक्षर *p;
	माप_प्रकार len;

	अगर (!module_blacklist)
		वापस false;

	क्रम (p = module_blacklist; *p; p += len) अणु
		len = म_खोज(p, ",");
		अगर (म_माप(module_name) == len && !स_भेद(module_name, p, len))
			वापस true;
		अगर (p[len] == ',')
			len++;
	पूर्ण
	वापस false;
पूर्ण
core_param(module_blacklist, module_blacklist, अक्षरp, 0400);

अटल काष्ठा module *layout_and_allocate(काष्ठा load_info *info, पूर्णांक flags)
अणु
	काष्ठा module *mod;
	अचिन्हित पूर्णांक ndx;
	पूर्णांक err;

	err = check_modinfo(info->mod, info, flags);
	अगर (err)
		वापस ERR_PTR(err);

	/* Allow arches to frob section contents and sizes.  */
	err = module_frob_arch_sections(info->hdr, info->sechdrs,
					info->secstrings, info->mod);
	अगर (err < 0)
		वापस ERR_PTR(err);

	err = module_enक्रमce_rwx_sections(info->hdr, info->sechdrs,
					  info->secstrings, info->mod);
	अगर (err < 0)
		वापस ERR_PTR(err);

	/* We will करो a special allocation क्रम per-cpu sections later. */
	info->sechdrs[info->index.pcpu].sh_flags &= ~(अचिन्हित दीर्घ)SHF_ALLOC;

	/*
	 * Mark ro_after_init section with SHF_RO_AFTER_INIT so that
	 * layout_sections() can put it in the right place.
	 * Note: ro_after_init sections also have SHF_अणुWRITE,ALLOCपूर्ण set.
	 */
	ndx = find_sec(info, ".data..ro_after_init");
	अगर (ndx)
		info->sechdrs[ndx].sh_flags |= SHF_RO_AFTER_INIT;
	/*
	 * Mark the __jump_table section as ro_after_init as well: these data
	 * काष्ठाures are never modअगरied, with the exception of entries that
	 * refer to code in the __init section, which are annotated as such
	 * at module load समय.
	 */
	ndx = find_sec(info, "__jump_table");
	अगर (ndx)
		info->sechdrs[ndx].sh_flags |= SHF_RO_AFTER_INIT;

	/*
	 * Determine total sizes, and put offsets in sh_entsize.  For now
	 * this is करोne generically; there करोesn't appear to be any
	 * special हालs क्रम the architectures.
	 */
	layout_sections(info->mod, info);
	layout_symtab(info->mod, info);

	/* Allocate and move to the final place */
	err = move_module(info->mod, info);
	अगर (err)
		वापस ERR_PTR(err);

	/* Module has been copied to its final place now: वापस it. */
	mod = (व्योम *)info->sechdrs[info->index.mod].sh_addr;
	kmemleak_load_module(mod, info);
	वापस mod;
पूर्ण

/* mod is no दीर्घer valid after this! */
अटल व्योम module_deallocate(काष्ठा module *mod, काष्ठा load_info *info)
अणु
	percpu_modमुक्त(mod);
	module_arch_मुक्तing_init(mod);
	module_memमुक्त(mod->init_layout.base);
	module_memमुक्त(mod->core_layout.base);
पूर्ण

पूर्णांक __weak module_finalize(स्थिर Elf_Ehdr *hdr,
			   स्थिर Elf_Shdr *sechdrs,
			   काष्ठा module *me)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक post_relocation(काष्ठा module *mod, स्थिर काष्ठा load_info *info)
अणु
	/* Sort exception table now relocations are करोne. */
	sort_extable(mod->extable, mod->extable + mod->num_exentries);

	/* Copy relocated percpu area over. */
	percpu_modcopy(mod, (व्योम *)info->sechdrs[info->index.pcpu].sh_addr,
		       info->sechdrs[info->index.pcpu].sh_size);

	/* Setup kallsyms-specअगरic fields. */
	add_kallsyms(mod, info);

	/* Arch-specअगरic module finalizing. */
	वापस module_finalize(info->hdr, info->sechdrs, mod);
पूर्ण

/* Is this module of this name करोne loading?  No locks held. */
अटल bool finished_loading(स्थिर अक्षर *name)
अणु
	काष्ठा module *mod;
	bool ret;

	/*
	 * The module_mutex should not be a heavily contended lock;
	 * अगर we get the occasional sleep here, we'll go an extra iteration
	 * in the रुको_event_पूर्णांकerruptible(), which is harmless.
	 */
	sched_annotate_sleep();
	mutex_lock(&module_mutex);
	mod = find_module_all(name, म_माप(name), true);
	ret = !mod || mod->state == MODULE_STATE_LIVE;
	mutex_unlock(&module_mutex);

	वापस ret;
पूर्ण

/* Call module स्थिरructors. */
अटल व्योम करो_mod_ctors(काष्ठा module *mod)
अणु
#अगर_घोषित CONFIG_CONSTRUCTORS
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < mod->num_ctors; i++)
		mod->ctors[i]();
#पूर्ण_अगर
पूर्ण

/* For मुक्तing module_init on success, in हाल kallsyms traversing */
काष्ठा mod_initमुक्त अणु
	काष्ठा llist_node node;
	व्योम *module_init;
पूर्ण;

अटल व्योम करो_मुक्त_init(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा llist_node *pos, *n, *list;
	काष्ठा mod_initमुक्त *initमुक्त;

	list = llist_del_all(&init_मुक्त_list);

	synchronize_rcu();

	llist_क्रम_each_safe(pos, n, list) अणु
		initमुक्त = container_of(pos, काष्ठा mod_initमुक्त, node);
		module_memमुक्त(initमुक्त->module_init);
		kमुक्त(initमुक्त);
	पूर्ण
पूर्ण

/*
 * This is where the real work happens.
 *
 * Keep it unअंतरभूतd to provide a reliable अवरोधpoपूर्णांक target, e.g. क्रम the gdb
 * helper command 'lx-symbols'.
 */
अटल noअंतरभूत पूर्णांक करो_init_module(काष्ठा module *mod)
अणु
	पूर्णांक ret = 0;
	काष्ठा mod_initमुक्त *मुक्तinit;

	मुक्तinit = kदो_स्मृति(माप(*मुक्तinit), GFP_KERNEL);
	अगर (!मुक्तinit) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	मुक्तinit->module_init = mod->init_layout.base;

	/*
	 * We want to find out whether @mod uses async during init.  Clear
	 * PF_USED_ASYNC.  async_schedule*() will set it.
	 */
	current->flags &= ~PF_USED_ASYNC;

	करो_mod_ctors(mod);
	/* Start the module */
	अगर (mod->init != शून्य)
		ret = करो_one_initcall(mod->init);
	अगर (ret < 0) अणु
		जाओ fail_मुक्त_मुक्तinit;
	पूर्ण
	अगर (ret > 0) अणु
		pr_warn("%s: '%s'->init suspiciously returned %d, it should "
			"follow 0/-E convention\n"
			"%s: loading module anyway...\n",
			__func__, mod->name, ret, __func__);
		dump_stack();
	पूर्ण

	/* Now it's a first class citizen! */
	mod->state = MODULE_STATE_LIVE;
	blocking_notअगरier_call_chain(&module_notअगरy_list,
				     MODULE_STATE_LIVE, mod);

	/* Delay uevent until module has finished its init routine */
	kobject_uevent(&mod->mkobj.kobj, KOBJ_ADD);

	/*
	 * We need to finish all async code beक्रमe the module init sequence
	 * is करोne.  This has potential to deadlock.  For example, a newly
	 * detected block device can trigger request_module() of the
	 * शेष iosched from async probing task.  Once userland helper
	 * reaches here, async_synchronize_full() will रुको on the async
	 * task रुकोing on request_module() and deadlock.
	 *
	 * This deadlock is aव्योमed by perfomring async_synchronize_full()
	 * अगरf module init queued any async jobs.  This isn't a full
	 * solution as it will deadlock the same अगर module loading from
	 * async jobs nests more than once; however, due to the various
	 * स्थिरraपूर्णांकs, this hack seems to be the best option क्रम now.
	 * Please refer to the following thपढ़ो क्रम details.
	 *
	 * http://thपढ़ो.gmane.org/gmane.linux.kernel/1420814
	 */
	अगर (!mod->async_probe_requested && (current->flags & PF_USED_ASYNC))
		async_synchronize_full();

	ftrace_मुक्त_mem(mod, mod->init_layout.base, mod->init_layout.base +
			mod->init_layout.size);
	mutex_lock(&module_mutex);
	/* Drop initial reference. */
	module_put(mod);
	trim_init_extable(mod);
#अगर_घोषित CONFIG_KALLSYMS
	/* Switch to core kallsyms now init is करोne: kallsyms may be walking! */
	rcu_assign_poपूर्णांकer(mod->kallsyms, &mod->core_kallsyms);
#पूर्ण_अगर
	module_enable_ro(mod, true);
	mod_tree_हटाओ_init(mod);
	module_arch_मुक्तing_init(mod);
	mod->init_layout.base = शून्य;
	mod->init_layout.size = 0;
	mod->init_layout.ro_size = 0;
	mod->init_layout.ro_after_init_size = 0;
	mod->init_layout.text_size = 0;
#अगर_घोषित CONFIG_DEBUG_INFO_BTF_MODULES
	/* .BTF is not SHF_ALLOC and will get हटाओd, so sanitize poपूर्णांकer */
	mod->btf_data = शून्य;
#पूर्ण_अगर
	/*
	 * We want to मुक्त module_init, but be aware that kallsyms may be
	 * walking this with preempt disabled.  In all the failure paths, we
	 * call synchronize_rcu(), but we करोn't want to slow करोwn the success
	 * path. module_memमुक्त() cannot be called in an पूर्णांकerrupt, so करो the
	 * work and call synchronize_rcu() in a work queue.
	 *
	 * Note that module_alloc() on most architectures creates W+X page
	 * mappings which won't be cleaned up until करो_मुक्त_init() runs.  Any
	 * code such as mark_rodata_ro() which depends on those mappings to
	 * be cleaned up needs to sync with the queued work - ie
	 * rcu_barrier()
	 */
	अगर (llist_add(&मुक्तinit->node, &init_मुक्त_list))
		schedule_work(&init_मुक्त_wq);

	mutex_unlock(&module_mutex);
	wake_up_all(&module_wq);

	वापस 0;

fail_मुक्त_मुक्तinit:
	kमुक्त(मुक्तinit);
fail:
	/* Try to protect us from buggy refcounters. */
	mod->state = MODULE_STATE_GOING;
	synchronize_rcu();
	module_put(mod);
	blocking_notअगरier_call_chain(&module_notअगरy_list,
				     MODULE_STATE_GOING, mod);
	klp_module_going(mod);
	ftrace_release_mod(mod);
	मुक्त_module(mod);
	wake_up_all(&module_wq);
	वापस ret;
पूर्ण

अटल पूर्णांक may_init_module(व्योम)
अणु
	अगर (!capable(CAP_SYS_MODULE) || modules_disabled)
		वापस -EPERM;

	वापस 0;
पूर्ण

/*
 * We try to place it in the list now to make sure it's unique beक्रमe
 * we dedicate too many resources.  In particular, temporary percpu
 * memory exhaustion.
 */
अटल पूर्णांक add_unक्रमmed_module(काष्ठा module *mod)
अणु
	पूर्णांक err;
	काष्ठा module *old;

	mod->state = MODULE_STATE_UNFORMED;

again:
	mutex_lock(&module_mutex);
	old = find_module_all(mod->name, म_माप(mod->name), true);
	अगर (old != शून्य) अणु
		अगर (old->state != MODULE_STATE_LIVE) अणु
			/* Wait in हाल it fails to load. */
			mutex_unlock(&module_mutex);
			err = रुको_event_पूर्णांकerruptible(module_wq,
					       finished_loading(mod->name));
			अगर (err)
				जाओ out_unlocked;
			जाओ again;
		पूर्ण
		err = -EEXIST;
		जाओ out;
	पूर्ण
	mod_update_bounds(mod);
	list_add_rcu(&mod->list, &modules);
	mod_tree_insert(mod);
	err = 0;

out:
	mutex_unlock(&module_mutex);
out_unlocked:
	वापस err;
पूर्ण

अटल पूर्णांक complete_क्रमmation(काष्ठा module *mod, काष्ठा load_info *info)
अणु
	पूर्णांक err;

	mutex_lock(&module_mutex);

	/* Find duplicate symbols (must be called under lock). */
	err = verअगरy_exported_symbols(mod);
	अगर (err < 0)
		जाओ out;

	/* This relies on module_mutex क्रम list पूर्णांकegrity. */
	module_bug_finalize(info->hdr, info->sechdrs, mod);

	module_enable_ro(mod, false);
	module_enable_nx(mod);
	module_enable_x(mod);

	/*
	 * Mark state as coming so strong_try_module_get() ignores us,
	 * but kallsyms etc. can see us.
	 */
	mod->state = MODULE_STATE_COMING;
	mutex_unlock(&module_mutex);

	वापस 0;

out:
	mutex_unlock(&module_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक prepare_coming_module(काष्ठा module *mod)
अणु
	पूर्णांक err;

	ftrace_module_enable(mod);
	err = klp_module_coming(mod);
	अगर (err)
		वापस err;

	err = blocking_notअगरier_call_chain_robust(&module_notअगरy_list,
			MODULE_STATE_COMING, MODULE_STATE_GOING, mod);
	err = notअगरier_to_त्रुटि_सं(err);
	अगर (err)
		klp_module_going(mod);

	वापस err;
पूर्ण

अटल पूर्णांक unknown_module_param_cb(अक्षर *param, अक्षर *val, स्थिर अक्षर *modname,
				   व्योम *arg)
अणु
	काष्ठा module *mod = arg;
	पूर्णांक ret;

	अगर (म_भेद(param, "async_probe") == 0) अणु
		mod->async_probe_requested = true;
		वापस 0;
	पूर्ण

	/* Check क्रम magic 'dyndbg' arg */
	ret = ddebug_dyndbg_module_param_cb(param, val, modname);
	अगर (ret != 0)
		pr_warn("%s: unknown parameter '%s' ignored\n", modname, param);
	वापस 0;
पूर्ण

अटल व्योम cfi_init(काष्ठा module *mod);

/*
 * Allocate and load the module: note that size of section 0 is always
 * zero, and we rely on this क्रम optional sections.
 */
अटल पूर्णांक load_module(काष्ठा load_info *info, स्थिर अक्षर __user *uargs,
		       पूर्णांक flags)
अणु
	काष्ठा module *mod;
	दीर्घ err = 0;
	अक्षर *after_dashes;

	/*
	 * Do the signature check (अगर any) first. All that
	 * the signature check needs is info->len, it करोes
	 * not need any of the section info. That can be
	 * set up later. This will minimize the chances
	 * of a corrupt module causing problems beक्रमe
	 * we even get to the signature check.
	 *
	 * The check will also adjust info->len by stripping
	 * off the sig length at the end of the module, making
	 * checks against info->len more correct.
	 */
	err = module_sig_check(info, flags);
	अगर (err)
		जाओ मुक्त_copy;

	/*
	 * Do basic sanity checks against the ELF header and
	 * sections.
	 */
	err = elf_validity_check(info);
	अगर (err) अणु
		pr_err("Module has invalid ELF structures\n");
		जाओ मुक्त_copy;
	पूर्ण

	/*
	 * Everything checks out, so set up the section info
	 * in the info काष्ठाure.
	 */
	err = setup_load_info(info, flags);
	अगर (err)
		जाओ मुक्त_copy;

	/*
	 * Now that we know we have the correct module name, check
	 * अगर it's blacklisted.
	 */
	अगर (blacklisted(info->name)) अणु
		err = -EPERM;
		pr_err("Module %s is blacklisted\n", info->name);
		जाओ मुक्त_copy;
	पूर्ण

	err = reग_लिखो_section_headers(info, flags);
	अगर (err)
		जाओ मुक्त_copy;

	/* Check module काष्ठा version now, beक्रमe we try to use module. */
	अगर (!check_modकाष्ठा_version(info, info->mod)) अणु
		err = -ENOEXEC;
		जाओ मुक्त_copy;
	पूर्ण

	/* Figure out module layout, and allocate all the memory. */
	mod = layout_and_allocate(info, flags);
	अगर (IS_ERR(mod)) अणु
		err = PTR_ERR(mod);
		जाओ मुक्त_copy;
	पूर्ण

	audit_log_kern_module(mod->name);

	/* Reserve our place in the list. */
	err = add_unक्रमmed_module(mod);
	अगर (err)
		जाओ मुक्त_module;

#अगर_घोषित CONFIG_MODULE_SIG
	mod->sig_ok = info->sig_ok;
	अगर (!mod->sig_ok) अणु
		pr_notice_once("%s: module verification failed: signature "
			       "and/or required key missing - tainting "
			       "kernel\n", mod->name);
		add_taपूर्णांक_module(mod, TAINT_UNSIGNED_MODULE, LOCKDEP_STILL_OK);
	पूर्ण
#पूर्ण_अगर

	/* To aव्योम stressing percpu allocator, करो this once we're unique. */
	err = percpu_modalloc(mod, info);
	अगर (err)
		जाओ unlink_mod;

	/* Now module is in final location, initialize linked lists, etc. */
	err = module_unload_init(mod);
	अगर (err)
		जाओ unlink_mod;

	init_param_lock(mod);

	/*
	 * Now we've got everything in the final locations, we can
	 * find optional sections.
	 */
	err = find_module_sections(mod, info);
	अगर (err)
		जाओ मुक्त_unload;

	err = check_module_license_and_versions(mod);
	अगर (err)
		जाओ मुक्त_unload;

	/* Set up MODINFO_ATTR fields */
	setup_modinfo(mod, info);

	/* Fix up syms, so that st_value is a poपूर्णांकer to location. */
	err = simplअगरy_symbols(mod, info);
	अगर (err < 0)
		जाओ मुक्त_modinfo;

	err = apply_relocations(mod, info);
	अगर (err < 0)
		जाओ मुक्त_modinfo;

	err = post_relocation(mod, info);
	अगर (err < 0)
		जाओ मुक्त_modinfo;

	flush_module_icache(mod);

	/* Setup CFI क्रम the module. */
	cfi_init(mod);

	/* Now copy in args */
	mod->args = strndup_user(uargs, ~0UL >> 1);
	अगर (IS_ERR(mod->args)) अणु
		err = PTR_ERR(mod->args);
		जाओ मुक्त_arch_cleanup;
	पूर्ण

	dynamic_debug_setup(mod, info->debug, info->num_debug);

	/* Ftrace init must be called in the MODULE_STATE_UNFORMED state */
	ftrace_module_init(mod);

	/* Finally it's fully क्रमmed, पढ़ोy to start executing. */
	err = complete_क्रमmation(mod, info);
	अगर (err)
		जाओ ddebug_cleanup;

	err = prepare_coming_module(mod);
	अगर (err)
		जाओ bug_cleanup;

	/* Module is पढ़ोy to execute: parsing args may करो that. */
	after_dashes = parse_args(mod->name, mod->args, mod->kp, mod->num_kp,
				  -32768, 32767, mod,
				  unknown_module_param_cb);
	अगर (IS_ERR(after_dashes)) अणु
		err = PTR_ERR(after_dashes);
		जाओ coming_cleanup;
	पूर्ण अन्यथा अगर (after_dashes) अणु
		pr_warn("%s: parameters '%s' after `--' ignored\n",
		       mod->name, after_dashes);
	पूर्ण

	/* Link in to sysfs. */
	err = mod_sysfs_setup(mod, info, mod->kp, mod->num_kp);
	अगर (err < 0)
		जाओ coming_cleanup;

	अगर (is_livepatch_module(mod)) अणु
		err = copy_module_elf(mod, info);
		अगर (err < 0)
			जाओ sysfs_cleanup;
	पूर्ण

	/* Get rid of temporary copy. */
	मुक्त_copy(info);

	/* Done! */
	trace_module_load(mod);

	वापस करो_init_module(mod);

 sysfs_cleanup:
	mod_sysfs_tearकरोwn(mod);
 coming_cleanup:
	mod->state = MODULE_STATE_GOING;
	destroy_params(mod->kp, mod->num_kp);
	blocking_notअगरier_call_chain(&module_notअगरy_list,
				     MODULE_STATE_GOING, mod);
	klp_module_going(mod);
 bug_cleanup:
	mod->state = MODULE_STATE_GOING;
	/* module_bug_cleanup needs module_mutex protection */
	mutex_lock(&module_mutex);
	module_bug_cleanup(mod);
	mutex_unlock(&module_mutex);

 ddebug_cleanup:
	ftrace_release_mod(mod);
	dynamic_debug_हटाओ(mod, info->debug);
	synchronize_rcu();
	kमुक्त(mod->args);
 मुक्त_arch_cleanup:
	cfi_cleanup(mod);
	module_arch_cleanup(mod);
 मुक्त_modinfo:
	मुक्त_modinfo(mod);
 मुक्त_unload:
	module_unload_मुक्त(mod);
 unlink_mod:
	mutex_lock(&module_mutex);
	/* Unlink carefully: kallsyms could be walking list. */
	list_del_rcu(&mod->list);
	mod_tree_हटाओ(mod);
	wake_up_all(&module_wq);
	/* Wait क्रम RCU-sched synchronizing beक्रमe releasing mod->list. */
	synchronize_rcu();
	mutex_unlock(&module_mutex);
 मुक्त_module:
	/* Free lock-classes; relies on the preceding sync_rcu() */
	lockdep_मुक्त_key_range(mod->core_layout.base, mod->core_layout.size);

	module_deallocate(mod, info);
 मुक्त_copy:
	मुक्त_copy(info);
	वापस err;
पूर्ण

SYSCALL_DEFINE3(init_module, व्योम __user *, umod,
		अचिन्हित दीर्घ, len, स्थिर अक्षर __user *, uargs)
अणु
	पूर्णांक err;
	काष्ठा load_info info = अणु पूर्ण;

	err = may_init_module();
	अगर (err)
		वापस err;

	pr_debug("init_module: umod=%p, len=%lu, uargs=%p\n",
	       umod, len, uargs);

	err = copy_module_from_user(umod, len, &info);
	अगर (err)
		वापस err;

	वापस load_module(&info, uargs, 0);
पूर्ण

SYSCALL_DEFINE3(finit_module, पूर्णांक, fd, स्थिर अक्षर __user *, uargs, पूर्णांक, flags)
अणु
	काष्ठा load_info info = अणु पूर्ण;
	व्योम *hdr = शून्य;
	पूर्णांक err;

	err = may_init_module();
	अगर (err)
		वापस err;

	pr_debug("finit_module: fd=%d, uargs=%p, flags=%i\n", fd, uargs, flags);

	अगर (flags & ~(MODULE_INIT_IGNORE_MODVERSIONS
		      |MODULE_INIT_IGNORE_VERMAGIC))
		वापस -EINVAL;

	err = kernel_पढ़ो_file_from_fd(fd, 0, &hdr, पूर्णांक_उच्च, शून्य,
				       READING_MODULE);
	अगर (err < 0)
		वापस err;
	info.hdr = hdr;
	info.len = err;

	वापस load_module(&info, uargs, flags);
पूर्ण

अटल अंतरभूत पूर्णांक within(अचिन्हित दीर्घ addr, व्योम *start, अचिन्हित दीर्घ size)
अणु
	वापस ((व्योम *)addr >= start && (व्योम *)addr < start + size);
पूर्ण

#अगर_घोषित CONFIG_KALLSYMS
/*
 * This ignores the पूर्णांकensely annoying "mapping symbols" found
 * in ARM ELF files: $a, $t and $d.
 */
अटल अंतरभूत पूर्णांक is_arm_mapping_symbol(स्थिर अक्षर *str)
अणु
	अगर (str[0] == '.' && str[1] == 'L')
		वापस true;
	वापस str[0] == '$' && म_अक्षर("axtd", str[1])
	       && (str[2] == '\0' || str[2] == '.');
पूर्ण

अटल स्थिर अक्षर *kallsyms_symbol_name(काष्ठा mod_kallsyms *kallsyms, अचिन्हित पूर्णांक symnum)
अणु
	वापस kallsyms->strtab + kallsyms->symtab[symnum].st_name;
पूर्ण

/*
 * Given a module and address, find the corresponding symbol and वापस its name
 * जबतक providing its size and offset अगर needed.
 */
अटल स्थिर अक्षर *find_kallsyms_symbol(काष्ठा module *mod,
					अचिन्हित दीर्घ addr,
					अचिन्हित दीर्घ *size,
					अचिन्हित दीर्घ *offset)
अणु
	अचिन्हित पूर्णांक i, best = 0;
	अचिन्हित दीर्घ nextval, bestval;
	काष्ठा mod_kallsyms *kallsyms = rcu_dereference_sched(mod->kallsyms);

	/* At worse, next value is at end of module */
	अगर (within_module_init(addr, mod))
		nextval = (अचिन्हित दीर्घ)mod->init_layout.base+mod->init_layout.text_size;
	अन्यथा
		nextval = (अचिन्हित दीर्घ)mod->core_layout.base+mod->core_layout.text_size;

	bestval = kallsyms_symbol_value(&kallsyms->symtab[best]);

	/*
	 * Scan क्रम बंदst preceding symbol, and next symbol. (ELF
	 * starts real symbols at 1).
	 */
	क्रम (i = 1; i < kallsyms->num_symtab; i++) अणु
		स्थिर Elf_Sym *sym = &kallsyms->symtab[i];
		अचिन्हित दीर्घ thisval = kallsyms_symbol_value(sym);

		अगर (sym->st_shndx == SHN_UNDEF)
			जारी;

		/*
		 * We ignore unnamed symbols: they're uninक्रमmative
		 * and inserted at a whim.
		 */
		अगर (*kallsyms_symbol_name(kallsyms, i) == '\0'
		    || is_arm_mapping_symbol(kallsyms_symbol_name(kallsyms, i)))
			जारी;

		अगर (thisval <= addr && thisval > bestval) अणु
			best = i;
			bestval = thisval;
		पूर्ण
		अगर (thisval > addr && thisval < nextval)
			nextval = thisval;
	पूर्ण

	अगर (!best)
		वापस शून्य;

	अगर (size)
		*size = nextval - bestval;
	अगर (offset)
		*offset = addr - bestval;

	वापस kallsyms_symbol_name(kallsyms, best);
पूर्ण

व्योम * __weak dereference_module_function_descriptor(काष्ठा module *mod,
						     व्योम *ptr)
अणु
	वापस ptr;
पूर्ण

/*
 * For kallsyms to ask क्रम address resolution.  शून्य means not found.  Careful
 * not to lock to aव्योम deadlock on oopses, simply disable preemption.
 */
स्थिर अक्षर *module_address_lookup(अचिन्हित दीर्घ addr,
			    अचिन्हित दीर्घ *size,
			    अचिन्हित दीर्घ *offset,
			    अक्षर **modname,
			    अक्षर *namebuf)
अणु
	स्थिर अक्षर *ret = शून्य;
	काष्ठा module *mod;

	preempt_disable();
	mod = __module_address(addr);
	अगर (mod) अणु
		अगर (modname)
			*modname = mod->name;

		ret = find_kallsyms_symbol(mod, addr, size, offset);
	पूर्ण
	/* Make a copy in here where it's safe */
	अगर (ret) अणु
		म_नकलन(namebuf, ret, KSYM_NAME_LEN - 1);
		ret = namebuf;
	पूर्ण
	preempt_enable();

	वापस ret;
पूर्ण

पूर्णांक lookup_module_symbol_name(अचिन्हित दीर्घ addr, अक्षर *symname)
अणु
	काष्ठा module *mod;

	preempt_disable();
	list_क्रम_each_entry_rcu(mod, &modules, list) अणु
		अगर (mod->state == MODULE_STATE_UNFORMED)
			जारी;
		अगर (within_module(addr, mod)) अणु
			स्थिर अक्षर *sym;

			sym = find_kallsyms_symbol(mod, addr, शून्य, शून्य);
			अगर (!sym)
				जाओ out;

			strlcpy(symname, sym, KSYM_NAME_LEN);
			preempt_enable();
			वापस 0;
		पूर्ण
	पूर्ण
out:
	preempt_enable();
	वापस -दुस्फल;
पूर्ण

पूर्णांक lookup_module_symbol_attrs(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *size,
			अचिन्हित दीर्घ *offset, अक्षर *modname, अक्षर *name)
अणु
	काष्ठा module *mod;

	preempt_disable();
	list_क्रम_each_entry_rcu(mod, &modules, list) अणु
		अगर (mod->state == MODULE_STATE_UNFORMED)
			जारी;
		अगर (within_module(addr, mod)) अणु
			स्थिर अक्षर *sym;

			sym = find_kallsyms_symbol(mod, addr, size, offset);
			अगर (!sym)
				जाओ out;
			अगर (modname)
				strlcpy(modname, mod->name, MODULE_NAME_LEN);
			अगर (name)
				strlcpy(name, sym, KSYM_NAME_LEN);
			preempt_enable();
			वापस 0;
		पूर्ण
	पूर्ण
out:
	preempt_enable();
	वापस -दुस्फल;
पूर्ण

पूर्णांक module_get_kallsym(अचिन्हित पूर्णांक symnum, अचिन्हित दीर्घ *value, अक्षर *type,
			अक्षर *name, अक्षर *module_name, पूर्णांक *exported)
अणु
	काष्ठा module *mod;

	preempt_disable();
	list_क्रम_each_entry_rcu(mod, &modules, list) अणु
		काष्ठा mod_kallsyms *kallsyms;

		अगर (mod->state == MODULE_STATE_UNFORMED)
			जारी;
		kallsyms = rcu_dereference_sched(mod->kallsyms);
		अगर (symnum < kallsyms->num_symtab) अणु
			स्थिर Elf_Sym *sym = &kallsyms->symtab[symnum];

			*value = kallsyms_symbol_value(sym);
			*type = kallsyms->typetab[symnum];
			strlcpy(name, kallsyms_symbol_name(kallsyms, symnum), KSYM_NAME_LEN);
			strlcpy(module_name, mod->name, MODULE_NAME_LEN);
			*exported = is_exported(name, *value, mod);
			preempt_enable();
			वापस 0;
		पूर्ण
		symnum -= kallsyms->num_symtab;
	पूर्ण
	preempt_enable();
	वापस -दुस्फल;
पूर्ण

/* Given a module and name of symbol, find and वापस the symbol's value */
अटल अचिन्हित दीर्घ find_kallsyms_symbol_value(काष्ठा module *mod, स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा mod_kallsyms *kallsyms = rcu_dereference_sched(mod->kallsyms);

	क्रम (i = 0; i < kallsyms->num_symtab; i++) अणु
		स्थिर Elf_Sym *sym = &kallsyms->symtab[i];

		अगर (म_भेद(name, kallsyms_symbol_name(kallsyms, i)) == 0 &&
		    sym->st_shndx != SHN_UNDEF)
			वापस kallsyms_symbol_value(sym);
	पूर्ण
	वापस 0;
पूर्ण

/* Look क्रम this name: can be of क्रमm module:name. */
अचिन्हित दीर्घ module_kallsyms_lookup_name(स्थिर अक्षर *name)
अणु
	काष्ठा module *mod;
	अक्षर *colon;
	अचिन्हित दीर्घ ret = 0;

	/* Don't lock: we're in enough trouble alपढ़ोy. */
	preempt_disable();
	अगर ((colon = strnchr(name, MODULE_NAME_LEN, ':')) != शून्य) अणु
		अगर ((mod = find_module_all(name, colon - name, false)) != शून्य)
			ret = find_kallsyms_symbol_value(mod, colon+1);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_rcu(mod, &modules, list) अणु
			अगर (mod->state == MODULE_STATE_UNFORMED)
				जारी;
			अगर ((ret = find_kallsyms_symbol_value(mod, name)) != 0)
				अवरोध;
		पूर्ण
	पूर्ण
	preempt_enable();
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_LIVEPATCH
पूर्णांक module_kallsyms_on_each_symbol(पूर्णांक (*fn)(व्योम *, स्थिर अक्षर *,
					     काष्ठा module *, अचिन्हित दीर्घ),
				   व्योम *data)
अणु
	काष्ठा module *mod;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	mutex_lock(&module_mutex);
	list_क्रम_each_entry(mod, &modules, list) अणु
		/* We hold module_mutex: no need क्रम rcu_dereference_sched */
		काष्ठा mod_kallsyms *kallsyms = mod->kallsyms;

		अगर (mod->state == MODULE_STATE_UNFORMED)
			जारी;
		क्रम (i = 0; i < kallsyms->num_symtab; i++) अणु
			स्थिर Elf_Sym *sym = &kallsyms->symtab[i];

			अगर (sym->st_shndx == SHN_UNDEF)
				जारी;

			ret = fn(data, kallsyms_symbol_name(kallsyms, i),
				 mod, kallsyms_symbol_value(sym));
			अगर (ret != 0)
				अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&module_mutex);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_LIVEPATCH */
#पूर्ण_अगर /* CONFIG_KALLSYMS */

अटल व्योम cfi_init(काष्ठा module *mod)
अणु
#अगर_घोषित CONFIG_CFI_CLANG
	initcall_t *init;
	निकासcall_t *निकास;

	rcu_पढ़ो_lock_sched();
	mod->cfi_check = (cfi_check_fn)
		find_kallsyms_symbol_value(mod, "__cfi_check");
	init = (initcall_t *)
		find_kallsyms_symbol_value(mod, "__cfi_jt_init_module");
	निकास = (निकासcall_t *)
		find_kallsyms_symbol_value(mod, "__cfi_jt_cleanup_module");
	rcu_पढ़ो_unlock_sched();

	/* Fix init/निकास functions to poपूर्णांक to the CFI jump table */
	अगर (init)
		mod->init = *init;
	अगर (निकास)
		mod->निकास = *निकास;

	cfi_module_add(mod, module_addr_min);
#पूर्ण_अगर
पूर्ण

अटल व्योम cfi_cleanup(काष्ठा module *mod)
अणु
#अगर_घोषित CONFIG_CFI_CLANG
	cfi_module_हटाओ(mod, module_addr_min);
#पूर्ण_अगर
पूर्ण

/* Maximum number of अक्षरacters written by module_flags() */
#घोषणा MODULE_FLAGS_BUF_SIZE (TAINT_FLAGS_COUNT + 4)

/* Keep in sync with MODULE_FLAGS_BUF_SIZE !!! */
अटल अक्षर *module_flags(काष्ठा module *mod, अक्षर *buf)
अणु
	पूर्णांक bx = 0;

	BUG_ON(mod->state == MODULE_STATE_UNFORMED);
	अगर (mod->taपूर्णांकs ||
	    mod->state == MODULE_STATE_GOING ||
	    mod->state == MODULE_STATE_COMING) अणु
		buf[bx++] = '(';
		bx += module_flags_taपूर्णांक(mod, buf + bx);
		/* Show a - क्रम module-is-being-unloaded */
		अगर (mod->state == MODULE_STATE_GOING)
			buf[bx++] = '-';
		/* Show a + क्रम module-is-being-loaded */
		अगर (mod->state == MODULE_STATE_COMING)
			buf[bx++] = '+';
		buf[bx++] = ')';
	पूर्ण
	buf[bx] = '\0';

	वापस buf;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
/* Called by the /proc file प्रणाली to वापस a list of modules. */
अटल व्योम *m_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	mutex_lock(&module_mutex);
	वापस seq_list_start(&modules, *pos);
पूर्ण

अटल व्योम *m_next(काष्ठा seq_file *m, व्योम *p, loff_t *pos)
अणु
	वापस seq_list_next(p, &modules, pos);
पूर्ण

अटल व्योम m_stop(काष्ठा seq_file *m, व्योम *p)
अणु
	mutex_unlock(&module_mutex);
पूर्ण

अटल पूर्णांक m_show(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा module *mod = list_entry(p, काष्ठा module, list);
	अक्षर buf[MODULE_FLAGS_BUF_SIZE];
	व्योम *value;

	/* We always ignore unक्रमmed modules. */
	अगर (mod->state == MODULE_STATE_UNFORMED)
		वापस 0;

	seq_म_लिखो(m, "%s %u",
		   mod->name, mod->init_layout.size + mod->core_layout.size);
	prपूर्णांक_unload_info(m, mod);

	/* Inक्रमmative क्रम users. */
	seq_म_लिखो(m, " %s",
		   mod->state == MODULE_STATE_GOING ? "Unloading" :
		   mod->state == MODULE_STATE_COMING ? "Loading" :
		   "Live");
	/* Used by oprofile and other similar tools. */
	value = m->निजी ? शून्य : mod->core_layout.base;
	seq_म_लिखो(m, " 0x%px", value);

	/* Taपूर्णांकs info */
	अगर (mod->taपूर्णांकs)
		seq_म_लिखो(m, " %s", module_flags(mod, buf));

	seq_माला_दो(m, "\n");
	वापस 0;
पूर्ण

/*
 * Format: modulename size refcount deps address
 *
 * Where refcount is a number or -, and deps is a comma-separated list
 * of depends or -.
 */
अटल स्थिर काष्ठा seq_operations modules_op = अणु
	.start	= m_start,
	.next	= m_next,
	.stop	= m_stop,
	.show	= m_show
पूर्ण;

/*
 * This also sets the "private" poपूर्णांकer to non-शून्य अगर the
 * kernel poपूर्णांकers should be hidden (so you can just test
 * "m->private" to see अगर you should keep the values निजी).
 *
 * We use the same logic as क्रम /proc/kallsyms.
 */
अटल पूर्णांक modules_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक err = seq_खोलो(file, &modules_op);

	अगर (!err) अणु
		काष्ठा seq_file *m = file->निजी_data;
		m->निजी = kallsyms_show_value(file->f_cred) ? शून्य : (व्योम *)8ul;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा proc_ops modules_proc_ops = अणु
	.proc_flags	= PROC_ENTRY_PERMANENT,
	.proc_खोलो	= modules_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= seq_release,
पूर्ण;

अटल पूर्णांक __init proc_modules_init(व्योम)
अणु
	proc_create("modules", 0, शून्य, &modules_proc_ops);
	वापस 0;
पूर्ण
module_init(proc_modules_init);
#पूर्ण_अगर

/* Given an address, look क्रम it in the module exception tables. */
स्थिर काष्ठा exception_table_entry *search_module_extables(अचिन्हित दीर्घ addr)
अणु
	स्थिर काष्ठा exception_table_entry *e = शून्य;
	काष्ठा module *mod;

	preempt_disable();
	mod = __module_address(addr);
	अगर (!mod)
		जाओ out;

	अगर (!mod->num_exentries)
		जाओ out;

	e = search_extable(mod->extable,
			   mod->num_exentries,
			   addr);
out:
	preempt_enable();

	/*
	 * Now, अगर we found one, we are running inside it now, hence
	 * we cannot unload the module, hence no refcnt needed.
	 */
	वापस e;
पूर्ण

/**
 * is_module_address() - is this address inside a module?
 * @addr: the address to check.
 *
 * See is_module_text_address() अगर you simply want to see अगर the address
 * is code (not data).
 */
bool is_module_address(अचिन्हित दीर्घ addr)
अणु
	bool ret;

	preempt_disable();
	ret = __module_address(addr) != शून्य;
	preempt_enable();

	वापस ret;
पूर्ण

/**
 * __module_address() - get the module which contains an address.
 * @addr: the address.
 *
 * Must be called with preempt disabled or module mutex held so that
 * module करोesn't get मुक्तd during this.
 */
काष्ठा module *__module_address(अचिन्हित दीर्घ addr)
अणु
	काष्ठा module *mod;

	अगर (addr < module_addr_min || addr > module_addr_max)
		वापस शून्य;

	module_निश्चित_mutex_or_preempt();

	mod = mod_find(addr);
	अगर (mod) अणु
		BUG_ON(!within_module(addr, mod));
		अगर (mod->state == MODULE_STATE_UNFORMED)
			mod = शून्य;
	पूर्ण
	वापस mod;
पूर्ण

/**
 * is_module_text_address() - is this address inside module code?
 * @addr: the address to check.
 *
 * See is_module_address() अगर you simply want to see अगर the address is
 * anywhere in a module.  See kernel_text_address() क्रम testing अगर an
 * address corresponds to kernel or module code.
 */
bool is_module_text_address(अचिन्हित दीर्घ addr)
अणु
	bool ret;

	preempt_disable();
	ret = __module_text_address(addr) != शून्य;
	preempt_enable();

	वापस ret;
पूर्ण

/**
 * __module_text_address() - get the module whose code contains an address.
 * @addr: the address.
 *
 * Must be called with preempt disabled or module mutex held so that
 * module करोesn't get मुक्तd during this.
 */
काष्ठा module *__module_text_address(अचिन्हित दीर्घ addr)
अणु
	काष्ठा module *mod = __module_address(addr);
	अगर (mod) अणु
		/* Make sure it's within the text section. */
		अगर (!within(addr, mod->init_layout.base, mod->init_layout.text_size)
		    && !within(addr, mod->core_layout.base, mod->core_layout.text_size))
			mod = शून्य;
	पूर्ण
	वापस mod;
पूर्ण

/* Don't grab lock, we're oopsing. */
व्योम prपूर्णांक_modules(व्योम)
अणु
	काष्ठा module *mod;
	अक्षर buf[MODULE_FLAGS_BUF_SIZE];

	prपूर्णांकk(KERN_DEFAULT "Modules linked in:");
	/* Most callers should alपढ़ोy have preempt disabled, but make sure */
	preempt_disable();
	list_क्रम_each_entry_rcu(mod, &modules, list) अणु
		अगर (mod->state == MODULE_STATE_UNFORMED)
			जारी;
		pr_cont(" %s%s", mod->name, module_flags(mod, buf));
	पूर्ण
	preempt_enable();
	अगर (last_unloaded_module[0])
		pr_cont(" [last unloaded: %s]", last_unloaded_module);
	pr_cont("\n");
पूर्ण

#अगर_घोषित CONFIG_MODVERSIONS
/*
 * Generate the signature क्रम all relevant module काष्ठाures here.
 * If these change, we करोn't want to try to parse the module.
 */
व्योम module_layout(काष्ठा module *mod,
		   काष्ठा modversion_info *ver,
		   काष्ठा kernel_param *kp,
		   काष्ठा kernel_symbol *ks,
		   काष्ठा tracepoपूर्णांक * स्थिर *tp)
अणु
पूर्ण
EXPORT_SYMBOL(module_layout);
#पूर्ण_अगर
