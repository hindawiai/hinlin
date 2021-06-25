<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * livepatch.h - Kernel Live Patching Core
 *
 * Copyright (C) 2014 Seth Jennings <sjenning@redhat.com>
 * Copyright (C) 2014 SUSE
 */

#अगर_अघोषित _LINUX_LIVEPATCH_H_
#घोषणा _LINUX_LIVEPATCH_H_

#समावेश <linux/module.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/completion.h>
#समावेश <linux/list.h>

#अगर IS_ENABLED(CONFIG_LIVEPATCH)

#समावेश <यंत्र/livepatch.h>

/* task patch states */
#घोषणा KLP_UNDEFINED	-1
#घोषणा KLP_UNPATCHED	 0
#घोषणा KLP_PATCHED	 1

/**
 * काष्ठा klp_func - function काष्ठाure क्रम live patching
 * @old_name:	name of the function to be patched
 * @new_func:	poपूर्णांकer to the patched function code
 * @old_sympos: a hपूर्णांक indicating which symbol position the old function
 *		can be found (optional)
 * @old_func:	poपूर्णांकer to the function being patched
 * @kobj:	kobject क्रम sysfs resources
 * @node:	list node क्रम klp_object func_list
 * @stack_node:	list node क्रम klp_ops func_stack list
 * @old_size:	size of the old function
 * @new_size:	size of the new function
 * @nop:        temporary patch to use the original code again; dyn. allocated
 * @patched:	the func has been added to the klp_ops list
 * @transition:	the func is currently being applied or reverted
 *
 * The patched and transition variables define the func's patching state.  When
 * patching, a func is always in one of the following states:
 *
 *   patched=0 transition=0: unpatched
 *   patched=0 transition=1: unpatched, temporary starting state
 *   patched=1 transition=1: patched, may be visible to some tasks
 *   patched=1 transition=0: patched, visible to all tasks
 *
 * And when unpatching, it goes in the reverse order:
 *
 *   patched=1 transition=0: patched, visible to all tasks
 *   patched=1 transition=1: patched, may be visible to some tasks
 *   patched=0 transition=1: unpatched, temporary ending state
 *   patched=0 transition=0: unpatched
 */
काष्ठा klp_func अणु
	/* बाह्यal */
	स्थिर अक्षर *old_name;
	व्योम *new_func;
	/*
	 * The old_sympos field is optional and can be used to resolve
	 * duplicate symbol names in livepatch objects. If this field is zero,
	 * it is expected the symbol is unique, otherwise patching fails. If
	 * this value is greater than zero then that occurrence of the symbol
	 * in kallsyms क्रम the given object is used.
	 */
	अचिन्हित दीर्घ old_sympos;

	/* पूर्णांकernal */
	व्योम *old_func;
	काष्ठा kobject kobj;
	काष्ठा list_head node;
	काष्ठा list_head stack_node;
	अचिन्हित दीर्घ old_size, new_size;
	bool nop;
	bool patched;
	bool transition;
पूर्ण;

काष्ठा klp_object;

/**
 * काष्ठा klp_callbacks - pre/post live-(un)patch callback काष्ठाure
 * @pre_patch:		executed beक्रमe code patching
 * @post_patch:		executed after code patching
 * @pre_unpatch:	executed beक्रमe code unpatching
 * @post_unpatch:	executed after code unpatching
 * @post_unpatch_enabled:	flag indicating अगर post-unpatch callback
 * 				should run
 *
 * All callbacks are optional.  Only the pre-patch callback, अगर provided,
 * will be unconditionally executed.  If the parent klp_object fails to
 * patch क्रम any reason, including a non-zero error status वापसed from
 * the pre-patch callback, no further callbacks will be executed.
 */
काष्ठा klp_callbacks अणु
	पूर्णांक (*pre_patch)(काष्ठा klp_object *obj);
	व्योम (*post_patch)(काष्ठा klp_object *obj);
	व्योम (*pre_unpatch)(काष्ठा klp_object *obj);
	व्योम (*post_unpatch)(काष्ठा klp_object *obj);
	bool post_unpatch_enabled;
पूर्ण;

/**
 * काष्ठा klp_object - kernel object काष्ठाure क्रम live patching
 * @name:	module name (or शून्य क्रम vmlinux)
 * @funcs:	function entries क्रम functions to be patched in the object
 * @callbacks:	functions to be executed pre/post (un)patching
 * @kobj:	kobject क्रम sysfs resources
 * @func_list:	dynamic list of the function entries
 * @node:	list node क्रम klp_patch obj_list
 * @mod:	kernel module associated with the patched object
 *		(शून्य क्रम vmlinux)
 * @dynamic:    temporary object क्रम nop functions; dynamically allocated
 * @patched:	the object's funcs have been added to the klp_ops list
 */
काष्ठा klp_object अणु
	/* बाह्यal */
	स्थिर अक्षर *name;
	काष्ठा klp_func *funcs;
	काष्ठा klp_callbacks callbacks;

	/* पूर्णांकernal */
	काष्ठा kobject kobj;
	काष्ठा list_head func_list;
	काष्ठा list_head node;
	काष्ठा module *mod;
	bool dynamic;
	bool patched;
पूर्ण;

/**
 * काष्ठा klp_state - state of the प्रणाली modअगरied by the livepatch
 * @id:		प्रणाली state identअगरier (non-zero)
 * @version:	version of the change
 * @data:	custom data
 */
काष्ठा klp_state अणु
	अचिन्हित दीर्घ id;
	अचिन्हित पूर्णांक version;
	व्योम *data;
पूर्ण;

/**
 * काष्ठा klp_patch - patch काष्ठाure क्रम live patching
 * @mod:	reference to the live patch module
 * @objs:	object entries क्रम kernel objects to be patched
 * @states:	प्रणाली states that can get modअगरied
 * @replace:	replace all actively used patches
 * @list:	list node क्रम global list of actively used patches
 * @kobj:	kobject क्रम sysfs resources
 * @obj_list:	dynamic list of the object entries
 * @enabled:	the patch is enabled (but operation may be incomplete)
 * @क्रमced:	was involved in a क्रमced transition
 * @मुक्त_work:	patch cleanup from workqueue-context
 * @finish:	क्रम रुकोing till it is safe to हटाओ the patch module
 */
काष्ठा klp_patch अणु
	/* बाह्यal */
	काष्ठा module *mod;
	काष्ठा klp_object *objs;
	काष्ठा klp_state *states;
	bool replace;

	/* पूर्णांकernal */
	काष्ठा list_head list;
	काष्ठा kobject kobj;
	काष्ठा list_head obj_list;
	bool enabled;
	bool क्रमced;
	काष्ठा work_काष्ठा मुक्त_work;
	काष्ठा completion finish;
पूर्ण;

#घोषणा klp_क्रम_each_object_अटल(patch, obj) \
	क्रम (obj = patch->objs; obj->funcs || obj->name; obj++)

#घोषणा klp_क्रम_each_object_safe(patch, obj, पंचांगp_obj)		\
	list_क्रम_each_entry_safe(obj, पंचांगp_obj, &patch->obj_list, node)

#घोषणा klp_क्रम_each_object(patch, obj)	\
	list_क्रम_each_entry(obj, &patch->obj_list, node)

#घोषणा klp_क्रम_each_func_अटल(obj, func) \
	क्रम (func = obj->funcs; \
	     func->old_name || func->new_func || func->old_sympos; \
	     func++)

#घोषणा klp_क्रम_each_func_safe(obj, func, पंचांगp_func)			\
	list_क्रम_each_entry_safe(func, पंचांगp_func, &obj->func_list, node)

#घोषणा klp_क्रम_each_func(obj, func)	\
	list_क्रम_each_entry(func, &obj->func_list, node)

पूर्णांक klp_enable_patch(काष्ठा klp_patch *);

/* Called from the module loader during module coming/going states */
पूर्णांक klp_module_coming(काष्ठा module *mod);
व्योम klp_module_going(काष्ठा module *mod);

व्योम klp_copy_process(काष्ठा task_काष्ठा *child);
व्योम klp_update_patch_state(काष्ठा task_काष्ठा *task);

अटल अंतरभूत bool klp_patch_pending(काष्ठा task_काष्ठा *task)
अणु
	वापस test_tsk_thपढ़ो_flag(task, TIF_PATCH_PENDING);
पूर्ण

अटल अंतरभूत bool klp_have_reliable_stack(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_STACKTRACE) &&
	       IS_ENABLED(CONFIG_HAVE_RELIABLE_STACKTRACE);
पूर्ण

प्रकार पूर्णांक (*klp_shaकरोw_ctor_t)(व्योम *obj,
				 व्योम *shaकरोw_data,
				 व्योम *ctor_data);
प्रकार व्योम (*klp_shaकरोw_dtor_t)(व्योम *obj, व्योम *shaकरोw_data);

व्योम *klp_shaकरोw_get(व्योम *obj, अचिन्हित दीर्घ id);
व्योम *klp_shaकरोw_alloc(व्योम *obj, अचिन्हित दीर्घ id,
		       माप_प्रकार size, gfp_t gfp_flags,
		       klp_shaकरोw_ctor_t ctor, व्योम *ctor_data);
व्योम *klp_shaकरोw_get_or_alloc(व्योम *obj, अचिन्हित दीर्घ id,
			      माप_प्रकार size, gfp_t gfp_flags,
			      klp_shaकरोw_ctor_t ctor, व्योम *ctor_data);
व्योम klp_shaकरोw_मुक्त(व्योम *obj, अचिन्हित दीर्घ id, klp_shaकरोw_dtor_t dtor);
व्योम klp_shaकरोw_मुक्त_all(अचिन्हित दीर्घ id, klp_shaकरोw_dtor_t dtor);

काष्ठा klp_state *klp_get_state(काष्ठा klp_patch *patch, अचिन्हित दीर्घ id);
काष्ठा klp_state *klp_get_prev_state(अचिन्हित दीर्घ id);

पूर्णांक klp_apply_section_relocs(काष्ठा module *pmod, Elf_Shdr *sechdrs,
			     स्थिर अक्षर *shstrtab, स्थिर अक्षर *strtab,
			     अचिन्हित पूर्णांक symindex, अचिन्हित पूर्णांक secindex,
			     स्थिर अक्षर *objname);

#अन्यथा /* !CONFIG_LIVEPATCH */

अटल अंतरभूत पूर्णांक klp_module_coming(काष्ठा module *mod) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम klp_module_going(काष्ठा module *mod) अणुपूर्ण
अटल अंतरभूत bool klp_patch_pending(काष्ठा task_काष्ठा *task) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम klp_update_patch_state(काष्ठा task_काष्ठा *task) अणुपूर्ण
अटल अंतरभूत व्योम klp_copy_process(काष्ठा task_काष्ठा *child) अणुपूर्ण

अटल अंतरभूत
पूर्णांक klp_apply_section_relocs(काष्ठा module *pmod, Elf_Shdr *sechdrs,
			     स्थिर अक्षर *shstrtab, स्थिर अक्षर *strtab,
			     अचिन्हित पूर्णांक symindex, अचिन्हित पूर्णांक secindex,
			     स्थिर अक्षर *objname)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_LIVEPATCH */

#पूर्ण_अगर /* _LINUX_LIVEPATCH_H_ */
