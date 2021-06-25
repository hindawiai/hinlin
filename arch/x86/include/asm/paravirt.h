<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PARAVIRT_H
#घोषणा _ASM_X86_PARAVIRT_H
/* Various inकाष्ठाions on x86 need to be replaced क्रम
 * para-भवization: those hooks are defined here. */

#अगर_घोषित CONFIG_PARAVIRT
#समावेश <यंत्र/pgtable_types.h>
#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/nospec-branch.h>

#समावेश <यंत्र/paravirt_types.h>

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/bug.h>
#समावेश <linux/types.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/अटल_call_types.h>
#समावेश <यंत्र/frame.h>

u64 dummy_steal_घड़ी(पूर्णांक cpu);
u64 dummy_sched_घड़ी(व्योम);

DECLARE_STATIC_CALL(pv_steal_घड़ी, dummy_steal_घड़ी);
DECLARE_STATIC_CALL(pv_sched_घड़ी, dummy_sched_घड़ी);

व्योम paravirt_set_sched_घड़ी(u64 (*func)(व्योम));

अटल अंतरभूत u64 paravirt_sched_घड़ी(व्योम)
अणु
	वापस अटल_call(pv_sched_घड़ी)();
पूर्ण

काष्ठा अटल_key;
बाह्य काष्ठा अटल_key paravirt_steal_enabled;
बाह्य काष्ठा अटल_key paravirt_steal_rq_enabled;

__visible व्योम __native_queued_spin_unlock(काष्ठा qspinlock *lock);
bool pv_is_native_spin_unlock(व्योम);
__visible bool __native_vcpu_is_preempted(दीर्घ cpu);
bool pv_is_native_vcpu_is_preempted(व्योम);

अटल अंतरभूत u64 paravirt_steal_घड़ी(पूर्णांक cpu)
अणु
	वापस अटल_call(pv_steal_घड़ी)(cpu);
पूर्ण

#अगर_घोषित CONFIG_PARAVIRT_SPINLOCKS
व्योम __init paravirt_set_cap(व्योम);
#पूर्ण_अगर

/* The paraभवized I/O functions */
अटल अंतरभूत व्योम slow_करोwn_io(व्योम)
अणु
	pv_ops.cpu.io_delay();
#अगर_घोषित REALLY_SLOW_IO
	pv_ops.cpu.io_delay();
	pv_ops.cpu.io_delay();
	pv_ops.cpu.io_delay();
#पूर्ण_अगर
पूर्ण

व्योम native_flush_tlb_local(व्योम);
व्योम native_flush_tlb_global(व्योम);
व्योम native_flush_tlb_one_user(अचिन्हित दीर्घ addr);
व्योम native_flush_tlb_multi(स्थिर काष्ठा cpumask *cpumask,
			     स्थिर काष्ठा flush_tlb_info *info);

अटल अंतरभूत व्योम __flush_tlb_local(व्योम)
अणु
	PVOP_VCALL0(mmu.flush_tlb_user);
पूर्ण

अटल अंतरभूत व्योम __flush_tlb_global(व्योम)
अणु
	PVOP_VCALL0(mmu.flush_tlb_kernel);
पूर्ण

अटल अंतरभूत व्योम __flush_tlb_one_user(अचिन्हित दीर्घ addr)
अणु
	PVOP_VCALL1(mmu.flush_tlb_one_user, addr);
पूर्ण

अटल अंतरभूत व्योम __flush_tlb_multi(स्थिर काष्ठा cpumask *cpumask,
				      स्थिर काष्ठा flush_tlb_info *info)
अणु
	PVOP_VCALL2(mmu.flush_tlb_multi, cpumask, info);
पूर्ण

अटल अंतरभूत व्योम paravirt_tlb_हटाओ_table(काष्ठा mmu_gather *tlb, व्योम *table)
अणु
	PVOP_VCALL2(mmu.tlb_हटाओ_table, tlb, table);
पूर्ण

अटल अंतरभूत व्योम paravirt_arch_निकास_mmap(काष्ठा mm_काष्ठा *mm)
अणु
	PVOP_VCALL1(mmu.निकास_mmap, mm);
पूर्ण

#अगर_घोषित CONFIG_PARAVIRT_XXL
अटल अंतरभूत व्योम load_sp0(अचिन्हित दीर्घ sp0)
अणु
	PVOP_VCALL1(cpu.load_sp0, sp0);
पूर्ण

/* The paraभवized CPUID inकाष्ठाion. */
अटल अंतरभूत व्योम __cpuid(अचिन्हित पूर्णांक *eax, अचिन्हित पूर्णांक *ebx,
			   अचिन्हित पूर्णांक *ecx, अचिन्हित पूर्णांक *edx)
अणु
	PVOP_VCALL4(cpu.cpuid, eax, ebx, ecx, edx);
पूर्ण

/*
 * These special macros can be used to get or set a debugging रेजिस्टर
 */
अटल अंतरभूत अचिन्हित दीर्घ paravirt_get_debugreg(पूर्णांक reg)
अणु
	वापस PVOP_CALL1(अचिन्हित दीर्घ, cpu.get_debugreg, reg);
पूर्ण
#घोषणा get_debugreg(var, reg) var = paravirt_get_debugreg(reg)
अटल अंतरभूत व्योम set_debugreg(अचिन्हित दीर्घ val, पूर्णांक reg)
अणु
	PVOP_VCALL2(cpu.set_debugreg, reg, val);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_cr0(व्योम)
अणु
	वापस PVOP_CALL0(अचिन्हित दीर्घ, cpu.पढ़ो_cr0);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_cr0(अचिन्हित दीर्घ x)
अणु
	PVOP_VCALL1(cpu.ग_लिखो_cr0, x);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_cr2(व्योम)
अणु
	वापस PVOP_ALT_CALLEE0(अचिन्हित दीर्घ, mmu.पढ़ो_cr2,
				"mov %%cr2, %%rax;",
				ALT_NOT(X86_FEATURE_XENPV));
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_cr2(अचिन्हित दीर्घ x)
अणु
	PVOP_VCALL1(mmu.ग_लिखो_cr2, x);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __पढ़ो_cr3(व्योम)
अणु
	वापस PVOP_ALT_CALL0(अचिन्हित दीर्घ, mmu.पढ़ो_cr3,
			      "mov %%cr3, %%rax;", ALT_NOT(X86_FEATURE_XENPV));
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_cr3(अचिन्हित दीर्घ x)
अणु
	PVOP_ALT_VCALL1(mmu.ग_लिखो_cr3, x,
			"mov %%rdi, %%cr3", ALT_NOT(X86_FEATURE_XENPV));
पूर्ण

अटल अंतरभूत व्योम __ग_लिखो_cr4(अचिन्हित दीर्घ x)
अणु
	PVOP_VCALL1(cpu.ग_लिखो_cr4, x);
पूर्ण

अटल अंतरभूत व्योम arch_safe_halt(व्योम)
अणु
	PVOP_VCALL0(irq.safe_halt);
पूर्ण

अटल अंतरभूत व्योम halt(व्योम)
अणु
	PVOP_VCALL0(irq.halt);
पूर्ण

अटल अंतरभूत व्योम wbinvd(व्योम)
अणु
	PVOP_ALT_VCALL0(cpu.wbinvd, "wbinvd", ALT_NOT(X86_FEATURE_XENPV));
पूर्ण

अटल अंतरभूत u64 paravirt_पढ़ो_msr(अचिन्हित msr)
अणु
	वापस PVOP_CALL1(u64, cpu.पढ़ो_msr, msr);
पूर्ण

अटल अंतरभूत व्योम paravirt_ग_लिखो_msr(अचिन्हित msr,
				      अचिन्हित low, अचिन्हित high)
अणु
	PVOP_VCALL3(cpu.ग_लिखो_msr, msr, low, high);
पूर्ण

अटल अंतरभूत u64 paravirt_पढ़ो_msr_safe(अचिन्हित msr, पूर्णांक *err)
अणु
	वापस PVOP_CALL2(u64, cpu.पढ़ो_msr_safe, msr, err);
पूर्ण

अटल अंतरभूत पूर्णांक paravirt_ग_लिखो_msr_safe(अचिन्हित msr,
					  अचिन्हित low, अचिन्हित high)
अणु
	वापस PVOP_CALL3(पूर्णांक, cpu.ग_लिखो_msr_safe, msr, low, high);
पूर्ण

#घोषणा rdmsr(msr, val1, val2)			\
करो अणु						\
	u64 _l = paravirt_पढ़ो_msr(msr);	\
	val1 = (u32)_l;				\
	val2 = _l >> 32;			\
पूर्ण जबतक (0)

#घोषणा wrmsr(msr, val1, val2)			\
करो अणु						\
	paravirt_ग_लिखो_msr(msr, val1, val2);	\
पूर्ण जबतक (0)

#घोषणा rdmsrl(msr, val)			\
करो अणु						\
	val = paravirt_पढ़ो_msr(msr);		\
पूर्ण जबतक (0)

अटल अंतरभूत व्योम wrmsrl(अचिन्हित msr, u64 val)
अणु
	wrmsr(msr, (u32)val, (u32)(val>>32));
पूर्ण

#घोषणा wrmsr_safe(msr, a, b)	paravirt_ग_लिखो_msr_safe(msr, a, b)

/* rdmsr with exception handling */
#घोषणा rdmsr_safe(msr, a, b)				\
(अणु							\
	पूर्णांक _err;					\
	u64 _l = paravirt_पढ़ो_msr_safe(msr, &_err);	\
	(*a) = (u32)_l;					\
	(*b) = _l >> 32;				\
	_err;						\
पूर्ण)

अटल अंतरभूत पूर्णांक rdmsrl_safe(अचिन्हित msr, अचिन्हित दीर्घ दीर्घ *p)
अणु
	पूर्णांक err;

	*p = paravirt_पढ़ो_msr_safe(msr, &err);
	वापस err;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ paravirt_पढ़ो_pmc(पूर्णांक counter)
अणु
	वापस PVOP_CALL1(u64, cpu.पढ़ो_pmc, counter);
पूर्ण

#घोषणा rdpmc(counter, low, high)		\
करो अणु						\
	u64 _l = paravirt_पढ़ो_pmc(counter);	\
	low = (u32)_l;				\
	high = _l >> 32;			\
पूर्ण जबतक (0)

#घोषणा rdpmcl(counter, val) ((val) = paravirt_पढ़ो_pmc(counter))

अटल अंतरभूत व्योम paravirt_alloc_ldt(काष्ठा desc_काष्ठा *ldt, अचिन्हित entries)
अणु
	PVOP_VCALL2(cpu.alloc_ldt, ldt, entries);
पूर्ण

अटल अंतरभूत व्योम paravirt_मुक्त_ldt(काष्ठा desc_काष्ठा *ldt, अचिन्हित entries)
अणु
	PVOP_VCALL2(cpu.मुक्त_ldt, ldt, entries);
पूर्ण

अटल अंतरभूत व्योम load_TR_desc(व्योम)
अणु
	PVOP_VCALL0(cpu.load_tr_desc);
पूर्ण
अटल अंतरभूत व्योम load_gdt(स्थिर काष्ठा desc_ptr *dtr)
अणु
	PVOP_VCALL1(cpu.load_gdt, dtr);
पूर्ण
अटल अंतरभूत व्योम load_idt(स्थिर काष्ठा desc_ptr *dtr)
अणु
	PVOP_VCALL1(cpu.load_idt, dtr);
पूर्ण
अटल अंतरभूत व्योम set_ldt(स्थिर व्योम *addr, अचिन्हित entries)
अणु
	PVOP_VCALL2(cpu.set_ldt, addr, entries);
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ paravirt_store_tr(व्योम)
अणु
	वापस PVOP_CALL0(अचिन्हित दीर्घ, cpu.store_tr);
पूर्ण

#घोषणा store_tr(tr)	((tr) = paravirt_store_tr())
अटल अंतरभूत व्योम load_TLS(काष्ठा thपढ़ो_काष्ठा *t, अचिन्हित cpu)
अणु
	PVOP_VCALL2(cpu.load_tls, t, cpu);
पूर्ण

अटल अंतरभूत व्योम load_gs_index(अचिन्हित पूर्णांक gs)
अणु
	PVOP_VCALL1(cpu.load_gs_index, gs);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_ldt_entry(काष्ठा desc_काष्ठा *dt, पूर्णांक entry,
				   स्थिर व्योम *desc)
अणु
	PVOP_VCALL3(cpu.ग_लिखो_ldt_entry, dt, entry, desc);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_gdt_entry(काष्ठा desc_काष्ठा *dt, पूर्णांक entry,
				   व्योम *desc, पूर्णांक type)
अणु
	PVOP_VCALL4(cpu.ग_लिखो_gdt_entry, dt, entry, desc, type);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_idt_entry(gate_desc *dt, पूर्णांक entry, स्थिर gate_desc *g)
अणु
	PVOP_VCALL3(cpu.ग_लिखो_idt_entry, dt, entry, g);
पूर्ण

#अगर_घोषित CONFIG_X86_IOPL_IOPERM
अटल अंतरभूत व्योम tss_invalidate_io_biपंचांगap(व्योम)
अणु
	PVOP_VCALL0(cpu.invalidate_io_biपंचांगap);
पूर्ण

अटल अंतरभूत व्योम tss_update_io_biपंचांगap(व्योम)
अणु
	PVOP_VCALL0(cpu.update_io_biपंचांगap);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम paravirt_activate_mm(काष्ठा mm_काष्ठा *prev,
					काष्ठा mm_काष्ठा *next)
अणु
	PVOP_VCALL2(mmu.activate_mm, prev, next);
पूर्ण

अटल अंतरभूत व्योम paravirt_arch_dup_mmap(काष्ठा mm_काष्ठा *oldmm,
					  काष्ठा mm_काष्ठा *mm)
अणु
	PVOP_VCALL2(mmu.dup_mmap, oldmm, mm);
पूर्ण

अटल अंतरभूत पूर्णांक paravirt_pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	वापस PVOP_CALL1(पूर्णांक, mmu.pgd_alloc, mm);
पूर्ण

अटल अंतरभूत व्योम paravirt_pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	PVOP_VCALL2(mmu.pgd_मुक्त, mm, pgd);
पूर्ण

अटल अंतरभूत व्योम paravirt_alloc_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn)
अणु
	PVOP_VCALL2(mmu.alloc_pte, mm, pfn);
पूर्ण
अटल अंतरभूत व्योम paravirt_release_pte(अचिन्हित दीर्घ pfn)
अणु
	PVOP_VCALL1(mmu.release_pte, pfn);
पूर्ण

अटल अंतरभूत व्योम paravirt_alloc_pmd(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn)
अणु
	PVOP_VCALL2(mmu.alloc_pmd, mm, pfn);
पूर्ण

अटल अंतरभूत व्योम paravirt_release_pmd(अचिन्हित दीर्घ pfn)
अणु
	PVOP_VCALL1(mmu.release_pmd, pfn);
पूर्ण

अटल अंतरभूत व्योम paravirt_alloc_pud(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn)
अणु
	PVOP_VCALL2(mmu.alloc_pud, mm, pfn);
पूर्ण
अटल अंतरभूत व्योम paravirt_release_pud(अचिन्हित दीर्घ pfn)
अणु
	PVOP_VCALL1(mmu.release_pud, pfn);
पूर्ण

अटल अंतरभूत व्योम paravirt_alloc_p4d(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ pfn)
अणु
	PVOP_VCALL2(mmu.alloc_p4d, mm, pfn);
पूर्ण

अटल अंतरभूत व्योम paravirt_release_p4d(अचिन्हित दीर्घ pfn)
अणु
	PVOP_VCALL1(mmu.release_p4d, pfn);
पूर्ण

अटल अंतरभूत pte_t __pte(pteval_t val)
अणु
	वापस (pte_t) अणु PVOP_ALT_CALLEE1(pteval_t, mmu.make_pte, val,
					  "mov %%rdi, %%rax",
					  ALT_NOT(X86_FEATURE_XENPV)) पूर्ण;
पूर्ण

अटल अंतरभूत pteval_t pte_val(pte_t pte)
अणु
	वापस PVOP_ALT_CALLEE1(pteval_t, mmu.pte_val, pte.pte,
				"mov %%rdi, %%rax", ALT_NOT(X86_FEATURE_XENPV));
पूर्ण

अटल अंतरभूत pgd_t __pgd(pgdval_t val)
अणु
	वापस (pgd_t) अणु PVOP_ALT_CALLEE1(pgdval_t, mmu.make_pgd, val,
					  "mov %%rdi, %%rax",
					  ALT_NOT(X86_FEATURE_XENPV)) पूर्ण;
पूर्ण

अटल अंतरभूत pgdval_t pgd_val(pgd_t pgd)
अणु
	वापस PVOP_ALT_CALLEE1(pgdval_t, mmu.pgd_val, pgd.pgd,
				"mov %%rdi, %%rax", ALT_NOT(X86_FEATURE_XENPV));
पूर्ण

#घोषणा  __HAVE_ARCH_PTEP_MODIFY_PROT_TRANSACTION
अटल अंतरभूत pte_t ptep_modअगरy_prot_start(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
					   pte_t *ptep)
अणु
	pteval_t ret;

	ret = PVOP_CALL3(pteval_t, mmu.ptep_modअगरy_prot_start, vma, addr, ptep);

	वापस (pte_t) अणु .pte = ret पूर्ण;
पूर्ण

अटल अंतरभूत व्योम ptep_modअगरy_prot_commit(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
					   pte_t *ptep, pte_t old_pte, pte_t pte)
अणु

	PVOP_VCALL4(mmu.ptep_modअगरy_prot_commit, vma, addr, ptep, pte.pte);
पूर्ण

अटल अंतरभूत व्योम set_pte(pte_t *ptep, pte_t pte)
अणु
	PVOP_VCALL2(mmu.set_pte, ptep, pte.pte);
पूर्ण

अटल अंतरभूत व्योम set_pmd(pmd_t *pmdp, pmd_t pmd)
अणु
	PVOP_VCALL2(mmu.set_pmd, pmdp, native_pmd_val(pmd));
पूर्ण

अटल अंतरभूत pmd_t __pmd(pmdval_t val)
अणु
	वापस (pmd_t) अणु PVOP_ALT_CALLEE1(pmdval_t, mmu.make_pmd, val,
					  "mov %%rdi, %%rax",
					  ALT_NOT(X86_FEATURE_XENPV)) पूर्ण;
पूर्ण

अटल अंतरभूत pmdval_t pmd_val(pmd_t pmd)
अणु
	वापस PVOP_ALT_CALLEE1(pmdval_t, mmu.pmd_val, pmd.pmd,
				"mov %%rdi, %%rax", ALT_NOT(X86_FEATURE_XENPV));
पूर्ण

अटल अंतरभूत व्योम set_pud(pud_t *pudp, pud_t pud)
अणु
	PVOP_VCALL2(mmu.set_pud, pudp, native_pud_val(pud));
पूर्ण

अटल अंतरभूत pud_t __pud(pudval_t val)
अणु
	pudval_t ret;

	ret = PVOP_ALT_CALLEE1(pudval_t, mmu.make_pud, val,
			       "mov %%rdi, %%rax", ALT_NOT(X86_FEATURE_XENPV));

	वापस (pud_t) अणु ret पूर्ण;
पूर्ण

अटल अंतरभूत pudval_t pud_val(pud_t pud)
अणु
	वापस PVOP_ALT_CALLEE1(pudval_t, mmu.pud_val, pud.pud,
				"mov %%rdi, %%rax", ALT_NOT(X86_FEATURE_XENPV));
पूर्ण

अटल अंतरभूत व्योम pud_clear(pud_t *pudp)
अणु
	set_pud(pudp, native_make_pud(0));
पूर्ण

अटल अंतरभूत व्योम set_p4d(p4d_t *p4dp, p4d_t p4d)
अणु
	p4dval_t val = native_p4d_val(p4d);

	PVOP_VCALL2(mmu.set_p4d, p4dp, val);
पूर्ण

#अगर CONFIG_PGTABLE_LEVELS >= 5

अटल अंतरभूत p4d_t __p4d(p4dval_t val)
अणु
	p4dval_t ret = PVOP_ALT_CALLEE1(p4dval_t, mmu.make_p4d, val,
					"mov %%rdi, %%rax",
					ALT_NOT(X86_FEATURE_XENPV));

	वापस (p4d_t) अणु ret पूर्ण;
पूर्ण

अटल अंतरभूत p4dval_t p4d_val(p4d_t p4d)
अणु
	वापस PVOP_ALT_CALLEE1(p4dval_t, mmu.p4d_val, p4d.p4d,
				"mov %%rdi, %%rax", ALT_NOT(X86_FEATURE_XENPV));
पूर्ण

अटल अंतरभूत व्योम __set_pgd(pgd_t *pgdp, pgd_t pgd)
अणु
	PVOP_VCALL2(mmu.set_pgd, pgdp, native_pgd_val(pgd));
पूर्ण

#घोषणा set_pgd(pgdp, pgdval) करो अणु					\
	अगर (pgtable_l5_enabled())						\
		__set_pgd(pgdp, pgdval);				\
	अन्यथा								\
		set_p4d((p4d_t *)(pgdp), (p4d_t) अणु (pgdval).pgd पूर्ण);	\
पूर्ण जबतक (0)

#घोषणा pgd_clear(pgdp) करो अणु						\
	अगर (pgtable_l5_enabled())					\
		set_pgd(pgdp, native_make_pgd(0));			\
पूर्ण जबतक (0)

#पूर्ण_अगर  /* CONFIG_PGTABLE_LEVELS == 5 */

अटल अंतरभूत व्योम p4d_clear(p4d_t *p4dp)
अणु
	set_p4d(p4dp, native_make_p4d(0));
पूर्ण

अटल अंतरभूत व्योम set_pte_atomic(pte_t *ptep, pte_t pte)
अणु
	set_pte(ptep, pte);
पूर्ण

अटल अंतरभूत व्योम pte_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			     pte_t *ptep)
अणु
	set_pte(ptep, native_make_pte(0));
पूर्ण

अटल अंतरभूत व्योम pmd_clear(pmd_t *pmdp)
अणु
	set_pmd(pmdp, native_make_pmd(0));
पूर्ण

#घोषणा  __HAVE_ARCH_START_CONTEXT_SWITCH
अटल अंतरभूत व्योम arch_start_context_चयन(काष्ठा task_काष्ठा *prev)
अणु
	PVOP_VCALL1(cpu.start_context_चयन, prev);
पूर्ण

अटल अंतरभूत व्योम arch_end_context_चयन(काष्ठा task_काष्ठा *next)
अणु
	PVOP_VCALL1(cpu.end_context_चयन, next);
पूर्ण

#घोषणा  __HAVE_ARCH_ENTER_LAZY_MMU_MODE
अटल अंतरभूत व्योम arch_enter_lazy_mmu_mode(व्योम)
अणु
	PVOP_VCALL0(mmu.lazy_mode.enter);
पूर्ण

अटल अंतरभूत व्योम arch_leave_lazy_mmu_mode(व्योम)
अणु
	PVOP_VCALL0(mmu.lazy_mode.leave);
पूर्ण

अटल अंतरभूत व्योम arch_flush_lazy_mmu_mode(व्योम)
अणु
	PVOP_VCALL0(mmu.lazy_mode.flush);
पूर्ण

अटल अंतरभूत व्योम __set_fixmap(अचिन्हित /* क्रमागत fixed_addresses */ idx,
				phys_addr_t phys, pgprot_t flags)
अणु
	pv_ops.mmu.set_fixmap(idx, phys, flags);
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SMP) && defined(CONFIG_PARAVIRT_SPINLOCKS)

अटल __always_अंतरभूत व्योम pv_queued_spin_lock_slowpath(काष्ठा qspinlock *lock,
							u32 val)
अणु
	PVOP_VCALL2(lock.queued_spin_lock_slowpath, lock, val);
पूर्ण

अटल __always_अंतरभूत व्योम pv_queued_spin_unlock(काष्ठा qspinlock *lock)
अणु
	PVOP_ALT_VCALLEE1(lock.queued_spin_unlock, lock,
			  "movb $0, (%%" _ASM_ARG1 ");",
			  ALT_NOT(X86_FEATURE_PVUNLOCK));
पूर्ण

अटल __always_अंतरभूत व्योम pv_रुको(u8 *ptr, u8 val)
अणु
	PVOP_VCALL2(lock.रुको, ptr, val);
पूर्ण

अटल __always_अंतरभूत व्योम pv_kick(पूर्णांक cpu)
अणु
	PVOP_VCALL1(lock.kick, cpu);
पूर्ण

अटल __always_अंतरभूत bool pv_vcpu_is_preempted(दीर्घ cpu)
अणु
	वापस PVOP_ALT_CALLEE1(bool, lock.vcpu_is_preempted, cpu,
				"xor %%" _ASM_AX ", %%" _ASM_AX ";",
				ALT_NOT(X86_FEATURE_VCPUPREEMPT));
पूर्ण

व्योम __raw_callee_save___native_queued_spin_unlock(काष्ठा qspinlock *lock);
bool __raw_callee_save___native_vcpu_is_preempted(दीर्घ cpu);

#पूर्ण_अगर /* SMP && PARAVIRT_SPINLOCKS */

#अगर_घोषित CONFIG_X86_32
/* save and restore all caller-save रेजिस्टरs, except वापस value */
#घोषणा PV_SAVE_ALL_CALLER_REGS		"pushl %ecx;"
#घोषणा PV_RESTORE_ALL_CALLER_REGS	"popl  %ecx;"
#अन्यथा
/* save and restore all caller-save रेजिस्टरs, except वापस value */
#घोषणा PV_SAVE_ALL_CALLER_REGS						\
	"push %rcx;"							\
	"push %rdx;"							\
	"push %rsi;"							\
	"push %rdi;"							\
	"push %r8;"							\
	"push %r9;"							\
	"push %r10;"							\
	"push %r11;"
#घोषणा PV_RESTORE_ALL_CALLER_REGS					\
	"pop %r11;"							\
	"pop %r10;"							\
	"pop %r9;"							\
	"pop %r8;"							\
	"pop %rdi;"							\
	"pop %rsi;"							\
	"pop %rdx;"							\
	"pop %rcx;"
#पूर्ण_अगर

/*
 * Generate a thunk around a function which saves all caller-save
 * रेजिस्टरs except क्रम the वापस value.  This allows C functions to
 * be called from assembler code where fewer than normal रेजिस्टरs are
 * available.  It may also help code generation around calls from C
 * code अगर the common हाल करोesn't use many रेजिस्टरs.
 *
 * When a callee is wrapped in a thunk, the caller can assume that all
 * arg regs and all scratch रेजिस्टरs are preserved across the
 * call. The वापस value in rax/eax will not be saved, even क्रम व्योम
 * functions.
 */
#घोषणा PV_THUNK_NAME(func) "__raw_callee_save_" #func
#घोषणा PV_CALLEE_SAVE_REGS_THUNK(func)					\
	बाह्य typeof(func) __raw_callee_save_##func;			\
									\
	यंत्र(".pushsection .text;"					\
	    ".globl " PV_THUNK_NAME(func) ";"				\
	    ".type " PV_THUNK_NAME(func) ", @function;"			\
	    PV_THUNK_NAME(func) ":"					\
	    FRAME_BEGIN							\
	    PV_SAVE_ALL_CALLER_REGS					\
	    "call " #func ";"						\
	    PV_RESTORE_ALL_CALLER_REGS					\
	    FRAME_END							\
	    "ret;"							\
	    ".size " PV_THUNK_NAME(func) ", .-" PV_THUNK_NAME(func) ";"	\
	    ".popsection")

/* Get a reference to a callee-save function */
#घोषणा PV_CALLEE_SAVE(func)						\
	((काष्ठा paravirt_callee_save) अणु __raw_callee_save_##func पूर्ण)

/* Promise that "func" alपढ़ोy uses the right calling convention */
#घोषणा __PV_IS_CALLEE_SAVE(func)			\
	((काष्ठा paravirt_callee_save) अणु func पूर्ण)

#अगर_घोषित CONFIG_PARAVIRT_XXL
अटल अंतरभूत notrace अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	वापस PVOP_ALT_CALLEE0(अचिन्हित दीर्घ, irq.save_fl, "pushf; pop %%rax;",
				ALT_NOT(X86_FEATURE_XENPV));
पूर्ण

अटल अंतरभूत notrace व्योम arch_local_irq_disable(व्योम)
अणु
	PVOP_ALT_VCALLEE0(irq.irq_disable, "cli;", ALT_NOT(X86_FEATURE_XENPV));
पूर्ण

अटल अंतरभूत notrace व्योम arch_local_irq_enable(व्योम)
अणु
	PVOP_ALT_VCALLEE0(irq.irq_enable, "sti;", ALT_NOT(X86_FEATURE_XENPV));
पूर्ण

अटल अंतरभूत notrace अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ f;

	f = arch_local_save_flags();
	arch_local_irq_disable();
	वापस f;
पूर्ण
#पूर्ण_अगर


/* Make sure as little as possible of this mess escapes. */
#अघोषित PARAVIRT_CALL
#अघोषित __PVOP_CALL
#अघोषित __PVOP_VCALL
#अघोषित PVOP_VCALL0
#अघोषित PVOP_CALL0
#अघोषित PVOP_VCALL1
#अघोषित PVOP_CALL1
#अघोषित PVOP_VCALL2
#अघोषित PVOP_CALL2
#अघोषित PVOP_VCALL3
#अघोषित PVOP_CALL3
#अघोषित PVOP_VCALL4
#अघोषित PVOP_CALL4

बाह्य व्योम शेष_banner(व्योम);

#अन्यथा  /* __ASSEMBLY__ */

#घोषणा _PVSITE(ptype, ops, word, algn)		\
771:;						\
	ops;					\
772:;						\
	.pushsection .parainकाष्ठाions,"a";	\
	 .align	algn;				\
	 word 771b;				\
	 .byte ptype;				\
	 .byte 772b-771b;			\
	.popsection


#अगर_घोषित CONFIG_X86_64
#अगर_घोषित CONFIG_PARAVIRT_XXL

#घोषणा PARA_PATCH(off)		((off) / 8)
#घोषणा PARA_SITE(ptype, ops)	_PVSITE(ptype, ops, .quad, 8)
#घोषणा PARA_INसूचीECT(addr)	*addr(%rip)

#घोषणा INTERRUPT_RETURN						\
	ANNOTATE_RETPOLINE_SAFE;					\
	ALTERNATIVE_TERNARY("jmp *paravirt_iret(%rip);",		\
		X86_FEATURE_XENPV, "jmp xen_iret;", "jmp native_iret;")

#अगर_घोषित CONFIG_DEBUG_ENTRY
.macro PARA_IRQ_save_fl
	PARA_SITE(PARA_PATCH(PV_IRQ_save_fl),
		  ANNOTATE_RETPOLINE_SAFE;
		  call PARA_INसूचीECT(pv_ops+PV_IRQ_save_fl);)
.endm

#घोषणा SAVE_FLAGS	ALTERNATIVE "PARA_IRQ_save_fl;", "pushf; pop %rax;", \
				    ALT_NOT(X86_FEATURE_XENPV)
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_PARAVIRT_XXL */
#पूर्ण_अगर	/* CONFIG_X86_64 */

#पूर्ण_अगर /* __ASSEMBLY__ */
#अन्यथा  /* CONFIG_PARAVIRT */
# define शेष_banner x86_init_noop
#पूर्ण_अगर /* !CONFIG_PARAVIRT */

#अगर_अघोषित __ASSEMBLY__
#अगर_अघोषित CONFIG_PARAVIRT_XXL
अटल अंतरभूत व्योम paravirt_arch_dup_mmap(काष्ठा mm_काष्ठा *oldmm,
					  काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित CONFIG_PARAVIRT
अटल अंतरभूत व्योम paravirt_arch_निकास_mmap(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित CONFIG_PARAVIRT_SPINLOCKS
अटल अंतरभूत व्योम paravirt_set_cap(व्योम)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_X86_PARAVIRT_H */
