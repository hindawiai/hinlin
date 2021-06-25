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

#अगर_अघोषित SMU_V11_0_7_PPSMC_H
#घोषणा SMU_V11_0_7_PPSMC_H

#घोषणा PPSMC_VERSION 0x1

// SMU Response Codes:
#घोषणा PPSMC_Result_OK                    0x1
#घोषणा PPSMC_Result_Failed                0xFF
#घोषणा PPSMC_Result_UnknownCmd            0xFE
#घोषणा PPSMC_Result_CmdRejectedPrereq     0xFD
#घोषणा PPSMC_Result_CmdRejectedBusy       0xFC

// Message Definitions:
// BASIC
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
#घोषणा PPSMC_MSG_GetRunningSmuFeaturesLow       0xC
#घोषणा PPSMC_MSG_GetRunningSmuFeaturesHigh      0xD
#घोषणा PPSMC_MSG_SetDriverDramAddrHigh          0xE
#घोषणा PPSMC_MSG_SetDriverDramAddrLow           0xF
#घोषणा PPSMC_MSG_SetToolsDramAddrHigh           0x10
#घोषणा PPSMC_MSG_SetToolsDramAddrLow            0x11
#घोषणा PPSMC_MSG_TransferTableSmu2Dram          0x12
#घोषणा PPSMC_MSG_TransferTableDram2Smu          0x13
#घोषणा PPSMC_MSG_UseDefaultPPTable              0x14

//BACO/BAMACO/BOMACO
#घोषणा PPSMC_MSG_EnterBaco                      0x15
#घोषणा PPSMC_MSG_ExitBaco                       0x16
#घोषणा PPSMC_MSG_ArmD3                          0x17
#घोषणा PPSMC_MSG_BacoAudioD3PME                 0x18

//DPM
#घोषणा PPSMC_MSG_SetSoftMinByFreq               0x19
#घोषणा PPSMC_MSG_SetSoftMaxByFreq               0x1A
#घोषणा PPSMC_MSG_SetHardMinByFreq               0x1B
#घोषणा PPSMC_MSG_SetHardMaxByFreq               0x1C
#घोषणा PPSMC_MSG_GetMinDpmFreq                  0x1D
#घोषणा PPSMC_MSG_GetMaxDpmFreq                  0x1E
#घोषणा PPSMC_MSG_GetDpmFreqByIndex              0x1F
#घोषणा PPSMC_MSG_OverridePcieParameters         0x20

//DramLog Set DramAddrHigh
#घोषणा PPSMC_MSG_DramLogSetDramAddrHigh         0x21

#घोषणा PPSMC_MSG_SetWorkloadMask                0x22
#घोषणा PPSMC_MSG_SetUclkFastSwitch              0x23
#घोषणा PPSMC_MSG_GetVoltageByDpm                0x24
#घोषणा PPSMC_MSG_SetVideoFps                    0x25
#घोषणा PPSMC_MSG_GetDcModeMaxDpmFreq            0x26

//DramLog Set DramAddrLow
#घोषणा PPSMC_MSG_DramLogSetDramAddrLow          0x27

//Power Gating
#घोषणा PPSMC_MSG_AllowGfxOff                    0x28
#घोषणा PPSMC_MSG_DisallowGfxOff                 0x29
#घोषणा PPSMC_MSG_PowerUpVcn                     0x2A
#घोषणा PPSMC_MSG_PowerDownVcn	                 0x2B
#घोषणा PPSMC_MSG_PowerUpJpeg                    0x2C
#घोषणा PPSMC_MSG_PowerDownJpeg	                 0x2D

//Resets
#घोषणा PPSMC_MSG_PrepareMp1ForUnload            0x2E

//DramLog Set DramLog SetDramSize 
#घोषणा PPSMC_MSG_DramLogSetDramSize             0x2F

#घोषणा PPSMC_MSG_Mode1Reset                     0x30

//Set SystemVirtual DramAddrHigh
#घोषणा PPSMC_MSG_SetSystemVirtualDramAddrHigh   0x31

//ACDC Power Source
#घोषणा PPSMC_MSG_SetPptLimit                    0x32
#घोषणा PPSMC_MSG_GetPptLimit                    0x33
#घोषणा PPSMC_MSG_ReenableAcDcInterrupt          0x34
#घोषणा PPSMC_MSG_NotअगरyPowerSource              0x35

//BTC
#घोषणा PPSMC_MSG_RunDcBtc                       0x36

//Set SystemVirtual DramAddrLow
#घोषणा PPSMC_MSG_SetSystemVirtualDramAddrLow    0x38

//Others
#घोषणा PPSMC_MSG_SetMemoryChannelEnable         0x39
#घोषणा PPSMC_MSG_SetDramBitWidth                0x3A
#घोषणा PPSMC_MSG_SetGeminiMode                  0x3B
#घोषणा PPSMC_MSG_SetGeminiApertureHigh          0x3C
#घोषणा PPSMC_MSG_SetGeminiApertureLow           0x3D

#घोषणा PPSMC_MSG_SetTemperatureInputSelect      0x3E
#घोषणा PPSMC_MSG_SetFwDstatesMask               0x3F
#घोषणा PPSMC_MSG_SetThrottlerMask               0x40

#घोषणा PPSMC_MSG_SetExternalClientDfCstateAllow 0x41
#घोषणा PPSMC_MSG_EnableOutOfBandMonTesting      0x42
#घोषणा PPSMC_MSG_SetMGpuFanBoostLimitRpm        0x43

#घोषणा PPSMC_MSG_SetNumBadHbmPagesRetired       0x44
#घोषणा PPSMC_MSG_SetGpoFeaturePMask             0x45
#घोषणा PPSMC_MSG_SetSMBUSInterrupt              0x46

#घोषणा PPSMC_MSG_DisallowGpo                    0x56

#घोषणा PPSMC_MSG_Enable2ndUSB20Port             0x57

#घोषणा PPSMC_Message_Count                      0x58

#पूर्ण_अगर
