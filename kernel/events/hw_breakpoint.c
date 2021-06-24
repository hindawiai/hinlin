<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2007 Alan Stern
 * Copyright (C) IBM Corporation, 2009
 * Copyright (C) 2009, Frederic Weisbecker <fweisbec@gmail.com>
 *
 * Thanks to Ingo Molnar क्रम his many suggestions.
 *
 * Authors: Alan Stern <stern@rowland.harvard.edu>
 *          K.Prasad <prasad@linux.vnet.ibm.com>
 *          Frederic Weisbecker <fweisbec@gmail.com>
 */

/*
 * HW_अवरोधpoपूर्णांक: a unअगरied kernel/user-space hardware अवरोधpoपूर्णांक facility,
 * using the CPU's debug रेजिस्टरs.
 * This file contains the arch-independent routines.
 */

#समावेश <linux/irqflags.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/percpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/cpu.h>
#समावेश <linux/smp.h>
#समावेश <linux/bug.h>

#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
/*
 * Constraपूर्णांकs data
 */
काष्ठा bp_cpuinfo अणु
	/* Number of pinned cpu अवरोधpoपूर्णांकs in a cpu */
	अचिन्हित पूर्णांक	cpu_pinned;
	/* tsk_pinned[n] is the number of tasks having n+1 अवरोधpoपूर्णांकs */
	अचिन्हित पूर्णांक	*tsk_pinned;
	/* Number of non-pinned cpu/task अवरोधpoपूर्णांकs in a cpu */
	अचिन्हित पूर्णांक	flexible; /* XXX: placeholder, see fetch_this_slot() */
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा bp_cpuinfo, bp_cpuinfo[TYPE_MAX]);
अटल पूर्णांक nr_slots[TYPE_MAX];

अटल काष्ठा bp_cpuinfo *get_bp_info(पूर्णांक cpu, क्रमागत bp_type_idx type)
अणु
	वापस per_cpu_ptr(bp_cpuinfo + type, cpu);
पूर्ण

/* Keep track of the अवरोधpoपूर्णांकs attached to tasks */
अटल LIST_HEAD(bp_task_head);

अटल पूर्णांक स्थिरraपूर्णांकs_initialized;

/* Gather the number of total pinned and un-pinned bp in a cpuset */
काष्ठा bp_busy_slots अणु
	अचिन्हित पूर्णांक pinned;
	अचिन्हित पूर्णांक flexible;
पूर्ण;

/* Serialize accesses to the above स्थिरraपूर्णांकs */
अटल DEFINE_MUTEX(nr_bp_mutex);

__weak पूर्णांक hw_अवरोधpoपूर्णांक_weight(काष्ठा perf_event *bp)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत क्रमागत bp_type_idx find_slot_idx(u64 bp_type)
अणु
	अगर (bp_type & HW_BREAKPOINT_RW)
		वापस TYPE_DATA;

	वापस TYPE_INST;
पूर्ण

/*
 * Report the maximum number of pinned अवरोधpoपूर्णांकs a task
 * have in this cpu
 */
अटल अचिन्हित पूर्णांक max_task_bp_pinned(पूर्णांक cpu, क्रमागत bp_type_idx type)
अणु
	अचिन्हित पूर्णांक *tsk_pinned = get_bp_info(cpu, type)->tsk_pinned;
	पूर्णांक i;

	क्रम (i = nr_slots[type] - 1; i >= 0; i--) अणु
		अगर (tsk_pinned[i] > 0)
			वापस i + 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Count the number of अवरोधpoपूर्णांकs of the same type and same task.
 * The given event must be not on the list.
 */
अटल पूर्णांक task_bp_pinned(पूर्णांक cpu, काष्ठा perf_event *bp, क्रमागत bp_type_idx type)
अणु
	काष्ठा task_काष्ठा *tsk = bp->hw.target;
	काष्ठा perf_event *iter;
	पूर्णांक count = 0;

	list_क्रम_each_entry(iter, &bp_task_head, hw.bp_list) अणु
		अगर (iter->hw.target == tsk &&
		    find_slot_idx(iter->attr.bp_type) == type &&
		    (iter->cpu < 0 || cpu == iter->cpu))
			count += hw_अवरोधpoपूर्णांक_weight(iter);
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा cpumask *cpumask_of_bp(काष्ठा perf_event *bp)
अणु
	अगर (bp->cpu >= 0)
		वापस cpumask_of(bp->cpu);
	वापस cpu_possible_mask;
पूर्ण

/*
 * Report the number of pinned/un-pinned अवरोधpoपूर्णांकs we have in
 * a given cpu (cpu > -1) or in all of them (cpu = -1).
 */
अटल व्योम
fetch_bp_busy_slots(काष्ठा bp_busy_slots *slots, काष्ठा perf_event *bp,
		    क्रमागत bp_type_idx type)
अणु
	स्थिर काष्ठा cpumask *cpumask = cpumask_of_bp(bp);
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, cpumask) अणु
		काष्ठा bp_cpuinfo *info = get_bp_info(cpu, type);
		पूर्णांक nr;

		nr = info->cpu_pinned;
		अगर (!bp->hw.target)
			nr += max_task_bp_pinned(cpu, type);
		अन्यथा
			nr += task_bp_pinned(cpu, bp, type);

		अगर (nr > slots->pinned)
			slots->pinned = nr;

		nr = info->flexible;
		अगर (nr > slots->flexible)
			slots->flexible = nr;
	पूर्ण
पूर्ण

/*
 * For now, जारी to consider flexible as pinned, until we can
 * ensure no flexible event can ever be scheduled beक्रमe a pinned event
 * in a same cpu.
 */
अटल व्योम
fetch_this_slot(काष्ठा bp_busy_slots *slots, पूर्णांक weight)
अणु
	slots->pinned += weight;
पूर्ण

/*
 * Add a pinned अवरोधpoपूर्णांक क्रम the given task in our स्थिरraपूर्णांक table
 */
अटल व्योम toggle_bp_task_slot(काष्ठा perf_event *bp, पूर्णांक cpu,
				क्रमागत bp_type_idx type, पूर्णांक weight)
अणु
	अचिन्हित पूर्णांक *tsk_pinned = get_bp_info(cpu, type)->tsk_pinned;
	पूर्णांक old_idx, new_idx;

	old_idx = task_bp_pinned(cpu, bp, type) - 1;
	new_idx = old_idx + weight;

	अगर (old_idx >= 0)
		tsk_pinned[old_idx]--;
	अगर (new_idx >= 0)
		tsk_pinned[new_idx]++;
पूर्ण

/*
 * Add/हटाओ the given अवरोधpoपूर्णांक in our स्थिरraपूर्णांक table
 */
अटल व्योम
toggle_bp_slot(काष्ठा perf_event *bp, bool enable, क्रमागत bp_type_idx type,
	       पूर्णांक weight)
अणु
	स्थिर काष्ठा cpumask *cpumask = cpumask_of_bp(bp);
	पूर्णांक cpu;

	अगर (!enable)
		weight = -weight;

	/* Pinned counter cpu profiling */
	अगर (!bp->hw.target) अणु
		get_bp_info(bp->cpu, type)->cpu_pinned += weight;
		वापस;
	पूर्ण

	/* Pinned counter task profiling */
	क्रम_each_cpu(cpu, cpumask)
		toggle_bp_task_slot(bp, cpu, type, weight);

	अगर (enable)
		list_add_tail(&bp->hw.bp_list, &bp_task_head);
	अन्यथा
		list_del(&bp->hw.bp_list);
पूर्ण

__weak पूर्णांक arch_reserve_bp_slot(काष्ठा perf_event *bp)
अणु
	वापस 0;
पूर्ण

__weak व्योम arch_release_bp_slot(काष्ठा perf_event *bp)
अणु
पूर्ण

/*
 * Function to perक्रमm processor-specअगरic cleanup during unregistration
 */
__weak व्योम arch_unरेजिस्टर_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp)
अणु
	/*
	 * A weak stub function here क्रम those archs that करोn't define
	 * it inside arch/.../kernel/hw_अवरोधpoपूर्णांक.c
	 */
पूर्ण

/*
 * Constraपूर्णांकs to check beक्रमe allowing this new अवरोधpoपूर्णांक counter:
 *
 *  == Non-pinned counter == (Considered as pinned क्रम now)
 *
 *   - If attached to a single cpu, check:
 *
 *       (per_cpu(info->flexible, cpu) || (per_cpu(info->cpu_pinned, cpu)
 *           + max(per_cpu(info->tsk_pinned, cpu)))) < HBP_NUM
 *
 *       -> If there are alपढ़ोy non-pinned counters in this cpu, it means
 *          there is alपढ़ोy a मुक्त slot क्रम them.
 *          Otherwise, we check that the maximum number of per task
 *          अवरोधpoपूर्णांकs (क्रम this cpu) plus the number of per cpu अवरोधpoपूर्णांक
 *          (क्रम this cpu) करोesn't cover every रेजिस्टरs.
 *
 *   - If attached to every cpus, check:
 *
 *       (per_cpu(info->flexible, *) || (max(per_cpu(info->cpu_pinned, *))
 *           + max(per_cpu(info->tsk_pinned, *)))) < HBP_NUM
 *
 *       -> This is roughly the same, except we check the number of per cpu
 *          bp क्रम every cpu and we keep the max one. Same क्रम the per tasks
 *          अवरोधpoपूर्णांकs.
 *
 *
 * == Pinned counter ==
 *
 *   - If attached to a single cpu, check:
 *
 *       ((per_cpu(info->flexible, cpu) > 1) + per_cpu(info->cpu_pinned, cpu)
 *            + max(per_cpu(info->tsk_pinned, cpu))) < HBP_NUM
 *
 *       -> Same checks as beक्रमe. But now the info->flexible, अगर any, must keep
 *          one रेजिस्टर at least (or they will never be fed).
 *
 *   - If attached to every cpus, check:
 *
 *       ((per_cpu(info->flexible, *) > 1) + max(per_cpu(info->cpu_pinned, *))
 *            + max(per_cpu(info->tsk_pinned, *))) < HBP_NUM
 */
अटल पूर्णांक __reserve_bp_slot(काष्ठा perf_event *bp, u64 bp_type)
अणु
	काष्ठा bp_busy_slots slots = अणु0पूर्ण;
	क्रमागत bp_type_idx type;
	पूर्णांक weight;
	पूर्णांक ret;

	/* We couldn't initialize अवरोधpoपूर्णांक स्थिरraपूर्णांकs on boot */
	अगर (!स्थिरraपूर्णांकs_initialized)
		वापस -ENOMEM;

	/* Basic checks */
	अगर (bp_type == HW_BREAKPOINT_EMPTY ||
	    bp_type == HW_BREAKPOINT_INVALID)
		वापस -EINVAL;

	type = find_slot_idx(bp_type);
	weight = hw_अवरोधpoपूर्णांक_weight(bp);

	fetch_bp_busy_slots(&slots, bp, type);
	/*
	 * Simulate the addition of this अवरोधpoपूर्णांक to the स्थिरraपूर्णांकs
	 * and see the result.
	 */
	fetch_this_slot(&slots, weight);

	/* Flexible counters need to keep at least one slot */
	अगर (slots.pinned + (!!slots.flexible) > nr_slots[type])
		वापस -ENOSPC;

	ret = arch_reserve_bp_slot(bp);
	अगर (ret)
		वापस ret;

	toggle_bp_slot(bp, true, type, weight);

	वापस 0;
पूर्ण

पूर्णांक reserve_bp_slot(काष्ठा perf_event *bp)
अणु
	पूर्णांक ret;

	mutex_lock(&nr_bp_mutex);

	ret = __reserve_bp_slot(bp, bp->attr.bp_type);

	mutex_unlock(&nr_bp_mutex);

	वापस ret;
पूर्ण

अटल व्योम __release_bp_slot(काष्ठा perf_event *bp, u64 bp_type)
अणु
	क्रमागत bp_type_idx type;
	पूर्णांक weight;

	arch_release_bp_slot(bp);

	type = find_slot_idx(bp_type);
	weight = hw_अवरोधpoपूर्णांक_weight(bp);
	toggle_bp_slot(bp, false, type, weight);
पूर्ण

व्योम release_bp_slot(काष्ठा perf_event *bp)
अणु
	mutex_lock(&nr_bp_mutex);

	arch_unरेजिस्टर_hw_अवरोधpoपूर्णांक(bp);
	__release_bp_slot(bp, bp->attr.bp_type);

	mutex_unlock(&nr_bp_mutex);
पूर्ण

अटल पूर्णांक __modअगरy_bp_slot(काष्ठा perf_event *bp, u64 old_type, u64 new_type)
अणु
	पूर्णांक err;

	__release_bp_slot(bp, old_type);

	err = __reserve_bp_slot(bp, new_type);
	अगर (err) अणु
		/*
		 * Reserve the old_type slot back in हाल
		 * there's no space क्रम the new type.
		 *
		 * This must succeed, because we just released
		 * the old_type slot in the __release_bp_slot
		 * call above. If not, something is broken.
		 */
		WARN_ON(__reserve_bp_slot(bp, old_type));
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक modअगरy_bp_slot(काष्ठा perf_event *bp, u64 old_type, u64 new_type)
अणु
	पूर्णांक ret;

	mutex_lock(&nr_bp_mutex);
	ret = __modअगरy_bp_slot(bp, old_type, new_type);
	mutex_unlock(&nr_bp_mutex);
	वापस ret;
पूर्ण

/*
 * Allow the kernel debugger to reserve अवरोधpoपूर्णांक slots without
 * taking a lock using the dbg_* variant of क्रम the reserve and
 * release अवरोधpoपूर्णांक slots.
 */
पूर्णांक dbg_reserve_bp_slot(काष्ठा perf_event *bp)
अणु
	अगर (mutex_is_locked(&nr_bp_mutex))
		वापस -1;

	वापस __reserve_bp_slot(bp, bp->attr.bp_type);
पूर्ण

पूर्णांक dbg_release_bp_slot(काष्ठा perf_event *bp)
अणु
	अगर (mutex_is_locked(&nr_bp_mutex))
		वापस -1;

	__release_bp_slot(bp, bp->attr.bp_type);

	वापस 0;
पूर्ण

अटल पूर्णांक hw_अवरोधpoपूर्णांक_parse(काष्ठा perf_event *bp,
			       स्थिर काष्ठा perf_event_attr *attr,
			       काष्ठा arch_hw_अवरोधpoपूर्णांक *hw)
अणु
	पूर्णांक err;

	err = hw_अवरोधpoपूर्णांक_arch_parse(bp, attr, hw);
	अगर (err)
		वापस err;

	अगर (arch_check_bp_in_kernelspace(hw)) अणु
		अगर (attr->exclude_kernel)
			वापस -EINVAL;
		/*
		 * Don't let unprivileged users set a अवरोधpoपूर्णांक in the trap
		 * path to aव्योम trap recursion attacks.
		 */
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक रेजिस्टर_perf_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक hw = अणु पूर्ण;
	पूर्णांक err;

	err = reserve_bp_slot(bp);
	अगर (err)
		वापस err;

	err = hw_अवरोधpoपूर्णांक_parse(bp, &bp->attr, &hw);
	अगर (err) अणु
		release_bp_slot(bp);
		वापस err;
	पूर्ण

	bp->hw.info = hw;

	वापस 0;
पूर्ण

/**
 * रेजिस्टर_user_hw_अवरोधpoपूर्णांक - रेजिस्टर a hardware अवरोधpoपूर्णांक क्रम user space
 * @attr: अवरोधpoपूर्णांक attributes
 * @triggered: callback to trigger when we hit the अवरोधpoपूर्णांक
 * @tsk: poपूर्णांकer to 'task_struct' of the process to which the address beदीर्घs
 */
काष्ठा perf_event *
रेजिस्टर_user_hw_अवरोधpoपूर्णांक(काष्ठा perf_event_attr *attr,
			    perf_overflow_handler_t triggered,
			    व्योम *context,
			    काष्ठा task_काष्ठा *tsk)
अणु
	वापस perf_event_create_kernel_counter(attr, -1, tsk, triggered,
						context);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_user_hw_अवरोधpoपूर्णांक);

अटल व्योम hw_अवरोधpoपूर्णांक_copy_attr(काष्ठा perf_event_attr *to,
				    काष्ठा perf_event_attr *from)
अणु
	to->bp_addr = from->bp_addr;
	to->bp_type = from->bp_type;
	to->bp_len  = from->bp_len;
	to->disabled = from->disabled;
पूर्ण

पूर्णांक
modअगरy_user_hw_अवरोधpoपूर्णांक_check(काष्ठा perf_event *bp, काष्ठा perf_event_attr *attr,
			        bool check)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक hw = अणु पूर्ण;
	पूर्णांक err;

	err = hw_अवरोधpoपूर्णांक_parse(bp, attr, &hw);
	अगर (err)
		वापस err;

	अगर (check) अणु
		काष्ठा perf_event_attr old_attr;

		old_attr = bp->attr;
		hw_अवरोधpoपूर्णांक_copy_attr(&old_attr, attr);
		अगर (स_भेद(&old_attr, attr, माप(*attr)))
			वापस -EINVAL;
	पूर्ण

	अगर (bp->attr.bp_type != attr->bp_type) अणु
		err = modअगरy_bp_slot(bp, bp->attr.bp_type, attr->bp_type);
		अगर (err)
			वापस err;
	पूर्ण

	hw_अवरोधpoपूर्णांक_copy_attr(&bp->attr, attr);
	bp->hw.info = hw;

	वापस 0;
पूर्ण

/**
 * modअगरy_user_hw_अवरोधpoपूर्णांक - modअगरy a user-space hardware अवरोधpoपूर्णांक
 * @bp: the अवरोधpoपूर्णांक काष्ठाure to modअगरy
 * @attr: new अवरोधpoपूर्णांक attributes
 */
पूर्णांक modअगरy_user_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp, काष्ठा perf_event_attr *attr)
अणु
	पूर्णांक err;

	/*
	 * modअगरy_user_hw_अवरोधpoपूर्णांक can be invoked with IRQs disabled and hence it
	 * will not be possible to उठाओ IPIs that invoke __perf_event_disable.
	 * So call the function directly after making sure we are targeting the
	 * current task.
	 */
	अगर (irqs_disabled() && bp->ctx && bp->ctx->task == current)
		perf_event_disable_local(bp);
	अन्यथा
		perf_event_disable(bp);

	err = modअगरy_user_hw_अवरोधpoपूर्णांक_check(bp, attr, false);

	अगर (!bp->attr.disabled)
		perf_event_enable(bp);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(modअगरy_user_hw_अवरोधpoपूर्णांक);

/**
 * unरेजिस्टर_hw_अवरोधpoपूर्णांक - unरेजिस्टर a user-space hardware अवरोधpoपूर्णांक
 * @bp: the अवरोधpoपूर्णांक काष्ठाure to unरेजिस्टर
 */
व्योम unरेजिस्टर_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp)
अणु
	अगर (!bp)
		वापस;
	perf_event_release_kernel(bp);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_hw_अवरोधpoपूर्णांक);

/**
 * रेजिस्टर_wide_hw_अवरोधpoपूर्णांक - रेजिस्टर a wide अवरोधpoपूर्णांक in the kernel
 * @attr: अवरोधpoपूर्णांक attributes
 * @triggered: callback to trigger when we hit the अवरोधpoपूर्णांक
 *
 * @वापस a set of per_cpu poपूर्णांकers to perf events
 */
काष्ठा perf_event * __percpu *
रेजिस्टर_wide_hw_अवरोधpoपूर्णांक(काष्ठा perf_event_attr *attr,
			    perf_overflow_handler_t triggered,
			    व्योम *context)
अणु
	काष्ठा perf_event * __percpu *cpu_events, *bp;
	दीर्घ err = 0;
	पूर्णांक cpu;

	cpu_events = alloc_percpu(typeof(*cpu_events));
	अगर (!cpu_events)
		वापस (व्योम __percpu __क्रमce *)ERR_PTR(-ENOMEM);

	get_online_cpus();
	क्रम_each_online_cpu(cpu) अणु
		bp = perf_event_create_kernel_counter(attr, cpu, शून्य,
						      triggered, context);
		अगर (IS_ERR(bp)) अणु
			err = PTR_ERR(bp);
			अवरोध;
		पूर्ण

		per_cpu(*cpu_events, cpu) = bp;
	पूर्ण
	put_online_cpus();

	अगर (likely(!err))
		वापस cpu_events;

	unरेजिस्टर_wide_hw_अवरोधpoपूर्णांक(cpu_events);
	वापस (व्योम __percpu __क्रमce *)ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_wide_hw_अवरोधpoपूर्णांक);

/**
 * unरेजिस्टर_wide_hw_अवरोधpoपूर्णांक - unरेजिस्टर a wide अवरोधpoपूर्णांक in the kernel
 * @cpu_events: the per cpu set of events to unरेजिस्टर
 */
व्योम unरेजिस्टर_wide_hw_अवरोधpoपूर्णांक(काष्ठा perf_event * __percpu *cpu_events)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		unरेजिस्टर_hw_अवरोधpoपूर्णांक(per_cpu(*cpu_events, cpu));

	मुक्त_percpu(cpu_events);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_wide_hw_अवरोधpoपूर्णांक);

अटल काष्ठा notअगरier_block hw_अवरोधpoपूर्णांक_exceptions_nb = अणु
	.notअगरier_call = hw_अवरोधpoपूर्णांक_exceptions_notअगरy,
	/* we need to be notअगरied first */
	.priority = 0x7fffffff
पूर्ण;

अटल व्योम bp_perf_event_destroy(काष्ठा perf_event *event)
अणु
	release_bp_slot(event);
पूर्ण

अटल पूर्णांक hw_अवरोधpoपूर्णांक_event_init(काष्ठा perf_event *bp)
अणु
	पूर्णांक err;

	अगर (bp->attr.type != PERF_TYPE_BREAKPOINT)
		वापस -ENOENT;

	/*
	 * no branch sampling क्रम अवरोधpoपूर्णांक events
	 */
	अगर (has_branch_stack(bp))
		वापस -EOPNOTSUPP;

	err = रेजिस्टर_perf_hw_अवरोधpoपूर्णांक(bp);
	अगर (err)
		वापस err;

	bp->destroy = bp_perf_event_destroy;

	वापस 0;
पूर्ण

अटल पूर्णांक hw_अवरोधpoपूर्णांक_add(काष्ठा perf_event *bp, पूर्णांक flags)
अणु
	अगर (!(flags & PERF_EF_START))
		bp->hw.state = PERF_HES_STOPPED;

	अगर (is_sampling_event(bp)) अणु
		bp->hw.last_period = bp->hw.sample_period;
		perf_swevent_set_period(bp);
	पूर्ण

	वापस arch_install_hw_अवरोधpoपूर्णांक(bp);
पूर्ण

अटल व्योम hw_अवरोधpoपूर्णांक_del(काष्ठा perf_event *bp, पूर्णांक flags)
अणु
	arch_uninstall_hw_अवरोधpoपूर्णांक(bp);
पूर्ण

अटल व्योम hw_अवरोधpoपूर्णांक_start(काष्ठा perf_event *bp, पूर्णांक flags)
अणु
	bp->hw.state = 0;
पूर्ण

अटल व्योम hw_अवरोधpoपूर्णांक_stop(काष्ठा perf_event *bp, पूर्णांक flags)
अणु
	bp->hw.state = PERF_HES_STOPPED;
पूर्ण

अटल काष्ठा pmu perf_अवरोधpoपूर्णांक = अणु
	.task_ctx_nr	= perf_sw_context, /* could eventually get its own */

	.event_init	= hw_अवरोधpoपूर्णांक_event_init,
	.add		= hw_अवरोधpoपूर्णांक_add,
	.del		= hw_अवरोधpoपूर्णांक_del,
	.start		= hw_अवरोधpoपूर्णांक_start,
	.stop		= hw_अवरोधpoपूर्णांक_stop,
	.पढ़ो		= hw_अवरोधpoपूर्णांक_pmu_पढ़ो,
पूर्ण;

पूर्णांक __init init_hw_अवरोधpoपूर्णांक(व्योम)
अणु
	पूर्णांक cpu, err_cpu;
	पूर्णांक i;

	क्रम (i = 0; i < TYPE_MAX; i++)
		nr_slots[i] = hw_अवरोधpoपूर्णांक_slots(i);

	क्रम_each_possible_cpu(cpu) अणु
		क्रम (i = 0; i < TYPE_MAX; i++) अणु
			काष्ठा bp_cpuinfo *info = get_bp_info(cpu, i);

			info->tsk_pinned = kसुस्मृति(nr_slots[i], माप(पूर्णांक),
							GFP_KERNEL);
			अगर (!info->tsk_pinned)
				जाओ err_alloc;
		पूर्ण
	पूर्ण

	स्थिरraपूर्णांकs_initialized = 1;

	perf_pmu_रेजिस्टर(&perf_अवरोधpoपूर्णांक, "breakpoint", PERF_TYPE_BREAKPOINT);

	वापस रेजिस्टर_die_notअगरier(&hw_अवरोधpoपूर्णांक_exceptions_nb);

 err_alloc:
	क्रम_each_possible_cpu(err_cpu) अणु
		क्रम (i = 0; i < TYPE_MAX; i++)
			kमुक्त(get_bp_info(err_cpu, i)->tsk_pinned);
		अगर (err_cpu == cpu)
			अवरोध;
	पूर्ण

	वापस -ENOMEM;
पूर्ण


