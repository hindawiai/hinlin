<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mm/fault.c
 *
 *  Copyright (C) 1995  Linus Torvalds
 *  Modअगरications क्रम ARM processor (c) 1995-2004 Russell King
 */
#समावेश <linux/extable.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/mm.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/init.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/debug.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/perf_event.h>

#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "fault.h"

#अगर_घोषित CONFIG_MMU

/*
 * This is useful to dump out the page tables associated with
 * 'addr' in mm 'mm'.
 */
व्योम show_pte(स्थिर अक्षर *lvl, काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgd;

	अगर (!mm)
		mm = &init_mm;

	prपूर्णांकk("%spgd = %p\n", lvl, mm->pgd);
	pgd = pgd_offset(mm, addr);
	prपूर्णांकk("%s[%08lx] *pgd=%08llx", lvl, addr, (दीर्घ दीर्घ)pgd_val(*pgd));

	करो अणु
		p4d_t *p4d;
		pud_t *pud;
		pmd_t *pmd;
		pte_t *pte;

		p4d = p4d_offset(pgd, addr);
		अगर (p4d_none(*p4d))
			अवरोध;

		अगर (p4d_bad(*p4d)) अणु
			pr_cont("(bad)");
			अवरोध;
		पूर्ण

		pud = pud_offset(p4d, addr);
		अगर (PTRS_PER_PUD != 1)
			pr_cont(", *pud=%08llx", (दीर्घ दीर्घ)pud_val(*pud));

		अगर (pud_none(*pud))
			अवरोध;

		अगर (pud_bad(*pud)) अणु
			pr_cont("(bad)");
			अवरोध;
		पूर्ण

		pmd = pmd_offset(pud, addr);
		अगर (PTRS_PER_PMD != 1)
			pr_cont(", *pmd=%08llx", (दीर्घ दीर्घ)pmd_val(*pmd));

		अगर (pmd_none(*pmd))
			अवरोध;

		अगर (pmd_bad(*pmd)) अणु
			pr_cont("(bad)");
			अवरोध;
		पूर्ण

		/* We must not map this अगर we have highmem enabled */
		अगर (PageHighMem(pfn_to_page(pmd_val(*pmd) >> PAGE_SHIFT)))
			अवरोध;

		pte = pte_offset_map(pmd, addr);
		pr_cont(", *pte=%08llx", (दीर्घ दीर्घ)pte_val(*pte));
#अगर_अघोषित CONFIG_ARM_LPAE
		pr_cont(", *ppte=%08llx",
		       (दीर्घ दीर्घ)pte_val(pte[PTE_HWTABLE_PTRS]));
#पूर्ण_अगर
		pte_unmap(pte);
	पूर्ण जबतक(0);

	pr_cont("\n");
पूर्ण
#अन्यथा					/* CONFIG_MMU */
व्योम show_pte(स्थिर अक्षर *lvl, काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु पूर्ण
#पूर्ण_अगर					/* CONFIG_MMU */

/*
 * Oops.  The kernel tried to access some page that wasn't present.
 */
अटल व्योम
__करो_kernel_fault(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr,
		  काष्ठा pt_regs *regs)
अणु
	/*
	 * Are we prepared to handle this kernel fault?
	 */
	अगर (fixup_exception(regs))
		वापस;

	/*
	 * No handler, we'll have to terminate things with extreme prejudice.
	 */
	bust_spinlocks(1);
	pr_alert("8<--- cut here ---\n");
	pr_alert("Unable to handle kernel %s at virtual address %08lx\n",
		 (addr < PAGE_SIZE) ? "NULL pointer dereference" :
		 "paging request", addr);

	show_pte(KERN_ALERT, mm, addr);
	die("Oops", regs, fsr);
	bust_spinlocks(0);
	करो_निकास(SIGKILL);
पूर्ण

/*
 * Something tried to access memory that isn't in our memory map..
 * User mode accesses just cause a संक_अंश
 */
अटल व्योम
__करो_user_fault(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr, अचिन्हित पूर्णांक sig,
		पूर्णांक code, काष्ठा pt_regs *regs)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	अगर (addr > TASK_SIZE)
		harden_branch_predictor();

#अगर_घोषित CONFIG_DEBUG_USER
	अगर (((user_debug & UDBG_SEGV) && (sig == संक_अंश)) ||
	    ((user_debug & UDBG_BUS)  && (sig == SIGBUS))) अणु
		pr_err("8<--- cut here ---\n");
		pr_err("%s: unhandled page fault (%d) at 0x%08lx, code 0x%03x\n",
		       tsk->comm, sig, addr, fsr);
		show_pte(KERN_ERR, tsk->mm, addr);
		show_regs(regs);
	पूर्ण
#पूर्ण_अगर
#अगर_अघोषित CONFIG_KUSER_HELPERS
	अगर ((sig == संक_अंश) && ((addr & PAGE_MASK) == 0xffff0000))
		prपूर्णांकk_ratelimited(KERN_DEBUG
				   "%s: CONFIG_KUSER_HELPERS disabled at 0x%08lx\n",
				   tsk->comm, addr);
#पूर्ण_अगर

	tsk->thपढ़ो.address = addr;
	tsk->thपढ़ो.error_code = fsr;
	tsk->thपढ़ो.trap_no = 14;
	क्रमce_sig_fault(sig, code, (व्योम __user *)addr);
पूर्ण

व्योम करो_bad_area(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr, काष्ठा pt_regs *regs)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा mm_काष्ठा *mm = tsk->active_mm;

	/*
	 * If we are in kernel mode at this poपूर्णांक, we
	 * have no context to handle this fault with.
	 */
	अगर (user_mode(regs))
		__करो_user_fault(addr, fsr, संक_अंश, SEGV_MAPERR, regs);
	अन्यथा
		__करो_kernel_fault(mm, addr, fsr, regs);
पूर्ण

#अगर_घोषित CONFIG_MMU
#घोषणा VM_FAULT_BADMAP		0x010000
#घोषणा VM_FAULT_BADACCESS	0x020000

/*
 * Check that the permissions on the VMA allow क्रम the fault which occurred.
 * If we encountered a ग_लिखो fault, we must have ग_लिखो permission, otherwise
 * we allow any permission.
 */
अटल अंतरभूत bool access_error(अचिन्हित पूर्णांक fsr, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित पूर्णांक mask = VM_ACCESS_FLAGS;

	अगर ((fsr & FSR_WRITE) && !(fsr & FSR_CM))
		mask = VM_WRITE;
	अगर (fsr & FSR_LNX_PF)
		mask = VM_EXEC;

	वापस vma->vm_flags & mask ? false : true;
पूर्ण

अटल vm_fault_t __kprobes
__करो_page_fault(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr,
		अचिन्हित पूर्णांक flags, काष्ठा task_काष्ठा *tsk,
		काष्ठा pt_regs *regs)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	vm_fault_t fault;

	vma = find_vma(mm, addr);
	fault = VM_FAULT_BADMAP;
	अगर (unlikely(!vma))
		जाओ out;
	अगर (unlikely(vma->vm_start > addr))
		जाओ check_stack;

	/*
	 * Ok, we have a good vm_area क्रम this
	 * memory access, so we can handle it.
	 */
good_area:
	अगर (access_error(fsr, vma)) अणु
		fault = VM_FAULT_BADACCESS;
		जाओ out;
	पूर्ण

	वापस handle_mm_fault(vma, addr & PAGE_MASK, flags, regs);

check_stack:
	/* Don't allow expansion below FIRST_USER_ADDRESS */
	अगर (vma->vm_flags & VM_GROWSDOWN &&
	    addr >= FIRST_USER_ADDRESS && !expand_stack(vma, addr))
		जाओ good_area;
out:
	वापस fault;
पूर्ण

अटल पूर्णांक __kprobes
करो_page_fault(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr, काष्ठा pt_regs *regs)
अणु
	काष्ठा task_काष्ठा *tsk;
	काष्ठा mm_काष्ठा *mm;
	पूर्णांक sig, code;
	vm_fault_t fault;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;

	अगर (kprobe_page_fault(regs, fsr))
		वापस 0;

	tsk = current;
	mm  = tsk->mm;

	/* Enable पूर्णांकerrupts अगर they were enabled in the parent context. */
	अगर (पूर्णांकerrupts_enabled(regs))
		local_irq_enable();

	/*
	 * If we're in an पूर्णांकerrupt or have no user
	 * context, we must not take the fault..
	 */
	अगर (faulthandler_disabled() || !mm)
		जाओ no_context;

	अगर (user_mode(regs))
		flags |= FAULT_FLAG_USER;
	अगर ((fsr & FSR_WRITE) && !(fsr & FSR_CM))
		flags |= FAULT_FLAG_WRITE;

	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, addr);

	/*
	 * As per x86, we may deadlock here.  However, since the kernel only
	 * validly references user space from well defined areas of the code,
	 * we can bug out early अगर this is from code which shouldn't.
	 */
	अगर (!mmap_पढ़ो_trylock(mm)) अणु
		अगर (!user_mode(regs) && !search_exception_tables(regs->ARM_pc))
			जाओ no_context;
retry:
		mmap_पढ़ो_lock(mm);
	पूर्ण अन्यथा अणु
		/*
		 * The above करोwn_पढ़ो_trylock() might have succeeded in
		 * which हाल, we'll have missed the might_sleep() from
		 * करोwn_पढ़ो()
		 */
		might_sleep();
#अगर_घोषित CONFIG_DEBUG_VM
		अगर (!user_mode(regs) &&
		    !search_exception_tables(regs->ARM_pc))
			जाओ no_context;
#पूर्ण_अगर
	पूर्ण

	fault = __करो_page_fault(mm, addr, fsr, flags, tsk, regs);

	/* If we need to retry but a fatal संकेत is pending, handle the
	 * संकेत first. We करो not need to release the mmap_lock because
	 * it would alपढ़ोy be released in __lock_page_or_retry in
	 * mm/filemap.c. */
	अगर (fault_संकेत_pending(fault, regs)) अणु
		अगर (!user_mode(regs))
			जाओ no_context;
		वापस 0;
	पूर्ण

	अगर (!(fault & VM_FAULT_ERROR) && flags & FAULT_FLAG_ALLOW_RETRY) अणु
		अगर (fault & VM_FAULT_RETRY) अणु
			flags |= FAULT_FLAG_TRIED;
			जाओ retry;
		पूर्ण
	पूर्ण

	mmap_पढ़ो_unlock(mm);

	/*
	 * Handle the "normal" हाल first - VM_FAULT_MAJOR
	 */
	अगर (likely(!(fault & (VM_FAULT_ERROR | VM_FAULT_BADMAP | VM_FAULT_BADACCESS))))
		वापस 0;

	/*
	 * If we are in kernel mode at this poपूर्णांक, we
	 * have no context to handle this fault with.
	 */
	अगर (!user_mode(regs))
		जाओ no_context;

	अगर (fault & VM_FAULT_OOM) अणु
		/*
		 * We ran out of memory, call the OOM समाप्तer, and वापस to
		 * userspace (which will retry the fault, or समाप्त us अगर we
		 * got oom-समाप्तed)
		 */
		pagefault_out_of_memory();
		वापस 0;
	पूर्ण

	अगर (fault & VM_FAULT_SIGBUS) अणु
		/*
		 * We had some memory, but were unable to
		 * successfully fix up this page fault.
		 */
		sig = SIGBUS;
		code = BUS_ADRERR;
	पूर्ण अन्यथा अणु
		/*
		 * Something tried to access memory that
		 * isn't in our memory map..
		 */
		sig = संक_अंश;
		code = fault == VM_FAULT_BADACCESS ?
			SEGV_ACCERR : SEGV_MAPERR;
	पूर्ण

	__करो_user_fault(addr, fsr, sig, code, regs);
	वापस 0;

no_context:
	__करो_kernel_fault(mm, addr, fsr, regs);
	वापस 0;
पूर्ण
#अन्यथा					/* CONFIG_MMU */
अटल पूर्णांक
करो_page_fault(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr, काष्ठा pt_regs *regs)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर					/* CONFIG_MMU */

/*
 * First Level Translation Fault Handler
 *
 * We enter here because the first level page table करोesn't contain
 * a valid entry क्रम the address.
 *
 * If the address is in kernel space (>= TASK_SIZE), then we are
 * probably faulting in the vदो_स्मृति() area.
 *
 * If the init_task's first level page tables contains the relevant
 * entry, we copy the it to this task.  If not, we send the process
 * a संकेत, fixup the exception, or oops the kernel.
 *
 * NOTE! We MUST NOT take any locks क्रम this हाल. We may be in an
 * पूर्णांकerrupt or a critical region, and should only copy the inक्रमmation
 * from the master page table, nothing more.
 */
#अगर_घोषित CONFIG_MMU
अटल पूर्णांक __kprobes
करो_translation_fault(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr,
		     काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक index;
	pgd_t *pgd, *pgd_k;
	p4d_t *p4d, *p4d_k;
	pud_t *pud, *pud_k;
	pmd_t *pmd, *pmd_k;

	अगर (addr < TASK_SIZE)
		वापस करो_page_fault(addr, fsr, regs);

	अगर (user_mode(regs))
		जाओ bad_area;

	index = pgd_index(addr);

	pgd = cpu_get_pgd() + index;
	pgd_k = init_mm.pgd + index;

	p4d = p4d_offset(pgd, addr);
	p4d_k = p4d_offset(pgd_k, addr);

	अगर (p4d_none(*p4d_k))
		जाओ bad_area;
	अगर (!p4d_present(*p4d))
		set_p4d(p4d, *p4d_k);

	pud = pud_offset(p4d, addr);
	pud_k = pud_offset(p4d_k, addr);

	अगर (pud_none(*pud_k))
		जाओ bad_area;
	अगर (!pud_present(*pud))
		set_pud(pud, *pud_k);

	pmd = pmd_offset(pud, addr);
	pmd_k = pmd_offset(pud_k, addr);

#अगर_घोषित CONFIG_ARM_LPAE
	/*
	 * Only one hardware entry per PMD with LPAE.
	 */
	index = 0;
#अन्यथा
	/*
	 * On ARM one Linux PGD entry contains two hardware entries (see page
	 * tables layout in pgtable.h). We normally guarantee that we always
	 * fill both L1 entries. But create_mapping() करोesn't follow the rule.
	 * It can create iniभागidual L1 entries, so here we have to call
	 * pmd_none() check क्रम the entry really corresponded to address, not
	 * क्रम the first of pair.
	 */
	index = (addr >> SECTION_SHIFT) & 1;
#पूर्ण_अगर
	अगर (pmd_none(pmd_k[index]))
		जाओ bad_area;

	copy_pmd(pmd, pmd_k);
	वापस 0;

bad_area:
	करो_bad_area(addr, fsr, regs);
	वापस 0;
पूर्ण
#अन्यथा					/* CONFIG_MMU */
अटल पूर्णांक
करो_translation_fault(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr,
		     काष्ठा pt_regs *regs)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर					/* CONFIG_MMU */

/*
 * Some section permission faults need to be handled gracefully.
 * They can happen due to a __अणुget,putपूर्ण_user during an oops.
 */
#अगर_अघोषित CONFIG_ARM_LPAE
अटल पूर्णांक
करो_sect_fault(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr, काष्ठा pt_regs *regs)
अणु
	करो_bad_area(addr, fsr, regs);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARM_LPAE */

/*
 * This पात handler always वापसs "fault".
 */
अटल पूर्णांक
करो_bad(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr, काष्ठा pt_regs *regs)
अणु
	वापस 1;
पूर्ण

काष्ठा fsr_info अणु
	पूर्णांक	(*fn)(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr, काष्ठा pt_regs *regs);
	पूर्णांक	sig;
	पूर्णांक	code;
	स्थिर अक्षर *name;
पूर्ण;

/* FSR definition */
#अगर_घोषित CONFIG_ARM_LPAE
#समावेश "fsr-3level.c"
#अन्यथा
#समावेश "fsr-2level.c"
#पूर्ण_अगर

व्योम __init
hook_fault_code(पूर्णांक nr, पूर्णांक (*fn)(अचिन्हित दीर्घ, अचिन्हित पूर्णांक, काष्ठा pt_regs *),
		पूर्णांक sig, पूर्णांक code, स्थिर अक्षर *name)
अणु
	अगर (nr < 0 || nr >= ARRAY_SIZE(fsr_info))
		BUG();

	fsr_info[nr].fn   = fn;
	fsr_info[nr].sig  = sig;
	fsr_info[nr].code = code;
	fsr_info[nr].name = name;
पूर्ण

/*
 * Dispatch a data पात to the relevant handler.
 */
यंत्रlinkage व्योम
करो_DataAbort(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr, काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा fsr_info *inf = fsr_info + fsr_fs(fsr);

	अगर (!inf->fn(addr, fsr & ~FSR_LNX_PF, regs))
		वापस;

	pr_alert("8<--- cut here ---\n");
	pr_alert("Unhandled fault: %s (0x%03x) at 0x%08lx\n",
		inf->name, fsr, addr);
	show_pte(KERN_ALERT, current->mm, addr);

	arm_notअगरy_die("", regs, inf->sig, inf->code, (व्योम __user *)addr,
		       fsr, 0);
पूर्ण

व्योम __init
hook_अगरault_code(पूर्णांक nr, पूर्णांक (*fn)(अचिन्हित दीर्घ, अचिन्हित पूर्णांक, काष्ठा pt_regs *),
		 पूर्णांक sig, पूर्णांक code, स्थिर अक्षर *name)
अणु
	अगर (nr < 0 || nr >= ARRAY_SIZE(अगरsr_info))
		BUG();

	अगरsr_info[nr].fn   = fn;
	अगरsr_info[nr].sig  = sig;
	अगरsr_info[nr].code = code;
	अगरsr_info[nr].name = name;
पूर्ण

यंत्रlinkage व्योम
करो_PrefetchAbort(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक अगरsr, काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा fsr_info *inf = अगरsr_info + fsr_fs(अगरsr);

	अगर (!inf->fn(addr, अगरsr | FSR_LNX_PF, regs))
		वापस;

	pr_alert("Unhandled prefetch abort: %s (0x%03x) at 0x%08lx\n",
		inf->name, अगरsr, addr);

	arm_notअगरy_die("", regs, inf->sig, inf->code, (व्योम __user *)addr,
		       अगरsr, 0);
पूर्ण

/*
 * Abort handler to be used only during first unmasking of asynchronous पातs
 * on the boot CPU. This makes sure that the machine will not die अगर the
 * firmware/bootloader left an imprecise पात pending क्रम us to trip over.
 */
अटल पूर्णांक __init early_पात_handler(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr,
				      काष्ठा pt_regs *regs)
अणु
	pr_warn("Hit pending asynchronous external abort (FSR=0x%08x) during "
		"first unmask, this is most likely caused by a "
		"firmware/bootloader bug.\n", fsr);

	वापस 0;
पूर्ण

व्योम __init early_abt_enable(व्योम)
अणु
	fsr_info[FSR_FS_AEA].fn = early_पात_handler;
	local_abt_enable();
	fsr_info[FSR_FS_AEA].fn = करो_bad;
पूर्ण

#अगर_अघोषित CONFIG_ARM_LPAE
अटल पूर्णांक __init exceptions_init(व्योम)
अणु
	अगर (cpu_architecture() >= CPU_ARCH_ARMv6) अणु
		hook_fault_code(4, करो_translation_fault, संक_अंश, SEGV_MAPERR,
				"I-cache maintenance fault");
	पूर्ण

	अगर (cpu_architecture() >= CPU_ARCH_ARMv7) अणु
		/*
		 * TODO: Access flag faults पूर्णांकroduced in ARMv6K.
		 * Runसमय check क्रम 'K' extension is needed
		 */
		hook_fault_code(3, करो_bad, संक_अंश, SEGV_MAPERR,
				"section access flag fault");
		hook_fault_code(6, करो_bad, संक_अंश, SEGV_MAPERR,
				"section access flag fault");
	पूर्ण

	वापस 0;
पूर्ण

arch_initcall(exceptions_init);
#पूर्ण_अगर
