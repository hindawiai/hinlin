<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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
 * Authors: Sonny Jiang <sonny.jiang@amd.com>
 */

#समावेश <linux/firmware.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_uvd.h"
#समावेश "sid.h"

#समावेश "uvd/uvd_3_1_d.h"
#समावेश "uvd/uvd_3_1_sh_mask.h"

#समावेश "oss/oss_1_0_d.h"
#समावेश "oss/oss_1_0_sh_mask.h"

/**
 * uvd_v3_1_ring_get_rptr - get पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t uvd_v3_1_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32(mmUVD_RBC_RB_RPTR);
पूर्ण

/**
 * uvd_v3_1_ring_get_wptr - get ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t uvd_v3_1_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32(mmUVD_RBC_RB_WPTR);
पूर्ण

/**
 * uvd_v3_1_ring_set_wptr - set ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम uvd_v3_1_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	WREG32(mmUVD_RBC_RB_WPTR, lower_32_bits(ring->wptr));
पूर्ण

/**
 * uvd_v3_1_ring_emit_ib - execute indirect buffer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @job: iob associated with the indirect buffer
 * @ib: indirect buffer to execute
 * @flags: flags associated with the indirect buffer
 *
 * Write ring commands to execute the indirect buffer
 */
अटल व्योम uvd_v3_1_ring_emit_ib(काष्ठा amdgpu_ring *ring,
				  काष्ठा amdgpu_job *job,
				  काष्ठा amdgpu_ib *ib,
				  uपूर्णांक32_t flags)
अणु
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_RBC_IB_BASE, 0));
	amdgpu_ring_ग_लिखो(ring, ib->gpu_addr);
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_RBC_IB_SIZE, 0));
	amdgpu_ring_ग_लिखो(ring, ib->length_dw);
पूर्ण

/**
 * uvd_v3_1_ring_emit_fence - emit an fence & trap command
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @addr: address
 * @seq: sequence number
 * @flags: fence related flags
 *
 * Write a fence and a trap command to the ring.
 */
अटल व्योम uvd_v3_1_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr, u64 seq,
				 अचिन्हित flags)
अणु
	WARN_ON(flags & AMDGPU_FENCE_FLAG_64BIT);

	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_CONTEXT_ID, 0));
	amdgpu_ring_ग_लिखो(ring, seq);
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA0, 0));
	amdgpu_ring_ग_लिखो(ring, addr & 0xffffffff);
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA1, 0));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr) & 0xff);
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_CMD, 0));
	amdgpu_ring_ग_लिखो(ring, 0);

	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA0, 0));
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA1, 0));
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_CMD, 0));
	amdgpu_ring_ग_लिखो(ring, 2);
पूर्ण

/**
 * uvd_v3_1_ring_test_ring - रेजिस्टर ग_लिखो test
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Test अगर we can successfully ग_लिखो to the context रेजिस्टर
 */
अटल पूर्णांक uvd_v3_1_ring_test_ring(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t पंचांगp = 0;
	अचिन्हित i;
	पूर्णांक r;

	WREG32(mmUVD_CONTEXT_ID, 0xCAFEDEAD);
	r = amdgpu_ring_alloc(ring, 3);
	अगर (r)
		वापस r;

	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_CONTEXT_ID, 0));
	amdgpu_ring_ग_लिखो(ring, 0xDEADBEEF);
	amdgpu_ring_commit(ring);
	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		पंचांगp = RREG32(mmUVD_CONTEXT_ID);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i >= adev->usec_समयout)
		r = -ETIMEDOUT;

	वापस r;
पूर्ण

अटल व्योम uvd_v3_1_ring_insert_nop(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t count)
अणु
	पूर्णांक i;

	WARN_ON(ring->wptr % 2 || count % 2);

	क्रम (i = 0; i < count / 2; i++) अणु
		amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_NO_OP, 0));
		amdgpu_ring_ग_लिखो(ring, 0);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा amdgpu_ring_funcs uvd_v3_1_ring_funcs = अणु
	.type = AMDGPU_RING_TYPE_UVD,
	.align_mask = 0xf,
	.support_64bit_ptrs = false,
	.no_user_fence = true,
	.get_rptr = uvd_v3_1_ring_get_rptr,
	.get_wptr = uvd_v3_1_ring_get_wptr,
	.set_wptr = uvd_v3_1_ring_set_wptr,
	.parse_cs = amdgpu_uvd_ring_parse_cs,
	.emit_frame_size =
		14, /* uvd_v3_1_ring_emit_fence  x1 no user fence */
	.emit_ib_size = 4, /* uvd_v3_1_ring_emit_ib */
	.emit_ib = uvd_v3_1_ring_emit_ib,
	.emit_fence = uvd_v3_1_ring_emit_fence,
	.test_ring = uvd_v3_1_ring_test_ring,
	.test_ib = amdgpu_uvd_ring_test_ib,
	.insert_nop = uvd_v3_1_ring_insert_nop,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = amdgpu_uvd_ring_begin_use,
	.end_use = amdgpu_uvd_ring_end_use,
पूर्ण;

अटल व्योम uvd_v3_1_set_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->uvd.inst->ring.funcs = &uvd_v3_1_ring_funcs;
पूर्ण

अटल व्योम uvd_v3_1_set_dcm(काष्ठा amdgpu_device *adev,
							 bool sw_mode)
अणु
	u32 पंचांगp, पंचांगp2;

	WREG32_FIELD(UVD_CGC_GATE, REGS, 0);

	पंचांगp = RREG32(mmUVD_CGC_CTRL);
	पंचांगp &= ~(UVD_CGC_CTRL__CLK_OFF_DELAY_MASK | UVD_CGC_CTRL__CLK_GATE_DLY_TIMER_MASK);
	पंचांगp |= UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK |
		(1 << UVD_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT) |
		(4 << UVD_CGC_CTRL__CLK_OFF_DELAY__SHIFT);

	अगर (sw_mode) अणु
		पंचांगp &= ~0x7ffff800;
		पंचांगp2 = UVD_CGC_CTRL2__DYN_OCLK_RAMP_EN_MASK |
			UVD_CGC_CTRL2__DYN_RCLK_RAMP_EN_MASK |
			(7 << UVD_CGC_CTRL2__GATER_DIV_ID__SHIFT);
	पूर्ण अन्यथा अणु
		पंचांगp |= 0x7ffff800;
		पंचांगp2 = 0;
	पूर्ण

	WREG32(mmUVD_CGC_CTRL, पंचांगp);
	WREG32_UVD_CTX(ixUVD_CGC_CTRL2, पंचांगp2);
पूर्ण

/**
 * uvd_v3_1_mc_resume - memory controller programming
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Let the UVD memory controller know it's offsets
 */
अटल व्योम uvd_v3_1_mc_resume(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t addr;
	uपूर्णांक32_t size;

	/* programm the VCPU memory controller bits 0-27 */
	addr = (adev->uvd.inst->gpu_addr + AMDGPU_UVD_FIRMWARE_OFFSET) >> 3;
	size = AMDGPU_UVD_FIRMWARE_SIZE(adev) >> 3;
	WREG32(mmUVD_VCPU_CACHE_OFFSET0, addr);
	WREG32(mmUVD_VCPU_CACHE_SIZE0, size);

	addr += size;
	size = AMDGPU_UVD_HEAP_SIZE >> 3;
	WREG32(mmUVD_VCPU_CACHE_OFFSET1, addr);
	WREG32(mmUVD_VCPU_CACHE_SIZE1, size);

	addr += size;
	size = (AMDGPU_UVD_STACK_SIZE +
		(AMDGPU_UVD_SESSION_SIZE * adev->uvd.max_handles)) >> 3;
	WREG32(mmUVD_VCPU_CACHE_OFFSET2, addr);
	WREG32(mmUVD_VCPU_CACHE_SIZE2, size);

	/* bits 28-31 */
	addr = (adev->uvd.inst->gpu_addr >> 28) & 0xF;
	WREG32(mmUVD_LMI_ADDR_EXT, (addr << 12) | (addr << 0));

	/* bits 32-39 */
	addr = (adev->uvd.inst->gpu_addr >> 32) & 0xFF;
	WREG32(mmUVD_LMI_EXT40_ADDR, addr | (0x9 << 16) | (0x1 << 31));

	WREG32(mmUVD_UDEC_ADDR_CONFIG, adev->gfx.config.gb_addr_config);
	WREG32(mmUVD_UDEC_DB_ADDR_CONFIG, adev->gfx.config.gb_addr_config);
	WREG32(mmUVD_UDEC_DBW_ADDR_CONFIG, adev->gfx.config.gb_addr_config);
पूर्ण

/**
 * uvd_v3_1_fw_validate - FW validation operation
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Initialate and check UVD validation.
 */
अटल पूर्णांक uvd_v3_1_fw_validate(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;
	uपूर्णांक32_t keysel = adev->uvd.keyselect;

	WREG32(mmUVD_FW_START, keysel);

	क्रम (i = 0; i < 10; ++i) अणु
		mdelay(10);
		अगर (RREG32(mmUVD_FW_STATUS) & UVD_FW_STATUS__DONE_MASK)
			अवरोध;
	पूर्ण

	अगर (i == 10)
		वापस -ETIMEDOUT;

	अगर (!(RREG32(mmUVD_FW_STATUS) & UVD_FW_STATUS__PASS_MASK))
		वापस -EINVAL;

	क्रम (i = 0; i < 10; ++i) अणु
		mdelay(10);
		अगर (!(RREG32(mmUVD_FW_STATUS) & UVD_FW_STATUS__BUSY_MASK))
			अवरोध;
	पूर्ण

	अगर (i == 10)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

/**
 * uvd_v3_1_start - start UVD block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Setup and start the UVD block
 */
अटल पूर्णांक uvd_v3_1_start(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring = &adev->uvd.inst->ring;
	uपूर्णांक32_t rb_bufsz;
	पूर्णांक i, j, r;
	u32 पंचांगp;
	/* disable byte swapping */
	u32 lmi_swap_cntl = 0;
	u32 mp_swap_cntl = 0;

	/* set uvd busy */
	WREG32_P(mmUVD_STATUS, 1<<2, ~(1<<2));

	uvd_v3_1_set_dcm(adev, true);
	WREG32(mmUVD_CGC_GATE, 0);

	/* take UVD block out of reset */
	WREG32_P(mmSRBM_SOFT_RESET, 0, ~SRBM_SOFT_RESET__SOFT_RESET_UVD_MASK);
	mdelay(5);

	/* enable VCPU घड़ी */
	WREG32(mmUVD_VCPU_CNTL,  1 << 9);

	/* disable पूर्णांकerupt */
	WREG32_P(mmUVD_MASTINT_EN, 0, ~(1 << 1));

#अगर_घोषित __BIG_ENDIAN
	/* swap (8 in 32) RB and IB */
	lmi_swap_cntl = 0xa;
	mp_swap_cntl = 0;
#पूर्ण_अगर
	WREG32(mmUVD_LMI_SWAP_CNTL, lmi_swap_cntl);
	WREG32(mmUVD_MP_SWAP_CNTL, mp_swap_cntl);

	/* initialize UVD memory controller */
	WREG32(mmUVD_LMI_CTRL, 0x40 | (1 << 8) | (1 << 13) |
		(1 << 21) | (1 << 9) | (1 << 20));

	पंचांगp = RREG32(mmUVD_MPC_CNTL);
	WREG32(mmUVD_MPC_CNTL, पंचांगp | 0x10);

	WREG32(mmUVD_MPC_SET_MUXA0, 0x40c2040);
	WREG32(mmUVD_MPC_SET_MUXA1, 0x0);
	WREG32(mmUVD_MPC_SET_MUXB0, 0x40c2040);
	WREG32(mmUVD_MPC_SET_MUXB1, 0x0);
	WREG32(mmUVD_MPC_SET_ALU, 0);
	WREG32(mmUVD_MPC_SET_MUX, 0x88);

	पंचांगp = RREG32_UVD_CTX(ixUVD_LMI_CACHE_CTRL);
	WREG32_UVD_CTX(ixUVD_LMI_CACHE_CTRL, पंचांगp & (~0x10));

	/* enable UMC */
	WREG32_P(mmUVD_LMI_CTRL2, 0, ~(1 << 8));

	WREG32_P(mmUVD_SOFT_RESET, 0, ~UVD_SOFT_RESET__LMI_SOFT_RESET_MASK);

	WREG32_P(mmUVD_SOFT_RESET, 0, ~UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK);

	WREG32_P(mmUVD_SOFT_RESET, 0, ~UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);

	mdelay(10);

	क्रम (i = 0; i < 10; ++i) अणु
		uपूर्णांक32_t status;
		क्रम (j = 0; j < 100; ++j) अणु
			status = RREG32(mmUVD_STATUS);
			अगर (status & 2)
				अवरोध;
			mdelay(10);
		पूर्ण
		r = 0;
		अगर (status & 2)
			अवरोध;

		DRM_ERROR("UVD not responding, trying to reset the VCPU!!!\n");
		WREG32_P(mmUVD_SOFT_RESET, UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK,
				 ~UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
		mdelay(10);
		WREG32_P(mmUVD_SOFT_RESET, 0, ~UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
		mdelay(10);
		r = -1;
	पूर्ण

	अगर (r) अणु
		DRM_ERROR("UVD not responding, giving up!!!\n");
		वापस r;
	पूर्ण

	/* enable पूर्णांकerupt */
	WREG32_P(mmUVD_MASTINT_EN, 3<<1, ~(3 << 1));

	WREG32_P(mmUVD_STATUS, 0, ~(1<<2));

	/* क्रमce RBC पूर्णांकo idle state */
	WREG32(mmUVD_RBC_RB_CNTL, 0x11010101);

	/* Set the ग_लिखो poपूर्णांकer delay */
	WREG32(mmUVD_RBC_RB_WPTR_CNTL, 0);

	/* programm the 4GB memory segment क्रम rptr and ring buffer */
	WREG32(mmUVD_LMI_EXT40_ADDR, upper_32_bits(ring->gpu_addr) |
		   (0x7 << 16) | (0x1 << 31));

	/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
	WREG32(mmUVD_RBC_RB_RPTR, 0x0);

	ring->wptr = RREG32(mmUVD_RBC_RB_RPTR);
	WREG32(mmUVD_RBC_RB_WPTR, lower_32_bits(ring->wptr));

	/* set the ring address */
	WREG32(mmUVD_RBC_RB_BASE, ring->gpu_addr);

	/* Set ring buffer size */
	rb_bufsz = order_base_2(ring->ring_size);
	rb_bufsz = (0x1 << 8) | rb_bufsz;
	WREG32_P(mmUVD_RBC_RB_CNTL, rb_bufsz, ~0x11f1f);

	वापस 0;
पूर्ण

/**
 * uvd_v3_1_stop - stop UVD block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * stop the UVD block
 */
अटल व्योम uvd_v3_1_stop(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t i, j;
	uपूर्णांक32_t status;

	WREG32(mmUVD_RBC_RB_CNTL, 0x11010101);

	क्रम (i = 0; i < 10; ++i) अणु
		क्रम (j = 0; j < 100; ++j) अणु
			status = RREG32(mmUVD_STATUS);
			अगर (status & 2)
				अवरोध;
			mdelay(1);
		पूर्ण
		अगर (status & 2)
			अवरोध;
	पूर्ण

	क्रम (i = 0; i < 10; ++i) अणु
		क्रम (j = 0; j < 100; ++j) अणु
			status = RREG32(mmUVD_LMI_STATUS);
			अगर (status & 0xf)
				अवरोध;
			mdelay(1);
		पूर्ण
		अगर (status & 0xf)
			अवरोध;
	पूर्ण

	/* Stall UMC and रेजिस्टर bus beक्रमe resetting VCPU */
	WREG32_P(mmUVD_LMI_CTRL2, 1 << 8, ~(1 << 8));

	क्रम (i = 0; i < 10; ++i) अणु
		क्रम (j = 0; j < 100; ++j) अणु
			status = RREG32(mmUVD_LMI_STATUS);
			अगर (status & 0x240)
				अवरोध;
			mdelay(1);
		पूर्ण
		अगर (status & 0x240)
			अवरोध;
	पूर्ण

	WREG32_P(0x3D49, 0, ~(1 << 2));

	WREG32_P(mmUVD_VCPU_CNTL, 0, ~(1 << 9));

	/* put LMI, VCPU, RBC etc... पूर्णांकo reset */
	WREG32(mmUVD_SOFT_RESET, UVD_SOFT_RESET__LMI_SOFT_RESET_MASK |
		UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK |
		UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK);

	WREG32(mmUVD_STATUS, 0);

	uvd_v3_1_set_dcm(adev, false);
पूर्ण

अटल पूर्णांक uvd_v3_1_set_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v3_1_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	DRM_DEBUG("IH: UVD TRAP\n");
	amdgpu_fence_process(&adev->uvd.inst->ring);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा amdgpu_irq_src_funcs uvd_v3_1_irq_funcs = अणु
	.set = uvd_v3_1_set_पूर्णांकerrupt_state,
	.process = uvd_v3_1_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम uvd_v3_1_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->uvd.inst->irq.num_types = 1;
	adev->uvd.inst->irq.funcs = &uvd_v3_1_irq_funcs;
पूर्ण


अटल पूर्णांक uvd_v3_1_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	adev->uvd.num_uvd_inst = 1;

	uvd_v3_1_set_ring_funcs(adev);
	uvd_v3_1_set_irq_funcs(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v3_1_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_ring *ring;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;
	व्योम *ptr;
	uपूर्णांक32_t ucode_len;

	/* UVD TRAP */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 124, &adev->uvd.inst->irq);
	अगर (r)
		वापस r;

	r = amdgpu_uvd_sw_init(adev);
	अगर (r)
		वापस r;

	ring = &adev->uvd.inst->ring;
	प्र_लिखो(ring->name, "uvd");
	r = amdgpu_ring_init(adev, ring, 512, &adev->uvd.inst->irq, 0,
			 AMDGPU_RING_PRIO_DEFAULT, शून्य);
	अगर (r)
		वापस r;

	r = amdgpu_uvd_resume(adev);
	अगर (r)
		वापस r;

	/* Retrieval firmware validate key */
	ptr = adev->uvd.inst[0].cpu_addr;
	ptr += 192 + 16;
	स_नकल(&ucode_len, ptr, 4);
	ptr += ucode_len;
	स_नकल(&adev->uvd.keyselect, ptr, 4);

	r = amdgpu_uvd_entity_init(adev);

	वापस r;
पूर्ण

अटल पूर्णांक uvd_v3_1_sw_fini(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_uvd_suspend(adev);
	अगर (r)
		वापस r;

	वापस amdgpu_uvd_sw_fini(adev);
पूर्ण

अटल व्योम uvd_v3_1_enable_mgcg(काष्ठा amdgpu_device *adev,
				 bool enable)
अणु
	u32 orig, data;

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_UVD_MGCG)) अणु
		data = RREG32_UVD_CTX(ixUVD_CGC_MEM_CTRL);
		data |= 0x3fff;
		WREG32_UVD_CTX(ixUVD_CGC_MEM_CTRL, data);

		orig = data = RREG32(mmUVD_CGC_CTRL);
		data |= UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK;
		अगर (orig != data)
			WREG32(mmUVD_CGC_CTRL, data);
	पूर्ण अन्यथा अणु
		data = RREG32_UVD_CTX(ixUVD_CGC_MEM_CTRL);
		data &= ~0x3fff;
		WREG32_UVD_CTX(ixUVD_CGC_MEM_CTRL, data);

		orig = data = RREG32(mmUVD_CGC_CTRL);
		data &= ~UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK;
		अगर (orig != data)
			WREG32(mmUVD_CGC_CTRL, data);
	पूर्ण
पूर्ण

/**
 * uvd_v3_1_hw_init - start and test UVD block
 *
 * @handle: handle used to pass amdgpu_device poपूर्णांकer
 *
 * Initialize the hardware, boot up the VCPU and करो some testing
 */
अटल पूर्णांक uvd_v3_1_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा amdgpu_ring *ring = &adev->uvd.inst->ring;
	uपूर्णांक32_t पंचांगp;
	पूर्णांक r;

	uvd_v3_1_mc_resume(adev);

	r = uvd_v3_1_fw_validate(adev);
	अगर (r) अणु
		DRM_ERROR("amdgpu: UVD Firmware validate fail (%d).\n", r);
		वापस r;
	पूर्ण

	uvd_v3_1_enable_mgcg(adev, true);
	amdgpu_asic_set_uvd_घड़ीs(adev, 53300, 40000);

	uvd_v3_1_start(adev);

	r = amdgpu_ring_test_helper(ring);
	अगर (r) अणु
		DRM_ERROR("amdgpu: UVD ring test fail (%d).\n", r);
		जाओ करोne;
	पूर्ण

	r = amdgpu_ring_alloc(ring, 10);
	अगर (r) अणु
		DRM_ERROR("amdgpu: ring failed to lock UVD ring (%d).\n", r);
		जाओ करोne;
	पूर्ण

	पंचांगp = PACKET0(mmUVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL, 0);
	amdgpu_ring_ग_लिखो(ring, पंचांगp);
	amdgpu_ring_ग_लिखो(ring, 0xFFFFF);

	पंचांगp = PACKET0(mmUVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL, 0);
	amdgpu_ring_ग_लिखो(ring, पंचांगp);
	amdgpu_ring_ग_लिखो(ring, 0xFFFFF);

	पंचांगp = PACKET0(mmUVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL, 0);
	amdgpu_ring_ग_लिखो(ring, पंचांगp);
	amdgpu_ring_ग_लिखो(ring, 0xFFFFF);

	/* Clear समयout status bits */
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_SEMA_TIMEOUT_STATUS, 0));
	amdgpu_ring_ग_लिखो(ring, 0x8);

	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_SEMA_CNTL, 0));
	amdgpu_ring_ग_लिखो(ring, 3);

	amdgpu_ring_commit(ring);

करोne:
	अगर (!r)
		DRM_INFO("UVD initialized successfully.\n");

	वापस r;
पूर्ण

/**
 * uvd_v3_1_hw_fini - stop the hardware block
 *
 * @handle: handle used to pass amdgpu_device poपूर्णांकer
 *
 * Stop the UVD block, mark ring as not पढ़ोy any more
 */
अटल पूर्णांक uvd_v3_1_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (RREG32(mmUVD_STATUS) != 0)
		uvd_v3_1_stop(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v3_1_suspend(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = uvd_v3_1_hw_fini(adev);
	अगर (r)
		वापस r;

	वापस amdgpu_uvd_suspend(adev);
पूर्ण

अटल पूर्णांक uvd_v3_1_resume(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_uvd_resume(adev);
	अगर (r)
		वापस r;

	वापस uvd_v3_1_hw_init(adev);
पूर्ण

अटल bool uvd_v3_1_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस !(RREG32(mmSRBM_STATUS) & SRBM_STATUS__UVD_BUSY_MASK);
पूर्ण

अटल पूर्णांक uvd_v3_1_रुको_क्रम_idle(व्योम *handle)
अणु
	अचिन्हित i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (!(RREG32(mmSRBM_STATUS) & SRBM_STATUS__UVD_BUSY_MASK))
			वापस 0;
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक uvd_v3_1_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	uvd_v3_1_stop(adev);

	WREG32_P(mmSRBM_SOFT_RESET, SRBM_SOFT_RESET__SOFT_RESET_UVD_MASK,
			 ~SRBM_SOFT_RESET__SOFT_RESET_UVD_MASK);
	mdelay(5);

	वापस uvd_v3_1_start(adev);
पूर्ण

अटल पूर्णांक uvd_v3_1_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v3_1_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs uvd_v3_1_ip_funcs = अणु
	.name = "uvd_v3_1",
	.early_init = uvd_v3_1_early_init,
	.late_init = शून्य,
	.sw_init = uvd_v3_1_sw_init,
	.sw_fini = uvd_v3_1_sw_fini,
	.hw_init = uvd_v3_1_hw_init,
	.hw_fini = uvd_v3_1_hw_fini,
	.suspend = uvd_v3_1_suspend,
	.resume = uvd_v3_1_resume,
	.is_idle = uvd_v3_1_is_idle,
	.रुको_क्रम_idle = uvd_v3_1_रुको_क्रम_idle,
	.soft_reset = uvd_v3_1_soft_reset,
	.set_घड़ीgating_state = uvd_v3_1_set_घड़ीgating_state,
	.set_घातergating_state = uvd_v3_1_set_घातergating_state,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version uvd_v3_1_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_UVD,
	.major = 3,
	.minor = 1,
	.rev = 0,
	.funcs = &uvd_v3_1_ip_funcs,
पूर्ण;
