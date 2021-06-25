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

#समावेश "vcn/vcn_3_0_0_offset.h"
#समावेश "vcn/vcn_3_0_0_sh_mask.h"
#समावेश "ivsrcid/vcn/irqsrcs_vcn_2_0.h"

#घोषणा mmUVD_JPEG_PITCH_INTERNAL_OFFSET	0x401f

अटल व्योम jpeg_v3_0_set_dec_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम jpeg_v3_0_set_irq_funcs(काष्ठा amdgpu_device *adev);
अटल पूर्णांक jpeg_v3_0_set_घातergating_state(व्योम *handle,
				क्रमागत amd_घातergating_state state);

/**
 * jpeg_v3_0_early_init - set function poपूर्णांकers
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Set ring and irq function poपूर्णांकers
 */
अटल पूर्णांक jpeg_v3_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 harvest = RREG32_SOC15(JPEG, 0, mmCC_UVD_HARVESTING);

	अगर (harvest & CC_UVD_HARVESTING__UVD_DISABLE_MASK)
		वापस -ENOENT;

	adev->jpeg.num_jpeg_inst = 1;

	jpeg_v3_0_set_dec_ring_funcs(adev);
	jpeg_v3_0_set_irq_funcs(adev);

	वापस 0;
पूर्ण

/**
 * jpeg_v3_0_sw_init - sw init क्रम JPEG block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Load firmware and sw initialization
 */
अटल पूर्णांक jpeg_v3_0_sw_init(व्योम *handle)
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
	r = amdgpu_ring_init(adev, ring, 512, &adev->jpeg.inst->irq, 0,
			     AMDGPU_RING_PRIO_DEFAULT, शून्य);
	अगर (r)
		वापस r;

	adev->jpeg.पूर्णांकernal.jpeg_pitch = mmUVD_JPEG_PITCH_INTERNAL_OFFSET;
	adev->jpeg.inst->बाह्यal.jpeg_pitch = SOC15_REG_OFFSET(JPEG, 0, mmUVD_JPEG_PITCH);

	वापस 0;
पूर्ण

/**
 * jpeg_v3_0_sw_fini - sw fini क्रम JPEG block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * JPEG suspend and मुक्त up sw allocation
 */
अटल पूर्णांक jpeg_v3_0_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	r = amdgpu_jpeg_suspend(adev);
	अगर (r)
		वापस r;

	r = amdgpu_jpeg_sw_fini(adev);

	वापस r;
पूर्ण

/**
 * jpeg_v3_0_hw_init - start and test JPEG block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 */
अटल पूर्णांक jpeg_v3_0_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा amdgpu_ring *ring = &adev->jpeg.inst->ring_dec;
	पूर्णांक r;

	adev->nbio.funcs->vcn_करोorbell_range(adev, ring->use_करोorbell,
		(adev->करोorbell_index.vcn.vcn_ring0_1 << 1), 0);

	r = amdgpu_ring_test_helper(ring);
	अगर (r)
		वापस r;

	DRM_INFO("JPEG decode initialized successfully.\n");

	वापस 0;
पूर्ण

/**
 * jpeg_v3_0_hw_fini - stop the hardware block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Stop the JPEG block, mark ring as not पढ़ोy any more
 */
अटल पूर्णांक jpeg_v3_0_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	cancel_delayed_work_sync(&adev->vcn.idle_work);

	अगर (adev->jpeg.cur_state != AMD_PG_STATE_GATE &&
	      RREG32_SOC15(JPEG, 0, mmUVD_JRBC_STATUS))
		jpeg_v3_0_set_घातergating_state(adev, AMD_PG_STATE_GATE);

	वापस 0;
पूर्ण

/**
 * jpeg_v3_0_suspend - suspend JPEG block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * HW fini and suspend JPEG block
 */
अटल पूर्णांक jpeg_v3_0_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	r = jpeg_v3_0_hw_fini(adev);
	अगर (r)
		वापस r;

	r = amdgpu_jpeg_suspend(adev);

	वापस r;
पूर्ण

/**
 * jpeg_v3_0_resume - resume JPEG block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Resume firmware and hw init JPEG block
 */
अटल पूर्णांक jpeg_v3_0_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	r = amdgpu_jpeg_resume(adev);
	अगर (r)
		वापस r;

	r = jpeg_v3_0_hw_init(adev);

	वापस r;
पूर्ण

अटल व्योम jpeg_v3_0_disable_घड़ी_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data = 0;

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

	data = RREG32_SOC15(JPEG, 0, mmJPEG_CGC_CTRL);
	data &= ~(JPEG_CGC_CTRL__JPEG_DEC_MODE_MASK
		| JPEG_CGC_CTRL__JPEG2_DEC_MODE_MASK
		| JPEG_CGC_CTRL__JMCIF_MODE_MASK
		| JPEG_CGC_CTRL__JRBBM_MODE_MASK);
	WREG32_SOC15(JPEG, 0, mmJPEG_CGC_CTRL, data);
पूर्ण

अटल व्योम jpeg_v3_0_enable_घड़ी_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data = 0;

	data = RREG32_SOC15(JPEG, 0, mmJPEG_CGC_GATE);
	data |= (JPEG_CGC_GATE__JPEG_DEC_MASK
		|JPEG_CGC_GATE__JPEG2_DEC_MASK
		|JPEG_CGC_GATE__JPEG_ENC_MASK
		|JPEG_CGC_GATE__JMCIF_MASK
		|JPEG_CGC_GATE__JRBBM_MASK);
	WREG32_SOC15(JPEG, 0, mmJPEG_CGC_GATE, data);
पूर्ण

अटल पूर्णांक jpeg_v3_0_disable_अटल_घातer_gating(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->pg_flags & AMD_PG_SUPPORT_JPEG) अणु
		uपूर्णांक32_t data = 0;
		पूर्णांक r = 0;

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

	/* disable anti hang mechanism */
	WREG32_P(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JPEG_POWER_STATUS), 0,
		~UVD_JPEG_POWER_STATUS__JPEG_POWER_STATUS_MASK);

	/* keep the JPEG in अटल PG mode */
	WREG32_P(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JPEG_POWER_STATUS), 0,
		~UVD_JPEG_POWER_STATUS__JPEG_PG_MODE_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक jpeg_v3_0_enable_अटल_घातer_gating(काष्ठा amdgpu_device *adev)
अणु
	/* enable anti hang mechanism */
	WREG32_P(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JPEG_POWER_STATUS),
		UVD_JPEG_POWER_STATUS__JPEG_POWER_STATUS_MASK,
		~UVD_JPEG_POWER_STATUS__JPEG_POWER_STATUS_MASK);

	अगर (adev->pg_flags & AMD_PG_SUPPORT_JPEG) अणु
		uपूर्णांक32_t data = 0;
		पूर्णांक r = 0;

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

/**
 * jpeg_v3_0_start - start JPEG block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Setup and start the JPEG block
 */
अटल पूर्णांक jpeg_v3_0_start(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring = &adev->jpeg.inst->ring_dec;
	पूर्णांक r;

	अगर (adev->pm.dpm_enabled)
		amdgpu_dpm_enable_jpeg(adev, true);

	/* disable घातer gating */
	r = jpeg_v3_0_disable_अटल_घातer_gating(adev);
	अगर (r)
		वापस r;

	/* JPEG disable CGC */
	jpeg_v3_0_disable_घड़ी_gating(adev);

	/* MJPEG global tiling रेजिस्टरs */
	WREG32_SOC15(JPEG, 0, mmJPEG_DEC_GFX10_ADDR_CONFIG,
		adev->gfx.config.gb_addr_config);
	WREG32_SOC15(JPEG, 0, mmJPEG_ENC_GFX10_ADDR_CONFIG,
		adev->gfx.config.gb_addr_config);

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
 * jpeg_v3_0_stop - stop JPEG block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * stop the JPEG block
 */
अटल पूर्णांक jpeg_v3_0_stop(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	/* reset JMI */
	WREG32_P(SOC15_REG_OFFSET(JPEG, 0, mmUVD_JMI_CNTL),
		UVD_JMI_CNTL__SOFT_RESET_MASK,
		~UVD_JMI_CNTL__SOFT_RESET_MASK);

	jpeg_v3_0_enable_घड़ी_gating(adev);

	/* enable घातer gating */
	r = jpeg_v3_0_enable_अटल_घातer_gating(adev);
	अगर (r)
		वापस r;

	अगर (adev->pm.dpm_enabled)
		amdgpu_dpm_enable_jpeg(adev, false);

	वापस 0;
पूर्ण

/**
 * jpeg_v3_0_dec_ring_get_rptr - get पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t jpeg_v3_0_dec_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_RPTR);
पूर्ण

/**
 * jpeg_v3_0_dec_ring_get_wptr - get ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t jpeg_v3_0_dec_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->use_करोorbell)
		वापस adev->wb.wb[ring->wptr_offs];
	अन्यथा
		वापस RREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_WPTR);
पूर्ण

/**
 * jpeg_v3_0_dec_ring_set_wptr - set ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम jpeg_v3_0_dec_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->use_करोorbell) अणु
		adev->wb.wb[ring->wptr_offs] = lower_32_bits(ring->wptr);
		WDOORBELL32(ring->करोorbell_index, lower_32_bits(ring->wptr));
	पूर्ण अन्यथा अणु
		WREG32_SOC15(JPEG, 0, mmUVD_JRBC_RB_WPTR, lower_32_bits(ring->wptr));
	पूर्ण
पूर्ण

अटल bool jpeg_v3_0_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक ret = 1;

	ret &= (((RREG32_SOC15(JPEG, 0, mmUVD_JRBC_STATUS) &
		UVD_JRBC_STATUS__RB_JOB_DONE_MASK) ==
		UVD_JRBC_STATUS__RB_JOB_DONE_MASK));

	वापस ret;
पूर्ण

अटल पूर्णांक jpeg_v3_0_रुको_क्रम_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस SOC15_WAIT_ON_RREG(JPEG, 0, mmUVD_JRBC_STATUS,
		UVD_JRBC_STATUS__RB_JOB_DONE_MASK,
		UVD_JRBC_STATUS__RB_JOB_DONE_MASK);
पूर्ण

अटल पूर्णांक jpeg_v3_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	bool enable = (state == AMD_CG_STATE_GATE) ? true : false;

	अगर (enable) अणु
		अगर (!jpeg_v3_0_is_idle(handle))
			वापस -EBUSY;
		jpeg_v3_0_enable_घड़ी_gating(adev);
	पूर्ण अन्यथा अणु
		jpeg_v3_0_disable_घड़ी_gating(adev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jpeg_v3_0_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक ret;

	अगर(state == adev->jpeg.cur_state)
		वापस 0;

	अगर (state == AMD_PG_STATE_GATE)
		ret = jpeg_v3_0_stop(adev);
	अन्यथा
		ret = jpeg_v3_0_start(adev);

	अगर(!ret)
		adev->jpeg.cur_state = state;

	वापस ret;
पूर्ण

अटल पूर्णांक jpeg_v3_0_set_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक jpeg_v3_0_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
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

अटल स्थिर काष्ठा amd_ip_funcs jpeg_v3_0_ip_funcs = अणु
	.name = "jpeg_v3_0",
	.early_init = jpeg_v3_0_early_init,
	.late_init = शून्य,
	.sw_init = jpeg_v3_0_sw_init,
	.sw_fini = jpeg_v3_0_sw_fini,
	.hw_init = jpeg_v3_0_hw_init,
	.hw_fini = jpeg_v3_0_hw_fini,
	.suspend = jpeg_v3_0_suspend,
	.resume = jpeg_v3_0_resume,
	.is_idle = jpeg_v3_0_is_idle,
	.रुको_क्रम_idle = jpeg_v3_0_रुको_क्रम_idle,
	.check_soft_reset = शून्य,
	.pre_soft_reset = शून्य,
	.soft_reset = शून्य,
	.post_soft_reset = शून्य,
	.set_घड़ीgating_state = jpeg_v3_0_set_घड़ीgating_state,
	.set_घातergating_state = jpeg_v3_0_set_घातergating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs jpeg_v3_0_dec_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_VCN_JPEG,
	.align_mask = 0xf,
	.vmhub = AMDGPU_MMHUB_0,
	.get_rptr = jpeg_v3_0_dec_ring_get_rptr,
	.get_wptr = jpeg_v3_0_dec_ring_get_wptr,
	.set_wptr = jpeg_v3_0_dec_ring_set_wptr,
	.emit_frame_size =
		SOC15_FLUSH_GPU_TLB_NUM_WREG * 6 +
		SOC15_FLUSH_GPU_TLB_NUM_REG_WAIT * 8 +
		8 + /* jpeg_v3_0_dec_ring_emit_vm_flush */
		18 + 18 + /* jpeg_v3_0_dec_ring_emit_fence x2 vm fence */
		8 + 16,
	.emit_ib_size = 22, /* jpeg_v3_0_dec_ring_emit_ib */
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

अटल व्योम jpeg_v3_0_set_dec_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->jpeg.inst->ring_dec.funcs = &jpeg_v3_0_dec_ring_vm_funcs;
	DRM_INFO("JPEG decode is enabled in VM mode\n");
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs jpeg_v3_0_irq_funcs = अणु
	.set = jpeg_v3_0_set_पूर्णांकerrupt_state,
	.process = jpeg_v3_0_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम jpeg_v3_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->jpeg.inst->irq.num_types = 1;
	adev->jpeg.inst->irq.funcs = &jpeg_v3_0_irq_funcs;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version jpeg_v3_0_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_JPEG,
	.major = 3,
	.minor = 0,
	.rev = 0,
	.funcs = &jpeg_v3_0_ip_funcs,
पूर्ण;
