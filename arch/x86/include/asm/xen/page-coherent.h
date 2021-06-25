<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_XEN_PAGE_COHERENT_H
#घोषणा _ASM_X86_XEN_PAGE_COHERENT_H

#समावेश <यंत्र/page.h>
#समावेश <linux/dma-mapping.h>

अटल अंतरभूत व्योम *xen_alloc_coherent_pages(काष्ठा device *hwdev, माप_प्रकार size,
		dma_addr_t *dma_handle, gfp_t flags,
		अचिन्हित दीर्घ attrs)
अणु
	व्योम *vstart = (व्योम*)__get_मुक्त_pages(flags, get_order(size));
	*dma_handle = virt_to_phys(vstart);
	वापस vstart;
पूर्ण

अटल अंतरभूत व्योम xen_मुक्त_coherent_pages(काष्ठा device *hwdev, माप_प्रकार size,
		व्योम *cpu_addr, dma_addr_t dma_handle,
		अचिन्हित दीर्घ attrs)
अणु
	मुक्त_pages((अचिन्हित दीर्घ) cpu_addr, get_order(size));
पूर्ण

#पूर्ण_अगर /* _ASM_X86_XEN_PAGE_COHERENT_H */
