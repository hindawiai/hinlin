<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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

#अगर_अघोषित TONGA_PP_SMC_H
#घोषणा TONGA_PP_SMC_H

#आशय pack(push, 1)

#घोषणा PPSMC_SWSTATE_FLAG_DC				0x01
#घोषणा PPSMC_SWSTATE_FLAG_UVD				0x02
#घोषणा PPSMC_SWSTATE_FLAG_VCE				0x04
#घोषणा PPSMC_SWSTATE_FLAG_PCIE_X1			0x08

#घोषणा PPSMC_THERMAL_PROTECT_TYPE_INTERNAL             0x00
#घोषणा PPSMC_THERMAL_PROTECT_TYPE_EXTERNAL             0x01
#घोषणा PPSMC_THERMAL_PROTECT_TYPE_NONE                 0xff

#घोषणा PPSMC_SYSTEMFLAG_GPIO_DC                        0x01
#घोषणा PPSMC_SYSTEMFLAG_STEPVDDC                       0x02
#घोषणा PPSMC_SYSTEMFLAG_GDDR5                          0x04

#घोषणा PPSMC_SYSTEMFLAG_DISABLE_BABYSTEP               0x08

#घोषणा PPSMC_SYSTEMFLAG_REGULATOR_HOT                  0x10
#घोषणा PPSMC_SYSTEMFLAG_REGULATOR_HOT_ANALOG           0x20
#घोषणा PPSMC_SYSTEMFLAG_12CHANNEL                      0x40


#घोषणा PPSMC_EXTRAFLAGS_AC2DC_ACTION_MASK              0x07
#घोषणा PPSMC_EXTRAFLAGS_AC2DC_DONT_WAIT_FOR_VBLANK     0x08

#घोषणा PPSMC_EXTRAFLAGS_AC2DC_ACTION_GOTODPMLOWSTATE   0x00
#घोषणा PPSMC_EXTRAFLAGS_AC2DC_ACTION_GOTOINITIALSTATE  0x01

#घोषणा PPSMC_EXTRAFLAGS_AC2DC_GPIO5_POLARITY_HIGH      0x10
#घोषणा PPSMC_EXTRAFLAGS_DRIVER_TO_GPIO17               0x20
#घोषणा PPSMC_EXTRAFLAGS_PCC_TO_GPIO17                  0x40

/* Defines क्रम DPM 2.0 */
#घोषणा PPSMC_DPM2FLAGS_TDPCLMP                         0x01
#घोषणा PPSMC_DPM2FLAGS_PWRSHFT                         0x02
#घोषणा PPSMC_DPM2FLAGS_OCP                             0x04

/* Defines क्रम display watermark level */

#घोषणा PPSMC_DISPLAY_WATERMARK_LOW                     0
#घोषणा PPSMC_DISPLAY_WATERMARK_HIGH                    1

/* In the HW perक्रमmance level's state flags:*/
#घोषणा PPSMC_STATEFLAG_AUTO_PULSE_SKIP    0x01
#घोषणा PPSMC_STATEFLAG_POWERBOOST         0x02
#घोषणा PPSMC_STATEFLAG_PSKIP_ON_TDP_FAULT 0x04
#घोषणा PPSMC_STATEFLAG_POWERSHIFT         0x08
#घोषणा PPSMC_STATEFLAG_SLOW_READ_MARGIN   0x10
#घोषणा PPSMC_STATEFLAG_DEEPSLEEP_THROTTLE 0x20
#घोषणा PPSMC_STATEFLAG_DEEPSLEEP_BYPASS   0x40

/* Fan control algorithm:*/
#घोषणा FDO_MODE_HARDWARE 0
#घोषणा FDO_MODE_PIECE_WISE_LINEAR 1

क्रमागत FAN_CONTROL अणु
	FAN_CONTROL_FUZZY,
	FAN_CONTROL_TABLE
पूर्ण;

/* Return codes क्रम driver to SMC communication.*/

#घोषणा PPSMC_Result_OK             ((uपूर्णांक16_t)0x01)
#घोषणा PPSMC_Result_NoMore         ((uपूर्णांक16_t)0x02)
#घोषणा PPSMC_Result_NotNow         ((uपूर्णांक16_t)0x03)

#घोषणा PPSMC_Result_Failed         ((uपूर्णांक16_t)0xFF)
#घोषणा PPSMC_Result_UnknownCmd     ((uपूर्णांक16_t)0xFE)
#घोषणा PPSMC_Result_UnknownVT      ((uपूर्णांक16_t)0xFD)

प्रकार uपूर्णांक16_t PPSMC_Result;

#घोषणा PPSMC_isERROR(x) ((uपूर्णांक16_t)0x80 & (x))


#घोषणा PPSMC_MSG_Halt                      ((uपूर्णांक16_t)0x10)
#घोषणा PPSMC_MSG_Resume                    ((uपूर्णांक16_t)0x11)
#घोषणा PPSMC_MSG_EnableDPMLevel            ((uपूर्णांक16_t)0x12)
#घोषणा PPSMC_MSG_ZeroLevelsDisabled        ((uपूर्णांक16_t)0x13)
#घोषणा PPSMC_MSG_OneLevelsDisabled         ((uपूर्णांक16_t)0x14)
#घोषणा PPSMC_MSG_TwoLevelsDisabled         ((uपूर्णांक16_t)0x15)
#घोषणा PPSMC_MSG_EnableThermalInterrupt    ((uपूर्णांक16_t)0x16)
#घोषणा PPSMC_MSG_RunningOnAC               ((uपूर्णांक16_t)0x17)
#घोषणा PPSMC_MSG_LevelUp                   ((uपूर्णांक16_t)0x18)
#घोषणा PPSMC_MSG_LevelDown                 ((uपूर्णांक16_t)0x19)
#घोषणा PPSMC_MSG_ResetDPMCounters          ((uपूर्णांक16_t)0x1a)
#घोषणा PPSMC_MSG_SwitchToSwState           ((uपूर्णांक16_t)0x20)

#घोषणा PPSMC_MSG_SwitchToSwStateLast       ((uपूर्णांक16_t)0x3f)
#घोषणा PPSMC_MSG_SwitchToInitialState      ((uपूर्णांक16_t)0x40)
#घोषणा PPSMC_MSG_NoForcedLevel             ((uपूर्णांक16_t)0x41)
#घोषणा PPSMC_MSG_ForceHigh                 ((uपूर्णांक16_t)0x42)
#घोषणा PPSMC_MSG_ForceMediumOrHigh         ((uपूर्णांक16_t)0x43)

#घोषणा PPSMC_MSG_SwitchToMinimumPower      ((uपूर्णांक16_t)0x51)
#घोषणा PPSMC_MSG_ResumeFromMinimumPower    ((uपूर्णांक16_t)0x52)
#घोषणा PPSMC_MSG_EnableCac                 ((uपूर्णांक16_t)0x53)
#घोषणा PPSMC_MSG_DisableCac                ((uपूर्णांक16_t)0x54)
#घोषणा PPSMC_DPMStateHistoryStart          ((uपूर्णांक16_t)0x55)
#घोषणा PPSMC_DPMStateHistoryStop           ((uपूर्णांक16_t)0x56)
#घोषणा PPSMC_CACHistoryStart               ((uपूर्णांक16_t)0x57)
#घोषणा PPSMC_CACHistoryStop                ((uपूर्णांक16_t)0x58)
#घोषणा PPSMC_TDPClampingActive             ((uपूर्णांक16_t)0x59)
#घोषणा PPSMC_TDPClampingInactive           ((uपूर्णांक16_t)0x5A)
#घोषणा PPSMC_StartFanControl               ((uपूर्णांक16_t)0x5B)
#घोषणा PPSMC_StopFanControl                ((uपूर्णांक16_t)0x5C)
#घोषणा PPSMC_NoDisplay                     ((uपूर्णांक16_t)0x5D)
#घोषणा PPSMC_HasDisplay                    ((uपूर्णांक16_t)0x5E)
#घोषणा PPSMC_MSG_UVDPowerOFF               ((uपूर्णांक16_t)0x60)
#घोषणा PPSMC_MSG_UVDPowerON                ((uपूर्णांक16_t)0x61)
#घोषणा PPSMC_MSG_EnableULV                 ((uपूर्णांक16_t)0x62)
#घोषणा PPSMC_MSG_DisableULV                ((uपूर्णांक16_t)0x63)
#घोषणा PPSMC_MSG_EnterULV                  ((uपूर्णांक16_t)0x64)
#घोषणा PPSMC_MSG_ExitULV                   ((uपूर्णांक16_t)0x65)
#घोषणा PPSMC_PowerShअगरtActive              ((uपूर्णांक16_t)0x6A)
#घोषणा PPSMC_PowerShअगरtInactive            ((uपूर्णांक16_t)0x6B)
#घोषणा PPSMC_OCPActive                     ((uपूर्णांक16_t)0x6C)
#घोषणा PPSMC_OCPInactive                   ((uपूर्णांक16_t)0x6D)
#घोषणा PPSMC_CACLongTermAvgEnable          ((uपूर्णांक16_t)0x6E)
#घोषणा PPSMC_CACLongTermAvgDisable         ((uपूर्णांक16_t)0x6F)
#घोषणा PPSMC_MSG_InferredStateSweep_Start  ((uपूर्णांक16_t)0x70)
#घोषणा PPSMC_MSG_InferredStateSweep_Stop   ((uपूर्णांक16_t)0x71)
#घोषणा PPSMC_MSG_SwitchToLowestInfState    ((uपूर्णांक16_t)0x72)
#घोषणा PPSMC_MSG_SwitchToNonInfState       ((uपूर्णांक16_t)0x73)
#घोषणा PPSMC_MSG_AllStateSweep_Start       ((uपूर्णांक16_t)0x74)
#घोषणा PPSMC_MSG_AllStateSweep_Stop        ((uपूर्णांक16_t)0x75)
#घोषणा PPSMC_MSG_SwitchNextLowerInfState   ((uपूर्णांक16_t)0x76)
#घोषणा PPSMC_MSG_SwitchNextHigherInfState  ((uपूर्णांक16_t)0x77)
#घोषणा PPSMC_MSG_MclkRetrainingTest        ((uपूर्णांक16_t)0x78)
#घोषणा PPSMC_MSG_ForceTDPClamping          ((uपूर्णांक16_t)0x79)
#घोषणा PPSMC_MSG_CollectCAC_PowerCorreln   ((uपूर्णांक16_t)0x7A)
#घोषणा PPSMC_MSG_CollectCAC_WeightCalib    ((uपूर्णांक16_t)0x7B)
#घोषणा PPSMC_MSG_CollectCAC_SQonly         ((uपूर्णांक16_t)0x7C)
#घोषणा PPSMC_MSG_CollectCAC_TemperaturePwr ((uपूर्णांक16_t)0x7D)

#घोषणा PPSMC_MSG_ExtremitiesTest_Start     ((uपूर्णांक16_t)0x7E)
#घोषणा PPSMC_MSG_ExtremitiesTest_Stop      ((uपूर्णांक16_t)0x7F)
#घोषणा PPSMC_FlushDataCache                ((uपूर्णांक16_t)0x80)
#घोषणा PPSMC_FlushInstrCache               ((uपूर्णांक16_t)0x81)

#घोषणा PPSMC_MSG_SetEnabledLevels          ((uपूर्णांक16_t)0x82)
#घोषणा PPSMC_MSG_SetForcedLevels           ((uपूर्णांक16_t)0x83)

#घोषणा PPSMC_MSG_ResetToDefaults           ((uपूर्णांक16_t)0x84)

#घोषणा PPSMC_MSG_SetForcedLevelsAndJump    ((uपूर्णांक16_t)0x85)
#घोषणा PPSMC_MSG_SetCACHistoryMode         ((uपूर्णांक16_t)0x86)
#घोषणा PPSMC_MSG_EnableDTE                 ((uपूर्णांक16_t)0x87)
#घोषणा PPSMC_MSG_DisableDTE                ((uपूर्णांक16_t)0x88)

#घोषणा PPSMC_MSG_SmcSpaceSetAddress        ((uपूर्णांक16_t)0x89)
#घोषणा PPSMC_MSG_ChangeNearTDPLimit        ((uपूर्णांक16_t)0x90)
#घोषणा PPSMC_MSG_ChangeSafePowerLimit      ((uपूर्णांक16_t)0x91)

#घोषणा PPSMC_MSG_DPMStateSweepStart        ((uपूर्णांक16_t)0x92)
#घोषणा PPSMC_MSG_DPMStateSweepStop         ((uपूर्णांक16_t)0x93)

#घोषणा PPSMC_MSG_OVRDDisableSCLKDS         ((uपूर्णांक16_t)0x94)
#घोषणा PPSMC_MSG_CancelDisableOVRDSCLKDS   ((uपूर्णांक16_t)0x95)
#घोषणा PPSMC_MSG_ThrottleOVRDSCLKDS        ((uपूर्णांक16_t)0x96)
#घोषणा PPSMC_MSG_CancelThrottleOVRDSCLKDS  ((uपूर्णांक16_t)0x97)
#घोषणा PPSMC_MSG_GPIO17					((uपूर्णांक16_t)0x98)

#घोषणा PPSMC_MSG_API_SetSvi2Volt_Vddc      ((uपूर्णांक16_t)0x99)
#घोषणा PPSMC_MSG_API_SetSvi2Volt_Vddci     ((uपूर्णांक16_t)0x9A)
#घोषणा PPSMC_MSG_API_SetSvi2Volt_Mvdd      ((uपूर्णांक16_t)0x9B)
#घोषणा PPSMC_MSG_API_GetSvi2Volt_Vddc      ((uपूर्णांक16_t)0x9C)
#घोषणा PPSMC_MSG_API_GetSvi2Volt_Vddci     ((uपूर्णांक16_t)0x9D)
#घोषणा PPSMC_MSG_API_GetSvi2Volt_Mvdd      ((uपूर्णांक16_t)0x9E)

#घोषणा PPSMC_MSG_BREAK                     ((uपूर्णांक16_t)0xF8)

/* Trinity Specअगरic Messages*/
#घोषणा PPSMC_MSG_Test                      ((uपूर्णांक16_t) 0x100)
#घोषणा PPSMC_MSG_DPM_Voltage_Pwrmgt        ((uपूर्णांक16_t) 0x101)
#घोषणा PPSMC_MSG_DPM_Config                ((uपूर्णांक16_t) 0x102)
#घोषणा PPSMC_MSG_PM_Controller_Start       ((uपूर्णांक16_t) 0x103)
#घोषणा PPSMC_MSG_DPM_ForceState            ((uपूर्णांक16_t) 0x104)
#घोषणा PPSMC_MSG_PG_PowerDownSIMD          ((uपूर्णांक16_t) 0x105)
#घोषणा PPSMC_MSG_PG_PowerUpSIMD            ((uपूर्णांक16_t) 0x106)
#घोषणा PPSMC_MSG_PM_Controller_Stop        ((uपूर्णांक16_t) 0x107)
#घोषणा PPSMC_MSG_PG_SIMD_Config            ((uपूर्णांक16_t) 0x108)
#घोषणा PPSMC_MSG_Voltage_Cntl_Enable       ((uपूर्णांक16_t) 0x109)
#घोषणा PPSMC_MSG_Thermal_Cntl_Enable       ((uपूर्णांक16_t) 0x10a)
#घोषणा PPSMC_MSG_Reset_Service             ((uपूर्णांक16_t) 0x10b)
#घोषणा PPSMC_MSG_VCEPowerOFF               ((uपूर्णांक16_t) 0x10e)
#घोषणा PPSMC_MSG_VCEPowerON                ((uपूर्णांक16_t) 0x10f)
#घोषणा PPSMC_MSG_DPM_Disable_VCE_HS        ((uपूर्णांक16_t) 0x110)
#घोषणा PPSMC_MSG_DPM_Enable_VCE_HS         ((uपूर्णांक16_t) 0x111)
#घोषणा PPSMC_MSG_DPM_N_LevelsDisabled      ((uपूर्णांक16_t) 0x112)
#घोषणा PPSMC_MSG_DCEPowerOFF               ((uपूर्णांक16_t) 0x113)
#घोषणा PPSMC_MSG_DCEPowerON                ((uपूर्णांक16_t) 0x114)
#घोषणा PPSMC_MSG_PCIE_DDIPowerDown         ((uपूर्णांक16_t) 0x117)
#घोषणा PPSMC_MSG_PCIE_DDIPowerUp           ((uपूर्णांक16_t) 0x118)
#घोषणा PPSMC_MSG_PCIE_CascadePLLPowerDown  ((uपूर्णांक16_t) 0x119)
#घोषणा PPSMC_MSG_PCIE_CascadePLLPowerUp    ((uपूर्णांक16_t) 0x11a)
#घोषणा PPSMC_MSG_SYSPLLPowerOff            ((uपूर्णांक16_t) 0x11b)
#घोषणा PPSMC_MSG_SYSPLLPowerOn             ((uपूर्णांक16_t) 0x11c)
#घोषणा PPSMC_MSG_DCE_RemoveVoltageAdjusपंचांगent   ((uपूर्णांक16_t) 0x11d)
#घोषणा PPSMC_MSG_DCE_AllowVoltageAdjusपंचांगent    ((uपूर्णांक16_t) 0x11e)
#घोषणा PPSMC_MSG_DISPLAYPHYStatusNotअगरy    ((uपूर्णांक16_t) 0x11f)
#घोषणा PPSMC_MSG_EnableBAPM                ((uपूर्णांक16_t) 0x120)
#घोषणा PPSMC_MSG_DisableBAPM               ((uपूर्णांक16_t) 0x121)
#घोषणा PPSMC_MSG_PCIE_PHYPowerDown         ((uपूर्णांक16_t) 0x122)
#घोषणा PPSMC_MSG_PCIE_PHYPowerUp           ((uपूर्णांक16_t) 0x123)
#घोषणा PPSMC_MSG_UVD_DPM_Config            ((uपूर्णांक16_t) 0x124)
#घोषणा PPSMC_MSG_Spmi_Enable               ((uपूर्णांक16_t) 0x122)
#घोषणा PPSMC_MSG_Spmi_Timer                ((uपूर्णांक16_t) 0x123)
#घोषणा PPSMC_MSG_LCLK_DPM_Config           ((uपूर्णांक16_t) 0x124)
#घोषणा PPSMC_MSG_NBDPM_Config             ((uपूर्णांक16_t) 0x125)
#घोषणा PPSMC_MSG_PCIE_DDIPhyPowerDown           ((uपूर्णांक16_t) 0x126)
#घोषणा PPSMC_MSG_PCIE_DDIPhyPowerUp             ((uपूर्णांक16_t) 0x127)
#घोषणा PPSMC_MSG_MCLKDPM_Config                ((uपूर्णांक16_t) 0x128)

#घोषणा PPSMC_MSG_UVDDPM_Config               ((uपूर्णांक16_t) 0x129)
#घोषणा PPSMC_MSG_VCEDPM_Config               ((uपूर्णांक16_t) 0x12A)
#घोषणा PPSMC_MSG_ACPDPM_Config               ((uपूर्णांक16_t) 0x12B)
#घोषणा PPSMC_MSG_SAMUDPM_Config              ((uपूर्णांक16_t) 0x12C)
#घोषणा PPSMC_MSG_UVDDPM_SetEnabledMask       ((uपूर्णांक16_t) 0x12D)
#घोषणा PPSMC_MSG_VCEDPM_SetEnabledMask       ((uपूर्णांक16_t) 0x12E)
#घोषणा PPSMC_MSG_ACPDPM_SetEnabledMask       ((uपूर्णांक16_t) 0x12F)
#घोषणा PPSMC_MSG_SAMUDPM_SetEnabledMask      ((uपूर्णांक16_t) 0x130)
#घोषणा PPSMC_MSG_MCLKDPM_ForceState          ((uपूर्णांक16_t) 0x131)
#घोषणा PPSMC_MSG_MCLKDPM_NoForcedLevel       ((uपूर्णांक16_t) 0x132)
#घोषणा PPSMC_MSG_Thermal_Cntl_Disable        ((uपूर्णांक16_t) 0x133)
#घोषणा PPSMC_MSG_SetTDPLimit                 ((uपूर्णांक16_t) 0x134)
#घोषणा PPSMC_MSG_Voltage_Cntl_Disable        ((uपूर्णांक16_t) 0x135)
#घोषणा PPSMC_MSG_PCIeDPM_Enable              ((uपूर्णांक16_t) 0x136)
#घोषणा PPSMC_MSG_ACPPowerOFF                 ((uपूर्णांक16_t) 0x137)
#घोषणा PPSMC_MSG_ACPPowerON                  ((uपूर्णांक16_t) 0x138)
#घोषणा PPSMC_MSG_SAMPowerOFF                 ((uपूर्णांक16_t) 0x139)
#घोषणा PPSMC_MSG_SAMPowerON                  ((uपूर्णांक16_t) 0x13a)
#घोषणा PPSMC_MSG_SDMAPowerOFF                ((uपूर्णांक16_t) 0x13b)
#घोषणा PPSMC_MSG_SDMAPowerON                 ((uपूर्णांक16_t) 0x13c)
#घोषणा PPSMC_MSG_PCIeDPM_Disable             ((uपूर्णांक16_t) 0x13d)
#घोषणा PPSMC_MSG_IOMMUPowerOFF               ((uपूर्णांक16_t) 0x13e)
#घोषणा PPSMC_MSG_IOMMUPowerON                ((uपूर्णांक16_t) 0x13f)
#घोषणा PPSMC_MSG_NBDPM_Enable                ((uपूर्णांक16_t) 0x140)
#घोषणा PPSMC_MSG_NBDPM_Disable               ((uपूर्णांक16_t) 0x141)
#घोषणा PPSMC_MSG_NBDPM_ForceNominal          ((uपूर्णांक16_t) 0x142)
#घोषणा PPSMC_MSG_NBDPM_ForcePerक्रमmance      ((uपूर्णांक16_t) 0x143)
#घोषणा PPSMC_MSG_NBDPM_UnForce               ((uपूर्णांक16_t) 0x144)
#घोषणा PPSMC_MSG_SCLKDPM_SetEnabledMask      ((uपूर्णांक16_t) 0x145)
#घोषणा PPSMC_MSG_MCLKDPM_SetEnabledMask      ((uपूर्णांक16_t) 0x146)
#घोषणा PPSMC_MSG_PCIeDPM_ForceLevel          ((uपूर्णांक16_t) 0x147)
#घोषणा PPSMC_MSG_PCIeDPM_UnForceLevel        ((uपूर्णांक16_t) 0x148)
#घोषणा PPSMC_MSG_EnableACDCGPIOInterrupt     ((uपूर्णांक16_t) 0x149)
#घोषणा PPSMC_MSG_EnableVRHotGPIOInterrupt    ((uपूर्णांक16_t) 0x14a)
#घोषणा PPSMC_MSG_SwitchToAC                  ((uपूर्णांक16_t) 0x14b)

#घोषणा PPSMC_MSG_XDMAPowerOFF                ((uपूर्णांक16_t) 0x14c)
#घोषणा PPSMC_MSG_XDMAPowerON                 ((uपूर्णांक16_t) 0x14d)

#घोषणा PPSMC_MSG_DPM_Enable                  ((uपूर्णांक16_t)0x14e)
#घोषणा PPSMC_MSG_DPM_Disable                 ((uपूर्णांक16_t)0x14f)
#घोषणा PPSMC_MSG_MCLKDPM_Enable              ((uपूर्णांक16_t)0x150)
#घोषणा PPSMC_MSG_MCLKDPM_Disable             ((uपूर्णांक16_t)0x151)
#घोषणा PPSMC_MSG_LCLKDPM_Enable              ((uपूर्णांक16_t)0x152)
#घोषणा PPSMC_MSG_LCLKDPM_Disable             ((uपूर्णांक16_t)0x153)
#घोषणा PPSMC_MSG_UVDDPM_Enable               ((uपूर्णांक16_t)0x154)
#घोषणा PPSMC_MSG_UVDDPM_Disable              ((uपूर्णांक16_t)0x155)
#घोषणा PPSMC_MSG_SAMUDPM_Enable              ((uपूर्णांक16_t)0x156)
#घोषणा PPSMC_MSG_SAMUDPM_Disable             ((uपूर्णांक16_t)0x157)
#घोषणा PPSMC_MSG_ACPDPM_Enable               ((uपूर्णांक16_t)0x158)
#घोषणा PPSMC_MSG_ACPDPM_Disable              ((uपूर्णांक16_t)0x159)
#घोषणा PPSMC_MSG_VCEDPM_Enable               ((uपूर्णांक16_t)0x15a)
#घोषणा PPSMC_MSG_VCEDPM_Disable              ((uपूर्णांक16_t)0x15b)
#घोषणा PPSMC_MSG_LCLKDPM_SetEnabledMask      ((uपूर्णांक16_t)0x15c)

#घोषणा PPSMC_MSG_DPM_FPS_Mode                ((uपूर्णांक16_t) 0x15d)
#घोषणा PPSMC_MSG_DPM_Activity_Mode           ((uपूर्णांक16_t) 0x15e)
#घोषणा PPSMC_MSG_VddC_Request                ((uपूर्णांक16_t) 0x15f)
#घोषणा PPSMC_MSG_MCLKDPM_GetEnabledMask      ((uपूर्णांक16_t) 0x160)
#घोषणा PPSMC_MSG_LCLKDPM_GetEnabledMask      ((uपूर्णांक16_t) 0x161)
#घोषणा PPSMC_MSG_SCLKDPM_GetEnabledMask      ((uपूर्णांक16_t) 0x162)
#घोषणा PPSMC_MSG_UVDDPM_GetEnabledMask       ((uपूर्णांक16_t) 0x163)
#घोषणा PPSMC_MSG_SAMUDPM_GetEnabledMask      ((uपूर्णांक16_t) 0x164)
#घोषणा PPSMC_MSG_ACPDPM_GetEnabledMask       ((uपूर्णांक16_t) 0x165)
#घोषणा PPSMC_MSG_VCEDPM_GetEnabledMask       ((uपूर्णांक16_t) 0x166)
#घोषणा PPSMC_MSG_PCIeDPM_SetEnabledMask      ((uपूर्णांक16_t) 0x167)
#घोषणा PPSMC_MSG_PCIeDPM_GetEnabledMask      ((uपूर्णांक16_t) 0x168)
#घोषणा PPSMC_MSG_TDCLimitEnable              ((uपूर्णांक16_t) 0x169)
#घोषणा PPSMC_MSG_TDCLimitDisable             ((uपूर्णांक16_t) 0x16a)
#घोषणा PPSMC_MSG_DPM_AutoRotate_Mode         ((uपूर्णांक16_t) 0x16b)
#घोषणा PPSMC_MSG_DISPCLK_FROM_FCH            ((uपूर्णांक16_t)0x16c)
#घोषणा PPSMC_MSG_DISPCLK_FROM_DFS            ((uपूर्णांक16_t)0x16d)
#घोषणा PPSMC_MSG_DPREFCLK_FROM_FCH           ((uपूर्णांक16_t)0x16e)
#घोषणा PPSMC_MSG_DPREFCLK_FROM_DFS           ((uपूर्णांक16_t)0x16f)
#घोषणा PPSMC_MSG_PmStatusLogStart            ((uपूर्णांक16_t)0x170)
#घोषणा PPSMC_MSG_PmStatusLogSample           ((uपूर्णांक16_t)0x171)
#घोषणा PPSMC_MSG_SCLK_AutoDPM_ON             ((uपूर्णांक16_t) 0x172)
#घोषणा PPSMC_MSG_MCLK_AutoDPM_ON             ((uपूर्णांक16_t) 0x173)
#घोषणा PPSMC_MSG_LCLK_AutoDPM_ON             ((uपूर्णांक16_t) 0x174)
#घोषणा PPSMC_MSG_UVD_AutoDPM_ON              ((uपूर्णांक16_t) 0x175)
#घोषणा PPSMC_MSG_SAMU_AutoDPM_ON             ((uपूर्णांक16_t) 0x176)
#घोषणा PPSMC_MSG_ACP_AutoDPM_ON              ((uपूर्णांक16_t) 0x177)
#घोषणा PPSMC_MSG_VCE_AutoDPM_ON              ((uपूर्णांक16_t) 0x178)
#घोषणा PPSMC_MSG_PCIe_AutoDPM_ON             ((uपूर्णांक16_t) 0x179)
#घोषणा PPSMC_MSG_MASTER_AutoDPM_ON           ((uपूर्णांक16_t) 0x17a)
#घोषणा PPSMC_MSG_MASTER_AutoDPM_OFF          ((uपूर्णांक16_t) 0x17b)
#घोषणा PPSMC_MSG_DYNAMICDISPPHYPOWER         ((uपूर्णांक16_t) 0x17c)
#घोषणा PPSMC_MSG_CAC_COLLECTION_ON           ((uपूर्णांक16_t) 0x17d)
#घोषणा PPSMC_MSG_CAC_COLLECTION_OFF          ((uपूर्णांक16_t) 0x17e)
#घोषणा PPSMC_MSG_CAC_CORRELATION_ON          ((uपूर्णांक16_t) 0x17f)
#घोषणा PPSMC_MSG_CAC_CORRELATION_OFF         ((uपूर्णांक16_t) 0x180)
#घोषणा PPSMC_MSG_PM_STATUS_TO_DRAM_ON        ((uपूर्णांक16_t) 0x181)
#घोषणा PPSMC_MSG_PM_STATUS_TO_DRAM_OFF       ((uपूर्णांक16_t) 0x182)
#घोषणा PPSMC_MSG_UVD_HANDSHAKE_OFF           ((uपूर्णांक16_t) 0x183)
#घोषणा PPSMC_MSG_ALLOW_LOWSCLK_INTERRUPT     ((uपूर्णांक16_t) 0x184)
#घोषणा PPSMC_MSG_PkgPwrLimitEnable           ((uपूर्णांक16_t) 0x185)
#घोषणा PPSMC_MSG_PkgPwrLimitDisable          ((uपूर्णांक16_t) 0x186)
#घोषणा PPSMC_MSG_PkgPwrSetLimit              ((uपूर्णांक16_t) 0x187)
#घोषणा PPSMC_MSG_OverDriveSetTargetTdp       ((uपूर्णांक16_t) 0x188)
#घोषणा PPSMC_MSG_SCLKDPM_FreezeLevel         ((uपूर्णांक16_t) 0x189)
#घोषणा PPSMC_MSG_SCLKDPM_Unमुक्तzeLevel       ((uपूर्णांक16_t) 0x18A)
#घोषणा PPSMC_MSG_MCLKDPM_FreezeLevel         ((uपूर्णांक16_t) 0x18B)
#घोषणा PPSMC_MSG_MCLKDPM_Unमुक्तzeLevel       ((uपूर्णांक16_t) 0x18C)
#घोषणा PPSMC_MSG_START_DRAM_LOGGING          ((uपूर्णांक16_t) 0x18D)
#घोषणा PPSMC_MSG_STOP_DRAM_LOGGING           ((uपूर्णांक16_t) 0x18E)
#घोषणा PPSMC_MSG_MASTER_DeepSleep_ON         ((uपूर्णांक16_t) 0x18F)
#घोषणा PPSMC_MSG_MASTER_DeepSleep_OFF        ((uपूर्णांक16_t) 0x190)
#घोषणा PPSMC_MSG_Remove_DC_Clamp             ((uपूर्णांक16_t) 0x191)
#घोषणा PPSMC_MSG_DisableACDCGPIOInterrupt    ((uपूर्णांक16_t) 0x192)
#घोषणा PPSMC_MSG_OverrideVoltageControl_SetVddc       ((uपूर्णांक16_t) 0x193)
#घोषणा PPSMC_MSG_OverrideVoltageControl_SetVddci      ((uपूर्णांक16_t) 0x194)
#घोषणा PPSMC_MSG_SetVidOffset_1              ((uपूर्णांक16_t) 0x195)
#घोषणा PPSMC_MSG_SetVidOffset_2              ((uपूर्णांक16_t) 0x207)
#घोषणा PPSMC_MSG_GetVidOffset_1              ((uपूर्णांक16_t) 0x196)
#घोषणा PPSMC_MSG_GetVidOffset_2              ((uपूर्णांक16_t) 0x208)
#घोषणा PPSMC_MSG_THERMAL_OVERDRIVE_Enable    ((uपूर्णांक16_t) 0x197)
#घोषणा PPSMC_MSG_THERMAL_OVERDRIVE_Disable	  ((uपूर्णांक16_t) 0x198)
#घोषणा PPSMC_MSG_SetTjMax                    ((uपूर्णांक16_t) 0x199)
#घोषणा PPSMC_MSG_SetFanPwmMax                ((uपूर्णांक16_t) 0x19A)

#घोषणा PPSMC_MSG_WaitForMclkSwitchFinish	  ((uपूर्णांक16_t) 0x19B)
#घोषणा PPSMC_MSG_ENABLE_THERMAL_DPM          ((uपूर्णांक16_t) 0x19C)
#घोषणा PPSMC_MSG_DISABLE_THERMAL_DPM         ((uपूर्णांक16_t) 0x19D)
#घोषणा PPSMC_MSG_Enable_PCC                  ((uपूर्णांक16_t) 0x19E)
#घोषणा PPSMC_MSG_Disable_PCC                 ((uपूर्णांक16_t) 0x19F)

#घोषणा PPSMC_MSG_API_GetSclkFrequency        ((uपूर्णांक16_t) 0x200)
#घोषणा PPSMC_MSG_API_GetMclkFrequency        ((uपूर्णांक16_t) 0x201)
#घोषणा PPSMC_MSG_API_GetSclkBusy             ((uपूर्णांक16_t) 0x202)
#घोषणा PPSMC_MSG_API_GetMclkBusy             ((uपूर्णांक16_t) 0x203)
#घोषणा PPSMC_MSG_API_GetAsicPower            ((uपूर्णांक16_t) 0x204)
#घोषणा PPSMC_MSG_SetFanRpmMax                ((uपूर्णांक16_t) 0x205)
#घोषणा PPSMC_MSG_SetFanSclkTarget            ((uपूर्णांक16_t) 0x206)
#घोषणा PPSMC_MSG_SetFanMinPwm                ((uपूर्णांक16_t) 0x209)
#घोषणा PPSMC_MSG_SetFanTemperatureTarget     ((uपूर्णांक16_t) 0x20A)

#घोषणा PPSMC_MSG_BACO_StartMonitor           ((uपूर्णांक16_t) 0x240)
#घोषणा PPSMC_MSG_BACO_Cancel                 ((uपूर्णांक16_t) 0x241)
#घोषणा PPSMC_MSG_EnableVddGfx                ((uपूर्णांक16_t) 0x242)
#घोषणा PPSMC_MSG_DisableVddGfx               ((uपूर्णांक16_t) 0x243)
#घोषणा PPSMC_MSG_UcodeAddressLow             ((uपूर्णांक16_t) 0x244)
#घोषणा PPSMC_MSG_UcodeAddressHigh            ((uपूर्णांक16_t) 0x245)
#घोषणा PPSMC_MSG_UcodeLoadStatus             ((uपूर्णांक16_t) 0x246)

#घोषणा PPSMC_MSG_DRV_DRAM_ADDR_HI			  ((uपूर्णांक16_t) 0x250)
#घोषणा PPSMC_MSG_DRV_DRAM_ADDR_LO            ((uपूर्णांक16_t) 0x251)
#घोषणा PPSMC_MSG_SMU_DRAM_ADDR_HI            ((uपूर्णांक16_t) 0x252)
#घोषणा PPSMC_MSG_SMU_DRAM_ADDR_LO            ((uपूर्णांक16_t) 0x253)
#घोषणा PPSMC_MSG_LoadUcodes                  ((uपूर्णांक16_t) 0x254)
#घोषणा PPSMC_MSG_PowerStateNotअगरy            ((uपूर्णांक16_t) 0x255)
#घोषणा PPSMC_MSG_COND_EXEC_DRAM_ADDR_HI      ((uपूर्णांक16_t) 0x256)
#घोषणा PPSMC_MSG_COND_EXEC_DRAM_ADDR_LO      ((uपूर्णांक16_t) 0x257)
#घोषणा PPSMC_MSG_VBIOS_DRAM_ADDR_HI          ((uपूर्णांक16_t) 0x258)
#घोषणा PPSMC_MSG_VBIOS_DRAM_ADDR_LO          ((uपूर्णांक16_t) 0x259)
#घोषणा PPSMC_MSG_LoadVBios                   ((uपूर्णांक16_t) 0x25A)
#घोषणा PPSMC_MSG_GetUcodeVersion             ((uपूर्णांक16_t) 0x25B)
#घोषणा DMCUSMC_MSG_PSREntry                  ((uपूर्णांक16_t) 0x25C)
#घोषणा DMCUSMC_MSG_PSRExit                   ((uपूर्णांक16_t) 0x25D)
#घोषणा PPSMC_MSG_EnableClockGatingFeature    ((uपूर्णांक16_t) 0x260)
#घोषणा PPSMC_MSG_DisableClockGatingFeature   ((uपूर्णांक16_t) 0x261)
#घोषणा PPSMC_MSG_IsDeviceRunning             ((uपूर्णांक16_t) 0x262)
#घोषणा PPSMC_MSG_LoadMetaData                ((uपूर्णांक16_t) 0x263)
#घोषणा PPSMC_MSG_TMON_AutoCaliberate_Enable  ((uपूर्णांक16_t) 0x264)
#घोषणा PPSMC_MSG_TMON_AutoCaliberate_Disable ((uपूर्णांक16_t) 0x265)
#घोषणा PPSMC_MSG_GetTelemetry1Slope          ((uपूर्णांक16_t) 0x266)
#घोषणा PPSMC_MSG_GetTelemetry1Offset         ((uपूर्णांक16_t) 0x267)
#घोषणा PPSMC_MSG_GetTelemetry2Slope          ((uपूर्णांक16_t) 0x268)
#घोषणा PPSMC_MSG_GetTelemetry2Offset         ((uपूर्णांक16_t) 0x269)

प्रकार uपूर्णांक16_t PPSMC_Msg;

/* If the SMC firmware has an event status soft रेजिस्टर this is what the inभागidual bits mean.*/
#घोषणा PPSMC_EVENT_STATUS_THERMAL          0x00000001
#घोषणा PPSMC_EVENT_STATUS_REGULATORHOT     0x00000002
#घोषणा PPSMC_EVENT_STATUS_DC               0x00000004
#घोषणा PPSMC_EVENT_STATUS_GPIO17           0x00000008


#आशय pack(pop)
#पूर्ण_अगर
