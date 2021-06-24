<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008, 2009 Intel Corporation
 * Authors: Andi Kleen, Fengguang Wu
 *
 * High level machine check handler. Handles pages reported by the
 * hardware as being corrupted usually due to a multi-bit ECC memory or cache
 * failure.
 * 
 * In addition there is a "soft offline" entry poपूर्णांक that allows stop using
 * not-yet-corrupted-by-suspicious pages without समाप्तing anything.
 *
 * Handles page cache pages in various states.	The tricky part
 * here is that we can access any page asynchronously in respect to 
 * other VM users, because memory failures could happen anyसमय and 
 * anywhere. This could violate some of their assumptions. This is why 
 * this code has to be extremely careful. Generally it tries to use 
 * normal locking rules, as in get the standard locks, even अगर that means 
 * the error handling takes potentially a दीर्घ समय.
 *
 * It can be very tempting to add handling क्रम obscure हालs here.
 * In general any code क्रम handling new हालs should only be added अगरf:
 * - You know how to test it.
 * - You have a test that can be added to mce-test
 *   https://git.kernel.org/cgit/utils/cpu/mce/mce-test.git/
 * - The हाल actually shows up as a frequent (top 10) page state in
 *   tools/vm/page-types when running a real workload.
 * 
 * There are several operations here with exponential complनिकासy because
 * of unsuitable VM data काष्ठाures. For example the operation to map back 
 * from RMAP chains to processes has to walk the complete process list and 
 * has non linear complनिकासy with the number. But since memory corruptions
 * are rare we hope to get away with this. This aव्योमs impacting the core 
 * VM.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/kernel-page-flags.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/ksm.h>
#समावेश <linux/rmap.h>
#समावेश <linux/export.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/migrate.h>
#समावेश <linux/suspend.h>
#समावेश <linux/slab.h>
#समावेश <linux/swapops.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/memory_hotplug.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/memremap.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/page-isolation.h>
#समावेश "internal.h"
#समावेश "ras/ras_event.h"

पूर्णांक sysctl_memory_failure_early_समाप्त __पढ़ो_mostly = 0;

पूर्णांक sysctl_memory_failure_recovery __पढ़ो_mostly = 1;

atomic_दीर्घ_t num_poisoned_pages __पढ़ो_mostly = ATOMIC_LONG_INIT(0);

अटल bool page_handle_poison(काष्ठा page *page, bool hugepage_or_मुक्तpage, bool release)
अणु
	अगर (hugepage_or_मुक्तpage) अणु
		/*
		 * Doing this check क्रम मुक्त pages is also fine since dissolve_मुक्त_huge_page
		 * वापसs 0 क्रम non-hugetlb pages as well.
		 */
		अगर (dissolve_मुक्त_huge_page(page) || !take_page_off_buddy(page))
			/*
			 * We could fail to take off the target page from buddy
			 * क्रम example due to racy page allocation, but that's
			 * acceptable because soft-offlined page is not broken
			 * and अगर someone really want to use it, they should
			 * take it.
			 */
			वापस false;
	पूर्ण

	SetPageHWPoison(page);
	अगर (release)
		put_page(page);
	page_ref_inc(page);
	num_poisoned_pages_inc();

	वापस true;
पूर्ण

#अगर defined(CONFIG_HWPOISON_INJECT) || defined(CONFIG_HWPOISON_INJECT_MODULE)

u32 hwpoison_filter_enable = 0;
u32 hwpoison_filter_dev_major = ~0U;
u32 hwpoison_filter_dev_minor = ~0U;
u64 hwpoison_filter_flags_mask;
u64 hwpoison_filter_flags_value;
EXPORT_SYMBOL_GPL(hwpoison_filter_enable);
EXPORT_SYMBOL_GPL(hwpoison_filter_dev_major);
EXPORT_SYMBOL_GPL(hwpoison_filter_dev_minor);
EXPORT_SYMBOL_GPL(hwpoison_filter_flags_mask);
EXPORT_SYMBOL_GPL(hwpoison_filter_flags_value);

अटल पूर्णांक hwpoison_filter_dev(काष्ठा page *p)
अणु
	काष्ठा address_space *mapping;
	dev_t dev;

	अगर (hwpoison_filter_dev_major == ~0U &&
	    hwpoison_filter_dev_minor == ~0U)
		वापस 0;

	/*
	 * page_mapping() करोes not accept slab pages.
	 */
	अगर (PageSlab(p))
		वापस -EINVAL;

	mapping = page_mapping(p);
	अगर (mapping == शून्य || mapping->host == शून्य)
		वापस -EINVAL;

	dev = mapping->host->i_sb->s_dev;
	अगर (hwpoison_filter_dev_major != ~0U &&
	    hwpoison_filter_dev_major != MAJOR(dev))
		वापस -EINVAL;
	अगर (hwpoison_filter_dev_minor != ~0U &&
	    hwpoison_filter_dev_minor != MINOR(dev))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक hwpoison_filter_flags(काष्ठा page *p)
अणु
	अगर (!hwpoison_filter_flags_mask)
		वापस 0;

	अगर ((stable_page_flags(p) & hwpoison_filter_flags_mask) ==
				    hwpoison_filter_flags_value)
		वापस 0;
	अन्यथा
		वापस -EINVAL;
पूर्ण

/*
 * This allows stress tests to limit test scope to a collection of tasks
 * by putting them under some memcg. This prevents समाप्तing unrelated/important
 * processes such as /sbin/init. Note that the target task may share clean
 * pages with init (eg. libc text), which is harmless. If the target task
 * share _dirty_ pages with another task B, the test scheme must make sure B
 * is also included in the memcg. At last, due to race conditions this filter
 * can only guarantee that the page either beदीर्घs to the memcg tasks, or is
 * a मुक्तd page.
 */
#अगर_घोषित CONFIG_MEMCG
u64 hwpoison_filter_memcg;
EXPORT_SYMBOL_GPL(hwpoison_filter_memcg);
अटल पूर्णांक hwpoison_filter_task(काष्ठा page *p)
अणु
	अगर (!hwpoison_filter_memcg)
		वापस 0;

	अगर (page_cgroup_ino(p) != hwpoison_filter_memcg)
		वापस -EINVAL;

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक hwpoison_filter_task(काष्ठा page *p) अणु वापस 0; पूर्ण
#पूर्ण_अगर

पूर्णांक hwpoison_filter(काष्ठा page *p)
अणु
	अगर (!hwpoison_filter_enable)
		वापस 0;

	अगर (hwpoison_filter_dev(p))
		वापस -EINVAL;

	अगर (hwpoison_filter_flags(p))
		वापस -EINVAL;

	अगर (hwpoison_filter_task(p))
		वापस -EINVAL;

	वापस 0;
पूर्ण
#अन्यथा
पूर्णांक hwpoison_filter(काष्ठा page *p)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

EXPORT_SYMBOL_GPL(hwpoison_filter);

/*
 * Kill all processes that have a poisoned page mapped and then isolate
 * the page.
 *
 * General strategy:
 * Find all processes having the page mapped and समाप्त them.
 * But we keep a page reference around so that the page is not
 * actually मुक्तd yet.
 * Then stash the page away
 *
 * There's no convenient way to get back to mapped processes
 * from the VMAs. So करो a brute-क्रमce search over all
 * running processes.
 *
 * Remember that machine checks are not common (or rather
 * अगर they are common you have other problems), so this shouldn't
 * be a perक्रमmance issue.
 *
 * Also there are some races possible जबतक we get from the
 * error detection to actually handle it.
 */

काष्ठा to_समाप्त अणु
	काष्ठा list_head nd;
	काष्ठा task_काष्ठा *tsk;
	अचिन्हित दीर्घ addr;
	लघु size_shअगरt;
पूर्ण;

/*
 * Send all the processes who have the page mapped a संकेत.
 * ``action optional'' अगर they are not immediately affected by the error
 * ``action required'' अगर error happened in current execution context
 */
अटल पूर्णांक समाप्त_proc(काष्ठा to_समाप्त *tk, अचिन्हित दीर्घ pfn, पूर्णांक flags)
अणु
	काष्ठा task_काष्ठा *t = tk->tsk;
	लघु addr_lsb = tk->size_shअगरt;
	पूर्णांक ret = 0;

	pr_err("Memory failure: %#lx: Sending SIGBUS to %s:%d due to hardware memory corruption\n",
			pfn, t->comm, t->pid);

	अगर (flags & MF_ACTION_REQUIRED) अणु
		अगर (t == current)
			ret = क्रमce_sig_mceerr(BUS_MCEERR_AR,
					 (व्योम __user *)tk->addr, addr_lsb);
		अन्यथा
			/* Signal other processes sharing the page अगर they have PF_MCE_EARLY set. */
			ret = send_sig_mceerr(BUS_MCEERR_AO, (व्योम __user *)tk->addr,
				addr_lsb, t);
	पूर्ण अन्यथा अणु
		/*
		 * Don't use force here, it's convenient अगर the संकेत
		 * can be temporarily blocked.
		 * This could cause a loop when the user sets SIGBUS
		 * to संक_छोड़ो, but hopefully no one will करो that?
		 */
		ret = send_sig_mceerr(BUS_MCEERR_AO, (व्योम __user *)tk->addr,
				      addr_lsb, t);  /* synchronous? */
	पूर्ण
	अगर (ret < 0)
		pr_info("Memory failure: Error sending signal to %s:%d: %d\n",
			t->comm, t->pid, ret);
	वापस ret;
पूर्ण

/*
 * Unknown page type encountered. Try to check whether it can turn PageLRU by
 * lru_add_drain_all, or a मुक्त page by reclaiming sद_असल when possible.
 */
व्योम shake_page(काष्ठा page *p, पूर्णांक access)
अणु
	अगर (PageHuge(p))
		वापस;

	अगर (!PageSlab(p)) अणु
		lru_add_drain_all();
		अगर (PageLRU(p) || is_मुक्त_buddy_page(p))
			वापस;
	पूर्ण

	/*
	 * Only call shrink_node_sद_असल here (which would also shrink
	 * other caches) अगर access is not potentially fatal.
	 */
	अगर (access)
		drop_slab_node(page_to_nid(p));
पूर्ण
EXPORT_SYMBOL_GPL(shake_page);

अटल अचिन्हित दीर्घ dev_pagemap_mapping_shअगरt(काष्ठा page *page,
		काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ address = vma_address(page, vma);
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	pgd = pgd_offset(vma->vm_mm, address);
	अगर (!pgd_present(*pgd))
		वापस 0;
	p4d = p4d_offset(pgd, address);
	अगर (!p4d_present(*p4d))
		वापस 0;
	pud = pud_offset(p4d, address);
	अगर (!pud_present(*pud))
		वापस 0;
	अगर (pud_devmap(*pud))
		वापस PUD_SHIFT;
	pmd = pmd_offset(pud, address);
	अगर (!pmd_present(*pmd))
		वापस 0;
	अगर (pmd_devmap(*pmd))
		वापस PMD_SHIFT;
	pte = pte_offset_map(pmd, address);
	अगर (!pte_present(*pte))
		वापस 0;
	अगर (pte_devmap(*pte))
		वापस PAGE_SHIFT;
	वापस 0;
पूर्ण

/*
 * Failure handling: अगर we can't find or can't kill a process there's
 * not much we can करो.	We just prपूर्णांक a message and ignore otherwise.
 */

/*
 * Schedule a process क्रम later समाप्त.
 * Uses GFP_ATOMIC allocations to aव्योम potential recursions in the VM.
 */
अटल व्योम add_to_समाप्त(काष्ठा task_काष्ठा *tsk, काष्ठा page *p,
		       काष्ठा vm_area_काष्ठा *vma,
		       काष्ठा list_head *to_समाप्त)
अणु
	काष्ठा to_समाप्त *tk;

	tk = kदो_स्मृति(माप(काष्ठा to_समाप्त), GFP_ATOMIC);
	अगर (!tk) अणु
		pr_err("Memory failure: Out of memory while machine check handling\n");
		वापस;
	पूर्ण

	tk->addr = page_address_in_vma(p, vma);
	अगर (is_zone_device_page(p))
		tk->size_shअगरt = dev_pagemap_mapping_shअगरt(p, vma);
	अन्यथा
		tk->size_shअगरt = page_shअगरt(compound_head(p));

	/*
	 * Send SIGKILL अगर "tk->addr == -EFAULT". Also, as
	 * "tk->size_shift" is always non-zero क्रम !is_zone_device_page(),
	 * so "tk->size_shift == 0" effectively checks no mapping on
	 * ZONE_DEVICE. Indeed, when a devdax page is mmapped N बार
	 * to a process' address space, it's possible not all N VMAs
	 * contain mappings क्रम the page, but at least one VMA करोes.
	 * Only deliver SIGBUS with payload derived from the VMA that
	 * has a mapping क्रम the page.
	 */
	अगर (tk->addr == -EFAULT) अणु
		pr_info("Memory failure: Unable to find user space address %lx in %s\n",
			page_to_pfn(p), tsk->comm);
	पूर्ण अन्यथा अगर (tk->size_shअगरt == 0) अणु
		kमुक्त(tk);
		वापस;
	पूर्ण

	get_task_काष्ठा(tsk);
	tk->tsk = tsk;
	list_add_tail(&tk->nd, to_समाप्त);
पूर्ण

/*
 * Kill the processes that have been collected earlier.
 *
 * Only करो anything when DOIT is set, otherwise just मुक्त the list
 * (this is used क्रम clean pages which करो not need समाप्तing)
 * Also when FAIL is set करो a क्रमce समाप्त because something went
 * wrong earlier.
 */
अटल व्योम समाप्त_procs(काष्ठा list_head *to_समाप्त, पूर्णांक क्रमceसमाप्त, bool fail,
		अचिन्हित दीर्घ pfn, पूर्णांक flags)
अणु
	काष्ठा to_समाप्त *tk, *next;

	list_क्रम_each_entry_safe (tk, next, to_समाप्त, nd) अणु
		अगर (क्रमceसमाप्त) अणु
			/*
			 * In हाल something went wrong with munmapping
			 * make sure the process करोesn't catch the
			 * संकेत and then access the memory. Just समाप्त it.
			 */
			अगर (fail || tk->addr == -EFAULT) अणु
				pr_err("Memory failure: %#lx: forcibly killing %s:%d because of failure to unmap corrupted page\n",
				       pfn, tk->tsk->comm, tk->tsk->pid);
				करो_send_sig_info(SIGKILL, SEND_SIG_PRIV,
						 tk->tsk, PIDTYPE_PID);
			पूर्ण

			/*
			 * In theory the process could have mapped
			 * something अन्यथा on the address in-between. We could
			 * check क्रम that, but we need to tell the
			 * process anyways.
			 */
			अन्यथा अगर (समाप्त_proc(tk, pfn, flags) < 0)
				pr_err("Memory failure: %#lx: Cannot send advisory machine check signal to %s:%d\n",
				       pfn, tk->tsk->comm, tk->tsk->pid);
		पूर्ण
		put_task_काष्ठा(tk->tsk);
		kमुक्त(tk);
	पूर्ण
पूर्ण

/*
 * Find a dedicated thपढ़ो which is supposed to handle SIGBUS(BUS_MCEERR_AO)
 * on behalf of the thपढ़ो group. Return task_काष्ठा of the (first found)
 * dedicated thपढ़ो अगर found, and वापस शून्य otherwise.
 *
 * We alपढ़ोy hold पढ़ो_lock(&tasklist_lock) in the caller, so we करोn't
 * have to call rcu_पढ़ो_lock/unlock() in this function.
 */
अटल काष्ठा task_काष्ठा *find_early_समाप्त_thपढ़ो(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा task_काष्ठा *t;

	क्रम_each_thपढ़ो(tsk, t) अणु
		अगर (t->flags & PF_MCE_PROCESS) अणु
			अगर (t->flags & PF_MCE_EARLY)
				वापस t;
		पूर्ण अन्यथा अणु
			अगर (sysctl_memory_failure_early_समाप्त)
				वापस t;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Determine whether a given process is "early kill" process which expects
 * to be संकेतed when some page under the process is hwpoisoned.
 * Return task_काष्ठा of the dedicated thपढ़ो (मुख्य thपढ़ो unless explicitly
 * specअगरied) अगर the process is "early kill" and otherwise वापसs शून्य.
 *
 * Note that the above is true क्रम Action Optional हाल. For Action Required
 * हाल, it's only meaningful to the current thपढ़ो which need to be संकेतed
 * with SIGBUS, this error is Action Optional क्रम other non current
 * processes sharing the same error page,अगर the process is "early kill", the
 * task_काष्ठा of the dedicated thपढ़ो will also be वापसed.
 */
अटल काष्ठा task_काष्ठा *task_early_समाप्त(काष्ठा task_काष्ठा *tsk,
					   पूर्णांक क्रमce_early)
अणु
	अगर (!tsk->mm)
		वापस शून्य;
	/*
	 * Comparing ->mm here because current task might represent
	 * a subthपढ़ो, जबतक tsk always poपूर्णांकs to the मुख्य thपढ़ो.
	 */
	अगर (क्रमce_early && tsk->mm == current->mm)
		वापस current;

	वापस find_early_समाप्त_thपढ़ो(tsk);
पूर्ण

/*
 * Collect processes when the error hit an anonymous page.
 */
अटल व्योम collect_procs_anon(काष्ठा page *page, काष्ठा list_head *to_समाप्त,
				पूर्णांक क्रमce_early)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा task_काष्ठा *tsk;
	काष्ठा anon_vma *av;
	pgoff_t pgoff;

	av = page_lock_anon_vma_पढ़ो(page);
	अगर (av == शून्य)	/* Not actually mapped anymore */
		वापस;

	pgoff = page_to_pgoff(page);
	पढ़ो_lock(&tasklist_lock);
	क्रम_each_process (tsk) अणु
		काष्ठा anon_vma_chain *vmac;
		काष्ठा task_काष्ठा *t = task_early_समाप्त(tsk, क्रमce_early);

		अगर (!t)
			जारी;
		anon_vma_पूर्णांकerval_tree_क्रमeach(vmac, &av->rb_root,
					       pgoff, pgoff) अणु
			vma = vmac->vma;
			अगर (!page_mapped_in_vma(page, vma))
				जारी;
			अगर (vma->vm_mm == t->mm)
				add_to_समाप्त(t, page, vma, to_समाप्त);
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);
	page_unlock_anon_vma_पढ़ो(av);
पूर्ण

/*
 * Collect processes when the error hit a file mapped page.
 */
अटल व्योम collect_procs_file(काष्ठा page *page, काष्ठा list_head *to_समाप्त,
				पूर्णांक क्रमce_early)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा task_काष्ठा *tsk;
	काष्ठा address_space *mapping = page->mapping;
	pgoff_t pgoff;

	i_mmap_lock_पढ़ो(mapping);
	पढ़ो_lock(&tasklist_lock);
	pgoff = page_to_pgoff(page);
	क्रम_each_process(tsk) अणु
		काष्ठा task_काष्ठा *t = task_early_समाप्त(tsk, क्रमce_early);

		अगर (!t)
			जारी;
		vma_पूर्णांकerval_tree_क्रमeach(vma, &mapping->i_mmap, pgoff,
				      pgoff) अणु
			/*
			 * Send early समाप्त संकेत to tasks where a vma covers
			 * the page but the corrupted page is not necessarily
			 * mapped it in its pte.
			 * Assume applications who requested early समाप्त want
			 * to be inक्रमmed of all such data corruptions.
			 */
			अगर (vma->vm_mm == t->mm)
				add_to_समाप्त(t, page, vma, to_समाप्त);
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);
	i_mmap_unlock_पढ़ो(mapping);
पूर्ण

/*
 * Collect the processes who have the corrupted page mapped to समाप्त.
 */
अटल व्योम collect_procs(काष्ठा page *page, काष्ठा list_head *toसमाप्त,
				पूर्णांक क्रमce_early)
अणु
	अगर (!page->mapping)
		वापस;

	अगर (PageAnon(page))
		collect_procs_anon(page, toसमाप्त, क्रमce_early);
	अन्यथा
		collect_procs_file(page, toसमाप्त, क्रमce_early);
पूर्ण

अटल स्थिर अक्षर *action_name[] = अणु
	[MF_IGNORED] = "Ignored",
	[MF_FAILED] = "Failed",
	[MF_DELAYED] = "Delayed",
	[MF_RECOVERED] = "Recovered",
पूर्ण;

अटल स्थिर अक्षर * स्थिर action_page_types[] = अणु
	[MF_MSG_KERNEL]			= "reserved kernel page",
	[MF_MSG_KERNEL_HIGH_ORDER]	= "high-order kernel page",
	[MF_MSG_SLAB]			= "kernel slab page",
	[MF_MSG_DIFFERENT_COMPOUND]	= "different compound page after locking",
	[MF_MSG_POISONED_HUGE]		= "huge page already hardware poisoned",
	[MF_MSG_HUGE]			= "huge page",
	[MF_MSG_FREE_HUGE]		= "free huge page",
	[MF_MSG_NON_PMD_HUGE]		= "non-pmd-sized huge page",
	[MF_MSG_UNMAP_FAILED]		= "unmapping failed page",
	[MF_MSG_सूचीTY_SWAPCACHE]	= "dirty swapcache page",
	[MF_MSG_CLEAN_SWAPCACHE]	= "clean swapcache page",
	[MF_MSG_सूचीTY_MLOCKED_LRU]	= "dirty mlocked LRU page",
	[MF_MSG_CLEAN_MLOCKED_LRU]	= "clean mlocked LRU page",
	[MF_MSG_सूचीTY_UNEVICTABLE_LRU]	= "dirty unevictable LRU page",
	[MF_MSG_CLEAN_UNEVICTABLE_LRU]	= "clean unevictable LRU page",
	[MF_MSG_सूचीTY_LRU]		= "dirty LRU page",
	[MF_MSG_CLEAN_LRU]		= "clean LRU page",
	[MF_MSG_TRUNCATED_LRU]		= "already truncated LRU page",
	[MF_MSG_BUDDY]			= "free buddy page",
	[MF_MSG_BUDDY_2ND]		= "free buddy page (2nd try)",
	[MF_MSG_DAX]			= "dax page",
	[MF_MSG_UNSPLIT_THP]		= "unsplit thp",
	[MF_MSG_UNKNOWN]		= "unknown page",
पूर्ण;

/*
 * XXX: It is possible that a page is isolated from LRU cache,
 * and then kept in swap cache or failed to हटाओ from page cache.
 * The page count will stop it from being मुक्तd by unpoison.
 * Stress tests should be aware of this memory leak problem.
 */
अटल पूर्णांक delete_from_lru_cache(काष्ठा page *p)
अणु
	अगर (!isolate_lru_page(p)) अणु
		/*
		 * Clear sensible page flags, so that the buddy प्रणाली won't
		 * complain when the page is unpoison-and-मुक्तd.
		 */
		ClearPageActive(p);
		ClearPageUnevictable(p);

		/*
		 * Poisoned page might never drop its ref count to 0 so we have
		 * to unअक्षरge it manually from its memcg.
		 */
		mem_cgroup_unअक्षरge(p);

		/*
		 * drop the page count elevated by isolate_lru_page()
		 */
		put_page(p);
		वापस 0;
	पूर्ण
	वापस -EIO;
पूर्ण

अटल पूर्णांक truncate_error_page(काष्ठा page *p, अचिन्हित दीर्घ pfn,
				काष्ठा address_space *mapping)
अणु
	पूर्णांक ret = MF_FAILED;

	अगर (mapping->a_ops->error_हटाओ_page) अणु
		पूर्णांक err = mapping->a_ops->error_हटाओ_page(mapping, p);

		अगर (err != 0) अणु
			pr_info("Memory failure: %#lx: Failed to punch page: %d\n",
				pfn, err);
		पूर्ण अन्यथा अगर (page_has_निजी(p) &&
			   !try_to_release_page(p, GFP_NOIO)) अणु
			pr_info("Memory failure: %#lx: failed to release buffers\n",
				pfn);
		पूर्ण अन्यथा अणु
			ret = MF_RECOVERED;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * If the file प्रणाली करोesn't support it just invalidate
		 * This fails on dirty or anything with निजी pages
		 */
		अगर (invalidate_inode_page(p))
			ret = MF_RECOVERED;
		अन्यथा
			pr_info("Memory failure: %#lx: Failed to invalidate\n",
				pfn);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Error hit kernel page.
 * Do nothing, try to be lucky and not touch this instead. For a few हालs we
 * could be more sophisticated.
 */
अटल पूर्णांक me_kernel(काष्ठा page *p, अचिन्हित दीर्घ pfn)
अणु
	वापस MF_IGNORED;
पूर्ण

/*
 * Page in unknown state. Do nothing.
 */
अटल पूर्णांक me_unknown(काष्ठा page *p, अचिन्हित दीर्घ pfn)
अणु
	pr_err("Memory failure: %#lx: Unknown page state\n", pfn);
	वापस MF_FAILED;
पूर्ण

/*
 * Clean (or cleaned) page cache page.
 */
अटल पूर्णांक me_pagecache_clean(काष्ठा page *p, अचिन्हित दीर्घ pfn)
अणु
	काष्ठा address_space *mapping;

	delete_from_lru_cache(p);

	/*
	 * For anonymous pages we're करोne the only reference left
	 * should be the one m_f() holds.
	 */
	अगर (PageAnon(p))
		वापस MF_RECOVERED;

	/*
	 * Now truncate the page in the page cache. This is really
	 * more like a "temporary hole punch"
	 * Don't करो this क्रम block devices when someone अन्यथा
	 * has a reference, because it could be file प्रणाली metadata
	 * and that's not safe to truncate.
	 */
	mapping = page_mapping(p);
	अगर (!mapping) अणु
		/*
		 * Page has been teared करोwn in the meanजबतक
		 */
		वापस MF_FAILED;
	पूर्ण

	/*
	 * Truncation is a bit tricky. Enable it per file प्रणाली क्रम now.
	 *
	 * Open: to take i_mutex or not क्रम this? Right now we करोn't.
	 */
	वापस truncate_error_page(p, pfn, mapping);
पूर्ण

/*
 * Dirty pagecache page
 * Issues: when the error hit a hole page the error is not properly
 * propagated.
 */
अटल पूर्णांक me_pagecache_dirty(काष्ठा page *p, अचिन्हित दीर्घ pfn)
अणु
	काष्ठा address_space *mapping = page_mapping(p);

	SetPageError(p);
	/* TBD: prपूर्णांक more inक्रमmation about the file. */
	अगर (mapping) अणु
		/*
		 * IO error will be reported by ग_लिखो(), fsync(), etc.
		 * who check the mapping.
		 * This way the application knows that something went
		 * wrong with its dirty file data.
		 *
		 * There's one खोलो issue:
		 *
		 * The EIO will be only reported on the next IO
		 * operation and then cleared through the IO map.
		 * Normally Linux has two mechanisms to pass IO error
		 * first through the AS_EIO flag in the address space
		 * and then through the PageError flag in the page.
		 * Since we drop pages on memory failure handling the
		 * only mechanism खोलो to use is through AS_AIO.
		 *
		 * This has the disadvantage that it माला_लो cleared on
		 * the first operation that वापसs an error, जबतक
		 * the PageError bit is more sticky and only cleared
		 * when the page is reपढ़ो or dropped.  If an
		 * application assumes it will always get error on
		 * fsync, but करोes other operations on the fd beक्रमe
		 * and the page is dropped between then the error
		 * will not be properly reported.
		 *
		 * This can alपढ़ोy happen even without hwpoisoned
		 * pages: first on metadata IO errors (which only
		 * report through AS_EIO) or when the page is dropped
		 * at the wrong समय.
		 *
		 * So right now we assume that the application DTRT on
		 * the first EIO, but we're not worse than other parts
		 * of the kernel.
		 */
		mapping_set_error(mapping, -EIO);
	पूर्ण

	वापस me_pagecache_clean(p, pfn);
पूर्ण

/*
 * Clean and dirty swap cache.
 *
 * Dirty swap cache page is tricky to handle. The page could live both in page
 * cache and swap cache(ie. page is freshly swapped in). So it could be
 * referenced concurrently by 2 types of PTEs:
 * normal PTEs and swap PTEs. We try to handle them consistently by calling
 * try_to_unmap(TTU_IGNORE_HWPOISON) to convert the normal PTEs to swap PTEs,
 * and then
 *      - clear dirty bit to prevent IO
 *      - हटाओ from LRU
 *      - but keep in the swap cache, so that when we वापस to it on
 *        a later page fault, we know the application is accessing
 *        corrupted data and shall be समाप्तed (we installed simple
 *        पूर्णांकerception code in करो_swap_page to catch it).
 *
 * Clean swap cache pages can be directly isolated. A later page fault will
 * bring in the known good data from disk.
 */
अटल पूर्णांक me_swapcache_dirty(काष्ठा page *p, अचिन्हित दीर्घ pfn)
अणु
	ClearPageDirty(p);
	/* Trigger EIO in shmem: */
	ClearPageUptodate(p);

	अगर (!delete_from_lru_cache(p))
		वापस MF_DELAYED;
	अन्यथा
		वापस MF_FAILED;
पूर्ण

अटल पूर्णांक me_swapcache_clean(काष्ठा page *p, अचिन्हित दीर्घ pfn)
अणु
	delete_from_swap_cache(p);

	अगर (!delete_from_lru_cache(p))
		वापस MF_RECOVERED;
	अन्यथा
		वापस MF_FAILED;
पूर्ण

/*
 * Huge pages. Needs work.
 * Issues:
 * - Error on hugepage is contained in hugepage unit (not in raw page unit.)
 *   To narrow करोwn समाप्त region to one page, we need to अवरोध up pmd.
 */
अटल पूर्णांक me_huge_page(काष्ठा page *p, अचिन्हित दीर्घ pfn)
अणु
	पूर्णांक res;
	काष्ठा page *hpage = compound_head(p);
	काष्ठा address_space *mapping;

	अगर (!PageHuge(hpage))
		वापस MF_DELAYED;

	mapping = page_mapping(hpage);
	अगर (mapping) अणु
		res = truncate_error_page(hpage, pfn, mapping);
	पूर्ण अन्यथा अणु
		res = MF_FAILED;
		unlock_page(hpage);
		/*
		 * migration entry prevents later access on error anonymous
		 * hugepage, so we can मुक्त and dissolve it पूर्णांकo buddy to
		 * save healthy subpages.
		 */
		अगर (PageAnon(hpage))
			put_page(hpage);
		अगर (!dissolve_मुक्त_huge_page(p) && take_page_off_buddy(p)) अणु
			page_ref_inc(p);
			res = MF_RECOVERED;
		पूर्ण
		lock_page(hpage);
	पूर्ण

	वापस res;
पूर्ण

/*
 * Various page states we can handle.
 *
 * A page state is defined by its current page->flags bits.
 * The table matches them in order and calls the right handler.
 *
 * This is quite tricky because we can access page at any समय
 * in its live cycle, so all accesses have to be extremely careful.
 *
 * This is not complete. More states could be added.
 * For any missing state करोn't attempt recovery.
 */

#घोषणा dirty		(1UL << PG_dirty)
#घोषणा sc		((1UL << PG_swapcache) | (1UL << PG_swapbacked))
#घोषणा unevict		(1UL << PG_unevictable)
#घोषणा mlock		(1UL << PG_mlocked)
#घोषणा lru		(1UL << PG_lru)
#घोषणा head		(1UL << PG_head)
#घोषणा slab		(1UL << PG_slab)
#घोषणा reserved	(1UL << PG_reserved)

अटल काष्ठा page_state अणु
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ res;
	क्रमागत mf_action_page_type type;
	पूर्णांक (*action)(काष्ठा page *p, अचिन्हित दीर्घ pfn);
पूर्ण error_states[] = अणु
	अणु reserved,	reserved,	MF_MSG_KERNEL,	me_kernel पूर्ण,
	/*
	 * मुक्त pages are specially detected outside this table:
	 * PG_buddy pages only make a small fraction of all मुक्त pages.
	 */

	/*
	 * Could in theory check अगर slab page is मुक्त or अगर we can drop
	 * currently unused objects without touching them. But just
	 * treat it as standard kernel क्रम now.
	 */
	अणु slab,		slab,		MF_MSG_SLAB,	me_kernel पूर्ण,

	अणु head,		head,		MF_MSG_HUGE,		me_huge_page पूर्ण,

	अणु sc|dirty,	sc|dirty,	MF_MSG_सूचीTY_SWAPCACHE,	me_swapcache_dirty पूर्ण,
	अणु sc|dirty,	sc,		MF_MSG_CLEAN_SWAPCACHE,	me_swapcache_clean पूर्ण,

	अणु mlock|dirty,	mlock|dirty,	MF_MSG_सूचीTY_MLOCKED_LRU,	me_pagecache_dirty पूर्ण,
	अणु mlock|dirty,	mlock,		MF_MSG_CLEAN_MLOCKED_LRU,	me_pagecache_clean पूर्ण,

	अणु unevict|dirty, unevict|dirty,	MF_MSG_सूचीTY_UNEVICTABLE_LRU,	me_pagecache_dirty पूर्ण,
	अणु unevict|dirty, unevict,	MF_MSG_CLEAN_UNEVICTABLE_LRU,	me_pagecache_clean पूर्ण,

	अणु lru|dirty,	lru|dirty,	MF_MSG_सूचीTY_LRU,	me_pagecache_dirty पूर्ण,
	अणु lru|dirty,	lru,		MF_MSG_CLEAN_LRU,	me_pagecache_clean पूर्ण,

	/*
	 * Catchall entry: must be at end.
	 */
	अणु 0,		0,		MF_MSG_UNKNOWN,	me_unknown पूर्ण,
पूर्ण;

#अघोषित dirty
#अघोषित sc
#अघोषित unevict
#अघोषित mlock
#अघोषित lru
#अघोषित head
#अघोषित slab
#अघोषित reserved

/*
 * "Dirty/Clean" indication is not 100% accurate due to the possibility of
 * setting PG_dirty outside page lock. See also comment above set_page_dirty().
 */
अटल व्योम action_result(अचिन्हित दीर्घ pfn, क्रमागत mf_action_page_type type,
			  क्रमागत mf_result result)
अणु
	trace_memory_failure_event(pfn, type, result);

	pr_err("Memory failure: %#lx: recovery action for %s: %s\n",
		pfn, action_page_types[type], action_name[result]);
पूर्ण

अटल पूर्णांक page_action(काष्ठा page_state *ps, काष्ठा page *p,
			अचिन्हित दीर्घ pfn)
अणु
	पूर्णांक result;
	पूर्णांक count;

	result = ps->action(p, pfn);

	count = page_count(p) - 1;
	अगर (ps->action == me_swapcache_dirty && result == MF_DELAYED)
		count--;
	अगर (count > 0) अणु
		pr_err("Memory failure: %#lx: %s still referenced by %d users\n",
		       pfn, action_page_types[ps->type], count);
		result = MF_FAILED;
	पूर्ण
	action_result(pfn, ps->type, result);

	/* Could करो more checks here अगर page looks ok */
	/*
	 * Could adjust zone counters here to correct क्रम the missing page.
	 */

	वापस (result == MF_RECOVERED || result == MF_DELAYED) ? 0 : -EBUSY;
पूर्ण

/*
 * Return true अगर a page type of a given page is supported by hwpoison
 * mechanism (जबतक handling could fail), otherwise false.  This function
 * करोes not वापस true क्रम hugetlb or device memory pages, so it's assumed
 * to be called only in the context where we never have such pages.
 */
अटल अंतरभूत bool HWPoisonHandlable(काष्ठा page *page)
अणु
	वापस PageLRU(page) || __PageMovable(page);
पूर्ण

/**
 * __get_hwpoison_page() - Get refcount क्रम memory error handling:
 * @page:	raw error page (hit by memory error)
 *
 * Return: वापस 0 अगर failed to grab the refcount, otherwise true (some
 * non-zero value.)
 */
अटल पूर्णांक __get_hwpoison_page(काष्ठा page *page)
अणु
	काष्ठा page *head = compound_head(page);
	पूर्णांक ret = 0;
	bool hugetlb = false;

	ret = get_hwpoison_huge_page(head, &hugetlb);
	अगर (hugetlb)
		वापस ret;

	/*
	 * This check prevents from calling get_hwpoison_unless_zero()
	 * क्रम any unsupported type of page in order to reduce the risk of
	 * unexpected races caused by taking a page refcount.
	 */
	अगर (!HWPoisonHandlable(head))
		वापस 0;

	अगर (PageTransHuge(head)) अणु
		/*
		 * Non anonymous thp exists only in allocation/मुक्त समय. We
		 * can't handle such a case correctly, so let's give it up.
		 * This should be better than triggering BUG_ON when kernel
		 * tries to touch the "partially handled" page.
		 */
		अगर (!PageAnon(head)) अणु
			pr_err("Memory failure: %#lx: non anonymous thp\n",
				page_to_pfn(page));
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (get_page_unless_zero(head)) अणु
		अगर (head == compound_head(page))
			वापस 1;

		pr_info("Memory failure: %#lx cannot catch tail\n",
			page_to_pfn(page));
		put_page(head);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Safely get reference count of an arbitrary page.
 *
 * Returns 0 क्रम a मुक्त page, 1 क्रम an in-use page,
 * -EIO क्रम a page-type we cannot handle and -EBUSY अगर we raced with an
 * allocation.
 * We only incremented refcount in हाल the page was alपढ़ोy in-use and it
 * is a known type we can handle.
 */
अटल पूर्णांक get_any_page(काष्ठा page *p, अचिन्हित दीर्घ flags)
अणु
	पूर्णांक ret = 0, pass = 0;
	bool count_increased = false;

	अगर (flags & MF_COUNT_INCREASED)
		count_increased = true;

try_again:
	अगर (!count_increased && !__get_hwpoison_page(p)) अणु
		अगर (page_count(p)) अणु
			/* We raced with an allocation, retry. */
			अगर (pass++ < 3)
				जाओ try_again;
			ret = -EBUSY;
		पूर्ण अन्यथा अगर (!PageHuge(p) && !is_मुक्त_buddy_page(p)) अणु
			/* We raced with put_page, retry. */
			अगर (pass++ < 3)
				जाओ try_again;
			ret = -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (PageHuge(p) || HWPoisonHandlable(p)) अणु
			ret = 1;
		पूर्ण अन्यथा अणु
			/*
			 * A page we cannot handle. Check whether we can turn
			 * it पूर्णांकo something we can handle.
			 */
			अगर (pass++ < 3) अणु
				put_page(p);
				shake_page(p, 1);
				count_increased = false;
				जाओ try_again;
			पूर्ण
			put_page(p);
			ret = -EIO;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक get_hwpoison_page(काष्ठा page *p, अचिन्हित दीर्घ flags,
			     क्रमागत mf_flags ctxt)
अणु
	पूर्णांक ret;

	zone_pcp_disable(page_zone(p));
	अगर (ctxt == MF_SOFT_OFFLINE)
		ret = get_any_page(p, flags);
	अन्यथा
		ret = __get_hwpoison_page(p);
	zone_pcp_enable(page_zone(p));

	वापस ret;
पूर्ण

/*
 * Do all that is necessary to हटाओ user space mappings. Unmap
 * the pages and send SIGBUS to the processes अगर the data was dirty.
 */
अटल bool hwpoison_user_mappings(काष्ठा page *p, अचिन्हित दीर्घ pfn,
				  पूर्णांक flags, काष्ठा page **hpagep)
अणु
	क्रमागत ttu_flags ttu = TTU_IGNORE_MLOCK;
	काष्ठा address_space *mapping;
	LIST_HEAD(toसमाप्त);
	bool unmap_success = true;
	पूर्णांक समाप्त = 1, क्रमceसमाप्त;
	काष्ठा page *hpage = *hpagep;
	bool mlocked = PageMlocked(hpage);

	/*
	 * Here we are पूर्णांकerested only in user-mapped pages, so skip any
	 * other types of pages.
	 */
	अगर (PageReserved(p) || PageSlab(p))
		वापस true;
	अगर (!(PageLRU(hpage) || PageHuge(p)))
		वापस true;

	/*
	 * This check implies we करोn't समाप्त processes अगर their pages
	 * are in the swap cache early. Those are always late समाप्तs.
	 */
	अगर (!page_mapped(hpage))
		वापस true;

	अगर (PageKsm(p)) अणु
		pr_err("Memory failure: %#lx: can't handle KSM pages.\n", pfn);
		वापस false;
	पूर्ण

	अगर (PageSwapCache(p)) अणु
		pr_err("Memory failure: %#lx: keeping poisoned page in swap cache\n",
			pfn);
		ttu |= TTU_IGNORE_HWPOISON;
	पूर्ण

	/*
	 * Propagate the dirty bit from PTEs to काष्ठा page first, because we
	 * need this to decide अगर we should समाप्त or just drop the page.
	 * XXX: the dirty test could be racy: set_page_dirty() may not always
	 * be called inside page lock (it's recommended but not enक्रमced).
	 */
	mapping = page_mapping(hpage);
	अगर (!(flags & MF_MUST_KILL) && !PageDirty(hpage) && mapping &&
	    mapping_can_ग_लिखोback(mapping)) अणु
		अगर (page_mkclean(hpage)) अणु
			SetPageDirty(hpage);
		पूर्ण अन्यथा अणु
			समाप्त = 0;
			ttu |= TTU_IGNORE_HWPOISON;
			pr_info("Memory failure: %#lx: corrupted page was clean: dropped without side effects\n",
				pfn);
		पूर्ण
	पूर्ण

	/*
	 * First collect all the processes that have the page
	 * mapped in dirty क्रमm.  This has to be करोne beक्रमe try_to_unmap,
	 * because ttu takes the rmap data काष्ठाures करोwn.
	 *
	 * Error handling: We ignore errors here because
	 * there's nothing that can be करोne.
	 */
	अगर (समाप्त)
		collect_procs(hpage, &toसमाप्त, flags & MF_ACTION_REQUIRED);

	अगर (!PageHuge(hpage)) अणु
		unmap_success = try_to_unmap(hpage, ttu);
	पूर्ण अन्यथा अणु
		अगर (!PageAnon(hpage)) अणु
			/*
			 * For hugetlb pages in shared mappings, try_to_unmap
			 * could potentially call huge_pmd_unshare.  Because of
			 * this, take semaphore in ग_लिखो mode here and set
			 * TTU_RMAP_LOCKED to indicate we have taken the lock
			 * at this higer level.
			 */
			mapping = hugetlb_page_mapping_lock_ग_लिखो(hpage);
			अगर (mapping) अणु
				unmap_success = try_to_unmap(hpage,
						     ttu|TTU_RMAP_LOCKED);
				i_mmap_unlock_ग_लिखो(mapping);
			पूर्ण अन्यथा अणु
				pr_info("Memory failure: %#lx: could not lock mapping for mapped huge page\n", pfn);
				unmap_success = false;
			पूर्ण
		पूर्ण अन्यथा अणु
			unmap_success = try_to_unmap(hpage, ttu);
		पूर्ण
	पूर्ण
	अगर (!unmap_success)
		pr_err("Memory failure: %#lx: failed to unmap page (mapcount=%d)\n",
		       pfn, page_mapcount(hpage));

	/*
	 * try_to_unmap() might put mlocked page in lru cache, so call
	 * shake_page() again to ensure that it's flushed.
	 */
	अगर (mlocked)
		shake_page(hpage, 0);

	/*
	 * Now that the dirty bit has been propagated to the
	 * काष्ठा page and all unmaps करोne we can decide अगर
	 * समाप्तing is needed or not.  Only समाप्त when the page
	 * was dirty or the process is not restartable,
	 * otherwise the toसमाप्त list is merely
	 * मुक्तd.  When there was a problem unmapping earlier
	 * use a more क्रमce-full uncatchable समाप्त to prevent
	 * any accesses to the poisoned memory.
	 */
	क्रमceसमाप्त = PageDirty(hpage) || (flags & MF_MUST_KILL);
	समाप्त_procs(&toसमाप्त, क्रमceसमाप्त, !unmap_success, pfn, flags);

	वापस unmap_success;
पूर्ण

अटल पूर्णांक identअगरy_page_state(अचिन्हित दीर्घ pfn, काष्ठा page *p,
				अचिन्हित दीर्घ page_flags)
अणु
	काष्ठा page_state *ps;

	/*
	 * The first check uses the current page flags which may not have any
	 * relevant inक्रमmation. The second check with the saved page flags is
	 * carried out only अगर the first check can't determine the page status.
	 */
	क्रम (ps = error_states;; ps++)
		अगर ((p->flags & ps->mask) == ps->res)
			अवरोध;

	page_flags |= (p->flags & (1UL << PG_dirty));

	अगर (!ps->mask)
		क्रम (ps = error_states;; ps++)
			अगर ((page_flags & ps->mask) == ps->res)
				अवरोध;
	वापस page_action(ps, p, pfn);
पूर्ण

अटल पूर्णांक try_to_split_thp_page(काष्ठा page *page, स्थिर अक्षर *msg)
अणु
	lock_page(page);
	अगर (!PageAnon(page) || unlikely(split_huge_page(page))) अणु
		अचिन्हित दीर्घ pfn = page_to_pfn(page);

		unlock_page(page);
		अगर (!PageAnon(page))
			pr_info("%s: %#lx: non anonymous thp\n", msg, pfn);
		अन्यथा
			pr_info("%s: %#lx: thp split failed\n", msg, pfn);
		put_page(page);
		वापस -EBUSY;
	पूर्ण
	unlock_page(page);

	वापस 0;
पूर्ण

अटल पूर्णांक memory_failure_hugetlb(अचिन्हित दीर्घ pfn, पूर्णांक flags)
अणु
	काष्ठा page *p = pfn_to_page(pfn);
	काष्ठा page *head = compound_head(p);
	पूर्णांक res;
	अचिन्हित दीर्घ page_flags;

	अगर (TestSetPageHWPoison(head)) अणु
		pr_err("Memory failure: %#lx: already hardware poisoned\n",
		       pfn);
		वापस 0;
	पूर्ण

	num_poisoned_pages_inc();

	अगर (!(flags & MF_COUNT_INCREASED) && !get_hwpoison_page(p, flags, 0)) अणु
		/*
		 * Check "filter hit" and "race with other subpage."
		 */
		lock_page(head);
		अगर (PageHWPoison(head)) अणु
			अगर ((hwpoison_filter(p) && TestClearPageHWPoison(p))
			    || (p != head && TestSetPageHWPoison(head))) अणु
				num_poisoned_pages_dec();
				unlock_page(head);
				वापस 0;
			पूर्ण
		पूर्ण
		unlock_page(head);
		res = MF_FAILED;
		अगर (!dissolve_मुक्त_huge_page(p) && take_page_off_buddy(p)) अणु
			page_ref_inc(p);
			res = MF_RECOVERED;
		पूर्ण
		action_result(pfn, MF_MSG_FREE_HUGE, res);
		वापस res == MF_RECOVERED ? 0 : -EBUSY;
	पूर्ण

	lock_page(head);
	page_flags = head->flags;

	अगर (!PageHWPoison(head)) अणु
		pr_err("Memory failure: %#lx: just unpoisoned\n", pfn);
		num_poisoned_pages_dec();
		unlock_page(head);
		put_page(head);
		वापस 0;
	पूर्ण

	/*
	 * TODO: hwpoison क्रम pud-sized hugetlb करोesn't work right now, so
	 * simply disable it. In order to make it work properly, we need
	 * make sure that:
	 *  - conversion of a pud that maps an error hugetlb पूर्णांकo hwpoison
	 *    entry properly works, and
	 *  - other mm code walking over page table is aware of pud-aligned
	 *    hwpoison entries.
	 */
	अगर (huge_page_size(page_hstate(head)) > PMD_SIZE) अणु
		action_result(pfn, MF_MSG_NON_PMD_HUGE, MF_IGNORED);
		res = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (!hwpoison_user_mappings(p, pfn, flags, &head)) अणु
		action_result(pfn, MF_MSG_UNMAP_FAILED, MF_IGNORED);
		res = -EBUSY;
		जाओ out;
	पूर्ण

	res = identअगरy_page_state(pfn, p, page_flags);
out:
	unlock_page(head);
	वापस res;
पूर्ण

अटल पूर्णांक memory_failure_dev_pagemap(अचिन्हित दीर्घ pfn, पूर्णांक flags,
		काष्ठा dev_pagemap *pgmap)
अणु
	काष्ठा page *page = pfn_to_page(pfn);
	स्थिर bool unmap_success = true;
	अचिन्हित दीर्घ size = 0;
	काष्ठा to_समाप्त *tk;
	LIST_HEAD(toसमाप्त);
	पूर्णांक rc = -EBUSY;
	loff_t start;
	dax_entry_t cookie;

	अगर (flags & MF_COUNT_INCREASED)
		/*
		 * Drop the extra refcount in हाल we come from madvise().
		 */
		put_page(page);

	/* device metadata space is not recoverable */
	अगर (!pgmap_pfn_valid(pgmap, pfn)) अणु
		rc = -ENXIO;
		जाओ out;
	पूर्ण

	/*
	 * Prevent the inode from being मुक्तd जबतक we are पूर्णांकerrogating
	 * the address_space, typically this would be handled by
	 * lock_page(), but dax pages करो not use the page lock. This
	 * also prevents changes to the mapping of this pfn until
	 * poison संकेतing is complete.
	 */
	cookie = dax_lock_page(page);
	अगर (!cookie)
		जाओ out;

	अगर (hwpoison_filter(page)) अणु
		rc = 0;
		जाओ unlock;
	पूर्ण

	अगर (pgmap->type == MEMORY_DEVICE_PRIVATE) अणु
		/*
		 * TODO: Handle HMM pages which may need coordination
		 * with device-side memory.
		 */
		जाओ unlock;
	पूर्ण

	/*
	 * Use this flag as an indication that the dax page has been
	 * remapped UC to prevent speculative consumption of poison.
	 */
	SetPageHWPoison(page);

	/*
	 * Unlike System-RAM there is no possibility to swap in a
	 * dअगरferent physical page at a given भव address, so all
	 * userspace consumption of ZONE_DEVICE memory necessitates
	 * SIGBUS (i.e. MF_MUST_KILL)
	 */
	flags |= MF_ACTION_REQUIRED | MF_MUST_KILL;
	collect_procs(page, &toसमाप्त, flags & MF_ACTION_REQUIRED);

	list_क्रम_each_entry(tk, &toसमाप्त, nd)
		अगर (tk->size_shअगरt)
			size = max(size, 1UL << tk->size_shअगरt);
	अगर (size) अणु
		/*
		 * Unmap the largest mapping to aव्योम अवरोधing up
		 * device-dax mappings which are स्थिरant size. The
		 * actual size of the mapping being torn करोwn is
		 * communicated in siginfo, see समाप्त_proc()
		 */
		start = (page->index << PAGE_SHIFT) & ~(size - 1);
		unmap_mapping_range(page->mapping, start, size, 0);
	पूर्ण
	समाप्त_procs(&toसमाप्त, flags & MF_MUST_KILL, !unmap_success, pfn, flags);
	rc = 0;
unlock:
	dax_unlock_page(page, cookie);
out:
	/* drop pgmap ref acquired in caller */
	put_dev_pagemap(pgmap);
	action_result(pfn, MF_MSG_DAX, rc ? MF_FAILED : MF_RECOVERED);
	वापस rc;
पूर्ण

/**
 * memory_failure - Handle memory failure of a page.
 * @pfn: Page Number of the corrupted page
 * @flags: fine tune action taken
 *
 * This function is called by the low level machine check code
 * of an architecture when it detects hardware memory corruption
 * of a page. It tries its best to recover, which includes
 * dropping pages, समाप्तing processes etc.
 *
 * The function is primarily of use क्रम corruptions that
 * happen outside the current execution context (e.g. when
 * detected by a background scrubber)
 *
 * Must run in process context (e.g. a work queue) with पूर्णांकerrupts
 * enabled and no spinlocks hold.
 */
पूर्णांक memory_failure(अचिन्हित दीर्घ pfn, पूर्णांक flags)
अणु
	काष्ठा page *p;
	काष्ठा page *hpage;
	काष्ठा page *orig_head;
	काष्ठा dev_pagemap *pgmap;
	पूर्णांक res;
	अचिन्हित दीर्घ page_flags;
	bool retry = true;

	अगर (!sysctl_memory_failure_recovery)
		panic("Memory failure on page %lx", pfn);

	p = pfn_to_online_page(pfn);
	अगर (!p) अणु
		अगर (pfn_valid(pfn)) अणु
			pgmap = get_dev_pagemap(pfn, शून्य);
			अगर (pgmap)
				वापस memory_failure_dev_pagemap(pfn, flags,
								  pgmap);
		पूर्ण
		pr_err("Memory failure: %#lx: memory outside kernel control\n",
			pfn);
		वापस -ENXIO;
	पूर्ण

try_again:
	अगर (PageHuge(p))
		वापस memory_failure_hugetlb(pfn, flags);
	अगर (TestSetPageHWPoison(p)) अणु
		pr_err("Memory failure: %#lx: already hardware poisoned\n",
			pfn);
		वापस 0;
	पूर्ण

	orig_head = hpage = compound_head(p);
	num_poisoned_pages_inc();

	/*
	 * We need/can करो nothing about count=0 pages.
	 * 1) it's a मुक्त page, and thereक्रमe in safe hand:
	 *    prep_new_page() will be the gate keeper.
	 * 2) it's part of a non-compound high order page.
	 *    Implies some kernel user: cannot stop them from
	 *    R/W the page; let's pray that the page has been
	 *    used and will be मुक्तd some समय later.
	 * In fact it's dangerous to directly bump up page count from 0,
	 * that may make page_ref_मुक्तze()/page_ref_unमुक्तze() mismatch.
	 */
	अगर (!(flags & MF_COUNT_INCREASED) && !get_hwpoison_page(p, flags, 0)) अणु
		अगर (is_मुक्त_buddy_page(p)) अणु
			अगर (take_page_off_buddy(p)) अणु
				page_ref_inc(p);
				res = MF_RECOVERED;
			पूर्ण अन्यथा अणु
				/* We lost the race, try again */
				अगर (retry) अणु
					ClearPageHWPoison(p);
					num_poisoned_pages_dec();
					retry = false;
					जाओ try_again;
				पूर्ण
				res = MF_FAILED;
			पूर्ण
			action_result(pfn, MF_MSG_BUDDY, res);
			वापस res == MF_RECOVERED ? 0 : -EBUSY;
		पूर्ण अन्यथा अणु
			action_result(pfn, MF_MSG_KERNEL_HIGH_ORDER, MF_IGNORED);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	अगर (PageTransHuge(hpage)) अणु
		अगर (try_to_split_thp_page(p, "Memory Failure") < 0) अणु
			action_result(pfn, MF_MSG_UNSPLIT_THP, MF_IGNORED);
			वापस -EBUSY;
		पूर्ण
		VM_BUG_ON_PAGE(!page_count(p), p);
	पूर्ण

	/*
	 * We ignore non-LRU pages क्रम good reasons.
	 * - PG_locked is only well defined क्रम LRU pages and a few others
	 * - to aव्योम races with __SetPageLocked()
	 * - to aव्योम races with __SetPageSlab*() (and more non-atomic ops)
	 * The check (unnecessarily) ignores LRU pages being isolated and
	 * walked by the page reclaim code, however that's not a big loss.
	 */
	shake_page(p, 0);

	lock_page(p);

	/*
	 * The page could have changed compound pages during the locking.
	 * If this happens just bail out.
	 */
	अगर (PageCompound(p) && compound_head(p) != orig_head) अणु
		action_result(pfn, MF_MSG_DIFFERENT_COMPOUND, MF_IGNORED);
		res = -EBUSY;
		जाओ out;
	पूर्ण

	/*
	 * We use page flags to determine what action should be taken, but
	 * the flags can be modअगरied by the error containment action.  One
	 * example is an mlocked page, where PG_mlocked is cleared by
	 * page_हटाओ_rmap() in try_to_unmap_one(). So to determine page status
	 * correctly, we save a copy of the page flags at this समय.
	 */
	page_flags = p->flags;

	/*
	 * unpoison always clear PG_hwpoison inside page lock
	 */
	अगर (!PageHWPoison(p)) अणु
		pr_err("Memory failure: %#lx: just unpoisoned\n", pfn);
		num_poisoned_pages_dec();
		unlock_page(p);
		put_page(p);
		वापस 0;
	पूर्ण
	अगर (hwpoison_filter(p)) अणु
		अगर (TestClearPageHWPoison(p))
			num_poisoned_pages_dec();
		unlock_page(p);
		put_page(p);
		वापस 0;
	पूर्ण

	/*
	 * __munlock_pagevec may clear a ग_लिखोback page's LRU flag without
	 * page_lock. We need रुको ग_लिखोback completion क्रम this page or it
	 * may trigger vfs BUG जबतक evict inode.
	 */
	अगर (!PageTransTail(p) && !PageLRU(p) && !PageWriteback(p))
		जाओ identअगरy_page_state;

	/*
	 * It's very dअगरficult to mess with pages currently under IO
	 * and in many हालs impossible, so we just aव्योम it here.
	 */
	रुको_on_page_ग_लिखोback(p);

	/*
	 * Now take care of user space mappings.
	 * Abort on fail: __delete_from_page_cache() assumes unmapped page.
	 */
	अगर (!hwpoison_user_mappings(p, pfn, flags, &p)) अणु
		action_result(pfn, MF_MSG_UNMAP_FAILED, MF_IGNORED);
		res = -EBUSY;
		जाओ out;
	पूर्ण

	/*
	 * Torn करोwn by someone अन्यथा?
	 */
	अगर (PageLRU(p) && !PageSwapCache(p) && p->mapping == शून्य) अणु
		action_result(pfn, MF_MSG_TRUNCATED_LRU, MF_IGNORED);
		res = -EBUSY;
		जाओ out;
	पूर्ण

identअगरy_page_state:
	res = identअगरy_page_state(pfn, p, page_flags);
out:
	unlock_page(p);
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(memory_failure);

#घोषणा MEMORY_FAILURE_FIFO_ORDER	4
#घोषणा MEMORY_FAILURE_FIFO_SIZE	(1 << MEMORY_FAILURE_FIFO_ORDER)

काष्ठा memory_failure_entry अणु
	अचिन्हित दीर्घ pfn;
	पूर्णांक flags;
पूर्ण;

काष्ठा memory_failure_cpu अणु
	DECLARE_KFIFO(fअगरo, काष्ठा memory_failure_entry,
		      MEMORY_FAILURE_FIFO_SIZE);
	spinlock_t lock;
	काष्ठा work_काष्ठा work;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा memory_failure_cpu, memory_failure_cpu);

/**
 * memory_failure_queue - Schedule handling memory failure of a page.
 * @pfn: Page Number of the corrupted page
 * @flags: Flags क्रम memory failure handling
 *
 * This function is called by the low level hardware error handler
 * when it detects hardware memory corruption of a page. It schedules
 * the recovering of error page, including dropping pages, समाप्तing
 * processes etc.
 *
 * The function is primarily of use क्रम corruptions that
 * happen outside the current execution context (e.g. when
 * detected by a background scrubber)
 *
 * Can run in IRQ context.
 */
व्योम memory_failure_queue(अचिन्हित दीर्घ pfn, पूर्णांक flags)
अणु
	काष्ठा memory_failure_cpu *mf_cpu;
	अचिन्हित दीर्घ proc_flags;
	काष्ठा memory_failure_entry entry = अणु
		.pfn =		pfn,
		.flags =	flags,
	पूर्ण;

	mf_cpu = &get_cpu_var(memory_failure_cpu);
	spin_lock_irqsave(&mf_cpu->lock, proc_flags);
	अगर (kfअगरo_put(&mf_cpu->fअगरo, entry))
		schedule_work_on(smp_processor_id(), &mf_cpu->work);
	अन्यथा
		pr_err("Memory failure: buffer overflow when queuing memory failure at %#lx\n",
		       pfn);
	spin_unlock_irqrestore(&mf_cpu->lock, proc_flags);
	put_cpu_var(memory_failure_cpu);
पूर्ण
EXPORT_SYMBOL_GPL(memory_failure_queue);

अटल व्योम memory_failure_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा memory_failure_cpu *mf_cpu;
	काष्ठा memory_failure_entry entry = अणु 0, पूर्ण;
	अचिन्हित दीर्घ proc_flags;
	पूर्णांक gotten;

	mf_cpu = container_of(work, काष्ठा memory_failure_cpu, work);
	क्रम (;;) अणु
		spin_lock_irqsave(&mf_cpu->lock, proc_flags);
		gotten = kfअगरo_get(&mf_cpu->fअगरo, &entry);
		spin_unlock_irqrestore(&mf_cpu->lock, proc_flags);
		अगर (!gotten)
			अवरोध;
		अगर (entry.flags & MF_SOFT_OFFLINE)
			soft_offline_page(entry.pfn, entry.flags);
		अन्यथा
			memory_failure(entry.pfn, entry.flags);
	पूर्ण
पूर्ण

/*
 * Process memory_failure work queued on the specअगरied CPU.
 * Used to aव्योम वापस-to-userspace racing with the memory_failure workqueue.
 */
व्योम memory_failure_queue_kick(पूर्णांक cpu)
अणु
	काष्ठा memory_failure_cpu *mf_cpu;

	mf_cpu = &per_cpu(memory_failure_cpu, cpu);
	cancel_work_sync(&mf_cpu->work);
	memory_failure_work_func(&mf_cpu->work);
पूर्ण

अटल पूर्णांक __init memory_failure_init(व्योम)
अणु
	काष्ठा memory_failure_cpu *mf_cpu;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		mf_cpu = &per_cpu(memory_failure_cpu, cpu);
		spin_lock_init(&mf_cpu->lock);
		INIT_KFIFO(mf_cpu->fअगरo);
		INIT_WORK(&mf_cpu->work, memory_failure_work_func);
	पूर्ण

	वापस 0;
पूर्ण
core_initcall(memory_failure_init);

#घोषणा unpoison_pr_info(fmt, pfn, rs)			\
(अणु							\
	अगर (__ratelimit(rs))				\
		pr_info(fmt, pfn);			\
पूर्ण)

/**
 * unpoison_memory - Unpoison a previously poisoned page
 * @pfn: Page number of the to be unpoisoned page
 *
 * Software-unpoison a page that has been poisoned by
 * memory_failure() earlier.
 *
 * This is only करोne on the software-level, so it only works
 * क्रम linux injected failures, not real hardware failures
 *
 * Returns 0 क्रम success, otherwise -त्रुटि_सं.
 */
पूर्णांक unpoison_memory(अचिन्हित दीर्घ pfn)
अणु
	काष्ठा page *page;
	काष्ठा page *p;
	पूर्णांक मुक्तit = 0;
	अचिन्हित दीर्घ flags = 0;
	अटल DEFINE_RATELIMIT_STATE(unpoison_rs, DEFAULT_RATELIMIT_INTERVAL,
					DEFAULT_RATELIMIT_BURST);

	अगर (!pfn_valid(pfn))
		वापस -ENXIO;

	p = pfn_to_page(pfn);
	page = compound_head(p);

	अगर (!PageHWPoison(p)) अणु
		unpoison_pr_info("Unpoison: Page was already unpoisoned %#lx\n",
				 pfn, &unpoison_rs);
		वापस 0;
	पूर्ण

	अगर (page_count(page) > 1) अणु
		unpoison_pr_info("Unpoison: Someone grabs the hwpoison page %#lx\n",
				 pfn, &unpoison_rs);
		वापस 0;
	पूर्ण

	अगर (page_mapped(page)) अणु
		unpoison_pr_info("Unpoison: Someone maps the hwpoison page %#lx\n",
				 pfn, &unpoison_rs);
		वापस 0;
	पूर्ण

	अगर (page_mapping(page)) अणु
		unpoison_pr_info("Unpoison: the hwpoison page has non-NULL mapping %#lx\n",
				 pfn, &unpoison_rs);
		वापस 0;
	पूर्ण

	/*
	 * unpoison_memory() can encounter thp only when the thp is being
	 * worked by memory_failure() and the page lock is not held yet.
	 * In such हाल, we yield to memory_failure() and make unpoison fail.
	 */
	अगर (!PageHuge(page) && PageTransHuge(page)) अणु
		unpoison_pr_info("Unpoison: Memory failure is now running on %#lx\n",
				 pfn, &unpoison_rs);
		वापस 0;
	पूर्ण

	अगर (!get_hwpoison_page(p, flags, 0)) अणु
		अगर (TestClearPageHWPoison(p))
			num_poisoned_pages_dec();
		unpoison_pr_info("Unpoison: Software-unpoisoned free page %#lx\n",
				 pfn, &unpoison_rs);
		वापस 0;
	पूर्ण

	lock_page(page);
	/*
	 * This test is racy because PG_hwpoison is set outside of page lock.
	 * That's acceptable because that won't trigger kernel panic. Instead,
	 * the PG_hwpoison page will be caught and isolated on the entrance to
	 * the मुक्त buddy page pool.
	 */
	अगर (TestClearPageHWPoison(page)) अणु
		unpoison_pr_info("Unpoison: Software-unpoisoned page %#lx\n",
				 pfn, &unpoison_rs);
		num_poisoned_pages_dec();
		मुक्तit = 1;
	पूर्ण
	unlock_page(page);

	put_page(page);
	अगर (मुक्तit && !(pfn == my_zero_pfn(0) && page_count(p) == 1))
		put_page(page);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(unpoison_memory);

अटल bool isolate_page(काष्ठा page *page, काष्ठा list_head *pagelist)
अणु
	bool isolated = false;
	bool lru = PageLRU(page);

	अगर (PageHuge(page)) अणु
		isolated = isolate_huge_page(page, pagelist);
	पूर्ण अन्यथा अणु
		अगर (lru)
			isolated = !isolate_lru_page(page);
		अन्यथा
			isolated = !isolate_movable_page(page, ISOLATE_UNEVICTABLE);

		अगर (isolated)
			list_add(&page->lru, pagelist);
	पूर्ण

	अगर (isolated && lru)
		inc_node_page_state(page, NR_ISOLATED_ANON +
				    page_is_file_lru(page));

	/*
	 * If we succeed to isolate the page, we grabbed another refcount on
	 * the page, so we can safely drop the one we got from get_any_pages().
	 * If we failed to isolate the page, it means that we cannot go further
	 * and we will वापस an error, so drop the reference we got from
	 * get_any_pages() as well.
	 */
	put_page(page);
	वापस isolated;
पूर्ण

/*
 * __soft_offline_page handles hugetlb-pages and non-hugetlb pages.
 * If the page is a non-dirty unmapped page-cache page, it simply invalidates.
 * If the page is mapped, it migrates the contents over.
 */
अटल पूर्णांक __soft_offline_page(काष्ठा page *page)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ pfn = page_to_pfn(page);
	काष्ठा page *hpage = compound_head(page);
	अक्षर स्थिर *msg_page[] = अणु"page", "hugepage"पूर्ण;
	bool huge = PageHuge(page);
	LIST_HEAD(pagelist);
	काष्ठा migration_target_control mtc = अणु
		.nid = NUMA_NO_NODE,
		.gfp_mask = GFP_USER | __GFP_MOVABLE | __GFP_RETRY_MAYFAIL,
	पूर्ण;

	/*
	 * Check PageHWPoison again inside page lock because PageHWPoison
	 * is set by memory_failure() outside page lock. Note that
	 * memory_failure() also द्विगुन-checks PageHWPoison inside page lock,
	 * so there's no race between soft_offline_page() and memory_failure().
	 */
	lock_page(page);
	अगर (!PageHuge(page))
		रुको_on_page_ग_लिखोback(page);
	अगर (PageHWPoison(page)) अणु
		unlock_page(page);
		put_page(page);
		pr_info("soft offline: %#lx page already poisoned\n", pfn);
		वापस 0;
	पूर्ण

	अगर (!PageHuge(page))
		/*
		 * Try to invalidate first. This should work क्रम
		 * non dirty unmapped page cache pages.
		 */
		ret = invalidate_inode_page(page);
	unlock_page(page);

	/*
	 * RED-PEN would be better to keep it isolated here, but we
	 * would need to fix isolation locking first.
	 */
	अगर (ret) अणु
		pr_info("soft_offline: %#lx: invalidated\n", pfn);
		page_handle_poison(page, false, true);
		वापस 0;
	पूर्ण

	अगर (isolate_page(hpage, &pagelist)) अणु
		ret = migrate_pages(&pagelist, alloc_migration_target, शून्य,
			(अचिन्हित दीर्घ)&mtc, MIGRATE_SYNC, MR_MEMORY_FAILURE);
		अगर (!ret) अणु
			bool release = !huge;

			अगर (!page_handle_poison(page, huge, release))
				ret = -EBUSY;
		पूर्ण अन्यथा अणु
			अगर (!list_empty(&pagelist))
				putback_movable_pages(&pagelist);

			pr_info("soft offline: %#lx: %s migration failed %d, type %lx (%pGp)\n",
				pfn, msg_page[huge], ret, page->flags, &page->flags);
			अगर (ret > 0)
				ret = -EBUSY;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_info("soft offline: %#lx: %s isolation failed, page count %d, type %lx (%pGp)\n",
			pfn, msg_page[huge], page_count(page), page->flags, &page->flags);
		ret = -EBUSY;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक soft_offline_in_use_page(काष्ठा page *page)
अणु
	काष्ठा page *hpage = compound_head(page);

	अगर (!PageHuge(page) && PageTransHuge(hpage))
		अगर (try_to_split_thp_page(page, "soft offline") < 0)
			वापस -EBUSY;
	वापस __soft_offline_page(page);
पूर्ण

अटल पूर्णांक soft_offline_मुक्त_page(काष्ठा page *page)
अणु
	पूर्णांक rc = 0;

	अगर (!page_handle_poison(page, true, false))
		rc = -EBUSY;

	वापस rc;
पूर्ण

अटल व्योम put_ref_page(काष्ठा page *page)
अणु
	अगर (page)
		put_page(page);
पूर्ण

/**
 * soft_offline_page - Soft offline a page.
 * @pfn: pfn to soft-offline
 * @flags: flags. Same as memory_failure().
 *
 * Returns 0 on success, otherwise negated त्रुटि_सं.
 *
 * Soft offline a page, by migration or invalidation,
 * without समाप्तing anything. This is क्रम the हाल when
 * a page is not corrupted yet (so it's still valid to access),
 * but has had a number of corrected errors and is better taken
 * out.
 *
 * The actual policy on when to करो that is मुख्यtained by
 * user space.
 *
 * This should never impact any application or cause data loss,
 * however it might take some समय.
 *
 * This is not a 100% solution क्रम all memory, but tries to be
 * ``good enough'' क्रम the majority of memory.
 */
पूर्णांक soft_offline_page(अचिन्हित दीर्घ pfn, पूर्णांक flags)
अणु
	पूर्णांक ret;
	bool try_again = true;
	काष्ठा page *page, *ref_page = शून्य;

	WARN_ON_ONCE(!pfn_valid(pfn) && (flags & MF_COUNT_INCREASED));

	अगर (!pfn_valid(pfn))
		वापस -ENXIO;
	अगर (flags & MF_COUNT_INCREASED)
		ref_page = pfn_to_page(pfn);

	/* Only online pages can be soft-offlined (esp., not ZONE_DEVICE). */
	page = pfn_to_online_page(pfn);
	अगर (!page) अणु
		put_ref_page(ref_page);
		वापस -EIO;
	पूर्ण

	अगर (PageHWPoison(page)) अणु
		pr_info("%s: %#lx page already poisoned\n", __func__, pfn);
		put_ref_page(ref_page);
		वापस 0;
	पूर्ण

retry:
	get_online_mems();
	ret = get_hwpoison_page(page, flags, MF_SOFT_OFFLINE);
	put_online_mems();

	अगर (ret > 0) अणु
		ret = soft_offline_in_use_page(page);
	पूर्ण अन्यथा अगर (ret == 0) अणु
		अगर (soft_offline_मुक्त_page(page) && try_again) अणु
			try_again = false;
			जाओ retry;
		पूर्ण
	पूर्ण अन्यथा अगर (ret == -EIO) अणु
		pr_info("%s: %#lx: unknown page type: %lx (%pGp)\n",
			 __func__, pfn, page->flags, &page->flags);
	पूर्ण

	वापस ret;
पूर्ण
