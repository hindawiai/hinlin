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
#अगर_अघोषित __R520D_H__
#घोषणा __R520D_H__

/* Registers */
#घोषणा R_0000F8_CONFIG_MEMSIZE                      0x0000F8
#घोषणा   S_0000F8_CONFIG_MEMSIZE(x)                   (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_0000F8_CONFIG_MEMSIZE(x)                   (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_0000F8_CONFIG_MEMSIZE                      0x00000000
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
#घोषणा   S_000E40_RBBM_HIBUSY(x)                      (((x) & 0x1) << 28)
#घोषणा   G_000E40_RBBM_HIBUSY(x)                      (((x) >> 28) & 0x1)
#घोषणा   C_000E40_RBBM_HIBUSY                         0xEFFFFFFF
#घोषणा   S_000E40_SKID_CFBUSY(x)                      (((x) & 0x1) << 29)
#घोषणा   G_000E40_SKID_CFBUSY(x)                      (((x) >> 29) & 0x1)
#घोषणा   C_000E40_SKID_CFBUSY                         0xDFFFFFFF
#घोषणा   S_000E40_VAP_VF_BUSY(x)                      (((x) & 0x1) << 30)
#घोषणा   G_000E40_VAP_VF_BUSY(x)                      (((x) >> 30) & 0x1)
#घोषणा   C_000E40_VAP_VF_BUSY                         0xBFFFFFFF
#घोषणा   S_000E40_GUI_ACTIVE(x)                       (((x) & 0x1) << 31)
#घोषणा   G_000E40_GUI_ACTIVE(x)                       (((x) >> 31) & 0x1)
#घोषणा   C_000E40_GUI_ACTIVE                          0x7FFFFFFF


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

#पूर्ण_अगर
