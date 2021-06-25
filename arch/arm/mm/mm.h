<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_घोषित CONFIG_MMU
#समावेश <linux/list.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pgtable.h>

/* the upper-most page table poपूर्णांकer */
बाह्य pmd_t *top_pmd;

बाह्य पूर्णांक icache_size;

/*
 * 0xffff8000 to 0xffffffff is reserved क्रम any ARM architecture
 * specअगरic hacks क्रम copying pages efficiently, जबतक 0xffff4000
 * is reserved क्रम VIPT aliasing flushing by generic code.
 *
 * Note that we करोn't allow VIPT aliasing caches with SMP.
 */
#घोषणा COPYPAGE_MINICACHE	0xffff8000
#घोषणा COPYPAGE_V6_FROM	0xffff8000
#घोषणा COPYPAGE_V6_TO		0xffffc000
/* PFN alias flushing, क्रम VIPT caches */
#घोषणा FLUSH_ALIAS_START	0xffff4000

अटल अंतरभूत व्योम set_top_pte(अचिन्हित दीर्घ va, pte_t pte)
अणु
	pte_t *ptep = pte_offset_kernel(top_pmd, va);
	set_pte_ext(ptep, pte, 0);
	local_flush_tlb_kernel_page(va);
पूर्ण

अटल अंतरभूत pte_t get_top_pte(अचिन्हित दीर्घ va)
अणु
	pte_t *ptep = pte_offset_kernel(top_pmd, va);
	वापस *ptep;
पूर्ण

काष्ठा mem_type अणु
	pteval_t prot_pte;
	pteval_t prot_pte_s2;
	pmdval_t prot_l1;
	pmdval_t prot_sect;
	अचिन्हित पूर्णांक करोमुख्य;
पूर्ण;

स्थिर काष्ठा mem_type *get_mem_type(अचिन्हित पूर्णांक type);

बाह्य व्योम __flush_dcache_page(काष्ठा address_space *mapping, काष्ठा page *page);

/*
 * ARM specअगरic vm_काष्ठा->flags bits.
 */

/* (super)section-mapped I/O regions used by ioremap()/iounmap() */
#घोषणा VM_ARM_SECTION_MAPPING	0x80000000

/* permanent अटल mappings from iotable_init() */
#घोषणा VM_ARM_STATIC_MAPPING	0x40000000

/* empty mapping */
#घोषणा VM_ARM_EMPTY_MAPPING	0x20000000

/* mapping type (attributes) क्रम permanent अटल mappings */
#घोषणा VM_ARM_MTYPE(mt)		((mt) << 20)
#घोषणा VM_ARM_MTYPE_MASK	(0x1f << 20)


काष्ठा अटल_vm अणु
	काष्ठा vm_काष्ठा vm;
	काष्ठा list_head list;
पूर्ण;

बाह्य काष्ठा list_head अटल_vmlist;
बाह्य काष्ठा अटल_vm *find_अटल_vm_vaddr(व्योम *vaddr);
बाह्य __init व्योम add_अटल_vm_early(काष्ठा अटल_vm *svm);

#पूर्ण_अगर

#अगर_घोषित CONFIG_ZONE_DMA
बाह्य phys_addr_t arm_dma_limit;
बाह्य अचिन्हित दीर्घ arm_dma_pfn_limit;
#अन्यथा
#घोषणा arm_dma_limit ((phys_addr_t)~0)
#घोषणा arm_dma_pfn_limit (~0ul >> PAGE_SHIFT)
#पूर्ण_अगर

बाह्य phys_addr_t arm_lowmem_limit;

व्योम __init booपंचांगem_init(व्योम);
व्योम arm_mm_memblock_reserve(व्योम);
व्योम dma_contiguous_remap(व्योम);

अचिन्हित दीर्घ __clear_cr(अचिन्हित दीर्घ mask);
