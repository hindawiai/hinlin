<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IOMMU_COMMON_H
#घोषणा _LINUX_IOMMU_COMMON_H

#समावेश <linux/spinlock_types.h>
#समावेश <linux/device.h>
#समावेश <यंत्र/page.h>

#घोषणा IOMMU_POOL_HASHBITS     4
#घोषणा IOMMU_NR_POOLS          (1 << IOMMU_POOL_HASHBITS)
#घोषणा IOMMU_ERROR_CODE	(~(अचिन्हित दीर्घ) 0)

काष्ठा iommu_pool अणु
	अचिन्हित दीर्घ	start;
	अचिन्हित दीर्घ	end;
	अचिन्हित दीर्घ	hपूर्णांक;
	spinlock_t	lock;
पूर्ण;

काष्ठा iommu_map_table अणु
	अचिन्हित दीर्घ		table_map_base;
	अचिन्हित दीर्घ		table_shअगरt;
	अचिन्हित दीर्घ		nr_pools;
	व्योम			(*lazy_flush)(काष्ठा iommu_map_table *);
	अचिन्हित दीर्घ		poolsize;
	काष्ठा iommu_pool	pools[IOMMU_NR_POOLS];
	u32			flags;
#घोषणा	IOMMU_HAS_LARGE_POOL	0x00000001
#घोषणा	IOMMU_NO_SPAN_BOUND	0x00000002
#घोषणा	IOMMU_NEED_FLUSH	0x00000004
	काष्ठा iommu_pool	large_pool;
	अचिन्हित दीर्घ		*map;
पूर्ण;

बाह्य व्योम iommu_tbl_pool_init(काष्ठा iommu_map_table *iommu,
				अचिन्हित दीर्घ num_entries,
				u32 table_shअगरt,
				व्योम (*lazy_flush)(काष्ठा iommu_map_table *),
				bool large_pool, u32 npools,
				bool skip_span_boundary_check);

बाह्य अचिन्हित दीर्घ iommu_tbl_range_alloc(काष्ठा device *dev,
					   काष्ठा iommu_map_table *iommu,
					   अचिन्हित दीर्घ npages,
					   अचिन्हित दीर्घ *handle,
					   अचिन्हित दीर्घ mask,
					   अचिन्हित पूर्णांक align_order);

बाह्य व्योम iommu_tbl_range_मुक्त(काष्ठा iommu_map_table *iommu,
				 u64 dma_addr, अचिन्हित दीर्घ npages,
				 अचिन्हित दीर्घ entry);

#पूर्ण_अगर
