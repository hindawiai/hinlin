<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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
 * Authors: Christian Kथघnig <christian.koenig@amd.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_uvd.h"
#समावेश "vid.h"
#समावेश "uvd/uvd_5_0_d.h"
#समावेश "uvd/uvd_5_0_sh_mask.h"
#समावेश "oss/oss_2_0_d.h"
#समावेश "oss/oss_2_0_sh_mask.h"
#समावेश "bif/bif_5_0_d.h"
#समावेश "vi.h"
#समावेश "smu/smu_7_1_2_d.h"
#समावेश "smu/smu_7_1_2_sh_mask.h"
#समावेश "ivsrcid/ivsrcid_vislands30.h"

अटल व्योम uvd_v5_0_set_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम uvd_v5_0_set_irq_funcs(काष्ठा amdgpu_device *adev);
अटल पूर्णांक uvd_v5_0_start(काष्ठा amdgpu_device *adev);
अटल व्योम uvd_v5_0_stop(काष्ठा amdgpu_device *adev);
अटल पूर्णांक uvd_v5_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state);
अटल व्योम uvd_v5_0_enable_mgcg(काष्ठा amdgpu_device *adev,
				 bool enable);
/**
 * uvd_v5_0_ring_get_rptr - get पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t uvd_v5_0_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32(mmUVD_RBC_RB_RPTR);
पूर्ण

/**
 * uvd_v5_0_ring_get_wptr - get ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t uvd_v5_0_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32(mmUVD_RBC_RB_WPTR);
पूर्ण

/**
 * uvd_v5_0_ring_set_wptr - set ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम uvd_v5_0_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	WREG32(mmUVD_RBC_RB_WPTR, lower_32_bits(ring->wptr));
पूर्ण

अटल पूर्णांक uvd_v5_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	adev->uvd.num_uvd_inst = 1;

	uvd_v5_0_set_ring_funcs(adev);
	uvd_v5_0_set_irq_funcs(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v5_0_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_ring *ring;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	/* UVD TRAP */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_UVD_SYSTEM_MESSAGE, &adev->uvd.inst->irq);
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

	r = amdgpu_uvd_entity_init(adev);

	वापस r;
पूर्ण

अटल पूर्णांक uvd_v5_0_sw_fini(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_uvd_suspend(adev);
	अगर (r)
		वापस r;

	वापस amdgpu_uvd_sw_fini(adev);
पूर्ण

/**
 * uvd_v5_0_hw_init - start and test UVD block
 *
 * @handle: handle used to pass amdgpu_device poपूर्णांकer
 *
 * Initialize the hardware, boot up the VCPU and करो some testing
 */
अटल पूर्णांक uvd_v5_0_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा amdgpu_ring *ring = &adev->uvd.inst->ring;
	uपूर्णांक32_t पंचांगp;
	पूर्णांक r;

	amdgpu_asic_set_uvd_घड़ीs(adev, 10000, 10000);
	uvd_v5_0_set_घड़ीgating_state(adev, AMD_CG_STATE_UNGATE);
	uvd_v5_0_enable_mgcg(adev, true);

	r = amdgpu_ring_test_helper(ring);
	अगर (r)
		जाओ करोne;

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
 * uvd_v5_0_hw_fini - stop the hardware block
 *
 * @handle: handle used to pass amdgpu_device poपूर्णांकer
 *
 * Stop the UVD block, mark ring as not पढ़ोy any more
 */
अटल पूर्णांक uvd_v5_0_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (RREG32(mmUVD_STATUS) != 0)
		uvd_v5_0_stop(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v5_0_suspend(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = uvd_v5_0_hw_fini(adev);
	अगर (r)
		वापस r;
	uvd_v5_0_set_घड़ीgating_state(adev, AMD_CG_STATE_GATE);

	वापस amdgpu_uvd_suspend(adev);
पूर्ण

अटल पूर्णांक uvd_v5_0_resume(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_uvd_resume(adev);
	अगर (r)
		वापस r;

	वापस uvd_v5_0_hw_init(adev);
पूर्ण

/**
 * uvd_v5_0_mc_resume - memory controller programming
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Let the UVD memory controller know it's offsets
 */
अटल व्योम uvd_v5_0_mc_resume(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t offset;
	uपूर्णांक32_t size;

	/* program memory controller bits 0-27 */
	WREG32(mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW,
			lower_32_bits(adev->uvd.inst->gpu_addr));
	WREG32(mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH,
			upper_32_bits(adev->uvd.inst->gpu_addr));

	offset = AMDGPU_UVD_FIRMWARE_OFFSET;
	size = AMDGPU_UVD_FIRMWARE_SIZE(adev);
	WREG32(mmUVD_VCPU_CACHE_OFFSET0, offset >> 3);
	WREG32(mmUVD_VCPU_CACHE_SIZE0, size);

	offset += size;
	size = AMDGPU_UVD_HEAP_SIZE;
	WREG32(mmUVD_VCPU_CACHE_OFFSET1, offset >> 3);
	WREG32(mmUVD_VCPU_CACHE_SIZE1, size);

	offset += size;
	size = AMDGPU_UVD_STACK_SIZE +
	       (AMDGPU_UVD_SESSION_SIZE * adev->uvd.max_handles);
	WREG32(mmUVD_VCPU_CACHE_OFFSET2, offset >> 3);
	WREG32(mmUVD_VCPU_CACHE_SIZE2, size);

	WREG32(mmUVD_UDEC_ADDR_CONFIG, adev->gfx.config.gb_addr_config);
	WREG32(mmUVD_UDEC_DB_ADDR_CONFIG, adev->gfx.config.gb_addr_config);
	WREG32(mmUVD_UDEC_DBW_ADDR_CONFIG, adev->gfx.config.gb_addr_config);
पूर्ण

/**
 * uvd_v5_0_start - start UVD block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Setup and start the UVD block
 */
अटल पूर्णांक uvd_v5_0_start(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring = &adev->uvd.inst->ring;
	uपूर्णांक32_t rb_bufsz, पंचांगp;
	uपूर्णांक32_t lmi_swap_cntl;
	uपूर्णांक32_t mp_swap_cntl;
	पूर्णांक i, j, r;

	/*disable DPG */
	WREG32_P(mmUVD_POWER_STATUS, 0, ~(1 << 2));

	/* disable byte swapping */
	lmi_swap_cntl = 0;
	mp_swap_cntl = 0;

	uvd_v5_0_mc_resume(adev);

	/* disable पूर्णांकerupt */
	WREG32_P(mmUVD_MASTINT_EN, 0, ~(1 << 1));

	/* stall UMC and रेजिस्टर bus beक्रमe resetting VCPU */
	WREG32_P(mmUVD_LMI_CTRL2, 1 << 8, ~(1 << 8));
	mdelay(1);

	/* put LMI, VCPU, RBC etc... पूर्णांकo reset */
	WREG32(mmUVD_SOFT_RESET, UVD_SOFT_RESET__LMI_SOFT_RESET_MASK |
		UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK | UVD_SOFT_RESET__LBSI_SOFT_RESET_MASK |
		UVD_SOFT_RESET__RBC_SOFT_RESET_MASK | UVD_SOFT_RESET__CSM_SOFT_RESET_MASK |
		UVD_SOFT_RESET__CXW_SOFT_RESET_MASK | UVD_SOFT_RESET__TAP_SOFT_RESET_MASK |
		UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK);
	mdelay(5);

	/* take UVD block out of reset */
	WREG32_P(mmSRBM_SOFT_RESET, 0, ~SRBM_SOFT_RESET__SOFT_RESET_UVD_MASK);
	mdelay(5);

	/* initialize UVD memory controller */
	WREG32(mmUVD_LMI_CTRL, 0x40 | (1 << 8) | (1 << 13) |
			     (1 << 21) | (1 << 9) | (1 << 20));

#अगर_घोषित __BIG_ENDIAN
	/* swap (8 in 32) RB and IB */
	lmi_swap_cntl = 0xa;
	mp_swap_cntl = 0;
#पूर्ण_अगर
	WREG32(mmUVD_LMI_SWAP_CNTL, lmi_swap_cntl);
	WREG32(mmUVD_MP_SWAP_CNTL, mp_swap_cntl);

	WREG32(mmUVD_MPC_SET_MUXA0, 0x40c2040);
	WREG32(mmUVD_MPC_SET_MUXA1, 0x0);
	WREG32(mmUVD_MPC_SET_MUXB0, 0x40c2040);
	WREG32(mmUVD_MPC_SET_MUXB1, 0x0);
	WREG32(mmUVD_MPC_SET_ALU, 0);
	WREG32(mmUVD_MPC_SET_MUX, 0x88);

	/* take all subblocks out of reset, except VCPU */
	WREG32(mmUVD_SOFT_RESET, UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
	mdelay(5);

	/* enable VCPU घड़ी */
	WREG32(mmUVD_VCPU_CNTL,  1 << 9);

	/* enable UMC */
	WREG32_P(mmUVD_LMI_CTRL2, 0, ~(1 << 8));

	/* boot up the VCPU */
	WREG32(mmUVD_SOFT_RESET, 0);
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
	/* enable master पूर्णांकerrupt */
	WREG32_P(mmUVD_MASTINT_EN, 3 << 1, ~(3 << 1));

	/* clear the bit 4 of UVD_STATUS */
	WREG32_P(mmUVD_STATUS, 0, ~(2 << 1));

	rb_bufsz = order_base_2(ring->ring_size);
	पंचांगp = 0;
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_BUFSZ, rb_bufsz);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_BLKSZ, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_FETCH, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_WPTR_POLL_EN, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_UPDATE, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_RPTR_WR_EN, 1);
	/* क्रमce RBC पूर्णांकo idle state */
	WREG32(mmUVD_RBC_RB_CNTL, पंचांगp);

	/* set the ग_लिखो poपूर्णांकer delay */
	WREG32(mmUVD_RBC_RB_WPTR_CNTL, 0);

	/* set the wb address */
	WREG32(mmUVD_RBC_RB_RPTR_ADDR, (upper_32_bits(ring->gpu_addr) >> 2));

	/* program the RB_BASE क्रम ring buffer */
	WREG32(mmUVD_LMI_RBC_RB_64BIT_BAR_LOW,
			lower_32_bits(ring->gpu_addr));
	WREG32(mmUVD_LMI_RBC_RB_64BIT_BAR_HIGH,
			upper_32_bits(ring->gpu_addr));

	/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
	WREG32(mmUVD_RBC_RB_RPTR, 0);

	ring->wptr = RREG32(mmUVD_RBC_RB_RPTR);
	WREG32(mmUVD_RBC_RB_WPTR, lower_32_bits(ring->wptr));

	WREG32_P(mmUVD_RBC_RB_CNTL, 0, ~UVD_RBC_RB_CNTL__RB_NO_FETCH_MASK);

	वापस 0;
पूर्ण

/**
 * uvd_v5_0_stop - stop UVD block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * stop the UVD block
 */
अटल व्योम uvd_v5_0_stop(काष्ठा amdgpu_device *adev)
अणु
	/* क्रमce RBC पूर्णांकo idle state */
	WREG32(mmUVD_RBC_RB_CNTL, 0x11010101);

	/* Stall UMC and रेजिस्टर bus beक्रमe resetting VCPU */
	WREG32_P(mmUVD_LMI_CTRL2, 1 << 8, ~(1 << 8));
	mdelay(1);

	/* put VCPU पूर्णांकo reset */
	WREG32(mmUVD_SOFT_RESET, UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
	mdelay(5);

	/* disable VCPU घड़ी */
	WREG32(mmUVD_VCPU_CNTL, 0x0);

	/* Unstall UMC and रेजिस्टर bus */
	WREG32_P(mmUVD_LMI_CTRL2, 0, ~(1 << 8));

	WREG32(mmUVD_STATUS, 0);
पूर्ण

/**
 * uvd_v5_0_ring_emit_fence - emit an fence & trap command
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @addr: address
 * @seq: sequence number
 * @flags: fence related flags
 *
 * Write a fence and a trap command to the ring.
 */
अटल व्योम uvd_v5_0_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr, u64 seq,
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
 * uvd_v5_0_ring_test_ring - रेजिस्टर ग_लिखो test
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Test अगर we can successfully ग_लिखो to the context रेजिस्टर
 */
अटल पूर्णांक uvd_v5_0_ring_test_ring(काष्ठा amdgpu_ring *ring)
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

/**
 * uvd_v5_0_ring_emit_ib - execute indirect buffer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @job: job to retrieve vmid from
 * @ib: indirect buffer to execute
 * @flags: unused
 *
 * Write ring commands to execute the indirect buffer
 */
अटल व्योम uvd_v5_0_ring_emit_ib(काष्ठा amdgpu_ring *ring,
				  काष्ठा amdgpu_job *job,
				  काष्ठा amdgpu_ib *ib,
				  uपूर्णांक32_t flags)
अणु
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_LMI_RBC_IB_64BIT_BAR_LOW, 0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_LMI_RBC_IB_64BIT_BAR_HIGH, 0));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_RBC_IB_SIZE, 0));
	amdgpu_ring_ग_लिखो(ring, ib->length_dw);
पूर्ण

अटल व्योम uvd_v5_0_ring_insert_nop(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t count)
अणु
	पूर्णांक i;

	WARN_ON(ring->wptr % 2 || count % 2);

	क्रम (i = 0; i < count / 2; i++) अणु
		amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_NO_OP, 0));
		amdgpu_ring_ग_लिखो(ring, 0);
	पूर्ण
पूर्ण

अटल bool uvd_v5_0_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस !(RREG32(mmSRBM_STATUS) & SRBM_STATUS__UVD_BUSY_MASK);
पूर्ण

अटल पूर्णांक uvd_v5_0_रुको_क्रम_idle(व्योम *handle)
अणु
	अचिन्हित i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (!(RREG32(mmSRBM_STATUS) & SRBM_STATUS__UVD_BUSY_MASK))
			वापस 0;
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक uvd_v5_0_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	uvd_v5_0_stop(adev);

	WREG32_P(mmSRBM_SOFT_RESET, SRBM_SOFT_RESET__SOFT_RESET_UVD_MASK,
			~SRBM_SOFT_RESET__SOFT_RESET_UVD_MASK);
	mdelay(5);

	वापस uvd_v5_0_start(adev);
पूर्ण

अटल पूर्णांक uvd_v5_0_set_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	// TODO
	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v5_0_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	DRM_DEBUG("IH: UVD TRAP\n");
	amdgpu_fence_process(&adev->uvd.inst->ring);
	वापस 0;
पूर्ण

अटल व्योम uvd_v5_0_enable_घड़ी_gating(काष्ठा amdgpu_device *adev, bool enable)
अणु
	uपूर्णांक32_t data1, data3, suvd_flags;

	data1 = RREG32(mmUVD_SUVD_CGC_GATE);
	data3 = RREG32(mmUVD_CGC_GATE);

	suvd_flags = UVD_SUVD_CGC_GATE__SRE_MASK |
		     UVD_SUVD_CGC_GATE__SIT_MASK |
		     UVD_SUVD_CGC_GATE__SMP_MASK |
		     UVD_SUVD_CGC_GATE__SCM_MASK |
		     UVD_SUVD_CGC_GATE__SDB_MASK;

	अगर (enable) अणु
		data3 |= (UVD_CGC_GATE__SYS_MASK     |
			UVD_CGC_GATE__UDEC_MASK      |
			UVD_CGC_GATE__MPEG2_MASK     |
			UVD_CGC_GATE__RBC_MASK       |
			UVD_CGC_GATE__LMI_MC_MASK    |
			UVD_CGC_GATE__IDCT_MASK      |
			UVD_CGC_GATE__MPRD_MASK      |
			UVD_CGC_GATE__MPC_MASK       |
			UVD_CGC_GATE__LBSI_MASK      |
			UVD_CGC_GATE__LRBBM_MASK     |
			UVD_CGC_GATE__UDEC_RE_MASK   |
			UVD_CGC_GATE__UDEC_CM_MASK   |
			UVD_CGC_GATE__UDEC_IT_MASK   |
			UVD_CGC_GATE__UDEC_DB_MASK   |
			UVD_CGC_GATE__UDEC_MP_MASK   |
			UVD_CGC_GATE__WCB_MASK       |
			UVD_CGC_GATE__JPEG_MASK      |
			UVD_CGC_GATE__SCPU_MASK);
		/* only in pg enabled, we can gate घड़ी to vcpu*/
		अगर (adev->pg_flags & AMD_PG_SUPPORT_UVD)
			data3 |= UVD_CGC_GATE__VCPU_MASK;
		data3 &= ~UVD_CGC_GATE__REGS_MASK;
		data1 |= suvd_flags;
	पूर्ण अन्यथा अणु
		data3 = 0;
		data1 = 0;
	पूर्ण

	WREG32(mmUVD_SUVD_CGC_GATE, data1);
	WREG32(mmUVD_CGC_GATE, data3);
पूर्ण

अटल व्योम uvd_v5_0_set_sw_घड़ी_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data, data2;

	data = RREG32(mmUVD_CGC_CTRL);
	data2 = RREG32(mmUVD_SUVD_CGC_CTRL);


	data &= ~(UVD_CGC_CTRL__CLK_OFF_DELAY_MASK |
		  UVD_CGC_CTRL__CLK_GATE_DLY_TIMER_MASK);


	data |= UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK |
		(1 << REG_FIELD_SHIFT(UVD_CGC_CTRL, CLK_GATE_DLY_TIMER)) |
		(4 << REG_FIELD_SHIFT(UVD_CGC_CTRL, CLK_OFF_DELAY));

	data &= ~(UVD_CGC_CTRL__UDEC_RE_MODE_MASK |
			UVD_CGC_CTRL__UDEC_CM_MODE_MASK |
			UVD_CGC_CTRL__UDEC_IT_MODE_MASK |
			UVD_CGC_CTRL__UDEC_DB_MODE_MASK |
			UVD_CGC_CTRL__UDEC_MP_MODE_MASK |
			UVD_CGC_CTRL__SYS_MODE_MASK |
			UVD_CGC_CTRL__UDEC_MODE_MASK |
			UVD_CGC_CTRL__MPEG2_MODE_MASK |
			UVD_CGC_CTRL__REGS_MODE_MASK |
			UVD_CGC_CTRL__RBC_MODE_MASK |
			UVD_CGC_CTRL__LMI_MC_MODE_MASK |
			UVD_CGC_CTRL__LMI_UMC_MODE_MASK |
			UVD_CGC_CTRL__IDCT_MODE_MASK |
			UVD_CGC_CTRL__MPRD_MODE_MASK |
			UVD_CGC_CTRL__MPC_MODE_MASK |
			UVD_CGC_CTRL__LBSI_MODE_MASK |
			UVD_CGC_CTRL__LRBBM_MODE_MASK |
			UVD_CGC_CTRL__WCB_MODE_MASK |
			UVD_CGC_CTRL__VCPU_MODE_MASK |
			UVD_CGC_CTRL__JPEG_MODE_MASK |
			UVD_CGC_CTRL__SCPU_MODE_MASK);
	data2 &= ~(UVD_SUVD_CGC_CTRL__SRE_MODE_MASK |
			UVD_SUVD_CGC_CTRL__SIT_MODE_MASK |
			UVD_SUVD_CGC_CTRL__SMP_MODE_MASK |
			UVD_SUVD_CGC_CTRL__SCM_MODE_MASK |
			UVD_SUVD_CGC_CTRL__SDB_MODE_MASK);

	WREG32(mmUVD_CGC_CTRL, data);
	WREG32(mmUVD_SUVD_CGC_CTRL, data2);
पूर्ण

#अगर 0
अटल व्योम uvd_v5_0_set_hw_घड़ी_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data, data1, cgc_flags, suvd_flags;

	data = RREG32(mmUVD_CGC_GATE);
	data1 = RREG32(mmUVD_SUVD_CGC_GATE);

	cgc_flags = UVD_CGC_GATE__SYS_MASK |
				UVD_CGC_GATE__UDEC_MASK |
				UVD_CGC_GATE__MPEG2_MASK |
				UVD_CGC_GATE__RBC_MASK |
				UVD_CGC_GATE__LMI_MC_MASK |
				UVD_CGC_GATE__IDCT_MASK |
				UVD_CGC_GATE__MPRD_MASK |
				UVD_CGC_GATE__MPC_MASK |
				UVD_CGC_GATE__LBSI_MASK |
				UVD_CGC_GATE__LRBBM_MASK |
				UVD_CGC_GATE__UDEC_RE_MASK |
				UVD_CGC_GATE__UDEC_CM_MASK |
				UVD_CGC_GATE__UDEC_IT_MASK |
				UVD_CGC_GATE__UDEC_DB_MASK |
				UVD_CGC_GATE__UDEC_MP_MASK |
				UVD_CGC_GATE__WCB_MASK |
				UVD_CGC_GATE__VCPU_MASK |
				UVD_CGC_GATE__SCPU_MASK;

	suvd_flags = UVD_SUVD_CGC_GATE__SRE_MASK |
				UVD_SUVD_CGC_GATE__SIT_MASK |
				UVD_SUVD_CGC_GATE__SMP_MASK |
				UVD_SUVD_CGC_GATE__SCM_MASK |
				UVD_SUVD_CGC_GATE__SDB_MASK;

	data |= cgc_flags;
	data1 |= suvd_flags;

	WREG32(mmUVD_CGC_GATE, data);
	WREG32(mmUVD_SUVD_CGC_GATE, data1);
पूर्ण
#पूर्ण_अगर

अटल व्योम uvd_v5_0_enable_mgcg(काष्ठा amdgpu_device *adev,
				 bool enable)
अणु
	u32 orig, data;

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_UVD_MGCG)) अणु
		data = RREG32_UVD_CTX(ixUVD_CGC_MEM_CTRL);
		data |= 0xfff;
		WREG32_UVD_CTX(ixUVD_CGC_MEM_CTRL, data);

		orig = data = RREG32(mmUVD_CGC_CTRL);
		data |= UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK;
		अगर (orig != data)
			WREG32(mmUVD_CGC_CTRL, data);
	पूर्ण अन्यथा अणु
		data = RREG32_UVD_CTX(ixUVD_CGC_MEM_CTRL);
		data &= ~0xfff;
		WREG32_UVD_CTX(ixUVD_CGC_MEM_CTRL, data);

		orig = data = RREG32(mmUVD_CGC_CTRL);
		data &= ~UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK;
		अगर (orig != data)
			WREG32(mmUVD_CGC_CTRL, data);
	पूर्ण
पूर्ण

अटल पूर्णांक uvd_v5_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	bool enable = (state == AMD_CG_STATE_GATE);

	अगर (enable) अणु
		/* रुको क्रम STATUS to clear */
		अगर (uvd_v5_0_रुको_क्रम_idle(handle))
			वापस -EBUSY;
		uvd_v5_0_enable_घड़ी_gating(adev, true);

		/* enable HW gates because UVD is idle */
/*		uvd_v5_0_set_hw_घड़ी_gating(adev); */
	पूर्ण अन्यथा अणु
		uvd_v5_0_enable_घड़ी_gating(adev, false);
	पूर्ण

	uvd_v5_0_set_sw_घड़ी_gating(adev);
	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v5_0_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	/* This करोesn't actually घातergate the UVD block.
	 * That's करोne in the dpm code via the SMC.  This
	 * just re-inits the block as necessary.  The actual
	 * gating still happens in the dpm code.  We should
	 * revisit this when there is a cleaner line between
	 * the smc and the hw blocks
	 */
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक ret = 0;

	अगर (state == AMD_PG_STATE_GATE) अणु
		uvd_v5_0_stop(adev);
	पूर्ण अन्यथा अणु
		ret = uvd_v5_0_start(adev);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल व्योम uvd_v5_0_get_घड़ीgating_state(व्योम *handle, u32 *flags)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक data;

	mutex_lock(&adev->pm.mutex);

	अगर (RREG32_SMC(ixCURRENT_PG_STATUS) &
				CURRENT_PG_STATUS__UVD_PG_STATUS_MASK) अणु
		DRM_INFO("Cannot get clockgating state when UVD is powergated.\n");
		जाओ out;
	पूर्ण

	/* AMD_CG_SUPPORT_UVD_MGCG */
	data = RREG32(mmUVD_CGC_CTRL);
	अगर (data & UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK)
		*flags |= AMD_CG_SUPPORT_UVD_MGCG;

out:
	mutex_unlock(&adev->pm.mutex);
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs uvd_v5_0_ip_funcs = अणु
	.name = "uvd_v5_0",
	.early_init = uvd_v5_0_early_init,
	.late_init = शून्य,
	.sw_init = uvd_v5_0_sw_init,
	.sw_fini = uvd_v5_0_sw_fini,
	.hw_init = uvd_v5_0_hw_init,
	.hw_fini = uvd_v5_0_hw_fini,
	.suspend = uvd_v5_0_suspend,
	.resume = uvd_v5_0_resume,
	.is_idle = uvd_v5_0_is_idle,
	.रुको_क्रम_idle = uvd_v5_0_रुको_क्रम_idle,
	.soft_reset = uvd_v5_0_soft_reset,
	.set_घड़ीgating_state = uvd_v5_0_set_घड़ीgating_state,
	.set_घातergating_state = uvd_v5_0_set_घातergating_state,
	.get_घड़ीgating_state = uvd_v5_0_get_घड़ीgating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs uvd_v5_0_ring_funcs = अणु
	.type = AMDGPU_RING_TYPE_UVD,
	.align_mask = 0xf,
	.support_64bit_ptrs = false,
	.no_user_fence = true,
	.get_rptr = uvd_v5_0_ring_get_rptr,
	.get_wptr = uvd_v5_0_ring_get_wptr,
	.set_wptr = uvd_v5_0_ring_set_wptr,
	.parse_cs = amdgpu_uvd_ring_parse_cs,
	.emit_frame_size =
		14, /* uvd_v5_0_ring_emit_fence  x1 no user fence */
	.emit_ib_size = 6, /* uvd_v5_0_ring_emit_ib */
	.emit_ib = uvd_v5_0_ring_emit_ib,
	.emit_fence = uvd_v5_0_ring_emit_fence,
	.test_ring = uvd_v5_0_ring_test_ring,
	.test_ib = amdgpu_uvd_ring_test_ib,
	.insert_nop = uvd_v5_0_ring_insert_nop,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = amdgpu_uvd_ring_begin_use,
	.end_use = amdgpu_uvd_ring_end_use,
पूर्ण;

अटल व्योम uvd_v5_0_set_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->uvd.inst->ring.funcs = &uvd_v5_0_ring_funcs;
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs uvd_v5_0_irq_funcs = अणु
	.set = uvd_v5_0_set_पूर्णांकerrupt_state,
	.process = uvd_v5_0_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम uvd_v5_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->uvd.inst->irq.num_types = 1;
	adev->uvd.inst->irq.funcs = &uvd_v5_0_irq_funcs;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version uvd_v5_0_ip_block =
अणु
		.type = AMD_IP_BLOCK_TYPE_UVD,
		.major = 5,
		.minor = 0,
		.rev = 0,
		.funcs = &uvd_v5_0_ip_funcs,
पूर्ण;
