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

#अगर_अघोषित SMU_11_5_0_PPSMC_H
#घोषणा SMU_11_5_0_PPSMC_H

// SMU Response Codes:
#घोषणा PPSMC_Result_OK 0x1
#घोषणा PPSMC_Result_Failed 0xFF
#घोषणा PPSMC_Result_UnknownCmd 0xFE
#घोषणा PPSMC_Result_CmdRejectedPrereq 0xFD
#घोषणा PPSMC_Result_CmdRejectedBusy 0xFC

// Message Definitions:
#घोषणा PPSMC_MSG_TestMessage                          0x1
#घोषणा PPSMC_MSG_GetSmuVersion                        0x2
#घोषणा PPSMC_MSG_GetDriverIfVersion                   0x3
#घोषणा PPSMC_MSG_EnableGfxOff                         0x4
#घोषणा PPSMC_MSG_DisableGfxOff                        0x5
#घोषणा PPSMC_MSG_PowerDownIspByTile                   0x6 // ISP is घातer gated by शेष
#घोषणा PPSMC_MSG_PowerUpIspByTile                     0x7
#घोषणा PPSMC_MSG_PowerDownVcn                         0x8 // VCN is घातer gated by शेष
#घोषणा PPSMC_MSG_PowerUpVcn                           0x9
#घोषणा PPSMC_MSG_RlcPowerNotअगरy                       0xA
#घोषणा PPSMC_MSG_SetHardMinVcn                        0xB // For wireless display
#घोषणा PPSMC_MSG_SetSoftMinGfxclk                     0xC //Sets SoftMin क्रम GFXCLK. Arg is in MHz
#घोषणा PPSMC_MSG_ActiveProcessNotअगरy                  0xD
#घोषणा PPSMC_MSG_SetHardMinIspiclkByFreq              0xE
#घोषणा PPSMC_MSG_SetHardMinIspxclkByFreq              0xF
#घोषणा PPSMC_MSG_SetDriverDramAddrHigh                0x10
#घोषणा PPSMC_MSG_SetDriverDramAddrLow                 0x11
#घोषणा PPSMC_MSG_TransferTableSmu2Dram                0x12
#घोषणा PPSMC_MSG_TransferTableDram2Smu                0x13
#घोषणा PPSMC_MSG_GfxDeviceDriverReset                 0x14 //mode 2 reset during TDR
#घोषणा PPSMC_MSG_GetEnabledSmuFeatures                0x15
#घोषणा PPSMC_MSG_spare1                               0x16
#घोषणा PPSMC_MSG_SetHardMinSocclkByFreq               0x17
#घोषणा PPSMC_MSG_SetSoftMinFclk                       0x18 //Used to be PPSMC_MSG_SetMinVideoFclkFreq
#घोषणा PPSMC_MSG_SetSoftMinVcn                        0x19
#घोषणा PPSMC_MSG_EnablePostCode                       0x1A
#घोषणा PPSMC_MSG_GetGfxclkFrequency                   0x1B
#घोषणा PPSMC_MSG_GetFclkFrequency                     0x1C
#घोषणा PPSMC_MSG_AllowGfxOff                          0x1D
#घोषणा PPSMC_MSG_DisallowGfxOff                       0x1E
#घोषणा PPSMC_MSG_SetSoftMaxGfxClk                     0x1F
#घोषणा PPSMC_MSG_SetHardMinGfxClk                     0x20
#घोषणा PPSMC_MSG_SetSoftMaxSocclkByFreq               0x21
#घोषणा PPSMC_MSG_SetSoftMaxFclkByFreq                 0x22
#घोषणा PPSMC_MSG_SetSoftMaxVcn                        0x23
#घोषणा PPSMC_MSG_spare2                               0x24
#घोषणा PPSMC_MSG_SetPowerLimitPercentage              0x25
#घोषणा PPSMC_MSG_PowerDownJpeg                        0x26
#घोषणा PPSMC_MSG_PowerUpJpeg                          0x27
#घोषणा PPSMC_MSG_SetHardMinFclkByFreq                 0x28
#घोषणा PPSMC_MSG_SetSoftMinSocclkByFreq               0x29
#घोषणा PPSMC_MSG_PowerUpCvip                          0x2A
#घोषणा PPSMC_MSG_PowerDownCvip                        0x2B
#घोषणा PPSMC_MSG_GetPptLimit                          0x2C
#घोषणा PPSMC_MSG_GetThermalLimit                      0x2D
#घोषणा PPSMC_MSG_GetCurrentTemperature                0x2E
#घोषणा PPSMC_MSG_GetCurrentPower                      0x2F
#घोषणा PPSMC_MSG_GetCurrentVoltage                    0x30
#घोषणा PPSMC_MSG_GetCurrentCurrent                    0x31
#घोषणा PPSMC_MSG_GetAverageCpuActivity                0x32
#घोषणा PPSMC_MSG_GetAverageGfxActivity                0x33
#घोषणा PPSMC_MSG_GetAveragePower                      0x34
#घोषणा PPSMC_MSG_GetAverageTemperature                0x35
#घोषणा PPSMC_MSG_SetAveragePowerTimeConstant          0x36
#घोषणा PPSMC_MSG_SetAverageActivityTimeConstant       0x37
#घोषणा PPSMC_MSG_SetAverageTemperatureTimeConstant    0x38
#घोषणा PPSMC_MSG_SetMitigationEndHysteresis           0x39
#घोषणा PPSMC_MSG_GetCurrentFreq                       0x3A
#घोषणा PPSMC_MSG_SetReducedPptLimit                   0x3B
#घोषणा PPSMC_MSG_SetReducedThermalLimit               0x3C
#घोषणा PPSMC_MSG_DramLogSetDramAddr                   0x3D
#घोषणा PPSMC_MSG_StartDramLogging                     0x3E
#घोषणा PPSMC_MSG_StopDramLogging                      0x3F
#घोषणा PPSMC_MSG_SetSoftMinCclk                       0x40
#घोषणा PPSMC_MSG_SetSoftMaxCclk                       0x41
#घोषणा PPSMC_MSG_SetDfPstateActiveLevel               0x42
#घोषणा PPSMC_MSG_SetDfPstateSoftMinLevel              0x43
#घोषणा PPSMC_MSG_SetCclkPolicy                        0x44
#घोषणा PPSMC_MSG_DramLogSetDramAddrHigh               0x45
#घोषणा PPSMC_MSG_DramLogSetDramBufferSize             0x46
#घोषणा PPSMC_MSG_RequestActiveWgp                     0x47
#घोषणा PPSMC_MSG_QueryActiveWgp                       0x48
#घोषणा PPSMC_MSG_SetFastPPTLimit                      0x49
#घोषणा PPSMC_MSG_SetSlowPPTLimit                      0x4A
#घोषणा PPSMC_MSG_GetFastPPTLimit                      0x4B
#घोषणा PPSMC_MSG_GetSlowPPTLimit                      0x4C
#घोषणा PPSMC_Message_Count                            0x4D

//Argument क्रम PPSMC_MSG_GfxDeviceDriverReset
क्रमागत अणु
  MODE1_RESET = 1,
  MODE2_RESET = 2
पूर्ण;

#पूर्ण_अगर
