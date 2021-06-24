<शैली गुरु>
/*
 * Copyright 2014 Canonical
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Andreas Pokorny
 */

#समावेश <drm/drm_prime.h>
#समावेश <linux/virtio_dma_buf.h>

#समावेश "virtgpu_drv.h"

अटल पूर्णांक virtgpu_virtio_get_uuid(काष्ठा dma_buf *buf,
				   uuid_t *uuid)
अणु
	काष्ठा drm_gem_object *obj = buf->priv;
	काष्ठा virtio_gpu_object *bo = gem_to_virtio_gpu_obj(obj);
	काष्ठा virtio_gpu_device *vgdev = obj->dev->dev_निजी;

	रुको_event(vgdev->resp_wq, bo->uuid_state != STATE_INITIALIZING);
	अगर (bo->uuid_state != STATE_OK)
		वापस -ENODEV;

	uuid_copy(uuid, &bo->uuid);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा virtio_dma_buf_ops virtgpu_dmabuf_ops =  अणु
	.ops = अणु
		.cache_sgt_mapping = true,
		.attach = virtio_dma_buf_attach,
		.detach = drm_gem_map_detach,
		.map_dma_buf = drm_gem_map_dma_buf,
		.unmap_dma_buf = drm_gem_unmap_dma_buf,
		.release = drm_gem_dmabuf_release,
		.mmap = drm_gem_dmabuf_mmap,
		.vmap = drm_gem_dmabuf_vmap,
		.vunmap = drm_gem_dmabuf_vunmap,
	पूर्ण,
	.device_attach = drm_gem_map_attach,
	.get_uuid = virtgpu_virtio_get_uuid,
पूर्ण;

पूर्णांक virtio_gpu_resource_assign_uuid(काष्ठा virtio_gpu_device *vgdev,
				    काष्ठा virtio_gpu_object *bo)
अणु
	पूर्णांक ret;
	काष्ठा virtio_gpu_object_array *objs;

	objs = virtio_gpu_array_alloc(1);
	अगर (!objs)
		वापस -ENOMEM;

	virtio_gpu_array_add_obj(objs, &bo->base.base);
	ret = virtio_gpu_cmd_resource_assign_uuid(vgdev, objs);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

काष्ठा dma_buf *virtgpu_gem_prime_export(काष्ठा drm_gem_object *obj,
					 पूर्णांक flags)
अणु
	काष्ठा dma_buf *buf;
	काष्ठा drm_device *dev = obj->dev;
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा virtio_gpu_object *bo = gem_to_virtio_gpu_obj(obj);
	पूर्णांक ret = 0;
	bool blob = bo->host3d_blob || bo->guest_blob;
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);

	अगर (!blob) अणु
		अगर (vgdev->has_resource_assign_uuid) अणु
			ret = virtio_gpu_resource_assign_uuid(vgdev, bo);
			अगर (ret)
				वापस ERR_PTR(ret);

			virtio_gpu_notअगरy(vgdev);
		पूर्ण अन्यथा अणु
			bo->uuid_state = STATE_ERR;
		पूर्ण
	पूर्ण

	exp_info.ops = &virtgpu_dmabuf_ops.ops;
	exp_info.size = obj->size;
	exp_info.flags = flags;
	exp_info.priv = obj;
	exp_info.resv = obj->resv;

	buf = virtio_dma_buf_export(&exp_info);
	अगर (IS_ERR(buf))
		वापस buf;

	drm_dev_get(dev);
	drm_gem_object_get(obj);

	वापस buf;
पूर्ण

काष्ठा drm_gem_object *virtgpu_gem_prime_import(काष्ठा drm_device *dev,
						काष्ठा dma_buf *buf)
अणु
	काष्ठा drm_gem_object *obj;

	अगर (buf->ops == &virtgpu_dmabuf_ops.ops) अणु
		obj = buf->priv;
		अगर (obj->dev == dev) अणु
			/*
			 * Importing dmabuf exported from our own gem increases
			 * refcount on gem itself instead of f_count of dmabuf.
			 */
			drm_gem_object_get(obj);
			वापस obj;
		पूर्ण
	पूर्ण

	वापस drm_gem_prime_import(dev, buf);
पूर्ण

काष्ठा drm_gem_object *virtgpu_gem_prime_import_sg_table(
	काष्ठा drm_device *dev, काष्ठा dma_buf_attachment *attach,
	काष्ठा sg_table *table)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
