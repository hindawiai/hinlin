<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _XEN_ARM_PAGE_COHERENT_H
#घोषणा _XEN_ARM_PAGE_COHERENT_H

#समावेश <linux/dma-mapping.h>
#समावेश <यंत्र/page.h>

अटल अंतरभूत व्योम *xen_alloc_coherent_pages(काष्ठा device *hwdev, माप_प्रकार size,
		dma_addr_t *dma_handle, gfp_t flags, अचिन्हित दीर्घ attrs)
अणु
	वापस dma_direct_alloc(hwdev, size, dma_handle, flags, attrs);
पूर्ण

अटल अंतरभूत व्योम xen_मुक्त_coherent_pages(काष्ठा device *hwdev, माप_प्रकार size,
		व्योम *cpu_addr, dma_addr_t dma_handle, अचिन्हित दीर्घ attrs)
अणु
	dma_direct_मुक्त(hwdev, size, cpu_addr, dma_handle, attrs);
पूर्ण

#पूर्ण_अगर /* _XEN_ARM_PAGE_COHERENT_H */
