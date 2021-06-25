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
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/gfp.h>

#समावेश "smumgr.h"
#समावेश "tonga_smumgr.h"
#समावेश "smu_ucode_xfer_vi.h"
#समावेश "tonga_ppsmc.h"
#समावेश "smu/smu_7_1_2_d.h"
#समावेश "smu/smu_7_1_2_sh_mask.h"
#समावेश "cgs_common.h"
#समावेश "smu7_smumgr.h"

#समावेश "smu7_dyn_defaults.h"

#समावेश "smu7_hwmgr.h"
#समावेश "hardwaremanager.h"
#समावेश "ppatomctrl.h"

#समावेश "atombios.h"

#समावेश "pppcielanes.h"
#समावेश "pp_endian.h"

#समावेश "gmc/gmc_8_1_d.h"
#समावेश "gmc/gmc_8_1_sh_mask.h"

#समावेश "bif/bif_5_0_d.h"
#समावेश "bif/bif_5_0_sh_mask.h"

#समावेश "dce/dce_10_0_d.h"
#समावेश "dce/dce_10_0_sh_mask.h"

#घोषणा POWERTUNE_DEFAULT_SET_MAX    1
#घोषणा MC_CG_ARB_FREQ_F1           0x0b
#घोषणा VDDC_VDDCI_DELTA            200


अटल स्थिर काष्ठा tonga_pt_शेषs tonga_घातer_tune_data_set_array[POWERTUNE_DEFAULT_SET_MAX] = अणु
/* sviLoadLIneEn, SviLoadLineVddC, TDC_VDDC_ThrottleReleaseLimitPerc,  TDC_MAWt,
 * TdcWaterfallCtl, DTEAmbientTempBase, DisplayCac,        BAPM_TEMP_GRADIENT
 */
	अणु1,               0xF,             0xFD,                0x19,
	 5,               45,                 0,              0xB0000,
	 अणु0x79, 0x253, 0x25D, 0xAE, 0x72, 0x80, 0x83, 0x86, 0x6F, 0xC8,
		0xC9, 0xC9, 0x2F, 0x4D, 0x61पूर्ण,
	 अणु0x17C, 0x172, 0x180, 0x1BC, 0x1B3, 0x1BD, 0x206, 0x200, 0x203,
		0x25D, 0x25A, 0x255, 0x2C3, 0x2C5, 0x2B4पूर्ण
	पूर्ण,
पूर्ण;

/* [Fmin, Fmax, LDO_REFSEL, USE_FOR_LOW_FREQ] */
अटल स्थिर uपूर्णांक16_t tonga_घड़ी_stretcher_lookup_table[2][4] = अणु
	अणु600, 1050, 3, 0पूर्ण,
	अणु600, 1050, 6, 1पूर्ण
पूर्ण;

/* [FF, SS] type, [] 4 voltage ranges,
 * and [Floor Freq, Boundary Freq, VID min , VID max]
 */
अटल स्थिर uपूर्णांक32_t tonga_घड़ी_stretcher_ddt_table[2][4][4] = अणु
	अणु अणु265, 529, 120, 128पूर्ण, अणु325, 650, 96, 119पूर्ण, अणु430, 860, 32, 95पूर्ण, अणु0, 0, 0, 31पूर्ण पूर्ण,
	अणु अणु275, 550, 104, 112पूर्ण, अणु319, 638, 96, 103पूर्ण, अणु360, 720, 64, 95पूर्ण, अणु384, 768, 32, 63पूर्ण पूर्ण
पूर्ण;

/* [Use_For_Low_freq] value, [0%, 5%, 10%, 7.14%, 14.28%, 20%] */
अटल स्थिर uपूर्णांक8_t tonga_घड़ी_stretch_amount_conversion[2][6] = अणु
	अणु0, 1, 3, 2, 4, 5पूर्ण,
	अणु0, 2, 4, 5, 6, 5पूर्ण
पूर्ण;

अटल पूर्णांक tonga_start_in_protection_mode(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;

	/* Assert reset */
	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
		SMC_SYSCON_RESET_CNTL, rst_reg, 1);

	result = smu7_upload_smu_firmware_image(hwmgr);
	अगर (result)
		वापस result;

	/* Clear status */
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
		ixSMU_STATUS, 0);

	/* Enable घड़ी */
	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
		SMC_SYSCON_CLOCK_CNTL_0, ck_disable, 0);

	/* De-निश्चित reset */
	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
		SMC_SYSCON_RESET_CNTL, rst_reg, 0);

	/* Set SMU Auto Start */
	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
		SMU_INPUT_DATA, AUTO_START, 1);

	/* Clear firmware पूर्णांकerrupt enable flag */
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
		ixFIRMWARE_FLAGS, 0);

	PHM_WAIT_VFPF_INसूचीECT_FIELD(hwmgr, SMC_IND,
		RCU_UC_EVENTS, INTERRUPTS_ENABLED, 1);

	/**
	 * Call Test SMU message with 0x20000 offset to trigger SMU start
	 */
	smu7_send_msg_to_smc_offset(hwmgr);

	/* Wait क्रम करोne bit to be set */
	PHM_WAIT_VFPF_INसूचीECT_FIELD_UNEQUAL(hwmgr, SMC_IND,
		SMU_STATUS, SMU_DONE, 0);

	/* Check pass/failed indicator */
	अगर (1 != PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device,
				CGS_IND_REG__SMC, SMU_STATUS, SMU_PASS)) अणु
		pr_err("SMU Firmware start failed\n");
		वापस -EINVAL;
	पूर्ण

	/* Wait क्रम firmware to initialize */
	PHM_WAIT_VFPF_INसूचीECT_FIELD(hwmgr, SMC_IND,
		FIRMWARE_FLAGS, INTERRUPTS_ENABLED, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_start_in_non_protection_mode(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;

	/* रुको क्रम smc boot up */
	PHM_WAIT_VFPF_INसूचीECT_FIELD_UNEQUAL(hwmgr, SMC_IND,
		RCU_UC_EVENTS, boot_seq_करोne, 0);

	/*Clear firmware पूर्णांकerrupt enable flag*/
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
		ixFIRMWARE_FLAGS, 0);


	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
		SMC_SYSCON_RESET_CNTL, rst_reg, 1);

	result = smu7_upload_smu_firmware_image(hwmgr);

	अगर (result != 0)
		वापस result;

	/* Set smc inकाष्ठा start poपूर्णांक at 0x0 */
	smu7_program_jump_on_start(hwmgr);


	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
		SMC_SYSCON_CLOCK_CNTL_0, ck_disable, 0);

	/*De-निश्चित reset*/
	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
		SMC_SYSCON_RESET_CNTL, rst_reg, 0);

	/* Wait क्रम firmware to initialize */
	PHM_WAIT_VFPF_INसूचीECT_FIELD(hwmgr, SMC_IND,
		FIRMWARE_FLAGS, INTERRUPTS_ENABLED, 1);

	वापस result;
पूर्ण

अटल पूर्णांक tonga_start_smu(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा tonga_smumgr *priv = hwmgr->smu_backend;
	पूर्णांक result;

	/* Only start SMC अगर SMC RAM is not running */
	अगर (!smu7_is_smc_ram_running(hwmgr) && hwmgr->not_vf) अणु
		/*Check अगर SMU is running in रक्षित mode*/
		अगर (0 == PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
					SMU_FIRMWARE, SMU_MODE)) अणु
			result = tonga_start_in_non_protection_mode(hwmgr);
			अगर (result)
				वापस result;
		पूर्ण अन्यथा अणु
			result = tonga_start_in_protection_mode(hwmgr);
			अगर (result)
				वापस result;
		पूर्ण
	पूर्ण

	/* Setup SoftRegsStart here to visit the रेजिस्टर UcodeLoadStatus
	 * to check fw loading state
	 */
	smu7_पढ़ो_smc_sram_dword(hwmgr,
			SMU72_FIRMWARE_HEADER_LOCATION +
			दुरत्व(SMU72_Firmware_Header, SoftRegisters),
			&(priv->smu7_data.soft_regs_start), 0x40000);

	result = smu7_request_smu_load_fw(hwmgr);

	वापस result;
पूर्ण

अटल पूर्णांक tonga_smu_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा tonga_smumgr *tonga_priv = शून्य;

	tonga_priv = kzalloc(माप(काष्ठा tonga_smumgr), GFP_KERNEL);
	अगर (tonga_priv == शून्य)
		वापस -ENOMEM;

	hwmgr->smu_backend = tonga_priv;

	अगर (smu7_init(hwmgr)) अणु
		kमुक्त(tonga_priv);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक tonga_get_dependency_volt_by_clk(काष्ठा pp_hwmgr *hwmgr,
	phm_ppt_v1_घड़ी_voltage_dependency_table *allowed_घड़ी_voltage_table,
	uपूर्णांक32_t घड़ी, SMU_VoltageLevel *voltage, uपूर्णांक32_t *mvdd)
अणु
	uपूर्णांक32_t i = 0;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *pptable_info =
			   (काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	/* घड़ी - voltage dependency table is empty table */
	अगर (allowed_घड़ी_voltage_table->count == 0)
		वापस -EINVAL;

	क्रम (i = 0; i < allowed_घड़ी_voltage_table->count; i++) अणु
		/* find first sclk bigger than request */
		अगर (allowed_घड़ी_voltage_table->entries[i].clk >= घड़ी) अणु
			voltage->VddGfx = phm_get_voltage_index(
					pptable_info->vddgfx_lookup_table,
				allowed_घड़ी_voltage_table->entries[i].vddgfx);
			voltage->Vddc = phm_get_voltage_index(
						pptable_info->vddc_lookup_table,
				  allowed_घड़ी_voltage_table->entries[i].vddc);

			अगर (allowed_घड़ी_voltage_table->entries[i].vddci)
				voltage->Vddci =
					phm_get_voltage_id(&data->vddci_voltage_table, allowed_घड़ी_voltage_table->entries[i].vddci);
			अन्यथा
				voltage->Vddci =
					phm_get_voltage_id(&data->vddci_voltage_table,
						allowed_घड़ी_voltage_table->entries[i].vddc - VDDC_VDDCI_DELTA);


			अगर (allowed_घड़ी_voltage_table->entries[i].mvdd)
				*mvdd = (uपूर्णांक32_t) allowed_घड़ी_voltage_table->entries[i].mvdd;

			voltage->Phases = 1;
			वापस 0;
		पूर्ण
	पूर्ण

	/* sclk is bigger than max sclk in the dependence table */
	voltage->VddGfx = phm_get_voltage_index(pptable_info->vddgfx_lookup_table,
		allowed_घड़ी_voltage_table->entries[i-1].vddgfx);
	voltage->Vddc = phm_get_voltage_index(pptable_info->vddc_lookup_table,
		allowed_घड़ी_voltage_table->entries[i-1].vddc);

	अगर (allowed_घड़ी_voltage_table->entries[i-1].vddci)
		voltage->Vddci = phm_get_voltage_id(&data->vddci_voltage_table,
			allowed_घड़ी_voltage_table->entries[i-1].vddci);

	अगर (allowed_घड़ी_voltage_table->entries[i-1].mvdd)
		*mvdd = (uपूर्णांक32_t) allowed_घड़ी_voltage_table->entries[i-1].mvdd;

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_smc_vddc_table(काष्ठा pp_hwmgr *hwmgr,
			SMU72_Discrete_DpmTable *table)
अणु
	अचिन्हित पूर्णांक count;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->voltage_control) अणु
		table->VddcLevelCount = data->vddc_voltage_table.count;
		क्रम (count = 0; count < table->VddcLevelCount; count++) अणु
			table->VddcTable[count] =
				PP_HOST_TO_SMC_US(data->vddc_voltage_table.entries[count].value * VOLTAGE_SCALE);
		पूर्ण
		CONVERT_FROM_HOST_TO_SMC_UL(table->VddcLevelCount);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_smc_vdd_gfx_table(काष्ठा pp_hwmgr *hwmgr,
			SMU72_Discrete_DpmTable *table)
अणु
	अचिन्हित पूर्णांक count;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->vdd_gfx_control) अणु
		table->VddGfxLevelCount = data->vddgfx_voltage_table.count;
		क्रम (count = 0; count < data->vddgfx_voltage_table.count; count++) अणु
			table->VddGfxTable[count] =
				PP_HOST_TO_SMC_US(data->vddgfx_voltage_table.entries[count].value * VOLTAGE_SCALE);
		पूर्ण
		CONVERT_FROM_HOST_TO_SMC_UL(table->VddGfxLevelCount);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_smc_vdd_ci_table(काष्ठा pp_hwmgr *hwmgr,
			SMU72_Discrete_DpmTable *table)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t count;

	table->VddciLevelCount = data->vddci_voltage_table.count;
	क्रम (count = 0; count < table->VddciLevelCount; count++) अणु
		अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->vddci_control) अणु
			table->VddciTable[count] =
				PP_HOST_TO_SMC_US(data->vddci_voltage_table.entries[count].value * VOLTAGE_SCALE);
		पूर्ण अन्यथा अगर (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->vddci_control) अणु
			table->SmioTable1.Pattern[count].Voltage =
				PP_HOST_TO_SMC_US(data->vddci_voltage_table.entries[count].value * VOLTAGE_SCALE);
			/* Index पूर्णांकo DpmTable.Smio. Drive bits from Smio entry to get this voltage level. */
			table->SmioTable1.Pattern[count].Smio =
				(uपूर्णांक8_t) count;
			table->Smio[count] |=
				data->vddci_voltage_table.entries[count].smio_low;
			table->VddciTable[count] =
				PP_HOST_TO_SMC_US(data->vddci_voltage_table.entries[count].value * VOLTAGE_SCALE);
		पूर्ण
	पूर्ण

	table->SmioMask1 = data->vddci_voltage_table.mask_low;
	CONVERT_FROM_HOST_TO_SMC_UL(table->VddciLevelCount);

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_smc_mvdd_table(काष्ठा pp_hwmgr *hwmgr,
			SMU72_Discrete_DpmTable *table)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t count;

	अगर (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->mvdd_control) अणु
		table->MvddLevelCount = data->mvdd_voltage_table.count;
		क्रम (count = 0; count < table->MvddLevelCount; count++) अणु
			table->SmioTable2.Pattern[count].Voltage =
				PP_HOST_TO_SMC_US(data->mvdd_voltage_table.entries[count].value * VOLTAGE_SCALE);
			/* Index पूर्णांकo DpmTable.Smio. Drive bits from Smio entry to get this voltage level.*/
			table->SmioTable2.Pattern[count].Smio =
				(uपूर्णांक8_t) count;
			table->Smio[count] |=
				data->mvdd_voltage_table.entries[count].smio_low;
		पूर्ण
		table->SmioMask2 = data->mvdd_voltage_table.mask_low;

		CONVERT_FROM_HOST_TO_SMC_UL(table->MvddLevelCount);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_cac_tables(काष्ठा pp_hwmgr *hwmgr,
			SMU72_Discrete_DpmTable *table)
अणु
	uपूर्णांक32_t count;
	uपूर्णांक8_t index = 0;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *pptable_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_voltage_lookup_table *vddgfx_lookup_table =
					   pptable_info->vddgfx_lookup_table;
	काष्ठा phm_ppt_v1_voltage_lookup_table *vddc_lookup_table =
						pptable_info->vddc_lookup_table;

	/* table is alपढ़ोy swapped, so in order to use the value from it
	 * we need to swap it back.
	 */
	uपूर्णांक32_t vddc_level_count = PP_SMC_TO_HOST_UL(table->VddcLevelCount);
	uपूर्णांक32_t vddgfx_level_count = PP_SMC_TO_HOST_UL(table->VddGfxLevelCount);

	क्रम (count = 0; count < vddc_level_count; count++) अणु
		/* We are populating vddc CAC data to BapmVddc table in split and merged mode */
		index = phm_get_voltage_index(vddc_lookup_table,
			data->vddc_voltage_table.entries[count].value);
		table->BapmVddcVidLoSidd[count] =
			convert_to_vid(vddc_lookup_table->entries[index].us_cac_low);
		table->BapmVddcVidHiSidd[count] =
			convert_to_vid(vddc_lookup_table->entries[index].us_cac_mid);
		table->BapmVddcVidHiSidd2[count] =
			convert_to_vid(vddc_lookup_table->entries[index].us_cac_high);
	पूर्ण

	अगर (data->vdd_gfx_control == SMU7_VOLTAGE_CONTROL_BY_SVID2) अणु
		/* We are populating vddgfx CAC data to BapmVddgfx table in split mode */
		क्रम (count = 0; count < vddgfx_level_count; count++) अणु
			index = phm_get_voltage_index(vddgfx_lookup_table,
				convert_to_vid(vddgfx_lookup_table->entries[index].us_cac_mid));
			table->BapmVddGfxVidHiSidd2[count] =
				convert_to_vid(vddgfx_lookup_table->entries[index].us_cac_high);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (count = 0; count < vddc_level_count; count++) अणु
			index = phm_get_voltage_index(vddc_lookup_table,
				data->vddc_voltage_table.entries[count].value);
			table->BapmVddGfxVidLoSidd[count] =
				convert_to_vid(vddc_lookup_table->entries[index].us_cac_low);
			table->BapmVddGfxVidHiSidd[count] =
				convert_to_vid(vddc_lookup_table->entries[index].us_cac_mid);
			table->BapmVddGfxVidHiSidd2[count] =
				convert_to_vid(vddc_lookup_table->entries[index].us_cac_high);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_smc_voltage_tables(काष्ठा pp_hwmgr *hwmgr,
	SMU72_Discrete_DpmTable *table)
अणु
	पूर्णांक result;

	result = tonga_populate_smc_vddc_table(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
			"can not populate VDDC voltage table to SMC",
			वापस -EINVAL);

	result = tonga_populate_smc_vdd_ci_table(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
			"can not populate VDDCI voltage table to SMC",
			वापस -EINVAL);

	result = tonga_populate_smc_vdd_gfx_table(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
			"can not populate VDDGFX voltage table to SMC",
			वापस -EINVAL);

	result = tonga_populate_smc_mvdd_table(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
			"can not populate MVDD voltage table to SMC",
			वापस -EINVAL);

	result = tonga_populate_cac_tables(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
			"can not populate CAC voltage tables to SMC",
			वापस -EINVAL);

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_ulv_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU72_Discrete_Ulv *state)
अणु
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	state->CcPwrDynRm = 0;
	state->CcPwrDynRm1 = 0;

	state->VddcOffset = (uपूर्णांक16_t) table_info->us_ulv_voltage_offset;
	state->VddcOffsetVid = (uपूर्णांक8_t)(table_info->us_ulv_voltage_offset *
			VOLTAGE_VID_OFFSET_SCALE2 / VOLTAGE_VID_OFFSET_SCALE1);

	state->VddcPhase = 1;

	CONVERT_FROM_HOST_TO_SMC_UL(state->CcPwrDynRm);
	CONVERT_FROM_HOST_TO_SMC_UL(state->CcPwrDynRm1);
	CONVERT_FROM_HOST_TO_SMC_US(state->VddcOffset);

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_ulv_state(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU72_Discrete_DpmTable *table)
अणु
	वापस tonga_populate_ulv_level(hwmgr, &table->Ulv);
पूर्ण

अटल पूर्णांक tonga_populate_smc_link_level(काष्ठा pp_hwmgr *hwmgr, SMU72_Discrete_DpmTable *table)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_dpm_table *dpm_table = &data->dpm_table;
	काष्ठा tonga_smumgr *smu_data = (काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t i;

	/* Index (dpm_table->pcie_speed_table.count) is reserved क्रम PCIE boot level. */
	क्रम (i = 0; i <= dpm_table->pcie_speed_table.count; i++) अणु
		table->LinkLevel[i].PcieGenSpeed  =
			(uपूर्णांक8_t)dpm_table->pcie_speed_table.dpm_levels[i].value;
		table->LinkLevel[i].PcieLaneCount =
			(uपूर्णांक8_t)encode_pcie_lane_width(dpm_table->pcie_speed_table.dpm_levels[i].param1);
		table->LinkLevel[i].EnabledForActivity =
			1;
		table->LinkLevel[i].SPC =
			(uपूर्णांक8_t)(data->pcie_spc_cap & 0xff);
		table->LinkLevel[i].DownThreshold =
			PP_HOST_TO_SMC_UL(5);
		table->LinkLevel[i].UpThreshold =
			PP_HOST_TO_SMC_UL(30);
	पूर्ण

	smu_data->smc_state_table.LinkLevelCount =
		(uपूर्णांक8_t)dpm_table->pcie_speed_table.count;
	data->dpm_level_enable_mask.pcie_dpm_enable_mask =
		phm_get_dpm_level_enable_mask_value(&dpm_table->pcie_speed_table);

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_calculate_sclk_params(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t engine_घड़ी, SMU72_Discrete_GraphicsLevel *sclk)
अणु
	स्थिर काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	pp_atomctrl_घड़ी_भागiders_vi भागiders;
	uपूर्णांक32_t spll_func_cntl            = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL;
	uपूर्णांक32_t spll_func_cntl_3          = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL_3;
	uपूर्णांक32_t spll_func_cntl_4          = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL_4;
	uपूर्णांक32_t cg_spll_spपढ़ो_spectrum   = data->घड़ी_रेजिस्टरs.vCG_SPLL_SPREAD_SPECTRUM;
	uपूर्णांक32_t cg_spll_spपढ़ो_spectrum_2 = data->घड़ी_रेजिस्टरs.vCG_SPLL_SPREAD_SPECTRUM_2;
	uपूर्णांक32_t    reference_घड़ी;
	uपूर्णांक32_t reference_भागider;
	uपूर्णांक32_t fbभाग;
	पूर्णांक result;

	/* get the engine घड़ी भागiders क्रम this घड़ी value*/
	result = atomctrl_get_engine_pll_भागiders_vi(hwmgr, engine_घड़ी,  &भागiders);

	PP_ASSERT_WITH_CODE(result == 0,
		"Error retrieving Engine Clock dividers from VBIOS.", वापस result);

	/* To get FBDIV we need to multiply this by 16384 and भागide it by Fref.*/
	reference_घड़ी = atomctrl_get_reference_घड़ी(hwmgr);

	reference_भागider = 1 + भागiders.uc_pll_ref_भाग;

	/* low 14 bits is fraction and high 12 bits is भागider*/
	fbभाग = भागiders.ul_fb_भाग.ul_fb_भागider & 0x3FFFFFF;

	/* SPLL_FUNC_CNTL setup*/
	spll_func_cntl = PHM_SET_FIELD(spll_func_cntl,
		CG_SPLL_FUNC_CNTL, SPLL_REF_DIV, भागiders.uc_pll_ref_भाग);
	spll_func_cntl = PHM_SET_FIELD(spll_func_cntl,
		CG_SPLL_FUNC_CNTL, SPLL_PDIV_A,  भागiders.uc_pll_post_भाग);

	/* SPLL_FUNC_CNTL_3 setup*/
	spll_func_cntl_3 = PHM_SET_FIELD(spll_func_cntl_3,
		CG_SPLL_FUNC_CNTL_3, SPLL_FB_DIV, fbभाग);

	/* set to use fractional accumulation*/
	spll_func_cntl_3 = PHM_SET_FIELD(spll_func_cntl_3,
		CG_SPLL_FUNC_CNTL_3, SPLL_DITHEN, 1);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_EngineSpपढ़ोSpectrumSupport)) अणु
		pp_atomctrl_पूर्णांकernal_ss_info ss_info;

		uपूर्णांक32_t vcoFreq = engine_घड़ी * भागiders.uc_pll_post_भाग;
		अगर (0 == atomctrl_get_engine_घड़ी_spपढ़ो_spectrum(hwmgr, vcoFreq, &ss_info)) अणु
			/*
			* ss_info.speed_spectrum_percentage -- in unit of 0.01%
			* ss_info.speed_spectrum_rate -- in unit of khz
			*/
			/* clks = reference_घड़ी * 10 / (REFDIV + 1) / speed_spectrum_rate / 2 */
			uपूर्णांक32_t clkS = reference_घड़ी * 5 / (reference_भागider * ss_info.speed_spectrum_rate);

			/* clkv = 2 * D * fbभाग / NS */
			uपूर्णांक32_t clkV = 4 * ss_info.speed_spectrum_percentage * fbभाग / (clkS * 10000);

			cg_spll_spपढ़ो_spectrum =
				PHM_SET_FIELD(cg_spll_spपढ़ो_spectrum, CG_SPLL_SPREAD_SPECTRUM, CLKS, clkS);
			cg_spll_spपढ़ो_spectrum =
				PHM_SET_FIELD(cg_spll_spपढ़ो_spectrum, CG_SPLL_SPREAD_SPECTRUM, SSEN, 1);
			cg_spll_spपढ़ो_spectrum_2 =
				PHM_SET_FIELD(cg_spll_spपढ़ो_spectrum_2, CG_SPLL_SPREAD_SPECTRUM_2, CLKV, clkV);
		पूर्ण
	पूर्ण

	sclk->SclkFrequency        = engine_घड़ी;
	sclk->CgSpllFuncCntl3      = spll_func_cntl_3;
	sclk->CgSpllFuncCntl4      = spll_func_cntl_4;
	sclk->SpllSpपढ़ोSpectrum   = cg_spll_spपढ़ो_spectrum;
	sclk->SpllSpपढ़ोSpectrum2  = cg_spll_spपढ़ो_spectrum_2;
	sclk->SclkDid              = (uपूर्णांक8_t)भागiders.pll_post_भागider;

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_single_graphic_level(काष्ठा pp_hwmgr *hwmgr,
						uपूर्णांक32_t engine_घड़ी,
				SMU72_Discrete_GraphicsLevel *graphic_level)
अणु
	पूर्णांक result;
	uपूर्णांक32_t mvdd;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *pptable_info =
			    (काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	phm_ppt_v1_घड़ी_voltage_dependency_table *vdd_dep_table = शून्य;

	result = tonga_calculate_sclk_params(hwmgr, engine_घड़ी, graphic_level);

	अगर (hwmgr->od_enabled)
		vdd_dep_table = (phm_ppt_v1_घड़ी_voltage_dependency_table *)&data->odn_dpm_table.vdd_dependency_on_sclk;
	अन्यथा
		vdd_dep_table = pptable_info->vdd_dep_on_sclk;

	/* populate graphics levels*/
	result = tonga_get_dependency_volt_by_clk(hwmgr,
		vdd_dep_table, engine_घड़ी,
		&graphic_level->MinVoltage, &mvdd);
	PP_ASSERT_WITH_CODE((!result),
		"can not find VDDC voltage value for VDDC "
		"engine clock dependency table", वापस result);

	/* SCLK frequency in units of 10KHz*/
	graphic_level->SclkFrequency = engine_घड़ी;
	/* Indicates maximum activity level क्रम this perक्रमmance level. 50% क्रम now*/
	graphic_level->ActivityLevel = data->current_profile_setting.sclk_activity;

	graphic_level->CcPwrDynRm = 0;
	graphic_level->CcPwrDynRm1 = 0;
	/* this level can be used अगर activity is high enough.*/
	graphic_level->EnabledForActivity = 0;
	/* this level can be used क्रम throttling.*/
	graphic_level->EnabledForThrottle = 1;
	graphic_level->UpHyst = data->current_profile_setting.sclk_up_hyst;
	graphic_level->DownHyst = data->current_profile_setting.sclk_करोwn_hyst;
	graphic_level->VoltageDownHyst = 0;
	graphic_level->PowerThrottle = 0;

	data->display_timing.min_घड़ी_in_sr =
			hwmgr->display_config->min_core_set_घड़ी_in_sr;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_SclkDeepSleep))
		graphic_level->DeepSleepDivId =
				smu7_get_sleep_भागider_id_from_घड़ी(engine_घड़ी,
						data->display_timing.min_घड़ी_in_sr);

	/* Default to slow, highest DPM level will be set to PPSMC_DISPLAY_WATERMARK_LOW later.*/
	graphic_level->DisplayWatermark = PPSMC_DISPLAY_WATERMARK_LOW;

	अगर (!result) अणु
		/* CONVERT_FROM_HOST_TO_SMC_UL(graphic_level->MinVoltage);*/
		/* CONVERT_FROM_HOST_TO_SMC_UL(graphic_level->MinVddcPhases);*/
		CONVERT_FROM_HOST_TO_SMC_UL(graphic_level->SclkFrequency);
		CONVERT_FROM_HOST_TO_SMC_US(graphic_level->ActivityLevel);
		CONVERT_FROM_HOST_TO_SMC_UL(graphic_level->CgSpllFuncCntl3);
		CONVERT_FROM_HOST_TO_SMC_UL(graphic_level->CgSpllFuncCntl4);
		CONVERT_FROM_HOST_TO_SMC_UL(graphic_level->SpllSpपढ़ोSpectrum);
		CONVERT_FROM_HOST_TO_SMC_UL(graphic_level->SpllSpपढ़ोSpectrum2);
		CONVERT_FROM_HOST_TO_SMC_UL(graphic_level->CcPwrDynRm);
		CONVERT_FROM_HOST_TO_SMC_UL(graphic_level->CcPwrDynRm1);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक tonga_populate_all_graphic_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा tonga_smumgr *smu_data = (काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	काष्ठा phm_ppt_v1_inक्रमmation *pptable_info = (काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा smu7_dpm_table *dpm_table = &data->dpm_table;
	काष्ठा phm_ppt_v1_pcie_table *pcie_table = pptable_info->pcie_table;
	uपूर्णांक8_t pcie_entry_count = (uपूर्णांक8_t) data->dpm_table.pcie_speed_table.count;
	uपूर्णांक32_t level_array_address = smu_data->smu7_data.dpm_table_start +
				दुरत्व(SMU72_Discrete_DpmTable, GraphicsLevel);

	uपूर्णांक32_t level_array_size = माप(SMU72_Discrete_GraphicsLevel) *
						SMU72_MAX_LEVELS_GRAPHICS;

	SMU72_Discrete_GraphicsLevel *levels = smu_data->smc_state_table.GraphicsLevel;

	uपूर्णांक32_t i, max_entry;
	uपूर्णांक8_t highest_pcie_level_enabled = 0;
	uपूर्णांक8_t lowest_pcie_level_enabled = 0, mid_pcie_level_enabled = 0;
	uपूर्णांक8_t count = 0;
	पूर्णांक result = 0;

	स_रखो(levels, 0x00, level_array_size);

	क्रम (i = 0; i < dpm_table->sclk_table.count; i++) अणु
		result = tonga_populate_single_graphic_level(hwmgr,
					dpm_table->sclk_table.dpm_levels[i].value,
					&(smu_data->smc_state_table.GraphicsLevel[i]));
		अगर (result != 0)
			वापस result;

		/* Making sure only DPM level 0-1 have Deep Sleep Div ID populated. */
		अगर (i > 1)
			smu_data->smc_state_table.GraphicsLevel[i].DeepSleepDivId = 0;
	पूर्ण

	/* Only enable level 0 क्रम now. */
	smu_data->smc_state_table.GraphicsLevel[0].EnabledForActivity = 1;

	/* set highest level watermark to high */
	अगर (dpm_table->sclk_table.count > 1)
		smu_data->smc_state_table.GraphicsLevel[dpm_table->sclk_table.count-1].DisplayWatermark =
			PPSMC_DISPLAY_WATERMARK_HIGH;

	smu_data->smc_state_table.GraphicsDpmLevelCount =
		(uपूर्णांक8_t)dpm_table->sclk_table.count;
	data->dpm_level_enable_mask.sclk_dpm_enable_mask =
		phm_get_dpm_level_enable_mask_value(&dpm_table->sclk_table);

	अगर (pcie_table != शून्य) अणु
		PP_ASSERT_WITH_CODE((pcie_entry_count >= 1),
			"There must be 1 or more PCIE levels defined in PPTable.",
			वापस -EINVAL);
		max_entry = pcie_entry_count - 1; /* क्रम indexing, we need to decrement by 1.*/
		क्रम (i = 0; i < dpm_table->sclk_table.count; i++) अणु
			smu_data->smc_state_table.GraphicsLevel[i].pcieDpmLevel =
				(uपूर्णांक8_t) ((i < max_entry) ? i : max_entry);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (0 == data->dpm_level_enable_mask.pcie_dpm_enable_mask)
			pr_err("Pcie Dpm Enablemask is 0 !");

		जबतक (data->dpm_level_enable_mask.pcie_dpm_enable_mask &&
				((data->dpm_level_enable_mask.pcie_dpm_enable_mask &
					(1<<(highest_pcie_level_enabled+1))) != 0)) अणु
			highest_pcie_level_enabled++;
		पूर्ण

		जबतक (data->dpm_level_enable_mask.pcie_dpm_enable_mask &&
				((data->dpm_level_enable_mask.pcie_dpm_enable_mask &
					(1<<lowest_pcie_level_enabled)) == 0)) अणु
			lowest_pcie_level_enabled++;
		पूर्ण

		जबतक ((count < highest_pcie_level_enabled) &&
				((data->dpm_level_enable_mask.pcie_dpm_enable_mask &
					(1<<(lowest_pcie_level_enabled+1+count))) == 0)) अणु
			count++;
		पूर्ण
		mid_pcie_level_enabled = (lowest_pcie_level_enabled+1+count) < highest_pcie_level_enabled ?
			(lowest_pcie_level_enabled+1+count) : highest_pcie_level_enabled;


		/* set pcieDpmLevel to highest_pcie_level_enabled*/
		क्रम (i = 2; i < dpm_table->sclk_table.count; i++)
			smu_data->smc_state_table.GraphicsLevel[i].pcieDpmLevel = highest_pcie_level_enabled;

		/* set pcieDpmLevel to lowest_pcie_level_enabled*/
		smu_data->smc_state_table.GraphicsLevel[0].pcieDpmLevel = lowest_pcie_level_enabled;

		/* set pcieDpmLevel to mid_pcie_level_enabled*/
		smu_data->smc_state_table.GraphicsLevel[1].pcieDpmLevel = mid_pcie_level_enabled;
	पूर्ण
	/* level count will send to smc once at init smc table and never change*/
	result = smu7_copy_bytes_to_smc(hwmgr, level_array_address,
				(uपूर्णांक8_t *)levels, (uपूर्णांक32_t)level_array_size,
								SMC_RAM_END);

	वापस result;
पूर्ण

अटल पूर्णांक tonga_calculate_mclk_params(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t memory_घड़ी,
		SMU72_Discrete_MemoryLevel *mclk,
		bool strobe_mode,
		bool dllStateOn
		)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	uपूर्णांक32_t dll_cntl = data->घड़ी_रेजिस्टरs.vDLL_CNTL;
	uपूर्णांक32_t mclk_pwrmgt_cntl = data->घड़ी_रेजिस्टरs.vMCLK_PWRMGT_CNTL;
	uपूर्णांक32_t mpll_ad_func_cntl = data->घड़ी_रेजिस्टरs.vMPLL_AD_FUNC_CNTL;
	uपूर्णांक32_t mpll_dq_func_cntl = data->घड़ी_रेजिस्टरs.vMPLL_DQ_FUNC_CNTL;
	uपूर्णांक32_t mpll_func_cntl = data->घड़ी_रेजिस्टरs.vMPLL_FUNC_CNTL;
	uपूर्णांक32_t mpll_func_cntl_1 = data->घड़ी_रेजिस्टरs.vMPLL_FUNC_CNTL_1;
	uपूर्णांक32_t mpll_func_cntl_2 = data->घड़ी_रेजिस्टरs.vMPLL_FUNC_CNTL_2;
	uपूर्णांक32_t mpll_ss1 = data->घड़ी_रेजिस्टरs.vMPLL_SS1;
	uपूर्णांक32_t mpll_ss2 = data->घड़ी_रेजिस्टरs.vMPLL_SS2;

	pp_atomctrl_memory_घड़ी_param mpll_param;
	पूर्णांक result;

	result = atomctrl_get_memory_pll_भागiders_si(hwmgr,
				memory_घड़ी, &mpll_param, strobe_mode);
	PP_ASSERT_WITH_CODE(
			!result,
			"Error retrieving Memory Clock Parameters from VBIOS.",
			वापस result);

	/* MPLL_FUNC_CNTL setup*/
	mpll_func_cntl = PHM_SET_FIELD(mpll_func_cntl, MPLL_FUNC_CNTL, BWCTRL,
					mpll_param.bw_ctrl);

	/* MPLL_FUNC_CNTL_1 setup*/
	mpll_func_cntl_1  = PHM_SET_FIELD(mpll_func_cntl_1,
					MPLL_FUNC_CNTL_1, CLKF,
					mpll_param.mpll_fb_भागider.cl_kf);
	mpll_func_cntl_1  = PHM_SET_FIELD(mpll_func_cntl_1,
					MPLL_FUNC_CNTL_1, CLKFRAC,
					mpll_param.mpll_fb_भागider.clk_frac);
	mpll_func_cntl_1  = PHM_SET_FIELD(mpll_func_cntl_1,
						MPLL_FUNC_CNTL_1, VCO_MODE,
						mpll_param.vco_mode);

	/* MPLL_AD_FUNC_CNTL setup*/
	mpll_ad_func_cntl = PHM_SET_FIELD(mpll_ad_func_cntl,
					MPLL_AD_FUNC_CNTL, YCLK_POST_DIV,
					mpll_param.mpll_post_भागider);

	अगर (data->is_memory_gddr5) अणु
		/* MPLL_DQ_FUNC_CNTL setup*/
		mpll_dq_func_cntl  = PHM_SET_FIELD(mpll_dq_func_cntl,
						MPLL_DQ_FUNC_CNTL, YCLK_SEL,
						mpll_param.yclk_sel);
		mpll_dq_func_cntl  = PHM_SET_FIELD(mpll_dq_func_cntl,
						MPLL_DQ_FUNC_CNTL, YCLK_POST_DIV,
						mpll_param.mpll_post_भागider);
	पूर्ण

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_MemorySpपढ़ोSpectrumSupport)) अणु
		/*
		 ************************************
		 Fref = Reference Frequency
		 NF = Feedback भागider ratio
		 NR = Reference भागider ratio
		 Fnom = Nominal VCO output frequency = Fref * NF / NR
		 Fs = Spपढ़ोing Rate
		 D = Percentage करोwn-spपढ़ो / 2
		 Fपूर्णांक = Reference input frequency to PFD = Fref / NR
		 NS = Spपढ़ोing rate भागider ratio = पूर्णांक(Fपूर्णांक / (2 * Fs))
		 CLKS = NS - 1 = ISS_STEP_NUM[11:0]
		 NV = D * Fs / Fnom * 4 * ((Fnom/Fref * NR) ^ 2)
		 CLKV = 65536 * NV = ISS_STEP_SIZE[25:0]
		 *************************************
		 */
		pp_atomctrl_पूर्णांकernal_ss_info ss_info;
		uपूर्णांक32_t freq_nom;
		uपूर्णांक32_t पंचांगp;
		uपूर्णांक32_t reference_घड़ी = atomctrl_get_mpll_reference_घड़ी(hwmgr);

		/* क्रम GDDR5 क्रम all modes and DDR3 */
		अगर (1 == mpll_param.qdr)
			freq_nom = memory_घड़ी * 4 * (1 << mpll_param.mpll_post_भागider);
		अन्यथा
			freq_nom = memory_घड़ी * 2 * (1 << mpll_param.mpll_post_भागider);

		/* पंचांगp = (freq_nom / reference_घड़ी * reference_भागider) ^ 2  Note: S.I. reference_भागider = 1*/
		पंचांगp = (freq_nom / reference_घड़ी);
		पंचांगp = पंचांगp * पंचांगp;

		अगर (0 == atomctrl_get_memory_घड़ी_spपढ़ो_spectrum(hwmgr, freq_nom, &ss_info)) अणु
			/* ss_info.speed_spectrum_percentage -- in unit of 0.01% */
			/* ss.Info.speed_spectrum_rate -- in unit of khz */
			/* CLKS = reference_घड़ी / (2 * speed_spectrum_rate * reference_भागider) * 10 */
			/*     = reference_घड़ी * 5 / speed_spectrum_rate */
			uपूर्णांक32_t clks = reference_घड़ी * 5 / ss_info.speed_spectrum_rate;

			/* CLKV = 65536 * speed_spectrum_percentage / 2 * spपढ़ोSpecrumRate / freq_nom * 4 / 100000 * ((freq_nom / reference_घड़ी) ^ 2) */
			/*     = 131 * speed_spectrum_percentage * speed_spectrum_rate / 100 * ((freq_nom / reference_घड़ी) ^ 2) / freq_nom */
			uपूर्णांक32_t clkv =
				(uपूर्णांक32_t)((((131 * ss_info.speed_spectrum_percentage *
							ss_info.speed_spectrum_rate) / 100) * पंचांगp) / freq_nom);

			mpll_ss1 = PHM_SET_FIELD(mpll_ss1, MPLL_SS1, CLKV, clkv);
			mpll_ss2 = PHM_SET_FIELD(mpll_ss2, MPLL_SS2, CLKS, clks);
		पूर्ण
	पूर्ण

	/* MCLK_PWRMGT_CNTL setup */
	mclk_pwrmgt_cntl = PHM_SET_FIELD(mclk_pwrmgt_cntl,
		MCLK_PWRMGT_CNTL, DLL_SPEED, mpll_param.dll_speed);
	mclk_pwrmgt_cntl = PHM_SET_FIELD(mclk_pwrmgt_cntl,
		MCLK_PWRMGT_CNTL, MRDCK0_PDNB, dllStateOn);
	mclk_pwrmgt_cntl = PHM_SET_FIELD(mclk_pwrmgt_cntl,
		MCLK_PWRMGT_CNTL, MRDCK1_PDNB, dllStateOn);

	/* Save the result data to outpupt memory level काष्ठाure */
	mclk->MclkFrequency   = memory_घड़ी;
	mclk->MpllFuncCntl    = mpll_func_cntl;
	mclk->MpllFuncCntl_1  = mpll_func_cntl_1;
	mclk->MpllFuncCntl_2  = mpll_func_cntl_2;
	mclk->MpllAdFuncCntl  = mpll_ad_func_cntl;
	mclk->MpllDqFuncCntl  = mpll_dq_func_cntl;
	mclk->MclkPwrmgtCntl  = mclk_pwrmgt_cntl;
	mclk->DllCntl         = dll_cntl;
	mclk->MpllSs1         = mpll_ss1;
	mclk->MpllSs2         = mpll_ss2;

	वापस 0;
पूर्ण

अटल uपूर्णांक8_t tonga_get_mclk_frequency_ratio(uपूर्णांक32_t memory_घड़ी,
		bool strobe_mode)
अणु
	uपूर्णांक8_t mc_para_index;

	अगर (strobe_mode) अणु
		अगर (memory_घड़ी < 12500)
			mc_para_index = 0x00;
		अन्यथा अगर (memory_घड़ी > 47500)
			mc_para_index = 0x0f;
		अन्यथा
			mc_para_index = (uपूर्णांक8_t)((memory_घड़ी - 10000) / 2500);
	पूर्ण अन्यथा अणु
		अगर (memory_घड़ी < 65000)
			mc_para_index = 0x00;
		अन्यथा अगर (memory_घड़ी > 135000)
			mc_para_index = 0x0f;
		अन्यथा
			mc_para_index = (uपूर्णांक8_t)((memory_घड़ी - 60000) / 5000);
	पूर्ण

	वापस mc_para_index;
पूर्ण

अटल uपूर्णांक8_t tonga_get_ddr3_mclk_frequency_ratio(uपूर्णांक32_t memory_घड़ी)
अणु
	uपूर्णांक8_t mc_para_index;

	अगर (memory_घड़ी < 10000)
		mc_para_index = 0;
	अन्यथा अगर (memory_घड़ी >= 80000)
		mc_para_index = 0x0f;
	अन्यथा
		mc_para_index = (uपूर्णांक8_t)((memory_घड़ी - 10000) / 5000 + 1);

	वापस mc_para_index;
पूर्ण


अटल पूर्णांक tonga_populate_single_memory_level(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t memory_घड़ी,
		SMU72_Discrete_MemoryLevel *memory_level
		)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *pptable_info =
			  (काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	uपूर्णांक32_t mclk_edc_wr_enable_threshold = 40000;
	uपूर्णांक32_t mclk_stutter_mode_threshold = 30000;
	uपूर्णांक32_t mclk_edc_enable_threshold = 40000;
	uपूर्णांक32_t mclk_strobe_mode_threshold = 40000;
	phm_ppt_v1_घड़ी_voltage_dependency_table *vdd_dep_table = शून्य;
	पूर्णांक result = 0;
	bool dll_state_on;
	uपूर्णांक32_t mvdd = 0;

	अगर (hwmgr->od_enabled)
		vdd_dep_table = (phm_ppt_v1_घड़ी_voltage_dependency_table *)&data->odn_dpm_table.vdd_dependency_on_mclk;
	अन्यथा
		vdd_dep_table = pptable_info->vdd_dep_on_mclk;

	अगर (शून्य != vdd_dep_table) अणु
		result = tonga_get_dependency_volt_by_clk(hwmgr,
				vdd_dep_table,
				memory_घड़ी,
				&memory_level->MinVoltage, &mvdd);
		PP_ASSERT_WITH_CODE(
			!result,
			"can not find MinVddc voltage value from memory VDDC "
			"voltage dependency table",
			वापस result);
	पूर्ण

	अगर (data->mvdd_control == SMU7_VOLTAGE_CONTROL_NONE)
		memory_level->MinMvdd = data->vbios_boot_state.mvdd_bootup_value;
	अन्यथा
		memory_level->MinMvdd = mvdd;

	memory_level->EnabledForThrottle = 1;
	memory_level->EnabledForActivity = 0;
	memory_level->UpHyst = data->current_profile_setting.mclk_up_hyst;
	memory_level->DownHyst = data->current_profile_setting.mclk_करोwn_hyst;
	memory_level->VoltageDownHyst = 0;

	/* Indicates maximum activity level क्रम this perक्रमmance level.*/
	memory_level->ActivityLevel = data->current_profile_setting.mclk_activity;
	memory_level->StutterEnable = 0;
	memory_level->StrobeEnable = 0;
	memory_level->EdcReadEnable = 0;
	memory_level->EdcWriteEnable = 0;
	memory_level->RttEnable = 0;

	/* शेष set to low watermark. Highest level will be set to high later.*/
	memory_level->DisplayWatermark = PPSMC_DISPLAY_WATERMARK_LOW;

	data->display_timing.num_existing_displays = hwmgr->display_config->num_display;
	data->display_timing.vrefresh = hwmgr->display_config->vrefresh;

	अगर ((mclk_stutter_mode_threshold != 0) &&
	    (memory_घड़ी <= mclk_stutter_mode_threshold) &&
	    (!data->is_uvd_enabled)
	    && (PHM_READ_FIELD(hwmgr->device, DPG_PIPE_STUTTER_CONTROL, STUTTER_ENABLE) & 0x1)
	    && (data->display_timing.num_existing_displays <= 2)
	    && (data->display_timing.num_existing_displays != 0))
		memory_level->StutterEnable = 1;

	/* decide strobe mode*/
	memory_level->StrobeEnable = (mclk_strobe_mode_threshold != 0) &&
		(memory_घड़ी <= mclk_strobe_mode_threshold);

	/* decide EDC mode and memory घड़ी ratio*/
	अगर (data->is_memory_gddr5) अणु
		memory_level->StrobeRatio = tonga_get_mclk_frequency_ratio(memory_घड़ी,
					memory_level->StrobeEnable);

		अगर ((mclk_edc_enable_threshold != 0) &&
				(memory_घड़ी > mclk_edc_enable_threshold)) अणु
			memory_level->EdcReadEnable = 1;
		पूर्ण

		अगर ((mclk_edc_wr_enable_threshold != 0) &&
				(memory_घड़ी > mclk_edc_wr_enable_threshold)) अणु
			memory_level->EdcWriteEnable = 1;
		पूर्ण

		अगर (memory_level->StrobeEnable) अणु
			अगर (tonga_get_mclk_frequency_ratio(memory_घड़ी, 1) >=
					((cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC7) >> 16) & 0xf)) अणु
				dll_state_on = ((cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC5) >> 1) & 0x1) ? 1 : 0;
			पूर्ण अन्यथा अणु
				dll_state_on = ((cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC6) >> 1) & 0x1) ? 1 : 0;
			पूर्ण

		पूर्ण अन्यथा अणु
			dll_state_on = data->dll_शेष_on;
		पूर्ण
	पूर्ण अन्यथा अणु
		memory_level->StrobeRatio =
			tonga_get_ddr3_mclk_frequency_ratio(memory_घड़ी);
		dll_state_on = ((cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC5) >> 1) & 0x1) ? 1 : 0;
	पूर्ण

	result = tonga_calculate_mclk_params(hwmgr,
		memory_घड़ी, memory_level, memory_level->StrobeEnable, dll_state_on);

	अगर (!result) अणु
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MinMvdd);
		/* MCLK frequency in units of 10KHz*/
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MclkFrequency);
		/* Indicates maximum activity level क्रम this perक्रमmance level.*/
		CONVERT_FROM_HOST_TO_SMC_US(memory_level->ActivityLevel);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MpllFuncCntl);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MpllFuncCntl_1);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MpllFuncCntl_2);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MpllAdFuncCntl);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MpllDqFuncCntl);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MclkPwrmgtCntl);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->DllCntl);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MpllSs1);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MpllSs2);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक tonga_populate_all_memory_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा tonga_smumgr *smu_data =
			(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	काष्ठा smu7_dpm_table *dpm_table = &data->dpm_table;
	पूर्णांक result;

	/* populate MCLK dpm table to SMU7 */
	uपूर्णांक32_t level_array_address =
				smu_data->smu7_data.dpm_table_start +
				दुरत्व(SMU72_Discrete_DpmTable, MemoryLevel);
	uपूर्णांक32_t level_array_size =
				माप(SMU72_Discrete_MemoryLevel) *
				SMU72_MAX_LEVELS_MEMORY;
	SMU72_Discrete_MemoryLevel *levels =
				smu_data->smc_state_table.MemoryLevel;
	uपूर्णांक32_t i;

	स_रखो(levels, 0x00, level_array_size);

	क्रम (i = 0; i < dpm_table->mclk_table.count; i++) अणु
		PP_ASSERT_WITH_CODE((0 != dpm_table->mclk_table.dpm_levels[i].value),
			"can not populate memory level as memory clock is zero",
			वापस -EINVAL);
		result = tonga_populate_single_memory_level(
				hwmgr,
				dpm_table->mclk_table.dpm_levels[i].value,
				&(smu_data->smc_state_table.MemoryLevel[i]));
		अगर (result)
			वापस result;
	पूर्ण

	/* Only enable level 0 क्रम now.*/
	smu_data->smc_state_table.MemoryLevel[0].EnabledForActivity = 1;

	/*
	* in order to prevent MC activity from stutter mode to push DPM up.
	* the UVD change complements this by putting the MCLK in a higher state
	* by शेष such that we are not effected by up threshold or and MCLK DPM latency.
	*/
	smu_data->smc_state_table.MemoryLevel[0].ActivityLevel = 0x1F;
	CONVERT_FROM_HOST_TO_SMC_US(smu_data->smc_state_table.MemoryLevel[0].ActivityLevel);

	smu_data->smc_state_table.MemoryDpmLevelCount = (uपूर्णांक8_t)dpm_table->mclk_table.count;
	data->dpm_level_enable_mask.mclk_dpm_enable_mask = phm_get_dpm_level_enable_mask_value(&dpm_table->mclk_table);
	/* set highest level watermark to high*/
	smu_data->smc_state_table.MemoryLevel[dpm_table->mclk_table.count-1].DisplayWatermark = PPSMC_DISPLAY_WATERMARK_HIGH;

	/* level count will send to smc once at init smc table and never change*/
	result = smu7_copy_bytes_to_smc(hwmgr,
		level_array_address, (uपूर्णांक8_t *)levels, (uपूर्णांक32_t)level_array_size,
		SMC_RAM_END);

	वापस result;
पूर्ण

अटल पूर्णांक tonga_populate_mvdd_value(काष्ठा pp_hwmgr *hwmgr,
				uपूर्णांक32_t mclk, SMIO_Pattern *smio_pattern)
अणु
	स्थिर काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	uपूर्णांक32_t i = 0;

	अगर (SMU7_VOLTAGE_CONTROL_NONE != data->mvdd_control) अणु
		/* find mvdd value which घड़ी is more than request */
		क्रम (i = 0; i < table_info->vdd_dep_on_mclk->count; i++) अणु
			अगर (mclk <= table_info->vdd_dep_on_mclk->entries[i].clk) अणु
				/* Always round to higher voltage. */
				smio_pattern->Voltage =
				      data->mvdd_voltage_table.entries[i].value;
				अवरोध;
			पूर्ण
		पूर्ण

		PP_ASSERT_WITH_CODE(i < table_info->vdd_dep_on_mclk->count,
			"MVDD Voltage is outside the supported range.",
			वापस -EINVAL);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक tonga_populate_smc_acpi_level(काष्ठा pp_hwmgr *hwmgr,
	SMU72_Discrete_DpmTable *table)
अणु
	पूर्णांक result = 0;
	काष्ठा tonga_smumgr *smu_data =
				(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	स्थिर काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा pp_atomctrl_घड़ी_भागiders_vi भागiders;

	SMIO_Pattern voltage_level;
	uपूर्णांक32_t spll_func_cntl    = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL;
	uपूर्णांक32_t spll_func_cntl_2  = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL_2;
	uपूर्णांक32_t dll_cntl          = data->घड़ी_रेजिस्टरs.vDLL_CNTL;
	uपूर्णांक32_t mclk_pwrmgt_cntl  = data->घड़ी_रेजिस्टरs.vMCLK_PWRMGT_CNTL;

	/* The ACPI state should not करो DPM on DC (or ever).*/
	table->ACPILevel.Flags &= ~PPSMC_SWSTATE_FLAG_DC;

	table->ACPILevel.MinVoltage =
			smu_data->smc_state_table.GraphicsLevel[0].MinVoltage;

	/* assign zero क्रम now*/
	table->ACPILevel.SclkFrequency = atomctrl_get_reference_घड़ी(hwmgr);

	/* get the engine घड़ी भागiders क्रम this घड़ी value*/
	result = atomctrl_get_engine_pll_भागiders_vi(hwmgr,
		table->ACPILevel.SclkFrequency,  &भागiders);

	PP_ASSERT_WITH_CODE(result == 0,
		"Error retrieving Engine Clock dividers from VBIOS.",
		वापस result);

	/* भागider ID क्रम required SCLK*/
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


	/* For various features to be enabled/disabled जबतक this level is active.*/
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.Flags);
	/* SCLK frequency in units of 10KHz*/
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.SclkFrequency);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CgSpllFuncCntl);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CgSpllFuncCntl2);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CgSpllFuncCntl3);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CgSpllFuncCntl4);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.SpllSpपढ़ोSpectrum);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.SpllSpपढ़ोSpectrum2);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CcPwrDynRm);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CcPwrDynRm1);

	/* table->MemoryACPILevel.MinVddcPhases = table->ACPILevel.MinVddcPhases;*/
	table->MemoryACPILevel.MinVoltage =
			    smu_data->smc_state_table.MemoryLevel[0].MinVoltage;

	/*  CONVERT_FROM_HOST_TO_SMC_UL(table->MemoryACPILevel.MinVoltage);*/

	अगर (0 == tonga_populate_mvdd_value(hwmgr, 0, &voltage_level))
		table->MemoryACPILevel.MinMvdd =
			PP_HOST_TO_SMC_UL(voltage_level.Voltage * VOLTAGE_SCALE);
	अन्यथा
		table->MemoryACPILevel.MinMvdd = 0;

	/* Force reset on DLL*/
	mclk_pwrmgt_cntl    = PHM_SET_FIELD(mclk_pwrmgt_cntl,
		MCLK_PWRMGT_CNTL, MRDCK0_RESET, 0x1);
	mclk_pwrmgt_cntl    = PHM_SET_FIELD(mclk_pwrmgt_cntl,
		MCLK_PWRMGT_CNTL, MRDCK1_RESET, 0x1);

	/* Disable DLL in ACPIState*/
	mclk_pwrmgt_cntl    = PHM_SET_FIELD(mclk_pwrmgt_cntl,
		MCLK_PWRMGT_CNTL, MRDCK0_PDNB, 0);
	mclk_pwrmgt_cntl    = PHM_SET_FIELD(mclk_pwrmgt_cntl,
		MCLK_PWRMGT_CNTL, MRDCK1_PDNB, 0);

	/* Enable DLL bypass संकेत*/
	dll_cntl            = PHM_SET_FIELD(dll_cntl,
		DLL_CNTL, MRDCK0_BYPASS, 0);
	dll_cntl            = PHM_SET_FIELD(dll_cntl,
		DLL_CNTL, MRDCK1_BYPASS, 0);

	table->MemoryACPILevel.DllCntl            =
		PP_HOST_TO_SMC_UL(dll_cntl);
	table->MemoryACPILevel.MclkPwrmgtCntl     =
		PP_HOST_TO_SMC_UL(mclk_pwrmgt_cntl);
	table->MemoryACPILevel.MpllAdFuncCntl     =
		PP_HOST_TO_SMC_UL(data->घड़ी_रेजिस्टरs.vMPLL_AD_FUNC_CNTL);
	table->MemoryACPILevel.MpllDqFuncCntl     =
		PP_HOST_TO_SMC_UL(data->घड़ी_रेजिस्टरs.vMPLL_DQ_FUNC_CNTL);
	table->MemoryACPILevel.MpllFuncCntl       =
		PP_HOST_TO_SMC_UL(data->घड़ी_रेजिस्टरs.vMPLL_FUNC_CNTL);
	table->MemoryACPILevel.MpllFuncCntl_1     =
		PP_HOST_TO_SMC_UL(data->घड़ी_रेजिस्टरs.vMPLL_FUNC_CNTL_1);
	table->MemoryACPILevel.MpllFuncCntl_2     =
		PP_HOST_TO_SMC_UL(data->घड़ी_रेजिस्टरs.vMPLL_FUNC_CNTL_2);
	table->MemoryACPILevel.MpllSs1            =
		PP_HOST_TO_SMC_UL(data->घड़ी_रेजिस्टरs.vMPLL_SS1);
	table->MemoryACPILevel.MpllSs2            =
		PP_HOST_TO_SMC_UL(data->घड़ी_रेजिस्टरs.vMPLL_SS2);

	table->MemoryACPILevel.EnabledForThrottle = 0;
	table->MemoryACPILevel.EnabledForActivity = 0;
	table->MemoryACPILevel.UpHyst = 0;
	table->MemoryACPILevel.DownHyst = 100;
	table->MemoryACPILevel.VoltageDownHyst = 0;
	/* Indicates maximum activity level क्रम this perक्रमmance level.*/
	table->MemoryACPILevel.ActivityLevel =
			PP_HOST_TO_SMC_US(data->current_profile_setting.mclk_activity);

	table->MemoryACPILevel.StutterEnable = 0;
	table->MemoryACPILevel.StrobeEnable = 0;
	table->MemoryACPILevel.EdcReadEnable = 0;
	table->MemoryACPILevel.EdcWriteEnable = 0;
	table->MemoryACPILevel.RttEnable = 0;

	वापस result;
पूर्ण

अटल पूर्णांक tonga_populate_smc_uvd_level(काष्ठा pp_hwmgr *hwmgr,
					SMU72_Discrete_DpmTable *table)
अणु
	पूर्णांक result = 0;

	uपूर्णांक8_t count;
	pp_atomctrl_घड़ी_भागiders_vi भागiders;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *pptable_info =
				(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	phm_ppt_v1_mm_घड़ी_voltage_dependency_table *mm_table =
						pptable_info->mm_dep_table;

	table->UvdLevelCount = (uपूर्णांक8_t) (mm_table->count);
	table->UvdBootLevel = 0;

	क्रम (count = 0; count < table->UvdLevelCount; count++) अणु
		table->UvdLevel[count].VclkFrequency = mm_table->entries[count].vclk;
		table->UvdLevel[count].DclkFrequency = mm_table->entries[count].dclk;
		table->UvdLevel[count].MinVoltage.Vddc =
			phm_get_voltage_index(pptable_info->vddc_lookup_table,
						mm_table->entries[count].vddc);
		table->UvdLevel[count].MinVoltage.VddGfx =
			(data->vdd_gfx_control == SMU7_VOLTAGE_CONTROL_BY_SVID2) ?
			phm_get_voltage_index(pptable_info->vddgfx_lookup_table,
						mm_table->entries[count].vddgfx) : 0;
		table->UvdLevel[count].MinVoltage.Vddci =
			phm_get_voltage_id(&data->vddci_voltage_table,
					     mm_table->entries[count].vddc - VDDC_VDDCI_DELTA);
		table->UvdLevel[count].MinVoltage.Phases = 1;

		/* retrieve भागider value क्रम VBIOS */
		result = atomctrl_get_dfs_pll_भागiders_vi(
					hwmgr,
					table->UvdLevel[count].VclkFrequency,
					&भागiders);

		PP_ASSERT_WITH_CODE((!result),
				    "can not find divide id for Vclk clock",
					वापस result);

		table->UvdLevel[count].VclkDivider = (uपूर्णांक8_t)भागiders.pll_post_भागider;

		result = atomctrl_get_dfs_pll_भागiders_vi(hwmgr,
							  table->UvdLevel[count].DclkFrequency, &भागiders);
		PP_ASSERT_WITH_CODE((!result),
				    "can not find divide id for Dclk clock",
					वापस result);

		table->UvdLevel[count].DclkDivider =
					(uपूर्णांक8_t)भागiders.pll_post_भागider;

		CONVERT_FROM_HOST_TO_SMC_UL(table->UvdLevel[count].VclkFrequency);
		CONVERT_FROM_HOST_TO_SMC_UL(table->UvdLevel[count].DclkFrequency);
	पूर्ण

	वापस result;

पूर्ण

अटल पूर्णांक tonga_populate_smc_vce_level(काष्ठा pp_hwmgr *hwmgr,
		SMU72_Discrete_DpmTable *table)
अणु
	पूर्णांक result = 0;

	uपूर्णांक8_t count;
	pp_atomctrl_घड़ी_भागiders_vi भागiders;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *pptable_info =
			      (काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	phm_ppt_v1_mm_घड़ी_voltage_dependency_table *mm_table =
						     pptable_info->mm_dep_table;

	table->VceLevelCount = (uपूर्णांक8_t) (mm_table->count);
	table->VceBootLevel = 0;

	क्रम (count = 0; count < table->VceLevelCount; count++) अणु
		table->VceLevel[count].Frequency =
			mm_table->entries[count].eclk;
		table->VceLevel[count].MinVoltage.Vddc =
			phm_get_voltage_index(pptable_info->vddc_lookup_table,
				mm_table->entries[count].vddc);
		table->VceLevel[count].MinVoltage.VddGfx =
			(data->vdd_gfx_control == SMU7_VOLTAGE_CONTROL_BY_SVID2) ?
			phm_get_voltage_index(pptable_info->vddgfx_lookup_table,
				mm_table->entries[count].vddgfx) : 0;
		table->VceLevel[count].MinVoltage.Vddci =
			phm_get_voltage_id(&data->vddci_voltage_table,
				mm_table->entries[count].vddc - VDDC_VDDCI_DELTA);
		table->VceLevel[count].MinVoltage.Phases = 1;

		/* retrieve भागider value क्रम VBIOS */
		result = atomctrl_get_dfs_pll_भागiders_vi(hwmgr,
					table->VceLevel[count].Frequency, &भागiders);
		PP_ASSERT_WITH_CODE((!result),
				"can not find divide id for VCE engine clock",
				वापस result);

		table->VceLevel[count].Divider = (uपूर्णांक8_t)भागiders.pll_post_भागider;

		CONVERT_FROM_HOST_TO_SMC_UL(table->VceLevel[count].Frequency);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक tonga_populate_smc_acp_level(काष्ठा pp_hwmgr *hwmgr,
		SMU72_Discrete_DpmTable *table)
अणु
	पूर्णांक result = 0;
	uपूर्णांक8_t count;
	pp_atomctrl_घड़ी_भागiders_vi भागiders;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *pptable_info =
			     (काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	phm_ppt_v1_mm_घड़ी_voltage_dependency_table *mm_table =
						    pptable_info->mm_dep_table;

	table->AcpLevelCount = (uपूर्णांक8_t) (mm_table->count);
	table->AcpBootLevel = 0;

	क्रम (count = 0; count < table->AcpLevelCount; count++) अणु
		table->AcpLevel[count].Frequency =
			pptable_info->mm_dep_table->entries[count].aclk;
		table->AcpLevel[count].MinVoltage.Vddc =
			phm_get_voltage_index(pptable_info->vddc_lookup_table,
			mm_table->entries[count].vddc);
		table->AcpLevel[count].MinVoltage.VddGfx =
			(data->vdd_gfx_control == SMU7_VOLTAGE_CONTROL_BY_SVID2) ?
			phm_get_voltage_index(pptable_info->vddgfx_lookup_table,
				mm_table->entries[count].vddgfx) : 0;
		table->AcpLevel[count].MinVoltage.Vddci =
			phm_get_voltage_id(&data->vddci_voltage_table,
				mm_table->entries[count].vddc - VDDC_VDDCI_DELTA);
		table->AcpLevel[count].MinVoltage.Phases = 1;

		/* retrieve भागider value क्रम VBIOS */
		result = atomctrl_get_dfs_pll_भागiders_vi(hwmgr,
			table->AcpLevel[count].Frequency, &भागiders);
		PP_ASSERT_WITH_CODE((!result),
			"can not find divide id for engine clock", वापस result);

		table->AcpLevel[count].Divider = (uपूर्णांक8_t)भागiders.pll_post_भागider;

		CONVERT_FROM_HOST_TO_SMC_UL(table->AcpLevel[count].Frequency);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक tonga_populate_memory_timing_parameters(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t engine_घड़ी,
		uपूर्णांक32_t memory_घड़ी,
		काष्ठा SMU72_Discrete_MCArbDramTimingTableEntry *arb_regs
		)
अणु
	uपूर्णांक32_t dramTiming;
	uपूर्णांक32_t dramTiming2;
	uपूर्णांक32_t burstTime;
	पूर्णांक result;

	result = atomctrl_set_engine_dram_timings_rv770(hwmgr,
				engine_घड़ी, memory_घड़ी);

	PP_ASSERT_WITH_CODE(result == 0,
		"Error calling VBIOS to set DRAM_TIMING.", वापस result);

	dramTiming  = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_ARB_DRAM_TIMING);
	dramTiming2 = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_ARB_DRAM_TIMING2);
	burstTime = PHM_READ_FIELD(hwmgr->device, MC_ARB_BURST_TIME, STATE0);

	arb_regs->McArbDramTiming  = PP_HOST_TO_SMC_UL(dramTiming);
	arb_regs->McArbDramTiming2 = PP_HOST_TO_SMC_UL(dramTiming2);
	arb_regs->McArbBurstTime = (uपूर्णांक8_t)burstTime;

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_program_memory_timing_parameters(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा tonga_smumgr *smu_data =
				(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	पूर्णांक result = 0;
	SMU72_Discrete_MCArbDramTimingTable  arb_regs;
	uपूर्णांक32_t i, j;

	स_रखो(&arb_regs, 0x00, माप(SMU72_Discrete_MCArbDramTimingTable));

	क्रम (i = 0; i < data->dpm_table.sclk_table.count; i++) अणु
		क्रम (j = 0; j < data->dpm_table.mclk_table.count; j++) अणु
			result = tonga_populate_memory_timing_parameters
				(hwmgr, data->dpm_table.sclk_table.dpm_levels[i].value,
				 data->dpm_table.mclk_table.dpm_levels[j].value,
				 &arb_regs.entries[i][j]);

			अगर (result)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (!result) अणु
		result = smu7_copy_bytes_to_smc(
				hwmgr,
				smu_data->smu7_data.arb_table_start,
				(uपूर्णांक8_t *)&arb_regs,
				माप(SMU72_Discrete_MCArbDramTimingTable),
				SMC_RAM_END
				);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक tonga_populate_smc_boot_level(काष्ठा pp_hwmgr *hwmgr,
			SMU72_Discrete_DpmTable *table)
अणु
	पूर्णांक result = 0;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा tonga_smumgr *smu_data =
				(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	table->GraphicsBootLevel = 0;
	table->MemoryBootLevel = 0;

	/* find boot level from dpm table*/
	result = phm_find_boot_level(&(data->dpm_table.sclk_table),
	data->vbios_boot_state.sclk_bootup_value,
	(uपूर्णांक32_t *)&(smu_data->smc_state_table.GraphicsBootLevel));

	अगर (result != 0) अणु
		smu_data->smc_state_table.GraphicsBootLevel = 0;
		pr_err("[powerplay] VBIOS did not find boot engine "
				"clock value in dependency table. "
				"Using Graphics DPM level 0 !");
		result = 0;
	पूर्ण

	result = phm_find_boot_level(&(data->dpm_table.mclk_table),
		data->vbios_boot_state.mclk_bootup_value,
		(uपूर्णांक32_t *)&(smu_data->smc_state_table.MemoryBootLevel));

	अगर (result != 0) अणु
		smu_data->smc_state_table.MemoryBootLevel = 0;
		pr_err("[powerplay] VBIOS did not find boot "
				"engine clock value in dependency table."
				"Using Memory DPM level 0 !");
		result = 0;
	पूर्ण

	table->BootVoltage.Vddc =
		phm_get_voltage_id(&(data->vddc_voltage_table),
			data->vbios_boot_state.vddc_bootup_value);
	table->BootVoltage.VddGfx =
		phm_get_voltage_id(&(data->vddgfx_voltage_table),
			data->vbios_boot_state.vddgfx_bootup_value);
	table->BootVoltage.Vddci =
		phm_get_voltage_id(&(data->vddci_voltage_table),
			data->vbios_boot_state.vddci_bootup_value);
	table->BootMVdd = data->vbios_boot_state.mvdd_bootup_value;

	CONVERT_FROM_HOST_TO_SMC_US(table->BootMVdd);

	वापस result;
पूर्ण

अटल पूर्णांक tonga_populate_घड़ी_stretcher_data_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t ro, efuse, efuse2, घड़ी_freq, volt_without_cks,
			volt_with_cks, value;
	uपूर्णांक16_t घड़ी_freq_u16;
	काष्ठा tonga_smumgr *smu_data =
				(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक8_t type, i, j, cks_setting, stretch_amount, stretch_amount2,
			volt_offset = 0;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *sclk_table =
			table_info->vdd_dep_on_sclk;
	uपूर्णांक32_t hw_revision, dev_id;
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	stretch_amount = (uपूर्णांक8_t)table_info->cac_dtp_table->usClockStretchAmount;

	hw_revision = adev->pdev->revision;
	dev_id = adev->pdev->device;

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
		अगर (ASICID_IS_TONGA_P(dev_id, hw_revision)) अणु
			volt_without_cks = (uपूर्णांक32_t)((7732 + 60 - ro - 20838 *
				(sclk_table->entries[i].clk/100) / 10000) * 1000 /
				(8730 - (5301 * (sclk_table->entries[i].clk/100) / 1000)));
			volt_with_cks = (uपूर्णांक32_t)((5250 + 51 - ro - 2404 *
				(sclk_table->entries[i].clk/100) / 100000) * 1000 /
				(6146 - (3193 * (sclk_table->entries[i].clk/100) / 1000)));
		पूर्ण अन्यथा अणु
			volt_without_cks = (uपूर्णांक32_t)((14041 *
				(sclk_table->entries[i].clk/100) / 10000 + 3571 + 75 - ro) * 1000 /
				(4026 - (13924 * (sclk_table->entries[i].clk/100) / 10000)));
			volt_with_cks = (uपूर्णांक32_t)((13946 *
				(sclk_table->entries[i].clk/100) / 10000 + 3320 + 45 - ro) * 1000 /
				(3664 - (11454 * (sclk_table->entries[i].clk/100) / 10000)));
		पूर्ण
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
			tonga_घड़ी_stretcher_lookup_table[stretch_amount2][0];
	smu_data->smc_state_table.CKS_LOOKUPTable.CKS_LOOKUPTableEntry[0].maxFreq =
			tonga_घड़ी_stretcher_lookup_table[stretch_amount2][1];
	घड़ी_freq_u16 = (uपूर्णांक16_t)(PP_SMC_TO_HOST_UL(smu_data->smc_state_table.
			GraphicsLevel[smu_data->smc_state_table.GraphicsDpmLevelCount - 1].
			SclkFrequency) / 100);
	अगर (tonga_घड़ी_stretcher_lookup_table[stretch_amount2][0] <
			घड़ी_freq_u16 &&
	    tonga_घड़ी_stretcher_lookup_table[stretch_amount2][1] >
			घड़ी_freq_u16) अणु
		/* Program PWR_CKS_CNTL. CKS_USE_FOR_LOW_FREQ */
		value |= (tonga_घड़ी_stretcher_lookup_table[stretch_amount2][3]) << 16;
		/* Program PWR_CKS_CNTL. CKS_LDO_REFSEL */
		value |= (tonga_घड़ी_stretcher_lookup_table[stretch_amount2][2]) << 18;
		/* Program PWR_CKS_CNTL. CKS_STRETCH_AMOUNT */
		value |= (tonga_घड़ी_stretch_amount_conversion
				[tonga_घड़ी_stretcher_lookup_table[stretch_amount2][3]]
				 [stretch_amount]) << 3;
	पूर्ण
	CONVERT_FROM_HOST_TO_SMC_US(smu_data->smc_state_table.CKS_LOOKUPTable.
			CKS_LOOKUPTableEntry[0].minFreq);
	CONVERT_FROM_HOST_TO_SMC_US(smu_data->smc_state_table.CKS_LOOKUPTable.
			CKS_LOOKUPTableEntry[0].maxFreq);
	smu_data->smc_state_table.CKS_LOOKUPTable.CKS_LOOKUPTableEntry[0].setting =
			tonga_घड़ी_stretcher_lookup_table[stretch_amount2][2] & 0x7F;
	smu_data->smc_state_table.CKS_LOOKUPTable.CKS_LOOKUPTableEntry[0].setting |=
			(tonga_घड़ी_stretcher_lookup_table[stretch_amount2][3]) << 7;

	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			ixPWR_CKS_CNTL, value);

	/* Populate DDT Lookup Table */
	क्रम (i = 0; i < 4; i++) अणु
		/* Assign the minimum and maximum VID stored
		 * in the last row of Clock Stretcher Voltage Table.
		 */
		smu_data->smc_state_table.ClockStretcherDataTable.
		ClockStretcherDataTableEntry[i].minVID =
				(uपूर्णांक8_t) tonga_घड़ी_stretcher_ddt_table[type][i][2];
		smu_data->smc_state_table.ClockStretcherDataTable.
		ClockStretcherDataTableEntry[i].maxVID =
				(uपूर्णांक8_t) tonga_घड़ी_stretcher_ddt_table[type][i][3];
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
			अगर (घड़ी_freq >= tonga_घड़ी_stretcher_ddt_table[type][i][0] * 100) अणु
				cks_setting |= 0x2;
				अगर (घड़ी_freq < tonga_घड़ी_stretcher_ddt_table[type][i][1] * 100)
					cks_setting |= 0x1;
			पूर्ण
			smu_data->smc_state_table.ClockStretcherDataTable.
			ClockStretcherDataTableEntry[i].setting |= cks_setting << (j * 2);
		पूर्ण
		CONVERT_FROM_HOST_TO_SMC_US(smu_data->smc_state_table.
				ClockStretcherDataTable.
				ClockStretcherDataTableEntry[i].setting);
	पूर्ण

	value = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
					ixPWR_CKS_CNTL);
	value &= 0xFFFFFFFE;
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
					ixPWR_CKS_CNTL, value);

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_vr_config(काष्ठा pp_hwmgr *hwmgr,
			SMU72_Discrete_DpmTable *table)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक16_t config;

	अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->vdd_gfx_control) अणु
		/*  Splitted mode */
		config = VR_SVI2_PLANE_1;
		table->VRConfig |= (config<<VRCONF_VDDGFX_SHIFT);

		अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->voltage_control) अणु
			config = VR_SVI2_PLANE_2;
			table->VRConfig |= config;
		पूर्ण अन्यथा अणु
			pr_err("VDDC and VDDGFX should "
				"be both on SVI2 control in splitted mode !\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Merged mode  */
		config = VR_MERGED_WITH_VDDC;
		table->VRConfig |= (config<<VRCONF_VDDGFX_SHIFT);

		/* Set Vddc Voltage Controller  */
		अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->voltage_control) अणु
			config = VR_SVI2_PLANE_1;
			table->VRConfig |= config;
		पूर्ण अन्यथा अणु
			pr_err("VDDC should be on "
					"SVI2 control in merged mode !\n");
		पूर्ण
	पूर्ण

	/* Set Vddci Voltage Controller  */
	अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->vddci_control) अणु
		config = VR_SVI2_PLANE_2;  /* only in merged mode */
		table->VRConfig |= (config<<VRCONF_VDDCI_SHIFT);
	पूर्ण अन्यथा अगर (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->vddci_control) अणु
		config = VR_SMIO_PATTERN_1;
		table->VRConfig |= (config<<VRCONF_VDDCI_SHIFT);
	पूर्ण

	/* Set Mvdd Voltage Controller */
	अगर (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->mvdd_control) अणु
		config = VR_SMIO_PATTERN_2;
		table->VRConfig |= (config<<VRCONF_MVDD_SHIFT);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_init_arb_table_index(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा tonga_smumgr *smu_data = (काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t पंचांगp;
	पूर्णांक result;

	/*
	* This is a पढ़ो-modअगरy-ग_लिखो on the first byte of the ARB table.
	* The first byte in the SMU72_Discrete_MCArbDramTimingTable काष्ठाure
	* is the field 'current'.
	* This solution is ugly, but we never ग_लिखो the whole table only
	* inभागidual fields in it.
	* In reality this field should not be in that काष्ठाure
	* but in a soft रेजिस्टर.
	*/
	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
				smu_data->smu7_data.arb_table_start, &पंचांगp, SMC_RAM_END);

	अगर (result != 0)
		वापस result;

	पंचांगp &= 0x00FFFFFF;
	पंचांगp |= ((uपूर्णांक32_t)MC_CG_ARB_FREQ_F1) << 24;

	वापस smu7_ग_लिखो_smc_sram_dword(hwmgr,
			smu_data->smu7_data.arb_table_start, पंचांगp, SMC_RAM_END);
पूर्ण


अटल पूर्णांक tonga_populate_bapm_parameters_in_dpm_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा tonga_smumgr *smu_data =
				(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	स्थिर काष्ठा tonga_pt_शेषs *शेषs = smu_data->घातer_tune_शेषs;
	SMU72_Discrete_DpmTable  *dpm_table = &(smu_data->smc_state_table);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_cac_tdp_table *cac_dtp_table = table_info->cac_dtp_table;
	पूर्णांक  i, j, k;
	स्थिर uपूर्णांक16_t *pdef1, *pdef2;

	dpm_table->DefaultTdp = PP_HOST_TO_SMC_US(
			(uपूर्णांक16_t)(cac_dtp_table->usTDP * 256));
	dpm_table->TargetTdp = PP_HOST_TO_SMC_US(
			(uपूर्णांक16_t)(cac_dtp_table->usConfigurableTDP * 256));

	PP_ASSERT_WITH_CODE(cac_dtp_table->usTargetOperatingTemp <= 255,
			"Target Operating Temp is out of Range !",
			);

	dpm_table->GpuTjMax = (uपूर्णांक8_t)(cac_dtp_table->usTargetOperatingTemp);
	dpm_table->GpuTjHyst = 8;

	dpm_table->DTEAmbientTempBase = शेषs->dte_ambient_temp_base;

	dpm_table->BAPM_TEMP_GRADIENT =
				PP_HOST_TO_SMC_UL(शेषs->bapm_temp_gradient);
	pdef1 = शेषs->bapmti_r;
	pdef2 = शेषs->bapmti_rc;

	क्रम (i = 0; i < SMU72_DTE_ITERATIONS; i++) अणु
		क्रम (j = 0; j < SMU72_DTE_SOURCES; j++) अणु
			क्रम (k = 0; k < SMU72_DTE_SINKS; k++) अणु
				dpm_table->BAPMTI_R[i][j][k] =
						PP_HOST_TO_SMC_US(*pdef1);
				dpm_table->BAPMTI_RC[i][j][k] =
						PP_HOST_TO_SMC_US(*pdef2);
				pdef1++;
				pdef2++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_svi_load_line(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा tonga_smumgr *smu_data =
				(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	स्थिर काष्ठा tonga_pt_शेषs *शेषs = smu_data->घातer_tune_शेषs;

	smu_data->घातer_tune_table.SviLoadLineEn = शेषs->svi_load_line_en;
	smu_data->घातer_tune_table.SviLoadLineVddC = शेषs->svi_load_line_vddC;
	smu_data->घातer_tune_table.SviLoadLineTrimVddC = 3;
	smu_data->घातer_tune_table.SviLoadLineOffsetVddC = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_tdc_limit(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक16_t tdc_limit;
	काष्ठा tonga_smumgr *smu_data =
				(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	स्थिर काष्ठा tonga_pt_शेषs *शेषs = smu_data->घातer_tune_शेषs;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	/* TDC number of fraction bits are changed from 8 to 7
	 * क्रम Fiji as requested by SMC team
	 */
	tdc_limit = (uपूर्णांक16_t)(table_info->cac_dtp_table->usTDC * 256);
	smu_data->घातer_tune_table.TDC_VDDC_PkgLimit =
			CONVERT_FROM_HOST_TO_SMC_US(tdc_limit);
	smu_data->घातer_tune_table.TDC_VDDC_ThrottleReleaseLimitPerc =
			शेषs->tdc_vddc_throttle_release_limit_perc;
	smu_data->घातer_tune_table.TDC_MAWt = शेषs->tdc_mawt;

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_dw8(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t fuse_table_offset)
अणु
	काष्ठा tonga_smumgr *smu_data =
			(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	स्थिर काष्ठा tonga_pt_शेषs *शेषs = smu_data->घातer_tune_शेषs;
	uपूर्णांक32_t temp;

	अगर (smu7_पढ़ो_smc_sram_dword(hwmgr,
			fuse_table_offset +
			दुरत्व(SMU72_Discrete_PmFuses, TdcWaterfallCtl),
			(uपूर्णांक32_t *)&temp, SMC_RAM_END))
		PP_ASSERT_WITH_CODE(false,
				"Attempt to read PmFuses.DW6 "
				"(SviLoadLineEn) from SMC Failed !",
				वापस -EINVAL);
	अन्यथा
		smu_data->घातer_tune_table.TdcWaterfallCtl = शेषs->tdc_waterfall_ctl;

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_temperature_scaler(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक i;
	काष्ठा tonga_smumgr *smu_data =
				(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);

	/* Currently not used. Set all to zero. */
	क्रम (i = 0; i < 16; i++)
		smu_data->घातer_tune_table.LPMLTemperatureScaler[i] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_fuzzy_fan(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा tonga_smumgr *smu_data = (काष्ठा tonga_smumgr *)(hwmgr->smu_backend);

	अगर ((hwmgr->thermal_controller.advanceFanControlParameters.
			usFanOutputSensitivity & (1 << 15)) ||
		(hwmgr->thermal_controller.advanceFanControlParameters.usFanOutputSensitivity == 0))
		hwmgr->thermal_controller.advanceFanControlParameters.
		usFanOutputSensitivity = hwmgr->thermal_controller.
			advanceFanControlParameters.usDefaultFanOutputSensitivity;

	smu_data->घातer_tune_table.FuzzyFan_PwmSetDelta =
			PP_HOST_TO_SMC_US(hwmgr->thermal_controller.
					advanceFanControlParameters.usFanOutputSensitivity);
	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_gnb_lpml(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक i;
	काष्ठा tonga_smumgr *smu_data =
				(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);

	/* Currently not used. Set all to zero. */
	क्रम (i = 0; i < 16; i++)
		smu_data->घातer_tune_table.GnbLPML[i] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_bapm_vddc_base_leakage_sidd(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा tonga_smumgr *smu_data =
				(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
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

अटल पूर्णांक tonga_populate_pm_fuses(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा tonga_smumgr *smu_data =
				(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t pm_fuse_table_offset;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_PowerContainment)) अणु
		अगर (smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU72_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU72_Firmware_Header, PmFuseTable),
				&pm_fuse_table_offset, SMC_RAM_END))
			PP_ASSERT_WITH_CODE(false,
				"Attempt to get pm_fuse_table_offset Failed !",
				वापस -EINVAL);

		/* DW6 */
		अगर (tonga_populate_svi_load_line(hwmgr))
			PP_ASSERT_WITH_CODE(false,
				"Attempt to populate SviLoadLine Failed !",
				वापस -EINVAL);
		/* DW7 */
		अगर (tonga_populate_tdc_limit(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate TDCLimit Failed !",
					वापस -EINVAL);
		/* DW8 */
		अगर (tonga_populate_dw8(hwmgr, pm_fuse_table_offset))
			PP_ASSERT_WITH_CODE(false,
				"Attempt to populate TdcWaterfallCtl Failed !",
				वापस -EINVAL);

		/* DW9-DW12 */
		अगर (tonga_populate_temperature_scaler(hwmgr) != 0)
			PP_ASSERT_WITH_CODE(false,
				"Attempt to populate LPMLTemperatureScaler Failed !",
				वापस -EINVAL);

		/* DW13-DW14 */
		अगर (tonga_populate_fuzzy_fan(hwmgr))
			PP_ASSERT_WITH_CODE(false,
				"Attempt to populate Fuzzy Fan "
				"Control parameters Failed !",
				वापस -EINVAL);

		/* DW15-DW18 */
		अगर (tonga_populate_gnb_lpml(hwmgr))
			PP_ASSERT_WITH_CODE(false,
				"Attempt to populate GnbLPML Failed !",
				वापस -EINVAL);

		/* DW20 */
		अगर (tonga_populate_bapm_vddc_base_leakage_sidd(hwmgr))
			PP_ASSERT_WITH_CODE(
				false,
				"Attempt to populate BapmVddCBaseLeakage "
				"Hi and Lo Sidd Failed !",
				वापस -EINVAL);

		अगर (smu7_copy_bytes_to_smc(hwmgr, pm_fuse_table_offset,
				(uपूर्णांक8_t *)&smu_data->घातer_tune_table,
				माप(काष्ठा SMU72_Discrete_PmFuses), SMC_RAM_END))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to download PmFuseTable Failed !",
					वापस -EINVAL);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tonga_populate_mc_reg_address(काष्ठा pp_hwmgr *hwmgr,
				 SMU72_Discrete_MCRegisters *mc_reg_table)
अणु
	स्थिर काष्ठा tonga_smumgr *smu_data = (काष्ठा tonga_smumgr *)hwmgr->smu_backend;

	uपूर्णांक32_t i, j;

	क्रम (i = 0, j = 0; j < smu_data->mc_reg_table.last; j++) अणु
		अगर (smu_data->mc_reg_table.validflag & 1<<j) अणु
			PP_ASSERT_WITH_CODE(
				i < SMU72_DISCRETE_MC_REGISTER_ARRAY_SIZE,
				"Index of mc_reg_table->address[] array "
				"out of boundary",
				वापस -EINVAL);
			mc_reg_table->address[i].s0 =
				PP_HOST_TO_SMC_US(smu_data->mc_reg_table.mc_reg_address[j].s0);
			mc_reg_table->address[i].s1 =
				PP_HOST_TO_SMC_US(smu_data->mc_reg_table.mc_reg_address[j].s1);
			i++;
		पूर्ण
	पूर्ण

	mc_reg_table->last = (uपूर्णांक8_t)i;

	वापस 0;
पूर्ण

/*convert रेजिस्टर values from driver to SMC क्रमmat */
अटल व्योम tonga_convert_mc_रेजिस्टरs(
	स्थिर काष्ठा tonga_mc_reg_entry *entry,
	SMU72_Discrete_MCRegisterSet *data,
	uपूर्णांक32_t num_entries, uपूर्णांक32_t valid_flag)
अणु
	uपूर्णांक32_t i, j;

	क्रम (i = 0, j = 0; j < num_entries; j++) अणु
		अगर (valid_flag & 1<<j) अणु
			data->value[i] = PP_HOST_TO_SMC_UL(entry->mc_data[j]);
			i++;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक tonga_convert_mc_reg_table_entry_to_smc(
		काष्ठा pp_hwmgr *hwmgr,
		स्थिर uपूर्णांक32_t memory_घड़ी,
		SMU72_Discrete_MCRegisterSet *mc_reg_table_data
		)
अणु
	काष्ठा tonga_smumgr *smu_data = (काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t i = 0;

	क्रम (i = 0; i < smu_data->mc_reg_table.num_entries; i++) अणु
		अगर (memory_घड़ी <=
			smu_data->mc_reg_table.mc_reg_table_entry[i].mclk_max) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर ((i == smu_data->mc_reg_table.num_entries) && (i > 0))
		--i;

	tonga_convert_mc_रेजिस्टरs(&smu_data->mc_reg_table.mc_reg_table_entry[i],
				mc_reg_table_data, smu_data->mc_reg_table.last,
				smu_data->mc_reg_table.validflag);

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_convert_mc_reg_table_to_smc(काष्ठा pp_hwmgr *hwmgr,
		SMU72_Discrete_MCRegisters *mc_regs)
अणु
	पूर्णांक result = 0;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	पूर्णांक res;
	uपूर्णांक32_t i;

	क्रम (i = 0; i < data->dpm_table.mclk_table.count; i++) अणु
		res = tonga_convert_mc_reg_table_entry_to_smc(
				hwmgr,
				data->dpm_table.mclk_table.dpm_levels[i].value,
				&mc_regs->data[i]
				);

		अगर (0 != res)
			result = res;
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक tonga_update_and_upload_mc_reg_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा tonga_smumgr *smu_data = (काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t address;
	पूर्णांक32_t result;

	अगर (0 == (data->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_MCLK))
		वापस 0;


	स_रखो(&smu_data->mc_regs, 0, माप(SMU72_Discrete_MCRegisters));

	result = tonga_convert_mc_reg_table_to_smc(hwmgr, &(smu_data->mc_regs));

	अगर (result != 0)
		वापस result;


	address = smu_data->smu7_data.mc_reg_table_start +
			(uपूर्णांक32_t)दुरत्व(SMU72_Discrete_MCRegisters, data[0]);

	वापस  smu7_copy_bytes_to_smc(
			hwmgr, address,
			(uपूर्णांक8_t *)&smu_data->mc_regs.data[0],
			माप(SMU72_Discrete_MCRegisterSet) *
			data->dpm_table.mclk_table.count,
			SMC_RAM_END);
पूर्ण

अटल पूर्णांक tonga_populate_initial_mc_reg_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	काष्ठा tonga_smumgr *smu_data = (काष्ठा tonga_smumgr *)(hwmgr->smu_backend);

	स_रखो(&smu_data->mc_regs, 0x00, माप(SMU72_Discrete_MCRegisters));
	result = tonga_populate_mc_reg_address(hwmgr, &(smu_data->mc_regs));
	PP_ASSERT_WITH_CODE(!result,
		"Failed to initialize MCRegTable for the MC register addresses !",
		वापस result;);

	result = tonga_convert_mc_reg_table_to_smc(hwmgr, &smu_data->mc_regs);
	PP_ASSERT_WITH_CODE(!result,
		"Failed to initialize MCRegTable for driver state !",
		वापस result;);

	वापस smu7_copy_bytes_to_smc(hwmgr, smu_data->smu7_data.mc_reg_table_start,
			(uपूर्णांक8_t *)&smu_data->mc_regs, माप(SMU72_Discrete_MCRegisters), SMC_RAM_END);
पूर्ण

अटल व्योम tonga_initialize_घातer_tune_शेषs(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा tonga_smumgr *smu_data = (काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	काष्ठा  phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा  phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	अगर (table_info &&
			table_info->cac_dtp_table->usPowerTuneDataSetID <= POWERTUNE_DEFAULT_SET_MAX &&
			table_info->cac_dtp_table->usPowerTuneDataSetID)
		smu_data->घातer_tune_शेषs =
				&tonga_घातer_tune_data_set_array
				[table_info->cac_dtp_table->usPowerTuneDataSetID - 1];
	अन्यथा
		smu_data->घातer_tune_शेषs = &tonga_घातer_tune_data_set_array[0];
पूर्ण

अटल पूर्णांक tonga_init_smc_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा tonga_smumgr *smu_data =
			(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	SMU72_Discrete_DpmTable *table = &(smu_data->smc_state_table);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	uपूर्णांक8_t i;
	pp_atomctrl_gpio_pin_assignment gpio_pin_assignment;


	स_रखो(&(smu_data->smc_state_table), 0x00, माप(smu_data->smc_state_table));

	tonga_initialize_घातer_tune_शेषs(hwmgr);

	अगर (SMU7_VOLTAGE_CONTROL_NONE != data->voltage_control)
		tonga_populate_smc_voltage_tables(hwmgr, table);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_AutomaticDCTransition))
		table->SystemFlags |= PPSMC_SYSTEMFLAG_GPIO_DC;


	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_StepVddc))
		table->SystemFlags |= PPSMC_SYSTEMFLAG_STEPVDDC;

	अगर (data->is_memory_gddr5)
		table->SystemFlags |= PPSMC_SYSTEMFLAG_GDDR5;

	i = PHM_READ_FIELD(hwmgr->device, CC_MC_MAX_CHANNEL, NOOFCHAN);

	अगर (i == 1 || i == 0)
		table->SystemFlags |= 0x40;

	अगर (data->ulv_supported && table_info->us_ulv_voltage_offset) अणु
		result = tonga_populate_ulv_state(hwmgr, table);
		PP_ASSERT_WITH_CODE(!result,
			"Failed to initialize ULV state !",
			वापस result;);

		cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			ixCG_ULV_PARAMETER, 0x40035);
	पूर्ण

	result = tonga_populate_smc_link_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
		"Failed to initialize Link Level !", वापस result);

	result = tonga_populate_all_graphic_levels(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
		"Failed to initialize Graphics Level !", वापस result);

	result = tonga_populate_all_memory_levels(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
		"Failed to initialize Memory Level !", वापस result);

	result = tonga_populate_smc_acpi_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
		"Failed to initialize ACPI Level !", वापस result);

	result = tonga_populate_smc_vce_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
		"Failed to initialize VCE Level !", वापस result);

	result = tonga_populate_smc_acp_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
		"Failed to initialize ACP Level !", वापस result);

	/* Since only the initial state is completely set up at this
	* poपूर्णांक (the other states are just copies of the boot state) we only
	* need to populate the  ARB settings क्रम the initial state.
	*/
	result = tonga_program_memory_timing_parameters(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
		"Failed to Write ARB settings for the initial state.",
		वापस result;);

	result = tonga_populate_smc_uvd_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
		"Failed to initialize UVD Level !", वापस result);

	result = tonga_populate_smc_boot_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
		"Failed to initialize Boot Level !", वापस result);

	tonga_populate_bapm_parameters_in_dpm_table(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
		"Failed to populate BAPM Parameters !", वापस result);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_ClockStretcher)) अणु
		result = tonga_populate_घड़ी_stretcher_data_table(hwmgr);
		PP_ASSERT_WITH_CODE(!result,
			"Failed to populate Clock Stretcher Data Table !",
			वापस result;);
	पूर्ण
	table->GraphicsVoltageChangeEnable  = 1;
	table->GraphicsThermThrottleEnable  = 1;
	table->GraphicsInterval = 1;
	table->VoltageInterval  = 1;
	table->ThermalInterval  = 1;
	table->TemperatureLimitHigh =
		table_info->cac_dtp_table->usTargetOperatingTemp *
		SMU7_Q88_FORMAT_CONVERSION_UNIT;
	table->TemperatureLimitLow =
		(table_info->cac_dtp_table->usTargetOperatingTemp - 1) *
		SMU7_Q88_FORMAT_CONVERSION_UNIT;
	table->MemoryVoltageChangeEnable  = 1;
	table->MemoryInterval  = 1;
	table->VoltageResponseTime  = 0;
	table->PhaseResponseTime  = 0;
	table->MemoryThermThrottleEnable  = 1;

	/*
	* Cail पढ़ोs current link status and reports it as cap (we cannot
	* change this due to some previous issues we had)
	* SMC drops the link status to lowest level after enabling
	* DPM by PowerPlay. After pnp or toggling CF, driver माला_लो reloaded again
	* but this समय Cail पढ़ोs current link status which was set to low by
	* SMC and reports it as cap to घातerplay
	* To aव्योम it, we set PCIeBootLinkLevel to highest dpm level
	*/
	PP_ASSERT_WITH_CODE((1 <= data->dpm_table.pcie_speed_table.count),
			"There must be 1 or more PCIE levels defined in PPTable.",
			वापस -EINVAL);

	table->PCIeBootLinkLevel = (uपूर्णांक8_t) (data->dpm_table.pcie_speed_table.count);

	table->PCIeGenInterval  = 1;

	result = tonga_populate_vr_config(hwmgr, table);
	PP_ASSERT_WITH_CODE(!result,
		"Failed to populate VRConfig setting !", वापस result);
	data->vr_config = table->VRConfig;
	table->ThermGpio  = 17;
	table->SclkStepSize = 0x4000;

	अगर (atomctrl_get_pp_assign_pin(hwmgr, VDDC_VRHOT_GPIO_PINID,
						&gpio_pin_assignment)) अणु
		table->VRHotGpio = gpio_pin_assignment.uc_gpio_pin_bit_shअगरt;
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_RegulatorHot);
	पूर्ण अन्यथा अणु
		table->VRHotGpio = SMU7_UNUSED_GPIO_PIN;
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_RegulatorHot);
	पूर्ण

	अगर (atomctrl_get_pp_assign_pin(hwmgr, PP_AC_DC_SWITCH_GPIO_PINID,
						&gpio_pin_assignment)) अणु
		table->AcDcGpio = gpio_pin_assignment.uc_gpio_pin_bit_shअगरt;
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_AutomaticDCTransition);
	पूर्ण अन्यथा अणु
		table->AcDcGpio = SMU7_UNUSED_GPIO_PIN;
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_AutomaticDCTransition);
	पूर्ण

	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
		PHM_Platक्रमmCaps_Falcon_QuickTransition);

	अगर (0) अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_AutomaticDCTransition);
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_Falcon_QuickTransition);
	पूर्ण

	अगर (atomctrl_get_pp_assign_pin(hwmgr,
			THERMAL_INT_OUTPUT_GPIO_PINID, &gpio_pin_assignment)) अणु
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_ThermalOutGPIO);

		table->ThermOutGpio = gpio_pin_assignment.uc_gpio_pin_bit_shअगरt;

		table->ThermOutPolarity =
			(0 == (cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmGPIOPAD_A) &
			(1 << gpio_pin_assignment.uc_gpio_pin_bit_shअगरt))) ? 1 : 0;

		table->ThermOutMode = SMU7_THERM_OUT_MODE_THERM_ONLY;

		/* अगर required, combine VRHot/PCC with thermal out GPIO*/
		अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_RegulatorHot) &&
			phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_CombinePCCWithThermalSignal))अणु
			table->ThermOutMode = SMU7_THERM_OUT_MODE_THERM_VRHOT;
		पूर्ण
	पूर्ण अन्यथा अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_ThermalOutGPIO);

		table->ThermOutGpio = 17;
		table->ThermOutPolarity = 1;
		table->ThermOutMode = SMU7_THERM_OUT_MODE_DISABLE;
	पूर्ण

	क्रम (i = 0; i < SMU72_MAX_ENTRIES_SMIO; i++)
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
	result = smu7_copy_bytes_to_smc(
			hwmgr,
			smu_data->smu7_data.dpm_table_start + दुरत्व(SMU72_Discrete_DpmTable, SystemFlags),
			(uपूर्णांक8_t *)&(table->SystemFlags),
			माप(SMU72_Discrete_DpmTable) - 3 * माप(SMU72_PIDController),
			SMC_RAM_END);

	PP_ASSERT_WITH_CODE(!result,
		"Failed to upload dpm data to SMC memory !", वापस result;);

	result = tonga_init_arb_table_index(hwmgr);
	PP_ASSERT_WITH_CODE(!result,
			"Failed to upload arb data to SMC memory !", वापस result);

	tonga_populate_pm_fuses(hwmgr);
	PP_ASSERT_WITH_CODE((!result),
		"Failed to populate initialize pm fuses !", वापस result);

	result = tonga_populate_initial_mc_reg_table(hwmgr);
	PP_ASSERT_WITH_CODE((!result),
		"Failed to populate initialize MC Reg table !", वापस result);

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_thermal_setup_fan_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा tonga_smumgr *smu_data =
			(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	SMU72_Discrete_FanTable fan_table = अणु FDO_MODE_HARDWARE पूर्ण;
	uपूर्णांक32_t duty100;
	uपूर्णांक32_t t_dअगरf1, t_dअगरf2, pwm_dअगरf1, pwm_dअगरf2;
	uपूर्णांक16_t fकरो_min, slope1, slope2;
	uपूर्णांक32_t reference_घड़ी;
	पूर्णांक res;
	uपूर्णांक64_t पंचांगp64;

	अगर (!phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_MicrocodeFanControl))
		वापस 0;

	अगर (hwmgr->thermal_controller.fanInfo.bNoFan) अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_MicrocodeFanControl);
		वापस 0;
	पूर्ण

	अगर (0 == smu_data->smu7_data.fan_table_start) अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_MicrocodeFanControl);
		वापस 0;
	पूर्ण

	duty100 = PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device,
						CGS_IND_REG__SMC,
						CG_FDO_CTRL1, FMAX_DUTY100);

	अगर (0 == duty100) अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_MicrocodeFanControl);
		वापस 0;
	पूर्ण

	पंचांगp64 = hwmgr->thermal_controller.advanceFanControlParameters.usPWMMin * duty100;
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

	fan_table.TempMin = cpu_to_be16((50 + hwmgr->thermal_controller.advanceFanControlParameters.usTMin) / 100);
	fan_table.TempMed = cpu_to_be16((50 + hwmgr->thermal_controller.advanceFanControlParameters.usTMed) / 100);
	fan_table.TempMax = cpu_to_be16((50 + hwmgr->thermal_controller.advanceFanControlParameters.usTMax) / 100);

	fan_table.Slope1 = cpu_to_be16(slope1);
	fan_table.Slope2 = cpu_to_be16(slope2);

	fan_table.FकरोMin = cpu_to_be16(fकरो_min);

	fan_table.HystDown = cpu_to_be16(hwmgr->thermal_controller.advanceFanControlParameters.ucTHyst);

	fan_table.HystUp = cpu_to_be16(1);

	fan_table.HystSlope = cpu_to_be16(1);

	fan_table.TempRespLim = cpu_to_be16(5);

	reference_घड़ी = amdgpu_asic_get_xclk((काष्ठा amdgpu_device *)hwmgr->adev);

	fan_table.RefreshPeriod = cpu_to_be32((hwmgr->thermal_controller.advanceFanControlParameters.ulCycleDelay * reference_घड़ी) / 1600);

	fan_table.FकरोMax = cpu_to_be16((uपूर्णांक16_t)duty100);

	fan_table.TempSrc = (uपूर्णांक8_t)PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, CG_MULT_THERMAL_CTRL, TEMP_SEL);

	fan_table.FanControl_GL_Flag = 1;

	res = smu7_copy_bytes_to_smc(hwmgr,
					smu_data->smu7_data.fan_table_start,
					(uपूर्णांक8_t *)&fan_table,
					(uपूर्णांक32_t)माप(fan_table),
					SMC_RAM_END);

	वापस res;
पूर्ण


अटल पूर्णांक tonga_program_mem_timing_parameters(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (data->need_update_smu7_dpm_table &
		(DPMTABLE_OD_UPDATE_SCLK + DPMTABLE_OD_UPDATE_MCLK))
		वापस tonga_program_memory_timing_parameters(hwmgr);

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_update_sclk_threshold(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा tonga_smumgr *smu_data =
			(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);

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
				दुरत्व(SMU72_Discrete_DpmTable,
					LowSclkInterruptThreshold),
				(uपूर्णांक8_t *)&low_sclk_पूर्णांकerrupt_threshold,
				माप(uपूर्णांक32_t),
				SMC_RAM_END);
	पूर्ण

	result = tonga_update_and_upload_mc_reg_table(hwmgr);

	PP_ASSERT_WITH_CODE((!result),
				"Failed to upload MC reg table !",
				वापस result);

	result = tonga_program_mem_timing_parameters(hwmgr);
	PP_ASSERT_WITH_CODE((result == 0),
			"Failed to program memory timing parameters !",
			);

	वापस result;
पूर्ण

अटल uपूर्णांक32_t tonga_get_दुरत्व(uपूर्णांक32_t type, uपूर्णांक32_t member)
अणु
	चयन (type) अणु
	हाल SMU_SoftRegisters:
		चयन (member) अणु
		हाल HandshakeDisables:
			वापस दुरत्व(SMU72_SoftRegisters, HandshakeDisables);
		हाल VoltageChangeTimeout:
			वापस दुरत्व(SMU72_SoftRegisters, VoltageChangeTimeout);
		हाल AverageGraphicsActivity:
			वापस दुरत्व(SMU72_SoftRegisters, AverageGraphicsActivity);
		हाल AverageMemoryActivity:
			वापस दुरत्व(SMU72_SoftRegisters, AverageMemoryActivity);
		हाल PreVBlankGap:
			वापस दुरत्व(SMU72_SoftRegisters, PreVBlankGap);
		हाल VBlankTimeout:
			वापस दुरत्व(SMU72_SoftRegisters, VBlankTimeout);
		हाल UcodeLoadStatus:
			वापस दुरत्व(SMU72_SoftRegisters, UcodeLoadStatus);
		हाल DRAM_LOG_ADDR_H:
			वापस दुरत्व(SMU72_SoftRegisters, DRAM_LOG_ADDR_H);
		हाल DRAM_LOG_ADDR_L:
			वापस दुरत्व(SMU72_SoftRegisters, DRAM_LOG_ADDR_L);
		हाल DRAM_LOG_PHY_ADDR_H:
			वापस दुरत्व(SMU72_SoftRegisters, DRAM_LOG_PHY_ADDR_H);
		हाल DRAM_LOG_PHY_ADDR_L:
			वापस दुरत्व(SMU72_SoftRegisters, DRAM_LOG_PHY_ADDR_L);
		हाल DRAM_LOG_BUFF_SIZE:
			वापस दुरत्व(SMU72_SoftRegisters, DRAM_LOG_BUFF_SIZE);
		पूर्ण
		अवरोध;
	हाल SMU_Discrete_DpmTable:
		चयन (member) अणु
		हाल UvdBootLevel:
			वापस दुरत्व(SMU72_Discrete_DpmTable, UvdBootLevel);
		हाल VceBootLevel:
			वापस दुरत्व(SMU72_Discrete_DpmTable, VceBootLevel);
		हाल LowSclkInterruptThreshold:
			वापस दुरत्व(SMU72_Discrete_DpmTable, LowSclkInterruptThreshold);
		पूर्ण
		अवरोध;
	पूर्ण
	pr_warn("can't get the offset of type %x member %x\n", type, member);
	वापस 0;
पूर्ण

अटल uपूर्णांक32_t tonga_get_mac_definition(uपूर्णांक32_t value)
अणु
	चयन (value) अणु
	हाल SMU_MAX_LEVELS_GRAPHICS:
		वापस SMU72_MAX_LEVELS_GRAPHICS;
	हाल SMU_MAX_LEVELS_MEMORY:
		वापस SMU72_MAX_LEVELS_MEMORY;
	हाल SMU_MAX_LEVELS_LINK:
		वापस SMU72_MAX_LEVELS_LINK;
	हाल SMU_MAX_ENTRIES_SMIO:
		वापस SMU72_MAX_ENTRIES_SMIO;
	हाल SMU_MAX_LEVELS_VDDC:
		वापस SMU72_MAX_LEVELS_VDDC;
	हाल SMU_MAX_LEVELS_VDDGFX:
		वापस SMU72_MAX_LEVELS_VDDGFX;
	हाल SMU_MAX_LEVELS_VDDCI:
		वापस SMU72_MAX_LEVELS_VDDCI;
	हाल SMU_MAX_LEVELS_MVDD:
		वापस SMU72_MAX_LEVELS_MVDD;
	पूर्ण
	pr_warn("can't get the mac value %x\n", value);

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_update_uvd_smc_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा tonga_smumgr *smu_data =
				(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t mm_boot_level_offset, mm_boot_level_value;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	smu_data->smc_state_table.UvdBootLevel = 0;
	अगर (table_info->mm_dep_table->count > 0)
		smu_data->smc_state_table.UvdBootLevel =
				(uपूर्णांक8_t) (table_info->mm_dep_table->count - 1);
	mm_boot_level_offset = smu_data->smu7_data.dpm_table_start +
				दुरत्व(SMU72_Discrete_DpmTable, UvdBootLevel);
	mm_boot_level_offset /= 4;
	mm_boot_level_offset *= 4;
	mm_boot_level_value = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device,
			CGS_IND_REG__SMC, mm_boot_level_offset);
	mm_boot_level_value &= 0x00FFFFFF;
	mm_boot_level_value |= smu_data->smc_state_table.UvdBootLevel << 24;
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device,
				CGS_IND_REG__SMC,
				mm_boot_level_offset, mm_boot_level_value);

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

अटल पूर्णांक tonga_update_vce_smc_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा tonga_smumgr *smu_data =
				(काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t mm_boot_level_offset, mm_boot_level_value;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);


	smu_data->smc_state_table.VceBootLevel =
		(uपूर्णांक8_t) (table_info->mm_dep_table->count - 1);

	mm_boot_level_offset = smu_data->smu7_data.dpm_table_start +
					दुरत्व(SMU72_Discrete_DpmTable, VceBootLevel);
	mm_boot_level_offset /= 4;
	mm_boot_level_offset *= 4;
	mm_boot_level_value = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device,
			CGS_IND_REG__SMC, mm_boot_level_offset);
	mm_boot_level_value &= 0xFF00FFFF;
	mm_boot_level_value |= smu_data->smc_state_table.VceBootLevel << 16;
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device,
			CGS_IND_REG__SMC, mm_boot_level_offset, mm_boot_level_value);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_StablePState))
		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_VCEDPM_SetEnabledMask,
				(uपूर्णांक32_t)1 << smu_data->smc_state_table.VceBootLevel,
				शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक tonga_update_smc_table(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t type)
अणु
	चयन (type) अणु
	हाल SMU_UVD_TABLE:
		tonga_update_uvd_smc_table(hwmgr);
		अवरोध;
	हाल SMU_VCE_TABLE:
		tonga_update_vce_smc_table(hwmgr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tonga_process_firmware_header(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा tonga_smumgr *smu_data = (काष्ठा tonga_smumgr *)(hwmgr->smu_backend);

	uपूर्णांक32_t पंचांगp;
	पूर्णांक result;
	bool error = false;

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU72_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU72_Firmware_Header, DpmTable),
				&पंचांगp, SMC_RAM_END);

	अगर (!result)
		smu_data->smu7_data.dpm_table_start = पंचांगp;

	error |= (result != 0);

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU72_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU72_Firmware_Header, SoftRegisters),
				&पंचांगp, SMC_RAM_END);

	अगर (!result) अणु
		data->soft_regs_start = पंचांगp;
		smu_data->smu7_data.soft_regs_start = पंचांगp;
	पूर्ण

	error |= (result != 0);


	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU72_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU72_Firmware_Header, mcRegisterTable),
				&पंचांगp, SMC_RAM_END);

	अगर (!result)
		smu_data->smu7_data.mc_reg_table_start = पंचांगp;

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU72_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU72_Firmware_Header, FanTable),
				&पंचांगp, SMC_RAM_END);

	अगर (!result)
		smu_data->smu7_data.fan_table_start = पंचांगp;

	error |= (result != 0);

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU72_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU72_Firmware_Header, mcArbDramTimingTable),
				&पंचांगp, SMC_RAM_END);

	अगर (!result)
		smu_data->smu7_data.arb_table_start = पंचांगp;

	error |= (result != 0);

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU72_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU72_Firmware_Header, Version),
				&पंचांगp, SMC_RAM_END);

	अगर (!result)
		hwmgr->microcode_version_info.SMC = पंचांगp;

	error |= (result != 0);

	वापस error ? 1 : 0;
पूर्ण

/*---------------------------MC----------------------------*/

अटल uपूर्णांक8_t tonga_get_memory_modile_index(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस (uपूर्णांक8_t) (0xFF & (cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmBIOS_SCRATCH_4) >> 16));
पूर्ण

अटल bool tonga_check_s0_mc_reg_index(uपूर्णांक16_t in_reg, uपूर्णांक16_t *out_reg)
अणु
	bool result = true;

	चयन (in_reg) अणु
	हाल  mmMC_SEQ_RAS_TIMING:
		*out_reg = mmMC_SEQ_RAS_TIMING_LP;
		अवरोध;

	हाल  mmMC_SEQ_DLL_STBY:
		*out_reg = mmMC_SEQ_DLL_STBY_LP;
		अवरोध;

	हाल  mmMC_SEQ_G5PDX_CMD0:
		*out_reg = mmMC_SEQ_G5PDX_CMD0_LP;
		अवरोध;

	हाल  mmMC_SEQ_G5PDX_CMD1:
		*out_reg = mmMC_SEQ_G5PDX_CMD1_LP;
		अवरोध;

	हाल  mmMC_SEQ_G5PDX_CTRL:
		*out_reg = mmMC_SEQ_G5PDX_CTRL_LP;
		अवरोध;

	हाल mmMC_SEQ_CAS_TIMING:
		*out_reg = mmMC_SEQ_CAS_TIMING_LP;
		अवरोध;

	हाल mmMC_SEQ_MISC_TIMING:
		*out_reg = mmMC_SEQ_MISC_TIMING_LP;
		अवरोध;

	हाल mmMC_SEQ_MISC_TIMING2:
		*out_reg = mmMC_SEQ_MISC_TIMING2_LP;
		अवरोध;

	हाल mmMC_SEQ_PMG_DVS_CMD:
		*out_reg = mmMC_SEQ_PMG_DVS_CMD_LP;
		अवरोध;

	हाल mmMC_SEQ_PMG_DVS_CTL:
		*out_reg = mmMC_SEQ_PMG_DVS_CTL_LP;
		अवरोध;

	हाल mmMC_SEQ_RD_CTL_D0:
		*out_reg = mmMC_SEQ_RD_CTL_D0_LP;
		अवरोध;

	हाल mmMC_SEQ_RD_CTL_D1:
		*out_reg = mmMC_SEQ_RD_CTL_D1_LP;
		अवरोध;

	हाल mmMC_SEQ_WR_CTL_D0:
		*out_reg = mmMC_SEQ_WR_CTL_D0_LP;
		अवरोध;

	हाल mmMC_SEQ_WR_CTL_D1:
		*out_reg = mmMC_SEQ_WR_CTL_D1_LP;
		अवरोध;

	हाल mmMC_PMG_CMD_EMRS:
		*out_reg = mmMC_SEQ_PMG_CMD_EMRS_LP;
		अवरोध;

	हाल mmMC_PMG_CMD_MRS:
		*out_reg = mmMC_SEQ_PMG_CMD_MRS_LP;
		अवरोध;

	हाल mmMC_PMG_CMD_MRS1:
		*out_reg = mmMC_SEQ_PMG_CMD_MRS1_LP;
		अवरोध;

	हाल mmMC_SEQ_PMG_TIMING:
		*out_reg = mmMC_SEQ_PMG_TIMING_LP;
		अवरोध;

	हाल mmMC_PMG_CMD_MRS2:
		*out_reg = mmMC_SEQ_PMG_CMD_MRS2_LP;
		अवरोध;

	हाल mmMC_SEQ_WR_CTL_2:
		*out_reg = mmMC_SEQ_WR_CTL_2_LP;
		अवरोध;

	शेष:
		result = false;
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक tonga_set_s0_mc_reg_index(काष्ठा tonga_mc_reg_table *table)
अणु
	uपूर्णांक32_t i;
	uपूर्णांक16_t address;

	क्रम (i = 0; i < table->last; i++) अणु
		table->mc_reg_address[i].s0 =
			tonga_check_s0_mc_reg_index(table->mc_reg_address[i].s1,
							&address) ?
							address :
						 table->mc_reg_address[i].s1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tonga_copy_vbios_smc_reg_table(स्थिर pp_atomctrl_mc_reg_table *table,
					काष्ठा tonga_mc_reg_table *ni_table)
अणु
	uपूर्णांक8_t i, j;

	PP_ASSERT_WITH_CODE((table->last <= SMU72_DISCRETE_MC_REGISTER_ARRAY_SIZE),
		"Invalid VramInfo table.", वापस -EINVAL);
	PP_ASSERT_WITH_CODE((table->num_entries <= MAX_AC_TIMING_ENTRIES),
		"Invalid VramInfo table.", वापस -EINVAL);

	क्रम (i = 0; i < table->last; i++)
		ni_table->mc_reg_address[i].s1 = table->mc_reg_address[i].s1;

	ni_table->last = table->last;

	क्रम (i = 0; i < table->num_entries; i++) अणु
		ni_table->mc_reg_table_entry[i].mclk_max =
			table->mc_reg_table_entry[i].mclk_max;
		क्रम (j = 0; j < table->last; j++) अणु
			ni_table->mc_reg_table_entry[i].mc_data[j] =
				table->mc_reg_table_entry[i].mc_data[j];
		पूर्ण
	पूर्ण

	ni_table->num_entries = table->num_entries;

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_set_mc_special_रेजिस्टरs(काष्ठा pp_hwmgr *hwmgr,
					काष्ठा tonga_mc_reg_table *table)
अणु
	uपूर्णांक8_t i, j, k;
	uपूर्णांक32_t temp_reg;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	क्रम (i = 0, j = table->last; i < table->last; i++) अणु
		PP_ASSERT_WITH_CODE((j < SMU72_DISCRETE_MC_REGISTER_ARRAY_SIZE),
			"Invalid VramInfo table.", वापस -EINVAL);

		चयन (table->mc_reg_address[i].s1) अणु

		हाल mmMC_SEQ_MISC1:
			temp_reg = cgs_पढ़ो_रेजिस्टर(hwmgr->device,
							mmMC_PMG_CMD_EMRS);
			table->mc_reg_address[j].s1 = mmMC_PMG_CMD_EMRS;
			table->mc_reg_address[j].s0 = mmMC_SEQ_PMG_CMD_EMRS_LP;
			क्रम (k = 0; k < table->num_entries; k++) अणु
				table->mc_reg_table_entry[k].mc_data[j] =
					((temp_reg & 0xffff0000)) |
					((table->mc_reg_table_entry[k].mc_data[i] & 0xffff0000) >> 16);
			पूर्ण
			j++;

			PP_ASSERT_WITH_CODE((j < SMU72_DISCRETE_MC_REGISTER_ARRAY_SIZE),
				"Invalid VramInfo table.", वापस -EINVAL);
			temp_reg = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_PMG_CMD_MRS);
			table->mc_reg_address[j].s1 = mmMC_PMG_CMD_MRS;
			table->mc_reg_address[j].s0 = mmMC_SEQ_PMG_CMD_MRS_LP;
			क्रम (k = 0; k < table->num_entries; k++) अणु
				table->mc_reg_table_entry[k].mc_data[j] =
					(temp_reg & 0xffff0000) |
					(table->mc_reg_table_entry[k].mc_data[i] & 0x0000ffff);

				अगर (!data->is_memory_gddr5)
					table->mc_reg_table_entry[k].mc_data[j] |= 0x100;
			पूर्ण
			j++;

			अगर (!data->is_memory_gddr5) अणु
				PP_ASSERT_WITH_CODE((j < SMU72_DISCRETE_MC_REGISTER_ARRAY_SIZE),
					"Invalid VramInfo table.", वापस -EINVAL);
				table->mc_reg_address[j].s1 = mmMC_PMG_AUTO_CMD;
				table->mc_reg_address[j].s0 = mmMC_PMG_AUTO_CMD;
				क्रम (k = 0; k < table->num_entries; k++)
					table->mc_reg_table_entry[k].mc_data[j] =
						(table->mc_reg_table_entry[k].mc_data[i] & 0xffff0000) >> 16;
				j++;
			पूर्ण

			अवरोध;

		हाल mmMC_SEQ_RESERVE_M:
			temp_reg = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_PMG_CMD_MRS1);
			table->mc_reg_address[j].s1 = mmMC_PMG_CMD_MRS1;
			table->mc_reg_address[j].s0 = mmMC_SEQ_PMG_CMD_MRS1_LP;
			क्रम (k = 0; k < table->num_entries; k++) अणु
				table->mc_reg_table_entry[k].mc_data[j] =
					(temp_reg & 0xffff0000) |
					(table->mc_reg_table_entry[k].mc_data[i] & 0x0000ffff);
			पूर्ण
			j++;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

	पूर्ण

	table->last = j;

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_set_valid_flag(काष्ठा tonga_mc_reg_table *table)
अणु
	uपूर्णांक8_t i, j;

	क्रम (i = 0; i < table->last; i++) अणु
		क्रम (j = 1; j < table->num_entries; j++) अणु
			अगर (table->mc_reg_table_entry[j-1].mc_data[i] !=
				table->mc_reg_table_entry[j].mc_data[i]) अणु
				table->validflag |= (1<<i);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tonga_initialize_mc_reg_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	काष्ठा tonga_smumgr *smu_data = (काष्ठा tonga_smumgr *)(hwmgr->smu_backend);
	pp_atomctrl_mc_reg_table *table;
	काष्ठा tonga_mc_reg_table *ni_table = &smu_data->mc_reg_table;
	uपूर्णांक8_t module_index = tonga_get_memory_modile_index(hwmgr);

	table = kzalloc(माप(pp_atomctrl_mc_reg_table), GFP_KERNEL);

	अगर (table == शून्य)
		वापस -ENOMEM;

	/* Program additional LP रेजिस्टरs that are no दीर्घer programmed by VBIOS */
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RAS_TIMING_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RAS_TIMING));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_CAS_TIMING_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_CAS_TIMING));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_DLL_STBY_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_DLL_STBY));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_G5PDX_CMD0_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_G5PDX_CMD0));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_G5PDX_CMD1_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_G5PDX_CMD1));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_G5PDX_CTRL_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_G5PDX_CTRL));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_DVS_CMD_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_DVS_CMD));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_DVS_CTL_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_DVS_CTL));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC_TIMING_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC_TIMING));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC_TIMING2_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC_TIMING2));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_CMD_EMRS_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_PMG_CMD_EMRS));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_CMD_MRS_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_PMG_CMD_MRS));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_CMD_MRS1_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_PMG_CMD_MRS1));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_WR_CTL_D0_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_WR_CTL_D0));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_WR_CTL_D1_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_WR_CTL_D1));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RD_CTL_D0_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RD_CTL_D0));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RD_CTL_D1_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RD_CTL_D1));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_TIMING_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_TIMING));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_CMD_MRS2_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_PMG_CMD_MRS2));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_WR_CTL_2_LP,
			cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_WR_CTL_2));

	result = atomctrl_initialize_mc_reg_table(hwmgr, module_index, table);

	अगर (!result)
		result = tonga_copy_vbios_smc_reg_table(table, ni_table);

	अगर (!result) अणु
		tonga_set_s0_mc_reg_index(ni_table);
		result = tonga_set_mc_special_रेजिस्टरs(hwmgr, ni_table);
	पूर्ण

	अगर (!result)
		tonga_set_valid_flag(ni_table);

	kमुक्त(table);

	वापस result;
पूर्ण

अटल bool tonga_is_dpm_running(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस (1 == PHM_READ_INसूचीECT_FIELD(hwmgr->device,
			CGS_IND_REG__SMC, FEATURE_STATUS, VOLTAGE_CONTROLLER_ON))
			? true : false;
पूर्ण

अटल पूर्णांक tonga_update_dpm_settings(काष्ठा pp_hwmgr *hwmgr,
				व्योम *profile_setting)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा tonga_smumgr *smu_data = (काष्ठा tonga_smumgr *)
			(hwmgr->smu_backend);
	काष्ठा profile_mode_setting *setting;
	काष्ठा SMU72_Discrete_GraphicsLevel *levels =
			smu_data->smc_state_table.GraphicsLevel;
	uपूर्णांक32_t array = smu_data->smu7_data.dpm_table_start +
			दुरत्व(SMU72_Discrete_DpmTable, GraphicsLevel);

	uपूर्णांक32_t mclk_array = smu_data->smu7_data.dpm_table_start +
			दुरत्व(SMU72_Discrete_DpmTable, MemoryLevel);
	काष्ठा SMU72_Discrete_MemoryLevel *mclk_levels =
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

				clk_activity_offset = array + (माप(SMU72_Discrete_GraphicsLevel) * i)
						+ दुरत्व(SMU72_Discrete_GraphicsLevel, ActivityLevel);
				offset = clk_activity_offset & ~0x3;
				पंचांगp = PP_HOST_TO_SMC_UL(cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, offset));
				पंचांगp = phm_set_field_to_u32(clk_activity_offset, पंचांगp, levels[i].ActivityLevel, माप(uपूर्णांक16_t));
				cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, offset, PP_HOST_TO_SMC_UL(पंचांगp));

			पूर्ण
			अगर (levels[i].UpHyst != setting->sclk_up_hyst ||
				levels[i].DownHyst != setting->sclk_करोwn_hyst) अणु
				levels[i].UpHyst = setting->sclk_up_hyst;
				levels[i].DownHyst = setting->sclk_करोwn_hyst;
				up_hyst_offset = array + (माप(SMU72_Discrete_GraphicsLevel) * i)
						+ दुरत्व(SMU72_Discrete_GraphicsLevel, UpHyst);
				करोwn_hyst_offset = array + (माप(SMU72_Discrete_GraphicsLevel) * i)
						+ दुरत्व(SMU72_Discrete_GraphicsLevel, DownHyst);
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

				clk_activity_offset = mclk_array + (माप(SMU72_Discrete_MemoryLevel) * i)
						+ दुरत्व(SMU72_Discrete_MemoryLevel, ActivityLevel);
				offset = clk_activity_offset & ~0x3;
				पंचांगp = PP_HOST_TO_SMC_UL(cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, offset));
				पंचांगp = phm_set_field_to_u32(clk_activity_offset, पंचांगp, mclk_levels[i].ActivityLevel, माप(uपूर्णांक16_t));
				cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, offset, PP_HOST_TO_SMC_UL(पंचांगp));

			पूर्ण
			अगर (mclk_levels[i].UpHyst != setting->mclk_up_hyst ||
				mclk_levels[i].DownHyst != setting->mclk_करोwn_hyst) अणु
				mclk_levels[i].UpHyst = setting->mclk_up_hyst;
				mclk_levels[i].DownHyst = setting->mclk_करोwn_hyst;
				up_hyst_offset = mclk_array + (माप(SMU72_Discrete_MemoryLevel) * i)
						+ दुरत्व(SMU72_Discrete_MemoryLevel, UpHyst);
				करोwn_hyst_offset = mclk_array + (माप(SMU72_Discrete_MemoryLevel) * i)
						+ दुरत्व(SMU72_Discrete_MemoryLevel, DownHyst);
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

स्थिर काष्ठा pp_smumgr_func tonga_smu_funcs = अणु
	.name = "tonga_smu",
	.smu_init = &tonga_smu_init,
	.smu_fini = &smu7_smu_fini,
	.start_smu = &tonga_start_smu,
	.check_fw_load_finish = &smu7_check_fw_load_finish,
	.request_smu_load_fw = &smu7_request_smu_load_fw,
	.request_smu_load_specअगरic_fw = शून्य,
	.send_msg_to_smc = &smu7_send_msg_to_smc,
	.send_msg_to_smc_with_parameter = &smu7_send_msg_to_smc_with_parameter,
	.get_argument = smu7_get_argument,
	.करोwnload_pptable_settings = शून्य,
	.upload_pptable_settings = शून्य,
	.update_smc_table = tonga_update_smc_table,
	.get_दुरत्व = tonga_get_दुरत्व,
	.process_firmware_header = tonga_process_firmware_header,
	.init_smc_table = tonga_init_smc_table,
	.update_sclk_threshold = tonga_update_sclk_threshold,
	.thermal_setup_fan_table = tonga_thermal_setup_fan_table,
	.populate_all_graphic_levels = tonga_populate_all_graphic_levels,
	.populate_all_memory_levels = tonga_populate_all_memory_levels,
	.get_mac_definition = tonga_get_mac_definition,
	.initialize_mc_reg_table = tonga_initialize_mc_reg_table,
	.is_dpm_running = tonga_is_dpm_running,
	.update_dpm_settings = tonga_update_dpm_settings,
पूर्ण;
