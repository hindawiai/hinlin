<शैली गुरु>
/*
 *
 * Copyright (C) 2016 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित SMU_6_0_D_H
#घोषणा SMU_6_0_D_H

#घोषणा ixLCAC_MC0_CNTL 0x011C
#घोषणा ixLCAC_MC0_OVR_SEL 0x011D
#घोषणा ixLCAC_MC0_OVR_VAL 0x011E
#घोषणा ixLCAC_MC1_CNTL 0x011F
#घोषणा ixLCAC_MC1_OVR_SEL 0x0120
#घोषणा ixLCAC_MC1_OVR_VAL 0x0121
#घोषणा ixLCAC_MC2_CNTL 0x0122
#घोषणा ixLCAC_MC2_OVR_SEL 0x0123
#घोषणा ixLCAC_MC2_OVR_VAL 0x0124
#घोषणा ixLCAC_MC3_CNTL 0x0125
#घोषणा ixLCAC_MC3_OVR_SEL 0x0126
#घोषणा ixLCAC_MC3_OVR_VAL 0x0127
#घोषणा ixLCAC_MC4_CNTL 0x0128
#घोषणा ixLCAC_MC4_OVR_SEL 0x0129
#घोषणा ixLCAC_MC4_OVR_VAL 0x012A
#घोषणा ixLCAC_MC5_CNTL 0x012B
#घोषणा ixLCAC_MC5_OVR_SEL 0x012C
#घोषणा ixLCAC_MC5_OVR_VAL 0x012D
#घोषणा ixSMC_PC_C 0x80000370
#घोषणा ixTHM_TMON0_DEBUG 0x03F0
#घोषणा ixTHM_TMON0_INT_DATA 0x0380
#घोषणा ixTHM_TMON0_RDIL0_DATA 0x0300
#घोषणा ixTHM_TMON0_RDIL10_DATA 0x030A
#घोषणा ixTHM_TMON0_RDIL11_DATA 0x030B
#घोषणा ixTHM_TMON0_RDIL12_DATA 0x030C
#घोषणा ixTHM_TMON0_RDIL13_DATA 0x030D
#घोषणा ixTHM_TMON0_RDIL14_DATA 0x030E
#घोषणा ixTHM_TMON0_RDIL15_DATA 0x030F
#घोषणा ixTHM_TMON0_RDIL1_DATA 0x0301
#घोषणा ixTHM_TMON0_RDIL2_DATA 0x0302
#घोषणा ixTHM_TMON0_RDIL3_DATA 0x0303
#घोषणा ixTHM_TMON0_RDIL4_DATA 0x0304
#घोषणा ixTHM_TMON0_RDIL5_DATA 0x0305
#घोषणा ixTHM_TMON0_RDIL6_DATA 0x0306
#घोषणा ixTHM_TMON0_RDIL7_DATA 0x0307
#घोषणा ixTHM_TMON0_RDIL8_DATA 0x0308
#घोषणा ixTHM_TMON0_RDIL9_DATA 0x0309
#घोषणा ixTHM_TMON0_Rसूची0_DATA 0x0310
#घोषणा ixTHM_TMON0_Rसूची10_DATA 0x031A
#घोषणा ixTHM_TMON0_Rसूची11_DATA 0x031B
#घोषणा ixTHM_TMON0_Rसूची12_DATA 0x031C
#घोषणा ixTHM_TMON0_Rसूची13_DATA 0x031D
#घोषणा ixTHM_TMON0_Rसूची14_DATA 0x031E
#घोषणा ixTHM_TMON0_Rसूची15_DATA 0x031F
#घोषणा ixTHM_TMON0_Rसूची1_DATA 0x0311
#घोषणा ixTHM_TMON0_Rसूची2_DATA 0x0312
#घोषणा ixTHM_TMON0_Rसूची3_DATA 0x0313
#घोषणा ixTHM_TMON0_Rसूची4_DATA 0x0314
#घोषणा ixTHM_TMON0_Rसूची5_DATA 0x0315
#घोषणा ixTHM_TMON0_Rसूची6_DATA 0x0316
#घोषणा ixTHM_TMON0_Rसूची7_DATA 0x0317
#घोषणा ixTHM_TMON0_Rसूची8_DATA 0x0318
#घोषणा ixTHM_TMON0_Rसूची9_DATA 0x0319
#घोषणा ixTHM_TMON1_DEBUG 0x03F1
#घोषणा ixTHM_TMON1_INT_DATA 0x0381
#घोषणा ixTHM_TMON1_RDIL0_DATA 0x0320
#घोषणा ixTHM_TMON1_RDIL10_DATA 0x032A
#घोषणा ixTHM_TMON1_RDIL11_DATA 0x032B
#घोषणा ixTHM_TMON1_RDIL12_DATA 0x032C
#घोषणा ixTHM_TMON1_RDIL13_DATA 0x032D
#घोषणा ixTHM_TMON1_RDIL14_DATA 0x032E
#घोषणा ixTHM_TMON1_RDIL15_DATA 0x032F
#घोषणा ixTHM_TMON1_RDIL1_DATA 0x0321
#घोषणा ixTHM_TMON1_RDIL2_DATA 0x0322
#घोषणा ixTHM_TMON1_RDIL3_DATA 0x0323
#घोषणा ixTHM_TMON1_RDIL4_DATA 0x0324
#घोषणा ixTHM_TMON1_RDIL5_DATA 0x0325
#घोषणा ixTHM_TMON1_RDIL6_DATA 0x0326
#घोषणा ixTHM_TMON1_RDIL7_DATA 0x0327
#घोषणा ixTHM_TMON1_RDIL8_DATA 0x0328
#घोषणा ixTHM_TMON1_RDIL9_DATA 0x0329
#घोषणा ixTHM_TMON1_Rसूची0_DATA 0x0330
#घोषणा ixTHM_TMON1_Rसूची10_DATA 0x033A
#घोषणा ixTHM_TMON1_Rसूची11_DATA 0x033B
#घोषणा ixTHM_TMON1_Rसूची12_DATA 0x033C
#घोषणा ixTHM_TMON1_Rसूची13_DATA 0x033D
#घोषणा ixTHM_TMON1_Rसूची14_DATA 0x033E
#घोषणा ixTHM_TMON1_Rसूची15_DATA 0x033F
#घोषणा ixTHM_TMON1_Rसूची1_DATA 0x0331
#घोषणा ixTHM_TMON1_Rसूची2_DATA 0x0332
#घोषणा ixTHM_TMON1_Rसूची3_DATA 0x0333
#घोषणा ixTHM_TMON1_Rसूची4_DATA 0x0334
#घोषणा ixTHM_TMON1_Rसूची5_DATA 0x0335
#घोषणा ixTHM_TMON1_Rसूची6_DATA 0x0336
#घोषणा ixTHM_TMON1_Rसूची7_DATA 0x0337
#घोषणा ixTHM_TMON1_Rसूची8_DATA 0x0338
#घोषणा ixTHM_TMON1_Rसूची9_DATA 0x0339
#घोषणा mmGPIOPAD_A 0x05E7
#घोषणा mmGPIOPAD_EN 0x05E8
#घोषणा mmGPIOPAD_EXTERN_TRIG_CNTL 0x05F1
#घोषणा mmGPIOPAD_INT_EN 0x05EE
#घोषणा mmGPIOPAD_INT_POLARITY 0x05F0
#घोषणा mmGPIOPAD_INT_STAT 0x05EC
#घोषणा mmGPIOPAD_INT_STAT_AK 0x05ED
#घोषणा mmGPIOPAD_INT_STAT_EN 0x05EB
#घोषणा mmGPIOPAD_INT_TYPE 0x05EF
#घोषणा mmGPIOPAD_MASK 0x05E6
#घोषणा mmGPIOPAD_PD_EN 0x05F4
#घोषणा mmGPIOPAD_PINSTRAPS 0x05EA
#घोषणा mmGPIOPAD_PU_EN 0x05F3
#घोषणा mmGPIOPAD_RCVR_SEL 0x05F2
#घोषणा mmGPIOPAD_STRENGTH 0x05E5
#घोषणा mmGPIOPAD_SW_INT_STAT 0x05E4
#घोषणा mmGPIOPAD_Y 0x05E9
#घोषणा mmSMC_IND_ACCESS_CNTL 0x008A
#घोषणा mmSMC_IND_DATA_0 0x0081
#घोषणा mmSMC_IND_DATA 0x0081
#घोषणा mmSMC_IND_DATA_1 0x0083
#घोषणा mmSMC_IND_DATA_2 0x0085
#घोषणा mmSMC_IND_DATA_3 0x0087
#घोषणा mmSMC_IND_INDEX_0 0x0080
#घोषणा mmSMC_IND_INDEX 0x0080
#घोषणा mmSMC_IND_INDEX_1 0x0082
#घोषणा mmSMC_IND_INDEX_2 0x0084
#घोषणा mmSMC_IND_INDEX_3 0x0086
#घोषणा mmSMC_MESSAGE_0 0x008B
#घोषणा mmSMC_MESSAGE_1 0x008D
#घोषणा mmSMC_MESSAGE_2 0x008F
#घोषणा mmSMC_RESP_0 0x008C
#घोषणा mmSMC_RESP_1 0x008E
#घोषणा mmSMC_RESP_2 0x0090

#पूर्ण_अगर
