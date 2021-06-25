<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  This file contains pgtable related functions क्रम 64-bit machines.
 *
 *  Derived from arch/ppc64/mm/init.c
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Modअगरications by Paul Mackerras (PowerMac) (paulus@samba.org)
 *  and Cort Dougan (PReP) (cort@cs.nmt.edu)
 *    Copyright (C) 1996 Paul Mackerras
 *
 *  Derived from "arch/i386/mm/init.c"
 *    Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 *
 *  Dave Engebretsen <engebret@us.ibm.com>
 *      Rework क्रम PPC64 port.
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/hugetlb.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/dma.h>

#समावेश <mm/mmu_decl.h>


#अगर_घोषित CONFIG_PPC_BOOK3S_64
/*
 * partition table and process table क्रम ISA 3.0
 */
काष्ठा prtb_entry *process_tb;
काष्ठा patb_entry *partition_tb;
/*
 * page table size
 */
अचिन्हित दीर्घ __pte_index_size;
EXPORT_SYMBOL(__pte_index_size);
अचिन्हित दीर्घ __pmd_index_size;
EXPORT_SYMBOL(__pmd_index_size);
अचिन्हित दीर्घ __pud_index_size;
EXPORT_SYMBOL(__pud_index_size);
अचिन्हित दीर्घ __pgd_index_size;
EXPORT_SYMBOL(__pgd_index_size);
अचिन्हित दीर्घ __pud_cache_index;
EXPORT_SYMBOL(__pud_cache_index);
अचिन्हित दीर्घ __pte_table_size;
EXPORT_SYMBOL(__pte_table_size);
अचिन्हित दीर्घ __pmd_table_size;
EXPORT_SYMBOL(__pmd_table_size);
अचिन्हित दीर्घ __pud_table_size;
EXPORT_SYMBOL(__pud_table_size);
अचिन्हित दीर्घ __pgd_table_size;
EXPORT_SYMBOL(__pgd_table_size);
अचिन्हित दीर्घ __pmd_val_bits;
EXPORT_SYMBOL(__pmd_val_bits);
अचिन्हित दीर्घ __pud_val_bits;
EXPORT_SYMBOL(__pud_val_bits);
अचिन्हित दीर्घ __pgd_val_bits;
EXPORT_SYMBOL(__pgd_val_bits);
अचिन्हित दीर्घ __kernel_virt_start;
EXPORT_SYMBOL(__kernel_virt_start);
अचिन्हित दीर्घ __vदो_स्मृति_start;
EXPORT_SYMBOL(__vदो_स्मृति_start);
अचिन्हित दीर्घ __vदो_स्मृति_end;
EXPORT_SYMBOL(__vदो_स्मृति_end);
अचिन्हित दीर्घ __kernel_io_start;
EXPORT_SYMBOL(__kernel_io_start);
अचिन्हित दीर्घ __kernel_io_end;
काष्ठा page *vmemmap;
EXPORT_SYMBOL(vmemmap);
अचिन्हित दीर्घ __pte_frag_nr;
EXPORT_SYMBOL(__pte_frag_nr);
अचिन्हित दीर्घ __pte_frag_size_shअगरt;
EXPORT_SYMBOL(__pte_frag_size_shअगरt);
#पूर्ण_अगर

#अगर_अघोषित __PAGETABLE_PUD_FOLDED
/* 4 level page table */
काष्ठा page *p4d_page(p4d_t p4d)
अणु
	अगर (p4d_is_leaf(p4d)) अणु
		VM_WARN_ON(!p4d_huge(p4d));
		वापस pte_page(p4d_pte(p4d));
	पूर्ण
	वापस virt_to_page(p4d_page_vaddr(p4d));
पूर्ण
#पूर्ण_अगर

काष्ठा page *pud_page(pud_t pud)
अणु
	अगर (pud_is_leaf(pud)) अणु
		VM_WARN_ON(!pud_huge(pud));
		वापस pte_page(pud_pte(pud));
	पूर्ण
	वापस virt_to_page(pud_page_vaddr(pud));
पूर्ण

/*
 * For hugepage we have pfn in the pmd, we use PTE_RPN_SHIFT bits क्रम flags
 * For PTE page, we have a PTE_FRAG_SIZE (4K) aligned भव address.
 */
काष्ठा page *pmd_page(pmd_t pmd)
अणु
	अगर (pmd_is_leaf(pmd)) अणु
		VM_WARN_ON(!(pmd_large(pmd) || pmd_huge(pmd)));
		वापस pte_page(pmd_pte(pmd));
	पूर्ण
	वापस virt_to_page(pmd_page_vaddr(pmd));
पूर्ण

#अगर_घोषित CONFIG_STRICT_KERNEL_RWX
व्योम mark_rodata_ro(व्योम)
अणु
	अगर (!mmu_has_feature(MMU_FTR_KERNEL_RO)) अणु
		pr_warn("Warning: Unable to mark rodata read only on this CPU.\n");
		वापस;
	पूर्ण

	अगर (radix_enabled())
		radix__mark_rodata_ro();
	अन्यथा
		hash__mark_rodata_ro();

	// mark_iniपंचांगem_nx() should have alपढ़ोy run by now
	ptdump_check_wx();
पूर्ण

व्योम mark_iniपंचांगem_nx(व्योम)
अणु
	अगर (radix_enabled())
		radix__mark_iniपंचांगem_nx();
	अन्यथा
		hash__mark_iniपंचांगem_nx();
पूर्ण
#पूर्ण_अगर
