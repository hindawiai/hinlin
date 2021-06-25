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
#अगर_अघोषित PP_SMC_H
#घोषणा PP_SMC_H

#आशय pack(push, 1)

#घोषणा PPSMC_SWSTATE_FLAG_DC                           0x01
#घोषणा PPSMC_SWSTATE_FLAG_UVD                          0x02
#घोषणा PPSMC_SWSTATE_FLAG_VCE                          0x04
#घोषणा PPSMC_SWSTATE_FLAG_PCIE_X1                      0x08

#घोषणा PPSMC_THERMAL_PROTECT_TYPE_INTERNAL             0x00
#घोषणा PPSMC_THERMAL_PROTECT_TYPE_EXTERNAL             0x01
#घोषणा PPSMC_THERMAL_PROTECT_TYPE_NONE                 0xff

#घोषणा PPSMC_SYSTEMFLAG_GPIO_DC                        0x01
#घोषणा PPSMC_SYSTEMFLAG_STEPVDDC                       0x02
#घोषणा PPSMC_SYSTEMFLAG_GDDR5                          0x04
#घोषणा PPSMC_SYSTEMFLAG_DISABLE_BABYSTEP               0x08
#घोषणा PPSMC_SYSTEMFLAG_REGULATOR_HOT                  0x10
#घोषणा PPSMC_SYSTEMFLAG_REGULATOR_HOT_ANALOG           0x20
#घोषणा PPSMC_SYSTEMFLAG_REGULATOR_HOT_PROG_GPIO        0x40

#घोषणा PPSMC_EXTRAFLAGS_AC2DC_ACTION_MASK              0x07
#घोषणा PPSMC_EXTRAFLAGS_AC2DC_DONT_WAIT_FOR_VBLANK     0x08
#घोषणा PPSMC_EXTRAFLAGS_AC2DC_ACTION_GOTODPMLOWSTATE   0x00
#घोषणा PPSMC_EXTRAFLAGS_AC2DC_ACTION_GOTOINITIALSTATE  0x01
#घोषणा PPSMC_EXTRAFLAGS_AC2DC_GPIO5_POLARITY_HIGH      0x02

#घोषणा PPSMC_DISPLAY_WATERMARK_LOW                     0
#घोषणा PPSMC_DISPLAY_WATERMARK_HIGH                    1

#घोषणा PPSMC_STATEFLAG_AUTO_PULSE_SKIP    0x01
#घोषणा PPSMC_STATEFLAG_POWERBOOST         0x02
#घोषणा PPSMC_STATEFLAG_DEEPSLEEP_THROTTLE 0x20
#घोषणा PPSMC_STATEFLAG_DEEPSLEEP_BYPASS   0x40

#घोषणा FDO_MODE_HARDWARE 0
#घोषणा FDO_MODE_PIECE_WISE_LINEAR 1

क्रमागत FAN_CONTROL अणु
	FAN_CONTROL_FUZZY,
	FAN_CONTROL_TABLE
पूर्ण;

#घोषणा PPSMC_Result_OK             ((uपूर्णांक8_t)0x01)
#घोषणा PPSMC_Result_Failed         ((uपूर्णांक8_t)0xFF)

प्रकार uपूर्णांक8_t PPSMC_Result;

#घोषणा PPSMC_MSG_Halt                      ((uपूर्णांक8_t)0x10)
#घोषणा PPSMC_MSG_Resume                    ((uपूर्णांक8_t)0x11)
#घोषणा PPSMC_MSG_ZeroLevelsDisabled        ((uपूर्णांक8_t)0x13)
#घोषणा PPSMC_MSG_OneLevelsDisabled         ((uपूर्णांक8_t)0x14)
#घोषणा PPSMC_MSG_TwoLevelsDisabled         ((uपूर्णांक8_t)0x15)
#घोषणा PPSMC_MSG_EnableThermalInterrupt    ((uपूर्णांक8_t)0x16)
#घोषणा PPSMC_MSG_RunningOnAC               ((uपूर्णांक8_t)0x17)
#घोषणा PPSMC_MSG_SwitchToSwState           ((uपूर्णांक8_t)0x20)
#घोषणा PPSMC_MSG_SwitchToInitialState      ((uपूर्णांक8_t)0x40)
#घोषणा PPSMC_MSG_NoForcedLevel             ((uपूर्णांक8_t)0x41)
#घोषणा PPSMC_MSG_ForceHigh                 ((uपूर्णांक8_t)0x42)
#घोषणा PPSMC_MSG_ForceMediumOrHigh         ((uपूर्णांक8_t)0x43)
#घोषणा PPSMC_MSG_SwitchToMinimumPower      ((uपूर्णांक8_t)0x51)
#घोषणा PPSMC_MSG_ResumeFromMinimumPower    ((uपूर्णांक8_t)0x52)
#घोषणा PPSMC_MSG_EnableCac                 ((uपूर्णांक8_t)0x53)
#घोषणा PPSMC_MSG_DisableCac                ((uपूर्णांक8_t)0x54)
#घोषणा PPSMC_TDPClampingActive             ((uपूर्णांक8_t)0x59)
#घोषणा PPSMC_TDPClampingInactive           ((uपूर्णांक8_t)0x5A)
#घोषणा PPSMC_StartFanControl               ((uपूर्णांक8_t)0x5B)
#घोषणा PPSMC_StopFanControl                ((uपूर्णांक8_t)0x5C)
#घोषणा PPSMC_MSG_NoDisplay                 ((uपूर्णांक8_t)0x5D)
#घोषणा PPSMC_NoDisplay                     ((uपूर्णांक8_t)0x5D)
#घोषणा PPSMC_MSG_HasDisplay                ((uपूर्णांक8_t)0x5E)
#घोषणा PPSMC_HasDisplay                    ((uपूर्णांक8_t)0x5E)
#घोषणा PPSMC_MSG_UVDPowerOFF               ((uपूर्णांक8_t)0x60)
#घोषणा PPSMC_MSG_UVDPowerON                ((uपूर्णांक8_t)0x61)
#घोषणा PPSMC_MSG_EnableULV                 ((uपूर्णांक8_t)0x62)
#घोषणा PPSMC_MSG_DisableULV                ((uपूर्णांक8_t)0x63)
#घोषणा PPSMC_MSG_EnterULV                  ((uपूर्णांक8_t)0x64)
#घोषणा PPSMC_MSG_ExitULV                   ((uपूर्णांक8_t)0x65)
#घोषणा PPSMC_CACLongTermAvgEnable          ((uपूर्णांक8_t)0x6E)
#घोषणा PPSMC_CACLongTermAvgDisable         ((uपूर्णांक8_t)0x6F)
#घोषणा PPSMC_MSG_CollectCAC_PowerCorreln   ((uपूर्णांक8_t)0x7A)
#घोषणा PPSMC_FlushDataCache                ((uपूर्णांक8_t)0x80)
#घोषणा PPSMC_MSG_SetEnabledLevels          ((uपूर्णांक8_t)0x82)
#घोषणा PPSMC_MSG_SetForcedLevels           ((uपूर्णांक8_t)0x83)
#घोषणा PPSMC_MSG_ResetToDefaults           ((uपूर्णांक8_t)0x84)
#घोषणा PPSMC_MSG_EnableDTE                 ((uपूर्णांक8_t)0x87)
#घोषणा PPSMC_MSG_DisableDTE                ((uपूर्णांक8_t)0x88)
#घोषणा PPSMC_MSG_ThrottleOVRDSCLKDS        ((uपूर्णांक8_t)0x96)
#घोषणा PPSMC_MSG_CancelThrottleOVRDSCLKDS  ((uपूर्णांक8_t)0x97)
#घोषणा PPSMC_MSG_EnableACDCGPIOInterrupt   ((uपूर्णांक16_t) 0x149)

/* CI/KV/KB */
#घोषणा PPSMC_MSG_UVDDPM_SetEnabledMask       ((uपूर्णांक16_t) 0x12D)
#घोषणा PPSMC_MSG_VCEDPM_SetEnabledMask       ((uपूर्णांक16_t) 0x12E)
#घोषणा PPSMC_MSG_ACPDPM_SetEnabledMask       ((uपूर्णांक16_t) 0x12F)
#घोषणा PPSMC_MSG_SAMUDPM_SetEnabledMask      ((uपूर्णांक16_t) 0x130)
#घोषणा PPSMC_MSG_MCLKDPM_ForceState          ((uपूर्णांक16_t) 0x131)
#घोषणा PPSMC_MSG_MCLKDPM_NoForcedLevel       ((uपूर्णांक16_t) 0x132)
#घोषणा PPSMC_MSG_Thermal_Cntl_Disable        ((uपूर्णांक16_t) 0x133)
#घोषणा PPSMC_MSG_Voltage_Cntl_Disable        ((uपूर्णांक16_t) 0x135)
#घोषणा PPSMC_MSG_PCIeDPM_Enable              ((uपूर्णांक16_t) 0x136)
#घोषणा PPSMC_MSG_PCIeDPM_Disable             ((uपूर्णांक16_t) 0x13d)
#घोषणा PPSMC_MSG_ACPPowerOFF                 ((uपूर्णांक16_t) 0x137)
#घोषणा PPSMC_MSG_ACPPowerON                  ((uपूर्णांक16_t) 0x138)
#घोषणा PPSMC_MSG_SAMPowerOFF                 ((uपूर्णांक16_t) 0x139)
#घोषणा PPSMC_MSG_SAMPowerON                  ((uपूर्णांक16_t) 0x13a)
#घोषणा PPSMC_MSG_PCIeDPM_Disable             ((uपूर्णांक16_t) 0x13d)
#घोषणा PPSMC_MSG_NBDPM_Enable                ((uपूर्णांक16_t) 0x140)
#घोषणा PPSMC_MSG_NBDPM_Disable               ((uपूर्णांक16_t) 0x141)
#घोषणा PPSMC_MSG_SCLKDPM_SetEnabledMask      ((uपूर्णांक16_t) 0x145)
#घोषणा PPSMC_MSG_MCLKDPM_SetEnabledMask      ((uपूर्णांक16_t) 0x146)
#घोषणा PPSMC_MSG_PCIeDPM_ForceLevel          ((uपूर्णांक16_t) 0x147)
#घोषणा PPSMC_MSG_PCIeDPM_UnForceLevel        ((uपूर्णांक16_t) 0x148)
#घोषणा PPSMC_MSG_EnableVRHotGPIOInterrupt    ((uपूर्णांक16_t) 0x14a)
#घोषणा PPSMC_MSG_DPM_Enable                  ((uपूर्णांक16_t) 0x14e)
#घोषणा PPSMC_MSG_DPM_Disable                 ((uपूर्णांक16_t) 0x14f)
#घोषणा PPSMC_MSG_MCLKDPM_Enable              ((uपूर्णांक16_t) 0x150)
#घोषणा PPSMC_MSG_MCLKDPM_Disable             ((uपूर्णांक16_t) 0x151)
#घोषणा PPSMC_MSG_UVDDPM_Enable               ((uपूर्णांक16_t) 0x154)
#घोषणा PPSMC_MSG_UVDDPM_Disable              ((uपूर्णांक16_t) 0x155)
#घोषणा PPSMC_MSG_SAMUDPM_Enable              ((uपूर्णांक16_t) 0x156)
#घोषणा PPSMC_MSG_SAMUDPM_Disable             ((uपूर्णांक16_t) 0x157)
#घोषणा PPSMC_MSG_ACPDPM_Enable               ((uपूर्णांक16_t) 0x158)
#घोषणा PPSMC_MSG_ACPDPM_Disable              ((uपूर्णांक16_t) 0x159)
#घोषणा PPSMC_MSG_VCEDPM_Enable               ((uपूर्णांक16_t) 0x15a)
#घोषणा PPSMC_MSG_VCEDPM_Disable              ((uपूर्णांक16_t) 0x15b)
#घोषणा PPSMC_MSG_VddC_Request                ((uपूर्णांक16_t) 0x15f)
#घोषणा PPSMC_MSG_SCLKDPM_GetEnabledMask      ((uपूर्णांक16_t) 0x162)
#घोषणा PPSMC_MSG_PCIeDPM_SetEnabledMask      ((uपूर्णांक16_t) 0x167)
#घोषणा PPSMC_MSG_TDCLimitEnable              ((uपूर्णांक16_t) 0x169)
#घोषणा PPSMC_MSG_TDCLimitDisable             ((uपूर्णांक16_t) 0x16a)
#घोषणा PPSMC_MSG_PkgPwrLimitEnable           ((uपूर्णांक16_t) 0x185)
#घोषणा PPSMC_MSG_PkgPwrLimitDisable          ((uपूर्णांक16_t) 0x186)
#घोषणा PPSMC_MSG_PkgPwrSetLimit              ((uपूर्णांक16_t) 0x187)
#घोषणा PPSMC_MSG_OverDriveSetTargetTdp       ((uपूर्णांक16_t) 0x188)
#घोषणा PPSMC_MSG_SCLKDPM_FreezeLevel         ((uपूर्णांक16_t) 0x189)
#घोषणा PPSMC_MSG_SCLKDPM_Unमुक्तzeLevel       ((uपूर्णांक16_t) 0x18A)
#घोषणा PPSMC_MSG_MCLKDPM_FreezeLevel         ((uपूर्णांक16_t) 0x18B)
#घोषणा PPSMC_MSG_MCLKDPM_Unमुक्तzeLevel       ((uपूर्णांक16_t) 0x18C)
#घोषणा PPSMC_MSG_MASTER_DeepSleep_ON         ((uपूर्णांक16_t) 0x18F)
#घोषणा PPSMC_MSG_MASTER_DeepSleep_OFF        ((uपूर्णांक16_t) 0x190)
#घोषणा PPSMC_MSG_Remove_DC_Clamp             ((uपूर्णांक16_t) 0x191)
#घोषणा PPSMC_MSG_SetFanPwmMax                ((uपूर्णांक16_t) 0x19A)
#घोषणा PPSMC_MSG_SetFanRpmMax                ((uपूर्णांक16_t) 0x205)

#घोषणा PPSMC_MSG_ENABLE_THERMAL_DPM          ((uपूर्णांक16_t) 0x19C)
#घोषणा PPSMC_MSG_DISABLE_THERMAL_DPM         ((uपूर्णांक16_t) 0x19D)

#घोषणा PPSMC_MSG_API_GetSclkFrequency        ((uपूर्णांक16_t) 0x200)
#घोषणा PPSMC_MSG_API_GetMclkFrequency        ((uपूर्णांक16_t) 0x201)

/* TN */
#घोषणा PPSMC_MSG_DPM_Config                ((uपूर्णांक32_t) 0x102)
#घोषणा PPSMC_MSG_DPM_ForceState            ((uपूर्णांक32_t) 0x104)
#घोषणा PPSMC_MSG_PG_SIMD_Config            ((uपूर्णांक32_t) 0x108)
#घोषणा PPSMC_MSG_Voltage_Cntl_Enable       ((uपूर्णांक32_t) 0x109)
#घोषणा PPSMC_MSG_Thermal_Cntl_Enable       ((uपूर्णांक32_t) 0x10a)
#घोषणा PPSMC_MSG_VCEPowerOFF               ((uपूर्णांक32_t) 0x10e)
#घोषणा PPSMC_MSG_VCEPowerON                ((uपूर्णांक32_t) 0x10f)
#घोषणा PPSMC_MSG_DPM_N_LevelsDisabled      ((uपूर्णांक32_t) 0x112)
#घोषणा PPSMC_MSG_DCE_RemoveVoltageAdjusपंचांगent   ((uपूर्णांक32_t) 0x11d)
#घोषणा PPSMC_MSG_DCE_AllowVoltageAdjusपंचांगent    ((uपूर्णांक32_t) 0x11e)
#घोषणा PPSMC_MSG_EnableBAPM                ((uपूर्णांक32_t) 0x120)
#घोषणा PPSMC_MSG_DisableBAPM               ((uपूर्णांक32_t) 0x121)
#घोषणा PPSMC_MSG_UVD_DPM_Config            ((uपूर्णांक32_t) 0x124)

#घोषणा PPSMC_MSG_DRV_DRAM_ADDR_HI            ((uपूर्णांक16_t) 0x250)
#घोषणा PPSMC_MSG_DRV_DRAM_ADDR_LO            ((uपूर्णांक16_t) 0x251)
#घोषणा PPSMC_MSG_SMU_DRAM_ADDR_HI            ((uपूर्णांक16_t) 0x252)
#घोषणा PPSMC_MSG_SMU_DRAM_ADDR_LO            ((uपूर्णांक16_t) 0x253)
#घोषणा PPSMC_MSG_LoadUcodes                  ((uपूर्णांक16_t) 0x254)

प्रकार uपूर्णांक16_t PPSMC_Msg;

#आशय pack(pop)

#पूर्ण_अगर
