<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  PowerPC version
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Derived from "arch/i386/mm/fault.c"
 *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 *
 *  Modअगरied by Cort Dougan and Paul Mackerras.
 *
 *  Modअगरied क्रम PPC64 by Dave Engebretsen (engebret@ibm.com)
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/extable.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kfence.h>
#समावेश <linux/pkeys.h>

#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/पूर्णांकerrupt.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/siginfo.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/kup.h>
#समावेश <यंत्र/inst.h>


/*
 * करो_page_fault error handling helpers
 */

अटल पूर्णांक
__bad_area_nosemaphore(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address, पूर्णांक si_code)
अणु
	/*
	 * If we are in kernel mode, bail out with a SEGV, this will
	 * be caught by the assembly which will restore the non-अस्थिर
	 * रेजिस्टरs beक्रमe calling bad_page_fault()
	 */
	अगर (!user_mode(regs))
		वापस संक_अंश;

	_exception(संक_अंश, regs, si_code, address);

	वापस 0;
पूर्ण

अटल noअंतरभूत पूर्णांक bad_area_nosemaphore(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address)
अणु
	वापस __bad_area_nosemaphore(regs, address, SEGV_MAPERR);
पूर्ण

अटल पूर्णांक __bad_area(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address, पूर्णांक si_code)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;

	/*
	 * Something tried to access memory that isn't in our memory map..
	 * Fix it, but check अगर it's kernel or user first..
	 */
	mmap_पढ़ो_unlock(mm);

	वापस __bad_area_nosemaphore(regs, address, si_code);
पूर्ण

अटल noअंतरभूत पूर्णांक bad_area(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address)
अणु
	वापस __bad_area(regs, address, SEGV_MAPERR);
पूर्ण

अटल noअंतरभूत पूर्णांक bad_access_pkey(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address,
				    काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	पूर्णांक pkey;

	/*
	 * We करोn't try to fetch the pkey from page table because पढ़ोing
	 * page table without locking करोesn't guarantee stable pte value.
	 * Hence the pkey value that we वापस to userspace can be dअगरferent
	 * from the pkey that actually caused access error.
	 *
	 * It करोes *not* guarantee that the VMA we find here
	 * was the one that we faulted on.
	 *
	 * 1. T1   : mprotect_key(foo, PAGE_SIZE, pkey=4);
	 * 2. T1   : set AMR to deny access to pkey=4, touches, page
	 * 3. T1   : faults...
	 * 4.    T2: mprotect_key(foo, PAGE_SIZE, pkey=5);
	 * 5. T1   : enters fault handler, takes mmap_lock, etc...
	 * 6. T1   : reaches here, sees vma_pkey(vma)=5, when we really
	 *	     faulted on a pte with its pkey=4.
	 */
	pkey = vma_pkey(vma);

	mmap_पढ़ो_unlock(mm);

	/*
	 * If we are in kernel mode, bail out with a SEGV, this will
	 * be caught by the assembly which will restore the non-अस्थिर
	 * रेजिस्टरs beक्रमe calling bad_page_fault()
	 */
	अगर (!user_mode(regs))
		वापस संक_अंश;

	_exception_pkey(regs, address, pkey);

	वापस 0;
पूर्ण

अटल noअंतरभूत पूर्णांक bad_access(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address)
अणु
	वापस __bad_area(regs, address, SEGV_ACCERR);
पूर्ण

अटल पूर्णांक करो_sigbus(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address,
		     vm_fault_t fault)
अणु
	अगर (!user_mode(regs))
		वापस SIGBUS;

	current->thपढ़ो.trap_nr = BUS_ADRERR;
#अगर_घोषित CONFIG_MEMORY_FAILURE
	अगर (fault & (VM_FAULT_HWPOISON|VM_FAULT_HWPOISON_LARGE)) अणु
		अचिन्हित पूर्णांक lsb = 0; /* shutup gcc */

		pr_err("MCE: Killing %s:%d due to hardware memory corruption fault at %lx\n",
			current->comm, current->pid, address);

		अगर (fault & VM_FAULT_HWPOISON_LARGE)
			lsb = hstate_index_to_shअगरt(VM_FAULT_GET_HINDEX(fault));
		अगर (fault & VM_FAULT_HWPOISON)
			lsb = PAGE_SHIFT;

		क्रमce_sig_mceerr(BUS_MCEERR_AR, (व्योम __user *)address, lsb);
		वापस 0;
	पूर्ण

#पूर्ण_अगर
	क्रमce_sig_fault(SIGBUS, BUS_ADRERR, (व्योम __user *)address);
	वापस 0;
पूर्ण

अटल पूर्णांक mm_fault_error(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr,
				vm_fault_t fault)
अणु
	/*
	 * Kernel page fault पूर्णांकerrupted by SIGKILL. We have no reason to
	 * जारी processing.
	 */
	अगर (fatal_संकेत_pending(current) && !user_mode(regs))
		वापस SIGKILL;

	/* Out of memory */
	अगर (fault & VM_FAULT_OOM) अणु
		/*
		 * We ran out of memory, or some other thing happened to us that
		 * made us unable to handle the page fault gracefully.
		 */
		अगर (!user_mode(regs))
			वापस संक_अंश;
		pagefault_out_of_memory();
	पूर्ण अन्यथा अणु
		अगर (fault & (VM_FAULT_SIGBUS|VM_FAULT_HWPOISON|
			     VM_FAULT_HWPOISON_LARGE))
			वापस करो_sigbus(regs, addr, fault);
		अन्यथा अगर (fault & VM_FAULT_संक_अंश)
			वापस bad_area_nosemaphore(regs, addr);
		अन्यथा
			BUG();
	पूर्ण
	वापस 0;
पूर्ण

/* Is this a bad kernel fault ? */
अटल bool bad_kernel_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
			     अचिन्हित दीर्घ address, bool is_ग_लिखो)
अणु
	पूर्णांक is_exec = TRAP(regs) == INTERRUPT_INST_STORAGE;

	/* NX faults set DSISR_PROTFAULT on the 8xx, DSISR_NOEXEC_OR_G on others */
	अगर (is_exec && (error_code & (DSISR_NOEXEC_OR_G | DSISR_KEYFAULT |
				      DSISR_PROTFAULT))) अणु
		pr_crit_ratelimited("kernel tried to execute %s page (%lx) - exploit attempt? (uid: %d)\n",
				    address >= TASK_SIZE ? "exec-protected" : "user",
				    address,
				    from_kuid(&init_user_ns, current_uid()));

		// Kernel exec fault is always bad
		वापस true;
	पूर्ण

	// Kernel fault on kernel address is bad
	अगर (address >= TASK_SIZE)
		वापस true;

	// Read/ग_लिखो fault blocked by KUAP is bad, it can never succeed.
	अगर (bad_kuap_fault(regs, address, is_ग_लिखो)) अणु
		pr_crit_ratelimited("Kernel attempted to %s user page (%lx) - exploit attempt? (uid: %d)\n",
				    is_ग_लिखो ? "write" : "read", address,
				    from_kuid(&init_user_ns, current_uid()));

		// Fault on user outside of certain regions (eg. copy_tofrom_user()) is bad
		अगर (!search_exception_tables(regs->nip))
			वापस true;

		// Read/ग_लिखो fault in a valid region (the exception table search passed
		// above), but blocked by KUAP is bad, it can never succeed.
		वापस WARN(true, "Bug: %s fault blocked by KUAP!", is_ग_लिखो ? "Write" : "Read");
	पूर्ण

	// What's left? Kernel fault on user and allowed by KUAP in the faulting context.
	वापस false;
पूर्ण

अटल bool access_pkey_error(bool is_ग_लिखो, bool is_exec, bool is_pkey,
			      काष्ठा vm_area_काष्ठा *vma)
अणु
	/*
	 * Make sure to check the VMA so that we करो not perक्रमm
	 * faults just to hit a pkey fault as soon as we fill in a
	 * page. Only called क्रम current mm, hence क्रमeign == 0
	 */
	अगर (!arch_vma_access_permitted(vma, is_ग_लिखो, is_exec, 0))
		वापस true;

	वापस false;
पूर्ण

अटल bool access_error(bool is_ग_लिखो, bool is_exec, काष्ठा vm_area_काष्ठा *vma)
अणु
	/*
	 * Allow execution from पढ़ोable areas अगर the MMU करोes not
	 * provide separate controls over पढ़ोing and executing.
	 *
	 * Note: That code used to not be enabled क्रम 4xx/BookE.
	 * It is now as I/D cache coherency क्रम these is करोne at
	 * set_pte_at() समय and I see no reason why the test
	 * below wouldn't be valid on those processors. This -may-
	 * अवरोध programs compiled with a really old ABI though.
	 */
	अगर (is_exec) अणु
		वापस !(vma->vm_flags & VM_EXEC) &&
			(cpu_has_feature(CPU_FTR_NOEXECUTE) ||
			 !(vma->vm_flags & (VM_READ | VM_WRITE)));
	पूर्ण

	अगर (is_ग_लिखो) अणु
		अगर (unlikely(!(vma->vm_flags & VM_WRITE)))
			वापस true;
		वापस false;
	पूर्ण

	अगर (unlikely(!vma_is_accessible(vma)))
		वापस true;
	/*
	 * We should ideally करो the vma pkey access check here. But in the
	 * fault path, handle_mm_fault() also करोes the same check. To aव्योम
	 * these multiple checks, we skip it here and handle access error due
	 * to pkeys later.
	 */
	वापस false;
पूर्ण

#अगर_घोषित CONFIG_PPC_SMLPAR
अटल अंतरभूत व्योम cmo_account_page_fault(व्योम)
अणु
	अगर (firmware_has_feature(FW_FEATURE_CMO)) अणु
		u32 page_ins;

		preempt_disable();
		page_ins = be32_to_cpu(get_lppaca()->page_ins);
		page_ins += 1 << PAGE_FACTOR;
		get_lppaca()->page_ins = cpu_to_be32(page_ins);
		preempt_enable();
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cmo_account_page_fault(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_SMLPAR */

अटल व्योम sanity_check_fault(bool is_ग_लिखो, bool is_user,
			       अचिन्हित दीर्घ error_code, अचिन्हित दीर्घ address)
अणु
	/*
	 * Userspace trying to access kernel address, we get PROTFAULT क्रम that.
	 */
	अगर (is_user && address >= TASK_SIZE) अणु
		अगर ((दीर्घ)address == -1)
			वापस;

		pr_crit_ratelimited("%s[%d]: User access of kernel address (%lx) - exploit attempt? (uid: %d)\n",
				   current->comm, current->pid, address,
				   from_kuid(&init_user_ns, current_uid()));
		वापस;
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_PPC_BOOK3S))
		वापस;

	/*
	 * For hash translation mode, we should never get a
	 * PROTFAULT. Any update to pte to reduce access will result in us
	 * removing the hash page table entry, thus resulting in a DSISR_NOHPTE
	 * fault instead of DSISR_PROTFAULT.
	 *
	 * A pte update to relax the access will not result in a hash page table
	 * entry invalidate and hence can result in DSISR_PROTFAULT.
	 * ptep_set_access_flags() करोesn't करो a hpte flush. This is why we have
	 * the special !is_ग_लिखो in the below conditional.
	 *
	 * For platक्रमms that करोesn't supports coherent icache and करो support
	 * per page noexec bit, we करो setup things such that we करो the
	 * sync between D/I cache via fault. But that is handled via low level
	 * hash fault code (hash_page_करो_lazy_icache()) and we should not reach
	 * here in such हाल.
	 *
	 * For wrong access that can result in PROTFAULT, the above vma->vm_flags
	 * check should handle those and hence we should fall to the bad_area
	 * handling correctly.
	 *
	 * For embedded with per page exec support that करोesn't support coherent
	 * icache we करो get PROTFAULT and we handle that D/I cache sync in
	 * set_pte_at जबतक taking the noexec/prot fault. Hence this is WARN_ON
	 * is conditional क्रम server MMU.
	 *
	 * For radix, we can get prot fault क्रम स्वतःnuma हाल, because radix
	 * page table will have them marked noaccess क्रम user.
	 */
	अगर (radix_enabled() || is_ग_लिखो)
		वापस;

	WARN_ON_ONCE(error_code & DSISR_PROTFAULT);
पूर्ण

/*
 * Define the correct "is_write" bit in error_code based
 * on the processor family
 */
#अगर (defined(CONFIG_4xx) || defined(CONFIG_BOOKE))
#घोषणा page_fault_is_ग_लिखो(__err)	((__err) & ESR_DST)
#अन्यथा
#घोषणा page_fault_is_ग_लिखो(__err)	((__err) & DSISR_ISSTORE)
#पूर्ण_अगर

#अगर defined(CONFIG_4xx) || defined(CONFIG_BOOKE)
#घोषणा page_fault_is_bad(__err)	(0)
#या_अगर defined(CONFIG_PPC_8xx)
#घोषणा page_fault_is_bad(__err)	((__err) & DSISR_NOEXEC_OR_G)
#या_अगर defined(CONFIG_PPC64)
#घोषणा page_fault_is_bad(__err)	((__err) & DSISR_BAD_FAULT_64S)
#अन्यथा
#घोषणा page_fault_is_bad(__err)	((__err) & DSISR_BAD_FAULT_32S)
#पूर्ण_अगर

/*
 * For 600- and 800-family processors, the error_code parameter is DSISR
 * क्रम a data fault, SRR1 क्रम an inकाष्ठाion fault.
 * For 400-family processors the error_code parameter is ESR क्रम a data fault,
 * 0 क्रम an inकाष्ठाion fault.
 * For 64-bit processors, the error_code parameter is DSISR क्रम a data access
 * fault, SRR1 & 0x08000000 क्रम an inकाष्ठाion access fault.
 *
 * The वापस value is 0 अगर the fault was handled, or the संकेत
 * number अगर this is a kernel fault that can't be handled here.
 */
अटल पूर्णांक ___करो_page_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address,
			   अचिन्हित दीर्घ error_code)
अणु
	काष्ठा vm_area_काष्ठा * vma;
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;
	पूर्णांक is_exec = TRAP(regs) == INTERRUPT_INST_STORAGE;
	पूर्णांक is_user = user_mode(regs);
	पूर्णांक is_ग_लिखो = page_fault_is_ग_लिखो(error_code);
	vm_fault_t fault, major = 0;
	bool kprobe_fault = kprobe_page_fault(regs, 11);

	अगर (unlikely(debugger_fault_handler(regs) || kprobe_fault))
		वापस 0;

	अगर (unlikely(page_fault_is_bad(error_code))) अणु
		अगर (is_user) अणु
			_exception(SIGBUS, regs, BUS_OBJERR, address);
			वापस 0;
		पूर्ण
		वापस SIGBUS;
	पूर्ण

	/* Additional sanity check(s) */
	sanity_check_fault(is_ग_लिखो, is_user, error_code, address);

	/*
	 * The kernel should never take an execute fault nor should it
	 * take a page fault to a kernel address or a page fault to a user
	 * address outside of dedicated places
	 */
	अगर (unlikely(!is_user && bad_kernel_fault(regs, error_code, address, is_ग_लिखो))) अणु
		अगर (kfence_handle_page_fault(address, is_ग_लिखो, regs))
			वापस 0;

		वापस संक_अंश;
	पूर्ण

	/*
	 * If we're in an पूर्णांकerrupt, have no user context or are running
	 * in a region with pagefaults disabled then we must not take the fault
	 */
	अगर (unlikely(faulthandler_disabled() || !mm)) अणु
		अगर (is_user)
			prपूर्णांकk_ratelimited(KERN_ERR "Page fault in user mode"
					   " with faulthandler_disabled()=%d"
					   " mm=%p\n",
					   faulthandler_disabled(), mm);
		वापस bad_area_nosemaphore(regs, address);
	पूर्ण

	पूर्णांकerrupt_cond_local_irq_enable(regs);

	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, address);

	/*
	 * We want to करो this outside mmap_lock, because पढ़ोing code around nip
	 * can result in fault, which will cause a deadlock when called with
	 * mmap_lock held
	 */
	अगर (is_user)
		flags |= FAULT_FLAG_USER;
	अगर (is_ग_लिखो)
		flags |= FAULT_FLAG_WRITE;
	अगर (is_exec)
		flags |= FAULT_FLAG_INSTRUCTION;

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
		अगर (!is_user && !search_exception_tables(regs->nip))
			वापस bad_area_nosemaphore(regs, address);

retry:
		mmap_पढ़ो_lock(mm);
	पूर्ण अन्यथा अणु
		/*
		 * The above करोwn_पढ़ो_trylock() might have succeeded in
		 * which हाल we'll have missed the might_sleep() from
		 * करोwn_पढ़ो():
		 */
		might_sleep();
	पूर्ण

	vma = find_vma(mm, address);
	अगर (unlikely(!vma))
		वापस bad_area(regs, address);

	अगर (unlikely(vma->vm_start > address)) अणु
		अगर (unlikely(!(vma->vm_flags & VM_GROWSDOWN)))
			वापस bad_area(regs, address);

		अगर (unlikely(expand_stack(vma, address)))
			वापस bad_area(regs, address);
	पूर्ण

	अगर (unlikely(access_pkey_error(is_ग_लिखो, is_exec,
				       (error_code & DSISR_KEYFAULT), vma)))
		वापस bad_access_pkey(regs, address, vma);

	अगर (unlikely(access_error(is_ग_लिखो, is_exec, vma)))
		वापस bad_access(regs, address);

	/*
	 * If क्रम any reason at all we couldn't handle the fault,
	 * make sure we निकास gracefully rather than endlessly reकरो
	 * the fault.
	 */
	fault = handle_mm_fault(vma, address, flags, regs);

	major |= fault & VM_FAULT_MAJOR;

	अगर (fault_संकेत_pending(fault, regs))
		वापस user_mode(regs) ? 0 : SIGBUS;

	/*
	 * Handle the retry right now, the mmap_lock has been released in that
	 * हाल.
	 */
	अगर (unlikely(fault & VM_FAULT_RETRY)) अणु
		अगर (flags & FAULT_FLAG_ALLOW_RETRY) अणु
			flags |= FAULT_FLAG_TRIED;
			जाओ retry;
		पूर्ण
	पूर्ण

	mmap_पढ़ो_unlock(current->mm);

	अगर (unlikely(fault & VM_FAULT_ERROR))
		वापस mm_fault_error(regs, address, fault);

	/*
	 * Major/minor page fault accounting.
	 */
	अगर (major)
		cmo_account_page_fault();

	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(___करो_page_fault);

अटल __always_अंतरभूत व्योम __करो_page_fault(काष्ठा pt_regs *regs)
अणु
	दीर्घ err;

	err = ___करो_page_fault(regs, regs->dar, regs->dsisr);
	अगर (unlikely(err))
		bad_page_fault(regs, err);
पूर्ण

DEFINE_INTERRUPT_HANDLER(करो_page_fault)
अणु
	__करो_page_fault(regs);
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64
/* Same as करो_page_fault but पूर्णांकerrupt entry has alपढ़ोy run in करो_hash_fault */
व्योम hash__करो_page_fault(काष्ठा pt_regs *regs)
अणु
	__करो_page_fault(regs);
पूर्ण
NOKPROBE_SYMBOL(hash__करो_page_fault);
#पूर्ण_अगर

/*
 * bad_page_fault is called when we have a bad access from the kernel.
 * It is called from the DSI and ISI handlers in head.S and from some
 * of the procedures in traps.c.
 */
अटल व्योम __bad_page_fault(काष्ठा pt_regs *regs, पूर्णांक sig)
अणु
	पूर्णांक is_ग_लिखो = page_fault_is_ग_लिखो(regs->dsisr);

	/* kernel has accessed a bad area */

	चयन (TRAP(regs)) अणु
	हाल INTERRUPT_DATA_STORAGE:
	हाल INTERRUPT_DATA_SEGMENT:
	हाल INTERRUPT_H_DATA_STORAGE:
		pr_alert("BUG: %s on %s at 0x%08lx\n",
			 regs->dar < PAGE_SIZE ? "Kernel NULL pointer dereference" :
			 "Unable to handle kernel data access",
			 is_ग_लिखो ? "write" : "read", regs->dar);
		अवरोध;
	हाल INTERRUPT_INST_STORAGE:
	हाल INTERRUPT_INST_SEGMENT:
		pr_alert("BUG: Unable to handle kernel instruction fetch%s",
			 regs->nip < PAGE_SIZE ? " (NULL pointer?)\n" : "\n");
		अवरोध;
	हाल INTERRUPT_ALIGNMENT:
		pr_alert("BUG: Unable to handle kernel unaligned access at 0x%08lx\n",
			 regs->dar);
		अवरोध;
	शेष:
		pr_alert("BUG: Unable to handle unknown paging fault at 0x%08lx\n",
			 regs->dar);
		अवरोध;
	पूर्ण
	prपूर्णांकk(KERN_ALERT "Faulting instruction address: 0x%08lx\n",
		regs->nip);

	अगर (task_stack_end_corrupted(current))
		prपूर्णांकk(KERN_ALERT "Thread overran stack, or stack corrupted\n");

	die("Kernel access of bad area", regs, sig);
पूर्ण

व्योम bad_page_fault(काष्ठा pt_regs *regs, पूर्णांक sig)
अणु
	स्थिर काष्ठा exception_table_entry *entry;

	/* Are we prepared to handle this fault?  */
	entry = search_exception_tables(inकाष्ठाion_poपूर्णांकer(regs));
	अगर (entry)
		inकाष्ठाion_poपूर्णांकer_set(regs, extable_fixup(entry));
	अन्यथा
		__bad_page_fault(regs, sig);
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64
DEFINE_INTERRUPT_HANDLER(करो_bad_page_fault_segv)
अणु
	bad_page_fault(regs, संक_अंश);
पूर्ण
#पूर्ण_अगर
