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
#समावेश "soc15.h"
#समावेश "soc15d.h"
#समावेश "jpeg_v2_0.h"

#समावेश "vcn/vcn_2_5_offset.h"
#समावेश "vcn/vcn_2_5_sh_mask.h"
#समावेश "ivsrcid/vcn/irqsrcs_vcn_2_0.h"

#घोषणा mmUVD_JPEG_PITCH_INTERNAL_OFFSET			0x401f

#घोषणा JPEG25_MAX_HW_INSTANCES_ARCTURUS			2

अटल व्योम jpeg_v2_5_set_dec_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम jpeg_v2_5_set_irq_funcs(काष्ठा amdgpu_device *adev);
अटल पूर्णांक jpeg_v2_5_set_घातergating_state(व्योम *handle,
				क्रमागत amd_घातergating_state state);

अटल पूर्णांक amdgpu_ih_clientid_jpeg[] = अणु
	SOC15_IH_CLIENTID_VCN,
	SOC15_IH_CLIENTID_VCN1
पूर्ण;

/**
 * jpeg_v2_5_early_init - set function poपूर्णांकers
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Set ring and irq function poपूर्णांकers
 */
अटल पूर्णांक jpeg_v2_5_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 harvest;
	पूर्णांक i;

	adev->jpeg.num_jpeg_inst = JPEG25_MAX_HW_INSTANCES_ARCTURUS;
	क्रम (i = 0; i < adev->jpeg.num_jpeg_inst; i++) अणु
		harvest = RREG32_SOC15(JPEG, i, mmCC_UVD_HARVESTING);
		अगर (harvest & CC_UVD_HARVESTING__UVD_DISABLE_MASK)
			adev->jpeg.harvest_config |= 1 << i;
	पूर्ण
	अगर (adev->jpeg.harvest_config == (AMDGPU_JPEG_HARVEST_JPEG0 |
					 AMDGPU_JPEG_HARVEST_JPEG1))
		वापस -ENOENT;

	jpeg_v2_5_set_dec_ring_funcs(adev);
	jpeg_v2_5_set_irq_funcs(adev);

	वापस 0;
पूर्ण

/**
 * jpeg_v2_5_sw_init - sw init क्रम JPEG block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Load firmware and sw initialization
 */
अटल पूर्णांक jpeg_v2_5_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_ring *ring;
	पूर्णांक i, r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) अणु
		अगर (adev->jpeg.harvest_config & (1 << i))
			जारी;

		/* JPEG TRAP */
		r = amdgpu_irq_add_id(adev, amdgpu_ih_clientid_jpeg[i],
				VCN_2_0__SRCID__JPEG_DECODE, &adev->jpeg.inst[i].irq);
		अगर (r)
			वापस r;
	पूर्ण

	r = amdgpu_jpeg_sw_init(adev);
	अगर (r)
		वापस r;

	r = amdgpu_jpeg_resume(adev);
	अगर (r)
		वापस r;

	क्रम (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) अणु
		अगर (adev->jpeg.harvest_config & (1 << i))
			जारी;

		ring = &adev->jpeg.inst[i].ring_dec;
		ring->use_करोorbell = true;
		ring->करोorbell_index = (adev->करोorbell_index.vcn.vcn_ring0_1 << 1) + 1 + 8 * i;
		प्र_लिखो(ring->name, "jpeg_dec_%d", i);
		r = amdgpu_ring_init(adev, ring, 512, &adev->jpeg.inst[i].irq,
				     0, AMDGPU_RING_PRIO_DEFAULT, शून्य);
		अगर (r)
			वापस r;

		adev->jpeg.पूर्णांकernal.jpeg_pitch = mmUVD_JPEG_PITCH_INTERNAL_OFFSET;
		adev->jpeg.inst[i].बाह्यal.jpeg_pitch = SOC15_REG_OFFSET(JPEG, i, mmUVD_JPEG_PITCH);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * jpeg_v2_5_sw_fini - sw fini क्रम JPEG block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * JPEG suspend and मुक्त up sw allocation
 */
अटल पूर्णांक jpeg_v2_5_sw_fini(व्योम *handle)
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
 * jpeg_v2_5_hw_init - start and test JPEG block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 */
अटल पूर्णांक jpeg_v2_5_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा amdgpu_ring *ring;
	पूर्णांक i, r;

	क्रम (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) अणु
		अगर (adev->jpeg.harvest_config & (1 << i))
			जारी;

		ring = &adev->jpeg.inst[i].ring_dec;
		adev->nbio.funcs->vcn_करोorbell_range(adev, ring->use_करोorbell,
			(adev->करोorbell_index.vcn.vcn_ring0_1 << 1) + 8 * i, i);

		r = amdgpu_ring_test_helper(ring);
		अगर (r)
			वापस r;
	पूर्ण

	DRM_INFO("JPEG decode initialized successfully.\n");

	वापस 0;
पूर्ण

/**
 * jpeg_v2_5_hw_fini - stop the hardware block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Stop the JPEG block, mark ring as not पढ़ोy any more
 */
अटल पूर्णांक jpeg_v2_5_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक i;

	cancel_delayed_work_sync(&adev->vcn.idle_work);

	क्रम (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) अणु
		अगर (adev->jpeg.harvest_config & (1 << i))
			जारी;

		अगर (adev->jpeg.cur_state != AMD_PG_STATE_GATE &&
		      RREG32_SOC15(JPEG, i, mmUVD_JRBC_STATUS))
			jpeg_v2_5_set_घातergating_state(adev, AMD_PG_STATE_GATE);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * jpeg_v2_5_suspend - suspend JPEG block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * HW fini and suspend JPEG block
 */
अटल पूर्णांक jpeg_v2_5_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	r = jpeg_v2_5_hw_fini(adev);
	अगर (r)
		वापस r;

	r = amdgpu_jpeg_suspend(adev);

	वापस r;
पूर्ण

/**
 * jpeg_v2_5_resume - resume JPEG block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Resume firmware and hw init JPEG block
 */
अटल पूर्णांक jpeg_v2_5_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	r = amdgpu_jpeg_resume(adev);
	अगर (r)
		वापस r;

	r = jpeg_v2_5_hw_init(adev);

	वापस r;
पूर्ण

अटल व्योम jpeg_v2_5_disable_घड़ी_gating(काष्ठा amdgpu_device *adev, पूर्णांक inst)
अणु
	uपूर्णांक32_t data;

	data = RREG32_SOC15(JPEG, inst, mmJPEG_CGC_CTRL);
	अगर (adev->cg_flags & AMD_CG_SUPPORT_JPEG_MGCG)
		data |= 1 << JPEG_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
	अन्यथा
		data &= ~JPEG_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;

	data |= 1 << JPEG_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT;
	data |= 4 << JPEG_CGC_CTRL__CLK_OFF_DELAY__SHIFT;
	WREG32_SOC15(JPEG, inst, mmJPEG_CGC_CTRL, data);

	data = RREG32_SOC15(JPEG, inst, mmJPEG_CGC_GATE);
	data &= ~(JPEG_CGC_GATE__JPEG_DEC_MASK
		| JPEG_CGC_GATE__JPEG2_DEC_MASK
		| JPEG_CGC_GATE__JMCIF_MASK
		| JPEG_CGC_GATE__JRBBM_MASK);
	WREG32_SOC15(JPEG, inst, mmJPEG_CGC_GATE, data);

	data = RREG32_SOC15(JPEG, inst, mmJPEG_CGC_CTRL);
	data &= ~(JPEG_CGC_CTRL__JPEG_DEC_MODE_MASK
		| JPEG_CGC_CTRL__JPEG2_DEC_MODE_MASK
		| JPEG_CGC_CTRL__JMCIF_MODE_MASK
		| JPEG_CGC_CTRL__JRBBM_MODE_MASK);
	WREG32_SOC15(JPEG, inst, mmJPEG_CGC_CTRL, data);
पूर्ण

अटल व्योम jpeg_v2_5_enable_घड़ी_gating(काष्ठा amdgpu_device *adev, पूर्णांक inst)
अणु
	uपूर्णांक32_t data;

	data = RREG32_SOC15(JPEG, inst, mmJPEG_CGC_GATE);
	data |= (JPEG_CGC_GATE__JPEG_DEC_MASK
		|JPEG_CGC_GATE__JPEG2_DEC_MASK
		|JPEG_CGC_GATE__JPEG_ENC_MASK
		|JPEG_CGC_GATE__JMCIF_MASK
		|JPEG_CGC_GATE__JRBBM_MASK);
	WREG32_SOC15(JPEG, inst, mmJPEG_CGC_GATE, data);
पूर्ण

/**
 * jpeg_v2_5_start - start JPEG block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Setup and start the JPEG block
 */
अटल पूर्णांक jpeg_v2_5_start(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	पूर्णांक i;

	क्रम (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) अणु
		अगर (adev->jpeg.harvest_config & (1 << i))
			जारी;

		ring = &adev->jpeg.inst[i].ring_dec;
		/* disable anti hang mechanism */
		WREG32_P(SOC15_REG_OFFSET(JPEG, i, mmUVD_JPEG_POWER_STATUS), 0,
			~UVD_JPEG_POWER_STATUS__JPEG_POWER_STATUS_MASK);

		/* JPEG disable CGC */
		jpeg_v2_5_disable_घड़ी_gating(adev, i);

		/* MJPEG global tiling रेजिस्टरs */
		WREG32_SOC15(JPEG, i, mmJPEG_DEC_GFX8_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);
		WREG32_SOC15(JPEG, i, mmJPEG_DEC_GFX10_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);

		/* enable JMI channel */
		WREG32_P(SOC15_REG_OFFSET(JPEG, i, mmUVD_JMI_CNTL), 0,
			~UVD_JMI_CNTL__SOFT_RESET_MASK);

		/* enable System Interrupt क्रम JRBC */
		WREG32_P(SOC15_REG_OFFSET(JPEG, i, mmJPEG_SYS_INT_EN),
			JPEG_SYS_INT_EN__DJRBC_MASK,
			~JPEG_SYS_INT_EN__DJRBC_MASK);

		WREG32_SOC15(JPEG, i, mmUVD_LMI_JRBC_RB_VMID, 0);
		WREG32_SOC15(JPEG, i, mmUVD_JRBC_RB_CNTL, (0x00000001L | 0x00000002L));
		WREG32_SOC15(JPEG, i, mmUVD_LMI_JRBC_RB_64BIT_BAR_LOW,
			lower_32_bits(ring->gpu_addr));
		WREG32_SOC15(JPEG, i, mmUVD_LMI_JRBC_RB_64BIT_BAR_HIGH,
			upper_32_bits(ring->gpu_addr));
		WREG32_SOC15(JPEG, i, mmUVD_JRBC_RB_RPTR, 0);
		WREG32_SOC15(JPEG, i, mmUVD_JRBC_RB_WPTR, 0);
		WREG32_SOC15(JPEG, i, mmUVD_JRBC_RB_CNTL, 0x00000002L);
		WREG32_SOC15(JPEG, i, mmUVD_JRBC_RB_SIZE, ring->ring_size / 4);
		ring->wptr = RREG32_SOC15(JPEG, i, mmUVD_JRBC_RB_WPTR);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * jpeg_v2_5_stop - stop JPEG block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * stop the JPEG block
 */
अटल पूर्णांक jpeg_v2_5_stop(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) अणु
		अगर (adev->jpeg.harvest_config & (1 << i))
			जारी;

		/* reset JMI */
		WREG32_P(SOC15_REG_OFFSET(JPEG, i, mmUVD_JMI_CNTL),
			UVD_JMI_CNTL__SOFT_RESET_MASK,
			~UVD_JMI_CNTL__SOFT_RESET_MASK);

		jpeg_v2_5_enable_घड़ी_gating(adev, i);

		/* enable anti hang mechanism */
		WREG32_P(SOC15_REG_OFFSET(JPEG, i, mmUVD_JPEG_POWER_STATUS),
			UVD_JPEG_POWER_STATUS__JPEG_POWER_STATUS_MASK,
			~UVD_JPEG_POWER_STATUS__JPEG_POWER_STATUS_MASK);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * jpeg_v2_5_dec_ring_get_rptr - get पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t jpeg_v2_5_dec_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32_SOC15(JPEG, ring->me, mmUVD_JRBC_RB_RPTR);
पूर्ण

/**
 * jpeg_v2_5_dec_ring_get_wptr - get ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t jpeg_v2_5_dec_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->use_करोorbell)
		वापस adev->wb.wb[ring->wptr_offs];
	अन्यथा
		वापस RREG32_SOC15(JPEG, ring->me, mmUVD_JRBC_RB_WPTR);
पूर्ण

/**
 * jpeg_v2_5_dec_ring_set_wptr - set ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम jpeg_v2_5_dec_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->use_करोorbell) अणु
		adev->wb.wb[ring->wptr_offs] = lower_32_bits(ring->wptr);
		WDOORBELL32(ring->करोorbell_index, lower_32_bits(ring->wptr));
	पूर्ण अन्यथा अणु
		WREG32_SOC15(JPEG, ring->me, mmUVD_JRBC_RB_WPTR, lower_32_bits(ring->wptr));
	पूर्ण
पूर्ण

अटल bool jpeg_v2_5_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक i, ret = 1;

	क्रम (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) अणु
		अगर (adev->jpeg.harvest_config & (1 << i))
			जारी;

		ret &= (((RREG32_SOC15(JPEG, i, mmUVD_JRBC_STATUS) &
			UVD_JRBC_STATUS__RB_JOB_DONE_MASK) ==
			UVD_JRBC_STATUS__RB_JOB_DONE_MASK));
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक jpeg_v2_5_रुको_क्रम_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक i, ret;

	क्रम (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) अणु
		अगर (adev->jpeg.harvest_config & (1 << i))
			जारी;

		ret = SOC15_WAIT_ON_RREG(JPEG, i, mmUVD_JRBC_STATUS,
			UVD_JRBC_STATUS__RB_JOB_DONE_MASK,
			UVD_JRBC_STATUS__RB_JOB_DONE_MASK);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jpeg_v2_5_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	bool enable = (state == AMD_CG_STATE_GATE);
	पूर्णांक i;

	क्रम (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) अणु
		अगर (adev->jpeg.harvest_config & (1 << i))
			जारी;

		अगर (enable) अणु
			अगर (!jpeg_v2_5_is_idle(handle))
				वापस -EBUSY;
			jpeg_v2_5_enable_घड़ी_gating(adev, i);
		पूर्ण अन्यथा अणु
			jpeg_v2_5_disable_घड़ी_gating(adev, i);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jpeg_v2_5_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक ret;

	अगर(state == adev->jpeg.cur_state)
		वापस 0;

	अगर (state == AMD_PG_STATE_GATE)
		ret = jpeg_v2_5_stop(adev);
	अन्यथा
		ret = jpeg_v2_5_start(adev);

	अगर(!ret)
		adev->jpeg.cur_state = state;

	वापस ret;
पूर्ण

अटल पूर्णांक jpeg_v2_5_set_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक jpeg_v2_5_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	uपूर्णांक32_t ip_instance;

	चयन (entry->client_id) अणु
	हाल SOC15_IH_CLIENTID_VCN:
		ip_instance = 0;
		अवरोध;
	हाल SOC15_IH_CLIENTID_VCN1:
		ip_instance = 1;
		अवरोध;
	शेष:
		DRM_ERROR("Unhandled client id: %d\n", entry->client_id);
		वापस 0;
	पूर्ण

	DRM_DEBUG("IH: JPEG TRAP\n");

	चयन (entry->src_id) अणु
	हाल VCN_2_0__SRCID__JPEG_DECODE:
		amdgpu_fence_process(&adev->jpeg.inst[ip_instance].ring_dec);
		अवरोध;
	शेष:
		DRM_ERROR("Unhandled interrupt: %d %d\n",
			  entry->src_id, entry->src_data[0]);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs jpeg_v2_5_ip_funcs = अणु
	.name = "jpeg_v2_5",
	.early_init = jpeg_v2_5_early_init,
	.late_init = शून्य,
	.sw_init = jpeg_v2_5_sw_init,
	.sw_fini = jpeg_v2_5_sw_fini,
	.hw_init = jpeg_v2_5_hw_init,
	.hw_fini = jpeg_v2_5_hw_fini,
	.suspend = jpeg_v2_5_suspend,
	.resume = jpeg_v2_5_resume,
	.is_idle = jpeg_v2_5_is_idle,
	.रुको_क्रम_idle = jpeg_v2_5_रुको_क्रम_idle,
	.check_soft_reset = शून्य,
	.pre_soft_reset = शून्य,
	.soft_reset = शून्य,
	.post_soft_reset = शून्य,
	.set_घड़ीgating_state = jpeg_v2_5_set_घड़ीgating_state,
	.set_घातergating_state = jpeg_v2_5_set_घातergating_state,
पूर्ण;

अटल स्थिर काष्ठा amd_ip_funcs jpeg_v2_6_ip_funcs = अणु
	.name = "jpeg_v2_6",
	.early_init = jpeg_v2_5_early_init,
	.late_init = शून्य,
	.sw_init = jpeg_v2_5_sw_init,
	.sw_fini = jpeg_v2_5_sw_fini,
	.hw_init = jpeg_v2_5_hw_init,
	.hw_fini = jpeg_v2_5_hw_fini,
	.suspend = jpeg_v2_5_suspend,
	.resume = jpeg_v2_5_resume,
	.is_idle = jpeg_v2_5_is_idle,
	.रुको_क्रम_idle = jpeg_v2_5_रुको_क्रम_idle,
	.check_soft_reset = शून्य,
	.pre_soft_reset = शून्य,
	.soft_reset = शून्य,
	.post_soft_reset = शून्य,
	.set_घड़ीgating_state = jpeg_v2_5_set_घड़ीgating_state,
	.set_घातergating_state = jpeg_v2_5_set_घातergating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs jpeg_v2_5_dec_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_VCN_JPEG,
	.align_mask = 0xf,
	.vmhub = AMDGPU_MMHUB_1,
	.get_rptr = jpeg_v2_5_dec_ring_get_rptr,
	.get_wptr = jpeg_v2_5_dec_ring_get_wptr,
	.set_wptr = jpeg_v2_5_dec_ring_set_wptr,
	.emit_frame_size =
		SOC15_FLUSH_GPU_TLB_NUM_WREG * 6 +
		SOC15_FLUSH_GPU_TLB_NUM_REG_WAIT * 8 +
		8 + /* jpeg_v2_5_dec_ring_emit_vm_flush */
		18 + 18 + /* jpeg_v2_5_dec_ring_emit_fence x2 vm fence */
		8 + 16,
	.emit_ib_size = 22, /* jpeg_v2_5_dec_ring_emit_ib */
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

अटल स्थिर काष्ठा amdgpu_ring_funcs jpeg_v2_6_dec_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_VCN_JPEG,
	.align_mask = 0xf,
	.vmhub = AMDGPU_MMHUB_0,
	.get_rptr = jpeg_v2_5_dec_ring_get_rptr,
	.get_wptr = jpeg_v2_5_dec_ring_get_wptr,
	.set_wptr = jpeg_v2_5_dec_ring_set_wptr,
	.emit_frame_size =
		SOC15_FLUSH_GPU_TLB_NUM_WREG * 6 +
		SOC15_FLUSH_GPU_TLB_NUM_REG_WAIT * 8 +
		8 + /* jpeg_v2_5_dec_ring_emit_vm_flush */
		18 + 18 + /* jpeg_v2_5_dec_ring_emit_fence x2 vm fence */
		8 + 16,
	.emit_ib_size = 22, /* jpeg_v2_5_dec_ring_emit_ib */
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

अटल व्योम jpeg_v2_5_set_dec_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) अणु
		अगर (adev->jpeg.harvest_config & (1 << i))
			जारी;
		अगर (adev->asic_type == CHIP_ARCTURUS)
			adev->jpeg.inst[i].ring_dec.funcs = &jpeg_v2_5_dec_ring_vm_funcs;
		अन्यथा  /* CHIP_ALDEBARAN */
			adev->jpeg.inst[i].ring_dec.funcs = &jpeg_v2_6_dec_ring_vm_funcs;
		adev->jpeg.inst[i].ring_dec.me = i;
		DRM_INFO("JPEG(%d) JPEG decode is enabled in VM mode\n", i);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs jpeg_v2_5_irq_funcs = अणु
	.set = jpeg_v2_5_set_पूर्णांकerrupt_state,
	.process = jpeg_v2_5_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम jpeg_v2_5_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) अणु
		अगर (adev->jpeg.harvest_config & (1 << i))
			जारी;

		adev->jpeg.inst[i].irq.num_types = 1;
		adev->jpeg.inst[i].irq.funcs = &jpeg_v2_5_irq_funcs;
	पूर्ण
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version jpeg_v2_5_ip_block =
अणु
		.type = AMD_IP_BLOCK_TYPE_JPEG,
		.major = 2,
		.minor = 5,
		.rev = 0,
		.funcs = &jpeg_v2_5_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version jpeg_v2_6_ip_block =
अणु
		.type = AMD_IP_BLOCK_TYPE_JPEG,
		.major = 2,
		.minor = 6,
		.rev = 0,
		.funcs = &jpeg_v2_6_ip_funcs,
पूर्ण;
