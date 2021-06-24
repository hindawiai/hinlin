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
#समावेश "mmsch_v3_0.h"

#समावेश "vcn/vcn_3_0_0_offset.h"
#समावेश "vcn/vcn_3_0_0_sh_mask.h"
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

#घोषणा VCN_INSTANCES_SIENNA_CICHLID				2
#घोषणा DEC_SW_RING_ENABLED					FALSE

#घोषणा RDECODE_MSG_CREATE					0x00000000
#घोषणा RDECODE_MESSAGE_CREATE					0x00000001

अटल पूर्णांक amdgpu_ih_clientid_vcns[] = अणु
	SOC15_IH_CLIENTID_VCN,
	SOC15_IH_CLIENTID_VCN1
पूर्ण;

अटल पूर्णांक amdgpu_ucode_id_vcns[] = अणु
	AMDGPU_UCODE_ID_VCN,
	AMDGPU_UCODE_ID_VCN1
पूर्ण;

अटल पूर्णांक vcn_v3_0_start_sriov(काष्ठा amdgpu_device *adev);
अटल व्योम vcn_v3_0_set_dec_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम vcn_v3_0_set_enc_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम vcn_v3_0_set_irq_funcs(काष्ठा amdgpu_device *adev);
अटल पूर्णांक vcn_v3_0_set_घातergating_state(व्योम *handle,
			क्रमागत amd_घातergating_state state);
अटल पूर्णांक vcn_v3_0_छोड़ो_dpg_mode(काष्ठा amdgpu_device *adev,
			पूर्णांक inst_idx, काष्ठा dpg_छोड़ो_state *new_state);

अटल व्योम vcn_v3_0_dec_ring_set_wptr(काष्ठा amdgpu_ring *ring);
अटल व्योम vcn_v3_0_enc_ring_set_wptr(काष्ठा amdgpu_ring *ring);

/**
 * vcn_v3_0_early_init - set function poपूर्णांकers
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Set ring and irq function poपूर्णांकers
 */
अटल पूर्णांक vcn_v3_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev)) अणु
		adev->vcn.num_vcn_inst = VCN_INSTANCES_SIENNA_CICHLID;
		adev->vcn.harvest_config = 0;
		adev->vcn.num_enc_rings = 1;

	पूर्ण अन्यथा अणु
		अगर (adev->asic_type == CHIP_SIENNA_CICHLID) अणु
			u32 harvest;
			पूर्णांक i;

			adev->vcn.num_vcn_inst = VCN_INSTANCES_SIENNA_CICHLID;
			क्रम (i = 0; i < adev->vcn.num_vcn_inst; i++) अणु
				harvest = RREG32_SOC15(VCN, i, mmCC_UVD_HARVESTING);
				अगर (harvest & CC_UVD_HARVESTING__UVD_DISABLE_MASK)
					adev->vcn.harvest_config |= 1 << i;
			पूर्ण

			अगर (adev->vcn.harvest_config == (AMDGPU_VCN_HARVEST_VCN0 |
						AMDGPU_VCN_HARVEST_VCN1))
				/* both instances are harvested, disable the block */
				वापस -ENOENT;
		पूर्ण अन्यथा
			adev->vcn.num_vcn_inst = 1;

		adev->vcn.num_enc_rings = 2;
	पूर्ण

	vcn_v3_0_set_dec_ring_funcs(adev);
	vcn_v3_0_set_enc_ring_funcs(adev);
	vcn_v3_0_set_irq_funcs(adev);

	वापस 0;
पूर्ण

/**
 * vcn_v3_0_sw_init - sw init क्रम VCN block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Load firmware and sw initialization
 */
अटल पूर्णांक vcn_v3_0_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_ring *ring;
	पूर्णांक i, j, r;
	पूर्णांक vcn_करोorbell_index = 0;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

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

		अगर (adev->vcn.num_vcn_inst == VCN_INSTANCES_SIENNA_CICHLID) अणु
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

	/*
	 * Note: करोorbell assignment is fixed क्रम SRIOV multiple VCN engines
	 * Formula:
	 *   vcn_db_base  = adev->करोorbell_index.vcn.vcn_ring0_1 << 1;
	 *   dec_ring_i   = vcn_db_base + i * (adev->vcn.num_enc_rings + 1)
	 *   enc_ring_i,j = vcn_db_base + i * (adev->vcn.num_enc_rings + 1) + 1 + j
	 */
	अगर (amdgpu_sriov_vf(adev)) अणु
		vcn_करोorbell_index = adev->करोorbell_index.vcn.vcn_ring0_1;
		/* get DWORD offset */
		vcn_करोorbell_index = vcn_करोorbell_index << 1;
	पूर्ण

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; i++) अणु
		अस्थिर काष्ठा amdgpu_fw_shared *fw_shared;

		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;

		adev->vcn.पूर्णांकernal.context_id = mmUVD_CONTEXT_ID_INTERNAL_OFFSET;
		adev->vcn.पूर्णांकernal.ib_vmid = mmUVD_LMI_RBC_IB_VMID_INTERNAL_OFFSET;
		adev->vcn.पूर्णांकernal.ib_bar_low = mmUVD_LMI_RBC_IB_64BIT_BAR_LOW_INTERNAL_OFFSET;
		adev->vcn.पूर्णांकernal.ib_bar_high = mmUVD_LMI_RBC_IB_64BIT_BAR_HIGH_INTERNAL_OFFSET;
		adev->vcn.पूर्णांकernal.ib_size = mmUVD_RBC_IB_SIZE_INTERNAL_OFFSET;
		adev->vcn.पूर्णांकernal.gp_scratch8 = mmUVD_GP_SCRATCH8_INTERNAL_OFFSET;

		adev->vcn.पूर्णांकernal.scratch9 = mmUVD_SCRATCH9_INTERNAL_OFFSET;
		adev->vcn.inst[i].बाह्यal.scratch9 = SOC15_REG_OFFSET(VCN, i, mmUVD_SCRATCH9);
		adev->vcn.पूर्णांकernal.data0 = mmUVD_GPCOM_VCPU_DATA0_INTERNAL_OFFSET;
		adev->vcn.inst[i].बाह्यal.data0 = SOC15_REG_OFFSET(VCN, i, mmUVD_GPCOM_VCPU_DATA0);
		adev->vcn.पूर्णांकernal.data1 = mmUVD_GPCOM_VCPU_DATA1_INTERNAL_OFFSET;
		adev->vcn.inst[i].बाह्यal.data1 = SOC15_REG_OFFSET(VCN, i, mmUVD_GPCOM_VCPU_DATA1);
		adev->vcn.पूर्णांकernal.cmd = mmUVD_GPCOM_VCPU_CMD_INTERNAL_OFFSET;
		adev->vcn.inst[i].बाह्यal.cmd = SOC15_REG_OFFSET(VCN, i, mmUVD_GPCOM_VCPU_CMD);
		adev->vcn.पूर्णांकernal.nop = mmUVD_NO_OP_INTERNAL_OFFSET;
		adev->vcn.inst[i].बाह्यal.nop = SOC15_REG_OFFSET(VCN, i, mmUVD_NO_OP);

		/* VCN DEC TRAP */
		r = amdgpu_irq_add_id(adev, amdgpu_ih_clientid_vcns[i],
				VCN_2_0__SRCID__UVD_SYSTEM_MESSAGE_INTERRUPT, &adev->vcn.inst[i].irq);
		अगर (r)
			वापस r;

		atomic_set(&adev->vcn.inst[i].sched_score, 0);

		ring = &adev->vcn.inst[i].ring_dec;
		ring->use_करोorbell = true;
		अगर (amdgpu_sriov_vf(adev)) अणु
			ring->करोorbell_index = vcn_करोorbell_index + i * (adev->vcn.num_enc_rings + 1);
		पूर्ण अन्यथा अणु
			ring->करोorbell_index = (adev->करोorbell_index.vcn.vcn_ring0_1 << 1) + 8 * i;
		पूर्ण
		प्र_लिखो(ring->name, "vcn_dec_%d", i);
		r = amdgpu_ring_init(adev, ring, 512, &adev->vcn.inst[i].irq, 0,
				     AMDGPU_RING_PRIO_DEFAULT,
				     &adev->vcn.inst[i].sched_score);
		अगर (r)
			वापस r;

		क्रम (j = 0; j < adev->vcn.num_enc_rings; ++j) अणु
			/* VCN ENC TRAP */
			r = amdgpu_irq_add_id(adev, amdgpu_ih_clientid_vcns[i],
				j + VCN_2_0__SRCID__UVD_ENC_GENERAL_PURPOSE, &adev->vcn.inst[i].irq);
			अगर (r)
				वापस r;

			ring = &adev->vcn.inst[i].ring_enc[j];
			ring->use_करोorbell = true;
			अगर (amdgpu_sriov_vf(adev)) अणु
				ring->करोorbell_index = vcn_करोorbell_index + i * (adev->vcn.num_enc_rings + 1) + 1 + j;
			पूर्ण अन्यथा अणु
				ring->करोorbell_index = (adev->करोorbell_index.vcn.vcn_ring0_1 << 1) + 2 + j + 8 * i;
			पूर्ण
			प्र_लिखो(ring->name, "vcn_enc_%d.%d", i, j);
			r = amdgpu_ring_init(adev, ring, 512, &adev->vcn.inst[i].irq, 0,
					     AMDGPU_RING_PRIO_DEFAULT,
					     &adev->vcn.inst[i].sched_score);
			अगर (r)
				वापस r;
		पूर्ण

		fw_shared = adev->vcn.inst[i].fw_shared_cpu_addr;
		fw_shared->present_flag_0 |= cpu_to_le32(AMDGPU_VCN_SW_RING_FLAG) |
					     cpu_to_le32(AMDGPU_VCN_MULTI_QUEUE_FLAG) |
					     cpu_to_le32(AMDGPU_VCN_FW_SHARED_FLAG_0_RB);
		fw_shared->sw_ring.is_enabled = cpu_to_le32(DEC_SW_RING_ENABLED);
	पूर्ण

	अगर (amdgpu_sriov_vf(adev)) अणु
		r = amdgpu_virt_alloc_mm_table(adev);
		अगर (r)
			वापस r;
	पूर्ण
	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG)
		adev->vcn.छोड़ो_dpg_mode = vcn_v3_0_छोड़ो_dpg_mode;

	वापस 0;
पूर्ण

/**
 * vcn_v3_0_sw_fini - sw fini क्रम VCN block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * VCN suspend and मुक्त up sw allocation
 */
अटल पूर्णांक vcn_v3_0_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक i, r;

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; i++) अणु
		अस्थिर काष्ठा amdgpu_fw_shared *fw_shared;

		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;
		fw_shared = adev->vcn.inst[i].fw_shared_cpu_addr;
		fw_shared->present_flag_0 = 0;
		fw_shared->sw_ring.is_enabled = false;
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
 * vcn_v3_0_hw_init - start and test VCN block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Initialize the hardware, boot up the VCPU and करो some testing
 */
अटल पूर्णांक vcn_v3_0_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा amdgpu_ring *ring;
	पूर्णांक i, j, r;

	अगर (amdgpu_sriov_vf(adev)) अणु
		r = vcn_v3_0_start_sriov(adev);
		अगर (r)
			जाओ करोne;

		/* initialize VCN dec and enc ring buffers */
		क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
			अगर (adev->vcn.harvest_config & (1 << i))
				जारी;

			ring = &adev->vcn.inst[i].ring_dec;
			अगर (ring->sched.पढ़ोy) अणु
				ring->wptr = 0;
				ring->wptr_old = 0;
				vcn_v3_0_dec_ring_set_wptr(ring);
			पूर्ण

			क्रम (j = 0; j < adev->vcn.num_enc_rings; ++j) अणु
				ring = &adev->vcn.inst[i].ring_enc[j];
				अगर (ring->sched.पढ़ोy) अणु
					ring->wptr = 0;
					ring->wptr_old = 0;
					vcn_v3_0_enc_ring_set_wptr(ring);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
			अगर (adev->vcn.harvest_config & (1 << i))
				जारी;

			ring = &adev->vcn.inst[i].ring_dec;

			adev->nbio.funcs->vcn_करोorbell_range(adev, ring->use_करोorbell,
						     ring->करोorbell_index, i);

			r = amdgpu_ring_test_helper(ring);
			अगर (r)
				जाओ करोne;

			क्रम (j = 0; j < adev->vcn.num_enc_rings; ++j) अणु
				ring = &adev->vcn.inst[i].ring_enc[j];
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
 * vcn_v3_0_hw_fini - stop the hardware block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Stop the VCN block, mark ring as not पढ़ोy any more
 */
अटल पूर्णांक vcn_v3_0_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक i;

	cancel_delayed_work_sync(&adev->vcn.idle_work);

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;

		अगर (!amdgpu_sriov_vf(adev)) अणु
			अगर ((adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG) ||
					(adev->vcn.cur_state != AMD_PG_STATE_GATE &&
					 RREG32_SOC15(VCN, i, mmUVD_STATUS))) अणु
				vcn_v3_0_set_घातergating_state(adev, AMD_PG_STATE_GATE);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vcn_v3_0_suspend - suspend VCN block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * HW fini and suspend VCN block
 */
अटल पूर्णांक vcn_v3_0_suspend(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = vcn_v3_0_hw_fini(adev);
	अगर (r)
		वापस r;

	r = amdgpu_vcn_suspend(adev);

	वापस r;
पूर्ण

/**
 * vcn_v3_0_resume - resume VCN block
 *
 * @handle: amdgpu_device poपूर्णांकer
 *
 * Resume firmware and hw init VCN block
 */
अटल पूर्णांक vcn_v3_0_resume(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_vcn_resume(adev);
	अगर (r)
		वापस r;

	r = vcn_v3_0_hw_init(adev);

	वापस r;
पूर्ण

/**
 * vcn_v3_0_mc_resume - memory controller programming
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @inst: instance number
 *
 * Let the VCN memory controller know it's offsets
 */
अटल व्योम vcn_v3_0_mc_resume(काष्ठा amdgpu_device *adev, पूर्णांक inst)
अणु
	uपूर्णांक32_t size = AMDGPU_GPU_PAGE_ALIGN(adev->vcn.fw->size + 4);
	uपूर्णांक32_t offset;

	/* cache winकरोw 0: fw */
	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
		WREG32_SOC15(VCN, inst, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW,
			(adev->firmware.ucode[AMDGPU_UCODE_ID_VCN + inst].पंचांगr_mc_addr_lo));
		WREG32_SOC15(VCN, inst, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH,
			(adev->firmware.ucode[AMDGPU_UCODE_ID_VCN + inst].पंचांगr_mc_addr_hi));
		WREG32_SOC15(VCN, inst, mmUVD_VCPU_CACHE_OFFSET0, 0);
		offset = 0;
	पूर्ण अन्यथा अणु
		WREG32_SOC15(VCN, inst, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW,
			lower_32_bits(adev->vcn.inst[inst].gpu_addr));
		WREG32_SOC15(VCN, inst, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH,
			upper_32_bits(adev->vcn.inst[inst].gpu_addr));
		offset = size;
		WREG32_SOC15(VCN, inst, mmUVD_VCPU_CACHE_OFFSET0,
			AMDGPU_UVD_FIRMWARE_OFFSET >> 3);
	पूर्ण
	WREG32_SOC15(VCN, inst, mmUVD_VCPU_CACHE_SIZE0, size);

	/* cache winकरोw 1: stack */
	WREG32_SOC15(VCN, inst, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW,
		lower_32_bits(adev->vcn.inst[inst].gpu_addr + offset));
	WREG32_SOC15(VCN, inst, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH,
		upper_32_bits(adev->vcn.inst[inst].gpu_addr + offset));
	WREG32_SOC15(VCN, inst, mmUVD_VCPU_CACHE_OFFSET1, 0);
	WREG32_SOC15(VCN, inst, mmUVD_VCPU_CACHE_SIZE1, AMDGPU_VCN_STACK_SIZE);

	/* cache winकरोw 2: context */
	WREG32_SOC15(VCN, inst, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW,
		lower_32_bits(adev->vcn.inst[inst].gpu_addr + offset + AMDGPU_VCN_STACK_SIZE));
	WREG32_SOC15(VCN, inst, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH,
		upper_32_bits(adev->vcn.inst[inst].gpu_addr + offset + AMDGPU_VCN_STACK_SIZE));
	WREG32_SOC15(VCN, inst, mmUVD_VCPU_CACHE_OFFSET2, 0);
	WREG32_SOC15(VCN, inst, mmUVD_VCPU_CACHE_SIZE2, AMDGPU_VCN_CONTEXT_SIZE);

	/* non-cache winकरोw */
	WREG32_SOC15(VCN, inst, mmUVD_LMI_VCPU_NC0_64BIT_BAR_LOW,
		lower_32_bits(adev->vcn.inst[inst].fw_shared_gpu_addr));
	WREG32_SOC15(VCN, inst, mmUVD_LMI_VCPU_NC0_64BIT_BAR_HIGH,
		upper_32_bits(adev->vcn.inst[inst].fw_shared_gpu_addr));
	WREG32_SOC15(VCN, inst, mmUVD_VCPU_NONCACHE_OFFSET0, 0);
	WREG32_SOC15(VCN, inst, mmUVD_VCPU_NONCACHE_SIZE0,
		AMDGPU_GPU_PAGE_ALIGN(माप(काष्ठा amdgpu_fw_shared)));
पूर्ण

अटल व्योम vcn_v3_0_mc_resume_dpg_mode(काष्ठा amdgpu_device *adev, पूर्णांक inst_idx, bool indirect)
अणु
	uपूर्णांक32_t size = AMDGPU_GPU_PAGE_ALIGN(adev->vcn.fw->size + 4);
	uपूर्णांक32_t offset;

	/* cache winकरोw 0: fw */
	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
		अगर (!indirect) अणु
			WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, inst_idx, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW),
				(adev->firmware.ucode[AMDGPU_UCODE_ID_VCN + inst_idx].पंचांगr_mc_addr_lo), 0, indirect);
			WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, inst_idx, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH),
				(adev->firmware.ucode[AMDGPU_UCODE_ID_VCN + inst_idx].पंचांगr_mc_addr_hi), 0, indirect);
			WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, inst_idx, mmUVD_VCPU_CACHE_OFFSET0), 0, 0, indirect);
		पूर्ण अन्यथा अणु
			WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, inst_idx, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW), 0, 0, indirect);
			WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, inst_idx, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH), 0, 0, indirect);
			WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, inst_idx, mmUVD_VCPU_CACHE_OFFSET0), 0, 0, indirect);
		पूर्ण
		offset = 0;
	पूर्ण अन्यथा अणु
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW),
			lower_32_bits(adev->vcn.inst[inst_idx].gpu_addr), 0, indirect);
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH),
			upper_32_bits(adev->vcn.inst[inst_idx].gpu_addr), 0, indirect);
		offset = size;
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_CACHE_OFFSET0),
			AMDGPU_UVD_FIRMWARE_OFFSET >> 3, 0, indirect);
	पूर्ण

	अगर (!indirect)
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_CACHE_SIZE0), size, 0, indirect);
	अन्यथा
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_CACHE_SIZE0), 0, 0, indirect);

	/* cache winकरोw 1: stack */
	अगर (!indirect) अणु
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW),
			lower_32_bits(adev->vcn.inst[inst_idx].gpu_addr + offset), 0, indirect);
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH),
			upper_32_bits(adev->vcn.inst[inst_idx].gpu_addr + offset), 0, indirect);
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_CACHE_OFFSET1), 0, 0, indirect);
	पूर्ण अन्यथा अणु
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW), 0, 0, indirect);
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH), 0, 0, indirect);
		WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_CACHE_OFFSET1), 0, 0, indirect);
	पूर्ण
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_CACHE_SIZE1), AMDGPU_VCN_STACK_SIZE, 0, indirect);

	/* cache winकरोw 2: context */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW),
			lower_32_bits(adev->vcn.inst[inst_idx].gpu_addr + offset + AMDGPU_VCN_STACK_SIZE), 0, indirect);
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH),
			upper_32_bits(adev->vcn.inst[inst_idx].gpu_addr + offset + AMDGPU_VCN_STACK_SIZE), 0, indirect);
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_CACHE_OFFSET2), 0, 0, indirect);
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_CACHE_SIZE2), AMDGPU_VCN_CONTEXT_SIZE, 0, indirect);

	/* non-cache winकरोw */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_LMI_VCPU_NC0_64BIT_BAR_LOW),
			lower_32_bits(adev->vcn.inst[inst_idx].fw_shared_gpu_addr), 0, indirect);
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_LMI_VCPU_NC0_64BIT_BAR_HIGH),
			upper_32_bits(adev->vcn.inst[inst_idx].fw_shared_gpu_addr), 0, indirect);
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_NONCACHE_OFFSET0), 0, 0, indirect);
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, mmUVD_VCPU_NONCACHE_SIZE0),
			AMDGPU_GPU_PAGE_ALIGN(माप(काष्ठा amdgpu_fw_shared)), 0, indirect);

	/* VCN global tiling रेजिस्टरs */
	WREG32_SOC15_DPG_MODE(0, SOC15_DPG_MODE_OFFSET(
		UVD, 0, mmUVD_GFX10_ADDR_CONFIG), adev->gfx.config.gb_addr_config, 0, indirect);
पूर्ण

अटल व्योम vcn_v3_0_disable_अटल_घातer_gating(काष्ठा amdgpu_device *adev, पूर्णांक inst)
अणु
	uपूर्णांक32_t data = 0;

	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN) अणु
		data = (1 << UVD_PGFSM_CONFIG__UVDM_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDU_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDF_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDC_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDB_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVसूचीL_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDLM_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTD_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTE_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDE_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDAB_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDATD_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDNA_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDNB_PWR_CONFIG__SHIFT);

		WREG32_SOC15(VCN, inst, mmUVD_PGFSM_CONFIG, data);
		SOC15_WAIT_ON_RREG(VCN, inst, mmUVD_PGFSM_STATUS,
			UVD_PGFSM_STATUS__UVDM_UVDU_UVDLM_PWR_ON_3_0, 0x3F3FFFFF);
	पूर्ण अन्यथा अणु
		data = (1 << UVD_PGFSM_CONFIG__UVDM_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDU_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDF_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDC_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDB_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVसूचीL_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDLM_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDTD_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDTE_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDE_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDAB_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDATD_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDNA_PWR_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDNB_PWR_CONFIG__SHIFT);
		WREG32_SOC15(VCN, inst, mmUVD_PGFSM_CONFIG, data);
		SOC15_WAIT_ON_RREG(VCN, inst, mmUVD_PGFSM_STATUS, 0,  0x3F3FFFFF);
	पूर्ण

	data = RREG32_SOC15(VCN, inst, mmUVD_POWER_STATUS);
	data &= ~0x103;
	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN)
		data |= UVD_PGFSM_CONFIG__UVDM_UVDU_PWR_ON |
			UVD_POWER_STATUS__UVD_PG_EN_MASK;

	WREG32_SOC15(VCN, inst, mmUVD_POWER_STATUS, data);
पूर्ण

अटल व्योम vcn_v3_0_enable_अटल_घातer_gating(काष्ठा amdgpu_device *adev, पूर्णांक inst)
अणु
	uपूर्णांक32_t data;

	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN) अणु
		/* Beक्रमe घातer off, this indicator has to be turned on */
		data = RREG32_SOC15(VCN, inst, mmUVD_POWER_STATUS);
		data &= ~UVD_POWER_STATUS__UVD_POWER_STATUS_MASK;
		data |= UVD_POWER_STATUS__UVD_POWER_STATUS_TILES_OFF;
		WREG32_SOC15(VCN, inst, mmUVD_POWER_STATUS, data);

		data = (2 << UVD_PGFSM_CONFIG__UVDM_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDU_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDF_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDC_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDB_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVसूचीL_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDLM_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTD_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTE_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDE_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDAB_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDATD_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDNA_PWR_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDNB_PWR_CONFIG__SHIFT);
		WREG32_SOC15(VCN, inst, mmUVD_PGFSM_CONFIG, data);

		data = (2 << UVD_PGFSM_STATUS__UVDM_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDU_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDF_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDC_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDB_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVसूचीL_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDLM_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDTD_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDTE_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDE_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDAB_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDATD_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDNA_PWR_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDNB_PWR_STATUS__SHIFT);
		SOC15_WAIT_ON_RREG(VCN, inst, mmUVD_PGFSM_STATUS, data, 0x3F3FFFFF);
	पूर्ण
पूर्ण

/**
 * vcn_v3_0_disable_घड़ी_gating - disable VCN घड़ी gating
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @inst: instance number
 *
 * Disable घड़ी gating क्रम VCN block
 */
अटल व्योम vcn_v3_0_disable_घड़ी_gating(काष्ठा amdgpu_device *adev, पूर्णांक inst)
अणु
	uपूर्णांक32_t data;

	/* VCN disable CGC */
	data = RREG32_SOC15(VCN, inst, mmUVD_CGC_CTRL);
	अगर (adev->cg_flags & AMD_CG_SUPPORT_VCN_MGCG)
		data |= 1 << UVD_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
	अन्यथा
		data &= ~UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK;
	data |= 1 << UVD_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT;
	data |= 4 << UVD_CGC_CTRL__CLK_OFF_DELAY__SHIFT;
	WREG32_SOC15(VCN, inst, mmUVD_CGC_CTRL, data);

	data = RREG32_SOC15(VCN, inst, mmUVD_CGC_GATE);
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

	WREG32_SOC15(VCN, inst, mmUVD_CGC_GATE, data);

	SOC15_WAIT_ON_RREG(VCN, inst, mmUVD_CGC_GATE, 0,  0xFFFFFFFF);

	data = RREG32_SOC15(VCN, inst, mmUVD_CGC_CTRL);
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
	WREG32_SOC15(VCN, inst, mmUVD_CGC_CTRL, data);

	data = RREG32_SOC15(VCN, inst, mmUVD_SUVD_CGC_GATE);
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
		| UVD_SUVD_CGC_GATE__ENT_MASK
		| UVD_SUVD_CGC_GATE__IME_MASK
		| UVD_SUVD_CGC_GATE__SIT_HEVC_DEC_MASK
		| UVD_SUVD_CGC_GATE__SIT_HEVC_ENC_MASK
		| UVD_SUVD_CGC_GATE__SITE_MASK
		| UVD_SUVD_CGC_GATE__SRE_VP9_MASK
		| UVD_SUVD_CGC_GATE__SCM_VP9_MASK
		| UVD_SUVD_CGC_GATE__SIT_VP9_DEC_MASK
		| UVD_SUVD_CGC_GATE__SDB_VP9_MASK
		| UVD_SUVD_CGC_GATE__IME_HEVC_MASK
		| UVD_SUVD_CGC_GATE__EFC_MASK
		| UVD_SUVD_CGC_GATE__SAOE_MASK
		| UVD_SUVD_CGC_GATE__SRE_AV1_MASK
		| UVD_SUVD_CGC_GATE__FBC_PCLK_MASK
		| UVD_SUVD_CGC_GATE__FBC_CCLK_MASK
		| UVD_SUVD_CGC_GATE__SCM_AV1_MASK
		| UVD_SUVD_CGC_GATE__SMPA_MASK);
	WREG32_SOC15(VCN, inst, mmUVD_SUVD_CGC_GATE, data);

	data = RREG32_SOC15(VCN, inst, mmUVD_SUVD_CGC_GATE2);
	data |= (UVD_SUVD_CGC_GATE2__MPBE0_MASK
		| UVD_SUVD_CGC_GATE2__MPBE1_MASK
		| UVD_SUVD_CGC_GATE2__SIT_AV1_MASK
		| UVD_SUVD_CGC_GATE2__SDB_AV1_MASK
		| UVD_SUVD_CGC_GATE2__MPC1_MASK);
	WREG32_SOC15(VCN, inst, mmUVD_SUVD_CGC_GATE2, data);

	data = RREG32_SOC15(VCN, inst, mmUVD_SUVD_CGC_CTRL);
	data &= ~(UVD_SUVD_CGC_CTRL__SRE_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SIT_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SMP_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SCM_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SDB_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SCLR_MODE_MASK
		| UVD_SUVD_CGC_CTRL__ENT_MODE_MASK
		| UVD_SUVD_CGC_CTRL__IME_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SITE_MODE_MASK
		| UVD_SUVD_CGC_CTRL__EFC_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SAOE_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SMPA_MODE_MASK
		| UVD_SUVD_CGC_CTRL__MPBE0_MODE_MASK
		| UVD_SUVD_CGC_CTRL__MPBE1_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SIT_AV1_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SDB_AV1_MODE_MASK
		| UVD_SUVD_CGC_CTRL__MPC1_MODE_MASK
		| UVD_SUVD_CGC_CTRL__FBC_PCLK_MASK
		| UVD_SUVD_CGC_CTRL__FBC_CCLK_MASK);
	WREG32_SOC15(VCN, inst, mmUVD_SUVD_CGC_CTRL, data);
पूर्ण

अटल व्योम vcn_v3_0_घड़ी_gating_dpg_mode(काष्ठा amdgpu_device *adev,
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
		VCN, inst_idx, mmUVD_CGC_CTRL), reg_data, sram_sel, indirect);

	/* turn off घड़ी gating */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_CGC_GATE), 0, sram_sel, indirect);

	/* turn on SUVD घड़ी gating */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_SUVD_CGC_GATE), 1, sram_sel, indirect);

	/* turn on sw mode in UVD_SUVD_CGC_CTRL */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_SUVD_CGC_CTRL), 0, sram_sel, indirect);
पूर्ण

/**
 * vcn_v3_0_enable_घड़ी_gating - enable VCN घड़ी gating
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @inst: instance number
 *
 * Enable घड़ी gating क्रम VCN block
 */
अटल व्योम vcn_v3_0_enable_घड़ी_gating(काष्ठा amdgpu_device *adev, पूर्णांक inst)
अणु
	uपूर्णांक32_t data;

	/* enable VCN CGC */
	data = RREG32_SOC15(VCN, inst, mmUVD_CGC_CTRL);
	अगर (adev->cg_flags & AMD_CG_SUPPORT_VCN_MGCG)
		data |= 1 << UVD_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
	अन्यथा
		data |= 0 << UVD_CGC_CTRL__DYN_CLOCK_MODE__SHIFT;
	data |= 1 << UVD_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT;
	data |= 4 << UVD_CGC_CTRL__CLK_OFF_DELAY__SHIFT;
	WREG32_SOC15(VCN, inst, mmUVD_CGC_CTRL, data);

	data = RREG32_SOC15(VCN, inst, mmUVD_CGC_CTRL);
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
		| UVD_CGC_CTRL__MMSCH_MODE_MASK);
	WREG32_SOC15(VCN, inst, mmUVD_CGC_CTRL, data);

	data = RREG32_SOC15(VCN, inst, mmUVD_SUVD_CGC_CTRL);
	data |= (UVD_SUVD_CGC_CTRL__SRE_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SIT_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SMP_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SCM_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SDB_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SCLR_MODE_MASK
		| UVD_SUVD_CGC_CTRL__ENT_MODE_MASK
		| UVD_SUVD_CGC_CTRL__IME_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SITE_MODE_MASK
		| UVD_SUVD_CGC_CTRL__EFC_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SAOE_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SMPA_MODE_MASK
		| UVD_SUVD_CGC_CTRL__MPBE0_MODE_MASK
		| UVD_SUVD_CGC_CTRL__MPBE1_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SIT_AV1_MODE_MASK
		| UVD_SUVD_CGC_CTRL__SDB_AV1_MODE_MASK
		| UVD_SUVD_CGC_CTRL__MPC1_MODE_MASK
		| UVD_SUVD_CGC_CTRL__FBC_PCLK_MASK
		| UVD_SUVD_CGC_CTRL__FBC_CCLK_MASK);
	WREG32_SOC15(VCN, inst, mmUVD_SUVD_CGC_CTRL, data);
पूर्ण

अटल पूर्णांक vcn_v3_0_start_dpg_mode(काष्ठा amdgpu_device *adev, पूर्णांक inst_idx, bool indirect)
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
	vcn_v3_0_घड़ी_gating_dpg_mode(adev, 0, inst_idx, indirect);

	/* enable VCPU घड़ी */
	पंचांगp = (0xFF << UVD_VCPU_CNTL__PRB_TIMEOUT_VAL__SHIFT);
	पंचांगp |= UVD_VCPU_CNTL__CLK_EN_MASK;
	पंचांगp |= UVD_VCPU_CNTL__BLK_RST_MASK;
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_VCPU_CNTL), पंचांगp, 0, indirect);

	/* disable master पूर्णांकerupt */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_MASTINT_EN), 0, 0, indirect);

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
		VCN, inst_idx, mmUVD_LMI_CTRL), पंचांगp, 0, indirect);

	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_MPC_CNTL),
		0x2 << UVD_MPC_CNTL__REPLACEMENT_MODE__SHIFT, 0, indirect);

	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_MPC_SET_MUXA0),
		((0x1 << UVD_MPC_SET_MUXA0__VARA_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUXA0__VARA_2__SHIFT) |
		 (0x3 << UVD_MPC_SET_MUXA0__VARA_3__SHIFT) |
		 (0x4 << UVD_MPC_SET_MUXA0__VARA_4__SHIFT)), 0, indirect);

	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_MPC_SET_MUXB0),
		 ((0x1 << UVD_MPC_SET_MUXB0__VARB_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUXB0__VARB_2__SHIFT) |
		 (0x3 << UVD_MPC_SET_MUXB0__VARB_3__SHIFT) |
		 (0x4 << UVD_MPC_SET_MUXB0__VARB_4__SHIFT)), 0, indirect);

	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_MPC_SET_MUX),
		((0x0 << UVD_MPC_SET_MUX__SET_0__SHIFT) |
		 (0x1 << UVD_MPC_SET_MUX__SET_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUX__SET_2__SHIFT)), 0, indirect);

	vcn_v3_0_mc_resume_dpg_mode(adev, inst_idx, indirect);

	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_REG_XX_MASK), 0x10, 0, indirect);
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_RBC_XX_IB_REG_CHECK), 0x3, 0, indirect);

	/* enable LMI MC and UMC channels */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_LMI_CTRL2), 0, 0, indirect);

	/* unblock VCPU रेजिस्टर access */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_RB_ARB_CTRL), 0, 0, indirect);

	पंचांगp = (0xFF << UVD_VCPU_CNTL__PRB_TIMEOUT_VAL__SHIFT);
	पंचांगp |= UVD_VCPU_CNTL__CLK_EN_MASK;
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_VCPU_CNTL), पंचांगp, 0, indirect);

	/* enable master पूर्णांकerrupt */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_MASTINT_EN),
		UVD_MASTINT_EN__VCPU_EN_MASK, 0, indirect);

	/* add nop to workaround PSP size check */
	WREG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, mmUVD_VCPU_CNTL), पंचांगp, 0, indirect);

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
	fw_shared->multi_queue.decode_queue_mode |= cpu_to_le32(FW_QUEUE_RING_RESET);

	/* set the ग_लिखो poपूर्णांकer delay */
	WREG32_SOC15(VCN, inst_idx, mmUVD_RBC_RB_WPTR_CNTL, 0);

	/* set the wb address */
	WREG32_SOC15(VCN, inst_idx, mmUVD_RBC_RB_RPTR_ADDR,
		(upper_32_bits(ring->gpu_addr) >> 2));

	/* programm the RB_BASE क्रम ring buffer */
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

	/* Reset FW shared memory RBC WPTR/RPTR */
	fw_shared->rb.rptr = 0;
	fw_shared->rb.wptr = lower_32_bits(ring->wptr);

	/*resetting करोne, fw can check RB ring */
	fw_shared->multi_queue.decode_queue_mode &= cpu_to_le32(~FW_QUEUE_RING_RESET);

	/* Unstall DPG */
	WREG32_P(SOC15_REG_OFFSET(VCN, inst_idx, mmUVD_POWER_STATUS),
		0, ~UVD_POWER_STATUS__STALL_DPG_POWER_UP_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v3_0_start(काष्ठा amdgpu_device *adev)
अणु
	अस्थिर काष्ठा amdgpu_fw_shared *fw_shared;
	काष्ठा amdgpu_ring *ring;
	uपूर्णांक32_t rb_bufsz, पंचांगp;
	पूर्णांक i, j, k, r;

	अगर (adev->pm.dpm_enabled)
		amdgpu_dpm_enable_uvd(adev, true);

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;

		अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG)अणु
			r = vcn_v3_0_start_dpg_mode(adev, i, adev->vcn.indirect_sram);
			जारी;
		पूर्ण

		/* disable VCN घातer gating */
		vcn_v3_0_disable_अटल_घातer_gating(adev, i);

		/* set VCN status busy */
		पंचांगp = RREG32_SOC15(VCN, i, mmUVD_STATUS) | UVD_STATUS__UVD_BUSY;
		WREG32_SOC15(VCN, i, mmUVD_STATUS, पंचांगp);

		/*SW घड़ी gating */
		vcn_v3_0_disable_घड़ी_gating(adev, i);

		/* enable VCPU घड़ी */
		WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_VCPU_CNTL),
			UVD_VCPU_CNTL__CLK_EN_MASK, ~UVD_VCPU_CNTL__CLK_EN_MASK);

		/* disable master पूर्णांकerrupt */
		WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_MASTINT_EN), 0,
			~UVD_MASTINT_EN__VCPU_EN_MASK);

		/* enable LMI MC and UMC channels */
		WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_LMI_CTRL2), 0,
			~UVD_LMI_CTRL2__STALL_ARB_UMC_MASK);

		पंचांगp = RREG32_SOC15(VCN, i, mmUVD_SOFT_RESET);
		पंचांगp &= ~UVD_SOFT_RESET__LMI_SOFT_RESET_MASK;
		पंचांगp &= ~UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK;
		WREG32_SOC15(VCN, i, mmUVD_SOFT_RESET, पंचांगp);

		/* setup mmUVD_LMI_CTRL */
		पंचांगp = RREG32_SOC15(VCN, i, mmUVD_LMI_CTRL);
		WREG32_SOC15(VCN, i, mmUVD_LMI_CTRL, पंचांगp |
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

		vcn_v3_0_mc_resume(adev, i);

		/* VCN global tiling रेजिस्टरs */
		WREG32_SOC15(VCN, i, mmUVD_GFX10_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);

		/* unblock VCPU रेजिस्टर access */
		WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_RB_ARB_CTRL), 0,
			~UVD_RB_ARB_CTRL__VCPU_DIS_MASK);

		/* release VCPU reset to boot */
		WREG32_P(SOC15_REG_OFFSET(VCN, i, mmUVD_VCPU_CNTL), 0,
			~UVD_VCPU_CNTL__BLK_RST_MASK);

		क्रम (j = 0; j < 10; ++j) अणु
			uपूर्णांक32_t status;

			क्रम (k = 0; k < 100; ++k) अणु
				status = RREG32_SOC15(VCN, i, mmUVD_STATUS);
				अगर (status & 2)
					अवरोध;
				mdelay(10);
			पूर्ण
			r = 0;
			अगर (status & 2)
				अवरोध;

			DRM_ERROR("VCN[%d] decode not responding, trying to reset the VCPU!!!\n", i);
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
			DRM_ERROR("VCN[%d] decode not responding, giving up!!!\n", i);
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

		fw_shared = adev->vcn.inst[i].fw_shared_cpu_addr;
		fw_shared->multi_queue.decode_queue_mode |= cpu_to_le32(FW_QUEUE_RING_RESET);

		/* programm the RB_BASE क्रम ring buffer */
		WREG32_SOC15(VCN, i, mmUVD_LMI_RBC_RB_64BIT_BAR_LOW,
			lower_32_bits(ring->gpu_addr));
		WREG32_SOC15(VCN, i, mmUVD_LMI_RBC_RB_64BIT_BAR_HIGH,
			upper_32_bits(ring->gpu_addr));

		/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
		WREG32_SOC15(VCN, i, mmUVD_RBC_RB_RPTR, 0);

		WREG32_SOC15(VCN, i, mmUVD_SCRATCH2, 0);
		ring->wptr = RREG32_SOC15(VCN, i, mmUVD_RBC_RB_RPTR);
		WREG32_SOC15(VCN, i, mmUVD_RBC_RB_WPTR,
			lower_32_bits(ring->wptr));
		fw_shared->rb.wptr = lower_32_bits(ring->wptr);
		fw_shared->multi_queue.decode_queue_mode &= cpu_to_le32(~FW_QUEUE_RING_RESET);

		fw_shared->multi_queue.encode_generalpurpose_queue_mode |= cpu_to_le32(FW_QUEUE_RING_RESET);
		ring = &adev->vcn.inst[i].ring_enc[0];
		WREG32_SOC15(VCN, i, mmUVD_RB_RPTR, lower_32_bits(ring->wptr));
		WREG32_SOC15(VCN, i, mmUVD_RB_WPTR, lower_32_bits(ring->wptr));
		WREG32_SOC15(VCN, i, mmUVD_RB_BASE_LO, ring->gpu_addr);
		WREG32_SOC15(VCN, i, mmUVD_RB_BASE_HI, upper_32_bits(ring->gpu_addr));
		WREG32_SOC15(VCN, i, mmUVD_RB_SIZE, ring->ring_size / 4);
		fw_shared->multi_queue.encode_generalpurpose_queue_mode &= cpu_to_le32(~FW_QUEUE_RING_RESET);

		fw_shared->multi_queue.encode_lowlatency_queue_mode |= cpu_to_le32(FW_QUEUE_RING_RESET);
		ring = &adev->vcn.inst[i].ring_enc[1];
		WREG32_SOC15(VCN, i, mmUVD_RB_RPTR2, lower_32_bits(ring->wptr));
		WREG32_SOC15(VCN, i, mmUVD_RB_WPTR2, lower_32_bits(ring->wptr));
		WREG32_SOC15(VCN, i, mmUVD_RB_BASE_LO2, ring->gpu_addr);
		WREG32_SOC15(VCN, i, mmUVD_RB_BASE_HI2, upper_32_bits(ring->gpu_addr));
		WREG32_SOC15(VCN, i, mmUVD_RB_SIZE2, ring->ring_size / 4);
		fw_shared->multi_queue.encode_lowlatency_queue_mode &= cpu_to_le32(~FW_QUEUE_RING_RESET);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v3_0_start_sriov(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, j;
	काष्ठा amdgpu_ring *ring;
	uपूर्णांक64_t cache_addr;
	uपूर्णांक64_t rb_addr;
	uपूर्णांक64_t ctx_addr;
	uपूर्णांक32_t param, resp, expected;
	uपूर्णांक32_t offset, cache_size;
	uपूर्णांक32_t पंचांगp, समयout;
	uपूर्णांक32_t id;

	काष्ठा amdgpu_mm_table *table = &adev->virt.mm_table;
	uपूर्णांक32_t *table_loc;
	uपूर्णांक32_t table_size;
	uपूर्णांक32_t size, size_dw;

	bool is_vcn_पढ़ोy;

	काष्ठा mmsch_v3_0_cmd_direct_ग_लिखो
		direct_wt = अणु अणु0पूर्ण पूर्ण;
	काष्ठा mmsch_v3_0_cmd_direct_पढ़ो_modअगरy_ग_लिखो
		direct_rd_mod_wt = अणु अणु0पूर्ण पूर्ण;
	काष्ठा mmsch_v3_0_cmd_end end = अणु अणु0पूर्ण पूर्ण;
	काष्ठा mmsch_v3_0_init_header header;

	direct_wt.cmd_header.command_type =
		MMSCH_COMMAND__सूचीECT_REG_WRITE;
	direct_rd_mod_wt.cmd_header.command_type =
		MMSCH_COMMAND__सूचीECT_REG_READ_MODIFY_WRITE;
	end.cmd_header.command_type =
		MMSCH_COMMAND__END;

	header.version = MMSCH_VERSION;
	header.total_size = माप(काष्ठा mmsch_v3_0_init_header) >> 2;
	क्रम (i = 0; i < AMDGPU_MAX_VCN_INSTANCES; i++) अणु
		header.inst[i].init_status = 0;
		header.inst[i].table_offset = 0;
		header.inst[i].table_size = 0;
	पूर्ण

	table_loc = (uपूर्णांक32_t *)table->cpu_addr;
	table_loc += header.total_size;
	क्रम (i = 0; i < adev->vcn.num_vcn_inst; i++) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;

		table_size = 0;

		MMSCH_V3_0_INSERT_सूचीECT_RD_MOD_WT(SOC15_REG_OFFSET(VCN, i,
			mmUVD_STATUS),
			~UVD_STATUS__UVD_BUSY, UVD_STATUS__UVD_BUSY);

		cache_size = AMDGPU_GPU_PAGE_ALIGN(adev->vcn.fw->size + 4);

		अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
			id = amdgpu_ucode_id_vcns[i];
			MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
				mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW),
				adev->firmware.ucode[id].पंचांगr_mc_addr_lo);
			MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
				mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH),
				adev->firmware.ucode[id].पंचांगr_mc_addr_hi);
			offset = 0;
			MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
				mmUVD_VCPU_CACHE_OFFSET0),
				0);
		पूर्ण अन्यथा अणु
			MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
				mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW),
				lower_32_bits(adev->vcn.inst[i].gpu_addr));
			MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
				mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH),
				upper_32_bits(adev->vcn.inst[i].gpu_addr));
			offset = cache_size;
			MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
				mmUVD_VCPU_CACHE_OFFSET0),
				AMDGPU_UVD_FIRMWARE_OFFSET >> 3);
		पूर्ण

		MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
			mmUVD_VCPU_CACHE_SIZE0),
			cache_size);

		cache_addr = adev->vcn.inst[i].gpu_addr + offset;
		MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
			mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW),
			lower_32_bits(cache_addr));
		MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
			mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH),
			upper_32_bits(cache_addr));
		MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
			mmUVD_VCPU_CACHE_OFFSET1),
			0);
		MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
			mmUVD_VCPU_CACHE_SIZE1),
			AMDGPU_VCN_STACK_SIZE);

		cache_addr = adev->vcn.inst[i].gpu_addr + offset +
			AMDGPU_VCN_STACK_SIZE;
		MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
			mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW),
			lower_32_bits(cache_addr));
		MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
			mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH),
			upper_32_bits(cache_addr));
		MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
			mmUVD_VCPU_CACHE_OFFSET2),
			0);
		MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
			mmUVD_VCPU_CACHE_SIZE2),
			AMDGPU_VCN_CONTEXT_SIZE);

		क्रम (j = 0; j < adev->vcn.num_enc_rings; ++j) अणु
			ring = &adev->vcn.inst[i].ring_enc[j];
			ring->wptr = 0;
			rb_addr = ring->gpu_addr;
			MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
				mmUVD_RB_BASE_LO),
				lower_32_bits(rb_addr));
			MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
				mmUVD_RB_BASE_HI),
				upper_32_bits(rb_addr));
			MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
				mmUVD_RB_SIZE),
				ring->ring_size / 4);
		पूर्ण

		ring = &adev->vcn.inst[i].ring_dec;
		ring->wptr = 0;
		rb_addr = ring->gpu_addr;
		MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
			mmUVD_LMI_RBC_RB_64BIT_BAR_LOW),
			lower_32_bits(rb_addr));
		MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
			mmUVD_LMI_RBC_RB_64BIT_BAR_HIGH),
			upper_32_bits(rb_addr));
		/* क्रमce RBC पूर्णांकo idle state */
		पंचांगp = order_base_2(ring->ring_size);
		पंचांगp = REG_SET_FIELD(0, UVD_RBC_RB_CNTL, RB_BUFSZ, पंचांगp);
		पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_BLKSZ, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_FETCH, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_UPDATE, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_RPTR_WR_EN, 1);
		MMSCH_V3_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(VCN, i,
			mmUVD_RBC_RB_CNTL),
			पंचांगp);

		/* add end packet */
		MMSCH_V3_0_INSERT_END();

		/* refine header */
		header.inst[i].init_status = 0;
		header.inst[i].table_offset = header.total_size;
		header.inst[i].table_size = table_size;
		header.total_size += table_size;
	पूर्ण

	/* Update init table header in memory */
	size = माप(काष्ठा mmsch_v3_0_init_header);
	table_loc = (uपूर्णांक32_t *)table->cpu_addr;
	स_नकल((व्योम *)table_loc, &header, size);

	/* message MMSCH (in VCN[0]) to initialize this client
	 * 1, ग_लिखो to mmsch_vf_ctx_addr_lo/hi रेजिस्टर with GPU mc addr
	 * of memory descriptor location
	 */
	ctx_addr = table->gpu_addr;
	WREG32_SOC15(VCN, 0, mmMMSCH_VF_CTX_ADDR_LO, lower_32_bits(ctx_addr));
	WREG32_SOC15(VCN, 0, mmMMSCH_VF_CTX_ADDR_HI, upper_32_bits(ctx_addr));

	/* 2, update vmid of descriptor */
	पंचांगp = RREG32_SOC15(VCN, 0, mmMMSCH_VF_VMID);
	पंचांगp &= ~MMSCH_VF_VMID__VF_CTX_VMID_MASK;
	/* use करोमुख्य0 क्रम MM scheduler */
	पंचांगp |= (0 << MMSCH_VF_VMID__VF_CTX_VMID__SHIFT);
	WREG32_SOC15(VCN, 0, mmMMSCH_VF_VMID, पंचांगp);

	/* 3, notअगरy mmsch about the size of this descriptor */
	size = header.total_size;
	WREG32_SOC15(VCN, 0, mmMMSCH_VF_CTX_SIZE, size);

	/* 4, set resp to zero */
	WREG32_SOC15(VCN, 0, mmMMSCH_VF_MAILBOX_RESP, 0);

	/* 5, kick off the initialization and रुको until
	 * MMSCH_VF_MAILBOX_RESP becomes non-zero
	 */
	param = 0x10000001;
	WREG32_SOC15(VCN, 0, mmMMSCH_VF_MAILBOX_HOST, param);
	पंचांगp = 0;
	समयout = 1000;
	resp = 0;
	expected = param + 1;
	जबतक (resp != expected) अणु
		resp = RREG32_SOC15(VCN, 0, mmMMSCH_VF_MAILBOX_RESP);
		अगर (resp == expected)
			अवरोध;

		udelay(10);
		पंचांगp = पंचांगp + 10;
		अगर (पंचांगp >= समयout) अणु
			DRM_ERROR("failed to init MMSCH. TIME-OUT after %d usec"\
				" waiting for mmMMSCH_VF_MAILBOX_RESP "\
				"(expected=0x%08x, readback=0x%08x)\n",
				पंचांगp, expected, resp);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* 6, check each VCN's init_status
	 * अगर it reमुख्यs as 0, then this VCN is not asचिन्हित to current VF
	 * करो not start ring क्रम this VCN
	 */
	size = माप(काष्ठा mmsch_v3_0_init_header);
	table_loc = (uपूर्णांक32_t *)table->cpu_addr;
	स_नकल(&header, (व्योम *)table_loc, size);

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; i++) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;

		is_vcn_पढ़ोy = (header.inst[i].init_status == 1);
		अगर (!is_vcn_पढ़ोy)
			DRM_INFO("VCN(%d) engine is disabled by hypervisor\n", i);

		ring = &adev->vcn.inst[i].ring_dec;
		ring->sched.पढ़ोy = is_vcn_पढ़ोy;
		क्रम (j = 0; j < adev->vcn.num_enc_rings; ++j) अणु
			ring = &adev->vcn.inst[i].ring_enc[j];
			ring->sched.पढ़ोy = is_vcn_पढ़ोy;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v3_0_stop_dpg_mode(काष्ठा amdgpu_device *adev, पूर्णांक inst_idx)
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

अटल पूर्णांक vcn_v3_0_stop(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t पंचांगp;
	पूर्णांक i, r = 0;

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;

		अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG) अणु
			r = vcn_v3_0_stop_dpg_mode(adev, i);
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

		/* disable LMI UMC channel */
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

		/* apply soft reset */
		पंचांगp = RREG32_SOC15(VCN, i, mmUVD_SOFT_RESET);
		पंचांगp |= UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK;
		WREG32_SOC15(VCN, i, mmUVD_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32_SOC15(VCN, i, mmUVD_SOFT_RESET);
		पंचांगp |= UVD_SOFT_RESET__LMI_SOFT_RESET_MASK;
		WREG32_SOC15(VCN, i, mmUVD_SOFT_RESET, पंचांगp);

		/* clear status */
		WREG32_SOC15(VCN, i, mmUVD_STATUS, 0);

		/* apply HW घड़ी gating */
		vcn_v3_0_enable_घड़ी_gating(adev, i);

		/* enable VCN घातer gating */
		vcn_v3_0_enable_अटल_घातer_gating(adev, i);
	पूर्ण

	अगर (adev->pm.dpm_enabled)
		amdgpu_dpm_enable_uvd(adev, false);

	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v3_0_छोड़ो_dpg_mode(काष्ठा amdgpu_device *adev,
		   पूर्णांक inst_idx, काष्ठा dpg_छोड़ो_state *new_state)
अणु
	अस्थिर काष्ठा amdgpu_fw_shared *fw_shared;
	काष्ठा amdgpu_ring *ring;
	uपूर्णांक32_t reg_data = 0;
	पूर्णांक ret_code;

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
				fw_shared = adev->vcn.inst[inst_idx].fw_shared_cpu_addr;
				fw_shared->multi_queue.encode_generalpurpose_queue_mode |= cpu_to_le32(FW_QUEUE_RING_RESET);
				ring = &adev->vcn.inst[inst_idx].ring_enc[0];
				ring->wptr = 0;
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_BASE_LO, ring->gpu_addr);
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_BASE_HI, upper_32_bits(ring->gpu_addr));
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_SIZE, ring->ring_size / 4);
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_RPTR, lower_32_bits(ring->wptr));
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_WPTR, lower_32_bits(ring->wptr));
				fw_shared->multi_queue.encode_generalpurpose_queue_mode &= cpu_to_le32(~FW_QUEUE_RING_RESET);

				fw_shared->multi_queue.encode_lowlatency_queue_mode |= cpu_to_le32(FW_QUEUE_RING_RESET);
				ring = &adev->vcn.inst[inst_idx].ring_enc[1];
				ring->wptr = 0;
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_BASE_LO2, ring->gpu_addr);
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_BASE_HI2, upper_32_bits(ring->gpu_addr));
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_SIZE2, ring->ring_size / 4);
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_RPTR2, lower_32_bits(ring->wptr));
				WREG32_SOC15(VCN, inst_idx, mmUVD_RB_WPTR2, lower_32_bits(ring->wptr));
				fw_shared->multi_queue.encode_lowlatency_queue_mode &= cpu_to_le32(~FW_QUEUE_RING_RESET);

				/* restore wptr/rptr with poपूर्णांकers saved in FW shared memory*/
				WREG32_SOC15(VCN, inst_idx, mmUVD_RBC_RB_RPTR, fw_shared->rb.rptr);
				WREG32_SOC15(VCN, inst_idx, mmUVD_RBC_RB_WPTR, fw_shared->rb.wptr);

				/* Unstall DPG */
				WREG32_P(SOC15_REG_OFFSET(VCN, inst_idx, mmUVD_POWER_STATUS),
					0, ~UVD_POWER_STATUS__STALL_DPG_POWER_UP_MASK);

				SOC15_WAIT_ON_RREG(VCN, inst_idx, mmUVD_POWER_STATUS,
					UVD_PGFSM_CONFIG__UVDM_UVDU_PWR_ON, UVD_POWER_STATUS__UVD_POWER_STATUS_MASK);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* unछोड़ो dpg, no need to रुको */
			reg_data &= ~UVD_DPG_PAUSE__NJ_PAUSE_DPG_REQ_MASK;
			WREG32_SOC15(VCN, inst_idx, mmUVD_DPG_PAUSE, reg_data);
		पूर्ण
		adev->vcn.inst[inst_idx].छोड़ो_state.fw_based = new_state->fw_based;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vcn_v3_0_dec_ring_get_rptr - get पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t vcn_v3_0_dec_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32_SOC15(VCN, ring->me, mmUVD_RBC_RB_RPTR);
पूर्ण

/**
 * vcn_v3_0_dec_ring_get_wptr - get ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t vcn_v3_0_dec_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->use_करोorbell)
		वापस adev->wb.wb[ring->wptr_offs];
	अन्यथा
		वापस RREG32_SOC15(VCN, ring->me, mmUVD_RBC_RB_WPTR);
पूर्ण

/**
 * vcn_v3_0_dec_ring_set_wptr - set ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम vcn_v3_0_dec_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	अस्थिर काष्ठा amdgpu_fw_shared *fw_shared;

	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG) अणु
		/*whenever update RBC_RB_WPTR, we save the wptr in shared rb.wptr and scratch2 */
		fw_shared = adev->vcn.inst[ring->me].fw_shared_cpu_addr;
		fw_shared->rb.wptr = lower_32_bits(ring->wptr);
		WREG32_SOC15(VCN, ring->me, mmUVD_SCRATCH2,
			lower_32_bits(ring->wptr));
	पूर्ण

	अगर (ring->use_करोorbell) अणु
		adev->wb.wb[ring->wptr_offs] = lower_32_bits(ring->wptr);
		WDOORBELL32(ring->करोorbell_index, lower_32_bits(ring->wptr));
	पूर्ण अन्यथा अणु
		WREG32_SOC15(VCN, ring->me, mmUVD_RBC_RB_WPTR, lower_32_bits(ring->wptr));
	पूर्ण
पूर्ण

अटल व्योम vcn_v3_0_dec_sw_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr,
				u64 seq, uपूर्णांक32_t flags)
अणु
	WARN_ON(flags & AMDGPU_FENCE_FLAG_64BIT);

	amdgpu_ring_ग_लिखो(ring, VCN_DEC_SW_CMD_FENCE);
	amdgpu_ring_ग_लिखो(ring, addr);
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, seq);
	amdgpu_ring_ग_लिखो(ring, VCN_DEC_SW_CMD_TRAP);
पूर्ण

अटल व्योम vcn_v3_0_dec_sw_ring_insert_end(काष्ठा amdgpu_ring *ring)
अणु
	amdgpu_ring_ग_लिखो(ring, VCN_DEC_SW_CMD_END);
पूर्ण

अटल व्योम vcn_v3_0_dec_sw_ring_emit_ib(काष्ठा amdgpu_ring *ring,
			       काष्ठा amdgpu_job *job,
			       काष्ठा amdgpu_ib *ib,
			       uपूर्णांक32_t flags)
अणु
	uपूर्णांक32_t vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_ring_ग_लिखो(ring, VCN_DEC_SW_CMD_IB);
	amdgpu_ring_ग_लिखो(ring, vmid);
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, ib->length_dw);
पूर्ण

अटल व्योम vcn_v3_0_dec_sw_ring_emit_reg_रुको(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t reg,
				uपूर्णांक32_t val, uपूर्णांक32_t mask)
अणु
	amdgpu_ring_ग_लिखो(ring, VCN_DEC_SW_CMD_REG_WAIT);
	amdgpu_ring_ग_लिखो(ring, reg << 2);
	amdgpu_ring_ग_लिखो(ring, mask);
	amdgpu_ring_ग_लिखो(ring, val);
पूर्ण

अटल व्योम vcn_v3_0_dec_sw_ring_emit_vm_flush(काष्ठा amdgpu_ring *ring,
				uपूर्णांक32_t vmid, uपूर्णांक64_t pd_addr)
अणु
	काष्ठा amdgpu_vmhub *hub = &ring->adev->vmhub[ring->funcs->vmhub];
	uपूर्णांक32_t data0, data1, mask;

	pd_addr = amdgpu_gmc_emit_flush_gpu_tlb(ring, vmid, pd_addr);

	/* रुको क्रम रेजिस्टर ग_लिखो */
	data0 = hub->ctx0_ptb_addr_lo32 + vmid * hub->ctx_addr_distance;
	data1 = lower_32_bits(pd_addr);
	mask = 0xffffffff;
	vcn_v3_0_dec_sw_ring_emit_reg_रुको(ring, data0, data1, mask);
पूर्ण

अटल व्योम vcn_v3_0_dec_sw_ring_emit_wreg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	amdgpu_ring_ग_लिखो(ring, VCN_DEC_SW_CMD_REG_WRITE);
	amdgpu_ring_ग_लिखो(ring,	reg << 2);
	amdgpu_ring_ग_लिखो(ring, val);
पूर्ण

अटल स्थिर काष्ठा amdgpu_ring_funcs vcn_v3_0_dec_sw_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_VCN_DEC,
	.align_mask = 0x3f,
	.nop = VCN_DEC_SW_CMD_NO_OP,
	.vmhub = AMDGPU_MMHUB_0,
	.get_rptr = vcn_v3_0_dec_ring_get_rptr,
	.get_wptr = vcn_v3_0_dec_ring_get_wptr,
	.set_wptr = vcn_v3_0_dec_ring_set_wptr,
	.emit_frame_size =
		SOC15_FLUSH_GPU_TLB_NUM_WREG * 3 +
		SOC15_FLUSH_GPU_TLB_NUM_REG_WAIT * 4 +
		4 + /* vcn_v3_0_dec_sw_ring_emit_vm_flush */
		5 + 5 + /* vcn_v3_0_dec_sw_ring_emit_fdec_swe x2 vm fdec_swe */
		1, /* vcn_v3_0_dec_sw_ring_insert_end */
	.emit_ib_size = 5, /* vcn_v3_0_dec_sw_ring_emit_ib */
	.emit_ib = vcn_v3_0_dec_sw_ring_emit_ib,
	.emit_fence = vcn_v3_0_dec_sw_ring_emit_fence,
	.emit_vm_flush = vcn_v3_0_dec_sw_ring_emit_vm_flush,
	.test_ring = amdgpu_vcn_dec_sw_ring_test_ring,
	.test_ib = शून्य,//amdgpu_vcn_dec_sw_ring_test_ib,
	.insert_nop = amdgpu_ring_insert_nop,
	.insert_end = vcn_v3_0_dec_sw_ring_insert_end,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = amdgpu_vcn_ring_begin_use,
	.end_use = amdgpu_vcn_ring_end_use,
	.emit_wreg = vcn_v3_0_dec_sw_ring_emit_wreg,
	.emit_reg_रुको = vcn_v3_0_dec_sw_ring_emit_reg_रुको,
	.emit_reg_ग_लिखो_reg_रुको = amdgpu_ring_emit_reg_ग_लिखो_reg_रुको_helper,
पूर्ण;

अटल पूर्णांक vcn_v3_0_limit_sched(काष्ठा amdgpu_cs_parser *p)
अणु
	काष्ठा drm_gpu_scheduler **scheds;

	/* The create msg must be in the first IB submitted */
	अगर (atomic_पढ़ो(&p->entity->fence_seq))
		वापस -EINVAL;

	scheds = p->adev->gpu_sched[AMDGPU_HW_IP_VCN_DEC]
		[AMDGPU_RING_PRIO_DEFAULT].sched;
	drm_sched_entity_modअगरy_sched(p->entity, scheds, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v3_0_dec_msg(काष्ठा amdgpu_cs_parser *p, uपूर्णांक64_t addr)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	काष्ठा amdgpu_bo_va_mapping *map;
	uपूर्णांक32_t *msg, num_buffers;
	काष्ठा amdgpu_bo *bo;
	uपूर्णांक64_t start, end;
	अचिन्हित पूर्णांक i;
	व्योम * ptr;
	पूर्णांक r;

	addr &= AMDGPU_GMC_HOLE_MASK;
	r = amdgpu_cs_find_mapping(p, addr, &bo, &map);
	अगर (r) अणु
		DRM_ERROR("Can't find BO for addr 0x%08Lx\n", addr);
		वापस r;
	पूर्ण

	start = map->start * AMDGPU_GPU_PAGE_SIZE;
	end = (map->last + 1) * AMDGPU_GPU_PAGE_SIZE;
	अगर (addr & 0x7) अणु
		DRM_ERROR("VCN messages must be 8 byte aligned!\n");
		वापस -EINVAL;
	पूर्ण

	bo->flags |= AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED;
	amdgpu_bo_placement_from_करोमुख्य(bo, bo->allowed_करोमुख्यs);
	r = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
	अगर (r) अणु
		DRM_ERROR("Failed validating the VCN message BO (%d)!\n", r);
		वापस r;
	पूर्ण

	r = amdgpu_bo_kmap(bo, &ptr);
	अगर (r) अणु
		DRM_ERROR("Failed mapping the VCN message (%d)!\n", r);
		वापस r;
	पूर्ण

	msg = ptr + addr - start;

	/* Check length */
	अगर (msg[1] > end - addr) अणु
		r = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (msg[3] != RDECODE_MSG_CREATE)
		जाओ out;

	num_buffers = msg[2];
	क्रम (i = 0, msg = &msg[6]; i < num_buffers; ++i, msg += 4) अणु
		uपूर्णांक32_t offset, size, *create;

		अगर (msg[0] != RDECODE_MESSAGE_CREATE)
			जारी;

		offset = msg[1];
		size = msg[2];

		अगर (offset + size > end) अणु
			r = -EINVAL;
			जाओ out;
		पूर्ण

		create = ptr + addr + offset - start;

		/* H246, HEVC and VP9 can run on any instance */
		अगर (create[0] == 0x7 || create[0] == 0x10 || create[0] == 0x11)
			जारी;

		r = vcn_v3_0_limit_sched(p);
		अगर (r)
			जाओ out;
	पूर्ण

out:
	amdgpu_bo_kunmap(bo);
	वापस r;
पूर्ण

अटल पूर्णांक vcn_v3_0_ring_patch_cs_in_place(काष्ठा amdgpu_cs_parser *p,
					   uपूर्णांक32_t ib_idx)
अणु
	काष्ठा amdgpu_ring *ring = to_amdgpu_ring(p->entity->rq->sched);
	काष्ठा amdgpu_ib *ib = &p->job->ibs[ib_idx];
	uपूर्णांक32_t msg_lo = 0, msg_hi = 0;
	अचिन्हित i;
	पूर्णांक r;

	/* The first instance can decode anything */
	अगर (!ring->me)
		वापस 0;

	क्रम (i = 0; i < ib->length_dw; i += 2) अणु
		uपूर्णांक32_t reg = amdgpu_get_ib_value(p, ib_idx, i);
		uपूर्णांक32_t val = amdgpu_get_ib_value(p, ib_idx, i + 1);

		अगर (reg == PACKET0(p->adev->vcn.पूर्णांकernal.data0, 0)) अणु
			msg_lo = val;
		पूर्ण अन्यथा अगर (reg == PACKET0(p->adev->vcn.पूर्णांकernal.data1, 0)) अणु
			msg_hi = val;
		पूर्ण अन्यथा अगर (reg == PACKET0(p->adev->vcn.पूर्णांकernal.cmd, 0) &&
			   val == 0) अणु
			r = vcn_v3_0_dec_msg(p, ((u64)msg_hi) << 32 | msg_lo);
			अगर (r)
				वापस r;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amdgpu_ring_funcs vcn_v3_0_dec_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_VCN_DEC,
	.align_mask = 0xf,
	.vmhub = AMDGPU_MMHUB_0,
	.get_rptr = vcn_v3_0_dec_ring_get_rptr,
	.get_wptr = vcn_v3_0_dec_ring_get_wptr,
	.set_wptr = vcn_v3_0_dec_ring_set_wptr,
	.patch_cs_in_place = vcn_v3_0_ring_patch_cs_in_place,
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
 * vcn_v3_0_enc_ring_get_rptr - get enc पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware enc पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t vcn_v3_0_enc_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring == &adev->vcn.inst[ring->me].ring_enc[0])
		वापस RREG32_SOC15(VCN, ring->me, mmUVD_RB_RPTR);
	अन्यथा
		वापस RREG32_SOC15(VCN, ring->me, mmUVD_RB_RPTR2);
पूर्ण

/**
 * vcn_v3_0_enc_ring_get_wptr - get enc ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware enc ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t vcn_v3_0_enc_ring_get_wptr(काष्ठा amdgpu_ring *ring)
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
 * vcn_v3_0_enc_ring_set_wptr - set enc ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the enc ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम vcn_v3_0_enc_ring_set_wptr(काष्ठा amdgpu_ring *ring)
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

अटल स्थिर काष्ठा amdgpu_ring_funcs vcn_v3_0_enc_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_VCN_ENC,
	.align_mask = 0x3f,
	.nop = VCN_ENC_CMD_NO_OP,
	.vmhub = AMDGPU_MMHUB_0,
	.get_rptr = vcn_v3_0_enc_ring_get_rptr,
	.get_wptr = vcn_v3_0_enc_ring_get_wptr,
	.set_wptr = vcn_v3_0_enc_ring_set_wptr,
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

अटल व्योम vcn_v3_0_set_dec_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;

		अगर (!DEC_SW_RING_ENABLED)
			adev->vcn.inst[i].ring_dec.funcs = &vcn_v3_0_dec_ring_vm_funcs;
		अन्यथा
			adev->vcn.inst[i].ring_dec.funcs = &vcn_v3_0_dec_sw_ring_vm_funcs;
		adev->vcn.inst[i].ring_dec.me = i;
		DRM_INFO("VCN(%d) decode%s is enabled in VM mode\n", i,
			  DEC_SW_RING_ENABLED?"(Software Ring)":"");
	पूर्ण
पूर्ण

अटल व्योम vcn_v3_0_set_enc_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;

		क्रम (j = 0; j < adev->vcn.num_enc_rings; ++j) अणु
			adev->vcn.inst[i].ring_enc[j].funcs = &vcn_v3_0_enc_ring_vm_funcs;
			adev->vcn.inst[i].ring_enc[j].me = i;
		पूर्ण
		DRM_INFO("VCN(%d) encode is enabled in VM mode\n", i);
	पूर्ण
पूर्ण

अटल bool vcn_v3_0_is_idle(व्योम *handle)
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

अटल पूर्णांक vcn_v3_0_रुको_क्रम_idle(व्योम *handle)
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

अटल पूर्णांक vcn_v3_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	bool enable = (state == AMD_CG_STATE_GATE) ? true : false;
	पूर्णांक i;

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;

		अगर (enable) अणु
			अगर (RREG32_SOC15(VCN, i, mmUVD_STATUS) != UVD_STATUS__IDLE)
				वापस -EBUSY;
			vcn_v3_0_enable_घड़ी_gating(adev, i);
		पूर्ण अन्यथा अणु
			vcn_v3_0_disable_घड़ी_gating(adev, i);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v3_0_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक ret;

	/* क्रम SRIOV, guest should not control VCN Power-gating
	 * MMSCH FW should control Power-gating and घड़ी-gating
	 * guest should aव्योम touching CGC and PG
	 */
	अगर (amdgpu_sriov_vf(adev)) अणु
		adev->vcn.cur_state = AMD_PG_STATE_UNGATE;
		वापस 0;
	पूर्ण

	अगर(state == adev->vcn.cur_state)
		वापस 0;

	अगर (state == AMD_PG_STATE_GATE)
		ret = vcn_v3_0_stop(adev);
	अन्यथा
		ret = vcn_v3_0_start(adev);

	अगर(!ret)
		adev->vcn.cur_state = state;

	वापस ret;
पूर्ण

अटल पूर्णांक vcn_v3_0_set_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vcn_v3_0_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
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

अटल स्थिर काष्ठा amdgpu_irq_src_funcs vcn_v3_0_irq_funcs = अणु
	.set = vcn_v3_0_set_पूर्णांकerrupt_state,
	.process = vcn_v3_0_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम vcn_v3_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->vcn.num_vcn_inst; ++i) अणु
		अगर (adev->vcn.harvest_config & (1 << i))
			जारी;

		adev->vcn.inst[i].irq.num_types = adev->vcn.num_enc_rings + 1;
		adev->vcn.inst[i].irq.funcs = &vcn_v3_0_irq_funcs;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs vcn_v3_0_ip_funcs = अणु
	.name = "vcn_v3_0",
	.early_init = vcn_v3_0_early_init,
	.late_init = शून्य,
	.sw_init = vcn_v3_0_sw_init,
	.sw_fini = vcn_v3_0_sw_fini,
	.hw_init = vcn_v3_0_hw_init,
	.hw_fini = vcn_v3_0_hw_fini,
	.suspend = vcn_v3_0_suspend,
	.resume = vcn_v3_0_resume,
	.is_idle = vcn_v3_0_is_idle,
	.रुको_क्रम_idle = vcn_v3_0_रुको_क्रम_idle,
	.check_soft_reset = शून्य,
	.pre_soft_reset = शून्य,
	.soft_reset = शून्य,
	.post_soft_reset = शून्य,
	.set_घड़ीgating_state = vcn_v3_0_set_घड़ीgating_state,
	.set_घातergating_state = vcn_v3_0_set_घातergating_state,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version vcn_v3_0_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_VCN,
	.major = 3,
	.minor = 0,
	.rev = 0,
	.funcs = &vcn_v3_0_ip_funcs,
पूर्ण;
