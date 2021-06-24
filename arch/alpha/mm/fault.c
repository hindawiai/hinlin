<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/alpha/mm/fault.c
 *
 *  Copyright (C) 1995  Linus Torvalds
 */

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/पन.स>

#घोषणा __EXTERN_INLINE अंतरभूत
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlbflush.h>
#अघोषित  __EXTERN_INLINE

#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/extable.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/perf_event.h>

बाह्य व्योम die_अगर_kernel(अक्षर *,काष्ठा pt_regs *,दीर्घ, अचिन्हित दीर्घ *);


/*
 * Force a new ASN क्रम a task.
 */

#अगर_अघोषित CONFIG_SMP
अचिन्हित दीर्घ last_asn = ASN_FIRST_VERSION;
#पूर्ण_अगर

व्योम
__load_new_mm_context(काष्ठा mm_काष्ठा *next_mm)
अणु
	अचिन्हित दीर्घ mmc;
	काष्ठा pcb_काष्ठा *pcb;

	mmc = __get_new_mm_context(next_mm, smp_processor_id());
	next_mm->context[smp_processor_id()] = mmc;

	pcb = &current_thपढ़ो_info()->pcb;
	pcb->asn = mmc & HARDWARE_ASN_MASK;
	pcb->ptbr = ((अचिन्हित दीर्घ) next_mm->pgd - IDENT_ADDR) >> PAGE_SHIFT;

	__reload_thपढ़ो(pcb);
पूर्ण


/*
 * This routine handles page faults.  It determines the address,
 * and the problem, and then passes it off to handle_mm_fault().
 *
 * mmcsr:
 *	0 = translation not valid
 *	1 = access violation
 *	2 = fault-on-पढ़ो
 *	3 = fault-on-execute
 *	4 = fault-on-ग_लिखो
 *
 * cause:
 *	-1 = inकाष्ठाion fetch
 *	0 = load
 *	1 = store
 *
 * Registers $9 through $15 are saved in a block just prior to `regs' and
 * are saved and restored around the call to allow exception code to
 * modअगरy them.
 */

/* Macro क्रम exception fixup code to access पूर्णांकeger रेजिस्टरs.  */
#घोषणा dpf_reg(r)							\
	(((अचिन्हित दीर्घ *)regs)[(r) <= 8 ? (r) : (r) <= 15 ? (r)-16 :	\
				 (r) <= 18 ? (r)+10 : (r)-10])

यंत्रlinkage व्योम
करो_page_fault(अचिन्हित दीर्घ address, अचिन्हित दीर्घ mmcsr,
	      दीर्घ cause, काष्ठा pt_regs *regs)
अणु
	काष्ठा vm_area_काष्ठा * vma;
	काष्ठा mm_काष्ठा *mm = current->mm;
	स्थिर काष्ठा exception_table_entry *fixup;
	पूर्णांक si_code = SEGV_MAPERR;
	vm_fault_t fault;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;

	/* As of EV6, a load पूर्णांकo $31/$f31 is a prefetch, and never faults
	   (or is suppressed by the PALcode).  Support that क्रम older CPUs
	   by ignoring such an inकाष्ठाion.  */
	अगर (cause == 0) अणु
		अचिन्हित पूर्णांक insn;
		__get_user(insn, (अचिन्हित पूर्णांक __user *)regs->pc);
		अगर ((insn >> 21 & 0x1f) == 0x1f &&
		    /* ldq ldl ldt lds ldg ldf ldwu ldbu */
		    (1ul << (insn >> 26) & 0x30f00001400ul)) अणु
			regs->pc += 4;
			वापस;
		पूर्ण
	पूर्ण

	/* If we're in an पूर्णांकerrupt context, or have no user context,
	   we must not take the fault.  */
	अगर (!mm || faulthandler_disabled())
		जाओ no_context;

#अगर_घोषित CONFIG_ALPHA_LARGE_VMALLOC
	अगर (address >= TASK_SIZE)
		जाओ vदो_स्मृति_fault;
#पूर्ण_अगर
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

	/* Ok, we have a good vm_area क्रम this memory access, so
	   we can handle it.  */
 good_area:
	si_code = SEGV_ACCERR;
	अगर (cause < 0) अणु
		अगर (!(vma->vm_flags & VM_EXEC))
			जाओ bad_area;
	पूर्ण अन्यथा अगर (!cause) अणु
		/* Allow पढ़ोs even क्रम ग_लिखो-only mappings */
		अगर (!(vma->vm_flags & (VM_READ | VM_WRITE)))
			जाओ bad_area;
	पूर्ण अन्यथा अणु
		अगर (!(vma->vm_flags & VM_WRITE))
			जाओ bad_area;
		flags |= FAULT_FLAG_WRITE;
	पूर्ण

	/* If क्रम any reason at all we couldn't handle the fault,
	   make sure we निकास gracefully rather than endlessly reकरो
	   the fault.  */
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

	/* Something tried to access memory that isn't in our memory map.
	   Fix it, but check अगर it's kernel or user first.  */
 bad_area:
	mmap_पढ़ो_unlock(mm);

	अगर (user_mode(regs))
		जाओ करो_sigsegv;

 no_context:
	/* Are we prepared to handle this fault as an exception?  */
	अगर ((fixup = search_exception_tables(regs->pc)) != 0) अणु
		अचिन्हित दीर्घ newpc;
		newpc = fixup_exception(dpf_reg, fixup, regs->pc);
		regs->pc = newpc;
		वापस;
	पूर्ण

	/* Oops. The kernel tried to access some bad page. We'll have to
	   terminate things with extreme prejudice.  */
	prपूर्णांकk(KERN_ALERT "Unable to handle kernel paging request at "
	       "virtual address %016lx\n", address);
	die_अगर_kernel("Oops", regs, cause, (अचिन्हित दीर्घ*)regs - 16);
	करो_निकास(SIGKILL);

	/* We ran out of memory, or some other thing happened to us that
	   made us unable to handle the page fault gracefully.  */
 out_of_memory:
	mmap_पढ़ो_unlock(mm);
	अगर (!user_mode(regs))
		जाओ no_context;
	pagefault_out_of_memory();
	वापस;

 करो_sigbus:
	mmap_पढ़ो_unlock(mm);
	/* Send a sigbus, regardless of whether we were in kernel
	   or user mode.  */
	क्रमce_sig_fault(SIGBUS, BUS_ADRERR, (व्योम __user *) address, 0);
	अगर (!user_mode(regs))
		जाओ no_context;
	वापस;

 करो_sigsegv:
	क्रमce_sig_fault(संक_अंश, si_code, (व्योम __user *) address, 0);
	वापस;

#अगर_घोषित CONFIG_ALPHA_LARGE_VMALLOC
 vदो_स्मृति_fault:
	अगर (user_mode(regs))
		जाओ करो_sigsegv;
	अन्यथा अणु
		/* Synchronize this task's top level page-table
		   with the "reference" page table from init.  */
		दीर्घ index = pgd_index(address);
		pgd_t *pgd, *pgd_k;

		pgd = current->active_mm->pgd + index;
		pgd_k = swapper_pg_dir + index;
		अगर (!pgd_present(*pgd) && pgd_present(*pgd_k)) अणु
			pgd_val(*pgd) = pgd_val(*pgd_k);
			वापस;
		पूर्ण
		जाओ no_context;
	पूर्ण
#पूर्ण_अगर
पूर्ण
