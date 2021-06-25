<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PARISC_MMU_CONTEXT_H
#घोषणा __PARISC_MMU_CONTEXT_H

#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/atomic.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र-generic/mm_hooks.h>

/* on PA-RISC, we actually have enough contexts to justअगरy an allocator
 * क्रम them.  prumpf */

बाह्य अचिन्हित दीर्घ alloc_sid(व्योम);
बाह्य व्योम मुक्त_sid(अचिन्हित दीर्घ);

#घोषणा init_new_context init_new_context
अटल अंतरभूत पूर्णांक
init_new_context(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm)
अणु
	BUG_ON(atomic_पढ़ो(&mm->mm_users) != 1);

	mm->context = alloc_sid();
	वापस 0;
पूर्ण

#घोषणा destroy_context destroy_context
अटल अंतरभूत व्योम
destroy_context(काष्ठा mm_काष्ठा *mm)
अणु
	मुक्त_sid(mm->context);
	mm->context = 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __space_to_prot(mm_context_t context)
अणु
#अगर SPACEID_SHIFT == 0
	वापस context << 1;
#अन्यथा
	वापस context >> (SPACEID_SHIFT - 1);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम load_context(mm_context_t context)
अणु
	mtsp(context, 3);
	mtctl(__space_to_prot(context), 8);
पूर्ण

अटल अंतरभूत व्योम चयन_mm_irqs_off(काष्ठा mm_काष्ठा *prev,
		काष्ठा mm_काष्ठा *next, काष्ठा task_काष्ठा *tsk)
अणु
	अगर (prev != next) अणु
#अगर_घोषित CONFIG_TLB_PTLOCK
		/* put physical address of page_table_lock in cr28 (tr4)
		   क्रम TLB faults */
		spinlock_t *pgd_lock = &next->page_table_lock;
		mtctl(__pa(__ldcw_align(&pgd_lock->rlock.raw_lock)), 28);
#पूर्ण_अगर
		mtctl(__pa(next->pgd), 25);
		load_context(next->context);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम चयन_mm(काष्ठा mm_काष्ठा *prev,
		काष्ठा mm_काष्ठा *next, काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ flags;

	अगर (prev == next)
		वापस;

	local_irq_save(flags);
	चयन_mm_irqs_off(prev, next, tsk);
	local_irq_restore(flags);
पूर्ण
#घोषणा चयन_mm_irqs_off चयन_mm_irqs_off

#घोषणा activate_mm activate_mm
अटल अंतरभूत व्योम activate_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next)
अणु
	/*
	 * Activate_mm is our one chance to allocate a space id
	 * क्रम a new mm created in the exec path. There's also
	 * some lazy tlb stuff, which is currently dead code, but
	 * we only allocate a space id अगर one hasn't been allocated
	 * alपढ़ोy, so we should be OK.
	 */

	BUG_ON(next == &init_mm); /* Should never happen */

	अगर (next->context == 0)
	    next->context = alloc_sid();

	चयन_mm(prev,next,current);
पूर्ण

#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर
