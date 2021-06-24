<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file contains the routines क्रम handling the MMU on those
 * PowerPC implementations where the MMU substantially follows the
 * architecture specअगरication.  This includes the 6xx, 7xx, 7xxx,
 * and 8260 implementations but excludes the 8xx and 4xx.
 *  -- paulus
 *
 *  Derived from arch/ppc/mm/init.c:
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Modअगरications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)
 *  and Cort Dougan (PReP) (cort@cs.nmt.edu)
 *    Copyright (C) 1996 Paul Mackerras
 *
 *  Derived from "arch/i386/mm/init.c"
 *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 */

#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/mmu_context.h>

/*
 * On 32-bit PowerPC 6xx/7xx/7xxx CPUs, we use a set of 16 VSIDs
 * (भव segment identअगरiers) क्रम each context.  Although the
 * hardware supports 24-bit VSIDs, and thus >1 million contexts,
 * we only use 32,768 of them.  That is ample, since there can be
 * at most around 30,000 tasks in the प्रणाली anyway, and it means
 * that we can use a biपंचांगap to indicate which contexts are in use.
 * Using a biपंचांगap means that we entirely aव्योम all of the problems
 * that we used to have when the context number overflowed,
 * particularly on SMP प्रणालीs.
 *  -- paulus.
 */
#घोषणा NO_CONTEXT      	((अचिन्हित दीर्घ) -1)
#घोषणा LAST_CONTEXT    	32767
#घोषणा FIRST_CONTEXT    	1

/*
 * This function defines the mapping from contexts to VSIDs (भव
 * segment IDs).  We use a skew on both the context and the high 4 bits
 * of the 32-bit भव address (the "effective segment ID") in order
 * to spपढ़ो out the entries in the MMU hash table.  Note, अगर this
 * function is changed then arch/ppc/mm/hashtable.S will have to be
 * changed to correspond.
 *
 *
 * CTX_TO_VSID(ctx, va)	(((ctx) * (897 * 16) + ((va) >> 28) * 0x111) \
 *				 & 0xffffff)
 */

अटल अचिन्हित दीर्घ next_mmu_context;
अटल अचिन्हित दीर्घ context_map[LAST_CONTEXT / BITS_PER_LONG + 1];

अचिन्हित दीर्घ __init_new_context(व्योम)
अणु
	अचिन्हित दीर्घ ctx = next_mmu_context;

	जबतक (test_and_set_bit(ctx, context_map)) अणु
		ctx = find_next_zero_bit(context_map, LAST_CONTEXT+1, ctx);
		अगर (ctx > LAST_CONTEXT)
			ctx = 0;
	पूर्ण
	next_mmu_context = (ctx + 1) & LAST_CONTEXT;

	वापस ctx;
पूर्ण
EXPORT_SYMBOL_GPL(__init_new_context);

/*
 * Set up the context क्रम a new address space.
 */
पूर्णांक init_new_context(काष्ठा task_काष्ठा *t, काष्ठा mm_काष्ठा *mm)
अणु
	mm->context.id = __init_new_context();

	वापस 0;
पूर्ण

/*
 * Free a context ID. Make sure to call this with preempt disabled!
 */
व्योम __destroy_context(अचिन्हित दीर्घ ctx)
अणु
	clear_bit(ctx, context_map);
पूर्ण
EXPORT_SYMBOL_GPL(__destroy_context);

/*
 * We're finished using the context क्रम an address space.
 */
व्योम destroy_context(काष्ठा mm_काष्ठा *mm)
अणु
	preempt_disable();
	अगर (mm->context.id != NO_CONTEXT) अणु
		__destroy_context(mm->context.id);
		mm->context.id = NO_CONTEXT;
	पूर्ण
	preempt_enable();
पूर्ण

/*
 * Initialize the context management stuff.
 */
व्योम __init mmu_context_init(व्योम)
अणु
	/* Reserve context 0 क्रम kernel use */
	context_map[0] = (1 << FIRST_CONTEXT) - 1;
	next_mmu_context = FIRST_CONTEXT;
पूर्ण
