<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test module to generate lockups
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/cpu.h>
#समावेश <linux/nmi.h>
#समावेश <linux/mm.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/file.h>

अटल अचिन्हित पूर्णांक समय_secs;
module_param(समय_secs, uपूर्णांक, 0600);
MODULE_PARM_DESC(समय_secs, "lockup time in seconds, default 0");

अटल अचिन्हित पूर्णांक समय_nsecs;
module_param(समय_nsecs, uपूर्णांक, 0600);
MODULE_PARM_DESC(समय_nsecs, "nanoseconds part of lockup time, default 0");

अटल अचिन्हित पूर्णांक coolकरोwn_secs;
module_param(coolकरोwn_secs, uपूर्णांक, 0600);
MODULE_PARM_DESC(coolकरोwn_secs, "cooldown time between iterations in seconds, default 0");

अटल अचिन्हित पूर्णांक coolकरोwn_nsecs;
module_param(coolकरोwn_nsecs, uपूर्णांक, 0600);
MODULE_PARM_DESC(coolकरोwn_nsecs, "nanoseconds part of cooldown, default 0");

अटल अचिन्हित पूर्णांक iterations = 1;
module_param(iterations, uपूर्णांक, 0600);
MODULE_PARM_DESC(iterations, "lockup iterations, default 1");

अटल bool all_cpus;
module_param(all_cpus, bool, 0400);
MODULE_PARM_DESC(all_cpus, "trigger lockup at all cpus at once");

अटल पूर्णांक रुको_state;
अटल अक्षर *state = "R";
module_param(state, अक्षरp, 0400);
MODULE_PARM_DESC(state, "wait in 'R' running (default), 'D' uninterruptible, 'K' killable, 'S' interruptible state");

अटल bool use_hrसमयr;
module_param(use_hrसमयr, bool, 0400);
MODULE_PARM_DESC(use_hrसमयr, "use high-resolution timer for sleeping");

अटल bool ioरुको;
module_param(ioरुको, bool, 0400);
MODULE_PARM_DESC(ioरुको, "account sleep time as iowait");

अटल bool lock_पढ़ो;
module_param(lock_पढ़ो, bool, 0400);
MODULE_PARM_DESC(lock_पढ़ो, "lock read-write locks for read");

अटल bool lock_single;
module_param(lock_single, bool, 0400);
MODULE_PARM_DESC(lock_single, "acquire locks only at one cpu");

अटल bool reacquire_locks;
module_param(reacquire_locks, bool, 0400);
MODULE_PARM_DESC(reacquire_locks, "release and reacquire locks/irq/preempt between iterations");

अटल bool touch_softlockup;
module_param(touch_softlockup, bool, 0600);
MODULE_PARM_DESC(touch_softlockup, "touch soft-lockup watchdog between iterations");

अटल bool touch_hardlockup;
module_param(touch_hardlockup, bool, 0600);
MODULE_PARM_DESC(touch_hardlockup, "touch hard-lockup watchdog between iterations");

अटल bool call_cond_resched;
module_param(call_cond_resched, bool, 0600);
MODULE_PARM_DESC(call_cond_resched, "call cond_resched() between iterations");

अटल bool measure_lock_रुको;
module_param(measure_lock_रुको, bool, 0400);
MODULE_PARM_DESC(measure_lock_रुको, "measure lock wait time");

अटल अचिन्हित दीर्घ lock_रुको_threshold = अच_दीर्घ_उच्च;
module_param(lock_रुको_threshold, uदीर्घ, 0400);
MODULE_PARM_DESC(lock_रुको_threshold, "print lock wait time longer than this in nanoseconds, default off");

अटल bool test_disable_irq;
module_param_named(disable_irq, test_disable_irq, bool, 0400);
MODULE_PARM_DESC(disable_irq, "disable interrupts: generate hard-lockups");

अटल bool disable_softirq;
module_param(disable_softirq, bool, 0400);
MODULE_PARM_DESC(disable_softirq, "disable bottom-half irq handlers");

अटल bool disable_preempt;
module_param(disable_preempt, bool, 0400);
MODULE_PARM_DESC(disable_preempt, "disable preemption: generate soft-lockups");

अटल bool lock_rcu;
module_param(lock_rcu, bool, 0400);
MODULE_PARM_DESC(lock_rcu, "grab rcu_read_lock: generate rcu stalls");

अटल bool lock_mmap_sem;
module_param(lock_mmap_sem, bool, 0400);
MODULE_PARM_DESC(lock_mmap_sem, "lock mm->mmap_lock: block procfs interfaces");

अटल अचिन्हित दीर्घ lock_rwsem_ptr;
module_param_unsafe(lock_rwsem_ptr, uदीर्घ, 0400);
MODULE_PARM_DESC(lock_rwsem_ptr, "lock rw_semaphore at address");

अटल अचिन्हित दीर्घ lock_mutex_ptr;
module_param_unsafe(lock_mutex_ptr, uदीर्घ, 0400);
MODULE_PARM_DESC(lock_mutex_ptr, "lock mutex at address");

अटल अचिन्हित दीर्घ lock_spinlock_ptr;
module_param_unsafe(lock_spinlock_ptr, uदीर्घ, 0400);
MODULE_PARM_DESC(lock_spinlock_ptr, "lock spinlock at address");

अटल अचिन्हित दीर्घ lock_rwlock_ptr;
module_param_unsafe(lock_rwlock_ptr, uदीर्घ, 0400);
MODULE_PARM_DESC(lock_rwlock_ptr, "lock rwlock at address");

अटल अचिन्हित पूर्णांक alloc_pages_nr;
module_param_unsafe(alloc_pages_nr, uपूर्णांक, 0600);
MODULE_PARM_DESC(alloc_pages_nr, "allocate and free pages under locks");

अटल अचिन्हित पूर्णांक alloc_pages_order;
module_param(alloc_pages_order, uपूर्णांक, 0400);
MODULE_PARM_DESC(alloc_pages_order, "page order to allocate");

अटल gfp_t alloc_pages_gfp = GFP_KERNEL;
module_param_unsafe(alloc_pages_gfp, uपूर्णांक, 0400);
MODULE_PARM_DESC(alloc_pages_gfp, "allocate pages with this gfp_mask, default GFP_KERNEL");

अटल bool alloc_pages_atomic;
module_param(alloc_pages_atomic, bool, 0400);
MODULE_PARM_DESC(alloc_pages_atomic, "allocate pages with GFP_ATOMIC");

अटल bool पुनः_स्मृतिate_pages;
module_param(पुनः_स्मृतिate_pages, bool, 0400);
MODULE_PARM_DESC(पुनः_स्मृतिate_pages, "free and allocate pages between iterations");

काष्ठा file *test_file;
अटल काष्ठा inode *test_inode;
अटल अक्षर test_file_path[256];
module_param_string(file_path, test_file_path, माप(test_file_path), 0400);
MODULE_PARM_DESC(file_path, "file path to test");

अटल bool test_lock_inode;
module_param_named(lock_inode, test_lock_inode, bool, 0400);
MODULE_PARM_DESC(lock_inode, "lock file -> inode -> i_rwsem");

अटल bool test_lock_mapping;
module_param_named(lock_mapping, test_lock_mapping, bool, 0400);
MODULE_PARM_DESC(lock_mapping, "lock file -> mapping -> i_mmap_rwsem");

अटल bool test_lock_sb_umount;
module_param_named(lock_sb_umount, test_lock_sb_umount, bool, 0400);
MODULE_PARM_DESC(lock_sb_umount, "lock file -> sb -> s_umount");

अटल atomic_t alloc_pages_failed = ATOMIC_INIT(0);

अटल atomic64_t max_lock_रुको = ATOMIC64_INIT(0);

अटल काष्ठा task_काष्ठा *मुख्य_task;
अटल पूर्णांक master_cpu;

अटल व्योम test_lock(bool master, bool verbose)
अणु
	u64 रुको_start;

	अगर (measure_lock_रुको)
		रुको_start = local_घड़ी();

	अगर (lock_mutex_ptr && master) अणु
		अगर (verbose)
			pr_notice("lock mutex %ps\n", (व्योम *)lock_mutex_ptr);
		mutex_lock((काष्ठा mutex *)lock_mutex_ptr);
	पूर्ण

	अगर (lock_rwsem_ptr && master) अणु
		अगर (verbose)
			pr_notice("lock rw_semaphore %ps\n",
				  (व्योम *)lock_rwsem_ptr);
		अगर (lock_पढ़ो)
			करोwn_पढ़ो((काष्ठा rw_semaphore *)lock_rwsem_ptr);
		अन्यथा
			करोwn_ग_लिखो((काष्ठा rw_semaphore *)lock_rwsem_ptr);
	पूर्ण

	अगर (lock_mmap_sem && master) अणु
		अगर (verbose)
			pr_notice("lock mmap_lock pid=%d\n", मुख्य_task->pid);
		अगर (lock_पढ़ो)
			mmap_पढ़ो_lock(मुख्य_task->mm);
		अन्यथा
			mmap_ग_लिखो_lock(मुख्य_task->mm);
	पूर्ण

	अगर (test_disable_irq)
		local_irq_disable();

	अगर (disable_softirq)
		local_bh_disable();

	अगर (disable_preempt)
		preempt_disable();

	अगर (lock_rcu)
		rcu_पढ़ो_lock();

	अगर (lock_spinlock_ptr && master) अणु
		अगर (verbose)
			pr_notice("lock spinlock %ps\n",
				  (व्योम *)lock_spinlock_ptr);
		spin_lock((spinlock_t *)lock_spinlock_ptr);
	पूर्ण

	अगर (lock_rwlock_ptr && master) अणु
		अगर (verbose)
			pr_notice("lock rwlock %ps\n",
				  (व्योम *)lock_rwlock_ptr);
		अगर (lock_पढ़ो)
			पढ़ो_lock((rwlock_t *)lock_rwlock_ptr);
		अन्यथा
			ग_लिखो_lock((rwlock_t *)lock_rwlock_ptr);
	पूर्ण

	अगर (measure_lock_रुको) अणु
		s64 cur_रुको = local_घड़ी() - रुको_start;
		s64 max_रुको = atomic64_पढ़ो(&max_lock_रुको);

		करो अणु
			अगर (cur_रुको < max_रुको)
				अवरोध;
			max_रुको = atomic64_cmpxchg(&max_lock_रुको,
						    max_रुको, cur_रुको);
		पूर्ण जबतक (max_रुको != cur_रुको);

		अगर (cur_रुको > lock_रुको_threshold)
			pr_notice_ratelimited("lock wait %lld ns\n", cur_रुको);
	पूर्ण
पूर्ण

अटल व्योम test_unlock(bool master, bool verbose)
अणु
	अगर (lock_rwlock_ptr && master) अणु
		अगर (lock_पढ़ो)
			पढ़ो_unlock((rwlock_t *)lock_rwlock_ptr);
		अन्यथा
			ग_लिखो_unlock((rwlock_t *)lock_rwlock_ptr);
		अगर (verbose)
			pr_notice("unlock rwlock %ps\n",
				  (व्योम *)lock_rwlock_ptr);
	पूर्ण

	अगर (lock_spinlock_ptr && master) अणु
		spin_unlock((spinlock_t *)lock_spinlock_ptr);
		अगर (verbose)
			pr_notice("unlock spinlock %ps\n",
				  (व्योम *)lock_spinlock_ptr);
	पूर्ण

	अगर (lock_rcu)
		rcu_पढ़ो_unlock();

	अगर (disable_preempt)
		preempt_enable();

	अगर (disable_softirq)
		local_bh_enable();

	अगर (test_disable_irq)
		local_irq_enable();

	अगर (lock_mmap_sem && master) अणु
		अगर (lock_पढ़ो)
			mmap_पढ़ो_unlock(मुख्य_task->mm);
		अन्यथा
			mmap_ग_लिखो_unlock(मुख्य_task->mm);
		अगर (verbose)
			pr_notice("unlock mmap_lock pid=%d\n", मुख्य_task->pid);
	पूर्ण

	अगर (lock_rwsem_ptr && master) अणु
		अगर (lock_पढ़ो)
			up_पढ़ो((काष्ठा rw_semaphore *)lock_rwsem_ptr);
		अन्यथा
			up_ग_लिखो((काष्ठा rw_semaphore *)lock_rwsem_ptr);
		अगर (verbose)
			pr_notice("unlock rw_semaphore %ps\n",
				  (व्योम *)lock_rwsem_ptr);
	पूर्ण

	अगर (lock_mutex_ptr && master) अणु
		mutex_unlock((काष्ठा mutex *)lock_mutex_ptr);
		अगर (verbose)
			pr_notice("unlock mutex %ps\n",
				  (व्योम *)lock_mutex_ptr);
	पूर्ण
पूर्ण

अटल व्योम test_alloc_pages(काष्ठा list_head *pages)
अणु
	काष्ठा page *page;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < alloc_pages_nr; i++) अणु
		page = alloc_pages(alloc_pages_gfp, alloc_pages_order);
		अगर (!page) अणु
			atomic_inc(&alloc_pages_failed);
			अवरोध;
		पूर्ण
		list_add(&page->lru, pages);
	पूर्ण
पूर्ण

अटल व्योम test_मुक्त_pages(काष्ठा list_head *pages)
अणु
	काष्ठा page *page, *next;

	list_क्रम_each_entry_safe(page, next, pages, lru)
		__मुक्त_pages(page, alloc_pages_order);
	INIT_LIST_HEAD(pages);
पूर्ण

अटल व्योम test_रुको(अचिन्हित पूर्णांक secs, अचिन्हित पूर्णांक nsecs)
अणु
	अगर (रुको_state == TASK_RUNNING) अणु
		अगर (secs)
			mdelay(secs * MSEC_PER_SEC);
		अगर (nsecs)
			ndelay(nsecs);
		वापस;
	पूर्ण

	__set_current_state(रुको_state);
	अगर (use_hrसमयr) अणु
		kसमय_प्रकार समय;

		समय = ns_to_kसमय((u64)secs * NSEC_PER_SEC + nsecs);
		schedule_hrसमयout(&समय, HRTIMER_MODE_REL);
	पूर्ण अन्यथा अणु
		schedule_समयout(secs * HZ + nsecs_to_jअगरfies(nsecs));
	पूर्ण
पूर्ण

अटल व्योम test_lockup(bool master)
अणु
	u64 lockup_start = local_घड़ी();
	अचिन्हित पूर्णांक iter = 0;
	LIST_HEAD(pages);

	pr_notice("Start on CPU%d\n", raw_smp_processor_id());

	test_lock(master, true);

	test_alloc_pages(&pages);

	जबतक (iter++ < iterations && !संकेत_pending(मुख्य_task)) अणु

		अगर (ioरुको)
			current->in_ioरुको = 1;

		test_रुको(समय_secs, समय_nsecs);

		अगर (ioरुको)
			current->in_ioरुको = 0;

		अगर (पुनः_स्मृतिate_pages)
			test_मुक्त_pages(&pages);

		अगर (reacquire_locks)
			test_unlock(master, false);

		अगर (touch_softlockup)
			touch_softlockup_watchकरोg();

		अगर (touch_hardlockup)
			touch_nmi_watchकरोg();

		अगर (call_cond_resched)
			cond_resched();

		test_रुको(coolकरोwn_secs, coolकरोwn_nsecs);

		अगर (reacquire_locks)
			test_lock(master, false);

		अगर (पुनः_स्मृतिate_pages)
			test_alloc_pages(&pages);
	पूर्ण

	pr_notice("Finish on CPU%d in %lld ns\n", raw_smp_processor_id(),
		  local_घड़ी() - lockup_start);

	test_मुक्त_pages(&pages);

	test_unlock(master, true);
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा work_काष्ठा, test_works);

अटल व्योम test_work_fn(काष्ठा work_काष्ठा *work)
अणु
	test_lockup(!lock_single ||
		    work == per_cpu_ptr(&test_works, master_cpu));
पूर्ण

अटल bool test_kernel_ptr(अचिन्हित दीर्घ addr, पूर्णांक size)
अणु
	व्योम *ptr = (व्योम *)addr;
	अक्षर buf;

	अगर (!addr)
		वापस false;

	/* should be at least पढ़ोable kernel address */
	अगर (access_ok(ptr, 1) ||
	    access_ok(ptr + size - 1, 1) ||
	    get_kernel_nofault(buf, ptr) ||
	    get_kernel_nofault(buf, ptr + size - 1)) अणु
		pr_err("invalid kernel ptr: %#lx\n", addr);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool __maybe_unused test_magic(अचिन्हित दीर्घ addr, पूर्णांक offset,
				      अचिन्हित पूर्णांक expected)
अणु
	व्योम *ptr = (व्योम *)addr + offset;
	अचिन्हित पूर्णांक magic = 0;

	अगर (!addr)
		वापस false;

	अगर (get_kernel_nofault(magic, ptr) || magic != expected) अणु
		pr_err("invalid magic at %#lx + %#x = %#x, expected %#x\n",
		       addr, offset, magic, expected);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक __init test_lockup_init(व्योम)
अणु
	u64 test_start = local_घड़ी();

	मुख्य_task = current;

	चयन (state[0]) अणु
	हाल 'S':
		रुको_state = TASK_INTERRUPTIBLE;
		अवरोध;
	हाल 'D':
		रुको_state = TASK_UNINTERRUPTIBLE;
		अवरोध;
	हाल 'K':
		रुको_state = TASK_KILLABLE;
		अवरोध;
	हाल 'R':
		रुको_state = TASK_RUNNING;
		अवरोध;
	शेष:
		pr_err("unknown state=%s\n", state);
		वापस -EINVAL;
	पूर्ण

	अगर (alloc_pages_atomic)
		alloc_pages_gfp = GFP_ATOMIC;

	अगर (test_kernel_ptr(lock_spinlock_ptr, माप(spinlock_t)) ||
	    test_kernel_ptr(lock_rwlock_ptr, माप(rwlock_t)) ||
	    test_kernel_ptr(lock_mutex_ptr, माप(काष्ठा mutex)) ||
	    test_kernel_ptr(lock_rwsem_ptr, माप(काष्ठा rw_semaphore)))
		वापस -EINVAL;

#अगर_घोषित CONFIG_DEBUG_SPINLOCK
#अगर_घोषित CONFIG_PREEMPT_RT
	अगर (test_magic(lock_spinlock_ptr,
		       दुरत्व(spinlock_t, lock.रुको_lock.magic),
		       SPINLOCK_MAGIC) ||
	    test_magic(lock_rwlock_ptr,
		       दुरत्व(rwlock_t, rपंचांगutex.रुको_lock.magic),
		       SPINLOCK_MAGIC) ||
	    test_magic(lock_mutex_ptr,
		       दुरत्व(काष्ठा mutex, lock.रुको_lock.magic),
		       SPINLOCK_MAGIC) ||
	    test_magic(lock_rwsem_ptr,
		       दुरत्व(काष्ठा rw_semaphore, rपंचांगutex.रुको_lock.magic),
		       SPINLOCK_MAGIC))
		वापस -EINVAL;
#अन्यथा
	अगर (test_magic(lock_spinlock_ptr,
		       दुरत्व(spinlock_t, rlock.magic),
		       SPINLOCK_MAGIC) ||
	    test_magic(lock_rwlock_ptr,
		       दुरत्व(rwlock_t, magic),
		       RWLOCK_MAGIC) ||
	    test_magic(lock_mutex_ptr,
		       दुरत्व(काष्ठा mutex, रुको_lock.rlock.magic),
		       SPINLOCK_MAGIC) ||
	    test_magic(lock_rwsem_ptr,
		       दुरत्व(काष्ठा rw_semaphore, रुको_lock.magic),
		       SPINLOCK_MAGIC))
		वापस -EINVAL;
#पूर्ण_अगर
#पूर्ण_अगर

	अगर ((रुको_state != TASK_RUNNING ||
	     (call_cond_resched && !reacquire_locks) ||
	     (alloc_pages_nr && gfpflags_allow_blocking(alloc_pages_gfp))) &&
	    (test_disable_irq || disable_softirq || disable_preempt ||
	     lock_rcu || lock_spinlock_ptr || lock_rwlock_ptr)) अणु
		pr_err("refuse to sleep in atomic context\n");
		वापस -EINVAL;
	पूर्ण

	अगर (lock_mmap_sem && !मुख्य_task->mm) अणु
		pr_err("no mm to lock mmap_lock\n");
		वापस -EINVAL;
	पूर्ण

	अगर (test_file_path[0]) अणु
		test_file = filp_खोलो(test_file_path, O_RDONLY, 0);
		अगर (IS_ERR(test_file)) अणु
			pr_err("failed to open %s: %ld\n", test_file_path, PTR_ERR(test_file));
			वापस PTR_ERR(test_file);
		पूर्ण
		test_inode = file_inode(test_file);
	पूर्ण अन्यथा अगर (test_lock_inode ||
		   test_lock_mapping ||
		   test_lock_sb_umount) अणु
		pr_err("no file to lock\n");
		वापस -EINVAL;
	पूर्ण

	अगर (test_lock_inode && test_inode)
		lock_rwsem_ptr = (अचिन्हित दीर्घ)&test_inode->i_rwsem;

	अगर (test_lock_mapping && test_file && test_file->f_mapping)
		lock_rwsem_ptr = (अचिन्हित दीर्घ)&test_file->f_mapping->i_mmap_rwsem;

	अगर (test_lock_sb_umount && test_inode)
		lock_rwsem_ptr = (अचिन्हित दीर्घ)&test_inode->i_sb->s_umount;

	pr_notice("START pid=%d time=%u +%u ns cooldown=%u +%u ns iterations=%u state=%s %s%s%s%s%s%s%s%s%s%s%s\n",
		  मुख्य_task->pid, समय_secs, समय_nsecs,
		  coolकरोwn_secs, coolकरोwn_nsecs, iterations, state,
		  all_cpus ? "all_cpus " : "",
		  ioरुको ? "iowait " : "",
		  test_disable_irq ? "disable_irq " : "",
		  disable_softirq ? "disable_softirq " : "",
		  disable_preempt ? "disable_preempt " : "",
		  lock_rcu ? "lock_rcu " : "",
		  lock_पढ़ो ? "lock_read " : "",
		  touch_softlockup ? "touch_softlockup " : "",
		  touch_hardlockup ? "touch_hardlockup " : "",
		  call_cond_resched ? "call_cond_resched " : "",
		  reacquire_locks ? "reacquire_locks " : "");

	अगर (alloc_pages_nr)
		pr_notice("ALLOCATE PAGES nr=%u order=%u gfp=%pGg %s\n",
			  alloc_pages_nr, alloc_pages_order, &alloc_pages_gfp,
			  पुनः_स्मृतिate_pages ? "reallocate_pages " : "");

	अगर (all_cpus) अणु
		अचिन्हित पूर्णांक cpu;

		cpus_पढ़ो_lock();

		preempt_disable();
		master_cpu = smp_processor_id();
		क्रम_each_online_cpu(cpu) अणु
			INIT_WORK(per_cpu_ptr(&test_works, cpu), test_work_fn);
			queue_work_on(cpu, प्रणाली_highpri_wq,
				      per_cpu_ptr(&test_works, cpu));
		पूर्ण
		preempt_enable();

		क्रम_each_online_cpu(cpu)
			flush_work(per_cpu_ptr(&test_works, cpu));

		cpus_पढ़ो_unlock();
	पूर्ण अन्यथा अणु
		test_lockup(true);
	पूर्ण

	अगर (measure_lock_रुको)
		pr_notice("Maximum lock wait: %lld ns\n",
			  atomic64_पढ़ो(&max_lock_रुको));

	अगर (alloc_pages_nr)
		pr_notice("Page allocation failed %u times\n",
			  atomic_पढ़ो(&alloc_pages_failed));

	pr_notice("FINISH in %llu ns\n", local_घड़ी() - test_start);

	अगर (test_file)
		fput(test_file);

	अगर (संकेत_pending(मुख्य_task))
		वापस -EINTR;

	वापस -EAGAIN;
पूर्ण
module_init(test_lockup_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Konstantin Khlebnikov <khlebnikov@yandex-team.ru>");
MODULE_DESCRIPTION("Test module to generate lockups");
