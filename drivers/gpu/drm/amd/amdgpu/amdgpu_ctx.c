<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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
 * Authors: monk liu <monk.liu@amd.com>
 */

#समावेश <drm/drm_auth.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_sched.h"
#समावेश "amdgpu_ras.h"
#समावेश <linux/nospec.h>

#घोषणा to_amdgpu_ctx_entity(e)	\
	container_of((e), काष्ठा amdgpu_ctx_entity, entity)

स्थिर अचिन्हित पूर्णांक amdgpu_ctx_num_entities[AMDGPU_HW_IP_NUM] = अणु
	[AMDGPU_HW_IP_GFX]	=	1,
	[AMDGPU_HW_IP_COMPUTE]	=	4,
	[AMDGPU_HW_IP_DMA]	=	2,
	[AMDGPU_HW_IP_UVD]	=	1,
	[AMDGPU_HW_IP_VCE]	=	1,
	[AMDGPU_HW_IP_UVD_ENC]	=	1,
	[AMDGPU_HW_IP_VCN_DEC]	=	1,
	[AMDGPU_HW_IP_VCN_ENC]	=	1,
	[AMDGPU_HW_IP_VCN_JPEG]	=	1,
पूर्ण;

अटल पूर्णांक amdgpu_ctx_priority_permit(काष्ठा drm_file *filp,
				      क्रमागत drm_sched_priority priority)
अणु
	अगर (priority < 0 || priority >= DRM_SCHED_PRIORITY_COUNT)
		वापस -EINVAL;

	/* NORMAL and below are accessible by everyone */
	अगर (priority <= DRM_SCHED_PRIORITY_NORMAL)
		वापस 0;

	अगर (capable(CAP_SYS_NICE))
		वापस 0;

	अगर (drm_is_current_master(filp))
		वापस 0;

	वापस -EACCES;
पूर्ण

अटल क्रमागत gfx_pipe_priority amdgpu_ctx_sched_prio_to_compute_prio(क्रमागत drm_sched_priority prio)
अणु
	चयन (prio) अणु
	हाल DRM_SCHED_PRIORITY_HIGH:
	हाल DRM_SCHED_PRIORITY_KERNEL:
		वापस AMDGPU_GFX_PIPE_PRIO_HIGH;
	शेष:
		वापस AMDGPU_GFX_PIPE_PRIO_NORMAL;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक amdgpu_ctx_prio_sched_to_hw(काष्ठा amdgpu_device *adev,
						 क्रमागत drm_sched_priority prio,
						 u32 hw_ip)
अणु
	अचिन्हित पूर्णांक hw_prio;

	hw_prio = (hw_ip == AMDGPU_HW_IP_COMPUTE) ?
			amdgpu_ctx_sched_prio_to_compute_prio(prio) :
			AMDGPU_RING_PRIO_DEFAULT;
	hw_ip = array_index_nospec(hw_ip, AMDGPU_HW_IP_NUM);
	अगर (adev->gpu_sched[hw_ip][hw_prio].num_scheds == 0)
		hw_prio = AMDGPU_RING_PRIO_DEFAULT;

	वापस hw_prio;
पूर्ण

अटल पूर्णांक amdgpu_ctx_init_entity(काष्ठा amdgpu_ctx *ctx, u32 hw_ip,
				   स्थिर u32 ring)
अणु
	काष्ठा amdgpu_device *adev = ctx->adev;
	काष्ठा amdgpu_ctx_entity *entity;
	काष्ठा drm_gpu_scheduler **scheds = शून्य, *sched = शून्य;
	अचिन्हित num_scheds = 0;
	अचिन्हित पूर्णांक hw_prio;
	क्रमागत drm_sched_priority priority;
	पूर्णांक r;

	entity = kzalloc(काष्ठा_size(entity, fences, amdgpu_sched_jobs),
			 GFP_KERNEL);
	अगर (!entity)
		वापस  -ENOMEM;

	entity->sequence = 1;
	priority = (ctx->override_priority == DRM_SCHED_PRIORITY_UNSET) ?
				ctx->init_priority : ctx->override_priority;
	hw_prio = amdgpu_ctx_prio_sched_to_hw(adev, priority, hw_ip);

	hw_ip = array_index_nospec(hw_ip, AMDGPU_HW_IP_NUM);
	scheds = adev->gpu_sched[hw_ip][hw_prio].sched;
	num_scheds = adev->gpu_sched[hw_ip][hw_prio].num_scheds;

	/* disable load balance अगर the hw engine retains context among dependent jobs */
	अगर (hw_ip == AMDGPU_HW_IP_VCN_ENC ||
	    hw_ip == AMDGPU_HW_IP_VCN_DEC ||
	    hw_ip == AMDGPU_HW_IP_UVD_ENC ||
	    hw_ip == AMDGPU_HW_IP_UVD) अणु
		sched = drm_sched_pick_best(scheds, num_scheds);
		scheds = &sched;
		num_scheds = 1;
	पूर्ण

	r = drm_sched_entity_init(&entity->entity, priority, scheds, num_scheds,
				  &ctx->guilty);
	अगर (r)
		जाओ error_मुक्त_entity;

	ctx->entities[hw_ip][ring] = entity;
	वापस 0;

error_मुक्त_entity:
	kमुक्त(entity);

	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_ctx_init(काष्ठा amdgpu_device *adev,
			   क्रमागत drm_sched_priority priority,
			   काष्ठा drm_file *filp,
			   काष्ठा amdgpu_ctx *ctx)
अणु
	पूर्णांक r;

	r = amdgpu_ctx_priority_permit(filp, priority);
	अगर (r)
		वापस r;

	स_रखो(ctx, 0, माप(*ctx));

	ctx->adev = adev;

	kref_init(&ctx->refcount);
	spin_lock_init(&ctx->ring_lock);
	mutex_init(&ctx->lock);

	ctx->reset_counter = atomic_पढ़ो(&adev->gpu_reset_counter);
	ctx->reset_counter_query = ctx->reset_counter;
	ctx->vram_lost_counter = atomic_पढ़ो(&adev->vram_lost_counter);
	ctx->init_priority = priority;
	ctx->override_priority = DRM_SCHED_PRIORITY_UNSET;

	वापस 0;
पूर्ण

अटल व्योम amdgpu_ctx_fini_entity(काष्ठा amdgpu_ctx_entity *entity)
अणु

	पूर्णांक i;

	अगर (!entity)
		वापस;

	क्रम (i = 0; i < amdgpu_sched_jobs; ++i)
		dma_fence_put(entity->fences[i]);

	kमुक्त(entity);
पूर्ण

अटल व्योम amdgpu_ctx_fini(काष्ठा kref *ref)
अणु
	काष्ठा amdgpu_ctx *ctx = container_of(ref, काष्ठा amdgpu_ctx, refcount);
	काष्ठा amdgpu_device *adev = ctx->adev;
	अचिन्हित i, j;

	अगर (!adev)
		वापस;

	क्रम (i = 0; i < AMDGPU_HW_IP_NUM; ++i) अणु
		क्रम (j = 0; j < AMDGPU_MAX_ENTITY_NUM; ++j) अणु
			amdgpu_ctx_fini_entity(ctx->entities[i][j]);
			ctx->entities[i][j] = शून्य;
		पूर्ण
	पूर्ण

	mutex_destroy(&ctx->lock);
	kमुक्त(ctx);
पूर्ण

पूर्णांक amdgpu_ctx_get_entity(काष्ठा amdgpu_ctx *ctx, u32 hw_ip, u32 instance,
			  u32 ring, काष्ठा drm_sched_entity **entity)
अणु
	पूर्णांक r;

	अगर (hw_ip >= AMDGPU_HW_IP_NUM) अणु
		DRM_ERROR("unknown HW IP type: %d\n", hw_ip);
		वापस -EINVAL;
	पूर्ण

	/* Right now all IPs have only one instance - multiple rings. */
	अगर (instance != 0) अणु
		DRM_DEBUG("invalid ip instance: %d\n", instance);
		वापस -EINVAL;
	पूर्ण

	अगर (ring >= amdgpu_ctx_num_entities[hw_ip]) अणु
		DRM_DEBUG("invalid ring: %d %d\n", hw_ip, ring);
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->entities[hw_ip][ring] == शून्य) अणु
		r = amdgpu_ctx_init_entity(ctx, hw_ip, ring);
		अगर (r)
			वापस r;
	पूर्ण

	*entity = &ctx->entities[hw_ip][ring]->entity;
	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_ctx_alloc(काष्ठा amdgpu_device *adev,
			    काष्ठा amdgpu_fpriv *fpriv,
			    काष्ठा drm_file *filp,
			    क्रमागत drm_sched_priority priority,
			    uपूर्णांक32_t *id)
अणु
	काष्ठा amdgpu_ctx_mgr *mgr = &fpriv->ctx_mgr;
	काष्ठा amdgpu_ctx *ctx;
	पूर्णांक r;

	ctx = kदो_स्मृति(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	mutex_lock(&mgr->lock);
	r = idr_alloc(&mgr->ctx_handles, ctx, 1, AMDGPU_VM_MAX_NUM_CTX, GFP_KERNEL);
	अगर (r < 0) अणु
		mutex_unlock(&mgr->lock);
		kमुक्त(ctx);
		वापस r;
	पूर्ण

	*id = (uपूर्णांक32_t)r;
	r = amdgpu_ctx_init(adev, priority, filp, ctx);
	अगर (r) अणु
		idr_हटाओ(&mgr->ctx_handles, *id);
		*id = 0;
		kमुक्त(ctx);
	पूर्ण
	mutex_unlock(&mgr->lock);
	वापस r;
पूर्ण

अटल व्योम amdgpu_ctx_करो_release(काष्ठा kref *ref)
अणु
	काष्ठा amdgpu_ctx *ctx;
	u32 i, j;

	ctx = container_of(ref, काष्ठा amdgpu_ctx, refcount);
	क्रम (i = 0; i < AMDGPU_HW_IP_NUM; ++i) अणु
		क्रम (j = 0; j < amdgpu_ctx_num_entities[i]; ++j) अणु
			अगर (!ctx->entities[i][j])
				जारी;

			drm_sched_entity_destroy(&ctx->entities[i][j]->entity);
		पूर्ण
	पूर्ण

	amdgpu_ctx_fini(ref);
पूर्ण

अटल पूर्णांक amdgpu_ctx_मुक्त(काष्ठा amdgpu_fpriv *fpriv, uपूर्णांक32_t id)
अणु
	काष्ठा amdgpu_ctx_mgr *mgr = &fpriv->ctx_mgr;
	काष्ठा amdgpu_ctx *ctx;

	mutex_lock(&mgr->lock);
	ctx = idr_हटाओ(&mgr->ctx_handles, id);
	अगर (ctx)
		kref_put(&ctx->refcount, amdgpu_ctx_करो_release);
	mutex_unlock(&mgr->lock);
	वापस ctx ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक amdgpu_ctx_query(काष्ठा amdgpu_device *adev,
			    काष्ठा amdgpu_fpriv *fpriv, uपूर्णांक32_t id,
			    जोड़ drm_amdgpu_ctx_out *out)
अणु
	काष्ठा amdgpu_ctx *ctx;
	काष्ठा amdgpu_ctx_mgr *mgr;
	अचिन्हित reset_counter;

	अगर (!fpriv)
		वापस -EINVAL;

	mgr = &fpriv->ctx_mgr;
	mutex_lock(&mgr->lock);
	ctx = idr_find(&mgr->ctx_handles, id);
	अगर (!ctx) अणु
		mutex_unlock(&mgr->lock);
		वापस -EINVAL;
	पूर्ण

	/* TODO: these two are always zero */
	out->state.flags = 0x0;
	out->state.hangs = 0x0;

	/* determine अगर a GPU reset has occured since the last call */
	reset_counter = atomic_पढ़ो(&adev->gpu_reset_counter);
	/* TODO: this should ideally वापस NO, GUILTY, or INNOCENT. */
	अगर (ctx->reset_counter_query == reset_counter)
		out->state.reset_status = AMDGPU_CTX_NO_RESET;
	अन्यथा
		out->state.reset_status = AMDGPU_CTX_UNKNOWN_RESET;
	ctx->reset_counter_query = reset_counter;

	mutex_unlock(&mgr->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_ctx_query2(काष्ठा amdgpu_device *adev,
	काष्ठा amdgpu_fpriv *fpriv, uपूर्णांक32_t id,
	जोड़ drm_amdgpu_ctx_out *out)
अणु
	काष्ठा amdgpu_ctx *ctx;
	काष्ठा amdgpu_ctx_mgr *mgr;

	अगर (!fpriv)
		वापस -EINVAL;

	mgr = &fpriv->ctx_mgr;
	mutex_lock(&mgr->lock);
	ctx = idr_find(&mgr->ctx_handles, id);
	अगर (!ctx) अणु
		mutex_unlock(&mgr->lock);
		वापस -EINVAL;
	पूर्ण

	out->state.flags = 0x0;
	out->state.hangs = 0x0;

	अगर (ctx->reset_counter != atomic_पढ़ो(&adev->gpu_reset_counter))
		out->state.flags |= AMDGPU_CTX_QUERY2_FLAGS_RESET;

	अगर (ctx->vram_lost_counter != atomic_पढ़ो(&adev->vram_lost_counter))
		out->state.flags |= AMDGPU_CTX_QUERY2_FLAGS_VRAMLOST;

	अगर (atomic_पढ़ो(&ctx->guilty))
		out->state.flags |= AMDGPU_CTX_QUERY2_FLAGS_GUILTY;

	mutex_unlock(&mgr->lock);
	वापस 0;
पूर्ण

पूर्णांक amdgpu_ctx_ioctl(काष्ठा drm_device *dev, व्योम *data,
		     काष्ठा drm_file *filp)
अणु
	पूर्णांक r;
	uपूर्णांक32_t id;
	क्रमागत drm_sched_priority priority;

	जोड़ drm_amdgpu_ctx *args = data;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_fpriv *fpriv = filp->driver_priv;

	id = args->in.ctx_id;
	r = amdgpu_to_sched_priority(args->in.priority, &priority);

	/* For backwards compatibility reasons, we need to accept
	 * ioctls with garbage in the priority field */
	अगर (r == -EINVAL)
		priority = DRM_SCHED_PRIORITY_NORMAL;

	चयन (args->in.op) अणु
	हाल AMDGPU_CTX_OP_ALLOC_CTX:
		r = amdgpu_ctx_alloc(adev, fpriv, filp, priority, &id);
		args->out.alloc.ctx_id = id;
		अवरोध;
	हाल AMDGPU_CTX_OP_FREE_CTX:
		r = amdgpu_ctx_मुक्त(fpriv, id);
		अवरोध;
	हाल AMDGPU_CTX_OP_QUERY_STATE:
		r = amdgpu_ctx_query(adev, fpriv, id, &args->out);
		अवरोध;
	हाल AMDGPU_CTX_OP_QUERY_STATE2:
		r = amdgpu_ctx_query2(adev, fpriv, id, &args->out);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस r;
पूर्ण

काष्ठा amdgpu_ctx *amdgpu_ctx_get(काष्ठा amdgpu_fpriv *fpriv, uपूर्णांक32_t id)
अणु
	काष्ठा amdgpu_ctx *ctx;
	काष्ठा amdgpu_ctx_mgr *mgr;

	अगर (!fpriv)
		वापस शून्य;

	mgr = &fpriv->ctx_mgr;

	mutex_lock(&mgr->lock);
	ctx = idr_find(&mgr->ctx_handles, id);
	अगर (ctx)
		kref_get(&ctx->refcount);
	mutex_unlock(&mgr->lock);
	वापस ctx;
पूर्ण

पूर्णांक amdgpu_ctx_put(काष्ठा amdgpu_ctx *ctx)
अणु
	अगर (ctx == शून्य)
		वापस -EINVAL;

	kref_put(&ctx->refcount, amdgpu_ctx_करो_release);
	वापस 0;
पूर्ण

व्योम amdgpu_ctx_add_fence(काष्ठा amdgpu_ctx *ctx,
			  काष्ठा drm_sched_entity *entity,
			  काष्ठा dma_fence *fence, uपूर्णांक64_t *handle)
अणु
	काष्ठा amdgpu_ctx_entity *centity = to_amdgpu_ctx_entity(entity);
	uपूर्णांक64_t seq = centity->sequence;
	काष्ठा dma_fence *other = शून्य;
	अचिन्हित idx = 0;

	idx = seq & (amdgpu_sched_jobs - 1);
	other = centity->fences[idx];
	अगर (other)
		BUG_ON(!dma_fence_is_संकेतed(other));

	dma_fence_get(fence);

	spin_lock(&ctx->ring_lock);
	centity->fences[idx] = fence;
	centity->sequence++;
	spin_unlock(&ctx->ring_lock);

	dma_fence_put(other);
	अगर (handle)
		*handle = seq;
पूर्ण

काष्ठा dma_fence *amdgpu_ctx_get_fence(काष्ठा amdgpu_ctx *ctx,
				       काष्ठा drm_sched_entity *entity,
				       uपूर्णांक64_t seq)
अणु
	काष्ठा amdgpu_ctx_entity *centity = to_amdgpu_ctx_entity(entity);
	काष्ठा dma_fence *fence;

	spin_lock(&ctx->ring_lock);

	अगर (seq == ~0ull)
		seq = centity->sequence - 1;

	अगर (seq >= centity->sequence) अणु
		spin_unlock(&ctx->ring_lock);
		वापस ERR_PTR(-EINVAL);
	पूर्ण


	अगर (seq + amdgpu_sched_jobs < centity->sequence) अणु
		spin_unlock(&ctx->ring_lock);
		वापस शून्य;
	पूर्ण

	fence = dma_fence_get(centity->fences[seq & (amdgpu_sched_jobs - 1)]);
	spin_unlock(&ctx->ring_lock);

	वापस fence;
पूर्ण

अटल व्योम amdgpu_ctx_set_entity_priority(काष्ठा amdgpu_ctx *ctx,
					    काष्ठा amdgpu_ctx_entity *aentity,
					    पूर्णांक hw_ip,
					    क्रमागत drm_sched_priority priority)
अणु
	काष्ठा amdgpu_device *adev = ctx->adev;
	अचिन्हित पूर्णांक hw_prio;
	काष्ठा drm_gpu_scheduler **scheds = शून्य;
	अचिन्हित num_scheds;

	/* set sw priority */
	drm_sched_entity_set_priority(&aentity->entity, priority);

	/* set hw priority */
	अगर (hw_ip == AMDGPU_HW_IP_COMPUTE) अणु
		hw_prio = amdgpu_ctx_prio_sched_to_hw(adev, priority,
						      AMDGPU_HW_IP_COMPUTE);
		hw_prio = array_index_nospec(hw_prio, AMDGPU_RING_PRIO_MAX);
		scheds = adev->gpu_sched[hw_ip][hw_prio].sched;
		num_scheds = adev->gpu_sched[hw_ip][hw_prio].num_scheds;
		drm_sched_entity_modअगरy_sched(&aentity->entity, scheds,
					      num_scheds);
	पूर्ण
पूर्ण

व्योम amdgpu_ctx_priority_override(काष्ठा amdgpu_ctx *ctx,
				  क्रमागत drm_sched_priority priority)
अणु
	क्रमागत drm_sched_priority ctx_prio;
	अचिन्हित i, j;

	ctx->override_priority = priority;

	ctx_prio = (ctx->override_priority == DRM_SCHED_PRIORITY_UNSET) ?
			ctx->init_priority : ctx->override_priority;
	क्रम (i = 0; i < AMDGPU_HW_IP_NUM; ++i) अणु
		क्रम (j = 0; j < amdgpu_ctx_num_entities[i]; ++j) अणु
			अगर (!ctx->entities[i][j])
				जारी;

			amdgpu_ctx_set_entity_priority(ctx, ctx->entities[i][j],
						       i, ctx_prio);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक amdgpu_ctx_रुको_prev_fence(काष्ठा amdgpu_ctx *ctx,
			       काष्ठा drm_sched_entity *entity)
अणु
	काष्ठा amdgpu_ctx_entity *centity = to_amdgpu_ctx_entity(entity);
	काष्ठा dma_fence *other;
	अचिन्हित idx;
	दीर्घ r;

	spin_lock(&ctx->ring_lock);
	idx = centity->sequence & (amdgpu_sched_jobs - 1);
	other = dma_fence_get(centity->fences[idx]);
	spin_unlock(&ctx->ring_lock);

	अगर (!other)
		वापस 0;

	r = dma_fence_रुको(other, true);
	अगर (r < 0 && r != -ERESTARTSYS)
		DRM_ERROR("Error (%ld) waiting for fence!\n", r);

	dma_fence_put(other);
	वापस r;
पूर्ण

व्योम amdgpu_ctx_mgr_init(काष्ठा amdgpu_ctx_mgr *mgr)
अणु
	mutex_init(&mgr->lock);
	idr_init(&mgr->ctx_handles);
पूर्ण

दीर्घ amdgpu_ctx_mgr_entity_flush(काष्ठा amdgpu_ctx_mgr *mgr, दीर्घ समयout)
अणु
	काष्ठा amdgpu_ctx *ctx;
	काष्ठा idr *idp;
	uपूर्णांक32_t id, i, j;

	idp = &mgr->ctx_handles;

	mutex_lock(&mgr->lock);
	idr_क्रम_each_entry(idp, ctx, id) अणु
		क्रम (i = 0; i < AMDGPU_HW_IP_NUM; ++i) अणु
			क्रम (j = 0; j < amdgpu_ctx_num_entities[i]; ++j) अणु
				काष्ठा drm_sched_entity *entity;

				अगर (!ctx->entities[i][j])
					जारी;

				entity = &ctx->entities[i][j]->entity;
				समयout = drm_sched_entity_flush(entity, समयout);
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&mgr->lock);
	वापस समयout;
पूर्ण

व्योम amdgpu_ctx_mgr_entity_fini(काष्ठा amdgpu_ctx_mgr *mgr)
अणु
	काष्ठा amdgpu_ctx *ctx;
	काष्ठा idr *idp;
	uपूर्णांक32_t id, i, j;

	idp = &mgr->ctx_handles;

	idr_क्रम_each_entry(idp, ctx, id) अणु
		अगर (kref_पढ़ो(&ctx->refcount) != 1) अणु
			DRM_ERROR("ctx %p is still alive\n", ctx);
			जारी;
		पूर्ण

		क्रम (i = 0; i < AMDGPU_HW_IP_NUM; ++i) अणु
			क्रम (j = 0; j < amdgpu_ctx_num_entities[i]; ++j) अणु
				काष्ठा drm_sched_entity *entity;

				अगर (!ctx->entities[i][j])
					जारी;

				entity = &ctx->entities[i][j]->entity;
				drm_sched_entity_fini(entity);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम amdgpu_ctx_mgr_fini(काष्ठा amdgpu_ctx_mgr *mgr)
अणु
	काष्ठा amdgpu_ctx *ctx;
	काष्ठा idr *idp;
	uपूर्णांक32_t id;

	amdgpu_ctx_mgr_entity_fini(mgr);

	idp = &mgr->ctx_handles;

	idr_क्रम_each_entry(idp, ctx, id) अणु
		अगर (kref_put(&ctx->refcount, amdgpu_ctx_fini) != 1)
			DRM_ERROR("ctx %p is still alive\n", ctx);
	पूर्ण

	idr_destroy(&mgr->ctx_handles);
	mutex_destroy(&mgr->lock);
पूर्ण
