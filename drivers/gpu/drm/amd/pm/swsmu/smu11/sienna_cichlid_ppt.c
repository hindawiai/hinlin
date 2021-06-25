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

#घोषणा SWSMU_CODE_LAYER_L2

#समावेश <linux/firmware.h>
#समावेश <linux/pci.h>
#समावेश <linux/i2c.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_smu.h"
#समावेश "atomfirmware.h"
#समावेश "amdgpu_atomfirmware.h"
#समावेश "amdgpu_atombios.h"
#समावेश "smu_v11_0.h"
#समावेश "smu11_driver_if_sienna_cichlid.h"
#समावेश "soc15_common.h"
#समावेश "atom.h"
#समावेश "sienna_cichlid_ppt.h"
#समावेश "smu_v11_0_7_pptable.h"
#समावेश "smu_v11_0_7_ppsmc.h"
#समावेश "nbio/nbio_2_3_offset.h"
#समावेश "nbio/nbio_2_3_sh_mask.h"
#समावेश "thm/thm_11_0_2_offset.h"
#समावेश "thm/thm_11_0_2_sh_mask.h"
#समावेश "mp/mp_11_0_offset.h"
#समावेश "mp/mp_11_0_sh_mask.h"

#समावेश "asic_reg/mp/mp_11_0_sh_mask.h"
#समावेश "smu_cmn.h"

/*
 * DO NOT use these क्रम err/warn/info/debug messages.
 * Use dev_err, dev_warn, dev_info and dev_dbg instead.
 * They are more MGPU मित्रly.
 */
#अघोषित pr_err
#अघोषित pr_warn
#अघोषित pr_info
#अघोषित pr_debug

#घोषणा to_amdgpu_device(x) (container_of(x, काष्ठा amdgpu_device, pm.smu_i2c))

#घोषणा FEATURE_MASK(feature) (1ULL << feature)
#घोषणा SMC_DPM_FEATURE ( \
	FEATURE_MASK(FEATURE_DPM_PREFETCHER_BIT) | \
	FEATURE_MASK(FEATURE_DPM_GFXCLK_BIT)     | \
	FEATURE_MASK(FEATURE_DPM_UCLK_BIT)	 | \
	FEATURE_MASK(FEATURE_DPM_LINK_BIT)       | \
	FEATURE_MASK(FEATURE_DPM_SOCCLK_BIT)     | \
	FEATURE_MASK(FEATURE_DPM_FCLK_BIT)	 | \
	FEATURE_MASK(FEATURE_DPM_DCEFCLK_BIT)	 | \
	FEATURE_MASK(FEATURE_DPM_MP0CLK_BIT))

#घोषणा SMU_11_0_7_GFX_BUSY_THRESHOLD 15

अटल काष्ठा cmn2asic_msg_mapping sienna_cichlid_message_map[SMU_MSG_MAX_COUNT] = अणु
	MSG_MAP(TestMessage,			PPSMC_MSG_TestMessage,                 1),
	MSG_MAP(GetSmuVersion,			PPSMC_MSG_GetSmuVersion,               1),
	MSG_MAP(GetDriverIfVersion,		PPSMC_MSG_GetDriverIfVersion,          1),
	MSG_MAP(SetAllowedFeaturesMaskLow,	PPSMC_MSG_SetAllowedFeaturesMaskLow,   0),
	MSG_MAP(SetAllowedFeaturesMaskHigh,	PPSMC_MSG_SetAllowedFeaturesMaskHigh,  0),
	MSG_MAP(EnableAllSmuFeatures,		PPSMC_MSG_EnableAllSmuFeatures,        0),
	MSG_MAP(DisableAllSmuFeatures,		PPSMC_MSG_DisableAllSmuFeatures,       0),
	MSG_MAP(EnableSmuFeaturesLow,		PPSMC_MSG_EnableSmuFeaturesLow,        1),
	MSG_MAP(EnableSmuFeaturesHigh,		PPSMC_MSG_EnableSmuFeaturesHigh,       1),
	MSG_MAP(DisableSmuFeaturesLow,		PPSMC_MSG_DisableSmuFeaturesLow,       1),
	MSG_MAP(DisableSmuFeaturesHigh,		PPSMC_MSG_DisableSmuFeaturesHigh,      1),
	MSG_MAP(GetEnabledSmuFeaturesLow,       PPSMC_MSG_GetRunningSmuFeaturesLow,    1),
	MSG_MAP(GetEnabledSmuFeaturesHigh,	PPSMC_MSG_GetRunningSmuFeaturesHigh,   1),
	MSG_MAP(SetWorkloadMask,		PPSMC_MSG_SetWorkloadMask,             1),
	MSG_MAP(SetPptLimit,			PPSMC_MSG_SetPptLimit,                 0),
	MSG_MAP(SetDriverDramAddrHigh,		PPSMC_MSG_SetDriverDramAddrHigh,       1),
	MSG_MAP(SetDriverDramAddrLow,		PPSMC_MSG_SetDriverDramAddrLow,        1),
	MSG_MAP(SetToolsDramAddrHigh,		PPSMC_MSG_SetToolsDramAddrHigh,        0),
	MSG_MAP(SetToolsDramAddrLow,		PPSMC_MSG_SetToolsDramAddrLow,         0),
	MSG_MAP(TransferTableSmu2Dram,		PPSMC_MSG_TransferTableSmu2Dram,       1),
	MSG_MAP(TransferTableDram2Smu,		PPSMC_MSG_TransferTableDram2Smu,       0),
	MSG_MAP(UseDefaultPPTable,		PPSMC_MSG_UseDefaultPPTable,           0),
	MSG_MAP(RunDcBtc,			PPSMC_MSG_RunDcBtc,                    0),
	MSG_MAP(EnterBaco,			PPSMC_MSG_EnterBaco,                   0),
	MSG_MAP(SetSoftMinByFreq,		PPSMC_MSG_SetSoftMinByFreq,            1),
	MSG_MAP(SetSoftMaxByFreq,		PPSMC_MSG_SetSoftMaxByFreq,            1),
	MSG_MAP(SetHardMinByFreq,		PPSMC_MSG_SetHardMinByFreq,            1),
	MSG_MAP(SetHardMaxByFreq,		PPSMC_MSG_SetHardMaxByFreq,            0),
	MSG_MAP(GetMinDpmFreq,			PPSMC_MSG_GetMinDpmFreq,               1),
	MSG_MAP(GetMaxDpmFreq,			PPSMC_MSG_GetMaxDpmFreq,               1),
	MSG_MAP(GetDpmFreqByIndex,		PPSMC_MSG_GetDpmFreqByIndex,           1),
	MSG_MAP(SetGeminiMode,			PPSMC_MSG_SetGeminiMode,               0),
	MSG_MAP(SetGeminiApertureHigh,		PPSMC_MSG_SetGeminiApertureHigh,       0),
	MSG_MAP(SetGeminiApertureLow,		PPSMC_MSG_SetGeminiApertureLow,        0),
	MSG_MAP(OverridePcieParameters,		PPSMC_MSG_OverridePcieParameters,      0),
	MSG_MAP(ReenableAcDcInterrupt,		PPSMC_MSG_ReenableAcDcInterrupt,       0),
	MSG_MAP(NotअगरyPowerSource,		PPSMC_MSG_NotअगरyPowerSource,           0),
	MSG_MAP(SetUclkFastSwitch,		PPSMC_MSG_SetUclkFastSwitch,           0),
	MSG_MAP(SetVideoFps,			PPSMC_MSG_SetVideoFps,                 0),
	MSG_MAP(PrepareMp1ForUnload,		PPSMC_MSG_PrepareMp1ForUnload,         1),
	MSG_MAP(AllowGfxOff,			PPSMC_MSG_AllowGfxOff,                 0),
	MSG_MAP(DisallowGfxOff,			PPSMC_MSG_DisallowGfxOff,              0),
	MSG_MAP(GetPptLimit,			PPSMC_MSG_GetPptLimit,                 0),
	MSG_MAP(GetDcModeMaxDpmFreq,		PPSMC_MSG_GetDcModeMaxDpmFreq,         1),
	MSG_MAP(ExitBaco,			PPSMC_MSG_ExitBaco,                    0),
	MSG_MAP(PowerUpVcn,			PPSMC_MSG_PowerUpVcn,                  0),
	MSG_MAP(PowerDownVcn,			PPSMC_MSG_PowerDownVcn,                0),
	MSG_MAP(PowerUpJpeg,			PPSMC_MSG_PowerUpJpeg,                 0),
	MSG_MAP(PowerDownJpeg,			PPSMC_MSG_PowerDownJpeg,               0),
	MSG_MAP(BacoAudioD3PME,			PPSMC_MSG_BacoAudioD3PME,              0),
	MSG_MAP(ArmD3,				PPSMC_MSG_ArmD3,                       0),
	MSG_MAP(Mode1Reset,                     PPSMC_MSG_Mode1Reset,		       0),
	MSG_MAP(SetMGpuFanBoostLimitRpm,	PPSMC_MSG_SetMGpuFanBoostLimitRpm,     0),
	MSG_MAP(SetGpoFeaturePMask,		PPSMC_MSG_SetGpoFeaturePMask,          0),
	MSG_MAP(DisallowGpo,			PPSMC_MSG_DisallowGpo,                 0),
	MSG_MAP(Enable2ndUSB20Port,		PPSMC_MSG_Enable2ndUSB20Port,          0),
पूर्ण;

अटल काष्ठा cmn2asic_mapping sienna_cichlid_clk_map[SMU_CLK_COUNT] = अणु
	CLK_MAP(GFXCLK,		PPCLK_GFXCLK),
	CLK_MAP(SCLK,		PPCLK_GFXCLK),
	CLK_MAP(SOCCLK,		PPCLK_SOCCLK),
	CLK_MAP(FCLK,		PPCLK_FCLK),
	CLK_MAP(UCLK,		PPCLK_UCLK),
	CLK_MAP(MCLK,		PPCLK_UCLK),
	CLK_MAP(DCLK,		PPCLK_DCLK_0),
	CLK_MAP(DCLK1,		PPCLK_DCLK_1),
	CLK_MAP(VCLK,		PPCLK_VCLK_0),
	CLK_MAP(VCLK1,		PPCLK_VCLK_1),
	CLK_MAP(DCEFCLK,	PPCLK_DCEFCLK),
	CLK_MAP(DISPCLK,	PPCLK_DISPCLK),
	CLK_MAP(PIXCLK,		PPCLK_PIXCLK),
	CLK_MAP(PHYCLK,		PPCLK_PHYCLK),
पूर्ण;

अटल काष्ठा cmn2asic_mapping sienna_cichlid_feature_mask_map[SMU_FEATURE_COUNT] = अणु
	FEA_MAP(DPM_PREFETCHER),
	FEA_MAP(DPM_GFXCLK),
	FEA_MAP(DPM_GFX_GPO),
	FEA_MAP(DPM_UCLK),
	FEA_MAP(DPM_FCLK),
	FEA_MAP(DPM_SOCCLK),
	FEA_MAP(DPM_MP0CLK),
	FEA_MAP(DPM_LINK),
	FEA_MAP(DPM_DCEFCLK),
	FEA_MAP(DPM_XGMI),
	FEA_MAP(MEM_VDDCI_SCALING),
	FEA_MAP(MEM_MVDD_SCALING),
	FEA_MAP(DS_GFXCLK),
	FEA_MAP(DS_SOCCLK),
	FEA_MAP(DS_FCLK),
	FEA_MAP(DS_LCLK),
	FEA_MAP(DS_DCEFCLK),
	FEA_MAP(DS_UCLK),
	FEA_MAP(GFX_ULV),
	FEA_MAP(FW_DSTATE),
	FEA_MAP(GFXOFF),
	FEA_MAP(BACO),
	FEA_MAP(MM_DPM_PG),
	FEA_MAP(RSMU_SMN_CG),
	FEA_MAP(PPT),
	FEA_MAP(TDC),
	FEA_MAP(APCC_PLUS),
	FEA_MAP(GTHR),
	FEA_MAP(ACDC),
	FEA_MAP(VR0HOT),
	FEA_MAP(VR1HOT),
	FEA_MAP(FW_CTF),
	FEA_MAP(FAN_CONTROL),
	FEA_MAP(THERMAL),
	FEA_MAP(GFX_DCS),
	FEA_MAP(RM),
	FEA_MAP(LED_DISPLAY),
	FEA_MAP(GFX_SS),
	FEA_MAP(OUT_OF_BAND_MONITOR),
	FEA_MAP(TEMP_DEPENDENT_VMIN),
	FEA_MAP(MMHUB_PG),
	FEA_MAP(ATHUB_PG),
	FEA_MAP(APCC_DFLL),
पूर्ण;

अटल काष्ठा cmn2asic_mapping sienna_cichlid_table_map[SMU_TABLE_COUNT] = अणु
	TAB_MAP(PPTABLE),
	TAB_MAP(WATERMARKS),
	TAB_MAP(AVFS_PSM_DEBUG),
	TAB_MAP(AVFS_FUSE_OVERRIDE),
	TAB_MAP(PMSTATUSLOG),
	TAB_MAP(SMU_METRICS),
	TAB_MAP(DRIVER_SMU_CONFIG),
	TAB_MAP(ACTIVITY_MONITOR_COEFF),
	TAB_MAP(OVERDRIVE),
	TAB_MAP(I2C_COMMANDS),
	TAB_MAP(PACE),
पूर्ण;

अटल काष्ठा cmn2asic_mapping sienna_cichlid_pwr_src_map[SMU_POWER_SOURCE_COUNT] = अणु
	PWR_MAP(AC),
	PWR_MAP(DC),
पूर्ण;

अटल काष्ठा cmn2asic_mapping sienna_cichlid_workload_map[PP_SMC_POWER_PROखाता_COUNT] = अणु
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT,	WORKLOAD_PPLIB_DEFAULT_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_FULLSCREEN3D,		WORKLOAD_PPLIB_FULL_SCREEN_3D_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_POWERSAVING,		WORKLOAD_PPLIB_POWER_SAVING_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_VIDEO,		WORKLOAD_PPLIB_VIDEO_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_VR,			WORKLOAD_PPLIB_VR_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_COMPUTE,		WORKLOAD_PPLIB_COMPUTE_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_CUSTOM,		WORKLOAD_PPLIB_CUSTOM_BIT),
पूर्ण;

अटल पूर्णांक
sienna_cichlid_get_allowed_feature_mask(काष्ठा smu_context *smu,
				  uपूर्णांक32_t *feature_mask, uपूर्णांक32_t num)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;

	अगर (num > 2)
		वापस -EINVAL;

	स_रखो(feature_mask, 0, माप(uपूर्णांक32_t) * num);

	*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_DPM_PREFETCHER_BIT)
				| FEATURE_MASK(FEATURE_DPM_FCLK_BIT)
				| FEATURE_MASK(FEATURE_DPM_MP0CLK_BIT)
				| FEATURE_MASK(FEATURE_DS_SOCCLK_BIT)
				| FEATURE_MASK(FEATURE_DS_DCEFCLK_BIT)
				| FEATURE_MASK(FEATURE_DS_FCLK_BIT)
				| FEATURE_MASK(FEATURE_DS_UCLK_BIT)
				| FEATURE_MASK(FEATURE_FW_DSTATE_BIT)
				| FEATURE_MASK(FEATURE_DF_CSTATE_BIT)
				| FEATURE_MASK(FEATURE_RSMU_SMN_CG_BIT)
				| FEATURE_MASK(FEATURE_GFX_SS_BIT)
				| FEATURE_MASK(FEATURE_VR0HOT_BIT)
				| FEATURE_MASK(FEATURE_PPT_BIT)
				| FEATURE_MASK(FEATURE_TDC_BIT)
				| FEATURE_MASK(FEATURE_BACO_BIT)
				| FEATURE_MASK(FEATURE_APCC_DFLL_BIT)
				| FEATURE_MASK(FEATURE_FW_CTF_BIT)
				| FEATURE_MASK(FEATURE_FAN_CONTROL_BIT)
				| FEATURE_MASK(FEATURE_THERMAL_BIT)
				| FEATURE_MASK(FEATURE_OUT_OF_BAND_MONITOR_BIT);

	अगर (adev->pm.pp_feature & PP_SCLK_DPM_MASK) अणु
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_DPM_GFXCLK_BIT);
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_DPM_GFX_GPO_BIT);
	पूर्ण

	अगर ((adev->pm.pp_feature & PP_GFX_DCS_MASK) &&
	    (adev->asic_type > CHIP_SIENNA_CICHLID) &&
	    !(adev->flags & AMD_IS_APU))
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_GFX_DCS_BIT);

	अगर (adev->pm.pp_feature & PP_MCLK_DPM_MASK)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_DPM_UCLK_BIT)
					| FEATURE_MASK(FEATURE_MEM_VDDCI_SCALING_BIT)
					| FEATURE_MASK(FEATURE_MEM_MVDD_SCALING_BIT);

	अगर (adev->pm.pp_feature & PP_PCIE_DPM_MASK)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_DPM_LINK_BIT);

	अगर (adev->pm.pp_feature & PP_DCEFCLK_DPM_MASK)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_DPM_DCEFCLK_BIT);

	अगर (adev->pm.pp_feature & PP_SOCCLK_DPM_MASK)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_DPM_SOCCLK_BIT);

	अगर (adev->pm.pp_feature & PP_ULV_MASK)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_GFX_ULV_BIT);

	अगर (adev->pm.pp_feature & PP_SCLK_DEEP_SLEEP_MASK)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_DS_GFXCLK_BIT);

	अगर (adev->pm.pp_feature & PP_GFXOFF_MASK)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_GFXOFF_BIT);

	अगर (smu->adev->pg_flags & AMD_PG_SUPPORT_ATHUB)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_ATHUB_PG_BIT);

	अगर (smu->adev->pg_flags & AMD_PG_SUPPORT_MMHUB)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_MMHUB_PG_BIT);

	अगर (smu->adev->pg_flags & AMD_PG_SUPPORT_VCN ||
	    smu->adev->pg_flags & AMD_PG_SUPPORT_JPEG)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_MM_DPM_PG_BIT);

	अगर (smu->dc_controlled_by_gpio)
       *(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_ACDC_BIT);

	अगर (amdgpu_aspm == 1)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_DS_LCLK_BIT);

	वापस 0;
पूर्ण

अटल पूर्णांक sienna_cichlid_check_घातerplay_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	काष्ठा smu_11_0_7_घातerplay_table *घातerplay_table =
		table_context->घातer_play_table;
	काष्ठा smu_baco_context *smu_baco = &smu->smu_baco;

	अगर (घातerplay_table->platक्रमm_caps & SMU_11_0_7_PP_PLATFORM_CAP_HARDWAREDC)
		smu->dc_controlled_by_gpio = true;

	अगर (घातerplay_table->platक्रमm_caps & SMU_11_0_7_PP_PLATFORM_CAP_BACO ||
	    घातerplay_table->platक्रमm_caps & SMU_11_0_7_PP_PLATFORM_CAP_MACO)
		smu_baco->platक्रमm_support = true;

	table_context->thermal_controller_type =
		घातerplay_table->thermal_controller_type;

	/*
	 * Instead of having its own buffer space and get overdrive_table copied,
	 * smu->od_settings just poपूर्णांकs to the actual overdrive_table
	 */
	smu->od_settings = &घातerplay_table->overdrive_table;

	वापस 0;
पूर्ण

अटल पूर्णांक sienna_cichlid_append_घातerplay_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	PPTable_t *smc_pptable = table_context->driver_pptable;
	काष्ठा atom_smc_dpm_info_v4_9 *smc_dpm_table;
	पूर्णांक index, ret;

	index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
					    smc_dpm_info);

	ret = amdgpu_atombios_get_data_table(smu->adev, index, शून्य, शून्य, शून्य,
				      (uपूर्णांक8_t **)&smc_dpm_table);
	अगर (ret)
		वापस ret;

	स_नकल(smc_pptable->I2cControllers, smc_dpm_table->I2cControllers,
	       माप(*smc_dpm_table) - माप(smc_dpm_table->table_header));
	
	वापस 0;
पूर्ण

अटल पूर्णांक sienna_cichlid_store_घातerplay_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	काष्ठा smu_11_0_7_घातerplay_table *घातerplay_table =
		table_context->घातer_play_table;

	स_नकल(table_context->driver_pptable, &घातerplay_table->smc_pptable,
	       माप(PPTable_t));

	वापस 0;
पूर्ण

अटल पूर्णांक sienna_cichlid_setup_pptable(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	ret = smu_v11_0_setup_pptable(smu);
	अगर (ret)
		वापस ret;

	ret = sienna_cichlid_store_घातerplay_table(smu);
	अगर (ret)
		वापस ret;

	ret = sienna_cichlid_append_घातerplay_table(smu);
	अगर (ret)
		वापस ret;

	ret = sienna_cichlid_check_घातerplay_table(smu);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक sienna_cichlid_tables_init(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा smu_table *tables = smu_table->tables;

	SMU_TABLE_INIT(tables, SMU_TABLE_PPTABLE, माप(PPTable_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_WATERMARKS, माप(Watermarks_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_SMU_METRICS, माप(SmuMetricsExternal_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_I2C_COMMANDS, माप(SwI2cRequest_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_OVERDRIVE, माप(OverDriveTable_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_PMSTATUSLOG, SMU11_TOOL_SIZE,
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_ACTIVITY_MONITOR_COEFF,
		       माप(DpmActivityMonitorCoeffIntExternal_t), PAGE_SIZE,
	               AMDGPU_GEM_DOMAIN_VRAM);

	smu_table->metrics_table = kzalloc(माप(SmuMetricsExternal_t), GFP_KERNEL);
	अगर (!smu_table->metrics_table)
		जाओ err0_out;
	smu_table->metrics_समय = 0;

	smu_table->gpu_metrics_table_size = माप(काष्ठा gpu_metrics_v1_1);
	smu_table->gpu_metrics_table = kzalloc(smu_table->gpu_metrics_table_size, GFP_KERNEL);
	अगर (!smu_table->gpu_metrics_table)
		जाओ err1_out;

	smu_table->watermarks_table = kzalloc(माप(Watermarks_t), GFP_KERNEL);
	अगर (!smu_table->watermarks_table)
		जाओ err2_out;

	वापस 0;

err2_out:
	kमुक्त(smu_table->gpu_metrics_table);
err1_out:
	kमुक्त(smu_table->metrics_table);
err0_out:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक sienna_cichlid_get_smu_metrics_data(काष्ठा smu_context *smu,
					       MetricsMember_t member,
					       uपूर्णांक32_t *value)
अणु
	काष्ठा smu_table_context *smu_table= &smu->smu_table;
	SmuMetrics_t *metrics =
		&(((SmuMetricsExternal_t *)(smu_table->metrics_table))->SmuMetrics);
	पूर्णांक ret = 0;

	mutex_lock(&smu->metrics_lock);

	ret = smu_cmn_get_metrics_table_locked(smu,
					       शून्य,
					       false);
	अगर (ret) अणु
		mutex_unlock(&smu->metrics_lock);
		वापस ret;
	पूर्ण

	चयन (member) अणु
	हाल METRICS_CURR_GFXCLK:
		*value = metrics->CurrClock[PPCLK_GFXCLK];
		अवरोध;
	हाल METRICS_CURR_SOCCLK:
		*value = metrics->CurrClock[PPCLK_SOCCLK];
		अवरोध;
	हाल METRICS_CURR_UCLK:
		*value = metrics->CurrClock[PPCLK_UCLK];
		अवरोध;
	हाल METRICS_CURR_VCLK:
		*value = metrics->CurrClock[PPCLK_VCLK_0];
		अवरोध;
	हाल METRICS_CURR_VCLK1:
		*value = metrics->CurrClock[PPCLK_VCLK_1];
		अवरोध;
	हाल METRICS_CURR_DCLK:
		*value = metrics->CurrClock[PPCLK_DCLK_0];
		अवरोध;
	हाल METRICS_CURR_DCLK1:
		*value = metrics->CurrClock[PPCLK_DCLK_1];
		अवरोध;
	हाल METRICS_CURR_DCEFCLK:
		*value = metrics->CurrClock[PPCLK_DCEFCLK];
		अवरोध;
	हाल METRICS_CURR_FCLK:
		*value = metrics->CurrClock[PPCLK_FCLK];
		अवरोध;
	हाल METRICS_AVERAGE_GFXCLK:
		अगर (metrics->AverageGfxActivity <= SMU_11_0_7_GFX_BUSY_THRESHOLD)
			*value = metrics->AverageGfxclkFrequencyPostDs;
		अन्यथा
			*value = metrics->AverageGfxclkFrequencyPreDs;
		अवरोध;
	हाल METRICS_AVERAGE_FCLK:
		*value = metrics->AverageFclkFrequencyPostDs;
		अवरोध;
	हाल METRICS_AVERAGE_UCLK:
		*value = metrics->AverageUclkFrequencyPostDs;
		अवरोध;
	हाल METRICS_AVERAGE_GFXACTIVITY:
		*value = metrics->AverageGfxActivity;
		अवरोध;
	हाल METRICS_AVERAGE_MEMACTIVITY:
		*value = metrics->AverageUclkActivity;
		अवरोध;
	हाल METRICS_AVERAGE_SOCKETPOWER:
		*value = metrics->AverageSocketPower << 8;
		अवरोध;
	हाल METRICS_TEMPERATURE_EDGE:
		*value = metrics->TemperatureEdge *
			SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
		अवरोध;
	हाल METRICS_TEMPERATURE_HOTSPOT:
		*value = metrics->TemperatureHotspot *
			SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
		अवरोध;
	हाल METRICS_TEMPERATURE_MEM:
		*value = metrics->TemperatureMem *
			SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
		अवरोध;
	हाल METRICS_TEMPERATURE_VRGFX:
		*value = metrics->TemperatureVrGfx *
			SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
		अवरोध;
	हाल METRICS_TEMPERATURE_VRSOC:
		*value = metrics->TemperatureVrSoc *
			SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
		अवरोध;
	हाल METRICS_THROTTLER_STATUS:
		*value = metrics->ThrottlerStatus;
		अवरोध;
	हाल METRICS_CURR_FANSPEED:
		*value = metrics->CurrFanSpeed;
		अवरोध;
	शेष:
		*value = अच_पूर्णांक_उच्च;
		अवरोध;
	पूर्ण

	mutex_unlock(&smu->metrics_lock);

	वापस ret;

पूर्ण

अटल पूर्णांक sienna_cichlid_allocate_dpm_context(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_dpm_context *smu_dpm = &smu->smu_dpm;

	smu_dpm->dpm_context = kzalloc(माप(काष्ठा smu_11_0_dpm_context),
				       GFP_KERNEL);
	अगर (!smu_dpm->dpm_context)
		वापस -ENOMEM;

	smu_dpm->dpm_context_size = माप(काष्ठा smu_11_0_dpm_context);

	वापस 0;
पूर्ण

अटल पूर्णांक sienna_cichlid_init_smc_tables(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	ret = sienna_cichlid_tables_init(smu);
	अगर (ret)
		वापस ret;

	ret = sienna_cichlid_allocate_dpm_context(smu);
	अगर (ret)
		वापस ret;

	वापस smu_v11_0_init_smc_tables(smu);
पूर्ण

अटल पूर्णांक sienna_cichlid_set_शेष_dpm_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_11_0_dpm_context *dpm_context = smu->smu_dpm.dpm_context;
	PPTable_t *driver_ppt = smu->smu_table.driver_pptable;
	काष्ठा smu_11_0_dpm_table *dpm_table;
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक ret = 0;

	/* socclk dpm table setup */
	dpm_table = &dpm_context->dpm_tables.soc_table;
	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_SOCCLK_BIT)) अणु
		ret = smu_v11_0_set_single_dpm_table(smu,
						     SMU_SOCCLK,
						     dpm_table);
		अगर (ret)
			वापस ret;
		dpm_table->is_fine_grained =
			!driver_ppt->DpmDescriptor[PPCLK_SOCCLK].SnapToDiscrete;
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.socclk / 100;
		dpm_table->dpm_levels[0].enabled = true;
		dpm_table->min = dpm_table->dpm_levels[0].value;
		dpm_table->max = dpm_table->dpm_levels[0].value;
	पूर्ण

	/* gfxclk dpm table setup */
	dpm_table = &dpm_context->dpm_tables.gfx_table;
	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_GFXCLK_BIT)) अणु
		ret = smu_v11_0_set_single_dpm_table(smu,
						     SMU_GFXCLK,
						     dpm_table);
		अगर (ret)
			वापस ret;
		dpm_table->is_fine_grained =
			!driver_ppt->DpmDescriptor[PPCLK_GFXCLK].SnapToDiscrete;
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.gfxclk / 100;
		dpm_table->dpm_levels[0].enabled = true;
		dpm_table->min = dpm_table->dpm_levels[0].value;
		dpm_table->max = dpm_table->dpm_levels[0].value;
	पूर्ण

	/* uclk dpm table setup */
	dpm_table = &dpm_context->dpm_tables.uclk_table;
	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_UCLK_BIT)) अणु
		ret = smu_v11_0_set_single_dpm_table(smu,
						     SMU_UCLK,
						     dpm_table);
		अगर (ret)
			वापस ret;
		dpm_table->is_fine_grained =
			!driver_ppt->DpmDescriptor[PPCLK_UCLK].SnapToDiscrete;
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.uclk / 100;
		dpm_table->dpm_levels[0].enabled = true;
		dpm_table->min = dpm_table->dpm_levels[0].value;
		dpm_table->max = dpm_table->dpm_levels[0].value;
	पूर्ण

	/* fclk dpm table setup */
	dpm_table = &dpm_context->dpm_tables.fclk_table;
	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_FCLK_BIT)) अणु
		ret = smu_v11_0_set_single_dpm_table(smu,
						     SMU_FCLK,
						     dpm_table);
		अगर (ret)
			वापस ret;
		dpm_table->is_fine_grained =
			!driver_ppt->DpmDescriptor[PPCLK_FCLK].SnapToDiscrete;
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.fclk / 100;
		dpm_table->dpm_levels[0].enabled = true;
		dpm_table->min = dpm_table->dpm_levels[0].value;
		dpm_table->max = dpm_table->dpm_levels[0].value;
	पूर्ण

	/* vclk0 dpm table setup */
	dpm_table = &dpm_context->dpm_tables.vclk_table;
	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_MM_DPM_PG_BIT)) अणु
		ret = smu_v11_0_set_single_dpm_table(smu,
						     SMU_VCLK,
						     dpm_table);
		अगर (ret)
			वापस ret;
		dpm_table->is_fine_grained =
			!driver_ppt->DpmDescriptor[PPCLK_VCLK_0].SnapToDiscrete;
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.vclk / 100;
		dpm_table->dpm_levels[0].enabled = true;
		dpm_table->min = dpm_table->dpm_levels[0].value;
		dpm_table->max = dpm_table->dpm_levels[0].value;
	पूर्ण

	/* vclk1 dpm table setup */
	अगर (adev->vcn.num_vcn_inst > 1) अणु
		dpm_table = &dpm_context->dpm_tables.vclk1_table;
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_MM_DPM_PG_BIT)) अणु
			ret = smu_v11_0_set_single_dpm_table(smu,
							     SMU_VCLK1,
							     dpm_table);
			अगर (ret)
				वापस ret;
			dpm_table->is_fine_grained =
				!driver_ppt->DpmDescriptor[PPCLK_VCLK_1].SnapToDiscrete;
		पूर्ण अन्यथा अणु
			dpm_table->count = 1;
			dpm_table->dpm_levels[0].value =
				smu->smu_table.boot_values.vclk / 100;
			dpm_table->dpm_levels[0].enabled = true;
			dpm_table->min = dpm_table->dpm_levels[0].value;
			dpm_table->max = dpm_table->dpm_levels[0].value;
		पूर्ण
	पूर्ण

	/* dclk0 dpm table setup */
	dpm_table = &dpm_context->dpm_tables.dclk_table;
	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_MM_DPM_PG_BIT)) अणु
		ret = smu_v11_0_set_single_dpm_table(smu,
						     SMU_DCLK,
						     dpm_table);
		अगर (ret)
			वापस ret;
		dpm_table->is_fine_grained =
			!driver_ppt->DpmDescriptor[PPCLK_DCLK_0].SnapToDiscrete;
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.dclk / 100;
		dpm_table->dpm_levels[0].enabled = true;
		dpm_table->min = dpm_table->dpm_levels[0].value;
		dpm_table->max = dpm_table->dpm_levels[0].value;
	पूर्ण

	/* dclk1 dpm table setup */
	अगर (adev->vcn.num_vcn_inst > 1) अणु
		dpm_table = &dpm_context->dpm_tables.dclk1_table;
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_MM_DPM_PG_BIT)) अणु
			ret = smu_v11_0_set_single_dpm_table(smu,
							     SMU_DCLK1,
							     dpm_table);
			अगर (ret)
				वापस ret;
			dpm_table->is_fine_grained =
				!driver_ppt->DpmDescriptor[PPCLK_DCLK_1].SnapToDiscrete;
		पूर्ण अन्यथा अणु
			dpm_table->count = 1;
			dpm_table->dpm_levels[0].value =
				smu->smu_table.boot_values.dclk / 100;
			dpm_table->dpm_levels[0].enabled = true;
			dpm_table->min = dpm_table->dpm_levels[0].value;
			dpm_table->max = dpm_table->dpm_levels[0].value;
		पूर्ण
	पूर्ण

	/* dcefclk dpm table setup */
	dpm_table = &dpm_context->dpm_tables.dcef_table;
	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_DCEFCLK_BIT)) अणु
		ret = smu_v11_0_set_single_dpm_table(smu,
						     SMU_DCEFCLK,
						     dpm_table);
		अगर (ret)
			वापस ret;
		dpm_table->is_fine_grained =
			!driver_ppt->DpmDescriptor[PPCLK_DCEFCLK].SnapToDiscrete;
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.dcefclk / 100;
		dpm_table->dpm_levels[0].enabled = true;
		dpm_table->min = dpm_table->dpm_levels[0].value;
		dpm_table->max = dpm_table->dpm_levels[0].value;
	पूर्ण

	/* pixelclk dpm table setup */
	dpm_table = &dpm_context->dpm_tables.pixel_table;
	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_DCEFCLK_BIT)) अणु
		ret = smu_v11_0_set_single_dpm_table(smu,
						     SMU_PIXCLK,
						     dpm_table);
		अगर (ret)
			वापस ret;
		dpm_table->is_fine_grained =
			!driver_ppt->DpmDescriptor[PPCLK_PIXCLK].SnapToDiscrete;
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.dcefclk / 100;
		dpm_table->dpm_levels[0].enabled = true;
		dpm_table->min = dpm_table->dpm_levels[0].value;
		dpm_table->max = dpm_table->dpm_levels[0].value;
	पूर्ण

	/* displayclk dpm table setup */
	dpm_table = &dpm_context->dpm_tables.display_table;
	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_DCEFCLK_BIT)) अणु
		ret = smu_v11_0_set_single_dpm_table(smu,
						     SMU_DISPCLK,
						     dpm_table);
		अगर (ret)
			वापस ret;
		dpm_table->is_fine_grained =
			!driver_ppt->DpmDescriptor[PPCLK_DISPCLK].SnapToDiscrete;
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.dcefclk / 100;
		dpm_table->dpm_levels[0].enabled = true;
		dpm_table->min = dpm_table->dpm_levels[0].value;
		dpm_table->max = dpm_table->dpm_levels[0].value;
	पूर्ण

	/* phyclk dpm table setup */
	dpm_table = &dpm_context->dpm_tables.phy_table;
	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_DCEFCLK_BIT)) अणु
		ret = smu_v11_0_set_single_dpm_table(smu,
						     SMU_PHYCLK,
						     dpm_table);
		अगर (ret)
			वापस ret;
		dpm_table->is_fine_grained =
			!driver_ppt->DpmDescriptor[PPCLK_PHYCLK].SnapToDiscrete;
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.dcefclk / 100;
		dpm_table->dpm_levels[0].enabled = true;
		dpm_table->min = dpm_table->dpm_levels[0].value;
		dpm_table->max = dpm_table->dpm_levels[0].value;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sienna_cichlid_dpm_set_vcn_enable(काष्ठा smu_context *smu, bool enable)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक ret = 0;

	अगर (enable) अणु
		/* vcn dpm on is a prerequisite क्रम vcn घातer gate messages */
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_MM_DPM_PG_BIT)) अणु
			ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_PowerUpVcn, 0, शून्य);
			अगर (ret)
				वापस ret;
			अगर (adev->vcn.num_vcn_inst > 1) अणु
				ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_PowerUpVcn,
								  0x10000, शून्य);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_MM_DPM_PG_BIT)) अणु
			ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_PowerDownVcn, 0, शून्य);
			अगर (ret)
				वापस ret;
			अगर (adev->vcn.num_vcn_inst > 1) अणु
				ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_PowerDownVcn,
								  0x10000, शून्य);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sienna_cichlid_dpm_set_jpeg_enable(काष्ठा smu_context *smu, bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (enable) अणु
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_MM_DPM_PG_BIT)) अणु
			ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_PowerUpJpeg, 0, शून्य);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_MM_DPM_PG_BIT)) अणु
			ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_PowerDownJpeg, 0, शून्य);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sienna_cichlid_get_current_clk_freq_by_table(काष्ठा smu_context *smu,
				       क्रमागत smu_clk_type clk_type,
				       uपूर्णांक32_t *value)
अणु
	MetricsMember_t member_type;
	पूर्णांक clk_id = 0;

	clk_id = smu_cmn_to_asic_specअगरic_index(smu,
						CMN2ASIC_MAPPING_CLK,
						clk_type);
	अगर (clk_id < 0)
		वापस clk_id;

	चयन (clk_id) अणु
	हाल PPCLK_GFXCLK:
		member_type = METRICS_CURR_GFXCLK;
		अवरोध;
	हाल PPCLK_UCLK:
		member_type = METRICS_CURR_UCLK;
		अवरोध;
	हाल PPCLK_SOCCLK:
		member_type = METRICS_CURR_SOCCLK;
		अवरोध;
	हाल PPCLK_FCLK:
		member_type = METRICS_CURR_FCLK;
		अवरोध;
	हाल PPCLK_VCLK_0:
		member_type = METRICS_CURR_VCLK;
		अवरोध;
	हाल PPCLK_VCLK_1:
		member_type = METRICS_CURR_VCLK1;
		अवरोध;
	हाल PPCLK_DCLK_0:
		member_type = METRICS_CURR_DCLK;
		अवरोध;
	हाल PPCLK_DCLK_1:
		member_type = METRICS_CURR_DCLK1;
		अवरोध;
	हाल PPCLK_DCEFCLK:
		member_type = METRICS_CURR_DCEFCLK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस sienna_cichlid_get_smu_metrics_data(smu,
						   member_type,
						   value);

पूर्ण

अटल bool sienna_cichlid_is_support_fine_grained_dpm(काष्ठा smu_context *smu, क्रमागत smu_clk_type clk_type)
अणु
	PPTable_t *pptable = smu->smu_table.driver_pptable;
	DpmDescriptor_t *dpm_desc = शून्य;
	uपूर्णांक32_t clk_index = 0;

	clk_index = smu_cmn_to_asic_specअगरic_index(smu,
						   CMN2ASIC_MAPPING_CLK,
						   clk_type);
	dpm_desc = &pptable->DpmDescriptor[clk_index];

	/* 0 - Fine grained DPM, 1 - Discrete DPM */
	वापस dpm_desc->SnapToDiscrete == 0;
पूर्ण

अटल bool sienna_cichlid_is_od_feature_supported(काष्ठा smu_11_0_7_overdrive_table *od_table,
						   क्रमागत SMU_11_0_7_ODFEATURE_CAP cap)
अणु
	वापस od_table->cap[cap];
पूर्ण

अटल व्योम sienna_cichlid_get_od_setting_range(काष्ठा smu_11_0_7_overdrive_table *od_table,
						क्रमागत SMU_11_0_7_ODSETTING_ID setting,
						uपूर्णांक32_t *min, uपूर्णांक32_t *max)
अणु
	अगर (min)
		*min = od_table->min[setting];
	अगर (max)
		*max = od_table->max[setting];
पूर्ण

अटल पूर्णांक sienna_cichlid_prपूर्णांक_clk_levels(काष्ठा smu_context *smu,
			क्रमागत smu_clk_type clk_type, अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	काष्ठा smu_dpm_context *smu_dpm = &smu->smu_dpm;
	काष्ठा smu_11_0_dpm_context *dpm_context = smu_dpm->dpm_context;
	PPTable_t *pptable = (PPTable_t *)table_context->driver_pptable;
	काष्ठा smu_11_0_7_overdrive_table *od_settings = smu->od_settings;
	OverDriveTable_t *od_table =
		(OverDriveTable_t *)table_context->overdrive_table;
	पूर्णांक i, size = 0, ret = 0;
	uपूर्णांक32_t cur_value = 0, value = 0, count = 0;
	uपूर्णांक32_t freq_values[3] = अणु0पूर्ण;
	uपूर्णांक32_t mark_index = 0;
	uपूर्णांक32_t gen_speed, lane_width;
	uपूर्णांक32_t min_value, max_value;
	uपूर्णांक32_t smu_version;

	चयन (clk_type) अणु
	हाल SMU_GFXCLK:
	हाल SMU_SCLK:
	हाल SMU_SOCCLK:
	हाल SMU_MCLK:
	हाल SMU_UCLK:
	हाल SMU_FCLK:
	हाल SMU_DCEFCLK:
		ret = sienna_cichlid_get_current_clk_freq_by_table(smu, clk_type, &cur_value);
		अगर (ret)
			जाओ prपूर्णांक_clk_out;

		/* no need to disable gfxoff when retrieving the current gfxclk */
		अगर ((clk_type == SMU_GFXCLK) || (clk_type == SMU_SCLK))
			amdgpu_gfx_off_ctrl(adev, false);

		ret = smu_v11_0_get_dpm_level_count(smu, clk_type, &count);
		अगर (ret)
			जाओ prपूर्णांक_clk_out;

		अगर (!sienna_cichlid_is_support_fine_grained_dpm(smu, clk_type)) अणु
			क्रम (i = 0; i < count; i++) अणु
				ret = smu_v11_0_get_dpm_freq_by_index(smu, clk_type, i, &value);
				अगर (ret)
					जाओ prपूर्णांक_clk_out;

				size += प्र_लिखो(buf + size, "%d: %uMhz %s\n", i, value,
						cur_value == value ? "*" : "");
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = smu_v11_0_get_dpm_freq_by_index(smu, clk_type, 0, &freq_values[0]);
			अगर (ret)
				जाओ prपूर्णांक_clk_out;
			ret = smu_v11_0_get_dpm_freq_by_index(smu, clk_type, count - 1, &freq_values[2]);
			अगर (ret)
				जाओ prपूर्णांक_clk_out;

			freq_values[1] = cur_value;
			mark_index = cur_value == freq_values[0] ? 0 :
				     cur_value == freq_values[2] ? 2 : 1;

			count = 3;
			अगर (mark_index != 1) अणु
				count = 2;
				freq_values[1] = freq_values[2];
			पूर्ण

			क्रम (i = 0; i < count; i++) अणु
				size += प्र_लिखो(buf + size, "%d: %uMhz %s\n", i, freq_values[i],
						cur_value  == freq_values[i] ? "*" : "");
			पूर्ण

		पूर्ण
		अवरोध;
	हाल SMU_PCIE:
		gen_speed = smu_v11_0_get_current_pcie_link_speed_level(smu);
		lane_width = smu_v11_0_get_current_pcie_link_width_level(smu);
		क्रम (i = 0; i < NUM_LINK_LEVELS; i++)
			size += प्र_लिखो(buf + size, "%d: %s %s %dMhz %s\n", i,
					(dpm_context->dpm_tables.pcie_table.pcie_gen[i] == 0) ? "2.5GT/s," :
					(dpm_context->dpm_tables.pcie_table.pcie_gen[i] == 1) ? "5.0GT/s," :
					(dpm_context->dpm_tables.pcie_table.pcie_gen[i] == 2) ? "8.0GT/s," :
					(dpm_context->dpm_tables.pcie_table.pcie_gen[i] == 3) ? "16.0GT/s," : "",
					(dpm_context->dpm_tables.pcie_table.pcie_lane[i] == 1) ? "x1" :
					(dpm_context->dpm_tables.pcie_table.pcie_lane[i] == 2) ? "x2" :
					(dpm_context->dpm_tables.pcie_table.pcie_lane[i] == 3) ? "x4" :
					(dpm_context->dpm_tables.pcie_table.pcie_lane[i] == 4) ? "x8" :
					(dpm_context->dpm_tables.pcie_table.pcie_lane[i] == 5) ? "x12" :
					(dpm_context->dpm_tables.pcie_table.pcie_lane[i] == 6) ? "x16" : "",
					pptable->LclkFreq[i],
					(gen_speed == dpm_context->dpm_tables.pcie_table.pcie_gen[i]) &&
					(lane_width == dpm_context->dpm_tables.pcie_table.pcie_lane[i]) ?
					"*" : "");
		अवरोध;
	हाल SMU_OD_SCLK:
		अगर (!smu->od_enabled || !od_table || !od_settings)
			अवरोध;

		अगर (!sienna_cichlid_is_od_feature_supported(od_settings, SMU_11_0_7_ODCAP_GFXCLK_LIMITS))
			अवरोध;

		size += प्र_लिखो(buf + size, "OD_SCLK:\n");
		size += प्र_लिखो(buf + size, "0: %uMhz\n1: %uMhz\n", od_table->GfxclkFmin, od_table->GfxclkFmax);
		अवरोध;

	हाल SMU_OD_MCLK:
		अगर (!smu->od_enabled || !od_table || !od_settings)
			अवरोध;

		अगर (!sienna_cichlid_is_od_feature_supported(od_settings, SMU_11_0_7_ODCAP_UCLK_LIMITS))
			अवरोध;

		size += प्र_लिखो(buf + size, "OD_MCLK:\n");
		size += प्र_लिखो(buf + size, "0: %uMhz\n1: %uMHz\n", od_table->UclkFmin, od_table->UclkFmax);
		अवरोध;

	हाल SMU_OD_VDDGFX_OFFSET:
		अगर (!smu->od_enabled || !od_table || !od_settings)
			अवरोध;

		/*
		 * OD GFX Voltage Offset functionality is supported only by 58.41.0
		 * and onwards SMU firmwares.
		 */
		smu_cmn_get_smc_version(smu, शून्य, &smu_version);
		अगर ((adev->asic_type == CHIP_SIENNA_CICHLID) &&
		     (smu_version < 0x003a2900))
			अवरोध;

		size += प्र_लिखो(buf + size, "OD_VDDGFX_OFFSET:\n");
		size += प्र_लिखो(buf + size, "%dmV\n", od_table->VddGfxOffset);
		अवरोध;

	हाल SMU_OD_RANGE:
		अगर (!smu->od_enabled || !od_table || !od_settings)
			अवरोध;

		size = प्र_लिखो(buf, "%s:\n", "OD_RANGE");

		अगर (sienna_cichlid_is_od_feature_supported(od_settings, SMU_11_0_7_ODCAP_GFXCLK_LIMITS)) अणु
			sienna_cichlid_get_od_setting_range(od_settings, SMU_11_0_7_ODSETTING_GFXCLKFMIN,
							    &min_value, शून्य);
			sienna_cichlid_get_od_setting_range(od_settings, SMU_11_0_7_ODSETTING_GFXCLKFMAX,
							    शून्य, &max_value);
			size += प्र_लिखो(buf + size, "SCLK: %7uMhz %10uMhz\n",
					min_value, max_value);
		पूर्ण

		अगर (sienna_cichlid_is_od_feature_supported(od_settings, SMU_11_0_7_ODCAP_UCLK_LIMITS)) अणु
			sienna_cichlid_get_od_setting_range(od_settings, SMU_11_0_7_ODSETTING_UCLKFMIN,
							    &min_value, शून्य);
			sienna_cichlid_get_od_setting_range(od_settings, SMU_11_0_7_ODSETTING_UCLKFMAX,
							    शून्य, &max_value);
			size += प्र_लिखो(buf + size, "MCLK: %7uMhz %10uMhz\n",
					min_value, max_value);
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

prपूर्णांक_clk_out:
	अगर ((clk_type == SMU_GFXCLK) || (clk_type == SMU_SCLK))
		amdgpu_gfx_off_ctrl(adev, true);

	वापस size;
पूर्ण

अटल पूर्णांक sienna_cichlid_क्रमce_clk_levels(काष्ठा smu_context *smu,
				   क्रमागत smu_clk_type clk_type, uपूर्णांक32_t mask)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक ret = 0, size = 0;
	uपूर्णांक32_t soft_min_level = 0, soft_max_level = 0, min_freq = 0, max_freq = 0;

	soft_min_level = mask ? (ffs(mask) - 1) : 0;
	soft_max_level = mask ? (fls(mask) - 1) : 0;

	अगर ((clk_type == SMU_GFXCLK) || (clk_type == SMU_SCLK))
		amdgpu_gfx_off_ctrl(adev, false);

	चयन (clk_type) अणु
	हाल SMU_GFXCLK:
	हाल SMU_SCLK:
	हाल SMU_SOCCLK:
	हाल SMU_MCLK:
	हाल SMU_UCLK:
	हाल SMU_FCLK:
		/* There is only 2 levels क्रम fine grained DPM */
		अगर (sienna_cichlid_is_support_fine_grained_dpm(smu, clk_type)) अणु
			soft_max_level = (soft_max_level >= 1 ? 1 : 0);
			soft_min_level = (soft_min_level >= 1 ? 1 : 0);
		पूर्ण

		ret = smu_v11_0_get_dpm_freq_by_index(smu, clk_type, soft_min_level, &min_freq);
		अगर (ret)
			जाओ क्रमec_level_out;

		ret = smu_v11_0_get_dpm_freq_by_index(smu, clk_type, soft_max_level, &max_freq);
		अगर (ret)
			जाओ क्रमec_level_out;

		ret = smu_v11_0_set_soft_freq_limited_range(smu, clk_type, min_freq, max_freq);
		अगर (ret)
			जाओ क्रमec_level_out;
		अवरोध;
	हाल SMU_DCEFCLK:
		dev_info(smu->adev->dev,"Setting DCEFCLK min/max dpm level is not supported!\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

क्रमec_level_out:
	अगर ((clk_type == SMU_GFXCLK) || (clk_type == SMU_SCLK))
		amdgpu_gfx_off_ctrl(adev, true);

	वापस size;
पूर्ण

अटल पूर्णांक sienna_cichlid_populate_umd_state_clk(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_11_0_dpm_context *dpm_context =
				smu->smu_dpm.dpm_context;
	काष्ठा smu_11_0_dpm_table *gfx_table =
				&dpm_context->dpm_tables.gfx_table;
	काष्ठा smu_11_0_dpm_table *mem_table =
				&dpm_context->dpm_tables.uclk_table;
	काष्ठा smu_11_0_dpm_table *soc_table =
				&dpm_context->dpm_tables.soc_table;
	काष्ठा smu_umd_pstate_table *pstate_table =
				&smu->pstate_table;

	pstate_table->gfxclk_pstate.min = gfx_table->min;
	pstate_table->gfxclk_pstate.peak = gfx_table->max;
	अगर (gfx_table->max >= SIENNA_CICHLID_UMD_PSTATE_PROFILING_GFXCLK)
		pstate_table->gfxclk_pstate.standard = SIENNA_CICHLID_UMD_PSTATE_PROFILING_GFXCLK;

	pstate_table->uclk_pstate.min = mem_table->min;
	pstate_table->uclk_pstate.peak = mem_table->max;
	अगर (mem_table->max >= SIENNA_CICHLID_UMD_PSTATE_PROFILING_MEMCLK)
		pstate_table->uclk_pstate.standard = SIENNA_CICHLID_UMD_PSTATE_PROFILING_MEMCLK;

	pstate_table->socclk_pstate.min = soc_table->min;
	pstate_table->socclk_pstate.peak = soc_table->max;
	अगर (soc_table->max >= SIENNA_CICHLID_UMD_PSTATE_PROFILING_SOCCLK)
		pstate_table->socclk_pstate.standard = SIENNA_CICHLID_UMD_PSTATE_PROFILING_SOCCLK;

	वापस 0;
पूर्ण

अटल पूर्णांक sienna_cichlid_pre_display_config_changed(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t max_freq = 0;

	/* Sienna_Cichlid करो not support to change display num currently */
	वापस 0;
#अगर 0
	ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_NumOfDisplays, 0, शून्य);
	अगर (ret)
		वापस ret;
#पूर्ण_अगर

	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_UCLK_BIT)) अणु
		ret = smu_v11_0_get_dpm_ultimate_freq(smu, SMU_UCLK, शून्य, &max_freq);
		अगर (ret)
			वापस ret;
		ret = smu_v11_0_set_hard_freq_limited_range(smu, SMU_UCLK, 0, max_freq);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sienna_cichlid_display_config_changed(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	अगर ((smu->watermarks_biपंचांगap & WATERMARKS_EXIST) &&
	    smu_cmn_feature_is_supported(smu, SMU_FEATURE_DPM_DCEFCLK_BIT) &&
	    smu_cmn_feature_is_supported(smu, SMU_FEATURE_DPM_SOCCLK_BIT)) अणु
#अगर 0
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_NumOfDisplays,
						  smu->display_config->num_display,
						  शून्य);
#पूर्ण_अगर
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool sienna_cichlid_is_dpm_running(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t feature_mask[2];
	uपूर्णांक64_t feature_enabled;

	ret = smu_cmn_get_enabled_mask(smu, feature_mask, 2);
	अगर (ret)
		वापस false;

	feature_enabled = (uपूर्णांक64_t)feature_mask[1] << 32 | feature_mask[0];

	वापस !!(feature_enabled & SMC_DPM_FEATURE);
पूर्ण

अटल पूर्णांक sienna_cichlid_get_fan_speed_percent(काष्ठा smu_context *smu,
						uपूर्णांक32_t *speed)
अणु
	पूर्णांक ret;
	u32 rpm;

	अगर (!speed)
		वापस -EINVAL;

	चयन (smu_v11_0_get_fan_control_mode(smu)) अणु
	हाल AMD_FAN_CTRL_AUTO:
		ret = sienna_cichlid_get_smu_metrics_data(smu,
							  METRICS_CURR_FANSPEED,
							  &rpm);
		अगर (!ret && smu->fan_max_rpm)
			*speed = rpm * 100 / smu->fan_max_rpm;
		वापस ret;
	शेष:
		*speed = smu->user_dpm_profile.fan_speed_percent;
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक sienna_cichlid_get_fan_parameters(काष्ठा smu_context *smu)
अणु
	PPTable_t *pptable = smu->smu_table.driver_pptable;

	smu->fan_max_rpm = pptable->FanMaximumRpm;

	वापस 0;
पूर्ण

अटल पूर्णांक sienna_cichlid_get_घातer_profile_mode(काष्ठा smu_context *smu, अक्षर *buf)
अणु
	DpmActivityMonitorCoeffIntExternal_t activity_monitor_बाह्यal;
	DpmActivityMonitorCoeffInt_t *activity_monitor =
		&(activity_monitor_बाह्यal.DpmActivityMonitorCoeffInt);
	uपूर्णांक32_t i, size = 0;
	पूर्णांक16_t workload_type = 0;
	अटल स्थिर अक्षर *profile_name[] = अणु
					"BOOTUP_DEFAULT",
					"3D_FULL_SCREEN",
					"POWER_SAVING",
					"VIDEO",
					"VR",
					"COMPUTE",
					"CUSTOM"पूर्ण;
	अटल स्थिर अक्षर *title[] = अणु
			"PROFILE_INDEX(NAME)",
			"CLOCK_TYPE(NAME)",
			"FPS",
			"MinFreqType",
			"MinActiveFreqType",
			"MinActiveFreq",
			"BoosterFreqType",
			"BoosterFreq",
			"PD_Data_limit_c",
			"PD_Data_error_coeff",
			"PD_Data_error_rate_coeff"पूर्ण;
	पूर्णांक result = 0;

	अगर (!buf)
		वापस -EINVAL;

	size += प्र_लिखो(buf + size, "%16s %s %s %s %s %s %s %s %s %s %s\n",
			title[0], title[1], title[2], title[3], title[4], title[5],
			title[6], title[7], title[8], title[9], title[10]);

	क्रम (i = 0; i <= PP_SMC_POWER_PROखाता_CUSTOM; i++) अणु
		/* conv PP_SMC_POWER_PROखाता* to WORKLOAD_PPLIB_*_BIT */
		workload_type = smu_cmn_to_asic_specअगरic_index(smu,
							       CMN2ASIC_MAPPING_WORKLOAD,
							       i);
		अगर (workload_type < 0)
			वापस -EINVAL;

		result = smu_cmn_update_table(smu,
					  SMU_TABLE_ACTIVITY_MONITOR_COEFF, workload_type,
					  (व्योम *)(&activity_monitor_बाह्यal), false);
		अगर (result) अणु
			dev_err(smu->adev->dev, "[%s] Failed to get activity monitor!", __func__);
			वापस result;
		पूर्ण

		size += प्र_लिखो(buf + size, "%2d %14s%s:\n",
			i, profile_name[i], (i == smu->घातer_profile_mode) ? "*" : " ");

		size += प्र_लिखो(buf + size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d %7d\n",
			" ",
			0,
			"GFXCLK",
			activity_monitor->Gfx_FPS,
			activity_monitor->Gfx_MinFreqStep,
			activity_monitor->Gfx_MinActiveFreqType,
			activity_monitor->Gfx_MinActiveFreq,
			activity_monitor->Gfx_BoosterFreqType,
			activity_monitor->Gfx_BoosterFreq,
			activity_monitor->Gfx_PD_Data_limit_c,
			activity_monitor->Gfx_PD_Data_error_coeff,
			activity_monitor->Gfx_PD_Data_error_rate_coeff);

		size += प्र_लिखो(buf + size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d %7d\n",
			" ",
			1,
			"SOCCLK",
			activity_monitor->Fclk_FPS,
			activity_monitor->Fclk_MinFreqStep,
			activity_monitor->Fclk_MinActiveFreqType,
			activity_monitor->Fclk_MinActiveFreq,
			activity_monitor->Fclk_BoosterFreqType,
			activity_monitor->Fclk_BoosterFreq,
			activity_monitor->Fclk_PD_Data_limit_c,
			activity_monitor->Fclk_PD_Data_error_coeff,
			activity_monitor->Fclk_PD_Data_error_rate_coeff);

		size += प्र_लिखो(buf + size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d %7d\n",
			" ",
			2,
			"MEMLK",
			activity_monitor->Mem_FPS,
			activity_monitor->Mem_MinFreqStep,
			activity_monitor->Mem_MinActiveFreqType,
			activity_monitor->Mem_MinActiveFreq,
			activity_monitor->Mem_BoosterFreqType,
			activity_monitor->Mem_BoosterFreq,
			activity_monitor->Mem_PD_Data_limit_c,
			activity_monitor->Mem_PD_Data_error_coeff,
			activity_monitor->Mem_PD_Data_error_rate_coeff);
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक sienna_cichlid_set_घातer_profile_mode(काष्ठा smu_context *smu, दीर्घ *input, uपूर्णांक32_t size)
अणु

	DpmActivityMonitorCoeffIntExternal_t activity_monitor_बाह्यal;
	DpmActivityMonitorCoeffInt_t *activity_monitor =
		&(activity_monitor_बाह्यal.DpmActivityMonitorCoeffInt);
	पूर्णांक workload_type, ret = 0;

	smu->घातer_profile_mode = input[size];

	अगर (smu->घातer_profile_mode > PP_SMC_POWER_PROखाता_CUSTOM) अणु
		dev_err(smu->adev->dev, "Invalid power profile mode %d\n", smu->घातer_profile_mode);
		वापस -EINVAL;
	पूर्ण

	अगर (smu->घातer_profile_mode == PP_SMC_POWER_PROखाता_CUSTOM) अणु

		ret = smu_cmn_update_table(smu,
				       SMU_TABLE_ACTIVITY_MONITOR_COEFF, WORKLOAD_PPLIB_CUSTOM_BIT,
				       (व्योम *)(&activity_monitor_बाह्यal), false);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "[%s] Failed to get activity monitor!", __func__);
			वापस ret;
		पूर्ण

		चयन (input[0]) अणु
		हाल 0: /* Gfxclk */
			activity_monitor->Gfx_FPS = input[1];
			activity_monitor->Gfx_MinFreqStep = input[2];
			activity_monitor->Gfx_MinActiveFreqType = input[3];
			activity_monitor->Gfx_MinActiveFreq = input[4];
			activity_monitor->Gfx_BoosterFreqType = input[5];
			activity_monitor->Gfx_BoosterFreq = input[6];
			activity_monitor->Gfx_PD_Data_limit_c = input[7];
			activity_monitor->Gfx_PD_Data_error_coeff = input[8];
			activity_monitor->Gfx_PD_Data_error_rate_coeff = input[9];
			अवरोध;
		हाल 1: /* Socclk */
			activity_monitor->Fclk_FPS = input[1];
			activity_monitor->Fclk_MinFreqStep = input[2];
			activity_monitor->Fclk_MinActiveFreqType = input[3];
			activity_monitor->Fclk_MinActiveFreq = input[4];
			activity_monitor->Fclk_BoosterFreqType = input[5];
			activity_monitor->Fclk_BoosterFreq = input[6];
			activity_monitor->Fclk_PD_Data_limit_c = input[7];
			activity_monitor->Fclk_PD_Data_error_coeff = input[8];
			activity_monitor->Fclk_PD_Data_error_rate_coeff = input[9];
			अवरोध;
		हाल 2: /* Memlk */
			activity_monitor->Mem_FPS = input[1];
			activity_monitor->Mem_MinFreqStep = input[2];
			activity_monitor->Mem_MinActiveFreqType = input[3];
			activity_monitor->Mem_MinActiveFreq = input[4];
			activity_monitor->Mem_BoosterFreqType = input[5];
			activity_monitor->Mem_BoosterFreq = input[6];
			activity_monitor->Mem_PD_Data_limit_c = input[7];
			activity_monitor->Mem_PD_Data_error_coeff = input[8];
			activity_monitor->Mem_PD_Data_error_rate_coeff = input[9];
			अवरोध;
		पूर्ण

		ret = smu_cmn_update_table(smu,
				       SMU_TABLE_ACTIVITY_MONITOR_COEFF, WORKLOAD_PPLIB_CUSTOM_BIT,
				       (व्योम *)(&activity_monitor_बाह्यal), true);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "[%s] Failed to set activity monitor!", __func__);
			वापस ret;
		पूर्ण
	पूर्ण

	/* conv PP_SMC_POWER_PROखाता* to WORKLOAD_PPLIB_*_BIT */
	workload_type = smu_cmn_to_asic_specअगरic_index(smu,
						       CMN2ASIC_MAPPING_WORKLOAD,
						       smu->घातer_profile_mode);
	अगर (workload_type < 0)
		वापस -EINVAL;
	smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetWorkloadMask,
				    1 << workload_type, शून्य);

	वापस ret;
पूर्ण

अटल पूर्णांक sienna_cichlid_notअगरy_smc_display_config(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_घड़ीs min_घड़ीs = अणु0पूर्ण;
	काष्ठा pp_display_घड़ी_request घड़ी_req;
	पूर्णांक ret = 0;

	min_घड़ीs.dcef_घड़ी = smu->display_config->min_dcef_set_clk;
	min_घड़ीs.dcef_घड़ी_in_sr = smu->display_config->min_dcef_deep_sleep_set_clk;
	min_घड़ीs.memory_घड़ी = smu->display_config->min_mem_set_घड़ी;

	अगर (smu_cmn_feature_is_supported(smu, SMU_FEATURE_DPM_DCEFCLK_BIT)) अणु
		घड़ी_req.घड़ी_प्रकारype = amd_pp_dcef_घड़ी;
		घड़ी_req.घड़ी_freq_in_khz = min_घड़ीs.dcef_घड़ी * 10;

		ret = smu_v11_0_display_घड़ी_voltage_request(smu, &घड़ी_req);
		अगर (!ret) अणु
			अगर (smu_cmn_feature_is_supported(smu, SMU_FEATURE_DS_DCEFCLK_BIT)) अणु
				ret = smu_cmn_send_smc_msg_with_param(smu,
								  SMU_MSG_SetMinDeepSleepDcefclk,
								  min_घड़ीs.dcef_घड़ी_in_sr/100,
								  शून्य);
				अगर (ret) अणु
					dev_err(smu->adev->dev, "Attempt to set divider for DCEFCLK Failed!");
					वापस ret;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_info(smu->adev->dev, "Attempt to set Hard Min for DCEFCLK Failed!");
		पूर्ण
	पूर्ण

	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_UCLK_BIT)) अणु
		ret = smu_v11_0_set_hard_freq_limited_range(smu, SMU_UCLK, min_घड़ीs.memory_घड़ी/100, 0);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "[%s] Set hard min uclk failed!", __func__);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sienna_cichlid_set_watermarks_table(काष्ठा smu_context *smu,
					       काष्ठा pp_smu_wm_range_sets *घड़ी_ranges)
अणु
	Watermarks_t *table = smu->smu_table.watermarks_table;
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (घड़ी_ranges) अणु
		अगर (घड़ी_ranges->num_पढ़ोer_wm_sets > NUM_WM_RANGES ||
		    घड़ी_ranges->num_ग_लिखोr_wm_sets > NUM_WM_RANGES)
			वापस -EINVAL;

		क्रम (i = 0; i < घड़ी_ranges->num_पढ़ोer_wm_sets; i++) अणु
			table->WatermarkRow[WM_DCEFCLK][i].MinClock =
				घड़ी_ranges->पढ़ोer_wm_sets[i].min_drain_clk_mhz;
			table->WatermarkRow[WM_DCEFCLK][i].MaxClock =
				घड़ी_ranges->पढ़ोer_wm_sets[i].max_drain_clk_mhz;
			table->WatermarkRow[WM_DCEFCLK][i].MinUclk =
				घड़ी_ranges->पढ़ोer_wm_sets[i].min_fill_clk_mhz;
			table->WatermarkRow[WM_DCEFCLK][i].MaxUclk =
				घड़ी_ranges->पढ़ोer_wm_sets[i].max_fill_clk_mhz;

			table->WatermarkRow[WM_DCEFCLK][i].WmSetting =
				घड़ी_ranges->पढ़ोer_wm_sets[i].wm_inst;
		पूर्ण

		क्रम (i = 0; i < घड़ी_ranges->num_ग_लिखोr_wm_sets; i++) अणु
			table->WatermarkRow[WM_SOCCLK][i].MinClock =
				घड़ी_ranges->ग_लिखोr_wm_sets[i].min_fill_clk_mhz;
			table->WatermarkRow[WM_SOCCLK][i].MaxClock =
				घड़ी_ranges->ग_लिखोr_wm_sets[i].max_fill_clk_mhz;
			table->WatermarkRow[WM_SOCCLK][i].MinUclk =
				घड़ी_ranges->ग_लिखोr_wm_sets[i].min_drain_clk_mhz;
			table->WatermarkRow[WM_SOCCLK][i].MaxUclk =
				घड़ी_ranges->ग_लिखोr_wm_sets[i].max_drain_clk_mhz;

			table->WatermarkRow[WM_SOCCLK][i].WmSetting =
				घड़ी_ranges->ग_लिखोr_wm_sets[i].wm_inst;
		पूर्ण

		smu->watermarks_biपंचांगap |= WATERMARKS_EXIST;
	पूर्ण

	अगर ((smu->watermarks_biपंचांगap & WATERMARKS_EXIST) &&
	     !(smu->watermarks_biपंचांगap & WATERMARKS_LOADED)) अणु
		ret = smu_cmn_ग_लिखो_watermarks_table(smu);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Failed to update WMTABLE!");
			वापस ret;
		पूर्ण
		smu->watermarks_biपंचांगap |= WATERMARKS_LOADED;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sienna_cichlid_पढ़ो_sensor(काष्ठा smu_context *smu,
				 क्रमागत amd_pp_sensors sensor,
				 व्योम *data, uपूर्णांक32_t *size)
अणु
	पूर्णांक ret = 0;
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	PPTable_t *pptable = table_context->driver_pptable;

	अगर(!data || !size)
		वापस -EINVAL;

	mutex_lock(&smu->sensor_lock);
	चयन (sensor) अणु
	हाल AMDGPU_PP_SENSOR_MAX_FAN_RPM:
		*(uपूर्णांक32_t *)data = pptable->FanMaximumRpm;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_MEM_LOAD:
		ret = sienna_cichlid_get_smu_metrics_data(smu,
							  METRICS_AVERAGE_MEMACTIVITY,
							  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GPU_LOAD:
		ret = sienna_cichlid_get_smu_metrics_data(smu,
							  METRICS_AVERAGE_GFXACTIVITY,
							  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GPU_POWER:
		ret = sienna_cichlid_get_smu_metrics_data(smu,
							  METRICS_AVERAGE_SOCKETPOWER,
							  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_HOTSPOT_TEMP:
		ret = sienna_cichlid_get_smu_metrics_data(smu,
							  METRICS_TEMPERATURE_HOTSPOT,
							  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_EDGE_TEMP:
		ret = sienna_cichlid_get_smu_metrics_data(smu,
							  METRICS_TEMPERATURE_EDGE,
							  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_MEM_TEMP:
		ret = sienna_cichlid_get_smu_metrics_data(smu,
							  METRICS_TEMPERATURE_MEM,
							  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GFX_MCLK:
		ret = sienna_cichlid_get_current_clk_freq_by_table(smu, SMU_UCLK, (uपूर्णांक32_t *)data);
		*(uपूर्णांक32_t *)data *= 100;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GFX_SCLK:
		ret = sienna_cichlid_get_current_clk_freq_by_table(smu, SMU_GFXCLK, (uपूर्णांक32_t *)data);
		*(uपूर्णांक32_t *)data *= 100;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_VDDGFX:
		ret = smu_v11_0_get_gfx_vdd(smu, (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	mutex_unlock(&smu->sensor_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक sienna_cichlid_get_uclk_dpm_states(काष्ठा smu_context *smu, uपूर्णांक32_t *घड़ीs_in_khz, uपूर्णांक32_t *num_states)
अणु
	uपूर्णांक32_t num_discrete_levels = 0;
	uपूर्णांक16_t *dpm_levels = शून्य;
	uपूर्णांक16_t i = 0;
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	PPTable_t *driver_ppt = शून्य;

	अगर (!घड़ीs_in_khz || !num_states || !table_context->driver_pptable)
		वापस -EINVAL;

	driver_ppt = table_context->driver_pptable;
	num_discrete_levels = driver_ppt->DpmDescriptor[PPCLK_UCLK].NumDiscreteLevels;
	dpm_levels = driver_ppt->FreqTableUclk;

	अगर (num_discrete_levels == 0 || dpm_levels == शून्य)
		वापस -EINVAL;

	*num_states = num_discrete_levels;
	क्रम (i = 0; i < num_discrete_levels; i++) अणु
		/* convert to khz */
		*घड़ीs_in_khz = (*dpm_levels) * 1000;
		घड़ीs_in_khz++;
		dpm_levels++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sienna_cichlid_get_thermal_temperature_range(काष्ठा smu_context *smu,
						काष्ठा smu_temperature_range *range)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	काष्ठा smu_11_0_7_घातerplay_table *घातerplay_table =
				table_context->घातer_play_table;
	PPTable_t *pptable = smu->smu_table.driver_pptable;

	अगर (!range)
		वापस -EINVAL;

	स_नकल(range, &smu11_thermal_policy[0], माप(काष्ठा smu_temperature_range));

	range->max = pptable->TemperatureLimit[TEMP_EDGE] *
		SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
	range->edge_emergency_max = (pptable->TemperatureLimit[TEMP_EDGE] + CTF_OFFSET_EDGE) *
		SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
	range->hotspot_crit_max = pptable->TemperatureLimit[TEMP_HOTSPOT] *
		SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
	range->hotspot_emergency_max = (pptable->TemperatureLimit[TEMP_HOTSPOT] + CTF_OFFSET_HOTSPOT) *
		SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
	range->mem_crit_max = pptable->TemperatureLimit[TEMP_MEM] *
		SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
	range->mem_emergency_max = (pptable->TemperatureLimit[TEMP_MEM] + CTF_OFFSET_MEM)*
		SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
	range->software_shutकरोwn_temp = घातerplay_table->software_shutकरोwn_temp;

	वापस 0;
पूर्ण

अटल पूर्णांक sienna_cichlid_display_disable_memory_घड़ी_चयन(काष्ठा smu_context *smu,
						bool disable_memory_घड़ी_चयन)
अणु
	पूर्णांक ret = 0;
	काष्ठा smu_11_0_max_sustainable_घड़ीs *max_sustainable_घड़ीs =
		(काष्ठा smu_11_0_max_sustainable_घड़ीs *)
			smu->smu_table.max_sustainable_घड़ीs;
	uपूर्णांक32_t min_memory_घड़ी = smu->hard_min_uclk_req_from_dal;
	uपूर्णांक32_t max_memory_घड़ी = max_sustainable_घड़ीs->uघड़ी;

	अगर(smu->disable_uclk_चयन == disable_memory_घड़ी_चयन)
		वापस 0;

	अगर(disable_memory_घड़ी_चयन)
		ret = smu_v11_0_set_hard_freq_limited_range(smu, SMU_UCLK, max_memory_घड़ी, 0);
	अन्यथा
		ret = smu_v11_0_set_hard_freq_limited_range(smu, SMU_UCLK, min_memory_घड़ी, 0);

	अगर(!ret)
		smu->disable_uclk_चयन = disable_memory_घड़ी_चयन;

	वापस ret;
पूर्ण

अटल पूर्णांक sienna_cichlid_get_घातer_limit(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_11_0_7_घातerplay_table *घातerplay_table =
		(काष्ठा smu_11_0_7_घातerplay_table *)smu->smu_table.घातer_play_table;
	PPTable_t *pptable = smu->smu_table.driver_pptable;
	uपूर्णांक32_t घातer_limit, od_percent;

	अगर (smu_v11_0_get_current_घातer_limit(smu, &घातer_limit)) अणु
		/* the last hope to figure out the ppt limit */
		अगर (!pptable) अणु
			dev_err(smu->adev->dev, "Cannot get PPT limit due to pptable missing!");
			वापस -EINVAL;
		पूर्ण
		घातer_limit =
			pptable->SocketPowerLimitAc[PPT_THROTTLER_PPT0];
	पूर्ण
	smu->current_घातer_limit = smu->शेष_घातer_limit = घातer_limit;

	अगर (smu->od_enabled) अणु
		od_percent = le32_to_cpu(घातerplay_table->overdrive_table.max[SMU_11_0_7_ODSETTING_POWERPERCENTAGE]);

		dev_dbg(smu->adev->dev, "ODSETTING_POWERPERCENTAGE: %d (default: %d)\n", od_percent, घातer_limit);

		घातer_limit *= (100 + od_percent);
		घातer_limit /= 100;
	पूर्ण
	smu->max_घातer_limit = घातer_limit;

	वापस 0;
पूर्ण

अटल पूर्णांक sienna_cichlid_update_pcie_parameters(काष्ठा smu_context *smu,
					 uपूर्णांक32_t pcie_gen_cap,
					 uपूर्णांक32_t pcie_width_cap)
अणु
	काष्ठा smu_11_0_dpm_context *dpm_context = smu->smu_dpm.dpm_context;
	PPTable_t *pptable = smu->smu_table.driver_pptable;
	uपूर्णांक32_t smu_pcie_arg;
	पूर्णांक ret, i;

	/* lclk dpm table setup */
	क्रम (i = 0; i < MAX_PCIE_CONF; i++) अणु
		dpm_context->dpm_tables.pcie_table.pcie_gen[i] = pptable->PcieGenSpeed[i];
		dpm_context->dpm_tables.pcie_table.pcie_lane[i] = pptable->PcieLaneCount[i];
	पूर्ण

	क्रम (i = 0; i < NUM_LINK_LEVELS; i++) अणु
		smu_pcie_arg = (i << 16) |
			((pptable->PcieGenSpeed[i] <= pcie_gen_cap) ?
					(pptable->PcieGenSpeed[i] << 8) :
					(pcie_gen_cap << 8)) |
			((pptable->PcieLaneCount[i] <= pcie_width_cap) ?
					pptable->PcieLaneCount[i] :
					pcie_width_cap);

		ret = smu_cmn_send_smc_msg_with_param(smu,
					  SMU_MSG_OverridePcieParameters,
					  smu_pcie_arg,
					  शून्य);

		अगर (ret)
			वापस ret;

		अगर (pptable->PcieGenSpeed[i] > pcie_gen_cap)
			dpm_context->dpm_tables.pcie_table.pcie_gen[i] = pcie_gen_cap;
		अगर (pptable->PcieLaneCount[i] > pcie_width_cap)
			dpm_context->dpm_tables.pcie_table.pcie_lane[i] = pcie_width_cap;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sienna_cichlid_get_dpm_ultimate_freq(काष्ठा smu_context *smu,
				क्रमागत smu_clk_type clk_type,
				uपूर्णांक32_t *min, uपूर्णांक32_t *max)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक ret;

	अगर (clk_type == SMU_GFXCLK)
		amdgpu_gfx_off_ctrl(adev, false);
	ret = smu_v11_0_get_dpm_ultimate_freq(smu, clk_type, min, max);
	अगर (clk_type == SMU_GFXCLK)
		amdgpu_gfx_off_ctrl(adev, true);

	वापस ret;
पूर्ण

अटल व्योम sienna_cichlid_dump_od_table(काष्ठा smu_context *smu,
					 OverDriveTable_t *od_table)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t smu_version;

	dev_dbg(smu->adev->dev, "OD: Gfxclk: (%d, %d)\n", od_table->GfxclkFmin,
							  od_table->GfxclkFmax);
	dev_dbg(smu->adev->dev, "OD: Uclk: (%d, %d)\n", od_table->UclkFmin,
							od_table->UclkFmax);

	smu_cmn_get_smc_version(smu, शून्य, &smu_version);
	अगर (!((adev->asic_type == CHIP_SIENNA_CICHLID) &&
	       (smu_version < 0x003a2900)))
		dev_dbg(smu->adev->dev, "OD: VddGfxOffset: %d\n", od_table->VddGfxOffset);
पूर्ण

अटल पूर्णांक sienna_cichlid_set_शेष_od_settings(काष्ठा smu_context *smu)
अणु
	OverDriveTable_t *od_table =
		(OverDriveTable_t *)smu->smu_table.overdrive_table;
	OverDriveTable_t *boot_od_table =
		(OverDriveTable_t *)smu->smu_table.boot_overdrive_table;
	पूर्णांक ret = 0;

	ret = smu_cmn_update_table(smu, SMU_TABLE_OVERDRIVE,
				   0, (व्योम *)od_table, false);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "Failed to get overdrive table!\n");
		वापस ret;
	पूर्ण

	स_नकल(boot_od_table, od_table, माप(OverDriveTable_t));

	sienna_cichlid_dump_od_table(smu, od_table);

	वापस 0;
पूर्ण

अटल पूर्णांक sienna_cichlid_od_setting_check_range(काष्ठा smu_context *smu,
						 काष्ठा smu_11_0_7_overdrive_table *od_table,
						 क्रमागत SMU_11_0_7_ODSETTING_ID setting,
						 uपूर्णांक32_t value)
अणु
	अगर (value < od_table->min[setting]) अणु
		dev_warn(smu->adev->dev, "OD setting (%d, %d) is less than the minimum allowed (%d)\n",
					  setting, value, od_table->min[setting]);
		वापस -EINVAL;
	पूर्ण
	अगर (value > od_table->max[setting]) अणु
		dev_warn(smu->adev->dev, "OD setting (%d, %d) is greater than the maximum allowed (%d)\n",
					  setting, value, od_table->max[setting]);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sienna_cichlid_od_edit_dpm_table(काष्ठा smu_context *smu,
					    क्रमागत PP_OD_DPM_TABLE_COMMAND type,
					    दीर्घ input[], uपूर्णांक32_t size)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	OverDriveTable_t *od_table =
		(OverDriveTable_t *)table_context->overdrive_table;
	काष्ठा smu_11_0_7_overdrive_table *od_settings =
		(काष्ठा smu_11_0_7_overdrive_table *)smu->od_settings;
	काष्ठा amdgpu_device *adev = smu->adev;
	क्रमागत SMU_11_0_7_ODSETTING_ID freq_setting;
	uपूर्णांक16_t *freq_ptr;
	पूर्णांक i, ret = 0;
	uपूर्णांक32_t smu_version;

	अगर (!smu->od_enabled) अणु
		dev_warn(smu->adev->dev, "OverDrive is not enabled!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!smu->od_settings) अणु
		dev_err(smu->adev->dev, "OD board limits are not set!\n");
		वापस -ENOENT;
	पूर्ण

	अगर (!(table_context->overdrive_table && table_context->boot_overdrive_table)) अणु
		dev_err(smu->adev->dev, "Overdrive table was not initialized!\n");
		वापस -EINVAL;
	पूर्ण

	चयन (type) अणु
	हाल PP_OD_EDIT_SCLK_VDDC_TABLE:
		अगर (!sienna_cichlid_is_od_feature_supported(od_settings,
							    SMU_11_0_7_ODCAP_GFXCLK_LIMITS)) अणु
			dev_warn(smu->adev->dev, "GFXCLK_LIMITS not supported!\n");
			वापस -ENOTSUPP;
		पूर्ण

		क्रम (i = 0; i < size; i += 2) अणु
			अगर (i + 2 > size) अणु
				dev_info(smu->adev->dev, "invalid number of input parameters %d\n", size);
				वापस -EINVAL;
			पूर्ण

			चयन (input[i]) अणु
			हाल 0:
				अगर (input[i + 1] > od_table->GfxclkFmax) अणु
					dev_info(smu->adev->dev, "GfxclkFmin (%ld) must be <= GfxclkFmax (%u)!\n",
						input[i + 1], od_table->GfxclkFmax);
					वापस -EINVAL;
				पूर्ण

				freq_setting = SMU_11_0_7_ODSETTING_GFXCLKFMIN;
				freq_ptr = &od_table->GfxclkFmin;
				अवरोध;

			हाल 1:
				अगर (input[i + 1] < od_table->GfxclkFmin) अणु
					dev_info(smu->adev->dev, "GfxclkFmax (%ld) must be >= GfxclkFmin (%u)!\n",
						input[i + 1], od_table->GfxclkFmin);
					वापस -EINVAL;
				पूर्ण

				freq_setting = SMU_11_0_7_ODSETTING_GFXCLKFMAX;
				freq_ptr = &od_table->GfxclkFmax;
				अवरोध;

			शेष:
				dev_info(smu->adev->dev, "Invalid SCLK_VDDC_TABLE index: %ld\n", input[i]);
				dev_info(smu->adev->dev, "Supported indices: [0:min,1:max]\n");
				वापस -EINVAL;
			पूर्ण

			ret = sienna_cichlid_od_setting_check_range(smu, od_settings,
								    freq_setting, input[i + 1]);
			अगर (ret)
				वापस ret;

			*freq_ptr = (uपूर्णांक16_t)input[i + 1];
		पूर्ण
		अवरोध;

	हाल PP_OD_EDIT_MCLK_VDDC_TABLE:
		अगर (!sienna_cichlid_is_od_feature_supported(od_settings, SMU_11_0_7_ODCAP_UCLK_LIMITS)) अणु
			dev_warn(smu->adev->dev, "UCLK_LIMITS not supported!\n");
			वापस -ENOTSUPP;
		पूर्ण

		क्रम (i = 0; i < size; i += 2) अणु
			अगर (i + 2 > size) अणु
				dev_info(smu->adev->dev, "invalid number of input parameters %d\n", size);
				वापस -EINVAL;
			पूर्ण

			चयन (input[i]) अणु
			हाल 0:
				अगर (input[i + 1] > od_table->UclkFmax) अणु
					dev_info(smu->adev->dev, "UclkFmin (%ld) must be <= UclkFmax (%u)!\n",
						input[i + 1], od_table->UclkFmax);
					वापस -EINVAL;
				पूर्ण

				freq_setting = SMU_11_0_7_ODSETTING_UCLKFMIN;
				freq_ptr = &od_table->UclkFmin;
				अवरोध;

			हाल 1:
				अगर (input[i + 1] < od_table->UclkFmin) अणु
					dev_info(smu->adev->dev, "UclkFmax (%ld) must be >= UclkFmin (%u)!\n",
						input[i + 1], od_table->UclkFmin);
					वापस -EINVAL;
				पूर्ण

				freq_setting = SMU_11_0_7_ODSETTING_UCLKFMAX;
				freq_ptr = &od_table->UclkFmax;
				अवरोध;

			शेष:
				dev_info(smu->adev->dev, "Invalid MCLK_VDDC_TABLE index: %ld\n", input[i]);
				dev_info(smu->adev->dev, "Supported indices: [0:min,1:max]\n");
				वापस -EINVAL;
			पूर्ण

			ret = sienna_cichlid_od_setting_check_range(smu, od_settings,
								    freq_setting, input[i + 1]);
			अगर (ret)
				वापस ret;

			*freq_ptr = (uपूर्णांक16_t)input[i + 1];
		पूर्ण
		अवरोध;

	हाल PP_OD_RESTORE_DEFAULT_TABLE:
		स_नकल(table_context->overdrive_table,
				table_context->boot_overdrive_table,
				माप(OverDriveTable_t));
		fallthrough;

	हाल PP_OD_COMMIT_DPM_TABLE:
		sienna_cichlid_dump_od_table(smu, od_table);

		ret = smu_cmn_update_table(smu, SMU_TABLE_OVERDRIVE,
					   0, (व्योम *)od_table, true);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Failed to import overdrive table!\n");
			वापस ret;
		पूर्ण
		अवरोध;

	हाल PP_OD_EDIT_VDDGFX_OFFSET:
		अगर (size != 1) अणु
			dev_info(smu->adev->dev, "invalid number of parameters: %d\n", size);
			वापस -EINVAL;
		पूर्ण

		/*
		 * OD GFX Voltage Offset functionality is supported only by 58.41.0
		 * and onwards SMU firmwares.
		 */
		smu_cmn_get_smc_version(smu, शून्य, &smu_version);
		अगर ((adev->asic_type == CHIP_SIENNA_CICHLID) &&
		     (smu_version < 0x003a2900)) अणु
			dev_err(smu->adev->dev, "OD GFX Voltage offset functionality is supported "
						"only by 58.41.0 and onwards SMU firmwares!\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		od_table->VddGfxOffset = (पूर्णांक16_t)input[0];

		sienna_cichlid_dump_od_table(smu, od_table);
		अवरोध;

	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sienna_cichlid_run_btc(काष्ठा smu_context *smu)
अणु
	वापस smu_cmn_send_smc_msg(smu, SMU_MSG_RunDcBtc, शून्य);
पूर्ण

अटल bool sienna_cichlid_is_baco_supported(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t val;

	अगर (amdgpu_sriov_vf(adev) || (!smu_v11_0_baco_is_support(smu)))
		वापस false;

	val = RREG32_SOC15(NBIO, 0, mmRCC_BIF_STRAP0);
	वापस (val & RCC_BIF_STRAP0__STRAP_PX_CAPABLE_MASK) ? true : false;
पूर्ण

अटल bool sienna_cichlid_is_mode1_reset_supported(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t val;
	u32 smu_version;

	/**
	 * SRIOV env will not support SMU mode1 reset
	 * PM FW support mode1 reset from 58.26
	 */
	smu_cmn_get_smc_version(smu, शून्य, &smu_version);
	अगर (amdgpu_sriov_vf(adev) || (smu_version < 0x003a1a00))
		वापस false;

	/**
	 * mode1 reset relies on PSP, so we should check अगर
	 * PSP is alive.
	 */
	val = RREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_81);
	वापस val != 0x0;
पूर्ण

अटल व्योम sienna_cichlid_dump_pptable(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	PPTable_t *pptable = table_context->driver_pptable;
	पूर्णांक i;

	dev_info(smu->adev->dev, "Dumped PPTable:\n");

	dev_info(smu->adev->dev, "Version = 0x%08x\n", pptable->Version);
	dev_info(smu->adev->dev, "FeaturesToRun[0] = 0x%08x\n", pptable->FeaturesToRun[0]);
	dev_info(smu->adev->dev, "FeaturesToRun[1] = 0x%08x\n", pptable->FeaturesToRun[1]);

	क्रम (i = 0; i < PPT_THROTTLER_COUNT; i++) अणु
		dev_info(smu->adev->dev, "SocketPowerLimitAc[%d] = 0x%x\n", i, pptable->SocketPowerLimitAc[i]);
		dev_info(smu->adev->dev, "SocketPowerLimitAcTau[%d] = 0x%x\n", i, pptable->SocketPowerLimitAcTau[i]);
		dev_info(smu->adev->dev, "SocketPowerLimitDc[%d] = 0x%x\n", i, pptable->SocketPowerLimitDc[i]);
		dev_info(smu->adev->dev, "SocketPowerLimitDcTau[%d] = 0x%x\n", i, pptable->SocketPowerLimitDcTau[i]);
	पूर्ण

	क्रम (i = 0; i < TDC_THROTTLER_COUNT; i++) अणु
		dev_info(smu->adev->dev, "TdcLimit[%d] = 0x%x\n", i, pptable->TdcLimit[i]);
		dev_info(smu->adev->dev, "TdcLimitTau[%d] = 0x%x\n", i, pptable->TdcLimitTau[i]);
	पूर्ण

	क्रम (i = 0; i < TEMP_COUNT; i++) अणु
		dev_info(smu->adev->dev, "TemperatureLimit[%d] = 0x%x\n", i, pptable->TemperatureLimit[i]);
	पूर्ण

	dev_info(smu->adev->dev, "FitLimit = 0x%x\n", pptable->FitLimit);
	dev_info(smu->adev->dev, "TotalPowerConfig = 0x%x\n", pptable->TotalPowerConfig);
	dev_info(smu->adev->dev, "TotalPowerPadding[0] = 0x%x\n", pptable->TotalPowerPadding[0]);
	dev_info(smu->adev->dev, "TotalPowerPadding[1] = 0x%x\n", pptable->TotalPowerPadding[1]);
	dev_info(smu->adev->dev, "TotalPowerPadding[2] = 0x%x\n", pptable->TotalPowerPadding[2]);

	dev_info(smu->adev->dev, "ApccPlusResidencyLimit = 0x%x\n", pptable->ApccPlusResidencyLimit);
	क्रम (i = 0; i < NUM_SMNCLK_DPM_LEVELS; i++) अणु
		dev_info(smu->adev->dev, "SmnclkDpmFreq[%d] = 0x%x\n", i, pptable->SmnclkDpmFreq[i]);
		dev_info(smu->adev->dev, "SmnclkDpmVoltage[%d] = 0x%x\n", i, pptable->SmnclkDpmVoltage[i]);
	पूर्ण
	dev_info(smu->adev->dev, "ThrottlerControlMask = 0x%x\n", pptable->ThrottlerControlMask);

	dev_info(smu->adev->dev, "FwDStateMask = 0x%x\n", pptable->FwDStateMask);

	dev_info(smu->adev->dev, "UlvVoltageOffsetSoc = 0x%x\n", pptable->UlvVoltageOffsetSoc);
	dev_info(smu->adev->dev, "UlvVoltageOffsetGfx = 0x%x\n", pptable->UlvVoltageOffsetGfx);
	dev_info(smu->adev->dev, "MinVoltageUlvGfx = 0x%x\n", pptable->MinVoltageUlvGfx);
	dev_info(smu->adev->dev, "MinVoltageUlvSoc = 0x%x\n", pptable->MinVoltageUlvSoc);

	dev_info(smu->adev->dev, "SocLIVmin = 0x%x\n", pptable->SocLIVmin);
	dev_info(smu->adev->dev, "PaddingLIVmin = 0x%x\n", pptable->PaddingLIVmin);

	dev_info(smu->adev->dev, "GceaLinkMgrIdleThreshold = 0x%x\n", pptable->GceaLinkMgrIdleThreshold);
	dev_info(smu->adev->dev, "paddingRlcUlvParams[0] = 0x%x\n", pptable->paddingRlcUlvParams[0]);
	dev_info(smu->adev->dev, "paddingRlcUlvParams[1] = 0x%x\n", pptable->paddingRlcUlvParams[1]);
	dev_info(smu->adev->dev, "paddingRlcUlvParams[2] = 0x%x\n", pptable->paddingRlcUlvParams[2]);

	dev_info(smu->adev->dev, "MinVoltageGfx = 0x%x\n", pptable->MinVoltageGfx);
	dev_info(smu->adev->dev, "MinVoltageSoc = 0x%x\n", pptable->MinVoltageSoc);
	dev_info(smu->adev->dev, "MaxVoltageGfx = 0x%x\n", pptable->MaxVoltageGfx);
	dev_info(smu->adev->dev, "MaxVoltageSoc = 0x%x\n", pptable->MaxVoltageSoc);

	dev_info(smu->adev->dev, "LoadLineResistanceGfx = 0x%x\n", pptable->LoadLineResistanceGfx);
	dev_info(smu->adev->dev, "LoadLineResistanceSoc = 0x%x\n", pptable->LoadLineResistanceSoc);

	dev_info(smu->adev->dev, "VDDGFX_TVmin = 0x%x\n", pptable->VDDGFX_TVmin);
	dev_info(smu->adev->dev, "VDDSOC_TVmin = 0x%x\n", pptable->VDDSOC_TVmin);
	dev_info(smu->adev->dev, "VDDGFX_Vmin_HiTemp = 0x%x\n", pptable->VDDGFX_Vmin_HiTemp);
	dev_info(smu->adev->dev, "VDDGFX_Vmin_LoTemp = 0x%x\n", pptable->VDDGFX_Vmin_LoTemp);
	dev_info(smu->adev->dev, "VDDSOC_Vmin_HiTemp = 0x%x\n", pptable->VDDSOC_Vmin_HiTemp);
	dev_info(smu->adev->dev, "VDDSOC_Vmin_LoTemp = 0x%x\n", pptable->VDDSOC_Vmin_LoTemp);
	dev_info(smu->adev->dev, "VDDGFX_TVminHystersis = 0x%x\n", pptable->VDDGFX_TVminHystersis);
	dev_info(smu->adev->dev, "VDDSOC_TVminHystersis = 0x%x\n", pptable->VDDSOC_TVminHystersis);

	dev_info(smu->adev->dev, "[PPCLK_GFXCLK]\n"
			"  .VoltageMode          = 0x%02x\n"
			"  .SnapToDiscrete       = 0x%02x\n"
			"  .NumDiscreteLevels    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConversionToAvfsClk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCurve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n"
			"  .SsFmin               = 0x%04x\n"
			"  .Padding_16           = 0x%04x\n",
			pptable->DpmDescriptor[PPCLK_GFXCLK].VoltageMode,
			pptable->DpmDescriptor[PPCLK_GFXCLK].SnapToDiscrete,
			pptable->DpmDescriptor[PPCLK_GFXCLK].NumDiscreteLevels,
			pptable->DpmDescriptor[PPCLK_GFXCLK].Padding,
			pptable->DpmDescriptor[PPCLK_GFXCLK].ConversionToAvfsClk.m,
			pptable->DpmDescriptor[PPCLK_GFXCLK].ConversionToAvfsClk.b,
			pptable->DpmDescriptor[PPCLK_GFXCLK].SsCurve.a,
			pptable->DpmDescriptor[PPCLK_GFXCLK].SsCurve.b,
			pptable->DpmDescriptor[PPCLK_GFXCLK].SsCurve.c,
			pptable->DpmDescriptor[PPCLK_GFXCLK].SsFmin,
			pptable->DpmDescriptor[PPCLK_GFXCLK].Padding16);

	dev_info(smu->adev->dev, "[PPCLK_SOCCLK]\n"
			"  .VoltageMode          = 0x%02x\n"
			"  .SnapToDiscrete       = 0x%02x\n"
			"  .NumDiscreteLevels    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConversionToAvfsClk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCurve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n"
			"  .SsFmin               = 0x%04x\n"
			"  .Padding_16           = 0x%04x\n",
			pptable->DpmDescriptor[PPCLK_SOCCLK].VoltageMode,
			pptable->DpmDescriptor[PPCLK_SOCCLK].SnapToDiscrete,
			pptable->DpmDescriptor[PPCLK_SOCCLK].NumDiscreteLevels,
			pptable->DpmDescriptor[PPCLK_SOCCLK].Padding,
			pptable->DpmDescriptor[PPCLK_SOCCLK].ConversionToAvfsClk.m,
			pptable->DpmDescriptor[PPCLK_SOCCLK].ConversionToAvfsClk.b,
			pptable->DpmDescriptor[PPCLK_SOCCLK].SsCurve.a,
			pptable->DpmDescriptor[PPCLK_SOCCLK].SsCurve.b,
			pptable->DpmDescriptor[PPCLK_SOCCLK].SsCurve.c,
			pptable->DpmDescriptor[PPCLK_SOCCLK].SsFmin,
			pptable->DpmDescriptor[PPCLK_SOCCLK].Padding16);

	dev_info(smu->adev->dev, "[PPCLK_UCLK]\n"
			"  .VoltageMode          = 0x%02x\n"
			"  .SnapToDiscrete       = 0x%02x\n"
			"  .NumDiscreteLevels    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConversionToAvfsClk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCurve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n"
			"  .SsFmin               = 0x%04x\n"
			"  .Padding_16           = 0x%04x\n",
			pptable->DpmDescriptor[PPCLK_UCLK].VoltageMode,
			pptable->DpmDescriptor[PPCLK_UCLK].SnapToDiscrete,
			pptable->DpmDescriptor[PPCLK_UCLK].NumDiscreteLevels,
			pptable->DpmDescriptor[PPCLK_UCLK].Padding,
			pptable->DpmDescriptor[PPCLK_UCLK].ConversionToAvfsClk.m,
			pptable->DpmDescriptor[PPCLK_UCLK].ConversionToAvfsClk.b,
			pptable->DpmDescriptor[PPCLK_UCLK].SsCurve.a,
			pptable->DpmDescriptor[PPCLK_UCLK].SsCurve.b,
			pptable->DpmDescriptor[PPCLK_UCLK].SsCurve.c,
			pptable->DpmDescriptor[PPCLK_UCLK].SsFmin,
			pptable->DpmDescriptor[PPCLK_UCLK].Padding16);

	dev_info(smu->adev->dev, "[PPCLK_FCLK]\n"
			"  .VoltageMode          = 0x%02x\n"
			"  .SnapToDiscrete       = 0x%02x\n"
			"  .NumDiscreteLevels    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConversionToAvfsClk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCurve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n"
			"  .SsFmin               = 0x%04x\n"
			"  .Padding_16           = 0x%04x\n",
			pptable->DpmDescriptor[PPCLK_FCLK].VoltageMode,
			pptable->DpmDescriptor[PPCLK_FCLK].SnapToDiscrete,
			pptable->DpmDescriptor[PPCLK_FCLK].NumDiscreteLevels,
			pptable->DpmDescriptor[PPCLK_FCLK].Padding,
			pptable->DpmDescriptor[PPCLK_FCLK].ConversionToAvfsClk.m,
			pptable->DpmDescriptor[PPCLK_FCLK].ConversionToAvfsClk.b,
			pptable->DpmDescriptor[PPCLK_FCLK].SsCurve.a,
			pptable->DpmDescriptor[PPCLK_FCLK].SsCurve.b,
			pptable->DpmDescriptor[PPCLK_FCLK].SsCurve.c,
			pptable->DpmDescriptor[PPCLK_FCLK].SsFmin,
			pptable->DpmDescriptor[PPCLK_FCLK].Padding16);

	dev_info(smu->adev->dev, "[PPCLK_DCLK_0]\n"
			"  .VoltageMode          = 0x%02x\n"
			"  .SnapToDiscrete       = 0x%02x\n"
			"  .NumDiscreteLevels    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConversionToAvfsClk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCurve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n"
			"  .SsFmin               = 0x%04x\n"
			"  .Padding_16           = 0x%04x\n",
			pptable->DpmDescriptor[PPCLK_DCLK_0].VoltageMode,
			pptable->DpmDescriptor[PPCLK_DCLK_0].SnapToDiscrete,
			pptable->DpmDescriptor[PPCLK_DCLK_0].NumDiscreteLevels,
			pptable->DpmDescriptor[PPCLK_DCLK_0].Padding,
			pptable->DpmDescriptor[PPCLK_DCLK_0].ConversionToAvfsClk.m,
			pptable->DpmDescriptor[PPCLK_DCLK_0].ConversionToAvfsClk.b,
			pptable->DpmDescriptor[PPCLK_DCLK_0].SsCurve.a,
			pptable->DpmDescriptor[PPCLK_DCLK_0].SsCurve.b,
			pptable->DpmDescriptor[PPCLK_DCLK_0].SsCurve.c,
			pptable->DpmDescriptor[PPCLK_DCLK_0].SsFmin,
			pptable->DpmDescriptor[PPCLK_DCLK_0].Padding16);

	dev_info(smu->adev->dev, "[PPCLK_VCLK_0]\n"
			"  .VoltageMode          = 0x%02x\n"
			"  .SnapToDiscrete       = 0x%02x\n"
			"  .NumDiscreteLevels    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConversionToAvfsClk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCurve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n"
			"  .SsFmin               = 0x%04x\n"
			"  .Padding_16           = 0x%04x\n",
			pptable->DpmDescriptor[PPCLK_VCLK_0].VoltageMode,
			pptable->DpmDescriptor[PPCLK_VCLK_0].SnapToDiscrete,
			pptable->DpmDescriptor[PPCLK_VCLK_0].NumDiscreteLevels,
			pptable->DpmDescriptor[PPCLK_VCLK_0].Padding,
			pptable->DpmDescriptor[PPCLK_VCLK_0].ConversionToAvfsClk.m,
			pptable->DpmDescriptor[PPCLK_VCLK_0].ConversionToAvfsClk.b,
			pptable->DpmDescriptor[PPCLK_VCLK_0].SsCurve.a,
			pptable->DpmDescriptor[PPCLK_VCLK_0].SsCurve.b,
			pptable->DpmDescriptor[PPCLK_VCLK_0].SsCurve.c,
			pptable->DpmDescriptor[PPCLK_VCLK_0].SsFmin,
			pptable->DpmDescriptor[PPCLK_VCLK_0].Padding16);

	dev_info(smu->adev->dev, "[PPCLK_DCLK_1]\n"
			"  .VoltageMode          = 0x%02x\n"
			"  .SnapToDiscrete       = 0x%02x\n"
			"  .NumDiscreteLevels    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConversionToAvfsClk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCurve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n"
			"  .SsFmin               = 0x%04x\n"
			"  .Padding_16           = 0x%04x\n",
			pptable->DpmDescriptor[PPCLK_DCLK_1].VoltageMode,
			pptable->DpmDescriptor[PPCLK_DCLK_1].SnapToDiscrete,
			pptable->DpmDescriptor[PPCLK_DCLK_1].NumDiscreteLevels,
			pptable->DpmDescriptor[PPCLK_DCLK_1].Padding,
			pptable->DpmDescriptor[PPCLK_DCLK_1].ConversionToAvfsClk.m,
			pptable->DpmDescriptor[PPCLK_DCLK_1].ConversionToAvfsClk.b,
			pptable->DpmDescriptor[PPCLK_DCLK_1].SsCurve.a,
			pptable->DpmDescriptor[PPCLK_DCLK_1].SsCurve.b,
			pptable->DpmDescriptor[PPCLK_DCLK_1].SsCurve.c,
			pptable->DpmDescriptor[PPCLK_DCLK_1].SsFmin,
			pptable->DpmDescriptor[PPCLK_DCLK_1].Padding16);

	dev_info(smu->adev->dev, "[PPCLK_VCLK_1]\n"
			"  .VoltageMode          = 0x%02x\n"
			"  .SnapToDiscrete       = 0x%02x\n"
			"  .NumDiscreteLevels    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConversionToAvfsClk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCurve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n"
			"  .SsFmin               = 0x%04x\n"
			"  .Padding_16           = 0x%04x\n",
			pptable->DpmDescriptor[PPCLK_VCLK_1].VoltageMode,
			pptable->DpmDescriptor[PPCLK_VCLK_1].SnapToDiscrete,
			pptable->DpmDescriptor[PPCLK_VCLK_1].NumDiscreteLevels,
			pptable->DpmDescriptor[PPCLK_VCLK_1].Padding,
			pptable->DpmDescriptor[PPCLK_VCLK_1].ConversionToAvfsClk.m,
			pptable->DpmDescriptor[PPCLK_VCLK_1].ConversionToAvfsClk.b,
			pptable->DpmDescriptor[PPCLK_VCLK_1].SsCurve.a,
			pptable->DpmDescriptor[PPCLK_VCLK_1].SsCurve.b,
			pptable->DpmDescriptor[PPCLK_VCLK_1].SsCurve.c,
			pptable->DpmDescriptor[PPCLK_VCLK_1].SsFmin,
			pptable->DpmDescriptor[PPCLK_VCLK_1].Padding16);

	dev_info(smu->adev->dev, "FreqTableGfx\n");
	क्रम (i = 0; i < NUM_GFXCLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = 0x%x\n", i, pptable->FreqTableGfx[i]);

	dev_info(smu->adev->dev, "FreqTableVclk\n");
	क्रम (i = 0; i < NUM_VCLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = 0x%x\n", i, pptable->FreqTableVclk[i]);

	dev_info(smu->adev->dev, "FreqTableDclk\n");
	क्रम (i = 0; i < NUM_DCLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = 0x%x\n", i, pptable->FreqTableDclk[i]);

	dev_info(smu->adev->dev, "FreqTableSocclk\n");
	क्रम (i = 0; i < NUM_SOCCLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = 0x%x\n", i, pptable->FreqTableSocclk[i]);

	dev_info(smu->adev->dev, "FreqTableUclk\n");
	क्रम (i = 0; i < NUM_UCLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = 0x%x\n", i, pptable->FreqTableUclk[i]);

	dev_info(smu->adev->dev, "FreqTableFclk\n");
	क्रम (i = 0; i < NUM_FCLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = 0x%x\n", i, pptable->FreqTableFclk[i]);

	dev_info(smu->adev->dev, "DcModeMaxFreq\n");
	dev_info(smu->adev->dev, "  .PPCLK_GFXCLK = 0x%x\n", pptable->DcModeMaxFreq[PPCLK_GFXCLK]);
	dev_info(smu->adev->dev, "  .PPCLK_SOCCLK = 0x%x\n", pptable->DcModeMaxFreq[PPCLK_SOCCLK]);
	dev_info(smu->adev->dev, "  .PPCLK_UCLK   = 0x%x\n", pptable->DcModeMaxFreq[PPCLK_UCLK]);
	dev_info(smu->adev->dev, "  .PPCLK_FCLK   = 0x%x\n", pptable->DcModeMaxFreq[PPCLK_FCLK]);
	dev_info(smu->adev->dev, "  .PPCLK_DCLK_0 = 0x%x\n", pptable->DcModeMaxFreq[PPCLK_DCLK_0]);
	dev_info(smu->adev->dev, "  .PPCLK_VCLK_0 = 0x%x\n", pptable->DcModeMaxFreq[PPCLK_VCLK_0]);
	dev_info(smu->adev->dev, "  .PPCLK_DCLK_1 = 0x%x\n", pptable->DcModeMaxFreq[PPCLK_DCLK_1]);
	dev_info(smu->adev->dev, "  .PPCLK_VCLK_1 = 0x%x\n", pptable->DcModeMaxFreq[PPCLK_VCLK_1]);

	dev_info(smu->adev->dev, "FreqTableUclkDiv\n");
	क्रम (i = 0; i < NUM_UCLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = 0x%x\n", i, pptable->FreqTableUclkDiv[i]);

	dev_info(smu->adev->dev, "FclkBoostFreq = 0x%x\n", pptable->FclkBoostFreq);
	dev_info(smu->adev->dev, "FclkParamPadding = 0x%x\n", pptable->FclkParamPadding);

	dev_info(smu->adev->dev, "Mp0clkFreq\n");
	क्रम (i = 0; i < NUM_MP0CLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = 0x%x\n", i, pptable->Mp0clkFreq[i]);

	dev_info(smu->adev->dev, "Mp0DpmVoltage\n");
	क्रम (i = 0; i < NUM_MP0CLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = 0x%x\n", i, pptable->Mp0DpmVoltage[i]);

	dev_info(smu->adev->dev, "MemVddciVoltage\n");
	क्रम (i = 0; i < NUM_UCLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = 0x%x\n", i, pptable->MemVddciVoltage[i]);

	dev_info(smu->adev->dev, "MemMvddVoltage\n");
	क्रम (i = 0; i < NUM_UCLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = 0x%x\n", i, pptable->MemMvddVoltage[i]);

	dev_info(smu->adev->dev, "GfxclkFgfxoffEntry = 0x%x\n", pptable->GfxclkFgfxoffEntry);
	dev_info(smu->adev->dev, "GfxclkFinit = 0x%x\n", pptable->GfxclkFinit);
	dev_info(smu->adev->dev, "GfxclkFidle = 0x%x\n", pptable->GfxclkFidle);
	dev_info(smu->adev->dev, "GfxclkSource = 0x%x\n", pptable->GfxclkSource);
	dev_info(smu->adev->dev, "GfxclkPadding = 0x%x\n", pptable->GfxclkPadding);

	dev_info(smu->adev->dev, "GfxGpoSubFeatureMask = 0x%x\n", pptable->GfxGpoSubFeatureMask);

	dev_info(smu->adev->dev, "GfxGpoEnabledWorkPolicyMask = 0x%x\n", pptable->GfxGpoEnabledWorkPolicyMask);
	dev_info(smu->adev->dev, "GfxGpoDisabledWorkPolicyMask = 0x%x\n", pptable->GfxGpoDisabledWorkPolicyMask);
	dev_info(smu->adev->dev, "GfxGpoPadding[0] = 0x%x\n", pptable->GfxGpoPadding[0]);
	dev_info(smu->adev->dev, "GfxGpoVotingAllow = 0x%x\n", pptable->GfxGpoVotingAllow);
	dev_info(smu->adev->dev, "GfxGpoPadding32[0] = 0x%x\n", pptable->GfxGpoPadding32[0]);
	dev_info(smu->adev->dev, "GfxGpoPadding32[1] = 0x%x\n", pptable->GfxGpoPadding32[1]);
	dev_info(smu->adev->dev, "GfxGpoPadding32[2] = 0x%x\n", pptable->GfxGpoPadding32[2]);
	dev_info(smu->adev->dev, "GfxGpoPadding32[3] = 0x%x\n", pptable->GfxGpoPadding32[3]);
	dev_info(smu->adev->dev, "GfxDcsFopt = 0x%x\n", pptable->GfxDcsFopt);
	dev_info(smu->adev->dev, "GfxDcsFclkFopt = 0x%x\n", pptable->GfxDcsFclkFopt);
	dev_info(smu->adev->dev, "GfxDcsUclkFopt = 0x%x\n", pptable->GfxDcsUclkFopt);

	dev_info(smu->adev->dev, "DcsGfxOffVoltage = 0x%x\n", pptable->DcsGfxOffVoltage);
	dev_info(smu->adev->dev, "DcsMinGfxOffTime = 0x%x\n", pptable->DcsMinGfxOffTime);
	dev_info(smu->adev->dev, "DcsMaxGfxOffTime = 0x%x\n", pptable->DcsMaxGfxOffTime);
	dev_info(smu->adev->dev, "DcsMinCreditAccum = 0x%x\n", pptable->DcsMinCreditAccum);
	dev_info(smu->adev->dev, "DcsExitHysteresis = 0x%x\n", pptable->DcsExitHysteresis);
	dev_info(smu->adev->dev, "DcsTimeout = 0x%x\n", pptable->DcsTimeout);

	dev_info(smu->adev->dev, "DcsParamPadding[0] = 0x%x\n", pptable->DcsParamPadding[0]);
	dev_info(smu->adev->dev, "DcsParamPadding[1] = 0x%x\n", pptable->DcsParamPadding[1]);
	dev_info(smu->adev->dev, "DcsParamPadding[2] = 0x%x\n", pptable->DcsParamPadding[2]);
	dev_info(smu->adev->dev, "DcsParamPadding[3] = 0x%x\n", pptable->DcsParamPadding[3]);
	dev_info(smu->adev->dev, "DcsParamPadding[4] = 0x%x\n", pptable->DcsParamPadding[4]);

	dev_info(smu->adev->dev, "FlopsPerByteTable\n");
	क्रम (i = 0; i < RLC_PACE_TABLE_NUM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = 0x%x\n", i, pptable->FlopsPerByteTable[i]);

	dev_info(smu->adev->dev, "LowestUclkReservedForUlv = 0x%x\n", pptable->LowestUclkReservedForUlv);
	dev_info(smu->adev->dev, "vddingMem[0] = 0x%x\n", pptable->PaddingMem[0]);
	dev_info(smu->adev->dev, "vddingMem[1] = 0x%x\n", pptable->PaddingMem[1]);
	dev_info(smu->adev->dev, "vddingMem[2] = 0x%x\n", pptable->PaddingMem[2]);

	dev_info(smu->adev->dev, "UclkDpmPstates\n");
	क्रम (i = 0; i < NUM_UCLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = 0x%x\n", i, pptable->UclkDpmPstates[i]);

	dev_info(smu->adev->dev, "UclkDpmSrcFreqRange\n");
	dev_info(smu->adev->dev, "  .Fmin = 0x%x\n",
		pptable->UclkDpmSrcFreqRange.Fmin);
	dev_info(smu->adev->dev, "  .Fmax = 0x%x\n",
		pptable->UclkDpmSrcFreqRange.Fmax);
	dev_info(smu->adev->dev, "UclkDpmTargFreqRange\n");
	dev_info(smu->adev->dev, "  .Fmin = 0x%x\n",
		pptable->UclkDpmTargFreqRange.Fmin);
	dev_info(smu->adev->dev, "  .Fmax = 0x%x\n",
		pptable->UclkDpmTargFreqRange.Fmax);
	dev_info(smu->adev->dev, "UclkDpmMidstepFreq = 0x%x\n", pptable->UclkDpmMidstepFreq);
	dev_info(smu->adev->dev, "UclkMidstepPadding = 0x%x\n", pptable->UclkMidstepPadding);

	dev_info(smu->adev->dev, "PcieGenSpeed\n");
	क्रम (i = 0; i < NUM_LINK_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = 0x%x\n", i, pptable->PcieGenSpeed[i]);

	dev_info(smu->adev->dev, "PcieLaneCount\n");
	क्रम (i = 0; i < NUM_LINK_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = 0x%x\n", i, pptable->PcieLaneCount[i]);

	dev_info(smu->adev->dev, "LclkFreq\n");
	क्रम (i = 0; i < NUM_LINK_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = 0x%x\n", i, pptable->LclkFreq[i]);

	dev_info(smu->adev->dev, "FanStopTemp = 0x%x\n", pptable->FanStopTemp);
	dev_info(smu->adev->dev, "FanStartTemp = 0x%x\n", pptable->FanStartTemp);

	dev_info(smu->adev->dev, "FanGain\n");
	क्रम (i = 0; i < TEMP_COUNT; i++)
		dev_info(smu->adev->dev, "  .[%d] = 0x%x\n", i, pptable->FanGain[i]);

	dev_info(smu->adev->dev, "FanPwmMin = 0x%x\n", pptable->FanPwmMin);
	dev_info(smu->adev->dev, "FanAcousticLimitRpm = 0x%x\n", pptable->FanAcousticLimitRpm);
	dev_info(smu->adev->dev, "FanThrottlingRpm = 0x%x\n", pptable->FanThrottlingRpm);
	dev_info(smu->adev->dev, "FanMaximumRpm = 0x%x\n", pptable->FanMaximumRpm);
	dev_info(smu->adev->dev, "MGpuFanBoostLimitRpm = 0x%x\n", pptable->MGpuFanBoostLimitRpm);
	dev_info(smu->adev->dev, "FanTargetTemperature = 0x%x\n", pptable->FanTargetTemperature);
	dev_info(smu->adev->dev, "FanTargetGfxclk = 0x%x\n", pptable->FanTargetGfxclk);
	dev_info(smu->adev->dev, "FanPadding16 = 0x%x\n", pptable->FanPadding16);
	dev_info(smu->adev->dev, "FanTempInputSelect = 0x%x\n", pptable->FanTempInputSelect);
	dev_info(smu->adev->dev, "FanPadding = 0x%x\n", pptable->FanPadding);
	dev_info(smu->adev->dev, "FanZeroRpmEnable = 0x%x\n", pptable->FanZeroRpmEnable);
	dev_info(smu->adev->dev, "FanTachEdgePerRev = 0x%x\n", pptable->FanTachEdgePerRev);

	dev_info(smu->adev->dev, "FuzzyFan_ErrorSetDelta = 0x%x\n", pptable->FuzzyFan_ErrorSetDelta);
	dev_info(smu->adev->dev, "FuzzyFan_ErrorRateSetDelta = 0x%x\n", pptable->FuzzyFan_ErrorRateSetDelta);
	dev_info(smu->adev->dev, "FuzzyFan_PwmSetDelta = 0x%x\n", pptable->FuzzyFan_PwmSetDelta);
	dev_info(smu->adev->dev, "FuzzyFan_Reserved = 0x%x\n", pptable->FuzzyFan_Reserved);

	dev_info(smu->adev->dev, "OverrideAvfsGb[AVFS_VOLTAGE_GFX] = 0x%x\n", pptable->OverrideAvfsGb[AVFS_VOLTAGE_GFX]);
	dev_info(smu->adev->dev, "OverrideAvfsGb[AVFS_VOLTAGE_SOC] = 0x%x\n", pptable->OverrideAvfsGb[AVFS_VOLTAGE_SOC]);
	dev_info(smu->adev->dev, "dBtcGbGfxDfllModelSelect = 0x%x\n", pptable->dBtcGbGfxDfllModelSelect);
	dev_info(smu->adev->dev, "Padding8_Avfs = 0x%x\n", pptable->Padding8_Avfs);

	dev_info(smu->adev->dev, "qAvfsGb[AVFS_VOLTAGE_GFX]{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptable->qAvfsGb[AVFS_VOLTAGE_GFX].a,
			pptable->qAvfsGb[AVFS_VOLTAGE_GFX].b,
			pptable->qAvfsGb[AVFS_VOLTAGE_GFX].c);
	dev_info(smu->adev->dev, "qAvfsGb[AVFS_VOLTAGE_SOC]{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptable->qAvfsGb[AVFS_VOLTAGE_SOC].a,
			pptable->qAvfsGb[AVFS_VOLTAGE_SOC].b,
			pptable->qAvfsGb[AVFS_VOLTAGE_SOC].c);
	dev_info(smu->adev->dev, "dBtcGbGfxPll{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptable->dBtcGbGfxPll.a,
			pptable->dBtcGbGfxPll.b,
			pptable->dBtcGbGfxPll.c);
	dev_info(smu->adev->dev, "dBtcGbGfxAfll{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptable->dBtcGbGfxDfll.a,
			pptable->dBtcGbGfxDfll.b,
			pptable->dBtcGbGfxDfll.c);
	dev_info(smu->adev->dev, "dBtcGbSoc{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptable->dBtcGbSoc.a,
			pptable->dBtcGbSoc.b,
			pptable->dBtcGbSoc.c);
	dev_info(smu->adev->dev, "qAgingGb[AVFS_VOLTAGE_GFX]{m = 0x%x b = 0x%x}\n",
			pptable->qAgingGb[AVFS_VOLTAGE_GFX].m,
			pptable->qAgingGb[AVFS_VOLTAGE_GFX].b);
	dev_info(smu->adev->dev, "qAgingGb[AVFS_VOLTAGE_SOC]{m = 0x%x b = 0x%x}\n",
			pptable->qAgingGb[AVFS_VOLTAGE_SOC].m,
			pptable->qAgingGb[AVFS_VOLTAGE_SOC].b);

	dev_info(smu->adev->dev, "PiecewiseLinearDroopIntGfxDfll\n");
	क्रम (i = 0; i < NUM_PIECE_WISE_LINEAR_DROOP_MODEL_VF_POINTS; i++) अणु
		dev_info(smu->adev->dev, "		Fset[%d] = 0x%x\n",
			i, pptable->PiecewiseLinearDroopIntGfxDfll.Fset[i]);
		dev_info(smu->adev->dev, "		Vdroop[%d] = 0x%x\n",
			i, pptable->PiecewiseLinearDroopIntGfxDfll.Vdroop[i]);
	पूर्ण

	dev_info(smu->adev->dev, "qStaticVoltageOffset[AVFS_VOLTAGE_GFX]{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptable->qStaticVoltageOffset[AVFS_VOLTAGE_GFX].a,
			pptable->qStaticVoltageOffset[AVFS_VOLTAGE_GFX].b,
			pptable->qStaticVoltageOffset[AVFS_VOLTAGE_GFX].c);
	dev_info(smu->adev->dev, "qStaticVoltageOffset[AVFS_VOLTAGE_SOC]{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptable->qStaticVoltageOffset[AVFS_VOLTAGE_SOC].a,
			pptable->qStaticVoltageOffset[AVFS_VOLTAGE_SOC].b,
			pptable->qStaticVoltageOffset[AVFS_VOLTAGE_SOC].c);

	dev_info(smu->adev->dev, "DcTol[AVFS_VOLTAGE_GFX] = 0x%x\n", pptable->DcTol[AVFS_VOLTAGE_GFX]);
	dev_info(smu->adev->dev, "DcTol[AVFS_VOLTAGE_SOC] = 0x%x\n", pptable->DcTol[AVFS_VOLTAGE_SOC]);

	dev_info(smu->adev->dev, "DcBtcEnabled[AVFS_VOLTAGE_GFX] = 0x%x\n", pptable->DcBtcEnabled[AVFS_VOLTAGE_GFX]);
	dev_info(smu->adev->dev, "DcBtcEnabled[AVFS_VOLTAGE_SOC] = 0x%x\n", pptable->DcBtcEnabled[AVFS_VOLTAGE_SOC]);
	dev_info(smu->adev->dev, "Padding8_GfxBtc[0] = 0x%x\n", pptable->Padding8_GfxBtc[0]);
	dev_info(smu->adev->dev, "Padding8_GfxBtc[1] = 0x%x\n", pptable->Padding8_GfxBtc[1]);

	dev_info(smu->adev->dev, "DcBtcMin[AVFS_VOLTAGE_GFX] = 0x%x\n", pptable->DcBtcMin[AVFS_VOLTAGE_GFX]);
	dev_info(smu->adev->dev, "DcBtcMin[AVFS_VOLTAGE_SOC] = 0x%x\n", pptable->DcBtcMin[AVFS_VOLTAGE_SOC]);
	dev_info(smu->adev->dev, "DcBtcMax[AVFS_VOLTAGE_GFX] = 0x%x\n", pptable->DcBtcMax[AVFS_VOLTAGE_GFX]);
	dev_info(smu->adev->dev, "DcBtcMax[AVFS_VOLTAGE_SOC] = 0x%x\n", pptable->DcBtcMax[AVFS_VOLTAGE_SOC]);

	dev_info(smu->adev->dev, "DcBtcGb[AVFS_VOLTAGE_GFX] = 0x%x\n", pptable->DcBtcGb[AVFS_VOLTAGE_GFX]);
	dev_info(smu->adev->dev, "DcBtcGb[AVFS_VOLTAGE_SOC] = 0x%x\n", pptable->DcBtcGb[AVFS_VOLTAGE_SOC]);

	dev_info(smu->adev->dev, "XgmiDpmPstates\n");
	क्रम (i = 0; i < NUM_XGMI_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = 0x%x\n", i, pptable->XgmiDpmPstates[i]);
	dev_info(smu->adev->dev, "XgmiDpmSpare[0] = 0x%02x\n", pptable->XgmiDpmSpare[0]);
	dev_info(smu->adev->dev, "XgmiDpmSpare[1] = 0x%02x\n", pptable->XgmiDpmSpare[1]);

	dev_info(smu->adev->dev, "DebugOverrides = 0x%x\n", pptable->DebugOverrides);
	dev_info(smu->adev->dev, "ReservedEquation0{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptable->ReservedEquation0.a,
			pptable->ReservedEquation0.b,
			pptable->ReservedEquation0.c);
	dev_info(smu->adev->dev, "ReservedEquation1{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptable->ReservedEquation1.a,
			pptable->ReservedEquation1.b,
			pptable->ReservedEquation1.c);
	dev_info(smu->adev->dev, "ReservedEquation2{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptable->ReservedEquation2.a,
			pptable->ReservedEquation2.b,
			pptable->ReservedEquation2.c);
	dev_info(smu->adev->dev, "ReservedEquation3{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptable->ReservedEquation3.a,
			pptable->ReservedEquation3.b,
			pptable->ReservedEquation3.c);

	dev_info(smu->adev->dev, "SkuReserved[0] = 0x%x\n", pptable->SkuReserved[0]);
	dev_info(smu->adev->dev, "SkuReserved[1] = 0x%x\n", pptable->SkuReserved[1]);
	dev_info(smu->adev->dev, "SkuReserved[2] = 0x%x\n", pptable->SkuReserved[2]);
	dev_info(smu->adev->dev, "SkuReserved[3] = 0x%x\n", pptable->SkuReserved[3]);
	dev_info(smu->adev->dev, "SkuReserved[4] = 0x%x\n", pptable->SkuReserved[4]);
	dev_info(smu->adev->dev, "SkuReserved[5] = 0x%x\n", pptable->SkuReserved[5]);
	dev_info(smu->adev->dev, "SkuReserved[6] = 0x%x\n", pptable->SkuReserved[6]);
	dev_info(smu->adev->dev, "SkuReserved[7] = 0x%x\n", pptable->SkuReserved[7]);

	dev_info(smu->adev->dev, "GamingClk[0] = 0x%x\n", pptable->GamingClk[0]);
	dev_info(smu->adev->dev, "GamingClk[1] = 0x%x\n", pptable->GamingClk[1]);
	dev_info(smu->adev->dev, "GamingClk[2] = 0x%x\n", pptable->GamingClk[2]);
	dev_info(smu->adev->dev, "GamingClk[3] = 0x%x\n", pptable->GamingClk[3]);
	dev_info(smu->adev->dev, "GamingClk[4] = 0x%x\n", pptable->GamingClk[4]);
	dev_info(smu->adev->dev, "GamingClk[5] = 0x%x\n", pptable->GamingClk[5]);

	क्रम (i = 0; i < NUM_I2C_CONTROLLERS; i++) अणु
		dev_info(smu->adev->dev, "I2cControllers[%d]:\n", i);
		dev_info(smu->adev->dev, "                   .Enabled = 0x%x\n",
				pptable->I2cControllers[i].Enabled);
		dev_info(smu->adev->dev, "                   .Speed = 0x%x\n",
				pptable->I2cControllers[i].Speed);
		dev_info(smu->adev->dev, "                   .SlaveAddress = 0x%x\n",
				pptable->I2cControllers[i].SlaveAddress);
		dev_info(smu->adev->dev, "                   .ControllerPort = 0x%x\n",
				pptable->I2cControllers[i].ControllerPort);
		dev_info(smu->adev->dev, "                   .ControllerName = 0x%x\n",
				pptable->I2cControllers[i].ControllerName);
		dev_info(smu->adev->dev, "                   .ThermalThrottler = 0x%x\n",
				pptable->I2cControllers[i].ThermalThrotter);
		dev_info(smu->adev->dev, "                   .I2cProtocol = 0x%x\n",
				pptable->I2cControllers[i].I2cProtocol);
		dev_info(smu->adev->dev, "                   .PaddingConfig = 0x%x\n",
				pptable->I2cControllers[i].PaddingConfig);
	पूर्ण

	dev_info(smu->adev->dev, "GpioScl = 0x%x\n", pptable->GpioScl);
	dev_info(smu->adev->dev, "GpioSda = 0x%x\n", pptable->GpioSda);
	dev_info(smu->adev->dev, "FchUsbPdSlaveAddr = 0x%x\n", pptable->FchUsbPdSlaveAddr);
	dev_info(smu->adev->dev, "I2cSpare[0] = 0x%x\n", pptable->I2cSpare[0]);

	dev_info(smu->adev->dev, "Board Parameters:\n");
	dev_info(smu->adev->dev, "VddGfxVrMapping = 0x%x\n", pptable->VddGfxVrMapping);
	dev_info(smu->adev->dev, "VddSocVrMapping = 0x%x\n", pptable->VddSocVrMapping);
	dev_info(smu->adev->dev, "VddMem0VrMapping = 0x%x\n", pptable->VddMem0VrMapping);
	dev_info(smu->adev->dev, "VddMem1VrMapping = 0x%x\n", pptable->VddMem1VrMapping);
	dev_info(smu->adev->dev, "GfxUlvPhaseSheddingMask = 0x%x\n", pptable->GfxUlvPhaseSheddingMask);
	dev_info(smu->adev->dev, "SocUlvPhaseSheddingMask = 0x%x\n", pptable->SocUlvPhaseSheddingMask);
	dev_info(smu->adev->dev, "VddciUlvPhaseSheddingMask = 0x%x\n", pptable->VddciUlvPhaseSheddingMask);
	dev_info(smu->adev->dev, "MvddUlvPhaseSheddingMask = 0x%x\n", pptable->MvddUlvPhaseSheddingMask);

	dev_info(smu->adev->dev, "GfxMaxCurrent = 0x%x\n", pptable->GfxMaxCurrent);
	dev_info(smu->adev->dev, "GfxOffset = 0x%x\n", pptable->GfxOffset);
	dev_info(smu->adev->dev, "Padding_TelemetryGfx = 0x%x\n", pptable->Padding_TelemetryGfx);

	dev_info(smu->adev->dev, "SocMaxCurrent = 0x%x\n", pptable->SocMaxCurrent);
	dev_info(smu->adev->dev, "SocOffset = 0x%x\n", pptable->SocOffset);
	dev_info(smu->adev->dev, "Padding_TelemetrySoc = 0x%x\n", pptable->Padding_TelemetrySoc);

	dev_info(smu->adev->dev, "Mem0MaxCurrent = 0x%x\n", pptable->Mem0MaxCurrent);
	dev_info(smu->adev->dev, "Mem0Offset = 0x%x\n", pptable->Mem0Offset);
	dev_info(smu->adev->dev, "Padding_TelemetryMem0 = 0x%x\n", pptable->Padding_TelemetryMem0);

	dev_info(smu->adev->dev, "Mem1MaxCurrent = 0x%x\n", pptable->Mem1MaxCurrent);
	dev_info(smu->adev->dev, "Mem1Offset = 0x%x\n", pptable->Mem1Offset);
	dev_info(smu->adev->dev, "Padding_TelemetryMem1 = 0x%x\n", pptable->Padding_TelemetryMem1);

	dev_info(smu->adev->dev, "MvddRatio = 0x%x\n", pptable->MvddRatio);

	dev_info(smu->adev->dev, "AcDcGpio = 0x%x\n", pptable->AcDcGpio);
	dev_info(smu->adev->dev, "AcDcPolarity = 0x%x\n", pptable->AcDcPolarity);
	dev_info(smu->adev->dev, "VR0HotGpio = 0x%x\n", pptable->VR0HotGpio);
	dev_info(smu->adev->dev, "VR0HotPolarity = 0x%x\n", pptable->VR0HotPolarity);
	dev_info(smu->adev->dev, "VR1HotGpio = 0x%x\n", pptable->VR1HotGpio);
	dev_info(smu->adev->dev, "VR1HotPolarity = 0x%x\n", pptable->VR1HotPolarity);
	dev_info(smu->adev->dev, "GthrGpio = 0x%x\n", pptable->GthrGpio);
	dev_info(smu->adev->dev, "GthrPolarity = 0x%x\n", pptable->GthrPolarity);
	dev_info(smu->adev->dev, "LedPin0 = 0x%x\n", pptable->LedPin0);
	dev_info(smu->adev->dev, "LedPin1 = 0x%x\n", pptable->LedPin1);
	dev_info(smu->adev->dev, "LedPin2 = 0x%x\n", pptable->LedPin2);
	dev_info(smu->adev->dev, "LedEnableMask = 0x%x\n", pptable->LedEnableMask);
	dev_info(smu->adev->dev, "LedPcie = 0x%x\n", pptable->LedPcie);
	dev_info(smu->adev->dev, "LedError = 0x%x\n", pptable->LedError);
	dev_info(smu->adev->dev, "LedSpare1[0] = 0x%x\n", pptable->LedSpare1[0]);
	dev_info(smu->adev->dev, "LedSpare1[1] = 0x%x\n", pptable->LedSpare1[1]);

	dev_info(smu->adev->dev, "PllGfxclkSpreadEnabled = 0x%x\n", pptable->PllGfxclkSpपढ़ोEnabled);
	dev_info(smu->adev->dev, "PllGfxclkSpreadPercent = 0x%x\n", pptable->PllGfxclkSpपढ़ोPercent);
	dev_info(smu->adev->dev, "PllGfxclkSpreadFreq = 0x%x\n",    pptable->PllGfxclkSpपढ़ोFreq);

	dev_info(smu->adev->dev, "DfllGfxclkSpreadEnabled = 0x%x\n", pptable->DfllGfxclkSpपढ़ोEnabled);
	dev_info(smu->adev->dev, "DfllGfxclkSpreadPercent = 0x%x\n", pptable->DfllGfxclkSpपढ़ोPercent);
	dev_info(smu->adev->dev, "DfllGfxclkSpreadFreq = 0x%x\n",    pptable->DfllGfxclkSpपढ़ोFreq);

	dev_info(smu->adev->dev, "UclkSpreadPadding = 0x%x\n", pptable->UclkSpपढ़ोPadding);
	dev_info(smu->adev->dev, "UclkSpreadFreq = 0x%x\n", pptable->UclkSpपढ़ोFreq);

	dev_info(smu->adev->dev, "FclkSpreadEnabled = 0x%x\n", pptable->FclkSpपढ़ोEnabled);
	dev_info(smu->adev->dev, "FclkSpreadPercent = 0x%x\n", pptable->FclkSpपढ़ोPercent);
	dev_info(smu->adev->dev, "FclkSpreadFreq = 0x%x\n", pptable->FclkSpपढ़ोFreq);

	dev_info(smu->adev->dev, "MemoryChannelEnabled = 0x%x\n", pptable->MemoryChannelEnabled);
	dev_info(smu->adev->dev, "DramBitWidth = 0x%x\n", pptable->DramBitWidth);
	dev_info(smu->adev->dev, "PaddingMem1[0] = 0x%x\n", pptable->PaddingMem1[0]);
	dev_info(smu->adev->dev, "PaddingMem1[1] = 0x%x\n", pptable->PaddingMem1[1]);
	dev_info(smu->adev->dev, "PaddingMem1[2] = 0x%x\n", pptable->PaddingMem1[2]);

	dev_info(smu->adev->dev, "TotalBoardPower = 0x%x\n", pptable->TotalBoardPower);
	dev_info(smu->adev->dev, "BoardPowerPadding = 0x%x\n", pptable->BoardPowerPadding);

	dev_info(smu->adev->dev, "XgmiLinkSpeed\n");
	क्रम (i = 0; i < NUM_XGMI_PSTATE_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = 0x%x\n", i, pptable->XgmiLinkSpeed[i]);
	dev_info(smu->adev->dev, "XgmiLinkWidth\n");
	क्रम (i = 0; i < NUM_XGMI_PSTATE_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = 0x%x\n", i, pptable->XgmiLinkWidth[i]);
	dev_info(smu->adev->dev, "XgmiFclkFreq\n");
	क्रम (i = 0; i < NUM_XGMI_PSTATE_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = 0x%x\n", i, pptable->XgmiFclkFreq[i]);
	dev_info(smu->adev->dev, "XgmiSocVoltage\n");
	क्रम (i = 0; i < NUM_XGMI_PSTATE_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = 0x%x\n", i, pptable->XgmiSocVoltage[i]);

	dev_info(smu->adev->dev, "HsrEnabled = 0x%x\n", pptable->HsrEnabled);
	dev_info(smu->adev->dev, "VddqOffEnabled = 0x%x\n", pptable->VddqOffEnabled);
	dev_info(smu->adev->dev, "PaddingUmcFlags[0] = 0x%x\n", pptable->PaddingUmcFlags[0]);
	dev_info(smu->adev->dev, "PaddingUmcFlags[1] = 0x%x\n", pptable->PaddingUmcFlags[1]);

	dev_info(smu->adev->dev, "BoardReserved[0] = 0x%x\n", pptable->BoardReserved[0]);
	dev_info(smu->adev->dev, "BoardReserved[1] = 0x%x\n", pptable->BoardReserved[1]);
	dev_info(smu->adev->dev, "BoardReserved[2] = 0x%x\n", pptable->BoardReserved[2]);
	dev_info(smu->adev->dev, "BoardReserved[3] = 0x%x\n", pptable->BoardReserved[3]);
	dev_info(smu->adev->dev, "BoardReserved[4] = 0x%x\n", pptable->BoardReserved[4]);
	dev_info(smu->adev->dev, "BoardReserved[5] = 0x%x\n", pptable->BoardReserved[5]);
	dev_info(smu->adev->dev, "BoardReserved[6] = 0x%x\n", pptable->BoardReserved[6]);
	dev_info(smu->adev->dev, "BoardReserved[7] = 0x%x\n", pptable->BoardReserved[7]);
	dev_info(smu->adev->dev, "BoardReserved[8] = 0x%x\n", pptable->BoardReserved[8]);
	dev_info(smu->adev->dev, "BoardReserved[9] = 0x%x\n", pptable->BoardReserved[9]);
	dev_info(smu->adev->dev, "BoardReserved[10] = 0x%x\n", pptable->BoardReserved[10]);

	dev_info(smu->adev->dev, "MmHubPadding[0] = 0x%x\n", pptable->MmHubPadding[0]);
	dev_info(smu->adev->dev, "MmHubPadding[1] = 0x%x\n", pptable->MmHubPadding[1]);
	dev_info(smu->adev->dev, "MmHubPadding[2] = 0x%x\n", pptable->MmHubPadding[2]);
	dev_info(smu->adev->dev, "MmHubPadding[3] = 0x%x\n", pptable->MmHubPadding[3]);
	dev_info(smu->adev->dev, "MmHubPadding[4] = 0x%x\n", pptable->MmHubPadding[4]);
	dev_info(smu->adev->dev, "MmHubPadding[5] = 0x%x\n", pptable->MmHubPadding[5]);
	dev_info(smu->adev->dev, "MmHubPadding[6] = 0x%x\n", pptable->MmHubPadding[6]);
	dev_info(smu->adev->dev, "MmHubPadding[7] = 0x%x\n", pptable->MmHubPadding[7]);
पूर्ण

अटल व्योम sienna_cichlid_fill_i2c_req(SwI2cRequest_t  *req, bool ग_लिखो,
				  uपूर्णांक8_t address, uपूर्णांक32_t numbytes,
				  uपूर्णांक8_t *data)
अणु
	पूर्णांक i;

	req->I2CcontrollerPort = 1;
	req->I2CSpeed = 2;
	req->SlaveAddress = address;
	req->NumCmds = numbytes;

	क्रम (i = 0; i < numbytes; i++) अणु
		SwI2cCmd_t *cmd =  &req->SwI2cCmds[i];

		/* First 2 bytes are always ग_लिखो क्रम lower 2b EEPROM address */
		अगर (i < 2)
			cmd->CmdConfig = CMDCONFIG_READWRITE_MASK;
		अन्यथा
			cmd->CmdConfig = ग_लिखो ? CMDCONFIG_READWRITE_MASK : 0;


		/* Add RESTART क्रम पढ़ो  after address filled */
		cmd->CmdConfig |= (i == 2 && !ग_लिखो) ? CMDCONFIG_RESTART_MASK : 0;

		/* Add STOP in the end */
		cmd->CmdConfig |= (i == (numbytes - 1)) ? CMDCONFIG_STOP_MASK : 0;

		/* Fill with data regardless अगर पढ़ो or ग_लिखो to simplअगरy code */
		cmd->ReadWriteData = data[i];
	पूर्ण
पूर्ण

अटल पूर्णांक sienna_cichlid_i2c_पढ़ो_data(काष्ठा i2c_adapter *control,
					       uपूर्णांक8_t address,
					       uपूर्णांक8_t *data,
					       uपूर्णांक32_t numbytes)
अणु
	uपूर्णांक32_t  i, ret = 0;
	SwI2cRequest_t req;
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);
	काष्ठा smu_table_context *smu_table = &adev->smu.smu_table;
	काष्ठा smu_table *table = &smu_table->driver_table;

	अगर (numbytes > MAX_SW_I2C_COMMANDS) अणु
		dev_err(adev->dev, "numbytes requested %d is over max allowed %d\n",
			numbytes, MAX_SW_I2C_COMMANDS);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&req, 0, माप(req));
	sienna_cichlid_fill_i2c_req(&req, false, address, numbytes, data);

	mutex_lock(&adev->smu.mutex);
	/* Now पढ़ो data starting with that address */
	ret = smu_cmn_update_table(&adev->smu, SMU_TABLE_I2C_COMMANDS, 0, &req,
					true);
	mutex_unlock(&adev->smu.mutex);

	अगर (!ret) अणु
		SwI2cRequest_t *res = (SwI2cRequest_t *)table->cpu_addr;

		/* Assume SMU  fills res.SwI2cCmds[i].Data with पढ़ो bytes */
		क्रम (i = 0; i < numbytes; i++)
			data[i] = res->SwI2cCmds[i].ReadWriteData;

		dev_dbg(adev->dev, "sienna_cichlid_i2c_read_data, address = %x, bytes = %d, data :",
				  (uपूर्णांक16_t)address, numbytes);

		prपूर्णांक_hex_dump(KERN_DEBUG, "data: ", DUMP_PREFIX_NONE,
			       8, 1, data, numbytes, false);
	पूर्ण अन्यथा
		dev_err(adev->dev, "sienna_cichlid_i2c_read_data - error occurred :%x", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक sienna_cichlid_i2c_ग_लिखो_data(काष्ठा i2c_adapter *control,
						uपूर्णांक8_t address,
						uपूर्णांक8_t *data,
						uपूर्णांक32_t numbytes)
अणु
	uपूर्णांक32_t ret;
	SwI2cRequest_t req;
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);

	अगर (numbytes > MAX_SW_I2C_COMMANDS) अणु
		dev_err(adev->dev, "numbytes requested %d is over max allowed %d\n",
			numbytes, MAX_SW_I2C_COMMANDS);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&req, 0, माप(req));
	sienna_cichlid_fill_i2c_req(&req, true, address, numbytes, data);

	mutex_lock(&adev->smu.mutex);
	ret = smu_cmn_update_table(&adev->smu, SMU_TABLE_I2C_COMMANDS, 0, &req, true);
	mutex_unlock(&adev->smu.mutex);

	अगर (!ret) अणु
		dev_dbg(adev->dev, "sienna_cichlid_i2c_write(), address = %x, bytes = %d , data: ",
					 (uपूर्णांक16_t)address, numbytes);

		prपूर्णांक_hex_dump(KERN_DEBUG, "data: ", DUMP_PREFIX_NONE,
			       8, 1, data, numbytes, false);
		/*
		 * According to EEPROM spec there is a MAX of 10 ms required क्रम
		 * EEPROM to flush पूर्णांकernal RX buffer after STOP was issued at the
		 * end of ग_लिखो transaction. During this समय the EEPROM will not be
		 * responsive to any more commands - so रुको a bit more.
		 */
		msleep(10);

	पूर्ण अन्यथा
		dev_err(adev->dev, "sienna_cichlid_i2c_write- error occurred :%x", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक sienna_cichlid_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
			      काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	uपूर्णांक32_t  i, j, ret, data_size, data_chunk_size, next_eeprom_addr = 0;
	uपूर्णांक8_t *data_ptr, data_chunk[MAX_SW_I2C_COMMANDS] = अणु 0 पूर्ण;

	क्रम (i = 0; i < num; i++) अणु
		/*
		 * SMU पूर्णांकerface allows at most MAX_SW_I2C_COMMANDS bytes of data at
		 * once and hence the data needs to be spliced पूर्णांकo chunks and sent each
		 * chunk separately
		 */
		data_size = msgs[i].len - 2;
		data_chunk_size = MAX_SW_I2C_COMMANDS - 2;
		next_eeprom_addr = (msgs[i].buf[0] << 8 & 0xff00) | (msgs[i].buf[1] & 0xff);
		data_ptr = msgs[i].buf + 2;

		क्रम (j = 0; j < data_size / data_chunk_size; j++) अणु
			/* Insert the EEPROM dest addess, bits 0-15 */
			data_chunk[0] = ((next_eeprom_addr >> 8) & 0xff);
			data_chunk[1] = (next_eeprom_addr & 0xff);

			अगर (msgs[i].flags & I2C_M_RD) अणु
				ret = sienna_cichlid_i2c_पढ़ो_data(i2c_adap,
							     (uपूर्णांक8_t)msgs[i].addr,
							     data_chunk, MAX_SW_I2C_COMMANDS);

				स_नकल(data_ptr, data_chunk + 2, data_chunk_size);
			पूर्ण अन्यथा अणु

				स_नकल(data_chunk + 2, data_ptr, data_chunk_size);

				ret = sienna_cichlid_i2c_ग_लिखो_data(i2c_adap,
							      (uपूर्णांक8_t)msgs[i].addr,
							      data_chunk, MAX_SW_I2C_COMMANDS);
			पूर्ण

			अगर (ret) अणु
				num = -EIO;
				जाओ fail;
			पूर्ण

			next_eeprom_addr += data_chunk_size;
			data_ptr += data_chunk_size;
		पूर्ण

		अगर (data_size % data_chunk_size) अणु
			data_chunk[0] = ((next_eeprom_addr >> 8) & 0xff);
			data_chunk[1] = (next_eeprom_addr & 0xff);

			अगर (msgs[i].flags & I2C_M_RD) अणु
				ret = sienna_cichlid_i2c_पढ़ो_data(i2c_adap,
							     (uपूर्णांक8_t)msgs[i].addr,
							     data_chunk, (data_size % data_chunk_size) + 2);

				स_नकल(data_ptr, data_chunk + 2, data_size % data_chunk_size);
			पूर्ण अन्यथा अणु
				स_नकल(data_chunk + 2, data_ptr, data_size % data_chunk_size);

				ret = sienna_cichlid_i2c_ग_लिखो_data(i2c_adap,
							      (uपूर्णांक8_t)msgs[i].addr,
							      data_chunk, (data_size % data_chunk_size) + 2);
			पूर्ण

			अगर (ret) अणु
				num = -EIO;
				जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण

fail:
	वापस num;
पूर्ण

अटल u32 sienna_cichlid_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण


अटल स्थिर काष्ठा i2c_algorithm sienna_cichlid_i2c_algo = अणु
	.master_xfer = sienna_cichlid_i2c_xfer,
	.functionality = sienna_cichlid_i2c_func,
पूर्ण;

अटल पूर्णांक sienna_cichlid_i2c_control_init(काष्ठा smu_context *smu, काष्ठा i2c_adapter *control)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);
	पूर्णांक res;

	control->owner = THIS_MODULE;
	control->class = I2C_CLASS_SPD;
	control->dev.parent = &adev->pdev->dev;
	control->algo = &sienna_cichlid_i2c_algo;
	snम_लिखो(control->name, माप(control->name), "AMDGPU SMU");

	res = i2c_add_adapter(control);
	अगर (res)
		DRM_ERROR("Failed to register hw i2c, err: %d\n", res);

	वापस res;
पूर्ण

अटल व्योम sienna_cichlid_i2c_control_fini(काष्ठा smu_context *smu, काष्ठा i2c_adapter *control)
अणु
	i2c_del_adapter(control);
पूर्ण

अटल sमाप_प्रकार sienna_cichlid_get_gpu_metrics(काष्ठा smu_context *smu,
					      व्योम **table)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा gpu_metrics_v1_1 *gpu_metrics =
		(काष्ठा gpu_metrics_v1_1 *)smu_table->gpu_metrics_table;
	SmuMetricsExternal_t metrics_बाह्यal;
	SmuMetrics_t *metrics =
		&(metrics_बाह्यal.SmuMetrics);
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t smu_version;
	पूर्णांक ret = 0;

	ret = smu_cmn_get_metrics_table(smu,
					&metrics_बाह्यal,
					true);
	अगर (ret)
		वापस ret;

	smu_cmn_init_soft_gpu_metrics(gpu_metrics, 1, 1);

	gpu_metrics->temperature_edge = metrics->TemperatureEdge;
	gpu_metrics->temperature_hotspot = metrics->TemperatureHotspot;
	gpu_metrics->temperature_mem = metrics->TemperatureMem;
	gpu_metrics->temperature_vrgfx = metrics->TemperatureVrGfx;
	gpu_metrics->temperature_vrsoc = metrics->TemperatureVrSoc;
	gpu_metrics->temperature_vrmem = metrics->TemperatureVrMem0;

	gpu_metrics->average_gfx_activity = metrics->AverageGfxActivity;
	gpu_metrics->average_umc_activity = metrics->AverageUclkActivity;
	gpu_metrics->average_mm_activity = metrics->VcnActivityPercentage;

	gpu_metrics->average_socket_घातer = metrics->AverageSocketPower;
	gpu_metrics->energy_accumulator = metrics->EnergyAccumulator;

	अगर (metrics->AverageGfxActivity <= SMU_11_0_7_GFX_BUSY_THRESHOLD)
		gpu_metrics->average_gfxclk_frequency = metrics->AverageGfxclkFrequencyPostDs;
	अन्यथा
		gpu_metrics->average_gfxclk_frequency = metrics->AverageGfxclkFrequencyPreDs;
	gpu_metrics->average_uclk_frequency = metrics->AverageUclkFrequencyPostDs;
	gpu_metrics->average_vclk0_frequency = metrics->AverageVclk0Frequency;
	gpu_metrics->average_dclk0_frequency = metrics->AverageDclk0Frequency;
	gpu_metrics->average_vclk1_frequency = metrics->AverageVclk1Frequency;
	gpu_metrics->average_dclk1_frequency = metrics->AverageDclk1Frequency;

	gpu_metrics->current_gfxclk = metrics->CurrClock[PPCLK_GFXCLK];
	gpu_metrics->current_socclk = metrics->CurrClock[PPCLK_SOCCLK];
	gpu_metrics->current_uclk = metrics->CurrClock[PPCLK_UCLK];
	gpu_metrics->current_vclk0 = metrics->CurrClock[PPCLK_VCLK_0];
	gpu_metrics->current_dclk0 = metrics->CurrClock[PPCLK_DCLK_0];
	gpu_metrics->current_vclk1 = metrics->CurrClock[PPCLK_VCLK_1];
	gpu_metrics->current_dclk1 = metrics->CurrClock[PPCLK_DCLK_1];

	gpu_metrics->throttle_status = metrics->ThrottlerStatus;

	gpu_metrics->current_fan_speed = metrics->CurrFanSpeed;

	ret = smu_cmn_get_smc_version(smu, शून्य, &smu_version);
	अगर (ret)
		वापस ret;

	अगर (((adev->asic_type == CHIP_SIENNA_CICHLID) && smu_version > 0x003A1E00) ||
	      ((adev->asic_type == CHIP_NAVY_FLOUNDER) && smu_version > 0x00410400)) अणु
		gpu_metrics->pcie_link_width = metrics->PcieWidth;
		gpu_metrics->pcie_link_speed = link_speed[metrics->PcieRate];
	पूर्ण अन्यथा अणु
		gpu_metrics->pcie_link_width =
				smu_v11_0_get_current_pcie_link_width(smu);
		gpu_metrics->pcie_link_speed =
				smu_v11_0_get_current_pcie_link_speed(smu);
	पूर्ण

	gpu_metrics->प्रणाली_घड़ी_counter = kसमय_get_bootसमय_ns();

	*table = (व्योम *)gpu_metrics;

	वापस माप(काष्ठा gpu_metrics_v1_1);
पूर्ण

अटल पूर्णांक sienna_cichlid_enable_mgpu_fan_boost(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	PPTable_t *smc_pptable = table_context->driver_pptable;

	/*
	 * Skip the MGpuFanBoost setting क्रम those ASICs
	 * which करो not support it
	 */
	अगर (!smc_pptable->MGpuFanBoostLimitRpm)
		वापस 0;

	वापस smu_cmn_send_smc_msg_with_param(smu,
					       SMU_MSG_SetMGpuFanBoostLimitRpm,
					       0,
					       शून्य);
पूर्ण

अटल पूर्णांक sienna_cichlid_gpo_control(काष्ठा smu_context *smu,
				      bool enablement)
अणु
	uपूर्णांक32_t smu_version;
	पूर्णांक ret = 0;


	अगर (smu_cmn_feature_is_supported(smu, SMU_FEATURE_DPM_GFX_GPO_BIT)) अणु
		ret = smu_cmn_get_smc_version(smu, शून्य, &smu_version);
		अगर (ret)
			वापस ret;

		अगर (enablement) अणु
			अगर (smu_version < 0x003a2500) अणु
				ret = smu_cmn_send_smc_msg_with_param(smu,
								      SMU_MSG_SetGpoFeaturePMask,
								      GFX_GPO_PACE_MASK | GFX_GPO_DEM_MASK,
								      शून्य);
			पूर्ण अन्यथा अणु
				ret = smu_cmn_send_smc_msg_with_param(smu,
								      SMU_MSG_DisallowGpo,
								      0,
								      शून्य);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (smu_version < 0x003a2500) अणु
				ret = smu_cmn_send_smc_msg_with_param(smu,
								      SMU_MSG_SetGpoFeaturePMask,
								      0,
								      शून्य);
			पूर्ण अन्यथा अणु
				ret = smu_cmn_send_smc_msg_with_param(smu,
								      SMU_MSG_DisallowGpo,
								      1,
								      शून्य);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sienna_cichlid_notअगरy_2nd_usb20_port(काष्ठा smu_context *smu)
अणु
	uपूर्णांक32_t smu_version;
	पूर्णांक ret = 0;

	ret = smu_cmn_get_smc_version(smu, शून्य, &smu_version);
	अगर (ret)
		वापस ret;

	/*
	 * Message SMU_MSG_Enable2ndUSB20Port is supported by 58.45
	 * onwards PMFWs.
	 */
	अगर (smu_version < 0x003A2D00)
		वापस 0;

	वापस smu_cmn_send_smc_msg_with_param(smu,
					       SMU_MSG_Enable2ndUSB20Port,
					       smu->smu_table.boot_values.firmware_caps & ATOM_FIRMWARE_CAP_ENABLE_2ND_USB20PORT ?
					       1 : 0,
					       शून्य);
पूर्ण

अटल पूर्णांक sienna_cichlid_प्रणाली_features_control(काष्ठा smu_context *smu,
						  bool en)
अणु
	पूर्णांक ret = 0;

	अगर (en) अणु
		ret = sienna_cichlid_notअगरy_2nd_usb20_port(smu);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस smu_v11_0_प्रणाली_features_control(smu, en);
पूर्ण

अटल पूर्णांक sienna_cichlid_set_mp1_state(काष्ठा smu_context *smu,
					क्रमागत pp_mp1_state mp1_state)
अणु
	पूर्णांक ret;

	चयन (mp1_state) अणु
	हाल PP_MP1_STATE_UNLOAD:
		ret = smu_cmn_set_mp1_state(smu, mp1_state);
		अवरोध;
	शेष:
		/* Ignore others */
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pptable_funcs sienna_cichlid_ppt_funcs = अणु
	.get_allowed_feature_mask = sienna_cichlid_get_allowed_feature_mask,
	.set_शेष_dpm_table = sienna_cichlid_set_शेष_dpm_table,
	.dpm_set_vcn_enable = sienna_cichlid_dpm_set_vcn_enable,
	.dpm_set_jpeg_enable = sienna_cichlid_dpm_set_jpeg_enable,
	.i2c_init = sienna_cichlid_i2c_control_init,
	.i2c_fini = sienna_cichlid_i2c_control_fini,
	.prपूर्णांक_clk_levels = sienna_cichlid_prपूर्णांक_clk_levels,
	.क्रमce_clk_levels = sienna_cichlid_क्रमce_clk_levels,
	.populate_umd_state_clk = sienna_cichlid_populate_umd_state_clk,
	.pre_display_config_changed = sienna_cichlid_pre_display_config_changed,
	.display_config_changed = sienna_cichlid_display_config_changed,
	.notअगरy_smc_display_config = sienna_cichlid_notअगरy_smc_display_config,
	.is_dpm_running = sienna_cichlid_is_dpm_running,
	.get_fan_speed_percent = sienna_cichlid_get_fan_speed_percent,
	.get_घातer_profile_mode = sienna_cichlid_get_घातer_profile_mode,
	.set_घातer_profile_mode = sienna_cichlid_set_घातer_profile_mode,
	.set_watermarks_table = sienna_cichlid_set_watermarks_table,
	.पढ़ो_sensor = sienna_cichlid_पढ़ो_sensor,
	.get_uclk_dpm_states = sienna_cichlid_get_uclk_dpm_states,
	.set_perक्रमmance_level = smu_v11_0_set_perक्रमmance_level,
	.get_thermal_temperature_range = sienna_cichlid_get_thermal_temperature_range,
	.display_disable_memory_घड़ी_चयन = sienna_cichlid_display_disable_memory_घड़ी_चयन,
	.get_घातer_limit = sienna_cichlid_get_घातer_limit,
	.update_pcie_parameters = sienna_cichlid_update_pcie_parameters,
	.dump_pptable = sienna_cichlid_dump_pptable,
	.init_microcode = smu_v11_0_init_microcode,
	.load_microcode = smu_v11_0_load_microcode,
	.init_smc_tables = sienna_cichlid_init_smc_tables,
	.fini_smc_tables = smu_v11_0_fini_smc_tables,
	.init_घातer = smu_v11_0_init_घातer,
	.fini_घातer = smu_v11_0_fini_घातer,
	.check_fw_status = smu_v11_0_check_fw_status,
	.setup_pptable = sienna_cichlid_setup_pptable,
	.get_vbios_bootup_values = smu_v11_0_get_vbios_bootup_values,
	.check_fw_version = smu_v11_0_check_fw_version,
	.ग_लिखो_pptable = smu_cmn_ग_लिखो_pptable,
	.set_driver_table_location = smu_v11_0_set_driver_table_location,
	.set_tool_table_location = smu_v11_0_set_tool_table_location,
	.notअगरy_memory_pool_location = smu_v11_0_notअगरy_memory_pool_location,
	.प्रणाली_features_control = sienna_cichlid_प्रणाली_features_control,
	.send_smc_msg_with_param = smu_cmn_send_smc_msg_with_param,
	.send_smc_msg = smu_cmn_send_smc_msg,
	.init_display_count = शून्य,
	.set_allowed_mask = smu_v11_0_set_allowed_mask,
	.get_enabled_mask = smu_cmn_get_enabled_mask,
	.feature_is_enabled = smu_cmn_feature_is_enabled,
	.disable_all_features_with_exception = smu_cmn_disable_all_features_with_exception,
	.notअगरy_display_change = शून्य,
	.set_घातer_limit = smu_v11_0_set_घातer_limit,
	.init_max_sustainable_घड़ीs = smu_v11_0_init_max_sustainable_घड़ीs,
	.enable_thermal_alert = smu_v11_0_enable_thermal_alert,
	.disable_thermal_alert = smu_v11_0_disable_thermal_alert,
	.set_min_dcef_deep_sleep = शून्य,
	.display_घड़ी_voltage_request = smu_v11_0_display_घड़ी_voltage_request,
	.get_fan_control_mode = smu_v11_0_get_fan_control_mode,
	.set_fan_control_mode = smu_v11_0_set_fan_control_mode,
	.set_fan_speed_percent = smu_v11_0_set_fan_speed_percent,
	.set_xgmi_pstate = smu_v11_0_set_xgmi_pstate,
	.gfx_off_control = smu_v11_0_gfx_off_control,
	.रेजिस्टर_irq_handler = smu_v11_0_रेजिस्टर_irq_handler,
	.set_azalia_d3_pme = smu_v11_0_set_azalia_d3_pme,
	.get_max_sustainable_घड़ीs_by_dc = smu_v11_0_get_max_sustainable_घड़ीs_by_dc,
	.baco_is_support= sienna_cichlid_is_baco_supported,
	.baco_get_state = smu_v11_0_baco_get_state,
	.baco_set_state = smu_v11_0_baco_set_state,
	.baco_enter = smu_v11_0_baco_enter,
	.baco_निकास = smu_v11_0_baco_निकास,
	.mode1_reset_is_support = sienna_cichlid_is_mode1_reset_supported,
	.mode1_reset = smu_v11_0_mode1_reset,
	.get_dpm_ultimate_freq = sienna_cichlid_get_dpm_ultimate_freq,
	.set_soft_freq_limited_range = smu_v11_0_set_soft_freq_limited_range,
	.set_शेष_od_settings = sienna_cichlid_set_शेष_od_settings,
	.od_edit_dpm_table = sienna_cichlid_od_edit_dpm_table,
	.run_btc = sienna_cichlid_run_btc,
	.set_घातer_source = smu_v11_0_set_घातer_source,
	.get_pp_feature_mask = smu_cmn_get_pp_feature_mask,
	.set_pp_feature_mask = smu_cmn_set_pp_feature_mask,
	.get_gpu_metrics = sienna_cichlid_get_gpu_metrics,
	.enable_mgpu_fan_boost = sienna_cichlid_enable_mgpu_fan_boost,
	.gfx_ulv_control = smu_v11_0_gfx_ulv_control,
	.deep_sleep_control = smu_v11_0_deep_sleep_control,
	.get_fan_parameters = sienna_cichlid_get_fan_parameters,
	.पूर्णांकerrupt_work = smu_v11_0_पूर्णांकerrupt_work,
	.gpo_control = sienna_cichlid_gpo_control,
	.set_mp1_state = sienna_cichlid_set_mp1_state,
पूर्ण;

व्योम sienna_cichlid_set_ppt_funcs(काष्ठा smu_context *smu)
अणु
	smu->ppt_funcs = &sienna_cichlid_ppt_funcs;
	smu->message_map = sienna_cichlid_message_map;
	smu->घड़ी_map = sienna_cichlid_clk_map;
	smu->feature_map = sienna_cichlid_feature_mask_map;
	smu->table_map = sienna_cichlid_table_map;
	smu->pwr_src_map = sienna_cichlid_pwr_src_map;
	smu->workload_map = sienna_cichlid_workload_map;
पूर्ण
