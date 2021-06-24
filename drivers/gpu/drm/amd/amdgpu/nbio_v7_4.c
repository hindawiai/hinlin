<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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
#समावेश "nbio_v7_4.h"
#समावेश "amdgpu_ras.h"

#समावेश "nbio/nbio_7_4_offset.h"
#समावेश "nbio/nbio_7_4_sh_mask.h"
#समावेश "nbio/nbio_7_4_0_smn.h"
#समावेश "ivsrcid/nbio/irqsrcs_nbif_7_4.h"
#समावेश <uapi/linux/kfd_ioctl.h>

#घोषणा smnPCIE_LC_CNTL		0x11140280
#घोषणा smnPCIE_LC_CNTL3	0x111402d4
#घोषणा smnPCIE_LC_CNTL6	0x111402ec
#घोषणा smnPCIE_LC_CNTL7	0x111402f0
#घोषणा smnNBIF_MGCG_CTRL_LCLK	0x1013a21c
#घोषणा smnRCC_BIF_STRAP3	0x1012348c
#घोषणा RCC_BIF_STRAP3__STRAP_VLINK_ASPM_IDLE_TIMER_MASK	0x0000FFFFL
#घोषणा RCC_BIF_STRAP3__STRAP_VLINK_PM_L1_ENTRY_TIMER_MASK	0xFFFF0000L
#घोषणा smnRCC_BIF_STRAP5	0x10123494
#घोषणा RCC_BIF_STRAP5__STRAP_VLINK_LDN_ENTRY_TIMER_MASK	0x0000FFFFL
#घोषणा smnBIF_CFG_DEV0_EPF0_DEVICE_CNTL2	0x1014008c
#घोषणा BIF_CFG_DEV0_EPF0_DEVICE_CNTL2__LTR_EN_MASK			0x0400L
#घोषणा smnBIF_CFG_DEV0_EPF0_PCIE_LTR_CAP	0x10140324
#घोषणा smnPSWUSP0_PCIE_LC_CNTL2		0x111402c4
#घोषणा smnRCC_EP_DEV0_0_EP_PCIE_TX_LTR_CNTL	0x10123538
#घोषणा smnRCC_BIF_STRAP2	0x10123488
#घोषणा RCC_BIF_STRAP2__STRAP_LTR_IN_ASPML1_DIS_MASK	0x00004000L
#घोषणा RCC_BIF_STRAP3__STRAP_VLINK_ASPM_IDLE_TIMER__SHIFT	0x0
#घोषणा RCC_BIF_STRAP3__STRAP_VLINK_PM_L1_ENTRY_TIMER__SHIFT	0x10
#घोषणा RCC_BIF_STRAP5__STRAP_VLINK_LDN_ENTRY_TIMER__SHIFT	0x0

/*
 * These are nbio v7_4_1 रेजिस्टरs mask. Temporarily define these here since
 * nbio v7_4_1 header is incomplete.
 */
#घोषणा GPU_HDP_FLUSH_DONE__RSVD_ENG0_MASK	0x00001000L
#घोषणा GPU_HDP_FLUSH_DONE__RSVD_ENG1_MASK	0x00002000L
#घोषणा GPU_HDP_FLUSH_DONE__RSVD_ENG2_MASK	0x00004000L
#घोषणा GPU_HDP_FLUSH_DONE__RSVD_ENG3_MASK	0x00008000L
#घोषणा GPU_HDP_FLUSH_DONE__RSVD_ENG4_MASK	0x00010000L
#घोषणा GPU_HDP_FLUSH_DONE__RSVD_ENG5_MASK	0x00020000L

#घोषणा mmBIF_MMSCH1_DOORBELL_RANGE                     0x01dc
#घोषणा mmBIF_MMSCH1_DOORBELL_RANGE_BASE_IDX            2
//BIF_MMSCH1_DOORBELL_RANGE
#घोषणा BIF_MMSCH1_DOORBELL_RANGE__OFFSET__SHIFT        0x2
#घोषणा BIF_MMSCH1_DOORBELL_RANGE__SIZE__SHIFT          0x10
#घोषणा BIF_MMSCH1_DOORBELL_RANGE__OFFSET_MASK          0x00000FFCL
#घोषणा BIF_MMSCH1_DOORBELL_RANGE__SIZE_MASK            0x001F0000L

#घोषणा BIF_MMSCH1_DOORBELL_RANGE__OFFSET_MASK          0x00000FFCL
#घोषणा BIF_MMSCH1_DOORBELL_RANGE__SIZE_MASK            0x001F0000L

#घोषणा mmBIF_MMSCH1_DOORBELL_RANGE_ALDE                0x01d8
#घोषणा mmBIF_MMSCH1_DOORBELL_RANGE_ALDE_BASE_IDX       2
//BIF_MMSCH1_DOORBELL_ALDE_RANGE
#घोषणा BIF_MMSCH1_DOORBELL_RANGE_ALDE__OFFSET__SHIFT   0x2
#घोषणा BIF_MMSCH1_DOORBELL_RANGE_ALDE__SIZE__SHIFT     0x10
#घोषणा BIF_MMSCH1_DOORBELL_RANGE_ALDE__OFFSET_MASK     0x00000FFCL
#घोषणा BIF_MMSCH1_DOORBELL_RANGE_ALDE__SIZE_MASK       0x001F0000L

#घोषणा mmRCC_DEV0_EPF0_STRAP0_ALDE			0x0015
#घोषणा mmRCC_DEV0_EPF0_STRAP0_ALDE_BASE_IDX		2

अटल व्योम nbio_v7_4_query_ras_error_count(काष्ठा amdgpu_device *adev,
					व्योम *ras_error_status);

अटल व्योम nbio_v7_4_remap_hdp_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	WREG32_SOC15(NBIO, 0, mmREMAP_HDP_MEM_FLUSH_CNTL,
		adev->rmmio_remap.reg_offset + KFD_MMIO_REMAP_HDP_MEM_FLUSH_CNTL);
	WREG32_SOC15(NBIO, 0, mmREMAP_HDP_REG_FLUSH_CNTL,
		adev->rmmio_remap.reg_offset + KFD_MMIO_REMAP_HDP_REG_FLUSH_CNTL);
पूर्ण

अटल u32 nbio_v7_4_get_rev_id(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp;

	अगर (adev->asic_type == CHIP_ALDEBARAN)
		पंचांगp = RREG32_SOC15(NBIO, 0, mmRCC_DEV0_EPF0_STRAP0_ALDE);
	अन्यथा
		पंचांगp = RREG32_SOC15(NBIO, 0, mmRCC_DEV0_EPF0_STRAP0);

	पंचांगp &= RCC_DEV0_EPF0_STRAP0__STRAP_ATI_REV_ID_DEV0_F0_MASK;
	पंचांगp >>= RCC_DEV0_EPF0_STRAP0__STRAP_ATI_REV_ID_DEV0_F0__SHIFT;

	वापस पंचांगp;
पूर्ण

अटल व्योम nbio_v7_4_mc_access_enable(काष्ठा amdgpu_device *adev, bool enable)
अणु
	अगर (enable)
		WREG32_SOC15(NBIO, 0, mmBIF_FB_EN,
			BIF_FB_EN__FB_READ_EN_MASK | BIF_FB_EN__FB_WRITE_EN_MASK);
	अन्यथा
		WREG32_SOC15(NBIO, 0, mmBIF_FB_EN, 0);
पूर्ण

अटल u32 nbio_v7_4_get_memsize(काष्ठा amdgpu_device *adev)
अणु
	वापस RREG32_SOC15(NBIO, 0, mmRCC_CONFIG_MEMSIZE);
पूर्ण

अटल व्योम nbio_v7_4_sdma_करोorbell_range(काष्ठा amdgpu_device *adev, पूर्णांक instance,
			bool use_करोorbell, पूर्णांक करोorbell_index, पूर्णांक करोorbell_size)
अणु
	u32 reg, करोorbell_range;

	अगर (instance < 2) अणु
		reg = instance +
			SOC15_REG_OFFSET(NBIO, 0, mmBIF_SDMA0_DOORBELL_RANGE);
	पूर्ण अन्यथा अणु
		/*
		 * These रेजिस्टरs address of SDMA2~7 is not consecutive
		 * from SDMA0~1. Need plus 4 dwords offset.
		 *
		 *   BIF_SDMA0_DOORBELL_RANGE:  0x3bc0
		 *   BIF_SDMA1_DOORBELL_RANGE:  0x3bc4
		 *   BIF_SDMA2_DOORBELL_RANGE:  0x3bd8
+		 *   BIF_SDMA4_DOORBELL_RANGE:
+		 *     ARCTURUS:  0x3be0
+		 *     ALDEBARAN: 0x3be4
		 */
		अगर (adev->asic_type == CHIP_ALDEBARAN && instance == 4)
			reg = instance + 0x4 + 0x1 +
				SOC15_REG_OFFSET(NBIO, 0,
						 mmBIF_SDMA0_DOORBELL_RANGE);
		अन्यथा
			reg = instance + 0x4 +
				SOC15_REG_OFFSET(NBIO, 0,
						 mmBIF_SDMA0_DOORBELL_RANGE);
	पूर्ण

	करोorbell_range = RREG32(reg);

	अगर (use_करोorbell) अणु
		करोorbell_range = REG_SET_FIELD(करोorbell_range, BIF_SDMA0_DOORBELL_RANGE, OFFSET, करोorbell_index);
		करोorbell_range = REG_SET_FIELD(करोorbell_range, BIF_SDMA0_DOORBELL_RANGE, SIZE, करोorbell_size);
	पूर्ण अन्यथा
		करोorbell_range = REG_SET_FIELD(करोorbell_range, BIF_SDMA0_DOORBELL_RANGE, SIZE, 0);

	WREG32(reg, करोorbell_range);
पूर्ण

अटल व्योम nbio_v7_4_vcn_करोorbell_range(काष्ठा amdgpu_device *adev, bool use_करोorbell,
					 पूर्णांक करोorbell_index, पूर्णांक instance)
अणु
	u32 reg;
	u32 करोorbell_range;

	अगर (instance) अणु
		अगर (adev->asic_type == CHIP_ALDEBARAN)
			reg = SOC15_REG_OFFSET(NBIO, 0, mmBIF_MMSCH1_DOORBELL_RANGE_ALDE);
		अन्यथा
			reg = SOC15_REG_OFFSET(NBIO, 0, mmBIF_MMSCH1_DOORBELL_RANGE);
	पूर्ण अन्यथा
		reg = SOC15_REG_OFFSET(NBIO, 0, mmBIF_MMSCH0_DOORBELL_RANGE);

	करोorbell_range = RREG32(reg);

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

अटल व्योम nbio_v7_4_enable_करोorbell_aperture(काष्ठा amdgpu_device *adev,
					       bool enable)
अणु
	WREG32_FIELD15(NBIO, 0, RCC_DOORBELL_APER_EN, BIF_DOORBELL_APER_EN, enable ? 1 : 0);
पूर्ण

अटल व्योम nbio_v7_4_enable_करोorbell_selfring_aperture(काष्ठा amdgpu_device *adev,
							bool enable)
अणु
	u32 पंचांगp = 0;

	अगर (enable) अणु
		पंचांगp = REG_SET_FIELD(पंचांगp, DOORBELL_SELFRING_GPA_APER_CNTL, DOORBELL_SELFRING_GPA_APER_EN, 1) |
		      REG_SET_FIELD(पंचांगp, DOORBELL_SELFRING_GPA_APER_CNTL, DOORBELL_SELFRING_GPA_APER_MODE, 1) |
		      REG_SET_FIELD(पंचांगp, DOORBELL_SELFRING_GPA_APER_CNTL, DOORBELL_SELFRING_GPA_APER_SIZE, 0);

		WREG32_SOC15(NBIO, 0, mmDOORBELL_SELFRING_GPA_APER_BASE_LOW,
			     lower_32_bits(adev->करोorbell.base));
		WREG32_SOC15(NBIO, 0, mmDOORBELL_SELFRING_GPA_APER_BASE_HIGH,
			     upper_32_bits(adev->करोorbell.base));
	पूर्ण

	WREG32_SOC15(NBIO, 0, mmDOORBELL_SELFRING_GPA_APER_CNTL, पंचांगp);
पूर्ण

अटल व्योम nbio_v7_4_ih_करोorbell_range(काष्ठा amdgpu_device *adev,
					bool use_करोorbell, पूर्णांक करोorbell_index)
अणु
	u32 ih_करोorbell_range = RREG32_SOC15(NBIO, 0 , mmBIF_IH_DOORBELL_RANGE);

	अगर (use_करोorbell) अणु
		ih_करोorbell_range = REG_SET_FIELD(ih_करोorbell_range, BIF_IH_DOORBELL_RANGE, OFFSET, करोorbell_index);
		ih_करोorbell_range = REG_SET_FIELD(ih_करोorbell_range, BIF_IH_DOORBELL_RANGE, SIZE, 4);
	पूर्ण अन्यथा
		ih_करोorbell_range = REG_SET_FIELD(ih_करोorbell_range, BIF_IH_DOORBELL_RANGE, SIZE, 0);

	WREG32_SOC15(NBIO, 0, mmBIF_IH_DOORBELL_RANGE, ih_करोorbell_range);
पूर्ण


अटल व्योम nbio_v7_4_update_medium_grain_घड़ी_gating(काष्ठा amdgpu_device *adev,
						       bool enable)
अणु
	//TODO: Add support क्रम v7.4
पूर्ण

अटल व्योम nbio_v7_4_update_medium_grain_light_sleep(काष्ठा amdgpu_device *adev,
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

अटल व्योम nbio_v7_4_get_घड़ीgating_state(काष्ठा amdgpu_device *adev,
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

अटल व्योम nbio_v7_4_ih_control(काष्ठा amdgpu_device *adev)
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

अटल u32 nbio_v7_4_get_hdp_flush_req_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, mmGPU_HDP_FLUSH_REQ);
पूर्ण

अटल u32 nbio_v7_4_get_hdp_flush_करोne_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, mmGPU_HDP_FLUSH_DONE);
पूर्ण

अटल u32 nbio_v7_4_get_pcie_index_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, mmPCIE_INDEX2);
पूर्ण

अटल u32 nbio_v7_4_get_pcie_data_offset(काष्ठा amdgpu_device *adev)
अणु
	वापस SOC15_REG_OFFSET(NBIO, 0, mmPCIE_DATA2);
पूर्ण

स्थिर काष्ठा nbio_hdp_flush_reg nbio_v7_4_hdp_flush_reg = अणु
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
	.ref_and_mask_sdma2 = GPU_HDP_FLUSH_DONE__RSVD_ENG0_MASK,
	.ref_and_mask_sdma3 = GPU_HDP_FLUSH_DONE__RSVD_ENG1_MASK,
	.ref_and_mask_sdma4 = GPU_HDP_FLUSH_DONE__RSVD_ENG2_MASK,
	.ref_and_mask_sdma5 = GPU_HDP_FLUSH_DONE__RSVD_ENG3_MASK,
	.ref_and_mask_sdma6 = GPU_HDP_FLUSH_DONE__RSVD_ENG4_MASK,
	.ref_and_mask_sdma7 = GPU_HDP_FLUSH_DONE__RSVD_ENG5_MASK,
पूर्ण;

अटल व्योम nbio_v7_4_init_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु

पूर्ण

अटल व्योम nbio_v7_4_handle_ras_controller_पूर्णांकr_no_bअगरring(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t bअगर_करोorbell_पूर्णांकr_cntl;
	काष्ठा ras_manager *obj = amdgpu_ras_find_obj(adev, adev->nbio.ras_अगर);
	काष्ठा ras_err_data err_data = अणु0, 0, 0, शून्यपूर्ण;
	काष्ठा amdgpu_ras *ras = amdgpu_ras_get_context(adev);

	bअगर_करोorbell_पूर्णांकr_cntl = RREG32_SOC15(NBIO, 0, mmBIF_DOORBELL_INT_CNTL);
	अगर (REG_GET_FIELD(bअगर_करोorbell_पूर्णांकr_cntl,
		BIF_DOORBELL_INT_CNTL, RAS_CNTLR_INTERRUPT_STATUS)) अणु
		/* driver has to clear the पूर्णांकerrupt status when bअगर ring is disabled */
		bअगर_करोorbell_पूर्णांकr_cntl = REG_SET_FIELD(bअगर_करोorbell_पूर्णांकr_cntl,
						BIF_DOORBELL_INT_CNTL,
						RAS_CNTLR_INTERRUPT_CLEAR, 1);
		WREG32_SOC15(NBIO, 0, mmBIF_DOORBELL_INT_CNTL, bअगर_करोorbell_पूर्णांकr_cntl);

		अगर (!ras->disable_ras_err_cnt_harvest) अणु
			/*
			 * clear error status after ras_controller_पूर्णांकr
			 * according to hw team and count ue number
			 * क्रम query
			 */
			nbio_v7_4_query_ras_error_count(adev, &err_data);

			/* logging on error cnt and prपूर्णांकing क्रम awareness */
			obj->err_data.ue_count += err_data.ue_count;
			obj->err_data.ce_count += err_data.ce_count;

			अगर (err_data.ce_count)
				dev_info(adev->dev, "%ld correctable hardware "
						"errors detected in %s block, "
						"no user action is needed.\n",
						obj->err_data.ce_count,
						adev->nbio.ras_अगर->name);

			अगर (err_data.ue_count)
				dev_info(adev->dev, "%ld uncorrectable hardware "
						"errors detected in %s block\n",
						obj->err_data.ue_count,
						adev->nbio.ras_अगर->name);
		पूर्ण

		dev_info(adev->dev, "RAS controller interrupt triggered "
					"by NBIF error\n");

		/* ras_controller_पूर्णांक is dedicated क्रम nbअगर ras error,
		 * not the global पूर्णांकerrupt क्रम sync flood
		 */
		amdgpu_ras_reset_gpu(adev);
	पूर्ण
पूर्ण

अटल व्योम nbio_v7_4_handle_ras_err_event_athub_पूर्णांकr_no_bअगरring(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t bअगर_करोorbell_पूर्णांकr_cntl;

	bअगर_करोorbell_पूर्णांकr_cntl = RREG32_SOC15(NBIO, 0, mmBIF_DOORBELL_INT_CNTL);
	अगर (REG_GET_FIELD(bअगर_करोorbell_पूर्णांकr_cntl,
		BIF_DOORBELL_INT_CNTL, RAS_ATHUB_ERR_EVENT_INTERRUPT_STATUS)) अणु
		/* driver has to clear the पूर्णांकerrupt status when bअगर ring is disabled */
		bअगर_करोorbell_पूर्णांकr_cntl = REG_SET_FIELD(bअगर_करोorbell_पूर्णांकr_cntl,
						BIF_DOORBELL_INT_CNTL,
						RAS_ATHUB_ERR_EVENT_INTERRUPT_CLEAR, 1);
		WREG32_SOC15(NBIO, 0, mmBIF_DOORBELL_INT_CNTL, bअगर_करोorbell_पूर्णांकr_cntl);

		amdgpu_ras_global_ras_isr(adev);
	पूर्ण
पूर्ण


अटल पूर्णांक nbio_v7_4_set_ras_controller_irq_state(काष्ठा amdgpu_device *adev,
						  काष्ठा amdgpu_irq_src *src,
						  अचिन्हित type,
						  क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	/* The ras_controller_irq enablement should be करोne in psp bl when it
	 * tries to enable ras feature. Driver only need to set the correct पूर्णांकerrupt
	 * vector क्रम bare-metal and sriov use हाल respectively
	 */
	uपूर्णांक32_t bअगर_पूर्णांकr_cntl;

	bअगर_पूर्णांकr_cntl = RREG32_SOC15(NBIO, 0, mmBIF_INTR_CNTL);
	अगर (state == AMDGPU_IRQ_STATE_ENABLE) अणु
		/* set पूर्णांकerrupt vector select bit to 0 to select
		 * vetcor 1 क्रम bare metal हाल */
		bअगर_पूर्णांकr_cntl = REG_SET_FIELD(bअगर_पूर्णांकr_cntl,
					      BIF_INTR_CNTL,
					      RAS_INTR_VEC_SEL, 0);
		WREG32_SOC15(NBIO, 0, mmBIF_INTR_CNTL, bअगर_पूर्णांकr_cntl);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nbio_v7_4_process_ras_controller_irq(काष्ठा amdgpu_device *adev,
						काष्ठा amdgpu_irq_src *source,
						काष्ठा amdgpu_iv_entry *entry)
अणु
	/* By design, the ih cookie क्रम ras_controller_irq should be written
	 * to BIFring instead of general iv ring. However, due to known bअगर ring
	 * hw bug, it has to be disabled. There is no chance the process function
	 * will be involked. Just left it as a dummy one.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक nbio_v7_4_set_ras_err_event_athub_irq_state(काष्ठा amdgpu_device *adev,
						       काष्ठा amdgpu_irq_src *src,
						       अचिन्हित type,
						       क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	/* The ras_controller_irq enablement should be करोne in psp bl when it
	 * tries to enable ras feature. Driver only need to set the correct पूर्णांकerrupt
	 * vector क्रम bare-metal and sriov use हाल respectively
	 */
	uपूर्णांक32_t bअगर_पूर्णांकr_cntl;

	bअगर_पूर्णांकr_cntl = RREG32_SOC15(NBIO, 0, mmBIF_INTR_CNTL);
	अगर (state == AMDGPU_IRQ_STATE_ENABLE) अणु
		/* set पूर्णांकerrupt vector select bit to 0 to select
		 * vetcor 1 क्रम bare metal हाल */
		bअगर_पूर्णांकr_cntl = REG_SET_FIELD(bअगर_पूर्णांकr_cntl,
					      BIF_INTR_CNTL,
					      RAS_INTR_VEC_SEL, 0);
		WREG32_SOC15(NBIO, 0, mmBIF_INTR_CNTL, bअगर_पूर्णांकr_cntl);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nbio_v7_4_process_err_event_athub_irq(काष्ठा amdgpu_device *adev,
						 काष्ठा amdgpu_irq_src *source,
						 काष्ठा amdgpu_iv_entry *entry)
अणु
	/* By design, the ih cookie क्रम err_event_athub_irq should be written
	 * to BIFring instead of general iv ring. However, due to known bअगर ring
	 * hw bug, it has to be disabled. There is no chance the process function
	 * will be involked. Just left it as a dummy one.
	 */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs nbio_v7_4_ras_controller_irq_funcs = अणु
	.set = nbio_v7_4_set_ras_controller_irq_state,
	.process = nbio_v7_4_process_ras_controller_irq,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs nbio_v7_4_ras_err_event_athub_irq_funcs = अणु
	.set = nbio_v7_4_set_ras_err_event_athub_irq_state,
	.process = nbio_v7_4_process_err_event_athub_irq,
पूर्ण;

अटल पूर्णांक nbio_v7_4_init_ras_controller_पूर्णांकerrupt (काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	/* init the irq funcs */
	adev->nbio.ras_controller_irq.funcs =
		&nbio_v7_4_ras_controller_irq_funcs;
	adev->nbio.ras_controller_irq.num_types = 1;

	/* रेजिस्टर ras controller पूर्णांकerrupt */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_BIF,
			      NBIF_7_4__SRCID__RAS_CONTROLLER_INTERRUPT,
			      &adev->nbio.ras_controller_irq);

	वापस r;
पूर्ण

अटल पूर्णांक nbio_v7_4_init_ras_err_event_athub_पूर्णांकerrupt (काष्ठा amdgpu_device *adev)
अणु

	पूर्णांक r;

	/* init the irq funcs */
	adev->nbio.ras_err_event_athub_irq.funcs =
		&nbio_v7_4_ras_err_event_athub_irq_funcs;
	adev->nbio.ras_err_event_athub_irq.num_types = 1;

	/* रेजिस्टर ras err event athub पूर्णांकerrupt */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_BIF,
			      NBIF_7_4__SRCID__ERREVENT_ATHUB_INTERRUPT,
			      &adev->nbio.ras_err_event_athub_irq);

	वापस r;
पूर्ण

#घोषणा smnPARITY_ERROR_STATUS_UNCORR_GRP2	0x13a20030

अटल व्योम nbio_v7_4_query_ras_error_count(काष्ठा amdgpu_device *adev,
					व्योम *ras_error_status)
अणु
	uपूर्णांक32_t global_sts, central_sts, पूर्णांक_eoi, parity_sts;
	uपूर्णांक32_t corr, fatal, non_fatal;
	काष्ठा ras_err_data *err_data = (काष्ठा ras_err_data *)ras_error_status;

	global_sts = RREG32_PCIE(smnRAS_GLOBAL_STATUS_LO);
	corr = REG_GET_FIELD(global_sts, RAS_GLOBAL_STATUS_LO, ParityErrCorr);
	fatal = REG_GET_FIELD(global_sts, RAS_GLOBAL_STATUS_LO, ParityErrFatal);
	non_fatal = REG_GET_FIELD(global_sts, RAS_GLOBAL_STATUS_LO,
				ParityErrNonFatal);
	parity_sts = RREG32_PCIE(smnPARITY_ERROR_STATUS_UNCORR_GRP2);

	अगर (corr)
		err_data->ce_count++;
	अगर (fatal)
		err_data->ue_count++;

	अगर (corr || fatal || non_fatal) अणु
		central_sts = RREG32_PCIE(smnBIFL_RAS_CENTRAL_STATUS);
		/* clear error status रेजिस्टर */
		WREG32_PCIE(smnRAS_GLOBAL_STATUS_LO, global_sts);

		अगर (fatal)
			/* clear parity fatal error indication field */
			WREG32_PCIE(smnPARITY_ERROR_STATUS_UNCORR_GRP2,
				    parity_sts);

		अगर (REG_GET_FIELD(central_sts, BIFL_RAS_CENTRAL_STATUS,
				BIFL_RasContller_Intr_Recv)) अणु
			/* clear पूर्णांकerrupt status रेजिस्टर */
			WREG32_PCIE(smnBIFL_RAS_CENTRAL_STATUS, central_sts);
			पूर्णांक_eoi = RREG32_PCIE(smnIOHC_INTERRUPT_EOI);
			पूर्णांक_eoi = REG_SET_FIELD(पूर्णांक_eoi,
					IOHC_INTERRUPT_EOI, SMI_EOI, 1);
			WREG32_PCIE(smnIOHC_INTERRUPT_EOI, पूर्णांक_eoi);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nbio_v7_4_enable_करोorbell_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
						bool enable)
अणु
	WREG32_FIELD15(NBIO, 0, BIF_DOORBELL_INT_CNTL,
		       DOORBELL_INTERRUPT_DISABLE, enable ? 0 : 1);
पूर्ण

स्थिर काष्ठा amdgpu_nbio_ras_funcs nbio_v7_4_ras_funcs = अणु
	.handle_ras_controller_पूर्णांकr_no_bअगरring = nbio_v7_4_handle_ras_controller_पूर्णांकr_no_bअगरring,
	.handle_ras_err_event_athub_पूर्णांकr_no_bअगरring = nbio_v7_4_handle_ras_err_event_athub_पूर्णांकr_no_bअगरring,
	.init_ras_controller_पूर्णांकerrupt = nbio_v7_4_init_ras_controller_पूर्णांकerrupt,
	.init_ras_err_event_athub_पूर्णांकerrupt = nbio_v7_4_init_ras_err_event_athub_पूर्णांकerrupt,
	.query_ras_error_count = nbio_v7_4_query_ras_error_count,
	.ras_late_init = amdgpu_nbio_ras_late_init,
	.ras_fini = amdgpu_nbio_ras_fini,
पूर्ण;

अटल व्योम nbio_v7_4_program_ltr(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t def, data;

	WREG32_PCIE(smnRCC_EP_DEV0_0_EP_PCIE_TX_LTR_CNTL, 0x75EB);

	def = data = RREG32_PCIE(smnRCC_BIF_STRAP2);
	data &= ~RCC_BIF_STRAP2__STRAP_LTR_IN_ASPML1_DIS_MASK;
	अगर (def != data)
		WREG32_PCIE(smnRCC_BIF_STRAP2, data);

	def = data = RREG32_PCIE(smnRCC_EP_DEV0_0_EP_PCIE_TX_LTR_CNTL);
	data &= ~EP_PCIE_TX_LTR_CNTL__LTR_PRIV_MSG_DIS_IN_PM_NON_D0_MASK;
	अगर (def != data)
		WREG32_PCIE(smnRCC_EP_DEV0_0_EP_PCIE_TX_LTR_CNTL, data);

	def = data = RREG32_PCIE(smnBIF_CFG_DEV0_EPF0_DEVICE_CNTL2);
	data |= BIF_CFG_DEV0_EPF0_DEVICE_CNTL2__LTR_EN_MASK;
	अगर (def != data)
		WREG32_PCIE(smnBIF_CFG_DEV0_EPF0_DEVICE_CNTL2, data);
पूर्ण

अटल व्योम nbio_v7_4_program_aspm(काष्ठा amdgpu_device *adev)
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

	def = data = RREG32_PCIE(smnRCC_BIF_STRAP3);
	data &= ~RCC_BIF_STRAP3__STRAP_VLINK_ASPM_IDLE_TIMER_MASK;
	data &= ~RCC_BIF_STRAP3__STRAP_VLINK_PM_L1_ENTRY_TIMER_MASK;
	अगर (def != data)
		WREG32_PCIE(smnRCC_BIF_STRAP3, data);

	def = data = RREG32_PCIE(smnRCC_BIF_STRAP5);
	data &= ~RCC_BIF_STRAP5__STRAP_VLINK_LDN_ENTRY_TIMER_MASK;
	अगर (def != data)
		WREG32_PCIE(smnRCC_BIF_STRAP5, data);

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

	nbio_v7_4_program_ltr(adev);

	def = data = RREG32_PCIE(smnRCC_BIF_STRAP3);
	data |= 0x5DE0 << RCC_BIF_STRAP3__STRAP_VLINK_ASPM_IDLE_TIMER__SHIFT;
	data |= 0x0010 << RCC_BIF_STRAP3__STRAP_VLINK_PM_L1_ENTRY_TIMER__SHIFT;
	अगर (def != data)
		WREG32_PCIE(smnRCC_BIF_STRAP3, data);

	def = data = RREG32_PCIE(smnRCC_BIF_STRAP5);
	data |= 0x0010 << RCC_BIF_STRAP5__STRAP_VLINK_LDN_ENTRY_TIMER__SHIFT;
	अगर (def != data)
		WREG32_PCIE(smnRCC_BIF_STRAP5, data);

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

स्थिर काष्ठा amdgpu_nbio_funcs nbio_v7_4_funcs = अणु
	.get_hdp_flush_req_offset = nbio_v7_4_get_hdp_flush_req_offset,
	.get_hdp_flush_करोne_offset = nbio_v7_4_get_hdp_flush_करोne_offset,
	.get_pcie_index_offset = nbio_v7_4_get_pcie_index_offset,
	.get_pcie_data_offset = nbio_v7_4_get_pcie_data_offset,
	.get_rev_id = nbio_v7_4_get_rev_id,
	.mc_access_enable = nbio_v7_4_mc_access_enable,
	.get_memsize = nbio_v7_4_get_memsize,
	.sdma_करोorbell_range = nbio_v7_4_sdma_करोorbell_range,
	.vcn_करोorbell_range = nbio_v7_4_vcn_करोorbell_range,
	.enable_करोorbell_aperture = nbio_v7_4_enable_करोorbell_aperture,
	.enable_करोorbell_selfring_aperture = nbio_v7_4_enable_करोorbell_selfring_aperture,
	.ih_करोorbell_range = nbio_v7_4_ih_करोorbell_range,
	.enable_करोorbell_पूर्णांकerrupt = nbio_v7_4_enable_करोorbell_पूर्णांकerrupt,
	.update_medium_grain_घड़ी_gating = nbio_v7_4_update_medium_grain_घड़ी_gating,
	.update_medium_grain_light_sleep = nbio_v7_4_update_medium_grain_light_sleep,
	.get_घड़ीgating_state = nbio_v7_4_get_घड़ीgating_state,
	.ih_control = nbio_v7_4_ih_control,
	.init_रेजिस्टरs = nbio_v7_4_init_रेजिस्टरs,
	.remap_hdp_रेजिस्टरs = nbio_v7_4_remap_hdp_रेजिस्टरs,
	.program_aspm =  nbio_v7_4_program_aspm,
पूर्ण;
