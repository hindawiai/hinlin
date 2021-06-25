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

#समावेश <linux/firmware.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_vcn.h"
#समावेश "amdgpu_pm.h"
#समावेश "soc15.h"
#समावेश "soc15d.h"
#समावेश "vcn_v2_0.h"
#समावेश "mmsch_v1_0.h"

#समावेश "vcn/vcn_2_5_offset.h"
#समावेश "vcn/vcn_2_5_sh_mask.h"
#समावेश "ivsrcid/vcn/irqsrcs_vcn_2_0.h"

#घोषणा mmUVD_CONTEXT_ID_INTERNAL_OFFSET			0x27
#घोषणा mmUVD_GPCOM_VCPU_CMD_INTERNAL_OFFSET			0x0f
#घोषणा mmUVD_GPCOM_VCPU_DATA0_INTERNAL_OFFSET			0x10
#घोषणा mmUVD_GPCOM_VCPU_DATA1_INTERNAL_OFFSET			0x11
#घोषणा mmUVD_NO_OP_INTERNAL_OFFSET				0x29
#घोषणा mmUVD_GP_SCRATCH8_INTERNAL_OFFSET			0x66
#घोषणा mmUVD_SCRATCH9_INTERNAL_OFFSET				0xc01d

#घोषणा mmUVD_LMI_RBC_IB_VMID_INTERNAL_OFFSET			0x431
#घोषणा mmUVD_LMI_RBC_IB_64BIT_BAR_LOW_INTERNAL_OFFSET		0x3b4
#घोषणा mmUVD_LMI_RBC_IB_64BIT_BAR_HIGH_INTERNAL_OFFSET		0x3b5
#घोषणा mmUVD_RBC_IB_SIZE_INTERNAL_OFFSET			0x25c

#घोषणा VCN25_MAX_HW_INSTANCES_ARCTURUS			2

अटल व्योम vcn_v2_5_set_dec_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम vcn_v2_5_set_enc_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम vcn_v2_5_set_irq_funcs(काष्ठा amdgpu_device *adev);
अटल पूर्णांक vcn_v2_5_set_घातergating_state(व्योम *handle,
				क्रमागत amd_घातergating_state state);
अटल पूर्णांक vcn_v2_5_छोड़ो_dpg_mode(काष्ठा amdgpu_device *adev,
				पूर्णांक inst_idx, काष्ठा dpg_छोड़ो_state *new_state);
अटल पूर्णांक vcn_v2_5_sriov_start(काष्ठा amdgpu_device *adev);

अटल पूर्णांक amdgpu_ih_clientid_vcns[] = अणु
	SOC15_IH_CLIENTID_VCN,
	SOC15_IH_CLIENTID_VCN1
पूर्ण;

/**
 * vcn_v2_5_early_init - set function poपूर्णांकers
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Set ring and irq function poपूर्णांकers
 */
अटल पूर्णांक vcn_v2_5_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev)) अणु
		adev->vcn.num_vcn_inst = 2;
		adev->vcn.harvest_config = 0;
		adev->vcn.num_enc_rings = 1;
	पूर्ण अन्यथा अणु
		u32 harvest;
		पूर्णांक i;
		adev->vcn.num_vcn_inst = VCN25_MAX_HW_INSTANCES_ARCTURUS;
		क्रम (i = 0; i < adev->vcn.num_vcn_inst; i++) अणु
			harvest = RREG32_SOC15(VCN, i, mmCC_UVD_HARVESTING);
			अगर (harvest & CC_UVD_HARVESTING__UVD_DISABLE_MASK)
				adev->vcn.harvest_config |= 1 << i;
		पूर्ण
		अगर (adev->vcn.harvest_config == (AMDGPU_VCN_HARVEST_VCN0 |
					AMDGPU_VCN_HARVEST_VCN1))
			/* both instances are harvested, disable the block */
			वापस -ENOENT;

		adev->vcn.num_enc_rings = 2;
	पूर्ण

	vcn_v2_5_set_dec_ring_funcs(adev);
	vcn_v2_5_set_enc_ring_funcs(adev);
	vcn_v2_5_set_irq_funcs(adev);

	वापस 0;
पूर्ण

/**
 * vcn_v2_5_sw_init - sw init क्रम VCN block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Load firmware and sw initialization
 */
अटल पूर्णांक vcn_v2_5_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_ring *ring;
	पूर्णांक i, j, r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (j = 0; j < adev->vcn.num_vcn_inst; j++) अणु
		अगर (adev->vcn.harvest_config & (1 << j))
			जारी;
		/* VCN DEC TRAP */
		r = amdgpu_irq_add_id(adev, amdgpu_ih_clientid_vcns[j],
				VCN_2_0__SRCID__UVD_SYSTEM_MESSAGE_INTERRUPT, &adev->vcn.inst[j].irq);
		अगर (r)
			वापस r;

		/* VCN ENC TRAP */
		क्रम (i = 0; i < adev->vcn.num_enc_rings; ++i) अणु
			r = amdgpu_irq_add_id(adev, amdgpu_ih_clientid_vcns[j],
				i + VCN_2_0__SRCID__UVD_ENC_GENERAL_PURPOSE, &adev->vcn.inst[j].irq);
			अगर (r)
				वापस r;
		पूर्ण
	पूर्ण

	r = amdgpu_vcn_sw_init(adev);
	अगर (r)
		वापस r;

	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
		स्थिर काष्ठा common_firmware_header *hdr;
		hdr = (स्थिर काष्ठा common_firmware_header *)adev->vcn.fw->data;
		adev->firmware.ucode[AMDGPU_UCODE_ID_VCN].ucode_id = AMDGPU_UCODE_ID_VCN;
		adev->firmware.ucode[AMDGPU_UCODE_ID_VCN].fw = adev->vcn.fw;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(hdr->ucode_size_bytes), PAGE_SIZE);

		अगर (adev->vcn.num_vcn_inst == VCN25_MAX_HW_INSTANCES_ARCTURUS) अणु
			adev->firmware.ucode[AMDGPU_UCODE_ID_VCN1].ucode_id = AMDGPU_UCODE_ID_VCN1;
			adev->firmware.ucode[AMDGPU_UCODE_ID_VCN1].fw = adev->vcn.fw;
			adev->firmware.fw_size +=
				ALIGN(le32_to_cpu(hdr->ucode_size_bytes), PAGE_SIZE);
		पूर्ण
		DRM_INFO("PSP loading VCN firmware\n");
	पूर्ण

	r = amdgpu_vcn_resume(adev);
	अगर (r)
		वापस r;

	क्रम (j = 0; j < adev->vcn.num_vcn_inst; j++) अणु
		अस्थिर काष्ठा amdgpu_fw_shared *fw_shared;

		अगर (adev->vcn.harvest_config & (1 << j))
			जारी;
		adev->vcn.पूर्णांकernal.context_id = mmUVD_CONTEXT_ID_INTERNAL_OFFSET;
		adev->vcn.पूर्णांकernal.ib_vmid = mmUVD_LMI_RBC_IB_VMID_INTERNAL_OFFSET;
		adev->vcn.पूर्णांकernal.ib_bar_low = mmUVD_LMI_RBC_IB_64BIT_BAR_LOW_INTERNAL_OFFSET;
		adev->vcn.पूर्णांकernal.ib_bar_high = mmUVD_LMI_RBC_IB_64BIT_BAR_HIGH_INTERNAL_OFFSET;
		adev->vcn.पूर्णांकernal.ib_size = mmUVD_RBC_IB_SIZE_INTERNAL_OFFSET;
		adev->vcn.पूर्णांकernal.gp_scratch8 = mmUVD_GP_SCRATCH8_INTERNAL_OFFSET;

		adev->vcn.पूर्णांकernal.scratch9 = mmUVD_SCRATCH9_INTERNAL_OFFSET;
		adev->vcn.inst[j].बाह्यal.scratch9 = SOC15_REG_OFFSET(VCN, j, mmUVD_SCRATCH9);
		adev->vcn.पूर्णांकernal.data0 = mmUVD_GPCOM_VCPU_DATA0_INTERNAL_OFFSET;
		adev->vcn.inst[j].बाह्यal.data0 = SOC15_REG_OFFSET(VCN, j, mmUVD_GPCOM_VCPU_DATA0);
		adev->vcn.पूर्णांकernal.data1 = mmUVD_GPCOM_VCPU_DATA1_INTERNAL_OFFSET;
		adev->vcn.inst[j].बाह्यal.data1 = SOC15_REG_OFFSET(VCN, j, mmUVD_GPCOM_VCPU_DATA1);
		adev->vcn.पूर्णांकernal.cmd = mmUVD_GPCOM_VCPU_CMD_INTERNAL_OFFSET;
		adev->vcn.inst[j].बाह्यal.cmd = SOC15_REG_OFFSET(VCN, j, mmUVD_GPCOM_VCPU_CMD);
		adev->vcn.पूर्णांकernal.nop = mmUVD_NO_OP_INTERNAL_OFFSET;
		adev->vcn.inst[j].बाह्यal.nop = SOC15_REG_OFFSET(VCN, j, mmUVD_NO_OP);

		ring = &adev->vcn.inst[j].ring_dec;
		ring->use_करोorbell = true;

		ring->करोorbell_index = (adev->करोorbell_index.vcn.vcn_ring0_1 << 1) +
				(amdgpu_sriov_vf(adev) ? 2*j : 8*j);
		प्र_लिखो(ring->name, "vcn_dec_%d", j);
		r = amdgpu_ring_init(adev, ring, 512, &adev->vcn.inst[j].irq,
				     0, AMDGPU_RING_PRIO_DEFAULT, शून्य);
		अगर (r)
			वापस r;

		क्रम (i = 0; i < adev->vcn.num_enc_rings; ++i) अणु
			ring = &adev->vcn.inst[j].ring_enc[i];
			ring->use_करोorbell = true;

			ring->करोorbell_index = (adev->करोorbell_index.vcn.vcn_ring0_1 << 1) +
					(amdgpu_sriov_vf(adev) ? (1 + i + 2*j) : (2 + i + 8*j));

			प्र_लिखो(ring->name, "vcn_enc_%d.%d", j, i);
			r = amdgpu_ring_init(adev, ring, 512,
					     &adev->vcn.inst[j].irq, 0,
					     AMDGPU_RING_PRIO_DEFAULT, शून्य);
			अगर (r)
				वापस r;
		पूर्ण

		fw_shared = adev->vcn.inst[j].fw_shared_cpu_addr;
		fw_shared->present_flag_0 = cpu_to_le32(AMDGPU_VCN_MULTI_QUEUE_FLAG);
	पूर्ण

	अगर (amdgpu_sriov_vf(adev)) अणु
		r = amdgpu_virt_alloc_mm_table(adev);
		अगर (r)
			वापस r;
	पूर्ण

	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG)
		adev->vcn.छोड़ो_dpg_mode = vcn_v2_5_छोड़ो_dpg_mode;

	वापस 0;
पूर्ण

/**
 * vcn_v2_5_sw_fini - sw fini क्रम VCN block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * VCN suspend and मुक्त up sw allocation
 */
अटल पूर्णांक vcn_v2_5_sw_fini(व्योम *handle)
अणु
	पूर्णांक i, r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	अस्थिर काष्ठा amdgpu_fw_shared *fw_shared;

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; i++) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;
		fw_shared = adev->vcn.inst[i].fw_shared_cpu_addr;
		fw_shared->present_flag_0 = 0;
	पूर्ण

	अगर (amdgpu_sriov_vf(adev))
		amdgpu_virt_मुक्त_mm_table(adev);

	r = amdgpu_vcn_suspend(adev);
	अगर (r)
		वापस r;

	r = amdgpu_vcn_sw_fini(adev);

	वापस r;
पूर्ण

/**
 * vcn_v2_5_hw_init - start and test VCN block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Initialize the hardware, boot up the VCPU and करो some testing
 */
अटल पूर्णांक vcn_v2_5_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा amdgpu_ring *ring;
	पूर्णांक i, j, r = 0;

	अगर (amdgpu_sriov_vf(adev))
		r = vcn_v2_5_sriov_start(adev);

	क्रम (j = 0; j < adev->vcn.num_vcn_inst; ++j) अणु
		अगर (adev->vcn.harvest_config & (1 << j))
			जारी;

		अगर (amdgpu_sriov_vf(adev)) अणु
			adev->vcn.inst[j].ring_enc[0].sched.पढ़ोy = true;
			adev->vcn.inst[j].ring_enc[1].sched.पढ़ोy = false;
			adev->vcn.inst[j].ring_enc[2].sched.पढ़ोy = false;
			adev->vcn.inst[j].ring_dec.sched.पढ़ोy = true;
		पूर्ण अन्यथा अणु

			ring = &adev->vcn.inst[j].ring_dec;

			adev->nbio.funcs->vcn_करोorbell_range(adev, ring->use_करोorbell,
						     ring->करोorbell_index, j);

			r = amdgpu_ring_test_helper(ring);
			अगर (r)
				जाओ करोne;

			क्रम (i = 0; i < adev->vcn.num_enc_rings; ++i) अणु
				ring = &adev->vcn.inst[j].ring_enc[i];
				r = amdgpu_ring_test_helper(ring);
				अगर (r)
					जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण

करोne:
	अगर (!r)
		DRM_INFO("VCN decode and encode initialized successfully(under %s).\n",
			(adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG)?"DPG Mode":"SPG Mode");

	वापस r;
पूर्ण

/**
 * vcn_v2_5_hw_fini - stop the hardware block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Stop the VCN block, mark ring as not पढ़ोy any more
 */
अटल पूर्णांक vcn_v2_5_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक i;

	cancel_delayed_work_sync(&adev->vcn.idle_work);

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;

		अगर ((adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG) ||
		    (adev->vcn.cur_state != AMD_PG_STATE_GATE &&
		     RREG32_SOC15(VCN, i, mmUVD_STATUS)))
			vcn_v2_5_set_घातergating_state(adev, AMD_PG_STATE_GATE);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vcn_v2_5_suspend - suspend VCN block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * HW fini and suspend VCN block
 */
अटल पूर्णांक vcn_v2_5_suspend(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = vcn_v2_5_hw_fini(adev);
	अगर (r)
		वापस r;

	r = amdgpu_vcn_suspend(adev);

	वापस r;
पूर्ण

/**
 * vcn_v2_5_resume - resume VCN block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Resume firmware and hw init VCN block
 */
अटल पूर्णांक vcn_v2_5_resume(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_vcn_resume(adev);
	अगर (r)
		वापस r;

	r = vcn_v2_5_hw_init(adev);

	वापस r;
पूर्ण

/**
 * vcn_v2_5_mc_resume - memory controller programming
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Let the VCN memory controller know it's offsets
 */
अटल व्योम vcn_v2_5_mc_resume(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t size = AMDGPU_GPU_PAGE_ALIGN(adev->vcn.fw->size + 4);
	uपूर्णांक32_t offset;
	पूर्णांक i;

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;
		/* cache winकरोw 0: fw */
		अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
			WREG32_SOC15(VCN, i, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW,
				(adev->firmware.ucode[AMDGPU_UCODE_ID_VCN + i].पंचांगr_mc_addr_lo));
			WREG32_SOC15(VCN, i, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH,
				(adev->firmware.ucode[AMDGPU_UCODE_ID_VCN + i].पंचांगr_mc_addr_hi));
			WREG32_SOC15(VCN, i, mmUVD_VCPU_CACHE_OFFSET0, 0);
			offset = 0;
		पूर्ण अन्यथा अणु
			WREG32_SOC15(VCN, i, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW,
				lower_32_bits(adev->vcn.inst[i].gpu_addr));
			WREG32_SOC15(VCN, i, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH,
				upper_32_bits(adev->vcn.inst[i].gpu_addr));
			offset = size;
			WREG32_SOC15(VCN, i, mmUVD_VCPU_CACHE_OFFSET0,
				AMDGPU_UVD_FIRMWARE_OFFSET >> 3);
		पूर्ण
		WREG32_SOC15(VCN, i, mmUVD_VCPU_CACHE_SIZE0, size);

		/* cache winकरोw 1: stack */
		WREG32_SOC15(VCN, i, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW,
			lower_32_bits(adev->vcn.inst[i].gpu_addr + offset));
		WREG32_SOC15(VCN, i, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH,
			upper_32_bits(adev->vcn.inst[i].gpu_addr + offset));
		WREG32_SOC15(VCN, i, mmUVD_VCPU_CACHE_OFFSET1, 0);
		WREG32_SOC15(VCN, i, mmUVD_VCPU_CACHE_SIZE1, AMDGPU_VCN_STACK_SIZE);

		/* cache winकरोw 2: context */
		WREG32_SOC15(VCN, i, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW,
			lower_32_bits(adev->vcn.inst[i].gpu_addr + offset + AMDGPU_VCN_STACK_SIZE));
		WREG32_SOC15(VCN, i, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH,
			upper_32_bits(adev->vcn.inst[i].gpu_addr + offset + AMDGPU_VCN_STACK_SIZE));
		WREG32_SOC15(VCN, i, mmUVD_VCPU_CACHE_OFFSET2, 0);
		WREG32_SOC15(VCN, i, mmUVD_VCPU_CACHE_SIZE2, AMDGPU_VCN_CONTEXT_SIZE);

		/* non-cache winकरोw */
		WREG32_SOC15(VCN, i, mmUVD_LMI_VCPU_NC0_64BIT_BAR_LOW,
			lower_32_bits(adev->vcn.inst[i].fw_shared_gpu_addr));
		WREG32_SOC15(VCN, i, mmUVD_LMI_VCPU_NC0_64BIT_BAR_HIGH,
			upper_32_bits(adev->vcn.inst[i].fw_shared_gpu_addr));
		WREG32_SOC15(VCN, i, mmUVD_VCPU_NONCACHE_OFFSET0, 0);
		WREG32_SOC15(VCN, i, mmUVD_VCPU_NONCACHE_SIZE0,
			AMDGPU_GPU_PAGE_ALIGN(माप(काष्ठा amdgpu_fw_shared)));
	पूर्ण
पूर्ण

अटल व्योम vcn_v2_5_mc_resume_dpg_mode(काष्ठा amdgpu_device *adev, पूर्णांक inst_idx, bool indirect)
अणु
	uपूर्णांक32_t size = AMDGPU_GPU_PAGE_ALIGN(adev->vcn.fw->size + 4);
	uपूर्णांक32_t offset;

	/* cache winकरोw 0: fw */
	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
		अगर (!indirect) अणु
			WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW),
				(adev->firmware.ucode[AMDGPU_UCODE_ID_VCN + inst_idx].पंचांगr_mc_addr_lo), 0, indirect);
			WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH),
				(adev->firmware.ucode[AMDGPU_UCODE_ID_VCN + inst_idx].पंचांगr_mc_addr_hi), 0, indirect);
			WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, 0, mmUVD_VCPU_CACHE_OFFSET0), 0, 0, indirect);
		पूर्ण अन्यथा अणु
			WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW), 0, 0, indirect);
			WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH), 0, 0, indirect);
			WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, 0, mmUVD_VCPU_CACHE_OFFSET0), 0, 0, indirect);
		पूर्ण
		offset = 0;
	पूर्ण अन्यथा अणु
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW),
			lower_32_bits(adev->vcn.inst[inst_idx].gpu_addr), 0, indirect);
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH),
			upper_32_bits(adev->vcn.inst[inst_idx].gpu_addr), 0, indirect);
		offset = size;
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, mmUVD_VCPU_CACHE_OFFSET0),
			AMDGPU_UVD_FIRMWARE_OFFSET >> 3, 0, indirect);
	पूर्ण

	अगर (!indirect)
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, mmUVD_VCPU_CACHE_SIZE0), size, 0, indirect);
	अन्यथा
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, mmUVD_VCPU_CACHE_SIZE0), 0, 0, indirect);

	/* cache winकरोw 1: stack */
	अगर (!indirect) अणु
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW),
			lower_32_bits(adev->vcn.inst[inst_idx].gpu_addr + offset), 0, indirect);
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH),
			upper_32_bits(adev->vcn.inst[inst_idx].gpu_addr + offset), 0, indirect);
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, mmUVD_VCPU_CACHE_OFFSET1), 0, 0, indirect);
	पूर्ण अन्यथा अणु
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW), 0, 0, indirect);
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH), 0, 0, indirect);
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, mmUVD_VCPU_CACHE_OFFSET1), 0, 0, indirect);
	पूर्ण
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_VCPU_CACHE_SIZE1), AMDGPU_VCN_STACK_SIZE, 0, indirect);

	/* cache winकरोw 2: context */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW),
		lower_32_bits(adev->vcn.inst[inst_idx].gpu_addr + offset + AMDGPU_VCN_STACK_SIZE), 0, indirect);
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH),
		upper_32_bits(adev->vcn.inst[inst_idx].gpu_addr + offset + AMDGPU_VCN_STACK_SIZE), 0, indirect);
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_VCPU_CACHE_OFFSET2), 0, 0, indirect);
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_VCPU_CACHE_SIZE2), AMDGPU_VCN_CONTEXT_SIZE, 0, indirect);

	/* non-cache winकरोw */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_LMI_VCPU_NC0_64BIT_BAR_LOW),
		lower_32_bits(adev->vcn.inst[inst_idx].fw_shared_gpu_addr), 0, indirect);
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_LMI_VCPU_NC0_64BIT_BAR_HIGH),
		upper_32_bits(adev->vcn.inst[inst_idx].fw_shared_gpu_addr), 0, indirect);
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_VCPU_NONCACHE_OFFSET0), 0, 0, indirect);
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_VCPU_NONCACHE_SIZE0),
		AMDGPU_GPU_PAGE_ALIGN(माप(काष्ठा amdgpu_fw_shared)), 0, indirect);

	/* VCN global tiling रेजिस्टरs */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_GFX8_ADDR_CONFIG), adev->gfx.config.gb_addr_config, 0, indirect);
पूर्ण

/**
 * vcn_v2_5_disable_घड़ी_gating - disable VCN घड़ी gating
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Disable घड़ी gating क्रम VCN block
 */
अटल व्योम vcn_v2_5_disable_घड़ी_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data;
	पूर्णांक i;

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;
		/* UVD disable CGC */
		data = RREG32_SOC15(VCN, i, mmUVD_CGC_CTRL);
		अगर (adev->cg_flags & AMD_CG_SUPPORT_VCN_MGCG)
			data |= 1 << UVD_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
		अन्यथा
			data &= ~UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK;
		data |= 1 << UVD_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT;
		data |= 4 << UVD_CGC_CTRL__CLK_OFF_DELAY__SHIFT;
		WREG32_SOC15(VCN, i, mmUVD_CGC_CTRL, data);

		data = RREG32_SOC15(VCN, i, mmUVD_CGC_GATE);
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
			| UVD_CGC_GATE__MMSCH_MASK);

		WREG32_SOC15(VCN, i, mmUVD_CGC_GATE, data);

		SOC15_WAIT_ON_RREG(VCN, i, mmUVD_CGC_GATE, 0,  0xFFFFFFFF);

		data = RREG32_SOC15(VCN, i, mmUVD_CGC_CTRL);
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
			| UVD_CGC_CTRL__MMSCH_MODE_MASK);
		WREG32_SOC15(VCN, i, mmUVD_CGC_CTRL, data);

		/* turn on */
		data = RREG32_SOC15(VCN, i, mmUVD_SUVD_CGC_GATE);
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
		WREG32_SOC15(VCN, i, mmUVD_SUVD_CGC_GATE, data);

		data = RREG32_SOC15(VCN, i, mmUVD_SUVD_CGC_CTRL);
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
		WREG32_SOC15(VCN, i, mmUVD_SUVD_CGC_CTRL, data);
	पूर्ण
पूर्ण

अटल व्योम vcn_v2_5_घड़ी_gating_dpg_mode(काष्ठा amdgpu_device *adev,
		uपूर्णांक8_t sram_sel, पूर्णांक inst_idx, uपूर्णांक8_t indirect)
अणु
	uपूर्णांक32_t reg_data = 0;

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
		 UVD_CGC_CTRL__MMSCH_MODE_MASK);
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_CGC_CTRL), reg_data, sram_sel, indirect);

	/* turn off घड़ी gating */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_CGC_GATE), 0, sram_sel, indirect);

	/* turn on SUVD घड़ी gating */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_SUVD_CGC_GATE), 1, sram_sel, indirect);

	/* turn on sw mode in UVD_SUVD_CGC_CTRL */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_SUVD_CGC_CTRL), 0, sram_sel, indirect);
पूर्ण

/**
 * vcn_v2_5_enable_घड़ी_gating - enable VCN घड़ी gating
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Enable घड़ी gating क्रम VCN block
 */
अटल व्योम vcn_v2_5_enable_घड़ी_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data = 0;
	पूर्णांक i;

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;
		/* enable UVD CGC */
		data = RREG32_SOC15(VCN, i, mmUVD_CGC_CTRL);
		अगर (adev->cg_flags & AMD_CG_SUPPORT_VCN_MGCG)
			data |= 1 << UVD_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
		अन्यथा
			data |= 0 << UVD_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
		data |= 1 << UVD_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT;
		data |= 4 << UVD_CGC_CTRL__CLK_OFF_DELAY__SHIFT;
		WREG32_SOC15(VCN, i, mmUVD_CGC_CTRL, data);

		data = RREG32_SOC15(VCN, i, mmUVD_CGC_CTRL);
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
			| UVD_CGC_CTRL__VCPU_MODE_MASK);
		WREG32_SOC15(VCN, i, mmUVD_CGC_CTRL, data);

		data = RREG32_SOC15(VCN, i, mmUVD_SUVD_CGC_CTRL);
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
		WREG32_SOC15(VCN, i, mmUVD_SUVD_CGC_CTRL, data);
	पूर्ण
पूर्ण

अटल पूर्णांक vcn_v2_5_start_dpg_mode(काष्ठा amdgpu_device *adev, पूर्णांक inst_idx, bool indirect)
अणु
	अस्थिर काष्ठा amdgpu_fw_shared *fw_shared = adev->vcn.inst[inst_idx].fw_shared_cpu_addr;
	काष्ठा amdgpu_ring *ring;
	uपूर्णांक32_t rb_bufsz, पंचांगp;

	/* disable रेजिस्टर anti-hang mechanism */
	WREG32_P(SOC15_REG_OFFSET(VCN, inst_idx, mmUVD_POWER_STATUS), 1,
		~UVD_POWER_STATUS__UVD_POWER_STATUS_MASK);
	/* enable dynamic घातer gating mode */
	पंचांगp = RREG32_SOC15(VCN, inst_idx, mmUVD_POWER_STATUS);
	पंचांगp |= UVD_POWER_STATUS__UVD_PG_MODE_MASK;
	पंचांगp |= UVD_POWER_STATUS__UVD_PG_EN_MASK;
	WREG32_SOC15(VCN, inst_idx, mmUVD_POWER_STATUS, पंचांगp);

	अगर (indirect)
		adev->vcn.inst[inst_idx].dpg_sram_curr_addr = (uपूर्णांक32_t *)adev->vcn.inst[inst_idx].dpg_sram_cpu_addr;

	/* enable घड़ी gating */
	vcn_v2_5_घड़ी_gating_dpg_mode(adev, 0, inst_idx, indirect);

	/* enable VCPU घड़ी */
	पंचांगp = (0xFF << UVD_VCPU_CNTL__PRB_TIMEOUT_VAL__SHIFT);
	पंचांगp |= UVD_VCPU_CNTL__CLK_EN_MASK;
	पंचांगp |= UVD_VCPU_CNTL__BLK_RST_MASK;
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_VCPU_CNTL), पंचांगp, 0, indirect);

	/* disable master पूर्णांकerupt */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_MASTINT_EN), 0, 0, indirect);

	/* setup mmUVD_LMI_CTRL */
	पंचांगp = (0x8 | UVD_LMI_CTRL__WRITE_CLEAN_TIMER_EN_MASK |
		UVD_LMI_CTRL__REQ_MODE_MASK |
		UVD_LMI_CTRL__CRC_RESET_MASK |
		UVD_LMI_CTRL__MASK_MC_URGENT_MASK |
		UVD_LMI_CTRL__DATA_COHERENCY_EN_MASK |
		UVD_LMI_CTRL__VCPU_DATA_COHERENCY_EN_MASK |
		(8 << UVD_LMI_CTRL__WRITE_CLEAN_TIMER__SHIFT) |
		0x00100000L);
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_LMI_CTRL), पंचांगp, 0, indirect);

	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_MPC_CNTL),
		0x2 << UVD_MPC_CNTL__REPLACEMENT_MODE__SHIFT, 0, indirect);

	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_MPC_SET_MUXA0),
		((0x1 << UVD_MPC_SET_MUXA0__VARA_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUXA0__VARA_2__SHIFT) |
		 (0x3 << UVD_MPC_SET_MUXA0__VARA_3__SHIFT) |
		 (0x4 << UVD_MPC_SET_MUXA0__VARA_4__SHIFT)), 0, indirect);

	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_MPC_SET_MUXB0),
		((0x1 << UVD_MPC_SET_MUXB0__VARB_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUXB0__VARB_2__SHIFT) |
		 (0x3 << UVD_MPC_SET_MUXB0__VARB_3__SHIFT) |
		 (0x4 << UVD_MPC_SET_MUXB0__VARB_4__SHIFT)), 0, indirect);

	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_MPC_SET_MUX),
		((0x0 << UVD_MPC_SET_MUX__SET_0__SHIFT) |
		 (0x1 << UVD_MPC_SET_MUX__SET_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUX__SET_2__SHIFT)), 0, indirect);

	vcn_v2_5_mc_resume_dpg_mode(adev, inst_idx, indirect);

	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_REG_XX_MASK), 0x10, 0, indirect);
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_RBC_XX_IB_REG_CHECK), 0x3, 0, indirect);

	/* enable LMI MC and UMC channels */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_LMI_CTRL2), 0, 0, indirect);

	/* unblock VCPU रेजिस्टर access */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_RB_ARB_CTRL), 0, 0, indirect);

	पंचांगp = (0xFF << UVD_VCPU_CNTL__PRB_TIMEOUT_VAL__SHIFT);
	पंचांगp |= UVD_VCPU_CNTL__CLK_EN_MASK;
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_VCPU_CNTL), पंचांगp, 0, indirect);

	/* enable master पूर्णांकerrupt */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, mmUVD_MASTINT_EN),
		UVD_MASTINT_EN__VCPU_EN_MASK, 0, indirect);

	अगर (indirect)
		psp_update_vcn_sram(adev, inst_idx, adev->vcn.inst[inst_idx].dpg_sram_gpu_addr,
				    (uपूर्णांक32_t)((uपूर्णांकptr_t)adev->vcn.inst[inst_idx].dpg_sram_curr_addr -
					       (uपूर्णांकptr_t)adev->vcn.inst[inst_idx].dpg_sram_cpu_addr));

	ring = &adev->vcn.inst[inst_idx].ring_dec;
	/* क्रमce RBC पूर्णांकo idle state */
	rb_bufsz = order_base_2(ring->ring_size);
	पंचांगp = REG_SET_FIELD(0, UVD_RBC_RB_CNTL, RB_BUFSZ, rb_bufsz);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_BLKSZ, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_FETCH, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_UPDATE, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_RPTR_WR_EN, 1);
	WREG32_SOC15(VCN, inst_idx, mmUVD_RBC_RB_CNTL, पंचांगp);

	/* Stall DPG beक्रमe WPTR/RPTR reset */
	WREG32_P(SOC15_REG_OFFSET(VCN, inst_idx, mmUVD_POWER_STATUS),
		UVD_POWER_STATUS__STALL_DPG_POWER_UP_MASK,
		~UVD_POWER_STATUS__STALL_DPG_POWER_UP_MASK);
	fw_shared->multi_queue.decode_queue_mode |= FW_QUEUE_RING_RESET;

	/* set the ग_लिखो poपूर्णांकer delay */
	WREG32_SOC15(VCN, inst_idx, mmUVD_RBC_RB_WPTR_CNTL, 0);

	/* set the wb address */
	WREG32_SOC15(VCN, inst_idx, mmUVD_RBC_RB_RPTR_ADDR,
		(upper_32_bits(ring->gpu_addr) >> 2));

	/* program the RB_BASE क्रम ring buffer */
	WREG32_SOC15(VCN, inst_idx, mmUVD_LMI_RBC_RB_64BIT_BAR_LOW,
		lower_32_bits(ring->gpu_addr));
	WREG32_SOC15(VCN, inst_idx, mmUVD_LMI_RBC_RB_64BIT_BAR_HIGH,
		upper_32_bits(ring->gpu_addr));

	/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
	WREG32_SOC15(VCN, inst_idx, mmUVD_RBC_RB_RPTR, 0);

	WREG32_SOC15(VCN, inst_idx, mmUVD_SCRATCH2, 0);

	ring->wptr = RREG32_SOC15(VCN, inst_idx, mmUVD_RBC_RB_RPTR);
	WREG32_SOC15(VCN, inst_idx, mmUVD_RBC_RB_WPTR,
		lower_32_bits(ring->wptr));

	fw_shared->multi_queue.decode_queue_mode &= ~FW_QUEUE_RING_RESET;
	/* Unstall DPG */
	WREG32_P(SOC15_REG_OFFSET(VCN, inst_idx, mmUVD_POWER_STATUS),
		0, ~UVD_POWER_STATUS__STALL_DPG_POWER_UP_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v2_5_start(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	uपूर्णांक32_t rb_bufsz, पंचांगp;
	पूर्णांक i, j, k, r;

	अगर (adev->pm.dpm_enabled)
		amdgpu_dpm_enable_uvd(adev, true);

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;
		अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG) अणु
			r = vcn_v2_5_start_dpg_mode(adev, i, adev->vcn.indirect_sram);
			जारी;
		पूर्ण

		/* disable रेजिस्टर anti-hang mechanism */
		WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_POWER_STATUS), 0,
			~UVD_POWER_STATUS__UVD_POWER_STATUS_MASK);

		/* set uvd status busy */
		पंचांगp = RREG32_SOC15(VCN, i, mmUVD_STATUS) | UVD_STATUS__UVD_BUSY;
		WREG32_SOC15(VCN, i, mmUVD_STATUS, पंचांगp);
	पूर्ण

	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG)
		वापस 0;

	/*SW घड़ी gating */
	vcn_v2_5_disable_घड़ी_gating(adev);

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;
		/* enable VCPU घड़ी */
		WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_VCPU_CNTL),
			UVD_VCPU_CNTL__CLK_EN_MASK, ~UVD_VCPU_CNTL__CLK_EN_MASK);

		/* disable master पूर्णांकerrupt */
		WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_MASTINT_EN), 0,
			~UVD_MASTINT_EN__VCPU_EN_MASK);

		/* setup mmUVD_LMI_CTRL */
		पंचांगp = RREG32_SOC15(VCN, i, mmUVD_LMI_CTRL);
		पंचांगp &= ~0xff;
		WREG32_SOC15(VCN, i, mmUVD_LMI_CTRL, पंचांगp | 0x8|
			UVD_LMI_CTRL__WRITE_CLEAN_TIMER_EN_MASK	|
			UVD_LMI_CTRL__MASK_MC_URGENT_MASK |
			UVD_LMI_CTRL__DATA_COHERENCY_EN_MASK |
			UVD_LMI_CTRL__VCPU_DATA_COHERENCY_EN_MASK);

		/* setup mmUVD_MPC_CNTL */
		पंचांगp = RREG32_SOC15(VCN, i, mmUVD_MPC_CNTL);
		पंचांगp &= ~UVD_MPC_CNTL__REPLACEMENT_MODE_MASK;
		पंचांगp |= 0x2 << UVD_MPC_CNTL__REPLACEMENT_MODE__SHIFT;
		WREG32_SOC15(VCN, i, mmUVD_MPC_CNTL, पंचांगp);

		/* setup UVD_MPC_SET_MUXA0 */
		WREG32_SOC15(VCN, i, mmUVD_MPC_SET_MUXA0,
			((0x1 << UVD_MPC_SET_MUXA0__VARA_1__SHIFT) |
			(0x2 << UVD_MPC_SET_MUXA0__VARA_2__SHIFT) |
			(0x3 << UVD_MPC_SET_MUXA0__VARA_3__SHIFT) |
			(0x4 << UVD_MPC_SET_MUXA0__VARA_4__SHIFT)));

		/* setup UVD_MPC_SET_MUXB0 */
		WREG32_SOC15(VCN, i, mmUVD_MPC_SET_MUXB0,
			((0x1 << UVD_MPC_SET_MUXB0__VARB_1__SHIFT) |
			(0x2 << UVD_MPC_SET_MUXB0__VARB_2__SHIFT) |
			(0x3 << UVD_MPC_SET_MUXB0__VARB_3__SHIFT) |
			(0x4 << UVD_MPC_SET_MUXB0__VARB_4__SHIFT)));

		/* setup mmUVD_MPC_SET_MUX */
		WREG32_SOC15(VCN, i, mmUVD_MPC_SET_MUX,
			((0x0 << UVD_MPC_SET_MUX__SET_0__SHIFT) |
			(0x1 << UVD_MPC_SET_MUX__SET_1__SHIFT) |
			(0x2 << UVD_MPC_SET_MUX__SET_2__SHIFT)));
	पूर्ण

	vcn_v2_5_mc_resume(adev);

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अस्थिर काष्ठा amdgpu_fw_shared *fw_shared = adev->vcn.inst[i].fw_shared_cpu_addr;
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;
		/* VCN global tiling रेजिस्टरs */
		WREG32_SOC15(VCN, i, mmUVD_GFX8_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);
		WREG32_SOC15(VCN, i, mmUVD_GFX8_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);

		/* enable LMI MC and UMC channels */
		WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_LMI_CTRL2), 0,
			~UVD_LMI_CTRL2__STALL_ARB_UMC_MASK);

		/* unblock VCPU रेजिस्टर access */
		WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_RB_ARB_CTRL), 0,
			~UVD_RB_ARB_CTRL__VCPU_DIS_MASK);

		WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_VCPU_CNTL), 0,
			~UVD_VCPU_CNTL__BLK_RST_MASK);

		क्रम (k = 0; k < 10; ++k) अणु
			uपूर्णांक32_t status;

			क्रम (j = 0; j < 100; ++j) अणु
				status = RREG32_SOC15(VCN, i, mmUVD_STATUS);
				अगर (status & 2)
					अवरोध;
				अगर (amdgpu_emu_mode == 1)
					msleep(500);
				अन्यथा
					mdelay(10);
			पूर्ण
			r = 0;
			अगर (status & 2)
				अवरोध;

			DRM_ERROR("VCN decode not responding, trying to reset the VCPU!!!\n");
			WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_VCPU_CNTL),
				UVD_VCPU_CNTL__BLK_RST_MASK,
				~UVD_VCPU_CNTL__BLK_RST_MASK);
			mdelay(10);
			WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_VCPU_CNTL), 0,
				~UVD_VCPU_CNTL__BLK_RST_MASK);

			mdelay(10);
			r = -1;
		पूर्ण

		अगर (r) अणु
			DRM_ERROR("VCN decode not responding, giving up!!!\n");
			वापस r;
		पूर्ण

		/* enable master पूर्णांकerrupt */
		WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_MASTINT_EN),
			UVD_MASTINT_EN__VCPU_EN_MASK,
			~UVD_MASTINT_EN__VCPU_EN_MASK);

		/* clear the busy bit of VCN_STATUS */
		WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_STATUS), 0,
			~(2 << UVD_STATUS__VCPU_REPORT__SHIFT));

		WREG32_SOC15(VCN, i, mmUVD_LMI_RBC_RB_VMID, 0);

		ring = &adev->vcn.inst[i].ring_dec;
		/* क्रमce RBC पूर्णांकo idle state */
		rb_bufsz = order_base_2(ring->ring_size);
		पंचांगp = REG_SET_FIELD(0, UVD_RBC_RB_CNTL, RB_BUFSZ, rb_bufsz);
		पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_BLKSZ, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_FETCH, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_UPDATE, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_RPTR_WR_EN, 1);
		WREG32_SOC15(VCN, i, mmUVD_RBC_RB_CNTL, पंचांगp);

		fw_shared->multi_queue.decode_queue_mode |= FW_QUEUE_RING_RESET;
		/* program the RB_BASE क्रम ring buffer */
		WREG32_SOC15(VCN, i, mmUVD_LMI_RBC_RB_64BIT_BAR_LOW,
			lower_32_bits(ring->gpu_addr));
		WREG32_SOC15(VCN, i, mmUVD_LMI_RBC_RB_64BIT_BAR_HIGH,
			upper_32_bits(ring->gpu_addr));

		/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
		WREG32_SOC15(VCN, i, mmUVD_RBC_RB_RPTR, 0);

		ring->wptr = RREG32_SOC15(VCN, i, mmUVD_RBC_RB_RPTR);
		WREG32_SOC15(VCN, i, mmUVD_RBC_RB_WPTR,
				lower_32_bits(ring->wptr));
		fw_shared->multi_queue.decode_queue_mode &= ~FW_QUEUE_RING_RESET;

		fw_shared->multi_queue.encode_generalpurpose_queue_mode |= FW_QUEUE_RING_RESET;
		ring = &adev->vcn.inst[i].ring_enc[0];
		WREG32_SOC15(VCN, i, mmUVD_RB_RPTR, lower_32_bits(ring->wptr));
		WREG32_SOC15(VCN, i, mmUVD_RB_WPTR, lower_32_bits(ring->wptr));
		WREG32_SOC15(VCN, i, mmUVD_RB_BASE_LO, ring->gpu_addr);
		WREG32_SOC15(VCN, i, mmUVD_RB_BASE_HI, upper_32_bits(ring->gpu_addr));
		WREG32_SOC15(VCN, i, mmUVD_RB_SIZE, ring->ring_size / 4);
		fw_shared->multi_queue.encode_generalpurpose_queue_mode &= ~FW_QUEUE_RING_RESET;

		fw_shared->multi_queue.encode_lowlatency_queue_mode |= FW_QUEUE_RING_RESET;
		ring = &adev->vcn.inst[i].ring_enc[1];
		WREG32_SOC15(VCN, i, mmUVD_RB_RPTR2, lower_32_bits(ring->wptr));
		WREG32_SOC15(VCN, i, mmUVD_RB_WPTR2, lower_32_bits(ring->wptr));
		WREG32_SOC15(VCN, i, mmUVD_RB_BASE_LO2, ring->gpu_addr);
		WREG32_SOC15(VCN, i, mmUVD_RB_BASE_HI2, upper_32_bits(ring->gpu_addr));
		WREG32_SOC15(VCN, i, mmUVD_RB_SIZE2, ring->ring_size / 4);
		fw_shared->multi_queue.encode_lowlatency_queue_mode &= ~FW_QUEUE_RING_RESET;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v2_5_mmsch_start(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_mm_table *table)
अणु
	uपूर्णांक32_t data = 0, loop = 0, size = 0;
	uपूर्णांक64_t addr = table->gpu_addr;
	काष्ठा mmsch_v1_1_init_header *header = शून्य;

	header = (काष्ठा mmsch_v1_1_init_header *)table->cpu_addr;
	size = header->total_size;

	/*
	 * 1, ग_लिखो to vce_mmsch_vf_ctx_addr_lo/hi रेजिस्टर with GPU mc addr of
	 *  memory descriptor location
	 */
	WREG32_SOC15(VCN, 0, mmMMSCH_VF_CTX_ADDR_LO, lower_32_bits(addr));
	WREG32_SOC15(VCN, 0, mmMMSCH_VF_CTX_ADDR_HI, upper_32_bits(addr));

	/* 2, update vmid of descriptor */
	data = RREG32_SOC15(VCN, 0, mmMMSCH_VF_VMID);
	data &= ~MMSCH_VF_VMID__VF_CTX_VMID_MASK;
	/* use करोमुख्य0 क्रम MM scheduler */
	data |= (0 << MMSCH_VF_VMID__VF_CTX_VMID__SHIFT);
	WREG32_SOC15(VCN, 0, mmMMSCH_VF_VMID, data);

	/* 3, notअगरy mmsch about the size of this descriptor */
	WREG32_SOC15(VCN, 0, mmMMSCH_VF_CTX_SIZE, size);

	/* 4, set resp to zero */
	WREG32_SOC15(VCN, 0, mmMMSCH_VF_MAILBOX_RESP, 0);

	/*
	 * 5, kick off the initialization and रुको until
	 * VCE_MMSCH_VF_MAILBOX_RESP becomes non-zero
	 */
	WREG32_SOC15(VCN, 0, mmMMSCH_VF_MAILBOX_HOST, 0x10000001);

	data = RREG32_SOC15(VCN, 0, mmMMSCH_VF_MAILBOX_RESP);
	loop = 10;
	जबतक ((data & 0x10000002) != 0x10000002) अणु
		udelay(100);
		data = RREG32_SOC15(VCN, 0, mmMMSCH_VF_MAILBOX_RESP);
		loop--;
		अगर (!loop)
			अवरोध;
	पूर्ण

	अगर (!loop) अणु
		dev_err(adev->dev,
			"failed to init MMSCH, mmMMSCH_VF_MAILBOX_RESP = %x\n",
			data);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v2_5_sriov_start(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	uपूर्णांक32_t offset, size, पंचांगp, i, rb_bufsz;
	uपूर्णांक32_t table_size = 0;
	काष्ठा mmsch_v1_0_cmd_direct_ग_लिखो direct_wt = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा mmsch_v1_0_cmd_direct_पढ़ो_modअगरy_ग_लिखो direct_rd_mod_wt = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा mmsch_v1_0_cmd_end end = अणु अणु 0 पूर्ण पूर्ण;
	uपूर्णांक32_t *init_table = adev->virt.mm_table.cpu_addr;
	काष्ठा mmsch_v1_1_init_header *header = (काष्ठा mmsch_v1_1_init_header *)init_table;

	direct_wt.cmd_header.command_type = MMSCH_COMMAND__सूचीECT_REG_WRITE;
	direct_rd_mod_wt.cmd_header.command_type = MMSCH_COMMAND__सूचीECT_REG_READ_MODIFY_WRITE;
	end.cmd_header.command_type = MMSCH_COMMAND__END;

	header->version = MMSCH_VERSION;
	header->total_size = माप(काष्ठा mmsch_v1_1_init_header) >> 2;
	init_table += header->total_size;

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		header->eng[i].table_offset = header->total_size;
		header->eng[i].init_status = 0;
		header->eng[i].table_size = 0;

		table_size = 0;

		MMSCH_V1_0_INSERT_सूचीECT_RD_MOD_WT(
			SOC15_REG_OFFSET(VCN, i, mmUVD_STATUS),
			~UVD_STATUS__UVD_BUSY, UVD_STATUS__UVD_BUSY);

		size = AMDGPU_GPU_PAGE_ALIGN(adev->vcn.fw->size + 4);
		/* mc resume*/
		अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
			MMSCH_V1_0_INSERT_सूचीECT_WT(
				SOC15_REG_OFFSET(VCN, i,
					mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW),
				adev->firmware.ucode[AMDGPU_UCODE_ID_VCN + i].पंचांगr_mc_addr_lo);
			MMSCH_V1_0_INSERT_सूचीECT_WT(
				SOC15_REG_OFFSET(VCN, i,
					mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH),
				adev->firmware.ucode[AMDGPU_UCODE_ID_VCN + i].पंचांगr_mc_addr_hi);
			offset = 0;
			MMSCH_V1_0_INSERT_सूचीECT_WT(
				SOC15_REG_OFFSET(VCN, i, mmUVD_VCPU_CACHE_OFFSET0), 0);
		पूर्ण अन्यथा अणु
			MMSCH_V1_0_INSERT_सूचीECT_WT(
				SOC15_REG_OFFSET(VCN, i,
					mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW),
				lower_32_bits(adev->vcn.inst[i].gpu_addr));
			MMSCH_V1_0_INSERT_सूचीECT_WT(
				SOC15_REG_OFFSET(VCN, i,
					mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH),
				upper_32_bits(adev->vcn.inst[i].gpu_addr));
			offset = size;
			MMSCH_V1_0_INSERT_सूचीECT_WT(
				SOC15_REG_OFFSET(VCN, i, mmUVD_VCPU_CACHE_OFFSET0),
				AMDGPU_UVD_FIRMWARE_OFFSET >> 3);
		पूर्ण

		MMSCH_V1_0_INSERT_सूचीECT_WT(
			SOC15_REG_OFFSET(VCN, i, mmUVD_VCPU_CACHE_SIZE0),
			size);
		MMSCH_V1_0_INSERT_सूचीECT_WT(
			SOC15_REG_OFFSET(VCN, i,
				mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW),
			lower_32_bits(adev->vcn.inst[i].gpu_addr + offset));
		MMSCH_V1_0_INSERT_सूचीECT_WT(
			SOC15_REG_OFFSET(VCN, i,
				mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH),
			upper_32_bits(adev->vcn.inst[i].gpu_addr + offset));
		MMSCH_V1_0_INSERT_सूचीECT_WT(
			SOC15_REG_OFFSET(VCN, i, mmUVD_VCPU_CACHE_OFFSET1),
			0);
		MMSCH_V1_0_INSERT_सूचीECT_WT(
			SOC15_REG_OFFSET(VCN, i, mmUVD_VCPU_CACHE_SIZE1),
			AMDGPU_VCN_STACK_SIZE);
		MMSCH_V1_0_INSERT_सूचीECT_WT(
			SOC15_REG_OFFSET(VCN, i,
				mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW),
			lower_32_bits(adev->vcn.inst[i].gpu_addr + offset +
				AMDGPU_VCN_STACK_SIZE));
		MMSCH_V1_0_INSERT_सूचीECT_WT(
			SOC15_REG_OFFSET(VCN, i,
				mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH),
			upper_32_bits(adev->vcn.inst[i].gpu_addr + offset +
				AMDGPU_VCN_STACK_SIZE));
		MMSCH_V1_0_INSERT_सूचीECT_WT(
			SOC15_REG_OFFSET(VCN, i, mmUVD_VCPU_CACHE_OFFSET2),
			0);
		MMSCH_V1_0_INSERT_सूचीECT_WT(
			SOC15_REG_OFFSET(VCN, i, mmUVD_VCPU_CACHE_SIZE2),
			AMDGPU_VCN_CONTEXT_SIZE);

		ring = &adev->vcn.inst[i].ring_enc[0];
		ring->wptr = 0;

		MMSCH_V1_0_INSERT_सूचीECT_WT(
			SOC15_REG_OFFSET(VCN, i, mmUVD_RB_BASE_LO),
			lower_32_bits(ring->gpu_addr));
		MMSCH_V1_0_INSERT_सूचीECT_WT(
			SOC15_REG_OFFSET(VCN, i, mmUVD_RB_BASE_HI),
			upper_32_bits(ring->gpu_addr));
		MMSCH_V1_0_INSERT_सूचीECT_WT(
			SOC15_REG_OFFSET(VCN, i, mmUVD_RB_SIZE),
			ring->ring_size / 4);

		ring = &adev->vcn.inst[i].ring_dec;
		ring->wptr = 0;
		MMSCH_V1_0_INSERT_सूचीECT_WT(
			SOC15_REG_OFFSET(VCN, i,
				mmUVD_LMI_RBC_RB_64BIT_BAR_LOW),
			lower_32_bits(ring->gpu_addr));
		MMSCH_V1_0_INSERT_सूचीECT_WT(
			SOC15_REG_OFFSET(VCN, i,
				mmUVD_LMI_RBC_RB_64BIT_BAR_HIGH),
			upper_32_bits(ring->gpu_addr));

		/* क्रमce RBC पूर्णांकo idle state */
		rb_bufsz = order_base_2(ring->ring_size);
		पंचांगp = REG_SET_FIELD(0, UVD_RBC_RB_CNTL, RB_BUFSZ, rb_bufsz);
		पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_BLKSZ, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_FETCH, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_UPDATE, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_RPTR_WR_EN, 1);
		MMSCH_V1_0_INSERT_सूचीECT_WT(
			SOC15_REG_OFFSET(VCN, i, mmUVD_RBC_RB_CNTL), पंचांगp);

		/* add end packet */
		स_नकल((व्योम *)init_table, &end, माप(काष्ठा mmsch_v1_0_cmd_end));
		table_size += माप(काष्ठा mmsch_v1_0_cmd_end) / 4;
		init_table += माप(काष्ठा mmsch_v1_0_cmd_end) / 4;

		/* refine header */
		header->eng[i].table_size = table_size;
		header->total_size += table_size;
	पूर्ण

	वापस vcn_v2_5_mmsch_start(adev, &adev->virt.mm_table);
पूर्ण

अटल पूर्णांक vcn_v2_5_stop_dpg_mode(काष्ठा amdgpu_device *adev, पूर्णांक inst_idx)
अणु
	uपूर्णांक32_t पंचांगp;

	/* Wait क्रम घातer status to be 1 */
	SOC15_WAIT_ON_RREG(VCN, inst_idx, mmUVD_POWER_STATUS, 1,
		UVD_POWER_STATUS__UVD_POWER_STATUS_MASK);

	/* रुको क्रम पढ़ो ptr to be equal to ग_लिखो ptr */
	पंचांगp = RREG32_SOC15(VCN, inst_idx, mmUVD_RB_WPTR);
	SOC15_WAIT_ON_RREG(VCN, inst_idx, mmUVD_RB_RPTR, पंचांगp, 0xFFFFFFFF);

	पंचांगp = RREG32_SOC15(VCN, inst_idx, mmUVD_RB_WPTR2);
	SOC15_WAIT_ON_RREG(VCN, inst_idx, mmUVD_RB_RPTR2, पंचांगp, 0xFFFFFFFF);

	पंचांगp = RREG32_SOC15(VCN, inst_idx, mmUVD_RBC_RB_WPTR) & 0x7FFFFFFF;
	SOC15_WAIT_ON_RREG(VCN, inst_idx, mmUVD_RBC_RB_RPTR, पंचांगp, 0xFFFFFFFF);

	SOC15_WAIT_ON_RREG(VCN, inst_idx, mmUVD_POWER_STATUS, 1,
		UVD_POWER_STATUS__UVD_POWER_STATUS_MASK);

	/* disable dynamic घातer gating mode */
	WREG32_P(SOC15_REG_OFFSET(VCN, inst_idx, mmUVD_POWER_STATUS), 0,
			~UVD_POWER_STATUS__UVD_PG_MODE_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v2_5_stop(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t पंचांगp;
	पूर्णांक i, r = 0;

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;
		अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG) अणु
			r = vcn_v2_5_stop_dpg_mode(adev, i);
			जारी;
		पूर्ण

		/* रुको क्रम vcn idle */
		r = SOC15_WAIT_ON_RREG(VCN, i, mmUVD_STATUS, UVD_STATUS__IDLE, 0x7);
		अगर (r)
			वापस r;

		पंचांगp = UVD_LMI_STATUS__VCPU_LMI_WRITE_CLEAN_MASK |
			UVD_LMI_STATUS__READ_CLEAN_MASK |
			UVD_LMI_STATUS__WRITE_CLEAN_MASK |
			UVD_LMI_STATUS__WRITE_CLEAN_RAW_MASK;
		r = SOC15_WAIT_ON_RREG(VCN, i, mmUVD_LMI_STATUS, पंचांगp, पंचांगp);
		अगर (r)
			वापस r;

		/* block LMI UMC channel */
		पंचांगp = RREG32_SOC15(VCN, i, mmUVD_LMI_CTRL2);
		पंचांगp |= UVD_LMI_CTRL2__STALL_ARB_UMC_MASK;
		WREG32_SOC15(VCN, i, mmUVD_LMI_CTRL2, पंचांगp);

		पंचांगp = UVD_LMI_STATUS__UMC_READ_CLEAN_RAW_MASK|
			UVD_LMI_STATUS__UMC_WRITE_CLEAN_RAW_MASK;
		r = SOC15_WAIT_ON_RREG(VCN, i, mmUVD_LMI_STATUS, पंचांगp, पंचांगp);
		अगर (r)
			वापस r;

		/* block VCPU रेजिस्टर access */
		WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_RB_ARB_CTRL),
			UVD_RB_ARB_CTRL__VCPU_DIS_MASK,
			~UVD_RB_ARB_CTRL__VCPU_DIS_MASK);

		/* reset VCPU */
		WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_VCPU_CNTL),
			UVD_VCPU_CNTL__BLK_RST_MASK,
			~UVD_VCPU_CNTL__BLK_RST_MASK);

		/* disable VCPU घड़ी */
		WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_VCPU_CNTL), 0,
			~(UVD_VCPU_CNTL__CLK_EN_MASK));

		/* clear status */
		WREG32_SOC15(VCN, i, mmUVD_STATUS, 0);

		vcn_v2_5_enable_घड़ी_gating(adev);

		/* enable रेजिस्टर anti-hang mechanism */
		WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_POWER_STATUS),
			UVD_POWER_STATUS__UVD_POWER_STATUS_MASK,
			~UVD_POWER_STATUS__UVD_POWER_STATUS_MASK);
	पूर्ण

	अगर (adev->pm.dpm_enabled)
		amdgpu_dpm_enable_uvd(adev, false);

	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v2_5_छोड़ो_dpg_mode(काष्ठा amdgpu_device *adev,
				पूर्णांक inst_idx, काष्ठा dpg_छोड़ो_state *new_state)
अणु
	काष्ठा amdgpu_ring *ring;
	uपूर्णांक32_t reg_data = 0;
	पूर्णांक ret_code = 0;

	/* छोड़ो/unछोड़ो अगर state is changed */
	अगर (adev->vcn.inst[inst_idx].छोड़ो_state.fw_based != new_state->fw_based) अणु
		DRM_DEBUG("dpg pause state changed %d -> %d",
			adev->vcn.inst[inst_idx].छोड़ो_state.fw_based,	new_state->fw_based);
		reg_data = RREG32_SOC15(VCN, inst_idx, mmUVD_DPG_PAUSE) &
			(~UVD_DPG_PAUSE__NJ_PAUSE_DPG_ACK_MASK);

		अगर (new_state->fw_based == VCN_DPG_STATE__PAUSE) अणु
			ret_code = SOC15_WAIT_ON_RREG(VCN, inst_idx, mmUVD_POWER_STATUS, 0x1,
				UVD_POWER_STATUS__UVD_POWER_STATUS_MASK);

			अगर (!ret_code) अणु
				अस्थिर काष्ठा amdgpu_fw_shared *fw_shared = adev->vcn.inst[inst_idx].fw_shared_cpu_addr;

				/* छोड़ो DPG */
				reg_data |= UVD_DPG_PAUSE__NJ_PAUSE_DPG_REQ_MASK;
				WREG32_SOC15(VCN, inst_idx, mmUVD_DPG_PAUSE, reg_data);

				/* रुको क्रम ACK */
				SOC15_WAIT_ON_RREG(VCN, inst_idx, mmUVD_DPG_PAUSE,
					   UVD_DPG_PAUSE__NJ_PAUSE_DPG_ACK_MASK,
					   UVD_DPG_PAUSE__NJ_PAUSE_DPG_ACK_MASK);

				/* Stall DPG beक्रमe WPTR/RPTR reset */
				WREG32_P(SOC15_REG_OFFSET(VCN, inst_idx, mmUVD_POWER_STATUS),
					   UVD_POWER_STATUS__STALL_DPG_POWER_UP_MASK,
					   ~UVD_POWER_STATUS__STALL_DPG_POWER_UP_MASK);

				/* Restore */
				fw_shared->multi_queue.encode_generalpurpose_queue_mode |= FW_QUEUE_RING_RESET;
				ring = &adev->vcn.inst[inst_idx].ring_enc[0];
				ring->wptr = 0;
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_BASE_LO, ring->gpu_addr);
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_BASE_HI, upper_32_bits(ring->gpu_addr));
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_SIZE, ring->ring_size / 4);
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_RPTR, lower_32_bits(ring->wptr));
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_WPTR, lower_32_bits(ring->wptr));
				fw_shared->multi_queue.encode_generalpurpose_queue_mode &= ~FW_QUEUE_RING_RESET;

				fw_shared->multi_queue.encode_lowlatency_queue_mode |= FW_QUEUE_RING_RESET;
				ring = &adev->vcn.inst[inst_idx].ring_enc[1];
				ring->wptr = 0;
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_BASE_LO2, ring->gpu_addr);
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_BASE_HI2, upper_32_bits(ring->gpu_addr));
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_SIZE2, ring->ring_size / 4);
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_RPTR2, lower_32_bits(ring->wptr));
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_WPTR2, lower_32_bits(ring->wptr));
				fw_shared->multi_queue.encode_lowlatency_queue_mode &= ~FW_QUEUE_RING_RESET;

				/* Unstall DPG */
				WREG32_P(SOC15_REG_OFFSET(VCN, inst_idx, mmUVD_POWER_STATUS),
					   0, ~UVD_POWER_STATUS__STALL_DPG_POWER_UP_MASK);

				SOC15_WAIT_ON_RREG(VCN, inst_idx, mmUVD_POWER_STATUS,
					   UVD_PGFSM_CONFIG__UVDM_UVDU_PWR_ON, UVD_POWER_STATUS__UVD_POWER_STATUS_MASK);
			पूर्ण
		पूर्ण अन्यथा अणु
			reg_data &= ~UVD_DPG_PAUSE__NJ_PAUSE_DPG_REQ_MASK;
			WREG32_SOC15(VCN, inst_idx, mmUVD_DPG_PAUSE, reg_data);
			SOC15_WAIT_ON_RREG(VCN, inst_idx, mmUVD_POWER_STATUS, 0x1,
				UVD_POWER_STATUS__UVD_POWER_STATUS_MASK);
		पूर्ण
		adev->vcn.inst[inst_idx].छोड़ो_state.fw_based = new_state->fw_based;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vcn_v2_5_dec_ring_get_rptr - get पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t vcn_v2_5_dec_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32_SOC15(VCN, ring->me, mmUVD_RBC_RB_RPTR);
पूर्ण

/**
 * vcn_v2_5_dec_ring_get_wptr - get ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t vcn_v2_5_dec_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->use_करोorbell)
		वापस adev->wb.wb[ring->wptr_offs];
	अन्यथा
		वापस RREG32_SOC15(VCN, ring->me, mmUVD_RBC_RB_WPTR);
पूर्ण

/**
 * vcn_v2_5_dec_ring_set_wptr - set ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम vcn_v2_5_dec_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->use_करोorbell) अणु
		adev->wb.wb[ring->wptr_offs] = lower_32_bits(ring->wptr);
		WDOORBELL32(ring->करोorbell_index, lower_32_bits(ring->wptr));
	पूर्ण अन्यथा अणु
		WREG32_SOC15(VCN, ring->me, mmUVD_RBC_RB_WPTR, lower_32_bits(ring->wptr));
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा amdgpu_ring_funcs vcn_v2_5_dec_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_VCN_DEC,
	.align_mask = 0xf,
	.vmhub = AMDGPU_MMHUB_1,
	.get_rptr = vcn_v2_5_dec_ring_get_rptr,
	.get_wptr = vcn_v2_5_dec_ring_get_wptr,
	.set_wptr = vcn_v2_5_dec_ring_set_wptr,
	.emit_frame_size =
		SOC15_FLUSH_GPU_TLB_NUM_WREG * 6 +
		SOC15_FLUSH_GPU_TLB_NUM_REG_WAIT * 8 +
		8 + /* vcn_v2_0_dec_ring_emit_vm_flush */
		14 + 14 + /* vcn_v2_0_dec_ring_emit_fence x2 vm fence */
		6,
	.emit_ib_size = 8, /* vcn_v2_0_dec_ring_emit_ib */
	.emit_ib = vcn_v2_0_dec_ring_emit_ib,
	.emit_fence = vcn_v2_0_dec_ring_emit_fence,
	.emit_vm_flush = vcn_v2_0_dec_ring_emit_vm_flush,
	.test_ring = vcn_v2_0_dec_ring_test_ring,
	.test_ib = amdgpu_vcn_dec_ring_test_ib,
	.insert_nop = vcn_v2_0_dec_ring_insert_nop,
	.insert_start = vcn_v2_0_dec_ring_insert_start,
	.insert_end = vcn_v2_0_dec_ring_insert_end,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = amdgpu_vcn_ring_begin_use,
	.end_use = amdgpu_vcn_ring_end_use,
	.emit_wreg = vcn_v2_0_dec_ring_emit_wreg,
	.emit_reg_रुको = vcn_v2_0_dec_ring_emit_reg_रुको,
	.emit_reg_ग_लिखो_reg_रुको = amdgpu_ring_emit_reg_ग_लिखो_reg_रुको_helper,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs vcn_v2_6_dec_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_VCN_DEC,
	.align_mask = 0xf,
	.vmhub = AMDGPU_MMHUB_0,
	.get_rptr = vcn_v2_5_dec_ring_get_rptr,
	.get_wptr = vcn_v2_5_dec_ring_get_wptr,
	.set_wptr = vcn_v2_5_dec_ring_set_wptr,
	.emit_frame_size =
		SOC15_FLUSH_GPU_TLB_NUM_WREG * 6 +
		SOC15_FLUSH_GPU_TLB_NUM_REG_WAIT * 8 +
		8 + /* vcn_v2_0_dec_ring_emit_vm_flush */
		14 + 14 + /* vcn_v2_0_dec_ring_emit_fence x2 vm fence */
		6,
	.emit_ib_size = 8, /* vcn_v2_0_dec_ring_emit_ib */
	.emit_ib = vcn_v2_0_dec_ring_emit_ib,
	.emit_fence = vcn_v2_0_dec_ring_emit_fence,
	.emit_vm_flush = vcn_v2_0_dec_ring_emit_vm_flush,
	.test_ring = vcn_v2_0_dec_ring_test_ring,
	.test_ib = amdgpu_vcn_dec_ring_test_ib,
	.insert_nop = vcn_v2_0_dec_ring_insert_nop,
	.insert_start = vcn_v2_0_dec_ring_insert_start,
	.insert_end = vcn_v2_0_dec_ring_insert_end,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = amdgpu_vcn_ring_begin_use,
	.end_use = amdgpu_vcn_ring_end_use,
	.emit_wreg = vcn_v2_0_dec_ring_emit_wreg,
	.emit_reg_रुको = vcn_v2_0_dec_ring_emit_reg_रुको,
	.emit_reg_ग_लिखो_reg_रुको = amdgpu_ring_emit_reg_ग_लिखो_reg_रुको_helper,
पूर्ण;

/**
 * vcn_v2_5_enc_ring_get_rptr - get enc पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware enc पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t vcn_v2_5_enc_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring == &adev->vcn.inst[ring->me].ring_enc[0])
		वापस RREG32_SOC15(VCN, ring->me, mmUVD_RB_RPTR);
	अन्यथा
		वापस RREG32_SOC15(VCN, ring->me, mmUVD_RB_RPTR2);
पूर्ण

/**
 * vcn_v2_5_enc_ring_get_wptr - get enc ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware enc ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t vcn_v2_5_enc_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring == &adev->vcn.inst[ring->me].ring_enc[0]) अणु
		अगर (ring->use_करोorbell)
			वापस adev->wb.wb[ring->wptr_offs];
		अन्यथा
			वापस RREG32_SOC15(VCN, ring->me, mmUVD_RB_WPTR);
	पूर्ण अन्यथा अणु
		अगर (ring->use_करोorbell)
			वापस adev->wb.wb[ring->wptr_offs];
		अन्यथा
			वापस RREG32_SOC15(VCN, ring->me, mmUVD_RB_WPTR2);
	पूर्ण
पूर्ण

/**
 * vcn_v2_5_enc_ring_set_wptr - set enc ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the enc ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम vcn_v2_5_enc_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring == &adev->vcn.inst[ring->me].ring_enc[0]) अणु
		अगर (ring->use_करोorbell) अणु
			adev->wb.wb[ring->wptr_offs] = lower_32_bits(ring->wptr);
			WDOORBELL32(ring->करोorbell_index, lower_32_bits(ring->wptr));
		पूर्ण अन्यथा अणु
			WREG32_SOC15(VCN, ring->me, mmUVD_RB_WPTR, lower_32_bits(ring->wptr));
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ring->use_करोorbell) अणु
			adev->wb.wb[ring->wptr_offs] = lower_32_bits(ring->wptr);
			WDOORBELL32(ring->करोorbell_index, lower_32_bits(ring->wptr));
		पूर्ण अन्यथा अणु
			WREG32_SOC15(VCN, ring->me, mmUVD_RB_WPTR2, lower_32_bits(ring->wptr));
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा amdgpu_ring_funcs vcn_v2_5_enc_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_VCN_ENC,
	.align_mask = 0x3f,
	.nop = VCN_ENC_CMD_NO_OP,
	.vmhub = AMDGPU_MMHUB_1,
	.get_rptr = vcn_v2_5_enc_ring_get_rptr,
	.get_wptr = vcn_v2_5_enc_ring_get_wptr,
	.set_wptr = vcn_v2_5_enc_ring_set_wptr,
	.emit_frame_size =
		SOC15_FLUSH_GPU_TLB_NUM_WREG * 3 +
		SOC15_FLUSH_GPU_TLB_NUM_REG_WAIT * 4 +
		4 + /* vcn_v2_0_enc_ring_emit_vm_flush */
		5 + 5 + /* vcn_v2_0_enc_ring_emit_fence x2 vm fence */
		1, /* vcn_v2_0_enc_ring_insert_end */
	.emit_ib_size = 5, /* vcn_v2_0_enc_ring_emit_ib */
	.emit_ib = vcn_v2_0_enc_ring_emit_ib,
	.emit_fence = vcn_v2_0_enc_ring_emit_fence,
	.emit_vm_flush = vcn_v2_0_enc_ring_emit_vm_flush,
	.test_ring = amdgpu_vcn_enc_ring_test_ring,
	.test_ib = amdgpu_vcn_enc_ring_test_ib,
	.insert_nop = amdgpu_ring_insert_nop,
	.insert_end = vcn_v2_0_enc_ring_insert_end,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = amdgpu_vcn_ring_begin_use,
	.end_use = amdgpu_vcn_ring_end_use,
	.emit_wreg = vcn_v2_0_enc_ring_emit_wreg,
	.emit_reg_रुको = vcn_v2_0_enc_ring_emit_reg_रुको,
	.emit_reg_ग_लिखो_reg_रुको = amdgpu_ring_emit_reg_ग_लिखो_reg_रुको_helper,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs vcn_v2_6_enc_ring_vm_funcs = अणु
        .type = AMDGPU_RING_TYPE_VCN_ENC,
        .align_mask = 0x3f,
        .nop = VCN_ENC_CMD_NO_OP,
        .vmhub = AMDGPU_MMHUB_0,
        .get_rptr = vcn_v2_5_enc_ring_get_rptr,
        .get_wptr = vcn_v2_5_enc_ring_get_wptr,
        .set_wptr = vcn_v2_5_enc_ring_set_wptr,
        .emit_frame_size =
                SOC15_FLUSH_GPU_TLB_NUM_WREG * 3 +
                SOC15_FLUSH_GPU_TLB_NUM_REG_WAIT * 4 +
                4 + /* vcn_v2_0_enc_ring_emit_vm_flush */
                5 + 5 + /* vcn_v2_0_enc_ring_emit_fence x2 vm fence */
                1, /* vcn_v2_0_enc_ring_insert_end */
        .emit_ib_size = 5, /* vcn_v2_0_enc_ring_emit_ib */
        .emit_ib = vcn_v2_0_enc_ring_emit_ib,
        .emit_fence = vcn_v2_0_enc_ring_emit_fence,
        .emit_vm_flush = vcn_v2_0_enc_ring_emit_vm_flush,
        .test_ring = amdgpu_vcn_enc_ring_test_ring,
        .test_ib = amdgpu_vcn_enc_ring_test_ib,
        .insert_nop = amdgpu_ring_insert_nop,
        .insert_end = vcn_v2_0_enc_ring_insert_end,
        .pad_ib = amdgpu_ring_generic_pad_ib,
        .begin_use = amdgpu_vcn_ring_begin_use,
        .end_use = amdgpu_vcn_ring_end_use,
        .emit_wreg = vcn_v2_0_enc_ring_emit_wreg,
        .emit_reg_रुको = vcn_v2_0_enc_ring_emit_reg_रुको,
        .emit_reg_ग_लिखो_reg_रुको = amdgpu_ring_emit_reg_ग_लिखो_reg_रुको_helper,
पूर्ण;

अटल व्योम vcn_v2_5_set_dec_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;
		अगर (adev->asic_type == CHIP_ARCTURUS)
			adev->vcn.inst[i].ring_dec.funcs = &vcn_v2_5_dec_ring_vm_funcs;
		अन्यथा /* CHIP_ALDEBARAN */
			adev->vcn.inst[i].ring_dec.funcs = &vcn_v2_6_dec_ring_vm_funcs;
		adev->vcn.inst[i].ring_dec.me = i;
		DRM_INFO("VCN(%d) decode is enabled in VM mode\n", i);
	पूर्ण
पूर्ण

अटल व्योम vcn_v2_5_set_enc_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, j;

	क्रम (j = 0; j < adev->vcn.num_vcn_inst; ++j) अणु
		अगर (adev->vcn.harvest_config & (1 << j))
			जारी;
		क्रम (i = 0; i < adev->vcn.num_enc_rings; ++i) अणु
			अगर (adev->asic_type == CHIP_ARCTURUS)
				adev->vcn.inst[j].ring_enc[i].funcs = &vcn_v2_5_enc_ring_vm_funcs;
			अन्यथा /* CHIP_ALDEBARAN */
				adev->vcn.inst[j].ring_enc[i].funcs = &vcn_v2_6_enc_ring_vm_funcs;
			adev->vcn.inst[j].ring_enc[i].me = j;
		पूर्ण
		DRM_INFO("VCN(%d) encode is enabled in VM mode\n", j);
	पूर्ण
पूर्ण

अटल bool vcn_v2_5_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक i, ret = 1;

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;
		ret &= (RREG32_SOC15(VCN, i, mmUVD_STATUS) == UVD_STATUS__IDLE);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vcn_v2_5_रुको_क्रम_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;
		ret = SOC15_WAIT_ON_RREG(VCN, i, mmUVD_STATUS, UVD_STATUS__IDLE,
			UVD_STATUS__IDLE);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vcn_v2_5_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	bool enable = (state == AMD_CG_STATE_GATE);

	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	अगर (enable) अणु
		अगर (!vcn_v2_5_is_idle(handle))
			वापस -EBUSY;
		vcn_v2_5_enable_घड़ी_gating(adev);
	पूर्ण अन्यथा अणु
		vcn_v2_5_disable_घड़ी_gating(adev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v2_5_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक ret;

	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	अगर(state == adev->vcn.cur_state)
		वापस 0;

	अगर (state == AMD_PG_STATE_GATE)
		ret = vcn_v2_5_stop(adev);
	अन्यथा
		ret = vcn_v2_5_start(adev);

	अगर(!ret)
		adev->vcn.cur_state = state;

	वापस ret;
पूर्ण

अटल पूर्णांक vcn_v2_5_set_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v2_5_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
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

	DRM_DEBUG("IH: VCN TRAP\n");

	चयन (entry->src_id) अणु
	हाल VCN_2_0__SRCID__UVD_SYSTEM_MESSAGE_INTERRUPT:
		amdgpu_fence_process(&adev->vcn.inst[ip_instance].ring_dec);
		अवरोध;
	हाल VCN_2_0__SRCID__UVD_ENC_GENERAL_PURPOSE:
		amdgpu_fence_process(&adev->vcn.inst[ip_instance].ring_enc[0]);
		अवरोध;
	हाल VCN_2_0__SRCID__UVD_ENC_LOW_LATENCY:
		amdgpu_fence_process(&adev->vcn.inst[ip_instance].ring_enc[1]);
		अवरोध;
	शेष:
		DRM_ERROR("Unhandled interrupt: %d %d\n",
			  entry->src_id, entry->src_data[0]);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs vcn_v2_5_irq_funcs = अणु
	.set = vcn_v2_5_set_पूर्णांकerrupt_state,
	.process = vcn_v2_5_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम vcn_v2_5_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;
		adev->vcn.inst[i].irq.num_types = adev->vcn.num_enc_rings + 1;
		adev->vcn.inst[i].irq.funcs = &vcn_v2_5_irq_funcs;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs vcn_v2_5_ip_funcs = अणु
	.name = "vcn_v2_5",
	.early_init = vcn_v2_5_early_init,
	.late_init = शून्य,
	.sw_init = vcn_v2_5_sw_init,
	.sw_fini = vcn_v2_5_sw_fini,
	.hw_init = vcn_v2_5_hw_init,
	.hw_fini = vcn_v2_5_hw_fini,
	.suspend = vcn_v2_5_suspend,
	.resume = vcn_v2_5_resume,
	.is_idle = vcn_v2_5_is_idle,
	.रुको_क्रम_idle = vcn_v2_5_रुको_क्रम_idle,
	.check_soft_reset = शून्य,
	.pre_soft_reset = शून्य,
	.soft_reset = शून्य,
	.post_soft_reset = शून्य,
	.set_घड़ीgating_state = vcn_v2_5_set_घड़ीgating_state,
	.set_घातergating_state = vcn_v2_5_set_घातergating_state,
पूर्ण;

अटल स्थिर काष्ठा amd_ip_funcs vcn_v2_6_ip_funcs = अणु
        .name = "vcn_v2_6",
        .early_init = vcn_v2_5_early_init,
        .late_init = शून्य,
        .sw_init = vcn_v2_5_sw_init,
        .sw_fini = vcn_v2_5_sw_fini,
        .hw_init = vcn_v2_5_hw_init,
        .hw_fini = vcn_v2_5_hw_fini,
        .suspend = vcn_v2_5_suspend,
        .resume = vcn_v2_5_resume,
        .is_idle = vcn_v2_5_is_idle,
        .रुको_क्रम_idle = vcn_v2_5_रुको_क्रम_idle,
        .check_soft_reset = शून्य,
        .pre_soft_reset = शून्य,
        .soft_reset = शून्य,
        .post_soft_reset = शून्य,
        .set_घड़ीgating_state = vcn_v2_5_set_घड़ीgating_state,
        .set_घातergating_state = vcn_v2_5_set_घातergating_state,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version vcn_v2_5_ip_block =
अणु
		.type = AMD_IP_BLOCK_TYPE_VCN,
		.major = 2,
		.minor = 5,
		.rev = 0,
		.funcs = &vcn_v2_5_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version vcn_v2_6_ip_block =
अणु
		.type = AMD_IP_BLOCK_TYPE_VCN,
		.major = 2,
		.minor = 6,
		.rev = 0,
		.funcs = &vcn_v2_6_ip_funcs,
पूर्ण;
