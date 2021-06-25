<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenRISC fault.c
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 */

#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/extable.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/perf_event.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/siginfo.h>
#समावेश <यंत्र/संकेत.स>

#घोषणा NUM_TLB_ENTRIES 64
#घोषणा TLB_OFFSET(add) (((add) >> PAGE_SHIFT) & (NUM_TLB_ENTRIES-1))

अचिन्हित दीर्घ pte_misses;	/* updated by करो_page_fault() */
अचिन्हित दीर्घ pte_errors;	/* updated by करो_page_fault() */

/* __PHX__ :: - check the vदो_स्मृति_fault in करो_page_fault()
 *            - also look पूर्णांकo include/यंत्र-or32/mmu_context.h
 */
अस्थिर pgd_t *current_pgd[NR_CPUS];

बाह्य व्योम die(अक्षर *, काष्ठा pt_regs *, दीर्घ);

/*
 * This routine handles page faults.  It determines the address,
 * and the problem, and then passes it off to one of the appropriate
 * routines.
 *
 * If this routine detects a bad access, it वापसs 1, otherwise it
 * वापसs 0.
 */

यंत्रlinkage व्योम करो_page_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address,
			      अचिन्हित दीर्घ vector, पूर्णांक ग_लिखो_acc)
अणु
	काष्ठा task_काष्ठा *tsk;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक si_code;
	vm_fault_t fault;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;

	tsk = current;

	/*
	 * We fault-in kernel-space भव memory on-demand. The
	 * 'reference' page table is init_mm.pgd.
	 *
	 * NOTE! We MUST NOT take any locks क्रम this हाल. We may
	 * be in an पूर्णांकerrupt or a critical region, and should
	 * only copy the inक्रमmation from the master page table,
	 * nothing more.
	 *
	 * NOTE2: This is करोne so that, when updating the vदो_स्मृति
	 * mappings we करोn't have to walk all processes pgdirs and
	 * add the high mappings all at once. Instead we करो it as they
	 * are used. However vदो_स्मृति'ed page entries have the PAGE_GLOBAL
	 * bit set so someबार the TLB can use a lingering entry.
	 *
	 * This verअगरies that the fault happens in kernel space
	 * and that the fault was not a protection error.
	 */

	अगर (address >= VMALLOC_START &&
	    (vector != 0x300 && vector != 0x400) &&
	    !user_mode(regs))
		जाओ vदो_स्मृति_fault;

	/* If exceptions were enabled, we can reenable them here */
	अगर (user_mode(regs)) अणु
		/* Exception was in userspace: reenable पूर्णांकerrupts */
		local_irq_enable();
		flags |= FAULT_FLAG_USER;
	पूर्ण अन्यथा अणु
		/* If exception was in a syscall, then IRQ's may have
		 * been enabled or disabled.  If they were enabled,
		 * reenable them.
		 */
		अगर (regs->sr && (SPR_SR_IEE | SPR_SR_TEE))
			local_irq_enable();
	पूर्ण

	mm = tsk->mm;
	si_code = SEGV_MAPERR;

	/*
	 * If we're in an पूर्णांकerrupt or have no user
	 * context, we must not take the fault..
	 */

	अगर (in_पूर्णांकerrupt() || !mm)
		जाओ no_context;

	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, address);

retry:
	mmap_पढ़ो_lock(mm);
	vma = find_vma(mm, address);

	अगर (!vma)
		जाओ bad_area;

	अगर (vma->vm_start <= address)
		जाओ good_area;

	अगर (!(vma->vm_flags & VM_GROWSDOWN))
		जाओ bad_area;

	अगर (user_mode(regs)) अणु
		/*
		 * accessing the stack below usp is always a bug.
		 * we get page-aligned addresses so we can only check
		 * अगर we're within a page from usp, but that might be
		 * enough to catch brutal errors at least.
		 */
		अगर (address + PAGE_SIZE < regs->sp)
			जाओ bad_area;
	पूर्ण
	अगर (expand_stack(vma, address))
		जाओ bad_area;

	/*
	 * Ok, we have a good vm_area क्रम this memory access, so
	 * we can handle it..
	 */

good_area:
	si_code = SEGV_ACCERR;

	/* first करो some preliminary protection checks */

	अगर (ग_लिखो_acc) अणु
		अगर (!(vma->vm_flags & VM_WRITE))
			जाओ bad_area;
		flags |= FAULT_FLAG_WRITE;
	पूर्ण अन्यथा अणु
		/* not present */
		अगर (!(vma->vm_flags & (VM_READ | VM_EXEC)))
			जाओ bad_area;
	पूर्ण

	/* are we trying to execute nonexecutable area */
	अगर ((vector == 0x400) && !(vma->vm_page_prot.pgprot & _PAGE_EXEC))
		जाओ bad_area;

	/*
	 * If क्रम any reason at all we couldn't handle the fault,
	 * make sure we निकास gracefully rather than endlessly reकरो
	 * the fault.
	 */

	fault = handle_mm_fault(vma, address, flags, regs);

	अगर (fault_संकेत_pending(fault, regs))
		वापस;

	अगर (unlikely(fault & VM_FAULT_ERROR)) अणु
		अगर (fault & VM_FAULT_OOM)
			जाओ out_of_memory;
		अन्यथा अगर (fault & VM_FAULT_संक_अंश)
			जाओ bad_area;
		अन्यथा अगर (fault & VM_FAULT_SIGBUS)
			जाओ करो_sigbus;
		BUG();
	पूर्ण

	अगर (flags & FAULT_FLAG_ALLOW_RETRY) अणु
		/*RGD modeled on Cris */
		अगर (fault & VM_FAULT_RETRY) अणु
			flags |= FAULT_FLAG_TRIED;

			 /* No need to mmap_पढ़ो_unlock(mm) as we would
			 * have alपढ़ोy released it in __lock_page_or_retry
			 * in mm/filemap.c.
			 */

			जाओ retry;
		पूर्ण
	पूर्ण

	mmap_पढ़ो_unlock(mm);
	वापस;

	/*
	 * Something tried to access memory that isn't in our memory map..
	 * Fix it, but check अगर it's kernel or user first..
	 */

bad_area:
	mmap_पढ़ो_unlock(mm);

bad_area_nosemaphore:

	/* User mode accesses just cause a संक_अंश */

	अगर (user_mode(regs)) अणु
		क्रमce_sig_fault(संक_अंश, si_code, (व्योम __user *)address);
		वापस;
	पूर्ण

no_context:

	/* Are we prepared to handle this kernel fault?
	 *
	 * (The kernel has valid exception-poपूर्णांकs in the source
	 *  when it acesses user-memory. When it fails in one
	 *  of those poपूर्णांकs, we find it in a table and करो a jump
	 *  to some fixup code that loads an appropriate error
	 *  code)
	 */

	अणु
		स्थिर काष्ठा exception_table_entry *entry;

		__यंत्र__ __अस्थिर__("l.nop 42");

		अगर ((entry = search_exception_tables(regs->pc)) != शून्य) अणु
			/* Adjust the inकाष्ठाion poपूर्णांकer in the stackframe */
			regs->pc = entry->fixup;
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * Oops. The kernel tried to access some bad page. We'll have to
	 * terminate things with extreme prejudice.
	 */

	अगर ((अचिन्हित दीर्घ)(address) < PAGE_SIZE)
		prपूर्णांकk(KERN_ALERT
		       "Unable to handle kernel NULL pointer dereference");
	अन्यथा
		prपूर्णांकk(KERN_ALERT "Unable to handle kernel access");
	prपूर्णांकk(" at virtual address 0x%08lx\n", address);

	die("Oops", regs, ग_लिखो_acc);

	करो_निकास(SIGKILL);

	/*
	 * We ran out of memory, or some other thing happened to us that made
	 * us unable to handle the page fault gracefully.
	 */

out_of_memory:
	__यंत्र__ __अस्थिर__("l.nop 42");
	__यंत्र__ __अस्थिर__("l.nop 1");

	mmap_पढ़ो_unlock(mm);
	अगर (!user_mode(regs))
		जाओ no_context;
	pagefault_out_of_memory();
	वापस;

करो_sigbus:
	mmap_पढ़ो_unlock(mm);

	/*
	 * Send a sigbus, regardless of whether we were in kernel
	 * or user mode.
	 */
	क्रमce_sig_fault(SIGBUS, BUS_ADRERR, (व्योम __user *)address);

	/* Kernel mode? Handle exceptions or die */
	अगर (!user_mode(regs))
		जाओ no_context;
	वापस;

vदो_स्मृति_fault:
	अणु
		/*
		 * Synchronize this task's top level page-table
		 * with the 'reference' page table.
		 *
		 * Use current_pgd instead of tsk->active_mm->pgd
		 * since the latter might be unavailable अगर this
		 * code is executed in a misक्रमtunately run irq
		 * (like inside schedule() between चयन_mm and
		 *  चयन_to...).
		 */

		पूर्णांक offset = pgd_index(address);
		pgd_t *pgd, *pgd_k;
		p4d_t *p4d, *p4d_k;
		pud_t *pud, *pud_k;
		pmd_t *pmd, *pmd_k;
		pte_t *pte_k;

/*
		phx_warn("do_page_fault(): vmalloc_fault will not work, "
			 "since current_pgd assign a proper value somewhere\n"
			 "anyhow we don't need this at the moment\n");

		phx_mmu("vmalloc_fault");
*/
		pgd = (pgd_t *)current_pgd[smp_processor_id()] + offset;
		pgd_k = init_mm.pgd + offset;

		/* Since we're two-level, we don't need to करो both
		 * set_pgd and set_pmd (they करो the same thing). If
		 * we go three-level at some poपूर्णांक, करो the right thing
		 * with pgd_present and set_pgd here.
		 *
		 * Also, since the vदो_स्मृति area is global, we करोn't
		 * need to copy inभागidual PTE's, it is enough to
		 * copy the pgd poपूर्णांकer पूर्णांकo the pte page of the
		 * root task. If that is there, we'll find our pte अगर
		 * it exists.
		 */

		p4d = p4d_offset(pgd, address);
		p4d_k = p4d_offset(pgd_k, address);
		अगर (!p4d_present(*p4d_k))
			जाओ no_context;

		pud = pud_offset(p4d, address);
		pud_k = pud_offset(p4d_k, address);
		अगर (!pud_present(*pud_k))
			जाओ no_context;

		pmd = pmd_offset(pud, address);
		pmd_k = pmd_offset(pud_k, address);

		अगर (!pmd_present(*pmd_k))
			जाओ bad_area_nosemaphore;

		set_pmd(pmd, *pmd_k);

		/* Make sure the actual PTE exists as well to
		 * catch kernel vदो_स्मृति-area accesses to non-mapped
		 * addresses. If we करोn't करो this, this will just
		 * silently loop क्रमever.
		 */

		pte_k = pte_offset_kernel(pmd_k, address);
		अगर (!pte_present(*pte_k))
			जाओ no_context;

		वापस;
	पूर्ण
पूर्ण
