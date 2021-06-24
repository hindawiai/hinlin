<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/sh/mm/nommu.c
 *
 * Various helper routines and stubs क्रम MMUless SH.
 *
 * Copyright (C) 2002 - 2009 Paul Mundt
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/page.h>
#समावेश <linux/uaccess.h>

/*
 * Nothing too terribly exciting here ..
 */
व्योम copy_page(व्योम *to, व्योम *from)
अणु
	स_नकल(to, from, PAGE_SIZE);
पूर्ण

__kernel_माप_प्रकार __copy_user(व्योम *to, स्थिर व्योम *from, __kernel_माप_प्रकार n)
अणु
	स_नकल(to, from, n);
	वापस 0;
पूर्ण

__kernel_माप_प्रकार __clear_user(व्योम *to, __kernel_माप_प्रकार n)
अणु
	स_रखो(to, 0, n);
	वापस 0;
पूर्ण

व्योम local_flush_tlb_all(व्योम)
अणु
	BUG();
पूर्ण

व्योम local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	BUG();
पूर्ण

व्योम local_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			    अचिन्हित दीर्घ end)
अणु
	BUG();
पूर्ण

व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page)
अणु
	BUG();
पूर्ण

व्योम local_flush_tlb_one(अचिन्हित दीर्घ asid, अचिन्हित दीर्घ page)
अणु
	BUG();
पूर्ण

व्योम local_flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	BUG();
पूर्ण

व्योम __flush_tlb_global(व्योम)
अणु
पूर्ण

व्योम __update_tlb(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address, pte_t pte)
अणु
पूर्ण

व्योम __init kmap_coherent_init(व्योम)
अणु
पूर्ण

व्योम *kmap_coherent(काष्ठा page *page, अचिन्हित दीर्घ addr)
अणु
	BUG();
	वापस शून्य;
पूर्ण

व्योम kunmap_coherent(व्योम *kvaddr)
अणु
	BUG();
पूर्ण

व्योम __init page_table_range_init(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				  pgd_t *pgd_base)
अणु
पूर्ण

व्योम __set_fixmap(क्रमागत fixed_addresses idx, अचिन्हित दीर्घ phys, pgprot_t prot)
अणु
पूर्ण
