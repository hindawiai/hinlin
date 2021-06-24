<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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

#समावेश <linux/firmware.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_vcn.h"
#समावेश "amdgpu_pm.h"
#समावेश "soc15.h"
#समावेश "soc15d.h"
#समावेश "soc15_common.h"

#समावेश "vcn/vcn_1_0_offset.h"
#समावेश "vcn/vcn_1_0_sh_mask.h"
#समावेश "mmhub/mmhub_9_1_offset.h"
#समावेश "mmhub/mmhub_9_1_sh_mask.h"

#समावेश "ivsrcid/vcn/irqsrcs_vcn_1_0.h"
#समावेश "jpeg_v1_0.h"
#समावेश "vcn_v1_0.h"

#घोषणा mmUVD_RBC_XX_IB_REG_CHECK_1_0		0x05ab
#घोषणा mmUVD_RBC_XX_IB_REG_CHECK_1_0_BASE_IDX	1
#घोषणा mmUVD_REG_XX_MASK_1_0			0x05ac
#घोषणा mmUVD_REG_XX_MASK_1_0_BASE_IDX		1

अटल पूर्णांक vcn_v1_0_stop(काष्ठा amdgpu_device *adev);
अटल व्योम vcn_v1_0_set_dec_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम vcn_v1_0_set_enc_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम vcn_v1_0_set_irq_funcs(काष्ठा amdgpu_device *adev);
अटल पूर्णांक vcn_v1_0_set_घातergating_state(व्योम *handle, क्रमागत amd_घातergating_state state);
अटल पूर्णांक vcn_v1_0_छोड़ो_dpg_mode(काष्ठा amdgpu_device *adev,
				पूर्णांक inst_idx, काष्ठा dpg_छोड़ो_state *new_state);

अटल व्योम vcn_v1_0_idle_work_handler(काष्ठा work_काष्ठा *work);
अटल व्योम vcn_v1_0_ring_begin_use(काष्ठा amdgpu_ring *ring);

/**
 * vcn_v1_0_early_init - set function poपूर्णांकers
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Set ring and irq function poपूर्णांकers
 */
अटल पूर्णांक vcn_v1_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->vcn.num_vcn_inst = 1;
	adev->vcn.num_enc_rings = 2;

	vcn_v1_0_set_dec_ring_funcs(adev);
	vcn_v1_0_set_enc_ring_funcs(adev);
	vcn_v1_0_set_irq_funcs(adev);

	jpeg_v1_0_early_init(handle);

	वापस 0;
पूर्ण

/**
 * vcn_v1_0_sw_init - sw init क्रम VCN block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Load firmware and sw initialization
 */
अटल पूर्णांक vcn_v1_0_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_ring *ring;
	पूर्णांक i, r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* VCN DEC TRAP */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_VCN,
			VCN_1_0__SRCID__UVD_SYSTEM_MESSAGE_INTERRUPT, &adev->vcn.inst->irq);
	अगर (r)
		वापस r;

	/* VCN ENC TRAP */
	क्रम (i = 0; i < adev->vcn.num_enc_rings; ++i) अणु
		r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_VCN, i + VCN_1_0__SRCID__UVD_ENC_GENERAL_PURPOSE,
					&adev->vcn.inst->irq);
		अगर (r)
			वापस r;
	पूर्ण

	r = amdgpu_vcn_sw_init(adev);
	अगर (r)
		वापस r;

	/* Override the work func */
	adev->vcn.idle_work.work.func = vcn_v1_0_idle_work_handler;

	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
		स्थिर काष्ठा common_firmware_header *hdr;
		hdr = (स्थिर काष्ठा common_firmware_header *)adev->vcn.fw->data;
		adev->firmware.ucode[AMDGPU_UCODE_ID_VCN].ucode_id = AMDGPU_UCODE_ID_VCN;
		adev->firmware.ucode[AMDGPU_UCODE_ID_VCN].fw = adev->vcn.fw;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(hdr->ucode_size_bytes), PAGE_SIZE);
		DRM_INFO("PSP loading VCN firmware\n");
	पूर्ण

	r = amdgpu_vcn_resume(adev);
	अगर (r)
		वापस r;

	ring = &adev->vcn.inst->ring_dec;
	प्र_लिखो(ring->name, "vcn_dec");
	r = amdgpu_ring_init(adev, ring, 512, &adev->vcn.inst->irq, 0,
			     AMDGPU_RING_PRIO_DEFAULT, शून्य);
	अगर (r)
		वापस r;

	adev->vcn.पूर्णांकernal.scratch9 = adev->vcn.inst->बाह्यal.scratch9 =
		SOC15_REG_OFFSET(UVD, 0, mmUVD_SCRATCH9);
	adev->vcn.पूर्णांकernal.data0 = adev->vcn.inst->बाह्यal.data0 =
		SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA0);
	adev->vcn.पूर्णांकernal.data1 = adev->vcn.inst->बाह्यal.data1 =
		SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA1);
	adev->vcn.पूर्णांकernal.cmd = adev->vcn.inst->बाह्यal.cmd =
		SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_CMD);
	adev->vcn.पूर्णांकernal.nop = adev->vcn.inst->बाह्यal.nop =
		SOC15_REG_OFFSET(UVD, 0, mmUVD_NO_OP);

	क्रम (i = 0; i < adev->vcn.num_enc_rings; ++i) अणु
		ring = &adev->vcn.inst->ring_enc[i];
		प्र_लिखो(ring->name, "vcn_enc%d", i);
		r = amdgpu_ring_init(adev, ring, 512, &adev->vcn.inst->irq, 0,
				     AMDGPU_RING_PRIO_DEFAULT, शून्य);
		अगर (r)
			वापस r;
	पूर्ण

	adev->vcn.छोड़ो_dpg_mode = vcn_v1_0_छोड़ो_dpg_mode;

	r = jpeg_v1_0_sw_init(handle);

	वापस r;
पूर्ण

/**
 * vcn_v1_0_sw_fini - sw fini क्रम VCN block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * VCN suspend and मुक्त up sw allocation
 */
अटल पूर्णांक vcn_v1_0_sw_fini(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_vcn_suspend(adev);
	अगर (r)
		वापस r;

	jpeg_v1_0_sw_fini(handle);

	r = amdgpu_vcn_sw_fini(adev);

	वापस r;
पूर्ण

/**
 * vcn_v1_0_hw_init - start and test VCN block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Initialize the hardware, boot up the VCPU and करो some testing
 */
अटल पूर्णांक vcn_v1_0_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा amdgpu_ring *ring = &adev->vcn.inst->ring_dec;
	पूर्णांक i, r;

	r = amdgpu_ring_test_helper(ring);
	अगर (r)
		जाओ करोne;

	क्रम (i = 0; i < adev->vcn.num_enc_rings; ++i) अणु
		ring = &adev->vcn.inst->ring_enc[i];
		r = amdgpu_ring_test_helper(ring);
		अगर (r)
			जाओ करोne;
	पूर्ण

	ring = &adev->jpeg.inst->ring_dec;
	r = amdgpu_ring_test_helper(ring);
	अगर (r)
		जाओ करोne;

करोne:
	अगर (!r)
		DRM_INFO("VCN decode and encode initialized successfully(under %s).\n",
			(adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG)?"DPG Mode":"SPG Mode");

	वापस r;
पूर्ण

/**
 * vcn_v1_0_hw_fini - stop the hardware block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Stop the VCN block, mark ring as not पढ़ोy any more
 */
अटल पूर्णांक vcn_v1_0_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	cancel_delayed_work_sync(&adev->vcn.idle_work);

	अगर ((adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG) ||
		(adev->vcn.cur_state != AMD_PG_STATE_GATE &&
		 RREG32_SOC15(VCN, 0, mmUVD_STATUS))) अणु
		vcn_v1_0_set_घातergating_state(adev, AMD_PG_STATE_GATE);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vcn_v1_0_suspend - suspend VCN block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * HW fini and suspend VCN block
 */
अटल पूर्णांक vcn_v1_0_suspend(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = vcn_v1_0_hw_fini(adev);
	अगर (r)
		वापस r;

	r = amdgpu_vcn_suspend(adev);

	वापस r;
पूर्ण

/**
 * vcn_v1_0_resume - resume VCN block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Resume firmware and hw init VCN block
 */
अटल पूर्णांक vcn_v1_0_resume(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_vcn_resume(adev);
	अगर (r)
		वापस r;

	r = vcn_v1_0_hw_init(adev);

	वापस r;
पूर्ण

/**
 * vcn_v1_0_mc_resume_spg_mode - memory controller programming
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Let the VCN memory controller know it's offsets
 */
अटल व्योम vcn_v1_0_mc_resume_spg_mode(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t size = AMDGPU_GPU_PAGE_ALIGN(adev->vcn.fw->size + 4);
	uपूर्णांक32_t offset;

	/* cache winकरोw 0: fw */
	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
		WREG32_SOC15(UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW,
			     (adev->firmware.ucode[AMDGPU_UCODE_ID_VCN].पंचांगr_mc_addr_lo));
		WREG32_SOC15(UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH,
			     (adev->firmware.ucode[AMDGPU_UCODE_ID_VCN].पंचांगr_mc_addr_hi));
		WREG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_OFFSET0, 0);
		offset = 0;
	पूर्ण अन्यथा अणु
		WREG32_SOC15(UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW,
			lower_32_bits(adev->vcn.inst->gpu_addr));
		WREG32_SOC15(UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH,
			upper_32_bits(adev->vcn.inst->gpu_addr));
		offset = size;
		WREG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_OFFSET0,
			     AMDGPU_UVD_FIRMWARE_OFFSET >> 3);
	पूर्ण

	WREG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_SIZE0, size);

	/* cache winकरोw 1: stack */
	WREG32_SOC15(UVD, 0, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW,
		     lower_32_bits(adev->vcn.inst->gpu_addr + offset));
	WREG32_SOC15(UVD, 0, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH,
		     upper_32_bits(adev->vcn.inst->gpu_addr + offset));
	WREG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_OFFSET1, 0);
	WREG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_SIZE1, AMDGPU_VCN_STACK_SIZE);

	/* cache winकरोw 2: context */
	WREG32_SOC15(UVD, 0, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW,
		     lower_32_bits(adev->vcn.inst->gpu_addr + offset + AMDGPU_VCN_STACK_SIZE));
	WREG32_SOC15(UVD, 0, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH,
		     upper_32_bits(adev->vcn.inst->gpu_addr + offset + AMDGPU_VCN_STACK_SIZE));
	WREG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_OFFSET2, 0);
	WREG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_SIZE2, AMDGPU_VCN_CONTEXT_SIZE);

	WREG32_SOC15(UVD, 0, mmUVD_UDEC_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);
	WREG32_SOC15(UVD, 0, mmUVD_UDEC_DB_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);
	WREG32_SOC15(UVD, 0, mmUVD_UDEC_DBW_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);
	WREG32_SOC15(UVD, 0, mmUVD_UDEC_DBW_UV_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);
	WREG32_SOC15(UVD, 0, mmUVD_MIF_CURR_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);
	WREG32_SOC15(UVD, 0, mmUVD_MIF_CURR_UV_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);
	WREG32_SOC15(UVD, 0, mmUVD_MIF_RECON1_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);
	WREG32_SOC15(UVD, 0, mmUVD_MIF_RECON1_UV_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);
	WREG32_SOC15(UVD, 0, mmUVD_MIF_REF_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);
	WREG32_SOC15(UVD, 0, mmUVD_MIF_REF_UV_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);
	WREG32_SOC15(UVD, 0, mmUVD_JPEG_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);
	WREG32_SOC15(UVD, 0, mmUVD_JPEG_UV_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);
पूर्ण

अटल व्योम vcn_v1_0_mc_resume_dpg_mode(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t size = AMDGPU_GPU_PAGE_ALIGN(adev->vcn.fw->size + 4);
	uपूर्णांक32_t offset;

	/* cache winकरोw 0: fw */
	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
		WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW,
			     (adev->firmware.ucode[AMDGPU_UCODE_ID_VCN].पंचांगr_mc_addr_lo),
			     0xFFFFFFFF, 0);
		WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH,
			     (adev->firmware.ucode[AMDGPU_UCODE_ID_VCN].पंचांगr_mc_addr_hi),
			     0xFFFFFFFF, 0);
		WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_VCPU_CACHE_OFFSET0, 0,
			     0xFFFFFFFF, 0);
		offset = 0;
	पूर्ण अन्यथा अणु
		WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW,
			lower_32_bits(adev->vcn.inst->gpu_addr), 0xFFFFFFFF, 0);
		WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH,
			upper_32_bits(adev->vcn.inst->gpu_addr), 0xFFFFFFFF, 0);
		offset = size;
		WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_VCPU_CACHE_OFFSET0,
			     AMDGPU_UVD_FIRMWARE_OFFSET >> 3, 0xFFFFFFFF, 0);
	पूर्ण

	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_VCPU_CACHE_SIZE0, size, 0xFFFFFFFF, 0);

	/* cache winकरोw 1: stack */
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW,
		     lower_32_bits(adev->vcn.inst->gpu_addr + offset), 0xFFFFFFFF, 0);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH,
		     upper_32_bits(adev->vcn.inst->gpu_addr + offset), 0xFFFFFFFF, 0);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_VCPU_CACHE_OFFSET1, 0,
			     0xFFFFFFFF, 0);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_VCPU_CACHE_SIZE1, AMDGPU_VCN_STACK_SIZE,
			     0xFFFFFFFF, 0);

	/* cache winकरोw 2: context */
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW,
		     lower_32_bits(adev->vcn.inst->gpu_addr + offset + AMDGPU_VCN_STACK_SIZE),
			     0xFFFFFFFF, 0);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH,
		     upper_32_bits(adev->vcn.inst->gpu_addr + offset + AMDGPU_VCN_STACK_SIZE),
			     0xFFFFFFFF, 0);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_VCPU_CACHE_OFFSET2, 0, 0xFFFFFFFF, 0);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_VCPU_CACHE_SIZE2, AMDGPU_VCN_CONTEXT_SIZE,
			     0xFFFFFFFF, 0);

	/* VCN global tiling रेजिस्टरs */
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_UDEC_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config, 0xFFFFFFFF, 0);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_UDEC_DB_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config, 0xFFFFFFFF, 0);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_UDEC_DBW_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config, 0xFFFFFFFF, 0);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_UDEC_DBW_UV_ADDR_CONFIG,
		adev->gfx.config.gb_addr_config, 0xFFFFFFFF, 0);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MIF_CURR_ADDR_CONFIG,
		adev->gfx.config.gb_addr_config, 0xFFFFFFFF, 0);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MIF_CURR_UV_ADDR_CONFIG,
		adev->gfx.config.gb_addr_config, 0xFFFFFFFF, 0);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MIF_RECON1_ADDR_CONFIG,
		adev->gfx.config.gb_addr_config, 0xFFFFFFFF, 0);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MIF_RECON1_UV_ADDR_CONFIG,
		adev->gfx.config.gb_addr_config, 0xFFFFFFFF, 0);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MIF_REF_ADDR_CONFIG,
		adev->gfx.config.gb_addr_config, 0xFFFFFFFF, 0);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MIF_REF_UV_ADDR_CONFIG,
		adev->gfx.config.gb_addr_config, 0xFFFFFFFF, 0);
पूर्ण

/**
 * vcn_v1_0_disable_घड़ी_gating - disable VCN घड़ी gating
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Disable घड़ी gating क्रम VCN block
 */
अटल व्योम vcn_v1_0_disable_घड़ी_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data;

	/* JPEG disable CGC */
	data = RREG32_SOC15(VCN, 0, mmJPEG_CGC_CTRL);

	अगर (adev->cg_flags & AMD_CG_SUPPORT_VCN_MGCG)
		data |= 1 << JPEG_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
	अन्यथा
		data &= ~JPEG_CGC_CTRL__DYN_CLOCK_MODE_MASK;

	data |= 1 << JPEG_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT;
	data |= 4 << JPEG_CGC_CTRL__CLK_OFF_DELAY__SHIFT;
	WREG32_SOC15(VCN, 0, mmJPEG_CGC_CTRL, data);

	data = RREG32_SOC15(VCN, 0, mmJPEG_CGC_GATE);
	data &= ~(JPEG_CGC_GATE__JPEG_MASK | JPEG_CGC_GATE__JPEG2_MASK);
	WREG32_SOC15(VCN, 0, mmJPEG_CGC_GATE, data);

	/* UVD disable CGC */
	data = RREG32_SOC15(VCN, 0, mmUVD_CGC_CTRL);
	अगर (adev->cg_flags & AMD_CG_SUPPORT_VCN_MGCG)
		data |= 1 << UVD_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
	अन्यथा
		data &= ~ UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK;

	data |= 1 << UVD_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT;
	data |= 4 << UVD_CGC_CTRL__CLK_OFF_DELAY__SHIFT;
	WREG32_SOC15(VCN, 0, mmUVD_CGC_CTRL, data);

	data = RREG32_SOC15(VCN, 0, mmUVD_CGC_GATE);
	data &= ~(UVD_CGC_GATE__SYS_MASK
		| UVD_CGC_GATE__UDEC_MASK
		| UVD_CGC_GATE__MPEG2_MASK
		| UVD_CGC_GATE__REGS_MASK
		| UVD_CGC_GATE__RBC_MASK
		| UVD_CGC_GATE__LMI_MC_MASK
		| UVD_CGC_GATE__LMI_UMC_MASK
		| UVD_CGC_GATE__IDCT_MASK
		| UVD_CGC_GATE__MPRD_MASK
		| UVD_CGC_GATE__MPC_MASK
		| UVD_CGC_GATE__LBSI_MASK
		| UVD_CGC_GATE__LRBBM_MASK
		| UVD_CGC_GATE__UDEC_RE_MASK
		| UVD_CGC_GATE__UDEC_CM_MASK
		| UVD_CGC_GATE__UDEC_IT_MASK
		| UVD_CGC_GATE__UDEC_DB_MASK
		| UVD_CGC_GATE__UDEC_MP_MASK
		| UVD_CGC_GATE__WCB_MASK
		| UVD_CGC_GATE__VCPU_MASK
		| UVD_CGC_GATE__SCPU_MASK);
	WREG32_SOC15(VCN, 0, mmUVD_CGC_GATE, data);

	data = RREG32_SOC15(VCN, 0, mmUVD_CGC_CTRL);
	data &= ~(UVD_CGC_CTRL__UDEC_RE_MODE_MASK
		| UVD_CGC_CTRL__UDEC_CM_MODE_MASK
		| UVD_CGC_CTRL__UDEC_IT_MODE_MASK
		| UVD_CGC_CTRL__UDEC_DB_MODE_MASK
		| UVD_CGC_CTRL__UDEC_MP_MODE_MASK
		| UVD_CGC_CTRL__SYS_MODE_MASK
		| UVD_CGC_CTRL__UDEC_MODE_MASK
		| UVD_CGC_CTRL__MPEG2_MODE_MASK
		| UVD_CGC_CTRL__REGS_MODE_MASK
		| UVD_CGC_CTRL__RBC_MODE_MASK
		| UVD_CGC_CTRL__LMI_MC_MODE_MASK
		| UVD_CGC_CTRL__LMI_UMC_MODE_MASK
		| UVD_CGC_CTRL__IDCT_MODE_MASK
		| UVD_CGC_CTRL__MPRD_MODE_MASK
		| UVD_CGC_CTRL__MPC_MODE_MASK
		| UVD_CGC_CTRL__LBSI_MODE_MASK
		| UVD_CGC_CTRL__LRBBM_MODE_MASK
		| UVD_CGC_CTRL__WCB_MODE_MASK
		| UVD_CGC_CTRL__VCPU_MODE_MASK
		| UVD_CGC_CTRL__SCPU_MODE_MASK);
	WREG32_SOC15(VCN, 0, mmUVD_CGC_CTRL, data);

	/* turn on */
	data = RREG32_SOC15(VCN, 0, mmUVD_SUVD_CGC_GATE);
	data |= (UVD_SUVD_CGC_GATE__SRE_MASK
		| UVD_SUVD_CGC_GATE__SIT_MASK
		| UVD_SUVD_CGC_GATE__SMP_MASK
		| UVD_SUVD_CGC_GATE__SCM_MASK
		| UVD_SUVD_CGC_GATE__SDB_MASK
		| UVD_SUVD_CGC_GATE__SRE_H264_MASK
		| UVD_SUVD_CGC_GATE__SRE_HEVC_MASK
		| UVD_SUVD_CGC_GATE__SIT_H264_MASK
		| UVD_SUVD_CGC_GATE__SIT_HEVC_MASK
		| UVD_SUVD_CGC_GATE__SCM_H264_MASK
		| UVD_SUVD_CGC_GATE__SCM_HEVC_MASK
		| UVD_SUVD_CGC_GATE__SDB_H264_MASK
		| UVD_SUVD_CGC_GATE__SDB_HEVC_MASK
		| UVD_SUVD_CGC_GATE__SCLR_MASK
		| UVD_SUVD_CGC_GATE__UVD_SC_MASK
		| UVD_SUVD_CGC_GATE__ENT_MASK
		| UVD_SUVD_CGC_GATE__SIT_HEVC_DEC_MASK
		| UVD_SUVD_CGC_GATE__SIT_HEVC_ENC_MASK
		| UVD_SUVD_CGC_GATE__SITE_MASK
		| UVD_SUVD_CGC_GATE__SRE_VP9_MASK
		| UVD_SUVD_CGC_GATE__SCM_VP9_MASK
		| UVD_SUVD_CGC_GATE__SIT_VP9_DEC_MASK
		| UVD_SUVD_CGC_GATE__SDB_VP9_MASK
		| UVD_SUVD_CGC_GATE__IME_HEVC_MASK);
	WREG32_SOC15(VCN, 0, mmUVD_SUVD_CGC_GATE, data);

	data = RREG32_SOC15(VCN, 0, mmUVD_SUVD_CGC_CTRL);
	data &= ~(UVD_SUVD_CGC_CTRL__SRE_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SIT_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SMP_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SCM_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SDB_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SCLR_MODE_MASK
		| UVD_SUVD_CGC_CTRL__UVD_SC_MODE_MASK
		| UVD_SUVD_CGC_CTRL__ENT_MODE_MASK
		| UVD_SUVD_CGC_CTRL__IME_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SITE_MODE_MASK);
	WREG32_SOC15(VCN, 0, mmUVD_SUVD_CGC_CTRL, data);
पूर्ण

/**
 * vcn_v1_0_enable_घड़ी_gating - enable VCN घड़ी gating
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Enable घड़ी gating क्रम VCN block
 */
अटल व्योम vcn_v1_0_enable_घड़ी_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data = 0;

	/* enable JPEG CGC */
	data = RREG32_SOC15(VCN, 0, mmJPEG_CGC_CTRL);
	अगर (adev->cg_flags & AMD_CG_SUPPORT_VCN_MGCG)
		data |= 1 << JPEG_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
	अन्यथा
		data |= 0 << JPEG_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
	data |= 1 << JPEG_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT;
	data |= 4 << JPEG_CGC_CTRL__CLK_OFF_DELAY__SHIFT;
	WREG32_SOC15(VCN, 0, mmJPEG_CGC_CTRL, data);

	data = RREG32_SOC15(VCN, 0, mmJPEG_CGC_GATE);
	data |= (JPEG_CGC_GATE__JPEG_MASK | JPEG_CGC_GATE__JPEG2_MASK);
	WREG32_SOC15(VCN, 0, mmJPEG_CGC_GATE, data);

	/* enable UVD CGC */
	data = RREG32_SOC15(VCN, 0, mmUVD_CGC_CTRL);
	अगर (adev->cg_flags & AMD_CG_SUPPORT_VCN_MGCG)
		data |= 1 << UVD_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
	अन्यथा
		data |= 0 << UVD_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
	data |= 1 << UVD_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT;
	data |= 4 << UVD_CGC_CTRL__CLK_OFF_DELAY__SHIFT;
	WREG32_SOC15(VCN, 0, mmUVD_CGC_CTRL, data);

	data = RREG32_SOC15(VCN, 0, mmUVD_CGC_CTRL);
	data |= (UVD_CGC_CTRL__UDEC_RE_MODE_MASK
		| UVD_CGC_CTRL__UDEC_CM_MODE_MASK
		| UVD_CGC_CTRL__UDEC_IT_MODE_MASK
		| UVD_CGC_CTRL__UDEC_DB_MODE_MASK
		| UVD_CGC_CTRL__UDEC_MP_MODE_MASK
		| UVD_CGC_CTRL__SYS_MODE_MASK
		| UVD_CGC_CTRL__UDEC_MODE_MASK
		| UVD_CGC_CTRL__MPEG2_MODE_MASK
		| UVD_CGC_CTRL__REGS_MODE_MASK
		| UVD_CGC_CTRL__RBC_MODE_MASK
		| UVD_CGC_CTRL__LMI_MC_MODE_MASK
		| UVD_CGC_CTRL__LMI_UMC_MODE_MASK
		| UVD_CGC_CTRL__IDCT_MODE_MASK
		| UVD_CGC_CTRL__MPRD_MODE_MASK
		| UVD_CGC_CTRL__MPC_MODE_MASK
		| UVD_CGC_CTRL__LBSI_MODE_MASK
		| UVD_CGC_CTRL__LRBBM_MODE_MASK
		| UVD_CGC_CTRL__WCB_MODE_MASK
		| UVD_CGC_CTRL__VCPU_MODE_MASK
		| UVD_CGC_CTRL__SCPU_MODE_MASK);
	WREG32_SOC15(VCN, 0, mmUVD_CGC_CTRL, data);

	data = RREG32_SOC15(VCN, 0, mmUVD_SUVD_CGC_CTRL);
	data |= (UVD_SUVD_CGC_CTRL__SRE_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SIT_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SMP_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SCM_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SDB_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SCLR_MODE_MASK
		| UVD_SUVD_CGC_CTRL__UVD_SC_MODE_MASK
		| UVD_SUVD_CGC_CTRL__ENT_MODE_MASK
		| UVD_SUVD_CGC_CTRL__IME_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SITE_MODE_MASK);
	WREG32_SOC15(VCN, 0, mmUVD_SUVD_CGC_CTRL, data);
पूर्ण

अटल व्योम vcn_v1_0_घड़ी_gating_dpg_mode(काष्ठा amdgpu_device *adev, uपूर्णांक8_t sram_sel)
अणु
	uपूर्णांक32_t reg_data = 0;

	/* disable JPEG CGC */
	अगर (adev->cg_flags & AMD_CG_SUPPORT_VCN_MGCG)
		reg_data = 1 << JPEG_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
	अन्यथा
		reg_data = 0 << JPEG_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
	reg_data |= 1 << JPEG_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT;
	reg_data |= 4 << JPEG_CGC_CTRL__CLK_OFF_DELAY__SHIFT;
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmJPEG_CGC_CTRL, reg_data, 0xFFFFFFFF, sram_sel);

	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmJPEG_CGC_GATE, 0, 0xFFFFFFFF, sram_sel);

	/* enable sw घड़ी gating control */
	अगर (adev->cg_flags & AMD_CG_SUPPORT_VCN_MGCG)
		reg_data = 1 << UVD_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
	अन्यथा
		reg_data = 0 << UVD_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
	reg_data |= 1 << UVD_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT;
	reg_data |= 4 << UVD_CGC_CTRL__CLK_OFF_DELAY__SHIFT;
	reg_data &= ~(UVD_CGC_CTRL__UDEC_RE_MODE_MASK |
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
		 UVD_CGC_CTRL__SCPU_MODE_MASK);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_CGC_CTRL, reg_data, 0xFFFFFFFF, sram_sel);

	/* turn off घड़ी gating */
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_CGC_GATE, 0, 0xFFFFFFFF, sram_sel);

	/* turn on SUVD घड़ी gating */
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_SUVD_CGC_GATE, 1, 0xFFFFFFFF, sram_sel);

	/* turn on sw mode in UVD_SUVD_CGC_CTRL */
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_SUVD_CGC_CTRL, 0, 0xFFFFFFFF, sram_sel);
पूर्ण

अटल व्योम vcn_1_0_disable_अटल_घातer_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data = 0;

	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN) अणु
		data = (1 << UVD_PGFSM_CONFIG__UVDM_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDU_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDF_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDC_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDB_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDIL_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVसूची_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTD_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTE_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDE_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDW_PWR_CONFIG__SHIFT);

		WREG32_SOC15(VCN, 0, mmUVD_PGFSM_CONFIG, data);
		SOC15_WAIT_ON_RREG(VCN, 0, mmUVD_PGFSM_STATUS, UVD_PGFSM_STATUS__UVDM_UVDU_PWR_ON, 0xFFFFFF);
	पूर्ण अन्यथा अणु
		data = (1 << UVD_PGFSM_CONFIG__UVDM_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDU_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDF_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDC_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDB_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDIL_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVसूची_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDTD_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDTE_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDE_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDW_PWR_CONFIG__SHIFT);
		WREG32_SOC15(VCN, 0, mmUVD_PGFSM_CONFIG, data);
		SOC15_WAIT_ON_RREG(VCN, 0, mmUVD_PGFSM_STATUS, 0,  0xFFFFFFFF);
	पूर्ण

	/* polling UVD_PGFSM_STATUS to confirm UVDM_PWR_STATUS , UVDU_PWR_STATUS are 0 (घातer on) */

	data = RREG32_SOC15(VCN, 0, mmUVD_POWER_STATUS);
	data &= ~0x103;
	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN)
		data |= UVD_PGFSM_CONFIG__UVDM_UVDU_PWR_ON | UVD_POWER_STATUS__UVD_PG_EN_MASK;

	WREG32_SOC15(VCN, 0, mmUVD_POWER_STATUS, data);
पूर्ण

अटल व्योम vcn_1_0_enable_अटल_घातer_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data = 0;

	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN) अणु
		/* Beक्रमe घातer off, this indicator has to be turned on */
		data = RREG32_SOC15(VCN, 0, mmUVD_POWER_STATUS);
		data &= ~UVD_POWER_STATUS__UVD_POWER_STATUS_MASK;
		data |= UVD_POWER_STATUS__UVD_POWER_STATUS_TILES_OFF;
		WREG32_SOC15(VCN, 0, mmUVD_POWER_STATUS, data);


		data = (2 << UVD_PGFSM_CONFIG__UVDM_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDU_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDF_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDC_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDB_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDIL_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVसूची_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTD_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTE_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDE_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDW_PWR_CONFIG__SHIFT);

		WREG32_SOC15(VCN, 0, mmUVD_PGFSM_CONFIG, data);

		data = (2 << UVD_PGFSM_STATUS__UVDM_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDU_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDF_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDC_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDB_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDIL_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVसूची_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDTD_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDTE_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDE_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDW_PWR_STATUS__SHIFT);
		SOC15_WAIT_ON_RREG(VCN, 0, mmUVD_PGFSM_STATUS, data, 0xFFFFFFFF);
	पूर्ण
पूर्ण

/**
 * vcn_v1_0_start - start VCN block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Setup and start the VCN block
 */
अटल पूर्णांक vcn_v1_0_start_spg_mode(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring = &adev->vcn.inst->ring_dec;
	uपूर्णांक32_t rb_bufsz, पंचांगp;
	uपूर्णांक32_t lmi_swap_cntl;
	पूर्णांक i, j, r;

	/* disable byte swapping */
	lmi_swap_cntl = 0;

	vcn_1_0_disable_अटल_घातer_gating(adev);

	पंचांगp = RREG32_SOC15(UVD, 0, mmUVD_STATUS) | UVD_STATUS__UVD_BUSY;
	WREG32_SOC15(UVD, 0, mmUVD_STATUS, पंचांगp);

	/* disable घड़ी gating */
	vcn_v1_0_disable_घड़ी_gating(adev);

	/* disable पूर्णांकerupt */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_MASTINT_EN), 0,
			~UVD_MASTINT_EN__VCPU_EN_MASK);

	/* initialize VCN memory controller */
	पंचांगp = RREG32_SOC15(UVD, 0, mmUVD_LMI_CTRL);
	WREG32_SOC15(UVD, 0, mmUVD_LMI_CTRL, पंचांगp		|
		UVD_LMI_CTRL__WRITE_CLEAN_TIMER_EN_MASK	|
		UVD_LMI_CTRL__MASK_MC_URGENT_MASK			|
		UVD_LMI_CTRL__DATA_COHERENCY_EN_MASK		|
		UVD_LMI_CTRL__VCPU_DATA_COHERENCY_EN_MASK);

#अगर_घोषित __BIG_ENDIAN
	/* swap (8 in 32) RB and IB */
	lmi_swap_cntl = 0xa;
#पूर्ण_अगर
	WREG32_SOC15(UVD, 0, mmUVD_LMI_SWAP_CNTL, lmi_swap_cntl);

	पंचांगp = RREG32_SOC15(UVD, 0, mmUVD_MPC_CNTL);
	पंचांगp &= ~UVD_MPC_CNTL__REPLACEMENT_MODE_MASK;
	पंचांगp |= 0x2 << UVD_MPC_CNTL__REPLACEMENT_MODE__SHIFT;
	WREG32_SOC15(UVD, 0, mmUVD_MPC_CNTL, पंचांगp);

	WREG32_SOC15(UVD, 0, mmUVD_MPC_SET_MUXA0,
		((0x1 << UVD_MPC_SET_MUXA0__VARA_1__SHIFT) |
		(0x2 << UVD_MPC_SET_MUXA0__VARA_2__SHIFT) |
		(0x3 << UVD_MPC_SET_MUXA0__VARA_3__SHIFT) |
		(0x4 << UVD_MPC_SET_MUXA0__VARA_4__SHIFT)));

	WREG32_SOC15(UVD, 0, mmUVD_MPC_SET_MUXB0,
		((0x1 << UVD_MPC_SET_MUXB0__VARB_1__SHIFT) |
		(0x2 << UVD_MPC_SET_MUXB0__VARB_2__SHIFT) |
		(0x3 << UVD_MPC_SET_MUXB0__VARB_3__SHIFT) |
		(0x4 << UVD_MPC_SET_MUXB0__VARB_4__SHIFT)));

	WREG32_SOC15(UVD, 0, mmUVD_MPC_SET_MUX,
		((0x0 << UVD_MPC_SET_MUX__SET_0__SHIFT) |
		(0x1 << UVD_MPC_SET_MUX__SET_1__SHIFT) |
		(0x2 << UVD_MPC_SET_MUX__SET_2__SHIFT)));

	vcn_v1_0_mc_resume_spg_mode(adev);

	WREG32_SOC15(UVD, 0, mmUVD_REG_XX_MASK_1_0, 0x10);
	WREG32_SOC15(UVD, 0, mmUVD_RBC_XX_IB_REG_CHECK_1_0,
		RREG32_SOC15(UVD, 0, mmUVD_RBC_XX_IB_REG_CHECK_1_0) | 0x3);

	/* enable VCPU घड़ी */
	WREG32_SOC15(UVD, 0, mmUVD_VCPU_CNTL, UVD_VCPU_CNTL__CLK_EN_MASK);

	/* boot up the VCPU */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_SOFT_RESET), 0,
			~UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);

	/* enable UMC */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_LMI_CTRL2), 0,
			~UVD_LMI_CTRL2__STALL_ARB_UMC_MASK);

	पंचांगp = RREG32_SOC15(UVD, 0, mmUVD_SOFT_RESET);
	पंचांगp &= ~UVD_SOFT_RESET__LMI_SOFT_RESET_MASK;
	पंचांगp &= ~UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK;
	WREG32_SOC15(UVD, 0, mmUVD_SOFT_RESET, पंचांगp);

	क्रम (i = 0; i < 10; ++i) अणु
		uपूर्णांक32_t status;

		क्रम (j = 0; j < 100; ++j) अणु
			status = RREG32_SOC15(UVD, 0, mmUVD_STATUS);
			अगर (status & UVD_STATUS__IDLE)
				अवरोध;
			mdelay(10);
		पूर्ण
		r = 0;
		अगर (status & UVD_STATUS__IDLE)
			अवरोध;

		DRM_ERROR("VCN decode not responding, trying to reset the VCPU!!!\n");
		WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_SOFT_RESET),
				UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK,
				~UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
		mdelay(10);
		WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_SOFT_RESET), 0,
				~UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
		mdelay(10);
		r = -1;
	पूर्ण

	अगर (r) अणु
		DRM_ERROR("VCN decode not responding, giving up!!!\n");
		वापस r;
	पूर्ण
	/* enable master पूर्णांकerrupt */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_MASTINT_EN),
		UVD_MASTINT_EN__VCPU_EN_MASK, ~UVD_MASTINT_EN__VCPU_EN_MASK);

	/* enable प्रणाली पूर्णांकerrupt क्रम JRBC, TODO: move to set पूर्णांकerrupt*/
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_SYS_INT_EN),
		UVD_SYS_INT_EN__UVD_JRBC_EN_MASK,
		~UVD_SYS_INT_EN__UVD_JRBC_EN_MASK);

	/* clear the busy bit of UVD_STATUS */
	पंचांगp = RREG32_SOC15(UVD, 0, mmUVD_STATUS) & ~UVD_STATUS__UVD_BUSY;
	WREG32_SOC15(UVD, 0, mmUVD_STATUS, पंचांगp);

	/* क्रमce RBC पूर्णांकo idle state */
	rb_bufsz = order_base_2(ring->ring_size);
	पंचांगp = REG_SET_FIELD(0, UVD_RBC_RB_CNTL, RB_BUFSZ, rb_bufsz);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_BLKSZ, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_FETCH, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_UPDATE, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_RPTR_WR_EN, 1);
	WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_CNTL, पंचांगp);

	/* set the ग_लिखो poपूर्णांकer delay */
	WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_WPTR_CNTL, 0);

	/* set the wb address */
	WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_RPTR_ADDR,
			(upper_32_bits(ring->gpu_addr) >> 2));

	/* program the RB_BASE क्रम ring buffer */
	WREG32_SOC15(UVD, 0, mmUVD_LMI_RBC_RB_64BIT_BAR_LOW,
			lower_32_bits(ring->gpu_addr));
	WREG32_SOC15(UVD, 0, mmUVD_LMI_RBC_RB_64BIT_BAR_HIGH,
			upper_32_bits(ring->gpu_addr));

	/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
	WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_RPTR, 0);

	WREG32_SOC15(UVD, 0, mmUVD_SCRATCH2, 0);

	ring->wptr = RREG32_SOC15(UVD, 0, mmUVD_RBC_RB_RPTR);
	WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_WPTR,
			lower_32_bits(ring->wptr));

	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_RBC_RB_CNTL), 0,
			~UVD_RBC_RB_CNTL__RB_NO_FETCH_MASK);

	ring = &adev->vcn.inst->ring_enc[0];
	WREG32_SOC15(UVD, 0, mmUVD_RB_RPTR, lower_32_bits(ring->wptr));
	WREG32_SOC15(UVD, 0, mmUVD_RB_WPTR, lower_32_bits(ring->wptr));
	WREG32_SOC15(UVD, 0, mmUVD_RB_BASE_LO, ring->gpu_addr);
	WREG32_SOC15(UVD, 0, mmUVD_RB_BASE_HI, upper_32_bits(ring->gpu_addr));
	WREG32_SOC15(UVD, 0, mmUVD_RB_SIZE, ring->ring_size / 4);

	ring = &adev->vcn.inst->ring_enc[1];
	WREG32_SOC15(UVD, 0, mmUVD_RB_RPTR2, lower_32_bits(ring->wptr));
	WREG32_SOC15(UVD, 0, mmUVD_RB_WPTR2, lower_32_bits(ring->wptr));
	WREG32_SOC15(UVD, 0, mmUVD_RB_BASE_LO2, ring->gpu_addr);
	WREG32_SOC15(UVD, 0, mmUVD_RB_BASE_HI2, upper_32_bits(ring->gpu_addr));
	WREG32_SOC15(UVD, 0, mmUVD_RB_SIZE2, ring->ring_size / 4);

	jpeg_v1_0_start(adev, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v1_0_start_dpg_mode(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring = &adev->vcn.inst->ring_dec;
	uपूर्णांक32_t rb_bufsz, पंचांगp;
	uपूर्णांक32_t lmi_swap_cntl;

	/* disable byte swapping */
	lmi_swap_cntl = 0;

	vcn_1_0_enable_अटल_घातer_gating(adev);

	/* enable dynamic घातer gating mode */
	पंचांगp = RREG32_SOC15(UVD, 0, mmUVD_POWER_STATUS);
	पंचांगp |= UVD_POWER_STATUS__UVD_PG_MODE_MASK;
	पंचांगp |= UVD_POWER_STATUS__UVD_PG_EN_MASK;
	WREG32_SOC15(UVD, 0, mmUVD_POWER_STATUS, पंचांगp);

	/* enable घड़ी gating */
	vcn_v1_0_घड़ी_gating_dpg_mode(adev, 0);

	/* enable VCPU घड़ी */
	पंचांगp = (0xFF << UVD_VCPU_CNTL__PRB_TIMEOUT_VAL__SHIFT);
	पंचांगp |= UVD_VCPU_CNTL__CLK_EN_MASK;
	पंचांगp |= UVD_VCPU_CNTL__MIF_WR_LOW_THRESHOLD_BP_MASK;
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_VCPU_CNTL, पंचांगp, 0xFFFFFFFF, 0);

	/* disable पूर्णांकerupt */
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MASTINT_EN,
			0, UVD_MASTINT_EN__VCPU_EN_MASK, 0);

	/* initialize VCN memory controller */
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_LMI_CTRL,
		(8 << UVD_LMI_CTRL__WRITE_CLEAN_TIMER__SHIFT) |
		UVD_LMI_CTRL__WRITE_CLEAN_TIMER_EN_MASK |
		UVD_LMI_CTRL__DATA_COHERENCY_EN_MASK |
		UVD_LMI_CTRL__VCPU_DATA_COHERENCY_EN_MASK |
		UVD_LMI_CTRL__REQ_MODE_MASK |
		UVD_LMI_CTRL__CRC_RESET_MASK |
		UVD_LMI_CTRL__MASK_MC_URGENT_MASK |
		0x00100000L, 0xFFFFFFFF, 0);

#अगर_घोषित __BIG_ENDIAN
	/* swap (8 in 32) RB and IB */
	lmi_swap_cntl = 0xa;
#पूर्ण_अगर
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_LMI_SWAP_CNTL, lmi_swap_cntl, 0xFFFFFFFF, 0);

	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MPC_CNTL,
		0x2 << UVD_MPC_CNTL__REPLACEMENT_MODE__SHIFT, 0xFFFFFFFF, 0);

	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MPC_SET_MUXA0,
		((0x1 << UVD_MPC_SET_MUXA0__VARA_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUXA0__VARA_2__SHIFT) |
		 (0x3 << UVD_MPC_SET_MUXA0__VARA_3__SHIFT) |
		 (0x4 << UVD_MPC_SET_MUXA0__VARA_4__SHIFT)), 0xFFFFFFFF, 0);

	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MPC_SET_MUXB0,
		((0x1 << UVD_MPC_SET_MUXB0__VARB_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUXB0__VARB_2__SHIFT) |
		 (0x3 << UVD_MPC_SET_MUXB0__VARB_3__SHIFT) |
		 (0x4 << UVD_MPC_SET_MUXB0__VARB_4__SHIFT)), 0xFFFFFFFF, 0);

	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MPC_SET_MUX,
		((0x0 << UVD_MPC_SET_MUX__SET_0__SHIFT) |
		 (0x1 << UVD_MPC_SET_MUX__SET_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUX__SET_2__SHIFT)), 0xFFFFFFFF, 0);

	vcn_v1_0_mc_resume_dpg_mode(adev);

	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_REG_XX_MASK, 0x10, 0xFFFFFFFF, 0);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_RBC_XX_IB_REG_CHECK, 0x3, 0xFFFFFFFF, 0);

	/* boot up the VCPU */
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_SOFT_RESET, 0, 0xFFFFFFFF, 0);

	/* enable UMC */
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_LMI_CTRL2,
		0x1F << UVD_LMI_CTRL2__RE_OFLD_MIF_WR_REQ_NUM__SHIFT,
		0xFFFFFFFF, 0);

	/* enable master पूर्णांकerrupt */
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MASTINT_EN,
			UVD_MASTINT_EN__VCPU_EN_MASK, UVD_MASTINT_EN__VCPU_EN_MASK, 0);

	vcn_v1_0_घड़ी_gating_dpg_mode(adev, 1);
	/* setup mmUVD_LMI_CTRL */
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_LMI_CTRL,
		(8 << UVD_LMI_CTRL__WRITE_CLEAN_TIMER__SHIFT) |
		UVD_LMI_CTRL__WRITE_CLEAN_TIMER_EN_MASK |
		UVD_LMI_CTRL__DATA_COHERENCY_EN_MASK |
		UVD_LMI_CTRL__VCPU_DATA_COHERENCY_EN_MASK |
		UVD_LMI_CTRL__REQ_MODE_MASK |
		UVD_LMI_CTRL__CRC_RESET_MASK |
		UVD_LMI_CTRL__MASK_MC_URGENT_MASK |
		0x00100000L, 0xFFFFFFFF, 1);

	पंचांगp = adev->gfx.config.gb_addr_config;
	/* setup VCN global tiling रेजिस्टरs */
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_JPEG_ADDR_CONFIG, पंचांगp, 0xFFFFFFFF, 1);
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_JPEG_UV_ADDR_CONFIG, पंचांगp, 0xFFFFFFFF, 1);

	/* enable System Interrupt क्रम JRBC */
	WREG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_SYS_INT_EN,
									UVD_SYS_INT_EN__UVD_JRBC_EN_MASK, 0xFFFFFFFF, 1);

	/* क्रमce RBC पूर्णांकo idle state */
	rb_bufsz = order_base_2(ring->ring_size);
	पंचांगp = REG_SET_FIELD(0, UVD_RBC_RB_CNTL, RB_BUFSZ, rb_bufsz);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_BLKSZ, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_FETCH, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_UPDATE, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_RPTR_WR_EN, 1);
	WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_CNTL, पंचांगp);

	/* set the ग_लिखो poपूर्णांकer delay */
	WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_WPTR_CNTL, 0);

	/* set the wb address */
	WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_RPTR_ADDR,
								(upper_32_bits(ring->gpu_addr) >> 2));

	/* program the RB_BASE क्रम ring buffer */
	WREG32_SOC15(UVD, 0, mmUVD_LMI_RBC_RB_64BIT_BAR_LOW,
								lower_32_bits(ring->gpu_addr));
	WREG32_SOC15(UVD, 0, mmUVD_LMI_RBC_RB_64BIT_BAR_HIGH,
								upper_32_bits(ring->gpu_addr));

	/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
	WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_RPTR, 0);

	WREG32_SOC15(UVD, 0, mmUVD_SCRATCH2, 0);

	ring->wptr = RREG32_SOC15(UVD, 0, mmUVD_RBC_RB_RPTR);
	WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_WPTR,
								lower_32_bits(ring->wptr));

	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_RBC_RB_CNTL), 0,
			~UVD_RBC_RB_CNTL__RB_NO_FETCH_MASK);

	jpeg_v1_0_start(adev, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v1_0_start(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG)
		r = vcn_v1_0_start_dpg_mode(adev);
	अन्यथा
		r = vcn_v1_0_start_spg_mode(adev);
	वापस r;
पूर्ण

/**
 * vcn_v1_0_stop - stop VCN block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * stop the VCN block
 */
अटल पूर्णांक vcn_v1_0_stop_spg_mode(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक पंचांगp;

	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_STATUS, UVD_STATUS__IDLE, 0x7);

	पंचांगp = UVD_LMI_STATUS__VCPU_LMI_WRITE_CLEAN_MASK |
		UVD_LMI_STATUS__READ_CLEAN_MASK |
		UVD_LMI_STATUS__WRITE_CLEAN_MASK |
		UVD_LMI_STATUS__WRITE_CLEAN_RAW_MASK;
	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_LMI_STATUS, पंचांगp, पंचांगp);

	/* stall UMC channel */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_LMI_CTRL2),
		UVD_LMI_CTRL2__STALL_ARB_UMC_MASK,
		~UVD_LMI_CTRL2__STALL_ARB_UMC_MASK);

	पंचांगp = UVD_LMI_STATUS__UMC_READ_CLEAN_RAW_MASK |
		UVD_LMI_STATUS__UMC_WRITE_CLEAN_RAW_MASK;
	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_LMI_STATUS, पंचांगp, पंचांगp);

	/* disable VCPU घड़ी */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_VCPU_CNTL), 0,
		~UVD_VCPU_CNTL__CLK_EN_MASK);

	/* reset LMI UMC/LMI */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_SOFT_RESET),
		UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK,
		~UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK);

	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_SOFT_RESET),
		UVD_SOFT_RESET__LMI_SOFT_RESET_MASK,
		~UVD_SOFT_RESET__LMI_SOFT_RESET_MASK);

	/* put VCPU पूर्णांकo reset */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_SOFT_RESET),
		UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK,
		~UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);

	WREG32_SOC15(UVD, 0, mmUVD_STATUS, 0);

	vcn_v1_0_enable_घड़ी_gating(adev);
	vcn_1_0_enable_अटल_घातer_gating(adev);
	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v1_0_stop_dpg_mode(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t पंचांगp;

	/* Wait क्रम घातer status to be UVD_POWER_STATUS__UVD_POWER_STATUS_TILES_OFF */
	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_POWER_STATUS,
			UVD_POWER_STATUS__UVD_POWER_STATUS_TILES_OFF,
			UVD_POWER_STATUS__UVD_POWER_STATUS_MASK);

	/* रुको क्रम पढ़ो ptr to be equal to ग_लिखो ptr */
	पंचांगp = RREG32_SOC15(UVD, 0, mmUVD_RB_WPTR);
	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_RB_RPTR, पंचांगp, 0xFFFFFFFF);

	पंचांगp = RREG32_SOC15(UVD, 0, mmUVD_RB_WPTR2);
	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_RB_RPTR2, पंचांगp, 0xFFFFFFFF);

	पंचांगp = RREG32_SOC15(UVD, 0, mmUVD_JRBC_RB_WPTR);
	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_JRBC_RB_RPTR, पंचांगp, 0xFFFFFFFF);

	पंचांगp = RREG32_SOC15(UVD, 0, mmUVD_RBC_RB_WPTR) & 0x7FFFFFFF;
	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_RBC_RB_RPTR, पंचांगp, 0xFFFFFFFF);

	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_POWER_STATUS,
		UVD_POWER_STATUS__UVD_POWER_STATUS_TILES_OFF,
		UVD_POWER_STATUS__UVD_POWER_STATUS_MASK);

	/* disable dynamic घातer gating mode */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_POWER_STATUS), 0,
			~UVD_POWER_STATUS__UVD_PG_MODE_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v1_0_stop(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG)
		r = vcn_v1_0_stop_dpg_mode(adev);
	अन्यथा
		r = vcn_v1_0_stop_spg_mode(adev);

	वापस r;
पूर्ण

अटल पूर्णांक vcn_v1_0_छोड़ो_dpg_mode(काष्ठा amdgpu_device *adev,
				पूर्णांक inst_idx, काष्ठा dpg_छोड़ो_state *new_state)
अणु
	पूर्णांक ret_code;
	uपूर्णांक32_t reg_data = 0;
	uपूर्णांक32_t reg_data2 = 0;
	काष्ठा amdgpu_ring *ring;

	/* छोड़ो/unछोड़ो अगर state is changed */
	अगर (adev->vcn.inst[inst_idx].छोड़ो_state.fw_based != new_state->fw_based) अणु
		DRM_DEBUG("dpg pause state changed %d:%d -> %d:%d",
			adev->vcn.inst[inst_idx].छोड़ो_state.fw_based,
			adev->vcn.inst[inst_idx].छोड़ो_state.jpeg,
			new_state->fw_based, new_state->jpeg);

		reg_data = RREG32_SOC15(UVD, 0, mmUVD_DPG_PAUSE) &
			(~UVD_DPG_PAUSE__NJ_PAUSE_DPG_ACK_MASK);

		अगर (new_state->fw_based == VCN_DPG_STATE__PAUSE) अणु
			ret_code = 0;

			अगर (!(reg_data & UVD_DPG_PAUSE__JPEG_PAUSE_DPG_ACK_MASK))
				ret_code = SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_POWER_STATUS,
						   UVD_POWER_STATUS__UVD_POWER_STATUS_TILES_OFF,
						   UVD_POWER_STATUS__UVD_POWER_STATUS_MASK);

			अगर (!ret_code) अणु
				/* छोड़ो DPG non-jpeg */
				reg_data |= UVD_DPG_PAUSE__NJ_PAUSE_DPG_REQ_MASK;
				WREG32_SOC15(UVD, 0, mmUVD_DPG_PAUSE, reg_data);
				SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_DPG_PAUSE,
						   UVD_DPG_PAUSE__NJ_PAUSE_DPG_ACK_MASK,
						   UVD_DPG_PAUSE__NJ_PAUSE_DPG_ACK_MASK);

				/* Restore */
				ring = &adev->vcn.inst->ring_enc[0];
				WREG32_SOC15(UVD, 0, mmUVD_RB_BASE_LO, ring->gpu_addr);
				WREG32_SOC15(UVD, 0, mmUVD_RB_BASE_HI, upper_32_bits(ring->gpu_addr));
				WREG32_SOC15(UVD, 0, mmUVD_RB_SIZE, ring->ring_size / 4);
				WREG32_SOC15(UVD, 0, mmUVD_RB_RPTR, lower_32_bits(ring->wptr));
				WREG32_SOC15(UVD, 0, mmUVD_RB_WPTR, lower_32_bits(ring->wptr));

				ring = &adev->vcn.inst->ring_enc[1];
				WREG32_SOC15(UVD, 0, mmUVD_RB_BASE_LO2, ring->gpu_addr);
				WREG32_SOC15(UVD, 0, mmUVD_RB_BASE_HI2, upper_32_bits(ring->gpu_addr));
				WREG32_SOC15(UVD, 0, mmUVD_RB_SIZE2, ring->ring_size / 4);
				WREG32_SOC15(UVD, 0, mmUVD_RB_RPTR2, lower_32_bits(ring->wptr));
				WREG32_SOC15(UVD, 0, mmUVD_RB_WPTR2, lower_32_bits(ring->wptr));

				ring = &adev->vcn.inst->ring_dec;
				WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_WPTR,
						   RREG32_SOC15(UVD, 0, mmUVD_SCRATCH2) & 0x7FFFFFFF);
				SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_POWER_STATUS,
						   UVD_PGFSM_CONFIG__UVDM_UVDU_PWR_ON,
						   UVD_POWER_STATUS__UVD_POWER_STATUS_MASK);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* unछोड़ो dpg non-jpeg, no need to रुको */
			reg_data &= ~UVD_DPG_PAUSE__NJ_PAUSE_DPG_REQ_MASK;
			WREG32_SOC15(UVD, 0, mmUVD_DPG_PAUSE, reg_data);
		पूर्ण
		adev->vcn.inst[inst_idx].छोड़ो_state.fw_based = new_state->fw_based;
	पूर्ण

	/* छोड़ो/unछोड़ो अगर state is changed */
	अगर (adev->vcn.inst[inst_idx].छोड़ो_state.jpeg != new_state->jpeg) अणु
		DRM_DEBUG("dpg pause state changed %d:%d -> %d:%d",
			adev->vcn.inst[inst_idx].छोड़ो_state.fw_based,
			adev->vcn.inst[inst_idx].छोड़ो_state.jpeg,
			new_state->fw_based, new_state->jpeg);

		reg_data = RREG32_SOC15(UVD, 0, mmUVD_DPG_PAUSE) &
			(~UVD_DPG_PAUSE__JPEG_PAUSE_DPG_ACK_MASK);

		अगर (new_state->jpeg == VCN_DPG_STATE__PAUSE) अणु
			ret_code = 0;

			अगर (!(reg_data & UVD_DPG_PAUSE__NJ_PAUSE_DPG_ACK_MASK))
				ret_code = SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_POWER_STATUS,
						   UVD_POWER_STATUS__UVD_POWER_STATUS_TILES_OFF,
						   UVD_POWER_STATUS__UVD_POWER_STATUS_MASK);

			अगर (!ret_code) अणु
				/* Make sure JPRG Snoop is disabled beक्रमe sending the छोड़ो */
				reg_data2 = RREG32_SOC15(UVD, 0, mmUVD_POWER_STATUS);
				reg_data2 |= UVD_POWER_STATUS__JRBC_SNOOP_DIS_MASK;
				WREG32_SOC15(UVD, 0, mmUVD_POWER_STATUS, reg_data2);

				/* छोड़ो DPG jpeg */
				reg_data |= UVD_DPG_PAUSE__JPEG_PAUSE_DPG_REQ_MASK;
				WREG32_SOC15(UVD, 0, mmUVD_DPG_PAUSE, reg_data);
				SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_DPG_PAUSE,
							UVD_DPG_PAUSE__JPEG_PAUSE_DPG_ACK_MASK,
							UVD_DPG_PAUSE__JPEG_PAUSE_DPG_ACK_MASK);

				/* Restore */
				ring = &adev->jpeg.inst->ring_dec;
				WREG32_SOC15(UVD, 0, mmUVD_LMI_JRBC_RB_VMID, 0);
				WREG32_SOC15(UVD, 0, mmUVD_JRBC_RB_CNTL,
							UVD_JRBC_RB_CNTL__RB_NO_FETCH_MASK |
							UVD_JRBC_RB_CNTL__RB_RPTR_WR_EN_MASK);
				WREG32_SOC15(UVD, 0, mmUVD_LMI_JRBC_RB_64BIT_BAR_LOW,
							lower_32_bits(ring->gpu_addr));
				WREG32_SOC15(UVD, 0, mmUVD_LMI_JRBC_RB_64BIT_BAR_HIGH,
							upper_32_bits(ring->gpu_addr));
				WREG32_SOC15(UVD, 0, mmUVD_JRBC_RB_RPTR, ring->wptr);
				WREG32_SOC15(UVD, 0, mmUVD_JRBC_RB_WPTR, ring->wptr);
				WREG32_SOC15(UVD, 0, mmUVD_JRBC_RB_CNTL,
							UVD_JRBC_RB_CNTL__RB_RPTR_WR_EN_MASK);

				ring = &adev->vcn.inst->ring_dec;
				WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_WPTR,
						   RREG32_SOC15(UVD, 0, mmUVD_SCRATCH2) & 0x7FFFFFFF);
				SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_POWER_STATUS,
						   UVD_PGFSM_CONFIG__UVDM_UVDU_PWR_ON,
						   UVD_POWER_STATUS__UVD_POWER_STATUS_MASK);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* unछोड़ो dpg jpeg, no need to रुको */
			reg_data &= ~UVD_DPG_PAUSE__JPEG_PAUSE_DPG_REQ_MASK;
			WREG32_SOC15(UVD, 0, mmUVD_DPG_PAUSE, reg_data);
		पूर्ण
		adev->vcn.inst[inst_idx].छोड़ो_state.jpeg = new_state->jpeg;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool vcn_v1_0_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस (RREG32_SOC15(VCN, 0, mmUVD_STATUS) == UVD_STATUS__IDLE);
पूर्ण

अटल पूर्णांक vcn_v1_0_रुको_क्रम_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक ret;

	ret = SOC15_WAIT_ON_RREG(VCN, 0, mmUVD_STATUS, UVD_STATUS__IDLE,
		UVD_STATUS__IDLE);

	वापस ret;
पूर्ण

अटल पूर्णांक vcn_v1_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	bool enable = (state == AMD_CG_STATE_GATE);

	अगर (enable) अणु
		/* रुको क्रम STATUS to clear */
		अगर (!vcn_v1_0_is_idle(handle))
			वापस -EBUSY;
		vcn_v1_0_enable_घड़ी_gating(adev);
	पूर्ण अन्यथा अणु
		/* disable HW gating and enable Sw gating */
		vcn_v1_0_disable_घड़ी_gating(adev);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * vcn_v1_0_dec_ring_get_rptr - get पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t vcn_v1_0_dec_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32_SOC15(UVD, 0, mmUVD_RBC_RB_RPTR);
पूर्ण

/**
 * vcn_v1_0_dec_ring_get_wptr - get ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t vcn_v1_0_dec_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32_SOC15(UVD, 0, mmUVD_RBC_RB_WPTR);
पूर्ण

/**
 * vcn_v1_0_dec_ring_set_wptr - set ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम vcn_v1_0_dec_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG)
		WREG32_SOC15(UVD, 0, mmUVD_SCRATCH2,
			lower_32_bits(ring->wptr) | 0x80000000);

	WREG32_SOC15(UVD, 0, mmUVD_RBC_RB_WPTR, lower_32_bits(ring->wptr));
पूर्ण

/**
 * vcn_v1_0_dec_ring_insert_start - insert a start command
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Write a start command to the ring.
 */
अटल व्योम vcn_v1_0_dec_ring_insert_start(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_ring_ग_लिखो(ring, VCN_DEC_CMD_PACKET_START << 1);
पूर्ण

/**
 * vcn_v1_0_dec_ring_insert_end - insert a end command
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Write a end command to the ring.
 */
अटल व्योम vcn_v1_0_dec_ring_insert_end(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_ring_ग_लिखो(ring, VCN_DEC_CMD_PACKET_END << 1);
पूर्ण

/**
 * vcn_v1_0_dec_ring_emit_fence - emit an fence & trap command
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @addr: address
 * @seq: sequence number
 * @flags: fence related flags
 *
 * Write a fence and a trap command to the ring.
 */
अटल व्योम vcn_v1_0_dec_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr, u64 seq,
				     अचिन्हित flags)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	WARN_ON(flags & AMDGPU_FENCE_FLAG_64BIT);

	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_CONTEXT_ID), 0));
	amdgpu_ring_ग_लिखो(ring, seq);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_ring_ग_लिखो(ring, addr & 0xffffffff);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA1), 0));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr) & 0xff);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_ring_ग_लिखो(ring, VCN_DEC_CMD_FENCE << 1);

	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA1), 0));
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_ring_ग_लिखो(ring, VCN_DEC_CMD_TRAP << 1);
पूर्ण

/**
 * vcn_v1_0_dec_ring_emit_ib - execute indirect buffer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @job: job to retrieve vmid from
 * @ib: indirect buffer to execute
 * @flags: unused
 *
 * Write ring commands to execute the indirect buffer
 */
अटल व्योम vcn_v1_0_dec_ring_emit_ib(काष्ठा amdgpu_ring *ring,
					काष्ठा amdgpu_job *job,
					काष्ठा amdgpu_ib *ib,
					uपूर्णांक32_t flags)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	अचिन्हित vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_LMI_RBC_IB_VMID), 0));
	amdgpu_ring_ग_लिखो(ring, vmid);

	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_LMI_RBC_IB_64BIT_BAR_LOW), 0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_LMI_RBC_IB_64BIT_BAR_HIGH), 0));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_RBC_IB_SIZE), 0));
	amdgpu_ring_ग_लिखो(ring, ib->length_dw);
पूर्ण

अटल व्योम vcn_v1_0_dec_ring_emit_reg_रुको(काष्ठा amdgpu_ring *ring,
					    uपूर्णांक32_t reg, uपूर्णांक32_t val,
					    uपूर्णांक32_t mask)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_ring_ग_लिखो(ring, reg << 2);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA1), 0));
	amdgpu_ring_ग_लिखो(ring, val);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GP_SCRATCH8), 0));
	amdgpu_ring_ग_लिखो(ring, mask);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_ring_ग_लिखो(ring, VCN_DEC_CMD_REG_READ_COND_WAIT << 1);
पूर्ण

अटल व्योम vcn_v1_0_dec_ring_emit_vm_flush(काष्ठा amdgpu_ring *ring,
					    अचिन्हित vmid, uपूर्णांक64_t pd_addr)
अणु
	काष्ठा amdgpu_vmhub *hub = &ring->adev->vmhub[ring->funcs->vmhub];
	uपूर्णांक32_t data0, data1, mask;

	pd_addr = amdgpu_gmc_emit_flush_gpu_tlb(ring, vmid, pd_addr);

	/* रुको क्रम रेजिस्टर ग_लिखो */
	data0 = hub->ctx0_ptb_addr_lo32 + vmid * hub->ctx_addr_distance;
	data1 = lower_32_bits(pd_addr);
	mask = 0xffffffff;
	vcn_v1_0_dec_ring_emit_reg_रुको(ring, data0, data1, mask);
पूर्ण

अटल व्योम vcn_v1_0_dec_ring_emit_wreg(काष्ठा amdgpu_ring *ring,
					uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_ring_ग_लिखो(ring, reg << 2);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA1), 0));
	amdgpu_ring_ग_लिखो(ring, val);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_ring_ग_लिखो(ring, VCN_DEC_CMD_WRITE_REG << 1);
पूर्ण

/**
 * vcn_v1_0_enc_ring_get_rptr - get enc पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware enc पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t vcn_v1_0_enc_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring == &adev->vcn.inst->ring_enc[0])
		वापस RREG32_SOC15(UVD, 0, mmUVD_RB_RPTR);
	अन्यथा
		वापस RREG32_SOC15(UVD, 0, mmUVD_RB_RPTR2);
पूर्ण

 /**
 * vcn_v1_0_enc_ring_get_wptr - get enc ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware enc ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t vcn_v1_0_enc_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring == &adev->vcn.inst->ring_enc[0])
		वापस RREG32_SOC15(UVD, 0, mmUVD_RB_WPTR);
	अन्यथा
		वापस RREG32_SOC15(UVD, 0, mmUVD_RB_WPTR2);
पूर्ण

 /**
 * vcn_v1_0_enc_ring_set_wptr - set enc ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the enc ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम vcn_v1_0_enc_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring == &adev->vcn.inst->ring_enc[0])
		WREG32_SOC15(UVD, 0, mmUVD_RB_WPTR,
			lower_32_bits(ring->wptr));
	अन्यथा
		WREG32_SOC15(UVD, 0, mmUVD_RB_WPTR2,
			lower_32_bits(ring->wptr));
पूर्ण

/**
 * vcn_v1_0_enc_ring_emit_fence - emit an enc fence & trap command
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @addr: address
 * @seq: sequence number
 * @flags: fence related flags
 *
 * Write enc a fence and a trap command to the ring.
 */
अटल व्योम vcn_v1_0_enc_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr,
			u64 seq, अचिन्हित flags)
अणु
	WARN_ON(flags & AMDGPU_FENCE_FLAG_64BIT);

	amdgpu_ring_ग_लिखो(ring, VCN_ENC_CMD_FENCE);
	amdgpu_ring_ग_लिखो(ring, addr);
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, seq);
	amdgpu_ring_ग_लिखो(ring, VCN_ENC_CMD_TRAP);
पूर्ण

अटल व्योम vcn_v1_0_enc_ring_insert_end(काष्ठा amdgpu_ring *ring)
अणु
	amdgpu_ring_ग_लिखो(ring, VCN_ENC_CMD_END);
पूर्ण

/**
 * vcn_v1_0_enc_ring_emit_ib - enc execute indirect buffer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @job: job to retrive vmid from
 * @ib: indirect buffer to execute
 * @flags: unused
 *
 * Write enc ring commands to execute the indirect buffer
 */
अटल व्योम vcn_v1_0_enc_ring_emit_ib(काष्ठा amdgpu_ring *ring,
					काष्ठा amdgpu_job *job,
					काष्ठा amdgpu_ib *ib,
					uपूर्णांक32_t flags)
अणु
	अचिन्हित vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_ring_ग_लिखो(ring, VCN_ENC_CMD_IB);
	amdgpu_ring_ग_लिखो(ring, vmid);
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, ib->length_dw);
पूर्ण

अटल व्योम vcn_v1_0_enc_ring_emit_reg_रुको(काष्ठा amdgpu_ring *ring,
					    uपूर्णांक32_t reg, uपूर्णांक32_t val,
					    uपूर्णांक32_t mask)
अणु
	amdgpu_ring_ग_लिखो(ring, VCN_ENC_CMD_REG_WAIT);
	amdgpu_ring_ग_लिखो(ring, reg << 2);
	amdgpu_ring_ग_लिखो(ring, mask);
	amdgpu_ring_ग_लिखो(ring, val);
पूर्ण

अटल व्योम vcn_v1_0_enc_ring_emit_vm_flush(काष्ठा amdgpu_ring *ring,
					    अचिन्हित पूर्णांक vmid, uपूर्णांक64_t pd_addr)
अणु
	काष्ठा amdgpu_vmhub *hub = &ring->adev->vmhub[ring->funcs->vmhub];

	pd_addr = amdgpu_gmc_emit_flush_gpu_tlb(ring, vmid, pd_addr);

	/* रुको क्रम reg ग_लिखोs */
	vcn_v1_0_enc_ring_emit_reg_रुको(ring, hub->ctx0_ptb_addr_lo32 +
					vmid * hub->ctx_addr_distance,
					lower_32_bits(pd_addr), 0xffffffff);
पूर्ण

अटल व्योम vcn_v1_0_enc_ring_emit_wreg(काष्ठा amdgpu_ring *ring,
					uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	amdgpu_ring_ग_लिखो(ring, VCN_ENC_CMD_REG_WRITE);
	amdgpu_ring_ग_लिखो(ring,	reg << 2);
	amdgpu_ring_ग_लिखो(ring, val);
पूर्ण

अटल पूर्णांक vcn_v1_0_set_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v1_0_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	DRM_DEBUG("IH: VCN TRAP\n");

	चयन (entry->src_id) अणु
	हाल 124:
		amdgpu_fence_process(&adev->vcn.inst->ring_dec);
		अवरोध;
	हाल 119:
		amdgpu_fence_process(&adev->vcn.inst->ring_enc[0]);
		अवरोध;
	हाल 120:
		amdgpu_fence_process(&adev->vcn.inst->ring_enc[1]);
		अवरोध;
	शेष:
		DRM_ERROR("Unhandled interrupt: %d %d\n",
			  entry->src_id, entry->src_data[0]);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vcn_v1_0_dec_ring_insert_nop(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t count)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	पूर्णांक i;

	WARN_ON(ring->wptr % 2 || count % 2);

	क्रम (i = 0; i < count / 2; i++) अणु
		amdgpu_ring_ग_लिखो(ring, PACKET0(SOC15_REG_OFFSET(UVD, 0, mmUVD_NO_OP), 0));
		amdgpu_ring_ग_लिखो(ring, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक vcn_v1_0_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	/* This करोesn't actually घातergate the VCN block.
	 * That's करोne in the dpm code via the SMC.  This
	 * just re-inits the block as necessary.  The actual
	 * gating still happens in the dpm code.  We should
	 * revisit this when there is a cleaner line between
	 * the smc and the hw blocks
	 */
	पूर्णांक ret;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर(state == adev->vcn.cur_state)
		वापस 0;

	अगर (state == AMD_PG_STATE_GATE)
		ret = vcn_v1_0_stop(adev);
	अन्यथा
		ret = vcn_v1_0_start(adev);

	अगर(!ret)
		adev->vcn.cur_state = state;
	वापस ret;
पूर्ण

अटल व्योम vcn_v1_0_idle_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdgpu_device *adev =
		container_of(work, काष्ठा amdgpu_device, vcn.idle_work.work);
	अचिन्हित पूर्णांक fences = 0, i;

	क्रम (i = 0; i < adev->vcn.num_enc_rings; ++i)
		fences += amdgpu_fence_count_emitted(&adev->vcn.inst->ring_enc[i]);

	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG) अणु
		काष्ठा dpg_छोड़ो_state new_state;

		अगर (fences)
			new_state.fw_based = VCN_DPG_STATE__PAUSE;
		अन्यथा
			new_state.fw_based = VCN_DPG_STATE__UNPAUSE;

		अगर (amdgpu_fence_count_emitted(&adev->jpeg.inst->ring_dec))
			new_state.jpeg = VCN_DPG_STATE__PAUSE;
		अन्यथा
			new_state.jpeg = VCN_DPG_STATE__UNPAUSE;

		adev->vcn.छोड़ो_dpg_mode(adev, 0, &new_state);
	पूर्ण

	fences += amdgpu_fence_count_emitted(&adev->jpeg.inst->ring_dec);
	fences += amdgpu_fence_count_emitted(&adev->vcn.inst->ring_dec);

	अगर (fences == 0) अणु
		amdgpu_gfx_off_ctrl(adev, true);
		अगर (adev->pm.dpm_enabled)
			amdgpu_dpm_enable_uvd(adev, false);
		अन्यथा
			amdgpu_device_ip_set_घातergating_state(adev, AMD_IP_BLOCK_TYPE_VCN,
			       AMD_PG_STATE_GATE);
	पूर्ण अन्यथा अणु
		schedule_delayed_work(&adev->vcn.idle_work, VCN_IDLE_TIMEOUT);
	पूर्ण
पूर्ण

अटल व्योम vcn_v1_0_ring_begin_use(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा	amdgpu_device *adev = ring->adev;
	bool set_घड़ीs = !cancel_delayed_work_sync(&adev->vcn.idle_work);

	mutex_lock(&adev->vcn.vcn1_jpeg1_workaround);

	अगर (amdgpu_fence_रुको_empty(&ring->adev->jpeg.inst->ring_dec))
		DRM_ERROR("VCN dec: jpeg dec ring may not be empty\n");

	vcn_v1_0_set_pg_क्रम_begin_use(ring, set_घड़ीs);

पूर्ण

व्योम vcn_v1_0_set_pg_क्रम_begin_use(काष्ठा amdgpu_ring *ring, bool set_घड़ीs)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (set_घड़ीs) अणु
		amdgpu_gfx_off_ctrl(adev, false);
		अगर (adev->pm.dpm_enabled)
			amdgpu_dpm_enable_uvd(adev, true);
		अन्यथा
			amdgpu_device_ip_set_घातergating_state(adev, AMD_IP_BLOCK_TYPE_VCN,
			       AMD_PG_STATE_UNGATE);
	पूर्ण

	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG) अणु
		काष्ठा dpg_छोड़ो_state new_state;
		अचिन्हित पूर्णांक fences = 0, i;

		क्रम (i = 0; i < adev->vcn.num_enc_rings; ++i)
			fences += amdgpu_fence_count_emitted(&adev->vcn.inst->ring_enc[i]);

		अगर (fences)
			new_state.fw_based = VCN_DPG_STATE__PAUSE;
		अन्यथा
			new_state.fw_based = VCN_DPG_STATE__UNPAUSE;

		अगर (amdgpu_fence_count_emitted(&adev->jpeg.inst->ring_dec))
			new_state.jpeg = VCN_DPG_STATE__PAUSE;
		अन्यथा
			new_state.jpeg = VCN_DPG_STATE__UNPAUSE;

		अगर (ring->funcs->type == AMDGPU_RING_TYPE_VCN_ENC)
			new_state.fw_based = VCN_DPG_STATE__PAUSE;
		अन्यथा अगर (ring->funcs->type == AMDGPU_RING_TYPE_VCN_JPEG)
			new_state.jpeg = VCN_DPG_STATE__PAUSE;

		adev->vcn.छोड़ो_dpg_mode(adev, 0, &new_state);
	पूर्ण
पूर्ण

व्योम vcn_v1_0_ring_end_use(काष्ठा amdgpu_ring *ring)
अणु
	schedule_delayed_work(&ring->adev->vcn.idle_work, VCN_IDLE_TIMEOUT);
	mutex_unlock(&ring->adev->vcn.vcn1_jpeg1_workaround);
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs vcn_v1_0_ip_funcs = अणु
	.name = "vcn_v1_0",
	.early_init = vcn_v1_0_early_init,
	.late_init = शून्य,
	.sw_init = vcn_v1_0_sw_init,
	.sw_fini = vcn_v1_0_sw_fini,
	.hw_init = vcn_v1_0_hw_init,
	.hw_fini = vcn_v1_0_hw_fini,
	.suspend = vcn_v1_0_suspend,
	.resume = vcn_v1_0_resume,
	.is_idle = vcn_v1_0_is_idle,
	.रुको_क्रम_idle = vcn_v1_0_रुको_क्रम_idle,
	.check_soft_reset = शून्य /* vcn_v1_0_check_soft_reset */,
	.pre_soft_reset = शून्य /* vcn_v1_0_pre_soft_reset */,
	.soft_reset = शून्य /* vcn_v1_0_soft_reset */,
	.post_soft_reset = शून्य /* vcn_v1_0_post_soft_reset */,
	.set_घड़ीgating_state = vcn_v1_0_set_घड़ीgating_state,
	.set_घातergating_state = vcn_v1_0_set_घातergating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs vcn_v1_0_dec_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_VCN_DEC,
	.align_mask = 0xf,
	.support_64bit_ptrs = false,
	.no_user_fence = true,
	.vmhub = AMDGPU_MMHUB_0,
	.get_rptr = vcn_v1_0_dec_ring_get_rptr,
	.get_wptr = vcn_v1_0_dec_ring_get_wptr,
	.set_wptr = vcn_v1_0_dec_ring_set_wptr,
	.emit_frame_size =
		6 + 6 + /* hdp invalidate / flush */
		SOC15_FLUSH_GPU_TLB_NUM_WREG * 6 +
		SOC15_FLUSH_GPU_TLB_NUM_REG_WAIT * 8 +
		8 + /* vcn_v1_0_dec_ring_emit_vm_flush */
		14 + 14 + /* vcn_v1_0_dec_ring_emit_fence x2 vm fence */
		6,
	.emit_ib_size = 8, /* vcn_v1_0_dec_ring_emit_ib */
	.emit_ib = vcn_v1_0_dec_ring_emit_ib,
	.emit_fence = vcn_v1_0_dec_ring_emit_fence,
	.emit_vm_flush = vcn_v1_0_dec_ring_emit_vm_flush,
	.test_ring = amdgpu_vcn_dec_ring_test_ring,
	.test_ib = amdgpu_vcn_dec_ring_test_ib,
	.insert_nop = vcn_v1_0_dec_ring_insert_nop,
	.insert_start = vcn_v1_0_dec_ring_insert_start,
	.insert_end = vcn_v1_0_dec_ring_insert_end,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = vcn_v1_0_ring_begin_use,
	.end_use = vcn_v1_0_ring_end_use,
	.emit_wreg = vcn_v1_0_dec_ring_emit_wreg,
	.emit_reg_रुको = vcn_v1_0_dec_ring_emit_reg_रुको,
	.emit_reg_ग_लिखो_reg_रुको = amdgpu_ring_emit_reg_ग_लिखो_reg_रुको_helper,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs vcn_v1_0_enc_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_VCN_ENC,
	.align_mask = 0x3f,
	.nop = VCN_ENC_CMD_NO_OP,
	.support_64bit_ptrs = false,
	.no_user_fence = true,
	.vmhub = AMDGPU_MMHUB_0,
	.get_rptr = vcn_v1_0_enc_ring_get_rptr,
	.get_wptr = vcn_v1_0_enc_ring_get_wptr,
	.set_wptr = vcn_v1_0_enc_ring_set_wptr,
	.emit_frame_size =
		SOC15_FLUSH_GPU_TLB_NUM_WREG * 3 +
		SOC15_FLUSH_GPU_TLB_NUM_REG_WAIT * 4 +
		4 + /* vcn_v1_0_enc_ring_emit_vm_flush */
		5 + 5 + /* vcn_v1_0_enc_ring_emit_fence x2 vm fence */
		1, /* vcn_v1_0_enc_ring_insert_end */
	.emit_ib_size = 5, /* vcn_v1_0_enc_ring_emit_ib */
	.emit_ib = vcn_v1_0_enc_ring_emit_ib,
	.emit_fence = vcn_v1_0_enc_ring_emit_fence,
	.emit_vm_flush = vcn_v1_0_enc_ring_emit_vm_flush,
	.test_ring = amdgpu_vcn_enc_ring_test_ring,
	.test_ib = amdgpu_vcn_enc_ring_test_ib,
	.insert_nop = amdgpu_ring_insert_nop,
	.insert_end = vcn_v1_0_enc_ring_insert_end,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = vcn_v1_0_ring_begin_use,
	.end_use = vcn_v1_0_ring_end_use,
	.emit_wreg = vcn_v1_0_enc_ring_emit_wreg,
	.emit_reg_रुको = vcn_v1_0_enc_ring_emit_reg_रुको,
	.emit_reg_ग_लिखो_reg_रुको = amdgpu_ring_emit_reg_ग_लिखो_reg_रुको_helper,
पूर्ण;

अटल व्योम vcn_v1_0_set_dec_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->vcn.inst->ring_dec.funcs = &vcn_v1_0_dec_ring_vm_funcs;
	DRM_INFO("VCN decode is enabled in VM mode\n");
पूर्ण

अटल व्योम vcn_v1_0_set_enc_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->vcn.num_enc_rings; ++i)
		adev->vcn.inst->ring_enc[i].funcs = &vcn_v1_0_enc_ring_vm_funcs;

	DRM_INFO("VCN encode is enabled in VM mode\n");
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs vcn_v1_0_irq_funcs = अणु
	.set = vcn_v1_0_set_पूर्णांकerrupt_state,
	.process = vcn_v1_0_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम vcn_v1_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->vcn.inst->irq.num_types = adev->vcn.num_enc_rings + 2;
	adev->vcn.inst->irq.funcs = &vcn_v1_0_irq_funcs;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version vcn_v1_0_ip_block =
अणु
		.type = AMD_IP_BLOCK_TYPE_VCN,
		.major = 1,
		.minor = 0,
		.rev = 0,
		.funcs = &vcn_v1_0_ip_funcs,
पूर्ण;
