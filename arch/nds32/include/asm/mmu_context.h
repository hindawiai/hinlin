<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित __ASM_NDS32_MMU_CONTEXT_H
#घोषणा __ASM_NDS32_MMU_CONTEXT_H

#समावेश <linux/spinlock.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र-generic/mm_hooks.h>

#घोषणा init_new_context init_new_context
अटल अंतरभूत पूर्णांक
init_new_context(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm)
अणु
	mm->context.id = 0;
	वापस 0;
पूर्ण

#घोषणा CID_BITS	9
बाह्य spinlock_t cid_lock;
बाह्य अचिन्हित पूर्णांक cpu_last_cid;

अटल अंतरभूत व्योम __new_context(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित पूर्णांक cid;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cid_lock, flags);
	cid = cpu_last_cid;
	cpu_last_cid += 1 << TLB_MISC_offCID;
	अगर (cpu_last_cid == 0)
		cpu_last_cid = 1 << TLB_MISC_offCID << CID_BITS;

	अगर ((cid & TLB_MISC_mskCID) == 0)
		flush_tlb_all();
	spin_unlock_irqrestore(&cid_lock, flags);

	mm->context.id = cid;
पूर्ण

अटल अंतरभूत व्योम check_context(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (unlikely
	    ((mm->context.id ^ cpu_last_cid) >> TLB_MISC_offCID >> CID_BITS))
		__new_context(mm);
पूर्ण

अटल अंतरभूत व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
			     काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	अगर (!cpumask_test_and_set_cpu(cpu, mm_cpumask(next)) || prev != next) अणु
		check_context(next);
		cpu_चयन_mm(next);
	पूर्ण
पूर्ण

#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर
