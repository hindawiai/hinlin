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
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <drm/amdgpu_drm.h>
#समावेश "ppatomctrl.h"
#समावेश "atombios.h"
#समावेश "pptable_v1_0.h"
#समावेश "pppcielanes.h"
#समावेश "amd_pcie_helpers.h"
#समावेश "hardwaremanager.h"
#समावेश "process_pptables_v1_0.h"
#समावेश "cgs_common.h"

#समावेश "smu7_common.h"

#समावेश "hwmgr.h"
#समावेश "smu7_hwmgr.h"
#समावेश "smu_ucode_xfer_vi.h"
#समावेश "smu7_powertune.h"
#समावेश "smu7_dyn_defaults.h"
#समावेश "smu7_thermal.h"
#समावेश "smu7_clockpowergating.h"
#समावेश "processpptables.h"
#समावेश "pp_thermal.h"
#समावेश "smu7_baco.h"
#समावेश "smu7_smumgr.h"
#समावेश "polaris10_smumgr.h"

#समावेश "ivsrcid/ivsrcid_vislands30.h"

#घोषणा MC_CG_ARB_FREQ_F0           0x0a
#घोषणा MC_CG_ARB_FREQ_F1           0x0b
#घोषणा MC_CG_ARB_FREQ_F2           0x0c
#घोषणा MC_CG_ARB_FREQ_F3           0x0d

#घोषणा MC_CG_SEQ_DRAMCONF_S0       0x05
#घोषणा MC_CG_SEQ_DRAMCONF_S1       0x06
#घोषणा MC_CG_SEQ_YCLK_SUSPEND      0x04
#घोषणा MC_CG_SEQ_YCLK_RESUME       0x0a

#घोषणा SMC_CG_IND_START            0xc0030000
#घोषणा SMC_CG_IND_END              0xc0040000

#घोषणा MEM_FREQ_LOW_LATENCY        25000
#घोषणा MEM_FREQ_HIGH_LATENCY       80000

#घोषणा MEM_LATENCY_HIGH            45
#घोषणा MEM_LATENCY_LOW             35
#घोषणा MEM_LATENCY_ERR             0xFFFF

#घोषणा MC_SEQ_MISC0_GDDR5_SHIFT 28
#घोषणा MC_SEQ_MISC0_GDDR5_MASK  0xf0000000
#घोषणा MC_SEQ_MISC0_GDDR5_VALUE 5

#घोषणा PCIE_BUS_CLK                10000
#घोषणा TCLK                        (PCIE_BUS_CLK / 10)

अटल काष्ठा profile_mode_setting smu7_profiling[7] =
					अणुअणु0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
					 अणु1, 0, 100, 30, 1, 0, 100, 10पूर्ण,
					 अणु1, 10, 0, 30, 0, 0, 0, 0पूर्ण,
					 अणु0, 0, 0, 0, 1, 10, 16, 31पूर्ण,
					 अणु1, 0, 11, 50, 1, 0, 100, 10पूर्ण,
					 अणु1, 0, 5, 30, 0, 0, 0, 0पूर्ण,
					 अणु0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
					पूर्ण;

#घोषणा PPSMC_MSG_SetVBITimeout_VEGAM    ((uपूर्णांक16_t) 0x310)

#घोषणा ixPWR_SVI2_PLANE1_LOAD                     0xC0200280
#घोषणा PWR_SVI2_PLANE1_LOAD__PSI1_MASK                    0x00000020L
#घोषणा PWR_SVI2_PLANE1_LOAD__PSI0_EN_MASK                 0x00000040L
#घोषणा PWR_SVI2_PLANE1_LOAD__PSI1__SHIFT                  0x00000005
#घोषणा PWR_SVI2_PLANE1_LOAD__PSI0_EN__SHIFT               0x00000006

#घोषणा STRAP_EVV_REVISION_MSB		2211
#घोषणा STRAP_EVV_REVISION_LSB		2208

/** Values क्रम the CG_THERMAL_CTRL::DPM_EVENT_SRC field. */
क्रमागत DPM_EVENT_SRC अणु
	DPM_EVENT_SRC_ANALOG = 0,
	DPM_EVENT_SRC_EXTERNAL = 1,
	DPM_EVENT_SRC_DIGITAL = 2,
	DPM_EVENT_SRC_ANALOG_OR_EXTERNAL = 3,
	DPM_EVENT_SRC_DIGITAL_OR_EXTERNAL = 4
पूर्ण;

#घोषणा ixDIDT_SQ_EDC_CTRL                         0x0013
#घोषणा ixDIDT_SQ_EDC_THRESHOLD                    0x0014
#घोषणा ixDIDT_SQ_EDC_STALL_PATTERN_1_2            0x0015
#घोषणा ixDIDT_SQ_EDC_STALL_PATTERN_3_4            0x0016
#घोषणा ixDIDT_SQ_EDC_STALL_PATTERN_5_6            0x0017
#घोषणा ixDIDT_SQ_EDC_STALL_PATTERN_7              0x0018

#घोषणा ixDIDT_TD_EDC_CTRL                         0x0053
#घोषणा ixDIDT_TD_EDC_THRESHOLD                    0x0054
#घोषणा ixDIDT_TD_EDC_STALL_PATTERN_1_2            0x0055
#घोषणा ixDIDT_TD_EDC_STALL_PATTERN_3_4            0x0056
#घोषणा ixDIDT_TD_EDC_STALL_PATTERN_5_6            0x0057
#घोषणा ixDIDT_TD_EDC_STALL_PATTERN_7              0x0058

#घोषणा ixDIDT_TCP_EDC_CTRL                        0x0073
#घोषणा ixDIDT_TCP_EDC_THRESHOLD                   0x0074
#घोषणा ixDIDT_TCP_EDC_STALL_PATTERN_1_2           0x0075
#घोषणा ixDIDT_TCP_EDC_STALL_PATTERN_3_4           0x0076
#घोषणा ixDIDT_TCP_EDC_STALL_PATTERN_5_6           0x0077
#घोषणा ixDIDT_TCP_EDC_STALL_PATTERN_7             0x0078

#घोषणा ixDIDT_DB_EDC_CTRL                         0x0033
#घोषणा ixDIDT_DB_EDC_THRESHOLD                    0x0034
#घोषणा ixDIDT_DB_EDC_STALL_PATTERN_1_2            0x0035
#घोषणा ixDIDT_DB_EDC_STALL_PATTERN_3_4            0x0036
#घोषणा ixDIDT_DB_EDC_STALL_PATTERN_5_6            0x0037
#घोषणा ixDIDT_DB_EDC_STALL_PATTERN_7              0x0038

uपूर्णांक32_t DIDTEDCConfig_P12[] = अणु
    ixDIDT_SQ_EDC_STALL_PATTERN_1_2,
    ixDIDT_SQ_EDC_STALL_PATTERN_3_4,
    ixDIDT_SQ_EDC_STALL_PATTERN_5_6,
    ixDIDT_SQ_EDC_STALL_PATTERN_7,
    ixDIDT_SQ_EDC_THRESHOLD,
    ixDIDT_SQ_EDC_CTRL,
    ixDIDT_TD_EDC_STALL_PATTERN_1_2,
    ixDIDT_TD_EDC_STALL_PATTERN_3_4,
    ixDIDT_TD_EDC_STALL_PATTERN_5_6,
    ixDIDT_TD_EDC_STALL_PATTERN_7,
    ixDIDT_TD_EDC_THRESHOLD,
    ixDIDT_TD_EDC_CTRL,
    ixDIDT_TCP_EDC_STALL_PATTERN_1_2,
    ixDIDT_TCP_EDC_STALL_PATTERN_3_4,
    ixDIDT_TCP_EDC_STALL_PATTERN_5_6,
    ixDIDT_TCP_EDC_STALL_PATTERN_7,
    ixDIDT_TCP_EDC_THRESHOLD,
    ixDIDT_TCP_EDC_CTRL,
    ixDIDT_DB_EDC_STALL_PATTERN_1_2,
    ixDIDT_DB_EDC_STALL_PATTERN_3_4,
    ixDIDT_DB_EDC_STALL_PATTERN_5_6,
    ixDIDT_DB_EDC_STALL_PATTERN_7,
    ixDIDT_DB_EDC_THRESHOLD,
    ixDIDT_DB_EDC_CTRL,
    0xFFFFFFFF // End of list
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ PhwVIslands_Magic = (अचिन्हित दीर्घ)(PHM_VIslands_Magic);
अटल पूर्णांक smu7_क्रमce_घड़ी_level(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत pp_घड़ी_प्रकारype type, uपूर्णांक32_t mask);
अटल पूर्णांक smu7_notअगरy_has_display(काष्ठा pp_hwmgr *hwmgr);

अटल काष्ठा smu7_घातer_state *cast_phw_smu7_घातer_state(
				  काष्ठा pp_hw_घातer_state *hw_ps)
अणु
	PP_ASSERT_WITH_CODE((PhwVIslands_Magic == hw_ps->magic),
				"Invalid Powerstate Type!",
				 वापस शून्य);

	वापस (काष्ठा smu7_घातer_state *)hw_ps;
पूर्ण

अटल स्थिर काष्ठा smu7_घातer_state *cast_स्थिर_phw_smu7_घातer_state(
				 स्थिर काष्ठा pp_hw_घातer_state *hw_ps)
अणु
	PP_ASSERT_WITH_CODE((PhwVIslands_Magic == hw_ps->magic),
				"Invalid Powerstate Type!",
				 वापस शून्य);

	वापस (स्थिर काष्ठा smu7_घातer_state *)hw_ps;
पूर्ण

/**
 * smu7_get_mc_microcode_version - Find the MC microcode version and store it in the HwMgr काष्ठा
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Return:   always 0
 */
अटल पूर्णांक smu7_get_mc_microcode_version(काष्ठा pp_hwmgr *hwmgr)
अणु
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_IO_DEBUG_INDEX, 0x9F);

	hwmgr->microcode_version_info.MC = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_IO_DEBUG_DATA);

	वापस 0;
पूर्ण

अटल uपूर्णांक16_t smu7_get_current_pcie_speed(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t speedCntl = 0;

	/* mmPCIE_PORT_INDEX नाम as mmPCIE_INDEX */
	speedCntl = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__PCIE,
			ixPCIE_LC_SPEED_CNTL);
	वापस((uपूर्णांक16_t)PHM_GET_FIELD(speedCntl,
			PCIE_LC_SPEED_CNTL, LC_CURRENT_DATA_RATE));
पूर्ण

अटल पूर्णांक smu7_get_current_pcie_lane_number(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t link_width;

	/* mmPCIE_PORT_INDEX नाम as mmPCIE_INDEX */
	link_width = PHM_READ_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__PCIE,
			PCIE_LC_LINK_WIDTH_CNTL, LC_LINK_WIDTH_RD);

	PP_ASSERT_WITH_CODE((7 >= link_width),
			"Invalid PCIe lane width!", वापस 0);

	वापस decode_pcie_lane_width(link_width);
पूर्ण

/**
 * smu7_enable_smc_voltage_controller - Enable voltage control
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Return:   always PP_Result_OK
 */
अटल पूर्णांक smu7_enable_smc_voltage_controller(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (hwmgr->chip_id >= CHIP_POLARIS10 &&
	    hwmgr->chip_id <= CHIP_VEGAM) अणु
		PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device,
				CGS_IND_REG__SMC, PWR_SVI2_PLANE1_LOAD, PSI1, 0);
		PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device,
				CGS_IND_REG__SMC, PWR_SVI2_PLANE1_LOAD, PSI0_EN, 0);
	पूर्ण

	अगर (hwmgr->feature_mask & PP_SMC_VOLTAGE_CONTROL_MASK)
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_Voltage_Cntl_Enable, शून्य);

	वापस 0;
पूर्ण

/**
 * smu7_voltage_control - Checks अगर we want to support voltage control
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 */
अटल bool smu7_voltage_control(स्थिर काष्ठा pp_hwmgr *hwmgr)
अणु
	स्थिर काष्ठा smu7_hwmgr *data =
			(स्थिर काष्ठा smu7_hwmgr *)(hwmgr->backend);

	वापस (SMU7_VOLTAGE_CONTROL_NONE != data->voltage_control);
पूर्ण

/**
 * smu7_enable_voltage_control - Enable voltage control
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Return:   always 0
 */
अटल पूर्णांक smu7_enable_voltage_control(काष्ठा pp_hwmgr *hwmgr)
अणु
	/* enable voltage control */
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			GENERAL_PWRMGT, VOLT_PWRMGT_EN, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक phm_get_svi2_voltage_table_v0(pp_atomctrl_voltage_table *voltage_table,
		काष्ठा phm_घड़ी_voltage_dependency_table *voltage_dependency_table
		)
अणु
	uपूर्णांक32_t i;

	PP_ASSERT_WITH_CODE((शून्य != voltage_table),
			"Voltage Dependency Table empty.", वापस -EINVAL;);

	voltage_table->mask_low = 0;
	voltage_table->phase_delay = 0;
	voltage_table->count = voltage_dependency_table->count;

	क्रम (i = 0; i < voltage_dependency_table->count; i++) अणु
		voltage_table->entries[i].value =
			voltage_dependency_table->entries[i].v;
		voltage_table->entries[i].smio_low = 0;
	पूर्ण

	वापस 0;
पूर्ण


/**
 * smu7_स्थिरruct_voltage_tables - Create Voltage Tables.
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Return:   always 0
 */
अटल पूर्णांक smu7_स्थिरruct_voltage_tables(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)hwmgr->pptable;
	पूर्णांक result = 0;
	uपूर्णांक32_t पंचांगp;

	अगर (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->mvdd_control) अणु
		result = atomctrl_get_voltage_table_v3(hwmgr,
				VOLTAGE_TYPE_MVDDC, VOLTAGE_OBJ_GPIO_LUT,
				&(data->mvdd_voltage_table));
		PP_ASSERT_WITH_CODE((0 == result),
				"Failed to retrieve MVDD table.",
				वापस result);
	पूर्ण अन्यथा अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->mvdd_control) अणु
		अगर (hwmgr->pp_table_version == PP_TABLE_V1)
			result = phm_get_svi2_mvdd_voltage_table(&(data->mvdd_voltage_table),
					table_info->vdd_dep_on_mclk);
		अन्यथा अगर (hwmgr->pp_table_version == PP_TABLE_V0)
			result = phm_get_svi2_voltage_table_v0(&(data->mvdd_voltage_table),
					hwmgr->dyn_state.mvdd_dependency_on_mclk);

		PP_ASSERT_WITH_CODE((0 == result),
				"Failed to retrieve SVI2 MVDD table from dependency table.",
				वापस result;);
	पूर्ण

	अगर (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->vddci_control) अणु
		result = atomctrl_get_voltage_table_v3(hwmgr,
				VOLTAGE_TYPE_VDDCI, VOLTAGE_OBJ_GPIO_LUT,
				&(data->vddci_voltage_table));
		PP_ASSERT_WITH_CODE((0 == result),
				"Failed to retrieve VDDCI table.",
				वापस result);
	पूर्ण अन्यथा अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->vddci_control) अणु
		अगर (hwmgr->pp_table_version == PP_TABLE_V1)
			result = phm_get_svi2_vddci_voltage_table(&(data->vddci_voltage_table),
					table_info->vdd_dep_on_mclk);
		अन्यथा अगर (hwmgr->pp_table_version == PP_TABLE_V0)
			result = phm_get_svi2_voltage_table_v0(&(data->vddci_voltage_table),
					hwmgr->dyn_state.vddci_dependency_on_mclk);
		PP_ASSERT_WITH_CODE((0 == result),
				"Failed to retrieve SVI2 VDDCI table from dependency table.",
				वापस result);
	पूर्ण

	अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->vdd_gfx_control) अणु
		/* VDDGFX has only SVI2 voltage control */
		result = phm_get_svi2_vdd_voltage_table(&(data->vddgfx_voltage_table),
					table_info->vddgfx_lookup_table);
		PP_ASSERT_WITH_CODE((0 == result),
			"Failed to retrieve SVI2 VDDGFX table from lookup table.", वापस result;);
	पूर्ण


	अगर (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->voltage_control) अणु
		result = atomctrl_get_voltage_table_v3(hwmgr,
					VOLTAGE_TYPE_VDDC, VOLTAGE_OBJ_GPIO_LUT,
					&data->vddc_voltage_table);
		PP_ASSERT_WITH_CODE((0 == result),
			"Failed to retrieve VDDC table.", वापस result;);
	पूर्ण अन्यथा अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->voltage_control) अणु

		अगर (hwmgr->pp_table_version == PP_TABLE_V0)
			result = phm_get_svi2_voltage_table_v0(&data->vddc_voltage_table,
					hwmgr->dyn_state.vddc_dependency_on_mclk);
		अन्यथा अगर (hwmgr->pp_table_version == PP_TABLE_V1)
			result = phm_get_svi2_vdd_voltage_table(&(data->vddc_voltage_table),
				table_info->vddc_lookup_table);

		PP_ASSERT_WITH_CODE((0 == result),
			"Failed to retrieve SVI2 VDDC table from dependency table.", वापस result;);
	पूर्ण

	पंचांगp = smum_get_mac_definition(hwmgr, SMU_MAX_LEVELS_VDDC);
	PP_ASSERT_WITH_CODE(
			(data->vddc_voltage_table.count <= पंचांगp),
		"Too many voltage values for VDDC. Trimming to fit state table.",
			phm_trim_voltage_table_to_fit_state_table(पंचांगp,
						&(data->vddc_voltage_table)));

	पंचांगp = smum_get_mac_definition(hwmgr, SMU_MAX_LEVELS_VDDGFX);
	PP_ASSERT_WITH_CODE(
			(data->vddgfx_voltage_table.count <= पंचांगp),
		"Too many voltage values for VDDC. Trimming to fit state table.",
			phm_trim_voltage_table_to_fit_state_table(पंचांगp,
						&(data->vddgfx_voltage_table)));

	पंचांगp = smum_get_mac_definition(hwmgr, SMU_MAX_LEVELS_VDDCI);
	PP_ASSERT_WITH_CODE(
			(data->vddci_voltage_table.count <= पंचांगp),
		"Too many voltage values for VDDCI. Trimming to fit state table.",
			phm_trim_voltage_table_to_fit_state_table(पंचांगp,
					&(data->vddci_voltage_table)));

	पंचांगp = smum_get_mac_definition(hwmgr, SMU_MAX_LEVELS_MVDD);
	PP_ASSERT_WITH_CODE(
			(data->mvdd_voltage_table.count <= पंचांगp),
		"Too many voltage values for MVDD. Trimming to fit state table.",
			phm_trim_voltage_table_to_fit_state_table(पंचांगp,
						&(data->mvdd_voltage_table)));

	वापस 0;
पूर्ण

/**
 * smu7_program_अटल_screen_threshold_parameters - Programs अटल screed detection parameters
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Return:   always 0
 */
अटल पूर्णांक smu7_program_अटल_screen_threshold_parameters(
							काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	/* Set अटल screen threshold unit */
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_STATIC_SCREEN_PARAMETER, STATIC_SCREEN_THRESHOLD_UNIT,
			data->अटल_screen_threshold_unit);
	/* Set अटल screen threshold */
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_STATIC_SCREEN_PARAMETER, STATIC_SCREEN_THRESHOLD,
			data->अटल_screen_threshold);

	वापस 0;
पूर्ण

/**
 * smu7_enable_display_gap - Setup display gap क्रम glitch मुक्त memory घड़ी चयनing.
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Return:   always  0
 */
अटल पूर्णांक smu7_enable_display_gap(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t display_gap =
			cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
					ixCG_DISPLAY_GAP_CNTL);

	display_gap = PHM_SET_FIELD(display_gap, CG_DISPLAY_GAP_CNTL,
			DISP_GAP, DISPLAY_GAP_IGNORE);

	display_gap = PHM_SET_FIELD(display_gap, CG_DISPLAY_GAP_CNTL,
			DISP_GAP_MCHG, DISPLAY_GAP_VBLANK);

	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			ixCG_DISPLAY_GAP_CNTL, display_gap);

	वापस 0;
पूर्ण

/**
 * smu7_program_voting_clients - Programs activity state transition voting clients
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Return:   always  0
 */
अटल पूर्णांक smu7_program_voting_clients(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	पूर्णांक i;

	/* Clear reset क्रम voting clients beक्रमe enabling DPM */
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			SCLK_PWRMGT_CNTL, RESET_SCLK_CNT, 0);
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			SCLK_PWRMGT_CNTL, RESET_BUSY_CNT, 0);

	क्रम (i = 0; i < 8; i++)
		cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
					ixCG_FREQ_TRAN_VOTING_0 + i * 4,
					data->voting_rights_clients[i]);
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_clear_voting_clients(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक i;

	/* Reset voting clients beक्रमe disabling DPM */
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			SCLK_PWRMGT_CNTL, RESET_SCLK_CNT, 1);
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			SCLK_PWRMGT_CNTL, RESET_BUSY_CNT, 1);

	क्रम (i = 0; i < 8; i++)
		cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
				ixCG_FREQ_TRAN_VOTING_0 + i * 4, 0);

	वापस 0;
पूर्ण

/* Copy one arb setting to another and then चयन the active set.
 * arb_src and arb_dest is one of the MC_CG_ARB_FREQ_Fx स्थिरants.
 */
अटल पूर्णांक smu7_copy_and_चयन_arb_sets(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t arb_src, uपूर्णांक32_t arb_dest)
अणु
	uपूर्णांक32_t mc_arb_dram_timing;
	uपूर्णांक32_t mc_arb_dram_timing2;
	uपूर्णांक32_t burst_समय;
	uपूर्णांक32_t mc_cg_config;

	चयन (arb_src) अणु
	हाल MC_CG_ARB_FREQ_F0:
		mc_arb_dram_timing  = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_ARB_DRAM_TIMING);
		mc_arb_dram_timing2 = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_ARB_DRAM_TIMING2);
		burst_समय = PHM_READ_FIELD(hwmgr->device, MC_ARB_BURST_TIME, STATE0);
		अवरोध;
	हाल MC_CG_ARB_FREQ_F1:
		mc_arb_dram_timing  = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_ARB_DRAM_TIMING_1);
		mc_arb_dram_timing2 = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_ARB_DRAM_TIMING2_1);
		burst_समय = PHM_READ_FIELD(hwmgr->device, MC_ARB_BURST_TIME, STATE1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (arb_dest) अणु
	हाल MC_CG_ARB_FREQ_F0:
		cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_ARB_DRAM_TIMING, mc_arb_dram_timing);
		cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_ARB_DRAM_TIMING2, mc_arb_dram_timing2);
		PHM_WRITE_FIELD(hwmgr->device, MC_ARB_BURST_TIME, STATE0, burst_समय);
		अवरोध;
	हाल MC_CG_ARB_FREQ_F1:
		cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_ARB_DRAM_TIMING_1, mc_arb_dram_timing);
		cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_ARB_DRAM_TIMING2_1, mc_arb_dram_timing2);
		PHM_WRITE_FIELD(hwmgr->device, MC_ARB_BURST_TIME, STATE1, burst_समय);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mc_cg_config = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_CG_CONFIG);
	mc_cg_config |= 0x0000000F;
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_CG_CONFIG, mc_cg_config);
	PHM_WRITE_FIELD(hwmgr->device, MC_ARB_CG, CG_ARB_REQ, arb_dest);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_reset_to_शेष(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस smum_send_msg_to_smc(hwmgr, PPSMC_MSG_ResetToDefaults, शून्य);
पूर्ण

/**
 * smu7_initial_चयन_from_arbf0_to_f1 - Initial चयन from ARB F0->F1
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Return:   always 0
 * This function is to be called from the SetPowerState table.
 */
अटल पूर्णांक smu7_initial_चयन_from_arbf0_to_f1(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस smu7_copy_and_चयन_arb_sets(hwmgr,
			MC_CG_ARB_FREQ_F0, MC_CG_ARB_FREQ_F1);
पूर्ण

अटल पूर्णांक smu7_क्रमce_चयन_to_arbf0(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t पंचांगp;

	पंचांगp = (cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device,
			CGS_IND_REG__SMC, ixSMC_SCRATCH9) &
			0x0000ff00) >> 8;

	अगर (पंचांगp == MC_CG_ARB_FREQ_F0)
		वापस 0;

	वापस smu7_copy_and_चयन_arb_sets(hwmgr,
			पंचांगp, MC_CG_ARB_FREQ_F0);
पूर्ण

अटल uपूर्णांक16_t smu7_override_pcie_speed(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)(hwmgr->adev);
	uपूर्णांक16_t pcie_gen = 0;

	अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN4 &&
	    adev->pm.pcie_gen_mask & CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN4)
		pcie_gen = 3;
	अन्यथा अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3 &&
		adev->pm.pcie_gen_mask & CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN3)
		pcie_gen = 2;
	अन्यथा अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2 &&
		adev->pm.pcie_gen_mask & CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN2)
		pcie_gen = 1;
	अन्यथा अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN1 &&
		adev->pm.pcie_gen_mask & CAIL_ASIC_PCIE_LINK_SPEED_SUPPORT_GEN1)
		pcie_gen = 0;

	वापस pcie_gen;
पूर्ण

अटल uपूर्णांक16_t smu7_override_pcie_width(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)(hwmgr->adev);
	uपूर्णांक16_t pcie_width = 0;

	अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X16)
		pcie_width = 16;
	अन्यथा अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X12)
		pcie_width = 12;
	अन्यथा अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X8)
		pcie_width = 8;
	अन्यथा अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X4)
		pcie_width = 4;
	अन्यथा अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X2)
		pcie_width = 2;
	अन्यथा अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X1)
		pcie_width = 1;

	वापस pcie_width;
पूर्ण

अटल पूर्णांक smu7_setup_शेष_pcie_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_pcie_table *pcie_table = शून्य;

	uपूर्णांक32_t i, max_entry;
	uपूर्णांक32_t पंचांगp;

	PP_ASSERT_WITH_CODE((data->use_pcie_perक्रमmance_levels ||
			data->use_pcie_घातer_saving_levels), "No pcie performance levels!",
			वापस -EINVAL);

	अगर (table_info != शून्य)
		pcie_table = table_info->pcie_table;

	अगर (data->use_pcie_perक्रमmance_levels &&
			!data->use_pcie_घातer_saving_levels) अणु
		data->pcie_gen_घातer_saving = data->pcie_gen_perक्रमmance;
		data->pcie_lane_घातer_saving = data->pcie_lane_perक्रमmance;
	पूर्ण अन्यथा अगर (!data->use_pcie_perक्रमmance_levels &&
			data->use_pcie_घातer_saving_levels) अणु
		data->pcie_gen_perक्रमmance = data->pcie_gen_घातer_saving;
		data->pcie_lane_perक्रमmance = data->pcie_lane_घातer_saving;
	पूर्ण
	पंचांगp = smum_get_mac_definition(hwmgr, SMU_MAX_LEVELS_LINK);
	phm_reset_single_dpm_table(&data->dpm_table.pcie_speed_table,
					पंचांगp,
					MAX_REGULAR_DPM_NUMBER);

	अगर (pcie_table != शून्य) अणु
		/* max_entry is used to make sure we reserve one PCIE level
		 * क्रम boot level (fix क्रम A+A PSPP issue).
		 * If PCIE table from PPTable have ULV entry + 8 entries,
		 * then ignore the last entry.*/
		max_entry = (पंचांगp < pcie_table->count) ? पंचांगp : pcie_table->count;
		क्रम (i = 1; i < max_entry; i++) अणु
			phm_setup_pcie_table_entry(&data->dpm_table.pcie_speed_table, i - 1,
					get_pcie_gen_support(data->pcie_gen_cap,
							pcie_table->entries[i].gen_speed),
					get_pcie_lane_support(data->pcie_lane_cap,
							pcie_table->entries[i].lane_width));
		पूर्ण
		data->dpm_table.pcie_speed_table.count = max_entry - 1;
		smum_update_smc_table(hwmgr, SMU_BIF_TABLE);
	पूर्ण अन्यथा अणु
		/* Hardcode Pcie Table */
		phm_setup_pcie_table_entry(&data->dpm_table.pcie_speed_table, 0,
				get_pcie_gen_support(data->pcie_gen_cap,
						PP_Min_PCIEGen),
				get_pcie_lane_support(data->pcie_lane_cap,
						PP_Max_PCIELane));
		phm_setup_pcie_table_entry(&data->dpm_table.pcie_speed_table, 1,
				get_pcie_gen_support(data->pcie_gen_cap,
						PP_Min_PCIEGen),
				get_pcie_lane_support(data->pcie_lane_cap,
						PP_Max_PCIELane));
		phm_setup_pcie_table_entry(&data->dpm_table.pcie_speed_table, 2,
				get_pcie_gen_support(data->pcie_gen_cap,
						PP_Max_PCIEGen),
				get_pcie_lane_support(data->pcie_lane_cap,
						PP_Max_PCIELane));
		phm_setup_pcie_table_entry(&data->dpm_table.pcie_speed_table, 3,
				get_pcie_gen_support(data->pcie_gen_cap,
						PP_Max_PCIEGen),
				get_pcie_lane_support(data->pcie_lane_cap,
						PP_Max_PCIELane));
		phm_setup_pcie_table_entry(&data->dpm_table.pcie_speed_table, 4,
				get_pcie_gen_support(data->pcie_gen_cap,
						PP_Max_PCIEGen),
				get_pcie_lane_support(data->pcie_lane_cap,
						PP_Max_PCIELane));
		phm_setup_pcie_table_entry(&data->dpm_table.pcie_speed_table, 5,
				get_pcie_gen_support(data->pcie_gen_cap,
						PP_Max_PCIEGen),
				get_pcie_lane_support(data->pcie_lane_cap,
						PP_Max_PCIELane));

		data->dpm_table.pcie_speed_table.count = 6;
	पूर्ण
	/* Populate last level क्रम boot PCIE level, but करो not increment count. */
	अगर (hwmgr->chip_family == AMDGPU_FAMILY_CI) अणु
		क्रम (i = 0; i <= data->dpm_table.pcie_speed_table.count; i++)
			phm_setup_pcie_table_entry(&data->dpm_table.pcie_speed_table, i,
				get_pcie_gen_support(data->pcie_gen_cap,
						PP_Max_PCIEGen),
				data->vbios_boot_state.pcie_lane_bootup_value);
	पूर्ण अन्यथा अणु
		phm_setup_pcie_table_entry(&data->dpm_table.pcie_speed_table,
			data->dpm_table.pcie_speed_table.count,
			get_pcie_gen_support(data->pcie_gen_cap,
					PP_Min_PCIEGen),
			get_pcie_lane_support(data->pcie_lane_cap,
					PP_Max_PCIELane));

		अगर (data->pcie_dpm_key_disabled)
			phm_setup_pcie_table_entry(&data->dpm_table.pcie_speed_table,
				data->dpm_table.pcie_speed_table.count,
				smu7_override_pcie_speed(hwmgr), smu7_override_pcie_width(hwmgr));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_reset_dpm_tables(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	स_रखो(&(data->dpm_table), 0x00, माप(data->dpm_table));

	phm_reset_single_dpm_table(
			&data->dpm_table.sclk_table,
				smum_get_mac_definition(hwmgr,
					SMU_MAX_LEVELS_GRAPHICS),
					MAX_REGULAR_DPM_NUMBER);
	phm_reset_single_dpm_table(
			&data->dpm_table.mclk_table,
			smum_get_mac_definition(hwmgr,
				SMU_MAX_LEVELS_MEMORY), MAX_REGULAR_DPM_NUMBER);

	phm_reset_single_dpm_table(
			&data->dpm_table.vddc_table,
				smum_get_mac_definition(hwmgr,
					SMU_MAX_LEVELS_VDDC),
					MAX_REGULAR_DPM_NUMBER);
	phm_reset_single_dpm_table(
			&data->dpm_table.vddci_table,
			smum_get_mac_definition(hwmgr,
				SMU_MAX_LEVELS_VDDCI), MAX_REGULAR_DPM_NUMBER);

	phm_reset_single_dpm_table(
			&data->dpm_table.mvdd_table,
				smum_get_mac_definition(hwmgr,
					SMU_MAX_LEVELS_MVDD),
					MAX_REGULAR_DPM_NUMBER);
	वापस 0;
पूर्ण
/*
 * This function is to initialize all DPM state tables
 * क्रम SMU7 based on the dependency table.
 * Dynamic state patching function will then trim these
 * state tables to the allowed range based
 * on the घातer policy or बाह्यal client requests,
 * such as UVD request, etc.
 */

अटल पूर्णांक smu7_setup_dpm_tables_v0(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_घड़ी_voltage_dependency_table *allowed_vdd_sclk_table =
		hwmgr->dyn_state.vddc_dependency_on_sclk;
	काष्ठा phm_घड़ी_voltage_dependency_table *allowed_vdd_mclk_table =
		hwmgr->dyn_state.vddc_dependency_on_mclk;
	काष्ठा phm_cac_leakage_table *std_voltage_table =
		hwmgr->dyn_state.cac_leakage_table;
	uपूर्णांक32_t i;

	PP_ASSERT_WITH_CODE(allowed_vdd_sclk_table != शून्य,
		"SCLK dependency table is missing. This table is mandatory", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(allowed_vdd_sclk_table->count >= 1,
		"SCLK dependency table has to have is missing. This table is mandatory", वापस -EINVAL);

	PP_ASSERT_WITH_CODE(allowed_vdd_mclk_table != शून्य,
		"MCLK dependency table is missing. This table is mandatory", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(allowed_vdd_mclk_table->count >= 1,
		"VMCLK dependency table has to have is missing. This table is mandatory", वापस -EINVAL);


	/* Initialize Sclk DPM table based on allow Sclk values*/
	data->dpm_table.sclk_table.count = 0;

	क्रम (i = 0; i < allowed_vdd_sclk_table->count; i++) अणु
		अगर (i == 0 || data->dpm_table.sclk_table.dpm_levels[data->dpm_table.sclk_table.count-1].value !=
				allowed_vdd_sclk_table->entries[i].clk) अणु
			data->dpm_table.sclk_table.dpm_levels[data->dpm_table.sclk_table.count].value =
				allowed_vdd_sclk_table->entries[i].clk;
			data->dpm_table.sclk_table.dpm_levels[data->dpm_table.sclk_table.count].enabled = (i == 0) ? 1 : 0;
			data->dpm_table.sclk_table.count++;
		पूर्ण
	पूर्ण

	PP_ASSERT_WITH_CODE(allowed_vdd_mclk_table != शून्य,
		"MCLK dependency table is missing. This table is mandatory", वापस -EINVAL);
	/* Initialize Mclk DPM table based on allow Mclk values */
	data->dpm_table.mclk_table.count = 0;
	क्रम (i = 0; i < allowed_vdd_mclk_table->count; i++) अणु
		अगर (i == 0 || data->dpm_table.mclk_table.dpm_levels[data->dpm_table.mclk_table.count-1].value !=
			allowed_vdd_mclk_table->entries[i].clk) अणु
			data->dpm_table.mclk_table.dpm_levels[data->dpm_table.mclk_table.count].value =
				allowed_vdd_mclk_table->entries[i].clk;
			data->dpm_table.mclk_table.dpm_levels[data->dpm_table.mclk_table.count].enabled = (i == 0) ? 1 : 0;
			data->dpm_table.mclk_table.count++;
		पूर्ण
	पूर्ण

	/* Initialize Vddc DPM table based on allow Vddc values.  And populate corresponding std values. */
	क्रम (i = 0; i < allowed_vdd_sclk_table->count; i++) अणु
		data->dpm_table.vddc_table.dpm_levels[i].value = allowed_vdd_mclk_table->entries[i].v;
		data->dpm_table.vddc_table.dpm_levels[i].param1 = std_voltage_table->entries[i].Leakage;
		/* param1 is क्रम corresponding std voltage */
		data->dpm_table.vddc_table.dpm_levels[i].enabled = true;
	पूर्ण

	data->dpm_table.vddc_table.count = allowed_vdd_sclk_table->count;
	allowed_vdd_mclk_table = hwmgr->dyn_state.vddci_dependency_on_mclk;

	अगर (शून्य != allowed_vdd_mclk_table) अणु
		/* Initialize Vddci DPM table based on allow Mclk values */
		क्रम (i = 0; i < allowed_vdd_mclk_table->count; i++) अणु
			data->dpm_table.vddci_table.dpm_levels[i].value = allowed_vdd_mclk_table->entries[i].v;
			data->dpm_table.vddci_table.dpm_levels[i].enabled = true;
		पूर्ण
		data->dpm_table.vddci_table.count = allowed_vdd_mclk_table->count;
	पूर्ण

	allowed_vdd_mclk_table = hwmgr->dyn_state.mvdd_dependency_on_mclk;

	अगर (शून्य != allowed_vdd_mclk_table) अणु
		/*
		 * Initialize MVDD DPM table based on allow Mclk
		 * values
		 */
		क्रम (i = 0; i < allowed_vdd_mclk_table->count; i++) अणु
			data->dpm_table.mvdd_table.dpm_levels[i].value = allowed_vdd_mclk_table->entries[i].v;
			data->dpm_table.mvdd_table.dpm_levels[i].enabled = true;
		पूर्ण
		data->dpm_table.mvdd_table.count = allowed_vdd_mclk_table->count;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_setup_dpm_tables_v1(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	uपूर्णांक32_t i;

	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_sclk_table;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_mclk_table;

	अगर (table_info == शून्य)
		वापस -EINVAL;

	dep_sclk_table = table_info->vdd_dep_on_sclk;
	dep_mclk_table = table_info->vdd_dep_on_mclk;

	PP_ASSERT_WITH_CODE(dep_sclk_table != शून्य,
			"SCLK dependency table is missing.",
			वापस -EINVAL);
	PP_ASSERT_WITH_CODE(dep_sclk_table->count >= 1,
			"SCLK dependency table count is 0.",
			वापस -EINVAL);

	PP_ASSERT_WITH_CODE(dep_mclk_table != शून्य,
			"MCLK dependency table is missing.",
			वापस -EINVAL);
	PP_ASSERT_WITH_CODE(dep_mclk_table->count >= 1,
			"MCLK dependency table count is 0",
			वापस -EINVAL);

	/* Initialize Sclk DPM table based on allow Sclk values */
	data->dpm_table.sclk_table.count = 0;
	क्रम (i = 0; i < dep_sclk_table->count; i++) अणु
		अगर (i == 0 || data->dpm_table.sclk_table.dpm_levels[data->dpm_table.sclk_table.count - 1].value !=
						dep_sclk_table->entries[i].clk) अणु

			data->dpm_table.sclk_table.dpm_levels[data->dpm_table.sclk_table.count].value =
					dep_sclk_table->entries[i].clk;

			data->dpm_table.sclk_table.dpm_levels[data->dpm_table.sclk_table.count].enabled =
					(i == 0) ? true : false;
			data->dpm_table.sclk_table.count++;
		पूर्ण
	पूर्ण
	अगर (hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock == 0)
		hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock = dep_sclk_table->entries[i-1].clk;
	/* Initialize Mclk DPM table based on allow Mclk values */
	data->dpm_table.mclk_table.count = 0;
	क्रम (i = 0; i < dep_mclk_table->count; i++) अणु
		अगर (i == 0 || data->dpm_table.mclk_table.dpm_levels
				[data->dpm_table.mclk_table.count - 1].value !=
						dep_mclk_table->entries[i].clk) अणु
			data->dpm_table.mclk_table.dpm_levels[data->dpm_table.mclk_table.count].value =
							dep_mclk_table->entries[i].clk;
			data->dpm_table.mclk_table.dpm_levels[data->dpm_table.mclk_table.count].enabled =
							(i == 0) ? true : false;
			data->dpm_table.mclk_table.count++;
		पूर्ण
	पूर्ण

	अगर (hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock == 0)
		hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock = dep_mclk_table->entries[i-1].clk;
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_odn_initial_शेष_setting(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_odn_dpm_table *odn_table = &(data->odn_dpm_table);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	uपूर्णांक32_t i;

	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_sclk_table;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_mclk_table;
	काष्ठा phm_odn_perक्रमmance_level *entries;

	अगर (table_info == शून्य)
		वापस -EINVAL;

	dep_sclk_table = table_info->vdd_dep_on_sclk;
	dep_mclk_table = table_info->vdd_dep_on_mclk;

	odn_table->odn_core_घड़ी_dpm_levels.num_of_pl =
						data->golden_dpm_table.sclk_table.count;
	entries = odn_table->odn_core_घड़ी_dpm_levels.entries;
	क्रम (i=0; i<data->golden_dpm_table.sclk_table.count; i++) अणु
		entries[i].घड़ी = data->golden_dpm_table.sclk_table.dpm_levels[i].value;
		entries[i].enabled = true;
		entries[i].vddc = dep_sclk_table->entries[i].vddc;
	पूर्ण

	smu_get_voltage_dependency_table_ppt_v1(dep_sclk_table,
		(काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *)&(odn_table->vdd_dependency_on_sclk));

	odn_table->odn_memory_घड़ी_dpm_levels.num_of_pl =
						data->golden_dpm_table.mclk_table.count;
	entries = odn_table->odn_memory_घड़ी_dpm_levels.entries;
	क्रम (i=0; i<data->golden_dpm_table.mclk_table.count; i++) अणु
		entries[i].घड़ी = data->golden_dpm_table.mclk_table.dpm_levels[i].value;
		entries[i].enabled = true;
		entries[i].vddc = dep_mclk_table->entries[i].vddc;
	पूर्ण

	smu_get_voltage_dependency_table_ppt_v1(dep_mclk_table,
		(काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *)&(odn_table->vdd_dependency_on_mclk));

	वापस 0;
पूर्ण

अटल व्योम smu7_setup_voltage_range_from_vbios(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_sclk_table;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	uपूर्णांक32_t min_vddc = 0;
	uपूर्णांक32_t max_vddc = 0;

	अगर (!table_info)
		वापस;

	dep_sclk_table = table_info->vdd_dep_on_sclk;

	atomctrl_get_voltage_range(hwmgr, &max_vddc, &min_vddc);

	अगर (min_vddc == 0 || min_vddc > 2000
		|| min_vddc > dep_sclk_table->entries[0].vddc)
		min_vddc = dep_sclk_table->entries[0].vddc;

	अगर (max_vddc == 0 || max_vddc > 2000
		|| max_vddc < dep_sclk_table->entries[dep_sclk_table->count-1].vddc)
		max_vddc = dep_sclk_table->entries[dep_sclk_table->count-1].vddc;

	data->odn_dpm_table.min_vddc = min_vddc;
	data->odn_dpm_table.max_vddc = max_vddc;
पूर्ण

अटल व्योम smu7_check_dpm_table_updated(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_odn_dpm_table *odn_table = &(data->odn_dpm_table);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	uपूर्णांक32_t i;

	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_table;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *odn_dep_table;

	अगर (table_info == शून्य)
		वापस;

	क्रम (i = 0; i < data->dpm_table.sclk_table.count; i++) अणु
		अगर (odn_table->odn_core_घड़ी_dpm_levels.entries[i].घड़ी !=
					data->dpm_table.sclk_table.dpm_levels[i].value) अणु
			data->need_update_smu7_dpm_table |= DPMTABLE_OD_UPDATE_SCLK;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < data->dpm_table.mclk_table.count; i++) अणु
		अगर (odn_table->odn_memory_घड़ी_dpm_levels.entries[i].घड़ी !=
					data->dpm_table.mclk_table.dpm_levels[i].value) अणु
			data->need_update_smu7_dpm_table |= DPMTABLE_OD_UPDATE_MCLK;
			अवरोध;
		पूर्ण
	पूर्ण

	dep_table = table_info->vdd_dep_on_mclk;
	odn_dep_table = (काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *)&(odn_table->vdd_dependency_on_mclk);

	क्रम (i = 0; i < dep_table->count; i++) अणु
		अगर (dep_table->entries[i].vddc != odn_dep_table->entries[i].vddc) अणु
			data->need_update_smu7_dpm_table |= DPMTABLE_OD_UPDATE_VDDC | DPMTABLE_OD_UPDATE_MCLK;
			वापस;
		पूर्ण
	पूर्ण

	dep_table = table_info->vdd_dep_on_sclk;
	odn_dep_table = (काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *)&(odn_table->vdd_dependency_on_sclk);
	क्रम (i = 0; i < dep_table->count; i++) अणु
		अगर (dep_table->entries[i].vddc != odn_dep_table->entries[i].vddc) अणु
			data->need_update_smu7_dpm_table |= DPMTABLE_OD_UPDATE_VDDC | DPMTABLE_OD_UPDATE_SCLK;
			वापस;
		पूर्ण
	पूर्ण
	अगर (data->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_VDDC) अणु
		data->need_update_smu7_dpm_table &= ~DPMTABLE_OD_UPDATE_VDDC;
		data->need_update_smu7_dpm_table |= DPMTABLE_OD_UPDATE_SCLK | DPMTABLE_OD_UPDATE_MCLK;
	पूर्ण
पूर्ण

अटल पूर्णांक smu7_setup_शेष_dpm_tables(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	smu7_reset_dpm_tables(hwmgr);

	अगर (hwmgr->pp_table_version == PP_TABLE_V1)
		smu7_setup_dpm_tables_v1(hwmgr);
	अन्यथा अगर (hwmgr->pp_table_version == PP_TABLE_V0)
		smu7_setup_dpm_tables_v0(hwmgr);

	smu7_setup_शेष_pcie_table(hwmgr);

	/* save a copy of the शेष DPM table */
	स_नकल(&(data->golden_dpm_table), &(data->dpm_table),
			माप(काष्ठा smu7_dpm_table));

	/* initialize ODN table */
	अगर (hwmgr->od_enabled) अणु
		अगर (data->odn_dpm_table.max_vddc) अणु
			smu7_check_dpm_table_updated(hwmgr);
		पूर्ण अन्यथा अणु
			smu7_setup_voltage_range_from_vbios(hwmgr);
			smu7_odn_initial_शेष_setting(hwmgr);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_enable_vrhot_gpio_पूर्णांकerrupt(काष्ठा pp_hwmgr *hwmgr)
अणु

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_RegulatorHot))
		वापस smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_EnableVRHotGPIOInterrupt,
				शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_enable_sclk_control(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, SCLK_PWRMGT_CNTL,
			SCLK_PWRMGT_OFF, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_enable_ulv(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (data->ulv_supported)
		वापस smum_send_msg_to_smc(hwmgr, PPSMC_MSG_EnableULV, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_disable_ulv(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (data->ulv_supported)
		वापस smum_send_msg_to_smc(hwmgr, PPSMC_MSG_DisableULV, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_enable_deep_sleep_master_चयन(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_SclkDeepSleep)) अणु
		अगर (smum_send_msg_to_smc(hwmgr, PPSMC_MSG_MASTER_DeepSleep_ON, शून्य))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to enable Master Deep Sleep switch failed!",
					वापस -EINVAL);
	पूर्ण अन्यथा अणु
		अगर (smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_MASTER_DeepSleep_OFF,
				शून्य)) अणु
			PP_ASSERT_WITH_CODE(false,
					"Attempt to disable Master Deep Sleep switch failed!",
					वापस -EINVAL);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_disable_deep_sleep_master_चयन(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_SclkDeepSleep)) अणु
		अगर (smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_MASTER_DeepSleep_OFF,
				शून्य)) अणु
			PP_ASSERT_WITH_CODE(false,
					"Attempt to disable Master Deep Sleep switch failed!",
					वापस -EINVAL);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_disable_sclk_vce_handshake(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t soft_रेजिस्टर_value = 0;
	uपूर्णांक32_t handshake_disables_offset = data->soft_regs_start
				+ smum_get_दुरत्व(hwmgr,
					SMU_SoftRegisters, HandshakeDisables);

	soft_रेजिस्टर_value = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device,
				CGS_IND_REG__SMC, handshake_disables_offset);
	soft_रेजिस्टर_value |= SMU7_VCE_SCLK_HANDSHAKE_DISABLE;
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			handshake_disables_offset, soft_रेजिस्टर_value);
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_disable_handshake_uvd(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t soft_रेजिस्टर_value = 0;
	uपूर्णांक32_t handshake_disables_offset = data->soft_regs_start
				+ smum_get_दुरत्व(hwmgr,
					SMU_SoftRegisters, HandshakeDisables);

	soft_रेजिस्टर_value = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device,
				CGS_IND_REG__SMC, handshake_disables_offset);
	soft_रेजिस्टर_value |= smum_get_mac_definition(hwmgr,
					SMU_UVD_MCLK_HANDSHAKE_DISABLE);
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			handshake_disables_offset, soft_रेजिस्टर_value);
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_enable_sclk_mclk_dpm(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	/* enable SCLK dpm */
	अगर (!data->sclk_dpm_key_disabled) अणु
		अगर (hwmgr->chip_id >= CHIP_POLARIS10 &&
		    hwmgr->chip_id <= CHIP_VEGAM)
			smu7_disable_sclk_vce_handshake(hwmgr);

		PP_ASSERT_WITH_CODE(
		(0 == smum_send_msg_to_smc(hwmgr, PPSMC_MSG_DPM_Enable, शून्य)),
		"Failed to enable SCLK DPM during DPM Start Function!",
		वापस -EINVAL);
	पूर्ण

	/* enable MCLK dpm */
	अगर (0 == data->mclk_dpm_key_disabled) अणु
		अगर (!(hwmgr->feature_mask & PP_UVD_HANDSHAKE_MASK))
			smu7_disable_handshake_uvd(hwmgr);

		PP_ASSERT_WITH_CODE(
				(0 == smum_send_msg_to_smc(hwmgr,
						PPSMC_MSG_MCLKDPM_Enable,
						शून्य)),
				"Failed to enable MCLK DPM during DPM Start Function!",
				वापस -EINVAL);

		अगर ((hwmgr->chip_family == AMDGPU_FAMILY_CI) ||
		    (hwmgr->chip_id == CHIP_POLARIS10) ||
		    (hwmgr->chip_id == CHIP_POLARIS11) ||
		    (hwmgr->chip_id == CHIP_POLARIS12) ||
		    (hwmgr->chip_id == CHIP_TONGA) ||
		    (hwmgr->chip_id == CHIP_TOPAZ))
			PHM_WRITE_FIELD(hwmgr->device, MC_SEQ_CNTL_3, CAC_EN, 0x1);


		अगर (hwmgr->chip_family == AMDGPU_FAMILY_CI) अणु
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, 0xc0400d30, 0x5);
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, 0xc0400d3c, 0x5);
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, 0xc0400d80, 0x100005);
			udelay(10);
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, 0xc0400d30, 0x400005);
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, 0xc0400d3c, 0x400005);
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, 0xc0400d80, 0x500005);
		पूर्ण अन्यथा अणु
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixLCAC_MC0_CNTL, 0x5);
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixLCAC_MC1_CNTL, 0x5);
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixLCAC_CPL_CNTL, 0x100005);
			udelay(10);
			अगर (hwmgr->chip_id == CHIP_VEGAM) अणु
				cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixLCAC_MC0_CNTL, 0x400009);
				cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixLCAC_MC1_CNTL, 0x400009);
			पूर्ण अन्यथा अणु
				cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixLCAC_MC0_CNTL, 0x400005);
				cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixLCAC_MC1_CNTL, 0x400005);
			पूर्ण
			cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixLCAC_CPL_CNTL, 0x500005);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_start_dpm(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	/*enable general घातer management */

	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, GENERAL_PWRMGT,
			GLOBAL_PWRMGT_EN, 1);

	/* enable sclk deep sleep */

	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, SCLK_PWRMGT_CNTL,
			DYNAMIC_PM_EN, 1);

	/* prepare क्रम PCIE DPM */

	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			data->soft_regs_start +
			smum_get_दुरत्व(hwmgr, SMU_SoftRegisters,
						VoltageChangeTimeout), 0x1000);
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__PCIE,
			SWRST_COMMAND_1, RESETLC, 0x0);

	अगर (hwmgr->chip_family == AMDGPU_FAMILY_CI)
		cgs_ग_लिखो_रेजिस्टर(hwmgr->device, 0x1488,
			(cgs_पढ़ो_रेजिस्टर(hwmgr->device, 0x1488) & ~0x1));

	अगर (smu7_enable_sclk_mclk_dpm(hwmgr)) अणु
		pr_err("Failed to enable Sclk DPM and Mclk DPM!");
		वापस -EINVAL;
	पूर्ण

	/* enable PCIE dpm */
	अगर (0 == data->pcie_dpm_key_disabled) अणु
		PP_ASSERT_WITH_CODE(
				(0 == smum_send_msg_to_smc(hwmgr,
						PPSMC_MSG_PCIeDPM_Enable,
						शून्य)),
				"Failed to enable pcie DPM during DPM Start Function!",
				वापस -EINVAL);
	पूर्ण अन्यथा अणु
		PP_ASSERT_WITH_CODE(
				(0 == smum_send_msg_to_smc(hwmgr,
						PPSMC_MSG_PCIeDPM_Disable,
						शून्य)),
				"Failed to disable pcie DPM during DPM Start Function!",
				वापस -EINVAL);
	पूर्ण

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_Falcon_QuickTransition)) अणु
		PP_ASSERT_WITH_CODE((0 == smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_EnableACDCGPIOInterrupt,
				शून्य)),
				"Failed to enable AC DC GPIO Interrupt!",
				);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_disable_sclk_mclk_dpm(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	/* disable SCLK dpm */
	अगर (!data->sclk_dpm_key_disabled) अणु
		PP_ASSERT_WITH_CODE(true == smum_is_dpm_running(hwmgr),
				"Trying to disable SCLK DPM when DPM is disabled",
				वापस 0);
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_DPM_Disable, शून्य);
	पूर्ण

	/* disable MCLK dpm */
	अगर (!data->mclk_dpm_key_disabled) अणु
		PP_ASSERT_WITH_CODE(true == smum_is_dpm_running(hwmgr),
				"Trying to disable MCLK DPM when DPM is disabled",
				वापस 0);
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_MCLKDPM_Disable, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_stop_dpm(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	/* disable general घातer management */
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, GENERAL_PWRMGT,
			GLOBAL_PWRMGT_EN, 0);
	/* disable sclk deep sleep */
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, SCLK_PWRMGT_CNTL,
			DYNAMIC_PM_EN, 0);

	/* disable PCIE dpm */
	अगर (!data->pcie_dpm_key_disabled) अणु
		PP_ASSERT_WITH_CODE(
				(smum_send_msg_to_smc(hwmgr,
						PPSMC_MSG_PCIeDPM_Disable,
						शून्य) == 0),
				"Failed to disable pcie DPM during DPM Stop Function!",
				वापस -EINVAL);
	पूर्ण

	smu7_disable_sclk_mclk_dpm(hwmgr);

	PP_ASSERT_WITH_CODE(true == smum_is_dpm_running(hwmgr),
			"Trying to disable voltage DPM when DPM is disabled",
			वापस 0);

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_Voltage_Cntl_Disable, शून्य);

	वापस 0;
पूर्ण

अटल व्योम smu7_set_dpm_event_sources(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t sources)
अणु
	bool protection;
	क्रमागत DPM_EVENT_SRC src;

	चयन (sources) अणु
	शेष:
		pr_err("Unknown throttling event sources.");
		fallthrough;
	हाल 0:
		protection = false;
		/* src is unused */
		अवरोध;
	हाल (1 << PHM_AutoThrottleSource_Thermal):
		protection = true;
		src = DPM_EVENT_SRC_DIGITAL;
		अवरोध;
	हाल (1 << PHM_AutoThrottleSource_External):
		protection = true;
		src = DPM_EVENT_SRC_EXTERNAL;
		अवरोध;
	हाल (1 << PHM_AutoThrottleSource_External) |
			(1 << PHM_AutoThrottleSource_Thermal):
		protection = true;
		src = DPM_EVENT_SRC_DIGITAL_OR_EXTERNAL;
		अवरोध;
	पूर्ण
	/* Order matters - करोn't enable thermal protection क्रम the wrong source. */
	अगर (protection) अणु
		PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, CG_THERMAL_CTRL,
				DPM_EVENT_SRC, src);
		PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, GENERAL_PWRMGT,
				THERMAL_PROTECTION_DIS,
				!phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
						PHM_Platक्रमmCaps_ThermalController));
	पूर्ण अन्यथा
		PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, GENERAL_PWRMGT,
				THERMAL_PROTECTION_DIS, 1);
पूर्ण

अटल पूर्णांक smu7_enable_स्वतः_throttle_source(काष्ठा pp_hwmgr *hwmgr,
		PHM_AutoThrottleSource source)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (!(data->active_स्वतः_throttle_sources & (1 << source))) अणु
		data->active_स्वतः_throttle_sources |= 1 << source;
		smu7_set_dpm_event_sources(hwmgr, data->active_स्वतः_throttle_sources);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_enable_thermal_स्वतः_throttle(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस smu7_enable_स्वतः_throttle_source(hwmgr, PHM_AutoThrottleSource_Thermal);
पूर्ण

अटल पूर्णांक smu7_disable_स्वतः_throttle_source(काष्ठा pp_hwmgr *hwmgr,
		PHM_AutoThrottleSource source)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (data->active_स्वतः_throttle_sources & (1 << source)) अणु
		data->active_स्वतः_throttle_sources &= ~(1 << source);
		smu7_set_dpm_event_sources(hwmgr, data->active_स्वतः_throttle_sources);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_disable_thermal_स्वतः_throttle(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस smu7_disable_स्वतः_throttle_source(hwmgr, PHM_AutoThrottleSource_Thermal);
पूर्ण

अटल पूर्णांक smu7_pcie_perक्रमmance_request(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	data->pcie_perक्रमmance_request = true;

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_program_edc_didt_रेजिस्टरs(काष्ठा pp_hwmgr *hwmgr,
					   uपूर्णांक32_t *cac_config_regs,
					   AtomCtrl_EDCLeakgeTable *edc_leakage_table)
अणु
	uपूर्णांक32_t data, i = 0;

	जबतक (cac_config_regs[i] != 0xFFFFFFFF) अणु
		data = edc_leakage_table->DIDT_REG[i];
		cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device,
				       CGS_IND_REG__DIDT,
				       cac_config_regs[i],
				       data);
		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_populate_edc_leakage_रेजिस्टरs(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	पूर्णांक ret = 0;

	अगर (!data->disable_edc_leakage_controller &&
	    data->edc_hilo_leakage_offset_from_vbios.usEdcDidtLoDpm7TableOffset &&
	    data->edc_hilo_leakage_offset_from_vbios.usEdcDidtHiDpm7TableOffset) अणु
		ret = smu7_program_edc_didt_रेजिस्टरs(hwmgr,
						      DIDTEDCConfig_P12,
						      &data->edc_leakage_table);
		अगर (ret)
			वापस ret;

		ret = smum_send_msg_to_smc(hwmgr,
					   (PPSMC_Msg)PPSMC_MSG_EnableEDCController,
					   शून्य);
	पूर्ण अन्यथा अणु
		ret = smum_send_msg_to_smc(hwmgr,
					   (PPSMC_Msg)PPSMC_MSG_DisableEDCController,
					   शून्य);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक smu7_enable_dpm_tasks(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक पंचांगp_result = 0;
	पूर्णांक result = 0;

	अगर (smu7_voltage_control(hwmgr)) अणु
		पंचांगp_result = smu7_enable_voltage_control(hwmgr);
		PP_ASSERT_WITH_CODE(पंचांगp_result == 0,
				"Failed to enable voltage control!",
				result = पंचांगp_result);

		पंचांगp_result = smu7_स्थिरruct_voltage_tables(hwmgr);
		PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
				"Failed to construct voltage tables!",
				result = पंचांगp_result);
	पूर्ण
	smum_initialize_mc_reg_table(hwmgr);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_EngineSpपढ़ोSpectrumSupport))
		PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
				GENERAL_PWRMGT, DYN_SPREAD_SPECTRUM_EN, 1);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_ThermalController))
		PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
				GENERAL_PWRMGT, THERMAL_PROTECTION_DIS, 0);

	पंचांगp_result = smu7_program_अटल_screen_threshold_parameters(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to program static screen threshold parameters!",
			result = पंचांगp_result);

	पंचांगp_result = smu7_enable_display_gap(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to enable display gap!", result = पंचांगp_result);

	पंचांगp_result = smu7_program_voting_clients(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to program voting clients!", result = पंचांगp_result);

	पंचांगp_result = smum_process_firmware_header(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to process firmware header!", result = पंचांगp_result);

	अगर (hwmgr->chip_id != CHIP_VEGAM) अणु
		पंचांगp_result = smu7_initial_चयन_from_arbf0_to_f1(hwmgr);
		PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
				"Failed to initialize switch from ArbF0 to F1!",
				result = पंचांगp_result);
	पूर्ण

	result = smu7_setup_शेष_dpm_tables(hwmgr);
	PP_ASSERT_WITH_CODE(0 == result,
			"Failed to setup default DPM tables!", वापस result);

	पंचांगp_result = smum_init_smc_table(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to initialize SMC table!", result = पंचांगp_result);

	पंचांगp_result = smu7_enable_vrhot_gpio_पूर्णांकerrupt(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to enable VR hot GPIO interrupt!", result = पंचांगp_result);

	अगर (hwmgr->chip_id >= CHIP_POLARIS10 &&
	    hwmgr->chip_id <= CHIP_VEGAM) अणु
		पंचांगp_result = smu7_notअगरy_has_display(hwmgr);
		PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
				"Failed to enable display setting!", result = पंचांगp_result);
	पूर्ण अन्यथा अणु
		smum_send_msg_to_smc(hwmgr, (PPSMC_Msg)PPSMC_NoDisplay, शून्य);
	पूर्ण

	अगर (hwmgr->chip_id >= CHIP_POLARIS10 &&
	    hwmgr->chip_id <= CHIP_VEGAM) अणु
		पंचांगp_result = smu7_populate_edc_leakage_रेजिस्टरs(hwmgr);
		PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
				"Failed to populate edc leakage registers!", result = पंचांगp_result);
	पूर्ण

	पंचांगp_result = smu7_enable_sclk_control(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to enable SCLK control!", result = पंचांगp_result);

	पंचांगp_result = smu7_enable_smc_voltage_controller(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to enable voltage control!", result = पंचांगp_result);

	पंचांगp_result = smu7_enable_ulv(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to enable ULV!", result = पंचांगp_result);

	पंचांगp_result = smu7_enable_deep_sleep_master_चयन(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to enable deep sleep master switch!", result = पंचांगp_result);

	पंचांगp_result = smu7_enable_didt_config(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to enable deep sleep master switch!", result = पंचांगp_result);

	पंचांगp_result = smu7_start_dpm(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to start DPM!", result = पंचांगp_result);

	पंचांगp_result = smu7_enable_smc_cac(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to enable SMC CAC!", result = पंचांगp_result);

	पंचांगp_result = smu7_enable_घातer_containment(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to enable power containment!", result = पंचांगp_result);

	पंचांगp_result = smu7_घातer_control_set_level(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to power control set level!", result = पंचांगp_result);

	पंचांगp_result = smu7_enable_thermal_स्वतः_throttle(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to enable thermal auto throttle!", result = पंचांगp_result);

	पंचांगp_result = smu7_pcie_perक्रमmance_request(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"pcie performance request failed!", result = पंचांगp_result);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_avfs_control(काष्ठा pp_hwmgr *hwmgr, bool enable)
अणु
	अगर (!hwmgr->avfs_supported)
		वापस 0;

	अगर (enable) अणु
		अगर (!PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device,
				CGS_IND_REG__SMC, FEATURE_STATUS, AVS_ON)) अणु
			PP_ASSERT_WITH_CODE(!smum_send_msg_to_smc(
					hwmgr, PPSMC_MSG_EnableAvfs, शून्य),
					"Failed to enable AVFS!",
					वापस -EINVAL);
		पूर्ण
	पूर्ण अन्यथा अगर (PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device,
			CGS_IND_REG__SMC, FEATURE_STATUS, AVS_ON)) अणु
		PP_ASSERT_WITH_CODE(!smum_send_msg_to_smc(
				hwmgr, PPSMC_MSG_DisableAvfs, शून्य),
				"Failed to disable AVFS!",
				वापस -EINVAL);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_update_avfs(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (!hwmgr->avfs_supported)
		वापस 0;

	अगर (data->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_VDDC) अणु
		smu7_avfs_control(hwmgr, false);
	पूर्ण अन्यथा अगर (data->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_SCLK) अणु
		smu7_avfs_control(hwmgr, false);
		smu7_avfs_control(hwmgr, true);
	पूर्ण अन्यथा अणु
		smu7_avfs_control(hwmgr, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_disable_dpm_tasks(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक पंचांगp_result, result = 0;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_ThermalController))
		PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
				GENERAL_PWRMGT, THERMAL_PROTECTION_DIS, 1);

	पंचांगp_result = smu7_disable_घातer_containment(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to disable power containment!", result = पंचांगp_result);

	पंचांगp_result = smu7_disable_smc_cac(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to disable SMC CAC!", result = पंचांगp_result);

	पंचांगp_result = smu7_disable_didt_config(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to disable DIDT!", result = पंचांगp_result);

	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_SPLL_SPREAD_SPECTRUM, SSEN, 0);
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			GENERAL_PWRMGT, DYN_SPREAD_SPECTRUM_EN, 0);

	पंचांगp_result = smu7_disable_thermal_स्वतः_throttle(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to disable thermal auto throttle!", result = पंचांगp_result);

	पंचांगp_result = smu7_avfs_control(hwmgr, false);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to disable AVFS!", result = पंचांगp_result);

	पंचांगp_result = smu7_stop_dpm(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to stop DPM!", result = पंचांगp_result);

	पंचांगp_result = smu7_disable_deep_sleep_master_चयन(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to disable deep sleep master switch!", result = पंचांगp_result);

	पंचांगp_result = smu7_disable_ulv(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to disable ULV!", result = पंचांगp_result);

	पंचांगp_result = smu7_clear_voting_clients(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to clear voting clients!", result = पंचांगp_result);

	पंचांगp_result = smu7_reset_to_शेष(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to reset to default!", result = पंचांगp_result);

	पंचांगp_result = smum_stop_smc(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to stop smc!", result = पंचांगp_result);

	पंचांगp_result = smu7_क्रमce_चयन_to_arbf0(hwmgr);
	PP_ASSERT_WITH_CODE((पंचांगp_result == 0),
			"Failed to force to switch arbf0!", result = पंचांगp_result);

	वापस result;
पूर्ण

अटल व्योम smu7_init_dpm_शेषs(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक8_t पंचांगp1, पंचांगp2;
	uपूर्णांक16_t पंचांगp3 = 0;

	data->dll_शेष_on = false;
	data->mclk_dpm0_activity_target = 0xa;
	data->vddc_vddgfx_delta = 300;
	data->अटल_screen_threshold = SMU7_STATICSCREENTHRESHOLD_DFLT;
	data->अटल_screen_threshold_unit = SMU7_STATICSCREENTHRESHOLDUNIT_DFLT;
	data->voting_rights_clients[0] = SMU7_VOTINGRIGHTSCLIENTS_DFLT0;
	data->voting_rights_clients[1]= SMU7_VOTINGRIGHTSCLIENTS_DFLT1;
	data->voting_rights_clients[2] = SMU7_VOTINGRIGHTSCLIENTS_DFLT2;
	data->voting_rights_clients[3]= SMU7_VOTINGRIGHTSCLIENTS_DFLT3;
	data->voting_rights_clients[4]= SMU7_VOTINGRIGHTSCLIENTS_DFLT4;
	data->voting_rights_clients[5]= SMU7_VOTINGRIGHTSCLIENTS_DFLT5;
	data->voting_rights_clients[6]= SMU7_VOTINGRIGHTSCLIENTS_DFLT6;
	data->voting_rights_clients[7]= SMU7_VOTINGRIGHTSCLIENTS_DFLT7;

	data->mclk_dpm_key_disabled = hwmgr->feature_mask & PP_MCLK_DPM_MASK ? false : true;
	data->sclk_dpm_key_disabled = hwmgr->feature_mask & PP_SCLK_DPM_MASK ? false : true;
	data->pcie_dpm_key_disabled = hwmgr->feature_mask & PP_PCIE_DPM_MASK ? false : true;
	/* need to set voltage control types beक्रमe EVV patching */
	data->voltage_control = SMU7_VOLTAGE_CONTROL_NONE;
	data->vddci_control = SMU7_VOLTAGE_CONTROL_NONE;
	data->mvdd_control = SMU7_VOLTAGE_CONTROL_NONE;
	data->enable_tdc_limit_feature = true;
	data->enable_pkg_pwr_tracking_feature = true;
	data->क्रमce_pcie_gen = PP_PCIEGenInvalid;
	data->ulv_supported = hwmgr->feature_mask & PP_ULV_MASK ? true : false;
	data->current_profile_setting.bupdate_sclk = 1;
	data->current_profile_setting.sclk_up_hyst = 0;
	data->current_profile_setting.sclk_करोwn_hyst = 100;
	data->current_profile_setting.sclk_activity = SMU7_SCLK_TARGETACTIVITY_DFLT;
	data->current_profile_setting.bupdate_mclk = 1;
	अगर (hwmgr->chip_id >= CHIP_POLARIS10) अणु
		अगर (adev->gmc.vram_width == 256) अणु
			data->current_profile_setting.mclk_up_hyst = 10;
			data->current_profile_setting.mclk_करोwn_hyst = 60;
			data->current_profile_setting.mclk_activity = 25;
		पूर्ण अन्यथा अगर (adev->gmc.vram_width == 128) अणु
			data->current_profile_setting.mclk_up_hyst = 5;
			data->current_profile_setting.mclk_करोwn_hyst = 16;
			data->current_profile_setting.mclk_activity = 20;
		पूर्ण अन्यथा अगर (adev->gmc.vram_width == 64) अणु
			data->current_profile_setting.mclk_up_hyst = 3;
			data->current_profile_setting.mclk_करोwn_hyst = 16;
			data->current_profile_setting.mclk_activity = 20;
		पूर्ण
	पूर्ण अन्यथा अणु
		data->current_profile_setting.mclk_up_hyst = 0;
		data->current_profile_setting.mclk_करोwn_hyst = 100;
		data->current_profile_setting.mclk_activity = SMU7_MCLK_TARGETACTIVITY_DFLT;
	पूर्ण
	hwmgr->workload_mask = 1 << hwmgr->workload_prority[PP_SMC_POWER_PROखाता_FULLSCREEN3D];
	hwmgr->घातer_profile_mode = PP_SMC_POWER_PROखाता_FULLSCREEN3D;
	hwmgr->शेष_घातer_profile_mode = PP_SMC_POWER_PROखाता_FULLSCREEN3D;

	अगर (hwmgr->chip_id  == CHIP_HAWAII) अणु
		data->thermal_temp_setting.temperature_low = 94500;
		data->thermal_temp_setting.temperature_high = 95000;
		data->thermal_temp_setting.temperature_shutकरोwn = 104000;
	पूर्ण अन्यथा अणु
		data->thermal_temp_setting.temperature_low = 99500;
		data->thermal_temp_setting.temperature_high = 100000;
		data->thermal_temp_setting.temperature_shutकरोwn = 104000;
	पूर्ण

	data->fast_watermark_threshold = 100;
	अगर (atomctrl_is_voltage_controlled_by_gpio_v3(hwmgr,
			VOLTAGE_TYPE_VDDC, VOLTAGE_OBJ_SVID2))
		data->voltage_control = SMU7_VOLTAGE_CONTROL_BY_SVID2;
	अन्यथा अगर (atomctrl_is_voltage_controlled_by_gpio_v3(hwmgr,
			VOLTAGE_TYPE_VDDC, VOLTAGE_OBJ_GPIO_LUT))
		data->voltage_control = SMU7_VOLTAGE_CONTROL_BY_GPIO;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_ControlVDDGFX)) अणु
		अगर (atomctrl_is_voltage_controlled_by_gpio_v3(hwmgr,
			VOLTAGE_TYPE_VDDGFX, VOLTAGE_OBJ_SVID2)) अणु
			data->vdd_gfx_control = SMU7_VOLTAGE_CONTROL_BY_SVID2;
		पूर्ण
	पूर्ण

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_EnableMVDDControl)) अणु
		अगर (atomctrl_is_voltage_controlled_by_gpio_v3(hwmgr,
				VOLTAGE_TYPE_MVDDC, VOLTAGE_OBJ_GPIO_LUT))
			data->mvdd_control = SMU7_VOLTAGE_CONTROL_BY_GPIO;
		अन्यथा अगर (atomctrl_is_voltage_controlled_by_gpio_v3(hwmgr,
				VOLTAGE_TYPE_MVDDC, VOLTAGE_OBJ_SVID2))
			data->mvdd_control = SMU7_VOLTAGE_CONTROL_BY_SVID2;
	पूर्ण

	अगर (SMU7_VOLTAGE_CONTROL_NONE == data->vdd_gfx_control)
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_ControlVDDGFX);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_ControlVDDCI)) अणु
		अगर (atomctrl_is_voltage_controlled_by_gpio_v3(hwmgr,
				VOLTAGE_TYPE_VDDCI, VOLTAGE_OBJ_GPIO_LUT))
			data->vddci_control = SMU7_VOLTAGE_CONTROL_BY_GPIO;
		अन्यथा अगर (atomctrl_is_voltage_controlled_by_gpio_v3(hwmgr,
				VOLTAGE_TYPE_VDDCI, VOLTAGE_OBJ_SVID2))
			data->vddci_control = SMU7_VOLTAGE_CONTROL_BY_SVID2;
	पूर्ण

	अगर (data->mvdd_control == SMU7_VOLTAGE_CONTROL_NONE)
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_EnableMVDDControl);

	अगर (data->vddci_control == SMU7_VOLTAGE_CONTROL_NONE)
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_ControlVDDCI);

	data->vddc_phase_shed_control = 1;
	अगर ((hwmgr->chip_id == CHIP_POLARIS12) ||
	    ASICID_IS_P20(adev->pdev->device, adev->pdev->revision) ||
	    ASICID_IS_P21(adev->pdev->device, adev->pdev->revision) ||
	    ASICID_IS_P30(adev->pdev->device, adev->pdev->revision) ||
	    ASICID_IS_P31(adev->pdev->device, adev->pdev->revision)) अणु
		अगर (data->voltage_control == SMU7_VOLTAGE_CONTROL_BY_SVID2) अणु
			atomctrl_get_svi2_info(hwmgr, VOLTAGE_TYPE_VDDC, &पंचांगp1, &पंचांगp2,
							&पंचांगp3);
			पंचांगp3 = (पंचांगp3 >> 5) & 0x3;
			data->vddc_phase_shed_control = ((पंचांगp3 << 1) | (पंचांगp3 >> 1)) & 0x3;
		पूर्ण
	पूर्ण अन्यथा अगर (hwmgr->chip_family == AMDGPU_FAMILY_CI) अणु
		data->vddc_phase_shed_control = 1;
	पूर्ण

	अगर ((hwmgr->pp_table_version != PP_TABLE_V0) && (hwmgr->feature_mask & PP_CLOCK_STRETCH_MASK)
		&& (table_info->cac_dtp_table->usClockStretchAmount != 0))
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_ClockStretcher);

	data->pcie_gen_perक्रमmance.max = PP_PCIEGen1;
	data->pcie_gen_perक्रमmance.min = PP_PCIEGen3;
	data->pcie_gen_घातer_saving.max = PP_PCIEGen1;
	data->pcie_gen_घातer_saving.min = PP_PCIEGen3;
	data->pcie_lane_perक्रमmance.max = 0;
	data->pcie_lane_perक्रमmance.min = 16;
	data->pcie_lane_घातer_saving.max = 0;
	data->pcie_lane_घातer_saving.min = 16;


	अगर (adev->pg_flags & AMD_PG_SUPPORT_UVD)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			      PHM_Platक्रमmCaps_UVDPowerGating);
	अगर (adev->pg_flags & AMD_PG_SUPPORT_VCE)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			      PHM_Platक्रमmCaps_VCEPowerGating);

	data->disable_edc_leakage_controller = true;
	अगर (((adev->asic_type == CHIP_POLARIS10) && hwmgr->is_kicker) ||
	    ((adev->asic_type == CHIP_POLARIS11) && hwmgr->is_kicker) ||
	    (adev->asic_type == CHIP_POLARIS12) ||
	    (adev->asic_type == CHIP_VEGAM))
		data->disable_edc_leakage_controller = false;

	अगर (!atomctrl_is_asic_पूर्णांकernal_ss_supported(hwmgr)) अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_MemorySpपढ़ोSpectrumSupport);
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_EngineSpपढ़ोSpectrumSupport);
	पूर्ण

	अगर ((adev->pdev->device == 0x699F) &&
	    (adev->pdev->revision == 0xCF)) अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_PowerContainment);
		data->enable_tdc_limit_feature = false;
		data->enable_pkg_pwr_tracking_feature = false;
		data->disable_edc_leakage_controller = true;
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_ClockStretcher);
	पूर्ण
पूर्ण

अटल पूर्णांक smu7_calculate_ro_range(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t asicrev1, evv_revision, max = 0, min = 0;

	atomctrl_पढ़ो_efuse(hwmgr, STRAP_EVV_REVISION_LSB, STRAP_EVV_REVISION_MSB,
			&evv_revision);

	atomctrl_पढ़ो_efuse(hwmgr, 568, 579, &asicrev1);

	अगर (ASICID_IS_P20(adev->pdev->device, adev->pdev->revision) ||
	    ASICID_IS_P30(adev->pdev->device, adev->pdev->revision)) अणु
		min = 1200;
		max = 2500;
	पूर्ण अन्यथा अगर (ASICID_IS_P21(adev->pdev->device, adev->pdev->revision) ||
		   ASICID_IS_P31(adev->pdev->device, adev->pdev->revision)) अणु
		min = 900;
		max= 2100;
	पूर्ण अन्यथा अगर (hwmgr->chip_id == CHIP_POLARIS10) अणु
		अगर (adev->pdev->subप्रणाली_venकरोr == 0x106B) अणु
			min = 1000;
			max = 2300;
		पूर्ण अन्यथा अणु
			अगर (evv_revision == 0) अणु
				min = 1000;
				max = 2300;
			पूर्ण अन्यथा अगर (evv_revision == 1) अणु
				अगर (asicrev1 == 326) अणु
					min = 1200;
					max = 2500;
					/* TODO: PATCH RO in VBIOS */
				पूर्ण अन्यथा अणु
					min = 1200;
					max = 2000;
				पूर्ण
			पूर्ण अन्यथा अगर (evv_revision == 2) अणु
				min = 1200;
				max = 2500;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		min = 1100;
		max = 2100;
	पूर्ण

	data->ro_range_minimum = min;
	data->ro_range_maximum = max;

	/* TODO: PATCH RO in VBIOS here */

	वापस 0;
पूर्ण

/**
 * smu7_get_evv_voltages - Get Leakage VDDC based on leakage ID.
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Return:   always 0
 */
अटल पूर्णांक smu7_get_evv_voltages(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक16_t vv_id;
	uपूर्णांक16_t vddc = 0;
	uपूर्णांक16_t vddgfx = 0;
	uपूर्णांक16_t i, j;
	uपूर्णांक32_t sclk = 0;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)hwmgr->pptable;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *sclk_table = शून्य;

	अगर (hwmgr->chip_id == CHIP_POLARIS10 ||
	    hwmgr->chip_id == CHIP_POLARIS11 ||
	    hwmgr->chip_id == CHIP_POLARIS12)
		smu7_calculate_ro_range(hwmgr);

	क्रम (i = 0; i < SMU7_MAX_LEAKAGE_COUNT; i++) अणु
		vv_id = ATOM_VIRTUAL_VOLTAGE_ID0 + i;

		अगर (data->vdd_gfx_control == SMU7_VOLTAGE_CONTROL_BY_SVID2) अणु
			अगर ((hwmgr->pp_table_version == PP_TABLE_V1)
			    && !phm_get_sclk_क्रम_voltage_evv(hwmgr,
						table_info->vddgfx_lookup_table, vv_id, &sclk)) अणु
				अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
							PHM_Platक्रमmCaps_ClockStretcher)) अणु
					sclk_table = table_info->vdd_dep_on_sclk;

					क्रम (j = 1; j < sclk_table->count; j++) अणु
						अगर (sclk_table->entries[j].clk == sclk &&
								sclk_table->entries[j].cks_enable == 0) अणु
							sclk += 5000;
							अवरोध;
						पूर्ण
					पूर्ण
				पूर्ण
				अगर (0 == atomctrl_get_voltage_evv_on_sclk
				    (hwmgr, VOLTAGE_TYPE_VDDGFX, sclk,
				     vv_id, &vddgfx)) अणु
					/* need to make sure vddgfx is less than 2v or अन्यथा, it could burn the ASIC. */
					PP_ASSERT_WITH_CODE((vddgfx < 2000 && vddgfx != 0), "Invalid VDDGFX value!", वापस -EINVAL);

					/* the voltage should not be zero nor equal to leakage ID */
					अगर (vddgfx != 0 && vddgfx != vv_id) अणु
						data->vddcgfx_leakage.actual_voltage[data->vddcgfx_leakage.count] = vddgfx;
						data->vddcgfx_leakage.leakage_id[data->vddcgfx_leakage.count] = vv_id;
						data->vddcgfx_leakage.count++;
					पूर्ण
				पूर्ण अन्यथा अणु
					pr_info("Error retrieving EVV voltage value!\n");
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ((hwmgr->pp_table_version == PP_TABLE_V0)
				|| !phm_get_sclk_क्रम_voltage_evv(hwmgr,
					table_info->vddc_lookup_table, vv_id, &sclk)) अणु
				अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
						PHM_Platक्रमmCaps_ClockStretcher)) अणु
					अगर (table_info == शून्य)
						वापस -EINVAL;
					sclk_table = table_info->vdd_dep_on_sclk;

					क्रम (j = 1; j < sclk_table->count; j++) अणु
						अगर (sclk_table->entries[j].clk == sclk &&
								sclk_table->entries[j].cks_enable == 0) अणु
							sclk += 5000;
							अवरोध;
						पूर्ण
					पूर्ण
				पूर्ण

				अगर (phm_get_voltage_evv_on_sclk(hwmgr,
							VOLTAGE_TYPE_VDDC,
							sclk, vv_id, &vddc) == 0) अणु
					अगर (vddc >= 2000 || vddc == 0)
						वापस -EINVAL;
				पूर्ण अन्यथा अणु
					pr_debug("failed to retrieving EVV voltage!\n");
					जारी;
				पूर्ण

				/* the voltage should not be zero nor equal to leakage ID */
				अगर (vddc != 0 && vddc != vv_id) अणु
					data->vddc_leakage.actual_voltage[data->vddc_leakage.count] = (uपूर्णांक16_t)(vddc);
					data->vddc_leakage.leakage_id[data->vddc_leakage.count] = vv_id;
					data->vddc_leakage.count++;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * smu7_patch_ppt_v1_with_vdd_leakage - Change भव leakage voltage to actual value.
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * @voltage: poपूर्णांकer to changing voltage
 * @leakage_table: poपूर्णांकer to leakage table
 */
अटल व्योम smu7_patch_ppt_v1_with_vdd_leakage(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक16_t *voltage, काष्ठा smu7_leakage_voltage *leakage_table)
अणु
	uपूर्णांक32_t index;

	/* search क्रम leakage voltage ID 0xff01 ~ 0xff08 */
	क्रम (index = 0; index < leakage_table->count; index++) अणु
		/* अगर this voltage matches a leakage voltage ID */
		/* patch with actual leakage voltage */
		अगर (leakage_table->leakage_id[index] == *voltage) अणु
			*voltage = leakage_table->actual_voltage[index];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (*voltage > ATOM_VIRTUAL_VOLTAGE_ID0)
		pr_err("Voltage value looks like a Leakage ID but it's not patched \n");
पूर्ण

/**
 * smu7_patch_lookup_table_with_leakage - Patch voltage lookup table by EVV leakages.
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * @lookup_table: poपूर्णांकer to voltage lookup table
 * @leakage_table: poपूर्णांकer to leakage table
 * Return:     always 0
 */
अटल पूर्णांक smu7_patch_lookup_table_with_leakage(काष्ठा pp_hwmgr *hwmgr,
		phm_ppt_v1_voltage_lookup_table *lookup_table,
		काष्ठा smu7_leakage_voltage *leakage_table)
अणु
	uपूर्णांक32_t i;

	क्रम (i = 0; i < lookup_table->count; i++)
		smu7_patch_ppt_v1_with_vdd_leakage(hwmgr,
				&lookup_table->entries[i].us_vdd, leakage_table);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_patch_घड़ी_voltage_limits_with_vddc_leakage(
		काष्ठा pp_hwmgr *hwmgr, काष्ठा smu7_leakage_voltage *leakage_table,
		uपूर्णांक16_t *vddc)
अणु
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	smu7_patch_ppt_v1_with_vdd_leakage(hwmgr, (uपूर्णांक16_t *)vddc, leakage_table);
	hwmgr->dyn_state.max_घड़ी_voltage_on_dc.vddc =
			table_info->max_घड़ी_voltage_on_dc.vddc;
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_patch_voltage_dependency_tables_with_lookup_table(
		काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक8_t entry_id;
	uपूर्णांक8_t voltage_id;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *sclk_table =
			table_info->vdd_dep_on_sclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *mclk_table =
			table_info->vdd_dep_on_mclk;
	काष्ठा phm_ppt_v1_mm_घड़ी_voltage_dependency_table *mm_table =
			table_info->mm_dep_table;

	अगर (data->vdd_gfx_control == SMU7_VOLTAGE_CONTROL_BY_SVID2) अणु
		क्रम (entry_id = 0; entry_id < sclk_table->count; ++entry_id) अणु
			voltage_id = sclk_table->entries[entry_id].vddInd;
			sclk_table->entries[entry_id].vddgfx =
				table_info->vddgfx_lookup_table->entries[voltage_id].us_vdd;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (entry_id = 0; entry_id < sclk_table->count; ++entry_id) अणु
			voltage_id = sclk_table->entries[entry_id].vddInd;
			sclk_table->entries[entry_id].vddc =
				table_info->vddc_lookup_table->entries[voltage_id].us_vdd;
		पूर्ण
	पूर्ण

	क्रम (entry_id = 0; entry_id < mclk_table->count; ++entry_id) अणु
		voltage_id = mclk_table->entries[entry_id].vddInd;
		mclk_table->entries[entry_id].vddc =
			table_info->vddc_lookup_table->entries[voltage_id].us_vdd;
	पूर्ण

	क्रम (entry_id = 0; entry_id < mm_table->count; ++entry_id) अणु
		voltage_id = mm_table->entries[entry_id].vddcInd;
		mm_table->entries[entry_id].vddc =
			table_info->vddc_lookup_table->entries[voltage_id].us_vdd;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक phm_add_voltage(काष्ठा pp_hwmgr *hwmgr,
			phm_ppt_v1_voltage_lookup_table *look_up_table,
			phm_ppt_v1_voltage_lookup_record *record)
अणु
	uपूर्णांक32_t i;

	PP_ASSERT_WITH_CODE((शून्य != look_up_table),
		"Lookup Table empty.", वापस -EINVAL);
	PP_ASSERT_WITH_CODE((0 != look_up_table->count),
		"Lookup Table empty.", वापस -EINVAL);

	i = smum_get_mac_definition(hwmgr, SMU_MAX_LEVELS_VDDGFX);
	PP_ASSERT_WITH_CODE((i >= look_up_table->count),
		"Lookup Table is full.", वापस -EINVAL);

	/* This is to aव्योम entering duplicate calculated records. */
	क्रम (i = 0; i < look_up_table->count; i++) अणु
		अगर (look_up_table->entries[i].us_vdd == record->us_vdd) अणु
			अगर (look_up_table->entries[i].us_calculated == 1)
				वापस 0;
			अवरोध;
		पूर्ण
	पूर्ण

	look_up_table->entries[i].us_calculated = 1;
	look_up_table->entries[i].us_vdd = record->us_vdd;
	look_up_table->entries[i].us_cac_low = record->us_cac_low;
	look_up_table->entries[i].us_cac_mid = record->us_cac_mid;
	look_up_table->entries[i].us_cac_high = record->us_cac_high;
	/* Only increment the count when we're appending, not replacing duplicate entry. */
	अगर (i == look_up_table->count)
		look_up_table->count++;

	वापस 0;
पूर्ण


अटल पूर्णांक smu7_calc_voltage_dependency_tables(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक8_t entry_id;
	काष्ठा phm_ppt_v1_voltage_lookup_record v_record;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *pptable_info = (काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	phm_ppt_v1_घड़ी_voltage_dependency_table *sclk_table = pptable_info->vdd_dep_on_sclk;
	phm_ppt_v1_घड़ी_voltage_dependency_table *mclk_table = pptable_info->vdd_dep_on_mclk;

	अगर (data->vdd_gfx_control == SMU7_VOLTAGE_CONTROL_BY_SVID2) अणु
		क्रम (entry_id = 0; entry_id < sclk_table->count; ++entry_id) अणु
			अगर (sclk_table->entries[entry_id].vdd_offset & (1 << 15))
				v_record.us_vdd = sclk_table->entries[entry_id].vddgfx +
					sclk_table->entries[entry_id].vdd_offset - 0xFFFF;
			अन्यथा
				v_record.us_vdd = sclk_table->entries[entry_id].vddgfx +
					sclk_table->entries[entry_id].vdd_offset;

			sclk_table->entries[entry_id].vddc =
				v_record.us_cac_low = v_record.us_cac_mid =
				v_record.us_cac_high = v_record.us_vdd;

			phm_add_voltage(hwmgr, pptable_info->vddc_lookup_table, &v_record);
		पूर्ण

		क्रम (entry_id = 0; entry_id < mclk_table->count; ++entry_id) अणु
			अगर (mclk_table->entries[entry_id].vdd_offset & (1 << 15))
				v_record.us_vdd = mclk_table->entries[entry_id].vddc +
					mclk_table->entries[entry_id].vdd_offset - 0xFFFF;
			अन्यथा
				v_record.us_vdd = mclk_table->entries[entry_id].vddc +
					mclk_table->entries[entry_id].vdd_offset;

			mclk_table->entries[entry_id].vddgfx = v_record.us_cac_low =
				v_record.us_cac_mid = v_record.us_cac_high = v_record.us_vdd;
			phm_add_voltage(hwmgr, pptable_info->vddgfx_lookup_table, &v_record);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_calc_mm_voltage_dependency_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक8_t entry_id;
	काष्ठा phm_ppt_v1_voltage_lookup_record v_record;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *pptable_info = (काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	phm_ppt_v1_mm_घड़ी_voltage_dependency_table *mm_table = pptable_info->mm_dep_table;

	अगर (data->vdd_gfx_control == SMU7_VOLTAGE_CONTROL_BY_SVID2) अणु
		क्रम (entry_id = 0; entry_id < mm_table->count; entry_id++) अणु
			अगर (mm_table->entries[entry_id].vddgfx_offset & (1 << 15))
				v_record.us_vdd = mm_table->entries[entry_id].vddc +
					mm_table->entries[entry_id].vddgfx_offset - 0xFFFF;
			अन्यथा
				v_record.us_vdd = mm_table->entries[entry_id].vddc +
					mm_table->entries[entry_id].vddgfx_offset;

			/* Add the calculated VDDGFX to the VDDGFX lookup table */
			mm_table->entries[entry_id].vddgfx = v_record.us_cac_low =
				v_record.us_cac_mid = v_record.us_cac_high = v_record.us_vdd;
			phm_add_voltage(hwmgr, pptable_info->vddgfx_lookup_table, &v_record);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_sort_lookup_table(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_ppt_v1_voltage_lookup_table *lookup_table)
अणु
	uपूर्णांक32_t table_size, i, j;
	table_size = lookup_table->count;

	PP_ASSERT_WITH_CODE(0 != lookup_table->count,
		"Lookup table is empty", वापस -EINVAL);

	/* Sorting voltages */
	क्रम (i = 0; i < table_size - 1; i++) अणु
		क्रम (j = i + 1; j > 0; j--) अणु
			अगर (lookup_table->entries[j].us_vdd <
					lookup_table->entries[j - 1].us_vdd) अणु
				swap(lookup_table->entries[j - 1],
				     lookup_table->entries[j]);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_complete_dependency_tables(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;
	पूर्णांक पंचांगp_result;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	अगर (data->vdd_gfx_control == SMU7_VOLTAGE_CONTROL_BY_SVID2) अणु
		पंचांगp_result = smu7_patch_lookup_table_with_leakage(hwmgr,
			table_info->vddgfx_lookup_table, &(data->vddcgfx_leakage));
		अगर (पंचांगp_result != 0)
			result = पंचांगp_result;

		smu7_patch_ppt_v1_with_vdd_leakage(hwmgr,
			&table_info->max_घड़ी_voltage_on_dc.vddgfx, &(data->vddcgfx_leakage));
	पूर्ण अन्यथा अणु

		पंचांगp_result = smu7_patch_lookup_table_with_leakage(hwmgr,
				table_info->vddc_lookup_table, &(data->vddc_leakage));
		अगर (पंचांगp_result)
			result = पंचांगp_result;

		पंचांगp_result = smu7_patch_घड़ी_voltage_limits_with_vddc_leakage(hwmgr,
				&(data->vddc_leakage), &table_info->max_घड़ी_voltage_on_dc.vddc);
		अगर (पंचांगp_result)
			result = पंचांगp_result;
	पूर्ण

	पंचांगp_result = smu7_patch_voltage_dependency_tables_with_lookup_table(hwmgr);
	अगर (पंचांगp_result)
		result = पंचांगp_result;

	पंचांगp_result = smu7_calc_voltage_dependency_tables(hwmgr);
	अगर (पंचांगp_result)
		result = पंचांगp_result;

	पंचांगp_result = smu7_calc_mm_voltage_dependency_table(hwmgr);
	अगर (पंचांगp_result)
		result = पंचांगp_result;

	पंचांगp_result = smu7_sort_lookup_table(hwmgr, table_info->vddgfx_lookup_table);
	अगर (पंचांगp_result)
		result = पंचांगp_result;

	पंचांगp_result = smu7_sort_lookup_table(hwmgr, table_info->vddc_lookup_table);
	अगर (पंचांगp_result)
		result = पंचांगp_result;

	वापस result;
पूर्ण

अटल पूर्णांक smu7_find_highest_vddc(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *allowed_sclk_vdd_table =
						table_info->vdd_dep_on_sclk;
	काष्ठा phm_ppt_v1_voltage_lookup_table *lookup_table =
						table_info->vddc_lookup_table;
	uपूर्णांक16_t highest_voltage;
	uपूर्णांक32_t i;

	highest_voltage = allowed_sclk_vdd_table->entries[allowed_sclk_vdd_table->count - 1].vddc;

	क्रम (i = 0; i < lookup_table->count; i++) अणु
		अगर (lookup_table->entries[i].us_vdd < ATOM_VIRTUAL_VOLTAGE_ID0 &&
		    lookup_table->entries[i].us_vdd > highest_voltage)
			highest_voltage = lookup_table->entries[i].us_vdd;
	पूर्ण

	वापस highest_voltage;
पूर्ण

अटल पूर्णांक smu7_set_निजी_data_based_on_pptable_v1(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *allowed_sclk_vdd_table =
						table_info->vdd_dep_on_sclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *allowed_mclk_vdd_table =
						table_info->vdd_dep_on_mclk;

	PP_ASSERT_WITH_CODE(allowed_sclk_vdd_table != शून्य,
		"VDD dependency on SCLK table is missing.",
		वापस -EINVAL);
	PP_ASSERT_WITH_CODE(allowed_sclk_vdd_table->count >= 1,
		"VDD dependency on SCLK table has to have is missing.",
		वापस -EINVAL);

	PP_ASSERT_WITH_CODE(allowed_mclk_vdd_table != शून्य,
		"VDD dependency on MCLK table is missing",
		वापस -EINVAL);
	PP_ASSERT_WITH_CODE(allowed_mclk_vdd_table->count >= 1,
		"VDD dependency on MCLK table has to have is missing.",
		वापस -EINVAL);

	table_info->max_घड़ी_voltage_on_ac.sclk =
		allowed_sclk_vdd_table->entries[allowed_sclk_vdd_table->count - 1].clk;
	table_info->max_घड़ी_voltage_on_ac.mclk =
		allowed_mclk_vdd_table->entries[allowed_mclk_vdd_table->count - 1].clk;
	अगर (hwmgr->chip_id >= CHIP_POLARIS10 && hwmgr->chip_id <= CHIP_VEGAM)
		table_info->max_घड़ी_voltage_on_ac.vddc =
			smu7_find_highest_vddc(hwmgr);
	अन्यथा
		table_info->max_घड़ी_voltage_on_ac.vddc =
			allowed_sclk_vdd_table->entries[allowed_sclk_vdd_table->count - 1].vddc;
	table_info->max_घड़ी_voltage_on_ac.vddci =
		allowed_mclk_vdd_table->entries[allowed_mclk_vdd_table->count - 1].vddci;

	hwmgr->dyn_state.max_घड़ी_voltage_on_ac.sclk = table_info->max_घड़ी_voltage_on_ac.sclk;
	hwmgr->dyn_state.max_घड़ी_voltage_on_ac.mclk = table_info->max_घड़ी_voltage_on_ac.mclk;
	hwmgr->dyn_state.max_घड़ी_voltage_on_ac.vddc = table_info->max_घड़ी_voltage_on_ac.vddc;
	hwmgr->dyn_state.max_घड़ी_voltage_on_ac.vddci = table_info->max_घड़ी_voltage_on_ac.vddci;

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_patch_voltage_workaround(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
		       (काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_mclk_table;
	काष्ठा phm_ppt_v1_voltage_lookup_table *lookup_table;
	uपूर्णांक32_t i;
	uपूर्णांक32_t hw_revision, sub_venकरोr_id, sub_sys_id;
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	अगर (table_info != शून्य) अणु
		dep_mclk_table = table_info->vdd_dep_on_mclk;
		lookup_table = table_info->vddc_lookup_table;
	पूर्ण अन्यथा
		वापस 0;

	hw_revision = adev->pdev->revision;
	sub_sys_id = adev->pdev->subप्रणाली_device;
	sub_venकरोr_id = adev->pdev->subप्रणाली_venकरोr;

	अगर (adev->pdev->device == 0x67DF && hw_revision == 0xC7 &&
	    ((sub_sys_id == 0xb37 && sub_venकरोr_id == 0x1002) ||
	     (sub_sys_id == 0x4a8 && sub_venकरोr_id == 0x1043) ||
	     (sub_sys_id == 0x9480 && sub_venकरोr_id == 0x1682))) अणु

		PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device,
					      CGS_IND_REG__SMC,
					      PWR_CKS_CNTL,
					      CKS_STRETCH_AMOUNT,
					      0x3);

		अगर (lookup_table->entries[dep_mclk_table->entries[dep_mclk_table->count-1].vddInd].us_vdd >= 1000)
			वापस 0;

		क्रम (i = 0; i < lookup_table->count; i++) अणु
			अगर (lookup_table->entries[i].us_vdd < 0xff01 && lookup_table->entries[i].us_vdd >= 1000) अणु
				dep_mclk_table->entries[dep_mclk_table->count-1].vddInd = (uपूर्णांक8_t) i;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_thermal_parameter_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा pp_atomctrl_gpio_pin_assignment gpio_pin_assignment;
	uपूर्णांक32_t temp_reg;
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);


	अगर (atomctrl_get_pp_assign_pin(hwmgr, VDDC_PCC_GPIO_PINID, &gpio_pin_assignment)) अणु
		temp_reg = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixCNB_PWRMGT_CNTL);
		चयन (gpio_pin_assignment.uc_gpio_pin_bit_shअगरt) अणु
		हाल 0:
			temp_reg = PHM_SET_FIELD(temp_reg, CNB_PWRMGT_CNTL, GNB_SLOW_MODE, 0x1);
			अवरोध;
		हाल 1:
			temp_reg = PHM_SET_FIELD(temp_reg, CNB_PWRMGT_CNTL, GNB_SLOW_MODE, 0x2);
			अवरोध;
		हाल 2:
			temp_reg = PHM_SET_FIELD(temp_reg, CNB_PWRMGT_CNTL, GNB_SLOW, 0x1);
			अवरोध;
		हाल 3:
			temp_reg = PHM_SET_FIELD(temp_reg, CNB_PWRMGT_CNTL, FORCE_NB_PS1, 0x1);
			अवरोध;
		हाल 4:
			temp_reg = PHM_SET_FIELD(temp_reg, CNB_PWRMGT_CNTL, DPM_ENABLED, 0x1);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixCNB_PWRMGT_CNTL, temp_reg);
	पूर्ण

	अगर (table_info == शून्य)
		वापस 0;

	अगर (table_info->cac_dtp_table->usDefaultTargetOperatingTemp != 0 &&
		hwmgr->thermal_controller.advanceFanControlParameters.ucFanControlMode) अणु
		hwmgr->thermal_controller.advanceFanControlParameters.usFanPWMMinLimit =
			(uपूर्णांक16_t)hwmgr->thermal_controller.advanceFanControlParameters.ucMinimumPWMLimit;

		hwmgr->thermal_controller.advanceFanControlParameters.usFanPWMMaxLimit =
			(uपूर्णांक16_t)hwmgr->thermal_controller.advanceFanControlParameters.usDefaultMaxFanPWM;

		hwmgr->thermal_controller.advanceFanControlParameters.usFanPWMStep = 1;

		hwmgr->thermal_controller.advanceFanControlParameters.usFanRPMMaxLimit = 100;

		hwmgr->thermal_controller.advanceFanControlParameters.usFanRPMMinLimit =
			(uपूर्णांक16_t)hwmgr->thermal_controller.advanceFanControlParameters.ucMinimumPWMLimit;

		hwmgr->thermal_controller.advanceFanControlParameters.usFanRPMStep = 1;

		table_info->cac_dtp_table->usDefaultTargetOperatingTemp = (table_info->cac_dtp_table->usDefaultTargetOperatingTemp >= 50) ?
								(table_info->cac_dtp_table->usDefaultTargetOperatingTemp - 50) : 0;

		table_info->cac_dtp_table->usOperatingTempMaxLimit = table_info->cac_dtp_table->usDefaultTargetOperatingTemp;
		table_info->cac_dtp_table->usOperatingTempStep = 1;
		table_info->cac_dtp_table->usOperatingTempHyst = 1;

		hwmgr->thermal_controller.advanceFanControlParameters.usMaxFanPWM =
			       hwmgr->thermal_controller.advanceFanControlParameters.usDefaultMaxFanPWM;

		hwmgr->thermal_controller.advanceFanControlParameters.usMaxFanRPM =
			       hwmgr->thermal_controller.advanceFanControlParameters.usDefaultMaxFanRPM;

		hwmgr->dyn_state.cac_dtp_table->usOperatingTempMinLimit =
			       table_info->cac_dtp_table->usOperatingTempMinLimit;

		hwmgr->dyn_state.cac_dtp_table->usOperatingTempMaxLimit =
			       table_info->cac_dtp_table->usOperatingTempMaxLimit;

		hwmgr->dyn_state.cac_dtp_table->usDefaultTargetOperatingTemp =
			       table_info->cac_dtp_table->usDefaultTargetOperatingTemp;

		hwmgr->dyn_state.cac_dtp_table->usOperatingTempStep =
			       table_info->cac_dtp_table->usOperatingTempStep;

		hwmgr->dyn_state.cac_dtp_table->usTargetOperatingTemp =
			       table_info->cac_dtp_table->usTargetOperatingTemp;
		अगर (hwmgr->feature_mask & PP_OD_FUZZY_FAN_CONTROL_MASK)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_ODFuzzyFanControlSupport);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * smu7_patch_ppt_v0_with_vdd_leakage - Change भव leakage voltage to actual value.
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * @voltage: poपूर्णांकer to changing voltage
 * @leakage_table: poपूर्णांकer to leakage table
 */
अटल व्योम smu7_patch_ppt_v0_with_vdd_leakage(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t *voltage, काष्ठा smu7_leakage_voltage *leakage_table)
अणु
	uपूर्णांक32_t index;

	/* search क्रम leakage voltage ID 0xff01 ~ 0xff08 */
	क्रम (index = 0; index < leakage_table->count; index++) अणु
		/* अगर this voltage matches a leakage voltage ID */
		/* patch with actual leakage voltage */
		अगर (leakage_table->leakage_id[index] == *voltage) अणु
			*voltage = leakage_table->actual_voltage[index];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (*voltage > ATOM_VIRTUAL_VOLTAGE_ID0)
		pr_err("Voltage value looks like a Leakage ID but it's not patched \n");
पूर्ण


अटल पूर्णांक smu7_patch_vddc(काष्ठा pp_hwmgr *hwmgr,
			      काष्ठा phm_घड़ी_voltage_dependency_table *tab)
अणु
	uपूर्णांक16_t i;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (tab)
		क्रम (i = 0; i < tab->count; i++)
			smu7_patch_ppt_v0_with_vdd_leakage(hwmgr, &tab->entries[i].v,
						&data->vddc_leakage);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_patch_vddci(काष्ठा pp_hwmgr *hwmgr,
			       काष्ठा phm_घड़ी_voltage_dependency_table *tab)
अणु
	uपूर्णांक16_t i;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (tab)
		क्रम (i = 0; i < tab->count; i++)
			smu7_patch_ppt_v0_with_vdd_leakage(hwmgr, &tab->entries[i].v,
							&data->vddci_leakage);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_patch_vce_vddc(काष्ठा pp_hwmgr *hwmgr,
				  काष्ठा phm_vce_घड़ी_voltage_dependency_table *tab)
अणु
	uपूर्णांक16_t i;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (tab)
		क्रम (i = 0; i < tab->count; i++)
			smu7_patch_ppt_v0_with_vdd_leakage(hwmgr, &tab->entries[i].v,
							&data->vddc_leakage);

	वापस 0;
पूर्ण


अटल पूर्णांक smu7_patch_uvd_vddc(काष्ठा pp_hwmgr *hwmgr,
				  काष्ठा phm_uvd_घड़ी_voltage_dependency_table *tab)
अणु
	uपूर्णांक16_t i;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (tab)
		क्रम (i = 0; i < tab->count; i++)
			smu7_patch_ppt_v0_with_vdd_leakage(hwmgr, &tab->entries[i].v,
							&data->vddc_leakage);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_patch_vddc_shed_limit(काष्ठा pp_hwmgr *hwmgr,
					 काष्ठा phm_phase_shedding_limits_table *tab)
अणु
	uपूर्णांक16_t i;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (tab)
		क्रम (i = 0; i < tab->count; i++)
			smu7_patch_ppt_v0_with_vdd_leakage(hwmgr, &tab->entries[i].Voltage,
							&data->vddc_leakage);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_patch_samu_vddc(काष्ठा pp_hwmgr *hwmgr,
				   काष्ठा phm_samu_घड़ी_voltage_dependency_table *tab)
अणु
	uपूर्णांक16_t i;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (tab)
		क्रम (i = 0; i < tab->count; i++)
			smu7_patch_ppt_v0_with_vdd_leakage(hwmgr, &tab->entries[i].v,
							&data->vddc_leakage);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_patch_acp_vddc(काष्ठा pp_hwmgr *hwmgr,
				  काष्ठा phm_acp_घड़ी_voltage_dependency_table *tab)
अणु
	uपूर्णांक16_t i;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (tab)
		क्रम (i = 0; i < tab->count; i++)
			smu7_patch_ppt_v0_with_vdd_leakage(hwmgr, &tab->entries[i].v,
					&data->vddc_leakage);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_patch_limits_vddc(काष्ठा pp_hwmgr *hwmgr,
				  काष्ठा phm_घड़ी_and_voltage_limits *tab)
अणु
	uपूर्णांक32_t vddc, vddci;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (tab) अणु
		vddc = tab->vddc;
		smu7_patch_ppt_v0_with_vdd_leakage(hwmgr, &vddc,
						   &data->vddc_leakage);
		tab->vddc = vddc;
		vddci = tab->vddci;
		smu7_patch_ppt_v0_with_vdd_leakage(hwmgr, &vddci,
						   &data->vddci_leakage);
		tab->vddci = vddci;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_patch_cac_vddc(काष्ठा pp_hwmgr *hwmgr, काष्ठा phm_cac_leakage_table *tab)
अणु
	uपूर्णांक32_t i;
	uपूर्णांक32_t vddc;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (tab) अणु
		क्रम (i = 0; i < tab->count; i++) अणु
			vddc = (uपूर्णांक32_t)(tab->entries[i].Vddc);
			smu7_patch_ppt_v0_with_vdd_leakage(hwmgr, &vddc, &data->vddc_leakage);
			tab->entries[i].Vddc = (uपूर्णांक16_t)vddc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_patch_dependency_tables_with_leakage(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक पंचांगp;

	पंचांगp = smu7_patch_vddc(hwmgr, hwmgr->dyn_state.vddc_dependency_on_sclk);
	अगर (पंचांगp)
		वापस -EINVAL;

	पंचांगp = smu7_patch_vddc(hwmgr, hwmgr->dyn_state.vddc_dependency_on_mclk);
	अगर (पंचांगp)
		वापस -EINVAL;

	पंचांगp = smu7_patch_vddc(hwmgr, hwmgr->dyn_state.vddc_dep_on_dal_pwrl);
	अगर (पंचांगp)
		वापस -EINVAL;

	पंचांगp = smu7_patch_vddci(hwmgr, hwmgr->dyn_state.vddci_dependency_on_mclk);
	अगर (पंचांगp)
		वापस -EINVAL;

	पंचांगp = smu7_patch_vce_vddc(hwmgr, hwmgr->dyn_state.vce_घड़ी_voltage_dependency_table);
	अगर (पंचांगp)
		वापस -EINVAL;

	पंचांगp = smu7_patch_uvd_vddc(hwmgr, hwmgr->dyn_state.uvd_घड़ी_voltage_dependency_table);
	अगर (पंचांगp)
		वापस -EINVAL;

	पंचांगp = smu7_patch_samu_vddc(hwmgr, hwmgr->dyn_state.samu_घड़ी_voltage_dependency_table);
	अगर (पंचांगp)
		वापस -EINVAL;

	पंचांगp = smu7_patch_acp_vddc(hwmgr, hwmgr->dyn_state.acp_घड़ी_voltage_dependency_table);
	अगर (पंचांगp)
		वापस -EINVAL;

	पंचांगp = smu7_patch_vddc_shed_limit(hwmgr, hwmgr->dyn_state.vddc_phase_shed_limits_table);
	अगर (पंचांगp)
		वापस -EINVAL;

	पंचांगp = smu7_patch_limits_vddc(hwmgr, &hwmgr->dyn_state.max_घड़ी_voltage_on_ac);
	अगर (पंचांगp)
		वापस -EINVAL;

	पंचांगp = smu7_patch_limits_vddc(hwmgr, &hwmgr->dyn_state.max_घड़ी_voltage_on_dc);
	अगर (पंचांगp)
		वापस -EINVAL;

	पंचांगp = smu7_patch_cac_vddc(hwmgr, hwmgr->dyn_state.cac_leakage_table);
	अगर (पंचांगp)
		वापस -EINVAL;

	वापस 0;
पूर्ण


अटल पूर्णांक smu7_set_निजी_data_based_on_pptable_v0(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	काष्ठा phm_घड़ी_voltage_dependency_table *allowed_sclk_vddc_table = hwmgr->dyn_state.vddc_dependency_on_sclk;
	काष्ठा phm_घड़ी_voltage_dependency_table *allowed_mclk_vddc_table = hwmgr->dyn_state.vddc_dependency_on_mclk;
	काष्ठा phm_घड़ी_voltage_dependency_table *allowed_mclk_vddci_table = hwmgr->dyn_state.vddci_dependency_on_mclk;

	PP_ASSERT_WITH_CODE(allowed_sclk_vddc_table != शून्य,
		"VDDC dependency on SCLK table is missing. This table is mandatory",
		वापस -EINVAL);
	PP_ASSERT_WITH_CODE(allowed_sclk_vddc_table->count >= 1,
		"VDDC dependency on SCLK table has to have is missing. This table is mandatory",
		वापस -EINVAL);

	PP_ASSERT_WITH_CODE(allowed_mclk_vddc_table != शून्य,
		"VDDC dependency on MCLK table is missing. This table is mandatory",
		वापस -EINVAL);
	PP_ASSERT_WITH_CODE(allowed_mclk_vddc_table->count >= 1,
		"VDD dependency on MCLK table has to have is missing. This table is mandatory",
		वापस -EINVAL);

	data->min_vddc_in_pptable = (uपूर्णांक16_t)allowed_sclk_vddc_table->entries[0].v;
	data->max_vddc_in_pptable = (uपूर्णांक16_t)allowed_sclk_vddc_table->entries[allowed_sclk_vddc_table->count - 1].v;

	hwmgr->dyn_state.max_घड़ी_voltage_on_ac.sclk =
		allowed_sclk_vddc_table->entries[allowed_sclk_vddc_table->count - 1].clk;
	hwmgr->dyn_state.max_घड़ी_voltage_on_ac.mclk =
		allowed_mclk_vddc_table->entries[allowed_mclk_vddc_table->count - 1].clk;
	hwmgr->dyn_state.max_घड़ी_voltage_on_ac.vddc =
		allowed_sclk_vddc_table->entries[allowed_sclk_vddc_table->count - 1].v;

	अगर (allowed_mclk_vddci_table != शून्य && allowed_mclk_vddci_table->count >= 1) अणु
		data->min_vddci_in_pptable = (uपूर्णांक16_t)allowed_mclk_vddci_table->entries[0].v;
		data->max_vddci_in_pptable = (uपूर्णांक16_t)allowed_mclk_vddci_table->entries[allowed_mclk_vddci_table->count - 1].v;
	पूर्ण

	अगर (hwmgr->dyn_state.vddci_dependency_on_mclk != शून्य && hwmgr->dyn_state.vddci_dependency_on_mclk->count >= 1)
		hwmgr->dyn_state.max_घड़ी_voltage_on_ac.vddci = hwmgr->dyn_state.vddci_dependency_on_mclk->entries[hwmgr->dyn_state.vddci_dependency_on_mclk->count - 1].v;

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_hwmgr_backend_fini(काष्ठा pp_hwmgr *hwmgr)
अणु
	kमुक्त(hwmgr->dyn_state.vddc_dep_on_dal_pwrl);
	hwmgr->dyn_state.vddc_dep_on_dal_pwrl = शून्य;
	kमुक्त(hwmgr->backend);
	hwmgr->backend = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_elb_voltages(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक16_t भव_voltage_id, vddc, vddci, efuse_voltage_id;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	पूर्णांक i;

	अगर (atomctrl_get_leakage_id_from_efuse(hwmgr, &efuse_voltage_id) == 0) अणु
		क्रम (i = 0; i < SMU7_MAX_LEAKAGE_COUNT; i++) अणु
			भव_voltage_id = ATOM_VIRTUAL_VOLTAGE_ID0 + i;
			अगर (atomctrl_get_leakage_vddc_base_on_leakage(hwmgr, &vddc, &vddci,
								भव_voltage_id,
								efuse_voltage_id) == 0) अणु
				अगर (vddc != 0 && vddc != भव_voltage_id) अणु
					data->vddc_leakage.actual_voltage[data->vddc_leakage.count] = vddc;
					data->vddc_leakage.leakage_id[data->vddc_leakage.count] = भव_voltage_id;
					data->vddc_leakage.count++;
				पूर्ण
				अगर (vddci != 0 && vddci != भव_voltage_id) अणु
					data->vddci_leakage.actual_voltage[data->vddci_leakage.count] = vddci;
					data->vddci_leakage.leakage_id[data->vddci_leakage.count] = भव_voltage_id;
					data->vddci_leakage.count++;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा LEAKAGE_ID_MSB			463
#घोषणा LEAKAGE_ID_LSB			454

अटल पूर्णांक smu7_update_edc_leakage_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t efuse;
	uपूर्णांक16_t offset;
	पूर्णांक ret = 0;

	अगर (data->disable_edc_leakage_controller)
		वापस 0;

	ret = atomctrl_get_edc_hilo_leakage_offset_table(hwmgr,
							 &data->edc_hilo_leakage_offset_from_vbios);
	अगर (ret)
		वापस ret;

	अगर (data->edc_hilo_leakage_offset_from_vbios.usEdcDidtLoDpm7TableOffset &&
	    data->edc_hilo_leakage_offset_from_vbios.usEdcDidtHiDpm7TableOffset) अणु
		atomctrl_पढ़ो_efuse(hwmgr, LEAKAGE_ID_LSB, LEAKAGE_ID_MSB, &efuse);
		अगर (efuse < data->edc_hilo_leakage_offset_from_vbios.usHiLoLeakageThreshold)
			offset = data->edc_hilo_leakage_offset_from_vbios.usEdcDidtLoDpm7TableOffset;
		अन्यथा
			offset = data->edc_hilo_leakage_offset_from_vbios.usEdcDidtHiDpm7TableOffset;

		ret = atomctrl_get_edc_leakage_table(hwmgr,
						     &data->edc_leakage_table,
						     offset);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक smu7_hwmgr_backend_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data;
	पूर्णांक result = 0;

	data = kzalloc(माप(काष्ठा smu7_hwmgr), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	hwmgr->backend = data;
	smu7_patch_voltage_workaround(hwmgr);
	smu7_init_dpm_शेषs(hwmgr);

	/* Get leakage voltage based on leakage ID. */
	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_EVV)) अणु
		result = smu7_get_evv_voltages(hwmgr);
		अगर (result) अणु
			pr_info("Get EVV Voltage Failed.  Abort Driver loading!\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		smu7_get_elb_voltages(hwmgr);
	पूर्ण

	अगर (hwmgr->pp_table_version == PP_TABLE_V1) अणु
		smu7_complete_dependency_tables(hwmgr);
		smu7_set_निजी_data_based_on_pptable_v1(hwmgr);
	पूर्ण अन्यथा अगर (hwmgr->pp_table_version == PP_TABLE_V0) अणु
		smu7_patch_dependency_tables_with_leakage(hwmgr);
		smu7_set_निजी_data_based_on_pptable_v0(hwmgr);
	पूर्ण

	/* Initalize Dynamic State Adjusपंचांगent Rule Settings */
	result = phm_initializa_dynamic_state_adjusपंचांगent_rule_settings(hwmgr);

	अगर (0 == result) अणु
		काष्ठा amdgpu_device *adev = hwmgr->adev;

		data->is_tlu_enabled = false;

		hwmgr->platक्रमm_descriptor.hardwareActivityPerक्रमmanceLevels =
							SMU7_MAX_HARDWARE_POWERLEVELS;
		hwmgr->platक्रमm_descriptor.hardwarePerक्रमmanceLevels = 2;
		hwmgr->platक्रमm_descriptor.minimumClocksReductionPercentage = 50;

		data->pcie_gen_cap = adev->pm.pcie_gen_mask;
		अगर (data->pcie_gen_cap & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3)
			data->pcie_spc_cap = 20;
		अन्यथा
			data->pcie_spc_cap = 16;
		data->pcie_lane_cap = adev->pm.pcie_mlw_mask;

		hwmgr->platक्रमm_descriptor.vbiosInterruptId = 0x20000400; /* IRQ_SOURCE1_SW_INT */
/* The true घड़ी step depends on the frequency, typically 4.5 or 9 MHz. Here we use 5. */
		hwmgr->platक्रमm_descriptor.घड़ीStep.engineClock = 500;
		hwmgr->platक्रमm_descriptor.घड़ीStep.memoryClock = 500;
		smu7_thermal_parameter_init(hwmgr);
	पूर्ण अन्यथा अणु
		/* Ignore वापस value in here, we are cleaning up a mess. */
		smu7_hwmgr_backend_fini(hwmgr);
	पूर्ण

	result = smu7_update_edc_leakage_table(hwmgr);
	अगर (result)
		वापस result;

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_क्रमce_dpm_highest(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t level, पंचांगp;

	अगर (!data->pcie_dpm_key_disabled) अणु
		अगर (data->dpm_level_enable_mask.pcie_dpm_enable_mask) अणु
			level = 0;
			पंचांगp = data->dpm_level_enable_mask.pcie_dpm_enable_mask;
			जबतक (पंचांगp >>= 1)
				level++;

			अगर (level)
				smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_PCIeDPM_ForceLevel, level,
						शून्य);
		पूर्ण
	पूर्ण

	अगर (!data->sclk_dpm_key_disabled) अणु
		अगर (data->dpm_level_enable_mask.sclk_dpm_enable_mask) अणु
			level = 0;
			पंचांगp = data->dpm_level_enable_mask.sclk_dpm_enable_mask;
			जबतक (पंचांगp >>= 1)
				level++;

			अगर (level)
				smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SCLKDPM_SetEnabledMask,
						(1 << level),
						शून्य);
		पूर्ण
	पूर्ण

	अगर (!data->mclk_dpm_key_disabled) अणु
		अगर (data->dpm_level_enable_mask.mclk_dpm_enable_mask) अणु
			level = 0;
			पंचांगp = data->dpm_level_enable_mask.mclk_dpm_enable_mask;
			जबतक (पंचांगp >>= 1)
				level++;

			अगर (level)
				smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_MCLKDPM_SetEnabledMask,
						(1 << level),
						शून्य);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_upload_dpm_level_enable_mask(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (hwmgr->pp_table_version == PP_TABLE_V1)
		phm_apply_dal_min_voltage_request(hwmgr);
/* TO DO  क्रम v0 iceland and Ci*/

	अगर (!data->sclk_dpm_key_disabled) अणु
		अगर (data->dpm_level_enable_mask.sclk_dpm_enable_mask)
			smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SCLKDPM_SetEnabledMask,
					data->dpm_level_enable_mask.sclk_dpm_enable_mask,
					शून्य);
	पूर्ण

	अगर (!data->mclk_dpm_key_disabled) अणु
		अगर (data->dpm_level_enable_mask.mclk_dpm_enable_mask)
			smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_MCLKDPM_SetEnabledMask,
					data->dpm_level_enable_mask.mclk_dpm_enable_mask,
					शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_unक्रमce_dpm_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (!smum_is_dpm_running(hwmgr))
		वापस -EINVAL;

	अगर (!data->pcie_dpm_key_disabled) अणु
		smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_PCIeDPM_UnForceLevel,
				शून्य);
	पूर्ण

	वापस smu7_upload_dpm_level_enable_mask(hwmgr);
पूर्ण

अटल पूर्णांक smu7_क्रमce_dpm_lowest(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data =
			(काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t level;

	अगर (!data->sclk_dpm_key_disabled)
		अगर (data->dpm_level_enable_mask.sclk_dpm_enable_mask) अणु
			level = phm_get_lowest_enabled_level(hwmgr,
							      data->dpm_level_enable_mask.sclk_dpm_enable_mask);
			smum_send_msg_to_smc_with_parameter(hwmgr,
							    PPSMC_MSG_SCLKDPM_SetEnabledMask,
							    (1 << level),
							    शून्य);

	पूर्ण

	अगर (!data->mclk_dpm_key_disabled) अणु
		अगर (data->dpm_level_enable_mask.mclk_dpm_enable_mask) अणु
			level = phm_get_lowest_enabled_level(hwmgr,
							      data->dpm_level_enable_mask.mclk_dpm_enable_mask);
			smum_send_msg_to_smc_with_parameter(hwmgr,
							    PPSMC_MSG_MCLKDPM_SetEnabledMask,
							    (1 << level),
							    शून्य);
		पूर्ण
	पूर्ण

	अगर (!data->pcie_dpm_key_disabled) अणु
		अगर (data->dpm_level_enable_mask.pcie_dpm_enable_mask) अणु
			level = phm_get_lowest_enabled_level(hwmgr,
							      data->dpm_level_enable_mask.pcie_dpm_enable_mask);
			smum_send_msg_to_smc_with_parameter(hwmgr,
							    PPSMC_MSG_PCIeDPM_ForceLevel,
							    (level),
							    शून्य);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_profiling_clk(काष्ठा pp_hwmgr *hwmgr, क्रमागत amd_dpm_क्रमced_level level,
				uपूर्णांक32_t *sclk_mask, uपूर्णांक32_t *mclk_mask, uपूर्णांक32_t *pcie_mask)
अणु
	uपूर्णांक32_t percentage;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_dpm_table *golden_dpm_table = &data->golden_dpm_table;
	पूर्णांक32_t पंचांगp_mclk;
	पूर्णांक32_t पंचांगp_sclk;
	पूर्णांक32_t count;

	अगर (golden_dpm_table->mclk_table.count < 1)
		वापस -EINVAL;

	percentage = 100 * golden_dpm_table->sclk_table.dpm_levels[golden_dpm_table->sclk_table.count - 1].value /
			golden_dpm_table->mclk_table.dpm_levels[golden_dpm_table->mclk_table.count - 1].value;

	अगर (golden_dpm_table->mclk_table.count == 1) अणु
		percentage = 70;
		पंचांगp_mclk = golden_dpm_table->mclk_table.dpm_levels[golden_dpm_table->mclk_table.count - 1].value;
		*mclk_mask = golden_dpm_table->mclk_table.count - 1;
	पूर्ण अन्यथा अणु
		पंचांगp_mclk = golden_dpm_table->mclk_table.dpm_levels[golden_dpm_table->mclk_table.count - 2].value;
		*mclk_mask = golden_dpm_table->mclk_table.count - 2;
	पूर्ण

	पंचांगp_sclk = पंचांगp_mclk * percentage / 100;

	अगर (hwmgr->pp_table_version == PP_TABLE_V0) अणु
		क्रम (count = hwmgr->dyn_state.vddc_dependency_on_sclk->count-1;
			count >= 0; count--) अणु
			अगर (पंचांगp_sclk >= hwmgr->dyn_state.vddc_dependency_on_sclk->entries[count].clk) अणु
				पंचांगp_sclk = hwmgr->dyn_state.vddc_dependency_on_sclk->entries[count].clk;
				*sclk_mask = count;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (count < 0 || level == AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK) अणु
			*sclk_mask = 0;
			पंचांगp_sclk = hwmgr->dyn_state.vddc_dependency_on_sclk->entries[0].clk;
		पूर्ण

		अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK)
			*sclk_mask = hwmgr->dyn_state.vddc_dependency_on_sclk->count-1;
	पूर्ण अन्यथा अगर (hwmgr->pp_table_version == PP_TABLE_V1) अणु
		काष्ठा phm_ppt_v1_inक्रमmation *table_info =
				(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

		क्रम (count = table_info->vdd_dep_on_sclk->count-1; count >= 0; count--) अणु
			अगर (पंचांगp_sclk >= table_info->vdd_dep_on_sclk->entries[count].clk) अणु
				पंचांगp_sclk = table_info->vdd_dep_on_sclk->entries[count].clk;
				*sclk_mask = count;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (count < 0 || level == AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK) अणु
			*sclk_mask = 0;
			पंचांगp_sclk =  table_info->vdd_dep_on_sclk->entries[0].clk;
		पूर्ण

		अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK)
			*sclk_mask = table_info->vdd_dep_on_sclk->count - 1;
	पूर्ण

	अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK)
		*mclk_mask = 0;
	अन्यथा अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK)
		*mclk_mask = golden_dpm_table->mclk_table.count - 1;

	*pcie_mask = data->dpm_table.pcie_speed_table.count - 1;
	hwmgr->pstate_sclk = पंचांगp_sclk;
	hwmgr->pstate_mclk = पंचांगp_mclk;

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_क्रमce_dpm_level(काष्ठा pp_hwmgr *hwmgr,
				क्रमागत amd_dpm_क्रमced_level level)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t sclk_mask = 0;
	uपूर्णांक32_t mclk_mask = 0;
	uपूर्णांक32_t pcie_mask = 0;

	अगर (hwmgr->pstate_sclk == 0)
		smu7_get_profiling_clk(hwmgr, level, &sclk_mask, &mclk_mask, &pcie_mask);

	चयन (level) अणु
	हाल AMD_DPM_FORCED_LEVEL_HIGH:
		ret = smu7_क्रमce_dpm_highest(hwmgr);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_LOW:
		ret = smu7_क्रमce_dpm_lowest(hwmgr);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_AUTO:
		ret = smu7_unक्रमce_dpm_levels(hwmgr);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_PEAK:
		ret = smu7_get_profiling_clk(hwmgr, level, &sclk_mask, &mclk_mask, &pcie_mask);
		अगर (ret)
			वापस ret;
		smu7_क्रमce_घड़ी_level(hwmgr, PP_SCLK, 1<<sclk_mask);
		smu7_क्रमce_घड़ी_level(hwmgr, PP_MCLK, 1<<mclk_mask);
		smu7_क्रमce_घड़ी_level(hwmgr, PP_PCIE, 1<<pcie_mask);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_MANUAL:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_EXIT:
	शेष:
		अवरोध;
	पूर्ण

	अगर (!ret) अणु
		अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK && hwmgr->dpm_level != AMD_DPM_FORCED_LEVEL_PROखाता_PEAK)
			smu7_fan_ctrl_set_fan_speed_percent(hwmgr, 100);
		अन्यथा अगर (level != AMD_DPM_FORCED_LEVEL_PROखाता_PEAK && hwmgr->dpm_level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK)
			smu7_fan_ctrl_reset_fan_speed_to_शेष(hwmgr);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक smu7_get_घातer_state_size(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस माप(काष्ठा smu7_घातer_state);
पूर्ण

अटल पूर्णांक smu7_vblank_too_लघु(काष्ठा pp_hwmgr *hwmgr,
				 uपूर्णांक32_t vblank_समय_us)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t चयन_limit_us;

	चयन (hwmgr->chip_id) अणु
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
		अगर (hwmgr->is_kicker || (hwmgr->chip_id == CHIP_POLARIS12))
			चयन_limit_us = data->is_memory_gddr5 ? 450 : 150;
		अन्यथा
			चयन_limit_us = data->is_memory_gddr5 ? 200 : 150;
		अवरोध;
	हाल CHIP_VEGAM:
		चयन_limit_us = 30;
		अवरोध;
	शेष:
		चयन_limit_us = data->is_memory_gddr5 ? 450 : 150;
		अवरोध;
	पूर्ण

	अगर (vblank_समय_us < चयन_limit_us)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक smu7_apply_state_adjust_rules(काष्ठा pp_hwmgr *hwmgr,
				काष्ठा pp_घातer_state *request_ps,
			स्थिर काष्ठा pp_घातer_state *current_ps)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	काष्ठा smu7_घातer_state *smu7_ps =
				cast_phw_smu7_घातer_state(&request_ps->hardware);
	uपूर्णांक32_t sclk;
	uपूर्णांक32_t mclk;
	काष्ठा PP_Clocks minimum_घड़ीs = अणु0पूर्ण;
	bool disable_mclk_चयनing;
	bool disable_mclk_चयनing_क्रम_frame_lock;
	bool disable_mclk_चयनing_क्रम_display;
	स्थिर काष्ठा phm_घड़ी_and_voltage_limits *max_limits;
	uपूर्णांक32_t i;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	पूर्णांक32_t count;
	पूर्णांक32_t stable_pstate_sclk = 0, stable_pstate_mclk = 0;
	uपूर्णांक32_t latency;
	bool latency_allowed = false;

	data->battery_state = (PP_StateUILabel_Battery ==
			request_ps->classअगरication.ui_label);
	data->mclk_ignore_संकेत = false;

	PP_ASSERT_WITH_CODE(smu7_ps->perक्रमmance_level_count == 2,
				 "VI should always have 2 performance levels",
				);

	max_limits = adev->pm.ac_घातer ?
			&(hwmgr->dyn_state.max_घड़ी_voltage_on_ac) :
			&(hwmgr->dyn_state.max_घड़ी_voltage_on_dc);

	/* Cap घड़ी DPM tables at DC MAX अगर it is in DC. */
	अगर (!adev->pm.ac_घातer) अणु
		क्रम (i = 0; i < smu7_ps->perक्रमmance_level_count; i++) अणु
			अगर (smu7_ps->perक्रमmance_levels[i].memory_घड़ी > max_limits->mclk)
				smu7_ps->perक्रमmance_levels[i].memory_घड़ी = max_limits->mclk;
			अगर (smu7_ps->perक्रमmance_levels[i].engine_घड़ी > max_limits->sclk)
				smu7_ps->perक्रमmance_levels[i].engine_घड़ी = max_limits->sclk;
		पूर्ण
	पूर्ण

	minimum_घड़ीs.engineClock = hwmgr->display_config->min_core_set_घड़ी;
	minimum_घड़ीs.memoryClock = hwmgr->display_config->min_mem_set_घड़ी;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_StablePState)) अणु
		max_limits = &(hwmgr->dyn_state.max_घड़ी_voltage_on_ac);
		stable_pstate_sclk = (max_limits->sclk * 75) / 100;

		क्रम (count = table_info->vdd_dep_on_sclk->count - 1;
				count >= 0; count--) अणु
			अगर (stable_pstate_sclk >=
					table_info->vdd_dep_on_sclk->entries[count].clk) अणु
				stable_pstate_sclk =
						table_info->vdd_dep_on_sclk->entries[count].clk;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (count < 0)
			stable_pstate_sclk = table_info->vdd_dep_on_sclk->entries[0].clk;

		stable_pstate_mclk = max_limits->mclk;

		minimum_घड़ीs.engineClock = stable_pstate_sclk;
		minimum_घड़ीs.memoryClock = stable_pstate_mclk;
	पूर्ण

	disable_mclk_चयनing_क्रम_frame_lock = phm_cap_enabled(
				    hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				    PHM_Platक्रमmCaps_DisableMclkSwitchingForFrameLock);

	disable_mclk_चयनing_क्रम_display = ((1 < hwmgr->display_config->num_display) &&
						!hwmgr->display_config->multi_monitor_in_sync) ||
						(hwmgr->display_config->num_display &&
						smu7_vblank_too_लघु(hwmgr, hwmgr->display_config->min_vblank_समय));

	disable_mclk_चयनing = disable_mclk_चयनing_क्रम_frame_lock ||
					 disable_mclk_चयनing_क्रम_display;

	अगर (hwmgr->display_config->num_display == 0) अणु
		अगर (hwmgr->chip_id >= CHIP_POLARIS10 && hwmgr->chip_id <= CHIP_VEGAM)
			data->mclk_ignore_संकेत = true;
		अन्यथा
			disable_mclk_चयनing = false;
	पूर्ण

	sclk = smu7_ps->perक्रमmance_levels[0].engine_घड़ी;
	mclk = smu7_ps->perक्रमmance_levels[0].memory_घड़ी;

	अगर (disable_mclk_चयनing &&
	    (!(hwmgr->chip_id >= CHIP_POLARIS10 &&
	    hwmgr->chip_id <= CHIP_VEGAM)))
		mclk = smu7_ps->perक्रमmance_levels
		[smu7_ps->perक्रमmance_level_count - 1].memory_घड़ी;

	अगर (sclk < minimum_घड़ीs.engineClock)
		sclk = (minimum_घड़ीs.engineClock > max_limits->sclk) ?
				max_limits->sclk : minimum_घड़ीs.engineClock;

	अगर (mclk < minimum_घड़ीs.memoryClock)
		mclk = (minimum_घड़ीs.memoryClock > max_limits->mclk) ?
				max_limits->mclk : minimum_घड़ीs.memoryClock;

	smu7_ps->perक्रमmance_levels[0].engine_घड़ी = sclk;
	smu7_ps->perक्रमmance_levels[0].memory_घड़ी = mclk;

	smu7_ps->perक्रमmance_levels[1].engine_घड़ी =
		(smu7_ps->perक्रमmance_levels[1].engine_घड़ी >=
				smu7_ps->perक्रमmance_levels[0].engine_घड़ी) ?
						smu7_ps->perक्रमmance_levels[1].engine_घड़ी :
						smu7_ps->perक्रमmance_levels[0].engine_घड़ी;

	अगर (disable_mclk_चयनing) अणु
		अगर (mclk < smu7_ps->perक्रमmance_levels[1].memory_घड़ी)
			mclk = smu7_ps->perक्रमmance_levels[1].memory_घड़ी;

		अगर (hwmgr->chip_id >= CHIP_POLARIS10 && hwmgr->chip_id <= CHIP_VEGAM) अणु
			अगर (disable_mclk_चयनing_क्रम_display) अणु
				/* Find the lowest MCLK frequency that is within
				 * the tolerable latency defined in DAL
				 */
				latency = hwmgr->display_config->dce_tolerable_mclk_in_active_latency;
				क्रम (i = 0; i < data->mclk_latency_table.count; i++) अणु
					अगर (data->mclk_latency_table.entries[i].latency <= latency) अणु
						latency_allowed = true;

						अगर ((data->mclk_latency_table.entries[i].frequency >=
								smu7_ps->perक्रमmance_levels[0].memory_घड़ी) &&
						    (data->mclk_latency_table.entries[i].frequency <=
								smu7_ps->perक्रमmance_levels[1].memory_घड़ी)) अणु
							mclk = data->mclk_latency_table.entries[i].frequency;
							अवरोध;
						पूर्ण
					पूर्ण
				पूर्ण
				अगर ((i >= data->mclk_latency_table.count - 1) && !latency_allowed) अणु
					data->mclk_ignore_संकेत = true;
				पूर्ण अन्यथा अणु
					data->mclk_ignore_संकेत = false;
				पूर्ण
			पूर्ण

			अगर (disable_mclk_चयनing_क्रम_frame_lock)
				mclk = smu7_ps->perक्रमmance_levels[1].memory_घड़ी;
		पूर्ण

		smu7_ps->perक्रमmance_levels[0].memory_घड़ी = mclk;

		अगर (!(hwmgr->chip_id >= CHIP_POLARIS10 &&
		      hwmgr->chip_id <= CHIP_VEGAM))
			smu7_ps->perक्रमmance_levels[1].memory_घड़ी = mclk;
	पूर्ण अन्यथा अणु
		अगर (smu7_ps->perक्रमmance_levels[1].memory_घड़ी <
				smu7_ps->perक्रमmance_levels[0].memory_घड़ी)
			smu7_ps->perक्रमmance_levels[1].memory_घड़ी =
					smu7_ps->perक्रमmance_levels[0].memory_घड़ी;
	पूर्ण

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_StablePState)) अणु
		क्रम (i = 0; i < smu7_ps->perक्रमmance_level_count; i++) अणु
			smu7_ps->perक्रमmance_levels[i].engine_घड़ी = stable_pstate_sclk;
			smu7_ps->perक्रमmance_levels[i].memory_घड़ी = stable_pstate_mclk;
			smu7_ps->perक्रमmance_levels[i].pcie_gen = data->pcie_gen_perक्रमmance.max;
			smu7_ps->perक्रमmance_levels[i].pcie_lane = data->pcie_gen_perक्रमmance.max;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


अटल uपूर्णांक32_t smu7_dpm_get_mclk(काष्ठा pp_hwmgr *hwmgr, bool low)
अणु
	काष्ठा pp_घातer_state  *ps;
	काष्ठा smu7_घातer_state  *smu7_ps;

	अगर (hwmgr == शून्य)
		वापस -EINVAL;

	ps = hwmgr->request_ps;

	अगर (ps == शून्य)
		वापस -EINVAL;

	smu7_ps = cast_phw_smu7_घातer_state(&ps->hardware);

	अगर (low)
		वापस smu7_ps->perक्रमmance_levels[0].memory_घड़ी;
	अन्यथा
		वापस smu7_ps->perक्रमmance_levels
				[smu7_ps->perक्रमmance_level_count-1].memory_घड़ी;
पूर्ण

अटल uपूर्णांक32_t smu7_dpm_get_sclk(काष्ठा pp_hwmgr *hwmgr, bool low)
अणु
	काष्ठा pp_घातer_state  *ps;
	काष्ठा smu7_घातer_state  *smu7_ps;

	अगर (hwmgr == शून्य)
		वापस -EINVAL;

	ps = hwmgr->request_ps;

	अगर (ps == शून्य)
		वापस -EINVAL;

	smu7_ps = cast_phw_smu7_घातer_state(&ps->hardware);

	अगर (low)
		वापस smu7_ps->perक्रमmance_levels[0].engine_घड़ी;
	अन्यथा
		वापस smu7_ps->perक्रमmance_levels
				[smu7_ps->perक्रमmance_level_count-1].engine_घड़ी;
पूर्ण

अटल पूर्णांक smu7_dpm_patch_boot_state(काष्ठा pp_hwmgr *hwmgr,
					काष्ठा pp_hw_घातer_state *hw_ps)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_घातer_state *ps = (काष्ठा smu7_घातer_state *)hw_ps;
	ATOM_FIRMWARE_INFO_V2_2 *fw_info;
	uपूर्णांक16_t size;
	uपूर्णांक8_t frev, crev;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, FirmwareInfo);

	/* First retrieve the Boot घड़ीs and VDDC from the firmware info table.
	 * We assume here that fw_info is unchanged अगर this call fails.
	 */
	fw_info = (ATOM_FIRMWARE_INFO_V2_2 *)smu_atom_get_data_table(hwmgr->adev, index,
			&size, &frev, &crev);
	अगर (!fw_info)
		/* During a test, there is no firmware info table. */
		वापस 0;

	/* Patch the state. */
	data->vbios_boot_state.sclk_bootup_value =
			le32_to_cpu(fw_info->ulDefaultEngineClock);
	data->vbios_boot_state.mclk_bootup_value =
			le32_to_cpu(fw_info->ulDefaultMemoryClock);
	data->vbios_boot_state.mvdd_bootup_value =
			le16_to_cpu(fw_info->usBootUpMVDDCVoltage);
	data->vbios_boot_state.vddc_bootup_value =
			le16_to_cpu(fw_info->usBootUpVDDCVoltage);
	data->vbios_boot_state.vddci_bootup_value =
			le16_to_cpu(fw_info->usBootUpVDDCIVoltage);
	data->vbios_boot_state.pcie_gen_bootup_value =
			smu7_get_current_pcie_speed(hwmgr);

	data->vbios_boot_state.pcie_lane_bootup_value =
			(uपूर्णांक16_t)smu7_get_current_pcie_lane_number(hwmgr);

	/* set boot घातer state */
	ps->perक्रमmance_levels[0].memory_घड़ी = data->vbios_boot_state.mclk_bootup_value;
	ps->perक्रमmance_levels[0].engine_घड़ी = data->vbios_boot_state.sclk_bootup_value;
	ps->perक्रमmance_levels[0].pcie_gen = data->vbios_boot_state.pcie_gen_bootup_value;
	ps->perक्रमmance_levels[0].pcie_lane = data->vbios_boot_state.pcie_lane_bootup_value;

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_number_of_घातerplay_table_entries(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	अचिन्हित दीर्घ ret = 0;

	अगर (hwmgr->pp_table_version == PP_TABLE_V0) अणु
		result = pp_tables_get_num_of_entries(hwmgr, &ret);
		वापस result ? 0 : ret;
	पूर्ण अन्यथा अगर (hwmgr->pp_table_version == PP_TABLE_V1) अणु
		result = get_number_of_घातerplay_table_entries_v1_0(hwmgr);
		वापस result;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_pp_table_entry_callback_func_v1(काष्ठा pp_hwmgr *hwmgr,
		व्योम *state, काष्ठा pp_घातer_state *घातer_state,
		व्योम *pp_table, uपूर्णांक32_t classअगरication_flag)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_घातer_state  *smu7_घातer_state =
			(काष्ठा smu7_घातer_state *)(&(घातer_state->hardware));
	काष्ठा smu7_perक्रमmance_level *perक्रमmance_level;
	ATOM_Tonga_State *state_entry = (ATOM_Tonga_State *)state;
	ATOM_Tonga_POWERPLAYTABLE *घातerplay_table =
			(ATOM_Tonga_POWERPLAYTABLE *)pp_table;
	PPTable_Generic_SubTable_Header *sclk_dep_table =
			(PPTable_Generic_SubTable_Header *)
			(((अचिन्हित दीर्घ)घातerplay_table) +
				le16_to_cpu(घातerplay_table->usSclkDependencyTableOffset));

	ATOM_Tonga_MCLK_Dependency_Table *mclk_dep_table =
			(ATOM_Tonga_MCLK_Dependency_Table *)
			(((अचिन्हित दीर्घ)घातerplay_table) +
				le16_to_cpu(घातerplay_table->usMclkDependencyTableOffset));

	/* The following fields are not initialized here: id orderedList allStatesList */
	घातer_state->classअगरication.ui_label =
			(le16_to_cpu(state_entry->usClassअगरication) &
			ATOM_PPLIB_CLASSIFICATION_UI_MASK) >>
			ATOM_PPLIB_CLASSIFICATION_UI_SHIFT;
	घातer_state->classअगरication.flags = classअगरication_flag;
	/* NOTE: There is a classअगरication2 flag in BIOS that is not being used right now */

	घातer_state->classअगरication.temporary_state = false;
	घातer_state->classअगरication.to_be_deleted = false;

	घातer_state->validation.disallowOnDC =
			(0 != (le32_to_cpu(state_entry->ulCapsAndSettings) &
					ATOM_Tonga_DISALLOW_ON_DC));

	घातer_state->pcie.lanes = 0;

	घातer_state->display.disableFrameModulation = false;
	घातer_state->display.limitRefreshrate = false;
	घातer_state->display.enableVariBright =
			(0 != (le32_to_cpu(state_entry->ulCapsAndSettings) &
					ATOM_Tonga_ENABLE_VARIBRIGHT));

	घातer_state->validation.supportedPowerLevels = 0;
	घातer_state->uvd_घड़ीs.VCLK = 0;
	घातer_state->uvd_घड़ीs.DCLK = 0;
	घातer_state->temperatures.min = 0;
	घातer_state->temperatures.max = 0;

	perक्रमmance_level = &(smu7_घातer_state->perक्रमmance_levels
			[smu7_घातer_state->perक्रमmance_level_count++]);

	PP_ASSERT_WITH_CODE(
			(smu7_घातer_state->perक्रमmance_level_count < smum_get_mac_definition(hwmgr, SMU_MAX_LEVELS_GRAPHICS)),
			"Performance levels exceeds SMC limit!",
			वापस -EINVAL);

	PP_ASSERT_WITH_CODE(
			(smu7_घातer_state->perक्रमmance_level_count <=
					hwmgr->platक्रमm_descriptor.hardwareActivityPerक्रमmanceLevels),
			"Performance levels exceeds Driver limit!",
			वापस -EINVAL);

	/* Perक्रमmance levels are arranged from low to high. */
	perक्रमmance_level->memory_घड़ी = mclk_dep_table->entries
			[state_entry->ucMemoryClockIndexLow].ulMclk;
	अगर (sclk_dep_table->ucRevId == 0)
		perक्रमmance_level->engine_घड़ी = ((ATOM_Tonga_SCLK_Dependency_Table *)sclk_dep_table)->entries
			[state_entry->ucEngineClockIndexLow].ulSclk;
	अन्यथा अगर (sclk_dep_table->ucRevId == 1)
		perक्रमmance_level->engine_घड़ी = ((ATOM_Polaris_SCLK_Dependency_Table *)sclk_dep_table)->entries
			[state_entry->ucEngineClockIndexLow].ulSclk;
	perक्रमmance_level->pcie_gen = get_pcie_gen_support(data->pcie_gen_cap,
			state_entry->ucPCIEGenLow);
	perक्रमmance_level->pcie_lane = get_pcie_lane_support(data->pcie_lane_cap,
			state_entry->ucPCIELaneLow);

	perक्रमmance_level = &(smu7_घातer_state->perक्रमmance_levels
			[smu7_घातer_state->perक्रमmance_level_count++]);
	perक्रमmance_level->memory_घड़ी = mclk_dep_table->entries
			[state_entry->ucMemoryClockIndexHigh].ulMclk;

	अगर (sclk_dep_table->ucRevId == 0)
		perक्रमmance_level->engine_घड़ी = ((ATOM_Tonga_SCLK_Dependency_Table *)sclk_dep_table)->entries
			[state_entry->ucEngineClockIndexHigh].ulSclk;
	अन्यथा अगर (sclk_dep_table->ucRevId == 1)
		perक्रमmance_level->engine_घड़ी = ((ATOM_Polaris_SCLK_Dependency_Table *)sclk_dep_table)->entries
			[state_entry->ucEngineClockIndexHigh].ulSclk;

	perक्रमmance_level->pcie_gen = get_pcie_gen_support(data->pcie_gen_cap,
			state_entry->ucPCIEGenHigh);
	perक्रमmance_level->pcie_lane = get_pcie_lane_support(data->pcie_lane_cap,
			state_entry->ucPCIELaneHigh);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_pp_table_entry_v1(काष्ठा pp_hwmgr *hwmgr,
		अचिन्हित दीर्घ entry_index, काष्ठा pp_घातer_state *state)
अणु
	पूर्णांक result;
	काष्ठा smu7_घातer_state *ps;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_mclk_table =
			table_info->vdd_dep_on_mclk;

	state->hardware.magic = PHM_VIslands_Magic;

	ps = (काष्ठा smu7_घातer_state *)(&state->hardware);

	result = get_घातerplay_table_entry_v1_0(hwmgr, entry_index, state,
			smu7_get_pp_table_entry_callback_func_v1);

	/* This is the earliest समय we have all the dependency table and the VBIOS boot state
	 * as PP_Tables_GetPowerPlayTableEntry retrieves the VBIOS boot state
	 * अगर there is only one VDDCI/MCLK level, check अगर it's the same as VBIOS boot state
	 */
	अगर (dep_mclk_table != शून्य && dep_mclk_table->count == 1) अणु
		अगर (dep_mclk_table->entries[0].clk !=
				data->vbios_boot_state.mclk_bootup_value)
			pr_debug("Single MCLK entry VDDCI/MCLK dependency table "
					"does not match VBIOS boot MCLK level");
		अगर (dep_mclk_table->entries[0].vddci !=
				data->vbios_boot_state.vddci_bootup_value)
			pr_debug("Single VDDCI entry VDDCI/MCLK dependency table "
					"does not match VBIOS boot VDDCI level");
	पूर्ण

	/* set DC compatible flag अगर this state supports DC */
	अगर (!state->validation.disallowOnDC)
		ps->dc_compatible = true;

	अगर (state->classअगरication.flags & PP_StateClassअगरicationFlag_ACPI)
		data->acpi_pcie_gen = ps->perक्रमmance_levels[0].pcie_gen;

	ps->uvd_clks.vclk = state->uvd_घड़ीs.VCLK;
	ps->uvd_clks.dclk = state->uvd_घड़ीs.DCLK;

	अगर (!result) अणु
		uपूर्णांक32_t i;

		चयन (state->classअगरication.ui_label) अणु
		हाल PP_StateUILabel_Perक्रमmance:
			data->use_pcie_perक्रमmance_levels = true;
			क्रम (i = 0; i < ps->perक्रमmance_level_count; i++) अणु
				अगर (data->pcie_gen_perक्रमmance.max <
						ps->perक्रमmance_levels[i].pcie_gen)
					data->pcie_gen_perक्रमmance.max =
							ps->perक्रमmance_levels[i].pcie_gen;

				अगर (data->pcie_gen_perक्रमmance.min >
						ps->perक्रमmance_levels[i].pcie_gen)
					data->pcie_gen_perक्रमmance.min =
							ps->perक्रमmance_levels[i].pcie_gen;

				अगर (data->pcie_lane_perक्रमmance.max <
						ps->perक्रमmance_levels[i].pcie_lane)
					data->pcie_lane_perक्रमmance.max =
							ps->perक्रमmance_levels[i].pcie_lane;
				अगर (data->pcie_lane_perक्रमmance.min >
						ps->perक्रमmance_levels[i].pcie_lane)
					data->pcie_lane_perक्रमmance.min =
							ps->perक्रमmance_levels[i].pcie_lane;
			पूर्ण
			अवरोध;
		हाल PP_StateUILabel_Battery:
			data->use_pcie_घातer_saving_levels = true;

			क्रम (i = 0; i < ps->perक्रमmance_level_count; i++) अणु
				अगर (data->pcie_gen_घातer_saving.max <
						ps->perक्रमmance_levels[i].pcie_gen)
					data->pcie_gen_घातer_saving.max =
							ps->perक्रमmance_levels[i].pcie_gen;

				अगर (data->pcie_gen_घातer_saving.min >
						ps->perक्रमmance_levels[i].pcie_gen)
					data->pcie_gen_घातer_saving.min =
							ps->perक्रमmance_levels[i].pcie_gen;

				अगर (data->pcie_lane_घातer_saving.max <
						ps->perक्रमmance_levels[i].pcie_lane)
					data->pcie_lane_घातer_saving.max =
							ps->perक्रमmance_levels[i].pcie_lane;

				अगर (data->pcie_lane_घातer_saving.min >
						ps->perक्रमmance_levels[i].pcie_lane)
					data->pcie_lane_घातer_saving.min =
							ps->perक्रमmance_levels[i].pcie_lane;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_pp_table_entry_callback_func_v0(काष्ठा pp_hwmgr *hwmgr,
					काष्ठा pp_hw_घातer_state *घातer_state,
					अचिन्हित पूर्णांक index, स्थिर व्योम *घड़ी_info)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_घातer_state  *ps = cast_phw_smu7_घातer_state(घातer_state);
	स्थिर ATOM_PPLIB_CI_CLOCK_INFO *visland_clk_info = घड़ी_info;
	काष्ठा smu7_perक्रमmance_level *perक्रमmance_level;
	uपूर्णांक32_t engine_घड़ी, memory_घड़ी;
	uपूर्णांक16_t pcie_gen_from_bios;

	engine_घड़ी = visland_clk_info->ucEngineClockHigh << 16 | visland_clk_info->usEngineClockLow;
	memory_घड़ी = visland_clk_info->ucMemoryClockHigh << 16 | visland_clk_info->usMemoryClockLow;

	अगर (!(data->mc_micro_code_feature & DISABLE_MC_LOADMICROCODE) && memory_घड़ी > data->highest_mclk)
		data->highest_mclk = memory_घड़ी;

	PP_ASSERT_WITH_CODE(
			(ps->perक्रमmance_level_count < smum_get_mac_definition(hwmgr, SMU_MAX_LEVELS_GRAPHICS)),
			"Performance levels exceeds SMC limit!",
			वापस -EINVAL);

	PP_ASSERT_WITH_CODE(
			(ps->perक्रमmance_level_count <
					hwmgr->platक्रमm_descriptor.hardwareActivityPerक्रमmanceLevels),
			"Performance levels exceeds Driver limit, Skip!",
			वापस 0);

	perक्रमmance_level = &(ps->perक्रमmance_levels
			[ps->perक्रमmance_level_count++]);

	/* Perक्रमmance levels are arranged from low to high. */
	perक्रमmance_level->memory_घड़ी = memory_घड़ी;
	perक्रमmance_level->engine_घड़ी = engine_घड़ी;

	pcie_gen_from_bios = visland_clk_info->ucPCIEGen;

	perक्रमmance_level->pcie_gen = get_pcie_gen_support(data->pcie_gen_cap, pcie_gen_from_bios);
	perक्रमmance_level->pcie_lane = get_pcie_lane_support(data->pcie_lane_cap, visland_clk_info->usPCIELane);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_pp_table_entry_v0(काष्ठा pp_hwmgr *hwmgr,
		अचिन्हित दीर्घ entry_index, काष्ठा pp_घातer_state *state)
अणु
	पूर्णांक result;
	काष्ठा smu7_घातer_state *ps;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_घड़ी_voltage_dependency_table *dep_mclk_table =
			hwmgr->dyn_state.vddci_dependency_on_mclk;

	स_रखो(&state->hardware, 0x00, माप(काष्ठा pp_hw_घातer_state));

	state->hardware.magic = PHM_VIslands_Magic;

	ps = (काष्ठा smu7_घातer_state *)(&state->hardware);

	result = pp_tables_get_entry(hwmgr, entry_index, state,
			smu7_get_pp_table_entry_callback_func_v0);

	/*
	 * This is the earliest समय we have all the dependency table
	 * and the VBIOS boot state as
	 * PP_Tables_GetPowerPlayTableEntry retrieves the VBIOS boot
	 * state अगर there is only one VDDCI/MCLK level, check अगर it's
	 * the same as VBIOS boot state
	 */
	अगर (dep_mclk_table != शून्य && dep_mclk_table->count == 1) अणु
		अगर (dep_mclk_table->entries[0].clk !=
				data->vbios_boot_state.mclk_bootup_value)
			pr_debug("Single MCLK entry VDDCI/MCLK dependency table "
					"does not match VBIOS boot MCLK level");
		अगर (dep_mclk_table->entries[0].v !=
				data->vbios_boot_state.vddci_bootup_value)
			pr_debug("Single VDDCI entry VDDCI/MCLK dependency table "
					"does not match VBIOS boot VDDCI level");
	पूर्ण

	/* set DC compatible flag अगर this state supports DC */
	अगर (!state->validation.disallowOnDC)
		ps->dc_compatible = true;

	अगर (state->classअगरication.flags & PP_StateClassअगरicationFlag_ACPI)
		data->acpi_pcie_gen = ps->perक्रमmance_levels[0].pcie_gen;

	ps->uvd_clks.vclk = state->uvd_घड़ीs.VCLK;
	ps->uvd_clks.dclk = state->uvd_घड़ीs.DCLK;

	अगर (!result) अणु
		uपूर्णांक32_t i;

		चयन (state->classअगरication.ui_label) अणु
		हाल PP_StateUILabel_Perक्रमmance:
			data->use_pcie_perक्रमmance_levels = true;

			क्रम (i = 0; i < ps->perक्रमmance_level_count; i++) अणु
				अगर (data->pcie_gen_perक्रमmance.max <
						ps->perक्रमmance_levels[i].pcie_gen)
					data->pcie_gen_perक्रमmance.max =
							ps->perक्रमmance_levels[i].pcie_gen;

				अगर (data->pcie_gen_perक्रमmance.min >
						ps->perक्रमmance_levels[i].pcie_gen)
					data->pcie_gen_perक्रमmance.min =
							ps->perक्रमmance_levels[i].pcie_gen;

				अगर (data->pcie_lane_perक्रमmance.max <
						ps->perक्रमmance_levels[i].pcie_lane)
					data->pcie_lane_perक्रमmance.max =
							ps->perक्रमmance_levels[i].pcie_lane;

				अगर (data->pcie_lane_perक्रमmance.min >
						ps->perक्रमmance_levels[i].pcie_lane)
					data->pcie_lane_perक्रमmance.min =
							ps->perक्रमmance_levels[i].pcie_lane;
			पूर्ण
			अवरोध;
		हाल PP_StateUILabel_Battery:
			data->use_pcie_घातer_saving_levels = true;

			क्रम (i = 0; i < ps->perक्रमmance_level_count; i++) अणु
				अगर (data->pcie_gen_घातer_saving.max <
						ps->perक्रमmance_levels[i].pcie_gen)
					data->pcie_gen_घातer_saving.max =
							ps->perक्रमmance_levels[i].pcie_gen;

				अगर (data->pcie_gen_घातer_saving.min >
						ps->perक्रमmance_levels[i].pcie_gen)
					data->pcie_gen_घातer_saving.min =
							ps->perक्रमmance_levels[i].pcie_gen;

				अगर (data->pcie_lane_घातer_saving.max <
						ps->perक्रमmance_levels[i].pcie_lane)
					data->pcie_lane_घातer_saving.max =
							ps->perक्रमmance_levels[i].pcie_lane;

				अगर (data->pcie_lane_घातer_saving.min >
						ps->perक्रमmance_levels[i].pcie_lane)
					data->pcie_lane_घातer_saving.min =
							ps->perक्रमmance_levels[i].pcie_lane;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_pp_table_entry(काष्ठा pp_hwmgr *hwmgr,
		अचिन्हित दीर्घ entry_index, काष्ठा pp_घातer_state *state)
अणु
	अगर (hwmgr->pp_table_version == PP_TABLE_V0)
		वापस smu7_get_pp_table_entry_v0(hwmgr, entry_index, state);
	अन्यथा अगर (hwmgr->pp_table_version == PP_TABLE_V1)
		वापस smu7_get_pp_table_entry_v1(hwmgr, entry_index, state);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_gpu_घातer(काष्ठा pp_hwmgr *hwmgr, u32 *query)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक i;
	u32 पंचांगp = 0;

	अगर (!query)
		वापस -EINVAL;

	/*
	 * PPSMC_MSG_GetCurrPkgPwr is not supported on:
	 *  - Hawaii
	 *  - Bonaire
	 *  - Fiji
	 *  - Tonga
	 */
	अगर ((adev->asic_type != CHIP_HAWAII) &&
	    (adev->asic_type != CHIP_BONAIRE) &&
	    (adev->asic_type != CHIP_FIJI) &&
	    (adev->asic_type != CHIP_TONGA)) अणु
		smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_GetCurrPkgPwr, 0, &पंचांगp);
		*query = पंचांगp;

		अगर (पंचांगp != 0)
			वापस 0;
	पूर्ण

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_PmStatusLogStart, शून्य);
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
							ixSMU_PM_STATUS_95, 0);

	क्रम (i = 0; i < 10; i++) अणु
		msleep(500);
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_PmStatusLogSample, शून्य);
		पंचांगp = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device,
						CGS_IND_REG__SMC,
						ixSMU_PM_STATUS_95);
		अगर (पंचांगp != 0)
			अवरोध;
	पूर्ण
	*query = पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_पढ़ो_sensor(काष्ठा pp_hwmgr *hwmgr, पूर्णांक idx,
			    व्योम *value, पूर्णांक *size)
अणु
	uपूर्णांक32_t sclk, mclk, activity_percent;
	uपूर्णांक32_t offset, val_vid;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	/* size must be at least 4 bytes क्रम all sensors */
	अगर (*size < 4)
		वापस -EINVAL;

	चयन (idx) अणु
	हाल AMDGPU_PP_SENSOR_GFX_SCLK:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_API_GetSclkFrequency, &sclk);
		*((uपूर्णांक32_t *)value) = sclk;
		*size = 4;
		वापस 0;
	हाल AMDGPU_PP_SENSOR_GFX_MCLK:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_API_GetMclkFrequency, &mclk);
		*((uपूर्णांक32_t *)value) = mclk;
		*size = 4;
		वापस 0;
	हाल AMDGPU_PP_SENSOR_GPU_LOAD:
	हाल AMDGPU_PP_SENSOR_MEM_LOAD:
		offset = data->soft_regs_start + smum_get_दुरत्व(hwmgr,
								SMU_SoftRegisters,
								(idx == AMDGPU_PP_SENSOR_GPU_LOAD) ?
								AverageGraphicsActivity:
								AverageMemoryActivity);

		activity_percent = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, offset);
		activity_percent += 0x80;
		activity_percent >>= 8;
		*((uपूर्णांक32_t *)value) = activity_percent > 100 ? 100 : activity_percent;
		*size = 4;
		वापस 0;
	हाल AMDGPU_PP_SENSOR_GPU_TEMP:
		*((uपूर्णांक32_t *)value) = smu7_thermal_get_temperature(hwmgr);
		*size = 4;
		वापस 0;
	हाल AMDGPU_PP_SENSOR_UVD_POWER:
		*((uपूर्णांक32_t *)value) = data->uvd_घातer_gated ? 0 : 1;
		*size = 4;
		वापस 0;
	हाल AMDGPU_PP_SENSOR_VCE_POWER:
		*((uपूर्णांक32_t *)value) = data->vce_घातer_gated ? 0 : 1;
		*size = 4;
		वापस 0;
	हाल AMDGPU_PP_SENSOR_GPU_POWER:
		वापस smu7_get_gpu_घातer(hwmgr, (uपूर्णांक32_t *)value);
	हाल AMDGPU_PP_SENSOR_VDDGFX:
		अगर ((data->vr_config & VRCONF_VDDGFX_MASK) ==
		    (VR_SVI2_PLANE_2 << VRCONF_VDDGFX_SHIFT))
			val_vid = PHM_READ_INसूचीECT_FIELD(hwmgr->device,
					CGS_IND_REG__SMC, PWR_SVI2_STATUS, PLANE2_VID);
		अन्यथा
			val_vid = PHM_READ_INसूचीECT_FIELD(hwmgr->device,
					CGS_IND_REG__SMC, PWR_SVI2_STATUS, PLANE1_VID);

		*((uपूर्णांक32_t *)value) = (uपूर्णांक32_t)convert_to_vddc(val_vid);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक smu7_find_dpm_states_घड़ीs_in_dpm_table(काष्ठा pp_hwmgr *hwmgr, स्थिर व्योम *input)
अणु
	स्थिर काष्ठा phm_set_घातer_state_input *states =
			(स्थिर काष्ठा phm_set_घातer_state_input *)input;
	स्थिर काष्ठा smu7_घातer_state *smu7_ps =
			cast_स्थिर_phw_smu7_घातer_state(states->pnew_state);
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_single_dpm_table *sclk_table = &(data->dpm_table.sclk_table);
	uपूर्णांक32_t sclk = smu7_ps->perक्रमmance_levels
			[smu7_ps->perक्रमmance_level_count - 1].engine_घड़ी;
	काष्ठा smu7_single_dpm_table *mclk_table = &(data->dpm_table.mclk_table);
	uपूर्णांक32_t mclk = smu7_ps->perक्रमmance_levels
			[smu7_ps->perक्रमmance_level_count - 1].memory_घड़ी;
	काष्ठा PP_Clocks min_घड़ीs = अणु0पूर्ण;
	uपूर्णांक32_t i;

	क्रम (i = 0; i < sclk_table->count; i++) अणु
		अगर (sclk == sclk_table->dpm_levels[i].value)
			अवरोध;
	पूर्ण

	अगर (i >= sclk_table->count) अणु
		अगर (sclk > sclk_table->dpm_levels[i-1].value) अणु
			data->need_update_smu7_dpm_table |= DPMTABLE_OD_UPDATE_SCLK;
			sclk_table->dpm_levels[i-1].value = sclk;
		पूर्ण
	पूर्ण अन्यथा अणु
	/* TODO: Check SCLK in DAL's minimum घड़ीs
	 * in हाल DeepSleep भागider update is required.
	 */
		अगर (data->display_timing.min_घड़ी_in_sr != min_घड़ीs.engineClockInSR &&
			(min_घड़ीs.engineClockInSR >= SMU7_MINIMUM_ENGINE_CLOCK ||
				data->display_timing.min_घड़ी_in_sr >= SMU7_MINIMUM_ENGINE_CLOCK))
			data->need_update_smu7_dpm_table |= DPMTABLE_UPDATE_SCLK;
	पूर्ण

	क्रम (i = 0; i < mclk_table->count; i++) अणु
		अगर (mclk == mclk_table->dpm_levels[i].value)
			अवरोध;
	पूर्ण

	अगर (i >= mclk_table->count) अणु
		अगर (mclk > mclk_table->dpm_levels[i-1].value) अणु
			data->need_update_smu7_dpm_table |= DPMTABLE_OD_UPDATE_MCLK;
			mclk_table->dpm_levels[i-1].value = mclk;
		पूर्ण
	पूर्ण

	अगर (data->display_timing.num_existing_displays != hwmgr->display_config->num_display)
		data->need_update_smu7_dpm_table |= DPMTABLE_UPDATE_MCLK;

	वापस 0;
पूर्ण

अटल uपूर्णांक16_t smu7_get_maximum_link_speed(काष्ठा pp_hwmgr *hwmgr,
		स्थिर काष्ठा smu7_घातer_state *smu7_ps)
अणु
	uपूर्णांक32_t i;
	uपूर्णांक32_t sclk, max_sclk = 0;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_dpm_table *dpm_table = &data->dpm_table;

	क्रम (i = 0; i < smu7_ps->perक्रमmance_level_count; i++) अणु
		sclk = smu7_ps->perक्रमmance_levels[i].engine_घड़ी;
		अगर (max_sclk < sclk)
			max_sclk = sclk;
	पूर्ण

	क्रम (i = 0; i < dpm_table->sclk_table.count; i++) अणु
		अगर (dpm_table->sclk_table.dpm_levels[i].value == max_sclk)
			वापस (uपूर्णांक16_t) ((i >= dpm_table->pcie_speed_table.count) ?
					dpm_table->pcie_speed_table.dpm_levels
					[dpm_table->pcie_speed_table.count - 1].value :
					dpm_table->pcie_speed_table.dpm_levels[i].value);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_request_link_speed_change_beक्रमe_state_change(
		काष्ठा pp_hwmgr *hwmgr, स्थिर व्योम *input)
अणु
	स्थिर काष्ठा phm_set_घातer_state_input *states =
			(स्थिर काष्ठा phm_set_घातer_state_input *)input;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	स्थिर काष्ठा smu7_घातer_state *smu7_nps =
			cast_स्थिर_phw_smu7_घातer_state(states->pnew_state);
	स्थिर काष्ठा smu7_घातer_state *polaris10_cps =
			cast_स्थिर_phw_smu7_घातer_state(states->pcurrent_state);

	uपूर्णांक16_t target_link_speed = smu7_get_maximum_link_speed(hwmgr, smu7_nps);
	uपूर्णांक16_t current_link_speed;

	अगर (data->क्रमce_pcie_gen == PP_PCIEGenInvalid)
		current_link_speed = smu7_get_maximum_link_speed(hwmgr, polaris10_cps);
	अन्यथा
		current_link_speed = data->क्रमce_pcie_gen;

	data->क्रमce_pcie_gen = PP_PCIEGenInvalid;
	data->pspp_notअगरy_required = false;

	अगर (target_link_speed > current_link_speed) अणु
		चयन (target_link_speed) अणु
#अगर_घोषित CONFIG_ACPI
		हाल PP_PCIEGen3:
			अगर (0 == amdgpu_acpi_pcie_perक्रमmance_request(hwmgr->adev, PCIE_PERF_REQ_GEN3, false))
				अवरोध;
			data->क्रमce_pcie_gen = PP_PCIEGen2;
			अगर (current_link_speed == PP_PCIEGen2)
				अवरोध;
			fallthrough;
		हाल PP_PCIEGen2:
			अगर (0 == amdgpu_acpi_pcie_perक्रमmance_request(hwmgr->adev, PCIE_PERF_REQ_GEN2, false))
				अवरोध;
			fallthrough;
#पूर्ण_अगर
		शेष:
			data->क्रमce_pcie_gen = smu7_get_current_pcie_speed(hwmgr);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (target_link_speed < current_link_speed)
			data->pspp_notअगरy_required = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_मुक्तze_sclk_mclk_dpm(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (0 == data->need_update_smu7_dpm_table)
		वापस 0;

	अगर ((0 == data->sclk_dpm_key_disabled) &&
		(data->need_update_smu7_dpm_table &
			(DPMTABLE_OD_UPDATE_SCLK + DPMTABLE_UPDATE_SCLK))) अणु
		PP_ASSERT_WITH_CODE(true == smum_is_dpm_running(hwmgr),
				"Trying to freeze SCLK DPM when DPM is disabled",
				);
		PP_ASSERT_WITH_CODE(0 == smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_SCLKDPM_FreezeLevel,
				शून्य),
				"Failed to freeze SCLK DPM during FreezeSclkMclkDPM Function!",
				वापस -EINVAL);
	पूर्ण

	अगर ((0 == data->mclk_dpm_key_disabled) &&
		!data->mclk_ignore_संकेत &&
		(data->need_update_smu7_dpm_table &
		 DPMTABLE_OD_UPDATE_MCLK)) अणु
		PP_ASSERT_WITH_CODE(true == smum_is_dpm_running(hwmgr),
				"Trying to freeze MCLK DPM when DPM is disabled",
				);
		PP_ASSERT_WITH_CODE(0 == smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_MCLKDPM_FreezeLevel,
				शून्य),
				"Failed to freeze MCLK DPM during FreezeSclkMclkDPM Function!",
				वापस -EINVAL);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_populate_and_upload_sclk_mclk_dpm_levels(
		काष्ठा pp_hwmgr *hwmgr, स्थिर व्योम *input)
अणु
	पूर्णांक result = 0;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_dpm_table *dpm_table = &data->dpm_table;
	uपूर्णांक32_t count;
	काष्ठा smu7_odn_dpm_table *odn_table = &(data->odn_dpm_table);
	काष्ठा phm_odn_घड़ी_levels *odn_sclk_table = &(odn_table->odn_core_घड़ी_dpm_levels);
	काष्ठा phm_odn_घड़ी_levels *odn_mclk_table = &(odn_table->odn_memory_घड़ी_dpm_levels);

	अगर (0 == data->need_update_smu7_dpm_table)
		वापस 0;

	अगर (hwmgr->od_enabled && data->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_SCLK) अणु
		क्रम (count = 0; count < dpm_table->sclk_table.count; count++) अणु
			dpm_table->sclk_table.dpm_levels[count].enabled = odn_sclk_table->entries[count].enabled;
			dpm_table->sclk_table.dpm_levels[count].value = odn_sclk_table->entries[count].घड़ी;
		पूर्ण
	पूर्ण

	अगर (hwmgr->od_enabled && data->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_MCLK) अणु
		क्रम (count = 0; count < dpm_table->mclk_table.count; count++) अणु
			dpm_table->mclk_table.dpm_levels[count].enabled = odn_mclk_table->entries[count].enabled;
			dpm_table->mclk_table.dpm_levels[count].value = odn_mclk_table->entries[count].घड़ी;
		पूर्ण
	पूर्ण

	अगर (data->need_update_smu7_dpm_table &
			(DPMTABLE_OD_UPDATE_SCLK + DPMTABLE_UPDATE_SCLK)) अणु
		result = smum_populate_all_graphic_levels(hwmgr);
		PP_ASSERT_WITH_CODE((0 == result),
				"Failed to populate SCLK during PopulateNewDPMClocksStates Function!",
				वापस result);
	पूर्ण

	अगर (data->need_update_smu7_dpm_table &
			(DPMTABLE_OD_UPDATE_MCLK + DPMTABLE_UPDATE_MCLK)) अणु
		/*populate MCLK dpm table to SMU7 */
		result = smum_populate_all_memory_levels(hwmgr);
		PP_ASSERT_WITH_CODE((0 == result),
				"Failed to populate MCLK during PopulateNewDPMClocksStates Function!",
				वापस result);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक smu7_trim_single_dpm_states(काष्ठा pp_hwmgr *hwmgr,
			  काष्ठा smu7_single_dpm_table *dpm_table,
			uपूर्णांक32_t low_limit, uपूर्णांक32_t high_limit)
अणु
	uपूर्णांक32_t i;

	/* क्रमce the trim अगर mclk_चयनing is disabled to prevent flicker */
	bool क्रमce_trim = (low_limit == high_limit);
	क्रम (i = 0; i < dpm_table->count; i++) अणु
	/*skip the trim अगर od is enabled*/
		अगर ((!hwmgr->od_enabled || क्रमce_trim)
			&& (dpm_table->dpm_levels[i].value < low_limit
			|| dpm_table->dpm_levels[i].value > high_limit))
			dpm_table->dpm_levels[i].enabled = false;
		अन्यथा
			dpm_table->dpm_levels[i].enabled = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_trim_dpm_states(काष्ठा pp_hwmgr *hwmgr,
		स्थिर काष्ठा smu7_घातer_state *smu7_ps)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t high_limit_count;

	PP_ASSERT_WITH_CODE((smu7_ps->perक्रमmance_level_count >= 1),
			"power state did not have any performance level",
			वापस -EINVAL);

	high_limit_count = (1 == smu7_ps->perक्रमmance_level_count) ? 0 : 1;

	smu7_trim_single_dpm_states(hwmgr,
			&(data->dpm_table.sclk_table),
			smu7_ps->perक्रमmance_levels[0].engine_घड़ी,
			smu7_ps->perक्रमmance_levels[high_limit_count].engine_घड़ी);

	smu7_trim_single_dpm_states(hwmgr,
			&(data->dpm_table.mclk_table),
			smu7_ps->perक्रमmance_levels[0].memory_घड़ी,
			smu7_ps->perक्रमmance_levels[high_limit_count].memory_घड़ी);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_generate_dpm_level_enable_mask(
		काष्ठा pp_hwmgr *hwmgr, स्थिर व्योम *input)
अणु
	पूर्णांक result = 0;
	स्थिर काष्ठा phm_set_घातer_state_input *states =
			(स्थिर काष्ठा phm_set_घातer_state_input *)input;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	स्थिर काष्ठा smu7_घातer_state *smu7_ps =
			cast_स्थिर_phw_smu7_घातer_state(states->pnew_state);


	result = smu7_trim_dpm_states(hwmgr, smu7_ps);
	अगर (result)
		वापस result;

	data->dpm_level_enable_mask.sclk_dpm_enable_mask =
			phm_get_dpm_level_enable_mask_value(&data->dpm_table.sclk_table);
	data->dpm_level_enable_mask.mclk_dpm_enable_mask =
			phm_get_dpm_level_enable_mask_value(&data->dpm_table.mclk_table);
	data->dpm_level_enable_mask.pcie_dpm_enable_mask =
			phm_get_dpm_level_enable_mask_value(&data->dpm_table.pcie_speed_table);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_unमुक्तze_sclk_mclk_dpm(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (0 == data->need_update_smu7_dpm_table)
		वापस 0;

	अगर ((0 == data->sclk_dpm_key_disabled) &&
		(data->need_update_smu7_dpm_table &
		(DPMTABLE_OD_UPDATE_SCLK + DPMTABLE_UPDATE_SCLK))) अणु

		PP_ASSERT_WITH_CODE(true == smum_is_dpm_running(hwmgr),
				"Trying to Unfreeze SCLK DPM when DPM is disabled",
				);
		PP_ASSERT_WITH_CODE(0 == smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_SCLKDPM_Unमुक्तzeLevel,
				शून्य),
			"Failed to unfreeze SCLK DPM during UnFreezeSclkMclkDPM Function!",
			वापस -EINVAL);
	पूर्ण

	अगर ((0 == data->mclk_dpm_key_disabled) &&
		!data->mclk_ignore_संकेत &&
		(data->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_MCLK)) अणु

		PP_ASSERT_WITH_CODE(true == smum_is_dpm_running(hwmgr),
				"Trying to Unfreeze MCLK DPM when DPM is disabled",
				);
		PP_ASSERT_WITH_CODE(0 == smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_MCLKDPM_Unमुक्तzeLevel,
				शून्य),
		    "Failed to unfreeze MCLK DPM during UnFreezeSclkMclkDPM Function!",
		    वापस -EINVAL);
	पूर्ण

	data->need_update_smu7_dpm_table &= DPMTABLE_OD_UPDATE_VDDC;

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_notअगरy_link_speed_change_after_state_change(
		काष्ठा pp_hwmgr *hwmgr, स्थिर व्योम *input)
अणु
	स्थिर काष्ठा phm_set_घातer_state_input *states =
			(स्थिर काष्ठा phm_set_घातer_state_input *)input;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	स्थिर काष्ठा smu7_घातer_state *smu7_ps =
			cast_स्थिर_phw_smu7_घातer_state(states->pnew_state);
	uपूर्णांक16_t target_link_speed = smu7_get_maximum_link_speed(hwmgr, smu7_ps);
	uपूर्णांक8_t  request;

	अगर (data->pspp_notअगरy_required) अणु
		अगर (target_link_speed == PP_PCIEGen3)
			request = PCIE_PERF_REQ_GEN3;
		अन्यथा अगर (target_link_speed == PP_PCIEGen2)
			request = PCIE_PERF_REQ_GEN2;
		अन्यथा
			request = PCIE_PERF_REQ_GEN1;

		अगर (request == PCIE_PERF_REQ_GEN1 &&
				smu7_get_current_pcie_speed(hwmgr) > 0)
			वापस 0;

#अगर_घोषित CONFIG_ACPI
		अगर (amdgpu_acpi_pcie_perक्रमmance_request(hwmgr->adev, request, false)) अणु
			अगर (PP_PCIEGen2 == target_link_speed)
				pr_info("PSPP request to switch to Gen2 from Gen3 Failed!");
			अन्यथा
				pr_info("PSPP request to switch to Gen1 from Gen2 Failed!");
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_notअगरy_no_display(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस (smum_send_msg_to_smc(hwmgr, (PPSMC_Msg)PPSMC_NoDisplay, शून्य) == 0) ?  0 : -EINVAL;
पूर्ण

अटल पूर्णांक smu7_notअगरy_has_display(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (hwmgr->feature_mask & PP_VBI_TIME_SUPPORT_MASK) अणु
		अगर (hwmgr->chip_id == CHIP_VEGAM)
			smum_send_msg_to_smc_with_parameter(hwmgr,
					(PPSMC_Msg)PPSMC_MSG_SetVBITimeout_VEGAM, data->frame_समय_x2,
					शून्य);
		अन्यथा
			smum_send_msg_to_smc_with_parameter(hwmgr,
					(PPSMC_Msg)PPSMC_MSG_SetVBITimeout, data->frame_समय_x2,
					शून्य);
		data->last_sent_vbi_समयout = data->frame_समय_x2;
	पूर्ण

	वापस (smum_send_msg_to_smc(hwmgr, (PPSMC_Msg)PPSMC_HasDisplay, शून्य) == 0) ?  0 : -EINVAL;
पूर्ण

अटल पूर्णांक smu7_notअगरy_smc_display(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	पूर्णांक result = 0;

	अगर (data->mclk_ignore_संकेत)
		result = smu7_notअगरy_no_display(hwmgr);
	अन्यथा
		result = smu7_notअगरy_has_display(hwmgr);

	वापस result;
पूर्ण

अटल पूर्णांक smu7_set_घातer_state_tasks(काष्ठा pp_hwmgr *hwmgr, स्थिर व्योम *input)
अणु
	पूर्णांक पंचांगp_result, result = 0;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	पंचांगp_result = smu7_find_dpm_states_घड़ीs_in_dpm_table(hwmgr, input);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to find DPM states clocks in DPM table!",
			result = पंचांगp_result);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_PCIEPerक्रमmanceRequest)) अणु
		पंचांगp_result =
			smu7_request_link_speed_change_beक्रमe_state_change(hwmgr, input);
		PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
				"Failed to request link speed change before state change!",
				result = पंचांगp_result);
	पूर्ण

	पंचांगp_result = smu7_मुक्तze_sclk_mclk_dpm(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to freeze SCLK MCLK DPM!", result = पंचांगp_result);

	पंचांगp_result = smu7_populate_and_upload_sclk_mclk_dpm_levels(hwmgr, input);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to populate and upload SCLK MCLK DPM levels!",
			result = पंचांगp_result);

	/*
	 * If a custom pp table is loaded, set DPMTABLE_OD_UPDATE_VDDC flag.
	 * That effectively disables AVFS feature.
	 */
	अगर (hwmgr->hardcode_pp_table != शून्य)
		data->need_update_smu7_dpm_table |= DPMTABLE_OD_UPDATE_VDDC;

	पंचांगp_result = smu7_update_avfs(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to update avfs voltages!",
			result = पंचांगp_result);

	पंचांगp_result = smu7_generate_dpm_level_enable_mask(hwmgr, input);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to generate DPM level enabled mask!",
			result = पंचांगp_result);

	पंचांगp_result = smum_update_sclk_threshold(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to update SCLK threshold!",
			result = पंचांगp_result);

	पंचांगp_result = smu7_unमुक्तze_sclk_mclk_dpm(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to unfreeze SCLK MCLK DPM!",
			result = पंचांगp_result);

	पंचांगp_result = smu7_upload_dpm_level_enable_mask(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to upload DPM level enabled mask!",
			result = पंचांगp_result);

	पंचांगp_result = smu7_notअगरy_smc_display(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to notify smc display settings!",
			result = पंचांगp_result);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_PCIEPerक्रमmanceRequest)) अणु
		पंचांगp_result =
			smu7_notअगरy_link_speed_change_after_state_change(hwmgr, input);
		PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
				"Failed to notify link speed change after state change!",
				result = पंचांगp_result);
	पूर्ण
	data->apply_optimized_settings = false;
	वापस result;
पूर्ण

अटल पूर्णांक smu7_set_max_fan_pwm_output(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t us_max_fan_pwm)
अणु
	hwmgr->thermal_controller.
	advanceFanControlParameters.usMaxFanPWM = us_max_fan_pwm;

	वापस smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetFanPwmMax, us_max_fan_pwm,
			शून्य);
पूर्ण

अटल पूर्णांक
smu7_notअगरy_smc_display_config_after_ps_adjusपंचांगent(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस 0;
पूर्ण

/**
 * smu7_program_display_gap - Programs the display gap
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Return:   always OK
 */
अटल पूर्णांक smu7_program_display_gap(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t display_gap = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixCG_DISPLAY_GAP_CNTL);
	uपूर्णांक32_t display_gap2;
	uपूर्णांक32_t pre_vbi_समय_in_us;
	uपूर्णांक32_t frame_समय_in_us;
	uपूर्णांक32_t ref_घड़ी, refresh_rate;

	display_gap = PHM_SET_FIELD(display_gap, CG_DISPLAY_GAP_CNTL, DISP_GAP, (hwmgr->display_config->num_display > 0) ? DISPLAY_GAP_VBLANK_OR_WM : DISPLAY_GAP_IGNORE);
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixCG_DISPLAY_GAP_CNTL, display_gap);

	ref_घड़ी =  amdgpu_asic_get_xclk((काष्ठा amdgpu_device *)hwmgr->adev);
	refresh_rate = hwmgr->display_config->vrefresh;

	अगर (0 == refresh_rate)
		refresh_rate = 60;

	frame_समय_in_us = 1000000 / refresh_rate;

	pre_vbi_समय_in_us = frame_समय_in_us - 200 - hwmgr->display_config->min_vblank_समय;

	data->frame_समय_x2 = frame_समय_in_us * 2 / 100;

	अगर (data->frame_समय_x2 < 280) अणु
		pr_debug("%s: enforce minimal VBITimeout: %d -> 280\n", __func__, data->frame_समय_x2);
		data->frame_समय_x2 = 280;
	पूर्ण

	display_gap2 = pre_vbi_समय_in_us * (ref_घड़ी / 100);

	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixCG_DISPLAY_GAP_CNTL2, display_gap2);

	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			data->soft_regs_start + smum_get_दुरत्व(hwmgr,
							SMU_SoftRegisters,
							PreVBlankGap), 0x64);

	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			data->soft_regs_start + smum_get_दुरत्व(hwmgr,
							SMU_SoftRegisters,
							VBlankTimeout),
					(frame_समय_in_us - pre_vbi_समय_in_us));

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_display_configuration_changed_task(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस smu7_program_display_gap(hwmgr);
पूर्ण

/**
 * smu7_set_max_fan_rpm_output - Set maximum target operating fan output RPM
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * @us_max_fan_rpm:  max operating fan RPM value.
 * Return:   The response that came from the SMC.
 */
अटल पूर्णांक smu7_set_max_fan_rpm_output(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t us_max_fan_rpm)
अणु
	hwmgr->thermal_controller.
	advanceFanControlParameters.usMaxFanRPM = us_max_fan_rpm;

	वापस smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetFanRpmMax, us_max_fan_rpm,
			शून्य);
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs smu7_irq_funcs = अणु
	.process = phm_irq_process,
पूर्ण;

अटल पूर्णांक smu7_रेजिस्टर_irq_handlers(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_irq_src *source =
		kzalloc(माप(काष्ठा amdgpu_irq_src), GFP_KERNEL);

	अगर (!source)
		वापस -ENOMEM;

	source->funcs = &smu7_irq_funcs;

	amdgpu_irq_add_id((काष्ठा amdgpu_device *)(hwmgr->adev),
			AMDGPU_IRQ_CLIENTID_LEGACY,
			VISLANDS30_IV_SRCID_CG_TSS_THERMAL_LOW_TO_HIGH,
			source);
	amdgpu_irq_add_id((काष्ठा amdgpu_device *)(hwmgr->adev),
			AMDGPU_IRQ_CLIENTID_LEGACY,
			VISLANDS30_IV_SRCID_CG_TSS_THERMAL_HIGH_TO_LOW,
			source);

	/* Register CTF(GPIO_19) पूर्णांकerrupt */
	amdgpu_irq_add_id((काष्ठा amdgpu_device *)(hwmgr->adev),
			AMDGPU_IRQ_CLIENTID_LEGACY,
			VISLANDS30_IV_SRCID_GPIO_19,
			source);

	वापस 0;
पूर्ण

अटल bool
smu7_check_smc_update_required_क्रम_display_configuration(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	bool is_update_required = false;

	अगर (data->display_timing.num_existing_displays != hwmgr->display_config->num_display)
		is_update_required = true;

	अगर (data->display_timing.vrefresh != hwmgr->display_config->vrefresh)
		is_update_required = true;

	अगर (hwmgr->chip_id >= CHIP_POLARIS10 &&
	    hwmgr->chip_id <= CHIP_VEGAM &&
	    data->last_sent_vbi_समयout != data->frame_समय_x2)
		is_update_required = true;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_SclkDeepSleep)) अणु
		अगर (data->display_timing.min_घड़ी_in_sr != hwmgr->display_config->min_core_set_घड़ी_in_sr &&
			(data->display_timing.min_घड़ी_in_sr >= SMU7_MINIMUM_ENGINE_CLOCK ||
			hwmgr->display_config->min_core_set_घड़ी_in_sr >= SMU7_MINIMUM_ENGINE_CLOCK))
			is_update_required = true;
	पूर्ण
	वापस is_update_required;
पूर्ण

अटल अंतरभूत bool smu7_are_घातer_levels_equal(स्थिर काष्ठा smu7_perक्रमmance_level *pl1,
							   स्थिर काष्ठा smu7_perक्रमmance_level *pl2)
अणु
	वापस ((pl1->memory_घड़ी == pl2->memory_घड़ी) &&
		  (pl1->engine_घड़ी == pl2->engine_घड़ी) &&
		  (pl1->pcie_gen == pl2->pcie_gen) &&
		  (pl1->pcie_lane == pl2->pcie_lane));
पूर्ण

अटल पूर्णांक smu7_check_states_equal(काष्ठा pp_hwmgr *hwmgr,
		स्थिर काष्ठा pp_hw_घातer_state *pstate1,
		स्थिर काष्ठा pp_hw_घातer_state *pstate2, bool *equal)
अणु
	स्थिर काष्ठा smu7_घातer_state *psa;
	स्थिर काष्ठा smu7_घातer_state *psb;
	पूर्णांक i;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (pstate1 == शून्य || pstate2 == शून्य || equal == शून्य)
		वापस -EINVAL;

	psa = cast_स्थिर_phw_smu7_घातer_state(pstate1);
	psb = cast_स्थिर_phw_smu7_घातer_state(pstate2);
	/* If the two states करोn't even have the same number of perक्रमmance levels they cannot be the same state. */
	अगर (psa->perक्रमmance_level_count != psb->perक्रमmance_level_count) अणु
		*equal = false;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < psa->perक्रमmance_level_count; i++) अणु
		अगर (!smu7_are_घातer_levels_equal(&(psa->perक्रमmance_levels[i]), &(psb->perक्रमmance_levels[i]))) अणु
			/* If we have found even one perक्रमmance level pair that is dअगरferent the states are dअगरferent. */
			*equal = false;
			वापस 0;
		पूर्ण
	पूर्ण

	/* If all perक्रमmance levels are the same try to use the UVD घड़ीs to अवरोध the tie.*/
	*equal = ((psa->uvd_clks.vclk == psb->uvd_clks.vclk) && (psa->uvd_clks.dclk == psb->uvd_clks.dclk));
	*equal &= ((psa->vce_clks.evclk == psb->vce_clks.evclk) && (psa->vce_clks.ecclk == psb->vce_clks.ecclk));
	*equal &= (psa->sclk_threshold == psb->sclk_threshold);
	/* For OD call, set value based on flag */
	*equal &= !(data->need_update_smu7_dpm_table & (DPMTABLE_OD_UPDATE_SCLK |
							DPMTABLE_OD_UPDATE_MCLK |
							DPMTABLE_OD_UPDATE_VDDC));

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_check_mc_firmware(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	uपूर्णांक32_t पंचांगp;

	/* Read MC indirect रेजिस्टर offset 0x9F bits [3:0] to see
	 * अगर VBIOS has alपढ़ोy loaded a full version of MC ucode
	 * or not.
	 */

	smu7_get_mc_microcode_version(hwmgr);

	data->need_दीर्घ_memory_training = false;

	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_IO_DEBUG_INDEX,
							ixMC_IO_DEBUG_UP_13);
	पंचांगp = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_IO_DEBUG_DATA);

	अगर (पंचांगp & (1 << 23)) अणु
		data->mem_latency_high = MEM_LATENCY_HIGH;
		data->mem_latency_low = MEM_LATENCY_LOW;
		अगर ((hwmgr->chip_id == CHIP_POLARIS10) ||
		    (hwmgr->chip_id == CHIP_POLARIS11) ||
		    (hwmgr->chip_id == CHIP_POLARIS12))
			smum_send_msg_to_smc(hwmgr, PPSMC_MSG_EnableFFC, शून्य);
	पूर्ण अन्यथा अणु
		data->mem_latency_high = 330;
		data->mem_latency_low = 330;
		अगर ((hwmgr->chip_id == CHIP_POLARIS10) ||
		    (hwmgr->chip_id == CHIP_POLARIS11) ||
		    (hwmgr->chip_id == CHIP_POLARIS12))
			smum_send_msg_to_smc(hwmgr, PPSMC_MSG_DisableFFC, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_पढ़ो_घड़ी_रेजिस्टरs(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL         =
		cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixCG_SPLL_FUNC_CNTL);
	data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL_2       =
		cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixCG_SPLL_FUNC_CNTL_2);
	data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL_3       =
		cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixCG_SPLL_FUNC_CNTL_3);
	data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL_4       =
		cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixCG_SPLL_FUNC_CNTL_4);
	data->घड़ी_रेजिस्टरs.vCG_SPLL_SPREAD_SPECTRUM   =
		cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixCG_SPLL_SPREAD_SPECTRUM);
	data->घड़ी_रेजिस्टरs.vCG_SPLL_SPREAD_SPECTRUM_2 =
		cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixCG_SPLL_SPREAD_SPECTRUM_2);
	data->घड़ी_रेजिस्टरs.vDLL_CNTL                  =
		cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmDLL_CNTL);
	data->घड़ी_रेजिस्टरs.vMCLK_PWRMGT_CNTL          =
		cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMCLK_PWRMGT_CNTL);
	data->घड़ी_रेजिस्टरs.vMPLL_AD_FUNC_CNTL         =
		cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMPLL_AD_FUNC_CNTL);
	data->घड़ी_रेजिस्टरs.vMPLL_DQ_FUNC_CNTL         =
		cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMPLL_DQ_FUNC_CNTL);
	data->घड़ी_रेजिस्टरs.vMPLL_FUNC_CNTL            =
		cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMPLL_FUNC_CNTL);
	data->घड़ी_रेजिस्टरs.vMPLL_FUNC_CNTL_1          =
		cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMPLL_FUNC_CNTL_1);
	data->घड़ी_रेजिस्टरs.vMPLL_FUNC_CNTL_2          =
		cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMPLL_FUNC_CNTL_2);
	data->घड़ी_रेजिस्टरs.vMPLL_SS1                  =
		cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMPLL_SS1);
	data->घड़ी_रेजिस्टरs.vMPLL_SS2                  =
		cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMPLL_SS2);
	वापस 0;

पूर्ण

/**
 * smu7_get_memory_type - Find out अगर memory is GDDR5.
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Return:   always 0
 */
अटल पूर्णांक smu7_get_memory_type(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	data->is_memory_gddr5 = (adev->gmc.vram_type == AMDGPU_VRAM_TYPE_GDDR5);

	वापस 0;
पूर्ण

/**
 * smu7_enable_acpi_घातer_management - Enables Dynamic Power Management by SMC
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Return:   always 0
 */
अटल पूर्णांक smu7_enable_acpi_घातer_management(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			GENERAL_PWRMGT, STATIC_PM_EN, 1);

	वापस 0;
पूर्ण

/**
 * smu7_init_घातer_gate_state - Initialize PowerGating States क्रम dअगरferent engines
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Return:   always 0
 */
अटल पूर्णांक smu7_init_घातer_gate_state(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	data->uvd_घातer_gated = false;
	data->vce_घातer_gated = false;

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_init_sclk_threshold(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	data->low_sclk_पूर्णांकerrupt_threshold = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_setup_asic_task(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक पंचांगp_result, result = 0;

	smu7_check_mc_firmware(hwmgr);

	पंचांगp_result = smu7_पढ़ो_घड़ी_रेजिस्टरs(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to read clock registers!", result = पंचांगp_result);

	पंचांगp_result = smu7_get_memory_type(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to get memory type!", result = पंचांगp_result);

	पंचांगp_result = smu7_enable_acpi_घातer_management(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to enable ACPI power management!", result = पंचांगp_result);

	पंचांगp_result = smu7_init_घातer_gate_state(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to init power gate state!", result = पंचांगp_result);

	पंचांगp_result = smu7_get_mc_microcode_version(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to get MC microcode version!", result = पंचांगp_result);

	पंचांगp_result = smu7_init_sclk_threshold(hwmgr);
	PP_ASSERT_WITH_CODE((0 == पंचांगp_result),
			"Failed to init sclk threshold!", result = पंचांगp_result);

	वापस result;
पूर्ण

अटल पूर्णांक smu7_क्रमce_घड़ी_level(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत pp_घड़ी_प्रकारype type, uपूर्णांक32_t mask)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (mask == 0)
		वापस -EINVAL;

	चयन (type) अणु
	हाल PP_SCLK:
		अगर (!data->sclk_dpm_key_disabled)
			smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SCLKDPM_SetEnabledMask,
					data->dpm_level_enable_mask.sclk_dpm_enable_mask & mask,
					शून्य);
		अवरोध;
	हाल PP_MCLK:
		अगर (!data->mclk_dpm_key_disabled)
			smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_MCLKDPM_SetEnabledMask,
					data->dpm_level_enable_mask.mclk_dpm_enable_mask & mask,
					शून्य);
		अवरोध;
	हाल PP_PCIE:
	अणु
		uपूर्णांक32_t पंचांगp = mask & data->dpm_level_enable_mask.pcie_dpm_enable_mask;

		अगर (!data->pcie_dpm_key_disabled) अणु
			अगर (fls(पंचांगp) != ffs(पंचांगp))
				smum_send_msg_to_smc(hwmgr, PPSMC_MSG_PCIeDPM_UnForceLevel,
						शून्य);
			अन्यथा
				smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_PCIeDPM_ForceLevel,
					fls(पंचांगp) - 1,
					शून्य);
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_prपूर्णांक_घड़ी_levels(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत pp_घड़ी_प्रकारype type, अक्षर *buf)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_single_dpm_table *sclk_table = &(data->dpm_table.sclk_table);
	काष्ठा smu7_single_dpm_table *mclk_table = &(data->dpm_table.mclk_table);
	काष्ठा smu7_single_dpm_table *pcie_table = &(data->dpm_table.pcie_speed_table);
	काष्ठा smu7_odn_dpm_table *odn_table = &(data->odn_dpm_table);
	काष्ठा phm_odn_घड़ी_levels *odn_sclk_table = &(odn_table->odn_core_घड़ी_dpm_levels);
	काष्ठा phm_odn_घड़ी_levels *odn_mclk_table = &(odn_table->odn_memory_घड़ी_dpm_levels);
	पूर्णांक i, now, size = 0;
	uपूर्णांक32_t घड़ी, pcie_speed;

	चयन (type) अणु
	हाल PP_SCLK:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_API_GetSclkFrequency, &घड़ी);

		क्रम (i = 0; i < sclk_table->count; i++) अणु
			अगर (घड़ी > sclk_table->dpm_levels[i].value)
				जारी;
			अवरोध;
		पूर्ण
		now = i;

		क्रम (i = 0; i < sclk_table->count; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
					i, sclk_table->dpm_levels[i].value / 100,
					(i == now) ? "*" : "");
		अवरोध;
	हाल PP_MCLK:
		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_API_GetMclkFrequency, &घड़ी);

		क्रम (i = 0; i < mclk_table->count; i++) अणु
			अगर (घड़ी > mclk_table->dpm_levels[i].value)
				जारी;
			अवरोध;
		पूर्ण
		now = i;

		क्रम (i = 0; i < mclk_table->count; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
					i, mclk_table->dpm_levels[i].value / 100,
					(i == now) ? "*" : "");
		अवरोध;
	हाल PP_PCIE:
		pcie_speed = smu7_get_current_pcie_speed(hwmgr);
		क्रम (i = 0; i < pcie_table->count; i++) अणु
			अगर (pcie_speed != pcie_table->dpm_levels[i].value)
				जारी;
			अवरोध;
		पूर्ण
		now = i;

		क्रम (i = 0; i < pcie_table->count; i++)
			size += प्र_लिखो(buf + size, "%d: %s %s\n", i,
					(pcie_table->dpm_levels[i].value == 0) ? "2.5GT/s, x8" :
					(pcie_table->dpm_levels[i].value == 1) ? "5.0GT/s, x16" :
					(pcie_table->dpm_levels[i].value == 2) ? "8.0GT/s, x16" : "",
					(i == now) ? "*" : "");
		अवरोध;
	हाल OD_SCLK:
		अगर (hwmgr->od_enabled) अणु
			size = प्र_लिखो(buf, "%s:\n", "OD_SCLK");
			क्रम (i = 0; i < odn_sclk_table->num_of_pl; i++)
				size += प्र_लिखो(buf + size, "%d: %10uMHz %10umV\n",
					i, odn_sclk_table->entries[i].घड़ी/100,
					odn_sclk_table->entries[i].vddc);
		पूर्ण
		अवरोध;
	हाल OD_MCLK:
		अगर (hwmgr->od_enabled) अणु
			size = प्र_लिखो(buf, "%s:\n", "OD_MCLK");
			क्रम (i = 0; i < odn_mclk_table->num_of_pl; i++)
				size += प्र_लिखो(buf + size, "%d: %10uMHz %10umV\n",
					i, odn_mclk_table->entries[i].घड़ी/100,
					odn_mclk_table->entries[i].vddc);
		पूर्ण
		अवरोध;
	हाल OD_RANGE:
		अगर (hwmgr->od_enabled) अणु
			size = प्र_लिखो(buf, "%s:\n", "OD_RANGE");
			size += प्र_लिखो(buf + size, "SCLK: %7uMHz %10uMHz\n",
				data->golden_dpm_table.sclk_table.dpm_levels[0].value/100,
				hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock/100);
			size += प्र_लिखो(buf + size, "MCLK: %7uMHz %10uMHz\n",
				data->golden_dpm_table.mclk_table.dpm_levels[0].value/100,
				hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock/100);
			size += प्र_लिखो(buf + size, "VDDC: %7umV %11umV\n",
				data->odn_dpm_table.min_vddc,
				data->odn_dpm_table.max_vddc);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस size;
पूर्ण

अटल व्योम smu7_set_fan_control_mode(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t mode)
अणु
	चयन (mode) अणु
	हाल AMD_FAN_CTRL_NONE:
		smu7_fan_ctrl_set_fan_speed_percent(hwmgr, 100);
		अवरोध;
	हाल AMD_FAN_CTRL_MANUAL:
		अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_MicrocodeFanControl))
			smu7_fan_ctrl_stop_smc_fan_control(hwmgr);
		अवरोध;
	हाल AMD_FAN_CTRL_AUTO:
		अगर (!smu7_fan_ctrl_set_अटल_mode(hwmgr, mode))
			smu7_fan_ctrl_start_smc_fan_control(hwmgr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल uपूर्णांक32_t smu7_get_fan_control_mode(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस hwmgr->fan_ctrl_enabled ? AMD_FAN_CTRL_AUTO : AMD_FAN_CTRL_MANUAL;
पूर्ण

अटल पूर्णांक smu7_get_sclk_od(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_single_dpm_table *sclk_table = &(data->dpm_table.sclk_table);
	काष्ठा smu7_single_dpm_table *golden_sclk_table =
			&(data->golden_dpm_table.sclk_table);
	पूर्णांक value = sclk_table->dpm_levels[sclk_table->count - 1].value;
	पूर्णांक golden_value = golden_sclk_table->dpm_levels
			[golden_sclk_table->count - 1].value;

	value -= golden_value;
	value = DIV_ROUND_UP(value * 100, golden_value);

	वापस value;
पूर्ण

अटल पूर्णांक smu7_set_sclk_od(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t value)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_single_dpm_table *golden_sclk_table =
			&(data->golden_dpm_table.sclk_table);
	काष्ठा pp_घातer_state  *ps;
	काष्ठा smu7_घातer_state  *smu7_ps;

	अगर (value > 20)
		value = 20;

	ps = hwmgr->request_ps;

	अगर (ps == शून्य)
		वापस -EINVAL;

	smu7_ps = cast_phw_smu7_घातer_state(&ps->hardware);

	smu7_ps->perक्रमmance_levels[smu7_ps->perक्रमmance_level_count - 1].engine_घड़ी =
			golden_sclk_table->dpm_levels[golden_sclk_table->count - 1].value *
			value / 100 +
			golden_sclk_table->dpm_levels[golden_sclk_table->count - 1].value;

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_mclk_od(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_single_dpm_table *mclk_table = &(data->dpm_table.mclk_table);
	काष्ठा smu7_single_dpm_table *golden_mclk_table =
			&(data->golden_dpm_table.mclk_table);
        पूर्णांक value = mclk_table->dpm_levels[mclk_table->count - 1].value;
	पूर्णांक golden_value = golden_mclk_table->dpm_levels
			[golden_mclk_table->count - 1].value;

	value -= golden_value;
	value = DIV_ROUND_UP(value * 100, golden_value);

	वापस value;
पूर्ण

अटल पूर्णांक smu7_set_mclk_od(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t value)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_single_dpm_table *golden_mclk_table =
			&(data->golden_dpm_table.mclk_table);
	काष्ठा pp_घातer_state  *ps;
	काष्ठा smu7_घातer_state  *smu7_ps;

	अगर (value > 20)
		value = 20;

	ps = hwmgr->request_ps;

	अगर (ps == शून्य)
		वापस -EINVAL;

	smu7_ps = cast_phw_smu7_घातer_state(&ps->hardware);

	smu7_ps->perक्रमmance_levels[smu7_ps->perक्रमmance_level_count - 1].memory_घड़ी =
			golden_mclk_table->dpm_levels[golden_mclk_table->count - 1].value *
			value / 100 +
			golden_mclk_table->dpm_levels[golden_mclk_table->count - 1].value;

	वापस 0;
पूर्ण


अटल पूर्णांक smu7_get_sclks(काष्ठा pp_hwmgr *hwmgr, काष्ठा amd_pp_घड़ीs *घड़ीs)
अणु
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)hwmgr->pptable;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_sclk_table = शून्य;
	काष्ठा phm_घड़ी_voltage_dependency_table *sclk_table;
	पूर्णांक i;

	अगर (hwmgr->pp_table_version == PP_TABLE_V1) अणु
		अगर (table_info == शून्य || table_info->vdd_dep_on_sclk == शून्य)
			वापस -EINVAL;
		dep_sclk_table = table_info->vdd_dep_on_sclk;
		क्रम (i = 0; i < dep_sclk_table->count; i++)
			घड़ीs->घड़ी[i] = dep_sclk_table->entries[i].clk * 10;
		घड़ीs->count = dep_sclk_table->count;
	पूर्ण अन्यथा अगर (hwmgr->pp_table_version == PP_TABLE_V0) अणु
		sclk_table = hwmgr->dyn_state.vddc_dependency_on_sclk;
		क्रम (i = 0; i < sclk_table->count; i++)
			घड़ीs->घड़ी[i] = sclk_table->entries[i].clk * 10;
		घड़ीs->count = sclk_table->count;
	पूर्ण

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t smu7_get_mem_latency(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t clk)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (clk >= MEM_FREQ_LOW_LATENCY && clk < MEM_FREQ_HIGH_LATENCY)
		वापस data->mem_latency_high;
	अन्यथा अगर (clk >= MEM_FREQ_HIGH_LATENCY)
		वापस data->mem_latency_low;
	अन्यथा
		वापस MEM_LATENCY_ERR;
पूर्ण

अटल पूर्णांक smu7_get_mclks(काष्ठा pp_hwmgr *hwmgr, काष्ठा amd_pp_घड़ीs *घड़ीs)
अणु
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)hwmgr->pptable;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_mclk_table;
	पूर्णांक i;
	काष्ठा phm_घड़ी_voltage_dependency_table *mclk_table;

	अगर (hwmgr->pp_table_version == PP_TABLE_V1) अणु
		अगर (table_info == शून्य)
			वापस -EINVAL;
		dep_mclk_table = table_info->vdd_dep_on_mclk;
		क्रम (i = 0; i < dep_mclk_table->count; i++) अणु
			घड़ीs->घड़ी[i] = dep_mclk_table->entries[i].clk * 10;
			घड़ीs->latency[i] = smu7_get_mem_latency(hwmgr,
						dep_mclk_table->entries[i].clk);
		पूर्ण
		घड़ीs->count = dep_mclk_table->count;
	पूर्ण अन्यथा अगर (hwmgr->pp_table_version == PP_TABLE_V0) अणु
		mclk_table = hwmgr->dyn_state.vddc_dependency_on_mclk;
		क्रम (i = 0; i < mclk_table->count; i++)
			घड़ीs->घड़ी[i] = mclk_table->entries[i].clk * 10;
		घड़ीs->count = mclk_table->count;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_घड़ी_by_type(काष्ठा pp_hwmgr *hwmgr, क्रमागत amd_pp_घड़ी_प्रकारype type,
						काष्ठा amd_pp_घड़ीs *घड़ीs)
अणु
	चयन (type) अणु
	हाल amd_pp_sys_घड़ी:
		smu7_get_sclks(hwmgr, घड़ीs);
		अवरोध;
	हाल amd_pp_mem_घड़ी:
		smu7_get_mclks(hwmgr, घड़ीs);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_sclks_with_latency(काष्ठा pp_hwmgr *hwmgr,
				       काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)hwmgr->pptable;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_sclk_table =
			table_info->vdd_dep_on_sclk;
	पूर्णांक i;

	घड़ीs->num_levels = 0;
	क्रम (i = 0; i < dep_sclk_table->count; i++) अणु
		अगर (dep_sclk_table->entries[i].clk) अणु
			घड़ीs->data[घड़ीs->num_levels].घड़ीs_in_khz =
				dep_sclk_table->entries[i].clk * 10;
			घड़ीs->num_levels++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_mclks_with_latency(काष्ठा pp_hwmgr *hwmgr,
				       काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)hwmgr->pptable;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_mclk_table =
			table_info->vdd_dep_on_mclk;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	पूर्णांक i;

	घड़ीs->num_levels = 0;
	data->mclk_latency_table.count = 0;
	क्रम (i = 0; i < dep_mclk_table->count; i++) अणु
		अगर (dep_mclk_table->entries[i].clk) अणु
			घड़ीs->data[घड़ीs->num_levels].घड़ीs_in_khz =
					dep_mclk_table->entries[i].clk * 10;
			data->mclk_latency_table.entries[data->mclk_latency_table.count].frequency =
					dep_mclk_table->entries[i].clk;
			घड़ीs->data[घड़ीs->num_levels].latency_in_us =
				data->mclk_latency_table.entries[data->mclk_latency_table.count].latency =
					smu7_get_mem_latency(hwmgr, dep_mclk_table->entries[i].clk);
			घड़ीs->num_levels++;
			data->mclk_latency_table.count++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_घड़ी_by_type_with_latency(काष्ठा pp_hwmgr *hwmgr,
					       क्रमागत amd_pp_घड़ी_प्रकारype type,
					       काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	अगर (!(hwmgr->chip_id >= CHIP_POLARIS10 &&
	      hwmgr->chip_id <= CHIP_VEGAM))
		वापस -EINVAL;

	चयन (type) अणु
	हाल amd_pp_sys_घड़ी:
		smu7_get_sclks_with_latency(hwmgr, घड़ीs);
		अवरोध;
	हाल amd_pp_mem_घड़ी:
		smu7_get_mclks_with_latency(hwmgr, घड़ीs);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_set_watermarks_क्रम_घड़ीs_ranges(काष्ठा pp_hwmgr *hwmgr,
						 व्योम *घड़ी_range)
अणु
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)hwmgr->pptable;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_mclk_table =
			table_info->vdd_dep_on_mclk;
	काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table *dep_sclk_table =
			table_info->vdd_dep_on_sclk;
	काष्ठा polaris10_smumgr *smu_data =
			(काष्ठा polaris10_smumgr *)(hwmgr->smu_backend);
	SMU74_Discrete_DpmTable  *table = &(smu_data->smc_state_table);
	काष्ठा dm_pp_wm_sets_with_घड़ी_ranges *watermarks =
			(काष्ठा dm_pp_wm_sets_with_घड़ी_ranges *)घड़ी_range;
	uपूर्णांक32_t i, j, k;
	bool valid_entry;

	अगर (!(hwmgr->chip_id >= CHIP_POLARIS10 &&
	      hwmgr->chip_id <= CHIP_VEGAM))
		वापस -EINVAL;

	क्रम (i = 0; i < dep_mclk_table->count; i++) अणु
		क्रम (j = 0; j < dep_sclk_table->count; j++) अणु
			valid_entry = false;
			क्रम (k = 0; k < watermarks->num_wm_sets; k++) अणु
				अगर (dep_sclk_table->entries[i].clk >= watermarks->wm_clk_ranges[k].wm_min_eng_clk_in_khz / 10 &&
				    dep_sclk_table->entries[i].clk < watermarks->wm_clk_ranges[k].wm_max_eng_clk_in_khz / 10 &&
				    dep_mclk_table->entries[i].clk >= watermarks->wm_clk_ranges[k].wm_min_mem_clk_in_khz / 10 &&
				    dep_mclk_table->entries[i].clk < watermarks->wm_clk_ranges[k].wm_max_mem_clk_in_khz / 10) अणु
					valid_entry = true;
					table->DisplayWatermark[i][j] = watermarks->wm_clk_ranges[k].wm_set_id;
					अवरोध;
				पूर्ण
			पूर्ण
			PP_ASSERT_WITH_CODE(valid_entry,
					"Clock is not in range of specified clock range for watermark from DAL!  Using highest water mark set.",
					table->DisplayWatermark[i][j] = watermarks->wm_clk_ranges[k - 1].wm_set_id);
		पूर्ण
	पूर्ण

	वापस smu7_copy_bytes_to_smc(hwmgr,
				      smu_data->smu7_data.dpm_table_start + दुरत्व(SMU74_Discrete_DpmTable, DisplayWatermark),
				      (uपूर्णांक8_t *)table->DisplayWatermark,
				      माप(uपूर्णांक8_t) * SMU74_MAX_LEVELS_MEMORY * SMU74_MAX_LEVELS_GRAPHICS,
				      SMC_RAM_END);
पूर्ण

अटल पूर्णांक smu7_notअगरy_cac_buffer_info(काष्ठा pp_hwmgr *hwmgr,
					uपूर्णांक32_t भव_addr_low,
					uपूर्णांक32_t भव_addr_hi,
					uपूर्णांक32_t mc_addr_low,
					uपूर्णांक32_t mc_addr_hi,
					uपूर्णांक32_t size)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
					data->soft_regs_start +
					smum_get_दुरत्व(hwmgr,
					SMU_SoftRegisters, DRAM_LOG_ADDR_H),
					mc_addr_hi);

	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
					data->soft_regs_start +
					smum_get_दुरत्व(hwmgr,
					SMU_SoftRegisters, DRAM_LOG_ADDR_L),
					mc_addr_low);

	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
					data->soft_regs_start +
					smum_get_दुरत्व(hwmgr,
					SMU_SoftRegisters, DRAM_LOG_PHY_ADDR_H),
					भव_addr_hi);

	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
					data->soft_regs_start +
					smum_get_दुरत्व(hwmgr,
					SMU_SoftRegisters, DRAM_LOG_PHY_ADDR_L),
					भव_addr_low);

	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
					data->soft_regs_start +
					smum_get_दुरत्व(hwmgr,
					SMU_SoftRegisters, DRAM_LOG_BUFF_SIZE),
					size);
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_max_high_घड़ीs(काष्ठा pp_hwmgr *hwmgr,
					काष्ठा amd_pp_simple_घड़ी_info *घड़ीs)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_single_dpm_table *sclk_table = &(data->dpm_table.sclk_table);
	काष्ठा smu7_single_dpm_table *mclk_table = &(data->dpm_table.mclk_table);

	अगर (घड़ीs == शून्य)
		वापस -EINVAL;

	घड़ीs->memory_max_घड़ी = mclk_table->count > 1 ?
				mclk_table->dpm_levels[mclk_table->count-1].value :
				mclk_table->dpm_levels[0].value;
	घड़ीs->engine_max_घड़ी = sclk_table->count > 1 ?
				sclk_table->dpm_levels[sclk_table->count-1].value :
				sclk_table->dpm_levels[0].value;
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_thermal_temperature_range(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा PP_TemperatureRange *thermal_data)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा phm_ppt_v1_inक्रमmation *table_info =
			(काष्ठा phm_ppt_v1_inक्रमmation *)hwmgr->pptable;

	स_नकल(thermal_data, &SMU7ThermalPolicy[0], माप(काष्ठा PP_TemperatureRange));

	अगर (hwmgr->pp_table_version == PP_TABLE_V1)
		thermal_data->max = table_info->cac_dtp_table->usSoftwareShutकरोwnTemp *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	अन्यथा अगर (hwmgr->pp_table_version == PP_TABLE_V0)
		thermal_data->max = data->thermal_temp_setting.temperature_shutकरोwn *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;

	वापस 0;
पूर्ण

अटल bool smu7_check_clk_voltage_valid(काष्ठा pp_hwmgr *hwmgr,
					क्रमागत PP_OD_DPM_TABLE_COMMAND type,
					uपूर्णांक32_t clk,
					uपूर्णांक32_t voltage)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (voltage < data->odn_dpm_table.min_vddc || voltage > data->odn_dpm_table.max_vddc) अणु
		pr_info("OD voltage is out of range [%d - %d] mV\n",
						data->odn_dpm_table.min_vddc,
						data->odn_dpm_table.max_vddc);
		वापस false;
	पूर्ण

	अगर (type == PP_OD_EDIT_SCLK_VDDC_TABLE) अणु
		अगर (data->golden_dpm_table.sclk_table.dpm_levels[0].value > clk ||
			hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock < clk) अणु
			pr_info("OD engine clock is out of range [%d - %d] MHz\n",
				data->golden_dpm_table.sclk_table.dpm_levels[0].value/100,
				hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock/100);
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अगर (type == PP_OD_EDIT_MCLK_VDDC_TABLE) अणु
		अगर (data->golden_dpm_table.mclk_table.dpm_levels[0].value > clk ||
			hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock < clk) अणु
			pr_info("OD memory clock is out of range [%d - %d] MHz\n",
				data->golden_dpm_table.mclk_table.dpm_levels[0].value/100,
				hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock/100);
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक smu7_odn_edit_dpm_table(काष्ठा pp_hwmgr *hwmgr,
					क्रमागत PP_OD_DPM_TABLE_COMMAND type,
					दीर्घ *input, uपूर्णांक32_t size)
अणु
	uपूर्णांक32_t i;
	काष्ठा phm_odn_घड़ी_levels *podn_dpm_table_in_backend = शून्य;
	काष्ठा smu7_odn_घड़ी_voltage_dependency_table *podn_vdd_dep_in_backend = शून्य;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	uपूर्णांक32_t input_clk;
	uपूर्णांक32_t input_vol;
	uपूर्णांक32_t input_level;

	PP_ASSERT_WITH_CODE(input, "NULL user input for clock and voltage",
				वापस -EINVAL);

	अगर (!hwmgr->od_enabled) अणु
		pr_info("OverDrive feature not enabled\n");
		वापस -EINVAL;
	पूर्ण

	अगर (PP_OD_EDIT_SCLK_VDDC_TABLE == type) अणु
		podn_dpm_table_in_backend = &data->odn_dpm_table.odn_core_घड़ी_dpm_levels;
		podn_vdd_dep_in_backend = &data->odn_dpm_table.vdd_dependency_on_sclk;
		PP_ASSERT_WITH_CODE((podn_dpm_table_in_backend && podn_vdd_dep_in_backend),
				"Failed to get ODN SCLK and Voltage tables",
				वापस -EINVAL);
	पूर्ण अन्यथा अगर (PP_OD_EDIT_MCLK_VDDC_TABLE == type) अणु
		podn_dpm_table_in_backend = &data->odn_dpm_table.odn_memory_घड़ी_dpm_levels;
		podn_vdd_dep_in_backend = &data->odn_dpm_table.vdd_dependency_on_mclk;

		PP_ASSERT_WITH_CODE((podn_dpm_table_in_backend && podn_vdd_dep_in_backend),
			"Failed to get ODN MCLK and Voltage tables",
			वापस -EINVAL);
	पूर्ण अन्यथा अगर (PP_OD_RESTORE_DEFAULT_TABLE == type) अणु
		smu7_odn_initial_शेष_setting(hwmgr);
		वापस 0;
	पूर्ण अन्यथा अगर (PP_OD_COMMIT_DPM_TABLE == type) अणु
		smu7_check_dpm_table_updated(hwmgr);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < size; i += 3) अणु
		अगर (i + 3 > size || input[i] >= podn_dpm_table_in_backend->num_of_pl) अणु
			pr_info("invalid clock voltage input \n");
			वापस 0;
		पूर्ण
		input_level = input[i];
		input_clk = input[i+1] * 100;
		input_vol = input[i+2];

		अगर (smu7_check_clk_voltage_valid(hwmgr, type, input_clk, input_vol)) अणु
			podn_dpm_table_in_backend->entries[input_level].घड़ी = input_clk;
			podn_vdd_dep_in_backend->entries[input_level].clk = input_clk;
			podn_dpm_table_in_backend->entries[input_level].vddc = input_vol;
			podn_vdd_dep_in_backend->entries[input_level].vddc = input_vol;
			podn_vdd_dep_in_backend->entries[input_level].vddgfx = input_vol;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_घातer_profile_mode(काष्ठा pp_hwmgr *hwmgr, अक्षर *buf)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t i, size = 0;
	uपूर्णांक32_t len;

	अटल स्थिर अक्षर *profile_name[7] = अणु"BOOTUP_DEFAULT",
					"3D_FULL_SCREEN",
					"POWER_SAVING",
					"VIDEO",
					"VR",
					"COMPUTE",
					"CUSTOM"पूर्ण;

	अटल स्थिर अक्षर *title[8] = अणु"NUM",
			"MODE_NAME",
			"SCLK_UP_HYST",
			"SCLK_DOWN_HYST",
			"SCLK_ACTIVE_LEVEL",
			"MCLK_UP_HYST",
			"MCLK_DOWN_HYST",
			"MCLK_ACTIVE_LEVEL"पूर्ण;

	अगर (!buf)
		वापस -EINVAL;

	size += प्र_लिखो(buf + size, "%s %16s %16s %16s %16s %16s %16s %16s\n",
			title[0], title[1], title[2], title[3],
			title[4], title[5], title[6], title[7]);

	len = ARRAY_SIZE(smu7_profiling);

	क्रम (i = 0; i < len; i++) अणु
		अगर (i == hwmgr->घातer_profile_mode) अणु
			size += प्र_लिखो(buf + size, "%3d %14s %s: %8d %16d %16d %16d %16d %16d\n",
			i, profile_name[i], "*",
			data->current_profile_setting.sclk_up_hyst,
			data->current_profile_setting.sclk_करोwn_hyst,
			data->current_profile_setting.sclk_activity,
			data->current_profile_setting.mclk_up_hyst,
			data->current_profile_setting.mclk_करोwn_hyst,
			data->current_profile_setting.mclk_activity);
			जारी;
		पूर्ण
		अगर (smu7_profiling[i].bupdate_sclk)
			size += प्र_लिखो(buf + size, "%3d %16s: %8d %16d %16d ",
			i, profile_name[i], smu7_profiling[i].sclk_up_hyst,
			smu7_profiling[i].sclk_करोwn_hyst,
			smu7_profiling[i].sclk_activity);
		अन्यथा
			size += प्र_लिखो(buf + size, "%3d %16s: %8s %16s %16s ",
			i, profile_name[i], "-", "-", "-");

		अगर (smu7_profiling[i].bupdate_mclk)
			size += प्र_लिखो(buf + size, "%16d %16d %16d\n",
			smu7_profiling[i].mclk_up_hyst,
			smu7_profiling[i].mclk_करोwn_hyst,
			smu7_profiling[i].mclk_activity);
		अन्यथा
			size += प्र_लिखो(buf + size, "%16s %16s %16s\n",
			"-", "-", "-");
	पूर्ण

	वापस size;
पूर्ण

अटल व्योम smu7_patch_compute_profile_mode(काष्ठा pp_hwmgr *hwmgr,
					क्रमागत PP_SMC_POWER_PROखाता requst)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t पंचांगp, level;

	अगर (requst == PP_SMC_POWER_PROखाता_COMPUTE) अणु
		अगर (data->dpm_level_enable_mask.sclk_dpm_enable_mask) अणु
			level = 0;
			पंचांगp = data->dpm_level_enable_mask.sclk_dpm_enable_mask;
			जबतक (पंचांगp >>= 1)
				level++;
			अगर (level > 0)
				smu7_क्रमce_घड़ी_level(hwmgr, PP_SCLK, 3 << (level-1));
		पूर्ण
	पूर्ण अन्यथा अगर (hwmgr->घातer_profile_mode == PP_SMC_POWER_PROखाता_COMPUTE) अणु
		smu7_क्रमce_घड़ी_level(hwmgr, PP_SCLK, data->dpm_level_enable_mask.sclk_dpm_enable_mask);
	पूर्ण
पूर्ण

अटल पूर्णांक smu7_set_घातer_profile_mode(काष्ठा pp_hwmgr *hwmgr, दीर्घ *input, uपूर्णांक32_t size)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा profile_mode_setting पंचांगp;
	क्रमागत PP_SMC_POWER_PROखाता mode;

	अगर (input == शून्य)
		वापस -EINVAL;

	mode = input[size];
	चयन (mode) अणु
	हाल PP_SMC_POWER_PROखाता_CUSTOM:
		अगर (size < 8 && size != 0)
			वापस -EINVAL;
		/* If only CUSTOM is passed in, use the saved values. Check
		 * that we actually have a CUSTOM profile by ensuring that
		 * the "use sclk" or the "use mclk" bits are set
		 */
		पंचांगp = smu7_profiling[PP_SMC_POWER_PROखाता_CUSTOM];
		अगर (size == 0) अणु
			अगर (पंचांगp.bupdate_sclk == 0 && पंचांगp.bupdate_mclk == 0)
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			पंचांगp.bupdate_sclk = input[0];
			पंचांगp.sclk_up_hyst = input[1];
			पंचांगp.sclk_करोwn_hyst = input[2];
			पंचांगp.sclk_activity = input[3];
			पंचांगp.bupdate_mclk = input[4];
			पंचांगp.mclk_up_hyst = input[5];
			पंचांगp.mclk_करोwn_hyst = input[6];
			पंचांगp.mclk_activity = input[7];
			smu7_profiling[PP_SMC_POWER_PROखाता_CUSTOM] = पंचांगp;
		पूर्ण
		अगर (!smum_update_dpm_settings(hwmgr, &पंचांगp)) अणु
			स_नकल(&data->current_profile_setting, &पंचांगp, माप(काष्ठा profile_mode_setting));
			hwmgr->घातer_profile_mode = mode;
		पूर्ण
		अवरोध;
	हाल PP_SMC_POWER_PROखाता_FULLSCREEN3D:
	हाल PP_SMC_POWER_PROखाता_POWERSAVING:
	हाल PP_SMC_POWER_PROखाता_VIDEO:
	हाल PP_SMC_POWER_PROखाता_VR:
	हाल PP_SMC_POWER_PROखाता_COMPUTE:
		अगर (mode == hwmgr->घातer_profile_mode)
			वापस 0;

		स_नकल(&पंचांगp, &smu7_profiling[mode], माप(काष्ठा profile_mode_setting));
		अगर (!smum_update_dpm_settings(hwmgr, &पंचांगp)) अणु
			अगर (पंचांगp.bupdate_sclk) अणु
				data->current_profile_setting.bupdate_sclk = पंचांगp.bupdate_sclk;
				data->current_profile_setting.sclk_up_hyst = पंचांगp.sclk_up_hyst;
				data->current_profile_setting.sclk_करोwn_hyst = पंचांगp.sclk_करोwn_hyst;
				data->current_profile_setting.sclk_activity = पंचांगp.sclk_activity;
			पूर्ण
			अगर (पंचांगp.bupdate_mclk) अणु
				data->current_profile_setting.bupdate_mclk = पंचांगp.bupdate_mclk;
				data->current_profile_setting.mclk_up_hyst = पंचांगp.mclk_up_hyst;
				data->current_profile_setting.mclk_करोwn_hyst = पंचांगp.mclk_करोwn_hyst;
				data->current_profile_setting.mclk_activity = पंचांगp.mclk_activity;
			पूर्ण
			smu7_patch_compute_profile_mode(hwmgr, mode);
			hwmgr->घातer_profile_mode = mode;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_get_perक्रमmance_level(काष्ठा pp_hwmgr *hwmgr, स्थिर काष्ठा pp_hw_घातer_state *state,
				PHM_Perक्रमmanceLevelDesignation designation, uपूर्णांक32_t index,
				PHM_Perक्रमmanceLevel *level)
अणु
	स्थिर काष्ठा smu7_घातer_state *ps;
	uपूर्णांक32_t i;

	अगर (level == शून्य || hwmgr == शून्य || state == शून्य)
		वापस -EINVAL;

	ps = cast_स्थिर_phw_smu7_घातer_state(state);

	i = index > ps->perक्रमmance_level_count - 1 ?
			ps->perक्रमmance_level_count - 1 : index;

	level->coreClock = ps->perक्रमmance_levels[i].engine_घड़ी;
	level->memory_घड़ी = ps->perक्रमmance_levels[i].memory_घड़ी;

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_घातer_off_asic(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;

	result = smu7_disable_dpm_tasks(hwmgr);
	PP_ASSERT_WITH_CODE((0 == result),
			"[disable_dpm_tasks] Failed to disable DPM!",
			);

	वापस result;
पूर्ण

अटल स्थिर काष्ठा pp_hwmgr_func smu7_hwmgr_funcs = अणु
	.backend_init = &smu7_hwmgr_backend_init,
	.backend_fini = &smu7_hwmgr_backend_fini,
	.asic_setup = &smu7_setup_asic_task,
	.dynamic_state_management_enable = &smu7_enable_dpm_tasks,
	.apply_state_adjust_rules = smu7_apply_state_adjust_rules,
	.क्रमce_dpm_level = &smu7_क्रमce_dpm_level,
	.घातer_state_set = smu7_set_घातer_state_tasks,
	.get_घातer_state_size = smu7_get_घातer_state_size,
	.get_mclk = smu7_dpm_get_mclk,
	.get_sclk = smu7_dpm_get_sclk,
	.patch_boot_state = smu7_dpm_patch_boot_state,
	.get_pp_table_entry = smu7_get_pp_table_entry,
	.get_num_of_pp_table_entries = smu7_get_number_of_घातerplay_table_entries,
	.घातerकरोwn_uvd = smu7_घातerकरोwn_uvd,
	.घातergate_uvd = smu7_घातergate_uvd,
	.घातergate_vce = smu7_घातergate_vce,
	.disable_घड़ी_घातer_gating = smu7_disable_घड़ी_घातer_gating,
	.update_घड़ी_gatings = smu7_update_घड़ी_gatings,
	.notअगरy_smc_display_config_after_ps_adjusपंचांगent = smu7_notअगरy_smc_display_config_after_ps_adjusपंचांगent,
	.display_config_changed = smu7_display_configuration_changed_task,
	.set_max_fan_pwm_output = smu7_set_max_fan_pwm_output,
	.set_max_fan_rpm_output = smu7_set_max_fan_rpm_output,
	.stop_thermal_controller = smu7_thermal_stop_thermal_controller,
	.get_fan_speed_info = smu7_fan_ctrl_get_fan_speed_info,
	.get_fan_speed_percent = smu7_fan_ctrl_get_fan_speed_percent,
	.set_fan_speed_percent = smu7_fan_ctrl_set_fan_speed_percent,
	.reset_fan_speed_to_शेष = smu7_fan_ctrl_reset_fan_speed_to_शेष,
	.get_fan_speed_rpm = smu7_fan_ctrl_get_fan_speed_rpm,
	.set_fan_speed_rpm = smu7_fan_ctrl_set_fan_speed_rpm,
	.uninitialize_thermal_controller = smu7_thermal_ctrl_uninitialize_thermal_controller,
	.रेजिस्टर_irq_handlers = smu7_रेजिस्टर_irq_handlers,
	.check_smc_update_required_क्रम_display_configuration = smu7_check_smc_update_required_क्रम_display_configuration,
	.check_states_equal = smu7_check_states_equal,
	.set_fan_control_mode = smu7_set_fan_control_mode,
	.get_fan_control_mode = smu7_get_fan_control_mode,
	.क्रमce_घड़ी_level = smu7_क्रमce_घड़ी_level,
	.prपूर्णांक_घड़ी_levels = smu7_prपूर्णांक_घड़ी_levels,
	.घातergate_gfx = smu7_घातergate_gfx,
	.get_sclk_od = smu7_get_sclk_od,
	.set_sclk_od = smu7_set_sclk_od,
	.get_mclk_od = smu7_get_mclk_od,
	.set_mclk_od = smu7_set_mclk_od,
	.get_घड़ी_by_type = smu7_get_घड़ी_by_type,
	.get_घड़ी_by_type_with_latency = smu7_get_घड़ी_by_type_with_latency,
	.set_watermarks_क्रम_घड़ीs_ranges = smu7_set_watermarks_क्रम_घड़ीs_ranges,
	.पढ़ो_sensor = smu7_पढ़ो_sensor,
	.dynamic_state_management_disable = smu7_disable_dpm_tasks,
	.avfs_control = smu7_avfs_control,
	.disable_smc_firmware_ctf = smu7_thermal_disable_alert,
	.start_thermal_controller = smu7_start_thermal_controller,
	.notअगरy_cac_buffer_info = smu7_notअगरy_cac_buffer_info,
	.get_max_high_घड़ीs = smu7_get_max_high_घड़ीs,
	.get_thermal_temperature_range = smu7_get_thermal_temperature_range,
	.odn_edit_dpm_table = smu7_odn_edit_dpm_table,
	.set_घातer_limit = smu7_set_घातer_limit,
	.get_घातer_profile_mode = smu7_get_घातer_profile_mode,
	.set_घातer_profile_mode = smu7_set_घातer_profile_mode,
	.get_perक्रमmance_level = smu7_get_perक्रमmance_level,
	.get_asic_baco_capability = smu7_baco_get_capability,
	.get_asic_baco_state = smu7_baco_get_state,
	.set_asic_baco_state = smu7_baco_set_state,
	.घातer_off_asic = smu7_घातer_off_asic,
पूर्ण;

uपूर्णांक8_t smu7_get_sleep_भागider_id_from_घड़ी(uपूर्णांक32_t घड़ी,
		uपूर्णांक32_t घड़ी_insr)
अणु
	uपूर्णांक8_t i;
	uपूर्णांक32_t temp;
	uपूर्णांक32_t min = max(घड़ी_insr, (uपूर्णांक32_t)SMU7_MINIMUM_ENGINE_CLOCK);

	PP_ASSERT_WITH_CODE((घड़ी >= min), "Engine clock can't satisfy stutter requirement!", वापस 0);
	क्रम (i = SMU7_MAX_DEEPSLEEP_DIVIDER_ID;  ; i--) अणु
		temp = घड़ी >> i;

		अगर (temp >= min || i == 0)
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

पूर्णांक smu7_init_function_poपूर्णांकers(काष्ठा pp_hwmgr *hwmgr)
अणु
	hwmgr->hwmgr_func = &smu7_hwmgr_funcs;
	अगर (hwmgr->pp_table_version == PP_TABLE_V0)
		hwmgr->pptable_func = &pptable_funcs;
	अन्यथा अगर (hwmgr->pp_table_version == PP_TABLE_V1)
		hwmgr->pptable_func = &pptable_v1_0_funcs;

	वापस 0;
पूर्ण
