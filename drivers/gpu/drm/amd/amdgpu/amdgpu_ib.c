<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
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
 *          Alex Deucher
 *          Jerome Glisse
 *          Christian Kथघnig
 */
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

#समावेश <drm/amdgpu_drm.h>

#समावेश "amdgpu.h"
#समावेश "atom.h"
#समावेश "amdgpu_trace.h"

#घोषणा AMDGPU_IB_TEST_TIMEOUT	msecs_to_jअगरfies(1000)
#घोषणा AMDGPU_IB_TEST_GFX_XGMI_TIMEOUT	msecs_to_jअगरfies(2000)

/*
 * IB
 * IBs (Indirect Buffers) and areas of GPU accessible memory where
 * commands are stored.  You can put a poपूर्णांकer to the IB in the
 * command ring and the hw will fetch the commands from the IB
 * and execute them.  Generally userspace acceleration drivers
 * produce command buffers which are send to the kernel and
 * put in IBs क्रम execution by the requested ring.
 */

/**
 * amdgpu_ib_get - request an IB (Indirect Buffer)
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: amdgpu_vm poपूर्णांकer
 * @size: requested IB size
 * @pool_type: IB pool type (delayed, immediate, direct)
 * @ib: IB object वापसed
 *
 * Request an IB (all asics).  IBs are allocated using the
 * suballocator.
 * Returns 0 on success, error on failure.
 */
पूर्णांक amdgpu_ib_get(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_vm *vm,
		  अचिन्हित size, क्रमागत amdgpu_ib_pool_type pool_type,
		  काष्ठा amdgpu_ib *ib)
अणु
	पूर्णांक r;

	अगर (size) अणु
		r = amdgpu_sa_bo_new(&adev->ib_pools[pool_type],
				      &ib->sa_bo, size, 256);
		अगर (r) अणु
			dev_err(adev->dev, "failed to get a new IB (%d)\n", r);
			वापस r;
		पूर्ण

		ib->ptr = amdgpu_sa_bo_cpu_addr(ib->sa_bo);
		/* flush the cache beक्रमe commit the IB */
		ib->flags = AMDGPU_IB_FLAG_EMIT_MEM_SYNC;

		अगर (!vm)
			ib->gpu_addr = amdgpu_sa_bo_gpu_addr(ib->sa_bo);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_ib_मुक्त - मुक्त an IB (Indirect Buffer)
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ib: IB object to मुक्त
 * @f: the fence SA bo need रुको on क्रम the ib alloation
 *
 * Free an IB (all asics).
 */
व्योम amdgpu_ib_मुक्त(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ib *ib,
		    काष्ठा dma_fence *f)
अणु
	amdgpu_sa_bo_मुक्त(adev, &ib->sa_bo, f);
पूर्ण

/**
 * amdgpu_ib_schedule - schedule an IB (Indirect Buffer) on the ring
 *
 * @ring: ring index the IB is associated with
 * @num_ibs: number of IBs to schedule
 * @ibs: IB objects to schedule
 * @job: job to schedule
 * @f: fence created during this submission
 *
 * Schedule an IB on the associated ring (all asics).
 * Returns 0 on success, error on failure.
 *
 * On SI, there are two parallel engines fed from the primary ring,
 * the CE (Constant Engine) and the DE (Drawing Engine).  Since
 * resource descriptors have moved to memory, the CE allows you to
 * prime the caches जबतक the DE is updating रेजिस्टर state so that
 * the resource descriptors will be alपढ़ोy in cache when the draw is
 * processed.  To accomplish this, the userspace driver submits two
 * IBs, one क्रम the CE and one क्रम the DE.  If there is a CE IB (called
 * a CONST_IB), it will be put on the ring prior to the DE IB.  Prior
 * to SI there was just a DE IB.
 */
पूर्णांक amdgpu_ib_schedule(काष्ठा amdgpu_ring *ring, अचिन्हित num_ibs,
		       काष्ठा amdgpu_ib *ibs, काष्ठा amdgpu_job *job,
		       काष्ठा dma_fence **f)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा amdgpu_ib *ib = &ibs[0];
	काष्ठा dma_fence *पंचांगp = शून्य;
	bool skip_preamble, need_ctx_चयन;
	अचिन्हित patch_offset = ~0;
	काष्ठा amdgpu_vm *vm;
	uपूर्णांक64_t fence_ctx;
	uपूर्णांक32_t status = 0, alloc_size;
	अचिन्हित fence_flags = 0;
	bool secure;

	अचिन्हित i;
	पूर्णांक r = 0;
	bool need_pipe_sync = false;

	अगर (num_ibs == 0)
		वापस -EINVAL;

	/* ring tests करोn't use a job */
	अगर (job) अणु
		vm = job->vm;
		fence_ctx = job->base.s_fence ?
			job->base.s_fence->scheduled.context : 0;
	पूर्ण अन्यथा अणु
		vm = शून्य;
		fence_ctx = 0;
	पूर्ण

	अगर (!ring->sched.पढ़ोy) अणु
		dev_err(adev->dev, "couldn't schedule ib on ring <%s>\n", ring->name);
		वापस -EINVAL;
	पूर्ण

	अगर (vm && !job->vmid) अणु
		dev_err(adev->dev, "VM IB without ID\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((ib->flags & AMDGPU_IB_FLAGS_SECURE) &&
	    (ring->funcs->type == AMDGPU_RING_TYPE_COMPUTE)) अणु
		dev_err(adev->dev, "secure submissions not supported on compute rings\n");
		वापस -EINVAL;
	पूर्ण

	alloc_size = ring->funcs->emit_frame_size + num_ibs *
		ring->funcs->emit_ib_size;

	r = amdgpu_ring_alloc(ring, alloc_size);
	अगर (r) अणु
		dev_err(adev->dev, "scheduling IB failed (%d).\n", r);
		वापस r;
	पूर्ण

	need_ctx_चयन = ring->current_ctx != fence_ctx;
	अगर (ring->funcs->emit_pipeline_sync && job &&
	    ((पंचांगp = amdgpu_sync_get_fence(&job->sched_sync)) ||
	     (amdgpu_sriov_vf(adev) && need_ctx_चयन) ||
	     amdgpu_vm_need_pipeline_sync(ring, job))) अणु
		need_pipe_sync = true;

		अगर (पंचांगp)
			trace_amdgpu_ib_pipe_sync(job, पंचांगp);

		dma_fence_put(पंचांगp);
	पूर्ण

	अगर ((ib->flags & AMDGPU_IB_FLAG_EMIT_MEM_SYNC) && ring->funcs->emit_mem_sync)
		ring->funcs->emit_mem_sync(ring);

	अगर (ring->funcs->emit_wave_limit &&
	    ring->hw_prio == AMDGPU_GFX_PIPE_PRIO_HIGH)
		ring->funcs->emit_wave_limit(ring, true);

	अगर (ring->funcs->insert_start)
		ring->funcs->insert_start(ring);

	अगर (job) अणु
		r = amdgpu_vm_flush(ring, job, need_pipe_sync);
		अगर (r) अणु
			amdgpu_ring_unकरो(ring);
			वापस r;
		पूर्ण
	पूर्ण

	अगर (job && ring->funcs->init_cond_exec)
		patch_offset = amdgpu_ring_init_cond_exec(ring);

#अगर_घोषित CONFIG_X86_64
	अगर (!(adev->flags & AMD_IS_APU))
#पूर्ण_अगर
	अणु
		अगर (ring->funcs->emit_hdp_flush)
			amdgpu_ring_emit_hdp_flush(ring);
		अन्यथा
			amdgpu_asic_flush_hdp(adev, ring);
	पूर्ण

	अगर (need_ctx_चयन)
		status |= AMDGPU_HAVE_CTX_SWITCH;

	skip_preamble = ring->current_ctx == fence_ctx;
	अगर (job && ring->funcs->emit_cntxcntl) अणु
		status |= job->preamble_status;
		status |= job->preemption_status;
		amdgpu_ring_emit_cntxcntl(ring, status);
	पूर्ण

	/* Setup initial TMZiness and send it off.
	 */
	secure = false;
	अगर (job && ring->funcs->emit_frame_cntl) अणु
		secure = ib->flags & AMDGPU_IB_FLAGS_SECURE;
		amdgpu_ring_emit_frame_cntl(ring, true, secure);
	पूर्ण

	क्रम (i = 0; i < num_ibs; ++i) अणु
		ib = &ibs[i];

		/* drop preamble IBs अगर we करोn't have a context चयन */
		अगर ((ib->flags & AMDGPU_IB_FLAG_PREAMBLE) &&
		    skip_preamble &&
		    !(status & AMDGPU_PREAMBLE_IB_PRESENT_FIRST) &&
		    !amdgpu_mcbp &&
		    !amdgpu_sriov_vf(adev)) /* क्रम SRIOV preemption, Preamble CE ib must be inserted anyway */
			जारी;

		अगर (job && ring->funcs->emit_frame_cntl) अणु
			अगर (secure != !!(ib->flags & AMDGPU_IB_FLAGS_SECURE)) अणु
				amdgpu_ring_emit_frame_cntl(ring, false, secure);
				secure = !secure;
				amdgpu_ring_emit_frame_cntl(ring, true, secure);
			पूर्ण
		पूर्ण

		amdgpu_ring_emit_ib(ring, job, ib, status);
		status &= ~AMDGPU_HAVE_CTX_SWITCH;
	पूर्ण

	अगर (job && ring->funcs->emit_frame_cntl)
		amdgpu_ring_emit_frame_cntl(ring, false, secure);

#अगर_घोषित CONFIG_X86_64
	अगर (!(adev->flags & AMD_IS_APU))
#पूर्ण_अगर
		amdgpu_asic_invalidate_hdp(adev, ring);

	अगर (ib->flags & AMDGPU_IB_FLAG_TC_WB_NOT_INVALIDATE)
		fence_flags |= AMDGPU_FENCE_FLAG_TC_WB_ONLY;

	/* wrap the last IB with fence */
	अगर (job && job->uf_addr) अणु
		amdgpu_ring_emit_fence(ring, job->uf_addr, job->uf_sequence,
				       fence_flags | AMDGPU_FENCE_FLAG_64BIT);
	पूर्ण

	r = amdgpu_fence_emit(ring, f, fence_flags);
	अगर (r) अणु
		dev_err(adev->dev, "failed to emit fence (%d)\n", r);
		अगर (job && job->vmid)
			amdgpu_vmid_reset(adev, ring->funcs->vmhub, job->vmid);
		amdgpu_ring_unकरो(ring);
		वापस r;
	पूर्ण

	अगर (ring->funcs->insert_end)
		ring->funcs->insert_end(ring);

	अगर (patch_offset != ~0 && ring->funcs->patch_cond_exec)
		amdgpu_ring_patch_cond_exec(ring, patch_offset);

	ring->current_ctx = fence_ctx;
	अगर (vm && ring->funcs->emit_चयन_buffer)
		amdgpu_ring_emit_चयन_buffer(ring);

	अगर (ring->funcs->emit_wave_limit &&
	    ring->hw_prio == AMDGPU_GFX_PIPE_PRIO_HIGH)
		ring->funcs->emit_wave_limit(ring, false);

	amdgpu_ring_commit(ring);
	वापस 0;
पूर्ण

/**
 * amdgpu_ib_pool_init - Init the IB (Indirect Buffer) pool
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Initialize the suballocator to manage a pool of memory
 * क्रम use as IBs (all asics).
 * Returns 0 on success, error on failure.
 */
पूर्णांक amdgpu_ib_pool_init(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित size;
	पूर्णांक r, i;

	अगर (adev->ib_pool_पढ़ोy)
		वापस 0;

	क्रम (i = 0; i < AMDGPU_IB_POOL_MAX; i++) अणु
		अगर (i == AMDGPU_IB_POOL_सूचीECT)
			size = PAGE_SIZE * 2;
		अन्यथा
			size = AMDGPU_IB_POOL_SIZE;

		r = amdgpu_sa_bo_manager_init(adev, &adev->ib_pools[i],
					      size, AMDGPU_GPU_PAGE_SIZE,
					      AMDGPU_GEM_DOMAIN_GTT);
		अगर (r)
			जाओ error;
	पूर्ण
	adev->ib_pool_पढ़ोy = true;

	वापस 0;

error:
	जबतक (i--)
		amdgpu_sa_bo_manager_fini(adev, &adev->ib_pools[i]);
	वापस r;
पूर्ण

/**
 * amdgpu_ib_pool_fini - Free the IB (Indirect Buffer) pool
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Tear करोwn the suballocator managing the pool of memory
 * क्रम use as IBs (all asics).
 */
व्योम amdgpu_ib_pool_fini(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	अगर (!adev->ib_pool_पढ़ोy)
		वापस;

	क्रम (i = 0; i < AMDGPU_IB_POOL_MAX; i++)
		amdgpu_sa_bo_manager_fini(adev, &adev->ib_pools[i]);
	adev->ib_pool_पढ़ोy = false;
पूर्ण

/**
 * amdgpu_ib_ring_tests - test IBs on the rings
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Test an IB (Indirect Buffer) on each ring.
 * If the test fails, disable the ring.
 * Returns 0 on success, error अगर the primary GFX ring
 * IB test fails.
 */
पूर्णांक amdgpu_ib_ring_tests(काष्ठा amdgpu_device *adev)
अणु
	दीर्घ पंचांगo_gfx, पंचांगo_mm;
	पूर्णांक r, ret = 0;
	अचिन्हित i;

	पंचांगo_mm = पंचांगo_gfx = AMDGPU_IB_TEST_TIMEOUT;
	अगर (amdgpu_sriov_vf(adev)) अणु
		/* क्रम MM engines in hypervisor side they are not scheduled together
		 * with CP and SDMA engines, so even in exclusive mode MM engine could
		 * still running on other VF thus the IB TEST TIMEOUT क्रम MM engines
		 * under SR-IOV should be set to a दीर्घ समय. 8 sec should be enough
		 * क्रम the MM comes back to this VF.
		 */
		पंचांगo_mm = 8 * AMDGPU_IB_TEST_TIMEOUT;
	पूर्ण

	अगर (amdgpu_sriov_runसमय(adev)) अणु
		/* क्रम CP & SDMA engines since they are scheduled together so
		 * need to make the समयout width enough to cover the समय
		 * cost रुकोing क्रम it coming back under RUNTIME only
		*/
		पंचांगo_gfx = 8 * AMDGPU_IB_TEST_TIMEOUT;
	पूर्ण अन्यथा अगर (adev->gmc.xgmi.hive_id) अणु
		पंचांगo_gfx = AMDGPU_IB_TEST_GFX_XGMI_TIMEOUT;
	पूर्ण

	क्रम (i = 0; i < adev->num_rings; ++i) अणु
		काष्ठा amdgpu_ring *ring = adev->rings[i];
		दीर्घ पंचांगo;

		/* KIQ rings करोn't have an IB test because we never submit IBs
		 * to them and they have no पूर्णांकerrupt support.
		 */
		अगर (!ring->sched.पढ़ोy || !ring->funcs->test_ib)
			जारी;

		/* MM engine need more समय */
		अगर (ring->funcs->type == AMDGPU_RING_TYPE_UVD ||
			ring->funcs->type == AMDGPU_RING_TYPE_VCE ||
			ring->funcs->type == AMDGPU_RING_TYPE_UVD_ENC ||
			ring->funcs->type == AMDGPU_RING_TYPE_VCN_DEC ||
			ring->funcs->type == AMDGPU_RING_TYPE_VCN_ENC ||
			ring->funcs->type == AMDGPU_RING_TYPE_VCN_JPEG)
			पंचांगo = पंचांगo_mm;
		अन्यथा
			पंचांगo = पंचांगo_gfx;

		r = amdgpu_ring_test_ib(ring, पंचांगo);
		अगर (!r) अणु
			DRM_DEV_DEBUG(adev->dev, "ib test on %s succeeded\n",
				      ring->name);
			जारी;
		पूर्ण

		ring->sched.पढ़ोy = false;
		DRM_DEV_ERROR(adev->dev, "IB test failed on %s (%d).\n",
			  ring->name, r);

		अगर (ring == &adev->gfx.gfx_ring[0]) अणु
			/* oh, oh, that's really bad */
			adev->accel_working = false;
			वापस r;

		पूर्ण अन्यथा अणु
			ret = r;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Debugfs info
 */
#अगर defined(CONFIG_DEBUG_FS)

अटल पूर्णांक amdgpu_debugfs_sa_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)m->निजी;

	seq_म_लिखो(m, "--------------------- DELAYED --------------------- \n");
	amdgpu_sa_bo_dump_debug_info(&adev->ib_pools[AMDGPU_IB_POOL_DELAYED],
				     m);
	seq_म_लिखो(m, "-------------------- IMMEDIATE -------------------- \n");
	amdgpu_sa_bo_dump_debug_info(&adev->ib_pools[AMDGPU_IB_POOL_IMMEDIATE],
				     m);
	seq_म_लिखो(m, "--------------------- DIRECT ---------------------- \n");
	amdgpu_sa_bo_dump_debug_info(&adev->ib_pools[AMDGPU_IB_POOL_सूचीECT], m);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(amdgpu_debugfs_sa_info);

#पूर्ण_अगर

व्योम amdgpu_debugfs_sa_init(काष्ठा amdgpu_device *adev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा drm_minor *minor = adev_to_drm(adev)->primary;
	काष्ठा dentry *root = minor->debugfs_root;

	debugfs_create_file("amdgpu_sa_info", 0444, root, adev,
			    &amdgpu_debugfs_sa_info_fops);

#पूर्ण_अगर
पूर्ण
