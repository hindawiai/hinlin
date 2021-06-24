<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/mmu_context.h
 *
 * Copyright (C) 1996 Russell King.
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_MMU_CONTEXT_H
#घोषणा __ASM_MMU_CONTEXT_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/compiler.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र-generic/mm_hooks.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/sysreg.h>
#समावेश <यंत्र/tlbflush.h>

बाह्य bool rodata_full;

अटल अंतरभूत व्योम contextidr_thपढ़ो_चयन(काष्ठा task_काष्ठा *next)
अणु
	अगर (!IS_ENABLED(CONFIG_PID_IN_CONTEXTIDR))
		वापस;

	ग_लिखो_sysreg(task_pid_nr(next), contextidr_el1);
	isb();
पूर्ण

/*
 * Set TTBR0 to reserved_pg_dir. No translations will be possible via TTBR0.
 */
अटल अंतरभूत व्योम cpu_set_reserved_ttbr0(व्योम)
अणु
	अचिन्हित दीर्घ ttbr = phys_to_ttbr(__pa_symbol(reserved_pg_dir));

	ग_लिखो_sysreg(ttbr, ttbr0_el1);
	isb();
पूर्ण

व्योम cpu_करो_चयन_mm(phys_addr_t pgd_phys, काष्ठा mm_काष्ठा *mm);

अटल अंतरभूत व्योम cpu_चयन_mm(pgd_t *pgd, काष्ठा mm_काष्ठा *mm)
अणु
	BUG_ON(pgd == swapper_pg_dir);
	cpu_set_reserved_ttbr0();
	cpu_करो_चयन_mm(virt_to_phys(pgd),mm);
पूर्ण

/*
 * TCR.T0SZ value to use when the ID map is active. Usually equals
 * TCR_T0SZ(VA_BITS), unless प्रणाली RAM is positioned very high in
 * physical memory, in which हाल it will be smaller.
 */
बाह्य u64 idmap_t0sz;
बाह्य u64 idmap_ptrs_per_pgd;

/*
 * Ensure TCR.T0SZ is set to the provided value.
 */
अटल अंतरभूत व्योम __cpu_set_tcr_t0sz(अचिन्हित दीर्घ t0sz)
अणु
	अचिन्हित दीर्घ tcr = पढ़ो_sysreg(tcr_el1);

	अगर ((tcr & TCR_T0SZ_MASK) >> TCR_T0SZ_OFFSET == t0sz)
		वापस;

	tcr &= ~TCR_T0SZ_MASK;
	tcr |= t0sz << TCR_T0SZ_OFFSET;
	ग_लिखो_sysreg(tcr, tcr_el1);
	isb();
पूर्ण

#घोषणा cpu_set_शेष_tcr_t0sz()	__cpu_set_tcr_t0sz(TCR_T0SZ(vabits_actual))
#घोषणा cpu_set_idmap_tcr_t0sz()	__cpu_set_tcr_t0sz(idmap_t0sz)

/*
 * Remove the idmap from TTBR0_EL1 and install the pgd of the active mm.
 *
 * The idmap lives in the same VA range as userspace, but uses global entries
 * and may use a dअगरferent TCR_EL1.T0SZ. To aव्योम issues resulting from
 * speculative TLB fetches, we must temporarily install the reserved page
 * tables जबतक we invalidate the TLBs and set up the correct TCR_EL1.T0SZ.
 *
 * If current is a not a user task, the mm covers the TTBR1_EL1 page tables,
 * which should not be installed in TTBR0_EL1. In this हाल we can leave the
 * reserved page tables in place.
 */
अटल अंतरभूत व्योम cpu_uninstall_idmap(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = current->active_mm;

	cpu_set_reserved_ttbr0();
	local_flush_tlb_all();
	cpu_set_शेष_tcr_t0sz();

	अगर (mm != &init_mm && !प्रणाली_uses_ttbr0_pan())
		cpu_चयन_mm(mm->pgd, mm);
पूर्ण

अटल अंतरभूत व्योम cpu_install_idmap(व्योम)
अणु
	cpu_set_reserved_ttbr0();
	local_flush_tlb_all();
	cpu_set_idmap_tcr_t0sz();

	cpu_चयन_mm(lm_alias(idmap_pg_dir), &init_mm);
पूर्ण

/*
 * Atomically replaces the active TTBR1_EL1 PGD with a new VA-compatible PGD,
 * aव्योमing the possibility of conflicting TLB entries being allocated.
 */
अटल अंतरभूत व्योम __nocfi cpu_replace_ttbr1(pgd_t *pgdp)
अणु
	प्रकार व्योम (ttbr_replace_func)(phys_addr_t);
	बाह्य ttbr_replace_func idmap_cpu_replace_ttbr1;
	ttbr_replace_func *replace_phys;

	/* phys_to_ttbr() zeros lower 2 bits of ttbr with 52-bit PA */
	phys_addr_t ttbr1 = phys_to_ttbr(virt_to_phys(pgdp));

	अगर (प्रणाली_supports_cnp() && !WARN_ON(pgdp != lm_alias(swapper_pg_dir))) अणु
		/*
		 * cpu_replace_ttbr1() is used when there's a boot CPU
		 * up (i.e. cpufeature framework is not up yet) and
		 * latter only when we enable CNP via cpufeature's
		 * enable() callback.
		 * Also we rely on the cpu_hwcap bit being set beक्रमe
		 * calling the enable() function.
		 */
		ttbr1 |= TTBR_CNP_BIT;
	पूर्ण

	replace_phys = (व्योम *)__pa_symbol(function_nocfi(idmap_cpu_replace_ttbr1));

	cpu_install_idmap();
	replace_phys(ttbr1);
	cpu_uninstall_idmap();
पूर्ण

/*
 * It would be nice to वापस ASIDs back to the allocator, but unक्रमtunately
 * that पूर्णांकroduces a race with a generation rollover where we could erroneously
 * मुक्त an ASID allocated in a future generation. We could workaround this by
 * मुक्तing the ASID from the context of the dying mm (e.g. in arch_निकास_mmap),
 * but we'd then need to make sure that we didn't dirty any TLBs afterwards.
 * Setting a reserved TTBR0 or EPD0 would work, but it all माला_लो ugly when you
 * take CPU migration पूर्णांकo account.
 */
व्योम check_and_चयन_context(काष्ठा mm_काष्ठा *mm);

#घोषणा init_new_context(tsk, mm) init_new_context(tsk, mm)
अटल अंतरभूत पूर्णांक
init_new_context(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm)
अणु
	atomic64_set(&mm->context.id, 0);
	refcount_set(&mm->context.pinned, 0);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ARM64_SW_TTBR0_PAN
अटल अंतरभूत व्योम update_saved_ttbr0(काष्ठा task_काष्ठा *tsk,
				      काष्ठा mm_काष्ठा *mm)
अणु
	u64 ttbr;

	अगर (!प्रणाली_uses_ttbr0_pan())
		वापस;

	अगर (mm == &init_mm)
		ttbr = __pa_symbol(reserved_pg_dir);
	अन्यथा
		ttbr = virt_to_phys(mm->pgd) | ASID(mm) << 48;

	WRITE_ONCE(task_thपढ़ो_info(tsk)->ttbr0, ttbr);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम update_saved_ttbr0(काष्ठा task_काष्ठा *tsk,
				      काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण
#पूर्ण_अगर

#घोषणा enter_lazy_tlb enter_lazy_tlb
अटल अंतरभूत व्योम
enter_lazy_tlb(काष्ठा mm_काष्ठा *mm, काष्ठा task_काष्ठा *tsk)
अणु
	/*
	 * We करोn't actually care about the ttbr0 mapping, so poपूर्णांक it at the
	 * zero page.
	 */
	update_saved_ttbr0(tsk, &init_mm);
पूर्ण

अटल अंतरभूत व्योम __चयन_mm(काष्ठा mm_काष्ठा *next)
अणु
	/*
	 * init_mm.pgd करोes not contain any user mappings and it is always
	 * active क्रम kernel addresses in TTBR1. Just set the reserved TTBR0.
	 */
	अगर (next == &init_mm) अणु
		cpu_set_reserved_ttbr0();
		वापस;
	पूर्ण

	check_and_चयन_context(next);
पूर्ण

अटल अंतरभूत व्योम
चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
	  काष्ठा task_काष्ठा *tsk)
अणु
	अगर (prev != next)
		__चयन_mm(next);

	/*
	 * Update the saved TTBR0_EL1 of the scheduled-in task as the previous
	 * value may have not been initialised yet (activate_mm caller) or the
	 * ASID has changed since the last run (following the context चयन
	 * of another thपढ़ो of the same process).
	 */
	update_saved_ttbr0(tsk, next);
पूर्ण

व्योम verअगरy_cpu_asid_bits(व्योम);
व्योम post_ttbr_update_workaround(व्योम);

अचिन्हित दीर्घ arm64_mm_context_get(काष्ठा mm_काष्ठा *mm);
व्योम arm64_mm_context_put(काष्ठा mm_काष्ठा *mm);

#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* !__ASM_MMU_CONTEXT_H */
