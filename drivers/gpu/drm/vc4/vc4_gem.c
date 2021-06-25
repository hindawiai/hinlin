<शैली गुरु>
/*
 * Copyright तऊ 2014 Broadcom
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/dma-fence-array.h>

#समावेश <drm/drm_syncobj.h>

#समावेश "uapi/drm/vc4_drm.h"
#समावेश "vc4_drv.h"
#समावेश "vc4_regs.h"
#समावेश "vc4_trace.h"

अटल व्योम
vc4_queue_hangcheck(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	mod_समयr(&vc4->hangcheck.समयr,
		  round_jअगरfies_up(jअगरfies + msecs_to_jअगरfies(100)));
पूर्ण

काष्ठा vc4_hang_state अणु
	काष्ठा drm_vc4_get_hang_state user_state;

	u32 bo_count;
	काष्ठा drm_gem_object **bo;
पूर्ण;

अटल व्योम
vc4_मुक्त_hang_state(काष्ठा drm_device *dev, काष्ठा vc4_hang_state *state)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < state->user_state.bo_count; i++)
		drm_gem_object_put(state->bo[i]);

	kमुक्त(state);
पूर्ण

पूर्णांक
vc4_get_hang_state_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vc4_get_hang_state *get_state = data;
	काष्ठा drm_vc4_get_hang_state_bo *bo_state;
	काष्ठा vc4_hang_state *kernel_state;
	काष्ठा drm_vc4_get_hang_state *state;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	अचिन्हित दीर्घ irqflags;
	u32 i;
	पूर्णांक ret = 0;

	अगर (!vc4->v3d) अणु
		DRM_DEBUG("VC4_GET_HANG_STATE with no VC4 V3D probed\n");
		वापस -ENODEV;
	पूर्ण

	spin_lock_irqsave(&vc4->job_lock, irqflags);
	kernel_state = vc4->hang_state;
	अगर (!kernel_state) अणु
		spin_unlock_irqrestore(&vc4->job_lock, irqflags);
		वापस -ENOENT;
	पूर्ण
	state = &kernel_state->user_state;

	/* If the user's array isn't big enough, just वापस the
	 * required array size.
	 */
	अगर (get_state->bo_count < state->bo_count) अणु
		get_state->bo_count = state->bo_count;
		spin_unlock_irqrestore(&vc4->job_lock, irqflags);
		वापस 0;
	पूर्ण

	vc4->hang_state = शून्य;
	spin_unlock_irqrestore(&vc4->job_lock, irqflags);

	/* Save the user's BO pointer, so we don't stomp it with the स_नकल. */
	state->bo = get_state->bo;
	स_नकल(get_state, state, माप(*state));

	bo_state = kसुस्मृति(state->bo_count, माप(*bo_state), GFP_KERNEL);
	अगर (!bo_state) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	क्रम (i = 0; i < state->bo_count; i++) अणु
		काष्ठा vc4_bo *vc4_bo = to_vc4_bo(kernel_state->bo[i]);
		u32 handle;

		ret = drm_gem_handle_create(file_priv, kernel_state->bo[i],
					    &handle);

		अगर (ret) अणु
			state->bo_count = i;
			जाओ err_delete_handle;
		पूर्ण
		bo_state[i].handle = handle;
		bo_state[i].paddr = vc4_bo->base.paddr;
		bo_state[i].size = vc4_bo->base.base.size;
	पूर्ण

	अगर (copy_to_user(u64_to_user_ptr(get_state->bo),
			 bo_state,
			 state->bo_count * माप(*bo_state)))
		ret = -EFAULT;

err_delete_handle:
	अगर (ret) अणु
		क्रम (i = 0; i < state->bo_count; i++)
			drm_gem_handle_delete(file_priv, bo_state[i].handle);
	पूर्ण

err_मुक्त:
	vc4_मुक्त_hang_state(dev, kernel_state);
	kमुक्त(bo_state);

	वापस ret;
पूर्ण

अटल व्योम
vc4_save_hang_state(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा drm_vc4_get_hang_state *state;
	काष्ठा vc4_hang_state *kernel_state;
	काष्ठा vc4_exec_info *exec[2];
	काष्ठा vc4_bo *bo;
	अचिन्हित दीर्घ irqflags;
	अचिन्हित पूर्णांक i, j, k, unref_list_count;

	kernel_state = kसुस्मृति(1, माप(*kernel_state), GFP_KERNEL);
	अगर (!kernel_state)
		वापस;

	state = &kernel_state->user_state;

	spin_lock_irqsave(&vc4->job_lock, irqflags);
	exec[0] = vc4_first_bin_job(vc4);
	exec[1] = vc4_first_render_job(vc4);
	अगर (!exec[0] && !exec[1]) अणु
		spin_unlock_irqrestore(&vc4->job_lock, irqflags);
		वापस;
	पूर्ण

	/* Get the bos from both binner and renderer पूर्णांकo hang state. */
	state->bo_count = 0;
	क्रम (i = 0; i < 2; i++) अणु
		अगर (!exec[i])
			जारी;

		unref_list_count = 0;
		list_क्रम_each_entry(bo, &exec[i]->unref_list, unref_head)
			unref_list_count++;
		state->bo_count += exec[i]->bo_count + unref_list_count;
	पूर्ण

	kernel_state->bo = kसुस्मृति(state->bo_count,
				   माप(*kernel_state->bo), GFP_ATOMIC);

	अगर (!kernel_state->bo) अणु
		spin_unlock_irqrestore(&vc4->job_lock, irqflags);
		वापस;
	पूर्ण

	k = 0;
	क्रम (i = 0; i < 2; i++) अणु
		अगर (!exec[i])
			जारी;

		क्रम (j = 0; j < exec[i]->bo_count; j++) अणु
			bo = to_vc4_bo(&exec[i]->bo[j]->base);

			/* Retain BOs just in हाल they were marked purgeable.
			 * This prevents the BO from being purged beक्रमe
			 * someone had a chance to dump the hang state.
			 */
			WARN_ON(!refcount_पढ़ो(&bo->usecnt));
			refcount_inc(&bo->usecnt);
			drm_gem_object_get(&exec[i]->bo[j]->base);
			kernel_state->bo[k++] = &exec[i]->bo[j]->base;
		पूर्ण

		list_क्रम_each_entry(bo, &exec[i]->unref_list, unref_head) अणु
			/* No need to retain BOs coming from the ->unref_list
			 * because they are naturally unpurgeable.
			 */
			drm_gem_object_get(&bo->base.base);
			kernel_state->bo[k++] = &bo->base.base;
		पूर्ण
	पूर्ण

	WARN_ON_ONCE(k != state->bo_count);

	अगर (exec[0])
		state->start_bin = exec[0]->ct0ca;
	अगर (exec[1])
		state->start_render = exec[1]->ct1ca;

	spin_unlock_irqrestore(&vc4->job_lock, irqflags);

	state->ct0ca = V3D_READ(V3D_CTNCA(0));
	state->ct0ea = V3D_READ(V3D_CTNEA(0));

	state->ct1ca = V3D_READ(V3D_CTNCA(1));
	state->ct1ea = V3D_READ(V3D_CTNEA(1));

	state->ct0cs = V3D_READ(V3D_CTNCS(0));
	state->ct1cs = V3D_READ(V3D_CTNCS(1));

	state->ct0ra0 = V3D_READ(V3D_CT00RA0);
	state->ct1ra0 = V3D_READ(V3D_CT01RA0);

	state->bpca = V3D_READ(V3D_BPCA);
	state->bpcs = V3D_READ(V3D_BPCS);
	state->bpoa = V3D_READ(V3D_BPOA);
	state->bpos = V3D_READ(V3D_BPOS);

	state->vpmbase = V3D_READ(V3D_VPMBASE);

	state->dbge = V3D_READ(V3D_DBGE);
	state->fdbgo = V3D_READ(V3D_FDBGO);
	state->fdbgb = V3D_READ(V3D_FDBGB);
	state->fdbgr = V3D_READ(V3D_FDBGR);
	state->fdbgs = V3D_READ(V3D_FDBGS);
	state->errstat = V3D_READ(V3D_ERRSTAT);

	/* We need to turn purgeable BOs पूर्णांकo unpurgeable ones so that
	 * userspace has a chance to dump the hang state beक्रमe the kernel
	 * decides to purge those BOs.
	 * Note that BO consistency at dump समय cannot be guaranteed. For
	 * example, अगर the owner of these BOs decides to re-use them or mark
	 * them purgeable again there's nothing we can करो to prevent it.
	 */
	क्रम (i = 0; i < kernel_state->user_state.bo_count; i++) अणु
		काष्ठा vc4_bo *bo = to_vc4_bo(kernel_state->bo[i]);

		अगर (bo->madv == __VC4_MADV_NOTSUPP)
			जारी;

		mutex_lock(&bo->madv_lock);
		अगर (!WARN_ON(bo->madv == __VC4_MADV_PURGED))
			bo->madv = VC4_MADV_WILLNEED;
		refcount_dec(&bo->usecnt);
		mutex_unlock(&bo->madv_lock);
	पूर्ण

	spin_lock_irqsave(&vc4->job_lock, irqflags);
	अगर (vc4->hang_state) अणु
		spin_unlock_irqrestore(&vc4->job_lock, irqflags);
		vc4_मुक्त_hang_state(dev, kernel_state);
	पूर्ण अन्यथा अणु
		vc4->hang_state = kernel_state;
		spin_unlock_irqrestore(&vc4->job_lock, irqflags);
	पूर्ण
पूर्ण

अटल व्योम
vc4_reset(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	DRM_INFO("Resetting GPU.\n");

	mutex_lock(&vc4->घातer_lock);
	अगर (vc4->घातer_refcount) अणु
		/* Power the device off and back on the by dropping the
		 * reference on runसमय PM.
		 */
		pm_runसमय_put_sync_suspend(&vc4->v3d->pdev->dev);
		pm_runसमय_get_sync(&vc4->v3d->pdev->dev);
	पूर्ण
	mutex_unlock(&vc4->घातer_lock);

	vc4_irq_reset(dev);

	/* Rearm the hangcheck -- another job might have been रुकोing
	 * क्रम our hung one to get kicked off, and vc4_irq_reset()
	 * would have started it.
	 */
	vc4_queue_hangcheck(dev);
पूर्ण

अटल व्योम
vc4_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vc4_dev *vc4 =
		container_of(work, काष्ठा vc4_dev, hangcheck.reset_work);

	vc4_save_hang_state(&vc4->base);

	vc4_reset(&vc4->base);
पूर्ण

अटल व्योम
vc4_hangcheck_elapsed(काष्ठा समयr_list *t)
अणु
	काष्ठा vc4_dev *vc4 = from_समयr(vc4, t, hangcheck.समयr);
	काष्ठा drm_device *dev = &vc4->base;
	uपूर्णांक32_t ct0ca, ct1ca;
	अचिन्हित दीर्घ irqflags;
	काष्ठा vc4_exec_info *bin_exec, *render_exec;

	spin_lock_irqsave(&vc4->job_lock, irqflags);

	bin_exec = vc4_first_bin_job(vc4);
	render_exec = vc4_first_render_job(vc4);

	/* If idle, we can stop watching क्रम hangs. */
	अगर (!bin_exec && !render_exec) अणु
		spin_unlock_irqrestore(&vc4->job_lock, irqflags);
		वापस;
	पूर्ण

	ct0ca = V3D_READ(V3D_CTNCA(0));
	ct1ca = V3D_READ(V3D_CTNCA(1));

	/* If we've made any progress in execution, rearm the समयr
	 * and रुको.
	 */
	अगर ((bin_exec && ct0ca != bin_exec->last_ct0ca) ||
	    (render_exec && ct1ca != render_exec->last_ct1ca)) अणु
		अगर (bin_exec)
			bin_exec->last_ct0ca = ct0ca;
		अगर (render_exec)
			render_exec->last_ct1ca = ct1ca;
		spin_unlock_irqrestore(&vc4->job_lock, irqflags);
		vc4_queue_hangcheck(dev);
		वापस;
	पूर्ण

	spin_unlock_irqrestore(&vc4->job_lock, irqflags);

	/* We've gone too दीर्घ with no progress, reset.  This has to
	 * be करोne from a work काष्ठा, since resetting can sleep and
	 * this समयr hook isn't allowed to.
	 */
	schedule_work(&vc4->hangcheck.reset_work);
पूर्ण

अटल व्योम
submit_cl(काष्ठा drm_device *dev, uपूर्णांक32_t thपढ़ो, uपूर्णांक32_t start, uपूर्णांक32_t end)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	/* Set the current and end address of the control list.
	 * Writing the end रेजिस्टर is what starts the job.
	 */
	V3D_WRITE(V3D_CTNCA(thपढ़ो), start);
	V3D_WRITE(V3D_CTNEA(thपढ़ो), end);
पूर्ण

पूर्णांक
vc4_रुको_क्रम_seqno(काष्ठा drm_device *dev, uपूर्णांक64_t seqno, uपूर्णांक64_t समयout_ns,
		   bool पूर्णांकerruptible)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ समयout_expire;
	DEFINE_WAIT(रुको);

	अगर (vc4->finished_seqno >= seqno)
		वापस 0;

	अगर (समयout_ns == 0)
		वापस -ETIME;

	समयout_expire = jअगरfies + nsecs_to_jअगरfies(समयout_ns);

	trace_vc4_रुको_क्रम_seqno_begin(dev, seqno, समयout_ns);
	क्रम (;;) अणु
		prepare_to_रुको(&vc4->job_रुको_queue, &रुको,
				पूर्णांकerruptible ? TASK_INTERRUPTIBLE :
				TASK_UNINTERRUPTIBLE);

		अगर (पूर्णांकerruptible && संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		अगर (vc4->finished_seqno >= seqno)
			अवरोध;

		अगर (समयout_ns != ~0ull) अणु
			अगर (समय_after_eq(jअगरfies, समयout_expire)) अणु
				ret = -ETIME;
				अवरोध;
			पूर्ण
			schedule_समयout(समयout_expire - jअगरfies);
		पूर्ण अन्यथा अणु
			schedule();
		पूर्ण
	पूर्ण

	finish_रुको(&vc4->job_रुको_queue, &रुको);
	trace_vc4_रुको_क्रम_seqno_end(dev, seqno);

	वापस ret;
पूर्ण

अटल व्योम
vc4_flush_caches(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	/* Flush the GPU L2 caches.  These caches sit on top of प्रणाली
	 * L3 (the 128kb or so shared with the CPU), and are
	 * non-allocating in the L3.
	 */
	V3D_WRITE(V3D_L2CACTL,
		  V3D_L2CACTL_L2CCLR);

	V3D_WRITE(V3D_SLCACTL,
		  VC4_SET_FIELD(0xf, V3D_SLCACTL_T1CC) |
		  VC4_SET_FIELD(0xf, V3D_SLCACTL_T0CC) |
		  VC4_SET_FIELD(0xf, V3D_SLCACTL_UCC) |
		  VC4_SET_FIELD(0xf, V3D_SLCACTL_ICC));
पूर्ण

अटल व्योम
vc4_flush_texture_caches(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	V3D_WRITE(V3D_L2CACTL,
		  V3D_L2CACTL_L2CCLR);

	V3D_WRITE(V3D_SLCACTL,
		  VC4_SET_FIELD(0xf, V3D_SLCACTL_T1CC) |
		  VC4_SET_FIELD(0xf, V3D_SLCACTL_T0CC));
पूर्ण

/* Sets the रेजिस्टरs क्रम the next job to be actually be executed in
 * the hardware.
 *
 * The job_lock should be held during this.
 */
व्योम
vc4_submit_next_bin_job(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_exec_info *exec;

again:
	exec = vc4_first_bin_job(vc4);
	अगर (!exec)
		वापस;

	vc4_flush_caches(dev);

	/* Only start the perfmon अगर it was not alपढ़ोy started by a previous
	 * job.
	 */
	अगर (exec->perfmon && vc4->active_perfmon != exec->perfmon)
		vc4_perfmon_start(vc4, exec->perfmon);

	/* Either put the job in the binner अगर it uses the binner, or
	 * immediately move it to the to-be-rendered queue.
	 */
	अगर (exec->ct0ca != exec->ct0ea) अणु
		submit_cl(dev, 0, exec->ct0ca, exec->ct0ea);
	पूर्ण अन्यथा अणु
		काष्ठा vc4_exec_info *next;

		vc4_move_job_to_render(dev, exec);
		next = vc4_first_bin_job(vc4);

		/* We can't start the next bin job अगर the previous job had a
		 * dअगरferent perfmon instance attached to it. The same goes
		 * अगर one of them had a perfmon attached to it and the other
		 * one करोesn't.
		 */
		अगर (next && next->perfmon == exec->perfmon)
			जाओ again;
	पूर्ण
पूर्ण

व्योम
vc4_submit_next_render_job(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_exec_info *exec = vc4_first_render_job(vc4);

	अगर (!exec)
		वापस;

	/* A previous RCL may have written to one of our textures, and
	 * our full cache flush at bin समय may have occurred beक्रमe
	 * that RCL completed.  Flush the texture cache now, but not
	 * the inकाष्ठाions or unअगरorms (since we करोn't ग_लिखो those
	 * from an RCL).
	 */
	vc4_flush_texture_caches(dev);

	submit_cl(dev, 1, exec->ct1ca, exec->ct1ea);
पूर्ण

व्योम
vc4_move_job_to_render(काष्ठा drm_device *dev, काष्ठा vc4_exec_info *exec)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	bool was_empty = list_empty(&vc4->render_job_list);

	list_move_tail(&exec->head, &vc4->render_job_list);
	अगर (was_empty)
		vc4_submit_next_render_job(dev);
पूर्ण

अटल व्योम
vc4_update_bo_seqnos(काष्ठा vc4_exec_info *exec, uपूर्णांक64_t seqno)
अणु
	काष्ठा vc4_bo *bo;
	अचिन्हित i;

	क्रम (i = 0; i < exec->bo_count; i++) अणु
		bo = to_vc4_bo(&exec->bo[i]->base);
		bo->seqno = seqno;

		dma_resv_add_shared_fence(bo->base.base.resv, exec->fence);
	पूर्ण

	list_क्रम_each_entry(bo, &exec->unref_list, unref_head) अणु
		bo->seqno = seqno;
	पूर्ण

	क्रम (i = 0; i < exec->rcl_ग_लिखो_bo_count; i++) अणु
		bo = to_vc4_bo(&exec->rcl_ग_लिखो_bo[i]->base);
		bo->ग_लिखो_seqno = seqno;

		dma_resv_add_excl_fence(bo->base.base.resv, exec->fence);
	पूर्ण
पूर्ण

अटल व्योम
vc4_unlock_bo_reservations(काष्ठा drm_device *dev,
			   काष्ठा vc4_exec_info *exec,
			   काष्ठा ww_acquire_ctx *acquire_ctx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < exec->bo_count; i++) अणु
		काष्ठा drm_gem_object *bo = &exec->bo[i]->base;

		dma_resv_unlock(bo->resv);
	पूर्ण

	ww_acquire_fini(acquire_ctx);
पूर्ण

/* Takes the reservation lock on all the BOs being referenced, so that
 * at queue submit समय we can update the reservations.
 *
 * We करोn't lock the RCL the tile alloc/state BOs, or overflow memory
 * (all of which are on exec->unref_list).  They're entirely निजी
 * to vc4, so we करोn't attach dma-buf fences to them.
 */
अटल पूर्णांक
vc4_lock_bo_reservations(काष्ठा drm_device *dev,
			 काष्ठा vc4_exec_info *exec,
			 काष्ठा ww_acquire_ctx *acquire_ctx)
अणु
	पूर्णांक contended_lock = -1;
	पूर्णांक i, ret;
	काष्ठा drm_gem_object *bo;

	ww_acquire_init(acquire_ctx, &reservation_ww_class);

retry:
	अगर (contended_lock != -1) अणु
		bo = &exec->bo[contended_lock]->base;
		ret = dma_resv_lock_slow_पूर्णांकerruptible(bo->resv, acquire_ctx);
		अगर (ret) अणु
			ww_acquire_करोne(acquire_ctx);
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < exec->bo_count; i++) अणु
		अगर (i == contended_lock)
			जारी;

		bo = &exec->bo[i]->base;

		ret = dma_resv_lock_पूर्णांकerruptible(bo->resv, acquire_ctx);
		अगर (ret) अणु
			पूर्णांक j;

			क्रम (j = 0; j < i; j++) अणु
				bo = &exec->bo[j]->base;
				dma_resv_unlock(bo->resv);
			पूर्ण

			अगर (contended_lock != -1 && contended_lock >= i) अणु
				bo = &exec->bo[contended_lock]->base;

				dma_resv_unlock(bo->resv);
			पूर्ण

			अगर (ret == -EDEADLK) अणु
				contended_lock = i;
				जाओ retry;
			पूर्ण

			ww_acquire_करोne(acquire_ctx);
			वापस ret;
		पूर्ण
	पूर्ण

	ww_acquire_करोne(acquire_ctx);

	/* Reserve space क्रम our shared (पढ़ो-only) fence references,
	 * beक्रमe we commit the CL to the hardware.
	 */
	क्रम (i = 0; i < exec->bo_count; i++) अणु
		bo = &exec->bo[i]->base;

		ret = dma_resv_reserve_shared(bo->resv, 1);
		अगर (ret) अणु
			vc4_unlock_bo_reservations(dev, exec, acquire_ctx);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Queues a काष्ठा vc4_exec_info क्रम execution.  If no job is
 * currently executing, then submits it.
 *
 * Unlike most GPUs, our hardware only handles one command list at a
 * समय.  To queue multiple jobs at once, we'd need to edit the
 * previous command list to have a jump to the new one at the end, and
 * then bump the end address.  That's a change क्रम a later date,
 * though.
 */
अटल पूर्णांक
vc4_queue_submit(काष्ठा drm_device *dev, काष्ठा vc4_exec_info *exec,
		 काष्ठा ww_acquire_ctx *acquire_ctx,
		 काष्ठा drm_syncobj *out_sync)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_exec_info *renderjob;
	uपूर्णांक64_t seqno;
	अचिन्हित दीर्घ irqflags;
	काष्ठा vc4_fence *fence;

	fence = kzalloc(माप(*fence), GFP_KERNEL);
	अगर (!fence)
		वापस -ENOMEM;
	fence->dev = dev;

	spin_lock_irqsave(&vc4->job_lock, irqflags);

	seqno = ++vc4->emit_seqno;
	exec->seqno = seqno;

	dma_fence_init(&fence->base, &vc4_fence_ops, &vc4->job_lock,
		       vc4->dma_fence_context, exec->seqno);
	fence->seqno = exec->seqno;
	exec->fence = &fence->base;

	अगर (out_sync)
		drm_syncobj_replace_fence(out_sync, exec->fence);

	vc4_update_bo_seqnos(exec, seqno);

	vc4_unlock_bo_reservations(dev, exec, acquire_ctx);

	list_add_tail(&exec->head, &vc4->bin_job_list);

	/* If no bin job was executing and अगर the render job (अगर any) has the
	 * same perfmon as our job attached to it (or अगर both jobs करोn't have
	 * perfmon activated), then kick ours off.  Otherwise, it'll get
	 * started when the previous job's flush/render करोne पूर्णांकerrupt occurs.
	 */
	renderjob = vc4_first_render_job(vc4);
	अगर (vc4_first_bin_job(vc4) == exec &&
	    (!renderjob || renderjob->perfmon == exec->perfmon)) अणु
		vc4_submit_next_bin_job(dev);
		vc4_queue_hangcheck(dev);
	पूर्ण

	spin_unlock_irqrestore(&vc4->job_lock, irqflags);

	वापस 0;
पूर्ण

/**
 * vc4_cl_lookup_bos() - Sets up exec->bo[] with the GEM objects
 * referenced by the job.
 * @dev: DRM device
 * @file_priv: DRM file क्रम this fd
 * @exec: V3D job being set up
 *
 * The command validator needs to reference BOs by their index within
 * the submitted job's BO list.  This does the validation of the job's
 * BO list and reference counting क्रम the lअगरeसमय of the job.
 */
अटल पूर्णांक
vc4_cl_lookup_bos(काष्ठा drm_device *dev,
		  काष्ठा drm_file *file_priv,
		  काष्ठा vc4_exec_info *exec)
अणु
	काष्ठा drm_vc4_submit_cl *args = exec->args;
	uपूर्णांक32_t *handles;
	पूर्णांक ret = 0;
	पूर्णांक i;

	exec->bo_count = args->bo_handle_count;

	अगर (!exec->bo_count) अणु
		/* See comment on bo_index क्रम why we have to check
		 * this.
		 */
		DRM_DEBUG("Rendering requires BOs to validate\n");
		वापस -EINVAL;
	पूर्ण

	exec->bo = kvदो_स्मृति_array(exec->bo_count,
				    माप(काष्ठा drm_gem_cma_object *),
				    GFP_KERNEL | __GFP_ZERO);
	अगर (!exec->bo) अणु
		DRM_ERROR("Failed to allocate validated BO pointers\n");
		वापस -ENOMEM;
	पूर्ण

	handles = kvदो_स्मृति_array(exec->bo_count, माप(uपूर्णांक32_t), GFP_KERNEL);
	अगर (!handles) अणु
		ret = -ENOMEM;
		DRM_ERROR("Failed to allocate incoming GEM handles\n");
		जाओ fail;
	पूर्ण

	अगर (copy_from_user(handles, u64_to_user_ptr(args->bo_handles),
			   exec->bo_count * माप(uपूर्णांक32_t))) अणु
		ret = -EFAULT;
		DRM_ERROR("Failed to copy in GEM handles\n");
		जाओ fail;
	पूर्ण

	spin_lock(&file_priv->table_lock);
	क्रम (i = 0; i < exec->bo_count; i++) अणु
		काष्ठा drm_gem_object *bo = idr_find(&file_priv->object_idr,
						     handles[i]);
		अगर (!bo) अणु
			DRM_DEBUG("Failed to look up GEM BO %d: %d\n",
				  i, handles[i]);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		drm_gem_object_get(bo);
		exec->bo[i] = (काष्ठा drm_gem_cma_object *)bo;
	पूर्ण
	spin_unlock(&file_priv->table_lock);

	अगर (ret)
		जाओ fail_put_bo;

	क्रम (i = 0; i < exec->bo_count; i++) अणु
		ret = vc4_bo_inc_usecnt(to_vc4_bo(&exec->bo[i]->base));
		अगर (ret)
			जाओ fail_dec_usecnt;
	पूर्ण

	kvमुक्त(handles);
	वापस 0;

fail_dec_usecnt:
	/* Decrease usecnt on acquired objects.
	 * We cannot rely on  vc4_complete_exec() to release resources here,
	 * because vc4_complete_exec() has no inक्रमmation about which BO has
	 * had its ->usecnt incremented.
	 * To make things easier we just मुक्त everything explicitly and set
	 * exec->bo to शून्य so that vc4_complete_exec() skips the 'BO release'
	 * step.
	 */
	क्रम (i-- ; i >= 0; i--)
		vc4_bo_dec_usecnt(to_vc4_bo(&exec->bo[i]->base));

fail_put_bo:
	/* Release any reference to acquired objects. */
	क्रम (i = 0; i < exec->bo_count && exec->bo[i]; i++)
		drm_gem_object_put(&exec->bo[i]->base);

fail:
	kvमुक्त(handles);
	kvमुक्त(exec->bo);
	exec->bo = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक
vc4_get_bcl(काष्ठा drm_device *dev, काष्ठा vc4_exec_info *exec)
अणु
	काष्ठा drm_vc4_submit_cl *args = exec->args;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	व्योम *temp = शून्य;
	व्योम *bin;
	पूर्णांक ret = 0;
	uपूर्णांक32_t bin_offset = 0;
	uपूर्णांक32_t shader_rec_offset = roundup(bin_offset + args->bin_cl_size,
					     16);
	uपूर्णांक32_t unअगरorms_offset = shader_rec_offset + args->shader_rec_size;
	uपूर्णांक32_t exec_size = unअगरorms_offset + args->unअगरorms_size;
	uपूर्णांक32_t temp_size = exec_size + (माप(काष्ठा vc4_shader_state) *
					  args->shader_rec_count);
	काष्ठा vc4_bo *bo;

	अगर (shader_rec_offset < args->bin_cl_size ||
	    unअगरorms_offset < shader_rec_offset ||
	    exec_size < unअगरorms_offset ||
	    args->shader_rec_count >= (अच_पूर्णांक_उच्च /
					  माप(काष्ठा vc4_shader_state)) ||
	    temp_size < exec_size) अणु
		DRM_DEBUG("overflow in exec arguments\n");
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	/* Allocate space where we'll store the copied in user command lists
	 * and shader records.
	 *
	 * We करोn't just copy directly पूर्णांकo the BOs because we need to
	 * पढ़ो the contents back क्रम validation, and I think the
	 * bo->vaddr is uncached access.
	 */
	temp = kvदो_स्मृति_array(temp_size, 1, GFP_KERNEL);
	अगर (!temp) अणु
		DRM_ERROR("Failed to allocate storage for copying "
			  "in bin/render CLs.\n");
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	bin = temp + bin_offset;
	exec->shader_rec_u = temp + shader_rec_offset;
	exec->unअगरorms_u = temp + unअगरorms_offset;
	exec->shader_state = temp + exec_size;
	exec->shader_state_size = args->shader_rec_count;

	अगर (copy_from_user(bin,
			   u64_to_user_ptr(args->bin_cl),
			   args->bin_cl_size)) अणु
		ret = -EFAULT;
		जाओ fail;
	पूर्ण

	अगर (copy_from_user(exec->shader_rec_u,
			   u64_to_user_ptr(args->shader_rec),
			   args->shader_rec_size)) अणु
		ret = -EFAULT;
		जाओ fail;
	पूर्ण

	अगर (copy_from_user(exec->unअगरorms_u,
			   u64_to_user_ptr(args->unअगरorms),
			   args->unअगरorms_size)) अणु
		ret = -EFAULT;
		जाओ fail;
	पूर्ण

	bo = vc4_bo_create(dev, exec_size, true, VC4_BO_TYPE_BCL);
	अगर (IS_ERR(bo)) अणु
		DRM_ERROR("Couldn't allocate BO for binning\n");
		ret = PTR_ERR(bo);
		जाओ fail;
	पूर्ण
	exec->exec_bo = &bo->base;

	list_add_tail(&to_vc4_bo(&exec->exec_bo->base)->unref_head,
		      &exec->unref_list);

	exec->ct0ca = exec->exec_bo->paddr + bin_offset;

	exec->bin_u = bin;

	exec->shader_rec_v = exec->exec_bo->vaddr + shader_rec_offset;
	exec->shader_rec_p = exec->exec_bo->paddr + shader_rec_offset;
	exec->shader_rec_size = args->shader_rec_size;

	exec->unअगरorms_v = exec->exec_bo->vaddr + unअगरorms_offset;
	exec->unअगरorms_p = exec->exec_bo->paddr + unअगरorms_offset;
	exec->unअगरorms_size = args->unअगरorms_size;

	ret = vc4_validate_bin_cl(dev,
				  exec->exec_bo->vaddr + bin_offset,
				  bin,
				  exec);
	अगर (ret)
		जाओ fail;

	ret = vc4_validate_shader_recs(dev, exec);
	अगर (ret)
		जाओ fail;

	अगर (exec->found_tile_binning_mode_config_packet) अणु
		ret = vc4_v3d_bin_bo_get(vc4, &exec->bin_bo_used);
		अगर (ret)
			जाओ fail;
	पूर्ण

	/* Block रुकोing on any previous rendering पूर्णांकo the CS's VBO,
	 * IB, or textures, so that pixels are actually written by the
	 * समय we try to पढ़ो them.
	 */
	ret = vc4_रुको_क्रम_seqno(dev, exec->bin_dep_seqno, ~0ull, true);

fail:
	kvमुक्त(temp);
	वापस ret;
पूर्ण

अटल व्योम
vc4_complete_exec(काष्ठा drm_device *dev, काष्ठा vc4_exec_info *exec)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	अचिन्हित दीर्घ irqflags;
	अचिन्हित i;

	/* If we got क्रमce-completed because of GPU reset rather than
	 * through our IRQ handler, संकेत the fence now.
	 */
	अगर (exec->fence) अणु
		dma_fence_संकेत(exec->fence);
		dma_fence_put(exec->fence);
	पूर्ण

	अगर (exec->bo) अणु
		क्रम (i = 0; i < exec->bo_count; i++) अणु
			काष्ठा vc4_bo *bo = to_vc4_bo(&exec->bo[i]->base);

			vc4_bo_dec_usecnt(bo);
			drm_gem_object_put(&exec->bo[i]->base);
		पूर्ण
		kvमुक्त(exec->bo);
	पूर्ण

	जबतक (!list_empty(&exec->unref_list)) अणु
		काष्ठा vc4_bo *bo = list_first_entry(&exec->unref_list,
						     काष्ठा vc4_bo, unref_head);
		list_del(&bo->unref_head);
		drm_gem_object_put(&bo->base.base);
	पूर्ण

	/* Free up the allocation of any bin slots we used. */
	spin_lock_irqsave(&vc4->job_lock, irqflags);
	vc4->bin_alloc_used &= ~exec->bin_slots;
	spin_unlock_irqrestore(&vc4->job_lock, irqflags);

	/* Release the reference on the binner BO अगर needed. */
	अगर (exec->bin_bo_used)
		vc4_v3d_bin_bo_put(vc4);

	/* Release the reference we had on the perf monitor. */
	vc4_perfmon_put(exec->perfmon);

	vc4_v3d_pm_put(vc4);

	kमुक्त(exec);
पूर्ण

व्योम
vc4_job_handle_completed(काष्ठा vc4_dev *vc4)
अणु
	अचिन्हित दीर्घ irqflags;
	काष्ठा vc4_seqno_cb *cb, *cb_temp;

	spin_lock_irqsave(&vc4->job_lock, irqflags);
	जबतक (!list_empty(&vc4->job_करोne_list)) अणु
		काष्ठा vc4_exec_info *exec =
			list_first_entry(&vc4->job_करोne_list,
					 काष्ठा vc4_exec_info, head);
		list_del(&exec->head);

		spin_unlock_irqrestore(&vc4->job_lock, irqflags);
		vc4_complete_exec(&vc4->base, exec);
		spin_lock_irqsave(&vc4->job_lock, irqflags);
	पूर्ण

	list_क्रम_each_entry_safe(cb, cb_temp, &vc4->seqno_cb_list, work.entry) अणु
		अगर (cb->seqno <= vc4->finished_seqno) अणु
			list_del_init(&cb->work.entry);
			schedule_work(&cb->work);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&vc4->job_lock, irqflags);
पूर्ण

अटल व्योम vc4_seqno_cb_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vc4_seqno_cb *cb = container_of(work, काष्ठा vc4_seqno_cb, work);

	cb->func(cb);
पूर्ण

पूर्णांक vc4_queue_seqno_cb(काष्ठा drm_device *dev,
		       काष्ठा vc4_seqno_cb *cb, uपूर्णांक64_t seqno,
		       व्योम (*func)(काष्ठा vc4_seqno_cb *cb))
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	अचिन्हित दीर्घ irqflags;

	cb->func = func;
	INIT_WORK(&cb->work, vc4_seqno_cb_work);

	spin_lock_irqsave(&vc4->job_lock, irqflags);
	अगर (seqno > vc4->finished_seqno) अणु
		cb->seqno = seqno;
		list_add_tail(&cb->work.entry, &vc4->seqno_cb_list);
	पूर्ण अन्यथा अणु
		schedule_work(&cb->work);
	पूर्ण
	spin_unlock_irqrestore(&vc4->job_lock, irqflags);

	वापस 0;
पूर्ण

/* Scheduled when any job has been completed, this walks the list of
 * jobs that had completed and unrefs their BOs and मुक्तs their exec
 * काष्ठाs.
 */
अटल व्योम
vc4_job_करोne_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vc4_dev *vc4 =
		container_of(work, काष्ठा vc4_dev, job_करोne_work);

	vc4_job_handle_completed(vc4);
पूर्ण

अटल पूर्णांक
vc4_रुको_क्रम_seqno_ioctl_helper(काष्ठा drm_device *dev,
				uपूर्णांक64_t seqno,
				uपूर्णांक64_t *समयout_ns)
अणु
	अचिन्हित दीर्घ start = jअगरfies;
	पूर्णांक ret = vc4_रुको_क्रम_seqno(dev, seqno, *समयout_ns, true);

	अगर ((ret == -EINTR || ret == -ERESTARTSYS) && *समयout_ns != ~0ull) अणु
		uपूर्णांक64_t delta = jअगरfies_to_nsecs(jअगरfies - start);

		अगर (*समयout_ns >= delta)
			*समयout_ns -= delta;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
vc4_रुको_seqno_ioctl(काष्ठा drm_device *dev, व्योम *data,
		     काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vc4_रुको_seqno *args = data;

	वापस vc4_रुको_क्रम_seqno_ioctl_helper(dev, args->seqno,
					       &args->समयout_ns);
पूर्ण

पूर्णांक
vc4_रुको_bo_ioctl(काष्ठा drm_device *dev, व्योम *data,
		  काष्ठा drm_file *file_priv)
अणु
	पूर्णांक ret;
	काष्ठा drm_vc4_रुको_bo *args = data;
	काष्ठा drm_gem_object *gem_obj;
	काष्ठा vc4_bo *bo;

	अगर (args->pad != 0)
		वापस -EINVAL;

	gem_obj = drm_gem_object_lookup(file_priv, args->handle);
	अगर (!gem_obj) अणु
		DRM_DEBUG("Failed to look up GEM BO %d\n", args->handle);
		वापस -EINVAL;
	पूर्ण
	bo = to_vc4_bo(gem_obj);

	ret = vc4_रुको_क्रम_seqno_ioctl_helper(dev, bo->seqno,
					      &args->समयout_ns);

	drm_gem_object_put(gem_obj);
	वापस ret;
पूर्ण

/**
 * vc4_submit_cl_ioctl() - Submits a job (frame) to the VC4.
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
vc4_submit_cl_ioctl(काष्ठा drm_device *dev, व्योम *data,
		    काष्ठा drm_file *file_priv)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	काष्ठा vc4_file *vc4file = file_priv->driver_priv;
	काष्ठा drm_vc4_submit_cl *args = data;
	काष्ठा drm_syncobj *out_sync = शून्य;
	काष्ठा vc4_exec_info *exec;
	काष्ठा ww_acquire_ctx acquire_ctx;
	काष्ठा dma_fence *in_fence;
	पूर्णांक ret = 0;

	अगर (!vc4->v3d) अणु
		DRM_DEBUG("VC4_SUBMIT_CL with no VC4 V3D probed\n");
		वापस -ENODEV;
	पूर्ण

	अगर ((args->flags & ~(VC4_SUBMIT_CL_USE_CLEAR_COLOR |
			     VC4_SUBMIT_CL_FIXED_RCL_ORDER |
			     VC4_SUBMIT_CL_RCL_ORDER_INCREASING_X |
			     VC4_SUBMIT_CL_RCL_ORDER_INCREASING_Y)) != 0) अणु
		DRM_DEBUG("Unknown flags: 0x%02x\n", args->flags);
		वापस -EINVAL;
	पूर्ण

	अगर (args->pad2 != 0) अणु
		DRM_DEBUG("Invalid pad: 0x%08x\n", args->pad2);
		वापस -EINVAL;
	पूर्ण

	exec = kसुस्मृति(1, माप(*exec), GFP_KERNEL);
	अगर (!exec) अणु
		DRM_ERROR("malloc failure on exec struct\n");
		वापस -ENOMEM;
	पूर्ण

	ret = vc4_v3d_pm_get(vc4);
	अगर (ret) अणु
		kमुक्त(exec);
		वापस ret;
	पूर्ण

	exec->args = args;
	INIT_LIST_HEAD(&exec->unref_list);

	ret = vc4_cl_lookup_bos(dev, file_priv, exec);
	अगर (ret)
		जाओ fail;

	अगर (args->perfmonid) अणु
		exec->perfmon = vc4_perfmon_find(vc4file,
						 args->perfmonid);
		अगर (!exec->perfmon) अणु
			ret = -ENOENT;
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (args->in_sync) अणु
		ret = drm_syncobj_find_fence(file_priv, args->in_sync,
					     0, 0, &in_fence);
		अगर (ret)
			जाओ fail;

		/* When the fence (or fence array) is exclusively from our
		 * context we can skip the रुको since jobs are executed in
		 * order of their submission through this ioctl and this can
		 * only have fences from a prior job.
		 */
		अगर (!dma_fence_match_context(in_fence,
					     vc4->dma_fence_context)) अणु
			ret = dma_fence_रुको(in_fence, true);
			अगर (ret) अणु
				dma_fence_put(in_fence);
				जाओ fail;
			पूर्ण
		पूर्ण

		dma_fence_put(in_fence);
	पूर्ण

	अगर (exec->args->bin_cl_size != 0) अणु
		ret = vc4_get_bcl(dev, exec);
		अगर (ret)
			जाओ fail;
	पूर्ण अन्यथा अणु
		exec->ct0ca = 0;
		exec->ct0ea = 0;
	पूर्ण

	ret = vc4_get_rcl(dev, exec);
	अगर (ret)
		जाओ fail;

	ret = vc4_lock_bo_reservations(dev, exec, &acquire_ctx);
	अगर (ret)
		जाओ fail;

	अगर (args->out_sync) अणु
		out_sync = drm_syncobj_find(file_priv, args->out_sync);
		अगर (!out_sync) अणु
			ret = -EINVAL;
			जाओ fail;
		पूर्ण

		/* We replace the fence in out_sync in vc4_queue_submit since
		 * the render job could execute immediately after that call.
		 * If it finishes beक्रमe our ioctl processing resumes the
		 * render job fence could alपढ़ोy have been मुक्तd.
		 */
	पूर्ण

	/* Clear this out of the काष्ठा we'll be putting in the queue,
	 * since it's part of our stack.
	 */
	exec->args = शून्य;

	ret = vc4_queue_submit(dev, exec, &acquire_ctx, out_sync);

	/* The syncobj isn't part of the exec data and we need to मुक्त our
	 * reference even अगर job submission failed.
	 */
	अगर (out_sync)
		drm_syncobj_put(out_sync);

	अगर (ret)
		जाओ fail;

	/* Return the seqno क्रम our job. */
	args->seqno = vc4->emit_seqno;

	वापस 0;

fail:
	vc4_complete_exec(&vc4->base, exec);

	वापस ret;
पूर्ण

अटल व्योम vc4_gem_destroy(काष्ठा drm_device *dev, व्योम *unused);
पूर्णांक vc4_gem_init(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	vc4->dma_fence_context = dma_fence_context_alloc(1);

	INIT_LIST_HEAD(&vc4->bin_job_list);
	INIT_LIST_HEAD(&vc4->render_job_list);
	INIT_LIST_HEAD(&vc4->job_करोne_list);
	INIT_LIST_HEAD(&vc4->seqno_cb_list);
	spin_lock_init(&vc4->job_lock);

	INIT_WORK(&vc4->hangcheck.reset_work, vc4_reset_work);
	समयr_setup(&vc4->hangcheck.समयr, vc4_hangcheck_elapsed, 0);

	INIT_WORK(&vc4->job_करोne_work, vc4_job_करोne_work);

	mutex_init(&vc4->घातer_lock);

	INIT_LIST_HEAD(&vc4->purgeable.list);
	mutex_init(&vc4->purgeable.lock);

	वापस drmm_add_action_or_reset(dev, vc4_gem_destroy, शून्य);
पूर्ण

अटल व्योम vc4_gem_destroy(काष्ठा drm_device *dev, व्योम *unused)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	/* Waiting क्रम exec to finish would need to be करोne beक्रमe
	 * unरेजिस्टरing V3D.
	 */
	WARN_ON(vc4->emit_seqno != vc4->finished_seqno);

	/* V3D should alपढ़ोy have disabled its पूर्णांकerrupt and cleared
	 * the overflow allocation रेजिस्टरs.  Now मुक्त the object.
	 */
	अगर (vc4->bin_bo) अणु
		drm_gem_object_put(&vc4->bin_bo->base.base);
		vc4->bin_bo = शून्य;
	पूर्ण

	अगर (vc4->hang_state)
		vc4_मुक्त_hang_state(dev, vc4->hang_state);
पूर्ण

पूर्णांक vc4_gem_madvise_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vc4_gem_madvise *args = data;
	काष्ठा drm_gem_object *gem_obj;
	काष्ठा vc4_bo *bo;
	पूर्णांक ret;

	चयन (args->madv) अणु
	हाल VC4_MADV_DONTNEED:
	हाल VC4_MADV_WILLNEED:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (args->pad != 0)
		वापस -EINVAL;

	gem_obj = drm_gem_object_lookup(file_priv, args->handle);
	अगर (!gem_obj) अणु
		DRM_DEBUG("Failed to look up GEM BO %d\n", args->handle);
		वापस -ENOENT;
	पूर्ण

	bo = to_vc4_bo(gem_obj);

	/* Only BOs exposed to userspace can be purged. */
	अगर (bo->madv == __VC4_MADV_NOTSUPP) अणु
		DRM_DEBUG("madvise not supported on this BO\n");
		ret = -EINVAL;
		जाओ out_put_gem;
	पूर्ण

	/* Not sure it's safe to purge imported BOs. Let's just assume it's
	 * not until proven otherwise.
	 */
	अगर (gem_obj->import_attach) अणु
		DRM_DEBUG("madvise not supported on imported BOs\n");
		ret = -EINVAL;
		जाओ out_put_gem;
	पूर्ण

	mutex_lock(&bo->madv_lock);

	अगर (args->madv == VC4_MADV_DONTNEED && bo->madv == VC4_MADV_WILLNEED &&
	    !refcount_पढ़ो(&bo->usecnt)) अणु
		/* If the BO is about to be marked as purgeable, is not used
		 * and is not alपढ़ोy purgeable or purged, add it to the
		 * purgeable list.
		 */
		vc4_bo_add_to_purgeable_pool(bo);
	पूर्ण अन्यथा अगर (args->madv == VC4_MADV_WILLNEED &&
		   bo->madv == VC4_MADV_DONTNEED &&
		   !refcount_पढ़ो(&bo->usecnt)) अणु
		/* The BO has not been purged yet, just हटाओ it from
		 * the purgeable list.
		 */
		vc4_bo_हटाओ_from_purgeable_pool(bo);
	पूर्ण

	/* Save the purged state. */
	args->retained = bo->madv != __VC4_MADV_PURGED;

	/* Update पूर्णांकernal madv state only अगर the bo was not purged. */
	अगर (bo->madv != __VC4_MADV_PURGED)
		bo->madv = args->madv;

	mutex_unlock(&bo->madv_lock);

	ret = 0;

out_put_gem:
	drm_gem_object_put(gem_obj);

	वापस ret;
पूर्ण
