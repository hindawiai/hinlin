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

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>

#समावेश "radeon.h"

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
अटल व्योम radeon_debugfs_ring_init(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);

/**
 * radeon_ring_supports_scratch_reg - check अगर the ring supports
 * writing to scratch रेजिस्टरs
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Check अगर a specअगरic ring supports writing to scratch रेजिस्टरs (all asics).
 * Returns true अगर the ring supports writing to scratch regs, false अगर not.
 */
bool radeon_ring_supports_scratch_reg(काष्ठा radeon_device *rdev,
				      काष्ठा radeon_ring *ring)
अणु
	चयन (ring->idx) अणु
	हाल RADEON_RING_TYPE_GFX_INDEX:
	हाल CAYMAN_RING_TYPE_CP1_INDEX:
	हाल CAYMAN_RING_TYPE_CP2_INDEX:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/**
 * radeon_ring_मुक्त_size - update the मुक्त size
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Update the मुक्त dw slots in the ring buffer (all asics).
 */
व्योम radeon_ring_मुक्त_size(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	uपूर्णांक32_t rptr = radeon_ring_get_rptr(rdev, ring);

	/* This works because ring_size is a घातer of 2 */
	ring->ring_मुक्त_dw = rptr + (ring->ring_size / 4);
	ring->ring_मुक्त_dw -= ring->wptr;
	ring->ring_मुक्त_dw &= ring->ptr_mask;
	अगर (!ring->ring_मुक्त_dw) अणु
		/* this is an empty ring */
		ring->ring_मुक्त_dw = ring->ring_size / 4;
		/*  update lockup info to aव्योम false positive */
		radeon_ring_lockup_update(rdev, ring);
	पूर्ण
पूर्ण

/**
 * radeon_ring_alloc - allocate space on the ring buffer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 * @ndw: number of dwords to allocate in the ring buffer
 *
 * Allocate @ndw dwords in the ring buffer (all asics).
 * Returns 0 on success, error on failure.
 */
पूर्णांक radeon_ring_alloc(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring, अचिन्हित ndw)
अणु
	पूर्णांक r;

	/* make sure we aren't trying to allocate more space than there is on the ring */
	अगर (ndw > (ring->ring_size / 4))
		वापस -ENOMEM;
	/* Align requested size with padding so unlock_commit can
	 * pad safely */
	radeon_ring_मुक्त_size(rdev, ring);
	ndw = (ndw + ring->align_mask) & ~ring->align_mask;
	जबतक (ndw > (ring->ring_मुक्त_dw - 1)) अणु
		radeon_ring_मुक्त_size(rdev, ring);
		अगर (ndw < ring->ring_मुक्त_dw) अणु
			अवरोध;
		पूर्ण
		r = radeon_fence_रुको_next(rdev, ring->idx);
		अगर (r)
			वापस r;
	पूर्ण
	ring->count_dw = ndw;
	ring->wptr_old = ring->wptr;
	वापस 0;
पूर्ण

/**
 * radeon_ring_lock - lock the ring and allocate space on it
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 * @ndw: number of dwords to allocate in the ring buffer
 *
 * Lock the ring and allocate @ndw dwords in the ring buffer
 * (all asics).
 * Returns 0 on success, error on failure.
 */
पूर्णांक radeon_ring_lock(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring, अचिन्हित ndw)
अणु
	पूर्णांक r;

	mutex_lock(&rdev->ring_lock);
	r = radeon_ring_alloc(rdev, ring, ndw);
	अगर (r) अणु
		mutex_unlock(&rdev->ring_lock);
		वापस r;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * radeon_ring_commit - tell the GPU to execute the new
 * commands on the ring buffer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 * @hdp_flush: Whether or not to perक्रमm an HDP cache flush
 *
 * Update the wptr (ग_लिखो poपूर्णांकer) to tell the GPU to
 * execute new commands on the ring buffer (all asics).
 */
व्योम radeon_ring_commit(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
			bool hdp_flush)
अणु
	/* If we are emitting the HDP flush via the ring buffer, we need to
	 * करो it beक्रमe padding.
	 */
	अगर (hdp_flush && rdev->asic->ring[ring->idx]->hdp_flush)
		rdev->asic->ring[ring->idx]->hdp_flush(rdev, ring);
	/* We pad to match fetch size */
	जबतक (ring->wptr & ring->align_mask) अणु
		radeon_ring_ग_लिखो(ring, ring->nop);
	पूर्ण
	mb();
	/* If we are emitting the HDP flush via MMIO, we need to करो it after
	 * all CPU ग_लिखोs to VRAM finished.
	 */
	अगर (hdp_flush && rdev->asic->mmio_hdp_flush)
		rdev->asic->mmio_hdp_flush(rdev);
	radeon_ring_set_wptr(rdev, ring);
पूर्ण

/**
 * radeon_ring_unlock_commit - tell the GPU to execute the new
 * commands on the ring buffer and unlock it
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 * @hdp_flush: Whether or not to perक्रमm an HDP cache flush
 *
 * Call radeon_ring_commit() then unlock the ring (all asics).
 */
व्योम radeon_ring_unlock_commit(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
			       bool hdp_flush)
अणु
	radeon_ring_commit(rdev, ring, hdp_flush);
	mutex_unlock(&rdev->ring_lock);
पूर्ण

/**
 * radeon_ring_unकरो - reset the wptr
 *
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Reset the driver's copy of the wptr (all asics).
 */
व्योम radeon_ring_unकरो(काष्ठा radeon_ring *ring)
अणु
	ring->wptr = ring->wptr_old;
पूर्ण

/**
 * radeon_ring_unlock_unकरो - reset the wptr and unlock the ring
 *
 * @rdev:       radeon device काष्ठाure
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Call radeon_ring_unकरो() then unlock the ring (all asics).
 */
व्योम radeon_ring_unlock_unकरो(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	radeon_ring_unकरो(ring);
	mutex_unlock(&rdev->ring_lock);
पूर्ण

/**
 * radeon_ring_lockup_update - update lockup variables
 *
 * @rdev:       radeon device काष्ठाure
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Update the last rptr value and बारtamp (all asics).
 */
व्योम radeon_ring_lockup_update(काष्ठा radeon_device *rdev,
			       काष्ठा radeon_ring *ring)
अणु
	atomic_set(&ring->last_rptr, radeon_ring_get_rptr(rdev, ring));
	atomic64_set(&ring->last_activity, jअगरfies_64);
पूर्ण

/**
 * radeon_ring_test_lockup() - check अगर ring is lockedup by recording inक्रमmation
 * @rdev:       radeon device काष्ठाure
 * @ring:       radeon_ring काष्ठाure holding ring inक्रमmation
 *
 */
bool radeon_ring_test_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	uपूर्णांक32_t rptr = radeon_ring_get_rptr(rdev, ring);
	uपूर्णांक64_t last = atomic64_पढ़ो(&ring->last_activity);
	uपूर्णांक64_t elapsed;

	अगर (rptr != atomic_पढ़ो(&ring->last_rptr)) अणु
		/* ring is still working, no lockup */
		radeon_ring_lockup_update(rdev, ring);
		वापस false;
	पूर्ण

	elapsed = jअगरfies_to_msecs(jअगरfies_64 - last);
	अगर (radeon_lockup_समयout && elapsed >= radeon_lockup_समयout) अणु
		dev_err(rdev->dev, "ring %d stalled for more than %llumsec\n",
			ring->idx, elapsed);
		वापस true;
	पूर्ण
	/* give a chance to the GPU ... */
	वापस false;
पूर्ण

/**
 * radeon_ring_backup - Back up the content of a ring
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: the ring we want to back up
 * @data: placeholder क्रम वापसed commit data
 *
 * Saves all unprocessed commits from a ring, वापसs the number of dwords saved.
 */
अचिन्हित radeon_ring_backup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
			    uपूर्णांक32_t **data)
अणु
	अचिन्हित size, ptr, i;

	/* just in हाल lock the ring */
	mutex_lock(&rdev->ring_lock);
	*data = शून्य;

	अगर (ring->ring_obj == शून्य) अणु
		mutex_unlock(&rdev->ring_lock);
		वापस 0;
	पूर्ण

	/* it करोesn't make sense to save anything अगर all fences are संकेतed */
	अगर (!radeon_fence_count_emitted(rdev, ring->idx)) अणु
		mutex_unlock(&rdev->ring_lock);
		वापस 0;
	पूर्ण

	/* calculate the number of dw on the ring */
	अगर (ring->rptr_save_reg)
		ptr = RREG32(ring->rptr_save_reg);
	अन्यथा अगर (rdev->wb.enabled)
		ptr = le32_to_cpu(*ring->next_rptr_cpu_addr);
	अन्यथा अणु
		/* no way to पढ़ो back the next rptr */
		mutex_unlock(&rdev->ring_lock);
		वापस 0;
	पूर्ण

	size = ring->wptr + (ring->ring_size / 4);
	size -= ptr;
	size &= ring->ptr_mask;
	अगर (size == 0) अणु
		mutex_unlock(&rdev->ring_lock);
		वापस 0;
	पूर्ण

	/* and then save the content of the ring */
	*data = kvदो_स्मृति_array(size, माप(uपूर्णांक32_t), GFP_KERNEL);
	अगर (!*data) अणु
		mutex_unlock(&rdev->ring_lock);
		वापस 0;
	पूर्ण
	क्रम (i = 0; i < size; ++i) अणु
		(*data)[i] = ring->ring[ptr++];
		ptr &= ring->ptr_mask;
	पूर्ण

	mutex_unlock(&rdev->ring_lock);
	वापस size;
पूर्ण

/**
 * radeon_ring_restore - append saved commands to the ring again
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: ring to append commands to
 * @size: number of dwords we want to ग_लिखो
 * @data: saved commands
 *
 * Allocates space on the ring and restore the previously saved commands.
 */
पूर्णांक radeon_ring_restore(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
			अचिन्हित size, uपूर्णांक32_t *data)
अणु
	पूर्णांक i, r;

	अगर (!size || !data)
		वापस 0;

	/* restore the saved ring content */
	r = radeon_ring_lock(rdev, ring, size);
	अगर (r)
		वापस r;

	क्रम (i = 0; i < size; ++i) अणु
		radeon_ring_ग_लिखो(ring, data[i]);
	पूर्ण

	radeon_ring_unlock_commit(rdev, ring, false);
	kvमुक्त(data);
	वापस 0;
पूर्ण

/**
 * radeon_ring_init - init driver ring काष्ठा.
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 * @ring_size: size of the ring
 * @rptr_offs: offset of the rptr ग_लिखोback location in the WB buffer
 * @nop: nop packet क्रम this ring
 *
 * Initialize the driver inक्रमmation क्रम the selected ring (all asics).
 * Returns 0 on success, error on failure.
 */
पूर्णांक radeon_ring_init(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring, अचिन्हित ring_size,
		     अचिन्हित rptr_offs, u32 nop)
अणु
	पूर्णांक r;

	ring->ring_size = ring_size;
	ring->rptr_offs = rptr_offs;
	ring->nop = nop;
	ring->rdev = rdev;
	/* Allocate ring buffer */
	अगर (ring->ring_obj == शून्य) अणु
		r = radeon_bo_create(rdev, ring->ring_size, PAGE_SIZE, true,
				     RADEON_GEM_DOMAIN_GTT, 0, शून्य,
				     शून्य, &ring->ring_obj);
		अगर (r) अणु
			dev_err(rdev->dev, "(%d) ring create failed\n", r);
			वापस r;
		पूर्ण
		r = radeon_bo_reserve(ring->ring_obj, false);
		अगर (unlikely(r != 0))
			वापस r;
		r = radeon_bo_pin(ring->ring_obj, RADEON_GEM_DOMAIN_GTT,
					&ring->gpu_addr);
		अगर (r) अणु
			radeon_bo_unreserve(ring->ring_obj);
			dev_err(rdev->dev, "(%d) ring pin failed\n", r);
			वापस r;
		पूर्ण
		r = radeon_bo_kmap(ring->ring_obj,
				       (व्योम **)&ring->ring);
		radeon_bo_unreserve(ring->ring_obj);
		अगर (r) अणु
			dev_err(rdev->dev, "(%d) ring map failed\n", r);
			वापस r;
		पूर्ण
	पूर्ण
	ring->ptr_mask = (ring->ring_size / 4) - 1;
	ring->ring_मुक्त_dw = ring->ring_size / 4;
	अगर (rdev->wb.enabled) अणु
		u32 index = RADEON_WB_RING0_NEXT_RPTR + (ring->idx * 4);
		ring->next_rptr_gpu_addr = rdev->wb.gpu_addr + index;
		ring->next_rptr_cpu_addr = &rdev->wb.wb[index/4];
	पूर्ण
	radeon_debugfs_ring_init(rdev, ring);
	radeon_ring_lockup_update(rdev, ring);
	वापस 0;
पूर्ण

/**
 * radeon_ring_fini - tear करोwn the driver ring काष्ठा.
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Tear करोwn the driver inक्रमmation क्रम the selected ring (all asics).
 */
व्योम radeon_ring_fini(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	पूर्णांक r;
	काष्ठा radeon_bo *ring_obj;

	mutex_lock(&rdev->ring_lock);
	ring_obj = ring->ring_obj;
	ring->पढ़ोy = false;
	ring->ring = शून्य;
	ring->ring_obj = शून्य;
	mutex_unlock(&rdev->ring_lock);

	अगर (ring_obj) अणु
		r = radeon_bo_reserve(ring_obj, false);
		अगर (likely(r == 0)) अणु
			radeon_bo_kunmap(ring_obj);
			radeon_bo_unpin(ring_obj);
			radeon_bo_unreserve(ring_obj);
		पूर्ण
		radeon_bo_unref(&ring_obj);
	पूर्ण
पूर्ण

/*
 * Debugfs info
 */
#अगर defined(CONFIG_DEBUG_FS)

अटल पूर्णांक radeon_debugfs_ring_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा radeon_ring *ring = (काष्ठा radeon_ring *) m->निजी;
	काष्ठा radeon_device *rdev = ring->rdev;

	uपूर्णांक32_t rptr, wptr, rptr_next;
	अचिन्हित count, i, j;

	radeon_ring_मुक्त_size(rdev, ring);
	count = (ring->ring_size / 4) - ring->ring_मुक्त_dw;

	wptr = radeon_ring_get_wptr(rdev, ring);
	seq_म_लिखो(m, "wptr: 0x%08x [%5d]\n",
		   wptr, wptr);

	rptr = radeon_ring_get_rptr(rdev, ring);
	seq_म_लिखो(m, "rptr: 0x%08x [%5d]\n",
		   rptr, rptr);

	अगर (ring->rptr_save_reg) अणु
		rptr_next = RREG32(ring->rptr_save_reg);
		seq_म_लिखो(m, "rptr next(0x%04x): 0x%08x [%5d]\n",
			   ring->rptr_save_reg, rptr_next, rptr_next);
	पूर्ण अन्यथा
		rptr_next = ~0;

	seq_म_लिखो(m, "driver's copy of the wptr: 0x%08x [%5d]\n",
		   ring->wptr, ring->wptr);
	seq_म_लिखो(m, "last semaphore signal addr : 0x%016llx\n",
		   ring->last_semaphore_संकेत_addr);
	seq_म_लिखो(m, "last semaphore wait addr   : 0x%016llx\n",
		   ring->last_semaphore_रुको_addr);
	seq_म_लिखो(m, "%u free dwords in ring\n", ring->ring_मुक्त_dw);
	seq_म_लिखो(m, "%u dwords in ring\n", count);

	अगर (!ring->ring)
		वापस 0;

	/* prपूर्णांक 8 dw beक्रमe current rptr as often it's the last executed
	 * packet that is the root issue
	 */
	i = (rptr + ring->ptr_mask + 1 - 32) & ring->ptr_mask;
	क्रम (j = 0; j <= (count + 32); j++) अणु
		seq_म_लिखो(m, "r[%5d]=0x%08x", i, ring->ring[i]);
		अगर (rptr == i)
			seq_माला_दो(m, " *");
		अगर (rptr_next == i)
			seq_माला_दो(m, " #");
		seq_माला_दो(m, "\n");
		i = (i + 1) & ring->ptr_mask;
	पूर्ण
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(radeon_debugfs_ring_info);

अटल स्थिर अक्षर *radeon_debugfs_ring_idx_to_name(uपूर्णांक32_t ridx)
अणु
	चयन (ridx) अणु
	हाल RADEON_RING_TYPE_GFX_INDEX:
		वापस "radeon_ring_gfx";
	हाल CAYMAN_RING_TYPE_CP1_INDEX:
		वापस "radeon_ring_cp1";
	हाल CAYMAN_RING_TYPE_CP2_INDEX:
		वापस "radeon_ring_cp2";
	हाल R600_RING_TYPE_DMA_INDEX:
		वापस "radeon_ring_dma1";
	हाल CAYMAN_RING_TYPE_DMA1_INDEX:
		वापस "radeon_ring_dma2";
	हाल R600_RING_TYPE_UVD_INDEX:
		वापस "radeon_ring_uvd";
	हाल TN_RING_TYPE_VCE1_INDEX:
		वापस "radeon_ring_vce1";
	हाल TN_RING_TYPE_VCE2_INDEX:
		वापस "radeon_ring_vce2";
	शेष:
		वापस शून्य;

	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम radeon_debugfs_ring_init(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	स्थिर अक्षर *ring_name = radeon_debugfs_ring_idx_to_name(ring->idx);
	काष्ठा dentry *root = rdev->ddev->primary->debugfs_root;

	अगर (ring_name)
		debugfs_create_file(ring_name, 0444, root, ring,
				    &radeon_debugfs_ring_info_fops);

#पूर्ण_अगर
पूर्ण
