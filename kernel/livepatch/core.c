<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * core.c - Kernel Live Patching Core
 *
 * Copyright (C) 2014 Seth Jennings <sjenning@redhat.com>
 * Copyright (C) 2014 SUSE
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/livepatch.h>
#समावेश <linux/elf.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/completion.h>
#समावेश <linux/memory.h>
#समावेश <linux/rcupdate.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश "core.h"
#समावेश "patch.h"
#समावेश "state.h"
#समावेश "transition.h"

/*
 * klp_mutex is a coarse lock which serializes access to klp data.  All
 * accesses to klp-related variables and काष्ठाures must have mutex protection,
 * except within the following functions which carefully aव्योम the need क्रम it:
 *
 * - klp_ftrace_handler()
 * - klp_update_patch_state()
 */
DEFINE_MUTEX(klp_mutex);

/*
 * Actively used patches: enabled or in transition. Note that replaced
 * or disabled patches are not listed even though the related kernel
 * module still can be loaded.
 */
LIST_HEAD(klp_patches);

अटल काष्ठा kobject *klp_root_kobj;

अटल bool klp_is_module(काष्ठा klp_object *obj)
अणु
	वापस obj->name;
पूर्ण

/* sets obj->mod अगर object is not vmlinux and module is found */
अटल व्योम klp_find_object_module(काष्ठा klp_object *obj)
अणु
	काष्ठा module *mod;

	अगर (!klp_is_module(obj))
		वापस;

	rcu_पढ़ो_lock_sched();
	/*
	 * We करो not want to block removal of patched modules and thereक्रमe
	 * we करो not take a reference here. The patches are हटाओd by
	 * klp_module_going() instead.
	 */
	mod = find_module(obj->name);
	/*
	 * Do not mess work of klp_module_coming() and klp_module_going().
	 * Note that the patch might still be needed beक्रमe klp_module_going()
	 * is called. Module functions can be called even in the GOING state
	 * until mod->निकास() finishes. This is especially important क्रम
	 * patches that modअगरy semantic of the functions.
	 */
	अगर (mod && mod->klp_alive)
		obj->mod = mod;

	rcu_पढ़ो_unlock_sched();
पूर्ण

अटल bool klp_initialized(व्योम)
अणु
	वापस !!klp_root_kobj;
पूर्ण

अटल काष्ठा klp_func *klp_find_func(काष्ठा klp_object *obj,
				      काष्ठा klp_func *old_func)
अणु
	काष्ठा klp_func *func;

	klp_क्रम_each_func(obj, func) अणु
		अगर ((म_भेद(old_func->old_name, func->old_name) == 0) &&
		    (old_func->old_sympos == func->old_sympos)) अणु
			वापस func;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा klp_object *klp_find_object(काष्ठा klp_patch *patch,
					  काष्ठा klp_object *old_obj)
अणु
	काष्ठा klp_object *obj;

	klp_क्रम_each_object(patch, obj) अणु
		अगर (klp_is_module(old_obj)) अणु
			अगर (klp_is_module(obj) &&
			    म_भेद(old_obj->name, obj->name) == 0) अणु
				वापस obj;
			पूर्ण
		पूर्ण अन्यथा अगर (!klp_is_module(obj)) अणु
			वापस obj;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा klp_find_arg अणु
	स्थिर अक्षर *objname;
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ count;
	अचिन्हित दीर्घ pos;
पूर्ण;

अटल पूर्णांक klp_find_callback(व्योम *data, स्थिर अक्षर *name,
			     काष्ठा module *mod, अचिन्हित दीर्घ addr)
अणु
	काष्ठा klp_find_arg *args = data;

	अगर ((mod && !args->objname) || (!mod && args->objname))
		वापस 0;

	अगर (म_भेद(args->name, name))
		वापस 0;

	अगर (args->objname && म_भेद(args->objname, mod->name))
		वापस 0;

	args->addr = addr;
	args->count++;

	/*
	 * Finish the search when the symbol is found क्रम the desired position
	 * or the position is not defined क्रम a non-unique symbol.
	 */
	अगर ((args->pos && (args->count == args->pos)) ||
	    (!args->pos && (args->count > 1)))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक klp_find_object_symbol(स्थिर अक्षर *objname, स्थिर अक्षर *name,
				  अचिन्हित दीर्घ sympos, अचिन्हित दीर्घ *addr)
अणु
	काष्ठा klp_find_arg args = अणु
		.objname = objname,
		.name = name,
		.addr = 0,
		.count = 0,
		.pos = sympos,
	पूर्ण;

	अगर (objname)
		module_kallsyms_on_each_symbol(klp_find_callback, &args);
	अन्यथा
		kallsyms_on_each_symbol(klp_find_callback, &args);

	/*
	 * Ensure an address was found. If sympos is 0, ensure symbol is unique;
	 * otherwise ensure the symbol position count matches sympos.
	 */
	अगर (args.addr == 0)
		pr_err("symbol '%s' not found in symbol table\n", name);
	अन्यथा अगर (args.count > 1 && sympos == 0) अणु
		pr_err("unresolvable ambiguity for symbol '%s' in object '%s'\n",
		       name, objname);
	पूर्ण अन्यथा अगर (sympos != args.count && sympos > 0) अणु
		pr_err("symbol position %lu for symbol '%s' in object '%s' not found\n",
		       sympos, name, objname ? objname : "vmlinux");
	पूर्ण अन्यथा अणु
		*addr = args.addr;
		वापस 0;
	पूर्ण

	*addr = 0;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक klp_resolve_symbols(Elf64_Shdr *sechdrs, स्थिर अक्षर *strtab,
			       अचिन्हित पूर्णांक symndx, Elf_Shdr *relasec,
			       स्थिर अक्षर *sec_objname)
अणु
	पूर्णांक i, cnt, ret;
	अक्षर sym_objname[MODULE_NAME_LEN];
	अक्षर sym_name[KSYM_NAME_LEN];
	Elf_Rela *relas;
	Elf_Sym *sym;
	अचिन्हित दीर्घ sympos, addr;
	bool sym_vmlinux;
	bool sec_vmlinux = !म_भेद(sec_objname, "vmlinux");

	/*
	 * Since the field widths क्रम sym_objname and sym_name in the माला_पूछो()
	 * call are hard-coded and correspond to MODULE_NAME_LEN and
	 * KSYM_NAME_LEN respectively, we must make sure that MODULE_NAME_LEN
	 * and KSYM_NAME_LEN have the values we expect them to have.
	 *
	 * Because the value of MODULE_NAME_LEN can dअगरfer among architectures,
	 * we use the smallest/strictest upper bound possible (56, based on
	 * the current definition of MODULE_NAME_LEN) to prevent overflows.
	 */
	BUILD_BUG_ON(MODULE_NAME_LEN < 56 || KSYM_NAME_LEN != 128);

	relas = (Elf_Rela *) relasec->sh_addr;
	/* For each rela in this klp relocation section */
	क्रम (i = 0; i < relasec->sh_size / माप(Elf_Rela); i++) अणु
		sym = (Elf64_Sym *)sechdrs[symndx].sh_addr + ELF_R_SYM(relas[i].r_info);
		अगर (sym->st_shndx != SHN_LIVEPATCH) अणु
			pr_err("symbol %s is not marked as a livepatch symbol\n",
			       strtab + sym->st_name);
			वापस -EINVAL;
		पूर्ण

		/* Format: .klp.sym.sym_objname.sym_name,sympos */
		cnt = माला_पूछो(strtab + sym->st_name,
			     ".klp.sym.%55[^.].%127[^,],%lu",
			     sym_objname, sym_name, &sympos);
		अगर (cnt != 3) अणु
			pr_err("symbol %s has an incorrectly formatted name\n",
			       strtab + sym->st_name);
			वापस -EINVAL;
		पूर्ण

		sym_vmlinux = !म_भेद(sym_objname, "vmlinux");

		/*
		 * Prevent module-specअगरic KLP rela sections from referencing
		 * vmlinux symbols.  This helps prevent ordering issues with
		 * module special section initializations.  Presumably such
		 * symbols are exported and normal relas can be used instead.
		 */
		अगर (!sec_vmlinux && sym_vmlinux) अणु
			pr_err("invalid access to vmlinux symbol '%s' from module-specific livepatch relocation section",
			       sym_name);
			वापस -EINVAL;
		पूर्ण

		/* klp_find_object_symbol() treats a शून्य objname as vmlinux */
		ret = klp_find_object_symbol(sym_vmlinux ? शून्य : sym_objname,
					     sym_name, sympos, &addr);
		अगर (ret)
			वापस ret;

		sym->st_value = addr;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * At a high-level, there are two types of klp relocation sections: those which
 * reference symbols which live in vmlinux; and those which reference symbols
 * which live in other modules.  This function is called क्रम both types:
 *
 * 1) When a klp module itself loads, the module code calls this function to
 *    ग_लिखो vmlinux-specअगरic klp relocations (.klp.rela.vmlinux.* sections).
 *    These relocations are written to the klp module text to allow the patched
 *    code/data to reference unexported vmlinux symbols.  They're written as
 *    early as possible to ensure that other module init code (.e.g.,
 *    jump_label_apply_nops) can access any unexported vmlinux symbols which
 *    might be referenced by the klp module's special sections.
 *
 * 2) When a to-be-patched module loads -- or is alपढ़ोy loaded when a
 *    corresponding klp module loads -- klp code calls this function to ग_लिखो
 *    module-specअगरic klp relocations (.klp.rela.अणुmoduleपूर्ण.* sections).  These
 *    are written to the klp module text to allow the patched code/data to
 *    reference symbols which live in the to-be-patched module or one of its
 *    module dependencies.  Exported symbols are supported, in addition to
 *    unexported symbols, in order to enable late module patching, which allows
 *    the to-be-patched module to be loaded and patched someसमय *after* the
 *    klp module is loaded.
 */
पूर्णांक klp_apply_section_relocs(काष्ठा module *pmod, Elf_Shdr *sechdrs,
			     स्थिर अक्षर *shstrtab, स्थिर अक्षर *strtab,
			     अचिन्हित पूर्णांक symndx, अचिन्हित पूर्णांक secndx,
			     स्थिर अक्षर *objname)
अणु
	पूर्णांक cnt, ret;
	अक्षर sec_objname[MODULE_NAME_LEN];
	Elf_Shdr *sec = sechdrs + secndx;

	/*
	 * Format: .klp.rela.sec_objname.section_name
	 * See comment in klp_resolve_symbols() क्रम an explanation
	 * of the selected field width value.
	 */
	cnt = माला_पूछो(shstrtab + sec->sh_name, ".klp.rela.%55[^.]",
		     sec_objname);
	अगर (cnt != 1) अणु
		pr_err("section %s has an incorrectly formatted name\n",
		       shstrtab + sec->sh_name);
		वापस -EINVAL;
	पूर्ण

	अगर (म_भेद(objname ? objname : "vmlinux", sec_objname))
		वापस 0;

	ret = klp_resolve_symbols(sechdrs, strtab, symndx, sec, sec_objname);
	अगर (ret)
		वापस ret;

	वापस apply_relocate_add(sechdrs, strtab, symndx, secndx, pmod);
पूर्ण

/*
 * Sysfs Interface
 *
 * /sys/kernel/livepatch
 * /sys/kernel/livepatch/<patch>
 * /sys/kernel/livepatch/<patch>/enabled
 * /sys/kernel/livepatch/<patch>/transition
 * /sys/kernel/livepatch/<patch>/क्रमce
 * /sys/kernel/livepatch/<patch>/<object>
 * /sys/kernel/livepatch/<patch>/<object>/<function,sympos>
 */
अटल पूर्णांक __klp_disable_patch(काष्ठा klp_patch *patch);

अटल sमाप_प्रकार enabled_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा klp_patch *patch;
	पूर्णांक ret;
	bool enabled;

	ret = kstrtobool(buf, &enabled);
	अगर (ret)
		वापस ret;

	patch = container_of(kobj, काष्ठा klp_patch, kobj);

	mutex_lock(&klp_mutex);

	अगर (patch->enabled == enabled) अणु
		/* alपढ़ोy in requested state */
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * Allow to reverse a pending transition in both ways. It might be
	 * necessary to complete the transition without क्रमcing and अवरोधing
	 * the प्रणाली पूर्णांकegrity.
	 *
	 * Do not allow to re-enable a disabled patch.
	 */
	अगर (patch == klp_transition_patch)
		klp_reverse_transition();
	अन्यथा अगर (!enabled)
		ret = __klp_disable_patch(patch);
	अन्यथा
		ret = -EINVAL;

out:
	mutex_unlock(&klp_mutex);

	अगर (ret)
		वापस ret;
	वापस count;
पूर्ण

अटल sमाप_प्रकार enabled_show(काष्ठा kobject *kobj,
			    काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा klp_patch *patch;

	patch = container_of(kobj, काष्ठा klp_patch, kobj);
	वापस snम_लिखो(buf, PAGE_SIZE-1, "%d\n", patch->enabled);
पूर्ण

अटल sमाप_प्रकार transition_show(काष्ठा kobject *kobj,
			       काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा klp_patch *patch;

	patch = container_of(kobj, काष्ठा klp_patch, kobj);
	वापस snम_लिखो(buf, PAGE_SIZE-1, "%d\n",
			patch == klp_transition_patch);
पूर्ण

अटल sमाप_प्रकार क्रमce_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा klp_patch *patch;
	पूर्णांक ret;
	bool val;

	ret = kstrtobool(buf, &val);
	अगर (ret)
		वापस ret;

	अगर (!val)
		वापस count;

	mutex_lock(&klp_mutex);

	patch = container_of(kobj, काष्ठा klp_patch, kobj);
	अगर (patch != klp_transition_patch) अणु
		mutex_unlock(&klp_mutex);
		वापस -EINVAL;
	पूर्ण

	klp_क्रमce_transition();

	mutex_unlock(&klp_mutex);

	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute enabled_kobj_attr = __ATTR_RW(enabled);
अटल काष्ठा kobj_attribute transition_kobj_attr = __ATTR_RO(transition);
अटल काष्ठा kobj_attribute क्रमce_kobj_attr = __ATTR_WO(क्रमce);
अटल काष्ठा attribute *klp_patch_attrs[] = अणु
	&enabled_kobj_attr.attr,
	&transition_kobj_attr.attr,
	&क्रमce_kobj_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(klp_patch);

अटल व्योम klp_मुक्त_object_dynamic(काष्ठा klp_object *obj)
अणु
	kमुक्त(obj->name);
	kमुक्त(obj);
पूर्ण

अटल व्योम klp_init_func_early(काष्ठा klp_object *obj,
				काष्ठा klp_func *func);
अटल व्योम klp_init_object_early(काष्ठा klp_patch *patch,
				  काष्ठा klp_object *obj);

अटल काष्ठा klp_object *klp_alloc_object_dynamic(स्थिर अक्षर *name,
						   काष्ठा klp_patch *patch)
अणु
	काष्ठा klp_object *obj;

	obj = kzalloc(माप(*obj), GFP_KERNEL);
	अगर (!obj)
		वापस शून्य;

	अगर (name) अणु
		obj->name = kstrdup(name, GFP_KERNEL);
		अगर (!obj->name) अणु
			kमुक्त(obj);
			वापस शून्य;
		पूर्ण
	पूर्ण

	klp_init_object_early(patch, obj);
	obj->dynamic = true;

	वापस obj;
पूर्ण

अटल व्योम klp_मुक्त_func_nop(काष्ठा klp_func *func)
अणु
	kमुक्त(func->old_name);
	kमुक्त(func);
पूर्ण

अटल काष्ठा klp_func *klp_alloc_func_nop(काष्ठा klp_func *old_func,
					   काष्ठा klp_object *obj)
अणु
	काष्ठा klp_func *func;

	func = kzalloc(माप(*func), GFP_KERNEL);
	अगर (!func)
		वापस शून्य;

	अगर (old_func->old_name) अणु
		func->old_name = kstrdup(old_func->old_name, GFP_KERNEL);
		अगर (!func->old_name) अणु
			kमुक्त(func);
			वापस शून्य;
		पूर्ण
	पूर्ण

	klp_init_func_early(obj, func);
	/*
	 * func->new_func is same as func->old_func. These addresses are
	 * set when the object is loaded, see klp_init_object_loaded().
	 */
	func->old_sympos = old_func->old_sympos;
	func->nop = true;

	वापस func;
पूर्ण

अटल पूर्णांक klp_add_object_nops(काष्ठा klp_patch *patch,
			       काष्ठा klp_object *old_obj)
अणु
	काष्ठा klp_object *obj;
	काष्ठा klp_func *func, *old_func;

	obj = klp_find_object(patch, old_obj);

	अगर (!obj) अणु
		obj = klp_alloc_object_dynamic(old_obj->name, patch);
		अगर (!obj)
			वापस -ENOMEM;
	पूर्ण

	klp_क्रम_each_func(old_obj, old_func) अणु
		func = klp_find_func(obj, old_func);
		अगर (func)
			जारी;

		func = klp_alloc_func_nop(old_func, obj);
		अगर (!func)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Add 'nop' functions which simply वापस to the caller to run
 * the original function. The 'nop' functions are added to a
 * patch to facilitate a 'replace' mode.
 */
अटल पूर्णांक klp_add_nops(काष्ठा klp_patch *patch)
अणु
	काष्ठा klp_patch *old_patch;
	काष्ठा klp_object *old_obj;

	klp_क्रम_each_patch(old_patch) अणु
		klp_क्रम_each_object(old_patch, old_obj) अणु
			पूर्णांक err;

			err = klp_add_object_nops(patch, old_obj);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम klp_kobj_release_patch(काष्ठा kobject *kobj)
अणु
	काष्ठा klp_patch *patch;

	patch = container_of(kobj, काष्ठा klp_patch, kobj);
	complete(&patch->finish);
पूर्ण

अटल काष्ठा kobj_type klp_ktype_patch = अणु
	.release = klp_kobj_release_patch,
	.sysfs_ops = &kobj_sysfs_ops,
	.शेष_groups = klp_patch_groups,
पूर्ण;

अटल व्योम klp_kobj_release_object(काष्ठा kobject *kobj)
अणु
	काष्ठा klp_object *obj;

	obj = container_of(kobj, काष्ठा klp_object, kobj);

	अगर (obj->dynamic)
		klp_मुक्त_object_dynamic(obj);
पूर्ण

अटल काष्ठा kobj_type klp_ktype_object = अणु
	.release = klp_kobj_release_object,
	.sysfs_ops = &kobj_sysfs_ops,
पूर्ण;

अटल व्योम klp_kobj_release_func(काष्ठा kobject *kobj)
अणु
	काष्ठा klp_func *func;

	func = container_of(kobj, काष्ठा klp_func, kobj);

	अगर (func->nop)
		klp_मुक्त_func_nop(func);
पूर्ण

अटल काष्ठा kobj_type klp_ktype_func = अणु
	.release = klp_kobj_release_func,
	.sysfs_ops = &kobj_sysfs_ops,
पूर्ण;

अटल व्योम __klp_मुक्त_funcs(काष्ठा klp_object *obj, bool nops_only)
अणु
	काष्ठा klp_func *func, *पंचांगp_func;

	klp_क्रम_each_func_safe(obj, func, पंचांगp_func) अणु
		अगर (nops_only && !func->nop)
			जारी;

		list_del(&func->node);
		kobject_put(&func->kobj);
	पूर्ण
पूर्ण

/* Clean up when a patched object is unloaded */
अटल व्योम klp_मुक्त_object_loaded(काष्ठा klp_object *obj)
अणु
	काष्ठा klp_func *func;

	obj->mod = शून्य;

	klp_क्रम_each_func(obj, func) अणु
		func->old_func = शून्य;

		अगर (func->nop)
			func->new_func = शून्य;
	पूर्ण
पूर्ण

अटल व्योम __klp_मुक्त_objects(काष्ठा klp_patch *patch, bool nops_only)
अणु
	काष्ठा klp_object *obj, *पंचांगp_obj;

	klp_क्रम_each_object_safe(patch, obj, पंचांगp_obj) अणु
		__klp_मुक्त_funcs(obj, nops_only);

		अगर (nops_only && !obj->dynamic)
			जारी;

		list_del(&obj->node);
		kobject_put(&obj->kobj);
	पूर्ण
पूर्ण

अटल व्योम klp_मुक्त_objects(काष्ठा klp_patch *patch)
अणु
	__klp_मुक्त_objects(patch, false);
पूर्ण

अटल व्योम klp_मुक्त_objects_dynamic(काष्ठा klp_patch *patch)
अणु
	__klp_मुक्त_objects(patch, true);
पूर्ण

/*
 * This function implements the मुक्त operations that can be called safely
 * under klp_mutex.
 *
 * The operation must be completed by calling klp_मुक्त_patch_finish()
 * outside klp_mutex.
 */
अटल व्योम klp_मुक्त_patch_start(काष्ठा klp_patch *patch)
अणु
	अगर (!list_empty(&patch->list))
		list_del(&patch->list);

	klp_मुक्त_objects(patch);
पूर्ण

/*
 * This function implements the मुक्त part that must be called outside
 * klp_mutex.
 *
 * It must be called after klp_मुक्त_patch_start(). And it has to be
 * the last function accessing the livepatch काष्ठाures when the patch
 * माला_लो disabled.
 */
अटल व्योम klp_मुक्त_patch_finish(काष्ठा klp_patch *patch)
अणु
	/*
	 * Aव्योम deadlock with enabled_store() sysfs callback by
	 * calling this outside klp_mutex. It is safe because
	 * this is called when the patch माला_लो disabled and it
	 * cannot get enabled again.
	 */
	kobject_put(&patch->kobj);
	रुको_क्रम_completion(&patch->finish);

	/* Put the module after the last access to काष्ठा klp_patch. */
	अगर (!patch->क्रमced)
		module_put(patch->mod);
पूर्ण

/*
 * The livepatch might be मुक्तd from sysfs पूर्णांकerface created by the patch.
 * This work allows to रुको until the पूर्णांकerface is destroyed in a separate
 * context.
 */
अटल व्योम klp_मुक्त_patch_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा klp_patch *patch =
		container_of(work, काष्ठा klp_patch, मुक्त_work);

	klp_मुक्त_patch_finish(patch);
पूर्ण

व्योम klp_मुक्त_patch_async(काष्ठा klp_patch *patch)
अणु
	klp_मुक्त_patch_start(patch);
	schedule_work(&patch->मुक्त_work);
पूर्ण

व्योम klp_मुक्त_replaced_patches_async(काष्ठा klp_patch *new_patch)
अणु
	काष्ठा klp_patch *old_patch, *पंचांगp_patch;

	klp_क्रम_each_patch_safe(old_patch, पंचांगp_patch) अणु
		अगर (old_patch == new_patch)
			वापस;
		klp_मुक्त_patch_async(old_patch);
	पूर्ण
पूर्ण

अटल पूर्णांक klp_init_func(काष्ठा klp_object *obj, काष्ठा klp_func *func)
अणु
	अगर (!func->old_name)
		वापस -EINVAL;

	/*
	 * NOPs get the address later. The patched module must be loaded,
	 * see klp_init_object_loaded().
	 */
	अगर (!func->new_func && !func->nop)
		वापस -EINVAL;

	अगर (म_माप(func->old_name) >= KSYM_NAME_LEN)
		वापस -EINVAL;

	INIT_LIST_HEAD(&func->stack_node);
	func->patched = false;
	func->transition = false;

	/* The क्रमmat क्रम the sysfs directory is <function,sympos> where sympos
	 * is the nth occurrence of this symbol in kallsyms क्रम the patched
	 * object. If the user selects 0 क्रम old_sympos, then 1 will be used
	 * since a unique symbol will be the first occurrence.
	 */
	वापस kobject_add(&func->kobj, &obj->kobj, "%s,%lu",
			   func->old_name,
			   func->old_sympos ? func->old_sympos : 1);
पूर्ण

अटल पूर्णांक klp_apply_object_relocs(काष्ठा klp_patch *patch,
				   काष्ठा klp_object *obj)
अणु
	पूर्णांक i, ret;
	काष्ठा klp_modinfo *info = patch->mod->klp_info;

	क्रम (i = 1; i < info->hdr.e_shnum; i++) अणु
		Elf_Shdr *sec = info->sechdrs + i;

		अगर (!(sec->sh_flags & SHF_RELA_LIVEPATCH))
			जारी;

		ret = klp_apply_section_relocs(patch->mod, info->sechdrs,
					       info->secstrings,
					       patch->mod->core_kallsyms.strtab,
					       info->symndx, i, obj->name);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* parts of the initialization that is करोne only when the object is loaded */
अटल पूर्णांक klp_init_object_loaded(काष्ठा klp_patch *patch,
				  काष्ठा klp_object *obj)
अणु
	काष्ठा klp_func *func;
	पूर्णांक ret;

	अगर (klp_is_module(obj)) अणु
		/*
		 * Only ग_लिखो module-specअगरic relocations here
		 * (.klp.rela.अणुmoduleपूर्ण.*).  vmlinux-specअगरic relocations were
		 * written earlier during the initialization of the klp module
		 * itself.
		 */
		ret = klp_apply_object_relocs(patch, obj);
		अगर (ret)
			वापस ret;
	पूर्ण

	klp_क्रम_each_func(obj, func) अणु
		ret = klp_find_object_symbol(obj->name, func->old_name,
					     func->old_sympos,
					     (अचिन्हित दीर्घ *)&func->old_func);
		अगर (ret)
			वापस ret;

		ret = kallsyms_lookup_size_offset((अचिन्हित दीर्घ)func->old_func,
						  &func->old_size, शून्य);
		अगर (!ret) अणु
			pr_err("kallsyms size lookup failed for '%s'\n",
			       func->old_name);
			वापस -ENOENT;
		पूर्ण

		अगर (func->nop)
			func->new_func = func->old_func;

		ret = kallsyms_lookup_size_offset((अचिन्हित दीर्घ)func->new_func,
						  &func->new_size, शून्य);
		अगर (!ret) अणु
			pr_err("kallsyms size lookup failed for '%s' replacement\n",
			       func->old_name);
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक klp_init_object(काष्ठा klp_patch *patch, काष्ठा klp_object *obj)
अणु
	काष्ठा klp_func *func;
	पूर्णांक ret;
	स्थिर अक्षर *name;

	अगर (klp_is_module(obj) && म_माप(obj->name) >= MODULE_NAME_LEN)
		वापस -EINVAL;

	obj->patched = false;
	obj->mod = शून्य;

	klp_find_object_module(obj);

	name = klp_is_module(obj) ? obj->name : "vmlinux";
	ret = kobject_add(&obj->kobj, &patch->kobj, "%s", name);
	अगर (ret)
		वापस ret;

	klp_क्रम_each_func(obj, func) अणु
		ret = klp_init_func(obj, func);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (klp_is_object_loaded(obj))
		ret = klp_init_object_loaded(patch, obj);

	वापस ret;
पूर्ण

अटल व्योम klp_init_func_early(काष्ठा klp_object *obj,
				काष्ठा klp_func *func)
अणु
	kobject_init(&func->kobj, &klp_ktype_func);
	list_add_tail(&func->node, &obj->func_list);
पूर्ण

अटल व्योम klp_init_object_early(काष्ठा klp_patch *patch,
				  काष्ठा klp_object *obj)
अणु
	INIT_LIST_HEAD(&obj->func_list);
	kobject_init(&obj->kobj, &klp_ktype_object);
	list_add_tail(&obj->node, &patch->obj_list);
पूर्ण

अटल पूर्णांक klp_init_patch_early(काष्ठा klp_patch *patch)
अणु
	काष्ठा klp_object *obj;
	काष्ठा klp_func *func;

	अगर (!patch->objs)
		वापस -EINVAL;

	INIT_LIST_HEAD(&patch->list);
	INIT_LIST_HEAD(&patch->obj_list);
	kobject_init(&patch->kobj, &klp_ktype_patch);
	patch->enabled = false;
	patch->क्रमced = false;
	INIT_WORK(&patch->मुक्त_work, klp_मुक्त_patch_work_fn);
	init_completion(&patch->finish);

	klp_क्रम_each_object_अटल(patch, obj) अणु
		अगर (!obj->funcs)
			वापस -EINVAL;

		klp_init_object_early(patch, obj);

		klp_क्रम_each_func_अटल(obj, func) अणु
			klp_init_func_early(obj, func);
		पूर्ण
	पूर्ण

	अगर (!try_module_get(patch->mod))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक klp_init_patch(काष्ठा klp_patch *patch)
अणु
	काष्ठा klp_object *obj;
	पूर्णांक ret;

	ret = kobject_add(&patch->kobj, klp_root_kobj, "%s", patch->mod->name);
	अगर (ret)
		वापस ret;

	अगर (patch->replace) अणु
		ret = klp_add_nops(patch);
		अगर (ret)
			वापस ret;
	पूर्ण

	klp_क्रम_each_object(patch, obj) अणु
		ret = klp_init_object(patch, obj);
		अगर (ret)
			वापस ret;
	पूर्ण

	list_add_tail(&patch->list, &klp_patches);

	वापस 0;
पूर्ण

अटल पूर्णांक __klp_disable_patch(काष्ठा klp_patch *patch)
अणु
	काष्ठा klp_object *obj;

	अगर (WARN_ON(!patch->enabled))
		वापस -EINVAL;

	अगर (klp_transition_patch)
		वापस -EBUSY;

	klp_init_transition(patch, KLP_UNPATCHED);

	klp_क्रम_each_object(patch, obj)
		अगर (obj->patched)
			klp_pre_unpatch_callback(obj);

	/*
	 * Enक्रमce the order of the func->transition ग_लिखोs in
	 * klp_init_transition() and the TIF_PATCH_PENDING ग_लिखोs in
	 * klp_start_transition().  In the rare हाल where klp_ftrace_handler()
	 * is called लघुly after klp_update_patch_state() चयनes the task,
	 * this ensures the handler sees that func->transition is set.
	 */
	smp_wmb();

	klp_start_transition();
	patch->enabled = false;
	klp_try_complete_transition();

	वापस 0;
पूर्ण

अटल पूर्णांक __klp_enable_patch(काष्ठा klp_patch *patch)
अणु
	काष्ठा klp_object *obj;
	पूर्णांक ret;

	अगर (klp_transition_patch)
		वापस -EBUSY;

	अगर (WARN_ON(patch->enabled))
		वापस -EINVAL;

	pr_notice("enabling patch '%s'\n", patch->mod->name);

	klp_init_transition(patch, KLP_PATCHED);

	/*
	 * Enक्रमce the order of the func->transition ग_लिखोs in
	 * klp_init_transition() and the ops->func_stack ग_लिखोs in
	 * klp_patch_object(), so that klp_ftrace_handler() will see the
	 * func->transition updates beक्रमe the handler is रेजिस्टरed and the
	 * new funcs become visible to the handler.
	 */
	smp_wmb();

	klp_क्रम_each_object(patch, obj) अणु
		अगर (!klp_is_object_loaded(obj))
			जारी;

		ret = klp_pre_patch_callback(obj);
		अगर (ret) अणु
			pr_warn("pre-patch callback failed for object '%s'\n",
				klp_is_module(obj) ? obj->name : "vmlinux");
			जाओ err;
		पूर्ण

		ret = klp_patch_object(obj);
		अगर (ret) अणु
			pr_warn("failed to patch object '%s'\n",
				klp_is_module(obj) ? obj->name : "vmlinux");
			जाओ err;
		पूर्ण
	पूर्ण

	klp_start_transition();
	patch->enabled = true;
	klp_try_complete_transition();

	वापस 0;
err:
	pr_warn("failed to enable patch '%s'\n", patch->mod->name);

	klp_cancel_transition();
	वापस ret;
पूर्ण

/**
 * klp_enable_patch() - enable the livepatch
 * @patch:	patch to be enabled
 *
 * Initializes the data काष्ठाure associated with the patch, creates the sysfs
 * पूर्णांकerface, perक्रमms the needed symbol lookups and code relocations,
 * रेजिस्टरs the patched functions with ftrace.
 *
 * This function is supposed to be called from the livepatch module_init()
 * callback.
 *
 * Return: 0 on success, otherwise error
 */
पूर्णांक klp_enable_patch(काष्ठा klp_patch *patch)
अणु
	पूर्णांक ret;

	अगर (!patch || !patch->mod)
		वापस -EINVAL;

	अगर (!is_livepatch_module(patch->mod)) अणु
		pr_err("module %s is not marked as a livepatch module\n",
		       patch->mod->name);
		वापस -EINVAL;
	पूर्ण

	अगर (!klp_initialized())
		वापस -ENODEV;

	अगर (!klp_have_reliable_stack()) अणु
		pr_warn("This architecture doesn't have support for the livepatch consistency model.\n");
		pr_warn("The livepatch transition may never complete.\n");
	पूर्ण

	mutex_lock(&klp_mutex);

	अगर (!klp_is_patch_compatible(patch)) अणु
		pr_err("Livepatch patch (%s) is not compatible with the already installed livepatches.\n",
			patch->mod->name);
		mutex_unlock(&klp_mutex);
		वापस -EINVAL;
	पूर्ण

	ret = klp_init_patch_early(patch);
	अगर (ret) अणु
		mutex_unlock(&klp_mutex);
		वापस ret;
	पूर्ण

	ret = klp_init_patch(patch);
	अगर (ret)
		जाओ err;

	ret = __klp_enable_patch(patch);
	अगर (ret)
		जाओ err;

	mutex_unlock(&klp_mutex);

	वापस 0;

err:
	klp_मुक्त_patch_start(patch);

	mutex_unlock(&klp_mutex);

	klp_मुक्त_patch_finish(patch);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(klp_enable_patch);

/*
 * This function unpatches objects from the replaced livepatches.
 *
 * We could be pretty aggressive here. It is called in the situation where
 * these काष्ठाures are no दीर्घer accessed from the ftrace handler.
 * All functions are redirected by the klp_transition_patch. They
 * use either a new code or they are in the original code because
 * of the special nop function patches.
 *
 * The only exception is when the transition was क्रमced. In this हाल,
 * klp_ftrace_handler() might still see the replaced patch on the stack.
 * Fortunately, it is carefully deचिन्हित to work with हटाओd functions
 * thanks to RCU. We only have to keep the patches on the प्रणाली. Also
 * this is handled transparently by patch->module_put.
 */
व्योम klp_unpatch_replaced_patches(काष्ठा klp_patch *new_patch)
अणु
	काष्ठा klp_patch *old_patch;

	klp_क्रम_each_patch(old_patch) अणु
		अगर (old_patch == new_patch)
			वापस;

		old_patch->enabled = false;
		klp_unpatch_objects(old_patch);
	पूर्ण
पूर्ण

/*
 * This function हटाओs the dynamically allocated 'nop' functions.
 *
 * We could be pretty aggressive. NOPs करो not change the existing
 * behavior except क्रम adding unnecessary delay by the ftrace handler.
 *
 * It is safe even when the transition was क्रमced. The ftrace handler
 * will see a valid ops->func_stack entry thanks to RCU.
 *
 * We could even मुक्त the NOPs काष्ठाures. They must be the last entry
 * in ops->func_stack. Thereक्रमe unरेजिस्टर_ftrace_function() is called.
 * It करोes the same as klp_synchronize_transition() to make sure that
 * nobody is inside the ftrace handler once the operation finishes.
 *
 * IMPORTANT: It must be called right after removing the replaced patches!
 */
व्योम klp_discard_nops(काष्ठा klp_patch *new_patch)
अणु
	klp_unpatch_objects_dynamic(klp_transition_patch);
	klp_मुक्त_objects_dynamic(klp_transition_patch);
पूर्ण

/*
 * Remove parts of patches that touch a given kernel module. The list of
 * patches processed might be limited. When limit is शून्य, all patches
 * will be handled.
 */
अटल व्योम klp_cleanup_module_patches_limited(काष्ठा module *mod,
					       काष्ठा klp_patch *limit)
अणु
	काष्ठा klp_patch *patch;
	काष्ठा klp_object *obj;

	klp_क्रम_each_patch(patch) अणु
		अगर (patch == limit)
			अवरोध;

		klp_क्रम_each_object(patch, obj) अणु
			अगर (!klp_is_module(obj) || म_भेद(obj->name, mod->name))
				जारी;

			अगर (patch != klp_transition_patch)
				klp_pre_unpatch_callback(obj);

			pr_notice("reverting patch '%s' on unloading module '%s'\n",
				  patch->mod->name, obj->mod->name);
			klp_unpatch_object(obj);

			klp_post_unpatch_callback(obj);

			klp_मुक्त_object_loaded(obj);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक klp_module_coming(काष्ठा module *mod)
अणु
	पूर्णांक ret;
	काष्ठा klp_patch *patch;
	काष्ठा klp_object *obj;

	अगर (WARN_ON(mod->state != MODULE_STATE_COMING))
		वापस -EINVAL;

	अगर (!म_भेद(mod->name, "vmlinux")) अणु
		pr_err("vmlinux.ko: invalid module name");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&klp_mutex);
	/*
	 * Each module has to know that klp_module_coming()
	 * has been called. We never know what module will
	 * get patched by a new patch.
	 */
	mod->klp_alive = true;

	klp_क्रम_each_patch(patch) अणु
		klp_क्रम_each_object(patch, obj) अणु
			अगर (!klp_is_module(obj) || म_भेद(obj->name, mod->name))
				जारी;

			obj->mod = mod;

			ret = klp_init_object_loaded(patch, obj);
			अगर (ret) अणु
				pr_warn("failed to initialize patch '%s' for module '%s' (%d)\n",
					patch->mod->name, obj->mod->name, ret);
				जाओ err;
			पूर्ण

			pr_notice("applying patch '%s' to loading module '%s'\n",
				  patch->mod->name, obj->mod->name);

			ret = klp_pre_patch_callback(obj);
			अगर (ret) अणु
				pr_warn("pre-patch callback failed for object '%s'\n",
					obj->name);
				जाओ err;
			पूर्ण

			ret = klp_patch_object(obj);
			अगर (ret) अणु
				pr_warn("failed to apply patch '%s' to module '%s' (%d)\n",
					patch->mod->name, obj->mod->name, ret);

				klp_post_unpatch_callback(obj);
				जाओ err;
			पूर्ण

			अगर (patch != klp_transition_patch)
				klp_post_patch_callback(obj);

			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&klp_mutex);

	वापस 0;

err:
	/*
	 * If a patch is unsuccessfully applied, वापस
	 * error to the module loader.
	 */
	pr_warn("patch '%s' failed for module '%s', refusing to load module '%s'\n",
		patch->mod->name, obj->mod->name, obj->mod->name);
	mod->klp_alive = false;
	obj->mod = शून्य;
	klp_cleanup_module_patches_limited(mod, patch);
	mutex_unlock(&klp_mutex);

	वापस ret;
पूर्ण

व्योम klp_module_going(काष्ठा module *mod)
अणु
	अगर (WARN_ON(mod->state != MODULE_STATE_GOING &&
		    mod->state != MODULE_STATE_COMING))
		वापस;

	mutex_lock(&klp_mutex);
	/*
	 * Each module has to know that klp_module_going()
	 * has been called. We never know what module will
	 * get patched by a new patch.
	 */
	mod->klp_alive = false;

	klp_cleanup_module_patches_limited(mod, शून्य);

	mutex_unlock(&klp_mutex);
पूर्ण

अटल पूर्णांक __init klp_init(व्योम)
अणु
	klp_root_kobj = kobject_create_and_add("livepatch", kernel_kobj);
	अगर (!klp_root_kobj)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

module_init(klp_init);
