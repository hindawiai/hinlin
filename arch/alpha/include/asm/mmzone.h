<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Written by Kanoj Sarcar (kanoj@sgi.com) Aug 99
 * Adapted क्रम the alpha wildfire architecture Jan 2001.
 */
#अगर_अघोषित _ASM_MMZONE_H_
#घोषणा _ASM_MMZONE_H_

#अगर_घोषित CONFIG_DISCONTIGMEM

#समावेश <यंत्र/smp.h>

/*
 * Following are macros that are specअगरic to this numa platक्रमm.
 */

बाह्य pg_data_t node_data[];

#घोषणा alpha_pa_to_nid(pa)		\
        (alpha_mv.pa_to_nid 		\
	 ? alpha_mv.pa_to_nid(pa)	\
	 : (0))
#घोषणा node_mem_start(nid)		\
        (alpha_mv.node_mem_start 	\
	 ? alpha_mv.node_mem_start(nid) \
	 : (0UL))
#घोषणा node_mem_size(nid)		\
        (alpha_mv.node_mem_size 	\
	 ? alpha_mv.node_mem_size(nid) 	\
	 : ((nid) ? (0UL) : (~0UL)))

#घोषणा pa_to_nid(pa)		alpha_pa_to_nid(pa)
#घोषणा NODE_DATA(nid)		(&node_data[(nid)])

#घोषणा node_localnr(pfn, nid)	((pfn) - NODE_DATA(nid)->node_start_pfn)

#अगर 1
#घोषणा PLAT_NODE_DATA_LOCALNR(p, n)	\
	(((p) >> PAGE_SHIFT) - PLAT_NODE_DATA(n)->gendata.node_start_pfn)
#अन्यथा
अटल अंतरभूत अचिन्हित दीर्घ
PLAT_NODE_DATA_LOCALNR(अचिन्हित दीर्घ p, पूर्णांक n)
अणु
	अचिन्हित दीर्घ temp;
	temp = p >> PAGE_SHIFT;
	वापस temp - PLAT_NODE_DATA(n)->gendata.node_start_pfn;
पूर्ण
#पूर्ण_अगर

/*
 * Following are macros that each numa implementation must define.
 */

/*
 * Given a kernel address, find the home node of the underlying memory.
 */
#घोषणा kvaddr_to_nid(kaddr)	pa_to_nid(__pa(kaddr))

/*
 * Given a kaddr, LOCAL_BASE_ADDR finds the owning node of the memory
 * and वापसs the kaddr corresponding to first physical page in the
 * node's mem_map.
 */
#घोषणा LOCAL_BASE_ADDR(kaddr)						  \
    ((अचिन्हित दीर्घ)__va(NODE_DATA(kvaddr_to_nid(kaddr))->node_start_pfn  \
			 << PAGE_SHIFT))

/* XXX: FIXME -- nyc */
#घोषणा kern_addr_valid(kaddr)	(0)

#घोषणा mk_pte(page, pgprot)						     \
(अणु								 	     \
	pte_t pte;                                                           \
	अचिन्हित दीर्घ pfn;                                                   \
									     \
	pfn = page_to_pfn(page) << 32; \
	pte_val(pte) = pfn | pgprot_val(pgprot);			     \
									     \
	pte;								     \
पूर्ण)

#घोषणा pte_page(x)							\
(अणु									\
       	अचिन्हित दीर्घ kvirt;						\
	काष्ठा page * __xx;						\
									\
	kvirt = (अचिन्हित दीर्घ)__va(pte_val(x) >> (32-PAGE_SHIFT));	\
	__xx = virt_to_page(kvirt);					\
									\
	__xx;                                                           \
पूर्ण)

#घोषणा pfn_to_nid(pfn)		pa_to_nid(((u64)(pfn) << PAGE_SHIFT))
#घोषणा pfn_valid(pfn)							\
	(((pfn) - node_start_pfn(pfn_to_nid(pfn))) <			\
	 node_spanned_pages(pfn_to_nid(pfn)))					\

#पूर्ण_अगर /* CONFIG_DISCONTIGMEM */

#पूर्ण_अगर /* _ASM_MMZONE_H_ */
