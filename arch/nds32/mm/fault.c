<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/extable.h>
#समावेश <linux/module.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/perf_event.h>

#समावेश <यंत्र/tlbflush.h>

बाह्य व्योम die(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err);

/*
 * This is useful to dump out the page tables associated with
 * 'addr' in mm 'mm'.
 */
व्योम show_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgd;
	अगर (!mm)
		mm = &init_mm;

	pr_alert("pgd = %p\n", mm->pgd);
	pgd = pgd_offset(mm, addr);
	pr_alert("[%08lx] *pgd=%08lx", addr, pgd_val(*pgd));

	करो अणु
		p4d_t *p4d;
		pud_t *pud;
		pmd_t *pmd;

		अगर (pgd_none(*pgd))
			अवरोध;

		अगर (pgd_bad(*pgd)) अणु
			pr_alert("(bad)");
			अवरोध;
		पूर्ण

		p4d = p4d_offset(pgd, addr);
		pud = pud_offset(p4d, addr);
		pmd = pmd_offset(pud, addr);
#अगर PTRS_PER_PMD != 1
		pr_alert(", *pmd=%08lx", pmd_val(*pmd));
#पूर्ण_अगर

		अगर (pmd_none(*pmd))
			अवरोध;

		अगर (pmd_bad(*pmd)) अणु
			pr_alert("(bad)");
			अवरोध;
		पूर्ण

		अगर (IS_ENABLED(CONFIG_HIGHMEM))
		अणु
			pte_t *pte;
			/* We must not map this अगर we have highmem enabled */
			pte = pte_offset_map(pmd, addr);
			pr_alert(", *pte=%08lx", pte_val(*pte));
			pte_unmap(pte);
		पूर्ण
	पूर्ण जबतक (0);

	pr_alert("\n");
पूर्ण

व्योम करो_page_fault(अचिन्हित दीर्घ entry, अचिन्हित दीर्घ addr,
		   अचिन्हित पूर्णांक error_code, काष्ठा pt_regs *regs)
अणु
	काष्ठा task_काष्ठा *tsk;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक si_code;
	vm_fault_t fault;
	अचिन्हित पूर्णांक mask = VM_ACCESS_FLAGS;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;

	error_code = error_code & (ITYPE_mskINST | ITYPE_mskETYPE);
	tsk = current;
	mm = tsk->mm;
	si_code = SEGV_MAPERR;
	/*
	 * We fault-in kernel-space भव memory on-demand. The
	 * 'reference' page table is init_mm.pgd.
	 *
	 * NOTE! We MUST NOT take any locks क्रम this हाल. We may
	 * be in an पूर्णांकerrupt or a critical region, and should
	 * only copy the inक्रमmation from the master page table,
	 * nothing more.
	 */
	अगर (addr >= TASK_SIZE) अणु
		अगर (user_mode(regs))
			जाओ bad_area_nosemaphore;

		अगर (addr >= TASK_SIZE && addr < VMALLOC_END
		    && (entry == ENTRY_PTE_NOT_PRESENT))
			जाओ vदो_स्मृति_fault;
		अन्यथा
			जाओ no_context;
	पूर्ण

	/* Send a संकेत to the task क्रम handling the unalignment access. */
	अगर (entry == ENTRY_GENERAL_EXCPETION
	    && error_code == ETYPE_ALIGNMENT_CHECK) अणु
		अगर (user_mode(regs))
			जाओ bad_area_nosemaphore;
		अन्यथा
			जाओ no_context;
	पूर्ण

	/*
	 * If we're in an पूर्णांकerrupt or have no user
	 * context, we must not take the fault..
	 */
	अगर (unlikely(faulthandler_disabled() || !mm))
		जाओ no_context;

	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, addr);

	/*
	 * As per x86, we may deadlock here. However, since the kernel only
	 * validly references user space from well defined areas of the code,
	 * we can bug out early अगर this is from code which shouldn't.
	 */
	अगर (unlikely(!mmap_पढ़ो_trylock(mm))) अणु
		अगर (!user_mode(regs) &&
		    !search_exception_tables(inकाष्ठाion_poपूर्णांकer(regs)))
			जाओ no_context;
retry:
		mmap_पढ़ो_lock(mm);
	पूर्ण अन्यथा अणु
		/*
		 * The above करोwn_पढ़ो_trylock() might have succeeded in which
		 * हाल, we'll have missed the might_sleep() from करोwn_पढ़ो().
		 */
		might_sleep();
		अगर (IS_ENABLED(CONFIG_DEBUG_VM)) अणु
			अगर (!user_mode(regs) &&
			    !search_exception_tables(inकाष्ठाion_poपूर्णांकer(regs)))
				जाओ no_context;
		पूर्ण
	पूर्ण

	vma = find_vma(mm, addr);

	अगर (unlikely(!vma))
		जाओ bad_area;

	अगर (vma->vm_start <= addr)
		जाओ good_area;

	अगर (unlikely(!(vma->vm_flags & VM_GROWSDOWN)))
		जाओ bad_area;

	अगर (unlikely(expand_stack(vma, addr)))
		जाओ bad_area;

	/*
	 * Ok, we have a good vm_area क्रम this memory access, so
	 * we can handle it..
	 */

good_area:
	si_code = SEGV_ACCERR;

	/* first करो some preliminary protection checks */
	अगर (entry == ENTRY_PTE_NOT_PRESENT) अणु
		अगर (error_code & ITYPE_mskINST)
			mask = VM_EXEC;
		अन्यथा अणु
			mask = VM_READ | VM_WRITE;
		पूर्ण
	पूर्ण अन्यथा अगर (entry == ENTRY_TLB_MISC) अणु
		चयन (error_code & ITYPE_mskETYPE) अणु
		हाल RD_PROT:
			mask = VM_READ;
			अवरोध;
		हाल WRT_PROT:
			mask = VM_WRITE;
			flags |= FAULT_FLAG_WRITE;
			अवरोध;
		हाल NOEXEC:
			mask = VM_EXEC;
			अवरोध;
		हाल PAGE_MODIFY:
			mask = VM_WRITE;
			flags |= FAULT_FLAG_WRITE;
			अवरोध;
		हाल ACC_BIT:
			BUG();
		शेष:
			अवरोध;
		पूर्ण

	पूर्ण
	अगर (!(vma->vm_flags & mask))
		जाओ bad_area;

	/*
	 * If क्रम any reason at all we couldn't handle the fault,
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
			जाओ no_context;
		वापस;
	पूर्ण

	अगर (unlikely(fault & VM_FAULT_ERROR)) अणु
		अगर (fault & VM_FAULT_OOM)
			जाओ out_of_memory;
		अन्यथा अगर (fault & VM_FAULT_SIGBUS)
			जाओ करो_sigbus;
		अन्यथा
			जाओ bad_area;
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

	/*
	 * Something tried to access memory that isn't in our memory map..
	 * Fix it, but check अगर it's kernel or user first..
	 */
bad_area:
	mmap_पढ़ो_unlock(mm);

bad_area_nosemaphore:

	/* User mode accesses just cause a संक_अंश */

	अगर (user_mode(regs)) अणु
		tsk->thपढ़ो.address = addr;
		tsk->thपढ़ो.error_code = error_code;
		tsk->thपढ़ो.trap_no = entry;
		क्रमce_sig_fault(संक_अंश, si_code, (व्योम __user *)addr);
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

		अगर ((entry =
		     search_exception_tables(inकाष्ठाion_poपूर्णांकer(regs))) !=
		    शून्य) अणु
			/* Adjust the inकाष्ठाion poपूर्णांकer in the stackframe */
			inकाष्ठाion_poपूर्णांकer(regs) = entry->fixup;
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * Oops. The kernel tried to access some bad page. We'll have to
	 * terminate things with extreme prejudice.
	 */

	bust_spinlocks(1);
	pr_alert("Unable to handle kernel %s at virtual address %08lx\n",
		 (addr < PAGE_SIZE) ? "NULL pointer dereference" :
		 "paging request", addr);

	show_pte(mm, addr);
	die("Oops", regs, error_code);
	bust_spinlocks(0);
	करो_निकास(SIGKILL);

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

	/*
	 * Send a sigbus
	 */
	tsk->thपढ़ो.address = addr;
	tsk->thपढ़ो.error_code = error_code;
	tsk->thपढ़ो.trap_no = entry;
	क्रमce_sig_fault(SIGBUS, BUS_ADRERR, (व्योम __user *)addr);

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

		अचिन्हित पूर्णांक index = pgd_index(addr);
		pgd_t *pgd, *pgd_k;
		p4d_t *p4d, *p4d_k;
		pud_t *pud, *pud_k;
		pmd_t *pmd, *pmd_k;
		pte_t *pte_k;

		pgd = (pgd_t *) __va(__nds32__mfsr(NDS32_SR_L1_PPTB)) + index;
		pgd_k = init_mm.pgd + index;

		अगर (!pgd_present(*pgd_k))
			जाओ no_context;

		p4d = p4d_offset(pgd, addr);
		p4d_k = p4d_offset(pgd_k, addr);
		अगर (!p4d_present(*p4d_k))
			जाओ no_context;

		pud = pud_offset(p4d, addr);
		pud_k = pud_offset(p4d_k, addr);
		अगर (!pud_present(*pud_k))
			जाओ no_context;

		pmd = pmd_offset(pud, addr);
		pmd_k = pmd_offset(pud_k, addr);
		अगर (!pmd_present(*pmd_k))
			जाओ no_context;

		अगर (!pmd_present(*pmd))
			set_pmd(pmd, *pmd_k);
		अन्यथा
			BUG_ON(pmd_page(*pmd) != pmd_page(*pmd_k));

		/*
		 * Since the vदो_स्मृति area is global, we करोn't
		 * need to copy inभागidual PTE's, it is enough to
		 * copy the pgd poपूर्णांकer पूर्णांकo the pte page of the
		 * root task. If that is there, we'll find our pte अगर
		 * it exists.
		 */

		/* Make sure the actual PTE exists as well to
		 * catch kernel vदो_स्मृति-area accesses to non-mapped
		 * addres. If we करोn't करो this, this will just
		 * silently loop क्रमever.
		 */

		pte_k = pte_offset_kernel(pmd_k, addr);
		अगर (!pte_present(*pte_k))
			जाओ no_context;

		वापस;
	पूर्ण
पूर्ण
