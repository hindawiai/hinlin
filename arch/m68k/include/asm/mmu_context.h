<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __M68K_MMU_CONTEXT_H
#घोषणा __M68K_MMU_CONTEXT_H

#समावेश <यंत्र-generic/mm_hooks.h>
#समावेश <linux/mm_types.h>

#अगर_घोषित CONFIG_MMU

#अगर defined(CONFIG_COLDFIRE)

#समावेश <यंत्र/atomic.h>
#समावेश <यंत्र/bitops.h>
#समावेश <यंत्र/mcfmmu.h>
#समावेश <यंत्र/mmu.h>

#घोषणा NO_CONTEXT		256
#घोषणा LAST_CONTEXT		255
#घोषणा FIRST_CONTEXT		1

बाह्य अचिन्हित दीर्घ context_map[];
बाह्य mm_context_t next_mmu_context;

बाह्य atomic_t nr_मुक्त_contexts;
बाह्य काष्ठा mm_काष्ठा *context_mm[LAST_CONTEXT+1];
बाह्य व्योम steal_context(व्योम);

अटल अंतरभूत व्योम get_mmu_context(काष्ठा mm_काष्ठा *mm)
अणु
	mm_context_t ctx;

	अगर (mm->context != NO_CONTEXT)
		वापस;
	जबतक (atomic_dec_and_test_lt(&nr_मुक्त_contexts)) अणु
		atomic_inc(&nr_मुक्त_contexts);
		steal_context();
	पूर्ण
	ctx = next_mmu_context;
	जबतक (test_and_set_bit(ctx, context_map)) अणु
		ctx = find_next_zero_bit(context_map, LAST_CONTEXT+1, ctx);
		अगर (ctx > LAST_CONTEXT)
			ctx = 0;
	पूर्ण
	next_mmu_context = (ctx + 1) & LAST_CONTEXT;
	mm->context = ctx;
	context_mm[ctx] = mm;
पूर्ण

/*
 * Set up the context क्रम a new address space.
 */
#घोषणा init_new_context(tsk, mm)	(((mm)->context = NO_CONTEXT), 0)

/*
 * We're finished using the context क्रम an address space.
 */
#घोषणा destroy_context destroy_context
अटल अंतरभूत व्योम destroy_context(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mm->context != NO_CONTEXT) अणु
		clear_bit(mm->context, context_map);
		mm->context = NO_CONTEXT;
		atomic_inc(&nr_मुक्त_contexts);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम set_context(mm_context_t context, pgd_t *pgd)
अणु
	__यंत्र__ __अस्थिर__ ("movec %0,%%asid" : : "d" (context));
पूर्ण

अटल अंतरभूत व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
	काष्ठा task_काष्ठा *tsk)
अणु
	get_mmu_context(tsk->mm);
	set_context(tsk->mm->context, next->pgd);
पूर्ण

/*
 * After we have set current->mm to a new value, this activates
 * the context क्रम the new mm so we see the new mappings.
 */
#घोषणा activate_mm activate_mm
अटल अंतरभूत व्योम activate_mm(काष्ठा mm_काष्ठा *active_mm,
	काष्ठा mm_काष्ठा *mm)
अणु
	get_mmu_context(mm);
	set_context(mm->context, mm->pgd);
पूर्ण

#घोषणा prepare_arch_चयन(next) load_ksp_mmu(next)

अटल अंतरभूत व्योम load_ksp_mmu(काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mm_काष्ठा *mm;
	पूर्णांक asid;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	अचिन्हित दीर्घ mmuar;

	local_irq_save(flags);
	mmuar = task->thपढ़ो.ksp;

	/* Search क्रम a valid TLB entry, अगर one is found, करोn't remap */
	mmu_ग_लिखो(MMUAR, mmuar);
	mmu_ग_लिखो(MMUOR, MMUOR_STLB | MMUOR_ADR);
	अगर (mmu_पढ़ो(MMUSR) & MMUSR_HIT)
		जाओ end;

	अगर (mmuar >= PAGE_OFFSET) अणु
		mm = &init_mm;
	पूर्ण अन्यथा अणु
		pr_info("load_ksp_mmu: non-kernel mm found: 0x%p\n", task->mm);
		mm = task->mm;
	पूर्ण

	अगर (!mm)
		जाओ bug;

	pgd = pgd_offset(mm, mmuar);
	अगर (pgd_none(*pgd))
		जाओ bug;

	p4d = p4d_offset(pgd, mmuar);
	अगर (p4d_none(*p4d))
		जाओ bug;

	pud = pud_offset(p4d, mmuar);
	अगर (pud_none(*pud))
		जाओ bug;

	pmd = pmd_offset(pud, mmuar);
	अगर (pmd_none(*pmd))
		जाओ bug;

	pte = (mmuar >= PAGE_OFFSET) ? pte_offset_kernel(pmd, mmuar)
				     : pte_offset_map(pmd, mmuar);
	अगर (pte_none(*pte) || !pte_present(*pte))
		जाओ bug;

	set_pte(pte, pte_mkyoung(*pte));
	asid = mm->context & 0xff;
	अगर (!pte_dirty(*pte) && mmuar <= PAGE_OFFSET)
		set_pte(pte, pte_wrprotect(*pte));

	mmu_ग_लिखो(MMUTR, (mmuar & PAGE_MASK) | (asid << MMUTR_IDN) |
		(((पूर्णांक)(pte->pte) & (पूर्णांक)CF_PAGE_MMUTR_MASK)
		>> CF_PAGE_MMUTR_SHIFT) | MMUTR_V);

	mmu_ग_लिखो(MMUDR, (pte_val(*pte) & PAGE_MASK) |
		((pte->pte) & CF_PAGE_MMUDR_MASK) | MMUDR_SZ_8KB | MMUDR_X);

	mmu_ग_लिखो(MMUOR, MMUOR_ACC | MMUOR_UAA);

	जाओ end;

bug:
	pr_info("ksp load failed: mm=0x%p ksp=0x08%lx\n", mm, mmuar);
end:
	local_irq_restore(flags);
पूर्ण

#या_अगर defined(CONFIG_SUN3)
#समावेश <यंत्र/sun3mmu.h>
#समावेश <linux/sched.h>

बाह्य अचिन्हित दीर्घ get_मुक्त_context(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम clear_context(अचिन्हित दीर्घ context);

/* set the context क्रम a new task to unmapped */
#घोषणा init_new_context init_new_context
अटल अंतरभूत पूर्णांक init_new_context(काष्ठा task_काष्ठा *tsk,
				   काष्ठा mm_काष्ठा *mm)
अणु
	mm->context = SUN3_INVALID_CONTEXT;
	वापस 0;
पूर्ण

/* find the context given to this process, and अगर it hasn't alपढ़ोy
   got one, go get one क्रम it. */
अटल अंतरभूत व्योम get_mmu_context(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mm->context == SUN3_INVALID_CONTEXT)
		mm->context = get_मुक्त_context(mm);
पूर्ण

/* flush context अगर allocated... */
#घोषणा destroy_context destroy_context
अटल अंतरभूत व्योम destroy_context(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mm->context != SUN3_INVALID_CONTEXT)
		clear_context(mm->context);
पूर्ण

अटल अंतरभूत व्योम activate_context(काष्ठा mm_काष्ठा *mm)
अणु
	get_mmu_context(mm);
	sun3_put_context(mm->context);
पूर्ण

अटल अंतरभूत व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
			     काष्ठा task_काष्ठा *tsk)
अणु
	activate_context(tsk->mm);
पूर्ण

#घोषणा activate_mm activate_mm
अटल अंतरभूत व्योम activate_mm(काष्ठा mm_काष्ठा *prev_mm,
			       काष्ठा mm_काष्ठा *next_mm)
अणु
	activate_context(next_mm);
पूर्ण

#अन्यथा

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cacheflush.h>

#घोषणा init_new_context init_new_context
अटल अंतरभूत पूर्णांक init_new_context(काष्ठा task_काष्ठा *tsk,
				   काष्ठा mm_काष्ठा *mm)
अणु
	mm->context = virt_to_phys(mm->pgd);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम चयन_mm_0230(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ crp[2] = अणु
		0x80000000 | _PAGE_TABLE, mm->context
	पूर्ण;
	अचिन्हित दीर्घ पंचांगp;

	यंत्र अस्थिर (".chip 68030");

	/* flush MC68030/MC68020 caches (they are भवly addressed) */
	यंत्र अस्थिर (
		"movec %%cacr,%0;"
		"orw %1,%0; "
		"movec %0,%%cacr"
		: "=d" (पंचांगp) : "di" (FLUSH_I_AND_D));

	/* Switch the root poपूर्णांकer. For a 030-only kernel,
	 * aव्योम flushing the whole ATC, we only need to
	 * flush the user entries. The 68851 करोes this by
	 * itself. Aव्योम a runसमय check here.
	 */
	यंत्र अस्थिर (
#अगर_घोषित CPU_M68030_ONLY
		"pmovefd %0,%%crp; "
		"pflush #0,#4"
#अन्यथा
		"pmove %0,%%crp"
#पूर्ण_अगर
		: : "m" (crp[0]));

	यंत्र अस्थिर (".chip 68k");
पूर्ण

अटल अंतरभूत व्योम चयन_mm_0460(काष्ठा mm_काष्ठा *mm)
अणु
	यंत्र अस्थिर (".chip 68040");

	/* flush address translation cache (user entries) */
	यंत्र अस्थिर ("pflushan");

	/* चयन the root poपूर्णांकer */
	यंत्र अस्थिर ("movec %0,%%urp" : : "r" (mm->context));

	अगर (CPU_IS_060) अणु
		अचिन्हित दीर्घ पंचांगp;

		/* clear user entries in the branch cache */
		यंत्र अस्थिर (
			"movec %%cacr,%0; "
		        "orl %1,%0; "
		        "movec %0,%%cacr"
			: "=d" (पंचांगp): "di" (0x00200000));
	पूर्ण

	यंत्र अस्थिर (".chip 68k");
पूर्ण

अटल अंतरभूत व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next, काष्ठा task_काष्ठा *tsk)
अणु
	अगर (prev != next) अणु
		अगर (CPU_IS_020_OR_030)
			चयन_mm_0230(next);
		अन्यथा
			चयन_mm_0460(next);
	पूर्ण
पूर्ण

#घोषणा activate_mm activate_mm
अटल अंतरभूत व्योम activate_mm(काष्ठा mm_काष्ठा *prev_mm,
			       काष्ठा mm_काष्ठा *next_mm)
अणु
	next_mm->context = virt_to_phys(next_mm->pgd);

	अगर (CPU_IS_020_OR_030)
		चयन_mm_0230(next_mm);
	अन्यथा
		चयन_mm_0460(next_mm);
पूर्ण

#पूर्ण_अगर

#समावेश <यंत्र-generic/mmu_context.h>

#अन्यथा /* !CONFIG_MMU */

#समावेश <यंत्र-generic/nommu_context.h>

#पूर्ण_अगर /* CONFIG_MMU */
#पूर्ण_अगर /* __M68K_MMU_CONTEXT_H */
