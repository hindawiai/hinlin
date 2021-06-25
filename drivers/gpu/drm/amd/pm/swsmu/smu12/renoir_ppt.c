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

#समावेश "amdgpu.h"
#समावेश "amdgpu_smu.h"
#समावेश "smu_v12_0_ppsmc.h"
#समावेश "smu12_driver_if.h"
#समावेश "smu_v12_0.h"
#समावेश "renoir_ppt.h"
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

अटल काष्ठा cmn2asic_msg_mapping renoir_message_map[SMU_MSG_MAX_COUNT] = अणु
	MSG_MAP(TestMessage,                    PPSMC_MSG_TestMessage,                  1),
	MSG_MAP(GetSmuVersion,                  PPSMC_MSG_GetSmuVersion,                1),
	MSG_MAP(GetDriverIfVersion,             PPSMC_MSG_GetDriverIfVersion,           1),
	MSG_MAP(PowerUpGfx,                     PPSMC_MSG_PowerUpGfx,                   1),
	MSG_MAP(AllowGfxOff,                    PPSMC_MSG_EnableGfxOff,                 1),
	MSG_MAP(DisallowGfxOff,                 PPSMC_MSG_DisableGfxOff,                1),
	MSG_MAP(PowerDownIspByTile,             PPSMC_MSG_PowerDownIspByTile,           1),
	MSG_MAP(PowerUpIspByTile,               PPSMC_MSG_PowerUpIspByTile,             1),
	MSG_MAP(PowerDownVcn,                   PPSMC_MSG_PowerDownVcn,                 1),
	MSG_MAP(PowerUpVcn,                     PPSMC_MSG_PowerUpVcn,                   1),
	MSG_MAP(PowerDownSdma,                  PPSMC_MSG_PowerDownSdma,                1),
	MSG_MAP(PowerUpSdma,                    PPSMC_MSG_PowerUpSdma,                  1),
	MSG_MAP(SetHardMinIspclkByFreq,         PPSMC_MSG_SetHardMinIspclkByFreq,       1),
	MSG_MAP(SetHardMinVcn,                  PPSMC_MSG_SetHardMinVcn,                1),
	MSG_MAP(SetAllowFclkSwitch,             PPSMC_MSG_SetAllowFclkSwitch,           1),
	MSG_MAP(SetMinVideoGfxclkFreq,          PPSMC_MSG_SetMinVideoGfxclkFreq,        1),
	MSG_MAP(ActiveProcessNotअगरy,            PPSMC_MSG_ActiveProcessNotअगरy,          1),
	MSG_MAP(SetCustomPolicy,                PPSMC_MSG_SetCustomPolicy,              1),
	MSG_MAP(SetVideoFps,                    PPSMC_MSG_SetVideoFps,                  1),
	MSG_MAP(NumOfDisplays,                  PPSMC_MSG_SetDisplayCount,              1),
	MSG_MAP(QueryPowerLimit,                PPSMC_MSG_QueryPowerLimit,              1),
	MSG_MAP(SetDriverDramAddrHigh,          PPSMC_MSG_SetDriverDramAddrHigh,        1),
	MSG_MAP(SetDriverDramAddrLow,           PPSMC_MSG_SetDriverDramAddrLow,         1),
	MSG_MAP(TransferTableSmu2Dram,          PPSMC_MSG_TransferTableSmu2Dram,        1),
	MSG_MAP(TransferTableDram2Smu,          PPSMC_MSG_TransferTableDram2Smu,        1),
	MSG_MAP(GfxDeviceDriverReset,           PPSMC_MSG_GfxDeviceDriverReset,         1),
	MSG_MAP(SetGfxclkOverdriveByFreqVid,    PPSMC_MSG_SetGfxclkOverdriveByFreqVid,  1),
	MSG_MAP(SetHardMinDcfclkByFreq,         PPSMC_MSG_SetHardMinDcfclkByFreq,       1),
	MSG_MAP(SetHardMinSocclkByFreq,         PPSMC_MSG_SetHardMinSocclkByFreq,       1),
	MSG_MAP(ControlIgpuATS,                 PPSMC_MSG_ControlIgpuATS,               1),
	MSG_MAP(SetMinVideoFclkFreq,            PPSMC_MSG_SetMinVideoFclkFreq,          1),
	MSG_MAP(SetMinDeepSleepDcfclk,          PPSMC_MSG_SetMinDeepSleepDcfclk,        1),
	MSG_MAP(ForcePowerDownGfx,              PPSMC_MSG_ForcePowerDownGfx,            1),
	MSG_MAP(SetPhyclkVoltageByFreq,         PPSMC_MSG_SetPhyclkVoltageByFreq,       1),
	MSG_MAP(SetDppclkVoltageByFreq,         PPSMC_MSG_SetDppclkVoltageByFreq,       1),
	MSG_MAP(SetSoftMinVcn,                  PPSMC_MSG_SetSoftMinVcn,                1),
	MSG_MAP(EnablePostCode,                 PPSMC_MSG_EnablePostCode,               1),
	MSG_MAP(GetGfxclkFrequency,             PPSMC_MSG_GetGfxclkFrequency,           1),
	MSG_MAP(GetFclkFrequency,               PPSMC_MSG_GetFclkFrequency,             1),
	MSG_MAP(GetMinGfxclkFrequency,          PPSMC_MSG_GetMinGfxclkFrequency,        1),
	MSG_MAP(GetMaxGfxclkFrequency,          PPSMC_MSG_GetMaxGfxclkFrequency,        1),
	MSG_MAP(SoftReset,                      PPSMC_MSG_SoftReset,                    1),
	MSG_MAP(SetGfxCGPG,                     PPSMC_MSG_SetGfxCGPG,                   1),
	MSG_MAP(SetSoftMaxGfxClk,               PPSMC_MSG_SetSoftMaxGfxClk,             1),
	MSG_MAP(SetHardMinGfxClk,               PPSMC_MSG_SetHardMinGfxClk,             1),
	MSG_MAP(SetSoftMaxSocclkByFreq,         PPSMC_MSG_SetSoftMaxSocclkByFreq,       1),
	MSG_MAP(SetSoftMaxFclkByFreq,           PPSMC_MSG_SetSoftMaxFclkByFreq,         1),
	MSG_MAP(SetSoftMaxVcn,                  PPSMC_MSG_SetSoftMaxVcn,                1),
	MSG_MAP(PowerGateMmHub,                 PPSMC_MSG_PowerGateMmHub,               1),
	MSG_MAP(UpdatePmeRestore,               PPSMC_MSG_UpdatePmeRestore,             1),
	MSG_MAP(GpuChangeState,                 PPSMC_MSG_GpuChangeState,               1),
	MSG_MAP(SetPowerLimitPercentage,        PPSMC_MSG_SetPowerLimitPercentage,      1),
	MSG_MAP(ForceGfxContentSave,            PPSMC_MSG_ForceGfxContentSave,          1),
	MSG_MAP(EnableTmdp48MHzRefclkPwrDown,   PPSMC_MSG_EnableTmdp48MHzRefclkPwrDown, 1),
	MSG_MAP(PowerDownJpeg,                  PPSMC_MSG_PowerDownJpeg,                1),
	MSG_MAP(PowerUpJpeg,                    PPSMC_MSG_PowerUpJpeg,                  1),
	MSG_MAP(PowerGateAtHub,                 PPSMC_MSG_PowerGateAtHub,               1),
	MSG_MAP(SetSoftMinJpeg,                 PPSMC_MSG_SetSoftMinJpeg,               1),
	MSG_MAP(SetHardMinFclkByFreq,           PPSMC_MSG_SetHardMinFclkByFreq,         1),
पूर्ण;

अटल काष्ठा cmn2asic_mapping renoir_clk_map[SMU_CLK_COUNT] = अणु
	CLK_MAP(GFXCLK, CLOCK_GFXCLK),
	CLK_MAP(SCLK,	CLOCK_GFXCLK),
	CLK_MAP(SOCCLK, CLOCK_SOCCLK),
	CLK_MAP(UCLK, CLOCK_FCLK),
	CLK_MAP(MCLK, CLOCK_FCLK),
पूर्ण;

अटल काष्ठा cmn2asic_mapping renoir_table_map[SMU_TABLE_COUNT] = अणु
	TAB_MAP_VALID(WATERMARKS),
	TAB_MAP_INVALID(CUSTOM_DPM),
	TAB_MAP_VALID(DPMCLOCKS),
	TAB_MAP_VALID(SMU_METRICS),
पूर्ण;

अटल काष्ठा cmn2asic_mapping renoir_workload_map[PP_SMC_POWER_PROखाता_COUNT] = अणु
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_FULLSCREEN3D,		WORKLOAD_PPLIB_FULL_SCREEN_3D_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_VIDEO,		WORKLOAD_PPLIB_VIDEO_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_VR,			WORKLOAD_PPLIB_VR_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_COMPUTE,		WORKLOAD_PPLIB_COMPUTE_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_CUSTOM,		WORKLOAD_PPLIB_CUSTOM_BIT),
पूर्ण;

अटल पूर्णांक renoir_init_smc_tables(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा smu_table *tables = smu_table->tables;

	SMU_TABLE_INIT(tables, SMU_TABLE_WATERMARKS, माप(Watermarks_t),
		PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_DPMCLOCKS, माप(DpmClocks_t),
		PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_SMU_METRICS, माप(SmuMetrics_t),
		PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);

	smu_table->घड़ीs_table = kzalloc(माप(DpmClocks_t), GFP_KERNEL);
	अगर (!smu_table->घड़ीs_table)
		जाओ err0_out;

	smu_table->metrics_table = kzalloc(माप(SmuMetrics_t), GFP_KERNEL);
	अगर (!smu_table->metrics_table)
		जाओ err1_out;
	smu_table->metrics_समय = 0;

	smu_table->watermarks_table = kzalloc(माप(Watermarks_t), GFP_KERNEL);
	अगर (!smu_table->watermarks_table)
		जाओ err2_out;

	smu_table->gpu_metrics_table_size = माप(काष्ठा gpu_metrics_v2_1);
	smu_table->gpu_metrics_table = kzalloc(smu_table->gpu_metrics_table_size, GFP_KERNEL);
	अगर (!smu_table->gpu_metrics_table)
		जाओ err3_out;

	वापस 0;

err3_out:
	kमुक्त(smu_table->watermarks_table);
err2_out:
	kमुक्त(smu_table->metrics_table);
err1_out:
	kमुक्त(smu_table->घड़ीs_table);
err0_out:
	वापस -ENOMEM;
पूर्ण

/*
 * This पूर्णांकerface just क्रम getting uclk ultimate freq and should't पूर्णांकroduce
 * other likewise function result in overmuch callback.
 */
अटल पूर्णांक renoir_get_dpm_clk_limited(काष्ठा smu_context *smu, क्रमागत smu_clk_type clk_type,
						uपूर्णांक32_t dpm_level, uपूर्णांक32_t *freq)
अणु
	DpmClocks_t *clk_table = smu->smu_table.घड़ीs_table;

	अगर (!clk_table || clk_type >= SMU_CLK_COUNT)
		वापस -EINVAL;

	चयन (clk_type) अणु
	हाल SMU_SOCCLK:
		अगर (dpm_level >= NUM_SOCCLK_DPM_LEVELS)
			वापस -EINVAL;
		*freq = clk_table->SocClocks[dpm_level].Freq;
		अवरोध;
	हाल SMU_UCLK:
	हाल SMU_MCLK:
		अगर (dpm_level >= NUM_FCLK_DPM_LEVELS)
			वापस -EINVAL;
		*freq = clk_table->FClocks[dpm_level].Freq;
		अवरोध;
	हाल SMU_DCEFCLK:
		अगर (dpm_level >= NUM_DCFCLK_DPM_LEVELS)
			वापस -EINVAL;
		*freq = clk_table->DcfClocks[dpm_level].Freq;
		अवरोध;
	हाल SMU_FCLK:
		अगर (dpm_level >= NUM_FCLK_DPM_LEVELS)
			वापस -EINVAL;
		*freq = clk_table->FClocks[dpm_level].Freq;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक renoir_get_profiling_clk_mask(काष्ठा smu_context *smu,
					 क्रमागत amd_dpm_क्रमced_level level,
					 uपूर्णांक32_t *sclk_mask,
					 uपूर्णांक32_t *mclk_mask,
					 uपूर्णांक32_t *soc_mask)
अणु

	अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK) अणु
		अगर (sclk_mask)
			*sclk_mask = 0;
	पूर्ण अन्यथा अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK) अणु
		अगर (mclk_mask)
			/* mclk levels are in reverse order */
			*mclk_mask = NUM_MEMCLK_DPM_LEVELS - 1;
	पूर्ण अन्यथा अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK) अणु
		अगर(sclk_mask)
			/* The sclk as gfxclk and has three level about max/min/current */
			*sclk_mask = 3 - 1;

		अगर(mclk_mask)
			/* mclk levels are in reverse order */
			*mclk_mask = 0;

		अगर(soc_mask)
			*soc_mask = NUM_SOCCLK_DPM_LEVELS - 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक renoir_get_dpm_ultimate_freq(काष्ठा smu_context *smu,
					क्रमागत smu_clk_type clk_type,
					uपूर्णांक32_t *min,
					uपूर्णांक32_t *max)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t mclk_mask, soc_mask;
	uपूर्णांक32_t घड़ी_limit;

	अगर (!smu_cmn_clk_dpm_is_enabled(smu, clk_type)) अणु
		चयन (clk_type) अणु
		हाल SMU_MCLK:
		हाल SMU_UCLK:
			घड़ी_limit = smu->smu_table.boot_values.uclk;
			अवरोध;
		हाल SMU_GFXCLK:
		हाल SMU_SCLK:
			घड़ी_limit = smu->smu_table.boot_values.gfxclk;
			अवरोध;
		हाल SMU_SOCCLK:
			घड़ी_limit = smu->smu_table.boot_values.socclk;
			अवरोध;
		शेष:
			घड़ी_limit = 0;
			अवरोध;
		पूर्ण

		/* घड़ी in Mhz unit */
		अगर (min)
			*min = घड़ी_limit / 100;
		अगर (max)
			*max = घड़ी_limit / 100;

		वापस 0;
	पूर्ण

	अगर (max) अणु
		ret = renoir_get_profiling_clk_mask(smu,
						    AMD_DPM_FORCED_LEVEL_PROखाता_PEAK,
						    शून्य,
						    &mclk_mask,
						    &soc_mask);
		अगर (ret)
			जाओ failed;

		चयन (clk_type) अणु
		हाल SMU_GFXCLK:
		हाल SMU_SCLK:
			ret = smu_cmn_send_smc_msg(smu, SMU_MSG_GetMaxGfxclkFrequency, max);
			अगर (ret) अणु
				dev_err(smu->adev->dev, "Attempt to get max GX frequency from SMC Failed !\n");
				जाओ failed;
			पूर्ण
			अवरोध;
		हाल SMU_UCLK:
		हाल SMU_FCLK:
		हाल SMU_MCLK:
			ret = renoir_get_dpm_clk_limited(smu, clk_type, mclk_mask, max);
			अगर (ret)
				जाओ failed;
			अवरोध;
		हाल SMU_SOCCLK:
			ret = renoir_get_dpm_clk_limited(smu, clk_type, soc_mask, max);
			अगर (ret)
				जाओ failed;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ failed;
		पूर्ण
	पूर्ण

	अगर (min) अणु
		चयन (clk_type) अणु
		हाल SMU_GFXCLK:
		हाल SMU_SCLK:
			ret = smu_cmn_send_smc_msg(smu, SMU_MSG_GetMinGfxclkFrequency, min);
			अगर (ret) अणु
				dev_err(smu->adev->dev, "Attempt to get min GX frequency from SMC Failed !\n");
				जाओ failed;
			पूर्ण
			अवरोध;
		हाल SMU_UCLK:
		हाल SMU_FCLK:
		हाल SMU_MCLK:
			ret = renoir_get_dpm_clk_limited(smu, clk_type, NUM_MEMCLK_DPM_LEVELS - 1, min);
			अगर (ret)
				जाओ failed;
			अवरोध;
		हाल SMU_SOCCLK:
			ret = renoir_get_dpm_clk_limited(smu, clk_type, 0, min);
			अगर (ret)
				जाओ failed;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ failed;
		पूर्ण
	पूर्ण
failed:
	वापस ret;
पूर्ण

अटल पूर्णांक renoir_od_edit_dpm_table(काष्ठा smu_context *smu,
							क्रमागत PP_OD_DPM_TABLE_COMMAND type,
							दीर्घ input[], uपूर्णांक32_t size)
अणु
	पूर्णांक ret = 0;
	काष्ठा smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);

	अगर (!(smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_MANUAL)) अणु
		dev_warn(smu->adev->dev,
			"pp_od_clk_voltage is not accessible if power_dpm_force_performance_level is not in manual mode!\n");
		वापस -EINVAL;
	पूर्ण

	चयन (type) अणु
	हाल PP_OD_EDIT_SCLK_VDDC_TABLE:
		अगर (size != 2) अणु
			dev_err(smu->adev->dev, "Input parameter number not correct\n");
			वापस -EINVAL;
		पूर्ण

		अगर (input[0] == 0) अणु
			अगर (input[1] < smu->gfx_शेष_hard_min_freq) अणु
				dev_warn(smu->adev->dev,
					"Fine grain setting minimum sclk (%ld) MHz is less than the minimum allowed (%d) MHz\n",
					input[1], smu->gfx_शेष_hard_min_freq);
				वापस -EINVAL;
			पूर्ण
			smu->gfx_actual_hard_min_freq = input[1];
		पूर्ण अन्यथा अगर (input[0] == 1) अणु
			अगर (input[1] > smu->gfx_शेष_soft_max_freq) अणु
				dev_warn(smu->adev->dev,
					"Fine grain setting maximum sclk (%ld) MHz is greater than the maximum allowed (%d) MHz\n",
					input[1], smu->gfx_शेष_soft_max_freq);
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
		पूर्ण
		smu->gfx_actual_hard_min_freq = smu->gfx_शेष_hard_min_freq;
		smu->gfx_actual_soft_max_freq = smu->gfx_शेष_soft_max_freq;
		अवरोध;
	हाल PP_OD_COMMIT_DPM_TABLE:
		अगर (size != 0) अणु
			dev_err(smu->adev->dev, "Input parameter number not correct\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (smu->gfx_actual_hard_min_freq > smu->gfx_actual_soft_max_freq) अणु
				dev_err(smu->adev->dev,
					"The setting minimun sclk (%d) MHz is greater than the setting maximum sclk (%d) MHz\n",
					smu->gfx_actual_hard_min_freq,
					smu->gfx_actual_soft_max_freq);
				वापस -EINVAL;
			पूर्ण

			ret = smu_cmn_send_smc_msg_with_param(smu,
								SMU_MSG_SetHardMinGfxClk,
								smu->gfx_actual_hard_min_freq,
								शून्य);
			अगर (ret) अणु
				dev_err(smu->adev->dev, "Set hard min sclk failed!");
				वापस ret;
			पूर्ण

			ret = smu_cmn_send_smc_msg_with_param(smu,
								SMU_MSG_SetSoftMaxGfxClk,
								smu->gfx_actual_soft_max_freq,
								शून्य);
			अगर (ret) अणु
				dev_err(smu->adev->dev, "Set soft max sclk failed!");
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक renoir_set_fine_grain_gfx_freq_parameters(काष्ठा smu_context *smu)
अणु
	uपूर्णांक32_t min = 0, max = 0;
	uपूर्णांक32_t ret = 0;

	ret = smu_cmn_send_smc_msg_with_param(smu,
								SMU_MSG_GetMinGfxclkFrequency,
								0, &min);
	अगर (ret)
		वापस ret;
	ret = smu_cmn_send_smc_msg_with_param(smu,
								SMU_MSG_GetMaxGfxclkFrequency,
								0, &max);
	अगर (ret)
		वापस ret;

	smu->gfx_शेष_hard_min_freq = min;
	smu->gfx_शेष_soft_max_freq = max;
	smu->gfx_actual_hard_min_freq = 0;
	smu->gfx_actual_soft_max_freq = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक renoir_prपूर्णांक_clk_levels(काष्ठा smu_context *smu,
			क्रमागत smu_clk_type clk_type, अक्षर *buf)
अणु
	पूर्णांक i, size = 0, ret = 0;
	uपूर्णांक32_t cur_value = 0, value = 0, count = 0, min = 0, max = 0;
	SmuMetrics_t metrics;
	काष्ठा smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);
	bool cur_value_match_level = false;

	स_रखो(&metrics, 0, माप(metrics));

	ret = smu_cmn_get_metrics_table(smu, &metrics, false);
	अगर (ret)
		वापस ret;

	चयन (clk_type) अणु
	हाल SMU_OD_RANGE:
		अगर (smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_MANUAL) अणु
			ret = smu_cmn_send_smc_msg_with_param(smu,
						SMU_MSG_GetMinGfxclkFrequency,
						0, &min);
			अगर (ret)
				वापस ret;
			ret = smu_cmn_send_smc_msg_with_param(smu,
						SMU_MSG_GetMaxGfxclkFrequency,
						0, &max);
			अगर (ret)
				वापस ret;
			size += प्र_लिखो(buf + size, "OD_RANGE\nSCLK: %10uMhz %10uMhz\n", min, max);
		पूर्ण
		अवरोध;
	हाल SMU_OD_SCLK:
		अगर (smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_MANUAL) अणु
			min = (smu->gfx_actual_hard_min_freq > 0) ? smu->gfx_actual_hard_min_freq : smu->gfx_शेष_hard_min_freq;
			max = (smu->gfx_actual_soft_max_freq > 0) ? smu->gfx_actual_soft_max_freq : smu->gfx_शेष_soft_max_freq;
			size += प्र_लिखो(buf + size, "OD_SCLK\n");
			size += प्र_लिखो(buf + size, "0:%10uMhz\n", min);
			size += प्र_लिखो(buf + size, "1:%10uMhz\n", max);
		पूर्ण
		अवरोध;
	हाल SMU_GFXCLK:
	हाल SMU_SCLK:
		/* retirve table वापसed paramters unit is MHz */
		cur_value = metrics.ClockFrequency[CLOCK_GFXCLK];
		ret = renoir_get_dpm_ultimate_freq(smu, SMU_GFXCLK, &min, &max);
		अगर (!ret) अणु
			/* driver only know min/max gfx_clk, Add level 1 क्रम all other gfx clks */
			अगर (cur_value  == max)
				i = 2;
			अन्यथा अगर (cur_value == min)
				i = 0;
			अन्यथा
				i = 1;

			size += प्र_लिखो(buf + size, "0: %uMhz %s\n", min,
					i == 0 ? "*" : "");
			size += प्र_लिखो(buf + size, "1: %uMhz %s\n",
					i == 1 ? cur_value : RENOIR_UMD_PSTATE_GFXCLK,
					i == 1 ? "*" : "");
			size += प्र_लिखो(buf + size, "2: %uMhz %s\n", max,
					i == 2 ? "*" : "");
		पूर्ण
		वापस size;
	हाल SMU_SOCCLK:
		count = NUM_SOCCLK_DPM_LEVELS;
		cur_value = metrics.ClockFrequency[CLOCK_SOCCLK];
		अवरोध;
	हाल SMU_MCLK:
		count = NUM_MEMCLK_DPM_LEVELS;
		cur_value = metrics.ClockFrequency[CLOCK_FCLK];
		अवरोध;
	हाल SMU_DCEFCLK:
		count = NUM_DCFCLK_DPM_LEVELS;
		cur_value = metrics.ClockFrequency[CLOCK_DCFCLK];
		अवरोध;
	हाल SMU_FCLK:
		count = NUM_FCLK_DPM_LEVELS;
		cur_value = metrics.ClockFrequency[CLOCK_FCLK];
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (clk_type) अणु
	हाल SMU_GFXCLK:
	हाल SMU_SCLK:
	हाल SMU_SOCCLK:
	हाल SMU_MCLK:
	हाल SMU_DCEFCLK:
	हाल SMU_FCLK:
		क्रम (i = 0; i < count; i++) अणु
			ret = renoir_get_dpm_clk_limited(smu, clk_type, i, &value);
			अगर (ret)
				वापस ret;
			अगर (!value)
				जारी;
			size += प्र_लिखो(buf + size, "%d: %uMhz %s\n", i, value,
					cur_value == value ? "*" : "");
			अगर (cur_value == value)
				cur_value_match_level = true;
		पूर्ण

		अगर (!cur_value_match_level)
			size += प्र_लिखो(buf + size, "   %uMhz *\n", cur_value);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस size;
पूर्ण

अटल क्रमागत amd_pm_state_type renoir_get_current_घातer_state(काष्ठा smu_context *smu)
अणु
	क्रमागत amd_pm_state_type pm_type;
	काष्ठा smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);

	अगर (!smu_dpm_ctx->dpm_context ||
	    !smu_dpm_ctx->dpm_current_घातer_state)
		वापस -EINVAL;

	चयन (smu_dpm_ctx->dpm_current_घातer_state->classअगरication.ui_label) अणु
	हाल SMU_STATE_UI_LABEL_BATTERY:
		pm_type = POWER_STATE_TYPE_BATTERY;
		अवरोध;
	हाल SMU_STATE_UI_LABEL_BALLANCED:
		pm_type = POWER_STATE_TYPE_BALANCED;
		अवरोध;
	हाल SMU_STATE_UI_LABEL_PERFORMANCE:
		pm_type = POWER_STATE_TYPE_PERFORMANCE;
		अवरोध;
	शेष:
		अगर (smu_dpm_ctx->dpm_current_घातer_state->classअगरication.flags & SMU_STATE_CLASSIFICATION_FLAG_BOOT)
			pm_type = POWER_STATE_TYPE_INTERNAL_BOOT;
		अन्यथा
			pm_type = POWER_STATE_TYPE_DEFAULT;
		अवरोध;
	पूर्ण

	वापस pm_type;
पूर्ण

अटल पूर्णांक renoir_dpm_set_vcn_enable(काष्ठा smu_context *smu, bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (enable) अणु
		/* vcn dpm on is a prerequisite क्रम vcn घातer gate messages */
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_VCN_PG_BIT)) अणु
			ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_PowerUpVcn, 0, शून्य);
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

अटल पूर्णांक renoir_dpm_set_jpeg_enable(काष्ठा smu_context *smu, bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (enable) अणु
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_JPEG_PG_BIT)) अणु
			ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_PowerUpJpeg, 0, शून्य);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (smu_cmn_feature_is_enabled(smu, SMU_FEATURE_JPEG_PG_BIT)) अणु
			ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_PowerDownJpeg, 0, शून्य);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक renoir_क्रमce_dpm_limit_value(काष्ठा smu_context *smu, bool highest)
अणु
	पूर्णांक ret = 0, i = 0;
	uपूर्णांक32_t min_freq, max_freq, क्रमce_freq;
	क्रमागत smu_clk_type clk_type;

	क्रमागत smu_clk_type clks[] = अणु
		SMU_GFXCLK,
		SMU_MCLK,
		SMU_SOCCLK,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(clks); i++) अणु
		clk_type = clks[i];
		ret = renoir_get_dpm_ultimate_freq(smu, clk_type, &min_freq, &max_freq);
		अगर (ret)
			वापस ret;

		क्रमce_freq = highest ? max_freq : min_freq;
		ret = smu_v12_0_set_soft_freq_limited_range(smu, clk_type, क्रमce_freq, क्रमce_freq);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक renoir_unक्रमce_dpm_levels(काष्ठा smu_context *smu) अणु

	पूर्णांक ret = 0, i = 0;
	uपूर्णांक32_t min_freq, max_freq;
	क्रमागत smu_clk_type clk_type;

	काष्ठा clk_feature_map अणु
		क्रमागत smu_clk_type clk_type;
		uपूर्णांक32_t	feature;
	पूर्ण clk_feature_map[] = अणु
		अणुSMU_GFXCLK, SMU_FEATURE_DPM_GFXCLK_BITपूर्ण,
		अणुSMU_MCLK,   SMU_FEATURE_DPM_UCLK_BITपूर्ण,
		अणुSMU_SOCCLK, SMU_FEATURE_DPM_SOCCLK_BITपूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(clk_feature_map); i++) अणु
		अगर (!smu_cmn_feature_is_enabled(smu, clk_feature_map[i].feature))
		    जारी;

		clk_type = clk_feature_map[i].clk_type;

		ret = renoir_get_dpm_ultimate_freq(smu, clk_type, &min_freq, &max_freq);
		अगर (ret)
			वापस ret;

		ret = smu_v12_0_set_soft_freq_limited_range(smu, clk_type, min_freq, max_freq);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This पूर्णांकerface get dpm घड़ी table क्रम dc
 */
अटल पूर्णांक renoir_get_dpm_घड़ी_प्रकारable(काष्ठा smu_context *smu, काष्ठा dpm_घड़ीs *घड़ी_प्रकारable)
अणु
	DpmClocks_t *table = smu->smu_table.घड़ीs_table;
	पूर्णांक i;

	अगर (!घड़ी_प्रकारable || !table)
		वापस -EINVAL;

	क्रम (i = 0; i < NUM_DCFCLK_DPM_LEVELS; i++) अणु
		घड़ी_प्रकारable->DcfClocks[i].Freq = table->DcfClocks[i].Freq;
		घड़ी_प्रकारable->DcfClocks[i].Vol = table->DcfClocks[i].Vol;
	पूर्ण

	क्रम (i = 0; i < NUM_SOCCLK_DPM_LEVELS; i++) अणु
		घड़ी_प्रकारable->SocClocks[i].Freq = table->SocClocks[i].Freq;
		घड़ी_प्रकारable->SocClocks[i].Vol = table->SocClocks[i].Vol;
	पूर्ण

	क्रम (i = 0; i < NUM_FCLK_DPM_LEVELS; i++) अणु
		घड़ी_प्रकारable->FClocks[i].Freq = table->FClocks[i].Freq;
		घड़ी_प्रकारable->FClocks[i].Vol = table->FClocks[i].Vol;
	पूर्ण

	क्रम (i = 0; i<  NUM_MEMCLK_DPM_LEVELS; i++) अणु
		घड़ी_प्रकारable->MemClocks[i].Freq = table->MemClocks[i].Freq;
		घड़ी_प्रकारable->MemClocks[i].Vol = table->MemClocks[i].Vol;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक renoir_क्रमce_clk_levels(काष्ठा smu_context *smu,
				   क्रमागत smu_clk_type clk_type, uपूर्णांक32_t mask)
अणु

	पूर्णांक ret = 0 ;
	uपूर्णांक32_t soft_min_level = 0, soft_max_level = 0, min_freq = 0, max_freq = 0;

	soft_min_level = mask ? (ffs(mask) - 1) : 0;
	soft_max_level = mask ? (fls(mask) - 1) : 0;

	चयन (clk_type) अणु
	हाल SMU_GFXCLK:
	हाल SMU_SCLK:
		अगर (soft_min_level > 2 || soft_max_level > 2) अणु
			dev_info(smu->adev->dev, "Currently sclk only support 3 levels on APU\n");
			वापस -EINVAL;
		पूर्ण

		ret = renoir_get_dpm_ultimate_freq(smu, SMU_GFXCLK, &min_freq, &max_freq);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetSoftMaxGfxClk,
					soft_max_level == 0 ? min_freq :
					soft_max_level == 1 ? RENOIR_UMD_PSTATE_GFXCLK : max_freq,
					शून्य);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetHardMinGfxClk,
					soft_min_level == 2 ? max_freq :
					soft_min_level == 1 ? RENOIR_UMD_PSTATE_GFXCLK : min_freq,
					शून्य);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल SMU_SOCCLK:
		ret = renoir_get_dpm_clk_limited(smu, clk_type, soft_min_level, &min_freq);
		अगर (ret)
			वापस ret;
		ret = renoir_get_dpm_clk_limited(smu, clk_type, soft_max_level, &max_freq);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetSoftMaxSocclkByFreq, max_freq, शून्य);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetHardMinSocclkByFreq, min_freq, शून्य);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल SMU_MCLK:
	हाल SMU_FCLK:
		ret = renoir_get_dpm_clk_limited(smu, clk_type, soft_min_level, &min_freq);
		अगर (ret)
			वापस ret;
		ret = renoir_get_dpm_clk_limited(smu, clk_type, soft_max_level, &max_freq);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetSoftMaxFclkByFreq, max_freq, शून्य);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetHardMinFclkByFreq, min_freq, शून्य);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक renoir_set_घातer_profile_mode(काष्ठा smu_context *smu, दीर्घ *input, uपूर्णांक32_t size)
अणु
	पूर्णांक workload_type, ret;
	uपूर्णांक32_t profile_mode = input[size];

	अगर (profile_mode > PP_SMC_POWER_PROखाता_CUSTOM) अणु
		dev_err(smu->adev->dev, "Invalid power profile mode %d\n", profile_mode);
		वापस -EINVAL;
	पूर्ण

	अगर (profile_mode == PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT ||
			profile_mode == PP_SMC_POWER_PROखाता_POWERSAVING)
		वापस 0;

	/* conv PP_SMC_POWER_PROखाता* to WORKLOAD_PPLIB_*_BIT */
	workload_type = smu_cmn_to_asic_specअगरic_index(smu,
						       CMN2ASIC_MAPPING_WORKLOAD,
						       profile_mode);
	अगर (workload_type < 0) अणु
		/*
		 * TODO: If some हाल need चयन to घातersave/शेष घातer mode
		 * then can consider enter WORKLOAD_COMPUTE/WORKLOAD_CUSTOM क्रम घातer saving.
		 */
		dev_dbg(smu->adev->dev, "Unsupported power profile mode %d on RENOIR\n", profile_mode);
		वापस -EINVAL;
	पूर्ण

	ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_ActiveProcessNotअगरy,
				    1 << workload_type,
				    शून्य);
	अगर (ret) अणु
		dev_err_once(smu->adev->dev, "Fail to set workload type %d\n", workload_type);
		वापस ret;
	पूर्ण

	smu->घातer_profile_mode = profile_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक renoir_set_peak_घड़ी_by_device(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t sclk_freq = 0, uclk_freq = 0;

	ret = renoir_get_dpm_ultimate_freq(smu, SMU_SCLK, शून्य, &sclk_freq);
	अगर (ret)
		वापस ret;

	ret = smu_v12_0_set_soft_freq_limited_range(smu, SMU_SCLK, sclk_freq, sclk_freq);
	अगर (ret)
		वापस ret;

	ret = renoir_get_dpm_ultimate_freq(smu, SMU_UCLK, शून्य, &uclk_freq);
	अगर (ret)
		वापस ret;

	ret = smu_v12_0_set_soft_freq_limited_range(smu, SMU_UCLK, uclk_freq, uclk_freq);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक renoir_set_perक्रमmance_level(काष्ठा smu_context *smu,
					क्रमागत amd_dpm_क्रमced_level level)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t sclk_mask, mclk_mask, soc_mask;

	चयन (level) अणु
	हाल AMD_DPM_FORCED_LEVEL_HIGH:
		smu->gfx_actual_hard_min_freq = smu->gfx_शेष_hard_min_freq;
		smu->gfx_actual_soft_max_freq = smu->gfx_शेष_soft_max_freq;

		ret = renoir_क्रमce_dpm_limit_value(smu, true);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_LOW:
		smu->gfx_actual_hard_min_freq = smu->gfx_शेष_hard_min_freq;
		smu->gfx_actual_soft_max_freq = smu->gfx_शेष_soft_max_freq;

		ret = renoir_क्रमce_dpm_limit_value(smu, false);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_AUTO:
		smu->gfx_actual_hard_min_freq = smu->gfx_शेष_hard_min_freq;
		smu->gfx_actual_soft_max_freq = smu->gfx_शेष_soft_max_freq;

		ret = renoir_unक्रमce_dpm_levels(smu);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD:
		smu->gfx_actual_hard_min_freq = smu->gfx_शेष_hard_min_freq;
		smu->gfx_actual_soft_max_freq = smu->gfx_शेष_soft_max_freq;

		ret = smu_cmn_send_smc_msg_with_param(smu,
						      SMU_MSG_SetHardMinGfxClk,
						      RENOIR_UMD_PSTATE_GFXCLK,
						      शून्य);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu,
						      SMU_MSG_SetHardMinFclkByFreq,
						      RENOIR_UMD_PSTATE_FCLK,
						      शून्य);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu,
						      SMU_MSG_SetHardMinSocclkByFreq,
						      RENOIR_UMD_PSTATE_SOCCLK,
						      शून्य);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu,
						      SMU_MSG_SetHardMinVcn,
						      RENOIR_UMD_PSTATE_VCNCLK,
						      शून्य);
		अगर (ret)
			वापस ret;

		ret = smu_cmn_send_smc_msg_with_param(smu,
						      SMU_MSG_SetSoftMaxGfxClk,
						      RENOIR_UMD_PSTATE_GFXCLK,
						      शून्य);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu,
						      SMU_MSG_SetSoftMaxFclkByFreq,
						      RENOIR_UMD_PSTATE_FCLK,
						      शून्य);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu,
						      SMU_MSG_SetSoftMaxSocclkByFreq,
						      RENOIR_UMD_PSTATE_SOCCLK,
						      शून्य);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu,
						      SMU_MSG_SetSoftMaxVcn,
						      RENOIR_UMD_PSTATE_VCNCLK,
						      शून्य);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK:
		smu->gfx_actual_hard_min_freq = smu->gfx_शेष_hard_min_freq;
		smu->gfx_actual_soft_max_freq = smu->gfx_शेष_soft_max_freq;

		ret = renoir_get_profiling_clk_mask(smu, level,
						    &sclk_mask,
						    &mclk_mask,
						    &soc_mask);
		अगर (ret)
			वापस ret;
		renoir_क्रमce_clk_levels(smu, SMU_SCLK, 1 << sclk_mask);
		renoir_क्रमce_clk_levels(smu, SMU_MCLK, 1 << mclk_mask);
		renoir_क्रमce_clk_levels(smu, SMU_SOCCLK, 1 << soc_mask);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_PEAK:
		smu->gfx_actual_hard_min_freq = smu->gfx_शेष_hard_min_freq;
		smu->gfx_actual_soft_max_freq = smu->gfx_शेष_soft_max_freq;

		ret = renoir_set_peak_घड़ी_by_device(smu);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_MANUAL:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_EXIT:
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/* save watermark settings पूर्णांकo pplib smu काष्ठाure,
 * also pass data to smu controller
 */
अटल पूर्णांक renoir_set_watermarks_table(
		काष्ठा smu_context *smu,
		काष्ठा pp_smu_wm_range_sets *घड़ी_ranges)
अणु
	Watermarks_t *table = smu->smu_table.watermarks_table;
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (घड़ी_ranges) अणु
		अगर (घड़ी_ranges->num_पढ़ोer_wm_sets > NUM_WM_RANGES ||
		    घड़ी_ranges->num_ग_लिखोr_wm_sets > NUM_WM_RANGES)
			वापस -EINVAL;

		/* save पूर्णांकo smu->smu_table.tables[SMU_TABLE_WATERMARKS]->cpu_addr*/
		क्रम (i = 0; i < घड़ी_ranges->num_पढ़ोer_wm_sets; i++) अणु
			table->WatermarkRow[WM_DCFCLK][i].MinClock =
				घड़ी_ranges->पढ़ोer_wm_sets[i].min_drain_clk_mhz;
			table->WatermarkRow[WM_DCFCLK][i].MaxClock =
				घड़ी_ranges->पढ़ोer_wm_sets[i].max_drain_clk_mhz;
			table->WatermarkRow[WM_DCFCLK][i].MinMclk =
				घड़ी_ranges->पढ़ोer_wm_sets[i].min_fill_clk_mhz;
			table->WatermarkRow[WM_DCFCLK][i].MaxMclk =
				घड़ी_ranges->पढ़ोer_wm_sets[i].max_fill_clk_mhz;

			table->WatermarkRow[WM_DCFCLK][i].WmSetting =
				घड़ी_ranges->पढ़ोer_wm_sets[i].wm_inst;
			table->WatermarkRow[WM_DCFCLK][i].WmType =
				घड़ी_ranges->पढ़ोer_wm_sets[i].wm_type;
		पूर्ण

		क्रम (i = 0; i < घड़ी_ranges->num_ग_लिखोr_wm_sets; i++) अणु
			table->WatermarkRow[WM_SOCCLK][i].MinClock =
				घड़ी_ranges->ग_लिखोr_wm_sets[i].min_fill_clk_mhz;
			table->WatermarkRow[WM_SOCCLK][i].MaxClock =
				घड़ी_ranges->ग_लिखोr_wm_sets[i].max_fill_clk_mhz;
			table->WatermarkRow[WM_SOCCLK][i].MinMclk =
				घड़ी_ranges->ग_लिखोr_wm_sets[i].min_drain_clk_mhz;
			table->WatermarkRow[WM_SOCCLK][i].MaxMclk =
				घड़ी_ranges->ग_लिखोr_wm_sets[i].max_drain_clk_mhz;

			table->WatermarkRow[WM_SOCCLK][i].WmSetting =
				घड़ी_ranges->ग_लिखोr_wm_sets[i].wm_inst;
			table->WatermarkRow[WM_SOCCLK][i].WmType =
				घड़ी_ranges->ग_लिखोr_wm_sets[i].wm_type;
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

अटल पूर्णांक renoir_get_घातer_profile_mode(काष्ठा smu_context *smu,
					   अक्षर *buf)
अणु
	अटल स्थिर अक्षर *profile_name[] = अणु
					"BOOTUP_DEFAULT",
					"3D_FULL_SCREEN",
					"POWER_SAVING",
					"VIDEO",
					"VR",
					"COMPUTE",
					"CUSTOM"पूर्ण;
	uपूर्णांक32_t i, size = 0;
	पूर्णांक16_t workload_type = 0;

	अगर (!buf)
		वापस -EINVAL;

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

		size += प्र_लिखो(buf + size, "%2d %14s%s\n",
			i, profile_name[i], (i == smu->घातer_profile_mode) ? "*" : " ");
	पूर्ण

	वापस size;
पूर्ण

अटल पूर्णांक renoir_get_smu_metrics_data(काष्ठा smu_context *smu,
				       MetricsMember_t member,
				       uपूर्णांक32_t *value)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;

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
	हाल METRICS_AVERAGE_GFXCLK:
		*value = metrics->ClockFrequency[CLOCK_GFXCLK];
		अवरोध;
	हाल METRICS_AVERAGE_SOCCLK:
		*value = metrics->ClockFrequency[CLOCK_SOCCLK];
		अवरोध;
	हाल METRICS_AVERAGE_UCLK:
		*value = metrics->ClockFrequency[CLOCK_FCLK];
		अवरोध;
	हाल METRICS_AVERAGE_GFXACTIVITY:
		*value = metrics->AverageGfxActivity / 100;
		अवरोध;
	हाल METRICS_AVERAGE_VCNACTIVITY:
		*value = metrics->AverageUvdActivity / 100;
		अवरोध;
	हाल METRICS_AVERAGE_SOCKETPOWER:
		*value = (metrics->CurrentSocketPower << 8) / 1000;
		अवरोध;
	हाल METRICS_TEMPERATURE_EDGE:
		*value = (metrics->GfxTemperature / 100) *
			SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
		अवरोध;
	हाल METRICS_TEMPERATURE_HOTSPOT:
		*value = (metrics->SocTemperature / 100) *
			SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
		अवरोध;
	हाल METRICS_THROTTLER_STATUS:
		*value = metrics->ThrottlerStatus;
		अवरोध;
	हाल METRICS_VOLTAGE_VDDGFX:
		*value = metrics->Voltage[0];
		अवरोध;
	हाल METRICS_VOLTAGE_VDDSOC:
		*value = metrics->Voltage[1];
		अवरोध;
	शेष:
		*value = अच_पूर्णांक_उच्च;
		अवरोध;
	पूर्ण

	mutex_unlock(&smu->metrics_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक renoir_पढ़ो_sensor(काष्ठा smu_context *smu,
				 क्रमागत amd_pp_sensors sensor,
				 व्योम *data, uपूर्णांक32_t *size)
अणु
	पूर्णांक ret = 0;

	अगर (!data || !size)
		वापस -EINVAL;

	mutex_lock(&smu->sensor_lock);
	चयन (sensor) अणु
	हाल AMDGPU_PP_SENSOR_GPU_LOAD:
		ret = renoir_get_smu_metrics_data(smu,
						  METRICS_AVERAGE_GFXACTIVITY,
						  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_EDGE_TEMP:
		ret = renoir_get_smu_metrics_data(smu,
						  METRICS_TEMPERATURE_EDGE,
						  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_HOTSPOT_TEMP:
		ret = renoir_get_smu_metrics_data(smu,
						  METRICS_TEMPERATURE_HOTSPOT,
						  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GFX_MCLK:
		ret = renoir_get_smu_metrics_data(smu,
						  METRICS_AVERAGE_UCLK,
						  (uपूर्णांक32_t *)data);
		*(uपूर्णांक32_t *)data *= 100;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GFX_SCLK:
		ret = renoir_get_smu_metrics_data(smu,
						  METRICS_AVERAGE_GFXCLK,
						  (uपूर्णांक32_t *)data);
		*(uपूर्णांक32_t *)data *= 100;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_VDDGFX:
		ret = renoir_get_smu_metrics_data(smu,
						  METRICS_VOLTAGE_VDDGFX,
						  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_VDDNB:
		ret = renoir_get_smu_metrics_data(smu,
						  METRICS_VOLTAGE_VDDSOC,
						  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GPU_POWER:
		ret = renoir_get_smu_metrics_data(smu,
						  METRICS_AVERAGE_SOCKETPOWER,
						  (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	mutex_unlock(&smu->sensor_lock);

	वापस ret;
पूर्ण

अटल bool renoir_is_dpm_running(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;

	/*
	 * Until now, the pmfw hasn't exported the पूर्णांकerface of SMU
	 * feature mask to APU SKU so just क्रमce on all the feature
	 * at early initial stage.
	 */
	अगर (adev->in_suspend)
		वापस false;
	अन्यथा
		वापस true;

पूर्ण

अटल sमाप_प्रकार renoir_get_gpu_metrics(काष्ठा smu_context *smu,
				      व्योम **table)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा gpu_metrics_v2_1 *gpu_metrics =
		(काष्ठा gpu_metrics_v2_1 *)smu_table->gpu_metrics_table;
	SmuMetrics_t metrics;
	पूर्णांक ret = 0;

	ret = smu_cmn_get_metrics_table(smu, &metrics, true);
	अगर (ret)
		वापस ret;

	smu_cmn_init_soft_gpu_metrics(gpu_metrics, 2, 1);

	gpu_metrics->temperature_gfx = metrics.GfxTemperature;
	gpu_metrics->temperature_soc = metrics.SocTemperature;
	स_नकल(&gpu_metrics->temperature_core[0],
		&metrics.CoreTemperature[0],
		माप(uपूर्णांक16_t) * 8);
	gpu_metrics->temperature_l3[0] = metrics.L3Temperature[0];
	gpu_metrics->temperature_l3[1] = metrics.L3Temperature[1];

	gpu_metrics->average_gfx_activity = metrics.AverageGfxActivity;
	gpu_metrics->average_mm_activity = metrics.AverageUvdActivity;

	gpu_metrics->average_socket_घातer = metrics.CurrentSocketPower;
	gpu_metrics->average_cpu_घातer = metrics.Power[0];
	gpu_metrics->average_soc_घातer = metrics.Power[1];
	स_नकल(&gpu_metrics->average_core_घातer[0],
		&metrics.CorePower[0],
		माप(uपूर्णांक16_t) * 8);

	gpu_metrics->average_gfxclk_frequency = metrics.AverageGfxclkFrequency;
	gpu_metrics->average_socclk_frequency = metrics.AverageSocclkFrequency;
	gpu_metrics->average_fclk_frequency = metrics.AverageFclkFrequency;
	gpu_metrics->average_vclk_frequency = metrics.AverageVclkFrequency;

	gpu_metrics->current_gfxclk = metrics.ClockFrequency[CLOCK_GFXCLK];
	gpu_metrics->current_socclk = metrics.ClockFrequency[CLOCK_SOCCLK];
	gpu_metrics->current_uclk = metrics.ClockFrequency[CLOCK_UMCCLK];
	gpu_metrics->current_fclk = metrics.ClockFrequency[CLOCK_FCLK];
	gpu_metrics->current_vclk = metrics.ClockFrequency[CLOCK_VCLK];
	gpu_metrics->current_dclk = metrics.ClockFrequency[CLOCK_DCLK];
	स_नकल(&gpu_metrics->current_coreclk[0],
		&metrics.CoreFrequency[0],
		माप(uपूर्णांक16_t) * 8);
	gpu_metrics->current_l3clk[0] = metrics.L3Frequency[0];
	gpu_metrics->current_l3clk[1] = metrics.L3Frequency[1];

	gpu_metrics->throttle_status = metrics.ThrottlerStatus;

	gpu_metrics->fan_pwm = metrics.FanPwm;

	gpu_metrics->प्रणाली_घड़ी_counter = kसमय_get_bootसमय_ns();

	*table = (व्योम *)gpu_metrics;

	वापस माप(काष्ठा gpu_metrics_v2_1);
पूर्ण

अटल पूर्णांक renoir_gfx_state_change_set(काष्ठा smu_context *smu, uपूर्णांक32_t state)
अणु

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pptable_funcs renoir_ppt_funcs = अणु
	.set_घातer_state = शून्य,
	.prपूर्णांक_clk_levels = renoir_prपूर्णांक_clk_levels,
	.get_current_घातer_state = renoir_get_current_घातer_state,
	.dpm_set_vcn_enable = renoir_dpm_set_vcn_enable,
	.dpm_set_jpeg_enable = renoir_dpm_set_jpeg_enable,
	.क्रमce_clk_levels = renoir_क्रमce_clk_levels,
	.set_घातer_profile_mode = renoir_set_घातer_profile_mode,
	.set_perक्रमmance_level = renoir_set_perक्रमmance_level,
	.get_dpm_घड़ी_प्रकारable = renoir_get_dpm_घड़ी_प्रकारable,
	.set_watermarks_table = renoir_set_watermarks_table,
	.get_घातer_profile_mode = renoir_get_घातer_profile_mode,
	.पढ़ो_sensor = renoir_पढ़ो_sensor,
	.check_fw_status = smu_v12_0_check_fw_status,
	.check_fw_version = smu_v12_0_check_fw_version,
	.घातergate_sdma = smu_v12_0_घातergate_sdma,
	.send_smc_msg_with_param = smu_cmn_send_smc_msg_with_param,
	.send_smc_msg = smu_cmn_send_smc_msg,
	.set_gfx_cgpg = smu_v12_0_set_gfx_cgpg,
	.gfx_off_control = smu_v12_0_gfx_off_control,
	.get_gfx_off_status = smu_v12_0_get_gfxoff_status,
	.init_smc_tables = renoir_init_smc_tables,
	.fini_smc_tables = smu_v12_0_fini_smc_tables,
	.set_शेष_dpm_table = smu_v12_0_set_शेष_dpm_tables,
	.get_enabled_mask = smu_cmn_get_enabled_mask,
	.feature_is_enabled = smu_cmn_feature_is_enabled,
	.disable_all_features_with_exception = smu_cmn_disable_all_features_with_exception,
	.get_dpm_ultimate_freq = renoir_get_dpm_ultimate_freq,
	.mode2_reset = smu_v12_0_mode2_reset,
	.set_soft_freq_limited_range = smu_v12_0_set_soft_freq_limited_range,
	.set_driver_table_location = smu_v12_0_set_driver_table_location,
	.is_dpm_running = renoir_is_dpm_running,
	.get_pp_feature_mask = smu_cmn_get_pp_feature_mask,
	.set_pp_feature_mask = smu_cmn_set_pp_feature_mask,
	.get_gpu_metrics = renoir_get_gpu_metrics,
	.gfx_state_change_set = renoir_gfx_state_change_set,
	.set_fine_grain_gfx_freq_parameters = renoir_set_fine_grain_gfx_freq_parameters,
	.od_edit_dpm_table = renoir_od_edit_dpm_table,
	.get_vbios_bootup_values = smu_v12_0_get_vbios_bootup_values,
पूर्ण;

व्योम renoir_set_ppt_funcs(काष्ठा smu_context *smu)
अणु
	smu->ppt_funcs = &renoir_ppt_funcs;
	smu->message_map = renoir_message_map;
	smu->घड़ी_map = renoir_clk_map;
	smu->table_map = renoir_table_map;
	smu->workload_map = renoir_workload_map;
	smu->smc_driver_अगर_version = SMU12_DRIVER_IF_VERSION;
	smu->is_apu = true;
पूर्ण
