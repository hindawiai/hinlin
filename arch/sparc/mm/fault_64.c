<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sparc64/mm/fault.c: Page fault handlers क्रम the 64-bit Sparc.
 *
 * Copyright (C) 1996, 2008 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1997, 1999 Jakub Jelinek (jj@ultra.linux.cz)
 */

#समावेश <यंत्र/head.h>

#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/mm.h>
#समावेश <linux/extable.h>
#समावेश <linux/init.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/percpu.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/asi.h>
#समावेश <यंत्र/lsu.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/setup.h>

पूर्णांक show_unhandled_संकेतs = 1;

अटल व्योम __kprobes unhandled_fault(अचिन्हित दीर्घ address,
				      काष्ठा task_काष्ठा *tsk,
				      काष्ठा pt_regs *regs)
अणु
	अगर ((अचिन्हित दीर्घ) address < PAGE_SIZE) अणु
		prपूर्णांकk(KERN_ALERT "Unable to handle kernel NULL "
		       "pointer dereference\n");
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ALERT "Unable to handle kernel paging request "
		       "at virtual address %016lx\n", (अचिन्हित दीर्घ)address);
	पूर्ण
	prपूर्णांकk(KERN_ALERT "tsk->{mm,active_mm}->context = %016lx\n",
	       (tsk->mm ?
		CTX_HWBITS(tsk->mm->context) :
		CTX_HWBITS(tsk->active_mm->context)));
	prपूर्णांकk(KERN_ALERT "tsk->{mm,active_mm}->pgd = %016lx\n",
	       (tsk->mm ? (अचिन्हित दीर्घ) tsk->mm->pgd :
		          (अचिन्हित दीर्घ) tsk->active_mm->pgd));
	die_अगर_kernel("Oops", regs);
पूर्ण

अटल व्योम __kprobes bad_kernel_pc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ vaddr)
अणु
	prपूर्णांकk(KERN_CRIT "OOPS: Bogus kernel PC [%016lx] in fault handler\n",
	       regs->tpc);
	prपूर्णांकk(KERN_CRIT "OOPS: RPC [%016lx]\n", regs->u_regs[15]);
	prपूर्णांकk("OOPS: RPC <%pS>\n", (व्योम *) regs->u_regs[15]);
	prपूर्णांकk(KERN_CRIT "OOPS: Fault was to vaddr[%lx]\n", vaddr);
	dump_stack();
	unhandled_fault(regs->tpc, current, regs);
पूर्ण

/*
 * We now make sure that mmap_lock is held in all paths that call
 * this. Additionally, to prevent kswapd from ripping ptes from
 * under us, उठाओ पूर्णांकerrupts around the समय that we look at the
 * pte, kswapd will have to रुको to get his smp ipi response from
 * us. vmtruncate likewise. This saves us having to get pte lock.
 */
अटल अचिन्हित पूर्णांक get_user_insn(अचिन्हित दीर्घ tpc)
अणु
	pgd_t *pgdp = pgd_offset(current->mm, tpc);
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep, pte;
	अचिन्हित दीर्घ pa;
	u32 insn = 0;

	अगर (pgd_none(*pgdp) || unlikely(pgd_bad(*pgdp)))
		जाओ out;
	p4dp = p4d_offset(pgdp, tpc);
	अगर (p4d_none(*p4dp) || unlikely(p4d_bad(*p4dp)))
		जाओ out;
	pudp = pud_offset(p4dp, tpc);
	अगर (pud_none(*pudp) || unlikely(pud_bad(*pudp)))
		जाओ out;

	/* This disables preemption क्रम us as well. */
	local_irq_disable();

	pmdp = pmd_offset(pudp, tpc);
	अगर (pmd_none(*pmdp) || unlikely(pmd_bad(*pmdp)))
		जाओ out_irq_enable;

#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
	अगर (is_hugetlb_pmd(*pmdp)) अणु
		pa  = pmd_pfn(*pmdp) << PAGE_SHIFT;
		pa += tpc & ~HPAGE_MASK;

		/* Use phys bypass so we करोn't pollute dtlb/dcache. */
		__यंत्र__ __अस्थिर__("lduwa [%1] %2, %0"
				     : "=r" (insn)
				     : "r" (pa), "i" (ASI_PHYS_USE_EC));
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		ptep = pte_offset_map(pmdp, tpc);
		pte = *ptep;
		अगर (pte_present(pte)) अणु
			pa  = (pte_pfn(pte) << PAGE_SHIFT);
			pa += (tpc & ~PAGE_MASK);

			/* Use phys bypass so we करोn't pollute dtlb/dcache. */
			__यंत्र__ __अस्थिर__("lduwa [%1] %2, %0"
					     : "=r" (insn)
					     : "r" (pa), "i" (ASI_PHYS_USE_EC));
		पूर्ण
		pte_unmap(ptep);
	पूर्ण
out_irq_enable:
	local_irq_enable();
out:
	वापस insn;
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
	       (व्योम *)regs->tpc, (व्योम *)regs->u_regs[UREG_I7],
	       (व्योम *)regs->u_regs[UREG_FP], code);

	prपूर्णांक_vma_addr(KERN_CONT " in ", regs->tpc);

	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

अटल व्योम करो_fault_siginfo(पूर्णांक code, पूर्णांक sig, काष्ठा pt_regs *regs,
			     अचिन्हित दीर्घ fault_addr, अचिन्हित पूर्णांक insn,
			     पूर्णांक fault_code)
अणु
	अचिन्हित दीर्घ addr;

	अगर (fault_code & FAULT_CODE_ITLB) अणु
		addr = regs->tpc;
	पूर्ण अन्यथा अणु
		/* If we were able to probe the faulting inकाष्ठाion, use it
		 * to compute a precise fault address.  Otherwise use the fault
		 * समय provided address which may only have page granularity.
		 */
		अगर (insn)
			addr = compute_effective_address(regs, insn, 0);
		अन्यथा
			addr = fault_addr;
	पूर्ण

	अगर (unlikely(show_unhandled_संकेतs))
		show_संकेत_msg(regs, sig, code, addr, current);

	क्रमce_sig_fault(sig, code, (व्योम __user *) addr, 0);
पूर्ण

अटल अचिन्हित पूर्णांक get_fault_insn(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn)
अणु
	अगर (!insn) अणु
		अगर (!regs->tpc || (regs->tpc & 0x3))
			वापस 0;
		अगर (regs->tstate & TSTATE_PRIV) अणु
			insn = *(अचिन्हित पूर्णांक *) regs->tpc;
		पूर्ण अन्यथा अणु
			insn = get_user_insn(regs->tpc);
		पूर्ण
	पूर्ण
	वापस insn;
पूर्ण

अटल व्योम __kprobes करो_kernel_fault(काष्ठा pt_regs *regs, पूर्णांक si_code,
				      पूर्णांक fault_code, अचिन्हित पूर्णांक insn,
				      अचिन्हित दीर्घ address)
अणु
	अचिन्हित अक्षर asi = ASI_P;
 
	अगर ((!insn) && (regs->tstate & TSTATE_PRIV))
		जाओ cannot_handle;

	/* If user insn could be पढ़ो (thus insn is zero), that
	 * is fine.  We will just gun करोwn the process with a संकेत
	 * in that हाल.
	 */

	अगर (!(fault_code & (FAULT_CODE_WRITE|FAULT_CODE_ITLB)) &&
	    (insn & 0xc0800000) == 0xc0800000) अणु
		अगर (insn & 0x2000)
			asi = (regs->tstate >> 24);
		अन्यथा
			asi = (insn >> 5);
		अगर ((asi & 0xf2) == 0x82) अणु
			अगर (insn & 0x1000000) अणु
				handle_ldf_stq(insn, regs);
			पूर्ण अन्यथा अणु
				/* This was a non-faulting load. Just clear the
				 * destination रेजिस्टर(s) and जारी with the next
				 * inकाष्ठाion. -jj
				 */
				handle_ld_nf(insn, regs);
			पूर्ण
			वापस;
		पूर्ण
	पूर्ण
		
	/* Is this in ex_table? */
	अगर (regs->tstate & TSTATE_PRIV) अणु
		स्थिर काष्ठा exception_table_entry *entry;

		entry = search_exception_tables(regs->tpc);
		अगर (entry) अणु
			regs->tpc = entry->fixup;
			regs->tnpc = regs->tpc + 4;
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* The si_code was set to make clear whether
		 * this was a SEGV_MAPERR or SEGV_ACCERR fault.
		 */
		करो_fault_siginfo(si_code, संक_अंश, regs, address, insn, fault_code);
		वापस;
	पूर्ण

cannot_handle:
	unhandled_fault (address, current, regs);
पूर्ण

अटल व्योम noअंतरभूत __kprobes bogus_32bit_fault_tpc(काष्ठा pt_regs *regs)
अणु
	अटल पूर्णांक बार;

	अगर (बार++ < 10)
		prपूर्णांकk(KERN_ERR "FAULT[%s:%d]: 32-bit process reports "
		       "64-bit TPC [%lx]\n",
		       current->comm, current->pid,
		       regs->tpc);
	show_regs(regs);
पूर्ण

यंत्रlinkage व्योम __kprobes करो_sparc64_fault(काष्ठा pt_regs *regs)
अणु
	क्रमागत ctx_state prev_state = exception_enter();
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित पूर्णांक insn = 0;
	पूर्णांक si_code, fault_code;
	vm_fault_t fault;
	अचिन्हित दीर्घ address, mm_rss;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;

	fault_code = get_thपढ़ो_fault_code();

	अगर (kprobe_page_fault(regs, 0))
		जाओ निकास_exception;

	si_code = SEGV_MAPERR;
	address = current_thपढ़ो_info()->fault_address;

	अगर ((fault_code & FAULT_CODE_ITLB) &&
	    (fault_code & FAULT_CODE_DTLB))
		BUG();

	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		अगर (!(regs->tstate & TSTATE_PRIV)) अणु
			अगर (unlikely((regs->tpc >> 32) != 0)) अणु
				bogus_32bit_fault_tpc(regs);
				जाओ पूर्णांकr_or_no_mm;
			पूर्ण
		पूर्ण
		अगर (unlikely((address >> 32) != 0))
			जाओ पूर्णांकr_or_no_mm;
	पूर्ण

	अगर (regs->tstate & TSTATE_PRIV) अणु
		अचिन्हित दीर्घ tpc = regs->tpc;

		/* Sanity check the PC. */
		अगर ((tpc >= KERNBASE && tpc < (अचिन्हित दीर्घ) __init_end) ||
		    (tpc >= MODULES_VADDR && tpc < MODULES_END)) अणु
			/* Valid, no problems... */
		पूर्ण अन्यथा अणु
			bad_kernel_pc(regs, address);
			जाओ निकास_exception;
		पूर्ण
	पूर्ण अन्यथा
		flags |= FAULT_FLAG_USER;

	/*
	 * If we're in an पूर्णांकerrupt or have no user
	 * context, we must not take the fault..
	 */
	अगर (faulthandler_disabled() || !mm)
		जाओ पूर्णांकr_or_no_mm;

	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, address);

	अगर (!mmap_पढ़ो_trylock(mm)) अणु
		अगर ((regs->tstate & TSTATE_PRIV) &&
		    !search_exception_tables(regs->tpc)) अणु
			insn = get_fault_insn(regs, insn);
			जाओ handle_kernel_fault;
		पूर्ण

retry:
		mmap_पढ़ो_lock(mm);
	पूर्ण

	अगर (fault_code & FAULT_CODE_BAD_RA)
		जाओ करो_sigbus;

	vma = find_vma(mm, address);
	अगर (!vma)
		जाओ bad_area;

	/* Pure DTLB misses करो not tell us whether the fault causing
	 * load/store/atomic was a ग_लिखो or not, it only says that there
	 * was no match.  So in such a हाल we (carefully) पढ़ो the
	 * inकाष्ठाion to try and figure this out.  It's an optimization
	 * so it's ok if we can't करो this.
	 *
	 * Special hack, winकरोw spill/fill knows the exact fault type.
	 */
	अगर (((fault_code &
	      (FAULT_CODE_DTLB | FAULT_CODE_WRITE | FAULT_CODE_WINFIXUP)) == FAULT_CODE_DTLB) &&
	    (vma->vm_flags & VM_WRITE) != 0) अणु
		insn = get_fault_insn(regs, 0);
		अगर (!insn)
			जाओ जारी_fault;
		/* All loads, stores and atomics have bits 30 and 31 both set
		 * in the inकाष्ठाion.  Bit 21 is set in all stores, but we
		 * have to aव्योम prefetches which also have bit 21 set.
		 */
		अगर ((insn & 0xc0200000) == 0xc0200000 &&
		    (insn & 0x01780000) != 0x01680000) अणु
			/* Don't bother updating thपढ़ो काष्ठा value,
			 * because update_mmu_cache only cares which tlb
			 * the access came from.
			 */
			fault_code |= FAULT_CODE_WRITE;
		पूर्ण
	पूर्ण
जारी_fault:

	अगर (vma->vm_start <= address)
		जाओ good_area;
	अगर (!(vma->vm_flags & VM_GROWSDOWN))
		जाओ bad_area;
	अगर (!(fault_code & FAULT_CODE_WRITE)) अणु
		/* Non-faulting loads shouldn't expand stack. */
		insn = get_fault_insn(regs, insn);
		अगर ((insn & 0xc0800000) == 0xc0800000) अणु
			अचिन्हित अक्षर asi;

			अगर (insn & 0x2000)
				asi = (regs->tstate >> 24);
			अन्यथा
				asi = (insn >> 5);
			अगर ((asi & 0xf2) == 0x82)
				जाओ bad_area;
		पूर्ण
	पूर्ण
	अगर (expand_stack(vma, address))
		जाओ bad_area;
	/*
	 * Ok, we have a good vm_area क्रम this memory access, so
	 * we can handle it..
	 */
good_area:
	si_code = SEGV_ACCERR;

	/* If we took a ITLB miss on a non-executable page, catch
	 * that here.
	 */
	अगर ((fault_code & FAULT_CODE_ITLB) && !(vma->vm_flags & VM_EXEC)) अणु
		WARN(address != regs->tpc,
		     "address (%lx) != regs->tpc (%lx)\n", address, regs->tpc);
		WARN_ON(regs->tstate & TSTATE_PRIV);
		जाओ bad_area;
	पूर्ण

	अगर (fault_code & FAULT_CODE_WRITE) अणु
		अगर (!(vma->vm_flags & VM_WRITE))
			जाओ bad_area;

		/* Spitfire has an icache which करोes not snoop
		 * processor stores.  Later processors करो...
		 */
		अगर (tlb_type == spitfire &&
		    (vma->vm_flags & VM_EXEC) != 0 &&
		    vma->vm_file != शून्य)
			set_thपढ़ो_fault_code(fault_code |
					      FAULT_CODE_BLKCOMMIT);

		flags |= FAULT_FLAG_WRITE;
	पूर्ण अन्यथा अणु
		/* Allow पढ़ोs even क्रम ग_लिखो-only mappings */
		अगर (!(vma->vm_flags & (VM_READ | VM_EXEC)))
			जाओ bad_area;
	पूर्ण

	fault = handle_mm_fault(vma, address, flags, regs);

	अगर (fault_संकेत_pending(fault, regs))
		जाओ निकास_exception;

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

	mm_rss = get_mm_rss(mm);
#अगर defined(CONFIG_TRANSPARENT_HUGEPAGE)
	mm_rss -= (mm->context.thp_pte_count * (HPAGE_SIZE / PAGE_SIZE));
#पूर्ण_अगर
	अगर (unlikely(mm_rss >
		     mm->context.tsb_block[MM_TSB_BASE].tsb_rss_limit))
		tsb_grow(mm, MM_TSB_BASE, mm_rss);
#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
	mm_rss = mm->context.hugetlb_pte_count + mm->context.thp_pte_count;
	mm_rss *= REAL_HPAGE_PER_HPAGE;
	अगर (unlikely(mm_rss >
		     mm->context.tsb_block[MM_TSB_HUGE].tsb_rss_limit)) अणु
		अगर (mm->context.tsb_block[MM_TSB_HUGE].tsb)
			tsb_grow(mm, MM_TSB_HUGE, mm_rss);
		अन्यथा
			hugetlb_setup(regs);

	पूर्ण
#पूर्ण_अगर
निकास_exception:
	exception_निकास(prev_state);
	वापस;

	/*
	 * Something tried to access memory that isn't in our memory map..
	 * Fix it, but check अगर it's kernel or user first..
	 */
bad_area:
	insn = get_fault_insn(regs, insn);
	mmap_पढ़ो_unlock(mm);

handle_kernel_fault:
	करो_kernel_fault(regs, si_code, fault_code, insn, address);
	जाओ निकास_exception;

/*
 * We ran out of memory, or some other thing happened to us that made
 * us unable to handle the page fault gracefully.
 */
out_of_memory:
	insn = get_fault_insn(regs, insn);
	mmap_पढ़ो_unlock(mm);
	अगर (!(regs->tstate & TSTATE_PRIV)) अणु
		pagefault_out_of_memory();
		जाओ निकास_exception;
	पूर्ण
	जाओ handle_kernel_fault;

पूर्णांकr_or_no_mm:
	insn = get_fault_insn(regs, 0);
	जाओ handle_kernel_fault;

करो_sigbus:
	insn = get_fault_insn(regs, insn);
	mmap_पढ़ो_unlock(mm);

	/*
	 * Send a sigbus, regardless of whether we were in kernel
	 * or user mode.
	 */
	करो_fault_siginfo(BUS_ADRERR, SIGBUS, regs, address, insn, fault_code);

	/* Kernel mode? Handle exceptions or die */
	अगर (regs->tstate & TSTATE_PRIV)
		जाओ handle_kernel_fault;
पूर्ण
