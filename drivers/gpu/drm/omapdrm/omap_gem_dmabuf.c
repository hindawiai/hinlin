<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Rob Clark <rob.clark@linaro.org>
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/highस्मृति.स>

#समावेश <drm/drm_prime.h>

#समावेश "omap_drv.h"

/* -----------------------------------------------------------------------------
 * DMABUF Export
 */

अटल काष्ठा sg_table *omap_gem_map_dma_buf(
		काष्ठा dma_buf_attachment *attachment,
		क्रमागत dma_data_direction dir)
अणु
	काष्ठा drm_gem_object *obj = attachment->dmabuf->priv;
	काष्ठा sg_table *sg;
	dma_addr_t dma_addr;
	पूर्णांक ret;

	sg = kzalloc(माप(*sg), GFP_KERNEL);
	अगर (!sg)
		वापस ERR_PTR(-ENOMEM);

	/* camera, etc, need physically contiguous.. but we need a
	 * better way to know this..
	 */
	ret = omap_gem_pin(obj, &dma_addr);
	अगर (ret)
		जाओ out;

	ret = sg_alloc_table(sg, 1, GFP_KERNEL);
	अगर (ret)
		जाओ out;

	sg_init_table(sg->sgl, 1);
	sg_dma_len(sg->sgl) = obj->size;
	sg_set_page(sg->sgl, pfn_to_page(PFN_DOWN(dma_addr)), obj->size, 0);
	sg_dma_address(sg->sgl) = dma_addr;

	/* this must be after omap_gem_pin() to ensure we have pages attached */
	omap_gem_dma_sync_buffer(obj, dir);

	वापस sg;
out:
	kमुक्त(sg);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम omap_gem_unmap_dma_buf(काष्ठा dma_buf_attachment *attachment,
		काष्ठा sg_table *sg, क्रमागत dma_data_direction dir)
अणु
	काष्ठा drm_gem_object *obj = attachment->dmabuf->priv;
	omap_gem_unpin(obj);
	sg_मुक्त_table(sg);
	kमुक्त(sg);
पूर्ण

अटल पूर्णांक omap_gem_dmabuf_begin_cpu_access(काष्ठा dma_buf *buffer,
		क्रमागत dma_data_direction dir)
अणु
	काष्ठा drm_gem_object *obj = buffer->priv;
	काष्ठा page **pages;
	अगर (omap_gem_flags(obj) & OMAP_BO_TILED_MASK) अणु
		/* TODO we would need to pin at least part of the buffer to
		 * get de-tiled view.  For now just reject it.
		 */
		वापस -ENOMEM;
	पूर्ण
	/* make sure we have the pages: */
	वापस omap_gem_get_pages(obj, &pages, true);
पूर्ण

अटल पूर्णांक omap_gem_dmabuf_end_cpu_access(काष्ठा dma_buf *buffer,
					  क्रमागत dma_data_direction dir)
अणु
	काष्ठा drm_gem_object *obj = buffer->priv;
	omap_gem_put_pages(obj);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_gem_dmabuf_mmap(काष्ठा dma_buf *buffer,
		काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_gem_object *obj = buffer->priv;
	पूर्णांक ret = 0;

	ret = drm_gem_mmap_obj(obj, omap_gem_mmap_size(obj), vma);
	अगर (ret < 0)
		वापस ret;

	वापस omap_gem_mmap_obj(obj, vma);
पूर्ण

अटल स्थिर काष्ठा dma_buf_ops omap_dmabuf_ops = अणु
	.map_dma_buf = omap_gem_map_dma_buf,
	.unmap_dma_buf = omap_gem_unmap_dma_buf,
	.release = drm_gem_dmabuf_release,
	.begin_cpu_access = omap_gem_dmabuf_begin_cpu_access,
	.end_cpu_access = omap_gem_dmabuf_end_cpu_access,
	.mmap = omap_gem_dmabuf_mmap,
पूर्ण;

काष्ठा dma_buf *omap_gem_prime_export(काष्ठा drm_gem_object *obj, पूर्णांक flags)
अणु
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);

	exp_info.ops = &omap_dmabuf_ops;
	exp_info.size = obj->size;
	exp_info.flags = flags;
	exp_info.priv = obj;

	वापस drm_gem_dmabuf_export(obj->dev, &exp_info);
पूर्ण

/* -----------------------------------------------------------------------------
 * DMABUF Import
 */

काष्ठा drm_gem_object *omap_gem_prime_import(काष्ठा drm_device *dev,
					     काष्ठा dma_buf *dma_buf)
अणु
	काष्ठा dma_buf_attachment *attach;
	काष्ठा drm_gem_object *obj;
	काष्ठा sg_table *sgt;
	पूर्णांक ret;

	अगर (dma_buf->ops == &omap_dmabuf_ops) अणु
		obj = dma_buf->priv;
		अगर (obj->dev == dev) अणु
			/*
			 * Importing dmabuf exported from out own gem increases
			 * refcount on gem itself instead of f_count of dmabuf.
			 */
			drm_gem_object_get(obj);
			वापस obj;
		पूर्ण
	पूर्ण

	attach = dma_buf_attach(dma_buf, dev->dev);
	अगर (IS_ERR(attach))
		वापस ERR_CAST(attach);

	get_dma_buf(dma_buf);

	sgt = dma_buf_map_attachment(attach, DMA_TO_DEVICE);
	अगर (IS_ERR(sgt)) अणु
		ret = PTR_ERR(sgt);
		जाओ fail_detach;
	पूर्ण

	obj = omap_gem_new_dmabuf(dev, dma_buf->size, sgt);
	अगर (IS_ERR(obj)) अणु
		ret = PTR_ERR(obj);
		जाओ fail_unmap;
	पूर्ण

	obj->import_attach = attach;

	वापस obj;

fail_unmap:
	dma_buf_unmap_attachment(attach, sgt, DMA_TO_DEVICE);
fail_detach:
	dma_buf_detach(dma_buf, attach);
	dma_buf_put(dma_buf);

	वापस ERR_PTR(ret);
पूर्ण
