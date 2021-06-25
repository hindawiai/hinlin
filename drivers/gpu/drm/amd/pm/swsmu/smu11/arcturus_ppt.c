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
#समावेश "amdgpu.h"
#समावेश "amdgpu_smu.h"
#समावेश "atomfirmware.h"
#समावेश "amdgpu_atomfirmware.h"
#समावेश "amdgpu_atombios.h"
#समावेश "smu_v11_0.h"
#समावेश "smu11_driver_if_arcturus.h"
#समावेश "soc15_common.h"
#समावेश "atom.h"
#समावेश "power_state.h"
#समावेश "arcturus_ppt.h"
#समावेश "smu_v11_0_pptable.h"
#समावेश "arcturus_ppsmc.h"
#समावेश "nbio/nbio_7_4_offset.h"
#समावेश "nbio/nbio_7_4_sh_mask.h"
#समावेश "thm/thm_11_0_2_offset.h"
#समावेश "thm/thm_11_0_2_sh_mask.h"
#समावेश "amdgpu_xgmi.h"
#समावेश <linux/i2c.h>
#समावेश <linux/pci.h>
#समावेश "amdgpu_ras.h"
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

#घोषणा ARCTURUS_FEA_MAP(smu_feature, arcturus_feature) \
	[smu_feature] = अणु1, (arcturus_feature)पूर्ण

#घोषणा SMU_FEATURES_LOW_MASK        0x00000000FFFFFFFF
#घोषणा SMU_FEATURES_LOW_SHIFT       0
#घोषणा SMU_FEATURES_HIGH_MASK       0xFFFFFFFF00000000
#घोषणा SMU_FEATURES_HIGH_SHIFT      32

#घोषणा SMC_DPM_FEATURE ( \
	FEATURE_DPM_PREFETCHER_MASK | \
	FEATURE_DPM_GFXCLK_MASK | \
	FEATURE_DPM_UCLK_MASK | \
	FEATURE_DPM_SOCCLK_MASK | \
	FEATURE_DPM_MP0CLK_MASK | \
	FEATURE_DPM_FCLK_MASK | \
	FEATURE_DPM_XGMI_MASK)

/* possible frequency drअगरt (1Mhz) */
#घोषणा EPSILON				1

#घोषणा smnPCIE_ESM_CTRL			0x111003D0

अटल स्थिर काष्ठा cmn2asic_msg_mapping arcturus_message_map[SMU_MSG_MAX_COUNT] = अणु
	MSG_MAP(TestMessage,			     PPSMC_MSG_TestMessage,			0),
	MSG_MAP(GetSmuVersion,			     PPSMC_MSG_GetSmuVersion,			1),
	MSG_MAP(GetDriverIfVersion,		     PPSMC_MSG_GetDriverIfVersion,		1),
	MSG_MAP(SetAllowedFeaturesMaskLow,	     PPSMC_MSG_SetAllowedFeaturesMaskLow,	0),
	MSG_MAP(SetAllowedFeaturesMaskHigh,	     PPSMC_MSG_SetAllowedFeaturesMaskHigh,	0),
	MSG_MAP(EnableAllSmuFeatures,		     PPSMC_MSG_EnableAllSmuFeatures,		0),
	MSG_MAP(DisableAllSmuFeatures,		     PPSMC_MSG_DisableAllSmuFeatures,		0),
	MSG_MAP(EnableSmuFeaturesLow,		     PPSMC_MSG_EnableSmuFeaturesLow,		1),
	MSG_MAP(EnableSmuFeaturesHigh,		     PPSMC_MSG_EnableSmuFeaturesHigh,		1),
	MSG_MAP(DisableSmuFeaturesLow,		     PPSMC_MSG_DisableSmuFeaturesLow,		0),
	MSG_MAP(DisableSmuFeaturesHigh,		     PPSMC_MSG_DisableSmuFeaturesHigh,		0),
	MSG_MAP(GetEnabledSmuFeaturesLow,	     PPSMC_MSG_GetEnabledSmuFeaturesLow,	0),
	MSG_MAP(GetEnabledSmuFeaturesHigh,	     PPSMC_MSG_GetEnabledSmuFeaturesHigh,	0),
	MSG_MAP(SetDriverDramAddrHigh,		     PPSMC_MSG_SetDriverDramAddrHigh,		1),
	MSG_MAP(SetDriverDramAddrLow,		     PPSMC_MSG_SetDriverDramAddrLow,		1),
	MSG_MAP(SetToolsDramAddrHigh,		     PPSMC_MSG_SetToolsDramAddrHigh,		0),
	MSG_MAP(SetToolsDramAddrLow,		     PPSMC_MSG_SetToolsDramAddrLow,		0),
	MSG_MAP(TransferTableSmu2Dram,		     PPSMC_MSG_TransferTableSmu2Dram,		1),
	MSG_MAP(TransferTableDram2Smu,		     PPSMC_MSG_TransferTableDram2Smu,		0),
	MSG_MAP(UseDefaultPPTable,		     PPSMC_MSG_UseDefaultPPTable,		0),
	MSG_MAP(UseBackupPPTable,		     PPSMC_MSG_UseBackupPPTable,		0),
	MSG_MAP(SetSystemVirtualDramAddrHigh,	     PPSMC_MSG_SetSystemVirtualDramAddrHigh,	0),
	MSG_MAP(SetSystemVirtualDramAddrLow,	     PPSMC_MSG_SetSystemVirtualDramAddrLow,	0),
	MSG_MAP(EnterBaco,			     PPSMC_MSG_EnterBaco,			0),
	MSG_MAP(ExitBaco,			     PPSMC_MSG_ExitBaco,			0),
	MSG_MAP(ArmD3,				     PPSMC_MSG_ArmD3,				0),
	MSG_MAP(SetSoftMinByFreq,		     PPSMC_MSG_SetSoftMinByFreq,		0),
	MSG_MAP(SetSoftMaxByFreq,		     PPSMC_MSG_SetSoftMaxByFreq,		0),
	MSG_MAP(SetHardMinByFreq,		     PPSMC_MSG_SetHardMinByFreq,		0),
	MSG_MAP(SetHardMaxByFreq,		     PPSMC_MSG_SetHardMaxByFreq,		0),
	MSG_MAP(GetMinDpmFreq,			     PPSMC_MSG_GetMinDpmFreq,			0),
	MSG_MAP(GetMaxDpmFreq,			     PPSMC_MSG_GetMaxDpmFreq,			0),
	MSG_MAP(GetDpmFreqByIndex,		     PPSMC_MSG_GetDpmFreqByIndex,		1),
	MSG_MAP(SetWorkloadMask,		     PPSMC_MSG_SetWorkloadMask,			1),
	MSG_MAP(SetDfSwitchType,		     PPSMC_MSG_SetDfSwitchType,			0),
	MSG_MAP(GetVoltageByDpm,		     PPSMC_MSG_GetVoltageByDpm,			0),
	MSG_MAP(GetVoltageByDpmOverdrive,	     PPSMC_MSG_GetVoltageByDpmOverdrive,	0),
	MSG_MAP(SetPptLimit,			     PPSMC_MSG_SetPptLimit,			0),
	MSG_MAP(GetPptLimit,			     PPSMC_MSG_GetPptLimit,			1),
	MSG_MAP(PowerUpVcn0,			     PPSMC_MSG_PowerUpVcn0,			0),
	MSG_MAP(PowerDownVcn0,			     PPSMC_MSG_PowerDownVcn0,			0),
	MSG_MAP(PowerUpVcn1,			     PPSMC_MSG_PowerUpVcn1,			0),
	MSG_MAP(PowerDownVcn1,			     PPSMC_MSG_PowerDownVcn1,			0),
	MSG_MAP(PrepareMp1ForUnload,		     PPSMC_MSG_PrepareMp1ForUnload,		0),
	MSG_MAP(PrepareMp1ForReset,		     PPSMC_MSG_PrepareMp1ForReset,		0),
	MSG_MAP(PrepareMp1ForShutकरोwn,		     PPSMC_MSG_PrepareMp1ForShutकरोwn,		0),
	MSG_MAP(SoftReset,			     PPSMC_MSG_SoftReset,			0),
	MSG_MAP(RunAfllBtc,			     PPSMC_MSG_RunAfllBtc,			0),
	MSG_MAP(RunDcBtc,			     PPSMC_MSG_RunDcBtc,			0),
	MSG_MAP(DramLogSetDramAddrHigh,		     PPSMC_MSG_DramLogSetDramAddrHigh,		0),
	MSG_MAP(DramLogSetDramAddrLow,		     PPSMC_MSG_DramLogSetDramAddrLow,		0),
	MSG_MAP(DramLogSetDramSize,		     PPSMC_MSG_DramLogSetDramSize,		0),
	MSG_MAP(GetDebugData,			     PPSMC_MSG_GetDebugData,			0),
	MSG_MAP(WaflTest,			     PPSMC_MSG_WaflTest,			0),
	MSG_MAP(SetXgmiMode,			     PPSMC_MSG_SetXgmiMode,			0),
	MSG_MAP(SetMemoryChannelEnable,		     PPSMC_MSG_SetMemoryChannelEnable,		0),
	MSG_MAP(DFCstateControl,		     PPSMC_MSG_DFCstateControl,			0),
	MSG_MAP(GmiPwrDnControl,		     PPSMC_MSG_GmiPwrDnControl,			0),
	MSG_MAP(ReadSerialNumTop32,		     PPSMC_MSG_ReadSerialNumTop32,		1),
	MSG_MAP(ReadSerialNumBottom32,		     PPSMC_MSG_ReadSerialNumBottom32,		1),
	MSG_MAP(LightSBR,			     PPSMC_MSG_LightSBR,			0),
पूर्ण;

अटल स्थिर काष्ठा cmn2asic_mapping arcturus_clk_map[SMU_CLK_COUNT] = अणु
	CLK_MAP(GFXCLK, PPCLK_GFXCLK),
	CLK_MAP(SCLK,	PPCLK_GFXCLK),
	CLK_MAP(SOCCLK, PPCLK_SOCCLK),
	CLK_MAP(FCLK, PPCLK_FCLK),
	CLK_MAP(UCLK, PPCLK_UCLK),
	CLK_MAP(MCLK, PPCLK_UCLK),
	CLK_MAP(DCLK, PPCLK_DCLK),
	CLK_MAP(VCLK, PPCLK_VCLK),
पूर्ण;

अटल स्थिर काष्ठा cmn2asic_mapping arcturus_feature_mask_map[SMU_FEATURE_COUNT] = अणु
	FEA_MAP(DPM_PREFETCHER),
	FEA_MAP(DPM_GFXCLK),
	FEA_MAP(DPM_UCLK),
	FEA_MAP(DPM_SOCCLK),
	FEA_MAP(DPM_FCLK),
	FEA_MAP(DPM_MP0CLK),
	ARCTURUS_FEA_MAP(SMU_FEATURE_XGMI_BIT, FEATURE_DPM_XGMI_BIT),
	FEA_MAP(DS_GFXCLK),
	FEA_MAP(DS_SOCCLK),
	FEA_MAP(DS_LCLK),
	FEA_MAP(DS_FCLK),
	FEA_MAP(DS_UCLK),
	FEA_MAP(GFX_ULV),
	ARCTURUS_FEA_MAP(SMU_FEATURE_VCN_PG_BIT, FEATURE_DPM_VCN_BIT),
	FEA_MAP(RSMU_SMN_CG),
	FEA_MAP(WAFL_CG),
	FEA_MAP(PPT),
	FEA_MAP(TDC),
	FEA_MAP(APCC_PLUS),
	FEA_MAP(VR0HOT),
	FEA_MAP(VR1HOT),
	FEA_MAP(FW_CTF),
	FEA_MAP(FAN_CONTROL),
	FEA_MAP(THERMAL),
	FEA_MAP(OUT_OF_BAND_MONITOR),
	FEA_MAP(TEMP_DEPENDENT_VMIN),
पूर्ण;

अटल स्थिर काष्ठा cmn2asic_mapping arcturus_table_map[SMU_TABLE_COUNT] = अणु
	TAB_MAP(PPTABLE),
	TAB_MAP(AVFS),
	TAB_MAP(AVFS_PSM_DEBUG),
	TAB_MAP(AVFS_FUSE_OVERRIDE),
	TAB_MAP(PMSTATUSLOG),
	TAB_MAP(SMU_METRICS),
	TAB_MAP(DRIVER_SMU_CONFIG),
	TAB_MAP(OVERDRIVE),
	TAB_MAP(I2C_COMMANDS),
	TAB_MAP(ACTIVITY_MONITOR_COEFF),
पूर्ण;

अटल स्थिर काष्ठा cmn2asic_mapping arcturus_pwr_src_map[SMU_POWER_SOURCE_COUNT] = अणु
	PWR_MAP(AC),
	PWR_MAP(DC),
पूर्ण;

अटल स्थिर काष्ठा cmn2asic_mapping arcturus_workload_map[PP_SMC_POWER_PROखाता_COUNT] = अणु
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT,	WORKLOAD_PPLIB_DEFAULT_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_POWERSAVING,		WORKLOAD_PPLIB_POWER_SAVING_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_VIDEO,		WORKLOAD_PPLIB_VIDEO_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_COMPUTE,		WORKLOAD_PPLIB_COMPUTE_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_CUSTOM,		WORKLOAD_PPLIB_CUSTOM_BIT),
पूर्ण;

अटल पूर्णांक arcturus_tables_init(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा smu_table *tables = smu_table->tables;

	SMU_TABLE_INIT(tables, SMU_TABLE_PPTABLE, माप(PPTable_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);

	SMU_TABLE_INIT(tables, SMU_TABLE_PMSTATUSLOG, SMU11_TOOL_SIZE,
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);

	SMU_TABLE_INIT(tables, SMU_TABLE_SMU_METRICS, माप(SmuMetrics_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);

	SMU_TABLE_INIT(tables, SMU_TABLE_I2C_COMMANDS, माप(SwI2cRequest_t),
			       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);

	SMU_TABLE_INIT(tables, SMU_TABLE_ACTIVITY_MONITOR_COEFF,
		       माप(DpmActivityMonitorCoeffInt_t), PAGE_SIZE,
		       AMDGPU_GEM_DOMAIN_VRAM);

	smu_table->metrics_table = kzalloc(माप(SmuMetrics_t), GFP_KERNEL);
	अगर (!smu_table->metrics_table)
		वापस -ENOMEM;
	smu_table->metrics_समय = 0;

	smu_table->gpu_metrics_table_size = माप(काष्ठा gpu_metrics_v1_1);
	smu_table->gpu_metrics_table = kzalloc(smu_table->gpu_metrics_table_size, GFP_KERNEL);
	अगर (!smu_table->gpu_metrics_table) अणु
		kमुक्त(smu_table->metrics_table);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arcturus_allocate_dpm_context(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_dpm_context *smu_dpm = &smu->smu_dpm;

	smu_dpm->dpm_context = kzalloc(माप(काष्ठा smu_11_0_dpm_context),
				       GFP_KERNEL);
	अगर (!smu_dpm->dpm_context)
		वापस -ENOMEM;
	smu_dpm->dpm_context_size = माप(काष्ठा smu_11_0_dpm_context);

	smu_dpm->dpm_current_घातer_state = kzalloc(माप(काष्ठा smu_घातer_state),
				       GFP_KERNEL);
	अगर (!smu_dpm->dpm_current_घातer_state)
		वापस -ENOMEM;

	smu_dpm->dpm_request_घातer_state = kzalloc(माप(काष्ठा smu_घातer_state),
				       GFP_KERNEL);
	अगर (!smu_dpm->dpm_request_घातer_state)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक arcturus_init_smc_tables(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	ret = arcturus_tables_init(smu);
	अगर (ret)
		वापस ret;

	ret = arcturus_allocate_dpm_context(smu);
	अगर (ret)
		वापस ret;

	वापस smu_v11_0_init_smc_tables(smu);
पूर्ण

अटल पूर्णांक
arcturus_get_allowed_feature_mask(काष्ठा smu_context *smu,
				  uपूर्णांक32_t *feature_mask, uपूर्णांक32_t num)
अणु
	अगर (num > 2)
		वापस -EINVAL;

	/* pptable will handle the features to enable */
	स_रखो(feature_mask, 0xFF, माप(uपूर्णांक32_t) * num);

	वापस 0;
पूर्ण

अटल पूर्णांक arcturus_set_शेष_dpm_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_11_0_dpm_context *dpm_context = smu->smu_dpm.dpm_context;
	PPTable_t *driver_ppt = smu->smu_table.driver_pptable;
	काष्ठा smu_11_0_dpm_table *dpm_table = शून्य;
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

	/* memclk dpm table setup */
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

	वापस 0;
पूर्ण

अटल पूर्णांक arcturus_check_घातerplay_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	काष्ठा smu_11_0_घातerplay_table *घातerplay_table =
		table_context->घातer_play_table;
	काष्ठा smu_baco_context *smu_baco = &smu->smu_baco;

	अगर (घातerplay_table->platक्रमm_caps & SMU_11_0_PP_PLATFORM_CAP_BACO ||
	    घातerplay_table->platक्रमm_caps & SMU_11_0_PP_PLATFORM_CAP_MACO)
		smu_baco->platक्रमm_support = true;

	table_context->thermal_controller_type =
		घातerplay_table->thermal_controller_type;

	वापस 0;
पूर्ण

अटल पूर्णांक arcturus_store_घातerplay_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	काष्ठा smu_11_0_घातerplay_table *घातerplay_table =
		table_context->घातer_play_table;

	स_नकल(table_context->driver_pptable, &घातerplay_table->smc_pptable,
	       माप(PPTable_t));

	वापस 0;
पूर्ण

अटल पूर्णांक arcturus_append_घातerplay_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	PPTable_t *smc_pptable = table_context->driver_pptable;
	काष्ठा atom_smc_dpm_info_v4_6 *smc_dpm_table;
	पूर्णांक index, ret;

	index = get_index_पूर्णांकo_master_table(atom_master_list_of_data_tables_v2_1,
					   smc_dpm_info);

	ret = amdgpu_atombios_get_data_table(smu->adev, index, शून्य, शून्य, शून्य,
				      (uपूर्णांक8_t **)&smc_dpm_table);
	अगर (ret)
		वापस ret;

	dev_info(smu->adev->dev, "smc_dpm_info table revision(format.content): %d.%d\n",
			smc_dpm_table->table_header.क्रमmat_revision,
			smc_dpm_table->table_header.content_revision);

	अगर ((smc_dpm_table->table_header.क्रमmat_revision == 4) &&
	    (smc_dpm_table->table_header.content_revision == 6))
		स_नकल(&smc_pptable->MaxVoltageStepGfx,
		       &smc_dpm_table->maxvoltagestepgfx,
		       माप(*smc_dpm_table) - दुरत्व(काष्ठा atom_smc_dpm_info_v4_6, maxvoltagestepgfx));

	वापस 0;
पूर्ण

अटल पूर्णांक arcturus_setup_pptable(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	ret = smu_v11_0_setup_pptable(smu);
	अगर (ret)
		वापस ret;

	ret = arcturus_store_घातerplay_table(smu);
	अगर (ret)
		वापस ret;

	ret = arcturus_append_घातerplay_table(smu);
	अगर (ret)
		वापस ret;

	ret = arcturus_check_घातerplay_table(smu);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक arcturus_run_btc(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	ret = smu_cmn_send_smc_msg(smu, SMU_MSG_RunAfllBtc, शून्य);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "RunAfllBtc failed!\n");
		वापस ret;
	पूर्ण

	वापस smu_cmn_send_smc_msg(smu, SMU_MSG_RunDcBtc, शून्य);
पूर्ण

अटल पूर्णांक arcturus_populate_umd_state_clk(काष्ठा smu_context *smu)
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

	pstate_table->uclk_pstate.min = mem_table->min;
	pstate_table->uclk_pstate.peak = mem_table->max;

	pstate_table->socclk_pstate.min = soc_table->min;
	pstate_table->socclk_pstate.peak = soc_table->max;

	अगर (gfx_table->count > ARCTURUS_UMD_PSTATE_GFXCLK_LEVEL &&
	    mem_table->count > ARCTURUS_UMD_PSTATE_MCLK_LEVEL &&
	    soc_table->count > ARCTURUS_UMD_PSTATE_SOCCLK_LEVEL) अणु
		pstate_table->gfxclk_pstate.standard =
			gfx_table->dpm_levels[ARCTURUS_UMD_PSTATE_GFXCLK_LEVEL].value;
		pstate_table->uclk_pstate.standard =
			mem_table->dpm_levels[ARCTURUS_UMD_PSTATE_MCLK_LEVEL].value;
		pstate_table->socclk_pstate.standard =
			soc_table->dpm_levels[ARCTURUS_UMD_PSTATE_SOCCLK_LEVEL].value;
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

अटल पूर्णांक arcturus_get_clk_table(काष्ठा smu_context *smu,
			काष्ठा pp_घड़ी_levels_with_latency *घड़ीs,
			काष्ठा smu_11_0_dpm_table *dpm_table)
अणु
	पूर्णांक i, count;

	count = (dpm_table->count > MAX_NUM_CLOCKS) ? MAX_NUM_CLOCKS : dpm_table->count;
	घड़ीs->num_levels = count;

	क्रम (i = 0; i < count; i++) अणु
		घड़ीs->data[i].घड़ीs_in_khz =
			dpm_table->dpm_levels[i].value * 1000;
		घड़ीs->data[i].latency_in_us = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arcturus_freqs_in_same_level(पूर्णांक32_t frequency1,
					पूर्णांक32_t frequency2)
अणु
	वापस (असल(frequency1 - frequency2) <= EPSILON);
पूर्ण

अटल पूर्णांक arcturus_get_smu_metrics_data(काष्ठा smu_context *smu,
					 MetricsMember_t member,
					 uपूर्णांक32_t *value)
अणु
	काष्ठा smu_table_context *smu_table= &smu->smu_table;
	SmuMetrics_t *metrics = (SmuMetrics_t *)smu_table->metrics_table;
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
	हाल METRICS_CURR_FCLK:
		*value = metrics->CurrClock[PPCLK_FCLK];
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
	हाल METRICS_AVERAGE_VCLK:
		*value = metrics->AverageVclkFrequency;
		अवरोध;
	हाल METRICS_AVERAGE_DCLK:
		*value = metrics->AverageDclkFrequency;
		अवरोध;
	हाल METRICS_AVERAGE_GFXACTIVITY:
		*value = metrics->AverageGfxActivity;
		अवरोध;
	हाल METRICS_AVERAGE_MEMACTIVITY:
		*value = metrics->AverageUclkActivity;
		अवरोध;
	हाल METRICS_AVERAGE_VCNACTIVITY:
		*value = metrics->VcnActivityPercentage;
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
		*value = metrics->TemperatureHBM *
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
	हाल METRICS_TEMPERATURE_VRMEM:
		*value = metrics->TemperatureVrMem *
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

अटल पूर्णांक arcturus_get_current_clk_freq_by_table(काष्ठा smu_context *smu,
				       क्रमागत smu_clk_type clk_type,
				       uपूर्णांक32_t *value)
अणु
	MetricsMember_t member_type;
	पूर्णांक clk_id = 0;

	अगर (!value)
		वापस -EINVAL;

	clk_id = smu_cmn_to_asic_specअगरic_index(smu,
						CMN2ASIC_MAPPING_CLK,
						clk_type);
	अगर (clk_id < 0)
		वापस -EINVAL;

	चयन (clk_id) अणु
	हाल PPCLK_GFXCLK:
		/*
		 * CurrClock[clk_id] can provide accurate
		 *   output only when the dpm feature is enabled.
		 * We can use Average_* क्रम dpm disabled हाल.
		 *   But this is available क्रम gfxclk/uclk/socclk/vclk/dclk.
		 */
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_GFXCLK_BIT))
			member_type = METRICS_CURR_GFXCLK;
		अन्यथा
			member_type = METRICS_AVERAGE_GFXCLK;
		अवरोध;
	हाल PPCLK_UCLK:
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_UCLK_BIT))
			member_type = METRICS_CURR_UCLK;
		अन्यथा
			member_type = METRICS_AVERAGE_UCLK;
		अवरोध;
	हाल PPCLK_SOCCLK:
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_SOCCLK_BIT))
			member_type = METRICS_CURR_SOCCLK;
		अन्यथा
			member_type = METRICS_AVERAGE_SOCCLK;
		अवरोध;
	हाल PPCLK_VCLK:
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_VCN_PG_BIT))
			member_type = METRICS_CURR_VCLK;
		अन्यथा
			member_type = METRICS_AVERAGE_VCLK;
		अवरोध;
	हाल PPCLK_DCLK:
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_VCN_PG_BIT))
			member_type = METRICS_CURR_DCLK;
		अन्यथा
			member_type = METRICS_AVERAGE_DCLK;
		अवरोध;
	हाल PPCLK_FCLK:
		member_type = METRICS_CURR_FCLK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस arcturus_get_smu_metrics_data(smu,
					     member_type,
					     value);
पूर्ण

अटल पूर्णांक arcturus_prपूर्णांक_clk_levels(काष्ठा smu_context *smu,
			क्रमागत smu_clk_type type, अक्षर *buf)
अणु
	पूर्णांक i, now, size = 0;
	पूर्णांक ret = 0;
	काष्ठा pp_घड़ी_levels_with_latency घड़ीs;
	काष्ठा smu_11_0_dpm_table *single_dpm_table;
	काष्ठा smu_dpm_context *smu_dpm = &smu->smu_dpm;
	काष्ठा smu_11_0_dpm_context *dpm_context = शून्य;
	uपूर्णांक32_t gen_speed, lane_width;

	अगर (amdgpu_ras_पूर्णांकr_triggered())
		वापस snम_लिखो(buf, PAGE_SIZE, "unavailable\n");

	dpm_context = smu_dpm->dpm_context;

	चयन (type) अणु
	हाल SMU_SCLK:
		ret = arcturus_get_current_clk_freq_by_table(smu, SMU_GFXCLK, &now);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Attempt to get current gfx clk Failed!");
			वापस ret;
		पूर्ण

		single_dpm_table = &(dpm_context->dpm_tables.gfx_table);
		ret = arcturus_get_clk_table(smu, &घड़ीs, single_dpm_table);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Attempt to get gfx clk levels Failed!");
			वापस ret;
		पूर्ण

		/*
		 * For DPM disabled हाल, there will be only one घड़ी level.
		 * And it's safe to assume that is always the current घड़ी.
		 */
		क्रम (i = 0; i < घड़ीs.num_levels; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n", i,
					घड़ीs.data[i].घड़ीs_in_khz / 1000,
					(घड़ीs.num_levels == 1) ? "*" :
					(arcturus_freqs_in_same_level(
					घड़ीs.data[i].घड़ीs_in_khz / 1000,
					now) ? "*" : ""));
		अवरोध;

	हाल SMU_MCLK:
		ret = arcturus_get_current_clk_freq_by_table(smu, SMU_UCLK, &now);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Attempt to get current mclk Failed!");
			वापस ret;
		पूर्ण

		single_dpm_table = &(dpm_context->dpm_tables.uclk_table);
		ret = arcturus_get_clk_table(smu, &घड़ीs, single_dpm_table);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Attempt to get memory clk levels Failed!");
			वापस ret;
		पूर्ण

		क्रम (i = 0; i < घड़ीs.num_levels; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
				i, घड़ीs.data[i].घड़ीs_in_khz / 1000,
				(घड़ीs.num_levels == 1) ? "*" :
				(arcturus_freqs_in_same_level(
				घड़ीs.data[i].घड़ीs_in_khz / 1000,
				now) ? "*" : ""));
		अवरोध;

	हाल SMU_SOCCLK:
		ret = arcturus_get_current_clk_freq_by_table(smu, SMU_SOCCLK, &now);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Attempt to get current socclk Failed!");
			वापस ret;
		पूर्ण

		single_dpm_table = &(dpm_context->dpm_tables.soc_table);
		ret = arcturus_get_clk_table(smu, &घड़ीs, single_dpm_table);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Attempt to get socclk levels Failed!");
			वापस ret;
		पूर्ण

		क्रम (i = 0; i < घड़ीs.num_levels; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
				i, घड़ीs.data[i].घड़ीs_in_khz / 1000,
				(घड़ीs.num_levels == 1) ? "*" :
				(arcturus_freqs_in_same_level(
				घड़ीs.data[i].घड़ीs_in_khz / 1000,
				now) ? "*" : ""));
		अवरोध;

	हाल SMU_FCLK:
		ret = arcturus_get_current_clk_freq_by_table(smu, SMU_FCLK, &now);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Attempt to get current fclk Failed!");
			वापस ret;
		पूर्ण

		single_dpm_table = &(dpm_context->dpm_tables.fclk_table);
		ret = arcturus_get_clk_table(smu, &घड़ीs, single_dpm_table);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Attempt to get fclk levels Failed!");
			वापस ret;
		पूर्ण

		क्रम (i = 0; i < single_dpm_table->count; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
				i, single_dpm_table->dpm_levels[i].value,
				(घड़ीs.num_levels == 1) ? "*" :
				(arcturus_freqs_in_same_level(
				घड़ीs.data[i].घड़ीs_in_khz / 1000,
				now) ? "*" : ""));
		अवरोध;

	हाल SMU_PCIE:
		gen_speed = smu_v11_0_get_current_pcie_link_speed_level(smu);
		lane_width = smu_v11_0_get_current_pcie_link_width_level(smu);
		size += प्र_लिखो(buf + size, "0: %s %s %dMhz *\n",
				(gen_speed == 0) ? "2.5GT/s," :
				(gen_speed == 1) ? "5.0GT/s," :
				(gen_speed == 2) ? "8.0GT/s," :
				(gen_speed == 3) ? "16.0GT/s," : "",
				(lane_width == 1) ? "x1" :
				(lane_width == 2) ? "x2" :
				(lane_width == 3) ? "x4" :
				(lane_width == 4) ? "x8" :
				(lane_width == 5) ? "x12" :
				(lane_width == 6) ? "x16" : "",
				smu->smu_table.boot_values.lclk / 100);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक arcturus_upload_dpm_level(काष्ठा smu_context *smu,
				     bool max,
				     uपूर्णांक32_t feature_mask,
				     uपूर्णांक32_t level)
अणु
	काष्ठा smu_11_0_dpm_context *dpm_context =
			smu->smu_dpm.dpm_context;
	uपूर्णांक32_t freq;
	पूर्णांक ret = 0;

	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_GFXCLK_BIT) &&
	    (feature_mask & FEATURE_DPM_GFXCLK_MASK)) अणु
		freq = dpm_context->dpm_tables.gfx_table.dpm_levels[level].value;
		ret = smu_cmn_send_smc_msg_with_param(smu,
			(max ? SMU_MSG_SetSoftMaxByFreq : SMU_MSG_SetSoftMinByFreq),
			(PPCLK_GFXCLK << 16) | (freq & 0xffff),
			शून्य);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Failed to set soft %s gfxclk !\n",
						max ? "max" : "min");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_UCLK_BIT) &&
	    (feature_mask & FEATURE_DPM_UCLK_MASK)) अणु
		freq = dpm_context->dpm_tables.uclk_table.dpm_levels[level].value;
		ret = smu_cmn_send_smc_msg_with_param(smu,
			(max ? SMU_MSG_SetSoftMaxByFreq : SMU_MSG_SetSoftMinByFreq),
			(PPCLK_UCLK << 16) | (freq & 0xffff),
			शून्य);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Failed to set soft %s memclk !\n",
						max ? "max" : "min");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_SOCCLK_BIT) &&
	    (feature_mask & FEATURE_DPM_SOCCLK_MASK)) अणु
		freq = dpm_context->dpm_tables.soc_table.dpm_levels[level].value;
		ret = smu_cmn_send_smc_msg_with_param(smu,
			(max ? SMU_MSG_SetSoftMaxByFreq : SMU_MSG_SetSoftMinByFreq),
			(PPCLK_SOCCLK << 16) | (freq & 0xffff),
			शून्य);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Failed to set soft %s socclk !\n",
						max ? "max" : "min");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक arcturus_क्रमce_clk_levels(काष्ठा smu_context *smu,
			क्रमागत smu_clk_type type, uपूर्णांक32_t mask)
अणु
	काष्ठा smu_11_0_dpm_context *dpm_context = smu->smu_dpm.dpm_context;
	काष्ठा smu_11_0_dpm_table *single_dpm_table = शून्य;
	uपूर्णांक32_t soft_min_level, soft_max_level;
	uपूर्णांक32_t smu_version;
	पूर्णांक ret = 0;

	ret = smu_cmn_get_smc_version(smu, शून्य, &smu_version);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "Failed to get smu version!\n");
		वापस ret;
	पूर्ण

	अगर ((smu_version >= 0x361200) &&
	    (smu_version <= 0x361a00)) अणु
		dev_err(smu->adev->dev, "Forcing clock level is not supported with "
		       "54.18 - 54.26(included) SMU firmwares\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	soft_min_level = mask ? (ffs(mask) - 1) : 0;
	soft_max_level = mask ? (fls(mask) - 1) : 0;

	चयन (type) अणु
	हाल SMU_SCLK:
		single_dpm_table = &(dpm_context->dpm_tables.gfx_table);
		अगर (soft_max_level >= single_dpm_table->count) अणु
			dev_err(smu->adev->dev, "Clock level specified %d is over max allowed %d\n",
					soft_max_level, single_dpm_table->count - 1);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ret = arcturus_upload_dpm_level(smu,
						false,
						FEATURE_DPM_GFXCLK_MASK,
						soft_min_level);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Failed to upload boot level to lowest!\n");
			अवरोध;
		पूर्ण

		ret = arcturus_upload_dpm_level(smu,
						true,
						FEATURE_DPM_GFXCLK_MASK,
						soft_max_level);
		अगर (ret)
			dev_err(smu->adev->dev, "Failed to upload dpm max level to highest!\n");

		अवरोध;

	हाल SMU_MCLK:
	हाल SMU_SOCCLK:
	हाल SMU_FCLK:
		/*
		 * Should not arrive here since Arcturus करोes not
		 * support mclk/socclk/fclk sofपंचांगin/sofपंचांगax settings
		 */
		ret = -EINVAL;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक arcturus_get_thermal_temperature_range(काष्ठा smu_context *smu,
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

अटल पूर्णांक arcturus_पढ़ो_sensor(काष्ठा smu_context *smu,
				क्रमागत amd_pp_sensors sensor,
				व्योम *data, uपूर्णांक32_t *size)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	PPTable_t *pptable = table_context->driver_pptable;
	पूर्णांक ret = 0;

	अगर (amdgpu_ras_पूर्णांकr_triggered())
		वापस 0;

	अगर (!data || !size)
		वापस -EINVAL;

	mutex_lock(&smu->sensor_lock);
	चयन (sensor) अणु
	हाल AMDGPU_PP_SENSOR_MAX_FAN_RPM:
		*(uपूर्णांक32_t *)data = pptable->FanMaximumRpm;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_MEM_LOAD:
		ret = arcturus_get_smu_metrics_data(smu,
						    METRICS_AVERAGE_MEMACTIVITY,
						    (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GPU_LOAD:
		ret = arcturus_get_smu_metrics_data(smu,
						    METRICS_AVERAGE_GFXACTIVITY,
						    (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GPU_POWER:
		ret = arcturus_get_smu_metrics_data(smu,
						    METRICS_AVERAGE_SOCKETPOWER,
						    (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_HOTSPOT_TEMP:
		ret = arcturus_get_smu_metrics_data(smu,
						    METRICS_TEMPERATURE_HOTSPOT,
						    (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_EDGE_TEMP:
		ret = arcturus_get_smu_metrics_data(smu,
						    METRICS_TEMPERATURE_EDGE,
						    (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_MEM_TEMP:
		ret = arcturus_get_smu_metrics_data(smu,
						    METRICS_TEMPERATURE_MEM,
						    (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GFX_MCLK:
		ret = arcturus_get_current_clk_freq_by_table(smu, SMU_UCLK, (uपूर्णांक32_t *)data);
		/* the output घड़ी frequency in 10K unit */
		*(uपूर्णांक32_t *)data *= 100;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GFX_SCLK:
		ret = arcturus_get_current_clk_freq_by_table(smu, SMU_GFXCLK, (uपूर्णांक32_t *)data);
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

अटल पूर्णांक arcturus_get_fan_speed_percent(काष्ठा smu_context *smu,
					  uपूर्णांक32_t *speed)
अणु
	पूर्णांक ret;
	u32 rpm;

	अगर (!speed)
		वापस -EINVAL;

	चयन (smu_v11_0_get_fan_control_mode(smu)) अणु
	हाल AMD_FAN_CTRL_AUTO:
		ret = arcturus_get_smu_metrics_data(smu,
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

अटल पूर्णांक arcturus_get_fan_parameters(काष्ठा smu_context *smu)
अणु
	PPTable_t *pptable = smu->smu_table.driver_pptable;

	smu->fan_max_rpm = pptable->FanMaximumRpm;

	वापस 0;
पूर्ण

अटल पूर्णांक arcturus_get_घातer_limit(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_11_0_घातerplay_table *घातerplay_table =
		(काष्ठा smu_11_0_घातerplay_table *)smu->smu_table.घातer_play_table;
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
		od_percent = le32_to_cpu(घातerplay_table->overdrive_table.max[SMU_11_0_ODSETTING_POWERPERCENTAGE]);

		dev_dbg(smu->adev->dev, "ODSETTING_POWERPERCENTAGE: %d (default: %d)\n", od_percent, घातer_limit);

		घातer_limit *= (100 + od_percent);
		घातer_limit /= 100;
	पूर्ण
	smu->max_घातer_limit = घातer_limit;

	वापस 0;
पूर्ण

अटल पूर्णांक arcturus_get_घातer_profile_mode(काष्ठा smu_context *smu,
					   अक्षर *buf)
अणु
	DpmActivityMonitorCoeffInt_t activity_monitor;
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
			"UseRlcBusy",
			"MinActiveFreqType",
			"MinActiveFreq",
			"BoosterFreqType",
			"BoosterFreq",
			"PD_Data_limit_c",
			"PD_Data_error_coeff",
			"PD_Data_error_rate_coeff"पूर्ण;
	uपूर्णांक32_t i, size = 0;
	पूर्णांक16_t workload_type = 0;
	पूर्णांक result = 0;
	uपूर्णांक32_t smu_version;

	अगर (!buf)
		वापस -EINVAL;

	result = smu_cmn_get_smc_version(smu, शून्य, &smu_version);
	अगर (result)
		वापस result;

	अगर (smu_version >= 0x360d00)
		size += प्र_लिखो(buf + size, "%16s %s %s %s %s %s %s %s %s %s %s\n",
			title[0], title[1], title[2], title[3], title[4], title[5],
			title[6], title[7], title[8], title[9], title[10]);
	अन्यथा
		size += प्र_लिखो(buf + size, "%16s\n",
			title[0]);

	क्रम (i = 0; i <= PP_SMC_POWER_PROखाता_CUSTOM; i++) अणु
		/*
		 * Conv PP_SMC_POWER_PROखाता* to WORKLOAD_PPLIB_*_BIT
		 * Not all profile modes are supported on arcturus.
		 */
		workload_type = smu_cmn_to_asic_specअगरic_index(smu,
							       CMN2ASIC_MAPPING_WORKLOAD,
							       i);
		अगर (workload_type < 0)
			जारी;

		अगर (smu_version >= 0x360d00) अणु
			result = smu_cmn_update_table(smu,
						  SMU_TABLE_ACTIVITY_MONITOR_COEFF,
						  workload_type,
						  (व्योम *)(&activity_monitor),
						  false);
			अगर (result) अणु
				dev_err(smu->adev->dev, "[%s] Failed to get activity monitor!", __func__);
				वापस result;
			पूर्ण
		पूर्ण

		size += प्र_लिखो(buf + size, "%2d %14s%s\n",
			i, profile_name[i], (i == smu->घातer_profile_mode) ? "*" : " ");

		अगर (smu_version >= 0x360d00) अणु
			size += प्र_लिखो(buf + size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d %7d\n",
				" ",
				0,
				"GFXCLK",
				activity_monitor.Gfx_FPS,
				activity_monitor.Gfx_UseRlcBusy,
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
				"UCLK",
				activity_monitor.Mem_FPS,
				activity_monitor.Mem_UseRlcBusy,
				activity_monitor.Mem_MinActiveFreqType,
				activity_monitor.Mem_MinActiveFreq,
				activity_monitor.Mem_BoosterFreqType,
				activity_monitor.Mem_BoosterFreq,
				activity_monitor.Mem_PD_Data_limit_c,
				activity_monitor.Mem_PD_Data_error_coeff,
				activity_monitor.Mem_PD_Data_error_rate_coeff);
		पूर्ण
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक arcturus_set_घातer_profile_mode(काष्ठा smu_context *smu,
					   दीर्घ *input,
					   uपूर्णांक32_t size)
अणु
	DpmActivityMonitorCoeffInt_t activity_monitor;
	पूर्णांक workload_type = 0;
	uपूर्णांक32_t profile_mode = input[size];
	पूर्णांक ret = 0;
	uपूर्णांक32_t smu_version;

	अगर (profile_mode > PP_SMC_POWER_PROखाता_CUSTOM) अणु
		dev_err(smu->adev->dev, "Invalid power profile mode %d\n", profile_mode);
		वापस -EINVAL;
	पूर्ण

	ret = smu_cmn_get_smc_version(smu, शून्य, &smu_version);
	अगर (ret)
		वापस ret;

	अगर ((profile_mode == PP_SMC_POWER_PROखाता_CUSTOM) &&
	     (smu_version >=0x360d00)) अणु
		ret = smu_cmn_update_table(smu,
				       SMU_TABLE_ACTIVITY_MONITOR_COEFF,
				       WORKLOAD_PPLIB_CUSTOM_BIT,
				       (व्योम *)(&activity_monitor),
				       false);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "[%s] Failed to get activity monitor!", __func__);
			वापस ret;
		पूर्ण

		चयन (input[0]) अणु
		हाल 0: /* Gfxclk */
			activity_monitor.Gfx_FPS = input[1];
			activity_monitor.Gfx_UseRlcBusy = input[2];
			activity_monitor.Gfx_MinActiveFreqType = input[3];
			activity_monitor.Gfx_MinActiveFreq = input[4];
			activity_monitor.Gfx_BoosterFreqType = input[5];
			activity_monitor.Gfx_BoosterFreq = input[6];
			activity_monitor.Gfx_PD_Data_limit_c = input[7];
			activity_monitor.Gfx_PD_Data_error_coeff = input[8];
			activity_monitor.Gfx_PD_Data_error_rate_coeff = input[9];
			अवरोध;
		हाल 1: /* Uclk */
			activity_monitor.Mem_FPS = input[1];
			activity_monitor.Mem_UseRlcBusy = input[2];
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
				       SMU_TABLE_ACTIVITY_MONITOR_COEFF,
				       WORKLOAD_PPLIB_CUSTOM_BIT,
				       (व्योम *)(&activity_monitor),
				       true);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "[%s] Failed to set activity monitor!", __func__);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Conv PP_SMC_POWER_PROखाता* to WORKLOAD_PPLIB_*_BIT
	 * Not all profile modes are supported on arcturus.
	 */
	workload_type = smu_cmn_to_asic_specअगरic_index(smu,
						       CMN2ASIC_MAPPING_WORKLOAD,
						       profile_mode);
	अगर (workload_type < 0) अणु
		dev_dbg(smu->adev->dev, "Unsupported power profile mode %d on arcturus\n", profile_mode);
		वापस -EINVAL;
	पूर्ण

	ret = smu_cmn_send_smc_msg_with_param(smu,
					  SMU_MSG_SetWorkloadMask,
					  1 << workload_type,
					  शून्य);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "Fail to set workload type %d\n", workload_type);
		वापस ret;
	पूर्ण

	smu->घातer_profile_mode = profile_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक arcturus_set_perक्रमmance_level(काष्ठा smu_context *smu,
					  क्रमागत amd_dpm_क्रमced_level level)
अणु
	uपूर्णांक32_t smu_version;
	पूर्णांक ret;

	ret = smu_cmn_get_smc_version(smu, शून्य, &smu_version);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "Failed to get smu version!\n");
		वापस ret;
	पूर्ण

	चयन (level) अणु
	हाल AMD_DPM_FORCED_LEVEL_HIGH:
	हाल AMD_DPM_FORCED_LEVEL_LOW:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_PEAK:
		अगर ((smu_version >= 0x361200) &&
		    (smu_version <= 0x361a00)) अणु
			dev_err(smu->adev->dev, "Forcing clock level is not supported with "
			       "54.18 - 54.26(included) SMU firmwares\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस smu_v11_0_set_perक्रमmance_level(smu, level);
पूर्ण

अटल व्योम arcturus_dump_pptable(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	PPTable_t *pptable = table_context->driver_pptable;
	पूर्णांक i;

	dev_info(smu->adev->dev, "Dumped PPTable:\n");

	dev_info(smu->adev->dev, "Version = 0x%08x\n", pptable->Version);

	dev_info(smu->adev->dev, "FeaturesToRun[0] = 0x%08x\n", pptable->FeaturesToRun[0]);
	dev_info(smu->adev->dev, "FeaturesToRun[1] = 0x%08x\n", pptable->FeaturesToRun[1]);

	क्रम (i = 0; i < PPT_THROTTLER_COUNT; i++) अणु
		dev_info(smu->adev->dev, "SocketPowerLimitAc[%d] = %d\n", i, pptable->SocketPowerLimitAc[i]);
		dev_info(smu->adev->dev, "SocketPowerLimitAcTau[%d] = %d\n", i, pptable->SocketPowerLimitAcTau[i]);
	पूर्ण

	dev_info(smu->adev->dev, "TdcLimitSoc = %d\n", pptable->TdcLimitSoc);
	dev_info(smu->adev->dev, "TdcLimitSocTau = %d\n", pptable->TdcLimitSocTau);
	dev_info(smu->adev->dev, "TdcLimitGfx = %d\n", pptable->TdcLimitGfx);
	dev_info(smu->adev->dev, "TdcLimitGfxTau = %d\n", pptable->TdcLimitGfxTau);

	dev_info(smu->adev->dev, "TedgeLimit = %d\n", pptable->TedgeLimit);
	dev_info(smu->adev->dev, "ThotspotLimit = %d\n", pptable->ThotspotLimit);
	dev_info(smu->adev->dev, "TmemLimit = %d\n", pptable->TmemLimit);
	dev_info(smu->adev->dev, "Tvr_gfxLimit = %d\n", pptable->Tvr_gfxLimit);
	dev_info(smu->adev->dev, "Tvr_memLimit = %d\n", pptable->Tvr_memLimit);
	dev_info(smu->adev->dev, "Tvr_socLimit = %d\n", pptable->Tvr_socLimit);
	dev_info(smu->adev->dev, "FitLimit = %d\n", pptable->FitLimit);

	dev_info(smu->adev->dev, "PpmPowerLimit = %d\n", pptable->PpmPowerLimit);
	dev_info(smu->adev->dev, "PpmTemperatureThreshold = %d\n", pptable->PpmTemperatureThreshold);

	dev_info(smu->adev->dev, "ThrottlerControlMask = %d\n", pptable->ThrottlerControlMask);

	dev_info(smu->adev->dev, "UlvVoltageOffsetGfx = %d\n", pptable->UlvVoltageOffsetGfx);
	dev_info(smu->adev->dev, "UlvPadding = 0x%08x\n", pptable->UlvPadding);

	dev_info(smu->adev->dev, "UlvGfxclkBypass = %d\n", pptable->UlvGfxclkBypass);
	dev_info(smu->adev->dev, "Padding234[0] = 0x%02x\n", pptable->Padding234[0]);
	dev_info(smu->adev->dev, "Padding234[1] = 0x%02x\n", pptable->Padding234[1]);
	dev_info(smu->adev->dev, "Padding234[2] = 0x%02x\n", pptable->Padding234[2]);

	dev_info(smu->adev->dev, "MinVoltageGfx = %d\n", pptable->MinVoltageGfx);
	dev_info(smu->adev->dev, "MinVoltageSoc = %d\n", pptable->MinVoltageSoc);
	dev_info(smu->adev->dev, "MaxVoltageGfx = %d\n", pptable->MaxVoltageGfx);
	dev_info(smu->adev->dev, "MaxVoltageSoc = %d\n", pptable->MaxVoltageSoc);

	dev_info(smu->adev->dev, "LoadLineResistanceGfx = %d\n", pptable->LoadLineResistanceGfx);
	dev_info(smu->adev->dev, "LoadLineResistanceSoc = %d\n", pptable->LoadLineResistanceSoc);

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
			pptable->DpmDescriptor[PPCLK_GFXCLK].padding,
			pptable->DpmDescriptor[PPCLK_GFXCLK].ConversionToAvfsClk.m,
			pptable->DpmDescriptor[PPCLK_GFXCLK].ConversionToAvfsClk.b,
			pptable->DpmDescriptor[PPCLK_GFXCLK].SsCurve.a,
			pptable->DpmDescriptor[PPCLK_GFXCLK].SsCurve.b,
			pptable->DpmDescriptor[PPCLK_GFXCLK].SsCurve.c,
			pptable->DpmDescriptor[PPCLK_GFXCLK].SsFmin,
			pptable->DpmDescriptor[PPCLK_GFXCLK].Padding16);

	dev_info(smu->adev->dev, "[PPCLK_VCLK]\n"
			"  .VoltageMode          = 0x%02x\n"
			"  .SnapToDiscrete       = 0x%02x\n"
			"  .NumDiscreteLevels    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConversionToAvfsClk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCurve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n"
			"  .SsFmin               = 0x%04x\n"
			"  .Padding_16           = 0x%04x\n",
			pptable->DpmDescriptor[PPCLK_VCLK].VoltageMode,
			pptable->DpmDescriptor[PPCLK_VCLK].SnapToDiscrete,
			pptable->DpmDescriptor[PPCLK_VCLK].NumDiscreteLevels,
			pptable->DpmDescriptor[PPCLK_VCLK].padding,
			pptable->DpmDescriptor[PPCLK_VCLK].ConversionToAvfsClk.m,
			pptable->DpmDescriptor[PPCLK_VCLK].ConversionToAvfsClk.b,
			pptable->DpmDescriptor[PPCLK_VCLK].SsCurve.a,
			pptable->DpmDescriptor[PPCLK_VCLK].SsCurve.b,
			pptable->DpmDescriptor[PPCLK_VCLK].SsCurve.c,
			pptable->DpmDescriptor[PPCLK_VCLK].SsFmin,
			pptable->DpmDescriptor[PPCLK_VCLK].Padding16);

	dev_info(smu->adev->dev, "[PPCLK_DCLK]\n"
			"  .VoltageMode          = 0x%02x\n"
			"  .SnapToDiscrete       = 0x%02x\n"
			"  .NumDiscreteLevels    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConversionToAvfsClk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCurve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n"
			"  .SsFmin               = 0x%04x\n"
			"  .Padding_16           = 0x%04x\n",
			pptable->DpmDescriptor[PPCLK_DCLK].VoltageMode,
			pptable->DpmDescriptor[PPCLK_DCLK].SnapToDiscrete,
			pptable->DpmDescriptor[PPCLK_DCLK].NumDiscreteLevels,
			pptable->DpmDescriptor[PPCLK_DCLK].padding,
			pptable->DpmDescriptor[PPCLK_DCLK].ConversionToAvfsClk.m,
			pptable->DpmDescriptor[PPCLK_DCLK].ConversionToAvfsClk.b,
			pptable->DpmDescriptor[PPCLK_DCLK].SsCurve.a,
			pptable->DpmDescriptor[PPCLK_DCLK].SsCurve.b,
			pptable->DpmDescriptor[PPCLK_DCLK].SsCurve.c,
			pptable->DpmDescriptor[PPCLK_DCLK].SsFmin,
			pptable->DpmDescriptor[PPCLK_DCLK].Padding16);

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
			pptable->DpmDescriptor[PPCLK_SOCCLK].padding,
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
			pptable->DpmDescriptor[PPCLK_UCLK].padding,
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
			pptable->DpmDescriptor[PPCLK_FCLK].padding,
			pptable->DpmDescriptor[PPCLK_FCLK].ConversionToAvfsClk.m,
			pptable->DpmDescriptor[PPCLK_FCLK].ConversionToAvfsClk.b,
			pptable->DpmDescriptor[PPCLK_FCLK].SsCurve.a,
			pptable->DpmDescriptor[PPCLK_FCLK].SsCurve.b,
			pptable->DpmDescriptor[PPCLK_FCLK].SsCurve.c,
			pptable->DpmDescriptor[PPCLK_FCLK].SsFmin,
			pptable->DpmDescriptor[PPCLK_FCLK].Padding16);


	dev_info(smu->adev->dev, "FreqTableGfx\n");
	क्रम (i = 0; i < NUM_GFXCLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = %d\n", i, pptable->FreqTableGfx[i]);

	dev_info(smu->adev->dev, "FreqTableVclk\n");
	क्रम (i = 0; i < NUM_VCLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = %d\n", i, pptable->FreqTableVclk[i]);

	dev_info(smu->adev->dev, "FreqTableDclk\n");
	क्रम (i = 0; i < NUM_DCLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = %d\n", i, pptable->FreqTableDclk[i]);

	dev_info(smu->adev->dev, "FreqTableSocclk\n");
	क्रम (i = 0; i < NUM_SOCCLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = %d\n", i, pptable->FreqTableSocclk[i]);

	dev_info(smu->adev->dev, "FreqTableUclk\n");
	क्रम (i = 0; i < NUM_UCLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = %d\n", i, pptable->FreqTableUclk[i]);

	dev_info(smu->adev->dev, "FreqTableFclk\n");
	क्रम (i = 0; i < NUM_FCLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = %d\n", i, pptable->FreqTableFclk[i]);

	dev_info(smu->adev->dev, "Mp0clkFreq\n");
	क्रम (i = 0; i < NUM_MP0CLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = %d\n", i, pptable->Mp0clkFreq[i]);

	dev_info(smu->adev->dev, "Mp0DpmVoltage\n");
	क्रम (i = 0; i < NUM_MP0CLK_DPM_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = %d\n", i, pptable->Mp0DpmVoltage[i]);

	dev_info(smu->adev->dev, "GfxclkFidle = 0x%x\n", pptable->GfxclkFidle);
	dev_info(smu->adev->dev, "GfxclkSlewRate = 0x%x\n", pptable->GfxclkSlewRate);
	dev_info(smu->adev->dev, "Padding567[0] = 0x%x\n", pptable->Padding567[0]);
	dev_info(smu->adev->dev, "Padding567[1] = 0x%x\n", pptable->Padding567[1]);
	dev_info(smu->adev->dev, "Padding567[2] = 0x%x\n", pptable->Padding567[2]);
	dev_info(smu->adev->dev, "Padding567[3] = 0x%x\n", pptable->Padding567[3]);
	dev_info(smu->adev->dev, "GfxclkDsMaxFreq = %d\n", pptable->GfxclkDsMaxFreq);
	dev_info(smu->adev->dev, "GfxclkSource = 0x%x\n", pptable->GfxclkSource);
	dev_info(smu->adev->dev, "Padding456 = 0x%x\n", pptable->Padding456);

	dev_info(smu->adev->dev, "EnableTdpm = %d\n", pptable->EnableTdpm);
	dev_info(smu->adev->dev, "TdpmHighHystTemperature = %d\n", pptable->TdpmHighHystTemperature);
	dev_info(smu->adev->dev, "TdpmLowHystTemperature = %d\n", pptable->TdpmLowHystTemperature);
	dev_info(smu->adev->dev, "GfxclkFreqHighTempLimit = %d\n", pptable->GfxclkFreqHighTempLimit);

	dev_info(smu->adev->dev, "FanStopTemp = %d\n", pptable->FanStopTemp);
	dev_info(smu->adev->dev, "FanStartTemp = %d\n", pptable->FanStartTemp);

	dev_info(smu->adev->dev, "FanGainEdge = %d\n", pptable->FanGainEdge);
	dev_info(smu->adev->dev, "FanGainHotspot = %d\n", pptable->FanGainHotspot);
	dev_info(smu->adev->dev, "FanGainVrGfx = %d\n", pptable->FanGainVrGfx);
	dev_info(smu->adev->dev, "FanGainVrSoc = %d\n", pptable->FanGainVrSoc);
	dev_info(smu->adev->dev, "FanGainVrMem = %d\n", pptable->FanGainVrMem);
	dev_info(smu->adev->dev, "FanGainHbm = %d\n", pptable->FanGainHbm);

	dev_info(smu->adev->dev, "FanPwmMin = %d\n", pptable->FanPwmMin);
	dev_info(smu->adev->dev, "FanAcousticLimitRpm = %d\n", pptable->FanAcousticLimitRpm);
	dev_info(smu->adev->dev, "FanThrottlingRpm = %d\n", pptable->FanThrottlingRpm);
	dev_info(smu->adev->dev, "FanMaximumRpm = %d\n", pptable->FanMaximumRpm);
	dev_info(smu->adev->dev, "FanTargetTemperature = %d\n", pptable->FanTargetTemperature);
	dev_info(smu->adev->dev, "FanTargetGfxclk = %d\n", pptable->FanTargetGfxclk);
	dev_info(smu->adev->dev, "FanZeroRpmEnable = %d\n", pptable->FanZeroRpmEnable);
	dev_info(smu->adev->dev, "FanTachEdgePerRev = %d\n", pptable->FanTachEdgePerRev);
	dev_info(smu->adev->dev, "FanTempInputSelect = %d\n", pptable->FanTempInputSelect);

	dev_info(smu->adev->dev, "FuzzyFan_ErrorSetDelta = %d\n", pptable->FuzzyFan_ErrorSetDelta);
	dev_info(smu->adev->dev, "FuzzyFan_ErrorRateSetDelta = %d\n", pptable->FuzzyFan_ErrorRateSetDelta);
	dev_info(smu->adev->dev, "FuzzyFan_PwmSetDelta = %d\n", pptable->FuzzyFan_PwmSetDelta);
	dev_info(smu->adev->dev, "FuzzyFan_Reserved = %d\n", pptable->FuzzyFan_Reserved);

	dev_info(smu->adev->dev, "OverrideAvfsGb[AVFS_VOLTAGE_GFX] = 0x%x\n", pptable->OverrideAvfsGb[AVFS_VOLTAGE_GFX]);
	dev_info(smu->adev->dev, "OverrideAvfsGb[AVFS_VOLTAGE_SOC] = 0x%x\n", pptable->OverrideAvfsGb[AVFS_VOLTAGE_SOC]);
	dev_info(smu->adev->dev, "Padding8_Avfs[0] = %d\n", pptable->Padding8_Avfs[0]);
	dev_info(smu->adev->dev, "Padding8_Avfs[1] = %d\n", pptable->Padding8_Avfs[1]);

	dev_info(smu->adev->dev, "dBtcGbGfxPll{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptable->dBtcGbGfxPll.a,
			pptable->dBtcGbGfxPll.b,
			pptable->dBtcGbGfxPll.c);
	dev_info(smu->adev->dev, "dBtcGbGfxAfll{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptable->dBtcGbGfxAfll.a,
			pptable->dBtcGbGfxAfll.b,
			pptable->dBtcGbGfxAfll.c);
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
		dev_info(smu->adev->dev, "  .[%d] = %d\n", i, pptable->XgmiDpmPstates[i]);
	dev_info(smu->adev->dev, "XgmiDpmSpare[0] = 0x%02x\n", pptable->XgmiDpmSpare[0]);
	dev_info(smu->adev->dev, "XgmiDpmSpare[1] = 0x%02x\n", pptable->XgmiDpmSpare[1]);

	dev_info(smu->adev->dev, "VDDGFX_TVmin = %d\n", pptable->VDDGFX_TVmin);
	dev_info(smu->adev->dev, "VDDSOC_TVmin = %d\n", pptable->VDDSOC_TVmin);
	dev_info(smu->adev->dev, "VDDGFX_Vmin_HiTemp = %d\n", pptable->VDDGFX_Vmin_HiTemp);
	dev_info(smu->adev->dev, "VDDGFX_Vmin_LoTemp = %d\n", pptable->VDDGFX_Vmin_LoTemp);
	dev_info(smu->adev->dev, "VDDSOC_Vmin_HiTemp = %d\n", pptable->VDDSOC_Vmin_HiTemp);
	dev_info(smu->adev->dev, "VDDSOC_Vmin_LoTemp = %d\n", pptable->VDDSOC_Vmin_LoTemp);
	dev_info(smu->adev->dev, "VDDGFX_TVminHystersis = %d\n", pptable->VDDGFX_TVminHystersis);
	dev_info(smu->adev->dev, "VDDSOC_TVminHystersis = %d\n", pptable->VDDSOC_TVminHystersis);

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

	dev_info(smu->adev->dev, "MinVoltageUlvGfx = %d\n", pptable->MinVoltageUlvGfx);
	dev_info(smu->adev->dev, "PaddingUlv = %d\n", pptable->PaddingUlv);

	dev_info(smu->adev->dev, "TotalPowerConfig = %d\n", pptable->TotalPowerConfig);
	dev_info(smu->adev->dev, "TotalPowerSpare1 = %d\n", pptable->TotalPowerSpare1);
	dev_info(smu->adev->dev, "TotalPowerSpare2 = %d\n", pptable->TotalPowerSpare2);

	dev_info(smu->adev->dev, "PccThresholdLow = %d\n", pptable->PccThresholdLow);
	dev_info(smu->adev->dev, "PccThresholdHigh = %d\n", pptable->PccThresholdHigh);

	dev_info(smu->adev->dev, "Board Parameters:\n");
	dev_info(smu->adev->dev, "MaxVoltageStepGfx = 0x%x\n", pptable->MaxVoltageStepGfx);
	dev_info(smu->adev->dev, "MaxVoltageStepSoc = 0x%x\n", pptable->MaxVoltageStepSoc);

	dev_info(smu->adev->dev, "VddGfxVrMapping = 0x%x\n", pptable->VddGfxVrMapping);
	dev_info(smu->adev->dev, "VddSocVrMapping = 0x%x\n", pptable->VddSocVrMapping);
	dev_info(smu->adev->dev, "VddMemVrMapping = 0x%x\n", pptable->VddMemVrMapping);
	dev_info(smu->adev->dev, "BoardVrMapping = 0x%x\n", pptable->BoardVrMapping);

	dev_info(smu->adev->dev, "GfxUlvPhaseSheddingMask = 0x%x\n", pptable->GfxUlvPhaseSheddingMask);
	dev_info(smu->adev->dev, "ExternalSensorPresent = 0x%x\n", pptable->ExternalSensorPresent);

	dev_info(smu->adev->dev, "GfxMaxCurrent = 0x%x\n", pptable->GfxMaxCurrent);
	dev_info(smu->adev->dev, "GfxOffset = 0x%x\n", pptable->GfxOffset);
	dev_info(smu->adev->dev, "Padding_TelemetryGfx = 0x%x\n", pptable->Padding_TelemetryGfx);

	dev_info(smu->adev->dev, "SocMaxCurrent = 0x%x\n", pptable->SocMaxCurrent);
	dev_info(smu->adev->dev, "SocOffset = 0x%x\n", pptable->SocOffset);
	dev_info(smu->adev->dev, "Padding_TelemetrySoc = 0x%x\n", pptable->Padding_TelemetrySoc);

	dev_info(smu->adev->dev, "MemMaxCurrent = 0x%x\n", pptable->MemMaxCurrent);
	dev_info(smu->adev->dev, "MemOffset = 0x%x\n", pptable->MemOffset);
	dev_info(smu->adev->dev, "Padding_TelemetryMem = 0x%x\n", pptable->Padding_TelemetryMem);

	dev_info(smu->adev->dev, "BoardMaxCurrent = 0x%x\n", pptable->BoardMaxCurrent);
	dev_info(smu->adev->dev, "BoardOffset = 0x%x\n", pptable->BoardOffset);
	dev_info(smu->adev->dev, "Padding_TelemetryBoardInput = 0x%x\n", pptable->Padding_TelemetryBoardInput);

	dev_info(smu->adev->dev, "VR0HotGpio = %d\n", pptable->VR0HotGpio);
	dev_info(smu->adev->dev, "VR0HotPolarity = %d\n", pptable->VR0HotPolarity);
	dev_info(smu->adev->dev, "VR1HotGpio = %d\n", pptable->VR1HotGpio);
	dev_info(smu->adev->dev, "VR1HotPolarity = %d\n", pptable->VR1HotPolarity);

	dev_info(smu->adev->dev, "PllGfxclkSpreadEnabled = %d\n", pptable->PllGfxclkSpपढ़ोEnabled);
	dev_info(smu->adev->dev, "PllGfxclkSpreadPercent = %d\n", pptable->PllGfxclkSpपढ़ोPercent);
	dev_info(smu->adev->dev, "PllGfxclkSpreadFreq = %d\n", pptable->PllGfxclkSpपढ़ोFreq);

	dev_info(smu->adev->dev, "UclkSpreadEnabled = %d\n", pptable->UclkSpपढ़ोEnabled);
	dev_info(smu->adev->dev, "UclkSpreadPercent = %d\n", pptable->UclkSpपढ़ोPercent);
	dev_info(smu->adev->dev, "UclkSpreadFreq = %d\n", pptable->UclkSpपढ़ोFreq);

	dev_info(smu->adev->dev, "FclkSpreadEnabled = %d\n", pptable->FclkSpपढ़ोEnabled);
	dev_info(smu->adev->dev, "FclkSpreadPercent = %d\n", pptable->FclkSpपढ़ोPercent);
	dev_info(smu->adev->dev, "FclkSpreadFreq = %d\n", pptable->FclkSpपढ़ोFreq);

	dev_info(smu->adev->dev, "FllGfxclkSpreadEnabled = %d\n", pptable->FllGfxclkSpपढ़ोEnabled);
	dev_info(smu->adev->dev, "FllGfxclkSpreadPercent = %d\n", pptable->FllGfxclkSpपढ़ोPercent);
	dev_info(smu->adev->dev, "FllGfxclkSpreadFreq = %d\n", pptable->FllGfxclkSpपढ़ोFreq);

	क्रम (i = 0; i < NUM_I2C_CONTROLLERS; i++) अणु
		dev_info(smu->adev->dev, "I2cControllers[%d]:\n", i);
		dev_info(smu->adev->dev, "                   .Enabled = %d\n",
				pptable->I2cControllers[i].Enabled);
		dev_info(smu->adev->dev, "                   .SlaveAddress = 0x%x\n",
				pptable->I2cControllers[i].SlaveAddress);
		dev_info(smu->adev->dev, "                   .ControllerPort = %d\n",
				pptable->I2cControllers[i].ControllerPort);
		dev_info(smu->adev->dev, "                   .ControllerName = %d\n",
				pptable->I2cControllers[i].ControllerName);
		dev_info(smu->adev->dev, "                   .ThermalThrottler = %d\n",
				pptable->I2cControllers[i].ThermalThrotter);
		dev_info(smu->adev->dev, "                   .I2cProtocol = %d\n",
				pptable->I2cControllers[i].I2cProtocol);
		dev_info(smu->adev->dev, "                   .Speed = %d\n",
				pptable->I2cControllers[i].Speed);
	पूर्ण

	dev_info(smu->adev->dev, "MemoryChannelEnabled = %d\n", pptable->MemoryChannelEnabled);
	dev_info(smu->adev->dev, "DramBitWidth = %d\n", pptable->DramBitWidth);

	dev_info(smu->adev->dev, "TotalBoardPower = %d\n", pptable->TotalBoardPower);

	dev_info(smu->adev->dev, "XgmiLinkSpeed\n");
	क्रम (i = 0; i < NUM_XGMI_PSTATE_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = %d\n", i, pptable->XgmiLinkSpeed[i]);
	dev_info(smu->adev->dev, "XgmiLinkWidth\n");
	क्रम (i = 0; i < NUM_XGMI_PSTATE_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = %d\n", i, pptable->XgmiLinkWidth[i]);
	dev_info(smu->adev->dev, "XgmiFclkFreq\n");
	क्रम (i = 0; i < NUM_XGMI_PSTATE_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = %d\n", i, pptable->XgmiFclkFreq[i]);
	dev_info(smu->adev->dev, "XgmiSocVoltage\n");
	क्रम (i = 0; i < NUM_XGMI_PSTATE_LEVELS; i++)
		dev_info(smu->adev->dev, "  .[%d] = %d\n", i, pptable->XgmiSocVoltage[i]);

पूर्ण

अटल bool arcturus_is_dpm_running(काष्ठा smu_context *smu)
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

अटल पूर्णांक arcturus_dpm_set_vcn_enable(काष्ठा smu_context *smu, bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (enable) अणु
		अगर (!smu_cmn_feature_is_enabled(smu, SMU_FEATURE_VCN_PG_BIT)) अणु
			ret = smu_cmn_feature_set_enabled(smu, SMU_FEATURE_VCN_PG_BIT, 1);
			अगर (ret) अणु
				dev_err(smu->adev->dev, "[EnableVCNDPM] failed!\n");
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_VCN_PG_BIT)) अणु
			ret = smu_cmn_feature_set_enabled(smu, SMU_FEATURE_VCN_PG_BIT, 0);
			अगर (ret) अणु
				dev_err(smu->adev->dev, "[DisableVCNDPM] failed!\n");
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम arcturus_fill_i2c_req(SwI2cRequest_t  *req, bool ग_लिखो,
				  uपूर्णांक8_t address, uपूर्णांक32_t numbytes,
				  uपूर्णांक8_t *data)
अणु
	पूर्णांक i;

	req->I2CcontrollerPort = 0;
	req->I2CSpeed = 2;
	req->SlaveAddress = address;
	req->NumCmds = numbytes;

	क्रम (i = 0; i < numbytes; i++) अणु
		SwI2cCmd_t *cmd =  &req->SwI2cCmds[i];

		/* First 2 bytes are always ग_लिखो क्रम lower 2b EEPROM address */
		अगर (i < 2)
			cmd->Cmd = 1;
		अन्यथा
			cmd->Cmd = ग_लिखो;


		/* Add RESTART क्रम पढ़ो  after address filled */
		cmd->CmdConfig |= (i == 2 && !ग_लिखो) ? CMDCONFIG_RESTART_MASK : 0;

		/* Add STOP in the end */
		cmd->CmdConfig |= (i == (numbytes - 1)) ? CMDCONFIG_STOP_MASK : 0;

		/* Fill with data regardless अगर पढ़ो or ग_लिखो to simplअगरy code */
		cmd->RegisterAddr = data[i];
	पूर्ण
पूर्ण

अटल पूर्णांक arcturus_i2c_पढ़ो_data(काष्ठा i2c_adapter *control,
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
	arcturus_fill_i2c_req(&req, false, address, numbytes, data);

	mutex_lock(&adev->smu.mutex);
	/* Now पढ़ो data starting with that address */
	ret = smu_cmn_update_table(&adev->smu, SMU_TABLE_I2C_COMMANDS, 0, &req,
					true);
	mutex_unlock(&adev->smu.mutex);

	अगर (!ret) अणु
		SwI2cRequest_t *res = (SwI2cRequest_t *)table->cpu_addr;

		/* Assume SMU  fills res.SwI2cCmds[i].Data with पढ़ो bytes */
		क्रम (i = 0; i < numbytes; i++)
			data[i] = res->SwI2cCmds[i].Data;

		dev_dbg(adev->dev, "arcturus_i2c_read_data, address = %x, bytes = %d, data :",
				  (uपूर्णांक16_t)address, numbytes);

		prपूर्णांक_hex_dump(KERN_DEBUG, "data: ", DUMP_PREFIX_NONE,
			       8, 1, data, numbytes, false);
	पूर्ण अन्यथा
		dev_err(adev->dev, "arcturus_i2c_read_data - error occurred :%x", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक arcturus_i2c_ग_लिखो_data(काष्ठा i2c_adapter *control,
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
	arcturus_fill_i2c_req(&req, true, address, numbytes, data);

	mutex_lock(&adev->smu.mutex);
	ret = smu_cmn_update_table(&adev->smu, SMU_TABLE_I2C_COMMANDS, 0, &req, true);
	mutex_unlock(&adev->smu.mutex);

	अगर (!ret) अणु
		dev_dbg(adev->dev, "arcturus_i2c_write(), address = %x, bytes = %d , data: ",
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
		dev_err(adev->dev, "arcturus_i2c_write- error occurred :%x", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक arcturus_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
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
				ret = arcturus_i2c_पढ़ो_data(i2c_adap,
							     (uपूर्णांक8_t)msgs[i].addr,
							     data_chunk, MAX_SW_I2C_COMMANDS);

				स_नकल(data_ptr, data_chunk + 2, data_chunk_size);
			पूर्ण अन्यथा अणु

				स_नकल(data_chunk + 2, data_ptr, data_chunk_size);

				ret = arcturus_i2c_ग_लिखो_data(i2c_adap,
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
				ret = arcturus_i2c_पढ़ो_data(i2c_adap,
							     (uपूर्णांक8_t)msgs[i].addr,
							     data_chunk, (data_size % data_chunk_size) + 2);

				स_नकल(data_ptr, data_chunk + 2, data_size % data_chunk_size);
			पूर्ण अन्यथा अणु
				स_नकल(data_chunk + 2, data_ptr, data_size % data_chunk_size);

				ret = arcturus_i2c_ग_लिखो_data(i2c_adap,
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

अटल u32 arcturus_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण


अटल स्थिर काष्ठा i2c_algorithm arcturus_i2c_algo = अणु
	.master_xfer = arcturus_i2c_xfer,
	.functionality = arcturus_i2c_func,
पूर्ण;

अटल पूर्णांक arcturus_i2c_control_init(काष्ठा smu_context *smu, काष्ठा i2c_adapter *control)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);
	पूर्णांक res;

	control->owner = THIS_MODULE;
	control->class = I2C_CLASS_SPD;
	control->dev.parent = &adev->pdev->dev;
	control->algo = &arcturus_i2c_algo;
	snम_लिखो(control->name, माप(control->name), "AMDGPU SMU");

	res = i2c_add_adapter(control);
	अगर (res)
		DRM_ERROR("Failed to register hw i2c, err: %d\n", res);

	वापस res;
पूर्ण

अटल व्योम arcturus_i2c_control_fini(काष्ठा smu_context *smu, काष्ठा i2c_adapter *control)
अणु
	i2c_del_adapter(control);
पूर्ण

अटल व्योम arcturus_get_unique_id(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t top32 = 0, bottom32 = 0, smu_version;
	uपूर्णांक64_t id;

	अगर (smu_cmn_get_smc_version(smu, शून्य, &smu_version)) अणु
		dev_warn(adev->dev, "Failed to get smu version, cannot get unique_id or serial_number\n");
		वापस;
	पूर्ण

	/* PPSMC_MSG_ReadSerial* is supported by 54.23.0 and onwards */
	अगर (smu_version < 0x361700) अणु
		dev_warn(adev->dev, "ReadSerial is only supported by PMFW 54.23.0 and onwards\n");
		वापस;
	पूर्ण

	/* Get the SN to turn पूर्णांकo a Unique ID */
	smu_cmn_send_smc_msg(smu, SMU_MSG_ReadSerialNumTop32, &top32);
	smu_cmn_send_smc_msg(smu, SMU_MSG_ReadSerialNumBottom32, &bottom32);

	id = ((uपूर्णांक64_t)bottom32 << 32) | top32;
	adev->unique_id = id;
	/* For Arcturus-and-later, unique_id == serial_number, so convert it to a
	 * 16-digit HEX string क्रम convenience and backwards-compatibility
	 */
	प्र_लिखो(adev->serial, "%llx", id);
पूर्ण

अटल bool arcturus_is_baco_supported(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t val;

	अगर (!smu_v11_0_baco_is_support(smu) || amdgpu_sriov_vf(adev))
		वापस false;

	val = RREG32_SOC15(NBIO, 0, mmRCC_BIF_STRAP0);
	वापस (val & RCC_BIF_STRAP0__STRAP_PX_CAPABLE_MASK) ? true : false;
पूर्ण

अटल पूर्णांक arcturus_set_df_cstate(काष्ठा smu_context *smu,
				  क्रमागत pp_df_cstate state)
अणु
	uपूर्णांक32_t smu_version;
	पूर्णांक ret;

	ret = smu_cmn_get_smc_version(smu, शून्य, &smu_version);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "Failed to get smu version!\n");
		वापस ret;
	पूर्ण

	/* PPSMC_MSG_DFCstateControl is supported by 54.15.0 and onwards */
	अगर (smu_version < 0x360F00) अणु
		dev_err(smu->adev->dev, "DFCstateControl is only supported by PMFW 54.15.0 and onwards\n");
		वापस -EINVAL;
	पूर्ण

	वापस smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_DFCstateControl, state, शून्य);
पूर्ण

अटल पूर्णांक arcturus_allow_xgmi_घातer_करोwn(काष्ठा smu_context *smu, bool en)
अणु
	uपूर्णांक32_t smu_version;
	पूर्णांक ret;

	ret = smu_cmn_get_smc_version(smu, शून्य, &smu_version);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "Failed to get smu version!\n");
		वापस ret;
	पूर्ण

	/* PPSMC_MSG_GmiPwrDnControl is supported by 54.23.0 and onwards */
	अगर (smu_version < 0x00361700) अणु
		dev_err(smu->adev->dev, "XGMI power down control is only supported by PMFW 54.23.0 and onwards\n");
		वापस -EINVAL;
	पूर्ण

	अगर (en)
		वापस smu_cmn_send_smc_msg_with_param(smu,
						   SMU_MSG_GmiPwrDnControl,
						   1,
						   शून्य);

	वापस smu_cmn_send_smc_msg_with_param(smu,
					   SMU_MSG_GmiPwrDnControl,
					   0,
					   शून्य);
पूर्ण

अटल स्थिर काष्ठा throttling_logging_label अणु
	uपूर्णांक32_t feature_mask;
	स्थिर अक्षर *label;
पूर्ण logging_label[] = अणु
	अणु(1U << THROTTLER_TEMP_HOTSPOT_BIT), "GPU"पूर्ण,
	अणु(1U << THROTTLER_TEMP_MEM_BIT), "HBM"पूर्ण,
	अणु(1U << THROTTLER_TEMP_VR_GFX_BIT), "VR of GFX rail"पूर्ण,
	अणु(1U << THROTTLER_TEMP_VR_MEM_BIT), "VR of HBM rail"पूर्ण,
	अणु(1U << THROTTLER_TEMP_VR_SOC_BIT), "VR of SOC rail"पूर्ण,
	अणु(1U << THROTTLER_VRHOT0_BIT), "VR0 HOT"पूर्ण,
	अणु(1U << THROTTLER_VRHOT1_BIT), "VR1 HOT"पूर्ण,
पूर्ण;
अटल व्योम arcturus_log_thermal_throttling_event(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret;
	पूर्णांक throttler_idx, throtting_events = 0, buf_idx = 0;
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t throttler_status;
	अक्षर log_buf[256];

	ret = arcturus_get_smu_metrics_data(smu,
					    METRICS_THROTTLER_STATUS,
					    &throttler_status);
	अगर (ret)
		वापस;

	स_रखो(log_buf, 0, माप(log_buf));
	क्रम (throttler_idx = 0; throttler_idx < ARRAY_SIZE(logging_label);
	     throttler_idx++) अणु
		अगर (throttler_status & logging_label[throttler_idx].feature_mask) अणु
			throtting_events++;
			buf_idx += snम_लिखो(log_buf + buf_idx,
					    माप(log_buf) - buf_idx,
					    "%s%s",
					    throtting_events > 1 ? " and " : "",
					    logging_label[throttler_idx].label);
			अगर (buf_idx >= माप(log_buf)) अणु
				dev_err(adev->dev, "buffer overflow!\n");
				log_buf[माप(log_buf) - 1] = '\0';
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	dev_warn(adev->dev, "WARN: GPU thermal throttling temperature reached, expect performance decrease. %s.\n",
			log_buf);
	kgd2kfd_smi_event_throttle(smu->adev->kfd.dev, throttler_status);
पूर्ण

अटल uपूर्णांक16_t arcturus_get_current_pcie_link_speed(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t esm_ctrl;

	/* TODO: confirm this on real target */
	esm_ctrl = RREG32_PCIE(smnPCIE_ESM_CTRL);
	अगर ((esm_ctrl >> 15) & 0x1FFFF)
		वापस (uपूर्णांक16_t)(((esm_ctrl >> 8) & 0x3F) + 128);

	वापस smu_v11_0_get_current_pcie_link_speed(smu);
पूर्ण

अटल sमाप_प्रकार arcturus_get_gpu_metrics(काष्ठा smu_context *smu,
					व्योम **table)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा gpu_metrics_v1_1 *gpu_metrics =
		(काष्ठा gpu_metrics_v1_1 *)smu_table->gpu_metrics_table;
	SmuMetrics_t metrics;
	पूर्णांक ret = 0;

	ret = smu_cmn_get_metrics_table(smu,
					&metrics,
					true);
	अगर (ret)
		वापस ret;

	smu_cmn_init_soft_gpu_metrics(gpu_metrics, 1, 1);

	gpu_metrics->temperature_edge = metrics.TemperatureEdge;
	gpu_metrics->temperature_hotspot = metrics.TemperatureHotspot;
	gpu_metrics->temperature_mem = metrics.TemperatureHBM;
	gpu_metrics->temperature_vrgfx = metrics.TemperatureVrGfx;
	gpu_metrics->temperature_vrsoc = metrics.TemperatureVrSoc;
	gpu_metrics->temperature_vrmem = metrics.TemperatureVrMem;

	gpu_metrics->average_gfx_activity = metrics.AverageGfxActivity;
	gpu_metrics->average_umc_activity = metrics.AverageUclkActivity;
	gpu_metrics->average_mm_activity = metrics.VcnActivityPercentage;

	gpu_metrics->average_socket_घातer = metrics.AverageSocketPower;
	gpu_metrics->energy_accumulator = metrics.EnergyAccumulator;

	gpu_metrics->average_gfxclk_frequency = metrics.AverageGfxclkFrequency;
	gpu_metrics->average_socclk_frequency = metrics.AverageSocclkFrequency;
	gpu_metrics->average_uclk_frequency = metrics.AverageUclkFrequency;
	gpu_metrics->average_vclk0_frequency = metrics.AverageVclkFrequency;
	gpu_metrics->average_dclk0_frequency = metrics.AverageDclkFrequency;

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
			arcturus_get_current_pcie_link_speed(smu);

	gpu_metrics->प्रणाली_घड़ी_counter = kसमय_get_bootसमय_ns();

	*table = (व्योम *)gpu_metrics;

	वापस माप(काष्ठा gpu_metrics_v1_1);
पूर्ण

अटल स्थिर काष्ठा pptable_funcs arcturus_ppt_funcs = अणु
	/* init dpm */
	.get_allowed_feature_mask = arcturus_get_allowed_feature_mask,
	/* btc */
	.run_btc = arcturus_run_btc,
	/* dpm/clk tables */
	.set_शेष_dpm_table = arcturus_set_शेष_dpm_table,
	.populate_umd_state_clk = arcturus_populate_umd_state_clk,
	.get_thermal_temperature_range = arcturus_get_thermal_temperature_range,
	.prपूर्णांक_clk_levels = arcturus_prपूर्णांक_clk_levels,
	.क्रमce_clk_levels = arcturus_क्रमce_clk_levels,
	.पढ़ो_sensor = arcturus_पढ़ो_sensor,
	.get_fan_speed_percent = arcturus_get_fan_speed_percent,
	.get_घातer_profile_mode = arcturus_get_घातer_profile_mode,
	.set_घातer_profile_mode = arcturus_set_घातer_profile_mode,
	.set_perक्रमmance_level = arcturus_set_perक्रमmance_level,
	/* debug (पूर्णांकernal used) */
	.dump_pptable = arcturus_dump_pptable,
	.get_घातer_limit = arcturus_get_घातer_limit,
	.is_dpm_running = arcturus_is_dpm_running,
	.dpm_set_vcn_enable = arcturus_dpm_set_vcn_enable,
	.i2c_init = arcturus_i2c_control_init,
	.i2c_fini = arcturus_i2c_control_fini,
	.get_unique_id = arcturus_get_unique_id,
	.init_microcode = smu_v11_0_init_microcode,
	.load_microcode = smu_v11_0_load_microcode,
	.fini_microcode = smu_v11_0_fini_microcode,
	.init_smc_tables = arcturus_init_smc_tables,
	.fini_smc_tables = smu_v11_0_fini_smc_tables,
	.init_घातer = smu_v11_0_init_घातer,
	.fini_घातer = smu_v11_0_fini_घातer,
	.check_fw_status = smu_v11_0_check_fw_status,
	/* pptable related */
	.setup_pptable = arcturus_setup_pptable,
	.get_vbios_bootup_values = smu_v11_0_get_vbios_bootup_values,
	.check_fw_version = smu_v11_0_check_fw_version,
	.ग_लिखो_pptable = smu_cmn_ग_लिखो_pptable,
	.set_driver_table_location = smu_v11_0_set_driver_table_location,
	.set_tool_table_location = smu_v11_0_set_tool_table_location,
	.notअगरy_memory_pool_location = smu_v11_0_notअगरy_memory_pool_location,
	.प्रणाली_features_control = smu_v11_0_प्रणाली_features_control,
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
	.baco_is_support= arcturus_is_baco_supported,
	.baco_get_state = smu_v11_0_baco_get_state,
	.baco_set_state = smu_v11_0_baco_set_state,
	.baco_enter = smu_v11_0_baco_enter,
	.baco_निकास = smu_v11_0_baco_निकास,
	.get_dpm_ultimate_freq = smu_v11_0_get_dpm_ultimate_freq,
	.set_soft_freq_limited_range = smu_v11_0_set_soft_freq_limited_range,
	.set_df_cstate = arcturus_set_df_cstate,
	.allow_xgmi_घातer_करोwn = arcturus_allow_xgmi_घातer_करोwn,
	.log_thermal_throttling_event = arcturus_log_thermal_throttling_event,
	.get_pp_feature_mask = smu_cmn_get_pp_feature_mask,
	.set_pp_feature_mask = smu_cmn_set_pp_feature_mask,
	.get_gpu_metrics = arcturus_get_gpu_metrics,
	.gfx_ulv_control = smu_v11_0_gfx_ulv_control,
	.deep_sleep_control = smu_v11_0_deep_sleep_control,
	.get_fan_parameters = arcturus_get_fan_parameters,
	.पूर्णांकerrupt_work = smu_v11_0_पूर्णांकerrupt_work,
	.set_light_sbr = smu_v11_0_set_light_sbr,
	.set_mp1_state = smu_cmn_set_mp1_state,
पूर्ण;

व्योम arcturus_set_ppt_funcs(काष्ठा smu_context *smu)
अणु
	smu->ppt_funcs = &arcturus_ppt_funcs;
	smu->message_map = arcturus_message_map;
	smu->घड़ी_map = arcturus_clk_map;
	smu->feature_map = arcturus_feature_mask_map;
	smu->table_map = arcturus_table_map;
	smu->pwr_src_map = arcturus_pwr_src_map;
	smu->workload_map = arcturus_workload_map;
पूर्ण
