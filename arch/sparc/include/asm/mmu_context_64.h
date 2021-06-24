<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SPARC64_MMU_CONTEXT_H
#घोषणा __SPARC64_MMU_CONTEXT_H

/* Derived heavily from Linus's Alpha/AXP ASN code... */

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/spinlock.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/smp.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/spitfire.h>
#समावेश <यंत्र/adi_64.h>
#समावेश <यंत्र-generic/mm_hooks.h>
#समावेश <यंत्र/percpu.h>

बाह्य spinlock_t ctx_alloc_lock;
बाह्य अचिन्हित दीर्घ tlb_context_cache;
बाह्य अचिन्हित दीर्घ mmu_context_bmap[];

DECLARE_PER_CPU(काष्ठा mm_काष्ठा *, per_cpu_secondary_mm);
व्योम get_new_mmu_context(काष्ठा mm_काष्ठा *mm);

#घोषणा init_new_context init_new_context
पूर्णांक init_new_context(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm);
#घोषणा destroy_context destroy_context
व्योम destroy_context(काष्ठा mm_काष्ठा *mm);

व्योम __tsb_context_चयन(अचिन्हित दीर्घ pgd_pa,
			  काष्ठा tsb_config *tsb_base,
			  काष्ठा tsb_config *tsb_huge,
			  अचिन्हित दीर्घ tsb_descr_pa,
			  अचिन्हित दीर्घ secondary_ctx);

अटल अंतरभूत व्योम tsb_context_चयन_ctx(काष्ठा mm_काष्ठा *mm,
					  अचिन्हित दीर्घ ctx)
अणु
	__tsb_context_चयन(__pa(mm->pgd),
			     &mm->context.tsb_block[MM_TSB_BASE],
#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
			     (mm->context.tsb_block[MM_TSB_HUGE].tsb ?
			      &mm->context.tsb_block[MM_TSB_HUGE] :
			      शून्य)
#अन्यथा
			     शून्य
#पूर्ण_अगर
			     , __pa(&mm->context.tsb_descr[MM_TSB_BASE]),
			     ctx);
पूर्ण

#घोषणा tsb_context_चयन(X) tsb_context_चयन_ctx(X, 0)

व्योम tsb_grow(काष्ठा mm_काष्ठा *mm,
	      अचिन्हित दीर्घ tsb_index,
	      अचिन्हित दीर्घ mm_rss);
#अगर_घोषित CONFIG_SMP
व्योम smp_tsb_sync(काष्ठा mm_काष्ठा *mm);
#अन्यथा
#घोषणा smp_tsb_sync(__mm) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/* Set MMU context in the actual hardware. */
#घोषणा load_secondary_context(__mm) \
	__यंत्र__ __अस्थिर__( \
	"\n661:	stxa		%0, [%1] %2\n" \
	"	.section	.sun4v_1insn_patch, \"ax\"\n" \
	"	.word		661b\n" \
	"	stxa		%0, [%1] %3\n" \
	"	.previous\n" \
	"	flush		%%g6\n" \
	: /* No outमाला_दो */ \
	: "r" (CTX_HWBITS((__mm)->context)), \
	  "r" (SECONDARY_CONTEXT), "i" (ASI_DMMU), "i" (ASI_MMU))

व्योम __flush_tlb_mm(अचिन्हित दीर्घ, अचिन्हित दीर्घ);

/* Switch the current MM context. */
अटल अंतरभूत व्योम चयन_mm(काष्ठा mm_काष्ठा *old_mm, काष्ठा mm_काष्ठा *mm, काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ ctx_valid, flags;
	पूर्णांक cpu = smp_processor_id();

	per_cpu(per_cpu_secondary_mm, cpu) = mm;
	अगर (unlikely(mm == &init_mm))
		वापस;

	spin_lock_irqsave(&mm->context.lock, flags);
	ctx_valid = CTX_VALID(mm->context);
	अगर (!ctx_valid)
		get_new_mmu_context(mm);

	/* We have to be extremely careful here or अन्यथा we will miss
	 * a TSB grow अगर we चयन back and क्रमth between a kernel
	 * thपढ़ो and an address space which has it's TSB size increased
	 * on another processor.
	 *
	 * It is possible to play some games in order to optimize the
	 * चयन, but the safest thing to करो is to unconditionally
	 * perक्रमm the secondary context load and the TSB context चयन.
	 *
	 * For reference the bad हाल is, क्रम address space "A":
	 *
	 *		CPU 0			CPU 1
	 *	run address space A
	 *	set cpu0's bits in cpu_vm_mask
	 *	चयन to kernel thपढ़ो, borrow
	 *	address space A via entry_lazy_tlb
	 *					run address space A
	 *					set cpu1's bit in cpu_vm_mask
	 *					flush_tlb_pending()
	 *					reset cpu_vm_mask to just cpu1
	 *					TSB grow
	 *	run address space A
	 *	context was valid, so skip
	 *	TSB context चयन
	 *
	 * At that poपूर्णांक cpu0 जारीs to use a stale TSB, the one from
	 * beक्रमe the TSB grow perक्रमmed on cpu1.  cpu1 did not cross-call
	 * cpu0 to update it's TSB because at that poपूर्णांक the cpu_vm_mask
	 * only had cpu1 set in it.
	 */
	tsb_context_चयन_ctx(mm, CTX_HWBITS(mm->context));

	/* Any समय a processor runs a context on an address space
	 * क्रम the first समय, we must flush that context out of the
	 * local TLB.
	 */
	अगर (!ctx_valid || !cpumask_test_cpu(cpu, mm_cpumask(mm))) अणु
		cpumask_set_cpu(cpu, mm_cpumask(mm));
		__flush_tlb_mm(CTX_HWBITS(mm->context),
			       SECONDARY_CONTEXT);
	पूर्ण
	spin_unlock_irqrestore(&mm->context.lock, flags);
पूर्ण

#घोषणा activate_mm(active_mm, mm) चयन_mm(active_mm, mm, शून्य)

#घोषणा  __HAVE_ARCH_START_CONTEXT_SWITCH
अटल अंतरभूत व्योम arch_start_context_चयन(काष्ठा task_काष्ठा *prev)
अणु
	/* Save the current state of MCDPER रेजिस्टर क्रम the process
	 * we are चयनing from
	 */
	अगर (adi_capable()) अणु
		रेजिस्टर अचिन्हित दीर्घ पंचांगp_mcdper;

		__यंत्र__ __अस्थिर__(
			".word 0x83438000\n\t"	/* rd  %mcdper, %g1 */
			"mov %%g1, %0\n\t"
			: "=r" (पंचांगp_mcdper)
			:
			: "g1");
		अगर (पंचांगp_mcdper)
			set_tsk_thपढ़ो_flag(prev, TIF_MCDPER);
		अन्यथा
			clear_tsk_thपढ़ो_flag(prev, TIF_MCDPER);
	पूर्ण
पूर्ण

#घोषणा finish_arch_post_lock_चयन	finish_arch_post_lock_चयन
अटल अंतरभूत व्योम finish_arch_post_lock_चयन(व्योम)
अणु
	/* Restore the state of MCDPER रेजिस्टर क्रम the new process
	 * just चयनed to.
	 */
	अगर (adi_capable()) अणु
		रेजिस्टर अचिन्हित दीर्घ पंचांगp_mcdper;

		पंचांगp_mcdper = test_thपढ़ो_flag(TIF_MCDPER);
		__यंत्र__ __अस्थिर__(
			"mov %0, %%g1\n\t"
			".word 0x9d800001\n\t"	/* wr %g0, %g1, %mcdper" */
			".word 0xaf902001\n\t"	/* wrpr %g0, 1, %pmcdper */
			:
			: "ir" (पंचांगp_mcdper)
			: "g1");
		अगर (current && current->mm && current->mm->context.adi) अणु
			काष्ठा pt_regs *regs;

			regs = task_pt_regs(current);
			regs->tstate |= TSTATE_MCDE;
		पूर्ण
	पूर्ण
पूर्ण

#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर /* !(__ASSEMBLY__) */

#पूर्ण_अगर /* !(__SPARC64_MMU_CONTEXT_H) */
