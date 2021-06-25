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
#समावेश <linux/firmware.h>

#समावेश "radeon.h"
#समावेश "radeon_ucode.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_trace.h"
#समावेश "cik.h"
#समावेश "cikd.h"

/* sdma */
#घोषणा CIK_SDMA_UCODE_SIZE 1050
#घोषणा CIK_SDMA_UCODE_VERSION 64

/*
 * sDMA - System DMA
 * Starting with CIK, the GPU has new asynchronous
 * DMA engines.  These engines are used क्रम compute
 * and gfx.  There are two DMA engines (SDMA0, SDMA1)
 * and each one supports 1 ring buffer used क्रम gfx
 * and 2 queues used क्रम compute.
 *
 * The programming model is very similar to the CP
 * (ring buffer, IBs, etc.), but sDMA has it's own
 * packet क्रमmat that is dअगरferent from the PM4 क्रमmat
 * used by the CP. sDMA supports copying data, writing
 * embedded data, solid fills, and a number of other
 * things.  It also has support क्रम tiling/detiling of
 * buffers.
 */

/**
 * cik_sdma_get_rptr - get the current पढ़ो poपूर्णांकer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon ring poपूर्णांकer
 *
 * Get the current rptr from the hardware (CIK+).
 */
uपूर्णांक32_t cik_sdma_get_rptr(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ring *ring)
अणु
	u32 rptr, reg;

	अगर (rdev->wb.enabled) अणु
		rptr = rdev->wb.wb[ring->rptr_offs/4];
	पूर्ण अन्यथा अणु
		अगर (ring->idx == R600_RING_TYPE_DMA_INDEX)
			reg = SDMA0_GFX_RB_RPTR + SDMA0_REGISTER_OFFSET;
		अन्यथा
			reg = SDMA0_GFX_RB_RPTR + SDMA1_REGISTER_OFFSET;

		rptr = RREG32(reg);
	पूर्ण

	वापस (rptr & 0x3fffc) >> 2;
पूर्ण

/**
 * cik_sdma_get_wptr - get the current ग_लिखो poपूर्णांकer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon ring poपूर्णांकer
 *
 * Get the current wptr from the hardware (CIK+).
 */
uपूर्णांक32_t cik_sdma_get_wptr(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ring *ring)
अणु
	u32 reg;

	अगर (ring->idx == R600_RING_TYPE_DMA_INDEX)
		reg = SDMA0_GFX_RB_WPTR + SDMA0_REGISTER_OFFSET;
	अन्यथा
		reg = SDMA0_GFX_RB_WPTR + SDMA1_REGISTER_OFFSET;

	वापस (RREG32(reg) & 0x3fffc) >> 2;
पूर्ण

/**
 * cik_sdma_set_wptr - commit the ग_लिखो poपूर्णांकer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon ring poपूर्णांकer
 *
 * Write the wptr back to the hardware (CIK+).
 */
व्योम cik_sdma_set_wptr(काष्ठा radeon_device *rdev,
		       काष्ठा radeon_ring *ring)
अणु
	u32 reg;

	अगर (ring->idx == R600_RING_TYPE_DMA_INDEX)
		reg = SDMA0_GFX_RB_WPTR + SDMA0_REGISTER_OFFSET;
	अन्यथा
		reg = SDMA0_GFX_RB_WPTR + SDMA1_REGISTER_OFFSET;

	WREG32(reg, (ring->wptr << 2) & 0x3fffc);
	(व्योम)RREG32(reg);
पूर्ण

/**
 * cik_sdma_ring_ib_execute - Schedule an IB on the DMA engine
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: IB object to schedule
 *
 * Schedule an IB in the DMA ring (CIK).
 */
व्योम cik_sdma_ring_ib_execute(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_ib *ib)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[ib->ring];
	u32 extra_bits = (ib->vm ? ib->vm->ids[ib->ring].id : 0) & 0xf;

	अगर (rdev->wb.enabled) अणु
		u32 next_rptr = ring->wptr + 5;
		जबतक ((next_rptr & 7) != 4)
			next_rptr++;
		next_rptr += 4;
		radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_WRITE, SDMA_WRITE_SUB_OPCODE_LINEAR, 0));
		radeon_ring_ग_लिखो(ring, ring->next_rptr_gpu_addr & 0xfffffffc);
		radeon_ring_ग_लिखो(ring, upper_32_bits(ring->next_rptr_gpu_addr));
		radeon_ring_ग_लिखो(ring, 1); /* number of DWs to follow */
		radeon_ring_ग_लिखो(ring, next_rptr);
	पूर्ण

	/* IB packet must end on a 8 DW boundary */
	जबतक ((ring->wptr & 7) != 4)
		radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_NOP, 0, 0));
	radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_INसूचीECT_BUFFER, 0, extra_bits));
	radeon_ring_ग_लिखो(ring, ib->gpu_addr & 0xffffffe0); /* base must be 32 byte aligned */
	radeon_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr));
	radeon_ring_ग_लिखो(ring, ib->length_dw);

पूर्ण

/**
 * cik_sdma_hdp_flush_ring_emit - emit an hdp flush on the DMA ring
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ridx: radeon ring index
 *
 * Emit an hdp flush packet on the requested DMA ring.
 */
अटल व्योम cik_sdma_hdp_flush_ring_emit(काष्ठा radeon_device *rdev,
					 पूर्णांक ridx)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[ridx];
	u32 extra_bits = (SDMA_POLL_REG_MEM_EXTRA_OP(1) |
			  SDMA_POLL_REG_MEM_EXTRA_FUNC(3)); /* == */
	u32 ref_and_mask;

	अगर (ridx == R600_RING_TYPE_DMA_INDEX)
		ref_and_mask = SDMA0;
	अन्यथा
		ref_and_mask = SDMA1;

	radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_POLL_REG_MEM, 0, extra_bits));
	radeon_ring_ग_लिखो(ring, GPU_HDP_FLUSH_DONE);
	radeon_ring_ग_लिखो(ring, GPU_HDP_FLUSH_REQ);
	radeon_ring_ग_लिखो(ring, ref_and_mask); /* reference */
	radeon_ring_ग_लिखो(ring, ref_and_mask); /* mask */
	radeon_ring_ग_लिखो(ring, (0xfff << 16) | 10); /* retry count, poll पूर्णांकerval */
पूर्ण

/**
 * cik_sdma_fence_ring_emit - emit a fence on the DMA ring
 *
 * @rdev: radeon_device poपूर्णांकer
 * @fence: radeon fence object
 *
 * Add a DMA fence packet to the ring to ग_लिखो
 * the fence seq number and DMA trap packet to generate
 * an पूर्णांकerrupt अगर needed (CIK).
 */
व्योम cik_sdma_fence_ring_emit(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_fence *fence)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[fence->ring];
	u64 addr = rdev->fence_drv[fence->ring].gpu_addr;

	/* ग_लिखो the fence */
	radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_FENCE, 0, 0));
	radeon_ring_ग_लिखो(ring, lower_32_bits(addr));
	radeon_ring_ग_लिखो(ring, upper_32_bits(addr));
	radeon_ring_ग_लिखो(ring, fence->seq);
	/* generate an पूर्णांकerrupt */
	radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_TRAP, 0, 0));
	/* flush HDP */
	cik_sdma_hdp_flush_ring_emit(rdev, fence->ring);
पूर्ण

/**
 * cik_sdma_semaphore_ring_emit - emit a semaphore on the dma ring
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 * @semaphore: radeon semaphore object
 * @emit_रुको: रुको or संकेत semaphore
 *
 * Add a DMA semaphore packet to the ring रुको on or संकेत
 * other rings (CIK).
 */
bool cik_sdma_semaphore_ring_emit(काष्ठा radeon_device *rdev,
				  काष्ठा radeon_ring *ring,
				  काष्ठा radeon_semaphore *semaphore,
				  bool emit_रुको)
अणु
	u64 addr = semaphore->gpu_addr;
	u32 extra_bits = emit_रुको ? 0 : SDMA_SEMAPHORE_EXTRA_S;

	radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_SEMAPHORE, 0, extra_bits));
	radeon_ring_ग_लिखो(ring, addr & 0xfffffff8);
	radeon_ring_ग_लिखो(ring, upper_32_bits(addr));

	वापस true;
पूर्ण

/**
 * cik_sdma_gfx_stop - stop the gfx async dma engines
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Stop the gfx async dma ring buffers (CIK).
 */
अटल व्योम cik_sdma_gfx_stop(काष्ठा radeon_device *rdev)
अणु
	u32 rb_cntl, reg_offset;
	पूर्णांक i;

	अगर ((rdev->asic->copy.copy_ring_index == R600_RING_TYPE_DMA_INDEX) ||
	    (rdev->asic->copy.copy_ring_index == CAYMAN_RING_TYPE_DMA1_INDEX))
		radeon_tपंचांग_set_active_vram_size(rdev, rdev->mc.visible_vram_size);

	क्रम (i = 0; i < 2; i++) अणु
		अगर (i == 0)
			reg_offset = SDMA0_REGISTER_OFFSET;
		अन्यथा
			reg_offset = SDMA1_REGISTER_OFFSET;
		rb_cntl = RREG32(SDMA0_GFX_RB_CNTL + reg_offset);
		rb_cntl &= ~SDMA_RB_ENABLE;
		WREG32(SDMA0_GFX_RB_CNTL + reg_offset, rb_cntl);
		WREG32(SDMA0_GFX_IB_CNTL + reg_offset, 0);
	पूर्ण
	rdev->ring[R600_RING_TYPE_DMA_INDEX].पढ़ोy = false;
	rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX].पढ़ोy = false;

	/* FIXME use something अन्यथा than big hammer but after few days can not
	 * seem to find good combination so reset SDMA blocks as it seems we
	 * करो not shut them करोwn properly. This fix hibernation and करोes not
	 * affect suspend to ram.
	 */
	WREG32(SRBM_SOFT_RESET, SOFT_RESET_SDMA | SOFT_RESET_SDMA1);
	(व्योम)RREG32(SRBM_SOFT_RESET);
	udelay(50);
	WREG32(SRBM_SOFT_RESET, 0);
	(व्योम)RREG32(SRBM_SOFT_RESET);
पूर्ण

/**
 * cik_sdma_rlc_stop - stop the compute async dma engines
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Stop the compute async dma queues (CIK).
 */
अटल व्योम cik_sdma_rlc_stop(काष्ठा radeon_device *rdev)
अणु
	/* XXX toकरो */
पूर्ण

/**
 * cik_sdma_ctx_चयन_enable - enable/disable sdma engine preemption
 *
 * @rdev: radeon_device poपूर्णांकer
 * @enable: enable/disable preemption.
 *
 * Halt or unhalt the async dma engines (CIK).
 */
अटल व्योम cik_sdma_ctx_चयन_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	uपूर्णांक32_t reg_offset, value;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (i == 0)
			reg_offset = SDMA0_REGISTER_OFFSET;
		अन्यथा
			reg_offset = SDMA1_REGISTER_OFFSET;
		value = RREG32(SDMA0_CNTL + reg_offset);
		अगर (enable)
			value |= AUTO_CTXSW_ENABLE;
		अन्यथा
			value &= ~AUTO_CTXSW_ENABLE;
		WREG32(SDMA0_CNTL + reg_offset, value);
	पूर्ण
पूर्ण

/**
 * cik_sdma_enable - stop the async dma engines
 *
 * @rdev: radeon_device poपूर्णांकer
 * @enable: enable/disable the DMA MEs.
 *
 * Halt or unhalt the async dma engines (CIK).
 */
व्योम cik_sdma_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	u32 me_cntl, reg_offset;
	पूर्णांक i;

	अगर (!enable) अणु
		cik_sdma_gfx_stop(rdev);
		cik_sdma_rlc_stop(rdev);
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		अगर (i == 0)
			reg_offset = SDMA0_REGISTER_OFFSET;
		अन्यथा
			reg_offset = SDMA1_REGISTER_OFFSET;
		me_cntl = RREG32(SDMA0_ME_CNTL + reg_offset);
		अगर (enable)
			me_cntl &= ~SDMA_HALT;
		अन्यथा
			me_cntl |= SDMA_HALT;
		WREG32(SDMA0_ME_CNTL + reg_offset, me_cntl);
	पूर्ण

	cik_sdma_ctx_चयन_enable(rdev, enable);
पूर्ण

/**
 * cik_sdma_gfx_resume - setup and start the async dma engines
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Set up the gfx DMA ring buffers and enable them (CIK).
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक cik_sdma_gfx_resume(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring;
	u32 rb_cntl, ib_cntl;
	u32 rb_bufsz;
	u32 reg_offset, wb_offset;
	पूर्णांक i, r;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (i == 0) अणु
			ring = &rdev->ring[R600_RING_TYPE_DMA_INDEX];
			reg_offset = SDMA0_REGISTER_OFFSET;
			wb_offset = R600_WB_DMA_RPTR_OFFSET;
		पूर्ण अन्यथा अणु
			ring = &rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX];
			reg_offset = SDMA1_REGISTER_OFFSET;
			wb_offset = CAYMAN_WB_DMA1_RPTR_OFFSET;
		पूर्ण

		WREG32(SDMA0_SEM_INCOMPLETE_TIMER_CNTL + reg_offset, 0);
		WREG32(SDMA0_SEM_WAIT_FAIL_TIMER_CNTL + reg_offset, 0);

		/* Set ring buffer size in dwords */
		rb_bufsz = order_base_2(ring->ring_size / 4);
		rb_cntl = rb_bufsz << 1;
#अगर_घोषित __BIG_ENDIAN
		rb_cntl |= SDMA_RB_SWAP_ENABLE | SDMA_RPTR_WRITEBACK_SWAP_ENABLE;
#पूर्ण_अगर
		WREG32(SDMA0_GFX_RB_CNTL + reg_offset, rb_cntl);

		/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
		WREG32(SDMA0_GFX_RB_RPTR + reg_offset, 0);
		WREG32(SDMA0_GFX_RB_WPTR + reg_offset, 0);

		/* set the wb address whether it's enabled or not */
		WREG32(SDMA0_GFX_RB_RPTR_ADDR_HI + reg_offset,
		       upper_32_bits(rdev->wb.gpu_addr + wb_offset) & 0xFFFFFFFF);
		WREG32(SDMA0_GFX_RB_RPTR_ADDR_LO + reg_offset,
		       ((rdev->wb.gpu_addr + wb_offset) & 0xFFFFFFFC));

		अगर (rdev->wb.enabled)
			rb_cntl |= SDMA_RPTR_WRITEBACK_ENABLE;

		WREG32(SDMA0_GFX_RB_BASE + reg_offset, ring->gpu_addr >> 8);
		WREG32(SDMA0_GFX_RB_BASE_HI + reg_offset, ring->gpu_addr >> 40);

		ring->wptr = 0;
		WREG32(SDMA0_GFX_RB_WPTR + reg_offset, ring->wptr << 2);

		/* enable DMA RB */
		WREG32(SDMA0_GFX_RB_CNTL + reg_offset, rb_cntl | SDMA_RB_ENABLE);

		ib_cntl = SDMA_IB_ENABLE;
#अगर_घोषित __BIG_ENDIAN
		ib_cntl |= SDMA_IB_SWAP_ENABLE;
#पूर्ण_अगर
		/* enable DMA IBs */
		WREG32(SDMA0_GFX_IB_CNTL + reg_offset, ib_cntl);

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
 * cik_sdma_rlc_resume - setup and start the async dma engines
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Set up the compute DMA queues and enable them (CIK).
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक cik_sdma_rlc_resume(काष्ठा radeon_device *rdev)
अणु
	/* XXX toकरो */
	वापस 0;
पूर्ण

/**
 * cik_sdma_load_microcode - load the sDMA ME ucode
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Loads the sDMA0/1 ucode.
 * Returns 0 क्रम success, -EINVAL अगर the ucode is not available.
 */
अटल पूर्णांक cik_sdma_load_microcode(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	अगर (!rdev->sdma_fw)
		वापस -EINVAL;

	/* halt the MEs */
	cik_sdma_enable(rdev, false);

	अगर (rdev->new_fw) अणु
		स्थिर काष्ठा sdma_firmware_header_v1_0 *hdr =
			(स्थिर काष्ठा sdma_firmware_header_v1_0 *)rdev->sdma_fw->data;
		स्थिर __le32 *fw_data;
		u32 fw_size;

		radeon_ucode_prपूर्णांक_sdma_hdr(&hdr->header);

		/* sdma0 */
		fw_data = (स्थिर __le32 *)
			(rdev->sdma_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
		fw_size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;
		WREG32(SDMA0_UCODE_ADDR + SDMA0_REGISTER_OFFSET, 0);
		क्रम (i = 0; i < fw_size; i++)
			WREG32(SDMA0_UCODE_DATA + SDMA0_REGISTER_OFFSET, le32_to_cpup(fw_data++));
		WREG32(SDMA0_UCODE_DATA + SDMA0_REGISTER_OFFSET, CIK_SDMA_UCODE_VERSION);

		/* sdma1 */
		fw_data = (स्थिर __le32 *)
			(rdev->sdma_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
		fw_size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;
		WREG32(SDMA0_UCODE_ADDR + SDMA1_REGISTER_OFFSET, 0);
		क्रम (i = 0; i < fw_size; i++)
			WREG32(SDMA0_UCODE_DATA + SDMA1_REGISTER_OFFSET, le32_to_cpup(fw_data++));
		WREG32(SDMA0_UCODE_DATA + SDMA1_REGISTER_OFFSET, CIK_SDMA_UCODE_VERSION);
	पूर्ण अन्यथा अणु
		स्थिर __be32 *fw_data;

		/* sdma0 */
		fw_data = (स्थिर __be32 *)rdev->sdma_fw->data;
		WREG32(SDMA0_UCODE_ADDR + SDMA0_REGISTER_OFFSET, 0);
		क्रम (i = 0; i < CIK_SDMA_UCODE_SIZE; i++)
			WREG32(SDMA0_UCODE_DATA + SDMA0_REGISTER_OFFSET, be32_to_cpup(fw_data++));
		WREG32(SDMA0_UCODE_DATA + SDMA0_REGISTER_OFFSET, CIK_SDMA_UCODE_VERSION);

		/* sdma1 */
		fw_data = (स्थिर __be32 *)rdev->sdma_fw->data;
		WREG32(SDMA0_UCODE_ADDR + SDMA1_REGISTER_OFFSET, 0);
		क्रम (i = 0; i < CIK_SDMA_UCODE_SIZE; i++)
			WREG32(SDMA0_UCODE_DATA + SDMA1_REGISTER_OFFSET, be32_to_cpup(fw_data++));
		WREG32(SDMA0_UCODE_DATA + SDMA1_REGISTER_OFFSET, CIK_SDMA_UCODE_VERSION);
	पूर्ण

	WREG32(SDMA0_UCODE_ADDR + SDMA0_REGISTER_OFFSET, 0);
	WREG32(SDMA0_UCODE_ADDR + SDMA1_REGISTER_OFFSET, 0);
	वापस 0;
पूर्ण

/**
 * cik_sdma_resume - setup and start the async dma engines
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Set up the DMA engines and enable them (CIK).
 * Returns 0 क्रम success, error क्रम failure.
 */
पूर्णांक cik_sdma_resume(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	r = cik_sdma_load_microcode(rdev);
	अगर (r)
		वापस r;

	/* unhalt the MEs */
	cik_sdma_enable(rdev, true);

	/* start the gfx rings and rlc compute queues */
	r = cik_sdma_gfx_resume(rdev);
	अगर (r)
		वापस r;
	r = cik_sdma_rlc_resume(rdev);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

/**
 * cik_sdma_fini - tear करोwn the async dma engines
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Stop the async dma engines and मुक्त the rings (CIK).
 */
व्योम cik_sdma_fini(काष्ठा radeon_device *rdev)
अणु
	/* halt the MEs */
	cik_sdma_enable(rdev, false);
	radeon_ring_fini(rdev, &rdev->ring[R600_RING_TYPE_DMA_INDEX]);
	radeon_ring_fini(rdev, &rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX]);
	/* XXX - compute dma queue tear करोwn */
पूर्ण

/**
 * cik_copy_dma - copy pages using the DMA engine
 *
 * @rdev: radeon_device poपूर्णांकer
 * @src_offset: src GPU address
 * @dst_offset: dst GPU address
 * @num_gpu_pages: number of GPU pages to xfer
 * @resv: reservation object to sync to
 *
 * Copy GPU paging using the DMA engine (CIK).
 * Used by the radeon tपंचांग implementation to move pages अगर
 * रेजिस्टरed as the asic copy callback.
 */
काष्ठा radeon_fence *cik_copy_dma(काष्ठा radeon_device *rdev,
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
	num_loops = DIV_ROUND_UP(size_in_bytes, 0x1fffff);
	r = radeon_ring_lock(rdev, ring, num_loops * 7 + 14);
	अगर (r) अणु
		DRM_ERROR("radeon: moving bo (%d).\n", r);
		radeon_sync_मुक्त(rdev, &sync, शून्य);
		वापस ERR_PTR(r);
	पूर्ण

	radeon_sync_resv(rdev, &sync, resv, false);
	radeon_sync_rings(rdev, &sync, ring->idx);

	क्रम (i = 0; i < num_loops; i++) अणु
		cur_size_in_bytes = size_in_bytes;
		अगर (cur_size_in_bytes > 0x1fffff)
			cur_size_in_bytes = 0x1fffff;
		size_in_bytes -= cur_size_in_bytes;
		radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_COPY, SDMA_COPY_SUB_OPCODE_LINEAR, 0));
		radeon_ring_ग_लिखो(ring, cur_size_in_bytes);
		radeon_ring_ग_लिखो(ring, 0); /* src/dst endian swap */
		radeon_ring_ग_लिखो(ring, lower_32_bits(src_offset));
		radeon_ring_ग_लिखो(ring, upper_32_bits(src_offset));
		radeon_ring_ग_लिखो(ring, lower_32_bits(dst_offset));
		radeon_ring_ग_लिखो(ring, upper_32_bits(dst_offset));
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

/**
 * cik_sdma_ring_test - simple async dma engine test
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Test the DMA engine by writing using it to ग_लिखो an
 * value to memory. (CIK).
 * Returns 0 क्रम success, error क्रम failure.
 */
पूर्णांक cik_sdma_ring_test(काष्ठा radeon_device *rdev,
		       काष्ठा radeon_ring *ring)
अणु
	अचिन्हित i;
	पूर्णांक r;
	अचिन्हित index;
	u32 पंचांगp;
	u64 gpu_addr;

	अगर (ring->idx == R600_RING_TYPE_DMA_INDEX)
		index = R600_WB_DMA_RING_TEST_OFFSET;
	अन्यथा
		index = CAYMAN_WB_DMA1_RING_TEST_OFFSET;

	gpu_addr = rdev->wb.gpu_addr + index;

	पंचांगp = 0xCAFEDEAD;
	rdev->wb.wb[index/4] = cpu_to_le32(पंचांगp);

	r = radeon_ring_lock(rdev, ring, 5);
	अगर (r) अणु
		DRM_ERROR("radeon: dma failed to lock ring %d (%d).\n", ring->idx, r);
		वापस r;
	पूर्ण
	radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_WRITE, SDMA_WRITE_SUB_OPCODE_LINEAR, 0));
	radeon_ring_ग_लिखो(ring, lower_32_bits(gpu_addr));
	radeon_ring_ग_लिखो(ring, upper_32_bits(gpu_addr));
	radeon_ring_ग_लिखो(ring, 1); /* number of DWs to follow */
	radeon_ring_ग_लिखो(ring, 0xDEADBEEF);
	radeon_ring_unlock_commit(rdev, ring, false);

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		पंचांगp = le32_to_cpu(rdev->wb.wb[index/4]);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i < rdev->usec_समयout) अणु
		DRM_INFO("ring test on %d succeeded in %d usecs\n", ring->idx, i);
	पूर्ण अन्यथा अणु
		DRM_ERROR("radeon: ring %d test failed (0x%08X)\n",
			  ring->idx, पंचांगp);
		r = -EINVAL;
	पूर्ण
	वापस r;
पूर्ण

/**
 * cik_sdma_ib_test - test an IB on the DMA engine
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Test a simple IB in the DMA ring (CIK).
 * Returns 0 on success, error on failure.
 */
पूर्णांक cik_sdma_ib_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	काष्ठा radeon_ib ib;
	अचिन्हित i;
	अचिन्हित index;
	पूर्णांक r;
	u32 पंचांगp = 0;
	u64 gpu_addr;

	अगर (ring->idx == R600_RING_TYPE_DMA_INDEX)
		index = R600_WB_DMA_RING_TEST_OFFSET;
	अन्यथा
		index = CAYMAN_WB_DMA1_RING_TEST_OFFSET;

	gpu_addr = rdev->wb.gpu_addr + index;

	पंचांगp = 0xCAFEDEAD;
	rdev->wb.wb[index/4] = cpu_to_le32(पंचांगp);

	r = radeon_ib_get(rdev, ring->idx, &ib, शून्य, 256);
	अगर (r) अणु
		DRM_ERROR("radeon: failed to get ib (%d).\n", r);
		वापस r;
	पूर्ण

	ib.ptr[0] = SDMA_PACKET(SDMA_OPCODE_WRITE, SDMA_WRITE_SUB_OPCODE_LINEAR, 0);
	ib.ptr[1] = lower_32_bits(gpu_addr);
	ib.ptr[2] = upper_32_bits(gpu_addr);
	ib.ptr[3] = 1;
	ib.ptr[4] = 0xDEADBEEF;
	ib.length_dw = 5;

	r = radeon_ib_schedule(rdev, &ib, शून्य, false);
	अगर (r) अणु
		radeon_ib_मुक्त(rdev, &ib);
		DRM_ERROR("radeon: failed to schedule ib (%d).\n", r);
		वापस r;
	पूर्ण
	r = radeon_fence_रुको_समयout(ib.fence, false, usecs_to_jअगरfies(
		RADEON_USEC_IB_TEST_TIMEOUT));
	अगर (r < 0) अणु
		DRM_ERROR("radeon: fence wait failed (%d).\n", r);
		वापस r;
	पूर्ण अन्यथा अगर (r == 0) अणु
		DRM_ERROR("radeon: fence wait timed out.\n");
		वापस -ETIMEDOUT;
	पूर्ण
	r = 0;
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		पंचांगp = le32_to_cpu(rdev->wb.wb[index/4]);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (i < rdev->usec_समयout) अणु
		DRM_INFO("ib test on ring %d succeeded in %u usecs\n", ib.fence->ring, i);
	पूर्ण अन्यथा अणु
		DRM_ERROR("radeon: ib test failed (0x%08X)\n", पंचांगp);
		r = -EINVAL;
	पूर्ण
	radeon_ib_मुक्त(rdev, &ib);
	वापस r;
पूर्ण

/**
 * cik_sdma_is_lockup - Check अगर the DMA engine is locked up
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Check अगर the async DMA engine is locked up (CIK).
 * Returns true अगर the engine appears to be locked up, false अगर not.
 */
bool cik_sdma_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	u32 reset_mask = cik_gpu_check_soft_reset(rdev);
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
 * cik_sdma_vm_copy_pages - update PTEs by copying them from the GART
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @src: src addr to copy from
 * @count: number of page entries to update
 *
 * Update PTEs by copying them from the GART using sDMA (CIK).
 */
व्योम cik_sdma_vm_copy_pages(काष्ठा radeon_device *rdev,
			    काष्ठा radeon_ib *ib,
			    uपूर्णांक64_t pe, uपूर्णांक64_t src,
			    अचिन्हित count)
अणु
	जबतक (count) अणु
		अचिन्हित bytes = count * 8;
		अगर (bytes > 0x1FFFF8)
			bytes = 0x1FFFF8;

		ib->ptr[ib->length_dw++] = SDMA_PACKET(SDMA_OPCODE_COPY,
			SDMA_WRITE_SUB_OPCODE_LINEAR, 0);
		ib->ptr[ib->length_dw++] = bytes;
		ib->ptr[ib->length_dw++] = 0; /* src/dst endian swap */
		ib->ptr[ib->length_dw++] = lower_32_bits(src);
		ib->ptr[ib->length_dw++] = upper_32_bits(src);
		ib->ptr[ib->length_dw++] = lower_32_bits(pe);
		ib->ptr[ib->length_dw++] = upper_32_bits(pe);

		pe += bytes;
		src += bytes;
		count -= bytes / 8;
	पूर्ण
पूर्ण

/**
 * cik_sdma_vm_ग_लिखो_pages - update PTEs by writing them manually
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @addr: dst addr to ग_लिखो पूर्णांकo pe
 * @count: number of page entries to update
 * @incr: increase next addr by incr bytes
 * @flags: access flags
 *
 * Update PTEs by writing them manually using sDMA (CIK).
 */
व्योम cik_sdma_vm_ग_लिखो_pages(काष्ठा radeon_device *rdev,
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
		ib->ptr[ib->length_dw++] = SDMA_PACKET(SDMA_OPCODE_WRITE,
			SDMA_WRITE_SUB_OPCODE_LINEAR, 0);
		ib->ptr[ib->length_dw++] = pe;
		ib->ptr[ib->length_dw++] = upper_32_bits(pe);
		ib->ptr[ib->length_dw++] = ndw;
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
 * cik_sdma_vm_set_pages - update the page tables using sDMA
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @addr: dst addr to ग_लिखो पूर्णांकo pe
 * @count: number of page entries to update
 * @incr: increase next addr by incr bytes
 * @flags: access flags
 *
 * Update the page tables using sDMA (CIK).
 */
व्योम cik_sdma_vm_set_pages(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ib *ib,
			   uपूर्णांक64_t pe,
			   uपूर्णांक64_t addr, अचिन्हित count,
			   uपूर्णांक32_t incr, uपूर्णांक32_t flags)
अणु
	uपूर्णांक64_t value;
	अचिन्हित ndw;

	जबतक (count) अणु
		ndw = count;
		अगर (ndw > 0x7FFFF)
			ndw = 0x7FFFF;

		अगर (flags & R600_PTE_VALID)
			value = addr;
		अन्यथा
			value = 0;

		/* क्रम physically contiguous pages (vram) */
		ib->ptr[ib->length_dw++] = SDMA_PACKET(SDMA_OPCODE_GENERATE_PTE_PDE, 0, 0);
		ib->ptr[ib->length_dw++] = pe; /* dst addr */
		ib->ptr[ib->length_dw++] = upper_32_bits(pe);
		ib->ptr[ib->length_dw++] = flags; /* mask */
		ib->ptr[ib->length_dw++] = 0;
		ib->ptr[ib->length_dw++] = value; /* value */
		ib->ptr[ib->length_dw++] = upper_32_bits(value);
		ib->ptr[ib->length_dw++] = incr; /* increment size */
		ib->ptr[ib->length_dw++] = 0;
		ib->ptr[ib->length_dw++] = ndw; /* number of entries */

		pe += ndw * 8;
		addr += ndw * incr;
		count -= ndw;
	पूर्ण
पूर्ण

/**
 * cik_sdma_vm_pad_ib - pad the IB to the required number of dw
 *
 * @ib: indirect buffer to fill with padding
 *
 */
व्योम cik_sdma_vm_pad_ib(काष्ठा radeon_ib *ib)
अणु
	जबतक (ib->length_dw & 0x7)
		ib->ptr[ib->length_dw++] = SDMA_PACKET(SDMA_OPCODE_NOP, 0, 0);
पूर्ण

/*
 * cik_dma_vm_flush - cik vm flush using sDMA
 *
 * Update the page table base and flush the VM TLB
 * using sDMA (CIK).
 */
व्योम cik_dma_vm_flush(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
		      अचिन्हित vm_id, uपूर्णांक64_t pd_addr)
अणु
	u32 extra_bits = (SDMA_POLL_REG_MEM_EXTRA_OP(0) |
			  SDMA_POLL_REG_MEM_EXTRA_FUNC(0)); /* always */

	radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_SRBM_WRITE, 0, 0xf000));
	अगर (vm_id < 8) अणु
		radeon_ring_ग_लिखो(ring, (VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + (vm_id << 2)) >> 2);
	पूर्ण अन्यथा अणु
		radeon_ring_ग_लिखो(ring, (VM_CONTEXT8_PAGE_TABLE_BASE_ADDR + ((vm_id - 8) << 2)) >> 2);
	पूर्ण
	radeon_ring_ग_लिखो(ring, pd_addr >> 12);

	/* update SH_MEM_* regs */
	radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_SRBM_WRITE, 0, 0xf000));
	radeon_ring_ग_लिखो(ring, SRBM_GFX_CNTL >> 2);
	radeon_ring_ग_लिखो(ring, VMID(vm_id));

	radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_SRBM_WRITE, 0, 0xf000));
	radeon_ring_ग_लिखो(ring, SH_MEM_BASES >> 2);
	radeon_ring_ग_लिखो(ring, 0);

	radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_SRBM_WRITE, 0, 0xf000));
	radeon_ring_ग_लिखो(ring, SH_MEM_CONFIG >> 2);
	radeon_ring_ग_लिखो(ring, 0);

	radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_SRBM_WRITE, 0, 0xf000));
	radeon_ring_ग_लिखो(ring, SH_MEM_APE1_BASE >> 2);
	radeon_ring_ग_लिखो(ring, 1);

	radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_SRBM_WRITE, 0, 0xf000));
	radeon_ring_ग_लिखो(ring, SH_MEM_APE1_LIMIT >> 2);
	radeon_ring_ग_लिखो(ring, 0);

	radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_SRBM_WRITE, 0, 0xf000));
	radeon_ring_ग_लिखो(ring, SRBM_GFX_CNTL >> 2);
	radeon_ring_ग_लिखो(ring, VMID(0));

	/* flush HDP */
	cik_sdma_hdp_flush_ring_emit(rdev, ring->idx);

	/* flush TLB */
	radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_SRBM_WRITE, 0, 0xf000));
	radeon_ring_ग_लिखो(ring, VM_INVALIDATE_REQUEST >> 2);
	radeon_ring_ग_लिखो(ring, 1 << vm_id);

	radeon_ring_ग_लिखो(ring, SDMA_PACKET(SDMA_OPCODE_POLL_REG_MEM, 0, extra_bits));
	radeon_ring_ग_लिखो(ring, VM_INVALIDATE_REQUEST >> 2);
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, 0); /* reference */
	radeon_ring_ग_लिखो(ring, 0); /* mask */
	radeon_ring_ग_लिखो(ring, (0xfff << 16) | 10); /* retry count, poll पूर्णांकerval */
पूर्ण

