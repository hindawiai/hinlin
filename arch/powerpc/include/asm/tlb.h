<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	TLB shootकरोwn specअगरics क्रम घातerpc
 *
 * Copyright (C) 2002 Anton Blanअक्षरd, IBM Corp.
 * Copyright (C) 2002 Paul Mackerras, IBM Corp.
 */
#अगर_अघोषित _ASM_POWERPC_TLB_H
#घोषणा _ASM_POWERPC_TLB_H
#अगर_घोषित __KERNEL__

#अगर_अघोषित __घातerpc64__
#समावेश <linux/pgtable.h>
#पूर्ण_अगर
#अगर_अघोषित __घातerpc64__
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmu.h>
#पूर्ण_अगर

#समावेश <linux/pagemap.h>

#घोषणा tlb_start_vma(tlb, vma)	करो अणु पूर्ण जबतक (0)
#घोषणा tlb_end_vma(tlb, vma)	करो अणु पूर्ण जबतक (0)
#घोषणा __tlb_हटाओ_tlb_entry	__tlb_हटाओ_tlb_entry

#घोषणा tlb_flush tlb_flush
बाह्य व्योम tlb_flush(काष्ठा mmu_gather *tlb);
/*
 * book3s:
 * Hash करोes not use the linux page-tables, so we can aव्योम
 * the TLB invalidate क्रम page-table मुक्तing, Radix otoh करोes use the
 * page-tables and needs the TLBI.
 *
 * nohash:
 * We still करो TLB invalidate in the __pte_मुक्त_tlb routine beक्रमe we
 * add the page table pages to mmu gather table batch.
 */
#घोषणा tlb_needs_table_invalidate()	radix_enabled()

/* Get the generic bits... */
#समावेश <यंत्र-generic/tlb.h>

अटल अंतरभूत व्योम __tlb_हटाओ_tlb_entry(काष्ठा mmu_gather *tlb, pte_t *ptep,
					  अचिन्हित दीर्घ address)
अणु
#अगर_घोषित CONFIG_PPC_BOOK3S_32
	अगर (pte_val(*ptep) & _PAGE_HASHPTE)
		flush_hash_entry(tlb->mm, ptep, address);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल अंतरभूत पूर्णांक mm_is_core_local(काष्ठा mm_काष्ठा *mm)
अणु
	वापस cpumask_subset(mm_cpumask(mm),
			      topology_sibling_cpumask(smp_processor_id()));
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64
अटल अंतरभूत पूर्णांक mm_is_thपढ़ो_local(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (atomic_पढ़ो(&mm->context.active_cpus) > 1)
		वापस false;
	वापस cpumask_test_cpu(smp_processor_id(), mm_cpumask(mm));
पूर्ण
#अन्यथा /* CONFIG_PPC_BOOK3S_64 */
अटल अंतरभूत पूर्णांक mm_is_thपढ़ो_local(काष्ठा mm_काष्ठा *mm)
अणु
	वापस cpumask_equal(mm_cpumask(mm),
			      cpumask_of(smp_processor_id()));
पूर्ण
#पूर्ण_अगर /* !CONFIG_PPC_BOOK3S_64 */

#अन्यथा /* CONFIG_SMP */
अटल अंतरभूत पूर्णांक mm_is_core_local(काष्ठा mm_काष्ठा *mm)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक mm_is_thपढ़ो_local(काष्ठा mm_काष्ठा *mm)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __ASM_POWERPC_TLB_H */
