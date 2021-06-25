<शैली गुरु>
// TODO VM_EXEC flag work-around, cache aliasing
/*
 * arch/xtensa/mm/fault.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2010 Tensilica Inc.
 *
 * Chris Zankel <chris@zankel.net>
 * Joe Taylor	<joe@tensilica.com, joetylr@yahoo.com>
 */

#समावेश <linux/mm.h>
#समावेश <linux/extable.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/hardirq.h>

DEFINE_PER_CPU(अचिन्हित दीर्घ, asid_cache) = ASID_USER_FIRST;
व्योम bad_page_fault(काष्ठा pt_regs*, अचिन्हित दीर्घ, पूर्णांक);

/*
 * This routine handles page faults.  It determines the address,
 * and the problem, and then passes it off to one of the appropriate
 * routines.
 *
 * Note: करोes not handle Miss and MultiHit.
 */

व्योम करो_page_fault(काष्ठा pt_regs *regs)
अणु
	काष्ठा vm_area_काष्ठा * vma;
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित पूर्णांक exccause = regs->exccause;
	अचिन्हित पूर्णांक address = regs->excvaddr;
	पूर्णांक code;

	पूर्णांक is_ग_लिखो, is_exec;
	vm_fault_t fault;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;

	code = SEGV_MAPERR;

	/* We fault-in kernel-space भव memory on-demand. The
	 * 'reference' page table is init_mm.pgd.
	 */
	अगर (address >= TASK_SIZE && !user_mode(regs))
		जाओ vदो_स्मृति_fault;

	/* If we're in an पूर्णांकerrupt or have no user
	 * context, we must not take the fault..
	 */
	अगर (faulthandler_disabled() || !mm) अणु
		bad_page_fault(regs, address, संक_अंश);
		वापस;
	पूर्ण

	is_ग_लिखो = (exccause == EXCCAUSE_STORE_CACHE_ATTRIBUTE) ? 1 : 0;
	is_exec =  (exccause == EXCCAUSE_ITLB_PRIVILEGE ||
		    exccause == EXCCAUSE_ITLB_MISS ||
		    exccause == EXCCAUSE_FETCH_CACHE_ATTRIBUTE) ? 1 : 0;

	pr_debug("[%s:%d:%08x:%d:%08lx:%s%s]\n",
		 current->comm, current->pid,
		 address, exccause, regs->pc,
		 is_ग_लिखो ? "w" : "", is_exec ? "x" : "");

	अगर (user_mode(regs))
		flags |= FAULT_FLAG_USER;

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
	अगर (expand_stack(vma, address))
		जाओ bad_area;

	/* Ok, we have a good vm_area क्रम this memory access, so
	 * we can handle it..
	 */

good_area:
	code = SEGV_ACCERR;

	अगर (is_ग_लिखो) अणु
		अगर (!(vma->vm_flags & VM_WRITE))
			जाओ bad_area;
		flags |= FAULT_FLAG_WRITE;
	पूर्ण अन्यथा अगर (is_exec) अणु
		अगर (!(vma->vm_flags & VM_EXEC))
			जाओ bad_area;
	पूर्ण अन्यथा	/* Allow पढ़ो even from ग_लिखो-only pages. */
		अगर (!(vma->vm_flags & (VM_READ | VM_WRITE)))
			जाओ bad_area;

	/* If क्रम any reason at all we couldn't handle the fault,
	 * make sure we निकास gracefully rather than endlessly reकरो
	 * the fault.
	 */
	fault = handle_mm_fault(vma, address, flags, regs);

	अगर (fault_संकेत_pending(fault, regs)) अणु
		अगर (!user_mode(regs))
			जाओ bad_page_fault;
		वापस;
	पूर्ण

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

			 /* No need to mmap_पढ़ो_unlock(mm) as we would
			 * have alपढ़ोy released it in __lock_page_or_retry
			 * in mm/filemap.c.
			 */

			जाओ retry;
		पूर्ण
	पूर्ण

	mmap_पढ़ो_unlock(mm);
	वापस;

	/* Something tried to access memory that isn't in our memory map..
	 * Fix it, but check अगर it's kernel or user first..
	 */
bad_area:
	mmap_पढ़ो_unlock(mm);
	अगर (user_mode(regs)) अणु
		current->thपढ़ो.bad_vaddr = address;
		current->thपढ़ो.error_code = is_ग_लिखो;
		क्रमce_sig_fault(संक_अंश, code, (व्योम *) address);
		वापस;
	पूर्ण
	bad_page_fault(regs, address, संक_अंश);
	वापस;


	/* We ran out of memory, or some other thing happened to us that made
	 * us unable to handle the page fault gracefully.
	 */
out_of_memory:
	mmap_पढ़ो_unlock(mm);
	अगर (!user_mode(regs))
		bad_page_fault(regs, address, SIGKILL);
	अन्यथा
		pagefault_out_of_memory();
	वापस;

करो_sigbus:
	mmap_पढ़ो_unlock(mm);

	/* Send a sigbus, regardless of whether we were in kernel
	 * or user mode.
	 */
	current->thपढ़ो.bad_vaddr = address;
	क्रमce_sig_fault(SIGBUS, BUS_ADRERR, (व्योम *) address);

	/* Kernel mode? Handle exceptions or die */
	अगर (!user_mode(regs))
		bad_page_fault(regs, address, SIGBUS);
	वापस;

vदो_स्मृति_fault:
	अणु
		/* Synchronize this task's top level page-table
		 * with the 'reference' page table.
		 */
		काष्ठा mm_काष्ठा *act_mm = current->active_mm;
		पूर्णांक index = pgd_index(address);
		pgd_t *pgd, *pgd_k;
		p4d_t *p4d, *p4d_k;
		pud_t *pud, *pud_k;
		pmd_t *pmd, *pmd_k;
		pte_t *pte_k;

		अगर (act_mm == शून्य)
			जाओ bad_page_fault;

		pgd = act_mm->pgd + index;
		pgd_k = init_mm.pgd + index;

		अगर (!pgd_present(*pgd_k))
			जाओ bad_page_fault;

		pgd_val(*pgd) = pgd_val(*pgd_k);

		p4d = p4d_offset(pgd, address);
		p4d_k = p4d_offset(pgd_k, address);
		अगर (!p4d_present(*p4d) || !p4d_present(*p4d_k))
			जाओ bad_page_fault;

		pud = pud_offset(p4d, address);
		pud_k = pud_offset(p4d_k, address);
		अगर (!pud_present(*pud) || !pud_present(*pud_k))
			जाओ bad_page_fault;

		pmd = pmd_offset(pud, address);
		pmd_k = pmd_offset(pud_k, address);
		अगर (!pmd_present(*pmd) || !pmd_present(*pmd_k))
			जाओ bad_page_fault;

		pmd_val(*pmd) = pmd_val(*pmd_k);
		pte_k = pte_offset_kernel(pmd_k, address);

		अगर (!pte_present(*pte_k))
			जाओ bad_page_fault;
		वापस;
	पूर्ण
bad_page_fault:
	bad_page_fault(regs, address, SIGKILL);
	वापस;
पूर्ण


व्योम
bad_page_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address, पूर्णांक sig)
अणु
	बाह्य व्योम die(स्थिर अक्षर*, काष्ठा pt_regs*, दीर्घ);
	स्थिर काष्ठा exception_table_entry *entry;

	/* Are we prepared to handle this kernel fault?  */
	अगर ((entry = search_exception_tables(regs->pc)) != शून्य) अणु
		pr_debug("%s: Exception at pc=%#010lx (%lx)\n",
			 current->comm, regs->pc, entry->fixup);
		current->thपढ़ो.bad_uaddr = address;
		regs->pc = entry->fixup;
		वापस;
	पूर्ण

	/* Oops. The kernel tried to access some bad page. We'll have to
	 * terminate things with extreme prejudice.
	 */
	pr_alert("Unable to handle kernel paging request at virtual "
		 "address %08lx\n pc = %08lx, ra = %08lx\n",
		 address, regs->pc, regs->areg[0]);
	die("Oops", regs, sig);
	करो_निकास(sig);
पूर्ण
