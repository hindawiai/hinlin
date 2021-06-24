<शैली गुरु>
/*
 * Copyright 2011 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __RV770_SMC_H__
#घोषणा __RV770_SMC_H__

#समावेश "ppsmc.h"

#आशय pack(push, 1)

#घोषणा RV770_SMC_TABLE_ADDRESS 0xB000

#घोषणा RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE    3

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

#घोषणा SMC_STROBE_RATIO    0x0F
#घोषणा SMC_STROBE_ENABLE   0x10

#घोषणा SMC_MC_EDC_RD_FLAG  0x01
#घोषणा SMC_MC_EDC_WR_FLAG  0x02
#घोषणा SMC_MC_RTT_ENABLE   0x04
#घोषणा SMC_MC_STUTTER_EN   0x08

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

#घोषणा RV770_SMC_VOLTAGEMASK_VDDC 0
#घोषणा RV770_SMC_VOLTAGEMASK_MVDD 1
#घोषणा RV770_SMC_VOLTAGEMASK_VDDCI 2
#घोषणा RV770_SMC_VOLTAGEMASK_MAX  4

काष्ठा RV770_SMC_VOLTAGEMASKTABLE
अणु
    uपूर्णांक8_t  highMask[RV770_SMC_VOLTAGEMASK_MAX];
    uपूर्णांक32_t lowMask[RV770_SMC_VOLTAGEMASK_MAX];
पूर्ण;

प्रकार काष्ठा RV770_SMC_VOLTAGEMASKTABLE RV770_SMC_VOLTAGEMASKTABLE;

#घोषणा MAX_NO_VREG_STEPS 32

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

#घोषणा PPSMC_STATEFLAG_AUTO_PULSE_SKIP 0x01

#आशय pack(pop)

#घोषणा RV770_SMC_SOFT_REGISTERS_START        0x104

#घोषणा RV770_SMC_SOFT_REGISTER_mclk_chg_समयout        0x0
#घोषणा RV770_SMC_SOFT_REGISTER_baby_step_समयr         0x8
#घोषणा RV770_SMC_SOFT_REGISTER_delay_bbias             0xC
#घोषणा RV770_SMC_SOFT_REGISTER_delay_vreg              0x10
#घोषणा RV770_SMC_SOFT_REGISTER_delay_acpi              0x2C
#घोषणा RV770_SMC_SOFT_REGISTER_seq_index               0x64
#घोषणा RV770_SMC_SOFT_REGISTER_mvdd_chg_समय           0x68
#घोषणा RV770_SMC_SOFT_REGISTER_mclk_चयन_lim         0x78
#घोषणा RV770_SMC_SOFT_REGISTER_mc_block_delay          0x90
#घोषणा RV770_SMC_SOFT_REGISTER_uvd_enabled             0x9C
#घोषणा RV770_SMC_SOFT_REGISTER_is_asic_lombok          0xA0

पूर्णांक rv770_copy_bytes_to_smc(काष्ठा radeon_device *rdev,
			    u16 smc_start_address, स्थिर u8 *src,
			    u16 byte_count, u16 limit);
व्योम rv770_start_smc(काष्ठा radeon_device *rdev);
व्योम rv770_reset_smc(काष्ठा radeon_device *rdev);
व्योम rv770_stop_smc_घड़ी(काष्ठा radeon_device *rdev);
व्योम rv770_start_smc_घड़ी(काष्ठा radeon_device *rdev);
bool rv770_is_smc_running(काष्ठा radeon_device *rdev);
PPSMC_Result rv770_send_msg_to_smc(काष्ठा radeon_device *rdev, PPSMC_Msg msg);
PPSMC_Result rv770_रुको_क्रम_smc_inactive(काष्ठा radeon_device *rdev);
पूर्णांक rv770_पढ़ो_smc_sram_dword(काष्ठा radeon_device *rdev,
			      u16 smc_address, u32 *value, u16 limit);
पूर्णांक rv770_ग_लिखो_smc_sram_dword(काष्ठा radeon_device *rdev,
			       u16 smc_address, u32 value, u16 limit);
पूर्णांक rv770_load_smc_ucode(काष्ठा radeon_device *rdev,
			 u16 limit);

#पूर्ण_अगर
