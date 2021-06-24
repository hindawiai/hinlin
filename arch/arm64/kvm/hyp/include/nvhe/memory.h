<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __KVM_HYP_MEMORY_H
#घोषणा __KVM_HYP_MEMORY_H

#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/page.h>

#समावेश <linux/types.h>

काष्ठा hyp_pool;
काष्ठा hyp_page अणु
	अचिन्हित पूर्णांक refcount;
	अचिन्हित पूर्णांक order;
	काष्ठा hyp_pool *pool;
	काष्ठा list_head node;
पूर्ण;

बाह्य u64 __hyp_vmemmap;
#घोषणा hyp_vmemmap ((काष्ठा hyp_page *)__hyp_vmemmap)

#घोषणा __hyp_va(phys)	((व्योम *)((phys_addr_t)(phys) - hyp_physvirt_offset))

अटल अंतरभूत व्योम *hyp_phys_to_virt(phys_addr_t phys)
अणु
	वापस __hyp_va(phys);
पूर्ण

अटल अंतरभूत phys_addr_t hyp_virt_to_phys(व्योम *addr)
अणु
	वापस __hyp_pa(addr);
पूर्ण

#घोषणा hyp_phys_to_pfn(phys)	((phys) >> PAGE_SHIFT)
#घोषणा hyp_pfn_to_phys(pfn)	((phys_addr_t)((pfn) << PAGE_SHIFT))
#घोषणा hyp_phys_to_page(phys)	(&hyp_vmemmap[hyp_phys_to_pfn(phys)])
#घोषणा hyp_virt_to_page(virt)	hyp_phys_to_page(__hyp_pa(virt))
#घोषणा hyp_virt_to_pfn(virt)	hyp_phys_to_pfn(__hyp_pa(virt))

#घोषणा hyp_page_to_pfn(page)	((काष्ठा hyp_page *)(page) - hyp_vmemmap)
#घोषणा hyp_page_to_phys(page)  hyp_pfn_to_phys((hyp_page_to_pfn(page)))
#घोषणा hyp_page_to_virt(page)	__hyp_va(hyp_page_to_phys(page))
#घोषणा hyp_page_to_pool(page)	(((काष्ठा hyp_page *)page)->pool)

अटल अंतरभूत पूर्णांक hyp_page_count(व्योम *addr)
अणु
	काष्ठा hyp_page *p = hyp_virt_to_page(addr);

	वापस p->refcount;
पूर्ण

#पूर्ण_अगर /* __KVM_HYP_MEMORY_H */
