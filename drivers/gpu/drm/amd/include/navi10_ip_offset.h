<शैली गुरु>
/*
 * Copyright (C) 2019  Advanced Micro Devices, Inc.
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
#अगर_अघोषित _navi10_ip_offset_HEADER
#घोषणा _navi10_ip_offset_HEADER

#घोषणा MAX_INSTANCE                                       6
#घोषणा MAX_SEGMENT                                        6


काष्ठा IP_BASE_INSTANCE अणु
	अचिन्हित पूर्णांक segment[MAX_SEGMENT];
पूर्ण;
 
काष्ठा IP_BASE अणु
	काष्ठा IP_BASE_INSTANCE instance[MAX_INSTANCE];
पूर्ण __maybe_unused;


अटल स्थिर काष्ठा IP_BASE ATHUB_BASE            =अणु अणु अणु अणु 0x00000C00, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE CLK_BASE            =अणु अणु अणु अणु 0x00016C00, 0x00016E00, 0x00017000, 0x00017200, 0x00017E00, 0x0001B000 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE DF_BASE            =अणु अणु अणु अणु 0x00007000, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE DCN_BASE            =अणु अणु अणु अणु 0x00000012, 0x000000C0, 0x000034C0, 0x00009000, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE FUSE_BASE            =अणु अणु अणु अणु 0x00017400, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE GC_BASE            =अणु अणु अणु अणु 0x00001260, 0x0000A000, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE HDP_BASE            =अणु अणु अणु अणु 0x00000F20, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE MMHUB_BASE            =अणु अणु अणु अणु 0x0001A000, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE MP0_BASE            =अणु अणु अणु अणु 0x00016000, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE MP1_BASE            =अणु अणु अणु अणु 0x00016000, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE NBIO_BASE            =अणु अणु अणु अणु 0x00000000, 0x00000014, 0x00000D20, 0x00010400, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE OSSSYS_BASE            =अणु अणु अणु अणु 0x000010A0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE RSMU_BASE			= अणु अणु अणु अणु 0x00012000, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
					अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
					अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
					अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
					अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
					अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE SMUIO_BASE            =अणु अणु अणु अणु 0x00016800, 0x00016A00, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE THM_BASE            =अणु अणु अणु अणु 0x00016600, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE UMC_BASE            =अणु अणु अणु अणु 0x00014000, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE VCN_BASE            =अणु अणु अणु अणु 0x00007800, 0x00007E00, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;


#घोषणा ATHUB_BASE__INST0_SEG0                     0x00000C00
#घोषणा ATHUB_BASE__INST0_SEG1                     0
#घोषणा ATHUB_BASE__INST0_SEG2                     0
#घोषणा ATHUB_BASE__INST0_SEG3                     0
#घोषणा ATHUB_BASE__INST0_SEG4                     0
#घोषणा ATHUB_BASE__INST0_SEG5                     0

#घोषणा ATHUB_BASE__INST1_SEG0                     0
#घोषणा ATHUB_BASE__INST1_SEG1                     0
#घोषणा ATHUB_BASE__INST1_SEG2                     0
#घोषणा ATHUB_BASE__INST1_SEG3                     0
#घोषणा ATHUB_BASE__INST1_SEG4                     0
#घोषणा ATHUB_BASE__INST1_SEG5                     0

#घोषणा ATHUB_BASE__INST2_SEG0                     0
#घोषणा ATHUB_BASE__INST2_SEG1                     0
#घोषणा ATHUB_BASE__INST2_SEG2                     0
#घोषणा ATHUB_BASE__INST2_SEG3                     0
#घोषणा ATHUB_BASE__INST2_SEG4                     0
#घोषणा ATHUB_BASE__INST2_SEG5                     0

#घोषणा ATHUB_BASE__INST3_SEG0                     0
#घोषणा ATHUB_BASE__INST3_SEG1                     0
#घोषणा ATHUB_BASE__INST3_SEG2                     0
#घोषणा ATHUB_BASE__INST3_SEG3                     0
#घोषणा ATHUB_BASE__INST3_SEG4                     0
#घोषणा ATHUB_BASE__INST3_SEG5                     0

#घोषणा ATHUB_BASE__INST4_SEG0                     0
#घोषणा ATHUB_BASE__INST4_SEG1                     0
#घोषणा ATHUB_BASE__INST4_SEG2                     0
#घोषणा ATHUB_BASE__INST4_SEG3                     0
#घोषणा ATHUB_BASE__INST4_SEG4                     0
#घोषणा ATHUB_BASE__INST4_SEG5                     0

#घोषणा ATHUB_BASE__INST5_SEG0                     0
#घोषणा ATHUB_BASE__INST5_SEG1                     0
#घोषणा ATHUB_BASE__INST5_SEG2                     0
#घोषणा ATHUB_BASE__INST5_SEG3                     0
#घोषणा ATHUB_BASE__INST5_SEG4                     0
#घोषणा ATHUB_BASE__INST5_SEG5                     0

#घोषणा CLK_BASE__INST0_SEG0                       0x00016C00
#घोषणा CLK_BASE__INST0_SEG1                       0x00016E00
#घोषणा CLK_BASE__INST0_SEG2                       0x00017000
#घोषणा CLK_BASE__INST0_SEG3                       0x00017200
#घोषणा CLK_BASE__INST0_SEG4                       0x00017E00
#घोषणा CLK_BASE__INST0_SEG5                       0x0001B000

#घोषणा CLK_BASE__INST1_SEG0                       0
#घोषणा CLK_BASE__INST1_SEG1                       0
#घोषणा CLK_BASE__INST1_SEG2                       0
#घोषणा CLK_BASE__INST1_SEG3                       0
#घोषणा CLK_BASE__INST1_SEG4                       0
#घोषणा CLK_BASE__INST1_SEG5                       0

#घोषणा CLK_BASE__INST2_SEG0                       0
#घोषणा CLK_BASE__INST2_SEG1                       0
#घोषणा CLK_BASE__INST2_SEG2                       0
#घोषणा CLK_BASE__INST2_SEG3                       0
#घोषणा CLK_BASE__INST2_SEG4                       0
#घोषणा CLK_BASE__INST2_SEG5                       0

#घोषणा CLK_BASE__INST3_SEG0                       0
#घोषणा CLK_BASE__INST3_SEG1                       0
#घोषणा CLK_BASE__INST3_SEG2                       0
#घोषणा CLK_BASE__INST3_SEG3                       0
#घोषणा CLK_BASE__INST3_SEG4                       0
#घोषणा CLK_BASE__INST3_SEG5                       0

#घोषणा CLK_BASE__INST4_SEG0                       0
#घोषणा CLK_BASE__INST4_SEG1                       0
#घोषणा CLK_BASE__INST4_SEG2                       0
#घोषणा CLK_BASE__INST4_SEG3                       0
#घोषणा CLK_BASE__INST4_SEG4                       0
#घोषणा CLK_BASE__INST4_SEG5                       0

#घोषणा CLK_BASE__INST5_SEG0                       0
#घोषणा CLK_BASE__INST5_SEG1                       0
#घोषणा CLK_BASE__INST5_SEG2                       0
#घोषणा CLK_BASE__INST5_SEG3                       0
#घोषणा CLK_BASE__INST5_SEG4                       0
#घोषणा CLK_BASE__INST5_SEG5                       0

#घोषणा DF_BASE__INST0_SEG0                        0x00007000
#घोषणा DF_BASE__INST0_SEG1                        0
#घोषणा DF_BASE__INST0_SEG2                        0
#घोषणा DF_BASE__INST0_SEG3                        0
#घोषणा DF_BASE__INST0_SEG4                        0
#घोषणा DF_BASE__INST0_SEG5                        0

#घोषणा DF_BASE__INST1_SEG0                        0
#घोषणा DF_BASE__INST1_SEG1                        0
#घोषणा DF_BASE__INST1_SEG2                        0
#घोषणा DF_BASE__INST1_SEG3                        0
#घोषणा DF_BASE__INST1_SEG4                        0
#घोषणा DF_BASE__INST1_SEG5                        0

#घोषणा DF_BASE__INST2_SEG0                        0
#घोषणा DF_BASE__INST2_SEG1                        0
#घोषणा DF_BASE__INST2_SEG2                        0
#घोषणा DF_BASE__INST2_SEG3                        0
#घोषणा DF_BASE__INST2_SEG4                        0
#घोषणा DF_BASE__INST2_SEG5                        0

#घोषणा DF_BASE__INST3_SEG0                        0
#घोषणा DF_BASE__INST3_SEG1                        0
#घोषणा DF_BASE__INST3_SEG2                        0
#घोषणा DF_BASE__INST3_SEG3                        0
#घोषणा DF_BASE__INST3_SEG4                        0
#घोषणा DF_BASE__INST3_SEG5                        0

#घोषणा DF_BASE__INST4_SEG0                        0
#घोषणा DF_BASE__INST4_SEG1                        0
#घोषणा DF_BASE__INST4_SEG2                        0
#घोषणा DF_BASE__INST4_SEG3                        0
#घोषणा DF_BASE__INST4_SEG4                        0
#घोषणा DF_BASE__INST4_SEG5                        0

#घोषणा DF_BASE__INST5_SEG0                        0
#घोषणा DF_BASE__INST5_SEG1                        0
#घोषणा DF_BASE__INST5_SEG2                        0
#घोषणा DF_BASE__INST5_SEG3                        0
#घोषणा DF_BASE__INST5_SEG4                        0
#घोषणा DF_BASE__INST5_SEG5                        0

#घोषणा DCN_BASE__INST0_SEG0                       0x00000012
#घोषणा DCN_BASE__INST0_SEG1                       0x000000C0
#घोषणा DCN_BASE__INST0_SEG2                       0x000034C0
#घोषणा DCN_BASE__INST0_SEG3                       0x00009000
#घोषणा DCN_BASE__INST0_SEG4                       0
#घोषणा DCN_BASE__INST0_SEG5                       0

#घोषणा DCN_BASE__INST1_SEG0                       0
#घोषणा DCN_BASE__INST1_SEG1                       0
#घोषणा DCN_BASE__INST1_SEG2                       0
#घोषणा DCN_BASE__INST1_SEG3                       0
#घोषणा DCN_BASE__INST1_SEG4                       0
#घोषणा DCN_BASE__INST1_SEG5                       0

#घोषणा DCN_BASE__INST2_SEG0                       0
#घोषणा DCN_BASE__INST2_SEG1                       0
#घोषणा DCN_BASE__INST2_SEG2                       0
#घोषणा DCN_BASE__INST2_SEG3                       0
#घोषणा DCN_BASE__INST2_SEG4                       0
#घोषणा DCN_BASE__INST2_SEG5                       0

#घोषणा DCN_BASE__INST3_SEG0                       0
#घोषणा DCN_BASE__INST3_SEG1                       0
#घोषणा DCN_BASE__INST3_SEG2                       0
#घोषणा DCN_BASE__INST3_SEG3                       0
#घोषणा DCN_BASE__INST3_SEG4                       0
#घोषणा DCN_BASE__INST3_SEG5                       0

#घोषणा DCN_BASE__INST4_SEG0                       0
#घोषणा DCN_BASE__INST4_SEG1                       0
#घोषणा DCN_BASE__INST4_SEG2                       0
#घोषणा DCN_BASE__INST4_SEG3                       0
#घोषणा DCN_BASE__INST4_SEG4                       0
#घोषणा DCN_BASE__INST4_SEG5                       0

#घोषणा DCN_BASE__INST5_SEG0                       0
#घोषणा DCN_BASE__INST5_SEG1                       0
#घोषणा DCN_BASE__INST5_SEG2                       0
#घोषणा DCN_BASE__INST5_SEG3                       0
#घोषणा DCN_BASE__INST5_SEG4                       0
#घोषणा DCN_BASE__INST5_SEG5                       0

#घोषणा FUSE_BASE__INST0_SEG0                      0x00017400
#घोषणा FUSE_BASE__INST0_SEG1                      0
#घोषणा FUSE_BASE__INST0_SEG2                      0
#घोषणा FUSE_BASE__INST0_SEG3                      0
#घोषणा FUSE_BASE__INST0_SEG4                      0
#घोषणा FUSE_BASE__INST0_SEG5                      0

#घोषणा FUSE_BASE__INST1_SEG0                      0
#घोषणा FUSE_BASE__INST1_SEG1                      0
#घोषणा FUSE_BASE__INST1_SEG2                      0
#घोषणा FUSE_BASE__INST1_SEG3                      0
#घोषणा FUSE_BASE__INST1_SEG4                      0
#घोषणा FUSE_BASE__INST1_SEG5                      0

#घोषणा FUSE_BASE__INST2_SEG0                      0
#घोषणा FUSE_BASE__INST2_SEG1                      0
#घोषणा FUSE_BASE__INST2_SEG2                      0
#घोषणा FUSE_BASE__INST2_SEG3                      0
#घोषणा FUSE_BASE__INST2_SEG4                      0
#घोषणा FUSE_BASE__INST2_SEG5                      0

#घोषणा FUSE_BASE__INST3_SEG0                      0
#घोषणा FUSE_BASE__INST3_SEG1                      0
#घोषणा FUSE_BASE__INST3_SEG2                      0
#घोषणा FUSE_BASE__INST3_SEG3                      0
#घोषणा FUSE_BASE__INST3_SEG4                      0
#घोषणा FUSE_BASE__INST3_SEG5                      0

#घोषणा FUSE_BASE__INST4_SEG0                      0
#घोषणा FUSE_BASE__INST4_SEG1                      0
#घोषणा FUSE_BASE__INST4_SEG2                      0
#घोषणा FUSE_BASE__INST4_SEG3                      0
#घोषणा FUSE_BASE__INST4_SEG4                      0
#घोषणा FUSE_BASE__INST4_SEG5                      0

#घोषणा FUSE_BASE__INST5_SEG0                      0
#घोषणा FUSE_BASE__INST5_SEG1                      0
#घोषणा FUSE_BASE__INST5_SEG2                      0
#घोषणा FUSE_BASE__INST5_SEG3                      0
#घोषणा FUSE_BASE__INST5_SEG4                      0
#घोषणा FUSE_BASE__INST5_SEG5                      0

#घोषणा GC_BASE__INST0_SEG0                        0x00001260
#घोषणा GC_BASE__INST0_SEG1                        0x0000A000
#घोषणा GC_BASE__INST0_SEG2                        0
#घोषणा GC_BASE__INST0_SEG3                        0
#घोषणा GC_BASE__INST0_SEG4                        0
#घोषणा GC_BASE__INST0_SEG5                        0

#घोषणा GC_BASE__INST1_SEG0                        0
#घोषणा GC_BASE__INST1_SEG1                        0
#घोषणा GC_BASE__INST1_SEG2                        0
#घोषणा GC_BASE__INST1_SEG3                        0
#घोषणा GC_BASE__INST1_SEG4                        0
#घोषणा GC_BASE__INST1_SEG5                        0

#घोषणा GC_BASE__INST2_SEG0                        0
#घोषणा GC_BASE__INST2_SEG1                        0
#घोषणा GC_BASE__INST2_SEG2                        0
#घोषणा GC_BASE__INST2_SEG3                        0
#घोषणा GC_BASE__INST2_SEG4                        0
#घोषणा GC_BASE__INST2_SEG5                        0

#घोषणा GC_BASE__INST3_SEG0                        0
#घोषणा GC_BASE__INST3_SEG1                        0
#घोषणा GC_BASE__INST3_SEG2                        0
#घोषणा GC_BASE__INST3_SEG3                        0
#घोषणा GC_BASE__INST3_SEG4                        0
#घोषणा GC_BASE__INST3_SEG5                        0

#घोषणा GC_BASE__INST4_SEG0                        0
#घोषणा GC_BASE__INST4_SEG1                        0
#घोषणा GC_BASE__INST4_SEG2                        0
#घोषणा GC_BASE__INST4_SEG3                        0
#घोषणा GC_BASE__INST4_SEG4                        0
#घोषणा GC_BASE__INST4_SEG5                        0

#घोषणा GC_BASE__INST5_SEG0                        0
#घोषणा GC_BASE__INST5_SEG1                        0
#घोषणा GC_BASE__INST5_SEG2                        0
#घोषणा GC_BASE__INST5_SEG3                        0
#घोषणा GC_BASE__INST5_SEG4                        0
#घोषणा GC_BASE__INST5_SEG5                        0

#घोषणा HDP_BASE__INST0_SEG0                       0x00000F20
#घोषणा HDP_BASE__INST0_SEG1                       0
#घोषणा HDP_BASE__INST0_SEG2                       0
#घोषणा HDP_BASE__INST0_SEG3                       0
#घोषणा HDP_BASE__INST0_SEG4                       0
#घोषणा HDP_BASE__INST0_SEG5                       0

#घोषणा HDP_BASE__INST1_SEG0                       0
#घोषणा HDP_BASE__INST1_SEG1                       0
#घोषणा HDP_BASE__INST1_SEG2                       0
#घोषणा HDP_BASE__INST1_SEG3                       0
#घोषणा HDP_BASE__INST1_SEG4                       0
#घोषणा HDP_BASE__INST1_SEG5                       0

#घोषणा HDP_BASE__INST2_SEG0                       0
#घोषणा HDP_BASE__INST2_SEG1                       0
#घोषणा HDP_BASE__INST2_SEG2                       0
#घोषणा HDP_BASE__INST2_SEG3                       0
#घोषणा HDP_BASE__INST2_SEG4                       0
#घोषणा HDP_BASE__INST2_SEG5                       0

#घोषणा HDP_BASE__INST3_SEG0                       0
#घोषणा HDP_BASE__INST3_SEG1                       0
#घोषणा HDP_BASE__INST3_SEG2                       0
#घोषणा HDP_BASE__INST3_SEG3                       0
#घोषणा HDP_BASE__INST3_SEG4                       0
#घोषणा HDP_BASE__INST3_SEG5                       0

#घोषणा HDP_BASE__INST4_SEG0                       0
#घोषणा HDP_BASE__INST4_SEG1                       0
#घोषणा HDP_BASE__INST4_SEG2                       0
#घोषणा HDP_BASE__INST4_SEG3                       0
#घोषणा HDP_BASE__INST4_SEG4                       0
#घोषणा HDP_BASE__INST4_SEG5                       0

#घोषणा HDP_BASE__INST5_SEG0                       0
#घोषणा HDP_BASE__INST5_SEG1                       0
#घोषणा HDP_BASE__INST5_SEG2                       0
#घोषणा HDP_BASE__INST5_SEG3                       0
#घोषणा HDP_BASE__INST5_SEG4                       0
#घोषणा HDP_BASE__INST5_SEG5                       0

#घोषणा MMHUB_BASE__INST0_SEG0                     0x0001A000
#घोषणा MMHUB_BASE__INST0_SEG1                     0
#घोषणा MMHUB_BASE__INST0_SEG2                     0
#घोषणा MMHUB_BASE__INST0_SEG3                     0
#घोषणा MMHUB_BASE__INST0_SEG4                     0
#घोषणा MMHUB_BASE__INST0_SEG5                     0

#घोषणा MMHUB_BASE__INST1_SEG0                     0
#घोषणा MMHUB_BASE__INST1_SEG1                     0
#घोषणा MMHUB_BASE__INST1_SEG2                     0
#घोषणा MMHUB_BASE__INST1_SEG3                     0
#घोषणा MMHUB_BASE__INST1_SEG4                     0
#घोषणा MMHUB_BASE__INST1_SEG5                     0

#घोषणा MMHUB_BASE__INST2_SEG0                     0
#घोषणा MMHUB_BASE__INST2_SEG1                     0
#घोषणा MMHUB_BASE__INST2_SEG2                     0
#घोषणा MMHUB_BASE__INST2_SEG3                     0
#घोषणा MMHUB_BASE__INST2_SEG4                     0
#घोषणा MMHUB_BASE__INST2_SEG5                     0

#घोषणा MMHUB_BASE__INST3_SEG0                     0
#घोषणा MMHUB_BASE__INST3_SEG1                     0
#घोषणा MMHUB_BASE__INST3_SEG2                     0
#घोषणा MMHUB_BASE__INST3_SEG3                     0
#घोषणा MMHUB_BASE__INST3_SEG4                     0
#घोषणा MMHUB_BASE__INST3_SEG5                     0

#घोषणा MMHUB_BASE__INST4_SEG0                     0
#घोषणा MMHUB_BASE__INST4_SEG1                     0
#घोषणा MMHUB_BASE__INST4_SEG2                     0
#घोषणा MMHUB_BASE__INST4_SEG3                     0
#घोषणा MMHUB_BASE__INST4_SEG4                     0
#घोषणा MMHUB_BASE__INST4_SEG5                     0

#घोषणा MMHUB_BASE__INST5_SEG0                     0
#घोषणा MMHUB_BASE__INST5_SEG1                     0
#घोषणा MMHUB_BASE__INST5_SEG2                     0
#घोषणा MMHUB_BASE__INST5_SEG3                     0
#घोषणा MMHUB_BASE__INST5_SEG4                     0
#घोषणा MMHUB_BASE__INST5_SEG5                     0

#घोषणा MP0_BASE__INST0_SEG0                       0x00016000
#घोषणा MP0_BASE__INST0_SEG1                       0
#घोषणा MP0_BASE__INST0_SEG2                       0
#घोषणा MP0_BASE__INST0_SEG3                       0
#घोषणा MP0_BASE__INST0_SEG4                       0
#घोषणा MP0_BASE__INST0_SEG5                       0

#घोषणा MP0_BASE__INST1_SEG0                       0
#घोषणा MP0_BASE__INST1_SEG1                       0
#घोषणा MP0_BASE__INST1_SEG2                       0
#घोषणा MP0_BASE__INST1_SEG3                       0
#घोषणा MP0_BASE__INST1_SEG4                       0
#घोषणा MP0_BASE__INST1_SEG5                       0

#घोषणा MP0_BASE__INST2_SEG0                       0
#घोषणा MP0_BASE__INST2_SEG1                       0
#घोषणा MP0_BASE__INST2_SEG2                       0
#घोषणा MP0_BASE__INST2_SEG3                       0
#घोषणा MP0_BASE__INST2_SEG4                       0
#घोषणा MP0_BASE__INST2_SEG5                       0

#घोषणा MP0_BASE__INST3_SEG0                       0
#घोषणा MP0_BASE__INST3_SEG1                       0
#घोषणा MP0_BASE__INST3_SEG2                       0
#घोषणा MP0_BASE__INST3_SEG3                       0
#घोषणा MP0_BASE__INST3_SEG4                       0
#घोषणा MP0_BASE__INST3_SEG5                       0

#घोषणा MP0_BASE__INST4_SEG0                       0
#घोषणा MP0_BASE__INST4_SEG1                       0
#घोषणा MP0_BASE__INST4_SEG2                       0
#घोषणा MP0_BASE__INST4_SEG3                       0
#घोषणा MP0_BASE__INST4_SEG4                       0
#घोषणा MP0_BASE__INST4_SEG5                       0

#घोषणा MP0_BASE__INST5_SEG0                       0
#घोषणा MP0_BASE__INST5_SEG1                       0
#घोषणा MP0_BASE__INST5_SEG2                       0
#घोषणा MP0_BASE__INST5_SEG3                       0
#घोषणा MP0_BASE__INST5_SEG4                       0
#घोषणा MP0_BASE__INST5_SEG5                       0

#घोषणा MP1_BASE__INST0_SEG0                       0x00016000
#घोषणा MP1_BASE__INST0_SEG1                       0
#घोषणा MP1_BASE__INST0_SEG2                       0
#घोषणा MP1_BASE__INST0_SEG3                       0
#घोषणा MP1_BASE__INST0_SEG4                       0
#घोषणा MP1_BASE__INST0_SEG5                       0

#घोषणा MP1_BASE__INST1_SEG0                       0
#घोषणा MP1_BASE__INST1_SEG1                       0
#घोषणा MP1_BASE__INST1_SEG2                       0
#घोषणा MP1_BASE__INST1_SEG3                       0
#घोषणा MP1_BASE__INST1_SEG4                       0
#घोषणा MP1_BASE__INST1_SEG5                       0

#घोषणा MP1_BASE__INST2_SEG0                       0
#घोषणा MP1_BASE__INST2_SEG1                       0
#घोषणा MP1_BASE__INST2_SEG2                       0
#घोषणा MP1_BASE__INST2_SEG3                       0
#घोषणा MP1_BASE__INST2_SEG4                       0
#घोषणा MP1_BASE__INST2_SEG5                       0

#घोषणा MP1_BASE__INST3_SEG0                       0
#घोषणा MP1_BASE__INST3_SEG1                       0
#घोषणा MP1_BASE__INST3_SEG2                       0
#घोषणा MP1_BASE__INST3_SEG3                       0
#घोषणा MP1_BASE__INST3_SEG4                       0
#घोषणा MP1_BASE__INST3_SEG5                       0

#घोषणा MP1_BASE__INST4_SEG0                       0
#घोषणा MP1_BASE__INST4_SEG1                       0
#घोषणा MP1_BASE__INST4_SEG2                       0
#घोषणा MP1_BASE__INST4_SEG3                       0
#घोषणा MP1_BASE__INST4_SEG4                       0
#घोषणा MP1_BASE__INST4_SEG5                       0

#घोषणा MP1_BASE__INST5_SEG0                       0
#घोषणा MP1_BASE__INST5_SEG1                       0
#घोषणा MP1_BASE__INST5_SEG2                       0
#घोषणा MP1_BASE__INST5_SEG3                       0
#घोषणा MP1_BASE__INST5_SEG4                       0
#घोषणा MP1_BASE__INST5_SEG5                       0

#घोषणा NBIO_BASE__INST0_SEG0                      0x00000000
#घोषणा NBIO_BASE__INST0_SEG1                      0x00000014
#घोषणा NBIO_BASE__INST0_SEG2                      0x00000D20
#घोषणा NBIO_BASE__INST0_SEG3                      0x00010400
#घोषणा NBIO_BASE__INST0_SEG4                      0
#घोषणा NBIO_BASE__INST0_SEG5                      0

#घोषणा NBIO_BASE__INST1_SEG0                      0
#घोषणा NBIO_BASE__INST1_SEG1                      0
#घोषणा NBIO_BASE__INST1_SEG2                      0
#घोषणा NBIO_BASE__INST1_SEG3                      0
#घोषणा NBIO_BASE__INST1_SEG4                      0
#घोषणा NBIO_BASE__INST1_SEG5                      0

#घोषणा NBIO_BASE__INST2_SEG0                      0
#घोषणा NBIO_BASE__INST2_SEG1                      0
#घोषणा NBIO_BASE__INST2_SEG2                      0
#घोषणा NBIO_BASE__INST2_SEG3                      0
#घोषणा NBIO_BASE__INST2_SEG4                      0
#घोषणा NBIO_BASE__INST2_SEG5                      0

#घोषणा NBIO_BASE__INST3_SEG0                      0
#घोषणा NBIO_BASE__INST3_SEG1                      0
#घोषणा NBIO_BASE__INST3_SEG2                      0
#घोषणा NBIO_BASE__INST3_SEG3                      0
#घोषणा NBIO_BASE__INST3_SEG4                      0
#घोषणा NBIO_BASE__INST3_SEG5                      0

#घोषणा NBIO_BASE__INST4_SEG0                      0
#घोषणा NBIO_BASE__INST4_SEG1                      0
#घोषणा NBIO_BASE__INST4_SEG2                      0
#घोषणा NBIO_BASE__INST4_SEG3                      0
#घोषणा NBIO_BASE__INST4_SEG4                      0
#घोषणा NBIO_BASE__INST4_SEG5                      0

#घोषणा NBIO_BASE__INST5_SEG0                      0
#घोषणा NBIO_BASE__INST5_SEG1                      0
#घोषणा NBIO_BASE__INST5_SEG2                      0
#घोषणा NBIO_BASE__INST5_SEG3                      0
#घोषणा NBIO_BASE__INST5_SEG4                      0
#घोषणा NBIO_BASE__INST5_SEG5                      0

#घोषणा OSSSYS_BASE__INST0_SEG0                    0x000010A0
#घोषणा OSSSYS_BASE__INST0_SEG1                    0
#घोषणा OSSSYS_BASE__INST0_SEG2                    0
#घोषणा OSSSYS_BASE__INST0_SEG3                    0
#घोषणा OSSSYS_BASE__INST0_SEG4                    0
#घोषणा OSSSYS_BASE__INST0_SEG5                    0

#घोषणा OSSSYS_BASE__INST1_SEG0                    0
#घोषणा OSSSYS_BASE__INST1_SEG1                    0
#घोषणा OSSSYS_BASE__INST1_SEG2                    0
#घोषणा OSSSYS_BASE__INST1_SEG3                    0
#घोषणा OSSSYS_BASE__INST1_SEG4                    0
#घोषणा OSSSYS_BASE__INST1_SEG5                    0

#घोषणा OSSSYS_BASE__INST2_SEG0                    0
#घोषणा OSSSYS_BASE__INST2_SEG1                    0
#घोषणा OSSSYS_BASE__INST2_SEG2                    0
#घोषणा OSSSYS_BASE__INST2_SEG3                    0
#घोषणा OSSSYS_BASE__INST2_SEG4                    0
#घोषणा OSSSYS_BASE__INST2_SEG5                    0

#घोषणा OSSSYS_BASE__INST3_SEG0                    0
#घोषणा OSSSYS_BASE__INST3_SEG1                    0
#घोषणा OSSSYS_BASE__INST3_SEG2                    0
#घोषणा OSSSYS_BASE__INST3_SEG3                    0
#घोषणा OSSSYS_BASE__INST3_SEG4                    0
#घोषणा OSSSYS_BASE__INST3_SEG5                    0

#घोषणा OSSSYS_BASE__INST4_SEG0                    0
#घोषणा OSSSYS_BASE__INST4_SEG1                    0
#घोषणा OSSSYS_BASE__INST4_SEG2                    0
#घोषणा OSSSYS_BASE__INST4_SEG3                    0
#घोषणा OSSSYS_BASE__INST4_SEG4                    0
#घोषणा OSSSYS_BASE__INST4_SEG5                    0

#घोषणा OSSSYS_BASE__INST5_SEG0                    0
#घोषणा OSSSYS_BASE__INST5_SEG1                    0
#घोषणा OSSSYS_BASE__INST5_SEG2                    0
#घोषणा OSSSYS_BASE__INST5_SEG3                    0
#घोषणा OSSSYS_BASE__INST5_SEG4                    0
#घोषणा OSSSYS_BASE__INST5_SEG5                    0

#घोषणा RSMU_BASE__INST0_SEG0                      0x00012000
#घोषणा RSMU_BASE__INST0_SEG1                      0
#घोषणा RSMU_BASE__INST0_SEG2                      0
#घोषणा RSMU_BASE__INST0_SEG3                      0
#घोषणा RSMU_BASE__INST0_SEG4                      0
#घोषणा RSMU_BASE__INST0_SEG5                      0

#घोषणा RSMU_BASE__INST1_SEG0                      0
#घोषणा RSMU_BASE__INST1_SEG1                      0
#घोषणा RSMU_BASE__INST1_SEG2                      0
#घोषणा RSMU_BASE__INST1_SEG3                      0
#घोषणा RSMU_BASE__INST1_SEG4                      0
#घोषणा RSMU_BASE__INST1_SEG5                      0

#घोषणा RSMU_BASE__INST2_SEG0                      0
#घोषणा RSMU_BASE__INST2_SEG1                      0
#घोषणा RSMU_BASE__INST2_SEG2                      0
#घोषणा RSMU_BASE__INST2_SEG3                      0
#घोषणा RSMU_BASE__INST2_SEG4                      0
#घोषणा RSMU_BASE__INST2_SEG5                      0

#घोषणा RSMU_BASE__INST3_SEG0                      0
#घोषणा RSMU_BASE__INST3_SEG1                      0
#घोषणा RSMU_BASE__INST3_SEG2                      0
#घोषणा RSMU_BASE__INST3_SEG3                      0
#घोषणा RSMU_BASE__INST3_SEG4                      0
#घोषणा RSMU_BASE__INST3_SEG5                      0

#घोषणा RSMU_BASE__INST4_SEG0                      0
#घोषणा RSMU_BASE__INST4_SEG1                      0
#घोषणा RSMU_BASE__INST4_SEG2                      0
#घोषणा RSMU_BASE__INST4_SEG3                      0
#घोषणा RSMU_BASE__INST4_SEG4                      0
#घोषणा RSMU_BASE__INST4_SEG5                      0

#घोषणा RSMU_BASE__INST5_SEG0                      0
#घोषणा RSMU_BASE__INST5_SEG1                      0
#घोषणा RSMU_BASE__INST5_SEG2                      0
#घोषणा RSMU_BASE__INST5_SEG3                      0
#घोषणा RSMU_BASE__INST5_SEG4                      0
#घोषणा RSMU_BASE__INST5_SEG5                      0

#घोषणा SMUIO_BASE__INST0_SEG0                     0x00016800
#घोषणा SMUIO_BASE__INST0_SEG1                     0x00016A00
#घोषणा SMUIO_BASE__INST0_SEG2                     0
#घोषणा SMUIO_BASE__INST0_SEG3                     0
#घोषणा SMUIO_BASE__INST0_SEG4                     0
#घोषणा SMUIO_BASE__INST0_SEG5                     0

#घोषणा SMUIO_BASE__INST1_SEG0                     0
#घोषणा SMUIO_BASE__INST1_SEG1                     0
#घोषणा SMUIO_BASE__INST1_SEG2                     0
#घोषणा SMUIO_BASE__INST1_SEG3                     0
#घोषणा SMUIO_BASE__INST1_SEG4                     0
#घोषणा SMUIO_BASE__INST1_SEG5                     0

#घोषणा SMUIO_BASE__INST2_SEG0                     0
#घोषणा SMUIO_BASE__INST2_SEG1                     0
#घोषणा SMUIO_BASE__INST2_SEG2                     0
#घोषणा SMUIO_BASE__INST2_SEG3                     0
#घोषणा SMUIO_BASE__INST2_SEG4                     0
#घोषणा SMUIO_BASE__INST2_SEG5                     0

#घोषणा SMUIO_BASE__INST3_SEG0                     0
#घोषणा SMUIO_BASE__INST3_SEG1                     0
#घोषणा SMUIO_BASE__INST3_SEG2                     0
#घोषणा SMUIO_BASE__INST3_SEG3                     0
#घोषणा SMUIO_BASE__INST3_SEG4                     0
#घोषणा SMUIO_BASE__INST3_SEG5                     0

#घोषणा SMUIO_BASE__INST4_SEG0                     0
#घोषणा SMUIO_BASE__INST4_SEG1                     0
#घोषणा SMUIO_BASE__INST4_SEG2                     0
#घोषणा SMUIO_BASE__INST4_SEG3                     0
#घोषणा SMUIO_BASE__INST4_SEG4                     0
#घोषणा SMUIO_BASE__INST4_SEG5                     0

#घोषणा SMUIO_BASE__INST5_SEG0                     0
#घोषणा SMUIO_BASE__INST5_SEG1                     0
#घोषणा SMUIO_BASE__INST5_SEG2                     0
#घोषणा SMUIO_BASE__INST5_SEG3                     0
#घोषणा SMUIO_BASE__INST5_SEG4                     0
#घोषणा SMUIO_BASE__INST5_SEG5                     0

#घोषणा THM_BASE__INST0_SEG0                       0x00016600
#घोषणा THM_BASE__INST0_SEG1                       0
#घोषणा THM_BASE__INST0_SEG2                       0
#घोषणा THM_BASE__INST0_SEG3                       0
#घोषणा THM_BASE__INST0_SEG4                       0
#घोषणा THM_BASE__INST0_SEG5                       0

#घोषणा THM_BASE__INST1_SEG0                       0
#घोषणा THM_BASE__INST1_SEG1                       0
#घोषणा THM_BASE__INST1_SEG2                       0
#घोषणा THM_BASE__INST1_SEG3                       0
#घोषणा THM_BASE__INST1_SEG4                       0
#घोषणा THM_BASE__INST1_SEG5                       0

#घोषणा THM_BASE__INST2_SEG0                       0
#घोषणा THM_BASE__INST2_SEG1                       0
#घोषणा THM_BASE__INST2_SEG2                       0
#घोषणा THM_BASE__INST2_SEG3                       0
#घोषणा THM_BASE__INST2_SEG4                       0
#घोषणा THM_BASE__INST2_SEG5                       0

#घोषणा THM_BASE__INST3_SEG0                       0
#घोषणा THM_BASE__INST3_SEG1                       0
#घोषणा THM_BASE__INST3_SEG2                       0
#घोषणा THM_BASE__INST3_SEG3                       0
#घोषणा THM_BASE__INST3_SEG4                       0
#घोषणा THM_BASE__INST3_SEG5                       0

#घोषणा THM_BASE__INST4_SEG0                       0
#घोषणा THM_BASE__INST4_SEG1                       0
#घोषणा THM_BASE__INST4_SEG2                       0
#घोषणा THM_BASE__INST4_SEG3                       0
#घोषणा THM_BASE__INST4_SEG4                       0
#घोषणा THM_BASE__INST4_SEG5                       0

#घोषणा THM_BASE__INST5_SEG0                       0
#घोषणा THM_BASE__INST5_SEG1                       0
#घोषणा THM_BASE__INST5_SEG2                       0
#घोषणा THM_BASE__INST5_SEG3                       0
#घोषणा THM_BASE__INST5_SEG4                       0
#घोषणा THM_BASE__INST5_SEG5                       0

#घोषणा UMC_BASE__INST0_SEG0                       0x00014000
#घोषणा UMC_BASE__INST0_SEG1                       0
#घोषणा UMC_BASE__INST0_SEG2                       0
#घोषणा UMC_BASE__INST0_SEG3                       0
#घोषणा UMC_BASE__INST0_SEG4                       0
#घोषणा UMC_BASE__INST0_SEG5                       0

#घोषणा UMC_BASE__INST1_SEG0                       0
#घोषणा UMC_BASE__INST1_SEG1                       0
#घोषणा UMC_BASE__INST1_SEG2                       0
#घोषणा UMC_BASE__INST1_SEG3                       0
#घोषणा UMC_BASE__INST1_SEG4                       0
#घोषणा UMC_BASE__INST1_SEG5                       0

#घोषणा UMC_BASE__INST2_SEG0                       0
#घोषणा UMC_BASE__INST2_SEG1                       0
#घोषणा UMC_BASE__INST2_SEG2                       0
#घोषणा UMC_BASE__INST2_SEG3                       0
#घोषणा UMC_BASE__INST2_SEG4                       0
#घोषणा UMC_BASE__INST2_SEG5                       0

#घोषणा UMC_BASE__INST3_SEG0                       0
#घोषणा UMC_BASE__INST3_SEG1                       0
#घोषणा UMC_BASE__INST3_SEG2                       0
#घोषणा UMC_BASE__INST3_SEG3                       0
#घोषणा UMC_BASE__INST3_SEG4                       0
#घोषणा UMC_BASE__INST3_SEG5                       0

#घोषणा UMC_BASE__INST4_SEG0                       0
#घोषणा UMC_BASE__INST4_SEG1                       0
#घोषणा UMC_BASE__INST4_SEG2                       0
#घोषणा UMC_BASE__INST4_SEG3                       0
#घोषणा UMC_BASE__INST4_SEG4                       0
#घोषणा UMC_BASE__INST4_SEG5                       0

#घोषणा UMC_BASE__INST5_SEG0                       0
#घोषणा UMC_BASE__INST5_SEG1                       0
#घोषणा UMC_BASE__INST5_SEG2                       0
#घोषणा UMC_BASE__INST5_SEG3                       0
#घोषणा UMC_BASE__INST5_SEG4                       0
#घोषणा UMC_BASE__INST5_SEG5                       0

#घोषणा VCN_BASE__INST0_SEG0                       0x00007800
#घोषणा VCN_BASE__INST0_SEG1                       0x00007E00
#घोषणा VCN_BASE__INST0_SEG2                       0
#घोषणा VCN_BASE__INST0_SEG3                       0
#घोषणा VCN_BASE__INST0_SEG4                       0
#घोषणा VCN_BASE__INST0_SEG5                       0

#घोषणा VCN_BASE__INST1_SEG0                       0
#घोषणा VCN_BASE__INST1_SEG1                       0
#घोषणा VCN_BASE__INST1_SEG2                       0
#घोषणा VCN_BASE__INST1_SEG3                       0
#घोषणा VCN_BASE__INST1_SEG4                       0
#घोषणा VCN_BASE__INST1_SEG5                       0

#घोषणा VCN_BASE__INST2_SEG0                       0
#घोषणा VCN_BASE__INST2_SEG1                       0
#घोषणा VCN_BASE__INST2_SEG2                       0
#घोषणा VCN_BASE__INST2_SEG3                       0
#घोषणा VCN_BASE__INST2_SEG4                       0
#घोषणा VCN_BASE__INST2_SEG5                       0

#घोषणा VCN_BASE__INST3_SEG0                       0
#घोषणा VCN_BASE__INST3_SEG1                       0
#घोषणा VCN_BASE__INST3_SEG2                       0
#घोषणा VCN_BASE__INST3_SEG3                       0
#घोषणा VCN_BASE__INST3_SEG4                       0
#घोषणा VCN_BASE__INST3_SEG5                       0

#घोषणा VCN_BASE__INST4_SEG0                       0
#घोषणा VCN_BASE__INST4_SEG1                       0
#घोषणा VCN_BASE__INST4_SEG2                       0
#घोषणा VCN_BASE__INST4_SEG3                       0
#घोषणा VCN_BASE__INST4_SEG4                       0
#घोषणा VCN_BASE__INST4_SEG5                       0

#घोषणा VCN_BASE__INST5_SEG0                       0
#घोषणा VCN_BASE__INST5_SEG1                       0
#घोषणा VCN_BASE__INST5_SEG2                       0
#घोषणा VCN_BASE__INST5_SEG3                       0
#घोषणा VCN_BASE__INST5_SEG4                       0
#घोषणा VCN_BASE__INST5_SEG5                       0

#पूर्ण_अगर
