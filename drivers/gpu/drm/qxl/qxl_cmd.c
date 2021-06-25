<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
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
 * Authors: Dave Airlie
 *          Alon Levy
 */

/* QXL cmd/ring handling */

#समावेश <linux/delay.h>

#समावेश <drm/drm_util.h>

#समावेश "qxl_drv.h"
#समावेश "qxl_object.h"

अटल पूर्णांक qxl_reap_surface_id(काष्ठा qxl_device *qdev, पूर्णांक max_to_reap);

काष्ठा ring अणु
	काष्ठा qxl_ring_header      header;
	uपूर्णांक8_t                     elements[];
पूर्ण;

काष्ठा qxl_ring अणु
	काष्ठा ring	       *ring;
	पूर्णांक			element_size;
	पूर्णांक			n_elements;
	पूर्णांक			prod_notअगरy;
	रुको_queue_head_t      *push_event;
	spinlock_t             lock;
पूर्ण;

व्योम qxl_ring_मुक्त(काष्ठा qxl_ring *ring)
अणु
	kमुक्त(ring);
पूर्ण

व्योम qxl_ring_init_hdr(काष्ठा qxl_ring *ring)
अणु
	ring->ring->header.notअगरy_on_prod = ring->n_elements;
पूर्ण

काष्ठा qxl_ring *
qxl_ring_create(काष्ठा qxl_ring_header *header,
		पूर्णांक element_size,
		पूर्णांक n_elements,
		पूर्णांक prod_notअगरy,
		bool set_prod_notअगरy,
		रुको_queue_head_t *push_event)
अणु
	काष्ठा qxl_ring *ring;

	ring = kदो_स्मृति(माप(*ring), GFP_KERNEL);
	अगर (!ring)
		वापस शून्य;

	ring->ring = (काष्ठा ring *)header;
	ring->element_size = element_size;
	ring->n_elements = n_elements;
	ring->prod_notअगरy = prod_notअगरy;
	ring->push_event = push_event;
	अगर (set_prod_notअगरy)
		qxl_ring_init_hdr(ring);
	spin_lock_init(&ring->lock);
	वापस ring;
पूर्ण

अटल पूर्णांक qxl_check_header(काष्ठा qxl_ring *ring)
अणु
	पूर्णांक ret;
	काष्ठा qxl_ring_header *header = &(ring->ring->header);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ring->lock, flags);
	ret = header->prod - header->cons < header->num_items;
	अगर (ret == 0)
		header->notअगरy_on_cons = header->cons + 1;
	spin_unlock_irqrestore(&ring->lock, flags);
	वापस ret;
पूर्ण

पूर्णांक qxl_check_idle(काष्ठा qxl_ring *ring)
अणु
	पूर्णांक ret;
	काष्ठा qxl_ring_header *header = &(ring->ring->header);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ring->lock, flags);
	ret = header->prod == header->cons;
	spin_unlock_irqrestore(&ring->lock, flags);
	वापस ret;
पूर्ण

पूर्णांक qxl_ring_push(काष्ठा qxl_ring *ring,
		  स्थिर व्योम *new_elt, bool पूर्णांकerruptible)
अणु
	काष्ठा qxl_ring_header *header = &(ring->ring->header);
	uपूर्णांक8_t *elt;
	पूर्णांक idx, ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ring->lock, flags);
	अगर (header->prod - header->cons == header->num_items) अणु
		header->notअगरy_on_cons = header->cons + 1;
		mb();
		spin_unlock_irqrestore(&ring->lock, flags);
		अगर (!drm_can_sleep()) अणु
			जबतक (!qxl_check_header(ring))
				udelay(1);
		पूर्ण अन्यथा अणु
			अगर (पूर्णांकerruptible) अणु
				ret = रुको_event_पूर्णांकerruptible(*ring->push_event,
							       qxl_check_header(ring));
				अगर (ret)
					वापस ret;
			पूर्ण अन्यथा अणु
				रुको_event(*ring->push_event,
					   qxl_check_header(ring));
			पूर्ण

		पूर्ण
		spin_lock_irqsave(&ring->lock, flags);
	पूर्ण

	idx = header->prod & (ring->n_elements - 1);
	elt = ring->ring->elements + idx * ring->element_size;

	स_नकल((व्योम *)elt, new_elt, ring->element_size);

	header->prod++;

	mb();

	अगर (header->prod == header->notअगरy_on_prod)
		outb(0, ring->prod_notअगरy);

	spin_unlock_irqrestore(&ring->lock, flags);
	वापस 0;
पूर्ण

अटल bool qxl_ring_pop(काष्ठा qxl_ring *ring,
			 व्योम *element)
अणु
	अस्थिर काष्ठा qxl_ring_header *header = &(ring->ring->header);
	अस्थिर uपूर्णांक8_t *ring_elt;
	पूर्णांक idx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ring->lock, flags);
	अगर (header->cons == header->prod) अणु
		header->notअगरy_on_prod = header->cons + 1;
		spin_unlock_irqrestore(&ring->lock, flags);
		वापस false;
	पूर्ण

	idx = header->cons & (ring->n_elements - 1);
	ring_elt = ring->ring->elements + idx * ring->element_size;

	स_नकल(element, (व्योम *)ring_elt, ring->element_size);

	header->cons++;

	spin_unlock_irqrestore(&ring->lock, flags);
	वापस true;
पूर्ण

पूर्णांक
qxl_push_command_ring_release(काष्ठा qxl_device *qdev, काष्ठा qxl_release *release,
			      uपूर्णांक32_t type, bool पूर्णांकerruptible)
अणु
	काष्ठा qxl_command cmd;

	cmd.type = type;
	cmd.data = qxl_bo_physical_address(qdev, release->release_bo, release->release_offset);

	वापस qxl_ring_push(qdev->command_ring, &cmd, पूर्णांकerruptible);
पूर्ण

पूर्णांक
qxl_push_cursor_ring_release(काष्ठा qxl_device *qdev, काष्ठा qxl_release *release,
			     uपूर्णांक32_t type, bool पूर्णांकerruptible)
अणु
	काष्ठा qxl_command cmd;

	cmd.type = type;
	cmd.data = qxl_bo_physical_address(qdev, release->release_bo, release->release_offset);

	वापस qxl_ring_push(qdev->cursor_ring, &cmd, पूर्णांकerruptible);
पूर्ण

bool qxl_queue_garbage_collect(काष्ठा qxl_device *qdev, bool flush)
अणु
	अगर (!qxl_check_idle(qdev->release_ring)) अणु
		schedule_work(&qdev->gc_work);
		अगर (flush)
			flush_work(&qdev->gc_work);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक qxl_garbage_collect(काष्ठा qxl_device *qdev)
अणु
	काष्ठा qxl_release *release;
	uपूर्णांक64_t id, next_id;
	पूर्णांक i = 0;
	जोड़ qxl_release_info *info;

	जबतक (qxl_ring_pop(qdev->release_ring, &id)) अणु
		DRM_DEBUG_DRIVER("popped %lld\n", id);
		जबतक (id) अणु
			release = qxl_release_from_id_locked(qdev, id);
			अगर (release == शून्य)
				अवरोध;

			info = qxl_release_map(qdev, release);
			next_id = info->next;
			qxl_release_unmap(qdev, release, info);

			DRM_DEBUG_DRIVER("popped %lld, next %lld\n", id,
					 next_id);

			चयन (release->type) अणु
			हाल QXL_RELEASE_DRAWABLE:
			हाल QXL_RELEASE_SURFACE_CMD:
			हाल QXL_RELEASE_CURSOR_CMD:
				अवरोध;
			शेष:
				DRM_ERROR("unexpected release type\n");
				अवरोध;
			पूर्ण
			id = next_id;

			qxl_release_मुक्त(qdev, release);
			++i;
		पूर्ण
	पूर्ण

	wake_up_all(&qdev->release_event);
	DRM_DEBUG_DRIVER("%d\n", i);

	वापस i;
पूर्ण

पूर्णांक qxl_alloc_bo_reserved(काष्ठा qxl_device *qdev,
			  काष्ठा qxl_release *release,
			  अचिन्हित दीर्घ size,
			  काष्ठा qxl_bo **_bo)
अणु
	काष्ठा qxl_bo *bo;
	पूर्णांक ret;

	ret = qxl_bo_create(qdev, size, false /* not kernel - device */,
			    false, QXL_GEM_DOMAIN_VRAM, 0, शून्य, &bo);
	अगर (ret) अणु
		DRM_ERROR("failed to allocate VRAM BO\n");
		वापस ret;
	पूर्ण
	ret = qxl_release_list_add(release, bo);
	अगर (ret)
		जाओ out_unref;

	*_bo = bo;
	वापस 0;
out_unref:
	qxl_bo_unref(&bo);
	वापस ret;
पूर्ण

अटल पूर्णांक रुको_क्रम_io_cmd_user(काष्ठा qxl_device *qdev, uपूर्णांक8_t val, दीर्घ port, bool पूर्णांकr)
अणु
	पूर्णांक irq_num;
	दीर्घ addr = qdev->io_base + port;
	पूर्णांक ret;

	mutex_lock(&qdev->async_io_mutex);
	irq_num = atomic_पढ़ो(&qdev->irq_received_io_cmd);
	अगर (qdev->last_sent_io_cmd > irq_num) अणु
		अगर (पूर्णांकr)
			ret = रुको_event_पूर्णांकerruptible_समयout(qdev->io_cmd_event,
							       atomic_पढ़ो(&qdev->irq_received_io_cmd) > irq_num, 5*HZ);
		अन्यथा
			ret = रुको_event_समयout(qdev->io_cmd_event,
						 atomic_पढ़ो(&qdev->irq_received_io_cmd) > irq_num, 5*HZ);
		/* 0 is समयout, just bail the "hw" has gone away */
		अगर (ret <= 0)
			जाओ out;
		irq_num = atomic_पढ़ो(&qdev->irq_received_io_cmd);
	पूर्ण
	outb(val, addr);
	qdev->last_sent_io_cmd = irq_num + 1;
	अगर (पूर्णांकr)
		ret = रुको_event_पूर्णांकerruptible_समयout(qdev->io_cmd_event,
						       atomic_पढ़ो(&qdev->irq_received_io_cmd) > irq_num, 5*HZ);
	अन्यथा
		ret = रुको_event_समयout(qdev->io_cmd_event,
					 atomic_पढ़ो(&qdev->irq_received_io_cmd) > irq_num, 5*HZ);
out:
	अगर (ret > 0)
		ret = 0;
	mutex_unlock(&qdev->async_io_mutex);
	वापस ret;
पूर्ण

अटल व्योम रुको_क्रम_io_cmd(काष्ठा qxl_device *qdev, uपूर्णांक8_t val, दीर्घ port)
अणु
	पूर्णांक ret;

restart:
	ret = रुको_क्रम_io_cmd_user(qdev, val, port, false);
	अगर (ret == -ERESTARTSYS)
		जाओ restart;
पूर्ण

पूर्णांक qxl_io_update_area(काष्ठा qxl_device *qdev, काष्ठा qxl_bo *surf,
			स्थिर काष्ठा qxl_rect *area)
अणु
	पूर्णांक surface_id;
	uपूर्णांक32_t surface_width, surface_height;
	पूर्णांक ret;

	अगर (!surf->hw_surf_alloc)
		DRM_ERROR("got io update area with no hw surface\n");

	अगर (surf->is_primary)
		surface_id = 0;
	अन्यथा
		surface_id = surf->surface_id;
	surface_width = surf->surf.width;
	surface_height = surf->surf.height;

	अगर (area->left < 0 || area->top < 0 ||
	    area->right > surface_width || area->bottom > surface_height)
		वापस -EINVAL;

	mutex_lock(&qdev->update_area_mutex);
	qdev->ram_header->update_area = *area;
	qdev->ram_header->update_surface = surface_id;
	ret = रुको_क्रम_io_cmd_user(qdev, 0, QXL_IO_UPDATE_AREA_ASYNC, true);
	mutex_unlock(&qdev->update_area_mutex);
	वापस ret;
पूर्ण

व्योम qxl_io_notअगरy_oom(काष्ठा qxl_device *qdev)
अणु
	outb(0, qdev->io_base + QXL_IO_NOTIFY_OOM);
पूर्ण

व्योम qxl_io_flush_release(काष्ठा qxl_device *qdev)
अणु
	outb(0, qdev->io_base + QXL_IO_FLUSH_RELEASE);
पूर्ण

व्योम qxl_io_flush_surfaces(काष्ठा qxl_device *qdev)
अणु
	रुको_क्रम_io_cmd(qdev, 0, QXL_IO_FLUSH_SURFACES_ASYNC);
पूर्ण

व्योम qxl_io_destroy_primary(काष्ठा qxl_device *qdev)
अणु
	रुको_क्रम_io_cmd(qdev, 0, QXL_IO_DESTROY_PRIMARY_ASYNC);
	qdev->primary_bo->is_primary = false;
	drm_gem_object_put(&qdev->primary_bo->tbo.base);
	qdev->primary_bo = शून्य;
पूर्ण

व्योम qxl_io_create_primary(काष्ठा qxl_device *qdev, काष्ठा qxl_bo *bo)
अणु
	काष्ठा qxl_surface_create *create;

	अगर (WARN_ON(qdev->primary_bo))
		वापस;

	DRM_DEBUG_DRIVER("qdev %p, ram_header %p\n", qdev, qdev->ram_header);
	create = &qdev->ram_header->create_surface;
	create->क्रमmat = bo->surf.क्रमmat;
	create->width = bo->surf.width;
	create->height = bo->surf.height;
	create->stride = bo->surf.stride;
	create->mem = qxl_bo_physical_address(qdev, bo, 0);

	DRM_DEBUG_DRIVER("mem = %llx, from %p\n", create->mem, bo->kptr);

	create->flags = QXL_SURF_FLAG_KEEP_DATA;
	create->type = QXL_SURF_TYPE_PRIMARY;

	रुको_क्रम_io_cmd(qdev, 0, QXL_IO_CREATE_PRIMARY_ASYNC);
	qdev->primary_bo = bo;
	qdev->primary_bo->is_primary = true;
	drm_gem_object_get(&qdev->primary_bo->tbo.base);
पूर्ण

व्योम qxl_io_memslot_add(काष्ठा qxl_device *qdev, uपूर्णांक8_t id)
अणु
	DRM_DEBUG_DRIVER("qxl_memslot_add %d\n", id);
	रुको_क्रम_io_cmd(qdev, id, QXL_IO_MEMSLOT_ADD_ASYNC);
पूर्ण

व्योम qxl_io_reset(काष्ठा qxl_device *qdev)
अणु
	outb(0, qdev->io_base + QXL_IO_RESET);
पूर्ण

व्योम qxl_io_monitors_config(काष्ठा qxl_device *qdev)
अणु
	रुको_क्रम_io_cmd(qdev, 0, QXL_IO_MONITORS_CONFIG_ASYNC);
पूर्ण

पूर्णांक qxl_surface_id_alloc(काष्ठा qxl_device *qdev,
		      काष्ठा qxl_bo *surf)
अणु
	uपूर्णांक32_t handle;
	पूर्णांक idr_ret;
	पूर्णांक count = 0;
again:
	idr_preload(GFP_ATOMIC);
	spin_lock(&qdev->surf_id_idr_lock);
	idr_ret = idr_alloc(&qdev->surf_id_idr, शून्य, 1, 0, GFP_NOWAIT);
	spin_unlock(&qdev->surf_id_idr_lock);
	idr_preload_end();
	अगर (idr_ret < 0)
		वापस idr_ret;
	handle = idr_ret;

	अगर (handle >= qdev->rom->n_surfaces) अणु
		count++;
		spin_lock(&qdev->surf_id_idr_lock);
		idr_हटाओ(&qdev->surf_id_idr, handle);
		spin_unlock(&qdev->surf_id_idr_lock);
		qxl_reap_surface_id(qdev, 2);
		जाओ again;
	पूर्ण
	surf->surface_id = handle;

	spin_lock(&qdev->surf_id_idr_lock);
	qdev->last_alloced_surf_id = handle;
	spin_unlock(&qdev->surf_id_idr_lock);
	वापस 0;
पूर्ण

व्योम qxl_surface_id_dealloc(काष्ठा qxl_device *qdev,
			    uपूर्णांक32_t surface_id)
अणु
	spin_lock(&qdev->surf_id_idr_lock);
	idr_हटाओ(&qdev->surf_id_idr, surface_id);
	spin_unlock(&qdev->surf_id_idr_lock);
पूर्ण

पूर्णांक qxl_hw_surface_alloc(काष्ठा qxl_device *qdev,
			 काष्ठा qxl_bo *surf)
अणु
	काष्ठा qxl_surface_cmd *cmd;
	काष्ठा qxl_release *release;
	पूर्णांक ret;

	अगर (surf->hw_surf_alloc)
		वापस 0;

	ret = qxl_alloc_surface_release_reserved(qdev, QXL_SURFACE_CMD_CREATE,
						 शून्य,
						 &release);
	अगर (ret)
		वापस ret;

	ret = qxl_release_reserve_list(release, true);
	अगर (ret) अणु
		qxl_release_मुक्त(qdev, release);
		वापस ret;
	पूर्ण
	cmd = (काष्ठा qxl_surface_cmd *)qxl_release_map(qdev, release);
	cmd->type = QXL_SURFACE_CMD_CREATE;
	cmd->flags = QXL_SURF_FLAG_KEEP_DATA;
	cmd->u.surface_create.क्रमmat = surf->surf.क्रमmat;
	cmd->u.surface_create.width = surf->surf.width;
	cmd->u.surface_create.height = surf->surf.height;
	cmd->u.surface_create.stride = surf->surf.stride;
	cmd->u.surface_create.data = qxl_bo_physical_address(qdev, surf, 0);
	cmd->surface_id = surf->surface_id;
	qxl_release_unmap(qdev, release, &cmd->release_info);

	surf->surf_create = release;

	/* no need to add a release to the fence क्रम this surface bo,
	   since it is only released when we ask to destroy the surface
	   and it would never संकेत otherwise */
	qxl_release_fence_buffer_objects(release);
	qxl_push_command_ring_release(qdev, release, QXL_CMD_SURFACE, false);

	surf->hw_surf_alloc = true;
	spin_lock(&qdev->surf_id_idr_lock);
	idr_replace(&qdev->surf_id_idr, surf, surf->surface_id);
	spin_unlock(&qdev->surf_id_idr_lock);
	वापस 0;
पूर्ण

पूर्णांक qxl_hw_surface_dealloc(काष्ठा qxl_device *qdev,
			   काष्ठा qxl_bo *surf)
अणु
	काष्ठा qxl_surface_cmd *cmd;
	काष्ठा qxl_release *release;
	पूर्णांक ret;
	पूर्णांक id;

	अगर (!surf->hw_surf_alloc)
		वापस 0;

	ret = qxl_alloc_surface_release_reserved(qdev, QXL_SURFACE_CMD_DESTROY,
						 surf->surf_create,
						 &release);
	अगर (ret)
		वापस ret;

	surf->surf_create = शून्य;
	/* हटाओ the surface from the idr, but not the surface id yet */
	spin_lock(&qdev->surf_id_idr_lock);
	idr_replace(&qdev->surf_id_idr, शून्य, surf->surface_id);
	spin_unlock(&qdev->surf_id_idr_lock);
	surf->hw_surf_alloc = false;

	id = surf->surface_id;
	surf->surface_id = 0;

	release->surface_release_id = id;
	cmd = (काष्ठा qxl_surface_cmd *)qxl_release_map(qdev, release);
	cmd->type = QXL_SURFACE_CMD_DESTROY;
	cmd->surface_id = id;
	qxl_release_unmap(qdev, release, &cmd->release_info);

	qxl_release_fence_buffer_objects(release);
	qxl_push_command_ring_release(qdev, release, QXL_CMD_SURFACE, false);

	वापस 0;
पूर्ण

अटल पूर्णांक qxl_update_surface(काष्ठा qxl_device *qdev, काष्ठा qxl_bo *surf)
अणु
	काष्ठा qxl_rect rect;
	पूर्णांक ret;

	/* अगर we are evicting, we need to make sure the surface is up
	   to date */
	rect.left = 0;
	rect.right = surf->surf.width;
	rect.top = 0;
	rect.bottom = surf->surf.height;
retry:
	ret = qxl_io_update_area(qdev, surf, &rect);
	अगर (ret == -ERESTARTSYS)
		जाओ retry;
	वापस ret;
पूर्ण

अटल व्योम qxl_surface_evict_locked(काष्ठा qxl_device *qdev, काष्ठा qxl_bo *surf, bool करो_update_area)
अणु
	/* no need to update area अगर we are just मुक्तing the surface normally */
	अगर (करो_update_area)
		qxl_update_surface(qdev, surf);

	/* nuke the surface id at the hw */
	qxl_hw_surface_dealloc(qdev, surf);
पूर्ण

व्योम qxl_surface_evict(काष्ठा qxl_device *qdev, काष्ठा qxl_bo *surf, bool करो_update_area)
अणु
	mutex_lock(&qdev->surf_evict_mutex);
	qxl_surface_evict_locked(qdev, surf, करो_update_area);
	mutex_unlock(&qdev->surf_evict_mutex);
पूर्ण

अटल पूर्णांक qxl_reap_surf(काष्ठा qxl_device *qdev, काष्ठा qxl_bo *surf, bool stall)
अणु
	पूर्णांक ret;

	ret = qxl_bo_reserve(surf);
	अगर (ret)
		वापस ret;

	अगर (stall)
		mutex_unlock(&qdev->surf_evict_mutex);

	ret = tपंचांग_bo_रुको(&surf->tbo, true, !stall);

	अगर (stall)
		mutex_lock(&qdev->surf_evict_mutex);
	अगर (ret) अणु
		qxl_bo_unreserve(surf);
		वापस ret;
	पूर्ण

	qxl_surface_evict_locked(qdev, surf, true);
	qxl_bo_unreserve(surf);
	वापस 0;
पूर्ण

अटल पूर्णांक qxl_reap_surface_id(काष्ठा qxl_device *qdev, पूर्णांक max_to_reap)
अणु
	पूर्णांक num_reaped = 0;
	पूर्णांक i, ret;
	bool stall = false;
	पूर्णांक start = 0;

	mutex_lock(&qdev->surf_evict_mutex);
again:

	spin_lock(&qdev->surf_id_idr_lock);
	start = qdev->last_alloced_surf_id + 1;
	spin_unlock(&qdev->surf_id_idr_lock);

	क्रम (i = start; i < start + qdev->rom->n_surfaces; i++) अणु
		व्योम *objptr;
		पूर्णांक surfid = i % qdev->rom->n_surfaces;

		/* this aव्योमs the हाल where the objects is in the
		   idr but has been evicted half way - its makes
		   the idr lookup atomic with the eviction */
		spin_lock(&qdev->surf_id_idr_lock);
		objptr = idr_find(&qdev->surf_id_idr, surfid);
		spin_unlock(&qdev->surf_id_idr_lock);

		अगर (!objptr)
			जारी;

		ret = qxl_reap_surf(qdev, objptr, stall);
		अगर (ret == 0)
			num_reaped++;
		अगर (num_reaped >= max_to_reap)
			अवरोध;
	पूर्ण
	अगर (num_reaped == 0 && stall == false) अणु
		stall = true;
		जाओ again;
	पूर्ण

	mutex_unlock(&qdev->surf_evict_mutex);
	अगर (num_reaped) अणु
		usleep_range(500, 1000);
		qxl_queue_garbage_collect(qdev, true);
	पूर्ण

	वापस 0;
पूर्ण
