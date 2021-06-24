<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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

#अगर_अघोषित VEGA12_PP_SMC_H
#घोषणा VEGA12_PP_SMC_H

#आशय pack(push, 1)

#घोषणा SMU_UCODE_VERSION                  0x00270a00

/* SMU Response Codes: */
#घोषणा PPSMC_Result_OK                    0x1
#घोषणा PPSMC_Result_Failed                0xFF
#घोषणा PPSMC_Result_UnknownCmd            0xFE
#घोषणा PPSMC_Result_CmdRejectedPrereq     0xFD
#घोषणा PPSMC_Result_CmdRejectedBusy       0xFC

#घोषणा PPSMC_MSG_TestMessage                    0x1
#घोषणा PPSMC_MSG_GetSmuVersion                  0x2
#घोषणा PPSMC_MSG_GetDriverIfVersion             0x3
#घोषणा PPSMC_MSG_SetAllowedFeaturesMaskLow      0x4
#घोषणा PPSMC_MSG_SetAllowedFeaturesMaskHigh     0x5
#घोषणा PPSMC_MSG_EnableAllSmuFeatures           0x6
#घोषणा PPSMC_MSG_DisableAllSmuFeatures          0x7
#घोषणा PPSMC_MSG_EnableSmuFeaturesLow           0x8
#घोषणा PPSMC_MSG_EnableSmuFeaturesHigh          0x9
#घोषणा PPSMC_MSG_DisableSmuFeaturesLow          0xA
#घोषणा PPSMC_MSG_DisableSmuFeaturesHigh         0xB
#घोषणा PPSMC_MSG_GetEnabledSmuFeaturesLow       0xC
#घोषणा PPSMC_MSG_GetEnabledSmuFeaturesHigh      0xD
#घोषणा PPSMC_MSG_SetWorkloadMask                0xE
#घोषणा PPSMC_MSG_SetPptLimit                    0xF
#घोषणा PPSMC_MSG_SetDriverDramAddrHigh          0x10
#घोषणा PPSMC_MSG_SetDriverDramAddrLow           0x11
#घोषणा PPSMC_MSG_SetToolsDramAddrHigh           0x12
#घोषणा PPSMC_MSG_SetToolsDramAddrLow            0x13
#घोषणा PPSMC_MSG_TransferTableSmu2Dram          0x14
#घोषणा PPSMC_MSG_TransferTableDram2Smu          0x15
#घोषणा PPSMC_MSG_UseDefaultPPTable              0x16
#घोषणा PPSMC_MSG_UseBackupPPTable               0x17
#घोषणा PPSMC_MSG_RunBtc                         0x18
#घोषणा PPSMC_MSG_RequestI2CBus                  0x19
#घोषणा PPSMC_MSG_ReleaseI2CBus                  0x1A
#घोषणा PPSMC_MSG_SetFloorSocVoltage             0x21
#घोषणा PPSMC_MSG_SoftReset                      0x22
#घोषणा PPSMC_MSG_StartBacoMonitor               0x23
#घोषणा PPSMC_MSG_CancelBacoMonitor              0x24
#घोषणा PPSMC_MSG_EnterBaco                      0x25
#घोषणा PPSMC_MSG_SetSoftMinByFreq               0x26
#घोषणा PPSMC_MSG_SetSoftMaxByFreq               0x27
#घोषणा PPSMC_MSG_SetHardMinByFreq               0x28
#घोषणा PPSMC_MSG_SetHardMaxByFreq               0x29
#घोषणा PPSMC_MSG_GetMinDpmFreq                  0x2A
#घोषणा PPSMC_MSG_GetMaxDpmFreq                  0x2B
#घोषणा PPSMC_MSG_GetDpmFreqByIndex              0x2C
#घोषणा PPSMC_MSG_GetDpmClockFreq                0x2D
#घोषणा PPSMC_MSG_GetSsVoltageByDpm              0x2E
#घोषणा PPSMC_MSG_SetMemoryChannelConfig         0x2F
#घोषणा PPSMC_MSG_SetGeminiMode                  0x30
#घोषणा PPSMC_MSG_SetGeminiApertureHigh          0x31
#घोषणा PPSMC_MSG_SetGeminiApertureLow           0x32
#घोषणा PPSMC_MSG_SetMinLinkDpmByIndex           0x33
#घोषणा PPSMC_MSG_OverridePcieParameters         0x34
#घोषणा PPSMC_MSG_OverDriveSetPercentage         0x35
#घोषणा PPSMC_MSG_SetMinDeepSleepDcefclk         0x36
#घोषणा PPSMC_MSG_ReenableAcDcInterrupt          0x37
#घोषणा PPSMC_MSG_NotअगरyPowerSource              0x38
#घोषणा PPSMC_MSG_SetUclkFastSwitch              0x39
#घोषणा PPSMC_MSG_SetUclkDownHyst                0x3A
#घोषणा PPSMC_MSG_GfxDeviceDriverReset           0x3B
#घोषणा PPSMC_MSG_GetCurrentRpm                  0x3C
#घोषणा PPSMC_MSG_SetVideoFps                    0x3D
#घोषणा PPSMC_MSG_SetTjMax                       0x3E
#घोषणा PPSMC_MSG_SetFanTemperatureTarget        0x3F
#घोषणा PPSMC_MSG_PrepareMp1ForUnload            0x40
#घोषणा PPSMC_MSG_DramLogSetDramAddrHigh         0x41
#घोषणा PPSMC_MSG_DramLogSetDramAddrLow          0x42
#घोषणा PPSMC_MSG_DramLogSetDramSize             0x43
#घोषणा PPSMC_MSG_SetFanMaxRpm                   0x44
#घोषणा PPSMC_MSG_SetFanMinPwm                   0x45
#घोषणा PPSMC_MSG_ConfigureGfxDidt               0x46
#घोषणा PPSMC_MSG_NumOfDisplays                  0x47
#घोषणा PPSMC_MSG_RemoveMargins                  0x48
#घोषणा PPSMC_MSG_ReadSerialNumTop32             0x49
#घोषणा PPSMC_MSG_ReadSerialNumBottom32          0x4A
#घोषणा PPSMC_MSG_SetSystemVirtualDramAddrHigh   0x4B
#घोषणा PPSMC_MSG_SetSystemVirtualDramAddrLow    0x4C
#घोषणा PPSMC_MSG_RunAcgBtc                      0x4D
#घोषणा PPSMC_MSG_InitializeAcg                  0x4E
#घोषणा PPSMC_MSG_EnableAcgBtcTestMode           0x4F
#घोषणा PPSMC_MSG_EnableAcgSpपढ़ोSpectrum        0x50
#घोषणा PPSMC_MSG_AllowGfxOff                    0x51
#घोषणा PPSMC_MSG_DisallowGfxOff                 0x52
#घोषणा PPSMC_MSG_GetPptLimit                    0x53
#घोषणा PPSMC_MSG_GetDcModeMaxDpmFreq            0x54
#घोषणा PPSMC_Message_Count                      0x56

प्रकार uपूर्णांक16_t PPSMC_Result;
प्रकार पूर्णांक PPSMC_Msg;

#आशय pack(pop)

#पूर्ण_अगर
