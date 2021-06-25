<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  S390 version
 *    Copyright IBM Corp. 1999
 *    Author(s): Harपंचांगut Penner (hp@de.ibm.com)
 *               Ulrich Weigand (uweigand@de.ibm.com)
 *
 *  Derived from "arch/i386/mm/fault.c"
 *    Copyright (C) 1995  Linus Torvalds
 */

#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/perf_event.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/compat.h>
#समावेश <linux/smp.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/extable.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/hugetlb.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/gmap.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/uv.h>
#समावेश "../kernel/entry.h"

#घोषणा __FAIL_ADDR_MASK -4096L
#घोषणा __SUBCODE_MASK 0x0600
#घोषणा __PF_RES_FIELD 0x8000000000000000ULL

#घोषणा VM_FAULT_BADCONTEXT	((__क्रमce vm_fault_t) 0x010000)
#घोषणा VM_FAULT_BADMAP		((__क्रमce vm_fault_t) 0x020000)
#घोषणा VM_FAULT_BADACCESS	((__क्रमce vm_fault_t) 0x040000)
#घोषणा VM_FAULT_SIGNAL		((__क्रमce vm_fault_t) 0x080000)
#घोषणा VM_FAULT_PFAULT		((__क्रमce vm_fault_t) 0x100000)

क्रमागत fault_type अणु
	KERNEL_FAULT,
	USER_FAULT,
	GMAP_FAULT,
पूर्ण;

अटल अचिन्हित दीर्घ store_indication __पढ़ो_mostly;

अटल पूर्णांक __init fault_init(व्योम)
अणु
	अगर (test_facility(75))
		store_indication = 0xc00;
	वापस 0;
पूर्ण
early_initcall(fault_init);

/*
 * Find out which address space caused the exception.
 */
अटल क्रमागत fault_type get_fault_type(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ trans_exc_code;

	trans_exc_code = regs->पूर्णांक_parm_दीर्घ & 3;
	अगर (likely(trans_exc_code == 0)) अणु
		/* primary space exception */
		अगर (user_mode(regs))
			वापस USER_FAULT;
		अगर (!IS_ENABLED(CONFIG_PGSTE))
			वापस KERNEL_FAULT;
		अगर (test_pt_regs_flag(regs, PIF_GUEST_FAULT))
			वापस GMAP_FAULT;
		वापस KERNEL_FAULT;
	पूर्ण
	अगर (trans_exc_code == 2)
		वापस USER_FAULT;
	अगर (trans_exc_code == 1) अणु
		/* access रेजिस्टर mode, not used in the kernel */
		वापस USER_FAULT;
	पूर्ण
	/* home space exception -> access via kernel ASCE */
	वापस KERNEL_FAULT;
पूर्ण

अटल पूर्णांक bad_address(व्योम *p)
अणु
	अचिन्हित दीर्घ dummy;

	वापस get_kernel_nofault(dummy, (अचिन्हित दीर्घ *)p);
पूर्ण

अटल व्योम dump_pagetable(अचिन्हित दीर्घ asce, अचिन्हित दीर्घ address)
अणु
	अचिन्हित दीर्घ *table = __va(asce & _ASCE_ORIGIN);

	pr_alert("AS:%016lx ", asce);
	चयन (asce & _ASCE_TYPE_MASK) अणु
	हाल _ASCE_TYPE_REGION1:
		table += (address & _REGION1_INDEX) >> _REGION1_SHIFT;
		अगर (bad_address(table))
			जाओ bad;
		pr_cont("R1:%016lx ", *table);
		अगर (*table & _REGION_ENTRY_INVALID)
			जाओ out;
		table = (अचिन्हित दीर्घ *)(*table & _REGION_ENTRY_ORIGIN);
		fallthrough;
	हाल _ASCE_TYPE_REGION2:
		table += (address & _REGION2_INDEX) >> _REGION2_SHIFT;
		अगर (bad_address(table))
			जाओ bad;
		pr_cont("R2:%016lx ", *table);
		अगर (*table & _REGION_ENTRY_INVALID)
			जाओ out;
		table = (अचिन्हित दीर्घ *)(*table & _REGION_ENTRY_ORIGIN);
		fallthrough;
	हाल _ASCE_TYPE_REGION3:
		table += (address & _REGION3_INDEX) >> _REGION3_SHIFT;
		अगर (bad_address(table))
			जाओ bad;
		pr_cont("R3:%016lx ", *table);
		अगर (*table & (_REGION_ENTRY_INVALID | _REGION3_ENTRY_LARGE))
			जाओ out;
		table = (अचिन्हित दीर्घ *)(*table & _REGION_ENTRY_ORIGIN);
		fallthrough;
	हाल _ASCE_TYPE_SEGMENT:
		table += (address & _SEGMENT_INDEX) >> _SEGMENT_SHIFT;
		अगर (bad_address(table))
			जाओ bad;
		pr_cont("S:%016lx ", *table);
		अगर (*table & (_SEGMENT_ENTRY_INVALID | _SEGMENT_ENTRY_LARGE))
			जाओ out;
		table = (अचिन्हित दीर्घ *)(*table & _SEGMENT_ENTRY_ORIGIN);
	पूर्ण
	table += (address & _PAGE_INDEX) >> _PAGE_SHIFT;
	अगर (bad_address(table))
		जाओ bad;
	pr_cont("P:%016lx ", *table);
out:
	pr_cont("\n");
	वापस;
bad:
	pr_cont("BAD\n");
पूर्ण

अटल व्योम dump_fault_info(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ asce;

	pr_alert("Failing address: %016lx TEID: %016lx\n",
		 regs->पूर्णांक_parm_दीर्घ & __FAIL_ADDR_MASK, regs->पूर्णांक_parm_दीर्घ);
	pr_alert("Fault in ");
	चयन (regs->पूर्णांक_parm_दीर्घ & 3) अणु
	हाल 3:
		pr_cont("home space ");
		अवरोध;
	हाल 2:
		pr_cont("secondary space ");
		अवरोध;
	हाल 1:
		pr_cont("access register ");
		अवरोध;
	हाल 0:
		pr_cont("primary space ");
		अवरोध;
	पूर्ण
	pr_cont("mode while using ");
	चयन (get_fault_type(regs)) अणु
	हाल USER_FAULT:
		asce = S390_lowcore.user_asce;
		pr_cont("user ");
		अवरोध;
	हाल GMAP_FAULT:
		asce = ((काष्ठा gmap *) S390_lowcore.gmap)->asce;
		pr_cont("gmap ");
		अवरोध;
	हाल KERNEL_FAULT:
		asce = S390_lowcore.kernel_asce;
		pr_cont("kernel ");
		अवरोध;
	शेष:
		unreachable();
	पूर्ण
	pr_cont("ASCE.\n");
	dump_pagetable(asce, regs->पूर्णांक_parm_दीर्घ & __FAIL_ADDR_MASK);
पूर्ण

पूर्णांक show_unhandled_संकेतs = 1;

व्योम report_user_fault(काष्ठा pt_regs *regs, दीर्घ signr, पूर्णांक is_mm_fault)
अणु
	अगर ((task_pid_nr(current) > 1) && !show_unhandled_संकेतs)
		वापस;
	अगर (!unhandled_संकेत(current, signr))
		वापस;
	अगर (!prपूर्णांकk_ratelimit())
		वापस;
	prपूर्णांकk(KERN_ALERT "User process fault: interruption code %04x ilc:%d ",
	       regs->पूर्णांक_code & 0xffff, regs->पूर्णांक_code >> 17);
	prपूर्णांक_vma_addr(KERN_CONT "in ", regs->psw.addr);
	prपूर्णांकk(KERN_CONT "\n");
	अगर (is_mm_fault)
		dump_fault_info(regs);
	show_regs(regs);
पूर्ण

/*
 * Send संक_अंश to task.  This is an बाह्यal routine
 * to keep the stack usage of करो_page_fault small.
 */
अटल noअंतरभूत व्योम करो_sigsegv(काष्ठा pt_regs *regs, पूर्णांक si_code)
अणु
	report_user_fault(regs, संक_अंश, 1);
	क्रमce_sig_fault(संक_अंश, si_code,
			(व्योम __user *)(regs->पूर्णांक_parm_दीर्घ & __FAIL_ADDR_MASK));
पूर्ण

स्थिर काष्ठा exception_table_entry *s390_search_extables(अचिन्हित दीर्घ addr)
अणु
	स्थिर काष्ठा exception_table_entry *fixup;

	fixup = search_extable(__start_dma_ex_table,
			       __stop_dma_ex_table - __start_dma_ex_table,
			       addr);
	अगर (!fixup)
		fixup = search_exception_tables(addr);
	वापस fixup;
पूर्ण

अटल noअंतरभूत व्योम करो_no_context(काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा exception_table_entry *fixup;

	/* Are we prepared to handle this kernel fault?  */
	fixup = s390_search_extables(regs->psw.addr);
	अगर (fixup && ex_handle(fixup, regs))
		वापस;

	/*
	 * Oops. The kernel tried to access some bad page. We'll have to
	 * terminate things with extreme prejudice.
	 */
	अगर (get_fault_type(regs) == KERNEL_FAULT)
		prपूर्णांकk(KERN_ALERT "Unable to handle kernel pointer dereference"
		       " in virtual kernel address space\n");
	अन्यथा
		prपूर्णांकk(KERN_ALERT "Unable to handle kernel paging request"
		       " in virtual user address space\n");
	dump_fault_info(regs);
	die(regs, "Oops");
	करो_निकास(SIGKILL);
पूर्ण

अटल noअंतरभूत व्योम करो_low_address(काष्ठा pt_regs *regs)
अणु
	/* Low-address protection hit in kernel mode means
	   शून्य poपूर्णांकer ग_लिखो access in kernel mode.  */
	अगर (regs->psw.mask & PSW_MASK_PSTATE) अणु
		/* Low-address protection hit in user mode 'cannot happen'. */
		die (regs, "Low-address protection");
		करो_निकास(SIGKILL);
	पूर्ण

	करो_no_context(regs);
पूर्ण

अटल noअंतरभूत व्योम करो_sigbus(काष्ठा pt_regs *regs)
अणु
	/*
	 * Send a sigbus, regardless of whether we were in kernel
	 * or user mode.
	 */
	क्रमce_sig_fault(SIGBUS, BUS_ADRERR,
			(व्योम __user *)(regs->पूर्णांक_parm_दीर्घ & __FAIL_ADDR_MASK));
पूर्ण

अटल noअंतरभूत पूर्णांक संकेत_वापस(काष्ठा pt_regs *regs)
अणु
	u16 inकाष्ठाion;
	पूर्णांक rc;

	rc = __get_user(inकाष्ठाion, (u16 __user *) regs->psw.addr);
	अगर (rc)
		वापस rc;
	अगर (inकाष्ठाion == 0x0a77) अणु
		set_pt_regs_flag(regs, PIF_SYSCALL);
		regs->पूर्णांक_code = 0x00040077;
		वापस 0;
	पूर्ण अन्यथा अगर (inकाष्ठाion == 0x0aad) अणु
		set_pt_regs_flag(regs, PIF_SYSCALL);
		regs->पूर्णांक_code = 0x000400ad;
		वापस 0;
	पूर्ण
	वापस -EACCES;
पूर्ण

अटल noअंतरभूत व्योम करो_fault_error(काष्ठा pt_regs *regs, पूर्णांक access,
					vm_fault_t fault)
अणु
	पूर्णांक si_code;

	चयन (fault) अणु
	हाल VM_FAULT_BADACCESS:
		अगर (access == VM_EXEC && संकेत_वापस(regs) == 0)
			अवरोध;
		fallthrough;
	हाल VM_FAULT_BADMAP:
		/* Bad memory access. Check अगर it is kernel or user space. */
		अगर (user_mode(regs)) अणु
			/* User mode accesses just cause a संक_अंश */
			si_code = (fault == VM_FAULT_BADMAP) ?
				SEGV_MAPERR : SEGV_ACCERR;
			करो_sigsegv(regs, si_code);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल VM_FAULT_BADCONTEXT:
	हाल VM_FAULT_PFAULT:
		करो_no_context(regs);
		अवरोध;
	हाल VM_FAULT_SIGNAL:
		अगर (!user_mode(regs))
			करो_no_context(regs);
		अवरोध;
	शेष: /* fault & VM_FAULT_ERROR */
		अगर (fault & VM_FAULT_OOM) अणु
			अगर (!user_mode(regs))
				करो_no_context(regs);
			अन्यथा
				pagefault_out_of_memory();
		पूर्ण अन्यथा अगर (fault & VM_FAULT_संक_अंश) अणु
			/* Kernel mode? Handle exceptions or die */
			अगर (!user_mode(regs))
				करो_no_context(regs);
			अन्यथा
				करो_sigsegv(regs, SEGV_MAPERR);
		पूर्ण अन्यथा अगर (fault & VM_FAULT_SIGBUS) अणु
			/* Kernel mode? Handle exceptions or die */
			अगर (!user_mode(regs))
				करो_no_context(regs);
			अन्यथा
				करो_sigbus(regs);
		पूर्ण अन्यथा
			BUG();
		अवरोध;
	पूर्ण
पूर्ण

/*
 * This routine handles page faults.  It determines the address,
 * and the problem, and then passes it off to one of the appropriate
 * routines.
 *
 * पूर्णांकerruption code (पूर्णांक_code):
 *   04       Protection           ->  Write-Protection  (suppression)
 *   10       Segment translation  ->  Not present       (nullअगरication)
 *   11       Page translation     ->  Not present       (nullअगरication)
 *   3b       Region third trans.  ->  Not present       (nullअगरication)
 */
अटल अंतरभूत vm_fault_t करो_exception(काष्ठा pt_regs *regs, पूर्णांक access)
अणु
	काष्ठा gmap *gmap;
	काष्ठा task_काष्ठा *tsk;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा vm_area_काष्ठा *vma;
	क्रमागत fault_type type;
	अचिन्हित दीर्घ trans_exc_code;
	अचिन्हित दीर्घ address;
	अचिन्हित पूर्णांक flags;
	vm_fault_t fault;

	tsk = current;
	/*
	 * The inकाष्ठाion that caused the program check has
	 * been nullअगरied. Don't संकेत single step via SIGTRAP.
	 */
	clear_thपढ़ो_flag(TIF_PER_TRAP);

	अगर (kprobe_page_fault(regs, 14))
		वापस 0;

	mm = tsk->mm;
	trans_exc_code = regs->पूर्णांक_parm_दीर्घ;

	/*
	 * Verअगरy that the fault happened in user space, that
	 * we are not in an पूर्णांकerrupt and that there is a 
	 * user context.
	 */
	fault = VM_FAULT_BADCONTEXT;
	type = get_fault_type(regs);
	चयन (type) अणु
	हाल KERNEL_FAULT:
		जाओ out;
	हाल USER_FAULT:
	हाल GMAP_FAULT:
		अगर (faulthandler_disabled() || !mm)
			जाओ out;
		अवरोध;
	पूर्ण

	address = trans_exc_code & __FAIL_ADDR_MASK;
	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, address);
	flags = FAULT_FLAG_DEFAULT;
	अगर (user_mode(regs))
		flags |= FAULT_FLAG_USER;
	अगर (access == VM_WRITE || (trans_exc_code & store_indication) == 0x400)
		flags |= FAULT_FLAG_WRITE;
	mmap_पढ़ो_lock(mm);

	gmap = शून्य;
	अगर (IS_ENABLED(CONFIG_PGSTE) && type == GMAP_FAULT) अणु
		gmap = (काष्ठा gmap *) S390_lowcore.gmap;
		current->thपढ़ो.gmap_addr = address;
		current->thपढ़ो.gmap_ग_लिखो_flag = !!(flags & FAULT_FLAG_WRITE);
		current->thपढ़ो.gmap_पूर्णांक_code = regs->पूर्णांक_code & 0xffff;
		address = __gmap_translate(gmap, address);
		अगर (address == -EFAULT) अणु
			fault = VM_FAULT_BADMAP;
			जाओ out_up;
		पूर्ण
		अगर (gmap->pfault_enabled)
			flags |= FAULT_FLAG_RETRY_NOWAIT;
	पूर्ण

retry:
	fault = VM_FAULT_BADMAP;
	vma = find_vma(mm, address);
	अगर (!vma)
		जाओ out_up;

	अगर (unlikely(vma->vm_start > address)) अणु
		अगर (!(vma->vm_flags & VM_GROWSDOWN))
			जाओ out_up;
		अगर (expand_stack(vma, address))
			जाओ out_up;
	पूर्ण

	/*
	 * Ok, we have a good vm_area क्रम this memory access, so
	 * we can handle it..
	 */
	fault = VM_FAULT_BADACCESS;
	अगर (unlikely(!(vma->vm_flags & access)))
		जाओ out_up;

	अगर (is_vm_hugetlb_page(vma))
		address &= HPAGE_MASK;
	/*
	 * If क्रम any reason at all we couldn't handle the fault,
	 * make sure we निकास gracefully rather than endlessly reकरो
	 * the fault.
	 */
	fault = handle_mm_fault(vma, address, flags, regs);
	अगर (fault_संकेत_pending(fault, regs)) अणु
		fault = VM_FAULT_SIGNAL;
		अगर (flags & FAULT_FLAG_RETRY_NOWAIT)
			जाओ out_up;
		जाओ out;
	पूर्ण
	अगर (unlikely(fault & VM_FAULT_ERROR))
		जाओ out_up;

	अगर (flags & FAULT_FLAG_ALLOW_RETRY) अणु
		अगर (fault & VM_FAULT_RETRY) अणु
			अगर (IS_ENABLED(CONFIG_PGSTE) && gmap &&
			    (flags & FAULT_FLAG_RETRY_NOWAIT)) अणु
				/* FAULT_FLAG_RETRY_NOWAIT has been set,
				 * mmap_lock has not been released */
				current->thपढ़ो.gmap_pfault = 1;
				fault = VM_FAULT_PFAULT;
				जाओ out_up;
			पूर्ण
			flags &= ~FAULT_FLAG_RETRY_NOWAIT;
			flags |= FAULT_FLAG_TRIED;
			mmap_पढ़ो_lock(mm);
			जाओ retry;
		पूर्ण
	पूर्ण
	अगर (IS_ENABLED(CONFIG_PGSTE) && gmap) अणु
		address =  __gmap_link(gmap, current->thपढ़ो.gmap_addr,
				       address);
		अगर (address == -EFAULT) अणु
			fault = VM_FAULT_BADMAP;
			जाओ out_up;
		पूर्ण
		अगर (address == -ENOMEM) अणु
			fault = VM_FAULT_OOM;
			जाओ out_up;
		पूर्ण
	पूर्ण
	fault = 0;
out_up:
	mmap_पढ़ो_unlock(mm);
out:
	वापस fault;
पूर्ण

व्योम करो_protection_exception(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ trans_exc_code;
	पूर्णांक access;
	vm_fault_t fault;

	trans_exc_code = regs->पूर्णांक_parm_दीर्घ;
	/*
	 * Protection exceptions are suppressing, decrement psw address.
	 * The exception to this rule are पातed transactions, क्रम these
	 * the PSW alपढ़ोy poपूर्णांकs to the correct location.
	 */
	अगर (!(regs->पूर्णांक_code & 0x200))
		regs->psw.addr = __शुरुआत_psw(regs->psw, regs->पूर्णांक_code >> 16);
	/*
	 * Check क्रम low-address protection.  This needs to be treated
	 * as a special हाल because the translation exception code
	 * field is not guaranteed to contain valid data in this हाल.
	 */
	अगर (unlikely(!(trans_exc_code & 4))) अणु
		करो_low_address(regs);
		वापस;
	पूर्ण
	अगर (unlikely(MACHINE_HAS_NX && (trans_exc_code & 0x80))) अणु
		regs->पूर्णांक_parm_दीर्घ = (trans_exc_code & ~PAGE_MASK) |
					(regs->psw.addr & PAGE_MASK);
		access = VM_EXEC;
		fault = VM_FAULT_BADACCESS;
	पूर्ण अन्यथा अणु
		access = VM_WRITE;
		fault = करो_exception(regs, access);
	पूर्ण
	अगर (unlikely(fault))
		करो_fault_error(regs, access, fault);
पूर्ण
NOKPROBE_SYMBOL(करो_protection_exception);

व्योम करो_dat_exception(काष्ठा pt_regs *regs)
अणु
	पूर्णांक access;
	vm_fault_t fault;

	access = VM_ACCESS_FLAGS;
	fault = करो_exception(regs, access);
	अगर (unlikely(fault))
		करो_fault_error(regs, access, fault);
पूर्ण
NOKPROBE_SYMBOL(करो_dat_exception);

#अगर_घोषित CONFIG_PFAULT 
/*
 * 'pfault' pseuकरो page faults routines.
 */
अटल पूर्णांक pfault_disable;

अटल पूर्णांक __init nopfault(अक्षर *str)
अणु
	pfault_disable = 1;
	वापस 1;
पूर्ण

__setup("nopfault", nopfault);

काष्ठा pfault_refbk अणु
	u16 refdiagc;
	u16 reffcode;
	u16 refdwlen;
	u16 refversn;
	u64 refgaddr;
	u64 refselmk;
	u64 refcmpmk;
	u64 reserved;
पूर्ण __attribute__ ((packed, aligned(8)));

अटल काष्ठा pfault_refbk pfault_init_refbk = अणु
	.refdiagc = 0x258,
	.reffcode = 0,
	.refdwlen = 5,
	.refversn = 2,
	.refgaddr = __LC_LPP,
	.refselmk = 1ULL << 48,
	.refcmpmk = 1ULL << 48,
	.reserved = __PF_RES_FIELD
पूर्ण;

पूर्णांक pfault_init(व्योम)
अणु
        पूर्णांक rc;

	अगर (pfault_disable)
		वापस -1;
	diag_stat_inc(DIAG_STAT_X258);
	यंत्र अस्थिर(
		"	diag	%1,%0,0x258\n"
		"0:	j	2f\n"
		"1:	la	%0,8\n"
		"2:\n"
		EX_TABLE(0b,1b)
		: "=d" (rc)
		: "a" (&pfault_init_refbk), "m" (pfault_init_refbk) : "cc");
        वापस rc;
पूर्ण

अटल काष्ठा pfault_refbk pfault_fini_refbk = अणु
	.refdiagc = 0x258,
	.reffcode = 1,
	.refdwlen = 5,
	.refversn = 2,
पूर्ण;

व्योम pfault_fini(व्योम)
अणु

	अगर (pfault_disable)
		वापस;
	diag_stat_inc(DIAG_STAT_X258);
	यंत्र अस्थिर(
		"	diag	%0,0,0x258\n"
		"0:	nopr	%%r7\n"
		EX_TABLE(0b,0b)
		: : "a" (&pfault_fini_refbk), "m" (pfault_fini_refbk) : "cc");
पूर्ण

अटल DEFINE_SPINLOCK(pfault_lock);
अटल LIST_HEAD(pfault_list);

#घोषणा PF_COMPLETE	0x0080

/*
 * The mechanism of our pfault code: अगर Linux is running as guest, runs a user
 * space process and the user space process accesses a page that the host has
 * paged out we get a pfault पूर्णांकerrupt.
 *
 * This allows us, within the guest, to schedule a dअगरferent process. Without
 * this mechanism the host would have to suspend the whole भव cpu until
 * the page has been paged in.
 *
 * So when we get such an पूर्णांकerrupt then we set the state of the current task
 * to unपूर्णांकerruptible and also set the need_resched flag. Both happens within
 * पूर्णांकerrupt context(!). If we later on want to वापस to user space we
 * recognize the need_resched flag and then call schedule().  It's not very
 * obvious how this works...
 *
 * Of course we have a lot of additional fun with the completion पूर्णांकerrupt (->
 * host संकेतs that a page of a process has been paged in and the process can
 * जारी to run). This पूर्णांकerrupt can arrive on any cpu and, since we have
 * भव cpus, actually appear beक्रमe the पूर्णांकerrupt that संकेतs that a page
 * is missing.
 */
अटल व्योम pfault_पूर्णांकerrupt(काष्ठा ext_code ext_code,
			     अचिन्हित पूर्णांक param32, अचिन्हित दीर्घ param64)
अणु
	काष्ठा task_काष्ठा *tsk;
	__u16 subcode;
	pid_t pid;

	/*
	 * Get the बाह्यal पूर्णांकerruption subcode & pfault initial/completion
	 * संकेत bit. VM stores this in the 'cpu address' field associated
	 * with the बाह्यal पूर्णांकerrupt.
	 */
	subcode = ext_code.subcode;
	अगर ((subcode & 0xff00) != __SUBCODE_MASK)
		वापस;
	inc_irq_stat(IRQEXT_PFL);
	/* Get the token (= pid of the affected task). */
	pid = param64 & LPP_PID_MASK;
	rcu_पढ़ो_lock();
	tsk = find_task_by_pid_ns(pid, &init_pid_ns);
	अगर (tsk)
		get_task_काष्ठा(tsk);
	rcu_पढ़ो_unlock();
	अगर (!tsk)
		वापस;
	spin_lock(&pfault_lock);
	अगर (subcode & PF_COMPLETE) अणु
		/* संकेत bit is set -> a page has been swapped in by VM */
		अगर (tsk->thपढ़ो.pfault_रुको == 1) अणु
			/* Initial पूर्णांकerrupt was faster than the completion
			 * पूर्णांकerrupt. pfault_रुको is valid. Set pfault_रुको
			 * back to zero and wake up the process. This can
			 * safely be करोne because the task is still sleeping
			 * and can't produce new pfaults. */
			tsk->thपढ़ो.pfault_रुको = 0;
			list_del(&tsk->thपढ़ो.list);
			wake_up_process(tsk);
			put_task_काष्ठा(tsk);
		पूर्ण अन्यथा अणु
			/* Completion पूर्णांकerrupt was faster than initial
			 * पूर्णांकerrupt. Set pfault_रुको to -1 so the initial
			 * पूर्णांकerrupt करोesn't put the task to sleep.
			 * If the task is not running, ignore the completion
			 * पूर्णांकerrupt since it must be a leftover of a PFAULT
			 * CANCEL operation which didn't हटाओ all pending
			 * completion पूर्णांकerrupts. */
			अगर (tsk->state == TASK_RUNNING)
				tsk->thपढ़ो.pfault_रुको = -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* संकेत bit not set -> a real page is missing. */
		अगर (WARN_ON_ONCE(tsk != current))
			जाओ out;
		अगर (tsk->thपढ़ो.pfault_रुको == 1) अणु
			/* Alपढ़ोy on the list with a reference: put to sleep */
			जाओ block;
		पूर्ण अन्यथा अगर (tsk->thपढ़ो.pfault_रुको == -1) अणु
			/* Completion पूर्णांकerrupt was faster than the initial
			 * पूर्णांकerrupt (pfault_रुको == -1). Set pfault_रुको
			 * back to zero and निकास. */
			tsk->thपढ़ो.pfault_रुको = 0;
		पूर्ण अन्यथा अणु
			/* Initial पूर्णांकerrupt arrived beक्रमe completion
			 * पूर्णांकerrupt. Let the task sleep.
			 * An extra task reference is needed since a dअगरferent
			 * cpu may set the task state to TASK_RUNNING again
			 * beक्रमe the scheduler is reached. */
			get_task_काष्ठा(tsk);
			tsk->thपढ़ो.pfault_रुको = 1;
			list_add(&tsk->thपढ़ो.list, &pfault_list);
block:
			/* Since this must be a userspace fault, there
			 * is no kernel task state to trample. Rely on the
			 * वापस to userspace schedule() to block. */
			__set_current_state(TASK_UNINTERRUPTIBLE);
			set_tsk_need_resched(tsk);
			set_preempt_need_resched();
		पूर्ण
	पूर्ण
out:
	spin_unlock(&pfault_lock);
	put_task_काष्ठा(tsk);
पूर्ण

अटल पूर्णांक pfault_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा thपढ़ो_काष्ठा *thपढ़ो, *next;
	काष्ठा task_काष्ठा *tsk;

	spin_lock_irq(&pfault_lock);
	list_क्रम_each_entry_safe(thपढ़ो, next, &pfault_list, list) अणु
		thपढ़ो->pfault_रुको = 0;
		list_del(&thपढ़ो->list);
		tsk = container_of(thपढ़ो, काष्ठा task_काष्ठा, thपढ़ो);
		wake_up_process(tsk);
		put_task_काष्ठा(tsk);
	पूर्ण
	spin_unlock_irq(&pfault_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक __init pfault_irq_init(व्योम)
अणु
	पूर्णांक rc;

	rc = रेजिस्टर_बाह्यal_irq(EXT_IRQ_CP_SERVICE, pfault_पूर्णांकerrupt);
	अगर (rc)
		जाओ out_extपूर्णांक;
	rc = pfault_init() == 0 ? 0 : -EOPNOTSUPP;
	अगर (rc)
		जाओ out_pfault;
	irq_subclass_रेजिस्टर(IRQ_SUBCLASS_SERVICE_SIGNAL);
	cpuhp_setup_state_nocalls(CPUHP_S390_PFAULT_DEAD, "s390/pfault:dead",
				  शून्य, pfault_cpu_dead);
	वापस 0;

out_pfault:
	unरेजिस्टर_बाह्यal_irq(EXT_IRQ_CP_SERVICE, pfault_पूर्णांकerrupt);
out_extपूर्णांक:
	pfault_disable = 1;
	वापस rc;
पूर्ण
early_initcall(pfault_irq_init);

#पूर्ण_अगर /* CONFIG_PFAULT */

#अगर IS_ENABLED(CONFIG_PGSTE)

व्योम करो_secure_storage_access(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ addr = regs->पूर्णांक_parm_दीर्घ & __FAIL_ADDR_MASK;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा page *page;
	पूर्णांक rc;

	चयन (get_fault_type(regs)) अणु
	हाल USER_FAULT:
		mm = current->mm;
		mmap_पढ़ो_lock(mm);
		vma = find_vma(mm, addr);
		अगर (!vma) अणु
			mmap_पढ़ो_unlock(mm);
			करो_fault_error(regs, VM_READ | VM_WRITE, VM_FAULT_BADMAP);
			अवरोध;
		पूर्ण
		page = follow_page(vma, addr, FOLL_WRITE | FOLL_GET);
		अगर (IS_ERR_OR_शून्य(page)) अणु
			mmap_पढ़ो_unlock(mm);
			अवरोध;
		पूर्ण
		अगर (arch_make_page_accessible(page))
			send_sig(संक_अंश, current, 0);
		put_page(page);
		mmap_पढ़ो_unlock(mm);
		अवरोध;
	हाल KERNEL_FAULT:
		page = phys_to_page(addr);
		अगर (unlikely(!try_get_page(page)))
			अवरोध;
		rc = arch_make_page_accessible(page);
		put_page(page);
		अगर (rc)
			BUG();
		अवरोध;
	हाल GMAP_FAULT:
	शेष:
		करो_fault_error(regs, VM_READ | VM_WRITE, VM_FAULT_BADMAP);
		WARN_ON_ONCE(1);
	पूर्ण
पूर्ण
NOKPROBE_SYMBOL(करो_secure_storage_access);

व्योम करो_non_secure_storage_access(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ gaddr = regs->पूर्णांक_parm_दीर्घ & __FAIL_ADDR_MASK;
	काष्ठा gmap *gmap = (काष्ठा gmap *)S390_lowcore.gmap;

	अगर (get_fault_type(regs) != GMAP_FAULT) अणु
		करो_fault_error(regs, VM_READ | VM_WRITE, VM_FAULT_BADMAP);
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	अगर (gmap_convert_to_secure(gmap, gaddr) == -EINVAL)
		send_sig(संक_अंश, current, 0);
पूर्ण
NOKPROBE_SYMBOL(करो_non_secure_storage_access);

व्योम करो_secure_storage_violation(काष्ठा pt_regs *regs)
अणु
	/*
	 * Either KVM messed up the secure guest mapping or the same
	 * page is mapped पूर्णांकo multiple secure guests.
	 *
	 * This exception is only triggered when a guest 2 is running
	 * and can thereक्रमe never occur in kernel context.
	 */
	prपूर्णांकk_ratelimited(KERN_WARNING
			   "Secure storage violation in task: %s, pid %d\n",
			   current->comm, current->pid);
	send_sig(संक_अंश, current, 0);
पूर्ण

#पूर्ण_अगर /* CONFIG_PGSTE */
