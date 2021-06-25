<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/extable.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/mmu_context.h>
#समावेश <linux/perf_event.h>

पूर्णांक fixup_exception(काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा exception_table_entry *fixup;

	fixup = search_exception_tables(inकाष्ठाion_poपूर्णांकer(regs));
	अगर (fixup) अणु
		regs->pc = fixup->fixup;

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत bool is_ग_लिखो(काष्ठा pt_regs *regs)
अणु
	चयन (trap_no(regs)) अणु
	हाल VEC_TLBINVALIDS:
		वापस true;
	हाल VEC_TLBMODIFIED:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

#अगर_घोषित CONFIG_CPU_HAS_LDSTEX
अटल अंतरभूत व्योम csky_cmpxchg_fixup(काष्ठा pt_regs *regs)
अणु
	वापस;
पूर्ण
#अन्यथा
बाह्य अचिन्हित दीर्घ csky_cmpxchg_ldw;
बाह्य अचिन्हित दीर्घ csky_cmpxchg_stw;
अटल अंतरभूत व्योम csky_cmpxchg_fixup(काष्ठा pt_regs *regs)
अणु
	अगर (trap_no(regs) != VEC_TLBMODIFIED)
		वापस;

	अगर (inकाष्ठाion_poपूर्णांकer(regs) == csky_cmpxchg_stw)
		inकाष्ठाion_poपूर्णांकer_set(regs, csky_cmpxchg_ldw);
	वापस;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम no_context(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr)
अणु
	current->thपढ़ो.trap_no = trap_no(regs);

	/* Are we prepared to handle this kernel fault? */
	अगर (fixup_exception(regs))
		वापस;

	/*
	 * Oops. The kernel tried to access some bad page. We'll have to
	 * terminate things with extreme prejudice.
	 */
	bust_spinlocks(1);
	pr_alert("Unable to handle kernel paging request at virtual "
		 "addr 0x%08lx, pc: 0x%08lx\n", addr, regs->pc);
	die(regs, "Oops");
	करो_निकास(SIGKILL);
पूर्ण

अटल अंतरभूत व्योम mm_fault_error(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr, vm_fault_t fault)
अणु
	current->thपढ़ो.trap_no = trap_no(regs);

	अगर (fault & VM_FAULT_OOM) अणु
		/*
		 * We ran out of memory, call the OOM समाप्तer, and वापस the userspace
		 * (which will retry the fault, or समाप्त us अगर we got oom-समाप्तed).
		 */
		अगर (!user_mode(regs)) अणु
			no_context(regs, addr);
			वापस;
		पूर्ण
		pagefault_out_of_memory();
		वापस;
	पूर्ण अन्यथा अगर (fault & VM_FAULT_SIGBUS) अणु
		/* Kernel mode? Handle exceptions or die */
		अगर (!user_mode(regs)) अणु
			no_context(regs, addr);
			वापस;
		पूर्ण
		करो_trap(regs, SIGBUS, BUS_ADRERR, addr);
		वापस;
	पूर्ण
	BUG();
पूर्ण

अटल अंतरभूत व्योम bad_area(काष्ठा pt_regs *regs, काष्ठा mm_काष्ठा *mm, पूर्णांक code, अचिन्हित दीर्घ addr)
अणु
	/*
	 * Something tried to access memory that isn't in our memory map.
	 * Fix it, but check अगर it's kernel or user first.
	 */
	mmap_पढ़ो_unlock(mm);
	/* User mode accesses just cause a संक_अंश */
	अगर (user_mode(regs)) अणु
		करो_trap(regs, संक_अंश, code, addr);
		वापस;
	पूर्ण

	no_context(regs, addr);
पूर्ण

अटल अंतरभूत व्योम vदो_स्मृति_fault(काष्ठा pt_regs *regs, पूर्णांक code, अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgd, *pgd_k;
	pud_t *pud, *pud_k;
	pmd_t *pmd, *pmd_k;
	pte_t *pte_k;
	पूर्णांक offset;

	/* User mode accesses just cause a संक_अंश */
	अगर (user_mode(regs)) अणु
		करो_trap(regs, संक_अंश, code, addr);
		वापस;
	पूर्ण

	/*
	 * Synchronize this task's top level page-table
	 * with the 'reference' page table.
	 *
	 * Do _not_ use "tsk" here. We might be inside
	 * an पूर्णांकerrupt in the middle of a task चयन..
	 */
	offset = pgd_index(addr);

	pgd = get_pgd() + offset;
	pgd_k = init_mm.pgd + offset;

	अगर (!pgd_present(*pgd_k)) अणु
		no_context(regs, addr);
		वापस;
	पूर्ण
	set_pgd(pgd, *pgd_k);

	pud = (pud_t *)pgd;
	pud_k = (pud_t *)pgd_k;
	अगर (!pud_present(*pud_k)) अणु
		no_context(regs, addr);
		वापस;
	पूर्ण

	pmd = pmd_offset(pud, addr);
	pmd_k = pmd_offset(pud_k, addr);
	अगर (!pmd_present(*pmd_k)) अणु
		no_context(regs, addr);
		वापस;
	पूर्ण
	set_pmd(pmd, *pmd_k);

	pte_k = pte_offset_kernel(pmd_k, addr);
	अगर (!pte_present(*pte_k)) अणु
		no_context(regs, addr);
		वापस;
	पूर्ण

	flush_tlb_one(addr);
पूर्ण

अटल अंतरभूत bool access_error(काष्ठा pt_regs *regs, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (is_ग_लिखो(regs)) अणु
		अगर (!(vma->vm_flags & VM_WRITE))
			वापस true;
	पूर्ण अन्यथा अणु
		अगर (unlikely(!vma_is_accessible(vma)))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * This routine handles page faults.  It determines the address and the
 * problem, and then passes it off to one of the appropriate routines.
 */
यंत्रlinkage व्योम करो_page_fault(काष्ठा pt_regs *regs)
अणु
	काष्ठा task_काष्ठा *tsk;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ addr = पढ़ो_mmu_entryhi() & PAGE_MASK;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;
	पूर्णांक code = SEGV_MAPERR;
	vm_fault_t fault;

	tsk = current;
	mm = tsk->mm;

	csky_cmpxchg_fixup(regs);

	अगर (kprobe_page_fault(regs, tsk->thपढ़ो.trap_no))
		वापस;

	/*
	 * Fault-in kernel-space भव memory on-demand.
	 * The 'reference' page table is init_mm.pgd.
	 *
	 * NOTE! We MUST NOT take any locks क्रम this हाल. We may
	 * be in an पूर्णांकerrupt or a critical region, and should
	 * only copy the inक्रमmation from the master page table,
	 * nothing more.
	 */
	अगर (unlikely((addr >= VMALLOC_START) && (addr <= VMALLOC_END))) अणु
		vदो_स्मृति_fault(regs, code, addr);
		वापस;
	पूर्ण

	/* Enable पूर्णांकerrupts अगर they were enabled in the parent context. */
	अगर (likely(regs->sr & BIT(6)))
		local_irq_enable();

	/*
	 * If we're in an पूर्णांकerrupt, have no user context, or are running
	 * in an atomic region, then we must not take the fault.
	 */
	अगर (unlikely(faulthandler_disabled() || !mm)) अणु
		no_context(regs, addr);
		वापस;
	पूर्ण

	अगर (user_mode(regs))
		flags |= FAULT_FLAG_USER;

	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, addr);

	अगर (is_ग_लिखो(regs))
		flags |= FAULT_FLAG_WRITE;
retry:
	mmap_पढ़ो_lock(mm);
	vma = find_vma(mm, addr);
	अगर (unlikely(!vma)) अणु
		bad_area(regs, mm, code, addr);
		वापस;
	पूर्ण
	अगर (likely(vma->vm_start <= addr))
		जाओ good_area;
	अगर (unlikely(!(vma->vm_flags & VM_GROWSDOWN))) अणु
		bad_area(regs, mm, code, addr);
		वापस;
	पूर्ण
	अगर (unlikely(expand_stack(vma, addr))) अणु
		bad_area(regs, mm, code, addr);
		वापस;
	पूर्ण

	/*
	 * Ok, we have a good vm_area क्रम this memory access, so
	 * we can handle it.
	 */
good_area:
	code = SEGV_ACCERR;

	अगर (unlikely(access_error(regs, vma))) अणु
		bad_area(regs, mm, code, addr);
		वापस;
	पूर्ण

	/*
	 * If क्रम any reason at all we could not handle the fault,
	 * make sure we निकास gracefully rather than endlessly reकरो
	 * the fault.
	 */
	fault = handle_mm_fault(vma, addr, flags, regs);

	/*
	 * If we need to retry but a fatal संकेत is pending, handle the
	 * संकेत first. We करो not need to release the mmap_lock because it
	 * would alपढ़ोy be released in __lock_page_or_retry in mm/filemap.c.
	 */
	अगर (fault_संकेत_pending(fault, regs)) अणु
		अगर (!user_mode(regs))
			no_context(regs, addr);
		वापस;
	पूर्ण

	अगर (unlikely((fault & VM_FAULT_RETRY) && (flags & FAULT_FLAG_ALLOW_RETRY))) अणु
		flags |= FAULT_FLAG_TRIED;

		/*
		 * No need to mmap_पढ़ो_unlock(mm) as we would
		 * have alपढ़ोy released it in __lock_page_or_retry
		 * in mm/filemap.c.
		 */
		जाओ retry;
	पूर्ण

	mmap_पढ़ो_unlock(mm);

	अगर (unlikely(fault & VM_FAULT_ERROR)) अणु
		mm_fault_error(regs, addr, fault);
		वापस;
	पूर्ण
	वापस;
पूर्ण
