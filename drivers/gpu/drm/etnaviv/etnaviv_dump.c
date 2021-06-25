<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2018 Etnaviv Project
 */

#समावेश <linux/devcoredump.h>
#समावेश <linux/moduleparam.h>

#समावेश "etnaviv_cmdbuf.h"
#समावेश "etnaviv_dump.h"
#समावेश "etnaviv_gem.h"
#समावेश "etnaviv_gpu.h"
#समावेश "etnaviv_mmu.h"
#समावेश "etnaviv_sched.h"
#समावेश "state.xml.h"
#समावेश "state_hi.xml.h"

अटल bool etnaviv_dump_core = true;
module_param_named(dump_core, etnaviv_dump_core, bool, 0600);

काष्ठा core_dump_iterator अणु
	व्योम *start;
	काष्ठा etnaviv_dump_object_header *hdr;
	व्योम *data;
पूर्ण;

अटल स्थिर अचिन्हित लघु etnaviv_dump_रेजिस्टरs[] = अणु
	VIVS_HI_AXI_STATUS,
	VIVS_HI_CLOCK_CONTROL,
	VIVS_HI_IDLE_STATE,
	VIVS_HI_AXI_CONFIG,
	VIVS_HI_INTR_ENBL,
	VIVS_HI_CHIP_IDENTITY,
	VIVS_HI_CHIP_FEATURE,
	VIVS_HI_CHIP_MODEL,
	VIVS_HI_CHIP_REV,
	VIVS_HI_CHIP_DATE,
	VIVS_HI_CHIP_TIME,
	VIVS_HI_CHIP_MINOR_FEATURE_0,
	VIVS_HI_CACHE_CONTROL,
	VIVS_HI_AXI_CONTROL,
	VIVS_PM_POWER_CONTROLS,
	VIVS_PM_MODULE_CONTROLS,
	VIVS_PM_MODULE_STATUS,
	VIVS_PM_PULSE_EATER,
	VIVS_MC_MMU_FE_PAGE_TABLE,
	VIVS_MC_MMU_TX_PAGE_TABLE,
	VIVS_MC_MMU_PE_PAGE_TABLE,
	VIVS_MC_MMU_PEZ_PAGE_TABLE,
	VIVS_MC_MMU_RA_PAGE_TABLE,
	VIVS_MC_DEBUG_MEMORY,
	VIVS_MC_MEMORY_BASE_ADDR_RA,
	VIVS_MC_MEMORY_BASE_ADDR_FE,
	VIVS_MC_MEMORY_BASE_ADDR_TX,
	VIVS_MC_MEMORY_BASE_ADDR_PEZ,
	VIVS_MC_MEMORY_BASE_ADDR_PE,
	VIVS_MC_MEMORY_TIMING_CONTROL,
	VIVS_MC_BUS_CONFIG,
	VIVS_FE_DMA_STATUS,
	VIVS_FE_DMA_DEBUG_STATE,
	VIVS_FE_DMA_ADDRESS,
	VIVS_FE_DMA_LOW,
	VIVS_FE_DMA_HIGH,
	VIVS_FE_AUTO_FLUSH,
पूर्ण;

अटल व्योम etnaviv_core_dump_header(काष्ठा core_dump_iterator *iter,
	u32 type, व्योम *data_end)
अणु
	काष्ठा etnaviv_dump_object_header *hdr = iter->hdr;

	hdr->magic = cpu_to_le32(ETDUMP_MAGIC);
	hdr->type = cpu_to_le32(type);
	hdr->file_offset = cpu_to_le32(iter->data - iter->start);
	hdr->file_size = cpu_to_le32(data_end - iter->data);

	iter->hdr++;
	iter->data += hdr->file_size;
पूर्ण

अटल व्योम etnaviv_core_dump_रेजिस्टरs(काष्ठा core_dump_iterator *iter,
	काष्ठा etnaviv_gpu *gpu)
अणु
	काष्ठा etnaviv_dump_रेजिस्टरs *reg = iter->data;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(etnaviv_dump_रेजिस्टरs); i++, reg++) अणु
		reg->reg = etnaviv_dump_रेजिस्टरs[i];
		reg->value = gpu_पढ़ो(gpu, etnaviv_dump_रेजिस्टरs[i]);
	पूर्ण

	etnaviv_core_dump_header(iter, ETDUMP_BUF_REG, reg);
पूर्ण

अटल व्योम etnaviv_core_dump_mmu(काष्ठा core_dump_iterator *iter,
	काष्ठा etnaviv_iommu_context *mmu, माप_प्रकार mmu_size)
अणु
	etnaviv_iommu_dump(mmu, iter->data);

	etnaviv_core_dump_header(iter, ETDUMP_BUF_MMU, iter->data + mmu_size);
पूर्ण

अटल व्योम etnaviv_core_dump_mem(काष्ठा core_dump_iterator *iter, u32 type,
	व्योम *ptr, माप_प्रकार size, u64 iova)
अणु
	स_नकल(iter->data, ptr, size);

	iter->hdr->iova = cpu_to_le64(iova);

	etnaviv_core_dump_header(iter, type, iter->data + size);
पूर्ण

व्योम etnaviv_core_dump(काष्ठा etnaviv_gem_submit *submit)
अणु
	काष्ठा etnaviv_gpu *gpu = submit->gpu;
	काष्ठा core_dump_iterator iter;
	काष्ठा etnaviv_gem_object *obj;
	अचिन्हित पूर्णांक n_obj, n_bomap_pages;
	माप_प्रकार file_size, mmu_size;
	__le64 *bomap, *bomap_start;
	पूर्णांक i;

	/* Only catch the first event, or when manually re-armed */
	अगर (!etnaviv_dump_core)
		वापस;
	etnaviv_dump_core = false;

	mutex_lock(&gpu->mmu_context->lock);

	mmu_size = etnaviv_iommu_dump_size(gpu->mmu_context);

	/* We always dump रेजिस्टरs, mmu, ring, hanging cmdbuf and end marker */
	n_obj = 5;
	n_bomap_pages = 0;
	file_size = ARRAY_SIZE(etnaviv_dump_रेजिस्टरs) *
			माप(काष्ठा etnaviv_dump_रेजिस्टरs) +
		    mmu_size + gpu->buffer.size + submit->cmdbuf.size;

	/* Add in the active buffer objects */
	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		obj = submit->bos[i].obj;
		file_size += obj->base.size;
		n_bomap_pages += obj->base.size >> PAGE_SHIFT;
		n_obj++;
	पूर्ण

	/* If we have any buffer objects, add a bomap object */
	अगर (n_bomap_pages) अणु
		file_size += n_bomap_pages * माप(__le64);
		n_obj++;
	पूर्ण

	/* Add the size of the headers */
	file_size += माप(*iter.hdr) * n_obj;

	/* Allocate the file in vदो_स्मृति memory, it's likely to be big */
	iter.start = __vदो_स्मृति(file_size, GFP_KERNEL | __GFP_NOWARN |
			__GFP_NORETRY);
	अगर (!iter.start) अणु
		mutex_unlock(&gpu->mmu_context->lock);
		dev_warn(gpu->dev, "failed to allocate devcoredump file\n");
		वापस;
	पूर्ण

	/* Poपूर्णांक the data member after the headers */
	iter.hdr = iter.start;
	iter.data = &iter.hdr[n_obj];

	स_रखो(iter.hdr, 0, iter.data - iter.start);

	etnaviv_core_dump_रेजिस्टरs(&iter, gpu);
	etnaviv_core_dump_mmu(&iter, gpu->mmu_context, mmu_size);
	etnaviv_core_dump_mem(&iter, ETDUMP_BUF_RING, gpu->buffer.vaddr,
			      gpu->buffer.size,
			      etnaviv_cmdbuf_get_va(&gpu->buffer,
					&gpu->mmu_context->cmdbuf_mapping));

	etnaviv_core_dump_mem(&iter, ETDUMP_BUF_CMD,
			      submit->cmdbuf.vaddr, submit->cmdbuf.size,
			      etnaviv_cmdbuf_get_va(&submit->cmdbuf,
					&gpu->mmu_context->cmdbuf_mapping));

	mutex_unlock(&gpu->mmu_context->lock);

	/* Reserve space क्रम the bomap */
	अगर (n_bomap_pages) अणु
		bomap_start = bomap = iter.data;
		स_रखो(bomap, 0, माप(*bomap) * n_bomap_pages);
		etnaviv_core_dump_header(&iter, ETDUMP_BUF_BOMAP,
					 bomap + n_bomap_pages);
	पूर्ण अन्यथा अणु
		/* Silence warning */
		bomap_start = bomap = शून्य;
	पूर्ण

	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		काष्ठा etnaviv_vram_mapping *vram;
		काष्ठा page **pages;
		व्योम *vaddr;

		obj = submit->bos[i].obj;
		vram = submit->bos[i].mapping;

		mutex_lock(&obj->lock);
		pages = etnaviv_gem_get_pages(obj);
		mutex_unlock(&obj->lock);
		अगर (!IS_ERR(pages)) अणु
			पूर्णांक j;

			iter.hdr->data[0] = bomap - bomap_start;

			क्रम (j = 0; j < obj->base.size >> PAGE_SHIFT; j++)
				*bomap++ = cpu_to_le64(page_to_phys(*pages++));
		पूर्ण

		iter.hdr->iova = cpu_to_le64(vram->iova);

		vaddr = etnaviv_gem_vmap(&obj->base);
		अगर (vaddr)
			स_नकल(iter.data, vaddr, obj->base.size);

		etnaviv_core_dump_header(&iter, ETDUMP_BUF_BO, iter.data +
					 obj->base.size);
	पूर्ण

	etnaviv_core_dump_header(&iter, ETDUMP_BUF_END, iter.data);

	dev_coredumpv(gpu->dev, iter.start, iter.data - iter.start, GFP_KERNEL);
पूर्ण
