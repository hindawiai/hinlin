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

#अगर_अघोषित ALDEBARAN_PP_SMC_H
#घोषणा ALDEBARAN_PP_SMC_H

#आशय pack(push, 1)

// SMU Response Codes:
#घोषणा PPSMC_Result_OK                    0x1
#घोषणा PPSMC_Result_Failed                0xFF
#घोषणा PPSMC_Result_UnknownCmd            0xFE
#घोषणा PPSMC_Result_CmdRejectedPrereq     0xFD
#घोषणा PPSMC_Result_CmdRejectedBusy       0xFC

// Message Definitions:
#घोषणा PPSMC_MSG_TestMessage                    0x1
#घोषणा PPSMC_MSG_GetSmuVersion                  0x2
#घोषणा PPSMC_MSG_GfxDriverReset                 0x3
#घोषणा PPSMC_MSG_GetDriverIfVersion             0x4
#घोषणा PPSMC_MSG_spare1                         0x5
#घोषणा PPSMC_MSG_spare2                         0x6
#घोषणा PPSMC_MSG_EnableAllSmuFeatures           0x7
#घोषणा PPSMC_MSG_DisableAllSmuFeatures          0x8
#घोषणा PPSMC_MSG_spare3                         0x9
#घोषणा PPSMC_MSG_spare4                         0xA
#घोषणा PPSMC_MSG_spare5                         0xB
#घोषणा PPSMC_MSG_spare6                         0xC
#घोषणा PPSMC_MSG_GetEnabledSmuFeaturesLow       0xD
#घोषणा PPSMC_MSG_GetEnabledSmuFeaturesHigh      0xE
#घोषणा PPSMC_MSG_SetDriverDramAddrHigh          0xF
#घोषणा PPSMC_MSG_SetDriverDramAddrLow           0x10
#घोषणा PPSMC_MSG_SetToolsDramAddrHigh           0x11
#घोषणा PPSMC_MSG_SetToolsDramAddrLow            0x12
#घोषणा PPSMC_MSG_TransferTableSmu2Dram          0x13
#घोषणा PPSMC_MSG_TransferTableDram2Smu          0x14
#घोषणा PPSMC_MSG_UseDefaultPPTable              0x15
#घोषणा PPSMC_MSG_SetSystemVirtualDramAddrHigh   0x16
#घोषणा PPSMC_MSG_SetSystemVirtualDramAddrLow    0x17
#घोषणा PPSMC_MSG_SetSoftMinByFreq               0x18
#घोषणा PPSMC_MSG_SetSoftMaxByFreq               0x19
#घोषणा PPSMC_MSG_SetHardMinByFreq               0x1A
#घोषणा PPSMC_MSG_SetHardMaxByFreq               0x1B
#घोषणा PPSMC_MSG_GetMinDpmFreq                  0x1C
#घोषणा PPSMC_MSG_GetMaxDpmFreq                  0x1D
#घोषणा PPSMC_MSG_GetDpmFreqByIndex              0x1E
#घोषणा PPSMC_MSG_SetWorkloadMask                0x1F
#घोषणा PPSMC_MSG_GetVoltageByDpm                0x20
#घोषणा PPSMC_MSG_GetVoltageByDpmOverdrive       0x21
#घोषणा PPSMC_MSG_SetPptLimit                    0x22
#घोषणा PPSMC_MSG_GetPptLimit                    0x23
#घोषणा PPSMC_MSG_PrepareMp1ForUnload            0x24
#घोषणा PPSMC_MSG_PrepareMp1ForReset             0x25 //retired in 68.07
#घोषणा PPSMC_MSG_SoftReset                      0x26 //retired in 68.07
#घोषणा PPSMC_MSG_RunDcBtc                       0x27
#घोषणा PPSMC_MSG_DramLogSetDramAddrHigh         0x28
#घोषणा PPSMC_MSG_DramLogSetDramAddrLow          0x29
#घोषणा PPSMC_MSG_DramLogSetDramSize             0x2A
#घोषणा PPSMC_MSG_GetDebugData                   0x2B
#घोषणा PPSMC_MSG_WaflTest                       0x2C
#घोषणा PPSMC_MSG_spare7                         0x2D
#घोषणा PPSMC_MSG_SetMemoryChannelEnable         0x2E
#घोषणा PPSMC_MSG_SetNumBadHbmPagesRetired       0x2F
#घोषणा PPSMC_MSG_DFCstateControl                0x32
#घोषणा PPSMC_MSG_GetGmiPwrDnHyst                0x33
#घोषणा PPSMC_MSG_SetGmiPwrDnHyst                0x34
#घोषणा PPSMC_MSG_GmiPwrDnControl                0x35
#घोषणा PPSMC_MSG_EnterGfxoff                    0x36
#घोषणा PPSMC_MSG_ExitGfxoff                     0x37
#घोषणा PPSMC_MSG_SetExecuteDMATest              0x38
#घोषणा PPSMC_MSG_EnableDeterminism              0x39
#घोषणा PPSMC_MSG_DisableDeterminism             0x3A
#घोषणा PPSMC_MSG_SetUclkDpmMode                 0x3B

//STB to dram log
#घोषणा PPSMC_MSG_DumpSTBtoDram                     0x3C
#घोषणा PPSMC_MSG_STBtoDramLogSetDramAddrHigh       0x3D
#घोषणा PPSMC_MSG_STBtoDramLogSetDramAddrLow        0x3E
#घोषणा PPSMC_MSG_STBtoDramLogSetDramSize           0x3F
#घोषणा PPSMC_MSG_SetSystemVirtualSTBtoDramAddrHigh 0x40
#घोषणा PPSMC_MSG_SetSystemVirtualSTBtoDramAddrLow  0x41

#घोषणा PPSMC_MSG_GfxDriverResetRecovery	0x42
#घोषणा PPSMC_Message_Count			0x43

//PPSMC Reset Types
#घोषणा PPSMC_RESET_TYPE_WARM_RESET              0x00
#घोषणा PPSMC_RESET_TYPE_DRIVER_MODE_1_RESET     0x01 //driver msg argument should be 1 क्रम mode-1
#घोषणा PPSMC_RESET_TYPE_DRIVER_MODE_2_RESET     0x02 //and 2 क्रम mode-2
#घोषणा PPSMC_RESET_TYPE_PCIE_LINK_RESET         0x03
#घोषणा PPSMC_RESET_TYPE_BIF_LINK_RESET          0x04
#घोषणा PPSMC_RESET_TYPE_PF0_FLR_RESET           0x05


प्रकार क्रमागत अणु
  GFXOFF_ERROR_NO_ERROR,
  GFXOFF_ERROR_DISALLOWED,
  GFXOFF_ERROR_GFX_BUSY,
  GFXOFF_ERROR_GFX_OFF,
  GFXOFF_ERROR_GFX_ON,
पूर्ण GFXOFF_ERROR_e;

प्रकार uपूर्णांक32_t PPSMC_Result;
प्रकार uपूर्णांक32_t PPSMC_Msg;
#आशय pack(pop)

#पूर्ण_अगर
