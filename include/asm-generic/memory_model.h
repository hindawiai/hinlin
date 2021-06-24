<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MEMORY_MODEL_H
#घोषणा __ASM_MEMORY_MODEL_H

#समावेश <linux/pfn.h>

#अगर_अघोषित __ASSEMBLY__

#अगर defined(CONFIG_FLATMEM)

#अगर_अघोषित ARCH_PFN_OFFSET
#घोषणा ARCH_PFN_OFFSET		(0UL)
#पूर्ण_अगर

#या_अगर defined(CONFIG_DISCONTIGMEM)

#अगर_अघोषित arch_pfn_to_nid
#घोषणा arch_pfn_to_nid(pfn)	pfn_to_nid(pfn)
#पूर्ण_अगर

#अगर_अघोषित arch_local_page_offset
#घोषणा arch_local_page_offset(pfn, nid)	\
	((pfn) - NODE_DATA(nid)->node_start_pfn)
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_DISCONTIGMEM */

/*
 * supports 3 memory models.
 */
#अगर defined(CONFIG_FLATMEM)

#घोषणा __pfn_to_page(pfn)	(mem_map + ((pfn) - ARCH_PFN_OFFSET))
#घोषणा __page_to_pfn(page)	((अचिन्हित दीर्घ)((page) - mem_map) + \
				 ARCH_PFN_OFFSET)
#या_अगर defined(CONFIG_DISCONTIGMEM)

#घोषणा __pfn_to_page(pfn)			\
(अणु	अचिन्हित दीर्घ __pfn = (pfn);		\
	अचिन्हित दीर्घ __nid = arch_pfn_to_nid(__pfn);  \
	NODE_DATA(__nid)->node_mem_map + arch_local_page_offset(__pfn, __nid);\
पूर्ण)

#घोषणा __page_to_pfn(pg)						\
(अणु	स्थिर काष्ठा page *__pg = (pg);					\
	काष्ठा pglist_data *__pgdat = NODE_DATA(page_to_nid(__pg));	\
	(अचिन्हित दीर्घ)(__pg - __pgdat->node_mem_map) +			\
	 __pgdat->node_start_pfn;					\
पूर्ण)

#या_अगर defined(CONFIG_SPARSEMEM_VMEMMAP)

/* memmap is भवly contiguous.  */
#घोषणा __pfn_to_page(pfn)	(vmemmap + (pfn))
#घोषणा __page_to_pfn(page)	(अचिन्हित दीर्घ)((page) - vmemmap)

#या_अगर defined(CONFIG_SPARSEMEM)
/*
 * Note: section's mem_map is encoded to reflect its start_pfn.
 * section[i].section_mem_map == mem_map's address - start_pfn;
 */
#घोषणा __page_to_pfn(pg)					\
(अणु	स्थिर काष्ठा page *__pg = (pg);				\
	पूर्णांक __sec = page_to_section(__pg);			\
	(अचिन्हित दीर्घ)(__pg - __section_mem_map_addr(__nr_to_section(__sec)));	\
पूर्ण)

#घोषणा __pfn_to_page(pfn)				\
(अणु	अचिन्हित दीर्घ __pfn = (pfn);			\
	काष्ठा mem_section *__sec = __pfn_to_section(__pfn);	\
	__section_mem_map_addr(__sec) + __pfn;		\
पूर्ण)
#पूर्ण_अगर /* CONFIG_FLATMEM/DISCONTIGMEM/SPARSEMEM */

/*
 * Convert a physical address to a Page Frame Number and back
 */
#घोषणा	__phys_to_pfn(paddr)	PHYS_PFN(paddr)
#घोषणा	__pfn_to_phys(pfn)	PFN_PHYS(pfn)

#घोषणा page_to_pfn __page_to_pfn
#घोषणा pfn_to_page __pfn_to_page

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर
