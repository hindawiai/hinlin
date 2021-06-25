<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MMU fault handling support.
 *
 * Copyright (C) 1998-2002 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/extable.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/perf_event.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/exception.h>

बाह्य पूर्णांक die(अक्षर *, काष्ठा pt_regs *, दीर्घ);

/*
 * Return TRUE अगर ADDRESS poपूर्णांकs at a page in the kernel's mapped segment
 * (inside region 5, on ia64) and that page is present.
 */
अटल पूर्णांक
mapped_kernel_page_is_present (अचिन्हित दीर्घ address)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *ptep, pte;

	pgd = pgd_offset_k(address);
	अगर (pgd_none(*pgd) || pgd_bad(*pgd))
		वापस 0;

	p4d = p4d_offset(pgd, address);
	अगर (p4d_none(*p4d) || p4d_bad(*p4d))
		वापस 0;

	pud = pud_offset(p4d, address);
	अगर (pud_none(*pud) || pud_bad(*pud))
		वापस 0;

	pmd = pmd_offset(pud, address);
	अगर (pmd_none(*pmd) || pmd_bad(*pmd))
		वापस 0;

	ptep = pte_offset_kernel(pmd, address);
	अगर (!ptep)
		वापस 0;

	pte = *ptep;
	वापस pte_present(pte);
पूर्ण

#	define VM_READ_BIT	0
#	define VM_WRITE_BIT	1
#	define VM_EXEC_BIT	2

व्योम __kprobes
ia64_करो_page_fault (अचिन्हित दीर्घ address, अचिन्हित दीर्घ isr, काष्ठा pt_regs *regs)
अणु
	पूर्णांक संकेत = संक_अंश, code = SEGV_MAPERR;
	काष्ठा vm_area_काष्ठा *vma, *prev_vma;
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ mask;
	vm_fault_t fault;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;

	mask = ((((isr >> IA64_ISR_X_BIT) & 1UL) << VM_EXEC_BIT)
		| (((isr >> IA64_ISR_W_BIT) & 1UL) << VM_WRITE_BIT));

	/* mmap_lock is perक्रमmance critical.... */
	prefetchw(&mm->mmap_lock);

	/*
	 * If we're in an पूर्णांकerrupt or have no user context, we must not take the fault..
	 */
	अगर (faulthandler_disabled() || !mm)
		जाओ no_context;

	/*
	 * This is to handle the kprobes on user space access inकाष्ठाions
	 */
	अगर (kprobe_page_fault(regs, TRAP_BRKPT))
		वापस;

	अगर (user_mode(regs))
		flags |= FAULT_FLAG_USER;
	अगर (mask & VM_WRITE)
		flags |= FAULT_FLAG_WRITE;

	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, address);
retry:
	mmap_पढ़ो_lock(mm);

	vma = find_vma_prev(mm, address, &prev_vma);
	अगर (!vma && !prev_vma )
		जाओ bad_area;

        /*
         * find_vma_prev() वापसs vma such that address < vma->vm_end or शून्य
         *
         * May find no vma, but could be that the last vm area is the
         * रेजिस्टर backing store that needs to expand upwards, in
         * this हाल vma will be null, but prev_vma will ne non-null
         */
        अगर (( !vma && prev_vma ) || (address < vma->vm_start) )
		जाओ check_expansion;

  good_area:
	code = SEGV_ACCERR;

	/* OK, we've got a good vm_area क्रम this memory area.  Check the access permissions: */

#	अगर (((1 << VM_READ_BIT) != VM_READ || (1 << VM_WRITE_BIT) != VM_WRITE) \
	    || (1 << VM_EXEC_BIT) != VM_EXEC)
#		error File is out of sync with <linux/mm.h>.  Please update.
#	endअगर

	अगर (((isr >> IA64_ISR_R_BIT) & 1UL) && (!(vma->vm_flags & (VM_READ | VM_WRITE))))
		जाओ bad_area;

	अगर ((vma->vm_flags & mask) != mask)
		जाओ bad_area;

	/*
	 * If क्रम any reason at all we couldn't handle the fault, make
	 * sure we निकास gracefully rather than endlessly reकरो the
	 * fault.
	 */
	fault = handle_mm_fault(vma, address, flags, regs);

	अगर (fault_संकेत_pending(fault, regs))
		वापस;

	अगर (unlikely(fault & VM_FAULT_ERROR)) अणु
		/*
		 * We ran out of memory, or some other thing happened
		 * to us that made us unable to handle the page fault
		 * gracefully.
		 */
		अगर (fault & VM_FAULT_OOM) अणु
			जाओ out_of_memory;
		पूर्ण अन्यथा अगर (fault & VM_FAULT_संक_अंश) अणु
			जाओ bad_area;
		पूर्ण अन्यथा अगर (fault & VM_FAULT_SIGBUS) अणु
			संकेत = SIGBUS;
			जाओ bad_area;
		पूर्ण
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

  check_expansion:
	अगर (!(prev_vma && (prev_vma->vm_flags & VM_GROWSUP) && (address == prev_vma->vm_end))) अणु
		अगर (!vma)
			जाओ bad_area;
		अगर (!(vma->vm_flags & VM_GROWSDOWN))
			जाओ bad_area;
		अगर (REGION_NUMBER(address) != REGION_NUMBER(vma->vm_start)
		    || REGION_OFFSET(address) >= RGN_MAP_LIMIT)
			जाओ bad_area;
		अगर (expand_stack(vma, address))
			जाओ bad_area;
	पूर्ण अन्यथा अणु
		vma = prev_vma;
		अगर (REGION_NUMBER(address) != REGION_NUMBER(vma->vm_start)
		    || REGION_OFFSET(address) >= RGN_MAP_LIMIT)
			जाओ bad_area;
		/*
		 * Since the रेजिस्टर backing store is accessed sequentially,
		 * we disallow growing it by more than a page at a समय.
		 */
		अगर (address > vma->vm_end + PAGE_SIZE - माप(दीर्घ))
			जाओ bad_area;
		अगर (expand_upwards(vma, address))
			जाओ bad_area;
	पूर्ण
	जाओ good_area;

  bad_area:
	mmap_पढ़ो_unlock(mm);
	अगर ((isr & IA64_ISR_SP)
	    || ((isr & IA64_ISR_NA) && (isr & IA64_ISR_CODE_MASK) == IA64_ISR_CODE_LFETCH))
	अणु
		/*
		 * This fault was due to a speculative load or lfetch.fault, set the "ed"
		 * bit in the psr to ensure क्रमward progress.  (Target रेजिस्टर will get a
		 * NaT क्रम ld.s, lfetch will be canceled.)
		 */
		ia64_psr(regs)->ed = 1;
		वापस;
	पूर्ण
	अगर (user_mode(regs)) अणु
		क्रमce_sig_fault(संकेत, code, (व्योम __user *) address,
				0, __ISR_VALID, isr);
		वापस;
	पूर्ण

  no_context:
	अगर ((isr & IA64_ISR_SP)
	    || ((isr & IA64_ISR_NA) && (isr & IA64_ISR_CODE_MASK) == IA64_ISR_CODE_LFETCH))
	अणु
		/*
		 * This fault was due to a speculative load or lfetch.fault, set the "ed"
		 * bit in the psr to ensure क्रमward progress.  (Target रेजिस्टर will get a
		 * NaT क्रम ld.s, lfetch will be canceled.)
		 */
		ia64_psr(regs)->ed = 1;
		वापस;
	पूर्ण

	/*
	 * Since we have no vma's क्रम region 5, we might get here even अगर the address is
	 * valid, due to the VHPT walker inserting a non present translation that becomes
	 * stale. If that happens, the non present fault handler alपढ़ोy purged the stale
	 * translation, which fixed the problem. So, we check to see अगर the translation is
	 * valid, and वापस अगर it is.
	 */
	अगर (REGION_NUMBER(address) == 5 && mapped_kernel_page_is_present(address))
		वापस;

	अगर (ia64_करोne_with_exception(regs))
		वापस;

	/*
	 * Oops. The kernel tried to access some bad page. We'll have to terminate things
	 * with extreme prejudice.
	 */
	bust_spinlocks(1);

	अगर (address < PAGE_SIZE)
		prपूर्णांकk(KERN_ALERT "Unable to handle kernel NULL pointer dereference (address %016lx)\n", address);
	अन्यथा
		prपूर्णांकk(KERN_ALERT "Unable to handle kernel paging request at "
		       "virtual address %016lx\n", address);
	अगर (die("Oops", regs, isr))
		regs = शून्य;
	bust_spinlocks(0);
	अगर (regs)
		करो_निकास(SIGKILL);
	वापस;

  out_of_memory:
	mmap_पढ़ो_unlock(mm);
	अगर (!user_mode(regs))
		जाओ no_context;
	pagefault_out_of_memory();
पूर्ण
