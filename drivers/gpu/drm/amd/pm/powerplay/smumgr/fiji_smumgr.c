<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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
#समावेश "smu7_dyn_defaults.h"
#समावेश "smu73.h"
#समावेश "smu_ucode_xfer_vi.h"
#समावेश "fiji_smumgr.h"
#समावेश "fiji_ppsmc.h"
#समावेश "smu73_discrete.h"
#समावेश "ppatomctrl.h"
#समावेश "smu/smu_7_1_3_d.h"
#समावेश "smu/smu_7_1_3_sh_mask.h"
#समावेश "gmc/gmc_8_1_d.h"
#समावेश "gmc/gmc_8_1_sh_mask.h"
#समावेश "oss/oss_3_0_d.h"
#समावेश "gca/gfx_8_0_d.h"
#समावेश "bif/bif_5_0_d.h"
#समावेश "bif/bif_5_0_sh_mask.h"
#समावेश "dce/dce_10_0_d.h"
#समावेश "dce/dce_10_0_sh_mask.h"
#समावेश "hardwaremanager.h"
#समावेश "cgs_common.h"
#समावेश "atombios.h"
#समावेश "pppcielanes.h"
#समावेश "hwmgr.h"
#समावेश "smu7_hwmgr.h"


#घोषणा AVFS_EN_MSB                                        1568
#घोषणा AVFS_EN_LSB                                        1568

#घोषणा FIJI_SMC_SIZE 0x20000

#घोषणा POWERTUNE_DEFAULT_SET_MAX    1
#घोषणा VDDC_VDDCI_DELTA            300
#घोषणा MC_CG_ARB_FREQ_F1           0x0b

/* [2.5%,~2.5%] Clock stretched is multiple of 2.5% vs
 * not and [Fmin, Fmax, LDO_REFSEL, USE_FOR_LOW_FREQ]
 */
अटल स्थिर uपूर्णांक16_t fiji_घड़ी_stretcher_lookup_table[2][4] = अणु
				अणु600, 1050, 3, 0पूर्ण, अणु600, 1050, 6, 1पूर्ण पूर्ण;

/* [FF, SS] type, [] 4 voltage ranges, and
 * [Floor Freq, Boundary Freq, VID min , VID max]
 */
अटल स्थिर uपूर्णांक32_t fiji_घड़ी_stretcher_ddt_table[2][4][4] = अणु
	अणु अणु265, 529, 120, 128पूर्ण, अणु325, 650, 96, 119पूर्ण, अणु430, 860, 32, 95पूर्ण, अणु0, 0, 0, 31पूर्ण पूर्ण,
	अणु अणु275, 550, 104, 112पूर्ण, अणु319, 638, 96, 103पूर्ण, अणु360, 720, 64, 95पूर्ण, अणु384, 768, 32, 63पूर्ण पूर्ण पूर्ण;

/* [Use_For_Low_freq] value, [0%, 5%, 10%, 7.14%, 14.28%, 20%]
 * (coming from PWR_CKS_CNTL.stretch_amount reg spec)
 */
अटल स्थिर uपूर्णांक8_t fiji_घड़ी_stretch_amount_conversion[2][6] = अणु
				अणु0, 1, 3, 2, 4, 5पूर्ण, अणु0, 2, 4, 5, 6, 5पूर्ण पूर्ण;

अटल स्थिर काष्ठा fiji_pt_शेषs fiji_घातer_tune_data_set_array[POWERTUNE_DEFAULT_SET_MAX] = अणु
		/*sviLoadLIneEn,  SviLoadLineVddC, TDC_VDDC_ThrottleReleaseLimitPerc */
		अणु1,               0xF,             0xFD,
		/* TDC_MAWt, TdcWaterfallCtl, DTEAmbientTempBase */
		0x19,        5,               45पूर्ण
पूर्ण;

अटल स्थिर काष्ठा SMU73_Discrete_GraphicsLevel avfs_graphics_level[8] = अणु
		/*  Min        Sclk       pcie     DeepSleep Activity  CgSpll      CgSpll    spllSpपढ़ो  SpllSpपढ़ो   CcPwr  CcPwr  Sclk   Display     Enabled     Enabled                       Voltage    Power */
		/* Voltage,  Frequency,  DpmLevel,  DivId,    Level,  FuncCntl3,  FuncCntl4,  Spectrum,   Spectrum2,  DynRm, DynRm1  Did, Watermark, ForActivity, ForThrottle, UpHyst, DownHyst, DownHyst, Throttle */
		अणु 0x3c0fd047, 0x30750000,   0x00,     0x03,   0x1e00, 0x00200410, 0x87020000, 0x21680000, 0x0c000000,   0,      0,   0x16,   0x00,       0x01,        0x01,      0x00,   0x00,      0x00,     0x00 पूर्ण,
		अणु 0xa00fd047, 0x409c0000,   0x01,     0x04,   0x1e00, 0x00800510, 0x87020000, 0x21680000, 0x11000000,   0,      0,   0x16,   0x00,       0x01,        0x01,      0x00,   0x00,      0x00,     0x00 पूर्ण,
		अणु 0x0410d047, 0x50c30000,   0x01,     0x00,   0x1e00, 0x00600410, 0x87020000, 0x21680000, 0x0d000000,   0,      0,   0x0e,   0x00,       0x01,        0x01,      0x00,   0x00,      0x00,     0x00 पूर्ण,
		अणु 0x6810d047, 0x60ea0000,   0x01,     0x00,   0x1e00, 0x00800410, 0x87020000, 0x21680000, 0x0e000000,   0,      0,   0x0c,   0x00,       0x01,        0x01,      0x00,   0x00,      0x00,     0x00 पूर्ण,
		अणु 0xcc10d047, 0xe8fd0000,   0x01,     0x00,   0x1e00, 0x00e00410, 0x87020000, 0x21680000, 0x0f000000,   0,      0,   0x0c,   0x00,       0x01,        0x01,      0x00,   0x00,      0x00,     0x00 पूर्ण,
		अणु 0x3011d047, 0x70110100,   0x01,     0x00,   0x1e00, 0x00400510, 0x87020000, 0x21680000, 0x10000000,   0,      0,   0x0c,   0x00,       0x01,        0x01,      0x00,   0x00,      0x00,     0x00 पूर्ण,
		अणु 0x9411d047, 0xf8240100,   0x01,     0x00,   0x1e00, 0x00a00510, 0x87020000, 0x21680000, 0x11000000,   0,      0,   0x0c,   0x00,       0x01,        0x01,      0x00,   0x00,      0x00,     0x00 पूर्ण,
		अणु 0xf811d047, 0x80380100,   0x01,     0x00,   0x1e00, 0x00000610, 0x87020000, 0x21680000, 0x12000000,   0,      0,   0x0c,   0x01,       0x01,        0x01,      0x00,   0x00,      0x00,     0x00 पूर्ण
पूर्ण;

अटल पूर्णांक fiji_start_smu_in_protection_mode(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;

	/* Wait क्रम smc boot up */
	/* PHM_WAIT_INसूचीECT_FIELD_UNEQUAL(hwmgr, SMC_IND,
		RCU_UC_EVENTS, boot_seq_करोne, 0); */

	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			SMC_SYSCON_RESET_CNTL, rst_reg, 1);

	result = smu7_upload_smu_firmware_image(hwmgr);
	अगर (result)
		वापस result;

	/* Clear status */
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			ixSMU_STATUS, 0);

	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			SMC_SYSCON_CLOCK_CNTL_0, ck_disable, 0);

	/* De-निश्चित reset */
	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			SMC_SYSCON_RESET_CNTL, rst_reg, 0);

	/* Wait क्रम ROM firmware to initialize पूर्णांकerrupt hendler */
	/*SMUM_WAIT_VFPF_INसूचीECT_REGISTER(hwmgr, SMC_IND,
			SMC_INTR_CNTL_MASK_0, 0x10040, 0xFFFFFFFF); */

	/* Set SMU Auto Start */
	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			SMU_INPUT_DATA, AUTO_START, 1);

	/* Clear firmware पूर्णांकerrupt enable flag */
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			ixFIRMWARE_FLAGS, 0);

	PHM_WAIT_VFPF_INसूचीECT_FIELD(hwmgr, SMC_IND, RCU_UC_EVENTS,
			INTERRUPTS_ENABLED, 1);

	smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_Test, 0x20000, शून्य);

	/* Wait क्रम करोne bit to be set */
	PHM_WAIT_VFPF_INसूचीECT_FIELD_UNEQUAL(hwmgr, SMC_IND,
			SMU_STATUS, SMU_DONE, 0);

	/* Check pass/failed indicator */
	अगर (PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			SMU_STATUS, SMU_PASS) != 1) अणु
		PP_ASSERT_WITH_CODE(false,
				"SMU Firmware start failed!", वापस -1);
	पूर्ण

	/* Wait क्रम firmware to initialize */
	PHM_WAIT_VFPF_INसूचीECT_FIELD(hwmgr, SMC_IND,
			FIRMWARE_FLAGS, INTERRUPTS_ENABLED, 1);

	वापस result;
पूर्ण

अटल पूर्णांक fiji_start_smu_in_non_protection_mode(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;

	/* रुको क्रम smc boot up */
	PHM_WAIT_VFPF_INसूचीECT_FIELD_UNEQUAL(hwmgr, SMC_IND,
			RCU_UC_EVENTS, boot_seq_करोne, 0);

	/* Clear firmware पूर्णांकerrupt enable flag */
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			ixFIRMWARE_FLAGS, 0);

	/* Assert reset */
	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			SMC_SYSCON_RESET_CNTL, rst_reg, 1);

	result = smu7_upload_smu_firmware_image(hwmgr);
	अगर (result)
		वापस result;

	/* Set smc inकाष्ठा start poपूर्णांक at 0x0 */
	smu7_program_jump_on_start(hwmgr);

	/* Enable घड़ी */
	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			SMC_SYSCON_CLOCK_CNTL_0, ck_disable, 0);

	/* De-निश्चित reset */
	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			SMC_SYSCON_RESET_CNTL, rst_reg, 0);

	/* Wait क्रम firmware to initialize */
	PHM_WAIT_VFPF_INसूचीECT_FIELD(hwmgr, SMC_IND,
			FIRMWARE_FLAGS, INTERRUPTS_ENABLED, 1);

	वापस result;
पूर्ण

अटल पूर्णांक fiji_start_avfs_btc(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;
	काष्ठा smu7_smumgr *smu_data = (काष्ठा smu7_smumgr *)(hwmgr->smu_backend);

	अगर (0 != smu_data->avfs_btc_param) अणु
		अगर (0 != smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_Perक्रमmBtc, smu_data->avfs_btc_param,
				शून्य)) अणु
			pr_info("[AVFS][Fiji_PerformBtc] PerformBTC SMU msg failed");
			result = -EINVAL;
		पूर्ण
	पूर्ण
	/* Soft-Reset to reset the engine beक्रमe loading uCode */
	 /* halt */
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmCP_MEC_CNTL, 0x50000000);
	/* reset everything */
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmGRBM_SOFT_RESET, 0xffffffff);
	/* clear reset */
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmGRBM_SOFT_RESET, 0);

	वापस result;
पूर्ण

अटल पूर्णांक fiji_setup_graphics_level_काष्ठाure(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक32_t vr_config;
	uपूर्णांक32_t table_start;
	uपूर्णांक32_t level_addr, vr_config_addr;
	uपूर्णांक32_t level_size = माप(avfs_graphics_level);

	PP_ASSERT_WITH_CODE(0 == smu7_पढ़ो_smc_sram_dword(hwmgr,
			SMU7_FIRMWARE_HEADER_LOCATION +
			दुरत्व(SMU73_Firmware_Header, DpmTable),
			&table_start, 0x40000),
			"[AVFS][Fiji_SetupGfxLvlStruct] SMU could not "
			"communicate starting address of DPM table",
			वापस -1;);

	/* Default value क्रम vr_config =
	 * VR_MERGED_WITH_VDDC + VR_STATIC_VOLTAGE(VDDCI) */
	vr_config = 0x01000500;   /* Real value:0x50001 */

	vr_config_addr = table_start +
			दुरत्व(SMU73_Discrete_DpmTable, VRConfig);

	PP_ASSERT_WITH_CODE(0 == smu7_copy_bytes_to_smc(hwmgr, vr_config_addr,
			(uपूर्णांक8_t *)&vr_config, माप(पूर्णांक32_t), 0x40000),
			"[AVFS][Fiji_SetupGfxLvlStruct] Problems copying "
			"vr_config value over to SMC",
			वापस -1;);

	level_addr = table_start + दुरत्व(SMU73_Discrete_DpmTable, GraphicsLevel);

	PP_ASSERT_WITH_CODE(0 == smu7_copy_bytes_to_smc(hwmgr, level_addr,
			(uपूर्णांक8_t *)(&avfs_graphics_level), level_size, 0x40000),
			"[AVFS][Fiji_SetupGfxLvlStruct] Copying of DPM table failed!",
			वापस -1;);

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_avfs_event_mgr(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (!hwmgr->avfs_supported)
		वापस 0;

	PP_ASSERT_WITH_CODE(0 == fiji_setup_graphics_level_काष्ठाure(hwmgr),
			"[AVFS][fiji_avfs_event_mgr] Could not Copy Graphics Level"
			" table over to SMU",
			वापस -EINVAL);
	PP_ASSERT_WITH_CODE(0 == smu7_setup_pwr_virus(hwmgr),
			"[AVFS][fiji_avfs_event_mgr] Could not setup "
			"Pwr Virus for AVFS ",
			वापस -EINVAL);
	PP_ASSERT_WITH_CODE(0 == fiji_start_avfs_btc(hwmgr),
			"[AVFS][fiji_avfs_event_mgr] Failure at "
			"fiji_start_avfs_btc. AVFS Disabled",
			वापस -EINVAL);

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_start_smu(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;
	काष्ठा fiji_smumgr *priv = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);

	/* Only start SMC अगर SMC RAM is not running */
	अगर (!smu7_is_smc_ram_running(hwmgr) && hwmgr->not_vf) अणु
		/* Check अगर SMU is running in रक्षित mode */
		अगर (0 == PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device,
				CGS_IND_REG__SMC,
				SMU_FIRMWARE, SMU_MODE)) अणु
			result = fiji_start_smu_in_non_protection_mode(hwmgr);
			अगर (result)
				वापस result;
		पूर्ण अन्यथा अणु
			result = fiji_start_smu_in_protection_mode(hwmgr);
			अगर (result)
				वापस result;
		पूर्ण
		अगर (fiji_avfs_event_mgr(hwmgr))
			hwmgr->avfs_supported = false;
	पूर्ण

	/* Setup SoftRegsStart here क्रम रेजिस्टर lookup in हाल
	 * DummyBackEnd is used and ProcessFirmwareHeader is not executed
	 */
	smu7_पढ़ो_smc_sram_dword(hwmgr,
			SMU7_FIRMWARE_HEADER_LOCATION +
			दुरत्व(SMU73_Firmware_Header, SoftRegisters),
			&(priv->smu7_data.soft_regs_start), 0x40000);

	result = smu7_request_smu_load_fw(hwmgr);

	वापस result;
पूर्ण

अटल bool fiji_is_hw_avfs_present(काष्ठा pp_hwmgr *hwmgr)
अणु

	uपूर्णांक32_t efuse = 0;

	अगर (!hwmgr->not_vf)
		वापस false;

	अगर (!atomctrl_पढ़ो_efuse(hwmgr, AVFS_EN_LSB, AVFS_EN_MSB,
			&efuse)) अणु
		अगर (efuse)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक fiji_smu_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा fiji_smumgr *fiji_priv = शून्य;

	fiji_priv = kzalloc(माप(काष्ठा fiji_smumgr), GFP_KERNEL);

	अगर (fiji_priv == शून्य)
		वापस -ENOMEM;

	hwmgr->smu_backend = fiji_priv;

	अगर (smu7_init(hwmgr)) अणु
		kमुक्त(fiji_priv);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_get_dependency_volt_by_clk(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table,
		uपूर्णांक32_t घड़ी, uपूर्णांक32_t *voltage, uपूर्णांक32_t *mvdd)
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
								VDDC_VDDCI_DELTA));
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
	अन्यथा अगर (dep_table->entries[i-1].vddci) अणु
		vddci = phm_find_बंदst_vddci(&(data->vddci_voltage_table),
				(dep_table->entries[i].vddc -
						VDDC_VDDCI_DELTA));
		*voltage |= (vddci * VOLTAGE_SCALE) << VDDCI_SHIFT;
	पूर्ण

	अगर (SMU7_VOLTAGE_CONTROL_NONE == data->mvdd_control)
		*mvdd = data->vbios_boot_state.mvdd_bootup_value * VOLTAGE_SCALE;
	अन्यथा अगर (dep_table->entries[i].mvdd)
		*mvdd = (uपूर्णांक32_t) dep_table->entries[i - 1].mvdd * VOLTAGE_SCALE;

	वापस 0;
पूर्ण


अटल uपूर्णांक16_t scale_fan_gain_settings(uपूर्णांक16_t raw_setting)
अणु
	uपूर्णांक32_t पंचांगp;
	पंचांगp = raw_setting * 4096 / 100;
	वापस (uपूर्णांक16_t)पंचांगp;
पूर्ण

अटल व्योम get_scl_sda_value(uपूर्णांक8_t line, uपूर्णांक8_t *scl, uपूर्णांक8_t *sda)
अणु
	चयन (line) अणु
	हाल SMU7_I2CLineID_DDC1:
		*scl = SMU7_I2C_DDC1CLK;
		*sda = SMU7_I2C_DDC1DATA;
		अवरोध;
	हाल SMU7_I2CLineID_DDC2:
		*scl = SMU7_I2C_DDC2CLK;
		*sda = SMU7_I2C_DDC2DATA;
		अवरोध;
	हाल SMU7_I2CLineID_DDC3:
		*scl = SMU7_I2C_DDC3CLK;
		*sda = SMU7_I2C_DDC3DATA;
		अवरोध;
	हाल SMU7_I2CLineID_DDC4:
		*scl = SMU7_I2C_DDC4CLK;
		*sda = SMU7_I2C_DDC4DATA;
		अवरोध;
	हाल SMU7_I2CLineID_DDC5:
		*scl = SMU7_I2C_DDC5CLK;
		*sda = SMU7_I2C_DDC5DATA;
		अवरोध;
	हाल SMU7_I2CLineID_DDC6:
		*scl = SMU7_I2C_DDC6CLK;
		*sda = SMU7_I2C_DDC6DATA;
		अवरोध;
	हाल SMU7_I2CLineID_SCLSDA:
		*scl = SMU7_I2C_SCL;
		*sda = SMU7_I2C_SDA;
		अवरोध;
	हाल SMU7_I2CLineID_DDCVGA:
		*scl = SMU7_I2C_DDCVGACLK;
		*sda = SMU7_I2C_DDCVGADATA;
		अवरोध;
	शेष:
		*scl = 0;
		*sda = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम fiji_initialize_घातer_tune_शेषs(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा  phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	अगर (table_info &&
			table_info->cac_dtp_table->usPowerTuneDataSetID <= POWERTUNE_DEFAULT_SET_MAX &&
			table_info->cac_dtp_table->usPowerTuneDataSetID)
		smu_data->घातer_tune_शेषs =
				&fiji_घातer_tune_data_set_array
				[table_info->cac_dtp_table->usPowerTuneDataSetID - 1];
	अन्यथा
		smu_data->घातer_tune_शेषs = &fiji_घातer_tune_data_set_array[0];

पूर्ण

अटल पूर्णांक fiji_populate_bapm_parameters_in_dpm_table(काष्ठा pp_hwmgr *hwmgr)
अणु

	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);
	स्थिर काष्ठा fiji_pt_शेषs *शेषs = smu_data->घातer_tune_शेषs;

	SMU73_Discrete_DpmTable  *dpm_table = &(smu_data->smc_state_table);

	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_cac_tdp_table *cac_dtp_table = table_info->cac_dtp_table;
	काष्ठा pp_advance_fan_control_parameters *fan_table =
			&hwmgr->thermal_controller.advanceFanControlParameters;
	uपूर्णांक8_t uc_scl, uc_sda;

	/* TDP number of fraction bits are changed from 8 to 7 क्रम Fiji
	 * as requested by SMC team
	 */
	dpm_table->DefaultTdp = PP_HOST_TO_SMC_US(
			(uपूर्णांक16_t)(cac_dtp_table->usTDP * 128));
	dpm_table->TargetTdp = PP_HOST_TO_SMC_US(
			(uपूर्णांक16_t)(cac_dtp_table->usTDP * 128));

	PP_ASSERT_WITH_CODE(cac_dtp_table->usTargetOperatingTemp <= 255,
			"Target Operating Temp is out of Range!",
			);

	dpm_table->GpuTjMax = (uपूर्णांक8_t)(cac_dtp_table->usTargetOperatingTemp);
	dpm_table->GpuTjHyst = 8;

	dpm_table->DTEAmbientTempBase = शेषs->DTEAmbientTempBase;

	/* The following are क्रम new Fiji Multi-input fan/thermal control */
	dpm_table->TemperatureLimitEdge = PP_HOST_TO_SMC_US(
			cac_dtp_table->usTargetOperatingTemp * 256);
	dpm_table->TemperatureLimitHotspot = PP_HOST_TO_SMC_US(
			cac_dtp_table->usTemperatureLimitHotspot * 256);
	dpm_table->TemperatureLimitLiquid1 = PP_HOST_TO_SMC_US(
			cac_dtp_table->usTemperatureLimitLiquid1 * 256);
	dpm_table->TemperatureLimitLiquid2 = PP_HOST_TO_SMC_US(
			cac_dtp_table->usTemperatureLimitLiquid2 * 256);
	dpm_table->TemperatureLimitVrVddc = PP_HOST_TO_SMC_US(
			cac_dtp_table->usTemperatureLimitVrVddc * 256);
	dpm_table->TemperatureLimitVrMvdd = PP_HOST_TO_SMC_US(
			cac_dtp_table->usTemperatureLimitVrMvdd * 256);
	dpm_table->TemperatureLimitPlx = PP_HOST_TO_SMC_US(
			cac_dtp_table->usTemperatureLimitPlx * 256);

	dpm_table->FanGainEdge = PP_HOST_TO_SMC_US(
			scale_fan_gain_settings(fan_table->usFanGainEdge));
	dpm_table->FanGainHotspot = PP_HOST_TO_SMC_US(
			scale_fan_gain_settings(fan_table->usFanGainHotspot));
	dpm_table->FanGainLiquid = PP_HOST_TO_SMC_US(
			scale_fan_gain_settings(fan_table->usFanGainLiquid));
	dpm_table->FanGainVrVddc = PP_HOST_TO_SMC_US(
			scale_fan_gain_settings(fan_table->usFanGainVrVddc));
	dpm_table->FanGainVrMvdd = PP_HOST_TO_SMC_US(
			scale_fan_gain_settings(fan_table->usFanGainVrMvdd));
	dpm_table->FanGainPlx = PP_HOST_TO_SMC_US(
			scale_fan_gain_settings(fan_table->usFanGainPlx));
	dpm_table->FanGainHbm = PP_HOST_TO_SMC_US(
			scale_fan_gain_settings(fan_table->usFanGainHbm));

	dpm_table->Liquid1_I2C_address = cac_dtp_table->ucLiquid1_I2C_address;
	dpm_table->Liquid2_I2C_address = cac_dtp_table->ucLiquid2_I2C_address;
	dpm_table->Vr_I2C_address = cac_dtp_table->ucVr_I2C_address;
	dpm_table->Plx_I2C_address = cac_dtp_table->ucPlx_I2C_address;

	get_scl_sda_value(cac_dtp_table->ucLiquid_I2C_Line, &uc_scl, &uc_sda);
	dpm_table->Liquid_I2C_LineSCL = uc_scl;
	dpm_table->Liquid_I2C_LineSDA = uc_sda;

	get_scl_sda_value(cac_dtp_table->ucVr_I2C_Line, &uc_scl, &uc_sda);
	dpm_table->Vr_I2C_LineSCL = uc_scl;
	dpm_table->Vr_I2C_LineSDA = uc_sda;

	get_scl_sda_value(cac_dtp_table->ucPlx_I2C_Line, &uc_scl, &uc_sda);
	dpm_table->Plx_I2C_LineSCL = uc_scl;
	dpm_table->Plx_I2C_LineSDA = uc_sda;

	वापस 0;
पूर्ण


अटल पूर्णांक fiji_populate_svi_load_line(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);
	स्थिर काष्ठा fiji_pt_शेषs *शेषs = smu_data->घातer_tune_शेषs;

	smu_data->घातer_tune_table.SviLoadLineEn = शेषs->SviLoadLineEn;
	smu_data->घातer_tune_table.SviLoadLineVddC = शेषs->SviLoadLineVddC;
	smu_data->घातer_tune_table.SviLoadLineTrimVddC = 3;
	smu_data->घातer_tune_table.SviLoadLineOffsetVddC = 0;

	वापस 0;
पूर्ण


अटल पूर्णांक fiji_populate_tdc_limit(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक16_t tdc_limit;
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	स्थिर काष्ठा fiji_pt_शेषs *शेषs = smu_data->घातer_tune_शेषs;

	/* TDC number of fraction bits are changed from 8 to 7
	 * क्रम Fiji as requested by SMC team
	 */
	tdc_limit = (uपूर्णांक16_t)(table_info->cac_dtp_table->usTDC * 128);
	smu_data->घातer_tune_table.TDC_VDDC_PkgLimit =
			CONVERT_FROM_HOST_TO_SMC_US(tdc_limit);
	smu_data->घातer_tune_table.TDC_VDDC_ThrottleReleaseLimitPerc =
			शेषs->TDC_VDDC_ThrottleReleaseLimitPerc;
	smu_data->घातer_tune_table.TDC_MAWt = शेषs->TDC_MAWt;

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_populate_dw8(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t fuse_table_offset)
अणु
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);
	स्थिर काष्ठा fiji_pt_शेषs *शेषs = smu_data->घातer_tune_शेषs;
	uपूर्णांक32_t temp;

	अगर (smu7_पढ़ो_smc_sram_dword(hwmgr,
			fuse_table_offset +
			दुरत्व(SMU73_Discrete_PmFuses, TdcWaterfallCtl),
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

अटल पूर्णांक fiji_populate_temperature_scaler(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक i;
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);

	/* Currently not used. Set all to zero. */
	क्रम (i = 0; i < 16; i++)
		smu_data->घातer_tune_table.LPMLTemperatureScaler[i] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_populate_fuzzy_fan(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);

	अगर ((hwmgr->thermal_controller.advanceFanControlParameters.
			usFanOutputSensitivity & (1 << 15)) ||
			0 == hwmgr->thermal_controller.advanceFanControlParameters.
			usFanOutputSensitivity)
		hwmgr->thermal_controller.advanceFanControlParameters.
		usFanOutputSensitivity = hwmgr->thermal_controller.
			advanceFanControlParameters.usDefaultFanOutputSensitivity;

	smu_data->घातer_tune_table.FuzzyFan_PwmSetDelta =
			PP_HOST_TO_SMC_US(hwmgr->thermal_controller.
					advanceFanControlParameters.usFanOutputSensitivity);
	वापस 0;
पूर्ण

अटल पूर्णांक fiji_populate_gnb_lpml(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक i;
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);

	/* Currently not used. Set all to zero. */
	क्रम (i = 0; i < 16; i++)
		smu_data->घातer_tune_table.GnbLPML[i] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_populate_bapm_vddc_base_leakage_sidd(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	uपूर्णांक16_t HiSidd = smu_data->घातer_tune_table.BapmVddCBaseLeakageHiSidd;
	uपूर्णांक16_t LoSidd = smu_data->घातer_tune_table.BapmVddCBaseLeakageLoSidd;
	काष्ठा phm_cac_tdp_table *cac_table = table_info->cac_dtp_table;

	HiSidd = (uपूर्णांक16_t)(cac_table->usHighCACLeakage / 100 * 256);
	LoSidd = (uपूर्णांक16_t)(cac_table->usLowCACLeakage / 100 * 256);

	smu_data->घातer_tune_table.BapmVddCBaseLeakageHiSidd =
			CONVERT_FROM_HOST_TO_SMC_US(HiSidd);
	smu_data->घातer_tune_table.BapmVddCBaseLeakageLoSidd =
			CONVERT_FROM_HOST_TO_SMC_US(LoSidd);

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_populate_pm_fuses(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t pm_fuse_table_offset;
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_PowerContainment)) अणु
		अगर (smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU7_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU73_Firmware_Header, PmFuseTable),
				&pm_fuse_table_offset, SMC_RAM_END))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to get pm_fuse_table_offset Failed!",
					वापस -EINVAL);

		/* DW6 */
		अगर (fiji_populate_svi_load_line(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate SviLoadLine Failed!",
					वापस -EINVAL);
		/* DW7 */
		अगर (fiji_populate_tdc_limit(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate TDCLimit Failed!", वापस -EINVAL);
		/* DW8 */
		अगर (fiji_populate_dw8(hwmgr, pm_fuse_table_offset))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate TdcWaterfallCtl, "
					"LPMLTemperature Min and Max Failed!",
					वापस -EINVAL);

		/* DW9-DW12 */
		अगर (0 != fiji_populate_temperature_scaler(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate LPMLTemperatureScaler Failed!",
					वापस -EINVAL);

		/* DW13-DW14 */
		अगर (fiji_populate_fuzzy_fan(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate Fuzzy Fan Control parameters Failed!",
					वापस -EINVAL);

		/* DW15-DW18 */
		अगर (fiji_populate_gnb_lpml(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate GnbLPML Failed!",
					वापस -EINVAL);

		/* DW20 */
		अगर (fiji_populate_bapm_vddc_base_leakage_sidd(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate BapmVddCBaseLeakage Hi and Lo "
					"Sidd Failed!", वापस -EINVAL);

		अगर (smu7_copy_bytes_to_smc(hwmgr, pm_fuse_table_offset,
				(uपूर्णांक8_t *)&smu_data->घातer_tune_table,
				माप(काष्ठा SMU73_Discrete_PmFuses), SMC_RAM_END))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to download PmFuseTable Failed!",
					वापस -EINVAL);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fiji_populate_cac_table(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU73_Discrete_DpmTable *table)
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
			convert_to_vid(lookup_table->entries[index].us_cac_high);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_populate_smc_voltage_tables(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU73_Discrete_DpmTable *table)
अणु
	पूर्णांक result;

	result = fiji_populate_cac_table(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
			"can not populate CAC voltage tables to SMC",
			वापस -EINVAL);

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_populate_ulv_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU73_Discrete_Ulv *state)
अणु
	पूर्णांक result = 0;

	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	state->CcPwrDynRm = 0;
	state->CcPwrDynRm1 = 0;

	state->VddcOffset = (uपूर्णांक16_t) table_info->us_ulv_voltage_offset;
	state->VddcOffsetVid = (uपूर्णांक8_t)(table_info->us_ulv_voltage_offset *
			VOLTAGE_VID_OFFSET_SCALE2 / VOLTAGE_VID_OFFSET_SCALE1);

	state->VddcPhase = 1;

	अगर (!result) अणु
		CONVERT_FROM_HOST_TO_SMC_UL(state->CcPwrDynRm);
		CONVERT_FROM_HOST_TO_SMC_UL(state->CcPwrDynRm1);
		CONVERT_FROM_HOST_TO_SMC_US(state->VddcOffset);
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक fiji_populate_ulv_state(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU73_Discrete_DpmTable *table)
अणु
	वापस fiji_populate_ulv_level(hwmgr, &table->Ulv);
पूर्ण

अटल पूर्णांक fiji_populate_smc_link_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU73_Discrete_DpmTable *table)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_dpm_table *dpm_table = &data->dpm_table;
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);
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
	data->dpm_level_enable_mask.pcie_dpm_enable_mask =
			phm_get_dpm_level_enable_mask_value(&dpm_table->pcie_speed_table);

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_calculate_sclk_params(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी, काष्ठा SMU73_Discrete_GraphicsLevel *sclk)
अणु
	स्थिर काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा pp_atomctrl_घड़ी_भागiders_vi भागiders;
	uपूर्णांक32_t spll_func_cntl            = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL;
	uपूर्णांक32_t spll_func_cntl_3          = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL_3;
	uपूर्णांक32_t spll_func_cntl_4          = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL_4;
	uपूर्णांक32_t cg_spll_spपढ़ो_spectrum   = data->घड़ी_रेजिस्टरs.vCG_SPLL_SPREAD_SPECTRUM;
	uपूर्णांक32_t cg_spll_spपढ़ो_spectrum_2 = data->घड़ी_रेजिस्टरs.vCG_SPLL_SPREAD_SPECTRUM_2;
	uपूर्णांक32_t ref_घड़ी;
	uपूर्णांक32_t ref_भागider;
	uपूर्णांक32_t fbभाग;
	पूर्णांक result;

	/* get the engine घड़ी भागiders क्रम this घड़ी value */
	result = atomctrl_get_engine_pll_भागiders_vi(hwmgr, घड़ी,  &भागiders);

	PP_ASSERT_WITH_CODE(result == 0,
			"Error retrieving Engine Clock dividers from VBIOS.",
			वापस result);

	/* To get FBDIV we need to multiply this by 16384 and भागide it by Fref. */
	ref_घड़ी = atomctrl_get_reference_घड़ी(hwmgr);
	ref_भागider = 1 + भागiders.uc_pll_ref_भाग;

	/* low 14 bits is fraction and high 12 bits is भागider */
	fbभाग = भागiders.ul_fb_भाग.ul_fb_भागider & 0x3FFFFFF;

	/* SPLL_FUNC_CNTL setup */
	spll_func_cntl = PHM_SET_FIELD(spll_func_cntl, CG_SPLL_FUNC_CNTL,
			SPLL_REF_DIV, भागiders.uc_pll_ref_भाग);
	spll_func_cntl = PHM_SET_FIELD(spll_func_cntl, CG_SPLL_FUNC_CNTL,
			SPLL_PDIV_A,  भागiders.uc_pll_post_भाग);

	/* SPLL_FUNC_CNTL_3 setup*/
	spll_func_cntl_3 = PHM_SET_FIELD(spll_func_cntl_3, CG_SPLL_FUNC_CNTL_3,
			SPLL_FB_DIV, fbभाग);

	/* set to use fractional accumulation*/
	spll_func_cntl_3 = PHM_SET_FIELD(spll_func_cntl_3, CG_SPLL_FUNC_CNTL_3,
			SPLL_DITHEN, 1);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_EngineSpपढ़ोSpectrumSupport)) अणु
		काष्ठा pp_atomctrl_पूर्णांकernal_ss_info ssInfo;

		uपूर्णांक32_t vco_freq = घड़ी * भागiders.uc_pll_post_भाग;
		अगर (!atomctrl_get_engine_घड़ी_spपढ़ो_spectrum(hwmgr,
				vco_freq, &ssInfo)) अणु
			/*
			 * ss_info.speed_spectrum_percentage -- in unit of 0.01%
			 * ss_info.speed_spectrum_rate -- in unit of khz
			 *
			 * clks = reference_घड़ी * 10 / (REFDIV + 1) / speed_spectrum_rate / 2
			 */
			uपूर्णांक32_t clk_s = ref_घड़ी * 5 /
					(ref_भागider * ssInfo.speed_spectrum_rate);
			/* clkv = 2 * D * fbभाग / NS */
			uपूर्णांक32_t clk_v = 4 * ssInfo.speed_spectrum_percentage *
					fbभाग / (clk_s * 10000);

			cg_spll_spपढ़ो_spectrum = PHM_SET_FIELD(cg_spll_spपढ़ो_spectrum,
					CG_SPLL_SPREAD_SPECTRUM, CLKS, clk_s);
			cg_spll_spपढ़ो_spectrum = PHM_SET_FIELD(cg_spll_spपढ़ो_spectrum,
					CG_SPLL_SPREAD_SPECTRUM, SSEN, 1);
			cg_spll_spपढ़ो_spectrum_2 = PHM_SET_FIELD(cg_spll_spपढ़ो_spectrum_2,
					CG_SPLL_SPREAD_SPECTRUM_2, CLKV, clk_v);
		पूर्ण
	पूर्ण

	sclk->SclkFrequency        = घड़ी;
	sclk->CgSpllFuncCntl3      = spll_func_cntl_3;
	sclk->CgSpllFuncCntl4      = spll_func_cntl_4;
	sclk->SpllSpपढ़ोSpectrum   = cg_spll_spपढ़ो_spectrum;
	sclk->SpllSpपढ़ोSpectrum2  = cg_spll_spपढ़ो_spectrum_2;
	sclk->SclkDid              = (uपूर्णांक8_t)भागiders.pll_post_भागider;

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_populate_single_graphic_level(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी, काष्ठा SMU73_Discrete_GraphicsLevel *level)
अणु
	पूर्णांक result;
	/* PP_Clocks minClocks; */
	uपूर्णांक32_t mvdd;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	phm_ppt_v1_घड़ी_voltage_dependency_table *vdd_dep_table = शून्य;

	result = fiji_calculate_sclk_params(hwmgr, घड़ी, level);

	अगर (hwmgr->od_enabled)
		vdd_dep_table = (phm_ppt_v1_घड़ी_voltage_dependency_table *)&data->odn_dpm_table.vdd_dependency_on_sclk;
	अन्यथा
		vdd_dep_table = table_info->vdd_dep_on_sclk;

	/* populate graphics levels */
	result = fiji_get_dependency_volt_by_clk(hwmgr,
			vdd_dep_table, घड़ी,
			(uपूर्णांक32_t *)(&level->MinVoltage), &mvdd);
	PP_ASSERT_WITH_CODE((0 == result),
			"can not find VDDC voltage value for "
			"VDDC engine clock dependency table",
			वापस result);

	level->SclkFrequency = घड़ी;
	level->ActivityLevel = data->current_profile_setting.sclk_activity;
	level->CcPwrDynRm = 0;
	level->CcPwrDynRm1 = 0;
	level->EnabledForActivity = 0;
	level->EnabledForThrottle = 1;
	level->UpHyst = data->current_profile_setting.sclk_up_hyst;
	level->DownHyst = data->current_profile_setting.sclk_करोwn_hyst;
	level->VoltageDownHyst = 0;
	level->PowerThrottle = 0;

	data->display_timing.min_घड़ी_in_sr = hwmgr->display_config->min_core_set_घड़ी_in_sr;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_SclkDeepSleep))
		level->DeepSleepDivId = smu7_get_sleep_भागider_id_from_घड़ी(घड़ी,
								hwmgr->display_config->min_core_set_घड़ी_in_sr);


	/* Default to slow, highest DPM level will be
	 * set to PPSMC_DISPLAY_WATERMARK_LOW later.
	 */
	level->DisplayWatermark = PPSMC_DISPLAY_WATERMARK_LOW;

	CONVERT_FROM_HOST_TO_SMC_UL(level->MinVoltage);
	CONVERT_FROM_HOST_TO_SMC_UL(level->SclkFrequency);
	CONVERT_FROM_HOST_TO_SMC_US(level->ActivityLevel);
	CONVERT_FROM_HOST_TO_SMC_UL(level->CgSpllFuncCntl3);
	CONVERT_FROM_HOST_TO_SMC_UL(level->CgSpllFuncCntl4);
	CONVERT_FROM_HOST_TO_SMC_UL(level->SpllSpपढ़ोSpectrum);
	CONVERT_FROM_HOST_TO_SMC_UL(level->SpllSpपढ़ोSpectrum2);
	CONVERT_FROM_HOST_TO_SMC_UL(level->CcPwrDynRm);
	CONVERT_FROM_HOST_TO_SMC_UL(level->CcPwrDynRm1);

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_populate_all_graphic_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);

	काष्ठा smu7_dpm_table *dpm_table = &data->dpm_table;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_pcie_table *pcie_table = table_info->pcie_table;
	uपूर्णांक8_t pcie_entry_cnt = (uपूर्णांक8_t) data->dpm_table.pcie_speed_table.count;
	पूर्णांक result = 0;
	uपूर्णांक32_t array = smu_data->smu7_data.dpm_table_start +
			दुरत्व(SMU73_Discrete_DpmTable, GraphicsLevel);
	uपूर्णांक32_t array_size = माप(काष्ठा SMU73_Discrete_GraphicsLevel) *
			SMU73_MAX_LEVELS_GRAPHICS;
	काष्ठा SMU73_Discrete_GraphicsLevel *levels =
			smu_data->smc_state_table.GraphicsLevel;
	uपूर्णांक32_t i, max_entry;
	uपूर्णांक8_t hightest_pcie_level_enabled = 0,
			lowest_pcie_level_enabled = 0,
			mid_pcie_level_enabled = 0,
			count = 0;

	क्रम (i = 0; i < dpm_table->sclk_table.count; i++) अणु
		result = fiji_populate_single_graphic_level(hwmgr,
				dpm_table->sclk_table.dpm_levels[i].value,
				&levels[i]);
		अगर (result)
			वापस result;

		/* Making sure only DPM level 0-1 have Deep Sleep Div ID populated. */
		अगर (i > 1)
			levels[i].DeepSleepDivId = 0;
	पूर्ण

	/* Only enable level 0 क्रम now.*/
	levels[0].EnabledForActivity = 1;

	/* set highest level watermark to high */
	levels[dpm_table->sclk_table.count - 1].DisplayWatermark =
			PPSMC_DISPLAY_WATERMARK_HIGH;

	smu_data->smc_state_table.GraphicsDpmLevelCount =
			(uपूर्णांक8_t)dpm_table->sclk_table.count;
	data->dpm_level_enable_mask.sclk_dpm_enable_mask =
			phm_get_dpm_level_enable_mask_value(&dpm_table->sclk_table);

	अगर (pcie_table != शून्य) अणु
		PP_ASSERT_WITH_CODE((1 <= pcie_entry_cnt),
				"There must be 1 or more PCIE levels defined in PPTable.",
				वापस -EINVAL);
		max_entry = pcie_entry_cnt - 1;
		क्रम (i = 0; i < dpm_table->sclk_table.count; i++)
			levels[i].pcieDpmLevel =
					(uपूर्णांक8_t) ((i < max_entry) ? i : max_entry);
	पूर्ण अन्यथा अणु
		जबतक (data->dpm_level_enable_mask.pcie_dpm_enable_mask &&
				((data->dpm_level_enable_mask.pcie_dpm_enable_mask &
						(1 << (hightest_pcie_level_enabled + 1))) != 0))
			hightest_pcie_level_enabled++;

		जबतक (data->dpm_level_enable_mask.pcie_dpm_enable_mask &&
				((data->dpm_level_enable_mask.pcie_dpm_enable_mask &
						(1 << lowest_pcie_level_enabled)) == 0))
			lowest_pcie_level_enabled++;

		जबतक ((count < hightest_pcie_level_enabled) &&
				((data->dpm_level_enable_mask.pcie_dpm_enable_mask &
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


/*
 * MCLK Frequency Ratio
 * SEQ_CG_RESP  Bit[31:24] - 0x0
 * Bit[27:24] \96 DDR3 Frequency ratio
 * 0x0 <= 100MHz,       450 < 0x8 <= 500MHz
 * 100 < 0x1 <= 150MHz,       500 < 0x9 <= 550MHz
 * 150 < 0x2 <= 200MHz,       550 < 0xA <= 600MHz
 * 200 < 0x3 <= 250MHz,       600 < 0xB <= 650MHz
 * 250 < 0x4 <= 300MHz,       650 < 0xC <= 700MHz
 * 300 < 0x5 <= 350MHz,       700 < 0xD <= 750MHz
 * 350 < 0x6 <= 400MHz,       750 < 0xE <= 800MHz
 * 400 < 0x7 <= 450MHz,       800 < 0xF
 */
अटल uपूर्णांक8_t fiji_get_mclk_frequency_ratio(uपूर्णांक32_t mem_घड़ी)
अणु
	अगर (mem_घड़ी <= 10000)
		वापस 0x0;
	अगर (mem_घड़ी <= 15000)
		वापस 0x1;
	अगर (mem_घड़ी <= 20000)
		वापस 0x2;
	अगर (mem_घड़ी <= 25000)
		वापस 0x3;
	अगर (mem_घड़ी <= 30000)
		वापस 0x4;
	अगर (mem_घड़ी <= 35000)
		वापस 0x5;
	अगर (mem_घड़ी <= 40000)
		वापस 0x6;
	अगर (mem_घड़ी <= 45000)
		वापस 0x7;
	अगर (mem_घड़ी <= 50000)
		वापस 0x8;
	अगर (mem_घड़ी <= 55000)
		वापस 0x9;
	अगर (mem_घड़ी <= 60000)
		वापस 0xa;
	अगर (mem_घड़ी <= 65000)
		वापस 0xb;
	अगर (mem_घड़ी <= 70000)
		वापस 0xc;
	अगर (mem_घड़ी <= 75000)
		वापस 0xd;
	अगर (mem_घड़ी <= 80000)
		वापस 0xe;
	/* mem_घड़ी > 800MHz */
	वापस 0xf;
पूर्ण

अटल पूर्णांक fiji_calculate_mclk_params(काष्ठा pp_hwmgr *hwmgr,
    uपूर्णांक32_t घड़ी, काष्ठा SMU73_Discrete_MemoryLevel *mclk)
अणु
	काष्ठा pp_atomctrl_memory_घड़ी_param mem_param;
	पूर्णांक result;

	result = atomctrl_get_memory_pll_भागiders_vi(hwmgr, घड़ी, &mem_param);
	PP_ASSERT_WITH_CODE((0 == result),
			"Failed to get Memory PLL Dividers.",
			);

	/* Save the result data to outpupt memory level काष्ठाure */
	mclk->MclkFrequency   = घड़ी;
	mclk->MclkDivider     = (uपूर्णांक8_t)mem_param.mpll_post_भागider;
	mclk->FreqRange       = fiji_get_mclk_frequency_ratio(घड़ी);

	वापस result;
पूर्ण

अटल पूर्णांक fiji_populate_single_memory_level(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी, काष्ठा SMU73_Discrete_MemoryLevel *mem_level)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	पूर्णांक result = 0;
	uपूर्णांक32_t mclk_stutter_mode_threshold = 60000;
	phm_ppt_v1_घड़ी_voltage_dependency_table *vdd_dep_table = शून्य;

	अगर (hwmgr->od_enabled)
		vdd_dep_table = (phm_ppt_v1_घड़ी_voltage_dependency_table *)&data->odn_dpm_table.vdd_dependency_on_mclk;
	अन्यथा
		vdd_dep_table = table_info->vdd_dep_on_mclk;

	अगर (vdd_dep_table) अणु
		result = fiji_get_dependency_volt_by_clk(hwmgr,
				vdd_dep_table, घड़ी,
				(uपूर्णांक32_t *)(&mem_level->MinVoltage), &mem_level->MinMvdd);
		PP_ASSERT_WITH_CODE((0 == result),
				"can not find MinVddc voltage value from memory "
				"VDDC voltage dependency table", वापस result);
	पूर्ण

	mem_level->EnabledForThrottle = 1;
	mem_level->EnabledForActivity = 0;
	mem_level->UpHyst = data->current_profile_setting.mclk_up_hyst;
	mem_level->DownHyst = data->current_profile_setting.mclk_करोwn_hyst;
	mem_level->VoltageDownHyst = 0;
	mem_level->ActivityLevel = data->current_profile_setting.mclk_activity;
	mem_level->StutterEnable = false;

	mem_level->DisplayWatermark = PPSMC_DISPLAY_WATERMARK_LOW;

	/* enable stutter mode अगर all the follow condition applied
	 * PECI_GetNumberOfActiveDisplays(hwmgr->pPECI,
	 * &(data->DisplayTiming.numExistingDisplays));
	 */
	data->display_timing.num_existing_displays = hwmgr->display_config->num_display;
	data->display_timing.vrefresh = hwmgr->display_config->vrefresh;

	अगर (mclk_stutter_mode_threshold &&
		(घड़ी <= mclk_stutter_mode_threshold) &&
		(!data->is_uvd_enabled) &&
		(PHM_READ_FIELD(hwmgr->device, DPG_PIPE_STUTTER_CONTROL,
				STUTTER_ENABLE) & 0x1))
		mem_level->StutterEnable = true;

	result = fiji_calculate_mclk_params(hwmgr, घड़ी, mem_level);
	अगर (!result) अणु
		CONVERT_FROM_HOST_TO_SMC_UL(mem_level->MinMvdd);
		CONVERT_FROM_HOST_TO_SMC_UL(mem_level->MclkFrequency);
		CONVERT_FROM_HOST_TO_SMC_US(mem_level->ActivityLevel);
		CONVERT_FROM_HOST_TO_SMC_UL(mem_level->MinVoltage);
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक fiji_populate_all_memory_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);
	काष्ठा smu7_dpm_table *dpm_table = &data->dpm_table;
	पूर्णांक result;
	/* populate MCLK dpm table to SMU7 */
	uपूर्णांक32_t array = smu_data->smu7_data.dpm_table_start +
			दुरत्व(SMU73_Discrete_DpmTable, MemoryLevel);
	uपूर्णांक32_t array_size = माप(SMU73_Discrete_MemoryLevel) *
			SMU73_MAX_LEVELS_MEMORY;
	काष्ठा SMU73_Discrete_MemoryLevel *levels =
			smu_data->smc_state_table.MemoryLevel;
	uपूर्णांक32_t i;

	क्रम (i = 0; i < dpm_table->mclk_table.count; i++) अणु
		PP_ASSERT_WITH_CODE((0 != dpm_table->mclk_table.dpm_levels[i].value),
				"can not populate memory level as memory clock is zero",
				वापस -EINVAL);
		result = fiji_populate_single_memory_level(hwmgr,
				dpm_table->mclk_table.dpm_levels[i].value,
				&levels[i]);
		अगर (result)
			वापस result;
	पूर्ण

	/* Only enable level 0 क्रम now. */
	levels[0].EnabledForActivity = 1;

	/* in order to prevent MC activity from stutter mode to push DPM up.
	 * the UVD change complements this by putting the MCLK in
	 * a higher state by शेष such that we are not effected by
	 * up threshold or and MCLK DPM latency.
	 */
	levels[0].ActivityLevel = (uपूर्णांक16_t)data->mclk_dpm0_activity_target;
	CONVERT_FROM_HOST_TO_SMC_US(levels[0].ActivityLevel);

	smu_data->smc_state_table.MemoryDpmLevelCount =
			(uपूर्णांक8_t)dpm_table->mclk_table.count;
	data->dpm_level_enable_mask.mclk_dpm_enable_mask =
			phm_get_dpm_level_enable_mask_value(&dpm_table->mclk_table);
	/* set highest level watermark to high */
	levels[dpm_table->mclk_table.count - 1].DisplayWatermark =
			PPSMC_DISPLAY_WATERMARK_HIGH;

	/* level count will send to smc once at init smc table and never change */
	result = smu7_copy_bytes_to_smc(hwmgr, array, (uपूर्णांक8_t *)levels,
			(uपूर्णांक32_t)array_size, SMC_RAM_END);

	वापस result;
पूर्ण

अटल पूर्णांक fiji_populate_mvdd_value(काष्ठा pp_hwmgr *hwmgr,
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

अटल पूर्णांक fiji_populate_smc_acpi_level(काष्ठा pp_hwmgr *hwmgr,
		SMU73_Discrete_DpmTable *table)
अणु
	पूर्णांक result = 0;
	स्थिर काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा pp_atomctrl_घड़ी_भागiders_vi भागiders;
	SMIO_Pattern vol_level;
	uपूर्णांक32_t mvdd;
	uपूर्णांक16_t us_mvdd;
	uपूर्णांक32_t spll_func_cntl    = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL;
	uपूर्णांक32_t spll_func_cntl_2  = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL_2;

	table->ACPILevel.Flags &= ~PPSMC_SWSTATE_FLAG_DC;

	अगर (!data->sclk_dpm_key_disabled) अणु
		/* Get MinVoltage and Frequency from DPM0,
		 * alपढ़ोy converted to SMC_UL */
		table->ACPILevel.SclkFrequency =
				data->dpm_table.sclk_table.dpm_levels[0].value;
		result = fiji_get_dependency_volt_by_clk(hwmgr,
				table_info->vdd_dep_on_sclk,
				table->ACPILevel.SclkFrequency,
				(uपूर्णांक32_t *)(&table->ACPILevel.MinVoltage), &mvdd);
		PP_ASSERT_WITH_CODE((0 == result),
				"Cannot find ACPI VDDC voltage value " \
				"in Clock Dependency Table",
				);
	पूर्ण अन्यथा अणु
		table->ACPILevel.SclkFrequency =
				data->vbios_boot_state.sclk_bootup_value;
		table->ACPILevel.MinVoltage =
				data->vbios_boot_state.vddc_bootup_value * VOLTAGE_SCALE;
	पूर्ण

	/* get the engine घड़ी भागiders क्रम this घड़ी value */
	result = atomctrl_get_engine_pll_भागiders_vi(hwmgr,
			table->ACPILevel.SclkFrequency,  &भागiders);
	PP_ASSERT_WITH_CODE(result == 0,
			"Error retrieving Engine Clock dividers from VBIOS.",
			वापस result);

	table->ACPILevel.SclkDid = (uपूर्णांक8_t)भागiders.pll_post_भागider;
	table->ACPILevel.DisplayWatermark = PPSMC_DISPLAY_WATERMARK_LOW;
	table->ACPILevel.DeepSleepDivId = 0;

	spll_func_cntl = PHM_SET_FIELD(spll_func_cntl, CG_SPLL_FUNC_CNTL,
			SPLL_PWRON, 0);
	spll_func_cntl = PHM_SET_FIELD(spll_func_cntl, CG_SPLL_FUNC_CNTL,
			SPLL_RESET, 1);
	spll_func_cntl_2 = PHM_SET_FIELD(spll_func_cntl_2, CG_SPLL_FUNC_CNTL_2,
			SCLK_MUX_SEL, 4);

	table->ACPILevel.CgSpllFuncCntl = spll_func_cntl;
	table->ACPILevel.CgSpllFuncCntl2 = spll_func_cntl_2;
	table->ACPILevel.CgSpllFuncCntl3 = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL_3;
	table->ACPILevel.CgSpllFuncCntl4 = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL_4;
	table->ACPILevel.SpllSpपढ़ोSpectrum = data->घड़ी_रेजिस्टरs.vCG_SPLL_SPREAD_SPECTRUM;
	table->ACPILevel.SpllSpपढ़ोSpectrum2 = data->घड़ी_रेजिस्टरs.vCG_SPLL_SPREAD_SPECTRUM_2;
	table->ACPILevel.CcPwrDynRm = 0;
	table->ACPILevel.CcPwrDynRm1 = 0;

	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.Flags);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.SclkFrequency);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.MinVoltage);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CgSpllFuncCntl);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CgSpllFuncCntl2);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CgSpllFuncCntl3);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CgSpllFuncCntl4);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.SpllSpपढ़ोSpectrum);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.SpllSpपढ़ोSpectrum2);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CcPwrDynRm);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CcPwrDynRm1);

	अगर (!data->mclk_dpm_key_disabled) अणु
		/* Get MinVoltage and Frequency from DPM0, alपढ़ोy converted to SMC_UL */
		table->MemoryACPILevel.MclkFrequency =
				data->dpm_table.mclk_table.dpm_levels[0].value;
		result = fiji_get_dependency_volt_by_clk(hwmgr,
				table_info->vdd_dep_on_mclk,
				table->MemoryACPILevel.MclkFrequency,
			(uपूर्णांक32_t *)(&table->MemoryACPILevel.MinVoltage), &mvdd);
		PP_ASSERT_WITH_CODE((0 == result),
				"Cannot find ACPI VDDCI voltage value in Clock Dependency Table",
				);
	पूर्ण अन्यथा अणु
		table->MemoryACPILevel.MclkFrequency =
				data->vbios_boot_state.mclk_bootup_value;
		table->MemoryACPILevel.MinVoltage =
				data->vbios_boot_state.vddci_bootup_value * VOLTAGE_SCALE;
	पूर्ण

	us_mvdd = 0;
	अगर ((SMU7_VOLTAGE_CONTROL_NONE == data->mvdd_control) ||
			(data->mclk_dpm_key_disabled))
		us_mvdd = data->vbios_boot_state.mvdd_bootup_value;
	अन्यथा अणु
		अगर (!fiji_populate_mvdd_value(hwmgr,
				data->dpm_table.mclk_table.dpm_levels[0].value,
				&vol_level))
			us_mvdd = vol_level.Voltage;
	पूर्ण

	table->MemoryACPILevel.MinMvdd =
			PP_HOST_TO_SMC_UL(us_mvdd * VOLTAGE_SCALE);

	table->MemoryACPILevel.EnabledForThrottle = 0;
	table->MemoryACPILevel.EnabledForActivity = 0;
	table->MemoryACPILevel.UpHyst = 0;
	table->MemoryACPILevel.DownHyst = 100;
	table->MemoryACPILevel.VoltageDownHyst = 0;
	table->MemoryACPILevel.ActivityLevel =
			PP_HOST_TO_SMC_US(data->current_profile_setting.mclk_activity);

	table->MemoryACPILevel.StutterEnable = false;
	CONVERT_FROM_HOST_TO_SMC_UL(table->MemoryACPILevel.MclkFrequency);
	CONVERT_FROM_HOST_TO_SMC_UL(table->MemoryACPILevel.MinVoltage);

	वापस result;
पूर्ण

अटल पूर्णांक fiji_populate_smc_vce_level(काष्ठा pp_hwmgr *hwmgr,
		SMU73_Discrete_DpmTable *table)
अणु
	पूर्णांक result = -EINVAL;
	uपूर्णांक8_t count;
	काष्ठा pp_atomctrl_घड़ी_भागiders_vi भागiders;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_mm_घड़ी_voltage_dependency_table *mm_table =
			table_info->mm_dep_table;

	table->VceLevelCount = (uपूर्णांक8_t)(mm_table->count);
	table->VceBootLevel = 0;

	क्रम (count = 0; count < table->VceLevelCount; count++) अणु
		table->VceLevel[count].Frequency = mm_table->entries[count].eclk;
		table->VceLevel[count].MinVoltage = 0;
		table->VceLevel[count].MinVoltage |=
				(mm_table->entries[count].vddc * VOLTAGE_SCALE) << VDDC_SHIFT;
		table->VceLevel[count].MinVoltage |=
				((mm_table->entries[count].vddc - VDDC_VDDCI_DELTA) *
						VOLTAGE_SCALE) << VDDCI_SHIFT;
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

अटल पूर्णांक fiji_populate_smc_acp_level(काष्ठा pp_hwmgr *hwmgr,
		SMU73_Discrete_DpmTable *table)
अणु
	पूर्णांक result = -EINVAL;
	uपूर्णांक8_t count;
	काष्ठा pp_atomctrl_घड़ी_भागiders_vi भागiders;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_mm_घड़ी_voltage_dependency_table *mm_table =
			table_info->mm_dep_table;

	table->AcpLevelCount = (uपूर्णांक8_t)(mm_table->count);
	table->AcpBootLevel = 0;

	क्रम (count = 0; count < table->AcpLevelCount; count++) अणु
		table->AcpLevel[count].Frequency = mm_table->entries[count].aclk;
		table->AcpLevel[count].MinVoltage |= (mm_table->entries[count].vddc *
				VOLTAGE_SCALE) << VDDC_SHIFT;
		table->AcpLevel[count].MinVoltage |= ((mm_table->entries[count].vddc -
				VDDC_VDDCI_DELTA) * VOLTAGE_SCALE) << VDDCI_SHIFT;
		table->AcpLevel[count].MinVoltage |= 1 << PHASES_SHIFT;

		/* retrieve भागider value क्रम VBIOS */
		result = atomctrl_get_dfs_pll_भागiders_vi(hwmgr,
				table->AcpLevel[count].Frequency, &भागiders);
		PP_ASSERT_WITH_CODE((0 == result),
				"can not find divide id for engine clock", वापस result);

		table->AcpLevel[count].Divider = (uपूर्णांक8_t)भागiders.pll_post_भागider;

		CONVERT_FROM_HOST_TO_SMC_UL(table->AcpLevel[count].Frequency);
		CONVERT_FROM_HOST_TO_SMC_UL(table->AcpLevel[count].MinVoltage);
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक fiji_populate_memory_timing_parameters(काष्ठा pp_hwmgr *hwmgr,
		पूर्णांक32_t eng_घड़ी, पूर्णांक32_t mem_घड़ी,
		काष्ठा SMU73_Discrete_MCArbDramTimingTableEntry *arb_regs)
अणु
	uपूर्णांक32_t dram_timing;
	uपूर्णांक32_t dram_timing2;
	uपूर्णांक32_t burstTime;
	ULONG trrds, trrdl;
	पूर्णांक result;

	result = atomctrl_set_engine_dram_timings_rv770(hwmgr,
			eng_घड़ी, mem_घड़ी);
	PP_ASSERT_WITH_CODE(result == 0,
			"Error calling VBIOS to set DRAM_TIMING.", वापस result);

	dram_timing = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_ARB_DRAM_TIMING);
	dram_timing2 = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_ARB_DRAM_TIMING2);
	burstTime = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_ARB_BURST_TIME);

	trrds = PHM_GET_FIELD(burstTime, MC_ARB_BURST_TIME, TRRDS0);
	trrdl = PHM_GET_FIELD(burstTime, MC_ARB_BURST_TIME, TRRDL0);

	arb_regs->McArbDramTiming  = PP_HOST_TO_SMC_UL(dram_timing);
	arb_regs->McArbDramTiming2 = PP_HOST_TO_SMC_UL(dram_timing2);
	arb_regs->McArbBurstTime   = (uपूर्णांक8_t)burstTime;
	arb_regs->TRRDS            = (uपूर्णांक8_t)trrds;
	arb_regs->TRRDL            = (uपूर्णांक8_t)trrdl;

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_program_memory_timing_parameters(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);
	काष्ठा SMU73_Discrete_MCArbDramTimingTable arb_regs;
	uपूर्णांक32_t i, j;
	पूर्णांक result = 0;

	क्रम (i = 0; i < data->dpm_table.sclk_table.count; i++) अणु
		क्रम (j = 0; j < data->dpm_table.mclk_table.count; j++) अणु
			result = fiji_populate_memory_timing_parameters(hwmgr,
					data->dpm_table.sclk_table.dpm_levels[i].value,
					data->dpm_table.mclk_table.dpm_levels[j].value,
					&arb_regs.entries[i][j]);
			अगर (result)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (!result)
		result = smu7_copy_bytes_to_smc(
				hwmgr,
				smu_data->smu7_data.arb_table_start,
				(uपूर्णांक8_t *)&arb_regs,
				माप(SMU73_Discrete_MCArbDramTimingTable),
				SMC_RAM_END);
	वापस result;
पूर्ण

अटल पूर्णांक fiji_populate_smc_uvd_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU73_Discrete_DpmTable *table)
अणु
	पूर्णांक result = -EINVAL;
	uपूर्णांक8_t count;
	काष्ठा pp_atomctrl_घड़ी_भागiders_vi भागiders;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_mm_घड़ी_voltage_dependency_table *mm_table =
			table_info->mm_dep_table;

	table->UvdLevelCount = (uपूर्णांक8_t)(mm_table->count);
	table->UvdBootLevel = 0;

	क्रम (count = 0; count < table->UvdLevelCount; count++) अणु
		table->UvdLevel[count].MinVoltage = 0;
		table->UvdLevel[count].VclkFrequency = mm_table->entries[count].vclk;
		table->UvdLevel[count].DclkFrequency = mm_table->entries[count].dclk;
		table->UvdLevel[count].MinVoltage |= (mm_table->entries[count].vddc *
				VOLTAGE_SCALE) << VDDC_SHIFT;
		table->UvdLevel[count].MinVoltage |= ((mm_table->entries[count].vddc -
				VDDC_VDDCI_DELTA) * VOLTAGE_SCALE) << VDDCI_SHIFT;
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

अटल पूर्णांक fiji_populate_smc_boot_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU73_Discrete_DpmTable *table)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	table->GraphicsBootLevel = 0;
	table->MemoryBootLevel = 0;

	/* find boot level from dpm table */
	phm_find_boot_level(&(data->dpm_table.sclk_table),
			    data->vbios_boot_state.sclk_bootup_value,
			    (uपूर्णांक32_t *)&(table->GraphicsBootLevel));

	phm_find_boot_level(&(data->dpm_table.mclk_table),
			    data->vbios_boot_state.mclk_bootup_value,
			    (uपूर्णांक32_t *)&(table->MemoryBootLevel));

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

अटल पूर्णांक fiji_populate_smc_initailial_state(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	uपूर्णांक8_t count, level;

	count = (uपूर्णांक8_t)(table_info->vdd_dep_on_sclk->count);
	क्रम (level = 0; level < count; level++) अणु
		अगर (table_info->vdd_dep_on_sclk->entries[level].clk >=
				data->vbios_boot_state.sclk_bootup_value) अणु
			smu_data->smc_state_table.GraphicsBootLevel = level;
			अवरोध;
		पूर्ण
	पूर्ण

	count = (uपूर्णांक8_t)(table_info->vdd_dep_on_mclk->count);
	क्रम (level = 0; level < count; level++) अणु
		अगर (table_info->vdd_dep_on_mclk->entries[level].clk >=
				data->vbios_boot_state.mclk_bootup_value) अणु
			smu_data->smc_state_table.MemoryBootLevel = level;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_populate_घड़ी_stretcher_data_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t ro, efuse, efuse2, घड़ी_freq, volt_without_cks,
			volt_with_cks, value;
	uपूर्णांक16_t घड़ी_freq_u16;
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक8_t type, i, j, cks_setting, stretch_amount, stretch_amount2,
			volt_offset = 0;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *sclk_table =
			table_info->vdd_dep_on_sclk;

	stretch_amount = (uपूर्णांक8_t)table_info->cac_dtp_table->usClockStretchAmount;

	/* Read SMU_Eefuse to पढ़ो and calculate RO and determine
	 * अगर the part is SS or FF. अगर RO >= 1660MHz, part is FF.
	 */
	efuse = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			ixSMU_EFUSE_0 + (146 * 4));
	efuse2 = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			ixSMU_EFUSE_0 + (148 * 4));
	efuse &= 0xFF000000;
	efuse = efuse >> 24;
	efuse2 &= 0xF;

	अगर (efuse2 == 1)
		ro = (2300 - 1350) * efuse / 255 + 1350;
	अन्यथा
		ro = (2500 - 1000) * efuse / 255 + 1000;

	अगर (ro >= 1660)
		type = 0;
	अन्यथा
		type = 1;

	/* Populate Stretch amount */
	smu_data->smc_state_table.ClockStretcherAmount = stretch_amount;

	/* Populate Sclk_CKS_masterEn0_7 and Sclk_voltageOffset */
	क्रम (i = 0; i < sclk_table->count; i++) अणु
		smu_data->smc_state_table.Sclk_CKS_masterEn0_7 |=
				sclk_table->entries[i].cks_enable << i;
		volt_without_cks = (uपूर्णांक32_t)((14041 *
			(sclk_table->entries[i].clk/100) / 10000 + 3571 + 75 - ro) * 1000 /
			(4026 - (13924 * (sclk_table->entries[i].clk/100) / 10000)));
		volt_with_cks = (uपूर्णांक32_t)((13946 *
			(sclk_table->entries[i].clk/100) / 10000 + 3320 + 45 - ro) * 1000 /
			(3664 - (11454 * (sclk_table->entries[i].clk/100) / 10000)));
		अगर (volt_without_cks >= volt_with_cks)
			volt_offset = (uपूर्णांक8_t)(((volt_without_cks - volt_with_cks +
					sclk_table->entries[i].cks_voffset) * 100 / 625) + 1);
		smu_data->smc_state_table.Sclk_voltageOffset[i] = volt_offset;
	पूर्ण

	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, PWR_CKS_ENABLE,
			STRETCH_ENABLE, 0x0);
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, PWR_CKS_ENABLE,
			masterReset, 0x1);
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, PWR_CKS_ENABLE,
			अटलEnable, 0x1);
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, PWR_CKS_ENABLE,
			masterReset, 0x0);

	/* Populate CKS Lookup Table */
	अगर (stretch_amount == 1 || stretch_amount == 2 || stretch_amount == 5)
		stretch_amount2 = 0;
	अन्यथा अगर (stretch_amount == 3 || stretch_amount == 4)
		stretch_amount2 = 1;
	अन्यथा अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_ClockStretcher);
		PP_ASSERT_WITH_CODE(false,
				"Stretch Amount in PPTable not supported",
				वापस -EINVAL);
	पूर्ण

	value = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			ixPWR_CKS_CNTL);
	value &= 0xFFC2FF87;
	smu_data->smc_state_table.CKS_LOOKUPTable.CKS_LOOKUPTableEntry[0].minFreq =
			fiji_घड़ी_stretcher_lookup_table[stretch_amount2][0];
	smu_data->smc_state_table.CKS_LOOKUPTable.CKS_LOOKUPTableEntry[0].maxFreq =
			fiji_घड़ी_stretcher_lookup_table[stretch_amount2][1];
	घड़ी_freq_u16 = (uपूर्णांक16_t)(PP_SMC_TO_HOST_UL(smu_data->smc_state_table.
			GraphicsLevel[smu_data->smc_state_table.GraphicsDpmLevelCount - 1].
			SclkFrequency) / 100);
	अगर (fiji_घड़ी_stretcher_lookup_table[stretch_amount2][0] <
			घड़ी_freq_u16 &&
	    fiji_घड़ी_stretcher_lookup_table[stretch_amount2][1] >
			घड़ी_freq_u16) अणु
		/* Program PWR_CKS_CNTL. CKS_USE_FOR_LOW_FREQ */
		value |= (fiji_घड़ी_stretcher_lookup_table[stretch_amount2][3]) << 16;
		/* Program PWR_CKS_CNTL. CKS_LDO_REFSEL */
		value |= (fiji_घड़ी_stretcher_lookup_table[stretch_amount2][2]) << 18;
		/* Program PWR_CKS_CNTL. CKS_STRETCH_AMOUNT */
		value |= (fiji_घड़ी_stretch_amount_conversion
				[fiji_घड़ी_stretcher_lookup_table[stretch_amount2][3]]
				 [stretch_amount]) << 3;
	पूर्ण
	CONVERT_FROM_HOST_TO_SMC_US(smu_data->smc_state_table.CKS_LOOKUPTable.
			CKS_LOOKUPTableEntry[0].minFreq);
	CONVERT_FROM_HOST_TO_SMC_US(smu_data->smc_state_table.CKS_LOOKUPTable.
			CKS_LOOKUPTableEntry[0].maxFreq);
	smu_data->smc_state_table.CKS_LOOKUPTable.CKS_LOOKUPTableEntry[0].setting =
			fiji_घड़ी_stretcher_lookup_table[stretch_amount2][2] & 0x7F;
	smu_data->smc_state_table.CKS_LOOKUPTable.CKS_LOOKUPTableEntry[0].setting |=
			(fiji_घड़ी_stretcher_lookup_table[stretch_amount2][3]) << 7;

	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			ixPWR_CKS_CNTL, value);

	/* Populate DDT Lookup Table */
	क्रम (i = 0; i < 4; i++) अणु
		/* Assign the minimum and maximum VID stored
		 * in the last row of Clock Stretcher Voltage Table.
		 */
		smu_data->smc_state_table.ClockStretcherDataTable.
		ClockStretcherDataTableEntry[i].minVID =
				(uपूर्णांक8_t) fiji_घड़ी_stretcher_ddt_table[type][i][2];
		smu_data->smc_state_table.ClockStretcherDataTable.
		ClockStretcherDataTableEntry[i].maxVID =
				(uपूर्णांक8_t) fiji_घड़ी_stretcher_ddt_table[type][i][3];
		/* Loop through each SCLK and check the frequency
		 * to see अगर it lies within the frequency क्रम घड़ी stretcher.
		 */
		क्रम (j = 0; j < smu_data->smc_state_table.GraphicsDpmLevelCount; j++) अणु
			cks_setting = 0;
			घड़ी_freq = PP_SMC_TO_HOST_UL(
					smu_data->smc_state_table.GraphicsLevel[j].SclkFrequency);
			/* Check the allowed frequency against the sclk level[j].
			 *  Sclk's endianness has alपढ़ोy been converted,
			 *  and it's in 10Khz unit,
			 *  as opposed to Data table, which is in Mhz unit.
			 */
			अगर (घड़ी_freq >=
					(fiji_घड़ी_stretcher_ddt_table[type][i][0]) * 100) अणु
				cks_setting |= 0x2;
				अगर (घड़ी_freq <
						(fiji_घड़ी_stretcher_ddt_table[type][i][1]) * 100)
					cks_setting |= 0x1;
			पूर्ण
			smu_data->smc_state_table.ClockStretcherDataTable.
			ClockStretcherDataTableEntry[i].setting |= cks_setting << (j * 2);
		पूर्ण
		CONVERT_FROM_HOST_TO_SMC_US(smu_data->smc_state_table.
				ClockStretcherDataTable.
				ClockStretcherDataTableEntry[i].setting);
	पूर्ण

	value = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixPWR_CKS_CNTL);
	value &= 0xFFFFFFFE;
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixPWR_CKS_CNTL, value);

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_populate_vr_config(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU73_Discrete_DpmTable *table)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
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
		config = VR_SVI2_PLANE_2;
		table->VRConfig |= (config << VRCONF_MVDD_SHIFT);
	पूर्ण अन्यथा अगर (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->mvdd_control) अणु
		config = VR_SMIO_PATTERN_2;
		table->VRConfig |= (config << VRCONF_MVDD_SHIFT);
	पूर्ण अन्यथा अणु
		config = VR_STATIC_VOLTAGE;
		table->VRConfig |= (config << VRCONF_MVDD_SHIFT);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_init_arb_table_index(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t पंचांगp;
	पूर्णांक result;

	/* This is a पढ़ो-modअगरy-ग_लिखो on the first byte of the ARB table.
	 * The first byte in the SMU73_Discrete_MCArbDramTimingTable काष्ठाure
	 * is the field 'current'.
	 * This solution is ugly, but we never ग_लिखो the whole table only
	 * inभागidual fields in it.
	 * In reality this field should not be in that काष्ठाure
	 * but in a soft रेजिस्टर.
	 */
	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
			smu_data->smu7_data.arb_table_start, &पंचांगp, SMC_RAM_END);

	अगर (result)
		वापस result;

	पंचांगp &= 0x00FFFFFF;
	पंचांगp |= ((uपूर्णांक32_t)MC_CG_ARB_FREQ_F1) << 24;

	वापस smu7_ग_लिखो_smc_sram_dword(hwmgr,
			smu_data->smu7_data.arb_table_start,  पंचांगp, SMC_RAM_END);
पूर्ण

अटल पूर्णांक fiji_setup_dpm_led_config(काष्ठा pp_hwmgr *hwmgr)
अणु
	pp_atomctrl_voltage_table param_led_dpm;
	पूर्णांक result = 0;
	u32 mask = 0;

	result = atomctrl_get_voltage_table_v3(hwmgr,
					       VOLTAGE_TYPE_LEDDPM, VOLTAGE_OBJ_GPIO_LUT,
					       &param_led_dpm);
	अगर (result == 0) अणु
		पूर्णांक i, j;
		u32 पंचांगp = param_led_dpm.mask_low;

		क्रम (i = 0, j = 0; i < 32; i++) अणु
			अगर (पंचांगp & 1) अणु
				mask |= (i << (8 * j));
				अगर (++j >= 3)
					अवरोध;
			पूर्ण
			पंचांगp >>= 1;
		पूर्ण
	पूर्ण
	अगर (mask)
		smum_send_msg_to_smc_with_parameter(hwmgr,
						    PPSMC_MSG_LedConfig,
						    mask,
						    शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक fiji_init_smc_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा SMU73_Discrete_DpmTable *table = &(smu_data->smc_state_table);
	uपूर्णांक8_t i;
	काष्ठा pp_atomctrl_gpio_pin_assignment gpio_pin;

	fiji_initialize_घातer_tune_शेषs(hwmgr);

	अगर (SMU7_VOLTAGE_CONTROL_NONE != data->voltage_control)
		fiji_populate_smc_voltage_tables(hwmgr, table);

	table->SystemFlags = 0;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_AutomaticDCTransition))
		table->SystemFlags |= PPSMC_SYSTEMFLAG_GPIO_DC;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_StepVddc))
		table->SystemFlags |= PPSMC_SYSTEMFLAG_STEPVDDC;

	अगर (data->is_memory_gddr5)
		table->SystemFlags |= PPSMC_SYSTEMFLAG_GDDR5;

	अगर (data->ulv_supported && table_info->us_ulv_voltage_offset) अणु
		result = fiji_populate_ulv_state(hwmgr, table);
		PP_ASSERT_WITH_CODE(0 == result,
				"Failed to initialize ULV state!", वापस result);
		cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
				ixCG_ULV_PARAMETER, 0x40035);
	पूर्ण

	result = fiji_populate_smc_link_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
			"Failed to initialize Link Level!", वापस result);

	result = fiji_populate_all_graphic_levels(hwmgr);
	PP_ASSERT_WITH_CODE(0 == result,
			"Failed to initialize Graphics Level!", वापस result);

	result = fiji_populate_all_memory_levels(hwmgr);
	PP_ASSERT_WITH_CODE(0 == result,
			"Failed to initialize Memory Level!", वापस result);

	result = fiji_populate_smc_acpi_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
			"Failed to initialize ACPI Level!", वापस result);

	result = fiji_populate_smc_vce_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
			"Failed to initialize VCE Level!", वापस result);

	result = fiji_populate_smc_acp_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
			"Failed to initialize ACP Level!", वापस result);

	/* Since only the initial state is completely set up at this poपूर्णांक
	 * (the other states are just copies of the boot state) we only
	 * need to populate the  ARB settings क्रम the initial state.
	 */
	result = fiji_program_memory_timing_parameters(hwmgr);
	PP_ASSERT_WITH_CODE(0 == result,
			"Failed to Write ARB settings for the initial state.", वापस result);

	result = fiji_populate_smc_uvd_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
			"Failed to initialize UVD Level!", वापस result);

	result = fiji_populate_smc_boot_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
			"Failed to initialize Boot Level!", वापस result);

	result = fiji_populate_smc_initailial_state(hwmgr);
	PP_ASSERT_WITH_CODE(0 == result,
			"Failed to initialize Boot State!", वापस result);

	result = fiji_populate_bapm_parameters_in_dpm_table(hwmgr);
	PP_ASSERT_WITH_CODE(0 == result,
			"Failed to populate BAPM Parameters!", वापस result);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_ClockStretcher)) अणु
		result = fiji_populate_घड़ी_stretcher_data_table(hwmgr);
		PP_ASSERT_WITH_CODE(0 == result,
				"Failed to populate Clock Stretcher Data Table!",
				वापस result);
	पूर्ण

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
	table->PCIeBootLinkLevel = 0;      /* 0:Gen1 1:Gen2 2:Gen3*/
	table->PCIeGenInterval = 1;
	table->VRConfig = 0;

	result = fiji_populate_vr_config(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
			"Failed to populate VRConfig setting!", वापस result);
	data->vr_config = table->VRConfig;
	table->ThermGpio = 17;
	table->SclkStepSize = 0x4000;

	अगर (atomctrl_get_pp_assign_pin(hwmgr, VDDC_VRHOT_GPIO_PINID, &gpio_pin)) अणु
		table->VRHotGpio = gpio_pin.uc_gpio_pin_bit_shअगरt;
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_RegulatorHot);
	पूर्ण अन्यथा अणु
		table->VRHotGpio = SMU7_UNUSED_GPIO_PIN;
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_RegulatorHot);
	पूर्ण

	अगर (atomctrl_get_pp_assign_pin(hwmgr, PP_AC_DC_SWITCH_GPIO_PINID,
			&gpio_pin)) अणु
		table->AcDcGpio = gpio_pin.uc_gpio_pin_bit_shअगरt;
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_AutomaticDCTransition);
	पूर्ण अन्यथा अणु
		table->AcDcGpio = SMU7_UNUSED_GPIO_PIN;
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_AutomaticDCTransition);
	पूर्ण

	/* Thermal Output GPIO */
	अगर (atomctrl_get_pp_assign_pin(hwmgr, THERMAL_INT_OUTPUT_GPIO_PINID,
			&gpio_pin)) अणु
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_ThermalOutGPIO);

		table->ThermOutGpio = gpio_pin.uc_gpio_pin_bit_shअगरt;

		/* For porlarity पढ़ो GPIOPAD_A with asचिन्हित Gpio pin
		 * since VBIOS will program this रेजिस्टर to set 'inactive state',
		 * driver can then determine 'active state' from this and
		 * program SMU with correct polarity
		 */
		table->ThermOutPolarity = (0 == (cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmGPIOPAD_A) &
				(1 << gpio_pin.uc_gpio_pin_bit_shअगरt))) ? 1:0;
		table->ThermOutMode = SMU7_THERM_OUT_MODE_THERM_ONLY;

		/* अगर required, combine VRHot/PCC with thermal out GPIO */
		अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_RegulatorHot) &&
			phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_CombinePCCWithThermalSignal))
			table->ThermOutMode = SMU7_THERM_OUT_MODE_THERM_VRHOT;
	पूर्ण अन्यथा अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_ThermalOutGPIO);
		table->ThermOutGpio = 17;
		table->ThermOutPolarity = 1;
		table->ThermOutMode = SMU7_THERM_OUT_MODE_DISABLE;
	पूर्ण

	क्रम (i = 0; i < SMU73_MAX_ENTRIES_SMIO; i++)
		table->Smio[i] = PP_HOST_TO_SMC_UL(table->Smio[i]);

	CONVERT_FROM_HOST_TO_SMC_UL(table->SystemFlags);
	CONVERT_FROM_HOST_TO_SMC_UL(table->VRConfig);
	CONVERT_FROM_HOST_TO_SMC_UL(table->SmioMask1);
	CONVERT_FROM_HOST_TO_SMC_UL(table->SmioMask2);
	CONVERT_FROM_HOST_TO_SMC_UL(table->SclkStepSize);
	CONVERT_FROM_HOST_TO_SMC_US(table->TemperatureLimitHigh);
	CONVERT_FROM_HOST_TO_SMC_US(table->TemperatureLimitLow);
	CONVERT_FROM_HOST_TO_SMC_US(table->VoltageResponseTime);
	CONVERT_FROM_HOST_TO_SMC_US(table->PhaseResponseTime);

	/* Upload all dpm data to SMC memory.(dpm level, dpm level count etc) */
	result = smu7_copy_bytes_to_smc(hwmgr,
			smu_data->smu7_data.dpm_table_start +
			दुरत्व(SMU73_Discrete_DpmTable, SystemFlags),
			(uपूर्णांक8_t *)&(table->SystemFlags),
			माप(SMU73_Discrete_DpmTable) - 3 * माप(SMU73_PIDController),
			SMC_RAM_END);
	PP_ASSERT_WITH_CODE(0 == result,
			"Failed to upload dpm data to SMC memory!", वापस result);

	result = fiji_init_arb_table_index(hwmgr);
	PP_ASSERT_WITH_CODE(0 == result,
			"Failed to upload arb data to SMC memory!", वापस result);

	result = fiji_populate_pm_fuses(hwmgr);
	PP_ASSERT_WITH_CODE(0 == result,
			"Failed to  populate PM fuses to SMC memory!", वापस result);

	result = fiji_setup_dpm_led_config(hwmgr);
	PP_ASSERT_WITH_CODE(0 == result,
			    "Failed to setup dpm led config", वापस result);

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_thermal_setup_fan_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);

	SMU73_Discrete_FanTable fan_table = अणु FDO_MODE_HARDWARE पूर्ण;
	uपूर्णांक32_t duty100;
	uपूर्णांक32_t t_dअगरf1, t_dअगरf2, pwm_dअगरf1, pwm_dअगरf2;
	uपूर्णांक16_t fकरो_min, slope1, slope2;
	uपूर्णांक32_t reference_घड़ी;
	पूर्णांक res;
	uपूर्णांक64_t पंचांगp64;

	अगर (hwmgr->thermal_controller.fanInfo.bNoFan) अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_MicrocodeFanControl);
		वापस 0;
	पूर्ण

	अगर (smu_data->smu7_data.fan_table_start == 0) अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_MicrocodeFanControl);
		वापस 0;
	पूर्ण

	duty100 = PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_FDO_CTRL1, FMAX_DUTY100);

	अगर (duty100 == 0) अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_MicrocodeFanControl);
		वापस 0;
	पूर्ण

	पंचांगp64 = hwmgr->thermal_controller.advanceFanControlParameters.
			usPWMMin * duty100;
	करो_भाग(पंचांगp64, 10000);
	fकरो_min = (uपूर्णांक16_t)पंचांगp64;

	t_dअगरf1 = hwmgr->thermal_controller.advanceFanControlParameters.usTMed -
			hwmgr->thermal_controller.advanceFanControlParameters.usTMin;
	t_dअगरf2 = hwmgr->thermal_controller.advanceFanControlParameters.usTHigh -
			hwmgr->thermal_controller.advanceFanControlParameters.usTMed;

	pwm_dअगरf1 = hwmgr->thermal_controller.advanceFanControlParameters.usPWMMed -
			hwmgr->thermal_controller.advanceFanControlParameters.usPWMMin;
	pwm_dअगरf2 = hwmgr->thermal_controller.advanceFanControlParameters.usPWMHigh -
			hwmgr->thermal_controller.advanceFanControlParameters.usPWMMed;

	slope1 = (uपूर्णांक16_t)((50 + ((16 * duty100 * pwm_dअगरf1) / t_dअगरf1)) / 100);
	slope2 = (uपूर्णांक16_t)((50 + ((16 * duty100 * pwm_dअगरf2) / t_dअगरf2)) / 100);

	fan_table.TempMin = cpu_to_be16((50 + hwmgr->
			thermal_controller.advanceFanControlParameters.usTMin) / 100);
	fan_table.TempMed = cpu_to_be16((50 + hwmgr->
			thermal_controller.advanceFanControlParameters.usTMed) / 100);
	fan_table.TempMax = cpu_to_be16((50 + hwmgr->
			thermal_controller.advanceFanControlParameters.usTMax) / 100);

	fan_table.Slope1 = cpu_to_be16(slope1);
	fan_table.Slope2 = cpu_to_be16(slope2);

	fan_table.FकरोMin = cpu_to_be16(fकरो_min);

	fan_table.HystDown = cpu_to_be16(hwmgr->
			thermal_controller.advanceFanControlParameters.ucTHyst);

	fan_table.HystUp = cpu_to_be16(1);

	fan_table.HystSlope = cpu_to_be16(1);

	fan_table.TempRespLim = cpu_to_be16(5);

	reference_घड़ी = amdgpu_asic_get_xclk((काष्ठा amdgpu_device *)hwmgr->adev);

	fan_table.RefreshPeriod = cpu_to_be32((hwmgr->
			thermal_controller.advanceFanControlParameters.ulCycleDelay *
			reference_घड़ी) / 1600);

	fan_table.FकरोMax = cpu_to_be16((uपूर्णांक16_t)duty100);

	fan_table.TempSrc = (uपूर्णांक8_t)PHM_READ_VFPF_INसूचीECT_FIELD(
			hwmgr->device, CGS_IND_REG__SMC,
			CG_MULT_THERMAL_CTRL, TEMP_SEL);

	res = smu7_copy_bytes_to_smc(hwmgr, smu_data->smu7_data.fan_table_start,
			(uपूर्णांक8_t *)&fan_table, (uपूर्णांक32_t)माप(fan_table),
			SMC_RAM_END);

	अगर (!res && hwmgr->thermal_controller.
			advanceFanControlParameters.ucMinimumPWMLimit)
		res = smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetFanMinPwm,
				hwmgr->thermal_controller.
				advanceFanControlParameters.ucMinimumPWMLimit,
				शून्य);

	अगर (!res && hwmgr->thermal_controller.
			advanceFanControlParameters.ulMinFanSCLKAcousticLimit)
		res = smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetFanSclkTarget,
				hwmgr->thermal_controller.
				advanceFanControlParameters.ulMinFanSCLKAcousticLimit,
				शून्य);

	अगर (res)
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_MicrocodeFanControl);

	वापस 0;
पूर्ण


अटल पूर्णांक fiji_thermal_avfs_enable(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (!hwmgr->avfs_supported)
		वापस 0;

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_EnableAvfs, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_program_mem_timing_parameters(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (data->need_update_smu7_dpm_table &
		(DPMTABLE_OD_UPDATE_SCLK + DPMTABLE_OD_UPDATE_MCLK))
		वापस fiji_program_memory_timing_parameters(hwmgr);

	वापस 0;
पूर्ण

अटल पूर्णांक fiji_update_sclk_threshold(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);

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
				दुरत्व(SMU73_Discrete_DpmTable,
					LowSclkInterruptThreshold),
				(uपूर्णांक8_t *)&low_sclk_पूर्णांकerrupt_threshold,
				माप(uपूर्णांक32_t),
				SMC_RAM_END);
	पूर्ण
	result = fiji_program_mem_timing_parameters(hwmgr);
	PP_ASSERT_WITH_CODE((result == 0),
			"Failed to program memory timing parameters!",
			);
	वापस result;
पूर्ण

अटल uपूर्णांक32_t fiji_get_दुरत्व(uपूर्णांक32_t type, uपूर्णांक32_t member)
अणु
	चयन (type) अणु
	हाल SMU_SoftRegisters:
		चयन (member) अणु
		हाल HandshakeDisables:
			वापस दुरत्व(SMU73_SoftRegisters, HandshakeDisables);
		हाल VoltageChangeTimeout:
			वापस दुरत्व(SMU73_SoftRegisters, VoltageChangeTimeout);
		हाल AverageGraphicsActivity:
			वापस दुरत्व(SMU73_SoftRegisters, AverageGraphicsActivity);
		हाल AverageMemoryActivity:
			वापस दुरत्व(SMU73_SoftRegisters, AverageMemoryActivity);
		हाल PreVBlankGap:
			वापस दुरत्व(SMU73_SoftRegisters, PreVBlankGap);
		हाल VBlankTimeout:
			वापस दुरत्व(SMU73_SoftRegisters, VBlankTimeout);
		हाल UcodeLoadStatus:
			वापस दुरत्व(SMU73_SoftRegisters, UcodeLoadStatus);
		हाल DRAM_LOG_ADDR_H:
			वापस दुरत्व(SMU73_SoftRegisters, DRAM_LOG_ADDR_H);
		हाल DRAM_LOG_ADDR_L:
			वापस दुरत्व(SMU73_SoftRegisters, DRAM_LOG_ADDR_L);
		हाल DRAM_LOG_PHY_ADDR_H:
			वापस दुरत्व(SMU73_SoftRegisters, DRAM_LOG_PHY_ADDR_H);
		हाल DRAM_LOG_PHY_ADDR_L:
			वापस दुरत्व(SMU73_SoftRegisters, DRAM_LOG_PHY_ADDR_L);
		हाल DRAM_LOG_BUFF_SIZE:
			वापस दुरत्व(SMU73_SoftRegisters, DRAM_LOG_BUFF_SIZE);
		पूर्ण
		अवरोध;
	हाल SMU_Discrete_DpmTable:
		चयन (member) अणु
		हाल UvdBootLevel:
			वापस दुरत्व(SMU73_Discrete_DpmTable, UvdBootLevel);
		हाल VceBootLevel:
			वापस दुरत्व(SMU73_Discrete_DpmTable, VceBootLevel);
		हाल LowSclkInterruptThreshold:
			वापस दुरत्व(SMU73_Discrete_DpmTable, LowSclkInterruptThreshold);
		पूर्ण
		अवरोध;
	पूर्ण
	pr_warn("can't get the offset of type %x member %x\n", type, member);
	वापस 0;
पूर्ण

अटल uपूर्णांक32_t fiji_get_mac_definition(uपूर्णांक32_t value)
अणु
	चयन (value) अणु
	हाल SMU_MAX_LEVELS_GRAPHICS:
		वापस SMU73_MAX_LEVELS_GRAPHICS;
	हाल SMU_MAX_LEVELS_MEMORY:
		वापस SMU73_MAX_LEVELS_MEMORY;
	हाल SMU_MAX_LEVELS_LINK:
		वापस SMU73_MAX_LEVELS_LINK;
	हाल SMU_MAX_ENTRIES_SMIO:
		वापस SMU73_MAX_ENTRIES_SMIO;
	हाल SMU_MAX_LEVELS_VDDC:
		वापस SMU73_MAX_LEVELS_VDDC;
	हाल SMU_MAX_LEVELS_VDDGFX:
		वापस SMU73_MAX_LEVELS_VDDGFX;
	हाल SMU_MAX_LEVELS_VDDCI:
		वापस SMU73_MAX_LEVELS_VDDCI;
	हाल SMU_MAX_LEVELS_MVDD:
		वापस SMU73_MAX_LEVELS_MVDD;
	पूर्ण

	pr_warn("can't get the mac of %x\n", value);
	वापस 0;
पूर्ण


अटल पूर्णांक fiji_update_uvd_smc_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t mm_boot_level_offset, mm_boot_level_value;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	smu_data->smc_state_table.UvdBootLevel = 0;
	अगर (table_info->mm_dep_table->count > 0)
		smu_data->smc_state_table.UvdBootLevel =
				(uपूर्णांक8_t) (table_info->mm_dep_table->count - 1);
	mm_boot_level_offset = smu_data->smu7_data.dpm_table_start + दुरत्व(SMU73_Discrete_DpmTable,
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

अटल पूर्णांक fiji_update_vce_smc_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);
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
					दुरत्व(SMU73_Discrete_DpmTable, VceBootLevel);
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

अटल पूर्णांक fiji_update_smc_table(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t type)
अणु
	चयन (type) अणु
	हाल SMU_UVD_TABLE:
		fiji_update_uvd_smc_table(hwmgr);
		अवरोध;
	हाल SMU_VCE_TABLE:
		fiji_update_vce_smc_table(hwmgr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fiji_process_firmware_header(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t पंचांगp;
	पूर्णांक result;
	bool error = false;

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
			SMU7_FIRMWARE_HEADER_LOCATION +
			दुरत्व(SMU73_Firmware_Header, DpmTable),
			&पंचांगp, SMC_RAM_END);

	अगर (0 == result)
		smu_data->smu7_data.dpm_table_start = पंचांगp;

	error |= (0 != result);

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
			SMU7_FIRMWARE_HEADER_LOCATION +
			दुरत्व(SMU73_Firmware_Header, SoftRegisters),
			&पंचांगp, SMC_RAM_END);

	अगर (!result) अणु
		data->soft_regs_start = पंचांगp;
		smu_data->smu7_data.soft_regs_start = पंचांगp;
	पूर्ण

	error |= (0 != result);

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
			SMU7_FIRMWARE_HEADER_LOCATION +
			दुरत्व(SMU73_Firmware_Header, mcRegisterTable),
			&पंचांगp, SMC_RAM_END);

	अगर (!result)
		smu_data->smu7_data.mc_reg_table_start = पंचांगp;

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
			SMU7_FIRMWARE_HEADER_LOCATION +
			दुरत्व(SMU73_Firmware_Header, FanTable),
			&पंचांगp, SMC_RAM_END);

	अगर (!result)
		smu_data->smu7_data.fan_table_start = पंचांगp;

	error |= (0 != result);

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
			SMU7_FIRMWARE_HEADER_LOCATION +
			दुरत्व(SMU73_Firmware_Header, mcArbDramTimingTable),
			&पंचांगp, SMC_RAM_END);

	अगर (!result)
		smu_data->smu7_data.arb_table_start = पंचांगp;

	error |= (0 != result);

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
			SMU7_FIRMWARE_HEADER_LOCATION +
			दुरत्व(SMU73_Firmware_Header, Version),
			&पंचांगp, SMC_RAM_END);

	अगर (!result)
		hwmgr->microcode_version_info.SMC = पंचांगp;

	error |= (0 != result);

	वापस error ? -1 : 0;
पूर्ण

अटल पूर्णांक fiji_initialize_mc_reg_table(काष्ठा pp_hwmgr *hwmgr)
अणु

	/* Program additional LP रेजिस्टरs
	 * that are no दीर्घer programmed by VBIOS
	 */
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RAS_TIMING_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RAS_TIMING));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_CAS_TIMING_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_CAS_TIMING));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC_TIMING2_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC_TIMING2));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_WR_CTL_D1_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_WR_CTL_D1));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RD_CTL_D0_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RD_CTL_D0));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RD_CTL_D1_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RD_CTL_D1));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_TIMING_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_TIMING));

	वापस 0;
पूर्ण

अटल bool fiji_is_dpm_running(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस (1 == PHM_READ_INसूचीECT_FIELD(hwmgr->device,
			CGS_IND_REG__SMC, FEATURE_STATUS, VOLTAGE_CONTROLLER_ON))
			? true : false;
पूर्ण

अटल पूर्णांक fiji_update_dpm_settings(काष्ठा pp_hwmgr *hwmgr,
				व्योम *profile_setting)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा fiji_smumgr *smu_data = (काष्ठा fiji_smumgr *)
			(hwmgr->smu_backend);
	काष्ठा profile_mode_setting *setting;
	काष्ठा SMU73_Discrete_GraphicsLevel *levels =
			smu_data->smc_state_table.GraphicsLevel;
	uपूर्णांक32_t array = smu_data->smu7_data.dpm_table_start +
			दुरत्व(SMU73_Discrete_DpmTable, GraphicsLevel);

	uपूर्णांक32_t mclk_array = smu_data->smu7_data.dpm_table_start +
			दुरत्व(SMU73_Discrete_DpmTable, MemoryLevel);
	काष्ठा SMU73_Discrete_MemoryLevel *mclk_levels =
			smu_data->smc_state_table.MemoryLevel;
	uपूर्णांक32_t i;
	uपूर्णांक32_t offset, up_hyst_offset, करोwn_hyst_offset, clk_activity_offset, पंचांगp;

	अगर (profile_setting == शून्य)
		वापस -EINVAL;

	setting = (काष्ठा profile_mode_setting *)profile_setting;

	अगर (setting->bupdate_sclk) अणु
		अगर (!data->sclk_dpm_key_disabled)
			smum_send_msg_to_smc(hwmgr, PPSMC_MSG_SCLKDPM_FreezeLevel, शून्य);
		क्रम (i = 0; i < smu_data->smc_state_table.GraphicsDpmLevelCount; i++) अणु
			अगर (levels[i].ActivityLevel !=
				cpu_to_be16(setting->sclk_activity)) अणु
				levels[i].ActivityLevel = cpu_to_be16(setting->sclk_activity);

				clk_activity_offset = array + (माप(SMU73_Discrete_GraphicsLevel) * i)
						+ दुरत्व(SMU73_Discrete_GraphicsLevel, ActivityLevel);
				offset = clk_activity_offset & ~0x3;
				पंचांगp = PP_HOST_TO_SMC_UL(cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, offset));
				पंचांगp = phm_set_field_to_u32(clk_activity_offset, पंचांगp, levels[i].ActivityLevel, माप(uपूर्णांक16_t));
				cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, offset, PP_HOST_TO_SMC_UL(पंचांगp));

			पूर्ण
			अगर (levels[i].UpHyst != setting->sclk_up_hyst ||
				levels[i].DownHyst != setting->sclk_करोwn_hyst) अणु
				levels[i].UpHyst = setting->sclk_up_hyst;
				levels[i].DownHyst = setting->sclk_करोwn_hyst;
				up_hyst_offset = array + (माप(SMU73_Discrete_GraphicsLevel) * i)
						+ दुरत्व(SMU73_Discrete_GraphicsLevel, UpHyst);
				करोwn_hyst_offset = array + (माप(SMU73_Discrete_GraphicsLevel) * i)
						+ दुरत्व(SMU73_Discrete_GraphicsLevel, DownHyst);
				offset = up_hyst_offset & ~0x3;
				पंचांगp = PP_HOST_TO_SMC_UL(cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, offset));
				पंचांगp = phm_set_field_to_u32(up_hyst_offset, पंचांगp, levels[i].UpHyst, माप(uपूर्णांक8_t));
				पंचांगp = phm_set_field_to_u32(करोwn_hyst_offset, पंचांगp, levels[i].DownHyst, माप(uपूर्णांक8_t));
				cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, offset, PP_HOST_TO_SMC_UL(पंचांगp));
			पूर्ण
		पूर्ण
		अगर (!data->sclk_dpm_key_disabled)
			smum_send_msg_to_smc(hwmgr, PPSMC_MSG_SCLKDPM_Unमुक्तzeLevel, शून्य);
	पूर्ण

	अगर (setting->bupdate_mclk) अणु
		अगर (!data->mclk_dpm_key_disabled)
			smum_send_msg_to_smc(hwmgr, PPSMC_MSG_MCLKDPM_FreezeLevel, शून्य);
		क्रम (i = 0; i < smu_data->smc_state_table.MemoryDpmLevelCount; i++) अणु
			अगर (mclk_levels[i].ActivityLevel !=
				cpu_to_be16(setting->mclk_activity)) अणु
				mclk_levels[i].ActivityLevel = cpu_to_be16(setting->mclk_activity);

				clk_activity_offset = mclk_array + (माप(SMU73_Discrete_MemoryLevel) * i)
						+ दुरत्व(SMU73_Discrete_MemoryLevel, ActivityLevel);
				offset = clk_activity_offset & ~0x3;
				पंचांगp = PP_HOST_TO_SMC_UL(cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, offset));
				पंचांगp = phm_set_field_to_u32(clk_activity_offset, पंचांगp, mclk_levels[i].ActivityLevel, माप(uपूर्णांक16_t));
				cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, offset, PP_HOST_TO_SMC_UL(पंचांगp));

			पूर्ण
			अगर (mclk_levels[i].UpHyst != setting->mclk_up_hyst ||
				mclk_levels[i].DownHyst != setting->mclk_करोwn_hyst) अणु
				mclk_levels[i].UpHyst = setting->mclk_up_hyst;
				mclk_levels[i].DownHyst = setting->mclk_करोwn_hyst;
				up_hyst_offset = mclk_array + (माप(SMU73_Discrete_MemoryLevel) * i)
						+ दुरत्व(SMU73_Discrete_MemoryLevel, UpHyst);
				करोwn_hyst_offset = mclk_array + (माप(SMU73_Discrete_MemoryLevel) * i)
						+ दुरत्व(SMU73_Discrete_MemoryLevel, DownHyst);
				offset = up_hyst_offset & ~0x3;
				पंचांगp = PP_HOST_TO_SMC_UL(cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, offset));
				पंचांगp = phm_set_field_to_u32(up_hyst_offset, पंचांगp, mclk_levels[i].UpHyst, माप(uपूर्णांक8_t));
				पंचांगp = phm_set_field_to_u32(करोwn_hyst_offset, पंचांगp, mclk_levels[i].DownHyst, माप(uपूर्णांक8_t));
				cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, offset, PP_HOST_TO_SMC_UL(पंचांगp));
			पूर्ण
		पूर्ण
		अगर (!data->mclk_dpm_key_disabled)
			smum_send_msg_to_smc(hwmgr, PPSMC_MSG_MCLKDPM_Unमुक्तzeLevel, शून्य);
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा pp_smumgr_func fiji_smu_funcs = अणु
	.name = "fiji_smu",
	.smu_init = &fiji_smu_init,
	.smu_fini = &smu7_smu_fini,
	.start_smu = &fiji_start_smu,
	.check_fw_load_finish = &smu7_check_fw_load_finish,
	.request_smu_load_fw = &smu7_reload_firmware,
	.request_smu_load_specअगरic_fw = शून्य,
	.send_msg_to_smc = &smu7_send_msg_to_smc,
	.send_msg_to_smc_with_parameter = &smu7_send_msg_to_smc_with_parameter,
	.get_argument = smu7_get_argument,
	.करोwnload_pptable_settings = शून्य,
	.upload_pptable_settings = शून्य,
	.update_smc_table = fiji_update_smc_table,
	.get_दुरत्व = fiji_get_दुरत्व,
	.process_firmware_header = fiji_process_firmware_header,
	.init_smc_table = fiji_init_smc_table,
	.update_sclk_threshold = fiji_update_sclk_threshold,
	.thermal_setup_fan_table = fiji_thermal_setup_fan_table,
	.thermal_avfs_enable = fiji_thermal_avfs_enable,
	.populate_all_graphic_levels = fiji_populate_all_graphic_levels,
	.populate_all_memory_levels = fiji_populate_all_memory_levels,
	.get_mac_definition = fiji_get_mac_definition,
	.initialize_mc_reg_table = fiji_initialize_mc_reg_table,
	.is_dpm_running = fiji_is_dpm_running,
	.is_hw_avfs_present = fiji_is_hw_avfs_present,
	.update_dpm_settings = fiji_update_dpm_settings,
पूर्ण;
