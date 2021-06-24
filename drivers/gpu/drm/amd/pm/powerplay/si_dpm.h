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
#अगर_अघोषित __SI_DPM_H__
#घोषणा __SI_DPM_H__

#समावेश "amdgpu_atombios.h"
#समावेश "sislands_smc.h"

#घोषणा MC_CG_CONFIG                                    0x96f
#घोषणा MC_ARB_CG                                       0x9fa
#घोषणा		CG_ARB_REQ(x)				((x) << 0)
#घोषणा		CG_ARB_REQ_MASK				(0xff << 0)

#घोषणा	MC_ARB_DRAM_TIMING_1				0x9fc
#घोषणा	MC_ARB_DRAM_TIMING_2				0x9fd
#घोषणा	MC_ARB_DRAM_TIMING_3				0x9fe
#घोषणा	MC_ARB_DRAM_TIMING2_1				0x9ff
#घोषणा	MC_ARB_DRAM_TIMING2_2				0xa00
#घोषणा	MC_ARB_DRAM_TIMING2_3				0xa01

#घोषणा MAX_NO_OF_MVDD_VALUES 2
#घोषणा MAX_NO_VREG_STEPS 32
#घोषणा NISLANDS_MAX_SMC_PERFORMANCE_LEVELS_PER_SWSTATE 16
#घोषणा SMC_NISLANDS_MC_REGISTER_ARRAY_SIZE 32
#घोषणा SMC_NISLANDS_MC_REGISTER_ARRAY_SET_COUNT 20
#घोषणा RV770_ASI_DFLT                                1000
#घोषणा CYPRESS_HASI_DFLT                               400000
#घोषणा PCIE_PERF_REQ_PECI_GEN1         2
#घोषणा PCIE_PERF_REQ_PECI_GEN2         3
#घोषणा PCIE_PERF_REQ_PECI_GEN3         4
#घोषणा RV770_DEFAULT_VCLK_FREQ  53300 /* 10 khz */
#घोषणा RV770_DEFAULT_DCLK_FREQ  40000 /* 10 khz */

#घोषणा SMC_EVERGREEN_MC_REGISTER_ARRAY_SIZE 16

#घोषणा RV770_SMC_TABLE_ADDRESS 0xB000
#घोषणा RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE    3

#घोषणा SMC_STROBE_RATIO    0x0F
#घोषणा SMC_STROBE_ENABLE   0x10

#घोषणा SMC_MC_EDC_RD_FLAG  0x01
#घोषणा SMC_MC_EDC_WR_FLAG  0x02
#घोषणा SMC_MC_RTT_ENABLE   0x04
#घोषणा SMC_MC_STUTTER_EN   0x08

#घोषणा RV770_SMC_VOLTAGEMASK_VDDC 0
#घोषणा RV770_SMC_VOLTAGEMASK_MVDD 1
#घोषणा RV770_SMC_VOLTAGEMASK_VDDCI 2
#घोषणा RV770_SMC_VOLTAGEMASK_MAX  4

#घोषणा NISLANDS_MAX_SMC_PERFORMANCE_LEVELS_PER_SWSTATE 16
#घोषणा NISLANDS_SMC_STROBE_RATIO    0x0F
#घोषणा NISLANDS_SMC_STROBE_ENABLE   0x10

#घोषणा NISLANDS_SMC_MC_EDC_RD_FLAG  0x01
#घोषणा NISLANDS_SMC_MC_EDC_WR_FLAG  0x02
#घोषणा NISLANDS_SMC_MC_RTT_ENABLE   0x04
#घोषणा NISLANDS_SMC_MC_STUTTER_EN   0x08

#घोषणा MAX_NO_VREG_STEPS 32

#घोषणा NISLANDS_SMC_VOLTAGEMASK_VDDC  0
#घोषणा NISLANDS_SMC_VOLTAGEMASK_MVDD  1
#घोषणा NISLANDS_SMC_VOLTAGEMASK_VDDCI 2
#घोषणा NISLANDS_SMC_VOLTAGEMASK_MAX   4

#घोषणा SISLANDS_MCREGISTERTABLE_INITIAL_SLOT               0
#घोषणा SISLANDS_MCREGISTERTABLE_ACPI_SLOT                  1
#घोषणा SISLANDS_MCREGISTERTABLE_ULV_SLOT                   2
#घोषणा SISLANDS_MCREGISTERTABLE_FIRST_DRIVERSTATE_SLOT     3

#घोषणा SISLANDS_LEAKAGE_INDEX0     0xff01
#घोषणा SISLANDS_MAX_LEAKAGE_COUNT  4

#घोषणा SISLANDS_MAX_HARDWARE_POWERLEVELS 5
#घोषणा SISLANDS_INITIAL_STATE_ARB_INDEX    0
#घोषणा SISLANDS_ACPI_STATE_ARB_INDEX       1
#घोषणा SISLANDS_ULV_STATE_ARB_INDEX        2
#घोषणा SISLANDS_DRIVER_STATE_ARB_INDEX     3

#घोषणा SISLANDS_DPM2_MAX_PULSE_SKIP        256

#घोषणा SISLANDS_DPM2_NEAR_TDP_DEC          10
#घोषणा SISLANDS_DPM2_ABOVE_SAFE_INC        5
#घोषणा SISLANDS_DPM2_BELOW_SAFE_INC        20

#घोषणा SISLANDS_DPM2_TDP_SAFE_LIMIT_PERCENT            80

#घोषणा SISLANDS_DPM2_MAXPS_PERCENT_H                   99
#घोषणा SISLANDS_DPM2_MAXPS_PERCENT_M                   99

#घोषणा SISLANDS_DPM2_SQ_RAMP_MAX_POWER                 0x3FFF
#घोषणा SISLANDS_DPM2_SQ_RAMP_MIN_POWER                 0x12
#घोषणा SISLANDS_DPM2_SQ_RAMP_MAX_POWER_DELTA           0x15
#घोषणा SISLANDS_DPM2_SQ_RAMP_STI_SIZE                  0x1E
#घोषणा SISLANDS_DPM2_SQ_RAMP_LTI_RATIO                 0xF

#घोषणा SISLANDS_DPM2_PWREFFICIENCYRATIO_MARGIN         10

#घोषणा SISLANDS_VRC_DFLT                               0xC000B3
#घोषणा SISLANDS_ULVVOLTAGECHANGEDELAY_DFLT             1687
#घोषणा SISLANDS_CGULVPARAMETER_DFLT                    0x00040035
#घोषणा SISLANDS_CGULVCONTROL_DFLT                      0x1f007550

#घोषणा SI_ASI_DFLT                                10000
#घोषणा SI_BSP_DFLT                                0x41EB
#घोषणा SI_BSU_DFLT                                0x2
#घोषणा SI_AH_DFLT                                 5
#घोषणा SI_RLP_DFLT                                25
#घोषणा SI_RMP_DFLT                                65
#घोषणा SI_LHP_DFLT                                40
#घोषणा SI_LMP_DFLT                                15
#घोषणा SI_TD_DFLT                                 0
#घोषणा SI_UTC_DFLT_00                             0x24
#घोषणा SI_UTC_DFLT_01                             0x22
#घोषणा SI_UTC_DFLT_02                             0x22
#घोषणा SI_UTC_DFLT_03                             0x22
#घोषणा SI_UTC_DFLT_04                             0x22
#घोषणा SI_UTC_DFLT_05                             0x22
#घोषणा SI_UTC_DFLT_06                             0x22
#घोषणा SI_UTC_DFLT_07                             0x22
#घोषणा SI_UTC_DFLT_08                             0x22
#घोषणा SI_UTC_DFLT_09                             0x22
#घोषणा SI_UTC_DFLT_10                             0x22
#घोषणा SI_UTC_DFLT_11                             0x22
#घोषणा SI_UTC_DFLT_12                             0x22
#घोषणा SI_UTC_DFLT_13                             0x22
#घोषणा SI_UTC_DFLT_14                             0x22
#घोषणा SI_DTC_DFLT_00                             0x24
#घोषणा SI_DTC_DFLT_01                             0x22
#घोषणा SI_DTC_DFLT_02                             0x22
#घोषणा SI_DTC_DFLT_03                             0x22
#घोषणा SI_DTC_DFLT_04                             0x22
#घोषणा SI_DTC_DFLT_05                             0x22
#घोषणा SI_DTC_DFLT_06                             0x22
#घोषणा SI_DTC_DFLT_07                             0x22
#घोषणा SI_DTC_DFLT_08                             0x22
#घोषणा SI_DTC_DFLT_09                             0x22
#घोषणा SI_DTC_DFLT_10                             0x22
#घोषणा SI_DTC_DFLT_11                             0x22
#घोषणा SI_DTC_DFLT_12                             0x22
#घोषणा SI_DTC_DFLT_13                             0x22
#घोषणा SI_DTC_DFLT_14                             0x22
#घोषणा SI_VRC_DFLT                                0x0000C003
#घोषणा SI_VOLTAGERESPONSETIME_DFLT                1000
#घोषणा SI_BACKBIASRESPONSETIME_DFLT               1000
#घोषणा SI_VRU_DFLT                                0x3
#घोषणा SI_SPLLSTEPTIME_DFLT                       0x1000
#घोषणा SI_SPLLSTEPUNIT_DFLT                       0x3
#घोषणा SI_TPU_DFLT                                0
#घोषणा SI_TPC_DFLT                                0x200
#घोषणा SI_SSTU_DFLT                               0
#घोषणा SI_SST_DFLT                                0x00C8
#घोषणा SI_GICST_DFLT                              0x200
#घोषणा SI_FCT_DFLT                                0x0400
#घोषणा SI_FCTU_DFLT                               0
#घोषणा SI_CTXCGTT3DRPHC_DFLT                      0x20
#घोषणा SI_CTXCGTT3DRSDC_DFLT                      0x40
#घोषणा SI_VDDC3DOORPHC_DFLT                       0x100
#घोषणा SI_VDDC3DOORSDC_DFLT                       0x7
#घोषणा SI_VDDC3DOORSU_DFLT                        0
#घोषणा SI_MPLLLOCKTIME_DFLT                       100
#घोषणा SI_MPLLRESETTIME_DFLT                      150
#घोषणा SI_VCOSTEPPCT_DFLT                          20
#घोषणा SI_ENDINGVCOSTEPPCT_DFLT                    5
#घोषणा SI_REFERENCEDIVIDER_DFLT                    4

#घोषणा SI_PM_NUMBER_OF_TC 15
#घोषणा SI_PM_NUMBER_OF_SCLKS 20
#घोषणा SI_PM_NUMBER_OF_MCLKS 4
#घोषणा SI_PM_NUMBER_OF_VOLTAGE_LEVELS 4
#घोषणा SI_PM_NUMBER_OF_ACTIVITY_LEVELS 3

/* XXX are these ok? */
#घोषणा SI_TEMP_RANGE_MIN (90 * 1000)
#घोषणा SI_TEMP_RANGE_MAX (120 * 1000)

#घोषणा FDO_PWM_MODE_STATIC  1
#घोषणा FDO_PWM_MODE_STATIC_RPM 5

क्रमागत ni_dc_cac_level
अणु
	NISLANDS_DCCAC_LEVEL_0 = 0,
	NISLANDS_DCCAC_LEVEL_1,
	NISLANDS_DCCAC_LEVEL_2,
	NISLANDS_DCCAC_LEVEL_3,
	NISLANDS_DCCAC_LEVEL_4,
	NISLANDS_DCCAC_LEVEL_5,
	NISLANDS_DCCAC_LEVEL_6,
	NISLANDS_DCCAC_LEVEL_7,
	NISLANDS_DCCAC_MAX_LEVELS
पूर्ण;

क्रमागत si_cac_config_reg_type
अणु
	SISLANDS_CACCONFIG_MMR = 0,
	SISLANDS_CACCONFIG_CGIND,
	SISLANDS_CACCONFIG_MAX
पूर्ण;

क्रमागत si_घातer_level अणु
	SI_POWER_LEVEL_LOW = 0,
	SI_POWER_LEVEL_MEDIUM = 1,
	SI_POWER_LEVEL_HIGH = 2,
	SI_POWER_LEVEL_CTXSW = 3,
पूर्ण;

क्रमागत si_td अणु
	SI_TD_AUTO,
	SI_TD_UP,
	SI_TD_DOWN,
पूर्ण;

क्रमागत si_display_watermark अणु
	SI_DISPLAY_WATERMARK_LOW = 0,
	SI_DISPLAY_WATERMARK_HIGH = 1,
पूर्ण;

क्रमागत si_display_gap
अणु
    SI_PM_DISPLAY_GAP_VBLANK_OR_WM = 0,
    SI_PM_DISPLAY_GAP_VBLANK       = 1,
    SI_PM_DISPLAY_GAP_WATERMARK    = 2,
    SI_PM_DISPLAY_GAP_IGNORE       = 3,
पूर्ण;

बाह्य स्थिर काष्ठा amdgpu_ip_block_version si_smu_ip_block;

काष्ठा ni_leakage_coeffients
अणु
	u32 at;
	u32 bt;
	u32 av;
	u32 bv;
	s32 t_slope;
	s32 t_पूर्णांकercept;
	u32 t_ref;
पूर्ण;

काष्ठा SMC_Evergreen_MCRegisterAddress
अणु
    uपूर्णांक16_t s0;
    uपूर्णांक16_t s1;
पूर्ण;

प्रकार काष्ठा SMC_Evergreen_MCRegisterAddress SMC_Evergreen_MCRegisterAddress;

काष्ठा evergreen_mc_reg_entry अणु
	u32 mclk_max;
	u32 mc_data[SMC_EVERGREEN_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा evergreen_mc_reg_table अणु
	u8 last;
	u8 num_entries;
	u16 valid_flag;
	काष्ठा evergreen_mc_reg_entry mc_reg_table_entry[MAX_AC_TIMING_ENTRIES];
	SMC_Evergreen_MCRegisterAddress mc_reg_address[SMC_EVERGREEN_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा SMC_Evergreen_MCRegisterSet
अणु
    uपूर्णांक32_t value[SMC_EVERGREEN_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

प्रकार काष्ठा SMC_Evergreen_MCRegisterSet SMC_Evergreen_MCRegisterSet;

काष्ठा SMC_Evergreen_MCRegisters
अणु
    uपूर्णांक8_t                             last;
    uपूर्णांक8_t                             reserved[3];
    SMC_Evergreen_MCRegisterAddress     address[SMC_EVERGREEN_MC_REGISTER_ARRAY_SIZE];
    SMC_Evergreen_MCRegisterSet         data[5];
पूर्ण;

प्रकार काष्ठा SMC_Evergreen_MCRegisters SMC_Evergreen_MCRegisters;

काष्ठा SMC_NIslands_MCRegisterSet
अणु
    uपूर्णांक32_t value[SMC_NISLANDS_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

प्रकार काष्ठा SMC_NIslands_MCRegisterSet SMC_NIslands_MCRegisterSet;

काष्ठा ni_mc_reg_entry अणु
	u32 mclk_max;
	u32 mc_data[SMC_NISLANDS_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा SMC_NIslands_MCRegisterAddress
अणु
    uपूर्णांक16_t s0;
    uपूर्णांक16_t s1;
पूर्ण;

प्रकार काष्ठा SMC_NIslands_MCRegisterAddress SMC_NIslands_MCRegisterAddress;

काष्ठा SMC_NIslands_MCRegisters
अणु
    uपूर्णांक8_t                             last;
    uपूर्णांक8_t                             reserved[3];
    SMC_NIslands_MCRegisterAddress      address[SMC_NISLANDS_MC_REGISTER_ARRAY_SIZE];
    SMC_NIslands_MCRegisterSet          data[SMC_NISLANDS_MC_REGISTER_ARRAY_SET_COUNT];
पूर्ण;

प्रकार काष्ठा SMC_NIslands_MCRegisters SMC_NIslands_MCRegisters;

काष्ठा evergreen_ulv_param अणु
	bool supported;
	काष्ठा rv7xx_pl *pl;
पूर्ण;

काष्ठा evergreen_arb_रेजिस्टरs अणु
	u32 mc_arb_dram_timing;
	u32 mc_arb_dram_timing2;
	u32 mc_arb_rfsh_rate;
	u32 mc_arb_burst_समय;
पूर्ण;

काष्ठा at अणु
	u32 rlp;
	u32 rmp;
	u32 lhp;
	u32 lmp;
पूर्ण;

काष्ठा ni_घड़ी_रेजिस्टरs अणु
	u32 cg_spll_func_cntl;
	u32 cg_spll_func_cntl_2;
	u32 cg_spll_func_cntl_3;
	u32 cg_spll_func_cntl_4;
	u32 cg_spll_spपढ़ो_spectrum;
	u32 cg_spll_spपढ़ो_spectrum_2;
	u32 mclk_pwrmgt_cntl;
	u32 dll_cntl;
	u32 mpll_ad_func_cntl;
	u32 mpll_ad_func_cntl_2;
	u32 mpll_dq_func_cntl;
	u32 mpll_dq_func_cntl_2;
	u32 mpll_ss1;
	u32 mpll_ss2;
पूर्ण;

काष्ठा RV770_SMC_SCLK_VALUE
अणु
    uपूर्णांक32_t        vCG_SPLL_FUNC_CNTL;
    uपूर्णांक32_t        vCG_SPLL_FUNC_CNTL_2;
    uपूर्णांक32_t        vCG_SPLL_FUNC_CNTL_3;
    uपूर्णांक32_t        vCG_SPLL_SPREAD_SPECTRUM;
    uपूर्णांक32_t        vCG_SPLL_SPREAD_SPECTRUM_2;
    uपूर्णांक32_t        sclk_value;
पूर्ण;

प्रकार काष्ठा RV770_SMC_SCLK_VALUE RV770_SMC_SCLK_VALUE;

काष्ठा RV770_SMC_MCLK_VALUE
अणु
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

प्रकार काष्ठा RV770_SMC_MCLK_VALUE RV770_SMC_MCLK_VALUE;


काष्ठा RV730_SMC_MCLK_VALUE
अणु
    uपूर्णांक32_t        vMCLK_PWRMGT_CNTL;
    uपूर्णांक32_t        vDLL_CNTL;
    uपूर्णांक32_t        vMPLL_FUNC_CNTL;
    uपूर्णांक32_t        vMPLL_FUNC_CNTL2;
    uपूर्णांक32_t        vMPLL_FUNC_CNTL3;
    uपूर्णांक32_t        vMPLL_SS;
    uपूर्णांक32_t        vMPLL_SS2;
    uपूर्णांक32_t        mclk_value;
पूर्ण;

प्रकार काष्ठा RV730_SMC_MCLK_VALUE RV730_SMC_MCLK_VALUE;

काष्ठा RV770_SMC_VOLTAGE_VALUE
अणु
    uपूर्णांक16_t             value;
    uपूर्णांक8_t              index;
    uपूर्णांक8_t              padding;
पूर्ण;

प्रकार काष्ठा RV770_SMC_VOLTAGE_VALUE RV770_SMC_VOLTAGE_VALUE;

जोड़ RV7XX_SMC_MCLK_VALUE
अणु
    RV770_SMC_MCLK_VALUE    mclk770;
    RV730_SMC_MCLK_VALUE    mclk730;
पूर्ण;

प्रकार जोड़ RV7XX_SMC_MCLK_VALUE RV7XX_SMC_MCLK_VALUE, *LPRV7XX_SMC_MCLK_VALUE;

काष्ठा RV770_SMC_HW_PERFORMANCE_LEVEL
अणु
    uपूर्णांक8_t                 arbValue;
    जोड़अणु
        uपूर्णांक8_t             seqValue;
        uपूर्णांक8_t             ACIndex;
    पूर्ण;
    uपूर्णांक8_t                 displayWatermark;
    uपूर्णांक8_t                 gen2PCIE;
    uपूर्णांक8_t                 gen2XSP;
    uपूर्णांक8_t                 backbias;
    uपूर्णांक8_t                 strobeMode;
    uपूर्णांक8_t                 mcFlags;
    uपूर्णांक32_t                aT;
    uपूर्णांक32_t                bSP;
    RV770_SMC_SCLK_VALUE    sclk;
    RV7XX_SMC_MCLK_VALUE    mclk;
    RV770_SMC_VOLTAGE_VALUE vddc;
    RV770_SMC_VOLTAGE_VALUE mvdd;
    RV770_SMC_VOLTAGE_VALUE vddci;
    uपूर्णांक8_t                 reserved1;
    uपूर्णांक8_t                 reserved2;
    uपूर्णांक8_t                 stateFlags;
    uपूर्णांक8_t                 padding;
पूर्ण;

प्रकार काष्ठा RV770_SMC_HW_PERFORMANCE_LEVEL RV770_SMC_HW_PERFORMANCE_LEVEL;

काष्ठा RV770_SMC_SWSTATE
अणु
    uपूर्णांक8_t           flags;
    uपूर्णांक8_t           padding1;
    uपूर्णांक8_t           padding2;
    uपूर्णांक8_t           padding3;
    RV770_SMC_HW_PERFORMANCE_LEVEL levels[RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE];
पूर्ण;

प्रकार काष्ठा RV770_SMC_SWSTATE RV770_SMC_SWSTATE;

काष्ठा RV770_SMC_VOLTAGEMASKTABLE
अणु
    uपूर्णांक8_t  highMask[RV770_SMC_VOLTAGEMASK_MAX];
    uपूर्णांक32_t lowMask[RV770_SMC_VOLTAGEMASK_MAX];
पूर्ण;

प्रकार काष्ठा RV770_SMC_VOLTAGEMASKTABLE RV770_SMC_VOLTAGEMASKTABLE;

काष्ठा RV770_SMC_STATETABLE
अणु
    uपूर्णांक8_t             thermalProtectType;
    uपूर्णांक8_t             प्रणालीFlags;
    uपूर्णांक8_t             maxVDDCIndexInPPTable;
    uपूर्णांक8_t             extraFlags;
    uपूर्णांक8_t             highSMIO[MAX_NO_VREG_STEPS];
    uपूर्णांक32_t            lowSMIO[MAX_NO_VREG_STEPS];
    RV770_SMC_VOLTAGEMASKTABLE voltageMaskTable;
    RV770_SMC_SWSTATE   initialState;
    RV770_SMC_SWSTATE   ACPIState;
    RV770_SMC_SWSTATE   driverState;
    RV770_SMC_SWSTATE   ULVState;
पूर्ण;

प्रकार काष्ठा RV770_SMC_STATETABLE RV770_SMC_STATETABLE;

काष्ठा vddc_table_entry अणु
	u16 vddc;
	u8 vddc_index;
	u8 high_smio;
	u32 low_smio;
पूर्ण;

काष्ठा rv770_घड़ी_रेजिस्टरs अणु
	u32 cg_spll_func_cntl;
	u32 cg_spll_func_cntl_2;
	u32 cg_spll_func_cntl_3;
	u32 cg_spll_spपढ़ो_spectrum;
	u32 cg_spll_spपढ़ो_spectrum_2;
	u32 mpll_ad_func_cntl;
	u32 mpll_ad_func_cntl_2;
	u32 mpll_dq_func_cntl;
	u32 mpll_dq_func_cntl_2;
	u32 mclk_pwrmgt_cntl;
	u32 dll_cntl;
	u32 mpll_ss1;
	u32 mpll_ss2;
पूर्ण;

काष्ठा rv730_घड़ी_रेजिस्टरs अणु
	u32 cg_spll_func_cntl;
	u32 cg_spll_func_cntl_2;
	u32 cg_spll_func_cntl_3;
	u32 cg_spll_spपढ़ो_spectrum;
	u32 cg_spll_spपढ़ो_spectrum_2;
	u32 mclk_pwrmgt_cntl;
	u32 dll_cntl;
	u32 mpll_func_cntl;
	u32 mpll_func_cntl2;
	u32 mpll_func_cntl3;
	u32 mpll_ss;
	u32 mpll_ss2;
पूर्ण;

जोड़ r7xx_घड़ी_रेजिस्टरs अणु
	काष्ठा rv770_घड़ी_रेजिस्टरs rv770;
	काष्ठा rv730_घड़ी_रेजिस्टरs rv730;
पूर्ण;

काष्ठा rv7xx_घातer_info अणु
	/* flags */
	bool mem_gddr5;
	bool pcie_gen2;
	bool dynamic_pcie_gen2;
	bool acpi_pcie_gen2;
	bool boot_in_gen2;
	bool voltage_control; /* vddc */
	bool mvdd_control;
	bool sclk_ss;
	bool mclk_ss;
	bool dynamic_ss;
	bool gfx_घड़ी_gating;
	bool mg_घड़ी_gating;
	bool mgcgtssm;
	bool घातer_gating;
	bool thermal_protection;
	bool display_gap;
	bool dcodt;
	bool ulps;
	/* रेजिस्टरs */
	जोड़ r7xx_घड़ी_रेजिस्टरs clk_regs;
	u32 s0_vid_lower_smio_cntl;
	/* voltage */
	u32 vddc_mask_low;
	u32 mvdd_mask_low;
	u32 mvdd_split_frequency;
	u32 mvdd_low_smio[MAX_NO_OF_MVDD_VALUES];
	u16 max_vddc;
	u16 max_vddc_in_table;
	u16 min_vddc_in_table;
	काष्ठा vddc_table_entry vddc_table[MAX_NO_VREG_STEPS];
	u8 valid_vddc_entries;
	/* dc odt */
	u32 mclk_odt_threshold;
	u8 odt_value_0[2];
	u8 odt_value_1[2];
	/* stored values */
	u32 boot_sclk;
	u16 acpi_vddc;
	u32 ref_भाग;
	u32 active_स्वतः_throttle_sources;
	u32 mclk_stutter_mode_threshold;
	u32 mclk_strobe_mode_threshold;
	u32 mclk_edc_enable_threshold;
	u32 bsp;
	u32 bsu;
	u32 pbsp;
	u32 pbsu;
	u32 dsp;
	u32 psp;
	u32 asi;
	u32 pasi;
	u32 vrc;
	u32 restricted_levels;
	u32 rlp;
	u32 rmp;
	u32 lhp;
	u32 lmp;
	/* smc offsets */
	u16 state_table_start;
	u16 soft_regs_start;
	u16 sram_end;
	/* scratch काष्ठाs */
	RV770_SMC_STATETABLE smc_statetable;
पूर्ण;

काष्ठा rv7xx_pl अणु
	u32 sclk;
	u32 mclk;
	u16 vddc;
	u16 vddci; /* eg+ only */
	u32 flags;
	क्रमागत amdgpu_pcie_gen pcie_gen; /* si+ only */
पूर्ण;

काष्ठा rv7xx_ps अणु
	काष्ठा rv7xx_pl high;
	काष्ठा rv7xx_pl medium;
	काष्ठा rv7xx_pl low;
	bool dc_compatible;
पूर्ण;

काष्ठा si_ps अणु
	u16 perक्रमmance_level_count;
	bool dc_compatible;
	काष्ठा rv7xx_pl perक्रमmance_levels[NISLANDS_MAX_SMC_PERFORMANCE_LEVELS_PER_SWSTATE];
पूर्ण;

काष्ठा ni_mc_reg_table अणु
	u8 last;
	u8 num_entries;
	u16 valid_flag;
	काष्ठा ni_mc_reg_entry mc_reg_table_entry[MAX_AC_TIMING_ENTRIES];
	SMC_NIslands_MCRegisterAddress mc_reg_address[SMC_NISLANDS_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा ni_cac_data
अणु
	काष्ठा ni_leakage_coeffients leakage_coefficients;
	u32 i_leakage;
	s32 leakage_minimum_temperature;
	u32 pwr_स्थिर;
	u32 dc_cac_value;
	u32 bअगर_cac_value;
	u32 lkge_pwr;
	u8 mc_wr_weight;
	u8 mc_rd_weight;
	u8 allow_ovrflw;
	u8 num_win_tdp;
	u8 l2num_win_tdp;
	u8 lts_truncate_n;
पूर्ण;

काष्ठा evergreen_घातer_info अणु
	/* must be first! */
	काष्ठा rv7xx_घातer_info rv7xx;
	/* flags */
	bool vddci_control;
	bool dynamic_ac_timing;
	bool abm;
	bool mcls;
	bool light_sleep;
	bool memory_transition;
	bool pcie_perक्रमmance_request;
	bool pcie_perक्रमmance_request_रेजिस्टरed;
	bool sclk_deep_sleep;
	bool dll_शेष_on;
	bool ls_घड़ी_gating;
	bool smu_uvd_hs;
	bool uvd_enabled;
	/* stored values */
	u16 acpi_vddci;
	u8 mvdd_high_index;
	u8 mvdd_low_index;
	u32 mclk_edc_wr_enable_threshold;
	काष्ठा evergreen_mc_reg_table mc_reg_table;
	काष्ठा atom_voltage_table vddc_voltage_table;
	काष्ठा atom_voltage_table vddci_voltage_table;
	काष्ठा evergreen_arb_रेजिस्टरs bootup_arb_रेजिस्टरs;
	काष्ठा evergreen_ulv_param ulv;
	काष्ठा at ats[2];
	/* smc offsets */
	u16 mc_reg_table_start;
	काष्ठा amdgpu_ps current_rps;
	काष्ठा rv7xx_ps current_ps;
	काष्ठा amdgpu_ps requested_rps;
	काष्ठा rv7xx_ps requested_ps;
पूर्ण;

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
    NISLANDS_SMC_SWSTATE                initialState;
    NISLANDS_SMC_SWSTATE                ACPIState;
    NISLANDS_SMC_SWSTATE                ULVState;
    NISLANDS_SMC_SWSTATE                driverState;
    NISLANDS_SMC_HW_PERFORMANCE_LEVEL   dpmLevels[NISLANDS_MAX_SMC_PERFORMANCE_LEVELS_PER_SWSTATE - 1];
पूर्ण;

प्रकार काष्ठा NISLANDS_SMC_STATETABLE NISLANDS_SMC_STATETABLE;

काष्ठा ni_घातer_info अणु
	/* must be first! */
	काष्ठा evergreen_घातer_info eg;
	काष्ठा ni_घड़ी_रेजिस्टरs घड़ी_रेजिस्टरs;
	काष्ठा ni_mc_reg_table mc_reg_table;
	u32 mclk_rtt_mode_threshold;
	/* flags */
	bool use_घातer_boost_limit;
	bool support_cac_दीर्घ_term_average;
	bool cac_enabled;
	bool cac_configuration_required;
	bool driver_calculate_cac_leakage;
	bool pc_enabled;
	bool enable_घातer_containment;
	bool enable_cac;
	bool enable_sq_ramping;
	/* smc offsets */
	u16 arb_table_start;
	u16 fan_table_start;
	u16 cac_table_start;
	u16 spll_table_start;
	/* CAC stuff */
	काष्ठा ni_cac_data cac_data;
	u32 dc_cac_table[NISLANDS_DCCAC_MAX_LEVELS];
	स्थिर काष्ठा ni_cac_weights *cac_weights;
	u8 lta_winकरोw_size;
	u8 lts_truncate;
	काष्ठा si_ps current_ps;
	काष्ठा si_ps requested_ps;
	/* scratch काष्ठाs */
	SMC_NIslands_MCRegisters smc_mc_reg_table;
	NISLANDS_SMC_STATETABLE smc_statetable;
पूर्ण;

काष्ठा si_cac_config_reg
अणु
	u32 offset;
	u32 mask;
	u32 shअगरt;
	u32 value;
	क्रमागत si_cac_config_reg_type type;
पूर्ण;

काष्ठा si_घातertune_data
अणु
	u32 cac_winकरोw;
	u32 l2_lta_winकरोw_size_शेष;
	u8 lts_truncate_शेष;
	u8 shअगरt_n_शेष;
	u8 operating_temp;
	काष्ठा ni_leakage_coeffients leakage_coefficients;
	u32 fixed_kt;
	u32 lkge_lut_v0_percent;
	u8 dc_cac[NISLANDS_DCCAC_MAX_LEVELS];
	bool enable_घातertune_by_शेष;
पूर्ण;

काष्ठा si_dyn_घातertune_data
अणु
	u32 cac_leakage;
	s32 leakage_minimum_temperature;
	u32 wपूर्णांकime;
	u32 l2_lta_winकरोw_size;
	u8 lts_truncate;
	u8 shअगरt_n;
	u8 dc_pwr_value;
	bool disable_uvd_घातertune;
पूर्ण;

काष्ठा si_dte_data
अणु
	u32 tau[SMC_SISLANDS_DTE_MAX_FILTER_STAGES];
	u32 r[SMC_SISLANDS_DTE_MAX_FILTER_STAGES];
	u32 k;
	u32 t0;
	u32 max_t;
	u8 winकरोw_size;
	u8 temp_select;
	u8 dte_mode;
	u8 tdep_count;
	u8 t_limits[SMC_SISLANDS_DTE_MAX_TEMPERATURE_DEPENDENT_ARRAY_SIZE];
	u32 tdep_tau[SMC_SISLANDS_DTE_MAX_TEMPERATURE_DEPENDENT_ARRAY_SIZE];
	u32 tdep_r[SMC_SISLANDS_DTE_MAX_TEMPERATURE_DEPENDENT_ARRAY_SIZE];
	u32 t_threshold;
	bool enable_dte_by_शेष;
पूर्ण;

काष्ठा si_घड़ी_रेजिस्टरs अणु
	u32 cg_spll_func_cntl;
	u32 cg_spll_func_cntl_2;
	u32 cg_spll_func_cntl_3;
	u32 cg_spll_func_cntl_4;
	u32 cg_spll_spपढ़ो_spectrum;
	u32 cg_spll_spपढ़ो_spectrum_2;
	u32 dll_cntl;
	u32 mclk_pwrmgt_cntl;
	u32 mpll_ad_func_cntl;
	u32 mpll_dq_func_cntl;
	u32 mpll_func_cntl;
	u32 mpll_func_cntl_1;
	u32 mpll_func_cntl_2;
	u32 mpll_ss1;
	u32 mpll_ss2;
पूर्ण;

काष्ठा si_mc_reg_entry अणु
	u32 mclk_max;
	u32 mc_data[SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा si_mc_reg_table अणु
	u8 last;
	u8 num_entries;
	u16 valid_flag;
	काष्ठा si_mc_reg_entry mc_reg_table_entry[MAX_AC_TIMING_ENTRIES];
	SMC_NIslands_MCRegisterAddress mc_reg_address[SMC_SISLANDS_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा si_leakage_voltage_entry
अणु
	u16 voltage;
	u16 leakage_index;
पूर्ण;

काष्ठा si_leakage_voltage
अणु
	u16 count;
	काष्ठा si_leakage_voltage_entry entries[SISLANDS_MAX_LEAKAGE_COUNT];
पूर्ण;


काष्ठा si_ulv_param अणु
	bool supported;
	u32 cg_ulv_control;
	u32 cg_ulv_parameter;
	u32 volt_change_delay;
	काष्ठा rv7xx_pl pl;
	bool one_pcie_lane_in_ulv;
पूर्ण;

काष्ठा si_घातer_info अणु
	/* must be first! */
	काष्ठा ni_घातer_info ni;
	काष्ठा si_घड़ी_रेजिस्टरs घड़ी_रेजिस्टरs;
	काष्ठा si_mc_reg_table mc_reg_table;
	काष्ठा atom_voltage_table mvdd_voltage_table;
	काष्ठा atom_voltage_table vddc_phase_shed_table;
	काष्ठा si_leakage_voltage leakage_voltage;
	u16 mvdd_bootup_value;
	काष्ठा si_ulv_param ulv;
	u32 max_cu;
	/* pcie gen */
	क्रमागत amdgpu_pcie_gen क्रमce_pcie_gen;
	क्रमागत amdgpu_pcie_gen boot_pcie_gen;
	क्रमागत amdgpu_pcie_gen acpi_pcie_gen;
	u32 sys_pcie_mask;
	/* flags */
	bool enable_dte;
	bool enable_ppm;
	bool vddc_phase_shed_control;
	bool pspp_notअगरy_required;
	bool sclk_deep_sleep_above_low;
	bool voltage_control_svi2;
	bool vddci_control_svi2;
	/* smc offsets */
	u32 sram_end;
	u32 state_table_start;
	u32 soft_regs_start;
	u32 mc_reg_table_start;
	u32 arb_table_start;
	u32 cac_table_start;
	u32 dte_table_start;
	u32 spll_table_start;
	u32 papm_cfg_table_start;
	u32 fan_table_start;
	/* CAC stuff */
	स्थिर काष्ठा si_cac_config_reg *cac_weights;
	स्थिर काष्ठा si_cac_config_reg *lcac_config;
	स्थिर काष्ठा si_cac_config_reg *cac_override;
	स्थिर काष्ठा si_घातertune_data *घातertune_data;
	काष्ठा si_dyn_घातertune_data dyn_घातertune_data;
	/* DTE stuff */
	काष्ठा si_dte_data dte_data;
	/* scratch काष्ठाs */
	SMC_SIslands_MCRegisters smc_mc_reg_table;
	SISLANDS_SMC_STATETABLE smc_statetable;
	PP_SIslands_PAPMParameters papm_parm;
	/* SVI2 */
	u8 svd_gpio_id;
	u8 svc_gpio_id;
	/* fan control */
	bool fan_ctrl_is_in_शेष_mode;
	u32 t_min;
	u32 fan_ctrl_शेष_mode;
	bool fan_is_controlled_by_smc;
पूर्ण;

#पूर्ण_अगर
