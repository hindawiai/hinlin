<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2009-2015 VMware, Inc., Palo Alto, CA., USA
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#समावेश "vmwgfx_drv.h"
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>

अटल स्थिर काष्ठा tपंचांग_place vram_placement_flags = अणु
	.fpfn = 0,
	.lpfn = 0,
	.mem_type = TTM_PL_VRAM,
	.flags = 0
पूर्ण;

अटल स्थिर काष्ठा tपंचांग_place sys_placement_flags = अणु
	.fpfn = 0,
	.lpfn = 0,
	.mem_type = TTM_PL_SYSTEM,
	.flags = 0
पूर्ण;

अटल स्थिर काष्ठा tपंचांग_place gmr_placement_flags = अणु
	.fpfn = 0,
	.lpfn = 0,
	.mem_type = VMW_PL_GMR,
	.flags = 0
पूर्ण;

अटल स्थिर काष्ठा tपंचांग_place mob_placement_flags = अणु
	.fpfn = 0,
	.lpfn = 0,
	.mem_type = VMW_PL_MOB,
	.flags = 0
पूर्ण;

काष्ठा tपंचांग_placement vmw_vram_placement = अणु
	.num_placement = 1,
	.placement = &vram_placement_flags,
	.num_busy_placement = 1,
	.busy_placement = &vram_placement_flags
पूर्ण;

अटल स्थिर काष्ठा tपंचांग_place vram_gmr_placement_flags[] = अणु
	अणु
		.fpfn = 0,
		.lpfn = 0,
		.mem_type = TTM_PL_VRAM,
		.flags = 0
	पूर्ण, अणु
		.fpfn = 0,
		.lpfn = 0,
		.mem_type = VMW_PL_GMR,
		.flags = 0
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा tपंचांग_place gmr_vram_placement_flags[] = अणु
	अणु
		.fpfn = 0,
		.lpfn = 0,
		.mem_type = VMW_PL_GMR,
		.flags = 0
	पूर्ण, अणु
		.fpfn = 0,
		.lpfn = 0,
		.mem_type = TTM_PL_VRAM,
		.flags = 0
	पूर्ण
पूर्ण;

काष्ठा tपंचांग_placement vmw_vram_gmr_placement = अणु
	.num_placement = 2,
	.placement = vram_gmr_placement_flags,
	.num_busy_placement = 1,
	.busy_placement = &gmr_placement_flags
पूर्ण;

काष्ठा tपंचांग_placement vmw_vram_sys_placement = अणु
	.num_placement = 1,
	.placement = &vram_placement_flags,
	.num_busy_placement = 1,
	.busy_placement = &sys_placement_flags
पूर्ण;

काष्ठा tपंचांग_placement vmw_sys_placement = अणु
	.num_placement = 1,
	.placement = &sys_placement_flags,
	.num_busy_placement = 1,
	.busy_placement = &sys_placement_flags
पूर्ण;

अटल स्थिर काष्ठा tपंचांग_place evictable_placement_flags[] = अणु
	अणु
		.fpfn = 0,
		.lpfn = 0,
		.mem_type = TTM_PL_SYSTEM,
		.flags = 0
	पूर्ण, अणु
		.fpfn = 0,
		.lpfn = 0,
		.mem_type = TTM_PL_VRAM,
		.flags = 0
	पूर्ण, अणु
		.fpfn = 0,
		.lpfn = 0,
		.mem_type = VMW_PL_GMR,
		.flags = 0
	पूर्ण, अणु
		.fpfn = 0,
		.lpfn = 0,
		.mem_type = VMW_PL_MOB,
		.flags = 0
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा tपंचांग_place nonfixed_placement_flags[] = अणु
	अणु
		.fpfn = 0,
		.lpfn = 0,
		.mem_type = TTM_PL_SYSTEM,
		.flags = 0
	पूर्ण, अणु
		.fpfn = 0,
		.lpfn = 0,
		.mem_type = VMW_PL_GMR,
		.flags = 0
	पूर्ण, अणु
		.fpfn = 0,
		.lpfn = 0,
		.mem_type = VMW_PL_MOB,
		.flags = 0
	पूर्ण
पूर्ण;

काष्ठा tपंचांग_placement vmw_evictable_placement = अणु
	.num_placement = 4,
	.placement = evictable_placement_flags,
	.num_busy_placement = 1,
	.busy_placement = &sys_placement_flags
पूर्ण;

काष्ठा tपंचांग_placement vmw_srf_placement = अणु
	.num_placement = 1,
	.num_busy_placement = 2,
	.placement = &gmr_placement_flags,
	.busy_placement = gmr_vram_placement_flags
पूर्ण;

काष्ठा tपंचांग_placement vmw_mob_placement = अणु
	.num_placement = 1,
	.num_busy_placement = 1,
	.placement = &mob_placement_flags,
	.busy_placement = &mob_placement_flags
पूर्ण;

काष्ठा tपंचांग_placement vmw_nonfixed_placement = अणु
	.num_placement = 3,
	.placement = nonfixed_placement_flags,
	.num_busy_placement = 1,
	.busy_placement = &sys_placement_flags
पूर्ण;

काष्ठा vmw_tपंचांग_tt अणु
	काष्ठा tपंचांग_tt dma_tपंचांग;
	काष्ठा vmw_निजी *dev_priv;
	पूर्णांक gmr_id;
	काष्ठा vmw_mob *mob;
	पूर्णांक mem_type;
	काष्ठा sg_table sgt;
	काष्ठा vmw_sg_table vsgt;
	uपूर्णांक64_t sg_alloc_size;
	bool mapped;
	bool bound;
पूर्ण;

स्थिर माप_प्रकार vmw_tt_size = माप(काष्ठा vmw_tपंचांग_tt);

/**
 * Helper functions to advance a काष्ठा vmw_piter iterator.
 *
 * @viter: Poपूर्णांकer to the iterator.
 *
 * These functions वापस false अगर past the end of the list,
 * true otherwise. Functions are selected depending on the current
 * DMA mapping mode.
 */
अटल bool __vmw_piter_non_sg_next(काष्ठा vmw_piter *viter)
अणु
	वापस ++(viter->i) < viter->num_pages;
पूर्ण

अटल bool __vmw_piter_sg_next(काष्ठा vmw_piter *viter)
अणु
	bool ret = __vmw_piter_non_sg_next(viter);

	वापस __sg_page_iter_dma_next(&viter->iter) && ret;
पूर्ण


/**
 * Helper functions to वापस a poपूर्णांकer to the current page.
 *
 * @viter: Poपूर्णांकer to the iterator
 *
 * These functions वापस a poपूर्णांकer to the page currently
 * poपूर्णांकed to by @viter. Functions are selected depending on the
 * current mapping mode.
 */
अटल काष्ठा page *__vmw_piter_non_sg_page(काष्ठा vmw_piter *viter)
अणु
	वापस viter->pages[viter->i];
पूर्ण

/**
 * Helper functions to वापस the DMA address of the current page.
 *
 * @viter: Poपूर्णांकer to the iterator
 *
 * These functions वापस the DMA address of the page currently
 * poपूर्णांकed to by @viter. Functions are selected depending on the
 * current mapping mode.
 */
अटल dma_addr_t __vmw_piter_phys_addr(काष्ठा vmw_piter *viter)
अणु
	वापस page_to_phys(viter->pages[viter->i]);
पूर्ण

अटल dma_addr_t __vmw_piter_dma_addr(काष्ठा vmw_piter *viter)
अणु
	वापस viter->addrs[viter->i];
पूर्ण

अटल dma_addr_t __vmw_piter_sg_addr(काष्ठा vmw_piter *viter)
अणु
	वापस sg_page_iter_dma_address(&viter->iter);
पूर्ण


/**
 * vmw_piter_start - Initialize a काष्ठा vmw_piter.
 *
 * @viter: Poपूर्णांकer to the iterator to initialize
 * @vsgt: Poपूर्णांकer to a काष्ठा vmw_sg_table to initialize from
 * @p_offset: Poपूर्णांकer offset used to update current array position
 *
 * Note that we're following the convention of __sg_page_iter_start, so that
 * the iterator करोesn't poपूर्णांक to a valid page after initialization; it has
 * to be advanced one step first.
 */
व्योम vmw_piter_start(काष्ठा vmw_piter *viter, स्थिर काष्ठा vmw_sg_table *vsgt,
		     अचिन्हित दीर्घ p_offset)
अणु
	viter->i = p_offset - 1;
	viter->num_pages = vsgt->num_pages;
	viter->page = &__vmw_piter_non_sg_page;
	viter->pages = vsgt->pages;
	चयन (vsgt->mode) अणु
	हाल vmw_dma_phys:
		viter->next = &__vmw_piter_non_sg_next;
		viter->dma_address = &__vmw_piter_phys_addr;
		अवरोध;
	हाल vmw_dma_alloc_coherent:
		viter->next = &__vmw_piter_non_sg_next;
		viter->dma_address = &__vmw_piter_dma_addr;
		viter->addrs = vsgt->addrs;
		अवरोध;
	हाल vmw_dma_map_populate:
	हाल vmw_dma_map_bind:
		viter->next = &__vmw_piter_sg_next;
		viter->dma_address = &__vmw_piter_sg_addr;
		__sg_page_iter_start(&viter->iter.base, vsgt->sgt->sgl,
				     vsgt->sgt->orig_nents, p_offset);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/**
 * vmw_tपंचांग_unmap_from_dma - unmap  device addresses previsouly mapped क्रम
 * TTM pages
 *
 * @vmw_tt: Poपूर्णांकer to a काष्ठा vmw_tपंचांग_backend
 *
 * Used to मुक्त dma mappings previously mapped by vmw_tपंचांग_map_क्रम_dma.
 */
अटल व्योम vmw_tपंचांग_unmap_from_dma(काष्ठा vmw_tपंचांग_tt *vmw_tt)
अणु
	काष्ठा device *dev = vmw_tt->dev_priv->drm.dev;

	dma_unmap_sgtable(dev, &vmw_tt->sgt, DMA_BIसूचीECTIONAL, 0);
	vmw_tt->sgt.nents = vmw_tt->sgt.orig_nents;
पूर्ण

/**
 * vmw_tपंचांग_map_क्रम_dma - map TTM pages to get device addresses
 *
 * @vmw_tt: Poपूर्णांकer to a काष्ठा vmw_tपंचांग_backend
 *
 * This function is used to get device addresses from the kernel DMA layer.
 * However, it's violating the DMA API in that when this operation has been
 * perक्रमmed, it's illegal क्रम the CPU to ग_लिखो to the pages without first
 * unmapping the DMA mappings, or calling dma_sync_sg_क्रम_cpu(). It is
 * thereक्रमe only legal to call this function अगर we know that the function
 * dma_sync_sg_क्रम_cpu() is a NOP, and dma_sync_sg_क्रम_device() is at most
 * a CPU ग_लिखो buffer flush.
 */
अटल पूर्णांक vmw_tपंचांग_map_क्रम_dma(काष्ठा vmw_tपंचांग_tt *vmw_tt)
अणु
	काष्ठा device *dev = vmw_tt->dev_priv->drm.dev;

	वापस dma_map_sgtable(dev, &vmw_tt->sgt, DMA_BIसूचीECTIONAL, 0);
पूर्ण

/**
 * vmw_tपंचांग_map_dma - Make sure TTM pages are visible to the device
 *
 * @vmw_tt: Poपूर्णांकer to a काष्ठा vmw_tपंचांग_tt
 *
 * Select the correct function क्रम and make sure the TTM pages are
 * visible to the device. Allocate storage क्रम the device mappings.
 * If a mapping has alपढ़ोy been perक्रमmed, indicated by the storage
 * poपूर्णांकer being non शून्य, the function वापसs success.
 */
अटल पूर्णांक vmw_tपंचांग_map_dma(काष्ठा vmw_tपंचांग_tt *vmw_tt)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_tt->dev_priv;
	काष्ठा tपंचांग_mem_global *glob = vmw_mem_glob(dev_priv);
	काष्ठा vmw_sg_table *vsgt = &vmw_tt->vsgt;
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = true,
		.no_रुको_gpu = false
	पूर्ण;
	काष्ठा vmw_piter iter;
	dma_addr_t old;
	पूर्णांक ret = 0;
	अटल माप_प्रकार sgl_size;
	अटल माप_प्रकार sgt_size;
	काष्ठा scatterlist *sg;

	अगर (vmw_tt->mapped)
		वापस 0;

	vsgt->mode = dev_priv->map_mode;
	vsgt->pages = vmw_tt->dma_tपंचांग.pages;
	vsgt->num_pages = vmw_tt->dma_tपंचांग.num_pages;
	vsgt->addrs = vmw_tt->dma_tपंचांग.dma_address;
	vsgt->sgt = &vmw_tt->sgt;

	चयन (dev_priv->map_mode) अणु
	हाल vmw_dma_map_bind:
	हाल vmw_dma_map_populate:
		अगर (unlikely(!sgl_size)) अणु
			sgl_size = tपंचांग_round_pot(माप(काष्ठा scatterlist));
			sgt_size = tपंचांग_round_pot(माप(काष्ठा sg_table));
		पूर्ण
		vmw_tt->sg_alloc_size = sgt_size + sgl_size * vsgt->num_pages;
		ret = tपंचांग_mem_global_alloc(glob, vmw_tt->sg_alloc_size, &ctx);
		अगर (unlikely(ret != 0))
			वापस ret;

		sg = __sg_alloc_table_from_pages(&vmw_tt->sgt, vsgt->pages,
				vsgt->num_pages, 0,
				(अचिन्हित दीर्घ) vsgt->num_pages << PAGE_SHIFT,
				dma_get_max_seg_size(dev_priv->drm.dev),
				शून्य, 0, GFP_KERNEL);
		अगर (IS_ERR(sg)) अणु
			ret = PTR_ERR(sg);
			जाओ out_sg_alloc_fail;
		पूर्ण

		अगर (vsgt->num_pages > vmw_tt->sgt.orig_nents) अणु
			uपूर्णांक64_t over_alloc =
				sgl_size * (vsgt->num_pages -
					    vmw_tt->sgt.orig_nents);

			tपंचांग_mem_global_मुक्त(glob, over_alloc);
			vmw_tt->sg_alloc_size -= over_alloc;
		पूर्ण

		ret = vmw_tपंचांग_map_क्रम_dma(vmw_tt);
		अगर (unlikely(ret != 0))
			जाओ out_map_fail;

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	old = ~((dma_addr_t) 0);
	vmw_tt->vsgt.num_regions = 0;
	क्रम (vmw_piter_start(&iter, vsgt, 0); vmw_piter_next(&iter);) अणु
		dma_addr_t cur = vmw_piter_dma_addr(&iter);

		अगर (cur != old + PAGE_SIZE)
			vmw_tt->vsgt.num_regions++;
		old = cur;
	पूर्ण

	vmw_tt->mapped = true;
	वापस 0;

out_map_fail:
	sg_मुक्त_table(vmw_tt->vsgt.sgt);
	vmw_tt->vsgt.sgt = शून्य;
out_sg_alloc_fail:
	tपंचांग_mem_global_मुक्त(glob, vmw_tt->sg_alloc_size);
	वापस ret;
पूर्ण

/**
 * vmw_tपंचांग_unmap_dma - Tear करोwn any TTM page device mappings
 *
 * @vmw_tt: Poपूर्णांकer to a काष्ठा vmw_tपंचांग_tt
 *
 * Tear करोwn any previously set up device DMA mappings and मुक्त
 * any storage space allocated क्रम them. If there are no mappings set up,
 * this function is a NOP.
 */
अटल व्योम vmw_tपंचांग_unmap_dma(काष्ठा vmw_tपंचांग_tt *vmw_tt)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_tt->dev_priv;

	अगर (!vmw_tt->vsgt.sgt)
		वापस;

	चयन (dev_priv->map_mode) अणु
	हाल vmw_dma_map_bind:
	हाल vmw_dma_map_populate:
		vmw_tपंचांग_unmap_from_dma(vmw_tt);
		sg_मुक्त_table(vmw_tt->vsgt.sgt);
		vmw_tt->vsgt.sgt = शून्य;
		tपंचांग_mem_global_मुक्त(vmw_mem_glob(dev_priv),
				    vmw_tt->sg_alloc_size);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	vmw_tt->mapped = false;
पूर्ण

/**
 * vmw_bo_sg_table - Return a काष्ठा vmw_sg_table object क्रम a
 * TTM buffer object
 *
 * @bo: Poपूर्णांकer to a काष्ठा tपंचांग_buffer_object
 *
 * Returns a poपूर्णांकer to a काष्ठा vmw_sg_table object. The object should
 * not be मुक्तd after use.
 * Note that क्रम the device addresses to be valid, the buffer object must
 * either be reserved or pinned.
 */
स्थिर काष्ठा vmw_sg_table *vmw_bo_sg_table(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा vmw_tपंचांग_tt *vmw_tt =
		container_of(bo->tपंचांग, काष्ठा vmw_tपंचांग_tt, dma_tपंचांग);

	वापस &vmw_tt->vsgt;
पूर्ण


अटल पूर्णांक vmw_tपंचांग_bind(काष्ठा tपंचांग_device *bdev,
			काष्ठा tपंचांग_tt *tपंचांग, काष्ठा tपंचांग_resource *bo_mem)
अणु
	काष्ठा vmw_tपंचांग_tt *vmw_be =
		container_of(tपंचांग, काष्ठा vmw_tपंचांग_tt, dma_tपंचांग);
	पूर्णांक ret = 0;

	अगर (!bo_mem)
		वापस -EINVAL;

	अगर (vmw_be->bound)
		वापस 0;

	ret = vmw_tपंचांग_map_dma(vmw_be);
	अगर (unlikely(ret != 0))
		वापस ret;

	vmw_be->gmr_id = bo_mem->start;
	vmw_be->mem_type = bo_mem->mem_type;

	चयन (bo_mem->mem_type) अणु
	हाल VMW_PL_GMR:
		ret = vmw_gmr_bind(vmw_be->dev_priv, &vmw_be->vsgt,
				    tपंचांग->num_pages, vmw_be->gmr_id);
		अवरोध;
	हाल VMW_PL_MOB:
		अगर (unlikely(vmw_be->mob == शून्य)) अणु
			vmw_be->mob =
				vmw_mob_create(tपंचांग->num_pages);
			अगर (unlikely(vmw_be->mob == शून्य))
				वापस -ENOMEM;
		पूर्ण

		ret = vmw_mob_bind(vmw_be->dev_priv, vmw_be->mob,
				    &vmw_be->vsgt, tपंचांग->num_pages,
				    vmw_be->gmr_id);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	vmw_be->bound = true;
	वापस ret;
पूर्ण

अटल व्योम vmw_tपंचांग_unbind(काष्ठा tपंचांग_device *bdev,
			   काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा vmw_tपंचांग_tt *vmw_be =
		container_of(tपंचांग, काष्ठा vmw_tपंचांग_tt, dma_tपंचांग);

	अगर (!vmw_be->bound)
		वापस;

	चयन (vmw_be->mem_type) अणु
	हाल VMW_PL_GMR:
		vmw_gmr_unbind(vmw_be->dev_priv, vmw_be->gmr_id);
		अवरोध;
	हाल VMW_PL_MOB:
		vmw_mob_unbind(vmw_be->dev_priv, vmw_be->mob);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (vmw_be->dev_priv->map_mode == vmw_dma_map_bind)
		vmw_tपंचांग_unmap_dma(vmw_be);
	vmw_be->bound = false;
पूर्ण


अटल व्योम vmw_tपंचांग_destroy(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा vmw_tपंचांग_tt *vmw_be =
		container_of(tपंचांग, काष्ठा vmw_tपंचांग_tt, dma_tपंचांग);

	vmw_tपंचांग_unbind(bdev, tपंचांग);
	tपंचांग_tt_destroy_common(bdev, tपंचांग);
	vmw_tपंचांग_unmap_dma(vmw_be);
	अगर (vmw_be->dev_priv->map_mode == vmw_dma_alloc_coherent)
		tपंचांग_tt_fini(&vmw_be->dma_tपंचांग);
	अन्यथा
		tपंचांग_tt_fini(tपंचांग);

	अगर (vmw_be->mob)
		vmw_mob_destroy(vmw_be->mob);

	kमुक्त(vmw_be);
पूर्ण


अटल पूर्णांक vmw_tपंचांग_populate(काष्ठा tपंचांग_device *bdev,
			    काष्ठा tपंचांग_tt *tपंचांग, काष्ठा tपंचांग_operation_ctx *ctx)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* TODO: maybe completely drop this ? */
	अगर (tपंचांग_tt_is_populated(tपंचांग))
		वापस 0;

	ret = tपंचांग_pool_alloc(&bdev->pool, tपंचांग, ctx);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < tपंचांग->num_pages; ++i) अणु
		ret = tपंचांग_mem_global_alloc_page(&tपंचांग_mem_glob, tपंचांग->pages[i],
						PAGE_SIZE, ctx);
		अगर (ret)
			जाओ error;
	पूर्ण
	वापस 0;

error:
	जबतक (i--)
		tपंचांग_mem_global_मुक्त_page(&tपंचांग_mem_glob, tपंचांग->pages[i],
					 PAGE_SIZE);
	tपंचांग_pool_मुक्त(&bdev->pool, tपंचांग);
	वापस ret;
पूर्ण

अटल व्योम vmw_tपंचांग_unpopulate(काष्ठा tपंचांग_device *bdev,
			       काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा vmw_tपंचांग_tt *vmw_tt = container_of(tपंचांग, काष्ठा vmw_tपंचांग_tt,
						 dma_tपंचांग);
	अचिन्हित पूर्णांक i;

	अगर (vmw_tt->mob) अणु
		vmw_mob_destroy(vmw_tt->mob);
		vmw_tt->mob = शून्य;
	पूर्ण

	vmw_tपंचांग_unmap_dma(vmw_tt);

	क्रम (i = 0; i < tपंचांग->num_pages; ++i)
		tपंचांग_mem_global_मुक्त_page(&tपंचांग_mem_glob, tपंचांग->pages[i],
					 PAGE_SIZE);

	tपंचांग_pool_मुक्त(&bdev->pool, tपंचांग);
पूर्ण

अटल काष्ठा tपंचांग_tt *vmw_tपंचांग_tt_create(काष्ठा tपंचांग_buffer_object *bo,
					uपूर्णांक32_t page_flags)
अणु
	काष्ठा vmw_tपंचांग_tt *vmw_be;
	पूर्णांक ret;

	vmw_be = kzalloc(माप(*vmw_be), GFP_KERNEL);
	अगर (!vmw_be)
		वापस शून्य;

	vmw_be->dev_priv = container_of(bo->bdev, काष्ठा vmw_निजी, bdev);
	vmw_be->mob = शून्य;

	अगर (vmw_be->dev_priv->map_mode == vmw_dma_alloc_coherent)
		ret = tपंचांग_sg_tt_init(&vmw_be->dma_tपंचांग, bo, page_flags,
				     tपंचांग_cached);
	अन्यथा
		ret = tपंचांग_tt_init(&vmw_be->dma_tपंचांग, bo, page_flags,
				  tपंचांग_cached);
	अगर (unlikely(ret != 0))
		जाओ out_no_init;

	वापस &vmw_be->dma_tपंचांग;
out_no_init:
	kमुक्त(vmw_be);
	वापस शून्य;
पूर्ण

अटल व्योम vmw_evict_flags(काष्ठा tपंचांग_buffer_object *bo,
		     काष्ठा tपंचांग_placement *placement)
अणु
	*placement = vmw_sys_placement;
पूर्ण

अटल पूर्णांक vmw_verअगरy_access(काष्ठा tपंचांग_buffer_object *bo, काष्ठा file *filp)
अणु
	काष्ठा tपंचांग_object_file *tfile =
		vmw_fpriv((काष्ठा drm_file *)filp->निजी_data)->tfile;

	वापस vmw_user_bo_verअगरy_access(bo, tfile);
पूर्ण

अटल पूर्णांक vmw_tपंचांग_io_mem_reserve(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा vmw_निजी *dev_priv = container_of(bdev, काष्ठा vmw_निजी, bdev);

	चयन (mem->mem_type) अणु
	हाल TTM_PL_SYSTEM:
	हाल VMW_PL_GMR:
	हाल VMW_PL_MOB:
		वापस 0;
	हाल TTM_PL_VRAM:
		mem->bus.offset = (mem->start << PAGE_SHIFT) +
			dev_priv->vram_start;
		mem->bus.is_iomem = true;
		mem->bus.caching = tपंचांग_cached;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * vmw_move_notअगरy - TTM move_notअगरy_callback
 *
 * @bo: The TTM buffer object about to move.
 * @old_mem: The old memory where we move from
 * @new_mem: The काष्ठा tपंचांग_resource indicating to what memory
 *       region the move is taking place.
 *
 * Calls move_notअगरy क्रम all subप्रणालीs needing it.
 * (currently only resources).
 */
अटल व्योम vmw_move_notअगरy(काष्ठा tपंचांग_buffer_object *bo,
			    काष्ठा tपंचांग_resource *old_mem,
			    काष्ठा tपंचांग_resource *new_mem)
अणु
	vmw_bo_move_notअगरy(bo, new_mem);
	vmw_query_move_notअगरy(bo, old_mem, new_mem);
पूर्ण


/**
 * vmw_swap_notअगरy - TTM move_notअगरy_callback
 *
 * @bo: The TTM buffer object about to be swapped out.
 */
अटल व्योम vmw_swap_notअगरy(काष्ठा tपंचांग_buffer_object *bo)
अणु
	vmw_bo_swap_notअगरy(bo);
	(व्योम) tपंचांग_bo_रुको(bo, false, false);
पूर्ण

अटल पूर्णांक vmw_move(काष्ठा tपंचांग_buffer_object *bo,
		    bool evict,
		    काष्ठा tपंचांग_operation_ctx *ctx,
		    काष्ठा tपंचांग_resource *new_mem,
		    काष्ठा tपंचांग_place *hop)
अणु
	काष्ठा tपंचांग_resource_manager *old_man = tपंचांग_manager_type(bo->bdev, bo->mem.mem_type);
	काष्ठा tपंचांग_resource_manager *new_man = tपंचांग_manager_type(bo->bdev, new_mem->mem_type);
	पूर्णांक ret;

	अगर (new_man->use_tt && new_mem->mem_type != TTM_PL_SYSTEM) अणु
		ret = vmw_tपंचांग_bind(bo->bdev, bo->tपंचांग, new_mem);
		अगर (ret)
			वापस ret;
	पूर्ण

	vmw_move_notअगरy(bo, &bo->mem, new_mem);

	अगर (old_man->use_tt && new_man->use_tt) अणु
		अगर (bo->mem.mem_type == TTM_PL_SYSTEM) अणु
			tपंचांग_bo_assign_mem(bo, new_mem);
			वापस 0;
		पूर्ण
		ret = tपंचांग_bo_रुको_ctx(bo, ctx);
		अगर (ret)
			जाओ fail;

		vmw_tपंचांग_unbind(bo->bdev, bo->tपंचांग);
		tपंचांग_resource_मुक्त(bo, &bo->mem);
		tपंचांग_bo_assign_mem(bo, new_mem);
		वापस 0;
	पूर्ण अन्यथा अणु
		ret = tपंचांग_bo_move_स_नकल(bo, ctx, new_mem);
		अगर (ret)
			जाओ fail;
	पूर्ण
	वापस 0;
fail:
	vmw_move_notअगरy(bo, new_mem, &bo->mem);
	वापस ret;
पूर्ण

काष्ठा tपंचांग_device_funcs vmw_bo_driver = अणु
	.tपंचांग_tt_create = &vmw_tपंचांग_tt_create,
	.tपंचांग_tt_populate = &vmw_tपंचांग_populate,
	.tपंचांग_tt_unpopulate = &vmw_tपंचांग_unpopulate,
	.tपंचांग_tt_destroy = &vmw_tपंचांग_destroy,
	.eviction_valuable = tपंचांग_bo_eviction_valuable,
	.evict_flags = vmw_evict_flags,
	.move = vmw_move,
	.verअगरy_access = vmw_verअगरy_access,
	.swap_notअगरy = vmw_swap_notअगरy,
	.io_mem_reserve = &vmw_tपंचांग_io_mem_reserve,
पूर्ण;

पूर्णांक vmw_bo_create_and_populate(काष्ठा vmw_निजी *dev_priv,
			       अचिन्हित दीर्घ bo_size,
			       काष्ठा tपंचांग_buffer_object **bo_p)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = false,
		.no_रुको_gpu = false
	पूर्ण;
	काष्ठा tपंचांग_buffer_object *bo;
	पूर्णांक ret;

	ret = vmw_bo_create_kernel(dev_priv, bo_size,
				   &vmw_sys_placement,
				   &bo);
	अगर (unlikely(ret != 0))
		वापस ret;

	ret = tपंचांग_bo_reserve(bo, false, true, शून्य);
	BUG_ON(ret != 0);
	ret = vmw_tपंचांग_populate(bo->bdev, bo->tपंचांग, &ctx);
	अगर (likely(ret == 0)) अणु
		काष्ठा vmw_tपंचांग_tt *vmw_tt =
			container_of(bo->tपंचांग, काष्ठा vmw_tपंचांग_tt, dma_tपंचांग);
		ret = vmw_tपंचांग_map_dma(vmw_tt);
	पूर्ण

	tपंचांग_bo_unreserve(bo);

	अगर (likely(ret == 0))
		*bo_p = bo;
	वापस ret;
पूर्ण
