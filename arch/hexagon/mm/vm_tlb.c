<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hexagon Virtual Machine TLB functions
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

/*
 * The Hexagon Virtual Machine conceals the real workings of
 * the TLB, but there are one or two functions that need to
 * be instantiated क्रम it, dअगरferently from a native build.
 */
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/hexagon_vm.h>

/*
 * Initial VM implementation has only one map active at a समय, with
 * TLB purgings on changes.  So either we're nuking the current map,
 * or it's a no-op.  This operation is messy on true SMPs where other
 * processors must be induced to flush the copies in their local TLBs,
 * but Hexagon thपढ़ो-based भव processors share the same MMU.
 */
व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			अचिन्हित दीर्घ end)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	अगर (mm->context.ptbase == current->active_mm->context.ptbase)
		__vmclrmap((व्योम *)start, end - start);
पूर्ण

/*
 * Flush a page from the kernel भव map - used by highmem
 */
व्योम flush_tlb_one(अचिन्हित दीर्घ vaddr)
अणु
	__vmclrmap((व्योम *)vaddr, PAGE_SIZE);
पूर्ण

/*
 * Flush all TLBs across all CPUs, भव or real.
 * A single Hexagon core has 6 thपढ़ो contexts but
 * only one TLB.
 */
व्योम tlb_flush_all(व्योम)
अणु
	/*  should probably use that fixaddr end or whateve label  */
	__vmclrmap(0, 0xffff0000);
पूर्ण

/*
 * Flush TLB entries associated with a given mm_काष्ठा mapping.
 */
व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	/* Current Virtual Machine has only one map active at a समय */
	अगर (current->active_mm->context.ptbase == mm->context.ptbase)
		tlb_flush_all();
पूर्ण

/*
 * Flush TLB state associated with a page of a vma.
 */
व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vaddr)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	अगर (mm->context.ptbase  == current->active_mm->context.ptbase)
		__vmclrmap((व्योम *)vaddr, PAGE_SIZE);
पूर्ण

/*
 * Flush TLB entries associated with a kernel address range.
 * Like flush range, but without the check on the vma->vm_mm.
 */
व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
		__vmclrmap((व्योम *)start, end - start);
पूर्ण
