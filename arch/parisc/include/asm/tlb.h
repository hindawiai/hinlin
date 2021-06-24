<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PARISC_TLB_H
#घोषणा _PARISC_TLB_H

#समावेश <यंत्र-generic/tlb.h>

#अगर CONFIG_PGTABLE_LEVELS == 3
#घोषणा __pmd_मुक्त_tlb(tlb, pmd, addr)	pmd_मुक्त((tlb)->mm, pmd)
#पूर्ण_अगर
#घोषणा __pte_मुक्त_tlb(tlb, pte, addr)	pte_मुक्त((tlb)->mm, pte)

#पूर्ण_अगर
