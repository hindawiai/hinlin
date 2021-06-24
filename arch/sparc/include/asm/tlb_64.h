<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_TLB_H
#घोषणा _SPARC64_TLB_H

#समावेश <linux/swap.h>
#समावेश <linux/pagemap.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/mmu_context.h>

#अगर_घोषित CONFIG_SMP
व्योम smp_flush_tlb_pending(काष्ठा mm_काष्ठा *,
				  अचिन्हित दीर्घ, अचिन्हित दीर्घ *);
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
व्योम smp_flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
#घोषणा करो_flush_tlb_mm(mm) smp_flush_tlb_mm(mm)
#अन्यथा
#घोषणा करो_flush_tlb_mm(mm) __flush_tlb_mm(CTX_HWBITS(mm->context), SECONDARY_CONTEXT)
#पूर्ण_अगर

व्योम __flush_tlb_pending(अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ *);
व्योम flush_tlb_pending(व्योम);

#घोषणा tlb_start_vma(tlb, vma) करो अणु पूर्ण जबतक (0)
#घोषणा tlb_end_vma(tlb, vma)	करो अणु पूर्ण जबतक (0)
#घोषणा tlb_flush(tlb)	flush_tlb_pending()

/*
 * SPARC64's hardware TLB fill करोes not use the Linux page-tables
 * and thereक्रमe we करोn't need a TLBI when मुक्तing page-table pages.
 */

#अगर_घोषित CONFIG_MMU_GATHER_RCU_TABLE_FREE
#घोषणा tlb_needs_table_invalidate()	(false)
#पूर्ण_अगर

#समावेश <यंत्र-generic/tlb.h>

#पूर्ण_अगर /* _SPARC64_TLB_H */
