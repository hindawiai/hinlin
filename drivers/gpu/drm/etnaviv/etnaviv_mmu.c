<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2018 Etnaviv Project
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/scatterlist.h>

#समावेश "common.xml.h"
#समावेश "etnaviv_cmdbuf.h"
#समावेश "etnaviv_drv.h"
#समावेश "etnaviv_gem.h"
#समावेश "etnaviv_gpu.h"
#समावेश "etnaviv_mmu.h"

अटल व्योम etnaviv_context_unmap(काष्ठा etnaviv_iommu_context *context,
				 अचिन्हित दीर्घ iova, माप_प्रकार size)
अणु
	माप_प्रकार unmapped_page, unmapped = 0;
	माप_प्रकार pgsize = SZ_4K;

	अगर (!IS_ALIGNED(iova | size, pgsize)) अणु
		pr_err("unaligned: iova 0x%lx size 0x%zx min_pagesz 0x%zx\n",
		       iova, size, pgsize);
		वापस;
	पूर्ण

	जबतक (unmapped < size) अणु
		unmapped_page = context->global->ops->unmap(context, iova,
							    pgsize);
		अगर (!unmapped_page)
			अवरोध;

		iova += unmapped_page;
		unmapped += unmapped_page;
	पूर्ण
पूर्ण

अटल पूर्णांक etnaviv_context_map(काष्ठा etnaviv_iommu_context *context,
			      अचिन्हित दीर्घ iova, phys_addr_t paddr,
			      माप_प्रकार size, पूर्णांक prot)
अणु
	अचिन्हित दीर्घ orig_iova = iova;
	माप_प्रकार pgsize = SZ_4K;
	माप_प्रकार orig_size = size;
	पूर्णांक ret = 0;

	अगर (!IS_ALIGNED(iova | paddr | size, pgsize)) अणु
		pr_err("unaligned: iova 0x%lx pa %pa size 0x%zx min_pagesz 0x%zx\n",
		       iova, &paddr, size, pgsize);
		वापस -EINVAL;
	पूर्ण

	जबतक (size) अणु
		ret = context->global->ops->map(context, iova, paddr, pgsize,
						prot);
		अगर (ret)
			अवरोध;

		iova += pgsize;
		paddr += pgsize;
		size -= pgsize;
	पूर्ण

	/* unroll mapping in हाल something went wrong */
	अगर (ret)
		etnaviv_context_unmap(context, orig_iova, orig_size - size);

	वापस ret;
पूर्ण

अटल पूर्णांक etnaviv_iommu_map(काष्ठा etnaviv_iommu_context *context, u32 iova,
			     काष्ठा sg_table *sgt, अचिन्हित len, पूर्णांक prot)
अणु	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक da = iova;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!context || !sgt)
		वापस -EINVAL;

	क्रम_each_sgtable_dma_sg(sgt, sg, i) अणु
		u32 pa = sg_dma_address(sg) - sg->offset;
		माप_प्रकार bytes = sg_dma_len(sg) + sg->offset;

		VERB("map[%d]: %08x %08x(%zx)", i, iova, pa, bytes);

		ret = etnaviv_context_map(context, da, pa, bytes, prot);
		अगर (ret)
			जाओ fail;

		da += bytes;
	पूर्ण

	वापस 0;

fail:
	etnaviv_context_unmap(context, iova, da - iova);
	वापस ret;
पूर्ण

अटल व्योम etnaviv_iommu_unmap(काष्ठा etnaviv_iommu_context *context, u32 iova,
				काष्ठा sg_table *sgt, अचिन्हित len)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक da = iova;
	पूर्णांक i;

	क्रम_each_sgtable_dma_sg(sgt, sg, i) अणु
		माप_प्रकार bytes = sg_dma_len(sg) + sg->offset;

		etnaviv_context_unmap(context, da, bytes);

		VERB("unmap[%d]: %08x(%zx)", i, iova, bytes);

		BUG_ON(!PAGE_ALIGNED(bytes));

		da += bytes;
	पूर्ण
पूर्ण

अटल व्योम etnaviv_iommu_हटाओ_mapping(काष्ठा etnaviv_iommu_context *context,
	काष्ठा etnaviv_vram_mapping *mapping)
अणु
	काष्ठा etnaviv_gem_object *etnaviv_obj = mapping->object;

	lockdep_निश्चित_held(&context->lock);

	etnaviv_iommu_unmap(context, mapping->vram_node.start,
			    etnaviv_obj->sgt, etnaviv_obj->base.size);
	drm_mm_हटाओ_node(&mapping->vram_node);
पूर्ण

अटल पूर्णांक etnaviv_iommu_find_iova(काष्ठा etnaviv_iommu_context *context,
				   काष्ठा drm_mm_node *node, माप_प्रकार size)
अणु
	काष्ठा etnaviv_vram_mapping *मुक्त = शून्य;
	क्रमागत drm_mm_insert_mode mode = DRM_MM_INSERT_LOW;
	पूर्णांक ret;

	lockdep_निश्चित_held(&context->lock);

	जबतक (1) अणु
		काष्ठा etnaviv_vram_mapping *m, *n;
		काष्ठा drm_mm_scan scan;
		काष्ठा list_head list;
		bool found;

		ret = drm_mm_insert_node_in_range(&context->mm, node,
						  size, 0, 0, 0, U64_MAX, mode);
		अगर (ret != -ENOSPC)
			अवरोध;

		/* Try to retire some entries */
		drm_mm_scan_init(&scan, &context->mm, size, 0, 0, mode);

		found = 0;
		INIT_LIST_HEAD(&list);
		list_क्रम_each_entry(मुक्त, &context->mappings, mmu_node) अणु
			/* If this vram node has not been used, skip this. */
			अगर (!मुक्त->vram_node.mm)
				जारी;

			/*
			 * If the iova is pinned, then it's in-use,
			 * so we must keep its mapping.
			 */
			अगर (मुक्त->use)
				जारी;

			list_add(&मुक्त->scan_node, &list);
			अगर (drm_mm_scan_add_block(&scan, &मुक्त->vram_node)) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			/* Nothing found, clean up and fail */
			list_क्रम_each_entry_safe(m, n, &list, scan_node)
				BUG_ON(drm_mm_scan_हटाओ_block(&scan, &m->vram_node));
			अवरोध;
		पूर्ण

		/*
		 * drm_mm करोes not allow any other operations जबतक
		 * scanning, so we have to हटाओ all blocks first.
		 * If drm_mm_scan_हटाओ_block() वापसs false, we
		 * can leave the block pinned.
		 */
		list_क्रम_each_entry_safe(m, n, &list, scan_node)
			अगर (!drm_mm_scan_हटाओ_block(&scan, &m->vram_node))
				list_del_init(&m->scan_node);

		/*
		 * Unmap the blocks which need to be reaped from the MMU.
		 * Clear the mmu poपूर्णांकer to prevent the mapping_get finding
		 * this mapping.
		 */
		list_क्रम_each_entry_safe(m, n, &list, scan_node) अणु
			etnaviv_iommu_हटाओ_mapping(context, m);
			m->context = शून्य;
			list_del_init(&m->mmu_node);
			list_del_init(&m->scan_node);
		पूर्ण

		mode = DRM_MM_INSERT_EVICT;

		/*
		 * We हटाओd enough mappings so that the new allocation will
		 * succeed, retry the allocation one more समय.
		 */
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक etnaviv_iommu_insert_exact(काष्ठा etnaviv_iommu_context *context,
		   काष्ठा drm_mm_node *node, माप_प्रकार size, u64 va)
अणु
	lockdep_निश्चित_held(&context->lock);

	वापस drm_mm_insert_node_in_range(&context->mm, node, size, 0, 0, va,
					   va + size, DRM_MM_INSERT_LOWEST);
पूर्ण

पूर्णांक etnaviv_iommu_map_gem(काष्ठा etnaviv_iommu_context *context,
	काष्ठा etnaviv_gem_object *etnaviv_obj, u32 memory_base,
	काष्ठा etnaviv_vram_mapping *mapping, u64 va)
अणु
	काष्ठा sg_table *sgt = etnaviv_obj->sgt;
	काष्ठा drm_mm_node *node;
	पूर्णांक ret;

	lockdep_निश्चित_held(&etnaviv_obj->lock);

	mutex_lock(&context->lock);

	/* v1 MMU can optimize single entry (contiguous) scatterlists */
	अगर (context->global->version == ETNAVIV_IOMMU_V1 &&
	    sgt->nents == 1 && !(etnaviv_obj->flags & ETNA_BO_FORCE_MMU)) अणु
		u32 iova;

		iova = sg_dma_address(sgt->sgl) - memory_base;
		अगर (iova < 0x80000000 - sg_dma_len(sgt->sgl)) अणु
			mapping->iova = iova;
			list_add_tail(&mapping->mmu_node, &context->mappings);
			ret = 0;
			जाओ unlock;
		पूर्ण
	पूर्ण

	node = &mapping->vram_node;

	अगर (va)
		ret = etnaviv_iommu_insert_exact(context, node,
						 etnaviv_obj->base.size, va);
	अन्यथा
		ret = etnaviv_iommu_find_iova(context, node,
					      etnaviv_obj->base.size);
	अगर (ret < 0)
		जाओ unlock;

	mapping->iova = node->start;
	ret = etnaviv_iommu_map(context, node->start, sgt, etnaviv_obj->base.size,
				ETNAVIV_PROT_READ | ETNAVIV_PROT_WRITE);

	अगर (ret < 0) अणु
		drm_mm_हटाओ_node(node);
		जाओ unlock;
	पूर्ण

	list_add_tail(&mapping->mmu_node, &context->mappings);
	context->flush_seq++;
unlock:
	mutex_unlock(&context->lock);

	वापस ret;
पूर्ण

व्योम etnaviv_iommu_unmap_gem(काष्ठा etnaviv_iommu_context *context,
	काष्ठा etnaviv_vram_mapping *mapping)
अणु
	WARN_ON(mapping->use);

	mutex_lock(&context->lock);

	/* If the vram node is on the mm, unmap and हटाओ the node */
	अगर (mapping->vram_node.mm == &context->mm)
		etnaviv_iommu_हटाओ_mapping(context, mapping);

	list_del(&mapping->mmu_node);
	context->flush_seq++;
	mutex_unlock(&context->lock);
पूर्ण

अटल व्योम etnaviv_iommu_context_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा etnaviv_iommu_context *context =
		container_of(kref, काष्ठा etnaviv_iommu_context, refcount);

	etnaviv_cmdbuf_suballoc_unmap(context, &context->cmdbuf_mapping);

	context->global->ops->मुक्त(context);
पूर्ण
व्योम etnaviv_iommu_context_put(काष्ठा etnaviv_iommu_context *context)
अणु
	kref_put(&context->refcount, etnaviv_iommu_context_मुक्त);
पूर्ण

काष्ठा etnaviv_iommu_context *
etnaviv_iommu_context_init(काष्ठा etnaviv_iommu_global *global,
			   काष्ठा etnaviv_cmdbuf_suballoc *suballoc)
अणु
	काष्ठा etnaviv_iommu_context *ctx;
	पूर्णांक ret;

	अगर (global->version == ETNAVIV_IOMMU_V1)
		ctx = etnaviv_iommuv1_context_alloc(global);
	अन्यथा
		ctx = etnaviv_iommuv2_context_alloc(global);

	अगर (!ctx)
		वापस शून्य;

	ret = etnaviv_cmdbuf_suballoc_map(suballoc, ctx, &ctx->cmdbuf_mapping,
					  global->memory_base);
	अगर (ret)
		जाओ out_मुक्त;

	अगर (global->version == ETNAVIV_IOMMU_V1 &&
	    ctx->cmdbuf_mapping.iova > 0x80000000) अणु
		dev_err(global->dev,
		        "command buffer outside valid memory window\n");
		जाओ out_unmap;
	पूर्ण

	वापस ctx;

out_unmap:
	etnaviv_cmdbuf_suballoc_unmap(ctx, &ctx->cmdbuf_mapping);
out_मुक्त:
	global->ops->मुक्त(ctx);
	वापस शून्य;
पूर्ण

व्योम etnaviv_iommu_restore(काष्ठा etnaviv_gpu *gpu,
			   काष्ठा etnaviv_iommu_context *context)
अणु
	context->global->ops->restore(gpu, context);
पूर्ण

पूर्णांक etnaviv_iommu_get_suballoc_va(काष्ठा etnaviv_iommu_context *context,
				  काष्ठा etnaviv_vram_mapping *mapping,
				  u32 memory_base, dma_addr_t paddr,
				  माप_प्रकार size)
अणु
	mutex_lock(&context->lock);

	अगर (mapping->use > 0) अणु
		mapping->use++;
		mutex_unlock(&context->lock);
		वापस 0;
	पूर्ण

	/*
	 * For MMUv1 we करोn't add the suballoc region to the pagetables, as
	 * those GPUs can only work with cmdbufs accessed through the linear
	 * winकरोw. Instead we manufacture a mapping to make it look unअगरorm
	 * to the upper layers.
	 */
	अगर (context->global->version == ETNAVIV_IOMMU_V1) अणु
		mapping->iova = paddr - memory_base;
	पूर्ण अन्यथा अणु
		काष्ठा drm_mm_node *node = &mapping->vram_node;
		पूर्णांक ret;

		ret = etnaviv_iommu_find_iova(context, node, size);
		अगर (ret < 0) अणु
			mutex_unlock(&context->lock);
			वापस ret;
		पूर्ण

		mapping->iova = node->start;
		ret = etnaviv_context_map(context, node->start, paddr, size,
					  ETNAVIV_PROT_READ);
		अगर (ret < 0) अणु
			drm_mm_हटाओ_node(node);
			mutex_unlock(&context->lock);
			वापस ret;
		पूर्ण

		context->flush_seq++;
	पूर्ण

	list_add_tail(&mapping->mmu_node, &context->mappings);
	mapping->use = 1;

	mutex_unlock(&context->lock);

	वापस 0;
पूर्ण

व्योम etnaviv_iommu_put_suballoc_va(काष्ठा etnaviv_iommu_context *context,
		  काष्ठा etnaviv_vram_mapping *mapping)
अणु
	काष्ठा drm_mm_node *node = &mapping->vram_node;

	mutex_lock(&context->lock);
	mapping->use--;

	अगर (mapping->use > 0 || context->global->version == ETNAVIV_IOMMU_V1) अणु
		mutex_unlock(&context->lock);
		वापस;
	पूर्ण

	etnaviv_context_unmap(context, node->start, node->size);
	drm_mm_हटाओ_node(node);
	mutex_unlock(&context->lock);
पूर्ण

माप_प्रकार etnaviv_iommu_dump_size(काष्ठा etnaviv_iommu_context *context)
अणु
	वापस context->global->ops->dump_size(context);
पूर्ण

व्योम etnaviv_iommu_dump(काष्ठा etnaviv_iommu_context *context, व्योम *buf)
अणु
	context->global->ops->dump(context, buf);
पूर्ण

पूर्णांक etnaviv_iommu_global_init(काष्ठा etnaviv_gpu *gpu)
अणु
	क्रमागत etnaviv_iommu_version version = ETNAVIV_IOMMU_V1;
	काष्ठा etnaviv_drm_निजी *priv = gpu->drm->dev_निजी;
	काष्ठा etnaviv_iommu_global *global;
	काष्ठा device *dev = gpu->drm->dev;

	अगर (gpu->identity.minor_features1 & chipMinorFeatures1_MMU_VERSION)
		version = ETNAVIV_IOMMU_V2;

	अगर (priv->mmu_global) अणु
		अगर (priv->mmu_global->version != version) अणु
			dev_err(gpu->dev,
				"MMU version doesn't match global version\n");
			वापस -ENXIO;
		पूर्ण

		priv->mmu_global->use++;
		वापस 0;
	पूर्ण

	global = kzalloc(माप(*global), GFP_KERNEL);
	अगर (!global)
		वापस -ENOMEM;

	global->bad_page_cpu = dma_alloc_wc(dev, SZ_4K, &global->bad_page_dma,
					    GFP_KERNEL);
	अगर (!global->bad_page_cpu)
		जाओ मुक्त_global;

	स_रखो32(global->bad_page_cpu, 0xdead55aa, SZ_4K / माप(u32));

	अगर (version == ETNAVIV_IOMMU_V2) अणु
		global->v2.pta_cpu = dma_alloc_wc(dev, ETNAVIV_PTA_SIZE,
					       &global->v2.pta_dma, GFP_KERNEL);
		अगर (!global->v2.pta_cpu)
			जाओ मुक्त_bad_page;
	पूर्ण

	global->dev = dev;
	global->version = version;
	global->use = 1;
	mutex_init(&global->lock);

	अगर (version == ETNAVIV_IOMMU_V1)
		global->ops = &etnaviv_iommuv1_ops;
	अन्यथा
		global->ops = &etnaviv_iommuv2_ops;

	priv->mmu_global = global;

	वापस 0;

मुक्त_bad_page:
	dma_मुक्त_wc(dev, SZ_4K, global->bad_page_cpu, global->bad_page_dma);
मुक्त_global:
	kमुक्त(global);

	वापस -ENOMEM;
पूर्ण

व्योम etnaviv_iommu_global_fini(काष्ठा etnaviv_gpu *gpu)
अणु
	काष्ठा etnaviv_drm_निजी *priv = gpu->drm->dev_निजी;
	काष्ठा etnaviv_iommu_global *global = priv->mmu_global;

	अगर (--global->use > 0)
		वापस;

	अगर (global->v2.pta_cpu)
		dma_मुक्त_wc(global->dev, ETNAVIV_PTA_SIZE,
			    global->v2.pta_cpu, global->v2.pta_dma);

	अगर (global->bad_page_cpu)
		dma_मुक्त_wc(global->dev, SZ_4K,
			    global->bad_page_cpu, global->bad_page_dma);

	mutex_destroy(&global->lock);
	kमुक्त(global);

	priv->mmu_global = शून्य;
पूर्ण
