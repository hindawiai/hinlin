<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015-2018 Etnaviv Project
 */

#अगर_अघोषित __ETNAVIV_MMU_H__
#घोषणा __ETNAVIV_MMU_H__

#घोषणा ETNAVIV_PROT_READ	(1 << 0)
#घोषणा ETNAVIV_PROT_WRITE	(1 << 1)

क्रमागत etnaviv_iommu_version अणु
	ETNAVIV_IOMMU_V1 = 0,
	ETNAVIV_IOMMU_V2,
पूर्ण;

काष्ठा etnaviv_gpu;
काष्ठा etnaviv_vram_mapping;
काष्ठा etnaviv_iommu_global;
काष्ठा etnaviv_iommu_context;

काष्ठा etnaviv_iommu_ops अणु
	काष्ठा etnaviv_iommu_context *(*init)(काष्ठा etnaviv_iommu_global *);
	व्योम (*मुक्त)(काष्ठा etnaviv_iommu_context *);
	पूर्णांक (*map)(काष्ठा etnaviv_iommu_context *context, अचिन्हित दीर्घ iova,
		   phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot);
	माप_प्रकार (*unmap)(काष्ठा etnaviv_iommu_context *context, अचिन्हित दीर्घ iova,
			माप_प्रकार size);
	माप_प्रकार (*dump_size)(काष्ठा etnaviv_iommu_context *);
	व्योम (*dump)(काष्ठा etnaviv_iommu_context *, व्योम *);
	व्योम (*restore)(काष्ठा etnaviv_gpu *, काष्ठा etnaviv_iommu_context *);
पूर्ण;

बाह्य स्थिर काष्ठा etnaviv_iommu_ops etnaviv_iommuv1_ops;
बाह्य स्थिर काष्ठा etnaviv_iommu_ops etnaviv_iommuv2_ops;

#घोषणा ETNAVIV_PTA_SIZE	SZ_4K
#घोषणा ETNAVIV_PTA_ENTRIES	(ETNAVIV_PTA_SIZE / माप(u64))

काष्ठा etnaviv_iommu_global अणु
	काष्ठा device *dev;
	क्रमागत etnaviv_iommu_version version;
	स्थिर काष्ठा etnaviv_iommu_ops *ops;
	अचिन्हित पूर्णांक use;
	काष्ठा mutex lock;

	व्योम *bad_page_cpu;
	dma_addr_t bad_page_dma;

	u32 memory_base;

	/*
	 * This जोड़ holds members needed by either MMUv1 or MMUv2, which
	 * can not exist at the same समय.
	 */
	जोड़ अणु
		काष्ठा अणु
			काष्ठा etnaviv_iommu_context *shared_context;
		पूर्ण v1;
		काष्ठा अणु
			/* P(age) T(able) A(rray) */
			u64 *pta_cpu;
			dma_addr_t pta_dma;
			काष्ठा spinlock pta_lock;
			DECLARE_BITMAP(pta_alloc, ETNAVIV_PTA_ENTRIES);
		पूर्ण v2;
	पूर्ण;
पूर्ण;

काष्ठा etnaviv_iommu_context अणु
	काष्ठा kref refcount;
	काष्ठा etnaviv_iommu_global *global;

	/* memory manager क्रम GPU address area */
	काष्ठा mutex lock;
	काष्ठा list_head mappings;
	काष्ठा drm_mm mm;
	अचिन्हित पूर्णांक flush_seq;

	/* Not part of the context, but needs to have the same lअगरeसमय */
	काष्ठा etnaviv_vram_mapping cmdbuf_mapping;
पूर्ण;

पूर्णांक etnaviv_iommu_global_init(काष्ठा etnaviv_gpu *gpu);
व्योम etnaviv_iommu_global_fini(काष्ठा etnaviv_gpu *gpu);

काष्ठा etnaviv_gem_object;

पूर्णांक etnaviv_iommu_map_gem(काष्ठा etnaviv_iommu_context *context,
	काष्ठा etnaviv_gem_object *etnaviv_obj, u32 memory_base,
	काष्ठा etnaviv_vram_mapping *mapping, u64 va);
व्योम etnaviv_iommu_unmap_gem(काष्ठा etnaviv_iommu_context *context,
	काष्ठा etnaviv_vram_mapping *mapping);

पूर्णांक etnaviv_iommu_get_suballoc_va(काष्ठा etnaviv_iommu_context *ctx,
				  काष्ठा etnaviv_vram_mapping *mapping,
				  u32 memory_base, dma_addr_t paddr,
				  माप_प्रकार size);
व्योम etnaviv_iommu_put_suballoc_va(काष्ठा etnaviv_iommu_context *ctx,
				   काष्ठा etnaviv_vram_mapping *mapping);

माप_प्रकार etnaviv_iommu_dump_size(काष्ठा etnaviv_iommu_context *ctx);
व्योम etnaviv_iommu_dump(काष्ठा etnaviv_iommu_context *ctx, व्योम *buf);

काष्ठा etnaviv_iommu_context *
etnaviv_iommu_context_init(काष्ठा etnaviv_iommu_global *global,
			   काष्ठा etnaviv_cmdbuf_suballoc *suballoc);
अटल अंतरभूत व्योम etnaviv_iommu_context_get(काष्ठा etnaviv_iommu_context *ctx)
अणु
	kref_get(&ctx->refcount);
पूर्ण
व्योम etnaviv_iommu_context_put(काष्ठा etnaviv_iommu_context *ctx);
व्योम etnaviv_iommu_restore(काष्ठा etnaviv_gpu *gpu,
			   काष्ठा etnaviv_iommu_context *ctx);

काष्ठा etnaviv_iommu_context *
etnaviv_iommuv1_context_alloc(काष्ठा etnaviv_iommu_global *global);
काष्ठा etnaviv_iommu_context *
etnaviv_iommuv2_context_alloc(काष्ठा etnaviv_iommu_global *global);

u32 etnaviv_iommuv2_get_mtlb_addr(काष्ठा etnaviv_iommu_context *context);
अचिन्हित लघु etnaviv_iommuv2_get_pta_id(काष्ठा etnaviv_iommu_context *context);

#पूर्ण_अगर /* __ETNAVIV_MMU_H__ */
