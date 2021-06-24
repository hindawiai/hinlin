<शैली गुरु>
/*
 * Copyright 2012 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __NISLANDS_SMC_H__
#घोषणा __NISLANDS_SMC_H__

#आशय pack(push, 1)

#घोषणा NISLANDS_MAX_SMC_PERFORMANCE_LEVELS_PER_SWSTATE 16

काष्ठा PP_NIslands_Dpm2PerfLevel
अणु
    uपूर्णांक8_t     MaxPS;
    uपूर्णांक8_t     TgtAct;
    uपूर्णांक8_t     MaxPS_StepInc;
    uपूर्णांक8_t     MaxPS_StepDec;
    uपूर्णांक8_t     PSST;
    uपूर्णांक8_t     NearTDPDec;
    uपूर्णांक8_t     AboveSafeInc;
    uपूर्णांक8_t     BelowSafeInc;
    uपूर्णांक8_t     PSDeltaLimit;
    uपूर्णांक8_t     PSDeltaWin;
    uपूर्णांक8_t     Reserved[6];
पूर्ण;

प्रकार काष्ठा PP_NIslands_Dpm2PerfLevel PP_NIslands_Dpm2PerfLevel;

काष्ठा PP_NIslands_DPM2Parameters
अणु
    uपूर्णांक32_t    TDPLimit;
    uपूर्णांक32_t    NearTDPLimit;
    uपूर्णांक32_t    SafePowerLimit;
    uपूर्णांक32_t    PowerBoostLimit;
पूर्ण;
प्रकार काष्ठा PP_NIslands_DPM2Parameters PP_NIslands_DPM2Parameters;

काष्ठा NISLANDS_SMC_SCLK_VALUE
अणु
    uपूर्णांक32_t        vCG_SPLL_FUNC_CNTL;
    uपूर्णांक32_t        vCG_SPLL_FUNC_CNTL_2;
    uपूर्णांक32_t        vCG_SPLL_FUNC_CNTL_3;
    uपूर्णांक32_t        vCG_SPLL_FUNC_CNTL_4;
    uपूर्णांक32_t        vCG_SPLL_SPREAD_SPECTRUM;
    uपूर्णांक32_t        vCG_SPLL_SPREAD_SPECTRUM_2;
    uपूर्णांक32_t        sclk_value;
पूर्ण;

प्रकार काष्ठा NISLANDS_SMC_SCLK_VALUE NISLANDS_SMC_SCLK_VALUE;

काष्ठा NISLANDS_SMC_MCLK_VALUE
अणु
    uपूर्णांक32_t        vMPLL_FUNC_CNTL;
    uपूर्णांक32_t        vMPLL_FUNC_CNTL_1;
    uपूर्णांक32_t        vMPLL_FUNC_CNTL_2;
    uपूर्णांक32_t        vMPLL_AD_FUNC_CNTL;
    uपूर्णांक32_t        vMPLL_AD_FUNC_CNTL_2;
    uपूर्णांक32_t        vMPLL_DQ_FUNC_CNTL;
    uपूर्णांक32_t        vMPLL_DQ_FUNC_CNTL_2;
    uपूर्णांक32_t        vMCLK_PWRMGT_CNTL;
    uपूर्णांक32_t        vDLL_CNTL;
    uपूर्णांक32_t        vMPLL_SS;
    uपूर्णांक32_t        vMPLL_SS2;
    uपूर्णांक32_t        mclk_value;
पूर्ण;

प्रकार काष्ठा NISLANDS_SMC_MCLK_VALUE NISLANDS_SMC_MCLK_VALUE;

काष्ठा NISLANDS_SMC_VOLTAGE_VALUE
अणु
    uपूर्णांक16_t             value;
    uपूर्णांक8_t              index;
    uपूर्णांक8_t              padding;
पूर्ण;

प्रकार काष्ठा NISLANDS_SMC_VOLTAGE_VALUE NISLANDS_SMC_VOLTAGE_VALUE;

काष्ठा NISLANDS_SMC_HW_PERFORMANCE_LEVEL
अणु
    uपूर्णांक8_t                     arbValue;
    uपूर्णांक8_t                     ACIndex;
    uपूर्णांक8_t                     displayWatermark;
    uपूर्णांक8_t                     gen2PCIE;
    uपूर्णांक8_t                     reserved1;
    uपूर्णांक8_t                     reserved2;
    uपूर्णांक8_t                     strobeMode;
    uपूर्णांक8_t                     mcFlags;
    uपूर्णांक32_t                    aT;
    uपूर्णांक32_t                    bSP;
    NISLANDS_SMC_SCLK_VALUE     sclk;
    NISLANDS_SMC_MCLK_VALUE     mclk;
    NISLANDS_SMC_VOLTAGE_VALUE  vddc;
    NISLANDS_SMC_VOLTAGE_VALUE  mvdd;
    NISLANDS_SMC_VOLTAGE_VALUE  vddci;
    NISLANDS_SMC_VOLTAGE_VALUE  std_vddc;
    uपूर्णांक32_t                    घातergate_en;
    uपूर्णांक8_t                     hUp;
    uपूर्णांक8_t                     hDown;
    uपूर्णांक8_t                     stateFlags;
    uपूर्णांक8_t                     arbRefreshState;
    uपूर्णांक32_t                    SQPowerThrottle;
    uपूर्णांक32_t                    SQPowerThrottle_2;
    uपूर्णांक32_t                    reserved[2];
    PP_NIslands_Dpm2PerfLevel   dpm2;
पूर्ण;

#घोषणा NISLANDS_SMC_STROBE_RATIO    0x0F
#घोषणा NISLANDS_SMC_STROBE_ENABLE   0x10

#घोषणा NISLANDS_SMC_MC_EDC_RD_FLAG  0x01
#घोषणा NISLANDS_SMC_MC_EDC_WR_FLAG  0x02
#घोषणा NISLANDS_SMC_MC_RTT_ENABLE   0x04
#घोषणा NISLANDS_SMC_MC_STUTTER_EN   0x08

प्रकार काष्ठा NISLANDS_SMC_HW_PERFORMANCE_LEVEL NISLANDS_SMC_HW_PERFORMANCE_LEVEL;

काष्ठा NISLANDS_SMC_SWSTATE
अणु
	uपूर्णांक8_t                             flags;
	uपूर्णांक8_t                             levelCount;
	uपूर्णांक8_t                             padding2;
	uपूर्णांक8_t                             padding3;
	NISLANDS_SMC_HW_PERFORMANCE_LEVEL   levels[];
पूर्ण;

प्रकार काष्ठा NISLANDS_SMC_SWSTATE NISLANDS_SMC_SWSTATE;

काष्ठा NISLANDS_SMC_SWSTATE_SINGLE अणु
	uपूर्णांक8_t                             flags;
	uपूर्णांक8_t                             levelCount;
	uपूर्णांक8_t                             padding2;
	uपूर्णांक8_t                             padding3;
	NISLANDS_SMC_HW_PERFORMANCE_LEVEL   level;
पूर्ण;

#घोषणा NISLANDS_SMC_VOLTAGEMASK_VDDC  0
#घोषणा NISLANDS_SMC_VOLTAGEMASK_MVDD  1
#घोषणा NISLANDS_SMC_VOLTAGEMASK_VDDCI 2
#घोषणा NISLANDS_SMC_VOLTAGEMASK_MAX   4

काष्ठा NISLANDS_SMC_VOLTAGEMASKTABLE
अणु
    uपूर्णांक8_t  highMask[NISLANDS_SMC_VOLTAGEMASK_MAX];
    uपूर्णांक32_t lowMask[NISLANDS_SMC_VOLTAGEMASK_MAX];
पूर्ण;

प्रकार काष्ठा NISLANDS_SMC_VOLTAGEMASKTABLE NISLANDS_SMC_VOLTAGEMASKTABLE;

#घोषणा NISLANDS_MAX_NO_VREG_STEPS 32

काष्ठा NISLANDS_SMC_STATETABLE
अणु
	uपूर्णांक8_t                             thermalProtectType;
	uपूर्णांक8_t                             प्रणालीFlags;
	uपूर्णांक8_t                             maxVDDCIndexInPPTable;
	uपूर्णांक8_t                             extraFlags;
	uपूर्णांक8_t                             highSMIO[NISLANDS_MAX_NO_VREG_STEPS];
	uपूर्णांक32_t                            lowSMIO[NISLANDS_MAX_NO_VREG_STEPS];
	NISLANDS_SMC_VOLTAGEMASKTABLE       voltageMaskTable;
	PP_NIslands_DPM2Parameters          dpm2Params;
	काष्ठा NISLANDS_SMC_SWSTATE_SINGLE  initialState;
	काष्ठा NISLANDS_SMC_SWSTATE_SINGLE  ACPIState;
	काष्ठा NISLANDS_SMC_SWSTATE_SINGLE  ULVState;
	NISLANDS_SMC_SWSTATE                driverState;
	NISLANDS_SMC_HW_PERFORMANCE_LEVEL   dpmLevels[NISLANDS_MAX_SMC_PERFORMANCE_LEVELS_PER_SWSTATE];
पूर्ण;

प्रकार काष्ठा NISLANDS_SMC_STATETABLE NISLANDS_SMC_STATETABLE;

#घोषणा NI_SMC_SOFT_REGISTERS_START        0x108

#घोषणा NI_SMC_SOFT_REGISTER_mclk_chg_समयout        0x0
#घोषणा NI_SMC_SOFT_REGISTER_delay_bbias             0xC
#घोषणा NI_SMC_SOFT_REGISTER_delay_vreg              0x10
#घोषणा NI_SMC_SOFT_REGISTER_delay_acpi              0x2C
#घोषणा NI_SMC_SOFT_REGISTER_seq_index               0x64
#घोषणा NI_SMC_SOFT_REGISTER_mvdd_chg_समय           0x68
#घोषणा NI_SMC_SOFT_REGISTER_mclk_चयन_lim         0x78
#घोषणा NI_SMC_SOFT_REGISTER_watermark_threshold     0x80
#घोषणा NI_SMC_SOFT_REGISTER_mc_block_delay          0x84
#घोषणा NI_SMC_SOFT_REGISTER_uvd_enabled             0x98

#घोषणा SMC_NISLANDS_MC_TPP_CAC_NUM_OF_ENTRIES 16
#घोषणा SMC_NISLANDS_LKGE_LUT_NUM_OF_TEMP_ENTRIES 16
#घोषणा SMC_NISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES 16
#घोषणा SMC_NISLANDS_BIF_LUT_NUM_OF_ENTRIES 4

काष्ठा SMC_NISLANDS_MC_TPP_CAC_TABLE
अणु
    uपूर्णांक32_t    tpp[SMC_NISLANDS_MC_TPP_CAC_NUM_OF_ENTRIES];
    uपूर्णांक32_t    cacValue[SMC_NISLANDS_MC_TPP_CAC_NUM_OF_ENTRIES];
पूर्ण;

प्रकार काष्ठा SMC_NISLANDS_MC_TPP_CAC_TABLE SMC_NISLANDS_MC_TPP_CAC_TABLE;


काष्ठा PP_NIslands_CACTABLES
अणु
    uपूर्णांक32_t                cac_bअगर_lut[SMC_NISLANDS_BIF_LUT_NUM_OF_ENTRIES];
    uपूर्णांक32_t                cac_lkge_lut[SMC_NISLANDS_LKGE_LUT_NUM_OF_TEMP_ENTRIES][SMC_NISLANDS_LKGE_LUT_NUM_OF_VOLT_ENTRIES];

    uपूर्णांक32_t                pwr_स्थिर;

    uपूर्णांक32_t                dc_cacValue;
    uपूर्णांक32_t                bअगर_cacValue;
    uपूर्णांक32_t                lkge_pwr;

    uपूर्णांक8_t                 cac_width;
    uपूर्णांक8_t                 winकरोw_size_p2;

    uपूर्णांक8_t                 num_drop_lsb;
    uपूर्णांक8_t                 padding_0;

    uपूर्णांक32_t                last_घातer;

    uपूर्णांक8_t                 AllowOvrflw;
    uपूर्णांक8_t                 MCWrWeight;
    uपूर्णांक8_t                 MCRdWeight;
    uपूर्णांक8_t                 padding_1[9];

    uपूर्णांक8_t                 enableWinAvg;
    uपूर्णांक8_t                 numWin_TDP;
    uपूर्णांक8_t                 l2numWin_TDP;
    uपूर्णांक8_t                 WinIndex;

    uपूर्णांक32_t                dynPwr_TDP[4];
    uपूर्णांक32_t                lkgePwr_TDP[4];
    uपूर्णांक32_t                घातer_TDP[4];
    uपूर्णांक32_t                avg_dynPwr_TDP;
    uपूर्णांक32_t                avg_lkgePwr_TDP;
    uपूर्णांक32_t                avg_घातer_TDP;
    uपूर्णांक32_t                lts_घातer_TDP;
    uपूर्णांक8_t                 lts_truncate_n;
    uपूर्णांक8_t                 padding_2[7];
पूर्ण;

प्रकार काष्ठा PP_NIslands_CACTABLES PP_NIslands_CACTABLES;

#घोषणा SMC_NISLANDS_MC_REGISTER_ARRAY_SIZE 32
#घोषणा SMC_NISLANDS_MC_REGISTER_ARRAY_SET_COUNT 20

काष्ठा SMC_NIslands_MCRegisterAddress
अणु
    uपूर्णांक16_t s0;
    uपूर्णांक16_t s1;
पूर्ण;

प्रकार काष्ठा SMC_NIslands_MCRegisterAddress SMC_NIslands_MCRegisterAddress;


काष्ठा SMC_NIslands_MCRegisterSet
अणु
    uपूर्णांक32_t value[SMC_NISLANDS_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

प्रकार काष्ठा SMC_NIslands_MCRegisterSet SMC_NIslands_MCRegisterSet;

काष्ठा SMC_NIslands_MCRegisters
अणु
    uपूर्णांक8_t                             last;
    uपूर्णांक8_t                             reserved[3];
    SMC_NIslands_MCRegisterAddress      address[SMC_NISLANDS_MC_REGISTER_ARRAY_SIZE];
    SMC_NIslands_MCRegisterSet          data[SMC_NISLANDS_MC_REGISTER_ARRAY_SET_COUNT];
पूर्ण;

प्रकार काष्ठा SMC_NIslands_MCRegisters SMC_NIslands_MCRegisters;

काष्ठा SMC_NIslands_MCArbDramTimingRegisterSet
अणु
    uपूर्णांक32_t mc_arb_dram_timing;
    uपूर्णांक32_t mc_arb_dram_timing2;
    uपूर्णांक8_t  mc_arb_rfsh_rate;
    uपूर्णांक8_t  padding[3];
पूर्ण;

प्रकार काष्ठा SMC_NIslands_MCArbDramTimingRegisterSet SMC_NIslands_MCArbDramTimingRegisterSet;

काष्ठा SMC_NIslands_MCArbDramTimingRegisters
अणु
    uपूर्णांक8_t                                     arb_current;
    uपूर्णांक8_t                                     reserved[3];
    SMC_NIslands_MCArbDramTimingRegisterSet     data[20];
पूर्ण;

प्रकार काष्ठा SMC_NIslands_MCArbDramTimingRegisters SMC_NIslands_MCArbDramTimingRegisters;

काष्ठा SMC_NISLANDS_SPLL_DIV_TABLE
अणु
    uपूर्णांक32_t    freq[256];
    uपूर्णांक32_t    ss[256];
पूर्ण;

#घोषणा SMC_NISLANDS_SPLL_DIV_TABLE_FBDIV_MASK  0x01ffffff
#घोषणा SMC_NISLANDS_SPLL_DIV_TABLE_FBDIV_SHIFT 0
#घोषणा SMC_NISLANDS_SPLL_DIV_TABLE_PDIV_MASK   0xfe000000
#घोषणा SMC_NISLANDS_SPLL_DIV_TABLE_PDIV_SHIFT  25
#घोषणा SMC_NISLANDS_SPLL_DIV_TABLE_CLKV_MASK   0x000fffff
#घोषणा SMC_NISLANDS_SPLL_DIV_TABLE_CLKV_SHIFT  0
#घोषणा SMC_NISLANDS_SPLL_DIV_TABLE_CLKS_MASK   0xfff00000
#घोषणा SMC_NISLANDS_SPLL_DIV_TABLE_CLKS_SHIFT  20

प्रकार काष्ठा SMC_NISLANDS_SPLL_DIV_TABLE SMC_NISLANDS_SPLL_DIV_TABLE;

#घोषणा NISLANDS_SMC_FIRMWARE_HEADER_LOCATION 0x100

#घोषणा NISLANDS_SMC_FIRMWARE_HEADER_version                   0x0
#घोषणा NISLANDS_SMC_FIRMWARE_HEADER_flags                     0x4
#घोषणा NISLANDS_SMC_FIRMWARE_HEADER_softRegisters             0x8
#घोषणा NISLANDS_SMC_FIRMWARE_HEADER_stateTable                0xC
#घोषणा NISLANDS_SMC_FIRMWARE_HEADER_fanTable                  0x10
#घोषणा NISLANDS_SMC_FIRMWARE_HEADER_cacTable                  0x14
#घोषणा NISLANDS_SMC_FIRMWARE_HEADER_mcRegisterTable           0x20
#घोषणा NISLANDS_SMC_FIRMWARE_HEADER_mcArbDramAutoRefreshTable 0x2C
#घोषणा NISLANDS_SMC_FIRMWARE_HEADER_spllTable                 0x30

#आशय pack(pop)

#पूर्ण_अगर

