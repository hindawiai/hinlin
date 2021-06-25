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
#समावेश "amdgpu.h"
#समावेश "amdgpu_atombios.h"
#समावेश "nbio_v7_0.h"

#समावेश "nbio/nbio_7_0_default.h"
#समावेश "nbio/nbio_7_0_offset.h"
#समावेश "nbio/nbio_7_0_sh_mask.h"
#समावेश "nbio/nbio_7_0_smn.h"
#समावेश "vega10_enum.h"
#समावेश <uapi/linux/kfd_ioctl.h>

#घोषणा smnNBIF_MGCG_CTRL_LCLK	0x1013a05c

अटल व्योम nbio_v7_0_remap_hdp_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	WREG32_SOC15(NBIO, 0, mmREMAP_HDP_MEM_FLUSH_CNTL,
		adev->rmmio_remap.reg_offset + KFD_MMIO_REMAP_HDP_MEM_FLUSH_CNTL);
	WREG32_SOC15(NBIO, 0, mmREMAP_HDP_REG_FLUSH_CNTL,
		adev->rmmio_remap.reg_offset + KFD_MMIO_REMAP_HDP_REG_FLUSH_CNTL);
पूर्ण

अटल u32 nbio_v7_0_get_rev_id(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp = RREG32_SOC15(NBIO, 0, mmRCC_DEV0_EPF0_STRAP0);

	पंचांगp &= RCC_DEV0_EPF0_STRAP0__STRAP_ATI_REV_ID_DEV0_F0_MASK;
	पंचांगp >>= RCC_DEV0_EPF0_STRAP0__STRAP_ATI_REV_ID_DEV0_F0__SHIFT;

	वापस पंचांगp;
पूर्ण

अटल व्योम nbio_v7_0_mc_access_enable(काष्ठा amdgpu_device *adev, bool enable)
अणु
	अगर (enable)
		WREG32_SOC15(NBIO, 0, mmBIF_FB_EN,
			BIF_FB_EN__FB_READ_EN_MASK | BIF_FB_EN__FB_WRITE_EN_MASK);
	अन्यथा
		WREG32_SOC15(NBIO, 0, mmBIF_FB_EN, 0);
पूर्ण

अटल u32 nbio_v7_0_get_memsize(काष्ठा amdgpu_device *adev)
अणु
	वापस RREG32_SOC15(NBIO, 0, mmRCC_CONFIG_MEMSIZE);
पूर्ण

अटल व्योम nbio_v7_0_sdma_करोorbell_range(काष्ठा amdgpu_device *adev, पूर्णांक instance,
			bool use_करोorbell, पूर्णांक करोorbell_index, पूर्णांक करोorbell_size)
अणु
	u32 reg = instance == 0 ? SOC15_REG_OFFSET(NBIO, 0, mmBIF_SDMA0_DOORBELL_RANGE) :
			SOC15_REG_OFFSET(NBIO, 0, mmBIF_SDMA1_DOORBELL_RANGE);

	u32 करोorbell_range = RREG32(reg);

	अगर (use_करोorbell) अणु
		करोorbell_range = REG_SET_FIELD(करोorbell_range, BIF_SDMA0_DOORBELL_RANGE, OFFSET, करोorbell_index);
		करोorbell_range = REG_SET_FIELD(करोorbell_range, BIF_SDMA0_DOORBELL_RANGE, SIZE, करोorbell_size);
	पूर्ण अन्यथा
		करोorbell_range = REG_SET_FIELD(करोorbell_range, BIF_SDMA0_DOORBELL_RANGE, SIZE, 0);

	WREG32(reg, करोorbell_range);
पूर्ण

अटल व्योम nbio_v7_0_vcn_करोorbell_range(काष्ठा amdgpu_device *adev, bool use_करोorbell,
					 पूर्णांक करोorbell_index, पूर्णांक instance)
अणु
	u32 reg = SOC15_REG_OFFSET(NBIO, 0, mmBIF_MMSCH0_DOORBELL_RANGE);

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

अटल व्योम nbio_v7_0_enable_करोorbell_aperture(काष्ठा amdgpu_device *adev,
					       bool enable)
अणु
	WREG32_FIELD15(NBIO, 0, RCC_DOORBELL_APER_EN, BIF_DOORBELL_APER_EN, enable ? 1 : 0);
पूर्ण

अटल व्योम nbio_v7_0_enable_करोorbell_selfring_aperture(काष्ठा amdgpu_device *adev,
							bool enable)
अणु

पूर्ण

अटल व्योम nbio_v7_0_ih_करोorbell_range(काष्ठा amdgpu_device *adev,
					bool use_करोorbell, पूर्णांक करोorbell_index)
अणु
	u32 ih_करोorbell_range = RREG32_SOC15(NBIO, 0, mmBIF_IH_DOORBELL_RANGE);

	अगर (use_करोorbell) अणु
		ih_करोorbell_range = REG_SET_FIELD(ih_करोorbell_range, BIF_IH_DOORBELL_RANGE, OFFSET, करोorbell_index);
		ih_करोorbell_range = REG_SET_FIELD(ih_करोorbell_range, BIF_IH_DOORBELL_RANGE, SIZE, 2);
	पूर्ण अन्यथा
		ih_करोorbell_range = REG_SET_FIELD(ih_करोorbell_range, BIF_IH_DOORBELL_RANGE, SIZE, 0);

	WREG32_SOC15(NBIO, 0, mmBIF_IH_DOORBELL_RANGE, ih_करोorbell_range);
पूर्ण

अटल uपूर्णांक32_t nbio_7_0_पढ़ो_syshub_ind_mmr(काष्ठा amdgpu_device *adev, uपूर्णांक32_t offset)
अणु
	uपूर्णांक32_t data;

	WREG32_SOC15(NBIO, 0, mmSYSHUB_INDEX, offset);
	data = RREG32_SOC15(NBIO, 0, mmSYSHUB_DATA);

	वापस data;
पूर्ण

अटल व्योम nbio_7_0_ग_लिखो_syshub_ind_mmr(काष्ठा amdgpu_device *adev, uपूर्णांक32_t offset,
				       uपूर्णांक32_t data)
अणु
	WREG32_SOC15(NBIO, 0, mmSYSHUB_INDEX, offset);
	WREG32_SOC15(NBIO, 0, mmSYSHUB_DATA, data);
पूर्ण

अटल व्योम nbio_v7_0_update_medium_grain_घड़ी_gating(काष्ठा amdgpu_device *adev,
						       bool enable)
अणु
	uपूर्णांक32_t def, data;

	/* NBIF_MGCG_CTRL_LCLK */
	def = data = RREG32_PCIE(smnNBIF_MGCG_CTRL_LCLK);

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_BIF_MGCG))
		data |= NBIF_MGCG_CTRL_LCLK__NBIF_MGCG_EN_LCLK_MASK;
	अन्यथा
		data &= ~NBIF_MGCG_CTRL_LCLK__NBIF_MGCG_EN_LCLK_MASK;

	अगर (def != data)
		WREG32_PCIE(smnNBIF_MGCG_CTRL_LCLK, data);

	/* SYSHUB_MGCG_CTRL_SOCCLK */
	def = data = nbio_7_0_पढ़ो_syshub_ind_mmr(adev, ixSYSHUB_MMREG_IND_SYSHUB_MGCG_CTRL_SOCCLK);

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_BIF_MGCG))
		data |= SYSHUB_MMREG_सूचीECT_SYSHUB_MGCG_CTRL_SOCCLK__SYSHUB_MGCG_EN_SOCCLK_MASK;
	अन्यथा
		data &= ~SYSHUB_MMREG_सूचीECT_SYSHUB_MGCG_CTRL_SOCCLK__SYSHUB_MGCG_EN_SOCCLK_MASK;

	अगर (def != data)
		nbio_7_0_ग_लिखो_syshub_ind_mmr(adev, ixSYSHUB_MMREG_IND_SYSHUB_MGCG_CTRL_SOCCLK, data);

	/* SYSHUB_MGCG_CTRL_SHUBCLK */
	def = data = nbio_7_0_पढ़ो_syshub_ind_mmr(adev, ixSYSHUB_MMREG_IND_SYSHUB_MGCG_CTRL_SHUBCLK);

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_BIF_MGCG))
		data |= SYSHUB_MMREG_सूचीECT_SYSHUB_MGCG_CTRL_SHUBCLK__SYSHUB_MGCG_EN_SHUBCLK_MASK;
	अन्यथा
		data &= ~SYSHUB_MMREG_सूचीECT_SYSHUB_MGCG_CTRL_SHUBCLK__SYSHUB_MGCG_EN_SHUBCLK_MASK;

	अगर (def != data)
		nbio_7_0_ग_लिखो_syshub_ind_mmr(adev, ixSYSHUB_MMREG_IND_SYSHUB_MGCG_CTRL_SHUBCLK, data);
पूर्ण

अटल व्योम nbio_v7_0_update_medium_grain_light_sleep(काष्ठा amdgpu_device *adev,
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

अटल व्योम nbio_v7_0_get_घड़ीgating_state(काष्ठा amdgpu_device *adev,
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

अटल व्योम nbio_v7_0_ih_control(काष्ठा amdgpu_device *adev)
अणु
	u32 पूर्णांकerrupt_cntl;

	/* setup पूर्णांकerrupt control */
	WREG32_SOC15(NBIO, 0, mmINTERRUPT_CNTL2, adev->dummy_page_addr >> 8);
	पूर्णांकerrupt_cntl = RREG32_SOC15(NBIO, 0, mmINTERRUPT_CNTL);
	/* INTERRUPT_CNTL__IH_DUMMY_RD_OVERRIDE_MASK=0 - dummy पढ़ो disabled with msi, enabled without msi
	 * INTERRUPT_CNTL__IH_DUMMY_RD_OVERRIDE_MASK=1 - dummy पढ़ो controlled by IH_DUMMY_RD_EN
	 */
	पूर्णांकerrupt_cntl = REG_SET_FIELD(पूर्णांकerrupt_cntl, INTERRUPT_CNTL, IH_DUMMY_RD_OVERRIDE, 0);
	/* INTERRUPT_CNTL__IH_REQ_NONSNOOP_EN_MASK=1 अगर ring is in non-cacheable memory, e.g., vram */
	पूर्णांकerrupt_cntl = REG_SET_FIELD(पूर्णांकerrupt_cntl, INTERRUPT_CNTL, IH_REQ_NONSNOOP_EN, 0);
	WREG32_SOC15(NBIO, 0, mmINTERRUPT_CNTL, पूर्णांकerrupt_cntl);
पूर्ण

अटल u32 nbio_v7_0_get_hdp_flush_req_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, mmGPU_HDP_FLUSH_REQ);
पूर्ण

अटल u32 nbio_v7_0_get_hdp_flush_करोne_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, mmGPU_HDP_FLUSH_DONE);
पूर्ण

अटल u32 nbio_v7_0_get_pcie_index_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, mmPCIE_INDEX2);
पूर्ण

अटल u32 nbio_v7_0_get_pcie_data_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, mmPCIE_DATA2);
पूर्ण

स्थिर काष्ठा nbio_hdp_flush_reg nbio_v7_0_hdp_flush_reg = अणु
	.ref_and_mask_cp0 = GPU_HDP_FLUSH_DONE__CP0_MASK,
	.ref_and_mask_cp1 = GPU_HDP_FLUSH_DONE__CP1_MASK,
	.ref_and_mask_cp2 = GPU_HDP_FLUSH_DONE__CP2_MASK,
	.ref_and_mask_cp3 = GPU_HDP_FLUSH_DONE__CP3_MASK,
	.ref_and_mask_cp4 = GPU_HDP_FLUSH_DONE__CP4_MASK,
	.ref_and_mask_cp5 = GPU_HDP_FLUSH_DONE__CP5_MASK,
	.ref_and_mask_cp6 = GPU_HDP_FLUSH_DONE__CP6_MASK,
	.ref_and_mask_cp7 = GPU_HDP_FLUSH_DONE__CP7_MASK,
	.ref_and_mask_cp8 = GPU_HDP_FLUSH_DONE__CP8_MASK,
	.ref_and_mask_cp9 = GPU_HDP_FLUSH_DONE__CP9_MASK,
	.ref_and_mask_sdma0 = GPU_HDP_FLUSH_DONE__SDMA0_MASK,
	.ref_and_mask_sdma1 = GPU_HDP_FLUSH_DONE__SDMA1_MASK,
पूर्ण;

अटल व्योम nbio_v7_0_init_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु

पूर्ण

स्थिर काष्ठा amdgpu_nbio_funcs nbio_v7_0_funcs = अणु
	.get_hdp_flush_req_offset = nbio_v7_0_get_hdp_flush_req_offset,
	.get_hdp_flush_करोne_offset = nbio_v7_0_get_hdp_flush_करोne_offset,
	.get_pcie_index_offset = nbio_v7_0_get_pcie_index_offset,
	.get_pcie_data_offset = nbio_v7_0_get_pcie_data_offset,
	.get_rev_id = nbio_v7_0_get_rev_id,
	.mc_access_enable = nbio_v7_0_mc_access_enable,
	.get_memsize = nbio_v7_0_get_memsize,
	.sdma_करोorbell_range = nbio_v7_0_sdma_करोorbell_range,
	.vcn_करोorbell_range = nbio_v7_0_vcn_करोorbell_range,
	.enable_करोorbell_aperture = nbio_v7_0_enable_करोorbell_aperture,
	.enable_करोorbell_selfring_aperture = nbio_v7_0_enable_करोorbell_selfring_aperture,
	.ih_करोorbell_range = nbio_v7_0_ih_करोorbell_range,
	.update_medium_grain_घड़ी_gating = nbio_v7_0_update_medium_grain_घड़ी_gating,
	.update_medium_grain_light_sleep = nbio_v7_0_update_medium_grain_light_sleep,
	.get_घड़ीgating_state = nbio_v7_0_get_घड़ीgating_state,
	.ih_control = nbio_v7_0_ih_control,
	.init_रेजिस्टरs = nbio_v7_0_init_रेजिस्टरs,
	.remap_hdp_रेजिस्टरs = nbio_v7_0_remap_hdp_रेजिस्टरs,
पूर्ण;
