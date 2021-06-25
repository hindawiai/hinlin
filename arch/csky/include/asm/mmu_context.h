<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_MMU_CONTEXT_H
#घोषणा __ASM_CSKY_MMU_CONTEXT_H

#समावेश <यंत्र-generic/mm_hooks.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <abi/ckmmu.h>

#घोषणा ASID_MASK		((1 << CONFIG_CPU_ASID_BITS) - 1)
#घोषणा cpu_asid(mm)		(atomic64_पढ़ो(&mm->context.asid) & ASID_MASK)

#घोषणा init_new_context(tsk,mm)	(अणु atomic64_set(&(mm)->context.asid, 0); 0; पूर्ण)

व्योम check_and_चयन_context(काष्ठा mm_काष्ठा *mm, अचिन्हित पूर्णांक cpu);

अटल अंतरभूत व्योम
चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
	  काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	अगर (prev != next)
		check_and_चयन_context(next, cpu);

	setup_pgd(next->pgd, next->context.asid.counter);

	flush_icache_deferred(next);
पूर्ण

#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर /* __ASM_CSKY_MMU_CONTEXT_H */
