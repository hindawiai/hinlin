<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*  Paraभवization पूर्णांकerfaces
    Copyright (C) 2006 Rusty Russell IBM Corporation


    2007 - x86_64 support added by Glauber de Oliveira Costa, Red Hat Inc
*/

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/efi.h>
#समावेश <linux/bcd.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/kprobes.h>
#समावेश <linux/pgtable.h>
#समावेश <linux/अटल_call.h>

#समावेश <यंत्र/bug.h>
#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/special_insns.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/io_biपंचांगap.h>

/*
 * nop stub, which must not clobber anything *including the stack* to
 * aव्योम confusing the entry prologues.
 */
बाह्य व्योम _paravirt_nop(व्योम);
यंत्र (".pushsection .entry.text, \"ax\"\n"
     ".global _paravirt_nop\n"
     "_paravirt_nop:\n\t"
     "ret\n\t"
     ".size _paravirt_nop, . - _paravirt_nop\n\t"
     ".type _paravirt_nop, @function\n\t"
     ".popsection");

व्योम __init शेष_banner(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "Booting paravirtualized kernel on %s\n",
	       pv_info.name);
पूर्ण

/* Undefined inकाष्ठाion क्रम dealing with missing ops poपूर्णांकers. */
अटल व्योम paravirt_BUG(व्योम)
अणु
	BUG();
पूर्ण

काष्ठा branch अणु
	अचिन्हित अक्षर opcode;
	u32 delta;
पूर्ण __attribute__((packed));

अटल अचिन्हित paravirt_patch_call(व्योम *insn_buff, स्थिर व्योम *target,
				    अचिन्हित दीर्घ addr, अचिन्हित len)
अणु
	स्थिर पूर्णांक call_len = 5;
	काष्ठा branch *b = insn_buff;
	अचिन्हित दीर्घ delta = (अचिन्हित दीर्घ)target - (addr+call_len);

	अगर (len < call_len) अणु
		pr_warn("paravirt: Failed to patch indirect CALL at %ps\n", (व्योम *)addr);
		/* Kernel might not be viable अगर patching fails, bail out: */
		BUG_ON(1);
	पूर्ण

	b->opcode = 0xe8; /* call */
	b->delta = delta;
	BUILD_BUG_ON(माप(*b) != call_len);

	वापस call_len;
पूर्ण

#अगर_घोषित CONFIG_PARAVIRT_XXL
/* identity function, which can be अंतरभूतd */
u64 notrace _paravirt_ident_64(u64 x)
अणु
	वापस x;
पूर्ण
#पूर्ण_अगर

DEFINE_STATIC_KEY_TRUE(virt_spin_lock_key);

व्योम __init native_pv_lock_init(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_HYPERVISOR))
		अटल_branch_disable(&virt_spin_lock_key);
पूर्ण

अचिन्हित पूर्णांक paravirt_patch(u8 type, व्योम *insn_buff, अचिन्हित दीर्घ addr,
			    अचिन्हित पूर्णांक len)
अणु
	/*
	 * Neat trick to map patch type back to the call within the
	 * corresponding काष्ठाure.
	 */
	व्योम *opfunc = *((व्योम **)&pv_ops + type);
	अचिन्हित ret;

	अगर (opfunc == शून्य)
		/* If there's no function, patch it with paravirt_BUG() */
		ret = paravirt_patch_call(insn_buff, paravirt_BUG, addr, len);
	अन्यथा अगर (opfunc == _paravirt_nop)
		ret = 0;
	अन्यथा
		/* Otherwise call the function. */
		ret = paravirt_patch_call(insn_buff, opfunc, addr, len);

	वापस ret;
पूर्ण

काष्ठा अटल_key paravirt_steal_enabled;
काष्ठा अटल_key paravirt_steal_rq_enabled;

अटल u64 native_steal_घड़ी(पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण

DEFINE_STATIC_CALL(pv_steal_घड़ी, native_steal_घड़ी);
DEFINE_STATIC_CALL(pv_sched_घड़ी, native_sched_घड़ी);

व्योम paravirt_set_sched_घड़ी(u64 (*func)(व्योम))
अणु
	अटल_call_update(pv_sched_घड़ी, func);
पूर्ण

/* These are in entry.S */
बाह्य व्योम native_iret(व्योम);

अटल काष्ठा resource reserve_ioports = अणु
	.start = 0,
	.end = IO_SPACE_LIMIT,
	.name = "paravirt-ioport",
	.flags = IORESOURCE_IO | IORESOURCE_BUSY,
पूर्ण;

/*
 * Reserve the whole legacy IO space to prevent any legacy drivers
 * from wasting समय probing क्रम their hardware.  This is a fairly
 * brute-क्रमce approach to disabling all non-भव drivers.
 *
 * Note that this must be called very early to have any effect.
 */
पूर्णांक paravirt_disable_iospace(व्योम)
अणु
	वापस request_resource(&ioport_resource, &reserve_ioports);
पूर्ण

अटल DEFINE_PER_CPU(क्रमागत paravirt_lazy_mode, paravirt_lazy_mode) = PARAVIRT_LAZY_NONE;

अटल अंतरभूत व्योम enter_lazy(क्रमागत paravirt_lazy_mode mode)
अणु
	BUG_ON(this_cpu_पढ़ो(paravirt_lazy_mode) != PARAVIRT_LAZY_NONE);

	this_cpu_ग_लिखो(paravirt_lazy_mode, mode);
पूर्ण

अटल व्योम leave_lazy(क्रमागत paravirt_lazy_mode mode)
अणु
	BUG_ON(this_cpu_पढ़ो(paravirt_lazy_mode) != mode);

	this_cpu_ग_लिखो(paravirt_lazy_mode, PARAVIRT_LAZY_NONE);
पूर्ण

व्योम paravirt_enter_lazy_mmu(व्योम)
अणु
	enter_lazy(PARAVIRT_LAZY_MMU);
पूर्ण

व्योम paravirt_leave_lazy_mmu(व्योम)
अणु
	leave_lazy(PARAVIRT_LAZY_MMU);
पूर्ण

व्योम paravirt_flush_lazy_mmu(व्योम)
अणु
	preempt_disable();

	अगर (paravirt_get_lazy_mode() == PARAVIRT_LAZY_MMU) अणु
		arch_leave_lazy_mmu_mode();
		arch_enter_lazy_mmu_mode();
	पूर्ण

	preempt_enable();
पूर्ण

#अगर_घोषित CONFIG_PARAVIRT_XXL
व्योम paravirt_start_context_चयन(काष्ठा task_काष्ठा *prev)
अणु
	BUG_ON(preemptible());

	अगर (this_cpu_पढ़ो(paravirt_lazy_mode) == PARAVIRT_LAZY_MMU) अणु
		arch_leave_lazy_mmu_mode();
		set_ti_thपढ़ो_flag(task_thपढ़ो_info(prev), TIF_LAZY_MMU_UPDATES);
	पूर्ण
	enter_lazy(PARAVIRT_LAZY_CPU);
पूर्ण

व्योम paravirt_end_context_चयन(काष्ठा task_काष्ठा *next)
अणु
	BUG_ON(preemptible());

	leave_lazy(PARAVIRT_LAZY_CPU);

	अगर (test_and_clear_ti_thपढ़ो_flag(task_thपढ़ो_info(next), TIF_LAZY_MMU_UPDATES))
		arch_enter_lazy_mmu_mode();
पूर्ण
#पूर्ण_अगर

क्रमागत paravirt_lazy_mode paravirt_get_lazy_mode(व्योम)
अणु
	अगर (in_पूर्णांकerrupt())
		वापस PARAVIRT_LAZY_NONE;

	वापस this_cpu_पढ़ो(paravirt_lazy_mode);
पूर्ण

काष्ठा pv_info pv_info = अणु
	.name = "bare hardware",
#अगर_घोषित CONFIG_PARAVIRT_XXL
	.extra_user_64bit_cs = __USER_CS,
#पूर्ण_अगर
पूर्ण;

/* 64-bit pagetable entries */
#घोषणा PTE_IDENT	__PV_IS_CALLEE_SAVE(_paravirt_ident_64)

काष्ठा paravirt_patch_ढाँचा pv_ops = अणु
	/* Cpu ops. */
	.cpu.io_delay		= native_io_delay,

#अगर_घोषित CONFIG_PARAVIRT_XXL
	.cpu.cpuid		= native_cpuid,
	.cpu.get_debugreg	= native_get_debugreg,
	.cpu.set_debugreg	= native_set_debugreg,
	.cpu.पढ़ो_cr0		= native_पढ़ो_cr0,
	.cpu.ग_लिखो_cr0		= native_ग_लिखो_cr0,
	.cpu.ग_लिखो_cr4		= native_ग_लिखो_cr4,
	.cpu.wbinvd		= native_wbinvd,
	.cpu.पढ़ो_msr		= native_पढ़ो_msr,
	.cpu.ग_लिखो_msr		= native_ग_लिखो_msr,
	.cpu.पढ़ो_msr_safe	= native_पढ़ो_msr_safe,
	.cpu.ग_लिखो_msr_safe	= native_ग_लिखो_msr_safe,
	.cpu.पढ़ो_pmc		= native_पढ़ो_pmc,
	.cpu.load_tr_desc	= native_load_tr_desc,
	.cpu.set_ldt		= native_set_ldt,
	.cpu.load_gdt		= native_load_gdt,
	.cpu.load_idt		= native_load_idt,
	.cpu.store_tr		= native_store_tr,
	.cpu.load_tls		= native_load_tls,
	.cpu.load_gs_index	= native_load_gs_index,
	.cpu.ग_लिखो_ldt_entry	= native_ग_लिखो_ldt_entry,
	.cpu.ग_लिखो_gdt_entry	= native_ग_लिखो_gdt_entry,
	.cpu.ग_लिखो_idt_entry	= native_ग_लिखो_idt_entry,

	.cpu.alloc_ldt		= paravirt_nop,
	.cpu.मुक्त_ldt		= paravirt_nop,

	.cpu.load_sp0		= native_load_sp0,

#अगर_घोषित CONFIG_X86_IOPL_IOPERM
	.cpu.invalidate_io_biपंचांगap	= native_tss_invalidate_io_biपंचांगap,
	.cpu.update_io_biपंचांगap		= native_tss_update_io_biपंचांगap,
#पूर्ण_अगर

	.cpu.start_context_चयन	= paravirt_nop,
	.cpu.end_context_चयन		= paravirt_nop,

	/* Irq ops. */
	.irq.save_fl		= __PV_IS_CALLEE_SAVE(native_save_fl),
	.irq.irq_disable	= __PV_IS_CALLEE_SAVE(native_irq_disable),
	.irq.irq_enable		= __PV_IS_CALLEE_SAVE(native_irq_enable),
	.irq.safe_halt		= native_safe_halt,
	.irq.halt		= native_halt,
#पूर्ण_अगर /* CONFIG_PARAVIRT_XXL */

	/* Mmu ops. */
	.mmu.flush_tlb_user	= native_flush_tlb_local,
	.mmu.flush_tlb_kernel	= native_flush_tlb_global,
	.mmu.flush_tlb_one_user	= native_flush_tlb_one_user,
	.mmu.flush_tlb_multi	= native_flush_tlb_multi,
	.mmu.tlb_हटाओ_table	=
			(व्योम (*)(काष्ठा mmu_gather *, व्योम *))tlb_हटाओ_page,

	.mmu.निकास_mmap		= paravirt_nop,

#अगर_घोषित CONFIG_PARAVIRT_XXL
	.mmu.पढ़ो_cr2		= __PV_IS_CALLEE_SAVE(native_पढ़ो_cr2),
	.mmu.ग_लिखो_cr2		= native_ग_लिखो_cr2,
	.mmu.पढ़ो_cr3		= __native_पढ़ो_cr3,
	.mmu.ग_लिखो_cr3		= native_ग_लिखो_cr3,

	.mmu.pgd_alloc		= __paravirt_pgd_alloc,
	.mmu.pgd_मुक्त		= paravirt_nop,

	.mmu.alloc_pte		= paravirt_nop,
	.mmu.alloc_pmd		= paravirt_nop,
	.mmu.alloc_pud		= paravirt_nop,
	.mmu.alloc_p4d		= paravirt_nop,
	.mmu.release_pte	= paravirt_nop,
	.mmu.release_pmd	= paravirt_nop,
	.mmu.release_pud	= paravirt_nop,
	.mmu.release_p4d	= paravirt_nop,

	.mmu.set_pte		= native_set_pte,
	.mmu.set_pmd		= native_set_pmd,

	.mmu.ptep_modअगरy_prot_start	= __ptep_modअगरy_prot_start,
	.mmu.ptep_modअगरy_prot_commit	= __ptep_modअगरy_prot_commit,

	.mmu.set_pud		= native_set_pud,

	.mmu.pmd_val		= PTE_IDENT,
	.mmu.make_pmd		= PTE_IDENT,

	.mmu.pud_val		= PTE_IDENT,
	.mmu.make_pud		= PTE_IDENT,

	.mmu.set_p4d		= native_set_p4d,

#अगर CONFIG_PGTABLE_LEVELS >= 5
	.mmu.p4d_val		= PTE_IDENT,
	.mmu.make_p4d		= PTE_IDENT,

	.mmu.set_pgd		= native_set_pgd,
#पूर्ण_अगर /* CONFIG_PGTABLE_LEVELS >= 5 */

	.mmu.pte_val		= PTE_IDENT,
	.mmu.pgd_val		= PTE_IDENT,

	.mmu.make_pte		= PTE_IDENT,
	.mmu.make_pgd		= PTE_IDENT,

	.mmu.dup_mmap		= paravirt_nop,
	.mmu.activate_mm	= paravirt_nop,

	.mmu.lazy_mode = अणु
		.enter		= paravirt_nop,
		.leave		= paravirt_nop,
		.flush		= paravirt_nop,
	पूर्ण,

	.mmu.set_fixmap		= native_set_fixmap,
#पूर्ण_अगर /* CONFIG_PARAVIRT_XXL */

#अगर defined(CONFIG_PARAVIRT_SPINLOCKS)
	/* Lock ops. */
#अगर_घोषित CONFIG_SMP
	.lock.queued_spin_lock_slowpath	= native_queued_spin_lock_slowpath,
	.lock.queued_spin_unlock	=
				PV_CALLEE_SAVE(__native_queued_spin_unlock),
	.lock.रुको			= paravirt_nop,
	.lock.kick			= paravirt_nop,
	.lock.vcpu_is_preempted		=
				PV_CALLEE_SAVE(__native_vcpu_is_preempted),
#पूर्ण_अगर /* SMP */
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_PARAVIRT_XXL
/* At this poपूर्णांक, native_get/set_debugreg has real function entries */
NOKPROBE_SYMBOL(native_get_debugreg);
NOKPROBE_SYMBOL(native_set_debugreg);
NOKPROBE_SYMBOL(native_load_idt);

व्योम (*paravirt_iret)(व्योम) = native_iret;
#पूर्ण_अगर

EXPORT_SYMBOL(pv_ops);
EXPORT_SYMBOL_GPL(pv_info);
