<शैली गुरु>
/*
 * Copyright (C) 2015 Red Hat, Inc.
 * All Rights Reserved.
 *
 * Authors:
 *    Dave Airlie <airlied@redhat.com>
 *    Gerd Hoffmann <kraxel@redhat.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_config.h>
#समावेश <linux/virtio_ring.h>

#समावेश "virtgpu_drv.h"
#समावेश "virtgpu_trace.h"

#घोषणा MAX_INLINE_CMD_SIZE   96
#घोषणा MAX_INLINE_RESP_SIZE  24
#घोषणा VBUFFER_SIZE          (माप(काष्ठा virtio_gpu_vbuffer) \
			       + MAX_INLINE_CMD_SIZE		 \
			       + MAX_INLINE_RESP_SIZE)

अटल व्योम convert_to_hw_box(काष्ठा virtio_gpu_box *dst,
			      स्थिर काष्ठा drm_virtgpu_3d_box *src)
अणु
	dst->x = cpu_to_le32(src->x);
	dst->y = cpu_to_le32(src->y);
	dst->z = cpu_to_le32(src->z);
	dst->w = cpu_to_le32(src->w);
	dst->h = cpu_to_le32(src->h);
	dst->d = cpu_to_le32(src->d);
पूर्ण

व्योम virtio_gpu_ctrl_ack(काष्ठा virtqueue *vq)
अणु
	काष्ठा drm_device *dev = vq->vdev->priv;
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;

	schedule_work(&vgdev->ctrlq.dequeue_work);
पूर्ण

व्योम virtio_gpu_cursor_ack(काष्ठा virtqueue *vq)
अणु
	काष्ठा drm_device *dev = vq->vdev->priv;
	काष्ठा virtio_gpu_device *vgdev = dev->dev_निजी;

	schedule_work(&vgdev->cursorq.dequeue_work);
पूर्ण

पूर्णांक virtio_gpu_alloc_vbufs(काष्ठा virtio_gpu_device *vgdev)
अणु
	vgdev->vbufs = kmem_cache_create("virtio-gpu-vbufs",
					 VBUFFER_SIZE,
					 __alignof__(काष्ठा virtio_gpu_vbuffer),
					 0, शून्य);
	अगर (!vgdev->vbufs)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम virtio_gpu_मुक्त_vbufs(काष्ठा virtio_gpu_device *vgdev)
अणु
	kmem_cache_destroy(vgdev->vbufs);
	vgdev->vbufs = शून्य;
पूर्ण

अटल काष्ठा virtio_gpu_vbuffer*
virtio_gpu_get_vbuf(काष्ठा virtio_gpu_device *vgdev,
		    पूर्णांक size, पूर्णांक resp_size, व्योम *resp_buf,
		    virtio_gpu_resp_cb resp_cb)
अणु
	काष्ठा virtio_gpu_vbuffer *vbuf;

	vbuf = kmem_cache_zalloc(vgdev->vbufs, GFP_KERNEL);
	अगर (!vbuf)
		वापस ERR_PTR(-ENOMEM);

	BUG_ON(size > MAX_INLINE_CMD_SIZE ||
	       size < माप(काष्ठा virtio_gpu_ctrl_hdr));
	vbuf->buf = (व्योम *)vbuf + माप(*vbuf);
	vbuf->size = size;

	vbuf->resp_cb = resp_cb;
	vbuf->resp_size = resp_size;
	अगर (resp_size <= MAX_INLINE_RESP_SIZE)
		vbuf->resp_buf = (व्योम *)vbuf->buf + size;
	अन्यथा
		vbuf->resp_buf = resp_buf;
	BUG_ON(!vbuf->resp_buf);
	वापस vbuf;
पूर्ण

अटल काष्ठा virtio_gpu_ctrl_hdr *
virtio_gpu_vbuf_ctrl_hdr(काष्ठा virtio_gpu_vbuffer *vbuf)
अणु
	/* this assumes a vbuf contains a command that starts with a
	 * virtio_gpu_ctrl_hdr, which is true क्रम both ctrl and cursor
	 * virtqueues.
	 */
	वापस (काष्ठा virtio_gpu_ctrl_hdr *)vbuf->buf;
पूर्ण

अटल काष्ठा virtio_gpu_update_cursor*
virtio_gpu_alloc_cursor(काष्ठा virtio_gpu_device *vgdev,
			काष्ठा virtio_gpu_vbuffer **vbuffer_p)
अणु
	काष्ठा virtio_gpu_vbuffer *vbuf;

	vbuf = virtio_gpu_get_vbuf
		(vgdev, माप(काष्ठा virtio_gpu_update_cursor),
		 0, शून्य, शून्य);
	अगर (IS_ERR(vbuf)) अणु
		*vbuffer_p = शून्य;
		वापस ERR_CAST(vbuf);
	पूर्ण
	*vbuffer_p = vbuf;
	वापस (काष्ठा virtio_gpu_update_cursor *)vbuf->buf;
पूर्ण

अटल व्योम *virtio_gpu_alloc_cmd_resp(काष्ठा virtio_gpu_device *vgdev,
				       virtio_gpu_resp_cb cb,
				       काष्ठा virtio_gpu_vbuffer **vbuffer_p,
				       पूर्णांक cmd_size, पूर्णांक resp_size,
				       व्योम *resp_buf)
अणु
	काष्ठा virtio_gpu_vbuffer *vbuf;

	vbuf = virtio_gpu_get_vbuf(vgdev, cmd_size,
				   resp_size, resp_buf, cb);
	अगर (IS_ERR(vbuf)) अणु
		*vbuffer_p = शून्य;
		वापस ERR_CAST(vbuf);
	पूर्ण
	*vbuffer_p = vbuf;
	वापस (काष्ठा virtio_gpu_command *)vbuf->buf;
पूर्ण

अटल व्योम *virtio_gpu_alloc_cmd(काष्ठा virtio_gpu_device *vgdev,
				  काष्ठा virtio_gpu_vbuffer **vbuffer_p,
				  पूर्णांक size)
अणु
	वापस virtio_gpu_alloc_cmd_resp(vgdev, शून्य, vbuffer_p, size,
					 माप(काष्ठा virtio_gpu_ctrl_hdr),
					 शून्य);
पूर्ण

अटल व्योम *virtio_gpu_alloc_cmd_cb(काष्ठा virtio_gpu_device *vgdev,
				     काष्ठा virtio_gpu_vbuffer **vbuffer_p,
				     पूर्णांक size,
				     virtio_gpu_resp_cb cb)
अणु
	वापस virtio_gpu_alloc_cmd_resp(vgdev, cb, vbuffer_p, size,
					 माप(काष्ठा virtio_gpu_ctrl_hdr),
					 शून्य);
पूर्ण

अटल व्योम मुक्त_vbuf(काष्ठा virtio_gpu_device *vgdev,
		      काष्ठा virtio_gpu_vbuffer *vbuf)
अणु
	अगर (vbuf->resp_size > MAX_INLINE_RESP_SIZE)
		kमुक्त(vbuf->resp_buf);
	kvमुक्त(vbuf->data_buf);
	kmem_cache_मुक्त(vgdev->vbufs, vbuf);
पूर्ण

अटल व्योम reclaim_vbufs(काष्ठा virtqueue *vq, काष्ठा list_head *reclaim_list)
अणु
	काष्ठा virtio_gpu_vbuffer *vbuf;
	अचिन्हित पूर्णांक len;
	पूर्णांक मुक्तd = 0;

	जबतक ((vbuf = virtqueue_get_buf(vq, &len))) अणु
		list_add_tail(&vbuf->list, reclaim_list);
		मुक्तd++;
	पूर्ण
	अगर (मुक्तd == 0)
		DRM_DEBUG("Huh? zero vbufs reclaimed");
पूर्ण

व्योम virtio_gpu_dequeue_ctrl_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_gpu_device *vgdev =
		container_of(work, काष्ठा virtio_gpu_device,
			     ctrlq.dequeue_work);
	काष्ठा list_head reclaim_list;
	काष्ठा virtio_gpu_vbuffer *entry, *पंचांगp;
	काष्ठा virtio_gpu_ctrl_hdr *resp;
	u64 fence_id = 0;

	INIT_LIST_HEAD(&reclaim_list);
	spin_lock(&vgdev->ctrlq.qlock);
	करो अणु
		virtqueue_disable_cb(vgdev->ctrlq.vq);
		reclaim_vbufs(vgdev->ctrlq.vq, &reclaim_list);

	पूर्ण जबतक (!virtqueue_enable_cb(vgdev->ctrlq.vq));
	spin_unlock(&vgdev->ctrlq.qlock);

	list_क्रम_each_entry(entry, &reclaim_list, list) अणु
		resp = (काष्ठा virtio_gpu_ctrl_hdr *)entry->resp_buf;

		trace_virtio_gpu_cmd_response(vgdev->ctrlq.vq, resp);

		अगर (resp->type != cpu_to_le32(VIRTIO_GPU_RESP_OK_NODATA)) अणु
			अगर (le32_to_cpu(resp->type) >= VIRTIO_GPU_RESP_ERR_UNSPEC) अणु
				काष्ठा virtio_gpu_ctrl_hdr *cmd;
				cmd = virtio_gpu_vbuf_ctrl_hdr(entry);
				DRM_ERROR_RATELIMITED("response 0x%x (command 0x%x)\n",
						      le32_to_cpu(resp->type),
						      le32_to_cpu(cmd->type));
			पूर्ण अन्यथा
				DRM_DEBUG("response 0x%x\n", le32_to_cpu(resp->type));
		पूर्ण
		अगर (resp->flags & cpu_to_le32(VIRTIO_GPU_FLAG_FENCE)) अणु
			u64 f = le64_to_cpu(resp->fence_id);

			अगर (fence_id > f) अणु
				DRM_ERROR("%s: Oops: fence %llx -> %llx\n",
					  __func__, fence_id, f);
			पूर्ण अन्यथा अणु
				fence_id = f;
			पूर्ण
		पूर्ण
		अगर (entry->resp_cb)
			entry->resp_cb(vgdev, entry);
	पूर्ण
	wake_up(&vgdev->ctrlq.ack_queue);

	अगर (fence_id)
		virtio_gpu_fence_event_process(vgdev, fence_id);

	list_क्रम_each_entry_safe(entry, पंचांगp, &reclaim_list, list) अणु
		अगर (entry->objs)
			virtio_gpu_array_put_मुक्त_delayed(vgdev, entry->objs);
		list_del(&entry->list);
		मुक्त_vbuf(vgdev, entry);
	पूर्ण
पूर्ण

व्योम virtio_gpu_dequeue_cursor_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_gpu_device *vgdev =
		container_of(work, काष्ठा virtio_gpu_device,
			     cursorq.dequeue_work);
	काष्ठा list_head reclaim_list;
	काष्ठा virtio_gpu_vbuffer *entry, *पंचांगp;

	INIT_LIST_HEAD(&reclaim_list);
	spin_lock(&vgdev->cursorq.qlock);
	करो अणु
		virtqueue_disable_cb(vgdev->cursorq.vq);
		reclaim_vbufs(vgdev->cursorq.vq, &reclaim_list);
	पूर्ण जबतक (!virtqueue_enable_cb(vgdev->cursorq.vq));
	spin_unlock(&vgdev->cursorq.qlock);

	list_क्रम_each_entry_safe(entry, पंचांगp, &reclaim_list, list) अणु
		list_del(&entry->list);
		मुक्त_vbuf(vgdev, entry);
	पूर्ण
	wake_up(&vgdev->cursorq.ack_queue);
पूर्ण

/* Create sg_table from a vदो_स्मृति'd buffer. */
अटल काष्ठा sg_table *vदो_स्मृति_to_sgt(अक्षर *data, uपूर्णांक32_t size, पूर्णांक *sg_ents)
अणु
	पूर्णांक ret, s, i;
	काष्ठा sg_table *sgt;
	काष्ठा scatterlist *sg;
	काष्ठा page *pg;

	अगर (WARN_ON(!PAGE_ALIGNED(data)))
		वापस शून्य;

	sgt = kदो_स्मृति(माप(*sgt), GFP_KERNEL);
	अगर (!sgt)
		वापस शून्य;

	*sg_ents = DIV_ROUND_UP(size, PAGE_SIZE);
	ret = sg_alloc_table(sgt, *sg_ents, GFP_KERNEL);
	अगर (ret) अणु
		kमुक्त(sgt);
		वापस शून्य;
	पूर्ण

	क्रम_each_sgtable_sg(sgt, sg, i) अणु
		pg = vदो_स्मृति_to_page(data);
		अगर (!pg) अणु
			sg_मुक्त_table(sgt);
			kमुक्त(sgt);
			वापस शून्य;
		पूर्ण

		s = min_t(पूर्णांक, PAGE_SIZE, size);
		sg_set_page(sg, pg, s, 0);

		size -= s;
		data += s;
	पूर्ण

	वापस sgt;
पूर्ण

अटल पूर्णांक virtio_gpu_queue_ctrl_sgs(काष्ठा virtio_gpu_device *vgdev,
				     काष्ठा virtio_gpu_vbuffer *vbuf,
				     काष्ठा virtio_gpu_fence *fence,
				     पूर्णांक elemcnt,
				     काष्ठा scatterlist **sgs,
				     पूर्णांक outcnt,
				     पूर्णांक incnt)
अणु
	काष्ठा virtqueue *vq = vgdev->ctrlq.vq;
	पूर्णांक ret, idx;

	अगर (!drm_dev_enter(vgdev->ddev, &idx)) अणु
		अगर (fence && vbuf->objs)
			virtio_gpu_array_unlock_resv(vbuf->objs);
		मुक्त_vbuf(vgdev, vbuf);
		वापस -1;
	पूर्ण

	अगर (vgdev->has_indirect)
		elemcnt = 1;

again:
	spin_lock(&vgdev->ctrlq.qlock);

	अगर (vq->num_मुक्त < elemcnt) अणु
		spin_unlock(&vgdev->ctrlq.qlock);
		virtio_gpu_notअगरy(vgdev);
		रुको_event(vgdev->ctrlq.ack_queue, vq->num_मुक्त >= elemcnt);
		जाओ again;
	पूर्ण

	/* now that the position of the vbuf in the virtqueue is known, we can
	 * finally set the fence id
	 */
	अगर (fence) अणु
		virtio_gpu_fence_emit(vgdev, virtio_gpu_vbuf_ctrl_hdr(vbuf),
				      fence);
		अगर (vbuf->objs) अणु
			virtio_gpu_array_add_fence(vbuf->objs, &fence->f);
			virtio_gpu_array_unlock_resv(vbuf->objs);
		पूर्ण
	पूर्ण

	ret = virtqueue_add_sgs(vq, sgs, outcnt, incnt, vbuf, GFP_ATOMIC);
	WARN_ON(ret);

	trace_virtio_gpu_cmd_queue(vq, virtio_gpu_vbuf_ctrl_hdr(vbuf));

	atomic_inc(&vgdev->pending_commands);

	spin_unlock(&vgdev->ctrlq.qlock);

	drm_dev_निकास(idx);
	वापस 0;
पूर्ण

अटल पूर्णांक virtio_gpu_queue_fenced_ctrl_buffer(काष्ठा virtio_gpu_device *vgdev,
					       काष्ठा virtio_gpu_vbuffer *vbuf,
					       काष्ठा virtio_gpu_fence *fence)
अणु
	काष्ठा scatterlist *sgs[3], vcmd, vout, vresp;
	काष्ठा sg_table *sgt = शून्य;
	पूर्णांक elemcnt = 0, outcnt = 0, incnt = 0, ret;

	/* set up vcmd */
	sg_init_one(&vcmd, vbuf->buf, vbuf->size);
	elemcnt++;
	sgs[outcnt] = &vcmd;
	outcnt++;

	/* set up vout */
	अगर (vbuf->data_size) अणु
		अगर (is_vदो_स्मृति_addr(vbuf->data_buf)) अणु
			पूर्णांक sg_ents;
			sgt = vदो_स्मृति_to_sgt(vbuf->data_buf, vbuf->data_size,
					     &sg_ents);
			अगर (!sgt) अणु
				अगर (fence && vbuf->objs)
					virtio_gpu_array_unlock_resv(vbuf->objs);
				वापस -1;
			पूर्ण

			elemcnt += sg_ents;
			sgs[outcnt] = sgt->sgl;
		पूर्ण अन्यथा अणु
			sg_init_one(&vout, vbuf->data_buf, vbuf->data_size);
			elemcnt++;
			sgs[outcnt] = &vout;
		पूर्ण
		outcnt++;
	पूर्ण

	/* set up vresp */
	अगर (vbuf->resp_size) अणु
		sg_init_one(&vresp, vbuf->resp_buf, vbuf->resp_size);
		elemcnt++;
		sgs[outcnt + incnt] = &vresp;
		incnt++;
	पूर्ण

	ret = virtio_gpu_queue_ctrl_sgs(vgdev, vbuf, fence, elemcnt, sgs, outcnt,
					incnt);

	अगर (sgt) अणु
		sg_मुक्त_table(sgt);
		kमुक्त(sgt);
	पूर्ण
	वापस ret;
पूर्ण

व्योम virtio_gpu_notअगरy(काष्ठा virtio_gpu_device *vgdev)
अणु
	bool notअगरy;

	अगर (!atomic_पढ़ो(&vgdev->pending_commands))
		वापस;

	spin_lock(&vgdev->ctrlq.qlock);
	atomic_set(&vgdev->pending_commands, 0);
	notअगरy = virtqueue_kick_prepare(vgdev->ctrlq.vq);
	spin_unlock(&vgdev->ctrlq.qlock);

	अगर (notअगरy)
		virtqueue_notअगरy(vgdev->ctrlq.vq);
पूर्ण

अटल पूर्णांक virtio_gpu_queue_ctrl_buffer(काष्ठा virtio_gpu_device *vgdev,
					काष्ठा virtio_gpu_vbuffer *vbuf)
अणु
	वापस virtio_gpu_queue_fenced_ctrl_buffer(vgdev, vbuf, शून्य);
पूर्ण

अटल व्योम virtio_gpu_queue_cursor(काष्ठा virtio_gpu_device *vgdev,
				    काष्ठा virtio_gpu_vbuffer *vbuf)
अणु
	काष्ठा virtqueue *vq = vgdev->cursorq.vq;
	काष्ठा scatterlist *sgs[1], ccmd;
	पूर्णांक idx, ret, outcnt;
	bool notअगरy;

	अगर (!drm_dev_enter(vgdev->ddev, &idx)) अणु
		मुक्त_vbuf(vgdev, vbuf);
		वापस;
	पूर्ण

	sg_init_one(&ccmd, vbuf->buf, vbuf->size);
	sgs[0] = &ccmd;
	outcnt = 1;

	spin_lock(&vgdev->cursorq.qlock);
retry:
	ret = virtqueue_add_sgs(vq, sgs, outcnt, 0, vbuf, GFP_ATOMIC);
	अगर (ret == -ENOSPC) अणु
		spin_unlock(&vgdev->cursorq.qlock);
		रुको_event(vgdev->cursorq.ack_queue, vq->num_मुक्त >= outcnt);
		spin_lock(&vgdev->cursorq.qlock);
		जाओ retry;
	पूर्ण अन्यथा अणु
		trace_virtio_gpu_cmd_queue(vq,
			virtio_gpu_vbuf_ctrl_hdr(vbuf));

		notअगरy = virtqueue_kick_prepare(vq);
	पूर्ण

	spin_unlock(&vgdev->cursorq.qlock);

	अगर (notअगरy)
		virtqueue_notअगरy(vq);

	drm_dev_निकास(idx);
पूर्ण

/* just create gem objects क्रम userspace and दीर्घ lived objects,
 * just use dma_alloced pages क्रम the queue objects?
 */

/* create a basic resource */
व्योम virtio_gpu_cmd_create_resource(काष्ठा virtio_gpu_device *vgdev,
				    काष्ठा virtio_gpu_object *bo,
				    काष्ठा virtio_gpu_object_params *params,
				    काष्ठा virtio_gpu_object_array *objs,
				    काष्ठा virtio_gpu_fence *fence)
अणु
	काष्ठा virtio_gpu_resource_create_2d *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;

	cmd_p = virtio_gpu_alloc_cmd(vgdev, &vbuf, माप(*cmd_p));
	स_रखो(cmd_p, 0, माप(*cmd_p));
	vbuf->objs = objs;

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_RESOURCE_CREATE_2D);
	cmd_p->resource_id = cpu_to_le32(bo->hw_res_handle);
	cmd_p->क्रमmat = cpu_to_le32(params->क्रमmat);
	cmd_p->width = cpu_to_le32(params->width);
	cmd_p->height = cpu_to_le32(params->height);

	virtio_gpu_queue_fenced_ctrl_buffer(vgdev, vbuf, fence);
	bo->created = true;
पूर्ण

अटल व्योम virtio_gpu_cmd_unref_cb(काष्ठा virtio_gpu_device *vgdev,
				    काष्ठा virtio_gpu_vbuffer *vbuf)
अणु
	काष्ठा virtio_gpu_object *bo;

	bo = vbuf->resp_cb_data;
	vbuf->resp_cb_data = शून्य;

	virtio_gpu_cleanup_object(bo);
पूर्ण

व्योम virtio_gpu_cmd_unref_resource(काष्ठा virtio_gpu_device *vgdev,
				   काष्ठा virtio_gpu_object *bo)
अणु
	काष्ठा virtio_gpu_resource_unref *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;
	पूर्णांक ret;

	cmd_p = virtio_gpu_alloc_cmd_cb(vgdev, &vbuf, माप(*cmd_p),
					virtio_gpu_cmd_unref_cb);
	स_रखो(cmd_p, 0, माप(*cmd_p));

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_RESOURCE_UNREF);
	cmd_p->resource_id = cpu_to_le32(bo->hw_res_handle);

	vbuf->resp_cb_data = bo;
	ret = virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);
	अगर (ret < 0)
		virtio_gpu_cleanup_object(bo);
पूर्ण

व्योम virtio_gpu_cmd_set_scanout(काष्ठा virtio_gpu_device *vgdev,
				uपूर्णांक32_t scanout_id, uपूर्णांक32_t resource_id,
				uपूर्णांक32_t width, uपूर्णांक32_t height,
				uपूर्णांक32_t x, uपूर्णांक32_t y)
अणु
	काष्ठा virtio_gpu_set_scanout *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;

	cmd_p = virtio_gpu_alloc_cmd(vgdev, &vbuf, माप(*cmd_p));
	स_रखो(cmd_p, 0, माप(*cmd_p));

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_SET_SCANOUT);
	cmd_p->resource_id = cpu_to_le32(resource_id);
	cmd_p->scanout_id = cpu_to_le32(scanout_id);
	cmd_p->r.width = cpu_to_le32(width);
	cmd_p->r.height = cpu_to_le32(height);
	cmd_p->r.x = cpu_to_le32(x);
	cmd_p->r.y = cpu_to_le32(y);

	virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);
पूर्ण

व्योम virtio_gpu_cmd_resource_flush(काष्ठा virtio_gpu_device *vgdev,
				   uपूर्णांक32_t resource_id,
				   uपूर्णांक32_t x, uपूर्णांक32_t y,
				   uपूर्णांक32_t width, uपूर्णांक32_t height)
अणु
	काष्ठा virtio_gpu_resource_flush *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;

	cmd_p = virtio_gpu_alloc_cmd(vgdev, &vbuf, माप(*cmd_p));
	स_रखो(cmd_p, 0, माप(*cmd_p));

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_RESOURCE_FLUSH);
	cmd_p->resource_id = cpu_to_le32(resource_id);
	cmd_p->r.width = cpu_to_le32(width);
	cmd_p->r.height = cpu_to_le32(height);
	cmd_p->r.x = cpu_to_le32(x);
	cmd_p->r.y = cpu_to_le32(y);

	virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);
पूर्ण

व्योम virtio_gpu_cmd_transfer_to_host_2d(काष्ठा virtio_gpu_device *vgdev,
					uपूर्णांक64_t offset,
					uपूर्णांक32_t width, uपूर्णांक32_t height,
					uपूर्णांक32_t x, uपूर्णांक32_t y,
					काष्ठा virtio_gpu_object_array *objs,
					काष्ठा virtio_gpu_fence *fence)
अणु
	काष्ठा virtio_gpu_object *bo = gem_to_virtio_gpu_obj(objs->objs[0]);
	काष्ठा virtio_gpu_transfer_to_host_2d *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;
	bool use_dma_api = !virtio_has_dma_quirk(vgdev->vdev);
	काष्ठा virtio_gpu_object_shmem *shmem = to_virtio_gpu_shmem(bo);

	अगर (use_dma_api)
		dma_sync_sgtable_क्रम_device(vgdev->vdev->dev.parent,
					    shmem->pages, DMA_TO_DEVICE);

	cmd_p = virtio_gpu_alloc_cmd(vgdev, &vbuf, माप(*cmd_p));
	स_रखो(cmd_p, 0, माप(*cmd_p));
	vbuf->objs = objs;

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D);
	cmd_p->resource_id = cpu_to_le32(bo->hw_res_handle);
	cmd_p->offset = cpu_to_le64(offset);
	cmd_p->r.width = cpu_to_le32(width);
	cmd_p->r.height = cpu_to_le32(height);
	cmd_p->r.x = cpu_to_le32(x);
	cmd_p->r.y = cpu_to_le32(y);

	virtio_gpu_queue_fenced_ctrl_buffer(vgdev, vbuf, fence);
पूर्ण

अटल व्योम
virtio_gpu_cmd_resource_attach_backing(काष्ठा virtio_gpu_device *vgdev,
				       uपूर्णांक32_t resource_id,
				       काष्ठा virtio_gpu_mem_entry *ents,
				       uपूर्णांक32_t nents,
				       काष्ठा virtio_gpu_fence *fence)
अणु
	काष्ठा virtio_gpu_resource_attach_backing *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;

	cmd_p = virtio_gpu_alloc_cmd(vgdev, &vbuf, माप(*cmd_p));
	स_रखो(cmd_p, 0, माप(*cmd_p));

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING);
	cmd_p->resource_id = cpu_to_le32(resource_id);
	cmd_p->nr_entries = cpu_to_le32(nents);

	vbuf->data_buf = ents;
	vbuf->data_size = माप(*ents) * nents;

	virtio_gpu_queue_fenced_ctrl_buffer(vgdev, vbuf, fence);
पूर्ण

अटल व्योम virtio_gpu_cmd_get_display_info_cb(काष्ठा virtio_gpu_device *vgdev,
					       काष्ठा virtio_gpu_vbuffer *vbuf)
अणु
	काष्ठा virtio_gpu_resp_display_info *resp =
		(काष्ठा virtio_gpu_resp_display_info *)vbuf->resp_buf;
	पूर्णांक i;

	spin_lock(&vgdev->display_info_lock);
	क्रम (i = 0; i < vgdev->num_scanouts; i++) अणु
		vgdev->outमाला_दो[i].info = resp->pmodes[i];
		अगर (resp->pmodes[i].enabled) अणु
			DRM_DEBUG("output %d: %dx%d+%d+%d", i,
				  le32_to_cpu(resp->pmodes[i].r.width),
				  le32_to_cpu(resp->pmodes[i].r.height),
				  le32_to_cpu(resp->pmodes[i].r.x),
				  le32_to_cpu(resp->pmodes[i].r.y));
		पूर्ण अन्यथा अणु
			DRM_DEBUG("output %d: disabled", i);
		पूर्ण
	पूर्ण

	vgdev->display_info_pending = false;
	spin_unlock(&vgdev->display_info_lock);
	wake_up(&vgdev->resp_wq);

	अगर (!drm_helper_hpd_irq_event(vgdev->ddev))
		drm_kms_helper_hotplug_event(vgdev->ddev);
पूर्ण

अटल व्योम virtio_gpu_cmd_get_capset_info_cb(काष्ठा virtio_gpu_device *vgdev,
					      काष्ठा virtio_gpu_vbuffer *vbuf)
अणु
	काष्ठा virtio_gpu_get_capset_info *cmd =
		(काष्ठा virtio_gpu_get_capset_info *)vbuf->buf;
	काष्ठा virtio_gpu_resp_capset_info *resp =
		(काष्ठा virtio_gpu_resp_capset_info *)vbuf->resp_buf;
	पूर्णांक i = le32_to_cpu(cmd->capset_index);

	spin_lock(&vgdev->display_info_lock);
	अगर (vgdev->capsets) अणु
		vgdev->capsets[i].id = le32_to_cpu(resp->capset_id);
		vgdev->capsets[i].max_version = le32_to_cpu(resp->capset_max_version);
		vgdev->capsets[i].max_size = le32_to_cpu(resp->capset_max_size);
	पूर्ण अन्यथा अणु
		DRM_ERROR("invalid capset memory.");
	पूर्ण
	spin_unlock(&vgdev->display_info_lock);
	wake_up(&vgdev->resp_wq);
पूर्ण

अटल व्योम virtio_gpu_cmd_capset_cb(काष्ठा virtio_gpu_device *vgdev,
				     काष्ठा virtio_gpu_vbuffer *vbuf)
अणु
	काष्ठा virtio_gpu_get_capset *cmd =
		(काष्ठा virtio_gpu_get_capset *)vbuf->buf;
	काष्ठा virtio_gpu_resp_capset *resp =
		(काष्ठा virtio_gpu_resp_capset *)vbuf->resp_buf;
	काष्ठा virtio_gpu_drv_cap_cache *cache_ent;

	spin_lock(&vgdev->display_info_lock);
	list_क्रम_each_entry(cache_ent, &vgdev->cap_cache, head) अणु
		अगर (cache_ent->version == le32_to_cpu(cmd->capset_version) &&
		    cache_ent->id == le32_to_cpu(cmd->capset_id)) अणु
			स_नकल(cache_ent->caps_cache, resp->capset_data,
			       cache_ent->size);
			/* Copy must occur beक्रमe is_valid is संकेतled. */
			smp_wmb();
			atomic_set(&cache_ent->is_valid, 1);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&vgdev->display_info_lock);
	wake_up_all(&vgdev->resp_wq);
पूर्ण

अटल पूर्णांक virtio_get_edid_block(व्योम *data, u8 *buf,
				 अचिन्हित पूर्णांक block, माप_प्रकार len)
अणु
	काष्ठा virtio_gpu_resp_edid *resp = data;
	माप_प्रकार start = block * EDID_LENGTH;

	अगर (start + len > le32_to_cpu(resp->size))
		वापस -1;
	स_नकल(buf, resp->edid + start, len);
	वापस 0;
पूर्ण

अटल व्योम virtio_gpu_cmd_get_edid_cb(काष्ठा virtio_gpu_device *vgdev,
				       काष्ठा virtio_gpu_vbuffer *vbuf)
अणु
	काष्ठा virtio_gpu_cmd_get_edid *cmd =
		(काष्ठा virtio_gpu_cmd_get_edid *)vbuf->buf;
	काष्ठा virtio_gpu_resp_edid *resp =
		(काष्ठा virtio_gpu_resp_edid *)vbuf->resp_buf;
	uपूर्णांक32_t scanout = le32_to_cpu(cmd->scanout);
	काष्ठा virtio_gpu_output *output;
	काष्ठा edid *new_edid, *old_edid;

	अगर (scanout >= vgdev->num_scanouts)
		वापस;
	output = vgdev->outमाला_दो + scanout;

	new_edid = drm_करो_get_edid(&output->conn, virtio_get_edid_block, resp);
	drm_connector_update_edid_property(&output->conn, new_edid);

	spin_lock(&vgdev->display_info_lock);
	old_edid = output->edid;
	output->edid = new_edid;
	spin_unlock(&vgdev->display_info_lock);

	kमुक्त(old_edid);
	wake_up(&vgdev->resp_wq);
पूर्ण

पूर्णांक virtio_gpu_cmd_get_display_info(काष्ठा virtio_gpu_device *vgdev)
अणु
	काष्ठा virtio_gpu_ctrl_hdr *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;
	व्योम *resp_buf;

	resp_buf = kzalloc(माप(काष्ठा virtio_gpu_resp_display_info),
			   GFP_KERNEL);
	अगर (!resp_buf)
		वापस -ENOMEM;

	cmd_p = virtio_gpu_alloc_cmd_resp
		(vgdev, &virtio_gpu_cmd_get_display_info_cb, &vbuf,
		 माप(*cmd_p), माप(काष्ठा virtio_gpu_resp_display_info),
		 resp_buf);
	स_रखो(cmd_p, 0, माप(*cmd_p));

	vgdev->display_info_pending = true;
	cmd_p->type = cpu_to_le32(VIRTIO_GPU_CMD_GET_DISPLAY_INFO);
	virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);
	वापस 0;
पूर्ण

पूर्णांक virtio_gpu_cmd_get_capset_info(काष्ठा virtio_gpu_device *vgdev, पूर्णांक idx)
अणु
	काष्ठा virtio_gpu_get_capset_info *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;
	व्योम *resp_buf;

	resp_buf = kzalloc(माप(काष्ठा virtio_gpu_resp_capset_info),
			   GFP_KERNEL);
	अगर (!resp_buf)
		वापस -ENOMEM;

	cmd_p = virtio_gpu_alloc_cmd_resp
		(vgdev, &virtio_gpu_cmd_get_capset_info_cb, &vbuf,
		 माप(*cmd_p), माप(काष्ठा virtio_gpu_resp_capset_info),
		 resp_buf);
	स_रखो(cmd_p, 0, माप(*cmd_p));

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_GET_CAPSET_INFO);
	cmd_p->capset_index = cpu_to_le32(idx);
	virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);
	वापस 0;
पूर्ण

पूर्णांक virtio_gpu_cmd_get_capset(काष्ठा virtio_gpu_device *vgdev,
			      पूर्णांक idx, पूर्णांक version,
			      काष्ठा virtio_gpu_drv_cap_cache **cache_p)
अणु
	काष्ठा virtio_gpu_get_capset *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;
	पूर्णांक max_size;
	काष्ठा virtio_gpu_drv_cap_cache *cache_ent;
	काष्ठा virtio_gpu_drv_cap_cache *search_ent;
	व्योम *resp_buf;

	*cache_p = शून्य;

	अगर (idx >= vgdev->num_capsets)
		वापस -EINVAL;

	अगर (version > vgdev->capsets[idx].max_version)
		वापस -EINVAL;

	cache_ent = kzalloc(माप(*cache_ent), GFP_KERNEL);
	अगर (!cache_ent)
		वापस -ENOMEM;

	max_size = vgdev->capsets[idx].max_size;
	cache_ent->caps_cache = kदो_स्मृति(max_size, GFP_KERNEL);
	अगर (!cache_ent->caps_cache) अणु
		kमुक्त(cache_ent);
		वापस -ENOMEM;
	पूर्ण

	resp_buf = kzalloc(माप(काष्ठा virtio_gpu_resp_capset) + max_size,
			   GFP_KERNEL);
	अगर (!resp_buf) अणु
		kमुक्त(cache_ent->caps_cache);
		kमुक्त(cache_ent);
		वापस -ENOMEM;
	पूर्ण

	cache_ent->version = version;
	cache_ent->id = vgdev->capsets[idx].id;
	atomic_set(&cache_ent->is_valid, 0);
	cache_ent->size = max_size;
	spin_lock(&vgdev->display_info_lock);
	/* Search जबतक under lock in हाल it was added by another task. */
	list_क्रम_each_entry(search_ent, &vgdev->cap_cache, head) अणु
		अगर (search_ent->id == vgdev->capsets[idx].id &&
		    search_ent->version == version) अणु
			*cache_p = search_ent;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!*cache_p)
		list_add_tail(&cache_ent->head, &vgdev->cap_cache);
	spin_unlock(&vgdev->display_info_lock);

	अगर (*cache_p) अणु
		/* Entry was found, so मुक्त everything that was just created. */
		kमुक्त(resp_buf);
		kमुक्त(cache_ent->caps_cache);
		kमुक्त(cache_ent);
		वापस 0;
	पूर्ण

	cmd_p = virtio_gpu_alloc_cmd_resp
		(vgdev, &virtio_gpu_cmd_capset_cb, &vbuf, माप(*cmd_p),
		 माप(काष्ठा virtio_gpu_resp_capset) + max_size,
		 resp_buf);
	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_GET_CAPSET);
	cmd_p->capset_id = cpu_to_le32(vgdev->capsets[idx].id);
	cmd_p->capset_version = cpu_to_le32(version);
	*cache_p = cache_ent;
	virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);

	वापस 0;
पूर्ण

पूर्णांक virtio_gpu_cmd_get_edids(काष्ठा virtio_gpu_device *vgdev)
अणु
	काष्ठा virtio_gpu_cmd_get_edid *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;
	व्योम *resp_buf;
	पूर्णांक scanout;

	अगर (WARN_ON(!vgdev->has_edid))
		वापस -EINVAL;

	क्रम (scanout = 0; scanout < vgdev->num_scanouts; scanout++) अणु
		resp_buf = kzalloc(माप(काष्ठा virtio_gpu_resp_edid),
				   GFP_KERNEL);
		अगर (!resp_buf)
			वापस -ENOMEM;

		cmd_p = virtio_gpu_alloc_cmd_resp
			(vgdev, &virtio_gpu_cmd_get_edid_cb, &vbuf,
			 माप(*cmd_p), माप(काष्ठा virtio_gpu_resp_edid),
			 resp_buf);
		cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_GET_EDID);
		cmd_p->scanout = cpu_to_le32(scanout);
		virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);
	पूर्ण

	वापस 0;
पूर्ण

व्योम virtio_gpu_cmd_context_create(काष्ठा virtio_gpu_device *vgdev, uपूर्णांक32_t id,
				   uपूर्णांक32_t nlen, स्थिर अक्षर *name)
अणु
	काष्ठा virtio_gpu_ctx_create *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;

	cmd_p = virtio_gpu_alloc_cmd(vgdev, &vbuf, माप(*cmd_p));
	स_रखो(cmd_p, 0, माप(*cmd_p));

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_CTX_CREATE);
	cmd_p->hdr.ctx_id = cpu_to_le32(id);
	cmd_p->nlen = cpu_to_le32(nlen);
	म_नकलन(cmd_p->debug_name, name, माप(cmd_p->debug_name) - 1);
	cmd_p->debug_name[माप(cmd_p->debug_name) - 1] = 0;
	virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);
पूर्ण

व्योम virtio_gpu_cmd_context_destroy(काष्ठा virtio_gpu_device *vgdev,
				    uपूर्णांक32_t id)
अणु
	काष्ठा virtio_gpu_ctx_destroy *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;

	cmd_p = virtio_gpu_alloc_cmd(vgdev, &vbuf, माप(*cmd_p));
	स_रखो(cmd_p, 0, माप(*cmd_p));

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_CTX_DESTROY);
	cmd_p->hdr.ctx_id = cpu_to_le32(id);
	virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);
पूर्ण

व्योम virtio_gpu_cmd_context_attach_resource(काष्ठा virtio_gpu_device *vgdev,
					    uपूर्णांक32_t ctx_id,
					    काष्ठा virtio_gpu_object_array *objs)
अणु
	काष्ठा virtio_gpu_object *bo = gem_to_virtio_gpu_obj(objs->objs[0]);
	काष्ठा virtio_gpu_ctx_resource *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;

	cmd_p = virtio_gpu_alloc_cmd(vgdev, &vbuf, माप(*cmd_p));
	स_रखो(cmd_p, 0, माप(*cmd_p));
	vbuf->objs = objs;

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_CTX_ATTACH_RESOURCE);
	cmd_p->hdr.ctx_id = cpu_to_le32(ctx_id);
	cmd_p->resource_id = cpu_to_le32(bo->hw_res_handle);
	virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);
पूर्ण

व्योम virtio_gpu_cmd_context_detach_resource(काष्ठा virtio_gpu_device *vgdev,
					    uपूर्णांक32_t ctx_id,
					    काष्ठा virtio_gpu_object_array *objs)
अणु
	काष्ठा virtio_gpu_object *bo = gem_to_virtio_gpu_obj(objs->objs[0]);
	काष्ठा virtio_gpu_ctx_resource *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;

	cmd_p = virtio_gpu_alloc_cmd(vgdev, &vbuf, माप(*cmd_p));
	स_रखो(cmd_p, 0, माप(*cmd_p));
	vbuf->objs = objs;

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_CTX_DETACH_RESOURCE);
	cmd_p->hdr.ctx_id = cpu_to_le32(ctx_id);
	cmd_p->resource_id = cpu_to_le32(bo->hw_res_handle);
	virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);
पूर्ण

व्योम
virtio_gpu_cmd_resource_create_3d(काष्ठा virtio_gpu_device *vgdev,
				  काष्ठा virtio_gpu_object *bo,
				  काष्ठा virtio_gpu_object_params *params,
				  काष्ठा virtio_gpu_object_array *objs,
				  काष्ठा virtio_gpu_fence *fence)
अणु
	काष्ठा virtio_gpu_resource_create_3d *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;

	cmd_p = virtio_gpu_alloc_cmd(vgdev, &vbuf, माप(*cmd_p));
	स_रखो(cmd_p, 0, माप(*cmd_p));
	vbuf->objs = objs;

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_RESOURCE_CREATE_3D);
	cmd_p->resource_id = cpu_to_le32(bo->hw_res_handle);
	cmd_p->क्रमmat = cpu_to_le32(params->क्रमmat);
	cmd_p->width = cpu_to_le32(params->width);
	cmd_p->height = cpu_to_le32(params->height);

	cmd_p->target = cpu_to_le32(params->target);
	cmd_p->bind = cpu_to_le32(params->bind);
	cmd_p->depth = cpu_to_le32(params->depth);
	cmd_p->array_size = cpu_to_le32(params->array_size);
	cmd_p->last_level = cpu_to_le32(params->last_level);
	cmd_p->nr_samples = cpu_to_le32(params->nr_samples);
	cmd_p->flags = cpu_to_le32(params->flags);

	virtio_gpu_queue_fenced_ctrl_buffer(vgdev, vbuf, fence);

	bo->created = true;
पूर्ण

व्योम virtio_gpu_cmd_transfer_to_host_3d(काष्ठा virtio_gpu_device *vgdev,
					uपूर्णांक32_t ctx_id,
					uपूर्णांक64_t offset, uपूर्णांक32_t level,
					uपूर्णांक32_t stride,
					uपूर्णांक32_t layer_stride,
					काष्ठा drm_virtgpu_3d_box *box,
					काष्ठा virtio_gpu_object_array *objs,
					काष्ठा virtio_gpu_fence *fence)
अणु
	काष्ठा virtio_gpu_object *bo = gem_to_virtio_gpu_obj(objs->objs[0]);
	काष्ठा virtio_gpu_transfer_host_3d *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;
	bool use_dma_api = !virtio_has_dma_quirk(vgdev->vdev);

	अगर (virtio_gpu_is_shmem(bo) && use_dma_api) अणु
		काष्ठा virtio_gpu_object_shmem *shmem = to_virtio_gpu_shmem(bo);
		dma_sync_sgtable_क्रम_device(vgdev->vdev->dev.parent,
					    shmem->pages, DMA_TO_DEVICE);
	पूर्ण

	cmd_p = virtio_gpu_alloc_cmd(vgdev, &vbuf, माप(*cmd_p));
	स_रखो(cmd_p, 0, माप(*cmd_p));

	vbuf->objs = objs;

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_TRANSFER_TO_HOST_3D);
	cmd_p->hdr.ctx_id = cpu_to_le32(ctx_id);
	cmd_p->resource_id = cpu_to_le32(bo->hw_res_handle);
	convert_to_hw_box(&cmd_p->box, box);
	cmd_p->offset = cpu_to_le64(offset);
	cmd_p->level = cpu_to_le32(level);
	cmd_p->stride = cpu_to_le32(stride);
	cmd_p->layer_stride = cpu_to_le32(layer_stride);

	virtio_gpu_queue_fenced_ctrl_buffer(vgdev, vbuf, fence);
पूर्ण

व्योम virtio_gpu_cmd_transfer_from_host_3d(काष्ठा virtio_gpu_device *vgdev,
					  uपूर्णांक32_t ctx_id,
					  uपूर्णांक64_t offset, uपूर्णांक32_t level,
					  uपूर्णांक32_t stride,
					  uपूर्णांक32_t layer_stride,
					  काष्ठा drm_virtgpu_3d_box *box,
					  काष्ठा virtio_gpu_object_array *objs,
					  काष्ठा virtio_gpu_fence *fence)
अणु
	काष्ठा virtio_gpu_object *bo = gem_to_virtio_gpu_obj(objs->objs[0]);
	काष्ठा virtio_gpu_transfer_host_3d *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;

	cmd_p = virtio_gpu_alloc_cmd(vgdev, &vbuf, माप(*cmd_p));
	स_रखो(cmd_p, 0, माप(*cmd_p));

	vbuf->objs = objs;

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_TRANSFER_FROM_HOST_3D);
	cmd_p->hdr.ctx_id = cpu_to_le32(ctx_id);
	cmd_p->resource_id = cpu_to_le32(bo->hw_res_handle);
	convert_to_hw_box(&cmd_p->box, box);
	cmd_p->offset = cpu_to_le64(offset);
	cmd_p->level = cpu_to_le32(level);
	cmd_p->stride = cpu_to_le32(stride);
	cmd_p->layer_stride = cpu_to_le32(layer_stride);

	virtio_gpu_queue_fenced_ctrl_buffer(vgdev, vbuf, fence);
पूर्ण

व्योम virtio_gpu_cmd_submit(काष्ठा virtio_gpu_device *vgdev,
			   व्योम *data, uपूर्णांक32_t data_size,
			   uपूर्णांक32_t ctx_id,
			   काष्ठा virtio_gpu_object_array *objs,
			   काष्ठा virtio_gpu_fence *fence)
अणु
	काष्ठा virtio_gpu_cmd_submit *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;

	cmd_p = virtio_gpu_alloc_cmd(vgdev, &vbuf, माप(*cmd_p));
	स_रखो(cmd_p, 0, माप(*cmd_p));

	vbuf->data_buf = data;
	vbuf->data_size = data_size;
	vbuf->objs = objs;

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_SUBMIT_3D);
	cmd_p->hdr.ctx_id = cpu_to_le32(ctx_id);
	cmd_p->size = cpu_to_le32(data_size);

	virtio_gpu_queue_fenced_ctrl_buffer(vgdev, vbuf, fence);
पूर्ण

व्योम virtio_gpu_object_attach(काष्ठा virtio_gpu_device *vgdev,
			      काष्ठा virtio_gpu_object *obj,
			      काष्ठा virtio_gpu_mem_entry *ents,
			      अचिन्हित पूर्णांक nents)
अणु
	virtio_gpu_cmd_resource_attach_backing(vgdev, obj->hw_res_handle,
					       ents, nents, शून्य);
पूर्ण

व्योम virtio_gpu_cursor_ping(काष्ठा virtio_gpu_device *vgdev,
			    काष्ठा virtio_gpu_output *output)
अणु
	काष्ठा virtio_gpu_vbuffer *vbuf;
	काष्ठा virtio_gpu_update_cursor *cur_p;

	output->cursor.pos.scanout_id = cpu_to_le32(output->index);
	cur_p = virtio_gpu_alloc_cursor(vgdev, &vbuf);
	स_नकल(cur_p, &output->cursor, माप(output->cursor));
	virtio_gpu_queue_cursor(vgdev, vbuf);
पूर्ण

अटल व्योम virtio_gpu_cmd_resource_uuid_cb(काष्ठा virtio_gpu_device *vgdev,
					    काष्ठा virtio_gpu_vbuffer *vbuf)
अणु
	काष्ठा virtio_gpu_object *obj =
		gem_to_virtio_gpu_obj(vbuf->objs->objs[0]);
	काष्ठा virtio_gpu_resp_resource_uuid *resp =
		(काष्ठा virtio_gpu_resp_resource_uuid *)vbuf->resp_buf;
	uपूर्णांक32_t resp_type = le32_to_cpu(resp->hdr.type);

	spin_lock(&vgdev->resource_export_lock);
	WARN_ON(obj->uuid_state != STATE_INITIALIZING);

	अगर (resp_type == VIRTIO_GPU_RESP_OK_RESOURCE_UUID &&
	    obj->uuid_state == STATE_INITIALIZING) अणु
		import_uuid(&obj->uuid, resp->uuid);
		obj->uuid_state = STATE_OK;
	पूर्ण अन्यथा अणु
		obj->uuid_state = STATE_ERR;
	पूर्ण
	spin_unlock(&vgdev->resource_export_lock);

	wake_up_all(&vgdev->resp_wq);
पूर्ण

पूर्णांक
virtio_gpu_cmd_resource_assign_uuid(काष्ठा virtio_gpu_device *vgdev,
				    काष्ठा virtio_gpu_object_array *objs)
अणु
	काष्ठा virtio_gpu_object *bo = gem_to_virtio_gpu_obj(objs->objs[0]);
	काष्ठा virtio_gpu_resource_assign_uuid *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;
	काष्ठा virtio_gpu_resp_resource_uuid *resp_buf;

	resp_buf = kzalloc(माप(*resp_buf), GFP_KERNEL);
	अगर (!resp_buf) अणु
		spin_lock(&vgdev->resource_export_lock);
		bo->uuid_state = STATE_ERR;
		spin_unlock(&vgdev->resource_export_lock);
		virtio_gpu_array_put_मुक्त(objs);
		वापस -ENOMEM;
	पूर्ण

	cmd_p = virtio_gpu_alloc_cmd_resp
		(vgdev, virtio_gpu_cmd_resource_uuid_cb, &vbuf, माप(*cmd_p),
		 माप(काष्ठा virtio_gpu_resp_resource_uuid), resp_buf);
	स_रखो(cmd_p, 0, माप(*cmd_p));

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_RESOURCE_ASSIGN_UUID);
	cmd_p->resource_id = cpu_to_le32(bo->hw_res_handle);

	vbuf->objs = objs;
	virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);
	वापस 0;
पूर्ण

अटल व्योम virtio_gpu_cmd_resource_map_cb(काष्ठा virtio_gpu_device *vgdev,
					   काष्ठा virtio_gpu_vbuffer *vbuf)
अणु
	काष्ठा virtio_gpu_object *bo =
		gem_to_virtio_gpu_obj(vbuf->objs->objs[0]);
	काष्ठा virtio_gpu_resp_map_info *resp =
		(काष्ठा virtio_gpu_resp_map_info *)vbuf->resp_buf;
	काष्ठा virtio_gpu_object_vram *vram = to_virtio_gpu_vram(bo);
	uपूर्णांक32_t resp_type = le32_to_cpu(resp->hdr.type);

	spin_lock(&vgdev->host_visible_lock);

	अगर (resp_type == VIRTIO_GPU_RESP_OK_MAP_INFO) अणु
		vram->map_info = resp->map_info;
		vram->map_state = STATE_OK;
	पूर्ण अन्यथा अणु
		vram->map_state = STATE_ERR;
	पूर्ण

	spin_unlock(&vgdev->host_visible_lock);
	wake_up_all(&vgdev->resp_wq);
पूर्ण

पूर्णांक virtio_gpu_cmd_map(काष्ठा virtio_gpu_device *vgdev,
		       काष्ठा virtio_gpu_object_array *objs, uपूर्णांक64_t offset)
अणु
	काष्ठा virtio_gpu_resource_map_blob *cmd_p;
	काष्ठा virtio_gpu_object *bo = gem_to_virtio_gpu_obj(objs->objs[0]);
	काष्ठा virtio_gpu_vbuffer *vbuf;
	काष्ठा virtio_gpu_resp_map_info *resp_buf;

	resp_buf = kzalloc(माप(*resp_buf), GFP_KERNEL);
	अगर (!resp_buf)
		वापस -ENOMEM;

	cmd_p = virtio_gpu_alloc_cmd_resp
		(vgdev, virtio_gpu_cmd_resource_map_cb, &vbuf, माप(*cmd_p),
		 माप(काष्ठा virtio_gpu_resp_map_info), resp_buf);
	स_रखो(cmd_p, 0, माप(*cmd_p));

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_RESOURCE_MAP_BLOB);
	cmd_p->resource_id = cpu_to_le32(bo->hw_res_handle);
	cmd_p->offset = cpu_to_le64(offset);
	vbuf->objs = objs;

	virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);
	वापस 0;
पूर्ण

व्योम virtio_gpu_cmd_unmap(काष्ठा virtio_gpu_device *vgdev,
			  काष्ठा virtio_gpu_object *bo)
अणु
	काष्ठा virtio_gpu_resource_unmap_blob *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;

	cmd_p = virtio_gpu_alloc_cmd(vgdev, &vbuf, माप(*cmd_p));
	स_रखो(cmd_p, 0, माप(*cmd_p));

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_RESOURCE_UNMAP_BLOB);
	cmd_p->resource_id = cpu_to_le32(bo->hw_res_handle);

	virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);
पूर्ण

व्योम
virtio_gpu_cmd_resource_create_blob(काष्ठा virtio_gpu_device *vgdev,
				    काष्ठा virtio_gpu_object *bo,
				    काष्ठा virtio_gpu_object_params *params,
				    काष्ठा virtio_gpu_mem_entry *ents,
				    uपूर्णांक32_t nents)
अणु
	काष्ठा virtio_gpu_resource_create_blob *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;

	cmd_p = virtio_gpu_alloc_cmd(vgdev, &vbuf, माप(*cmd_p));
	स_रखो(cmd_p, 0, माप(*cmd_p));

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_RESOURCE_CREATE_BLOB);
	cmd_p->hdr.ctx_id = cpu_to_le32(params->ctx_id);
	cmd_p->resource_id = cpu_to_le32(bo->hw_res_handle);
	cmd_p->blob_mem = cpu_to_le32(params->blob_mem);
	cmd_p->blob_flags = cpu_to_le32(params->blob_flags);
	cmd_p->blob_id = cpu_to_le64(params->blob_id);
	cmd_p->size = cpu_to_le64(params->size);
	cmd_p->nr_entries = cpu_to_le32(nents);

	vbuf->data_buf = ents;
	vbuf->data_size = माप(*ents) * nents;

	virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);
	bo->created = true;
पूर्ण

व्योम virtio_gpu_cmd_set_scanout_blob(काष्ठा virtio_gpu_device *vgdev,
				     uपूर्णांक32_t scanout_id,
				     काष्ठा virtio_gpu_object *bo,
				     काष्ठा drm_framebuffer *fb,
				     uपूर्णांक32_t width, uपूर्णांक32_t height,
				     uपूर्णांक32_t x, uपूर्णांक32_t y)
अणु
	uपूर्णांक32_t i;
	काष्ठा virtio_gpu_set_scanout_blob *cmd_p;
	काष्ठा virtio_gpu_vbuffer *vbuf;
	uपूर्णांक32_t क्रमmat = virtio_gpu_translate_क्रमmat(fb->क्रमmat->क्रमmat);

	cmd_p = virtio_gpu_alloc_cmd(vgdev, &vbuf, माप(*cmd_p));
	स_रखो(cmd_p, 0, माप(*cmd_p));

	cmd_p->hdr.type = cpu_to_le32(VIRTIO_GPU_CMD_SET_SCANOUT_BLOB);
	cmd_p->resource_id = cpu_to_le32(bo->hw_res_handle);
	cmd_p->scanout_id = cpu_to_le32(scanout_id);

	cmd_p->क्रमmat = cpu_to_le32(क्रमmat);
	cmd_p->width  = cpu_to_le32(fb->width);
	cmd_p->height = cpu_to_le32(fb->height);

	क्रम (i = 0; i < 4; i++) अणु
		cmd_p->strides[i] = cpu_to_le32(fb->pitches[i]);
		cmd_p->offsets[i] = cpu_to_le32(fb->offsets[i]);
	पूर्ण

	cmd_p->r.width = cpu_to_le32(width);
	cmd_p->r.height = cpu_to_le32(height);
	cmd_p->r.x = cpu_to_le32(x);
	cmd_p->r.y = cpu_to_le32(y);

	virtio_gpu_queue_ctrl_buffer(vgdev, vbuf);
पूर्ण
