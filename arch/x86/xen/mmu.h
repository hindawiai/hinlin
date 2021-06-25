<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _XEN_MMU_H

#समावेश <linux/linkage.h>
#समावेश <यंत्र/page.h>

क्रमागत pt_level अणु
	PT_PGD,
	PT_P4D,
	PT_PUD,
	PT_PMD,
	PT_PTE
पूर्ण;


bool __set_phys_to_machine(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ mfn);

व्योम set_pte_mfn(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ pfn, pgprot_t flags);

pte_t xen_ptep_modअगरy_prot_start(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr, pte_t *ptep);
व्योम  xen_ptep_modअगरy_prot_commit(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
				  pte_t *ptep, pte_t pte);

अचिन्हित दीर्घ xen_पढ़ो_cr2_direct(व्योम);

बाह्य व्योम xen_init_mmu_ops(व्योम);
बाह्य व्योम xen_hvm_init_mmu_ops(व्योम);
#पूर्ण_अगर	/* _XEN_MMU_H */
