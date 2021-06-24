<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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

#अगर_अघोषित ARCTURUS_PP_SMC_H
#घोषणा ARCTURUS_PP_SMC_H

#आशय pack(push, 1)

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
#घोषणा PPSMC_MSG_GetEnabledSmuFeaturesLow       0xC
#घोषणा PPSMC_MSG_GetEnabledSmuFeaturesHigh      0xD
#घोषणा PPSMC_MSG_SetDriverDramAddrHigh          0xE
#घोषणा PPSMC_MSG_SetDriverDramAddrLow           0xF
#घोषणा PPSMC_MSG_SetToolsDramAddrHigh           0x10
#घोषणा PPSMC_MSG_SetToolsDramAddrLow            0x11
#घोषणा PPSMC_MSG_TransferTableSmu2Dram          0x12
#घोषणा PPSMC_MSG_TransferTableDram2Smu          0x13
#घोषणा PPSMC_MSG_UseDefaultPPTable              0x14
#घोषणा PPSMC_MSG_UseBackupPPTable               0x15
#घोषणा PPSMC_MSG_SetSystemVirtualDramAddrHigh   0x16
#घोषणा PPSMC_MSG_SetSystemVirtualDramAddrLow    0x17

//BACO/BAMACO/BOMACO
#घोषणा PPSMC_MSG_EnterBaco                      0x18
#घोषणा PPSMC_MSG_ExitBaco                       0x19
#घोषणा PPSMC_MSG_ArmD3                          0x1A

//DPM
#घोषणा PPSMC_MSG_SetSoftMinByFreq               0x1B
#घोषणा PPSMC_MSG_SetSoftMaxByFreq               0x1C
#घोषणा PPSMC_MSG_SetHardMinByFreq               0x1D
#घोषणा PPSMC_MSG_SetHardMaxByFreq               0x1E
#घोषणा PPSMC_MSG_GetMinDpmFreq                  0x1F
#घोषणा PPSMC_MSG_GetMaxDpmFreq                  0x20
#घोषणा PPSMC_MSG_GetDpmFreqByIndex              0x21

#घोषणा PPSMC_MSG_SetWorkloadMask                0x22
#घोषणा PPSMC_MSG_SetDfSwitchType                0x23
#घोषणा PPSMC_MSG_GetVoltageByDpm                0x24
#घोषणा PPSMC_MSG_GetVoltageByDpmOverdrive       0x25

#घोषणा PPSMC_MSG_SetPptLimit                    0x26
#घोषणा PPSMC_MSG_GetPptLimit                    0x27

//Power Gating
#घोषणा PPSMC_MSG_PowerUpVcn0                    0x28
#घोषणा PPSMC_MSG_PowerDownVcn0                  0x29
#घोषणा PPSMC_MSG_PowerUpVcn1                    0x2A
#घोषणा PPSMC_MSG_PowerDownVcn1                  0x2B

//Resets and reload
#घोषणा PPSMC_MSG_PrepareMp1ForUnload            0x2C
#घोषणा PPSMC_MSG_PrepareMp1ForReset             0x2D
#घोषणा PPSMC_MSG_PrepareMp1ForShutकरोwn          0x2E
#घोषणा PPSMC_MSG_SoftReset                      0x2F

//BTC
#घोषणा PPSMC_MSG_RunAfllBtc                     0x30
#घोषणा PPSMC_MSG_RunDcBtc                       0x31

//Debug
#घोषणा PPSMC_MSG_DramLogSetDramAddrHigh         0x33
#घोषणा PPSMC_MSG_DramLogSetDramAddrLow          0x34
#घोषणा PPSMC_MSG_DramLogSetDramSize             0x35
#घोषणा PPSMC_MSG_GetDebugData                   0x36

//WAFL and XGMI
#घोषणा PPSMC_MSG_WaflTest                       0x37
#घोषणा PPSMC_MSG_SetXgmiMode                    0x38

//Others
#घोषणा PPSMC_MSG_SetMemoryChannelEnable         0x39

//OOB
#घोषणा PPSMC_MSG_SetNumBadHbmPagesRetired	 0x3A

#घोषणा PPSMC_MSG_DFCstateControl		 0x3B
#घोषणा PPSMC_MSG_GmiPwrDnControl                0x3D
#घोषणा PPSMC_Message_Count                      0x3E

#घोषणा PPSMC_MSG_ReadSerialNumTop32		 0x40
#घोषणा PPSMC_MSG_ReadSerialNumBottom32		 0x41

/* paramater क्रम MSG_LightSBR
 * 1 -- Enable light secondary bus reset, only करो nbio respond without further handling,
 *      leave driver to handle the real reset
 * 0 -- Disable LightSBR, शेष behavior, SMU will pass the reset to PSP
 */
#घोषणा PPSMC_MSG_LightSBR			 0x42

प्रकार uपूर्णांक32_t PPSMC_Result;
प्रकार uपूर्णांक32_t PPSMC_Msg;
#आशय pack(pop)

#पूर्ण_अगर
