<शैली गुरु>
/*
 *  arch/microblaze/mm/fault.c
 *
 *    Copyright (C) 2007 Xilinx, Inc.  All rights reserved.
 *
 *  Derived from "arch/ppc/mm/fault.c"
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Derived from "arch/i386/mm/fault.c"
 *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 *
 *  Modअगरied by Cort Dougan and Paul Mackerras.
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.
 *
 */

#समावेश <linux/extable.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/perf_event.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmu.h>
#समावेश <linux/mmu_context.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/exceptions.h>

अटल अचिन्हित दीर्घ pte_misses;	/* updated by करो_page_fault() */
अटल अचिन्हित दीर्घ pte_errors;	/* updated by करो_page_fault() */

/*
 * Check whether the inकाष्ठाion at regs->pc is a store using
 * an update addressing क्रमm which will update r1.
 */
अटल पूर्णांक store_updates_sp(काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक inst;

	अगर (get_user(inst, (अचिन्हित पूर्णांक __user *)regs->pc))
		वापस 0;
	/* check क्रम 1 in the rD field */
	अगर (((inst >> 21) & 0x1f) != 1)
		वापस 0;
	/* check क्रम store opcodes */
	अगर ((inst & 0xd0000000) == 0xd0000000)
		वापस 1;
	वापस 0;
पूर्ण


/*
 * bad_page_fault is called when we have a bad access from the kernel.
 * It is called from करो_page_fault above and from some of the procedures
 * in traps.c.
 */
व्योम bad_page_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address, पूर्णांक sig)
अणु
	स्थिर काष्ठा exception_table_entry *fixup;
/* MS: no context */
	/* Are we prepared to handle this fault?  */
	fixup = search_exception_tables(regs->pc);
	अगर (fixup) अणु
		regs->pc = fixup->fixup;
		वापस;
	पूर्ण

	/* kernel has accessed a bad area */
	die("kernel access of bad area", regs, sig);
पूर्ण

/*
 * The error_code parameter is ESR क्रम a data fault,
 * 0 क्रम an inकाष्ठाion fault.
 */
व्योम करो_page_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address,
		   अचिन्हित दीर्घ error_code)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mm_काष्ठा *mm = current->mm;
	पूर्णांक code = SEGV_MAPERR;
	पूर्णांक is_ग_लिखो = error_code & ESR_S;
	vm_fault_t fault;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;

	regs->ear = address;
	regs->esr = error_code;

	/* On a kernel SLB miss we can only check क्रम a valid exception entry */
	अगर (unlikely(kernel_mode(regs) && (address >= TASK_SIZE))) अणु
		pr_warn("kernel task_size exceed");
		_exception(संक_अंश, regs, code, address);
	पूर्ण

	/* क्रम instr TLB miss and instr storage exception ESR_S is undefined */
	अगर ((error_code & 0x13) == 0x13 || (error_code & 0x11) == 0x11)
		is_ग_लिखो = 0;

	अगर (unlikely(faulthandler_disabled() || !mm)) अणु
		अगर (kernel_mode(regs))
			जाओ bad_area_nosemaphore;

		/* faulthandler_disabled() in user mode is really bad,
		   as is current->mm == शून्य. */
		pr_emerg("Page fault in user mode with faulthandler_disabled(), mm = %p\n",
			 mm);
		pr_emerg("r15 = %lx  MSR = %lx\n",
		       regs->r15, regs->msr);
		die("Weird page fault", regs, संक_अंश);
	पूर्ण

	अगर (user_mode(regs))
		flags |= FAULT_FLAG_USER;

	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, address);

	/* When running in the kernel we expect faults to occur only to
	 * addresses in user space.  All other faults represent errors in the
	 * kernel and should generate an OOPS.  Unक्रमtunately, in the हाल of an
	 * erroneous fault occurring in a code path which alपढ़ोy holds mmap_lock
	 * we will deadlock attempting to validate the fault against the
	 * address space.  Luckily the kernel only validly references user
	 * space from well defined areas of code, which are listed in the
	 * exceptions table.
	 *
	 * As the vast majority of faults will be valid we will only perक्रमm
	 * the source reference check when there is a possibility of a deadlock.
	 * Attempt to lock the address space, अगर we cannot we then validate the
	 * source.  If this is invalid we can skip the address space check,
	 * thus aव्योमing the deadlock.
	 */
	अगर (unlikely(!mmap_पढ़ो_trylock(mm))) अणु
		अगर (kernel_mode(regs) && !search_exception_tables(regs->pc))
			जाओ bad_area_nosemaphore;

retry:
		mmap_पढ़ो_lock(mm);
	पूर्ण

	vma = find_vma(mm, address);
	अगर (unlikely(!vma))
		जाओ bad_area;

	अगर (vma->vm_start <= address)
		जाओ good_area;

	अगर (unlikely(!(vma->vm_flags & VM_GROWSDOWN)))
		जाओ bad_area;

	अगर (unlikely(!is_ग_लिखो))
		जाओ bad_area;

	/*
	 * N.B. The ABI allows programs to access up to
	 * a few hundred bytes below the stack poपूर्णांकer (TBD).
	 * The kernel संकेत delivery code ग_लिखोs up to about 1.5kB
	 * below the stack poपूर्णांकer (r1) beक्रमe decrementing it.
	 * The exec code can ग_लिखो slightly over 640kB to the stack
	 * beक्रमe setting the user r1.  Thus we allow the stack to
	 * expand to 1MB without further checks.
	 */
	अगर (unlikely(address + 0x100000 < vma->vm_end)) अणु

		/* get user regs even अगर this fault is in kernel mode */
		काष्ठा pt_regs *uregs = current->thपढ़ो.regs;
		अगर (uregs == शून्य)
			जाओ bad_area;

		/*
		 * A user-mode access to an address a दीर्घ way below
		 * the stack poपूर्णांकer is only valid अगर the inकाष्ठाion
		 * is one which would update the stack poपूर्णांकer to the
		 * address accessed अगर the inकाष्ठाion completed,
		 * i.e. either stwu rs,n(r1) or stwux rs,r1,rb
		 * (or the byte, halfword, भग्न or द्विगुन क्रमms).
		 *
		 * If we करोn't check this then any ग_लिखो to the area
		 * between the last mapped region and the stack will
		 * expand the stack rather than segfaulting.
		 */
		अगर (address + 2048 < uregs->r1
			&& (kernel_mode(regs) || !store_updates_sp(regs)))
				जाओ bad_area;
	पूर्ण
	अगर (expand_stack(vma, address))
		जाओ bad_area;

good_area:
	code = SEGV_ACCERR;

	/* a ग_लिखो */
	अगर (unlikely(is_ग_लिखो)) अणु
		अगर (unlikely(!(vma->vm_flags & VM_WRITE)))
			जाओ bad_area;
		flags |= FAULT_FLAG_WRITE;
	/* a पढ़ो */
	पूर्ण अन्यथा अणु
		/* protection fault */
		अगर (unlikely(error_code & 0x08000000))
			जाओ bad_area;
		अगर (unlikely(!(vma->vm_flags & (VM_READ | VM_EXEC))))
			जाओ bad_area;
	पूर्ण

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

			/*
			 * No need to mmap_पढ़ो_unlock(mm) as we would
			 * have alपढ़ोy released it in __lock_page_or_retry
			 * in mm/filemap.c.
			 */

			जाओ retry;
		पूर्ण
	पूर्ण

	mmap_पढ़ो_unlock(mm);

	/*
	 * keep track of tlb+htab misses that are good addrs but
	 * just need pte's created via handle_mm_fault()
	 * -- Cort
	 */
	pte_misses++;
	वापस;

bad_area:
	mmap_पढ़ो_unlock(mm);

bad_area_nosemaphore:
	pte_errors++;

	/* User mode accesses cause a संक_अंश */
	अगर (user_mode(regs)) अणु
		_exception(संक_अंश, regs, code, address);
		वापस;
	पूर्ण

	bad_page_fault(regs, address, संक_अंश);
	वापस;

/*
 * We ran out of memory, or some other thing happened to us that made
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
	अगर (user_mode(regs)) अणु
		क्रमce_sig_fault(SIGBUS, BUS_ADRERR, (व्योम __user *)address);
		वापस;
	पूर्ण
	bad_page_fault(regs, address, SIGBUS);
पूर्ण
