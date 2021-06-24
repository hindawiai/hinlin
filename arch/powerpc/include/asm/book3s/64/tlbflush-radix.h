<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_TLBFLUSH_RADIX_H
#घोषणा _ASM_POWERPC_TLBFLUSH_RADIX_H

#समावेश <यंत्र/hvcall.h>

काष्ठा vm_area_काष्ठा;
काष्ठा mm_काष्ठा;
काष्ठा mmu_gather;

अटल अंतरभूत u64 pमाप_प्रकारo_rpti_pgsize(अचिन्हित दीर्घ psize)
अणु
	अगर (psize == MMU_PAGE_4K)
		वापस H_RPTI_PAGE_4K;
	अगर (psize == MMU_PAGE_64K)
		वापस H_RPTI_PAGE_64K;
	अगर (psize == MMU_PAGE_2M)
		वापस H_RPTI_PAGE_2M;
	अगर (psize == MMU_PAGE_1G)
		वापस H_RPTI_PAGE_1G;
	वापस H_RPTI_PAGE_ALL;
पूर्ण

अटल अंतरभूत पूर्णांक mmu_get_ap(पूर्णांक psize)
अणु
	वापस mmu_psize_defs[psize].ap;
पूर्ण

#अगर_घोषित CONFIG_PPC_RADIX_MMU
बाह्य व्योम radix__tlbiel_all(अचिन्हित पूर्णांक action);
बाह्य व्योम radix__flush_tlb_lpid_page(अचिन्हित पूर्णांक lpid,
					अचिन्हित दीर्घ addr,
					अचिन्हित दीर्घ page_size);
बाह्य व्योम radix__flush_pwc_lpid(अचिन्हित पूर्णांक lpid);
बाह्य व्योम radix__flush_all_lpid(अचिन्हित पूर्णांक lpid);
बाह्य व्योम radix__flush_all_lpid_guest(अचिन्हित पूर्णांक lpid);
#अन्यथा
अटल अंतरभूत व्योम radix__tlbiel_all(अचिन्हित पूर्णांक action) अणु WARN_ON(1); पूर्ण
अटल अंतरभूत व्योम radix__flush_tlb_lpid_page(अचिन्हित पूर्णांक lpid,
					अचिन्हित दीर्घ addr,
					अचिन्हित दीर्घ page_size)
अणु
	WARN_ON(1);
पूर्ण
अटल अंतरभूत व्योम radix__flush_pwc_lpid(अचिन्हित पूर्णांक lpid)
अणु
	WARN_ON(1);
पूर्ण
अटल अंतरभूत व्योम radix__flush_all_lpid(अचिन्हित पूर्णांक lpid)
अणु
	WARN_ON(1);
पूर्ण
अटल अंतरभूत व्योम radix__flush_all_lpid_guest(अचिन्हित पूर्णांक lpid)
अणु
	WARN_ON(1);
पूर्ण
#पूर्ण_अगर

बाह्य व्योम radix__flush_hugetlb_tlb_range(काष्ठा vm_area_काष्ठा *vma,
					   अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम radix__flush_tlb_range_psize(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
					 अचिन्हित दीर्घ end, पूर्णांक psize);
बाह्य व्योम radix__flush_pmd_tlb_range(काष्ठा vm_area_काष्ठा *vma,
				       अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम radix__flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			    अचिन्हित दीर्घ end);
बाह्य व्योम radix__flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

बाह्य व्योम radix__local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम radix__local_flush_all_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम radix__local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr);
बाह्य व्योम radix__local_flush_tlb_page_psize(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr,
					      पूर्णांक psize);
बाह्य व्योम radix__tlb_flush(काष्ठा mmu_gather *tlb);
#अगर_घोषित CONFIG_SMP
बाह्य व्योम radix__flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम radix__flush_all_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम radix__flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr);
बाह्य व्योम radix__flush_tlb_page_psize(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr,
					पूर्णांक psize);
#अन्यथा
#घोषणा radix__flush_tlb_mm(mm)		radix__local_flush_tlb_mm(mm)
#घोषणा radix__flush_all_mm(mm)		radix__local_flush_all_mm(mm)
#घोषणा radix__flush_tlb_page(vma,addr)	radix__local_flush_tlb_page(vma,addr)
#घोषणा radix__flush_tlb_page_psize(mm,addr,p) radix__local_flush_tlb_page_psize(mm,addr,p)
#पूर्ण_अगर
बाह्य व्योम radix__flush_tlb_pwc(काष्ठा mmu_gather *tlb, अचिन्हित दीर्घ addr);
बाह्य व्योम radix__flush_tlb_collapsed_pmd(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);
बाह्य व्योम radix__flush_tlb_all(व्योम);

#पूर्ण_अगर
