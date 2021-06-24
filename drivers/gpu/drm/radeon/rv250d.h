<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
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
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */
#अगर_अघोषित __RV250D_H__
#घोषणा __RV250D_H__

#घोषणा R_00000D_SCLK_CNTL_M6                        0x00000D
#घोषणा   S_00000D_SCLK_SRC_SEL(x)                     (((x) & 0x7) << 0)
#घोषणा   G_00000D_SCLK_SRC_SEL(x)                     (((x) >> 0) & 0x7)
#घोषणा   C_00000D_SCLK_SRC_SEL                        0xFFFFFFF8
#घोषणा   S_00000D_CP_MAX_DYN_STOP_LAT(x)              (((x) & 0x1) << 3)
#घोषणा   G_00000D_CP_MAX_DYN_STOP_LAT(x)              (((x) >> 3) & 0x1)
#घोषणा   C_00000D_CP_MAX_DYN_STOP_LAT                 0xFFFFFFF7
#घोषणा   S_00000D_HDP_MAX_DYN_STOP_LAT(x)             (((x) & 0x1) << 4)
#घोषणा   G_00000D_HDP_MAX_DYN_STOP_LAT(x)             (((x) >> 4) & 0x1)
#घोषणा   C_00000D_HDP_MAX_DYN_STOP_LAT                0xFFFFFFEF
#घोषणा   S_00000D_TV_MAX_DYN_STOP_LAT(x)              (((x) & 0x1) << 5)
#घोषणा   G_00000D_TV_MAX_DYN_STOP_LAT(x)              (((x) >> 5) & 0x1)
#घोषणा   C_00000D_TV_MAX_DYN_STOP_LAT                 0xFFFFFFDF
#घोषणा   S_00000D_E2_MAX_DYN_STOP_LAT(x)              (((x) & 0x1) << 6)
#घोषणा   G_00000D_E2_MAX_DYN_STOP_LAT(x)              (((x) >> 6) & 0x1)
#घोषणा   C_00000D_E2_MAX_DYN_STOP_LAT                 0xFFFFFFBF
#घोषणा   S_00000D_SE_MAX_DYN_STOP_LAT(x)              (((x) & 0x1) << 7)
#घोषणा   G_00000D_SE_MAX_DYN_STOP_LAT(x)              (((x) >> 7) & 0x1)
#घोषणा   C_00000D_SE_MAX_DYN_STOP_LAT                 0xFFFFFF7F
#घोषणा   S_00000D_IDCT_MAX_DYN_STOP_LAT(x)            (((x) & 0x1) << 8)
#घोषणा   G_00000D_IDCT_MAX_DYN_STOP_LAT(x)            (((x) >> 8) & 0x1)
#घोषणा   C_00000D_IDCT_MAX_DYN_STOP_LAT               0xFFFFFEFF
#घोषणा   S_00000D_VIP_MAX_DYN_STOP_LAT(x)             (((x) & 0x1) << 9)
#घोषणा   G_00000D_VIP_MAX_DYN_STOP_LAT(x)             (((x) >> 9) & 0x1)
#घोषणा   C_00000D_VIP_MAX_DYN_STOP_LAT                0xFFFFFDFF
#घोषणा   S_00000D_RE_MAX_DYN_STOP_LAT(x)              (((x) & 0x1) << 10)
#घोषणा   G_00000D_RE_MAX_DYN_STOP_LAT(x)              (((x) >> 10) & 0x1)
#घोषणा   C_00000D_RE_MAX_DYN_STOP_LAT                 0xFFFFFBFF
#घोषणा   S_00000D_PB_MAX_DYN_STOP_LAT(x)              (((x) & 0x1) << 11)
#घोषणा   G_00000D_PB_MAX_DYN_STOP_LAT(x)              (((x) >> 11) & 0x1)
#घोषणा   C_00000D_PB_MAX_DYN_STOP_LAT                 0xFFFFF7FF
#घोषणा   S_00000D_TAM_MAX_DYN_STOP_LAT(x)             (((x) & 0x1) << 12)
#घोषणा   G_00000D_TAM_MAX_DYN_STOP_LAT(x)             (((x) >> 12) & 0x1)
#घोषणा   C_00000D_TAM_MAX_DYN_STOP_LAT                0xFFFFEFFF
#घोषणा   S_00000D_TDM_MAX_DYN_STOP_LAT(x)             (((x) & 0x1) << 13)
#घोषणा   G_00000D_TDM_MAX_DYN_STOP_LAT(x)             (((x) >> 13) & 0x1)
#घोषणा   C_00000D_TDM_MAX_DYN_STOP_LAT                0xFFFFDFFF
#घोषणा   S_00000D_RB_MAX_DYN_STOP_LAT(x)              (((x) & 0x1) << 14)
#घोषणा   G_00000D_RB_MAX_DYN_STOP_LAT(x)              (((x) >> 14) & 0x1)
#घोषणा   C_00000D_RB_MAX_DYN_STOP_LAT                 0xFFFFBFFF
#घोषणा   S_00000D_FORCE_DISP2(x)                      (((x) & 0x1) << 15)
#घोषणा   G_00000D_FORCE_DISP2(x)                      (((x) >> 15) & 0x1)
#घोषणा   C_00000D_FORCE_DISP2                         0xFFFF7FFF
#घोषणा   S_00000D_FORCE_CP(x)                         (((x) & 0x1) << 16)
#घोषणा   G_00000D_FORCE_CP(x)                         (((x) >> 16) & 0x1)
#घोषणा   C_00000D_FORCE_CP                            0xFFFEFFFF
#घोषणा   S_00000D_FORCE_HDP(x)                        (((x) & 0x1) << 17)
#घोषणा   G_00000D_FORCE_HDP(x)                        (((x) >> 17) & 0x1)
#घोषणा   C_00000D_FORCE_HDP                           0xFFFDFFFF
#घोषणा   S_00000D_FORCE_DISP1(x)                      (((x) & 0x1) << 18)
#घोषणा   G_00000D_FORCE_DISP1(x)                      (((x) >> 18) & 0x1)
#घोषणा   C_00000D_FORCE_DISP1                         0xFFFBFFFF
#घोषणा   S_00000D_FORCE_TOP(x)                        (((x) & 0x1) << 19)
#घोषणा   G_00000D_FORCE_TOP(x)                        (((x) >> 19) & 0x1)
#घोषणा   C_00000D_FORCE_TOP                           0xFFF7FFFF
#घोषणा   S_00000D_FORCE_E2(x)                         (((x) & 0x1) << 20)
#घोषणा   G_00000D_FORCE_E2(x)                         (((x) >> 20) & 0x1)
#घोषणा   C_00000D_FORCE_E2                            0xFFEFFFFF
#घोषणा   S_00000D_FORCE_SE(x)                         (((x) & 0x1) << 21)
#घोषणा   G_00000D_FORCE_SE(x)                         (((x) >> 21) & 0x1)
#घोषणा   C_00000D_FORCE_SE                            0xFFDFFFFF
#घोषणा   S_00000D_FORCE_IDCT(x)                       (((x) & 0x1) << 22)
#घोषणा   G_00000D_FORCE_IDCT(x)                       (((x) >> 22) & 0x1)
#घोषणा   C_00000D_FORCE_IDCT                          0xFFBFFFFF
#घोषणा   S_00000D_FORCE_VIP(x)                        (((x) & 0x1) << 23)
#घोषणा   G_00000D_FORCE_VIP(x)                        (((x) >> 23) & 0x1)
#घोषणा   C_00000D_FORCE_VIP                           0xFF7FFFFF
#घोषणा   S_00000D_FORCE_RE(x)                         (((x) & 0x1) << 24)
#घोषणा   G_00000D_FORCE_RE(x)                         (((x) >> 24) & 0x1)
#घोषणा   C_00000D_FORCE_RE                            0xFEFFFFFF
#घोषणा   S_00000D_FORCE_PB(x)                         (((x) & 0x1) << 25)
#घोषणा   G_00000D_FORCE_PB(x)                         (((x) >> 25) & 0x1)
#घोषणा   C_00000D_FORCE_PB                            0xFDFFFFFF
#घोषणा   S_00000D_FORCE_TAM(x)                        (((x) & 0x1) << 26)
#घोषणा   G_00000D_FORCE_TAM(x)                        (((x) >> 26) & 0x1)
#घोषणा   C_00000D_FORCE_TAM                           0xFBFFFFFF
#घोषणा   S_00000D_FORCE_TDM(x)                        (((x) & 0x1) << 27)
#घोषणा   G_00000D_FORCE_TDM(x)                        (((x) >> 27) & 0x1)
#घोषणा   C_00000D_FORCE_TDM                           0xF7FFFFFF
#घोषणा   S_00000D_FORCE_RB(x)                         (((x) & 0x1) << 28)
#घोषणा   G_00000D_FORCE_RB(x)                         (((x) >> 28) & 0x1)
#घोषणा   C_00000D_FORCE_RB                            0xEFFFFFFF
#घोषणा   S_00000D_FORCE_TV_SCLK(x)                    (((x) & 0x1) << 29)
#घोषणा   G_00000D_FORCE_TV_SCLK(x)                    (((x) >> 29) & 0x1)
#घोषणा   C_00000D_FORCE_TV_SCLK                       0xDFFFFFFF
#घोषणा   S_00000D_FORCE_SUBPIC(x)                     (((x) & 0x1) << 30)
#घोषणा   G_00000D_FORCE_SUBPIC(x)                     (((x) >> 30) & 0x1)
#घोषणा   C_00000D_FORCE_SUBPIC                        0xBFFFFFFF
#घोषणा   S_00000D_FORCE_OV0(x)                        (((x) & 0x1) << 31)
#घोषणा   G_00000D_FORCE_OV0(x)                        (((x) >> 31) & 0x1)
#घोषणा   C_00000D_FORCE_OV0                           0x7FFFFFFF

#पूर्ण_अगर
