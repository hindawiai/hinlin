<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright 2012 Red Hat Inc
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/dma-resv.h>

#समावेश "i915_drv.h"
#समावेश "i915_gem_object.h"
#समावेश "i915_scatterlist.h"

अटल काष्ठा drm_i915_gem_object *dma_buf_to_obj(काष्ठा dma_buf *buf)
अणु
	वापस to_पूर्णांकel_bo(buf->priv);
पूर्ण

अटल काष्ठा sg_table *i915_gem_map_dma_buf(काष्ठा dma_buf_attachment *attachment,
					     क्रमागत dma_data_direction dir)
अणु
	काष्ठा drm_i915_gem_object *obj = dma_buf_to_obj(attachment->dmabuf);
	काष्ठा sg_table *st;
	काष्ठा scatterlist *src, *dst;
	पूर्णांक ret, i;

	ret = i915_gem_object_pin_pages_unlocked(obj);
	अगर (ret)
		जाओ err;

	/* Copy sg so that we make an independent mapping */
	st = kदो_स्मृति(माप(काष्ठा sg_table), GFP_KERNEL);
	अगर (st == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_unpin_pages;
	पूर्ण

	ret = sg_alloc_table(st, obj->mm.pages->nents, GFP_KERNEL);
	अगर (ret)
		जाओ err_मुक्त;

	src = obj->mm.pages->sgl;
	dst = st->sgl;
	क्रम (i = 0; i < obj->mm.pages->nents; i++) अणु
		sg_set_page(dst, sg_page(src), src->length, 0);
		dst = sg_next(dst);
		src = sg_next(src);
	पूर्ण

	ret = dma_map_sgtable(attachment->dev, st, dir, DMA_ATTR_SKIP_CPU_SYNC);
	अगर (ret)
		जाओ err_मुक्त_sg;

	वापस st;

err_मुक्त_sg:
	sg_मुक्त_table(st);
err_मुक्त:
	kमुक्त(st);
err_unpin_pages:
	i915_gem_object_unpin_pages(obj);
err:
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम i915_gem_unmap_dma_buf(काष्ठा dma_buf_attachment *attachment,
				   काष्ठा sg_table *sg,
				   क्रमागत dma_data_direction dir)
अणु
	काष्ठा drm_i915_gem_object *obj = dma_buf_to_obj(attachment->dmabuf);

	dma_unmap_sgtable(attachment->dev, sg, dir, DMA_ATTR_SKIP_CPU_SYNC);
	sg_मुक्त_table(sg);
	kमुक्त(sg);

	i915_gem_object_unpin_pages(obj);
पूर्ण

अटल पूर्णांक i915_gem_dmabuf_vmap(काष्ठा dma_buf *dma_buf, काष्ठा dma_buf_map *map)
अणु
	काष्ठा drm_i915_gem_object *obj = dma_buf_to_obj(dma_buf);
	व्योम *vaddr;

	vaddr = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WB);
	अगर (IS_ERR(vaddr))
		वापस PTR_ERR(vaddr);

	dma_buf_map_set_vaddr(map, vaddr);

	वापस 0;
पूर्ण

अटल व्योम i915_gem_dmabuf_vunmap(काष्ठा dma_buf *dma_buf, काष्ठा dma_buf_map *map)
अणु
	काष्ठा drm_i915_gem_object *obj = dma_buf_to_obj(dma_buf);

	i915_gem_object_flush_map(obj);
	i915_gem_object_unpin_map(obj);
पूर्ण

अटल पूर्णांक i915_gem_dmabuf_mmap(काष्ठा dma_buf *dma_buf, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_i915_gem_object *obj = dma_buf_to_obj(dma_buf);
	पूर्णांक ret;

	अगर (obj->base.size < vma->vm_end - vma->vm_start)
		वापस -EINVAL;

	अगर (!obj->base.filp)
		वापस -ENODEV;

	ret = call_mmap(obj->base.filp, vma);
	अगर (ret)
		वापस ret;

	vma_set_file(vma, obj->base.filp);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_gem_begin_cpu_access(काष्ठा dma_buf *dma_buf, क्रमागत dma_data_direction direction)
अणु
	काष्ठा drm_i915_gem_object *obj = dma_buf_to_obj(dma_buf);
	bool ग_लिखो = (direction == DMA_BIसूचीECTIONAL || direction == DMA_TO_DEVICE);
	काष्ठा i915_gem_ww_ctx ww;
	पूर्णांक err;

	i915_gem_ww_ctx_init(&ww, true);
retry:
	err = i915_gem_object_lock(obj, &ww);
	अगर (!err)
		err = i915_gem_object_pin_pages(obj);
	अगर (!err) अणु
		err = i915_gem_object_set_to_cpu_करोमुख्य(obj, ग_लिखो);
		i915_gem_object_unpin_pages(obj);
	पूर्ण
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
	वापस err;
पूर्ण

अटल पूर्णांक i915_gem_end_cpu_access(काष्ठा dma_buf *dma_buf, क्रमागत dma_data_direction direction)
अणु
	काष्ठा drm_i915_gem_object *obj = dma_buf_to_obj(dma_buf);
	काष्ठा i915_gem_ww_ctx ww;
	पूर्णांक err;

	i915_gem_ww_ctx_init(&ww, true);
retry:
	err = i915_gem_object_lock(obj, &ww);
	अगर (!err)
		err = i915_gem_object_pin_pages(obj);
	अगर (!err) अणु
		err = i915_gem_object_set_to_gtt_करोमुख्य(obj, false);
		i915_gem_object_unpin_pages(obj);
	पूर्ण
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा dma_buf_ops i915_dmabuf_ops =  अणु
	.map_dma_buf = i915_gem_map_dma_buf,
	.unmap_dma_buf = i915_gem_unmap_dma_buf,
	.release = drm_gem_dmabuf_release,
	.mmap = i915_gem_dmabuf_mmap,
	.vmap = i915_gem_dmabuf_vmap,
	.vunmap = i915_gem_dmabuf_vunmap,
	.begin_cpu_access = i915_gem_begin_cpu_access,
	.end_cpu_access = i915_gem_end_cpu_access,
पूर्ण;

काष्ठा dma_buf *i915_gem_prime_export(काष्ठा drm_gem_object *gem_obj, पूर्णांक flags)
अणु
	काष्ठा drm_i915_gem_object *obj = to_पूर्णांकel_bo(gem_obj);
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);

	exp_info.ops = &i915_dmabuf_ops;
	exp_info.size = gem_obj->size;
	exp_info.flags = flags;
	exp_info.priv = gem_obj;
	exp_info.resv = obj->base.resv;

	अगर (obj->ops->dmabuf_export) अणु
		पूर्णांक ret = obj->ops->dmabuf_export(obj);
		अगर (ret)
			वापस ERR_PTR(ret);
	पूर्ण

	वापस drm_gem_dmabuf_export(gem_obj->dev, &exp_info);
पूर्ण

अटल पूर्णांक i915_gem_object_get_pages_dmabuf(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा sg_table *pages;
	अचिन्हित पूर्णांक sg_page_sizes;

	pages = dma_buf_map_attachment(obj->base.import_attach,
				       DMA_BIसूचीECTIONAL);
	अगर (IS_ERR(pages))
		वापस PTR_ERR(pages);

	sg_page_sizes = i915_sg_page_sizes(pages->sgl);

	__i915_gem_object_set_pages(obj, pages, sg_page_sizes);

	वापस 0;
पूर्ण

अटल व्योम i915_gem_object_put_pages_dmabuf(काष्ठा drm_i915_gem_object *obj,
					     काष्ठा sg_table *pages)
अणु
	dma_buf_unmap_attachment(obj->base.import_attach, pages,
				 DMA_BIसूचीECTIONAL);
पूर्ण

अटल स्थिर काष्ठा drm_i915_gem_object_ops i915_gem_object_dmabuf_ops = अणु
	.name = "i915_gem_object_dmabuf",
	.get_pages = i915_gem_object_get_pages_dmabuf,
	.put_pages = i915_gem_object_put_pages_dmabuf,
पूर्ण;

काष्ठा drm_gem_object *i915_gem_prime_import(काष्ठा drm_device *dev,
					     काष्ठा dma_buf *dma_buf)
अणु
	अटल काष्ठा lock_class_key lock_class;
	काष्ठा dma_buf_attachment *attach;
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांक ret;

	/* is this one of own objects? */
	अगर (dma_buf->ops == &i915_dmabuf_ops) अणु
		obj = dma_buf_to_obj(dma_buf);
		/* is it from our device? */
		अगर (obj->base.dev == dev) अणु
			/*
			 * Importing dmabuf exported from out own gem increases
			 * refcount on gem itself instead of f_count of dmabuf.
			 */
			वापस &i915_gem_object_get(obj)->base;
		पूर्ण
	पूर्ण

	अगर (i915_gem_object_size_2big(dma_buf->size))
		वापस ERR_PTR(-E2BIG);

	/* need to attach */
	attach = dma_buf_attach(dma_buf, dev->dev);
	अगर (IS_ERR(attach))
		वापस ERR_CAST(attach);

	get_dma_buf(dma_buf);

	obj = i915_gem_object_alloc();
	अगर (obj == शून्य) अणु
		ret = -ENOMEM;
		जाओ fail_detach;
	पूर्ण

	drm_gem_निजी_object_init(dev, &obj->base, dma_buf->size);
	i915_gem_object_init(obj, &i915_gem_object_dmabuf_ops, &lock_class, 0);
	obj->base.import_attach = attach;
	obj->base.resv = dma_buf->resv;

	/* We use GTT as लघुhand क्रम a coherent करोमुख्य, one that is
	 * neither in the GPU cache nor in the CPU cache, where all
	 * ग_लिखोs are immediately visible in memory. (That's not strictly
	 * true, but it's बंद! There are पूर्णांकernal buffers such as the
	 * ग_लिखो-combined buffer or a delay through the chipset क्रम GTT
	 * ग_लिखोs that करो require us to treat GTT as a separate cache करोमुख्य.)
	 */
	obj->पढ़ो_करोमुख्यs = I915_GEM_DOMAIN_GTT;
	obj->ग_लिखो_करोमुख्य = 0;

	वापस &obj->base;

fail_detach:
	dma_buf_detach(dma_buf, attach);
	dma_buf_put(dma_buf);

	वापस ERR_PTR(ret);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/mock_dmabuf.c"
#समावेश "selftests/i915_gem_dmabuf.c"
#पूर्ण_अगर
