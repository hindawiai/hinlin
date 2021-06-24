<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018 The Linux Foundation. All rights reserved. */

#समावेश <linux/dma-mapping.h>

#समावेश "msm_drv.h"
#समावेश "msm_mmu.h"
#समावेश "adreno/adreno_gpu.h"
#समावेश "adreno/a2xx.xml.h"

काष्ठा msm_gpummu अणु
	काष्ठा msm_mmu base;
	काष्ठा msm_gpu *gpu;
	dma_addr_t pt_base;
	uपूर्णांक32_t *table;
पूर्ण;
#घोषणा to_msm_gpummu(x) container_of(x, काष्ठा msm_gpummu, base)

#घोषणा GPUMMU_VA_START SZ_16M
#घोषणा GPUMMU_VA_RANGE (0xfff * SZ_64K)
#घोषणा GPUMMU_PAGE_SIZE SZ_4K
#घोषणा TABLE_SIZE (माप(uपूर्णांक32_t) * GPUMMU_VA_RANGE / GPUMMU_PAGE_SIZE)

अटल व्योम msm_gpummu_detach(काष्ठा msm_mmu *mmu)
अणु
पूर्ण

अटल पूर्णांक msm_gpummu_map(काष्ठा msm_mmu *mmu, uपूर्णांक64_t iova,
		काष्ठा sg_table *sgt, माप_प्रकार len, पूर्णांक prot)
अणु
	काष्ठा msm_gpummu *gpummu = to_msm_gpummu(mmu);
	अचिन्हित idx = (iova - GPUMMU_VA_START) / GPUMMU_PAGE_SIZE;
	काष्ठा sg_dma_page_iter dma_iter;
	अचिन्हित prot_bits = 0;

	अगर (prot & IOMMU_WRITE)
		prot_bits |= 1;
	अगर (prot & IOMMU_READ)
		prot_bits |= 2;

	क्रम_each_sgtable_dma_page(sgt, &dma_iter, 0) अणु
		dma_addr_t addr = sg_page_iter_dma_address(&dma_iter);
		पूर्णांक i;

		क्रम (i = 0; i < PAGE_SIZE; i += GPUMMU_PAGE_SIZE)
			gpummu->table[idx++] = (addr + i) | prot_bits;
	पूर्ण

	/* we can improve by deferring flush क्रम multiple map() */
	gpu_ग_लिखो(gpummu->gpu, REG_A2XX_MH_MMU_INVALIDATE,
		A2XX_MH_MMU_INVALIDATE_INVALIDATE_ALL |
		A2XX_MH_MMU_INVALIDATE_INVALIDATE_TC);
	वापस 0;
पूर्ण

अटल पूर्णांक msm_gpummu_unmap(काष्ठा msm_mmu *mmu, uपूर्णांक64_t iova, माप_प्रकार len)
अणु
	काष्ठा msm_gpummu *gpummu = to_msm_gpummu(mmu);
	अचिन्हित idx = (iova - GPUMMU_VA_START) / GPUMMU_PAGE_SIZE;
	अचिन्हित i;

	क्रम (i = 0; i < len / GPUMMU_PAGE_SIZE; i++, idx++)
                gpummu->table[idx] = 0;

	gpu_ग_लिखो(gpummu->gpu, REG_A2XX_MH_MMU_INVALIDATE,
		A2XX_MH_MMU_INVALIDATE_INVALIDATE_ALL |
		A2XX_MH_MMU_INVALIDATE_INVALIDATE_TC);
	वापस 0;
पूर्ण

अटल व्योम msm_gpummu_destroy(काष्ठा msm_mmu *mmu)
अणु
	काष्ठा msm_gpummu *gpummu = to_msm_gpummu(mmu);

	dma_मुक्त_attrs(mmu->dev, TABLE_SIZE, gpummu->table, gpummu->pt_base,
		DMA_ATTR_FORCE_CONTIGUOUS);

	kमुक्त(gpummu);
पूर्ण

अटल स्थिर काष्ठा msm_mmu_funcs funcs = अणु
		.detach = msm_gpummu_detach,
		.map = msm_gpummu_map,
		.unmap = msm_gpummu_unmap,
		.destroy = msm_gpummu_destroy,
पूर्ण;

काष्ठा msm_mmu *msm_gpummu_new(काष्ठा device *dev, काष्ठा msm_gpu *gpu)
अणु
	काष्ठा msm_gpummu *gpummu;

	gpummu = kzalloc(माप(*gpummu), GFP_KERNEL);
	अगर (!gpummu)
		वापस ERR_PTR(-ENOMEM);

	gpummu->table = dma_alloc_attrs(dev, TABLE_SIZE + 32, &gpummu->pt_base,
		GFP_KERNEL | __GFP_ZERO, DMA_ATTR_FORCE_CONTIGUOUS);
	अगर (!gpummu->table) अणु
		kमुक्त(gpummu);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	gpummu->gpu = gpu;
	msm_mmu_init(&gpummu->base, dev, &funcs, MSM_MMU_GPUMMU);

	वापस &gpummu->base;
पूर्ण

व्योम msm_gpummu_params(काष्ठा msm_mmu *mmu, dma_addr_t *pt_base,
		dma_addr_t *tran_error)
अणु
	dma_addr_t base = to_msm_gpummu(mmu)->pt_base;

	*pt_base = base;
	*tran_error = base + TABLE_SIZE; /* 32-byte aligned */
पूर्ण
