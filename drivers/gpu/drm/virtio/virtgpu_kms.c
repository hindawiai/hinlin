<शैली गुरु>
/*
 * Copyright (C) 2015 Red Hat, Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_config.h>
#समावेश <linux/virtio_ring.h>

#समावेश <drm/drm_file.h>

#समावेश "virtgpu_drv.h"

अटल व्योम virtio_gpu_config_changed_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_gpu_device *vgdev =
		container_of(work, काष्ठा virtio_gpu_device,
			     config_changed_work);
	u32 events_पढ़ो, events_clear = 0;

	/* पढ़ो the config space */
	virtio_cपढ़ो_le(vgdev->vdev, काष्ठा virtio_gpu_config,
			events_पढ़ो, &events_पढ़ो);
	अगर (events_पढ़ो & VIRTIO_GPU_EVENT_DISPLAY) अणु
		अगर (vgdev->has_edid)
			virtio_gpu_cmd_get_edids(vgdev);
		virtio_gpu_cmd_get_display_info(vgdev);
		virtio_gpu_notअगरy(vgdev);
		drm_helper_hpd_irq_event(vgdev->ddev);
		events_clear |= VIRTIO_GPU_EVENT_DISPLAY;
	पूर्ण
	virtio_cग_लिखो_le(vgdev->vdev, काष्ठा virtio_gpu_config,
			 events_clear, &events_clear);
पूर्ण

अटल व्योम virtio_gpu_init_vq(काष्ठा virtio_gpu_queue *vgvq,
			       व्योम (*work_func)(काष्ठा work_काष्ठा *work))
अणु
	spin_lock_init(&vgvq->qlock);
	init_रुकोqueue_head(&vgvq->ack_queue);
	INIT_WORK(&vgvq->dequeue_work, work_func);
पूर्ण

अटल व्योम virtio_gpu_get_capsets(काष्ठा virtio_gpu_device *vgdev,
				   पूर्णांक num_capsets)
अणु
	पूर्णांक i, ret;

	vgdev->capsets = kसुस्मृति(num_capsets,
				 माप(काष्ठा virtio_gpu_drv_capset),
				 GFP_KERNEL);
	अगर (!vgdev->capsets) अणु
		DRM_ERROR("failed to allocate cap sets\n");
		वापस;
	पूर्ण
	क्रम (i = 0; i < num_capsets; i++) अणु
		virtio_gpu_cmd_get_capset_info(vgdev, i);
		virtio_gpu_notअगरy(vgdev);
		ret = रुको_event_समयout(vgdev->resp_wq,
					 vgdev->capsets[i].id > 0, 5 * HZ);
		अगर (ret == 0) अणु
			DRM_ERROR("timed out waiting for cap set %d\n", i);
			spin_lock(&vgdev->display_info_lock);
			kमुक्त(vgdev->capsets);
			vgdev->capsets = शून्य;
			spin_unlock(&vgdev->display_info_lock);
			वापस;
		पूर्ण
		DRM_INFO("cap set %d: id %d, max-version %d, max-size %d\n",
			 i, vgdev->capsets[i].id,
			 vgdev->capsets[i].max_version,
			 vgdev->capsets[i].max_size);
	पूर्ण
	vgdev->num_capsets = num_capsets;
पूर्ण

पूर्णांक virtio_gpu_init(काष्ठा drm_device *dev)
अणु
	अटल vq_callback_t *callbacks[] = अणु
		virtio_gpu_ctrl_ack, virtio_gpu_cursor_ack
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर names[] = अणु "control", "cursor" पूर्ण;

	काष्ठा virtio_gpu_device *vgdev;
	/* this will expand later */
	काष्ठा virtqueue *vqs[2];
	u32 num_scanouts, num_capsets;
	पूर्णांक ret = 0;

	अगर (!virtio_has_feature(dev_to_virtio(dev->dev), VIRTIO_F_VERSION_1))
		वापस -ENODEV;

	vgdev = kzalloc(माप(काष्ठा virtio_gpu_device), GFP_KERNEL);
	अगर (!vgdev)
		वापस -ENOMEM;

	vgdev->ddev = dev;
	dev->dev_निजी = vgdev;
	vgdev->vdev = dev_to_virtio(dev->dev);
	vgdev->dev = dev->dev;

	spin_lock_init(&vgdev->display_info_lock);
	spin_lock_init(&vgdev->resource_export_lock);
	spin_lock_init(&vgdev->host_visible_lock);
	ida_init(&vgdev->ctx_id_ida);
	ida_init(&vgdev->resource_ida);
	init_रुकोqueue_head(&vgdev->resp_wq);
	virtio_gpu_init_vq(&vgdev->ctrlq, virtio_gpu_dequeue_ctrl_func);
	virtio_gpu_init_vq(&vgdev->cursorq, virtio_gpu_dequeue_cursor_func);

	vgdev->fence_drv.context = dma_fence_context_alloc(1);
	spin_lock_init(&vgdev->fence_drv.lock);
	INIT_LIST_HEAD(&vgdev->fence_drv.fences);
	INIT_LIST_HEAD(&vgdev->cap_cache);
	INIT_WORK(&vgdev->config_changed_work,
		  virtio_gpu_config_changed_work_func);

	INIT_WORK(&vgdev->obj_मुक्त_work,
		  virtio_gpu_array_put_मुक्त_work);
	INIT_LIST_HEAD(&vgdev->obj_मुक्त_list);
	spin_lock_init(&vgdev->obj_मुक्त_lock);

#अगर_घोषित __LITTLE_ENDIAN
	अगर (virtio_has_feature(vgdev->vdev, VIRTIO_GPU_F_VIRGL))
		vgdev->has_virgl_3d = true;
#पूर्ण_अगर
	अगर (virtio_has_feature(vgdev->vdev, VIRTIO_GPU_F_EDID)) अणु
		vgdev->has_edid = true;
	पूर्ण
	अगर (virtio_has_feature(vgdev->vdev, VIRTIO_RING_F_INसूचीECT_DESC)) अणु
		vgdev->has_indirect = true;
	पूर्ण
	अगर (virtio_has_feature(vgdev->vdev, VIRTIO_GPU_F_RESOURCE_UUID)) अणु
		vgdev->has_resource_assign_uuid = true;
	पूर्ण
	अगर (virtio_has_feature(vgdev->vdev, VIRTIO_GPU_F_RESOURCE_BLOB)) अणु
		vgdev->has_resource_blob = true;
	पूर्ण
	अगर (virtio_get_shm_region(vgdev->vdev, &vgdev->host_visible_region,
				  VIRTIO_GPU_SHM_ID_HOST_VISIBLE)) अणु
		अगर (!devm_request_mem_region(&vgdev->vdev->dev,
					     vgdev->host_visible_region.addr,
					     vgdev->host_visible_region.len,
					     dev_name(&vgdev->vdev->dev))) अणु
			DRM_ERROR("Could not reserve host visible region\n");
			ret = -EBUSY;
			जाओ err_vqs;
		पूर्ण

		DRM_INFO("Host memory window: 0x%lx +0x%lx\n",
			 (अचिन्हित दीर्घ)vgdev->host_visible_region.addr,
			 (अचिन्हित दीर्घ)vgdev->host_visible_region.len);
		vgdev->has_host_visible = true;
		drm_mm_init(&vgdev->host_visible_mm,
			    (अचिन्हित दीर्घ)vgdev->host_visible_region.addr,
			    (अचिन्हित दीर्घ)vgdev->host_visible_region.len);
	पूर्ण

	DRM_INFO("features: %cvirgl %cedid %cresource_blob %chost_visible\n",
		 vgdev->has_virgl_3d    ? '+' : '-',
		 vgdev->has_edid        ? '+' : '-',
		 vgdev->has_resource_blob ? '+' : '-',
		 vgdev->has_host_visible ? '+' : '-');

	ret = virtio_find_vqs(vgdev->vdev, 2, vqs, callbacks, names, शून्य);
	अगर (ret) अणु
		DRM_ERROR("failed to find virt queues\n");
		जाओ err_vqs;
	पूर्ण
	vgdev->ctrlq.vq = vqs[0];
	vgdev->cursorq.vq = vqs[1];
	ret = virtio_gpu_alloc_vbufs(vgdev);
	अगर (ret) अणु
		DRM_ERROR("failed to alloc vbufs\n");
		जाओ err_vbufs;
	पूर्ण

	/* get display info */
	virtio_cपढ़ो_le(vgdev->vdev, काष्ठा virtio_gpu_config,
			num_scanouts, &num_scanouts);
	vgdev->num_scanouts = min_t(uपूर्णांक32_t, num_scanouts,
				    VIRTIO_GPU_MAX_SCANOUTS);
	अगर (!vgdev->num_scanouts) अणु
		DRM_ERROR("num_scanouts is zero\n");
		ret = -EINVAL;
		जाओ err_scanouts;
	पूर्ण
	DRM_INFO("number of scanouts: %d\n", num_scanouts);

	virtio_cपढ़ो_le(vgdev->vdev, काष्ठा virtio_gpu_config,
			num_capsets, &num_capsets);
	DRM_INFO("number of cap sets: %d\n", num_capsets);

	ret = virtio_gpu_modeset_init(vgdev);
	अगर (ret) अणु
		DRM_ERROR("modeset init failed\n");
		जाओ err_scanouts;
	पूर्ण

	virtio_device_पढ़ोy(vgdev->vdev);

	अगर (num_capsets)
		virtio_gpu_get_capsets(vgdev, num_capsets);
	अगर (vgdev->has_edid)
		virtio_gpu_cmd_get_edids(vgdev);
	virtio_gpu_cmd_get_display_info(vgdev);
	virtio_gpu_notअगरy(vgdev);
	रुको_event_समयout(vgdev->resp_wq, !vgdev->display_info_pending,
			   5 * HZ);
	वापस 0;

err_scanouts:
	virtio_gpu_मुक्त_vbufs(vgdev);
err_vbufs:
	vgdev->vdev->config->del_vqs(vgdev->vdev);
err_vqs:
	kमुक्त(vgdev);
	वापस ret;
पूर्ण

अटल व्योम virtio_gpu_cleanup_cap_cache(काष्ठा virtio_gpu_device *vgdev)
अणु
	काष्ठा virtio_gpu_drv_cap_cache *cache_ent, *पंचांगp;

	list_क्रम_each_entry_safe(cache_ent, पंचांगp, &vgdev->cap_cache, head) अणु
		kमुक्त(cache_ent->caps_cache);
		kमुक्त(cache_ent);
	पूर्ण
पूर्ण

व्योम virtio_gpu_deinit(काष्ठा drm_device *dev)
अणु
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;

	flush_work(&vgdev->obj_मुक्त_work);
	flush_work(&vgdev->ctrlq.dequeue_work);
	flush_work(&vgdev->cursorq.dequeue_work);
	flush_work(&vgdev->config_changed_work);
	vgdev->vdev->config->reset(vgdev->vdev);
	vgdev->vdev->config->del_vqs(vgdev->vdev);
पूर्ण

व्योम virtio_gpu_release(काष्ठा drm_device *dev)
अणु
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;

	virtio_gpu_modeset_fini(vgdev);
	virtio_gpu_मुक्त_vbufs(vgdev);
	virtio_gpu_cleanup_cap_cache(vgdev);

	अगर (vgdev->has_host_visible)
		drm_mm_takeकरोwn(&vgdev->host_visible_mm);

	kमुक्त(vgdev->capsets);
	kमुक्त(vgdev);
पूर्ण

पूर्णांक virtio_gpu_driver_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा virtio_gpu_fpriv *vfpriv;
	पूर्णांक handle;

	/* can't create contexts without 3d renderer */
	अगर (!vgdev->has_virgl_3d)
		वापस 0;

	/* allocate a virt GPU context क्रम this खोलोer */
	vfpriv = kzalloc(माप(*vfpriv), GFP_KERNEL);
	अगर (!vfpriv)
		वापस -ENOMEM;

	mutex_init(&vfpriv->context_lock);

	handle = ida_alloc(&vgdev->ctx_id_ida, GFP_KERNEL);
	अगर (handle < 0) अणु
		kमुक्त(vfpriv);
		वापस handle;
	पूर्ण

	vfpriv->ctx_id = handle + 1;
	file->driver_priv = vfpriv;
	वापस 0;
पूर्ण

व्योम virtio_gpu_driver_postबंद(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;
	काष्ठा virtio_gpu_fpriv *vfpriv = file->driver_priv;

	अगर (!vgdev->has_virgl_3d)
		वापस;

	अगर (vfpriv->context_created) अणु
		virtio_gpu_cmd_context_destroy(vgdev, vfpriv->ctx_id);
		virtio_gpu_notअगरy(vgdev);
	पूर्ण

	ida_मुक्त(&vgdev->ctx_id_ida, vfpriv->ctx_id - 1);
	mutex_destroy(&vfpriv->context_lock);
	kमुक्त(vfpriv);
	file->driver_priv = शून्य;
पूर्ण
