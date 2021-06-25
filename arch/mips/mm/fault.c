<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995 - 2000 by Ralf Baechle
 */
#समावेश <linux/context_tracking.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/branch.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/highस्मृति.स>		/* For VMALLOC_END */
#समावेश <linux/kdebug.h>

पूर्णांक show_unhandled_संकेतs = 1;

/*
 * This routine handles page faults.  It determines the address,
 * and the problem, and then passes it off to one of the appropriate
 * routines.
 */
अटल व्योम __kprobes __करो_page_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ ग_लिखो,
	अचिन्हित दीर्घ address)
अणु
	काष्ठा vm_area_काष्ठा * vma = शून्य;
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा mm_काष्ठा *mm = tsk->mm;
	स्थिर पूर्णांक field = माप(अचिन्हित दीर्घ) * 2;
	पूर्णांक si_code;
	vm_fault_t fault;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;

	अटल DEFINE_RATELIMIT_STATE(ratelimit_state, 5 * HZ, 10);

#अगर 0
	prपूर्णांकk("Cpu%d[%s:%d:%0*lx:%ld:%0*lx]\n", raw_smp_processor_id(),
	       current->comm, current->pid, field, address, ग_लिखो,
	       field, regs->cp0_epc);
#पूर्ण_अगर

#अगर_घोषित CONFIG_KPROBES
	/*
	 * This is to notअगरy the fault handler of the kprobes.
	 */
	अगर (notअगरy_die(DIE_PAGE_FAULT, "page fault", regs, -1,
		       current->thपढ़ो.trap_nr, संक_अंश) == NOTIFY_STOP)
		वापस;
#पूर्ण_अगर

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
#अगर_घोषित CONFIG_64BIT
# define VMALLOC_FAULT_TARGET no_context
#अन्यथा
# define VMALLOC_FAULT_TARGET vदो_स्मृति_fault
#पूर्ण_अगर

	अगर (unlikely(address >= VMALLOC_START && address <= VMALLOC_END))
		जाओ VMALLOC_FAULT_TARGET;
#अगर_घोषित MODULE_START
	अगर (unlikely(address >= MODULE_START && address < MODULE_END))
		जाओ VMALLOC_FAULT_TARGET;
#पूर्ण_अगर

	/*
	 * If we're in an पूर्णांकerrupt or have no user
	 * context, we must not take the fault..
	 */
	अगर (faulthandler_disabled() || !mm)
		जाओ bad_area_nosemaphore;

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
/*
 * Ok, we have a good vm_area क्रम this memory access, so
 * we can handle it..
 */
good_area:
	si_code = SEGV_ACCERR;

	अगर (ग_लिखो) अणु
		अगर (!(vma->vm_flags & VM_WRITE))
			जाओ bad_area;
		flags |= FAULT_FLAG_WRITE;
	पूर्ण अन्यथा अणु
		अगर (cpu_has_rixi) अणु
			अगर (address == regs->cp0_epc && !(vma->vm_flags & VM_EXEC)) अणु
#अगर 0
				pr_notice("Cpu%d[%s:%d:%0*lx:%ld:%0*lx] XI violation\n",
					  raw_smp_processor_id(),
					  current->comm, current->pid,
					  field, address, ग_लिखो,
					  field, regs->cp0_epc);
#पूर्ण_अगर
				जाओ bad_area;
			पूर्ण
			अगर (!(vma->vm_flags & VM_READ) &&
			    exception_epc(regs) != address) अणु
#अगर 0
				pr_notice("Cpu%d[%s:%d:%0*lx:%ld:%0*lx] RI violation\n",
					  raw_smp_processor_id(),
					  current->comm, current->pid,
					  field, address, ग_लिखो,
					  field, regs->cp0_epc);
#पूर्ण_अगर
				जाओ bad_area;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (unlikely(!vma_is_accessible(vma)))
				जाओ bad_area;
		पूर्ण
	पूर्ण

	/*
	 * If क्रम any reason at all we couldn't handle the fault,
	 * make sure we निकास gracefully rather than endlessly reकरो
	 * the fault.
	 */
	fault = handle_mm_fault(vma, address, flags, regs);

	अगर (fault_संकेत_pending(fault, regs)) अणु
		अगर (!user_mode(regs))
			जाओ no_context;
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
		tsk->thपढ़ो.cp0_badvaddr = address;
		tsk->thपढ़ो.error_code = ग_लिखो;
		अगर (show_unhandled_संकेतs &&
		    unhandled_संकेत(tsk, संक_अंश) &&
		    __ratelimit(&ratelimit_state)) अणु
			pr_info("do_page_fault(): sending SIGSEGV to %s for invalid %s %0*lx\n",
				tsk->comm,
				ग_लिखो ? "write access to" : "read access from",
				field, address);
			pr_info("epc = %0*lx in", field,
				(अचिन्हित दीर्घ) regs->cp0_epc);
			prपूर्णांक_vma_addr(KERN_CONT " ", regs->cp0_epc);
			pr_cont("\n");
			pr_info("ra  = %0*lx in", field,
				(अचिन्हित दीर्घ) regs->regs[31]);
			prपूर्णांक_vma_addr(KERN_CONT " ", regs->regs[31]);
			pr_cont("\n");
		पूर्ण
		current->thपढ़ो.trap_nr = (regs->cp0_cause >> 2) & 0x1f;
		क्रमce_sig_fault(संक_अंश, si_code, (व्योम __user *)address);
		वापस;
	पूर्ण

no_context:
	/* Are we prepared to handle this kernel fault?	 */
	अगर (fixup_exception(regs)) अणु
		current->thपढ़ो.cp0_baduaddr = address;
		वापस;
	पूर्ण

	/*
	 * Oops. The kernel tried to access some bad page. We'll have to
	 * terminate things with extreme prejudice.
	 */
	bust_spinlocks(1);

	prपूर्णांकk(KERN_ALERT "CPU %d Unable to handle kernel paging request at "
	       "virtual address %0*lx, epc == %0*lx, ra == %0*lx\n",
	       raw_smp_processor_id(), field, address, field, regs->cp0_epc,
	       field,  regs->regs[31]);
	die("Oops", regs);

out_of_memory:
	/*
	 * We ran out of memory, call the OOM समाप्तer, and वापस the userspace
	 * (which will retry the fault, or समाप्त us अगर we got oom-समाप्तed).
	 */
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
	 * Send a sigbus, regardless of whether we were in kernel
	 * or user mode.
	 */
#अगर 0
	prपूर्णांकk("do_page_fault() #3: sending SIGBUS to %s for "
	       "invalid %s\n%0*lx (epc == %0*lx, ra == %0*lx)\n",
	       tsk->comm,
	       ग_लिखो ? "write access to" : "read access from",
	       field, address,
	       field, (अचिन्हित दीर्घ) regs->cp0_epc,
	       field, (अचिन्हित दीर्घ) regs->regs[31]);
#पूर्ण_अगर
	current->thपढ़ो.trap_nr = (regs->cp0_cause >> 2) & 0x1f;
	tsk->thपढ़ो.cp0_badvaddr = address;
	क्रमce_sig_fault(SIGBUS, BUS_ADRERR, (व्योम __user *)address);

	वापस;
#अगर_अघोषित CONFIG_64BIT
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

		pgd = (pgd_t *) pgd_current[raw_smp_processor_id()] + offset;
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
		वापस;
	पूर्ण
#पूर्ण_अगर
पूर्ण

यंत्रlinkage व्योम __kprobes करो_page_fault(काष्ठा pt_regs *regs,
	अचिन्हित दीर्घ ग_लिखो, अचिन्हित दीर्घ address)
अणु
	क्रमागत ctx_state prev_state;

	prev_state = exception_enter();
	__करो_page_fault(regs, ग_लिखो, address);
	exception_निकास(prev_state);
पूर्ण
