<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Page Fault Handling क्रम ARC (TLB Miss / ProtV)
 *
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/mm_types.h>
#समावेश <यंत्र/mmu.h>

/*
 * kernel भव address is required to implement vदो_स्मृति/pkmap/fixmap
 * Refer to यंत्र/processor.h क्रम System Memory Map
 *
 * It simply copies the PMD entry (poपूर्णांकer to 2nd level page table or hugepage)
 * from swapper pgdir to task pgdir. The 2nd level table/page is thus shared
 */
noअंतरभूत अटल पूर्णांक handle_kernel_vaddr_fault(अचिन्हित दीर्घ address)
अणु
	/*
	 * Synchronize this task's top level page-table
	 * with the 'reference' page table.
	 */
	pgd_t *pgd, *pgd_k;
	p4d_t *p4d, *p4d_k;
	pud_t *pud, *pud_k;
	pmd_t *pmd, *pmd_k;

	pgd = pgd_offset_fast(current->active_mm, address);
	pgd_k = pgd_offset_k(address);

	अगर (!pgd_present(*pgd_k))
		जाओ bad_area;

	p4d = p4d_offset(pgd, address);
	p4d_k = p4d_offset(pgd_k, address);
	अगर (!p4d_present(*p4d_k))
		जाओ bad_area;

	pud = pud_offset(p4d, address);
	pud_k = pud_offset(p4d_k, address);
	अगर (!pud_present(*pud_k))
		जाओ bad_area;

	pmd = pmd_offset(pud, address);
	pmd_k = pmd_offset(pud_k, address);
	अगर (!pmd_present(*pmd_k))
		जाओ bad_area;

	set_pmd(pmd, *pmd_k);

	/* XXX: create the TLB entry here */
	वापस 0;

bad_area:
	वापस 1;
पूर्ण

व्योम करो_page_fault(अचिन्हित दीर्घ address, काष्ठा pt_regs *regs)
अणु
	काष्ठा vm_area_काष्ठा *vma = शून्य;
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा mm_काष्ठा *mm = tsk->mm;
	पूर्णांक sig, si_code = SEGV_MAPERR;
	अचिन्हित पूर्णांक ग_लिखो = 0, exec = 0, mask;
	vm_fault_t fault = VM_FAULT_संक_अंश;	/* handle_mm_fault() output */
	अचिन्हित पूर्णांक flags;			/* handle_mm_fault() input */

	/*
	 * NOTE! We MUST NOT take any locks क्रम this हाल. We may
	 * be in an पूर्णांकerrupt or a critical region, and should
	 * only copy the inक्रमmation from the master page table,
	 * nothing more.
	 */
	अगर (address >= VMALLOC_START && !user_mode(regs)) अणु
		अगर (unlikely(handle_kernel_vaddr_fault(address)))
			जाओ no_context;
		अन्यथा
			वापस;
	पूर्ण

	/*
	 * If we're in an पूर्णांकerrupt or have no user
	 * context, we must not take the fault..
	 */
	अगर (faulthandler_disabled() || !mm)
		जाओ no_context;

	अगर (regs->ecr_cause & ECR_C_PROTV_STORE)	/* ST/EX */
		ग_लिखो = 1;
	अन्यथा अगर ((regs->ecr_vec == ECR_V_PROTV) &&
	         (regs->ecr_cause == ECR_C_PROTV_INST_FETCH))
		exec = 1;

	flags = FAULT_FLAG_DEFAULT;
	अगर (user_mode(regs))
		flags |= FAULT_FLAG_USER;
	अगर (ग_लिखो)
		flags |= FAULT_FLAG_WRITE;

	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, address);
retry:
	mmap_पढ़ो_lock(mm);

	vma = find_vma(mm, address);
	अगर (!vma)
		जाओ bad_area;
	अगर (unlikely(address < vma->vm_start)) अणु
		अगर (!(vma->vm_flags & VM_GROWSDOWN) || expand_stack(vma, address))
			जाओ bad_area;
	पूर्ण

	/*
	 * vm_area is good, now check permissions क्रम this memory access
	 */
	mask = VM_READ;
	अगर (ग_लिखो)
		mask = VM_WRITE;
	अगर (exec)
		mask = VM_EXEC;

	अगर (!(vma->vm_flags & mask)) अणु
		si_code = SEGV_ACCERR;
		जाओ bad_area;
	पूर्ण

	fault = handle_mm_fault(vma, address, flags, regs);

	/* Quick path to respond to संकेतs */
	अगर (fault_संकेत_pending(fault, regs)) अणु
		अगर (!user_mode(regs))
			जाओ no_context;
		वापस;
	पूर्ण

	/*
	 * Fault retry nuances, mmap_lock alपढ़ोy relinquished by core mm
	 */
	अगर (unlikely((fault & VM_FAULT_RETRY) &&
		     (flags & FAULT_FLAG_ALLOW_RETRY))) अणु
		flags |= FAULT_FLAG_TRIED;
		जाओ retry;
	पूर्ण

bad_area:
	mmap_पढ़ो_unlock(mm);

	/*
	 * Major/minor page fault accounting
	 * (in हाल of retry we only land here once)
	 */
	अगर (likely(!(fault & VM_FAULT_ERROR)))
		/* Normal वापस path: fault Handled Gracefully */
		वापस;

	अगर (!user_mode(regs))
		जाओ no_context;

	अगर (fault & VM_FAULT_OOM) अणु
		pagefault_out_of_memory();
		वापस;
	पूर्ण

	अगर (fault & VM_FAULT_SIGBUS) अणु
		sig = SIGBUS;
		si_code = BUS_ADRERR;
	पूर्ण
	अन्यथा अणु
		sig = संक_अंश;
	पूर्ण

	tsk->thपढ़ो.fault_address = address;
	क्रमce_sig_fault(sig, si_code, (व्योम __user *)address);
	वापस;

no_context:
	अगर (fixup_exception(regs))
		वापस;

	die("Oops", regs, address);
पूर्ण
