<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/m68k/mm/fault.c
 *
 *  Copyright (C) 1995  Hamish Macकरोnald
 */

#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/perf_event.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/traps.h>

बाह्य व्योम die_अगर_kernel(अक्षर *, काष्ठा pt_regs *, दीर्घ);

पूर्णांक send_fault_sig(काष्ठा pt_regs *regs)
अणु
	पूर्णांक signo, si_code;
	व्योम __user *addr;

	signo = current->thपढ़ो.signo;
	si_code = current->thपढ़ो.code;
	addr = (व्योम __user *)current->thपढ़ो.faddr;
	pr_debug("send_fault_sig: %p,%d,%d\n", addr, signo, si_code);

	अगर (user_mode(regs)) अणु
		क्रमce_sig_fault(signo, si_code, addr);
	पूर्ण अन्यथा अणु
		अगर (fixup_exception(regs))
			वापस -1;

		//अगर (signo == SIGBUS)
		//	क्रमce_sig_fault(si_signo, si_code, addr);

		/*
		 * Oops. The kernel tried to access some bad page. We'll have to
		 * terminate things with extreme prejudice.
		 */
		अगर ((अचिन्हित दीर्घ)addr < PAGE_SIZE)
			pr_alert("Unable to handle kernel NULL pointer dereference");
		अन्यथा
			pr_alert("Unable to handle kernel access");
		pr_cont(" at virtual address %p\n", addr);
		die_अगर_kernel("Oops", regs, 0 /*error_code*/);
		करो_निकास(SIGKILL);
	पूर्ण

	वापस 1;
पूर्ण

/*
 * This routine handles page faults.  It determines the problem, and
 * then passes it off to one of the appropriate routines.
 *
 * error_code:
 *	bit 0 == 0 means no page found, 1 means protection fault
 *	bit 1 == 0 means पढ़ो, 1 means ग_लिखो
 *
 * If this routine detects a bad access, it वापसs 1, otherwise it
 * वापसs 0.
 */
पूर्णांक करो_page_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address,
			      अचिन्हित दीर्घ error_code)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा * vma;
	vm_fault_t fault;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;

	pr_debug("do page fault:\nregs->sr=%#x, regs->pc=%#lx, address=%#lx, %ld, %p\n",
		regs->sr, regs->pc, address, error_code, mm ? mm->pgd : शून्य);

	/*
	 * If we're in an पूर्णांकerrupt or have no user
	 * context, we must not take the fault..
	 */
	अगर (faulthandler_disabled() || !mm)
		जाओ no_context;

	अगर (user_mode(regs))
		flags |= FAULT_FLAG_USER;

	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, address);
retry:
	mmap_पढ़ो_lock(mm);

	vma = find_vma(mm, address);
	अगर (!vma)
		जाओ map_err;
	अगर (vma->vm_flags & VM_IO)
		जाओ acc_err;
	अगर (vma->vm_start <= address)
		जाओ good_area;
	अगर (!(vma->vm_flags & VM_GROWSDOWN))
		जाओ map_err;
	अगर (user_mode(regs)) अणु
		/* Accessing the stack below usp is always a bug.  The
		   "+ 256" is there due to some inकाष्ठाions करोing
		   pre-decrement on the stack and that करोesn't show up
		   until later.  */
		अगर (address + 256 < rdusp())
			जाओ map_err;
	पूर्ण
	अगर (expand_stack(vma, address))
		जाओ map_err;

/*
 * Ok, we have a good vm_area क्रम this memory access, so
 * we can handle it..
 */
good_area:
	pr_debug("do_page_fault: good_area\n");
	चयन (error_code & 3) अणु
		शेष:	/* 3: ग_लिखो, present */
			fallthrough;
		हाल 2:		/* ग_लिखो, not present */
			अगर (!(vma->vm_flags & VM_WRITE))
				जाओ acc_err;
			flags |= FAULT_FLAG_WRITE;
			अवरोध;
		हाल 1:		/* पढ़ो, present */
			जाओ acc_err;
		हाल 0:		/* पढ़ो, not present */
			अगर (unlikely(!vma_is_accessible(vma)))
				जाओ acc_err;
	पूर्ण

	/*
	 * If क्रम any reason at all we couldn't handle the fault,
	 * make sure we निकास gracefully rather than endlessly reकरो
	 * the fault.
	 */

	fault = handle_mm_fault(vma, address, flags, regs);
	pr_debug("handle_mm_fault returns %x\n", fault);

	अगर (fault_संकेत_pending(fault, regs))
		वापस 0;

	अगर (unlikely(fault & VM_FAULT_ERROR)) अणु
		अगर (fault & VM_FAULT_OOM)
			जाओ out_of_memory;
		अन्यथा अगर (fault & VM_FAULT_संक_अंश)
			जाओ map_err;
		अन्यथा अगर (fault & VM_FAULT_SIGBUS)
			जाओ bus_err;
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
	वापस 0;

/*
 * We ran out of memory, or some other thing happened to us that made
 * us unable to handle the page fault gracefully.
 */
out_of_memory:
	mmap_पढ़ो_unlock(mm);
	अगर (!user_mode(regs))
		जाओ no_context;
	pagefault_out_of_memory();
	वापस 0;

no_context:
	current->thपढ़ो.signo = SIGBUS;
	current->thपढ़ो.faddr = address;
	वापस send_fault_sig(regs);

bus_err:
	current->thपढ़ो.signo = SIGBUS;
	current->thपढ़ो.code = BUS_ADRERR;
	current->thपढ़ो.faddr = address;
	जाओ send_sig;

map_err:
	current->thपढ़ो.signo = संक_अंश;
	current->thपढ़ो.code = SEGV_MAPERR;
	current->thपढ़ो.faddr = address;
	जाओ send_sig;

acc_err:
	current->thपढ़ो.signo = संक_अंश;
	current->thपढ़ो.code = SEGV_ACCERR;
	current->thपढ़ो.faddr = address;

send_sig:
	mmap_पढ़ो_unlock(mm);
	वापस send_fault_sig(regs);
पूर्ण
