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
#समावेश "soc15_common.h"
#समावेश "smu_v11_0.h"
#समावेश "smu11_driver_if_navi10.h"
#समावेश "atom.h"
#समावेश "navi10_ppt.h"
#समावेश "smu_v11_0_pptable.h"
#समावेश "smu_v11_0_ppsmc.h"
#समावेश "nbio/nbio_2_3_offset.h"
#समावेश "nbio/nbio_2_3_sh_mask.h"
#समावेश "thm/thm_11_0_2_offset.h"
#समावेश "thm/thm_11_0_2_sh_mask.h"

#समावेश "asic_reg/mp/mp_11_0_sh_mask.h"
#समावेश "smu_cmn.h"
#समावेश "smu_11_0_cdr_table.h"

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
	FEATURE_MASK(FEATURE_DPM_GFXCLK_BIT)	 | \
	FEATURE_MASK(FEATURE_DPM_GFX_PACE_BIT)	 | \
	FEATURE_MASK(FEATURE_DPM_UCLK_BIT)	 | \
	FEATURE_MASK(FEATURE_DPM_SOCCLK_BIT)	 | \
	FEATURE_MASK(FEATURE_DPM_MP0CLK_BIT)	 | \
	FEATURE_MASK(FEATURE_DPM_LINK_BIT)	 | \
	FEATURE_MASK(FEATURE_DPM_DCEFCLK_BIT))

#घोषणा SMU_11_0_GFX_BUSY_THRESHOLD 15

अटल काष्ठा cmn2asic_msg_mapping navi10_message_map[SMU_MSG_MAX_COUNT] = अणु
	MSG_MAP(TestMessage,			PPSMC_MSG_TestMessage,			1),
	MSG_MAP(GetSmuVersion,			PPSMC_MSG_GetSmuVersion,		1),
	MSG_MAP(GetDriverIfVersion,		PPSMC_MSG_GetDriverIfVersion,		1),
	MSG_MAP(SetAllowedFeaturesMaskLow,	PPSMC_MSG_SetAllowedFeaturesMaskLow,	0),
	MSG_MAP(SetAllowedFeaturesMaskHigh,	PPSMC_MSG_SetAllowedFeaturesMaskHigh,	0),
	MSG_MAP(EnableAllSmuFeatures,		PPSMC_MSG_EnableAllSmuFeatures,		0),
	MSG_MAP(DisableAllSmuFeatures,		PPSMC_MSG_DisableAllSmuFeatures,	0),
	MSG_MAP(EnableSmuFeaturesLow,		PPSMC_MSG_EnableSmuFeaturesLow,		1),
	MSG_MAP(EnableSmuFeaturesHigh,		PPSMC_MSG_EnableSmuFeaturesHigh,	1),
	MSG_MAP(DisableSmuFeaturesLow,		PPSMC_MSG_DisableSmuFeaturesLow,	1),
	MSG_MAP(DisableSmuFeaturesHigh,		PPSMC_MSG_DisableSmuFeaturesHigh,	1),
	MSG_MAP(GetEnabledSmuFeaturesLow,	PPSMC_MSG_GetEnabledSmuFeaturesLow,	1),
	MSG_MAP(GetEnabledSmuFeaturesHigh,	PPSMC_MSG_GetEnabledSmuFeaturesHigh,	1),
	MSG_MAP(SetWorkloadMask,		PPSMC_MSG_SetWorkloadMask,		1),
	MSG_MAP(SetPptLimit,			PPSMC_MSG_SetPptLimit,			0),
	MSG_MAP(SetDriverDramAddrHigh,		PPSMC_MSG_SetDriverDramAddrHigh,	0),
	MSG_MAP(SetDriverDramAddrLow,		PPSMC_MSG_SetDriverDramAddrLow,		0),
	MSG_MAP(SetToolsDramAddrHigh,		PPSMC_MSG_SetToolsDramAddrHigh,		0),
	MSG_MAP(SetToolsDramAddrLow,		PPSMC_MSG_SetToolsDramAddrLow,		0),
	MSG_MAP(TransferTableSmu2Dram,		PPSMC_MSG_TransferTableSmu2Dram,	0),
	MSG_MAP(TransferTableDram2Smu,		PPSMC_MSG_TransferTableDram2Smu,	0),
	MSG_MAP(UseDefaultPPTable,		PPSMC_MSG_UseDefaultPPTable,		0),
	MSG_MAP(UseBackupPPTable,		PPSMC_MSG_UseBackupPPTable,		0),
	MSG_MAP(RunBtc,				PPSMC_MSG_RunBtc,			0),
	MSG_MAP(EnterBaco,			PPSMC_MSG_EnterBaco,			0),
	MSG_MAP(SetSoftMinByFreq,		PPSMC_MSG_SetSoftMinByFreq,		0),
	MSG_MAP(SetSoftMaxByFreq,		PPSMC_MSG_SetSoftMaxByFreq,		0),
	MSG_MAP(SetHardMinByFreq,		PPSMC_MSG_SetHardMinByFreq,		1),
	MSG_MAP(SetHardMaxByFreq,		PPSMC_MSG_SetHardMaxByFreq,		0),
	MSG_MAP(GetMinDpmFreq,			PPSMC_MSG_GetMinDpmFreq,		1),
	MSG_MAP(GetMaxDpmFreq,			PPSMC_MSG_GetMaxDpmFreq,		1),
	MSG_MAP(GetDpmFreqByIndex,		PPSMC_MSG_GetDpmFreqByIndex,		1),
	MSG_MAP(SetMemoryChannelConfig,		PPSMC_MSG_SetMemoryChannelConfig,	0),
	MSG_MAP(SetGeminiMode,			PPSMC_MSG_SetGeminiMode,		0),
	MSG_MAP(SetGeminiApertureHigh,		PPSMC_MSG_SetGeminiApertureHigh,	0),
	MSG_MAP(SetGeminiApertureLow,		PPSMC_MSG_SetGeminiApertureLow,		0),
	MSG_MAP(OverridePcieParameters,		PPSMC_MSG_OverridePcieParameters,	0),
	MSG_MAP(SetMinDeepSleepDcefclk,		PPSMC_MSG_SetMinDeepSleepDcefclk,	0),
	MSG_MAP(ReenableAcDcInterrupt,		PPSMC_MSG_ReenableAcDcInterrupt,	0),
	MSG_MAP(NotअगरyPowerSource,		PPSMC_MSG_NotअगरyPowerSource,		0),
	MSG_MAP(SetUclkFastSwitch,		PPSMC_MSG_SetUclkFastSwitch,		0),
	MSG_MAP(SetVideoFps,			PPSMC_MSG_SetVideoFps,			0),
	MSG_MAP(PrepareMp1ForUnload,		PPSMC_MSG_PrepareMp1ForUnload,		1),
	MSG_MAP(DramLogSetDramAddrHigh,		PPSMC_MSG_DramLogSetDramAddrHigh,	0),
	MSG_MAP(DramLogSetDramAddrLow,		PPSMC_MSG_DramLogSetDramAddrLow,	0),
	MSG_MAP(DramLogSetDramSize,		PPSMC_MSG_DramLogSetDramSize,		0),
	MSG_MAP(ConfigureGfxDidt,		PPSMC_MSG_ConfigureGfxDidt,		0),
	MSG_MAP(NumOfDisplays,			PPSMC_MSG_NumOfDisplays,		0),
	MSG_MAP(SetSystemVirtualDramAddrHigh,	PPSMC_MSG_SetSystemVirtualDramAddrHigh,	0),
	MSG_MAP(SetSystemVirtualDramAddrLow,	PPSMC_MSG_SetSystemVirtualDramAddrLow,	0),
	MSG_MAP(AllowGfxOff,			PPSMC_MSG_AllowGfxOff,			0),
	MSG_MAP(DisallowGfxOff,			PPSMC_MSG_DisallowGfxOff,		0),
	MSG_MAP(GetPptLimit,			PPSMC_MSG_GetPptLimit,			0),
	MSG_MAP(GetDcModeMaxDpmFreq,		PPSMC_MSG_GetDcModeMaxDpmFreq,		1),
	MSG_MAP(GetDebugData,			PPSMC_MSG_GetDebugData,			0),
	MSG_MAP(ExitBaco,			PPSMC_MSG_ExitBaco,			0),
	MSG_MAP(PrepareMp1ForReset,		PPSMC_MSG_PrepareMp1ForReset,		0),
	MSG_MAP(PrepareMp1ForShutकरोwn,		PPSMC_MSG_PrepareMp1ForShutकरोwn,	0),
	MSG_MAP(PowerUpVcn,			PPSMC_MSG_PowerUpVcn,			0),
	MSG_MAP(PowerDownVcn,			PPSMC_MSG_PowerDownVcn,			0),
	MSG_MAP(PowerUpJpeg,			PPSMC_MSG_PowerUpJpeg,			0),
	MSG_MAP(PowerDownJpeg,			PPSMC_MSG_PowerDownJpeg,		0),
	MSG_MAP(BacoAudioD3PME,			PPSMC_MSG_BacoAudioD3PME,		0),
	MSG_MAP(ArmD3,				PPSMC_MSG_ArmD3,			0),
	MSG_MAP(DAL_DISABLE_DUMMY_PSTATE_CHANGE,PPSMC_MSG_DALDisableDummyPstateChange,	0),
	MSG_MAP(DAL_ENABLE_DUMMY_PSTATE_CHANGE,	PPSMC_MSG_DALEnableDummyPstateChange,	0),
	MSG_MAP(GetVoltageByDpm,		PPSMC_MSG_GetVoltageByDpm,		0),
	MSG_MAP(GetVoltageByDpmOverdrive,	PPSMC_MSG_GetVoltageByDpmOverdrive,	0),
	MSG_MAP(SetMGpuFanBoostLimitRpm,	PPSMC_MSG_SetMGpuFanBoostLimitRpm,	0),
	MSG_MAP(SET_DRIVER_DUMMY_TABLE_DRAM_ADDR_HIGH, PPSMC_MSG_SetDriverDummyTableDramAddrHigh, 0),
	MSG_MAP(SET_DRIVER_DUMMY_TABLE_DRAM_ADDR_LOW, PPSMC_MSG_SetDriverDummyTableDramAddrLow, 0),
	MSG_MAP(GET_UMC_FW_WA,			PPSMC_MSG_GetUMCFWWA,			0),
पूर्ण;

अटल काष्ठा cmn2asic_mapping navi10_clk_map[SMU_CLK_COUNT] = अणु
	CLK_MAP(GFXCLK, PPCLK_GFXCLK),
	CLK_MAP(SCLK,	PPCLK_GFXCLK),
	CLK_MAP(SOCCLK, PPCLK_SOCCLK),
	CLK_MAP(FCLK, PPCLK_SOCCLK),
	CLK_MAP(UCLK, PPCLK_UCLK),
	CLK_MAP(MCLK, PPCLK_UCLK),
	CLK_MAP(DCLK, PPCLK_DCLK),
	CLK_MAP(VCLK, PPCLK_VCLK),
	CLK_MAP(DCEFCLK, PPCLK_DCEFCLK),
	CLK_MAP(DISPCLK, PPCLK_DISPCLK),
	CLK_MAP(PIXCLK, PPCLK_PIXCLK),
	CLK_MAP(PHYCLK, PPCLK_PHYCLK),
पूर्ण;

अटल काष्ठा cmn2asic_mapping navi10_feature_mask_map[SMU_FEATURE_COUNT] = अणु
	FEA_MAP(DPM_PREFETCHER),
	FEA_MAP(DPM_GFXCLK),
	FEA_MAP(DPM_GFX_PACE),
	FEA_MAP(DPM_UCLK),
	FEA_MAP(DPM_SOCCLK),
	FEA_MAP(DPM_MP0CLK),
	FEA_MAP(DPM_LINK),
	FEA_MAP(DPM_DCEFCLK),
	FEA_MAP(MEM_VDDCI_SCALING),
	FEA_MAP(MEM_MVDD_SCALING),
	FEA_MAP(DS_GFXCLK),
	FEA_MAP(DS_SOCCLK),
	FEA_MAP(DS_LCLK),
	FEA_MAP(DS_DCEFCLK),
	FEA_MAP(DS_UCLK),
	FEA_MAP(GFX_ULV),
	FEA_MAP(FW_DSTATE),
	FEA_MAP(GFXOFF),
	FEA_MAP(BACO),
	FEA_MAP(VCN_PG),
	FEA_MAP(JPEG_PG),
	FEA_MAP(USB_PG),
	FEA_MAP(RSMU_SMN_CG),
	FEA_MAP(PPT),
	FEA_MAP(TDC),
	FEA_MAP(GFX_EDC),
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

अटल काष्ठा cmn2asic_mapping navi10_table_map[SMU_TABLE_COUNT] = अणु
	TAB_MAP(PPTABLE),
	TAB_MAP(WATERMARKS),
	TAB_MAP(AVFS),
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

अटल काष्ठा cmn2asic_mapping navi10_pwr_src_map[SMU_POWER_SOURCE_COUNT] = अणु
	PWR_MAP(AC),
	PWR_MAP(DC),
पूर्ण;

अटल काष्ठा cmn2asic_mapping navi10_workload_map[PP_SMC_POWER_PROखाता_COUNT] = अणु
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT,	WORKLOAD_PPLIB_DEFAULT_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_FULLSCREEN3D,		WORKLOAD_PPLIB_FULL_SCREEN_3D_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_POWERSAVING,		WORKLOAD_PPLIB_POWER_SAVING_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_VIDEO,		WORKLOAD_PPLIB_VIDEO_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_VR,			WORKLOAD_PPLIB_VR_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_COMPUTE,		WORKLOAD_PPLIB_COMPUTE_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_CUSTOM,		WORKLOAD_PPLIB_CUSTOM_BIT),
पूर्ण;

अटल bool is_asic_secure(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	bool is_secure = true;
	uपूर्णांक32_t mp0_fw_पूर्णांकf;

	mp0_fw_पूर्णांकf = RREG32_PCIE(MP0_Public |
				   (smnMP0_FW_INTF & 0xffffffff));

	अगर (!(mp0_fw_पूर्णांकf & (1 << 19)))
		is_secure = false;

	वापस is_secure;
पूर्ण

अटल पूर्णांक
navi10_get_allowed_feature_mask(काष्ठा smu_context *smu,
				  uपूर्णांक32_t *feature_mask, uपूर्णांक32_t num)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;

	अगर (num > 2)
		वापस -EINVAL;

	स_रखो(feature_mask, 0, माप(uपूर्णांक32_t) * num);

	*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_DPM_PREFETCHER_BIT)
				| FEATURE_MASK(FEATURE_DPM_MP0CLK_BIT)
				| FEATURE_MASK(FEATURE_RSMU_SMN_CG_BIT)
				| FEATURE_MASK(FEATURE_DS_SOCCLK_BIT)
				| FEATURE_MASK(FEATURE_PPT_BIT)
				| FEATURE_MASK(FEATURE_TDC_BIT)
				| FEATURE_MASK(FEATURE_GFX_EDC_BIT)
				| FEATURE_MASK(FEATURE_APCC_PLUS_BIT)
				| FEATURE_MASK(FEATURE_VR0HOT_BIT)
				| FEATURE_MASK(FEATURE_FAN_CONTROL_BIT)
				| FEATURE_MASK(FEATURE_THERMAL_BIT)
				| FEATURE_MASK(FEATURE_LED_DISPLAY_BIT)
				| FEATURE_MASK(FEATURE_DS_LCLK_BIT)
				| FEATURE_MASK(FEATURE_DS_DCEFCLK_BIT)
				| FEATURE_MASK(FEATURE_FW_DSTATE_BIT)
				| FEATURE_MASK(FEATURE_BACO_BIT)
				| FEATURE_MASK(FEATURE_GFX_SS_BIT)
				| FEATURE_MASK(FEATURE_APCC_DFLL_BIT)
				| FEATURE_MASK(FEATURE_FW_CTF_BIT)
				| FEATURE_MASK(FEATURE_OUT_OF_BAND_MONITOR_BIT);

	अगर (adev->pm.pp_feature & PP_SCLK_DPM_MASK)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_DPM_GFXCLK_BIT);

	अगर (adev->pm.pp_feature & PP_PCIE_DPM_MASK)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_DPM_LINK_BIT);

	अगर (adev->pm.pp_feature & PP_DCEFCLK_DPM_MASK)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_DPM_DCEFCLK_BIT);

	अगर (adev->pm.pp_feature & PP_ULV_MASK)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_GFX_ULV_BIT);

	अगर (adev->pm.pp_feature & PP_SCLK_DEEP_SLEEP_MASK)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_DS_GFXCLK_BIT);

	अगर (adev->pm.pp_feature & PP_GFXOFF_MASK)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_GFXOFF_BIT);

	अगर (smu->adev->pg_flags & AMD_PG_SUPPORT_MMHUB)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_MMHUB_PG_BIT);

	अगर (smu->adev->pg_flags & AMD_PG_SUPPORT_ATHUB)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_ATHUB_PG_BIT);

	अगर (smu->adev->pg_flags & AMD_PG_SUPPORT_VCN)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_VCN_PG_BIT);

	अगर (smu->adev->pg_flags & AMD_PG_SUPPORT_JPEG)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_JPEG_PG_BIT);

	अगर (smu->dc_controlled_by_gpio)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_ACDC_BIT);

	अगर (adev->pm.pp_feature & PP_SOCCLK_DPM_MASK)
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_DPM_SOCCLK_BIT);

	/* DPM UCLK enablement should be skipped क्रम navi10 A0 secure board */
	अगर (!(is_asic_secure(smu) &&
	     (adev->asic_type == CHIP_NAVI10) &&
	     (adev->rev_id == 0)) &&
	    (adev->pm.pp_feature & PP_MCLK_DPM_MASK))
		*(uपूर्णांक64_t *)feature_mask |= FEATURE_MASK(FEATURE_DPM_UCLK_BIT)
				| FEATURE_MASK(FEATURE_MEM_VDDCI_SCALING_BIT)
				| FEATURE_MASK(FEATURE_MEM_MVDD_SCALING_BIT);

	/* DS SOCCLK enablement should be skipped क्रम navi10 A0 secure board */
	अगर (is_asic_secure(smu) &&
	    (adev->asic_type == CHIP_NAVI10) &&
	    (adev->rev_id == 0))
		*(uपूर्णांक64_t *)feature_mask &=
				~FEATURE_MASK(FEATURE_DS_SOCCLK_BIT);

	वापस 0;
पूर्ण

अटल पूर्णांक navi10_check_घातerplay_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	काष्ठा smu_11_0_घातerplay_table *घातerplay_table =
		table_context->घातer_play_table;
	काष्ठा smu_baco_context *smu_baco = &smu->smu_baco;

	अगर (घातerplay_table->platक्रमm_caps & SMU_11_0_PP_PLATFORM_CAP_HARDWAREDC)
		smu->dc_controlled_by_gpio = true;

	अगर (घातerplay_table->platक्रमm_caps & SMU_11_0_PP_PLATFORM_CAP_BACO ||
	    घातerplay_table->platक्रमm_caps & SMU_11_0_PP_PLATFORM_CAP_MACO)
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

अटल पूर्णांक navi10_append_घातerplay_table(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	PPTable_t *smc_pptable = table_context->driver_pptable;
	काष्ठा atom_smc_dpm_info_v4_5 *smc_dpm_table;
	काष्ठा atom_smc_dpm_info_v4_7 *smc_dpm_table_v4_7;
	पूर्णांक index, ret;

	index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
					   smc_dpm_info);

	ret = amdgpu_atombios_get_data_table(adev, index, शून्य, शून्य, शून्य,
				      (uपूर्णांक8_t **)&smc_dpm_table);
	अगर (ret)
		वापस ret;

	dev_info(adev->dev, "smc_dpm_info table revision(format.content): %d.%d\n",
			smc_dpm_table->table_header.क्रमmat_revision,
			smc_dpm_table->table_header.content_revision);

	अगर (smc_dpm_table->table_header.क्रमmat_revision != 4) अणु
		dev_err(adev->dev, "smc_dpm_info table format revision is not 4!\n");
		वापस -EINVAL;
	पूर्ण

	चयन (smc_dpm_table->table_header.content_revision) अणु
	हाल 5: /* nv10 and nv14 */
		स_नकल(smc_pptable->I2cControllers, smc_dpm_table->I2cControllers,
			माप(*smc_dpm_table) - माप(smc_dpm_table->table_header));
		अवरोध;
	हाल 7: /* nv12 */
		ret = amdgpu_atombios_get_data_table(adev, index, शून्य, शून्य, शून्य,
					      (uपूर्णांक8_t **)&smc_dpm_table_v4_7);
		अगर (ret)
			वापस ret;
		स_नकल(smc_pptable->I2cControllers, smc_dpm_table_v4_7->I2cControllers,
			माप(*smc_dpm_table_v4_7) - माप(smc_dpm_table_v4_7->table_header));
		अवरोध;
	शेष:
		dev_err(smu->adev->dev, "smc_dpm_info with unsupported content revision %d!\n",
				smc_dpm_table->table_header.content_revision);
		वापस -EINVAL;
	पूर्ण

	अगर (adev->pm.pp_feature & PP_GFXOFF_MASK) अणु
		/* TODO: हटाओ it once SMU fw fix it */
		smc_pptable->DebugOverrides |= DPM_OVERRIDE_DISABLE_DFLL_PLL_SHUTDOWN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक navi10_store_घातerplay_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	काष्ठा smu_11_0_घातerplay_table *घातerplay_table =
		table_context->घातer_play_table;

	स_नकल(table_context->driver_pptable, &घातerplay_table->smc_pptable,
	       माप(PPTable_t));

	वापस 0;
पूर्ण

अटल पूर्णांक navi10_set_mp1_state(काष्ठा smu_context *smu,
				क्रमागत pp_mp1_state mp1_state)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t mp1_fw_flags;
	पूर्णांक ret = 0;

	ret = smu_cmn_set_mp1_state(smu, mp1_state);
	अगर (ret)
		वापस ret;

	अगर (mp1_state == PP_MP1_STATE_UNLOAD) अणु
		mp1_fw_flags = RREG32_PCIE(MP1_Public |
					   (smnMP1_FIRMWARE_FLAGS & 0xffffffff));

		mp1_fw_flags &= ~MP1_FIRMWARE_FLAGS__INTERRUPTS_ENABLED_MASK;

		WREG32_PCIE(MP1_Public |
			    (smnMP1_FIRMWARE_FLAGS & 0xffffffff), mp1_fw_flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक navi10_setup_pptable(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	ret = smu_v11_0_setup_pptable(smu);
	अगर (ret)
		वापस ret;

	ret = navi10_store_घातerplay_table(smu);
	अगर (ret)
		वापस ret;

	ret = navi10_append_घातerplay_table(smu);
	अगर (ret)
		वापस ret;

	ret = navi10_check_घातerplay_table(smu);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक navi10_tables_init(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा smu_table *tables = smu_table->tables;

	SMU_TABLE_INIT(tables, SMU_TABLE_PPTABLE, माप(PPTable_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_WATERMARKS, माप(Watermarks_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_SMU_METRICS, माप(SmuMetrics_NV1X_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_I2C_COMMANDS, माप(SwI2cRequest_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_OVERDRIVE, माप(OverDriveTable_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_PMSTATUSLOG, SMU11_TOOL_SIZE,
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_ACTIVITY_MONITOR_COEFF,
		       माप(DpmActivityMonitorCoeffInt_t), PAGE_SIZE,
		       AMDGPU_GEM_DOMAIN_VRAM);

	smu_table->metrics_table = kzalloc(माप(SmuMetrics_NV1X_t),
					   GFP_KERNEL);
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

अटल पूर्णांक navi10_get_legacy_smu_metrics_data(काष्ठा smu_context *smu,
					      MetricsMember_t member,
					      uपूर्णांक32_t *value)
अणु
	काष्ठा smu_table_context *smu_table= &smu->smu_table;
	SmuMetrics_legacy_t *metrics =
		(SmuMetrics_legacy_t *)smu_table->metrics_table;
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
		*value = metrics->CurrClock[PPCLK_VCLK];
		अवरोध;
	हाल METRICS_CURR_DCLK:
		*value = metrics->CurrClock[PPCLK_DCLK];
		अवरोध;
	हाल METRICS_CURR_DCEFCLK:
		*value = metrics->CurrClock[PPCLK_DCEFCLK];
		अवरोध;
	हाल METRICS_AVERAGE_GFXCLK:
		*value = metrics->AverageGfxclkFrequency;
		अवरोध;
	हाल METRICS_AVERAGE_SOCCLK:
		*value = metrics->AverageSocclkFrequency;
		अवरोध;
	हाल METRICS_AVERAGE_UCLK:
		*value = metrics->AverageUclkFrequency;
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

अटल पूर्णांक navi10_get_smu_metrics_data(काष्ठा smu_context *smu,
				       MetricsMember_t member,
				       uपूर्णांक32_t *value)
अणु
	काष्ठा smu_table_context *smu_table= &smu->smu_table;
	SmuMetrics_t *metrics =
		(SmuMetrics_t *)smu_table->metrics_table;
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
		*value = metrics->CurrClock[PPCLK_VCLK];
		अवरोध;
	हाल METRICS_CURR_DCLK:
		*value = metrics->CurrClock[PPCLK_DCLK];
		अवरोध;
	हाल METRICS_CURR_DCEFCLK:
		*value = metrics->CurrClock[PPCLK_DCEFCLK];
		अवरोध;
	हाल METRICS_AVERAGE_GFXCLK:
		अगर (metrics->AverageGfxActivity > SMU_11_0_GFX_BUSY_THRESHOLD)
			*value = metrics->AverageGfxclkFrequencyPreDs;
		अन्यथा
			*value = metrics->AverageGfxclkFrequencyPostDs;
		अवरोध;
	हाल METRICS_AVERAGE_SOCCLK:
		*value = metrics->AverageSocclkFrequency;
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

अटल पूर्णांक navi12_get_legacy_smu_metrics_data(काष्ठा smu_context *smu,
					      MetricsMember_t member,
					      uपूर्णांक32_t *value)
अणु
	काष्ठा smu_table_context *smu_table= &smu->smu_table;
	SmuMetrics_NV12_legacy_t *metrics =
		(SmuMetrics_NV12_legacy_t *)smu_table->metrics_table;
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
		*value = metrics->CurrClock[PPCLK_VCLK];
		अवरोध;
	हाल METRICS_CURR_DCLK:
		*value = metrics->CurrClock[PPCLK_DCLK];
		अवरोध;
	हाल METRICS_CURR_DCEFCLK:
		*value = metrics->CurrClock[PPCLK_DCEFCLK];
		अवरोध;
	हाल METRICS_AVERAGE_GFXCLK:
		*value = metrics->AverageGfxclkFrequency;
		अवरोध;
	हाल METRICS_AVERAGE_SOCCLK:
		*value = metrics->AverageSocclkFrequency;
		अवरोध;
	हाल METRICS_AVERAGE_UCLK:
		*value = metrics->AverageUclkFrequency;
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

अटल पूर्णांक navi12_get_smu_metrics_data(काष्ठा smu_context *smu,
				       MetricsMember_t member,
				       uपूर्णांक32_t *value)
अणु
	काष्ठा smu_table_context *smu_table= &smu->smu_table;
	SmuMetrics_NV12_t *metrics =
		(SmuMetrics_NV12_t *)smu_table->metrics_table;
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
		*value = metrics->CurrClock[PPCLK_VCLK];
		अवरोध;
	हाल METRICS_CURR_DCLK:
		*value = metrics->CurrClock[PPCLK_DCLK];
		अवरोध;
	हाल METRICS_CURR_DCEFCLK:
		*value = metrics->CurrClock[PPCLK_DCEFCLK];
		अवरोध;
	हाल METRICS_AVERAGE_GFXCLK:
		अगर (metrics->AverageGfxActivity > SMU_11_0_GFX_BUSY_THRESHOLD)
			*value = metrics->AverageGfxclkFrequencyPreDs;
		अन्यथा
			*value = metrics->AverageGfxclkFrequencyPostDs;
		अवरोध;
	हाल METRICS_AVERAGE_SOCCLK:
		*value = metrics->AverageSocclkFrequency;
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

अटल पूर्णांक navi1x_get_smu_metrics_data(काष्ठा smu_context *smu,
				       MetricsMember_t member,
				       uपूर्णांक32_t *value)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t smu_version;
	पूर्णांक ret = 0;

	ret = smu_cmn_get_smc_version(smu, शून्य, &smu_version);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to get smu version!\n");
		वापस ret;
	पूर्ण

	चयन (adev->asic_type) अणु
	हाल CHIP_NAVI12:
		अगर (smu_version > 0x00341C00)
			ret = navi12_get_smu_metrics_data(smu, member, value);
		अन्यथा
			ret = navi12_get_legacy_smu_metrics_data(smu, member, value);
		अवरोध;
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
	शेष:
		अगर (((adev->asic_type == CHIP_NAVI14) && smu_version > 0x00351F00) ||
		      ((adev->asic_type == CHIP_NAVI10) && smu_version > 0x002A3B00))
			ret = navi10_get_smu_metrics_data(smu, member, value);
		अन्यथा
			ret = navi10_get_legacy_smu_metrics_data(smu, member, value);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक navi10_allocate_dpm_context(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_dpm_context *smu_dpm = &smu->smu_dpm;

	smu_dpm->dpm_context = kzalloc(माप(काष्ठा smu_11_0_dpm_context),
				       GFP_KERNEL);
	अगर (!smu_dpm->dpm_context)
		वापस -ENOMEM;

	smu_dpm->dpm_context_size = माप(काष्ठा smu_11_0_dpm_context);

	वापस 0;
पूर्ण

अटल पूर्णांक navi10_init_smc_tables(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	ret = navi10_tables_init(smu);
	अगर (ret)
		वापस ret;

	ret = navi10_allocate_dpm_context(smu);
	अगर (ret)
		वापस ret;

	वापस smu_v11_0_init_smc_tables(smu);
पूर्ण

अटल पूर्णांक navi10_set_शेष_dpm_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_11_0_dpm_context *dpm_context = smu->smu_dpm.dpm_context;
	PPTable_t *driver_ppt = smu->smu_table.driver_pptable;
	काष्ठा smu_11_0_dpm_table *dpm_table;
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

	/* vclk dpm table setup */
	dpm_table = &dpm_context->dpm_tables.vclk_table;
	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_VCN_PG_BIT)) अणु
		ret = smu_v11_0_set_single_dpm_table(smu,
						     SMU_VCLK,
						     dpm_table);
		अगर (ret)
			वापस ret;
		dpm_table->is_fine_grained =
			!driver_ppt->DpmDescriptor[PPCLK_VCLK].SnapToDiscrete;
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.vclk / 100;
		dpm_table->dpm_levels[0].enabled = true;
		dpm_table->min = dpm_table->dpm_levels[0].value;
		dpm_table->max = dpm_table->dpm_levels[0].value;
	पूर्ण

	/* dclk dpm table setup */
	dpm_table = &dpm_context->dpm_tables.dclk_table;
	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_VCN_PG_BIT)) अणु
		ret = smu_v11_0_set_single_dpm_table(smu,
						     SMU_DCLK,
						     dpm_table);
		अगर (ret)
			वापस ret;
		dpm_table->is_fine_grained =
			!driver_ppt->DpmDescriptor[PPCLK_DCLK].SnapToDiscrete;
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.dclk / 100;
		dpm_table->dpm_levels[0].enabled = true;
		dpm_table->min = dpm_table->dpm_levels[0].value;
		dpm_table->max = dpm_table->dpm_levels[0].value;
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

अटल पूर्णांक navi10_dpm_set_vcn_enable(काष्ठा smu_context *smu, bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (enable) अणु
		/* vcn dpm on is a prerequisite क्रम vcn घातer gate messages */
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_VCN_PG_BIT)) अणु
			ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_PowerUpVcn, 1, शून्य);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_VCN_PG_BIT)) अणु
			ret = smu_cmn_send_smc_msg(smu, SMU_MSG_PowerDownVcn, शून्य);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक navi10_dpm_set_jpeg_enable(काष्ठा smu_context *smu, bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (enable) अणु
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_JPEG_PG_BIT)) अणु
			ret = smu_cmn_send_smc_msg(smu, SMU_MSG_PowerUpJpeg, शून्य);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_JPEG_PG_BIT)) अणु
			ret = smu_cmn_send_smc_msg(smu, SMU_MSG_PowerDownJpeg, शून्य);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक navi10_get_current_clk_freq_by_table(काष्ठा smu_context *smu,
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
	हाल PPCLK_VCLK:
		member_type = METRICS_CURR_VCLK;
		अवरोध;
	हाल PPCLK_DCLK:
		member_type = METRICS_CURR_DCLK;
		अवरोध;
	हाल PPCLK_DCEFCLK:
		member_type = METRICS_CURR_DCEFCLK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस navi1x_get_smu_metrics_data(smu,
					   member_type,
					   value);
पूर्ण

अटल bool navi10_is_support_fine_grained_dpm(काष्ठा smu_context *smu, क्रमागत smu_clk_type clk_type)
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

अटल अंतरभूत bool navi10_od_feature_is_supported(काष्ठा smu_11_0_overdrive_table *od_table, क्रमागत SMU_11_0_ODFEATURE_CAP cap)
अणु
	वापस od_table->cap[cap];
पूर्ण

अटल व्योम navi10_od_setting_get_range(काष्ठा smu_11_0_overdrive_table *od_table,
					क्रमागत SMU_11_0_ODSETTING_ID setting,
					uपूर्णांक32_t *min, uपूर्णांक32_t *max)
अणु
	अगर (min)
		*min = od_table->min[setting];
	अगर (max)
		*max = od_table->max[setting];
पूर्ण

अटल पूर्णांक navi10_prपूर्णांक_clk_levels(काष्ठा smu_context *smu,
			क्रमागत smu_clk_type clk_type, अक्षर *buf)
अणु
	uपूर्णांक16_t *curve_settings;
	पूर्णांक i, size = 0, ret = 0;
	uपूर्णांक32_t cur_value = 0, value = 0, count = 0;
	uपूर्णांक32_t freq_values[3] = अणु0पूर्ण;
	uपूर्णांक32_t mark_index = 0;
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	uपूर्णांक32_t gen_speed, lane_width;
	काष्ठा smu_dpm_context *smu_dpm = &smu->smu_dpm;
	काष्ठा smu_11_0_dpm_context *dpm_context = smu_dpm->dpm_context;
	PPTable_t *pptable = (PPTable_t *)table_context->driver_pptable;
	OverDriveTable_t *od_table =
		(OverDriveTable_t *)table_context->overdrive_table;
	काष्ठा smu_11_0_overdrive_table *od_settings = smu->od_settings;
	uपूर्णांक32_t min_value, max_value;

	चयन (clk_type) अणु
	हाल SMU_GFXCLK:
	हाल SMU_SCLK:
	हाल SMU_SOCCLK:
	हाल SMU_MCLK:
	हाल SMU_UCLK:
	हाल SMU_FCLK:
	हाल SMU_DCEFCLK:
		ret = navi10_get_current_clk_freq_by_table(smu, clk_type, &cur_value);
		अगर (ret)
			वापस size;

		ret = smu_v11_0_get_dpm_level_count(smu, clk_type, &count);
		अगर (ret)
			वापस size;

		अगर (!navi10_is_support_fine_grained_dpm(smu, clk_type)) अणु
			क्रम (i = 0; i < count; i++) अणु
				ret = smu_v11_0_get_dpm_freq_by_index(smu, clk_type, i, &value);
				अगर (ret)
					वापस size;

				size += प्र_लिखो(buf + size, "%d: %uMhz %s\n", i, value,
						cur_value == value ? "*" : "");
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = smu_v11_0_get_dpm_freq_by_index(smu, clk_type, 0, &freq_values[0]);
			अगर (ret)
				वापस size;
			ret = smu_v11_0_get_dpm_freq_by_index(smu, clk_type, count - 1, &freq_values[2]);
			अगर (ret)
				वापस size;

			freq_values[1] = cur_value;
			mark_index = cur_value == freq_values[0] ? 0 :
				     cur_value == freq_values[2] ? 2 : 1;
			अगर (mark_index != 1)
				freq_values[1] = (freq_values[0] + freq_values[2]) / 2;

			क्रम (i = 0; i < 3; i++) अणु
				size += प्र_लिखो(buf + size, "%d: %uMhz %s\n", i, freq_values[i],
						i == mark_index ? "*" : "");
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
		अगर (!navi10_od_feature_is_supported(od_settings, SMU_11_0_ODCAP_GFXCLK_LIMITS))
			अवरोध;
		size += प्र_लिखो(buf + size, "OD_SCLK:\n");
		size += प्र_लिखो(buf + size, "0: %uMhz\n1: %uMhz\n", od_table->GfxclkFmin, od_table->GfxclkFmax);
		अवरोध;
	हाल SMU_OD_MCLK:
		अगर (!smu->od_enabled || !od_table || !od_settings)
			अवरोध;
		अगर (!navi10_od_feature_is_supported(od_settings, SMU_11_0_ODCAP_UCLK_MAX))
			अवरोध;
		size += प्र_लिखो(buf + size, "OD_MCLK:\n");
		size += प्र_लिखो(buf + size, "1: %uMHz\n", od_table->UclkFmax);
		अवरोध;
	हाल SMU_OD_VDDC_CURVE:
		अगर (!smu->od_enabled || !od_table || !od_settings)
			अवरोध;
		अगर (!navi10_od_feature_is_supported(od_settings, SMU_11_0_ODCAP_GFXCLK_CURVE))
			अवरोध;
		size += प्र_लिखो(buf + size, "OD_VDDC_CURVE:\n");
		क्रम (i = 0; i < 3; i++) अणु
			चयन (i) अणु
			हाल 0:
				curve_settings = &od_table->GfxclkFreq1;
				अवरोध;
			हाल 1:
				curve_settings = &od_table->GfxclkFreq2;
				अवरोध;
			हाल 2:
				curve_settings = &od_table->GfxclkFreq3;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			size += प्र_लिखो(buf + size, "%d: %uMHz %umV\n", i, curve_settings[0], curve_settings[1] / NAVI10_VOLTAGE_SCALE);
		पूर्ण
		अवरोध;
	हाल SMU_OD_RANGE:
		अगर (!smu->od_enabled || !od_table || !od_settings)
			अवरोध;
		size = प्र_लिखो(buf, "%s:\n", "OD_RANGE");

		अगर (navi10_od_feature_is_supported(od_settings, SMU_11_0_ODCAP_GFXCLK_LIMITS)) अणु
			navi10_od_setting_get_range(od_settings, SMU_11_0_ODSETTING_GFXCLKFMIN,
						    &min_value, शून्य);
			navi10_od_setting_get_range(od_settings, SMU_11_0_ODSETTING_GFXCLKFMAX,
						    शून्य, &max_value);
			size += प्र_लिखो(buf + size, "SCLK: %7uMhz %10uMhz\n",
					min_value, max_value);
		पूर्ण

		अगर (navi10_od_feature_is_supported(od_settings, SMU_11_0_ODCAP_UCLK_MAX)) अणु
			navi10_od_setting_get_range(od_settings, SMU_11_0_ODSETTING_UCLKFMAX,
						    &min_value, &max_value);
			size += प्र_लिखो(buf + size, "MCLK: %7uMhz %10uMhz\n",
					min_value, max_value);
		पूर्ण

		अगर (navi10_od_feature_is_supported(od_settings, SMU_11_0_ODCAP_GFXCLK_CURVE)) अणु
			navi10_od_setting_get_range(od_settings, SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P1,
						    &min_value, &max_value);
			size += प्र_लिखो(buf + size, "VDDC_CURVE_SCLK[0]: %7uMhz %10uMhz\n",
					min_value, max_value);
			navi10_od_setting_get_range(od_settings, SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P1,
						    &min_value, &max_value);
			size += प्र_लिखो(buf + size, "VDDC_CURVE_VOLT[0]: %7dmV %11dmV\n",
					min_value, max_value);
			navi10_od_setting_get_range(od_settings, SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P2,
						    &min_value, &max_value);
			size += प्र_लिखो(buf + size, "VDDC_CURVE_SCLK[1]: %7uMhz %10uMhz\n",
					min_value, max_value);
			navi10_od_setting_get_range(od_settings, SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P2,
						    &min_value, &max_value);
			size += प्र_लिखो(buf + size, "VDDC_CURVE_VOLT[1]: %7dmV %11dmV\n",
					min_value, max_value);
			navi10_od_setting_get_range(od_settings, SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P3,
						    &min_value, &max_value);
			size += प्र_लिखो(buf + size, "VDDC_CURVE_SCLK[2]: %7uMhz %10uMhz\n",
					min_value, max_value);
			navi10_od_setting_get_range(od_settings, SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P3,
						    &min_value, &max_value);
			size += प्र_लिखो(buf + size, "VDDC_CURVE_VOLT[2]: %7dmV %11dmV\n",
					min_value, max_value);
		पूर्ण

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक navi10_क्रमce_clk_levels(काष्ठा smu_context *smu,
				   क्रमागत smu_clk_type clk_type, uपूर्णांक32_t mask)
अणु

	पूर्णांक ret = 0, size = 0;
	uपूर्णांक32_t soft_min_level = 0, soft_max_level = 0, min_freq = 0, max_freq = 0;

	soft_min_level = mask ? (ffs(mask) - 1) : 0;
	soft_max_level = mask ? (fls(mask) - 1) : 0;

	चयन (clk_type) अणु
	हाल SMU_GFXCLK:
	हाल SMU_SCLK:
	हाल SMU_SOCCLK:
	हाल SMU_MCLK:
	हाल SMU_UCLK:
	हाल SMU_FCLK:
		/* There is only 2 levels क्रम fine grained DPM */
		अगर (navi10_is_support_fine_grained_dpm(smu, clk_type)) अणु
			soft_max_level = (soft_max_level >= 1 ? 1 : 0);
			soft_min_level = (soft_min_level >= 1 ? 1 : 0);
		पूर्ण

		ret = smu_v11_0_get_dpm_freq_by_index(smu, clk_type, soft_min_level, &min_freq);
		अगर (ret)
			वापस size;

		ret = smu_v11_0_get_dpm_freq_by_index(smu, clk_type, soft_max_level, &max_freq);
		अगर (ret)
			वापस size;

		ret = smu_v11_0_set_soft_freq_limited_range(smu, clk_type, min_freq, max_freq);
		अगर (ret)
			वापस size;
		अवरोध;
	हाल SMU_DCEFCLK:
		dev_info(smu->adev->dev,"Setting DCEFCLK min/max dpm level is not supported!\n");
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक navi10_populate_umd_state_clk(काष्ठा smu_context *smu)
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
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t sclk_freq;

	pstate_table->gfxclk_pstate.min = gfx_table->min;
	चयन (adev->asic_type) अणु
	हाल CHIP_NAVI10:
		चयन (adev->pdev->revision) अणु
		हाल 0xf0: /* XTX */
		हाल 0xc0:
			sclk_freq = NAVI10_PEAK_SCLK_XTX;
			अवरोध;
		हाल 0xf1: /* XT */
		हाल 0xc1:
			sclk_freq = NAVI10_PEAK_SCLK_XT;
			अवरोध;
		शेष: /* XL */
			sclk_freq = NAVI10_PEAK_SCLK_XL;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CHIP_NAVI14:
		चयन (adev->pdev->revision) अणु
		हाल 0xc7: /* XT */
		हाल 0xf4:
			sclk_freq = NAVI14_UMD_PSTATE_PEAK_XT_GFXCLK;
			अवरोध;
		हाल 0xc1: /* XTM */
		हाल 0xf2:
			sclk_freq = NAVI14_UMD_PSTATE_PEAK_XTM_GFXCLK;
			अवरोध;
		हाल 0xc3: /* XLM */
		हाल 0xf3:
			sclk_freq = NAVI14_UMD_PSTATE_PEAK_XLM_GFXCLK;
			अवरोध;
		हाल 0xc5: /* XTX */
		हाल 0xf6:
			sclk_freq = NAVI14_UMD_PSTATE_PEAK_XLM_GFXCLK;
			अवरोध;
		शेष: /* XL */
			sclk_freq = NAVI14_UMD_PSTATE_PEAK_XL_GFXCLK;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CHIP_NAVI12:
		sclk_freq = NAVI12_UMD_PSTATE_PEAK_GFXCLK;
		अवरोध;
	शेष:
		sclk_freq = gfx_table->dpm_levels[gfx_table->count - 1].value;
		अवरोध;
	पूर्ण
	pstate_table->gfxclk_pstate.peak = sclk_freq;

	pstate_table->uclk_pstate.min = mem_table->min;
	pstate_table->uclk_pstate.peak = mem_table->max;

	pstate_table->socclk_pstate.min = soc_table->min;
	pstate_table->socclk_pstate.peak = soc_table->max;

	अगर (gfx_table->max > NAVI10_UMD_PSTATE_PROFILING_GFXCLK &&
	    mem_table->max > NAVI10_UMD_PSTATE_PROFILING_MEMCLK &&
	    soc_table->max > NAVI10_UMD_PSTATE_PROFILING_SOCCLK) अणु
		pstate_table->gfxclk_pstate.standard =
			NAVI10_UMD_PSTATE_PROFILING_GFXCLK;
		pstate_table->uclk_pstate.standard =
			NAVI10_UMD_PSTATE_PROFILING_MEMCLK;
		pstate_table->socclk_pstate.standard =
			NAVI10_UMD_PSTATE_PROFILING_SOCCLK;
	पूर्ण अन्यथा अणु
		pstate_table->gfxclk_pstate.standard =
			pstate_table->gfxclk_pstate.min;
		pstate_table->uclk_pstate.standard =
			pstate_table->uclk_pstate.min;
		pstate_table->socclk_pstate.standard =
			pstate_table->socclk_pstate.min;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक navi10_get_घड़ी_by_type_with_latency(काष्ठा smu_context *smu,
						 क्रमागत smu_clk_type clk_type,
						 काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	पूर्णांक ret = 0, i = 0;
	uपूर्णांक32_t level_count = 0, freq = 0;

	चयन (clk_type) अणु
	हाल SMU_GFXCLK:
	हाल SMU_DCEFCLK:
	हाल SMU_SOCCLK:
	हाल SMU_MCLK:
	हाल SMU_UCLK:
		ret = smu_v11_0_get_dpm_level_count(smu, clk_type, &level_count);
		अगर (ret)
			वापस ret;

		level_count = min(level_count, (uपूर्णांक32_t)MAX_NUM_CLOCKS);
		घड़ीs->num_levels = level_count;

		क्रम (i = 0; i < level_count; i++) अणु
			ret = smu_v11_0_get_dpm_freq_by_index(smu, clk_type, i, &freq);
			अगर (ret)
				वापस ret;

			घड़ीs->data[i].घड़ीs_in_khz = freq * 1000;
			घड़ीs->data[i].latency_in_us = 0;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक navi10_pre_display_config_changed(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t max_freq = 0;

	ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_NumOfDisplays, 0, शून्य);
	अगर (ret)
		वापस ret;

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

अटल पूर्णांक navi10_display_config_changed(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	अगर ((smu->watermarks_biपंचांगap & WATERMARKS_EXIST) &&
	    smu_cmn_feature_is_supported(smu, SMU_FEATURE_DPM_DCEFCLK_BIT) &&
	    smu_cmn_feature_is_supported(smu, SMU_FEATURE_DPM_SOCCLK_BIT)) अणु
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_NumOfDisplays,
						  smu->display_config->num_display,
						  शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool navi10_is_dpm_running(काष्ठा smu_context *smu)
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

अटल पूर्णांक navi10_get_fan_speed_percent(काष्ठा smu_context *smu,
					uपूर्णांक32_t *speed)
अणु
	पूर्णांक ret;
	u32 rpm;

	अगर (!speed)
		वापस -EINVAL;

	चयन (smu_v11_0_get_fan_control_mode(smu)) अणु
	हाल AMD_FAN_CTRL_AUTO:
		ret = navi1x_get_smu_metrics_data(smu,
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

अटल पूर्णांक navi10_get_fan_parameters(काष्ठा smu_context *smu)
अणु
	PPTable_t *pptable = smu->smu_table.driver_pptable;

	smu->fan_max_rpm = pptable->FanMaximumRpm;

	वापस 0;
पूर्ण

अटल पूर्णांक navi10_get_घातer_profile_mode(काष्ठा smu_context *smu, अक्षर *buf)
अणु
	DpmActivityMonitorCoeffInt_t activity_monitor;
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
					  (व्योम *)(&activity_monitor), false);
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
			activity_monitor.Gfx_FPS,
			activity_monitor.Gfx_MinFreqStep,
			activity_monitor.Gfx_MinActiveFreqType,
			activity_monitor.Gfx_MinActiveFreq,
			activity_monitor.Gfx_BoosterFreqType,
			activity_monitor.Gfx_BoosterFreq,
			activity_monitor.Gfx_PD_Data_limit_c,
			activity_monitor.Gfx_PD_Data_error_coeff,
			activity_monitor.Gfx_PD_Data_error_rate_coeff);

		size += प्र_लिखो(buf + size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d %7d\n",
			" ",
			1,
			"SOCCLK",
			activity_monitor.Soc_FPS,
			activity_monitor.Soc_MinFreqStep,
			activity_monitor.Soc_MinActiveFreqType,
			activity_monitor.Soc_MinActiveFreq,
			activity_monitor.Soc_BoosterFreqType,
			activity_monitor.Soc_BoosterFreq,
			activity_monitor.Soc_PD_Data_limit_c,
			activity_monitor.Soc_PD_Data_error_coeff,
			activity_monitor.Soc_PD_Data_error_rate_coeff);

		size += प्र_लिखो(buf + size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d %7d\n",
			" ",
			2,
			"MEMLK",
			activity_monitor.Mem_FPS,
			activity_monitor.Mem_MinFreqStep,
			activity_monitor.Mem_MinActiveFreqType,
			activity_monitor.Mem_MinActiveFreq,
			activity_monitor.Mem_BoosterFreqType,
			activity_monitor.Mem_BoosterFreq,
			activity_monitor.Mem_PD_Data_limit_c,
			activity_monitor.Mem_PD_Data_error_coeff,
			activity_monitor.Mem_PD_Data_error_rate_coeff);
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक navi10_set_घातer_profile_mode(काष्ठा smu_context *smu, दीर्घ *input, uपूर्णांक32_t size)
अणु
	DpmActivityMonitorCoeffInt_t activity_monitor;
	पूर्णांक workload_type, ret = 0;

	smu->घातer_profile_mode = input[size];

	अगर (smu->घातer_profile_mode > PP_SMC_POWER_PROखाता_CUSTOM) अणु
		dev_err(smu->adev->dev, "Invalid power profile mode %d\n", smu->घातer_profile_mode);
		वापस -EINVAL;
	पूर्ण

	अगर (smu->घातer_profile_mode == PP_SMC_POWER_PROखाता_CUSTOM) अणु

		ret = smu_cmn_update_table(smu,
				       SMU_TABLE_ACTIVITY_MONITOR_COEFF, WORKLOAD_PPLIB_CUSTOM_BIT,
				       (व्योम *)(&activity_monitor), false);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "[%s] Failed to get activity monitor!", __func__);
			वापस ret;
		पूर्ण

		चयन (input[0]) अणु
		हाल 0: /* Gfxclk */
			activity_monitor.Gfx_FPS = input[1];
			activity_monitor.Gfx_MinFreqStep = input[2];
			activity_monitor.Gfx_MinActiveFreqType = input[3];
			activity_monitor.Gfx_MinActiveFreq = input[4];
			activity_monitor.Gfx_BoosterFreqType = input[5];
			activity_monitor.Gfx_BoosterFreq = input[6];
			activity_monitor.Gfx_PD_Data_limit_c = input[7];
			activity_monitor.Gfx_PD_Data_error_coeff = input[8];
			activity_monitor.Gfx_PD_Data_error_rate_coeff = input[9];
			अवरोध;
		हाल 1: /* Socclk */
			activity_monitor.Soc_FPS = input[1];
			activity_monitor.Soc_MinFreqStep = input[2];
			activity_monitor.Soc_MinActiveFreqType = input[3];
			activity_monitor.Soc_MinActiveFreq = input[4];
			activity_monitor.Soc_BoosterFreqType = input[5];
			activity_monitor.Soc_BoosterFreq = input[6];
			activity_monitor.Soc_PD_Data_limit_c = input[7];
			activity_monitor.Soc_PD_Data_error_coeff = input[8];
			activity_monitor.Soc_PD_Data_error_rate_coeff = input[9];
			अवरोध;
		हाल 2: /* Memlk */
			activity_monitor.Mem_FPS = input[1];
			activity_monitor.Mem_MinFreqStep = input[2];
			activity_monitor.Mem_MinActiveFreqType = input[3];
			activity_monitor.Mem_MinActiveFreq = input[4];
			activity_monitor.Mem_BoosterFreqType = input[5];
			activity_monitor.Mem_BoosterFreq = input[6];
			activity_monitor.Mem_PD_Data_limit_c = input[7];
			activity_monitor.Mem_PD_Data_error_coeff = input[8];
			activity_monitor.Mem_PD_Data_error_rate_coeff = input[9];
			अवरोध;
		पूर्ण

		ret = smu_cmn_update_table(smu,
				       SMU_TABLE_ACTIVITY_MONITOR_COEFF, WORKLOAD_PPLIB_CUSTOM_BIT,
				       (व्योम *)(&activity_monitor), true);
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

अटल पूर्णांक navi10_notअगरy_smc_display_config(काष्ठा smu_context *smu)
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

अटल पूर्णांक navi10_set_watermarks_table(काष्ठा smu_context *smu,
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

	/* pass data to smu controller */
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

अटल पूर्णांक navi10_पढ़ो_sensor(काष्ठा smu_context *smu,
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
		ret = navi1x_get_smu_metrics_data(smu,
						  METRICS_AVERAGE_MEMACTIVITY,
						  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GPU_LOAD:
		ret = navi1x_get_smu_metrics_data(smu,
						  METRICS_AVERAGE_GFXACTIVITY,
						  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GPU_POWER:
		ret = navi1x_get_smu_metrics_data(smu,
						  METRICS_AVERAGE_SOCKETPOWER,
						  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_HOTSPOT_TEMP:
		ret = navi1x_get_smu_metrics_data(smu,
						  METRICS_TEMPERATURE_HOTSPOT,
						  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_EDGE_TEMP:
		ret = navi1x_get_smu_metrics_data(smu,
						  METRICS_TEMPERATURE_EDGE,
						  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_MEM_TEMP:
		ret = navi1x_get_smu_metrics_data(smu,
						  METRICS_TEMPERATURE_MEM,
						  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GFX_MCLK:
		ret = navi10_get_current_clk_freq_by_table(smu, SMU_UCLK, (uपूर्णांक32_t *)data);
		*(uपूर्णांक32_t *)data *= 100;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GFX_SCLK:
		ret = navi1x_get_smu_metrics_data(smu, METRICS_AVERAGE_GFXCLK, (uपूर्णांक32_t *)data);
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

अटल पूर्णांक navi10_get_uclk_dpm_states(काष्ठा smu_context *smu, uपूर्णांक32_t *घड़ीs_in_khz, uपूर्णांक32_t *num_states)
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

अटल पूर्णांक navi10_get_thermal_temperature_range(काष्ठा smu_context *smu,
						काष्ठा smu_temperature_range *range)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	काष्ठा smu_11_0_घातerplay_table *घातerplay_table =
				table_context->घातer_play_table;
	PPTable_t *pptable = smu->smu_table.driver_pptable;

	अगर (!range)
		वापस -EINVAL;

	स_नकल(range, &smu11_thermal_policy[0], माप(काष्ठा smu_temperature_range));

	range->max = pptable->TedgeLimit *
		SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
	range->edge_emergency_max = (pptable->TedgeLimit + CTF_OFFSET_EDGE) *
		SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
	range->hotspot_crit_max = pptable->ThotspotLimit *
		SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
	range->hotspot_emergency_max = (pptable->ThotspotLimit + CTF_OFFSET_HOTSPOT) *
		SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
	range->mem_crit_max = pptable->TmemLimit *
		SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
	range->mem_emergency_max = (pptable->TmemLimit + CTF_OFFSET_MEM)*
		SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
	range->software_shutकरोwn_temp = घातerplay_table->software_shutकरोwn_temp;

	वापस 0;
पूर्ण

अटल पूर्णांक navi10_display_disable_memory_घड़ी_चयन(काष्ठा smu_context *smu,
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

अटल पूर्णांक navi10_get_घातer_limit(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_11_0_घातerplay_table *घातerplay_table =
		(काष्ठा smu_11_0_घातerplay_table *)smu->smu_table.घातer_play_table;
	काष्ठा smu_11_0_overdrive_table *od_settings = smu->od_settings;
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

	अगर (smu->od_enabled &&
	    navi10_od_feature_is_supported(od_settings, SMU_11_0_ODCAP_POWER_LIMIT)) अणु
		od_percent = le32_to_cpu(घातerplay_table->overdrive_table.max[SMU_11_0_ODSETTING_POWERPERCENTAGE]);

		dev_dbg(smu->adev->dev, "ODSETTING_POWERPERCENTAGE: %d (default: %d)\n", od_percent, घातer_limit);

		घातer_limit *= (100 + od_percent);
		घातer_limit /= 100;
	पूर्ण
	smu->max_घातer_limit = घातer_limit;

	वापस 0;
पूर्ण

अटल पूर्णांक navi10_update_pcie_parameters(काष्ठा smu_context *smu,
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
			((pptable->PcieGenSpeed[i] <= pcie_gen_cap) ? (pptable->PcieGenSpeed[i] << 8) :
				(pcie_gen_cap << 8)) | ((pptable->PcieLaneCount[i] <= pcie_width_cap) ?
					pptable->PcieLaneCount[i] : pcie_width_cap);
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

अटल अंतरभूत व्योम navi10_dump_od_table(काष्ठा smu_context *smu,
					OverDriveTable_t *od_table)
अणु
	dev_dbg(smu->adev->dev, "OD: Gfxclk: (%d, %d)\n", od_table->GfxclkFmin, od_table->GfxclkFmax);
	dev_dbg(smu->adev->dev, "OD: Gfx1: (%d, %d)\n", od_table->GfxclkFreq1, od_table->GfxclkVolt1);
	dev_dbg(smu->adev->dev, "OD: Gfx2: (%d, %d)\n", od_table->GfxclkFreq2, od_table->GfxclkVolt2);
	dev_dbg(smu->adev->dev, "OD: Gfx3: (%d, %d)\n", od_table->GfxclkFreq3, od_table->GfxclkVolt3);
	dev_dbg(smu->adev->dev, "OD: UclkFmax: %d\n", od_table->UclkFmax);
	dev_dbg(smu->adev->dev, "OD: OverDrivePct: %d\n", od_table->OverDrivePct);
पूर्ण

अटल पूर्णांक navi10_od_setting_check_range(काष्ठा smu_context *smu,
					 काष्ठा smu_11_0_overdrive_table *od_table,
					 क्रमागत SMU_11_0_ODSETTING_ID setting,
					 uपूर्णांक32_t value)
अणु
	अगर (value < od_table->min[setting]) अणु
		dev_warn(smu->adev->dev, "OD setting (%d, %d) is less than the minimum allowed (%d)\n", setting, value, od_table->min[setting]);
		वापस -EINVAL;
	पूर्ण
	अगर (value > od_table->max[setting]) अणु
		dev_warn(smu->adev->dev, "OD setting (%d, %d) is greater than the maximum allowed (%d)\n", setting, value, od_table->max[setting]);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक navi10_overdrive_get_gfx_clk_base_voltage(काष्ठा smu_context *smu,
						     uपूर्णांक16_t *voltage,
						     uपूर्णांक32_t freq)
अणु
	uपूर्णांक32_t param = (freq & 0xFFFF) | (PPCLK_GFXCLK << 16);
	uपूर्णांक32_t value = 0;
	पूर्णांक ret;

	ret = smu_cmn_send_smc_msg_with_param(smu,
					  SMU_MSG_GetVoltageByDpm,
					  param,
					  &value);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "[GetBaseVoltage] failed to get GFXCLK AVFS voltage from SMU!");
		वापस ret;
	पूर्ण

	*voltage = (uपूर्णांक16_t)value;

	वापस 0;
पूर्ण

अटल bool navi10_is_baco_supported(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t val;

	अगर (amdgpu_sriov_vf(adev) || (!smu_v11_0_baco_is_support(smu)))
		वापस false;

	val = RREG32_SOC15(NBIO, 0, mmRCC_BIF_STRAP0);
	वापस (val & RCC_BIF_STRAP0__STRAP_PX_CAPABLE_MASK) ? true : false;
पूर्ण

अटल पूर्णांक navi10_set_शेष_od_settings(काष्ठा smu_context *smu)
अणु
	OverDriveTable_t *od_table =
		(OverDriveTable_t *)smu->smu_table.overdrive_table;
	OverDriveTable_t *boot_od_table =
		(OverDriveTable_t *)smu->smu_table.boot_overdrive_table;
	पूर्णांक ret = 0;

	ret = smu_cmn_update_table(smu, SMU_TABLE_OVERDRIVE, 0, (व्योम *)od_table, false);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "Failed to get overdrive table!\n");
		वापस ret;
	पूर्ण

	अगर (!od_table->GfxclkVolt1) अणु
		ret = navi10_overdrive_get_gfx_clk_base_voltage(smu,
								&od_table->GfxclkVolt1,
								od_table->GfxclkFreq1);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!od_table->GfxclkVolt2) अणु
		ret = navi10_overdrive_get_gfx_clk_base_voltage(smu,
								&od_table->GfxclkVolt2,
								od_table->GfxclkFreq2);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!od_table->GfxclkVolt3) अणु
		ret = navi10_overdrive_get_gfx_clk_base_voltage(smu,
								&od_table->GfxclkVolt3,
								od_table->GfxclkFreq3);
		अगर (ret)
			वापस ret;
	पूर्ण

	स_नकल(boot_od_table, od_table, माप(OverDriveTable_t));

	navi10_dump_od_table(smu, od_table);

	वापस 0;
पूर्ण

अटल पूर्णांक navi10_od_edit_dpm_table(काष्ठा smu_context *smu, क्रमागत PP_OD_DPM_TABLE_COMMAND type, दीर्घ input[], uपूर्णांक32_t size) अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	OverDriveTable_t *od_table;
	काष्ठा smu_11_0_overdrive_table *od_settings;
	क्रमागत SMU_11_0_ODSETTING_ID freq_setting, voltage_setting;
	uपूर्णांक16_t *freq_ptr, *voltage_ptr;
	od_table = (OverDriveTable_t *)table_context->overdrive_table;

	अगर (!smu->od_enabled) अणु
		dev_warn(smu->adev->dev, "OverDrive is not enabled!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!smu->od_settings) अणु
		dev_err(smu->adev->dev, "OD board limits are not set!\n");
		वापस -ENOENT;
	पूर्ण

	od_settings = smu->od_settings;

	चयन (type) अणु
	हाल PP_OD_EDIT_SCLK_VDDC_TABLE:
		अगर (!navi10_od_feature_is_supported(od_settings, SMU_11_0_ODCAP_GFXCLK_LIMITS)) अणु
			dev_warn(smu->adev->dev, "GFXCLK_LIMITS not supported!\n");
			वापस -ENOTSUPP;
		पूर्ण
		अगर (!table_context->overdrive_table) अणु
			dev_err(smu->adev->dev, "Overdrive is not initialized\n");
			वापस -EINVAL;
		पूर्ण
		क्रम (i = 0; i < size; i += 2) अणु
			अगर (i + 2 > size) अणु
				dev_info(smu->adev->dev, "invalid number of input parameters %d\n", size);
				वापस -EINVAL;
			पूर्ण
			चयन (input[i]) अणु
			हाल 0:
				freq_setting = SMU_11_0_ODSETTING_GFXCLKFMIN;
				freq_ptr = &od_table->GfxclkFmin;
				अगर (input[i + 1] > od_table->GfxclkFmax) अणु
					dev_info(smu->adev->dev, "GfxclkFmin (%ld) must be <= GfxclkFmax (%u)!\n",
						input[i + 1],
						od_table->GfxclkFmin);
					वापस -EINVAL;
				पूर्ण
				अवरोध;
			हाल 1:
				freq_setting = SMU_11_0_ODSETTING_GFXCLKFMAX;
				freq_ptr = &od_table->GfxclkFmax;
				अगर (input[i + 1] < od_table->GfxclkFmin) अणु
					dev_info(smu->adev->dev, "GfxclkFmax (%ld) must be >= GfxclkFmin (%u)!\n",
						input[i + 1],
						od_table->GfxclkFmax);
					वापस -EINVAL;
				पूर्ण
				अवरोध;
			शेष:
				dev_info(smu->adev->dev, "Invalid SCLK_VDDC_TABLE index: %ld\n", input[i]);
				dev_info(smu->adev->dev, "Supported indices: [0:min,1:max]\n");
				वापस -EINVAL;
			पूर्ण
			ret = navi10_od_setting_check_range(smu, od_settings, freq_setting, input[i + 1]);
			अगर (ret)
				वापस ret;
			*freq_ptr = input[i + 1];
		पूर्ण
		अवरोध;
	हाल PP_OD_EDIT_MCLK_VDDC_TABLE:
		अगर (!navi10_od_feature_is_supported(od_settings, SMU_11_0_ODCAP_UCLK_MAX)) अणु
			dev_warn(smu->adev->dev, "UCLK_MAX not supported!\n");
			वापस -ENOTSUPP;
		पूर्ण
		अगर (size < 2) अणु
			dev_info(smu->adev->dev, "invalid number of parameters: %d\n", size);
			वापस -EINVAL;
		पूर्ण
		अगर (input[0] != 1) अणु
			dev_info(smu->adev->dev, "Invalid MCLK_VDDC_TABLE index: %ld\n", input[0]);
			dev_info(smu->adev->dev, "Supported indices: [1:max]\n");
			वापस -EINVAL;
		पूर्ण
		ret = navi10_od_setting_check_range(smu, od_settings, SMU_11_0_ODSETTING_UCLKFMAX, input[1]);
		अगर (ret)
			वापस ret;
		od_table->UclkFmax = input[1];
		अवरोध;
	हाल PP_OD_RESTORE_DEFAULT_TABLE:
		अगर (!(table_context->overdrive_table && table_context->boot_overdrive_table)) अणु
			dev_err(smu->adev->dev, "Overdrive table was not initialized!\n");
			वापस -EINVAL;
		पूर्ण
		स_नकल(table_context->overdrive_table, table_context->boot_overdrive_table, माप(OverDriveTable_t));
		अवरोध;
	हाल PP_OD_COMMIT_DPM_TABLE:
		navi10_dump_od_table(smu, od_table);
		ret = smu_cmn_update_table(smu, SMU_TABLE_OVERDRIVE, 0, (व्योम *)od_table, true);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Failed to import overdrive table!\n");
			वापस ret;
		पूर्ण
		अवरोध;
	हाल PP_OD_EDIT_VDDC_CURVE:
		अगर (!navi10_od_feature_is_supported(od_settings, SMU_11_0_ODCAP_GFXCLK_CURVE)) अणु
			dev_warn(smu->adev->dev, "GFXCLK_CURVE not supported!\n");
			वापस -ENOTSUPP;
		पूर्ण
		अगर (size < 3) अणु
			dev_info(smu->adev->dev, "invalid number of parameters: %d\n", size);
			वापस -EINVAL;
		पूर्ण
		अगर (!od_table) अणु
			dev_info(smu->adev->dev, "Overdrive is not initialized\n");
			वापस -EINVAL;
		पूर्ण

		चयन (input[0]) अणु
		हाल 0:
			freq_setting = SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P1;
			voltage_setting = SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P1;
			freq_ptr = &od_table->GfxclkFreq1;
			voltage_ptr = &od_table->GfxclkVolt1;
			अवरोध;
		हाल 1:
			freq_setting = SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P2;
			voltage_setting = SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P2;
			freq_ptr = &od_table->GfxclkFreq2;
			voltage_ptr = &od_table->GfxclkVolt2;
			अवरोध;
		हाल 2:
			freq_setting = SMU_11_0_ODSETTING_VDDGFXCURVEFREQ_P3;
			voltage_setting = SMU_11_0_ODSETTING_VDDGFXCURVEVOLTAGE_P3;
			freq_ptr = &od_table->GfxclkFreq3;
			voltage_ptr = &od_table->GfxclkVolt3;
			अवरोध;
		शेष:
			dev_info(smu->adev->dev, "Invalid VDDC_CURVE index: %ld\n", input[0]);
			dev_info(smu->adev->dev, "Supported indices: [0, 1, 2]\n");
			वापस -EINVAL;
		पूर्ण
		ret = navi10_od_setting_check_range(smu, od_settings, freq_setting, input[1]);
		अगर (ret)
			वापस ret;
		// Allow setting zero to disable the OverDrive VDDC curve
		अगर (input[2] != 0) अणु
			ret = navi10_od_setting_check_range(smu, od_settings, voltage_setting, input[2]);
			अगर (ret)
				वापस ret;
			*freq_ptr = input[1];
			*voltage_ptr = ((uपूर्णांक16_t)input[2]) * NAVI10_VOLTAGE_SCALE;
			dev_dbg(smu->adev->dev, "OD: set curve %ld: (%d, %d)\n", input[0], *freq_ptr, *voltage_ptr);
		पूर्ण अन्यथा अणु
			// If setting 0, disable all voltage curve settings
			od_table->GfxclkVolt1 = 0;
			od_table->GfxclkVolt2 = 0;
			od_table->GfxclkVolt3 = 0;
		पूर्ण
		navi10_dump_od_table(smu, od_table);
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक navi10_run_btc(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	ret = smu_cmn_send_smc_msg(smu, SMU_MSG_RunBtc, शून्य);
	अगर (ret)
		dev_err(smu->adev->dev, "RunBtc failed!\n");

	वापस ret;
पूर्ण

अटल bool navi10_need_umc_cdr_workaround(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;

	अगर (!smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_UCLK_BIT))
		वापस false;

	अगर (adev->asic_type == CHIP_NAVI10 ||
	    adev->asic_type == CHIP_NAVI14)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक navi10_umc_hybrid_cdr_workaround(काष्ठा smu_context *smu)
अणु
	uपूर्णांक32_t uclk_count, uclk_min, uclk_max;
	पूर्णांक ret = 0;

	/* This workaround can be applied only with uclk dpm enabled */
	अगर (!smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_UCLK_BIT))
		वापस 0;

	ret = smu_v11_0_get_dpm_level_count(smu, SMU_UCLK, &uclk_count);
	अगर (ret)
		वापस ret;

	ret = smu_v11_0_get_dpm_freq_by_index(smu, SMU_UCLK, (uपूर्णांक16_t)(uclk_count - 1), &uclk_max);
	अगर (ret)
		वापस ret;

	/*
	 * The NAVI10_UMC_HYBRID_CDR_WORKAROUND_UCLK_THRESHOLD is 750Mhz.
	 * This workaround is needed only when the max uclk frequency
	 * not greater than that.
	 */
	अगर (uclk_max > 0x2EE)
		वापस 0;

	ret = smu_v11_0_get_dpm_freq_by_index(smu, SMU_UCLK, (uपूर्णांक16_t)0, &uclk_min);
	अगर (ret)
		वापस ret;

	/* Force UCLK out of the highest DPM */
	ret = smu_v11_0_set_hard_freq_limited_range(smu, SMU_UCLK, 0, uclk_min);
	अगर (ret)
		वापस ret;

	/* Revert the UCLK Hardmax */
	ret = smu_v11_0_set_hard_freq_limited_range(smu, SMU_UCLK, 0, uclk_max);
	अगर (ret)
		वापस ret;

	/*
	 * In this हाल, SMU alपढ़ोy disabled dummy pstate during enablement
	 * of UCLK DPM, we have to re-enabled it.
	 */
	वापस smu_cmn_send_smc_msg(smu, SMU_MSG_DAL_ENABLE_DUMMY_PSTATE_CHANGE, शून्य);
पूर्ण

अटल पूर्णांक navi10_set_dummy_pstates_table_location(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा smu_table *dummy_पढ़ो_table =
				&smu_table->dummy_पढ़ो_1_table;
	अक्षर *dummy_table = dummy_पढ़ो_table->cpu_addr;
	पूर्णांक ret = 0;
	uपूर्णांक32_t i;

	क्रम (i = 0; i < 0x40000; i += 0x1000 * 2) अणु
		स_नकल(dummy_table, &NoDbiPrbs7[0], 0x1000);
		dummy_table += 0x1000;
		स_नकल(dummy_table, &DbiPrbs7[0], 0x1000);
		dummy_table += 0x1000;
	पूर्ण

	amdgpu_asic_flush_hdp(smu->adev, शून्य);

	ret = smu_cmn_send_smc_msg_with_param(smu,
					      SMU_MSG_SET_DRIVER_DUMMY_TABLE_DRAM_ADDR_HIGH,
					      upper_32_bits(dummy_पढ़ो_table->mc_address),
					      शून्य);
	अगर (ret)
		वापस ret;

	वापस smu_cmn_send_smc_msg_with_param(smu,
					       SMU_MSG_SET_DRIVER_DUMMY_TABLE_DRAM_ADDR_LOW,
					       lower_32_bits(dummy_पढ़ो_table->mc_address),
					       शून्य);
पूर्ण

अटल पूर्णांक navi10_run_umc_cdr_workaround(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक8_t umc_fw_greater_than_v136 = false;
	uपूर्णांक8_t umc_fw_disable_cdr = false;
	uपूर्णांक32_t pmfw_version;
	uपूर्णांक32_t param;
	पूर्णांक ret = 0;

	अगर (!navi10_need_umc_cdr_workaround(smu))
		वापस 0;

	ret = smu_cmn_get_smc_version(smu, शून्य, &pmfw_version);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to get smu version!\n");
		वापस ret;
	पूर्ण

	/*
	 * The messages below are only supported by Navi10 42.53.0 and later
	 * PMFWs and Navi14 53.29.0 and later PMFWs.
	 * - PPSMC_MSG_SetDriverDummyTableDramAddrHigh
	 * - PPSMC_MSG_SetDriverDummyTableDramAddrLow
	 * - PPSMC_MSG_GetUMCFWWA
	 */
	अगर (((adev->asic_type == CHIP_NAVI10) && (pmfw_version >= 0x2a3500)) ||
	    ((adev->asic_type == CHIP_NAVI14) && (pmfw_version >= 0x351D00))) अणु
		ret = smu_cmn_send_smc_msg_with_param(smu,
						      SMU_MSG_GET_UMC_FW_WA,
						      0,
						      &param);
		अगर (ret)
			वापस ret;

		/* First bit indicates अगर the UMC f/w is above v137 */
		umc_fw_greater_than_v136 = param & 0x1;

		/* Second bit indicates अगर hybrid-cdr is disabled */
		umc_fw_disable_cdr = param & 0x2;

		/* w/a only allowed अगर UMC f/w is <= 136 */
		अगर (umc_fw_greater_than_v136)
			वापस 0;

		अगर (umc_fw_disable_cdr) अणु
			अगर (adev->asic_type == CHIP_NAVI10)
				वापस navi10_umc_hybrid_cdr_workaround(smu);
		पूर्ण अन्यथा अणु
			वापस navi10_set_dummy_pstates_table_location(smu);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (adev->asic_type == CHIP_NAVI10)
			वापस navi10_umc_hybrid_cdr_workaround(smu);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार navi10_get_legacy_gpu_metrics(काष्ठा smu_context *smu,
					     व्योम **table)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा gpu_metrics_v1_1 *gpu_metrics =
		(काष्ठा gpu_metrics_v1_1 *)smu_table->gpu_metrics_table;
	SmuMetrics_legacy_t metrics;
	पूर्णांक ret = 0;

	mutex_lock(&smu->metrics_lock);

	ret = smu_cmn_get_metrics_table_locked(smu,
					       शून्य,
					       true);
	अगर (ret) अणु
		mutex_unlock(&smu->metrics_lock);
		वापस ret;
	पूर्ण

	स_नकल(&metrics, smu_table->metrics_table, माप(SmuMetrics_legacy_t));

	mutex_unlock(&smu->metrics_lock);

	smu_cmn_init_soft_gpu_metrics(gpu_metrics, 1, 1);

	gpu_metrics->temperature_edge = metrics.TemperatureEdge;
	gpu_metrics->temperature_hotspot = metrics.TemperatureHotspot;
	gpu_metrics->temperature_mem = metrics.TemperatureMem;
	gpu_metrics->temperature_vrgfx = metrics.TemperatureVrGfx;
	gpu_metrics->temperature_vrsoc = metrics.TemperatureVrSoc;
	gpu_metrics->temperature_vrmem = metrics.TemperatureVrMem0;

	gpu_metrics->average_gfx_activity = metrics.AverageGfxActivity;
	gpu_metrics->average_umc_activity = metrics.AverageUclkActivity;

	gpu_metrics->average_socket_घातer = metrics.AverageSocketPower;

	gpu_metrics->average_gfxclk_frequency = metrics.AverageGfxclkFrequency;
	gpu_metrics->average_socclk_frequency = metrics.AverageSocclkFrequency;
	gpu_metrics->average_uclk_frequency = metrics.AverageUclkFrequency;

	gpu_metrics->current_gfxclk = metrics.CurrClock[PPCLK_GFXCLK];
	gpu_metrics->current_socclk = metrics.CurrClock[PPCLK_SOCCLK];
	gpu_metrics->current_uclk = metrics.CurrClock[PPCLK_UCLK];
	gpu_metrics->current_vclk0 = metrics.CurrClock[PPCLK_VCLK];
	gpu_metrics->current_dclk0 = metrics.CurrClock[PPCLK_DCLK];

	gpu_metrics->throttle_status = metrics.ThrottlerStatus;

	gpu_metrics->current_fan_speed = metrics.CurrFanSpeed;

	gpu_metrics->pcie_link_width =
			smu_v11_0_get_current_pcie_link_width(smu);
	gpu_metrics->pcie_link_speed =
			smu_v11_0_get_current_pcie_link_speed(smu);

	gpu_metrics->प्रणाली_घड़ी_counter = kसमय_get_bootसमय_ns();

	*table = (व्योम *)gpu_metrics;

	वापस माप(काष्ठा gpu_metrics_v1_1);
पूर्ण

अटल sमाप_प्रकार navi10_get_gpu_metrics(काष्ठा smu_context *smu,
				      व्योम **table)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा gpu_metrics_v1_1 *gpu_metrics =
		(काष्ठा gpu_metrics_v1_1 *)smu_table->gpu_metrics_table;
	SmuMetrics_t metrics;
	पूर्णांक ret = 0;

	mutex_lock(&smu->metrics_lock);

	ret = smu_cmn_get_metrics_table_locked(smu,
					       शून्य,
					       true);
	अगर (ret) अणु
		mutex_unlock(&smu->metrics_lock);
		वापस ret;
	पूर्ण

	स_नकल(&metrics, smu_table->metrics_table, माप(SmuMetrics_t));

	mutex_unlock(&smu->metrics_lock);

	smu_cmn_init_soft_gpu_metrics(gpu_metrics, 1, 1);

	gpu_metrics->temperature_edge = metrics.TemperatureEdge;
	gpu_metrics->temperature_hotspot = metrics.TemperatureHotspot;
	gpu_metrics->temperature_mem = metrics.TemperatureMem;
	gpu_metrics->temperature_vrgfx = metrics.TemperatureVrGfx;
	gpu_metrics->temperature_vrsoc = metrics.TemperatureVrSoc;
	gpu_metrics->temperature_vrmem = metrics.TemperatureVrMem0;

	gpu_metrics->average_gfx_activity = metrics.AverageGfxActivity;
	gpu_metrics->average_umc_activity = metrics.AverageUclkActivity;

	gpu_metrics->average_socket_घातer = metrics.AverageSocketPower;

	अगर (metrics.AverageGfxActivity > SMU_11_0_GFX_BUSY_THRESHOLD)
		gpu_metrics->average_gfxclk_frequency = metrics.AverageGfxclkFrequencyPreDs;
	अन्यथा
		gpu_metrics->average_gfxclk_frequency = metrics.AverageGfxclkFrequencyPostDs;

	gpu_metrics->average_socclk_frequency = metrics.AverageSocclkFrequency;
	gpu_metrics->average_uclk_frequency = metrics.AverageUclkFrequencyPostDs;

	gpu_metrics->current_gfxclk = metrics.CurrClock[PPCLK_GFXCLK];
	gpu_metrics->current_socclk = metrics.CurrClock[PPCLK_SOCCLK];
	gpu_metrics->current_uclk = metrics.CurrClock[PPCLK_UCLK];
	gpu_metrics->current_vclk0 = metrics.CurrClock[PPCLK_VCLK];
	gpu_metrics->current_dclk0 = metrics.CurrClock[PPCLK_DCLK];

	gpu_metrics->throttle_status = metrics.ThrottlerStatus;

	gpu_metrics->current_fan_speed = metrics.CurrFanSpeed;

	gpu_metrics->pcie_link_width = metrics.PcieWidth;
	gpu_metrics->pcie_link_speed = link_speed[metrics.PcieRate];

	gpu_metrics->प्रणाली_घड़ी_counter = kसमय_get_bootसमय_ns();

	*table = (व्योम *)gpu_metrics;

	वापस माप(काष्ठा gpu_metrics_v1_1);
पूर्ण

अटल sमाप_प्रकार navi12_get_legacy_gpu_metrics(काष्ठा smu_context *smu,
					     व्योम **table)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा gpu_metrics_v1_1 *gpu_metrics =
		(काष्ठा gpu_metrics_v1_1 *)smu_table->gpu_metrics_table;
	SmuMetrics_NV12_legacy_t metrics;
	पूर्णांक ret = 0;

	mutex_lock(&smu->metrics_lock);

	ret = smu_cmn_get_metrics_table_locked(smu,
					       शून्य,
					       true);
	अगर (ret) अणु
		mutex_unlock(&smu->metrics_lock);
		वापस ret;
	पूर्ण

	स_नकल(&metrics, smu_table->metrics_table, माप(SmuMetrics_NV12_legacy_t));

	mutex_unlock(&smu->metrics_lock);

	smu_cmn_init_soft_gpu_metrics(gpu_metrics, 1, 1);

	gpu_metrics->temperature_edge = metrics.TemperatureEdge;
	gpu_metrics->temperature_hotspot = metrics.TemperatureHotspot;
	gpu_metrics->temperature_mem = metrics.TemperatureMem;
	gpu_metrics->temperature_vrgfx = metrics.TemperatureVrGfx;
	gpu_metrics->temperature_vrsoc = metrics.TemperatureVrSoc;
	gpu_metrics->temperature_vrmem = metrics.TemperatureVrMem0;

	gpu_metrics->average_gfx_activity = metrics.AverageGfxActivity;
	gpu_metrics->average_umc_activity = metrics.AverageUclkActivity;

	gpu_metrics->average_socket_घातer = metrics.AverageSocketPower;

	gpu_metrics->average_gfxclk_frequency = metrics.AverageGfxclkFrequency;
	gpu_metrics->average_socclk_frequency = metrics.AverageSocclkFrequency;
	gpu_metrics->average_uclk_frequency = metrics.AverageUclkFrequency;

	gpu_metrics->energy_accumulator = metrics.EnergyAccumulator;
	gpu_metrics->average_vclk0_frequency = metrics.AverageVclkFrequency;
	gpu_metrics->average_dclk0_frequency = metrics.AverageDclkFrequency;
	gpu_metrics->average_mm_activity = metrics.VcnActivityPercentage;

	gpu_metrics->current_gfxclk = metrics.CurrClock[PPCLK_GFXCLK];
	gpu_metrics->current_socclk = metrics.CurrClock[PPCLK_SOCCLK];
	gpu_metrics->current_uclk = metrics.CurrClock[PPCLK_UCLK];
	gpu_metrics->current_vclk0 = metrics.CurrClock[PPCLK_VCLK];
	gpu_metrics->current_dclk0 = metrics.CurrClock[PPCLK_DCLK];

	gpu_metrics->throttle_status = metrics.ThrottlerStatus;

	gpu_metrics->current_fan_speed = metrics.CurrFanSpeed;

	gpu_metrics->pcie_link_width =
			smu_v11_0_get_current_pcie_link_width(smu);
	gpu_metrics->pcie_link_speed =
			smu_v11_0_get_current_pcie_link_speed(smu);

	gpu_metrics->प्रणाली_घड़ी_counter = kसमय_get_bootसमय_ns();

	*table = (व्योम *)gpu_metrics;

	वापस माप(काष्ठा gpu_metrics_v1_1);
पूर्ण

अटल sमाप_प्रकार navi12_get_gpu_metrics(काष्ठा smu_context *smu,
				      व्योम **table)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा gpu_metrics_v1_1 *gpu_metrics =
		(काष्ठा gpu_metrics_v1_1 *)smu_table->gpu_metrics_table;
	SmuMetrics_NV12_t metrics;
	पूर्णांक ret = 0;

	mutex_lock(&smu->metrics_lock);

	ret = smu_cmn_get_metrics_table_locked(smu,
					       शून्य,
					       true);
	अगर (ret) अणु
		mutex_unlock(&smu->metrics_lock);
		वापस ret;
	पूर्ण

	स_नकल(&metrics, smu_table->metrics_table, माप(SmuMetrics_NV12_t));

	mutex_unlock(&smu->metrics_lock);

	smu_cmn_init_soft_gpu_metrics(gpu_metrics, 1, 1);

	gpu_metrics->temperature_edge = metrics.TemperatureEdge;
	gpu_metrics->temperature_hotspot = metrics.TemperatureHotspot;
	gpu_metrics->temperature_mem = metrics.TemperatureMem;
	gpu_metrics->temperature_vrgfx = metrics.TemperatureVrGfx;
	gpu_metrics->temperature_vrsoc = metrics.TemperatureVrSoc;
	gpu_metrics->temperature_vrmem = metrics.TemperatureVrMem0;

	gpu_metrics->average_gfx_activity = metrics.AverageGfxActivity;
	gpu_metrics->average_umc_activity = metrics.AverageUclkActivity;

	gpu_metrics->average_socket_घातer = metrics.AverageSocketPower;

	अगर (metrics.AverageGfxActivity > SMU_11_0_GFX_BUSY_THRESHOLD)
		gpu_metrics->average_gfxclk_frequency = metrics.AverageGfxclkFrequencyPreDs;
	अन्यथा
		gpu_metrics->average_gfxclk_frequency = metrics.AverageGfxclkFrequencyPostDs;

	gpu_metrics->average_socclk_frequency = metrics.AverageSocclkFrequency;
	gpu_metrics->average_uclk_frequency = metrics.AverageUclkFrequencyPostDs;

	gpu_metrics->energy_accumulator = metrics.EnergyAccumulator;
	gpu_metrics->average_vclk0_frequency = metrics.AverageVclkFrequency;
	gpu_metrics->average_dclk0_frequency = metrics.AverageDclkFrequency;
	gpu_metrics->average_mm_activity = metrics.VcnActivityPercentage;

	gpu_metrics->current_gfxclk = metrics.CurrClock[PPCLK_GFXCLK];
	gpu_metrics->current_socclk = metrics.CurrClock[PPCLK_SOCCLK];
	gpu_metrics->current_uclk = metrics.CurrClock[PPCLK_UCLK];
	gpu_metrics->current_vclk0 = metrics.CurrClock[PPCLK_VCLK];
	gpu_metrics->current_dclk0 = metrics.CurrClock[PPCLK_DCLK];

	gpu_metrics->throttle_status = metrics.ThrottlerStatus;

	gpu_metrics->current_fan_speed = metrics.CurrFanSpeed;

	gpu_metrics->pcie_link_width = metrics.PcieWidth;
	gpu_metrics->pcie_link_speed = link_speed[metrics.PcieRate];

	gpu_metrics->प्रणाली_घड़ी_counter = kसमय_get_bootसमय_ns();

	*table = (व्योम *)gpu_metrics;

	वापस माप(काष्ठा gpu_metrics_v1_1);
पूर्ण

अटल sमाप_प्रकार navi1x_get_gpu_metrics(काष्ठा smu_context *smu,
				      व्योम **table)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t smu_version;
	पूर्णांक ret = 0;

	ret = smu_cmn_get_smc_version(smu, शून्य, &smu_version);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to get smu version!\n");
		वापस ret;
	पूर्ण

	चयन (adev->asic_type) अणु
	हाल CHIP_NAVI12:
		अगर (smu_version > 0x00341C00)
			ret = navi12_get_gpu_metrics(smu, table);
		अन्यथा
			ret = navi12_get_legacy_gpu_metrics(smu, table);
		अवरोध;
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
	शेष:
		अगर (((adev->asic_type == CHIP_NAVI14) && smu_version > 0x00351F00) ||
		      ((adev->asic_type == CHIP_NAVI10) && smu_version > 0x002A3B00))
			ret = navi10_get_gpu_metrics(smu, table);
		अन्यथा
			ret =navi10_get_legacy_gpu_metrics(smu, table);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक navi10_enable_mgpu_fan_boost(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	PPTable_t *smc_pptable = table_context->driver_pptable;
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t param = 0;

	/* Navi12 करोes not support this */
	अगर (adev->asic_type == CHIP_NAVI12)
		वापस 0;

	/*
	 * Skip the MGpuFanBoost setting क्रम those ASICs
	 * which करो not support it
	 */
	अगर (!smc_pptable->MGpuFanBoostLimitRpm)
		वापस 0;

	/* Workaround क्रम WS SKU */
	अगर (adev->pdev->device == 0x7312 &&
	    adev->pdev->revision == 0)
		param = 0xD188;

	वापस smu_cmn_send_smc_msg_with_param(smu,
					       SMU_MSG_SetMGpuFanBoostLimitRpm,
					       param,
					       शून्य);
पूर्ण

अटल पूर्णांक navi10_post_smu_init(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक ret = 0;

	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	ret = navi10_run_umc_cdr_workaround(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to apply umc cdr workaround!\n");
		वापस ret;
	पूर्ण

	अगर (!smu->dc_controlled_by_gpio) अणु
		/*
		 * For Navi1X, manually चयन it to AC mode as PMFW
		 * may boot it with DC mode.
		 */
		ret = smu_v11_0_set_घातer_source(smu,
						 adev->pm.ac_घातer ?
						 SMU_POWER_SOURCE_AC :
						 SMU_POWER_SOURCE_DC);
		अगर (ret) अणु
			dev_err(adev->dev, "Failed to switch to %s mode!\n",
					adev->pm.ac_घातer ? "AC" : "DC");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pptable_funcs navi10_ppt_funcs = अणु
	.get_allowed_feature_mask = navi10_get_allowed_feature_mask,
	.set_शेष_dpm_table = navi10_set_शेष_dpm_table,
	.dpm_set_vcn_enable = navi10_dpm_set_vcn_enable,
	.dpm_set_jpeg_enable = navi10_dpm_set_jpeg_enable,
	.prपूर्णांक_clk_levels = navi10_prपूर्णांक_clk_levels,
	.क्रमce_clk_levels = navi10_क्रमce_clk_levels,
	.populate_umd_state_clk = navi10_populate_umd_state_clk,
	.get_घड़ी_by_type_with_latency = navi10_get_घड़ी_by_type_with_latency,
	.pre_display_config_changed = navi10_pre_display_config_changed,
	.display_config_changed = navi10_display_config_changed,
	.notअगरy_smc_display_config = navi10_notअगरy_smc_display_config,
	.is_dpm_running = navi10_is_dpm_running,
	.get_fan_speed_percent = navi10_get_fan_speed_percent,
	.get_घातer_profile_mode = navi10_get_घातer_profile_mode,
	.set_घातer_profile_mode = navi10_set_घातer_profile_mode,
	.set_watermarks_table = navi10_set_watermarks_table,
	.पढ़ो_sensor = navi10_पढ़ो_sensor,
	.get_uclk_dpm_states = navi10_get_uclk_dpm_states,
	.set_perक्रमmance_level = smu_v11_0_set_perक्रमmance_level,
	.get_thermal_temperature_range = navi10_get_thermal_temperature_range,
	.display_disable_memory_घड़ी_चयन = navi10_display_disable_memory_घड़ी_चयन,
	.get_घातer_limit = navi10_get_घातer_limit,
	.update_pcie_parameters = navi10_update_pcie_parameters,
	.init_microcode = smu_v11_0_init_microcode,
	.load_microcode = smu_v11_0_load_microcode,
	.fini_microcode = smu_v11_0_fini_microcode,
	.init_smc_tables = navi10_init_smc_tables,
	.fini_smc_tables = smu_v11_0_fini_smc_tables,
	.init_घातer = smu_v11_0_init_घातer,
	.fini_घातer = smu_v11_0_fini_घातer,
	.check_fw_status = smu_v11_0_check_fw_status,
	.setup_pptable = navi10_setup_pptable,
	.get_vbios_bootup_values = smu_v11_0_get_vbios_bootup_values,
	.check_fw_version = smu_v11_0_check_fw_version,
	.ग_लिखो_pptable = smu_cmn_ग_लिखो_pptable,
	.set_driver_table_location = smu_v11_0_set_driver_table_location,
	.set_tool_table_location = smu_v11_0_set_tool_table_location,
	.notअगरy_memory_pool_location = smu_v11_0_notअगरy_memory_pool_location,
	.प्रणाली_features_control = smu_v11_0_प्रणाली_features_control,
	.send_smc_msg_with_param = smu_cmn_send_smc_msg_with_param,
	.send_smc_msg = smu_cmn_send_smc_msg,
	.init_display_count = smu_v11_0_init_display_count,
	.set_allowed_mask = smu_v11_0_set_allowed_mask,
	.get_enabled_mask = smu_cmn_get_enabled_mask,
	.feature_is_enabled = smu_cmn_feature_is_enabled,
	.disable_all_features_with_exception = smu_cmn_disable_all_features_with_exception,
	.notअगरy_display_change = smu_v11_0_notअगरy_display_change,
	.set_घातer_limit = smu_v11_0_set_घातer_limit,
	.init_max_sustainable_घड़ीs = smu_v11_0_init_max_sustainable_घड़ीs,
	.enable_thermal_alert = smu_v11_0_enable_thermal_alert,
	.disable_thermal_alert = smu_v11_0_disable_thermal_alert,
	.set_min_dcef_deep_sleep = smu_v11_0_set_min_deep_sleep_dcefclk,
	.display_घड़ी_voltage_request = smu_v11_0_display_घड़ी_voltage_request,
	.get_fan_control_mode = smu_v11_0_get_fan_control_mode,
	.set_fan_control_mode = smu_v11_0_set_fan_control_mode,
	.set_fan_speed_percent = smu_v11_0_set_fan_speed_percent,
	.set_xgmi_pstate = smu_v11_0_set_xgmi_pstate,
	.gfx_off_control = smu_v11_0_gfx_off_control,
	.रेजिस्टर_irq_handler = smu_v11_0_रेजिस्टर_irq_handler,
	.set_azalia_d3_pme = smu_v11_0_set_azalia_d3_pme,
	.get_max_sustainable_घड़ीs_by_dc = smu_v11_0_get_max_sustainable_घड़ीs_by_dc,
	.baco_is_support= navi10_is_baco_supported,
	.baco_get_state = smu_v11_0_baco_get_state,
	.baco_set_state = smu_v11_0_baco_set_state,
	.baco_enter = smu_v11_0_baco_enter,
	.baco_निकास = smu_v11_0_baco_निकास,
	.get_dpm_ultimate_freq = smu_v11_0_get_dpm_ultimate_freq,
	.set_soft_freq_limited_range = smu_v11_0_set_soft_freq_limited_range,
	.set_शेष_od_settings = navi10_set_शेष_od_settings,
	.od_edit_dpm_table = navi10_od_edit_dpm_table,
	.run_btc = navi10_run_btc,
	.set_घातer_source = smu_v11_0_set_घातer_source,
	.get_pp_feature_mask = smu_cmn_get_pp_feature_mask,
	.set_pp_feature_mask = smu_cmn_set_pp_feature_mask,
	.get_gpu_metrics = navi1x_get_gpu_metrics,
	.enable_mgpu_fan_boost = navi10_enable_mgpu_fan_boost,
	.gfx_ulv_control = smu_v11_0_gfx_ulv_control,
	.deep_sleep_control = smu_v11_0_deep_sleep_control,
	.get_fan_parameters = navi10_get_fan_parameters,
	.post_init = navi10_post_smu_init,
	.पूर्णांकerrupt_work = smu_v11_0_पूर्णांकerrupt_work,
	.set_mp1_state = navi10_set_mp1_state,
पूर्ण;

व्योम navi10_set_ppt_funcs(काष्ठा smu_context *smu)
अणु
	smu->ppt_funcs = &navi10_ppt_funcs;
	smu->message_map = navi10_message_map;
	smu->घड़ी_map = navi10_clk_map;
	smu->feature_map = navi10_feature_mask_map;
	smu->table_map = navi10_table_map;
	smu->pwr_src_map = navi10_pwr_src_map;
	smu->workload_map = navi10_workload_map;
पूर्ण
