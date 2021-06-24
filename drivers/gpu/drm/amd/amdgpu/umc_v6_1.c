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
#समावेश "umc_v6_1.h"
#समावेश "amdgpu_ras.h"
#समावेश "amdgpu_umc.h"
#समावेश "amdgpu.h"

#समावेश "rsmu/rsmu_0_0_2_offset.h"
#समावेश "rsmu/rsmu_0_0_2_sh_mask.h"
#समावेश "umc/umc_6_1_1_offset.h"
#समावेश "umc/umc_6_1_1_sh_mask.h"
#समावेश "umc/umc_6_1_2_offset.h"

#घोषणा UMC_6_INST_DIST			0x40000

स्थिर uपूर्णांक32_t
	umc_v6_1_channel_idx_tbl[UMC_V6_1_UMC_INSTANCE_NUM][UMC_V6_1_CHANNEL_INSTANCE_NUM] = अणु
		अणु2, 18, 11, 27पूर्ण,	अणु4, 20, 13, 29पूर्ण,
		अणु1, 17, 8, 24पूर्ण,		अणु7, 23, 14, 30पूर्ण,
		अणु10, 26, 3, 19पूर्ण,	अणु12, 28, 5, 21पूर्ण,
		अणु9, 25, 0, 16पूर्ण,		अणु15, 31, 6, 22पूर्ण
पूर्ण;

अटल व्योम umc_v6_1_enable_umc_index_mode(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t rsmu_umc_addr, rsmu_umc_val;

	rsmu_umc_addr = SOC15_REG_OFFSET(RSMU, 0,
			mmRSMU_UMC_INDEX_REGISTER_NBIF_VG20_GPU);
	rsmu_umc_val = RREG32_PCIE(rsmu_umc_addr * 4);

	rsmu_umc_val = REG_SET_FIELD(rsmu_umc_val,
			RSMU_UMC_INDEX_REGISTER_NBIF_VG20_GPU,
			RSMU_UMC_INDEX_MODE_EN, 1);

	WREG32_PCIE(rsmu_umc_addr * 4, rsmu_umc_val);
पूर्ण

अटल व्योम umc_v6_1_disable_umc_index_mode(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t rsmu_umc_addr, rsmu_umc_val;

	rsmu_umc_addr = SOC15_REG_OFFSET(RSMU, 0,
			mmRSMU_UMC_INDEX_REGISTER_NBIF_VG20_GPU);
	rsmu_umc_val = RREG32_PCIE(rsmu_umc_addr * 4);

	rsmu_umc_val = REG_SET_FIELD(rsmu_umc_val,
			RSMU_UMC_INDEX_REGISTER_NBIF_VG20_GPU,
			RSMU_UMC_INDEX_MODE_EN, 0);

	WREG32_PCIE(rsmu_umc_addr * 4, rsmu_umc_val);
पूर्ण

अटल uपूर्णांक32_t umc_v6_1_get_umc_index_mode_state(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t rsmu_umc_addr, rsmu_umc_val;

	rsmu_umc_addr = SOC15_REG_OFFSET(RSMU, 0,
			mmRSMU_UMC_INDEX_REGISTER_NBIF_VG20_GPU);
	rsmu_umc_val = RREG32_PCIE(rsmu_umc_addr * 4);

	वापस REG_GET_FIELD(rsmu_umc_val,
			RSMU_UMC_INDEX_REGISTER_NBIF_VG20_GPU,
			RSMU_UMC_INDEX_MODE_EN);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t get_umc_6_reg_offset(काष्ठा amdgpu_device *adev,
					    uपूर्णांक32_t umc_inst,
					    uपूर्णांक32_t ch_inst)
अणु
	वापस adev->umc.channel_offs*ch_inst + UMC_6_INST_DIST*umc_inst;
पूर्ण

अटल व्योम umc_v6_1_clear_error_count_per_channel(काष्ठा amdgpu_device *adev,
					uपूर्णांक32_t umc_reg_offset)
अणु
	uपूर्णांक32_t ecc_err_cnt_addr;
	uपूर्णांक32_t ecc_err_cnt_sel, ecc_err_cnt_sel_addr;

	अगर (adev->asic_type == CHIP_ARCTURUS) अणु
		/* UMC 6_1_2 रेजिस्टरs */
		ecc_err_cnt_sel_addr =
			SOC15_REG_OFFSET(UMC, 0,
					mmUMCCH0_0_EccErrCntSel_ARCT);
		ecc_err_cnt_addr =
			SOC15_REG_OFFSET(UMC, 0,
					mmUMCCH0_0_EccErrCnt_ARCT);
	पूर्ण अन्यथा अणु
		/* UMC 6_1_1 रेजिस्टरs */
		ecc_err_cnt_sel_addr =
			SOC15_REG_OFFSET(UMC, 0,
					mmUMCCH0_0_EccErrCntSel);
		ecc_err_cnt_addr =
			SOC15_REG_OFFSET(UMC, 0,
					mmUMCCH0_0_EccErrCnt);
	पूर्ण

	/* select the lower chip */
	ecc_err_cnt_sel = RREG32_PCIE((ecc_err_cnt_sel_addr +
					umc_reg_offset) * 4);
	ecc_err_cnt_sel = REG_SET_FIELD(ecc_err_cnt_sel,
					UMCCH0_0_EccErrCntSel,
					EccErrCntCsSel, 0);
	WREG32_PCIE((ecc_err_cnt_sel_addr + umc_reg_offset) * 4,
			ecc_err_cnt_sel);

	/* clear lower chip error count */
	WREG32_PCIE((ecc_err_cnt_addr + umc_reg_offset) * 4,
			UMC_V6_1_CE_CNT_INIT);

	/* select the higher chip */
	ecc_err_cnt_sel = RREG32_PCIE((ecc_err_cnt_sel_addr +
					umc_reg_offset) * 4);
	ecc_err_cnt_sel = REG_SET_FIELD(ecc_err_cnt_sel,
					UMCCH0_0_EccErrCntSel,
					EccErrCntCsSel, 1);
	WREG32_PCIE((ecc_err_cnt_sel_addr + umc_reg_offset) * 4,
			ecc_err_cnt_sel);

	/* clear higher chip error count */
	WREG32_PCIE((ecc_err_cnt_addr + umc_reg_offset) * 4,
			UMC_V6_1_CE_CNT_INIT);
पूर्ण

अटल व्योम umc_v6_1_clear_error_count(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t umc_inst        = 0;
	uपूर्णांक32_t ch_inst         = 0;
	uपूर्णांक32_t umc_reg_offset  = 0;
	uपूर्णांक32_t rsmu_umc_index_state =
				umc_v6_1_get_umc_index_mode_state(adev);

	अगर (rsmu_umc_index_state)
		umc_v6_1_disable_umc_index_mode(adev);

	LOOP_UMC_INST_AND_CH(umc_inst, ch_inst) अणु
		umc_reg_offset = get_umc_6_reg_offset(adev,
						umc_inst,
						ch_inst);

		umc_v6_1_clear_error_count_per_channel(adev,
						umc_reg_offset);
	पूर्ण

	अगर (rsmu_umc_index_state)
		umc_v6_1_enable_umc_index_mode(adev);
पूर्ण

अटल व्योम umc_v6_1_query_correctable_error_count(काष्ठा amdgpu_device *adev,
						   uपूर्णांक32_t umc_reg_offset,
						   अचिन्हित दीर्घ *error_count)
अणु
	uपूर्णांक32_t ecc_err_cnt_sel, ecc_err_cnt_sel_addr;
	uपूर्णांक32_t ecc_err_cnt, ecc_err_cnt_addr;
	uपूर्णांक64_t mc_umc_status;
	uपूर्णांक32_t mc_umc_status_addr;

	अगर (adev->asic_type == CHIP_ARCTURUS) अणु
		/* UMC 6_1_2 रेजिस्टरs */
		ecc_err_cnt_sel_addr =
			SOC15_REG_OFFSET(UMC, 0, mmUMCCH0_0_EccErrCntSel_ARCT);
		ecc_err_cnt_addr =
			SOC15_REG_OFFSET(UMC, 0, mmUMCCH0_0_EccErrCnt_ARCT);
		mc_umc_status_addr =
			SOC15_REG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_STATUST0_ARCT);
	पूर्ण अन्यथा अणु
		/* UMC 6_1_1 रेजिस्टरs */
		ecc_err_cnt_sel_addr =
			SOC15_REG_OFFSET(UMC, 0, mmUMCCH0_0_EccErrCntSel);
		ecc_err_cnt_addr =
			SOC15_REG_OFFSET(UMC, 0, mmUMCCH0_0_EccErrCnt);
		mc_umc_status_addr =
			SOC15_REG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_STATUST0);
	पूर्ण

	/* select the lower chip and check the error count */
	ecc_err_cnt_sel = RREG32_PCIE((ecc_err_cnt_sel_addr + umc_reg_offset) * 4);
	ecc_err_cnt_sel = REG_SET_FIELD(ecc_err_cnt_sel, UMCCH0_0_EccErrCntSel,
					EccErrCntCsSel, 0);
	WREG32_PCIE((ecc_err_cnt_sel_addr + umc_reg_offset) * 4, ecc_err_cnt_sel);

	ecc_err_cnt = RREG32_PCIE((ecc_err_cnt_addr + umc_reg_offset) * 4);
	*error_count +=
		(REG_GET_FIELD(ecc_err_cnt, UMCCH0_0_EccErrCnt, EccErrCnt) -
		 UMC_V6_1_CE_CNT_INIT);

	/* select the higher chip and check the err counter */
	ecc_err_cnt_sel = REG_SET_FIELD(ecc_err_cnt_sel, UMCCH0_0_EccErrCntSel,
					EccErrCntCsSel, 1);
	WREG32_PCIE((ecc_err_cnt_sel_addr + umc_reg_offset) * 4, ecc_err_cnt_sel);

	ecc_err_cnt = RREG32_PCIE((ecc_err_cnt_addr + umc_reg_offset) * 4);
	*error_count +=
		(REG_GET_FIELD(ecc_err_cnt, UMCCH0_0_EccErrCnt, EccErrCnt) -
		 UMC_V6_1_CE_CNT_INIT);

	/* check क्रम SRAM correctable error
	  MCUMC_STATUS is a 64 bit रेजिस्टर */
	mc_umc_status = RREG64_PCIE((mc_umc_status_addr + umc_reg_offset) * 4);
	अगर (REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, ErrorCodeExt) == 6 &&
	    REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Val) == 1 &&
	    REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, CECC) == 1)
		*error_count += 1;
पूर्ण

अटल व्योम umc_v6_1_querry_uncorrectable_error_count(काष्ठा amdgpu_device *adev,
						      uपूर्णांक32_t umc_reg_offset,
						      अचिन्हित दीर्घ *error_count)
अणु
	uपूर्णांक64_t mc_umc_status;
	uपूर्णांक32_t mc_umc_status_addr;

	अगर (adev->asic_type == CHIP_ARCTURUS) अणु
		/* UMC 6_1_2 रेजिस्टरs */
		mc_umc_status_addr =
			SOC15_REG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_STATUST0_ARCT);
	पूर्ण अन्यथा अणु
		/* UMC 6_1_1 रेजिस्टरs */
		mc_umc_status_addr =
			SOC15_REG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_STATUST0);
	पूर्ण

	/* check the MCUMC_STATUS */
	mc_umc_status = RREG64_PCIE((mc_umc_status_addr + umc_reg_offset) * 4);
	अगर ((REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Val) == 1) &&
	    (REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Deferred) == 1 ||
	    REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UECC) == 1 ||
	    REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, PCC) == 1 ||
	    REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UC) == 1 ||
	    REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, TCC) == 1))
		*error_count += 1;
पूर्ण

अटल व्योम umc_v6_1_query_ras_error_count(काष्ठा amdgpu_device *adev,
					   व्योम *ras_error_status)
अणु
	काष्ठा ras_err_data *err_data = (काष्ठा ras_err_data *)ras_error_status;

	uपूर्णांक32_t umc_inst        = 0;
	uपूर्णांक32_t ch_inst         = 0;
	uपूर्णांक32_t umc_reg_offset  = 0;

	uपूर्णांक32_t rsmu_umc_index_state = umc_v6_1_get_umc_index_mode_state(adev);

	अगर (rsmu_umc_index_state)
		umc_v6_1_disable_umc_index_mode(adev);

	अगर ((adev->asic_type == CHIP_ARCTURUS) &&
		amdgpu_dpm_set_df_cstate(adev, DF_CSTATE_DISALLOW))
		DRM_WARN("Fail to disable DF-Cstate.\n");

	LOOP_UMC_INST_AND_CH(umc_inst, ch_inst) अणु
		umc_reg_offset = get_umc_6_reg_offset(adev,
						      umc_inst,
						      ch_inst);

		umc_v6_1_query_correctable_error_count(adev,
						       umc_reg_offset,
						       &(err_data->ce_count));
		umc_v6_1_querry_uncorrectable_error_count(adev,
							  umc_reg_offset,
							  &(err_data->ue_count));
	पूर्ण

	अगर ((adev->asic_type == CHIP_ARCTURUS) &&
		amdgpu_dpm_set_df_cstate(adev, DF_CSTATE_ALLOW))
		DRM_WARN("Fail to enable DF-Cstate\n");

	अगर (rsmu_umc_index_state)
		umc_v6_1_enable_umc_index_mode(adev);

	umc_v6_1_clear_error_count(adev);
पूर्ण

अटल व्योम umc_v6_1_query_error_address(काष्ठा amdgpu_device *adev,
					 काष्ठा ras_err_data *err_data,
					 uपूर्णांक32_t umc_reg_offset,
					 uपूर्णांक32_t ch_inst,
					 uपूर्णांक32_t umc_inst)
अणु
	uपूर्णांक32_t lsb, mc_umc_status_addr;
	uपूर्णांक64_t mc_umc_status, err_addr, retired_page, mc_umc_addrt0;
	काष्ठा eeprom_table_record *err_rec;
	uपूर्णांक32_t channel_index = adev->umc.channel_idx_tbl[umc_inst * adev->umc.channel_inst_num + ch_inst];

	अगर (adev->asic_type == CHIP_ARCTURUS) अणु
		/* UMC 6_1_2 रेजिस्टरs */
		mc_umc_status_addr =
			SOC15_REG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_STATUST0_ARCT);
		mc_umc_addrt0 =
			SOC15_REG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_ADDRT0_ARCT);
	पूर्ण अन्यथा अणु
		/* UMC 6_1_1 रेजिस्टरs */
		mc_umc_status_addr =
			SOC15_REG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_STATUST0);
		mc_umc_addrt0 =
			SOC15_REG_OFFSET(UMC, 0, mmMCA_UMC_UMC0_MCUMC_ADDRT0);
	पूर्ण

	mc_umc_status = RREG64_PCIE((mc_umc_status_addr + umc_reg_offset) * 4);

	अगर (mc_umc_status == 0)
		वापस;

	अगर (!err_data->err_addr) अणु
		/* clear umc status */
		WREG64_PCIE((mc_umc_status_addr + umc_reg_offset) * 4, 0x0ULL);
		वापस;
	पूर्ण

	err_rec = &err_data->err_addr[err_data->err_addr_cnt];

	/* calculate error address अगर ue/ce error is detected */
	अगर (REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, Val) == 1 &&
	    (REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UECC) == 1 ||
	    REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, CECC) == 1)) अणु

		err_addr = RREG64_PCIE((mc_umc_addrt0 + umc_reg_offset) * 4);
		/* the lowest lsb bits should be ignored */
		lsb = REG_GET_FIELD(err_addr, MCA_UMC_UMC0_MCUMC_ADDRT0, LSB);
		err_addr = REG_GET_FIELD(err_addr, MCA_UMC_UMC0_MCUMC_ADDRT0, ErrorAddr);
		err_addr &= ~((0x1ULL << lsb) - 1);

		/* translate umc channel address to soc pa, 3 parts are included */
		retired_page = ADDR_OF_8KB_BLOCK(err_addr) |
				ADDR_OF_256B_BLOCK(channel_index) |
				OFFSET_IN_256B_BLOCK(err_addr);

		/* we only save ue error inक्रमmation currently, ce is skipped */
		अगर (REG_GET_FIELD(mc_umc_status, MCA_UMC_UMC0_MCUMC_STATUST0, UECC)
				== 1) अणु
			err_rec->address = err_addr;
			/* page frame address is saved */
			err_rec->retired_page = retired_page >> AMDGPU_GPU_PAGE_SHIFT;
			err_rec->ts = (uपूर्णांक64_t)kसमय_get_real_seconds();
			err_rec->err_type = AMDGPU_RAS_EEPROM_ERR_NON_RECOVERABLE;
			err_rec->cu = 0;
			err_rec->mem_channel = channel_index;
			err_rec->mcumc_id = umc_inst;

			err_data->err_addr_cnt++;
		पूर्ण
	पूर्ण

	/* clear umc status */
	WREG64_PCIE((mc_umc_status_addr + umc_reg_offset) * 4, 0x0ULL);
पूर्ण

अटल व्योम umc_v6_1_query_ras_error_address(काष्ठा amdgpu_device *adev,
					     व्योम *ras_error_status)
अणु
	काष्ठा ras_err_data *err_data = (काष्ठा ras_err_data *)ras_error_status;

	uपूर्णांक32_t umc_inst        = 0;
	uपूर्णांक32_t ch_inst         = 0;
	uपूर्णांक32_t umc_reg_offset  = 0;

	uपूर्णांक32_t rsmu_umc_index_state = umc_v6_1_get_umc_index_mode_state(adev);

	अगर (rsmu_umc_index_state)
		umc_v6_1_disable_umc_index_mode(adev);

	अगर ((adev->asic_type == CHIP_ARCTURUS) &&
		amdgpu_dpm_set_df_cstate(adev, DF_CSTATE_DISALLOW))
		DRM_WARN("Fail to disable DF-Cstate.\n");

	LOOP_UMC_INST_AND_CH(umc_inst, ch_inst) अणु
		umc_reg_offset = get_umc_6_reg_offset(adev,
						      umc_inst,
						      ch_inst);

		umc_v6_1_query_error_address(adev,
					     err_data,
					     umc_reg_offset,
					     ch_inst,
					     umc_inst);
	पूर्ण

	अगर ((adev->asic_type == CHIP_ARCTURUS) &&
		amdgpu_dpm_set_df_cstate(adev, DF_CSTATE_ALLOW))
		DRM_WARN("Fail to enable DF-Cstate\n");

	अगर (rsmu_umc_index_state)
		umc_v6_1_enable_umc_index_mode(adev);
पूर्ण

अटल व्योम umc_v6_1_err_cnt_init_per_channel(काष्ठा amdgpu_device *adev,
					      uपूर्णांक32_t umc_reg_offset)
अणु
	uपूर्णांक32_t ecc_err_cnt_sel, ecc_err_cnt_sel_addr;
	uपूर्णांक32_t ecc_err_cnt_addr;

	अगर (adev->asic_type == CHIP_ARCTURUS) अणु
		/* UMC 6_1_2 रेजिस्टरs */
		ecc_err_cnt_sel_addr =
			SOC15_REG_OFFSET(UMC, 0, mmUMCCH0_0_EccErrCntSel_ARCT);
		ecc_err_cnt_addr =
			SOC15_REG_OFFSET(UMC, 0, mmUMCCH0_0_EccErrCnt_ARCT);
	पूर्ण अन्यथा अणु
		/* UMC 6_1_1 रेजिस्टरs */
		ecc_err_cnt_sel_addr =
			SOC15_REG_OFFSET(UMC, 0, mmUMCCH0_0_EccErrCntSel);
		ecc_err_cnt_addr =
			SOC15_REG_OFFSET(UMC, 0, mmUMCCH0_0_EccErrCnt);
	पूर्ण

	/* select the lower chip and check the error count */
	ecc_err_cnt_sel = RREG32_PCIE((ecc_err_cnt_sel_addr + umc_reg_offset) * 4);
	ecc_err_cnt_sel = REG_SET_FIELD(ecc_err_cnt_sel, UMCCH0_0_EccErrCntSel,
					EccErrCntCsSel, 0);
	/* set ce error पूर्णांकerrupt type to APIC based पूर्णांकerrupt */
	ecc_err_cnt_sel = REG_SET_FIELD(ecc_err_cnt_sel, UMCCH0_0_EccErrCntSel,
					EccErrInt, 0x1);
	WREG32_PCIE((ecc_err_cnt_sel_addr + umc_reg_offset) * 4, ecc_err_cnt_sel);
	/* set error count to initial value */
	WREG32_PCIE((ecc_err_cnt_addr + umc_reg_offset) * 4, UMC_V6_1_CE_CNT_INIT);

	/* select the higher chip and check the err counter */
	ecc_err_cnt_sel = REG_SET_FIELD(ecc_err_cnt_sel, UMCCH0_0_EccErrCntSel,
					EccErrCntCsSel, 1);
	WREG32_PCIE((ecc_err_cnt_sel_addr + umc_reg_offset) * 4, ecc_err_cnt_sel);
	WREG32_PCIE((ecc_err_cnt_addr + umc_reg_offset) * 4, UMC_V6_1_CE_CNT_INIT);
पूर्ण

अटल व्योम umc_v6_1_err_cnt_init(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t umc_inst        = 0;
	uपूर्णांक32_t ch_inst         = 0;
	uपूर्णांक32_t umc_reg_offset  = 0;

	uपूर्णांक32_t rsmu_umc_index_state = umc_v6_1_get_umc_index_mode_state(adev);

	अगर (rsmu_umc_index_state)
		umc_v6_1_disable_umc_index_mode(adev);

	LOOP_UMC_INST_AND_CH(umc_inst, ch_inst) अणु
		umc_reg_offset = get_umc_6_reg_offset(adev,
						      umc_inst,
						      ch_inst);

		umc_v6_1_err_cnt_init_per_channel(adev, umc_reg_offset);
	पूर्ण

	अगर (rsmu_umc_index_state)
		umc_v6_1_enable_umc_index_mode(adev);
पूर्ण

स्थिर काष्ठा amdgpu_umc_ras_funcs umc_v6_1_ras_funcs = अणु
	.err_cnt_init = umc_v6_1_err_cnt_init,
	.ras_late_init = amdgpu_umc_ras_late_init,
	.ras_fini = amdgpu_umc_ras_fini,
	.query_ras_error_count = umc_v6_1_query_ras_error_count,
	.query_ras_error_address = umc_v6_1_query_ras_error_address,
पूर्ण;
