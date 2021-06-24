<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_TLB_H
#घोषणा __ASM_SH_TLB_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/pagemap.h>
#समावेश <यंत्र-generic/tlb.h>

#अगर_घोषित CONFIG_MMU
#समावेश <linux/swap.h>

#अगर defined(CONFIG_CPU_SH4)
बाह्य व्योम tlb_wire_entry(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ, pte_t);
बाह्य व्योम tlb_unwire_entry(व्योम);
#अन्यथा
अटल अंतरभूत व्योम tlb_wire_entry(काष्ठा vm_area_काष्ठा *vma ,
				  अचिन्हित दीर्घ addr, pte_t pte)
अणु
	BUG();
पूर्ण

अटल अंतरभूत व्योम tlb_unwire_entry(व्योम)
अणु
	BUG();
पूर्ण
#पूर्ण_अगर /* CONFIG_CPU_SH4 */
#पूर्ण_अगर /* CONFIG_MMU */
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_SH_TLB_H */
