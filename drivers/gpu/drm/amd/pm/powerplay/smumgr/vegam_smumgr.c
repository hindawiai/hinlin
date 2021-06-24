<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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
#समावेश "pp_debug.h"
#समावेश "smumgr.h"
#समावेश "smu_ucode_xfer_vi.h"
#समावेश "vegam_smumgr.h"
#समावेश "smu/smu_7_1_3_d.h"
#समावेश "smu/smu_7_1_3_sh_mask.h"
#समावेश "gmc/gmc_8_1_d.h"
#समावेश "gmc/gmc_8_1_sh_mask.h"
#समावेश "oss/oss_3_0_d.h"
#समावेश "gca/gfx_8_0_d.h"
#समावेश "bif/bif_5_0_d.h"
#समावेश "bif/bif_5_0_sh_mask.h"
#समावेश "ppatomctrl.h"
#समावेश "cgs_common.h"
#समावेश "smu7_ppsmc.h"

#समावेश "smu7_dyn_defaults.h"

#समावेश "smu7_hwmgr.h"
#समावेश "hardwaremanager.h"
#समावेश "atombios.h"
#समावेश "pppcielanes.h"

#समावेश "dce/dce_11_2_d.h"
#समावेश "dce/dce_11_2_sh_mask.h"

#घोषणा PPVEGAM_TARGETACTIVITY_DFLT                     50

#घोषणा VOLTAGE_VID_OFFSET_SCALE1   625
#घोषणा VOLTAGE_VID_OFFSET_SCALE2   100
#घोषणा POWERTUNE_DEFAULT_SET_MAX    1
#घोषणा VDDC_VDDCI_DELTA            200
#घोषणा MC_CG_ARB_FREQ_F1           0x0b

#घोषणा STRAP_ASIC_RO_LSB    2168
#घोषणा STRAP_ASIC_RO_MSB    2175

#घोषणा PPSMC_MSG_ApplyAvfsCksOffVoltage      ((uपूर्णांक16_t) 0x415)
#घोषणा PPSMC_MSG_EnableModeSwitchRLCNotअगरication  ((uपूर्णांक16_t) 0x305)

अटल स्थिर काष्ठा vegam_pt_शेषs
vegam_घातer_tune_data_set_array[POWERTUNE_DEFAULT_SET_MAX] = अणु
	/* sviLoadLIneEn, SviLoadLineVddC, TDC_VDDC_ThrottleReleaseLimitPerc, TDC_MAWt,
	 * TdcWaterfallCtl, DTEAmbientTempBase, DisplayCac, BAPM_TEMP_GRADIENT */
	अणु 1, 0xF, 0xFD, 0x19, 5, 45, 0, 0xB0000,
	अणु 0x79, 0x253, 0x25D, 0xAE, 0x72, 0x80, 0x83, 0x86, 0x6F, 0xC8, 0xC9, 0xC9, 0x2F, 0x4D, 0x61पूर्ण,
	अणु 0x17C, 0x172, 0x180, 0x1BC, 0x1B3, 0x1BD, 0x206, 0x200, 0x203, 0x25D, 0x25A, 0x255, 0x2C3, 0x2C5, 0x2B4 पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर sclkFcwRange_t Range_Table[NUM_SCLK_RANGE] = अणु
			अणुVCO_2_4, POSTDIV_DIV_BY_16,  75, 160, 112पूर्ण,
			अणुVCO_3_6, POSTDIV_DIV_BY_16, 112, 224, 160पूर्ण,
			अणुVCO_2_4, POSTDIV_DIV_BY_8,   75, 160, 112पूर्ण,
			अणुVCO_3_6, POSTDIV_DIV_BY_8,  112, 224, 160पूर्ण,
			अणुVCO_2_4, POSTDIV_DIV_BY_4,   75, 160, 112पूर्ण,
			अणुVCO_3_6, POSTDIV_DIV_BY_4,  112, 216, 160पूर्ण,
			अणुVCO_2_4, POSTDIV_DIV_BY_2,   75, 160, 108पूर्ण,
			अणुVCO_3_6, POSTDIV_DIV_BY_2,  112, 216, 160पूर्ण पूर्ण;

अटल पूर्णांक vegam_smu_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vegam_smumgr *smu_data;

	smu_data = kzalloc(माप(काष्ठा vegam_smumgr), GFP_KERNEL);
	अगर (smu_data == शून्य)
		वापस -ENOMEM;

	hwmgr->smu_backend = smu_data;

	अगर (smu7_init(hwmgr)) अणु
		kमुक्त(smu_data);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_start_smu_in_protection_mode(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;

	/* Wait क्रम smc boot up */
	/* PHM_WAIT_VFPF_INसूचीECT_FIELD_UNEQUAL(smumgr, SMC_IND, RCU_UC_EVENTS, boot_seq_करोne, 0) */

	/* Assert reset */
	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
					SMC_SYSCON_RESET_CNTL, rst_reg, 1);

	result = smu7_upload_smu_firmware_image(hwmgr);
	अगर (result != 0)
		वापस result;

	/* Clear status */
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixSMU_STATUS, 0);

	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
					SMC_SYSCON_CLOCK_CNTL_0, ck_disable, 0);

	/* De-निश्चित reset */
	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
					SMC_SYSCON_RESET_CNTL, rst_reg, 0);


	PHM_WAIT_VFPF_INसूचीECT_FIELD(hwmgr, SMC_IND, RCU_UC_EVENTS, INTERRUPTS_ENABLED, 1);


	/* Call Test SMU message with 0x20000 offset to trigger SMU start */
	smu7_send_msg_to_smc_offset(hwmgr);

	/* Wait करोne bit to be set */
	/* Check pass/failed indicator */

	PHM_WAIT_VFPF_INसूचीECT_FIELD_UNEQUAL(hwmgr, SMC_IND, SMU_STATUS, SMU_DONE, 0);

	अगर (1 != PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
						SMU_STATUS, SMU_PASS))
		PP_ASSERT_WITH_CODE(false, "SMU Firmware start failed!", वापस -1);

	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixFIRMWARE_FLAGS, 0);

	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
					SMC_SYSCON_RESET_CNTL, rst_reg, 1);

	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
					SMC_SYSCON_RESET_CNTL, rst_reg, 0);

	/* Wait क्रम firmware to initialize */
	PHM_WAIT_VFPF_INसूचीECT_FIELD(hwmgr, SMC_IND, FIRMWARE_FLAGS, INTERRUPTS_ENABLED, 1);

	वापस result;
पूर्ण

अटल पूर्णांक vegam_start_smu_in_non_protection_mode(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;

	/* रुको क्रम smc boot up */
	PHM_WAIT_VFPF_INसूचीECT_FIELD_UNEQUAL(hwmgr, SMC_IND, RCU_UC_EVENTS, boot_seq_करोne, 0);

	/* Clear firmware पूर्णांकerrupt enable flag */
	/* PHM_WRITE_VFPF_INसूचीECT_FIELD(pSmuMgr, SMC_IND, SMC_SYSCON_MISC_CNTL, pre_fetcher_en, 1); */
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
				ixFIRMWARE_FLAGS, 0);

	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
					SMC_SYSCON_RESET_CNTL,
					rst_reg, 1);

	result = smu7_upload_smu_firmware_image(hwmgr);
	अगर (result != 0)
		वापस result;

	/* Set smc inकाष्ठा start poपूर्णांक at 0x0 */
	smu7_program_jump_on_start(hwmgr);

	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
					SMC_SYSCON_CLOCK_CNTL_0, ck_disable, 0);

	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
					SMC_SYSCON_RESET_CNTL, rst_reg, 0);

	/* Wait क्रम firmware to initialize */

	PHM_WAIT_VFPF_INसूचीECT_FIELD(hwmgr, SMC_IND,
					FIRMWARE_FLAGS, INTERRUPTS_ENABLED, 1);

	वापस result;
पूर्ण

अटल पूर्णांक vegam_start_smu(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);

	/* Only start SMC अगर SMC RAM is not running */
	अगर (!smu7_is_smc_ram_running(hwmgr) && hwmgr->not_vf) अणु
		smu_data->रक्षित_mode = (uपूर्णांक8_t)(PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device,
				CGS_IND_REG__SMC, SMU_FIRMWARE, SMU_MODE));
		smu_data->smu7_data.security_hard_key = (uपूर्णांक8_t)(PHM_READ_VFPF_INसूचीECT_FIELD(
				hwmgr->device, CGS_IND_REG__SMC, SMU_FIRMWARE, SMU_SEL));

		/* Check अगर SMU is running in रक्षित mode */
		अगर (smu_data->रक्षित_mode == 0)
			result = vegam_start_smu_in_non_protection_mode(hwmgr);
		अन्यथा
			result = vegam_start_smu_in_protection_mode(hwmgr);

		अगर (result != 0)
			PP_ASSERT_WITH_CODE(0, "Failed to load SMU ucode.", वापस result);
	पूर्ण

	/* Setup SoftRegsStart here क्रम रेजिस्टर lookup in हाल DummyBackEnd is used and ProcessFirmwareHeader is not executed */
	smu7_पढ़ो_smc_sram_dword(hwmgr,
			SMU7_FIRMWARE_HEADER_LOCATION + दुरत्व(SMU75_Firmware_Header, SoftRegisters),
			&(smu_data->smu7_data.soft_regs_start),
			0x40000);

	result = smu7_request_smu_load_fw(hwmgr);

	वापस result;
पूर्ण

अटल पूर्णांक vegam_process_firmware_header(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t पंचांगp;
	पूर्णांक result;
	bool error = false;

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
			SMU7_FIRMWARE_HEADER_LOCATION +
			दुरत्व(SMU75_Firmware_Header, DpmTable),
			&पंचांगp, SMC_RAM_END);

	अगर (0 == result)
		smu_data->smu7_data.dpm_table_start = पंचांगp;

	error |= (0 != result);

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
			SMU7_FIRMWARE_HEADER_LOCATION +
			दुरत्व(SMU75_Firmware_Header, SoftRegisters),
			&पंचांगp, SMC_RAM_END);

	अगर (!result) अणु
		data->soft_regs_start = पंचांगp;
		smu_data->smu7_data.soft_regs_start = पंचांगp;
	पूर्ण

	error |= (0 != result);

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
			SMU7_FIRMWARE_HEADER_LOCATION +
			दुरत्व(SMU75_Firmware_Header, mcRegisterTable),
			&पंचांगp, SMC_RAM_END);

	अगर (!result)
		smu_data->smu7_data.mc_reg_table_start = पंचांगp;

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
			SMU7_FIRMWARE_HEADER_LOCATION +
			दुरत्व(SMU75_Firmware_Header, FanTable),
			&पंचांगp, SMC_RAM_END);

	अगर (!result)
		smu_data->smu7_data.fan_table_start = पंचांगp;

	error |= (0 != result);

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
			SMU7_FIRMWARE_HEADER_LOCATION +
			दुरत्व(SMU75_Firmware_Header, mcArbDramTimingTable),
			&पंचांगp, SMC_RAM_END);

	अगर (!result)
		smu_data->smu7_data.arb_table_start = पंचांगp;

	error |= (0 != result);

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
			SMU7_FIRMWARE_HEADER_LOCATION +
			दुरत्व(SMU75_Firmware_Header, Version),
			&पंचांगp, SMC_RAM_END);

	अगर (!result)
		hwmgr->microcode_version_info.SMC = पंचांगp;

	error |= (0 != result);

	वापस error ? -1 : 0;
पूर्ण

अटल bool vegam_is_dpm_running(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस (1 == PHM_READ_INसूचीECT_FIELD(hwmgr->device,
			CGS_IND_REG__SMC, FEATURE_STATUS, VOLTAGE_CONTROLLER_ON))
			? true : false;
पूर्ण

अटल uपूर्णांक32_t vegam_get_mac_definition(uपूर्णांक32_t value)
अणु
	चयन (value) अणु
	हाल SMU_MAX_LEVELS_GRAPHICS:
		वापस SMU75_MAX_LEVELS_GRAPHICS;
	हाल SMU_MAX_LEVELS_MEMORY:
		वापस SMU75_MAX_LEVELS_MEMORY;
	हाल SMU_MAX_LEVELS_LINK:
		वापस SMU75_MAX_LEVELS_LINK;
	हाल SMU_MAX_ENTRIES_SMIO:
		वापस SMU75_MAX_ENTRIES_SMIO;
	हाल SMU_MAX_LEVELS_VDDC:
		वापस SMU75_MAX_LEVELS_VDDC;
	हाल SMU_MAX_LEVELS_VDDGFX:
		वापस SMU75_MAX_LEVELS_VDDGFX;
	हाल SMU_MAX_LEVELS_VDDCI:
		वापस SMU75_MAX_LEVELS_VDDCI;
	हाल SMU_MAX_LEVELS_MVDD:
		वापस SMU75_MAX_LEVELS_MVDD;
	हाल SMU_UVD_MCLK_HANDSHAKE_DISABLE:
		वापस SMU7_UVD_MCLK_HANDSHAKE_DISABLE |
				SMU7_VCE_MCLK_HANDSHAKE_DISABLE;
	पूर्ण

	pr_warn("can't get the mac of %x\n", value);
	वापस 0;
पूर्ण

अटल पूर्णांक vegam_update_uvd_smc_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t mm_boot_level_offset, mm_boot_level_value;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	smu_data->smc_state_table.UvdBootLevel = 0;
	अगर (table_info->mm_dep_table->count > 0)
		smu_data->smc_state_table.UvdBootLevel =
				(uपूर्णांक8_t) (table_info->mm_dep_table->count - 1);
	mm_boot_level_offset = smu_data->smu7_data.dpm_table_start + दुरत्व(SMU75_Discrete_DpmTable,
						UvdBootLevel);
	mm_boot_level_offset /= 4;
	mm_boot_level_offset *= 4;
	mm_boot_level_value = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device,
			CGS_IND_REG__SMC, mm_boot_level_offset);
	mm_boot_level_value &= 0x00FFFFFF;
	mm_boot_level_value |= smu_data->smc_state_table.UvdBootLevel << 24;
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device,
			CGS_IND_REG__SMC, mm_boot_level_offset, mm_boot_level_value);

	अगर (!phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_UVDDPM) ||
		phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_StablePState))
		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_UVDDPM_SetEnabledMask,
				(uपूर्णांक32_t)(1 << smu_data->smc_state_table.UvdBootLevel),
				शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक vegam_update_vce_smc_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t mm_boot_level_offset, mm_boot_level_value;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_StablePState))
		smu_data->smc_state_table.VceBootLevel =
			(uपूर्णांक8_t) (table_info->mm_dep_table->count - 1);
	अन्यथा
		smu_data->smc_state_table.VceBootLevel = 0;

	mm_boot_level_offset = smu_data->smu7_data.dpm_table_start +
					दुरत्व(SMU75_Discrete_DpmTable, VceBootLevel);
	mm_boot_level_offset /= 4;
	mm_boot_level_offset *= 4;
	mm_boot_level_value = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device,
			CGS_IND_REG__SMC, mm_boot_level_offset);
	mm_boot_level_value &= 0xFF00FFFF;
	mm_boot_level_value |= smu_data->smc_state_table.VceBootLevel << 16;
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device,
			CGS_IND_REG__SMC, mm_boot_level_offset, mm_boot_level_value);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_StablePState))
		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_VCEDPM_SetEnabledMask,
				(uपूर्णांक32_t)1 << smu_data->smc_state_table.VceBootLevel,
				शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक vegam_update_bअगर_smc_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_pcie_table *pcie_table = table_info->pcie_table;
	पूर्णांक max_entry, i;

	max_entry = (SMU75_MAX_LEVELS_LINK < pcie_table->count) ?
						SMU75_MAX_LEVELS_LINK :
						pcie_table->count;
	/* Setup BIF_SCLK levels */
	क्रम (i = 0; i < max_entry; i++)
		smu_data->bअगर_sclk_table[i] = pcie_table->entries[i].pcie_sclk;
	वापस 0;
पूर्ण

अटल पूर्णांक vegam_update_smc_table(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t type)
अणु
	चयन (type) अणु
	हाल SMU_UVD_TABLE:
		vegam_update_uvd_smc_table(hwmgr);
		अवरोध;
	हाल SMU_VCE_TABLE:
		vegam_update_vce_smc_table(hwmgr);
		अवरोध;
	हाल SMU_BIF_TABLE:
		vegam_update_bअगर_smc_table(hwmgr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम vegam_initialize_घातer_tune_शेषs(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	काष्ठा  phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा  phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	अगर (table_info &&
			table_info->cac_dtp_table->usPowerTuneDataSetID <= POWERTUNE_DEFAULT_SET_MAX &&
			table_info->cac_dtp_table->usPowerTuneDataSetID)
		smu_data->घातer_tune_शेषs =
				&vegam_घातer_tune_data_set_array
				[table_info->cac_dtp_table->usPowerTuneDataSetID - 1];
	अन्यथा
		smu_data->घातer_tune_शेषs = &vegam_घातer_tune_data_set_array[0];

पूर्ण

अटल पूर्णांक vegam_populate_smc_mvdd_table(काष्ठा pp_hwmgr *hwmgr,
			SMU75_Discrete_DpmTable *table)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t count, level;

	अगर (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->mvdd_control) अणु
		count = data->mvdd_voltage_table.count;
		अगर (count > SMU_MAX_SMIO_LEVELS)
			count = SMU_MAX_SMIO_LEVELS;
		क्रम (level = 0; level < count; level++) अणु
			table->SmioTable2.Pattern[level].Voltage = PP_HOST_TO_SMC_US(
					data->mvdd_voltage_table.entries[level].value * VOLTAGE_SCALE);
			/* Index पूर्णांकo DpmTable.Smio. Drive bits from Smio entry to get this voltage level.*/
			table->SmioTable2.Pattern[level].Smio =
				(uपूर्णांक8_t) level;
			table->Smio[level] |=
				data->mvdd_voltage_table.entries[level].smio_low;
		पूर्ण
		table->SmioMask2 = data->mvdd_voltage_table.mask_low;

		table->MvddLevelCount = (uपूर्णांक32_t) PP_HOST_TO_SMC_UL(count);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_smc_vddci_table(काष्ठा pp_hwmgr *hwmgr,
					काष्ठा SMU75_Discrete_DpmTable *table)
अणु
	uपूर्णांक32_t count, level;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	count = data->vddci_voltage_table.count;

	अगर (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->vddci_control) अणु
		अगर (count > SMU_MAX_SMIO_LEVELS)
			count = SMU_MAX_SMIO_LEVELS;
		क्रम (level = 0; level < count; ++level) अणु
			table->SmioTable1.Pattern[level].Voltage = PP_HOST_TO_SMC_US(
					data->vddci_voltage_table.entries[level].value * VOLTAGE_SCALE);
			table->SmioTable1.Pattern[level].Smio = (uपूर्णांक8_t) level;

			table->Smio[level] |= data->vddci_voltage_table.entries[level].smio_low;
		पूर्ण
	पूर्ण

	table->SmioMask1 = data->vddci_voltage_table.mask_low;

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_cac_table(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU75_Discrete_DpmTable *table)
अणु
	uपूर्णांक32_t count;
	uपूर्णांक8_t index;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_voltage_lookup_table *lookup_table =
			table_info->vddc_lookup_table;
	/* tables is alपढ़ोy swapped, so in order to use the value from it,
	 * we need to swap it back.
	 * We are populating vddc CAC data to BapmVddc table
	 * in split and merged mode
	 */
	क्रम (count = 0; count < lookup_table->count; count++) अणु
		index = phm_get_voltage_index(lookup_table,
				data->vddc_voltage_table.entries[count].value);
		table->BapmVddcVidLoSidd[count] =
				convert_to_vid(lookup_table->entries[index].us_cac_low);
		table->BapmVddcVidHiSidd[count] =
				convert_to_vid(lookup_table->entries[index].us_cac_mid);
		table->BapmVddcVidHiSidd2[count] =
				convert_to_vid(lookup_table->entries[index].us_cac_high);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_smc_voltage_tables(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU75_Discrete_DpmTable *table)
अणु
	vegam_populate_smc_vddci_table(hwmgr, table);
	vegam_populate_smc_mvdd_table(hwmgr, table);
	vegam_populate_cac_table(hwmgr, table);

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_ulv_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU75_Discrete_Ulv *state)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	state->CcPwrDynRm = 0;
	state->CcPwrDynRm1 = 0;

	state->VddcOffset = (uपूर्णांक16_t) table_info->us_ulv_voltage_offset;
	state->VddcOffsetVid = (uपूर्णांक8_t)(table_info->us_ulv_voltage_offset *
			VOLTAGE_VID_OFFSET_SCALE2 / VOLTAGE_VID_OFFSET_SCALE1);

	state->VddcPhase = data->vddc_phase_shed_control ^ 0x3;

	CONVERT_FROM_HOST_TO_SMC_UL(state->CcPwrDynRm);
	CONVERT_FROM_HOST_TO_SMC_UL(state->CcPwrDynRm1);
	CONVERT_FROM_HOST_TO_SMC_US(state->VddcOffset);

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_ulv_state(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU75_Discrete_DpmTable *table)
अणु
	वापस vegam_populate_ulv_level(hwmgr, &table->Ulv);
पूर्ण

अटल पूर्णांक vegam_populate_smc_link_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU75_Discrete_DpmTable *table)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा vegam_smumgr *smu_data =
			(काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	काष्ठा smu7_dpm_table *dpm_table = &data->dpm_table;
	पूर्णांक i;

	/* Index (dpm_table->pcie_speed_table.count)
	 * is reserved क्रम PCIE boot level. */
	क्रम (i = 0; i <= dpm_table->pcie_speed_table.count; i++) अणु
		table->LinkLevel[i].PcieGenSpeed  =
				(uपूर्णांक8_t)dpm_table->pcie_speed_table.dpm_levels[i].value;
		table->LinkLevel[i].PcieLaneCount = (uपूर्णांक8_t)encode_pcie_lane_width(
				dpm_table->pcie_speed_table.dpm_levels[i].param1);
		table->LinkLevel[i].EnabledForActivity = 1;
		table->LinkLevel[i].SPC = (uपूर्णांक8_t)(data->pcie_spc_cap & 0xff);
		table->LinkLevel[i].DownThreshold = PP_HOST_TO_SMC_UL(5);
		table->LinkLevel[i].UpThreshold = PP_HOST_TO_SMC_UL(30);
	पूर्ण

	smu_data->smc_state_table.LinkLevelCount =
			(uपूर्णांक8_t)dpm_table->pcie_speed_table.count;

/* To Do move to hwmgr */
	data->dpm_level_enable_mask.pcie_dpm_enable_mask =
			phm_get_dpm_level_enable_mask_value(&dpm_table->pcie_speed_table);

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_get_dependency_volt_by_clk(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table,
		uपूर्णांक32_t घड़ी, SMU_VoltageLevel *voltage, uपूर्णांक32_t *mvdd)
अणु
	uपूर्णांक32_t i;
	uपूर्णांक16_t vddci;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	*voltage = *mvdd = 0;

	/* घड़ी - voltage dependency table is empty table */
	अगर (dep_table->count == 0)
		वापस -EINVAL;

	क्रम (i = 0; i < dep_table->count; i++) अणु
		/* find first sclk bigger than request */
		अगर (dep_table->entries[i].clk >= घड़ी) अणु
			*voltage |= (dep_table->entries[i].vddc *
					VOLTAGE_SCALE) << VDDC_SHIFT;
			अगर (SMU7_VOLTAGE_CONTROL_NONE == data->vddci_control)
				*voltage |= (data->vbios_boot_state.vddci_bootup_value *
						VOLTAGE_SCALE) << VDDCI_SHIFT;
			अन्यथा अगर (dep_table->entries[i].vddci)
				*voltage |= (dep_table->entries[i].vddci *
						VOLTAGE_SCALE) << VDDCI_SHIFT;
			अन्यथा अणु
				vddci = phm_find_बंदst_vddci(&(data->vddci_voltage_table),
						(dep_table->entries[i].vddc -
								(uपूर्णांक16_t)VDDC_VDDCI_DELTA));
				*voltage |= (vddci * VOLTAGE_SCALE) << VDDCI_SHIFT;
			पूर्ण

			अगर (SMU7_VOLTAGE_CONTROL_NONE == data->mvdd_control)
				*mvdd = data->vbios_boot_state.mvdd_bootup_value *
					VOLTAGE_SCALE;
			अन्यथा अगर (dep_table->entries[i].mvdd)
				*mvdd = (uपूर्णांक32_t) dep_table->entries[i].mvdd *
					VOLTAGE_SCALE;

			*voltage |= 1 << PHASES_SHIFT;
			वापस 0;
		पूर्ण
	पूर्ण

	/* sclk is bigger than max sclk in the dependence table */
	*voltage |= (dep_table->entries[i - 1].vddc * VOLTAGE_SCALE) << VDDC_SHIFT;

	अगर (SMU7_VOLTAGE_CONTROL_NONE == data->vddci_control)
		*voltage |= (data->vbios_boot_state.vddci_bootup_value *
				VOLTAGE_SCALE) << VDDCI_SHIFT;
	अन्यथा अगर (dep_table->entries[i - 1].vddci)
		*voltage |= (dep_table->entries[i - 1].vddci *
				VOLTAGE_SCALE) << VDDC_SHIFT;
	अन्यथा अणु
		vddci = phm_find_बंदst_vddci(&(data->vddci_voltage_table),
				(dep_table->entries[i - 1].vddc -
						(uपूर्णांक16_t)VDDC_VDDCI_DELTA));

		*voltage |= (vddci * VOLTAGE_SCALE) << VDDCI_SHIFT;
	पूर्ण

	अगर (SMU7_VOLTAGE_CONTROL_NONE == data->mvdd_control)
		*mvdd = data->vbios_boot_state.mvdd_bootup_value * VOLTAGE_SCALE;
	अन्यथा अगर (dep_table->entries[i].mvdd)
		*mvdd = (uपूर्णांक32_t) dep_table->entries[i - 1].mvdd * VOLTAGE_SCALE;

	वापस 0;
पूर्ण

अटल व्योम vegam_get_sclk_range_table(काष्ठा pp_hwmgr *hwmgr,
				   SMU75_Discrete_DpmTable  *table)
अणु
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t i, ref_clk;

	काष्ठा pp_atom_ctrl_sclk_range_table range_table_from_vbios = अणु अणु अणु0पूर्ण पूर्ण पूर्ण;

	ref_clk = amdgpu_asic_get_xclk((काष्ठा amdgpu_device *)hwmgr->adev);

	अगर (0 == atomctrl_get_smc_sclk_range_table(hwmgr, &range_table_from_vbios)) अणु
		क्रम (i = 0; i < NUM_SCLK_RANGE; i++) अणु
			table->SclkFcwRangeTable[i].vco_setting =
					range_table_from_vbios.entry[i].ucVco_setting;
			table->SclkFcwRangeTable[i].postभाग =
					range_table_from_vbios.entry[i].ucPostभाग;
			table->SclkFcwRangeTable[i].fcw_pcc =
					range_table_from_vbios.entry[i].usFcw_pcc;

			table->SclkFcwRangeTable[i].fcw_trans_upper =
					range_table_from_vbios.entry[i].usFcw_trans_upper;
			table->SclkFcwRangeTable[i].fcw_trans_lower =
					range_table_from_vbios.entry[i].usRcw_trans_lower;

			CONVERT_FROM_HOST_TO_SMC_US(table->SclkFcwRangeTable[i].fcw_pcc);
			CONVERT_FROM_HOST_TO_SMC_US(table->SclkFcwRangeTable[i].fcw_trans_upper);
			CONVERT_FROM_HOST_TO_SMC_US(table->SclkFcwRangeTable[i].fcw_trans_lower);
		पूर्ण
		वापस;
	पूर्ण

	क्रम (i = 0; i < NUM_SCLK_RANGE; i++) अणु
		smu_data->range_table[i].trans_lower_frequency =
				(ref_clk * Range_Table[i].fcw_trans_lower) >> Range_Table[i].postभाग;
		smu_data->range_table[i].trans_upper_frequency =
				(ref_clk * Range_Table[i].fcw_trans_upper) >> Range_Table[i].postभाग;

		table->SclkFcwRangeTable[i].vco_setting = Range_Table[i].vco_setting;
		table->SclkFcwRangeTable[i].postभाग = Range_Table[i].postभाग;
		table->SclkFcwRangeTable[i].fcw_pcc = Range_Table[i].fcw_pcc;

		table->SclkFcwRangeTable[i].fcw_trans_upper = Range_Table[i].fcw_trans_upper;
		table->SclkFcwRangeTable[i].fcw_trans_lower = Range_Table[i].fcw_trans_lower;

		CONVERT_FROM_HOST_TO_SMC_US(table->SclkFcwRangeTable[i].fcw_pcc);
		CONVERT_FROM_HOST_TO_SMC_US(table->SclkFcwRangeTable[i].fcw_trans_upper);
		CONVERT_FROM_HOST_TO_SMC_US(table->SclkFcwRangeTable[i].fcw_trans_lower);
	पूर्ण
पूर्ण

अटल पूर्णांक vegam_calculate_sclk_params(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी, SMU_SclkSetting *sclk_setting)
अणु
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	स्थिर SMU75_Discrete_DpmTable *table = &(smu_data->smc_state_table);
	काष्ठा pp_atomctrl_घड़ी_भागiders_ai भागiders;
	uपूर्णांक32_t ref_घड़ी;
	uपूर्णांक32_t pcc_target_percent, pcc_target_freq, ss_target_percent, ss_target_freq;
	uपूर्णांक8_t i;
	पूर्णांक result;
	uपूर्णांक64_t temp;

	sclk_setting->SclkFrequency = घड़ी;
	/* get the engine घड़ी भागiders क्रम this घड़ी value */
	result = atomctrl_get_engine_pll_भागiders_ai(hwmgr, घड़ी,  &भागiders);
	अगर (result == 0) अणु
		sclk_setting->Fcw_पूर्णांक = भागiders.usSclk_fcw_पूर्णांक;
		sclk_setting->Fcw_frac = भागiders.usSclk_fcw_frac;
		sclk_setting->Pcc_fcw_पूर्णांक = भागiders.usPcc_fcw_पूर्णांक;
		sclk_setting->PllRange = भागiders.ucSclkPllRange;
		sclk_setting->Sclk_slew_rate = 0x400;
		sclk_setting->Pcc_up_slew_rate = भागiders.usPcc_fcw_slew_frac;
		sclk_setting->Pcc_करोwn_slew_rate = 0xffff;
		sclk_setting->SSc_En = भागiders.ucSscEnable;
		sclk_setting->Fcw1_पूर्णांक = भागiders.usSsc_fcw1_पूर्णांक;
		sclk_setting->Fcw1_frac = भागiders.usSsc_fcw1_frac;
		sclk_setting->Sclk_ss_slew_rate = भागiders.usSsc_fcw_slew_frac;
		वापस result;
	पूर्ण

	ref_घड़ी = amdgpu_asic_get_xclk((काष्ठा amdgpu_device *)hwmgr->adev);

	क्रम (i = 0; i < NUM_SCLK_RANGE; i++) अणु
		अगर (घड़ी > smu_data->range_table[i].trans_lower_frequency
		&& घड़ी <= smu_data->range_table[i].trans_upper_frequency) अणु
			sclk_setting->PllRange = i;
			अवरोध;
		पूर्ण
	पूर्ण

	sclk_setting->Fcw_पूर्णांक = (uपूर्णांक16_t)
			((घड़ी << table->SclkFcwRangeTable[sclk_setting->PllRange].postभाग) /
					ref_घड़ी);
	temp = घड़ी << table->SclkFcwRangeTable[sclk_setting->PllRange].postभाग;
	temp <<= 0x10;
	करो_भाग(temp, ref_घड़ी);
	sclk_setting->Fcw_frac = temp & 0xffff;

	pcc_target_percent = 10; /*  Hardcode 10% क्रम now. */
	pcc_target_freq = घड़ी - (घड़ी * pcc_target_percent / 100);
	sclk_setting->Pcc_fcw_पूर्णांक = (uपूर्णांक16_t)
			((pcc_target_freq << table->SclkFcwRangeTable[sclk_setting->PllRange].postभाग) /
					ref_घड़ी);

	ss_target_percent = 2; /*  Hardcode 2% क्रम now. */
	sclk_setting->SSc_En = 0;
	अगर (ss_target_percent) अणु
		sclk_setting->SSc_En = 1;
		ss_target_freq = घड़ी - (घड़ी * ss_target_percent / 100);
		sclk_setting->Fcw1_पूर्णांक = (uपूर्णांक16_t)
				((ss_target_freq << table->SclkFcwRangeTable[sclk_setting->PllRange].postभाग) /
						ref_घड़ी);
		temp = ss_target_freq << table->SclkFcwRangeTable[sclk_setting->PllRange].postभाग;
		temp <<= 0x10;
		करो_भाग(temp, ref_घड़ी);
		sclk_setting->Fcw1_frac = temp & 0xffff;
	पूर्ण

	वापस 0;
पूर्ण

अटल uपूर्णांक8_t vegam_get_sleep_भागider_id_from_घड़ी(uपूर्णांक32_t घड़ी,
		uपूर्णांक32_t घड़ी_insr)
अणु
	uपूर्णांक8_t i;
	uपूर्णांक32_t temp;
	uपूर्णांक32_t min = max(घड़ी_insr, (uपूर्णांक32_t)SMU7_MINIMUM_ENGINE_CLOCK);

	PP_ASSERT_WITH_CODE((घड़ी >= min),
			"Engine clock can't satisfy stutter requirement!",
			वापस 0);
	क्रम (i = 31;  ; i--) अणु
		temp = घड़ी / (i + 1);

		अगर (temp >= min || i == 0)
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

अटल पूर्णांक vegam_populate_single_graphic_level(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी, काष्ठा SMU75_Discrete_GraphicsLevel *level)
अणु
	पूर्णांक result;
	/* PP_Clocks minClocks; */
	uपूर्णांक32_t mvdd;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	SMU_SclkSetting curr_sclk_setting = अणु 0 पूर्ण;

	result = vegam_calculate_sclk_params(hwmgr, घड़ी, &curr_sclk_setting);

	/* populate graphics levels */
	result = vegam_get_dependency_volt_by_clk(hwmgr,
			table_info->vdd_dep_on_sclk, घड़ी,
			&level->MinVoltage, &mvdd);

	PP_ASSERT_WITH_CODE((0 == result),
			"can not find VDDC voltage value for "
			"VDDC engine clock dependency table",
			वापस result);
	level->ActivityLevel = (uपूर्णांक16_t)(SclkDPMTuning_VEGAM >> DPMTuning_Activity_Shअगरt);

	level->CcPwrDynRm = 0;
	level->CcPwrDynRm1 = 0;
	level->EnabledForActivity = 0;
	level->EnabledForThrottle = 1;
	level->VoltageDownHyst = 0;
	level->PowerThrottle = 0;
	data->display_timing.min_घड़ी_in_sr = hwmgr->display_config->min_core_set_घड़ी_in_sr;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_SclkDeepSleep))
		level->DeepSleepDivId = vegam_get_sleep_भागider_id_from_घड़ी(घड़ी,
								hwmgr->display_config->min_core_set_घड़ी_in_sr);

	level->SclkSetting = curr_sclk_setting;

	CONVERT_FROM_HOST_TO_SMC_UL(level->MinVoltage);
	CONVERT_FROM_HOST_TO_SMC_UL(level->CcPwrDynRm);
	CONVERT_FROM_HOST_TO_SMC_UL(level->CcPwrDynRm1);
	CONVERT_FROM_HOST_TO_SMC_US(level->ActivityLevel);
	CONVERT_FROM_HOST_TO_SMC_UL(level->SclkSetting.SclkFrequency);
	CONVERT_FROM_HOST_TO_SMC_US(level->SclkSetting.Fcw_पूर्णांक);
	CONVERT_FROM_HOST_TO_SMC_US(level->SclkSetting.Fcw_frac);
	CONVERT_FROM_HOST_TO_SMC_US(level->SclkSetting.Pcc_fcw_पूर्णांक);
	CONVERT_FROM_HOST_TO_SMC_US(level->SclkSetting.Sclk_slew_rate);
	CONVERT_FROM_HOST_TO_SMC_US(level->SclkSetting.Pcc_up_slew_rate);
	CONVERT_FROM_HOST_TO_SMC_US(level->SclkSetting.Pcc_करोwn_slew_rate);
	CONVERT_FROM_HOST_TO_SMC_US(level->SclkSetting.Fcw1_पूर्णांक);
	CONVERT_FROM_HOST_TO_SMC_US(level->SclkSetting.Fcw1_frac);
	CONVERT_FROM_HOST_TO_SMC_US(level->SclkSetting.Sclk_ss_slew_rate);
	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_all_graphic_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *hw_data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	काष्ठा smu7_dpm_table *dpm_table = &hw_data->dpm_table;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_pcie_table *pcie_table = table_info->pcie_table;
	uपूर्णांक8_t pcie_entry_cnt = (uपूर्णांक8_t) hw_data->dpm_table.pcie_speed_table.count;
	पूर्णांक result = 0;
	uपूर्णांक32_t array = smu_data->smu7_data.dpm_table_start +
			दुरत्व(SMU75_Discrete_DpmTable, GraphicsLevel);
	uपूर्णांक32_t array_size = माप(काष्ठा SMU75_Discrete_GraphicsLevel) *
			SMU75_MAX_LEVELS_GRAPHICS;
	काष्ठा SMU75_Discrete_GraphicsLevel *levels =
			smu_data->smc_state_table.GraphicsLevel;
	uपूर्णांक32_t i, max_entry;
	uपूर्णांक8_t hightest_pcie_level_enabled = 0,
		lowest_pcie_level_enabled = 0,
		mid_pcie_level_enabled = 0,
		count = 0;

	vegam_get_sclk_range_table(hwmgr, &(smu_data->smc_state_table));

	क्रम (i = 0; i < dpm_table->sclk_table.count; i++) अणु

		result = vegam_populate_single_graphic_level(hwmgr,
				dpm_table->sclk_table.dpm_levels[i].value,
				&(smu_data->smc_state_table.GraphicsLevel[i]));
		अगर (result)
			वापस result;

		levels[i].UpHyst = (uपूर्णांक8_t)
				(SclkDPMTuning_VEGAM >> DPMTuning_Uphyst_Shअगरt);
		levels[i].DownHyst = (uपूर्णांक8_t)
				(SclkDPMTuning_VEGAM >> DPMTuning_Downhyst_Shअगरt);
		/* Making sure only DPM level 0-1 have Deep Sleep Div ID populated. */
		अगर (i > 1)
			levels[i].DeepSleepDivId = 0;
	पूर्ण
	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_SPLLShutकरोwnSupport))
		smu_data->smc_state_table.GraphicsLevel[0].SclkSetting.SSc_En = 0;

	smu_data->smc_state_table.GraphicsDpmLevelCount =
			(uपूर्णांक8_t)dpm_table->sclk_table.count;
	hw_data->dpm_level_enable_mask.sclk_dpm_enable_mask =
			phm_get_dpm_level_enable_mask_value(&dpm_table->sclk_table);

	क्रम (i = 0; i < dpm_table->sclk_table.count; i++)
		levels[i].EnabledForActivity =
				(hw_data->dpm_level_enable_mask.sclk_dpm_enable_mask >> i) & 0x1;

	अगर (pcie_table != शून्य) अणु
		PP_ASSERT_WITH_CODE((1 <= pcie_entry_cnt),
				"There must be 1 or more PCIE levels defined in PPTable.",
				वापस -EINVAL);
		max_entry = pcie_entry_cnt - 1;
		क्रम (i = 0; i < dpm_table->sclk_table.count; i++)
			levels[i].pcieDpmLevel =
					(uपूर्णांक8_t) ((i < max_entry) ? i : max_entry);
	पूर्ण अन्यथा अणु
		जबतक (hw_data->dpm_level_enable_mask.pcie_dpm_enable_mask &&
				((hw_data->dpm_level_enable_mask.pcie_dpm_enable_mask &
						(1 << (hightest_pcie_level_enabled + 1))) != 0))
			hightest_pcie_level_enabled++;

		जबतक (hw_data->dpm_level_enable_mask.pcie_dpm_enable_mask &&
				((hw_data->dpm_level_enable_mask.pcie_dpm_enable_mask &
						(1 << lowest_pcie_level_enabled)) == 0))
			lowest_pcie_level_enabled++;

		जबतक ((count < hightest_pcie_level_enabled) &&
				((hw_data->dpm_level_enable_mask.pcie_dpm_enable_mask &
						(1 << (lowest_pcie_level_enabled + 1 + count))) == 0))
			count++;

		mid_pcie_level_enabled = (lowest_pcie_level_enabled + 1 + count) <
				hightest_pcie_level_enabled ?
						(lowest_pcie_level_enabled + 1 + count) :
						hightest_pcie_level_enabled;

		/* set pcieDpmLevel to hightest_pcie_level_enabled */
		क्रम (i = 2; i < dpm_table->sclk_table.count; i++)
			levels[i].pcieDpmLevel = hightest_pcie_level_enabled;

		/* set pcieDpmLevel to lowest_pcie_level_enabled */
		levels[0].pcieDpmLevel = lowest_pcie_level_enabled;

		/* set pcieDpmLevel to mid_pcie_level_enabled */
		levels[1].pcieDpmLevel = mid_pcie_level_enabled;
	पूर्ण
	/* level count will send to smc once at init smc table and never change */
	result = smu7_copy_bytes_to_smc(hwmgr, array, (uपूर्णांक8_t *)levels,
			(uपूर्णांक32_t)array_size, SMC_RAM_END);

	वापस result;
पूर्ण

अटल पूर्णांक vegam_calculate_mclk_params(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी, काष्ठा SMU75_Discrete_MemoryLevel *mem_level)
अणु
	काष्ठा pp_atomctrl_memory_घड़ी_param_ai mpll_param;

	PP_ASSERT_WITH_CODE(!atomctrl_get_memory_pll_भागiders_ai(hwmgr,
			घड़ी, &mpll_param),
			"Failed to retrieve memory pll parameter.",
			वापस -EINVAL);

	mem_level->MclkFrequency = (uपूर्णांक32_t)mpll_param.ulClock;
	mem_level->Fcw_पूर्णांक = (uपूर्णांक16_t)mpll_param.ulMclk_fcw_पूर्णांक;
	mem_level->Fcw_frac = (uपूर्णांक16_t)mpll_param.ulMclk_fcw_frac;
	mem_level->Postभाग = (uपूर्णांक8_t)mpll_param.ulPostDiv;

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_single_memory_level(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी, काष्ठा SMU75_Discrete_MemoryLevel *mem_level)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	पूर्णांक result = 0;
	uपूर्णांक32_t mclk_stutter_mode_threshold = 60000;


	अगर (table_info->vdd_dep_on_mclk) अणु
		result = vegam_get_dependency_volt_by_clk(hwmgr,
				table_info->vdd_dep_on_mclk, घड़ी,
				&mem_level->MinVoltage, &mem_level->MinMvdd);
		PP_ASSERT_WITH_CODE(!result,
				"can not find MinVddc voltage value from memory "
				"VDDC voltage dependency table", वापस result);
	पूर्ण

	result = vegam_calculate_mclk_params(hwmgr, घड़ी, mem_level);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to calculate mclk params.",
			वापस -EINVAL);

	mem_level->EnabledForThrottle = 1;
	mem_level->EnabledForActivity = 0;
	mem_level->VoltageDownHyst = 0;
	mem_level->ActivityLevel = (uपूर्णांक16_t)
			(MemoryDPMTuning_VEGAM >> DPMTuning_Activity_Shअगरt);
	mem_level->StutterEnable = false;
	mem_level->DisplayWatermark = PPSMC_DISPLAY_WATERMARK_LOW;

	data->display_timing.num_existing_displays = hwmgr->display_config->num_display;
	data->display_timing.vrefresh = hwmgr->display_config->vrefresh;

	अगर (mclk_stutter_mode_threshold &&
		(घड़ी <= mclk_stutter_mode_threshold) &&
		(PHM_READ_FIELD(hwmgr->device, DPG_PIPE_STUTTER_CONTROL,
				STUTTER_ENABLE) & 0x1))
		mem_level->StutterEnable = true;

	अगर (!result) अणु
		CONVERT_FROM_HOST_TO_SMC_UL(mem_level->MinMvdd);
		CONVERT_FROM_HOST_TO_SMC_UL(mem_level->MclkFrequency);
		CONVERT_FROM_HOST_TO_SMC_US(mem_level->Fcw_पूर्णांक);
		CONVERT_FROM_HOST_TO_SMC_US(mem_level->Fcw_frac);
		CONVERT_FROM_HOST_TO_SMC_US(mem_level->ActivityLevel);
		CONVERT_FROM_HOST_TO_SMC_UL(mem_level->MinVoltage);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक vegam_populate_all_memory_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *hw_data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	काष्ठा smu7_dpm_table *dpm_table = &hw_data->dpm_table;
	पूर्णांक result;
	/* populate MCLK dpm table to SMU7 */
	uपूर्णांक32_t array = smu_data->smu7_data.dpm_table_start +
			दुरत्व(SMU75_Discrete_DpmTable, MemoryLevel);
	uपूर्णांक32_t array_size = माप(SMU75_Discrete_MemoryLevel) *
			SMU75_MAX_LEVELS_MEMORY;
	काष्ठा SMU75_Discrete_MemoryLevel *levels =
			smu_data->smc_state_table.MemoryLevel;
	uपूर्णांक32_t i;

	क्रम (i = 0; i < dpm_table->mclk_table.count; i++) अणु
		PP_ASSERT_WITH_CODE((0 != dpm_table->mclk_table.dpm_levels[i].value),
				"can not populate memory level as memory clock is zero",
				वापस -EINVAL);
		result = vegam_populate_single_memory_level(hwmgr,
				dpm_table->mclk_table.dpm_levels[i].value,
				&levels[i]);

		अगर (result)
			वापस result;

		levels[i].UpHyst = (uपूर्णांक8_t)
				(MemoryDPMTuning_VEGAM >> DPMTuning_Uphyst_Shअगरt);
		levels[i].DownHyst = (uपूर्णांक8_t)
				(MemoryDPMTuning_VEGAM >> DPMTuning_Downhyst_Shअगरt);
	पूर्ण

	smu_data->smc_state_table.MemoryDpmLevelCount =
			(uपूर्णांक8_t)dpm_table->mclk_table.count;
	hw_data->dpm_level_enable_mask.mclk_dpm_enable_mask =
			phm_get_dpm_level_enable_mask_value(&dpm_table->mclk_table);

	क्रम (i = 0; i < dpm_table->mclk_table.count; i++)
		levels[i].EnabledForActivity =
				(hw_data->dpm_level_enable_mask.mclk_dpm_enable_mask >> i) & 0x1;

	levels[dpm_table->mclk_table.count - 1].DisplayWatermark =
			PPSMC_DISPLAY_WATERMARK_HIGH;

	/* level count will send to smc once at init smc table and never change */
	result = smu7_copy_bytes_to_smc(hwmgr, array, (uपूर्णांक8_t *)levels,
			(uपूर्णांक32_t)array_size, SMC_RAM_END);

	वापस result;
पूर्ण

अटल पूर्णांक vegam_populate_mvdd_value(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t mclk, SMIO_Pattern *smio_pat)
अणु
	स्थिर काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	uपूर्णांक32_t i = 0;

	अगर (SMU7_VOLTAGE_CONTROL_NONE != data->mvdd_control) अणु
		/* find mvdd value which घड़ी is more than request */
		क्रम (i = 0; i < table_info->vdd_dep_on_mclk->count; i++) अणु
			अगर (mclk <= table_info->vdd_dep_on_mclk->entries[i].clk) अणु
				smio_pat->Voltage = data->mvdd_voltage_table.entries[i].value;
				अवरोध;
			पूर्ण
		पूर्ण
		PP_ASSERT_WITH_CODE(i < table_info->vdd_dep_on_mclk->count,
				"MVDD Voltage is outside the supported range.",
				वापस -EINVAL);
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_smc_acpi_level(काष्ठा pp_hwmgr *hwmgr,
		SMU75_Discrete_DpmTable *table)
अणु
	पूर्णांक result = 0;
	uपूर्णांक32_t sclk_frequency;
	स्थिर काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	SMIO_Pattern vol_level;
	uपूर्णांक32_t mvdd;

	table->ACPILevel.Flags &= ~PPSMC_SWSTATE_FLAG_DC;

	/* Get MinVoltage and Frequency from DPM0,
	 * alपढ़ोy converted to SMC_UL */
	sclk_frequency = data->vbios_boot_state.sclk_bootup_value;
	result = vegam_get_dependency_volt_by_clk(hwmgr,
			table_info->vdd_dep_on_sclk,
			sclk_frequency,
			&table->ACPILevel.MinVoltage, &mvdd);
	PP_ASSERT_WITH_CODE(!result,
			"Cannot find ACPI VDDC voltage value "
			"in Clock Dependency Table",
			);

	result = vegam_calculate_sclk_params(hwmgr, sclk_frequency,
			&(table->ACPILevel.SclkSetting));
	PP_ASSERT_WITH_CODE(!result,
			"Error retrieving Engine Clock dividers from VBIOS.",
			वापस result);

	table->ACPILevel.DeepSleepDivId = 0;
	table->ACPILevel.CcPwrDynRm = 0;
	table->ACPILevel.CcPwrDynRm1 = 0;

	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.Flags);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.MinVoltage);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CcPwrDynRm);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CcPwrDynRm1);

	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.SclkSetting.SclkFrequency);
	CONVERT_FROM_HOST_TO_SMC_US(table->ACPILevel.SclkSetting.Fcw_पूर्णांक);
	CONVERT_FROM_HOST_TO_SMC_US(table->ACPILevel.SclkSetting.Fcw_frac);
	CONVERT_FROM_HOST_TO_SMC_US(table->ACPILevel.SclkSetting.Pcc_fcw_पूर्णांक);
	CONVERT_FROM_HOST_TO_SMC_US(table->ACPILevel.SclkSetting.Sclk_slew_rate);
	CONVERT_FROM_HOST_TO_SMC_US(table->ACPILevel.SclkSetting.Pcc_up_slew_rate);
	CONVERT_FROM_HOST_TO_SMC_US(table->ACPILevel.SclkSetting.Pcc_करोwn_slew_rate);
	CONVERT_FROM_HOST_TO_SMC_US(table->ACPILevel.SclkSetting.Fcw1_पूर्णांक);
	CONVERT_FROM_HOST_TO_SMC_US(table->ACPILevel.SclkSetting.Fcw1_frac);
	CONVERT_FROM_HOST_TO_SMC_US(table->ACPILevel.SclkSetting.Sclk_ss_slew_rate);


	/* Get MinVoltage and Frequency from DPM0, alपढ़ोy converted to SMC_UL */
	table->MemoryACPILevel.MclkFrequency = data->vbios_boot_state.mclk_bootup_value;
	result = vegam_get_dependency_volt_by_clk(hwmgr,
			table_info->vdd_dep_on_mclk,
			table->MemoryACPILevel.MclkFrequency,
			&table->MemoryACPILevel.MinVoltage, &mvdd);
	PP_ASSERT_WITH_CODE((0 == result),
			"Cannot find ACPI VDDCI voltage value "
			"in Clock Dependency Table",
			);

	अगर (!vegam_populate_mvdd_value(hwmgr, 0, &vol_level))
		table->MemoryACPILevel.MinMvdd = PP_HOST_TO_SMC_UL(vol_level.Voltage);
	अन्यथा
		table->MemoryACPILevel.MinMvdd = 0;

	table->MemoryACPILevel.StutterEnable = false;

	table->MemoryACPILevel.EnabledForThrottle = 0;
	table->MemoryACPILevel.EnabledForActivity = 0;
	table->MemoryACPILevel.UpHyst = 0;
	table->MemoryACPILevel.DownHyst = 100;
	table->MemoryACPILevel.VoltageDownHyst = 0;
	table->MemoryACPILevel.ActivityLevel =
		PP_HOST_TO_SMC_US(data->current_profile_setting.mclk_activity);

	CONVERT_FROM_HOST_TO_SMC_UL(table->MemoryACPILevel.MclkFrequency);
	CONVERT_FROM_HOST_TO_SMC_UL(table->MemoryACPILevel.MinVoltage);

	वापस result;
पूर्ण

अटल पूर्णांक vegam_populate_smc_vce_level(काष्ठा pp_hwmgr *hwmgr,
		SMU75_Discrete_DpmTable *table)
अणु
	पूर्णांक result = -EINVAL;
	uपूर्णांक8_t count;
	काष्ठा pp_atomctrl_घड़ी_भागiders_vi भागiders;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_mm_घड़ी_voltage_dependency_table *mm_table =
			table_info->mm_dep_table;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t vddci;

	table->VceLevelCount = (uपूर्णांक8_t)(mm_table->count);
	table->VceBootLevel = 0;

	क्रम (count = 0; count < table->VceLevelCount; count++) अणु
		table->VceLevel[count].Frequency = mm_table->entries[count].eclk;
		table->VceLevel[count].MinVoltage = 0;
		table->VceLevel[count].MinVoltage |=
				(mm_table->entries[count].vddc * VOLTAGE_SCALE) << VDDC_SHIFT;

		अगर (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->vddci_control)
			vddci = (uपूर्णांक32_t)phm_find_बंदst_vddci(&(data->vddci_voltage_table),
						mm_table->entries[count].vddc - VDDC_VDDCI_DELTA);
		अन्यथा अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->vddci_control)
			vddci = mm_table->entries[count].vddc - VDDC_VDDCI_DELTA;
		अन्यथा
			vddci = (data->vbios_boot_state.vddci_bootup_value * VOLTAGE_SCALE) << VDDCI_SHIFT;


		table->VceLevel[count].MinVoltage |=
				(vddci * VOLTAGE_SCALE) << VDDCI_SHIFT;
		table->VceLevel[count].MinVoltage |= 1 << PHASES_SHIFT;

		/*retrieve भागider value क्रम VBIOS */
		result = atomctrl_get_dfs_pll_भागiders_vi(hwmgr,
				table->VceLevel[count].Frequency, &भागiders);
		PP_ASSERT_WITH_CODE((0 == result),
				"can not find divide id for VCE engine clock",
				वापस result);

		table->VceLevel[count].Divider = (uपूर्णांक8_t)भागiders.pll_post_भागider;

		CONVERT_FROM_HOST_TO_SMC_UL(table->VceLevel[count].Frequency);
		CONVERT_FROM_HOST_TO_SMC_UL(table->VceLevel[count].MinVoltage);
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक vegam_populate_memory_timing_parameters(काष्ठा pp_hwmgr *hwmgr,
		पूर्णांक32_t eng_घड़ी, पूर्णांक32_t mem_घड़ी,
		SMU75_Discrete_MCArbDramTimingTableEntry *arb_regs)
अणु
	uपूर्णांक32_t dram_timing;
	uपूर्णांक32_t dram_timing2;
	uपूर्णांक32_t burst_समय;
	uपूर्णांक32_t rfsh_rate;
	uपूर्णांक32_t misc3;

	पूर्णांक result;

	result = atomctrl_set_engine_dram_timings_rv770(hwmgr,
			eng_घड़ी, mem_घड़ी);
	PP_ASSERT_WITH_CODE(result == 0,
			"Error calling VBIOS to set DRAM_TIMING.",
			वापस result);

	dram_timing = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_ARB_DRAM_TIMING);
	dram_timing2 = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_ARB_DRAM_TIMING2);
	burst_समय = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_ARB_BURST_TIME);
	rfsh_rate = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_ARB_RFSH_RATE);
	misc3 = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_ARB_MISC3);

	arb_regs->McArbDramTiming  = PP_HOST_TO_SMC_UL(dram_timing);
	arb_regs->McArbDramTiming2 = PP_HOST_TO_SMC_UL(dram_timing2);
	arb_regs->McArbBurstTime   = PP_HOST_TO_SMC_UL(burst_समय);
	arb_regs->McArbRfshRate = PP_HOST_TO_SMC_UL(rfsh_rate);
	arb_regs->McArbMisc3 = PP_HOST_TO_SMC_UL(misc3);

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_program_memory_timing_parameters(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *hw_data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	काष्ठा SMU75_Discrete_MCArbDramTimingTable arb_regs;
	uपूर्णांक32_t i, j;
	पूर्णांक result = 0;

	स_रखो(&arb_regs, 0, माप(SMU75_Discrete_MCArbDramTimingTable));

	क्रम (i = 0; i < hw_data->dpm_table.sclk_table.count; i++) अणु
		क्रम (j = 0; j < hw_data->dpm_table.mclk_table.count; j++) अणु
			result = vegam_populate_memory_timing_parameters(hwmgr,
					hw_data->dpm_table.sclk_table.dpm_levels[i].value,
					hw_data->dpm_table.mclk_table.dpm_levels[j].value,
					&arb_regs.entries[i][j]);
			अगर (result)
				वापस result;
		पूर्ण
	पूर्ण

	result = smu7_copy_bytes_to_smc(
			hwmgr,
			smu_data->smu7_data.arb_table_start,
			(uपूर्णांक8_t *)&arb_regs,
			माप(SMU75_Discrete_MCArbDramTimingTable),
			SMC_RAM_END);
	वापस result;
पूर्ण

अटल पूर्णांक vegam_populate_smc_uvd_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU75_Discrete_DpmTable *table)
अणु
	पूर्णांक result = -EINVAL;
	uपूर्णांक8_t count;
	काष्ठा pp_atomctrl_घड़ी_भागiders_vi भागiders;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_mm_घड़ी_voltage_dependency_table *mm_table =
			table_info->mm_dep_table;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t vddci;

	table->UvdLevelCount = (uपूर्णांक8_t)(mm_table->count);
	table->UvdBootLevel = 0;

	क्रम (count = 0; count < table->UvdLevelCount; count++) अणु
		table->UvdLevel[count].MinVoltage = 0;
		table->UvdLevel[count].VclkFrequency = mm_table->entries[count].vclk;
		table->UvdLevel[count].DclkFrequency = mm_table->entries[count].dclk;
		table->UvdLevel[count].MinVoltage |=
				(mm_table->entries[count].vddc * VOLTAGE_SCALE) << VDDC_SHIFT;

		अगर (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->vddci_control)
			vddci = (uपूर्णांक32_t)phm_find_बंदst_vddci(&(data->vddci_voltage_table),
						mm_table->entries[count].vddc - VDDC_VDDCI_DELTA);
		अन्यथा अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->vddci_control)
			vddci = mm_table->entries[count].vddc - VDDC_VDDCI_DELTA;
		अन्यथा
			vddci = (data->vbios_boot_state.vddci_bootup_value * VOLTAGE_SCALE) << VDDCI_SHIFT;

		table->UvdLevel[count].MinVoltage |= (vddci * VOLTAGE_SCALE) << VDDCI_SHIFT;
		table->UvdLevel[count].MinVoltage |= 1 << PHASES_SHIFT;

		/* retrieve भागider value क्रम VBIOS */
		result = atomctrl_get_dfs_pll_भागiders_vi(hwmgr,
				table->UvdLevel[count].VclkFrequency, &भागiders);
		PP_ASSERT_WITH_CODE((0 == result),
				"can not find divide id for Vclk clock", वापस result);

		table->UvdLevel[count].VclkDivider = (uपूर्णांक8_t)भागiders.pll_post_भागider;

		result = atomctrl_get_dfs_pll_भागiders_vi(hwmgr,
				table->UvdLevel[count].DclkFrequency, &भागiders);
		PP_ASSERT_WITH_CODE((0 == result),
				"can not find divide id for Dclk clock", वापस result);

		table->UvdLevel[count].DclkDivider = (uपूर्णांक8_t)भागiders.pll_post_भागider;

		CONVERT_FROM_HOST_TO_SMC_UL(table->UvdLevel[count].VclkFrequency);
		CONVERT_FROM_HOST_TO_SMC_UL(table->UvdLevel[count].DclkFrequency);
		CONVERT_FROM_HOST_TO_SMC_UL(table->UvdLevel[count].MinVoltage);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक vegam_populate_smc_boot_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU75_Discrete_DpmTable *table)
अणु
	पूर्णांक result = 0;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	table->GraphicsBootLevel = 0;
	table->MemoryBootLevel = 0;

	/* find boot level from dpm table */
	result = phm_find_boot_level(&(data->dpm_table.sclk_table),
			data->vbios_boot_state.sclk_bootup_value,
			(uपूर्णांक32_t *)&(table->GraphicsBootLevel));
	अगर (result)
		वापस result;

	result = phm_find_boot_level(&(data->dpm_table.mclk_table),
			data->vbios_boot_state.mclk_bootup_value,
			(uपूर्णांक32_t *)&(table->MemoryBootLevel));

	अगर (result)
		वापस result;

	table->BootVddc  = data->vbios_boot_state.vddc_bootup_value *
			VOLTAGE_SCALE;
	table->BootVddci = data->vbios_boot_state.vddci_bootup_value *
			VOLTAGE_SCALE;
	table->BootMVdd  = data->vbios_boot_state.mvdd_bootup_value *
			VOLTAGE_SCALE;

	CONVERT_FROM_HOST_TO_SMC_US(table->BootVddc);
	CONVERT_FROM_HOST_TO_SMC_US(table->BootVddci);
	CONVERT_FROM_HOST_TO_SMC_US(table->BootMVdd);

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_smc_initial_state(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *hw_data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	uपूर्णांक8_t count, level;

	count = (uपूर्णांक8_t)(table_info->vdd_dep_on_sclk->count);

	क्रम (level = 0; level < count; level++) अणु
		अगर (table_info->vdd_dep_on_sclk->entries[level].clk >=
				hw_data->vbios_boot_state.sclk_bootup_value) अणु
			smu_data->smc_state_table.GraphicsBootLevel = level;
			अवरोध;
		पूर्ण
	पूर्ण

	count = (uपूर्णांक8_t)(table_info->vdd_dep_on_mclk->count);
	क्रम (level = 0; level < count; level++) अणु
		अगर (table_info->vdd_dep_on_mclk->entries[level].clk >=
				hw_data->vbios_boot_state.mclk_bootup_value) अणु
			smu_data->smc_state_table.MemoryBootLevel = level;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल uपूर्णांक16_t scale_fan_gain_settings(uपूर्णांक16_t raw_setting)
अणु
	uपूर्णांक32_t पंचांगp;
	पंचांगp = raw_setting * 4096 / 100;
	वापस (uपूर्णांक16_t)पंचांगp;
पूर्ण

अटल पूर्णांक vegam_populate_bapm_parameters_in_dpm_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);

	स्थिर काष्ठा vegam_pt_शेषs *शेषs = smu_data->घातer_tune_शेषs;
	SMU75_Discrete_DpmTable  *table = &(smu_data->smc_state_table);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_cac_tdp_table *cac_dtp_table = table_info->cac_dtp_table;
	काष्ठा pp_advance_fan_control_parameters *fan_table =
			&hwmgr->thermal_controller.advanceFanControlParameters;
	पूर्णांक i, j, k;
	स्थिर uपूर्णांक16_t *pdef1;
	स्थिर uपूर्णांक16_t *pdef2;

	table->DefaultTdp = PP_HOST_TO_SMC_US((uपूर्णांक16_t)(cac_dtp_table->usTDP * 128));
	table->TargetTdp  = PP_HOST_TO_SMC_US((uपूर्णांक16_t)(cac_dtp_table->usTDP * 128));

	PP_ASSERT_WITH_CODE(cac_dtp_table->usTargetOperatingTemp <= 255,
				"Target Operating Temp is out of Range!",
				);

	table->TemperatureLimitEdge = PP_HOST_TO_SMC_US(
			cac_dtp_table->usTargetOperatingTemp * 256);
	table->TemperatureLimitHotspot = PP_HOST_TO_SMC_US(
			cac_dtp_table->usTemperatureLimitHotspot * 256);
	table->FanGainEdge = PP_HOST_TO_SMC_US(
			scale_fan_gain_settings(fan_table->usFanGainEdge));
	table->FanGainHotspot = PP_HOST_TO_SMC_US(
			scale_fan_gain_settings(fan_table->usFanGainHotspot));

	pdef1 = शेषs->BAPMTI_R;
	pdef2 = शेषs->BAPMTI_RC;

	क्रम (i = 0; i < SMU75_DTE_ITERATIONS; i++) अणु
		क्रम (j = 0; j < SMU75_DTE_SOURCES; j++) अणु
			क्रम (k = 0; k < SMU75_DTE_SINKS; k++) अणु
				table->BAPMTI_R[i][j][k] = PP_HOST_TO_SMC_US(*pdef1);
				table->BAPMTI_RC[i][j][k] = PP_HOST_TO_SMC_US(*pdef2);
				pdef1++;
				pdef2++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_घड़ी_stretcher_data_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t ro, efuse, volt_without_cks, volt_with_cks, value, max, min;
	काष्ठा vegam_smumgr *smu_data =
			(काष्ठा vegam_smumgr *)(hwmgr->smu_backend);

	uपूर्णांक8_t i, stretch_amount, volt_offset = 0;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *sclk_table =
			table_info->vdd_dep_on_sclk;

	stretch_amount = (uपूर्णांक8_t)table_info->cac_dtp_table->usClockStretchAmount;

	atomctrl_पढ़ो_efuse(hwmgr, STRAP_ASIC_RO_LSB, STRAP_ASIC_RO_MSB,
			&efuse);

	min = 1200;
	max = 2500;

	ro = efuse * (max - min) / 255 + min;

	/* Populate Sclk_CKS_masterEn0_7 and Sclk_voltageOffset */
	क्रम (i = 0; i < sclk_table->count; i++) अणु
		smu_data->smc_state_table.Sclk_CKS_masterEn0_7 |=
				sclk_table->entries[i].cks_enable << i;
		volt_without_cks = (uपूर्णांक32_t)((2753594000U + (sclk_table->entries[i].clk/100) *
				136418 - (ro - 70) * 1000000) /
				(2424180 - (sclk_table->entries[i].clk/100) * 1132925/1000));
		volt_with_cks = (uपूर्णांक32_t)((2797202000U + sclk_table->entries[i].clk/100 *
				3232 - (ro - 65) * 1000000) /
				(2522480 - sclk_table->entries[i].clk/100 * 115764/100));

		अगर (volt_without_cks >= volt_with_cks)
			volt_offset = (uपूर्णांक8_t)(((volt_without_cks - volt_with_cks +
					sclk_table->entries[i].cks_voffset) * 100 + 624) / 625);

		smu_data->smc_state_table.Sclk_voltageOffset[i] = volt_offset;
	पूर्ण

	smu_data->smc_state_table.LकरोRefSel =
			(table_info->cac_dtp_table->ucCKS_LDO_REFSEL != 0) ?
			table_info->cac_dtp_table->ucCKS_LDO_REFSEL : 5;
	/* Populate CKS Lookup Table */
	अगर (!(stretch_amount == 1 || stretch_amount == 2 ||
	      stretch_amount == 5 || stretch_amount == 3 ||
	      stretch_amount == 4)) अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_ClockStretcher);
		PP_ASSERT_WITH_CODE(false,
				"Stretch Amount in PPTable not supported\n",
				वापस -EINVAL);
	पूर्ण

	value = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixPWR_CKS_CNTL);
	value &= 0xFFFFFFFE;
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixPWR_CKS_CNTL, value);

	वापस 0;
पूर्ण

अटल bool vegam_is_hw_avfs_present(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t efuse;

	efuse = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			ixSMU_EFUSE_0 + (49 * 4));
	efuse &= 0x00000001;

	अगर (efuse)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक vegam_populate_avfs_parameters(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);

	SMU75_Discrete_DpmTable  *table = &(smu_data->smc_state_table);
	पूर्णांक result = 0;
	काष्ठा pp_atom_ctrl__avfs_parameters avfs_params = अणु0पूर्ण;
	AVFS_meanNsigma_t AVFS_meanNsigma = अणु अणु0पूर्ण पूर्ण;
	AVFS_Sclk_Offset_t AVFS_SclkOffset = अणु अणु0पूर्ण पूर्ण;
	uपूर्णांक32_t पंचांगp, i;

	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)hwmgr->pptable;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *sclk_table =
			table_info->vdd_dep_on_sclk;

	अगर (!hwmgr->avfs_supported)
		वापस 0;

	result = atomctrl_get_avfs_inक्रमmation(hwmgr, &avfs_params);

	अगर (0 == result) अणु
		table->BTCGB_VDROOP_TABLE[0].a0 =
				PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSON_a0);
		table->BTCGB_VDROOP_TABLE[0].a1 =
				PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSON_a1);
		table->BTCGB_VDROOP_TABLE[0].a2 =
				PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSON_a2);
		table->BTCGB_VDROOP_TABLE[1].a0 =
				PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a0);
		table->BTCGB_VDROOP_TABLE[1].a1 =
				PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a1);
		table->BTCGB_VDROOP_TABLE[1].a2 =
				PP_HOST_TO_SMC_UL(avfs_params.ulGB_VDROOP_TABLE_CKSOFF_a2);
		table->AVFSGB_FUSE_TABLE[0].m1 =
				PP_HOST_TO_SMC_UL(avfs_params.ulAVFSGB_FUSE_TABLE_CKSON_m1);
		table->AVFSGB_FUSE_TABLE[0].m2 =
				PP_HOST_TO_SMC_US(avfs_params.usAVFSGB_FUSE_TABLE_CKSON_m2);
		table->AVFSGB_FUSE_TABLE[0].b =
				PP_HOST_TO_SMC_UL(avfs_params.ulAVFSGB_FUSE_TABLE_CKSON_b);
		table->AVFSGB_FUSE_TABLE[0].m1_shअगरt = 24;
		table->AVFSGB_FUSE_TABLE[0].m2_shअगरt = 12;
		table->AVFSGB_FUSE_TABLE[1].m1 =
				PP_HOST_TO_SMC_UL(avfs_params.ulAVFSGB_FUSE_TABLE_CKSOFF_m1);
		table->AVFSGB_FUSE_TABLE[1].m2 =
				PP_HOST_TO_SMC_US(avfs_params.usAVFSGB_FUSE_TABLE_CKSOFF_m2);
		table->AVFSGB_FUSE_TABLE[1].b =
				PP_HOST_TO_SMC_UL(avfs_params.ulAVFSGB_FUSE_TABLE_CKSOFF_b);
		table->AVFSGB_FUSE_TABLE[1].m1_shअगरt = 24;
		table->AVFSGB_FUSE_TABLE[1].m2_shअगरt = 12;
		table->MaxVoltage = PP_HOST_TO_SMC_US(avfs_params.usMaxVoltage_0_25mv);
		AVFS_meanNsigma.Aस्थिरant[0] =
				PP_HOST_TO_SMC_UL(avfs_params.ulAVFS_meanNsigma_Acontant0);
		AVFS_meanNsigma.Aस्थिरant[1] =
				PP_HOST_TO_SMC_UL(avfs_params.ulAVFS_meanNsigma_Acontant1);
		AVFS_meanNsigma.Aस्थिरant[2] =
				PP_HOST_TO_SMC_UL(avfs_params.ulAVFS_meanNsigma_Acontant2);
		AVFS_meanNsigma.DC_tol_sigma =
				PP_HOST_TO_SMC_US(avfs_params.usAVFS_meanNsigma_DC_tol_sigma);
		AVFS_meanNsigma.Platक्रमm_mean =
				PP_HOST_TO_SMC_US(avfs_params.usAVFS_meanNsigma_Platक्रमm_mean);
		AVFS_meanNsigma.PSM_Age_CompFactor =
				PP_HOST_TO_SMC_US(avfs_params.usPSM_Age_ComFactor);
		AVFS_meanNsigma.Platक्रमm_sigma =
				PP_HOST_TO_SMC_US(avfs_params.usAVFS_meanNsigma_Platक्रमm_sigma);

		क्रम (i = 0; i < sclk_table->count; i++) अणु
			AVFS_meanNsigma.Static_Voltage_Offset[i] =
					(uपूर्णांक8_t)(sclk_table->entries[i].cks_voffset * 100 / 625);
			AVFS_SclkOffset.Sclk_Offset[i] =
					PP_HOST_TO_SMC_US((uपूर्णांक16_t)
							(sclk_table->entries[i].sclk_offset) / 100);
		पूर्ण

		result = smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU7_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU75_Firmware_Header, AvfsMeanNSigma),
				&पंचांगp, SMC_RAM_END);
		smu7_copy_bytes_to_smc(hwmgr,
					पंचांगp,
					(uपूर्णांक8_t *)&AVFS_meanNsigma,
					माप(AVFS_meanNsigma_t),
					SMC_RAM_END);

		result = smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU7_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU75_Firmware_Header, AvfsSclkOffsetTable),
				&पंचांगp, SMC_RAM_END);
		smu7_copy_bytes_to_smc(hwmgr,
					पंचांगp,
					(uपूर्णांक8_t *)&AVFS_SclkOffset,
					माप(AVFS_Sclk_Offset_t),
					SMC_RAM_END);

		data->avfs_vdroop_override_setting =
				(avfs_params.ucEnableGB_VDROOP_TABLE_CKSON << BTCGB0_Vdroop_Enable_SHIFT) |
				(avfs_params.ucEnableGB_VDROOP_TABLE_CKSOFF << BTCGB1_Vdroop_Enable_SHIFT) |
				(avfs_params.ucEnableGB_FUSE_TABLE_CKSON << AVFSGB0_Vdroop_Enable_SHIFT) |
				(avfs_params.ucEnableGB_FUSE_TABLE_CKSOFF << AVFSGB1_Vdroop_Enable_SHIFT);
		data->apply_avfs_cks_off_voltage =
				(avfs_params.ucEnableApplyAVFS_CKS_OFF_Voltage == 1) ? true : false;
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक vegam_populate_vr_config(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU75_Discrete_DpmTable *table)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा vegam_smumgr *smu_data =
			(काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक16_t config;

	config = VR_MERGED_WITH_VDDC;
	table->VRConfig |= (config << VRCONF_VDDGFX_SHIFT);

	/* Set Vddc Voltage Controller */
	अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->voltage_control) अणु
		config = VR_SVI2_PLANE_1;
		table->VRConfig |= config;
	पूर्ण अन्यथा अणु
		PP_ASSERT_WITH_CODE(false,
				"VDDC should be on SVI2 control in merged mode!",
				);
	पूर्ण
	/* Set Vddci Voltage Controller */
	अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->vddci_control) अणु
		config = VR_SVI2_PLANE_2;  /* only in merged mode */
		table->VRConfig |= (config << VRCONF_VDDCI_SHIFT);
	पूर्ण अन्यथा अगर (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->vddci_control) अणु
		config = VR_SMIO_PATTERN_1;
		table->VRConfig |= (config << VRCONF_VDDCI_SHIFT);
	पूर्ण अन्यथा अणु
		config = VR_STATIC_VOLTAGE;
		table->VRConfig |= (config << VRCONF_VDDCI_SHIFT);
	पूर्ण
	/* Set Mvdd Voltage Controller */
	अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->mvdd_control) अणु
		अगर (config != VR_SVI2_PLANE_2) अणु
			config = VR_SVI2_PLANE_2;
			table->VRConfig |= (config << VRCONF_MVDD_SHIFT);
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device,
					CGS_IND_REG__SMC,
					smu_data->smu7_data.soft_regs_start +
					दुरत्व(SMU75_SoftRegisters, AllowMvddSwitch),
					0x1);
		पूर्ण अन्यथा अणु
			PP_ASSERT_WITH_CODE(false,
					"SVI2 Plane 2 is already taken, set MVDD as Static",);
			config = VR_STATIC_VOLTAGE;
			table->VRConfig = (config << VRCONF_MVDD_SHIFT);
		पूर्ण
	पूर्ण अन्यथा अगर (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->mvdd_control) अणु
		config = VR_SMIO_PATTERN_2;
		table->VRConfig = (config << VRCONF_MVDD_SHIFT);
		cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device,
				CGS_IND_REG__SMC,
				smu_data->smu7_data.soft_regs_start +
				दुरत्व(SMU75_SoftRegisters, AllowMvddSwitch),
				0x1);
	पूर्ण अन्यथा अणु
		config = VR_STATIC_VOLTAGE;
		table->VRConfig |= (config << VRCONF_MVDD_SHIFT);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_svi_load_line(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	स्थिर काष्ठा vegam_pt_शेषs *शेषs = smu_data->घातer_tune_शेषs;

	smu_data->घातer_tune_table.SviLoadLineEn = शेषs->SviLoadLineEn;
	smu_data->घातer_tune_table.SviLoadLineVddC = शेषs->SviLoadLineVddC;
	smu_data->घातer_tune_table.SviLoadLineTrimVddC = 3;
	smu_data->घातer_tune_table.SviLoadLineOffsetVddC = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_tdc_limit(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक16_t tdc_limit;
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	स्थिर काष्ठा vegam_pt_शेषs *शेषs = smu_data->घातer_tune_शेषs;

	tdc_limit = (uपूर्णांक16_t)(table_info->cac_dtp_table->usTDC * 128);
	smu_data->घातer_tune_table.TDC_VDDC_PkgLimit =
			CONVERT_FROM_HOST_TO_SMC_US(tdc_limit);
	smu_data->घातer_tune_table.TDC_VDDC_ThrottleReleaseLimitPerc =
			शेषs->TDC_VDDC_ThrottleReleaseLimitPerc;
	smu_data->घातer_tune_table.TDC_MAWt = शेषs->TDC_MAWt;

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_dw8(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t fuse_table_offset)
अणु
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	स्थिर काष्ठा vegam_pt_शेषs *शेषs = smu_data->घातer_tune_शेषs;
	uपूर्णांक32_t temp;

	अगर (smu7_पढ़ो_smc_sram_dword(hwmgr,
			fuse_table_offset +
			दुरत्व(SMU75_Discrete_PmFuses, TdcWaterfallCtl),
			(uपूर्णांक32_t *)&temp, SMC_RAM_END))
		PP_ASSERT_WITH_CODE(false,
				"Attempt to read PmFuses.DW6 (SviLoadLineEn) from SMC Failed!",
				वापस -EINVAL);
	अन्यथा अणु
		smu_data->घातer_tune_table.TdcWaterfallCtl = शेषs->TdcWaterfallCtl;
		smu_data->घातer_tune_table.LPMLTemperatureMin =
				(uपूर्णांक8_t)((temp >> 16) & 0xff);
		smu_data->घातer_tune_table.LPMLTemperatureMax =
				(uपूर्णांक8_t)((temp >> 8) & 0xff);
		smu_data->घातer_tune_table.Reserved = (uपूर्णांक8_t)(temp & 0xff);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_temperature_scaler(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक i;
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);

	/* Currently not used. Set all to zero. */
	क्रम (i = 0; i < 16; i++)
		smu_data->घातer_tune_table.LPMLTemperatureScaler[i] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_fuzzy_fan(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);

/* TO DO move to hwmgr */
	अगर ((hwmgr->thermal_controller.advanceFanControlParameters.usFanOutputSensitivity & (1 << 15))
		|| 0 == hwmgr->thermal_controller.advanceFanControlParameters.usFanOutputSensitivity)
		hwmgr->thermal_controller.advanceFanControlParameters.usFanOutputSensitivity =
			hwmgr->thermal_controller.advanceFanControlParameters.usDefaultFanOutputSensitivity;

	smu_data->घातer_tune_table.FuzzyFan_PwmSetDelta = PP_HOST_TO_SMC_US(
				hwmgr->thermal_controller.advanceFanControlParameters.usFanOutputSensitivity);
	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_gnb_lpml(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक i;
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);

	/* Currently not used. Set all to zero. */
	क्रम (i = 0; i < 16; i++)
		smu_data->घातer_tune_table.GnbLPML[i] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_bapm_vddc_base_leakage_sidd(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	uपूर्णांक16_t hi_sidd = smu_data->घातer_tune_table.BapmVddCBaseLeakageHiSidd;
	uपूर्णांक16_t lo_sidd = smu_data->घातer_tune_table.BapmVddCBaseLeakageLoSidd;
	काष्ठा phm_cac_tdp_table *cac_table = table_info->cac_dtp_table;

	hi_sidd = (uपूर्णांक16_t)(cac_table->usHighCACLeakage / 100 * 256);
	lo_sidd = (uपूर्णांक16_t)(cac_table->usLowCACLeakage / 100 * 256);

	smu_data->घातer_tune_table.BapmVddCBaseLeakageHiSidd =
			CONVERT_FROM_HOST_TO_SMC_US(hi_sidd);
	smu_data->घातer_tune_table.BapmVddCBaseLeakageLoSidd =
			CONVERT_FROM_HOST_TO_SMC_US(lo_sidd);

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_populate_pm_fuses(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t pm_fuse_table_offset;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_PowerContainment)) अणु
		अगर (smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU7_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU75_Firmware_Header, PmFuseTable),
				&pm_fuse_table_offset, SMC_RAM_END))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to get pm_fuse_table_offset Failed!",
					वापस -EINVAL);

		अगर (vegam_populate_svi_load_line(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate SviLoadLine Failed!",
					वापस -EINVAL);

		अगर (vegam_populate_tdc_limit(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate TDCLimit Failed!", वापस -EINVAL);

		अगर (vegam_populate_dw8(hwmgr, pm_fuse_table_offset))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate TdcWaterfallCtl, "
					"LPMLTemperature Min and Max Failed!",
					वापस -EINVAL);

		अगर (0 != vegam_populate_temperature_scaler(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate LPMLTemperatureScaler Failed!",
					वापस -EINVAL);

		अगर (vegam_populate_fuzzy_fan(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate Fuzzy Fan Control parameters Failed!",
					वापस -EINVAL);

		अगर (vegam_populate_gnb_lpml(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate GnbLPML Failed!",
					वापस -EINVAL);

		अगर (vegam_populate_bapm_vddc_base_leakage_sidd(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate BapmVddCBaseLeakage Hi and Lo "
					"Sidd Failed!", वापस -EINVAL);

		अगर (smu7_copy_bytes_to_smc(hwmgr, pm_fuse_table_offset,
				(uपूर्णांक8_t *)&smu_data->घातer_tune_table,
				(माप(काष्ठा SMU75_Discrete_PmFuses) - PMFUSES_AVFSSIZE),
				SMC_RAM_END))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to download PmFuseTable Failed!",
					वापस -EINVAL);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vegam_enable_reconfig_cus(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	smum_send_msg_to_smc_with_parameter(hwmgr,
					    PPSMC_MSG_EnableModeSwitchRLCNotअगरication,
					    adev->gfx.cu_info.number,
					    शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_init_smc_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	काष्ठा smu7_hwmgr *hw_data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा vegam_smumgr *smu_data = (काष्ठा vegam_smumgr *)(hwmgr->smu_backend);

	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा SMU75_Discrete_DpmTable *table = &(smu_data->smc_state_table);
	uपूर्णांक8_t i;
	काष्ठा pp_atomctrl_gpio_pin_assignment gpio_pin;
	काष्ठा phm_ppt_v1_gpio_table *gpio_table =
			(काष्ठा phm_ppt_v1_gpio_table *)table_info->gpio_table;
	pp_atomctrl_घड़ी_भागiders_vi भागiders;

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_AutomaticDCTransition);

	vegam_initialize_घातer_tune_शेषs(hwmgr);

	अगर (SMU7_VOLTAGE_CONTROL_NONE != hw_data->voltage_control)
		vegam_populate_smc_voltage_tables(hwmgr, table);

	table->SystemFlags = 0;
	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_AutomaticDCTransition))
		table->SystemFlags |= PPSMC_SYSTEMFLAG_GPIO_DC;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_StepVddc))
		table->SystemFlags |= PPSMC_SYSTEMFLAG_STEPVDDC;

	अगर (hw_data->is_memory_gddr5)
		table->SystemFlags |= PPSMC_SYSTEMFLAG_GDDR5;

	अगर (hw_data->ulv_supported && table_info->us_ulv_voltage_offset) अणु
		result = vegam_populate_ulv_state(hwmgr, table);
		PP_ASSERT_WITH_CODE(!result,
				"Failed to initialize ULV state!", वापस result);
		cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
				ixCG_ULV_PARAMETER, SMU7_CGULVPARAMETER_DFLT);
	पूर्ण

	result = vegam_populate_smc_link_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to initialize Link Level!", वापस result);

	result = vegam_populate_all_graphic_levels(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to initialize Graphics Level!", वापस result);

	result = vegam_populate_all_memory_levels(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to initialize Memory Level!", वापस result);

	result = vegam_populate_smc_acpi_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to initialize ACPI Level!", वापस result);

	result = vegam_populate_smc_vce_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to initialize VCE Level!", वापस result);

	/* Since only the initial state is completely set up at this poपूर्णांक
	 * (the other states are just copies of the boot state) we only
	 * need to populate the  ARB settings क्रम the initial state.
	 */
	result = vegam_program_memory_timing_parameters(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to Write ARB settings for the initial state.", वापस result);

	result = vegam_populate_smc_uvd_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to initialize UVD Level!", वापस result);

	result = vegam_populate_smc_boot_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to initialize Boot Level!", वापस result);

	result = vegam_populate_smc_initial_state(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to initialize Boot State!", वापस result);

	result = vegam_populate_bapm_parameters_in_dpm_table(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to populate BAPM Parameters!", वापस result);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_ClockStretcher)) अणु
		result = vegam_populate_घड़ी_stretcher_data_table(hwmgr);
		PP_ASSERT_WITH_CODE(!result,
				"Failed to populate Clock Stretcher Data Table!",
				वापस result);
	पूर्ण

	result = vegam_populate_avfs_parameters(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to populate AVFS Parameters!", वापस result;);

	table->CurrSclkPllRange = 0xff;
	table->GraphicsVoltageChangeEnable  = 1;
	table->GraphicsThermThrottleEnable  = 1;
	table->GraphicsInterval = 1;
	table->VoltageInterval  = 1;
	table->ThermalInterval  = 1;
	table->TemperatureLimitHigh =
			table_info->cac_dtp_table->usTargetOperatingTemp *
			SMU7_Q88_FORMAT_CONVERSION_UNIT;
	table->TemperatureLimitLow  =
			(table_info->cac_dtp_table->usTargetOperatingTemp - 1) *
			SMU7_Q88_FORMAT_CONVERSION_UNIT;
	table->MemoryVoltageChangeEnable = 1;
	table->MemoryInterval = 1;
	table->VoltageResponseTime = 0;
	table->PhaseResponseTime = 0;
	table->MemoryThermThrottleEnable = 1;

	PP_ASSERT_WITH_CODE(hw_data->dpm_table.pcie_speed_table.count >= 1,
			"There must be 1 or more PCIE levels defined in PPTable.",
			वापस -EINVAL);
	table->PCIeBootLinkLevel =
			hw_data->dpm_table.pcie_speed_table.count;
	table->PCIeGenInterval = 1;
	table->VRConfig = 0;

	result = vegam_populate_vr_config(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to populate VRConfig setting!", वापस result);

	table->ThermGpio = 17;
	table->SclkStepSize = 0x4000;

	अगर (atomctrl_get_pp_assign_pin(hwmgr,
			VDDC_VRHOT_GPIO_PINID, &gpio_pin)) अणु
		table->VRHotGpio = gpio_pin.uc_gpio_pin_bit_shअगरt;
		अगर (gpio_table)
			table->VRHotLevel =
					table_info->gpio_table->vrhot_triggered_sclk_dpm_index;
	पूर्ण अन्यथा अणु
		table->VRHotGpio = SMU7_UNUSED_GPIO_PIN;
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_RegulatorHot);
	पूर्ण

	अगर (atomctrl_get_pp_assign_pin(hwmgr,
			PP_AC_DC_SWITCH_GPIO_PINID,	&gpio_pin)) अणु
		table->AcDcGpio = gpio_pin.uc_gpio_pin_bit_shअगरt;
		अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_AutomaticDCTransition) &&
				!smum_send_msg_to_smc(hwmgr, PPSMC_MSG_UseNewGPIOScheme, शून्य))
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_SMCtoPPLIBAcdcGpioScheme);
	पूर्ण अन्यथा अणु
		table->AcDcGpio = SMU7_UNUSED_GPIO_PIN;
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_AutomaticDCTransition);
	पूर्ण

	/* Thermal Output GPIO */
	अगर (atomctrl_get_pp_assign_pin(hwmgr,
			THERMAL_INT_OUTPUT_GPIO_PINID, &gpio_pin)) अणु
		table->ThermOutGpio = gpio_pin.uc_gpio_pin_bit_shअगरt;

		/* For porlarity पढ़ो GPIOPAD_A with asचिन्हित Gpio pin
		 * since VBIOS will program this रेजिस्टर to set 'inactive state',
		 * driver can then determine 'active state' from this and
		 * program SMU with correct polarity
		 */
		table->ThermOutPolarity =
				(0 == (cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmGPIOPAD_A) &
				(1 << gpio_pin.uc_gpio_pin_bit_shअगरt))) ? 1:0;
		table->ThermOutMode = SMU7_THERM_OUT_MODE_THERM_ONLY;

		/* अगर required, combine VRHot/PCC with thermal out GPIO */
		अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_RegulatorHot) &&
			phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_CombinePCCWithThermalSignal))
			table->ThermOutMode = SMU7_THERM_OUT_MODE_THERM_VRHOT;
	पूर्ण अन्यथा अणु
		table->ThermOutGpio = 17;
		table->ThermOutPolarity = 1;
		table->ThermOutMode = SMU7_THERM_OUT_MODE_DISABLE;
	पूर्ण

	/* Populate BIF_SCLK levels पूर्णांकo SMC DPM table */
	क्रम (i = 0; i <= hw_data->dpm_table.pcie_speed_table.count; i++) अणु
		result = atomctrl_get_dfs_pll_भागiders_vi(hwmgr,
				smu_data->bअगर_sclk_table[i], &भागiders);
		PP_ASSERT_WITH_CODE(!result,
				"Can not find DFS divide id for Sclk",
				वापस result);

		अगर (i == 0)
			table->Ulv.BअगरSclkDfs =
					PP_HOST_TO_SMC_US((uपूर्णांक16_t)(भागiders.pll_post_भागider));
		अन्यथा
			table->LinkLevel[i - 1].BअगरSclkDfs =
					PP_HOST_TO_SMC_US((uपूर्णांक16_t)(भागiders.pll_post_भागider));
	पूर्ण

	क्रम (i = 0; i < SMU75_MAX_ENTRIES_SMIO; i++)
		table->Smio[i] = PP_HOST_TO_SMC_UL(table->Smio[i]);

	CONVERT_FROM_HOST_TO_SMC_UL(table->SystemFlags);
	CONVERT_FROM_HOST_TO_SMC_UL(table->VRConfig);
	CONVERT_FROM_HOST_TO_SMC_UL(table->SmioMask1);
	CONVERT_FROM_HOST_TO_SMC_UL(table->SmioMask2);
	CONVERT_FROM_HOST_TO_SMC_UL(table->SclkStepSize);
	CONVERT_FROM_HOST_TO_SMC_UL(table->CurrSclkPllRange);
	CONVERT_FROM_HOST_TO_SMC_US(table->TemperatureLimitHigh);
	CONVERT_FROM_HOST_TO_SMC_US(table->TemperatureLimitLow);
	CONVERT_FROM_HOST_TO_SMC_US(table->VoltageResponseTime);
	CONVERT_FROM_HOST_TO_SMC_US(table->PhaseResponseTime);

	/* Upload all dpm data to SMC memory.(dpm level, dpm level count etc) */
	result = smu7_copy_bytes_to_smc(hwmgr,
			smu_data->smu7_data.dpm_table_start +
			दुरत्व(SMU75_Discrete_DpmTable, SystemFlags),
			(uपूर्णांक8_t *)&(table->SystemFlags),
			माप(SMU75_Discrete_DpmTable) - 3 * माप(SMU75_PIDController),
			SMC_RAM_END);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to upload dpm data to SMC memory!", वापस result);

	result = vegam_populate_pm_fuses(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to  populate PM fuses to SMC memory!", वापस result);

	result = vegam_enable_reconfig_cus(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to enable reconfigurable CUs!", वापस result);

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t vegam_get_दुरत्व(uपूर्णांक32_t type, uपूर्णांक32_t member)
अणु
	चयन (type) अणु
	हाल SMU_SoftRegisters:
		चयन (member) अणु
		हाल HandshakeDisables:
			वापस दुरत्व(SMU75_SoftRegisters, HandshakeDisables);
		हाल VoltageChangeTimeout:
			वापस दुरत्व(SMU75_SoftRegisters, VoltageChangeTimeout);
		हाल AverageGraphicsActivity:
			वापस दुरत्व(SMU75_SoftRegisters, AverageGraphicsActivity);
		हाल AverageMemoryActivity:
			वापस दुरत्व(SMU75_SoftRegisters, AverageMemoryActivity);
		हाल PreVBlankGap:
			वापस दुरत्व(SMU75_SoftRegisters, PreVBlankGap);
		हाल VBlankTimeout:
			वापस दुरत्व(SMU75_SoftRegisters, VBlankTimeout);
		हाल UcodeLoadStatus:
			वापस दुरत्व(SMU75_SoftRegisters, UcodeLoadStatus);
		हाल DRAM_LOG_ADDR_H:
			वापस दुरत्व(SMU75_SoftRegisters, DRAM_LOG_ADDR_H);
		हाल DRAM_LOG_ADDR_L:
			वापस दुरत्व(SMU75_SoftRegisters, DRAM_LOG_ADDR_L);
		हाल DRAM_LOG_PHY_ADDR_H:
			वापस दुरत्व(SMU75_SoftRegisters, DRAM_LOG_PHY_ADDR_H);
		हाल DRAM_LOG_PHY_ADDR_L:
			वापस दुरत्व(SMU75_SoftRegisters, DRAM_LOG_PHY_ADDR_L);
		हाल DRAM_LOG_BUFF_SIZE:
			वापस दुरत्व(SMU75_SoftRegisters, DRAM_LOG_BUFF_SIZE);
		पूर्ण
		अवरोध;
	हाल SMU_Discrete_DpmTable:
		चयन (member) अणु
		हाल UvdBootLevel:
			वापस दुरत्व(SMU75_Discrete_DpmTable, UvdBootLevel);
		हाल VceBootLevel:
			वापस दुरत्व(SMU75_Discrete_DpmTable, VceBootLevel);
		हाल LowSclkInterruptThreshold:
			वापस दुरत्व(SMU75_Discrete_DpmTable, LowSclkInterruptThreshold);
		पूर्ण
		अवरोध;
	पूर्ण
	pr_warn("can't get the offset of type %x member %x\n", type, member);
	वापस 0;
पूर्ण

अटल पूर्णांक vegam_program_mem_timing_parameters(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (data->need_update_smu7_dpm_table &
		(DPMTABLE_OD_UPDATE_SCLK +
		DPMTABLE_UPDATE_SCLK +
		DPMTABLE_UPDATE_MCLK))
		वापस vegam_program_memory_timing_parameters(hwmgr);

	वापस 0;
पूर्ण

अटल पूर्णांक vegam_update_sclk_threshold(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा vegam_smumgr *smu_data =
			(काष्ठा vegam_smumgr *)(hwmgr->smu_backend);
	पूर्णांक result = 0;
	uपूर्णांक32_t low_sclk_पूर्णांकerrupt_threshold = 0;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_SclkThrottleLowNotअगरication)
	    && (data->low_sclk_पूर्णांकerrupt_threshold != 0)) अणु
		low_sclk_पूर्णांकerrupt_threshold =
				data->low_sclk_पूर्णांकerrupt_threshold;

		CONVERT_FROM_HOST_TO_SMC_UL(low_sclk_पूर्णांकerrupt_threshold);

		result = smu7_copy_bytes_to_smc(
				hwmgr,
				smu_data->smu7_data.dpm_table_start +
				दुरत्व(SMU75_Discrete_DpmTable,
					LowSclkInterruptThreshold),
				(uपूर्णांक8_t *)&low_sclk_पूर्णांकerrupt_threshold,
				माप(uपूर्णांक32_t),
				SMC_RAM_END);
	पूर्ण
	PP_ASSERT_WITH_CODE((result == 0),
			"Failed to update SCLK threshold!", वापस result);

	result = vegam_program_mem_timing_parameters(hwmgr);
	PP_ASSERT_WITH_CODE((result == 0),
			"Failed to program memory timing parameters!",
			);

	वापस result;
पूर्ण

अटल पूर्णांक vegam_thermal_avfs_enable(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	पूर्णांक ret;

	अगर (!hwmgr->avfs_supported)
		वापस 0;

	ret = smum_send_msg_to_smc(hwmgr, PPSMC_MSG_EnableAvfs, शून्य);
	अगर (!ret) अणु
		अगर (data->apply_avfs_cks_off_voltage)
			ret = smum_send_msg_to_smc(hwmgr,
					PPSMC_MSG_ApplyAvfsCksOffVoltage,
					शून्य);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vegam_thermal_setup_fan_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	PP_ASSERT_WITH_CODE(hwmgr->thermal_controller.fanInfo.bNoFan,
			"VBIOS fan info is not correct!",
			);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_MicrocodeFanControl);
	वापस 0;
पूर्ण

स्थिर काष्ठा pp_smumgr_func vegam_smu_funcs = अणु
	.name = "vegam_smu",
	.smu_init = vegam_smu_init,
	.smu_fini = smu7_smu_fini,
	.start_smu = vegam_start_smu,
	.check_fw_load_finish = smu7_check_fw_load_finish,
	.request_smu_load_fw = smu7_reload_firmware,
	.request_smu_load_specअगरic_fw = शून्य,
	.send_msg_to_smc = smu7_send_msg_to_smc,
	.send_msg_to_smc_with_parameter = smu7_send_msg_to_smc_with_parameter,
	.get_argument = smu7_get_argument,
	.process_firmware_header = vegam_process_firmware_header,
	.is_dpm_running = vegam_is_dpm_running,
	.get_mac_definition = vegam_get_mac_definition,
	.update_smc_table = vegam_update_smc_table,
	.init_smc_table = vegam_init_smc_table,
	.get_दुरत्व = vegam_get_दुरत्व,
	.populate_all_graphic_levels = vegam_populate_all_graphic_levels,
	.populate_all_memory_levels = vegam_populate_all_memory_levels,
	.update_sclk_threshold = vegam_update_sclk_threshold,
	.is_hw_avfs_present = vegam_is_hw_avfs_present,
	.thermal_avfs_enable = vegam_thermal_avfs_enable,
	.thermal_setup_fan_table = vegam_thermal_setup_fan_table,
पूर्ण;
