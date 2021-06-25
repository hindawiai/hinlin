<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */

#अगर_अघोषित _ASM_MICROBLAZE_MMU_CONTEXT_H
#घोषणा _ASM_MICROBLAZE_MMU_CONTEXT_H

#समावेश <linux/atomic.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/bitops.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र-generic/mm_hooks.h>

# अगरdef __KERNEL__
/*
 * This function defines the mapping from contexts to VSIDs (भव
 * segment IDs).  We use a skew on both the context and the high 4 bits
 * of the 32-bit भव address (the "effective segment ID") in order
 * to spपढ़ो out the entries in the MMU hash table.
 */
# define CTX_TO_VSID(ctx, va)	(((ctx) * (897 * 16) + ((va) >> 28) * 0x111) \
				 & 0xffffff)

/*
   MicroBlaze has 256 contexts, so we can just rotate through these
   as a way of "switching" contexts.  If the TID of the TLB is zero,
   the PID/TID comparison is disabled, so we can use a TID of zero
   to represent all kernel pages as shared among all contexts.
 */

# define NO_CONTEXT	256
# define LAST_CONTEXT	255
# define FIRST_CONTEXT	1

/*
 * Set the current MMU context.
 * This is करोne byloading up the segment रेजिस्टरs क्रम the user part of the
 * address space.
 *
 * Since the PGD is immediately available, it is much faster to simply
 * pass this aदीर्घ as a second parameter, which is required क्रम 8xx and
 * can be used क्रम debugging on all processors (अगर you happen to have
 * an Abatron).
 */
बाह्य व्योम set_context(mm_context_t context, pgd_t *pgd);

/*
 * Biपंचांगap of contexts in use.
 * The size of this biपंचांगap is LAST_CONTEXT + 1 bits.
 */
बाह्य अचिन्हित दीर्घ context_map[];

/*
 * This caches the next context number that we expect to be मुक्त.
 * Its use is an optimization only, we can't rely on this context
 * number to be मुक्त, but it usually will be.
 */
बाह्य mm_context_t next_mmu_context;

/*
 * Since we करोn't have sufficient contexts to give one to every task
 * that could be in the प्रणाली, we need to be able to steal contexts.
 * These variables support that.
 */
बाह्य atomic_t nr_मुक्त_contexts;
बाह्य काष्ठा mm_काष्ठा *context_mm[LAST_CONTEXT+1];
बाह्य व्योम steal_context(व्योम);

/*
 * Get a new mmu context क्रम the address space described by `mm'.
 */
अटल अंतरभूत व्योम get_mmu_context(काष्ठा mm_काष्ठा *mm)
अणु
	mm_context_t ctx;

	अगर (mm->context != NO_CONTEXT)
		वापस;
	जबतक (atomic_dec_अगर_positive(&nr_मुक्त_contexts) < 0)
		steal_context();
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
# define init_new_context(tsk, mm)	(((mm)->context = NO_CONTEXT), 0)

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

अटल अंतरभूत व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
			     काष्ठा task_काष्ठा *tsk)
अणु
	tsk->thपढ़ो.pgdir = next->pgd;
	get_mmu_context(next);
	set_context(next->context, next->pgd);
पूर्ण

/*
 * After we have set current->mm to a new value, this activates
 * the context क्रम the new mm so we see the new mappings.
 */
#घोषणा activate_mm activate_mm
अटल अंतरभूत व्योम activate_mm(काष्ठा mm_काष्ठा *active_mm,
			काष्ठा mm_काष्ठा *mm)
अणु
	current->thपढ़ो.pgdir = mm->pgd;
	get_mmu_context(mm);
	set_context(mm->context, mm->pgd);
पूर्ण

बाह्य व्योम mmu_context_init(व्योम);

#समावेश <यंत्र-generic/mmu_context.h>

# endअगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_MICROBLAZE_MMU_CONTEXT_H */
