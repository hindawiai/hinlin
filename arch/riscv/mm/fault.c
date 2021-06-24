<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2009 Sunplus Core Technology Co., Ltd.
 *  Lennox Wu <lennox.wu@sunplusct.com>
 *  Chen Liqin <liqin.chen@sunplusct.com>
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */


#समावेश <linux/mm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/kprobes.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "../kernel/head.h"

अटल व्योम die_kernel_fault(स्थिर अक्षर *msg, अचिन्हित दीर्घ addr,
		काष्ठा pt_regs *regs)
अणु
	bust_spinlocks(1);

	pr_alert("Unable to handle kernel %s at virtual address " REG_FMT "\n", msg,
		addr);

	bust_spinlocks(0);
	die(regs, "Oops");
	करो_निकास(SIGKILL);
पूर्ण

अटल अंतरभूत व्योम no_context(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr)
अणु
	स्थिर अक्षर *msg;

	/* Are we prepared to handle this kernel fault? */
	अगर (fixup_exception(regs))
		वापस;

	/*
	 * Oops. The kernel tried to access some bad page. We'll have to
	 * terminate things with extreme prejudice.
	 */
	msg = (addr < PAGE_SIZE) ? "NULL pointer dereference" : "paging request";
	die_kernel_fault(msg, addr, regs);
पूर्ण

अटल अंतरभूत व्योम mm_fault_error(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr, vm_fault_t fault)
अणु
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
	p4d_t *p4d, *p4d_k;
	pmd_t *pmd, *pmd_k;
	pte_t *pte_k;
	पूर्णांक index;
	अचिन्हित दीर्घ pfn;

	/* User mode accesses just cause a संक_अंश */
	अगर (user_mode(regs))
		वापस करो_trap(regs, संक_अंश, code, addr);

	/*
	 * Synchronize this task's top level page-table
	 * with the 'reference' page table.
	 *
	 * Do _not_ use "tsk->active_mm->pgd" here.
	 * We might be inside an पूर्णांकerrupt in the middle
	 * of a task चयन.
	 */
	index = pgd_index(addr);
	pfn = csr_पढ़ो(CSR_SATP) & SATP_PPN;
	pgd = (pgd_t *)pfn_to_virt(pfn) + index;
	pgd_k = init_mm.pgd + index;

	अगर (!pgd_present(*pgd_k)) अणु
		no_context(regs, addr);
		वापस;
	पूर्ण
	set_pgd(pgd, *pgd_k);

	p4d = p4d_offset(pgd, addr);
	p4d_k = p4d_offset(pgd_k, addr);
	अगर (!p4d_present(*p4d_k)) अणु
		no_context(regs, addr);
		वापस;
	पूर्ण

	pud = pud_offset(p4d, addr);
	pud_k = pud_offset(p4d_k, addr);
	अगर (!pud_present(*pud_k)) अणु
		no_context(regs, addr);
		वापस;
	पूर्ण

	/*
	 * Since the vदो_स्मृति area is global, it is unnecessary
	 * to copy inभागidual PTEs
	 */
	pmd = pmd_offset(pud, addr);
	pmd_k = pmd_offset(pud_k, addr);
	अगर (!pmd_present(*pmd_k)) अणु
		no_context(regs, addr);
		वापस;
	पूर्ण
	set_pmd(pmd, *pmd_k);

	/*
	 * Make sure the actual PTE exists as well to
	 * catch kernel vदो_स्मृति-area accesses to non-mapped
	 * addresses. If we करोn't करो this, this will just
	 * silently loop क्रमever.
	 */
	pte_k = pte_offset_kernel(pmd_k, addr);
	अगर (!pte_present(*pte_k)) अणु
		no_context(regs, addr);
		वापस;
	पूर्ण

	/*
	 * The kernel assumes that TLBs करोn't cache invalid
	 * entries, but in RISC-V, SFENCE.VMA specअगरies an
	 * ordering स्थिरraपूर्णांक, not a cache flush; it is
	 * necessary even after writing invalid entries.
	 */
	local_flush_tlb_page(addr);
पूर्ण

अटल अंतरभूत bool access_error(अचिन्हित दीर्घ cause, काष्ठा vm_area_काष्ठा *vma)
अणु
	चयन (cause) अणु
	हाल EXC_INST_PAGE_FAULT:
		अगर (!(vma->vm_flags & VM_EXEC)) अणु
			वापस true;
		पूर्ण
		अवरोध;
	हाल EXC_LOAD_PAGE_FAULT:
		अगर (!(vma->vm_flags & VM_READ)) अणु
			वापस true;
		पूर्ण
		अवरोध;
	हाल EXC_STORE_PAGE_FAULT:
		अगर (!(vma->vm_flags & VM_WRITE)) अणु
			वापस true;
		पूर्ण
		अवरोध;
	शेष:
		panic("%s: unhandled cause %lu", __func__, cause);
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
	अचिन्हित दीर्घ addr, cause;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;
	पूर्णांक code = SEGV_MAPERR;
	vm_fault_t fault;

	cause = regs->cause;
	addr = regs->badaddr;

	tsk = current;
	mm = tsk->mm;

	अगर (kprobe_page_fault(regs, cause))
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

#अगर_घोषित CONFIG_64BIT
	/*
	 * Modules in 64bit kernels lie in their own भव region which is not
	 * in the vदो_स्मृति region, but dealing with page faults in this region
	 * or the vदो_स्मृति region amounts to करोing the same thing: checking that
	 * the mapping exists in init_mm.pgd and updating user page table, so
	 * just use vदो_स्मृति_fault.
	 */
	अगर (unlikely(addr >= MODULES_VADDR && addr < MODULES_END)) अणु
		vदो_स्मृति_fault(regs, code, addr);
		वापस;
	पूर्ण
#पूर्ण_अगर
	/* Enable पूर्णांकerrupts अगर they were enabled in the parent context. */
	अगर (likely(regs->status & SR_PIE))
		local_irq_enable();

	/*
	 * If we're in an पूर्णांकerrupt, have no user context, or are running
	 * in an atomic region, then we must not take the fault.
	 */
	अगर (unlikely(faulthandler_disabled() || !mm)) अणु
		tsk->thपढ़ो.bad_cause = cause;
		no_context(regs, addr);
		वापस;
	पूर्ण

	अगर (user_mode(regs))
		flags |= FAULT_FLAG_USER;

	अगर (!user_mode(regs) && addr < TASK_SIZE &&
			unlikely(!(regs->status & SR_SUM)))
		die_kernel_fault("access to user memory without uaccess routines",
				addr, regs);

	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, addr);

	अगर (cause == EXC_STORE_PAGE_FAULT)
		flags |= FAULT_FLAG_WRITE;
	अन्यथा अगर (cause == EXC_INST_PAGE_FAULT)
		flags |= FAULT_FLAG_INSTRUCTION;
retry:
	mmap_पढ़ो_lock(mm);
	vma = find_vma(mm, addr);
	अगर (unlikely(!vma)) अणु
		tsk->thपढ़ो.bad_cause = cause;
		bad_area(regs, mm, code, addr);
		वापस;
	पूर्ण
	अगर (likely(vma->vm_start <= addr))
		जाओ good_area;
	अगर (unlikely(!(vma->vm_flags & VM_GROWSDOWN))) अणु
		tsk->thपढ़ो.bad_cause = cause;
		bad_area(regs, mm, code, addr);
		वापस;
	पूर्ण
	अगर (unlikely(expand_stack(vma, addr))) अणु
		tsk->thपढ़ो.bad_cause = cause;
		bad_area(regs, mm, code, addr);
		वापस;
	पूर्ण

	/*
	 * Ok, we have a good vm_area क्रम this memory access, so
	 * we can handle it.
	 */
good_area:
	code = SEGV_ACCERR;

	अगर (unlikely(access_error(cause, vma))) अणु
		tsk->thपढ़ो.bad_cause = cause;
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
	अगर (fault_संकेत_pending(fault, regs))
		वापस;

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
		tsk->thपढ़ो.bad_cause = cause;
		mm_fault_error(regs, addr, fault);
		वापस;
	पूर्ण
	वापस;
पूर्ण
NOKPROBE_SYMBOL(करो_page_fault);
