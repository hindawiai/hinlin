<शैली गुरु>
/*
 * Copyright 2011 Red Hat, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * on the rights to use, copy, modअगरy, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/delay.h>

#समावेश <trace/events/dma_fence.h>

#समावेश "qxl_drv.h"
#समावेश "qxl_object.h"

/*
 * drawable cmd cache - allocate a bunch of VRAM pages, suballocate
 * पूर्णांकo 256 byte chunks क्रम now - gives 16 cmds per page.
 *
 * use an ida to index पूर्णांकo the chunks?
 */
/* manage releaseables */
/* stack them 16 high क्रम now -drawable object is 191 */
#घोषणा RELEASE_SIZE 256
#घोषणा RELEASES_PER_BO (4096 / RELEASE_SIZE)
/* put an alloc/dealloc surface cmd पूर्णांकo one bo and round up to 128 */
#घोषणा SURFACE_RELEASE_SIZE 128
#घोषणा SURFACE_RELEASES_PER_BO (4096 / SURFACE_RELEASE_SIZE)

अटल स्थिर पूर्णांक release_size_per_bo[] = अणु RELEASE_SIZE, SURFACE_RELEASE_SIZE, RELEASE_SIZE पूर्ण;
अटल स्थिर पूर्णांक releases_per_bo[] = अणु RELEASES_PER_BO, SURFACE_RELEASES_PER_BO, RELEASES_PER_BO पूर्ण;

अटल स्थिर अक्षर *qxl_get_driver_name(काष्ठा dma_fence *fence)
अणु
	वापस "qxl";
पूर्ण

अटल स्थिर अक्षर *qxl_get_समयline_name(काष्ठा dma_fence *fence)
अणु
	वापस "release";
पूर्ण

अटल दीर्घ qxl_fence_रुको(काष्ठा dma_fence *fence, bool पूर्णांकr,
			   चिन्हित दीर्घ समयout)
अणु
	काष्ठा qxl_device *qdev;
	अचिन्हित दीर्घ cur, end = jअगरfies + समयout;

	qdev = container_of(fence->lock, काष्ठा qxl_device, release_lock);

	अगर (!रुको_event_समयout(qdev->release_event,
				(dma_fence_is_संकेतed(fence) ||
				 (qxl_io_notअगरy_oom(qdev), 0)),
				समयout))
		वापस 0;

	cur = jअगरfies;
	अगर (समय_after(cur, end))
		वापस 0;
	वापस end - cur;
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops qxl_fence_ops = अणु
	.get_driver_name = qxl_get_driver_name,
	.get_समयline_name = qxl_get_समयline_name,
	.रुको = qxl_fence_रुको,
पूर्ण;

अटल पूर्णांक
qxl_release_alloc(काष्ठा qxl_device *qdev, पूर्णांक type,
		  काष्ठा qxl_release **ret)
अणु
	काष्ठा qxl_release *release;
	पूर्णांक handle;
	माप_प्रकार size = माप(*release);

	release = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!release) अणु
		DRM_ERROR("Out of memory\n");
		वापस -ENOMEM;
	पूर्ण
	release->base.ops = शून्य;
	release->type = type;
	release->release_offset = 0;
	release->surface_release_id = 0;
	INIT_LIST_HEAD(&release->bos);

	idr_preload(GFP_KERNEL);
	spin_lock(&qdev->release_idr_lock);
	handle = idr_alloc(&qdev->release_idr, release, 1, 0, GFP_NOWAIT);
	release->base.seqno = ++qdev->release_seqno;
	spin_unlock(&qdev->release_idr_lock);
	idr_preload_end();
	अगर (handle < 0) अणु
		kमुक्त(release);
		*ret = शून्य;
		वापस handle;
	पूर्ण
	*ret = release;
	DRM_DEBUG_DRIVER("allocated release %d\n", handle);
	release->id = handle;
	वापस handle;
पूर्ण

अटल व्योम
qxl_release_मुक्त_list(काष्ठा qxl_release *release)
अणु
	जबतक (!list_empty(&release->bos)) अणु
		काष्ठा qxl_bo_list *entry;
		काष्ठा qxl_bo *bo;

		entry = container_of(release->bos.next,
				     काष्ठा qxl_bo_list, tv.head);
		bo = to_qxl_bo(entry->tv.bo);
		qxl_bo_unref(&bo);
		list_del(&entry->tv.head);
		kमुक्त(entry);
	पूर्ण
	release->release_bo = शून्य;
पूर्ण

व्योम
qxl_release_मुक्त(काष्ठा qxl_device *qdev,
		 काष्ठा qxl_release *release)
अणु
	DRM_DEBUG_DRIVER("release %d, type %d\n", release->id, release->type);

	अगर (release->surface_release_id)
		qxl_surface_id_dealloc(qdev, release->surface_release_id);

	spin_lock(&qdev->release_idr_lock);
	idr_हटाओ(&qdev->release_idr, release->id);
	spin_unlock(&qdev->release_idr_lock);

	अगर (release->base.ops) अणु
		WARN_ON(list_empty(&release->bos));
		qxl_release_मुक्त_list(release);

		dma_fence_संकेत(&release->base);
		dma_fence_put(&release->base);
	पूर्ण अन्यथा अणु
		qxl_release_मुक्त_list(release);
		kमुक्त(release);
	पूर्ण
	atomic_dec(&qdev->release_count);
पूर्ण

अटल पूर्णांक qxl_release_bo_alloc(काष्ठा qxl_device *qdev,
				काष्ठा qxl_bo **bo,
				u32 priority)
अणु
	/* pin releases bo's they are too messy to evict */
	वापस qxl_bo_create(qdev, PAGE_SIZE, false, true,
			     QXL_GEM_DOMAIN_VRAM, priority, शून्य, bo);
पूर्ण

पूर्णांक qxl_release_list_add(काष्ठा qxl_release *release, काष्ठा qxl_bo *bo)
अणु
	काष्ठा qxl_bo_list *entry;

	list_क्रम_each_entry(entry, &release->bos, tv.head) अणु
		अगर (entry->tv.bo == &bo->tbo)
			वापस 0;
	पूर्ण

	entry = kदो_स्मृति(माप(काष्ठा qxl_bo_list), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	qxl_bo_ref(bo);
	entry->tv.bo = &bo->tbo;
	entry->tv.num_shared = 0;
	list_add_tail(&entry->tv.head, &release->bos);
	वापस 0;
पूर्ण

अटल पूर्णांक qxl_release_validate_bo(काष्ठा qxl_bo *bo)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु true, false पूर्ण;
	पूर्णांक ret;

	अगर (!bo->tbo.pin_count) अणु
		qxl_tपंचांग_placement_from_करोमुख्य(bo, bo->type);
		ret = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = dma_resv_reserve_shared(bo->tbo.base.resv, 1);
	अगर (ret)
		वापस ret;

	/* allocate a surface क्रम reserved + validated buffers */
	ret = qxl_bo_check_id(to_qxl(bo->tbo.base.dev), bo);
	अगर (ret)
		वापस ret;
	वापस 0;
पूर्ण

पूर्णांक qxl_release_reserve_list(काष्ठा qxl_release *release, bool no_पूर्णांकr)
अणु
	पूर्णांक ret;
	काष्ठा qxl_bo_list *entry;

	/* अगर only one object on the release its the release itself
	   since these objects are pinned no need to reserve */
	अगर (list_is_singular(&release->bos))
		वापस 0;

	ret = tपंचांग_eu_reserve_buffers(&release->ticket, &release->bos,
				     !no_पूर्णांकr, शून्य);
	अगर (ret)
		वापस ret;

	list_क्रम_each_entry(entry, &release->bos, tv.head) अणु
		काष्ठा qxl_bo *bo = to_qxl_bo(entry->tv.bo);

		ret = qxl_release_validate_bo(bo);
		अगर (ret) अणु
			tपंचांग_eu_backoff_reservation(&release->ticket, &release->bos);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम qxl_release_backoff_reserve_list(काष्ठा qxl_release *release)
अणु
	/* अगर only one object on the release its the release itself
	   since these objects are pinned no need to reserve */
	अगर (list_is_singular(&release->bos))
		वापस;

	tपंचांग_eu_backoff_reservation(&release->ticket, &release->bos);
पूर्ण

पूर्णांक qxl_alloc_surface_release_reserved(काष्ठा qxl_device *qdev,
				       क्रमागत qxl_surface_cmd_type surface_cmd_type,
				       काष्ठा qxl_release *create_rel,
				       काष्ठा qxl_release **release)
अणु
	अगर (surface_cmd_type == QXL_SURFACE_CMD_DESTROY && create_rel) अणु
		पूर्णांक idr_ret;
		काष्ठा qxl_bo *bo;
		जोड़ qxl_release_info *info;

		/* stash the release after the create command */
		idr_ret = qxl_release_alloc(qdev, QXL_RELEASE_SURFACE_CMD, release);
		अगर (idr_ret < 0)
			वापस idr_ret;
		bo = create_rel->release_bo;

		(*release)->release_bo = bo;
		(*release)->release_offset = create_rel->release_offset + 64;

		qxl_release_list_add(*release, bo);

		info = qxl_release_map(qdev, *release);
		info->id = idr_ret;
		qxl_release_unmap(qdev, *release, info);
		वापस 0;
	पूर्ण

	वापस qxl_alloc_release_reserved(qdev, माप(काष्ठा qxl_surface_cmd),
					 QXL_RELEASE_SURFACE_CMD, release, शून्य);
पूर्ण

पूर्णांक qxl_alloc_release_reserved(काष्ठा qxl_device *qdev, अचिन्हित दीर्घ size,
				       पूर्णांक type, काष्ठा qxl_release **release,
				       काष्ठा qxl_bo **rbo)
अणु
	काष्ठा qxl_bo *bo, *मुक्त_bo = शून्य;
	पूर्णांक idr_ret;
	पूर्णांक ret = 0;
	जोड़ qxl_release_info *info;
	पूर्णांक cur_idx;
	u32 priority;

	अगर (type == QXL_RELEASE_DRAWABLE) अणु
		cur_idx = 0;
		priority = 0;
	पूर्ण अन्यथा अगर (type == QXL_RELEASE_SURFACE_CMD) अणु
		cur_idx = 1;
		priority = 1;
	पूर्ण अन्यथा अगर (type == QXL_RELEASE_CURSOR_CMD) अणु
		cur_idx = 2;
		priority = 1;
	पूर्ण
	अन्यथा अणु
		DRM_ERROR("got illegal type: %d\n", type);
		वापस -EINVAL;
	पूर्ण

	idr_ret = qxl_release_alloc(qdev, type, release);
	अगर (idr_ret < 0) अणु
		अगर (rbo)
			*rbo = शून्य;
		वापस idr_ret;
	पूर्ण
	atomic_inc(&qdev->release_count);

	mutex_lock(&qdev->release_mutex);
	अगर (qdev->current_release_bo_offset[cur_idx] + 1 >= releases_per_bo[cur_idx]) अणु
		मुक्त_bo = qdev->current_release_bo[cur_idx];
		qdev->current_release_bo_offset[cur_idx] = 0;
		qdev->current_release_bo[cur_idx] = शून्य;
	पूर्ण
	अगर (!qdev->current_release_bo[cur_idx]) अणु
		ret = qxl_release_bo_alloc(qdev, &qdev->current_release_bo[cur_idx], priority);
		अगर (ret) अणु
			mutex_unlock(&qdev->release_mutex);
			अगर (मुक्त_bo) अणु
				qxl_bo_unpin(मुक्त_bo);
				qxl_bo_unref(&मुक्त_bo);
			पूर्ण
			qxl_release_मुक्त(qdev, *release);
			वापस ret;
		पूर्ण
	पूर्ण

	bo = qxl_bo_ref(qdev->current_release_bo[cur_idx]);

	(*release)->release_bo = bo;
	(*release)->release_offset = qdev->current_release_bo_offset[cur_idx] * release_size_per_bo[cur_idx];
	qdev->current_release_bo_offset[cur_idx]++;

	अगर (rbo)
		*rbo = bo;

	mutex_unlock(&qdev->release_mutex);
	अगर (मुक्त_bo) अणु
		qxl_bo_unpin(मुक्त_bo);
		qxl_bo_unref(&मुक्त_bo);
	पूर्ण

	ret = qxl_release_list_add(*release, bo);
	qxl_bo_unref(&bo);
	अगर (ret) अणु
		qxl_release_मुक्त(qdev, *release);
		वापस ret;
	पूर्ण

	info = qxl_release_map(qdev, *release);
	info->id = idr_ret;
	qxl_release_unmap(qdev, *release, info);

	वापस ret;
पूर्ण

काष्ठा qxl_release *qxl_release_from_id_locked(काष्ठा qxl_device *qdev,
						   uपूर्णांक64_t id)
अणु
	काष्ठा qxl_release *release;

	spin_lock(&qdev->release_idr_lock);
	release = idr_find(&qdev->release_idr, id);
	spin_unlock(&qdev->release_idr_lock);
	अगर (!release) अणु
		DRM_ERROR("failed to find id in release_idr\n");
		वापस शून्य;
	पूर्ण

	वापस release;
पूर्ण

जोड़ qxl_release_info *qxl_release_map(काष्ठा qxl_device *qdev,
					काष्ठा qxl_release *release)
अणु
	व्योम *ptr;
	जोड़ qxl_release_info *info;
	काष्ठा qxl_bo *bo = release->release_bo;

	ptr = qxl_bo_kmap_atomic_page(qdev, bo, release->release_offset & PAGE_MASK);
	अगर (!ptr)
		वापस शून्य;
	info = ptr + (release->release_offset & ~PAGE_MASK);
	वापस info;
पूर्ण

व्योम qxl_release_unmap(काष्ठा qxl_device *qdev,
		       काष्ठा qxl_release *release,
		       जोड़ qxl_release_info *info)
अणु
	काष्ठा qxl_bo *bo = release->release_bo;
	व्योम *ptr;

	ptr = ((व्योम *)info) - (release->release_offset & ~PAGE_MASK);
	qxl_bo_kunmap_atomic_page(qdev, bo, ptr);
पूर्ण

व्योम qxl_release_fence_buffer_objects(काष्ठा qxl_release *release)
अणु
	काष्ठा tपंचांग_buffer_object *bo;
	काष्ठा tपंचांग_device *bdev;
	काष्ठा tपंचांग_validate_buffer *entry;
	काष्ठा qxl_device *qdev;

	/* अगर only one object on the release its the release itself
	   since these objects are pinned no need to reserve */
	अगर (list_is_singular(&release->bos) || list_empty(&release->bos))
		वापस;

	bo = list_first_entry(&release->bos, काष्ठा tपंचांग_validate_buffer, head)->bo;
	bdev = bo->bdev;
	qdev = container_of(bdev, काष्ठा qxl_device, mman.bdev);

	/*
	 * Since we never really allocated a context and we करोn't want to conflict,
	 * set the highest bits. This will अवरोध अगर we really allow exporting of dma-bufs.
	 */
	dma_fence_init(&release->base, &qxl_fence_ops, &qdev->release_lock,
		       release->id | 0xf0000000, release->base.seqno);
	trace_dma_fence_emit(&release->base);

	list_क्रम_each_entry(entry, &release->bos, head) अणु
		bo = entry->bo;

		dma_resv_add_shared_fence(bo->base.resv, &release->base);
		tपंचांग_bo_move_to_lru_tail_unlocked(bo);
		dma_resv_unlock(bo->base.resv);
	पूर्ण
	ww_acquire_fini(&release->ticket);
पूर्ण

