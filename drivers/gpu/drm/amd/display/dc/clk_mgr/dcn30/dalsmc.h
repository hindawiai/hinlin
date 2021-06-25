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
 * Authors: AMD
 *
 */

// TEMPORARY until this exists in the proper location
#अगर_अघोषित DALSMC_H
#घोषणा DALSMC_H

#घोषणा DALSMC_VERSION 0x1

// SMU Response Codes:
#घोषणा DALSMC_Result_OK                   0x1
#घोषणा DALSMC_Result_Failed               0xFF
#घोषणा DALSMC_Result_UnknownCmd           0xFE
#घोषणा DALSMC_Result_CmdRejectedPrereq    0xFD
#घोषणा DALSMC_Result_CmdRejectedBusy      0xFC



// Message Definitions:
#घोषणा DALSMC_MSG_TestMessage                    0x1
#घोषणा DALSMC_MSG_GetSmuVersion                  0x2
#घोषणा DALSMC_MSG_GetDriverIfVersion             0x3
#घोषणा DALSMC_MSG_GetMsgHeaderVersion            0x4
#घोषणा DALSMC_MSG_SetDalDramAddrHigh             0x5
#घोषणा DALSMC_MSG_SetDalDramAddrLow              0x6
#घोषणा DALSMC_MSG_TransferTableSmu2Dram          0x7
#घोषणा DALSMC_MSG_TransferTableDram2Smu          0x8
#घोषणा DALSMC_MSG_SetHardMinByFreq               0x9
#घोषणा DALSMC_MSG_SetHardMaxByFreq               0xA
#घोषणा DALSMC_MSG_GetDpmFreqByIndex              0xB
#घोषणा DALSMC_MSG_GetDcModeMaxDpmFreq            0xC
#घोषणा DALSMC_MSG_SetMinDeepSleepDcefclk         0xD
#घोषणा DALSMC_MSG_NumOfDisplays                  0xE
#घोषणा DALSMC_MSG_SetDisplayRefreshFromMall      0xF
#घोषणा DALSMC_MSG_SetExternalClientDfCstateAllow 0x10
#घोषणा DALSMC_MSG_BacoAudioD3PME                 0x11
#घोषणा DALSMC_Message_Count                      0x12

#पूर्ण_अगर
