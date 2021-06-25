<शैली गुरु>
/*
 * Copyright (C) 2009 Wind River Systems Inc
 *   Implemented by fredrik.markstrom@gmail.com and ivarholmqvist@gmail.com
 *
 * based on arch/mips/mm/fault.c which is:
 *
 * Copyright (C) 1995-2000 Ralf Baechle
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/extable.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/perf_event.h>

#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/traps.h>

#घोषणा EXC_SUPERV_INSN_ACCESS	9  /* Supervisor only inकाष्ठाion address */
#घोषणा EXC_SUPERV_DATA_ACCESS	11 /* Supervisor only data address */
#घोषणा EXC_X_PROTECTION_FAULT	13 /* TLB permission violation (x) */
#घोषणा EXC_R_PROTECTION_FAULT	14 /* TLB permission violation (r) */
#घोषणा EXC_W_PROTECTION_FAULT	15 /* TLB permission violation (w) */

/*
 * This routine handles page faults.  It determines the address,
 * and the problem, and then passes it off to one of the appropriate
 * routines.
 */
यंत्रlinkage व्योम करो_page_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ cause,
				अचिन्हित दीर्घ address)
अणु
	काष्ठा vm_area_काष्ठा *vma = शून्य;
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा mm_काष्ठा *mm = tsk->mm;
	पूर्णांक code = SEGV_MAPERR;
	vm_fault_t fault;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;

	cause >>= 2;

	/* Restart the inकाष्ठाion */
	regs->ea -= 4;

	/*
	 * We fault-in kernel-space भव memory on-demand. The
	 * 'reference' page table is init_mm.pgd.
	 *
	 * NOTE! We MUST NOT take any locks क्रम this हाल. We may
	 * be in an पूर्णांकerrupt or a critical region, and should
	 * only copy the inक्रमmation from the master page table,
	 * nothing more.
	 */
	अगर (unlikely(address >= VMALLOC_START && address <= VMALLOC_END)) अणु
		अगर (user_mode(regs))
			जाओ bad_area_nosemaphore;
		अन्यथा
			जाओ vदो_स्मृति_fault;
	पूर्ण

	अगर (unlikely(address >= TASK_SIZE))
		जाओ bad_area_nosemaphore;

	/*
	 * If we're in an पूर्णांकerrupt or have no user
	 * context, we must not take the fault..
	 */
	अगर (faulthandler_disabled() || !mm)
		जाओ bad_area_nosemaphore;

	अगर (user_mode(regs))
		flags |= FAULT_FLAG_USER;

	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, address);

	अगर (!mmap_पढ़ो_trylock(mm)) अणु
		अगर (!user_mode(regs) && !search_exception_tables(regs->ea))
			जाओ bad_area_nosemaphore;
retry:
		mmap_पढ़ो_lock(mm);
	पूर्ण

	vma = find_vma(mm, address);
	अगर (!vma)
		जाओ bad_area;
	अगर (vma->vm_start <= address)
		जाओ good_area;
	अगर (!(vma->vm_flags & VM_GROWSDOWN))
		जाओ bad_area;
	अगर (expand_stack(vma, address))
		जाओ bad_area;
/*
 * Ok, we have a good vm_area क्रम this memory access, so
 * we can handle it..
 */
good_area:
	code = SEGV_ACCERR;

	चयन (cause) अणु
	हाल EXC_SUPERV_INSN_ACCESS:
		जाओ bad_area;
	हाल EXC_SUPERV_DATA_ACCESS:
		जाओ bad_area;
	हाल EXC_X_PROTECTION_FAULT:
		अगर (!(vma->vm_flags & VM_EXEC))
			जाओ bad_area;
		अवरोध;
	हाल EXC_R_PROTECTION_FAULT:
		अगर (!(vma->vm_flags & VM_READ))
			जाओ bad_area;
		अवरोध;
	हाल EXC_W_PROTECTION_FAULT:
		अगर (!(vma->vm_flags & VM_WRITE))
			जाओ bad_area;
		flags = FAULT_FLAG_WRITE;
		अवरोध;
	पूर्ण

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
		अगर (fault & VM_FAULT_RETRY) अणु
			flags |= FAULT_FLAG_TRIED;

			/*
			 * No need to mmap_पढ़ो_unlock(mm) as we would
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
		अगर (unhandled_संकेत(current, संक_अंश) && prपूर्णांकk_ratelimit()) अणु
			pr_info("%s: unhandled page fault (%d) at 0x%08lx, "
				"cause %ld\n", current->comm, संक_अंश, address, cause);
			show_regs(regs);
		पूर्ण
		_exception(संक_अंश, regs, code, address);
		वापस;
	पूर्ण

no_context:
	/* Are we prepared to handle this kernel fault? */
	अगर (fixup_exception(regs))
		वापस;

	/*
	 * Oops. The kernel tried to access some bad page. We'll have to
	 * terminate things with extreme prejudice.
	 */
	bust_spinlocks(1);

	pr_alert("Unable to handle kernel %s at virtual address %08lx",
		address < PAGE_SIZE ? "NULL pointer dereference" :
		"paging request", address);
	pr_alert("ea = %08lx, ra = %08lx, cause = %ld\n", regs->ea, regs->ra,
		cause);
	panic("Oops");
	वापस;

/*
 * We ran out of memory, or some other thing happened to us that made
 * us unable to handle the page fault gracefully.
 */
out_of_memory:
	mmap_पढ़ो_unlock(mm);
	अगर (!user_mode(regs))
		जाओ no_context;
	pagefault_out_of_memory();
	वापस;

करो_sigbus:
	mmap_पढ़ो_unlock(mm);

	/* Kernel mode? Handle exceptions or die */
	अगर (!user_mode(regs))
		जाओ no_context;

	_exception(SIGBUS, regs, BUS_ADRERR, address);
	वापस;

vदो_स्मृति_fault:
	अणु
		/*
		 * Synchronize this task's top level page-table
		 * with the 'reference' page table.
		 *
		 * Do _not_ use "tsk" here. We might be inside
		 * an पूर्णांकerrupt in the middle of a task चयन..
		 */
		पूर्णांक offset = pgd_index(address);
		pgd_t *pgd, *pgd_k;
		p4d_t *p4d, *p4d_k;
		pud_t *pud, *pud_k;
		pmd_t *pmd, *pmd_k;
		pte_t *pte_k;

		pgd = pgd_current + offset;
		pgd_k = init_mm.pgd + offset;

		अगर (!pgd_present(*pgd_k))
			जाओ no_context;
		set_pgd(pgd, *pgd_k);

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
			जाओ no_context;
		set_pmd(pmd, *pmd_k);

		pte_k = pte_offset_kernel(pmd_k, address);
		अगर (!pte_present(*pte_k))
			जाओ no_context;

		flush_tlb_kernel_page(address);
		वापस;
	पूर्ण
पूर्ण
