<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**************************************************************************
 *
 * Copyright (c) 2006-2009 VMware, Inc., Palo Alto, CA., USA
 * All Rights Reserved.
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
/*
 * Authors: Thomas Hellstrom <thellstrom-at-vmware-करोt-com>
 */

#घोषणा pr_fmt(fmt) "[TTM] " fmt

#समावेश <linux/sched.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/file.h>
#समावेश <drm/drm_cache.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>

#समावेश "ttm_module.h"

अटल अचिन्हित दीर्घ tपंचांग_pages_limit;

MODULE_PARM_DESC(pages_limit, "Limit for the allocated pages");
module_param_named(pages_limit, tपंचांग_pages_limit, uदीर्घ, 0644);

अटल अचिन्हित दीर्घ tपंचांग_dma32_pages_limit;

MODULE_PARM_DESC(dma32_pages_limit, "Limit for the allocated DMA32 pages");
module_param_named(dma32_pages_limit, tपंचांग_dma32_pages_limit, uदीर्घ, 0644);

अटल atomic_दीर्घ_t tपंचांग_pages_allocated;
अटल atomic_दीर्घ_t tपंचांग_dma32_pages_allocated;

/*
 * Allocates a tपंचांग काष्ठाure क्रम the given BO.
 */
पूर्णांक tपंचांग_tt_create(काष्ठा tपंचांग_buffer_object *bo, bool zero_alloc)
अणु
	काष्ठा tपंचांग_device *bdev = bo->bdev;
	uपूर्णांक32_t page_flags = 0;

	dma_resv_निश्चित_held(bo->base.resv);

	अगर (bo->tपंचांग)
		वापस 0;

	चयन (bo->type) अणु
	हाल tपंचांग_bo_type_device:
		अगर (zero_alloc)
			page_flags |= TTM_PAGE_FLAG_ZERO_ALLOC;
		अवरोध;
	हाल tपंचांग_bo_type_kernel:
		अवरोध;
	हाल tपंचांग_bo_type_sg:
		page_flags |= TTM_PAGE_FLAG_SG;
		अवरोध;
	शेष:
		pr_err("Illegal buffer object type\n");
		वापस -EINVAL;
	पूर्ण

	bo->tपंचांग = bdev->funcs->tपंचांग_tt_create(bo, page_flags);
	अगर (unlikely(bo->tपंचांग == शून्य))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/*
 * Allocates storage क्रम poपूर्णांकers to the pages that back the tपंचांग.
 */
अटल पूर्णांक tपंचांग_tt_alloc_page_directory(काष्ठा tपंचांग_tt *tपंचांग)
अणु
	tपंचांग->pages = kvदो_स्मृति_array(tपंचांग->num_pages, माप(व्योम*),
			GFP_KERNEL | __GFP_ZERO);
	अगर (!tपंचांग->pages)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक tपंचांग_dma_tt_alloc_page_directory(काष्ठा tपंचांग_tt *tपंचांग)
अणु
	tपंचांग->pages = kvदो_स्मृति_array(tपंचांग->num_pages,
				    माप(*tपंचांग->pages) +
				    माप(*tपंचांग->dma_address),
				    GFP_KERNEL | __GFP_ZERO);
	अगर (!tपंचांग->pages)
		वापस -ENOMEM;

	tपंचांग->dma_address = (व्योम *)(tपंचांग->pages + tपंचांग->num_pages);
	वापस 0;
पूर्ण

अटल पूर्णांक tपंचांग_sg_tt_alloc_page_directory(काष्ठा tपंचांग_tt *tपंचांग)
अणु
	tपंचांग->dma_address = kvदो_स्मृति_array(tपंचांग->num_pages,
					  माप(*tपंचांग->dma_address),
					  GFP_KERNEL | __GFP_ZERO);
	अगर (!tपंचांग->dma_address)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम tपंचांग_tt_destroy_common(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग)
अणु
	tपंचांग_tt_unpopulate(bdev, tपंचांग);

	अगर (tपंचांग->swap_storage)
		fput(tपंचांग->swap_storage);

	tपंचांग->swap_storage = शून्य;
पूर्ण
EXPORT_SYMBOL(tपंचांग_tt_destroy_common);

व्योम tपंचांग_tt_destroy(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग)
अणु
	bdev->funcs->tपंचांग_tt_destroy(bdev, tपंचांग);
पूर्ण

अटल व्योम tपंचांग_tt_init_fields(काष्ठा tपंचांग_tt *tपंचांग,
			       काष्ठा tपंचांग_buffer_object *bo,
			       uपूर्णांक32_t page_flags,
			       क्रमागत tपंचांग_caching caching)
अणु
	tपंचांग->num_pages = PAGE_ALIGN(bo->base.size) >> PAGE_SHIFT;
	tपंचांग->caching = tपंचांग_cached;
	tपंचांग->page_flags = page_flags;
	tपंचांग->dma_address = शून्य;
	tपंचांग->swap_storage = शून्य;
	tपंचांग->sg = bo->sg;
	tपंचांग->caching = caching;
पूर्ण

पूर्णांक tपंचांग_tt_init(काष्ठा tपंचांग_tt *tपंचांग, काष्ठा tपंचांग_buffer_object *bo,
		uपूर्णांक32_t page_flags, क्रमागत tपंचांग_caching caching)
अणु
	tपंचांग_tt_init_fields(tपंचांग, bo, page_flags, caching);

	अगर (tपंचांग_tt_alloc_page_directory(tपंचांग)) अणु
		pr_err("Failed allocating page table\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tपंचांग_tt_init);

व्योम tपंचांग_tt_fini(काष्ठा tपंचांग_tt *tपंचांग)
अणु
	अगर (tपंचांग->pages)
		kvमुक्त(tपंचांग->pages);
	अन्यथा
		kvमुक्त(tपंचांग->dma_address);
	tपंचांग->pages = शून्य;
	tपंचांग->dma_address = शून्य;
पूर्ण
EXPORT_SYMBOL(tपंचांग_tt_fini);

पूर्णांक tपंचांग_sg_tt_init(काष्ठा tपंचांग_tt *tपंचांग, काष्ठा tपंचांग_buffer_object *bo,
		   uपूर्णांक32_t page_flags, क्रमागत tपंचांग_caching caching)
अणु
	पूर्णांक ret;

	tपंचांग_tt_init_fields(tपंचांग, bo, page_flags, caching);

	अगर (page_flags & TTM_PAGE_FLAG_SG)
		ret = tपंचांग_sg_tt_alloc_page_directory(tपंचांग);
	अन्यथा
		ret = tपंचांग_dma_tt_alloc_page_directory(tपंचांग);
	अगर (ret) अणु
		pr_err("Failed allocating page table\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tपंचांग_sg_tt_init);

पूर्णांक tपंचांग_tt_swapin(काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा address_space *swap_space;
	काष्ठा file *swap_storage;
	काष्ठा page *from_page;
	काष्ठा page *to_page;
	gfp_t gfp_mask;
	पूर्णांक i, ret;

	swap_storage = tपंचांग->swap_storage;
	BUG_ON(swap_storage == शून्य);

	swap_space = swap_storage->f_mapping;
	gfp_mask = mapping_gfp_mask(swap_space);

	क्रम (i = 0; i < tपंचांग->num_pages; ++i) अणु
		from_page = shmem_पढ़ो_mapping_page_gfp(swap_space, i,
							gfp_mask);
		अगर (IS_ERR(from_page)) अणु
			ret = PTR_ERR(from_page);
			जाओ out_err;
		पूर्ण
		to_page = tपंचांग->pages[i];
		अगर (unlikely(to_page == शून्य)) अणु
			ret = -ENOMEM;
			जाओ out_err;
		पूर्ण

		copy_highpage(to_page, from_page);
		put_page(from_page);
	पूर्ण

	fput(swap_storage);
	tपंचांग->swap_storage = शून्य;
	tपंचांग->page_flags &= ~TTM_PAGE_FLAG_SWAPPED;

	वापस 0;

out_err:
	वापस ret;
पूर्ण

/**
 * tपंचांग_tt_swapout - swap out tt object
 *
 * @bdev: TTM device काष्ठाure.
 * @tपंचांग: The काष्ठा tपंचांग_tt.
 * @gfp_flags: Flags to use क्रम memory allocation.
 *
 * Swapout a TT object to a shmem_file, वापस number of pages swapped out or
 * negative error code.
 */
पूर्णांक tपंचांग_tt_swapout(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग,
		   gfp_t gfp_flags)
अणु
	loff_t size = (loff_t)tपंचांग->num_pages << PAGE_SHIFT;
	काष्ठा address_space *swap_space;
	काष्ठा file *swap_storage;
	काष्ठा page *from_page;
	काष्ठा page *to_page;
	पूर्णांक i, ret;

	swap_storage = shmem_file_setup("ttm swap", size, 0);
	अगर (IS_ERR(swap_storage)) अणु
		pr_err("Failed allocating swap storage\n");
		वापस PTR_ERR(swap_storage);
	पूर्ण

	swap_space = swap_storage->f_mapping;
	gfp_flags &= mapping_gfp_mask(swap_space);

	क्रम (i = 0; i < tपंचांग->num_pages; ++i) अणु
		from_page = tपंचांग->pages[i];
		अगर (unlikely(from_page == शून्य))
			जारी;

		to_page = shmem_पढ़ो_mapping_page_gfp(swap_space, i, gfp_flags);
		अगर (IS_ERR(to_page)) अणु
			ret = PTR_ERR(to_page);
			जाओ out_err;
		पूर्ण
		copy_highpage(to_page, from_page);
		set_page_dirty(to_page);
		mark_page_accessed(to_page);
		put_page(to_page);
	पूर्ण

	tपंचांग_tt_unpopulate(bdev, tपंचांग);
	tपंचांग->swap_storage = swap_storage;
	tपंचांग->page_flags |= TTM_PAGE_FLAG_SWAPPED;

	वापस tपंचांग->num_pages;

out_err:
	fput(swap_storage);

	वापस ret;
पूर्ण

अटल व्योम tपंचांग_tt_add_mapping(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग)
अणु
	pgoff_t i;

	अगर (tपंचांग->page_flags & TTM_PAGE_FLAG_SG)
		वापस;

	क्रम (i = 0; i < tपंचांग->num_pages; ++i)
		tपंचांग->pages[i]->mapping = bdev->dev_mapping;
पूर्ण

पूर्णांक tपंचांग_tt_populate(काष्ठा tपंचांग_device *bdev,
		    काष्ठा tपंचांग_tt *tपंचांग, काष्ठा tपंचांग_operation_ctx *ctx)
अणु
	पूर्णांक ret;

	अगर (!tपंचांग)
		वापस -EINVAL;

	अगर (tपंचांग_tt_is_populated(tपंचांग))
		वापस 0;

	अगर (!(tपंचांग->page_flags & TTM_PAGE_FLAG_SG)) अणु
		atomic_दीर्घ_add(tपंचांग->num_pages, &tपंचांग_pages_allocated);
		अगर (bdev->pool.use_dma32)
			atomic_दीर्घ_add(tपंचांग->num_pages,
					&tपंचांग_dma32_pages_allocated);
	पूर्ण

	जबतक (atomic_दीर्घ_पढ़ो(&tपंचांग_pages_allocated) > tपंचांग_pages_limit ||
	       atomic_दीर्घ_पढ़ो(&tपंचांग_dma32_pages_allocated) >
	       tपंचांग_dma32_pages_limit) अणु

		ret = tपंचांग_global_swapout(ctx, GFP_KERNEL);
		अगर (ret == 0)
			अवरोध;
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	अगर (bdev->funcs->tपंचांग_tt_populate)
		ret = bdev->funcs->tपंचांग_tt_populate(bdev, tपंचांग, ctx);
	अन्यथा
		ret = tपंचांग_pool_alloc(&bdev->pool, tपंचांग, ctx);
	अगर (ret)
		जाओ error;

	tपंचांग_tt_add_mapping(bdev, tपंचांग);
	tपंचांग->page_flags |= TTM_PAGE_FLAG_PRIV_POPULATED;
	अगर (unlikely(tपंचांग->page_flags & TTM_PAGE_FLAG_SWAPPED)) अणु
		ret = tपंचांग_tt_swapin(tपंचांग);
		अगर (unlikely(ret != 0)) अणु
			tपंचांग_tt_unpopulate(bdev, tपंचांग);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;

error:
	अगर (!(tपंचांग->page_flags & TTM_PAGE_FLAG_SG)) अणु
		atomic_दीर्घ_sub(tपंचांग->num_pages, &tपंचांग_pages_allocated);
		अगर (bdev->pool.use_dma32)
			atomic_दीर्घ_sub(tपंचांग->num_pages,
					&tपंचांग_dma32_pages_allocated);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(tपंचांग_tt_populate);

अटल व्योम tपंचांग_tt_clear_mapping(काष्ठा tपंचांग_tt *tपंचांग)
अणु
	pgoff_t i;
	काष्ठा page **page = tपंचांग->pages;

	अगर (tपंचांग->page_flags & TTM_PAGE_FLAG_SG)
		वापस;

	क्रम (i = 0; i < tपंचांग->num_pages; ++i) अणु
		(*page)->mapping = शून्य;
		(*page++)->index = 0;
	पूर्ण
पूर्ण

व्योम tपंचांग_tt_unpopulate(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग)
अणु
	अगर (!tपंचांग_tt_is_populated(tपंचांग))
		वापस;

	tपंचांग_tt_clear_mapping(tपंचांग);
	अगर (bdev->funcs->tपंचांग_tt_unpopulate)
		bdev->funcs->tपंचांग_tt_unpopulate(bdev, tपंचांग);
	अन्यथा
		tपंचांग_pool_मुक्त(&bdev->pool, tपंचांग);

	अगर (!(tपंचांग->page_flags & TTM_PAGE_FLAG_SG)) अणु
		atomic_दीर्घ_sub(tपंचांग->num_pages, &tपंचांग_pages_allocated);
		अगर (bdev->pool.use_dma32)
			atomic_दीर्घ_sub(tपंचांग->num_pages,
					&tपंचांग_dma32_pages_allocated);
	पूर्ण

	tपंचांग->page_flags &= ~TTM_PAGE_FLAG_PRIV_POPULATED;
पूर्ण

/**
 * tपंचांग_tt_mgr_init - रेजिस्टर with the MM shrinker
 *
 * Register with the MM shrinker क्रम swapping out BOs.
 */
व्योम tपंचांग_tt_mgr_init(अचिन्हित दीर्घ num_pages, अचिन्हित दीर्घ num_dma32_pages)
अणु
	अगर (!tपंचांग_pages_limit)
		tपंचांग_pages_limit = num_pages;

	अगर (!tपंचांग_dma32_pages_limit)
		tपंचांग_dma32_pages_limit = num_dma32_pages;
पूर्ण
