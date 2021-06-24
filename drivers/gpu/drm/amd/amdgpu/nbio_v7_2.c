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
 */
#समावेश "amdgpu.h"
#समावेश "amdgpu_atombios.h"
#समावेश "nbio_v7_2.h"

#समावेश "nbio/nbio_7_2_0_offset.h"
#समावेश "nbio/nbio_7_2_0_sh_mask.h"
#समावेश <uapi/linux/kfd_ioctl.h>

अटल व्योम nbio_v7_2_remap_hdp_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	WREG32_SOC15(NBIO, 0, regBIF_BX0_REMAP_HDP_MEM_FLUSH_CNTL,
		adev->rmmio_remap.reg_offset + KFD_MMIO_REMAP_HDP_MEM_FLUSH_CNTL);
	WREG32_SOC15(NBIO, 0, regBIF_BX0_REMAP_HDP_REG_FLUSH_CNTL,
		adev->rmmio_remap.reg_offset + KFD_MMIO_REMAP_HDP_REG_FLUSH_CNTL);
पूर्ण

अटल u32 nbio_v7_2_get_rev_id(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp = RREG32_SOC15(NBIO, 0, regRCC_STRAP0_RCC_DEV0_EPF0_STRAP0);

	पंचांगp &= RCC_STRAP0_RCC_DEV0_EPF0_STRAP0__STRAP_ATI_REV_ID_DEV0_F0_MASK;
	पंचांगp >>= RCC_STRAP0_RCC_DEV0_EPF0_STRAP0__STRAP_ATI_REV_ID_DEV0_F0__SHIFT;

	वापस पंचांगp;
पूर्ण

अटल व्योम nbio_v7_2_mc_access_enable(काष्ठा amdgpu_device *adev, bool enable)
अणु
	अगर (enable)
		WREG32_SOC15(NBIO, 0, regBIF_BX0_BIF_FB_EN,
			     BIF_BX0_BIF_FB_EN__FB_READ_EN_MASK |
			     BIF_BX0_BIF_FB_EN__FB_WRITE_EN_MASK);
	अन्यथा
		WREG32_SOC15(NBIO, 0, regBIF_BX0_BIF_FB_EN, 0);
पूर्ण

अटल u32 nbio_v7_2_get_memsize(काष्ठा amdgpu_device *adev)
अणु
	वापस RREG32_SOC15(NBIO, 0, regRCC_DEV0_EPF0_0_RCC_CONFIG_MEMSIZE);
पूर्ण

अटल व्योम nbio_v7_2_sdma_करोorbell_range(काष्ठा amdgpu_device *adev, पूर्णांक instance,
					  bool use_करोorbell, पूर्णांक करोorbell_index,
					  पूर्णांक करोorbell_size)
अणु
	u32 reg = SOC15_REG_OFFSET(NBIO, 0, regGDC0_BIF_SDMA0_DOORBELL_RANGE);
	u32 करोorbell_range = RREG32_PCIE_PORT(reg);

	अगर (use_करोorbell) अणु
		करोorbell_range = REG_SET_FIELD(करोorbell_range,
					       GDC0_BIF_SDMA0_DOORBELL_RANGE,
					       OFFSET, करोorbell_index);
		करोorbell_range = REG_SET_FIELD(करोorbell_range,
					       GDC0_BIF_SDMA0_DOORBELL_RANGE,
					       SIZE, करोorbell_size);
	पूर्ण अन्यथा अणु
		करोorbell_range = REG_SET_FIELD(करोorbell_range,
					       GDC0_BIF_SDMA0_DOORBELL_RANGE,
					       SIZE, 0);
	पूर्ण

	WREG32_PCIE_PORT(reg, करोorbell_range);
पूर्ण

अटल व्योम nbio_v7_2_vcn_करोorbell_range(काष्ठा amdgpu_device *adev, bool use_करोorbell,
					 पूर्णांक करोorbell_index, पूर्णांक instance)
अणु
	u32 reg = SOC15_REG_OFFSET(NBIO, 0, regGDC0_BIF_VCN0_DOORBELL_RANGE);
	u32 करोorbell_range = RREG32_PCIE_PORT(reg);

	अगर (use_करोorbell) अणु
		करोorbell_range = REG_SET_FIELD(करोorbell_range,
					       GDC0_BIF_VCN0_DOORBELL_RANGE, OFFSET,
					       करोorbell_index);
		करोorbell_range = REG_SET_FIELD(करोorbell_range,
					       GDC0_BIF_VCN0_DOORBELL_RANGE, SIZE, 8);
	पूर्ण अन्यथा अणु
		करोorbell_range = REG_SET_FIELD(करोorbell_range,
					       GDC0_BIF_VCN0_DOORBELL_RANGE, SIZE, 0);
	पूर्ण

	WREG32_PCIE_PORT(reg, करोorbell_range);
पूर्ण

अटल व्योम nbio_v7_2_enable_करोorbell_aperture(काष्ठा amdgpu_device *adev,
					       bool enable)
अणु
	u32 reg;

	reg = RREG32_SOC15(NBIO, 0, regRCC_DEV0_EPF0_0_RCC_DOORBELL_APER_EN);
	reg = REG_SET_FIELD(reg, RCC_DEV0_EPF0_0_RCC_DOORBELL_APER_EN,
			    BIF_DOORBELL_APER_EN, enable ? 1 : 0);

	WREG32_SOC15(NBIO, 0, regRCC_DEV0_EPF0_0_RCC_DOORBELL_APER_EN, reg);
पूर्ण

अटल व्योम nbio_v7_2_enable_करोorbell_selfring_aperture(काष्ठा amdgpu_device *adev,
							bool enable)
अणु
	u32 पंचांगp = 0;

	अगर (enable) अणु
		पंचांगp = REG_SET_FIELD(पंचांगp, BIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_CNTL,
				    DOORBELL_SELFRING_GPA_APER_EN, 1) |
		      REG_SET_FIELD(पंचांगp, BIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_CNTL,
				    DOORBELL_SELFRING_GPA_APER_MODE, 1) |
		      REG_SET_FIELD(पंचांगp, BIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_CNTL,
				    DOORBELL_SELFRING_GPA_APER_SIZE, 0);

		WREG32_SOC15(NBIO, 0,
			     regBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_BASE_LOW,
			     lower_32_bits(adev->करोorbell.base));
		WREG32_SOC15(NBIO, 0,
			     regBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_BASE_HIGH,
			     upper_32_bits(adev->करोorbell.base));
	पूर्ण

	WREG32_SOC15(NBIO, 0, regBIF_BX_PF0_DOORBELL_SELFRING_GPA_APER_CNTL,
		     पंचांगp);
पूर्ण


अटल व्योम nbio_v7_2_ih_करोorbell_range(काष्ठा amdgpu_device *adev,
					bool use_करोorbell, पूर्णांक करोorbell_index)
अणु
	u32 ih_करोorbell_range = RREG32_PCIE_PORT(SOC15_REG_OFFSET(NBIO, 0, regGDC0_BIF_IH_DOORBELL_RANGE));

	अगर (use_करोorbell) अणु
		ih_करोorbell_range = REG_SET_FIELD(ih_करोorbell_range,
						  GDC0_BIF_IH_DOORBELL_RANGE, OFFSET,
						  करोorbell_index);
		ih_करोorbell_range = REG_SET_FIELD(ih_करोorbell_range,
						  GDC0_BIF_IH_DOORBELL_RANGE, SIZE,
						  2);
	पूर्ण अन्यथा अणु
		ih_करोorbell_range = REG_SET_FIELD(ih_करोorbell_range,
						  GDC0_BIF_IH_DOORBELL_RANGE, SIZE,
						  0);
	पूर्ण

	WREG32_PCIE_PORT(SOC15_REG_OFFSET(NBIO, 0, regGDC0_BIF_IH_DOORBELL_RANGE),
			 ih_करोorbell_range);
पूर्ण

अटल व्योम nbio_v7_2_ih_control(काष्ठा amdgpu_device *adev)
अणु
	u32 पूर्णांकerrupt_cntl;

	/* setup पूर्णांकerrupt control */
	WREG32_SOC15(NBIO, 0, regBIF_BX0_INTERRUPT_CNTL2,
		     adev->dummy_page_addr >> 8);

	पूर्णांकerrupt_cntl = RREG32_SOC15(NBIO, 0, regBIF_BX0_INTERRUPT_CNTL);
	/*
	 * INTERRUPT_CNTL__IH_DUMMY_RD_OVERRIDE_MASK=0 - dummy पढ़ो disabled with msi, enabled without msi
	 * INTERRUPT_CNTL__IH_DUMMY_RD_OVERRIDE_MASK=1 - dummy पढ़ो controlled by IH_DUMMY_RD_EN
	 */
	पूर्णांकerrupt_cntl = REG_SET_FIELD(पूर्णांकerrupt_cntl, BIF_BX0_INTERRUPT_CNTL,
				       IH_DUMMY_RD_OVERRIDE, 0);

	/* INTERRUPT_CNTL__IH_REQ_NONSNOOP_EN_MASK=1 अगर ring is in non-cacheable memory, e.g., vram */
	पूर्णांकerrupt_cntl = REG_SET_FIELD(पूर्णांकerrupt_cntl, BIF_BX0_INTERRUPT_CNTL,
				       IH_REQ_NONSNOOP_EN, 0);

	WREG32_SOC15(NBIO, 0, regBIF_BX0_INTERRUPT_CNTL, पूर्णांकerrupt_cntl);
पूर्ण

अटल व्योम nbio_v7_2_update_medium_grain_घड़ी_gating(काष्ठा amdgpu_device *adev,
						       bool enable)
अणु
	uपूर्णांक32_t def, data;

	def = data = RREG32_PCIE_PORT(SOC15_REG_OFFSET(NBIO, 0, regCPM_CONTROL));
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
		WREG32_PCIE_PORT(SOC15_REG_OFFSET(NBIO, 0, regCPM_CONTROL), data);
पूर्ण

अटल व्योम nbio_v7_2_update_medium_grain_light_sleep(काष्ठा amdgpu_device *adev,
						      bool enable)
अणु
	uपूर्णांक32_t def, data;

	def = data = RREG32_PCIE_PORT(SOC15_REG_OFFSET(NBIO, 0, regPCIE_CNTL2));
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
		WREG32_PCIE_PORT(SOC15_REG_OFFSET(NBIO, 0, regPCIE_CNTL2), data);
पूर्ण

अटल व्योम nbio_v7_2_get_घड़ीgating_state(काष्ठा amdgpu_device *adev,
					    u32 *flags)
अणु
	पूर्णांक data;

	/* AMD_CG_SUPPORT_BIF_MGCG */
	data = RREG32_PCIE_PORT(SOC15_REG_OFFSET(NBIO, 0, regCPM_CONTROL));
	अगर (data & CPM_CONTROL__LCLK_DYN_GATE_ENABLE_MASK)
		*flags |= AMD_CG_SUPPORT_BIF_MGCG;

	/* AMD_CG_SUPPORT_BIF_LS */
	data = RREG32_PCIE_PORT(SOC15_REG_OFFSET(NBIO, 0, regPCIE_CNTL2));
	अगर (data & PCIE_CNTL2__SLV_MEM_LS_EN_MASK)
		*flags |= AMD_CG_SUPPORT_BIF_LS;
पूर्ण

अटल u32 nbio_v7_2_get_hdp_flush_req_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, regBIF_BX_PF0_GPU_HDP_FLUSH_REQ);
पूर्ण

अटल u32 nbio_v7_2_get_hdp_flush_करोne_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, regBIF_BX_PF0_GPU_HDP_FLUSH_DONE);
पूर्ण

अटल u32 nbio_v7_2_get_pcie_index_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, regBIF_BX0_PCIE_INDEX2);
पूर्ण

अटल u32 nbio_v7_2_get_pcie_data_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, regBIF_BX0_PCIE_DATA2);
पूर्ण

अटल u32 nbio_v7_2_get_pcie_port_index_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, regBIF_BX_PF0_RSMU_INDEX);
पूर्ण

अटल u32 nbio_v7_2_get_pcie_port_data_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, regBIF_BX_PF0_RSMU_DATA);
पूर्ण

स्थिर काष्ठा nbio_hdp_flush_reg nbio_v7_2_hdp_flush_reg = अणु
	.ref_and_mask_cp0 = BIF_BX_PF0_GPU_HDP_FLUSH_DONE__CP0_MASK,
	.ref_and_mask_cp1 = BIF_BX_PF0_GPU_HDP_FLUSH_DONE__CP1_MASK,
	.ref_and_mask_cp2 = BIF_BX_PF0_GPU_HDP_FLUSH_DONE__CP2_MASK,
	.ref_and_mask_cp3 = BIF_BX_PF0_GPU_HDP_FLUSH_DONE__CP3_MASK,
	.ref_and_mask_cp4 = BIF_BX_PF0_GPU_HDP_FLUSH_DONE__CP4_MASK,
	.ref_and_mask_cp5 = BIF_BX_PF0_GPU_HDP_FLUSH_DONE__CP5_MASK,
	.ref_and_mask_cp6 = BIF_BX_PF0_GPU_HDP_FLUSH_DONE__CP6_MASK,
	.ref_and_mask_cp7 = BIF_BX_PF0_GPU_HDP_FLUSH_DONE__CP7_MASK,
	.ref_and_mask_cp8 = BIF_BX_PF0_GPU_HDP_FLUSH_DONE__CP8_MASK,
	.ref_and_mask_cp9 = BIF_BX_PF0_GPU_HDP_FLUSH_DONE__CP9_MASK,
	.ref_and_mask_sdma0 = BIF_BX_PF0_GPU_HDP_FLUSH_DONE__SDMA0_MASK,
	.ref_and_mask_sdma1 = BIF_BX_PF0_GPU_HDP_FLUSH_DONE__SDMA1_MASK,
पूर्ण;

अटल व्योम nbio_v7_2_init_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t def, data;

	def = data = RREG32_PCIE_PORT(SOC15_REG_OFFSET(NBIO, 0, regPCIE_CONFIG_CNTL));
	data = REG_SET_FIELD(data, PCIE_CONFIG_CNTL, CI_SWUS_MAX_READ_REQUEST_SIZE_MODE, 1);
	data = REG_SET_FIELD(data, PCIE_CONFIG_CNTL, CI_SWUS_MAX_READ_REQUEST_SIZE_PRIV, 1);

	अगर (def != data)
		WREG32_PCIE_PORT(SOC15_REG_OFFSET(NBIO, 0, regPCIE_CONFIG_CNTL),
				 data);
पूर्ण

स्थिर काष्ठा amdgpu_nbio_funcs nbio_v7_2_funcs = अणु
	.get_hdp_flush_req_offset = nbio_v7_2_get_hdp_flush_req_offset,
	.get_hdp_flush_करोne_offset = nbio_v7_2_get_hdp_flush_करोne_offset,
	.get_pcie_index_offset = nbio_v7_2_get_pcie_index_offset,
	.get_pcie_data_offset = nbio_v7_2_get_pcie_data_offset,
	.get_pcie_port_index_offset = nbio_v7_2_get_pcie_port_index_offset,
	.get_pcie_port_data_offset = nbio_v7_2_get_pcie_port_data_offset,
	.get_rev_id = nbio_v7_2_get_rev_id,
	.mc_access_enable = nbio_v7_2_mc_access_enable,
	.get_memsize = nbio_v7_2_get_memsize,
	.sdma_करोorbell_range = nbio_v7_2_sdma_करोorbell_range,
	.vcn_करोorbell_range = nbio_v7_2_vcn_करोorbell_range,
	.enable_करोorbell_aperture = nbio_v7_2_enable_करोorbell_aperture,
	.enable_करोorbell_selfring_aperture = nbio_v7_2_enable_करोorbell_selfring_aperture,
	.ih_करोorbell_range = nbio_v7_2_ih_करोorbell_range,
	.update_medium_grain_घड़ी_gating = nbio_v7_2_update_medium_grain_घड़ी_gating,
	.update_medium_grain_light_sleep = nbio_v7_2_update_medium_grain_light_sleep,
	.get_घड़ीgating_state = nbio_v7_2_get_घड़ीgating_state,
	.ih_control = nbio_v7_2_ih_control,
	.init_रेजिस्टरs = nbio_v7_2_init_रेजिस्टरs,
	.remap_hdp_रेजिस्टरs = nbio_v7_2_remap_hdp_रेजिस्टरs,
पूर्ण;
