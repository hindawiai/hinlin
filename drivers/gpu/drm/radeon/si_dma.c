<शैली गुरु>
/*
 * Copyright 2013 Advanced Micro Devices, Inc.
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
 * Authors: Alex Deucher
 */

#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_trace.h"
#समावेश "si.h"
#समावेश "sid.h"

/**
 * si_dma_is_lockup - Check अगर the DMA engine is locked up
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Check अगर the async DMA engine is locked up.
 * Returns true अगर the engine appears to be locked up, false अगर not.
 */
bool si_dma_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	u32 reset_mask = si_gpu_check_soft_reset(rdev);
	u32 mask;

	अगर (ring->idx == R600_RING_TYPE_DMA_INDEX)
		mask = RADEON_RESET_DMA;
	अन्यथा
		mask = RADEON_RESET_DMA1;

	अगर (!(reset_mask & mask)) अणु
		radeon_ring_lockup_update(rdev, ring);
		वापस false;
	पूर्ण
	वापस radeon_ring_test_lockup(rdev, ring);
पूर्ण

/**
 * si_dma_vm_copy_pages - update PTEs by copying them from the GART
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @src: src addr where to copy from
 * @count: number of page entries to update
 *
 * Update PTEs by copying them from the GART using the DMA (SI).
 */
व्योम si_dma_vm_copy_pages(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_ib *ib,
			  uपूर्णांक64_t pe, uपूर्णांक64_t src,
			  अचिन्हित count)
अणु
	जबतक (count) अणु
		अचिन्हित bytes = count * 8;
		अगर (bytes > 0xFFFF8)
			bytes = 0xFFFF8;

		ib->ptr[ib->length_dw++] = DMA_PACKET(DMA_PACKET_COPY,
						      1, 0, 0, bytes);
		ib->ptr[ib->length_dw++] = lower_32_bits(pe);
		ib->ptr[ib->length_dw++] = lower_32_bits(src);
		ib->ptr[ib->length_dw++] = upper_32_bits(pe) & 0xff;
		ib->ptr[ib->length_dw++] = upper_32_bits(src) & 0xff;

		pe += bytes;
		src += bytes;
		count -= bytes / 8;
	पूर्ण
पूर्ण

/**
 * si_dma_vm_ग_लिखो_pages - update PTEs by writing them manually
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @addr: dst addr to ग_लिखो पूर्णांकo pe
 * @count: number of page entries to update
 * @incr: increase next addr by incr bytes
 * @flags: access flags
 *
 * Update PTEs by writing them manually using the DMA (SI).
 */
व्योम si_dma_vm_ग_लिखो_pages(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ib *ib,
			   uपूर्णांक64_t pe,
			   uपूर्णांक64_t addr, अचिन्हित count,
			   uपूर्णांक32_t incr, uपूर्णांक32_t flags)
अणु
	uपूर्णांक64_t value;
	अचिन्हित ndw;

	जबतक (count) अणु
		ndw = count * 2;
		अगर (ndw > 0xFFFFE)
			ndw = 0xFFFFE;

		/* क्रम non-physically contiguous pages (प्रणाली) */
		ib->ptr[ib->length_dw++] = DMA_PACKET(DMA_PACKET_WRITE, 0, 0, 0, ndw);
		ib->ptr[ib->length_dw++] = pe;
		ib->ptr[ib->length_dw++] = upper_32_bits(pe) & 0xff;
		क्रम (; ndw > 0; ndw -= 2, --count, pe += 8) अणु
			अगर (flags & R600_PTE_SYSTEM) अणु
				value = radeon_vm_map_gart(rdev, addr);
			पूर्ण अन्यथा अगर (flags & R600_PTE_VALID) अणु
				value = addr;
			पूर्ण अन्यथा अणु
				value = 0;
			पूर्ण
			addr += incr;
			value |= flags;
			ib->ptr[ib->length_dw++] = value;
			ib->ptr[ib->length_dw++] = upper_32_bits(value);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * si_dma_vm_set_pages - update the page tables using the DMA
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @addr: dst addr to ग_लिखो पूर्णांकo pe
 * @count: number of page entries to update
 * @incr: increase next addr by incr bytes
 * @flags: access flags
 *
 * Update the page tables using the DMA (SI).
 */
व्योम si_dma_vm_set_pages(काष्ठा radeon_device *rdev,
			 काष्ठा radeon_ib *ib,
			 uपूर्णांक64_t pe,
			 uपूर्णांक64_t addr, अचिन्हित count,
			 uपूर्णांक32_t incr, uपूर्णांक32_t flags)
अणु
	uपूर्णांक64_t value;
	अचिन्हित ndw;

	जबतक (count) अणु
		ndw = count * 2;
		अगर (ndw > 0xFFFFE)
			ndw = 0xFFFFE;

		अगर (flags & R600_PTE_VALID)
			value = addr;
		अन्यथा
			value = 0;

		/* क्रम physically contiguous pages (vram) */
		ib->ptr[ib->length_dw++] = DMA_PTE_PDE_PACKET(ndw);
		ib->ptr[ib->length_dw++] = pe; /* dst addr */
		ib->ptr[ib->length_dw++] = upper_32_bits(pe) & 0xff;
		ib->ptr[ib->length_dw++] = flags; /* mask */
		ib->ptr[ib->length_dw++] = 0;
		ib->ptr[ib->length_dw++] = value; /* value */
		ib->ptr[ib->length_dw++] = upper_32_bits(value);
		ib->ptr[ib->length_dw++] = incr; /* increment size */
		ib->ptr[ib->length_dw++] = 0;
		pe += ndw * 4;
		addr += (ndw / 2) * incr;
		count -= ndw / 2;
	पूर्ण
पूर्ण

व्योम si_dma_vm_flush(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
		     अचिन्हित vm_id, uपूर्णांक64_t pd_addr)

अणु
	radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_SRBM_WRITE, 0, 0, 0, 0));
	अगर (vm_id < 8) अणु
		radeon_ring_ग_लिखो(ring, (0xf << 16) | ((VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + (vm_id << 2)) >> 2));
	पूर्ण अन्यथा अणु
		radeon_ring_ग_लिखो(ring, (0xf << 16) | ((VM_CONTEXT8_PAGE_TABLE_BASE_ADDR + ((vm_id - 8) << 2)) >> 2));
	पूर्ण
	radeon_ring_ग_लिखो(ring, pd_addr >> 12);

	/* flush hdp cache */
	radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_SRBM_WRITE, 0, 0, 0, 0));
	radeon_ring_ग_लिखो(ring, (0xf << 16) | (HDP_MEM_COHERENCY_FLUSH_CNTL >> 2));
	radeon_ring_ग_लिखो(ring, 1);

	/* bits 0-7 are the VM contexts0-7 */
	radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_SRBM_WRITE, 0, 0, 0, 0));
	radeon_ring_ग_लिखो(ring, (0xf << 16) | (VM_INVALIDATE_REQUEST >> 2));
	radeon_ring_ग_लिखो(ring, 1 << vm_id);

	/* रुको क्रम invalidate to complete */
	radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_POLL_REG_MEM, 0, 0, 0, 0));
	radeon_ring_ग_लिखो(ring, VM_INVALIDATE_REQUEST);
	radeon_ring_ग_लिखो(ring, 0xff << 16); /* retry */
	radeon_ring_ग_लिखो(ring, 1 << vm_id); /* mask */
	radeon_ring_ग_लिखो(ring, 0); /* value */
	radeon_ring_ग_लिखो(ring, (0 << 28) | 0x20); /* func(always) | poll पूर्णांकerval */
पूर्ण

/**
 * si_copy_dma - copy pages using the DMA engine
 *
 * @rdev: radeon_device poपूर्णांकer
 * @src_offset: src GPU address
 * @dst_offset: dst GPU address
 * @num_gpu_pages: number of GPU pages to xfer
 * @resv: reservation object to sync to
 *
 * Copy GPU paging using the DMA engine (SI).
 * Used by the radeon tपंचांग implementation to move pages अगर
 * रेजिस्टरed as the asic copy callback.
 */
काष्ठा radeon_fence *si_copy_dma(काष्ठा radeon_device *rdev,
				 uपूर्णांक64_t src_offset, uपूर्णांक64_t dst_offset,
				 अचिन्हित num_gpu_pages,
				 काष्ठा dma_resv *resv)
अणु
	काष्ठा radeon_fence *fence;
	काष्ठा radeon_sync sync;
	पूर्णांक ring_index = rdev->asic->copy.dma_ring_index;
	काष्ठा radeon_ring *ring = &rdev->ring[ring_index];
	u32 size_in_bytes, cur_size_in_bytes;
	पूर्णांक i, num_loops;
	पूर्णांक r = 0;

	radeon_sync_create(&sync);

	size_in_bytes = (num_gpu_pages << RADEON_GPU_PAGE_SHIFT);
	num_loops = DIV_ROUND_UP(size_in_bytes, 0xfffff);
	r = radeon_ring_lock(rdev, ring, num_loops * 5 + 11);
	अगर (r) अणु
		DRM_ERROR("radeon: moving bo (%d).\n", r);
		radeon_sync_मुक्त(rdev, &sync, शून्य);
		वापस ERR_PTR(r);
	पूर्ण

	radeon_sync_resv(rdev, &sync, resv, false);
	radeon_sync_rings(rdev, &sync, ring->idx);

	क्रम (i = 0; i < num_loops; i++) अणु
		cur_size_in_bytes = size_in_bytes;
		अगर (cur_size_in_bytes > 0xFFFFF)
			cur_size_in_bytes = 0xFFFFF;
		size_in_bytes -= cur_size_in_bytes;
		radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_COPY, 1, 0, 0, cur_size_in_bytes));
		radeon_ring_ग_लिखो(ring, lower_32_bits(dst_offset));
		radeon_ring_ग_लिखो(ring, lower_32_bits(src_offset));
		radeon_ring_ग_लिखो(ring, upper_32_bits(dst_offset) & 0xff);
		radeon_ring_ग_लिखो(ring, upper_32_bits(src_offset) & 0xff);
		src_offset += cur_size_in_bytes;
		dst_offset += cur_size_in_bytes;
	पूर्ण

	r = radeon_fence_emit(rdev, &fence, ring->idx);
	अगर (r) अणु
		radeon_ring_unlock_unकरो(rdev, ring);
		radeon_sync_मुक्त(rdev, &sync, शून्य);
		वापस ERR_PTR(r);
	पूर्ण

	radeon_ring_unlock_commit(rdev, ring, false);
	radeon_sync_मुक्त(rdev, &sync, fence);

	वापस fence;
पूर्ण

