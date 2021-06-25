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
#अगर_अघोषित __R300D_H__
#घोषणा __R300D_H__

#घोषणा CP_PACKET0			0x00000000
#घोषणा		PACKET0_BASE_INDEX_SHIFT	0
#घोषणा		PACKET0_BASE_INDEX_MASK		(0x1ffff << 0)
#घोषणा		PACKET0_COUNT_SHIFT		16
#घोषणा		PACKET0_COUNT_MASK		(0x3fff << 16)
#घोषणा CP_PACKET1			0x40000000
#घोषणा CP_PACKET2			0x80000000
#घोषणा		PACKET2_PAD_SHIFT		0
#घोषणा		PACKET2_PAD_MASK		(0x3fffffff << 0)
#घोषणा CP_PACKET3			0xC0000000
#घोषणा		PACKET3_IT_OPCODE_SHIFT		8
#घोषणा		PACKET3_IT_OPCODE_MASK		(0xff << 8)
#घोषणा		PACKET3_COUNT_SHIFT		16
#घोषणा		PACKET3_COUNT_MASK		(0x3fff << 16)
/* PACKET3 op code */
#घोषणा		PACKET3_NOP			0x10
#घोषणा		PACKET3_3D_DRAW_VBUF		0x28
#घोषणा		PACKET3_3D_DRAW_IMMD		0x29
#घोषणा		PACKET3_3D_DRAW_INDX		0x2A
#घोषणा		PACKET3_3D_LOAD_VBPNTR		0x2F
#घोषणा		PACKET3_3D_CLEAR_ZMASK		0x32
#घोषणा		PACKET3_INDX_BUFFER		0x33
#घोषणा		PACKET3_3D_DRAW_VBUF_2		0x34
#घोषणा		PACKET3_3D_DRAW_IMMD_2		0x35
#घोषणा		PACKET3_3D_DRAW_INDX_2		0x36
#घोषणा		PACKET3_3D_CLEAR_HIZ		0x37
#घोषणा		PACKET3_3D_CLEAR_CMASK		0x38
#घोषणा		PACKET3_BITBLT_MULTI		0x9B

#घोषणा PACKET0(reg, n)	(CP_PACKET0 |					\
			 REG_SET(PACKET0_BASE_INDEX, (reg) >> 2) |	\
			 REG_SET(PACKET0_COUNT, (n)))
#घोषणा PACKET2(v)	(CP_PACKET2 | REG_SET(PACKET2_PAD, (v)))
#घोषणा PACKET3(op, n)	(CP_PACKET3 |					\
			 REG_SET(PACKET3_IT_OPCODE, (op)) |		\
			 REG_SET(PACKET3_COUNT, (n)))

/* Registers */
#घोषणा R_000148_MC_FB_LOCATION                      0x000148
#घोषणा   S_000148_MC_FB_START(x)                      (((x) & 0xFFFF) << 0)
#घोषणा   G_000148_MC_FB_START(x)                      (((x) >> 0) & 0xFFFF)
#घोषणा   C_000148_MC_FB_START                         0xFFFF0000
#घोषणा   S_000148_MC_FB_TOP(x)                        (((x) & 0xFFFF) << 16)
#घोषणा   G_000148_MC_FB_TOP(x)                        (((x) >> 16) & 0xFFFF)
#घोषणा   C_000148_MC_FB_TOP                           0x0000FFFF
#घोषणा R_00014C_MC_AGP_LOCATION                     0x00014C
#घोषणा   S_00014C_MC_AGP_START(x)                     (((x) & 0xFFFF) << 0)
#घोषणा   G_00014C_MC_AGP_START(x)                     (((x) >> 0) & 0xFFFF)
#घोषणा   C_00014C_MC_AGP_START                        0xFFFF0000
#घोषणा   S_00014C_MC_AGP_TOP(x)                       (((x) & 0xFFFF) << 16)
#घोषणा   G_00014C_MC_AGP_TOP(x)                       (((x) >> 16) & 0xFFFF)
#घोषणा   C_00014C_MC_AGP_TOP                          0x0000FFFF
#घोषणा R_00015C_AGP_BASE_2                          0x00015C
#घोषणा   S_00015C_AGP_BASE_ADDR_2(x)                  (((x) & 0xF) << 0)
#घोषणा   G_00015C_AGP_BASE_ADDR_2(x)                  (((x) >> 0) & 0xF)
#घोषणा   C_00015C_AGP_BASE_ADDR_2                     0xFFFFFFF0
#घोषणा R_000170_AGP_BASE                            0x000170
#घोषणा   S_000170_AGP_BASE_ADDR(x)                    (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_000170_AGP_BASE_ADDR(x)                    (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_000170_AGP_BASE_ADDR                       0x00000000
#घोषणा R_0007C0_CP_STAT                             0x0007C0
#घोषणा   S_0007C0_MRU_BUSY(x)                         (((x) & 0x1) << 0)
#घोषणा   G_0007C0_MRU_BUSY(x)                         (((x) >> 0) & 0x1)
#घोषणा   C_0007C0_MRU_BUSY                            0xFFFFFFFE
#घोषणा   S_0007C0_MWU_BUSY(x)                         (((x) & 0x1) << 1)
#घोषणा   G_0007C0_MWU_BUSY(x)                         (((x) >> 1) & 0x1)
#घोषणा   C_0007C0_MWU_BUSY                            0xFFFFFFFD
#घोषणा   S_0007C0_RSIU_BUSY(x)                        (((x) & 0x1) << 2)
#घोषणा   G_0007C0_RSIU_BUSY(x)                        (((x) >> 2) & 0x1)
#घोषणा   C_0007C0_RSIU_BUSY                           0xFFFFFFFB
#घोषणा   S_0007C0_RCIU_BUSY(x)                        (((x) & 0x1) << 3)
#घोषणा   G_0007C0_RCIU_BUSY(x)                        (((x) >> 3) & 0x1)
#घोषणा   C_0007C0_RCIU_BUSY                           0xFFFFFFF7
#घोषणा   S_0007C0_CSF_PRIMARY_BUSY(x)                 (((x) & 0x1) << 9)
#घोषणा   G_0007C0_CSF_PRIMARY_BUSY(x)                 (((x) >> 9) & 0x1)
#घोषणा   C_0007C0_CSF_PRIMARY_BUSY                    0xFFFFFDFF
#घोषणा   S_0007C0_CSF_INसूचीECT_BUSY(x)                (((x) & 0x1) << 10)
#घोषणा   G_0007C0_CSF_INसूचीECT_BUSY(x)                (((x) >> 10) & 0x1)
#घोषणा   C_0007C0_CSF_INसूचीECT_BUSY                   0xFFFFFBFF
#घोषणा   S_0007C0_CSQ_PRIMARY_BUSY(x)                 (((x) & 0x1) << 11)
#घोषणा   G_0007C0_CSQ_PRIMARY_BUSY(x)                 (((x) >> 11) & 0x1)
#घोषणा   C_0007C0_CSQ_PRIMARY_BUSY                    0xFFFFF7FF
#घोषणा   S_0007C0_CSQ_INसूचीECT_BUSY(x)                (((x) & 0x1) << 12)
#घोषणा   G_0007C0_CSQ_INसूचीECT_BUSY(x)                (((x) >> 12) & 0x1)
#घोषणा   C_0007C0_CSQ_INसूचीECT_BUSY                   0xFFFFEFFF
#घोषणा   S_0007C0_CSI_BUSY(x)                         (((x) & 0x1) << 13)
#घोषणा   G_0007C0_CSI_BUSY(x)                         (((x) >> 13) & 0x1)
#घोषणा   C_0007C0_CSI_BUSY                            0xFFFFDFFF
#घोषणा   S_0007C0_CSF_INसूचीECT2_BUSY(x)               (((x) & 0x1) << 14)
#घोषणा   G_0007C0_CSF_INसूचीECT2_BUSY(x)               (((x) >> 14) & 0x1)
#घोषणा   C_0007C0_CSF_INसूचीECT2_BUSY                  0xFFFFBFFF
#घोषणा   S_0007C0_CSQ_INसूचीECT2_BUSY(x)               (((x) & 0x1) << 15)
#घोषणा   G_0007C0_CSQ_INसूचीECT2_BUSY(x)               (((x) >> 15) & 0x1)
#घोषणा   C_0007C0_CSQ_INसूचीECT2_BUSY                  0xFFFF7FFF
#घोषणा   S_0007C0_GUIDMA_BUSY(x)                      (((x) & 0x1) << 28)
#घोषणा   G_0007C0_GUIDMA_BUSY(x)                      (((x) >> 28) & 0x1)
#घोषणा   C_0007C0_GUIDMA_BUSY                         0xEFFFFFFF
#घोषणा   S_0007C0_VIDDMA_BUSY(x)                      (((x) & 0x1) << 29)
#घोषणा   G_0007C0_VIDDMA_BUSY(x)                      (((x) >> 29) & 0x1)
#घोषणा   C_0007C0_VIDDMA_BUSY                         0xDFFFFFFF
#घोषणा   S_0007C0_CMDSTRM_BUSY(x)                     (((x) & 0x1) << 30)
#घोषणा   G_0007C0_CMDSTRM_BUSY(x)                     (((x) >> 30) & 0x1)
#घोषणा   C_0007C0_CMDSTRM_BUSY                        0xBFFFFFFF
#घोषणा   S_0007C0_CP_BUSY(x)                          (((x) & 0x1) << 31)
#घोषणा   G_0007C0_CP_BUSY(x)                          (((x) >> 31) & 0x1)
#घोषणा   C_0007C0_CP_BUSY                             0x7FFFFFFF
#घोषणा R_000E40_RBBM_STATUS                         0x000E40
#घोषणा   S_000E40_CMDFIFO_AVAIL(x)                    (((x) & 0x7F) << 0)
#घोषणा   G_000E40_CMDFIFO_AVAIL(x)                    (((x) >> 0) & 0x7F)
#घोषणा   C_000E40_CMDFIFO_AVAIL                       0xFFFFFF80
#घोषणा   S_000E40_HIRQ_ON_RBB(x)                      (((x) & 0x1) << 8)
#घोषणा   G_000E40_HIRQ_ON_RBB(x)                      (((x) >> 8) & 0x1)
#घोषणा   C_000E40_HIRQ_ON_RBB                         0xFFFFFEFF
#घोषणा   S_000E40_CPRQ_ON_RBB(x)                      (((x) & 0x1) << 9)
#घोषणा   G_000E40_CPRQ_ON_RBB(x)                      (((x) >> 9) & 0x1)
#घोषणा   C_000E40_CPRQ_ON_RBB                         0xFFFFFDFF
#घोषणा   S_000E40_CFRQ_ON_RBB(x)                      (((x) & 0x1) << 10)
#घोषणा   G_000E40_CFRQ_ON_RBB(x)                      (((x) >> 10) & 0x1)
#घोषणा   C_000E40_CFRQ_ON_RBB                         0xFFFFFBFF
#घोषणा   S_000E40_HIRQ_IN_RTBUF(x)                    (((x) & 0x1) << 11)
#घोषणा   G_000E40_HIRQ_IN_RTBUF(x)                    (((x) >> 11) & 0x1)
#घोषणा   C_000E40_HIRQ_IN_RTBUF                       0xFFFFF7FF
#घोषणा   S_000E40_CPRQ_IN_RTBUF(x)                    (((x) & 0x1) << 12)
#घोषणा   G_000E40_CPRQ_IN_RTBUF(x)                    (((x) >> 12) & 0x1)
#घोषणा   C_000E40_CPRQ_IN_RTBUF                       0xFFFFEFFF
#घोषणा   S_000E40_CFRQ_IN_RTBUF(x)                    (((x) & 0x1) << 13)
#घोषणा   G_000E40_CFRQ_IN_RTBUF(x)                    (((x) >> 13) & 0x1)
#घोषणा   C_000E40_CFRQ_IN_RTBUF                       0xFFFFDFFF
#घोषणा   S_000E40_CF_PIPE_BUSY(x)                     (((x) & 0x1) << 14)
#घोषणा   G_000E40_CF_PIPE_BUSY(x)                     (((x) >> 14) & 0x1)
#घोषणा   C_000E40_CF_PIPE_BUSY                        0xFFFFBFFF
#घोषणा   S_000E40_ENG_EV_BUSY(x)                      (((x) & 0x1) << 15)
#घोषणा   G_000E40_ENG_EV_BUSY(x)                      (((x) >> 15) & 0x1)
#घोषणा   C_000E40_ENG_EV_BUSY                         0xFFFF7FFF
#घोषणा   S_000E40_CP_CMDSTRM_BUSY(x)                  (((x) & 0x1) << 16)
#घोषणा   G_000E40_CP_CMDSTRM_BUSY(x)                  (((x) >> 16) & 0x1)
#घोषणा   C_000E40_CP_CMDSTRM_BUSY                     0xFFFEFFFF
#घोषणा   S_000E40_E2_BUSY(x)                          (((x) & 0x1) << 17)
#घोषणा   G_000E40_E2_BUSY(x)                          (((x) >> 17) & 0x1)
#घोषणा   C_000E40_E2_BUSY                             0xFFFDFFFF
#घोषणा   S_000E40_RB2D_BUSY(x)                        (((x) & 0x1) << 18)
#घोषणा   G_000E40_RB2D_BUSY(x)                        (((x) >> 18) & 0x1)
#घोषणा   C_000E40_RB2D_BUSY                           0xFFFBFFFF
#घोषणा   S_000E40_RB3D_BUSY(x)                        (((x) & 0x1) << 19)
#घोषणा   G_000E40_RB3D_BUSY(x)                        (((x) >> 19) & 0x1)
#घोषणा   C_000E40_RB3D_BUSY                           0xFFF7FFFF
#घोषणा   S_000E40_VAP_BUSY(x)                         (((x) & 0x1) << 20)
#घोषणा   G_000E40_VAP_BUSY(x)                         (((x) >> 20) & 0x1)
#घोषणा   C_000E40_VAP_BUSY                            0xFFEFFFFF
#घोषणा   S_000E40_RE_BUSY(x)                          (((x) & 0x1) << 21)
#घोषणा   G_000E40_RE_BUSY(x)                          (((x) >> 21) & 0x1)
#घोषणा   C_000E40_RE_BUSY                             0xFFDFFFFF
#घोषणा   S_000E40_TAM_BUSY(x)                         (((x) & 0x1) << 22)
#घोषणा   G_000E40_TAM_BUSY(x)                         (((x) >> 22) & 0x1)
#घोषणा   C_000E40_TAM_BUSY                            0xFFBFFFFF
#घोषणा   S_000E40_TDM_BUSY(x)                         (((x) & 0x1) << 23)
#घोषणा   G_000E40_TDM_BUSY(x)                         (((x) >> 23) & 0x1)
#घोषणा   C_000E40_TDM_BUSY                            0xFF7FFFFF
#घोषणा   S_000E40_PB_BUSY(x)                          (((x) & 0x1) << 24)
#घोषणा   G_000E40_PB_BUSY(x)                          (((x) >> 24) & 0x1)
#घोषणा   C_000E40_PB_BUSY                             0xFEFFFFFF
#घोषणा   S_000E40_TIM_BUSY(x)                         (((x) & 0x1) << 25)
#घोषणा   G_000E40_TIM_BUSY(x)                         (((x) >> 25) & 0x1)
#घोषणा   C_000E40_TIM_BUSY                            0xFDFFFFFF
#घोषणा   S_000E40_GA_BUSY(x)                          (((x) & 0x1) << 26)
#घोषणा   G_000E40_GA_BUSY(x)                          (((x) >> 26) & 0x1)
#घोषणा   C_000E40_GA_BUSY                             0xFBFFFFFF
#घोषणा   S_000E40_CBA2D_BUSY(x)                       (((x) & 0x1) << 27)
#घोषणा   G_000E40_CBA2D_BUSY(x)                       (((x) >> 27) & 0x1)
#घोषणा   C_000E40_CBA2D_BUSY                          0xF7FFFFFF
#घोषणा   S_000E40_GUI_ACTIVE(x)                       (((x) & 0x1) << 31)
#घोषणा   G_000E40_GUI_ACTIVE(x)                       (((x) >> 31) & 0x1)
#घोषणा   C_000E40_GUI_ACTIVE                          0x7FFFFFFF
#घोषणा R_0000F0_RBBM_SOFT_RESET                     0x0000F0
#घोषणा   S_0000F0_SOFT_RESET_CP(x)                    (((x) & 0x1) << 0)
#घोषणा   G_0000F0_SOFT_RESET_CP(x)                    (((x) >> 0) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_CP                       0xFFFFFFFE
#घोषणा   S_0000F0_SOFT_RESET_HI(x)                    (((x) & 0x1) << 1)
#घोषणा   G_0000F0_SOFT_RESET_HI(x)                    (((x) >> 1) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_HI                       0xFFFFFFFD
#घोषणा   S_0000F0_SOFT_RESET_VAP(x)                   (((x) & 0x1) << 2)
#घोषणा   G_0000F0_SOFT_RESET_VAP(x)                   (((x) >> 2) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_VAP                      0xFFFFFFFB
#घोषणा   S_0000F0_SOFT_RESET_RE(x)                    (((x) & 0x1) << 3)
#घोषणा   G_0000F0_SOFT_RESET_RE(x)                    (((x) >> 3) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_RE                       0xFFFFFFF7
#घोषणा   S_0000F0_SOFT_RESET_PP(x)                    (((x) & 0x1) << 4)
#घोषणा   G_0000F0_SOFT_RESET_PP(x)                    (((x) >> 4) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_PP                       0xFFFFFFEF
#घोषणा   S_0000F0_SOFT_RESET_E2(x)                    (((x) & 0x1) << 5)
#घोषणा   G_0000F0_SOFT_RESET_E2(x)                    (((x) >> 5) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_E2                       0xFFFFFFDF
#घोषणा   S_0000F0_SOFT_RESET_RB(x)                    (((x) & 0x1) << 6)
#घोषणा   G_0000F0_SOFT_RESET_RB(x)                    (((x) >> 6) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_RB                       0xFFFFFFBF
#घोषणा   S_0000F0_SOFT_RESET_HDP(x)                   (((x) & 0x1) << 7)
#घोषणा   G_0000F0_SOFT_RESET_HDP(x)                   (((x) >> 7) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_HDP                      0xFFFFFF7F
#घोषणा   S_0000F0_SOFT_RESET_MC(x)                    (((x) & 0x1) << 8)
#घोषणा   G_0000F0_SOFT_RESET_MC(x)                    (((x) >> 8) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_MC                       0xFFFFFEFF
#घोषणा   S_0000F0_SOFT_RESET_AIC(x)                   (((x) & 0x1) << 9)
#घोषणा   G_0000F0_SOFT_RESET_AIC(x)                   (((x) >> 9) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_AIC                      0xFFFFFDFF
#घोषणा   S_0000F0_SOFT_RESET_VIP(x)                   (((x) & 0x1) << 10)
#घोषणा   G_0000F0_SOFT_RESET_VIP(x)                   (((x) >> 10) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_VIP                      0xFFFFFBFF
#घोषणा   S_0000F0_SOFT_RESET_DISP(x)                  (((x) & 0x1) << 11)
#घोषणा   G_0000F0_SOFT_RESET_DISP(x)                  (((x) >> 11) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_DISP                     0xFFFFF7FF
#घोषणा   S_0000F0_SOFT_RESET_CG(x)                    (((x) & 0x1) << 12)
#घोषणा   G_0000F0_SOFT_RESET_CG(x)                    (((x) >> 12) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_CG                       0xFFFFEFFF
#घोषणा   S_0000F0_SOFT_RESET_GA(x)                    (((x) & 0x1) << 13)
#घोषणा   G_0000F0_SOFT_RESET_GA(x)                    (((x) >> 13) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_GA                       0xFFFFDFFF
#घोषणा   S_0000F0_SOFT_RESET_IDCT(x)                  (((x) & 0x1) << 14)
#घोषणा   G_0000F0_SOFT_RESET_IDCT(x)                  (((x) >> 14) & 0x1)
#घोषणा   C_0000F0_SOFT_RESET_IDCT                     0xFFFFBFFF

#घोषणा R_00000D_SCLK_CNTL                           0x00000D
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
