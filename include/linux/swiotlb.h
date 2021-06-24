<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_SWIOTLB_H
#घोषणा __LINUX_SWIOTLB_H

#समावेश <linux/dma-direction.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/spinlock.h>

काष्ठा device;
काष्ठा page;
काष्ठा scatterlist;

क्रमागत swiotlb_क्रमce अणु
	SWIOTLB_NORMAL,		/* Default - depending on HW DMA mask etc. */
	SWIOTLB_FORCE,		/* swiotlb=क्रमce */
	SWIOTLB_NO_FORCE,	/* swiotlb=noक्रमce */
पूर्ण;

/*
 * Maximum allowable number of contiguous sद_असल to map,
 * must be a घातer of 2.  What is the appropriate value ?
 * The complनिकासy of अणुmap,unmapपूर्ण_single is linearly dependent on this value.
 */
#घोषणा IO_TLB_SEGSIZE	128

/*
 * log of the size of each IO TLB slab.  The number of sद_असल is command line
 * controllable.
 */
#घोषणा IO_TLB_SHIFT 11
#घोषणा IO_TLB_SIZE (1 << IO_TLB_SHIFT)

/* शेष to 64MB */
#घोषणा IO_TLB_DEFAULT_SIZE (64UL<<20)

बाह्य व्योम swiotlb_init(पूर्णांक verbose);
पूर्णांक swiotlb_init_with_tbl(अक्षर *tlb, अचिन्हित दीर्घ nsद_असल, पूर्णांक verbose);
अचिन्हित दीर्घ swiotlb_size_or_शेष(व्योम);
बाह्य पूर्णांक swiotlb_late_init_with_tbl(अक्षर *tlb, अचिन्हित दीर्घ nsद_असल);
बाह्य पूर्णांक swiotlb_late_init_with_शेष_size(माप_प्रकार शेष_size);
बाह्य व्योम __init swiotlb_update_mem_attributes(व्योम);

phys_addr_t swiotlb_tbl_map_single(काष्ठा device *hwdev, phys_addr_t phys,
		माप_प्रकार mapping_size, माप_प्रकार alloc_size,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs);

बाह्य व्योम swiotlb_tbl_unmap_single(काष्ठा device *hwdev,
				     phys_addr_t tlb_addr,
				     माप_प्रकार mapping_size,
				     क्रमागत dma_data_direction dir,
				     अचिन्हित दीर्घ attrs);

व्योम swiotlb_sync_single_क्रम_device(काष्ठा device *dev, phys_addr_t tlb_addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir);
व्योम swiotlb_sync_single_क्रम_cpu(काष्ठा device *dev, phys_addr_t tlb_addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir);
dma_addr_t swiotlb_map(काष्ठा device *dev, phys_addr_t phys,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs);

#अगर_घोषित CONFIG_SWIOTLB
बाह्य क्रमागत swiotlb_क्रमce swiotlb_क्रमce;

/**
 * काष्ठा io_tlb_mem - IO TLB Memory Pool Descriptor
 *
 * @start:	The start address of the swiotlb memory pool. Used to करो a quick
 *		range check to see अगर the memory was in fact allocated by this
 *		API.
 * @end:	The end address of the swiotlb memory pool. Used to करो a quick
 *		range check to see अगर the memory was in fact allocated by this
 *		API.
 * @nsद_असल:	The number of IO TLB blocks (in groups of 64) between @start and
 *		@end. This is command line adjustable via setup_io_tlb_npages.
 * @used:	The number of used IO TLB block.
 * @list:	The मुक्त list describing the number of मुक्त entries available
 *		from each index.
 * @index:	The index to start searching in the next round.
 * @orig_addr:	The original address corresponding to a mapped entry.
 * @alloc_size:	Size of the allocated buffer.
 * @lock:	The lock to protect the above data काष्ठाures in the map and
 *		unmap calls.
 * @debugfs:	The dentry to debugfs.
 * @late_alloc:	%true अगर allocated using the page allocator
 */
काष्ठा io_tlb_mem अणु
	phys_addr_t start;
	phys_addr_t end;
	अचिन्हित दीर्घ nsद_असल;
	अचिन्हित दीर्घ used;
	अचिन्हित पूर्णांक index;
	spinlock_t lock;
	काष्ठा dentry *debugfs;
	bool late_alloc;
	काष्ठा io_tlb_slot अणु
		phys_addr_t orig_addr;
		माप_प्रकार alloc_size;
		अचिन्हित पूर्णांक list;
	पूर्ण slots[];
पूर्ण;
बाह्य काष्ठा io_tlb_mem *io_tlb_शेष_mem;

अटल अंतरभूत bool is_swiotlb_buffer(phys_addr_t paddr)
अणु
	काष्ठा io_tlb_mem *mem = io_tlb_शेष_mem;

	वापस mem && paddr >= mem->start && paddr < mem->end;
पूर्ण

व्योम __init swiotlb_निकास(व्योम);
अचिन्हित पूर्णांक swiotlb_max_segment(व्योम);
माप_प्रकार swiotlb_max_mapping_size(काष्ठा device *dev);
bool is_swiotlb_active(व्योम);
व्योम __init swiotlb_adjust_size(अचिन्हित दीर्घ size);
#अन्यथा
#घोषणा swiotlb_क्रमce SWIOTLB_NO_FORCE
अटल अंतरभूत bool is_swiotlb_buffer(phys_addr_t paddr)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम swiotlb_निकास(व्योम)
अणु
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक swiotlb_max_segment(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत माप_प्रकार swiotlb_max_mapping_size(काष्ठा device *dev)
अणु
	वापस SIZE_MAX;
पूर्ण

अटल अंतरभूत bool is_swiotlb_active(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम swiotlb_adjust_size(अचिन्हित दीर्घ size)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SWIOTLB */

बाह्य व्योम swiotlb_prपूर्णांक_info(व्योम);
बाह्य व्योम swiotlb_set_max_segment(अचिन्हित पूर्णांक);

#पूर्ण_अगर /* __LINUX_SWIOTLB_H */
