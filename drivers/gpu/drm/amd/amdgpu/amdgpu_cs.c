<शैली गुरु>
/*
 * Copyright 2008 Jerome Glisse.
 * All Rights Reserved.
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
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Jerome Glisse <glisse@मुक्तdesktop.org>
 */

#समावेश <linux/file.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sync_file.h>
#समावेश <linux/dma-buf.h>

#समावेश <drm/amdgpu_drm.h>
#समावेश <drm/drm_syncobj.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_trace.h"
#समावेश "amdgpu_gmc.h"
#समावेश "amdgpu_gem.h"
#समावेश "amdgpu_ras.h"

अटल पूर्णांक amdgpu_cs_user_fence_chunk(काष्ठा amdgpu_cs_parser *p,
				      काष्ठा drm_amdgpu_cs_chunk_fence *data,
				      uपूर्णांक32_t *offset)
अणु
	काष्ठा drm_gem_object *gobj;
	काष्ठा amdgpu_bo *bo;
	अचिन्हित दीर्घ size;
	पूर्णांक r;

	gobj = drm_gem_object_lookup(p->filp, data->handle);
	अगर (gobj == शून्य)
		वापस -EINVAL;

	bo = amdgpu_bo_ref(gem_to_amdgpu_bo(gobj));
	p->uf_entry.priority = 0;
	p->uf_entry.tv.bo = &bo->tbo;
	/* One क्रम TTM and one क्रम the CS job */
	p->uf_entry.tv.num_shared = 2;

	drm_gem_object_put(gobj);

	size = amdgpu_bo_size(bo);
	अगर (size != PAGE_SIZE || (data->offset + 8) > size) अणु
		r = -EINVAL;
		जाओ error_unref;
	पूर्ण

	अगर (amdgpu_tपंचांग_tt_get_usermm(bo->tbo.tपंचांग)) अणु
		r = -EINVAL;
		जाओ error_unref;
	पूर्ण

	*offset = data->offset;

	वापस 0;

error_unref:
	amdgpu_bo_unref(&bo);
	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_cs_bo_handles_chunk(काष्ठा amdgpu_cs_parser *p,
				      काष्ठा drm_amdgpu_bo_list_in *data)
अणु
	पूर्णांक r;
	काष्ठा drm_amdgpu_bo_list_entry *info = शून्य;

	r = amdgpu_bo_create_list_entry_array(data, &info);
	अगर (r)
		वापस r;

	r = amdgpu_bo_list_create(p->adev, p->filp, info, data->bo_number,
				  &p->bo_list);
	अगर (r)
		जाओ error_मुक्त;

	kvमुक्त(info);
	वापस 0;

error_मुक्त:
	kvमुक्त(info);

	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_cs_parser_init(काष्ठा amdgpu_cs_parser *p, जोड़ drm_amdgpu_cs *cs)
अणु
	काष्ठा amdgpu_fpriv *fpriv = p->filp->driver_priv;
	काष्ठा amdgpu_vm *vm = &fpriv->vm;
	uपूर्णांक64_t *chunk_array_user;
	uपूर्णांक64_t *chunk_array;
	अचिन्हित size, num_ibs = 0;
	uपूर्णांक32_t uf_offset = 0;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (cs->in.num_chunks == 0)
		वापस 0;

	chunk_array = kvदो_स्मृति_array(cs->in.num_chunks, माप(uपूर्णांक64_t), GFP_KERNEL);
	अगर (!chunk_array)
		वापस -ENOMEM;

	p->ctx = amdgpu_ctx_get(fpriv, cs->in.ctx_id);
	अगर (!p->ctx) अणु
		ret = -EINVAL;
		जाओ मुक्त_chunk;
	पूर्ण

	mutex_lock(&p->ctx->lock);

	/* skip guilty context job */
	अगर (atomic_पढ़ो(&p->ctx->guilty) == 1) अणु
		ret = -ECANCELED;
		जाओ मुक्त_chunk;
	पूर्ण

	/* get chunks */
	chunk_array_user = u64_to_user_ptr(cs->in.chunks);
	अगर (copy_from_user(chunk_array, chunk_array_user,
			   माप(uपूर्णांक64_t)*cs->in.num_chunks)) अणु
		ret = -EFAULT;
		जाओ मुक्त_chunk;
	पूर्ण

	p->nchunks = cs->in.num_chunks;
	p->chunks = kvदो_स्मृति_array(p->nchunks, माप(काष्ठा amdgpu_cs_chunk),
			    GFP_KERNEL);
	अगर (!p->chunks) अणु
		ret = -ENOMEM;
		जाओ मुक्त_chunk;
	पूर्ण

	क्रम (i = 0; i < p->nchunks; i++) अणु
		काष्ठा drm_amdgpu_cs_chunk __user **chunk_ptr = शून्य;
		काष्ठा drm_amdgpu_cs_chunk user_chunk;
		uपूर्णांक32_t __user *cdata;

		chunk_ptr = u64_to_user_ptr(chunk_array[i]);
		अगर (copy_from_user(&user_chunk, chunk_ptr,
				       माप(काष्ठा drm_amdgpu_cs_chunk))) अणु
			ret = -EFAULT;
			i--;
			जाओ मुक्त_partial_kdata;
		पूर्ण
		p->chunks[i].chunk_id = user_chunk.chunk_id;
		p->chunks[i].length_dw = user_chunk.length_dw;

		size = p->chunks[i].length_dw;
		cdata = u64_to_user_ptr(user_chunk.chunk_data);

		p->chunks[i].kdata = kvदो_स्मृति_array(size, माप(uपूर्णांक32_t), GFP_KERNEL);
		अगर (p->chunks[i].kdata == शून्य) अणु
			ret = -ENOMEM;
			i--;
			जाओ मुक्त_partial_kdata;
		पूर्ण
		size *= माप(uपूर्णांक32_t);
		अगर (copy_from_user(p->chunks[i].kdata, cdata, size)) अणु
			ret = -EFAULT;
			जाओ मुक्त_partial_kdata;
		पूर्ण

		चयन (p->chunks[i].chunk_id) अणु
		हाल AMDGPU_CHUNK_ID_IB:
			++num_ibs;
			अवरोध;

		हाल AMDGPU_CHUNK_ID_FENCE:
			size = माप(काष्ठा drm_amdgpu_cs_chunk_fence);
			अगर (p->chunks[i].length_dw * माप(uपूर्णांक32_t) < size) अणु
				ret = -EINVAL;
				जाओ मुक्त_partial_kdata;
			पूर्ण

			ret = amdgpu_cs_user_fence_chunk(p, p->chunks[i].kdata,
							 &uf_offset);
			अगर (ret)
				जाओ मुक्त_partial_kdata;

			अवरोध;

		हाल AMDGPU_CHUNK_ID_BO_HANDLES:
			size = माप(काष्ठा drm_amdgpu_bo_list_in);
			अगर (p->chunks[i].length_dw * माप(uपूर्णांक32_t) < size) अणु
				ret = -EINVAL;
				जाओ मुक्त_partial_kdata;
			पूर्ण

			ret = amdgpu_cs_bo_handles_chunk(p, p->chunks[i].kdata);
			अगर (ret)
				जाओ मुक्त_partial_kdata;

			अवरोध;

		हाल AMDGPU_CHUNK_ID_DEPENDENCIES:
		हाल AMDGPU_CHUNK_ID_SYNCOBJ_IN:
		हाल AMDGPU_CHUNK_ID_SYNCOBJ_OUT:
		हाल AMDGPU_CHUNK_ID_SCHEDULED_DEPENDENCIES:
		हाल AMDGPU_CHUNK_ID_SYNCOBJ_TIMELINE_WAIT:
		हाल AMDGPU_CHUNK_ID_SYNCOBJ_TIMELINE_SIGNAL:
			अवरोध;

		शेष:
			ret = -EINVAL;
			जाओ मुक्त_partial_kdata;
		पूर्ण
	पूर्ण

	ret = amdgpu_job_alloc(p->adev, num_ibs, &p->job, vm);
	अगर (ret)
		जाओ मुक्त_all_kdata;

	अगर (p->ctx->vram_lost_counter != p->job->vram_lost_counter) अणु
		ret = -ECANCELED;
		जाओ मुक्त_all_kdata;
	पूर्ण

	अगर (p->uf_entry.tv.bo)
		p->job->uf_addr = uf_offset;
	kvमुक्त(chunk_array);

	/* Use this opportunity to fill in task info क्रम the vm */
	amdgpu_vm_set_task_info(vm);

	वापस 0;

मुक्त_all_kdata:
	i = p->nchunks - 1;
मुक्त_partial_kdata:
	क्रम (; i >= 0; i--)
		kvमुक्त(p->chunks[i].kdata);
	kvमुक्त(p->chunks);
	p->chunks = शून्य;
	p->nchunks = 0;
मुक्त_chunk:
	kvमुक्त(chunk_array);

	वापस ret;
पूर्ण

/* Convert microseconds to bytes. */
अटल u64 us_to_bytes(काष्ठा amdgpu_device *adev, s64 us)
अणु
	अगर (us <= 0 || !adev->mm_stats.log2_max_MBps)
		वापस 0;

	/* Since accum_us is incremented by a million per second, just
	 * multiply it by the number of MB/s to get the number of bytes.
	 */
	वापस us << adev->mm_stats.log2_max_MBps;
पूर्ण

अटल s64 bytes_to_us(काष्ठा amdgpu_device *adev, u64 bytes)
अणु
	अगर (!adev->mm_stats.log2_max_MBps)
		वापस 0;

	वापस bytes >> adev->mm_stats.log2_max_MBps;
पूर्ण

/* Returns how many bytes TTM can move right now. If no bytes can be moved,
 * it वापसs 0. If it वापसs non-zero, it's OK to move at least one buffer,
 * which means it can go over the threshold once. If that happens, the driver
 * will be in debt and no other buffer migrations can be करोne until that debt
 * is repaid.
 *
 * This approach allows moving a buffer of any size (it's important to allow
 * that).
 *
 * The currency is simply समय in microseconds and it increases as the घड़ी
 * ticks. The accumulated microseconds (us) are converted to bytes and
 * वापसed.
 */
अटल व्योम amdgpu_cs_get_threshold_क्रम_moves(काष्ठा amdgpu_device *adev,
					      u64 *max_bytes,
					      u64 *max_vis_bytes)
अणु
	s64 समय_us, increment_us;
	u64 मुक्त_vram, total_vram, used_vram;
	काष्ठा tपंचांग_resource_manager *vram_man = tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_VRAM);
	/* Allow a maximum of 200 accumulated ms. This is basically per-IB
	 * throttling.
	 *
	 * It means that in order to get full max MBps, at least 5 IBs per
	 * second must be submitted and not more than 200ms apart from each
	 * other.
	 */
	स्थिर s64 us_upper_bound = 200000;

	अगर (!adev->mm_stats.log2_max_MBps) अणु
		*max_bytes = 0;
		*max_vis_bytes = 0;
		वापस;
	पूर्ण

	total_vram = adev->gmc.real_vram_size - atomic64_पढ़ो(&adev->vram_pin_size);
	used_vram = amdgpu_vram_mgr_usage(vram_man);
	मुक्त_vram = used_vram >= total_vram ? 0 : total_vram - used_vram;

	spin_lock(&adev->mm_stats.lock);

	/* Increase the amount of accumulated us. */
	समय_us = kसमय_प्रकारo_us(kसमय_get());
	increment_us = समय_us - adev->mm_stats.last_update_us;
	adev->mm_stats.last_update_us = समय_us;
	adev->mm_stats.accum_us = min(adev->mm_stats.accum_us + increment_us,
				      us_upper_bound);

	/* This prevents the लघु period of low perक्रमmance when the VRAM
	 * usage is low and the driver is in debt or करोesn't have enough
	 * accumulated us to fill VRAM quickly.
	 *
	 * The situation can occur in these हालs:
	 * - a lot of VRAM is मुक्तd by userspace
	 * - the presence of a big buffer causes a lot of evictions
	 *   (solution: split buffers पूर्णांकo smaller ones)
	 *
	 * If 128 MB or 1/8th of VRAM is मुक्त, start filling it now by setting
	 * accum_us to a positive number.
	 */
	अगर (मुक्त_vram >= 128 * 1024 * 1024 || मुक्त_vram >= total_vram / 8) अणु
		s64 min_us;

		/* Be more aggresive on dGPUs. Try to fill a portion of मुक्त
		 * VRAM now.
		 */
		अगर (!(adev->flags & AMD_IS_APU))
			min_us = bytes_to_us(adev, मुक्त_vram / 4);
		अन्यथा
			min_us = 0; /* Reset accum_us on APUs. */

		adev->mm_stats.accum_us = max(min_us, adev->mm_stats.accum_us);
	पूर्ण

	/* This is set to 0 अगर the driver is in debt to disallow (optional)
	 * buffer moves.
	 */
	*max_bytes = us_to_bytes(adev, adev->mm_stats.accum_us);

	/* Do the same क्रम visible VRAM अगर half of it is मुक्त */
	अगर (!amdgpu_gmc_vram_full_visible(&adev->gmc)) अणु
		u64 total_vis_vram = adev->gmc.visible_vram_size;
		u64 used_vis_vram =
		  amdgpu_vram_mgr_vis_usage(vram_man);

		अगर (used_vis_vram < total_vis_vram) अणु
			u64 मुक्त_vis_vram = total_vis_vram - used_vis_vram;
			adev->mm_stats.accum_us_vis = min(adev->mm_stats.accum_us_vis +
							  increment_us, us_upper_bound);

			अगर (मुक्त_vis_vram >= total_vis_vram / 2)
				adev->mm_stats.accum_us_vis =
					max(bytes_to_us(adev, मुक्त_vis_vram / 2),
					    adev->mm_stats.accum_us_vis);
		पूर्ण

		*max_vis_bytes = us_to_bytes(adev, adev->mm_stats.accum_us_vis);
	पूर्ण अन्यथा अणु
		*max_vis_bytes = 0;
	पूर्ण

	spin_unlock(&adev->mm_stats.lock);
पूर्ण

/* Report how many bytes have really been moved क्रम the last command
 * submission. This can result in a debt that can stop buffer migrations
 * temporarily.
 */
व्योम amdgpu_cs_report_moved_bytes(काष्ठा amdgpu_device *adev, u64 num_bytes,
				  u64 num_vis_bytes)
अणु
	spin_lock(&adev->mm_stats.lock);
	adev->mm_stats.accum_us -= bytes_to_us(adev, num_bytes);
	adev->mm_stats.accum_us_vis -= bytes_to_us(adev, num_vis_bytes);
	spin_unlock(&adev->mm_stats.lock);
पूर्ण

अटल पूर्णांक amdgpu_cs_bo_validate(काष्ठा amdgpu_cs_parser *p,
				 काष्ठा amdgpu_bo *bo)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = true,
		.no_रुको_gpu = false,
		.resv = bo->tbo.base.resv
	पूर्ण;
	uपूर्णांक32_t करोमुख्य;
	पूर्णांक r;

	अगर (bo->tbo.pin_count)
		वापस 0;

	/* Don't move this buffer अगर we have depleted our allowance
	 * to move it. Don't move anything अगर the threshold is zero.
	 */
	अगर (p->bytes_moved < p->bytes_moved_threshold &&
	    (!bo->tbo.base.dma_buf ||
	    list_empty(&bo->tbo.base.dma_buf->attachments))) अणु
		अगर (!amdgpu_gmc_vram_full_visible(&adev->gmc) &&
		    (bo->flags & AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED)) अणु
			/* And करोn't move a CPU_ACCESS_REQUIRED BO to limited
			 * visible VRAM अगर we've depleted our allowance to करो
			 * that.
			 */
			अगर (p->bytes_moved_vis < p->bytes_moved_vis_threshold)
				करोमुख्य = bo->preferred_करोमुख्यs;
			अन्यथा
				करोमुख्य = bo->allowed_करोमुख्यs;
		पूर्ण अन्यथा अणु
			करोमुख्य = bo->preferred_करोमुख्यs;
		पूर्ण
	पूर्ण अन्यथा अणु
		करोमुख्य = bo->allowed_करोमुख्यs;
	पूर्ण

retry:
	amdgpu_bo_placement_from_करोमुख्य(bo, करोमुख्य);
	r = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);

	p->bytes_moved += ctx.bytes_moved;
	अगर (!amdgpu_gmc_vram_full_visible(&adev->gmc) &&
	    amdgpu_bo_in_cpu_visible_vram(bo))
		p->bytes_moved_vis += ctx.bytes_moved;

	अगर (unlikely(r == -ENOMEM) && करोमुख्य != bo->allowed_करोमुख्यs) अणु
		करोमुख्य = bo->allowed_करोमुख्यs;
		जाओ retry;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_cs_validate(व्योम *param, काष्ठा amdgpu_bo *bo)
अणु
	काष्ठा amdgpu_cs_parser *p = param;
	पूर्णांक r;

	r = amdgpu_cs_bo_validate(p, bo);
	अगर (r)
		वापस r;

	अगर (bo->shaकरोw)
		r = amdgpu_cs_bo_validate(p, bo->shaकरोw);

	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_cs_list_validate(काष्ठा amdgpu_cs_parser *p,
			    काष्ठा list_head *validated)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु true, false पूर्ण;
	काष्ठा amdgpu_bo_list_entry *lobj;
	पूर्णांक r;

	list_क्रम_each_entry(lobj, validated, tv.head) अणु
		काष्ठा amdgpu_bo *bo = tपंचांग_to_amdgpu_bo(lobj->tv.bo);
		काष्ठा mm_काष्ठा *usermm;

		usermm = amdgpu_tपंचांग_tt_get_usermm(bo->tbo.tपंचांग);
		अगर (usermm && usermm != current->mm)
			वापस -EPERM;

		अगर (amdgpu_tपंचांग_tt_is_userptr(bo->tbo.tपंचांग) &&
		    lobj->user_invalidated && lobj->user_pages) अणु
			amdgpu_bo_placement_from_करोमुख्य(bo,
							AMDGPU_GEM_DOMAIN_CPU);
			r = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
			अगर (r)
				वापस r;

			amdgpu_tपंचांग_tt_set_user_pages(bo->tbo.tपंचांग,
						     lobj->user_pages);
		पूर्ण

		r = amdgpu_cs_validate(p, bo);
		अगर (r)
			वापस r;

		kvमुक्त(lobj->user_pages);
		lobj->user_pages = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_cs_parser_bos(काष्ठा amdgpu_cs_parser *p,
				जोड़ drm_amdgpu_cs *cs)
अणु
	काष्ठा amdgpu_fpriv *fpriv = p->filp->driver_priv;
	काष्ठा amdgpu_vm *vm = &fpriv->vm;
	काष्ठा amdgpu_bo_list_entry *e;
	काष्ठा list_head duplicates;
	काष्ठा amdgpu_bo *gds;
	काष्ठा amdgpu_bo *gws;
	काष्ठा amdgpu_bo *oa;
	पूर्णांक r;

	INIT_LIST_HEAD(&p->validated);

	/* p->bo_list could alपढ़ोy be asचिन्हित अगर AMDGPU_CHUNK_ID_BO_HANDLES is present */
	अगर (cs->in.bo_list_handle) अणु
		अगर (p->bo_list)
			वापस -EINVAL;

		r = amdgpu_bo_list_get(fpriv, cs->in.bo_list_handle,
				       &p->bo_list);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अगर (!p->bo_list) अणु
		/* Create a empty bo_list when no handle is provided */
		r = amdgpu_bo_list_create(p->adev, p->filp, शून्य, 0,
					  &p->bo_list);
		अगर (r)
			वापस r;
	पूर्ण

	/* One क्रम TTM and one क्रम the CS job */
	amdgpu_bo_list_क्रम_each_entry(e, p->bo_list)
		e->tv.num_shared = 2;

	amdgpu_bo_list_get_list(p->bo_list, &p->validated);

	INIT_LIST_HEAD(&duplicates);
	amdgpu_vm_get_pd_bo(&fpriv->vm, &p->validated, &p->vm_pd);

	अगर (p->uf_entry.tv.bo && !tपंचांग_to_amdgpu_bo(p->uf_entry.tv.bo)->parent)
		list_add(&p->uf_entry.tv.head, &p->validated);

	/* Get userptr backing pages. If pages are updated after रेजिस्टरed
	 * in amdgpu_gem_userptr_ioctl(), amdgpu_cs_list_validate() will करो
	 * amdgpu_tपंचांग_backend_bind() to flush and invalidate new pages
	 */
	amdgpu_bo_list_क्रम_each_userptr_entry(e, p->bo_list) अणु
		काष्ठा amdgpu_bo *bo = tपंचांग_to_amdgpu_bo(e->tv.bo);
		bool userpage_invalidated = false;
		पूर्णांक i;

		e->user_pages = kvदो_स्मृति_array(bo->tbo.tपंचांग->num_pages,
					माप(काष्ठा page *),
					GFP_KERNEL | __GFP_ZERO);
		अगर (!e->user_pages) अणु
			DRM_ERROR("kvmalloc_array failure\n");
			वापस -ENOMEM;
		पूर्ण

		r = amdgpu_tपंचांग_tt_get_user_pages(bo, e->user_pages);
		अगर (r) अणु
			kvमुक्त(e->user_pages);
			e->user_pages = शून्य;
			वापस r;
		पूर्ण

		क्रम (i = 0; i < bo->tbo.tपंचांग->num_pages; i++) अणु
			अगर (bo->tbo.tपंचांग->pages[i] != e->user_pages[i]) अणु
				userpage_invalidated = true;
				अवरोध;
			पूर्ण
		पूर्ण
		e->user_invalidated = userpage_invalidated;
	पूर्ण

	r = tपंचांग_eu_reserve_buffers(&p->ticket, &p->validated, true,
				   &duplicates);
	अगर (unlikely(r != 0)) अणु
		अगर (r != -ERESTARTSYS)
			DRM_ERROR("ttm_eu_reserve_buffers failed.\n");
		जाओ out;
	पूर्ण

	amdgpu_cs_get_threshold_क्रम_moves(p->adev, &p->bytes_moved_threshold,
					  &p->bytes_moved_vis_threshold);
	p->bytes_moved = 0;
	p->bytes_moved_vis = 0;

	r = amdgpu_vm_validate_pt_bos(p->adev, &fpriv->vm,
				      amdgpu_cs_validate, p);
	अगर (r) अणु
		DRM_ERROR("amdgpu_vm_validate_pt_bos() failed.\n");
		जाओ error_validate;
	पूर्ण

	r = amdgpu_cs_list_validate(p, &duplicates);
	अगर (r)
		जाओ error_validate;

	r = amdgpu_cs_list_validate(p, &p->validated);
	अगर (r)
		जाओ error_validate;

	amdgpu_cs_report_moved_bytes(p->adev, p->bytes_moved,
				     p->bytes_moved_vis);

	gds = p->bo_list->gds_obj;
	gws = p->bo_list->gws_obj;
	oa = p->bo_list->oa_obj;

	amdgpu_bo_list_क्रम_each_entry(e, p->bo_list) अणु
		काष्ठा amdgpu_bo *bo = tपंचांग_to_amdgpu_bo(e->tv.bo);

		/* Make sure we use the exclusive slot क्रम shared BOs */
		अगर (bo->prime_shared_count)
			e->tv.num_shared = 0;
		e->bo_va = amdgpu_vm_bo_find(vm, bo);
	पूर्ण

	अगर (gds) अणु
		p->job->gds_base = amdgpu_bo_gpu_offset(gds) >> PAGE_SHIFT;
		p->job->gds_size = amdgpu_bo_size(gds) >> PAGE_SHIFT;
	पूर्ण
	अगर (gws) अणु
		p->job->gws_base = amdgpu_bo_gpu_offset(gws) >> PAGE_SHIFT;
		p->job->gws_size = amdgpu_bo_size(gws) >> PAGE_SHIFT;
	पूर्ण
	अगर (oa) अणु
		p->job->oa_base = amdgpu_bo_gpu_offset(oa) >> PAGE_SHIFT;
		p->job->oa_size = amdgpu_bo_size(oa) >> PAGE_SHIFT;
	पूर्ण

	अगर (!r && p->uf_entry.tv.bo) अणु
		काष्ठा amdgpu_bo *uf = tपंचांग_to_amdgpu_bo(p->uf_entry.tv.bo);

		r = amdgpu_tपंचांग_alloc_gart(&uf->tbo);
		p->job->uf_addr += amdgpu_bo_gpu_offset(uf);
	पूर्ण

error_validate:
	अगर (r)
		tपंचांग_eu_backoff_reservation(&p->ticket, &p->validated);
out:
	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_cs_sync_rings(काष्ठा amdgpu_cs_parser *p)
अणु
	काष्ठा amdgpu_fpriv *fpriv = p->filp->driver_priv;
	काष्ठा amdgpu_bo_list_entry *e;
	पूर्णांक r;

	list_क्रम_each_entry(e, &p->validated, tv.head) अणु
		काष्ठा amdgpu_bo *bo = tपंचांग_to_amdgpu_bo(e->tv.bo);
		काष्ठा dma_resv *resv = bo->tbo.base.resv;
		क्रमागत amdgpu_sync_mode sync_mode;

		sync_mode = amdgpu_bo_explicit_sync(bo) ?
			AMDGPU_SYNC_EXPLICIT : AMDGPU_SYNC_NE_OWNER;
		r = amdgpu_sync_resv(p->adev, &p->job->sync, resv, sync_mode,
				     &fpriv->vm);
		अगर (r)
			वापस r;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * cs_parser_fini() - clean parser states
 * @parser:	parser काष्ठाure holding parsing context.
 * @error:	error number
 * @backoff:	indicator to backoff the reservation
 *
 * If error is set than unvalidate buffer, otherwise just मुक्त memory
 * used by parsing context.
 **/
अटल व्योम amdgpu_cs_parser_fini(काष्ठा amdgpu_cs_parser *parser, पूर्णांक error,
				  bool backoff)
अणु
	अचिन्हित i;

	अगर (error && backoff)
		tपंचांग_eu_backoff_reservation(&parser->ticket,
					   &parser->validated);

	क्रम (i = 0; i < parser->num_post_deps; i++) अणु
		drm_syncobj_put(parser->post_deps[i].syncobj);
		kमुक्त(parser->post_deps[i].chain);
	पूर्ण
	kमुक्त(parser->post_deps);

	dma_fence_put(parser->fence);

	अगर (parser->ctx) अणु
		mutex_unlock(&parser->ctx->lock);
		amdgpu_ctx_put(parser->ctx);
	पूर्ण
	अगर (parser->bo_list)
		amdgpu_bo_list_put(parser->bo_list);

	क्रम (i = 0; i < parser->nchunks; i++)
		kvमुक्त(parser->chunks[i].kdata);
	kvमुक्त(parser->chunks);
	अगर (parser->job)
		amdgpu_job_मुक्त(parser->job);
	अगर (parser->uf_entry.tv.bo) अणु
		काष्ठा amdgpu_bo *uf = tपंचांग_to_amdgpu_bo(parser->uf_entry.tv.bo);

		amdgpu_bo_unref(&uf);
	पूर्ण
पूर्ण

अटल पूर्णांक amdgpu_cs_vm_handling(काष्ठा amdgpu_cs_parser *p)
अणु
	काष्ठा amdgpu_ring *ring = to_amdgpu_ring(p->entity->rq->sched);
	काष्ठा amdgpu_fpriv *fpriv = p->filp->driver_priv;
	काष्ठा amdgpu_device *adev = p->adev;
	काष्ठा amdgpu_vm *vm = &fpriv->vm;
	काष्ठा amdgpu_bo_list_entry *e;
	काष्ठा amdgpu_bo_va *bo_va;
	काष्ठा amdgpu_bo *bo;
	पूर्णांक r;

	/* Only क्रम UVD/VCE VM emulation */
	अगर (ring->funcs->parse_cs || ring->funcs->patch_cs_in_place) अणु
		अचिन्हित i, j;

		क्रम (i = 0, j = 0; i < p->nchunks && j < p->job->num_ibs; i++) अणु
			काष्ठा drm_amdgpu_cs_chunk_ib *chunk_ib;
			काष्ठा amdgpu_bo_va_mapping *m;
			काष्ठा amdgpu_bo *aobj = शून्य;
			काष्ठा amdgpu_cs_chunk *chunk;
			uपूर्णांक64_t offset, बहु_शुरू;
			काष्ठा amdgpu_ib *ib;
			uपूर्णांक8_t *kptr;

			chunk = &p->chunks[i];
			ib = &p->job->ibs[j];
			chunk_ib = chunk->kdata;

			अगर (chunk->chunk_id != AMDGPU_CHUNK_ID_IB)
				जारी;

			बहु_शुरू = chunk_ib->बहु_शुरू & AMDGPU_GMC_HOLE_MASK;
			r = amdgpu_cs_find_mapping(p, बहु_शुरू, &aobj, &m);
			अगर (r) अणु
				DRM_ERROR("IB va_start is invalid\n");
				वापस r;
			पूर्ण

			अगर ((बहु_शुरू + chunk_ib->ib_bytes) >
			    (m->last + 1) * AMDGPU_GPU_PAGE_SIZE) अणु
				DRM_ERROR("IB va_start+ib_bytes is invalid\n");
				वापस -EINVAL;
			पूर्ण

			/* the IB should be reserved at this poपूर्णांक */
			r = amdgpu_bo_kmap(aobj, (व्योम **)&kptr);
			अगर (r) अणु
				वापस r;
			पूर्ण

			offset = m->start * AMDGPU_GPU_PAGE_SIZE;
			kptr += बहु_शुरू - offset;

			अगर (ring->funcs->parse_cs) अणु
				स_नकल(ib->ptr, kptr, chunk_ib->ib_bytes);
				amdgpu_bo_kunmap(aobj);

				r = amdgpu_ring_parse_cs(ring, p, j);
				अगर (r)
					वापस r;
			पूर्ण अन्यथा अणु
				ib->ptr = (uपूर्णांक32_t *)kptr;
				r = amdgpu_ring_patch_cs_in_place(ring, p, j);
				amdgpu_bo_kunmap(aobj);
				अगर (r)
					वापस r;
			पूर्ण

			j++;
		पूर्ण
	पूर्ण

	अगर (!p->job->vm)
		वापस amdgpu_cs_sync_rings(p);


	r = amdgpu_vm_clear_मुक्तd(adev, vm, शून्य);
	अगर (r)
		वापस r;

	r = amdgpu_vm_bo_update(adev, fpriv->prt_va, false);
	अगर (r)
		वापस r;

	r = amdgpu_sync_vm_fence(&p->job->sync, fpriv->prt_va->last_pt_update);
	अगर (r)
		वापस r;

	अगर (amdgpu_mcbp || amdgpu_sriov_vf(adev)) अणु
		bo_va = fpriv->csa_va;
		BUG_ON(!bo_va);
		r = amdgpu_vm_bo_update(adev, bo_va, false);
		अगर (r)
			वापस r;

		r = amdgpu_sync_vm_fence(&p->job->sync, bo_va->last_pt_update);
		अगर (r)
			वापस r;
	पूर्ण

	amdgpu_bo_list_क्रम_each_entry(e, p->bo_list) अणु
		/* ignore duplicates */
		bo = tपंचांग_to_amdgpu_bo(e->tv.bo);
		अगर (!bo)
			जारी;

		bo_va = e->bo_va;
		अगर (bo_va == शून्य)
			जारी;

		r = amdgpu_vm_bo_update(adev, bo_va, false);
		अगर (r)
			वापस r;

		r = amdgpu_sync_vm_fence(&p->job->sync, bo_va->last_pt_update);
		अगर (r)
			वापस r;
	पूर्ण

	r = amdgpu_vm_handle_moved(adev, vm);
	अगर (r)
		वापस r;

	r = amdgpu_vm_update_pdes(adev, vm, false);
	अगर (r)
		वापस r;

	r = amdgpu_sync_vm_fence(&p->job->sync, vm->last_update);
	अगर (r)
		वापस r;

	p->job->vm_pd_addr = amdgpu_gmc_pd_addr(vm->root.base.bo);

	अगर (amdgpu_vm_debug) अणु
		/* Invalidate all BOs to test क्रम userspace bugs */
		amdgpu_bo_list_क्रम_each_entry(e, p->bo_list) अणु
			काष्ठा amdgpu_bo *bo = tपंचांग_to_amdgpu_bo(e->tv.bo);

			/* ignore duplicates */
			अगर (!bo)
				जारी;

			amdgpu_vm_bo_invalidate(adev, bo, false);
		पूर्ण
	पूर्ण

	वापस amdgpu_cs_sync_rings(p);
पूर्ण

अटल पूर्णांक amdgpu_cs_ib_fill(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_cs_parser *parser)
अणु
	काष्ठा amdgpu_fpriv *fpriv = parser->filp->driver_priv;
	काष्ठा amdgpu_vm *vm = &fpriv->vm;
	पूर्णांक r, ce_preempt = 0, de_preempt = 0;
	काष्ठा amdgpu_ring *ring;
	पूर्णांक i, j;

	क्रम (i = 0, j = 0; i < parser->nchunks && j < parser->job->num_ibs; i++) अणु
		काष्ठा amdgpu_cs_chunk *chunk;
		काष्ठा amdgpu_ib *ib;
		काष्ठा drm_amdgpu_cs_chunk_ib *chunk_ib;
		काष्ठा drm_sched_entity *entity;

		chunk = &parser->chunks[i];
		ib = &parser->job->ibs[j];
		chunk_ib = (काष्ठा drm_amdgpu_cs_chunk_ib *)chunk->kdata;

		अगर (chunk->chunk_id != AMDGPU_CHUNK_ID_IB)
			जारी;

		अगर (chunk_ib->ip_type == AMDGPU_HW_IP_GFX &&
		    (amdgpu_mcbp || amdgpu_sriov_vf(adev))) अणु
			अगर (chunk_ib->flags & AMDGPU_IB_FLAG_PREEMPT) अणु
				अगर (chunk_ib->flags & AMDGPU_IB_FLAG_CE)
					ce_preempt++;
				अन्यथा
					de_preempt++;
			पूर्ण

			/* each GFX command submit allows 0 or 1 IB preemptible क्रम CE & DE */
			अगर (ce_preempt > 1 || de_preempt > 1)
				वापस -EINVAL;
		पूर्ण

		r = amdgpu_ctx_get_entity(parser->ctx, chunk_ib->ip_type,
					  chunk_ib->ip_instance, chunk_ib->ring,
					  &entity);
		अगर (r)
			वापस r;

		अगर (chunk_ib->flags & AMDGPU_IB_FLAG_PREAMBLE)
			parser->job->preamble_status |=
				AMDGPU_PREAMBLE_IB_PRESENT;

		अगर (parser->entity && parser->entity != entity)
			वापस -EINVAL;

		/* Return अगर there is no run queue associated with this entity.
		 * Possibly because of disabled HW IP*/
		अगर (entity->rq == शून्य)
			वापस -EINVAL;

		parser->entity = entity;

		ring = to_amdgpu_ring(entity->rq->sched);
		r =  amdgpu_ib_get(adev, vm, ring->funcs->parse_cs ?
				   chunk_ib->ib_bytes : 0,
				   AMDGPU_IB_POOL_DELAYED, ib);
		अगर (r) अणु
			DRM_ERROR("Failed to get ib !\n");
			वापस r;
		पूर्ण

		ib->gpu_addr = chunk_ib->बहु_शुरू;
		ib->length_dw = chunk_ib->ib_bytes / 4;
		ib->flags = chunk_ib->flags;

		j++;
	पूर्ण

	/* MM engine करोesn't support user fences */
	ring = to_amdgpu_ring(parser->entity->rq->sched);
	अगर (parser->job->uf_addr && ring->funcs->no_user_fence)
		वापस -EINVAL;

	वापस amdgpu_ctx_रुको_prev_fence(parser->ctx, parser->entity);
पूर्ण

अटल पूर्णांक amdgpu_cs_process_fence_dep(काष्ठा amdgpu_cs_parser *p,
				       काष्ठा amdgpu_cs_chunk *chunk)
अणु
	काष्ठा amdgpu_fpriv *fpriv = p->filp->driver_priv;
	अचिन्हित num_deps;
	पूर्णांक i, r;
	काष्ठा drm_amdgpu_cs_chunk_dep *deps;

	deps = (काष्ठा drm_amdgpu_cs_chunk_dep *)chunk->kdata;
	num_deps = chunk->length_dw * 4 /
		माप(काष्ठा drm_amdgpu_cs_chunk_dep);

	क्रम (i = 0; i < num_deps; ++i) अणु
		काष्ठा amdgpu_ctx *ctx;
		काष्ठा drm_sched_entity *entity;
		काष्ठा dma_fence *fence;

		ctx = amdgpu_ctx_get(fpriv, deps[i].ctx_id);
		अगर (ctx == शून्य)
			वापस -EINVAL;

		r = amdgpu_ctx_get_entity(ctx, deps[i].ip_type,
					  deps[i].ip_instance,
					  deps[i].ring, &entity);
		अगर (r) अणु
			amdgpu_ctx_put(ctx);
			वापस r;
		पूर्ण

		fence = amdgpu_ctx_get_fence(ctx, entity, deps[i].handle);
		amdgpu_ctx_put(ctx);

		अगर (IS_ERR(fence))
			वापस PTR_ERR(fence);
		अन्यथा अगर (!fence)
			जारी;

		अगर (chunk->chunk_id == AMDGPU_CHUNK_ID_SCHEDULED_DEPENDENCIES) अणु
			काष्ठा drm_sched_fence *s_fence;
			काष्ठा dma_fence *old = fence;

			s_fence = to_drm_sched_fence(fence);
			fence = dma_fence_get(&s_fence->scheduled);
			dma_fence_put(old);
		पूर्ण

		r = amdgpu_sync_fence(&p->job->sync, fence);
		dma_fence_put(fence);
		अगर (r)
			वापस r;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_syncobj_lookup_and_add_to_sync(काष्ठा amdgpu_cs_parser *p,
						 uपूर्णांक32_t handle, u64 poपूर्णांक,
						 u64 flags)
अणु
	काष्ठा dma_fence *fence;
	पूर्णांक r;

	r = drm_syncobj_find_fence(p->filp, handle, poपूर्णांक, flags, &fence);
	अगर (r) अणु
		DRM_ERROR("syncobj %u failed to find fence @ %llu (%d)!\n",
			  handle, poपूर्णांक, r);
		वापस r;
	पूर्ण

	r = amdgpu_sync_fence(&p->job->sync, fence);
	dma_fence_put(fence);

	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_cs_process_syncobj_in_dep(काष्ठा amdgpu_cs_parser *p,
					    काष्ठा amdgpu_cs_chunk *chunk)
अणु
	काष्ठा drm_amdgpu_cs_chunk_sem *deps;
	अचिन्हित num_deps;
	पूर्णांक i, r;

	deps = (काष्ठा drm_amdgpu_cs_chunk_sem *)chunk->kdata;
	num_deps = chunk->length_dw * 4 /
		माप(काष्ठा drm_amdgpu_cs_chunk_sem);
	क्रम (i = 0; i < num_deps; ++i) अणु
		r = amdgpu_syncobj_lookup_and_add_to_sync(p, deps[i].handle,
							  0, 0);
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक amdgpu_cs_process_syncobj_समयline_in_dep(काष्ठा amdgpu_cs_parser *p,
						     काष्ठा amdgpu_cs_chunk *chunk)
अणु
	काष्ठा drm_amdgpu_cs_chunk_syncobj *syncobj_deps;
	अचिन्हित num_deps;
	पूर्णांक i, r;

	syncobj_deps = (काष्ठा drm_amdgpu_cs_chunk_syncobj *)chunk->kdata;
	num_deps = chunk->length_dw * 4 /
		माप(काष्ठा drm_amdgpu_cs_chunk_syncobj);
	क्रम (i = 0; i < num_deps; ++i) अणु
		r = amdgpu_syncobj_lookup_and_add_to_sync(p,
							  syncobj_deps[i].handle,
							  syncobj_deps[i].poपूर्णांक,
							  syncobj_deps[i].flags);
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_cs_process_syncobj_out_dep(काष्ठा amdgpu_cs_parser *p,
					     काष्ठा amdgpu_cs_chunk *chunk)
अणु
	काष्ठा drm_amdgpu_cs_chunk_sem *deps;
	अचिन्हित num_deps;
	पूर्णांक i;

	deps = (काष्ठा drm_amdgpu_cs_chunk_sem *)chunk->kdata;
	num_deps = chunk->length_dw * 4 /
		माप(काष्ठा drm_amdgpu_cs_chunk_sem);

	अगर (p->post_deps)
		वापस -EINVAL;

	p->post_deps = kदो_स्मृति_array(num_deps, माप(*p->post_deps),
				     GFP_KERNEL);
	p->num_post_deps = 0;

	अगर (!p->post_deps)
		वापस -ENOMEM;


	क्रम (i = 0; i < num_deps; ++i) अणु
		p->post_deps[i].syncobj =
			drm_syncobj_find(p->filp, deps[i].handle);
		अगर (!p->post_deps[i].syncobj)
			वापस -EINVAL;
		p->post_deps[i].chain = शून्य;
		p->post_deps[i].poपूर्णांक = 0;
		p->num_post_deps++;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक amdgpu_cs_process_syncobj_समयline_out_dep(काष्ठा amdgpu_cs_parser *p,
						      काष्ठा amdgpu_cs_chunk *chunk)
अणु
	काष्ठा drm_amdgpu_cs_chunk_syncobj *syncobj_deps;
	अचिन्हित num_deps;
	पूर्णांक i;

	syncobj_deps = (काष्ठा drm_amdgpu_cs_chunk_syncobj *)chunk->kdata;
	num_deps = chunk->length_dw * 4 /
		माप(काष्ठा drm_amdgpu_cs_chunk_syncobj);

	अगर (p->post_deps)
		वापस -EINVAL;

	p->post_deps = kदो_स्मृति_array(num_deps, माप(*p->post_deps),
				     GFP_KERNEL);
	p->num_post_deps = 0;

	अगर (!p->post_deps)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_deps; ++i) अणु
		काष्ठा amdgpu_cs_post_dep *dep = &p->post_deps[i];

		dep->chain = शून्य;
		अगर (syncobj_deps[i].poपूर्णांक) अणु
			dep->chain = kदो_स्मृति(माप(*dep->chain), GFP_KERNEL);
			अगर (!dep->chain)
				वापस -ENOMEM;
		पूर्ण

		dep->syncobj = drm_syncobj_find(p->filp,
						syncobj_deps[i].handle);
		अगर (!dep->syncobj) अणु
			kमुक्त(dep->chain);
			वापस -EINVAL;
		पूर्ण
		dep->poपूर्णांक = syncobj_deps[i].poपूर्णांक;
		p->num_post_deps++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_cs_dependencies(काष्ठा amdgpu_device *adev,
				  काष्ठा amdgpu_cs_parser *p)
अणु
	पूर्णांक i, r;

	क्रम (i = 0; i < p->nchunks; ++i) अणु
		काष्ठा amdgpu_cs_chunk *chunk;

		chunk = &p->chunks[i];

		चयन (chunk->chunk_id) अणु
		हाल AMDGPU_CHUNK_ID_DEPENDENCIES:
		हाल AMDGPU_CHUNK_ID_SCHEDULED_DEPENDENCIES:
			r = amdgpu_cs_process_fence_dep(p, chunk);
			अगर (r)
				वापस r;
			अवरोध;
		हाल AMDGPU_CHUNK_ID_SYNCOBJ_IN:
			r = amdgpu_cs_process_syncobj_in_dep(p, chunk);
			अगर (r)
				वापस r;
			अवरोध;
		हाल AMDGPU_CHUNK_ID_SYNCOBJ_OUT:
			r = amdgpu_cs_process_syncobj_out_dep(p, chunk);
			अगर (r)
				वापस r;
			अवरोध;
		हाल AMDGPU_CHUNK_ID_SYNCOBJ_TIMELINE_WAIT:
			r = amdgpu_cs_process_syncobj_समयline_in_dep(p, chunk);
			अगर (r)
				वापस r;
			अवरोध;
		हाल AMDGPU_CHUNK_ID_SYNCOBJ_TIMELINE_SIGNAL:
			r = amdgpu_cs_process_syncobj_समयline_out_dep(p, chunk);
			अगर (r)
				वापस r;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम amdgpu_cs_post_dependencies(काष्ठा amdgpu_cs_parser *p)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < p->num_post_deps; ++i) अणु
		अगर (p->post_deps[i].chain && p->post_deps[i].poपूर्णांक) अणु
			drm_syncobj_add_poपूर्णांक(p->post_deps[i].syncobj,
					      p->post_deps[i].chain,
					      p->fence, p->post_deps[i].poपूर्णांक);
			p->post_deps[i].chain = शून्य;
		पूर्ण अन्यथा अणु
			drm_syncobj_replace_fence(p->post_deps[i].syncobj,
						  p->fence);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक amdgpu_cs_submit(काष्ठा amdgpu_cs_parser *p,
			    जोड़ drm_amdgpu_cs *cs)
अणु
	काष्ठा amdgpu_fpriv *fpriv = p->filp->driver_priv;
	काष्ठा drm_sched_entity *entity = p->entity;
	काष्ठा amdgpu_bo_list_entry *e;
	काष्ठा amdgpu_job *job;
	uपूर्णांक64_t seq;
	पूर्णांक r;

	job = p->job;
	p->job = शून्य;

	r = drm_sched_job_init(&job->base, entity, &fpriv->vm);
	अगर (r)
		जाओ error_unlock;

	/* No memory allocation is allowed जबतक holding the notअगरier lock.
	 * The lock is held until amdgpu_cs_submit is finished and fence is
	 * added to BOs.
	 */
	mutex_lock(&p->adev->notअगरier_lock);

	/* If userptr are invalidated after amdgpu_cs_parser_bos(), वापस
	 * -EAGAIN, drmIoctl in libdrm will restart the amdgpu_cs_ioctl.
	 */
	amdgpu_bo_list_क्रम_each_userptr_entry(e, p->bo_list) अणु
		काष्ठा amdgpu_bo *bo = tपंचांग_to_amdgpu_bo(e->tv.bo);

		r |= !amdgpu_tपंचांग_tt_get_user_pages_करोne(bo->tbo.tपंचांग);
	पूर्ण
	अगर (r) अणु
		r = -EAGAIN;
		जाओ error_पात;
	पूर्ण

	p->fence = dma_fence_get(&job->base.s_fence->finished);

	amdgpu_ctx_add_fence(p->ctx, entity, p->fence, &seq);
	amdgpu_cs_post_dependencies(p);

	अगर ((job->preamble_status & AMDGPU_PREAMBLE_IB_PRESENT) &&
	    !p->ctx->preamble_presented) अणु
		job->preamble_status |= AMDGPU_PREAMBLE_IB_PRESENT_FIRST;
		p->ctx->preamble_presented = true;
	पूर्ण

	cs->out.handle = seq;
	job->uf_sequence = seq;

	amdgpu_job_मुक्त_resources(job);

	trace_amdgpu_cs_ioctl(job);
	amdgpu_vm_bo_trace_cs(&fpriv->vm, &p->ticket);
	drm_sched_entity_push_job(&job->base, entity);

	amdgpu_vm_move_to_lru_tail(p->adev, &fpriv->vm);

	tपंचांग_eu_fence_buffer_objects(&p->ticket, &p->validated, p->fence);
	mutex_unlock(&p->adev->notअगरier_lock);

	वापस 0;

error_पात:
	drm_sched_job_cleanup(&job->base);
	mutex_unlock(&p->adev->notअगरier_lock);

error_unlock:
	amdgpu_job_मुक्त(job);
	वापस r;
पूर्ण

अटल व्योम trace_amdgpu_cs_ibs(काष्ठा amdgpu_cs_parser *parser)
अणु
	पूर्णांक i;

	अगर (!trace_amdgpu_cs_enabled())
		वापस;

	क्रम (i = 0; i < parser->job->num_ibs; i++)
		trace_amdgpu_cs(parser, i);
पूर्ण

पूर्णांक amdgpu_cs_ioctl(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *filp)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	जोड़ drm_amdgpu_cs *cs = data;
	काष्ठा amdgpu_cs_parser parser = अणुपूर्ण;
	bool reserved_buffers = false;
	पूर्णांक r;

	अगर (amdgpu_ras_पूर्णांकr_triggered())
		वापस -EHWPOISON;

	अगर (!adev->accel_working)
		वापस -EBUSY;

	parser.adev = adev;
	parser.filp = filp;

	r = amdgpu_cs_parser_init(&parser, data);
	अगर (r) अणु
		अगर (prपूर्णांकk_ratelimit())
			DRM_ERROR("Failed to initialize parser %d!\n", r);
		जाओ out;
	पूर्ण

	r = amdgpu_cs_ib_fill(adev, &parser);
	अगर (r)
		जाओ out;

	r = amdgpu_cs_dependencies(adev, &parser);
	अगर (r) अणु
		DRM_ERROR("Failed in the dependencies handling %d!\n", r);
		जाओ out;
	पूर्ण

	r = amdgpu_cs_parser_bos(&parser, data);
	अगर (r) अणु
		अगर (r == -ENOMEM)
			DRM_ERROR("Not enough memory for command submission!\n");
		अन्यथा अगर (r != -ERESTARTSYS && r != -EAGAIN)
			DRM_ERROR("Failed to process the buffer list %d!\n", r);
		जाओ out;
	पूर्ण

	reserved_buffers = true;

	trace_amdgpu_cs_ibs(&parser);

	r = amdgpu_cs_vm_handling(&parser);
	अगर (r)
		जाओ out;

	r = amdgpu_cs_submit(&parser, cs);

out:
	amdgpu_cs_parser_fini(&parser, r, reserved_buffers);

	वापस r;
पूर्ण

/**
 * amdgpu_cs_रुको_ioctl - रुको क्रम a command submission to finish
 *
 * @dev: drm device
 * @data: data from userspace
 * @filp: file निजी
 *
 * Wait क्रम the command submission identअगरied by handle to finish.
 */
पूर्णांक amdgpu_cs_रुको_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *filp)
अणु
	जोड़ drm_amdgpu_रुको_cs *रुको = data;
	अचिन्हित दीर्घ समयout = amdgpu_gem_समयout(रुको->in.समयout);
	काष्ठा drm_sched_entity *entity;
	काष्ठा amdgpu_ctx *ctx;
	काष्ठा dma_fence *fence;
	दीर्घ r;

	ctx = amdgpu_ctx_get(filp->driver_priv, रुको->in.ctx_id);
	अगर (ctx == शून्य)
		वापस -EINVAL;

	r = amdgpu_ctx_get_entity(ctx, रुको->in.ip_type, रुको->in.ip_instance,
				  रुको->in.ring, &entity);
	अगर (r) अणु
		amdgpu_ctx_put(ctx);
		वापस r;
	पूर्ण

	fence = amdgpu_ctx_get_fence(ctx, entity, रुको->in.handle);
	अगर (IS_ERR(fence))
		r = PTR_ERR(fence);
	अन्यथा अगर (fence) अणु
		r = dma_fence_रुको_समयout(fence, true, समयout);
		अगर (r > 0 && fence->error)
			r = fence->error;
		dma_fence_put(fence);
	पूर्ण अन्यथा
		r = 1;

	amdgpu_ctx_put(ctx);
	अगर (r < 0)
		वापस r;

	स_रखो(रुको, 0, माप(*रुको));
	रुको->out.status = (r == 0);

	वापस 0;
पूर्ण

/**
 * amdgpu_cs_get_fence - helper to get fence from drm_amdgpu_fence
 *
 * @adev: amdgpu device
 * @filp: file निजी
 * @user: drm_amdgpu_fence copied from user space
 */
अटल काष्ठा dma_fence *amdgpu_cs_get_fence(काष्ठा amdgpu_device *adev,
					     काष्ठा drm_file *filp,
					     काष्ठा drm_amdgpu_fence *user)
अणु
	काष्ठा drm_sched_entity *entity;
	काष्ठा amdgpu_ctx *ctx;
	काष्ठा dma_fence *fence;
	पूर्णांक r;

	ctx = amdgpu_ctx_get(filp->driver_priv, user->ctx_id);
	अगर (ctx == शून्य)
		वापस ERR_PTR(-EINVAL);

	r = amdgpu_ctx_get_entity(ctx, user->ip_type, user->ip_instance,
				  user->ring, &entity);
	अगर (r) अणु
		amdgpu_ctx_put(ctx);
		वापस ERR_PTR(r);
	पूर्ण

	fence = amdgpu_ctx_get_fence(ctx, entity, user->seq_no);
	amdgpu_ctx_put(ctx);

	वापस fence;
पूर्ण

पूर्णांक amdgpu_cs_fence_to_handle_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *filp)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	जोड़ drm_amdgpu_fence_to_handle *info = data;
	काष्ठा dma_fence *fence;
	काष्ठा drm_syncobj *syncobj;
	काष्ठा sync_file *sync_file;
	पूर्णांक fd, r;

	fence = amdgpu_cs_get_fence(adev, filp, &info->in.fence);
	अगर (IS_ERR(fence))
		वापस PTR_ERR(fence);

	अगर (!fence)
		fence = dma_fence_get_stub();

	चयन (info->in.what) अणु
	हाल AMDGPU_FENCE_TO_HANDLE_GET_SYNCOBJ:
		r = drm_syncobj_create(&syncobj, 0, fence);
		dma_fence_put(fence);
		अगर (r)
			वापस r;
		r = drm_syncobj_get_handle(filp, syncobj, &info->out.handle);
		drm_syncobj_put(syncobj);
		वापस r;

	हाल AMDGPU_FENCE_TO_HANDLE_GET_SYNCOBJ_FD:
		r = drm_syncobj_create(&syncobj, 0, fence);
		dma_fence_put(fence);
		अगर (r)
			वापस r;
		r = drm_syncobj_get_fd(syncobj, (पूर्णांक *)&info->out.handle);
		drm_syncobj_put(syncobj);
		वापस r;

	हाल AMDGPU_FENCE_TO_HANDLE_GET_SYNC_खाता_FD:
		fd = get_unused_fd_flags(O_CLOEXEC);
		अगर (fd < 0) अणु
			dma_fence_put(fence);
			वापस fd;
		पूर्ण

		sync_file = sync_file_create(fence);
		dma_fence_put(fence);
		अगर (!sync_file) अणु
			put_unused_fd(fd);
			वापस -ENOMEM;
		पूर्ण

		fd_install(fd, sync_file->file);
		info->out.handle = fd;
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * amdgpu_cs_रुको_all_fence - रुको on all fences to संकेत
 *
 * @adev: amdgpu device
 * @filp: file निजी
 * @रुको: रुको parameters
 * @fences: array of drm_amdgpu_fence
 */
अटल पूर्णांक amdgpu_cs_रुको_all_fences(काष्ठा amdgpu_device *adev,
				     काष्ठा drm_file *filp,
				     जोड़ drm_amdgpu_रुको_fences *रुको,
				     काष्ठा drm_amdgpu_fence *fences)
अणु
	uपूर्णांक32_t fence_count = रुको->in.fence_count;
	अचिन्हित पूर्णांक i;
	दीर्घ r = 1;

	क्रम (i = 0; i < fence_count; i++) अणु
		काष्ठा dma_fence *fence;
		अचिन्हित दीर्घ समयout = amdgpu_gem_समयout(रुको->in.समयout_ns);

		fence = amdgpu_cs_get_fence(adev, filp, &fences[i]);
		अगर (IS_ERR(fence))
			वापस PTR_ERR(fence);
		अन्यथा अगर (!fence)
			जारी;

		r = dma_fence_रुको_समयout(fence, true, समयout);
		dma_fence_put(fence);
		अगर (r < 0)
			वापस r;

		अगर (r == 0)
			अवरोध;

		अगर (fence->error)
			वापस fence->error;
	पूर्ण

	स_रखो(रुको, 0, माप(*रुको));
	रुको->out.status = (r > 0);

	वापस 0;
पूर्ण

/**
 * amdgpu_cs_रुको_any_fence - रुको on any fence to संकेत
 *
 * @adev: amdgpu device
 * @filp: file निजी
 * @रुको: रुको parameters
 * @fences: array of drm_amdgpu_fence
 */
अटल पूर्णांक amdgpu_cs_रुको_any_fence(काष्ठा amdgpu_device *adev,
				    काष्ठा drm_file *filp,
				    जोड़ drm_amdgpu_रुको_fences *रुको,
				    काष्ठा drm_amdgpu_fence *fences)
अणु
	अचिन्हित दीर्घ समयout = amdgpu_gem_समयout(रुको->in.समयout_ns);
	uपूर्णांक32_t fence_count = रुको->in.fence_count;
	uपूर्णांक32_t first = ~0;
	काष्ठा dma_fence **array;
	अचिन्हित पूर्णांक i;
	दीर्घ r;

	/* Prepare the fence array */
	array = kसुस्मृति(fence_count, माप(काष्ठा dma_fence *), GFP_KERNEL);

	अगर (array == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < fence_count; i++) अणु
		काष्ठा dma_fence *fence;

		fence = amdgpu_cs_get_fence(adev, filp, &fences[i]);
		अगर (IS_ERR(fence)) अणु
			r = PTR_ERR(fence);
			जाओ err_मुक्त_fence_array;
		पूर्ण अन्यथा अगर (fence) अणु
			array[i] = fence;
		पूर्ण अन्यथा अणु /* शून्य, the fence has been alपढ़ोy संकेतed */
			r = 1;
			first = i;
			जाओ out;
		पूर्ण
	पूर्ण

	r = dma_fence_रुको_any_समयout(array, fence_count, true, समयout,
				       &first);
	अगर (r < 0)
		जाओ err_मुक्त_fence_array;

out:
	स_रखो(रुको, 0, माप(*रुको));
	रुको->out.status = (r > 0);
	रुको->out.first_संकेतed = first;

	अगर (first < fence_count && array[first])
		r = array[first]->error;
	अन्यथा
		r = 0;

err_मुक्त_fence_array:
	क्रम (i = 0; i < fence_count; i++)
		dma_fence_put(array[i]);
	kमुक्त(array);

	वापस r;
पूर्ण

/**
 * amdgpu_cs_रुको_fences_ioctl - रुको क्रम multiple command submissions to finish
 *
 * @dev: drm device
 * @data: data from userspace
 * @filp: file निजी
 */
पूर्णांक amdgpu_cs_रुको_fences_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *filp)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	जोड़ drm_amdgpu_रुको_fences *रुको = data;
	uपूर्णांक32_t fence_count = रुको->in.fence_count;
	काष्ठा drm_amdgpu_fence *fences_user;
	काष्ठा drm_amdgpu_fence *fences;
	पूर्णांक r;

	/* Get the fences from userspace */
	fences = kदो_स्मृति_array(fence_count, माप(काष्ठा drm_amdgpu_fence),
			GFP_KERNEL);
	अगर (fences == शून्य)
		वापस -ENOMEM;

	fences_user = u64_to_user_ptr(रुको->in.fences);
	अगर (copy_from_user(fences, fences_user,
		माप(काष्ठा drm_amdgpu_fence) * fence_count)) अणु
		r = -EFAULT;
		जाओ err_मुक्त_fences;
	पूर्ण

	अगर (रुको->in.रुको_all)
		r = amdgpu_cs_रुको_all_fences(adev, filp, रुको, fences);
	अन्यथा
		r = amdgpu_cs_रुको_any_fence(adev, filp, रुको, fences);

err_मुक्त_fences:
	kमुक्त(fences);

	वापस r;
पूर्ण

/**
 * amdgpu_cs_find_bo_va - find bo_va क्रम VM address
 *
 * @parser: command submission parser context
 * @addr: VM address
 * @bo: resulting BO of the mapping found
 * @map: Placeholder to वापस found BO mapping
 *
 * Search the buffer objects in the command submission context क्रम a certain
 * भव memory address. Returns allocation काष्ठाure when found, शून्य
 * otherwise.
 */
पूर्णांक amdgpu_cs_find_mapping(काष्ठा amdgpu_cs_parser *parser,
			   uपूर्णांक64_t addr, काष्ठा amdgpu_bo **bo,
			   काष्ठा amdgpu_bo_va_mapping **map)
अणु
	काष्ठा amdgpu_fpriv *fpriv = parser->filp->driver_priv;
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	काष्ठा amdgpu_vm *vm = &fpriv->vm;
	काष्ठा amdgpu_bo_va_mapping *mapping;
	पूर्णांक r;

	addr /= AMDGPU_GPU_PAGE_SIZE;

	mapping = amdgpu_vm_bo_lookup_mapping(vm, addr);
	अगर (!mapping || !mapping->bo_va || !mapping->bo_va->base.bo)
		वापस -EINVAL;

	*bo = mapping->bo_va->base.bo;
	*map = mapping;

	/* Double check that the BO is reserved by this CS */
	अगर (dma_resv_locking_ctx((*bo)->tbo.base.resv) != &parser->ticket)
		वापस -EINVAL;

	अगर (!((*bo)->flags & AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS)) अणु
		(*bo)->flags |= AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS;
		amdgpu_bo_placement_from_करोमुख्य(*bo, (*bo)->allowed_करोमुख्यs);
		r = tपंचांग_bo_validate(&(*bo)->tbo, &(*bo)->placement, &ctx);
		अगर (r)
			वापस r;
	पूर्ण

	वापस amdgpu_tपंचांग_alloc_gart(&(*bo)->tbo);
पूर्ण
