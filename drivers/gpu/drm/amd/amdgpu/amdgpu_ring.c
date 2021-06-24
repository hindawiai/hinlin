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
#समावेश <linux/uaccess.h>
#समावेश <linux/debugfs.h>

#समावेश <drm/amdgpu_drm.h>
#समावेश "amdgpu.h"
#समावेश "atom.h"

/*
 * Rings
 * Most engines on the GPU are fed via ring buffers.  Ring
 * buffers are areas of GPU accessible memory that the host
 * ग_लिखोs commands पूर्णांकo and the GPU पढ़ोs commands out of.
 * There is a rptr (पढ़ो poपूर्णांकer) that determines where the
 * GPU is currently पढ़ोing, and a wptr (ग_लिखो poपूर्णांकer)
 * which determines where the host has written.  When the
 * poपूर्णांकers are equal, the ring is idle.  When the host
 * ग_लिखोs commands to the ring buffer, it increments the
 * wptr.  The GPU then starts fetching commands and executes
 * them until the poपूर्णांकers are equal again.
 */

/**
 * amdgpu_ring_alloc - allocate space on the ring buffer
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 * @ndw: number of dwords to allocate in the ring buffer
 *
 * Allocate @ndw dwords in the ring buffer (all asics).
 * Returns 0 on success, error on failure.
 */
पूर्णांक amdgpu_ring_alloc(काष्ठा amdgpu_ring *ring, अचिन्हित ndw)
अणु
	/* Align requested size with padding so unlock_commit can
	 * pad safely */
	ndw = (ndw + ring->funcs->align_mask) & ~ring->funcs->align_mask;

	/* Make sure we aren't trying to allocate more space
	 * than the maximum क्रम one submission
	 */
	अगर (WARN_ON_ONCE(ndw > ring->max_dw))
		वापस -ENOMEM;

	ring->count_dw = ndw;
	ring->wptr_old = ring->wptr;

	अगर (ring->funcs->begin_use)
		ring->funcs->begin_use(ring);

	वापस 0;
पूर्ण

/** amdgpu_ring_insert_nop - insert NOP packets
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 * @count: the number of NOP packets to insert
 *
 * This is the generic insert_nop function क्रम rings except SDMA
 */
व्योम amdgpu_ring_insert_nop(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		amdgpu_ring_ग_लिखो(ring, ring->funcs->nop);
पूर्ण

/**
 * amdgpu_ring_generic_pad_ib - pad IB with NOP packets
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 * @ib: IB to add NOP packets to
 *
 * This is the generic pad_ib function क्रम rings except SDMA
 */
व्योम amdgpu_ring_generic_pad_ib(काष्ठा amdgpu_ring *ring, काष्ठा amdgpu_ib *ib)
अणु
	जबतक (ib->length_dw & ring->funcs->align_mask)
		ib->ptr[ib->length_dw++] = ring->funcs->nop;
पूर्ण

/**
 * amdgpu_ring_commit - tell the GPU to execute the new
 * commands on the ring buffer
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 *
 * Update the wptr (ग_लिखो poपूर्णांकer) to tell the GPU to
 * execute new commands on the ring buffer (all asics).
 */
व्योम amdgpu_ring_commit(काष्ठा amdgpu_ring *ring)
अणु
	uपूर्णांक32_t count;

	/* We pad to match fetch size */
	count = ring->funcs->align_mask + 1 -
		(ring->wptr & ring->funcs->align_mask);
	count %= ring->funcs->align_mask + 1;
	ring->funcs->insert_nop(ring, count);

	mb();
	amdgpu_ring_set_wptr(ring);

	अगर (ring->funcs->end_use)
		ring->funcs->end_use(ring);
पूर्ण

/**
 * amdgpu_ring_unकरो - reset the wptr
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 *
 * Reset the driver's copy of the wptr (all asics).
 */
व्योम amdgpu_ring_unकरो(काष्ठा amdgpu_ring *ring)
अणु
	ring->wptr = ring->wptr_old;

	अगर (ring->funcs->end_use)
		ring->funcs->end_use(ring);
पूर्ण

/**
 * amdgpu_ring_init - init driver ring काष्ठा.
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 * @max_dw: maximum number of dw क्रम ring alloc
 * @irq_src: पूर्णांकerrupt source to use क्रम this ring
 * @irq_type: पूर्णांकerrupt type to use क्रम this ring
 * @hw_prio: ring priority (NORMAL/HIGH)
 *
 * Initialize the driver inक्रमmation क्रम the selected ring (all asics).
 * Returns 0 on success, error on failure.
 */
पूर्णांक amdgpu_ring_init(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ring *ring,
		     अचिन्हित पूर्णांक max_dw, काष्ठा amdgpu_irq_src *irq_src,
		     अचिन्हित पूर्णांक irq_type, अचिन्हित पूर्णांक hw_prio,
		     atomic_t *sched_score)
अणु
	पूर्णांक r;
	पूर्णांक sched_hw_submission = amdgpu_sched_hw_submission;
	u32 *num_sched;
	u32 hw_ip;

	/* Set the hw submission limit higher क्रम KIQ because
	 * it's used क्रम a number of gfx/compute tasks by both
	 * KFD and KGD which may have outstanding fences and
	 * it करोesn't really use the gpu scheduler anyway;
	 * KIQ tasks get submitted directly to the ring.
	 */
	अगर (ring->funcs->type == AMDGPU_RING_TYPE_KIQ)
		sched_hw_submission = max(sched_hw_submission, 256);
	अन्यथा अगर (ring == &adev->sdma.instance[0].page)
		sched_hw_submission = 256;

	अगर (ring->adev == शून्य) अणु
		अगर (adev->num_rings >= AMDGPU_MAX_RINGS)
			वापस -EINVAL;

		ring->adev = adev;
		ring->idx = adev->num_rings++;
		adev->rings[ring->idx] = ring;
		r = amdgpu_fence_driver_init_ring(ring, sched_hw_submission,
						  sched_score);
		अगर (r)
			वापस r;
	पूर्ण

	r = amdgpu_device_wb_get(adev, &ring->rptr_offs);
	अगर (r) अणु
		dev_err(adev->dev, "(%d) ring rptr_offs wb alloc failed\n", r);
		वापस r;
	पूर्ण

	r = amdgpu_device_wb_get(adev, &ring->wptr_offs);
	अगर (r) अणु
		dev_err(adev->dev, "(%d) ring wptr_offs wb alloc failed\n", r);
		वापस r;
	पूर्ण

	r = amdgpu_device_wb_get(adev, &ring->fence_offs);
	अगर (r) अणु
		dev_err(adev->dev, "(%d) ring fence_offs wb alloc failed\n", r);
		वापस r;
	पूर्ण

	r = amdgpu_device_wb_get(adev, &ring->trail_fence_offs);
	अगर (r) अणु
		dev_err(adev->dev,
			"(%d) ring trail_fence_offs wb alloc failed\n", r);
		वापस r;
	पूर्ण
	ring->trail_fence_gpu_addr =
		adev->wb.gpu_addr + (ring->trail_fence_offs * 4);
	ring->trail_fence_cpu_addr = &adev->wb.wb[ring->trail_fence_offs];

	r = amdgpu_device_wb_get(adev, &ring->cond_exe_offs);
	अगर (r) अणु
		dev_err(adev->dev, "(%d) ring cond_exec_polling wb alloc failed\n", r);
		वापस r;
	पूर्ण
	ring->cond_exe_gpu_addr = adev->wb.gpu_addr + (ring->cond_exe_offs * 4);
	ring->cond_exe_cpu_addr = &adev->wb.wb[ring->cond_exe_offs];
	/* always set cond_exec_polling to CONTINUE */
	*ring->cond_exe_cpu_addr = 1;

	r = amdgpu_fence_driver_start_ring(ring, irq_src, irq_type);
	अगर (r) अणु
		dev_err(adev->dev, "failed initializing fences (%d).\n", r);
		वापस r;
	पूर्ण

	ring->ring_size = roundup_घात_of_two(max_dw * 4 * sched_hw_submission);

	ring->buf_mask = (ring->ring_size / 4) - 1;
	ring->ptr_mask = ring->funcs->support_64bit_ptrs ?
		0xffffffffffffffff : ring->buf_mask;
	/* Allocate ring buffer */
	अगर (ring->ring_obj == शून्य) अणु
		r = amdgpu_bo_create_kernel(adev, ring->ring_size + ring->funcs->extra_dw, PAGE_SIZE,
					    AMDGPU_GEM_DOMAIN_GTT,
					    &ring->ring_obj,
					    &ring->gpu_addr,
					    (व्योम **)&ring->ring);
		अगर (r) अणु
			dev_err(adev->dev, "(%d) ring create failed\n", r);
			वापस r;
		पूर्ण
		amdgpu_ring_clear_ring(ring);
	पूर्ण

	ring->max_dw = max_dw;
	ring->hw_prio = hw_prio;

	अगर (!ring->no_scheduler) अणु
		hw_ip = ring->funcs->type;
		num_sched = &adev->gpu_sched[hw_ip][hw_prio].num_scheds;
		adev->gpu_sched[hw_ip][hw_prio].sched[(*num_sched)++] =
			&ring->sched;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_ring_fini - tear करोwn the driver ring काष्ठा.
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 *
 * Tear करोwn the driver inक्रमmation क्रम the selected ring (all asics).
 */
व्योम amdgpu_ring_fini(काष्ठा amdgpu_ring *ring)
अणु

	/* Not to finish a ring which is not initialized */
	अगर (!(ring->adev) || !(ring->adev->rings[ring->idx]))
		वापस;

	ring->sched.पढ़ोy = false;

	amdgpu_device_wb_मुक्त(ring->adev, ring->rptr_offs);
	amdgpu_device_wb_मुक्त(ring->adev, ring->wptr_offs);

	amdgpu_device_wb_मुक्त(ring->adev, ring->cond_exe_offs);
	amdgpu_device_wb_मुक्त(ring->adev, ring->fence_offs);

	amdgpu_bo_मुक्त_kernel(&ring->ring_obj,
			      &ring->gpu_addr,
			      (व्योम **)&ring->ring);

	dma_fence_put(ring->vmid_रुको);
	ring->vmid_रुको = शून्य;
	ring->me = 0;

	ring->adev->rings[ring->idx] = शून्य;
पूर्ण

/**
 * amdgpu_ring_emit_reg_ग_लिखो_reg_रुको_helper - ring helper
 *
 * @ring: ring to ग_लिखो to
 * @reg0: रेजिस्टर to ग_लिखो
 * @reg1: रेजिस्टर to रुको on
 * @ref: reference value to ग_लिखो/रुको on
 * @mask: mask to रुको on
 *
 * Helper क्रम rings that करोn't support ग_लिखो and रुको in a
 * single oneshot packet.
 */
व्योम amdgpu_ring_emit_reg_ग_लिखो_reg_रुको_helper(काष्ठा amdgpu_ring *ring,
						uपूर्णांक32_t reg0, uपूर्णांक32_t reg1,
						uपूर्णांक32_t ref, uपूर्णांक32_t mask)
अणु
	amdgpu_ring_emit_wreg(ring, reg0, ref);
	amdgpu_ring_emit_reg_रुको(ring, reg1, mask, mask);
पूर्ण

/**
 * amdgpu_ring_soft_recovery - try to soft recover a ring lockup
 *
 * @ring: ring to try the recovery on
 * @vmid: VMID we try to get going again
 * @fence: समयकरोut fence
 *
 * Tries to get a ring proceeding again when it is stuck.
 */
bool amdgpu_ring_soft_recovery(काष्ठा amdgpu_ring *ring, अचिन्हित पूर्णांक vmid,
			       काष्ठा dma_fence *fence)
अणु
	kसमय_प्रकार deadline = kसमय_add_us(kसमय_get(), 10000);

	अगर (amdgpu_sriov_vf(ring->adev) || !ring->funcs->soft_recovery || !fence)
		वापस false;

	atomic_inc(&ring->adev->gpu_reset_counter);
	जबतक (!dma_fence_is_संकेतed(fence) &&
	       kसमय_प्रकारo_ns(kसमय_sub(deadline, kसमय_get())) > 0)
		ring->funcs->soft_recovery(ring, vmid);

	वापस dma_fence_is_संकेतed(fence);
पूर्ण

/*
 * Debugfs info
 */
#अगर defined(CONFIG_DEBUG_FS)

/* Layout of file is 12 bytes consisting of
 * - rptr
 * - wptr
 * - driver's copy of wptr
 *
 * followed by n-words of ring data
 */
अटल sमाप_प्रकार amdgpu_debugfs_ring_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
					माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_ring *ring = file_inode(f)->i_निजी;
	पूर्णांक r, i;
	uपूर्णांक32_t value, result, early[3];

	अगर (*pos & 3 || size & 3)
		वापस -EINVAL;

	result = 0;

	अगर (*pos < 12) अणु
		early[0] = amdgpu_ring_get_rptr(ring) & ring->buf_mask;
		early[1] = amdgpu_ring_get_wptr(ring) & ring->buf_mask;
		early[2] = ring->wptr & ring->buf_mask;
		क्रम (i = *pos / 4; i < 3 && size; i++) अणु
			r = put_user(early[i], (uपूर्णांक32_t *)buf);
			अगर (r)
				वापस r;
			buf += 4;
			result += 4;
			size -= 4;
			*pos += 4;
		पूर्ण
	पूर्ण

	जबतक (size) अणु
		अगर (*pos >= (ring->ring_size + 12))
			वापस result;

		value = ring->ring[(*pos - 12)/4];
		r = put_user(value, (uपूर्णांक32_t *)buf);
		अगर (r)
			वापस r;
		buf += 4;
		result += 4;
		size -= 4;
		*pos += 4;
	पूर्ण

	वापस result;
पूर्ण

अटल स्थिर काष्ठा file_operations amdgpu_debugfs_ring_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = amdgpu_debugfs_ring_पढ़ो,
	.llseek = शेष_llseek
पूर्ण;

#पूर्ण_अगर

पूर्णांक amdgpu_debugfs_ring_init(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_ring *ring)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा drm_minor *minor = adev_to_drm(adev)->primary;
	काष्ठा dentry *ent, *root = minor->debugfs_root;
	अक्षर name[32];

	प्र_लिखो(name, "amdgpu_ring_%s", ring->name);

	ent = debugfs_create_file(name,
				  S_IFREG | S_IRUGO, root,
				  ring, &amdgpu_debugfs_ring_fops);
	अगर (!ent)
		वापस -ENOMEM;

	i_size_ग_लिखो(ent->d_inode, ring->ring_size + 12);
	ring->ent = ent;
#पूर्ण_अगर
	वापस 0;
पूर्ण

/**
 * amdgpu_ring_test_helper - tests ring and set sched पढ़ोiness status
 *
 * @ring: ring to try the recovery on
 *
 * Tests ring and set sched पढ़ोiness status
 *
 * Returns 0 on success, error on failure.
 */
पूर्णांक amdgpu_ring_test_helper(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	पूर्णांक r;

	r = amdgpu_ring_test_ring(ring);
	अगर (r)
		DRM_DEV_ERROR(adev->dev, "ring %s test failed (%d)\n",
			      ring->name, r);
	अन्यथा
		DRM_DEV_DEBUG(adev->dev, "ring test on %s succeeded\n",
			      ring->name);

	ring->sched.पढ़ोy = !r;
	वापस r;
पूर्ण
