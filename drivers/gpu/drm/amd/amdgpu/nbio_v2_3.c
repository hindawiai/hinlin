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
#समावेश "amdgpu_atombios.h"
#समावेश "nbio_v2_3.h"

#समावेश "nbio/nbio_2_3_default.h"
#समावेश "nbio/nbio_2_3_offset.h"
#समावेश "nbio/nbio_2_3_sh_mask.h"
#समावेश <uapi/linux/kfd_ioctl.h>
#समावेश <linux/pci.h>

#घोषणा smnPCIE_CONFIG_CNTL	0x11180044
#घोषणा smnCPM_CONTROL		0x11180460
#घोषणा smnPCIE_CNTL2		0x11180070
#घोषणा smnPCIE_LC_CNTL		0x11140280
#घोषणा smnPCIE_LC_CNTL3	0x111402d4
#घोषणा smnPCIE_LC_CNTL6	0x111402ec
#घोषणा smnPCIE_LC_CNTL7	0x111402f0
#घोषणा smnBIF_CFG_DEV0_EPF0_DEVICE_CNTL2	0x1014008c
#घोषणा smnRCC_EP_DEV0_0_EP_PCIE_TX_LTR_CNTL	0x10123538
#घोषणा smnBIF_CFG_DEV0_EPF0_PCIE_LTR_CAP	0x10140324
#घोषणा smnPSWUSP0_PCIE_LC_CNTL2		0x111402c4
#घोषणा smnNBIF_MGCG_CTRL_LCLK			0x1013a21c

#घोषणा mmBIF_SDMA2_DOORBELL_RANGE		0x01d6
#घोषणा mmBIF_SDMA2_DOORBELL_RANGE_BASE_IDX	2
#घोषणा mmBIF_SDMA3_DOORBELL_RANGE		0x01d7
#घोषणा mmBIF_SDMA3_DOORBELL_RANGE_BASE_IDX	2

#घोषणा mmBIF_MMSCH1_DOORBELL_RANGE		0x01d8
#घोषणा mmBIF_MMSCH1_DOORBELL_RANGE_BASE_IDX	2

अटल व्योम nbio_v2_3_remap_hdp_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	WREG32_SOC15(NBIO, 0, mmREMAP_HDP_MEM_FLUSH_CNTL,
		adev->rmmio_remap.reg_offset + KFD_MMIO_REMAP_HDP_MEM_FLUSH_CNTL);
	WREG32_SOC15(NBIO, 0, mmREMAP_HDP_REG_FLUSH_CNTL,
		adev->rmmio_remap.reg_offset + KFD_MMIO_REMAP_HDP_REG_FLUSH_CNTL);
पूर्ण

अटल u32 nbio_v2_3_get_rev_id(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp;

	/*
	 * guest vm माला_लो 0xffffffff when पढ़ोing RCC_DEV0_EPF0_STRAP0,
	 * thereक्रमe we क्रमce rev_id to 0 (which is the शेष value)
	 */
	अगर (amdgpu_sriov_vf(adev)) अणु
		वापस 0;
	पूर्ण

	पंचांगp = RREG32_SOC15(NBIO, 0, mmRCC_DEV0_EPF0_STRAP0);
	पंचांगp &= RCC_DEV0_EPF0_STRAP0__STRAP_ATI_REV_ID_DEV0_F0_MASK;
	पंचांगp >>= RCC_DEV0_EPF0_STRAP0__STRAP_ATI_REV_ID_DEV0_F0__SHIFT;

	वापस पंचांगp;
पूर्ण

अटल व्योम nbio_v2_3_mc_access_enable(काष्ठा amdgpu_device *adev, bool enable)
अणु
	अगर (enable)
		WREG32_SOC15(NBIO, 0, mmBIF_FB_EN,
			     BIF_FB_EN__FB_READ_EN_MASK |
			     BIF_FB_EN__FB_WRITE_EN_MASK);
	अन्यथा
		WREG32_SOC15(NBIO, 0, mmBIF_FB_EN, 0);
पूर्ण

अटल u32 nbio_v2_3_get_memsize(काष्ठा amdgpu_device *adev)
अणु
	वापस RREG32_SOC15(NBIO, 0, mmRCC_DEV0_EPF0_RCC_CONFIG_MEMSIZE);
पूर्ण

अटल व्योम nbio_v2_3_sdma_करोorbell_range(काष्ठा amdgpu_device *adev, पूर्णांक instance,
					  bool use_करोorbell, पूर्णांक करोorbell_index,
					  पूर्णांक करोorbell_size)
अणु
	u32 reg = instance == 0 ? SOC15_REG_OFFSET(NBIO, 0, mmBIF_SDMA0_DOORBELL_RANGE) :
			instance == 1 ? SOC15_REG_OFFSET(NBIO, 0, mmBIF_SDMA1_DOORBELL_RANGE) :
			instance == 2 ? SOC15_REG_OFFSET(NBIO, 0, mmBIF_SDMA2_DOORBELL_RANGE) :
			SOC15_REG_OFFSET(NBIO, 0, mmBIF_SDMA3_DOORBELL_RANGE);

	u32 करोorbell_range = RREG32(reg);

	अगर (use_करोorbell) अणु
		करोorbell_range = REG_SET_FIELD(करोorbell_range,
					       BIF_SDMA0_DOORBELL_RANGE, OFFSET,
					       करोorbell_index);
		करोorbell_range = REG_SET_FIELD(करोorbell_range,
					       BIF_SDMA0_DOORBELL_RANGE, SIZE,
					       करोorbell_size);
	पूर्ण अन्यथा
		करोorbell_range = REG_SET_FIELD(करोorbell_range,
					       BIF_SDMA0_DOORBELL_RANGE, SIZE,
					       0);

	WREG32(reg, करोorbell_range);
पूर्ण

अटल व्योम nbio_v2_3_vcn_करोorbell_range(काष्ठा amdgpu_device *adev, bool use_करोorbell,
					 पूर्णांक करोorbell_index, पूर्णांक instance)
अणु
	u32 reg = instance ? SOC15_REG_OFFSET(NBIO, 0, mmBIF_MMSCH1_DOORBELL_RANGE) :
		SOC15_REG_OFFSET(NBIO, 0, mmBIF_MMSCH0_DOORBELL_RANGE);

	u32 करोorbell_range = RREG32(reg);

	अगर (use_करोorbell) अणु
		करोorbell_range = REG_SET_FIELD(करोorbell_range,
					       BIF_MMSCH0_DOORBELL_RANGE, OFFSET,
					       करोorbell_index);
		करोorbell_range = REG_SET_FIELD(करोorbell_range,
					       BIF_MMSCH0_DOORBELL_RANGE, SIZE, 8);
	पूर्ण अन्यथा
		करोorbell_range = REG_SET_FIELD(करोorbell_range,
					       BIF_MMSCH0_DOORBELL_RANGE, SIZE, 0);

	WREG32(reg, करोorbell_range);
पूर्ण

अटल व्योम nbio_v2_3_enable_करोorbell_aperture(काष्ठा amdgpu_device *adev,
					       bool enable)
अणु
	WREG32_FIELD15(NBIO, 0, RCC_DEV0_EPF0_RCC_DOORBELL_APER_EN, BIF_DOORBELL_APER_EN,
		       enable ? 1 : 0);
पूर्ण

अटल व्योम nbio_v2_3_enable_करोorbell_selfring_aperture(काष्ठा amdgpu_device *adev,
							bool enable)
अणु
	u32 पंचांगp = 0;

	अगर (enable) अणु
		पंचांगp = REG_SET_FIELD(पंचांगp, BIF_BX_PF_DOORBELL_SELFRING_GPA_APER_CNTL,
				    DOORBELL_SELFRING_GPA_APER_EN, 1) |
		      REG_SET_FIELD(पंचांगp, BIF_BX_PF_DOORBELL_SELFRING_GPA_APER_CNTL,
				    DOORBELL_SELFRING_GPA_APER_MODE, 1) |
		      REG_SET_FIELD(पंचांगp, BIF_BX_PF_DOORBELL_SELFRING_GPA_APER_CNTL,
				    DOORBELL_SELFRING_GPA_APER_SIZE, 0);

		WREG32_SOC15(NBIO, 0, mmBIF_BX_PF_DOORBELL_SELFRING_GPA_APER_BASE_LOW,
			     lower_32_bits(adev->करोorbell.base));
		WREG32_SOC15(NBIO, 0, mmBIF_BX_PF_DOORBELL_SELFRING_GPA_APER_BASE_HIGH,
			     upper_32_bits(adev->करोorbell.base));
	पूर्ण

	WREG32_SOC15(NBIO, 0, mmBIF_BX_PF_DOORBELL_SELFRING_GPA_APER_CNTL,
		     पंचांगp);
पूर्ण


अटल व्योम nbio_v2_3_ih_करोorbell_range(काष्ठा amdgpu_device *adev,
					bool use_करोorbell, पूर्णांक करोorbell_index)
अणु
	u32 ih_करोorbell_range = RREG32_SOC15(NBIO, 0, mmBIF_IH_DOORBELL_RANGE);

	अगर (use_करोorbell) अणु
		ih_करोorbell_range = REG_SET_FIELD(ih_करोorbell_range,
						  BIF_IH_DOORBELL_RANGE, OFFSET,
						  करोorbell_index);
		ih_करोorbell_range = REG_SET_FIELD(ih_करोorbell_range,
						  BIF_IH_DOORBELL_RANGE, SIZE,
						  2);
	पूर्ण अन्यथा
		ih_करोorbell_range = REG_SET_FIELD(ih_करोorbell_range,
						  BIF_IH_DOORBELL_RANGE, SIZE,
						  0);

	WREG32_SOC15(NBIO, 0, mmBIF_IH_DOORBELL_RANGE, ih_करोorbell_range);
पूर्ण

अटल व्योम nbio_v2_3_ih_control(काष्ठा amdgpu_device *adev)
अणु
	u32 पूर्णांकerrupt_cntl;

	/* setup पूर्णांकerrupt control */
	WREG32_SOC15(NBIO, 0, mmINTERRUPT_CNTL2, adev->dummy_page_addr >> 8);

	पूर्णांकerrupt_cntl = RREG32_SOC15(NBIO, 0, mmINTERRUPT_CNTL);
	/*
	 * INTERRUPT_CNTL__IH_DUMMY_RD_OVERRIDE_MASK=0 - dummy पढ़ो disabled with msi, enabled without msi
	 * INTERRUPT_CNTL__IH_DUMMY_RD_OVERRIDE_MASK=1 - dummy पढ़ो controlled by IH_DUMMY_RD_EN
	 */
	पूर्णांकerrupt_cntl = REG_SET_FIELD(पूर्णांकerrupt_cntl, INTERRUPT_CNTL,
				       IH_DUMMY_RD_OVERRIDE, 0);

	/* INTERRUPT_CNTL__IH_REQ_NONSNOOP_EN_MASK=1 अगर ring is in non-cacheable memory, e.g., vram */
	पूर्णांकerrupt_cntl = REG_SET_FIELD(पूर्णांकerrupt_cntl, INTERRUPT_CNTL,
				       IH_REQ_NONSNOOP_EN, 0);

	WREG32_SOC15(NBIO, 0, mmINTERRUPT_CNTL, पूर्णांकerrupt_cntl);
पूर्ण

अटल व्योम nbio_v2_3_update_medium_grain_घड़ी_gating(काष्ठा amdgpu_device *adev,
						       bool enable)
अणु
	uपूर्णांक32_t def, data;

	def = data = RREG32_PCIE(smnCPM_CONTROL);
	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_BIF_MGCG)) अणु
		data |= (CPM_CONTROL__LCLK_DYN_GATE_ENABLE_MASK |
			 CPM_CONTROL__TXCLK_DYN_GATE_ENABLE_MASK |
			 CPM_CONTROL__TXCLK_LCNT_GATE_ENABLE_MASK |
			 CPM_CONTROL__TXCLK_REGS_GATE_ENABLE_MASK |
			 CPM_CONTROL__TXCLK_PRBS_GATE_ENABLE_MASK |
			 CPM_CONTROL__REFCLK_REGS_GATE_ENABLE_MASK);
	पूर्ण अन्यथा अणु
		data &= ~(CPM_CONTROL__LCLK_DYN_GATE_ENABLE_MASK |
			  CPM_CONTROL__TXCLK_DYN_GATE_ENABLE_MASK |
			  CPM_CONTROL__TXCLK_LCNT_GATE_ENABLE_MASK |
			  CPM_CONTROL__TXCLK_REGS_GATE_ENABLE_MASK |
			  CPM_CONTROL__TXCLK_PRBS_GATE_ENABLE_MASK |
			  CPM_CONTROL__REFCLK_REGS_GATE_ENABLE_MASK);
	पूर्ण

	अगर (def != data)
		WREG32_PCIE(smnCPM_CONTROL, data);
पूर्ण

अटल व्योम nbio_v2_3_update_medium_grain_light_sleep(काष्ठा amdgpu_device *adev,
						      bool enable)
अणु
	uपूर्णांक32_t def, data;

	def = data = RREG32_PCIE(smnPCIE_CNTL2);
	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_BIF_LS)) अणु
		data |= (PCIE_CNTL2__SLV_MEM_LS_EN_MASK |
			 PCIE_CNTL2__MST_MEM_LS_EN_MASK |
			 PCIE_CNTL2__REPLAY_MEM_LS_EN_MASK);
	पूर्ण अन्यथा अणु
		data &= ~(PCIE_CNTL2__SLV_MEM_LS_EN_MASK |
			  PCIE_CNTL2__MST_MEM_LS_EN_MASK |
			  PCIE_CNTL2__REPLAY_MEM_LS_EN_MASK);
	पूर्ण

	अगर (def != data)
		WREG32_PCIE(smnPCIE_CNTL2, data);
पूर्ण

अटल व्योम nbio_v2_3_get_घड़ीgating_state(काष्ठा amdgpu_device *adev,
					    u32 *flags)
अणु
	पूर्णांक data;

	/* AMD_CG_SUPPORT_BIF_MGCG */
	data = RREG32_PCIE(smnCPM_CONTROL);
	अगर (data & CPM_CONTROL__LCLK_DYN_GATE_ENABLE_MASK)
		*flags |= AMD_CG_SUPPORT_BIF_MGCG;

	/* AMD_CG_SUPPORT_BIF_LS */
	data = RREG32_PCIE(smnPCIE_CNTL2);
	अगर (data & PCIE_CNTL2__SLV_MEM_LS_EN_MASK)
		*flags |= AMD_CG_SUPPORT_BIF_LS;
पूर्ण

अटल u32 nbio_v2_3_get_hdp_flush_req_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, mmBIF_BX_PF_GPU_HDP_FLUSH_REQ);
पूर्ण

अटल u32 nbio_v2_3_get_hdp_flush_करोne_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, mmBIF_BX_PF_GPU_HDP_FLUSH_DONE);
पूर्ण

अटल u32 nbio_v2_3_get_pcie_index_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, mmPCIE_INDEX2);
पूर्ण

अटल u32 nbio_v2_3_get_pcie_data_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, mmPCIE_DATA2);
पूर्ण

स्थिर काष्ठा nbio_hdp_flush_reg nbio_v2_3_hdp_flush_reg = अणु
	.ref_and_mask_cp0 = BIF_BX_PF_GPU_HDP_FLUSH_DONE__CP0_MASK,
	.ref_and_mask_cp1 = BIF_BX_PF_GPU_HDP_FLUSH_DONE__CP1_MASK,
	.ref_and_mask_cp2 = BIF_BX_PF_GPU_HDP_FLUSH_DONE__CP2_MASK,
	.ref_and_mask_cp3 = BIF_BX_PF_GPU_HDP_FLUSH_DONE__CP3_MASK,
	.ref_and_mask_cp4 = BIF_BX_PF_GPU_HDP_FLUSH_DONE__CP4_MASK,
	.ref_and_mask_cp5 = BIF_BX_PF_GPU_HDP_FLUSH_DONE__CP5_MASK,
	.ref_and_mask_cp6 = BIF_BX_PF_GPU_HDP_FLUSH_DONE__CP6_MASK,
	.ref_and_mask_cp7 = BIF_BX_PF_GPU_HDP_FLUSH_DONE__CP7_MASK,
	.ref_and_mask_cp8 = BIF_BX_PF_GPU_HDP_FLUSH_DONE__CP8_MASK,
	.ref_and_mask_cp9 = BIF_BX_PF_GPU_HDP_FLUSH_DONE__CP9_MASK,
	.ref_and_mask_sdma0 = BIF_BX_PF_GPU_HDP_FLUSH_DONE__SDMA0_MASK,
	.ref_and_mask_sdma1 = BIF_BX_PF_GPU_HDP_FLUSH_DONE__SDMA1_MASK,
पूर्ण;

अटल व्योम nbio_v2_3_init_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t def, data;

	def = data = RREG32_PCIE(smnPCIE_CONFIG_CNTL);
	data = REG_SET_FIELD(data, PCIE_CONFIG_CNTL, CI_SWUS_MAX_READ_REQUEST_SIZE_MODE, 1);
	data = REG_SET_FIELD(data, PCIE_CONFIG_CNTL, CI_SWUS_MAX_READ_REQUEST_SIZE_PRIV, 1);

	अगर (def != data)
		WREG32_PCIE(smnPCIE_CONFIG_CNTL, data);
पूर्ण

#घोषणा NAVI10_PCIE__LC_L0S_INACTIVITY_DEFAULT		0x00000000 // off by शेष, no gains over L1
#घोषणा NAVI10_PCIE__LC_L1_INACTIVITY_DEFAULT		0x00000009 // 1=1us, 9=1ms
#घोषणा NAVI10_PCIE__LC_L1_INACTIVITY_TBT_DEFAULT	0x0000000E // 4ms

अटल व्योम nbio_v2_3_enable_aspm(काष्ठा amdgpu_device *adev,
				  bool enable)
अणु
	uपूर्णांक32_t def, data;

	def = data = RREG32_PCIE(smnPCIE_LC_CNTL);

	अगर (enable) अणु
		/* Disable ASPM L0s/L1 first */
		data &= ~(PCIE_LC_CNTL__LC_L0S_INACTIVITY_MASK | PCIE_LC_CNTL__LC_L1_INACTIVITY_MASK);

		data |= NAVI10_PCIE__LC_L0S_INACTIVITY_DEFAULT << PCIE_LC_CNTL__LC_L0S_INACTIVITY__SHIFT;

		अगर (pci_is_thunderbolt_attached(adev->pdev))
			data |= NAVI10_PCIE__LC_L1_INACTIVITY_TBT_DEFAULT  << PCIE_LC_CNTL__LC_L1_INACTIVITY__SHIFT;
		अन्यथा
			data |= NAVI10_PCIE__LC_L1_INACTIVITY_DEFAULT << PCIE_LC_CNTL__LC_L1_INACTIVITY__SHIFT;

		data &= ~PCIE_LC_CNTL__LC_PMI_TO_L1_DIS_MASK;
	पूर्ण अन्यथा अणु
		/* Disbale ASPM L1 */
		data &= ~PCIE_LC_CNTL__LC_L1_INACTIVITY_MASK;
		/* Disable ASPM TxL0s */
		data &= ~PCIE_LC_CNTL__LC_L0S_INACTIVITY_MASK;
		/* Disable ACPI L1 */
		data |= PCIE_LC_CNTL__LC_PMI_TO_L1_DIS_MASK;
	पूर्ण

	अगर (def != data)
		WREG32_PCIE(smnPCIE_LC_CNTL, data);
पूर्ण

अटल व्योम nbio_v2_3_program_ltr(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t def, data;

	WREG32_PCIE(smnRCC_EP_DEV0_0_EP_PCIE_TX_LTR_CNTL, 0x75EB);

	def = data = RREG32_SOC15(NBIO, 0, mmRCC_BIF_STRAP2);
	data &= ~RCC_BIF_STRAP2__STRAP_LTR_IN_ASPML1_DIS_MASK;
	अगर (def != data)
		WREG32_SOC15(NBIO, 0, mmRCC_BIF_STRAP2, data);

	def = data = RREG32_PCIE(smnRCC_EP_DEV0_0_EP_PCIE_TX_LTR_CNTL);
	data &= ~EP_PCIE_TX_LTR_CNTL__LTR_PRIV_MSG_DIS_IN_PM_NON_D0_MASK;
	अगर (def != data)
		WREG32_PCIE(smnRCC_EP_DEV0_0_EP_PCIE_TX_LTR_CNTL, data);

	def = data = RREG32_PCIE(smnBIF_CFG_DEV0_EPF0_DEVICE_CNTL2);
	data |= BIF_CFG_DEV0_EPF0_DEVICE_CNTL2__LTR_EN_MASK;
	अगर (def != data)
		WREG32_PCIE(smnBIF_CFG_DEV0_EPF0_DEVICE_CNTL2, data);
पूर्ण

अटल व्योम nbio_v2_3_program_aspm(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t def, data;

	def = data = RREG32_PCIE(smnPCIE_LC_CNTL);
	data &= ~PCIE_LC_CNTL__LC_L1_INACTIVITY_MASK;
	data &= ~PCIE_LC_CNTL__LC_L0S_INACTIVITY_MASK;
	data |= PCIE_LC_CNTL__LC_PMI_TO_L1_DIS_MASK;
	अगर (def != data)
		WREG32_PCIE(smnPCIE_LC_CNTL, data);

	def = data = RREG32_PCIE(smnPCIE_LC_CNTL7);
	data |= PCIE_LC_CNTL7__LC_NBIF_ASPM_INPUT_EN_MASK;
	अगर (def != data)
		WREG32_PCIE(smnPCIE_LC_CNTL7, data);

	def = data = RREG32_PCIE(smnNBIF_MGCG_CTRL_LCLK);
	data |= NBIF_MGCG_CTRL_LCLK__NBIF_MGCG_REG_DIS_LCLK_MASK;
	अगर (def != data)
		WREG32_PCIE(smnNBIF_MGCG_CTRL_LCLK, data);

	def = data = RREG32_PCIE(smnPCIE_LC_CNTL3);
	data |= PCIE_LC_CNTL3__LC_DSC_DONT_ENTER_L23_AFTER_PME_ACK_MASK;
	अगर (def != data)
		WREG32_PCIE(smnPCIE_LC_CNTL3, data);

	def = data = RREG32_SOC15(NBIO, 0, mmRCC_BIF_STRAP3);
	data &= ~RCC_BIF_STRAP3__STRAP_VLINK_ASPM_IDLE_TIMER_MASK;
	data &= ~RCC_BIF_STRAP3__STRAP_VLINK_PM_L1_ENTRY_TIMER_MASK;
	अगर (def != data)
		WREG32_SOC15(NBIO, 0, mmRCC_BIF_STRAP3, data);

	def = data = RREG32_SOC15(NBIO, 0, mmRCC_BIF_STRAP5);
	data &= ~RCC_BIF_STRAP5__STRAP_VLINK_LDN_ENTRY_TIMER_MASK;
	अगर (def != data)
		WREG32_SOC15(NBIO, 0, mmRCC_BIF_STRAP5, data);

	def = data = RREG32_PCIE(smnBIF_CFG_DEV0_EPF0_DEVICE_CNTL2);
	data &= ~BIF_CFG_DEV0_EPF0_DEVICE_CNTL2__LTR_EN_MASK;
	अगर (def != data)
		WREG32_PCIE(smnBIF_CFG_DEV0_EPF0_DEVICE_CNTL2, data);

	WREG32_PCIE(smnBIF_CFG_DEV0_EPF0_PCIE_LTR_CAP, 0x10011001);

	def = data = RREG32_PCIE(smnPSWUSP0_PCIE_LC_CNTL2);
	data |= PSWUSP0_PCIE_LC_CNTL2__LC_ALLOW_PDWN_IN_L1_MASK |
		PSWUSP0_PCIE_LC_CNTL2__LC_ALLOW_PDWN_IN_L23_MASK;
	data &= ~PSWUSP0_PCIE_LC_CNTL2__LC_RCV_L0_TO_RCV_L0S_DIS_MASK;
	अगर (def != data)
		WREG32_PCIE(smnPSWUSP0_PCIE_LC_CNTL2, data);

	def = data = RREG32_PCIE(smnPCIE_LC_CNTL6);
	data |= PCIE_LC_CNTL6__LC_L1_POWERDOWN_MASK |
		PCIE_LC_CNTL6__LC_RX_L0S_STANDBY_EN_MASK;
	अगर (def != data)
		WREG32_PCIE(smnPCIE_LC_CNTL6, data);

	nbio_v2_3_program_ltr(adev);

	def = data = RREG32_SOC15(NBIO, 0, mmRCC_BIF_STRAP3);
	data |= 0x5DE0 << RCC_BIF_STRAP3__STRAP_VLINK_ASPM_IDLE_TIMER__SHIFT;
	data |= 0x0010 << RCC_BIF_STRAP3__STRAP_VLINK_PM_L1_ENTRY_TIMER__SHIFT;
	अगर (def != data)
		WREG32_SOC15(NBIO, 0, mmRCC_BIF_STRAP3, data);

	def = data = RREG32_SOC15(NBIO, 0, mmRCC_BIF_STRAP5);
	data |= 0x0010 << RCC_BIF_STRAP5__STRAP_VLINK_LDN_ENTRY_TIMER__SHIFT;
	अगर (def != data)
		WREG32_SOC15(NBIO, 0, mmRCC_BIF_STRAP5, data);

	def = data = RREG32_PCIE(smnPCIE_LC_CNTL);
	data &= ~PCIE_LC_CNTL__LC_L0S_INACTIVITY_MASK;
	data |= 0x9 << PCIE_LC_CNTL__LC_L1_INACTIVITY__SHIFT;
	data |= 0x1 << PCIE_LC_CNTL__LC_PMI_TO_L1_DIS__SHIFT;
	अगर (def != data)
		WREG32_PCIE(smnPCIE_LC_CNTL, data);

	def = data = RREG32_PCIE(smnPCIE_LC_CNTL3);
	data &= ~PCIE_LC_CNTL3__LC_DSC_DONT_ENTER_L23_AFTER_PME_ACK_MASK;
	अगर (def != data)
		WREG32_PCIE(smnPCIE_LC_CNTL3, data);
पूर्ण

स्थिर काष्ठा amdgpu_nbio_funcs nbio_v2_3_funcs = अणु
	.get_hdp_flush_req_offset = nbio_v2_3_get_hdp_flush_req_offset,
	.get_hdp_flush_करोne_offset = nbio_v2_3_get_hdp_flush_करोne_offset,
	.get_pcie_index_offset = nbio_v2_3_get_pcie_index_offset,
	.get_pcie_data_offset = nbio_v2_3_get_pcie_data_offset,
	.get_rev_id = nbio_v2_3_get_rev_id,
	.mc_access_enable = nbio_v2_3_mc_access_enable,
	.get_memsize = nbio_v2_3_get_memsize,
	.sdma_करोorbell_range = nbio_v2_3_sdma_करोorbell_range,
	.vcn_करोorbell_range = nbio_v2_3_vcn_करोorbell_range,
	.enable_करोorbell_aperture = nbio_v2_3_enable_करोorbell_aperture,
	.enable_करोorbell_selfring_aperture = nbio_v2_3_enable_करोorbell_selfring_aperture,
	.ih_करोorbell_range = nbio_v2_3_ih_करोorbell_range,
	.update_medium_grain_घड़ी_gating = nbio_v2_3_update_medium_grain_घड़ी_gating,
	.update_medium_grain_light_sleep = nbio_v2_3_update_medium_grain_light_sleep,
	.get_घड़ीgating_state = nbio_v2_3_get_घड़ीgating_state,
	.ih_control = nbio_v2_3_ih_control,
	.init_रेजिस्टरs = nbio_v2_3_init_रेजिस्टरs,
	.remap_hdp_रेजिस्टरs = nbio_v2_3_remap_hdp_रेजिस्टरs,
	.enable_aspm = nbio_v2_3_enable_aspm,
	.program_aspm =  nbio_v2_3_program_aspm,
पूर्ण;
