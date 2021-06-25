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

#समावेश <trace/events/dma_fence.h>

#समावेश "virtgpu_drv.h"

#घोषणा to_virtio_gpu_fence(x) \
	container_of(x, काष्ठा virtio_gpu_fence, f)

अटल स्थिर अक्षर *virtio_gpu_get_driver_name(काष्ठा dma_fence *f)
अणु
	वापस "virtio_gpu";
पूर्ण

अटल स्थिर अक्षर *virtio_gpu_get_समयline_name(काष्ठा dma_fence *f)
अणु
	वापस "controlq";
पूर्ण

अटल bool virtio_gpu_fence_संकेतed(काष्ठा dma_fence *f)
अणु
	/* leaked fence outside driver beक्रमe completing
	 * initialization with virtio_gpu_fence_emit.
	 */
	WARN_ON_ONCE(f->seqno == 0);
	वापस false;
पूर्ण

अटल व्योम virtio_gpu_fence_value_str(काष्ठा dma_fence *f, अक्षर *str, पूर्णांक size)
अणु
	snम_लिखो(str, size, "[%llu, %llu]", f->context, f->seqno);
पूर्ण

अटल व्योम virtio_gpu_समयline_value_str(काष्ठा dma_fence *f, अक्षर *str,
					  पूर्णांक size)
अणु
	काष्ठा virtio_gpu_fence *fence = to_virtio_gpu_fence(f);

	snम_लिखो(str, size, "%llu",
		 (u64)atomic64_पढ़ो(&fence->drv->last_fence_id));
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops virtio_gpu_fence_ops = अणु
	.get_driver_name     = virtio_gpu_get_driver_name,
	.get_समयline_name   = virtio_gpu_get_समयline_name,
	.संकेतed            = virtio_gpu_fence_संकेतed,
	.fence_value_str     = virtio_gpu_fence_value_str,
	.समयline_value_str  = virtio_gpu_समयline_value_str,
पूर्ण;

काष्ठा virtio_gpu_fence *virtio_gpu_fence_alloc(काष्ठा virtio_gpu_device *vgdev)
अणु
	काष्ठा virtio_gpu_fence_driver *drv = &vgdev->fence_drv;
	काष्ठा virtio_gpu_fence *fence = kzalloc(माप(काष्ठा virtio_gpu_fence),
							GFP_KERNEL);
	अगर (!fence)
		वापस fence;

	fence->drv = drv;

	/* This only partially initializes the fence because the seqno is
	 * unknown yet.  The fence must not be used outside of the driver
	 * until virtio_gpu_fence_emit is called.
	 */
	dma_fence_init(&fence->f, &virtio_gpu_fence_ops, &drv->lock, drv->context,
		       0);

	वापस fence;
पूर्ण

व्योम virtio_gpu_fence_emit(काष्ठा virtio_gpu_device *vgdev,
			  काष्ठा virtio_gpu_ctrl_hdr *cmd_hdr,
			  काष्ठा virtio_gpu_fence *fence)
अणु
	काष्ठा virtio_gpu_fence_driver *drv = &vgdev->fence_drv;
	अचिन्हित दीर्घ irq_flags;

	spin_lock_irqsave(&drv->lock, irq_flags);
	fence->fence_id = fence->f.seqno = ++drv->current_fence_id;
	dma_fence_get(&fence->f);
	list_add_tail(&fence->node, &drv->fences);
	spin_unlock_irqrestore(&drv->lock, irq_flags);

	trace_dma_fence_emit(&fence->f);

	cmd_hdr->flags |= cpu_to_le32(VIRTIO_GPU_FLAG_FENCE);
	cmd_hdr->fence_id = cpu_to_le64(fence->fence_id);
पूर्ण

व्योम virtio_gpu_fence_event_process(काष्ठा virtio_gpu_device *vgdev,
				    u64 fence_id)
अणु
	काष्ठा virtio_gpu_fence_driver *drv = &vgdev->fence_drv;
	काष्ठा virtio_gpu_fence *संकेतed, *curr, *पंचांगp;
	अचिन्हित दीर्घ irq_flags;

	spin_lock_irqsave(&drv->lock, irq_flags);
	atomic64_set(&vgdev->fence_drv.last_fence_id, fence_id);
	list_क्रम_each_entry_safe(curr, पंचांगp, &drv->fences, node) अणु
		अगर (fence_id != curr->fence_id)
			जारी;

		संकेतed = curr;

		/*
		 * Signal any fences with a strictly smaller sequence number
		 * than the current संकेतed fence.
		 */
		list_क्रम_each_entry_safe(curr, पंचांगp, &drv->fences, node) अणु
			/* dma-fence contexts must match */
			अगर (संकेतed->f.context != curr->f.context)
				जारी;

			अगर (!dma_fence_is_later(&संकेतed->f, &curr->f))
				जारी;

			dma_fence_संकेत_locked(&curr->f);
			list_del(&curr->node);
			dma_fence_put(&curr->f);
		पूर्ण

		dma_fence_संकेत_locked(&संकेतed->f);
		list_del(&संकेतed->node);
		dma_fence_put(&संकेतed->f);
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&drv->lock, irq_flags);
पूर्ण
