<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/mm/fault.c
 *
 * Copyright (C) 1995  Linus Torvalds
 * Copyright (C) 1995-2004 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/extable.h>
#समावेश <linux/kfence.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/mm.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/init.h>
#समावेश <linux/kasan.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/debug.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/perf_event.h>
#समावेश <linux/preempt.h>
#समावेश <linux/hugetlb.h>

#समावेश <यंत्र/acpi.h>
#समावेश <यंत्र/bug.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/daअगरflags.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/esr.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/mte.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sysreg.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/traps.h>

काष्ठा fault_info अणु
	पूर्णांक	(*fn)(अचिन्हित दीर्घ far, अचिन्हित पूर्णांक esr,
		      काष्ठा pt_regs *regs);
	पूर्णांक	sig;
	पूर्णांक	code;
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा fault_info fault_info[];
अटल काष्ठा fault_info debug_fault_info[];

अटल अंतरभूत स्थिर काष्ठा fault_info *esr_to_fault_info(अचिन्हित पूर्णांक esr)
अणु
	वापस fault_info + (esr & ESR_ELx_FSC);
पूर्ण

अटल अंतरभूत स्थिर काष्ठा fault_info *esr_to_debug_fault_info(अचिन्हित पूर्णांक esr)
अणु
	वापस debug_fault_info + DBG_ESR_EVT(esr);
पूर्ण

अटल व्योम data_पात_decode(अचिन्हित पूर्णांक esr)
अणु
	pr_alert("Data abort info:\n");

	अगर (esr & ESR_ELx_ISV) अणु
		pr_alert("  Access size = %u byte(s)\n",
			 1U << ((esr & ESR_ELx_SAS) >> ESR_ELx_SAS_SHIFT));
		pr_alert("  SSE = %lu, SRT = %lu\n",
			 (esr & ESR_ELx_SSE) >> ESR_ELx_SSE_SHIFT,
			 (esr & ESR_ELx_SRT_MASK) >> ESR_ELx_SRT_SHIFT);
		pr_alert("  SF = %lu, AR = %lu\n",
			 (esr & ESR_ELx_SF) >> ESR_ELx_SF_SHIFT,
			 (esr & ESR_ELx_AR) >> ESR_ELx_AR_SHIFT);
	पूर्ण अन्यथा अणु
		pr_alert("  ISV = 0, ISS = 0x%08lx\n", esr & ESR_ELx_ISS_MASK);
	पूर्ण

	pr_alert("  CM = %lu, WnR = %lu\n",
		 (esr & ESR_ELx_CM) >> ESR_ELx_CM_SHIFT,
		 (esr & ESR_ELx_WNR) >> ESR_ELx_WNR_SHIFT);
पूर्ण

अटल व्योम mem_पात_decode(अचिन्हित पूर्णांक esr)
अणु
	pr_alert("Mem abort info:\n");

	pr_alert("  ESR = 0x%08x\n", esr);
	pr_alert("  EC = 0x%02lx: %s, IL = %u bits\n",
		 ESR_ELx_EC(esr), esr_get_class_string(esr),
		 (esr & ESR_ELx_IL) ? 32 : 16);
	pr_alert("  SET = %lu, FnV = %lu\n",
		 (esr & ESR_ELx_SET_MASK) >> ESR_ELx_SET_SHIFT,
		 (esr & ESR_ELx_FnV) >> ESR_ELx_FnV_SHIFT);
	pr_alert("  EA = %lu, S1PTW = %lu\n",
		 (esr & ESR_ELx_EA) >> ESR_ELx_EA_SHIFT,
		 (esr & ESR_ELx_S1PTW) >> ESR_ELx_S1PTW_SHIFT);

	अगर (esr_is_data_पात(esr))
		data_पात_decode(esr);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mm_to_pgd_phys(काष्ठा mm_काष्ठा *mm)
अणु
	/* Either init_pg_dir or swapper_pg_dir */
	अगर (mm == &init_mm)
		वापस __pa_symbol(mm->pgd);

	वापस (अचिन्हित दीर्घ)virt_to_phys(mm->pgd);
पूर्ण

/*
 * Dump out the page tables associated with 'addr' in the currently active mm.
 */
अटल व्योम show_pte(अचिन्हित दीर्घ addr)
अणु
	काष्ठा mm_काष्ठा *mm;
	pgd_t *pgdp;
	pgd_t pgd;

	अगर (is_ttbr0_addr(addr)) अणु
		/* TTBR0 */
		mm = current->active_mm;
		अगर (mm == &init_mm) अणु
			pr_alert("[%016lx] user address but active_mm is swapper\n",
				 addr);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (is_ttbr1_addr(addr)) अणु
		/* TTBR1 */
		mm = &init_mm;
	पूर्ण अन्यथा अणु
		pr_alert("[%016lx] address between user and kernel address ranges\n",
			 addr);
		वापस;
	पूर्ण

	pr_alert("%s pgtable: %luk pages, %llu-bit VAs, pgdp=%016lx\n",
		 mm == &init_mm ? "swapper" : "user", PAGE_SIZE / SZ_1K,
		 vabits_actual, mm_to_pgd_phys(mm));
	pgdp = pgd_offset(mm, addr);
	pgd = READ_ONCE(*pgdp);
	pr_alert("[%016lx] pgd=%016llx", addr, pgd_val(pgd));

	करो अणु
		p4d_t *p4dp, p4d;
		pud_t *pudp, pud;
		pmd_t *pmdp, pmd;
		pte_t *ptep, pte;

		अगर (pgd_none(pgd) || pgd_bad(pgd))
			अवरोध;

		p4dp = p4d_offset(pgdp, addr);
		p4d = READ_ONCE(*p4dp);
		pr_cont(", p4d=%016llx", p4d_val(p4d));
		अगर (p4d_none(p4d) || p4d_bad(p4d))
			अवरोध;

		pudp = pud_offset(p4dp, addr);
		pud = READ_ONCE(*pudp);
		pr_cont(", pud=%016llx", pud_val(pud));
		अगर (pud_none(pud) || pud_bad(pud))
			अवरोध;

		pmdp = pmd_offset(pudp, addr);
		pmd = READ_ONCE(*pmdp);
		pr_cont(", pmd=%016llx", pmd_val(pmd));
		अगर (pmd_none(pmd) || pmd_bad(pmd))
			अवरोध;

		ptep = pte_offset_map(pmdp, addr);
		pte = READ_ONCE(*ptep);
		pr_cont(", pte=%016llx", pte_val(pte));
		pte_unmap(ptep);
	पूर्ण जबतक(0);

	pr_cont("\n");
पूर्ण

/*
 * This function sets the access flags (dirty, accessed), as well as ग_लिखो
 * permission, and only to a more permissive setting.
 *
 * It needs to cope with hardware update of the accessed/dirty state by other
 * agents in the प्रणाली and can safely skip the __sync_icache_dcache() call as,
 * like set_pte_at(), the PTE is never changed from no-exec to exec here.
 *
 * Returns whether or not the PTE actually changed.
 */
पूर्णांक ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
			  अचिन्हित दीर्घ address, pte_t *ptep,
			  pte_t entry, पूर्णांक dirty)
अणु
	pteval_t old_pteval, pteval;
	pte_t pte = READ_ONCE(*ptep);

	अगर (pte_same(pte, entry))
		वापस 0;

	/* only preserve the access flags and ग_लिखो permission */
	pte_val(entry) &= PTE_RDONLY | PTE_AF | PTE_WRITE | PTE_सूचीTY;

	/*
	 * Setting the flags must be करोne atomically to aव्योम racing with the
	 * hardware update of the access/dirty state. The PTE_RDONLY bit must
	 * be set to the most permissive (lowest value) of *ptep and entry
	 * (calculated as: a & b == ~(~a | ~b)).
	 */
	pte_val(entry) ^= PTE_RDONLY;
	pteval = pte_val(pte);
	करो अणु
		old_pteval = pteval;
		pteval ^= PTE_RDONLY;
		pteval |= pte_val(entry);
		pteval ^= PTE_RDONLY;
		pteval = cmpxchg_relaxed(&pte_val(*ptep), old_pteval, pteval);
	पूर्ण जबतक (pteval != old_pteval);

	/* Invalidate a stale पढ़ो-only entry */
	अगर (dirty)
		flush_tlb_page(vma, address);
	वापस 1;
पूर्ण

अटल bool is_el1_inकाष्ठाion_पात(अचिन्हित पूर्णांक esr)
अणु
	वापस ESR_ELx_EC(esr) == ESR_ELx_EC_IABT_CUR;
पूर्ण

अटल अंतरभूत bool is_el1_permission_fault(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक esr,
					   काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक ec       = ESR_ELx_EC(esr);
	अचिन्हित पूर्णांक fsc_type = esr & ESR_ELx_FSC_TYPE;

	अगर (ec != ESR_ELx_EC_DABT_CUR && ec != ESR_ELx_EC_IABT_CUR)
		वापस false;

	अगर (fsc_type == ESR_ELx_FSC_PERM)
		वापस true;

	अगर (is_ttbr0_addr(addr) && प्रणाली_uses_ttbr0_pan())
		वापस fsc_type == ESR_ELx_FSC_FAULT &&
			(regs->pstate & PSR_PAN_BIT);

	वापस false;
पूर्ण

अटल bool __kprobes is_spurious_el1_translation_fault(अचिन्हित दीर्घ addr,
							अचिन्हित पूर्णांक esr,
							काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ flags;
	u64 par, dfsc;

	अगर (ESR_ELx_EC(esr) != ESR_ELx_EC_DABT_CUR ||
	    (esr & ESR_ELx_FSC_TYPE) != ESR_ELx_FSC_FAULT)
		वापस false;

	local_irq_save(flags);
	यंत्र अस्थिर("at s1e1r, %0" :: "r" (addr));
	isb();
	par = पढ़ो_sysreg_par();
	local_irq_restore(flags);

	/*
	 * If we now have a valid translation, treat the translation fault as
	 * spurious.
	 */
	अगर (!(par & SYS_PAR_EL1_F))
		वापस true;

	/*
	 * If we got a dअगरferent type of fault from the AT inकाष्ठाion,
	 * treat the translation fault as spurious.
	 */
	dfsc = FIELD_GET(SYS_PAR_EL1_FST, par);
	वापस (dfsc & ESR_ELx_FSC_TYPE) != ESR_ELx_FSC_FAULT;
पूर्ण

अटल व्योम die_kernel_fault(स्थिर अक्षर *msg, अचिन्हित दीर्घ addr,
			     अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	bust_spinlocks(1);

	pr_alert("Unable to handle kernel %s at virtual address %016lx\n", msg,
		 addr);

	mem_पात_decode(esr);

	show_pte(addr);
	die("Oops", regs, esr);
	bust_spinlocks(0);
	करो_निकास(SIGKILL);
पूर्ण

#अगर_घोषित CONFIG_KASAN_HW_TAGS
अटल व्योम report_tag_fault(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक esr,
			     काष्ठा pt_regs *regs)
अणु
	अटल bool reported;
	bool is_ग_लिखो;

	अगर (READ_ONCE(reported))
		वापस;

	/*
	 * This is used क्रम KASAN tests and assumes that no MTE faults
	 * happened beक्रमe running the tests.
	 */
	अगर (mte_report_once())
		WRITE_ONCE(reported, true);

	/*
	 * SAS bits aren't set for all faults reported in EL1, so we can't
	 * find out access size.
	 */
	is_ग_लिखो = !!(esr & ESR_ELx_WNR);
	kasan_report(addr, 0, is_ग_लिखो, regs->pc);
पूर्ण
#अन्यथा
/* Tag faults aren't enabled without CONFIG_KASAN_HW_TAGS. */
अटल अंतरभूत व्योम report_tag_fault(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक esr,
				    काष्ठा pt_regs *regs) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम करो_tag_recovery(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक esr,
			   काष्ठा pt_regs *regs)
अणु

	report_tag_fault(addr, esr, regs);

	/*
	 * Disable MTE Tag Checking on the local CPU क्रम the current EL.
	 * It will be करोne lazily on the other CPUs when they will hit a
	 * tag fault.
	 */
	sysreg_clear_set(sctlr_el1, SCTLR_ELx_TCF_MASK, SCTLR_ELx_TCF_NONE);
	isb();
पूर्ण

अटल bool is_el1_mte_sync_tag_check_fault(अचिन्हित पूर्णांक esr)
अणु
	अचिन्हित पूर्णांक ec = ESR_ELx_EC(esr);
	अचिन्हित पूर्णांक fsc = esr & ESR_ELx_FSC;

	अगर (ec != ESR_ELx_EC_DABT_CUR)
		वापस false;

	अगर (fsc == ESR_ELx_FSC_MTE)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम __करो_kernel_fault(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक esr,
			      काष्ठा pt_regs *regs)
अणु
	स्थिर अक्षर *msg;

	/*
	 * Are we prepared to handle this kernel fault?
	 * We are almost certainly not prepared to handle inकाष्ठाion faults.
	 */
	अगर (!is_el1_inकाष्ठाion_पात(esr) && fixup_exception(regs))
		वापस;

	अगर (WARN_RATELIMIT(is_spurious_el1_translation_fault(addr, esr, regs),
	    "Ignoring spurious kernel translation fault at virtual address %016lx\n", addr))
		वापस;

	अगर (is_el1_mte_sync_tag_check_fault(esr)) अणु
		करो_tag_recovery(addr, esr, regs);

		वापस;
	पूर्ण

	अगर (is_el1_permission_fault(addr, esr, regs)) अणु
		अगर (esr & ESR_ELx_WNR)
			msg = "write to read-only memory";
		अन्यथा अगर (is_el1_inकाष्ठाion_पात(esr))
			msg = "execute from non-executable memory";
		अन्यथा
			msg = "read from unreadable memory";
	पूर्ण अन्यथा अगर (addr < PAGE_SIZE) अणु
		msg = "NULL pointer dereference";
	पूर्ण अन्यथा अणु
		अगर (kfence_handle_page_fault(addr, esr & ESR_ELx_WNR, regs))
			वापस;

		msg = "paging request";
	पूर्ण

	die_kernel_fault(msg, addr, esr, regs);
पूर्ण

अटल व्योम set_thपढ़ो_esr(अचिन्हित दीर्घ address, अचिन्हित पूर्णांक esr)
अणु
	current->thपढ़ो.fault_address = address;

	/*
	 * If the faulting address is in the kernel, we must sanitize the ESR.
	 * From userspace's point of view, kernel-only mappings don't exist
	 * at all, so we report them as level 0 translation faults.
	 * (This is not quite the way that "no mapping there at all" behaves:
	 * an alignment fault not caused by the memory type would take
	 * precedence over translation fault क्रम a real access to empty
	 * space. Unक्रमtunately we can't easily distinguish "alignment fault
	 * not caused by memory type" from "alignment fault caused by memory
	 * type", so we ignore this wrinkle and just वापस the translation
	 * fault.)
	 */
	अगर (!is_ttbr0_addr(current->thपढ़ो.fault_address)) अणु
		चयन (ESR_ELx_EC(esr)) अणु
		हाल ESR_ELx_EC_DABT_LOW:
			/*
			 * These bits provide only inक्रमmation about the
			 * faulting inकाष्ठाion, which userspace knows alपढ़ोy.
			 * We explicitly clear bits which are architecturally
			 * RES0 in हाल they are given meanings in future.
			 * We always report the ESR as अगर the fault was taken
			 * to EL1 and so ISV and the bits in ISS[23:14] are
			 * clear. (In fact it always will be a fault to EL1.)
			 */
			esr &= ESR_ELx_EC_MASK | ESR_ELx_IL |
				ESR_ELx_CM | ESR_ELx_WNR;
			esr |= ESR_ELx_FSC_FAULT;
			अवरोध;
		हाल ESR_ELx_EC_IABT_LOW:
			/*
			 * Claim a level 0 translation fault.
			 * All other bits are architecturally RES0 क्रम faults
			 * reported with that DFSC value, so we clear them.
			 */
			esr &= ESR_ELx_EC_MASK | ESR_ELx_IL;
			esr |= ESR_ELx_FSC_FAULT;
			अवरोध;
		शेष:
			/*
			 * This should never happen (entry.S only brings us
			 * पूर्णांकo this code क्रम insn and data पातs from a lower
			 * exception level). Fail safe by not providing an ESR
			 * context record at all.
			 */
			WARN(1, "ESR 0x%x is not DABT or IABT from EL0\n", esr);
			esr = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	current->thपढ़ो.fault_code = esr;
पूर्ण

अटल व्योम करो_bad_area(अचिन्हित दीर्घ far, अचिन्हित पूर्णांक esr,
			काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ addr = untagged_addr(far);

	/*
	 * If we are in kernel mode at this poपूर्णांक, we have no context to
	 * handle this fault with.
	 */
	अगर (user_mode(regs)) अणु
		स्थिर काष्ठा fault_info *inf = esr_to_fault_info(esr);

		set_thपढ़ो_esr(addr, esr);
		arm64_क्रमce_sig_fault(inf->sig, inf->code, far, inf->name);
	पूर्ण अन्यथा अणु
		__करो_kernel_fault(addr, esr, regs);
	पूर्ण
पूर्ण

#घोषणा VM_FAULT_BADMAP		0x010000
#घोषणा VM_FAULT_BADACCESS	0x020000

अटल vm_fault_t __करो_page_fault(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				  अचिन्हित पूर्णांक mm_flags, अचिन्हित दीर्घ vm_flags,
				  काष्ठा pt_regs *regs)
अणु
	काष्ठा vm_area_काष्ठा *vma = find_vma(mm, addr);

	अगर (unlikely(!vma))
		वापस VM_FAULT_BADMAP;

	/*
	 * Ok, we have a good vm_area क्रम this memory access, so we can handle
	 * it.
	 */
	अगर (unlikely(vma->vm_start > addr)) अणु
		अगर (!(vma->vm_flags & VM_GROWSDOWN))
			वापस VM_FAULT_BADMAP;
		अगर (expand_stack(vma, addr))
			वापस VM_FAULT_BADMAP;
	पूर्ण

	/*
	 * Check that the permissions on the VMA allow क्रम the fault which
	 * occurred.
	 */
	अगर (!(vma->vm_flags & vm_flags))
		वापस VM_FAULT_BADACCESS;
	वापस handle_mm_fault(vma, addr & PAGE_MASK, mm_flags, regs);
पूर्ण

अटल bool is_el0_inकाष्ठाion_पात(अचिन्हित पूर्णांक esr)
अणु
	वापस ESR_ELx_EC(esr) == ESR_ELx_EC_IABT_LOW;
पूर्ण

/*
 * Note: not valid क्रम EL1 DC IVAC, but we never use that such that it
 * should fault. EL0 cannot issue DC IVAC (undef).
 */
अटल bool is_ग_लिखो_पात(अचिन्हित पूर्णांक esr)
अणु
	वापस (esr & ESR_ELx_WNR) && !(esr & ESR_ELx_CM);
पूर्ण

अटल पूर्णांक __kprobes करो_page_fault(अचिन्हित दीर्घ far, अचिन्हित पूर्णांक esr,
				   काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा fault_info *inf;
	काष्ठा mm_काष्ठा *mm = current->mm;
	vm_fault_t fault;
	अचिन्हित दीर्घ vm_flags;
	अचिन्हित पूर्णांक mm_flags = FAULT_FLAG_DEFAULT;
	अचिन्हित दीर्घ addr = untagged_addr(far);

	अगर (kprobe_page_fault(regs, esr))
		वापस 0;

	/*
	 * If we're in an पूर्णांकerrupt or have no user context, we must not take
	 * the fault.
	 */
	अगर (faulthandler_disabled() || !mm)
		जाओ no_context;

	अगर (user_mode(regs))
		mm_flags |= FAULT_FLAG_USER;

	/*
	 * vm_flags tells us what bits we must have in vma->vm_flags
	 * क्रम the fault to be benign, __करो_page_fault() would check
	 * vma->vm_flags & vm_flags and वापसs an error अगर the
	 * पूर्णांकersection is empty
	 */
	अगर (is_el0_inकाष्ठाion_पात(esr)) अणु
		/* It was exec fault */
		vm_flags = VM_EXEC;
		mm_flags |= FAULT_FLAG_INSTRUCTION;
	पूर्ण अन्यथा अगर (is_ग_लिखो_पात(esr)) अणु
		/* It was ग_लिखो fault */
		vm_flags = VM_WRITE;
		mm_flags |= FAULT_FLAG_WRITE;
	पूर्ण अन्यथा अणु
		/* It was पढ़ो fault */
		vm_flags = VM_READ;
		/* Write implies पढ़ो */
		vm_flags |= VM_WRITE;
		/* If EPAN is असलent then exec implies पढ़ो */
		अगर (!cpus_have_स्थिर_cap(ARM64_HAS_EPAN))
			vm_flags |= VM_EXEC;
	पूर्ण

	अगर (is_ttbr0_addr(addr) && is_el1_permission_fault(addr, esr, regs)) अणु
		अगर (is_el1_inकाष्ठाion_पात(esr))
			die_kernel_fault("execution of user memory",
					 addr, esr, regs);

		अगर (!search_exception_tables(regs->pc))
			die_kernel_fault("access to user memory outside uaccess routines",
					 addr, esr, regs);
	पूर्ण

	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, addr);

	/*
	 * As per x86, we may deadlock here. However, since the kernel only
	 * validly references user space from well defined areas of the code,
	 * we can bug out early अगर this is from code which shouldn't.
	 */
	अगर (!mmap_पढ़ो_trylock(mm)) अणु
		अगर (!user_mode(regs) && !search_exception_tables(regs->pc))
			जाओ no_context;
retry:
		mmap_पढ़ो_lock(mm);
	पूर्ण अन्यथा अणु
		/*
		 * The above mmap_पढ़ो_trylock() might have succeeded in which
		 * हाल, we'll have missed the might_sleep() from करोwn_पढ़ो().
		 */
		might_sleep();
#अगर_घोषित CONFIG_DEBUG_VM
		अगर (!user_mode(regs) && !search_exception_tables(regs->pc)) अणु
			mmap_पढ़ो_unlock(mm);
			जाओ no_context;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	fault = __करो_page_fault(mm, addr, mm_flags, vm_flags, regs);

	/* Quick path to respond to संकेतs */
	अगर (fault_संकेत_pending(fault, regs)) अणु
		अगर (!user_mode(regs))
			जाओ no_context;
		वापस 0;
	पूर्ण

	अगर (fault & VM_FAULT_RETRY) अणु
		अगर (mm_flags & FAULT_FLAG_ALLOW_RETRY) अणु
			mm_flags |= FAULT_FLAG_TRIED;
			जाओ retry;
		पूर्ण
	पूर्ण
	mmap_पढ़ो_unlock(mm);

	/*
	 * Handle the "normal" (no error) हाल first.
	 */
	अगर (likely(!(fault & (VM_FAULT_ERROR | VM_FAULT_BADMAP |
			      VM_FAULT_BADACCESS))))
		वापस 0;

	/*
	 * If we are in kernel mode at this poपूर्णांक, we have no context to
	 * handle this fault with.
	 */
	अगर (!user_mode(regs))
		जाओ no_context;

	अगर (fault & VM_FAULT_OOM) अणु
		/*
		 * We ran out of memory, call the OOM समाप्तer, and वापस to
		 * userspace (which will retry the fault, or समाप्त us अगर we got
		 * oom-समाप्तed).
		 */
		pagefault_out_of_memory();
		वापस 0;
	पूर्ण

	inf = esr_to_fault_info(esr);
	set_thपढ़ो_esr(addr, esr);
	अगर (fault & VM_FAULT_SIGBUS) अणु
		/*
		 * We had some memory, but were unable to successfully fix up
		 * this page fault.
		 */
		arm64_क्रमce_sig_fault(SIGBUS, BUS_ADRERR, far, inf->name);
	पूर्ण अन्यथा अगर (fault & (VM_FAULT_HWPOISON_LARGE | VM_FAULT_HWPOISON)) अणु
		अचिन्हित पूर्णांक lsb;

		lsb = PAGE_SHIFT;
		अगर (fault & VM_FAULT_HWPOISON_LARGE)
			lsb = hstate_index_to_shअगरt(VM_FAULT_GET_HINDEX(fault));

		arm64_क्रमce_sig_mceerr(BUS_MCEERR_AR, far, lsb, inf->name);
	पूर्ण अन्यथा अणु
		/*
		 * Something tried to access memory that isn't in our memory
		 * map.
		 */
		arm64_क्रमce_sig_fault(संक_अंश,
				      fault == VM_FAULT_BADACCESS ? SEGV_ACCERR : SEGV_MAPERR,
				      far, inf->name);
	पूर्ण

	वापस 0;

no_context:
	__करो_kernel_fault(addr, esr, regs);
	वापस 0;
पूर्ण

अटल पूर्णांक __kprobes करो_translation_fault(अचिन्हित दीर्घ far,
					  अचिन्हित पूर्णांक esr,
					  काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ addr = untagged_addr(far);

	अगर (is_ttbr0_addr(addr))
		वापस करो_page_fault(far, esr, regs);

	करो_bad_area(far, esr, regs);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_alignment_fault(अचिन्हित दीर्घ far, अचिन्हित पूर्णांक esr,
			      काष्ठा pt_regs *regs)
अणु
	करो_bad_area(far, esr, regs);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_bad(अचिन्हित दीर्घ far, अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	वापस 1; /* "fault" */
पूर्ण

अटल पूर्णांक करो_sea(अचिन्हित दीर्घ far, अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा fault_info *inf;
	अचिन्हित दीर्घ siaddr;

	inf = esr_to_fault_info(esr);

	अगर (user_mode(regs) && apei_claim_sea(regs) == 0) अणु
		/*
		 * APEI claimed this as a firmware-first notअगरication.
		 * Some processing deferred to task_work beक्रमe ret_to_user().
		 */
		वापस 0;
	पूर्ण

	अगर (esr & ESR_ELx_FnV) अणु
		siaddr = 0;
	पूर्ण अन्यथा अणु
		/*
		 * The architecture specअगरies that the tag bits of FAR_EL1 are
		 * UNKNOWN क्रम synchronous बाह्यal पातs. Mask them out now
		 * so that userspace करोesn't see them.
		 */
		siaddr  = untagged_addr(far);
	पूर्ण
	arm64_notअगरy_die(inf->name, regs, inf->sig, inf->code, siaddr, esr);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_tag_check_fault(अचिन्हित दीर्घ far, अचिन्हित पूर्णांक esr,
			      काष्ठा pt_regs *regs)
अणु
	/*
	 * The architecture specअगरies that bits 63:60 of FAR_EL1 are UNKNOWN
	 * क्रम tag check faults. Set them to corresponding bits in the untagged
	 * address.
	 */
	far = (__untagged_addr(far) & ~MTE_TAG_MASK) | (far & MTE_TAG_MASK);
	करो_bad_area(far, esr, regs);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fault_info fault_info[] = अणु
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"ttbr address size fault"	पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"level 1 address size fault"	पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"level 2 address size fault"	पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"level 3 address size fault"	पूर्ण,
	अणु करो_translation_fault,	संक_अंश, SEGV_MAPERR,	"level 0 translation fault"	पूर्ण,
	अणु करो_translation_fault,	संक_अंश, SEGV_MAPERR,	"level 1 translation fault"	पूर्ण,
	अणु करो_translation_fault,	संक_अंश, SEGV_MAPERR,	"level 2 translation fault"	पूर्ण,
	अणु करो_translation_fault,	संक_अंश, SEGV_MAPERR,	"level 3 translation fault"	पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 8"			पूर्ण,
	अणु करो_page_fault,	संक_अंश, SEGV_ACCERR,	"level 1 access flag fault"	पूर्ण,
	अणु करो_page_fault,	संक_अंश, SEGV_ACCERR,	"level 2 access flag fault"	पूर्ण,
	अणु करो_page_fault,	संक_अंश, SEGV_ACCERR,	"level 3 access flag fault"	पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 12"			पूर्ण,
	अणु करो_page_fault,	संक_अंश, SEGV_ACCERR,	"level 1 permission fault"	पूर्ण,
	अणु करो_page_fault,	संक_अंश, SEGV_ACCERR,	"level 2 permission fault"	पूर्ण,
	अणु करो_page_fault,	संक_अंश, SEGV_ACCERR,	"level 3 permission fault"	पूर्ण,
	अणु करो_sea,		SIGBUS,  BUS_OBJERR,	"synchronous external abort"	पूर्ण,
	अणु करो_tag_check_fault,	संक_अंश, SEGV_MTESERR,	"synchronous tag check fault"	पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 18"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 19"			पूर्ण,
	अणु करो_sea,		SIGKILL, SI_KERNEL,	"level 0 (translation table walk)"	पूर्ण,
	अणु करो_sea,		SIGKILL, SI_KERNEL,	"level 1 (translation table walk)"	पूर्ण,
	अणु करो_sea,		SIGKILL, SI_KERNEL,	"level 2 (translation table walk)"	पूर्ण,
	अणु करो_sea,		SIGKILL, SI_KERNEL,	"level 3 (translation table walk)"	पूर्ण,
	अणु करो_sea,		SIGBUS,  BUS_OBJERR,	"synchronous parity or ECC error" पूर्ण,	// Reserved when RAS is implemented
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 25"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 26"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 27"			पूर्ण,
	अणु करो_sea,		SIGKILL, SI_KERNEL,	"level 0 synchronous parity error (translation table walk)"	पूर्ण,	// Reserved when RAS is implemented
	अणु करो_sea,		SIGKILL, SI_KERNEL,	"level 1 synchronous parity error (translation table walk)"	पूर्ण,	// Reserved when RAS is implemented
	अणु करो_sea,		SIGKILL, SI_KERNEL,	"level 2 synchronous parity error (translation table walk)"	पूर्ण,	// Reserved when RAS is implemented
	अणु करो_sea,		SIGKILL, SI_KERNEL,	"level 3 synchronous parity error (translation table walk)"	पूर्ण,	// Reserved when RAS is implemented
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 32"			पूर्ण,
	अणु करो_alignment_fault,	SIGBUS,  BUS_ADRALN,	"alignment fault"		पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 34"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 35"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 36"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 37"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 38"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 39"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 40"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 41"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 42"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 43"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 44"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 45"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 46"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 47"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"TLB conflict abort"		पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"Unsupported atomic hardware update fault"	पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 50"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 51"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"implementation fault (lockdown abort)" पूर्ण,
	अणु करो_bad,		SIGBUS,  BUS_OBJERR,	"implementation fault (unsupported exclusive)" पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 54"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 55"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 56"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 57"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 58" 			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 59"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 60"			पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"section domain fault"		पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"page domain fault"		पूर्ण,
	अणु करो_bad,		SIGKILL, SI_KERNEL,	"unknown 63"			पूर्ण,
पूर्ण;

व्योम करो_mem_पात(अचिन्हित दीर्घ far, अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा fault_info *inf = esr_to_fault_info(esr);
	अचिन्हित दीर्घ addr = untagged_addr(far);

	अगर (!inf->fn(far, esr, regs))
		वापस;

	अगर (!user_mode(regs)) अणु
		pr_alert("Unhandled fault at 0x%016lx\n", addr);
		mem_पात_decode(esr);
		show_pte(addr);
	पूर्ण

	/*
	 * At this poपूर्णांक we have an unrecognized fault type whose tag bits may
	 * have been defined as UNKNOWN. Thereक्रमe we only expose the untagged
	 * address to the संकेत handler.
	 */
	arm64_notअगरy_die(inf->name, regs, inf->sig, inf->code, addr, esr);
पूर्ण
NOKPROBE_SYMBOL(करो_mem_पात);

व्योम करो_el0_irq_bp_hardening(व्योम)
अणु
	/* PC has alपढ़ोy been checked in entry.S */
	arm64_apply_bp_hardening();
पूर्ण
NOKPROBE_SYMBOL(करो_el0_irq_bp_hardening);

व्योम करो_sp_pc_पात(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	arm64_notअगरy_die("SP/PC alignment exception", regs, SIGBUS, BUS_ADRALN,
			 addr, esr);
पूर्ण
NOKPROBE_SYMBOL(करो_sp_pc_पात);

पूर्णांक __init early_brk64(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक esr,
		       काष्ठा pt_regs *regs);

/*
 * __refdata because early_brk64 is __init, but the reference to it is
 * clobbered at arch_initcall समय.
 * See traps.c and debug-monitors.c:debug_traps_init().
 */
अटल काष्ठा fault_info __refdata debug_fault_info[] = अणु
	अणु करो_bad,	SIGTRAP,	TRAP_HWBKPT,	"hardware breakpoint"	पूर्ण,
	अणु करो_bad,	SIGTRAP,	TRAP_HWBKPT,	"hardware single-step"	पूर्ण,
	अणु करो_bad,	SIGTRAP,	TRAP_HWBKPT,	"hardware watchpoint"	पूर्ण,
	अणु करो_bad,	SIGKILL,	SI_KERNEL,	"unknown 3"		पूर्ण,
	अणु करो_bad,	SIGTRAP,	TRAP_BRKPT,	"aarch32 BKPT"		पूर्ण,
	अणु करो_bad,	SIGKILL,	SI_KERNEL,	"aarch32 vector catch"	पूर्ण,
	अणु early_brk64,	SIGTRAP,	TRAP_BRKPT,	"aarch64 BRK"		पूर्ण,
	अणु करो_bad,	SIGKILL,	SI_KERNEL,	"unknown 7"		पूर्ण,
पूर्ण;

व्योम __init hook_debug_fault_code(पूर्णांक nr,
				  पूर्णांक (*fn)(अचिन्हित दीर्घ, अचिन्हित पूर्णांक, काष्ठा pt_regs *),
				  पूर्णांक sig, पूर्णांक code, स्थिर अक्षर *name)
अणु
	BUG_ON(nr < 0 || nr >= ARRAY_SIZE(debug_fault_info));

	debug_fault_info[nr].fn		= fn;
	debug_fault_info[nr].sig	= sig;
	debug_fault_info[nr].code	= code;
	debug_fault_info[nr].name	= name;
पूर्ण

/*
 * In debug exception context, we explicitly disable preemption despite
 * having पूर्णांकerrupts disabled.
 * This serves two purposes: it makes it much less likely that we would
 * accidentally schedule in exception context and it will क्रमce a warning
 * अगर we somehow manage to schedule by accident.
 */
अटल व्योम debug_exception_enter(काष्ठा pt_regs *regs)
अणु
	preempt_disable();

	/* This code is a bit fragile.  Test it. */
	RCU_LOCKDEP_WARN(!rcu_is_watching(), "exception_enter didn't work");
पूर्ण
NOKPROBE_SYMBOL(debug_exception_enter);

अटल व्योम debug_exception_निकास(काष्ठा pt_regs *regs)
अणु
	preempt_enable_no_resched();
पूर्ण
NOKPROBE_SYMBOL(debug_exception_निकास);

व्योम करो_debug_exception(अचिन्हित दीर्घ addr_अगर_watchpoपूर्णांक, अचिन्हित पूर्णांक esr,
			काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा fault_info *inf = esr_to_debug_fault_info(esr);
	अचिन्हित दीर्घ pc = inकाष्ठाion_poपूर्णांकer(regs);

	debug_exception_enter(regs);

	अगर (user_mode(regs) && !is_ttbr0_addr(pc))
		arm64_apply_bp_hardening();

	अगर (inf->fn(addr_अगर_watchpoपूर्णांक, esr, regs)) अणु
		arm64_notअगरy_die(inf->name, regs, inf->sig, inf->code, pc, esr);
	पूर्ण

	debug_exception_निकास(regs);
पूर्ण
NOKPROBE_SYMBOL(करो_debug_exception);
