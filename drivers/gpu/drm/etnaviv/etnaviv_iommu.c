<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014-2018 Etnaviv Project
 */

#समावेश <linux/bitops.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>

#समावेश "etnaviv_gpu.h"
#समावेश "etnaviv_mmu.h"
#समावेश "state_hi.xml.h"

#घोषणा PT_SIZE		SZ_2M
#घोषणा PT_ENTRIES	(PT_SIZE / माप(u32))

#घोषणा GPU_MEM_START	0x80000000

काष्ठा etnaviv_iommuv1_context अणु
	काष्ठा etnaviv_iommu_context base;
	u32 *pgtable_cpu;
	dma_addr_t pgtable_dma;
पूर्ण;

अटल काष्ठा etnaviv_iommuv1_context *
to_v1_context(काष्ठा etnaviv_iommu_context *context)
अणु
	वापस container_of(context, काष्ठा etnaviv_iommuv1_context, base);
पूर्ण

अटल व्योम etnaviv_iommuv1_मुक्त(काष्ठा etnaviv_iommu_context *context)
अणु
	काष्ठा etnaviv_iommuv1_context *v1_context = to_v1_context(context);

	drm_mm_takeकरोwn(&context->mm);

	dma_मुक्त_wc(context->global->dev, PT_SIZE, v1_context->pgtable_cpu,
		    v1_context->pgtable_dma);

	context->global->v1.shared_context = शून्य;

	kमुक्त(v1_context);
पूर्ण

अटल पूर्णांक etnaviv_iommuv1_map(काष्ठा etnaviv_iommu_context *context,
			       अचिन्हित दीर्घ iova, phys_addr_t paddr,
			       माप_प्रकार size, पूर्णांक prot)
अणु
	काष्ठा etnaviv_iommuv1_context *v1_context = to_v1_context(context);
	अचिन्हित पूर्णांक index = (iova - GPU_MEM_START) / SZ_4K;

	अगर (size != SZ_4K)
		वापस -EINVAL;

	v1_context->pgtable_cpu[index] = paddr;

	वापस 0;
पूर्ण

अटल माप_प्रकार etnaviv_iommuv1_unmap(काष्ठा etnaviv_iommu_context *context,
	अचिन्हित दीर्घ iova, माप_प्रकार size)
अणु
	काष्ठा etnaviv_iommuv1_context *v1_context = to_v1_context(context);
	अचिन्हित पूर्णांक index = (iova - GPU_MEM_START) / SZ_4K;

	अगर (size != SZ_4K)
		वापस -EINVAL;

	v1_context->pgtable_cpu[index] = context->global->bad_page_dma;

	वापस SZ_4K;
पूर्ण

अटल माप_प्रकार etnaviv_iommuv1_dump_size(काष्ठा etnaviv_iommu_context *context)
अणु
	वापस PT_SIZE;
पूर्ण

अटल व्योम etnaviv_iommuv1_dump(काष्ठा etnaviv_iommu_context *context,
				 व्योम *buf)
अणु
	काष्ठा etnaviv_iommuv1_context *v1_context = to_v1_context(context);

	स_नकल(buf, v1_context->pgtable_cpu, PT_SIZE);
पूर्ण

अटल व्योम etnaviv_iommuv1_restore(काष्ठा etnaviv_gpu *gpu,
			     काष्ठा etnaviv_iommu_context *context)
अणु
	काष्ठा etnaviv_iommuv1_context *v1_context = to_v1_context(context);
	u32 pgtable;

	/* set base addresses */
	gpu_ग_लिखो(gpu, VIVS_MC_MEMORY_BASE_ADDR_RA, context->global->memory_base);
	gpu_ग_लिखो(gpu, VIVS_MC_MEMORY_BASE_ADDR_FE, context->global->memory_base);
	gpu_ग_लिखो(gpu, VIVS_MC_MEMORY_BASE_ADDR_TX, context->global->memory_base);
	gpu_ग_लिखो(gpu, VIVS_MC_MEMORY_BASE_ADDR_PEZ, context->global->memory_base);
	gpu_ग_लिखो(gpu, VIVS_MC_MEMORY_BASE_ADDR_PE, context->global->memory_base);

	/* set page table address in MC */
	pgtable = (u32)v1_context->pgtable_dma;

	gpu_ग_लिखो(gpu, VIVS_MC_MMU_FE_PAGE_TABLE, pgtable);
	gpu_ग_लिखो(gpu, VIVS_MC_MMU_TX_PAGE_TABLE, pgtable);
	gpu_ग_लिखो(gpu, VIVS_MC_MMU_PE_PAGE_TABLE, pgtable);
	gpu_ग_लिखो(gpu, VIVS_MC_MMU_PEZ_PAGE_TABLE, pgtable);
	gpu_ग_लिखो(gpu, VIVS_MC_MMU_RA_PAGE_TABLE, pgtable);
पूर्ण


स्थिर काष्ठा etnaviv_iommu_ops etnaviv_iommuv1_ops = अणु
	.मुक्त = etnaviv_iommuv1_मुक्त,
	.map = etnaviv_iommuv1_map,
	.unmap = etnaviv_iommuv1_unmap,
	.dump_size = etnaviv_iommuv1_dump_size,
	.dump = etnaviv_iommuv1_dump,
	.restore = etnaviv_iommuv1_restore,
पूर्ण;

काष्ठा etnaviv_iommu_context *
etnaviv_iommuv1_context_alloc(काष्ठा etnaviv_iommu_global *global)
अणु
	काष्ठा etnaviv_iommuv1_context *v1_context;
	काष्ठा etnaviv_iommu_context *context;

	mutex_lock(&global->lock);

	/*
	 * MMUv1 करोes not support चयनing between dअगरferent contexts without
	 * a stop the world operation, so we only support a single shared
	 * context with this version.
	 */
	अगर (global->v1.shared_context) अणु
		context = global->v1.shared_context;
		etnaviv_iommu_context_get(context);
		mutex_unlock(&global->lock);
		वापस context;
	पूर्ण

	v1_context = kzalloc(माप(*v1_context), GFP_KERNEL);
	अगर (!v1_context) अणु
		mutex_unlock(&global->lock);
		वापस शून्य;
	पूर्ण

	v1_context->pgtable_cpu = dma_alloc_wc(global->dev, PT_SIZE,
					       &v1_context->pgtable_dma,
					       GFP_KERNEL);
	अगर (!v1_context->pgtable_cpu)
		जाओ out_मुक्त;

	स_रखो32(v1_context->pgtable_cpu, global->bad_page_dma, PT_ENTRIES);

	context = &v1_context->base;
	context->global = global;
	kref_init(&context->refcount);
	mutex_init(&context->lock);
	INIT_LIST_HEAD(&context->mappings);
	drm_mm_init(&context->mm, GPU_MEM_START, PT_ENTRIES * SZ_4K);
	context->global->v1.shared_context = context;

	mutex_unlock(&global->lock);

	वापस context;

out_मुक्त:
	mutex_unlock(&global->lock);
	kमुक्त(v1_context);
	वापस शून्य;
पूर्ण
