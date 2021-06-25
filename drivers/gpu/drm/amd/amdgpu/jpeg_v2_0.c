<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
 */

#समावेश "amdgpu.h"
#समावेश "amdgpu_jpeg.h"
#समावेश "amdgpu_pm.h"
#समावेश "soc15.h"
#समावेश "soc15d.h"
#समावेश "jpeg_v2_0.h"

#समावेश "vcn/vcn_2_0_0_offset.h"
#समावेश "vcn/vcn_2_0_0_sh_mask.h"
#समावेश "ivsrcid/vcn/irqsrcs_vcn_2_0.h"

#घोषणा mmUVD_JRBC_EXTERNAL_REG_INTERNAL_OFFSET				0x1bfff
#घोषणा mmUVD_JPEG_GPCOM_CMD_INTERNAL_OFFSET				0x4029
#घोषणा mmUVD_JPEG_GPCOM_DATA0_INTERNAL_OFFSET				0x402a
#घोषणा mmUVD_JPEG_GPCOM_DATA1_INTERNAL_OFFSET				0x402b
#घोषणा mmUVD_LMI_JRBC_RB_MEM_WR_64BIT_BAR_LOW_INTERNAL_OFFSET		0x40ea
#घोषणा mmUVD_LMI_JRBC_RB_MEM_WR_64BIT_BAR_HIGH_INTERNAL_OFFSET		0x40eb
#घोषणा mmUVD_LMI_JRBC_IB_VMID_INTERNAL_OFFSET				0x40cf
#घोषणा mmUVD_LMI_JPEG_VMID_INTERNAL_OFFSET				0x40d1
#घोषणा mmUVD_LMI_JRBC_IB_64BIT_BAR_LOW_INTERNAL_OFFSET			0x40e8
#घोषणा mmUVD_LMI_JRBC_IB_64BIT_BAR_HIGH_INTERNAL_OFFSET		0x40e9
#घोषणा mmUVD_JRBC_IB_SIZE_INTERNAL_OFFSET				0x4082
#घोषणा mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_LOW_INTERNAL_OFFSET		0x40ec
#घोषणा mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_HIGH_INTERNAL_OFFSET		0x40ed
#घोषणा mmUVD_JRBC_RB_COND_RD_TIMER_INTERNAL_OFFSET			0x4085
#घोषणा mmUVD_JRBC_RB_REF_DATA_INTERNAL_OFFSET				0x4084
#घोषणा mmUVD_JRBC_STATUS_INTERNAL_OFFSET				0x4089
#घोषणा mmUVD_JPEG_PITCH_INTERNAL_OFFSET				0x401f

#घोषणा JRBC_DEC_EXTERNAL_REG_WRITE_ADDR				0x18000

अटल व्योम jpeg_v2_0_set_dec_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम jpeg_v2_0_set_irq_funcs(काष्ठा amdgpu_device *adev);
अटल पूर्णांक jpeg_v2_0_set_घातergating_state(व्योम *handle,
				क्रमागत amd_घातergating_state state);

/**
 * jpeg_v2_0_early_init - set function poपूर्णांकers
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Set ring and irq function poपूर्णांकers
 */
अटल पूर्णांक jpeg_v2_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->jpeg.num_jpeg_inst = 1;

	jpeg_v2_0_set_dec_ring_funcs(adev);
	jpeg_v2_0_set_irq_funcs(adev);

	वापस 0;
पूर्ण

/**
 * jpeg_v2_0_sw_init - sw init क्रम JPEG block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Load firmware and sw initialization
 */
अटल पूर्णांक jpeg_v2_0_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा amdgpu_ring *ring;
	पूर्णांक r;

	/* JPEG TRAP */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_VCN,
		VCN_2_0__SRCID__JPEG_DECODE, &adev->jpeg.inst->irq);
	अगर (r)
		वापस r;

	r = amdgpu_jpeg_sw_init(adev);
	अगर (r)
		वापस r;

	r = amdgpu_jpeg_resume(adev);
	अगर (r)
		वापस r;

	ring = &adev->jpeg.inst->ring_dec;
	ring->use_करोorbell = true;
	ring->करोorbell_index = (adev->करोorbell_index.vcn.vcn_ring0_1 << 1) + 1;
	प्र_लिखो(ring->name, "jpeg_dec");
	r = amdgpu_ring_init(adev, ring, 512, &adev->jpeg.inst->irq,
			     0, AMDGPU_RING_PRIO_DEFAULT, शून्य);
	अगर (r)
		वापस r;

	adev->jpeg.पूर्णांकernal.jpeg_pitch = mmUVD_JPEG_PITCH_INTERNAL_OFFSET;
	adev->jpeg.inst->बाह्यal.jpeg_pitch = SOC15_REG_OFFSET(JPEG, 0, mmUVD_JPEG_PITCH);

	वापस 0;
पूर्ण

/**
 * jpeg_v2_0_sw_fini - sw fini क्रम JPEG block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * JPEG suspend and मुक्त up sw allocation
 */
अटल पूर्णांक jpeg_v2_0_sw_fini(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_jpeg_suspend(adev);
	अगर (r)
		वापस r;

	r = amdgpu_jpeg_sw_fini(adev);

	वापस r;
पूर्ण

/**
 * jpeg_v2_0_hw_init - start and test JPEG block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 */
अटल पूर्णांक jpeg_v2_0_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा amdgpu_ring *ring = &adev->jpeg.inst->ring_dec;
	पूर्णांक r;

	adev->nbio.funcs->vcn_करोorbell_range(adev, ring->use_करोorbell,
		(adev->करोorbell_index.vcn.vcn_ring0_1 << 1), 0);

	r = amdgpu_ring_test_helper(ring);
	अगर (!r)
		DRM_INFO("JPEG decode initialized successfully.\n");

	वापस r;
पूर्ण

/**
 * jpeg_v2_0_hw_fini - stop the hardware block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Stop the JPEG block, mark ring as not पढ़ोy any more
 */
अटल पूर्णांक jpeg_v2_0_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	cancel_delayed_work_sync(&adev->vcn.idle_work);

	अगर (adev->jpeg.cur_state != AMD_PG_STATE_GATE &&
	      RREG32_SOC15(JPEG, 0, mmUVD_JRBC_STATUS))
		jpeg_v2_0_set_घातergating_state(adev, AMD_PG_STATE_GATE);

	वापस 0;
पूर्ण

/**
 * jpeg_v2_0_suspend - suspend JPEG block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * HW fini and suspend JPEG block
 */
अटल पूर्णांक jpeg_v2_0_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	r = jpeg_v2_0_hw_fini(adev);
	अगर (r)
		वापस r;

	r = amdgpu_jpeg_suspend(adev);

	वापस r;
पूर्ण

/**
 * jpeg_v2_0_resume - resume JPEG block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Resume firmware and hw init JPEG block
 */
अटल पूर्णांक jpeg_v2_0_resume(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_jpeg_resume(adev);
	अगर (r)
		वापस r;

	r = jpeg_v2_0_hw_init(adev);

	वापस r;
पूर्ण

अटल पूर्णांक jpeg_v2_0_disable_घातer_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data;
	पूर्णांक r = 0;

	अगर (adev->pg_flags & AMD_PG_SUPPORT_JPEG) अणु
		data = 1 << UVD_PGFSM_CONFIG__UVDJ_PWR_CONFIG__SHIFT;
		WREG32(SOC15_REG_OFFSET(JPEG, 0, mmUVD_PGFSM_CONFIG), data);

		r = SOC15_WAIT_ON_RREG(JPEG, 0,
			mmUVD_PGFSM_STATUS, UVD_PGFSM_STATUS_UVDJ_PWR_ON,
			UVD_PGFSM_STATUS__UVDJ_PWR_STATUS_MASK);

		अगर (r) अणु
			DRM_ERROR("amdgpu: JPEG disable power gating failed\n");
			वापस r;
		पूर्ण
	पूर्ण

	/* Removing the anti hang mechanism to indicate the UVDJ tile is ON */
	data = RREG32(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JPEG_POWER_STATUS)) & ~0x1;
	WREG32(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JPEG_POWER_STATUS), data);

	वापस 0;
पूर्ण

अटल पूर्णांक jpeg_v2_0_enable_घातer_gating(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->pg_flags & AMD_PG_SUPPORT_JPEG) अणु
		uपूर्णांक32_t data;
		पूर्णांक r = 0;

		data = RREG32(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JPEG_POWER_STATUS));
		data &= ~UVD_JPEG_POWER_STATUS__JPEG_POWER_STATUS_MASK;
		data |=  0x1; //UVD_JPEG_POWER_STATUS__JPEG_POWER_STATUS_TILES_OFF;
		WREG32(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JPEG_POWER_STATUS), data);

		data = 2 << UVD_PGFSM_CONFIG__UVDJ_PWR_CONFIG__SHIFT;
		WREG32(SOC15_REG_OFFSET(JPEG, 0, mmUVD_PGFSM_CONFIG), data);

		r = SOC15_WAIT_ON_RREG(JPEG, 0, mmUVD_PGFSM_STATUS,
			(2 << UVD_PGFSM_STATUS__UVDJ_PWR_STATUS__SHIFT),
			UVD_PGFSM_STATUS__UVDJ_PWR_STATUS_MASK);

		अगर (r) अणु
			DRM_ERROR("amdgpu: JPEG enable power gating failed\n");
			वापस r;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम jpeg_v2_0_disable_घड़ी_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data;

	data = RREG32_SOC15(JPEG, 0, mmJPEG_CGC_CTRL);
	अगर (adev->cg_flags & AMD_CG_SUPPORT_JPEG_MGCG)
		data |= 1 << JPEG_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
	अन्यथा
		data &= ~JPEG_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;

	data |= 1 << JPEG_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT;
	data |= 4 << JPEG_CGC_CTRL__CLK_OFF_DELAY__SHIFT;
	WREG32_SOC15(JPEG, 0, mmJPEG_CGC_CTRL, data);

	data = RREG32_SOC15(JPEG, 0, mmJPEG_CGC_GATE);
	data &= ~(JPEG_CGC_GATE__JPEG_DEC_MASK
		| JPEG_CGC_GATE__JPEG2_DEC_MASK
		| JPEG_CGC_GATE__JPEG_ENC_MASK
		| JPEG_CGC_GATE__JMCIF_MASK
		| JPEG_CGC_GATE__JRBBM_MASK);
	WREG32_SOC15(JPEG, 0, mmJPEG_CGC_GATE, data);
पूर्ण

अटल व्योम jpeg_v2_0_enable_घड़ी_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data;

	data = RREG32_SOC15(JPEG, 0, mmJPEG_CGC_CTRL);
	अगर (adev->cg_flags & AMD_CG_SUPPORT_JPEG_MGCG)
		data |= 1 << JPEG_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
	अन्यथा
		data |= 0 << JPEG_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;

	data |= 1 << JPEG_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT;
	data |= 4 << JPEG_CGC_CTRL__CLK_OFF_DELAY__SHIFT;
	WREG32_SOC15(JPEG, 0, mmJPEG_CGC_CTRL, data);

	data = RREG32_SOC15(JPEG, 0, mmJPEG_CGC_GATE);
	data |= (JPEG_CGC_GATE__JPEG_DEC_MASK
		|JPEG_CGC_GATE__JPEG2_DEC_MASK
		|JPEG_CGC_GATE__JPEG_ENC_MASK
		|JPEG_CGC_GATE__JMCIF_MASK
		|JPEG_CGC_GATE__JRBBM_MASK);
	WREG32_SOC15(JPEG, 0, mmJPEG_CGC_GATE, data);
पूर्ण

/**
 * jpeg_v2_0_start - start JPEG block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Setup and start the JPEG block
 */
अटल पूर्णांक jpeg_v2_0_start(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring = &adev->jpeg.inst->ring_dec;
	पूर्णांक r;

	अगर (adev->pm.dpm_enabled)
		amdgpu_dpm_enable_jpeg(adev, true);

	/* disable घातer gating */
	r = jpeg_v2_0_disable_घातer_gating(adev);
	अगर (r)
		वापस r;

	/* JPEG disable CGC */
	jpeg_v2_0_disable_घड़ी_gating(adev);

	WREG32_SOC15(JPEG, 0, mmJPEG_DEC_GFX10_ADDR_CONFIG, adev->gfx.config.gb_addr_config);

	/* enable JMI channel */
	WREG32_P(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JMI_CNTL), 0,
		~UVD_JMI_CNTL__SOFT_RESET_MASK);

	/* enable System Interrupt क्रम JRBC */
	WREG32_P(SOC15_REG_OFFSET(JPEG, 0, mmJPEG_SYS_INT_EN),
		JPEG_SYS_INT_EN__DJRBC_MASK,
		~JPEG_SYS_INT_EN__DJRBC_MASK);

	WREG32_SOC15(JPEG, 0, mmUVD_LMI_JRBC_RB_VMID, 0);
	WREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_CNTL, (0x00000001L | 0x00000002L));
	WREG32_SOC15(JPEG, 0, mmUVD_LMI_JRBC_RB_64BIT_BAR_LOW,
		lower_32_bits(ring->gpu_addr));
	WREG32_SOC15(JPEG, 0, mmUVD_LMI_JRBC_RB_64BIT_BAR_HIGH,
		upper_32_bits(ring->gpu_addr));
	WREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_RPTR, 0);
	WREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_WPTR, 0);
	WREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_CNTL, 0x00000002L);
	WREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_SIZE, ring->ring_size / 4);
	ring->wptr = RREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_WPTR);

	वापस 0;
पूर्ण

/**
 * jpeg_v2_0_stop - stop JPEG block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * stop the JPEG block
 */
अटल पूर्णांक jpeg_v2_0_stop(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	/* reset JMI */
	WREG32_P(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JMI_CNTL),
		UVD_JMI_CNTL__SOFT_RESET_MASK,
		~UVD_JMI_CNTL__SOFT_RESET_MASK);

	/* enable JPEG CGC */
	jpeg_v2_0_enable_घड़ी_gating(adev);

	/* enable घातer gating */
	r = jpeg_v2_0_enable_घातer_gating(adev);
	अगर (r)
		वापस r;

	अगर (adev->pm.dpm_enabled)
		amdgpu_dpm_enable_jpeg(adev, false);

	वापस 0;
पूर्ण

/**
 * jpeg_v2_0_dec_ring_get_rptr - get पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t jpeg_v2_0_dec_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_RPTR);
पूर्ण

/**
 * jpeg_v2_0_dec_ring_get_wptr - get ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t jpeg_v2_0_dec_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->use_करोorbell)
		वापस adev->wb.wb[ring->wptr_offs];
	अन्यथा
		वापस RREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_WPTR);
पूर्ण

/**
 * jpeg_v2_0_dec_ring_set_wptr - set ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम jpeg_v2_0_dec_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->use_करोorbell) अणु
		adev->wb.wb[ring->wptr_offs] = lower_32_bits(ring->wptr);
		WDOORBELL32(ring->करोorbell_index, lower_32_bits(ring->wptr));
	पूर्ण अन्यथा अणु
		WREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_WPTR, lower_32_bits(ring->wptr));
	पूर्ण
पूर्ण

/**
 * jpeg_v2_0_dec_ring_insert_start - insert a start command
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Write a start command to the ring.
 */
व्योम jpeg_v2_0_dec_ring_insert_start(काष्ठा amdgpu_ring *ring)
अणु
	amdgpu_ring_ग_लिखो(ring, PACKETJ(mmUVD_JRBC_EXTERNAL_REG_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x68e04);

	amdgpu_ring_ग_लिखो(ring, PACKETJ(JRBC_DEC_EXTERNAL_REG_WRITE_ADDR,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x80010000);
पूर्ण

/**
 * jpeg_v2_0_dec_ring_insert_end - insert a end command
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Write a end command to the ring.
 */
व्योम jpeg_v2_0_dec_ring_insert_end(काष्ठा amdgpu_ring *ring)
अणु
	amdgpu_ring_ग_लिखो(ring, PACKETJ(mmUVD_JRBC_EXTERNAL_REG_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x68e04);

	amdgpu_ring_ग_लिखो(ring, PACKETJ(JRBC_DEC_EXTERNAL_REG_WRITE_ADDR,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x00010000);
पूर्ण

/**
 * jpeg_v2_0_dec_ring_emit_fence - emit an fence & trap command
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @addr: address
 * @seq: sequence number
 * @flags: fence related flags
 *
 * Write a fence and a trap command to the ring.
 */
व्योम jpeg_v2_0_dec_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr, u64 seq,
				अचिन्हित flags)
अणु
	WARN_ON(flags & AMDGPU_FENCE_FLAG_64BIT);

	amdgpu_ring_ग_लिखो(ring, PACKETJ(mmUVD_JPEG_GPCOM_DATA0_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, seq);

	amdgpu_ring_ग_लिखो(ring,	PACKETJ(mmUVD_JPEG_GPCOM_DATA1_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, seq);

	amdgpu_ring_ग_लिखो(ring,	PACKETJ(mmUVD_LMI_JRBC_RB_MEM_WR_64BIT_BAR_LOW_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(addr));

	amdgpu_ring_ग_लिखो(ring,	PACKETJ(mmUVD_LMI_JRBC_RB_MEM_WR_64BIT_BAR_HIGH_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));

	amdgpu_ring_ग_लिखो(ring,	PACKETJ(mmUVD_JPEG_GPCOM_CMD_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x8);

	amdgpu_ring_ग_लिखो(ring,	PACKETJ(mmUVD_JPEG_GPCOM_CMD_INTERNAL_OFFSET,
		0, PACKETJ_CONDITION_CHECK0, PACKETJ_TYPE4));
	amdgpu_ring_ग_लिखो(ring, 0);

	amdgpu_ring_ग_लिखो(ring,	PACKETJ(mmUVD_JRBC_EXTERNAL_REG_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x3fbc);

	amdgpu_ring_ग_लिखो(ring, PACKETJ(JRBC_DEC_EXTERNAL_REG_WRITE_ADDR,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x1);

	amdgpu_ring_ग_लिखो(ring, PACKETJ(0, 0, 0, PACKETJ_TYPE7));
	amdgpu_ring_ग_लिखो(ring, 0);
पूर्ण

/**
 * jpeg_v2_0_dec_ring_emit_ib - execute indirect buffer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @job: job to retrieve vmid from
 * @ib: indirect buffer to execute
 * @flags: unused
 *
 * Write ring commands to execute the indirect buffer.
 */
व्योम jpeg_v2_0_dec_ring_emit_ib(काष्ठा amdgpu_ring *ring,
				काष्ठा amdgpu_job *job,
				काष्ठा amdgpu_ib *ib,
				uपूर्णांक32_t flags)
अणु
	अचिन्हित vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_ring_ग_लिखो(ring, PACKETJ(mmUVD_LMI_JRBC_IB_VMID_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, (vmid | (vmid << 4)));

	amdgpu_ring_ग_लिखो(ring, PACKETJ(mmUVD_LMI_JPEG_VMID_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, (vmid | (vmid << 4)));

	amdgpu_ring_ग_लिखो(ring,	PACKETJ(mmUVD_LMI_JRBC_IB_64BIT_BAR_LOW_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ib->gpu_addr));

	amdgpu_ring_ग_लिखो(ring,	PACKETJ(mmUVD_LMI_JRBC_IB_64BIT_BAR_HIGH_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr));

	amdgpu_ring_ग_लिखो(ring,	PACKETJ(mmUVD_JRBC_IB_SIZE_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, ib->length_dw);

	amdgpu_ring_ग_लिखो(ring,	PACKETJ(mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_LOW_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ring->gpu_addr));

	amdgpu_ring_ग_लिखो(ring,	PACKETJ(mmUVD_LMI_JRBC_RB_MEM_RD_64BIT_BAR_HIGH_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ring->gpu_addr));

	amdgpu_ring_ग_लिखो(ring,	PACKETJ(0, 0, PACKETJ_CONDITION_CHECK0, PACKETJ_TYPE2));
	amdgpu_ring_ग_लिखो(ring, 0);

	amdgpu_ring_ग_लिखो(ring,	PACKETJ(mmUVD_JRBC_RB_COND_RD_TIMER_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x01400200);

	amdgpu_ring_ग_लिखो(ring, PACKETJ(mmUVD_JRBC_RB_REF_DATA_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x2);

	amdgpu_ring_ग_लिखो(ring,	PACKETJ(mmUVD_JRBC_STATUS_INTERNAL_OFFSET,
		0, PACKETJ_CONDITION_CHECK3, PACKETJ_TYPE3));
	amdgpu_ring_ग_लिखो(ring, 0x2);
पूर्ण

व्योम jpeg_v2_0_dec_ring_emit_reg_रुको(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t reg,
				uपूर्णांक32_t val, uपूर्णांक32_t mask)
अणु
	uपूर्णांक32_t reg_offset = (reg << 2);

	amdgpu_ring_ग_लिखो(ring, PACKETJ(mmUVD_JRBC_RB_COND_RD_TIMER_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, 0x01400200);

	amdgpu_ring_ग_लिखो(ring,	PACKETJ(mmUVD_JRBC_RB_REF_DATA_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	amdgpu_ring_ग_लिखो(ring, val);

	amdgpu_ring_ग_लिखो(ring, PACKETJ(mmUVD_JRBC_EXTERNAL_REG_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	अगर (reg_offset >= 0x10000 && reg_offset <= 0x105ff) अणु
		amdgpu_ring_ग_लिखो(ring, 0);
		amdgpu_ring_ग_लिखो(ring,
			PACKETJ((reg_offset >> 2), 0, 0, PACKETJ_TYPE3));
	पूर्ण अन्यथा अणु
		amdgpu_ring_ग_लिखो(ring, reg_offset);
		amdgpu_ring_ग_लिखो(ring,	PACKETJ(JRBC_DEC_EXTERNAL_REG_WRITE_ADDR,
			0, 0, PACKETJ_TYPE3));
	पूर्ण
	amdgpu_ring_ग_लिखो(ring, mask);
पूर्ण

व्योम jpeg_v2_0_dec_ring_emit_vm_flush(काष्ठा amdgpu_ring *ring,
				अचिन्हित vmid, uपूर्णांक64_t pd_addr)
अणु
	काष्ठा amdgpu_vmhub *hub = &ring->adev->vmhub[ring->funcs->vmhub];
	uपूर्णांक32_t data0, data1, mask;

	pd_addr = amdgpu_gmc_emit_flush_gpu_tlb(ring, vmid, pd_addr);

	/* रुको क्रम रेजिस्टर ग_लिखो */
	data0 = hub->ctx0_ptb_addr_lo32 + vmid * hub->ctx_addr_distance;
	data1 = lower_32_bits(pd_addr);
	mask = 0xffffffff;
	jpeg_v2_0_dec_ring_emit_reg_रुको(ring, data0, data1, mask);
पूर्ण

व्योम jpeg_v2_0_dec_ring_emit_wreg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	uपूर्णांक32_t reg_offset = (reg << 2);

	amdgpu_ring_ग_लिखो(ring,	PACKETJ(mmUVD_JRBC_EXTERNAL_REG_INTERNAL_OFFSET,
		0, 0, PACKETJ_TYPE0));
	अगर (reg_offset >= 0x10000 && reg_offset <= 0x105ff) अणु
		amdgpu_ring_ग_लिखो(ring, 0);
		amdgpu_ring_ग_लिखो(ring,
			PACKETJ((reg_offset >> 2), 0, 0, PACKETJ_TYPE0));
	पूर्ण अन्यथा अणु
		amdgpu_ring_ग_लिखो(ring, reg_offset);
		amdgpu_ring_ग_लिखो(ring,	PACKETJ(JRBC_DEC_EXTERNAL_REG_WRITE_ADDR,
			0, 0, PACKETJ_TYPE0));
	पूर्ण
	amdgpu_ring_ग_लिखो(ring, val);
पूर्ण

व्योम jpeg_v2_0_dec_ring_nop(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t count)
अणु
	पूर्णांक i;

	WARN_ON(ring->wptr % 2 || count % 2);

	क्रम (i = 0; i < count / 2; i++) अणु
		amdgpu_ring_ग_लिखो(ring, PACKETJ(0, 0, 0, PACKETJ_TYPE6));
		amdgpu_ring_ग_लिखो(ring, 0);
	पूर्ण
पूर्ण

अटल bool jpeg_v2_0_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस ((RREG32_SOC15(JPEG, 0, mmUVD_JRBC_STATUS) &
		UVD_JRBC_STATUS__RB_JOB_DONE_MASK) ==
		UVD_JRBC_STATUS__RB_JOB_DONE_MASK);
पूर्ण

अटल पूर्णांक jpeg_v2_0_रुको_क्रम_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक ret;

	ret = SOC15_WAIT_ON_RREG(JPEG, 0, mmUVD_JRBC_STATUS, UVD_JRBC_STATUS__RB_JOB_DONE_MASK,
		UVD_JRBC_STATUS__RB_JOB_DONE_MASK);

	वापस ret;
पूर्ण

अटल पूर्णांक jpeg_v2_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	bool enable = (state == AMD_CG_STATE_GATE);

	अगर (enable) अणु
		अगर (!jpeg_v2_0_is_idle(handle))
			वापस -EBUSY;
		jpeg_v2_0_enable_घड़ी_gating(adev);
	पूर्ण अन्यथा अणु
		jpeg_v2_0_disable_घड़ी_gating(adev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jpeg_v2_0_set_घातergating_state(व्योम *handle,
					क्रमागत amd_घातergating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक ret;

	अगर (state == adev->jpeg.cur_state)
		वापस 0;

	अगर (state == AMD_PG_STATE_GATE)
		ret = jpeg_v2_0_stop(adev);
	अन्यथा
		ret = jpeg_v2_0_start(adev);

	अगर (!ret)
		adev->jpeg.cur_state = state;

	वापस ret;
पूर्ण

अटल पूर्णांक jpeg_v2_0_set_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक jpeg_v2_0_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	DRM_DEBUG("IH: JPEG TRAP\n");

	चयन (entry->src_id) अणु
	हाल VCN_2_0__SRCID__JPEG_DECODE:
		amdgpu_fence_process(&adev->jpeg.inst->ring_dec);
		अवरोध;
	शेष:
		DRM_ERROR("Unhandled interrupt: %d %d\n",
			  entry->src_id, entry->src_data[0]);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs jpeg_v2_0_ip_funcs = अणु
	.name = "jpeg_v2_0",
	.early_init = jpeg_v2_0_early_init,
	.late_init = शून्य,
	.sw_init = jpeg_v2_0_sw_init,
	.sw_fini = jpeg_v2_0_sw_fini,
	.hw_init = jpeg_v2_0_hw_init,
	.hw_fini = jpeg_v2_0_hw_fini,
	.suspend = jpeg_v2_0_suspend,
	.resume = jpeg_v2_0_resume,
	.is_idle = jpeg_v2_0_is_idle,
	.रुको_क्रम_idle = jpeg_v2_0_रुको_क्रम_idle,
	.check_soft_reset = शून्य,
	.pre_soft_reset = शून्य,
	.soft_reset = शून्य,
	.post_soft_reset = शून्य,
	.set_घड़ीgating_state = jpeg_v2_0_set_घड़ीgating_state,
	.set_घातergating_state = jpeg_v2_0_set_घातergating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs jpeg_v2_0_dec_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_VCN_JPEG,
	.align_mask = 0xf,
	.vmhub = AMDGPU_MMHUB_0,
	.get_rptr = jpeg_v2_0_dec_ring_get_rptr,
	.get_wptr = jpeg_v2_0_dec_ring_get_wptr,
	.set_wptr = jpeg_v2_0_dec_ring_set_wptr,
	.emit_frame_size =
		SOC15_FLUSH_GPU_TLB_NUM_WREG * 6 +
		SOC15_FLUSH_GPU_TLB_NUM_REG_WAIT * 8 +
		8 + /* jpeg_v2_0_dec_ring_emit_vm_flush */
		18 + 18 + /* jpeg_v2_0_dec_ring_emit_fence x2 vm fence */
		8 + 16,
	.emit_ib_size = 22, /* jpeg_v2_0_dec_ring_emit_ib */
	.emit_ib = jpeg_v2_0_dec_ring_emit_ib,
	.emit_fence = jpeg_v2_0_dec_ring_emit_fence,
	.emit_vm_flush = jpeg_v2_0_dec_ring_emit_vm_flush,
	.test_ring = amdgpu_jpeg_dec_ring_test_ring,
	.test_ib = amdgpu_jpeg_dec_ring_test_ib,
	.insert_nop = jpeg_v2_0_dec_ring_nop,
	.insert_start = jpeg_v2_0_dec_ring_insert_start,
	.insert_end = jpeg_v2_0_dec_ring_insert_end,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = amdgpu_jpeg_ring_begin_use,
	.end_use = amdgpu_jpeg_ring_end_use,
	.emit_wreg = jpeg_v2_0_dec_ring_emit_wreg,
	.emit_reg_रुको = jpeg_v2_0_dec_ring_emit_reg_रुको,
	.emit_reg_ग_लिखो_reg_रुको = amdgpu_ring_emit_reg_ग_लिखो_reg_रुको_helper,
पूर्ण;

अटल व्योम jpeg_v2_0_set_dec_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->jpeg.inst->ring_dec.funcs = &jpeg_v2_0_dec_ring_vm_funcs;
	DRM_INFO("JPEG decode is enabled in VM mode\n");
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs jpeg_v2_0_irq_funcs = अणु
	.set = jpeg_v2_0_set_पूर्णांकerrupt_state,
	.process = jpeg_v2_0_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम jpeg_v2_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->jpeg.inst->irq.num_types = 1;
	adev->jpeg.inst->irq.funcs = &jpeg_v2_0_irq_funcs;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version jpeg_v2_0_ip_block =
अणु
		.type = AMD_IP_BLOCK_TYPE_JPEG,
		.major = 2,
		.minor = 0,
		.rev = 0,
		.funcs = &jpeg_v2_0_ip_funcs,
पूर्ण;
