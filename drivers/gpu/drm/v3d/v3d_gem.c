<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (C) 2014-2018 Broadcom */

#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_syncobj.h>
#समावेश <uapi/drm/v3d_drm.h>

#समावेश "v3d_drv.h"
#समावेश "v3d_regs.h"
#समावेश "v3d_trace.h"

अटल व्योम
v3d_init_core(काष्ठा v3d_dev *v3d, पूर्णांक core)
अणु
	/* Set OVRTMUOUT, which means that the texture sampler unअगरorm
	 * configuration's पंचांगu output type field is used, instead of
	 * using the hardware शेष behavior based on the texture
	 * type.  If you want the शेष behavior, you can still put
	 * "2" in the indirect texture state's output_type field.
	 */
	अगर (v3d->ver < 40)
		V3D_CORE_WRITE(core, V3D_CTL_MISCCFG, V3D_MISCCFG_OVRTMUOUT);

	/* Whenever we flush the L2T cache, we always want to flush
	 * the whole thing.
	 */
	V3D_CORE_WRITE(core, V3D_CTL_L2TFLSTA, 0);
	V3D_CORE_WRITE(core, V3D_CTL_L2TFLEND, ~0);
पूर्ण

/* Sets invariant state क्रम the HW. */
अटल व्योम
v3d_init_hw_state(काष्ठा v3d_dev *v3d)
अणु
	v3d_init_core(v3d, 0);
पूर्ण

अटल व्योम
v3d_idle_axi(काष्ठा v3d_dev *v3d, पूर्णांक core)
अणु
	V3D_CORE_WRITE(core, V3D_GMP_CFG, V3D_GMP_CFG_STOP_REQ);

	अगर (रुको_क्रम((V3D_CORE_READ(core, V3D_GMP_STATUS) &
		      (V3D_GMP_STATUS_RD_COUNT_MASK |
		       V3D_GMP_STATUS_WR_COUNT_MASK |
		       V3D_GMP_STATUS_CFG_BUSY)) == 0, 100)) अणु
		DRM_ERROR("Failed to wait for safe GMP shutdown\n");
	पूर्ण
पूर्ण

अटल व्योम
v3d_idle_gca(काष्ठा v3d_dev *v3d)
अणु
	अगर (v3d->ver >= 41)
		वापस;

	V3D_GCA_WRITE(V3D_GCA_SAFE_SHUTDOWN, V3D_GCA_SAFE_SHUTDOWN_EN);

	अगर (रुको_क्रम((V3D_GCA_READ(V3D_GCA_SAFE_SHUTDOWN_ACK) &
		      V3D_GCA_SAFE_SHUTDOWN_ACK_ACKED) ==
		     V3D_GCA_SAFE_SHUTDOWN_ACK_ACKED, 100)) अणु
		DRM_ERROR("Failed to wait for safe GCA shutdown\n");
	पूर्ण
पूर्ण

अटल व्योम
v3d_reset_by_bridge(काष्ठा v3d_dev *v3d)
अणु
	पूर्णांक version = V3D_BRIDGE_READ(V3D_TOP_GR_BRIDGE_REVISION);

	अगर (V3D_GET_FIELD(version, V3D_TOP_GR_BRIDGE_MAJOR) == 2) अणु
		V3D_BRIDGE_WRITE(V3D_TOP_GR_BRIDGE_SW_INIT_0,
				 V3D_TOP_GR_BRIDGE_SW_INIT_0_V3D_CLK_108_SW_INIT);
		V3D_BRIDGE_WRITE(V3D_TOP_GR_BRIDGE_SW_INIT_0, 0);

		/* GFXH-1383: The SW_INIT may cause a stray ग_लिखो to address 0
		 * of the unit, so reset it to its घातer-on value here.
		 */
		V3D_WRITE(V3D_HUB_AXICFG, V3D_HUB_AXICFG_MAX_LEN_MASK);
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(V3D_GET_FIELD(version,
					   V3D_TOP_GR_BRIDGE_MAJOR) != 7);
		V3D_BRIDGE_WRITE(V3D_TOP_GR_BRIDGE_SW_INIT_1,
				 V3D_TOP_GR_BRIDGE_SW_INIT_1_V3D_CLK_108_SW_INIT);
		V3D_BRIDGE_WRITE(V3D_TOP_GR_BRIDGE_SW_INIT_1, 0);
	पूर्ण
पूर्ण

अटल व्योम
v3d_reset_v3d(काष्ठा v3d_dev *v3d)
अणु
	अगर (v3d->reset)
		reset_control_reset(v3d->reset);
	अन्यथा
		v3d_reset_by_bridge(v3d);

	v3d_init_hw_state(v3d);
पूर्ण

व्योम
v3d_reset(काष्ठा v3d_dev *v3d)
अणु
	काष्ठा drm_device *dev = &v3d->drm;

	DRM_DEV_ERROR(dev->dev, "Resetting GPU for hang.\n");
	DRM_DEV_ERROR(dev->dev, "V3D_ERR_STAT: 0x%08x\n",
		      V3D_CORE_READ(0, V3D_ERR_STAT));
	trace_v3d_reset_begin(dev);

	/* XXX: only needed क्रम safe घातerकरोwn, not reset. */
	अगर (false)
		v3d_idle_axi(v3d, 0);

	v3d_idle_gca(v3d);
	v3d_reset_v3d(v3d);

	v3d_mmu_set_page_table(v3d);
	v3d_irq_reset(v3d);

	trace_v3d_reset_end(dev);
पूर्ण

अटल व्योम
v3d_flush_l3(काष्ठा v3d_dev *v3d)
अणु
	अगर (v3d->ver < 41) अणु
		u32 gca_ctrl = V3D_GCA_READ(V3D_GCA_CACHE_CTRL);

		V3D_GCA_WRITE(V3D_GCA_CACHE_CTRL,
			      gca_ctrl | V3D_GCA_CACHE_CTRL_FLUSH);

		अगर (v3d->ver < 33) अणु
			V3D_GCA_WRITE(V3D_GCA_CACHE_CTRL,
				      gca_ctrl & ~V3D_GCA_CACHE_CTRL_FLUSH);
		पूर्ण
	पूर्ण
पूर्ण

/* Invalidates the (पढ़ो-only) L2C cache.  This was the L2 cache क्रम
 * unअगरorms and inकाष्ठाions on V3D 3.2.
 */
अटल व्योम
v3d_invalidate_l2c(काष्ठा v3d_dev *v3d, पूर्णांक core)
अणु
	अगर (v3d->ver > 32)
		वापस;

	V3D_CORE_WRITE(core, V3D_CTL_L2CACTL,
		       V3D_L2CACTL_L2CCLR |
		       V3D_L2CACTL_L2CENA);
पूर्ण

/* Invalidates texture L2 cachelines */
अटल व्योम
v3d_flush_l2t(काष्ठा v3d_dev *v3d, पूर्णांक core)
अणु
	/* While there is a busy bit (V3D_L2TCACTL_L2TFLS), we करोn't
	 * need to रुको क्रम completion beक्रमe dispatching the job --
	 * L2T accesses will be stalled until the flush has completed.
	 * However, we करो need to make sure we करोn't try to trigger a
	 * new flush जबतक the L2_CLEAN queue is trying to
	 * synchronously clean after a job.
	 */
	mutex_lock(&v3d->cache_clean_lock);
	V3D_CORE_WRITE(core, V3D_CTL_L2TCACTL,
		       V3D_L2TCACTL_L2TFLS |
		       V3D_SET_FIELD(V3D_L2TCACTL_FLM_FLUSH, V3D_L2TCACTL_FLM));
	mutex_unlock(&v3d->cache_clean_lock);
पूर्ण

/* Cleans texture L1 and L2 cachelines (writing back dirty data).
 *
 * For cleaning, which happens from the CACHE_CLEAN queue after CSD has
 * executed, we need to make sure that the clean is करोne beक्रमe
 * संकेतing job completion.  So, we synchronously रुको beक्रमe
 * वापसing, and we make sure that L2 invalidates करोn't happen in the
 * meanसमय to confuse our are-we-करोne checks.
 */
व्योम
v3d_clean_caches(काष्ठा v3d_dev *v3d)
अणु
	काष्ठा drm_device *dev = &v3d->drm;
	पूर्णांक core = 0;

	trace_v3d_cache_clean_begin(dev);

	V3D_CORE_WRITE(core, V3D_CTL_L2TCACTL, V3D_L2TCACTL_TMUWCF);
	अगर (रुको_क्रम(!(V3D_CORE_READ(core, V3D_CTL_L2TCACTL) &
		       V3D_L2TCACTL_L2TFLS), 100)) अणु
		DRM_ERROR("Timeout waiting for L1T write combiner flush\n");
	पूर्ण

	mutex_lock(&v3d->cache_clean_lock);
	V3D_CORE_WRITE(core, V3D_CTL_L2TCACTL,
		       V3D_L2TCACTL_L2TFLS |
		       V3D_SET_FIELD(V3D_L2TCACTL_FLM_CLEAN, V3D_L2TCACTL_FLM));

	अगर (रुको_क्रम(!(V3D_CORE_READ(core, V3D_CTL_L2TCACTL) &
		       V3D_L2TCACTL_L2TFLS), 100)) अणु
		DRM_ERROR("Timeout waiting for L2T clean\n");
	पूर्ण

	mutex_unlock(&v3d->cache_clean_lock);

	trace_v3d_cache_clean_end(dev);
पूर्ण

/* Invalidates the slice caches.  These are पढ़ो-only caches. */
अटल व्योम
v3d_invalidate_slices(काष्ठा v3d_dev *v3d, पूर्णांक core)
अणु
	V3D_CORE_WRITE(core, V3D_CTL_SLCACTL,
		       V3D_SET_FIELD(0xf, V3D_SLCACTL_TVCCS) |
		       V3D_SET_FIELD(0xf, V3D_SLCACTL_TDCCS) |
		       V3D_SET_FIELD(0xf, V3D_SLCACTL_UCC) |
		       V3D_SET_FIELD(0xf, V3D_SLCACTL_ICC));
पूर्ण

व्योम
v3d_invalidate_caches(काष्ठा v3d_dev *v3d)
अणु
	/* Invalidate the caches from the outside in.  That way अगर
	 * another CL's concurrent use of nearby memory were to pull
	 * an invalidated cacheline back in, we wouldn't leave stale
	 * data in the inner cache.
	 */
	v3d_flush_l3(v3d);
	v3d_invalidate_l2c(v3d, 0);
	v3d_flush_l2t(v3d, 0);
	v3d_invalidate_slices(v3d, 0);
पूर्ण

/* Takes the reservation lock on all the BOs being referenced, so that
 * at queue submit समय we can update the reservations.
 *
 * We करोn't lock the RCL the tile alloc/state BOs, or overflow memory
 * (all of which are on exec->unref_list).  They're entirely निजी
 * to v3d, so we करोn't attach dma-buf fences to them.
 */
अटल पूर्णांक
v3d_lock_bo_reservations(काष्ठा v3d_job *job,
			 काष्ठा ww_acquire_ctx *acquire_ctx)
अणु
	पूर्णांक i, ret;

	ret = drm_gem_lock_reservations(job->bo, job->bo_count, acquire_ctx);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < job->bo_count; i++) अणु
		ret = drm_gem_fence_array_add_implicit(&job->deps,
						       job->bo[i], true);
		अगर (ret) अणु
			drm_gem_unlock_reservations(job->bo, job->bo_count,
						    acquire_ctx);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * v3d_lookup_bos() - Sets up job->bo[] with the GEM objects
 * referenced by the job.
 * @dev: DRM device
 * @file_priv: DRM file क्रम this fd
 * @job: V3D job being set up
 * @bo_handles: GEM handles
 * @bo_count: Number of GEM handles passed in
 *
 * The command validator needs to reference BOs by their index within
 * the submitted job's BO list.  This does the validation of the job's
 * BO list and reference counting क्रम the lअगरeसमय of the job.
 *
 * Note that this function करोesn't need to unreference the BOs on
 * failure, because that will happen at v3d_exec_cleanup() समय.
 */
अटल पूर्णांक
v3d_lookup_bos(काष्ठा drm_device *dev,
	       काष्ठा drm_file *file_priv,
	       काष्ठा v3d_job *job,
	       u64 bo_handles,
	       u32 bo_count)
अणु
	u32 *handles;
	पूर्णांक ret = 0;
	पूर्णांक i;

	job->bo_count = bo_count;

	अगर (!job->bo_count) अणु
		/* See comment on bo_index क्रम why we have to check
		 * this.
		 */
		DRM_DEBUG("Rendering requires BOs\n");
		वापस -EINVAL;
	पूर्ण

	job->bo = kvदो_स्मृति_array(job->bo_count,
				 माप(काष्ठा drm_gem_cma_object *),
				 GFP_KERNEL | __GFP_ZERO);
	अगर (!job->bo) अणु
		DRM_DEBUG("Failed to allocate validated BO pointers\n");
		वापस -ENOMEM;
	पूर्ण

	handles = kvदो_स्मृति_array(job->bo_count, माप(u32), GFP_KERNEL);
	अगर (!handles) अणु
		ret = -ENOMEM;
		DRM_DEBUG("Failed to allocate incoming GEM handles\n");
		जाओ fail;
	पूर्ण

	अगर (copy_from_user(handles,
			   (व्योम __user *)(uपूर्णांकptr_t)bo_handles,
			   job->bo_count * माप(u32))) अणु
		ret = -EFAULT;
		DRM_DEBUG("Failed to copy in GEM handles\n");
		जाओ fail;
	पूर्ण

	spin_lock(&file_priv->table_lock);
	क्रम (i = 0; i < job->bo_count; i++) अणु
		काष्ठा drm_gem_object *bo = idr_find(&file_priv->object_idr,
						     handles[i]);
		अगर (!bo) अणु
			DRM_DEBUG("Failed to look up GEM BO %d: %d\n",
				  i, handles[i]);
			ret = -ENOENT;
			spin_unlock(&file_priv->table_lock);
			जाओ fail;
		पूर्ण
		drm_gem_object_get(bo);
		job->bo[i] = bo;
	पूर्ण
	spin_unlock(&file_priv->table_lock);

fail:
	kvमुक्त(handles);
	वापस ret;
पूर्ण

अटल व्योम
v3d_job_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा v3d_job *job = container_of(ref, काष्ठा v3d_job, refcount);
	अचिन्हित दीर्घ index;
	काष्ठा dma_fence *fence;
	पूर्णांक i;

	क्रम (i = 0; i < job->bo_count; i++) अणु
		अगर (job->bo[i])
			drm_gem_object_put(job->bo[i]);
	पूर्ण
	kvमुक्त(job->bo);

	xa_क्रम_each(&job->deps, index, fence) अणु
		dma_fence_put(fence);
	पूर्ण
	xa_destroy(&job->deps);

	dma_fence_put(job->irq_fence);
	dma_fence_put(job->करोne_fence);

	pm_runसमय_mark_last_busy(job->v3d->drm.dev);
	pm_runसमय_put_स्वतःsuspend(job->v3d->drm.dev);

	kमुक्त(job);
पूर्ण

अटल व्योम
v3d_render_job_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा v3d_render_job *job = container_of(ref, काष्ठा v3d_render_job,
						  base.refcount);
	काष्ठा v3d_bo *bo, *save;

	list_क्रम_each_entry_safe(bo, save, &job->unref_list, unref_head) अणु
		drm_gem_object_put(&bo->base.base);
	पूर्ण

	v3d_job_मुक्त(ref);
पूर्ण

व्योम v3d_job_put(काष्ठा v3d_job *job)
अणु
	kref_put(&job->refcount, job->मुक्त);
पूर्ण

पूर्णांक
v3d_रुको_bo_ioctl(काष्ठा drm_device *dev, व्योम *data,
		  काष्ठा drm_file *file_priv)
अणु
	पूर्णांक ret;
	काष्ठा drm_v3d_रुको_bo *args = data;
	kसमय_प्रकार start = kसमय_get();
	u64 delta_ns;
	अचिन्हित दीर्घ समयout_jअगरfies =
		nsecs_to_jअगरfies_समयout(args->समयout_ns);

	अगर (args->pad != 0)
		वापस -EINVAL;

	ret = drm_gem_dma_resv_रुको(file_priv, args->handle,
					      true, समयout_jअगरfies);

	/* Decrement the user's समयout, in हाल we got पूर्णांकerrupted
	 * such that the ioctl will be restarted.
	 */
	delta_ns = kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(), start));
	अगर (delta_ns < args->समयout_ns)
		args->समयout_ns -= delta_ns;
	अन्यथा
		args->समयout_ns = 0;

	/* Asked to रुको beyond the jअगरfie/scheduler precision? */
	अगर (ret == -ETIME && args->समयout_ns)
		ret = -EAGAIN;

	वापस ret;
पूर्ण

अटल पूर्णांक
v3d_job_init(काष्ठा v3d_dev *v3d, काष्ठा drm_file *file_priv,
	     काष्ठा v3d_job *job, व्योम (*मुक्त)(काष्ठा kref *ref),
	     u32 in_sync)
अणु
	काष्ठा dma_fence *in_fence = शून्य;
	पूर्णांक ret;

	job->v3d = v3d;
	job->मुक्त = मुक्त;

	ret = pm_runसमय_get_sync(v3d->drm.dev);
	अगर (ret < 0)
		वापस ret;

	xa_init_flags(&job->deps, XA_FLAGS_ALLOC);

	ret = drm_syncobj_find_fence(file_priv, in_sync, 0, 0, &in_fence);
	अगर (ret == -EINVAL)
		जाओ fail;

	ret = drm_gem_fence_array_add(&job->deps, in_fence);
	अगर (ret)
		जाओ fail;

	kref_init(&job->refcount);

	वापस 0;
fail:
	xa_destroy(&job->deps);
	pm_runसमय_put_स्वतःsuspend(v3d->drm.dev);
	वापस ret;
पूर्ण

अटल पूर्णांक
v3d_push_job(काष्ठा v3d_file_priv *v3d_priv,
	     काष्ठा v3d_job *job, क्रमागत v3d_queue queue)
अणु
	पूर्णांक ret;

	ret = drm_sched_job_init(&job->base, &v3d_priv->sched_entity[queue],
				 v3d_priv);
	अगर (ret)
		वापस ret;

	job->करोne_fence = dma_fence_get(&job->base.s_fence->finished);

	/* put by scheduler job completion */
	kref_get(&job->refcount);

	drm_sched_entity_push_job(&job->base, &v3d_priv->sched_entity[queue]);

	वापस 0;
पूर्ण

अटल व्योम
v3d_attach_fences_and_unlock_reservation(काष्ठा drm_file *file_priv,
					 काष्ठा v3d_job *job,
					 काष्ठा ww_acquire_ctx *acquire_ctx,
					 u32 out_sync,
					 काष्ठा dma_fence *करोne_fence)
अणु
	काष्ठा drm_syncobj *sync_out;
	पूर्णांक i;

	क्रम (i = 0; i < job->bo_count; i++) अणु
		/* XXX: Use shared fences क्रम पढ़ो-only objects. */
		dma_resv_add_excl_fence(job->bo[i]->resv,
						  job->करोne_fence);
	पूर्ण

	drm_gem_unlock_reservations(job->bo, job->bo_count, acquire_ctx);

	/* Update the वापस sync object क्रम the job */
	sync_out = drm_syncobj_find(file_priv, out_sync);
	अगर (sync_out) अणु
		drm_syncobj_replace_fence(sync_out, करोne_fence);
		drm_syncobj_put(sync_out);
	पूर्ण
पूर्ण

/**
 * v3d_submit_cl_ioctl() - Submits a job (frame) to the V3D.
 * @dev: DRM device
 * @data: ioctl argument
 * @file_priv: DRM file क्रम this fd
 *
 * This is the मुख्य entrypoपूर्णांक क्रम userspace to submit a 3D frame to
 * the GPU.  Userspace provides the binner command list (अगर
 * applicable), and the kernel sets up the render command list to draw
 * to the framebuffer described in the ioctl, using the command lists
 * that the 3D engine's binner will produce.
 */
पूर्णांक
v3d_submit_cl_ioctl(काष्ठा drm_device *dev, व्योम *data,
		    काष्ठा drm_file *file_priv)
अणु
	काष्ठा v3d_dev *v3d = to_v3d_dev(dev);
	काष्ठा v3d_file_priv *v3d_priv = file_priv->driver_priv;
	काष्ठा drm_v3d_submit_cl *args = data;
	काष्ठा v3d_bin_job *bin = शून्य;
	काष्ठा v3d_render_job *render;
	काष्ठा v3d_job *clean_job = शून्य;
	काष्ठा v3d_job *last_job;
	काष्ठा ww_acquire_ctx acquire_ctx;
	पूर्णांक ret = 0;

	trace_v3d_submit_cl_ioctl(&v3d->drm, args->rcl_start, args->rcl_end);

	अगर (args->flags != 0 &&
	    args->flags != DRM_V3D_SUBMIT_CL_FLUSH_CACHE) अणु
		DRM_INFO("invalid flags: %d\n", args->flags);
		वापस -EINVAL;
	पूर्ण

	render = kसुस्मृति(1, माप(*render), GFP_KERNEL);
	अगर (!render)
		वापस -ENOMEM;

	render->start = args->rcl_start;
	render->end = args->rcl_end;
	INIT_LIST_HEAD(&render->unref_list);

	ret = v3d_job_init(v3d, file_priv, &render->base,
			   v3d_render_job_मुक्त, args->in_sync_rcl);
	अगर (ret) अणु
		kमुक्त(render);
		वापस ret;
	पूर्ण

	अगर (args->bcl_start != args->bcl_end) अणु
		bin = kसुस्मृति(1, माप(*bin), GFP_KERNEL);
		अगर (!bin) अणु
			v3d_job_put(&render->base);
			वापस -ENOMEM;
		पूर्ण

		ret = v3d_job_init(v3d, file_priv, &bin->base,
				   v3d_job_मुक्त, args->in_sync_bcl);
		अगर (ret) अणु
			v3d_job_put(&render->base);
			kमुक्त(bin);
			वापस ret;
		पूर्ण

		bin->start = args->bcl_start;
		bin->end = args->bcl_end;
		bin->qma = args->qma;
		bin->qms = args->qms;
		bin->qts = args->qts;
		bin->render = render;
	पूर्ण

	अगर (args->flags & DRM_V3D_SUBMIT_CL_FLUSH_CACHE) अणु
		clean_job = kसुस्मृति(1, माप(*clean_job), GFP_KERNEL);
		अगर (!clean_job) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		ret = v3d_job_init(v3d, file_priv, clean_job, v3d_job_मुक्त, 0);
		अगर (ret) अणु
			kमुक्त(clean_job);
			clean_job = शून्य;
			जाओ fail;
		पूर्ण

		last_job = clean_job;
	पूर्ण अन्यथा अणु
		last_job = &render->base;
	पूर्ण

	ret = v3d_lookup_bos(dev, file_priv, last_job,
			     args->bo_handles, args->bo_handle_count);
	अगर (ret)
		जाओ fail;

	ret = v3d_lock_bo_reservations(last_job, &acquire_ctx);
	अगर (ret)
		जाओ fail;

	mutex_lock(&v3d->sched_lock);
	अगर (bin) अणु
		ret = v3d_push_job(v3d_priv, &bin->base, V3D_BIN);
		अगर (ret)
			जाओ fail_unreserve;

		ret = drm_gem_fence_array_add(&render->base.deps,
					      dma_fence_get(bin->base.करोne_fence));
		अगर (ret)
			जाओ fail_unreserve;
	पूर्ण

	ret = v3d_push_job(v3d_priv, &render->base, V3D_RENDER);
	अगर (ret)
		जाओ fail_unreserve;

	अगर (clean_job) अणु
		काष्ठा dma_fence *render_fence =
			dma_fence_get(render->base.करोne_fence);
		ret = drm_gem_fence_array_add(&clean_job->deps, render_fence);
		अगर (ret)
			जाओ fail_unreserve;
		ret = v3d_push_job(v3d_priv, clean_job, V3D_CACHE_CLEAN);
		अगर (ret)
			जाओ fail_unreserve;
	पूर्ण

	mutex_unlock(&v3d->sched_lock);

	v3d_attach_fences_and_unlock_reservation(file_priv,
						 last_job,
						 &acquire_ctx,
						 args->out_sync,
						 last_job->करोne_fence);

	अगर (bin)
		v3d_job_put(&bin->base);
	v3d_job_put(&render->base);
	अगर (clean_job)
		v3d_job_put(clean_job);

	वापस 0;

fail_unreserve:
	mutex_unlock(&v3d->sched_lock);
	drm_gem_unlock_reservations(last_job->bo,
				    last_job->bo_count, &acquire_ctx);
fail:
	अगर (bin)
		v3d_job_put(&bin->base);
	v3d_job_put(&render->base);
	अगर (clean_job)
		v3d_job_put(clean_job);

	वापस ret;
पूर्ण

/**
 * v3d_submit_tfu_ioctl() - Submits a TFU (texture क्रमmatting) job to the V3D.
 * @dev: DRM device
 * @data: ioctl argument
 * @file_priv: DRM file क्रम this fd
 *
 * Userspace provides the रेजिस्टर setup क्रम the TFU, which we करोn't
 * need to validate since the TFU is behind the MMU.
 */
पूर्णांक
v3d_submit_tfu_ioctl(काष्ठा drm_device *dev, व्योम *data,
		     काष्ठा drm_file *file_priv)
अणु
	काष्ठा v3d_dev *v3d = to_v3d_dev(dev);
	काष्ठा v3d_file_priv *v3d_priv = file_priv->driver_priv;
	काष्ठा drm_v3d_submit_tfu *args = data;
	काष्ठा v3d_tfu_job *job;
	काष्ठा ww_acquire_ctx acquire_ctx;
	पूर्णांक ret = 0;

	trace_v3d_submit_tfu_ioctl(&v3d->drm, args->iia);

	job = kसुस्मृति(1, माप(*job), GFP_KERNEL);
	अगर (!job)
		वापस -ENOMEM;

	ret = v3d_job_init(v3d, file_priv, &job->base,
			   v3d_job_मुक्त, args->in_sync);
	अगर (ret) अणु
		kमुक्त(job);
		वापस ret;
	पूर्ण

	job->base.bo = kसुस्मृति(ARRAY_SIZE(args->bo_handles),
			       माप(*job->base.bo), GFP_KERNEL);
	अगर (!job->base.bo) अणु
		v3d_job_put(&job->base);
		वापस -ENOMEM;
	पूर्ण

	job->args = *args;

	spin_lock(&file_priv->table_lock);
	क्रम (job->base.bo_count = 0;
	     job->base.bo_count < ARRAY_SIZE(args->bo_handles);
	     job->base.bo_count++) अणु
		काष्ठा drm_gem_object *bo;

		अगर (!args->bo_handles[job->base.bo_count])
			अवरोध;

		bo = idr_find(&file_priv->object_idr,
			      args->bo_handles[job->base.bo_count]);
		अगर (!bo) अणु
			DRM_DEBUG("Failed to look up GEM BO %d: %d\n",
				  job->base.bo_count,
				  args->bo_handles[job->base.bo_count]);
			ret = -ENOENT;
			spin_unlock(&file_priv->table_lock);
			जाओ fail;
		पूर्ण
		drm_gem_object_get(bo);
		job->base.bo[job->base.bo_count] = bo;
	पूर्ण
	spin_unlock(&file_priv->table_lock);

	ret = v3d_lock_bo_reservations(&job->base, &acquire_ctx);
	अगर (ret)
		जाओ fail;

	mutex_lock(&v3d->sched_lock);
	ret = v3d_push_job(v3d_priv, &job->base, V3D_TFU);
	अगर (ret)
		जाओ fail_unreserve;
	mutex_unlock(&v3d->sched_lock);

	v3d_attach_fences_and_unlock_reservation(file_priv,
						 &job->base, &acquire_ctx,
						 args->out_sync,
						 job->base.करोne_fence);

	v3d_job_put(&job->base);

	वापस 0;

fail_unreserve:
	mutex_unlock(&v3d->sched_lock);
	drm_gem_unlock_reservations(job->base.bo, job->base.bo_count,
				    &acquire_ctx);
fail:
	v3d_job_put(&job->base);

	वापस ret;
पूर्ण

/**
 * v3d_submit_csd_ioctl() - Submits a CSD (texture क्रमmatting) job to the V3D.
 * @dev: DRM device
 * @data: ioctl argument
 * @file_priv: DRM file क्रम this fd
 *
 * Userspace provides the रेजिस्टर setup क्रम the CSD, which we करोn't
 * need to validate since the CSD is behind the MMU.
 */
पूर्णांक
v3d_submit_csd_ioctl(काष्ठा drm_device *dev, व्योम *data,
		     काष्ठा drm_file *file_priv)
अणु
	काष्ठा v3d_dev *v3d = to_v3d_dev(dev);
	काष्ठा v3d_file_priv *v3d_priv = file_priv->driver_priv;
	काष्ठा drm_v3d_submit_csd *args = data;
	काष्ठा v3d_csd_job *job;
	काष्ठा v3d_job *clean_job;
	काष्ठा ww_acquire_ctx acquire_ctx;
	पूर्णांक ret;

	trace_v3d_submit_csd_ioctl(&v3d->drm, args->cfg[5], args->cfg[6]);

	अगर (!v3d_has_csd(v3d)) अणु
		DRM_DEBUG("Attempting CSD submit on non-CSD hardware\n");
		वापस -EINVAL;
	पूर्ण

	job = kसुस्मृति(1, माप(*job), GFP_KERNEL);
	अगर (!job)
		वापस -ENOMEM;

	ret = v3d_job_init(v3d, file_priv, &job->base,
			   v3d_job_मुक्त, args->in_sync);
	अगर (ret) अणु
		kमुक्त(job);
		वापस ret;
	पूर्ण

	clean_job = kसुस्मृति(1, माप(*clean_job), GFP_KERNEL);
	अगर (!clean_job) अणु
		v3d_job_put(&job->base);
		kमुक्त(job);
		वापस -ENOMEM;
	पूर्ण

	ret = v3d_job_init(v3d, file_priv, clean_job, v3d_job_मुक्त, 0);
	अगर (ret) अणु
		v3d_job_put(&job->base);
		kमुक्त(clean_job);
		वापस ret;
	पूर्ण

	job->args = *args;

	ret = v3d_lookup_bos(dev, file_priv, clean_job,
			     args->bo_handles, args->bo_handle_count);
	अगर (ret)
		जाओ fail;

	ret = v3d_lock_bo_reservations(clean_job, &acquire_ctx);
	अगर (ret)
		जाओ fail;

	mutex_lock(&v3d->sched_lock);
	ret = v3d_push_job(v3d_priv, &job->base, V3D_CSD);
	अगर (ret)
		जाओ fail_unreserve;

	ret = drm_gem_fence_array_add(&clean_job->deps,
				      dma_fence_get(job->base.करोne_fence));
	अगर (ret)
		जाओ fail_unreserve;

	ret = v3d_push_job(v3d_priv, clean_job, V3D_CACHE_CLEAN);
	अगर (ret)
		जाओ fail_unreserve;
	mutex_unlock(&v3d->sched_lock);

	v3d_attach_fences_and_unlock_reservation(file_priv,
						 clean_job,
						 &acquire_ctx,
						 args->out_sync,
						 clean_job->करोne_fence);

	v3d_job_put(&job->base);
	v3d_job_put(clean_job);

	वापस 0;

fail_unreserve:
	mutex_unlock(&v3d->sched_lock);
	drm_gem_unlock_reservations(clean_job->bo, clean_job->bo_count,
				    &acquire_ctx);
fail:
	v3d_job_put(&job->base);
	v3d_job_put(clean_job);

	वापस ret;
पूर्ण

पूर्णांक
v3d_gem_init(काष्ठा drm_device *dev)
अणु
	काष्ठा v3d_dev *v3d = to_v3d_dev(dev);
	u32 pt_size = 4096 * 1024;
	पूर्णांक ret, i;

	क्रम (i = 0; i < V3D_MAX_QUEUES; i++)
		v3d->queue[i].fence_context = dma_fence_context_alloc(1);

	spin_lock_init(&v3d->mm_lock);
	spin_lock_init(&v3d->job_lock);
	mutex_init(&v3d->bo_lock);
	mutex_init(&v3d->reset_lock);
	mutex_init(&v3d->sched_lock);
	mutex_init(&v3d->cache_clean_lock);

	/* Note: We करोn't allocate address 0.  Various bits of HW
	 * treat 0 as special, such as the occlusion query counters
	 * where 0 means "disabled".
	 */
	drm_mm_init(&v3d->mm, 1, pt_size / माप(u32) - 1);

	v3d->pt = dma_alloc_wc(v3d->drm.dev, pt_size,
			       &v3d->pt_paddr,
			       GFP_KERNEL | __GFP_NOWARN | __GFP_ZERO);
	अगर (!v3d->pt) अणु
		drm_mm_takeकरोwn(&v3d->mm);
		dev_err(v3d->drm.dev,
			"Failed to allocate page tables. "
			"Please ensure you have CMA enabled.\n");
		वापस -ENOMEM;
	पूर्ण

	v3d_init_hw_state(v3d);
	v3d_mmu_set_page_table(v3d);

	ret = v3d_sched_init(v3d);
	अगर (ret) अणु
		drm_mm_takeकरोwn(&v3d->mm);
		dma_मुक्त_coherent(v3d->drm.dev, 4096 * 1024, (व्योम *)v3d->pt,
				  v3d->pt_paddr);
	पूर्ण

	वापस 0;
पूर्ण

व्योम
v3d_gem_destroy(काष्ठा drm_device *dev)
अणु
	काष्ठा v3d_dev *v3d = to_v3d_dev(dev);

	v3d_sched_fini(v3d);

	/* Waiting क्रम jobs to finish would need to be करोne beक्रमe
	 * unरेजिस्टरing V3D.
	 */
	WARN_ON(v3d->bin_job);
	WARN_ON(v3d->render_job);

	drm_mm_takeकरोwn(&v3d->mm);

	dma_मुक्त_coherent(v3d->drm.dev, 4096 * 1024, (व्योम *)v3d->pt,
			  v3d->pt_paddr);
पूर्ण
