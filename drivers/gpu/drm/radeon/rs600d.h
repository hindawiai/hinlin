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
#अगर_अघोषित __RS600D_H__
#घोषणा __RS600D_H__

/* Registers */
#घोषणा R_000040_GEN_INT_CNTL                        0x000040
#घोषणा   S_000040_SCRATCH_INT_MASK(x)                 (((x) & 0x1) << 18)
#घोषणा   G_000040_SCRATCH_INT_MASK(x)                 (((x) >> 18) & 0x1)
#घोषणा   C_000040_SCRATCH_INT_MASK                    0xFFFBFFFF
#घोषणा   S_000040_GUI_IDLE_MASK(x)                    (((x) & 0x1) << 19)
#घोषणा   G_000040_GUI_IDLE_MASK(x)                    (((x) >> 19) & 0x1)
#घोषणा   C_000040_GUI_IDLE_MASK                       0xFFF7FFFF
#घोषणा   S_000040_DMA_VIPH1_INT_EN(x)                 (((x) & 0x1) << 13)
#घोषणा   G_000040_DMA_VIPH1_INT_EN(x)                 (((x) >> 13) & 0x1)
#घोषणा   C_000040_DMA_VIPH1_INT_EN                    0xFFFFDFFF
#घोषणा   S_000040_DMA_VIPH2_INT_EN(x)                 (((x) & 0x1) << 14)
#घोषणा   G_000040_DMA_VIPH2_INT_EN(x)                 (((x) >> 14) & 0x1)
#घोषणा   C_000040_DMA_VIPH2_INT_EN                    0xFFFFBFFF
#घोषणा   S_000040_DMA_VIPH3_INT_EN(x)                 (((x) & 0x1) << 15)
#घोषणा   G_000040_DMA_VIPH3_INT_EN(x)                 (((x) >> 15) & 0x1)
#घोषणा   C_000040_DMA_VIPH3_INT_EN                    0xFFFF7FFF
#घोषणा   S_000040_I2C_INT_EN(x)                       (((x) & 0x1) << 17)
#घोषणा   G_000040_I2C_INT_EN(x)                       (((x) >> 17) & 0x1)
#घोषणा   C_000040_I2C_INT_EN                          0xFFFDFFFF
#घोषणा   S_000040_GUI_IDLE(x)                         (((x) & 0x1) << 19)
#घोषणा   G_000040_GUI_IDLE(x)                         (((x) >> 19) & 0x1)
#घोषणा   C_000040_GUI_IDLE                            0xFFF7FFFF
#घोषणा   S_000040_VIPH_INT_EN(x)                      (((x) & 0x1) << 24)
#घोषणा   G_000040_VIPH_INT_EN(x)                      (((x) >> 24) & 0x1)
#घोषणा   C_000040_VIPH_INT_EN                         0xFEFFFFFF
#घोषणा   S_000040_SW_INT_EN(x)                        (((x) & 0x1) << 25)
#घोषणा   G_000040_SW_INT_EN(x)                        (((x) >> 25) & 0x1)
#घोषणा   C_000040_SW_INT_EN                           0xFDFFFFFF
#घोषणा   S_000040_GEYSERVILLE(x)                      (((x) & 0x1) << 27)
#घोषणा   G_000040_GEYSERVILLE(x)                      (((x) >> 27) & 0x1)
#घोषणा   C_000040_GEYSERVILLE                         0xF7FFFFFF
#घोषणा   S_000040_HDCP_AUTHORIZED_INT(x)              (((x) & 0x1) << 28)
#घोषणा   G_000040_HDCP_AUTHORIZED_INT(x)              (((x) >> 28) & 0x1)
#घोषणा   C_000040_HDCP_AUTHORIZED_INT                 0xEFFFFFFF
#घोषणा   S_000040_DVI_I2C_INT(x)                      (((x) & 0x1) << 29)
#घोषणा   G_000040_DVI_I2C_INT(x)                      (((x) >> 29) & 0x1)
#घोषणा   C_000040_DVI_I2C_INT                         0xDFFFFFFF
#घोषणा   S_000040_GUIDMA(x)                           (((x) & 0x1) << 30)
#घोषणा   G_000040_GUIDMA(x)                           (((x) >> 30) & 0x1)
#घोषणा   C_000040_GUIDMA                              0xBFFFFFFF
#घोषणा   S_000040_VIDDMA(x)                           (((x) & 0x1) << 31)
#घोषणा   G_000040_VIDDMA(x)                           (((x) >> 31) & 0x1)
#घोषणा   C_000040_VIDDMA                              0x7FFFFFFF
#घोषणा R_000044_GEN_INT_STATUS                      0x000044
#घोषणा   S_000044_DISPLAY_INT_STAT(x)                 (((x) & 0x1) << 0)
#घोषणा   G_000044_DISPLAY_INT_STAT(x)                 (((x) >> 0) & 0x1)
#घोषणा   C_000044_DISPLAY_INT_STAT                    0xFFFFFFFE
#घोषणा   S_000044_VGA_INT_STAT(x)                     (((x) & 0x1) << 1)
#घोषणा   G_000044_VGA_INT_STAT(x)                     (((x) >> 1) & 0x1)
#घोषणा   C_000044_VGA_INT_STAT                        0xFFFFFFFD
#घोषणा   S_000044_CAP0_INT_ACTIVE(x)                  (((x) & 0x1) << 8)
#घोषणा   G_000044_CAP0_INT_ACTIVE(x)                  (((x) >> 8) & 0x1)
#घोषणा   C_000044_CAP0_INT_ACTIVE                     0xFFFFFEFF
#घोषणा   S_000044_DMA_VIPH0_INT(x)                    (((x) & 0x1) << 12)
#घोषणा   G_000044_DMA_VIPH0_INT(x)                    (((x) >> 12) & 0x1)
#घोषणा   C_000044_DMA_VIPH0_INT                       0xFFFFEFFF
#घोषणा   S_000044_DMA_VIPH1_INT(x)                    (((x) & 0x1) << 13)
#घोषणा   G_000044_DMA_VIPH1_INT(x)                    (((x) >> 13) & 0x1)
#घोषणा   C_000044_DMA_VIPH1_INT                       0xFFFFDFFF
#घोषणा   S_000044_DMA_VIPH2_INT(x)                    (((x) & 0x1) << 14)
#घोषणा   G_000044_DMA_VIPH2_INT(x)                    (((x) >> 14) & 0x1)
#घोषणा   C_000044_DMA_VIPH2_INT                       0xFFFFBFFF
#घोषणा   S_000044_DMA_VIPH3_INT(x)                    (((x) & 0x1) << 15)
#घोषणा   G_000044_DMA_VIPH3_INT(x)                    (((x) >> 15) & 0x1)
#घोषणा   C_000044_DMA_VIPH3_INT                       0xFFFF7FFF
#घोषणा   S_000044_MC_PROBE_FAULT_STAT(x)              (((x) & 0x1) << 16)
#घोषणा   G_000044_MC_PROBE_FAULT_STAT(x)              (((x) >> 16) & 0x1)
#घोषणा   C_000044_MC_PROBE_FAULT_STAT                 0xFFFEFFFF
#घोषणा   S_000044_I2C_INT(x)                          (((x) & 0x1) << 17)
#घोषणा   G_000044_I2C_INT(x)                          (((x) >> 17) & 0x1)
#घोषणा   C_000044_I2C_INT                             0xFFFDFFFF
#घोषणा   S_000044_SCRATCH_INT_STAT(x)                 (((x) & 0x1) << 18)
#घोषणा   G_000044_SCRATCH_INT_STAT(x)                 (((x) >> 18) & 0x1)
#घोषणा   C_000044_SCRATCH_INT_STAT                    0xFFFBFFFF
#घोषणा   S_000044_GUI_IDLE_STAT(x)                    (((x) & 0x1) << 19)
#घोषणा   G_000044_GUI_IDLE_STAT(x)                    (((x) >> 19) & 0x1)
#घोषणा   C_000044_GUI_IDLE_STAT                       0xFFF7FFFF
#घोषणा   S_000044_ATI_OVERDRIVE_INT_STAT(x)           (((x) & 0x1) << 20)
#घोषणा   G_000044_ATI_OVERDRIVE_INT_STAT(x)           (((x) >> 20) & 0x1)
#घोषणा   C_000044_ATI_OVERDRIVE_INT_STAT              0xFFEFFFFF
#घोषणा   S_000044_MC_PROTECTION_FAULT_STAT(x)         (((x) & 0x1) << 21)
#घोषणा   G_000044_MC_PROTECTION_FAULT_STAT(x)         (((x) >> 21) & 0x1)
#घोषणा   C_000044_MC_PROTECTION_FAULT_STAT            0xFFDFFFFF
#घोषणा   S_000044_RBBM_READ_INT_STAT(x)               (((x) & 0x1) << 22)
#घोषणा   G_000044_RBBM_READ_INT_STAT(x)               (((x) >> 22) & 0x1)
#घोषणा   C_000044_RBBM_READ_INT_STAT                  0xFFBFFFFF
#घोषणा   S_000044_CB_CONTEXT_SWITCH_STAT(x)           (((x) & 0x1) << 23)
#घोषणा   G_000044_CB_CONTEXT_SWITCH_STAT(x)           (((x) >> 23) & 0x1)
#घोषणा   C_000044_CB_CONTEXT_SWITCH_STAT              0xFF7FFFFF
#घोषणा   S_000044_VIPH_INT(x)                         (((x) & 0x1) << 24)
#घोषणा   G_000044_VIPH_INT(x)                         (((x) >> 24) & 0x1)
#घोषणा   C_000044_VIPH_INT                            0xFEFFFFFF
#घोषणा   S_000044_SW_INT(x)                           (((x) & 0x1) << 25)
#घोषणा   G_000044_SW_INT(x)                           (((x) >> 25) & 0x1)
#घोषणा   C_000044_SW_INT                              0xFDFFFFFF
#घोषणा   S_000044_SW_INT_SET(x)                       (((x) & 0x1) << 26)
#घोषणा   G_000044_SW_INT_SET(x)                       (((x) >> 26) & 0x1)
#घोषणा   C_000044_SW_INT_SET                          0xFBFFFFFF
#घोषणा   S_000044_IDCT_INT_STAT(x)                    (((x) & 0x1) << 27)
#घोषणा   G_000044_IDCT_INT_STAT(x)                    (((x) >> 27) & 0x1)
#घोषणा   C_000044_IDCT_INT_STAT                       0xF7FFFFFF
#घोषणा   S_000044_GUIDMA_STAT(x)                      (((x) & 0x1) << 30)
#घोषणा   G_000044_GUIDMA_STAT(x)                      (((x) >> 30) & 0x1)
#घोषणा   C_000044_GUIDMA_STAT                         0xBFFFFFFF
#घोषणा   S_000044_VIDDMA_STAT(x)                      (((x) & 0x1) << 31)
#घोषणा   G_000044_VIDDMA_STAT(x)                      (((x) >> 31) & 0x1)
#घोषणा   C_000044_VIDDMA_STAT                         0x7FFFFFFF
#घोषणा R_00004C_BUS_CNTL                            0x00004C
#घोषणा   S_00004C_BUS_MASTER_DIS(x)                   (((x) & 0x1) << 14)
#घोषणा   G_00004C_BUS_MASTER_DIS(x)                   (((x) >> 14) & 0x1)
#घोषणा   C_00004C_BUS_MASTER_DIS                      0xFFFFBFFF
#घोषणा   S_00004C_BUS_MSI_REARM(x)                    (((x) & 0x1) << 20)
#घोषणा   G_00004C_BUS_MSI_REARM(x)                    (((x) >> 20) & 0x1)
#घोषणा   C_00004C_BUS_MSI_REARM                       0xFFEFFFFF
#घोषणा R_000070_MC_IND_INDEX                        0x000070
#घोषणा   S_000070_MC_IND_ADDR(x)                      (((x) & 0xFFFF) << 0)
#घोषणा   G_000070_MC_IND_ADDR(x)                      (((x) >> 0) & 0xFFFF)
#घोषणा   C_000070_MC_IND_ADDR                         0xFFFF0000
#घोषणा   S_000070_MC_IND_SEQ_RBS_0(x)                 (((x) & 0x1) << 16)
#घोषणा   G_000070_MC_IND_SEQ_RBS_0(x)                 (((x) >> 16) & 0x1)
#घोषणा   C_000070_MC_IND_SEQ_RBS_0                    0xFFFEFFFF
#घोषणा   S_000070_MC_IND_SEQ_RBS_1(x)                 (((x) & 0x1) << 17)
#घोषणा   G_000070_MC_IND_SEQ_RBS_1(x)                 (((x) >> 17) & 0x1)
#घोषणा   C_000070_MC_IND_SEQ_RBS_1                    0xFFFDFFFF
#घोषणा   S_000070_MC_IND_SEQ_RBS_2(x)                 (((x) & 0x1) << 18)
#घोषणा   G_000070_MC_IND_SEQ_RBS_2(x)                 (((x) >> 18) & 0x1)
#घोषणा   C_000070_MC_IND_SEQ_RBS_2                    0xFFFBFFFF
#घोषणा   S_000070_MC_IND_SEQ_RBS_3(x)                 (((x) & 0x1) << 19)
#घोषणा   G_000070_MC_IND_SEQ_RBS_3(x)                 (((x) >> 19) & 0x1)
#घोषणा   C_000070_MC_IND_SEQ_RBS_3                    0xFFF7FFFF
#घोषणा   S_000070_MC_IND_AIC_RBS(x)                   (((x) & 0x1) << 20)
#घोषणा   G_000070_MC_IND_AIC_RBS(x)                   (((x) >> 20) & 0x1)
#घोषणा   C_000070_MC_IND_AIC_RBS                      0xFFEFFFFF
#घोषणा   S_000070_MC_IND_CITF_ARB0(x)                 (((x) & 0x1) << 21)
#घोषणा   G_000070_MC_IND_CITF_ARB0(x)                 (((x) >> 21) & 0x1)
#घोषणा   C_000070_MC_IND_CITF_ARB0                    0xFFDFFFFF
#घोषणा   S_000070_MC_IND_CITF_ARB1(x)                 (((x) & 0x1) << 22)
#घोषणा   G_000070_MC_IND_CITF_ARB1(x)                 (((x) >> 22) & 0x1)
#घोषणा   C_000070_MC_IND_CITF_ARB1                    0xFFBFFFFF
#घोषणा   S_000070_MC_IND_WR_EN(x)                     (((x) & 0x1) << 23)
#घोषणा   G_000070_MC_IND_WR_EN(x)                     (((x) >> 23) & 0x1)
#घोषणा   C_000070_MC_IND_WR_EN                        0xFF7FFFFF
#घोषणा   S_000070_MC_IND_RD_INV(x)                    (((x) & 0x1) << 24)
#घोषणा   G_000070_MC_IND_RD_INV(x)                    (((x) >> 24) & 0x1)
#घोषणा   C_000070_MC_IND_RD_INV                       0xFEFFFFFF
#घोषणा R_000074_MC_IND_DATA                         0x000074
#घोषणा   S_000074_MC_IND_DATA(x)                      (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_000074_MC_IND_DATA(x)                      (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_000074_MC_IND_DATA                         0x00000000
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
#घोषणा R_000134_HDP_FB_LOCATION                     0x000134
#घोषणा   S_000134_HDP_FB_START(x)                     (((x) & 0xFFFF) << 0)
#घोषणा   G_000134_HDP_FB_START(x)                     (((x) >> 0) & 0xFFFF)
#घोषणा   C_000134_HDP_FB_START                        0xFFFF0000
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
#घोषणा R_0060A4_D1CRTC_STATUS_FRAME_COUNT           0x0060A4
#घोषणा   S_0060A4_D1CRTC_FRAME_COUNT(x)               (((x) & 0xFFFFFF) << 0)
#घोषणा   G_0060A4_D1CRTC_FRAME_COUNT(x)               (((x) >> 0) & 0xFFFFFF)
#घोषणा   C_0060A4_D1CRTC_FRAME_COUNT                  0xFF000000
#घोषणा R_006534_D1MODE_VBLANK_STATUS                0x006534
#घोषणा   S_006534_D1MODE_VBLANK_OCCURRED(x)           (((x) & 0x1) << 0)
#घोषणा   G_006534_D1MODE_VBLANK_OCCURRED(x)           (((x) >> 0) & 0x1)
#घोषणा   C_006534_D1MODE_VBLANK_OCCURRED              0xFFFFFFFE
#घोषणा   S_006534_D1MODE_VBLANK_ACK(x)                (((x) & 0x1) << 4)
#घोषणा   G_006534_D1MODE_VBLANK_ACK(x)                (((x) >> 4) & 0x1)
#घोषणा   C_006534_D1MODE_VBLANK_ACK                   0xFFFFFFEF
#घोषणा   S_006534_D1MODE_VBLANK_STAT(x)               (((x) & 0x1) << 12)
#घोषणा   G_006534_D1MODE_VBLANK_STAT(x)               (((x) >> 12) & 0x1)
#घोषणा   C_006534_D1MODE_VBLANK_STAT                  0xFFFFEFFF
#घोषणा   S_006534_D1MODE_VBLANK_INTERRUPT(x)          (((x) & 0x1) << 16)
#घोषणा   G_006534_D1MODE_VBLANK_INTERRUPT(x)          (((x) >> 16) & 0x1)
#घोषणा   C_006534_D1MODE_VBLANK_INTERRUPT             0xFFFEFFFF
#घोषणा R_006540_DxMODE_INT_MASK                     0x006540
#घोषणा   S_006540_D1MODE_VBLANK_INT_MASK(x)           (((x) & 0x1) << 0)
#घोषणा   G_006540_D1MODE_VBLANK_INT_MASK(x)           (((x) >> 0) & 0x1)
#घोषणा   C_006540_D1MODE_VBLANK_INT_MASK              0xFFFFFFFE
#घोषणा   S_006540_D1MODE_VLINE_INT_MASK(x)            (((x) & 0x1) << 4)
#घोषणा   G_006540_D1MODE_VLINE_INT_MASK(x)            (((x) >> 4) & 0x1)
#घोषणा   C_006540_D1MODE_VLINE_INT_MASK               0xFFFFFFEF
#घोषणा   S_006540_D2MODE_VBLANK_INT_MASK(x)           (((x) & 0x1) << 8)
#घोषणा   G_006540_D2MODE_VBLANK_INT_MASK(x)           (((x) >> 8) & 0x1)
#घोषणा   C_006540_D2MODE_VBLANK_INT_MASK              0xFFFFFEFF
#घोषणा   S_006540_D2MODE_VLINE_INT_MASK(x)            (((x) & 0x1) << 12)
#घोषणा   G_006540_D2MODE_VLINE_INT_MASK(x)            (((x) >> 12) & 0x1)
#घोषणा   C_006540_D2MODE_VLINE_INT_MASK               0xFFFFEFFF
#घोषणा   S_006540_D1MODE_VBLANK_CP_SEL(x)             (((x) & 0x1) << 30)
#घोषणा   G_006540_D1MODE_VBLANK_CP_SEL(x)             (((x) >> 30) & 0x1)
#घोषणा   C_006540_D1MODE_VBLANK_CP_SEL                0xBFFFFFFF
#घोषणा   S_006540_D2MODE_VBLANK_CP_SEL(x)             (((x) & 0x1) << 31)
#घोषणा   G_006540_D2MODE_VBLANK_CP_SEL(x)             (((x) >> 31) & 0x1)
#घोषणा   C_006540_D2MODE_VBLANK_CP_SEL                0x7FFFFFFF
#घोषणा R_0068A4_D2CRTC_STATUS_FRAME_COUNT           0x0068A4
#घोषणा   S_0068A4_D2CRTC_FRAME_COUNT(x)               (((x) & 0xFFFFFF) << 0)
#घोषणा   G_0068A4_D2CRTC_FRAME_COUNT(x)               (((x) >> 0) & 0xFFFFFF)
#घोषणा   C_0068A4_D2CRTC_FRAME_COUNT                  0xFF000000
#घोषणा R_006D34_D2MODE_VBLANK_STATUS                0x006D34
#घोषणा   S_006D34_D2MODE_VBLANK_OCCURRED(x)           (((x) & 0x1) << 0)
#घोषणा   G_006D34_D2MODE_VBLANK_OCCURRED(x)           (((x) >> 0) & 0x1)
#घोषणा   C_006D34_D2MODE_VBLANK_OCCURRED              0xFFFFFFFE
#घोषणा   S_006D34_D2MODE_VBLANK_ACK(x)                (((x) & 0x1) << 4)
#घोषणा   G_006D34_D2MODE_VBLANK_ACK(x)                (((x) >> 4) & 0x1)
#घोषणा   C_006D34_D2MODE_VBLANK_ACK                   0xFFFFFFEF
#घोषणा   S_006D34_D2MODE_VBLANK_STAT(x)               (((x) & 0x1) << 12)
#घोषणा   G_006D34_D2MODE_VBLANK_STAT(x)               (((x) >> 12) & 0x1)
#घोषणा   C_006D34_D2MODE_VBLANK_STAT                  0xFFFFEFFF
#घोषणा   S_006D34_D2MODE_VBLANK_INTERRUPT(x)          (((x) & 0x1) << 16)
#घोषणा   G_006D34_D2MODE_VBLANK_INTERRUPT(x)          (((x) >> 16) & 0x1)
#घोषणा   C_006D34_D2MODE_VBLANK_INTERRUPT             0xFFFEFFFF
#घोषणा R_007EDC_DISP_INTERRUPT_STATUS               0x007EDC
#घोषणा   S_007EDC_LB_D1_VBLANK_INTERRUPT(x)           (((x) & 0x1) << 4)
#घोषणा   G_007EDC_LB_D1_VBLANK_INTERRUPT(x)           (((x) >> 4) & 0x1)
#घोषणा   C_007EDC_LB_D1_VBLANK_INTERRUPT              0xFFFFFFEF
#घोषणा   S_007EDC_LB_D2_VBLANK_INTERRUPT(x)           (((x) & 0x1) << 5)
#घोषणा   G_007EDC_LB_D2_VBLANK_INTERRUPT(x)           (((x) >> 5) & 0x1)
#घोषणा   C_007EDC_LB_D2_VBLANK_INTERRUPT              0xFFFFFFDF
#घोषणा   S_007EDC_DACA_AUTODETECT_INTERRUPT(x)        (((x) & 0x1) << 16)
#घोषणा   G_007EDC_DACA_AUTODETECT_INTERRUPT(x)        (((x) >> 16) & 0x1)
#घोषणा   C_007EDC_DACA_AUTODETECT_INTERRUPT           0xFFFEFFFF
#घोषणा   S_007EDC_DACB_AUTODETECT_INTERRUPT(x)        (((x) & 0x1) << 17)
#घोषणा   G_007EDC_DACB_AUTODETECT_INTERRUPT(x)        (((x) >> 17) & 0x1)
#घोषणा   C_007EDC_DACB_AUTODETECT_INTERRUPT           0xFFFDFFFF
#घोषणा   S_007EDC_DC_HOT_PLUG_DETECT1_INTERRUPT(x)    (((x) & 0x1) << 18)
#घोषणा   G_007EDC_DC_HOT_PLUG_DETECT1_INTERRUPT(x)    (((x) >> 18) & 0x1)
#घोषणा   C_007EDC_DC_HOT_PLUG_DETECT1_INTERRUPT       0xFFFBFFFF
#घोषणा   S_007EDC_DC_HOT_PLUG_DETECT2_INTERRUPT(x)    (((x) & 0x1) << 19)
#घोषणा   G_007EDC_DC_HOT_PLUG_DETECT2_INTERRUPT(x)    (((x) >> 19) & 0x1)
#घोषणा   C_007EDC_DC_HOT_PLUG_DETECT2_INTERRUPT       0xFFF7FFFF
#घोषणा R_007828_DACA_AUTODETECT_CONTROL               0x007828
#घोषणा   S_007828_DACA_AUTODETECT_MODE(x)             (((x) & 0x3) << 0)
#घोषणा   G_007828_DACA_AUTODETECT_MODE(x)             (((x) >> 0) & 0x3)
#घोषणा   C_007828_DACA_AUTODETECT_MODE                0xFFFFFFFC
#घोषणा   S_007828_DACA_AUTODETECT_FRAME_TIME_COUNTER(x) (((x) & 0xff) << 8)
#घोषणा   G_007828_DACA_AUTODETECT_FRAME_TIME_COUNTER(x) (((x) >> 8) & 0xff)
#घोषणा   C_007828_DACA_AUTODETECT_FRAME_TIME_COUNTER  0xFFFF00FF
#घोषणा   S_007828_DACA_AUTODETECT_CHECK_MASK(x)       (((x) & 0x3) << 16)
#घोषणा   G_007828_DACA_AUTODETECT_CHECK_MASK(x)       (((x) >> 16) & 0x3)
#घोषणा   C_007828_DACA_AUTODETECT_CHECK_MASK          0xFFFCFFFF
#घोषणा R_007838_DACA_AUTODETECT_INT_CONTROL           0x007838
#घोषणा   S_007838_DACA_AUTODETECT_ACK(x)              (((x) & 0x1) << 0)
#घोषणा   C_007838_DACA_DACA_AUTODETECT_ACK            0xFFFFFFFE
#घोषणा   S_007838_DACA_AUTODETECT_INT_ENABLE(x)       (((x) & 0x1) << 16)
#घोषणा   G_007838_DACA_AUTODETECT_INT_ENABLE(x)       (((x) >> 16) & 0x1)
#घोषणा   C_007838_DACA_AUTODETECT_INT_ENABLE          0xFFFCFFFF
#घोषणा R_007A28_DACB_AUTODETECT_CONTROL               0x007A28
#घोषणा   S_007A28_DACB_AUTODETECT_MODE(x)             (((x) & 0x3) << 0)
#घोषणा   G_007A28_DACB_AUTODETECT_MODE(x)             (((x) >> 0) & 0x3)
#घोषणा   C_007A28_DACB_AUTODETECT_MODE                0xFFFFFFFC
#घोषणा   S_007A28_DACB_AUTODETECT_FRAME_TIME_COUNTER(x) (((x) & 0xff) << 8)
#घोषणा   G_007A28_DACB_AUTODETECT_FRAME_TIME_COUNTER(x) (((x) >> 8) & 0xff)
#घोषणा   C_007A28_DACB_AUTODETECT_FRAME_TIME_COUNTER  0xFFFF00FF
#घोषणा   S_007A28_DACB_AUTODETECT_CHECK_MASK(x)       (((x) & 0x3) << 16)
#घोषणा   G_007A28_DACB_AUTODETECT_CHECK_MASK(x)       (((x) >> 16) & 0x3)
#घोषणा   C_007A28_DACB_AUTODETECT_CHECK_MASK          0xFFFCFFFF
#घोषणा R_007A38_DACB_AUTODETECT_INT_CONTROL           0x007A38
#घोषणा   S_007A38_DACB_AUTODETECT_ACK(x)              (((x) & 0x1) << 0)
#घोषणा   C_007A38_DACB_DACA_AUTODETECT_ACK            0xFFFFFFFE
#घोषणा   S_007A38_DACB_AUTODETECT_INT_ENABLE(x)       (((x) & 0x1) << 16)
#घोषणा   G_007A38_DACB_AUTODETECT_INT_ENABLE(x)       (((x) >> 16) & 0x1)
#घोषणा   C_007A38_DACB_AUTODETECT_INT_ENABLE          0xFFFCFFFF
#घोषणा R_007D00_DC_HOT_PLUG_DETECT1_CONTROL           0x007D00
#घोषणा   S_007D00_DC_HOT_PLUG_DETECT1_EN(x)           (((x) & 0x1) << 0)
#घोषणा   G_007D00_DC_HOT_PLUG_DETECT1_EN(x)           (((x) >> 0) & 0x1)
#घोषणा   C_007D00_DC_HOT_PLUG_DETECT1_EN              0xFFFFFFFE
#घोषणा R_007D04_DC_HOT_PLUG_DETECT1_INT_STATUS        0x007D04
#घोषणा   S_007D04_DC_HOT_PLUG_DETECT1_INT_STATUS(x)   (((x) & 0x1) << 0)
#घोषणा   G_007D04_DC_HOT_PLUG_DETECT1_INT_STATUS(x)   (((x) >> 0) & 0x1)
#घोषणा   C_007D04_DC_HOT_PLUG_DETECT1_INT_STATUS      0xFFFFFFFE
#घोषणा   S_007D04_DC_HOT_PLUG_DETECT1_SENSE(x)        (((x) & 0x1) << 1)
#घोषणा   G_007D04_DC_HOT_PLUG_DETECT1_SENSE(x)        (((x) >> 1) & 0x1)
#घोषणा   C_007D04_DC_HOT_PLUG_DETECT1_SENSE           0xFFFFFFFD
#घोषणा R_007D08_DC_HOT_PLUG_DETECT1_INT_CONTROL       0x007D08
#घोषणा   S_007D08_DC_HOT_PLUG_DETECT1_INT_ACK(x)      (((x) & 0x1) << 0)
#घोषणा   C_007D08_DC_HOT_PLUG_DETECT1_INT_ACK         0xFFFFFFFE
#घोषणा   S_007D08_DC_HOT_PLUG_DETECT1_INT_POLARITY(x) (((x) & 0x1) << 8)
#घोषणा   G_007D08_DC_HOT_PLUG_DETECT1_INT_POLARITY(x) (((x) >> 8) & 0x1)
#घोषणा   C_007D08_DC_HOT_PLUG_DETECT1_INT_POLARITY    0xFFFFFEFF
#घोषणा   S_007D08_DC_HOT_PLUG_DETECT1_INT_EN(x)       (((x) & 0x1) << 16)
#घोषणा   G_007D08_DC_HOT_PLUG_DETECT1_INT_EN(x)       (((x) >> 16) & 0x1)
#घोषणा   C_007D08_DC_HOT_PLUG_DETECT1_INT_EN          0xFFFEFFFF
#घोषणा R_007D10_DC_HOT_PLUG_DETECT2_CONTROL           0x007D10
#घोषणा   S_007D10_DC_HOT_PLUG_DETECT2_EN(x)           (((x) & 0x1) << 0)
#घोषणा   G_007D10_DC_HOT_PLUG_DETECT2_EN(x)           (((x) >> 0) & 0x1)
#घोषणा   C_007D10_DC_HOT_PLUG_DETECT2_EN              0xFFFFFFFE
#घोषणा R_007D14_DC_HOT_PLUG_DETECT2_INT_STATUS        0x007D14
#घोषणा   S_007D14_DC_HOT_PLUG_DETECT2_INT_STATUS(x)   (((x) & 0x1) << 0)
#घोषणा   G_007D14_DC_HOT_PLUG_DETECT2_INT_STATUS(x)   (((x) >> 0) & 0x1)
#घोषणा   C_007D14_DC_HOT_PLUG_DETECT2_INT_STATUS      0xFFFFFFFE
#घोषणा   S_007D14_DC_HOT_PLUG_DETECT2_SENSE(x)        (((x) & 0x1) << 1)
#घोषणा   G_007D14_DC_HOT_PLUG_DETECT2_SENSE(x)        (((x) >> 1) & 0x1)
#घोषणा   C_007D14_DC_HOT_PLUG_DETECT2_SENSE           0xFFFFFFFD
#घोषणा R_007D18_DC_HOT_PLUG_DETECT2_INT_CONTROL       0x007D18
#घोषणा   S_007D18_DC_HOT_PLUG_DETECT2_INT_ACK(x)      (((x) & 0x1) << 0)
#घोषणा   C_007D18_DC_HOT_PLUG_DETECT2_INT_ACK         0xFFFFFFFE
#घोषणा   S_007D18_DC_HOT_PLUG_DETECT2_INT_POLARITY(x) (((x) & 0x1) << 8)
#घोषणा   G_007D18_DC_HOT_PLUG_DETECT2_INT_POLARITY(x) (((x) >> 8) & 0x1)
#घोषणा   C_007D18_DC_HOT_PLUG_DETECT2_INT_POLARITY    0xFFFFFEFF
#घोषणा   S_007D18_DC_HOT_PLUG_DETECT2_INT_EN(x)       (((x) & 0x1) << 16)
#घोषणा   G_007D18_DC_HOT_PLUG_DETECT2_INT_EN(x)       (((x) >> 16) & 0x1)
#घोषणा   C_007D18_DC_HOT_PLUG_DETECT2_INT_EN          0xFFFEFFFF
#घोषणा R_007404_HDMI0_STATUS                          0x007404
#घोषणा   S_007404_HDMI0_AZ_FORMAT_WTRIG(x)            (((x) & 0x1) << 28)
#घोषणा   G_007404_HDMI0_AZ_FORMAT_WTRIG(x)            (((x) >> 28) & 0x1)
#घोषणा   C_007404_HDMI0_AZ_FORMAT_WTRIG               0xEFFFFFFF
#घोषणा   S_007404_HDMI0_AZ_FORMAT_WTRIG_INT(x)        (((x) & 0x1) << 29)
#घोषणा   G_007404_HDMI0_AZ_FORMAT_WTRIG_INT(x)        (((x) >> 29) & 0x1)
#घोषणा   C_007404_HDMI0_AZ_FORMAT_WTRIG_INT           0xDFFFFFFF
#घोषणा R_007408_HDMI0_AUDIO_PACKET_CONTROL            0x007408
#घोषणा   S_007408_HDMI0_AZ_FORMAT_WTRIG_MASK(x)       (((x) & 0x1) << 28)
#घोषणा   G_007408_HDMI0_AZ_FORMAT_WTRIG_MASK(x)       (((x) >> 28) & 0x1)
#घोषणा   C_007408_HDMI0_AZ_FORMAT_WTRIG_MASK          0xEFFFFFFF
#घोषणा   S_007408_HDMI0_AZ_FORMAT_WTRIG_ACK(x)        (((x) & 0x1) << 29)
#घोषणा   G_007408_HDMI0_AZ_FORMAT_WTRIG_ACK(x)        (((x) >> 29) & 0x1)
#घोषणा   C_007408_HDMI0_AZ_FORMAT_WTRIG_ACK           0xDFFFFFFF

/* MC रेजिस्टरs */
#घोषणा R_000000_MC_STATUS                           0x000000
#घोषणा   S_000000_MC_IDLE(x)                          (((x) & 0x1) << 0)
#घोषणा   G_000000_MC_IDLE(x)                          (((x) >> 0) & 0x1)
#घोषणा   C_000000_MC_IDLE                             0xFFFFFFFE
#घोषणा R_000004_MC_FB_LOCATION                      0x000004
#घोषणा   S_000004_MC_FB_START(x)                      (((x) & 0xFFFF) << 0)
#घोषणा   G_000004_MC_FB_START(x)                      (((x) >> 0) & 0xFFFF)
#घोषणा   C_000004_MC_FB_START                         0xFFFF0000
#घोषणा   S_000004_MC_FB_TOP(x)                        (((x) & 0xFFFF) << 16)
#घोषणा   G_000004_MC_FB_TOP(x)                        (((x) >> 16) & 0xFFFF)
#घोषणा   C_000004_MC_FB_TOP                           0x0000FFFF
#घोषणा R_000005_MC_AGP_LOCATION                     0x000005
#घोषणा   S_000005_MC_AGP_START(x)                     (((x) & 0xFFFF) << 0)
#घोषणा   G_000005_MC_AGP_START(x)                     (((x) >> 0) & 0xFFFF)
#घोषणा   C_000005_MC_AGP_START                        0xFFFF0000
#घोषणा   S_000005_MC_AGP_TOP(x)                       (((x) & 0xFFFF) << 16)
#घोषणा   G_000005_MC_AGP_TOP(x)                       (((x) >> 16) & 0xFFFF)
#घोषणा   C_000005_MC_AGP_TOP                          0x0000FFFF
#घोषणा R_000006_AGP_BASE                            0x000006
#घोषणा   S_000006_AGP_BASE_ADDR(x)                    (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_000006_AGP_BASE_ADDR(x)                    (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_000006_AGP_BASE_ADDR                       0x00000000
#घोषणा R_000007_AGP_BASE_2                          0x000007
#घोषणा   S_000007_AGP_BASE_ADDR_2(x)                  (((x) & 0xF) << 0)
#घोषणा   G_000007_AGP_BASE_ADDR_2(x)                  (((x) >> 0) & 0xF)
#घोषणा   C_000007_AGP_BASE_ADDR_2                     0xFFFFFFF0
#घोषणा R_000009_MC_CNTL1                            0x000009
#घोषणा   S_000009_ENABLE_PAGE_TABLES(x)               (((x) & 0x1) << 26)
#घोषणा   G_000009_ENABLE_PAGE_TABLES(x)               (((x) >> 26) & 0x1)
#घोषणा   C_000009_ENABLE_PAGE_TABLES                  0xFBFFFFFF
/* FIXME करोn't know the various field size need feedback from AMD */
#घोषणा R_000100_MC_PT0_CNTL                         0x000100
#घोषणा   S_000100_ENABLE_PT(x)                        (((x) & 0x1) << 0)
#घोषणा   G_000100_ENABLE_PT(x)                        (((x) >> 0) & 0x1)
#घोषणा   C_000100_ENABLE_PT                           0xFFFFFFFE
#घोषणा   S_000100_EFFECTIVE_L2_CACHE_SIZE(x)          (((x) & 0x7) << 15)
#घोषणा   G_000100_EFFECTIVE_L2_CACHE_SIZE(x)          (((x) >> 15) & 0x7)
#घोषणा   C_000100_EFFECTIVE_L2_CACHE_SIZE             0xFFFC7FFF
#घोषणा   S_000100_EFFECTIVE_L2_QUEUE_SIZE(x)          (((x) & 0x7) << 21)
#घोषणा   G_000100_EFFECTIVE_L2_QUEUE_SIZE(x)          (((x) >> 21) & 0x7)
#घोषणा   C_000100_EFFECTIVE_L2_QUEUE_SIZE             0xFF1FFFFF
#घोषणा   S_000100_INVALIDATE_ALL_L1_TLBS(x)           (((x) & 0x1) << 28)
#घोषणा   G_000100_INVALIDATE_ALL_L1_TLBS(x)           (((x) >> 28) & 0x1)
#घोषणा   C_000100_INVALIDATE_ALL_L1_TLBS              0xEFFFFFFF
#घोषणा   S_000100_INVALIDATE_L2_CACHE(x)              (((x) & 0x1) << 29)
#घोषणा   G_000100_INVALIDATE_L2_CACHE(x)              (((x) >> 29) & 0x1)
#घोषणा   C_000100_INVALIDATE_L2_CACHE                 0xDFFFFFFF
#घोषणा R_000102_MC_PT0_CONTEXT0_CNTL                0x000102
#घोषणा   S_000102_ENABLE_PAGE_TABLE(x)                (((x) & 0x1) << 0)
#घोषणा   G_000102_ENABLE_PAGE_TABLE(x)                (((x) >> 0) & 0x1)
#घोषणा   C_000102_ENABLE_PAGE_TABLE                   0xFFFFFFFE
#घोषणा   S_000102_PAGE_TABLE_DEPTH(x)                 (((x) & 0x3) << 1)
#घोषणा   G_000102_PAGE_TABLE_DEPTH(x)                 (((x) >> 1) & 0x3)
#घोषणा   C_000102_PAGE_TABLE_DEPTH                    0xFFFFFFF9
#घोषणा   V_000102_PAGE_TABLE_FLAT                     0
/* R600 करोcumentation suggest that this should be a number of pages */
#घोषणा R_000112_MC_PT0_SYSTEM_APERTURE_LOW_ADDR     0x000112
#घोषणा R_000114_MC_PT0_SYSTEM_APERTURE_HIGH_ADDR    0x000114
#घोषणा R_00011C_MC_PT0_CONTEXT0_DEFAULT_READ_ADDR   0x00011C
#घोषणा R_00012C_MC_PT0_CONTEXT0_FLAT_BASE_ADDR      0x00012C
#घोषणा R_00013C_MC_PT0_CONTEXT0_FLAT_START_ADDR     0x00013C
#घोषणा R_00014C_MC_PT0_CONTEXT0_FLAT_END_ADDR       0x00014C
#घोषणा R_00016C_MC_PT0_CLIENT0_CNTL                 0x00016C
#घोषणा   S_00016C_ENABLE_TRANSLATION_MODE_OVERRIDE(x) (((x) & 0x1) << 0)
#घोषणा   G_00016C_ENABLE_TRANSLATION_MODE_OVERRIDE(x) (((x) >> 0) & 0x1)
#घोषणा   C_00016C_ENABLE_TRANSLATION_MODE_OVERRIDE    0xFFFFFFFE
#घोषणा   S_00016C_TRANSLATION_MODE_OVERRIDE(x)        (((x) & 0x1) << 1)
#घोषणा   G_00016C_TRANSLATION_MODE_OVERRIDE(x)        (((x) >> 1) & 0x1)
#घोषणा   C_00016C_TRANSLATION_MODE_OVERRIDE           0xFFFFFFFD
#घोषणा   S_00016C_SYSTEM_ACCESS_MODE_MASK(x)          (((x) & 0x3) << 8)
#घोषणा   G_00016C_SYSTEM_ACCESS_MODE_MASK(x)          (((x) >> 8) & 0x3)
#घोषणा   C_00016C_SYSTEM_ACCESS_MODE_MASK             0xFFFFFCFF
#घोषणा   V_00016C_SYSTEM_ACCESS_MODE_PA_ONLY          0
#घोषणा   V_00016C_SYSTEM_ACCESS_MODE_USE_SYS_MAP      1
#घोषणा   V_00016C_SYSTEM_ACCESS_MODE_IN_SYS           2
#घोषणा   V_00016C_SYSTEM_ACCESS_MODE_NOT_IN_SYS       3
#घोषणा   S_00016C_SYSTEM_APERTURE_UNMAPPED_ACCESS(x)  (((x) & 0x1) << 10)
#घोषणा   G_00016C_SYSTEM_APERTURE_UNMAPPED_ACCESS(x)  (((x) >> 10) & 0x1)
#घोषणा   C_00016C_SYSTEM_APERTURE_UNMAPPED_ACCESS     0xFFFFFBFF
#घोषणा   V_00016C_SYSTEM_APERTURE_UNMAPPED_PASSTHROUGH  0
#घोषणा   V_00016C_SYSTEM_APERTURE_UNMAPPED_DEFAULT_PAGE 1
#घोषणा   S_00016C_EFFECTIVE_L1_CACHE_SIZE(x)          (((x) & 0x7) << 11)
#घोषणा   G_00016C_EFFECTIVE_L1_CACHE_SIZE(x)          (((x) >> 11) & 0x7)
#घोषणा   C_00016C_EFFECTIVE_L1_CACHE_SIZE             0xFFFFC7FF
#घोषणा   S_00016C_ENABLE_FRAGMENT_PROCESSING(x)       (((x) & 0x1) << 14)
#घोषणा   G_00016C_ENABLE_FRAGMENT_PROCESSING(x)       (((x) >> 14) & 0x1)
#घोषणा   C_00016C_ENABLE_FRAGMENT_PROCESSING          0xFFFFBFFF
#घोषणा   S_00016C_EFFECTIVE_L1_QUEUE_SIZE(x)          (((x) & 0x7) << 15)
#घोषणा   G_00016C_EFFECTIVE_L1_QUEUE_SIZE(x)          (((x) >> 15) & 0x7)
#घोषणा   C_00016C_EFFECTIVE_L1_QUEUE_SIZE             0xFFFC7FFF
#घोषणा   S_00016C_INVALIDATE_L1_TLB(x)                (((x) & 0x1) << 20)
#घोषणा   G_00016C_INVALIDATE_L1_TLB(x)                (((x) >> 20) & 0x1)
#घोषणा   C_00016C_INVALIDATE_L1_TLB                   0xFFEFFFFF

#घोषणा R_006548_D1MODE_PRIORITY_A_CNT               0x006548
#घोषणा   S_006548_D1MODE_PRIORITY_MARK_A(x)           (((x) & 0x7FFF) << 0)
#घोषणा   G_006548_D1MODE_PRIORITY_MARK_A(x)           (((x) >> 0) & 0x7FFF)
#घोषणा   C_006548_D1MODE_PRIORITY_MARK_A              0xFFFF8000
#घोषणा   S_006548_D1MODE_PRIORITY_A_OFF(x)            (((x) & 0x1) << 16)
#घोषणा   G_006548_D1MODE_PRIORITY_A_OFF(x)            (((x) >> 16) & 0x1)
#घोषणा   C_006548_D1MODE_PRIORITY_A_OFF               0xFFFEFFFF
#घोषणा   S_006548_D1MODE_PRIORITY_A_ALWAYS_ON(x)      (((x) & 0x1) << 20)
#घोषणा   G_006548_D1MODE_PRIORITY_A_ALWAYS_ON(x)      (((x) >> 20) & 0x1)
#घोषणा   C_006548_D1MODE_PRIORITY_A_ALWAYS_ON         0xFFEFFFFF
#घोषणा   S_006548_D1MODE_PRIORITY_A_FORCE_MASK(x)     (((x) & 0x1) << 24)
#घोषणा   G_006548_D1MODE_PRIORITY_A_FORCE_MASK(x)     (((x) >> 24) & 0x1)
#घोषणा   C_006548_D1MODE_PRIORITY_A_FORCE_MASK        0xFEFFFFFF
#घोषणा R_00654C_D1MODE_PRIORITY_B_CNT               0x00654C
#घोषणा   S_00654C_D1MODE_PRIORITY_MARK_B(x)           (((x) & 0x7FFF) << 0)
#घोषणा   G_00654C_D1MODE_PRIORITY_MARK_B(x)           (((x) >> 0) & 0x7FFF)
#घोषणा   C_00654C_D1MODE_PRIORITY_MARK_B              0xFFFF8000
#घोषणा   S_00654C_D1MODE_PRIORITY_B_OFF(x)            (((x) & 0x1) << 16)
#घोषणा   G_00654C_D1MODE_PRIORITY_B_OFF(x)            (((x) >> 16) & 0x1)
#घोषणा   C_00654C_D1MODE_PRIORITY_B_OFF               0xFFFEFFFF
#घोषणा   S_00654C_D1MODE_PRIORITY_B_ALWAYS_ON(x)      (((x) & 0x1) << 20)
#घोषणा   G_00654C_D1MODE_PRIORITY_B_ALWAYS_ON(x)      (((x) >> 20) & 0x1)
#घोषणा   C_00654C_D1MODE_PRIORITY_B_ALWAYS_ON         0xFFEFFFFF
#घोषणा   S_00654C_D1MODE_PRIORITY_B_FORCE_MASK(x)     (((x) & 0x1) << 24)
#घोषणा   G_00654C_D1MODE_PRIORITY_B_FORCE_MASK(x)     (((x) >> 24) & 0x1)
#घोषणा   C_00654C_D1MODE_PRIORITY_B_FORCE_MASK        0xFEFFFFFF
#घोषणा R_006D48_D2MODE_PRIORITY_A_CNT               0x006D48
#घोषणा   S_006D48_D2MODE_PRIORITY_MARK_A(x)           (((x) & 0x7FFF) << 0)
#घोषणा   G_006D48_D2MODE_PRIORITY_MARK_A(x)           (((x) >> 0) & 0x7FFF)
#घोषणा   C_006D48_D2MODE_PRIORITY_MARK_A              0xFFFF8000
#घोषणा   S_006D48_D2MODE_PRIORITY_A_OFF(x)            (((x) & 0x1) << 16)
#घोषणा   G_006D48_D2MODE_PRIORITY_A_OFF(x)            (((x) >> 16) & 0x1)
#घोषणा   C_006D48_D2MODE_PRIORITY_A_OFF               0xFFFEFFFF
#घोषणा   S_006D48_D2MODE_PRIORITY_A_ALWAYS_ON(x)      (((x) & 0x1) << 20)
#घोषणा   G_006D48_D2MODE_PRIORITY_A_ALWAYS_ON(x)      (((x) >> 20) & 0x1)
#घोषणा   C_006D48_D2MODE_PRIORITY_A_ALWAYS_ON         0xFFEFFFFF
#घोषणा   S_006D48_D2MODE_PRIORITY_A_FORCE_MASK(x)     (((x) & 0x1) << 24)
#घोषणा   G_006D48_D2MODE_PRIORITY_A_FORCE_MASK(x)     (((x) >> 24) & 0x1)
#घोषणा   C_006D48_D2MODE_PRIORITY_A_FORCE_MASK        0xFEFFFFFF
#घोषणा R_006D4C_D2MODE_PRIORITY_B_CNT               0x006D4C
#घोषणा   S_006D4C_D2MODE_PRIORITY_MARK_B(x)           (((x) & 0x7FFF) << 0)
#घोषणा   G_006D4C_D2MODE_PRIORITY_MARK_B(x)           (((x) >> 0) & 0x7FFF)
#घोषणा   C_006D4C_D2MODE_PRIORITY_MARK_B              0xFFFF8000
#घोषणा   S_006D4C_D2MODE_PRIORITY_B_OFF(x)            (((x) & 0x1) << 16)
#घोषणा   G_006D4C_D2MODE_PRIORITY_B_OFF(x)            (((x) >> 16) & 0x1)
#घोषणा   C_006D4C_D2MODE_PRIORITY_B_OFF               0xFFFEFFFF
#घोषणा   S_006D4C_D2MODE_PRIORITY_B_ALWAYS_ON(x)      (((x) & 0x1) << 20)
#घोषणा   G_006D4C_D2MODE_PRIORITY_B_ALWAYS_ON(x)      (((x) >> 20) & 0x1)
#घोषणा   C_006D4C_D2MODE_PRIORITY_B_ALWAYS_ON         0xFFEFFFFF
#घोषणा   S_006D4C_D2MODE_PRIORITY_B_FORCE_MASK(x)     (((x) & 0x1) << 24)
#घोषणा   G_006D4C_D2MODE_PRIORITY_B_FORCE_MASK(x)     (((x) >> 24) & 0x1)
#घोषणा   C_006D4C_D2MODE_PRIORITY_B_FORCE_MASK        0xFEFFFFFF

/* PLL regs */
#घोषणा GENERAL_PWRMGT                                 0x8
#घोषणा   GLOBAL_PWRMGT_EN                             (1 << 0)
#घोषणा   MOBILE_SU                                    (1 << 2)
#घोषणा DYN_PWRMGT_SCLK_LENGTH                         0xc
#घोषणा   NORMAL_POWER_SCLK_HILEN(x)                   ((x) << 0)
#घोषणा   NORMAL_POWER_SCLK_LOLEN(x)                   ((x) << 4)
#घोषणा   REDUCED_POWER_SCLK_HILEN(x)                  ((x) << 8)
#घोषणा   REDUCED_POWER_SCLK_LOLEN(x)                  ((x) << 12)
#घोषणा   POWER_D1_SCLK_HILEN(x)                       ((x) << 16)
#घोषणा   POWER_D1_SCLK_LOLEN(x)                       ((x) << 20)
#घोषणा   STATIC_SCREEN_HILEN(x)                       ((x) << 24)
#घोषणा   STATIC_SCREEN_LOLEN(x)                       ((x) << 28)
#घोषणा DYN_SCLK_VOL_CNTL                              0xe
#घोषणा   IO_CG_VOLTAGE_DROP                           (1 << 0)
#घोषणा   VOLTAGE_DROP_SYNC                            (1 << 2)
#घोषणा   VOLTAGE_DELAY_SEL(x)                         ((x) << 3)
#घोषणा HDP_DYN_CNTL                                   0x10
#घोषणा   HDP_FORCEON                                  (1 << 0)
#घोषणा MC_HOST_DYN_CNTL                               0x1e
#घोषणा   MC_HOST_FORCEON                              (1 << 0)
#घोषणा DYN_BACKBIAS_CNTL                              0x29
#घोषणा   IO_CG_BACKBIAS_EN                            (1 << 0)

/* mmreg */
#घोषणा DOUT_POWER_MANAGEMENT_CNTL                     0x7ee0
#घोषणा   PWRDN_WAIT_BUSY_OFF                          (1 << 0)
#घोषणा   PWRDN_WAIT_PWRSEQ_OFF                        (1 << 4)
#घोषणा   PWRDN_WAIT_PPLL_OFF                          (1 << 8)
#घोषणा   PWRUP_WAIT_PPLL_ON                           (1 << 12)
#घोषणा   PWRUP_WAIT_MEM_INIT_DONE                     (1 << 16)
#घोषणा   PM_ASSERT_RESET                              (1 << 20)
#घोषणा   PM_PWRDN_PPLL                                (1 << 24)

#पूर्ण_अगर
