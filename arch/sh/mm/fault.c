<शैली गुरु>
/*
 * Page fault handler क्रम SH with an MMU.
 *
 *  Copyright (C) 1999  Niibe Yutaka
 *  Copyright (C) 2003 - 2012  Paul Mundt
 *
 *  Based on linux/arch/i386/mm/fault.c:
 *   Copyright (C) 1995  Linus Torvalds
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/hardirq.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/io_trapped.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/traps.h>

अटल व्योम
क्रमce_sig_info_fault(पूर्णांक si_signo, पूर्णांक si_code, अचिन्हित दीर्घ address)
अणु
	क्रमce_sig_fault(si_signo, si_code, (व्योम __user *)address);
पूर्ण

/*
 * This is useful to dump out the page tables associated with
 * 'addr' in mm 'mm'.
 */
अटल व्योम show_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgd;

	अगर (mm) अणु
		pgd = mm->pgd;
	पूर्ण अन्यथा अणु
		pgd = get_TTB();

		अगर (unlikely(!pgd))
			pgd = swapper_pg_dir;
	पूर्ण

	pr_alert("pgd = %p\n", pgd);
	pgd += pgd_index(addr);
	pr_alert("[%08lx] *pgd=%0*llx", addr, (u32)(माप(*pgd) * 2),
		 (u64)pgd_val(*pgd));

	करो अणु
		p4d_t *p4d;
		pud_t *pud;
		pmd_t *pmd;
		pte_t *pte;

		अगर (pgd_none(*pgd))
			अवरोध;

		अगर (pgd_bad(*pgd)) अणु
			pr_cont("(bad)");
			अवरोध;
		पूर्ण

		p4d = p4d_offset(pgd, addr);
		अगर (PTRS_PER_P4D != 1)
			pr_cont(", *p4d=%0*Lx", (u32)(माप(*p4d) * 2),
			        (u64)p4d_val(*p4d));

		अगर (p4d_none(*p4d))
			अवरोध;

		अगर (p4d_bad(*p4d)) अणु
			pr_cont("(bad)");
			अवरोध;
		पूर्ण

		pud = pud_offset(p4d, addr);
		अगर (PTRS_PER_PUD != 1)
			pr_cont(", *pud=%0*llx", (u32)(माप(*pud) * 2),
				(u64)pud_val(*pud));

		अगर (pud_none(*pud))
			अवरोध;

		अगर (pud_bad(*pud)) अणु
			pr_cont("(bad)");
			अवरोध;
		पूर्ण

		pmd = pmd_offset(pud, addr);
		अगर (PTRS_PER_PMD != 1)
			pr_cont(", *pmd=%0*llx", (u32)(माप(*pmd) * 2),
				(u64)pmd_val(*pmd));

		अगर (pmd_none(*pmd))
			अवरोध;

		अगर (pmd_bad(*pmd)) अणु
			pr_cont("(bad)");
			अवरोध;
		पूर्ण

		/* We must not map this अगर we have highmem enabled */
		अगर (PageHighMem(pfn_to_page(pmd_val(*pmd) >> PAGE_SHIFT)))
			अवरोध;

		pte = pte_offset_kernel(pmd, addr);
		pr_cont(", *pte=%0*llx", (u32)(माप(*pte) * 2),
			(u64)pte_val(*pte));
	पूर्ण जबतक (0);

	pr_cont("\n");
पूर्ण

अटल अंतरभूत pmd_t *vदो_स्मृति_sync_one(pgd_t *pgd, अचिन्हित दीर्घ address)
अणु
	अचिन्हित index = pgd_index(address);
	pgd_t *pgd_k;
	p4d_t *p4d, *p4d_k;
	pud_t *pud, *pud_k;
	pmd_t *pmd, *pmd_k;

	pgd += index;
	pgd_k = init_mm.pgd + index;

	अगर (!pgd_present(*pgd_k))
		वापस शून्य;

	p4d = p4d_offset(pgd, address);
	p4d_k = p4d_offset(pgd_k, address);
	अगर (!p4d_present(*p4d_k))
		वापस शून्य;

	pud = pud_offset(p4d, address);
	pud_k = pud_offset(p4d_k, address);
	अगर (!pud_present(*pud_k))
		वापस शून्य;

	अगर (!pud_present(*pud))
	    set_pud(pud, *pud_k);

	pmd = pmd_offset(pud, address);
	pmd_k = pmd_offset(pud_k, address);
	अगर (!pmd_present(*pmd_k))
		वापस शून्य;

	अगर (!pmd_present(*pmd))
		set_pmd(pmd, *pmd_k);
	अन्यथा अणु
		/*
		 * The page tables are fully synchronised so there must
		 * be another reason क्रम the fault. Return शून्य here to
		 * संकेत that we have not taken care of the fault.
		 */
		BUG_ON(pmd_page(*pmd) != pmd_page(*pmd_k));
		वापस शून्य;
	पूर्ण

	वापस pmd_k;
पूर्ण

#अगर_घोषित CONFIG_SH_STORE_QUEUES
#घोषणा __FAULT_ADDR_LIMIT	P3_ADDR_MAX
#अन्यथा
#घोषणा __FAULT_ADDR_LIMIT	VMALLOC_END
#पूर्ण_अगर

/*
 * Handle a fault on the vदो_स्मृति or module mapping area
 */
अटल noअंतरभूत पूर्णांक vदो_स्मृति_fault(अचिन्हित दीर्घ address)
अणु
	pgd_t *pgd_k;
	pmd_t *pmd_k;
	pte_t *pte_k;

	/* Make sure we are in vदो_स्मृति/module/P3 area: */
	अगर (!(address >= VMALLOC_START && address < __FAULT_ADDR_LIMIT))
		वापस -1;

	/*
	 * Synchronize this task's top level page-table
	 * with the 'reference' page table.
	 *
	 * Do _not_ use "current" here. We might be inside
	 * an पूर्णांकerrupt in the middle of a task चयन..
	 */
	pgd_k = get_TTB();
	pmd_k = vदो_स्मृति_sync_one(pgd_k, address);
	अगर (!pmd_k)
		वापस -1;

	pte_k = pte_offset_kernel(pmd_k, address);
	अगर (!pte_present(*pte_k))
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम
show_fault_oops(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address)
अणु
	अगर (!oops_may_prपूर्णांक())
		वापस;

	pr_alert("BUG: unable to handle kernel %s at %08lx\n",
		 address < PAGE_SIZE ? "NULL pointer dereference"
				     : "paging request",
		 address);
	pr_alert("PC:");
	prपूर्णांकk_address(regs->pc, 1);

	show_pte(शून्य, address);
पूर्ण

अटल noअंतरभूत व्योम
no_context(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
	   अचिन्हित दीर्घ address)
अणु
	/* Are we prepared to handle this kernel fault?  */
	अगर (fixup_exception(regs))
		वापस;

	अगर (handle_trapped_io(regs, address))
		वापस;

	/*
	 * Oops. The kernel tried to access some bad page. We'll have to
	 * terminate things with extreme prejudice.
	 */
	bust_spinlocks(1);

	show_fault_oops(regs, address);

	die("Oops", regs, error_code);
	bust_spinlocks(0);
	करो_निकास(SIGKILL);
पूर्ण

अटल व्योम
__bad_area_nosemaphore(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
		       अचिन्हित दीर्घ address, पूर्णांक si_code)
अणु
	/* User mode accesses just cause a संक_अंश */
	अगर (user_mode(regs)) अणु
		/*
		 * It's possible to have पूर्णांकerrupts off here:
		 */
		local_irq_enable();

		क्रमce_sig_info_fault(संक_अंश, si_code, address);

		वापस;
	पूर्ण

	no_context(regs, error_code, address);
पूर्ण

अटल noअंतरभूत व्योम
bad_area_nosemaphore(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
		     अचिन्हित दीर्घ address)
अणु
	__bad_area_nosemaphore(regs, error_code, address, SEGV_MAPERR);
पूर्ण

अटल व्योम
__bad_area(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
	   अचिन्हित दीर्घ address, पूर्णांक si_code)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;

	/*
	 * Something tried to access memory that isn't in our memory map..
	 * Fix it, but check अगर it's kernel or user first..
	 */
	mmap_पढ़ो_unlock(mm);

	__bad_area_nosemaphore(regs, error_code, address, si_code);
पूर्ण

अटल noअंतरभूत व्योम
bad_area(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code, अचिन्हित दीर्घ address)
अणु
	__bad_area(regs, error_code, address, SEGV_MAPERR);
पूर्ण

अटल noअंतरभूत व्योम
bad_area_access_error(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
		      अचिन्हित दीर्घ address)
अणु
	__bad_area(regs, error_code, address, SEGV_ACCERR);
पूर्ण

अटल व्योम
करो_sigbus(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code, अचिन्हित दीर्घ address)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा mm_काष्ठा *mm = tsk->mm;

	mmap_पढ़ो_unlock(mm);

	/* Kernel mode? Handle exceptions or die: */
	अगर (!user_mode(regs))
		no_context(regs, error_code, address);

	क्रमce_sig_info_fault(SIGBUS, BUS_ADRERR, address);
पूर्ण

अटल noअंतरभूत पूर्णांक
mm_fault_error(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
	       अचिन्हित दीर्घ address, vm_fault_t fault)
अणु
	/*
	 * Pagefault was पूर्णांकerrupted by SIGKILL. We have no reason to
	 * जारी pagefault.
	 */
	अगर (fault_संकेत_pending(fault, regs)) अणु
		अगर (!user_mode(regs))
			no_context(regs, error_code, address);
		वापस 1;
	पूर्ण

	/* Release mmap_lock first अगर necessary */
	अगर (!(fault & VM_FAULT_RETRY))
		mmap_पढ़ो_unlock(current->mm);

	अगर (!(fault & VM_FAULT_ERROR))
		वापस 0;

	अगर (fault & VM_FAULT_OOM) अणु
		/* Kernel mode? Handle exceptions or die: */
		अगर (!user_mode(regs)) अणु
			no_context(regs, error_code, address);
			वापस 1;
		पूर्ण

		/*
		 * We ran out of memory, call the OOM समाप्तer, and वापस the
		 * userspace (which will retry the fault, or समाप्त us अगर we got
		 * oom-समाप्तed):
		 */
		pagefault_out_of_memory();
	पूर्ण अन्यथा अणु
		अगर (fault & VM_FAULT_SIGBUS)
			करो_sigbus(regs, error_code, address);
		अन्यथा अगर (fault & VM_FAULT_संक_अंश)
			bad_area(regs, error_code, address);
		अन्यथा
			BUG();
	पूर्ण

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक access_error(पूर्णांक error_code, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (error_code & FAULT_CODE_WRITE) अणु
		/* ग_लिखो, present and ग_लिखो, not present: */
		अगर (unlikely(!(vma->vm_flags & VM_WRITE)))
			वापस 1;
		वापस 0;
	पूर्ण

	/* ITLB miss on NX page */
	अगर (unlikely((error_code & FAULT_CODE_ITLB) &&
		     !(vma->vm_flags & VM_EXEC)))
		वापस 1;

	/* पढ़ो, not present: */
	अगर (unlikely(!vma_is_accessible(vma)))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक fault_in_kernel_space(अचिन्हित दीर्घ address)
अणु
	वापस address >= TASK_SIZE;
पूर्ण

/*
 * This routine handles page faults.  It determines the address,
 * and the problem, and then passes it off to one of the appropriate
 * routines.
 */
यंत्रlinkage व्योम __kprobes करो_page_fault(काष्ठा pt_regs *regs,
					अचिन्हित दीर्घ error_code,
					अचिन्हित दीर्घ address)
अणु
	अचिन्हित दीर्घ vec;
	काष्ठा task_काष्ठा *tsk;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा vm_area_काष्ठा * vma;
	vm_fault_t fault;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;

	tsk = current;
	mm = tsk->mm;
	vec = lookup_exception_vector();

	/*
	 * We fault-in kernel-space भव memory on-demand. The
	 * 'reference' page table is init_mm.pgd.
	 *
	 * NOTE! We MUST NOT take any locks क्रम this हाल. We may
	 * be in an पूर्णांकerrupt or a critical region, and should
	 * only copy the inक्रमmation from the master page table,
	 * nothing more.
	 */
	अगर (unlikely(fault_in_kernel_space(address))) अणु
		अगर (vदो_स्मृति_fault(address) >= 0)
			वापस;
		अगर (kprobe_page_fault(regs, vec))
			वापस;

		bad_area_nosemaphore(regs, error_code, address);
		वापस;
	पूर्ण

	अगर (unlikely(kprobe_page_fault(regs, vec)))
		वापस;

	/* Only enable पूर्णांकerrupts अगर they were on beक्रमe the fault */
	अगर ((regs->sr & SR_IMASK) != SR_IMASK)
		local_irq_enable();

	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, address);

	/*
	 * If we're in an पूर्णांकerrupt, have no user context or are running
	 * with pagefaults disabled then we must not take the fault:
	 */
	अगर (unlikely(faulthandler_disabled() || !mm)) अणु
		bad_area_nosemaphore(regs, error_code, address);
		वापस;
	पूर्ण

retry:
	mmap_पढ़ो_lock(mm);

	vma = find_vma(mm, address);
	अगर (unlikely(!vma)) अणु
		bad_area(regs, error_code, address);
		वापस;
	पूर्ण
	अगर (likely(vma->vm_start <= address))
		जाओ good_area;
	अगर (unlikely(!(vma->vm_flags & VM_GROWSDOWN))) अणु
		bad_area(regs, error_code, address);
		वापस;
	पूर्ण
	अगर (unlikely(expand_stack(vma, address))) अणु
		bad_area(regs, error_code, address);
		वापस;
	पूर्ण

	/*
	 * Ok, we have a good vm_area क्रम this memory access, so
	 * we can handle it..
	 */
good_area:
	अगर (unlikely(access_error(error_code, vma))) अणु
		bad_area_access_error(regs, error_code, address);
		वापस;
	पूर्ण

	set_thपढ़ो_fault_code(error_code);

	अगर (user_mode(regs))
		flags |= FAULT_FLAG_USER;
	अगर (error_code & FAULT_CODE_WRITE)
		flags |= FAULT_FLAG_WRITE;

	/*
	 * If क्रम any reason at all we couldn't handle the fault,
	 * make sure we निकास gracefully rather than endlessly reकरो
	 * the fault.
	 */
	fault = handle_mm_fault(vma, address, flags, regs);

	अगर (unlikely(fault & (VM_FAULT_RETRY | VM_FAULT_ERROR)))
		अगर (mm_fault_error(regs, error_code, address, fault))
			वापस;

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
पूर्ण
