<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016-2018 Etnaviv Project
 */

#समावेश <linux/bitops.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "etnaviv_cmdbuf.h"
#समावेश "etnaviv_gpu.h"
#समावेश "etnaviv_mmu.h"
#समावेश "state.xml.h"
#समावेश "state_hi.xml.h"

#घोषणा MMUv2_PTE_PRESENT		BIT(0)
#घोषणा MMUv2_PTE_EXCEPTION		BIT(1)
#घोषणा MMUv2_PTE_WRITEABLE		BIT(2)

#घोषणा MMUv2_MTLB_MASK			0xffc00000
#घोषणा MMUv2_MTLB_SHIFT		22
#घोषणा MMUv2_STLB_MASK			0x003ff000
#घोषणा MMUv2_STLB_SHIFT		12

#घोषणा MMUv2_MAX_STLB_ENTRIES		1024

काष्ठा etnaviv_iommuv2_context अणु
	काष्ठा etnaviv_iommu_context base;
	अचिन्हित लघु id;
	/* M(aster) TLB aka first level pagetable */
	u32 *mtlb_cpu;
	dma_addr_t mtlb_dma;
	/* S(lave) TLB aka second level pagetable */
	u32 *stlb_cpu[MMUv2_MAX_STLB_ENTRIES];
	dma_addr_t stlb_dma[MMUv2_MAX_STLB_ENTRIES];
पूर्ण;

अटल काष्ठा etnaviv_iommuv2_context *
to_v2_context(काष्ठा etnaviv_iommu_context *context)
अणु
	वापस container_of(context, काष्ठा etnaviv_iommuv2_context, base);
पूर्ण

अटल व्योम etnaviv_iommuv2_मुक्त(काष्ठा etnaviv_iommu_context *context)
अणु
	काष्ठा etnaviv_iommuv2_context *v2_context = to_v2_context(context);
	पूर्णांक i;

	drm_mm_takeकरोwn(&context->mm);

	क्रम (i = 0; i < MMUv2_MAX_STLB_ENTRIES; i++) अणु
		अगर (v2_context->stlb_cpu[i])
			dma_मुक्त_wc(context->global->dev, SZ_4K,
				    v2_context->stlb_cpu[i],
				    v2_context->stlb_dma[i]);
	पूर्ण

	dma_मुक्त_wc(context->global->dev, SZ_4K, v2_context->mtlb_cpu,
		    v2_context->mtlb_dma);

	clear_bit(v2_context->id, context->global->v2.pta_alloc);

	vमुक्त(v2_context);
पूर्ण
अटल पूर्णांक
etnaviv_iommuv2_ensure_stlb(काष्ठा etnaviv_iommuv2_context *v2_context,
			    पूर्णांक stlb)
अणु
	अगर (v2_context->stlb_cpu[stlb])
		वापस 0;

	v2_context->stlb_cpu[stlb] =
			dma_alloc_wc(v2_context->base.global->dev, SZ_4K,
				     &v2_context->stlb_dma[stlb],
				     GFP_KERNEL);

	अगर (!v2_context->stlb_cpu[stlb])
		वापस -ENOMEM;

	स_रखो32(v2_context->stlb_cpu[stlb], MMUv2_PTE_EXCEPTION,
		 SZ_4K / माप(u32));

	v2_context->mtlb_cpu[stlb] =
			v2_context->stlb_dma[stlb] | MMUv2_PTE_PRESENT;

	वापस 0;
पूर्ण

अटल पूर्णांक etnaviv_iommuv2_map(काष्ठा etnaviv_iommu_context *context,
			       अचिन्हित दीर्घ iova, phys_addr_t paddr,
			       माप_प्रकार size, पूर्णांक prot)
अणु
	काष्ठा etnaviv_iommuv2_context *v2_context = to_v2_context(context);
	पूर्णांक mtlb_entry, stlb_entry, ret;
	u32 entry = lower_32_bits(paddr) | MMUv2_PTE_PRESENT;

	अगर (size != SZ_4K)
		वापस -EINVAL;

	अगर (IS_ENABLED(CONFIG_PHYS_ADDR_T_64BIT))
		entry |= (upper_32_bits(paddr) & 0xff) << 4;

	अगर (prot & ETNAVIV_PROT_WRITE)
		entry |= MMUv2_PTE_WRITEABLE;

	mtlb_entry = (iova & MMUv2_MTLB_MASK) >> MMUv2_MTLB_SHIFT;
	stlb_entry = (iova & MMUv2_STLB_MASK) >> MMUv2_STLB_SHIFT;

	ret = etnaviv_iommuv2_ensure_stlb(v2_context, mtlb_entry);
	अगर (ret)
		वापस ret;

	v2_context->stlb_cpu[mtlb_entry][stlb_entry] = entry;

	वापस 0;
पूर्ण

अटल माप_प्रकार etnaviv_iommuv2_unmap(काष्ठा etnaviv_iommu_context *context,
				    अचिन्हित दीर्घ iova, माप_प्रकार size)
अणु
	काष्ठा etnaviv_iommuv2_context *etnaviv_करोमुख्य = to_v2_context(context);
	पूर्णांक mtlb_entry, stlb_entry;

	अगर (size != SZ_4K)
		वापस -EINVAL;

	mtlb_entry = (iova & MMUv2_MTLB_MASK) >> MMUv2_MTLB_SHIFT;
	stlb_entry = (iova & MMUv2_STLB_MASK) >> MMUv2_STLB_SHIFT;

	etnaviv_करोमुख्य->stlb_cpu[mtlb_entry][stlb_entry] = MMUv2_PTE_EXCEPTION;

	वापस SZ_4K;
पूर्ण

अटल माप_प्रकार etnaviv_iommuv2_dump_size(काष्ठा etnaviv_iommu_context *context)
अणु
	काष्ठा etnaviv_iommuv2_context *v2_context = to_v2_context(context);
	माप_प्रकार dump_size = SZ_4K;
	पूर्णांक i;

	क्रम (i = 0; i < MMUv2_MAX_STLB_ENTRIES; i++)
		अगर (v2_context->mtlb_cpu[i] & MMUv2_PTE_PRESENT)
			dump_size += SZ_4K;

	वापस dump_size;
पूर्ण

अटल व्योम etnaviv_iommuv2_dump(काष्ठा etnaviv_iommu_context *context, व्योम *buf)
अणु
	काष्ठा etnaviv_iommuv2_context *v2_context = to_v2_context(context);
	पूर्णांक i;

	स_नकल(buf, v2_context->mtlb_cpu, SZ_4K);
	buf += SZ_4K;
	क्रम (i = 0; i < MMUv2_MAX_STLB_ENTRIES; i++)
		अगर (v2_context->mtlb_cpu[i] & MMUv2_PTE_PRESENT) अणु
			स_नकल(buf, v2_context->stlb_cpu[i], SZ_4K);
			buf += SZ_4K;
		पूर्ण
पूर्ण

अटल व्योम etnaviv_iommuv2_restore_nonsec(काष्ठा etnaviv_gpu *gpu,
	काष्ठा etnaviv_iommu_context *context)
अणु
	काष्ठा etnaviv_iommuv2_context *v2_context = to_v2_context(context);
	u16 prefetch;

	/* If the MMU is alपढ़ोy enabled the state is still there. */
	अगर (gpu_पढ़ो(gpu, VIVS_MMUv2_CONTROL) & VIVS_MMUv2_CONTROL_ENABLE)
		वापस;

	prefetch = etnaviv_buffer_config_mmuv2(gpu,
				(u32)v2_context->mtlb_dma,
				(u32)context->global->bad_page_dma);
	etnaviv_gpu_start_fe(gpu, (u32)etnaviv_cmdbuf_get_pa(&gpu->buffer),
			     prefetch);
	etnaviv_gpu_रुको_idle(gpu, 100);

	gpu_ग_लिखो(gpu, VIVS_MMUv2_CONTROL, VIVS_MMUv2_CONTROL_ENABLE);
पूर्ण

अटल व्योम etnaviv_iommuv2_restore_sec(काष्ठा etnaviv_gpu *gpu,
	काष्ठा etnaviv_iommu_context *context)
अणु
	काष्ठा etnaviv_iommuv2_context *v2_context = to_v2_context(context);
	u16 prefetch;

	/* If the MMU is alपढ़ोy enabled the state is still there. */
	अगर (gpu_पढ़ो(gpu, VIVS_MMUv2_SEC_CONTROL) & VIVS_MMUv2_SEC_CONTROL_ENABLE)
		वापस;

	gpu_ग_लिखो(gpu, VIVS_MMUv2_PTA_ADDRESS_LOW,
		  lower_32_bits(context->global->v2.pta_dma));
	gpu_ग_लिखो(gpu, VIVS_MMUv2_PTA_ADDRESS_HIGH,
		  upper_32_bits(context->global->v2.pta_dma));
	gpu_ग_लिखो(gpu, VIVS_MMUv2_PTA_CONTROL, VIVS_MMUv2_PTA_CONTROL_ENABLE);

	gpu_ग_लिखो(gpu, VIVS_MMUv2_NONSEC_SAFE_ADDR_LOW,
		  lower_32_bits(context->global->bad_page_dma));
	gpu_ग_लिखो(gpu, VIVS_MMUv2_SEC_SAFE_ADDR_LOW,
		  lower_32_bits(context->global->bad_page_dma));
	gpu_ग_लिखो(gpu, VIVS_MMUv2_SAFE_ADDRESS_CONFIG,
		  VIVS_MMUv2_SAFE_ADDRESS_CONFIG_NON_SEC_SAFE_ADDR_HIGH(
		  upper_32_bits(context->global->bad_page_dma)) |
		  VIVS_MMUv2_SAFE_ADDRESS_CONFIG_SEC_SAFE_ADDR_HIGH(
		  upper_32_bits(context->global->bad_page_dma)));

	context->global->v2.pta_cpu[v2_context->id] = v2_context->mtlb_dma |
				 	 VIVS_MMUv2_CONFIGURATION_MODE_MODE4_K;

	/* trigger a PTA load through the FE */
	prefetch = etnaviv_buffer_config_pta(gpu, v2_context->id);
	etnaviv_gpu_start_fe(gpu, (u32)etnaviv_cmdbuf_get_pa(&gpu->buffer),
			     prefetch);
	etnaviv_gpu_रुको_idle(gpu, 100);

	gpu_ग_लिखो(gpu, VIVS_MMUv2_SEC_CONTROL, VIVS_MMUv2_SEC_CONTROL_ENABLE);
पूर्ण

u32 etnaviv_iommuv2_get_mtlb_addr(काष्ठा etnaviv_iommu_context *context)
अणु
	काष्ठा etnaviv_iommuv2_context *v2_context = to_v2_context(context);

	वापस v2_context->mtlb_dma;
पूर्ण

अचिन्हित लघु etnaviv_iommuv2_get_pta_id(काष्ठा etnaviv_iommu_context *context)
अणु
	काष्ठा etnaviv_iommuv2_context *v2_context = to_v2_context(context);

	वापस v2_context->id;
पूर्ण
अटल व्योम etnaviv_iommuv2_restore(काष्ठा etnaviv_gpu *gpu,
				    काष्ठा etnaviv_iommu_context *context)
अणु
	चयन (gpu->sec_mode) अणु
	हाल ETNA_SEC_NONE:
		etnaviv_iommuv2_restore_nonsec(gpu, context);
		अवरोध;
	हाल ETNA_SEC_KERNEL:
		etnaviv_iommuv2_restore_sec(gpu, context);
		अवरोध;
	शेष:
		WARN(1, "unhandled GPU security mode\n");
		अवरोध;
	पूर्ण
पूर्ण

स्थिर काष्ठा etnaviv_iommu_ops etnaviv_iommuv2_ops = अणु
	.मुक्त = etnaviv_iommuv2_मुक्त,
	.map = etnaviv_iommuv2_map,
	.unmap = etnaviv_iommuv2_unmap,
	.dump_size = etnaviv_iommuv2_dump_size,
	.dump = etnaviv_iommuv2_dump,
	.restore = etnaviv_iommuv2_restore,
पूर्ण;

काष्ठा etnaviv_iommu_context *
etnaviv_iommuv2_context_alloc(काष्ठा etnaviv_iommu_global *global)
अणु
	काष्ठा etnaviv_iommuv2_context *v2_context;
	काष्ठा etnaviv_iommu_context *context;

	v2_context = vzalloc(माप(*v2_context));
	अगर (!v2_context)
		वापस शून्य;

	mutex_lock(&global->lock);
	v2_context->id = find_first_zero_bit(global->v2.pta_alloc,
					     ETNAVIV_PTA_ENTRIES);
	अगर (v2_context->id < ETNAVIV_PTA_ENTRIES) अणु
		set_bit(v2_context->id, global->v2.pta_alloc);
	पूर्ण अन्यथा अणु
		mutex_unlock(&global->lock);
		जाओ out_मुक्त;
	पूर्ण
	mutex_unlock(&global->lock);

	v2_context->mtlb_cpu = dma_alloc_wc(global->dev, SZ_4K,
					    &v2_context->mtlb_dma, GFP_KERNEL);
	अगर (!v2_context->mtlb_cpu)
		जाओ out_मुक्त_id;

	स_रखो32(v2_context->mtlb_cpu, MMUv2_PTE_EXCEPTION,
		 MMUv2_MAX_STLB_ENTRIES);

	global->v2.pta_cpu[v2_context->id] = v2_context->mtlb_dma;

	context = &v2_context->base;
	context->global = global;
	kref_init(&context->refcount);
	mutex_init(&context->lock);
	INIT_LIST_HEAD(&context->mappings);
	drm_mm_init(&context->mm, SZ_4K, (u64)SZ_1G * 4 - SZ_4K);

	वापस context;

out_मुक्त_id:
	clear_bit(v2_context->id, global->v2.pta_alloc);
out_मुक्त:
	vमुक्त(v2_context);
	वापस शून्य;
पूर्ण
