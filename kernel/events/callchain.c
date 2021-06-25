<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Perक्रमmance events callchain code, extracted from core.c:
 *
 *  Copyright (C) 2008 Thomas Gleixner <tglx@linutronix.de>
 *  Copyright (C) 2008-2011 Red Hat, Inc., Ingo Molnar
 *  Copyright (C) 2008-2011 Red Hat, Inc., Peter Zijlstra
 *  Copyright  तऊ  2009 Paul Mackerras, IBM Corp. <paulus@au1.ibm.com>
 */

#समावेश <linux/perf_event.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/task_stack.h>

#समावेश "internal.h"

काष्ठा callchain_cpus_entries अणु
	काष्ठा rcu_head			rcu_head;
	काष्ठा perf_callchain_entry	*cpu_entries[];
पूर्ण;

पूर्णांक sysctl_perf_event_max_stack __पढ़ो_mostly = PERF_MAX_STACK_DEPTH;
पूर्णांक sysctl_perf_event_max_contexts_per_stack __पढ़ो_mostly = PERF_MAX_CONTEXTS_PER_STACK;

अटल अंतरभूत माप_प्रकार perf_callchain_entry__माप(व्योम)
अणु
	वापस (माप(काष्ठा perf_callchain_entry) +
		माप(__u64) * (sysctl_perf_event_max_stack +
				 sysctl_perf_event_max_contexts_per_stack));
पूर्ण

अटल DEFINE_PER_CPU(पूर्णांक, callchain_recursion[PERF_NR_CONTEXTS]);
अटल atomic_t nr_callchain_events;
अटल DEFINE_MUTEX(callchain_mutex);
अटल काष्ठा callchain_cpus_entries *callchain_cpus_entries;


__weak व्योम perf_callchain_kernel(काष्ठा perf_callchain_entry_ctx *entry,
				  काष्ठा pt_regs *regs)
अणु
पूर्ण

__weak व्योम perf_callchain_user(काष्ठा perf_callchain_entry_ctx *entry,
				काष्ठा pt_regs *regs)
अणु
पूर्ण

अटल व्योम release_callchain_buffers_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा callchain_cpus_entries *entries;
	पूर्णांक cpu;

	entries = container_of(head, काष्ठा callchain_cpus_entries, rcu_head);

	क्रम_each_possible_cpu(cpu)
		kमुक्त(entries->cpu_entries[cpu]);

	kमुक्त(entries);
पूर्ण

अटल व्योम release_callchain_buffers(व्योम)
अणु
	काष्ठा callchain_cpus_entries *entries;

	entries = callchain_cpus_entries;
	RCU_INIT_POINTER(callchain_cpus_entries, शून्य);
	call_rcu(&entries->rcu_head, release_callchain_buffers_rcu);
पूर्ण

अटल पूर्णांक alloc_callchain_buffers(व्योम)
अणु
	पूर्णांक cpu;
	पूर्णांक size;
	काष्ठा callchain_cpus_entries *entries;

	/*
	 * We can't use the percpu allocation API क्रम data that can be
	 * accessed from NMI. Use a temporary manual per cpu allocation
	 * until that माला_लो sorted out.
	 */
	size = दुरत्व(काष्ठा callchain_cpus_entries, cpu_entries[nr_cpu_ids]);

	entries = kzalloc(size, GFP_KERNEL);
	अगर (!entries)
		वापस -ENOMEM;

	size = perf_callchain_entry__माप() * PERF_NR_CONTEXTS;

	क्रम_each_possible_cpu(cpu) अणु
		entries->cpu_entries[cpu] = kदो_स्मृति_node(size, GFP_KERNEL,
							 cpu_to_node(cpu));
		अगर (!entries->cpu_entries[cpu])
			जाओ fail;
	पूर्ण

	rcu_assign_poपूर्णांकer(callchain_cpus_entries, entries);

	वापस 0;

fail:
	क्रम_each_possible_cpu(cpu)
		kमुक्त(entries->cpu_entries[cpu]);
	kमुक्त(entries);

	वापस -ENOMEM;
पूर्ण

पूर्णांक get_callchain_buffers(पूर्णांक event_max_stack)
अणु
	पूर्णांक err = 0;
	पूर्णांक count;

	mutex_lock(&callchain_mutex);

	count = atomic_inc_वापस(&nr_callchain_events);
	अगर (WARN_ON_ONCE(count < 1)) अणु
		err = -EINVAL;
		जाओ निकास;
	पूर्ण

	/*
	 * If requesting per event more than the global cap,
	 * वापस a dअगरferent error to help userspace figure
	 * this out.
	 *
	 * And also करो it here so that we have &callchain_mutex held.
	 */
	अगर (event_max_stack > sysctl_perf_event_max_stack) अणु
		err = -EOVERFLOW;
		जाओ निकास;
	पूर्ण

	अगर (count == 1)
		err = alloc_callchain_buffers();
निकास:
	अगर (err)
		atomic_dec(&nr_callchain_events);

	mutex_unlock(&callchain_mutex);

	वापस err;
पूर्ण

व्योम put_callchain_buffers(व्योम)
अणु
	अगर (atomic_dec_and_mutex_lock(&nr_callchain_events, &callchain_mutex)) अणु
		release_callchain_buffers();
		mutex_unlock(&callchain_mutex);
	पूर्ण
पूर्ण

काष्ठा perf_callchain_entry *get_callchain_entry(पूर्णांक *rctx)
अणु
	पूर्णांक cpu;
	काष्ठा callchain_cpus_entries *entries;

	*rctx = get_recursion_context(this_cpu_ptr(callchain_recursion));
	अगर (*rctx == -1)
		वापस शून्य;

	entries = rcu_dereference(callchain_cpus_entries);
	अगर (!entries) अणु
		put_recursion_context(this_cpu_ptr(callchain_recursion), *rctx);
		वापस शून्य;
	पूर्ण

	cpu = smp_processor_id();

	वापस (((व्योम *)entries->cpu_entries[cpu]) +
		(*rctx * perf_callchain_entry__माप()));
पूर्ण

व्योम
put_callchain_entry(पूर्णांक rctx)
अणु
	put_recursion_context(this_cpu_ptr(callchain_recursion), rctx);
पूर्ण

काष्ठा perf_callchain_entry *
get_perf_callchain(काष्ठा pt_regs *regs, u32 init_nr, bool kernel, bool user,
		   u32 max_stack, bool crosstask, bool add_mark)
अणु
	काष्ठा perf_callchain_entry *entry;
	काष्ठा perf_callchain_entry_ctx ctx;
	पूर्णांक rctx;

	entry = get_callchain_entry(&rctx);
	अगर (!entry)
		वापस शून्य;

	ctx.entry     = entry;
	ctx.max_stack = max_stack;
	ctx.nr	      = entry->nr = init_nr;
	ctx.contexts       = 0;
	ctx.contexts_maxed = false;

	अगर (kernel && !user_mode(regs)) अणु
		अगर (add_mark)
			perf_callchain_store_context(&ctx, PERF_CONTEXT_KERNEL);
		perf_callchain_kernel(&ctx, regs);
	पूर्ण

	अगर (user) अणु
		अगर (!user_mode(regs)) अणु
			अगर  (current->mm)
				regs = task_pt_regs(current);
			अन्यथा
				regs = शून्य;
		पूर्ण

		अगर (regs) अणु
			mm_segment_t fs;

			अगर (crosstask)
				जाओ निकास_put;

			अगर (add_mark)
				perf_callchain_store_context(&ctx, PERF_CONTEXT_USER);

			fs = क्रमce_uaccess_begin();
			perf_callchain_user(&ctx, regs);
			क्रमce_uaccess_end(fs);
		पूर्ण
	पूर्ण

निकास_put:
	put_callchain_entry(rctx);

	वापस entry;
पूर्ण

/*
 * Used क्रम sysctl_perf_event_max_stack and
 * sysctl_perf_event_max_contexts_per_stack.
 */
पूर्णांक perf_event_max_stack_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				 व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक *value = table->data;
	पूर्णांक new_value = *value, ret;
	काष्ठा ctl_table new_table = *table;

	new_table.data = &new_value;
	ret = proc_करोपूर्णांकvec_minmax(&new_table, ग_लिखो, buffer, lenp, ppos);
	अगर (ret || !ग_लिखो)
		वापस ret;

	mutex_lock(&callchain_mutex);
	अगर (atomic_पढ़ो(&nr_callchain_events))
		ret = -EBUSY;
	अन्यथा
		*value = new_value;

	mutex_unlock(&callchain_mutex);

	वापस ret;
पूर्ण
