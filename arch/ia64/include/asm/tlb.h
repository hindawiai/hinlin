<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_TLB_H
#घोषणा _ASM_IA64_TLB_H
/*
 * Based on <यंत्र-generic/tlb.h>.
 *
 * Copyright (C) 2002-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */
/*
 * Removing a translation from a page table (including TLB-shootकरोwn) is a four-step
 * procedure:
 *
 *	(1) Flush (भव) caches --- ensures भव memory is coherent with kernel memory
 *	    (this is a no-op on ia64).
 *	(2) Clear the relevant portions of the page-table
 *	(3) Flush the TLBs --- ensures that stale content is gone from CPU TLBs
 *	(4) Release the pages that were मुक्तd up in step (2).
 *
 * Note that the ordering of these steps is crucial to aव्योम races on MP machines.
 *
 * The Linux kernel defines several platक्रमm-specअगरic hooks क्रम TLB-shootकरोwn.  When
 * unmapping a portion of the भव address space, these hooks are called according to
 * the following ढाँचा:
 *
 *	tlb <- tlb_gather_mmu(mm);			// start unmap क्रम address space MM
 *	अणु
 *	  क्रम each vma that needs a shootकरोwn करो अणु
 *	    tlb_start_vma(tlb, vma);
 *	      क्रम each page-table-entry PTE that needs to be हटाओd करो अणु
 *		tlb_हटाओ_tlb_entry(tlb, pte, address);
 *		अगर (pte refers to a normal page) अणु
 *		  tlb_हटाओ_page(tlb, page);
 *		पूर्ण
 *	      पूर्ण
 *	    tlb_end_vma(tlb, vma);
 *	  पूर्ण
 *	पूर्ण
 *	tlb_finish_mmu(tlb);				// finish unmap क्रम address space MM
 */
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश <यंत्र-generic/tlb.h>

#पूर्ण_अगर /* _ASM_IA64_TLB_H */
