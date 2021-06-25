<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Memory fault handling क्रम Hexagon
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

/*
 * Page fault handling क्रम the Hexagon Virtual Machine.
 * Can also be called by a native port emulating the HVM
 * execptions.
 */

#समावेश <यंत्र/traps.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/extable.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/perf_event.h>

/*
 * Decode of hardware exception sends us to one of several
 * entry poपूर्णांकs.  At each, we generate canonical arguments
 * क्रम handling by the असलtract memory management code.
 */
#घोषणा FLT_IFETCH     -1
#घोषणा FLT_LOAD        0
#घोषणा FLT_STORE       1


/*
 * Canonical page fault handler
 */
व्योम करो_page_fault(अचिन्हित दीर्घ address, दीर्घ cause, काष्ठा pt_regs *regs)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mm_काष्ठा *mm = current->mm;
	पूर्णांक si_signo;
	पूर्णांक si_code = SEGV_MAPERR;
	vm_fault_t fault;
	स्थिर काष्ठा exception_table_entry *fixup;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;

	/*
	 * If we're in an पूर्णांकerrupt or have no user context,
	 * then must not take the fault.
	 */
	अगर (unlikely(in_पूर्णांकerrupt() || !mm))
		जाओ no_context;

	local_irq_enable();

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

good_area:
	/* Address space is OK.  Now check access rights. */
	si_code = SEGV_ACCERR;

	चयन (cause) अणु
	हाल FLT_IFETCH:
		अगर (!(vma->vm_flags & VM_EXEC))
			जाओ bad_area;
		अवरोध;
	हाल FLT_LOAD:
		अगर (!(vma->vm_flags & VM_READ))
			जाओ bad_area;
		अवरोध;
	हाल FLT_STORE:
		अगर (!(vma->vm_flags & VM_WRITE))
			जाओ bad_area;
		flags |= FAULT_FLAG_WRITE;
		अवरोध;
	पूर्ण

	fault = handle_mm_fault(vma, address, flags, regs);

	अगर (fault_संकेत_pending(fault, regs))
		वापस;

	/* The most common हाल -- we are करोne. */
	अगर (likely(!(fault & VM_FAULT_ERROR))) अणु
		अगर (flags & FAULT_FLAG_ALLOW_RETRY) अणु
			अगर (fault & VM_FAULT_RETRY) अणु
				flags |= FAULT_FLAG_TRIED;
				जाओ retry;
			पूर्ण
		पूर्ण

		mmap_पढ़ो_unlock(mm);
		वापस;
	पूर्ण

	mmap_पढ़ो_unlock(mm);

	/* Handle copyin/out exception हालs */
	अगर (!user_mode(regs))
		जाओ no_context;

	अगर (fault & VM_FAULT_OOM) अणु
		pagefault_out_of_memory();
		वापस;
	पूर्ण

	/* User-mode address is in the memory map, but we are
	 * unable to fix up the page fault.
	 */
	अगर (fault & VM_FAULT_SIGBUS) अणु
		si_signo = SIGBUS;
		si_code = BUS_ADRERR;
	पूर्ण
	/* Address is not in the memory map */
	अन्यथा अणु
		si_signo = संक_अंश;
		si_code  = SEGV_ACCERR;
	पूर्ण
	क्रमce_sig_fault(si_signo, si_code, (व्योम __user *)address);
	वापस;

bad_area:
	mmap_पढ़ो_unlock(mm);

	अगर (user_mode(regs)) अणु
		क्रमce_sig_fault(संक_अंश, si_code, (व्योम __user *)address);
		वापस;
	पूर्ण
	/* Kernel-mode fault falls through */

no_context:
	fixup = search_exception_tables(pt_elr(regs));
	अगर (fixup) अणु
		pt_set_elr(regs, fixup->fixup);
		वापस;
	पूर्ण

	/* Things are looking very, very bad now */
	bust_spinlocks(1);
	prपूर्णांकk(KERN_EMERG "Unable to handle kernel paging request at "
		"virtual address 0x%08lx, regs %p\n", address, regs);
	die("Bad Kernel VA", regs, SIGKILL);
पूर्ण


व्योम पढ़ो_protection_fault(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ badvadr = pt_badva(regs);

	करो_page_fault(badvadr, FLT_LOAD, regs);
पूर्ण

व्योम ग_लिखो_protection_fault(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ badvadr = pt_badva(regs);

	करो_page_fault(badvadr, FLT_STORE, regs);
पूर्ण

व्योम execute_protection_fault(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ badvadr = pt_badva(regs);

	करो_page_fault(badvadr, FLT_IFETCH, regs);
पूर्ण
