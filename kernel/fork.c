<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/kernel/विभाजन.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

/*
 *  'fork.c' contains the help-routines for the 'fork' प्रणाली call
 * (see also entry.S and others).
 * Fork is rather simple, once you get the hang of it, but the memory
 * management can be a bitch. See 'mm/memory.c': 'copy_page_range()'
 */

#समावेश <linux/anon_inodes.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/स्वतःgroup.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/sched/user.h>
#समावेश <linux/sched/numa_balancing.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/rपंचांगutex.h>
#समावेश <linux/init.h>
#समावेश <linux/unistd.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/completion.h>
#समावेश <linux/personality.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/sem.h>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/iocontext.h>
#समावेश <linux/key.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/mman.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/vmacache.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/capability.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/security.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/swap.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/futex.h>
#समावेश <linux/compat.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mount.h>
#समावेश <linux/audit.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/profile.h>
#समावेश <linux/rmap.h>
#समावेश <linux/ksm.h>
#समावेश <linux/acct.h>
#समावेश <linux/userfaultfd_k.h>
#समावेश <linux/tsacct_kern.h>
#समावेश <linux/cn_proc.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/delayacct.h>
#समावेश <linux/taskstats_kern.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/tty.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/magic.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/user-वापस-notअगरier.h>
#समावेश <linux/oom.h>
#समावेश <linux/khugepaged.h>
#समावेश <linux/संकेतfd.h>
#समावेश <linux/uprobes.h>
#समावेश <linux/aपन.स>
#समावेश <linux/compiler.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/kcov.h>
#समावेश <linux/livepatch.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/stackleak.h>
#समावेश <linux/kasan.h>
#समावेश <linux/scs.h>
#समावेश <linux/io_uring.h>
#समावेश <linux/bpf.h>

#समावेश <यंत्र/pgभाग.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश <trace/events/sched.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/task.h>

/*
 * Minimum number of thपढ़ोs to boot the kernel
 */
#घोषणा MIN_THREADS 20

/*
 * Maximum number of thपढ़ोs
 */
#घोषणा MAX_THREADS FUTEX_TID_MASK

/*
 * Protected counters by ग_लिखो_lock_irq(&tasklist_lock)
 */
अचिन्हित दीर्घ total_विभाजनs;	/* Handle normal Linux upबार. */
पूर्णांक nr_thपढ़ोs;			/* The idle thपढ़ोs करो not count.. */

अटल पूर्णांक max_thपढ़ोs;		/* tunable limit on nr_thपढ़ोs */

#घोषणा NAMED_ARRAY_INDEX(x)	[x] = __stringअगरy(x)

अटल स्थिर अक्षर * स्थिर resident_page_types[] = अणु
	NAMED_ARRAY_INDEX(MM_खाताPAGES),
	NAMED_ARRAY_INDEX(MM_ANONPAGES),
	NAMED_ARRAY_INDEX(MM_SWAPENTS),
	NAMED_ARRAY_INDEX(MM_SHMEMPAGES),
पूर्ण;

DEFINE_PER_CPU(अचिन्हित दीर्घ, process_counts) = 0;

__cacheline_aligned DEFINE_RWLOCK(tasklist_lock);  /* outer */

#अगर_घोषित CONFIG_PROVE_RCU
पूर्णांक lockdep_tasklist_lock_is_held(व्योम)
अणु
	वापस lockdep_is_held(&tasklist_lock);
पूर्ण
EXPORT_SYMBOL_GPL(lockdep_tasklist_lock_is_held);
#पूर्ण_अगर /* #अगर_घोषित CONFIG_PROVE_RCU */

पूर्णांक nr_processes(व्योम)
अणु
	पूर्णांक cpu;
	पूर्णांक total = 0;

	क्रम_each_possible_cpu(cpu)
		total += per_cpu(process_counts, cpu);

	वापस total;
पूर्ण

व्योम __weak arch_release_task_काष्ठा(काष्ठा task_काष्ठा *tsk)
अणु
पूर्ण

#अगर_अघोषित CONFIG_ARCH_TASK_STRUCT_ALLOCATOR
अटल काष्ठा kmem_cache *task_काष्ठा_cachep;

अटल अंतरभूत काष्ठा task_काष्ठा *alloc_task_काष्ठा_node(पूर्णांक node)
अणु
	वापस kmem_cache_alloc_node(task_काष्ठा_cachep, GFP_KERNEL, node);
पूर्ण

अटल अंतरभूत व्योम मुक्त_task_काष्ठा(काष्ठा task_काष्ठा *tsk)
अणु
	kmem_cache_मुक्त(task_काष्ठा_cachep, tsk);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित CONFIG_ARCH_THREAD_STACK_ALLOCATOR

/*
 * Allocate pages अगर THREAD_SIZE is >= PAGE_SIZE, otherwise use a
 * kmemcache based allocator.
 */
# अगर THREAD_SIZE >= PAGE_SIZE || defined(CONFIG_VMAP_STACK)

#अगर_घोषित CONFIG_VMAP_STACK
/*
 * vदो_स्मृति() is a bit slow, and calling vमुक्त() enough बार will क्रमce a TLB
 * flush.  Try to minimize the number of calls by caching stacks.
 */
#घोषणा NR_CACHED_STACKS 2
अटल DEFINE_PER_CPU(काष्ठा vm_काष्ठा *, cached_stacks[NR_CACHED_STACKS]);

अटल पूर्णांक मुक्त_vm_stack_cache(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा vm_काष्ठा **cached_vm_stacks = per_cpu_ptr(cached_stacks, cpu);
	पूर्णांक i;

	क्रम (i = 0; i < NR_CACHED_STACKS; i++) अणु
		काष्ठा vm_काष्ठा *vm_stack = cached_vm_stacks[i];

		अगर (!vm_stack)
			जारी;

		vमुक्त(vm_stack->addr);
		cached_vm_stacks[i] = शून्य;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित दीर्घ *alloc_thपढ़ो_stack_node(काष्ठा task_काष्ठा *tsk, पूर्णांक node)
अणु
#अगर_घोषित CONFIG_VMAP_STACK
	व्योम *stack;
	पूर्णांक i;

	क्रम (i = 0; i < NR_CACHED_STACKS; i++) अणु
		काष्ठा vm_काष्ठा *s;

		s = this_cpu_xchg(cached_stacks[i], शून्य);

		अगर (!s)
			जारी;

		/* Mark stack accessible क्रम KASAN. */
		kasan_unpoison_range(s->addr, THREAD_SIZE);

		/* Clear stale poपूर्णांकers from reused stack. */
		स_रखो(s->addr, 0, THREAD_SIZE);

		tsk->stack_vm_area = s;
		tsk->stack = s->addr;
		वापस s->addr;
	पूर्ण

	/*
	 * Allocated stacks are cached and later reused by new thपढ़ोs,
	 * so memcg accounting is perक्रमmed manually on assigning/releasing
	 * stacks to tasks. Drop __GFP_ACCOUNT.
	 */
	stack = __vदो_स्मृति_node_range(THREAD_SIZE, THREAD_ALIGN,
				     VMALLOC_START, VMALLOC_END,
				     THREADINFO_GFP & ~__GFP_ACCOUNT,
				     PAGE_KERNEL,
				     0, node, __builtin_वापस_address(0));

	/*
	 * We can't call find_vm_area() in पूर्णांकerrupt context, and
	 * मुक्त_thपढ़ो_stack() can be called in पूर्णांकerrupt context,
	 * so cache the vm_काष्ठा.
	 */
	अगर (stack) अणु
		tsk->stack_vm_area = find_vm_area(stack);
		tsk->stack = stack;
	पूर्ण
	वापस stack;
#अन्यथा
	काष्ठा page *page = alloc_pages_node(node, THREADINFO_GFP,
					     THREAD_SIZE_ORDER);

	अगर (likely(page)) अणु
		tsk->stack = kasan_reset_tag(page_address(page));
		वापस tsk->stack;
	पूर्ण
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम मुक्त_thपढ़ो_stack(काष्ठा task_काष्ठा *tsk)
अणु
#अगर_घोषित CONFIG_VMAP_STACK
	काष्ठा vm_काष्ठा *vm = task_stack_vm_area(tsk);

	अगर (vm) अणु
		पूर्णांक i;

		क्रम (i = 0; i < THREAD_SIZE / PAGE_SIZE; i++)
			memcg_kmem_unअक्षरge_page(vm->pages[i], 0);

		क्रम (i = 0; i < NR_CACHED_STACKS; i++) अणु
			अगर (this_cpu_cmpxchg(cached_stacks[i],
					शून्य, tsk->stack_vm_area) != शून्य)
				जारी;

			वापस;
		पूर्ण

		vमुक्त_atomic(tsk->stack);
		वापस;
	पूर्ण
#पूर्ण_अगर

	__मुक्त_pages(virt_to_page(tsk->stack), THREAD_SIZE_ORDER);
पूर्ण
# अन्यथा
अटल काष्ठा kmem_cache *thपढ़ो_stack_cache;

अटल अचिन्हित दीर्घ *alloc_thपढ़ो_stack_node(काष्ठा task_काष्ठा *tsk,
						  पूर्णांक node)
अणु
	अचिन्हित दीर्घ *stack;
	stack = kmem_cache_alloc_node(thपढ़ो_stack_cache, THREADINFO_GFP, node);
	stack = kasan_reset_tag(stack);
	tsk->stack = stack;
	वापस stack;
पूर्ण

अटल व्योम मुक्त_thपढ़ो_stack(काष्ठा task_काष्ठा *tsk)
अणु
	kmem_cache_मुक्त(thपढ़ो_stack_cache, tsk->stack);
पूर्ण

व्योम thपढ़ो_stack_cache_init(व्योम)
अणु
	thपढ़ो_stack_cache = kmem_cache_create_usercopy("thread_stack",
					THREAD_SIZE, THREAD_SIZE, 0, 0,
					THREAD_SIZE, शून्य);
	BUG_ON(thपढ़ो_stack_cache == शून्य);
पूर्ण
# endअगर
#पूर्ण_अगर

/* SLAB cache क्रम संकेत_काष्ठा काष्ठाures (tsk->संकेत) */
अटल काष्ठा kmem_cache *संकेत_cachep;

/* SLAB cache क्रम sighand_काष्ठा काष्ठाures (tsk->sighand) */
काष्ठा kmem_cache *sighand_cachep;

/* SLAB cache क्रम files_काष्ठा काष्ठाures (tsk->files) */
काष्ठा kmem_cache *files_cachep;

/* SLAB cache क्रम fs_काष्ठा काष्ठाures (tsk->fs) */
काष्ठा kmem_cache *fs_cachep;

/* SLAB cache क्रम vm_area_काष्ठा काष्ठाures */
अटल काष्ठा kmem_cache *vm_area_cachep;

/* SLAB cache क्रम mm_काष्ठा काष्ठाures (tsk->mm) */
अटल काष्ठा kmem_cache *mm_cachep;

काष्ठा vm_area_काष्ठा *vm_area_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा vm_area_काष्ठा *vma;

	vma = kmem_cache_alloc(vm_area_cachep, GFP_KERNEL);
	अगर (vma)
		vma_init(vma, mm);
	वापस vma;
पूर्ण

काष्ठा vm_area_काष्ठा *vm_area_dup(काष्ठा vm_area_काष्ठा *orig)
अणु
	काष्ठा vm_area_काष्ठा *new = kmem_cache_alloc(vm_area_cachep, GFP_KERNEL);

	अगर (new) अणु
		ASSERT_EXCLUSIVE_WRITER(orig->vm_flags);
		ASSERT_EXCLUSIVE_WRITER(orig->vm_file);
		/*
		 * orig->shared.rb may be modअगरied concurrently, but the clone
		 * will be reinitialized.
		 */
		*new = data_race(*orig);
		INIT_LIST_HEAD(&new->anon_vma_chain);
		new->vm_next = new->vm_prev = शून्य;
	पूर्ण
	वापस new;
पूर्ण

व्योम vm_area_मुक्त(काष्ठा vm_area_काष्ठा *vma)
अणु
	kmem_cache_मुक्त(vm_area_cachep, vma);
पूर्ण

अटल व्योम account_kernel_stack(काष्ठा task_काष्ठा *tsk, पूर्णांक account)
अणु
	व्योम *stack = task_stack_page(tsk);
	काष्ठा vm_काष्ठा *vm = task_stack_vm_area(tsk);

	अगर (vm) अणु
		पूर्णांक i;

		क्रम (i = 0; i < THREAD_SIZE / PAGE_SIZE; i++)
			mod_lruvec_page_state(vm->pages[i], NR_KERNEL_STACK_KB,
					      account * (PAGE_SIZE / 1024));
	पूर्ण अन्यथा अणु
		/* All stack pages are in the same node. */
		mod_lruvec_kmem_state(stack, NR_KERNEL_STACK_KB,
				      account * (THREAD_SIZE / 1024));
	पूर्ण
पूर्ण

अटल पूर्णांक memcg_अक्षरge_kernel_stack(काष्ठा task_काष्ठा *tsk)
अणु
#अगर_घोषित CONFIG_VMAP_STACK
	काष्ठा vm_काष्ठा *vm = task_stack_vm_area(tsk);
	पूर्णांक ret;

	BUILD_BUG_ON(IS_ENABLED(CONFIG_VMAP_STACK) && PAGE_SIZE % 1024 != 0);

	अगर (vm) अणु
		पूर्णांक i;

		BUG_ON(vm->nr_pages != THREAD_SIZE / PAGE_SIZE);

		क्रम (i = 0; i < THREAD_SIZE / PAGE_SIZE; i++) अणु
			/*
			 * If memcg_kmem_अक्षरge_page() fails, page's
			 * memory cgroup poपूर्णांकer is शून्य, and
			 * memcg_kmem_unअक्षरge_page() in मुक्त_thपढ़ो_stack()
			 * will ignore this page.
			 */
			ret = memcg_kmem_अक्षरge_page(vm->pages[i], GFP_KERNEL,
						     0);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम release_task_stack(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (WARN_ON(tsk->state != TASK_DEAD))
		वापस;  /* Better to leak the stack than to मुक्त prematurely */

	account_kernel_stack(tsk, -1);
	मुक्त_thपढ़ो_stack(tsk);
	tsk->stack = शून्य;
#अगर_घोषित CONFIG_VMAP_STACK
	tsk->stack_vm_area = शून्य;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_THREAD_INFO_IN_TASK
व्योम put_task_stack(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (refcount_dec_and_test(&tsk->stack_refcount))
		release_task_stack(tsk);
पूर्ण
#पूर्ण_अगर

व्योम मुक्त_task(काष्ठा task_काष्ठा *tsk)
अणु
	scs_release(tsk);

#अगर_अघोषित CONFIG_THREAD_INFO_IN_TASK
	/*
	 * The task is finally करोne with both the stack and thपढ़ो_info,
	 * so मुक्त both.
	 */
	release_task_stack(tsk);
#अन्यथा
	/*
	 * If the task had a separate stack allocation, it should be gone
	 * by now.
	 */
	WARN_ON_ONCE(refcount_पढ़ो(&tsk->stack_refcount) != 0);
#पूर्ण_अगर
	rt_mutex_debug_task_मुक्त(tsk);
	ftrace_graph_निकास_task(tsk);
	arch_release_task_काष्ठा(tsk);
	अगर (tsk->flags & PF_KTHREAD)
		मुक्त_kthपढ़ो_काष्ठा(tsk);
	मुक्त_task_काष्ठा(tsk);
पूर्ण
EXPORT_SYMBOL(मुक्त_task);

#अगर_घोषित CONFIG_MMU
अटल __latent_entropy पूर्णांक dup_mmap(काष्ठा mm_काष्ठा *mm,
					काष्ठा mm_काष्ठा *oldmm)
अणु
	काष्ठा vm_area_काष्ठा *mpnt, *पंचांगp, *prev, **pprev;
	काष्ठा rb_node **rb_link, *rb_parent;
	पूर्णांक retval;
	अचिन्हित दीर्घ अक्षरge;
	LIST_HEAD(uf);

	uprobe_start_dup_mmap();
	अगर (mmap_ग_लिखो_lock_समाप्तable(oldmm)) अणु
		retval = -EINTR;
		जाओ fail_uprobe_end;
	पूर्ण
	flush_cache_dup_mm(oldmm);
	uprobe_dup_mmap(oldmm, mm);
	/*
	 * Not linked in yet - no deadlock potential:
	 */
	mmap_ग_लिखो_lock_nested(mm, SINGLE_DEPTH_NESTING);

	/* No ordering required: file alपढ़ोy has been exposed. */
	RCU_INIT_POINTER(mm->exe_file, get_mm_exe_file(oldmm));

	mm->total_vm = oldmm->total_vm;
	mm->data_vm = oldmm->data_vm;
	mm->exec_vm = oldmm->exec_vm;
	mm->stack_vm = oldmm->stack_vm;

	rb_link = &mm->mm_rb.rb_node;
	rb_parent = शून्य;
	pprev = &mm->mmap;
	retval = ksm_विभाजन(mm, oldmm);
	अगर (retval)
		जाओ out;
	retval = khugepaged_विभाजन(mm, oldmm);
	अगर (retval)
		जाओ out;

	prev = शून्य;
	क्रम (mpnt = oldmm->mmap; mpnt; mpnt = mpnt->vm_next) अणु
		काष्ठा file *file;

		अगर (mpnt->vm_flags & VM_DONTCOPY) अणु
			vm_stat_account(mm, mpnt->vm_flags, -vma_pages(mpnt));
			जारी;
		पूर्ण
		अक्षरge = 0;
		/*
		 * Don't duplicate many vmas if we've been oom-समाप्तed (क्रम
		 * example)
		 */
		अगर (fatal_संकेत_pending(current)) अणु
			retval = -EINTR;
			जाओ out;
		पूर्ण
		अगर (mpnt->vm_flags & VM_ACCOUNT) अणु
			अचिन्हित दीर्घ len = vma_pages(mpnt);

			अगर (security_vm_enough_memory_mm(oldmm, len)) /* sic */
				जाओ fail_nomem;
			अक्षरge = len;
		पूर्ण
		पंचांगp = vm_area_dup(mpnt);
		अगर (!पंचांगp)
			जाओ fail_nomem;
		retval = vma_dup_policy(mpnt, पंचांगp);
		अगर (retval)
			जाओ fail_nomem_policy;
		पंचांगp->vm_mm = mm;
		retval = dup_userfaultfd(पंचांगp, &uf);
		अगर (retval)
			जाओ fail_nomem_anon_vma_विभाजन;
		अगर (पंचांगp->vm_flags & VM_WIPEONFORK) अणु
			/*
			 * VM_WIPEONFORK माला_लो a clean slate in the child.
			 * Don't prepare anon_vma until fault since we don't
			 * copy page क्रम current vma.
			 */
			पंचांगp->anon_vma = शून्य;
		पूर्ण अन्यथा अगर (anon_vma_विभाजन(पंचांगp, mpnt))
			जाओ fail_nomem_anon_vma_विभाजन;
		पंचांगp->vm_flags &= ~(VM_LOCKED | VM_LOCKONFAULT);
		file = पंचांगp->vm_file;
		अगर (file) अणु
			काष्ठा inode *inode = file_inode(file);
			काष्ठा address_space *mapping = file->f_mapping;

			get_file(file);
			अगर (पंचांगp->vm_flags & VM_DENYWRITE)
				put_ग_लिखो_access(inode);
			i_mmap_lock_ग_लिखो(mapping);
			अगर (पंचांगp->vm_flags & VM_SHARED)
				mapping_allow_writable(mapping);
			flush_dcache_mmap_lock(mapping);
			/* insert पंचांगp पूर्णांकo the share list, just after mpnt */
			vma_पूर्णांकerval_tree_insert_after(पंचांगp, mpnt,
					&mapping->i_mmap);
			flush_dcache_mmap_unlock(mapping);
			i_mmap_unlock_ग_लिखो(mapping);
		पूर्ण

		/*
		 * Clear hugetlb-related page reserves क्रम children. This only
		 * affects MAP_PRIVATE mappings. Faults generated by the child
		 * are not guaranteed to succeed, even अगर पढ़ो-only
		 */
		अगर (is_vm_hugetlb_page(पंचांगp))
			reset_vma_resv_huge_pages(पंचांगp);

		/*
		 * Link in the new vma and copy the page table entries.
		 */
		*pprev = पंचांगp;
		pprev = &पंचांगp->vm_next;
		पंचांगp->vm_prev = prev;
		prev = पंचांगp;

		__vma_link_rb(mm, पंचांगp, rb_link, rb_parent);
		rb_link = &पंचांगp->vm_rb.rb_right;
		rb_parent = &पंचांगp->vm_rb;

		mm->map_count++;
		अगर (!(पंचांगp->vm_flags & VM_WIPEONFORK))
			retval = copy_page_range(पंचांगp, mpnt);

		अगर (पंचांगp->vm_ops && पंचांगp->vm_ops->खोलो)
			पंचांगp->vm_ops->खोलो(पंचांगp);

		अगर (retval)
			जाओ out;
	पूर्ण
	/* a new mm has just been created */
	retval = arch_dup_mmap(oldmm, mm);
out:
	mmap_ग_लिखो_unlock(mm);
	flush_tlb_mm(oldmm);
	mmap_ग_लिखो_unlock(oldmm);
	dup_userfaultfd_complete(&uf);
fail_uprobe_end:
	uprobe_end_dup_mmap();
	वापस retval;
fail_nomem_anon_vma_विभाजन:
	mpol_put(vma_policy(पंचांगp));
fail_nomem_policy:
	vm_area_मुक्त(पंचांगp);
fail_nomem:
	retval = -ENOMEM;
	vm_unacct_memory(अक्षरge);
	जाओ out;
पूर्ण

अटल अंतरभूत पूर्णांक mm_alloc_pgd(काष्ठा mm_काष्ठा *mm)
अणु
	mm->pgd = pgd_alloc(mm);
	अगर (unlikely(!mm->pgd))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mm_मुक्त_pgd(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_मुक्त(mm, mm->pgd);
पूर्ण
#अन्यथा
अटल पूर्णांक dup_mmap(काष्ठा mm_काष्ठा *mm, काष्ठा mm_काष्ठा *oldmm)
अणु
	mmap_ग_लिखो_lock(oldmm);
	RCU_INIT_POINTER(mm->exe_file, get_mm_exe_file(oldmm));
	mmap_ग_लिखो_unlock(oldmm);
	वापस 0;
पूर्ण
#घोषणा mm_alloc_pgd(mm)	(0)
#घोषणा mm_मुक्त_pgd(mm)
#पूर्ण_अगर /* CONFIG_MMU */

अटल व्योम check_mm(काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक i;

	BUILD_BUG_ON_MSG(ARRAY_SIZE(resident_page_types) != NR_MM_COUNTERS,
			 "Please make sure 'struct resident_page_types[]' is updated as well");

	क्रम (i = 0; i < NR_MM_COUNTERS; i++) अणु
		दीर्घ x = atomic_दीर्घ_पढ़ो(&mm->rss_stat.count[i]);

		अगर (unlikely(x))
			pr_alert("BUG: Bad rss-counter state mm:%p type:%s val:%ld\n",
				 mm, resident_page_types[i], x);
	पूर्ण

	अगर (mm_pgtables_bytes(mm))
		pr_alert("BUG: non-zero pgtables_bytes on freeing mm: %ld\n",
				mm_pgtables_bytes(mm));

#अगर defined(CONFIG_TRANSPARENT_HUGEPAGE) && !USE_SPLIT_PMD_PTLOCKS
	VM_BUG_ON_MM(mm->pmd_huge_pte, mm);
#पूर्ण_अगर
पूर्ण

#घोषणा allocate_mm()	(kmem_cache_alloc(mm_cachep, GFP_KERNEL))
#घोषणा मुक्त_mm(mm)	(kmem_cache_मुक्त(mm_cachep, (mm)))

/*
 * Called when the last reference to the mm
 * is dropped: either by a lazy thपढ़ो or by
 * mmput. Free the page directory and the mm.
 */
व्योम __mmdrop(काष्ठा mm_काष्ठा *mm)
अणु
	BUG_ON(mm == &init_mm);
	WARN_ON_ONCE(mm == current->mm);
	WARN_ON_ONCE(mm == current->active_mm);
	mm_मुक्त_pgd(mm);
	destroy_context(mm);
	mmu_notअगरier_subscriptions_destroy(mm);
	check_mm(mm);
	put_user_ns(mm->user_ns);
	मुक्त_mm(mm);
पूर्ण
EXPORT_SYMBOL_GPL(__mmdrop);

अटल व्योम mmdrop_async_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mm_काष्ठा *mm;

	mm = container_of(work, काष्ठा mm_काष्ठा, async_put_work);
	__mmdrop(mm);
पूर्ण

अटल व्योम mmdrop_async(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (unlikely(atomic_dec_and_test(&mm->mm_count))) अणु
		INIT_WORK(&mm->async_put_work, mmdrop_async_fn);
		schedule_work(&mm->async_put_work);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम मुक्त_संकेत_काष्ठा(काष्ठा संकेत_काष्ठा *sig)
अणु
	taskstats_tgid_मुक्त(sig);
	sched_स्वतःgroup_निकास(sig);
	/*
	 * __mmdrop is not safe to call from softirq context on x86 due to
	 * pgd_dtor so postpone it to the async context
	 */
	अगर (sig->oom_mm)
		mmdrop_async(sig->oom_mm);
	kmem_cache_मुक्त(संकेत_cachep, sig);
पूर्ण

अटल अंतरभूत व्योम put_संकेत_काष्ठा(काष्ठा संकेत_काष्ठा *sig)
अणु
	अगर (refcount_dec_and_test(&sig->sigcnt))
		मुक्त_संकेत_काष्ठा(sig);
पूर्ण

व्योम __put_task_काष्ठा(काष्ठा task_काष्ठा *tsk)
अणु
	WARN_ON(!tsk->निकास_state);
	WARN_ON(refcount_पढ़ो(&tsk->usage));
	WARN_ON(tsk == current);

	io_uring_मुक्त(tsk);
	cgroup_मुक्त(tsk);
	task_numa_मुक्त(tsk, true);
	security_task_मुक्त(tsk);
	bpf_task_storage_मुक्त(tsk);
	निकास_creds(tsk);
	delayacct_tsk_मुक्त(tsk);
	put_संकेत_काष्ठा(tsk->संकेत);

	अगर (!profile_hanकरोff_task(tsk))
		मुक्त_task(tsk);
पूर्ण
EXPORT_SYMBOL_GPL(__put_task_काष्ठा);

व्योम __init __weak arch_task_cache_init(व्योम) अणु पूर्ण

/*
 * set_max_thपढ़ोs
 */
अटल व्योम set_max_thपढ़ोs(अचिन्हित पूर्णांक max_thपढ़ोs_suggested)
अणु
	u64 thपढ़ोs;
	अचिन्हित दीर्घ nr_pages = totalram_pages();

	/*
	 * The number of thपढ़ोs shall be limited such that the thपढ़ो
	 * काष्ठाures may only consume a small part of the available memory.
	 */
	अगर (fls64(nr_pages) + fls64(PAGE_SIZE) > 64)
		thपढ़ोs = MAX_THREADS;
	अन्यथा
		thपढ़ोs = भाग64_u64((u64) nr_pages * (u64) PAGE_SIZE,
				    (u64) THREAD_SIZE * 8UL);

	अगर (thपढ़ोs > max_thपढ़ोs_suggested)
		thपढ़ोs = max_thपढ़ोs_suggested;

	max_thपढ़ोs = clamp_t(u64, thपढ़ोs, MIN_THREADS, MAX_THREADS);
पूर्ण

#अगर_घोषित CONFIG_ARCH_WANTS_DYNAMIC_TASK_STRUCT
/* Initialized by the architecture: */
पूर्णांक arch_task_काष्ठा_size __पढ़ो_mostly;
#पूर्ण_अगर

#अगर_अघोषित CONFIG_ARCH_TASK_STRUCT_ALLOCATOR
अटल व्योम task_काष्ठा_whitelist(अचिन्हित दीर्घ *offset, अचिन्हित दीर्घ *size)
अणु
	/* Fetch thपढ़ो_काष्ठा whitelist क्रम the architecture. */
	arch_thपढ़ो_काष्ठा_whitelist(offset, size);

	/*
	 * Handle zero-sized whitelist or empty thपढ़ो_काष्ठा, otherwise
	 * adjust offset to position of thपढ़ो_काष्ठा in task_काष्ठा.
	 */
	अगर (unlikely(*size == 0))
		*offset = 0;
	अन्यथा
		*offset += दुरत्व(काष्ठा task_काष्ठा, thपढ़ो);
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_TASK_STRUCT_ALLOCATOR */

व्योम __init विभाजन_init(व्योम)
अणु
	पूर्णांक i;
#अगर_अघोषित CONFIG_ARCH_TASK_STRUCT_ALLOCATOR
#अगर_अघोषित ARCH_MIN_TASKALIGN
#घोषणा ARCH_MIN_TASKALIGN	0
#पूर्ण_अगर
	पूर्णांक align = max_t(पूर्णांक, L1_CACHE_BYTES, ARCH_MIN_TASKALIGN);
	अचिन्हित दीर्घ useroffset, usersize;

	/* create a slab on which task_काष्ठाs can be allocated */
	task_काष्ठा_whitelist(&useroffset, &usersize);
	task_काष्ठा_cachep = kmem_cache_create_usercopy("task_struct",
			arch_task_काष्ठा_size, align,
			SLAB_PANIC|SLAB_ACCOUNT,
			useroffset, usersize, शून्य);
#पूर्ण_अगर

	/* करो the arch specअगरic task caches init */
	arch_task_cache_init();

	set_max_thपढ़ोs(MAX_THREADS);

	init_task.संकेत->rlim[RLIMIT_NPROC].rlim_cur = max_thपढ़ोs/2;
	init_task.संकेत->rlim[RLIMIT_NPROC].rlim_max = max_thपढ़ोs/2;
	init_task.संकेत->rlim[RLIMIT_SIGPENDING] =
		init_task.संकेत->rlim[RLIMIT_NPROC];

	क्रम (i = 0; i < UCOUNT_COUNTS; i++)
		init_user_ns.ucount_max[i] = max_thपढ़ोs/2;

#अगर_घोषित CONFIG_VMAP_STACK
	cpuhp_setup_state(CPUHP_BP_PREPARE_DYN, "fork:vm_stack_cache",
			  शून्य, मुक्त_vm_stack_cache);
#पूर्ण_अगर

	scs_init();

	lockdep_init_task(&init_task);
	uprobes_init();
पूर्ण

पूर्णांक __weak arch_dup_task_काष्ठा(काष्ठा task_काष्ठा *dst,
					       काष्ठा task_काष्ठा *src)
अणु
	*dst = *src;
	वापस 0;
पूर्ण

व्योम set_task_stack_end_magic(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ *stackend;

	stackend = end_of_stack(tsk);
	*stackend = STACK_END_MAGIC;	/* क्रम overflow detection */
पूर्ण

अटल काष्ठा task_काष्ठा *dup_task_काष्ठा(काष्ठा task_काष्ठा *orig, पूर्णांक node)
अणु
	काष्ठा task_काष्ठा *tsk;
	अचिन्हित दीर्घ *stack;
	काष्ठा vm_काष्ठा *stack_vm_area __maybe_unused;
	पूर्णांक err;

	अगर (node == NUMA_NO_NODE)
		node = tsk_विभाजन_get_node(orig);
	tsk = alloc_task_काष्ठा_node(node);
	अगर (!tsk)
		वापस शून्य;

	stack = alloc_thपढ़ो_stack_node(tsk, node);
	अगर (!stack)
		जाओ मुक्त_tsk;

	अगर (memcg_अक्षरge_kernel_stack(tsk))
		जाओ मुक्त_stack;

	stack_vm_area = task_stack_vm_area(tsk);

	err = arch_dup_task_काष्ठा(tsk, orig);

	/*
	 * arch_dup_task_काष्ठा() clobbers the stack-related fields.  Make
	 * sure they're properly initialized beक्रमe using any stack-related
	 * functions again.
	 */
	tsk->stack = stack;
#अगर_घोषित CONFIG_VMAP_STACK
	tsk->stack_vm_area = stack_vm_area;
#पूर्ण_अगर
#अगर_घोषित CONFIG_THREAD_INFO_IN_TASK
	refcount_set(&tsk->stack_refcount, 1);
#पूर्ण_अगर

	अगर (err)
		जाओ मुक्त_stack;

	err = scs_prepare(tsk, node);
	अगर (err)
		जाओ मुक्त_stack;

#अगर_घोषित CONFIG_SECCOMP
	/*
	 * We must handle setting up seccomp filters once we're under
	 * the sighand lock in हाल orig has changed between now and
	 * then. Until then, filter must be शून्य to aव्योम messing up
	 * the usage counts on the error path calling मुक्त_task.
	 */
	tsk->seccomp.filter = शून्य;
#पूर्ण_अगर

	setup_thपढ़ो_stack(tsk, orig);
	clear_user_वापस_notअगरier(tsk);
	clear_tsk_need_resched(tsk);
	set_task_stack_end_magic(tsk);
	clear_syscall_work_syscall_user_dispatch(tsk);

#अगर_घोषित CONFIG_STACKPROTECTOR
	tsk->stack_canary = get_अक्रमom_canary();
#पूर्ण_अगर
	अगर (orig->cpus_ptr == &orig->cpus_mask)
		tsk->cpus_ptr = &tsk->cpus_mask;

	/*
	 * One क्रम the user space visible state that goes away when reaped.
	 * One क्रम the scheduler.
	 */
	refcount_set(&tsk->rcu_users, 2);
	/* One क्रम the rcu users */
	refcount_set(&tsk->usage, 1);
#अगर_घोषित CONFIG_BLK_DEV_IO_TRACE
	tsk->btrace_seq = 0;
#पूर्ण_अगर
	tsk->splice_pipe = शून्य;
	tsk->task_frag.page = शून्य;
	tsk->wake_q.next = शून्य;
	tsk->pf_io_worker = शून्य;

	account_kernel_stack(tsk, 1);

	kcov_task_init(tsk);
	kmap_local_विभाजन(tsk);

#अगर_घोषित CONFIG_FAULT_INJECTION
	tsk->fail_nth = 0;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BLK_CGROUP
	tsk->throttle_queue = शून्य;
	tsk->use_memdelay = 0;
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEMCG
	tsk->active_memcg = शून्य;
#पूर्ण_अगर
	वापस tsk;

मुक्त_stack:
	मुक्त_thपढ़ो_stack(tsk);
मुक्त_tsk:
	मुक्त_task_काष्ठा(tsk);
	वापस शून्य;
पूर्ण

__cacheline_aligned_in_smp DEFINE_SPINLOCK(mmlist_lock);

अटल अचिन्हित दीर्घ शेष_dump_filter = MMF_DUMP_FILTER_DEFAULT;

अटल पूर्णांक __init coredump_filter_setup(अक्षर *s)
अणु
	शेष_dump_filter =
		(simple_म_से_अदीर्घ(s, शून्य, 0) << MMF_DUMP_FILTER_SHIFT) &
		MMF_DUMP_FILTER_MASK;
	वापस 1;
पूर्ण

__setup("coredump_filter=", coredump_filter_setup);

#समावेश <linux/init_task.h>

अटल व्योम mm_init_aio(काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_AIO
	spin_lock_init(&mm->ioctx_lock);
	mm->ioctx_table = शून्य;
#पूर्ण_अगर
पूर्ण

अटल __always_अंतरभूत व्योम mm_clear_owner(काष्ठा mm_काष्ठा *mm,
					   काष्ठा task_काष्ठा *p)
अणु
#अगर_घोषित CONFIG_MEMCG
	अगर (mm->owner == p)
		WRITE_ONCE(mm->owner, शून्य);
#पूर्ण_अगर
पूर्ण

अटल व्योम mm_init_owner(काष्ठा mm_काष्ठा *mm, काष्ठा task_काष्ठा *p)
अणु
#अगर_घोषित CONFIG_MEMCG
	mm->owner = p;
#पूर्ण_अगर
पूर्ण

अटल व्योम mm_init_pasid(काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_IOMMU_SUPPORT
	mm->pasid = INIT_PASID;
#पूर्ण_अगर
पूर्ण

अटल व्योम mm_init_uprobes_state(काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_UPROBES
	mm->uprobes_state.xol_area = शून्य;
#पूर्ण_अगर
पूर्ण

अटल काष्ठा mm_काष्ठा *mm_init(काष्ठा mm_काष्ठा *mm, काष्ठा task_काष्ठा *p,
	काष्ठा user_namespace *user_ns)
अणु
	mm->mmap = शून्य;
	mm->mm_rb = RB_ROOT;
	mm->vmacache_seqnum = 0;
	atomic_set(&mm->mm_users, 1);
	atomic_set(&mm->mm_count, 1);
	seqcount_init(&mm->ग_लिखो_protect_seq);
	mmap_init_lock(mm);
	INIT_LIST_HEAD(&mm->mmlist);
	mm->core_state = शून्य;
	mm_pgtables_bytes_init(mm);
	mm->map_count = 0;
	mm->locked_vm = 0;
	atomic_set(&mm->has_pinned, 0);
	atomic64_set(&mm->pinned_vm, 0);
	स_रखो(&mm->rss_stat, 0, माप(mm->rss_stat));
	spin_lock_init(&mm->page_table_lock);
	spin_lock_init(&mm->arg_lock);
	mm_init_cpumask(mm);
	mm_init_aio(mm);
	mm_init_owner(mm, p);
	mm_init_pasid(mm);
	RCU_INIT_POINTER(mm->exe_file, शून्य);
	mmu_notअगरier_subscriptions_init(mm);
	init_tlb_flush_pending(mm);
#अगर defined(CONFIG_TRANSPARENT_HUGEPAGE) && !USE_SPLIT_PMD_PTLOCKS
	mm->pmd_huge_pte = शून्य;
#पूर्ण_अगर
	mm_init_uprobes_state(mm);

	अगर (current->mm) अणु
		mm->flags = current->mm->flags & MMF_INIT_MASK;
		mm->def_flags = current->mm->def_flags & VM_INIT_DEF_MASK;
	पूर्ण अन्यथा अणु
		mm->flags = शेष_dump_filter;
		mm->def_flags = 0;
	पूर्ण

	अगर (mm_alloc_pgd(mm))
		जाओ fail_nopgd;

	अगर (init_new_context(p, mm))
		जाओ fail_nocontext;

	mm->user_ns = get_user_ns(user_ns);
	वापस mm;

fail_nocontext:
	mm_मुक्त_pgd(mm);
fail_nopgd:
	मुक्त_mm(mm);
	वापस शून्य;
पूर्ण

/*
 * Allocate and initialize an mm_काष्ठा.
 */
काष्ठा mm_काष्ठा *mm_alloc(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm;

	mm = allocate_mm();
	अगर (!mm)
		वापस शून्य;

	स_रखो(mm, 0, माप(*mm));
	वापस mm_init(mm, current, current_user_ns());
पूर्ण

अटल अंतरभूत व्योम __mmput(काष्ठा mm_काष्ठा *mm)
अणु
	VM_BUG_ON(atomic_पढ़ो(&mm->mm_users));

	uprobe_clear_state(mm);
	निकास_aio(mm);
	ksm_निकास(mm);
	khugepaged_निकास(mm); /* must run beक्रमe निकास_mmap */
	निकास_mmap(mm);
	mm_put_huge_zero_page(mm);
	set_mm_exe_file(mm, शून्य);
	अगर (!list_empty(&mm->mmlist)) अणु
		spin_lock(&mmlist_lock);
		list_del(&mm->mmlist);
		spin_unlock(&mmlist_lock);
	पूर्ण
	अगर (mm->binfmt)
		module_put(mm->binfmt->module);
	mmdrop(mm);
पूर्ण

/*
 * Decrement the use count and release all resources क्रम an mm.
 */
व्योम mmput(काष्ठा mm_काष्ठा *mm)
अणु
	might_sleep();

	अगर (atomic_dec_and_test(&mm->mm_users))
		__mmput(mm);
पूर्ण
EXPORT_SYMBOL_GPL(mmput);

#अगर_घोषित CONFIG_MMU
अटल व्योम mmput_async_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mm_काष्ठा *mm = container_of(work, काष्ठा mm_काष्ठा,
					    async_put_work);

	__mmput(mm);
पूर्ण

व्योम mmput_async(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (atomic_dec_and_test(&mm->mm_users)) अणु
		INIT_WORK(&mm->async_put_work, mmput_async_fn);
		schedule_work(&mm->async_put_work);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/**
 * set_mm_exe_file - change a reference to the mm's executable file
 *
 * This changes mm's executable file (shown as symlink /proc/[pid]/exe).
 *
 * Main users are mmput() and sys_execve(). Callers prevent concurrent
 * invocations: in mmput() nobody alive left, in execve task is single
 * thपढ़ोed. sys_prctl(PR_SET_MM_MAP/EXE_खाता) also needs to set the
 * mm->exe_file, but करोes so without using set_mm_exe_file() in order
 * to aव्योम the need क्रम any locks.
 */
व्योम set_mm_exe_file(काष्ठा mm_काष्ठा *mm, काष्ठा file *new_exe_file)
अणु
	काष्ठा file *old_exe_file;

	/*
	 * It is safe to dereference the exe_file without RCU as
	 * this function is only called अगर nobody अन्यथा can access
	 * this mm -- see comment above क्रम justअगरication.
	 */
	old_exe_file = rcu_dereference_raw(mm->exe_file);

	अगर (new_exe_file)
		get_file(new_exe_file);
	rcu_assign_poपूर्णांकer(mm->exe_file, new_exe_file);
	अगर (old_exe_file)
		fput(old_exe_file);
पूर्ण

/**
 * get_mm_exe_file - acquire a reference to the mm's executable file
 *
 * Returns %शून्य अगर mm has no associated executable file.
 * User must release file via fput().
 */
काष्ठा file *get_mm_exe_file(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा file *exe_file;

	rcu_पढ़ो_lock();
	exe_file = rcu_dereference(mm->exe_file);
	अगर (exe_file && !get_file_rcu(exe_file))
		exe_file = शून्य;
	rcu_पढ़ो_unlock();
	वापस exe_file;
पूर्ण
EXPORT_SYMBOL(get_mm_exe_file);

/**
 * get_task_exe_file - acquire a reference to the task's executable file
 *
 * Returns %शून्य अगर task's mm (अगर any) has no associated executable file or
 * this is a kernel thपढ़ो with borrowed mm (see the comment above get_task_mm).
 * User must release file via fput().
 */
काष्ठा file *get_task_exe_file(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा file *exe_file = शून्य;
	काष्ठा mm_काष्ठा *mm;

	task_lock(task);
	mm = task->mm;
	अगर (mm) अणु
		अगर (!(task->flags & PF_KTHREAD))
			exe_file = get_mm_exe_file(mm);
	पूर्ण
	task_unlock(task);
	वापस exe_file;
पूर्ण
EXPORT_SYMBOL(get_task_exe_file);

/**
 * get_task_mm - acquire a reference to the task's mm
 *
 * Returns %शून्य अगर the task has no mm.  Checks PF_KTHREAD (meaning
 * this kernel workthपढ़ो has transiently aकरोpted a user mm with use_mm,
 * to करो its AIO) is not set and अगर so वापसs a reference to it, after
 * bumping up the use count.  User must release the mm via mmput()
 * after use.  Typically used by /proc and ptrace.
 */
काष्ठा mm_काष्ठा *get_task_mm(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा mm_काष्ठा *mm;

	task_lock(task);
	mm = task->mm;
	अगर (mm) अणु
		अगर (task->flags & PF_KTHREAD)
			mm = शून्य;
		अन्यथा
			mmget(mm);
	पूर्ण
	task_unlock(task);
	वापस mm;
पूर्ण
EXPORT_SYMBOL_GPL(get_task_mm);

काष्ठा mm_काष्ठा *mm_access(काष्ठा task_काष्ठा *task, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा mm_काष्ठा *mm;
	पूर्णांक err;

	err =  करोwn_पढ़ो_समाप्तable(&task->संकेत->exec_update_lock);
	अगर (err)
		वापस ERR_PTR(err);

	mm = get_task_mm(task);
	अगर (mm && mm != current->mm &&
			!ptrace_may_access(task, mode)) अणु
		mmput(mm);
		mm = ERR_PTR(-EACCES);
	पूर्ण
	up_पढ़ो(&task->संकेत->exec_update_lock);

	वापस mm;
पूर्ण

अटल व्योम complete_vविभाजन_करोne(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा completion *vविभाजन;

	task_lock(tsk);
	vविभाजन = tsk->vविभाजन_करोne;
	अगर (likely(vविभाजन)) अणु
		tsk->vविभाजन_करोne = शून्य;
		complete(vविभाजन);
	पूर्ण
	task_unlock(tsk);
पूर्ण

अटल पूर्णांक रुको_क्रम_vविभाजन_करोne(काष्ठा task_काष्ठा *child,
				काष्ठा completion *vविभाजन)
अणु
	पूर्णांक समाप्तed;

	मुक्तzer_करो_not_count();
	cgroup_enter_frozen();
	समाप्तed = रुको_क्रम_completion_समाप्तable(vविभाजन);
	cgroup_leave_frozen(false);
	मुक्तzer_count();

	अगर (समाप्तed) अणु
		task_lock(child);
		child->vविभाजन_करोne = शून्य;
		task_unlock(child);
	पूर्ण

	put_task_काष्ठा(child);
	वापस समाप्तed;
पूर्ण

/* Please note the dअगरferences between mmput and mm_release.
 * mmput is called whenever we stop holding onto a mm_काष्ठा,
 * error success whatever.
 *
 * mm_release is called after a mm_काष्ठा has been हटाओd
 * from the current process.
 *
 * This dअगरference is important क्रम error handling, when we
 * only half set up a mm_काष्ठा क्रम a new process and need to restore
 * the old one.  Because we mmput the new mm_काष्ठा beक्रमe
 * restoring the old one. . .
 * Eric Biederman 10 January 1998
 */
अटल व्योम mm_release(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm)
अणु
	uprobe_मुक्त_utask(tsk);

	/* Get rid of any cached रेजिस्टर state */
	deactivate_mm(tsk, mm);

	/*
	 * Signal userspace अगर we're not निकासing with a core dump
	 * because we want to leave the value पूर्णांकact क्रम debugging
	 * purposes.
	 */
	अगर (tsk->clear_child_tid) अणु
		अगर (!(tsk->संकेत->flags & SIGNAL_GROUP_COREDUMP) &&
		    atomic_पढ़ो(&mm->mm_users) > 1) अणु
			/*
			 * We करोn't check the error code - अगर userspace has
			 * not set up a proper poपूर्णांकer then tough luck.
			 */
			put_user(0, tsk->clear_child_tid);
			करो_futex(tsk->clear_child_tid, FUTEX_WAKE,
					1, शून्य, शून्य, 0, 0);
		पूर्ण
		tsk->clear_child_tid = शून्य;
	पूर्ण

	/*
	 * All करोne, finally we can wake up parent and वापस this mm to him.
	 * Also kthपढ़ो_stop() uses this completion क्रम synchronization.
	 */
	अगर (tsk->vविभाजन_करोne)
		complete_vविभाजन_करोne(tsk);
पूर्ण

व्योम निकास_mm_release(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm)
अणु
	futex_निकास_release(tsk);
	mm_release(tsk, mm);
पूर्ण

व्योम exec_mm_release(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm)
अणु
	futex_exec_release(tsk);
	mm_release(tsk, mm);
पूर्ण

/**
 * dup_mm() - duplicates an existing mm काष्ठाure
 * @tsk: the task_काष्ठा with which the new mm will be associated.
 * @oldmm: the mm to duplicate.
 *
 * Allocates a new mm काष्ठाure and duplicates the provided @oldmm काष्ठाure
 * content पूर्णांकo it.
 *
 * Return: the duplicated mm or शून्य on failure.
 */
अटल काष्ठा mm_काष्ठा *dup_mm(काष्ठा task_काष्ठा *tsk,
				काष्ठा mm_काष्ठा *oldmm)
अणु
	काष्ठा mm_काष्ठा *mm;
	पूर्णांक err;

	mm = allocate_mm();
	अगर (!mm)
		जाओ fail_nomem;

	स_नकल(mm, oldmm, माप(*mm));

	अगर (!mm_init(mm, tsk, mm->user_ns))
		जाओ fail_nomem;

	err = dup_mmap(mm, oldmm);
	अगर (err)
		जाओ मुक्त_pt;

	mm->hiwater_rss = get_mm_rss(mm);
	mm->hiwater_vm = mm->total_vm;

	अगर (mm->binfmt && !try_module_get(mm->binfmt->module))
		जाओ मुक्त_pt;

	वापस mm;

मुक्त_pt:
	/* करोn't put binfmt in mmput, we haven't got module yet */
	mm->binfmt = शून्य;
	mm_init_owner(mm, शून्य);
	mmput(mm);

fail_nomem:
	वापस शून्य;
पूर्ण

अटल पूर्णांक copy_mm(अचिन्हित दीर्घ clone_flags, काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा mm_काष्ठा *mm, *oldmm;

	tsk->min_flt = tsk->maj_flt = 0;
	tsk->nvcsw = tsk->nivcsw = 0;
#अगर_घोषित CONFIG_DETECT_HUNG_TASK
	tsk->last_चयन_count = tsk->nvcsw + tsk->nivcsw;
	tsk->last_चयन_समय = 0;
#पूर्ण_अगर

	tsk->mm = शून्य;
	tsk->active_mm = शून्य;

	/*
	 * Are we cloning a kernel thपढ़ो?
	 *
	 * We need to steal a active VM क्रम that..
	 */
	oldmm = current->mm;
	अगर (!oldmm)
		वापस 0;

	/* initialize the new vmacache entries */
	vmacache_flush(tsk);

	अगर (clone_flags & CLONE_VM) अणु
		mmget(oldmm);
		mm = oldmm;
	पूर्ण अन्यथा अणु
		mm = dup_mm(tsk, current->mm);
		अगर (!mm)
			वापस -ENOMEM;
	पूर्ण

	tsk->mm = mm;
	tsk->active_mm = mm;
	वापस 0;
पूर्ण

अटल पूर्णांक copy_fs(अचिन्हित दीर्घ clone_flags, काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा fs_काष्ठा *fs = current->fs;
	अगर (clone_flags & CLONE_FS) अणु
		/* tsk->fs is alपढ़ोy what we want */
		spin_lock(&fs->lock);
		अगर (fs->in_exec) अणु
			spin_unlock(&fs->lock);
			वापस -EAGAIN;
		पूर्ण
		fs->users++;
		spin_unlock(&fs->lock);
		वापस 0;
	पूर्ण
	tsk->fs = copy_fs_काष्ठा(fs);
	अगर (!tsk->fs)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक copy_files(अचिन्हित दीर्घ clone_flags, काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा files_काष्ठा *oldf, *newf;
	पूर्णांक error = 0;

	/*
	 * A background process may not have any files ...
	 */
	oldf = current->files;
	अगर (!oldf)
		जाओ out;

	अगर (clone_flags & CLONE_खाताS) अणु
		atomic_inc(&oldf->count);
		जाओ out;
	पूर्ण

	newf = dup_fd(oldf, NR_OPEN_MAX, &error);
	अगर (!newf)
		जाओ out;

	tsk->files = newf;
	error = 0;
out:
	वापस error;
पूर्ण

अटल पूर्णांक copy_io(अचिन्हित दीर्घ clone_flags, काष्ठा task_काष्ठा *tsk)
अणु
#अगर_घोषित CONFIG_BLOCK
	काष्ठा io_context *ioc = current->io_context;
	काष्ठा io_context *new_ioc;

	अगर (!ioc)
		वापस 0;
	/*
	 * Share io context with parent, अगर CLONE_IO is set
	 */
	अगर (clone_flags & CLONE_IO) अणु
		ioc_task_link(ioc);
		tsk->io_context = ioc;
	पूर्ण अन्यथा अगर (ioprio_valid(ioc->ioprio)) अणु
		new_ioc = get_task_io_context(tsk, GFP_KERNEL, NUMA_NO_NODE);
		अगर (unlikely(!new_ioc))
			वापस -ENOMEM;

		new_ioc->ioprio = ioc->ioprio;
		put_io_context(new_ioc);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक copy_sighand(अचिन्हित दीर्घ clone_flags, काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा sighand_काष्ठा *sig;

	अगर (clone_flags & CLONE_SIGHAND) अणु
		refcount_inc(&current->sighand->count);
		वापस 0;
	पूर्ण
	sig = kmem_cache_alloc(sighand_cachep, GFP_KERNEL);
	RCU_INIT_POINTER(tsk->sighand, sig);
	अगर (!sig)
		वापस -ENOMEM;

	refcount_set(&sig->count, 1);
	spin_lock_irq(&current->sighand->siglock);
	स_नकल(sig->action, current->sighand->action, माप(sig->action));
	spin_unlock_irq(&current->sighand->siglock);

	/* Reset all संकेत handler not set to संक_छोड़ो to संक_पूर्व. */
	अगर (clone_flags & CLONE_CLEAR_SIGHAND)
		flush_संकेत_handlers(tsk, 0);

	वापस 0;
पूर्ण

व्योम __cleanup_sighand(काष्ठा sighand_काष्ठा *sighand)
अणु
	अगर (refcount_dec_and_test(&sighand->count)) अणु
		संकेतfd_cleanup(sighand);
		/*
		 * sighand_cachep is SLAB_TYPESAFE_BY_RCU so we can मुक्त it
		 * without an RCU grace period, see __lock_task_sighand().
		 */
		kmem_cache_मुक्त(sighand_cachep, sighand);
	पूर्ण
पूर्ण

/*
 * Initialize POSIX समयr handling क्रम a thपढ़ो group.
 */
अटल व्योम posix_cpu_समयrs_init_group(काष्ठा संकेत_काष्ठा *sig)
अणु
	काष्ठा posix_cpuसमयrs *pct = &sig->posix_cpuसमयrs;
	अचिन्हित दीर्घ cpu_limit;

	cpu_limit = READ_ONCE(sig->rlim[RLIMIT_CPU].rlim_cur);
	posix_cpuसमयrs_group_init(pct, cpu_limit);
पूर्ण

अटल पूर्णांक copy_संकेत(अचिन्हित दीर्घ clone_flags, काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा संकेत_काष्ठा *sig;

	अगर (clone_flags & CLONE_THREAD)
		वापस 0;

	sig = kmem_cache_zalloc(संकेत_cachep, GFP_KERNEL);
	tsk->संकेत = sig;
	अगर (!sig)
		वापस -ENOMEM;

	sig->nr_thपढ़ोs = 1;
	atomic_set(&sig->live, 1);
	refcount_set(&sig->sigcnt, 1);

	/* list_add(thपढ़ो_node, thपढ़ो_head) without INIT_LIST_HEAD() */
	sig->thपढ़ो_head = (काष्ठा list_head)LIST_HEAD_INIT(tsk->thपढ़ो_node);
	tsk->thपढ़ो_node = (काष्ठा list_head)LIST_HEAD_INIT(sig->thपढ़ो_head);

	init_रुकोqueue_head(&sig->रुको_chldनिकास);
	sig->curr_target = tsk;
	init_संक_बाकी(&sig->shared_pending);
	INIT_HLIST_HEAD(&sig->multiprocess);
	seqlock_init(&sig->stats_lock);
	prev_cpuसमय_init(&sig->prev_cpuसमय);

#अगर_घोषित CONFIG_POSIX_TIMERS
	INIT_LIST_HEAD(&sig->posix_समयrs);
	hrसमयr_init(&sig->real_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	sig->real_समयr.function = it_real_fn;
#पूर्ण_अगर

	task_lock(current->group_leader);
	स_नकल(sig->rlim, current->संकेत->rlim, माप sig->rlim);
	task_unlock(current->group_leader);

	posix_cpu_समयrs_init_group(sig);

	tty_audit_विभाजन(sig);
	sched_स्वतःgroup_विभाजन(sig);

	sig->oom_score_adj = current->संकेत->oom_score_adj;
	sig->oom_score_adj_min = current->संकेत->oom_score_adj_min;

	mutex_init(&sig->cred_guard_mutex);
	init_rwsem(&sig->exec_update_lock);

	वापस 0;
पूर्ण

अटल व्योम copy_seccomp(काष्ठा task_काष्ठा *p)
अणु
#अगर_घोषित CONFIG_SECCOMP
	/*
	 * Must be called with sighand->lock held, which is common to
	 * all thपढ़ोs in the group. Holding cred_guard_mutex is not
	 * needed because this new task is not yet running and cannot
	 * be racing exec.
	 */
	निश्चित_spin_locked(&current->sighand->siglock);

	/* Ref-count the new filter user, and assign it. */
	get_seccomp_filter(current);
	p->seccomp = current->seccomp;

	/*
	 * Explicitly enable no_new_privs here in हाल it got set
	 * between the task_काष्ठा being duplicated and holding the
	 * sighand lock. The seccomp state and nnp must be in sync.
	 */
	अगर (task_no_new_privs(current))
		task_set_no_new_privs(p);

	/*
	 * If the parent gained a seccomp mode after copying thपढ़ो
	 * flags and between beक्रमe we held the sighand lock, we have
	 * to manually enable the seccomp thपढ़ो flag here.
	 */
	अगर (p->seccomp.mode != SECCOMP_MODE_DISABLED)
		set_task_syscall_work(p, SECCOMP);
#पूर्ण_अगर
पूर्ण

SYSCALL_DEFINE1(set_tid_address, पूर्णांक __user *, tidptr)
अणु
	current->clear_child_tid = tidptr;

	वापस task_pid_vnr(current);
पूर्ण

अटल व्योम rt_mutex_init_task(काष्ठा task_काष्ठा *p)
अणु
	raw_spin_lock_init(&p->pi_lock);
#अगर_घोषित CONFIG_RT_MUTEXES
	p->pi_रुकोers = RB_ROOT_CACHED;
	p->pi_top_task = शून्य;
	p->pi_blocked_on = शून्य;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम init_task_pid_links(काष्ठा task_काष्ठा *task)
अणु
	क्रमागत pid_type type;

	क्रम (type = PIDTYPE_PID; type < PIDTYPE_MAX; ++type)
		INIT_HLIST_NODE(&task->pid_links[type]);
पूर्ण

अटल अंतरभूत व्योम
init_task_pid(काष्ठा task_काष्ठा *task, क्रमागत pid_type type, काष्ठा pid *pid)
अणु
	अगर (type == PIDTYPE_PID)
		task->thपढ़ो_pid = pid;
	अन्यथा
		task->संकेत->pids[type] = pid;
पूर्ण

अटल अंतरभूत व्योम rcu_copy_process(काष्ठा task_काष्ठा *p)
अणु
#अगर_घोषित CONFIG_PREEMPT_RCU
	p->rcu_पढ़ो_lock_nesting = 0;
	p->rcu_पढ़ो_unlock_special.s = 0;
	p->rcu_blocked_node = शून्य;
	INIT_LIST_HEAD(&p->rcu_node_entry);
#पूर्ण_अगर /* #अगर_घोषित CONFIG_PREEMPT_RCU */
#अगर_घोषित CONFIG_TASKS_RCU
	p->rcu_tasks_holकरोut = false;
	INIT_LIST_HEAD(&p->rcu_tasks_holकरोut_list);
	p->rcu_tasks_idle_cpu = -1;
#पूर्ण_अगर /* #अगर_घोषित CONFIG_TASKS_RCU */
#अगर_घोषित CONFIG_TASKS_TRACE_RCU
	p->trc_पढ़ोer_nesting = 0;
	p->trc_पढ़ोer_special.s = 0;
	INIT_LIST_HEAD(&p->trc_holकरोut_list);
#पूर्ण_अगर /* #अगर_घोषित CONFIG_TASKS_TRACE_RCU */
पूर्ण

काष्ठा pid *pidfd_pid(स्थिर काष्ठा file *file)
अणु
	अगर (file->f_op == &pidfd_fops)
		वापस file->निजी_data;

	वापस ERR_PTR(-EBADF);
पूर्ण

अटल पूर्णांक pidfd_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा pid *pid = file->निजी_data;

	file->निजी_data = शून्य;
	put_pid(pid);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
/**
 * pidfd_show_fdinfo - prपूर्णांक inक्रमmation about a pidfd
 * @m: proc fdinfo file
 * @f: file referencing a pidfd
 *
 * Pid:
 * This function will prपूर्णांक the pid that a given pidfd refers to in the
 * pid namespace of the procfs instance.
 * If the pid namespace of the process is not a descendant of the pid
 * namespace of the procfs instance 0 will be shown as its pid. This is
 * similar to calling getppid() on a process whose parent is outside of
 * its pid namespace.
 *
 * NSpid:
 * If pid namespaces are supported then this function will also prपूर्णांक
 * the pid of a given pidfd refers to क्रम all descendant pid namespaces
 * starting from the current pid namespace of the instance, i.e. the
 * Pid field and the first entry in the NSpid field will be identical.
 * If the pid namespace of the process is not a descendant of the pid
 * namespace of the procfs instance 0 will be shown as its first NSpid
 * entry and no others will be shown.
 * Note that this dअगरfers from the Pid and NSpid fields in
 * /proc/<pid>/status where Pid and NSpid are always shown relative to
 * the  pid namespace of the procfs instance. The dअगरference becomes
 * obvious when sending around a pidfd between pid namespaces from a
 * dअगरferent branch of the tree, i.e. where no ancestral relation is
 * present between the pid namespaces:
 * - create two new pid namespaces ns1 and ns2 in the initial pid
 *   namespace (also take care to create new mount namespaces in the
 *   new pid namespace and mount procfs)
 * - create a process with a pidfd in ns1
 * - send pidfd from ns1 to ns2
 * - पढ़ो /proc/self/fdinfo/<pidfd> and observe that both Pid and NSpid
 *   have exactly one entry, which is 0
 */
अटल व्योम pidfd_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *f)
अणु
	काष्ठा pid *pid = f->निजी_data;
	काष्ठा pid_namespace *ns;
	pid_t nr = -1;

	अगर (likely(pid_has_task(pid, PIDTYPE_PID))) अणु
		ns = proc_pid_ns(file_inode(m->file)->i_sb);
		nr = pid_nr_ns(pid, ns);
	पूर्ण

	seq_put_decimal_ll(m, "Pid:\t", nr);

#अगर_घोषित CONFIG_PID_NS
	seq_put_decimal_ll(m, "\nNSpid:\t", nr);
	अगर (nr > 0) अणु
		पूर्णांक i;

		/* If nr is non-zero it means that 'pid' is valid and that
		 * ns, i.e. the pid namespace associated with the procfs
		 * instance, is in the pid namespace hierarchy of pid.
		 * Start at one below the alपढ़ोy prपूर्णांकed level.
		 */
		क्रम (i = ns->level + 1; i <= pid->level; i++)
			seq_put_decimal_ll(m, "\t", pid->numbers[i].nr);
	पूर्ण
#पूर्ण_अगर
	seq_अ_दो(m, '\n');
पूर्ण
#पूर्ण_अगर

/*
 * Poll support क्रम process निकास notअगरication.
 */
अटल __poll_t pidfd_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *pts)
अणु
	काष्ठा pid *pid = file->निजी_data;
	__poll_t poll_flags = 0;

	poll_रुको(file, &pid->रुको_pidfd, pts);

	/*
	 * Inक्रमm pollers only when the whole thपढ़ो group निकासs.
	 * If the thपढ़ो group leader निकासs beक्रमe all other thपढ़ोs in the
	 * group, then poll(2) should block, similar to the रुको(2) family.
	 */
	अगर (thपढ़ो_group_निकासed(pid))
		poll_flags = EPOLLIN | EPOLLRDNORM;

	वापस poll_flags;
पूर्ण

स्थिर काष्ठा file_operations pidfd_fops = अणु
	.release = pidfd_release,
	.poll = pidfd_poll,
#अगर_घोषित CONFIG_PROC_FS
	.show_fdinfo = pidfd_show_fdinfo,
#पूर्ण_अगर
पूर्ण;

अटल व्योम __delayed_मुक्त_task(काष्ठा rcu_head *rhp)
अणु
	काष्ठा task_काष्ठा *tsk = container_of(rhp, काष्ठा task_काष्ठा, rcu);

	मुक्त_task(tsk);
पूर्ण

अटल __always_अंतरभूत व्योम delayed_मुक्त_task(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (IS_ENABLED(CONFIG_MEMCG))
		call_rcu(&tsk->rcu, __delayed_मुक्त_task);
	अन्यथा
		मुक्त_task(tsk);
पूर्ण

अटल व्योम copy_oom_score_adj(u64 clone_flags, काष्ठा task_काष्ठा *tsk)
अणु
	/* Skip अगर kernel thपढ़ो */
	अगर (!tsk->mm)
		वापस;

	/* Skip अगर spawning a thपढ़ो or using vविभाजन */
	अगर ((clone_flags & (CLONE_VM | CLONE_THREAD | CLONE_VFORK)) != CLONE_VM)
		वापस;

	/* We need to synchronize with __set_oom_adj */
	mutex_lock(&oom_adj_mutex);
	set_bit(MMF_MULTIPROCESS, &tsk->mm->flags);
	/* Update the values in हाल they were changed after copy_संकेत */
	tsk->संकेत->oom_score_adj = current->संकेत->oom_score_adj;
	tsk->संकेत->oom_score_adj_min = current->संकेत->oom_score_adj_min;
	mutex_unlock(&oom_adj_mutex);
पूर्ण

/*
 * This creates a new process as a copy of the old one,
 * but करोes not actually start it yet.
 *
 * It copies the रेजिस्टरs, and all the appropriate
 * parts of the process environment (as per the clone
 * flags). The actual kick-off is left to the caller.
 */
अटल __latent_entropy काष्ठा task_काष्ठा *copy_process(
					काष्ठा pid *pid,
					पूर्णांक trace,
					पूर्णांक node,
					काष्ठा kernel_clone_args *args)
अणु
	पूर्णांक pidfd = -1, retval;
	काष्ठा task_काष्ठा *p;
	काष्ठा multiprocess_संकेतs delayed;
	काष्ठा file *pidfile = शून्य;
	u64 clone_flags = args->flags;
	काष्ठा nsproxy *nsp = current->nsproxy;

	/*
	 * Don't allow sharing the root directory with processes in a dअगरferent
	 * namespace
	 */
	अगर ((clone_flags & (CLONE_NEWNS|CLONE_FS)) == (CLONE_NEWNS|CLONE_FS))
		वापस ERR_PTR(-EINVAL);

	अगर ((clone_flags & (CLONE_NEWUSER|CLONE_FS)) == (CLONE_NEWUSER|CLONE_FS))
		वापस ERR_PTR(-EINVAL);

	/*
	 * Thपढ़ो groups must share संकेतs as well, and detached thपढ़ोs
	 * can only be started up within the thपढ़ो group.
	 */
	अगर ((clone_flags & CLONE_THREAD) && !(clone_flags & CLONE_SIGHAND))
		वापस ERR_PTR(-EINVAL);

	/*
	 * Shared संकेत handlers imply shared VM. By way of the above,
	 * thपढ़ो groups also imply shared VM. Blocking this हाल allows
	 * क्रम various simplअगरications in other code.
	 */
	अगर ((clone_flags & CLONE_SIGHAND) && !(clone_flags & CLONE_VM))
		वापस ERR_PTR(-EINVAL);

	/*
	 * Siblings of global init reमुख्य as zombies on निकास since they are
	 * not reaped by their parent (swapper). To solve this and to aव्योम
	 * multi-rooted process trees, prevent global and container-inits
	 * from creating siblings.
	 */
	अगर ((clone_flags & CLONE_PARENT) &&
				current->संकेत->flags & SIGNAL_UNKILLABLE)
		वापस ERR_PTR(-EINVAL);

	/*
	 * If the new process will be in a dअगरferent pid or user namespace
	 * करो not allow it to share a thपढ़ो group with the विभाजनing task.
	 */
	अगर (clone_flags & CLONE_THREAD) अणु
		अगर ((clone_flags & (CLONE_NEWUSER | CLONE_NEWPID)) ||
		    (task_active_pid_ns(current) != nsp->pid_ns_क्रम_children))
			वापस ERR_PTR(-EINVAL);
	पूर्ण

	/*
	 * If the new process will be in a dअगरferent समय namespace
	 * करो not allow it to share VM or a thपढ़ो group with the विभाजनing task.
	 */
	अगर (clone_flags & (CLONE_THREAD | CLONE_VM)) अणु
		अगर (nsp->समय_ns != nsp->समय_ns_क्रम_children)
			वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (clone_flags & CLONE_PIDFD) अणु
		/*
		 * - CLONE_DETACHED is blocked so that we can potentially
		 *   reuse it later क्रम CLONE_PIDFD.
		 * - CLONE_THREAD is blocked until someone really needs it.
		 */
		अगर (clone_flags & (CLONE_DETACHED | CLONE_THREAD))
			वापस ERR_PTR(-EINVAL);
	पूर्ण

	/*
	 * Force any संकेतs received beक्रमe this poपूर्णांक to be delivered
	 * beक्रमe the विभाजन happens.  Collect up संकेतs sent to multiple
	 * processes that happen during the विभाजन and delay them so that
	 * they appear to happen after the विभाजन.
	 */
	sigemptyset(&delayed.संकेत);
	INIT_HLIST_NODE(&delayed.node);

	spin_lock_irq(&current->sighand->siglock);
	अगर (!(clone_flags & CLONE_THREAD))
		hlist_add_head(&delayed.node, &current->संकेत->multiprocess);
	recalc_संक_बाकी();
	spin_unlock_irq(&current->sighand->siglock);
	retval = -ERESTARTNOINTR;
	अगर (task_संक_बाकी(current))
		जाओ विभाजन_out;

	retval = -ENOMEM;
	p = dup_task_काष्ठा(current, node);
	अगर (!p)
		जाओ विभाजन_out;
	अगर (args->io_thपढ़ो) अणु
		/*
		 * Mark us an IO worker, and block any संकेत that isn't
		 * fatal or STOP
		 */
		p->flags |= PF_IO_WORKER;
		siginitsetinv(&p->blocked, sigmask(SIGKILL)|sigmask(SIGSTOP));
	पूर्ण

	/*
	 * This _must_ happen beक्रमe we call मुक्त_task(), i.e. beक्रमe we jump
	 * to any of the bad_विभाजन_* labels. This is to aव्योम मुक्तing
	 * p->set_child_tid which is (ab)used as a kthपढ़ो's data poपूर्णांकer क्रम
	 * kernel thपढ़ोs (PF_KTHREAD).
	 */
	p->set_child_tid = (clone_flags & CLONE_CHILD_SETTID) ? args->child_tid : शून्य;
	/*
	 * Clear TID on mm_release()?
	 */
	p->clear_child_tid = (clone_flags & CLONE_CHILD_CLEARTID) ? args->child_tid : शून्य;

	ftrace_graph_init_task(p);

	rt_mutex_init_task(p);

	lockdep_निश्चित_irqs_enabled();
#अगर_घोषित CONFIG_PROVE_LOCKING
	DEBUG_LOCKS_WARN_ON(!p->softirqs_enabled);
#पूर्ण_अगर
	retval = -EAGAIN;
	अगर (atomic_पढ़ो(&p->real_cred->user->processes) >=
			task_rlimit(p, RLIMIT_NPROC)) अणु
		अगर (p->real_cred->user != INIT_USER &&
		    !capable(CAP_SYS_RESOURCE) && !capable(CAP_SYS_ADMIN))
			जाओ bad_विभाजन_मुक्त;
	पूर्ण
	current->flags &= ~PF_NPROC_EXCEEDED;

	retval = copy_creds(p, clone_flags);
	अगर (retval < 0)
		जाओ bad_विभाजन_मुक्त;

	/*
	 * If multiple thपढ़ोs are within copy_process(), then this check
	 * triggers too late. This करोesn't hurt, the check is only there
	 * to stop root विभाजन bombs.
	 */
	retval = -EAGAIN;
	अगर (data_race(nr_thपढ़ोs >= max_thपढ़ोs))
		जाओ bad_विभाजन_cleanup_count;

	delayacct_tsk_init(p);	/* Must reमुख्य after dup_task_काष्ठा() */
	p->flags &= ~(PF_SUPERPRIV | PF_WQ_WORKER | PF_IDLE);
	p->flags |= PF_FORKNOEXEC;
	INIT_LIST_HEAD(&p->children);
	INIT_LIST_HEAD(&p->sibling);
	rcu_copy_process(p);
	p->vविभाजन_करोne = शून्य;
	spin_lock_init(&p->alloc_lock);

	init_संक_बाकी(&p->pending);
	p->sigqueue_cache = शून्य;

	p->uसमय = p->sसमय = p->gसमय = 0;
#अगर_घोषित CONFIG_ARCH_HAS_SCALED_CPUTIME
	p->uबारcaled = p->sबारcaled = 0;
#पूर्ण_अगर
	prev_cpuसमय_init(&p->prev_cpuसमय);

#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_GEN
	seqcount_init(&p->vसमय.seqcount);
	p->vसमय.startसमय = 0;
	p->vसमय.state = VTIME_INACTIVE;
#पूर्ण_अगर

#अगर_घोषित CONFIG_IO_URING
	p->io_uring = शून्य;
#पूर्ण_अगर

#अगर defined(SPLIT_RSS_COUNTING)
	स_रखो(&p->rss_stat, 0, माप(p->rss_stat));
#पूर्ण_अगर

	p->शेष_समयr_slack_ns = current->समयr_slack_ns;

#अगर_घोषित CONFIG_PSI
	p->psi_flags = 0;
#पूर्ण_अगर

	task_io_accounting_init(&p->ioac);
	acct_clear_पूर्णांकegrals(p);

	posix_cpuसमयrs_init(&p->posix_cpuसमयrs);

	p->io_context = शून्य;
	audit_set_context(p, शून्य);
	cgroup_विभाजन(p);
#अगर_घोषित CONFIG_NUMA
	p->mempolicy = mpol_dup(p->mempolicy);
	अगर (IS_ERR(p->mempolicy)) अणु
		retval = PTR_ERR(p->mempolicy);
		p->mempolicy = शून्य;
		जाओ bad_विभाजन_cleanup_thपढ़ोgroup_lock;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPUSETS
	p->cpuset_mem_spपढ़ो_rotor = NUMA_NO_NODE;
	p->cpuset_slab_spपढ़ो_rotor = NUMA_NO_NODE;
	seqcount_spinlock_init(&p->mems_allowed_seq, &p->alloc_lock);
#पूर्ण_अगर
#अगर_घोषित CONFIG_TRACE_IRQFLAGS
	स_रखो(&p->irqtrace, 0, माप(p->irqtrace));
	p->irqtrace.hardirq_disable_ip	= _THIS_IP_;
	p->irqtrace.softirq_enable_ip	= _THIS_IP_;
	p->softirqs_enabled		= 1;
	p->softirq_context		= 0;
#पूर्ण_अगर

	p->pagefault_disabled = 0;

#अगर_घोषित CONFIG_LOCKDEP
	lockdep_init_task(p);
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_MUTEXES
	p->blocked_on = शून्य; /* not blocked yet */
#पूर्ण_अगर
#अगर_घोषित CONFIG_BCACHE
	p->sequential_io	= 0;
	p->sequential_io_avg	= 0;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BPF_SYSCALL
	RCU_INIT_POINTER(p->bpf_storage, शून्य);
#पूर्ण_अगर

	/* Perक्रमm scheduler related setup. Assign this task to a CPU. */
	retval = sched_विभाजन(clone_flags, p);
	अगर (retval)
		जाओ bad_विभाजन_cleanup_policy;

	retval = perf_event_init_task(p, clone_flags);
	अगर (retval)
		जाओ bad_विभाजन_cleanup_policy;
	retval = audit_alloc(p);
	अगर (retval)
		जाओ bad_विभाजन_cleanup_perf;
	/* copy all the process inक्रमmation */
	shm_init_task(p);
	retval = security_task_alloc(p, clone_flags);
	अगर (retval)
		जाओ bad_विभाजन_cleanup_audit;
	retval = copy_semunकरो(clone_flags, p);
	अगर (retval)
		जाओ bad_विभाजन_cleanup_security;
	retval = copy_files(clone_flags, p);
	अगर (retval)
		जाओ bad_विभाजन_cleanup_semunकरो;
	retval = copy_fs(clone_flags, p);
	अगर (retval)
		जाओ bad_विभाजन_cleanup_files;
	retval = copy_sighand(clone_flags, p);
	अगर (retval)
		जाओ bad_विभाजन_cleanup_fs;
	retval = copy_संकेत(clone_flags, p);
	अगर (retval)
		जाओ bad_विभाजन_cleanup_sighand;
	retval = copy_mm(clone_flags, p);
	अगर (retval)
		जाओ bad_विभाजन_cleanup_संकेत;
	retval = copy_namespaces(clone_flags, p);
	अगर (retval)
		जाओ bad_विभाजन_cleanup_mm;
	retval = copy_io(clone_flags, p);
	अगर (retval)
		जाओ bad_विभाजन_cleanup_namespaces;
	retval = copy_thपढ़ो(clone_flags, args->stack, args->stack_size, p, args->tls);
	अगर (retval)
		जाओ bad_विभाजन_cleanup_io;

	stackleak_task_init(p);

	अगर (pid != &init_काष्ठा_pid) अणु
		pid = alloc_pid(p->nsproxy->pid_ns_क्रम_children, args->set_tid,
				args->set_tid_size);
		अगर (IS_ERR(pid)) अणु
			retval = PTR_ERR(pid);
			जाओ bad_विभाजन_cleanup_thपढ़ो;
		पूर्ण
	पूर्ण

	/*
	 * This has to happen after we've potentially unshared the file
	 * descriptor table (so that the pidfd करोesn't leak पूर्णांकo the child
	 * अगर the fd table isn't shared).
	 */
	अगर (clone_flags & CLONE_PIDFD) अणु
		retval = get_unused_fd_flags(O_RDWR | O_CLOEXEC);
		अगर (retval < 0)
			जाओ bad_विभाजन_मुक्त_pid;

		pidfd = retval;

		pidfile = anon_inode_getfile("[pidfd]", &pidfd_fops, pid,
					      O_RDWR | O_CLOEXEC);
		अगर (IS_ERR(pidfile)) अणु
			put_unused_fd(pidfd);
			retval = PTR_ERR(pidfile);
			जाओ bad_विभाजन_मुक्त_pid;
		पूर्ण
		get_pid(pid);	/* held by pidfile now */

		retval = put_user(pidfd, args->pidfd);
		अगर (retval)
			जाओ bad_विभाजन_put_pidfd;
	पूर्ण

#अगर_घोषित CONFIG_BLOCK
	p->plug = शून्य;
#पूर्ण_अगर
	futex_init_task(p);

	/*
	 * sigaltstack should be cleared when sharing the same VM
	 */
	अगर ((clone_flags & (CLONE_VM|CLONE_VFORK)) == CLONE_VM)
		sas_ss_reset(p);

	/*
	 * Syscall tracing and stepping should be turned off in the
	 * child regardless of CLONE_PTRACE.
	 */
	user_disable_single_step(p);
	clear_task_syscall_work(p, SYSCALL_TRACE);
#अगर defined(CONFIG_GENERIC_ENTRY) || defined(TIF_SYSCALL_EMU)
	clear_task_syscall_work(p, SYSCALL_EMU);
#पूर्ण_अगर
	clear_tsk_latency_tracing(p);

	/* ok, now we should be set up.. */
	p->pid = pid_nr(pid);
	अगर (clone_flags & CLONE_THREAD) अणु
		p->group_leader = current->group_leader;
		p->tgid = current->tgid;
	पूर्ण अन्यथा अणु
		p->group_leader = p;
		p->tgid = p->pid;
	पूर्ण

	p->nr_dirtied = 0;
	p->nr_dirtied_छोड़ो = 128 >> (PAGE_SHIFT - 10);
	p->dirty_छोड़ोd_when = 0;

	p->pdeath_संकेत = 0;
	INIT_LIST_HEAD(&p->thपढ़ो_group);
	p->task_works = शून्य;

#अगर_घोषित CONFIG_KRETPROBES
	p->kretprobe_instances.first = शून्य;
#पूर्ण_अगर

	/*
	 * Ensure that the cgroup subप्रणाली policies allow the new process to be
	 * विभाजनed. It should be noted that the new process's css_set can be changed
	 * between here and cgroup_post_विभाजन() अगर an organisation operation is in
	 * progress.
	 */
	retval = cgroup_can_विभाजन(p, args);
	अगर (retval)
		जाओ bad_विभाजन_put_pidfd;

	/*
	 * From this poपूर्णांक on we must aव्योम any synchronous user-space
	 * communication until we take the tasklist-lock. In particular, we करो
	 * not want user-space to be able to predict the process start-समय by
	 * stalling विभाजन(2) after we recorded the start_समय but beक्रमe it is
	 * visible to the प्रणाली.
	 */

	p->start_समय = kसमय_get_ns();
	p->start_bootसमय = kसमय_get_bootसमय_ns();

	/*
	 * Make it visible to the rest of the प्रणाली, but करोnt wake it up yet.
	 * Need tasklist lock क्रम parent etc handling!
	 */
	ग_लिखो_lock_irq(&tasklist_lock);

	/* CLONE_PARENT re-uses the old parent */
	अगर (clone_flags & (CLONE_PARENT|CLONE_THREAD)) अणु
		p->real_parent = current->real_parent;
		p->parent_exec_id = current->parent_exec_id;
		अगर (clone_flags & CLONE_THREAD)
			p->निकास_संकेत = -1;
		अन्यथा
			p->निकास_संकेत = current->group_leader->निकास_संकेत;
	पूर्ण अन्यथा अणु
		p->real_parent = current;
		p->parent_exec_id = current->self_exec_id;
		p->निकास_संकेत = args->निकास_संकेत;
	पूर्ण

	klp_copy_process(p);

	spin_lock(&current->sighand->siglock);

	/*
	 * Copy seccomp details explicitly here, in हाल they were changed
	 * beक्रमe holding sighand lock.
	 */
	copy_seccomp(p);

	rseq_विभाजन(p, clone_flags);

	/* Don't start children in a dying pid namespace */
	अगर (unlikely(!(ns_of_pid(pid)->pid_allocated & PIDNS_ADDING))) अणु
		retval = -ENOMEM;
		जाओ bad_विभाजन_cancel_cgroup;
	पूर्ण

	/* Let समाप्त terminate clone/विभाजन in the middle */
	अगर (fatal_संकेत_pending(current)) अणु
		retval = -EINTR;
		जाओ bad_विभाजन_cancel_cgroup;
	पूर्ण

	/* past the last poपूर्णांक of failure */
	अगर (pidfile)
		fd_install(pidfd, pidfile);

	init_task_pid_links(p);
	अगर (likely(p->pid)) अणु
		ptrace_init_task(p, (clone_flags & CLONE_PTRACE) || trace);

		init_task_pid(p, PIDTYPE_PID, pid);
		अगर (thपढ़ो_group_leader(p)) अणु
			init_task_pid(p, PIDTYPE_TGID, pid);
			init_task_pid(p, PIDTYPE_PGID, task_pgrp(current));
			init_task_pid(p, PIDTYPE_SID, task_session(current));

			अगर (is_child_reaper(pid)) अणु
				ns_of_pid(pid)->child_reaper = p;
				p->संकेत->flags |= SIGNAL_UNKILLABLE;
			पूर्ण
			p->संकेत->shared_pending.संकेत = delayed.संकेत;
			p->संकेत->tty = tty_kref_get(current->संकेत->tty);
			/*
			 * Inherit has_child_subreaper flag under the same
			 * tasklist_lock with adding child to the process tree
			 * क्रम propagate_has_child_subreaper optimization.
			 */
			p->संकेत->has_child_subreaper = p->real_parent->संकेत->has_child_subreaper ||
							 p->real_parent->संकेत->is_child_subreaper;
			list_add_tail(&p->sibling, &p->real_parent->children);
			list_add_tail_rcu(&p->tasks, &init_task.tasks);
			attach_pid(p, PIDTYPE_TGID);
			attach_pid(p, PIDTYPE_PGID);
			attach_pid(p, PIDTYPE_SID);
			__this_cpu_inc(process_counts);
		पूर्ण अन्यथा अणु
			current->संकेत->nr_thपढ़ोs++;
			atomic_inc(&current->संकेत->live);
			refcount_inc(&current->संकेत->sigcnt);
			task_join_group_stop(p);
			list_add_tail_rcu(&p->thपढ़ो_group,
					  &p->group_leader->thपढ़ो_group);
			list_add_tail_rcu(&p->thपढ़ो_node,
					  &p->संकेत->thपढ़ो_head);
		पूर्ण
		attach_pid(p, PIDTYPE_PID);
		nr_thपढ़ोs++;
	पूर्ण
	total_विभाजनs++;
	hlist_del_init(&delayed.node);
	spin_unlock(&current->sighand->siglock);
	syscall_tracepoपूर्णांक_update(p);
	ग_लिखो_unlock_irq(&tasklist_lock);

	proc_विभाजन_connector(p);
	sched_post_विभाजन(p);
	cgroup_post_विभाजन(p, args);
	perf_event_विभाजन(p);

	trace_task_newtask(p, clone_flags);
	uprobe_copy_process(p, clone_flags);

	copy_oom_score_adj(clone_flags, p);

	वापस p;

bad_विभाजन_cancel_cgroup:
	spin_unlock(&current->sighand->siglock);
	ग_लिखो_unlock_irq(&tasklist_lock);
	cgroup_cancel_विभाजन(p, args);
bad_विभाजन_put_pidfd:
	अगर (clone_flags & CLONE_PIDFD) अणु
		fput(pidfile);
		put_unused_fd(pidfd);
	पूर्ण
bad_विभाजन_मुक्त_pid:
	अगर (pid != &init_काष्ठा_pid)
		मुक्त_pid(pid);
bad_विभाजन_cleanup_thपढ़ो:
	निकास_thपढ़ो(p);
bad_विभाजन_cleanup_io:
	अगर (p->io_context)
		निकास_io_context(p);
bad_विभाजन_cleanup_namespaces:
	निकास_task_namespaces(p);
bad_विभाजन_cleanup_mm:
	अगर (p->mm) अणु
		mm_clear_owner(p->mm, p);
		mmput(p->mm);
	पूर्ण
bad_विभाजन_cleanup_संकेत:
	अगर (!(clone_flags & CLONE_THREAD))
		मुक्त_संकेत_काष्ठा(p->संकेत);
bad_विभाजन_cleanup_sighand:
	__cleanup_sighand(p->sighand);
bad_विभाजन_cleanup_fs:
	निकास_fs(p); /* blocking */
bad_विभाजन_cleanup_files:
	निकास_files(p); /* blocking */
bad_विभाजन_cleanup_semunकरो:
	निकास_sem(p);
bad_विभाजन_cleanup_security:
	security_task_मुक्त(p);
bad_विभाजन_cleanup_audit:
	audit_मुक्त(p);
bad_विभाजन_cleanup_perf:
	perf_event_मुक्त_task(p);
bad_विभाजन_cleanup_policy:
	lockdep_मुक्त_task(p);
#अगर_घोषित CONFIG_NUMA
	mpol_put(p->mempolicy);
bad_विभाजन_cleanup_thपढ़ोgroup_lock:
#पूर्ण_अगर
	delayacct_tsk_मुक्त(p);
bad_विभाजन_cleanup_count:
	atomic_dec(&p->cred->user->processes);
	निकास_creds(p);
bad_विभाजन_मुक्त:
	p->state = TASK_DEAD;
	put_task_stack(p);
	delayed_मुक्त_task(p);
विभाजन_out:
	spin_lock_irq(&current->sighand->siglock);
	hlist_del_init(&delayed.node);
	spin_unlock_irq(&current->sighand->siglock);
	वापस ERR_PTR(retval);
पूर्ण

अटल अंतरभूत व्योम init_idle_pids(काष्ठा task_काष्ठा *idle)
अणु
	क्रमागत pid_type type;

	क्रम (type = PIDTYPE_PID; type < PIDTYPE_MAX; ++type) अणु
		INIT_HLIST_NODE(&idle->pid_links[type]); /* not really needed */
		init_task_pid(idle, type, &init_काष्ठा_pid);
	पूर्ण
पूर्ण

काष्ठा task_काष्ठा *विभाजन_idle(पूर्णांक cpu)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा kernel_clone_args args = अणु
		.flags = CLONE_VM,
	पूर्ण;

	task = copy_process(&init_काष्ठा_pid, 0, cpu_to_node(cpu), &args);
	अगर (!IS_ERR(task)) अणु
		init_idle_pids(task);
		init_idle(task, cpu);
	पूर्ण

	वापस task;
पूर्ण

काष्ठा mm_काष्ठा *copy_init_mm(व्योम)
अणु
	वापस dup_mm(शून्य, &init_mm);
पूर्ण

/*
 * This is like kernel_clone(), but shaved करोwn and tailored to just
 * creating io_uring workers. It वापसs a created task, or an error poपूर्णांकer.
 * The वापसed task is inactive, and the caller must fire it up through
 * wake_up_new_task(p). All संकेतs are blocked in the created task.
 */
काष्ठा task_काष्ठा *create_io_thपढ़ो(पूर्णांक (*fn)(व्योम *), व्योम *arg, पूर्णांक node)
अणु
	अचिन्हित दीर्घ flags = CLONE_FS|CLONE_खाताS|CLONE_SIGHAND|CLONE_THREAD|
				CLONE_IO;
	काष्ठा kernel_clone_args args = अणु
		.flags		= ((lower_32_bits(flags) | CLONE_VM |
				    CLONE_UNTRACED) & ~CSIGNAL),
		.निकास_संकेत	= (lower_32_bits(flags) & CSIGNAL),
		.stack		= (अचिन्हित दीर्घ)fn,
		.stack_size	= (अचिन्हित दीर्घ)arg,
		.io_thपढ़ो	= 1,
	पूर्ण;

	वापस copy_process(शून्य, 0, node, &args);
पूर्ण

/*
 *  Ok, this is the मुख्य विभाजन-routine.
 *
 * It copies the process, and अगर successful kick-starts
 * it and रुकोs क्रम it to finish using the VM अगर required.
 *
 * args->निकास_संकेत is expected to be checked क्रम sanity by the caller.
 */
pid_t kernel_clone(काष्ठा kernel_clone_args *args)
अणु
	u64 clone_flags = args->flags;
	काष्ठा completion vविभाजन;
	काष्ठा pid *pid;
	काष्ठा task_काष्ठा *p;
	पूर्णांक trace = 0;
	pid_t nr;

	/*
	 * For legacy clone() calls, CLONE_PIDFD uses the parent_tid argument
	 * to वापस the pidfd. Hence, CLONE_PIDFD and CLONE_PARENT_SETTID are
	 * mutually exclusive. With clone3() CLONE_PIDFD has grown a separate
	 * field in काष्ठा clone_args and it still करोesn't make sense to have
	 * them both poपूर्णांक at the same memory location. Perक्रमming this check
	 * here has the advantage that we करोn't need to have a separate helper
	 * to check क्रम legacy clone().
	 */
	अगर ((args->flags & CLONE_PIDFD) &&
	    (args->flags & CLONE_PARENT_SETTID) &&
	    (args->pidfd == args->parent_tid))
		वापस -EINVAL;

	/*
	 * Determine whether and which event to report to ptracer.  When
	 * called from kernel_thपढ़ो or CLONE_UNTRACED is explicitly
	 * requested, no event is reported; otherwise, report अगर the event
	 * क्रम the type of विभाजनing is enabled.
	 */
	अगर (!(clone_flags & CLONE_UNTRACED)) अणु
		अगर (clone_flags & CLONE_VFORK)
			trace = PTRACE_EVENT_VFORK;
		अन्यथा अगर (args->निकास_संकेत != SIGCHLD)
			trace = PTRACE_EVENT_CLONE;
		अन्यथा
			trace = PTRACE_EVENT_FORK;

		अगर (likely(!ptrace_event_enabled(current, trace)))
			trace = 0;
	पूर्ण

	p = copy_process(शून्य, trace, NUMA_NO_NODE, args);
	add_latent_entropy();

	अगर (IS_ERR(p))
		वापस PTR_ERR(p);

	/*
	 * Do this prior waking up the new thपढ़ो - the thपढ़ो poपूर्णांकer
	 * might get invalid after that poपूर्णांक, अगर the thपढ़ो निकासs quickly.
	 */
	trace_sched_process_विभाजन(current, p);

	pid = get_task_pid(p, PIDTYPE_PID);
	nr = pid_vnr(pid);

	अगर (clone_flags & CLONE_PARENT_SETTID)
		put_user(nr, args->parent_tid);

	अगर (clone_flags & CLONE_VFORK) अणु
		p->vविभाजन_करोne = &vविभाजन;
		init_completion(&vविभाजन);
		get_task_काष्ठा(p);
	पूर्ण

	wake_up_new_task(p);

	/* विभाजनing complete and child started to run, tell ptracer */
	अगर (unlikely(trace))
		ptrace_event_pid(trace, pid);

	अगर (clone_flags & CLONE_VFORK) अणु
		अगर (!रुको_क्रम_vविभाजन_करोne(p, &vविभाजन))
			ptrace_event_pid(PTRACE_EVENT_VFORK_DONE, pid);
	पूर्ण

	put_pid(pid);
	वापस nr;
पूर्ण

/*
 * Create a kernel thपढ़ो.
 */
pid_t kernel_thपढ़ो(पूर्णांक (*fn)(व्योम *), व्योम *arg, अचिन्हित दीर्घ flags)
अणु
	काष्ठा kernel_clone_args args = अणु
		.flags		= ((lower_32_bits(flags) | CLONE_VM |
				    CLONE_UNTRACED) & ~CSIGNAL),
		.निकास_संकेत	= (lower_32_bits(flags) & CSIGNAL),
		.stack		= (अचिन्हित दीर्घ)fn,
		.stack_size	= (अचिन्हित दीर्घ)arg,
	पूर्ण;

	वापस kernel_clone(&args);
पूर्ण

#अगर_घोषित __ARCH_WANT_SYS_FORK
SYSCALL_DEFINE0(विभाजन)
अणु
#अगर_घोषित CONFIG_MMU
	काष्ठा kernel_clone_args args = अणु
		.निकास_संकेत = SIGCHLD,
	पूर्ण;

	वापस kernel_clone(&args);
#अन्यथा
	/* can not support in nommu mode */
	वापस -EINVAL;
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

#अगर_घोषित __ARCH_WANT_SYS_VFORK
SYSCALL_DEFINE0(vविभाजन)
अणु
	काष्ठा kernel_clone_args args = अणु
		.flags		= CLONE_VFORK | CLONE_VM,
		.निकास_संकेत	= SIGCHLD,
	पूर्ण;

	वापस kernel_clone(&args);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित __ARCH_WANT_SYS_CLONE
#अगर_घोषित CONFIG_CLONE_BACKWARDS
SYSCALL_DEFINE5(clone, अचिन्हित दीर्घ, clone_flags, अचिन्हित दीर्घ, newsp,
		 पूर्णांक __user *, parent_tidptr,
		 अचिन्हित दीर्घ, tls,
		 पूर्णांक __user *, child_tidptr)
#या_अगर defined(CONFIG_CLONE_BACKWARDS2)
SYSCALL_DEFINE5(clone, अचिन्हित दीर्घ, newsp, अचिन्हित दीर्घ, clone_flags,
		 पूर्णांक __user *, parent_tidptr,
		 पूर्णांक __user *, child_tidptr,
		 अचिन्हित दीर्घ, tls)
#या_अगर defined(CONFIG_CLONE_BACKWARDS3)
SYSCALL_DEFINE6(clone, अचिन्हित दीर्घ, clone_flags, अचिन्हित दीर्घ, newsp,
		पूर्णांक, stack_size,
		पूर्णांक __user *, parent_tidptr,
		पूर्णांक __user *, child_tidptr,
		अचिन्हित दीर्घ, tls)
#अन्यथा
SYSCALL_DEFINE5(clone, अचिन्हित दीर्घ, clone_flags, अचिन्हित दीर्घ, newsp,
		 पूर्णांक __user *, parent_tidptr,
		 पूर्णांक __user *, child_tidptr,
		 अचिन्हित दीर्घ, tls)
#पूर्ण_अगर
अणु
	काष्ठा kernel_clone_args args = अणु
		.flags		= (lower_32_bits(clone_flags) & ~CSIGNAL),
		.pidfd		= parent_tidptr,
		.child_tid	= child_tidptr,
		.parent_tid	= parent_tidptr,
		.निकास_संकेत	= (lower_32_bits(clone_flags) & CSIGNAL),
		.stack		= newsp,
		.tls		= tls,
	पूर्ण;

	वापस kernel_clone(&args);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित __ARCH_WANT_SYS_CLONE3

noअंतरभूत अटल पूर्णांक copy_clone_args_from_user(काष्ठा kernel_clone_args *kargs,
					      काष्ठा clone_args __user *uargs,
					      माप_प्रकार usize)
अणु
	पूर्णांक err;
	काष्ठा clone_args args;
	pid_t *kset_tid = kargs->set_tid;

	BUILD_BUG_ON(दुरत्वend(काष्ठा clone_args, tls) !=
		     CLONE_ARGS_SIZE_VER0);
	BUILD_BUG_ON(दुरत्वend(काष्ठा clone_args, set_tid_size) !=
		     CLONE_ARGS_SIZE_VER1);
	BUILD_BUG_ON(दुरत्वend(काष्ठा clone_args, cgroup) !=
		     CLONE_ARGS_SIZE_VER2);
	BUILD_BUG_ON(माप(काष्ठा clone_args) != CLONE_ARGS_SIZE_VER2);

	अगर (unlikely(usize > PAGE_SIZE))
		वापस -E2BIG;
	अगर (unlikely(usize < CLONE_ARGS_SIZE_VER0))
		वापस -EINVAL;

	err = copy_काष्ठा_from_user(&args, माप(args), uargs, usize);
	अगर (err)
		वापस err;

	अगर (unlikely(args.set_tid_size > MAX_PID_NS_LEVEL))
		वापस -EINVAL;

	अगर (unlikely(!args.set_tid && args.set_tid_size > 0))
		वापस -EINVAL;

	अगर (unlikely(args.set_tid && args.set_tid_size == 0))
		वापस -EINVAL;

	/*
	 * Verअगरy that higher 32bits of निकास_संकेत are unset and that
	 * it is a valid संकेत
	 */
	अगर (unlikely((args.निकास_संकेत & ~((u64)CSIGNAL)) ||
		     !valid_संकेत(args.निकास_संकेत)))
		वापस -EINVAL;

	अगर ((args.flags & CLONE_INTO_CGROUP) &&
	    (args.cgroup > पूर्णांक_उच्च || usize < CLONE_ARGS_SIZE_VER2))
		वापस -EINVAL;

	*kargs = (काष्ठा kernel_clone_args)अणु
		.flags		= args.flags,
		.pidfd		= u64_to_user_ptr(args.pidfd),
		.child_tid	= u64_to_user_ptr(args.child_tid),
		.parent_tid	= u64_to_user_ptr(args.parent_tid),
		.निकास_संकेत	= args.निकास_संकेत,
		.stack		= args.stack,
		.stack_size	= args.stack_size,
		.tls		= args.tls,
		.set_tid_size	= args.set_tid_size,
		.cgroup		= args.cgroup,
	पूर्ण;

	अगर (args.set_tid &&
		copy_from_user(kset_tid, u64_to_user_ptr(args.set_tid),
			(kargs->set_tid_size * माप(pid_t))))
		वापस -EFAULT;

	kargs->set_tid = kset_tid;

	वापस 0;
पूर्ण

/**
 * clone3_stack_valid - check and prepare stack
 * @kargs: kernel clone args
 *
 * Verअगरy that the stack arguments userspace gave us are sane.
 * In addition, set the stack direction क्रम userspace since it's easy क्रम us to
 * determine.
 */
अटल अंतरभूत bool clone3_stack_valid(काष्ठा kernel_clone_args *kargs)
अणु
	अगर (kargs->stack == 0) अणु
		अगर (kargs->stack_size > 0)
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (kargs->stack_size == 0)
			वापस false;

		अगर (!access_ok((व्योम __user *)kargs->stack, kargs->stack_size))
			वापस false;

#अगर !defined(CONFIG_STACK_GROWSUP) && !defined(CONFIG_IA64)
		kargs->stack += kargs->stack_size;
#पूर्ण_अगर
	पूर्ण

	वापस true;
पूर्ण

अटल bool clone3_args_valid(काष्ठा kernel_clone_args *kargs)
अणु
	/* Verअगरy that no unknown flags are passed aदीर्घ. */
	अगर (kargs->flags &
	    ~(CLONE_LEGACY_FLAGS | CLONE_CLEAR_SIGHAND | CLONE_INTO_CGROUP))
		वापस false;

	/*
	 * - make the CLONE_DETACHED bit reusable क्रम clone3
	 * - make the CSIGNAL bits reusable क्रम clone3
	 */
	अगर (kargs->flags & (CLONE_DETACHED | CSIGNAL))
		वापस false;

	अगर ((kargs->flags & (CLONE_SIGHAND | CLONE_CLEAR_SIGHAND)) ==
	    (CLONE_SIGHAND | CLONE_CLEAR_SIGHAND))
		वापस false;

	अगर ((kargs->flags & (CLONE_THREAD | CLONE_PARENT)) &&
	    kargs->निकास_संकेत)
		वापस false;

	अगर (!clone3_stack_valid(kargs))
		वापस false;

	वापस true;
पूर्ण

/**
 * clone3 - create a new process with specअगरic properties
 * @uargs: argument काष्ठाure
 * @size:  size of @uargs
 *
 * clone3() is the extensible successor to clone()/clone2().
 * It takes a काष्ठा as argument that is versioned by its size.
 *
 * Return: On success, a positive PID क्रम the child process.
 *         On error, a negative त्रुटि_सं number.
 */
SYSCALL_DEFINE2(clone3, काष्ठा clone_args __user *, uargs, माप_प्रकार, size)
अणु
	पूर्णांक err;

	काष्ठा kernel_clone_args kargs;
	pid_t set_tid[MAX_PID_NS_LEVEL];

	kargs.set_tid = set_tid;

	err = copy_clone_args_from_user(&kargs, uargs, size);
	अगर (err)
		वापस err;

	अगर (!clone3_args_valid(&kargs))
		वापस -EINVAL;

	वापस kernel_clone(&kargs);
पूर्ण
#पूर्ण_अगर

व्योम walk_process_tree(काष्ठा task_काष्ठा *top, proc_visitor visitor, व्योम *data)
अणु
	काष्ठा task_काष्ठा *leader, *parent, *child;
	पूर्णांक res;

	पढ़ो_lock(&tasklist_lock);
	leader = top = top->group_leader;
करोwn:
	क्रम_each_thपढ़ो(leader, parent) अणु
		list_क्रम_each_entry(child, &parent->children, sibling) अणु
			res = visitor(child, data);
			अगर (res) अणु
				अगर (res < 0)
					जाओ out;
				leader = child;
				जाओ करोwn;
			पूर्ण
up:
			;
		पूर्ण
	पूर्ण

	अगर (leader != top) अणु
		child = leader;
		parent = child->real_parent;
		leader = parent->group_leader;
		जाओ up;
	पूर्ण
out:
	पढ़ो_unlock(&tasklist_lock);
पूर्ण

#अगर_अघोषित ARCH_MIN_MMSTRUCT_ALIGN
#घोषणा ARCH_MIN_MMSTRUCT_ALIGN 0
#पूर्ण_अगर

अटल व्योम sighand_ctor(व्योम *data)
अणु
	काष्ठा sighand_काष्ठा *sighand = data;

	spin_lock_init(&sighand->siglock);
	init_रुकोqueue_head(&sighand->संकेतfd_wqh);
पूर्ण

व्योम __init proc_caches_init(व्योम)
अणु
	अचिन्हित पूर्णांक mm_size;

	sighand_cachep = kmem_cache_create("sighand_cache",
			माप(काष्ठा sighand_काष्ठा), 0,
			SLAB_HWCACHE_ALIGN|SLAB_PANIC|SLAB_TYPESAFE_BY_RCU|
			SLAB_ACCOUNT, sighand_ctor);
	संकेत_cachep = kmem_cache_create("signal_cache",
			माप(काष्ठा संकेत_काष्ठा), 0,
			SLAB_HWCACHE_ALIGN|SLAB_PANIC|SLAB_ACCOUNT,
			शून्य);
	files_cachep = kmem_cache_create("files_cache",
			माप(काष्ठा files_काष्ठा), 0,
			SLAB_HWCACHE_ALIGN|SLAB_PANIC|SLAB_ACCOUNT,
			शून्य);
	fs_cachep = kmem_cache_create("fs_cache",
			माप(काष्ठा fs_काष्ठा), 0,
			SLAB_HWCACHE_ALIGN|SLAB_PANIC|SLAB_ACCOUNT,
			शून्य);

	/*
	 * The mm_cpumask is located at the end of mm_काष्ठा, and is
	 * dynamically sized based on the maximum CPU number this प्रणाली
	 * can have, taking hotplug पूर्णांकo account (nr_cpu_ids).
	 */
	mm_size = माप(काष्ठा mm_काष्ठा) + cpumask_size();

	mm_cachep = kmem_cache_create_usercopy("mm_struct",
			mm_size, ARCH_MIN_MMSTRUCT_ALIGN,
			SLAB_HWCACHE_ALIGN|SLAB_PANIC|SLAB_ACCOUNT,
			दुरत्व(काष्ठा mm_काष्ठा, saved_auxv),
			माप_field(काष्ठा mm_काष्ठा, saved_auxv),
			शून्य);
	vm_area_cachep = KMEM_CACHE(vm_area_काष्ठा, SLAB_PANIC|SLAB_ACCOUNT);
	mmap_init();
	nsproxy_cache_init();
पूर्ण

/*
 * Check स्थिरraपूर्णांकs on flags passed to the unshare प्रणाली call.
 */
अटल पूर्णांक check_unshare_flags(अचिन्हित दीर्घ unshare_flags)
अणु
	अगर (unshare_flags & ~(CLONE_THREAD|CLONE_FS|CLONE_NEWNS|CLONE_SIGHAND|
				CLONE_VM|CLONE_खाताS|CLONE_SYSVSEM|
				CLONE_NEWUTS|CLONE_NEWIPC|CLONE_NEWNET|
				CLONE_NEWUSER|CLONE_NEWPID|CLONE_NEWCGROUP|
				CLONE_NEWTIME))
		वापस -EINVAL;
	/*
	 * Not implemented, but pretend it works अगर there is nothing
	 * to unshare.  Note that unsharing the address space or the
	 * संकेत handlers also need to unshare the संकेत queues (aka
	 * CLONE_THREAD).
	 */
	अगर (unshare_flags & (CLONE_THREAD | CLONE_SIGHAND | CLONE_VM)) अणु
		अगर (!thपढ़ो_group_empty(current))
			वापस -EINVAL;
	पूर्ण
	अगर (unshare_flags & (CLONE_SIGHAND | CLONE_VM)) अणु
		अगर (refcount_पढ़ो(&current->sighand->count) > 1)
			वापस -EINVAL;
	पूर्ण
	अगर (unshare_flags & CLONE_VM) अणु
		अगर (!current_is_single_thपढ़ोed())
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Unshare the fileप्रणाली काष्ठाure अगर it is being shared
 */
अटल पूर्णांक unshare_fs(अचिन्हित दीर्घ unshare_flags, काष्ठा fs_काष्ठा **new_fsp)
अणु
	काष्ठा fs_काष्ठा *fs = current->fs;

	अगर (!(unshare_flags & CLONE_FS) || !fs)
		वापस 0;

	/* करोn't need lock here; in the worst case we'll करो useless copy */
	अगर (fs->users == 1)
		वापस 0;

	*new_fsp = copy_fs_काष्ठा(fs);
	अगर (!*new_fsp)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/*
 * Unshare file descriptor table अगर it is being shared
 */
पूर्णांक unshare_fd(अचिन्हित दीर्घ unshare_flags, अचिन्हित पूर्णांक max_fds,
	       काष्ठा files_काष्ठा **new_fdp)
अणु
	काष्ठा files_काष्ठा *fd = current->files;
	पूर्णांक error = 0;

	अगर ((unshare_flags & CLONE_खाताS) &&
	    (fd && atomic_पढ़ो(&fd->count) > 1)) अणु
		*new_fdp = dup_fd(fd, max_fds, &error);
		अगर (!*new_fdp)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * unshare allows a process to 'unshare' part of the process
 * context which was originally shared using clone.  copy_*
 * functions used by kernel_clone() cannot be used here directly
 * because they modअगरy an inactive task_काष्ठा that is being
 * स्थिरructed. Here we are modअगरying the current, active,
 * task_काष्ठा.
 */
पूर्णांक ksys_unshare(अचिन्हित दीर्घ unshare_flags)
अणु
	काष्ठा fs_काष्ठा *fs, *new_fs = शून्य;
	काष्ठा files_काष्ठा *fd, *new_fd = शून्य;
	काष्ठा cred *new_cred = शून्य;
	काष्ठा nsproxy *new_nsproxy = शून्य;
	पूर्णांक करो_sysvsem = 0;
	पूर्णांक err;

	/*
	 * If unsharing a user namespace must also unshare the thपढ़ो group
	 * and unshare the fileप्रणाली root and working directories.
	 */
	अगर (unshare_flags & CLONE_NEWUSER)
		unshare_flags |= CLONE_THREAD | CLONE_FS;
	/*
	 * If unsharing vm, must also unshare संकेत handlers.
	 */
	अगर (unshare_flags & CLONE_VM)
		unshare_flags |= CLONE_SIGHAND;
	/*
	 * If unsharing a संकेत handlers, must also unshare the संकेत queues.
	 */
	अगर (unshare_flags & CLONE_SIGHAND)
		unshare_flags |= CLONE_THREAD;
	/*
	 * If unsharing namespace, must also unshare fileप्रणाली inक्रमmation.
	 */
	अगर (unshare_flags & CLONE_NEWNS)
		unshare_flags |= CLONE_FS;

	err = check_unshare_flags(unshare_flags);
	अगर (err)
		जाओ bad_unshare_out;
	/*
	 * CLONE_NEWIPC must also detach from the unकरोlist: after चयनing
	 * to a new ipc namespace, the semaphore arrays from the old
	 * namespace are unreachable.
	 */
	अगर (unshare_flags & (CLONE_NEWIPC|CLONE_SYSVSEM))
		करो_sysvsem = 1;
	err = unshare_fs(unshare_flags, &new_fs);
	अगर (err)
		जाओ bad_unshare_out;
	err = unshare_fd(unshare_flags, NR_OPEN_MAX, &new_fd);
	अगर (err)
		जाओ bad_unshare_cleanup_fs;
	err = unshare_userns(unshare_flags, &new_cred);
	अगर (err)
		जाओ bad_unshare_cleanup_fd;
	err = unshare_nsproxy_namespaces(unshare_flags, &new_nsproxy,
					 new_cred, new_fs);
	अगर (err)
		जाओ bad_unshare_cleanup_cred;

	अगर (new_fs || new_fd || करो_sysvsem || new_cred || new_nsproxy) अणु
		अगर (करो_sysvsem) अणु
			/*
			 * CLONE_SYSVSEM is equivalent to sys_निकास().
			 */
			निकास_sem(current);
		पूर्ण
		अगर (unshare_flags & CLONE_NEWIPC) अणु
			/* Orphan segments in old ns (see sem above). */
			निकास_shm(current);
			shm_init_task(current);
		पूर्ण

		अगर (new_nsproxy)
			चयन_task_namespaces(current, new_nsproxy);

		task_lock(current);

		अगर (new_fs) अणु
			fs = current->fs;
			spin_lock(&fs->lock);
			current->fs = new_fs;
			अगर (--fs->users)
				new_fs = शून्य;
			अन्यथा
				new_fs = fs;
			spin_unlock(&fs->lock);
		पूर्ण

		अगर (new_fd) अणु
			fd = current->files;
			current->files = new_fd;
			new_fd = fd;
		पूर्ण

		task_unlock(current);

		अगर (new_cred) अणु
			/* Install the new user namespace */
			commit_creds(new_cred);
			new_cred = शून्य;
		पूर्ण
	पूर्ण

	perf_event_namespaces(current);

bad_unshare_cleanup_cred:
	अगर (new_cred)
		put_cred(new_cred);
bad_unshare_cleanup_fd:
	अगर (new_fd)
		put_files_काष्ठा(new_fd);

bad_unshare_cleanup_fs:
	अगर (new_fs)
		मुक्त_fs_काष्ठा(new_fs);

bad_unshare_out:
	वापस err;
पूर्ण

SYSCALL_DEFINE1(unshare, अचिन्हित दीर्घ, unshare_flags)
अणु
	वापस ksys_unshare(unshare_flags);
पूर्ण

/*
 *	Helper to unshare the files of the current task.
 *	We करोn't want to expose copy_files पूर्णांकernals to
 *	the exec layer of the kernel.
 */

पूर्णांक unshare_files(व्योम)
अणु
	काष्ठा task_काष्ठा *task = current;
	काष्ठा files_काष्ठा *old, *copy = शून्य;
	पूर्णांक error;

	error = unshare_fd(CLONE_खाताS, NR_OPEN_MAX, &copy);
	अगर (error || !copy)
		वापस error;

	old = task->files;
	task_lock(task);
	task->files = copy;
	task_unlock(task);
	put_files_काष्ठा(old);
	वापस 0;
पूर्ण

पूर्णांक sysctl_max_thपढ़ोs(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		       व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table t;
	पूर्णांक ret;
	पूर्णांक thपढ़ोs = max_thपढ़ोs;
	पूर्णांक min = 1;
	पूर्णांक max = MAX_THREADS;

	t = *table;
	t.data = &thपढ़ोs;
	t.extra1 = &min;
	t.extra2 = &max;

	ret = proc_करोपूर्णांकvec_minmax(&t, ग_लिखो, buffer, lenp, ppos);
	अगर (ret || !ग_लिखो)
		वापस ret;

	max_thपढ़ोs = thपढ़ोs;

	वापस 0;
पूर्ण
