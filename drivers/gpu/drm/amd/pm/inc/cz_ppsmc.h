<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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

#अगर_अघोषित CZ_PP_SMC_H
#घोषणा CZ_PP_SMC_H

#आशय pack(push, 1)

/* Fan control algorithm:*/
#घोषणा FDO_MODE_HARDWARE 0
#घोषणा FDO_MODE_PIECE_WISE_LINEAR 1

क्रमागत FAN_CONTROL अणु
    FAN_CONTROL_FUZZY,
    FAN_CONTROL_TABLE
पूर्ण;

क्रमागत DPM_ARRAY अणु
    DPM_ARRAY_HARD_MAX,
    DPM_ARRAY_HARD_MIN,
    DPM_ARRAY_SOFT_MAX,
    DPM_ARRAY_SOFT_MIN
पूर्ण;

/*
 * Return codes क्रम driver to SMC communication.
 * Leave these #घोषणा-s, क्रमागतs might not be exactly 8-bits on the microcontroller.
 */
#घोषणा PPSMC_Result_OK             ((uपूर्णांक16_t)0x01)
#घोषणा PPSMC_Result_NoMore         ((uपूर्णांक16_t)0x02)
#घोषणा PPSMC_Result_NotNow         ((uपूर्णांक16_t)0x03)
#घोषणा PPSMC_Result_Failed         ((uपूर्णांक16_t)0xFF)
#घोषणा PPSMC_Result_UnknownCmd     ((uपूर्णांक16_t)0xFE)
#घोषणा PPSMC_Result_UnknownVT      ((uपूर्णांक16_t)0xFD)

#घोषणा PPSMC_isERROR(x)            ((uपूर्णांक16_t)0x80 & (x))

/*
 * Supported driver messages
 */
#घोषणा PPSMC_MSG_Test                        ((uपूर्णांक16_t) 0x1)
#घोषणा PPSMC_MSG_GetFeatureStatus            ((uपूर्णांक16_t) 0x2)
#घोषणा PPSMC_MSG_EnableAllSmuFeatures        ((uपूर्णांक16_t) 0x3)
#घोषणा PPSMC_MSG_DisableAllSmuFeatures       ((uपूर्णांक16_t) 0x4)
#घोषणा PPSMC_MSG_OptimizeBattery             ((uपूर्णांक16_t) 0x5)
#घोषणा PPSMC_MSG_MaximizePerf                ((uपूर्णांक16_t) 0x6)
#घोषणा PPSMC_MSG_UVDPowerOFF                 ((uपूर्णांक16_t) 0x7)
#घोषणा PPSMC_MSG_UVDPowerON                  ((uपूर्णांक16_t) 0x8)
#घोषणा PPSMC_MSG_VCEPowerOFF                 ((uपूर्णांक16_t) 0x9)
#घोषणा PPSMC_MSG_VCEPowerON                  ((uपूर्णांक16_t) 0xA)
#घोषणा PPSMC_MSG_ACPPowerOFF                 ((uपूर्णांक16_t) 0xB)
#घोषणा PPSMC_MSG_ACPPowerON                  ((uपूर्णांक16_t) 0xC)
#घोषणा PPSMC_MSG_SDMAPowerOFF                ((uपूर्णांक16_t) 0xD)
#घोषणा PPSMC_MSG_SDMAPowerON                 ((uपूर्णांक16_t) 0xE)
#घोषणा PPSMC_MSG_XDMAPowerOFF                ((uपूर्णांक16_t) 0xF)
#घोषणा PPSMC_MSG_XDMAPowerON                 ((uपूर्णांक16_t) 0x10)
#घोषणा PPSMC_MSG_SetMinDeepSleepSclk         ((uपूर्णांक16_t) 0x11)
#घोषणा PPSMC_MSG_SetSclkSoftMin              ((uपूर्णांक16_t) 0x12)
#घोषणा PPSMC_MSG_SetSclkSoftMax              ((uपूर्णांक16_t) 0x13)
#घोषणा PPSMC_MSG_SetSclkHardMin              ((uपूर्णांक16_t) 0x14)
#घोषणा PPSMC_MSG_SetSclkHardMax              ((uपूर्णांक16_t) 0x15)
#घोषणा PPSMC_MSG_SetLclkSoftMin              ((uपूर्णांक16_t) 0x16)
#घोषणा PPSMC_MSG_SetLclkSoftMax              ((uपूर्णांक16_t) 0x17)
#घोषणा PPSMC_MSG_SetLclkHardMin              ((uपूर्णांक16_t) 0x18)
#घोषणा PPSMC_MSG_SetLclkHardMax              ((uपूर्णांक16_t) 0x19)
#घोषणा PPSMC_MSG_SetUvdSoftMin               ((uपूर्णांक16_t) 0x1A)
#घोषणा PPSMC_MSG_SetUvdSoftMax               ((uपूर्णांक16_t) 0x1B)
#घोषणा PPSMC_MSG_SetUvdHardMin               ((uपूर्णांक16_t) 0x1C)
#घोषणा PPSMC_MSG_SetUvdHardMax               ((uपूर्णांक16_t) 0x1D)
#घोषणा PPSMC_MSG_SetEclkSoftMin              ((uपूर्णांक16_t) 0x1E)
#घोषणा PPSMC_MSG_SetEclkSoftMax              ((uपूर्णांक16_t) 0x1F)
#घोषणा PPSMC_MSG_SetEclkHardMin              ((uपूर्णांक16_t) 0x20)
#घोषणा PPSMC_MSG_SetEclkHardMax              ((uपूर्णांक16_t) 0x21)
#घोषणा PPSMC_MSG_SetAclkSoftMin              ((uपूर्णांक16_t) 0x22)
#घोषणा PPSMC_MSG_SetAclkSoftMax              ((uपूर्णांक16_t) 0x23)
#घोषणा PPSMC_MSG_SetAclkHardMin              ((uपूर्णांक16_t) 0x24)
#घोषणा PPSMC_MSG_SetAclkHardMax              ((uपूर्णांक16_t) 0x25)
#घोषणा PPSMC_MSG_SetNclkSoftMin              ((uपूर्णांक16_t) 0x26)
#घोषणा PPSMC_MSG_SetNclkSoftMax              ((uपूर्णांक16_t) 0x27)
#घोषणा PPSMC_MSG_SetNclkHardMin              ((uपूर्णांक16_t) 0x28)
#घोषणा PPSMC_MSG_SetNclkHardMax              ((uपूर्णांक16_t) 0x29)
#घोषणा PPSMC_MSG_SetPstateSoftMin            ((uपूर्णांक16_t) 0x2A)
#घोषणा PPSMC_MSG_SetPstateSoftMax            ((uपूर्णांक16_t) 0x2B)
#घोषणा PPSMC_MSG_SetPstateHardMin            ((uपूर्णांक16_t) 0x2C)
#घोषणा PPSMC_MSG_SetPstateHardMax            ((uपूर्णांक16_t) 0x2D)
#घोषणा PPSMC_MSG_DisableLowMemoryPstate      ((uपूर्णांक16_t) 0x2E)
#घोषणा PPSMC_MSG_EnableLowMemoryPstate       ((uपूर्णांक16_t) 0x2F)
#घोषणा PPSMC_MSG_UcodeAddressLow             ((uपूर्णांक16_t) 0x30)
#घोषणा PPSMC_MSG_UcodeAddressHigh            ((uपूर्णांक16_t) 0x31)
#घोषणा PPSMC_MSG_UcodeLoadStatus             ((uपूर्णांक16_t) 0x32)
#घोषणा PPSMC_MSG_DriverDramAddrHi            ((uपूर्णांक16_t) 0x33)
#घोषणा PPSMC_MSG_DriverDramAddrLo            ((uपूर्णांक16_t) 0x34)
#घोषणा PPSMC_MSG_CondExecDramAddrHi          ((uपूर्णांक16_t) 0x35)
#घोषणा PPSMC_MSG_CondExecDramAddrLo          ((uपूर्णांक16_t) 0x36)
#घोषणा PPSMC_MSG_LoadUcodes                  ((uपूर्णांक16_t) 0x37)
#घोषणा PPSMC_MSG_DriverResetMode             ((uपूर्णांक16_t) 0x38)
#घोषणा PPSMC_MSG_PowerStateNotअगरy            ((uपूर्णांक16_t) 0x39)
#घोषणा PPSMC_MSG_SetDisplayPhyConfig         ((uपूर्णांक16_t) 0x3A)
#घोषणा PPSMC_MSG_GetMaxSclkLevel             ((uपूर्णांक16_t) 0x3B)
#घोषणा PPSMC_MSG_GetMaxLclkLevel             ((uपूर्णांक16_t) 0x3C)
#घोषणा PPSMC_MSG_GetMaxUvdLevel              ((uपूर्णांक16_t) 0x3D)
#घोषणा PPSMC_MSG_GetMaxEclkLevel             ((uपूर्णांक16_t) 0x3E)
#घोषणा PPSMC_MSG_GetMaxAclkLevel             ((uपूर्णांक16_t) 0x3F)
#घोषणा PPSMC_MSG_GetMaxNclkLevel             ((uपूर्णांक16_t) 0x40)
#घोषणा PPSMC_MSG_GetMaxPstate                ((uपूर्णांक16_t) 0x41)
#घोषणा PPSMC_MSG_DramAddrHiVirtual           ((uपूर्णांक16_t) 0x42)
#घोषणा PPSMC_MSG_DramAddrLoVirtual           ((uपूर्णांक16_t) 0x43)
#घोषणा PPSMC_MSG_DramAddrHiPhysical          ((uपूर्णांक16_t) 0x44)
#घोषणा PPSMC_MSG_DramAddrLoPhysical          ((uपूर्णांक16_t) 0x45)
#घोषणा PPSMC_MSG_DramBufferSize              ((uपूर्णांक16_t) 0x46)
#घोषणा PPSMC_MSG_SetMmPwrLogDramAddrHi       ((uपूर्णांक16_t) 0x47)
#घोषणा PPSMC_MSG_SetMmPwrLogDramAddrLo       ((uपूर्णांक16_t) 0x48)
#घोषणा PPSMC_MSG_SetClkTableAddrHi           ((uपूर्णांक16_t) 0x49)
#घोषणा PPSMC_MSG_SetClkTableAddrLo           ((uपूर्णांक16_t) 0x4A)
#घोषणा PPSMC_MSG_GetConservativePowerLimit   ((uपूर्णांक16_t) 0x4B)

#घोषणा PPSMC_MSG_InitJobs                    ((uपूर्णांक16_t) 0x252)
#घोषणा PPSMC_MSG_ExecuteJob                  ((uपूर्णांक16_t) 0x254)

#घोषणा PPSMC_MSG_NBDPM_Enable                ((uपूर्णांक16_t) 0x140)
#घोषणा PPSMC_MSG_NBDPM_Disable               ((uपूर्णांक16_t) 0x141)

#घोषणा PPSMC_MSG_DPM_FPS_Mode                ((uपूर्णांक16_t) 0x15d)
#घोषणा PPSMC_MSG_DPM_Activity_Mode           ((uपूर्णांक16_t) 0x15e)

#घोषणा PPSMC_MSG_PmStatusLogStart            ((uपूर्णांक16_t) 0x170)
#घोषणा PPSMC_MSG_PmStatusLogSample           ((uपूर्णांक16_t) 0x171)

#घोषणा PPSMC_MSG_AllowLowSclkInterrupt       ((uपूर्णांक16_t) 0x184)
#घोषणा PPSMC_MSG_MmPowerMonitorStart         ((uपूर्णांक16_t) 0x18F)
#घोषणा PPSMC_MSG_MmPowerMonitorStop          ((uपूर्णांक16_t) 0x190)
#घोषणा PPSMC_MSG_MmPowerMonitorRestart       ((uपूर्णांक16_t) 0x191)

#घोषणा PPSMC_MSG_SetClockGateMask            ((uपूर्णांक16_t) 0x260)
#घोषणा PPSMC_MSG_SetFpsThresholdLo           ((uपूर्णांक16_t) 0x264)
#घोषणा PPSMC_MSG_SetFpsThresholdHi           ((uपूर्णांक16_t) 0x265)
#घोषणा PPSMC_MSG_SetLowSclkIntrThreshold     ((uपूर्णांक16_t) 0x266)

#घोषणा PPSMC_MSG_ClkTableXferToDram          ((uपूर्णांक16_t) 0x267)
#घोषणा PPSMC_MSG_ClkTableXferToSmu           ((uपूर्णांक16_t) 0x268)
#घोषणा PPSMC_MSG_GetAverageGraphicsActivity  ((uपूर्णांक16_t) 0x269)
#घोषणा PPSMC_MSG_GetAverageGioActivity       ((uपूर्णांक16_t) 0x26A)
#घोषणा PPSMC_MSG_SetLoggerBufferSize         ((uपूर्णांक16_t) 0x26B)
#घोषणा PPSMC_MSG_SetLoggerAddressHigh        ((uपूर्णांक16_t) 0x26C)
#घोषणा PPSMC_MSG_SetLoggerAddressLow         ((uपूर्णांक16_t) 0x26D)
#घोषणा PPSMC_MSG_SetWatermarkFrequency       ((uपूर्णांक16_t) 0x26E)
#घोषणा PPSMC_MSG_SetDisplaySizePowerParams   ((uपूर्णांक16_t) 0x26F)

/* REMOVE LATER*/
#घोषणा PPSMC_MSG_DPM_ForceState              ((uपूर्णांक16_t) 0x104)

/* Feature Enable Masks*/
#घोषणा NB_DPM_MASK             0x00000800
#घोषणा VDDGFX_MASK             0x00800000
#घोषणा VCE_DPM_MASK            0x00400000
#घोषणा ACP_DPM_MASK            0x00040000
#घोषणा UVD_DPM_MASK            0x00010000
#घोषणा GFX_CU_PG_MASK          0x00004000
#घोषणा SCLK_DPM_MASK           0x00080000

#अगर !defined(SMC_MICROCODE)
#आशय pack(pop)

#पूर्ण_अगर

#पूर्ण_अगर
