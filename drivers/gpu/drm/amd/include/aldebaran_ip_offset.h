<शैली गुरु>
/*
 * Copyright (C) 2020  Advanced Micro Devices, Inc.
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
#अगर_अघोषित _aldebaran_ip_offset_HEADER
#घोषणा _aldebaran_ip_offset_HEADER

#घोषणा MAX_INSTANCE                                        7
#घोषणा MAX_SEGMENT                                         6

काष्ठा IP_BASE_INSTANCE अणु
    अचिन्हित पूर्णांक segment[MAX_SEGMENT];
पूर्ण;

काष्ठा IP_BASE अणु
    काष्ठा IP_BASE_INSTANCE instance[MAX_INSTANCE];
पूर्ण;

अटल स्थिर काष्ठा IP_BASE ATHUB_BASE = अणु अणु अणु अणु 0x00000C20, 0x02408C00, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE CLK_BASE = अणु अणु अणु अणु 0x00016C00, 0x02401800, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0x00016E00, 0x02401C00, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0x00017000, 0x02402000, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0x00017200, 0x02402400, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0x0001B000, 0x0242D800, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0x0001B200, 0x0242DC00, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0x00017E00, 0x0240BC00, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE DBGU_IO0_BASE = अणु अणु अणु अणु 0x000001E0, 0x0240B400, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0x00000260, 0x02413C00, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0x00000280, 0x02416000, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE DF_BASE = अणु अणु अणु अणु 0x00007000, 0x0240B800, 0x07C00000, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE FUSE_BASE = अणु अणु अणु अणु 0x00017400, 0x02401400, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE GC_BASE = अणु अणु अणु अणु 0x00002000, 0x0000A000, 0x02402C00, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE HDP_BASE = अणु अणु अणु अणु 0x00000F20, 0x0240A400, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE IOAGR0_BASE = अणु अणु अणु अणु 0x02419000, 0x056C0000, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE IOAPIC0_BASE = अणु अणु अणु अणु 0x00A00000, 0x0241F000, 0x050C0000, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE IOHC0_BASE = अणु अणु अणु अणु 0x00010000, 0x02406000, 0x04EC0000, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE L1IMUIOAGR0_BASE = अणु अणु अणु अणु 0x0240CC00, 0x05200000, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE L1IMUPCIE0_BASE = अणु अणु अणु अणु 0x0240C800, 0x051C0000, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE L2IMU0_BASE = अणु अणु अणु अणु 0x00007DC0, 0x00900000, 0x02407000, 0x04FC0000, 0x055C0000, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE MMHUB_BASE = अणु अणु अणु अणु 0x0001A000, 0x02408800, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE MP0_BASE = अणु अणु अणु अणु 0x00016000, 0x00DC0000, 0x00E00000, 0x00E40000, 0x0243FC00, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE MP1_BASE = अणु अणु अणु अणु 0x00016000, 0x00DC0000, 0x00E00000, 0x00E40000, 0x0243FC00, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE NBIO_BASE = अणु अणु अणु अणु 0x00000000, 0x00000014, 0x00000D20, 0x00010400, 0x0241B000, 0x04040000 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE OSSSYS_BASE = अणु अणु अणु अणु 0x000010A0, 0x0240A000, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE PCIE0_BASE = अणु अणु अणु अणु 0x02411800, 0x04440000, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE SDMA0_BASE = अणु अणु अणु अणु 0x00001260, 0x00012540, 0x0040A800, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE SDMA1_BASE = अणु अणु अणु अणु 0x00001860, 0x00012560, 0x0040AC00, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE SDMA2_BASE = अणु अणु अणु अणु 0x00013760, 0x0001E000, 0x0042EC00, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE SDMA3_BASE = अणु अणु अणु अणु 0x00013780, 0x0001E400, 0x0042F000, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE SDMA4_BASE = अणु अणु अणु अणु 0x000137A0, 0x0001E800, 0x0042F400, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE SMUIO_BASE = अणु अणु अणु अणु 0x00016800, 0x00016A00, 0x02401000, 0x03440000, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE THM_BASE = अणु अणु अणु अणु 0x00016600, 0x02400C00, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE UMC_BASE = अणु अणु अणु अणु 0x00014000, 0x00054000, 0x02425800, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0x00094000, 0x000D4000, 0x02425C00, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0x00114000, 0x00154000, 0x02426000, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0x00194000, 0x001D4000, 0x02426400, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE VCN_BASE = अणु अणु अणु अणु 0x00007800, 0x00007E00, 0x02403000, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0x00007A00, 0x00009000, 0x02445000, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE WAFL0_BASE = अणु अणु अणु अणु 0x02438000, 0x04880000, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE WAFL1_BASE = अणु अणु अणु अणु 0, 0x01300000, 0x02410800, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE XGMI0_BASE = अणु अणु अणु अणु 0x02438C00, 0x04680000, 0x04940000, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE XGMI1_BASE = अणु अणु अणु अणु 0x02439000, 0x046C0000, 0x04980000, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;
अटल स्थिर काष्ठा IP_BASE XGMI2_BASE = अणु अणु अणु अणु 0x04700000, 0x049C0000, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0x04740000, 0x04A00000, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0x04780000, 0x04A40000, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0x047C0000, 0x04A80000, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0x04800000, 0x04AC0000, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0x04840000, 0x04B00000, 0, 0, 0, 0 पूर्ण पूर्ण,
                                        अणु अणु 0, 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;


#घोषणा ATHUB_BASE__INST0_SEG0                     0x00000C20
#घोषणा ATHUB_BASE__INST0_SEG1                     0x02408C00
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

#घोषणा ATHUB_BASE__INST6_SEG0                     0
#घोषणा ATHUB_BASE__INST6_SEG1                     0
#घोषणा ATHUB_BASE__INST6_SEG2                     0
#घोषणा ATHUB_BASE__INST6_SEG3                     0
#घोषणा ATHUB_BASE__INST6_SEG4                     0
#घोषणा ATHUB_BASE__INST6_SEG5                     0

#घोषणा CLK_BASE__INST0_SEG0                       0x00016C00
#घोषणा CLK_BASE__INST0_SEG1                       0x02401800
#घोषणा CLK_BASE__INST0_SEG2                       0
#घोषणा CLK_BASE__INST0_SEG3                       0
#घोषणा CLK_BASE__INST0_SEG4                       0
#घोषणा CLK_BASE__INST0_SEG5                       0

#घोषणा CLK_BASE__INST1_SEG0                       0x00016E00
#घोषणा CLK_BASE__INST1_SEG1                       0x02401C00
#घोषणा CLK_BASE__INST1_SEG2                       0
#घोषणा CLK_BASE__INST1_SEG3                       0
#घोषणा CLK_BASE__INST1_SEG4                       0
#घोषणा CLK_BASE__INST1_SEG5                       0

#घोषणा CLK_BASE__INST2_SEG0                       0x00017000
#घोषणा CLK_BASE__INST2_SEG1                       0x02402000
#घोषणा CLK_BASE__INST2_SEG2                       0
#घोषणा CLK_BASE__INST2_SEG3                       0
#घोषणा CLK_BASE__INST2_SEG4                       0
#घोषणा CLK_BASE__INST2_SEG5                       0

#घोषणा CLK_BASE__INST3_SEG0                       0x00017200
#घोषणा CLK_BASE__INST3_SEG1                       0x02402400
#घोषणा CLK_BASE__INST3_SEG2                       0
#घोषणा CLK_BASE__INST3_SEG3                       0
#घोषणा CLK_BASE__INST3_SEG4                       0
#घोषणा CLK_BASE__INST3_SEG5                       0

#घोषणा CLK_BASE__INST4_SEG0                       0x0001B000
#घोषणा CLK_BASE__INST4_SEG1                       0x0242D800
#घोषणा CLK_BASE__INST4_SEG2                       0
#घोषणा CLK_BASE__INST4_SEG3                       0
#घोषणा CLK_BASE__INST4_SEG4                       0
#घोषणा CLK_BASE__INST4_SEG5                       0

#घोषणा CLK_BASE__INST5_SEG0                       0x0001B200
#घोषणा CLK_BASE__INST5_SEG1                       0x0242DC00
#घोषणा CLK_BASE__INST5_SEG2                       0
#घोषणा CLK_BASE__INST5_SEG3                       0
#घोषणा CLK_BASE__INST5_SEG4                       0
#घोषणा CLK_BASE__INST5_SEG5                       0

#घोषणा CLK_BASE__INST6_SEG0                       0x00017E00
#घोषणा CLK_BASE__INST6_SEG1                       0x0240BC00
#घोषणा CLK_BASE__INST6_SEG2                       0
#घोषणा CLK_BASE__INST6_SEG3                       0
#घोषणा CLK_BASE__INST6_SEG4                       0
#घोषणा CLK_BASE__INST6_SEG5                       0

#घोषणा DBGU_IO0_BASE__INST0_SEG0                  0x000001E0
#घोषणा DBGU_IO0_BASE__INST0_SEG1                  0x0240B400
#घोषणा DBGU_IO0_BASE__INST0_SEG2                  0
#घोषणा DBGU_IO0_BASE__INST0_SEG3                  0
#घोषणा DBGU_IO0_BASE__INST0_SEG4                  0
#घोषणा DBGU_IO0_BASE__INST0_SEG5                  0

#घोषणा DBGU_IO0_BASE__INST1_SEG0                  0x00000260
#घोषणा DBGU_IO0_BASE__INST1_SEG1                  0x02413C00
#घोषणा DBGU_IO0_BASE__INST1_SEG2                  0
#घोषणा DBGU_IO0_BASE__INST1_SEG3                  0
#घोषणा DBGU_IO0_BASE__INST1_SEG4                  0
#घोषणा DBGU_IO0_BASE__INST1_SEG5                  0

#घोषणा DBGU_IO0_BASE__INST2_SEG0                  0x00000280
#घोषणा DBGU_IO0_BASE__INST2_SEG1                  0x02416000
#घोषणा DBGU_IO0_BASE__INST2_SEG2                  0
#घोषणा DBGU_IO0_BASE__INST2_SEG3                  0
#घोषणा DBGU_IO0_BASE__INST2_SEG4                  0
#घोषणा DBGU_IO0_BASE__INST2_SEG5                  0

#घोषणा DBGU_IO0_BASE__INST3_SEG0                  0
#घोषणा DBGU_IO0_BASE__INST3_SEG1                  0
#घोषणा DBGU_IO0_BASE__INST3_SEG2                  0
#घोषणा DBGU_IO0_BASE__INST3_SEG3                  0
#घोषणा DBGU_IO0_BASE__INST3_SEG4                  0
#घोषणा DBGU_IO0_BASE__INST3_SEG5                  0

#घोषणा DBGU_IO0_BASE__INST4_SEG0                  0
#घोषणा DBGU_IO0_BASE__INST4_SEG1                  0
#घोषणा DBGU_IO0_BASE__INST4_SEG2                  0
#घोषणा DBGU_IO0_BASE__INST4_SEG3                  0
#घोषणा DBGU_IO0_BASE__INST4_SEG4                  0
#घोषणा DBGU_IO0_BASE__INST4_SEG5                  0

#घोषणा DBGU_IO0_BASE__INST5_SEG0                  0
#घोषणा DBGU_IO0_BASE__INST5_SEG1                  0
#घोषणा DBGU_IO0_BASE__INST5_SEG2                  0
#घोषणा DBGU_IO0_BASE__INST5_SEG3                  0
#घोषणा DBGU_IO0_BASE__INST5_SEG4                  0
#घोषणा DBGU_IO0_BASE__INST5_SEG5                  0

#घोषणा DBGU_IO0_BASE__INST6_SEG0                  0
#घोषणा DBGU_IO0_BASE__INST6_SEG1                  0
#घोषणा DBGU_IO0_BASE__INST6_SEG2                  0
#घोषणा DBGU_IO0_BASE__INST6_SEG3                  0
#घोषणा DBGU_IO0_BASE__INST6_SEG4                  0
#घोषणा DBGU_IO0_BASE__INST6_SEG5                  0

#घोषणा DF_BASE__INST0_SEG0                        0x00007000
#घोषणा DF_BASE__INST0_SEG1                        0x0240B800
#घोषणा DF_BASE__INST0_SEG2                        0x07C00000
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

#घोषणा DF_BASE__INST6_SEG0                        0
#घोषणा DF_BASE__INST6_SEG1                        0
#घोषणा DF_BASE__INST6_SEG2                        0
#घोषणा DF_BASE__INST6_SEG3                        0
#घोषणा DF_BASE__INST6_SEG4                        0
#घोषणा DF_BASE__INST6_SEG5                        0

#घोषणा FUSE_BASE__INST0_SEG0                      0x00017400
#घोषणा FUSE_BASE__INST0_SEG1                      0x02401400
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

#घोषणा FUSE_BASE__INST6_SEG0                      0
#घोषणा FUSE_BASE__INST6_SEG1                      0
#घोषणा FUSE_BASE__INST6_SEG2                      0
#घोषणा FUSE_BASE__INST6_SEG3                      0
#घोषणा FUSE_BASE__INST6_SEG4                      0
#घोषणा FUSE_BASE__INST6_SEG5                      0

#घोषणा GC_BASE__INST0_SEG0                        0x00002000
#घोषणा GC_BASE__INST0_SEG1                        0x0000A000
#घोषणा GC_BASE__INST0_SEG2                        0x02402C00
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

#घोषणा GC_BASE__INST6_SEG0                        0
#घोषणा GC_BASE__INST6_SEG1                        0
#घोषणा GC_BASE__INST6_SEG2                        0
#घोषणा GC_BASE__INST6_SEG3                        0
#घोषणा GC_BASE__INST6_SEG4                        0
#घोषणा GC_BASE__INST6_SEG5                        0

#घोषणा HDP_BASE__INST0_SEG0                       0x00000F20
#घोषणा HDP_BASE__INST0_SEG1                       0x0240A400
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

#घोषणा HDP_BASE__INST6_SEG0                       0
#घोषणा HDP_BASE__INST6_SEG1                       0
#घोषणा HDP_BASE__INST6_SEG2                       0
#घोषणा HDP_BASE__INST6_SEG3                       0
#घोषणा HDP_BASE__INST6_SEG4                       0
#घोषणा HDP_BASE__INST6_SEG5                       0

#घोषणा IOAGR0_BASE__INST0_SEG0                    0x02419000
#घोषणा IOAGR0_BASE__INST0_SEG1                    0x056C0000
#घोषणा IOAGR0_BASE__INST0_SEG2                    0
#घोषणा IOAGR0_BASE__INST0_SEG3                    0
#घोषणा IOAGR0_BASE__INST0_SEG4                    0
#घोषणा IOAGR0_BASE__INST0_SEG5                    0

#घोषणा IOAGR0_BASE__INST1_SEG0                    0
#घोषणा IOAGR0_BASE__INST1_SEG1                    0
#घोषणा IOAGR0_BASE__INST1_SEG2                    0
#घोषणा IOAGR0_BASE__INST1_SEG3                    0
#घोषणा IOAGR0_BASE__INST1_SEG4                    0
#घोषणा IOAGR0_BASE__INST1_SEG5                    0

#घोषणा IOAGR0_BASE__INST2_SEG0                    0
#घोषणा IOAGR0_BASE__INST2_SEG1                    0
#घोषणा IOAGR0_BASE__INST2_SEG2                    0
#घोषणा IOAGR0_BASE__INST2_SEG3                    0
#घोषणा IOAGR0_BASE__INST2_SEG4                    0
#घोषणा IOAGR0_BASE__INST2_SEG5                    0

#घोषणा IOAGR0_BASE__INST3_SEG0                    0
#घोषणा IOAGR0_BASE__INST3_SEG1                    0
#घोषणा IOAGR0_BASE__INST3_SEG2                    0
#घोषणा IOAGR0_BASE__INST3_SEG3                    0
#घोषणा IOAGR0_BASE__INST3_SEG4                    0
#घोषणा IOAGR0_BASE__INST3_SEG5                    0

#घोषणा IOAGR0_BASE__INST4_SEG0                    0
#घोषणा IOAGR0_BASE__INST4_SEG1                    0
#घोषणा IOAGR0_BASE__INST4_SEG2                    0
#घोषणा IOAGR0_BASE__INST4_SEG3                    0
#घोषणा IOAGR0_BASE__INST4_SEG4                    0
#घोषणा IOAGR0_BASE__INST4_SEG5                    0

#घोषणा IOAGR0_BASE__INST5_SEG0                    0
#घोषणा IOAGR0_BASE__INST5_SEG1                    0
#घोषणा IOAGR0_BASE__INST5_SEG2                    0
#घोषणा IOAGR0_BASE__INST5_SEG3                    0
#घोषणा IOAGR0_BASE__INST5_SEG4                    0
#घोषणा IOAGR0_BASE__INST5_SEG5                    0

#घोषणा IOAGR0_BASE__INST6_SEG0                    0
#घोषणा IOAGR0_BASE__INST6_SEG1                    0
#घोषणा IOAGR0_BASE__INST6_SEG2                    0
#घोषणा IOAGR0_BASE__INST6_SEG3                    0
#घोषणा IOAGR0_BASE__INST6_SEG4                    0
#घोषणा IOAGR0_BASE__INST6_SEG5                    0

#घोषणा IOAPIC0_BASE__INST0_SEG0                   0x00A00000
#घोषणा IOAPIC0_BASE__INST0_SEG1                   0x0241F000
#घोषणा IOAPIC0_BASE__INST0_SEG2                   0x050C0000
#घोषणा IOAPIC0_BASE__INST0_SEG3                   0
#घोषणा IOAPIC0_BASE__INST0_SEG4                   0
#घोषणा IOAPIC0_BASE__INST0_SEG5                   0

#घोषणा IOAPIC0_BASE__INST1_SEG0                   0
#घोषणा IOAPIC0_BASE__INST1_SEG1                   0
#घोषणा IOAPIC0_BASE__INST1_SEG2                   0
#घोषणा IOAPIC0_BASE__INST1_SEG3                   0
#घोषणा IOAPIC0_BASE__INST1_SEG4                   0
#घोषणा IOAPIC0_BASE__INST1_SEG5                   0

#घोषणा IOAPIC0_BASE__INST2_SEG0                   0
#घोषणा IOAPIC0_BASE__INST2_SEG1                   0
#घोषणा IOAPIC0_BASE__INST2_SEG2                   0
#घोषणा IOAPIC0_BASE__INST2_SEG3                   0
#घोषणा IOAPIC0_BASE__INST2_SEG4                   0
#घोषणा IOAPIC0_BASE__INST2_SEG5                   0

#घोषणा IOAPIC0_BASE__INST3_SEG0                   0
#घोषणा IOAPIC0_BASE__INST3_SEG1                   0
#घोषणा IOAPIC0_BASE__INST3_SEG2                   0
#घोषणा IOAPIC0_BASE__INST3_SEG3                   0
#घोषणा IOAPIC0_BASE__INST3_SEG4                   0
#घोषणा IOAPIC0_BASE__INST3_SEG5                   0

#घोषणा IOAPIC0_BASE__INST4_SEG0                   0
#घोषणा IOAPIC0_BASE__INST4_SEG1                   0
#घोषणा IOAPIC0_BASE__INST4_SEG2                   0
#घोषणा IOAPIC0_BASE__INST4_SEG3                   0
#घोषणा IOAPIC0_BASE__INST4_SEG4                   0
#घोषणा IOAPIC0_BASE__INST4_SEG5                   0

#घोषणा IOAPIC0_BASE__INST5_SEG0                   0
#घोषणा IOAPIC0_BASE__INST5_SEG1                   0
#घोषणा IOAPIC0_BASE__INST5_SEG2                   0
#घोषणा IOAPIC0_BASE__INST5_SEG3                   0
#घोषणा IOAPIC0_BASE__INST5_SEG4                   0
#घोषणा IOAPIC0_BASE__INST5_SEG5                   0

#घोषणा IOAPIC0_BASE__INST6_SEG0                   0
#घोषणा IOAPIC0_BASE__INST6_SEG1                   0
#घोषणा IOAPIC0_BASE__INST6_SEG2                   0
#घोषणा IOAPIC0_BASE__INST6_SEG3                   0
#घोषणा IOAPIC0_BASE__INST6_SEG4                   0
#घोषणा IOAPIC0_BASE__INST6_SEG5                   0

#घोषणा IOHC0_BASE__INST0_SEG0                     0x00010000
#घोषणा IOHC0_BASE__INST0_SEG1                     0x02406000
#घोषणा IOHC0_BASE__INST0_SEG2                     0x04EC0000
#घोषणा IOHC0_BASE__INST0_SEG3                     0
#घोषणा IOHC0_BASE__INST0_SEG4                     0
#घोषणा IOHC0_BASE__INST0_SEG5                     0

#घोषणा IOHC0_BASE__INST1_SEG0                     0
#घोषणा IOHC0_BASE__INST1_SEG1                     0
#घोषणा IOHC0_BASE__INST1_SEG2                     0
#घोषणा IOHC0_BASE__INST1_SEG3                     0
#घोषणा IOHC0_BASE__INST1_SEG4                     0
#घोषणा IOHC0_BASE__INST1_SEG5                     0

#घोषणा IOHC0_BASE__INST2_SEG0                     0
#घोषणा IOHC0_BASE__INST2_SEG1                     0
#घोषणा IOHC0_BASE__INST2_SEG2                     0
#घोषणा IOHC0_BASE__INST2_SEG3                     0
#घोषणा IOHC0_BASE__INST2_SEG4                     0
#घोषणा IOHC0_BASE__INST2_SEG5                     0

#घोषणा IOHC0_BASE__INST3_SEG0                     0
#घोषणा IOHC0_BASE__INST3_SEG1                     0
#घोषणा IOHC0_BASE__INST3_SEG2                     0
#घोषणा IOHC0_BASE__INST3_SEG3                     0
#घोषणा IOHC0_BASE__INST3_SEG4                     0
#घोषणा IOHC0_BASE__INST3_SEG5                     0

#घोषणा IOHC0_BASE__INST4_SEG0                     0
#घोषणा IOHC0_BASE__INST4_SEG1                     0
#घोषणा IOHC0_BASE__INST4_SEG2                     0
#घोषणा IOHC0_BASE__INST4_SEG3                     0
#घोषणा IOHC0_BASE__INST4_SEG4                     0
#घोषणा IOHC0_BASE__INST4_SEG5                     0

#घोषणा IOHC0_BASE__INST5_SEG0                     0
#घोषणा IOHC0_BASE__INST5_SEG1                     0
#घोषणा IOHC0_BASE__INST5_SEG2                     0
#घोषणा IOHC0_BASE__INST5_SEG3                     0
#घोषणा IOHC0_BASE__INST5_SEG4                     0
#घोषणा IOHC0_BASE__INST5_SEG5                     0

#घोषणा IOHC0_BASE__INST6_SEG0                     0
#घोषणा IOHC0_BASE__INST6_SEG1                     0
#घोषणा IOHC0_BASE__INST6_SEG2                     0
#घोषणा IOHC0_BASE__INST6_SEG3                     0
#घोषणा IOHC0_BASE__INST6_SEG4                     0
#घोषणा IOHC0_BASE__INST6_SEG5                     0

#घोषणा L1IMUIOAGR0_BASE__INST0_SEG0               0x0240CC00
#घोषणा L1IMUIOAGR0_BASE__INST0_SEG1               0x05200000
#घोषणा L1IMUIOAGR0_BASE__INST0_SEG2               0
#घोषणा L1IMUIOAGR0_BASE__INST0_SEG3               0
#घोषणा L1IMUIOAGR0_BASE__INST0_SEG4               0
#घोषणा L1IMUIOAGR0_BASE__INST0_SEG5               0

#घोषणा L1IMUIOAGR0_BASE__INST1_SEG0               0
#घोषणा L1IMUIOAGR0_BASE__INST1_SEG1               0
#घोषणा L1IMUIOAGR0_BASE__INST1_SEG2               0
#घोषणा L1IMUIOAGR0_BASE__INST1_SEG3               0
#घोषणा L1IMUIOAGR0_BASE__INST1_SEG4               0
#घोषणा L1IMUIOAGR0_BASE__INST1_SEG5               0

#घोषणा L1IMUIOAGR0_BASE__INST2_SEG0               0
#घोषणा L1IMUIOAGR0_BASE__INST2_SEG1               0
#घोषणा L1IMUIOAGR0_BASE__INST2_SEG2               0
#घोषणा L1IMUIOAGR0_BASE__INST2_SEG3               0
#घोषणा L1IMUIOAGR0_BASE__INST2_SEG4               0
#घोषणा L1IMUIOAGR0_BASE__INST2_SEG5               0

#घोषणा L1IMUIOAGR0_BASE__INST3_SEG0               0
#घोषणा L1IMUIOAGR0_BASE__INST3_SEG1               0
#घोषणा L1IMUIOAGR0_BASE__INST3_SEG2               0
#घोषणा L1IMUIOAGR0_BASE__INST3_SEG3               0
#घोषणा L1IMUIOAGR0_BASE__INST3_SEG4               0
#घोषणा L1IMUIOAGR0_BASE__INST3_SEG5               0

#घोषणा L1IMUIOAGR0_BASE__INST4_SEG0               0
#घोषणा L1IMUIOAGR0_BASE__INST4_SEG1               0
#घोषणा L1IMUIOAGR0_BASE__INST4_SEG2               0
#घोषणा L1IMUIOAGR0_BASE__INST4_SEG3               0
#घोषणा L1IMUIOAGR0_BASE__INST4_SEG4               0
#घोषणा L1IMUIOAGR0_BASE__INST4_SEG5               0

#घोषणा L1IMUIOAGR0_BASE__INST5_SEG0               0
#घोषणा L1IMUIOAGR0_BASE__INST5_SEG1               0
#घोषणा L1IMUIOAGR0_BASE__INST5_SEG2               0
#घोषणा L1IMUIOAGR0_BASE__INST5_SEG3               0
#घोषणा L1IMUIOAGR0_BASE__INST5_SEG4               0
#घोषणा L1IMUIOAGR0_BASE__INST5_SEG5               0

#घोषणा L1IMUIOAGR0_BASE__INST6_SEG0               0
#घोषणा L1IMUIOAGR0_BASE__INST6_SEG1               0
#घोषणा L1IMUIOAGR0_BASE__INST6_SEG2               0
#घोषणा L1IMUIOAGR0_BASE__INST6_SEG3               0
#घोषणा L1IMUIOAGR0_BASE__INST6_SEG4               0
#घोषणा L1IMUIOAGR0_BASE__INST6_SEG5               0

#घोषणा L1IMUPCIE0_BASE__INST0_SEG0                0x0240C800
#घोषणा L1IMUPCIE0_BASE__INST0_SEG1                0x051C0000
#घोषणा L1IMUPCIE0_BASE__INST0_SEG2                0
#घोषणा L1IMUPCIE0_BASE__INST0_SEG3                0
#घोषणा L1IMUPCIE0_BASE__INST0_SEG4                0
#घोषणा L1IMUPCIE0_BASE__INST0_SEG5                0

#घोषणा L1IMUPCIE0_BASE__INST1_SEG0                0
#घोषणा L1IMUPCIE0_BASE__INST1_SEG1                0
#घोषणा L1IMUPCIE0_BASE__INST1_SEG2                0
#घोषणा L1IMUPCIE0_BASE__INST1_SEG3                0
#घोषणा L1IMUPCIE0_BASE__INST1_SEG4                0
#घोषणा L1IMUPCIE0_BASE__INST1_SEG5                0

#घोषणा L1IMUPCIE0_BASE__INST2_SEG0                0
#घोषणा L1IMUPCIE0_BASE__INST2_SEG1                0
#घोषणा L1IMUPCIE0_BASE__INST2_SEG2                0
#घोषणा L1IMUPCIE0_BASE__INST2_SEG3                0
#घोषणा L1IMUPCIE0_BASE__INST2_SEG4                0
#घोषणा L1IMUPCIE0_BASE__INST2_SEG5                0

#घोषणा L1IMUPCIE0_BASE__INST3_SEG0                0
#घोषणा L1IMUPCIE0_BASE__INST3_SEG1                0
#घोषणा L1IMUPCIE0_BASE__INST3_SEG2                0
#घोषणा L1IMUPCIE0_BASE__INST3_SEG3                0
#घोषणा L1IMUPCIE0_BASE__INST3_SEG4                0
#घोषणा L1IMUPCIE0_BASE__INST3_SEG5                0

#घोषणा L1IMUPCIE0_BASE__INST4_SEG0                0
#घोषणा L1IMUPCIE0_BASE__INST4_SEG1                0
#घोषणा L1IMUPCIE0_BASE__INST4_SEG2                0
#घोषणा L1IMUPCIE0_BASE__INST4_SEG3                0
#घोषणा L1IMUPCIE0_BASE__INST4_SEG4                0
#घोषणा L1IMUPCIE0_BASE__INST4_SEG5                0

#घोषणा L1IMUPCIE0_BASE__INST5_SEG0                0
#घोषणा L1IMUPCIE0_BASE__INST5_SEG1                0
#घोषणा L1IMUPCIE0_BASE__INST5_SEG2                0
#घोषणा L1IMUPCIE0_BASE__INST5_SEG3                0
#घोषणा L1IMUPCIE0_BASE__INST5_SEG4                0
#घोषणा L1IMUPCIE0_BASE__INST5_SEG5                0

#घोषणा L1IMUPCIE0_BASE__INST6_SEG0                0
#घोषणा L1IMUPCIE0_BASE__INST6_SEG1                0
#घोषणा L1IMUPCIE0_BASE__INST6_SEG2                0
#घोषणा L1IMUPCIE0_BASE__INST6_SEG3                0
#घोषणा L1IMUPCIE0_BASE__INST6_SEG4                0
#घोषणा L1IMUPCIE0_BASE__INST6_SEG5                0

#घोषणा L2IMU0_BASE__INST0_SEG0                    0x00007DC0
#घोषणा L2IMU0_BASE__INST0_SEG1                    0x00900000
#घोषणा L2IMU0_BASE__INST0_SEG2                    0x02407000
#घोषणा L2IMU0_BASE__INST0_SEG3                    0x04FC0000
#घोषणा L2IMU0_BASE__INST0_SEG4                    0x055C0000
#घोषणा L2IMU0_BASE__INST0_SEG5                    0

#घोषणा L2IMU0_BASE__INST1_SEG0                    0
#घोषणा L2IMU0_BASE__INST1_SEG1                    0
#घोषणा L2IMU0_BASE__INST1_SEG2                    0
#घोषणा L2IMU0_BASE__INST1_SEG3                    0
#घोषणा L2IMU0_BASE__INST1_SEG4                    0
#घोषणा L2IMU0_BASE__INST1_SEG5                    0

#घोषणा L2IMU0_BASE__INST2_SEG0                    0
#घोषणा L2IMU0_BASE__INST2_SEG1                    0
#घोषणा L2IMU0_BASE__INST2_SEG2                    0
#घोषणा L2IMU0_BASE__INST2_SEG3                    0
#घोषणा L2IMU0_BASE__INST2_SEG4                    0
#घोषणा L2IMU0_BASE__INST2_SEG5                    0

#घोषणा L2IMU0_BASE__INST3_SEG0                    0
#घोषणा L2IMU0_BASE__INST3_SEG1                    0
#घोषणा L2IMU0_BASE__INST3_SEG2                    0
#घोषणा L2IMU0_BASE__INST3_SEG3                    0
#घोषणा L2IMU0_BASE__INST3_SEG4                    0
#घोषणा L2IMU0_BASE__INST3_SEG5                    0

#घोषणा L2IMU0_BASE__INST4_SEG0                    0
#घोषणा L2IMU0_BASE__INST4_SEG1                    0
#घोषणा L2IMU0_BASE__INST4_SEG2                    0
#घोषणा L2IMU0_BASE__INST4_SEG3                    0
#घोषणा L2IMU0_BASE__INST4_SEG4                    0
#घोषणा L2IMU0_BASE__INST4_SEG5                    0

#घोषणा L2IMU0_BASE__INST5_SEG0                    0
#घोषणा L2IMU0_BASE__INST5_SEG1                    0
#घोषणा L2IMU0_BASE__INST5_SEG2                    0
#घोषणा L2IMU0_BASE__INST5_SEG3                    0
#घोषणा L2IMU0_BASE__INST5_SEG4                    0
#घोषणा L2IMU0_BASE__INST5_SEG5                    0

#घोषणा L2IMU0_BASE__INST6_SEG0                    0
#घोषणा L2IMU0_BASE__INST6_SEG1                    0
#घोषणा L2IMU0_BASE__INST6_SEG2                    0
#घोषणा L2IMU0_BASE__INST6_SEG3                    0
#घोषणा L2IMU0_BASE__INST6_SEG4                    0
#घोषणा L2IMU0_BASE__INST6_SEG5                    0

#घोषणा MMHUB_BASE__INST0_SEG0                     0x0001A000
#घोषणा MMHUB_BASE__INST0_SEG1                     0x02408800
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

#घोषणा MMHUB_BASE__INST6_SEG0                     0
#घोषणा MMHUB_BASE__INST6_SEG1                     0
#घोषणा MMHUB_BASE__INST6_SEG2                     0
#घोषणा MMHUB_BASE__INST6_SEG3                     0
#घोषणा MMHUB_BASE__INST6_SEG4                     0
#घोषणा MMHUB_BASE__INST6_SEG5                     0

#घोषणा MP0_BASE__INST0_SEG0                       0x00016000
#घोषणा MP0_BASE__INST0_SEG1                       0x00DC0000
#घोषणा MP0_BASE__INST0_SEG2                       0x00E00000
#घोषणा MP0_BASE__INST0_SEG3                       0x00E40000
#घोषणा MP0_BASE__INST0_SEG4                       0x0243FC00
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

#घोषणा MP0_BASE__INST6_SEG0                       0
#घोषणा MP0_BASE__INST6_SEG1                       0
#घोषणा MP0_BASE__INST6_SEG2                       0
#घोषणा MP0_BASE__INST6_SEG3                       0
#घोषणा MP0_BASE__INST6_SEG4                       0
#घोषणा MP0_BASE__INST6_SEG5                       0

#घोषणा MP1_BASE__INST0_SEG0                       0x00016000
#घोषणा MP1_BASE__INST0_SEG1                       0x00DC0000
#घोषणा MP1_BASE__INST0_SEG2                       0x00E00000
#घोषणा MP1_BASE__INST0_SEG3                       0x00E40000
#घोषणा MP1_BASE__INST0_SEG4                       0x0243FC00
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

#घोषणा MP1_BASE__INST6_SEG0                       0
#घोषणा MP1_BASE__INST6_SEG1                       0
#घोषणा MP1_BASE__INST6_SEG2                       0
#घोषणा MP1_BASE__INST6_SEG3                       0
#घोषणा MP1_BASE__INST6_SEG4                       0
#घोषणा MP1_BASE__INST6_SEG5                       0

#घोषणा NBIO_BASE__INST0_SEG0                      0x00000000
#घोषणा NBIO_BASE__INST0_SEG1                      0x00000014
#घोषणा NBIO_BASE__INST0_SEG2                      0x00000D20
#घोषणा NBIO_BASE__INST0_SEG3                      0x00010400
#घोषणा NBIO_BASE__INST0_SEG4                      0x0241B000
#घोषणा NBIO_BASE__INST0_SEG5                      0x04040000

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

#घोषणा NBIO_BASE__INST6_SEG0                      0
#घोषणा NBIO_BASE__INST6_SEG1                      0
#घोषणा NBIO_BASE__INST6_SEG2                      0
#घोषणा NBIO_BASE__INST6_SEG3                      0
#घोषणा NBIO_BASE__INST6_SEG4                      0
#घोषणा NBIO_BASE__INST6_SEG5                      0

#घोषणा OSSSYS_BASE__INST0_SEG0                    0x000010A0
#घोषणा OSSSYS_BASE__INST0_SEG1                    0x0240A000
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

#घोषणा OSSSYS_BASE__INST6_SEG0                    0
#घोषणा OSSSYS_BASE__INST6_SEG1                    0
#घोषणा OSSSYS_BASE__INST6_SEG2                    0
#घोषणा OSSSYS_BASE__INST6_SEG3                    0
#घोषणा OSSSYS_BASE__INST6_SEG4                    0
#घोषणा OSSSYS_BASE__INST6_SEG5                    0

#घोषणा PCIE0_BASE__INST0_SEG0                     0x02411800
#घोषणा PCIE0_BASE__INST0_SEG1                     0x04440000
#घोषणा PCIE0_BASE__INST0_SEG2                     0
#घोषणा PCIE0_BASE__INST0_SEG3                     0
#घोषणा PCIE0_BASE__INST0_SEG4                     0
#घोषणा PCIE0_BASE__INST0_SEG5                     0

#घोषणा PCIE0_BASE__INST1_SEG0                     0
#घोषणा PCIE0_BASE__INST1_SEG1                     0
#घोषणा PCIE0_BASE__INST1_SEG2                     0
#घोषणा PCIE0_BASE__INST1_SEG3                     0
#घोषणा PCIE0_BASE__INST1_SEG4                     0
#घोषणा PCIE0_BASE__INST1_SEG5                     0

#घोषणा PCIE0_BASE__INST2_SEG0                     0
#घोषणा PCIE0_BASE__INST2_SEG1                     0
#घोषणा PCIE0_BASE__INST2_SEG2                     0
#घोषणा PCIE0_BASE__INST2_SEG3                     0
#घोषणा PCIE0_BASE__INST2_SEG4                     0
#घोषणा PCIE0_BASE__INST2_SEG5                     0

#घोषणा PCIE0_BASE__INST3_SEG0                     0
#घोषणा PCIE0_BASE__INST3_SEG1                     0
#घोषणा PCIE0_BASE__INST3_SEG2                     0
#घोषणा PCIE0_BASE__INST3_SEG3                     0
#घोषणा PCIE0_BASE__INST3_SEG4                     0
#घोषणा PCIE0_BASE__INST3_SEG5                     0

#घोषणा PCIE0_BASE__INST4_SEG0                     0
#घोषणा PCIE0_BASE__INST4_SEG1                     0
#घोषणा PCIE0_BASE__INST4_SEG2                     0
#घोषणा PCIE0_BASE__INST4_SEG3                     0
#घोषणा PCIE0_BASE__INST4_SEG4                     0
#घोषणा PCIE0_BASE__INST4_SEG5                     0

#घोषणा PCIE0_BASE__INST5_SEG0                     0
#घोषणा PCIE0_BASE__INST5_SEG1                     0
#घोषणा PCIE0_BASE__INST5_SEG2                     0
#घोषणा PCIE0_BASE__INST5_SEG3                     0
#घोषणा PCIE0_BASE__INST5_SEG4                     0
#घोषणा PCIE0_BASE__INST5_SEG5                     0

#घोषणा PCIE0_BASE__INST6_SEG0                     0
#घोषणा PCIE0_BASE__INST6_SEG1                     0
#घोषणा PCIE0_BASE__INST6_SEG2                     0
#घोषणा PCIE0_BASE__INST6_SEG3                     0
#घोषणा PCIE0_BASE__INST6_SEG4                     0
#घोषणा PCIE0_BASE__INST6_SEG5                     0

#घोषणा SDMA0_BASE__INST0_SEG0                     0x00001260
#घोषणा SDMA0_BASE__INST0_SEG1                     0x02445400
#घोषणा SDMA0_BASE__INST0_SEG2                     0
#घोषणा SDMA0_BASE__INST0_SEG3                     0
#घोषणा SDMA0_BASE__INST0_SEG4                     0
#घोषणा SDMA0_BASE__INST0_SEG5                     0

#घोषणा SDMA0_BASE__INST1_SEG0                     0
#घोषणा SDMA0_BASE__INST1_SEG1                     0
#घोषणा SDMA0_BASE__INST1_SEG2                     0
#घोषणा SDMA0_BASE__INST1_SEG3                     0
#घोषणा SDMA0_BASE__INST1_SEG4                     0
#घोषणा SDMA0_BASE__INST1_SEG5                     0

#घोषणा SDMA0_BASE__INST2_SEG0                     0
#घोषणा SDMA0_BASE__INST2_SEG1                     0
#घोषणा SDMA0_BASE__INST2_SEG2                     0
#घोषणा SDMA0_BASE__INST2_SEG3                     0
#घोषणा SDMA0_BASE__INST2_SEG4                     0
#घोषणा SDMA0_BASE__INST2_SEG5                     0

#घोषणा SDMA0_BASE__INST3_SEG0                     0
#घोषणा SDMA0_BASE__INST3_SEG1                     0
#घोषणा SDMA0_BASE__INST3_SEG2                     0
#घोषणा SDMA0_BASE__INST3_SEG3                     0
#घोषणा SDMA0_BASE__INST3_SEG4                     0
#घोषणा SDMA0_BASE__INST3_SEG5                     0

#घोषणा SDMA0_BASE__INST4_SEG0                     0
#घोषणा SDMA0_BASE__INST4_SEG1                     0
#घोषणा SDMA0_BASE__INST4_SEG2                     0
#घोषणा SDMA0_BASE__INST4_SEG3                     0
#घोषणा SDMA0_BASE__INST4_SEG4                     0
#घोषणा SDMA0_BASE__INST4_SEG5                     0

#घोषणा SDMA0_BASE__INST5_SEG0                     0
#घोषणा SDMA0_BASE__INST5_SEG1                     0
#घोषणा SDMA0_BASE__INST5_SEG2                     0
#घोषणा SDMA0_BASE__INST5_SEG3                     0
#घोषणा SDMA0_BASE__INST5_SEG4                     0
#घोषणा SDMA0_BASE__INST5_SEG5                     0

#घोषणा SDMA0_BASE__INST6_SEG0                     0
#घोषणा SDMA0_BASE__INST6_SEG1                     0
#घोषणा SDMA0_BASE__INST6_SEG2                     0
#घोषणा SDMA0_BASE__INST6_SEG3                     0
#घोषणा SDMA0_BASE__INST6_SEG4                     0
#घोषणा SDMA0_BASE__INST6_SEG5                     0

#घोषणा SDMA1_BASE__INST0_SEG0                     0x00001860
#घोषणा SDMA1_BASE__INST0_SEG1                     0x02445800
#घोषणा SDMA1_BASE__INST0_SEG2                     0
#घोषणा SDMA1_BASE__INST0_SEG3                     0
#घोषणा SDMA1_BASE__INST0_SEG4                     0
#घोषणा SDMA1_BASE__INST0_SEG5                     0

#घोषणा SDMA1_BASE__INST1_SEG0                     0x0001E000
#घोषणा SDMA1_BASE__INST1_SEG1                     0x02446400
#घोषणा SDMA1_BASE__INST1_SEG2                     0
#घोषणा SDMA1_BASE__INST1_SEG3                     0
#घोषणा SDMA1_BASE__INST1_SEG4                     0
#घोषणा SDMA1_BASE__INST1_SEG5                     0

#घोषणा SDMA1_BASE__INST2_SEG0                     0x0001E400
#घोषणा SDMA1_BASE__INST2_SEG1                     0x02446800
#घोषणा SDMA1_BASE__INST2_SEG2                     0
#घोषणा SDMA1_BASE__INST2_SEG3                     0
#घोषणा SDMA1_BASE__INST2_SEG4                     0
#घोषणा SDMA1_BASE__INST2_SEG5                     0

#घोषणा SDMA1_BASE__INST3_SEG0                     0x0001E800
#घोषणा SDMA1_BASE__INST3_SEG1                     0x02446C00
#घोषणा SDMA1_BASE__INST3_SEG2                     0
#घोषणा SDMA1_BASE__INST3_SEG3                     0
#घोषणा SDMA1_BASE__INST3_SEG4                     0
#घोषणा SDMA1_BASE__INST3_SEG5                     0

#घोषणा SDMA1_BASE__INST4_SEG0                     0
#घोषणा SDMA1_BASE__INST4_SEG1                     0
#घोषणा SDMA1_BASE__INST4_SEG2                     0
#घोषणा SDMA1_BASE__INST4_SEG3                     0
#घोषणा SDMA1_BASE__INST4_SEG4                     0
#घोषणा SDMA1_BASE__INST4_SEG5                     0

#घोषणा SDMA1_BASE__INST5_SEG0                     0
#घोषणा SDMA1_BASE__INST5_SEG1                     0
#घोषणा SDMA1_BASE__INST5_SEG2                     0
#घोषणा SDMA1_BASE__INST5_SEG3                     0
#घोषणा SDMA1_BASE__INST5_SEG4                     0
#घोषणा SDMA1_BASE__INST5_SEG5                     0

#घोषणा SDMA1_BASE__INST6_SEG0                     0
#घोषणा SDMA1_BASE__INST6_SEG1                     0
#घोषणा SDMA1_BASE__INST6_SEG2                     0
#घोषणा SDMA1_BASE__INST6_SEG3                     0
#घोषणा SDMA1_BASE__INST6_SEG4                     0
#घोषणा SDMA1_BASE__INST6_SEG5                     0

#घोषणा SMUIO_BASE__INST0_SEG0                     0x00016800
#घोषणा SMUIO_BASE__INST0_SEG1                     0x00016A00
#घोषणा SMUIO_BASE__INST0_SEG2                     0x02401000
#घोषणा SMUIO_BASE__INST0_SEG3                     0x03440000
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

#घोषणा SMUIO_BASE__INST6_SEG0                     0
#घोषणा SMUIO_BASE__INST6_SEG1                     0
#घोषणा SMUIO_BASE__INST6_SEG2                     0
#घोषणा SMUIO_BASE__INST6_SEG3                     0
#घोषणा SMUIO_BASE__INST6_SEG4                     0
#घोषणा SMUIO_BASE__INST6_SEG5                     0

#घोषणा THM_BASE__INST0_SEG0                       0x00016600
#घोषणा THM_BASE__INST0_SEG1                       0x02400C00
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

#घोषणा THM_BASE__INST6_SEG0                       0
#घोषणा THM_BASE__INST6_SEG1                       0
#घोषणा THM_BASE__INST6_SEG2                       0
#घोषणा THM_BASE__INST6_SEG3                       0
#घोषणा THM_BASE__INST6_SEG4                       0
#घोषणा THM_BASE__INST6_SEG5                       0

#घोषणा UMC_BASE__INST0_SEG0                       0x00014000
#घोषणा UMC_BASE__INST0_SEG1                       0x00054000
#घोषणा UMC_BASE__INST0_SEG2                       0x02425800
#घोषणा UMC_BASE__INST0_SEG3                       0
#घोषणा UMC_BASE__INST0_SEG4                       0
#घोषणा UMC_BASE__INST0_SEG5                       0

#घोषणा UMC_BASE__INST1_SEG0                       0x00094000
#घोषणा UMC_BASE__INST1_SEG1                       0x000D4000
#घोषणा UMC_BASE__INST1_SEG2                       0x02425C00
#घोषणा UMC_BASE__INST1_SEG3                       0
#घोषणा UMC_BASE__INST1_SEG4                       0
#घोषणा UMC_BASE__INST1_SEG5                       0

#घोषणा UMC_BASE__INST2_SEG0                       0x00114000
#घोषणा UMC_BASE__INST2_SEG1                       0x00154000
#घोषणा UMC_BASE__INST2_SEG2                       0x02426000
#घोषणा UMC_BASE__INST2_SEG3                       0
#घोषणा UMC_BASE__INST2_SEG4                       0
#घोषणा UMC_BASE__INST2_SEG5                       0

#घोषणा UMC_BASE__INST3_SEG0                       0x00194000
#घोषणा UMC_BASE__INST3_SEG1                       0x001D4000
#घोषणा UMC_BASE__INST3_SEG2                       0x02426400
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

#घोषणा UMC_BASE__INST6_SEG0                       0
#घोषणा UMC_BASE__INST6_SEG1                       0
#घोषणा UMC_BASE__INST6_SEG2                       0
#घोषणा UMC_BASE__INST6_SEG3                       0
#घोषणा UMC_BASE__INST6_SEG4                       0
#घोषणा UMC_BASE__INST6_SEG5                       0

#घोषणा VCN_BASE__INST0_SEG0                       0x00007800
#घोषणा VCN_BASE__INST0_SEG1                       0x00007E00
#घोषणा VCN_BASE__INST0_SEG2                       0x02403000
#घोषणा VCN_BASE__INST0_SEG3                       0
#घोषणा VCN_BASE__INST0_SEG4                       0
#घोषणा VCN_BASE__INST0_SEG5                       0

#घोषणा VCN_BASE__INST1_SEG0                       0x00007A00
#घोषणा VCN_BASE__INST1_SEG1                       0x00009000
#घोषणा VCN_BASE__INST1_SEG2                       0x02445000
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

#घोषणा VCN_BASE__INST6_SEG0                       0
#घोषणा VCN_BASE__INST6_SEG1                       0
#घोषणा VCN_BASE__INST6_SEG2                       0
#घोषणा VCN_BASE__INST6_SEG3                       0
#घोषणा VCN_BASE__INST6_SEG4                       0
#घोषणा VCN_BASE__INST6_SEG5                       0

#घोषणा WAFL0_BASE__INST0_SEG0                     0x02438000
#घोषणा WAFL0_BASE__INST0_SEG1                     0x04880000
#घोषणा WAFL0_BASE__INST0_SEG2                     0
#घोषणा WAFL0_BASE__INST0_SEG3                     0
#घोषणा WAFL0_BASE__INST0_SEG4                     0
#घोषणा WAFL0_BASE__INST0_SEG5                     0

#घोषणा WAFL0_BASE__INST1_SEG0                     0
#घोषणा WAFL0_BASE__INST1_SEG1                     0
#घोषणा WAFL0_BASE__INST1_SEG2                     0
#घोषणा WAFL0_BASE__INST1_SEG3                     0
#घोषणा WAFL0_BASE__INST1_SEG4                     0
#घोषणा WAFL0_BASE__INST1_SEG5                     0

#घोषणा WAFL0_BASE__INST2_SEG0                     0
#घोषणा WAFL0_BASE__INST2_SEG1                     0
#घोषणा WAFL0_BASE__INST2_SEG2                     0
#घोषणा WAFL0_BASE__INST2_SEG3                     0
#घोषणा WAFL0_BASE__INST2_SEG4                     0
#घोषणा WAFL0_BASE__INST2_SEG5                     0

#घोषणा WAFL0_BASE__INST3_SEG0                     0
#घोषणा WAFL0_BASE__INST3_SEG1                     0
#घोषणा WAFL0_BASE__INST3_SEG2                     0
#घोषणा WAFL0_BASE__INST3_SEG3                     0
#घोषणा WAFL0_BASE__INST3_SEG4                     0
#घोषणा WAFL0_BASE__INST3_SEG5                     0

#घोषणा WAFL0_BASE__INST4_SEG0                     0
#घोषणा WAFL0_BASE__INST4_SEG1                     0
#घोषणा WAFL0_BASE__INST4_SEG2                     0
#घोषणा WAFL0_BASE__INST4_SEG3                     0
#घोषणा WAFL0_BASE__INST4_SEG4                     0
#घोषणा WAFL0_BASE__INST4_SEG5                     0

#घोषणा WAFL0_BASE__INST5_SEG0                     0
#घोषणा WAFL0_BASE__INST5_SEG1                     0
#घोषणा WAFL0_BASE__INST5_SEG2                     0
#घोषणा WAFL0_BASE__INST5_SEG3                     0
#घोषणा WAFL0_BASE__INST5_SEG4                     0
#घोषणा WAFL0_BASE__INST5_SEG5                     0

#घोषणा WAFL0_BASE__INST6_SEG0                     0
#घोषणा WAFL0_BASE__INST6_SEG1                     0
#घोषणा WAFL0_BASE__INST6_SEG2                     0
#घोषणा WAFL0_BASE__INST6_SEG3                     0
#घोषणा WAFL0_BASE__INST6_SEG4                     0
#घोषणा WAFL0_BASE__INST6_SEG5                     0

#घोषणा WAFL1_BASE__INST0_SEG0                     0
#घोषणा WAFL1_BASE__INST0_SEG1                     0x01300000
#घोषणा WAFL1_BASE__INST0_SEG2                     0x02410800
#घोषणा WAFL1_BASE__INST0_SEG3                     0
#घोषणा WAFL1_BASE__INST0_SEG4                     0
#घोषणा WAFL1_BASE__INST0_SEG5                     0

#घोषणा WAFL1_BASE__INST1_SEG0                     0
#घोषणा WAFL1_BASE__INST1_SEG1                     0
#घोषणा WAFL1_BASE__INST1_SEG2                     0
#घोषणा WAFL1_BASE__INST1_SEG3                     0
#घोषणा WAFL1_BASE__INST1_SEG4                     0
#घोषणा WAFL1_BASE__INST1_SEG5                     0

#घोषणा WAFL1_BASE__INST2_SEG0                     0
#घोषणा WAFL1_BASE__INST2_SEG1                     0
#घोषणा WAFL1_BASE__INST2_SEG2                     0
#घोषणा WAFL1_BASE__INST2_SEG3                     0
#घोषणा WAFL1_BASE__INST2_SEG4                     0
#घोषणा WAFL1_BASE__INST2_SEG5                     0

#घोषणा WAFL1_BASE__INST3_SEG0                     0
#घोषणा WAFL1_BASE__INST3_SEG1                     0
#घोषणा WAFL1_BASE__INST3_SEG2                     0
#घोषणा WAFL1_BASE__INST3_SEG3                     0
#घोषणा WAFL1_BASE__INST3_SEG4                     0
#घोषणा WAFL1_BASE__INST3_SEG5                     0

#घोषणा WAFL1_BASE__INST4_SEG0                     0
#घोषणा WAFL1_BASE__INST4_SEG1                     0
#घोषणा WAFL1_BASE__INST4_SEG2                     0
#घोषणा WAFL1_BASE__INST4_SEG3                     0
#घोषणा WAFL1_BASE__INST4_SEG4                     0
#घोषणा WAFL1_BASE__INST4_SEG5                     0

#घोषणा WAFL1_BASE__INST5_SEG0                     0
#घोषणा WAFL1_BASE__INST5_SEG1                     0
#घोषणा WAFL1_BASE__INST5_SEG2                     0
#घोषणा WAFL1_BASE__INST5_SEG3                     0
#घोषणा WAFL1_BASE__INST5_SEG4                     0
#घोषणा WAFL1_BASE__INST5_SEG5                     0

#घोषणा WAFL1_BASE__INST6_SEG0                     0
#घोषणा WAFL1_BASE__INST6_SEG1                     0
#घोषणा WAFL1_BASE__INST6_SEG2                     0
#घोषणा WAFL1_BASE__INST6_SEG3                     0
#घोषणा WAFL1_BASE__INST6_SEG4                     0
#घोषणा WAFL1_BASE__INST6_SEG5                     0

#घोषणा XGMI0_BASE__INST0_SEG0                     0x02438C00
#घोषणा XGMI0_BASE__INST0_SEG1                     0x04680000
#घोषणा XGMI0_BASE__INST0_SEG2                     0x04940000
#घोषणा XGMI0_BASE__INST0_SEG3                     0
#घोषणा XGMI0_BASE__INST0_SEG4                     0
#घोषणा XGMI0_BASE__INST0_SEG5                     0

#घोषणा XGMI0_BASE__INST1_SEG0                     0
#घोषणा XGMI0_BASE__INST1_SEG1                     0
#घोषणा XGMI0_BASE__INST1_SEG2                     0
#घोषणा XGMI0_BASE__INST1_SEG3                     0
#घोषणा XGMI0_BASE__INST1_SEG4                     0
#घोषणा XGMI0_BASE__INST1_SEG5                     0

#घोषणा XGMI0_BASE__INST2_SEG0                     0
#घोषणा XGMI0_BASE__INST2_SEG1                     0
#घोषणा XGMI0_BASE__INST2_SEG2                     0
#घोषणा XGMI0_BASE__INST2_SEG3                     0
#घोषणा XGMI0_BASE__INST2_SEG4                     0
#घोषणा XGMI0_BASE__INST2_SEG5                     0

#घोषणा XGMI0_BASE__INST3_SEG0                     0
#घोषणा XGMI0_BASE__INST3_SEG1                     0
#घोषणा XGMI0_BASE__INST3_SEG2                     0
#घोषणा XGMI0_BASE__INST3_SEG3                     0
#घोषणा XGMI0_BASE__INST3_SEG4                     0
#घोषणा XGMI0_BASE__INST3_SEG5                     0

#घोषणा XGMI0_BASE__INST4_SEG0                     0
#घोषणा XGMI0_BASE__INST4_SEG1                     0
#घोषणा XGMI0_BASE__INST4_SEG2                     0
#घोषणा XGMI0_BASE__INST4_SEG3                     0
#घोषणा XGMI0_BASE__INST4_SEG4                     0
#घोषणा XGMI0_BASE__INST4_SEG5                     0

#घोषणा XGMI0_BASE__INST5_SEG0                     0
#घोषणा XGMI0_BASE__INST5_SEG1                     0
#घोषणा XGMI0_BASE__INST5_SEG2                     0
#घोषणा XGMI0_BASE__INST5_SEG3                     0
#घोषणा XGMI0_BASE__INST5_SEG4                     0
#घोषणा XGMI0_BASE__INST5_SEG5                     0

#घोषणा XGMI0_BASE__INST6_SEG0                     0
#घोषणा XGMI0_BASE__INST6_SEG1                     0
#घोषणा XGMI0_BASE__INST6_SEG2                     0
#घोषणा XGMI0_BASE__INST6_SEG3                     0
#घोषणा XGMI0_BASE__INST6_SEG4                     0
#घोषणा XGMI0_BASE__INST6_SEG5                     0

#घोषणा XGMI1_BASE__INST0_SEG0                     0x02439000
#घोषणा XGMI1_BASE__INST0_SEG1                     0x046C0000
#घोषणा XGMI1_BASE__INST0_SEG2                     0x04980000
#घोषणा XGMI1_BASE__INST0_SEG3                     0
#घोषणा XGMI1_BASE__INST0_SEG4                     0
#घोषणा XGMI1_BASE__INST0_SEG5                     0

#घोषणा XGMI1_BASE__INST1_SEG0                     0
#घोषणा XGMI1_BASE__INST1_SEG1                     0
#घोषणा XGMI1_BASE__INST1_SEG2                     0
#घोषणा XGMI1_BASE__INST1_SEG3                     0
#घोषणा XGMI1_BASE__INST1_SEG4                     0
#घोषणा XGMI1_BASE__INST1_SEG5                     0

#घोषणा XGMI1_BASE__INST2_SEG0                     0
#घोषणा XGMI1_BASE__INST2_SEG1                     0
#घोषणा XGMI1_BASE__INST2_SEG2                     0
#घोषणा XGMI1_BASE__INST2_SEG3                     0
#घोषणा XGMI1_BASE__INST2_SEG4                     0
#घोषणा XGMI1_BASE__INST2_SEG5                     0

#घोषणा XGMI1_BASE__INST3_SEG0                     0
#घोषणा XGMI1_BASE__INST3_SEG1                     0
#घोषणा XGMI1_BASE__INST3_SEG2                     0
#घोषणा XGMI1_BASE__INST3_SEG3                     0
#घोषणा XGMI1_BASE__INST3_SEG4                     0
#घोषणा XGMI1_BASE__INST3_SEG5                     0

#घोषणा XGMI1_BASE__INST4_SEG0                     0
#घोषणा XGMI1_BASE__INST4_SEG1                     0
#घोषणा XGMI1_BASE__INST4_SEG2                     0
#घोषणा XGMI1_BASE__INST4_SEG3                     0
#घोषणा XGMI1_BASE__INST4_SEG4                     0
#घोषणा XGMI1_BASE__INST4_SEG5                     0

#घोषणा XGMI1_BASE__INST5_SEG0                     0
#घोषणा XGMI1_BASE__INST5_SEG1                     0
#घोषणा XGMI1_BASE__INST5_SEG2                     0
#घोषणा XGMI1_BASE__INST5_SEG3                     0
#घोषणा XGMI1_BASE__INST5_SEG4                     0
#घोषणा XGMI1_BASE__INST5_SEG5                     0

#घोषणा XGMI1_BASE__INST6_SEG0                     0
#घोषणा XGMI1_BASE__INST6_SEG1                     0
#घोषणा XGMI1_BASE__INST6_SEG2                     0
#घोषणा XGMI1_BASE__INST6_SEG3                     0
#घोषणा XGMI1_BASE__INST6_SEG4                     0
#घोषणा XGMI1_BASE__INST6_SEG5                     0

#घोषणा XGMI2_BASE__INST0_SEG0                     0x04700000
#घोषणा XGMI2_BASE__INST0_SEG1                     0x049C0000
#घोषणा XGMI2_BASE__INST0_SEG2                     0
#घोषणा XGMI2_BASE__INST0_SEG3                     0
#घोषणा XGMI2_BASE__INST0_SEG4                     0
#घोषणा XGMI2_BASE__INST0_SEG5                     0

#घोषणा XGMI2_BASE__INST1_SEG0                     0x04740000
#घोषणा XGMI2_BASE__INST1_SEG1                     0x04A00000
#घोषणा XGMI2_BASE__INST1_SEG2                     0
#घोषणा XGMI2_BASE__INST1_SEG3                     0
#घोषणा XGMI2_BASE__INST1_SEG4                     0
#घोषणा XGMI2_BASE__INST1_SEG5                     0

#घोषणा XGMI2_BASE__INST2_SEG0                     0x04780000
#घोषणा XGMI2_BASE__INST2_SEG1                     0x04A40000
#घोषणा XGMI2_BASE__INST2_SEG2                     0
#घोषणा XGMI2_BASE__INST2_SEG3                     0
#घोषणा XGMI2_BASE__INST2_SEG4                     0
#घोषणा XGMI2_BASE__INST2_SEG5                     0

#घोषणा XGMI2_BASE__INST3_SEG0                     0x047C0000
#घोषणा XGMI2_BASE__INST3_SEG1                     0x04A80000
#घोषणा XGMI2_BASE__INST3_SEG2                     0
#घोषणा XGMI2_BASE__INST3_SEG3                     0
#घोषणा XGMI2_BASE__INST3_SEG4                     0
#घोषणा XGMI2_BASE__INST3_SEG5                     0

#घोषणा XGMI2_BASE__INST4_SEG0                     0x04800000
#घोषणा XGMI2_BASE__INST4_SEG1                     0x04AC0000
#घोषणा XGMI2_BASE__INST4_SEG2                     0
#घोषणा XGMI2_BASE__INST4_SEG3                     0
#घोषणा XGMI2_BASE__INST4_SEG4                     0
#घोषणा XGMI2_BASE__INST4_SEG5                     0

#घोषणा XGMI2_BASE__INST5_SEG0                     0x04840000
#घोषणा XGMI2_BASE__INST5_SEG1                     0x04B00000
#घोषणा XGMI2_BASE__INST5_SEG2                     0
#घोषणा XGMI2_BASE__INST5_SEG3                     0
#घोषणा XGMI2_BASE__INST5_SEG4                     0
#घोषणा XGMI2_BASE__INST5_SEG5                     0

#घोषणा XGMI2_BASE__INST6_SEG0                     0
#घोषणा XGMI2_BASE__INST6_SEG1                     0
#घोषणा XGMI2_BASE__INST6_SEG2                     0
#घोषणा XGMI2_BASE__INST6_SEG3                     0
#घोषणा XGMI2_BASE__INST6_SEG4                     0
#घोषणा XGMI2_BASE__INST6_SEG5                     0

#पूर्ण_अगर
