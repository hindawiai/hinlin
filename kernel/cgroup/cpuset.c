<शैली गुरु>
/*
 *  kernel/cpuset.c
 *
 *  Processor and Memory placement स्थिरraपूर्णांकs क्रम sets of tasks.
 *
 *  Copyright (C) 2003 BULL SA.
 *  Copyright (C) 2004-2007 Silicon Graphics, Inc.
 *  Copyright (C) 2006 Google, Inc
 *
 *  Portions derived from Patrick Mochel's sysfs code.
 *  sysfs is Copyright (c) 2001-3 Patrick Mochel
 *
 *  2003-10-10 Written by Simon Derr.
 *  2003-10-22 Updates by Stephen Hemminger.
 *  2004 May-July Rework by Paul Jackson.
 *  2006 Rework by Paul Menage to use generic cgroups
 *  2008 Rework of the scheduler करोमुख्यs and CPU hotplug handling
 *       by Max Krasnyansky
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of the Linux
 *  distribution क्रम more details.
 */

#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kmod.h>
#समावेश <linux/list.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/mm.h>
#समावेश <linux/memory.h>
#समावेश <linux/export.h>
#समावेश <linux/mount.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/namei.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/deadline.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/security.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/समय.स>
#समावेश <linux/समय64.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/sort.h>
#समावेश <linux/oom.h>
#समावेश <linux/sched/isolation.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>
#समावेश <linux/mutex.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/रुको.h>

DEFINE_STATIC_KEY_FALSE(cpusets_pre_enable_key);
DEFINE_STATIC_KEY_FALSE(cpusets_enabled_key);

/* See "Frequency meter" comments, below. */

काष्ठा fmeter अणु
	पूर्णांक cnt;		/* unprocessed events count */
	पूर्णांक val;		/* most recent output value */
	समय64_t समय;		/* घड़ी (secs) when val computed */
	spinlock_t lock;	/* guards पढ़ो or ग_लिखो of above */
पूर्ण;

काष्ठा cpuset अणु
	काष्ठा cgroup_subsys_state css;

	अचिन्हित दीर्घ flags;		/* "unsigned long" so bitops work */

	/*
	 * On शेष hierarchy:
	 *
	 * The user-configured masks can only be changed by writing to
	 * cpuset.cpus and cpuset.mems, and won't be limited by the
	 * parent masks.
	 *
	 * The effective masks is the real masks that apply to the tasks
	 * in the cpuset. They may be changed अगर the configured masks are
	 * changed or hotplug happens.
	 *
	 * effective_mask == configured_mask & parent's effective_mask,
	 * and अगर it ends up empty, it will inherit the parent's mask.
	 *
	 *
	 * On legacy hierarchy:
	 *
	 * The user-configured masks are always the same with effective masks.
	 */

	/* user-configured CPUs and Memory Nodes allow to tasks */
	cpumask_var_t cpus_allowed;
	nodemask_t mems_allowed;

	/* effective CPUs and Memory Nodes allow to tasks */
	cpumask_var_t effective_cpus;
	nodemask_t effective_mems;

	/*
	 * CPUs allocated to child sub-partitions (शेष hierarchy only)
	 * - CPUs granted by the parent = effective_cpus U subparts_cpus
	 * - effective_cpus and subparts_cpus are mutually exclusive.
	 *
	 * effective_cpus contains only onlined CPUs, but subparts_cpus
	 * may have offlined ones.
	 */
	cpumask_var_t subparts_cpus;

	/*
	 * This is old Memory Nodes tasks took on.
	 *
	 * - top_cpuset.old_mems_allowed is initialized to mems_allowed.
	 * - A new cpuset's old_mems_allowed is initialized when some
	 *   task is moved पूर्णांकo it.
	 * - old_mems_allowed is used in cpuset_migrate_mm() when we change
	 *   cpuset.mems_allowed and have tasks' nodemask updated, and
	 *   then old_mems_allowed is updated to mems_allowed.
	 */
	nodemask_t old_mems_allowed;

	काष्ठा fmeter fmeter;		/* memory_pressure filter */

	/*
	 * Tasks are being attached to this cpuset.  Used to prevent
	 * zeroing cpus/mems_allowed between ->can_attach() and ->attach().
	 */
	पूर्णांक attach_in_progress;

	/* partition number क्रम rebuild_sched_करोमुख्यs() */
	पूर्णांक pn;

	/* क्रम custom sched करोमुख्य */
	पूर्णांक relax_करोमुख्य_level;

	/* number of CPUs in subparts_cpus */
	पूर्णांक nr_subparts_cpus;

	/* partition root state */
	पूर्णांक partition_root_state;

	/*
	 * Default hierarchy only:
	 * use_parent_ecpus - set अगर using parent's effective_cpus
	 * child_ecpus_count - # of children with use_parent_ecpus set
	 */
	पूर्णांक use_parent_ecpus;
	पूर्णांक child_ecpus_count;
पूर्ण;

/*
 * Partition root states:
 *
 *   0 - not a partition root
 *
 *   1 - partition root
 *
 *  -1 - invalid partition root
 *       None of the cpus in cpus_allowed can be put पूर्णांकo the parent's
 *       subparts_cpus. In this हाल, the cpuset is not a real partition
 *       root anymore.  However, the CPU_EXCLUSIVE bit will still be set
 *       and the cpuset can be restored back to a partition root अगर the
 *       parent cpuset can give more CPUs back to this child cpuset.
 */
#घोषणा PRS_DISABLED		0
#घोषणा PRS_ENABLED		1
#घोषणा PRS_ERROR		-1

/*
 * Temporary cpumasks क्रम working with partitions that are passed among
 * functions to aव्योम memory allocation in inner functions.
 */
काष्ठा पंचांगpmasks अणु
	cpumask_var_t addmask, delmask;	/* For partition root */
	cpumask_var_t new_cpus;		/* For update_cpumasks_hier() */
पूर्ण;

अटल अंतरभूत काष्ठा cpuset *css_cs(काष्ठा cgroup_subsys_state *css)
अणु
	वापस css ? container_of(css, काष्ठा cpuset, css) : शून्य;
पूर्ण

/* Retrieve the cpuset क्रम a task */
अटल अंतरभूत काष्ठा cpuset *task_cs(काष्ठा task_काष्ठा *task)
अणु
	वापस css_cs(task_css(task, cpuset_cgrp_id));
पूर्ण

अटल अंतरभूत काष्ठा cpuset *parent_cs(काष्ठा cpuset *cs)
अणु
	वापस css_cs(cs->css.parent);
पूर्ण

/* bits in काष्ठा cpuset flags field */
प्रकार क्रमागत अणु
	CS_ONLINE,
	CS_CPU_EXCLUSIVE,
	CS_MEM_EXCLUSIVE,
	CS_MEM_HARDWALL,
	CS_MEMORY_MIGRATE,
	CS_SCHED_LOAD_BALANCE,
	CS_SPREAD_PAGE,
	CS_SPREAD_SLAB,
पूर्ण cpuset_flagbits_t;

/* convenient tests क्रम these bits */
अटल अंतरभूत bool is_cpuset_online(काष्ठा cpuset *cs)
अणु
	वापस test_bit(CS_ONLINE, &cs->flags) && !css_is_dying(&cs->css);
पूर्ण

अटल अंतरभूत पूर्णांक is_cpu_exclusive(स्थिर काष्ठा cpuset *cs)
अणु
	वापस test_bit(CS_CPU_EXCLUSIVE, &cs->flags);
पूर्ण

अटल अंतरभूत पूर्णांक is_mem_exclusive(स्थिर काष्ठा cpuset *cs)
अणु
	वापस test_bit(CS_MEM_EXCLUSIVE, &cs->flags);
पूर्ण

अटल अंतरभूत पूर्णांक is_mem_hardwall(स्थिर काष्ठा cpuset *cs)
अणु
	वापस test_bit(CS_MEM_HARDWALL, &cs->flags);
पूर्ण

अटल अंतरभूत पूर्णांक is_sched_load_balance(स्थिर काष्ठा cpuset *cs)
अणु
	वापस test_bit(CS_SCHED_LOAD_BALANCE, &cs->flags);
पूर्ण

अटल अंतरभूत पूर्णांक is_memory_migrate(स्थिर काष्ठा cpuset *cs)
अणु
	वापस test_bit(CS_MEMORY_MIGRATE, &cs->flags);
पूर्ण

अटल अंतरभूत पूर्णांक is_spपढ़ो_page(स्थिर काष्ठा cpuset *cs)
अणु
	वापस test_bit(CS_SPREAD_PAGE, &cs->flags);
पूर्ण

अटल अंतरभूत पूर्णांक is_spपढ़ो_slab(स्थिर काष्ठा cpuset *cs)
अणु
	वापस test_bit(CS_SPREAD_SLAB, &cs->flags);
पूर्ण

अटल अंतरभूत पूर्णांक is_partition_root(स्थिर काष्ठा cpuset *cs)
अणु
	वापस cs->partition_root_state > 0;
पूर्ण

अटल काष्ठा cpuset top_cpuset = अणु
	.flags = ((1 << CS_ONLINE) | (1 << CS_CPU_EXCLUSIVE) |
		  (1 << CS_MEM_EXCLUSIVE)),
	.partition_root_state = PRS_ENABLED,
पूर्ण;

/**
 * cpuset_क्रम_each_child - traverse online children of a cpuset
 * @child_cs: loop cursor poपूर्णांकing to the current child
 * @pos_css: used क्रम iteration
 * @parent_cs: target cpuset to walk children of
 *
 * Walk @child_cs through the online children of @parent_cs.  Must be used
 * with RCU पढ़ो locked.
 */
#घोषणा cpuset_क्रम_each_child(child_cs, pos_css, parent_cs)		\
	css_क्रम_each_child((pos_css), &(parent_cs)->css)		\
		अगर (is_cpuset_online(((child_cs) = css_cs((pos_css)))))

/**
 * cpuset_क्रम_each_descendant_pre - pre-order walk of a cpuset's descendants
 * @des_cs: loop cursor poपूर्णांकing to the current descendant
 * @pos_css: used क्रम iteration
 * @root_cs: target cpuset to walk ancestor of
 *
 * Walk @des_cs through the online descendants of @root_cs.  Must be used
 * with RCU पढ़ो locked.  The caller may modअगरy @pos_css by calling
 * css_righपंचांगost_descendant() to skip subtree.  @root_cs is included in the
 * iteration and the first node to be visited.
 */
#घोषणा cpuset_क्रम_each_descendant_pre(des_cs, pos_css, root_cs)	\
	css_क्रम_each_descendant_pre((pos_css), &(root_cs)->css)		\
		अगर (is_cpuset_online(((des_cs) = css_cs((pos_css)))))

/*
 * There are two global locks guarding cpuset काष्ठाures - cpuset_mutex and
 * callback_lock. We also require taking task_lock() when dereferencing a
 * task's cpuset poपूर्णांकer. See "The task_lock() exception", at the end of this
 * comment.
 *
 * A task must hold both locks to modअगरy cpusets.  If a task holds
 * cpuset_mutex, then it blocks others wanting that mutex, ensuring that it
 * is the only task able to also acquire callback_lock and be able to
 * modअगरy cpusets.  It can perक्रमm various checks on the cpuset काष्ठाure
 * first, knowing nothing will change.  It can also allocate memory जबतक
 * just holding cpuset_mutex.  While it is perक्रमming these checks, various
 * callback routines can briefly acquire callback_lock to query cpusets.
 * Once it is पढ़ोy to make the changes, it takes callback_lock, blocking
 * everyone अन्यथा.
 *
 * Calls to the kernel memory allocator can not be made जबतक holding
 * callback_lock, as that would risk द्विगुन tripping on callback_lock
 * from one of the callbacks पूर्णांकo the cpuset code from within
 * __alloc_pages().
 *
 * If a task is only holding callback_lock, then it has पढ़ो-only
 * access to cpusets.
 *
 * Now, the task_काष्ठा fields mems_allowed and mempolicy may be changed
 * by other task, we use alloc_lock in the task_काष्ठा fields to protect
 * them.
 *
 * The cpuset_common_file_पढ़ो() handlers only hold callback_lock across
 * small pieces of code, such as when पढ़ोing out possibly multi-word
 * cpumasks and nodemasks.
 *
 * Accessing a task's cpuset should be करोne in accordance with the
 * guidelines क्रम accessing subप्रणाली state in kernel/cgroup.c
 */

DEFINE_STATIC_PERCPU_RWSEM(cpuset_rwsem);

व्योम cpuset_पढ़ो_lock(व्योम)
अणु
	percpu_करोwn_पढ़ो(&cpuset_rwsem);
पूर्ण

व्योम cpuset_पढ़ो_unlock(व्योम)
अणु
	percpu_up_पढ़ो(&cpuset_rwsem);
पूर्ण

अटल DEFINE_SPINLOCK(callback_lock);

अटल काष्ठा workqueue_काष्ठा *cpuset_migrate_mm_wq;

/*
 * CPU / memory hotplug is handled asynchronously.
 */
अटल व्योम cpuset_hotplug_workfn(काष्ठा work_काष्ठा *work);
अटल DECLARE_WORK(cpuset_hotplug_work, cpuset_hotplug_workfn);

अटल DECLARE_WAIT_QUEUE_HEAD(cpuset_attach_wq);

/*
 * Cgroup v2 behavior is used on the "cpus" and "mems" control files when
 * on शेष hierarchy or when the cpuset_v2_mode flag is set by mounting
 * the v1 cpuset cgroup fileप्रणाली with the "cpuset_v2_mode" mount option.
 * With v2 behavior, "cpus" and "mems" are always what the users have
 * requested and won't be changed by hotplug events. Only the effective
 * cpus or mems will be affected.
 */
अटल अंतरभूत bool is_in_v2_mode(व्योम)
अणु
	वापस cgroup_subsys_on_dfl(cpuset_cgrp_subsys) ||
	      (cpuset_cgrp_subsys.root->flags & CGRP_ROOT_CPUSET_V2_MODE);
पूर्ण

/*
 * Return in pmask the portion of a cpusets's cpus_allowed that
 * are online.  If none are online, walk up the cpuset hierarchy
 * until we find one that करोes have some online cpus.
 *
 * One way or another, we guarantee to वापस some non-empty subset
 * of cpu_online_mask.
 *
 * Call with callback_lock or cpuset_mutex held.
 */
अटल व्योम guarantee_online_cpus(काष्ठा cpuset *cs, काष्ठा cpumask *pmask)
अणु
	जबतक (!cpumask_पूर्णांकersects(cs->effective_cpus, cpu_online_mask)) अणु
		cs = parent_cs(cs);
		अगर (unlikely(!cs)) अणु
			/*
			 * The top cpuset करोesn't have any online cpu as a
			 * consequence of a race between cpuset_hotplug_work
			 * and cpu hotplug notअगरier.  But we know the top
			 * cpuset's effective_cpus is on its way to be
			 * identical to cpu_online_mask.
			 */
			cpumask_copy(pmask, cpu_online_mask);
			वापस;
		पूर्ण
	पूर्ण
	cpumask_and(pmask, cs->effective_cpus, cpu_online_mask);
पूर्ण

/*
 * Return in *pmask the portion of a cpusets's mems_allowed that
 * are online, with memory.  If none are online with memory, walk
 * up the cpuset hierarchy until we find one that करोes have some
 * online mems.  The top cpuset always has some mems online.
 *
 * One way or another, we guarantee to वापस some non-empty subset
 * of node_states[N_MEMORY].
 *
 * Call with callback_lock or cpuset_mutex held.
 */
अटल व्योम guarantee_online_mems(काष्ठा cpuset *cs, nodemask_t *pmask)
अणु
	जबतक (!nodes_पूर्णांकersects(cs->effective_mems, node_states[N_MEMORY]))
		cs = parent_cs(cs);
	nodes_and(*pmask, cs->effective_mems, node_states[N_MEMORY]);
पूर्ण

/*
 * update task's spread flag if cpuset's page/slab spपढ़ो flag is set
 *
 * Call with callback_lock or cpuset_mutex held.
 */
अटल व्योम cpuset_update_task_spपढ़ो_flag(काष्ठा cpuset *cs,
					काष्ठा task_काष्ठा *tsk)
अणु
	अगर (is_spपढ़ो_page(cs))
		task_set_spपढ़ो_page(tsk);
	अन्यथा
		task_clear_spपढ़ो_page(tsk);

	अगर (is_spपढ़ो_slab(cs))
		task_set_spपढ़ो_slab(tsk);
	अन्यथा
		task_clear_spपढ़ो_slab(tsk);
पूर्ण

/*
 * is_cpuset_subset(p, q) - Is cpuset p a subset of cpuset q?
 *
 * One cpuset is a subset of another अगर all its allowed CPUs and
 * Memory Nodes are a subset of the other, and its exclusive flags
 * are only set अगर the other's are set.  Call holding cpuset_mutex.
 */

अटल पूर्णांक is_cpuset_subset(स्थिर काष्ठा cpuset *p, स्थिर काष्ठा cpuset *q)
अणु
	वापस	cpumask_subset(p->cpus_allowed, q->cpus_allowed) &&
		nodes_subset(p->mems_allowed, q->mems_allowed) &&
		is_cpu_exclusive(p) <= is_cpu_exclusive(q) &&
		is_mem_exclusive(p) <= is_mem_exclusive(q);
पूर्ण

/**
 * alloc_cpumasks - allocate three cpumasks क्रम cpuset
 * @cs:  the cpuset that have cpumasks to be allocated.
 * @पंचांगp: the पंचांगpmasks काष्ठाure poपूर्णांकer
 * Return: 0 अगर successful, -ENOMEM otherwise.
 *
 * Only one of the two input arguments should be non-शून्य.
 */
अटल अंतरभूत पूर्णांक alloc_cpumasks(काष्ठा cpuset *cs, काष्ठा पंचांगpmasks *पंचांगp)
अणु
	cpumask_var_t *pmask1, *pmask2, *pmask3;

	अगर (cs) अणु
		pmask1 = &cs->cpus_allowed;
		pmask2 = &cs->effective_cpus;
		pmask3 = &cs->subparts_cpus;
	पूर्ण अन्यथा अणु
		pmask1 = &पंचांगp->new_cpus;
		pmask2 = &पंचांगp->addmask;
		pmask3 = &पंचांगp->delmask;
	पूर्ण

	अगर (!zalloc_cpumask_var(pmask1, GFP_KERNEL))
		वापस -ENOMEM;

	अगर (!zalloc_cpumask_var(pmask2, GFP_KERNEL))
		जाओ मुक्त_one;

	अगर (!zalloc_cpumask_var(pmask3, GFP_KERNEL))
		जाओ मुक्त_two;

	वापस 0;

मुक्त_two:
	मुक्त_cpumask_var(*pmask2);
मुक्त_one:
	मुक्त_cpumask_var(*pmask1);
	वापस -ENOMEM;
पूर्ण

/**
 * मुक्त_cpumasks - मुक्त cpumasks in a पंचांगpmasks काष्ठाure
 * @cs:  the cpuset that have cpumasks to be मुक्त.
 * @पंचांगp: the पंचांगpmasks काष्ठाure poपूर्णांकer
 */
अटल अंतरभूत व्योम मुक्त_cpumasks(काष्ठा cpuset *cs, काष्ठा पंचांगpmasks *पंचांगp)
अणु
	अगर (cs) अणु
		मुक्त_cpumask_var(cs->cpus_allowed);
		मुक्त_cpumask_var(cs->effective_cpus);
		मुक्त_cpumask_var(cs->subparts_cpus);
	पूर्ण
	अगर (पंचांगp) अणु
		मुक्त_cpumask_var(पंचांगp->new_cpus);
		मुक्त_cpumask_var(पंचांगp->addmask);
		मुक्त_cpumask_var(पंचांगp->delmask);
	पूर्ण
पूर्ण

/**
 * alloc_trial_cpuset - allocate a trial cpuset
 * @cs: the cpuset that the trial cpuset duplicates
 */
अटल काष्ठा cpuset *alloc_trial_cpuset(काष्ठा cpuset *cs)
अणु
	काष्ठा cpuset *trial;

	trial = kmemdup(cs, माप(*cs), GFP_KERNEL);
	अगर (!trial)
		वापस शून्य;

	अगर (alloc_cpumasks(trial, शून्य)) अणु
		kमुक्त(trial);
		वापस शून्य;
	पूर्ण

	cpumask_copy(trial->cpus_allowed, cs->cpus_allowed);
	cpumask_copy(trial->effective_cpus, cs->effective_cpus);
	वापस trial;
पूर्ण

/**
 * मुक्त_cpuset - मुक्त the cpuset
 * @cs: the cpuset to be मुक्तd
 */
अटल अंतरभूत व्योम मुक्त_cpuset(काष्ठा cpuset *cs)
अणु
	मुक्त_cpumasks(cs, शून्य);
	kमुक्त(cs);
पूर्ण

/*
 * validate_change() - Used to validate that any proposed cpuset change
 *		       follows the काष्ठाural rules क्रम cpusets.
 *
 * If we replaced the flag and mask values of the current cpuset
 * (cur) with those values in the trial cpuset (trial), would
 * our various subset and exclusive rules still be valid?  Presumes
 * cpuset_mutex held.
 *
 * 'cur' is the address of an actual, in-use cpuset.  Operations
 * such as list traversal that depend on the actual address of the
 * cpuset in the list must use cur below, not trial.
 *
 * 'trial' is the address of bulk काष्ठाure copy of cur, with
 * perhaps one or more of the fields cpus_allowed, mems_allowed,
 * or flags changed to new, trial values.
 *
 * Return 0 अगर valid, -त्रुटि_सं अगर not.
 */

अटल पूर्णांक validate_change(काष्ठा cpuset *cur, काष्ठा cpuset *trial)
अणु
	काष्ठा cgroup_subsys_state *css;
	काष्ठा cpuset *c, *par;
	पूर्णांक ret;

	rcu_पढ़ो_lock();

	/* Each of our child cpusets must be a subset of us */
	ret = -EBUSY;
	cpuset_क्रम_each_child(c, css, cur)
		अगर (!is_cpuset_subset(c, trial))
			जाओ out;

	/* Reमुख्यing checks करोn't apply to root cpuset */
	ret = 0;
	अगर (cur == &top_cpuset)
		जाओ out;

	par = parent_cs(cur);

	/* On legacy hierarchy, we must be a subset of our parent cpuset. */
	ret = -EACCES;
	अगर (!is_in_v2_mode() && !is_cpuset_subset(trial, par))
		जाओ out;

	/*
	 * If either I or some sibling (!= me) is exclusive, we can't
	 * overlap
	 */
	ret = -EINVAL;
	cpuset_क्रम_each_child(c, css, par) अणु
		अगर ((is_cpu_exclusive(trial) || is_cpu_exclusive(c)) &&
		    c != cur &&
		    cpumask_पूर्णांकersects(trial->cpus_allowed, c->cpus_allowed))
			जाओ out;
		अगर ((is_mem_exclusive(trial) || is_mem_exclusive(c)) &&
		    c != cur &&
		    nodes_पूर्णांकersects(trial->mems_allowed, c->mems_allowed))
			जाओ out;
	पूर्ण

	/*
	 * Cpusets with tasks - existing or newly being attached - can't
	 * be changed to have empty cpus_allowed or mems_allowed.
	 */
	ret = -ENOSPC;
	अगर ((cgroup_is_populated(cur->css.cgroup) || cur->attach_in_progress)) अणु
		अगर (!cpumask_empty(cur->cpus_allowed) &&
		    cpumask_empty(trial->cpus_allowed))
			जाओ out;
		अगर (!nodes_empty(cur->mems_allowed) &&
		    nodes_empty(trial->mems_allowed))
			जाओ out;
	पूर्ण

	/*
	 * We can't shrink if we won't have enough room क्रम SCHED_DEADLINE
	 * tasks.
	 */
	ret = -EBUSY;
	अगर (is_cpu_exclusive(cur) &&
	    !cpuset_cpumask_can_shrink(cur->cpus_allowed,
				       trial->cpus_allowed))
		जाओ out;

	ret = 0;
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SMP
/*
 * Helper routine क्रम generate_sched_करोमुख्यs().
 * Do cpusets a, b have overlapping effective cpus_allowed masks?
 */
अटल पूर्णांक cpusets_overlap(काष्ठा cpuset *a, काष्ठा cpuset *b)
अणु
	वापस cpumask_पूर्णांकersects(a->effective_cpus, b->effective_cpus);
पूर्ण

अटल व्योम
update_करोमुख्य_attr(काष्ठा sched_करोमुख्य_attr *dattr, काष्ठा cpuset *c)
अणु
	अगर (dattr->relax_करोमुख्य_level < c->relax_करोमुख्य_level)
		dattr->relax_करोमुख्य_level = c->relax_करोमुख्य_level;
	वापस;
पूर्ण

अटल व्योम update_करोमुख्य_attr_tree(काष्ठा sched_करोमुख्य_attr *dattr,
				    काष्ठा cpuset *root_cs)
अणु
	काष्ठा cpuset *cp;
	काष्ठा cgroup_subsys_state *pos_css;

	rcu_पढ़ो_lock();
	cpuset_क्रम_each_descendant_pre(cp, pos_css, root_cs) अणु
		/* skip the whole subtree अगर @cp करोesn't have any CPU */
		अगर (cpumask_empty(cp->cpus_allowed)) अणु
			pos_css = css_righपंचांगost_descendant(pos_css);
			जारी;
		पूर्ण

		अगर (is_sched_load_balance(cp))
			update_करोमुख्य_attr(dattr, cp);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* Must be called with cpuset_mutex held.  */
अटल अंतरभूत पूर्णांक nr_cpusets(व्योम)
अणु
	/* jump label reference count + the top-level cpuset */
	वापस अटल_key_count(&cpusets_enabled_key.key) + 1;
पूर्ण

/*
 * generate_sched_करोमुख्यs()
 *
 * This function builds a partial partition of the प्रणालीs CPUs
 * A 'partial partition' is a set of non-overlapping subsets whose
 * जोड़ is a subset of that set.
 * The output of this function needs to be passed to kernel/sched/core.c
 * partition_sched_करोमुख्यs() routine, which will rebuild the scheduler's
 * load balancing करोमुख्यs (sched करोमुख्यs) as specअगरied by that partial
 * partition.
 *
 * See "What is sched_load_balance" in Documentation/admin-guide/cgroup-v1/cpusets.rst
 * क्रम a background explanation of this.
 *
 * Does not वापस errors, on the theory that the callers of this
 * routine would rather not worry about failures to rebuild sched
 * करोमुख्यs when operating in the severe memory लघुage situations
 * that could cause allocation failures below.
 *
 * Must be called with cpuset_mutex held.
 *
 * The three key local variables below are:
 *    cp - cpuset poपूर्णांकer, used (together with pos_css) to perक्रमm a
 *	   top-करोwn scan of all cpusets. For our purposes, rebuilding
 *	   the schedulers sched करोमुख्यs, we can ignore !is_sched_load_
 *	   balance cpusets.
 *  csa  - (क्रम CpuSet Array) Array of poपूर्णांकers to all the cpusets
 *	   that need to be load balanced, क्रम convenient iterative
 *	   access by the subsequent code that finds the best partition,
 *	   i.e the set of करोमुख्यs (subsets) of CPUs such that the
 *	   cpus_allowed of every cpuset marked is_sched_load_balance
 *	   is a subset of one of these करोमुख्यs, जबतक there are as
 *	   many such करोमुख्यs as possible, each as small as possible.
 * करोms  - Conversion of 'csa' to an array of cpumasks, क्रम passing to
 *	   the kernel/sched/core.c routine partition_sched_करोमुख्यs() in a
 *	   convenient क्रमmat, that can be easily compared to the prior
 *	   value to determine what partition elements (sched करोमुख्यs)
 *	   were changed (added or हटाओd.)
 *
 * Finding the best partition (set of करोमुख्यs):
 *	The triple nested loops below over i, j, k scan over the
 *	load balanced cpusets (using the array of cpuset poपूर्णांकers in
 *	csa[]) looking क्रम pairs of cpusets that have overlapping
 *	cpus_allowed, but which करोn't have the same 'pn' partition
 *	number and gives them in the same partition number.  It keeps
 *	looping on the 'restart' label until it can no दीर्घer find
 *	any such pairs.
 *
 *	The जोड़ of the cpus_allowed masks from the set of
 *	all cpusets having the same 'pn' value then क्रमm the one
 *	element of the partition (one sched करोमुख्य) to be passed to
 *	partition_sched_करोमुख्यs().
 */
अटल पूर्णांक generate_sched_करोमुख्यs(cpumask_var_t **करोमुख्यs,
			काष्ठा sched_करोमुख्य_attr **attributes)
अणु
	काष्ठा cpuset *cp;	/* top-करोwn scan of cpusets */
	काष्ठा cpuset **csa;	/* array of all cpuset ptrs */
	पूर्णांक csn;		/* how many cpuset ptrs in csa so far */
	पूर्णांक i, j, k;		/* indices क्रम partition finding loops */
	cpumask_var_t *करोms;	/* resulting partition; i.e. sched करोमुख्यs */
	काष्ठा sched_करोमुख्य_attr *dattr;  /* attributes क्रम custom करोमुख्यs */
	पूर्णांक nकरोms = 0;		/* number of sched करोमुख्यs in result */
	पूर्णांक nslot;		/* next empty करोms[] काष्ठा cpumask slot */
	काष्ठा cgroup_subsys_state *pos_css;
	bool root_load_balance = is_sched_load_balance(&top_cpuset);

	करोms = शून्य;
	dattr = शून्य;
	csa = शून्य;

	/* Special हाल क्रम the 99% of प्रणालीs with one, full, sched करोमुख्य */
	अगर (root_load_balance && !top_cpuset.nr_subparts_cpus) अणु
		nकरोms = 1;
		करोms = alloc_sched_करोमुख्यs(nकरोms);
		अगर (!करोms)
			जाओ करोne;

		dattr = kदो_स्मृति(माप(काष्ठा sched_करोमुख्य_attr), GFP_KERNEL);
		अगर (dattr) अणु
			*dattr = SD_ATTR_INIT;
			update_करोमुख्य_attr_tree(dattr, &top_cpuset);
		पूर्ण
		cpumask_and(करोms[0], top_cpuset.effective_cpus,
			    housekeeping_cpumask(HK_FLAG_DOMAIN));

		जाओ करोne;
	पूर्ण

	csa = kदो_स्मृति_array(nr_cpusets(), माप(cp), GFP_KERNEL);
	अगर (!csa)
		जाओ करोne;
	csn = 0;

	rcu_पढ़ो_lock();
	अगर (root_load_balance)
		csa[csn++] = &top_cpuset;
	cpuset_क्रम_each_descendant_pre(cp, pos_css, &top_cpuset) अणु
		अगर (cp == &top_cpuset)
			जारी;
		/*
		 * Continue traversing beyond @cp अगरf @cp has some CPUs and
		 * isn't load balancing.  The क्रमmer is obvious.  The
		 * latter: All child cpusets contain a subset of the
		 * parent's cpus, so just skip them, and then we call
		 * update_करोमुख्य_attr_tree() to calc relax_करोमुख्य_level of
		 * the corresponding sched करोमुख्य.
		 *
		 * If root is load-balancing, we can skip @cp अगर it
		 * is a subset of the root's effective_cpus.
		 */
		अगर (!cpumask_empty(cp->cpus_allowed) &&
		    !(is_sched_load_balance(cp) &&
		      cpumask_पूर्णांकersects(cp->cpus_allowed,
					 housekeeping_cpumask(HK_FLAG_DOMAIN))))
			जारी;

		अगर (root_load_balance &&
		    cpumask_subset(cp->cpus_allowed, top_cpuset.effective_cpus))
			जारी;

		अगर (is_sched_load_balance(cp) &&
		    !cpumask_empty(cp->effective_cpus))
			csa[csn++] = cp;

		/* skip @cp's subtree अगर not a partition root */
		अगर (!is_partition_root(cp))
			pos_css = css_righपंचांगost_descendant(pos_css);
	पूर्ण
	rcu_पढ़ो_unlock();

	क्रम (i = 0; i < csn; i++)
		csa[i]->pn = i;
	nकरोms = csn;

restart:
	/* Find the best partition (set of sched करोमुख्यs) */
	क्रम (i = 0; i < csn; i++) अणु
		काष्ठा cpuset *a = csa[i];
		पूर्णांक apn = a->pn;

		क्रम (j = 0; j < csn; j++) अणु
			काष्ठा cpuset *b = csa[j];
			पूर्णांक bpn = b->pn;

			अगर (apn != bpn && cpusets_overlap(a, b)) अणु
				क्रम (k = 0; k < csn; k++) अणु
					काष्ठा cpuset *c = csa[k];

					अगर (c->pn == bpn)
						c->pn = apn;
				पूर्ण
				nकरोms--;	/* one less element */
				जाओ restart;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Now we know how many करोमुख्यs to create.
	 * Convert <csn, csa> to <nकरोms, करोms> and populate cpu masks.
	 */
	करोms = alloc_sched_करोमुख्यs(nकरोms);
	अगर (!करोms)
		जाओ करोne;

	/*
	 * The rest of the code, including the scheduler, can deal with
	 * dattr==शून्य हाल. No need to पात अगर alloc fails.
	 */
	dattr = kदो_स्मृति_array(nकरोms, माप(काष्ठा sched_करोमुख्य_attr),
			      GFP_KERNEL);

	क्रम (nslot = 0, i = 0; i < csn; i++) अणु
		काष्ठा cpuset *a = csa[i];
		काष्ठा cpumask *dp;
		पूर्णांक apn = a->pn;

		अगर (apn < 0) अणु
			/* Skip completed partitions */
			जारी;
		पूर्ण

		dp = करोms[nslot];

		अगर (nslot == nकरोms) अणु
			अटल पूर्णांक warnings = 10;
			अगर (warnings) अणु
				pr_warn("rebuild_sched_domains confused: nslot %d, ndoms %d, csn %d, i %d, apn %d\n",
					nslot, nकरोms, csn, i, apn);
				warnings--;
			पूर्ण
			जारी;
		पूर्ण

		cpumask_clear(dp);
		अगर (dattr)
			*(dattr + nslot) = SD_ATTR_INIT;
		क्रम (j = i; j < csn; j++) अणु
			काष्ठा cpuset *b = csa[j];

			अगर (apn == b->pn) अणु
				cpumask_or(dp, dp, b->effective_cpus);
				cpumask_and(dp, dp, housekeeping_cpumask(HK_FLAG_DOMAIN));
				अगर (dattr)
					update_करोमुख्य_attr_tree(dattr + nslot, b);

				/* Done with this partition */
				b->pn = -1;
			पूर्ण
		पूर्ण
		nslot++;
	पूर्ण
	BUG_ON(nslot != nकरोms);

करोne:
	kमुक्त(csa);

	/*
	 * Fallback to the शेष करोमुख्य अगर kदो_स्मृति() failed.
	 * See comments in partition_sched_करोमुख्यs().
	 */
	अगर (करोms == शून्य)
		nकरोms = 1;

	*करोमुख्यs    = करोms;
	*attributes = dattr;
	वापस nकरोms;
पूर्ण

अटल व्योम update_tasks_root_करोमुख्य(काष्ठा cpuset *cs)
अणु
	काष्ठा css_task_iter it;
	काष्ठा task_काष्ठा *task;

	css_task_iter_start(&cs->css, 0, &it);

	जबतक ((task = css_task_iter_next(&it)))
		dl_add_task_root_करोमुख्य(task);

	css_task_iter_end(&it);
पूर्ण

अटल व्योम rebuild_root_करोमुख्यs(व्योम)
अणु
	काष्ठा cpuset *cs = शून्य;
	काष्ठा cgroup_subsys_state *pos_css;

	percpu_rwsem_निश्चित_held(&cpuset_rwsem);
	lockdep_निश्चित_cpus_held();
	lockdep_निश्चित_held(&sched_करोमुख्यs_mutex);

	rcu_पढ़ो_lock();

	/*
	 * Clear शेष root करोमुख्य DL accounting, it will be computed again
	 * अगर a task beदीर्घs to it.
	 */
	dl_clear_root_करोमुख्य(&def_root_करोमुख्य);

	cpuset_क्रम_each_descendant_pre(cs, pos_css, &top_cpuset) अणु

		अगर (cpumask_empty(cs->effective_cpus)) अणु
			pos_css = css_righपंचांगost_descendant(pos_css);
			जारी;
		पूर्ण

		css_get(&cs->css);

		rcu_पढ़ो_unlock();

		update_tasks_root_करोमुख्य(cs);

		rcu_पढ़ो_lock();
		css_put(&cs->css);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम
partition_and_rebuild_sched_करोमुख्यs(पूर्णांक nकरोms_new, cpumask_var_t करोms_new[],
				    काष्ठा sched_करोमुख्य_attr *dattr_new)
अणु
	mutex_lock(&sched_करोमुख्यs_mutex);
	partition_sched_करोमुख्यs_locked(nकरोms_new, करोms_new, dattr_new);
	rebuild_root_करोमुख्यs();
	mutex_unlock(&sched_करोमुख्यs_mutex);
पूर्ण

/*
 * Rebuild scheduler करोमुख्यs.
 *
 * If the flag 'sched_load_balance' of any cpuset with non-empty
 * 'cpus' changes, or if the 'cpus' allowed changes in any cpuset
 * which has that flag enabled, or अगर any cpuset with a non-empty
 * 'cpus' is हटाओd, then call this routine to rebuild the
 * scheduler's dynamic sched करोमुख्यs.
 *
 * Call with cpuset_mutex held.  Takes get_online_cpus().
 */
अटल व्योम rebuild_sched_करोमुख्यs_locked(व्योम)
अणु
	काष्ठा cgroup_subsys_state *pos_css;
	काष्ठा sched_करोमुख्य_attr *attr;
	cpumask_var_t *करोms;
	काष्ठा cpuset *cs;
	पूर्णांक nकरोms;

	lockdep_निश्चित_cpus_held();
	percpu_rwsem_निश्चित_held(&cpuset_rwsem);

	/*
	 * If we have raced with CPU hotplug, वापस early to aव्योम
	 * passing करोms with offlined cpu to partition_sched_करोमुख्यs().
	 * Anyways, cpuset_hotplug_workfn() will rebuild sched करोमुख्यs.
	 *
	 * With no CPUs in any subpartitions, top_cpuset's effective CPUs
	 * should be the same as the active CPUs, so checking only top_cpuset
	 * is enough to detect racing CPU offlines.
	 */
	अगर (!top_cpuset.nr_subparts_cpus &&
	    !cpumask_equal(top_cpuset.effective_cpus, cpu_active_mask))
		वापस;

	/*
	 * With subpartition CPUs, however, the effective CPUs of a partition
	 * root should be only a subset of the active CPUs.  Since a CPU in any
	 * partition root could be offlined, all must be checked.
	 */
	अगर (top_cpuset.nr_subparts_cpus) अणु
		rcu_पढ़ो_lock();
		cpuset_क्रम_each_descendant_pre(cs, pos_css, &top_cpuset) अणु
			अगर (!is_partition_root(cs)) अणु
				pos_css = css_righपंचांगost_descendant(pos_css);
				जारी;
			पूर्ण
			अगर (!cpumask_subset(cs->effective_cpus,
					    cpu_active_mask)) अणु
				rcu_पढ़ो_unlock();
				वापस;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	/* Generate करोमुख्य masks and attrs */
	nकरोms = generate_sched_करोमुख्यs(&करोms, &attr);

	/* Have scheduler rebuild the करोमुख्यs */
	partition_and_rebuild_sched_करोमुख्यs(nकरोms, करोms, attr);
पूर्ण
#अन्यथा /* !CONFIG_SMP */
अटल व्योम rebuild_sched_करोमुख्यs_locked(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

व्योम rebuild_sched_करोमुख्यs(व्योम)
अणु
	get_online_cpus();
	percpu_करोwn_ग_लिखो(&cpuset_rwsem);
	rebuild_sched_करोमुख्यs_locked();
	percpu_up_ग_लिखो(&cpuset_rwsem);
	put_online_cpus();
पूर्ण

/**
 * update_tasks_cpumask - Update the cpumasks of tasks in the cpuset.
 * @cs: the cpuset in which each task's cpus_allowed mask needs to be changed
 *
 * Iterate through each task of @cs updating its cpus_allowed to the
 * effective cpuset's.  As this function is called with cpuset_mutex held,
 * cpuset membership stays stable.
 */
अटल व्योम update_tasks_cpumask(काष्ठा cpuset *cs)
अणु
	काष्ठा css_task_iter it;
	काष्ठा task_काष्ठा *task;

	css_task_iter_start(&cs->css, 0, &it);
	जबतक ((task = css_task_iter_next(&it)))
		set_cpus_allowed_ptr(task, cs->effective_cpus);
	css_task_iter_end(&it);
पूर्ण

/**
 * compute_effective_cpumask - Compute the effective cpumask of the cpuset
 * @new_cpus: the temp variable क्रम the new effective_cpus mask
 * @cs: the cpuset the need to recompute the new effective_cpus mask
 * @parent: the parent cpuset
 *
 * If the parent has subpartition CPUs, include them in the list of
 * allowable CPUs in computing the new effective_cpus mask. Since offlined
 * CPUs are not हटाओd from subparts_cpus, we have to use cpu_active_mask
 * to mask those out.
 */
अटल व्योम compute_effective_cpumask(काष्ठा cpumask *new_cpus,
				      काष्ठा cpuset *cs, काष्ठा cpuset *parent)
अणु
	अगर (parent->nr_subparts_cpus) अणु
		cpumask_or(new_cpus, parent->effective_cpus,
			   parent->subparts_cpus);
		cpumask_and(new_cpus, new_cpus, cs->cpus_allowed);
		cpumask_and(new_cpus, new_cpus, cpu_active_mask);
	पूर्ण अन्यथा अणु
		cpumask_and(new_cpus, cs->cpus_allowed, parent->effective_cpus);
	पूर्ण
पूर्ण

/*
 * Commands क्रम update_parent_subparts_cpumask
 */
क्रमागत subparts_cmd अणु
	partcmd_enable,		/* Enable partition root	 */
	partcmd_disable,	/* Disable partition root	 */
	partcmd_update,		/* Update parent's subparts_cpus */
पूर्ण;

/**
 * update_parent_subparts_cpumask - update subparts_cpus mask of parent cpuset
 * @cpuset:  The cpuset that requests change in partition root state
 * @cmd:     Partition root state change command
 * @newmask: Optional new cpumask क्रम partcmd_update
 * @पंचांगp:     Temporary addmask and delmask
 * Return:   0, 1 or an error code
 *
 * For partcmd_enable, the cpuset is being transक्रमmed from a non-partition
 * root to a partition root. The cpus_allowed mask of the given cpuset will
 * be put पूर्णांकo parent's subparts_cpus and taken away from parent's
 * effective_cpus. The function will वापस 0 अगर all the CPUs listed in
 * cpus_allowed can be granted or an error code will be वापसed.
 *
 * For partcmd_disable, the cpuset is being transofrmed from a partition
 * root back to a non-partition root. any CPUs in cpus_allowed that are in
 * parent's subparts_cpus will be taken away from that cpumask and put back
 * पूर्णांकo parent's effective_cpus. 0 should always be वापसed.
 *
 * For partcmd_update, अगर the optional newmask is specअगरied, the cpu
 * list is to be changed from cpus_allowed to newmask. Otherwise,
 * cpus_allowed is assumed to reमुख्य the same. The cpuset should either
 * be a partition root or an invalid partition root. The partition root
 * state may change अगर newmask is शून्य and none of the requested CPUs can
 * be granted by the parent. The function will वापस 1 अगर changes to
 * parent's subparts_cpus and effective_cpus happen or 0 otherwise.
 * Error code should only be वापसed when newmask is non-शून्य.
 *
 * The partcmd_enable and partcmd_disable commands are used by
 * update_prstate(). The partcmd_update command is used by
 * update_cpumasks_hier() with newmask शून्य and update_cpumask() with
 * newmask set.
 *
 * The checking is more strict when enabling partition root than the
 * other two commands.
 *
 * Because of the implicit cpu exclusive nature of a partition root,
 * cpumask changes that violates the cpu exclusivity rule will not be
 * permitted when checked by validate_change(). The validate_change()
 * function will also prevent any changes to the cpu list अगर it is not
 * a superset of children's cpu lists.
 */
अटल पूर्णांक update_parent_subparts_cpumask(काष्ठा cpuset *cpuset, पूर्णांक cmd,
					  काष्ठा cpumask *newmask,
					  काष्ठा पंचांगpmasks *पंचांगp)
अणु
	काष्ठा cpuset *parent = parent_cs(cpuset);
	पूर्णांक adding;	/* Moving cpus from effective_cpus to subparts_cpus */
	पूर्णांक deleting;	/* Moving cpus from subparts_cpus to effective_cpus */
	bool part_error = false;	/* Partition error? */

	percpu_rwsem_निश्चित_held(&cpuset_rwsem);

	/*
	 * The parent must be a partition root.
	 * The new cpumask, अगर present, or the current cpus_allowed must
	 * not be empty.
	 */
	अगर (!is_partition_root(parent) ||
	   (newmask && cpumask_empty(newmask)) ||
	   (!newmask && cpumask_empty(cpuset->cpus_allowed)))
		वापस -EINVAL;

	/*
	 * Enabling/disabling partition root is not allowed अगर there are
	 * online children.
	 */
	अगर ((cmd != partcmd_update) && css_has_online_children(&cpuset->css))
		वापस -EBUSY;

	/*
	 * Enabling partition root is not allowed अगर not all the CPUs
	 * can be granted from parent's effective_cpus or at least one
	 * CPU will be left after that.
	 */
	अगर ((cmd == partcmd_enable) &&
	   (!cpumask_subset(cpuset->cpus_allowed, parent->effective_cpus) ||
	     cpumask_equal(cpuset->cpus_allowed, parent->effective_cpus)))
		वापस -EINVAL;

	/*
	 * A cpumask update cannot make parent's effective_cpus become empty.
	 */
	adding = deleting = false;
	अगर (cmd == partcmd_enable) अणु
		cpumask_copy(पंचांगp->addmask, cpuset->cpus_allowed);
		adding = true;
	पूर्ण अन्यथा अगर (cmd == partcmd_disable) अणु
		deleting = cpumask_and(पंचांगp->delmask, cpuset->cpus_allowed,
				       parent->subparts_cpus);
	पूर्ण अन्यथा अगर (newmask) अणु
		/*
		 * partcmd_update with newmask:
		 *
		 * delmask = cpus_allowed & ~newmask & parent->subparts_cpus
		 * addmask = newmask & parent->effective_cpus
		 *		     & ~parent->subparts_cpus
		 */
		cpumask_andnot(पंचांगp->delmask, cpuset->cpus_allowed, newmask);
		deleting = cpumask_and(पंचांगp->delmask, पंचांगp->delmask,
				       parent->subparts_cpus);

		cpumask_and(पंचांगp->addmask, newmask, parent->effective_cpus);
		adding = cpumask_andnot(पंचांगp->addmask, पंचांगp->addmask,
					parent->subparts_cpus);
		/*
		 * Return error अगर the new effective_cpus could become empty.
		 */
		अगर (adding &&
		    cpumask_equal(parent->effective_cpus, पंचांगp->addmask)) अणु
			अगर (!deleting)
				वापस -EINVAL;
			/*
			 * As some of the CPUs in subparts_cpus might have
			 * been offlined, we need to compute the real delmask
			 * to confirm that.
			 */
			अगर (!cpumask_and(पंचांगp->addmask, पंचांगp->delmask,
					 cpu_active_mask))
				वापस -EINVAL;
			cpumask_copy(पंचांगp->addmask, parent->effective_cpus);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * partcmd_update w/o newmask:
		 *
		 * addmask = cpus_allowed & parent->effectiveb_cpus
		 *
		 * Note that parent's subparts_cpus may have been
		 * pre-shrunk in हाल there is a change in the cpu list.
		 * So no deletion is needed.
		 */
		adding = cpumask_and(पंचांगp->addmask, cpuset->cpus_allowed,
				     parent->effective_cpus);
		part_error = cpumask_equal(पंचांगp->addmask,
					   parent->effective_cpus);
	पूर्ण

	अगर (cmd == partcmd_update) अणु
		पूर्णांक prev_prs = cpuset->partition_root_state;

		/*
		 * Check क्रम possible transition between PRS_ENABLED
		 * and PRS_ERROR.
		 */
		चयन (cpuset->partition_root_state) अणु
		हाल PRS_ENABLED:
			अगर (part_error)
				cpuset->partition_root_state = PRS_ERROR;
			अवरोध;
		हाल PRS_ERROR:
			अगर (!part_error)
				cpuset->partition_root_state = PRS_ENABLED;
			अवरोध;
		पूर्ण
		/*
		 * Set part_error अगर previously in invalid state.
		 */
		part_error = (prev_prs == PRS_ERROR);
	पूर्ण

	अगर (!part_error && (cpuset->partition_root_state == PRS_ERROR))
		वापस 0;	/* Nothing need to be करोne */

	अगर (cpuset->partition_root_state == PRS_ERROR) अणु
		/*
		 * Remove all its cpus from parent's subparts_cpus.
		 */
		adding = false;
		deleting = cpumask_and(पंचांगp->delmask, cpuset->cpus_allowed,
				       parent->subparts_cpus);
	पूर्ण

	अगर (!adding && !deleting)
		वापस 0;

	/*
	 * Change the parent's subparts_cpus.
	 * Newly added CPUs will be हटाओd from effective_cpus and
	 * newly deleted ones will be added back to effective_cpus.
	 */
	spin_lock_irq(&callback_lock);
	अगर (adding) अणु
		cpumask_or(parent->subparts_cpus,
			   parent->subparts_cpus, पंचांगp->addmask);
		cpumask_andnot(parent->effective_cpus,
			       parent->effective_cpus, पंचांगp->addmask);
	पूर्ण
	अगर (deleting) अणु
		cpumask_andnot(parent->subparts_cpus,
			       parent->subparts_cpus, पंचांगp->delmask);
		/*
		 * Some of the CPUs in subparts_cpus might have been offlined.
		 */
		cpumask_and(पंचांगp->delmask, पंचांगp->delmask, cpu_active_mask);
		cpumask_or(parent->effective_cpus,
			   parent->effective_cpus, पंचांगp->delmask);
	पूर्ण

	parent->nr_subparts_cpus = cpumask_weight(parent->subparts_cpus);
	spin_unlock_irq(&callback_lock);

	वापस cmd == partcmd_update;
पूर्ण

/*
 * update_cpumasks_hier - Update effective cpumasks and tasks in the subtree
 * @cs:  the cpuset to consider
 * @पंचांगp: temp variables क्रम calculating effective_cpus & partition setup
 *
 * When configured cpumask is changed, the effective cpumasks of this cpuset
 * and all its descendants need to be updated.
 *
 * On legacy hierarchy, effective_cpus will be the same with cpu_allowed.
 *
 * Called with cpuset_mutex held
 */
अटल व्योम update_cpumasks_hier(काष्ठा cpuset *cs, काष्ठा पंचांगpmasks *पंचांगp)
अणु
	काष्ठा cpuset *cp;
	काष्ठा cgroup_subsys_state *pos_css;
	bool need_rebuild_sched_करोमुख्यs = false;

	rcu_पढ़ो_lock();
	cpuset_क्रम_each_descendant_pre(cp, pos_css, cs) अणु
		काष्ठा cpuset *parent = parent_cs(cp);

		compute_effective_cpumask(पंचांगp->new_cpus, cp, parent);

		/*
		 * If it becomes empty, inherit the effective mask of the
		 * parent, which is guaranteed to have some CPUs.
		 */
		अगर (is_in_v2_mode() && cpumask_empty(पंचांगp->new_cpus)) अणु
			cpumask_copy(पंचांगp->new_cpus, parent->effective_cpus);
			अगर (!cp->use_parent_ecpus) अणु
				cp->use_parent_ecpus = true;
				parent->child_ecpus_count++;
			पूर्ण
		पूर्ण अन्यथा अगर (cp->use_parent_ecpus) अणु
			cp->use_parent_ecpus = false;
			WARN_ON_ONCE(!parent->child_ecpus_count);
			parent->child_ecpus_count--;
		पूर्ण

		/*
		 * Skip the whole subtree अगर the cpumask reमुख्यs the same
		 * and has no partition root state.
		 */
		अगर (!cp->partition_root_state &&
		    cpumask_equal(पंचांगp->new_cpus, cp->effective_cpus)) अणु
			pos_css = css_righपंचांगost_descendant(pos_css);
			जारी;
		पूर्ण

		/*
		 * update_parent_subparts_cpumask() should have been called
		 * क्रम cs alपढ़ोy in update_cpumask(). We should also call
		 * update_tasks_cpumask() again क्रम tasks in the parent
		 * cpuset अगर the parent's subparts_cpus changes.
		 */
		अगर ((cp != cs) && cp->partition_root_state) अणु
			चयन (parent->partition_root_state) अणु
			हाल PRS_DISABLED:
				/*
				 * If parent is not a partition root or an
				 * invalid partition root, clear the state
				 * state and the CS_CPU_EXCLUSIVE flag.
				 */
				WARN_ON_ONCE(cp->partition_root_state
					     != PRS_ERROR);
				cp->partition_root_state = 0;

				/*
				 * clear_bit() is an atomic operation and
				 * पढ़ोers aren't पूर्णांकerested in the state
				 * of CS_CPU_EXCLUSIVE anyway. So we can
				 * just update the flag without holding
				 * the callback_lock.
				 */
				clear_bit(CS_CPU_EXCLUSIVE, &cp->flags);
				अवरोध;

			हाल PRS_ENABLED:
				अगर (update_parent_subparts_cpumask(cp, partcmd_update, शून्य, पंचांगp))
					update_tasks_cpumask(parent);
				अवरोध;

			हाल PRS_ERROR:
				/*
				 * When parent is invalid, it has to be too.
				 */
				cp->partition_root_state = PRS_ERROR;
				अगर (cp->nr_subparts_cpus) अणु
					cp->nr_subparts_cpus = 0;
					cpumask_clear(cp->subparts_cpus);
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!css_tryget_online(&cp->css))
			जारी;
		rcu_पढ़ो_unlock();

		spin_lock_irq(&callback_lock);

		cpumask_copy(cp->effective_cpus, पंचांगp->new_cpus);
		अगर (cp->nr_subparts_cpus &&
		   (cp->partition_root_state != PRS_ENABLED)) अणु
			cp->nr_subparts_cpus = 0;
			cpumask_clear(cp->subparts_cpus);
		पूर्ण अन्यथा अगर (cp->nr_subparts_cpus) अणु
			/*
			 * Make sure that effective_cpus & subparts_cpus
			 * are mutually exclusive.
			 *
			 * In the unlikely event that effective_cpus
			 * becomes empty. we clear cp->nr_subparts_cpus and
			 * let its child partition roots to compete क्रम
			 * CPUs again.
			 */
			cpumask_andnot(cp->effective_cpus, cp->effective_cpus,
				       cp->subparts_cpus);
			अगर (cpumask_empty(cp->effective_cpus)) अणु
				cpumask_copy(cp->effective_cpus, पंचांगp->new_cpus);
				cpumask_clear(cp->subparts_cpus);
				cp->nr_subparts_cpus = 0;
			पूर्ण अन्यथा अगर (!cpumask_subset(cp->subparts_cpus,
						   पंचांगp->new_cpus)) अणु
				cpumask_andnot(cp->subparts_cpus,
					cp->subparts_cpus, पंचांगp->new_cpus);
				cp->nr_subparts_cpus
					= cpumask_weight(cp->subparts_cpus);
			पूर्ण
		पूर्ण
		spin_unlock_irq(&callback_lock);

		WARN_ON(!is_in_v2_mode() &&
			!cpumask_equal(cp->cpus_allowed, cp->effective_cpus));

		update_tasks_cpumask(cp);

		/*
		 * On legacy hierarchy, अगर the effective cpumask of any non-
		 * empty cpuset is changed, we need to rebuild sched करोमुख्यs.
		 * On शेष hierarchy, the cpuset needs to be a partition
		 * root as well.
		 */
		अगर (!cpumask_empty(cp->cpus_allowed) &&
		    is_sched_load_balance(cp) &&
		   (!cgroup_subsys_on_dfl(cpuset_cgrp_subsys) ||
		    is_partition_root(cp)))
			need_rebuild_sched_करोमुख्यs = true;

		rcu_पढ़ो_lock();
		css_put(&cp->css);
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (need_rebuild_sched_करोमुख्यs)
		rebuild_sched_करोमुख्यs_locked();
पूर्ण

/**
 * update_sibling_cpumasks - Update siblings cpumasks
 * @parent:  Parent cpuset
 * @cs:      Current cpuset
 * @पंचांगp:     Temp variables
 */
अटल व्योम update_sibling_cpumasks(काष्ठा cpuset *parent, काष्ठा cpuset *cs,
				    काष्ठा पंचांगpmasks *पंचांगp)
अणु
	काष्ठा cpuset *sibling;
	काष्ठा cgroup_subsys_state *pos_css;

	/*
	 * Check all its siblings and call update_cpumasks_hier()
	 * अगर their use_parent_ecpus flag is set in order क्रम them
	 * to use the right effective_cpus value.
	 */
	rcu_पढ़ो_lock();
	cpuset_क्रम_each_child(sibling, pos_css, parent) अणु
		अगर (sibling == cs)
			जारी;
		अगर (!sibling->use_parent_ecpus)
			जारी;

		update_cpumasks_hier(sibling, पंचांगp);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * update_cpumask - update the cpus_allowed mask of a cpuset and all tasks in it
 * @cs: the cpuset to consider
 * @trialcs: trial cpuset
 * @buf: buffer of cpu numbers written to this cpuset
 */
अटल पूर्णांक update_cpumask(काष्ठा cpuset *cs, काष्ठा cpuset *trialcs,
			  स्थिर अक्षर *buf)
अणु
	पूर्णांक retval;
	काष्ठा पंचांगpmasks पंचांगp;

	/* top_cpuset.cpus_allowed tracks cpu_online_mask; it's पढ़ो-only */
	अगर (cs == &top_cpuset)
		वापस -EACCES;

	/*
	 * An empty cpus_allowed is ok only अगर the cpuset has no tasks.
	 * Since cpulist_parse() fails on an empty mask, we special हाल
	 * that parsing.  The validate_change() call ensures that cpusets
	 * with tasks have cpus.
	 */
	अगर (!*buf) अणु
		cpumask_clear(trialcs->cpus_allowed);
	पूर्ण अन्यथा अणु
		retval = cpulist_parse(buf, trialcs->cpus_allowed);
		अगर (retval < 0)
			वापस retval;

		अगर (!cpumask_subset(trialcs->cpus_allowed,
				    top_cpuset.cpus_allowed))
			वापस -EINVAL;
	पूर्ण

	/* Nothing to करो अगर the cpus didn't change */
	अगर (cpumask_equal(cs->cpus_allowed, trialcs->cpus_allowed))
		वापस 0;

	retval = validate_change(cs, trialcs);
	अगर (retval < 0)
		वापस retval;

#अगर_घोषित CONFIG_CPUMASK_OFFSTACK
	/*
	 * Use the cpumasks in trialcs क्रम पंचांगpmasks when they are poपूर्णांकers
	 * to allocated cpumasks.
	 */
	पंचांगp.addmask  = trialcs->subparts_cpus;
	पंचांगp.delmask  = trialcs->effective_cpus;
	पंचांगp.new_cpus = trialcs->cpus_allowed;
#पूर्ण_अगर

	अगर (cs->partition_root_state) अणु
		/* Cpumask of a partition root cannot be empty */
		अगर (cpumask_empty(trialcs->cpus_allowed))
			वापस -EINVAL;
		अगर (update_parent_subparts_cpumask(cs, partcmd_update,
					trialcs->cpus_allowed, &पंचांगp) < 0)
			वापस -EINVAL;
	पूर्ण

	spin_lock_irq(&callback_lock);
	cpumask_copy(cs->cpus_allowed, trialcs->cpus_allowed);

	/*
	 * Make sure that subparts_cpus is a subset of cpus_allowed.
	 */
	अगर (cs->nr_subparts_cpus) अणु
		cpumask_andnot(cs->subparts_cpus, cs->subparts_cpus,
			       cs->cpus_allowed);
		cs->nr_subparts_cpus = cpumask_weight(cs->subparts_cpus);
	पूर्ण
	spin_unlock_irq(&callback_lock);

	update_cpumasks_hier(cs, &पंचांगp);

	अगर (cs->partition_root_state) अणु
		काष्ठा cpuset *parent = parent_cs(cs);

		/*
		 * For partition root, update the cpumasks of sibling
		 * cpusets अगर they use parent's effective_cpus.
		 */
		अगर (parent->child_ecpus_count)
			update_sibling_cpumasks(parent, cs, &पंचांगp);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Migrate memory region from one set of nodes to another.  This is
 * perक्रमmed asynchronously as it can be called from process migration path
 * holding locks involved in process management.  All mm migrations are
 * perक्रमmed in the queued order and can be रुकोed क्रम by flushing
 * cpuset_migrate_mm_wq.
 */

काष्ठा cpuset_migrate_mm_work अणु
	काष्ठा work_काष्ठा	work;
	काष्ठा mm_काष्ठा	*mm;
	nodemask_t		from;
	nodemask_t		to;
पूर्ण;

अटल व्योम cpuset_migrate_mm_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cpuset_migrate_mm_work *mwork =
		container_of(work, काष्ठा cpuset_migrate_mm_work, work);

	/* on a wq worker, no need to worry about %current's mems_allowed */
	करो_migrate_pages(mwork->mm, &mwork->from, &mwork->to, MPOL_MF_MOVE_ALL);
	mmput(mwork->mm);
	kमुक्त(mwork);
पूर्ण

अटल व्योम cpuset_migrate_mm(काष्ठा mm_काष्ठा *mm, स्थिर nodemask_t *from,
							स्थिर nodemask_t *to)
अणु
	काष्ठा cpuset_migrate_mm_work *mwork;

	mwork = kzalloc(माप(*mwork), GFP_KERNEL);
	अगर (mwork) अणु
		mwork->mm = mm;
		mwork->from = *from;
		mwork->to = *to;
		INIT_WORK(&mwork->work, cpuset_migrate_mm_workfn);
		queue_work(cpuset_migrate_mm_wq, &mwork->work);
	पूर्ण अन्यथा अणु
		mmput(mm);
	पूर्ण
पूर्ण

अटल व्योम cpuset_post_attach(व्योम)
अणु
	flush_workqueue(cpuset_migrate_mm_wq);
पूर्ण

/*
 * cpuset_change_task_nodemask - change task's mems_allowed and mempolicy
 * @tsk: the task to change
 * @newmems: new nodes that the task will be set
 *
 * We use the mems_allowed_seq seqlock to safely update both tsk->mems_allowed
 * and rebind an eventual tasks' mempolicy. If the task is allocating in
 * parallel, it might temporarily see an empty पूर्णांकersection, which results in
 * a seqlock check and retry beक्रमe OOM or allocation failure.
 */
अटल व्योम cpuset_change_task_nodemask(काष्ठा task_काष्ठा *tsk,
					nodemask_t *newmems)
अणु
	task_lock(tsk);

	local_irq_disable();
	ग_लिखो_seqcount_begin(&tsk->mems_allowed_seq);

	nodes_or(tsk->mems_allowed, tsk->mems_allowed, *newmems);
	mpol_rebind_task(tsk, newmems);
	tsk->mems_allowed = *newmems;

	ग_लिखो_seqcount_end(&tsk->mems_allowed_seq);
	local_irq_enable();

	task_unlock(tsk);
पूर्ण

अटल व्योम *cpuset_being_rebound;

/**
 * update_tasks_nodemask - Update the nodemasks of tasks in the cpuset.
 * @cs: the cpuset in which each task's mems_allowed mask needs to be changed
 *
 * Iterate through each task of @cs updating its mems_allowed to the
 * effective cpuset's.  As this function is called with cpuset_mutex held,
 * cpuset membership stays stable.
 */
अटल व्योम update_tasks_nodemask(काष्ठा cpuset *cs)
अणु
	अटल nodemask_t newmems;	/* रक्षित by cpuset_mutex */
	काष्ठा css_task_iter it;
	काष्ठा task_काष्ठा *task;

	cpuset_being_rebound = cs;		/* causes mpol_dup() rebind */

	guarantee_online_mems(cs, &newmems);

	/*
	 * The mpol_rebind_mm() call takes mmap_lock, which we couldn't
	 * take जबतक holding tasklist_lock.  Forks can happen - the
	 * mpol_dup() cpuset_being_rebound check will catch such विभाजनs,
	 * and rebind their vma mempolicies too.  Because we still hold
	 * the global cpuset_mutex, we know that no other rebind efक्रमt
	 * will be contending क्रम the global variable cpuset_being_rebound.
	 * It's ok अगर we rebind the same mm twice; mpol_rebind_mm()
	 * is idempotent.  Also migrate pages in each mm to new nodes.
	 */
	css_task_iter_start(&cs->css, 0, &it);
	जबतक ((task = css_task_iter_next(&it))) अणु
		काष्ठा mm_काष्ठा *mm;
		bool migrate;

		cpuset_change_task_nodemask(task, &newmems);

		mm = get_task_mm(task);
		अगर (!mm)
			जारी;

		migrate = is_memory_migrate(cs);

		mpol_rebind_mm(mm, &cs->mems_allowed);
		अगर (migrate)
			cpuset_migrate_mm(mm, &cs->old_mems_allowed, &newmems);
		अन्यथा
			mmput(mm);
	पूर्ण
	css_task_iter_end(&it);

	/*
	 * All the tasks' nodemasks have been updated, update
	 * cs->old_mems_allowed.
	 */
	cs->old_mems_allowed = newmems;

	/* We're done rebinding vmas to this cpuset's new mems_allowed. */
	cpuset_being_rebound = शून्य;
पूर्ण

/*
 * update_nodemasks_hier - Update effective nodemasks and tasks in the subtree
 * @cs: the cpuset to consider
 * @new_mems: a temp variable क्रम calculating new effective_mems
 *
 * When configured nodemask is changed, the effective nodemasks of this cpuset
 * and all its descendants need to be updated.
 *
 * On legacy hierarchy, effective_mems will be the same with mems_allowed.
 *
 * Called with cpuset_mutex held
 */
अटल व्योम update_nodemasks_hier(काष्ठा cpuset *cs, nodemask_t *new_mems)
अणु
	काष्ठा cpuset *cp;
	काष्ठा cgroup_subsys_state *pos_css;

	rcu_पढ़ो_lock();
	cpuset_क्रम_each_descendant_pre(cp, pos_css, cs) अणु
		काष्ठा cpuset *parent = parent_cs(cp);

		nodes_and(*new_mems, cp->mems_allowed, parent->effective_mems);

		/*
		 * If it becomes empty, inherit the effective mask of the
		 * parent, which is guaranteed to have some MEMs.
		 */
		अगर (is_in_v2_mode() && nodes_empty(*new_mems))
			*new_mems = parent->effective_mems;

		/* Skip the whole subtree अगर the nodemask reमुख्यs the same. */
		अगर (nodes_equal(*new_mems, cp->effective_mems)) अणु
			pos_css = css_righपंचांगost_descendant(pos_css);
			जारी;
		पूर्ण

		अगर (!css_tryget_online(&cp->css))
			जारी;
		rcu_पढ़ो_unlock();

		spin_lock_irq(&callback_lock);
		cp->effective_mems = *new_mems;
		spin_unlock_irq(&callback_lock);

		WARN_ON(!is_in_v2_mode() &&
			!nodes_equal(cp->mems_allowed, cp->effective_mems));

		update_tasks_nodemask(cp);

		rcu_पढ़ो_lock();
		css_put(&cp->css);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Handle user request to change the 'mems' memory placement
 * of a cpuset.  Needs to validate the request, update the
 * cpusets mems_allowed, and क्रम each task in the cpuset,
 * update mems_allowed and rebind task's mempolicy and any vma
 * mempolicies and अगर the cpuset is marked 'memory_migrate',
 * migrate the tasks pages to the new memory.
 *
 * Call with cpuset_mutex held. May take callback_lock during call.
 * Will take tasklist_lock, scan tasklist क्रम tasks in cpuset cs,
 * lock each such tasks mm->mmap_lock, scan its vma's and rebind
 * their mempolicies to the cpusets new mems_allowed.
 */
अटल पूर्णांक update_nodemask(काष्ठा cpuset *cs, काष्ठा cpuset *trialcs,
			   स्थिर अक्षर *buf)
अणु
	पूर्णांक retval;

	/*
	 * top_cpuset.mems_allowed tracks node_stats[N_MEMORY];
	 * it's पढ़ो-only
	 */
	अगर (cs == &top_cpuset) अणु
		retval = -EACCES;
		जाओ करोne;
	पूर्ण

	/*
	 * An empty mems_allowed is ok अगरf there are no tasks in the cpuset.
	 * Since nodelist_parse() fails on an empty mask, we special हाल
	 * that parsing.  The validate_change() call ensures that cpusets
	 * with tasks have memory.
	 */
	अगर (!*buf) अणु
		nodes_clear(trialcs->mems_allowed);
	पूर्ण अन्यथा अणु
		retval = nodelist_parse(buf, trialcs->mems_allowed);
		अगर (retval < 0)
			जाओ करोne;

		अगर (!nodes_subset(trialcs->mems_allowed,
				  top_cpuset.mems_allowed)) अणु
			retval = -EINVAL;
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (nodes_equal(cs->mems_allowed, trialcs->mems_allowed)) अणु
		retval = 0;		/* Too easy - nothing to करो */
		जाओ करोne;
	पूर्ण
	retval = validate_change(cs, trialcs);
	अगर (retval < 0)
		जाओ करोne;

	spin_lock_irq(&callback_lock);
	cs->mems_allowed = trialcs->mems_allowed;
	spin_unlock_irq(&callback_lock);

	/* use trialcs->mems_allowed as a temp variable */
	update_nodemasks_hier(cs, &trialcs->mems_allowed);
करोne:
	वापस retval;
पूर्ण

bool current_cpuset_is_being_rebound(व्योम)
अणु
	bool ret;

	rcu_पढ़ो_lock();
	ret = task_cs(current) == cpuset_being_rebound;
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल पूर्णांक update_relax_करोमुख्य_level(काष्ठा cpuset *cs, s64 val)
अणु
#अगर_घोषित CONFIG_SMP
	अगर (val < -1 || val >= sched_करोमुख्य_level_max)
		वापस -EINVAL;
#पूर्ण_अगर

	अगर (val != cs->relax_करोमुख्य_level) अणु
		cs->relax_करोमुख्य_level = val;
		अगर (!cpumask_empty(cs->cpus_allowed) &&
		    is_sched_load_balance(cs))
			rebuild_sched_करोमुख्यs_locked();
	पूर्ण

	वापस 0;
पूर्ण

/**
 * update_tasks_flags - update the spपढ़ो flags of tasks in the cpuset.
 * @cs: the cpuset in which each task's spपढ़ो flags needs to be changed
 *
 * Iterate through each task of @cs updating its spपढ़ो flags.  As this
 * function is called with cpuset_mutex held, cpuset membership stays
 * stable.
 */
अटल व्योम update_tasks_flags(काष्ठा cpuset *cs)
अणु
	काष्ठा css_task_iter it;
	काष्ठा task_काष्ठा *task;

	css_task_iter_start(&cs->css, 0, &it);
	जबतक ((task = css_task_iter_next(&it)))
		cpuset_update_task_spपढ़ो_flag(cs, task);
	css_task_iter_end(&it);
पूर्ण

/*
 * update_flag - पढ़ो a 0 or a 1 in a file and update associated flag
 * bit:		the bit to update (see cpuset_flagbits_t)
 * cs:		the cpuset to update
 * turning_on: 	whether the flag is being set or cleared
 *
 * Call with cpuset_mutex held.
 */

अटल पूर्णांक update_flag(cpuset_flagbits_t bit, काष्ठा cpuset *cs,
		       पूर्णांक turning_on)
अणु
	काष्ठा cpuset *trialcs;
	पूर्णांक balance_flag_changed;
	पूर्णांक spपढ़ो_flag_changed;
	पूर्णांक err;

	trialcs = alloc_trial_cpuset(cs);
	अगर (!trialcs)
		वापस -ENOMEM;

	अगर (turning_on)
		set_bit(bit, &trialcs->flags);
	अन्यथा
		clear_bit(bit, &trialcs->flags);

	err = validate_change(cs, trialcs);
	अगर (err < 0)
		जाओ out;

	balance_flag_changed = (is_sched_load_balance(cs) !=
				is_sched_load_balance(trialcs));

	spपढ़ो_flag_changed = ((is_spपढ़ो_slab(cs) != is_spपढ़ो_slab(trialcs))
			|| (is_spपढ़ो_page(cs) != is_spपढ़ो_page(trialcs)));

	spin_lock_irq(&callback_lock);
	cs->flags = trialcs->flags;
	spin_unlock_irq(&callback_lock);

	अगर (!cpumask_empty(trialcs->cpus_allowed) && balance_flag_changed)
		rebuild_sched_करोमुख्यs_locked();

	अगर (spपढ़ो_flag_changed)
		update_tasks_flags(cs);
out:
	मुक्त_cpuset(trialcs);
	वापस err;
पूर्ण

/*
 * update_prstate - update partititon_root_state
 * cs:	the cpuset to update
 * val: 0 - disabled, 1 - enabled
 *
 * Call with cpuset_mutex held.
 */
अटल पूर्णांक update_prstate(काष्ठा cpuset *cs, पूर्णांक val)
अणु
	पूर्णांक err;
	काष्ठा cpuset *parent = parent_cs(cs);
	काष्ठा पंचांगpmasks पंचांगp;

	अगर ((val != 0) && (val != 1))
		वापस -EINVAL;
	अगर (val == cs->partition_root_state)
		वापस 0;

	/*
	 * Cannot क्रमce a partial or invalid partition root to a full
	 * partition root.
	 */
	अगर (val && cs->partition_root_state)
		वापस -EINVAL;

	अगर (alloc_cpumasks(शून्य, &पंचांगp))
		वापस -ENOMEM;

	err = -EINVAL;
	अगर (!cs->partition_root_state) अणु
		/*
		 * Turning on partition root requires setting the
		 * CS_CPU_EXCLUSIVE bit implicitly as well and cpus_allowed
		 * cannot be शून्य.
		 */
		अगर (cpumask_empty(cs->cpus_allowed))
			जाओ out;

		err = update_flag(CS_CPU_EXCLUSIVE, cs, 1);
		अगर (err)
			जाओ out;

		err = update_parent_subparts_cpumask(cs, partcmd_enable,
						     शून्य, &पंचांगp);
		अगर (err) अणु
			update_flag(CS_CPU_EXCLUSIVE, cs, 0);
			जाओ out;
		पूर्ण
		cs->partition_root_state = PRS_ENABLED;
	पूर्ण अन्यथा अणु
		/*
		 * Turning off partition root will clear the
		 * CS_CPU_EXCLUSIVE bit.
		 */
		अगर (cs->partition_root_state == PRS_ERROR) अणु
			cs->partition_root_state = 0;
			update_flag(CS_CPU_EXCLUSIVE, cs, 0);
			err = 0;
			जाओ out;
		पूर्ण

		err = update_parent_subparts_cpumask(cs, partcmd_disable,
						     शून्य, &पंचांगp);
		अगर (err)
			जाओ out;

		cs->partition_root_state = 0;

		/* Turning off CS_CPU_EXCLUSIVE will not वापस error */
		update_flag(CS_CPU_EXCLUSIVE, cs, 0);
	पूर्ण

	/*
	 * Update cpumask of parent's tasks except when it is the top
	 * cpuset as some प्रणाली daemons cannot be mapped to other CPUs.
	 */
	अगर (parent != &top_cpuset)
		update_tasks_cpumask(parent);

	अगर (parent->child_ecpus_count)
		update_sibling_cpumasks(parent, cs, &पंचांगp);

	rebuild_sched_करोमुख्यs_locked();
out:
	मुक्त_cpumasks(शून्य, &पंचांगp);
	वापस err;
पूर्ण

/*
 * Frequency meter - How fast is some event occurring?
 *
 * These routines manage a digitally filtered, स्थिरant समय based,
 * event frequency meter.  There are four routines:
 *   fmeter_init() - initialize a frequency meter.
 *   fmeter_markevent() - called each समय the event happens.
 *   fmeter_getrate() - वापसs the recent rate of such events.
 *   fmeter_update() - पूर्णांकernal routine used to update fmeter.
 *
 * A common data काष्ठाure is passed to each of these routines,
 * which is used to keep track of the state required to manage the
 * frequency meter and its digital filter.
 *
 * The filter works on the number of events marked per unit समय.
 * The filter is single-pole low-pass recursive (IIR).  The समय unit
 * is 1 second.  Arithmetic is करोne using 32-bit पूर्णांकegers scaled to
 * simulate 3 decimal digits of precision (multiplied by 1000).
 *
 * With an FM_COEF of 933, and a समय base of 1 second, the filter
 * has a half-lअगरe of 10 seconds, meaning that अगर the events quit
 * happening, then the rate वापसed from the fmeter_getrate()
 * will be cut in half each 10 seconds, until it converges to zero.
 *
 * It is not worth करोing a real infinitely recursive filter.  If more
 * than FM_MAXTICKS ticks have elapsed since the last filter event,
 * just compute FM_MAXTICKS ticks worth, by which poपूर्णांक the level
 * will be stable.
 *
 * Limit the count of unprocessed events to FM_MAXCNT, so as to aव्योम
 * arithmetic overflow in the fmeter_update() routine.
 *
 * Given the simple 32 bit पूर्णांकeger arithmetic used, this meter works
 * best क्रम reporting rates between one per millisecond (msec) and
 * one per 32 (approx) seconds.  At स्थिरant rates faster than one
 * per msec it maxes out at values just under 1,000,000.  At स्थिरant
 * rates between one per msec, and one per second it will stabilize
 * to a value N*1000, where N is the rate of events per second.
 * At स्थिरant rates between one per second and one per 32 seconds,
 * it will be choppy, moving up on the seconds that have an event,
 * and then decaying until the next event.  At rates slower than
 * about one in 32 seconds, it decays all the way back to zero between
 * each event.
 */

#घोषणा FM_COEF 933		/* coefficient क्रम half-lअगरe of 10 secs */
#घोषणा FM_MAXTICKS ((u32)99)   /* useless computing more ticks than this */
#घोषणा FM_MAXCNT 1000000	/* limit cnt to aव्योम overflow */
#घोषणा FM_SCALE 1000		/* faux fixed poपूर्णांक scale */

/* Initialize a frequency meter */
अटल व्योम fmeter_init(काष्ठा fmeter *fmp)
अणु
	fmp->cnt = 0;
	fmp->val = 0;
	fmp->समय = 0;
	spin_lock_init(&fmp->lock);
पूर्ण

/* Internal meter update - process cnt events and update value */
अटल व्योम fmeter_update(काष्ठा fmeter *fmp)
अणु
	समय64_t now;
	u32 ticks;

	now = kसमय_get_seconds();
	ticks = now - fmp->समय;

	अगर (ticks == 0)
		वापस;

	ticks = min(FM_MAXTICKS, ticks);
	जबतक (ticks-- > 0)
		fmp->val = (FM_COEF * fmp->val) / FM_SCALE;
	fmp->समय = now;

	fmp->val += ((FM_SCALE - FM_COEF) * fmp->cnt) / FM_SCALE;
	fmp->cnt = 0;
पूर्ण

/* Process any previous ticks, then bump cnt by one (बार scale). */
अटल व्योम fmeter_markevent(काष्ठा fmeter *fmp)
अणु
	spin_lock(&fmp->lock);
	fmeter_update(fmp);
	fmp->cnt = min(FM_MAXCNT, fmp->cnt + FM_SCALE);
	spin_unlock(&fmp->lock);
पूर्ण

/* Process any previous ticks, then वापस current value. */
अटल पूर्णांक fmeter_getrate(काष्ठा fmeter *fmp)
अणु
	पूर्णांक val;

	spin_lock(&fmp->lock);
	fmeter_update(fmp);
	val = fmp->val;
	spin_unlock(&fmp->lock);
	वापस val;
पूर्ण

अटल काष्ठा cpuset *cpuset_attach_old_cs;

/* Called by cgroups to determine अगर a cpuset is usable; cpuset_mutex held */
अटल पूर्णांक cpuset_can_attach(काष्ठा cgroup_taskset *tset)
अणु
	काष्ठा cgroup_subsys_state *css;
	काष्ठा cpuset *cs;
	काष्ठा task_काष्ठा *task;
	पूर्णांक ret;

	/* used later by cpuset_attach() */
	cpuset_attach_old_cs = task_cs(cgroup_taskset_first(tset, &css));
	cs = css_cs(css);

	percpu_करोwn_ग_लिखो(&cpuset_rwsem);

	/* allow moving tasks पूर्णांकo an empty cpuset अगर on शेष hierarchy */
	ret = -ENOSPC;
	अगर (!is_in_v2_mode() &&
	    (cpumask_empty(cs->cpus_allowed) || nodes_empty(cs->mems_allowed)))
		जाओ out_unlock;

	cgroup_taskset_क्रम_each(task, css, tset) अणु
		ret = task_can_attach(task, cs->cpus_allowed);
		अगर (ret)
			जाओ out_unlock;
		ret = security_task_setscheduler(task);
		अगर (ret)
			जाओ out_unlock;
	पूर्ण

	/*
	 * Mark attach is in progress.  This makes validate_change() fail
	 * changes which zero cpus/mems_allowed.
	 */
	cs->attach_in_progress++;
	ret = 0;
out_unlock:
	percpu_up_ग_लिखो(&cpuset_rwsem);
	वापस ret;
पूर्ण

अटल व्योम cpuset_cancel_attach(काष्ठा cgroup_taskset *tset)
अणु
	काष्ठा cgroup_subsys_state *css;

	cgroup_taskset_first(tset, &css);

	percpu_करोwn_ग_लिखो(&cpuset_rwsem);
	css_cs(css)->attach_in_progress--;
	percpu_up_ग_लिखो(&cpuset_rwsem);
पूर्ण

/*
 * Protected by cpuset_mutex.  cpus_attach is used only by cpuset_attach()
 * but we can't allocate it dynamically there.  Define it global and
 * allocate from cpuset_init().
 */
अटल cpumask_var_t cpus_attach;

अटल व्योम cpuset_attach(काष्ठा cgroup_taskset *tset)
अणु
	/* अटल buf रक्षित by cpuset_mutex */
	अटल nodemask_t cpuset_attach_nodemask_to;
	काष्ठा task_काष्ठा *task;
	काष्ठा task_काष्ठा *leader;
	काष्ठा cgroup_subsys_state *css;
	काष्ठा cpuset *cs;
	काष्ठा cpuset *oldcs = cpuset_attach_old_cs;

	cgroup_taskset_first(tset, &css);
	cs = css_cs(css);

	percpu_करोwn_ग_लिखो(&cpuset_rwsem);

	/* prepare क्रम attach */
	अगर (cs == &top_cpuset)
		cpumask_copy(cpus_attach, cpu_possible_mask);
	अन्यथा
		guarantee_online_cpus(cs, cpus_attach);

	guarantee_online_mems(cs, &cpuset_attach_nodemask_to);

	cgroup_taskset_क्रम_each(task, css, tset) अणु
		/*
		 * can_attach beक्रमehand should guarantee that this करोesn't
		 * fail.  TODO: have a better way to handle failure here
		 */
		WARN_ON_ONCE(set_cpus_allowed_ptr(task, cpus_attach));

		cpuset_change_task_nodemask(task, &cpuset_attach_nodemask_to);
		cpuset_update_task_spपढ़ो_flag(cs, task);
	पूर्ण

	/*
	 * Change mm क्रम all thपढ़ोgroup leaders. This is expensive and may
	 * sleep and should be moved outside migration path proper.
	 */
	cpuset_attach_nodemask_to = cs->effective_mems;
	cgroup_taskset_क्रम_each_leader(leader, css, tset) अणु
		काष्ठा mm_काष्ठा *mm = get_task_mm(leader);

		अगर (mm) अणु
			mpol_rebind_mm(mm, &cpuset_attach_nodemask_to);

			/*
			 * old_mems_allowed is the same with mems_allowed
			 * here, except अगर this task is being moved
			 * स्वतःmatically due to hotplug.  In that हाल
			 * @mems_allowed has been updated and is empty, so
			 * @old_mems_allowed is the right nodesets that we
			 * migrate mm from.
			 */
			अगर (is_memory_migrate(cs))
				cpuset_migrate_mm(mm, &oldcs->old_mems_allowed,
						  &cpuset_attach_nodemask_to);
			अन्यथा
				mmput(mm);
		पूर्ण
	पूर्ण

	cs->old_mems_allowed = cpuset_attach_nodemask_to;

	cs->attach_in_progress--;
	अगर (!cs->attach_in_progress)
		wake_up(&cpuset_attach_wq);

	percpu_up_ग_लिखो(&cpuset_rwsem);
पूर्ण

/* The various types of files and directories in a cpuset file प्रणाली */

प्रकार क्रमागत अणु
	खाता_MEMORY_MIGRATE,
	खाता_CPULIST,
	खाता_MEMLIST,
	खाता_EFFECTIVE_CPULIST,
	खाता_EFFECTIVE_MEMLIST,
	खाता_SUBPARTS_CPULIST,
	खाता_CPU_EXCLUSIVE,
	खाता_MEM_EXCLUSIVE,
	खाता_MEM_HARDWALL,
	खाता_SCHED_LOAD_BALANCE,
	खाता_PARTITION_ROOT,
	खाता_SCHED_RELAX_DOMAIN_LEVEL,
	खाता_MEMORY_PRESSURE_ENABLED,
	खाता_MEMORY_PRESSURE,
	खाता_SPREAD_PAGE,
	खाता_SPREAD_SLAB,
पूर्ण cpuset_filetype_t;

अटल पूर्णांक cpuset_ग_लिखो_u64(काष्ठा cgroup_subsys_state *css, काष्ठा cftype *cft,
			    u64 val)
अणु
	काष्ठा cpuset *cs = css_cs(css);
	cpuset_filetype_t type = cft->निजी;
	पूर्णांक retval = 0;

	get_online_cpus();
	percpu_करोwn_ग_लिखो(&cpuset_rwsem);
	अगर (!is_cpuset_online(cs)) अणु
		retval = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	चयन (type) अणु
	हाल खाता_CPU_EXCLUSIVE:
		retval = update_flag(CS_CPU_EXCLUSIVE, cs, val);
		अवरोध;
	हाल खाता_MEM_EXCLUSIVE:
		retval = update_flag(CS_MEM_EXCLUSIVE, cs, val);
		अवरोध;
	हाल खाता_MEM_HARDWALL:
		retval = update_flag(CS_MEM_HARDWALL, cs, val);
		अवरोध;
	हाल खाता_SCHED_LOAD_BALANCE:
		retval = update_flag(CS_SCHED_LOAD_BALANCE, cs, val);
		अवरोध;
	हाल खाता_MEMORY_MIGRATE:
		retval = update_flag(CS_MEMORY_MIGRATE, cs, val);
		अवरोध;
	हाल खाता_MEMORY_PRESSURE_ENABLED:
		cpuset_memory_pressure_enabled = !!val;
		अवरोध;
	हाल खाता_SPREAD_PAGE:
		retval = update_flag(CS_SPREAD_PAGE, cs, val);
		अवरोध;
	हाल खाता_SPREAD_SLAB:
		retval = update_flag(CS_SPREAD_SLAB, cs, val);
		अवरोध;
	शेष:
		retval = -EINVAL;
		अवरोध;
	पूर्ण
out_unlock:
	percpu_up_ग_लिखो(&cpuset_rwsem);
	put_online_cpus();
	वापस retval;
पूर्ण

अटल पूर्णांक cpuset_ग_लिखो_s64(काष्ठा cgroup_subsys_state *css, काष्ठा cftype *cft,
			    s64 val)
अणु
	काष्ठा cpuset *cs = css_cs(css);
	cpuset_filetype_t type = cft->निजी;
	पूर्णांक retval = -ENODEV;

	get_online_cpus();
	percpu_करोwn_ग_लिखो(&cpuset_rwsem);
	अगर (!is_cpuset_online(cs))
		जाओ out_unlock;

	चयन (type) अणु
	हाल खाता_SCHED_RELAX_DOMAIN_LEVEL:
		retval = update_relax_करोमुख्य_level(cs, val);
		अवरोध;
	शेष:
		retval = -EINVAL;
		अवरोध;
	पूर्ण
out_unlock:
	percpu_up_ग_लिखो(&cpuset_rwsem);
	put_online_cpus();
	वापस retval;
पूर्ण

/*
 * Common handling क्रम a ग_लिखो to a "cpus" or "mems" file.
 */
अटल sमाप_प्रकार cpuset_ग_लिखो_resmask(काष्ठा kernfs_खोलो_file *of,
				    अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा cpuset *cs = css_cs(of_css(of));
	काष्ठा cpuset *trialcs;
	पूर्णांक retval = -ENODEV;

	buf = म_मालाip(buf);

	/*
	 * CPU or memory hotunplug may leave @cs w/o any execution
	 * resources, in which हाल the hotplug code asynchronously updates
	 * configuration and transfers all tasks to the nearest ancestor
	 * which can execute.
	 *
	 * As ग_लिखोs to "cpus" or "mems" may restore @cs's execution
	 * resources, रुको क्रम the previously scheduled operations beक्रमe
	 * proceeding, so that we करोn't end up keep removing tasks added
	 * after execution capability is restored.
	 *
	 * cpuset_hotplug_work calls back पूर्णांकo cgroup core via
	 * cgroup_transfer_tasks() and रुकोing क्रम it from a cgroupfs
	 * operation like this one can lead to a deadlock through kernfs
	 * active_ref protection.  Let's अवरोध the protection.  Losing the
	 * protection is okay as we check whether @cs is online after
	 * grabbing cpuset_mutex anyway.  This only happens on the legacy
	 * hierarchies.
	 */
	css_get(&cs->css);
	kernfs_अवरोध_active_protection(of->kn);
	flush_work(&cpuset_hotplug_work);

	get_online_cpus();
	percpu_करोwn_ग_लिखो(&cpuset_rwsem);
	अगर (!is_cpuset_online(cs))
		जाओ out_unlock;

	trialcs = alloc_trial_cpuset(cs);
	अगर (!trialcs) अणु
		retval = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	चयन (of_cft(of)->निजी) अणु
	हाल खाता_CPULIST:
		retval = update_cpumask(cs, trialcs, buf);
		अवरोध;
	हाल खाता_MEMLIST:
		retval = update_nodemask(cs, trialcs, buf);
		अवरोध;
	शेष:
		retval = -EINVAL;
		अवरोध;
	पूर्ण

	मुक्त_cpuset(trialcs);
out_unlock:
	percpu_up_ग_लिखो(&cpuset_rwsem);
	put_online_cpus();
	kernfs_unअवरोध_active_protection(of->kn);
	css_put(&cs->css);
	flush_workqueue(cpuset_migrate_mm_wq);
	वापस retval ?: nbytes;
पूर्ण

/*
 * These ascii lists should be पढ़ो in a single call, by using a user
 * buffer large enough to hold the entire map.  If पढ़ो in smaller
 * chunks, there is no guarantee of atomicity.  Since the display क्रमmat
 * used, list of ranges of sequential numbers, is variable length,
 * and since these maps can change value dynamically, one could पढ़ो
 * gibberish by करोing partial पढ़ोs जबतक a list was changing.
 */
अटल पूर्णांक cpuset_common_seq_show(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा cpuset *cs = css_cs(seq_css(sf));
	cpuset_filetype_t type = seq_cft(sf)->निजी;
	पूर्णांक ret = 0;

	spin_lock_irq(&callback_lock);

	चयन (type) अणु
	हाल खाता_CPULIST:
		seq_म_लिखो(sf, "%*pbl\n", cpumask_pr_args(cs->cpus_allowed));
		अवरोध;
	हाल खाता_MEMLIST:
		seq_म_लिखो(sf, "%*pbl\n", nodemask_pr_args(&cs->mems_allowed));
		अवरोध;
	हाल खाता_EFFECTIVE_CPULIST:
		seq_म_लिखो(sf, "%*pbl\n", cpumask_pr_args(cs->effective_cpus));
		अवरोध;
	हाल खाता_EFFECTIVE_MEMLIST:
		seq_म_लिखो(sf, "%*pbl\n", nodemask_pr_args(&cs->effective_mems));
		अवरोध;
	हाल खाता_SUBPARTS_CPULIST:
		seq_म_लिखो(sf, "%*pbl\n", cpumask_pr_args(cs->subparts_cpus));
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	spin_unlock_irq(&callback_lock);
	वापस ret;
पूर्ण

अटल u64 cpuset_पढ़ो_u64(काष्ठा cgroup_subsys_state *css, काष्ठा cftype *cft)
अणु
	काष्ठा cpuset *cs = css_cs(css);
	cpuset_filetype_t type = cft->निजी;
	चयन (type) अणु
	हाल खाता_CPU_EXCLUSIVE:
		वापस is_cpu_exclusive(cs);
	हाल खाता_MEM_EXCLUSIVE:
		वापस is_mem_exclusive(cs);
	हाल खाता_MEM_HARDWALL:
		वापस is_mem_hardwall(cs);
	हाल खाता_SCHED_LOAD_BALANCE:
		वापस is_sched_load_balance(cs);
	हाल खाता_MEMORY_MIGRATE:
		वापस is_memory_migrate(cs);
	हाल खाता_MEMORY_PRESSURE_ENABLED:
		वापस cpuset_memory_pressure_enabled;
	हाल खाता_MEMORY_PRESSURE:
		वापस fmeter_getrate(&cs->fmeter);
	हाल खाता_SPREAD_PAGE:
		वापस is_spपढ़ो_page(cs);
	हाल खाता_SPREAD_SLAB:
		वापस is_spपढ़ो_slab(cs);
	शेष:
		BUG();
	पूर्ण

	/* Unreachable but makes gcc happy */
	वापस 0;
पूर्ण

अटल s64 cpuset_पढ़ो_s64(काष्ठा cgroup_subsys_state *css, काष्ठा cftype *cft)
अणु
	काष्ठा cpuset *cs = css_cs(css);
	cpuset_filetype_t type = cft->निजी;
	चयन (type) अणु
	हाल खाता_SCHED_RELAX_DOMAIN_LEVEL:
		वापस cs->relax_करोमुख्य_level;
	शेष:
		BUG();
	पूर्ण

	/* Unreachable but makes gcc happy */
	वापस 0;
पूर्ण

अटल पूर्णांक sched_partition_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा cpuset *cs = css_cs(seq_css(seq));

	चयन (cs->partition_root_state) अणु
	हाल PRS_ENABLED:
		seq_माला_दो(seq, "root\n");
		अवरोध;
	हाल PRS_DISABLED:
		seq_माला_दो(seq, "member\n");
		अवरोध;
	हाल PRS_ERROR:
		seq_माला_दो(seq, "root invalid\n");
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार sched_partition_ग_लिखो(काष्ठा kernfs_खोलो_file *of, अक्षर *buf,
				     माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा cpuset *cs = css_cs(of_css(of));
	पूर्णांक val;
	पूर्णांक retval = -ENODEV;

	buf = म_मालाip(buf);

	/*
	 * Convert "root" to ENABLED, and convert "member" to DISABLED.
	 */
	अगर (!म_भेद(buf, "root"))
		val = PRS_ENABLED;
	अन्यथा अगर (!म_भेद(buf, "member"))
		val = PRS_DISABLED;
	अन्यथा
		वापस -EINVAL;

	css_get(&cs->css);
	get_online_cpus();
	percpu_करोwn_ग_लिखो(&cpuset_rwsem);
	अगर (!is_cpuset_online(cs))
		जाओ out_unlock;

	retval = update_prstate(cs, val);
out_unlock:
	percpu_up_ग_लिखो(&cpuset_rwsem);
	put_online_cpus();
	css_put(&cs->css);
	वापस retval ?: nbytes;
पूर्ण

/*
 * क्रम the common functions, 'private' gives the type of file
 */

अटल काष्ठा cftype legacy_files[] = अणु
	अणु
		.name = "cpus",
		.seq_show = cpuset_common_seq_show,
		.ग_लिखो = cpuset_ग_लिखो_resmask,
		.max_ग_लिखो_len = (100U + 6 * NR_CPUS),
		.निजी = खाता_CPULIST,
	पूर्ण,

	अणु
		.name = "mems",
		.seq_show = cpuset_common_seq_show,
		.ग_लिखो = cpuset_ग_लिखो_resmask,
		.max_ग_लिखो_len = (100U + 6 * MAX_NUMNODES),
		.निजी = खाता_MEMLIST,
	पूर्ण,

	अणु
		.name = "effective_cpus",
		.seq_show = cpuset_common_seq_show,
		.निजी = खाता_EFFECTIVE_CPULIST,
	पूर्ण,

	अणु
		.name = "effective_mems",
		.seq_show = cpuset_common_seq_show,
		.निजी = खाता_EFFECTIVE_MEMLIST,
	पूर्ण,

	अणु
		.name = "cpu_exclusive",
		.पढ़ो_u64 = cpuset_पढ़ो_u64,
		.ग_लिखो_u64 = cpuset_ग_लिखो_u64,
		.निजी = खाता_CPU_EXCLUSIVE,
	पूर्ण,

	अणु
		.name = "mem_exclusive",
		.पढ़ो_u64 = cpuset_पढ़ो_u64,
		.ग_लिखो_u64 = cpuset_ग_लिखो_u64,
		.निजी = खाता_MEM_EXCLUSIVE,
	पूर्ण,

	अणु
		.name = "mem_hardwall",
		.पढ़ो_u64 = cpuset_पढ़ो_u64,
		.ग_लिखो_u64 = cpuset_ग_लिखो_u64,
		.निजी = खाता_MEM_HARDWALL,
	पूर्ण,

	अणु
		.name = "sched_load_balance",
		.पढ़ो_u64 = cpuset_पढ़ो_u64,
		.ग_लिखो_u64 = cpuset_ग_लिखो_u64,
		.निजी = खाता_SCHED_LOAD_BALANCE,
	पूर्ण,

	अणु
		.name = "sched_relax_domain_level",
		.पढ़ो_s64 = cpuset_पढ़ो_s64,
		.ग_लिखो_s64 = cpuset_ग_लिखो_s64,
		.निजी = खाता_SCHED_RELAX_DOMAIN_LEVEL,
	पूर्ण,

	अणु
		.name = "memory_migrate",
		.पढ़ो_u64 = cpuset_पढ़ो_u64,
		.ग_लिखो_u64 = cpuset_ग_लिखो_u64,
		.निजी = खाता_MEMORY_MIGRATE,
	पूर्ण,

	अणु
		.name = "memory_pressure",
		.पढ़ो_u64 = cpuset_पढ़ो_u64,
		.निजी = खाता_MEMORY_PRESSURE,
	पूर्ण,

	अणु
		.name = "memory_spread_page",
		.पढ़ो_u64 = cpuset_पढ़ो_u64,
		.ग_लिखो_u64 = cpuset_ग_लिखो_u64,
		.निजी = खाता_SPREAD_PAGE,
	पूर्ण,

	अणु
		.name = "memory_spread_slab",
		.पढ़ो_u64 = cpuset_पढ़ो_u64,
		.ग_लिखो_u64 = cpuset_ग_लिखो_u64,
		.निजी = खाता_SPREAD_SLAB,
	पूर्ण,

	अणु
		.name = "memory_pressure_enabled",
		.flags = CFTYPE_ONLY_ON_ROOT,
		.पढ़ो_u64 = cpuset_पढ़ो_u64,
		.ग_लिखो_u64 = cpuset_ग_लिखो_u64,
		.निजी = खाता_MEMORY_PRESSURE_ENABLED,
	पूर्ण,

	अणु पूर्ण	/* terminate */
पूर्ण;

/*
 * This is currently a minimal set क्रम the शेष hierarchy. It can be
 * expanded later on by migrating more features and control files from v1.
 */
अटल काष्ठा cftype dfl_files[] = अणु
	अणु
		.name = "cpus",
		.seq_show = cpuset_common_seq_show,
		.ग_लिखो = cpuset_ग_लिखो_resmask,
		.max_ग_लिखो_len = (100U + 6 * NR_CPUS),
		.निजी = खाता_CPULIST,
		.flags = CFTYPE_NOT_ON_ROOT,
	पूर्ण,

	अणु
		.name = "mems",
		.seq_show = cpuset_common_seq_show,
		.ग_लिखो = cpuset_ग_लिखो_resmask,
		.max_ग_लिखो_len = (100U + 6 * MAX_NUMNODES),
		.निजी = खाता_MEMLIST,
		.flags = CFTYPE_NOT_ON_ROOT,
	पूर्ण,

	अणु
		.name = "cpus.effective",
		.seq_show = cpuset_common_seq_show,
		.निजी = खाता_EFFECTIVE_CPULIST,
	पूर्ण,

	अणु
		.name = "mems.effective",
		.seq_show = cpuset_common_seq_show,
		.निजी = खाता_EFFECTIVE_MEMLIST,
	पूर्ण,

	अणु
		.name = "cpus.partition",
		.seq_show = sched_partition_show,
		.ग_लिखो = sched_partition_ग_लिखो,
		.निजी = खाता_PARTITION_ROOT,
		.flags = CFTYPE_NOT_ON_ROOT,
	पूर्ण,

	अणु
		.name = "cpus.subpartitions",
		.seq_show = cpuset_common_seq_show,
		.निजी = खाता_SUBPARTS_CPULIST,
		.flags = CFTYPE_DEBUG,
	पूर्ण,

	अणु पूर्ण	/* terminate */
पूर्ण;


/*
 *	cpuset_css_alloc - allocate a cpuset css
 *	cgrp:	control group that the new cpuset will be part of
 */

अटल काष्ठा cgroup_subsys_state *
cpuset_css_alloc(काष्ठा cgroup_subsys_state *parent_css)
अणु
	काष्ठा cpuset *cs;

	अगर (!parent_css)
		वापस &top_cpuset.css;

	cs = kzalloc(माप(*cs), GFP_KERNEL);
	अगर (!cs)
		वापस ERR_PTR(-ENOMEM);

	अगर (alloc_cpumasks(cs, शून्य)) अणु
		kमुक्त(cs);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	set_bit(CS_SCHED_LOAD_BALANCE, &cs->flags);
	nodes_clear(cs->mems_allowed);
	nodes_clear(cs->effective_mems);
	fmeter_init(&cs->fmeter);
	cs->relax_करोमुख्य_level = -1;

	वापस &cs->css;
पूर्ण

अटल पूर्णांक cpuset_css_online(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा cpuset *cs = css_cs(css);
	काष्ठा cpuset *parent = parent_cs(cs);
	काष्ठा cpuset *पंचांगp_cs;
	काष्ठा cgroup_subsys_state *pos_css;

	अगर (!parent)
		वापस 0;

	get_online_cpus();
	percpu_करोwn_ग_लिखो(&cpuset_rwsem);

	set_bit(CS_ONLINE, &cs->flags);
	अगर (is_spपढ़ो_page(parent))
		set_bit(CS_SPREAD_PAGE, &cs->flags);
	अगर (is_spपढ़ो_slab(parent))
		set_bit(CS_SPREAD_SLAB, &cs->flags);

	cpuset_inc();

	spin_lock_irq(&callback_lock);
	अगर (is_in_v2_mode()) अणु
		cpumask_copy(cs->effective_cpus, parent->effective_cpus);
		cs->effective_mems = parent->effective_mems;
		cs->use_parent_ecpus = true;
		parent->child_ecpus_count++;
	पूर्ण
	spin_unlock_irq(&callback_lock);

	अगर (!test_bit(CGRP_CPUSET_CLONE_CHILDREN, &css->cgroup->flags))
		जाओ out_unlock;

	/*
	 * Clone @parent's configuration अगर CGRP_CPUSET_CLONE_CHILDREN is
	 * set.  This flag handling is implemented in cgroup core क्रम
	 * histrical reasons - the flag may be specअगरied during mount.
	 *
	 * Currently, अगर any sibling cpusets have exclusive cpus or mem, we
	 * refuse to clone the configuration - thereby refusing the task to
	 * be entered, and as a result refusing the sys_unshare() or
	 * clone() which initiated it.  If this becomes a problem क्रम some
	 * users who wish to allow that scenario, then this could be
	 * changed to grant parent->cpus_allowed-sibling_cpus_exclusive
	 * (and likewise क्रम mems) to the new cgroup.
	 */
	rcu_पढ़ो_lock();
	cpuset_क्रम_each_child(पंचांगp_cs, pos_css, parent) अणु
		अगर (is_mem_exclusive(पंचांगp_cs) || is_cpu_exclusive(पंचांगp_cs)) अणु
			rcu_पढ़ो_unlock();
			जाओ out_unlock;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	spin_lock_irq(&callback_lock);
	cs->mems_allowed = parent->mems_allowed;
	cs->effective_mems = parent->mems_allowed;
	cpumask_copy(cs->cpus_allowed, parent->cpus_allowed);
	cpumask_copy(cs->effective_cpus, parent->cpus_allowed);
	spin_unlock_irq(&callback_lock);
out_unlock:
	percpu_up_ग_लिखो(&cpuset_rwsem);
	put_online_cpus();
	वापस 0;
पूर्ण

/*
 * If the cpuset being हटाओd has its flag 'sched_load_balance'
 * enabled, then simulate turning sched_load_balance off, which
 * will call rebuild_sched_करोमुख्यs_locked(). That is not needed
 * in the शेष hierarchy where only changes in partition
 * will cause repartitioning.
 *
 * If the cpuset has the 'sched.partition' flag enabled, simulate
 * turning 'sched.partition" off.
 */

अटल व्योम cpuset_css_offline(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा cpuset *cs = css_cs(css);

	get_online_cpus();
	percpu_करोwn_ग_लिखो(&cpuset_rwsem);

	अगर (is_partition_root(cs))
		update_prstate(cs, 0);

	अगर (!cgroup_subsys_on_dfl(cpuset_cgrp_subsys) &&
	    is_sched_load_balance(cs))
		update_flag(CS_SCHED_LOAD_BALANCE, cs, 0);

	अगर (cs->use_parent_ecpus) अणु
		काष्ठा cpuset *parent = parent_cs(cs);

		cs->use_parent_ecpus = false;
		parent->child_ecpus_count--;
	पूर्ण

	cpuset_dec();
	clear_bit(CS_ONLINE, &cs->flags);

	percpu_up_ग_लिखो(&cpuset_rwsem);
	put_online_cpus();
पूर्ण

अटल व्योम cpuset_css_मुक्त(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा cpuset *cs = css_cs(css);

	मुक्त_cpuset(cs);
पूर्ण

अटल व्योम cpuset_bind(काष्ठा cgroup_subsys_state *root_css)
अणु
	percpu_करोwn_ग_लिखो(&cpuset_rwsem);
	spin_lock_irq(&callback_lock);

	अगर (is_in_v2_mode()) अणु
		cpumask_copy(top_cpuset.cpus_allowed, cpu_possible_mask);
		top_cpuset.mems_allowed = node_possible_map;
	पूर्ण अन्यथा अणु
		cpumask_copy(top_cpuset.cpus_allowed,
			     top_cpuset.effective_cpus);
		top_cpuset.mems_allowed = top_cpuset.effective_mems;
	पूर्ण

	spin_unlock_irq(&callback_lock);
	percpu_up_ग_लिखो(&cpuset_rwsem);
पूर्ण

/*
 * Make sure the new task conक्रमm to the current state of its parent,
 * which could have been changed by cpuset just after it inherits the
 * state from the parent and beक्रमe it sits on the cgroup's task list.
 */
अटल व्योम cpuset_विभाजन(काष्ठा task_काष्ठा *task)
अणु
	अगर (task_css_is_root(task, cpuset_cgrp_id))
		वापस;

	set_cpus_allowed_ptr(task, current->cpus_ptr);
	task->mems_allowed = current->mems_allowed;
पूर्ण

काष्ठा cgroup_subsys cpuset_cgrp_subsys = अणु
	.css_alloc	= cpuset_css_alloc,
	.css_online	= cpuset_css_online,
	.css_offline	= cpuset_css_offline,
	.css_मुक्त	= cpuset_css_मुक्त,
	.can_attach	= cpuset_can_attach,
	.cancel_attach	= cpuset_cancel_attach,
	.attach		= cpuset_attach,
	.post_attach	= cpuset_post_attach,
	.bind		= cpuset_bind,
	.विभाजन		= cpuset_विभाजन,
	.legacy_cftypes	= legacy_files,
	.dfl_cftypes	= dfl_files,
	.early_init	= true,
	.thपढ़ोed	= true,
पूर्ण;

/**
 * cpuset_init - initialize cpusets at प्रणाली boot
 *
 * Description: Initialize top_cpuset
 **/

पूर्णांक __init cpuset_init(व्योम)
अणु
	BUG_ON(percpu_init_rwsem(&cpuset_rwsem));

	BUG_ON(!alloc_cpumask_var(&top_cpuset.cpus_allowed, GFP_KERNEL));
	BUG_ON(!alloc_cpumask_var(&top_cpuset.effective_cpus, GFP_KERNEL));
	BUG_ON(!zalloc_cpumask_var(&top_cpuset.subparts_cpus, GFP_KERNEL));

	cpumask_setall(top_cpuset.cpus_allowed);
	nodes_setall(top_cpuset.mems_allowed);
	cpumask_setall(top_cpuset.effective_cpus);
	nodes_setall(top_cpuset.effective_mems);

	fmeter_init(&top_cpuset.fmeter);
	set_bit(CS_SCHED_LOAD_BALANCE, &top_cpuset.flags);
	top_cpuset.relax_करोमुख्य_level = -1;

	BUG_ON(!alloc_cpumask_var(&cpus_attach, GFP_KERNEL));

	वापस 0;
पूर्ण

/*
 * If CPU and/or memory hotplug handlers, below, unplug any CPUs
 * or memory nodes, we need to walk over the cpuset hierarchy,
 * removing that CPU or node from all cpusets.  If this हटाओs the
 * last CPU or node from a cpuset, then move the tasks in the empty
 * cpuset to its next-highest non-empty parent.
 */
अटल व्योम हटाओ_tasks_in_empty_cpuset(काष्ठा cpuset *cs)
अणु
	काष्ठा cpuset *parent;

	/*
	 * Find its next-highest non-empty parent, (top cpuset
	 * has online cpus, so can't be empty).
	 */
	parent = parent_cs(cs);
	जबतक (cpumask_empty(parent->cpus_allowed) ||
			nodes_empty(parent->mems_allowed))
		parent = parent_cs(parent);

	अगर (cgroup_transfer_tasks(parent->css.cgroup, cs->css.cgroup)) अणु
		pr_err("cpuset: failed to transfer tasks out of empty cpuset ");
		pr_cont_cgroup_name(cs->css.cgroup);
		pr_cont("\n");
	पूर्ण
पूर्ण

अटल व्योम
hotplug_update_tasks_legacy(काष्ठा cpuset *cs,
			    काष्ठा cpumask *new_cpus, nodemask_t *new_mems,
			    bool cpus_updated, bool mems_updated)
अणु
	bool is_empty;

	spin_lock_irq(&callback_lock);
	cpumask_copy(cs->cpus_allowed, new_cpus);
	cpumask_copy(cs->effective_cpus, new_cpus);
	cs->mems_allowed = *new_mems;
	cs->effective_mems = *new_mems;
	spin_unlock_irq(&callback_lock);

	/*
	 * Don't call update_tasks_cpumask() अगर the cpuset becomes empty,
	 * as the tasks will be migratecd to an ancestor.
	 */
	अगर (cpus_updated && !cpumask_empty(cs->cpus_allowed))
		update_tasks_cpumask(cs);
	अगर (mems_updated && !nodes_empty(cs->mems_allowed))
		update_tasks_nodemask(cs);

	is_empty = cpumask_empty(cs->cpus_allowed) ||
		   nodes_empty(cs->mems_allowed);

	percpu_up_ग_लिखो(&cpuset_rwsem);

	/*
	 * Move tasks to the nearest ancestor with execution resources,
	 * This is full cgroup operation which will also call back पूर्णांकo
	 * cpuset. Should be करोne outside any lock.
	 */
	अगर (is_empty)
		हटाओ_tasks_in_empty_cpuset(cs);

	percpu_करोwn_ग_लिखो(&cpuset_rwsem);
पूर्ण

अटल व्योम
hotplug_update_tasks(काष्ठा cpuset *cs,
		     काष्ठा cpumask *new_cpus, nodemask_t *new_mems,
		     bool cpus_updated, bool mems_updated)
अणु
	अगर (cpumask_empty(new_cpus))
		cpumask_copy(new_cpus, parent_cs(cs)->effective_cpus);
	अगर (nodes_empty(*new_mems))
		*new_mems = parent_cs(cs)->effective_mems;

	spin_lock_irq(&callback_lock);
	cpumask_copy(cs->effective_cpus, new_cpus);
	cs->effective_mems = *new_mems;
	spin_unlock_irq(&callback_lock);

	अगर (cpus_updated)
		update_tasks_cpumask(cs);
	अगर (mems_updated)
		update_tasks_nodemask(cs);
पूर्ण

अटल bool क्रमce_rebuild;

व्योम cpuset_क्रमce_rebuild(व्योम)
अणु
	क्रमce_rebuild = true;
पूर्ण

/**
 * cpuset_hotplug_update_tasks - update tasks in a cpuset क्रम hotunplug
 * @cs: cpuset in पूर्णांकerest
 * @पंचांगp: the पंचांगpmasks काष्ठाure poपूर्णांकer
 *
 * Compare @cs's cpu and mem masks against top_cpuset and अगर some have gone
 * offline, update @cs accordingly.  If @cs ends up with no CPU or memory,
 * all its tasks are moved to the nearest ancestor with both resources.
 */
अटल व्योम cpuset_hotplug_update_tasks(काष्ठा cpuset *cs, काष्ठा पंचांगpmasks *पंचांगp)
अणु
	अटल cpumask_t new_cpus;
	अटल nodemask_t new_mems;
	bool cpus_updated;
	bool mems_updated;
	काष्ठा cpuset *parent;
retry:
	रुको_event(cpuset_attach_wq, cs->attach_in_progress == 0);

	percpu_करोwn_ग_लिखो(&cpuset_rwsem);

	/*
	 * We have raced with task attaching. We रुको until attaching
	 * is finished, so we won't attach a task to an empty cpuset.
	 */
	अगर (cs->attach_in_progress) अणु
		percpu_up_ग_लिखो(&cpuset_rwsem);
		जाओ retry;
	पूर्ण

	parent =  parent_cs(cs);
	compute_effective_cpumask(&new_cpus, cs, parent);
	nodes_and(new_mems, cs->mems_allowed, parent->effective_mems);

	अगर (cs->nr_subparts_cpus)
		/*
		 * Make sure that CPUs allocated to child partitions
		 * करो not show up in effective_cpus.
		 */
		cpumask_andnot(&new_cpus, &new_cpus, cs->subparts_cpus);

	अगर (!पंचांगp || !cs->partition_root_state)
		जाओ update_tasks;

	/*
	 * In the unlikely event that a partition root has empty
	 * effective_cpus or its parent becomes erroneous, we have to
	 * transition it to the erroneous state.
	 */
	अगर (is_partition_root(cs) && (cpumask_empty(&new_cpus) ||
	   (parent->partition_root_state == PRS_ERROR))) अणु
		अगर (cs->nr_subparts_cpus) अणु
			cs->nr_subparts_cpus = 0;
			cpumask_clear(cs->subparts_cpus);
			compute_effective_cpumask(&new_cpus, cs, parent);
		पूर्ण

		/*
		 * If the effective_cpus is empty because the child
		 * partitions take away all the CPUs, we can keep
		 * the current partition and let the child partitions
		 * fight क्रम available CPUs.
		 */
		अगर ((parent->partition_root_state == PRS_ERROR) ||
		     cpumask_empty(&new_cpus)) अणु
			update_parent_subparts_cpumask(cs, partcmd_disable,
						       शून्य, पंचांगp);
			cs->partition_root_state = PRS_ERROR;
		पूर्ण
		cpuset_क्रमce_rebuild();
	पूर्ण

	/*
	 * On the other hand, an erroneous partition root may be transitioned
	 * back to a regular one or a partition root with no CPU allocated
	 * from the parent may change to erroneous.
	 */
	अगर (is_partition_root(parent) &&
	   ((cs->partition_root_state == PRS_ERROR) ||
	    !cpumask_पूर्णांकersects(&new_cpus, parent->subparts_cpus)) &&
	     update_parent_subparts_cpumask(cs, partcmd_update, शून्य, पंचांगp))
		cpuset_क्रमce_rebuild();

update_tasks:
	cpus_updated = !cpumask_equal(&new_cpus, cs->effective_cpus);
	mems_updated = !nodes_equal(new_mems, cs->effective_mems);

	अगर (is_in_v2_mode())
		hotplug_update_tasks(cs, &new_cpus, &new_mems,
				     cpus_updated, mems_updated);
	अन्यथा
		hotplug_update_tasks_legacy(cs, &new_cpus, &new_mems,
					    cpus_updated, mems_updated);

	percpu_up_ग_लिखो(&cpuset_rwsem);
पूर्ण

/**
 * cpuset_hotplug_workfn - handle CPU/memory hotunplug क्रम a cpuset
 *
 * This function is called after either CPU or memory configuration has
 * changed and updates cpuset accordingly.  The top_cpuset is always
 * synchronized to cpu_active_mask and N_MEMORY, which is necessary in
 * order to make cpusets transparent (of no affect) on प्रणालीs that are
 * actively using CPU hotplug but making no active use of cpusets.
 *
 * Non-root cpusets are only affected by offlining.  If any CPUs or memory
 * nodes have been taken करोwn, cpuset_hotplug_update_tasks() is invoked on
 * all descendants.
 *
 * Note that CPU offlining during suspend is ignored.  We करोn't modअगरy
 * cpusets across suspend/resume cycles at all.
 */
अटल व्योम cpuset_hotplug_workfn(काष्ठा work_काष्ठा *work)
अणु
	अटल cpumask_t new_cpus;
	अटल nodemask_t new_mems;
	bool cpus_updated, mems_updated;
	bool on_dfl = is_in_v2_mode();
	काष्ठा पंचांगpmasks पंचांगp, *pपंचांगp = शून्य;

	अगर (on_dfl && !alloc_cpumasks(शून्य, &पंचांगp))
		pपंचांगp = &पंचांगp;

	percpu_करोwn_ग_लिखो(&cpuset_rwsem);

	/* fetch the available cpus/mems and find out which changed how */
	cpumask_copy(&new_cpus, cpu_active_mask);
	new_mems = node_states[N_MEMORY];

	/*
	 * If subparts_cpus is populated, it is likely that the check below
	 * will produce a false positive on cpus_updated when the cpu list
	 * isn't changed. It is extra work, but it is better to be safe.
	 */
	cpus_updated = !cpumask_equal(top_cpuset.effective_cpus, &new_cpus);
	mems_updated = !nodes_equal(top_cpuset.effective_mems, new_mems);

	/* synchronize cpus_allowed to cpu_active_mask */
	अगर (cpus_updated) अणु
		spin_lock_irq(&callback_lock);
		अगर (!on_dfl)
			cpumask_copy(top_cpuset.cpus_allowed, &new_cpus);
		/*
		 * Make sure that CPUs allocated to child partitions
		 * करो not show up in effective_cpus. If no CPU is left,
		 * we clear the subparts_cpus & let the child partitions
		 * fight क्रम the CPUs again.
		 */
		अगर (top_cpuset.nr_subparts_cpus) अणु
			अगर (cpumask_subset(&new_cpus,
					   top_cpuset.subparts_cpus)) अणु
				top_cpuset.nr_subparts_cpus = 0;
				cpumask_clear(top_cpuset.subparts_cpus);
			पूर्ण अन्यथा अणु
				cpumask_andnot(&new_cpus, &new_cpus,
					       top_cpuset.subparts_cpus);
			पूर्ण
		पूर्ण
		cpumask_copy(top_cpuset.effective_cpus, &new_cpus);
		spin_unlock_irq(&callback_lock);
		/* we करोn't mess with cpumasks of tasks in top_cpuset */
	पूर्ण

	/* synchronize mems_allowed to N_MEMORY */
	अगर (mems_updated) अणु
		spin_lock_irq(&callback_lock);
		अगर (!on_dfl)
			top_cpuset.mems_allowed = new_mems;
		top_cpuset.effective_mems = new_mems;
		spin_unlock_irq(&callback_lock);
		update_tasks_nodemask(&top_cpuset);
	पूर्ण

	percpu_up_ग_लिखो(&cpuset_rwsem);

	/* अगर cpus or mems changed, we need to propagate to descendants */
	अगर (cpus_updated || mems_updated) अणु
		काष्ठा cpuset *cs;
		काष्ठा cgroup_subsys_state *pos_css;

		rcu_पढ़ो_lock();
		cpuset_क्रम_each_descendant_pre(cs, pos_css, &top_cpuset) अणु
			अगर (cs == &top_cpuset || !css_tryget_online(&cs->css))
				जारी;
			rcu_पढ़ो_unlock();

			cpuset_hotplug_update_tasks(cs, pपंचांगp);

			rcu_पढ़ो_lock();
			css_put(&cs->css);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	/* rebuild sched करोमुख्यs अगर cpus_allowed has changed */
	अगर (cpus_updated || क्रमce_rebuild) अणु
		क्रमce_rebuild = false;
		rebuild_sched_करोमुख्यs();
	पूर्ण

	मुक्त_cpumasks(शून्य, pपंचांगp);
पूर्ण

व्योम cpuset_update_active_cpus(व्योम)
अणु
	/*
	 * We're inside cpu hotplug critical region which usually nests
	 * inside cgroup synchronization.  Bounce actual hotplug processing
	 * to a work item to aव्योम reverse locking order.
	 */
	schedule_work(&cpuset_hotplug_work);
पूर्ण

व्योम cpuset_रुको_क्रम_hotplug(व्योम)
अणु
	flush_work(&cpuset_hotplug_work);
पूर्ण

/*
 * Keep top_cpuset.mems_allowed tracking node_states[N_MEMORY].
 * Call this routine anyसमय after node_states[N_MEMORY] changes.
 * See cpuset_update_active_cpus() क्रम CPU hotplug handling.
 */
अटल पूर्णांक cpuset_track_online_nodes(काष्ठा notअगरier_block *self,
				अचिन्हित दीर्घ action, व्योम *arg)
अणु
	schedule_work(&cpuset_hotplug_work);
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block cpuset_track_online_nodes_nb = अणु
	.notअगरier_call = cpuset_track_online_nodes,
	.priority = 10,		/* ??! */
पूर्ण;

/**
 * cpuset_init_smp - initialize cpus_allowed
 *
 * Description: Finish top cpuset after cpu, node maps are initialized
 */
व्योम __init cpuset_init_smp(व्योम)
अणु
	cpumask_copy(top_cpuset.cpus_allowed, cpu_active_mask);
	top_cpuset.mems_allowed = node_states[N_MEMORY];
	top_cpuset.old_mems_allowed = top_cpuset.mems_allowed;

	cpumask_copy(top_cpuset.effective_cpus, cpu_active_mask);
	top_cpuset.effective_mems = node_states[N_MEMORY];

	रेजिस्टर_hoपंचांगemory_notअगरier(&cpuset_track_online_nodes_nb);

	cpuset_migrate_mm_wq = alloc_ordered_workqueue("cpuset_migrate_mm", 0);
	BUG_ON(!cpuset_migrate_mm_wq);
पूर्ण

/**
 * cpuset_cpus_allowed - वापस cpus_allowed mask from a tasks cpuset.
 * @tsk: poपूर्णांकer to task_काष्ठा from which to obtain cpuset->cpus_allowed.
 * @pmask: poपूर्णांकer to काष्ठा cpumask variable to receive cpus_allowed set.
 *
 * Description: Returns the cpumask_var_t cpus_allowed of the cpuset
 * attached to the specअगरied @tsk.  Guaranteed to वापस some non-empty
 * subset of cpu_online_mask, even अगर this means going outside the
 * tasks cpuset.
 **/

व्योम cpuset_cpus_allowed(काष्ठा task_काष्ठा *tsk, काष्ठा cpumask *pmask)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&callback_lock, flags);
	rcu_पढ़ो_lock();
	guarantee_online_cpus(task_cs(tsk), pmask);
	rcu_पढ़ो_unlock();
	spin_unlock_irqrestore(&callback_lock, flags);
पूर्ण

/**
 * cpuset_cpus_allowed_fallback - final fallback beक्रमe complete catastrophe.
 * @tsk: poपूर्णांकer to task_काष्ठा with which the scheduler is struggling
 *
 * Description: In the हाल that the scheduler cannot find an allowed cpu in
 * tsk->cpus_allowed, we fall back to task_cs(tsk)->cpus_allowed. In legacy
 * mode however, this value is the same as task_cs(tsk)->effective_cpus,
 * which will not contain a sane cpumask during हालs such as cpu hotplugging.
 * This is the असलolute last resort क्रम the scheduler and it is only used अगर
 * _every_ other avenue has been traveled.
 **/

व्योम cpuset_cpus_allowed_fallback(काष्ठा task_काष्ठा *tsk)
अणु
	rcu_पढ़ो_lock();
	करो_set_cpus_allowed(tsk, is_in_v2_mode() ?
		task_cs(tsk)->cpus_allowed : cpu_possible_mask);
	rcu_पढ़ो_unlock();

	/*
	 * We own tsk->cpus_allowed, nobody can change it under us.
	 *
	 * But we used cs && cs->cpus_allowed lockless and thus can
	 * race with cgroup_attach_task() or update_cpumask() and get
	 * the wrong tsk->cpus_allowed. However, both हालs imply the
	 * subsequent cpuset_change_cpumask()->set_cpus_allowed_ptr()
	 * which takes task_rq_lock().
	 *
	 * If we are called after it dropped the lock we must see all
	 * changes in tsk_cs()->cpus_allowed. Otherwise we can temporary
	 * set any mask even अगर it is not right from task_cs() pov,
	 * the pending set_cpus_allowed_ptr() will fix things.
	 *
	 * select_fallback_rq() will fix things ups and set cpu_possible_mask
	 * अगर required.
	 */
पूर्ण

व्योम __init cpuset_init_current_mems_allowed(व्योम)
अणु
	nodes_setall(current->mems_allowed);
पूर्ण

/**
 * cpuset_mems_allowed - वापस mems_allowed mask from a tasks cpuset.
 * @tsk: poपूर्णांकer to task_काष्ठा from which to obtain cpuset->mems_allowed.
 *
 * Description: Returns the nodemask_t mems_allowed of the cpuset
 * attached to the specअगरied @tsk.  Guaranteed to वापस some non-empty
 * subset of node_states[N_MEMORY], even अगर this means going outside the
 * tasks cpuset.
 **/

nodemask_t cpuset_mems_allowed(काष्ठा task_काष्ठा *tsk)
अणु
	nodemask_t mask;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&callback_lock, flags);
	rcu_पढ़ो_lock();
	guarantee_online_mems(task_cs(tsk), &mask);
	rcu_पढ़ो_unlock();
	spin_unlock_irqrestore(&callback_lock, flags);

	वापस mask;
पूर्ण

/**
 * cpuset_nodemask_valid_mems_allowed - check nodemask vs. current mems_allowed
 * @nodemask: the nodemask to be checked
 *
 * Are any of the nodes in the nodemask allowed in current->mems_allowed?
 */
पूर्णांक cpuset_nodemask_valid_mems_allowed(nodemask_t *nodemask)
अणु
	वापस nodes_पूर्णांकersects(*nodemask, current->mems_allowed);
पूर्ण

/*
 * nearest_hardwall_ancestor() - Returns the nearest mem_exclusive or
 * mem_hardwall ancestor to the specअगरied cpuset.  Call holding
 * callback_lock.  If no ancestor is mem_exclusive or mem_hardwall
 * (an unusual configuration), then वापसs the root cpuset.
 */
अटल काष्ठा cpuset *nearest_hardwall_ancestor(काष्ठा cpuset *cs)
अणु
	जबतक (!(is_mem_exclusive(cs) || is_mem_hardwall(cs)) && parent_cs(cs))
		cs = parent_cs(cs);
	वापस cs;
पूर्ण

/**
 * cpuset_node_allowed - Can we allocate on a memory node?
 * @node: is this an allowed node?
 * @gfp_mask: memory allocation flags
 *
 * If we're in पूर्णांकerrupt, yes, we can always allocate.  If @node is set in
 * current's mems_allowed, yes.  If it's not a __GFP_HARDWALL request and this
 * node is set in the nearest hardwalled cpuset ancestor to current's cpuset,
 * yes.  If current has access to memory reserves as an oom victim, yes.
 * Otherwise, no.
 *
 * GFP_USER allocations are marked with the __GFP_HARDWALL bit,
 * and करो not allow allocations outside the current tasks cpuset
 * unless the task has been OOM समाप्तed.
 * GFP_KERNEL allocations are not so marked, so can escape to the
 * nearest enclosing hardwalled ancestor cpuset.
 *
 * Scanning up parent cpusets requires callback_lock.  The
 * __alloc_pages() routine only calls here with __GFP_HARDWALL bit
 * _not_ set अगर it's a GFP_KERNEL allocation, and all nodes in the
 * current tasks mems_allowed came up empty on the first pass over
 * the zonelist.  So only GFP_KERNEL allocations, अगर all nodes in the
 * cpuset are लघु of memory, might require taking the callback_lock.
 *
 * The first call here from mm/page_alloc:get_page_from_मुक्तlist()
 * has __GFP_HARDWALL set in gfp_mask, enक्रमcing hardwall cpusets,
 * so no allocation on a node outside the cpuset is allowed (unless
 * in पूर्णांकerrupt, of course).
 *
 * The second pass through get_page_from_मुक्तlist() करोesn't even call
 * here क्रम GFP_ATOMIC calls.  For those calls, the __alloc_pages()
 * variable 'wait' is not set, and the bit ALLOC_CPUSET is not set
 * in alloc_flags.  That logic and the checks below have the combined
 * affect that:
 *	in_पूर्णांकerrupt - any node ok (current task context irrelevant)
 *	GFP_ATOMIC   - any node ok
 *	tsk_is_oom_victim   - any node ok
 *	GFP_KERNEL   - any node in enclosing hardwalled cpuset ok
 *	GFP_USER     - only nodes in current tasks mems allowed ok.
 */
bool __cpuset_node_allowed(पूर्णांक node, gfp_t gfp_mask)
अणु
	काष्ठा cpuset *cs;		/* current cpuset ancestors */
	पूर्णांक allowed;			/* is allocation in zone z allowed? */
	अचिन्हित दीर्घ flags;

	अगर (in_पूर्णांकerrupt())
		वापस true;
	अगर (node_isset(node, current->mems_allowed))
		वापस true;
	/*
	 * Allow tasks that have access to memory reserves because they have
	 * been OOM समाप्तed to get memory anywhere.
	 */
	अगर (unlikely(tsk_is_oom_victim(current)))
		वापस true;
	अगर (gfp_mask & __GFP_HARDWALL)	/* If hardwall request, stop here */
		वापस false;

	अगर (current->flags & PF_EXITING) /* Let dying task have memory */
		वापस true;

	/* Not hardwall and node outside mems_allowed: scan up cpusets */
	spin_lock_irqsave(&callback_lock, flags);

	rcu_पढ़ो_lock();
	cs = nearest_hardwall_ancestor(task_cs(current));
	allowed = node_isset(node, cs->mems_allowed);
	rcu_पढ़ो_unlock();

	spin_unlock_irqrestore(&callback_lock, flags);
	वापस allowed;
पूर्ण

/**
 * cpuset_mem_spपढ़ो_node() - On which node to begin search क्रम a file page
 * cpuset_slab_spपढ़ो_node() - On which node to begin search क्रम a slab page
 *
 * If a task is marked PF_SPREAD_PAGE or PF_SPREAD_SLAB (as क्रम
 * tasks in a cpuset with is_spपढ़ो_page or is_spपढ़ो_slab set),
 * and अगर the memory allocation used cpuset_mem_spपढ़ो_node()
 * to determine on which node to start looking, as it will क्रम
 * certain page cache or slab cache pages such as used क्रम file
 * प्रणाली buffers and inode caches, then instead of starting on the
 * local node to look क्रम a मुक्त page, rather spपढ़ो the starting
 * node around the tasks mems_allowed nodes.
 *
 * We करोn't have to worry about the वापसed node being offline
 * because "it can't happen", and even अगर it did, it would be ok.
 *
 * The routines calling guarantee_online_mems() are careful to
 * only set nodes in task->mems_allowed that are online.  So it
 * should not be possible क्रम the following code to वापस an
 * offline node.  But अगर it did, that would be ok, as this routine
 * is not वापसing the node where the allocation must be, only
 * the node where the search should start.  The zonelist passed to
 * __alloc_pages() will include all nodes.  If the slab allocator
 * is passed an offline node, it will fall back to the local node.
 * See kmem_cache_alloc_node().
 */

अटल पूर्णांक cpuset_spपढ़ो_node(पूर्णांक *rotor)
अणु
	वापस *rotor = next_node_in(*rotor, current->mems_allowed);
पूर्ण

पूर्णांक cpuset_mem_spपढ़ो_node(व्योम)
अणु
	अगर (current->cpuset_mem_spपढ़ो_rotor == NUMA_NO_NODE)
		current->cpuset_mem_spपढ़ो_rotor =
			node_अक्रमom(&current->mems_allowed);

	वापस cpuset_spपढ़ो_node(&current->cpuset_mem_spपढ़ो_rotor);
पूर्ण

पूर्णांक cpuset_slab_spपढ़ो_node(व्योम)
अणु
	अगर (current->cpuset_slab_spपढ़ो_rotor == NUMA_NO_NODE)
		current->cpuset_slab_spपढ़ो_rotor =
			node_अक्रमom(&current->mems_allowed);

	वापस cpuset_spपढ़ो_node(&current->cpuset_slab_spपढ़ो_rotor);
पूर्ण

EXPORT_SYMBOL_GPL(cpuset_mem_spपढ़ो_node);

/**
 * cpuset_mems_allowed_पूर्णांकersects - Does @tsk1's mems_allowed intersect @tsk2's?
 * @tsk1: poपूर्णांकer to task_काष्ठा of some task.
 * @tsk2: poपूर्णांकer to task_काष्ठा of some other task.
 *
 * Description: Return true अगर @tsk1's mems_allowed पूर्णांकersects the
 * mems_allowed of @tsk2.  Used by the OOM समाप्तer to determine अगर
 * one of the task's memory usage might impact the memory available
 * to the other.
 **/

पूर्णांक cpuset_mems_allowed_पूर्णांकersects(स्थिर काष्ठा task_काष्ठा *tsk1,
				   स्थिर काष्ठा task_काष्ठा *tsk2)
अणु
	वापस nodes_पूर्णांकersects(tsk1->mems_allowed, tsk2->mems_allowed);
पूर्ण

/**
 * cpuset_prपूर्णांक_current_mems_allowed - prपूर्णांकs current's cpuset and mems_allowed
 *
 * Description: Prपूर्णांकs current's name, cpuset name, and cached copy of its
 * mems_allowed to the kernel log.
 */
व्योम cpuset_prपूर्णांक_current_mems_allowed(व्योम)
अणु
	काष्ठा cgroup *cgrp;

	rcu_पढ़ो_lock();

	cgrp = task_cs(current)->css.cgroup;
	pr_cont(",cpuset=");
	pr_cont_cgroup_name(cgrp);
	pr_cont(",mems_allowed=%*pbl",
		nodemask_pr_args(&current->mems_allowed));

	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Collection of memory_pressure is suppressed unless
 * this flag is enabled by writing "1" to the special
 * cpuset file 'memory_pressure_enabled' in the root cpuset.
 */

पूर्णांक cpuset_memory_pressure_enabled __पढ़ो_mostly;

/**
 * cpuset_memory_pressure_bump - keep stats of per-cpuset reclaims.
 *
 * Keep a running average of the rate of synchronous (direct)
 * page reclaim efक्रमts initiated by tasks in each cpuset.
 *
 * This represents the rate at which some task in the cpuset
 * ran low on memory on all nodes it was allowed to use, and
 * had to enter the kernels page reclaim code in an efक्रमt to
 * create more मुक्त memory by tossing clean pages or swapping
 * or writing dirty pages.
 *
 * Display to user space in the per-cpuset पढ़ो-only file
 * "memory_pressure".  Value displayed is an पूर्णांकeger
 * representing the recent rate of entry पूर्णांकo the synchronous
 * (direct) page reclaim by any task attached to the cpuset.
 **/

व्योम __cpuset_memory_pressure_bump(व्योम)
अणु
	rcu_पढ़ो_lock();
	fmeter_markevent(&task_cs(current)->fmeter);
	rcu_पढ़ो_unlock();
पूर्ण

#अगर_घोषित CONFIG_PROC_PID_CPUSET
/*
 * proc_cpuset_show()
 *  - Prपूर्णांक tasks cpuset path पूर्णांकo seq_file.
 *  - Used क्रम /proc/<pid>/cpuset.
 *  - No need to task_lock(tsk) on this tsk->cpuset reference, as it
 *    करोesn't really matter अगर tsk->cpuset changes after we पढ़ो it,
 *    and we take cpuset_mutex, keeping cpuset_attach() from changing it
 *    anyway.
 */
पूर्णांक proc_cpuset_show(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
		     काष्ठा pid *pid, काष्ठा task_काष्ठा *tsk)
अणु
	अक्षर *buf;
	काष्ठा cgroup_subsys_state *css;
	पूर्णांक retval;

	retval = -ENOMEM;
	buf = kदो_स्मृति(PATH_MAX, GFP_KERNEL);
	अगर (!buf)
		जाओ out;

	css = task_get_css(tsk, cpuset_cgrp_id);
	retval = cgroup_path_ns(css->cgroup, buf, PATH_MAX,
				current->nsproxy->cgroup_ns);
	css_put(css);
	अगर (retval >= PATH_MAX)
		retval = -ENAMETOOLONG;
	अगर (retval < 0)
		जाओ out_मुक्त;
	seq_माला_दो(m, buf);
	seq_अ_दो(m, '\n');
	retval = 0;
out_मुक्त:
	kमुक्त(buf);
out:
	वापस retval;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_PID_CPUSET */

/* Display task mems_allowed in /proc/<pid>/status file. */
व्योम cpuset_task_status_allowed(काष्ठा seq_file *m, काष्ठा task_काष्ठा *task)
अणु
	seq_म_लिखो(m, "Mems_allowed:\t%*pb\n",
		   nodemask_pr_args(&task->mems_allowed));
	seq_म_लिखो(m, "Mems_allowed_list:\t%*pbl\n",
		   nodemask_pr_args(&task->mems_allowed));
पूर्ण
