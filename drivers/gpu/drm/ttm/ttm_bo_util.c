<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**************************************************************************
 *
 * Copyright (c) 2007-2009 VMware, Inc., Palo Alto, CA., USA
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

#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>
#समावेश <drm/drm_vma_manager.h>
#समावेश <linux/dma-buf-map.h>
#समावेश <linux/पन.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-resv.h>

काष्ठा tपंचांग_transfer_obj अणु
	काष्ठा tपंचांग_buffer_object base;
	काष्ठा tपंचांग_buffer_object *bo;
पूर्ण;

पूर्णांक tपंचांग_mem_io_reserve(काष्ठा tपंचांग_device *bdev,
		       काष्ठा tपंचांग_resource *mem)
अणु
	अगर (mem->bus.offset || mem->bus.addr)
		वापस 0;

	mem->bus.is_iomem = false;
	अगर (!bdev->funcs->io_mem_reserve)
		वापस 0;

	वापस bdev->funcs->io_mem_reserve(bdev, mem);
पूर्ण

व्योम tपंचांग_mem_io_मुक्त(काष्ठा tपंचांग_device *bdev,
		     काष्ठा tपंचांग_resource *mem)
अणु
	अगर (!mem->bus.offset && !mem->bus.addr)
		वापस;

	अगर (bdev->funcs->io_mem_मुक्त)
		bdev->funcs->io_mem_मुक्त(bdev, mem);

	mem->bus.offset = 0;
	mem->bus.addr = शून्य;
पूर्ण

अटल पूर्णांक tपंचांग_resource_ioremap(काष्ठा tपंचांग_device *bdev,
			       काष्ठा tपंचांग_resource *mem,
			       व्योम **भव)
अणु
	पूर्णांक ret;
	व्योम *addr;

	*भव = शून्य;
	ret = tपंचांग_mem_io_reserve(bdev, mem);
	अगर (ret || !mem->bus.is_iomem)
		वापस ret;

	अगर (mem->bus.addr) अणु
		addr = mem->bus.addr;
	पूर्ण अन्यथा अणु
		माप_प्रकार bus_size = (माप_प्रकार)mem->num_pages << PAGE_SHIFT;

		अगर (mem->bus.caching == tपंचांग_ग_लिखो_combined)
			addr = ioremap_wc(mem->bus.offset, bus_size);
#अगर_घोषित CONFIG_X86
		अन्यथा अगर (mem->bus.caching == tपंचांग_cached)
			addr = ioremap_cache(mem->bus.offset, bus_size);
#पूर्ण_अगर
		अन्यथा
			addr = ioremap(mem->bus.offset, bus_size);
		अगर (!addr) अणु
			tपंचांग_mem_io_मुक्त(bdev, mem);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	*भव = addr;
	वापस 0;
पूर्ण

अटल व्योम tपंचांग_resource_iounmap(काष्ठा tपंचांग_device *bdev,
				काष्ठा tपंचांग_resource *mem,
				व्योम *भव)
अणु
	अगर (भव && mem->bus.addr == शून्य)
		iounmap(भव);
	tपंचांग_mem_io_मुक्त(bdev, mem);
पूर्ण

अटल पूर्णांक tपंचांग_copy_io_page(व्योम *dst, व्योम *src, अचिन्हित दीर्घ page)
अणु
	uपूर्णांक32_t *dstP =
	    (uपूर्णांक32_t *) ((अचिन्हित दीर्घ)dst + (page << PAGE_SHIFT));
	uपूर्णांक32_t *srcP =
	    (uपूर्णांक32_t *) ((अचिन्हित दीर्घ)src + (page << PAGE_SHIFT));

	पूर्णांक i;
	क्रम (i = 0; i < PAGE_SIZE / माप(uपूर्णांक32_t); ++i)
		ioग_लिखो32(ioपढ़ो32(srcP++), dstP++);
	वापस 0;
पूर्ण

अटल पूर्णांक tपंचांग_copy_io_tपंचांग_page(काष्ठा tपंचांग_tt *tपंचांग, व्योम *src,
				अचिन्हित दीर्घ page,
				pgprot_t prot)
अणु
	काष्ठा page *d = tपंचांग->pages[page];
	व्योम *dst;

	अगर (!d)
		वापस -ENOMEM;

	src = (व्योम *)((अचिन्हित दीर्घ)src + (page << PAGE_SHIFT));
	dst = kmap_atomic_prot(d, prot);
	अगर (!dst)
		वापस -ENOMEM;

	स_नकल_fromio(dst, src, PAGE_SIZE);

	kunmap_atomic(dst);

	वापस 0;
पूर्ण

अटल पूर्णांक tपंचांग_copy_tपंचांग_io_page(काष्ठा tपंचांग_tt *tपंचांग, व्योम *dst,
				अचिन्हित दीर्घ page,
				pgprot_t prot)
अणु
	काष्ठा page *s = tपंचांग->pages[page];
	व्योम *src;

	अगर (!s)
		वापस -ENOMEM;

	dst = (व्योम *)((अचिन्हित दीर्घ)dst + (page << PAGE_SHIFT));
	src = kmap_atomic_prot(s, prot);
	अगर (!src)
		वापस -ENOMEM;

	स_नकल_toio(dst, src, PAGE_SIZE);

	kunmap_atomic(src);

	वापस 0;
पूर्ण

पूर्णांक tपंचांग_bo_move_स_नकल(काष्ठा tपंचांग_buffer_object *bo,
		       काष्ठा tपंचांग_operation_ctx *ctx,
		       काष्ठा tपंचांग_resource *new_mem)
अणु
	काष्ठा tपंचांग_device *bdev = bo->bdev;
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(bdev, new_mem->mem_type);
	काष्ठा tपंचांग_tt *tपंचांग = bo->tपंचांग;
	काष्ठा tपंचांग_resource *old_mem = &bo->mem;
	काष्ठा tपंचांग_resource old_copy = *old_mem;
	व्योम *old_iomap;
	व्योम *new_iomap;
	पूर्णांक ret;
	अचिन्हित दीर्घ i;

	ret = tपंचांग_bo_रुको_ctx(bo, ctx);
	अगर (ret)
		वापस ret;

	ret = tपंचांग_resource_ioremap(bdev, old_mem, &old_iomap);
	अगर (ret)
		वापस ret;
	ret = tपंचांग_resource_ioremap(bdev, new_mem, &new_iomap);
	अगर (ret)
		जाओ out;

	/*
	 * Single TTM move. NOP.
	 */
	अगर (old_iomap == शून्य && new_iomap == शून्य)
		जाओ out2;

	/*
	 * Don't move nonexistent data. Clear destination instead.
	 */
	अगर (old_iomap == शून्य &&
	    (tपंचांग == शून्य || (!tपंचांग_tt_is_populated(tपंचांग) &&
			     !(tपंचांग->page_flags & TTM_PAGE_FLAG_SWAPPED)))) अणु
		स_रखो_io(new_iomap, 0, new_mem->num_pages*PAGE_SIZE);
		जाओ out2;
	पूर्ण

	/*
	 * TTM might be null क्रम moves within the same region.
	 */
	अगर (tपंचांग) अणु
		ret = tपंचांग_tt_populate(bdev, tपंचांग, ctx);
		अगर (ret)
			जाओ out1;
	पूर्ण

	क्रम (i = 0; i < new_mem->num_pages; ++i) अणु
		अगर (old_iomap == शून्य) अणु
			pgprot_t prot = tपंचांग_io_prot(bo, old_mem, PAGE_KERNEL);
			ret = tपंचांग_copy_tपंचांग_io_page(tपंचांग, new_iomap, i,
						   prot);
		पूर्ण अन्यथा अगर (new_iomap == शून्य) अणु
			pgprot_t prot = tपंचांग_io_prot(bo, new_mem, PAGE_KERNEL);
			ret = tपंचांग_copy_io_tपंचांग_page(tपंचांग, old_iomap, i,
						   prot);
		पूर्ण अन्यथा अणु
			ret = tपंचांग_copy_io_page(new_iomap, old_iomap, i);
		पूर्ण
		अगर (ret)
			जाओ out1;
	पूर्ण
	mb();
out2:
	old_copy = *old_mem;

	tपंचांग_bo_assign_mem(bo, new_mem);

	अगर (!man->use_tt)
		tपंचांग_bo_tt_destroy(bo);

out1:
	tपंचांग_resource_iounmap(bdev, old_mem, new_iomap);
out:
	tपंचांग_resource_iounmap(bdev, &old_copy, old_iomap);

	/*
	 * On error, keep the mm node!
	 */
	अगर (!ret)
		tपंचांग_resource_मुक्त(bo, &old_copy);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_move_स_नकल);

अटल व्योम tपंचांग_transfered_destroy(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा tपंचांग_transfer_obj *fbo;

	fbo = container_of(bo, काष्ठा tपंचांग_transfer_obj, base);
	tपंचांग_bo_put(fbo->bo);
	kमुक्त(fbo);
पूर्ण

/**
 * tपंचांग_buffer_object_transfer
 *
 * @bo: A poपूर्णांकer to a काष्ठा tपंचांग_buffer_object.
 * @new_obj: A poपूर्णांकer to a poपूर्णांकer to a newly created tपंचांग_buffer_object,
 * holding the data of @bo with the old placement.
 *
 * This is a utility function that may be called after an accelerated move
 * has been scheduled. A new buffer object is created as a placeholder क्रम
 * the old data जबतक it's being copied. When that buffer object is idle,
 * it can be destroyed, releasing the space of the old placement.
 * Returns:
 * !0: Failure.
 */

अटल पूर्णांक tपंचांग_buffer_object_transfer(काष्ठा tपंचांग_buffer_object *bo,
				      काष्ठा tपंचांग_buffer_object **new_obj)
अणु
	काष्ठा tपंचांग_transfer_obj *fbo;
	पूर्णांक ret;

	fbo = kदो_स्मृति(माप(*fbo), GFP_KERNEL);
	अगर (!fbo)
		वापस -ENOMEM;

	fbo->base = *bo;

	tपंचांग_bo_get(bo);
	fbo->bo = bo;

	/**
	 * Fix up members that we shouldn't copy directly:
	 * TODO: Explicit member copy would probably be better here.
	 */

	atomic_inc(&tपंचांग_glob.bo_count);
	INIT_LIST_HEAD(&fbo->base.ddestroy);
	INIT_LIST_HEAD(&fbo->base.lru);
	fbo->base.moving = शून्य;
	drm_vma_node_reset(&fbo->base.base.vma_node);

	kref_init(&fbo->base.kref);
	fbo->base.destroy = &tपंचांग_transfered_destroy;
	fbo->base.pin_count = 0;
	अगर (bo->type != tपंचांग_bo_type_sg)
		fbo->base.base.resv = &fbo->base.base._resv;

	dma_resv_init(&fbo->base.base._resv);
	fbo->base.base.dev = शून्य;
	ret = dma_resv_trylock(&fbo->base.base._resv);
	WARN_ON(!ret);

	tपंचांग_bo_move_to_lru_tail_unlocked(&fbo->base);

	*new_obj = &fbo->base;
	वापस 0;
पूर्ण

pgprot_t tपंचांग_io_prot(काष्ठा tपंचांग_buffer_object *bo, काष्ठा tपंचांग_resource *res,
		     pgprot_t पंचांगp)
अणु
	काष्ठा tपंचांग_resource_manager *man;
	क्रमागत tपंचांग_caching caching;

	man = tपंचांग_manager_type(bo->bdev, res->mem_type);
	caching = man->use_tt ? bo->tपंचांग->caching : res->bus.caching;

	/* Cached mappings need no adjusपंचांगent */
	अगर (caching == tपंचांग_cached)
		वापस पंचांगp;

#अगर defined(__i386__) || defined(__x86_64__)
	अगर (caching == tपंचांग_ग_लिखो_combined)
		पंचांगp = pgprot_ग_लिखोcombine(पंचांगp);
	अन्यथा अगर (boot_cpu_data.x86 > 3)
		पंचांगp = pgprot_noncached(पंचांगp);
#पूर्ण_अगर
#अगर defined(__ia64__) || defined(__arm__) || defined(__aarch64__) || \
    defined(__घातerpc__) || defined(__mips__)
	अगर (caching == tपंचांग_ग_लिखो_combined)
		पंचांगp = pgprot_ग_लिखोcombine(पंचांगp);
	अन्यथा
		पंचांगp = pgprot_noncached(पंचांगp);
#पूर्ण_अगर
#अगर defined(__sparc__)
	पंचांगp = pgprot_noncached(पंचांगp);
#पूर्ण_अगर
	वापस पंचांगp;
पूर्ण
EXPORT_SYMBOL(tपंचांग_io_prot);

अटल पूर्णांक tपंचांग_bo_ioremap(काष्ठा tपंचांग_buffer_object *bo,
			  अचिन्हित दीर्घ offset,
			  अचिन्हित दीर्घ size,
			  काष्ठा tपंचांग_bo_kmap_obj *map)
अणु
	काष्ठा tपंचांग_resource *mem = &bo->mem;

	अगर (bo->mem.bus.addr) अणु
		map->bo_kmap_type = tपंचांग_bo_map_premapped;
		map->भव = (व्योम *)(((u8 *)bo->mem.bus.addr) + offset);
	पूर्ण अन्यथा अणु
		map->bo_kmap_type = tपंचांग_bo_map_iomap;
		अगर (mem->bus.caching == tपंचांग_ग_लिखो_combined)
			map->भव = ioremap_wc(bo->mem.bus.offset + offset,
						  size);
#अगर_घोषित CONFIG_X86
		अन्यथा अगर (mem->bus.caching == tपंचांग_cached)
			map->भव = ioremap_cache(bo->mem.bus.offset + offset,
						  size);
#पूर्ण_अगर
		अन्यथा
			map->भव = ioremap(bo->mem.bus.offset + offset,
					       size);
	पूर्ण
	वापस (!map->भव) ? -ENOMEM : 0;
पूर्ण

अटल पूर्णांक tपंचांग_bo_kmap_tपंचांग(काष्ठा tपंचांग_buffer_object *bo,
			   अचिन्हित दीर्घ start_page,
			   अचिन्हित दीर्घ num_pages,
			   काष्ठा tपंचांग_bo_kmap_obj *map)
अणु
	काष्ठा tपंचांग_resource *mem = &bo->mem;
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = false,
		.no_रुको_gpu = false
	पूर्ण;
	काष्ठा tपंचांग_tt *tपंचांग = bo->tपंचांग;
	pgprot_t prot;
	पूर्णांक ret;

	BUG_ON(!tपंचांग);

	ret = tपंचांग_tt_populate(bo->bdev, tपंचांग, &ctx);
	अगर (ret)
		वापस ret;

	अगर (num_pages == 1 && tपंचांग->caching == tपंचांग_cached) अणु
		/*
		 * We're mapping a single page, and the desired
		 * page protection is consistent with the bo.
		 */

		map->bo_kmap_type = tपंचांग_bo_map_kmap;
		map->page = tपंचांग->pages[start_page];
		map->भव = kmap(map->page);
	पूर्ण अन्यथा अणु
		/*
		 * We need to use vmap to get the desired page protection
		 * or to make the buffer object look contiguous.
		 */
		prot = tपंचांग_io_prot(bo, mem, PAGE_KERNEL);
		map->bo_kmap_type = tपंचांग_bo_map_vmap;
		map->भव = vmap(tपंचांग->pages + start_page, num_pages,
				    0, prot);
	पूर्ण
	वापस (!map->भव) ? -ENOMEM : 0;
पूर्ण

पूर्णांक tपंचांग_bo_kmap(काष्ठा tपंचांग_buffer_object *bo,
		अचिन्हित दीर्घ start_page, अचिन्हित दीर्घ num_pages,
		काष्ठा tपंचांग_bo_kmap_obj *map)
अणु
	अचिन्हित दीर्घ offset, size;
	पूर्णांक ret;

	map->भव = शून्य;
	map->bo = bo;
	अगर (num_pages > bo->mem.num_pages)
		वापस -EINVAL;
	अगर ((start_page + num_pages) > bo->mem.num_pages)
		वापस -EINVAL;

	ret = tपंचांग_mem_io_reserve(bo->bdev, &bo->mem);
	अगर (ret)
		वापस ret;
	अगर (!bo->mem.bus.is_iomem) अणु
		वापस tपंचांग_bo_kmap_tपंचांग(bo, start_page, num_pages, map);
	पूर्ण अन्यथा अणु
		offset = start_page << PAGE_SHIFT;
		size = num_pages << PAGE_SHIFT;
		वापस tपंचांग_bo_ioremap(bo, offset, size, map);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_kmap);

व्योम tपंचांग_bo_kunmap(काष्ठा tपंचांग_bo_kmap_obj *map)
अणु
	अगर (!map->भव)
		वापस;
	चयन (map->bo_kmap_type) अणु
	हाल tपंचांग_bo_map_iomap:
		iounmap(map->भव);
		अवरोध;
	हाल tपंचांग_bo_map_vmap:
		vunmap(map->भव);
		अवरोध;
	हाल tपंचांग_bo_map_kmap:
		kunmap(map->page);
		अवरोध;
	हाल tपंचांग_bo_map_premapped:
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	tपंचांग_mem_io_मुक्त(map->bo->bdev, &map->bo->mem);
	map->भव = शून्य;
	map->page = शून्य;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_kunmap);

पूर्णांक tपंचांग_bo_vmap(काष्ठा tपंचांग_buffer_object *bo, काष्ठा dma_buf_map *map)
अणु
	काष्ठा tपंचांग_resource *mem = &bo->mem;
	पूर्णांक ret;

	ret = tपंचांग_mem_io_reserve(bo->bdev, mem);
	अगर (ret)
		वापस ret;

	अगर (mem->bus.is_iomem) अणु
		व्योम __iomem *vaddr_iomem;

		अगर (mem->bus.addr)
			vaddr_iomem = (व्योम __iomem *)mem->bus.addr;
		अन्यथा अगर (mem->bus.caching == tपंचांग_ग_लिखो_combined)
			vaddr_iomem = ioremap_wc(mem->bus.offset,
						 bo->base.size);
#अगर_घोषित CONFIG_X86
		अन्यथा अगर (mem->bus.caching == tपंचांग_cached)
			vaddr_iomem = ioremap_cache(mem->bus.offset,
						  bo->base.size);
#पूर्ण_अगर
		अन्यथा
			vaddr_iomem = ioremap(mem->bus.offset, bo->base.size);

		अगर (!vaddr_iomem)
			वापस -ENOMEM;

		dma_buf_map_set_vaddr_iomem(map, vaddr_iomem);

	पूर्ण अन्यथा अणु
		काष्ठा tपंचांग_operation_ctx ctx = अणु
			.पूर्णांकerruptible = false,
			.no_रुको_gpu = false
		पूर्ण;
		काष्ठा tपंचांग_tt *tपंचांग = bo->tपंचांग;
		pgprot_t prot;
		व्योम *vaddr;

		ret = tपंचांग_tt_populate(bo->bdev, tपंचांग, &ctx);
		अगर (ret)
			वापस ret;

		/*
		 * We need to use vmap to get the desired page protection
		 * or to make the buffer object look contiguous.
		 */
		prot = tपंचांग_io_prot(bo, mem, PAGE_KERNEL);
		vaddr = vmap(tपंचांग->pages, tपंचांग->num_pages, 0, prot);
		अगर (!vaddr)
			वापस -ENOMEM;

		dma_buf_map_set_vaddr(map, vaddr);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_vmap);

व्योम tपंचांग_bo_vunmap(काष्ठा tपंचांग_buffer_object *bo, काष्ठा dma_buf_map *map)
अणु
	काष्ठा tपंचांग_resource *mem = &bo->mem;

	अगर (dma_buf_map_is_null(map))
		वापस;

	अगर (!map->is_iomem)
		vunmap(map->vaddr);
	अन्यथा अगर (!mem->bus.addr)
		iounmap(map->vaddr_iomem);
	dma_buf_map_clear(map);

	tपंचांग_mem_io_मुक्त(bo->bdev, &bo->mem);
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_vunmap);

अटल पूर्णांक tपंचांग_bo_रुको_मुक्त_node(काष्ठा tपंचांग_buffer_object *bo,
				 bool dst_use_tt)
अणु
	पूर्णांक ret;
	ret = tपंचांग_bo_रुको(bo, false, false);
	अगर (ret)
		वापस ret;

	अगर (!dst_use_tt)
		tपंचांग_bo_tt_destroy(bo);
	tपंचांग_resource_मुक्त(bo, &bo->mem);
	वापस 0;
पूर्ण

अटल पूर्णांक tपंचांग_bo_move_to_ghost(काष्ठा tपंचांग_buffer_object *bo,
				काष्ठा dma_fence *fence,
				bool dst_use_tt)
अणु
	काष्ठा tपंचांग_buffer_object *ghost_obj;
	पूर्णांक ret;

	/**
	 * This should help pipeline ordinary buffer moves.
	 *
	 * Hang old buffer memory on a new buffer object,
	 * and leave it to be released when the GPU
	 * operation has completed.
	 */

	dma_fence_put(bo->moving);
	bo->moving = dma_fence_get(fence);

	ret = tपंचांग_buffer_object_transfer(bo, &ghost_obj);
	अगर (ret)
		वापस ret;

	dma_resv_add_excl_fence(&ghost_obj->base._resv, fence);

	/**
	 * If we're not moving to fixed memory, the TTM object
	 * needs to stay alive. Otherwhise hang it on the ghost
	 * bo to be unbound and destroyed.
	 */

	अगर (dst_use_tt)
		ghost_obj->tपंचांग = शून्य;
	अन्यथा
		bo->tपंचांग = शून्य;

	dma_resv_unlock(&ghost_obj->base._resv);
	tपंचांग_bo_put(ghost_obj);
	वापस 0;
पूर्ण

अटल व्योम tपंचांग_bo_move_pipeline_evict(काष्ठा tपंचांग_buffer_object *bo,
				       काष्ठा dma_fence *fence)
अणु
	काष्ठा tपंचांग_device *bdev = bo->bdev;
	काष्ठा tपंचांग_resource_manager *from = tपंचांग_manager_type(bdev, bo->mem.mem_type);

	/**
	 * BO करोesn't have a TTM we need to bind/unbind. Just remember
	 * this eviction and मुक्त up the allocation
	 */
	spin_lock(&from->move_lock);
	अगर (!from->move || dma_fence_is_later(fence, from->move)) अणु
		dma_fence_put(from->move);
		from->move = dma_fence_get(fence);
	पूर्ण
	spin_unlock(&from->move_lock);

	tपंचांग_resource_मुक्त(bo, &bo->mem);

	dma_fence_put(bo->moving);
	bo->moving = dma_fence_get(fence);
पूर्ण

पूर्णांक tपंचांग_bo_move_accel_cleanup(काष्ठा tपंचांग_buffer_object *bo,
			      काष्ठा dma_fence *fence,
			      bool evict,
			      bool pipeline,
			      काष्ठा tपंचांग_resource *new_mem)
अणु
	काष्ठा tपंचांग_device *bdev = bo->bdev;
	काष्ठा tपंचांग_resource_manager *from = tपंचांग_manager_type(bdev, bo->mem.mem_type);
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(bdev, new_mem->mem_type);
	पूर्णांक ret = 0;

	dma_resv_add_excl_fence(bo->base.resv, fence);
	अगर (!evict)
		ret = tपंचांग_bo_move_to_ghost(bo, fence, man->use_tt);
	अन्यथा अगर (!from->use_tt && pipeline)
		tपंचांग_bo_move_pipeline_evict(bo, fence);
	अन्यथा
		ret = tपंचांग_bo_रुको_मुक्त_node(bo, man->use_tt);

	अगर (ret)
		वापस ret;

	tपंचांग_bo_assign_mem(bo, new_mem);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_move_accel_cleanup);

पूर्णांक tपंचांग_bo_pipeline_gutting(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा tपंचांग_buffer_object *ghost;
	पूर्णांक ret;

	ret = tपंचांग_buffer_object_transfer(bo, &ghost);
	अगर (ret)
		वापस ret;

	ret = dma_resv_copy_fences(&ghost->base._resv, bo->base.resv);
	/* Last resort, रुको क्रम the BO to be idle when we are OOM */
	अगर (ret)
		tपंचांग_bo_रुको(bo, false, false);

	स_रखो(&bo->mem, 0, माप(bo->mem));
	bo->mem.mem_type = TTM_PL_SYSTEM;
	bo->tपंचांग = शून्य;

	dma_resv_unlock(&ghost->base._resv);
	tपंचांग_bo_put(ghost);

	वापस 0;
पूर्ण
