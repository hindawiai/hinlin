<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * MM context support क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_MMU_CONTEXT_H
#घोषणा _ASM_MMU_CONTEXT_H

#समावेश <linux/mm_types.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/mem-layout.h>

/*
 * VM port hides all TLB management, so "lazy TLB" isn't very
 * meaningful.  Even क्रम ports to architectures with visble TLBs,
 * this is almost invariably a null function.
 *
 * mm->context is set up by pgd_alloc, so no init_new_context required.
 */

/*
 *  Switch active mm context
 */
अटल अंतरभूत व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
				काष्ठा task_काष्ठा *tsk)
अणु
	पूर्णांक l1;

	/*
	 * For भव machine, we have to update प्रणाली map अगर it's been
	 * touched.
	 */
	अगर (next->context.generation < prev->context.generation) अणु
		क्रम (l1 = MIN_KERNEL_SEG; l1 <= max_kernel_seg; l1++)
			next->pgd[l1] = init_mm.pgd[l1];

		next->context.generation = prev->context.generation;
	पूर्ण

	__vmnewmap((व्योम *)next->context.ptbase);
पूर्ण

/*
 *  Activate new memory map क्रम task
 */
#घोषणा activate_mm activate_mm
अटल अंतरभूत व्योम activate_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	चयन_mm(prev, next, current_thपढ़ो_info()->task);
	local_irq_restore(flags);
पूर्ण

/*  Generic hooks क्रम arch_dup_mmap and arch_निकास_mmap  */
#समावेश <यंत्र-generic/mm_hooks.h>

#समावेश <यंत्र-generic/mmu_context.h>

#पूर्ण_अगर
