<शैली गुरु>
/*
 * Copyright 2013 Advanced Micro Devices, Inc.
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
#अगर_अघोषित PP_SISLANDS_SMC_H
#घोषणा PP_SISLANDS_SMC_H

#समावेश "ppsmc.h"

#आशय pack(push, 1)

#घोषणा SISLANDS_MAX_SMC_PERFORMANCE_LEVELS_PER_SWSTATE 16

काष्ठा PP_SIslands_Dpm2PerfLevel
अणु
    uपूर्णांक8_t MaxPS;
    uपूर्णांक8_t TgtAct;
    uपूर्णांक8_t MaxPS_StepInc;
    uपूर्णांक8_t MaxPS_StepDec;
    uपूर्णांक8_t PSSamplingTime;
    uपूर्णांक8_t NearTDPDec;
    uपूर्णांक8_t AboveSafeInc;
    uपूर्णांक8_t BelowSafeInc;
    uपूर्णांक8_t PSDeltaLimit;
    uपूर्णांक8_t PSDeltaWin;
    uपूर्णांक16_t PwrEfficiencyRatio;
    uपूर्णांक8_t Reserved[4];
पूर्ण;

प्रकार काष्ठा PP_SIslands_Dpm2PerfLevel PP_SIslands_Dpm2PerfLevel;

काष्ठा PP_SIslands_DPM2Status
अणु
    uपूर्णांक32_t    dpm2Flags;
    uपूर्णांक8_t     CurrPSkip;
    uपूर्णांक8_t     CurrPSkipPowerShअगरt;
    uपूर्णांक8_t     CurrPSkipTDP;
    uपूर्णांक8_t     CurrPSkipOCP;
    uपूर्णांक8_t     MaxSPLLIndex;
    uपूर्णांक8_t     MinSPLLIndex;
    uपूर्णांक8_t     CurrSPLLIndex;
    uपूर्णांक8_t     InfSweepMode;
    uपूर्णांक8_t     InfSweepDir;
    uपूर्णांक8_t     TDPexceeded;
    uपूर्णांक8_t     reserved;
    uपूर्णांक8_t     SwitchDownThreshold;
    uपूर्णांक32_t    SwitchDownCounter;
    uपूर्णांक32_t    SysScalingFactor;
पूर्ण;

प्रकार काष्ठा PP_SIslands_DPM2Status PP_SIslands_DPM2Status;

काष्ठा PP_SIslands_DPM2Parameters
अणु
    uपूर्णांक32_t    TDPLimit;
    uपूर्णांक32_t    NearTDPLimit;
    uपूर्णांक32_t    SafePowerLimit;
    uपूर्णांक32_t    PowerBoostLimit;
    uपूर्णांक32_t    MinLimitDelta;
पूर्ण;
प्रकार काष्ठा PP_SIslands_DPM2Parameters PP_SIslands_DPM2Parameters;

काष्ठा PP_SIslands_PAPMStatus
अणु
    uपूर्णांक32_t    EstimatedDGPU_T;
    uपूर्णांक32_t    EstimatedDGPU_P;
    uपूर्णांक32_t    EstimatedAPU_T;
    uपूर्णांक32_t    EstimatedAPU_P;
    uपूर्णांक8_t     dGPU_T_Limit_Exceeded;
    uपूर्णांक8_t     reserved[3];
पूर्ण;
प्रकार काष्ठा PP_SIslands_PAPMStatus PP_SIslands_PAPMStatus;

काष्ठा PP_SIslands_PAPMParameters
अणु
    uपूर्णांक32_t    NearTDPLimitTherm;
    uपूर्णांक32_t    NearTDPLimitPAPM;
    uपूर्णांक32_t    Platक्रमmPowerLimit;
    uपूर्णांक32_t    dGPU_T_Limit;
    uपूर्णांक32_t    dGPU_T_Warning;
    uपूर्णांक32_t    dGPU_T_Hysteresis;
पूर्ण;
प्रकार काष्ठा PP_SIslands_PAPMParameters PP_SIslands_PAPMParameters;

काष्ठा SISLANDS_SMC_SCLK_VALUE
अणु
    uपूर्णांक32_t    vCG_SPLL_FUNC_CNTL;
    uपूर्णांक32_t    vCG_SPLL_FUNC_CNTL_2;
    uपूर्णांक32_t    vCG_SPLL_FUNC_CNTL_3;
    uपूर्णांक32_t    vCG_SPLL_FUNC_CNTL_4;
    uपूर्णांक32_t    vCG_SPLL_SPREAD_SPECTRUM;
    uपूर्णांक32_t    vCG_SPLL_SPREAD_SPECTRUM_2;
    uपूर्णांक32_t    sclk_value;
पूर्ण;

प्रकार काष्ठा SISLANDS_SMC_SCLK_VALUE SISLANDS_SMC_SCLK_VALUE;

काष्ठा SISLANDS_SMC_MCLK_VALUE
अणु
    uपूर्णांक32_t    vMPLL_FUNC_CNTL;
    uपूर्णांक32_t    vMPLL_FUNC_CNTL_1;
    uपूर्णांक32_t    vMPLL_FUNC_CNTL_2;
    uपूर्णांक32_t    vMPLL_AD_FUNC_CNTL;
    uपूर्णांक32_t    vMPLL_DQ_FUNC_CNTL;
    uपूर्णांक32_t    vMCLK_PWRMGT_CNTL;
    uपूर्णांक32_t    vDLL_CNTL;
    uपूर्णांक32_t    vMPLL_SS;
    uपूर्णांक32_t    vMPLL_SS2;
    uपूर्णांक32_t    mclk_value;
पूर्ण;

प्रकार काष्ठा SISLANDS_SMC_MCLK_VALUE SISLANDS_SMC_MCLK_VALUE;

काष्ठा SISLANDS_SMC_VOLTAGE_VALUE
अणु
    uपूर्णांक16_t    value;
    uपूर्णांक8_t     index;
    uपूर्णांक8_t     phase_settings;
पूर्ण;

प्रकार काष्ठा SISLANDS_SMC_VOLTAGE_VALUE SISLANDS_SMC_VOLTAGE_VALUE;

काष्ठा SISLANDS_SMC_HW_PERFORMANCE_LEVEL
अणु
    uपूर्णांक8_t                     ACIndex;
    uपूर्णांक8_t                     displayWatermark;
    uपूर्णांक8_t                     gen2PCIE;
    uपूर्णांक8_t                     UVDWatermark;
    uपूर्णांक8_t                     VCEWatermark;
    uपूर्णांक8_t                     strobeMode;
    uपूर्णांक8_t                     mcFlags;
    uपूर्णांक8_t                     padding;
    uपूर्णांक32_t                    aT;
    uपूर्णांक32_t                    bSP;
    SISLANDS_SMC_SCLK_VALUE     sclk;
    SISLANDS_SMC_MCLK_VALUE     mclk;
    SISLANDS_SMC_VOLTAGE_VALUE  vddc;
    SISLANDS_SMC_VOLTAGE_VALUE  mvdd;
    SISLANDS_SMC_VOLTAGE_VALUE  vddci;
    SISLANDS_SMC_VOLTAGE_VALUE  std_vddc;
    uपूर्णांक8_t                     hysteresisUp;
    uपूर्णांक8_t                     hysteresisDown;
    uपूर्णांक8_t                     stateFlags;
    uपूर्णांक8_t                     arbRefreshState;
    uपूर्णांक32_t                    SQPowerThrottle;
    uपूर्णांक32_t                    SQPowerThrottle_2;
    uपूर्णांक32_t                    MaxPoweredUpCU;
    SISLANDS_SMC_VOLTAGE_VALUE  high_temp_vddc;
    SISLANDS_SMC_VOLTAGE_VALUE  low_temp_vddc;
    uपूर्णांक32_t                    reserved[2];
    PP_SIslands_Dpm2PerfLevel   dpm2;
पूर्ण;

#घोषणा SISLANDS_SMC_STROBE_RATIO    0x0F
#घोषणा SISLANDS_SMC_STROBE_ENABLE   0x10

#घोषणा SISLANDS_SMC_MC_EDC_RD_FLAG  0x01
#घोषणा SISLANDS_SMC_MC_EDC_WR_FLAG  0x02
#घोषणा SISLANDS_SMC_MC_RTT_ENABLE   0x04
#घोषणा SISLANDS_SMC_MC_STUTTER_EN   0x08
#घोषणा SISLANDS_SMC_MC_PG_EN        0x10

प्रकार काष्ठा SISLANDS_SMC_HW_PERFORMANCE_LEVEL SISLANDS_SMC_HW_PERFORMANCE_LEVEL;

काष्ठा SISLANDS_SMC_SWSTATE
अणु
	uपूर्णांक8_t                             flags;
	uपूर्णांक8_t                             levelCount;
	uपूर्णांक8_t                             padding2;
	uपूर्णांक8_t                             padding3;
	SISLANDS_SMC_HW_PERFORMANCE_LEVEL   levels[];
पूर्ण;

प्रकार काष्ठा SISLANDS_SMC_SWSTATE SISLANDS_SMC_SWSTATE;

काष्ठा SISLANDS_SMC_SWSTATE_SINGLE अणु
	uपूर्णांक8_t                             flags;
	uपूर्णांक8_t                             levelCount;
	uपूर्णांक8_t                             padding2;
	uपूर्णांक8_t                             padding3;
	SISLANDS_SMC_HW_PERFORMANCE_LEVEL   level;
पूर्ण;

#घोषणा SISLANDS_SMC_VOLTAGEMASK_VDDC  0
#घोषणा SISLANDS_SMC_VOLTAGEMASK_MVDD  1
#घोषणा SISLANDS_SMC_VOLTAGEMASK_VDDCI 2
#घोषणा SISLANDS_SMC_VOLTAGEMASK_VDDC_PHASE_SHEDDING 3
#घोषणा SISLANDS_SMC_VOLTAGEMASK_MAX   4

काष्ठा SISLANDS_SMC_VOLTAGEMASKTABLE
अणु
    uपूर्णांक32_t lowMask[SISLANDS_SMC_VOLTAGEMASK_MAX];
पूर्ण;

प्रकार काष्ठा SISLANDS_SMC_VOLTAGEMASKTABLE SISLANDS_SMC_VOLTAGEMASKTABLE;

#घोषणा SISLANDS_MAX_NO_VREG_STEPS 32

काष्ठा SISLANDS_SMC_STATETABLE
अणु
	uपूर्णांक8_t					thermalProtectType;
	uपूर्णांक8_t					प्रणालीFlags;
	uपूर्णांक8_t					maxVDDCIndexInPPTable;
	uपूर्णांक8_t					extraFlags;
	uपूर्णांक32_t				lowSMIO[SISLANDS_MAX_NO_VREG_STEPS];
	SISLANDS_SMC_VOLTAGEMASKTABLE		voltageMaskTable;
	SISLANDS_SMC_VOLTAGEMASKTABLE		phaseMaskTable;
	PP_SIslands_DPM2Parameters		dpm2Params;
	काष्ठा SISLANDS_SMC_SWSTATE_SINGLE	initialState;
	काष्ठा SISLANDS_SMC_SWSTATE_SINGLE      ACPIState;
	काष्ठा SISLANDS_SMC_SWSTATE_SINGLE      ULVState;
	SISLANDS_SMC_SWSTATE			driverState;
	SISLANDS_SMC_HW_PERFORMANCE_LEVEL	dpmLevels[SISLANDS_MAX_SMC_PERFORMANCE_LEVELS_PER_SWSTATE];
पूर्ण;

प्रकार काष्ठा SISLANDS_SMC_STATETABLE SISLANDS_SMC_STATETABLE;

#घोषणा SI_SMC_SOFT_REGISTER_mclk_chg_समयout         0x0
#घोषणा SI_SMC_SOFT_REGISTER_delay_vreg               0xC
#घोषणा SI_SMC_SOFT_REGISTER_delay_acpi               0x28
#घोषणा SI_SMC_SOFT_REGISTER_seq_index                0x5C
#घोषणा SI_SMC_SOFT_REGISTER_mvdd_chg_समय            0x60
#घोषणा SI_SMC_SOFT_REGISTER_mclk_चयन_lim          0x70
#घोषणा SI_SMC_SOFT_REGISTER_watermark_threshold      0x78
#घोषणा SI_SMC_SOFT_REGISTER_phase_shedding_delay     0x88
#घोषणा SI_SMC_SOFT_REGISTER_ulv_volt_change_delay    0x8C
#घोषणा SI_SMC_SOFT_REGISTER_mc_block_delay           0x98
#घोषणा SI_SMC_SOFT_REGISTER_ticks_per_us             0xA8
#घोषणा SI_SMC_SOFT_REGISTER_crtc_index               0xC4
#घोषणा SI_SMC_SOFT_REGISTER_mclk_change_block_cp_min 0xC8
#घोषणा SI_SMC_SOFT_REGISTER_mclk_change_block_cp_max 0xCC
#घोषणा SI_SMC_SOFT_REGISTER_non_ulv_pcie_link_width  0xF4
#घोषणा SI_SMC_SOFT_REGISTER_tdr_is_about_to_happen   0xFC
#घोषणा SI_SMC_SOFT_REGISTER_vr_hot_gpio              0x100
#घोषणा SI_SMC_SOFT_REGISTER_svi_rework_plat_type     0x118
#घोषणा SI_SMC_SOFT_REGISTER_svi_rework_gpio_id_svd   0x11c
#घोषणा SI_SMC_SOFT_REGISTER_svi_rework_gpio_id_svc   0x120

काष्ठा PP_SIslands_FanTable
अणु
	uपूर्णांक8_t  fकरो_mode;
	uपूर्णांक8_t  padding;
	पूर्णांक16_t  temp_min;
	पूर्णांक16_t  temp_med;
	पूर्णांक16_t  temp_max;
	पूर्णांक16_t  slope1;
	पूर्णांक16_t  slope2;
	पूर्णांक16_t  fकरो_min;
	पूर्णांक16_t  hys_up;
	पूर्णांक16_t  hys_करोwn;
	पूर्णांक16_t  hys_slope;
	पूर्णांक16_t  temp_resp_lim;
	पूर्णांक16_t  temp_curr;
	पूर्णांक16_t  slope_curr;
	पूर्णांक16_t  pwm_curr;
	uपूर्णांक32_t refresh_period;
	पूर्णांक16_t  fकरो_max;
	uपूर्णांक8_t  temp_src;
	पूर्णांक8_t  padding2;
पूर्ण;

प्रकार काष्ठा PP_SIslands_FanTable PP_SIslands_FanTable;

#घोषणा SMC_SISLANDS_LKGE_LUT_NUM_OF_TEMP_ENTRIES 16
#घोषणा SMC_SISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES 32

#घोषणा SMC_SISLANDS_SCALE_I  7
#घोषणा SMC_SISLANDS_SCALE_R 12

काष्ठा PP_SIslands_CacConfig
अणु
    uपूर्णांक16_t   cac_lkge_lut[SMC_SISLANDS_LKGE_LUT_NUM_OF_TEMP_ENTRIES][SMC_SISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES];
    uपूर्णांक32_t   lkge_lut_V0;
    uपूर्णांक32_t   lkge_lut_Vstep;
    uपूर्णांक32_t   WinTime;
    uपूर्णांक32_t   R_LL;
    uपूर्णांक32_t   calculation_repeats;
    uपूर्णांक32_t   l2numWin_TDP;
    uपूर्णांक32_t   dc_cac;
    uपूर्णांक8_t    lts_truncate_n;
    uपूर्णांक8_t    SHIFT_N;
    uपूर्णांक8_t    log2_PG_LKG_SCALE;
    uपूर्णांक8_t    cac_temp;
    uपूर्णांक32_t   lkge_lut_T0;
    uपूर्णांक32_t   lkge_lut_Tstep;
पूर्ण;

प्रकार काष्ठा PP_SIslands_CacConfig PP_SIslands_CacConfig;

#घोषणा SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE 16
#घोषणा SMC_SISLANDS_MC_REGISTER_ARRAY_SET_COUNT 20

काष्ठा SMC_SIslands_MCRegisterAddress
अणु
    uपूर्णांक16_t s0;
    uपूर्णांक16_t s1;
पूर्ण;

प्रकार काष्ठा SMC_SIslands_MCRegisterAddress SMC_SIslands_MCRegisterAddress;

काष्ठा SMC_SIslands_MCRegisterSet
अणु
    uपूर्णांक32_t value[SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

प्रकार काष्ठा SMC_SIslands_MCRegisterSet SMC_SIslands_MCRegisterSet;

काष्ठा SMC_SIslands_MCRegisters
अणु
    uपूर्णांक8_t                             last;
    uपूर्णांक8_t                             reserved[3];
    SMC_SIslands_MCRegisterAddress      address[SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE];
    SMC_SIslands_MCRegisterSet          data[SMC_SISLANDS_MC_REGISTER_ARRAY_SET_COUNT];
पूर्ण;

प्रकार काष्ठा SMC_SIslands_MCRegisters SMC_SIslands_MCRegisters;

काष्ठा SMC_SIslands_MCArbDramTimingRegisterSet
अणु
    uपूर्णांक32_t mc_arb_dram_timing;
    uपूर्णांक32_t mc_arb_dram_timing2;
    uपूर्णांक8_t  mc_arb_rfsh_rate;
    uपूर्णांक8_t  mc_arb_burst_समय;
    uपूर्णांक8_t  padding[2];
पूर्ण;

प्रकार काष्ठा SMC_SIslands_MCArbDramTimingRegisterSet SMC_SIslands_MCArbDramTimingRegisterSet;

काष्ठा SMC_SIslands_MCArbDramTimingRegisters
अणु
    uपूर्णांक8_t                                     arb_current;
    uपूर्णांक8_t                                     reserved[3];
    SMC_SIslands_MCArbDramTimingRegisterSet     data[16];
पूर्ण;

प्रकार काष्ठा SMC_SIslands_MCArbDramTimingRegisters SMC_SIslands_MCArbDramTimingRegisters;

काष्ठा SMC_SISLANDS_SPLL_DIV_TABLE
अणु
    uपूर्णांक32_t    freq[256];
    uपूर्णांक32_t    ss[256];
पूर्ण;

#घोषणा SMC_SISLANDS_SPLL_DIV_TABLE_FBDIV_MASK  0x01ffffff
#घोषणा SMC_SISLANDS_SPLL_DIV_TABLE_FBDIV_SHIFT 0
#घोषणा SMC_SISLANDS_SPLL_DIV_TABLE_PDIV_MASK   0xfe000000
#घोषणा SMC_SISLANDS_SPLL_DIV_TABLE_PDIV_SHIFT  25
#घोषणा SMC_SISLANDS_SPLL_DIV_TABLE_CLKV_MASK   0x000fffff
#घोषणा SMC_SISLANDS_SPLL_DIV_TABLE_CLKV_SHIFT  0
#घोषणा SMC_SISLANDS_SPLL_DIV_TABLE_CLKS_MASK   0xfff00000
#घोषणा SMC_SISLANDS_SPLL_DIV_TABLE_CLKS_SHIFT  20

प्रकार काष्ठा SMC_SISLANDS_SPLL_DIV_TABLE SMC_SISLANDS_SPLL_DIV_TABLE;

#घोषणा SMC_SISLANDS_DTE_MAX_FILTER_STAGES 5

#घोषणा SMC_SISLANDS_DTE_MAX_TEMPERATURE_DEPENDENT_ARRAY_SIZE 16

काष्ठा Smc_SIslands_DTE_Configuration
अणु
    uपूर्णांक32_t tau[SMC_SISLANDS_DTE_MAX_FILTER_STAGES];
    uपूर्णांक32_t R[SMC_SISLANDS_DTE_MAX_FILTER_STAGES];
    uपूर्णांक32_t K;
    uपूर्णांक32_t T0;
    uपूर्णांक32_t MaxT;
    uपूर्णांक8_t  WinकरोwSize;
    uपूर्णांक8_t  Tdep_count;
    uपूर्णांक8_t  temp_select;
    uपूर्णांक8_t  DTE_mode;
    uपूर्णांक8_t  T_limits[SMC_SISLANDS_DTE_MAX_TEMPERATURE_DEPENDENT_ARRAY_SIZE];
    uपूर्णांक32_t Tdep_tau[SMC_SISLANDS_DTE_MAX_TEMPERATURE_DEPENDENT_ARRAY_SIZE];
    uपूर्णांक32_t Tdep_R[SMC_SISLANDS_DTE_MAX_TEMPERATURE_DEPENDENT_ARRAY_SIZE];
    uपूर्णांक32_t Tthreshold;
पूर्ण;

प्रकार काष्ठा Smc_SIslands_DTE_Configuration Smc_SIslands_DTE_Configuration;

#घोषणा SMC_SISLANDS_DTE_STATUS_FLAG_DTE_ON 1

#घोषणा SISLANDS_SMC_FIRMWARE_HEADER_LOCATION 0x10000

#घोषणा SISLANDS_SMC_FIRMWARE_HEADER_version                   0x0
#घोषणा SISLANDS_SMC_FIRMWARE_HEADER_flags                     0x4
#घोषणा SISLANDS_SMC_FIRMWARE_HEADER_softRegisters             0xC
#घोषणा SISLANDS_SMC_FIRMWARE_HEADER_stateTable                0x10
#घोषणा SISLANDS_SMC_FIRMWARE_HEADER_fanTable                  0x14
#घोषणा SISLANDS_SMC_FIRMWARE_HEADER_CacConfigTable            0x18
#घोषणा SISLANDS_SMC_FIRMWARE_HEADER_mcRegisterTable           0x24
#घोषणा SISLANDS_SMC_FIRMWARE_HEADER_mcArbDramAutoRefreshTable 0x30
#घोषणा SISLANDS_SMC_FIRMWARE_HEADER_spllTable                 0x38
#घोषणा SISLANDS_SMC_FIRMWARE_HEADER_DteConfiguration          0x40
#घोषणा SISLANDS_SMC_FIRMWARE_HEADER_PAPMParameters            0x48

#आशय pack(pop)

पूर्णांक si_copy_bytes_to_smc(काष्ठा radeon_device *rdev,
			 u32 smc_start_address,
			 स्थिर u8 *src, u32 byte_count, u32 limit);
व्योम si_start_smc(काष्ठा radeon_device *rdev);
व्योम si_reset_smc(काष्ठा radeon_device *rdev);
पूर्णांक si_program_jump_on_start(काष्ठा radeon_device *rdev);
व्योम si_stop_smc_घड़ी(काष्ठा radeon_device *rdev);
व्योम si_start_smc_घड़ी(काष्ठा radeon_device *rdev);
bool si_is_smc_running(काष्ठा radeon_device *rdev);
PPSMC_Result si_send_msg_to_smc(काष्ठा radeon_device *rdev, PPSMC_Msg msg);
PPSMC_Result si_रुको_क्रम_smc_inactive(काष्ठा radeon_device *rdev);
पूर्णांक si_load_smc_ucode(काष्ठा radeon_device *rdev, u32 limit);
पूर्णांक si_पढ़ो_smc_sram_dword(काष्ठा radeon_device *rdev, u32 smc_address,
			   u32 *value, u32 limit);
पूर्णांक si_ग_लिखो_smc_sram_dword(काष्ठा radeon_device *rdev, u32 smc_address,
			    u32 value, u32 limit);

#पूर्ण_अगर

