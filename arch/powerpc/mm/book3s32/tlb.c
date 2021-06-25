<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file contains the routines क्रम TLB flushing.
 * On machines where the MMU uses a hash table to store भव to
 * physical translations, these routines flush entries from the
 * hash table also.
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

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/tlb.h>

#समावेश <mm/mmu_decl.h>

/*
 * TLB flushing:
 *
 *  - flush_tlb_mm(mm) flushes the specअगरied mm context TLB's
 *  - flush_tlb_page(vma, vmaddr) flushes one page
 *  - flush_tlb_range(vma, start, end) flushes a range of pages
 *  - flush_tlb_kernel_range(start, end) flushes kernel pages
 *
 * since the hardware hash table functions as an extension of the
 * tlb as far as the linux tables are concerned, flush it too.
 *    -- Cort
 */

/*
 * For each address in the range, find the pte क्रम the address
 * and check _PAGE_HASHPTE bit; अगर it is set, find and destroy
 * the corresponding HPTE.
 */
व्योम hash__flush_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ pmd_end;
	पूर्णांक count;
	अचिन्हित पूर्णांक ctx = mm->context.id;

	start &= PAGE_MASK;
	अगर (start >= end)
		वापस;
	end = (end - 1) | ~PAGE_MASK;
	pmd = pmd_off(mm, start);
	क्रम (;;) अणु
		pmd_end = ((start + PGसूची_SIZE) & PGसूची_MASK) - 1;
		अगर (pmd_end > end)
			pmd_end = end;
		अगर (!pmd_none(*pmd)) अणु
			count = ((pmd_end - start) >> PAGE_SHIFT) + 1;
			flush_hash_pages(ctx, start, pmd_val(*pmd), count);
		पूर्ण
		अगर (pmd_end == end)
			अवरोध;
		start = pmd_end + 1;
		++pmd;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(hash__flush_range);

/*
 * Flush all the (user) entries क्रम the address space described by mm.
 */
व्योम hash__flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा vm_area_काष्ठा *mp;

	/*
	 * It is safe to go करोwn the mm's list of vmas when called
	 * from dup_mmap, holding mmap_lock.  It would also be safe from
	 * unmap_region or निकास_mmap, but not from vmtruncate on SMP -
	 * but it seems dup_mmap is the only SMP हाल which माला_लो here.
	 */
	क्रम (mp = mm->mmap; mp != शून्य; mp = mp->vm_next)
		hash__flush_range(mp->vm_mm, mp->vm_start, mp->vm_end);
पूर्ण
EXPORT_SYMBOL(hash__flush_tlb_mm);

व्योम hash__flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr)
अणु
	काष्ठा mm_काष्ठा *mm;
	pmd_t *pmd;

	mm = (vmaddr < TASK_SIZE)? vma->vm_mm: &init_mm;
	pmd = pmd_off(mm, vmaddr);
	अगर (!pmd_none(*pmd))
		flush_hash_pages(mm->context.id, vmaddr, pmd_val(*pmd), 1);
पूर्ण
EXPORT_SYMBOL(hash__flush_tlb_page);
