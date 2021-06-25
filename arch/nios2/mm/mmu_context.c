<शैली गुरु>
/*
 * MMU context handling.
 *
 * Copyright (C) 2011 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2009 Wind River Systems Inc
 *   Implemented by fredrik.markstrom@gmail.com and ivarholmqvist@gmail.com
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/mm.h>

#समावेश <यंत्र/cpuinfo.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlb.h>

/* The pids position and mask in context */
#घोषणा PID_SHIFT	0
#घोषणा PID_BITS	(cpuinfo.tlb_pid_num_bits)
#घोषणा PID_MASK	((1UL << PID_BITS) - 1)

/* The versions position and mask in context */
#घोषणा VERSION_BITS	(32 - PID_BITS)
#घोषणा VERSION_SHIFT	(PID_SHIFT + PID_BITS)
#घोषणा VERSION_MASK	((1UL << VERSION_BITS) - 1)

/* Return the version part of a context */
#घोषणा CTX_VERSION(c)	(((c) >> VERSION_SHIFT) & VERSION_MASK)

/* Return the pid part of a context */
#घोषणा CTX_PID(c)	(((c) >> PID_SHIFT) & PID_MASK)

/* Value of the first context (version 1, pid 0) */
#घोषणा FIRST_CTX	((1UL << VERSION_SHIFT) | (0 << PID_SHIFT))

अटल mm_context_t next_mmu_context;

/*
 * Initialize MMU context management stuff.
 */
व्योम __init mmu_context_init(व्योम)
अणु
	/* We need to set this here because the value depends on runसमय data
	 * from cpuinfo */
	next_mmu_context = FIRST_CTX;
पूर्ण

/*
 * Set new context (pid), keep way
 */
अटल व्योम set_context(mm_context_t context)
अणु
	set_mmu_pid(CTX_PID(context));
पूर्ण

अटल mm_context_t get_new_context(व्योम)
अणु
	/* Return the next pid */
	next_mmu_context += (1UL << PID_SHIFT);

	/* If the pid field wraps around we increase the version and
	 * flush the tlb */
	अगर (unlikely(CTX_PID(next_mmu_context) == 0)) अणु
		/* Version is incremented since the pid increment above
		 * overflows info version */
		flush_cache_all();
		flush_tlb_all();
	पूर्ण

	/* If the version wraps we start over with the first generation, we करो
	 * not need to flush the tlb here since it's always करोne above */
	अगर (unlikely(CTX_VERSION(next_mmu_context) == 0))
		next_mmu_context = FIRST_CTX;

	वापस next_mmu_context;
पूर्ण

व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
	       काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	/* If the process context we are swapping in has a dअगरferent context
	 * generation then we have it should get a new generation/pid */
	अगर (unlikely(CTX_VERSION(next->context) !=
		CTX_VERSION(next_mmu_context)))
		next->context = get_new_context();

	/* Save the current pgd so the fast tlb handler can find it */
	pgd_current = next->pgd;

	/* Set the current context */
	set_context(next->context);

	local_irq_restore(flags);
पूर्ण

/*
 * After we have set current->mm to a new value, this activates
 * the context क्रम the new mm so we see the new mappings.
 */
व्योम activate_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next)
अणु
	next->context = get_new_context();
	set_context(next->context);
	pgd_current = next->pgd;
पूर्ण

अचिन्हित दीर्घ get_pid_from_context(mm_context_t *context)
अणु
	वापस CTX_PID((*context));
पूर्ण
