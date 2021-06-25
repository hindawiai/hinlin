<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *
 *  Derived from "include/asm-i386/mmu_context.h"
 */

#अगर_अघोषित __S390_MMU_CONTEXT_H
#घोषणा __S390_MMU_CONTEXT_H

#समावेश <यंत्र/pgभाग.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/mm_types.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/ctl_reg.h>
#समावेश <यंत्र-generic/mm_hooks.h>

#घोषणा init_new_context init_new_context
अटल अंतरभूत पूर्णांक init_new_context(काष्ठा task_काष्ठा *tsk,
				   काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ asce_type, init_entry;

	spin_lock_init(&mm->context.lock);
	INIT_LIST_HEAD(&mm->context.pgtable_list);
	INIT_LIST_HEAD(&mm->context.gmap_list);
	cpumask_clear(&mm->context.cpu_attach_mask);
	atomic_set(&mm->context.flush_count, 0);
	atomic_set(&mm->context.is_रक्षित, 0);
	mm->context.gmap_asce = 0;
	mm->context.flush_mm = 0;
#अगर_घोषित CONFIG_PGSTE
	mm->context.alloc_pgste = page_table_allocate_pgste ||
		test_thपढ़ो_flag(TIF_PGSTE) ||
		(current->mm && current->mm->context.alloc_pgste);
	mm->context.has_pgste = 0;
	mm->context.uses_skeys = 0;
	mm->context.uses_cmm = 0;
	mm->context.allow_gmap_hpage_1m = 0;
#पूर्ण_अगर
	चयन (mm->context.asce_limit) अणु
	शेष:
		/*
		 * context created by exec, the value of asce_limit can
		 * only be zero in this हाल
		 */
		VM_BUG_ON(mm->context.asce_limit);
		/* जारी as 3-level task */
		mm->context.asce_limit = _REGION2_SIZE;
		fallthrough;
	हाल _REGION2_SIZE:
		/* विभाजनed 3-level task */
		init_entry = _REGION3_ENTRY_EMPTY;
		asce_type = _ASCE_TYPE_REGION3;
		अवरोध;
	हाल TASK_SIZE_MAX:
		/* विभाजनed 5-level task */
		init_entry = _REGION1_ENTRY_EMPTY;
		asce_type = _ASCE_TYPE_REGION1;
		अवरोध;
	हाल _REGION1_SIZE:
		/* विभाजनed 4-level task */
		init_entry = _REGION2_ENTRY_EMPTY;
		asce_type = _ASCE_TYPE_REGION2;
		अवरोध;
	पूर्ण
	mm->context.asce = __pa(mm->pgd) | _ASCE_TABLE_LENGTH |
			   _ASCE_USER_BITS | asce_type;
	crst_table_init((अचिन्हित दीर्घ *) mm->pgd, init_entry);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
			     काष्ठा task_काष्ठा *tsk)
अणु
	पूर्णांक cpu = smp_processor_id();

	अगर (next == &init_mm)
		S390_lowcore.user_asce = s390_invalid_asce;
	अन्यथा
		S390_lowcore.user_asce = next->context.asce;
	cpumask_set_cpu(cpu, &next->context.cpu_attach_mask);
	/* Clear previous user-ASCE from CR7 */
	__ctl_load(s390_invalid_asce, 7, 7);
	अगर (prev != next)
		cpumask_clear_cpu(cpu, &prev->context.cpu_attach_mask);
पूर्ण

#घोषणा finish_arch_post_lock_चयन finish_arch_post_lock_चयन
अटल अंतरभूत व्योम finish_arch_post_lock_चयन(व्योम)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा mm_काष्ठा *mm = tsk->mm;

	अगर (mm) अणु
		preempt_disable();
		जबतक (atomic_पढ़ो(&mm->context.flush_count))
			cpu_relax();
		cpumask_set_cpu(smp_processor_id(), mm_cpumask(mm));
		__tlb_flush_mm_lazy(mm);
		preempt_enable();
	पूर्ण
	__ctl_load(S390_lowcore.user_asce, 7, 7);
पूर्ण

#घोषणा activate_mm activate_mm
अटल अंतरभूत व्योम activate_mm(काष्ठा mm_काष्ठा *prev,
                               काष्ठा mm_काष्ठा *next)
अणु
	चयन_mm(prev, next, current);
	cpumask_set_cpu(smp_processor_id(), mm_cpumask(next));
	__ctl_load(S390_lowcore.user_asce, 7, 7);
पूर्ण

#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर /* __S390_MMU_CONTEXT_H */
