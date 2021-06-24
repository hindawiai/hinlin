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

#अगर_अघोषित RAVEN_PP_SMC_H
#घोषणा RAVEN_PP_SMC_H

#आशय pack(push, 1)

#घोषणा PPSMC_Result_OK                    0x1
#घोषणा PPSMC_Result_Failed                0xFF
#घोषणा PPSMC_Result_UnknownCmd            0xFE
#घोषणा PPSMC_Result_CmdRejectedPrereq     0xFD
#घोषणा PPSMC_Result_CmdRejectedBusy       0xFC

#घोषणा PPSMC_MSG_TestMessage                   0x1
#घोषणा PPSMC_MSG_GetSmuVersion                 0x2
#घोषणा PPSMC_MSG_GetDriverIfVersion            0x3
#घोषणा PPSMC_MSG_PowerUpGfx                    0x6
#घोषणा PPSMC_MSG_EnableGfxOff                  0x7
#घोषणा PPSMC_MSG_DisableGfxOff                 0x8
#घोषणा PPSMC_MSG_PowerDownIspByTile            0x9
#घोषणा PPSMC_MSG_PowerUpIspByTile              0xA
#घोषणा PPSMC_MSG_PowerDownVcn                  0xB
#घोषणा PPSMC_MSG_PowerUpVcn                    0xC
#घोषणा PPSMC_MSG_PowerDownSdma                 0xD
#घोषणा PPSMC_MSG_PowerUpSdma                   0xE
#घोषणा PPSMC_MSG_SetHardMinIspclkByFreq        0xF
#घोषणा PPSMC_MSG_SetHardMinVcn                 0x10
#घोषणा PPSMC_MSG_SetMinDisplayClock            0x11
#घोषणा PPSMC_MSG_SetHardMinFclkByFreq          0x12
#घोषणा PPSMC_MSG_SetAllowFclkSwitch            0x13
#घोषणा PPSMC_MSG_SetMinVideoGfxclkFreq         0x14
#घोषणा PPSMC_MSG_ActiveProcessNotअगरy           0x15
#घोषणा PPSMC_MSG_SetCustomPolicy               0x16
#घोषणा PPSMC_MSG_SetVideoFps                   0x17
#घोषणा PPSMC_MSG_SetDisplayCount               0x18
#घोषणा PPSMC_MSG_QueryPowerLimit               0x19
#घोषणा PPSMC_MSG_SetDriverDramAddrHigh         0x1A
#घोषणा PPSMC_MSG_SetDriverDramAddrLow          0x1B
#घोषणा PPSMC_MSG_TransferTableSmu2Dram         0x1C
#घोषणा PPSMC_MSG_TransferTableDram2Smu         0x1D
#घोषणा PPSMC_MSG_DeviceDriverReset             0x1E
#घोषणा PPSMC_MSG_SetGfxclkOverdriveByFreqVid   0x1F
#घोषणा PPSMC_MSG_SetHardMinDcefclkByFreq       0x20
#घोषणा PPSMC_MSG_SetHardMinSocclkByFreq        0x21
#घोषणा PPSMC_MSG_SetMinVddcrSocVoltage         0x22
#घोषणा PPSMC_MSG_SetMinVideoFclkFreq           0x23
#घोषणा PPSMC_MSG_SetMinDeepSleepDcefclk        0x24
#घोषणा PPSMC_MSG_ForcePowerDownGfx             0x25
#घोषणा PPSMC_MSG_SetPhyclkVoltageByFreq        0x26
#घोषणा PPSMC_MSG_SetDppclkVoltageByFreq        0x27
#घोषणा PPSMC_MSG_SetSoftMinVcn                 0x28
#घोषणा PPSMC_MSG_GetGfxclkFrequency            0x2A
#घोषणा PPSMC_MSG_GetFclkFrequency              0x2B
#घोषणा PPSMC_MSG_GetMinGfxclkFrequency         0x2C
#घोषणा PPSMC_MSG_GetMaxGfxclkFrequency         0x2D
#घोषणा PPSMC_MSG_SoftReset                     0x2E
#घोषणा PPSMC_MSG_SetGfxCGPG			0x2F
#घोषणा PPSMC_MSG_SetSoftMaxGfxClk              0x30
#घोषणा PPSMC_MSG_SetHardMinGfxClk              0x31
#घोषणा PPSMC_MSG_SetSoftMaxSocclkByFreq        0x32
#घोषणा PPSMC_MSG_SetSoftMaxFclkByFreq          0x33
#घोषणा PPSMC_MSG_SetSoftMaxVcn                 0x34
#घोषणा PPSMC_MSG_PowerGateMmHub                0x35
#घोषणा PPSMC_MSG_SetRccPfcPmeRestoreRegister   0x36
#घोषणा PPSMC_MSG_GpuChangeState                0x37
#घोषणा PPSMC_MSG_GetGfxBusy                    0x3D
#घोषणा PPSMC_Message_Count                     0x42

प्रकार uपूर्णांक16_t PPSMC_Result;
प्रकार पूर्णांक      PPSMC_Msg;


#आशय pack(pop)

#पूर्ण_अगर
