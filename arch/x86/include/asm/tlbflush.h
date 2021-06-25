<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_TLBFLUSH_H
#घोषणा _ASM_X86_TLBFLUSH_H

#समावेश <linux/mm.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/special_insns.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/invpcid.h>
#समावेश <यंत्र/pti.h>
#समावेश <यंत्र/processor-flags.h>

व्योम __flush_tlb_all(व्योम);

#घोषणा TLB_FLUSH_ALL	-1UL

व्योम cr4_update_irqsoff(अचिन्हित दीर्घ set, अचिन्हित दीर्घ clear);
अचिन्हित दीर्घ cr4_पढ़ो_shaकरोw(व्योम);

/* Set in this cpu's CR4. */
अटल अंतरभूत व्योम cr4_set_bits_irqsoff(अचिन्हित दीर्घ mask)
अणु
	cr4_update_irqsoff(mask, 0);
पूर्ण

/* Clear in this cpu's CR4. */
अटल अंतरभूत व्योम cr4_clear_bits_irqsoff(अचिन्हित दीर्घ mask)
अणु
	cr4_update_irqsoff(0, mask);
पूर्ण

/* Set in this cpu's CR4. */
अटल अंतरभूत व्योम cr4_set_bits(अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	cr4_set_bits_irqsoff(mask);
	local_irq_restore(flags);
पूर्ण

/* Clear in this cpu's CR4. */
अटल अंतरभूत व्योम cr4_clear_bits(अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	cr4_clear_bits_irqsoff(mask);
	local_irq_restore(flags);
पूर्ण

#अगर_अघोषित MODULE
/*
 * 6 because 6 should be plenty and काष्ठा tlb_state will fit in two cache
 * lines.
 */
#घोषणा TLB_NR_DYN_ASIDS	6

काष्ठा tlb_context अणु
	u64 ctx_id;
	u64 tlb_gen;
पूर्ण;

काष्ठा tlb_state अणु
	/*
	 * cpu_tlbstate.loaded_mm should match CR3 whenever पूर्णांकerrupts
	 * are on.  This means that it may not match current->active_mm,
	 * which will contain the previous user mm when we're in lazy TLB
	 * mode even अगर we've alपढ़ोy चयनed back to swapper_pg_dir.
	 *
	 * During चयन_mm_irqs_off(), loaded_mm will be set to
	 * LOADED_MM_SWITCHING during the brief पूर्णांकerrupts-off winकरोw
	 * when CR3 and loaded_mm would otherwise be inconsistent.  This
	 * is क्रम nmi_uaccess_okay()'s benefit.
	 */
	काष्ठा mm_काष्ठा *loaded_mm;

#घोषणा LOADED_MM_SWITCHING ((काष्ठा mm_काष्ठा *)1UL)

	/* Last user mm क्रम optimizing IBPB */
	जोड़ अणु
		काष्ठा mm_काष्ठा	*last_user_mm;
		अचिन्हित दीर्घ		last_user_mm_ibpb;
	पूर्ण;

	u16 loaded_mm_asid;
	u16 next_asid;

	/*
	 * If set we changed the page tables in such a way that we
	 * needed an invalidation of all contexts (aka. PCIDs / ASIDs).
	 * This tells us to go invalidate all the non-loaded ctxs[]
	 * on the next context चयन.
	 *
	 * The current ctx was kept up-to-date as it ran and करोes not
	 * need to be invalidated.
	 */
	bool invalidate_other;

	/*
	 * Mask that contains TLB_NR_DYN_ASIDS+1 bits to indicate
	 * the corresponding user PCID needs a flush next समय we
	 * चयन to it; see SWITCH_TO_USER_CR3.
	 */
	अचिन्हित लघु user_pcid_flush_mask;

	/*
	 * Access to this CR4 shaकरोw and to H/W CR4 is रक्षित by
	 * disabling पूर्णांकerrupts when modअगरying either one.
	 */
	अचिन्हित दीर्घ cr4;

	/*
	 * This is a list of all contexts that might exist in the TLB.
	 * There is one per ASID that we use, and the ASID (what the
	 * CPU calls PCID) is the index पूर्णांकo ctxts.
	 *
	 * For each context, ctx_id indicates which mm the TLB's user
	 * entries came from.  As an invariant, the TLB will never
	 * contain entries that are out-of-date as when that mm reached
	 * the tlb_gen in the list.
	 *
	 * To be clear, this means that it's legal क्रम the TLB code to
	 * flush the TLB without updating tlb_gen.  This can happen
	 * (क्रम now, at least) due to paravirt remote flushes.
	 *
	 * NB: context 0 is a bit special, since it's also used by
	 * various bits of init code.  This is fine -- code that
	 * isn't aware of PCID will end up harmlessly flushing
	 * context 0.
	 */
	काष्ठा tlb_context ctxs[TLB_NR_DYN_ASIDS];
पूर्ण;
DECLARE_PER_CPU_ALIGNED(काष्ठा tlb_state, cpu_tlbstate);

काष्ठा tlb_state_shared अणु
	/*
	 * We can be in one of several states:
	 *
	 *  - Actively using an mm.  Our CPU's bit will be set in
	 *    mm_cpumask(loaded_mm) and is_lazy == false;
	 *
	 *  - Not using a real mm.  loaded_mm == &init_mm.  Our CPU's bit
	 *    will not be set in mm_cpumask(&init_mm) and is_lazy == false.
	 *
	 *  - Lazily using a real mm.  loaded_mm != &init_mm, our bit
	 *    is set in mm_cpumask(loaded_mm), but is_lazy == true.
	 *    We're heuristically guessing that the CR3 load we
	 *    skipped more than makes up क्रम the overhead added by
	 *    lazy mode.
	 */
	bool is_lazy;
पूर्ण;
DECLARE_PER_CPU_SHARED_ALIGNED(काष्ठा tlb_state_shared, cpu_tlbstate_shared);

bool nmi_uaccess_okay(व्योम);
#घोषणा nmi_uaccess_okay nmi_uaccess_okay

/* Initialize cr4 shaकरोw क्रम this CPU. */
अटल अंतरभूत व्योम cr4_init_shaकरोw(व्योम)
अणु
	this_cpu_ग_लिखो(cpu_tlbstate.cr4, __पढ़ो_cr4());
पूर्ण

बाह्य अचिन्हित दीर्घ mmu_cr4_features;
बाह्य u32 *trampoline_cr4_features;

बाह्य व्योम initialize_tlbstate_and_flush(व्योम);

/*
 * TLB flushing:
 *
 *  - flush_tlb_all() flushes all processes TLBs
 *  - flush_tlb_mm(mm) flushes the specअगरied mm context TLB's
 *  - flush_tlb_page(vma, vmaddr) flushes one page
 *  - flush_tlb_range(vma, start, end) flushes a range of pages
 *  - flush_tlb_kernel_range(start, end) flushes a range of kernel pages
 *  - flush_tlb_multi(cpumask, info) flushes TLBs on multiple cpus
 *
 * ..but the i386 has somewhat limited tlb flushing capabilities,
 * and page-granular flushes are available only on i486 and up.
 */
काष्ठा flush_tlb_info अणु
	/*
	 * We support several kinds of flushes.
	 *
	 * - Fully flush a single mm.  .mm will be set, .end will be
	 *   TLB_FLUSH_ALL, and .new_tlb_gen will be the tlb_gen to
	 *   which the IPI sender is trying to catch us up.
	 *
	 * - Partially flush a single mm.  .mm will be set, .start and
	 *   .end will indicate the range, and .new_tlb_gen will be set
	 *   such that the changes between generation .new_tlb_gen-1 and
	 *   .new_tlb_gen are entirely contained in the indicated range.
	 *
	 * - Fully flush all mms whose tlb_gens have been updated.  .mm
	 *   will be शून्य, .end will be TLB_FLUSH_ALL, and .new_tlb_gen
	 *   will be zero.
	 */
	काष्ठा mm_काष्ठा	*mm;
	अचिन्हित दीर्घ		start;
	अचिन्हित दीर्घ		end;
	u64			new_tlb_gen;
	अचिन्हित पूर्णांक		initiating_cpu;
	u8			stride_shअगरt;
	u8			मुक्तd_tables;
पूर्ण;

व्योम flush_tlb_local(व्योम);
व्योम flush_tlb_one_user(अचिन्हित दीर्घ addr);
व्योम flush_tlb_one_kernel(अचिन्हित दीर्घ addr);
व्योम flush_tlb_multi(स्थिर काष्ठा cpumask *cpumask,
		      स्थिर काष्ठा flush_tlb_info *info);

#अगर_घोषित CONFIG_PARAVIRT
#समावेश <यंत्र/paravirt.h>
#पूर्ण_अगर

#घोषणा flush_tlb_mm(mm)						\
		flush_tlb_mm_range(mm, 0UL, TLB_FLUSH_ALL, 0UL, true)

#घोषणा flush_tlb_range(vma, start, end)				\
	flush_tlb_mm_range((vma)->vm_mm, start, end,			\
			   ((vma)->vm_flags & VM_HUGETLB)		\
				? huge_page_shअगरt(hstate_vma(vma))	\
				: PAGE_SHIFT, false)

बाह्य व्योम flush_tlb_all(व्योम);
बाह्य व्योम flush_tlb_mm_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
				अचिन्हित दीर्घ end, अचिन्हित पूर्णांक stride_shअगरt,
				bool मुक्तd_tables);
बाह्य व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

अटल अंतरभूत व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ a)
अणु
	flush_tlb_mm_range(vma->vm_mm, a, a + PAGE_SIZE, PAGE_SHIFT, false);
पूर्ण

अटल अंतरभूत u64 inc_mm_tlb_gen(काष्ठा mm_काष्ठा *mm)
अणु
	/*
	 * Bump the generation count.  This also serves as a full barrier
	 * that synchronizes with चयन_mm(): callers are required to order
	 * their पढ़ो of mm_cpumask after their ग_लिखोs to the paging
	 * काष्ठाures.
	 */
	वापस atomic64_inc_वापस(&mm->context.tlb_gen);
पूर्ण

अटल अंतरभूत व्योम arch_tlbbatch_add_mm(काष्ठा arch_tlbflush_unmap_batch *batch,
					काष्ठा mm_काष्ठा *mm)
अणु
	inc_mm_tlb_gen(mm);
	cpumask_or(&batch->cpumask, &batch->cpumask, mm_cpumask(mm));
पूर्ण

बाह्य व्योम arch_tlbbatch_flush(काष्ठा arch_tlbflush_unmap_batch *batch);

#पूर्ण_अगर /* !MODULE */

#पूर्ण_अगर /* _ASM_X86_TLBFLUSH_H */
