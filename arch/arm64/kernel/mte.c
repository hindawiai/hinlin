<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 ARM Ltd.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/prctl.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/types.h>
#समावेश <linux/uपन.स>

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/mte.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sysreg.h>

u64 gcr_kernel_excl __ro_after_init;

अटल bool report_fault_once = true;

#अगर_घोषित CONFIG_KASAN_HW_TAGS
/* Whether the MTE asynchronous mode is enabled. */
DEFINE_STATIC_KEY_FALSE(mte_async_mode);
EXPORT_SYMBOL_GPL(mte_async_mode);
#पूर्ण_अगर

अटल व्योम mte_sync_page_tags(काष्ठा page *page, pte_t *ptep, bool check_swap)
अणु
	pte_t old_pte = READ_ONCE(*ptep);

	अगर (check_swap && is_swap_pte(old_pte)) अणु
		swp_entry_t entry = pte_to_swp_entry(old_pte);

		अगर (!non_swap_entry(entry) && mte_restore_tags(entry, page))
			वापस;
	पूर्ण

	page_kasan_tag_reset(page);
	/*
	 * We need smp_wmb() in between setting the flags and clearing the
	 * tags because अगर another thपढ़ो पढ़ोs page->flags and builds a
	 * tagged address out of it, there is an actual dependency to the
	 * memory access, but on the current thपढ़ो we करो not guarantee that
	 * the new page->flags are visible beक्रमe the tags were updated.
	 */
	smp_wmb();
	mte_clear_page_tags(page_address(page));
पूर्ण

व्योम mte_sync_tags(pte_t *ptep, pte_t pte)
अणु
	काष्ठा page *page = pte_page(pte);
	दीर्घ i, nr_pages = compound_nr(page);
	bool check_swap = nr_pages == 1;

	/* अगर PG_mte_tagged is set, tags have alपढ़ोy been initialised */
	क्रम (i = 0; i < nr_pages; i++, page++) अणु
		अगर (!test_and_set_bit(PG_mte_tagged, &page->flags))
			mte_sync_page_tags(page, ptep, check_swap);
	पूर्ण
पूर्ण

पूर्णांक स_भेद_pages(काष्ठा page *page1, काष्ठा page *page2)
अणु
	अक्षर *addr1, *addr2;
	पूर्णांक ret;

	addr1 = page_address(page1);
	addr2 = page_address(page2);
	ret = स_भेद(addr1, addr2, PAGE_SIZE);

	अगर (!प्रणाली_supports_mte() || ret)
		वापस ret;

	/*
	 * If the page content is identical but at least one of the pages is
	 * tagged, वापस non-zero to aव्योम KSM merging. If only one of the
	 * pages is tagged, set_pte_at() may zero or change the tags of the
	 * other page via mte_sync_tags().
	 */
	अगर (test_bit(PG_mte_tagged, &page1->flags) ||
	    test_bit(PG_mte_tagged, &page2->flags))
		वापस addr1 != addr2;

	वापस ret;
पूर्ण

व्योम mte_init_tags(u64 max_tag)
अणु
	अटल bool gcr_kernel_excl_initialized;

	अगर (!gcr_kernel_excl_initialized) अणु
		/*
		 * The क्रमmat of the tags in KASAN is 0xFF and in MTE is 0xF.
		 * This conversion extracts an MTE tag from a KASAN tag.
		 */
		u64 incl = GENMASK(FIELD_GET(MTE_TAG_MASK >> MTE_TAG_SHIFT,
					     max_tag), 0);

		gcr_kernel_excl = ~incl & SYS_GCR_EL1_EXCL_MASK;
		gcr_kernel_excl_initialized = true;
	पूर्ण

	/* Enable the kernel exclude mask क्रम अक्रमom tags generation. */
	ग_लिखो_sysreg_s(SYS_GCR_EL1_RRND | gcr_kernel_excl, SYS_GCR_EL1);
पूर्ण

अटल अंतरभूत व्योम __mte_enable_kernel(स्थिर अक्षर *mode, अचिन्हित दीर्घ tcf)
अणु
	/* Enable MTE Sync Mode क्रम EL1. */
	sysreg_clear_set(sctlr_el1, SCTLR_ELx_TCF_MASK, tcf);
	isb();

	pr_info_once("MTE: enabled in %s mode at EL1\n", mode);
पूर्ण

#अगर_घोषित CONFIG_KASAN_HW_TAGS
व्योम mte_enable_kernel_sync(व्योम)
अणु
	/*
	 * Make sure we enter this function when no PE has set
	 * async mode previously.
	 */
	WARN_ONCE(प्रणाली_uses_mte_async_mode(),
			"MTE async mode enabled system wide!");

	__mte_enable_kernel("synchronous", SCTLR_ELx_TCF_SYNC);
पूर्ण

व्योम mte_enable_kernel_async(व्योम)
अणु
	__mte_enable_kernel("asynchronous", SCTLR_ELx_TCF_ASYNC);

	/*
	 * MTE async mode is set प्रणाली wide by the first PE that
	 * executes this function.
	 *
	 * Note: If in future KASAN acquires a runसमय चयनing
	 * mode in between sync and async, this strategy needs
	 * to be reviewed.
	 */
	अगर (!प्रणाली_uses_mte_async_mode())
		अटल_branch_enable(&mte_async_mode);
पूर्ण
#पूर्ण_अगर

व्योम mte_set_report_once(bool state)
अणु
	WRITE_ONCE(report_fault_once, state);
पूर्ण

bool mte_report_once(व्योम)
अणु
	वापस READ_ONCE(report_fault_once);
पूर्ण

#अगर_घोषित CONFIG_KASAN_HW_TAGS
व्योम mte_check_tfsr_el1(व्योम)
अणु
	u64 tfsr_el1;

	अगर (!प्रणाली_supports_mte())
		वापस;

	tfsr_el1 = पढ़ो_sysreg_s(SYS_TFSR_EL1);

	अगर (unlikely(tfsr_el1 & SYS_TFSR_EL1_TF1)) अणु
		/*
		 * Note: isb() is not required after this direct ग_लिखो
		 * because there is no indirect पढ़ो subsequent to it
		 * (per ARM DDI 0487F.c table D13-1).
		 */
		ग_लिखो_sysreg_s(0, SYS_TFSR_EL1);

		kasan_report_async();
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम update_gcr_el1_excl(u64 excl)
अणु

	/*
	 * Note that the mask controlled by the user via prctl() is an
	 * include जबतक GCR_EL1 accepts an exclude mask.
	 * No need क्रम ISB since this only affects EL0 currently, implicit
	 * with ERET.
	 */
	sysreg_clear_set_s(SYS_GCR_EL1, SYS_GCR_EL1_EXCL_MASK, excl);
पूर्ण

अटल व्योम set_gcr_el1_excl(u64 excl)
अणु
	current->thपढ़ो.gcr_user_excl = excl;

	/*
	 * SYS_GCR_EL1 will be set to current->thपढ़ो.gcr_user_excl value
	 * by mte_set_user_gcr() in kernel_निकास,
	 */
पूर्ण

व्योम mte_thपढ़ो_init_user(व्योम)
अणु
	अगर (!प्रणाली_supports_mte())
		वापस;

	/* clear any pending asynchronous tag fault */
	dsb(ish);
	ग_लिखो_sysreg_s(0, SYS_TFSRE0_EL1);
	clear_thपढ़ो_flag(TIF_MTE_ASYNC_FAULT);
	/* disable tag checking */
	set_task_sctlr_el1((current->thपढ़ो.sctlr_user & ~SCTLR_EL1_TCF0_MASK) |
			   SCTLR_EL1_TCF0_NONE);
	/* reset tag generation mask */
	set_gcr_el1_excl(SYS_GCR_EL1_EXCL_MASK);
पूर्ण

व्योम mte_thपढ़ो_चयन(काष्ठा task_काष्ठा *next)
अणु
	/*
	 * Check अगर an async tag exception occurred at EL1.
	 *
	 * Note: On the context चयन path we rely on the dsb() present
	 * in __चयन_to() to guarantee that the indirect ग_लिखोs to TFSR_EL1
	 * are synchronized beक्रमe this poपूर्णांक.
	 */
	isb();
	mte_check_tfsr_el1();
पूर्ण

व्योम mte_suspend_enter(व्योम)
अणु
	अगर (!प्रणाली_supports_mte())
		वापस;

	/*
	 * The barriers are required to guarantee that the indirect ग_लिखोs
	 * to TFSR_EL1 are synchronized beक्रमe we report the state.
	 */
	dsb(nsh);
	isb();

	/* Report SYS_TFSR_EL1 beक्रमe suspend entry */
	mte_check_tfsr_el1();
पूर्ण

व्योम mte_suspend_निकास(व्योम)
अणु
	अगर (!प्रणाली_supports_mte())
		वापस;

	update_gcr_el1_excl(gcr_kernel_excl);
पूर्ण

दीर्घ set_mte_ctrl(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ arg)
अणु
	u64 sctlr = task->thपढ़ो.sctlr_user & ~SCTLR_EL1_TCF0_MASK;
	u64 gcr_excl = ~((arg & PR_MTE_TAG_MASK) >> PR_MTE_TAG_SHIFT) &
		       SYS_GCR_EL1_EXCL_MASK;

	अगर (!प्रणाली_supports_mte())
		वापस 0;

	चयन (arg & PR_MTE_TCF_MASK) अणु
	हाल PR_MTE_TCF_NONE:
		sctlr |= SCTLR_EL1_TCF0_NONE;
		अवरोध;
	हाल PR_MTE_TCF_SYNC:
		sctlr |= SCTLR_EL1_TCF0_SYNC;
		अवरोध;
	हाल PR_MTE_TCF_ASYNC:
		sctlr |= SCTLR_EL1_TCF0_ASYNC;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (task != current) अणु
		task->thपढ़ो.sctlr_user = sctlr;
		task->thपढ़ो.gcr_user_excl = gcr_excl;
	पूर्ण अन्यथा अणु
		set_task_sctlr_el1(sctlr);
		set_gcr_el1_excl(gcr_excl);
	पूर्ण

	वापस 0;
पूर्ण

दीर्घ get_mte_ctrl(काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ ret;
	u64 incl = ~task->thपढ़ो.gcr_user_excl & SYS_GCR_EL1_EXCL_MASK;

	अगर (!प्रणाली_supports_mte())
		वापस 0;

	ret = incl << PR_MTE_TAG_SHIFT;

	चयन (task->thपढ़ो.sctlr_user & SCTLR_EL1_TCF0_MASK) अणु
	हाल SCTLR_EL1_TCF0_NONE:
		ret |= PR_MTE_TCF_NONE;
		अवरोध;
	हाल SCTLR_EL1_TCF0_SYNC:
		ret |= PR_MTE_TCF_SYNC;
		अवरोध;
	हाल SCTLR_EL1_TCF0_ASYNC:
		ret |= PR_MTE_TCF_ASYNC;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Access MTE tags in another process' address space as given in mm. Update
 * the number of tags copied. Return 0 अगर any tags copied, error otherwise.
 * Inspired by __access_remote_vm().
 */
अटल पूर्णांक __access_remote_tags(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				काष्ठा iovec *kiov, अचिन्हित पूर्णांक gup_flags)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	व्योम __user *buf = kiov->iov_base;
	माप_प्रकार len = kiov->iov_len;
	पूर्णांक ret;
	पूर्णांक ग_लिखो = gup_flags & FOLL_WRITE;

	अगर (!access_ok(buf, len))
		वापस -EFAULT;

	अगर (mmap_पढ़ो_lock_समाप्तable(mm))
		वापस -EIO;

	जबतक (len) अणु
		अचिन्हित दीर्घ tags, offset;
		व्योम *maddr;
		काष्ठा page *page = शून्य;

		ret = get_user_pages_remote(mm, addr, 1, gup_flags, &page,
					    &vma, शून्य);
		अगर (ret <= 0)
			अवरोध;

		/*
		 * Only copy tags अगर the page has been mapped as PROT_MTE
		 * (PG_mte_tagged set). Otherwise the tags are not valid and
		 * not accessible to user. Moreover, an mprotect(PROT_MTE)
		 * would cause the existing tags to be cleared अगर the page
		 * was never mapped with PROT_MTE.
		 */
		अगर (!(vma->vm_flags & VM_MTE)) अणु
			ret = -EOPNOTSUPP;
			put_page(page);
			अवरोध;
		पूर्ण
		WARN_ON_ONCE(!test_bit(PG_mte_tagged, &page->flags));

		/* limit access to the end of the page */
		offset = offset_in_page(addr);
		tags = min(len, (PAGE_SIZE - offset) / MTE_GRANULE_SIZE);

		maddr = page_address(page);
		अगर (ग_लिखो) अणु
			tags = mte_copy_tags_from_user(maddr + offset, buf, tags);
			set_page_dirty_lock(page);
		पूर्ण अन्यथा अणु
			tags = mte_copy_tags_to_user(buf, maddr + offset, tags);
		पूर्ण
		put_page(page);

		/* error accessing the tracer's buffer */
		अगर (!tags)
			अवरोध;

		len -= tags;
		buf += tags;
		addr += tags * MTE_GRANULE_SIZE;
	पूर्ण
	mmap_पढ़ो_unlock(mm);

	/* वापस an error अगर no tags copied */
	kiov->iov_len = buf - kiov->iov_base;
	अगर (!kiov->iov_len) अणु
		/* check क्रम error accessing the tracee's address space */
		अगर (ret <= 0)
			वापस -EIO;
		अन्यथा
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Copy MTE tags in another process' address space at 'addr' to/from tracer's
 * iovec buffer. Return 0 on success. Inspired by ptrace_access_vm().
 */
अटल पूर्णांक access_remote_tags(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ addr,
			      काष्ठा iovec *kiov, अचिन्हित पूर्णांक gup_flags)
अणु
	काष्ठा mm_काष्ठा *mm;
	पूर्णांक ret;

	mm = get_task_mm(tsk);
	अगर (!mm)
		वापस -EPERM;

	अगर (!tsk->ptrace || (current != tsk->parent) ||
	    ((get_dumpable(mm) != SUID_DUMP_USER) &&
	     !ptracer_capable(tsk, mm->user_ns))) अणु
		mmput(mm);
		वापस -EPERM;
	पूर्ण

	ret = __access_remote_tags(mm, addr, kiov, gup_flags);
	mmput(mm);

	वापस ret;
पूर्ण

पूर्णांक mte_ptrace_copy_tags(काष्ठा task_काष्ठा *child, दीर्घ request,
			 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	पूर्णांक ret;
	काष्ठा iovec kiov;
	काष्ठा iovec __user *uiov = (व्योम __user *)data;
	अचिन्हित पूर्णांक gup_flags = FOLL_FORCE;

	अगर (!प्रणाली_supports_mte())
		वापस -EIO;

	अगर (get_user(kiov.iov_base, &uiov->iov_base) ||
	    get_user(kiov.iov_len, &uiov->iov_len))
		वापस -EFAULT;

	अगर (request == PTRACE_POKEMTETAGS)
		gup_flags |= FOLL_WRITE;

	/* align addr to the MTE tag granule */
	addr &= MTE_GRANULE_MASK;

	ret = access_remote_tags(child, addr, &kiov, gup_flags);
	अगर (!ret)
		ret = put_user(kiov.iov_len, &uiov->iov_len);

	वापस ret;
पूर्ण
