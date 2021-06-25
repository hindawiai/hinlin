<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * patch.c - livepatch patching functions
 *
 * Copyright (C) 2014 Seth Jennings <sjenning@redhat.com>
 * Copyright (C) 2014 SUSE
 * Copyright (C) 2015 Josh Poimboeuf <jpoimboe@redhat.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/livepatch.h>
#समावेश <linux/list.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/rculist.h>
#समावेश <linux/slab.h>
#समावेश <linux/bug.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश "core.h"
#समावेश "patch.h"
#समावेश "transition.h"

अटल LIST_HEAD(klp_ops);

काष्ठा klp_ops *klp_find_ops(व्योम *old_func)
अणु
	काष्ठा klp_ops *ops;
	काष्ठा klp_func *func;

	list_क्रम_each_entry(ops, &klp_ops, node) अणु
		func = list_first_entry(&ops->func_stack, काष्ठा klp_func,
					stack_node);
		अगर (func->old_func == old_func)
			वापस ops;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम notrace klp_ftrace_handler(अचिन्हित दीर्घ ip,
				       अचिन्हित दीर्घ parent_ip,
				       काष्ठा ftrace_ops *fops,
				       काष्ठा ftrace_regs *fregs)
अणु
	काष्ठा klp_ops *ops;
	काष्ठा klp_func *func;
	पूर्णांक patch_state;
	पूर्णांक bit;

	ops = container_of(fops, काष्ठा klp_ops, fops);

	bit = ftrace_test_recursion_trylock(ip, parent_ip);
	अगर (WARN_ON_ONCE(bit < 0))
		वापस;
	/*
	 * A variant of synchronize_rcu() is used to allow patching functions
	 * where RCU is not watching, see klp_synchronize_transition().
	 */
	preempt_disable_notrace();

	func = list_first_or_null_rcu(&ops->func_stack, काष्ठा klp_func,
				      stack_node);

	/*
	 * func should never be शून्य because preemption should be disabled here
	 * and unरेजिस्टर_ftrace_function() करोes the equivalent of a
	 * synchronize_rcu() beक्रमe the func_stack removal.
	 */
	अगर (WARN_ON_ONCE(!func))
		जाओ unlock;

	/*
	 * In the enable path, enक्रमce the order of the ops->func_stack and
	 * func->transition पढ़ोs.  The corresponding ग_लिखो barrier is in
	 * __klp_enable_patch().
	 *
	 * (Note that this barrier technically isn't needed in the disable
	 * path.  In the rare हाल where klp_update_patch_state() runs beक्रमe
	 * this handler, its TIF_PATCH_PENDING पढ़ो and this func->transition
	 * पढ़ो need to be ordered.  But klp_update_patch_state() alपढ़ोy
	 * enक्रमces that.)
	 */
	smp_rmb();

	अगर (unlikely(func->transition)) अणु

		/*
		 * Enक्रमce the order of the func->transition and
		 * current->patch_state पढ़ोs.  Otherwise we could पढ़ो an
		 * out-of-date task state and pick the wrong function.  The
		 * corresponding ग_लिखो barrier is in klp_init_transition().
		 */
		smp_rmb();

		patch_state = current->patch_state;

		WARN_ON_ONCE(patch_state == KLP_UNDEFINED);

		अगर (patch_state == KLP_UNPATCHED) अणु
			/*
			 * Use the previously patched version of the function.
			 * If no previous patches exist, जारी with the
			 * original function.
			 */
			func = list_entry_rcu(func->stack_node.next,
					      काष्ठा klp_func, stack_node);

			अगर (&func->stack_node == &ops->func_stack)
				जाओ unlock;
		पूर्ण
	पूर्ण

	/*
	 * NOPs are used to replace existing patches with original code.
	 * Do nothing! Setting pc would cause an infinite loop.
	 */
	अगर (func->nop)
		जाओ unlock;

	klp_arch_set_pc(fregs, (अचिन्हित दीर्घ)func->new_func);

unlock:
	preempt_enable_notrace();
	ftrace_test_recursion_unlock(bit);
पूर्ण

/*
 * Convert a function address पूर्णांकo the appropriate ftrace location.
 *
 * Usually this is just the address of the function, but on some architectures
 * it's more complicated so allow them to provide a custom behaviour.
 */
#अगर_अघोषित klp_get_ftrace_location
अटल अचिन्हित दीर्घ klp_get_ftrace_location(अचिन्हित दीर्घ faddr)
अणु
	वापस faddr;
पूर्ण
#पूर्ण_अगर

अटल व्योम klp_unpatch_func(काष्ठा klp_func *func)
अणु
	काष्ठा klp_ops *ops;

	अगर (WARN_ON(!func->patched))
		वापस;
	अगर (WARN_ON(!func->old_func))
		वापस;

	ops = klp_find_ops(func->old_func);
	अगर (WARN_ON(!ops))
		वापस;

	अगर (list_is_singular(&ops->func_stack)) अणु
		अचिन्हित दीर्घ ftrace_loc;

		ftrace_loc =
			klp_get_ftrace_location((अचिन्हित दीर्घ)func->old_func);
		अगर (WARN_ON(!ftrace_loc))
			वापस;

		WARN_ON(unरेजिस्टर_ftrace_function(&ops->fops));
		WARN_ON(ftrace_set_filter_ip(&ops->fops, ftrace_loc, 1, 0));

		list_del_rcu(&func->stack_node);
		list_del(&ops->node);
		kमुक्त(ops);
	पूर्ण अन्यथा अणु
		list_del_rcu(&func->stack_node);
	पूर्ण

	func->patched = false;
पूर्ण

अटल पूर्णांक klp_patch_func(काष्ठा klp_func *func)
अणु
	काष्ठा klp_ops *ops;
	पूर्णांक ret;

	अगर (WARN_ON(!func->old_func))
		वापस -EINVAL;

	अगर (WARN_ON(func->patched))
		वापस -EINVAL;

	ops = klp_find_ops(func->old_func);
	अगर (!ops) अणु
		अचिन्हित दीर्घ ftrace_loc;

		ftrace_loc =
			klp_get_ftrace_location((अचिन्हित दीर्घ)func->old_func);
		अगर (!ftrace_loc) अणु
			pr_err("failed to find location for function '%s'\n",
				func->old_name);
			वापस -EINVAL;
		पूर्ण

		ops = kzalloc(माप(*ops), GFP_KERNEL);
		अगर (!ops)
			वापस -ENOMEM;

		ops->fops.func = klp_ftrace_handler;
		ops->fops.flags = FTRACE_OPS_FL_DYNAMIC |
#अगर_अघोषित CONFIG_HAVE_DYNAMIC_FTRACE_WITH_ARGS
				  FTRACE_OPS_FL_SAVE_REGS |
#पूर्ण_अगर
				  FTRACE_OPS_FL_IPMODIFY |
				  FTRACE_OPS_FL_PERMANENT;

		list_add(&ops->node, &klp_ops);

		INIT_LIST_HEAD(&ops->func_stack);
		list_add_rcu(&func->stack_node, &ops->func_stack);

		ret = ftrace_set_filter_ip(&ops->fops, ftrace_loc, 0, 0);
		अगर (ret) अणु
			pr_err("failed to set ftrace filter for function '%s' (%d)\n",
			       func->old_name, ret);
			जाओ err;
		पूर्ण

		ret = रेजिस्टर_ftrace_function(&ops->fops);
		अगर (ret) अणु
			pr_err("failed to register ftrace handler for function '%s' (%d)\n",
			       func->old_name, ret);
			ftrace_set_filter_ip(&ops->fops, ftrace_loc, 1, 0);
			जाओ err;
		पूर्ण


	पूर्ण अन्यथा अणु
		list_add_rcu(&func->stack_node, &ops->func_stack);
	पूर्ण

	func->patched = true;

	वापस 0;

err:
	list_del_rcu(&func->stack_node);
	list_del(&ops->node);
	kमुक्त(ops);
	वापस ret;
पूर्ण

अटल व्योम __klp_unpatch_object(काष्ठा klp_object *obj, bool nops_only)
अणु
	काष्ठा klp_func *func;

	klp_क्रम_each_func(obj, func) अणु
		अगर (nops_only && !func->nop)
			जारी;

		अगर (func->patched)
			klp_unpatch_func(func);
	पूर्ण

	अगर (obj->dynamic || !nops_only)
		obj->patched = false;
पूर्ण


व्योम klp_unpatch_object(काष्ठा klp_object *obj)
अणु
	__klp_unpatch_object(obj, false);
पूर्ण

पूर्णांक klp_patch_object(काष्ठा klp_object *obj)
अणु
	काष्ठा klp_func *func;
	पूर्णांक ret;

	अगर (WARN_ON(obj->patched))
		वापस -EINVAL;

	klp_क्रम_each_func(obj, func) अणु
		ret = klp_patch_func(func);
		अगर (ret) अणु
			klp_unpatch_object(obj);
			वापस ret;
		पूर्ण
	पूर्ण
	obj->patched = true;

	वापस 0;
पूर्ण

अटल व्योम __klp_unpatch_objects(काष्ठा klp_patch *patch, bool nops_only)
अणु
	काष्ठा klp_object *obj;

	klp_क्रम_each_object(patch, obj)
		अगर (obj->patched)
			__klp_unpatch_object(obj, nops_only);
पूर्ण

व्योम klp_unpatch_objects(काष्ठा klp_patch *patch)
अणु
	__klp_unpatch_objects(patch, false);
पूर्ण

व्योम klp_unpatch_objects_dynamic(काष्ठा klp_patch *patch)
अणु
	__klp_unpatch_objects(patch, true);
पूर्ण
