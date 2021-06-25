<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2001 Mike Corrigan & Dave Engebretsen, IBM Corporation
 * Reग_लिखो, cleanup:
 * Copyright (C) 2004 Olof Johansson <olof@lixom.net>, IBM Corporation
 */

#अगर_अघोषित _ASM_IOMMU_H
#घोषणा _ASM_IOMMU_H
#अगर_घोषित __KERNEL__

#समावेश <linux/compiler.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/यंत्र-स्थिर.h>

#घोषणा IOMMU_PAGE_SHIFT_4K      12
#घोषणा IOMMU_PAGE_SIZE_4K       (ASM_CONST(1) << IOMMU_PAGE_SHIFT_4K)
#घोषणा IOMMU_PAGE_MASK_4K       (~((1 << IOMMU_PAGE_SHIFT_4K) - 1))
#घोषणा IOMMU_PAGE_ALIGN_4K(addr) ALIGN(addr, IOMMU_PAGE_SIZE_4K)

#घोषणा IOMMU_PAGE_SIZE(tblptr) (ASM_CONST(1) << (tblptr)->it_page_shअगरt)
#घोषणा IOMMU_PAGE_MASK(tblptr) (~((1 << (tblptr)->it_page_shअगरt) - 1))
#घोषणा IOMMU_PAGE_ALIGN(addr, tblptr) ALIGN(addr, IOMMU_PAGE_SIZE(tblptr))

/* Boot समय flags */
बाह्य पूर्णांक iommu_is_off;
बाह्य पूर्णांक iommu_क्रमce_on;

काष्ठा iommu_table_ops अणु
	/*
	 * When called with direction==DMA_NONE, it is equal to clear().
	 * uaddr is a linear map address.
	 */
	पूर्णांक (*set)(काष्ठा iommu_table *tbl,
			दीर्घ index, दीर्घ npages,
			अचिन्हित दीर्घ uaddr,
			क्रमागत dma_data_direction direction,
			अचिन्हित दीर्घ attrs);
#अगर_घोषित CONFIG_IOMMU_API
	/*
	 * Exchanges existing TCE with new TCE plus direction bits;
	 * वापसs old TCE and DMA direction mask.
	 * @tce is a physical address.
	 */
	पूर्णांक (*xchg_no_समाप्त)(काष्ठा iommu_table *tbl,
			दीर्घ index,
			अचिन्हित दीर्घ *hpa,
			क्रमागत dma_data_direction *direction,
			bool realmode);

	व्योम (*tce_समाप्त)(काष्ठा iommu_table *tbl,
			अचिन्हित दीर्घ index,
			अचिन्हित दीर्घ pages,
			bool realmode);

	__be64 *(*useraddrptr)(काष्ठा iommu_table *tbl, दीर्घ index, bool alloc);
#पूर्ण_अगर
	व्योम (*clear)(काष्ठा iommu_table *tbl,
			दीर्घ index, दीर्घ npages);
	/* get() वापसs a physical address */
	अचिन्हित दीर्घ (*get)(काष्ठा iommu_table *tbl, दीर्घ index);
	व्योम (*flush)(काष्ठा iommu_table *tbl);
	व्योम (*मुक्त)(काष्ठा iommu_table *tbl);
पूर्ण;

/* These are used by VIO */
बाह्य काष्ठा iommu_table_ops iommu_table_lpar_multi_ops;
बाह्य काष्ठा iommu_table_ops iommu_table_pseries_ops;

/*
 * IOMAP_MAX_ORDER defines the largest contiguous block
 * of dma space we can get.  IOMAP_MAX_ORDER = 13
 * allows up to 2**12 pages (4096 * 4096) = 16 MB
 */
#घोषणा IOMAP_MAX_ORDER		13

#घोषणा IOMMU_POOL_HASHBITS	2
#घोषणा IOMMU_NR_POOLS		(1 << IOMMU_POOL_HASHBITS)

काष्ठा iommu_pool अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ hपूर्णांक;
	spinlock_t lock;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा iommu_table अणु
	अचिन्हित दीर्घ  it_busno;     /* Bus number this table beदीर्घs to */
	अचिन्हित दीर्घ  it_size;      /* Size of iommu table in entries */
	अचिन्हित दीर्घ  it_indirect_levels;
	अचिन्हित दीर्घ  it_level_size;
	अचिन्हित दीर्घ  it_allocated_size;
	अचिन्हित दीर्घ  it_offset;    /* Offset पूर्णांकo global table */
	अचिन्हित दीर्घ  it_base;      /* mapped address of tce table */
	अचिन्हित दीर्घ  it_index;     /* which iommu table this is */
	अचिन्हित दीर्घ  it_type;      /* type: PCI or Virtual Bus */
	अचिन्हित दीर्घ  it_blocksize; /* Entries in each block (cacheline) */
	अचिन्हित दीर्घ  poolsize;
	अचिन्हित दीर्घ  nr_pools;
	काष्ठा iommu_pool large_pool;
	काष्ठा iommu_pool pools[IOMMU_NR_POOLS];
	अचिन्हित दीर्घ *it_map;       /* A simple allocation biपंचांगap क्रम now */
	अचिन्हित दीर्घ  it_page_shअगरt;/* table iommu page size */
	काष्ठा list_head it_group_list;/* List of iommu_table_group_link */
	__be64 *it_userspace; /* userspace view of the table */
	काष्ठा iommu_table_ops *it_ops;
	काष्ठा kref    it_kref;
	पूर्णांक it_nid;
	अचिन्हित दीर्घ it_reserved_start; /* Start of not-DMA-able (MMIO) area */
	अचिन्हित दीर्घ it_reserved_end;
पूर्ण;

#घोषणा IOMMU_TABLE_USERSPACE_ENTRY_RO(tbl, entry) \
		((tbl)->it_ops->useraddrptr((tbl), (entry), false))
#घोषणा IOMMU_TABLE_USERSPACE_ENTRY(tbl, entry) \
		((tbl)->it_ops->useraddrptr((tbl), (entry), true))

/* Pure 2^n version of get_order */
अटल अंतरभूत __attribute_स्थिर__
पूर्णांक get_iommu_order(अचिन्हित दीर्घ size, काष्ठा iommu_table *tbl)
अणु
	वापस __ilog2((size - 1) >> tbl->it_page_shअगरt) + 1;
पूर्ण


काष्ठा scatterlist;

#अगर_घोषित CONFIG_PPC64

अटल अंतरभूत व्योम set_iommu_table_base(काष्ठा device *dev,
					काष्ठा iommu_table *base)
अणु
	dev->archdata.iommu_table_base = base;
पूर्ण

अटल अंतरभूत व्योम *get_iommu_table_base(काष्ठा device *dev)
अणु
	वापस dev->archdata.iommu_table_base;
पूर्ण

बाह्य पूर्णांक dma_iommu_dma_supported(काष्ठा device *dev, u64 mask);

बाह्य काष्ठा iommu_table *iommu_tce_table_get(काष्ठा iommu_table *tbl);
बाह्य पूर्णांक iommu_tce_table_put(काष्ठा iommu_table *tbl);

/* Initializes an iommu_table based in values set in the passed-in
 * काष्ठाure
 */
बाह्य काष्ठा iommu_table *iommu_init_table(काष्ठा iommu_table *tbl,
		पूर्णांक nid, अचिन्हित दीर्घ res_start, अचिन्हित दीर्घ res_end);

#घोषणा IOMMU_TABLE_GROUP_MAX_TABLES	2

काष्ठा iommu_table_group;

काष्ठा iommu_table_group_ops अणु
	अचिन्हित दीर्घ (*get_table_size)(
			__u32 page_shअगरt,
			__u64 winकरोw_size,
			__u32 levels);
	दीर्घ (*create_table)(काष्ठा iommu_table_group *table_group,
			पूर्णांक num,
			__u32 page_shअगरt,
			__u64 winकरोw_size,
			__u32 levels,
			काष्ठा iommu_table **ptbl);
	दीर्घ (*set_winकरोw)(काष्ठा iommu_table_group *table_group,
			पूर्णांक num,
			काष्ठा iommu_table *tblnew);
	दीर्घ (*unset_winकरोw)(काष्ठा iommu_table_group *table_group,
			पूर्णांक num);
	/* Switch ownership from platक्रमm code to बाह्यal user (e.g. VFIO) */
	व्योम (*take_ownership)(काष्ठा iommu_table_group *table_group);
	/* Switch ownership from बाह्यal user (e.g. VFIO) back to core */
	व्योम (*release_ownership)(काष्ठा iommu_table_group *table_group);
पूर्ण;

काष्ठा iommu_table_group_link अणु
	काष्ठा list_head next;
	काष्ठा rcu_head rcu;
	काष्ठा iommu_table_group *table_group;
पूर्ण;

काष्ठा iommu_table_group अणु
	/* IOMMU properties */
	__u32 tce32_start;
	__u32 tce32_size;
	__u64 pgsizes; /* Biपंचांगap of supported page sizes */
	__u32 max_dynamic_winकरोws_supported;
	__u32 max_levels;

	काष्ठा iommu_group *group;
	काष्ठा iommu_table *tables[IOMMU_TABLE_GROUP_MAX_TABLES];
	काष्ठा iommu_table_group_ops *ops;
पूर्ण;

#अगर_घोषित CONFIG_IOMMU_API

बाह्य व्योम iommu_रेजिस्टर_group(काष्ठा iommu_table_group *table_group,
				 पूर्णांक pci_करोमुख्य_number, अचिन्हित दीर्घ pe_num);
बाह्य पूर्णांक iommu_add_device(काष्ठा iommu_table_group *table_group,
		काष्ठा device *dev);
बाह्य व्योम iommu_del_device(काष्ठा device *dev);
बाह्य दीर्घ iommu_tce_xchg(काष्ठा mm_काष्ठा *mm, काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry, अचिन्हित दीर्घ *hpa,
		क्रमागत dma_data_direction *direction);
बाह्य दीर्घ iommu_tce_xchg_no_समाप्त(काष्ठा mm_काष्ठा *mm,
		काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry, अचिन्हित दीर्घ *hpa,
		क्रमागत dma_data_direction *direction);
बाह्य व्योम iommu_tce_समाप्त(काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry, अचिन्हित दीर्घ pages);
#अन्यथा
अटल अंतरभूत व्योम iommu_रेजिस्टर_group(काष्ठा iommu_table_group *table_group,
					पूर्णांक pci_करोमुख्य_number,
					अचिन्हित दीर्घ pe_num)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक iommu_add_device(काष्ठा iommu_table_group *table_group,
		काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम iommu_del_device(काष्ठा device *dev)
अणु
पूर्ण
#पूर्ण_अगर /* !CONFIG_IOMMU_API */

u64 dma_iommu_get_required_mask(काष्ठा device *dev);
#अन्यथा

अटल अंतरभूत व्योम *get_iommu_table_base(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक dma_iommu_dma_supported(काष्ठा device *dev, u64 mask)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC64 */

बाह्य पूर्णांक ppc_iommu_map_sg(काष्ठा device *dev, काष्ठा iommu_table *tbl,
			    काष्ठा scatterlist *sglist, पूर्णांक nelems,
			    अचिन्हित दीर्घ mask,
			    क्रमागत dma_data_direction direction,
			    अचिन्हित दीर्घ attrs);
बाह्य व्योम ppc_iommu_unmap_sg(काष्ठा iommu_table *tbl,
			       काष्ठा scatterlist *sglist,
			       पूर्णांक nelems,
			       क्रमागत dma_data_direction direction,
			       अचिन्हित दीर्घ attrs);

बाह्य व्योम *iommu_alloc_coherent(काष्ठा device *dev, काष्ठा iommu_table *tbl,
				  माप_प्रकार size, dma_addr_t *dma_handle,
				  अचिन्हित दीर्घ mask, gfp_t flag, पूर्णांक node);
बाह्य व्योम iommu_मुक्त_coherent(काष्ठा iommu_table *tbl, माप_प्रकार size,
				व्योम *vaddr, dma_addr_t dma_handle);
बाह्य dma_addr_t iommu_map_page(काष्ठा device *dev, काष्ठा iommu_table *tbl,
				 काष्ठा page *page, अचिन्हित दीर्घ offset,
				 माप_प्रकार size, अचिन्हित दीर्घ mask,
				 क्रमागत dma_data_direction direction,
				 अचिन्हित दीर्घ attrs);
बाह्य व्योम iommu_unmap_page(काष्ठा iommu_table *tbl, dma_addr_t dma_handle,
			     माप_प्रकार size, क्रमागत dma_data_direction direction,
			     अचिन्हित दीर्घ attrs);

बाह्य व्योम iommu_init_early_pSeries(व्योम);
बाह्य व्योम iommu_init_early_dart(काष्ठा pci_controller_ops *controller_ops);
बाह्य व्योम iommu_init_early_pasemi(व्योम);

#अगर defined(CONFIG_PPC64) && defined(CONFIG_PM)
अटल अंतरभूत व्योम iommu_save(व्योम)
अणु
	अगर (ppc_md.iommu_save)
		ppc_md.iommu_save();
पूर्ण

अटल अंतरभूत व्योम iommu_restore(व्योम)
अणु
	अगर (ppc_md.iommu_restore)
		ppc_md.iommu_restore();
पूर्ण
#पूर्ण_अगर

/* The API to support IOMMU operations क्रम VFIO */
बाह्य पूर्णांक iommu_tce_check_ioba(अचिन्हित दीर्घ page_shअगरt,
		अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ ioba, अचिन्हित दीर्घ npages);
बाह्य पूर्णांक iommu_tce_check_gpa(अचिन्हित दीर्घ page_shअगरt,
		अचिन्हित दीर्घ gpa);

#घोषणा iommu_tce_clear_param_check(tbl, ioba, tce_value, npages) \
		(iommu_tce_check_ioba((tbl)->it_page_shअगरt,       \
				(tbl)->it_offset, (tbl)->it_size, \
				(ioba), (npages)) || (tce_value))
#घोषणा iommu_tce_put_param_check(tbl, ioba, gpa)                 \
		(iommu_tce_check_ioba((tbl)->it_page_shअगरt,       \
				(tbl)->it_offset, (tbl)->it_size, \
				(ioba), 1) ||                     \
		iommu_tce_check_gpa((tbl)->it_page_shअगरt, (gpa)))

बाह्य व्योम iommu_flush_tce(काष्ठा iommu_table *tbl);
बाह्य पूर्णांक iommu_take_ownership(काष्ठा iommu_table *tbl);
बाह्य व्योम iommu_release_ownership(काष्ठा iommu_table *tbl);

बाह्य क्रमागत dma_data_direction iommu_tce_direction(अचिन्हित दीर्घ tce);
बाह्य अचिन्हित दीर्घ iommu_direction_to_tce_perm(क्रमागत dma_data_direction dir);

#अगर_घोषित CONFIG_PPC_CELL_NATIVE
बाह्य bool iommu_fixed_is_weak;
#अन्यथा
#घोषणा iommu_fixed_is_weak false
#पूर्ण_अगर

बाह्य स्थिर काष्ठा dma_map_ops dma_iommu_ops;

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_IOMMU_H */
