<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fault.c:  Page fault handlers क्रम the Sparc.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 1996 Eddie C. Dost (ecd@skynet.be)
 * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */

#समावेश <यंत्र/head.h>

#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/extable.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/traps.h>

#समावेश "mm_32.h"

पूर्णांक show_unhandled_संकेतs = 1;

अटल व्योम __noवापस unhandled_fault(अचिन्हित दीर्घ address,
				       काष्ठा task_काष्ठा *tsk,
				       काष्ठा pt_regs *regs)
अणु
	अगर ((अचिन्हित दीर्घ) address < PAGE_SIZE) अणु
		prपूर्णांकk(KERN_ALERT
		    "Unable to handle kernel NULL pointer dereference\n");
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ALERT "Unable to handle kernel paging request at virtual address %08lx\n",
		       address);
	पूर्ण
	prपूर्णांकk(KERN_ALERT "tsk->{mm,active_mm}->context = %08lx\n",
		(tsk->mm ? tsk->mm->context : tsk->active_mm->context));
	prपूर्णांकk(KERN_ALERT "tsk->{mm,active_mm}->pgd = %08lx\n",
		(tsk->mm ? (अचिन्हित दीर्घ) tsk->mm->pgd :
			(अचिन्हित दीर्घ) tsk->active_mm->pgd));
	die_अगर_kernel("Oops", regs);
पूर्ण

अटल अंतरभूत व्योम
show_संकेत_msg(काष्ठा pt_regs *regs, पूर्णांक sig, पूर्णांक code,
		अचिन्हित दीर्घ address, काष्ठा task_काष्ठा *tsk)
अणु
	अगर (!unhandled_संकेत(tsk, sig))
		वापस;

	अगर (!prपूर्णांकk_ratelimit())
		वापस;

	prपूर्णांकk("%s%s[%d]: segfault at %lx ip %px (rpc %px) sp %px error %x",
	       task_pid_nr(tsk) > 1 ? KERN_INFO : KERN_EMERG,
	       tsk->comm, task_pid_nr(tsk), address,
	       (व्योम *)regs->pc, (व्योम *)regs->u_regs[UREG_I7],
	       (व्योम *)regs->u_regs[UREG_FP], code);

	prपूर्णांक_vma_addr(KERN_CONT " in ", regs->pc);

	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

अटल व्योम __करो_fault_siginfo(पूर्णांक code, पूर्णांक sig, काष्ठा pt_regs *regs,
			       अचिन्हित दीर्घ addr)
अणु
	अगर (unlikely(show_unhandled_संकेतs))
		show_संकेत_msg(regs, sig, code,
				addr, current);

	क्रमce_sig_fault(sig, code, (व्योम __user *) addr, 0);
पूर्ण

अटल अचिन्हित दीर्घ compute_si_addr(काष्ठा pt_regs *regs, पूर्णांक text_fault)
अणु
	अचिन्हित पूर्णांक insn;

	अगर (text_fault)
		वापस regs->pc;

	अगर (regs->psr & PSR_PS)
		insn = *(अचिन्हित पूर्णांक *) regs->pc;
	अन्यथा
		__get_user(insn, (अचिन्हित पूर्णांक *) regs->pc);

	वापस safe_compute_effective_address(regs, insn);
पूर्ण

अटल noअंतरभूत व्योम करो_fault_siginfo(पूर्णांक code, पूर्णांक sig, काष्ठा pt_regs *regs,
				      पूर्णांक text_fault)
अणु
	अचिन्हित दीर्घ addr = compute_si_addr(regs, text_fault);

	__करो_fault_siginfo(code, sig, regs, addr);
पूर्ण

यंत्रlinkage व्योम करो_sparc_fault(काष्ठा pt_regs *regs, पूर्णांक text_fault, पूर्णांक ग_लिखो,
			       अचिन्हित दीर्घ address)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा mm_काष्ठा *mm = tsk->mm;
	पूर्णांक from_user = !(regs->psr & PSR_PS);
	पूर्णांक code;
	vm_fault_t fault;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;

	अगर (text_fault)
		address = regs->pc;

	/*
	 * We fault-in kernel-space भव memory on-demand. The
	 * 'reference' page table is init_mm.pgd.
	 *
	 * NOTE! We MUST NOT take any locks क्रम this हाल. We may
	 * be in an पूर्णांकerrupt or a critical region, and should
	 * only copy the inक्रमmation from the master page table,
	 * nothing more.
	 */
	code = SEGV_MAPERR;
	अगर (address >= TASK_SIZE)
		जाओ vदो_स्मृति_fault;

	/*
	 * If we're in an पूर्णांकerrupt or have no user
	 * context, we must not take the fault..
	 */
	अगर (pagefault_disabled() || !mm)
		जाओ no_context;

	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, address);

retry:
	mmap_पढ़ो_lock(mm);

	अगर (!from_user && address >= PAGE_OFFSET)
		जाओ bad_area;

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
	अगर (ग_लिखो) अणु
		अगर (!(vma->vm_flags & VM_WRITE))
			जाओ bad_area;
	पूर्ण अन्यथा अणु
		/* Allow पढ़ोs even क्रम ग_लिखो-only mappings */
		अगर (!(vma->vm_flags & (VM_READ | VM_EXEC)))
			जाओ bad_area;
	पूर्ण

	अगर (from_user)
		flags |= FAULT_FLAG_USER;
	अगर (ग_लिखो)
		flags |= FAULT_FLAG_WRITE;

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
	अगर (from_user) अणु
		करो_fault_siginfo(code, संक_अंश, regs, text_fault);
		वापस;
	पूर्ण

	/* Is this in ex_table? */
no_context:
	अगर (!from_user) अणु
		स्थिर काष्ठा exception_table_entry *entry;

		entry = search_exception_tables(regs->pc);
#अगर_घोषित DEBUG_EXCEPTIONS
		prपूर्णांकk("Exception: PC<%08lx> faddr<%08lx>\n",
		       regs->pc, address);
		prपूर्णांकk("EX_TABLE: insn<%08lx> fixup<%08x>\n",
			regs->pc, entry->fixup);
#पूर्ण_अगर
		regs->pc = entry->fixup;
		regs->npc = regs->pc + 4;
		वापस;
	पूर्ण

	unhandled_fault(address, tsk, regs);
	करो_निकास(SIGKILL);

/*
 * We ran out of memory, or some other thing happened to us that made
 * us unable to handle the page fault gracefully.
 */
out_of_memory:
	mmap_पढ़ो_unlock(mm);
	अगर (from_user) अणु
		pagefault_out_of_memory();
		वापस;
	पूर्ण
	जाओ no_context;

करो_sigbus:
	mmap_पढ़ो_unlock(mm);
	करो_fault_siginfo(BUS_ADRERR, SIGBUS, regs, text_fault);
	अगर (!from_user)
		जाओ no_context;

vदो_स्मृति_fault:
	अणु
		/*
		 * Synchronize this task's top level page-table
		 * with the 'reference' page table.
		 */
		पूर्णांक offset = pgd_index(address);
		pgd_t *pgd, *pgd_k;
		p4d_t *p4d, *p4d_k;
		pud_t *pud, *pud_k;
		pmd_t *pmd, *pmd_k;

		pgd = tsk->active_mm->pgd + offset;
		pgd_k = init_mm.pgd + offset;

		अगर (!pgd_present(*pgd)) अणु
			अगर (!pgd_present(*pgd_k))
				जाओ bad_area_nosemaphore;
			pgd_val(*pgd) = pgd_val(*pgd_k);
			वापस;
		पूर्ण

		p4d = p4d_offset(pgd, address);
		pud = pud_offset(p4d, address);
		pmd = pmd_offset(pud, address);

		p4d_k = p4d_offset(pgd_k, address);
		pud_k = pud_offset(p4d_k, address);
		pmd_k = pmd_offset(pud_k, address);

		अगर (pmd_present(*pmd) || !pmd_present(*pmd_k))
			जाओ bad_area_nosemaphore;

		*pmd = *pmd_k;
		वापस;
	पूर्ण
पूर्ण

/* This always deals with user addresses. */
अटल व्योम क्रमce_user_fault(अचिन्हित दीर्घ address, पूर्णांक ग_लिखो)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा mm_काष्ठा *mm = tsk->mm;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_USER;
	पूर्णांक code;

	code = SEGV_MAPERR;

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
good_area:
	code = SEGV_ACCERR;
	अगर (ग_लिखो) अणु
		अगर (!(vma->vm_flags & VM_WRITE))
			जाओ bad_area;
		flags |= FAULT_FLAG_WRITE;
	पूर्ण अन्यथा अणु
		अगर (!(vma->vm_flags & (VM_READ | VM_EXEC)))
			जाओ bad_area;
	पूर्ण
	चयन (handle_mm_fault(vma, address, flags, शून्य)) अणु
	हाल VM_FAULT_SIGBUS:
	हाल VM_FAULT_OOM:
		जाओ करो_sigbus;
	पूर्ण
	mmap_पढ़ो_unlock(mm);
	वापस;
bad_area:
	mmap_पढ़ो_unlock(mm);
	__करो_fault_siginfo(code, संक_अंश, tsk->thपढ़ो.kregs, address);
	वापस;

करो_sigbus:
	mmap_पढ़ो_unlock(mm);
	__करो_fault_siginfo(BUS_ADRERR, SIGBUS, tsk->thपढ़ो.kregs, address);
पूर्ण

अटल व्योम check_stack_aligned(अचिन्हित दीर्घ sp)
अणु
	अगर (sp & 0x7UL)
		क्रमce_sig(संक_अवैध);
पूर्ण

व्योम winकरोw_overflow_fault(व्योम)
अणु
	अचिन्हित दीर्घ sp;

	sp = current_thपढ़ो_info()->rwbuf_stkptrs[0];
	अगर (((sp + 0x38) & PAGE_MASK) != (sp & PAGE_MASK))
		क्रमce_user_fault(sp + 0x38, 1);
	क्रमce_user_fault(sp, 1);

	check_stack_aligned(sp);
पूर्ण

व्योम winकरोw_underflow_fault(अचिन्हित दीर्घ sp)
अणु
	अगर (((sp + 0x38) & PAGE_MASK) != (sp & PAGE_MASK))
		क्रमce_user_fault(sp + 0x38, 0);
	क्रमce_user_fault(sp, 0);

	check_stack_aligned(sp);
पूर्ण

व्योम winकरोw_ret_fault(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ sp;

	sp = regs->u_regs[UREG_FP];
	अगर (((sp + 0x38) & PAGE_MASK) != (sp & PAGE_MASK))
		क्रमce_user_fault(sp + 0x38, 0);
	क्रमce_user_fault(sp, 0);

	check_stack_aligned(sp);
पूर्ण
