<शैली गुरु>
/*
 * Copyright 2010 Advanced Micro Devices, Inc.
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
#समावेश "ni.h"
#समावेश "nid.h"

/*
 * DMA
 * Starting with R600, the GPU has an asynchronous
 * DMA engine.  The programming model is very similar
 * to the 3D engine (ring buffer, IBs, etc.), but the
 * DMA controller has it's own packet क्रमmat that is
 * dअगरferent क्रमm the PM4 क्रमmat used by the 3D engine.
 * It supports copying data, writing embedded data,
 * solid fills, and a number of other things.  It also
 * has support क्रम tiling/detiling of buffers.
 * Cayman and newer support two asynchronous DMA engines.
 */

/**
 * cayman_dma_get_rptr - get the current पढ़ो poपूर्णांकer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon ring poपूर्णांकer
 *
 * Get the current rptr from the hardware (cayman+).
 */
uपूर्णांक32_t cayman_dma_get_rptr(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_ring *ring)
अणु
	u32 rptr, reg;

	अगर (rdev->wb.enabled) अणु
		rptr = rdev->wb.wb[ring->rptr_offs/4];
	पूर्ण अन्यथा अणु
		अगर (ring->idx == R600_RING_TYPE_DMA_INDEX)
			reg = DMA_RB_RPTR + DMA0_REGISTER_OFFSET;
		अन्यथा
			reg = DMA_RB_RPTR + DMA1_REGISTER_OFFSET;

		rptr = RREG32(reg);
	पूर्ण

	वापस (rptr & 0x3fffc) >> 2;
पूर्ण

/**
 * cayman_dma_get_wptr - get the current ग_लिखो poपूर्णांकer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon ring poपूर्णांकer
 *
 * Get the current wptr from the hardware (cayman+).
 */
uपूर्णांक32_t cayman_dma_get_wptr(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ring *ring)
अणु
	u32 reg;

	अगर (ring->idx == R600_RING_TYPE_DMA_INDEX)
		reg = DMA_RB_WPTR + DMA0_REGISTER_OFFSET;
	अन्यथा
		reg = DMA_RB_WPTR + DMA1_REGISTER_OFFSET;

	वापस (RREG32(reg) & 0x3fffc) >> 2;
पूर्ण

/**
 * cayman_dma_set_wptr - commit the ग_लिखो poपूर्णांकer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon ring poपूर्णांकer
 *
 * Write the wptr back to the hardware (cayman+).
 */
व्योम cayman_dma_set_wptr(काष्ठा radeon_device *rdev,
			 काष्ठा radeon_ring *ring)
अणु
	u32 reg;

	अगर (ring->idx == R600_RING_TYPE_DMA_INDEX)
		reg = DMA_RB_WPTR + DMA0_REGISTER_OFFSET;
	अन्यथा
		reg = DMA_RB_WPTR + DMA1_REGISTER_OFFSET;

	WREG32(reg, (ring->wptr << 2) & 0x3fffc);
पूर्ण

/**
 * cayman_dma_ring_ib_execute - Schedule an IB on the DMA engine
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: IB object to schedule
 *
 * Schedule an IB in the DMA ring (cayman-SI).
 */
व्योम cayman_dma_ring_ib_execute(काष्ठा radeon_device *rdev,
				काष्ठा radeon_ib *ib)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[ib->ring];
	अचिन्हित vm_id = ib->vm ? ib->vm->ids[ib->ring].id : 0;

	अगर (rdev->wb.enabled) अणु
		u32 next_rptr = ring->wptr + 4;
		जबतक ((next_rptr & 7) != 5)
			next_rptr++;
		next_rptr += 3;
		radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_WRITE, 0, 0, 1));
		radeon_ring_ग_लिखो(ring, ring->next_rptr_gpu_addr & 0xfffffffc);
		radeon_ring_ग_लिखो(ring, upper_32_bits(ring->next_rptr_gpu_addr) & 0xff);
		radeon_ring_ग_लिखो(ring, next_rptr);
	पूर्ण

	/* The indirect buffer packet must end on an 8 DW boundary in the DMA ring.
	 * Pad as necessary with NOPs.
	 */
	जबतक ((ring->wptr & 7) != 5)
		radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0));
	radeon_ring_ग_लिखो(ring, DMA_IB_PACKET(DMA_PACKET_INसूचीECT_BUFFER, vm_id, 0));
	radeon_ring_ग_लिखो(ring, (ib->gpu_addr & 0xFFFFFFE0));
	radeon_ring_ग_लिखो(ring, (ib->length_dw << 12) | (upper_32_bits(ib->gpu_addr) & 0xFF));

पूर्ण

/**
 * cayman_dma_stop - stop the async dma engines
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Stop the async dma engines (cayman-SI).
 */
व्योम cayman_dma_stop(काष्ठा radeon_device *rdev)
अणु
	u32 rb_cntl;

	अगर ((rdev->asic->copy.copy_ring_index == R600_RING_TYPE_DMA_INDEX) ||
	    (rdev->asic->copy.copy_ring_index == CAYMAN_RING_TYPE_DMA1_INDEX))
		radeon_tपंचांग_set_active_vram_size(rdev, rdev->mc.visible_vram_size);

	/* dma0 */
	rb_cntl = RREG32(DMA_RB_CNTL + DMA0_REGISTER_OFFSET);
	rb_cntl &= ~DMA_RB_ENABLE;
	WREG32(DMA_RB_CNTL + DMA0_REGISTER_OFFSET, rb_cntl);

	/* dma1 */
	rb_cntl = RREG32(DMA_RB_CNTL + DMA1_REGISTER_OFFSET);
	rb_cntl &= ~DMA_RB_ENABLE;
	WREG32(DMA_RB_CNTL + DMA1_REGISTER_OFFSET, rb_cntl);

	rdev->ring[R600_RING_TYPE_DMA_INDEX].पढ़ोy = false;
	rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX].पढ़ोy = false;
पूर्ण

/**
 * cayman_dma_resume - setup and start the async dma engines
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Set up the DMA ring buffers and enable them. (cayman-SI).
 * Returns 0 क्रम success, error क्रम failure.
 */
पूर्णांक cayman_dma_resume(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
	u32 rb_cntl, dma_cntl, ib_cntl;
	u32 rb_bufsz;
	u32 reg_offset, wb_offset;
	पूर्णांक i, r;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (i == 0) अणु
			ring = &rdev->ring[R600_RING_TYPE_DMA_INDEX];
			reg_offset = DMA0_REGISTER_OFFSET;
			wb_offset = R600_WB_DMA_RPTR_OFFSET;
		पूर्ण अन्यथा अणु
			ring = &rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX];
			reg_offset = DMA1_REGISTER_OFFSET;
			wb_offset = CAYMAN_WB_DMA1_RPTR_OFFSET;
		पूर्ण

		WREG32(DMA_SEM_INCOMPLETE_TIMER_CNTL + reg_offset, 0);
		WREG32(DMA_SEM_WAIT_FAIL_TIMER_CNTL + reg_offset, 0);

		/* Set ring buffer size in dwords */
		rb_bufsz = order_base_2(ring->ring_size / 4);
		rb_cntl = rb_bufsz << 1;
#अगर_घोषित __BIG_ENDIAN
		rb_cntl |= DMA_RB_SWAP_ENABLE | DMA_RPTR_WRITEBACK_SWAP_ENABLE;
#पूर्ण_अगर
		WREG32(DMA_RB_CNTL + reg_offset, rb_cntl);

		/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
		WREG32(DMA_RB_RPTR + reg_offset, 0);
		WREG32(DMA_RB_WPTR + reg_offset, 0);

		/* set the wb address whether it's enabled or not */
		WREG32(DMA_RB_RPTR_ADDR_HI + reg_offset,
		       upper_32_bits(rdev->wb.gpu_addr + wb_offset) & 0xFF);
		WREG32(DMA_RB_RPTR_ADDR_LO + reg_offset,
		       ((rdev->wb.gpu_addr + wb_offset) & 0xFFFFFFFC));

		अगर (rdev->wb.enabled)
			rb_cntl |= DMA_RPTR_WRITEBACK_ENABLE;

		WREG32(DMA_RB_BASE + reg_offset, ring->gpu_addr >> 8);

		/* enable DMA IBs */
		ib_cntl = DMA_IB_ENABLE | CMD_VMID_FORCE;
#अगर_घोषित __BIG_ENDIAN
		ib_cntl |= DMA_IB_SWAP_ENABLE;
#पूर्ण_अगर
		WREG32(DMA_IB_CNTL + reg_offset, ib_cntl);

		dma_cntl = RREG32(DMA_CNTL + reg_offset);
		dma_cntl &= ~CTXEMPTY_INT_ENABLE;
		WREG32(DMA_CNTL + reg_offset, dma_cntl);

		ring->wptr = 0;
		WREG32(DMA_RB_WPTR + reg_offset, ring->wptr << 2);

		WREG32(DMA_RB_CNTL + reg_offset, rb_cntl | DMA_RB_ENABLE);

		ring->पढ़ोy = true;

		r = radeon_ring_test(rdev, ring->idx, ring);
		अगर (r) अणु
			ring->पढ़ोy = false;
			वापस r;
		पूर्ण
	पूर्ण

	अगर ((rdev->asic->copy.copy_ring_index == R600_RING_TYPE_DMA_INDEX) ||
	    (rdev->asic->copy.copy_ring_index == CAYMAN_RING_TYPE_DMA1_INDEX))
		radeon_tपंचांग_set_active_vram_size(rdev, rdev->mc.real_vram_size);

	वापस 0;
पूर्ण

/**
 * cayman_dma_fini - tear करोwn the async dma engines
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Stop the async dma engines and मुक्त the rings (cayman-SI).
 */
व्योम cayman_dma_fini(काष्ठा radeon_device *rdev)
अणु
	cayman_dma_stop(rdev);
	radeon_ring_fini(rdev, &rdev->ring[R600_RING_TYPE_DMA_INDEX]);
	radeon_ring_fini(rdev, &rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX]);
पूर्ण

/**
 * cayman_dma_is_lockup - Check अगर the DMA engine is locked up
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Check अगर the async DMA engine is locked up.
 * Returns true अगर the engine appears to be locked up, false अगर not.
 */
bool cayman_dma_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	u32 reset_mask = cayman_gpu_check_soft_reset(rdev);
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
 * cayman_dma_vm_copy_pages - update PTEs by copying them from the GART
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @src: src addr where to copy from
 * @count: number of page entries to update
 *
 * Update PTEs by copying them from the GART using the DMA (cayman/TN).
 */
व्योम cayman_dma_vm_copy_pages(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_ib *ib,
			      uपूर्णांक64_t pe, uपूर्णांक64_t src,
			      अचिन्हित count)
अणु
	अचिन्हित ndw;

	जबतक (count) अणु
		ndw = count * 2;
		अगर (ndw > 0xFFFFE)
			ndw = 0xFFFFE;

		ib->ptr[ib->length_dw++] = DMA_PACKET(DMA_PACKET_COPY,
						      0, 0, ndw);
		ib->ptr[ib->length_dw++] = lower_32_bits(pe);
		ib->ptr[ib->length_dw++] = lower_32_bits(src);
		ib->ptr[ib->length_dw++] = upper_32_bits(pe) & 0xff;
		ib->ptr[ib->length_dw++] = upper_32_bits(src) & 0xff;

		pe += ndw * 4;
		src += ndw * 4;
		count -= ndw / 2;
	पूर्ण
पूर्ण

/**
 * cayman_dma_vm_ग_लिखो_pages - update PTEs by writing them manually
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @addr: dst addr to ग_लिखो पूर्णांकo pe
 * @count: number of page entries to update
 * @incr: increase next addr by incr bytes
 * @flags: hw access flags
 *
 * Update PTEs by writing them manually using the DMA (cayman/TN).
 */
व्योम cayman_dma_vm_ग_लिखो_pages(काष्ठा radeon_device *rdev,
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
		ib->ptr[ib->length_dw++] = DMA_PACKET(DMA_PACKET_WRITE,
						      0, 0, ndw);
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
 * cayman_dma_vm_set_pages - update the page tables using the DMA
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @addr: dst addr to ग_लिखो पूर्णांकo pe
 * @count: number of page entries to update
 * @incr: increase next addr by incr bytes
 * @flags: hw access flags
 *
 * Update the page tables using the DMA (cayman/TN).
 */
व्योम cayman_dma_vm_set_pages(काष्ठा radeon_device *rdev,
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

/**
 * cayman_dma_vm_pad_ib - pad the IB to the required number of dw
 *
 * @ib: indirect buffer to fill with padding
 *
 */
व्योम cayman_dma_vm_pad_ib(काष्ठा radeon_ib *ib)
अणु
	जबतक (ib->length_dw & 0x7)
		ib->ptr[ib->length_dw++] = DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0);
पूर्ण

व्योम cayman_dma_vm_flush(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
			 अचिन्हित vm_id, uपूर्णांक64_t pd_addr)
अणु
	radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_SRBM_WRITE, 0, 0, 0));
	radeon_ring_ग_लिखो(ring, (0xf << 16) | ((VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + (vm_id << 2)) >> 2));
	radeon_ring_ग_लिखो(ring, pd_addr >> 12);

	/* flush hdp cache */
	radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_SRBM_WRITE, 0, 0, 0));
	radeon_ring_ग_लिखो(ring, (0xf << 16) | (HDP_MEM_COHERENCY_FLUSH_CNTL >> 2));
	radeon_ring_ग_लिखो(ring, 1);

	/* bits 0-7 are the VM contexts0-7 */
	radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_SRBM_WRITE, 0, 0, 0));
	radeon_ring_ग_लिखो(ring, (0xf << 16) | (VM_INVALIDATE_REQUEST >> 2));
	radeon_ring_ग_लिखो(ring, 1 << vm_id);

	/* रुको क्रम invalidate to complete */
	radeon_ring_ग_लिखो(ring, DMA_SRBM_READ_PACKET);
	radeon_ring_ग_लिखो(ring, (0xff << 20) | (VM_INVALIDATE_REQUEST >> 2));
	radeon_ring_ग_लिखो(ring, 0); /* mask */
	radeon_ring_ग_लिखो(ring, 0); /* value */
पूर्ण

