<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_PGTABLE_H
#घोषणा _ASM_POWERPC_BOOK3S_PGTABLE_H

#अगर_घोषित CONFIG_PPC64
#समावेश <यंत्र/book3s/64/pgtable.h>
#अन्यथा
#समावेश <यंत्र/book3s/32/pgtable.h>
#पूर्ण_अगर

#घोषणा FIRST_USER_ADDRESS	0UL
#अगर_अघोषित __ASSEMBLY__
/* Insert a PTE, top-level function is out of line. It uses an अंतरभूत
 * low level function in the respective pgtable-* files
 */
बाह्य व्योम set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep,
		       pte_t pte);


#घोषणा __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
बाह्य पूर्णांक ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
				 pte_t *ptep, pte_t entry, पूर्णांक dirty);

काष्ठा file;
बाह्य pgprot_t phys_mem_access_prot(काष्ठा file *file, अचिन्हित दीर्घ pfn,
				     अचिन्हित दीर्घ size, pgprot_t vma_prot);
#घोषणा __HAVE_PHYS_MEM_ACCESS_PROT

/*
 * This माला_लो called at the end of handling a page fault, when
 * the kernel has put a new PTE पूर्णांकo the page table क्रम the process.
 * We use it to ensure coherency between the i-cache and d-cache
 * क्रम the page which has just been mapped in.
 * On machines which use an MMU hash table, we use this to put a
 * corresponding HPTE पूर्णांकo the hash table ahead of समय, instead of
 * रुकोing क्रम the inevitable extra hash-table miss exception.
 */
व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address, pte_t *ptep);

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर
