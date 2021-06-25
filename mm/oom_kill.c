<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/mm/oom_समाप्त.c
 * 
 *  Copyright (C)  1998,2000  Rik van Riel
 *	Thanks go out to Claus Fischer क्रम some serious inspiration and
 *	क्रम goading me पूर्णांकo coding this file...
 *  Copyright (C)  2010  Google, Inc.
 *	Rewritten by David Rientjes
 *
 *  The routines in this file are used to समाप्त a process when
 *  we're seriously out of memory. This माला_लो called from __alloc_pages()
 *  in mm/page_alloc.c when we really run out of memory.
 *
 *  Since we won't call these routines often (on a well-configured
 *  machine) this file will द्विगुन as a 'coding guide' and a signpost
 *  क्रम newbie kernel hackers. It features several poपूर्णांकers to major
 *  kernel subप्रणालीs and hपूर्णांकs as to where to find out what things करो.
 */

#समावेश <linux/oom.h>
#समावेश <linux/mm.h>
#समावेश <linux/err.h>
#समावेश <linux/gfp.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/swap.h>
#समावेश <linux/समयx.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/export.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/security.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/init.h>
#समावेश <linux/mmu_notअगरier.h>

#समावेश <यंत्र/tlb.h>
#समावेश "internal.h"
#समावेश "slab.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/oom.h>

पूर्णांक sysctl_panic_on_oom;
पूर्णांक sysctl_oom_समाप्त_allocating_task;
पूर्णांक sysctl_oom_dump_tasks = 1;

/*
 * Serializes oom समाप्तer invocations (out_of_memory()) from all contexts to
 * prevent from over eager oom समाप्तing (e.g. when the oom समाप्तer is invoked
 * from dअगरferent करोमुख्यs).
 *
 * oom_समाप्तer_disable() relies on this lock to stabilize oom_समाप्तer_disabled
 * and mark_oom_victim
 */
DEFINE_MUTEX(oom_lock);
/* Serializes oom_score_adj and oom_score_adj_min updates */
DEFINE_MUTEX(oom_adj_mutex);

अटल अंतरभूत bool is_memcg_oom(काष्ठा oom_control *oc)
अणु
	वापस oc->memcg != शून्य;
पूर्ण

#अगर_घोषित CONFIG_NUMA
/**
 * oom_cpuset_eligible() - check task eligibility क्रम समाप्त
 * @start: task काष्ठा of which task to consider
 * @oc: poपूर्णांकer to काष्ठा oom_control
 *
 * Task eligibility is determined by whether or not a candidate task, @tsk,
 * shares the same mempolicy nodes as current अगर it is bound by such a policy
 * and whether or not it has the same set of allowed cpuset nodes.
 *
 * This function is assuming oom-समाप्तer context and 'current' has triggered
 * the oom-समाप्तer.
 */
अटल bool oom_cpuset_eligible(काष्ठा task_काष्ठा *start,
				काष्ठा oom_control *oc)
अणु
	काष्ठा task_काष्ठा *tsk;
	bool ret = false;
	स्थिर nodemask_t *mask = oc->nodemask;

	अगर (is_memcg_oom(oc))
		वापस true;

	rcu_पढ़ो_lock();
	क्रम_each_thपढ़ो(start, tsk) अणु
		अगर (mask) अणु
			/*
			 * If this is a mempolicy स्थिरrained oom, tsk's
			 * cpuset is irrelevant.  Only वापस true अगर its
			 * mempolicy पूर्णांकersects current, otherwise it may be
			 * needlessly समाप्तed.
			 */
			ret = mempolicy_nodemask_पूर्णांकersects(tsk, mask);
		पूर्ण अन्यथा अणु
			/*
			 * This is not a mempolicy स्थिरrained oom, so only
			 * check the mems of tsk's cpuset.
			 */
			ret = cpuset_mems_allowed_पूर्णांकersects(current, tsk);
		पूर्ण
		अगर (ret)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
#अन्यथा
अटल bool oom_cpuset_eligible(काष्ठा task_काष्ठा *tsk, काष्ठा oom_control *oc)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA */

/*
 * The process p may have detached its own ->mm जबतक निकासing or through
 * kthपढ़ो_use_mm(), but one or more of its subthपढ़ोs may still have a valid
 * poपूर्णांकer.  Return p, or any of its subthपढ़ोs with a valid ->mm, with
 * task_lock() held.
 */
काष्ठा task_काष्ठा *find_lock_task_mm(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा task_काष्ठा *t;

	rcu_पढ़ो_lock();

	क्रम_each_thपढ़ो(p, t) अणु
		task_lock(t);
		अगर (likely(t->mm))
			जाओ found;
		task_unlock(t);
	पूर्ण
	t = शून्य;
found:
	rcu_पढ़ो_unlock();

	वापस t;
पूर्ण

/*
 * order == -1 means the oom समाप्त is required by sysrq, otherwise only
 * क्रम display purposes.
 */
अटल अंतरभूत bool is_sysrq_oom(काष्ठा oom_control *oc)
अणु
	वापस oc->order == -1;
पूर्ण

/* वापस true अगर the task is not adequate as candidate victim task. */
अटल bool oom_unसमाप्तable_task(काष्ठा task_काष्ठा *p)
अणु
	अगर (is_global_init(p))
		वापस true;
	अगर (p->flags & PF_KTHREAD)
		वापस true;
	वापस false;
पूर्ण

/*
 * Check whether unreclaimable slab amount is greater than
 * all user memory(LRU pages).
 * dump_unreclaimable_slab() could help in the हाल that
 * oom due to too much unreclaimable slab used by kernel.
*/
अटल bool should_dump_unreclaim_slab(व्योम)
अणु
	अचिन्हित दीर्घ nr_lru;

	nr_lru = global_node_page_state(NR_ACTIVE_ANON) +
		 global_node_page_state(NR_INACTIVE_ANON) +
		 global_node_page_state(NR_ACTIVE_खाता) +
		 global_node_page_state(NR_INACTIVE_खाता) +
		 global_node_page_state(NR_ISOLATED_ANON) +
		 global_node_page_state(NR_ISOLATED_खाता) +
		 global_node_page_state(NR_UNEVICTABLE);

	वापस (global_node_page_state_pages(NR_SLAB_UNRECLAIMABLE_B) > nr_lru);
पूर्ण

/**
 * oom_badness - heuristic function to determine which candidate task to समाप्त
 * @p: task काष्ठा of which task we should calculate
 * @totalpages: total present RAM allowed क्रम page allocation
 *
 * The heuristic क्रम determining which task to समाप्त is made to be as simple and
 * predictable as possible.  The goal is to वापस the highest value क्रम the
 * task consuming the most memory to aव्योम subsequent oom failures.
 */
दीर्घ oom_badness(काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ totalpages)
अणु
	दीर्घ poपूर्णांकs;
	दीर्घ adj;

	अगर (oom_unसमाप्तable_task(p))
		वापस दीर्घ_न्यून;

	p = find_lock_task_mm(p);
	अगर (!p)
		वापस दीर्घ_न्यून;

	/*
	 * Do not even consider tasks which are explicitly marked oom
	 * unसमाप्तable or have been alपढ़ोy oom reaped or the are in
	 * the middle of vविभाजन
	 */
	adj = (दीर्घ)p->संकेत->oom_score_adj;
	अगर (adj == OOM_SCORE_ADJ_MIN ||
			test_bit(MMF_OOM_SKIP, &p->mm->flags) ||
			in_vविभाजन(p)) अणु
		task_unlock(p);
		वापस दीर्घ_न्यून;
	पूर्ण

	/*
	 * The baseline क्रम the badness score is the proportion of RAM that each
	 * task's rss, pagetable and swap space use.
	 */
	poपूर्णांकs = get_mm_rss(p->mm) + get_mm_counter(p->mm, MM_SWAPENTS) +
		mm_pgtables_bytes(p->mm) / PAGE_SIZE;
	task_unlock(p);

	/* Normalize to oom_score_adj units */
	adj *= totalpages / 1000;
	poपूर्णांकs += adj;

	वापस poपूर्णांकs;
पूर्ण

अटल स्थिर अक्षर * स्थिर oom_स्थिरraपूर्णांक_text[] = अणु
	[CONSTRAINT_NONE] = "CONSTRAINT_NONE",
	[CONSTRAINT_CPUSET] = "CONSTRAINT_CPUSET",
	[CONSTRAINT_MEMORY_POLICY] = "CONSTRAINT_MEMORY_POLICY",
	[CONSTRAINT_MEMCG] = "CONSTRAINT_MEMCG",
पूर्ण;

/*
 * Determine the type of allocation स्थिरraपूर्णांक.
 */
अटल क्रमागत oom_स्थिरraपूर्णांक स्थिरrained_alloc(काष्ठा oom_control *oc)
अणु
	काष्ठा zone *zone;
	काष्ठा zoneref *z;
	क्रमागत zone_type highest_zoneidx = gfp_zone(oc->gfp_mask);
	bool cpuset_limited = false;
	पूर्णांक nid;

	अगर (is_memcg_oom(oc)) अणु
		oc->totalpages = mem_cgroup_get_max(oc->memcg) ?: 1;
		वापस CONSTRAINT_MEMCG;
	पूर्ण

	/* Default to all available memory */
	oc->totalpages = totalram_pages() + total_swap_pages;

	अगर (!IS_ENABLED(CONFIG_NUMA))
		वापस CONSTRAINT_NONE;

	अगर (!oc->zonelist)
		वापस CONSTRAINT_NONE;
	/*
	 * Reach here only when __GFP_NOFAIL is used. So, we should aव्योम
	 * to समाप्त current.We have to अक्रमom task समाप्त in this हाल.
	 * Hopefully, CONSTRAINT_THISNODE...but no way to handle it, now.
	 */
	अगर (oc->gfp_mask & __GFP_THISNODE)
		वापस CONSTRAINT_NONE;

	/*
	 * This is not a __GFP_THISNODE allocation, so a truncated nodemask in
	 * the page allocator means a mempolicy is in effect.  Cpuset policy
	 * is enक्रमced in get_page_from_मुक्तlist().
	 */
	अगर (oc->nodemask &&
	    !nodes_subset(node_states[N_MEMORY], *oc->nodemask)) अणु
		oc->totalpages = total_swap_pages;
		क्रम_each_node_mask(nid, *oc->nodemask)
			oc->totalpages += node_present_pages(nid);
		वापस CONSTRAINT_MEMORY_POLICY;
	पूर्ण

	/* Check this allocation failure is caused by cpuset's wall function */
	क्रम_each_zone_zonelist_nodemask(zone, z, oc->zonelist,
			highest_zoneidx, oc->nodemask)
		अगर (!cpuset_zone_allowed(zone, oc->gfp_mask))
			cpuset_limited = true;

	अगर (cpuset_limited) अणु
		oc->totalpages = total_swap_pages;
		क्रम_each_node_mask(nid, cpuset_current_mems_allowed)
			oc->totalpages += node_present_pages(nid);
		वापस CONSTRAINT_CPUSET;
	पूर्ण
	वापस CONSTRAINT_NONE;
पूर्ण

अटल पूर्णांक oom_evaluate_task(काष्ठा task_काष्ठा *task, व्योम *arg)
अणु
	काष्ठा oom_control *oc = arg;
	दीर्घ poपूर्णांकs;

	अगर (oom_unसमाप्तable_task(task))
		जाओ next;

	/* p may not have मुक्तable memory in nodemask */
	अगर (!is_memcg_oom(oc) && !oom_cpuset_eligible(task, oc))
		जाओ next;

	/*
	 * This task alपढ़ोy has access to memory reserves and is being समाप्तed.
	 * Don't allow any other task to have access to the reserves unless
	 * the task has MMF_OOM_SKIP because chances that it would release
	 * any memory is quite low.
	 */
	अगर (!is_sysrq_oom(oc) && tsk_is_oom_victim(task)) अणु
		अगर (test_bit(MMF_OOM_SKIP, &task->संकेत->oom_mm->flags))
			जाओ next;
		जाओ पात;
	पूर्ण

	/*
	 * If task is allocating a lot of memory and has been marked to be
	 * समाप्तed first अगर it triggers an oom, then select it.
	 */
	अगर (oom_task_origin(task)) अणु
		poपूर्णांकs = दीर्घ_उच्च;
		जाओ select;
	पूर्ण

	poपूर्णांकs = oom_badness(task, oc->totalpages);
	अगर (poपूर्णांकs == दीर्घ_न्यून || poपूर्णांकs < oc->chosen_poपूर्णांकs)
		जाओ next;

select:
	अगर (oc->chosen)
		put_task_काष्ठा(oc->chosen);
	get_task_काष्ठा(task);
	oc->chosen = task;
	oc->chosen_poपूर्णांकs = poपूर्णांकs;
next:
	वापस 0;
पात:
	अगर (oc->chosen)
		put_task_काष्ठा(oc->chosen);
	oc->chosen = (व्योम *)-1UL;
	वापस 1;
पूर्ण

/*
 * Simple selection loop. We choose the process with the highest number of
 * 'points'. In हाल scan was पातed, oc->chosen is set to -1.
 */
अटल व्योम select_bad_process(काष्ठा oom_control *oc)
अणु
	oc->chosen_poपूर्णांकs = दीर्घ_न्यून;

	अगर (is_memcg_oom(oc))
		mem_cgroup_scan_tasks(oc->memcg, oom_evaluate_task, oc);
	अन्यथा अणु
		काष्ठा task_काष्ठा *p;

		rcu_पढ़ो_lock();
		क्रम_each_process(p)
			अगर (oom_evaluate_task(p, oc))
				अवरोध;
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

अटल पूर्णांक dump_task(काष्ठा task_काष्ठा *p, व्योम *arg)
अणु
	काष्ठा oom_control *oc = arg;
	काष्ठा task_काष्ठा *task;

	अगर (oom_unसमाप्तable_task(p))
		वापस 0;

	/* p may not have मुक्तable memory in nodemask */
	अगर (!is_memcg_oom(oc) && !oom_cpuset_eligible(p, oc))
		वापस 0;

	task = find_lock_task_mm(p);
	अगर (!task) अणु
		/*
		 * All of p's threads have already detached their mm's. There's
		 * no need to report them; they can't be oom समाप्तed anyway.
		 */
		वापस 0;
	पूर्ण

	pr_info("[%7d] %5d %5d %8lu %8lu %8ld %8lu         %5hd %s\n",
		task->pid, from_kuid(&init_user_ns, task_uid(task)),
		task->tgid, task->mm->total_vm, get_mm_rss(task->mm),
		mm_pgtables_bytes(task->mm),
		get_mm_counter(task->mm, MM_SWAPENTS),
		task->संकेत->oom_score_adj, task->comm);
	task_unlock(task);

	वापस 0;
पूर्ण

/**
 * dump_tasks - dump current memory state of all प्रणाली tasks
 * @oc: poपूर्णांकer to काष्ठा oom_control
 *
 * Dumps the current memory state of all eligible tasks.  Tasks not in the same
 * memcg, not in the same cpuset, or bound to a disjoपूर्णांक set of mempolicy nodes
 * are not shown.
 * State inक्रमmation includes task's pid, uid, tgid, vm size, rss,
 * pgtables_bytes, swapents, oom_score_adj value, and name.
 */
अटल व्योम dump_tasks(काष्ठा oom_control *oc)
अणु
	pr_info("Tasks state (memory values in pages):\n");
	pr_info("[  pid  ]   uid  tgid total_vm      rss pgtables_bytes swapents oom_score_adj name\n");

	अगर (is_memcg_oom(oc))
		mem_cgroup_scan_tasks(oc->memcg, dump_task, oc);
	अन्यथा अणु
		काष्ठा task_काष्ठा *p;

		rcu_पढ़ो_lock();
		क्रम_each_process(p)
			dump_task(p, oc);
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

अटल व्योम dump_oom_summary(काष्ठा oom_control *oc, काष्ठा task_काष्ठा *victim)
अणु
	/* one line summary of the oom समाप्तer context. */
	pr_info("oom-kill:constraint=%s,nodemask=%*pbl",
			oom_स्थिरraपूर्णांक_text[oc->स्थिरraपूर्णांक],
			nodemask_pr_args(oc->nodemask));
	cpuset_prपूर्णांक_current_mems_allowed();
	mem_cgroup_prपूर्णांक_oom_context(oc->memcg, victim);
	pr_cont(",task=%s,pid=%d,uid=%d\n", victim->comm, victim->pid,
		from_kuid(&init_user_ns, task_uid(victim)));
पूर्ण

अटल व्योम dump_header(काष्ठा oom_control *oc, काष्ठा task_काष्ठा *p)
अणु
	pr_warn("%s invoked oom-killer: gfp_mask=%#x(%pGg), order=%d, oom_score_adj=%hd\n",
		current->comm, oc->gfp_mask, &oc->gfp_mask, oc->order,
			current->संकेत->oom_score_adj);
	अगर (!IS_ENABLED(CONFIG_COMPACTION) && oc->order)
		pr_warn("COMPACTION is disabled!!!\n");

	dump_stack();
	अगर (is_memcg_oom(oc))
		mem_cgroup_prपूर्णांक_oom_meminfo(oc->memcg);
	अन्यथा अणु
		show_mem(SHOW_MEM_FILTER_NODES, oc->nodemask);
		अगर (should_dump_unreclaim_slab())
			dump_unreclaimable_slab();
	पूर्ण
	अगर (sysctl_oom_dump_tasks)
		dump_tasks(oc);
	अगर (p)
		dump_oom_summary(oc, p);
पूर्ण

/*
 * Number of OOM victims in flight
 */
अटल atomic_t oom_victims = ATOMIC_INIT(0);
अटल DECLARE_WAIT_QUEUE_HEAD(oom_victims_रुको);

अटल bool oom_समाप्तer_disabled __पढ़ो_mostly;

#घोषणा K(x) ((x) << (PAGE_SHIFT-10))

/*
 * task->mm can be शून्य अगर the task is the निकासed group leader.  So to
 * determine whether the task is using a particular mm, we examine all the
 * task's thपढ़ोs: अगर one of those is using this mm then this task was also
 * using it.
 */
bool process_shares_mm(काष्ठा task_काष्ठा *p, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा task_काष्ठा *t;

	क्रम_each_thपढ़ो(p, t) अणु
		काष्ठा mm_काष्ठा *t_mm = READ_ONCE(t->mm);
		अगर (t_mm)
			वापस t_mm == mm;
	पूर्ण
	वापस false;
पूर्ण

#अगर_घोषित CONFIG_MMU
/*
 * OOM Reaper kernel thपढ़ो which tries to reap the memory used by the OOM
 * victim (अगर that is possible) to help the OOM समाप्तer to move on.
 */
अटल काष्ठा task_काष्ठा *oom_reaper_th;
अटल DECLARE_WAIT_QUEUE_HEAD(oom_reaper_रुको);
अटल काष्ठा task_काष्ठा *oom_reaper_list;
अटल DEFINE_SPINLOCK(oom_reaper_lock);

bool __oom_reap_task_mm(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	bool ret = true;

	/*
	 * Tell all users of get_user/copy_from_user etc... that the content
	 * is no दीर्घer stable. No barriers really needed because unmapping
	 * should imply barriers alपढ़ोy and the पढ़ोer would hit a page fault
	 * अगर it stumbled over a reaped memory.
	 */
	set_bit(MMF_UNSTABLE, &mm->flags);

	क्रम (vma = mm->mmap ; vma; vma = vma->vm_next) अणु
		अगर (!can_madv_lru_vma(vma))
			जारी;

		/*
		 * Only anonymous pages have a good chance to be dropped
		 * without additional steps which we cannot afक्रमd as we
		 * are OOM alपढ़ोy.
		 *
		 * We करो not even care about fs backed pages because all
		 * which are reclaimable have alपढ़ोy been reclaimed and
		 * we करो not want to block निकास_mmap by keeping mm ref
		 * count elevated without a good reason.
		 */
		अगर (vma_is_anonymous(vma) || !(vma->vm_flags & VM_SHARED)) अणु
			काष्ठा mmu_notअगरier_range range;
			काष्ठा mmu_gather tlb;

			mmu_notअगरier_range_init(&range, MMU_NOTIFY_UNMAP, 0,
						vma, mm, vma->vm_start,
						vma->vm_end);
			tlb_gather_mmu(&tlb, mm);
			अगर (mmu_notअगरier_invalidate_range_start_nonblock(&range)) अणु
				tlb_finish_mmu(&tlb);
				ret = false;
				जारी;
			पूर्ण
			unmap_page_range(&tlb, vma, range.start, range.end, शून्य);
			mmu_notअगरier_invalidate_range_end(&range);
			tlb_finish_mmu(&tlb);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Reaps the address space of the give task.
 *
 * Returns true on success and false अगर none or part of the address space
 * has been reclaimed and the caller should retry later.
 */
अटल bool oom_reap_task_mm(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm)
अणु
	bool ret = true;

	अगर (!mmap_पढ़ो_trylock(mm)) अणु
		trace_skip_task_reaping(tsk->pid);
		वापस false;
	पूर्ण

	/*
	 * MMF_OOM_SKIP is set by निकास_mmap when the OOM reaper can't
	 * work on the mm anymore. The check क्रम MMF_OOM_SKIP must run
	 * under mmap_lock क्रम पढ़ोing because it serializes against the
	 * mmap_ग_लिखो_lock();mmap_ग_लिखो_unlock() cycle in निकास_mmap().
	 */
	अगर (test_bit(MMF_OOM_SKIP, &mm->flags)) अणु
		trace_skip_task_reaping(tsk->pid);
		जाओ out_unlock;
	पूर्ण

	trace_start_task_reaping(tsk->pid);

	/* failed to reap part of the address space. Try again later */
	ret = __oom_reap_task_mm(mm);
	अगर (!ret)
		जाओ out_finish;

	pr_info("oom_reaper: reaped process %d (%s), now anon-rss:%lukB, file-rss:%lukB, shmem-rss:%lukB\n",
			task_pid_nr(tsk), tsk->comm,
			K(get_mm_counter(mm, MM_ANONPAGES)),
			K(get_mm_counter(mm, MM_खाताPAGES)),
			K(get_mm_counter(mm, MM_SHMEMPAGES)));
out_finish:
	trace_finish_task_reaping(tsk->pid);
out_unlock:
	mmap_पढ़ो_unlock(mm);

	वापस ret;
पूर्ण

#घोषणा MAX_OOM_REAP_RETRIES 10
अटल व्योम oom_reap_task(काष्ठा task_काष्ठा *tsk)
अणु
	पूर्णांक attempts = 0;
	काष्ठा mm_काष्ठा *mm = tsk->संकेत->oom_mm;

	/* Retry the mmap_पढ़ो_trylock(mm) a few बार */
	जबतक (attempts++ < MAX_OOM_REAP_RETRIES && !oom_reap_task_mm(tsk, mm))
		schedule_समयout_idle(HZ/10);

	अगर (attempts <= MAX_OOM_REAP_RETRIES ||
	    test_bit(MMF_OOM_SKIP, &mm->flags))
		जाओ करोne;

	pr_info("oom_reaper: unable to reap pid:%d (%s)\n",
		task_pid_nr(tsk), tsk->comm);
	sched_show_task(tsk);
	debug_show_all_locks();

करोne:
	tsk->oom_reaper_list = शून्य;

	/*
	 * Hide this mm from OOM समाप्तer because it has been either reaped or
	 * somebody can't call mmap_ग_लिखो_unlock(mm).
	 */
	set_bit(MMF_OOM_SKIP, &mm->flags);

	/* Drop a reference taken by wake_oom_reaper */
	put_task_काष्ठा(tsk);
पूर्ण

अटल पूर्णांक oom_reaper(व्योम *unused)
अणु
	जबतक (true) अणु
		काष्ठा task_काष्ठा *tsk = शून्य;

		रुको_event_मुक्तzable(oom_reaper_रुको, oom_reaper_list != शून्य);
		spin_lock(&oom_reaper_lock);
		अगर (oom_reaper_list != शून्य) अणु
			tsk = oom_reaper_list;
			oom_reaper_list = tsk->oom_reaper_list;
		पूर्ण
		spin_unlock(&oom_reaper_lock);

		अगर (tsk)
			oom_reap_task(tsk);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wake_oom_reaper(काष्ठा task_काष्ठा *tsk)
अणु
	/* mm is alपढ़ोy queued? */
	अगर (test_and_set_bit(MMF_OOM_REAP_QUEUED, &tsk->संकेत->oom_mm->flags))
		वापस;

	get_task_काष्ठा(tsk);

	spin_lock(&oom_reaper_lock);
	tsk->oom_reaper_list = oom_reaper_list;
	oom_reaper_list = tsk;
	spin_unlock(&oom_reaper_lock);
	trace_wake_reaper(tsk->pid);
	wake_up(&oom_reaper_रुको);
पूर्ण

अटल पूर्णांक __init oom_init(व्योम)
अणु
	oom_reaper_th = kthपढ़ो_run(oom_reaper, शून्य, "oom_reaper");
	वापस 0;
पूर्ण
subsys_initcall(oom_init)
#अन्यथा
अटल अंतरभूत व्योम wake_oom_reaper(काष्ठा task_काष्ठा *tsk)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_MMU */

/**
 * mark_oom_victim - mark the given task as OOM victim
 * @tsk: task to mark
 *
 * Has to be called with oom_lock held and never after
 * oom has been disabled alपढ़ोy.
 *
 * tsk->mm has to be non शून्य and caller has to guarantee it is stable (either
 * under task_lock or operate on the current).
 */
अटल व्योम mark_oom_victim(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा mm_काष्ठा *mm = tsk->mm;

	WARN_ON(oom_समाप्तer_disabled);
	/* OOM समाप्तer might race with memcg OOM */
	अगर (test_and_set_tsk_thपढ़ो_flag(tsk, TIF_MEMDIE))
		वापस;

	/* oom_mm is bound to the संकेत काष्ठा lअगरe समय. */
	अगर (!cmpxchg(&tsk->संकेत->oom_mm, शून्य, mm)) अणु
		mmgrab(tsk->संकेत->oom_mm);
		set_bit(MMF_OOM_VICTIM, &mm->flags);
	पूर्ण

	/*
	 * Make sure that the task is woken up from unपूर्णांकerruptible sleep
	 * अगर it is frozen because OOM समाप्तer wouldn't be able to मुक्त
	 * any memory and livelock. मुक्तzing_slow_path will tell the मुक्तzer
	 * that TIF_MEMDIE tasks should be ignored.
	 */
	__thaw_task(tsk);
	atomic_inc(&oom_victims);
	trace_mark_victim(tsk->pid);
पूर्ण

/**
 * निकास_oom_victim - note the निकास of an OOM victim
 */
व्योम निकास_oom_victim(व्योम)
अणु
	clear_thपढ़ो_flag(TIF_MEMDIE);

	अगर (!atomic_dec_वापस(&oom_victims))
		wake_up_all(&oom_victims_रुको);
पूर्ण

/**
 * oom_समाप्तer_enable - enable OOM समाप्तer
 */
व्योम oom_समाप्तer_enable(व्योम)
अणु
	oom_समाप्तer_disabled = false;
	pr_info("OOM killer enabled.\n");
पूर्ण

/**
 * oom_समाप्तer_disable - disable OOM समाप्तer
 * @समयout: maximum समयout to रुको क्रम oom victims in jअगरfies
 *
 * Forces all page allocations to fail rather than trigger OOM समाप्तer.
 * Will block and रुको until all OOM victims are समाप्तed or the given
 * समयout expires.
 *
 * The function cannot be called when there are runnable user tasks because
 * the userspace would see unexpected allocation failures as a result. Any
 * new usage of this function should be consulted with MM people.
 *
 * Returns true अगर successful and false अगर the OOM समाप्तer cannot be
 * disabled.
 */
bool oom_समाप्तer_disable(चिन्हित दीर्घ समयout)
अणु
	चिन्हित दीर्घ ret;

	/*
	 * Make sure to not race with an ongoing OOM समाप्तer. Check that the
	 * current is not समाप्तed (possibly due to sharing the victim's memory).
	 */
	अगर (mutex_lock_समाप्तable(&oom_lock))
		वापस false;
	oom_समाप्तer_disabled = true;
	mutex_unlock(&oom_lock);

	ret = रुको_event_पूर्णांकerruptible_समयout(oom_victims_रुको,
			!atomic_पढ़ो(&oom_victims), समयout);
	अगर (ret <= 0) अणु
		oom_समाप्तer_enable();
		वापस false;
	पूर्ण
	pr_info("OOM killer disabled.\n");

	वापस true;
पूर्ण

अटल अंतरभूत bool __task_will_मुक्त_mem(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा संकेत_काष्ठा *sig = task->संकेत;

	/*
	 * A coredumping process may sleep क्रम an extended period in निकास_mm(),
	 * so the oom समाप्तer cannot assume that the process will promptly निकास
	 * and release memory.
	 */
	अगर (sig->flags & SIGNAL_GROUP_COREDUMP)
		वापस false;

	अगर (sig->flags & SIGNAL_GROUP_EXIT)
		वापस true;

	अगर (thपढ़ो_group_empty(task) && (task->flags & PF_EXITING))
		वापस true;

	वापस false;
पूर्ण

/*
 * Checks whether the given task is dying or निकासing and likely to
 * release its address space. This means that all thपढ़ोs and processes
 * sharing the same mm have to be समाप्तed or निकासing.
 * Caller has to make sure that task->mm is stable (hold task_lock or
 * it operates on the current).
 */
अटल bool task_will_मुक्त_mem(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा mm_काष्ठा *mm = task->mm;
	काष्ठा task_काष्ठा *p;
	bool ret = true;

	/*
	 * Skip tasks without mm because it might have passed its निकास_mm and
	 * निकास_oom_victim. oom_reaper could have rescued that but करो not rely
	 * on that क्रम now. We can consider find_lock_task_mm in future.
	 */
	अगर (!mm)
		वापस false;

	अगर (!__task_will_मुक्त_mem(task))
		वापस false;

	/*
	 * This task has alपढ़ोy been drained by the oom reaper so there are
	 * only small chances it will मुक्त some more
	 */
	अगर (test_bit(MMF_OOM_SKIP, &mm->flags))
		वापस false;

	अगर (atomic_पढ़ो(&mm->mm_users) <= 1)
		वापस true;

	/*
	 * Make sure that all tasks which share the mm with the given tasks
	 * are dying as well to make sure that a) nobody pins its mm and
	 * b) the task is also reapable by the oom reaper.
	 */
	rcu_पढ़ो_lock();
	क्रम_each_process(p) अणु
		अगर (!process_shares_mm(p, mm))
			जारी;
		अगर (same_thपढ़ो_group(task, p))
			जारी;
		ret = __task_will_मुक्त_mem(p);
		अगर (!ret)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल व्योम __oom_समाप्त_process(काष्ठा task_काष्ठा *victim, स्थिर अक्षर *message)
अणु
	काष्ठा task_काष्ठा *p;
	काष्ठा mm_काष्ठा *mm;
	bool can_oom_reap = true;

	p = find_lock_task_mm(victim);
	अगर (!p) अणु
		pr_info("%s: OOM victim %d (%s) is already exiting. Skip killing the task\n",
			message, task_pid_nr(victim), victim->comm);
		put_task_काष्ठा(victim);
		वापस;
	पूर्ण अन्यथा अगर (victim != p) अणु
		get_task_काष्ठा(p);
		put_task_काष्ठा(victim);
		victim = p;
	पूर्ण

	/* Get a reference to safely compare mm after task_unlock(victim) */
	mm = victim->mm;
	mmgrab(mm);

	/* Raise event beक्रमe sending संकेत: task reaper must see this */
	count_vm_event(OOM_KILL);
	memcg_memory_event_mm(mm, MEMCG_OOM_KILL);

	/*
	 * We should send SIGKILL beक्रमe granting access to memory reserves
	 * in order to prevent the OOM victim from depleting the memory
	 * reserves from the user space under its control.
	 */
	करो_send_sig_info(SIGKILL, SEND_SIG_PRIV, victim, PIDTYPE_TGID);
	mark_oom_victim(victim);
	pr_err("%s: Killed process %d (%s) total-vm:%lukB, anon-rss:%lukB, file-rss:%lukB, shmem-rss:%lukB, UID:%u pgtables:%lukB oom_score_adj:%hd\n",
		message, task_pid_nr(victim), victim->comm, K(mm->total_vm),
		K(get_mm_counter(mm, MM_ANONPAGES)),
		K(get_mm_counter(mm, MM_खाताPAGES)),
		K(get_mm_counter(mm, MM_SHMEMPAGES)),
		from_kuid(&init_user_ns, task_uid(victim)),
		mm_pgtables_bytes(mm) >> 10, victim->संकेत->oom_score_adj);
	task_unlock(victim);

	/*
	 * Kill all user processes sharing victim->mm in other thपढ़ो groups, अगर
	 * any.  They करोn't get access to memory reserves, though, to aव्योम
	 * depletion of all memory.  This prevents mm->mmap_lock livelock when an
	 * oom समाप्तed thपढ़ो cannot निकास because it requires the semaphore and
	 * its contended by another thपढ़ो trying to allocate memory itself.
	 * That thपढ़ो will now get access to memory reserves since it has a
	 * pending fatal संकेत.
	 */
	rcu_पढ़ो_lock();
	क्रम_each_process(p) अणु
		अगर (!process_shares_mm(p, mm))
			जारी;
		अगर (same_thपढ़ो_group(p, victim))
			जारी;
		अगर (is_global_init(p)) अणु
			can_oom_reap = false;
			set_bit(MMF_OOM_SKIP, &mm->flags);
			pr_info("oom killer %d (%s) has mm pinned by %d (%s)\n",
					task_pid_nr(victim), victim->comm,
					task_pid_nr(p), p->comm);
			जारी;
		पूर्ण
		/*
		 * No kthead_use_mm() user needs to पढ़ो from the userspace so
		 * we are ok to reap it.
		 */
		अगर (unlikely(p->flags & PF_KTHREAD))
			जारी;
		करो_send_sig_info(SIGKILL, SEND_SIG_PRIV, p, PIDTYPE_TGID);
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (can_oom_reap)
		wake_oom_reaper(victim);

	mmdrop(mm);
	put_task_काष्ठा(victim);
पूर्ण
#अघोषित K

/*
 * Kill provided task unless it's secured by setting
 * oom_score_adj to OOM_SCORE_ADJ_MIN.
 */
अटल पूर्णांक oom_समाप्त_memcg_member(काष्ठा task_काष्ठा *task, व्योम *message)
अणु
	अगर (task->संकेत->oom_score_adj != OOM_SCORE_ADJ_MIN &&
	    !is_global_init(task)) अणु
		get_task_काष्ठा(task);
		__oom_समाप्त_process(task, message);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम oom_समाप्त_process(काष्ठा oom_control *oc, स्थिर अक्षर *message)
अणु
	काष्ठा task_काष्ठा *victim = oc->chosen;
	काष्ठा mem_cgroup *oom_group;
	अटल DEFINE_RATELIMIT_STATE(oom_rs, DEFAULT_RATELIMIT_INTERVAL,
					      DEFAULT_RATELIMIT_BURST);

	/*
	 * If the task is alपढ़ोy निकासing, करोn't alarm the sysadmin or समाप्त
	 * its children or thपढ़ोs, just give it access to memory reserves
	 * so it can die quickly
	 */
	task_lock(victim);
	अगर (task_will_मुक्त_mem(victim)) अणु
		mark_oom_victim(victim);
		wake_oom_reaper(victim);
		task_unlock(victim);
		put_task_काष्ठा(victim);
		वापस;
	पूर्ण
	task_unlock(victim);

	अगर (__ratelimit(&oom_rs))
		dump_header(oc, victim);

	/*
	 * Do we need to समाप्त the entire memory cgroup?
	 * Or even one of the ancestor memory cgroups?
	 * Check this out beक्रमe समाप्तing the victim task.
	 */
	oom_group = mem_cgroup_get_oom_group(victim, oc->memcg);

	__oom_समाप्त_process(victim, message);

	/*
	 * If necessary, समाप्त all tasks in the selected memory cgroup.
	 */
	अगर (oom_group) अणु
		mem_cgroup_prपूर्णांक_oom_group(oom_group);
		mem_cgroup_scan_tasks(oom_group, oom_समाप्त_memcg_member,
				      (व्योम *)message);
		mem_cgroup_put(oom_group);
	पूर्ण
पूर्ण

/*
 * Determines whether the kernel must panic because of the panic_on_oom sysctl.
 */
अटल व्योम check_panic_on_oom(काष्ठा oom_control *oc)
अणु
	अगर (likely(!sysctl_panic_on_oom))
		वापस;
	अगर (sysctl_panic_on_oom != 2) अणु
		/*
		 * panic_on_oom == 1 only affects CONSTRAINT_NONE, the kernel
		 * करोes not panic क्रम cpuset, mempolicy, or memcg allocation
		 * failures.
		 */
		अगर (oc->स्थिरraपूर्णांक != CONSTRAINT_NONE)
			वापस;
	पूर्ण
	/* Do not panic क्रम oom समाप्तs triggered by sysrq */
	अगर (is_sysrq_oom(oc))
		वापस;
	dump_header(oc, शून्य);
	panic("Out of memory: %s panic_on_oom is enabled\n",
		sysctl_panic_on_oom == 2 ? "compulsory" : "system-wide");
पूर्ण

अटल BLOCKING_NOTIFIER_HEAD(oom_notअगरy_list);

पूर्णांक रेजिस्टर_oom_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&oom_notअगरy_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_oom_notअगरier);

पूर्णांक unरेजिस्टर_oom_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&oom_notअगरy_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_oom_notअगरier);

/**
 * out_of_memory - समाप्त the "best" process when we run out of memory
 * @oc: poपूर्णांकer to काष्ठा oom_control
 *
 * If we run out of memory, we have the choice between either
 * समाप्तing a अक्रमom task (bad), letting the प्रणाली crash (worse)
 * OR try to be smart about which process to समाप्त. Note that we
 * करोn't have to be perfect here, we just have to be good.
 */
bool out_of_memory(काष्ठा oom_control *oc)
अणु
	अचिन्हित दीर्घ मुक्तd = 0;

	अगर (oom_समाप्तer_disabled)
		वापस false;

	अगर (!is_memcg_oom(oc)) अणु
		blocking_notअगरier_call_chain(&oom_notअगरy_list, 0, &मुक्तd);
		अगर (मुक्तd > 0)
			/* Got some memory back in the last second. */
			वापस true;
	पूर्ण

	/*
	 * If current has a pending SIGKILL or is निकासing, then स्वतःmatically
	 * select it.  The goal is to allow it to allocate so that it may
	 * quickly निकास and मुक्त its memory.
	 */
	अगर (task_will_मुक्त_mem(current)) अणु
		mark_oom_victim(current);
		wake_oom_reaper(current);
		वापस true;
	पूर्ण

	/*
	 * The OOM समाप्तer करोes not compensate क्रम IO-less reclaim.
	 * pagefault_out_of_memory lost its gfp context so we have to
	 * make sure exclude 0 mask - all other users should have at least
	 * ___GFP_सूचीECT_RECLAIM to get here. But mem_cgroup_oom() has to
	 * invoke the OOM समाप्तer even अगर it is a GFP_NOFS allocation.
	 */
	अगर (oc->gfp_mask && !(oc->gfp_mask & __GFP_FS) && !is_memcg_oom(oc))
		वापस true;

	/*
	 * Check अगर there were limitations on the allocation (only relevant क्रम
	 * NUMA and memcg) that may require dअगरferent handling.
	 */
	oc->स्थिरraपूर्णांक = स्थिरrained_alloc(oc);
	अगर (oc->स्थिरraपूर्णांक != CONSTRAINT_MEMORY_POLICY)
		oc->nodemask = शून्य;
	check_panic_on_oom(oc);

	अगर (!is_memcg_oom(oc) && sysctl_oom_समाप्त_allocating_task &&
	    current->mm && !oom_unसमाप्तable_task(current) &&
	    oom_cpuset_eligible(current, oc) &&
	    current->संकेत->oom_score_adj != OOM_SCORE_ADJ_MIN) अणु
		get_task_काष्ठा(current);
		oc->chosen = current;
		oom_समाप्त_process(oc, "Out of memory (oom_kill_allocating_task)");
		वापस true;
	पूर्ण

	select_bad_process(oc);
	/* Found nothing?!?! */
	अगर (!oc->chosen) अणु
		dump_header(oc, शून्य);
		pr_warn("Out of memory and no killable processes...\n");
		/*
		 * If we got here due to an actual allocation at the
		 * प्रणाली level, we cannot survive this and will enter
		 * an endless loop in the allocator. Bail out now.
		 */
		अगर (!is_sysrq_oom(oc) && !is_memcg_oom(oc))
			panic("System is deadlocked on memory\n");
	पूर्ण
	अगर (oc->chosen && oc->chosen != (व्योम *)-1UL)
		oom_समाप्त_process(oc, !is_memcg_oom(oc) ? "Out of memory" :
				 "Memory cgroup out of memory");
	वापस !!oc->chosen;
पूर्ण

/*
 * The pagefault handler calls here because it is out of memory, so समाप्त a
 * memory-hogging task. If oom_lock is held by somebody अन्यथा, a parallel oom
 * समाप्तing is alपढ़ोy in progress so करो nothing.
 */
व्योम pagefault_out_of_memory(व्योम)
अणु
	काष्ठा oom_control oc = अणु
		.zonelist = शून्य,
		.nodemask = शून्य,
		.memcg = शून्य,
		.gfp_mask = 0,
		.order = 0,
	पूर्ण;

	अगर (mem_cgroup_oom_synchronize(true))
		वापस;

	अगर (!mutex_trylock(&oom_lock))
		वापस;
	out_of_memory(&oc);
	mutex_unlock(&oom_lock);
पूर्ण
