<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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
#समावेश "smu_v11_0.h"
#समावेश "smu11_driver_if_vangogh.h"
#समावेश "vangogh_ppt.h"
#समावेश "smu_v11_5_ppsmc.h"
#समावेश "smu_v11_5_pmfw.h"
#समावेश "smu_cmn.h"
#समावेश "soc15_common.h"
#समावेश "asic_reg/gc/gc_10_3_0_offset.h"
#समावेश "asic_reg/gc/gc_10_3_0_sh_mask.h"
#समावेश <यंत्र/processor.h>

/*
 * DO NOT use these क्रम err/warn/info/debug messages.
 * Use dev_err, dev_warn, dev_info and dev_dbg instead.
 * They are more MGPU मित्रly.
 */
#अघोषित pr_err
#अघोषित pr_warn
#अघोषित pr_info
#अघोषित pr_debug

#घोषणा FEATURE_MASK(feature) (1ULL << feature)
#घोषणा SMC_DPM_FEATURE ( \
	FEATURE_MASK(FEATURE_CCLK_DPM_BIT) | \
	FEATURE_MASK(FEATURE_VCN_DPM_BIT)	 | \
	FEATURE_MASK(FEATURE_FCLK_DPM_BIT)	 | \
	FEATURE_MASK(FEATURE_SOCCLK_DPM_BIT)	 | \
	FEATURE_MASK(FEATURE_MP0CLK_DPM_BIT)	 | \
	FEATURE_MASK(FEATURE_LCLK_DPM_BIT)	 | \
	FEATURE_MASK(FEATURE_SHUBCLK_DPM_BIT)	 | \
	FEATURE_MASK(FEATURE_DCFCLK_DPM_BIT)| \
	FEATURE_MASK(FEATURE_GFX_DPM_BIT))

अटल काष्ठा cmn2asic_msg_mapping vangogh_message_map[SMU_MSG_MAX_COUNT] = अणु
	MSG_MAP(TestMessage,                    PPSMC_MSG_TestMessage,			0),
	MSG_MAP(GetSmuVersion,                  PPSMC_MSG_GetSmuVersion,		0),
	MSG_MAP(GetDriverIfVersion,             PPSMC_MSG_GetDriverIfVersion,	0),
	MSG_MAP(EnableGfxOff,                   PPSMC_MSG_EnableGfxOff,			0),
	MSG_MAP(AllowGfxOff,                    PPSMC_MSG_AllowGfxOff,          0),
	MSG_MAP(DisallowGfxOff,                 PPSMC_MSG_DisallowGfxOff,		0),
	MSG_MAP(PowerDownIspByTile,             PPSMC_MSG_PowerDownIspByTile,	0),
	MSG_MAP(PowerUpIspByTile,               PPSMC_MSG_PowerUpIspByTile,		0),
	MSG_MAP(PowerDownVcn,                   PPSMC_MSG_PowerDownVcn,			0),
	MSG_MAP(PowerUpVcn,                     PPSMC_MSG_PowerUpVcn,			0),
	MSG_MAP(RlcPowerNotअगरy,                 PPSMC_MSG_RlcPowerNotअगरy,		0),
	MSG_MAP(SetHardMinVcn,                  PPSMC_MSG_SetHardMinVcn,		0),
	MSG_MAP(SetSoftMinGfxclk,               PPSMC_MSG_SetSoftMinGfxclk,		0),
	MSG_MAP(ActiveProcessNotअगरy,            PPSMC_MSG_ActiveProcessNotअगरy,		0),
	MSG_MAP(SetHardMinIspiclkByFreq,        PPSMC_MSG_SetHardMinIspiclkByFreq,	0),
	MSG_MAP(SetHardMinIspxclkByFreq,        PPSMC_MSG_SetHardMinIspxclkByFreq,	0),
	MSG_MAP(SetDriverDramAddrHigh,          PPSMC_MSG_SetDriverDramAddrHigh,	0),
	MSG_MAP(SetDriverDramAddrLow,           PPSMC_MSG_SetDriverDramAddrLow,		0),
	MSG_MAP(TransferTableSmu2Dram,          PPSMC_MSG_TransferTableSmu2Dram,	0),
	MSG_MAP(TransferTableDram2Smu,          PPSMC_MSG_TransferTableDram2Smu,	0),
	MSG_MAP(GfxDeviceDriverReset,           PPSMC_MSG_GfxDeviceDriverReset,		0),
	MSG_MAP(GetEnabledSmuFeatures,          PPSMC_MSG_GetEnabledSmuFeatures,	0),
	MSG_MAP(SetHardMinSocclkByFreq,         PPSMC_MSG_SetHardMinSocclkByFreq,	0),
	MSG_MAP(SetSoftMinFclk,                 PPSMC_MSG_SetSoftMinFclk,		0),
	MSG_MAP(SetSoftMinVcn,                  PPSMC_MSG_SetSoftMinVcn,		0),
	MSG_MAP(EnablePostCode,                 PPSMC_MSG_EnablePostCode,		0),
	MSG_MAP(GetGfxclkFrequency,             PPSMC_MSG_GetGfxclkFrequency,	0),
	MSG_MAP(GetFclkFrequency,               PPSMC_MSG_GetFclkFrequency,		0),
	MSG_MAP(SetSoftMaxGfxClk,               PPSMC_MSG_SetSoftMaxGfxClk,		0),
	MSG_MAP(SetHardMinGfxClk,               PPSMC_MSG_SetHardMinGfxClk,		0),
	MSG_MAP(SetSoftMaxSocclkByFreq,         PPSMC_MSG_SetSoftMaxSocclkByFreq,	0),
	MSG_MAP(SetSoftMaxFclkByFreq,           PPSMC_MSG_SetSoftMaxFclkByFreq,		0),
	MSG_MAP(SetSoftMaxVcn,                  PPSMC_MSG_SetSoftMaxVcn,			0),
	MSG_MAP(SetPowerLimitPercentage,        PPSMC_MSG_SetPowerLimitPercentage,	0),
	MSG_MAP(PowerDownJpeg,                  PPSMC_MSG_PowerDownJpeg,			0),
	MSG_MAP(PowerUpJpeg,                    PPSMC_MSG_PowerUpJpeg,				0),
	MSG_MAP(SetHardMinFclkByFreq,           PPSMC_MSG_SetHardMinFclkByFreq,		0),
	MSG_MAP(SetSoftMinSocclkByFreq,         PPSMC_MSG_SetSoftMinSocclkByFreq,	0),
	MSG_MAP(PowerUpCvip,                    PPSMC_MSG_PowerUpCvip,				0),
	MSG_MAP(PowerDownCvip,                  PPSMC_MSG_PowerDownCvip,			0),
	MSG_MAP(GetPptLimit,                        PPSMC_MSG_GetPptLimit,			0),
	MSG_MAP(GetThermalLimit,                    PPSMC_MSG_GetThermalLimit,		0),
	MSG_MAP(GetCurrentTemperature,              PPSMC_MSG_GetCurrentTemperature, 0),
	MSG_MAP(GetCurrentPower,                    PPSMC_MSG_GetCurrentPower,		 0),
	MSG_MAP(GetCurrentVoltage,                  PPSMC_MSG_GetCurrentVoltage,	 0),
	MSG_MAP(GetCurrentCurrent,                  PPSMC_MSG_GetCurrentCurrent,	 0),
	MSG_MAP(GetAverageCpuActivity,              PPSMC_MSG_GetAverageCpuActivity, 0),
	MSG_MAP(GetAverageGfxActivity,              PPSMC_MSG_GetAverageGfxActivity, 0),
	MSG_MAP(GetAveragePower,                    PPSMC_MSG_GetAveragePower,		 0),
	MSG_MAP(GetAverageTemperature,              PPSMC_MSG_GetAverageTemperature, 0),
	MSG_MAP(SetAveragePowerTimeConstant,        PPSMC_MSG_SetAveragePowerTimeConstant,			0),
	MSG_MAP(SetAverageActivityTimeConstant,     PPSMC_MSG_SetAverageActivityTimeConstant,		0),
	MSG_MAP(SetAverageTemperatureTimeConstant,  PPSMC_MSG_SetAverageTemperatureTimeConstant,	0),
	MSG_MAP(SetMitigationEndHysteresis,         PPSMC_MSG_SetMitigationEndHysteresis,			0),
	MSG_MAP(GetCurrentFreq,                     PPSMC_MSG_GetCurrentFreq,						0),
	MSG_MAP(SetReducedPptLimit,                 PPSMC_MSG_SetReducedPptLimit,					0),
	MSG_MAP(SetReducedThermalLimit,             PPSMC_MSG_SetReducedThermalLimit,				0),
	MSG_MAP(DramLogSetDramAddr,                 PPSMC_MSG_DramLogSetDramAddr,					0),
	MSG_MAP(StartDramLogging,                   PPSMC_MSG_StartDramLogging,						0),
	MSG_MAP(StopDramLogging,                    PPSMC_MSG_StopDramLogging,						0),
	MSG_MAP(SetSoftMinCclk,                     PPSMC_MSG_SetSoftMinCclk,						0),
	MSG_MAP(SetSoftMaxCclk,                     PPSMC_MSG_SetSoftMaxCclk,						0),
	MSG_MAP(RequestActiveWgp,                   PPSMC_MSG_RequestActiveWgp,                     0),
	MSG_MAP(SetFastPPTLimit,                    PPSMC_MSG_SetFastPPTLimit,						0),
	MSG_MAP(SetSlowPPTLimit,                    PPSMC_MSG_SetSlowPPTLimit,						0),
	MSG_MAP(GetFastPPTLimit,                    PPSMC_MSG_GetFastPPTLimit,						0),
	MSG_MAP(GetSlowPPTLimit,                    PPSMC_MSG_GetSlowPPTLimit,						0),
पूर्ण;

अटल काष्ठा cmn2asic_mapping vangogh_feature_mask_map[SMU_FEATURE_COUNT] = अणु
	FEA_MAP(PPT),
	FEA_MAP(TDC),
	FEA_MAP(THERMAL),
	FEA_MAP(DS_GFXCLK),
	FEA_MAP(DS_SOCCLK),
	FEA_MAP(DS_LCLK),
	FEA_MAP(DS_FCLK),
	FEA_MAP(DS_MP1CLK),
	FEA_MAP(DS_MP0CLK),
	FEA_MAP(ATHUB_PG),
	FEA_MAP(CCLK_DPM),
	FEA_MAP(FAN_CONTROLLER),
	FEA_MAP(ULV),
	FEA_MAP(VCN_DPM),
	FEA_MAP(LCLK_DPM),
	FEA_MAP(SHUBCLK_DPM),
	FEA_MAP(DCFCLK_DPM),
	FEA_MAP(DS_DCFCLK),
	FEA_MAP(S0I2),
	FEA_MAP(SMU_LOW_POWER),
	FEA_MAP(GFX_DEM),
	FEA_MAP(PSI),
	FEA_MAP(PROCHOT),
	FEA_MAP(CPUOFF),
	FEA_MAP(STAPM),
	FEA_MAP(S0I3),
	FEA_MAP(DF_CSTATES),
	FEA_MAP(PERF_LIMIT),
	FEA_MAP(CORE_DLDO),
	FEA_MAP(RSMU_LOW_POWER),
	FEA_MAP(SMN_LOW_POWER),
	FEA_MAP(THM_LOW_POWER),
	FEA_MAP(SMUIO_LOW_POWER),
	FEA_MAP(MP1_LOW_POWER),
	FEA_MAP(DS_VCN),
	FEA_MAP(CPPC),
	FEA_MAP(OS_CSTATES),
	FEA_MAP(ISP_DPM),
	FEA_MAP(A55_DPM),
	FEA_MAP(CVIP_DSP_DPM),
	FEA_MAP(MSMU_LOW_POWER),
	FEA_MAP_REVERSE(SOCCLK),
	FEA_MAP_REVERSE(FCLK),
	FEA_MAP_HALF_REVERSE(GFX),
पूर्ण;

अटल काष्ठा cmn2asic_mapping vangogh_table_map[SMU_TABLE_COUNT] = अणु
	TAB_MAP_VALID(WATERMARKS),
	TAB_MAP_VALID(SMU_METRICS),
	TAB_MAP_VALID(CUSTOM_DPM),
	TAB_MAP_VALID(DPMCLOCKS),
पूर्ण;

अटल काष्ठा cmn2asic_mapping vangogh_workload_map[PP_SMC_POWER_PROखाता_COUNT] = अणु
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_FULLSCREEN3D,		WORKLOAD_PPLIB_FULL_SCREEN_3D_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_VIDEO,		WORKLOAD_PPLIB_VIDEO_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_VR,			WORKLOAD_PPLIB_VR_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_COMPUTE,		WORKLOAD_PPLIB_COMPUTE_BIT),
	WORKLOAD_MAP(PP_SMC_POWER_PROखाता_CUSTOM,		WORKLOAD_PPLIB_CUSTOM_BIT),
पूर्ण;

अटल पूर्णांक vangogh_tables_init(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा smu_table *tables = smu_table->tables;
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t अगर_version;
	uपूर्णांक32_t ret = 0;

	ret = smu_cmn_get_smc_version(smu, &अगर_version, शून्य);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to get smu if version!\n");
		जाओ err0_out;
	पूर्ण

	SMU_TABLE_INIT(tables, SMU_TABLE_WATERMARKS, माप(Watermarks_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_DPMCLOCKS, माप(DpmClocks_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_PMSTATUSLOG, SMU11_TOOL_SIZE,
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
	SMU_TABLE_INIT(tables, SMU_TABLE_ACTIVITY_MONITOR_COEFF, माप(DpmActivityMonitorCoeffExt_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);

	अगर (अगर_version < 0x3) अणु
		SMU_TABLE_INIT(tables, SMU_TABLE_SMU_METRICS, माप(SmuMetrics_legacy_t),
				PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
		smu_table->metrics_table = kzalloc(माप(SmuMetrics_legacy_t), GFP_KERNEL);
	पूर्ण अन्यथा अणु
		SMU_TABLE_INIT(tables, SMU_TABLE_SMU_METRICS, माप(SmuMetrics_t),
				PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM);
		smu_table->metrics_table = kzalloc(माप(SmuMetrics_t), GFP_KERNEL);
	पूर्ण
	अगर (!smu_table->metrics_table)
		जाओ err0_out;
	smu_table->metrics_समय = 0;

	smu_table->gpu_metrics_table_size = माप(काष्ठा gpu_metrics_v2_1);
	smu_table->gpu_metrics_table = kzalloc(smu_table->gpu_metrics_table_size, GFP_KERNEL);
	अगर (!smu_table->gpu_metrics_table)
		जाओ err1_out;

	smu_table->watermarks_table = kzalloc(माप(Watermarks_t), GFP_KERNEL);
	अगर (!smu_table->watermarks_table)
		जाओ err2_out;

	smu_table->घड़ीs_table = kzalloc(माप(DpmClocks_t), GFP_KERNEL);
	अगर (!smu_table->घड़ीs_table)
		जाओ err3_out;

	वापस 0;

err3_out:
	kमुक्त(smu_table->घड़ीs_table);
err2_out:
	kमुक्त(smu_table->gpu_metrics_table);
err1_out:
	kमुक्त(smu_table->metrics_table);
err0_out:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक vangogh_get_legacy_smu_metrics_data(काष्ठा smu_context *smu,
				       MetricsMember_t member,
				       uपूर्णांक32_t *value)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	SmuMetrics_legacy_t *metrics = (SmuMetrics_legacy_t *)smu_table->metrics_table;
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
		*value = metrics->GfxclkFrequency;
		अवरोध;
	हाल METRICS_AVERAGE_SOCCLK:
		*value = metrics->SocclkFrequency;
		अवरोध;
	हाल METRICS_AVERAGE_VCLK:
		*value = metrics->VclkFrequency;
		अवरोध;
	हाल METRICS_AVERAGE_DCLK:
		*value = metrics->DclkFrequency;
		अवरोध;
	हाल METRICS_CURR_UCLK:
		*value = metrics->MemclkFrequency;
		अवरोध;
	हाल METRICS_AVERAGE_GFXACTIVITY:
		*value = metrics->GfxActivity / 100;
		अवरोध;
	हाल METRICS_AVERAGE_VCNACTIVITY:
		*value = metrics->UvdActivity;
		अवरोध;
	हाल METRICS_AVERAGE_SOCKETPOWER:
		*value = (metrics->CurrentSocketPower << 8) /
		1000 ;
		अवरोध;
	हाल METRICS_TEMPERATURE_EDGE:
		*value = metrics->GfxTemperature / 100 *
		SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
		अवरोध;
	हाल METRICS_TEMPERATURE_HOTSPOT:
		*value = metrics->SocTemperature / 100 *
		SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
		अवरोध;
	हाल METRICS_THROTTLER_STATUS:
		*value = metrics->ThrottlerStatus;
		अवरोध;
	हाल METRICS_VOLTAGE_VDDGFX:
		*value = metrics->Voltage[2];
		अवरोध;
	हाल METRICS_VOLTAGE_VDDSOC:
		*value = metrics->Voltage[1];
		अवरोध;
	हाल METRICS_AVERAGE_CPUCLK:
		स_नकल(value, &metrics->CoreFrequency[0],
		       smu->cpu_core_num * माप(uपूर्णांक16_t));
		अवरोध;
	शेष:
		*value = अच_पूर्णांक_उच्च;
		अवरोध;
	पूर्ण

	mutex_unlock(&smu->metrics_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक vangogh_get_smu_metrics_data(काष्ठा smu_context *smu,
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
	हाल METRICS_CURR_GFXCLK:
		*value = metrics->Current.GfxclkFrequency;
		अवरोध;
	हाल METRICS_AVERAGE_SOCCLK:
		*value = metrics->Current.SocclkFrequency;
		अवरोध;
	हाल METRICS_AVERAGE_VCLK:
		*value = metrics->Current.VclkFrequency;
		अवरोध;
	हाल METRICS_AVERAGE_DCLK:
		*value = metrics->Current.DclkFrequency;
		अवरोध;
	हाल METRICS_CURR_UCLK:
		*value = metrics->Current.MemclkFrequency;
		अवरोध;
	हाल METRICS_AVERAGE_GFXACTIVITY:
		*value = metrics->Current.GfxActivity;
		अवरोध;
	हाल METRICS_AVERAGE_VCNACTIVITY:
		*value = metrics->Current.UvdActivity;
		अवरोध;
	हाल METRICS_AVERAGE_SOCKETPOWER:
		*value = (metrics->Current.CurrentSocketPower << 8) /
		1000;
		अवरोध;
	हाल METRICS_TEMPERATURE_EDGE:
		*value = metrics->Current.GfxTemperature / 100 *
		SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
		अवरोध;
	हाल METRICS_TEMPERATURE_HOTSPOT:
		*value = metrics->Current.SocTemperature / 100 *
		SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;
		अवरोध;
	हाल METRICS_THROTTLER_STATUS:
		*value = metrics->Current.ThrottlerStatus;
		अवरोध;
	हाल METRICS_VOLTAGE_VDDGFX:
		*value = metrics->Current.Voltage[2];
		अवरोध;
	हाल METRICS_VOLTAGE_VDDSOC:
		*value = metrics->Current.Voltage[1];
		अवरोध;
	हाल METRICS_AVERAGE_CPUCLK:
		स_नकल(value, &metrics->Current.CoreFrequency[0],
		       smu->cpu_core_num * माप(uपूर्णांक16_t));
		अवरोध;
	शेष:
		*value = अच_पूर्णांक_उच्च;
		अवरोध;
	पूर्ण

	mutex_unlock(&smu->metrics_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक vangogh_common_get_smu_metrics_data(काष्ठा smu_context *smu,
				       MetricsMember_t member,
				       uपूर्णांक32_t *value)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t अगर_version;
	पूर्णांक ret = 0;

	ret = smu_cmn_get_smc_version(smu, &अगर_version, शून्य);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to get smu if version!\n");
		वापस ret;
	पूर्ण

	अगर (अगर_version < 0x3)
		ret = vangogh_get_legacy_smu_metrics_data(smu, member, value);
	अन्यथा
		ret = vangogh_get_smu_metrics_data(smu, member, value);

	वापस ret;
पूर्ण

अटल पूर्णांक vangogh_allocate_dpm_context(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_dpm_context *smu_dpm = &smu->smu_dpm;

	smu_dpm->dpm_context = kzalloc(माप(काष्ठा smu_11_0_dpm_context),
				       GFP_KERNEL);
	अगर (!smu_dpm->dpm_context)
		वापस -ENOMEM;

	smu_dpm->dpm_context_size = माप(काष्ठा smu_11_0_dpm_context);

	वापस 0;
पूर्ण

अटल पूर्णांक vangogh_init_smc_tables(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	ret = vangogh_tables_init(smu);
	अगर (ret)
		वापस ret;

	ret = vangogh_allocate_dpm_context(smu);
	अगर (ret)
		वापस ret;

#अगर_घोषित CONFIG_X86
	/* AMD x86 APU only */
	smu->cpu_core_num = boot_cpu_data.x86_max_cores;
#अन्यथा
	smu->cpu_core_num = 4;
#पूर्ण_अगर

	वापस smu_v11_0_init_smc_tables(smu);
पूर्ण

अटल पूर्णांक vangogh_dpm_set_vcn_enable(काष्ठा smu_context *smu, bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (enable) अणु
		/* vcn dpm on is a prerequisite क्रम vcn घातer gate messages */
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_PowerUpVcn, 0, शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_PowerDownVcn, 0, शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vangogh_dpm_set_jpeg_enable(काष्ठा smu_context *smu, bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (enable) अणु
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_PowerUpJpeg, 0, शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_PowerDownJpeg, 0, शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool vangogh_is_dpm_running(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक ret = 0;
	uपूर्णांक32_t feature_mask[2];
	uपूर्णांक64_t feature_enabled;

	/* we need to re-init after suspend so वापस false */
	अगर (adev->in_suspend)
		वापस false;

	ret = smu_cmn_get_enabled_32_bits_mask(smu, feature_mask, 2);

	अगर (ret)
		वापस false;

	feature_enabled = (अचिन्हित दीर्घ)((uपूर्णांक64_t)feature_mask[0] |
				((uपूर्णांक64_t)feature_mask[1] << 32));

	वापस !!(feature_enabled & SMC_DPM_FEATURE);
पूर्ण

अटल पूर्णांक vangogh_get_dpm_clk_limited(काष्ठा smu_context *smu, क्रमागत smu_clk_type clk_type,
						uपूर्णांक32_t dpm_level, uपूर्णांक32_t *freq)
अणु
	DpmClocks_t *clk_table = smu->smu_table.घड़ीs_table;

	अगर (!clk_table || clk_type >= SMU_CLK_COUNT)
		वापस -EINVAL;

	चयन (clk_type) अणु
	हाल SMU_SOCCLK:
		अगर (dpm_level >= clk_table->NumSocClkLevelsEnabled)
			वापस -EINVAL;
		*freq = clk_table->SocClocks[dpm_level];
		अवरोध;
	हाल SMU_VCLK:
		अगर (dpm_level >= clk_table->VcnClkLevelsEnabled)
			वापस -EINVAL;
		*freq = clk_table->VcnClocks[dpm_level].vclk;
		अवरोध;
	हाल SMU_DCLK:
		अगर (dpm_level >= clk_table->VcnClkLevelsEnabled)
			वापस -EINVAL;
		*freq = clk_table->VcnClocks[dpm_level].dclk;
		अवरोध;
	हाल SMU_UCLK:
	हाल SMU_MCLK:
		अगर (dpm_level >= clk_table->NumDfPstatesEnabled)
			वापस -EINVAL;
		*freq = clk_table->DfPstateTable[dpm_level].memclk;

		अवरोध;
	हाल SMU_FCLK:
		अगर (dpm_level >= clk_table->NumDfPstatesEnabled)
			वापस -EINVAL;
		*freq = clk_table->DfPstateTable[dpm_level].fclk;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vangogh_prपूर्णांक_legacy_clk_levels(काष्ठा smu_context *smu,
			क्रमागत smu_clk_type clk_type, अक्षर *buf)
अणु
	DpmClocks_t *clk_table = smu->smu_table.घड़ीs_table;
	SmuMetrics_legacy_t metrics;
	काष्ठा smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);
	पूर्णांक i, size = 0, ret = 0;
	uपूर्णांक32_t cur_value = 0, value = 0, count = 0;
	bool cur_value_match_level = false;

	स_रखो(&metrics, 0, माप(metrics));

	ret = smu_cmn_get_metrics_table(smu, &metrics, false);
	अगर (ret)
		वापस ret;

	चयन (clk_type) अणु
	हाल SMU_OD_SCLK:
		अगर (smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_MANUAL) अणु
			size = प्र_लिखो(buf, "%s:\n", "OD_SCLK");
			size += प्र_लिखो(buf + size, "0: %10uMhz\n",
			(smu->gfx_actual_hard_min_freq > 0) ? smu->gfx_actual_hard_min_freq : smu->gfx_शेष_hard_min_freq);
			size += प्र_लिखो(buf + size, "1: %10uMhz\n",
			(smu->gfx_actual_soft_max_freq > 0) ? smu->gfx_actual_soft_max_freq : smu->gfx_शेष_soft_max_freq);
		पूर्ण
		अवरोध;
	हाल SMU_OD_CCLK:
		अगर (smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_MANUAL) अणु
			size = प्र_लिखो(buf, "CCLK_RANGE in Core%d:\n",  smu->cpu_core_id_select);
			size += प्र_लिखो(buf + size, "0: %10uMhz\n",
			(smu->cpu_actual_soft_min_freq > 0) ? smu->cpu_actual_soft_min_freq : smu->cpu_शेष_soft_min_freq);
			size += प्र_लिखो(buf + size, "1: %10uMhz\n",
			(smu->cpu_actual_soft_max_freq > 0) ? smu->cpu_actual_soft_max_freq : smu->cpu_शेष_soft_max_freq);
		पूर्ण
		अवरोध;
	हाल SMU_OD_RANGE:
		अगर (smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_MANUAL) अणु
			size = प्र_लिखो(buf, "%s:\n", "OD_RANGE");
			size += प्र_लिखो(buf + size, "SCLK: %7uMhz %10uMhz\n",
				smu->gfx_शेष_hard_min_freq, smu->gfx_शेष_soft_max_freq);
			size += प्र_लिखो(buf + size, "CCLK: %7uMhz %10uMhz\n",
				smu->cpu_शेष_soft_min_freq, smu->cpu_शेष_soft_max_freq);
		पूर्ण
		अवरोध;
	हाल SMU_SOCCLK:
		/* the level 3 ~ 6 of socclk use the same frequency क्रम vangogh */
		count = clk_table->NumSocClkLevelsEnabled;
		cur_value = metrics.SocclkFrequency;
		अवरोध;
	हाल SMU_VCLK:
		count = clk_table->VcnClkLevelsEnabled;
		cur_value = metrics.VclkFrequency;
		अवरोध;
	हाल SMU_DCLK:
		count = clk_table->VcnClkLevelsEnabled;
		cur_value = metrics.DclkFrequency;
		अवरोध;
	हाल SMU_MCLK:
		count = clk_table->NumDfPstatesEnabled;
		cur_value = metrics.MemclkFrequency;
		अवरोध;
	हाल SMU_FCLK:
		count = clk_table->NumDfPstatesEnabled;
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_GetFclkFrequency, 0, &cur_value);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (clk_type) अणु
	हाल SMU_SOCCLK:
	हाल SMU_VCLK:
	हाल SMU_DCLK:
	हाल SMU_MCLK:
	हाल SMU_FCLK:
		क्रम (i = 0; i < count; i++) अणु
			ret = vangogh_get_dpm_clk_limited(smu, clk_type, i, &value);
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

अटल पूर्णांक vangogh_prपूर्णांक_clk_levels(काष्ठा smu_context *smu,
			क्रमागत smu_clk_type clk_type, अक्षर *buf)
अणु
	DpmClocks_t *clk_table = smu->smu_table.घड़ीs_table;
	SmuMetrics_t metrics;
	काष्ठा smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);
	पूर्णांक i, size = 0, ret = 0;
	uपूर्णांक32_t cur_value = 0, value = 0, count = 0;
	bool cur_value_match_level = false;

	स_रखो(&metrics, 0, माप(metrics));

	ret = smu_cmn_get_metrics_table(smu, &metrics, false);
	अगर (ret)
		वापस ret;

	चयन (clk_type) अणु
	हाल SMU_OD_SCLK:
		अगर (smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_MANUAL) अणु
			size = प्र_लिखो(buf, "%s:\n", "OD_SCLK");
			size += प्र_लिखो(buf + size, "0: %10uMhz\n",
			(smu->gfx_actual_hard_min_freq > 0) ? smu->gfx_actual_hard_min_freq : smu->gfx_शेष_hard_min_freq);
			size += प्र_लिखो(buf + size, "1: %10uMhz\n",
			(smu->gfx_actual_soft_max_freq > 0) ? smu->gfx_actual_soft_max_freq : smu->gfx_शेष_soft_max_freq);
		पूर्ण
		अवरोध;
	हाल SMU_OD_CCLK:
		अगर (smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_MANUAL) अणु
			size = प्र_लिखो(buf, "CCLK_RANGE in Core%d:\n",  smu->cpu_core_id_select);
			size += प्र_लिखो(buf + size, "0: %10uMhz\n",
			(smu->cpu_actual_soft_min_freq > 0) ? smu->cpu_actual_soft_min_freq : smu->cpu_शेष_soft_min_freq);
			size += प्र_लिखो(buf + size, "1: %10uMhz\n",
			(smu->cpu_actual_soft_max_freq > 0) ? smu->cpu_actual_soft_max_freq : smu->cpu_शेष_soft_max_freq);
		पूर्ण
		अवरोध;
	हाल SMU_OD_RANGE:
		अगर (smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_MANUAL) अणु
			size = प्र_लिखो(buf, "%s:\n", "OD_RANGE");
			size += प्र_लिखो(buf + size, "SCLK: %7uMhz %10uMhz\n",
				smu->gfx_शेष_hard_min_freq, smu->gfx_शेष_soft_max_freq);
			size += प्र_लिखो(buf + size, "CCLK: %7uMhz %10uMhz\n",
				smu->cpu_शेष_soft_min_freq, smu->cpu_शेष_soft_max_freq);
		पूर्ण
		अवरोध;
	हाल SMU_SOCCLK:
		/* the level 3 ~ 6 of socclk use the same frequency क्रम vangogh */
		count = clk_table->NumSocClkLevelsEnabled;
		cur_value = metrics.Current.SocclkFrequency;
		अवरोध;
	हाल SMU_VCLK:
		count = clk_table->VcnClkLevelsEnabled;
		cur_value = metrics.Current.VclkFrequency;
		अवरोध;
	हाल SMU_DCLK:
		count = clk_table->VcnClkLevelsEnabled;
		cur_value = metrics.Current.DclkFrequency;
		अवरोध;
	हाल SMU_MCLK:
		count = clk_table->NumDfPstatesEnabled;
		cur_value = metrics.Current.MemclkFrequency;
		अवरोध;
	हाल SMU_FCLK:
		count = clk_table->NumDfPstatesEnabled;
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_GetFclkFrequency, 0, &cur_value);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (clk_type) अणु
	हाल SMU_SOCCLK:
	हाल SMU_VCLK:
	हाल SMU_DCLK:
	हाल SMU_MCLK:
	हाल SMU_FCLK:
		क्रम (i = 0; i < count; i++) अणु
			ret = vangogh_get_dpm_clk_limited(smu, clk_type, i, &value);
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

अटल पूर्णांक vangogh_common_prपूर्णांक_clk_levels(काष्ठा smu_context *smu,
			क्रमागत smu_clk_type clk_type, अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t अगर_version;
	पूर्णांक ret = 0;

	ret = smu_cmn_get_smc_version(smu, &अगर_version, शून्य);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to get smu if version!\n");
		वापस ret;
	पूर्ण

	अगर (अगर_version < 0x3)
		ret = vangogh_prपूर्णांक_legacy_clk_levels(smu, clk_type, buf);
	अन्यथा
		ret = vangogh_prपूर्णांक_clk_levels(smu, clk_type, buf);

	वापस ret;
पूर्ण

अटल पूर्णांक vangogh_get_profiling_clk_mask(काष्ठा smu_context *smu,
					 क्रमागत amd_dpm_क्रमced_level level,
					 uपूर्णांक32_t *vclk_mask,
					 uपूर्णांक32_t *dclk_mask,
					 uपूर्णांक32_t *mclk_mask,
					 uपूर्णांक32_t *fclk_mask,
					 uपूर्णांक32_t *soc_mask)
अणु
	DpmClocks_t *clk_table = smu->smu_table.घड़ीs_table;

	अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK) अणु
		अगर (mclk_mask)
			*mclk_mask = clk_table->NumDfPstatesEnabled - 1;

		अगर (fclk_mask)
			*fclk_mask = clk_table->NumDfPstatesEnabled - 1;

		अगर (soc_mask)
			*soc_mask = 0;
	पूर्ण अन्यथा अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK) अणु
		अगर (mclk_mask)
			*mclk_mask = 0;

		अगर (fclk_mask)
			*fclk_mask = 0;

		अगर (soc_mask)
			*soc_mask = 1;

		अगर (vclk_mask)
			*vclk_mask = 1;

		अगर (dclk_mask)
			*dclk_mask = 1;
	पूर्ण अन्यथा अगर (level == AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD) अणु
		अगर (mclk_mask)
			*mclk_mask = 0;

		अगर (fclk_mask)
			*fclk_mask = 0;

		अगर (soc_mask)
			*soc_mask = 1;

		अगर (vclk_mask)
			*vclk_mask = 1;

		अगर (dclk_mask)
			*dclk_mask = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool vangogh_clk_dpm_is_enabled(काष्ठा smu_context *smu,
				क्रमागत smu_clk_type clk_type)
अणु
	क्रमागत smu_feature_mask feature_id = 0;

	चयन (clk_type) अणु
	हाल SMU_MCLK:
	हाल SMU_UCLK:
	हाल SMU_FCLK:
		feature_id = SMU_FEATURE_DPM_FCLK_BIT;
		अवरोध;
	हाल SMU_GFXCLK:
	हाल SMU_SCLK:
		feature_id = SMU_FEATURE_DPM_GFXCLK_BIT;
		अवरोध;
	हाल SMU_SOCCLK:
		feature_id = SMU_FEATURE_DPM_SOCCLK_BIT;
		अवरोध;
	हाल SMU_VCLK:
	हाल SMU_DCLK:
		feature_id = SMU_FEATURE_VCN_DPM_BIT;
		अवरोध;
	शेष:
		वापस true;
	पूर्ण

	अगर (!smu_cmn_feature_is_enabled(smu, feature_id))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक vangogh_get_dpm_ultimate_freq(काष्ठा smu_context *smu,
					क्रमागत smu_clk_type clk_type,
					uपूर्णांक32_t *min,
					uपूर्णांक32_t *max)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t soc_mask;
	uपूर्णांक32_t vclk_mask;
	uपूर्णांक32_t dclk_mask;
	uपूर्णांक32_t mclk_mask;
	uपूर्णांक32_t fclk_mask;
	uपूर्णांक32_t घड़ी_limit;

	अगर (!vangogh_clk_dpm_is_enabled(smu, clk_type)) अणु
		चयन (clk_type) अणु
		हाल SMU_MCLK:
		हाल SMU_UCLK:
			घड़ी_limit = smu->smu_table.boot_values.uclk;
			अवरोध;
		हाल SMU_FCLK:
			घड़ी_limit = smu->smu_table.boot_values.fclk;
			अवरोध;
		हाल SMU_GFXCLK:
		हाल SMU_SCLK:
			घड़ी_limit = smu->smu_table.boot_values.gfxclk;
			अवरोध;
		हाल SMU_SOCCLK:
			घड़ी_limit = smu->smu_table.boot_values.socclk;
			अवरोध;
		हाल SMU_VCLK:
			घड़ी_limit = smu->smu_table.boot_values.vclk;
			अवरोध;
		हाल SMU_DCLK:
			घड़ी_limit = smu->smu_table.boot_values.dclk;
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
		ret = vangogh_get_profiling_clk_mask(smu,
							AMD_DPM_FORCED_LEVEL_PROखाता_PEAK,
							&vclk_mask,
							&dclk_mask,
							&mclk_mask,
							&fclk_mask,
							&soc_mask);
		अगर (ret)
			जाओ failed;

		चयन (clk_type) अणु
		हाल SMU_UCLK:
		हाल SMU_MCLK:
			ret = vangogh_get_dpm_clk_limited(smu, clk_type, mclk_mask, max);
			अगर (ret)
				जाओ failed;
			अवरोध;
		हाल SMU_SOCCLK:
			ret = vangogh_get_dpm_clk_limited(smu, clk_type, soc_mask, max);
			अगर (ret)
				जाओ failed;
			अवरोध;
		हाल SMU_FCLK:
			ret = vangogh_get_dpm_clk_limited(smu, clk_type, fclk_mask, max);
			अगर (ret)
				जाओ failed;
			अवरोध;
		हाल SMU_VCLK:
			ret = vangogh_get_dpm_clk_limited(smu, clk_type, vclk_mask, max);
			अगर (ret)
				जाओ failed;
			अवरोध;
		हाल SMU_DCLK:
			ret = vangogh_get_dpm_clk_limited(smu, clk_type, dclk_mask, max);
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
		हाल SMU_UCLK:
		हाल SMU_MCLK:
			ret = vangogh_get_dpm_clk_limited(smu, clk_type, mclk_mask, min);
			अगर (ret)
				जाओ failed;
			अवरोध;
		हाल SMU_SOCCLK:
			ret = vangogh_get_dpm_clk_limited(smu, clk_type, soc_mask, min);
			अगर (ret)
				जाओ failed;
			अवरोध;
		हाल SMU_FCLK:
			ret = vangogh_get_dpm_clk_limited(smu, clk_type, fclk_mask, min);
			अगर (ret)
				जाओ failed;
			अवरोध;
		हाल SMU_VCLK:
			ret = vangogh_get_dpm_clk_limited(smu, clk_type, vclk_mask, min);
			अगर (ret)
				जाओ failed;
			अवरोध;
		हाल SMU_DCLK:
			ret = vangogh_get_dpm_clk_limited(smu, clk_type, dclk_mask, min);
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

अटल पूर्णांक vangogh_get_घातer_profile_mode(काष्ठा smu_context *smu,
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
		 * Not all profile modes are supported on vangogh.
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

अटल पूर्णांक vangogh_set_घातer_profile_mode(काष्ठा smu_context *smu, दीर्घ *input, uपूर्णांक32_t size)
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
		dev_dbg(smu->adev->dev, "Unsupported power profile mode %d on VANGOGH\n",
					profile_mode);
		वापस -EINVAL;
	पूर्ण

	ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_ActiveProcessNotअगरy,
				    1 << workload_type,
				    शून्य);
	अगर (ret) अणु
		dev_err_once(smu->adev->dev, "Fail to set workload type %d\n",
					workload_type);
		वापस ret;
	पूर्ण

	smu->घातer_profile_mode = profile_mode;

	वापस 0;
पूर्ण

अटल पूर्णांक vangogh_set_soft_freq_limited_range(काष्ठा smu_context *smu,
					  क्रमागत smu_clk_type clk_type,
					  uपूर्णांक32_t min,
					  uपूर्णांक32_t max)
अणु
	पूर्णांक ret = 0;

	अगर (!vangogh_clk_dpm_is_enabled(smu, clk_type))
		वापस 0;

	चयन (clk_type) अणु
	हाल SMU_GFXCLK:
	हाल SMU_SCLK:
		ret = smu_cmn_send_smc_msg_with_param(smu,
							SMU_MSG_SetHardMinGfxClk,
							min, शून्य);
		अगर (ret)
			वापस ret;

		ret = smu_cmn_send_smc_msg_with_param(smu,
							SMU_MSG_SetSoftMaxGfxClk,
							max, शून्य);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल SMU_FCLK:
		ret = smu_cmn_send_smc_msg_with_param(smu,
							SMU_MSG_SetHardMinFclkByFreq,
							min, शून्य);
		अगर (ret)
			वापस ret;

		ret = smu_cmn_send_smc_msg_with_param(smu,
							SMU_MSG_SetSoftMaxFclkByFreq,
							max, शून्य);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल SMU_SOCCLK:
		ret = smu_cmn_send_smc_msg_with_param(smu,
							SMU_MSG_SetHardMinSocclkByFreq,
							min, शून्य);
		अगर (ret)
			वापस ret;

		ret = smu_cmn_send_smc_msg_with_param(smu,
							SMU_MSG_SetSoftMaxSocclkByFreq,
							max, शून्य);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल SMU_VCLK:
		ret = smu_cmn_send_smc_msg_with_param(smu,
							SMU_MSG_SetHardMinVcn,
							min << 16, शून्य);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu,
							SMU_MSG_SetSoftMaxVcn,
							max << 16, शून्य);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल SMU_DCLK:
		ret = smu_cmn_send_smc_msg_with_param(smu,
							SMU_MSG_SetHardMinVcn,
							min, शून्य);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu,
							SMU_MSG_SetSoftMaxVcn,
							max, शून्य);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vangogh_क्रमce_clk_levels(काष्ठा smu_context *smu,
				   क्रमागत smu_clk_type clk_type, uपूर्णांक32_t mask)
अणु
	uपूर्णांक32_t soft_min_level = 0, soft_max_level = 0;
	uपूर्णांक32_t min_freq = 0, max_freq = 0;
	पूर्णांक ret = 0 ;

	soft_min_level = mask ? (ffs(mask) - 1) : 0;
	soft_max_level = mask ? (fls(mask) - 1) : 0;

	चयन (clk_type) अणु
	हाल SMU_SOCCLK:
		ret = vangogh_get_dpm_clk_limited(smu, clk_type,
						soft_min_level, &min_freq);
		अगर (ret)
			वापस ret;
		ret = vangogh_get_dpm_clk_limited(smu, clk_type,
						soft_max_level, &max_freq);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu,
								SMU_MSG_SetSoftMaxSocclkByFreq,
								max_freq, शून्य);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu,
								SMU_MSG_SetHardMinSocclkByFreq,
								min_freq, शून्य);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल SMU_FCLK:
		ret = vangogh_get_dpm_clk_limited(smu,
							clk_type, soft_min_level, &min_freq);
		अगर (ret)
			वापस ret;
		ret = vangogh_get_dpm_clk_limited(smu,
							clk_type, soft_max_level, &max_freq);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu,
								SMU_MSG_SetSoftMaxFclkByFreq,
								max_freq, शून्य);
		अगर (ret)
			वापस ret;
		ret = smu_cmn_send_smc_msg_with_param(smu,
								SMU_MSG_SetHardMinFclkByFreq,
								min_freq, शून्य);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल SMU_VCLK:
		ret = vangogh_get_dpm_clk_limited(smu,
							clk_type, soft_min_level, &min_freq);
		अगर (ret)
			वापस ret;

		ret = vangogh_get_dpm_clk_limited(smu,
							clk_type, soft_max_level, &max_freq);
		अगर (ret)
			वापस ret;


		ret = smu_cmn_send_smc_msg_with_param(smu,
								SMU_MSG_SetHardMinVcn,
								min_freq << 16, शून्य);
		अगर (ret)
			वापस ret;

		ret = smu_cmn_send_smc_msg_with_param(smu,
								SMU_MSG_SetSoftMaxVcn,
								max_freq << 16, शून्य);
		अगर (ret)
			वापस ret;

		अवरोध;
	हाल SMU_DCLK:
		ret = vangogh_get_dpm_clk_limited(smu,
							clk_type, soft_min_level, &min_freq);
		अगर (ret)
			वापस ret;

		ret = vangogh_get_dpm_clk_limited(smu,
							clk_type, soft_max_level, &max_freq);
		अगर (ret)
			वापस ret;

		ret = smu_cmn_send_smc_msg_with_param(smu,
							SMU_MSG_SetHardMinVcn,
							min_freq, शून्य);
		अगर (ret)
			वापस ret;

		ret = smu_cmn_send_smc_msg_with_param(smu,
							SMU_MSG_SetSoftMaxVcn,
							max_freq, शून्य);
		अगर (ret)
			वापस ret;

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vangogh_क्रमce_dpm_limit_value(काष्ठा smu_context *smu, bool highest)
अणु
	पूर्णांक ret = 0, i = 0;
	uपूर्णांक32_t min_freq, max_freq, क्रमce_freq;
	क्रमागत smu_clk_type clk_type;

	क्रमागत smu_clk_type clks[] = अणु
		SMU_SOCCLK,
		SMU_VCLK,
		SMU_DCLK,
		SMU_FCLK,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(clks); i++) अणु
		clk_type = clks[i];
		ret = vangogh_get_dpm_ultimate_freq(smu, clk_type, &min_freq, &max_freq);
		अगर (ret)
			वापस ret;

		क्रमce_freq = highest ? max_freq : min_freq;
		ret = vangogh_set_soft_freq_limited_range(smu, clk_type, क्रमce_freq, क्रमce_freq);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vangogh_unक्रमce_dpm_levels(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0, i = 0;
	uपूर्णांक32_t min_freq, max_freq;
	क्रमागत smu_clk_type clk_type;

	काष्ठा clk_feature_map अणु
		क्रमागत smu_clk_type clk_type;
		uपूर्णांक32_t	feature;
	पूर्ण clk_feature_map[] = अणु
		अणुSMU_FCLK, SMU_FEATURE_DPM_FCLK_BITपूर्ण,
		अणुSMU_SOCCLK, SMU_FEATURE_DPM_SOCCLK_BITपूर्ण,
		अणुSMU_VCLK, SMU_FEATURE_VCN_DPM_BITपूर्ण,
		अणुSMU_DCLK, SMU_FEATURE_VCN_DPM_BITपूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(clk_feature_map); i++) अणु

		अगर (!smu_cmn_feature_is_enabled(smu, clk_feature_map[i].feature))
		    जारी;

		clk_type = clk_feature_map[i].clk_type;

		ret = vangogh_get_dpm_ultimate_freq(smu, clk_type, &min_freq, &max_freq);

		अगर (ret)
			वापस ret;

		ret = vangogh_set_soft_freq_limited_range(smu, clk_type, min_freq, max_freq);

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vangogh_set_peak_घड़ी_by_device(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t socclk_freq = 0, fclk_freq = 0;
	uपूर्णांक32_t vclk_freq = 0, dclk_freq = 0;

	ret = vangogh_get_dpm_ultimate_freq(smu, SMU_FCLK, शून्य, &fclk_freq);
	अगर (ret)
		वापस ret;

	ret = vangogh_set_soft_freq_limited_range(smu, SMU_FCLK, fclk_freq, fclk_freq);
	अगर (ret)
		वापस ret;

	ret = vangogh_get_dpm_ultimate_freq(smu, SMU_SOCCLK, शून्य, &socclk_freq);
	अगर (ret)
		वापस ret;

	ret = vangogh_set_soft_freq_limited_range(smu, SMU_SOCCLK, socclk_freq, socclk_freq);
	अगर (ret)
		वापस ret;

	ret = vangogh_get_dpm_ultimate_freq(smu, SMU_VCLK, शून्य, &vclk_freq);
	अगर (ret)
		वापस ret;

	ret = vangogh_set_soft_freq_limited_range(smu, SMU_VCLK, vclk_freq, vclk_freq);
	अगर (ret)
		वापस ret;

	ret = vangogh_get_dpm_ultimate_freq(smu, SMU_DCLK, शून्य, &dclk_freq);
	अगर (ret)
		वापस ret;

	ret = vangogh_set_soft_freq_limited_range(smu, SMU_DCLK, dclk_freq, dclk_freq);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक vangogh_set_perक्रमmance_level(काष्ठा smu_context *smu,
					क्रमागत amd_dpm_क्रमced_level level)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t soc_mask, mclk_mask, fclk_mask;
	uपूर्णांक32_t vclk_mask = 0, dclk_mask = 0;

	चयन (level) अणु
	हाल AMD_DPM_FORCED_LEVEL_HIGH:
		smu->gfx_actual_hard_min_freq = smu->gfx_शेष_hard_min_freq;
		smu->gfx_actual_soft_max_freq = smu->gfx_शेष_soft_max_freq;

		smu->cpu_actual_soft_min_freq = smu->cpu_शेष_soft_min_freq;
		smu->cpu_actual_soft_max_freq = smu->cpu_शेष_soft_max_freq;

		ret = vangogh_क्रमce_dpm_limit_value(smu, true);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_LOW:
		smu->gfx_actual_hard_min_freq = smu->gfx_शेष_hard_min_freq;
		smu->gfx_actual_soft_max_freq = smu->gfx_शेष_soft_max_freq;

		smu->cpu_actual_soft_min_freq = smu->cpu_शेष_soft_min_freq;
		smu->cpu_actual_soft_max_freq = smu->cpu_शेष_soft_max_freq;

		ret = vangogh_क्रमce_dpm_limit_value(smu, false);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_AUTO:
		smu->gfx_actual_hard_min_freq = smu->gfx_शेष_hard_min_freq;
		smu->gfx_actual_soft_max_freq = smu->gfx_शेष_soft_max_freq;

		smu->cpu_actual_soft_min_freq = smu->cpu_शेष_soft_min_freq;
		smu->cpu_actual_soft_max_freq = smu->cpu_शेष_soft_max_freq;

		ret = vangogh_unक्रमce_dpm_levels(smu);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD:
		smu->gfx_actual_hard_min_freq = smu->gfx_शेष_hard_min_freq;
		smu->gfx_actual_soft_max_freq = smu->gfx_शेष_soft_max_freq;

		smu->cpu_actual_soft_min_freq = smu->cpu_शेष_soft_min_freq;
		smu->cpu_actual_soft_max_freq = smu->cpu_शेष_soft_max_freq;

		ret = smu_cmn_send_smc_msg_with_param(smu,
					SMU_MSG_SetHardMinGfxClk,
					VANGOGH_UMD_PSTATE_STANDARD_GFXCLK, शून्य);
		अगर (ret)
			वापस ret;

		ret = smu_cmn_send_smc_msg_with_param(smu,
					SMU_MSG_SetSoftMaxGfxClk,
					VANGOGH_UMD_PSTATE_STANDARD_GFXCLK, शून्य);
		अगर (ret)
			वापस ret;

		ret = vangogh_get_profiling_clk_mask(smu, level,
							&vclk_mask,
							&dclk_mask,
							&mclk_mask,
							&fclk_mask,
							&soc_mask);
		अगर (ret)
			वापस ret;

		vangogh_क्रमce_clk_levels(smu, SMU_FCLK, 1 << fclk_mask);
		vangogh_क्रमce_clk_levels(smu, SMU_SOCCLK, 1 << soc_mask);
		vangogh_क्रमce_clk_levels(smu, SMU_VCLK, 1 << vclk_mask);
		vangogh_क्रमce_clk_levels(smu, SMU_DCLK, 1 << dclk_mask);

		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK:
		smu->gfx_actual_hard_min_freq = smu->gfx_शेष_hard_min_freq;
		smu->gfx_actual_soft_max_freq = smu->gfx_शेष_soft_max_freq;

		smu->cpu_actual_soft_min_freq = smu->cpu_शेष_soft_min_freq;
		smu->cpu_actual_soft_max_freq = smu->cpu_शेष_soft_max_freq;

		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetHardMinVcn,
								VANGOGH_UMD_PSTATE_PEAK_DCLK, शून्य);
		अगर (ret)
			वापस ret;

		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetSoftMaxVcn,
								VANGOGH_UMD_PSTATE_PEAK_DCLK, शून्य);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK:
		smu->gfx_actual_hard_min_freq = smu->gfx_शेष_hard_min_freq;
		smu->gfx_actual_soft_max_freq = smu->gfx_शेष_soft_max_freq;

		smu->cpu_actual_soft_min_freq = smu->cpu_शेष_soft_min_freq;
		smu->cpu_actual_soft_max_freq = smu->cpu_शेष_soft_max_freq;

		ret = vangogh_get_profiling_clk_mask(smu, level,
							शून्य,
							शून्य,
							&mclk_mask,
							&fclk_mask,
							शून्य);
		अगर (ret)
			वापस ret;

		vangogh_क्रमce_clk_levels(smu, SMU_FCLK, 1 << fclk_mask);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_PEAK:
		smu->gfx_actual_hard_min_freq = smu->gfx_शेष_hard_min_freq;
		smu->gfx_actual_soft_max_freq = smu->gfx_शेष_soft_max_freq;

		smu->cpu_actual_soft_min_freq = smu->cpu_शेष_soft_min_freq;
		smu->cpu_actual_soft_max_freq = smu->cpu_शेष_soft_max_freq;

		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetHardMinGfxClk,
				VANGOGH_UMD_PSTATE_PEAK_GFXCLK, शून्य);
		अगर (ret)
			वापस ret;

		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetSoftMaxGfxClk,
				VANGOGH_UMD_PSTATE_PEAK_GFXCLK, शून्य);
		अगर (ret)
			वापस ret;

		ret = vangogh_set_peak_घड़ी_by_device(smu);
		अवरोध;
	हाल AMD_DPM_FORCED_LEVEL_MANUAL:
	हाल AMD_DPM_FORCED_LEVEL_PROखाता_EXIT:
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक vangogh_पढ़ो_sensor(काष्ठा smu_context *smu,
				 क्रमागत amd_pp_sensors sensor,
				 व्योम *data, uपूर्णांक32_t *size)
अणु
	पूर्णांक ret = 0;

	अगर (!data || !size)
		वापस -EINVAL;

	mutex_lock(&smu->sensor_lock);
	चयन (sensor) अणु
	हाल AMDGPU_PP_SENSOR_GPU_LOAD:
		ret = vangogh_common_get_smu_metrics_data(smu,
						   METRICS_AVERAGE_GFXACTIVITY,
						   (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GPU_POWER:
		ret = vangogh_common_get_smu_metrics_data(smu,
						   METRICS_AVERAGE_SOCKETPOWER,
						   (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_EDGE_TEMP:
		ret = vangogh_common_get_smu_metrics_data(smu,
						   METRICS_TEMPERATURE_EDGE,
						   (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_HOTSPOT_TEMP:
		ret = vangogh_common_get_smu_metrics_data(smu,
						   METRICS_TEMPERATURE_HOTSPOT,
						   (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GFX_MCLK:
		ret = vangogh_common_get_smu_metrics_data(smu,
						   METRICS_CURR_UCLK,
						   (uपूर्णांक32_t *)data);
		*(uपूर्णांक32_t *)data *= 100;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_GFX_SCLK:
		ret = vangogh_common_get_smu_metrics_data(smu,
						   METRICS_CURR_GFXCLK,
						   (uपूर्णांक32_t *)data);
		*(uपूर्णांक32_t *)data *= 100;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_VDDGFX:
		ret = vangogh_common_get_smu_metrics_data(smu,
						   METRICS_VOLTAGE_VDDGFX,
						   (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_VDDNB:
		ret = vangogh_common_get_smu_metrics_data(smu,
						   METRICS_VOLTAGE_VDDSOC,
						   (uपूर्णांक32_t *)data);
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_CPU_CLK:
		ret = vangogh_common_get_smu_metrics_data(smu,
						   METRICS_AVERAGE_CPUCLK,
						   (uपूर्णांक32_t *)data);
		*size = smu->cpu_core_num * माप(uपूर्णांक16_t);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	mutex_unlock(&smu->sensor_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक vangogh_set_watermarks_table(काष्ठा smu_context *smu,
				       काष्ठा pp_smu_wm_range_sets *घड़ी_ranges)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	Watermarks_t *table = smu->smu_table.watermarks_table;

	अगर (!table || !घड़ी_ranges)
		वापस -EINVAL;

	अगर (घड़ी_ranges) अणु
		अगर (घड़ी_ranges->num_पढ़ोer_wm_sets > NUM_WM_RANGES ||
			घड़ी_ranges->num_ग_लिखोr_wm_sets > NUM_WM_RANGES)
			वापस -EINVAL;

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

अटल sमाप_प्रकार vangogh_get_legacy_gpu_metrics(काष्ठा smu_context *smu,
				      व्योम **table)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा gpu_metrics_v2_1 *gpu_metrics =
		(काष्ठा gpu_metrics_v2_1 *)smu_table->gpu_metrics_table;
	SmuMetrics_legacy_t metrics;
	पूर्णांक ret = 0;

	ret = smu_cmn_get_metrics_table(smu, &metrics, true);
	अगर (ret)
		वापस ret;

	smu_cmn_init_soft_gpu_metrics(gpu_metrics, 2, 1);

	gpu_metrics->temperature_gfx = metrics.GfxTemperature;
	gpu_metrics->temperature_soc = metrics.SocTemperature;
	स_नकल(&gpu_metrics->temperature_core[0],
		&metrics.CoreTemperature[0],
		माप(uपूर्णांक16_t) * 4);
	gpu_metrics->temperature_l3[0] = metrics.L3Temperature[0];

	gpu_metrics->average_gfx_activity = metrics.GfxActivity;
	gpu_metrics->average_mm_activity = metrics.UvdActivity;

	gpu_metrics->average_socket_घातer = metrics.CurrentSocketPower;
	gpu_metrics->average_cpu_घातer = metrics.Power[0];
	gpu_metrics->average_soc_घातer = metrics.Power[1];
	gpu_metrics->average_gfx_घातer = metrics.Power[2];
	स_नकल(&gpu_metrics->average_core_घातer[0],
		&metrics.CorePower[0],
		माप(uपूर्णांक16_t) * 4);

	gpu_metrics->average_gfxclk_frequency = metrics.GfxclkFrequency;
	gpu_metrics->average_socclk_frequency = metrics.SocclkFrequency;
	gpu_metrics->average_uclk_frequency = metrics.MemclkFrequency;
	gpu_metrics->average_fclk_frequency = metrics.MemclkFrequency;
	gpu_metrics->average_vclk_frequency = metrics.VclkFrequency;
	gpu_metrics->average_dclk_frequency = metrics.DclkFrequency;

	स_नकल(&gpu_metrics->current_coreclk[0],
		&metrics.CoreFrequency[0],
		माप(uपूर्णांक16_t) * 4);
	gpu_metrics->current_l3clk[0] = metrics.L3Frequency[0];

	gpu_metrics->throttle_status = metrics.ThrottlerStatus;

	gpu_metrics->प्रणाली_घड़ी_counter = kसमय_get_bootसमय_ns();

	*table = (व्योम *)gpu_metrics;

	वापस माप(काष्ठा gpu_metrics_v2_1);
पूर्ण

अटल sमाप_प्रकार vangogh_get_gpu_metrics(काष्ठा smu_context *smu,
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

	gpu_metrics->temperature_gfx = metrics.Current.GfxTemperature;
	gpu_metrics->temperature_soc = metrics.Current.SocTemperature;
	स_नकल(&gpu_metrics->temperature_core[0],
		&metrics.Current.CoreTemperature[0],
		माप(uपूर्णांक16_t) * 4);
	gpu_metrics->temperature_l3[0] = metrics.Current.L3Temperature[0];

	gpu_metrics->average_gfx_activity = metrics.Current.GfxActivity;
	gpu_metrics->average_mm_activity = metrics.Current.UvdActivity;

	gpu_metrics->average_socket_घातer = metrics.Current.CurrentSocketPower;
	gpu_metrics->average_cpu_घातer = metrics.Current.Power[0];
	gpu_metrics->average_soc_घातer = metrics.Current.Power[1];
	gpu_metrics->average_gfx_घातer = metrics.Current.Power[2];
	स_नकल(&gpu_metrics->average_core_घातer[0],
		&metrics.Average.CorePower[0],
		माप(uपूर्णांक16_t) * 4);

	gpu_metrics->average_gfxclk_frequency = metrics.Average.GfxclkFrequency;
	gpu_metrics->average_socclk_frequency = metrics.Average.SocclkFrequency;
	gpu_metrics->average_uclk_frequency = metrics.Average.MemclkFrequency;
	gpu_metrics->average_fclk_frequency = metrics.Average.MemclkFrequency;
	gpu_metrics->average_vclk_frequency = metrics.Average.VclkFrequency;
	gpu_metrics->average_dclk_frequency = metrics.Average.DclkFrequency;

	gpu_metrics->current_gfxclk = metrics.Current.GfxclkFrequency;
	gpu_metrics->current_socclk = metrics.Current.SocclkFrequency;
	gpu_metrics->current_uclk = metrics.Current.MemclkFrequency;
	gpu_metrics->current_fclk = metrics.Current.MemclkFrequency;
	gpu_metrics->current_vclk = metrics.Current.VclkFrequency;
	gpu_metrics->current_dclk = metrics.Current.DclkFrequency;

	स_नकल(&gpu_metrics->current_coreclk[0],
		&metrics.Current.CoreFrequency[0],
		माप(uपूर्णांक16_t) * 4);
	gpu_metrics->current_l3clk[0] = metrics.Current.L3Frequency[0];

	gpu_metrics->throttle_status = metrics.Current.ThrottlerStatus;

	gpu_metrics->प्रणाली_घड़ी_counter = kसमय_get_bootसमय_ns();

	*table = (व्योम *)gpu_metrics;

	वापस माप(काष्ठा gpu_metrics_v2_1);
पूर्ण

अटल sमाप_प्रकार vangogh_common_get_gpu_metrics(काष्ठा smu_context *smu,
				      व्योम **table)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t अगर_version;
	पूर्णांक ret = 0;

	ret = smu_cmn_get_smc_version(smu, &अगर_version, शून्य);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to get smu if version!\n");
		वापस ret;
	पूर्ण

	अगर (अगर_version < 0x3)
		ret = vangogh_get_legacy_gpu_metrics(smu, table);
	अन्यथा
		ret = vangogh_get_gpu_metrics(smu, table);

	वापस ret;
पूर्ण

अटल पूर्णांक vangogh_od_edit_dpm_table(काष्ठा smu_context *smu, क्रमागत PP_OD_DPM_TABLE_COMMAND type,
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
	हाल PP_OD_EDIT_CCLK_VDDC_TABLE:
		अगर (size != 3) अणु
			dev_err(smu->adev->dev, "Input parameter number not correct (should be 4 for processor)\n");
			वापस -EINVAL;
		पूर्ण
		अगर (input[0] >= smu->cpu_core_num) अणु
			dev_err(smu->adev->dev, "core index is overflow, should be less than %d\n",
				smu->cpu_core_num);
		पूर्ण
		smu->cpu_core_id_select = input[0];
		अगर (input[1] == 0) अणु
			अगर (input[2] < smu->cpu_शेष_soft_min_freq) अणु
				dev_warn(smu->adev->dev, "Fine grain setting minimum cclk (%ld) MHz is less than the minimum allowed (%d) MHz\n",
					input[2], smu->cpu_शेष_soft_min_freq);
				वापस -EINVAL;
			पूर्ण
			smu->cpu_actual_soft_min_freq = input[2];
		पूर्ण अन्यथा अगर (input[1] == 1) अणु
			अगर (input[2] > smu->cpu_शेष_soft_max_freq) अणु
				dev_warn(smu->adev->dev, "Fine grain setting maximum cclk (%ld) MHz is greater than the maximum allowed (%d) MHz\n",
					input[2], smu->cpu_शेष_soft_max_freq);
				वापस -EINVAL;
			पूर्ण
			smu->cpu_actual_soft_max_freq = input[2];
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;
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
		पूर्ण अन्यथा अणु
			smu->gfx_actual_hard_min_freq = smu->gfx_शेष_hard_min_freq;
			smu->gfx_actual_soft_max_freq = smu->gfx_शेष_soft_max_freq;
			smu->cpu_actual_soft_min_freq = smu->cpu_शेष_soft_min_freq;
			smu->cpu_actual_soft_max_freq = smu->cpu_शेष_soft_max_freq;
		पूर्ण
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

			ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetHardMinGfxClk,
									smu->gfx_actual_hard_min_freq, शून्य);
			अगर (ret) अणु
				dev_err(smu->adev->dev, "Set hard min sclk failed!");
				वापस ret;
			पूर्ण

			ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetSoftMaxGfxClk,
									smu->gfx_actual_soft_max_freq, शून्य);
			अगर (ret) अणु
				dev_err(smu->adev->dev, "Set soft max sclk failed!");
				वापस ret;
			पूर्ण

			अगर (smu->adev->pm.fw_version < 0x43f1b00) अणु
				dev_warn(smu->adev->dev, "CPUSoftMax/CPUSoftMin are not supported, please update SBIOS!\n");
				अवरोध;
			पूर्ण

			ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetSoftMinCclk,
							      ((smu->cpu_core_id_select << 20)
							       | smu->cpu_actual_soft_min_freq),
							      शून्य);
			अगर (ret) अणु
				dev_err(smu->adev->dev, "Set hard min cclk failed!");
				वापस ret;
			पूर्ण

			ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_SetSoftMaxCclk,
							      ((smu->cpu_core_id_select << 20)
							       | smu->cpu_actual_soft_max_freq),
							      शून्य);
			अगर (ret) अणु
				dev_err(smu->adev->dev, "Set soft max cclk failed!");
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vangogh_set_शेष_dpm_tables(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;

	वापस smu_cmn_update_table(smu, SMU_TABLE_DPMCLOCKS, 0, smu_table->घड़ीs_table, false);
पूर्ण

अटल पूर्णांक vangogh_set_fine_grain_gfx_freq_parameters(काष्ठा smu_context *smu)
अणु
	DpmClocks_t *clk_table = smu->smu_table.घड़ीs_table;

	smu->gfx_शेष_hard_min_freq = clk_table->MinGfxClk;
	smu->gfx_शेष_soft_max_freq = clk_table->MaxGfxClk;
	smu->gfx_actual_hard_min_freq = 0;
	smu->gfx_actual_soft_max_freq = 0;

	smu->cpu_शेष_soft_min_freq = 1400;
	smu->cpu_शेष_soft_max_freq = 3500;
	smu->cpu_actual_soft_min_freq = 0;
	smu->cpu_actual_soft_max_freq = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक vangogh_get_dpm_घड़ी_प्रकारable(काष्ठा smu_context *smu, काष्ठा dpm_घड़ीs *घड़ी_प्रकारable)
अणु
	DpmClocks_t *table = smu->smu_table.घड़ीs_table;
	पूर्णांक i;

	अगर (!घड़ी_प्रकारable || !table)
		वापस -EINVAL;

	क्रम (i = 0; i < NUM_SOCCLK_DPM_LEVELS; i++) अणु
		घड़ी_प्रकारable->SocClocks[i].Freq = table->SocClocks[i];
		घड़ी_प्रकारable->SocClocks[i].Vol = table->SocVoltage[i];
	पूर्ण

	क्रम (i = 0; i < NUM_FCLK_DPM_LEVELS; i++) अणु
		घड़ी_प्रकारable->FClocks[i].Freq = table->DfPstateTable[i].fclk;
		घड़ी_प्रकारable->FClocks[i].Vol = table->DfPstateTable[i].voltage;
	पूर्ण

	क्रम (i = 0; i < NUM_FCLK_DPM_LEVELS; i++) अणु
		घड़ी_प्रकारable->MemClocks[i].Freq = table->DfPstateTable[i].memclk;
		घड़ी_प्रकारable->MemClocks[i].Vol = table->DfPstateTable[i].voltage;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक vangogh_प्रणाली_features_control(काष्ठा smu_context *smu, bool en)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	काष्ठा smu_feature *feature = &smu->smu_feature;
	uपूर्णांक32_t feature_mask[2];
	पूर्णांक ret = 0;

	अगर (adev->pm.fw_version >= 0x43f1700 && !en)
		ret = smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_RlcPowerNotअगरy,
						      RLC_STATUS_OFF, शून्य);

	biपंचांगap_zero(feature->enabled, feature->feature_num);
	biपंचांगap_zero(feature->supported, feature->feature_num);

	अगर (!en)
		वापस ret;

	ret = smu_cmn_get_enabled_32_bits_mask(smu, feature_mask, 2);
	अगर (ret)
		वापस ret;

	biपंचांगap_copy(feature->enabled, (अचिन्हित दीर्घ *)&feature_mask,
		    feature->feature_num);
	biपंचांगap_copy(feature->supported, (अचिन्हित दीर्घ *)&feature_mask,
		    feature->feature_num);

	वापस 0;
पूर्ण

अटल पूर्णांक vangogh_post_smu_init(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t पंचांगp;
	पूर्णांक ret = 0;
	uपूर्णांक8_t aon_bits = 0;
	/* Two CUs in one WGP */
	uपूर्णांक32_t req_active_wgps = adev->gfx.cu_info.number/2;
	uपूर्णांक32_t total_cu = adev->gfx.config.max_cu_per_sh *
		adev->gfx.config.max_sh_per_se * adev->gfx.config.max_shader_engines;

	/* allow message will be sent after enable message on Vangogh*/
	अगर (smu_cmn_feature_is_supported(smu, SMU_FEATURE_DPM_GFXCLK_BIT) &&
			(adev->pg_flags & AMD_PG_SUPPORT_GFX_PG)) अणु
		ret = smu_cmn_send_smc_msg(smu, SMU_MSG_EnableGfxOff, शून्य);
		अगर (ret) अणु
			dev_err(adev->dev, "Failed to Enable GfxOff!\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		adev->pm.pp_feature &= ~PP_GFXOFF_MASK;
		dev_info(adev->dev, "If GFX DPM or power gate disabled, disable GFXOFF\n");
	पूर्ण

	/* अगर all CUs are active, no need to घातer off any WGPs */
	अगर (total_cu == adev->gfx.cu_info.number)
		वापस 0;

	/*
	 * Calculate the total bits number of always on WGPs क्रम all SA/SEs in
	 * RLC_PG_ALWAYS_ON_WGP_MASK.
	 */
	पंचांगp = RREG32_KIQ(SOC15_REG_OFFSET(GC, 0, mmRLC_PG_ALWAYS_ON_WGP_MASK));
	पंचांगp &= RLC_PG_ALWAYS_ON_WGP_MASK__AON_WGP_MASK_MASK;

	aon_bits = hweight32(पंचांगp) * adev->gfx.config.max_sh_per_se * adev->gfx.config.max_shader_engines;

	/* Do not request any WGPs less than set in the AON_WGP_MASK */
	अगर (aon_bits > req_active_wgps) अणु
		dev_info(adev->dev, "Number of always on WGPs greater than active WGPs: WGP power save not requested.\n");
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस smu_cmn_send_smc_msg_with_param(smu, SMU_MSG_RequestActiveWgp, req_active_wgps, शून्य);
	पूर्ण
पूर्ण

अटल पूर्णांक vangogh_mode_reset(काष्ठा smu_context *smu, पूर्णांक type)
अणु
	पूर्णांक ret = 0, index = 0;

	index = smu_cmn_to_asic_specअगरic_index(smu, CMN2ASIC_MAPPING_MSG,
					       SMU_MSG_GfxDeviceDriverReset);
	अगर (index < 0)
		वापस index == -EACCES ? 0 : index;

	mutex_lock(&smu->message_lock);

	ret = smu_cmn_send_msg_without_रुकोing(smu, (uपूर्णांक16_t)index, type);

	mutex_unlock(&smu->message_lock);

	mdelay(10);

	वापस ret;
पूर्ण

अटल पूर्णांक vangogh_mode2_reset(काष्ठा smu_context *smu)
अणु
	वापस vangogh_mode_reset(smu, SMU_RESET_MODE_2);
पूर्ण

अटल पूर्णांक vangogh_get_घातer_limit(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_11_5_घातer_context *घातer_context =
								smu->smu_घातer.घातer_context;
	uपूर्णांक32_t ppt_limit;
	पूर्णांक ret = 0;

	अगर (smu->adev->pm.fw_version < 0x43f1e00)
		वापस ret;

	ret = smu_cmn_send_smc_msg(smu, SMU_MSG_GetSlowPPTLimit, &ppt_limit);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "Get slow PPT limit failed!\n");
		वापस ret;
	पूर्ण
	/* convert from milliwatt to watt */
	smu->current_घातer_limit = smu->शेष_घातer_limit = ppt_limit / 1000;
	smu->max_घातer_limit = 29;

	ret = smu_cmn_send_smc_msg(smu, SMU_MSG_GetFastPPTLimit, &ppt_limit);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "Get fast PPT limit failed!\n");
		वापस ret;
	पूर्ण
	/* convert from milliwatt to watt */
	घातer_context->current_fast_ppt_limit =
			घातer_context->शेष_fast_ppt_limit = ppt_limit / 1000;
	घातer_context->max_fast_ppt_limit = 30;

	वापस ret;
पूर्ण

अटल पूर्णांक vangogh_get_ppt_limit(काष्ठा smu_context *smu,
								uपूर्णांक32_t *ppt_limit,
								क्रमागत smu_ppt_limit_type type,
								क्रमागत smu_ppt_limit_level level)
अणु
	काष्ठा smu_11_5_घातer_context *घातer_context =
							smu->smu_घातer.घातer_context;

	अगर (!घातer_context)
		वापस -EOPNOTSUPP;

	अगर (type == SMU_FAST_PPT_LIMIT) अणु
		चयन (level) अणु
		हाल SMU_PPT_LIMIT_MAX:
			*ppt_limit = घातer_context->max_fast_ppt_limit;
			अवरोध;
		हाल SMU_PPT_LIMIT_CURRENT:
			*ppt_limit = घातer_context->current_fast_ppt_limit;
			अवरोध;
		हाल SMU_PPT_LIMIT_DEFAULT:
			*ppt_limit = घातer_context->शेष_fast_ppt_limit;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vangogh_set_घातer_limit(काष्ठा smu_context *smu, uपूर्णांक32_t ppt_limit)
अणु
	काष्ठा smu_11_5_घातer_context *घातer_context =
							smu->smu_घातer.घातer_context;
	uपूर्णांक32_t limit_type = ppt_limit >> 24;
	पूर्णांक ret = 0;

	अगर (!smu_cmn_feature_is_enabled(smu, SMU_FEATURE_PPT_BIT)) अणु
		dev_err(smu->adev->dev, "Setting new power limit is not supported!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (limit_type) अणु
	हाल SMU_DEFAULT_PPT_LIMIT:
		ret = smu_cmn_send_smc_msg_with_param(smu,
				SMU_MSG_SetSlowPPTLimit,
				ppt_limit * 1000, /* convert from watt to milliwatt */
				शून्य);
		अगर (ret)
			वापस ret;

		smu->current_घातer_limit = ppt_limit;
		अवरोध;
	हाल SMU_FAST_PPT_LIMIT:
		ppt_limit &= ~(SMU_FAST_PPT_LIMIT << 24);
		अगर (ppt_limit > घातer_context->max_fast_ppt_limit) अणु
			dev_err(smu->adev->dev,
				"New power limit (%d) is over the max allowed %d\n",
				ppt_limit, घातer_context->max_fast_ppt_limit);
			वापस ret;
		पूर्ण

		ret = smu_cmn_send_smc_msg_with_param(smu,
				SMU_MSG_SetFastPPTLimit,
				ppt_limit * 1000, /* convert from watt to milliwatt */
				शून्य);
		अगर (ret)
			वापस ret;

		घातer_context->current_fast_ppt_limit = ppt_limit;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pptable_funcs vangogh_ppt_funcs = अणु

	.check_fw_status = smu_v11_0_check_fw_status,
	.check_fw_version = smu_v11_0_check_fw_version,
	.init_smc_tables = vangogh_init_smc_tables,
	.fini_smc_tables = smu_v11_0_fini_smc_tables,
	.init_घातer = smu_v11_0_init_घातer,
	.fini_घातer = smu_v11_0_fini_घातer,
	.रेजिस्टर_irq_handler = smu_v11_0_रेजिस्टर_irq_handler,
	.notअगरy_memory_pool_location = smu_v11_0_notअगरy_memory_pool_location,
	.send_smc_msg_with_param = smu_cmn_send_smc_msg_with_param,
	.send_smc_msg = smu_cmn_send_smc_msg,
	.dpm_set_vcn_enable = vangogh_dpm_set_vcn_enable,
	.dpm_set_jpeg_enable = vangogh_dpm_set_jpeg_enable,
	.is_dpm_running = vangogh_is_dpm_running,
	.पढ़ो_sensor = vangogh_पढ़ो_sensor,
	.get_enabled_mask = smu_cmn_get_enabled_32_bits_mask,
	.get_pp_feature_mask = smu_cmn_get_pp_feature_mask,
	.set_watermarks_table = vangogh_set_watermarks_table,
	.set_driver_table_location = smu_v11_0_set_driver_table_location,
	.पूर्णांकerrupt_work = smu_v11_0_पूर्णांकerrupt_work,
	.get_gpu_metrics = vangogh_common_get_gpu_metrics,
	.od_edit_dpm_table = vangogh_od_edit_dpm_table,
	.prपूर्णांक_clk_levels = vangogh_common_prपूर्णांक_clk_levels,
	.set_शेष_dpm_table = vangogh_set_शेष_dpm_tables,
	.set_fine_grain_gfx_freq_parameters = vangogh_set_fine_grain_gfx_freq_parameters,
	.प्रणाली_features_control = vangogh_प्रणाली_features_control,
	.feature_is_enabled = smu_cmn_feature_is_enabled,
	.set_घातer_profile_mode = vangogh_set_घातer_profile_mode,
	.get_घातer_profile_mode = vangogh_get_घातer_profile_mode,
	.get_dpm_घड़ी_प्रकारable = vangogh_get_dpm_घड़ी_प्रकारable,
	.क्रमce_clk_levels = vangogh_क्रमce_clk_levels,
	.set_perक्रमmance_level = vangogh_set_perक्रमmance_level,
	.post_init = vangogh_post_smu_init,
	.mode2_reset = vangogh_mode2_reset,
	.gfx_off_control = smu_v11_0_gfx_off_control,
	.get_ppt_limit = vangogh_get_ppt_limit,
	.get_घातer_limit = vangogh_get_घातer_limit,
	.set_घातer_limit = vangogh_set_घातer_limit,
	.get_vbios_bootup_values = smu_v11_0_get_vbios_bootup_values,
पूर्ण;

व्योम vangogh_set_ppt_funcs(काष्ठा smu_context *smu)
अणु
	smu->ppt_funcs = &vangogh_ppt_funcs;
	smu->message_map = vangogh_message_map;
	smu->feature_map = vangogh_feature_mask_map;
	smu->table_map = vangogh_table_map;
	smu->workload_map = vangogh_workload_map;
	smu->is_apu = true;
पूर्ण
