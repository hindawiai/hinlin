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
#समावेश "smu_v13_0.h"
#समावेश "smu13_driver_if_aldebaran.h"
#समावेश "soc15_common.h"
#समावेश "atom.h"
#समावेश "power_state.h"
#समावेश "aldebaran_ppt.h"
#समावेश "smu_v13_0_pptable.h"
#समावेश "aldebaran_ppsmc.h"
#समावेश "nbio/nbio_7_4_offset.h"
#समावेश "nbio/nbio_7_4_sh_mask.h"
#समावेश "thm/thm_11_0_2_offset.h"
#समावेश "thm/thm_11_0_2_sh_mask.h"
#समावेश "amdgpu_xgmi.h"
#समावेश <linux/pci.h>
#समावेश "amdgpu_ras.h"
#समावेश "smu_cmn.h"
#समावेश "mp/mp_13_0_2_offset.h"

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

#घोषणा ALDEBARAN_FEA_MAP(smu_feature, aldebaran_feature) \
	[smu_feature] = अणु1, (aldebaran_feature)पूर्ण

#घोषणा FEATURE_MASK(feature) (1ULL << feature)
#घोषणा SMC_DPM_FEATURE ( \
			  FEATURE_MASK(FEATURE_DATA_CALCULATIONS) | \
			  FEATURE_MASK(FEATURE_DPM_GFXCLK_BIT)	| \
			  FEATURE_MASK(FEATURE_DPM_UCLK_BIT)	| \
			  FEATURE_MASK(FEATURE_DPM_SOCCLK_BIT)	| \
			  FEATURE_MASK(FEATURE_DPM_FCLK_BIT)	| \
			  FEATURE_MASK(FEATURE_DPM_LCLK_BIT)	| \
			  FEATURE_MASK(FEATURE_DPM_XGMI_BIT)	| \
			  FEATURE_MASK(FEATURE_DPM_VCN_BIT))

/* possible frequency drअगरt (1Mhz) */
#घोषणा EPSILON				1

#घोषणा smnPCIE_ESM_CTRL			0x111003D0

#घोषणा CLOCK_VALID (1 << 31)

अटल स्थिर काष्ठा cmn2asic_msg_mapping aldebaran_message_map[SMU_MSG_MAX_COUNT] = अणु
	MSG_MAP(TestMessage,			     PPSMC_MSG_TestMessage,			0),
	MSG_MAP(GetSmuVersion,			     PPSMC_MSG_GetSmuVersion,			1),
	MSG_MAP(GetDriverIfVersion,		     PPSMC_MSG_GetDriverIfVersion,		1),
	MSG_MAP(EnableAllSmuFeatures,		     PPSMC_MSG_EnableAllSmuFeatures,		0),
	MSG_MAP(DisableAllSmuFeatures,		     PPSMC_MSG_DisableAllSmuFeatures,		0),
	MSG_MAP(GetEnabledSmuFeaturesLow,	     PPSMC_MSG_GetEnabledSmuFeaturesLow,	0),
	MSG_MAP(GetEnabledSmuFeaturesHigh,	     PPSMC_MSG_GetEnabledSmuFeaturesHigh,	0),
	MSG_MAP(SetDriverDramAddrHigh,		     PPSMC_MSG_SetDriverDramAddrHigh,		1),
	MSG_MAP(SetDriverDramAddrLow,		     PPSMC_MSG_SetDriverDramAddrLow,		1),
	MSG_MAP(SetToolsDramAddrHigh,		     PPSMC_MSG_SetToolsDramAddrHigh,		0),
	MSG_MAP(SetToolsDramAddrLow,		     PPSMC_MSG_SetToolsDramAddrLow,		0),
	MSG_MAP(TransferTableSmu2Dram,		     PPSMC_MSG_TransferTableSmu2Dram,		1),
	MSG_MAP(TransferTableDram2Smu,		     PPSMC_MSG_TransferTableDram2Smu,		0),
	MSG_MAP(UseDefaultPPTable,		     PPSMC_MSG_UseDefaultPPTable,		0),
	MSG_MAP(SetSystemVirtualDramAddrHigh,	     PPSMC_MSG_SetSystemVirtualDramAddrHigh,	0),
	MSG_MAP(SetSystemVirtualDramAddrLow,	     PPSMC_MSG_SetSystemVirtualDramAddrLow,	0),
	MSG_MAP(SetSoftMinByFreq,		     PPSMC_MSG_SetSoftMinByFreq,		0),
	MSG_MAP(SetSoftMaxByFreq,		     PPSMC_MSG_SetSoftMaxByFreq,		0),
	MSG_MAP(SetHardMinByFreq,		     PPSMC_MSG_SetHardMinByFreq,		0),
	MSG_MAP(SetHardMaxByFreq,		     PPSMC_MSG_SetHardMaxByFreq,		0),
	MSG_MAP(GetMinDpmFreq,			     PPSMC_MSG_GetMinDpmFreq,			0),
	MSG_MAP(GetMaxDpmFreq,			     PPSMC_MSG_GetMaxDpmFreq,			0),
	MSG_MAP(GetDpmFreqByIndex,		     PPSMC_MSG_GetDpmFreqByIndex,		1),
	MSG_MAP(SetWorkloadMask,		     PPSMC_MSG_SetWorkloadMask,			1),
	MSG_MAP(GetVoltageByDpm,		     PPSMC_MSG_GetVoltageByDpm,			0),
	MSG_MAP(GetVoltageByDpmOverdrive,	     PPSMC_MSG_GetVoltageByDpmOverdrive,	0),
	MSG_MAP(SetPptLimit,			     PPSMC_MSG_SetPptLimit,			0),
	MSG_MAP(GetPptLimit,			     PPSMC_MSG_GetPptLimit,			1),
	MSG_MAP(PrepareMp1ForUnload,		     PPSMC_MSG_PrepareMp1ForUnload,		0),
	MSG_MAP(GfxDeviceDriverReset,		     PPSMC_MSG_GfxDriverReset,			0),
	MSG_MAP(RunDcBtc,			     PPSMC_MSG_RunDcBtc,			0),
	MSG_MAP(DramLogSetDramAddrHigh,		     PPSMC_MSG_DramLogSetDramAddrHigh,		0),
	MSG_MAP(DramLogSetDramAddrLow,		     PPSMC_MSG_DramLogSetDramAddrLow,		0),
	MSG_MAP(DramLogSetDramSize,		     PPSMC_MSG_DramLogSetDramSize,		0),
	MSG_MAP(GetDebugData,			     PPSMC_MSG_GetDebugData,			0),
	MSG_MAP(WaflTest,			     PPSMC_MSG_WaflTest,			0),
	MSG_MAP(SetMemoryChannelEnable,		     PPSMC_MSG_SetMemoryChannelEnable,		0),
	MSG_MAP(SetNumBadHbmPagesRetired,	     PPSMC_MSG_SetNumBadHbmPagesRetired,	0),
	MSG_MAP(DFCstateControl,		     PPSMC_MSG_DFCstateControl,			0),
	MSG_MAP(GetGmiPwrDnHyst,		     PPSMC_MSG_GetGmiPwrDnHyst,			0),
	MSG_MAP(SetGmiPwrDnHyst,		     PPSMC_MSG_SetGmiPwrDnHyst,			0),
	MSG_MAP(GmiPwrDnControl,		     PPSMC_MSG_GmiPwrDnControl,			0),
	MSG_MAP(EnterGfxoff,			     PPSMC_MSG_EnterGfxoff,			0),
	MSG_MAP(ExitGfxoff,			     PPSMC_MSG_ExitGfxoff,			0),
	MSG_MAP(SetExecuteDMATest,		     PPSMC_MSG_SetExecuteDMATest,		0),
	MSG_MAP(EnableDeterminism,		     PPSMC_MSG_EnableDeterminism,		0),
	MSG_MAP(DisableDeterminism,		     PPSMC_MSG_DisableDeterminism,		0),
	MSG_MAP(SetUclkDpmMode,			     PPSMC_MSG_SetUclkDpmMode,			0),
	MSG_MAP(GfxDriverResetRecovery,		     PPSMC_MSG_GfxDriverResetRecovery,		0),
पूर्ण;

अटल स्थिर काष्ठा cmn2asic_mapping aldebaran_clk_map[SMU_CLK_COUNT] = अणु
	CLK_MAP(GFXCLK, PPCLK_GFXCLK),
	CLK_MAP(SCLK,	PPCLK_GFXCLK),
	CLK_MAP(SOCCLK, PPCLK_SOCCLK),
	CLK_MAP(FCLK, PPCLK_FCLK),
	CLK_MAP(UCLK, PPCLK_UCLK),
	CLK_MAP(MCLK, PPCLK_UCLK),
	CLK_MAP(DCLK, PPCLK_DCLK),
	CLK_MAP(VCLK, PPCLK_VCLK),
	CLK_MAP(LCLK, 	PPCLK_LCLK),
पूर्ण;

अटल स्थिर काष्ठा cmn2asic_mapping aldebaran_feature_mask_map[SMU_FEATURE_COUNT] = अणु
	ALDEBARAN_FEA_MAP(SMU_FEATURE_DPM_PREFETCHER_BIT, 		FEATURE_DATA_CALCULATIONS),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_DPM_GFXCLK_BIT, 			FEATURE_DPM_GFXCLK_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_DPM_UCLK_BIT, 			FEATURE_DPM_UCLK_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_DPM_SOCCLK_BIT, 			FEATURE_DPM_SOCCLK_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_DPM_FCLK_BIT, 			FEATURE_DPM_FCLK_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_DPM_LCLK_BIT, 			FEATURE_DPM_LCLK_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_XGMI_BIT, 				FEATURE_DPM_XGMI_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_DS_GFXCLK_BIT, 			FEATURE_DS_GFXCLK_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_DS_SOCCLK_BIT, 			FEATURE_DS_SOCCLK_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_DS_LCLK_BIT, 				FEATURE_DS_LCLK_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_DS_FCLK_BIT, 				FEATURE_DS_FCLK_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_DS_UCLK_BIT,				FEATURE_DS_UCLK_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_GFX_SS_BIT, 				FEATURE_GFX_SS_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_VCN_PG_BIT, 				FEATURE_DPM_VCN_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_RSMU_SMN_CG_BIT, 			FEATURE_RSMU_SMN_CG_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_WAFL_CG_BIT, 				FEATURE_WAFL_CG_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_PPT_BIT, 					FEATURE_PPT_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_TDC_BIT, 					FEATURE_TDC_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_APCC_PLUS_BIT, 			FEATURE_APCC_PLUS_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_APCC_DFLL_BIT, 			FEATURE_APCC_DFLL_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_FUSE_CG_BIT, 				FEATURE_FUSE_CG_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_MP1_CG_BIT, 				FEATURE_MP1_CG_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_SMUIO_CG_BIT, 			FEATURE_SMUIO_CG_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_THM_CG_BIT, 				FEATURE_THM_CG_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_CLK_CG_BIT, 				FEATURE_CLK_CG_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_FW_CTF_BIT, 				FEATURE_FW_CTF_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_THERMAL_BIT, 				FEATURE_THERMAL_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_OUT_OF_BAND_MONITOR_BIT, 	FEATURE_OUT_OF_BAND_MONITOR_BIT),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_XGMI_PER_LINK_PWR_DWN_BIT,FEATURE_XGMI_PER_LINK_PWR_DWN),
	ALDEBARAN_FEA_MAP(SMU_FEATURE_DF_CSTATE_BIT, 			FEATURE_DF_CSTATE),
पूर्ण;

अटल स्थिर काष्ठा cmn2asic_mapping aldebaran_table_map[SMU_TABLE_COUNT] = अणु
	TAB_MAP(PPTABLE),
	TAB_MAP(AVFS_PSM_DEBUG),
	TAB_MAP(AVFS_FUSE_OVERRIDE),
	TAB_MAP(PMSTATUSLOG),
	TAB_MAP(SMU_METRICS),
	TAB_MAP(DRIVER_SMU_CONFIG),
	TAB_MAP(I2C_COMMANDS),
पूर्ण;

अटल पूर्णांक aldebaran_tables_init(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा smu_table *tables = smu_table->tables;

	SMU_TABLE_INIT(tables, SMU_TABLE_PPTABLE, माप(PPTable_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);

	SMU_TABLE_INIT(tables, SMU_TABLE_PMSTATUSLOG, SMU13_TOOL_SIZE,
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);

	SMU_TABLE_INIT(tables, SMU_TABLE_SMU_METRICS, माप(SmuMetrics_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);

	SMU_TABLE_INIT(tables, SMU_TABLE_I2C_COMMANDS, माप(SwI2cRequest_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);

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

अटल पूर्णांक aldebaran_allocate_dpm_context(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_dpm_context *smu_dpm = &smu->smu_dpm;

	smu_dpm->dpm_context = kzalloc(माप(काष्ठा smu_13_0_dpm_context),
				       GFP_KERNEL);
	अगर (!smu_dpm->dpm_context)
		वापस -ENOMEM;
	smu_dpm->dpm_context_size = माप(काष्ठा smu_13_0_dpm_context);

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

अटल पूर्णांक aldebaran_init_smc_tables(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	ret = aldebaran_tables_init(smu);
	अगर (ret)
		वापस ret;

	ret = aldebaran_allocate_dpm_context(smu);
	अगर (ret)
		वापस ret;

	वापस smu_v13_0_init_smc_tables(smu);
पूर्ण

अटल पूर्णांक aldebaran_get_allowed_feature_mask(काष्ठा smu_context *smu,
					      uपूर्णांक32_t *feature_mask, uपूर्णांक32_t num)
अणु
	अगर (num > 2)
		वापस -EINVAL;

	/* pptable will handle the features to enable */
	स_रखो(feature_mask, 0xFF, माप(uपूर्णांक32_t) * num);

	वापस 0;
पूर्ण

अटल पूर्णांक aldebaran_set_शेष_dpm_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_13_0_dpm_context *dpm_context = smu->smu_dpm.dpm_context;
	काष्ठा smu_13_0_dpm_table *dpm_table = शून्य;
	PPTable_t *pptable = smu->smu_table.driver_pptable;
	पूर्णांक ret = 0;

	/* socclk dpm table setup */
	dpm_table = &dpm_context->dpm_tables.soc_table;
	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_SOCCLK_BIT)) अणु
		ret = smu_v13_0_set_single_dpm_table(smu,
						     SMU_SOCCLK,
						     dpm_table);
		अगर (ret)
			वापस ret;
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
		/* in the हाल of gfxclk, only fine-grained dpm is honored */
		dpm_table->count = 2;
		dpm_table->dpm_levels[0].value = pptable->GfxclkFmin;
		dpm_table->dpm_levels[0].enabled = true;
		dpm_table->dpm_levels[1].value = pptable->GfxclkFmax;
		dpm_table->dpm_levels[1].enabled = true;
		dpm_table->min = dpm_table->dpm_levels[0].value;
		dpm_table->max = dpm_table->dpm_levels[1].value;
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
		ret = smu_v13_0_set_single_dpm_table(smu,
						     SMU_UCLK,
						     dpm_table);
		अगर (ret)
			वापस ret;
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
		ret = smu_v13_0_set_single_dpm_table(smu,
						     SMU_FCLK,
						     dpm_table);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		dpm_table->count = 1;
		dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.fclk / 100;
		dpm_table->dpm_levels[0].enabled = true;
		dpm_table->min = dpm_table->dpm_levels[0].value;
		dpm_table->max = dpm_table->dpm_levels[0].value;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aldebaran_check_घातerplay_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	काष्ठा smu_13_0_घातerplay_table *घातerplay_table =
		table_context->घातer_play_table;
	काष्ठा smu_baco_context *smu_baco = &smu->smu_baco;

	mutex_lock(&smu_baco->mutex);
	अगर (घातerplay_table->platक्रमm_caps & SMU_13_0_PP_PLATFORM_CAP_BACO ||
	    घातerplay_table->platक्रमm_caps & SMU_13_0_PP_PLATFORM_CAP_MACO)
		smu_baco->platक्रमm_support = true;
	mutex_unlock(&smu_baco->mutex);

	table_context->thermal_controller_type =
		घातerplay_table->thermal_controller_type;

	वापस 0;
पूर्ण

अटल पूर्णांक aldebaran_store_घातerplay_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	काष्ठा smu_13_0_घातerplay_table *घातerplay_table =
		table_context->घातer_play_table;
	स_नकल(table_context->driver_pptable, &घातerplay_table->smc_pptable,
	       माप(PPTable_t));

	वापस 0;
पूर्ण

अटल पूर्णांक aldebaran_append_घातerplay_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	PPTable_t *smc_pptable = table_context->driver_pptable;
	काष्ठा atom_smc_dpm_info_v4_10 *smc_dpm_table;
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
	    (smc_dpm_table->table_header.content_revision == 10))
		स_नकल(&smc_pptable->GfxMaxCurrent,
		       &smc_dpm_table->GfxMaxCurrent,
		       माप(*smc_dpm_table) - दुरत्व(काष्ठा atom_smc_dpm_info_v4_10, GfxMaxCurrent));
	वापस 0;
पूर्ण

अटल पूर्णांक aldebaran_setup_pptable(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	/* VBIOS pptable is the first choice */
	smu->smu_table.boot_values.pp_table_id = 0;

	ret = smu_v13_0_setup_pptable(smu);
	अगर (ret)
		वापस ret;

	ret = aldebaran_store_घातerplay_table(smu);
	अगर (ret)
		वापस ret;

	ret = aldebaran_append_घातerplay_table(smu);
	अगर (ret)
		वापस ret;

	ret = aldebaran_check_घातerplay_table(smu);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक aldebaran_run_btc(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret;

	ret = smu_cmn_send_smc_msg(smu, SMU_MSG_RunDcBtc, शून्य);
	अगर (ret)
		dev_err(smu->adev->dev, "RunDcBtc failed!\n");

	वापस ret;
पूर्ण

अटल पूर्णांक aldebaran_populate_umd_state_clk(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_13_0_dpm_context *dpm_context =
		smu->smu_dpm.dpm_context;
	काष्ठा smu_13_0_dpm_table *gfx_table =
		&dpm_context->dpm_tables.gfx_table;
	काष्ठा smu_13_0_dpm_table *mem_table =
		&dpm_context->dpm_tables.uclk_table;
	काष्ठा smu_13_0_dpm_table *soc_table =
		&dpm_context->dpm_tables.soc_table;
	काष्ठा smu_umd_pstate_table *pstate_table =
		&smu->pstate_table;

	pstate_table->gfxclk_pstate.min = gfx_table->min;
	pstate_table->gfxclk_pstate.peak = gfx_table->max;

	pstate_table->uclk_pstate.min = mem_table->min;
	pstate_table->uclk_pstate.peak = mem_table->max;

	pstate_table->socclk_pstate.min = soc_table->min;
	pstate_table->socclk_pstate.peak = soc_table->max;

	अगर (gfx_table->count > ALDEBARAN_UMD_PSTATE_GFXCLK_LEVEL &&
	    mem_table->count > ALDEBARAN_UMD_PSTATE_MCLK_LEVEL &&
	    soc_table->count > ALDEBARAN_UMD_PSTATE_SOCCLK_LEVEL) अणु
		pstate_table->gfxclk_pstate.standard =
			gfx_table->dpm_levels[ALDEBARAN_UMD_PSTATE_GFXCLK_LEVEL].value;
		pstate_table->uclk_pstate.standard =
			mem_table->dpm_levels[ALDEBARAN_UMD_PSTATE_MCLK_LEVEL].value;
		pstate_table->socclk_pstate.standard =
			soc_table->dpm_levels[ALDEBARAN_UMD_PSTATE_SOCCLK_LEVEL].value;
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

अटल पूर्णांक aldebaran_get_clk_table(काष्ठा smu_context *smu,
				   काष्ठा pp_घड़ी_levels_with_latency *घड़ीs,
				   काष्ठा smu_13_0_dpm_table *dpm_table)
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

अटल पूर्णांक aldebaran_freqs_in_same_level(पूर्णांक32_t frequency1,
					 पूर्णांक32_t frequency2)
अणु
	वापस (असल(frequency1 - frequency2) <= EPSILON);
पूर्ण

अटल पूर्णांक aldebaran_get_smu_metrics_data(काष्ठा smu_context *smu,
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
	शेष:
		*value = अच_पूर्णांक_उच्च;
		अवरोध;
	पूर्ण

	mutex_unlock(&smu->metrics_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक aldebaran_get_current_clk_freq_by_table(काष्ठा smu_context *smu,
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

	वापस aldebaran_get_smu_metrics_data(smu,
					      member_type,
					      value);
पूर्ण

अटल पूर्णांक aldebaran_prपूर्णांक_clk_levels(काष्ठा smu_context *smu,
				      क्रमागत smu_clk_type type, अक्षर *buf)
अणु
	पूर्णांक i, now, size = 0;
	पूर्णांक ret = 0;
	काष्ठा pp_घड़ी_levels_with_latency घड़ीs;
	काष्ठा smu_13_0_dpm_table *single_dpm_table;
	काष्ठा smu_dpm_context *smu_dpm = &smu->smu_dpm;
	काष्ठा smu_13_0_dpm_context *dpm_context = शून्य;
	uपूर्णांक32_t display_levels;
	uपूर्णांक32_t freq_values[3] = अणु0पूर्ण;
	uपूर्णांक32_t min_clk, max_clk;

	अगर (amdgpu_ras_पूर्णांकr_triggered())
		वापस snम_लिखो(buf, PAGE_SIZE, "unavailable\n");

	dpm_context = smu_dpm->dpm_context;

	चयन (type) अणु

	हाल SMU_OD_SCLK:
		size = प्र_लिखो(buf, "%s:\n", "GFXCLK");
		fallthrough;
	हाल SMU_SCLK:
		ret = aldebaran_get_current_clk_freq_by_table(smu, SMU_GFXCLK, &now);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Attempt to get current gfx clk Failed!");
			वापस ret;
		पूर्ण

		single_dpm_table = &(dpm_context->dpm_tables.gfx_table);
		ret = aldebaran_get_clk_table(smu, &घड़ीs, single_dpm_table);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Attempt to get gfx clk levels Failed!");
			वापस ret;
		पूर्ण

		display_levels = घड़ीs.num_levels;

		min_clk = smu->gfx_actual_hard_min_freq & CLOCK_VALID ?
				  smu->gfx_actual_hard_min_freq & ~CLOCK_VALID :
				  single_dpm_table->dpm_levels[0].value;
		max_clk = smu->gfx_actual_soft_max_freq & CLOCK_VALID ?
				  smu->gfx_actual_soft_max_freq & ~CLOCK_VALID :
				  single_dpm_table->dpm_levels[1].value;

		freq_values[0] = min_clk;
		freq_values[1] = max_clk;

		/* fine-grained dpm has only 2 levels */
		अगर (now > min_clk && now < max_clk) अणु
			display_levels = घड़ीs.num_levels + 1;
			freq_values[2] = max_clk;
			freq_values[1] = now;
		पूर्ण

		/*
		 * For DPM disabled हाल, there will be only one घड़ी level.
		 * And it's safe to assume that is always the current घड़ी.
		 */
		अगर (display_levels == घड़ीs.num_levels) अणु
			क्रम (i = 0; i < घड़ीs.num_levels; i++)
				size += प्र_लिखो(
					buf + size, "%d: %uMhz %s\n", i,
					freq_values[i],
					(घड़ीs.num_levels == 1) ?
						"*" :
						(aldebaran_freqs_in_same_level(
							 freq_values[i], now) ?
							 "*" :
							 ""));
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < display_levels; i++)
				size += प्र_लिखो(buf + size, "%d: %uMhz %s\n", i,
						freq_values[i], i == 1 ? "*" : "");
		पूर्ण

		अवरोध;

	हाल SMU_OD_MCLK:
		size = प्र_लिखो(buf, "%s:\n", "MCLK");
		fallthrough;
	हाल SMU_MCLK:
		ret = aldebaran_get_current_clk_freq_by_table(smu, SMU_UCLK, &now);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Attempt to get current mclk Failed!");
			वापस ret;
		पूर्ण

		single_dpm_table = &(dpm_context->dpm_tables.uclk_table);
		ret = aldebaran_get_clk_table(smu, &घड़ीs, single_dpm_table);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Attempt to get memory clk levels Failed!");
			वापस ret;
		पूर्ण

		क्रम (i = 0; i < घड़ीs.num_levels; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
					i, घड़ीs.data[i].घड़ीs_in_khz / 1000,
					(घड़ीs.num_levels == 1) ? "*" :
					(aldebaran_freqs_in_same_level(
								       घड़ीs.data[i].घड़ीs_in_khz / 1000,
								       now) ? "*" : ""));
		अवरोध;

	हाल SMU_SOCCLK:
		ret = aldebaran_get_current_clk_freq_by_table(smu, SMU_SOCCLK, &now);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Attempt to get current socclk Failed!");
			वापस ret;
		पूर्ण

		single_dpm_table = &(dpm_context->dpm_tables.soc_table);
		ret = aldebaran_get_clk_table(smu, &घड़ीs, single_dpm_table);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Attempt to get socclk levels Failed!");
			वापस ret;
		पूर्ण

		क्रम (i = 0; i < घड़ीs.num_levels; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
					i, घड़ीs.data[i].घड़ीs_in_khz / 1000,
					(घड़ीs.num_levels == 1) ? "*" :
					(aldebaran_freqs_in_same_level(
								       घड़ीs.data[i].घड़ीs_in_khz / 1000,
								       now) ? "*" : ""));
		अवरोध;

	हाल SMU_FCLK:
		ret = aldebaran_get_current_clk_freq_by_table(smu, SMU_FCLK, &now);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Attempt to get current fclk Failed!");
			वापस ret;
		पूर्ण

		single_dpm_table = &(dpm_context->dpm_tables.fclk_table);
		ret = aldebaran_get_clk_table(smu, &घड़ीs, single_dpm_table);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Attempt to get fclk levels Failed!");
			वापस ret;
		पूर्ण

		क्रम (i = 0; i < single_dpm_table->count; i++)
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n",
					i, single_dpm_table->dpm_levels[i].value,
					(घड़ीs.num_levels == 1) ? "*" :
					(aldebaran_freqs_in_same_level(
								       घड़ीs.data[i].घड़ीs_in_khz / 1000,
								       now) ? "*" : ""));
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक aldebaran_upload_dpm_level(काष्ठा smu_context *smu,
				      bool max,
				      uपूर्णांक32_t feature_mask,
				      uपूर्णांक32_t level)
अणु
	काष्ठा smu_13_0_dpm_context *dpm_context =
		smu->smu_dpm.dpm_context;
	uपूर्णांक32_t freq;
	पूर्णांक ret = 0;

	अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_DPM_GFXCLK_BIT) &&
	    (feature_mask & FEATURE_MASK(FEATURE_DPM_GFXCLK_BIT))) अणु
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
	    (feature_mask & FEATURE_MASK(FEATURE_DPM_UCLK_BIT))) अणु
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
	    (feature_mask & FEATURE_MASK(FEATURE_DPM_SOCCLK_BIT))) अणु
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

अटल पूर्णांक aldebaran_क्रमce_clk_levels(काष्ठा smu_context *smu,
				      क्रमागत smu_clk_type type, uपूर्णांक32_t mask)
अणु
	काष्ठा smu_13_0_dpm_context *dpm_context = smu->smu_dpm.dpm_context;
	काष्ठा smu_13_0_dpm_table *single_dpm_table = शून्य;
	uपूर्णांक32_t soft_min_level, soft_max_level;
	पूर्णांक ret = 0;

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

		ret = aldebaran_upload_dpm_level(smu,
						 false,
						 FEATURE_MASK(FEATURE_DPM_GFXCLK_BIT),
						 soft_min_level);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Failed to upload boot level to lowest!\n");
			अवरोध;
		पूर्ण

		ret = aldebaran_upload_dpm_level(smu,
						 true,
						 FEATURE_MASK(FEATURE_DPM_GFXCLK_BIT),
						 soft_max_level);
		अगर (ret)
			dev_err(smu->adev->dev, "Failed to upload dpm max level to highest!\n");

		अवरोध;

	हाल SMU_MCLK:
	हाल SMU_SOCCLK:
	हाल SMU_FCLK:
		/*
		 * Should not arrive here since aldebaran करोes not
		 * support mclk/socclk/fclk sofपंचांगin/sofपंचांगax settings
		 */
		ret = -EINVAL;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aldebaran_get_thermal_temperature_range(काष्ठा smu_context *smu,
						   काष्ठा smu_temperature_range *range)
अणु
	काष्ठा smu_table_context *table_context = &smu->smu_table;
	काष्ठा smu_13_0_घातerplay_table *घातerplay_table =
		table_context->घातer_play_table;
	PPTable_t *pptable = smu->smu_table.driver_pptable;

	अगर (!range)
		वापस -EINVAL;

	स_नकल(range, &smu13_thermal_policy[0], माप(काष्ठा smu_temperature_range));

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

अटल पूर्णांक aldebaran_get_current_activity_percent(काष्ठा smu_context *smu,
						  क्रमागत amd_pp_sensors sensor,
						  uपूर्णांक32_t *value)
अणु
	पूर्णांक ret = 0;

	अगर (!value)
		वापस -EINVAL;

	चयन (sensor) अणु
	हाल AMDGPU_PP_SENSOR_GPU_LOAD:
		ret = aldebaran_get_smu_metrics_data(smu,
						     METRICS_AVERAGE_GFXACTIVITY,
						     value);
		अवरोध;
	हाल AMDGPU_PP_SENSOR_MEM_LOAD:
		ret = aldebaran_get_smu_metrics_data(smu,
						     METRICS_AVERAGE_MEMACTIVITY,
						     value);
		अवरोध;
	शेष:
		dev_err(smu->adev->dev, "Invalid sensor for retrieving clock activity\n");
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aldebaran_get_gpu_घातer(काष्ठा smu_context *smu, uपूर्णांक32_t *value)
अणु
	अगर (!value)
		वापस -EINVAL;

	वापस aldebaran_get_smu_metrics_data(smu,
					      METRICS_AVERAGE_SOCKETPOWER,
					      value);
पूर्ण

अटल पूर्णांक aldebaran_thermal_get_temperature(काष्ठा smu_context *smu,
					     क्रमागत amd_pp_sensors sensor,
					     uपूर्णांक32_t *value)
अणु
	पूर्णांक ret = 0;

	अगर (!value)
		वापस -EINVAL;

	चयन (sensor) अणु
	हाल AMDGPU_PP_SENSOR_HOTSPOT_TEMP:
		ret = aldebaran_get_smu_metrics_data(smu,
						     METRICS_TEMPERATURE_HOTSPOT,
						     value);
		अवरोध;
	हाल AMDGPU_PP_SENSOR_EDGE_TEMP:
		ret = aldebaran_get_smu_metrics_data(smu,
						     METRICS_TEMPERATURE_EDGE,
						     value);
		अवरोध;
	हाल AMDGPU_PP_SENSOR_MEM_TEMP:
		ret = aldebaran_get_smu_metrics_data(smu,
						     METRICS_TEMPERATURE_MEM,
						     value);
		अवरोध;
	शेष:
		dev_err(smu->adev->dev, "Invalid sensor for retrieving temp\n");
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aldebaran_पढ़ो_sensor(काष्ठा smu_context *smu,
				 क्रमागत amd_pp_sensors sensor,
				 व्योम *data, uपूर्णांक32_t *size)
अणु
	पूर्णांक ret = 0;

	अगर (amdgpu_ras_पूर्णांकr_triggered())
		वापस 0;

	अगर (!data || !size)
		वापस -EINVAL;

	mutex_lock(&smu->sensor_lock);
	चयन (sensor) अणु
	हाल AMDGPU_PP_SENSOR_MEM_LOAD:
	हाल AMDGPU_PP_SENSOR_GPU_LOAD:
		ret = aldebaran_get_current_activity_percent(smu,
							     sensor,
							     (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GPU_POWER:
		ret = aldebaran_get_gpu_घातer(smu, (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_HOTSPOT_TEMP:
	हाल AMDGPU_PP_SENSOR_EDGE_TEMP:
	हाल AMDGPU_PP_SENSOR_MEM_TEMP:
		ret = aldebaran_thermal_get_temperature(smu, sensor,
							(uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GFX_MCLK:
		ret = aldebaran_get_current_clk_freq_by_table(smu, SMU_UCLK, (uपूर्णांक32_t *)data);
		/* the output घड़ी frequency in 10K unit */
		*(uपूर्णांक32_t *)data *= 100;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GFX_SCLK:
		ret = aldebaran_get_current_clk_freq_by_table(smu, SMU_GFXCLK, (uपूर्णांक32_t *)data);
		*(uपूर्णांक32_t *)data *= 100;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_VDDGFX:
		ret = smu_v13_0_get_gfx_vdd(smu, (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	mutex_unlock(&smu->sensor_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक aldebaran_get_घातer_limit(काष्ठा smu_context *smu)
अणु
	PPTable_t *pptable = smu->smu_table.driver_pptable;
	uपूर्णांक32_t घातer_limit = 0;
	पूर्णांक ret;

	अगर (!smu_cmn_feature_is_enabled(smu, SMU_FEATURE_PPT_BIT))
		वापस -EINVAL;

	ret = smu_cmn_send_smc_msg(smu, SMU_MSG_GetPptLimit, &घातer_limit);

	अगर (ret) अणु
		/* the last hope to figure out the ppt limit */
		अगर (!pptable) अणु
			dev_err(smu->adev->dev, "Cannot get PPT limit due to pptable missing!");
			वापस -EINVAL;
		पूर्ण
		घातer_limit = pptable->PptLimit;
	पूर्ण

	smu->current_घातer_limit = smu->शेष_घातer_limit = घातer_limit;
	अगर (pptable)
		smu->max_घातer_limit = pptable->PptLimit;

	वापस 0;
पूर्ण

अटल पूर्णांक aldebaran_प्रणाली_features_control(काष्ठा  smu_context *smu, bool enable)
अणु
	पूर्णांक ret;

	ret = smu_v13_0_प्रणाली_features_control(smu, enable);
	अगर (!ret && enable)
		ret = aldebaran_run_btc(smu);

	वापस ret;
पूर्ण

अटल पूर्णांक aldebaran_set_perक्रमmance_level(काष्ठा smu_context *smu,
					   क्रमागत amd_dpm_क्रमced_level level)
अणु
	काष्ठा smu_dpm_context *smu_dpm = &(smu->smu_dpm);

	/* Disable determinism अगर चयनing to another mode */
	अगर ((smu_dpm->dpm_level == AMD_DPM_FORCED_LEVEL_PERF_DETERMINISM)
			&& (level != AMD_DPM_FORCED_LEVEL_PERF_DETERMINISM))
		smu_cmn_send_smc_msg(smu, SMU_MSG_DisableDeterminism, शून्य);

	/* Reset user min/max gfx घड़ी */
	smu->gfx_actual_hard_min_freq = 0;
	smu->gfx_actual_soft_max_freq = 0;

	चयन (level) अणु

	हाल AMD_DPM_FORCED_LEVEL_PERF_DETERMINISM:
		वापस 0;

	हाल AMD_DPM_FORCED_LEVEL_HIGH:
	हाल AMD_DPM_FORCED_LEVEL_LOW:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_PEAK:
	शेष:
		अवरोध;
	पूर्ण

	वापस smu_v13_0_set_perक्रमmance_level(smu, level);
पूर्ण

अटल पूर्णांक aldebaran_set_soft_freq_limited_range(काष्ठा smu_context *smu,
					  क्रमागत smu_clk_type clk_type,
					  uपूर्णांक32_t min,
					  uपूर्णांक32_t max)
अणु
	काष्ठा smu_dpm_context *smu_dpm = &(smu->smu_dpm);
	काष्ठा smu_13_0_dpm_context *dpm_context = smu_dpm->dpm_context;
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t min_clk;
	uपूर्णांक32_t max_clk;
	पूर्णांक ret = 0;

	अगर (clk_type != SMU_GFXCLK && clk_type != SMU_SCLK)
		वापस -EINVAL;

	अगर ((smu_dpm->dpm_level != AMD_DPM_FORCED_LEVEL_MANUAL)
			&& (smu_dpm->dpm_level != AMD_DPM_FORCED_LEVEL_PERF_DETERMINISM))
		वापस -EINVAL;

	अगर (smu_dpm->dpm_level == AMD_DPM_FORCED_LEVEL_MANUAL) अणु
		min_clk = max(min, dpm_context->dpm_tables.gfx_table.min);
		max_clk = min(max, dpm_context->dpm_tables.gfx_table.max);
		ret = smu_v13_0_set_soft_freq_limited_range(smu, SMU_GFXCLK,
							    min_clk, max_clk);

		अगर (!ret) अणु
			smu->gfx_actual_hard_min_freq = min_clk | CLOCK_VALID;
			smu->gfx_actual_soft_max_freq = max_clk | CLOCK_VALID;
		पूर्ण
		वापस ret;
	पूर्ण

	अगर (smu_dpm->dpm_level == AMD_DPM_FORCED_LEVEL_PERF_DETERMINISM) अणु
		अगर (!max || (max < dpm_context->dpm_tables.gfx_table.min) ||
			(max > dpm_context->dpm_tables.gfx_table.max)) अणु
			dev_warn(adev->dev,
					"Invalid max frequency %d MHz specified for determinism\n", max);
			वापस -EINVAL;
		पूर्ण

		/* Restore शेष min/max घड़ीs and enable determinism */
		min_clk = dpm_context->dpm_tables.gfx_table.min;
		max_clk = dpm_context->dpm_tables.gfx_table.max;
		ret = smu_v13_0_set_soft_freq_limited_range(smu, SMU_GFXCLK, min_clk, max_clk);
		अगर (!ret) अणु
			usleep_range(500, 1000);
			ret = smu_cmn_send_smc_msg_with_param(smu,
					SMU_MSG_EnableDeterminism,
					max, शून्य);
			अगर (ret) अणु
				dev_err(adev->dev,
						"Failed to enable determinism at GFX clock %d MHz\n", max);
			पूर्ण अन्यथा अणु
				smu->gfx_actual_hard_min_freq =
					min_clk | CLOCK_VALID;
				smu->gfx_actual_soft_max_freq =
					max | CLOCK_VALID;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aldebaran_usr_edit_dpm_table(काष्ठा smu_context *smu, क्रमागत PP_OD_DPM_TABLE_COMMAND type,
							दीर्घ input[], uपूर्णांक32_t size)
अणु
	काष्ठा smu_dpm_context *smu_dpm = &(smu->smu_dpm);
	काष्ठा smu_13_0_dpm_context *dpm_context = smu_dpm->dpm_context;
	uपूर्णांक32_t min_clk;
	uपूर्णांक32_t max_clk;
	पूर्णांक ret = 0;

	/* Only allowed in manual or determinism mode */
	अगर ((smu_dpm->dpm_level != AMD_DPM_FORCED_LEVEL_MANUAL)
			&& (smu_dpm->dpm_level != AMD_DPM_FORCED_LEVEL_PERF_DETERMINISM))
		वापस -EINVAL;

	चयन (type) अणु
	हाल PP_OD_EDIT_SCLK_VDDC_TABLE:
		अगर (size != 2) अणु
			dev_err(smu->adev->dev, "Input parameter number not correct\n");
			वापस -EINVAL;
		पूर्ण

		अगर (input[0] == 0) अणु
			अगर (input[1] < dpm_context->dpm_tables.gfx_table.min) अणु
				dev_warn(smu->adev->dev, "Minimum GFX clk (%ld) MHz specified is less than the minimum allowed (%d) MHz\n",
					input[1], dpm_context->dpm_tables.gfx_table.min);
				वापस -EINVAL;
			पूर्ण
			smu->gfx_actual_hard_min_freq = input[1];
		पूर्ण अन्यथा अगर (input[0] == 1) अणु
			अगर (input[1] > dpm_context->dpm_tables.gfx_table.max) अणु
				dev_warn(smu->adev->dev, "Maximum GFX clk (%ld) MHz specified is greater than the maximum allowed (%d) MHz\n",
					input[1], dpm_context->dpm_tables.gfx_table.max);
				वापस -EINVAL;
			पूर्ण
			smu->gfx_actual_soft_max_freq = input[1];
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल PP_OD_RESTORE_DEFAULT_TABLE:
		अगर (size != 0) अणु
			dev_err(smu->adev->dev, "Input parameter number not correct\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			/* Use the शेष frequencies क्रम manual and determinism mode */
			min_clk = dpm_context->dpm_tables.gfx_table.min;
			max_clk = dpm_context->dpm_tables.gfx_table.max;

			वापस aldebaran_set_soft_freq_limited_range(smu, SMU_GFXCLK, min_clk, max_clk);
		पूर्ण
		अवरोध;
	हाल PP_OD_COMMIT_DPM_TABLE:
		अगर (size != 0) अणु
			dev_err(smu->adev->dev, "Input parameter number not correct\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			min_clk = smu->gfx_actual_hard_min_freq;
			max_clk = smu->gfx_actual_soft_max_freq;
			वापस aldebaran_set_soft_freq_limited_range(smu, SMU_GFXCLK, min_clk, max_clk);
		पूर्ण
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool aldebaran_is_dpm_running(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t feature_mask[2];
	अचिन्हित दीर्घ feature_enabled;
	ret = smu_cmn_get_enabled_mask(smu, feature_mask, 2);
	feature_enabled = (अचिन्हित दीर्घ)((uपूर्णांक64_t)feature_mask[0] |
					  ((uपूर्णांक64_t)feature_mask[1] << 32));
	वापस !!(feature_enabled & SMC_DPM_FEATURE);
पूर्ण

अटल व्योम aldebaran_fill_i2c_req(SwI2cRequest_t  *req, bool ग_लिखो,
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

अटल पूर्णांक aldebaran_i2c_पढ़ो_data(काष्ठा i2c_adapter *control,
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
	aldebaran_fill_i2c_req(&req, false, address, numbytes, data);

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

		dev_dbg(adev->dev, "aldebaran_i2c_read_data, address = %x, bytes = %d, data :",
				  (uपूर्णांक16_t)address, numbytes);

		prपूर्णांक_hex_dump(KERN_DEBUG, "data: ", DUMP_PREFIX_NONE,
			       8, 1, data, numbytes, false);
	पूर्ण अन्यथा
		dev_err(adev->dev, "aldebaran_i2c_read_data - error occurred :%x", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक aldebaran_i2c_ग_लिखो_data(काष्ठा i2c_adapter *control,
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
	aldebaran_fill_i2c_req(&req, true, address, numbytes, data);

	mutex_lock(&adev->smu.mutex);
	ret = smu_cmn_update_table(&adev->smu, SMU_TABLE_I2C_COMMANDS, 0, &req, true);
	mutex_unlock(&adev->smu.mutex);

	अगर (!ret) अणु
		dev_dbg(adev->dev, "aldebaran_i2c_write(), address = %x, bytes = %d , data: ",
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
		dev_err(adev->dev, "aldebaran_i2c_write- error occurred :%x", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक aldebaran_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
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
				ret = aldebaran_i2c_पढ़ो_data(i2c_adap,
							     (uपूर्णांक8_t)msgs[i].addr,
							     data_chunk, MAX_SW_I2C_COMMANDS);

				स_नकल(data_ptr, data_chunk + 2, data_chunk_size);
			पूर्ण अन्यथा अणु

				स_नकल(data_chunk + 2, data_ptr, data_chunk_size);

				ret = aldebaran_i2c_ग_लिखो_data(i2c_adap,
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
				ret = aldebaran_i2c_पढ़ो_data(i2c_adap,
							     (uपूर्णांक8_t)msgs[i].addr,
							     data_chunk, (data_size % data_chunk_size) + 2);

				स_नकल(data_ptr, data_chunk + 2, data_size % data_chunk_size);
			पूर्ण अन्यथा अणु
				स_नकल(data_chunk + 2, data_ptr, data_size % data_chunk_size);

				ret = aldebaran_i2c_ग_लिखो_data(i2c_adap,
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

अटल u32 aldebaran_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण


अटल स्थिर काष्ठा i2c_algorithm aldebaran_i2c_algo = अणु
	.master_xfer = aldebaran_i2c_xfer,
	.functionality = aldebaran_i2c_func,
पूर्ण;

अटल पूर्णांक aldebaran_i2c_control_init(काष्ठा smu_context *smu, काष्ठा i2c_adapter *control)
अणु
	काष्ठा amdgpu_device *adev = to_amdgpu_device(control);
	पूर्णांक res;

	control->owner = THIS_MODULE;
	control->class = I2C_CLASS_SPD;
	control->dev.parent = &adev->pdev->dev;
	control->algo = &aldebaran_i2c_algo;
	snम_लिखो(control->name, माप(control->name), "AMDGPU SMU");

	res = i2c_add_adapter(control);
	अगर (res)
		DRM_ERROR("Failed to register hw i2c, err: %d\n", res);

	वापस res;
पूर्ण

अटल व्योम aldebaran_i2c_control_fini(काष्ठा smu_context *smu, काष्ठा i2c_adapter *control)
अणु
	i2c_del_adapter(control);
पूर्ण

अटल व्योम aldebaran_get_unique_id(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	SmuMetrics_t *metrics = smu->smu_table.metrics_table;
	uपूर्णांक32_t upper32 = 0, lower32 = 0;
	पूर्णांक ret;

	mutex_lock(&smu->metrics_lock);
	ret = smu_cmn_get_metrics_table_locked(smu, शून्य, false);
	अगर (ret)
		जाओ out_unlock;

	upper32 = metrics->PublicSerialNumUpper32;
	lower32 = metrics->PublicSerialNumLower32;

out_unlock:
	mutex_unlock(&smu->metrics_lock);

	adev->unique_id = ((uपूर्णांक64_t)upper32 << 32) | lower32;
	प्र_लिखो(adev->serial, "%016llx", adev->unique_id);
पूर्ण

अटल bool aldebaran_is_baco_supported(काष्ठा smu_context *smu)
अणु
	/* aldebaran is not support baco */

	वापस false;
पूर्ण

अटल पूर्णांक aldebaran_set_df_cstate(काष्ठा smu_context *smu,
				   क्रमागत pp_df_cstate state)
अणु
	वापस smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_DFCstateControl, state, शून्य);
पूर्ण

अटल पूर्णांक aldebaran_allow_xgmi_घातer_करोwn(काष्ठा smu_context *smu, bool en)
अणु
	वापस smu_cmn_send_smc_msg_with_param(smu,
					       SMU_MSG_GmiPwrDnControl,
					       en ? 1 : 0,
					       शून्य);
पूर्ण

अटल स्थिर काष्ठा throttling_logging_label अणु
	uपूर्णांक32_t feature_mask;
	स्थिर अक्षर *label;
पूर्ण logging_label[] = अणु
	अणु(1U << THROTTLER_TEMP_MEM_BIT), "HBM"पूर्ण,
	अणु(1U << THROTTLER_TEMP_VR_GFX_BIT), "VR of GFX rail"पूर्ण,
	अणु(1U << THROTTLER_TEMP_VR_MEM_BIT), "VR of HBM rail"पूर्ण,
	अणु(1U << THROTTLER_TEMP_VR_SOC_BIT), "VR of SOC rail"पूर्ण,
पूर्ण;
अटल व्योम aldebaran_log_thermal_throttling_event(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret;
	पूर्णांक throttler_idx, throtting_events = 0, buf_idx = 0;
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t throttler_status;
	अक्षर log_buf[256];

	ret = aldebaran_get_smu_metrics_data(smu,
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

अटल पूर्णांक aldebaran_get_current_pcie_link_speed(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t esm_ctrl;

	/* TODO: confirm this on real target */
	esm_ctrl = RREG32_PCIE(smnPCIE_ESM_CTRL);
	अगर ((esm_ctrl >> 15) & 0x1FFFF)
		वापस (((esm_ctrl >> 8) & 0x3F) + 128);

	वापस smu_v13_0_get_current_pcie_link_speed(smu);
पूर्ण

अटल sमाप_प्रकार aldebaran_get_gpu_metrics(काष्ठा smu_context *smu,
					 व्योम **table)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा gpu_metrics_v1_1 *gpu_metrics =
		(काष्ठा gpu_metrics_v1_1 *)smu_table->gpu_metrics_table;
	SmuMetrics_t metrics;
	पूर्णांक i, ret = 0;

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
	gpu_metrics->average_mm_activity = 0;

	gpu_metrics->average_socket_घातer = metrics.AverageSocketPower;
	gpu_metrics->energy_accumulator = 0;

	gpu_metrics->average_gfxclk_frequency = metrics.AverageGfxclkFrequency;
	gpu_metrics->average_socclk_frequency = metrics.AverageSocclkFrequency;
	gpu_metrics->average_uclk_frequency = metrics.AverageUclkFrequency;
	gpu_metrics->average_vclk0_frequency = 0;
	gpu_metrics->average_dclk0_frequency = 0;

	gpu_metrics->current_gfxclk = metrics.CurrClock[PPCLK_GFXCLK];
	gpu_metrics->current_socclk = metrics.CurrClock[PPCLK_SOCCLK];
	gpu_metrics->current_uclk = metrics.CurrClock[PPCLK_UCLK];
	gpu_metrics->current_vclk0 = metrics.CurrClock[PPCLK_VCLK];
	gpu_metrics->current_dclk0 = metrics.CurrClock[PPCLK_DCLK];

	gpu_metrics->throttle_status = metrics.ThrottlerStatus;

	gpu_metrics->current_fan_speed = 0;

	gpu_metrics->pcie_link_width =
		smu_v13_0_get_current_pcie_link_width(smu);
	gpu_metrics->pcie_link_speed =
		aldebaran_get_current_pcie_link_speed(smu);

	gpu_metrics->प्रणाली_घड़ी_counter = kसमय_get_bootसमय_ns();

	gpu_metrics->gfx_activity_acc = metrics.GfxBusyAcc;
	gpu_metrics->mem_activity_acc = metrics.DramBusyAcc;

	क्रम (i = 0; i < NUM_HBM_INSTANCES; i++)
		gpu_metrics->temperature_hbm[i] = metrics.TemperatureAllHBM[i];

	*table = (व्योम *)gpu_metrics;

	वापस माप(काष्ठा gpu_metrics_v1_1);
पूर्ण

अटल पूर्णांक aldebaran_mode2_reset(काष्ठा smu_context *smu)
अणु
	u32 smu_version;
	पूर्णांक ret = 0, index;
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक समयout = 10;

	smu_cmn_get_smc_version(smu, शून्य, &smu_version);

	index = smu_cmn_to_asic_specअगरic_index(smu, CMN2ASIC_MAPPING_MSG,
						SMU_MSG_GfxDeviceDriverReset);

	mutex_lock(&smu->message_lock);
	अगर (smu_version >= 0x00441400) अणु
		ret = smu_cmn_send_msg_without_रुकोing(smu, (uपूर्णांक16_t)index, SMU_RESET_MODE_2);
		/* This is similar to FLR, रुको till max FLR समयout */
		msleep(100);
		dev_dbg(smu->adev->dev, "restore config space...\n");
		/* Restore the config space saved during init */
		amdgpu_device_load_pci_state(adev->pdev);

		dev_dbg(smu->adev->dev, "wait for reset ack\n");
		जबतक (ret == -ETIME && समयout)  अणु
			ret = smu_cmn_रुको_क्रम_response(smu);
			/* Wait a bit more समय क्रम getting ACK */
			अगर (ret == -ETIME) अणु
				--समयout;
				usleep_range(500, 1000);
				जारी;
			पूर्ण

			अगर (ret != 1) अणु
				dev_err(adev->dev, "failed to send mode2 message \tparam: 0x%08x response %#x\n",
						SMU_RESET_MODE_2, ret);
				जाओ out;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु
		dev_err(adev->dev, "smu fw 0x%x does not support MSG_GfxDeviceDriverReset MSG\n",
				smu_version);
	पूर्ण

	अगर (ret == 1)
		ret = 0;
out:
	mutex_unlock(&smu->message_lock);

	वापस ret;
पूर्ण

अटल bool aldebaran_is_mode1_reset_supported(काष्ठा smu_context *smu)
अणु
#अगर 0
	काष्ठा amdgpu_device *adev = smu->adev;
	u32 smu_version;
	uपूर्णांक32_t val;
	/**
	 * PM FW version support mode1 reset from 68.07
	 */
	smu_cmn_get_smc_version(smu, शून्य, &smu_version);
	अगर ((smu_version < 0x00440700))
		वापस false;
	/**
	 * mode1 reset relies on PSP, so we should check अगर
	 * PSP is alive.
	 */
	val = RREG32_SOC15(MP0, 0, regMP0_SMN_C2PMSG_81);

	वापस val != 0x0;
#पूर्ण_अगर
	वापस true;
पूर्ण

अटल bool aldebaran_is_mode2_reset_supported(काष्ठा smu_context *smu)
अणु
	वापस true;
पूर्ण

अटल पूर्णांक aldebaran_set_mp1_state(काष्ठा smu_context *smu,
				   क्रमागत pp_mp1_state mp1_state)
अणु
	चयन (mp1_state) अणु
	हाल PP_MP1_STATE_UNLOAD:
		वापस smu_cmn_set_mp1_state(smu, mp1_state);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pptable_funcs aldebaran_ppt_funcs = अणु
	/* init dpm */
	.get_allowed_feature_mask = aldebaran_get_allowed_feature_mask,
	/* dpm/clk tables */
	.set_शेष_dpm_table = aldebaran_set_शेष_dpm_table,
	.populate_umd_state_clk = aldebaran_populate_umd_state_clk,
	.get_thermal_temperature_range = aldebaran_get_thermal_temperature_range,
	.prपूर्णांक_clk_levels = aldebaran_prपूर्णांक_clk_levels,
	.क्रमce_clk_levels = aldebaran_क्रमce_clk_levels,
	.पढ़ो_sensor = aldebaran_पढ़ो_sensor,
	.set_perक्रमmance_level = aldebaran_set_perक्रमmance_level,
	.get_घातer_limit = aldebaran_get_घातer_limit,
	.is_dpm_running = aldebaran_is_dpm_running,
	.get_unique_id = aldebaran_get_unique_id,
	.init_microcode = smu_v13_0_init_microcode,
	.load_microcode = smu_v13_0_load_microcode,
	.fini_microcode = smu_v13_0_fini_microcode,
	.init_smc_tables = aldebaran_init_smc_tables,
	.fini_smc_tables = smu_v13_0_fini_smc_tables,
	.init_घातer = smu_v13_0_init_घातer,
	.fini_घातer = smu_v13_0_fini_घातer,
	.check_fw_status = smu_v13_0_check_fw_status,
	/* pptable related */
	.setup_pptable = aldebaran_setup_pptable,
	.get_vbios_bootup_values = smu_v13_0_get_vbios_bootup_values,
	.check_fw_version = smu_v13_0_check_fw_version,
	.ग_लिखो_pptable = smu_cmn_ग_लिखो_pptable,
	.set_driver_table_location = smu_v13_0_set_driver_table_location,
	.set_tool_table_location = smu_v13_0_set_tool_table_location,
	.notअगरy_memory_pool_location = smu_v13_0_notअगरy_memory_pool_location,
	.प्रणाली_features_control = aldebaran_प्रणाली_features_control,
	.send_smc_msg_with_param = smu_cmn_send_smc_msg_with_param,
	.send_smc_msg = smu_cmn_send_smc_msg,
	.get_enabled_mask = smu_cmn_get_enabled_mask,
	.feature_is_enabled = smu_cmn_feature_is_enabled,
	.disable_all_features_with_exception = smu_cmn_disable_all_features_with_exception,
	.set_घातer_limit = smu_v13_0_set_घातer_limit,
	.init_max_sustainable_घड़ीs = smu_v13_0_init_max_sustainable_घड़ीs,
	.enable_thermal_alert = smu_v13_0_enable_thermal_alert,
	.disable_thermal_alert = smu_v13_0_disable_thermal_alert,
	.set_xgmi_pstate = smu_v13_0_set_xgmi_pstate,
	.रेजिस्टर_irq_handler = smu_v13_0_रेजिस्टर_irq_handler,
	.set_azalia_d3_pme = smu_v13_0_set_azalia_d3_pme,
	.get_max_sustainable_घड़ीs_by_dc = smu_v13_0_get_max_sustainable_घड़ीs_by_dc,
	.baco_is_support= aldebaran_is_baco_supported,
	.get_dpm_ultimate_freq = smu_v13_0_get_dpm_ultimate_freq,
	.set_soft_freq_limited_range = aldebaran_set_soft_freq_limited_range,
	.od_edit_dpm_table = aldebaran_usr_edit_dpm_table,
	.set_df_cstate = aldebaran_set_df_cstate,
	.allow_xgmi_घातer_करोwn = aldebaran_allow_xgmi_घातer_करोwn,
	.log_thermal_throttling_event = aldebaran_log_thermal_throttling_event,
	.get_pp_feature_mask = smu_cmn_get_pp_feature_mask,
	.set_pp_feature_mask = smu_cmn_set_pp_feature_mask,
	.get_gpu_metrics = aldebaran_get_gpu_metrics,
	.mode1_reset_is_support = aldebaran_is_mode1_reset_supported,
	.mode2_reset_is_support = aldebaran_is_mode2_reset_supported,
	.mode1_reset = smu_v13_0_mode1_reset,
	.set_mp1_state = aldebaran_set_mp1_state,
	.mode2_reset = aldebaran_mode2_reset,
	.रुको_क्रम_event = smu_v13_0_रुको_क्रम_event,
	.i2c_init = aldebaran_i2c_control_init,
	.i2c_fini = aldebaran_i2c_control_fini,
पूर्ण;

व्योम aldebaran_set_ppt_funcs(काष्ठा smu_context *smu)
अणु
	smu->ppt_funcs = &aldebaran_ppt_funcs;
	smu->message_map = aldebaran_message_map;
	smu->घड़ी_map = aldebaran_clk_map;
	smu->feature_map = aldebaran_feature_mask_map;
	smu->table_map = aldebaran_table_map;
पूर्ण
