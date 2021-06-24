<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * transition.c - Kernel Live Patching transition functions
 *
 * Copyright (C) 2015-2016 Josh Poimboeuf <jpoimboe@redhat.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cpu.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/tracehook.h>
#समावेश "core.h"
#समावेश "patch.h"
#समावेश "transition.h"
#समावेश "../sched/sched.h"

#घोषणा MAX_STACK_ENTRIES  100
#घोषणा STACK_ERR_BUF_SIZE 128

#घोषणा SIGNALS_TIMEOUT 15

काष्ठा klp_patch *klp_transition_patch;

अटल पूर्णांक klp_target_state = KLP_UNDEFINED;

अटल अचिन्हित पूर्णांक klp_संकेतs_cnt;

/*
 * This work can be perक्रमmed periodically to finish patching or unpatching any
 * "straggler" tasks which failed to transition in the first attempt.
 */
अटल व्योम klp_transition_work_fn(काष्ठा work_काष्ठा *work)
अणु
	mutex_lock(&klp_mutex);

	अगर (klp_transition_patch)
		klp_try_complete_transition();

	mutex_unlock(&klp_mutex);
पूर्ण
अटल DECLARE_DELAYED_WORK(klp_transition_work, klp_transition_work_fn);

/*
 * This function is just a stub to implement a hard क्रमce
 * of synchronize_rcu(). This requires synchronizing
 * tasks even in userspace and idle.
 */
अटल व्योम klp_sync(काष्ठा work_काष्ठा *work)
अणु
पूर्ण

/*
 * We allow to patch also functions where RCU is not watching,
 * e.g. beक्रमe user_निकास(). We can not rely on the RCU infraकाष्ठाure
 * to करो the synchronization. Instead hard क्रमce the sched synchronization.
 *
 * This approach allows to use RCU functions क्रम manipulating func_stack
 * safely.
 */
अटल व्योम klp_synchronize_transition(व्योम)
अणु
	schedule_on_each_cpu(klp_sync);
पूर्ण

/*
 * The transition to the target patch state is complete.  Clean up the data
 * काष्ठाures.
 */
अटल व्योम klp_complete_transition(व्योम)
अणु
	काष्ठा klp_object *obj;
	काष्ठा klp_func *func;
	काष्ठा task_काष्ठा *g, *task;
	अचिन्हित पूर्णांक cpu;

	pr_debug("'%s': completing %s transition\n",
		 klp_transition_patch->mod->name,
		 klp_target_state == KLP_PATCHED ? "patching" : "unpatching");

	अगर (klp_transition_patch->replace && klp_target_state == KLP_PATCHED) अणु
		klp_unpatch_replaced_patches(klp_transition_patch);
		klp_discard_nops(klp_transition_patch);
	पूर्ण

	अगर (klp_target_state == KLP_UNPATCHED) अणु
		/*
		 * All tasks have transitioned to KLP_UNPATCHED so we can now
		 * हटाओ the new functions from the func_stack.
		 */
		klp_unpatch_objects(klp_transition_patch);

		/*
		 * Make sure klp_ftrace_handler() can no दीर्घer see functions
		 * from this patch on the ops->func_stack.  Otherwise, after
		 * func->transition माला_लो cleared, the handler may choose a
		 * हटाओd function.
		 */
		klp_synchronize_transition();
	पूर्ण

	klp_क्रम_each_object(klp_transition_patch, obj)
		klp_क्रम_each_func(obj, func)
			func->transition = false;

	/* Prevent klp_ftrace_handler() from seeing KLP_UNDEFINED state */
	अगर (klp_target_state == KLP_PATCHED)
		klp_synchronize_transition();

	पढ़ो_lock(&tasklist_lock);
	क्रम_each_process_thपढ़ो(g, task) अणु
		WARN_ON_ONCE(test_tsk_thपढ़ो_flag(task, TIF_PATCH_PENDING));
		task->patch_state = KLP_UNDEFINED;
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);

	क्रम_each_possible_cpu(cpu) अणु
		task = idle_task(cpu);
		WARN_ON_ONCE(test_tsk_thपढ़ो_flag(task, TIF_PATCH_PENDING));
		task->patch_state = KLP_UNDEFINED;
	पूर्ण

	klp_क्रम_each_object(klp_transition_patch, obj) अणु
		अगर (!klp_is_object_loaded(obj))
			जारी;
		अगर (klp_target_state == KLP_PATCHED)
			klp_post_patch_callback(obj);
		अन्यथा अगर (klp_target_state == KLP_UNPATCHED)
			klp_post_unpatch_callback(obj);
	पूर्ण

	pr_notice("'%s': %s complete\n", klp_transition_patch->mod->name,
		  klp_target_state == KLP_PATCHED ? "patching" : "unpatching");

	klp_target_state = KLP_UNDEFINED;
	klp_transition_patch = शून्य;
पूर्ण

/*
 * This is called in the error path, to cancel a transition beक्रमe it has
 * started, i.e. klp_init_transition() has been called but
 * klp_start_transition() hasn't.  If the transition *has* been started,
 * klp_reverse_transition() should be used instead.
 */
व्योम klp_cancel_transition(व्योम)
अणु
	अगर (WARN_ON_ONCE(klp_target_state != KLP_PATCHED))
		वापस;

	pr_debug("'%s': canceling patching transition, going to unpatch\n",
		 klp_transition_patch->mod->name);

	klp_target_state = KLP_UNPATCHED;
	klp_complete_transition();
पूर्ण

/*
 * Switch the patched state of the task to the set of functions in the target
 * patch state.
 *
 * NOTE: If task is not 'current', the caller must ensure the task is inactive.
 * Otherwise klp_ftrace_handler() might पढ़ो the wrong 'patch_state' value.
 */
व्योम klp_update_patch_state(काष्ठा task_काष्ठा *task)
अणु
	/*
	 * A variant of synchronize_rcu() is used to allow patching functions
	 * where RCU is not watching, see klp_synchronize_transition().
	 */
	preempt_disable_notrace();

	/*
	 * This test_and_clear_tsk_thपढ़ो_flag() call also serves as a पढ़ो
	 * barrier (smp_rmb) क्रम two हालs:
	 *
	 * 1) Enक्रमce the order of the TIF_PATCH_PENDING पढ़ो and the
	 *    klp_target_state पढ़ो.  The corresponding ग_लिखो barrier is in
	 *    klp_init_transition().
	 *
	 * 2) Enक्रमce the order of the TIF_PATCH_PENDING पढ़ो and a future पढ़ो
	 *    of func->transition, अगर klp_ftrace_handler() is called later on
	 *    the same CPU.  See __klp_disable_patch().
	 */
	अगर (test_and_clear_tsk_thपढ़ो_flag(task, TIF_PATCH_PENDING))
		task->patch_state = READ_ONCE(klp_target_state);

	preempt_enable_notrace();
पूर्ण

/*
 * Determine whether the given stack trace includes any references to a
 * to-be-patched or to-be-unpatched function.
 */
अटल पूर्णांक klp_check_stack_func(काष्ठा klp_func *func, अचिन्हित दीर्घ *entries,
				अचिन्हित पूर्णांक nr_entries)
अणु
	अचिन्हित दीर्घ func_addr, func_size, address;
	काष्ठा klp_ops *ops;
	पूर्णांक i;

	क्रम (i = 0; i < nr_entries; i++) अणु
		address = entries[i];

		अगर (klp_target_state == KLP_UNPATCHED) अणु
			 /*
			  * Check क्रम the to-be-unpatched function
			  * (the func itself).
			  */
			func_addr = (अचिन्हित दीर्घ)func->new_func;
			func_size = func->new_size;
		पूर्ण अन्यथा अणु
			/*
			 * Check क्रम the to-be-patched function
			 * (the previous func).
			 */
			ops = klp_find_ops(func->old_func);

			अगर (list_is_singular(&ops->func_stack)) अणु
				/* original function */
				func_addr = (अचिन्हित दीर्घ)func->old_func;
				func_size = func->old_size;
			पूर्ण अन्यथा अणु
				/* previously patched function */
				काष्ठा klp_func *prev;

				prev = list_next_entry(func, stack_node);
				func_addr = (अचिन्हित दीर्घ)prev->new_func;
				func_size = prev->new_size;
			पूर्ण
		पूर्ण

		अगर (address >= func_addr && address < func_addr + func_size)
			वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Determine whether it's safe to transition the task to the target patch state
 * by looking क्रम any to-be-patched or to-be-unpatched functions on its stack.
 */
अटल पूर्णांक klp_check_stack(काष्ठा task_काष्ठा *task, अक्षर *err_buf)
अणु
	अटल अचिन्हित दीर्घ entries[MAX_STACK_ENTRIES];
	काष्ठा klp_object *obj;
	काष्ठा klp_func *func;
	पूर्णांक ret, nr_entries;

	ret = stack_trace_save_tsk_reliable(task, entries, ARRAY_SIZE(entries));
	अगर (ret < 0) अणु
		snम_लिखो(err_buf, STACK_ERR_BUF_SIZE,
			 "%s: %s:%d has an unreliable stack\n",
			 __func__, task->comm, task->pid);
		वापस ret;
	पूर्ण
	nr_entries = ret;

	klp_क्रम_each_object(klp_transition_patch, obj) अणु
		अगर (!obj->patched)
			जारी;
		klp_क्रम_each_func(obj, func) अणु
			ret = klp_check_stack_func(func, entries, nr_entries);
			अगर (ret) अणु
				snम_लिखो(err_buf, STACK_ERR_BUF_SIZE,
					 "%s: %s:%d is sleeping on function %s\n",
					 __func__, task->comm, task->pid,
					 func->old_name);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Try to safely चयन a task to the target patch state.  If it's currently
 * running, or it's sleeping on a to-be-patched or to-be-unpatched function, or
 * अगर the stack is unreliable, वापस false.
 */
अटल bool klp_try_चयन_task(काष्ठा task_काष्ठा *task)
अणु
	अटल अक्षर err_buf[STACK_ERR_BUF_SIZE];
	काष्ठा rq *rq;
	काष्ठा rq_flags flags;
	पूर्णांक ret;
	bool success = false;

	err_buf[0] = '\0';

	/* check अगर this task has alपढ़ोy चयनed over */
	अगर (task->patch_state == klp_target_state)
		वापस true;

	/*
	 * For arches which करोn't have reliable stack traces, we have to rely
	 * on other methods (e.g., चयनing tasks at kernel निकास).
	 */
	अगर (!klp_have_reliable_stack())
		वापस false;

	/*
	 * Now try to check the stack क्रम any to-be-patched or to-be-unpatched
	 * functions.  If all goes well, चयन the task to the target patch
	 * state.
	 */
	rq = task_rq_lock(task, &flags);

	अगर (task_running(rq, task) && task != current) अणु
		snम_लिखो(err_buf, STACK_ERR_BUF_SIZE,
			 "%s: %s:%d is running\n", __func__, task->comm,
			 task->pid);
		जाओ करोne;
	पूर्ण

	ret = klp_check_stack(task, err_buf);
	अगर (ret)
		जाओ करोne;

	success = true;

	clear_tsk_thपढ़ो_flag(task, TIF_PATCH_PENDING);
	task->patch_state = klp_target_state;

करोne:
	task_rq_unlock(rq, task, &flags);

	/*
	 * Due to console deadlock issues, pr_debug() can't be used जबतक
	 * holding the task rq lock.  Instead we have to use a temporary buffer
	 * and prपूर्णांक the debug message after releasing the lock.
	 */
	अगर (err_buf[0] != '\0')
		pr_debug("%s", err_buf);

	वापस success;
पूर्ण

/*
 * Sends a fake संकेत to all non-kthपढ़ो tasks with TIF_PATCH_PENDING set.
 * Kthपढ़ोs with TIF_PATCH_PENDING set are woken up.
 */
अटल व्योम klp_send_संकेतs(व्योम)
अणु
	काष्ठा task_काष्ठा *g, *task;

	अगर (klp_संकेतs_cnt == SIGNALS_TIMEOUT)
		pr_notice("signaling remaining tasks\n");

	पढ़ो_lock(&tasklist_lock);
	क्रम_each_process_thपढ़ो(g, task) अणु
		अगर (!klp_patch_pending(task))
			जारी;

		/*
		 * There is a small race here. We could see TIF_PATCH_PENDING
		 * set and decide to wake up a kthपढ़ो or send a fake संकेत.
		 * Meanजबतक the task could migrate itself and the action
		 * would be meaningless. It is not serious though.
		 */
		अगर (task->flags & PF_KTHREAD) अणु
			/*
			 * Wake up a kthपढ़ो which sleeps पूर्णांकerruptedly and
			 * still has not been migrated.
			 */
			wake_up_state(task, TASK_INTERRUPTIBLE);
		पूर्ण अन्यथा अणु
			/*
			 * Send fake संकेत to all non-kthपढ़ो tasks which are
			 * still not migrated.
			 */
			set_notअगरy_संकेत(task);
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);
पूर्ण

/*
 * Try to चयन all reमुख्यing tasks to the target patch state by walking the
 * stacks of sleeping tasks and looking क्रम any to-be-patched or
 * to-be-unpatched functions.  If such functions are found, the task can't be
 * चयनed yet.
 *
 * If any tasks are still stuck in the initial patch state, schedule a retry.
 */
व्योम klp_try_complete_transition(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;
	काष्ठा task_काष्ठा *g, *task;
	काष्ठा klp_patch *patch;
	bool complete = true;

	WARN_ON_ONCE(klp_target_state == KLP_UNDEFINED);

	/*
	 * Try to चयन the tasks to the target patch state by walking their
	 * stacks and looking क्रम any to-be-patched or to-be-unpatched
	 * functions.  If such functions are found on a stack, or अगर the stack
	 * is deemed unreliable, the task can't be चयनed yet.
	 *
	 * Usually this will transition most (or all) of the tasks on a प्रणाली
	 * unless the patch includes changes to a very common function.
	 */
	पढ़ो_lock(&tasklist_lock);
	क्रम_each_process_thपढ़ो(g, task)
		अगर (!klp_try_चयन_task(task))
			complete = false;
	पढ़ो_unlock(&tasklist_lock);

	/*
	 * Ditto क्रम the idle "swapper" tasks.
	 */
	get_online_cpus();
	क्रम_each_possible_cpu(cpu) अणु
		task = idle_task(cpu);
		अगर (cpu_online(cpu)) अणु
			अगर (!klp_try_चयन_task(task))
				complete = false;
		पूर्ण अन्यथा अगर (task->patch_state != klp_target_state) अणु
			/* offline idle tasks can be चयनed immediately */
			clear_tsk_thपढ़ो_flag(task, TIF_PATCH_PENDING);
			task->patch_state = klp_target_state;
		पूर्ण
	पूर्ण
	put_online_cpus();

	अगर (!complete) अणु
		अगर (klp_संकेतs_cnt && !(klp_संकेतs_cnt % SIGNALS_TIMEOUT))
			klp_send_संकेतs();
		klp_संकेतs_cnt++;

		/*
		 * Some tasks weren't able to be चयनed over.  Try again
		 * later and/or रुको क्रम other methods like kernel निकास
		 * चयनing.
		 */
		schedule_delayed_work(&klp_transition_work,
				      round_jअगरfies_relative(HZ));
		वापस;
	पूर्ण

	/* we're करोne, now cleanup the data काष्ठाures */
	patch = klp_transition_patch;
	klp_complete_transition();

	/*
	 * It would make more sense to मुक्त the unused patches in
	 * klp_complete_transition() but it is called also
	 * from klp_cancel_transition().
	 */
	अगर (!patch->enabled)
		klp_मुक्त_patch_async(patch);
	अन्यथा अगर (patch->replace)
		klp_मुक्त_replaced_patches_async(patch);
पूर्ण

/*
 * Start the transition to the specअगरied target patch state so tasks can begin
 * चयनing to it.
 */
व्योम klp_start_transition(व्योम)
अणु
	काष्ठा task_काष्ठा *g, *task;
	अचिन्हित पूर्णांक cpu;

	WARN_ON_ONCE(klp_target_state == KLP_UNDEFINED);

	pr_notice("'%s': starting %s transition\n",
		  klp_transition_patch->mod->name,
		  klp_target_state == KLP_PATCHED ? "patching" : "unpatching");

	/*
	 * Mark all normal tasks as needing a patch state update.  They'll
	 * चयन either in klp_try_complete_transition() or as they निकास the
	 * kernel.
	 */
	पढ़ो_lock(&tasklist_lock);
	क्रम_each_process_thपढ़ो(g, task)
		अगर (task->patch_state != klp_target_state)
			set_tsk_thपढ़ो_flag(task, TIF_PATCH_PENDING);
	पढ़ो_unlock(&tasklist_lock);

	/*
	 * Mark all idle tasks as needing a patch state update.  They'll चयन
	 * either in klp_try_complete_transition() or at the idle loop चयन
	 * poपूर्णांक.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		task = idle_task(cpu);
		अगर (task->patch_state != klp_target_state)
			set_tsk_thपढ़ो_flag(task, TIF_PATCH_PENDING);
	पूर्ण

	klp_संकेतs_cnt = 0;
पूर्ण

/*
 * Initialize the global target patch state and all tasks to the initial patch
 * state, and initialize all function transition states to true in preparation
 * क्रम patching or unpatching.
 */
व्योम klp_init_transition(काष्ठा klp_patch *patch, पूर्णांक state)
अणु
	काष्ठा task_काष्ठा *g, *task;
	अचिन्हित पूर्णांक cpu;
	काष्ठा klp_object *obj;
	काष्ठा klp_func *func;
	पूर्णांक initial_state = !state;

	WARN_ON_ONCE(klp_target_state != KLP_UNDEFINED);

	klp_transition_patch = patch;

	/*
	 * Set the global target patch state which tasks will चयन to.  This
	 * has no effect until the TIF_PATCH_PENDING flags get set later.
	 */
	klp_target_state = state;

	pr_debug("'%s': initializing %s transition\n", patch->mod->name,
		 klp_target_state == KLP_PATCHED ? "patching" : "unpatching");

	/*
	 * Initialize all tasks to the initial patch state to prepare them क्रम
	 * चयनing to the target state.
	 */
	पढ़ो_lock(&tasklist_lock);
	क्रम_each_process_thपढ़ो(g, task) अणु
		WARN_ON_ONCE(task->patch_state != KLP_UNDEFINED);
		task->patch_state = initial_state;
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);

	/*
	 * Ditto क्रम the idle "swapper" tasks.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		task = idle_task(cpu);
		WARN_ON_ONCE(task->patch_state != KLP_UNDEFINED);
		task->patch_state = initial_state;
	पूर्ण

	/*
	 * Enक्रमce the order of the task->patch_state initializations and the
	 * func->transition updates to ensure that klp_ftrace_handler() करोesn't
	 * see a func in transition with a task->patch_state of KLP_UNDEFINED.
	 *
	 * Also enक्रमce the order of the klp_target_state ग_लिखो and future
	 * TIF_PATCH_PENDING ग_लिखोs to ensure klp_update_patch_state() करोesn't
	 * set a task->patch_state to KLP_UNDEFINED.
	 */
	smp_wmb();

	/*
	 * Set the func transition states so klp_ftrace_handler() will know to
	 * चयन to the transition logic.
	 *
	 * When patching, the funcs aren't yet in the func_stack and will be
	 * made visible to the ftrace handler लघुly by the calls to
	 * klp_patch_object().
	 *
	 * When unpatching, the funcs are alपढ़ोy in the func_stack and so are
	 * alपढ़ोy visible to the ftrace handler.
	 */
	klp_क्रम_each_object(patch, obj)
		klp_क्रम_each_func(obj, func)
			func->transition = true;
पूर्ण

/*
 * This function can be called in the middle of an existing transition to
 * reverse the direction of the target patch state.  This can be करोne to
 * effectively cancel an existing enable or disable operation अगर there are any
 * tasks which are stuck in the initial patch state.
 */
व्योम klp_reverse_transition(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;
	काष्ठा task_काष्ठा *g, *task;

	pr_debug("'%s': reversing transition from %s\n",
		 klp_transition_patch->mod->name,
		 klp_target_state == KLP_PATCHED ? "patching to unpatching" :
						   "unpatching to patching");

	klp_transition_patch->enabled = !klp_transition_patch->enabled;

	klp_target_state = !klp_target_state;

	/*
	 * Clear all TIF_PATCH_PENDING flags to prevent races caused by
	 * klp_update_patch_state() running in parallel with
	 * klp_start_transition().
	 */
	पढ़ो_lock(&tasklist_lock);
	क्रम_each_process_thपढ़ो(g, task)
		clear_tsk_thपढ़ो_flag(task, TIF_PATCH_PENDING);
	पढ़ो_unlock(&tasklist_lock);

	क्रम_each_possible_cpu(cpu)
		clear_tsk_thपढ़ो_flag(idle_task(cpu), TIF_PATCH_PENDING);

	/* Let any reमुख्यing calls to klp_update_patch_state() complete */
	klp_synchronize_transition();

	klp_start_transition();
पूर्ण

/* Called from copy_process() during विभाजन */
व्योम klp_copy_process(काष्ठा task_काष्ठा *child)
अणु
	child->patch_state = current->patch_state;

	/* TIF_PATCH_PENDING माला_लो copied in setup_thपढ़ो_stack() */
पूर्ण

/*
 * Drop TIF_PATCH_PENDING of all tasks on admin's request. This क्रमces an
 * existing transition to finish.
 *
 * NOTE: klp_update_patch_state(task) requires the task to be inactive or
 * 'current'. This is not the हाल here and the consistency model could be
 * broken. Administrator, who is the only one to execute the
 * klp_क्रमce_transitions(), has to be aware of this.
 */
व्योम klp_क्रमce_transition(व्योम)
अणु
	काष्ठा klp_patch *patch;
	काष्ठा task_काष्ठा *g, *task;
	अचिन्हित पूर्णांक cpu;

	pr_warn("forcing remaining tasks to the patched state\n");

	पढ़ो_lock(&tasklist_lock);
	क्रम_each_process_thपढ़ो(g, task)
		klp_update_patch_state(task);
	पढ़ो_unlock(&tasklist_lock);

	क्रम_each_possible_cpu(cpu)
		klp_update_patch_state(idle_task(cpu));

	klp_क्रम_each_patch(patch)
		patch->क्रमced = true;
पूर्ण
