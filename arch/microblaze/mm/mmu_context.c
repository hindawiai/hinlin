<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file contains the routines क्रम handling the MMU.
 *
 *    Copyright (C) 2007 Xilinx, Inc.  All rights reserved.
 *
 *  Derived from arch/ppc/mm/4xx_mmu.c:
 *  -- paulus
 *
 *  Derived from arch/ppc/mm/init.c:
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Modअगरications by Paul Mackerras (PowerMac) (paulus@cs.anu.edu.au)
 *  and Cort Dougan (PReP) (cort@cs.nmt.edu)
 *    Copyright (C) 1996 Paul Mackerras
 *  Amiga/APUS changes by Jesper Skov (jskov@cygnus.co.uk).
 *
 *  Derived from "arch/i386/mm/init.c"
 *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 */

#समावेश <linux/mm.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mmu_context.h>

mm_context_t next_mmu_context;
अचिन्हित दीर्घ context_map[LAST_CONTEXT / BITS_PER_LONG + 1];
atomic_t nr_मुक्त_contexts;
काष्ठा mm_काष्ठा *context_mm[LAST_CONTEXT+1];

/*
 * Initialize the context management stuff.
 */
व्योम __init mmu_context_init(व्योम)
अणु
	/*
	 * The use of context zero is reserved क्रम the kernel.
	 * This code assumes FIRST_CONTEXT < 32.
	 */
	context_map[0] = (1 << FIRST_CONTEXT) - 1;
	next_mmu_context = FIRST_CONTEXT;
	atomic_set(&nr_मुक्त_contexts, LAST_CONTEXT - FIRST_CONTEXT + 1);
पूर्ण

/*
 * Steal a context from a task that has one at the moment.
 *
 * This isn't an LRU प्रणाली, it just मुक्तs up each context in
 * turn (sort-of pseuकरो-अक्रमom replacement :).  This would be the
 * place to implement an LRU scheme अगर anyone were motivated to करो it.
 */
व्योम steal_context(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm;

	/* मुक्त up context `next_mmu_context' */
	/* अगर we shouldn't free context 0, don't... */
	अगर (next_mmu_context < FIRST_CONTEXT)
		next_mmu_context = FIRST_CONTEXT;
	mm = context_mm[next_mmu_context];
	flush_tlb_mm(mm);
	destroy_context(mm);
पूर्ण
