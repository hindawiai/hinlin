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

#समावेश <drm/drm_file.h>

#समावेश "radeon.h"

/*
 * IB
 * IBs (Indirect Buffers) and areas of GPU accessible memory where
 * commands are stored.  You can put a poपूर्णांकer to the IB in the
 * command ring and the hw will fetch the commands from the IB
 * and execute them.  Generally userspace acceleration drivers
 * produce command buffers which are send to the kernel and
 * put in IBs क्रम execution by the requested ring.
 */
अटल व्योम radeon_debugfs_sa_init(काष्ठा radeon_device *rdev);

/**
 * radeon_ib_get - request an IB (Indirect Buffer)
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: ring index the IB is associated with
 * @vm: requested vm
 * @ib: IB object वापसed
 * @size: requested IB size
 *
 * Request an IB (all asics).  IBs are allocated using the
 * suballocator.
 * Returns 0 on success, error on failure.
 */
पूर्णांक radeon_ib_get(काष्ठा radeon_device *rdev, पूर्णांक ring,
		  काष्ठा radeon_ib *ib, काष्ठा radeon_vm *vm,
		  अचिन्हित size)
अणु
	पूर्णांक r;

	r = radeon_sa_bo_new(rdev, &rdev->ring_पंचांगp_bo, &ib->sa_bo, size, 256);
	अगर (r) अणु
		dev_err(rdev->dev, "failed to get a new IB (%d)\n", r);
		वापस r;
	पूर्ण

	radeon_sync_create(&ib->sync);

	ib->ring = ring;
	ib->fence = शून्य;
	ib->ptr = radeon_sa_bo_cpu_addr(ib->sa_bo);
	ib->vm = vm;
	अगर (vm) अणु
		/* ib pool is bound at RADEON_VA_IB_OFFSET in भव address
		 * space and soffset is the offset inside the pool bo
		 */
		ib->gpu_addr = ib->sa_bo->soffset + RADEON_VA_IB_OFFSET;
	पूर्ण अन्यथा अणु
		ib->gpu_addr = radeon_sa_bo_gpu_addr(ib->sa_bo);
	पूर्ण
	ib->is_स्थिर_ib = false;

	वापस 0;
पूर्ण

/**
 * radeon_ib_मुक्त - मुक्त an IB (Indirect Buffer)
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: IB object to मुक्त
 *
 * Free an IB (all asics).
 */
व्योम radeon_ib_मुक्त(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib)
अणु
	radeon_sync_मुक्त(rdev, &ib->sync, ib->fence);
	radeon_sa_bo_मुक्त(rdev, &ib->sa_bo, ib->fence);
	radeon_fence_unref(&ib->fence);
पूर्ण

/**
 * radeon_ib_schedule - schedule an IB (Indirect Buffer) on the ring
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: IB object to schedule
 * @स्थिर_ib: Const IB to schedule (SI only)
 * @hdp_flush: Whether or not to perक्रमm an HDP cache flush
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
पूर्णांक radeon_ib_schedule(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib,
		       काष्ठा radeon_ib *स्थिर_ib, bool hdp_flush)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[ib->ring];
	पूर्णांक r = 0;

	अगर (!ib->length_dw || !ring->पढ़ोy) अणु
		/* TODO: Nothings in the ib we should report. */
		dev_err(rdev->dev, "couldn't schedule ib\n");
		वापस -EINVAL;
	पूर्ण

	/* 64 dwords should be enough क्रम fence too */
	r = radeon_ring_lock(rdev, ring, 64 + RADEON_NUM_SYNCS * 8);
	अगर (r) अणु
		dev_err(rdev->dev, "scheduling IB failed (%d).\n", r);
		वापस r;
	पूर्ण

	/* grab a vm id अगर necessary */
	अगर (ib->vm) अणु
		काष्ठा radeon_fence *vm_id_fence;
		vm_id_fence = radeon_vm_grab_id(rdev, ib->vm, ib->ring);
		radeon_sync_fence(&ib->sync, vm_id_fence);
	पूर्ण

	/* sync with other rings */
	r = radeon_sync_rings(rdev, &ib->sync, ib->ring);
	अगर (r) अणु
		dev_err(rdev->dev, "failed to sync rings (%d)\n", r);
		radeon_ring_unlock_unकरो(rdev, ring);
		वापस r;
	पूर्ण

	अगर (ib->vm)
		radeon_vm_flush(rdev, ib->vm, ib->ring,
				ib->sync.last_vm_update);

	अगर (स्थिर_ib) अणु
		radeon_ring_ib_execute(rdev, स्थिर_ib->ring, स्थिर_ib);
		radeon_sync_मुक्त(rdev, &स्थिर_ib->sync, शून्य);
	पूर्ण
	radeon_ring_ib_execute(rdev, ib->ring, ib);
	r = radeon_fence_emit(rdev, &ib->fence, ib->ring);
	अगर (r) अणु
		dev_err(rdev->dev, "failed to emit fence for new IB (%d)\n", r);
		radeon_ring_unlock_unकरो(rdev, ring);
		वापस r;
	पूर्ण
	अगर (स्थिर_ib) अणु
		स्थिर_ib->fence = radeon_fence_ref(ib->fence);
	पूर्ण

	अगर (ib->vm)
		radeon_vm_fence(rdev, ib->vm, ib->fence);

	radeon_ring_unlock_commit(rdev, ring, hdp_flush);
	वापस 0;
पूर्ण

/**
 * radeon_ib_pool_init - Init the IB (Indirect Buffer) pool
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Initialize the suballocator to manage a pool of memory
 * क्रम use as IBs (all asics).
 * Returns 0 on success, error on failure.
 */
पूर्णांक radeon_ib_pool_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (rdev->ib_pool_पढ़ोy) अणु
		वापस 0;
	पूर्ण

	अगर (rdev->family >= CHIP_BONAIRE) अणु
		r = radeon_sa_bo_manager_init(rdev, &rdev->ring_पंचांगp_bo,
					      RADEON_IB_POOL_SIZE*64*1024,
					      RADEON_GPU_PAGE_SIZE,
					      RADEON_GEM_DOMAIN_GTT,
					      RADEON_GEM_GTT_WC);
	पूर्ण अन्यथा अणु
		/* Beक्रमe CIK, it's better to stick to cacheable GTT due
		 * to the command stream checking
		 */
		r = radeon_sa_bo_manager_init(rdev, &rdev->ring_पंचांगp_bo,
					      RADEON_IB_POOL_SIZE*64*1024,
					      RADEON_GPU_PAGE_SIZE,
					      RADEON_GEM_DOMAIN_GTT, 0);
	पूर्ण
	अगर (r) अणु
		वापस r;
	पूर्ण

	r = radeon_sa_bo_manager_start(rdev, &rdev->ring_पंचांगp_bo);
	अगर (r) अणु
		वापस r;
	पूर्ण

	rdev->ib_pool_पढ़ोy = true;
	radeon_debugfs_sa_init(rdev);
	वापस 0;
पूर्ण

/**
 * radeon_ib_pool_fini - Free the IB (Indirect Buffer) pool
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Tear करोwn the suballocator managing the pool of memory
 * क्रम use as IBs (all asics).
 */
व्योम radeon_ib_pool_fini(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->ib_pool_पढ़ोy) अणु
		radeon_sa_bo_manager_suspend(rdev, &rdev->ring_पंचांगp_bo);
		radeon_sa_bo_manager_fini(rdev, &rdev->ring_पंचांगp_bo);
		rdev->ib_pool_पढ़ोy = false;
	पूर्ण
पूर्ण

/**
 * radeon_ib_ring_tests - test IBs on the rings
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Test an IB (Indirect Buffer) on each ring.
 * If the test fails, disable the ring.
 * Returns 0 on success, error अगर the primary GFX ring
 * IB test fails.
 */
पूर्णांक radeon_ib_ring_tests(काष्ठा radeon_device *rdev)
अणु
	अचिन्हित i;
	पूर्णांक r;

	क्रम (i = 0; i < RADEON_NUM_RINGS; ++i) अणु
		काष्ठा radeon_ring *ring = &rdev->ring[i];

		अगर (!ring->पढ़ोy)
			जारी;

		r = radeon_ib_test(rdev, i, ring);
		अगर (r) अणु
			radeon_fence_driver_क्रमce_completion(rdev, i);
			ring->पढ़ोy = false;
			rdev->needs_reset = false;

			अगर (i == RADEON_RING_TYPE_GFX_INDEX) अणु
				/* oh, oh, that's really bad */
				DRM_ERROR("radeon: failed testing IB on GFX ring (%d).\n", r);
				rdev->accel_working = false;
				वापस r;

			पूर्ण अन्यथा अणु
				/* still not good, but we can live with it */
				DRM_ERROR("radeon: failed testing IB on ring %d (%d).\n", i, r);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Debugfs info
 */
#अगर defined(CONFIG_DEBUG_FS)

अटल पूर्णांक radeon_debugfs_sa_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;

	radeon_sa_bo_dump_debug_info(&rdev->ring_पंचांगp_bo, m);

	वापस 0;

पूर्ण

DEFINE_SHOW_ATTRIBUTE(radeon_debugfs_sa_info);

#पूर्ण_अगर

अटल व्योम radeon_debugfs_sa_init(काष्ठा radeon_device *rdev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा dentry *root = rdev->ddev->primary->debugfs_root;

	debugfs_create_file("radeon_sa_info", 0444, root, rdev,
			    &radeon_debugfs_sa_info_fops);
#पूर्ण_अगर
पूर्ण
