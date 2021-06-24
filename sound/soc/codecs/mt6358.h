<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mt6358.h  --  mt6358 ALSA SoC audio codec driver
 *
 * Copyright (c) 2018 MediaTek Inc.
 * Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>
 */

#अगर_अघोषित __MT6358_H__
#घोषणा __MT6358_H__

/* Reg bit define */
/* MT6358_DCXO_CW14 */
#घोषणा RG_XO_AUDIO_EN_M_SFT 13

/* MT6358_DCXO_CW13 */
#घोषणा RG_XO_VOW_EN_SFT 8

/* MT6358_AUD_TOP_CKPDN_CON0 */
#घोषणा RG_VOW13M_CK_PDN_SFT                              13
#घोषणा RG_VOW13M_CK_PDN_MASK                             0x1
#घोषणा RG_VOW13M_CK_PDN_MASK_SFT                         (0x1 << 13)
#घोषणा RG_VOW32K_CK_PDN_SFT                              12
#घोषणा RG_VOW32K_CK_PDN_MASK                             0x1
#घोषणा RG_VOW32K_CK_PDN_MASK_SFT                         (0x1 << 12)
#घोषणा RG_AUD_INTRP_CK_PDN_SFT                           8
#घोषणा RG_AUD_INTRP_CK_PDN_MASK                          0x1
#घोषणा RG_AUD_INTRP_CK_PDN_MASK_SFT                      (0x1 << 8)
#घोषणा RG_PAD_AUD_CLK_MISO_CK_PDN_SFT                    7
#घोषणा RG_PAD_AUD_CLK_MISO_CK_PDN_MASK                   0x1
#घोषणा RG_PAD_AUD_CLK_MISO_CK_PDN_MASK_SFT               (0x1 << 7)
#घोषणा RG_AUDNCP_CK_PDN_SFT                              6
#घोषणा RG_AUDNCP_CK_PDN_MASK                             0x1
#घोषणा RG_AUDNCP_CK_PDN_MASK_SFT                         (0x1 << 6)
#घोषणा RG_ZCD13M_CK_PDN_SFT                              5
#घोषणा RG_ZCD13M_CK_PDN_MASK                             0x1
#घोषणा RG_ZCD13M_CK_PDN_MASK_SFT                         (0x1 << 5)
#घोषणा RG_AUDIF_CK_PDN_SFT                               2
#घोषणा RG_AUDIF_CK_PDN_MASK                              0x1
#घोषणा RG_AUDIF_CK_PDN_MASK_SFT                          (0x1 << 2)
#घोषणा RG_AUD_CK_PDN_SFT                                 1
#घोषणा RG_AUD_CK_PDN_MASK                                0x1
#घोषणा RG_AUD_CK_PDN_MASK_SFT                            (0x1 << 1)
#घोषणा RG_ACCDET_CK_PDN_SFT                              0
#घोषणा RG_ACCDET_CK_PDN_MASK                             0x1
#घोषणा RG_ACCDET_CK_PDN_MASK_SFT                         (0x1 << 0)

/* MT6358_AUD_TOP_CKPDN_CON0_SET */
#घोषणा RG_AUD_TOP_CKPDN_CON0_SET_SFT                     0
#घोषणा RG_AUD_TOP_CKPDN_CON0_SET_MASK                    0x3fff
#घोषणा RG_AUD_TOP_CKPDN_CON0_SET_MASK_SFT                (0x3fff << 0)

/* MT6358_AUD_TOP_CKPDN_CON0_CLR */
#घोषणा RG_AUD_TOP_CKPDN_CON0_CLR_SFT                     0
#घोषणा RG_AUD_TOP_CKPDN_CON0_CLR_MASK                    0x3fff
#घोषणा RG_AUD_TOP_CKPDN_CON0_CLR_MASK_SFT                (0x3fff << 0)

/* MT6358_AUD_TOP_CKSEL_CON0 */
#घोषणा RG_AUDIF_CK_CKSEL_SFT                             3
#घोषणा RG_AUDIF_CK_CKSEL_MASK                            0x1
#घोषणा RG_AUDIF_CK_CKSEL_MASK_SFT                        (0x1 << 3)
#घोषणा RG_AUD_CK_CKSEL_SFT                               2
#घोषणा RG_AUD_CK_CKSEL_MASK                              0x1
#घोषणा RG_AUD_CK_CKSEL_MASK_SFT                          (0x1 << 2)

/* MT6358_AUD_TOP_CKSEL_CON0_SET */
#घोषणा RG_AUD_TOP_CKSEL_CON0_SET_SFT                     0
#घोषणा RG_AUD_TOP_CKSEL_CON0_SET_MASK                    0xf
#घोषणा RG_AUD_TOP_CKSEL_CON0_SET_MASK_SFT                (0xf << 0)

/* MT6358_AUD_TOP_CKSEL_CON0_CLR */
#घोषणा RG_AUD_TOP_CKSEL_CON0_CLR_SFT                     0
#घोषणा RG_AUD_TOP_CKSEL_CON0_CLR_MASK                    0xf
#घोषणा RG_AUD_TOP_CKSEL_CON0_CLR_MASK_SFT                (0xf << 0)

/* MT6358_AUD_TOP_CKTST_CON0 */
#घोषणा RG_VOW13M_CK_TSTSEL_SFT                           9
#घोषणा RG_VOW13M_CK_TSTSEL_MASK                          0x1
#घोषणा RG_VOW13M_CK_TSTSEL_MASK_SFT                      (0x1 << 9)
#घोषणा RG_VOW13M_CK_TST_DIS_SFT                          8
#घोषणा RG_VOW13M_CK_TST_DIS_MASK                         0x1
#घोषणा RG_VOW13M_CK_TST_DIS_MASK_SFT                     (0x1 << 8)
#घोषणा RG_AUD26M_CK_TSTSEL_SFT                           4
#घोषणा RG_AUD26M_CK_TSTSEL_MASK                          0x1
#घोषणा RG_AUD26M_CK_TSTSEL_MASK_SFT                      (0x1 << 4)
#घोषणा RG_AUDIF_CK_TSTSEL_SFT                            3
#घोषणा RG_AUDIF_CK_TSTSEL_MASK                           0x1
#घोषणा RG_AUDIF_CK_TSTSEL_MASK_SFT                       (0x1 << 3)
#घोषणा RG_AUD_CK_TSTSEL_SFT                              2
#घोषणा RG_AUD_CK_TSTSEL_MASK                             0x1
#घोषणा RG_AUD_CK_TSTSEL_MASK_SFT                         (0x1 << 2)
#घोषणा RG_AUD26M_CK_TST_DIS_SFT                          0
#घोषणा RG_AUD26M_CK_TST_DIS_MASK                         0x1
#घोषणा RG_AUD26M_CK_TST_DIS_MASK_SFT                     (0x1 << 0)

/* MT6358_AUD_TOP_CLK_HWEN_CON0 */
#घोषणा RG_AUD_INTRP_CK_PDN_HWEN_SFT                      0
#घोषणा RG_AUD_INTRP_CK_PDN_HWEN_MASK                     0x1
#घोषणा RG_AUD_INTRP_CK_PDN_HWEN_MASK_SFT                 (0x1 << 0)

/* MT6358_AUD_TOP_CLK_HWEN_CON0_SET */
#घोषणा RG_AUD_INTRP_CK_PND_HWEN_CON0_SET_SFT             0
#घोषणा RG_AUD_INTRP_CK_PND_HWEN_CON0_SET_MASK            0xffff
#घोषणा RG_AUD_INTRP_CK_PND_HWEN_CON0_SET_MASK_SFT        (0xffff << 0)

/* MT6358_AUD_TOP_CLK_HWEN_CON0_CLR */
#घोषणा RG_AUD_INTRP_CLK_PDN_HWEN_CON0_CLR_SFT            0
#घोषणा RG_AUD_INTRP_CLK_PDN_HWEN_CON0_CLR_MASK           0xffff
#घोषणा RG_AUD_INTRP_CLK_PDN_HWEN_CON0_CLR_MASK_SFT       (0xffff << 0)

/* MT6358_AUD_TOP_RST_CON0 */
#घोषणा RG_AUDNCP_RST_SFT                                 3
#घोषणा RG_AUDNCP_RST_MASK                                0x1
#घोषणा RG_AUDNCP_RST_MASK_SFT                            (0x1 << 3)
#घोषणा RG_ZCD_RST_SFT                                    2
#घोषणा RG_ZCD_RST_MASK                                   0x1
#घोषणा RG_ZCD_RST_MASK_SFT                               (0x1 << 2)
#घोषणा RG_ACCDET_RST_SFT                                 1
#घोषणा RG_ACCDET_RST_MASK                                0x1
#घोषणा RG_ACCDET_RST_MASK_SFT                            (0x1 << 1)
#घोषणा RG_AUDIO_RST_SFT                                  0
#घोषणा RG_AUDIO_RST_MASK                                 0x1
#घोषणा RG_AUDIO_RST_MASK_SFT                             (0x1 << 0)

/* MT6358_AUD_TOP_RST_CON0_SET */
#घोषणा RG_AUD_TOP_RST_CON0_SET_SFT                       0
#घोषणा RG_AUD_TOP_RST_CON0_SET_MASK                      0xf
#घोषणा RG_AUD_TOP_RST_CON0_SET_MASK_SFT                  (0xf << 0)

/* MT6358_AUD_TOP_RST_CON0_CLR */
#घोषणा RG_AUD_TOP_RST_CON0_CLR_SFT                       0
#घोषणा RG_AUD_TOP_RST_CON0_CLR_MASK                      0xf
#घोषणा RG_AUD_TOP_RST_CON0_CLR_MASK_SFT                  (0xf << 0)

/* MT6358_AUD_TOP_RST_BANK_CON0 */
#घोषणा BANK_AUDZCD_SWRST_SFT                             2
#घोषणा BANK_AUDZCD_SWRST_MASK                            0x1
#घोषणा BANK_AUDZCD_SWRST_MASK_SFT                        (0x1 << 2)
#घोषणा BANK_AUDIO_SWRST_SFT                              1
#घोषणा BANK_AUDIO_SWRST_MASK                             0x1
#घोषणा BANK_AUDIO_SWRST_MASK_SFT                         (0x1 << 1)
#घोषणा BANK_ACCDET_SWRST_SFT                             0
#घोषणा BANK_ACCDET_SWRST_MASK                            0x1
#घोषणा BANK_ACCDET_SWRST_MASK_SFT                        (0x1 << 0)

/* MT6358_AUD_TOP_INT_CON0 */
#घोषणा RG_INT_EN_AUDIO_SFT                               0
#घोषणा RG_INT_EN_AUDIO_MASK                              0x1
#घोषणा RG_INT_EN_AUDIO_MASK_SFT                          (0x1 << 0)
#घोषणा RG_INT_EN_ACCDET_SFT                              5
#घोषणा RG_INT_EN_ACCDET_MASK                             0x1
#घोषणा RG_INT_EN_ACCDET_MASK_SFT                         (0x1 << 5)
#घोषणा RG_INT_EN_ACCDET_EINT0_SFT                        6
#घोषणा RG_INT_EN_ACCDET_EINT0_MASK                       0x1
#घोषणा RG_INT_EN_ACCDET_EINT0_MASK_SFT                   (0x1 << 6)
#घोषणा RG_INT_EN_ACCDET_EINT1_SFT                        7
#घोषणा RG_INT_EN_ACCDET_EINT1_MASK                       0x1
#घोषणा RG_INT_EN_ACCDET_EINT1_MASK_SFT                   (0x1 << 7)

/* MT6358_AUD_TOP_INT_CON0_SET */
#घोषणा RG_AUD_INT_CON0_SET_SFT                           0
#घोषणा RG_AUD_INT_CON0_SET_MASK                          0xffff
#घोषणा RG_AUD_INT_CON0_SET_MASK_SFT                      (0xffff << 0)

/* MT6358_AUD_TOP_INT_CON0_CLR */
#घोषणा RG_AUD_INT_CON0_CLR_SFT                           0
#घोषणा RG_AUD_INT_CON0_CLR_MASK                          0xffff
#घोषणा RG_AUD_INT_CON0_CLR_MASK_SFT                      (0xffff << 0)

/* MT6358_AUD_TOP_INT_MASK_CON0 */
#घोषणा RG_INT_MASK_AUDIO_SFT                             0
#घोषणा RG_INT_MASK_AUDIO_MASK                            0x1
#घोषणा RG_INT_MASK_AUDIO_MASK_SFT                        (0x1 << 0)
#घोषणा RG_INT_MASK_ACCDET_SFT                            5
#घोषणा RG_INT_MASK_ACCDET_MASK                           0x1
#घोषणा RG_INT_MASK_ACCDET_MASK_SFT                       (0x1 << 5)
#घोषणा RG_INT_MASK_ACCDET_EINT0_SFT                      6
#घोषणा RG_INT_MASK_ACCDET_EINT0_MASK                     0x1
#घोषणा RG_INT_MASK_ACCDET_EINT0_MASK_SFT                 (0x1 << 6)
#घोषणा RG_INT_MASK_ACCDET_EINT1_SFT                      7
#घोषणा RG_INT_MASK_ACCDET_EINT1_MASK                     0x1
#घोषणा RG_INT_MASK_ACCDET_EINT1_MASK_SFT                 (0x1 << 7)

/* MT6358_AUD_TOP_INT_MASK_CON0_SET */
#घोषणा RG_AUD_INT_MASK_CON0_SET_SFT                      0
#घोषणा RG_AUD_INT_MASK_CON0_SET_MASK                     0xff
#घोषणा RG_AUD_INT_MASK_CON0_SET_MASK_SFT                 (0xff << 0)

/* MT6358_AUD_TOP_INT_MASK_CON0_CLR */
#घोषणा RG_AUD_INT_MASK_CON0_CLR_SFT                      0
#घोषणा RG_AUD_INT_MASK_CON0_CLR_MASK                     0xff
#घोषणा RG_AUD_INT_MASK_CON0_CLR_MASK_SFT                 (0xff << 0)

/* MT6358_AUD_TOP_INT_STATUS0 */
#घोषणा RG_INT_STATUS_AUDIO_SFT                           0
#घोषणा RG_INT_STATUS_AUDIO_MASK                          0x1
#घोषणा RG_INT_STATUS_AUDIO_MASK_SFT                      (0x1 << 0)
#घोषणा RG_INT_STATUS_ACCDET_SFT                          5
#घोषणा RG_INT_STATUS_ACCDET_MASK                         0x1
#घोषणा RG_INT_STATUS_ACCDET_MASK_SFT                     (0x1 << 5)
#घोषणा RG_INT_STATUS_ACCDET_EINT0_SFT                    6
#घोषणा RG_INT_STATUS_ACCDET_EINT0_MASK                   0x1
#घोषणा RG_INT_STATUS_ACCDET_EINT0_MASK_SFT               (0x1 << 6)
#घोषणा RG_INT_STATUS_ACCDET_EINT1_SFT                    7
#घोषणा RG_INT_STATUS_ACCDET_EINT1_MASK                   0x1
#घोषणा RG_INT_STATUS_ACCDET_EINT1_MASK_SFT               (0x1 << 7)

/* MT6358_AUD_TOP_INT_RAW_STATUS0 */
#घोषणा RG_INT_RAW_STATUS_AUDIO_SFT                       0
#घोषणा RG_INT_RAW_STATUS_AUDIO_MASK                      0x1
#घोषणा RG_INT_RAW_STATUS_AUDIO_MASK_SFT                  (0x1 << 0)
#घोषणा RG_INT_RAW_STATUS_ACCDET_SFT                      5
#घोषणा RG_INT_RAW_STATUS_ACCDET_MASK                     0x1
#घोषणा RG_INT_RAW_STATUS_ACCDET_MASK_SFT                 (0x1 << 5)
#घोषणा RG_INT_RAW_STATUS_ACCDET_EINT0_SFT                6
#घोषणा RG_INT_RAW_STATUS_ACCDET_EINT0_MASK               0x1
#घोषणा RG_INT_RAW_STATUS_ACCDET_EINT0_MASK_SFT           (0x1 << 6)
#घोषणा RG_INT_RAW_STATUS_ACCDET_EINT1_SFT                7
#घोषणा RG_INT_RAW_STATUS_ACCDET_EINT1_MASK               0x1
#घोषणा RG_INT_RAW_STATUS_ACCDET_EINT1_MASK_SFT           (0x1 << 7)

/* MT6358_AUD_TOP_INT_MISC_CON0 */
#घोषणा RG_AUD_TOP_INT_POLARITY_SFT                       0
#घोषणा RG_AUD_TOP_INT_POLARITY_MASK                      0x1
#घोषणा RG_AUD_TOP_INT_POLARITY_MASK_SFT                  (0x1 << 0)

/* MT6358_AUDNCP_CLKDIV_CON0 */
#घोषणा RG_DIVCKS_CHG_SFT                                 0
#घोषणा RG_DIVCKS_CHG_MASK                                0x1
#घोषणा RG_DIVCKS_CHG_MASK_SFT                            (0x1 << 0)

/* MT6358_AUDNCP_CLKDIV_CON1 */
#घोषणा RG_DIVCKS_ON_SFT                                  0
#घोषणा RG_DIVCKS_ON_MASK                                 0x1
#घोषणा RG_DIVCKS_ON_MASK_SFT                             (0x1 << 0)

/* MT6358_AUDNCP_CLKDIV_CON2 */
#घोषणा RG_DIVCKS_PRG_SFT                                 0
#घोषणा RG_DIVCKS_PRG_MASK                                0x1ff
#घोषणा RG_DIVCKS_PRG_MASK_SFT                            (0x1ff << 0)

/* MT6358_AUDNCP_CLKDIV_CON3 */
#घोषणा RG_DIVCKS_PWD_NCP_SFT                             0
#घोषणा RG_DIVCKS_PWD_NCP_MASK                            0x1
#घोषणा RG_DIVCKS_PWD_NCP_MASK_SFT                        (0x1 << 0)

/* MT6358_AUDNCP_CLKDIV_CON4 */
#घोषणा RG_DIVCKS_PWD_NCP_ST_SEL_SFT                      0
#घोषणा RG_DIVCKS_PWD_NCP_ST_SEL_MASK                     0x3
#घोषणा RG_DIVCKS_PWD_NCP_ST_SEL_MASK_SFT                 (0x3 << 0)

/* MT6358_AUD_TOP_MON_CON0 */
#घोषणा RG_AUD_TOP_MON_SEL_SFT                            0
#घोषणा RG_AUD_TOP_MON_SEL_MASK                           0x7
#घोषणा RG_AUD_TOP_MON_SEL_MASK_SFT                       (0x7 << 0)
#घोषणा RG_AUD_CLK_INT_MON_FLAG_SEL_SFT                   3
#घोषणा RG_AUD_CLK_INT_MON_FLAG_SEL_MASK                  0xff
#घोषणा RG_AUD_CLK_INT_MON_FLAG_SEL_MASK_SFT              (0xff << 3)
#घोषणा RG_AUD_CLK_INT_MON_FLAG_EN_SFT                    11
#घोषणा RG_AUD_CLK_INT_MON_FLAG_EN_MASK                   0x1
#घोषणा RG_AUD_CLK_INT_MON_FLAG_EN_MASK_SFT               (0x1 << 11)

/* MT6358_AUDIO_DIG_DSN_ID */
#घोषणा AUDIO_DIG_ANA_ID_SFT                              0
#घोषणा AUDIO_DIG_ANA_ID_MASK                             0xff
#घोषणा AUDIO_DIG_ANA_ID_MASK_SFT                         (0xff << 0)
#घोषणा AUDIO_DIG_DIG_ID_SFT                              8
#घोषणा AUDIO_DIG_DIG_ID_MASK                             0xff
#घोषणा AUDIO_DIG_DIG_ID_MASK_SFT                         (0xff << 8)

/* MT6358_AUDIO_DIG_DSN_REV0 */
#घोषणा AUDIO_DIG_ANA_MINOR_REV_SFT                       0
#घोषणा AUDIO_DIG_ANA_MINOR_REV_MASK                      0xf
#घोषणा AUDIO_DIG_ANA_MINOR_REV_MASK_SFT                  (0xf << 0)
#घोषणा AUDIO_DIG_ANA_MAJOR_REV_SFT                       4
#घोषणा AUDIO_DIG_ANA_MAJOR_REV_MASK                      0xf
#घोषणा AUDIO_DIG_ANA_MAJOR_REV_MASK_SFT                  (0xf << 4)
#घोषणा AUDIO_DIG_DIG_MINOR_REV_SFT                       8
#घोषणा AUDIO_DIG_DIG_MINOR_REV_MASK                      0xf
#घोषणा AUDIO_DIG_DIG_MINOR_REV_MASK_SFT                  (0xf << 8)
#घोषणा AUDIO_DIG_DIG_MAJOR_REV_SFT                       12
#घोषणा AUDIO_DIG_DIG_MAJOR_REV_MASK                      0xf
#घोषणा AUDIO_DIG_DIG_MAJOR_REV_MASK_SFT                  (0xf << 12)

/* MT6358_AUDIO_DIG_DSN_DBI */
#घोषणा AUDIO_DIG_DSN_CBS_SFT                             0
#घोषणा AUDIO_DIG_DSN_CBS_MASK                            0x3
#घोषणा AUDIO_DIG_DSN_CBS_MASK_SFT                        (0x3 << 0)
#घोषणा AUDIO_DIG_DSN_BIX_SFT                             2
#घोषणा AUDIO_DIG_DSN_BIX_MASK                            0x3
#घोषणा AUDIO_DIG_DSN_BIX_MASK_SFT                        (0x3 << 2)
#घोषणा AUDIO_DIG_ESP_SFT                                 8
#घोषणा AUDIO_DIG_ESP_MASK                                0xff
#घोषणा AUDIO_DIG_ESP_MASK_SFT                            (0xff << 8)

/* MT6358_AUDIO_DIG_DSN_DXI */
#घोषणा AUDIO_DIG_DSN_FPI_SFT                             0
#घोषणा AUDIO_DIG_DSN_FPI_MASK                            0xff
#घोषणा AUDIO_DIG_DSN_FPI_MASK_SFT                        (0xff << 0)

/* MT6358_AFE_UL_DL_CON0 */
#घोषणा AFE_UL_LR_SWAP_SFT                                15
#घोषणा AFE_UL_LR_SWAP_MASK                               0x1
#घोषणा AFE_UL_LR_SWAP_MASK_SFT                           (0x1 << 15)
#घोषणा AFE_DL_LR_SWAP_SFT                                14
#घोषणा AFE_DL_LR_SWAP_MASK                               0x1
#घोषणा AFE_DL_LR_SWAP_MASK_SFT                           (0x1 << 14)
#घोषणा AFE_ON_SFT                                        0
#घोषणा AFE_ON_MASK                                       0x1
#घोषणा AFE_ON_MASK_SFT                                   (0x1 << 0)

/* MT6358_AFE_DL_SRC2_CON0_L */
#घोषणा DL_2_SRC_ON_TMP_CTL_PRE_SFT                       0
#घोषणा DL_2_SRC_ON_TMP_CTL_PRE_MASK                      0x1
#घोषणा DL_2_SRC_ON_TMP_CTL_PRE_MASK_SFT                  (0x1 << 0)

/* MT6358_AFE_UL_SRC_CON0_H */
#घोषणा C_DIGMIC_PHASE_SEL_CH1_CTL_SFT                    11
#घोषणा C_DIGMIC_PHASE_SEL_CH1_CTL_MASK                   0x7
#घोषणा C_DIGMIC_PHASE_SEL_CH1_CTL_MASK_SFT               (0x7 << 11)
#घोषणा C_DIGMIC_PHASE_SEL_CH2_CTL_SFT                    8
#घोषणा C_DIGMIC_PHASE_SEL_CH2_CTL_MASK                   0x7
#घोषणा C_DIGMIC_PHASE_SEL_CH2_CTL_MASK_SFT               (0x7 << 8)
#घोषणा C_TWO_DIGITAL_MIC_CTL_SFT                         7
#घोषणा C_TWO_DIGITAL_MIC_CTL_MASK                        0x1
#घोषणा C_TWO_DIGITAL_MIC_CTL_MASK_SFT                    (0x1 << 7)

/* MT6358_AFE_UL_SRC_CON0_L */
#घोषणा DMIC_LOW_POWER_MODE_CTL_SFT                       14
#घोषणा DMIC_LOW_POWER_MODE_CTL_MASK                      0x3
#घोषणा DMIC_LOW_POWER_MODE_CTL_MASK_SFT                  (0x3 << 14)
#घोषणा DIGMIC_3P25M_1P625M_SEL_CTL_SFT                   5
#घोषणा DIGMIC_3P25M_1P625M_SEL_CTL_MASK                  0x1
#घोषणा DIGMIC_3P25M_1P625M_SEL_CTL_MASK_SFT              (0x1 << 5)
#घोषणा UL_LOOP_BACK_MODE_CTL_SFT                         2
#घोषणा UL_LOOP_BACK_MODE_CTL_MASK                        0x1
#घोषणा UL_LOOP_BACK_MODE_CTL_MASK_SFT                    (0x1 << 2)
#घोषणा UL_SDM_3_LEVEL_CTL_SFT                            1
#घोषणा UL_SDM_3_LEVEL_CTL_MASK                           0x1
#घोषणा UL_SDM_3_LEVEL_CTL_MASK_SFT                       (0x1 << 1)
#घोषणा UL_SRC_ON_TMP_CTL_SFT                             0
#घोषणा UL_SRC_ON_TMP_CTL_MASK                            0x1
#घोषणा UL_SRC_ON_TMP_CTL_MASK_SFT                        (0x1 << 0)

/* MT6358_AFE_TOP_CON0 */
#घोषणा MTKAIF_SINE_ON_SFT                                2
#घोषणा MTKAIF_SINE_ON_MASK                               0x1
#घोषणा MTKAIF_SINE_ON_MASK_SFT                           (0x1 << 2)
#घोषणा UL_SINE_ON_SFT                                    1
#घोषणा UL_SINE_ON_MASK                                   0x1
#घोषणा UL_SINE_ON_MASK_SFT                               (0x1 << 1)
#घोषणा DL_SINE_ON_SFT                                    0
#घोषणा DL_SINE_ON_MASK                                   0x1
#घोषणा DL_SINE_ON_MASK_SFT                               (0x1 << 0)

/* MT6358_AUDIO_TOP_CON0 */
#घोषणा PDN_AFE_CTL_SFT                                   7
#घोषणा PDN_AFE_CTL_MASK                                  0x1
#घोषणा PDN_AFE_CTL_MASK_SFT                              (0x1 << 7)
#घोषणा PDN_DAC_CTL_SFT                                   6
#घोषणा PDN_DAC_CTL_MASK                                  0x1
#घोषणा PDN_DAC_CTL_MASK_SFT                              (0x1 << 6)
#घोषणा PDN_ADC_CTL_SFT                                   5
#घोषणा PDN_ADC_CTL_MASK                                  0x1
#घोषणा PDN_ADC_CTL_MASK_SFT                              (0x1 << 5)
#घोषणा PDN_I2S_DL_CTL_SFT                                3
#घोषणा PDN_I2S_DL_CTL_MASK                               0x1
#घोषणा PDN_I2S_DL_CTL_MASK_SFT                           (0x1 << 3)
#घोषणा PWR_CLK_DIS_CTL_SFT                               2
#घोषणा PWR_CLK_DIS_CTL_MASK                              0x1
#घोषणा PWR_CLK_DIS_CTL_MASK_SFT                          (0x1 << 2)
#घोषणा PDN_AFE_TESTMODEL_CTL_SFT                         1
#घोषणा PDN_AFE_TESTMODEL_CTL_MASK                        0x1
#घोषणा PDN_AFE_TESTMODEL_CTL_MASK_SFT                    (0x1 << 1)
#घोषणा PDN_RESERVED_SFT                                  0
#घोषणा PDN_RESERVED_MASK                                 0x1
#घोषणा PDN_RESERVED_MASK_SFT                             (0x1 << 0)

/* MT6358_AFE_MON_DEBUG0 */
#घोषणा AUDIO_SYS_TOP_MON_SWAP_SFT                        14
#घोषणा AUDIO_SYS_TOP_MON_SWAP_MASK                       0x3
#घोषणा AUDIO_SYS_TOP_MON_SWAP_MASK_SFT                   (0x3 << 14)
#घोषणा AUDIO_SYS_TOP_MON_SEL_SFT                         8
#घोषणा AUDIO_SYS_TOP_MON_SEL_MASK                        0x1f
#घोषणा AUDIO_SYS_TOP_MON_SEL_MASK_SFT                    (0x1f << 8)
#घोषणा AFE_MON_SEL_SFT                                   0
#घोषणा AFE_MON_SEL_MASK                                  0xff
#घोषणा AFE_MON_SEL_MASK_SFT                              (0xff << 0)

/* MT6358_AFUNC_AUD_CON0 */
#घोषणा CCI_AUD_ANACK_SEL_SFT                             15
#घोषणा CCI_AUD_ANACK_SEL_MASK                            0x1
#घोषणा CCI_AUD_ANACK_SEL_MASK_SFT                        (0x1 << 15)
#घोषणा CCI_AUDIO_FIFO_WPTR_SFT                           12
#घोषणा CCI_AUDIO_FIFO_WPTR_MASK                          0x7
#घोषणा CCI_AUDIO_FIFO_WPTR_MASK_SFT                      (0x7 << 12)
#घोषणा CCI_SCRAMBLER_CG_EN_SFT                           11
#घोषणा CCI_SCRAMBLER_CG_EN_MASK                          0x1
#घोषणा CCI_SCRAMBLER_CG_EN_MASK_SFT                      (0x1 << 11)
#घोषणा CCI_LCH_INV_SFT                                   10
#घोषणा CCI_LCH_INV_MASK                                  0x1
#घोषणा CCI_LCH_INV_MASK_SFT                              (0x1 << 10)
#घोषणा CCI_RAND_EN_SFT                                   9
#घोषणा CCI_RAND_EN_MASK                                  0x1
#घोषणा CCI_RAND_EN_MASK_SFT                              (0x1 << 9)
#घोषणा CCI_SPLT_SCRMB_CLK_ON_SFT                         8
#घोषणा CCI_SPLT_SCRMB_CLK_ON_MASK                        0x1
#घोषणा CCI_SPLT_SCRMB_CLK_ON_MASK_SFT                    (0x1 << 8)
#घोषणा CCI_SPLT_SCRMB_ON_SFT                             7
#घोषणा CCI_SPLT_SCRMB_ON_MASK                            0x1
#घोषणा CCI_SPLT_SCRMB_ON_MASK_SFT                        (0x1 << 7)
#घोषणा CCI_AUD_IDAC_TEST_EN_SFT                          6
#घोषणा CCI_AUD_IDAC_TEST_EN_MASK                         0x1
#घोषणा CCI_AUD_IDAC_TEST_EN_MASK_SFT                     (0x1 << 6)
#घोषणा CCI_ZERO_PAD_DISABLE_SFT                          5
#घोषणा CCI_ZERO_PAD_DISABLE_MASK                         0x1
#घोषणा CCI_ZERO_PAD_DISABLE_MASK_SFT                     (0x1 << 5)
#घोषणा CCI_AUD_SPLIT_TEST_EN_SFT                         4
#घोषणा CCI_AUD_SPLIT_TEST_EN_MASK                        0x1
#घोषणा CCI_AUD_SPLIT_TEST_EN_MASK_SFT                    (0x1 << 4)
#घोषणा CCI_AUD_SDM_MUTEL_SFT                             3
#घोषणा CCI_AUD_SDM_MUTEL_MASK                            0x1
#घोषणा CCI_AUD_SDM_MUTEL_MASK_SFT                        (0x1 << 3)
#घोषणा CCI_AUD_SDM_MUTER_SFT                             2
#घोषणा CCI_AUD_SDM_MUTER_MASK                            0x1
#घोषणा CCI_AUD_SDM_MUTER_MASK_SFT                        (0x1 << 2)
#घोषणा CCI_AUD_SDM_7BIT_SEL_SFT                          1
#घोषणा CCI_AUD_SDM_7BIT_SEL_MASK                         0x1
#घोषणा CCI_AUD_SDM_7BIT_SEL_MASK_SFT                     (0x1 << 1)
#घोषणा CCI_SCRAMBLER_EN_SFT                              0
#घोषणा CCI_SCRAMBLER_EN_MASK                             0x1
#घोषणा CCI_SCRAMBLER_EN_MASK_SFT                         (0x1 << 0)

/* MT6358_AFUNC_AUD_CON1 */
#घोषणा AUD_SDM_TEST_L_SFT                                8
#घोषणा AUD_SDM_TEST_L_MASK                               0xff
#घोषणा AUD_SDM_TEST_L_MASK_SFT                           (0xff << 8)
#घोषणा AUD_SDM_TEST_R_SFT                                0
#घोषणा AUD_SDM_TEST_R_MASK                               0xff
#घोषणा AUD_SDM_TEST_R_MASK_SFT                           (0xff << 0)

/* MT6358_AFUNC_AUD_CON2 */
#घोषणा CCI_AUD_DAC_ANA_MUTE_SFT                          7
#घोषणा CCI_AUD_DAC_ANA_MUTE_MASK                         0x1
#घोषणा CCI_AUD_DAC_ANA_MUTE_MASK_SFT                     (0x1 << 7)
#घोषणा CCI_AUD_DAC_ANA_RSTB_SEL_SFT                      6
#घोषणा CCI_AUD_DAC_ANA_RSTB_SEL_MASK                     0x1
#घोषणा CCI_AUD_DAC_ANA_RSTB_SEL_MASK_SFT                 (0x1 << 6)
#घोषणा CCI_AUDIO_FIFO_CLKIN_INV_SFT                      4
#घोषणा CCI_AUDIO_FIFO_CLKIN_INV_MASK                     0x1
#घोषणा CCI_AUDIO_FIFO_CLKIN_INV_MASK_SFT                 (0x1 << 4)
#घोषणा CCI_AUDIO_FIFO_ENABLE_SFT                         3
#घोषणा CCI_AUDIO_FIFO_ENABLE_MASK                        0x1
#घोषणा CCI_AUDIO_FIFO_ENABLE_MASK_SFT                    (0x1 << 3)
#घोषणा CCI_ACD_MODE_SFT                                  2
#घोषणा CCI_ACD_MODE_MASK                                 0x1
#घोषणा CCI_ACD_MODE_MASK_SFT                             (0x1 << 2)
#घोषणा CCI_AFIFO_CLK_PWDB_SFT                            1
#घोषणा CCI_AFIFO_CLK_PWDB_MASK                           0x1
#घोषणा CCI_AFIFO_CLK_PWDB_MASK_SFT                       (0x1 << 1)
#घोषणा CCI_ACD_FUNC_RSTB_SFT                             0
#घोषणा CCI_ACD_FUNC_RSTB_MASK                            0x1
#घोषणा CCI_ACD_FUNC_RSTB_MASK_SFT                        (0x1 << 0)

/* MT6358_AFUNC_AUD_CON3 */
#घोषणा SDM_ANA13M_TESTCK_SEL_SFT                         15
#घोषणा SDM_ANA13M_TESTCK_SEL_MASK                        0x1
#घोषणा SDM_ANA13M_TESTCK_SEL_MASK_SFT                    (0x1 << 15)
#घोषणा SDM_ANA13M_TESTCK_SRC_SEL_SFT                     12
#घोषणा SDM_ANA13M_TESTCK_SRC_SEL_MASK                    0x7
#घोषणा SDM_ANA13M_TESTCK_SRC_SEL_MASK_SFT                (0x7 << 12)
#घोषणा SDM_TESTCK_SRC_SEL_SFT                            8
#घोषणा SDM_TESTCK_SRC_SEL_MASK                           0x7
#घोषणा SDM_TESTCK_SRC_SEL_MASK_SFT                       (0x7 << 8)
#घोषणा DIGMIC_TESTCK_SRC_SEL_SFT                         4
#घोषणा DIGMIC_TESTCK_SRC_SEL_MASK                        0x7
#घोषणा DIGMIC_TESTCK_SRC_SEL_MASK_SFT                    (0x7 << 4)
#घोषणा DIGMIC_TESTCK_SEL_SFT                             0
#घोषणा DIGMIC_TESTCK_SEL_MASK                            0x1
#घोषणा DIGMIC_TESTCK_SEL_MASK_SFT                        (0x1 << 0)

/* MT6358_AFUNC_AUD_CON4 */
#घोषणा UL_FIFO_WCLK_INV_SFT                              8
#घोषणा UL_FIFO_WCLK_INV_MASK                             0x1
#घोषणा UL_FIFO_WCLK_INV_MASK_SFT                         (0x1 << 8)
#घोषणा UL_FIFO_DIGMIC_WDATA_TESTSRC_SEL_SFT              6
#घोषणा UL_FIFO_DIGMIC_WDATA_TESTSRC_SEL_MASK             0x1
#घोषणा UL_FIFO_DIGMIC_WDATA_TESTSRC_SEL_MASK_SFT         (0x1 << 6)
#घोषणा UL_FIFO_WDATA_TESTEN_SFT                          5
#घोषणा UL_FIFO_WDATA_TESTEN_MASK                         0x1
#घोषणा UL_FIFO_WDATA_TESTEN_MASK_SFT                     (0x1 << 5)
#घोषणा UL_FIFO_WDATA_TESTSRC_SEL_SFT                     4
#घोषणा UL_FIFO_WDATA_TESTSRC_SEL_MASK                    0x1
#घोषणा UL_FIFO_WDATA_TESTSRC_SEL_MASK_SFT                (0x1 << 4)
#घोषणा UL_FIFO_WCLK_6P5M_TESTCK_SEL_SFT                  3
#घोषणा UL_FIFO_WCLK_6P5M_TESTCK_SEL_MASK                 0x1
#घोषणा UL_FIFO_WCLK_6P5M_TESTCK_SEL_MASK_SFT             (0x1 << 3)
#घोषणा UL_FIFO_WCLK_6P5M_TESTCK_SRC_SEL_SFT              0
#घोषणा UL_FIFO_WCLK_6P5M_TESTCK_SRC_SEL_MASK             0x7
#घोषणा UL_FIFO_WCLK_6P5M_TESTCK_SRC_SEL_MASK_SFT         (0x7 << 0)

/* MT6358_AFUNC_AUD_CON5 */
#घोषणा R_AUD_DAC_POS_LARGE_MONO_SFT                      8
#घोषणा R_AUD_DAC_POS_LARGE_MONO_MASK                     0xff
#घोषणा R_AUD_DAC_POS_LARGE_MONO_MASK_SFT                 (0xff << 8)
#घोषणा R_AUD_DAC_NEG_LARGE_MONO_SFT                      0
#घोषणा R_AUD_DAC_NEG_LARGE_MONO_MASK                     0xff
#घोषणा R_AUD_DAC_NEG_LARGE_MONO_MASK_SFT                 (0xff << 0)

/* MT6358_AFUNC_AUD_CON6 */
#घोषणा R_AUD_DAC_POS_SMALL_MONO_SFT                      12
#घोषणा R_AUD_DAC_POS_SMALL_MONO_MASK                     0xf
#घोषणा R_AUD_DAC_POS_SMALL_MONO_MASK_SFT                 (0xf << 12)
#घोषणा R_AUD_DAC_NEG_SMALL_MONO_SFT                      8
#घोषणा R_AUD_DAC_NEG_SMALL_MONO_MASK                     0xf
#घोषणा R_AUD_DAC_NEG_SMALL_MONO_MASK_SFT                 (0xf << 8)
#घोषणा R_AUD_DAC_POS_TINY_MONO_SFT                       6
#घोषणा R_AUD_DAC_POS_TINY_MONO_MASK                      0x3
#घोषणा R_AUD_DAC_POS_TINY_MONO_MASK_SFT                  (0x3 << 6)
#घोषणा R_AUD_DAC_NEG_TINY_MONO_SFT                       4
#घोषणा R_AUD_DAC_NEG_TINY_MONO_MASK                      0x3
#घोषणा R_AUD_DAC_NEG_TINY_MONO_MASK_SFT                  (0x3 << 4)
#घोषणा R_AUD_DAC_MONO_SEL_SFT                            3
#घोषणा R_AUD_DAC_MONO_SEL_MASK                           0x1
#घोषणा R_AUD_DAC_MONO_SEL_MASK_SFT                       (0x1 << 3)
#घोषणा R_AUD_DAC_SW_RSTB_SFT                             0
#घोषणा R_AUD_DAC_SW_RSTB_MASK                            0x1
#घोषणा R_AUD_DAC_SW_RSTB_MASK_SFT                        (0x1 << 0)

/* MT6358_AFUNC_AUD_MON0 */
#घोषणा AUD_SCR_OUT_L_SFT                                 8
#घोषणा AUD_SCR_OUT_L_MASK                                0xff
#घोषणा AUD_SCR_OUT_L_MASK_SFT                            (0xff << 8)
#घोषणा AUD_SCR_OUT_R_SFT                                 0
#घोषणा AUD_SCR_OUT_R_MASK                                0xff
#घोषणा AUD_SCR_OUT_R_MASK_SFT                            (0xff << 0)

/* MT6358_AUDRC_TUNE_MON0 */
#घोषणा ASYNC_TEST_OUT_BCK_SFT                            15
#घोषणा ASYNC_TEST_OUT_BCK_MASK                           0x1
#घोषणा ASYNC_TEST_OUT_BCK_MASK_SFT                       (0x1 << 15)
#घोषणा RGS_AUDRCTUNE1READ_SFT                            8
#घोषणा RGS_AUDRCTUNE1READ_MASK                           0x1f
#घोषणा RGS_AUDRCTUNE1READ_MASK_SFT                       (0x1f << 8)
#घोषणा RGS_AUDRCTUNE0READ_SFT                            0
#घोषणा RGS_AUDRCTUNE0READ_MASK                           0x1f
#घोषणा RGS_AUDRCTUNE0READ_MASK_SFT                       (0x1f << 0)

/* MT6358_AFE_ADDA_MTKAIF_FIFO_CFG0 */
#घोषणा AFE_RESERVED_SFT                                  1
#घोषणा AFE_RESERVED_MASK                                 0x7fff
#घोषणा AFE_RESERVED_MASK_SFT                             (0x7fff << 1)
#घोषणा RG_MTKAIF_RXIF_FIFO_INTEN_SFT                     0
#घोषणा RG_MTKAIF_RXIF_FIFO_INTEN_MASK                    0x1
#घोषणा RG_MTKAIF_RXIF_FIFO_INTEN_MASK_SFT                (0x1 << 0)

/* MT6358_AFE_ADDA_MTKAIF_FIFO_LOG_MON1 */
#घोषणा MTKAIF_RXIF_WR_FULL_STATUS_SFT                    1
#घोषणा MTKAIF_RXIF_WR_FULL_STATUS_MASK                   0x1
#घोषणा MTKAIF_RXIF_WR_FULL_STATUS_MASK_SFT               (0x1 << 1)
#घोषणा MTKAIF_RXIF_RD_EMPTY_STATUS_SFT                   0
#घोषणा MTKAIF_RXIF_RD_EMPTY_STATUS_MASK                  0x1
#घोषणा MTKAIF_RXIF_RD_EMPTY_STATUS_MASK_SFT              (0x1 << 0)

/* MT6358_AFE_ADDA_MTKAIF_MON0 */
#घोषणा MTKAIFTX_V3_SYNC_OUT_SFT                          14
#घोषणा MTKAIFTX_V3_SYNC_OUT_MASK                         0x1
#घोषणा MTKAIFTX_V3_SYNC_OUT_MASK_SFT                     (0x1 << 14)
#घोषणा MTKAIFTX_V3_SDATA_OUT2_SFT                        13
#घोषणा MTKAIFTX_V3_SDATA_OUT2_MASK                       0x1
#घोषणा MTKAIFTX_V3_SDATA_OUT2_MASK_SFT                   (0x1 << 13)
#घोषणा MTKAIFTX_V3_SDATA_OUT1_SFT                        12
#घोषणा MTKAIFTX_V3_SDATA_OUT1_MASK                       0x1
#घोषणा MTKAIFTX_V3_SDATA_OUT1_MASK_SFT                   (0x1 << 12)
#घोषणा MTKAIF_RXIF_FIFO_STATUS_SFT                       0
#घोषणा MTKAIF_RXIF_FIFO_STATUS_MASK                      0xfff
#घोषणा MTKAIF_RXIF_FIFO_STATUS_MASK_SFT                  (0xfff << 0)

/* MT6358_AFE_ADDA_MTKAIF_MON1 */
#घोषणा MTKAIFRX_V3_SYNC_IN_SFT                           14
#घोषणा MTKAIFRX_V3_SYNC_IN_MASK                          0x1
#घोषणा MTKAIFRX_V3_SYNC_IN_MASK_SFT                      (0x1 << 14)
#घोषणा MTKAIFRX_V3_SDATA_IN2_SFT                         13
#घोषणा MTKAIFRX_V3_SDATA_IN2_MASK                        0x1
#घोषणा MTKAIFRX_V3_SDATA_IN2_MASK_SFT                    (0x1 << 13)
#घोषणा MTKAIFRX_V3_SDATA_IN1_SFT                         12
#घोषणा MTKAIFRX_V3_SDATA_IN1_MASK                        0x1
#घोषणा MTKAIFRX_V3_SDATA_IN1_MASK_SFT                    (0x1 << 12)
#घोषणा MTKAIF_RXIF_SEARCH_FAIL_FLAG_SFT                  11
#घोषणा MTKAIF_RXIF_SEARCH_FAIL_FLAG_MASK                 0x1
#घोषणा MTKAIF_RXIF_SEARCH_FAIL_FLAG_MASK_SFT             (0x1 << 11)
#घोषणा MTKAIF_RXIF_INVALID_FLAG_SFT                      8
#घोषणा MTKAIF_RXIF_INVALID_FLAG_MASK                     0x1
#घोषणा MTKAIF_RXIF_INVALID_FLAG_MASK_SFT                 (0x1 << 8)
#घोषणा MTKAIF_RXIF_INVALID_CYCLE_SFT                     0
#घोषणा MTKAIF_RXIF_INVALID_CYCLE_MASK                    0xff
#घोषणा MTKAIF_RXIF_INVALID_CYCLE_MASK_SFT                (0xff << 0)

/* MT6358_AFE_ADDA_MTKAIF_MON2 */
#घोषणा MTKAIF_TXIF_IN_CH2_SFT                            8
#घोषणा MTKAIF_TXIF_IN_CH2_MASK                           0xff
#घोषणा MTKAIF_TXIF_IN_CH2_MASK_SFT                       (0xff << 8)
#घोषणा MTKAIF_TXIF_IN_CH1_SFT                            0
#घोषणा MTKAIF_TXIF_IN_CH1_MASK                           0xff
#घोषणा MTKAIF_TXIF_IN_CH1_MASK_SFT                       (0xff << 0)

/* MT6358_AFE_ADDA_MTKAIF_MON3 */
#घोषणा MTKAIF_RXIF_OUT_CH2_SFT                           8
#घोषणा MTKAIF_RXIF_OUT_CH2_MASK                          0xff
#घोषणा MTKAIF_RXIF_OUT_CH2_MASK_SFT                      (0xff << 8)
#घोषणा MTKAIF_RXIF_OUT_CH1_SFT                           0
#घोषणा MTKAIF_RXIF_OUT_CH1_MASK                          0xff
#घोषणा MTKAIF_RXIF_OUT_CH1_MASK_SFT                      (0xff << 0)

/* MT6358_AFE_ADDA_MTKAIF_CFG0 */
#घोषणा RG_MTKAIF_RXIF_CLKINV_SFT                         15
#घोषणा RG_MTKAIF_RXIF_CLKINV_MASK                        0x1
#घोषणा RG_MTKAIF_RXIF_CLKINV_MASK_SFT                    (0x1 << 15)
#घोषणा RG_MTKAIF_RXIF_PROTOCOL2_SFT                      8
#घोषणा RG_MTKAIF_RXIF_PROTOCOL2_MASK                     0x1
#घोषणा RG_MTKAIF_RXIF_PROTOCOL2_MASK_SFT                 (0x1 << 8)
#घोषणा RG_MTKAIF_BYPASS_SRC_MODE_SFT                     6
#घोषणा RG_MTKAIF_BYPASS_SRC_MODE_MASK                    0x3
#घोषणा RG_MTKAIF_BYPASS_SRC_MODE_MASK_SFT                (0x3 << 6)
#घोषणा RG_MTKAIF_BYPASS_SRC_TEST_SFT                     5
#घोषणा RG_MTKAIF_BYPASS_SRC_TEST_MASK                    0x1
#घोषणा RG_MTKAIF_BYPASS_SRC_TEST_MASK_SFT                (0x1 << 5)
#घोषणा RG_MTKAIF_TXIF_PROTOCOL2_SFT                      4
#घोषणा RG_MTKAIF_TXIF_PROTOCOL2_MASK                     0x1
#घोषणा RG_MTKAIF_TXIF_PROTOCOL2_MASK_SFT                 (0x1 << 4)
#घोषणा RG_MTKAIF_PMIC_TXIF_8TO5_SFT                      2
#घोषणा RG_MTKAIF_PMIC_TXIF_8TO5_MASK                     0x1
#घोषणा RG_MTKAIF_PMIC_TXIF_8TO5_MASK_SFT                 (0x1 << 2)
#घोषणा RG_MTKAIF_LOOPBACK_TEST2_SFT                      1
#घोषणा RG_MTKAIF_LOOPBACK_TEST2_MASK                     0x1
#घोषणा RG_MTKAIF_LOOPBACK_TEST2_MASK_SFT                 (0x1 << 1)
#घोषणा RG_MTKAIF_LOOPBACK_TEST1_SFT                      0
#घोषणा RG_MTKAIF_LOOPBACK_TEST1_MASK                     0x1
#घोषणा RG_MTKAIF_LOOPBACK_TEST1_MASK_SFT                 (0x1 << 0)

/* MT6358_AFE_ADDA_MTKAIF_RX_CFG0 */
#घोषणा RG_MTKAIF_RXIF_VOICE_MODE_SFT                     12
#घोषणा RG_MTKAIF_RXIF_VOICE_MODE_MASK                    0xf
#घोषणा RG_MTKAIF_RXIF_VOICE_MODE_MASK_SFT                (0xf << 12)
#घोषणा RG_MTKAIF_RXIF_DATA_BIT_SFT                       8
#घोषणा RG_MTKAIF_RXIF_DATA_BIT_MASK                      0x7
#घोषणा RG_MTKAIF_RXIF_DATA_BIT_MASK_SFT                  (0x7 << 8)
#घोषणा RG_MTKAIF_RXIF_FIFO_RSP_SFT                       4
#घोषणा RG_MTKAIF_RXIF_FIFO_RSP_MASK                      0x7
#घोषणा RG_MTKAIF_RXIF_FIFO_RSP_MASK_SFT                  (0x7 << 4)
#घोषणा RG_MTKAIF_RXIF_DETECT_ON_SFT                      3
#घोषणा RG_MTKAIF_RXIF_DETECT_ON_MASK                     0x1
#घोषणा RG_MTKAIF_RXIF_DETECT_ON_MASK_SFT                 (0x1 << 3)
#घोषणा RG_MTKAIF_RXIF_DATA_MODE_SFT                      0
#घोषणा RG_MTKAIF_RXIF_DATA_MODE_MASK                     0x1
#घोषणा RG_MTKAIF_RXIF_DATA_MODE_MASK_SFT                 (0x1 << 0)

/* MT6358_AFE_ADDA_MTKAIF_RX_CFG1 */
#घोषणा RG_MTKAIF_RXIF_SYNC_SEARCH_TABLE_SFT              12
#घोषणा RG_MTKAIF_RXIF_SYNC_SEARCH_TABLE_MASK             0xf
#घोषणा RG_MTKAIF_RXIF_SYNC_SEARCH_TABLE_MASK_SFT         (0xf << 12)
#घोषणा RG_MTKAIF_RXIF_INVALID_SYNC_CHECK_ROUND_SFT       8
#घोषणा RG_MTKAIF_RXIF_INVALID_SYNC_CHECK_ROUND_MASK      0xf
#घोषणा RG_MTKAIF_RXIF_INVALID_SYNC_CHECK_ROUND_MASK_SFT  (0xf << 8)
#घोषणा RG_MTKAIF_RXIF_SYNC_CHECK_ROUND_SFT               4
#घोषणा RG_MTKAIF_RXIF_SYNC_CHECK_ROUND_MASK              0xf
#घोषणा RG_MTKAIF_RXIF_SYNC_CHECK_ROUND_MASK_SFT          (0xf << 4)
#घोषणा RG_MTKAIF_RXIF_VOICE_MODE_PROTOCOL2_SFT           0
#घोषणा RG_MTKAIF_RXIF_VOICE_MODE_PROTOCOL2_MASK          0xf
#घोषणा RG_MTKAIF_RXIF_VOICE_MODE_PROTOCOL2_MASK_SFT      (0xf << 0)

/* MT6358_AFE_ADDA_MTKAIF_RX_CFG2 */
#घोषणा RG_MTKAIF_RXIF_CLEAR_SYNC_FAIL_SFT                12
#घोषणा RG_MTKAIF_RXIF_CLEAR_SYNC_FAIL_MASK               0x1
#घोषणा RG_MTKAIF_RXIF_CLEAR_SYNC_FAIL_MASK_SFT           (0x1 << 12)
#घोषणा RG_MTKAIF_RXIF_SYNC_CNT_TABLE_SFT                 0
#घोषणा RG_MTKAIF_RXIF_SYNC_CNT_TABLE_MASK                0xfff
#घोषणा RG_MTKAIF_RXIF_SYNC_CNT_TABLE_MASK_SFT            (0xfff << 0)

/* MT6358_AFE_ADDA_MTKAIF_RX_CFG3 */
#घोषणा RG_MTKAIF_RXIF_LOOPBACK_USE_NLE_SFT               7
#घोषणा RG_MTKAIF_RXIF_LOOPBACK_USE_NLE_MASK              0x1
#घोषणा RG_MTKAIF_RXIF_LOOPBACK_USE_NLE_MASK_SFT          (0x1 << 7)
#घोषणा RG_MTKAIF_RXIF_FIFO_RSP_PROTOCOL2_SFT             4
#घोषणा RG_MTKAIF_RXIF_FIFO_RSP_PROTOCOL2_MASK            0x7
#घोषणा RG_MTKAIF_RXIF_FIFO_RSP_PROTOCOL2_MASK_SFT        (0x7 << 4)
#घोषणा RG_MTKAIF_RXIF_DETECT_ON_PROTOCOL2_SFT            3
#घोषणा RG_MTKAIF_RXIF_DETECT_ON_PROTOCOL2_MASK           0x1
#घोषणा RG_MTKAIF_RXIF_DETECT_ON_PROTOCOL2_MASK_SFT       (0x1 << 3)

/* MT6358_AFE_ADDA_MTKAIF_TX_CFG1 */
#घोषणा RG_MTKAIF_SYNC_WORD2_SFT                          4
#घोषणा RG_MTKAIF_SYNC_WORD2_MASK                         0x7
#घोषणा RG_MTKAIF_SYNC_WORD2_MASK_SFT                     (0x7 << 4)
#घोषणा RG_MTKAIF_SYNC_WORD1_SFT                          0
#घोषणा RG_MTKAIF_SYNC_WORD1_MASK                         0x7
#घोषणा RG_MTKAIF_SYNC_WORD1_MASK_SFT                     (0x7 << 0)

/* MT6358_AFE_SGEN_CFG0 */
#घोषणा SGEN_AMP_DIV_CH1_CTL_SFT                          12
#घोषणा SGEN_AMP_DIV_CH1_CTL_MASK                         0xf
#घोषणा SGEN_AMP_DIV_CH1_CTL_MASK_SFT                     (0xf << 12)
#घोषणा SGEN_DAC_EN_CTL_SFT                               7
#घोषणा SGEN_DAC_EN_CTL_MASK                              0x1
#घोषणा SGEN_DAC_EN_CTL_MASK_SFT                          (0x1 << 7)
#घोषणा SGEN_MUTE_SW_CTL_SFT                              6
#घोषणा SGEN_MUTE_SW_CTL_MASK                             0x1
#घोषणा SGEN_MUTE_SW_CTL_MASK_SFT                         (0x1 << 6)
#घोषणा R_AUD_SDM_MUTE_L_SFT                              5
#घोषणा R_AUD_SDM_MUTE_L_MASK                             0x1
#घोषणा R_AUD_SDM_MUTE_L_MASK_SFT                         (0x1 << 5)
#घोषणा R_AUD_SDM_MUTE_R_SFT                              4
#घोषणा R_AUD_SDM_MUTE_R_MASK                             0x1
#घोषणा R_AUD_SDM_MUTE_R_MASK_SFT                         (0x1 << 4)

/* MT6358_AFE_SGEN_CFG1 */
#घोषणा C_SGEN_RCH_INV_5BIT_SFT                           15
#घोषणा C_SGEN_RCH_INV_5BIT_MASK                          0x1
#घोषणा C_SGEN_RCH_INV_5BIT_MASK_SFT                      (0x1 << 15)
#घोषणा C_SGEN_RCH_INV_8BIT_SFT                           14
#घोषणा C_SGEN_RCH_INV_8BIT_MASK                          0x1
#घोषणा C_SGEN_RCH_INV_8BIT_MASK_SFT                      (0x1 << 14)
#घोषणा SGEN_FREQ_DIV_CH1_CTL_SFT                         0
#घोषणा SGEN_FREQ_DIV_CH1_CTL_MASK                        0x1f
#घोषणा SGEN_FREQ_DIV_CH1_CTL_MASK_SFT                    (0x1f << 0)

/* MT6358_AFE_ADC_ASYNC_FIFO_CFG */
#घोषणा RG_UL_ASYNC_FIFO_SOFT_RST_EN_SFT                  5
#घोषणा RG_UL_ASYNC_FIFO_SOFT_RST_EN_MASK                 0x1
#घोषणा RG_UL_ASYNC_FIFO_SOFT_RST_EN_MASK_SFT             (0x1 << 5)
#घोषणा RG_UL_ASYNC_FIFO_SOFT_RST_SFT                     4
#घोषणा RG_UL_ASYNC_FIFO_SOFT_RST_MASK                    0x1
#घोषणा RG_UL_ASYNC_FIFO_SOFT_RST_MASK_SFT                (0x1 << 4)
#घोषणा RG_AMIC_UL_ADC_CLK_SEL_SFT                        1
#घोषणा RG_AMIC_UL_ADC_CLK_SEL_MASK                       0x1
#घोषणा RG_AMIC_UL_ADC_CLK_SEL_MASK_SFT                   (0x1 << 1)

/* MT6358_AFE_DCCLK_CFG0 */
#घोषणा DCCLK_DIV_SFT                                     5
#घोषणा DCCLK_DIV_MASK                                    0x7ff
#घोषणा DCCLK_DIV_MASK_SFT                                (0x7ff << 5)
#घोषणा DCCLK_INV_SFT                                     4
#घोषणा DCCLK_INV_MASK                                    0x1
#घोषणा DCCLK_INV_MASK_SFT                                (0x1 << 4)
#घोषणा DCCLK_PDN_SFT                                     1
#घोषणा DCCLK_PDN_MASK                                    0x1
#घोषणा DCCLK_PDN_MASK_SFT                                (0x1 << 1)
#घोषणा DCCLK_GEN_ON_SFT                                  0
#घोषणा DCCLK_GEN_ON_MASK                                 0x1
#घोषणा DCCLK_GEN_ON_MASK_SFT                             (0x1 << 0)

/* MT6358_AFE_DCCLK_CFG1 */
#घोषणा RESYNC_SRC_SEL_SFT                                10
#घोषणा RESYNC_SRC_SEL_MASK                               0x3
#घोषणा RESYNC_SRC_SEL_MASK_SFT                           (0x3 << 10)
#घोषणा RESYNC_SRC_CK_INV_SFT                             9
#घोषणा RESYNC_SRC_CK_INV_MASK                            0x1
#घोषणा RESYNC_SRC_CK_INV_MASK_SFT                        (0x1 << 9)
#घोषणा DCCLK_RESYNC_BYPASS_SFT                           8
#घोषणा DCCLK_RESYNC_BYPASS_MASK                          0x1
#घोषणा DCCLK_RESYNC_BYPASS_MASK_SFT                      (0x1 << 8)
#घोषणा DCCLK_PHASE_SEL_SFT                               4
#घोषणा DCCLK_PHASE_SEL_MASK                              0xf
#घोषणा DCCLK_PHASE_SEL_MASK_SFT                          (0xf << 4)

/* MT6358_AUDIO_DIG_CFG */
#घोषणा RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_SFT             15
#घोषणा RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_MASK            0x1
#घोषणा RG_AUD_PAD_TOP_DAT_MISO2_LOOPBACK_MASK_SFT        (0x1 << 15)
#घोषणा RG_AUD_PAD_TOP_PHASE_MODE2_SFT                    8
#घोषणा RG_AUD_PAD_TOP_PHASE_MODE2_MASK                   0x7f
#घोषणा RG_AUD_PAD_TOP_PHASE_MODE2_MASK_SFT               (0x7f << 8)
#घोषणा RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_SFT              7
#घोषणा RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_MASK             0x1
#घोषणा RG_AUD_PAD_TOP_DAT_MISO_LOOPBACK_MASK_SFT         (0x1 << 7)
#घोषणा RG_AUD_PAD_TOP_PHASE_MODE_SFT                     0
#घोषणा RG_AUD_PAD_TOP_PHASE_MODE_MASK                    0x7f
#घोषणा RG_AUD_PAD_TOP_PHASE_MODE_MASK_SFT                (0x7f << 0)

/* MT6358_AFE_AUD_PAD_TOP */
#घोषणा RG_AUD_PAD_TOP_TX_FIFO_RSP_SFT                    12
#घोषणा RG_AUD_PAD_TOP_TX_FIFO_RSP_MASK                   0x7
#घोषणा RG_AUD_PAD_TOP_TX_FIFO_RSP_MASK_SFT               (0x7 << 12)
#घोषणा RG_AUD_PAD_TOP_MTKAIF_CLK_PROTOCOL2_SFT           11
#घोषणा RG_AUD_PAD_TOP_MTKAIF_CLK_PROTOCOL2_MASK          0x1
#घोषणा RG_AUD_PAD_TOP_MTKAIF_CLK_PROTOCOL2_MASK_SFT      (0x1 << 11)
#घोषणा RG_AUD_PAD_TOP_TX_FIFO_ON_SFT                     8
#घोषणा RG_AUD_PAD_TOP_TX_FIFO_ON_MASK                    0x1
#घोषणा RG_AUD_PAD_TOP_TX_FIFO_ON_MASK_SFT                (0x1 << 8)

/* MT6358_AFE_AUD_PAD_TOP_MON */
#घोषणा ADDA_AUD_PAD_TOP_MON_SFT                          0
#घोषणा ADDA_AUD_PAD_TOP_MON_MASK                         0xffff
#घोषणा ADDA_AUD_PAD_TOP_MON_MASK_SFT                     (0xffff << 0)

/* MT6358_AFE_AUD_PAD_TOP_MON1 */
#घोषणा ADDA_AUD_PAD_TOP_MON1_SFT                         0
#घोषणा ADDA_AUD_PAD_TOP_MON1_MASK                        0xffff
#घोषणा ADDA_AUD_PAD_TOP_MON1_MASK_SFT                    (0xffff << 0)

/* MT6358_AFE_DL_NLE_CFG */
#घोषणा NLE_RCH_HPGAIN_SEL_SFT                            10
#घोषणा NLE_RCH_HPGAIN_SEL_MASK                           0x1
#घोषणा NLE_RCH_HPGAIN_SEL_MASK_SFT                       (0x1 << 10)
#घोषणा NLE_RCH_CH_SEL_SFT                                9
#घोषणा NLE_RCH_CH_SEL_MASK                               0x1
#घोषणा NLE_RCH_CH_SEL_MASK_SFT                           (0x1 << 9)
#घोषणा NLE_RCH_ON_SFT                                    8
#घोषणा NLE_RCH_ON_MASK                                   0x1
#घोषणा NLE_RCH_ON_MASK_SFT                               (0x1 << 8)
#घोषणा NLE_LCH_HPGAIN_SEL_SFT                            2
#घोषणा NLE_LCH_HPGAIN_SEL_MASK                           0x1
#घोषणा NLE_LCH_HPGAIN_SEL_MASK_SFT                       (0x1 << 2)
#घोषणा NLE_LCH_CH_SEL_SFT                                1
#घोषणा NLE_LCH_CH_SEL_MASK                               0x1
#घोषणा NLE_LCH_CH_SEL_MASK_SFT                           (0x1 << 1)
#घोषणा NLE_LCH_ON_SFT                                    0
#घोषणा NLE_LCH_ON_MASK                                   0x1
#घोषणा NLE_LCH_ON_MASK_SFT                               (0x1 << 0)

/* MT6358_AFE_DL_NLE_MON */
#घोषणा NLE_MONITOR_SFT                                   0
#घोषणा NLE_MONITOR_MASK                                  0x3fff
#घोषणा NLE_MONITOR_MASK_SFT                              (0x3fff << 0)

/* MT6358_AFE_CG_EN_MON */
#घोषणा CK_CG_EN_MON_SFT                                  0
#घोषणा CK_CG_EN_MON_MASK                                 0x3f
#घोषणा CK_CG_EN_MON_MASK_SFT                             (0x3f << 0)

/* MT6358_AFE_VOW_TOP */
#घोषणा PDN_VOW_SFT                                       15
#घोषणा PDN_VOW_MASK                                      0x1
#घोषणा PDN_VOW_MASK_SFT                                  (0x1 << 15)
#घोषणा VOW_1P6M_800K_SEL_SFT                             14
#घोषणा VOW_1P6M_800K_SEL_MASK                            0x1
#घोषणा VOW_1P6M_800K_SEL_MASK_SFT                        (0x1 << 14)
#घोषणा VOW_DIGMIC_ON_SFT                                 13
#घोषणा VOW_DIGMIC_ON_MASK                                0x1
#घोषणा VOW_DIGMIC_ON_MASK_SFT                            (0x1 << 13)
#घोषणा VOW_CK_DIV_RST_SFT                                12
#घोषणा VOW_CK_DIV_RST_MASK                               0x1
#घोषणा VOW_CK_DIV_RST_MASK_SFT                           (0x1 << 12)
#घोषणा VOW_ON_SFT                                        11
#घोषणा VOW_ON_MASK                                       0x1
#घोषणा VOW_ON_MASK_SFT                                   (0x1 << 11)
#घोषणा VOW_DIGMIC_CK_PHASE_SEL_SFT                       8
#घोषणा VOW_DIGMIC_CK_PHASE_SEL_MASK                      0x7
#घोषणा VOW_DIGMIC_CK_PHASE_SEL_MASK_SFT                  (0x7 << 8)
#घोषणा MAIN_DMIC_CK_VOW_SEL_SFT                          7
#घोषणा MAIN_DMIC_CK_VOW_SEL_MASK                         0x1
#घोषणा MAIN_DMIC_CK_VOW_SEL_MASK_SFT                     (0x1 << 7)
#घोषणा VOW_SDM_3_LEVEL_SFT                               6
#घोषणा VOW_SDM_3_LEVEL_MASK                              0x1
#घोषणा VOW_SDM_3_LEVEL_MASK_SFT                          (0x1 << 6)
#घोषणा VOW_LOOP_BACK_MODE_SFT                            5
#घोषणा VOW_LOOP_BACK_MODE_MASK                           0x1
#घोषणा VOW_LOOP_BACK_MODE_MASK_SFT                       (0x1 << 5)
#घोषणा VOW_INTR_SOURCE_SEL_SFT                           4
#घोषणा VOW_INTR_SOURCE_SEL_MASK                          0x1
#घोषणा VOW_INTR_SOURCE_SEL_MASK_SFT                      (0x1 << 4)
#घोषणा VOW_INTR_CLR_SFT                                  3
#घोषणा VOW_INTR_CLR_MASK                                 0x1
#घोषणा VOW_INTR_CLR_MASK_SFT                             (0x1 << 3)
#घोषणा S_N_VALUE_RST_SFT                                 2
#घोषणा S_N_VALUE_RST_MASK                                0x1
#घोषणा S_N_VALUE_RST_MASK_SFT                            (0x1 << 2)
#घोषणा SAMPLE_BASE_MODE_SFT                              1
#घोषणा SAMPLE_BASE_MODE_MASK                             0x1
#घोषणा SAMPLE_BASE_MODE_MASK_SFT                         (0x1 << 1)
#घोषणा VOW_INTR_FLAG_SFT                                 0
#घोषणा VOW_INTR_FLAG_MASK                                0x1
#घोषणा VOW_INTR_FLAG_MASK_SFT                            (0x1 << 0)

/* MT6358_AFE_VOW_CFG0 */
#घोषणा AMPREF_SFT                                        0
#घोषणा AMPREF_MASK                                       0xffff
#घोषणा AMPREF_MASK_SFT                                   (0xffff << 0)

/* MT6358_AFE_VOW_CFG1 */
#घोषणा TIMERINI_SFT                                      0
#घोषणा TIMERINI_MASK                                     0xffff
#घोषणा TIMERINI_MASK_SFT                                 (0xffff << 0)

/* MT6358_AFE_VOW_CFG2 */
#घोषणा B_DEFAULT_SFT                                     12
#घोषणा B_DEFAULT_MASK                                    0x7
#घोषणा B_DEFAULT_MASK_SFT                                (0x7 << 12)
#घोषणा A_DEFAULT_SFT                                     8
#घोषणा A_DEFAULT_MASK                                    0x7
#घोषणा A_DEFAULT_MASK_SFT                                (0x7 << 8)
#घोषणा B_INI_SFT                                         4
#घोषणा B_INI_MASK                                        0x7
#घोषणा B_INI_MASK_SFT                                    (0x7 << 4)
#घोषणा A_INI_SFT                                         0
#घोषणा A_INI_MASK                                        0x7
#घोषणा A_INI_MASK_SFT                                    (0x7 << 0)

/* MT6358_AFE_VOW_CFG3 */
#घोषणा K_BETA_RISE_SFT                                   12
#घोषणा K_BETA_RISE_MASK                                  0xf
#घोषणा K_BETA_RISE_MASK_SFT                              (0xf << 12)
#घोषणा K_BETA_FALL_SFT                                   8
#घोषणा K_BETA_FALL_MASK                                  0xf
#घोषणा K_BETA_FALL_MASK_SFT                              (0xf << 8)
#घोषणा K_ALPHA_RISE_SFT                                  4
#घोषणा K_ALPHA_RISE_MASK                                 0xf
#घोषणा K_ALPHA_RISE_MASK_SFT                             (0xf << 4)
#घोषणा K_ALPHA_FALL_SFT                                  0
#घोषणा K_ALPHA_FALL_MASK                                 0xf
#घोषणा K_ALPHA_FALL_MASK_SFT                             (0xf << 0)

/* MT6358_AFE_VOW_CFG4 */
#घोषणा VOW_TXIF_SCK_INV_SFT                              15
#घोषणा VOW_TXIF_SCK_INV_MASK                             0x1
#घोषणा VOW_TXIF_SCK_INV_MASK_SFT                         (0x1 << 15)
#घोषणा VOW_ADC_TESTCK_SRC_SEL_SFT                        12
#घोषणा VOW_ADC_TESTCK_SRC_SEL_MASK                       0x7
#घोषणा VOW_ADC_TESTCK_SRC_SEL_MASK_SFT                   (0x7 << 12)
#घोषणा VOW_ADC_TESTCK_SEL_SFT                            11
#घोषणा VOW_ADC_TESTCK_SEL_MASK                           0x1
#घोषणा VOW_ADC_TESTCK_SEL_MASK_SFT                       (0x1 << 11)
#घोषणा VOW_ADC_CLK_INV_SFT                               10
#घोषणा VOW_ADC_CLK_INV_MASK                              0x1
#घोषणा VOW_ADC_CLK_INV_MASK_SFT                          (0x1 << 10)
#घोषणा VOW_TXIF_MONO_SFT                                 9
#घोषणा VOW_TXIF_MONO_MASK                                0x1
#घोषणा VOW_TXIF_MONO_MASK_SFT                            (0x1 << 9)
#घोषणा VOW_TXIF_SCK_DIV_SFT                              4
#घोषणा VOW_TXIF_SCK_DIV_MASK                             0x1f
#घोषणा VOW_TXIF_SCK_DIV_MASK_SFT                         (0x1f << 4)
#घोषणा K_GAMMA_SFT                                       0
#घोषणा K_GAMMA_MASK                                      0xf
#घोषणा K_GAMMA_MASK_SFT                                  (0xf << 0)

/* MT6358_AFE_VOW_CFG5 */
#घोषणा N_MIN_SFT                                         0
#घोषणा N_MIN_MASK                                        0xffff
#घोषणा N_MIN_MASK_SFT                                    (0xffff << 0)

/* MT6358_AFE_VOW_CFG6 */
#घोषणा RG_WINDOW_SIZE_SEL_SFT                            12
#घोषणा RG_WINDOW_SIZE_SEL_MASK                           0x1
#घोषणा RG_WINDOW_SIZE_SEL_MASK_SFT                       (0x1 << 12)
#घोषणा RG_FLR_BYPASS_SFT                                 11
#घोषणा RG_FLR_BYPASS_MASK                                0x1
#घोषणा RG_FLR_BYPASS_MASK_SFT                            (0x1 << 11)
#घोषणा RG_FLR_RATIO_SFT                                  8
#घोषणा RG_FLR_RATIO_MASK                                 0x7
#घोषणा RG_FLR_RATIO_MASK_SFT                             (0x7 << 8)
#घोषणा RG_BUCK_DVFS_DONE_SW_CTL_SFT                      7
#घोषणा RG_BUCK_DVFS_DONE_SW_CTL_MASK                     0x1
#घोषणा RG_BUCK_DVFS_DONE_SW_CTL_MASK_SFT                 (0x1 << 7)
#घोषणा RG_BUCK_DVFS_DONE_HW_MODE_SFT                     6
#घोषणा RG_BUCK_DVFS_DONE_HW_MODE_MASK                    0x1
#घोषणा RG_BUCK_DVFS_DONE_HW_MODE_MASK_SFT                (0x1 << 6)
#घोषणा RG_BUCK_DVFS_HW_CNT_THR_SFT                       0
#घोषणा RG_BUCK_DVFS_HW_CNT_THR_MASK                      0x3f
#घोषणा RG_BUCK_DVFS_HW_CNT_THR_MASK_SFT                  (0x3f << 0)

/* MT6358_AFE_VOW_MON0 */
#घोषणा VOW_DOWNCNT_SFT                                   0
#घोषणा VOW_DOWNCNT_MASK                                  0xffff
#घोषणा VOW_DOWNCNT_MASK_SFT                              (0xffff << 0)

/* MT6358_AFE_VOW_MON1 */
#घोषणा K_TMP_MON_SFT                                     10
#घोषणा K_TMP_MON_MASK                                    0xf
#घोषणा K_TMP_MON_MASK_SFT                                (0xf << 10)
#घोषणा SLT_COUNTER_MON_SFT                               7
#घोषणा SLT_COUNTER_MON_MASK                              0x7
#घोषणा SLT_COUNTER_MON_MASK_SFT                          (0x7 << 7)
#घोषणा VOW_B_SFT                                         4
#घोषणा VOW_B_MASK                                        0x7
#घोषणा VOW_B_MASK_SFT                                    (0x7 << 4)
#घोषणा VOW_A_SFT                                         1
#घोषणा VOW_A_MASK                                        0x7
#घोषणा VOW_A_MASK_SFT                                    (0x7 << 1)
#घोषणा SECOND_CNT_START_SFT                              0
#घोषणा SECOND_CNT_START_MASK                             0x1
#घोषणा SECOND_CNT_START_MASK_SFT                         (0x1 << 0)

/* MT6358_AFE_VOW_MON2 */
#घोषणा VOW_S_L_SFT                                       0
#घोषणा VOW_S_L_MASK                                      0xffff
#घोषणा VOW_S_L_MASK_SFT                                  (0xffff << 0)

/* MT6358_AFE_VOW_MON3 */
#घोषणा VOW_S_H_SFT                                       0
#घोषणा VOW_S_H_MASK                                      0xffff
#घोषणा VOW_S_H_MASK_SFT                                  (0xffff << 0)

/* MT6358_AFE_VOW_MON4 */
#घोषणा VOW_N_L_SFT                                       0
#घोषणा VOW_N_L_MASK                                      0xffff
#घोषणा VOW_N_L_MASK_SFT                                  (0xffff << 0)

/* MT6358_AFE_VOW_MON5 */
#घोषणा VOW_N_H_SFT                                       0
#घोषणा VOW_N_H_MASK                                      0xffff
#घोषणा VOW_N_H_MASK_SFT                                  (0xffff << 0)

/* MT6358_AFE_VOW_SN_INI_CFG */
#घोषणा VOW_SN_INI_CFG_EN_SFT                             15
#घोषणा VOW_SN_INI_CFG_EN_MASK                            0x1
#घोषणा VOW_SN_INI_CFG_EN_MASK_SFT                        (0x1 << 15)
#घोषणा VOW_SN_INI_CFG_VAL_SFT                            0
#घोषणा VOW_SN_INI_CFG_VAL_MASK                           0x7fff
#घोषणा VOW_SN_INI_CFG_VAL_MASK_SFT                       (0x7fff << 0)

/* MT6358_AFE_VOW_TGEN_CFG0 */
#घोषणा VOW_TGEN_EN_SFT                                   15
#घोषणा VOW_TGEN_EN_MASK                                  0x1
#घोषणा VOW_TGEN_EN_MASK_SFT                              (0x1 << 15)
#घोषणा VOW_TGEN_MUTE_SW_SFT                              14
#घोषणा VOW_TGEN_MUTE_SW_MASK                             0x1
#घोषणा VOW_TGEN_MUTE_SW_MASK_SFT                         (0x1 << 14)
#घोषणा VOW_TGEN_FREQ_DIV_SFT                             0
#घोषणा VOW_TGEN_FREQ_DIV_MASK                            0x3fff
#घोषणा VOW_TGEN_FREQ_DIV_MASK_SFT                        (0x3fff << 0)

/* MT6358_AFE_VOW_POSDIV_CFG0 */
#घोषणा BUCK_DVFS_DONE_SFT                                15
#घोषणा BUCK_DVFS_DONE_MASK                               0x1
#घोषणा BUCK_DVFS_DONE_MASK_SFT                           (0x1 << 15)
#घोषणा VOW_32K_MODE_SFT                                  13
#घोषणा VOW_32K_MODE_MASK                                 0x1
#घोषणा VOW_32K_MODE_MASK_SFT                             (0x1 << 13)
#घोषणा RG_BUCK_CLK_DIV_SFT                               8
#घोषणा RG_BUCK_CLK_DIV_MASK                              0x1f
#घोषणा RG_BUCK_CLK_DIV_MASK_SFT                          (0x1f << 8)
#घोषणा RG_A1P6M_EN_SEL_SFT                               7
#घोषणा RG_A1P6M_EN_SEL_MASK                              0x1
#घोषणा RG_A1P6M_EN_SEL_MASK_SFT                          (0x1 << 7)
#घोषणा VOW_CLK_SEL_SFT                                   6
#घोषणा VOW_CLK_SEL_MASK                                  0x1
#घोषणा VOW_CLK_SEL_MASK_SFT                              (0x1 << 6)
#घोषणा VOW_INTR_SW_MODE_SFT                              5
#घोषणा VOW_INTR_SW_MODE_MASK                             0x1
#घोषणा VOW_INTR_SW_MODE_MASK_SFT                         (0x1 << 5)
#घोषणा VOW_INTR_SW_VAL_SFT                               4
#घोषणा VOW_INTR_SW_VAL_MASK                              0x1
#घोषणा VOW_INTR_SW_VAL_MASK_SFT                          (0x1 << 4)
#घोषणा VOW_CIC_MODE_SEL_SFT                              2
#घोषणा VOW_CIC_MODE_SEL_MASK                             0x3
#घोषणा VOW_CIC_MODE_SEL_MASK_SFT                         (0x3 << 2)
#घोषणा RG_VOW_POSDIV_SFT                                 0
#घोषणा RG_VOW_POSDIV_MASK                                0x3
#घोषणा RG_VOW_POSDIV_MASK_SFT                            (0x3 << 0)

/* MT6358_AFE_VOW_HPF_CFG0 */
#घोषणा VOW_HPF_DC_TEST_SFT                               12
#घोषणा VOW_HPF_DC_TEST_MASK                              0xf
#घोषणा VOW_HPF_DC_TEST_MASK_SFT                          (0xf << 12)
#घोषणा VOW_IRQ_LATCH_SNR_EN_SFT                          10
#घोषणा VOW_IRQ_LATCH_SNR_EN_MASK                         0x1
#घोषणा VOW_IRQ_LATCH_SNR_EN_MASK_SFT                     (0x1 << 10)
#घोषणा VOW_DMICCLK_PDN_SFT                               9
#घोषणा VOW_DMICCLK_PDN_MASK                              0x1
#घोषणा VOW_DMICCLK_PDN_MASK_SFT                          (0x1 << 9)
#घोषणा VOW_POSDIVCLK_PDN_SFT                             8
#घोषणा VOW_POSDIVCLK_PDN_MASK                            0x1
#घोषणा VOW_POSDIVCLK_PDN_MASK_SFT                        (0x1 << 8)
#घोषणा RG_BASELINE_ALPHA_ORDER_SFT                       4
#घोषणा RG_BASELINE_ALPHA_ORDER_MASK                      0xf
#घोषणा RG_BASELINE_ALPHA_ORDER_MASK_SFT                  (0xf << 4)
#घोषणा RG_MTKAIF_HPF_BYPASS_SFT                          2
#घोषणा RG_MTKAIF_HPF_BYPASS_MASK                         0x1
#घोषणा RG_MTKAIF_HPF_BYPASS_MASK_SFT                     (0x1 << 2)
#घोषणा RG_SNRDET_HPF_BYPASS_SFT                          1
#घोषणा RG_SNRDET_HPF_BYPASS_MASK                         0x1
#घोषणा RG_SNRDET_HPF_BYPASS_MASK_SFT                     (0x1 << 1)
#घोषणा RG_HPF_ON_SFT                                     0
#घोषणा RG_HPF_ON_MASK                                    0x1
#घोषणा RG_HPF_ON_MASK_SFT                                (0x1 << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG0 */
#घोषणा RG_PERIODIC_EN_SFT                                15
#घोषणा RG_PERIODIC_EN_MASK                               0x1
#घोषणा RG_PERIODIC_EN_MASK_SFT                           (0x1 << 15)
#घोषणा RG_PERIODIC_CNT_CLR_SFT                           14
#घोषणा RG_PERIODIC_CNT_CLR_MASK                          0x1
#घोषणा RG_PERIODIC_CNT_CLR_MASK_SFT                      (0x1 << 14)
#घोषणा RG_PERIODIC_CNT_PERIOD_SFT                        0
#घोषणा RG_PERIODIC_CNT_PERIOD_MASK                       0x3fff
#घोषणा RG_PERIODIC_CNT_PERIOD_MASK_SFT                   (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG1 */
#घोषणा RG_PERIODIC_CNT_SET_SFT                           15
#घोषणा RG_PERIODIC_CNT_SET_MASK                          0x1
#घोषणा RG_PERIODIC_CNT_SET_MASK_SFT                      (0x1 << 15)
#घोषणा RG_PERIODIC_CNT_PAUSE_SFT                         14
#घोषणा RG_PERIODIC_CNT_PAUSE_MASK                        0x1
#घोषणा RG_PERIODIC_CNT_PAUSE_MASK_SFT                    (0x1 << 14)
#घोषणा RG_PERIODIC_CNT_SET_VALUE_SFT                     0
#घोषणा RG_PERIODIC_CNT_SET_VALUE_MASK                    0x3fff
#घोषणा RG_PERIODIC_CNT_SET_VALUE_MASK_SFT                (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG2 */
#घोषणा AUDPREAMPLON_PERIODIC_MODE_SFT                    15
#घोषणा AUDPREAMPLON_PERIODIC_MODE_MASK                   0x1
#घोषणा AUDPREAMPLON_PERIODIC_MODE_MASK_SFT               (0x1 << 15)
#घोषणा AUDPREAMPLON_PERIODIC_INVERSE_SFT                 14
#घोषणा AUDPREAMPLON_PERIODIC_INVERSE_MASK                0x1
#घोषणा AUDPREAMPLON_PERIODIC_INVERSE_MASK_SFT            (0x1 << 14)
#घोषणा AUDPREAMPLON_PERIODIC_ON_CYCLE_SFT                0
#घोषणा AUDPREAMPLON_PERIODIC_ON_CYCLE_MASK               0x3fff
#घोषणा AUDPREAMPLON_PERIODIC_ON_CYCLE_MASK_SFT           (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG3 */
#घोषणा AUDPREAMPLDCPRECHARGE_PERIODIC_MODE_SFT           15
#घोषणा AUDPREAMPLDCPRECHARGE_PERIODIC_MODE_MASK          0x1
#घोषणा AUDPREAMPLDCPRECHARGE_PERIODIC_MODE_MASK_SFT      (0x1 << 15)
#घोषणा AUDPREAMPLDCPRECHARGE_PERIODIC_INVERSE_SFT        14
#घोषणा AUDPREAMPLDCPRECHARGE_PERIODIC_INVERSE_MASK       0x1
#घोषणा AUDPREAMPLDCPRECHARGE_PERIODIC_INVERSE_MASK_SFT   (0x1 << 14)
#घोषणा AUDPREAMPLDCPRECHARGE_PERIODIC_ON_CYCLE_SFT       0
#घोषणा AUDPREAMPLDCPRECHARGE_PERIODIC_ON_CYCLE_MASK      0x3fff
#घोषणा AUDPREAMPLDCPRECHARGE_PERIODIC_ON_CYCLE_MASK_SFT  (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG4 */
#घोषणा AUDADCLPWRUP_PERIODIC_MODE_SFT                    15
#घोषणा AUDADCLPWRUP_PERIODIC_MODE_MASK                   0x1
#घोषणा AUDADCLPWRUP_PERIODIC_MODE_MASK_SFT               (0x1 << 15)
#घोषणा AUDADCLPWRUP_PERIODIC_INVERSE_SFT                 14
#घोषणा AUDADCLPWRUP_PERIODIC_INVERSE_MASK                0x1
#घोषणा AUDADCLPWRUP_PERIODIC_INVERSE_MASK_SFT            (0x1 << 14)
#घोषणा AUDADCLPWRUP_PERIODIC_ON_CYCLE_SFT                0
#घोषणा AUDADCLPWRUP_PERIODIC_ON_CYCLE_MASK               0x3fff
#घोषणा AUDADCLPWRUP_PERIODIC_ON_CYCLE_MASK_SFT           (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG5 */
#घोषणा AUDGLBVOWLPWEN_PERIODIC_MODE_SFT                  15
#घोषणा AUDGLBVOWLPWEN_PERIODIC_MODE_MASK                 0x1
#घोषणा AUDGLBVOWLPWEN_PERIODIC_MODE_MASK_SFT             (0x1 << 15)
#घोषणा AUDGLBVOWLPWEN_PERIODIC_INVERSE_SFT               14
#घोषणा AUDGLBVOWLPWEN_PERIODIC_INVERSE_MASK              0x1
#घोषणा AUDGLBVOWLPWEN_PERIODIC_INVERSE_MASK_SFT          (0x1 << 14)
#घोषणा AUDGLBVOWLPWEN_PERIODIC_ON_CYCLE_SFT              0
#घोषणा AUDGLBVOWLPWEN_PERIODIC_ON_CYCLE_MASK             0x3fff
#घोषणा AUDGLBVOWLPWEN_PERIODIC_ON_CYCLE_MASK_SFT         (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG6 */
#घोषणा AUDDIGMICEN_PERIODIC_MODE_SFT                     15
#घोषणा AUDDIGMICEN_PERIODIC_MODE_MASK                    0x1
#घोषणा AUDDIGMICEN_PERIODIC_MODE_MASK_SFT                (0x1 << 15)
#घोषणा AUDDIGMICEN_PERIODIC_INVERSE_SFT                  14
#घोषणा AUDDIGMICEN_PERIODIC_INVERSE_MASK                 0x1
#घोषणा AUDDIGMICEN_PERIODIC_INVERSE_MASK_SFT             (0x1 << 14)
#घोषणा AUDDIGMICEN_PERIODIC_ON_CYCLE_SFT                 0
#घोषणा AUDDIGMICEN_PERIODIC_ON_CYCLE_MASK                0x3fff
#घोषणा AUDDIGMICEN_PERIODIC_ON_CYCLE_MASK_SFT            (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG7 */
#घोषणा AUDPWDBMICBIAS0_PERIODIC_MODE_SFT                 15
#घोषणा AUDPWDBMICBIAS0_PERIODIC_MODE_MASK                0x1
#घोषणा AUDPWDBMICBIAS0_PERIODIC_MODE_MASK_SFT            (0x1 << 15)
#घोषणा AUDPWDBMICBIAS0_PERIODIC_INVERSE_SFT              14
#घोषणा AUDPWDBMICBIAS0_PERIODIC_INVERSE_MASK             0x1
#घोषणा AUDPWDBMICBIAS0_PERIODIC_INVERSE_MASK_SFT         (0x1 << 14)
#घोषणा AUDPWDBMICBIAS0_PERIODIC_ON_CYCLE_SFT             0
#घोषणा AUDPWDBMICBIAS0_PERIODIC_ON_CYCLE_MASK            0x3fff
#घोषणा AUDPWDBMICBIAS0_PERIODIC_ON_CYCLE_MASK_SFT        (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG8 */
#घोषणा AUDPWDBMICBIAS1_PERIODIC_MODE_SFT                 15
#घोषणा AUDPWDBMICBIAS1_PERIODIC_MODE_MASK                0x1
#घोषणा AUDPWDBMICBIAS1_PERIODIC_MODE_MASK_SFT            (0x1 << 15)
#घोषणा AUDPWDBMICBIAS1_PERIODIC_INVERSE_SFT              14
#घोषणा AUDPWDBMICBIAS1_PERIODIC_INVERSE_MASK             0x1
#घोषणा AUDPWDBMICBIAS1_PERIODIC_INVERSE_MASK_SFT         (0x1 << 14)
#घोषणा AUDPWDBMICBIAS1_PERIODIC_ON_CYCLE_SFT             0
#घोषणा AUDPWDBMICBIAS1_PERIODIC_ON_CYCLE_MASK            0x3fff
#घोषणा AUDPWDBMICBIAS1_PERIODIC_ON_CYCLE_MASK_SFT        (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG9 */
#घोषणा XO_VOW_CK_EN_PERIODIC_MODE_SFT                    15
#घोषणा XO_VOW_CK_EN_PERIODIC_MODE_MASK                   0x1
#घोषणा XO_VOW_CK_EN_PERIODIC_MODE_MASK_SFT               (0x1 << 15)
#घोषणा XO_VOW_CK_EN_PERIODIC_INVERSE_SFT                 14
#घोषणा XO_VOW_CK_EN_PERIODIC_INVERSE_MASK                0x1
#घोषणा XO_VOW_CK_EN_PERIODIC_INVERSE_MASK_SFT            (0x1 << 14)
#घोषणा XO_VOW_CK_EN_PERIODIC_ON_CYCLE_SFT                0
#घोषणा XO_VOW_CK_EN_PERIODIC_ON_CYCLE_MASK               0x3fff
#घोषणा XO_VOW_CK_EN_PERIODIC_ON_CYCLE_MASK_SFT           (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG10 */
#घोषणा AUDGLB_PWRDN_PERIODIC_MODE_SFT                    15
#घोषणा AUDGLB_PWRDN_PERIODIC_MODE_MASK                   0x1
#घोषणा AUDGLB_PWRDN_PERIODIC_MODE_MASK_SFT               (0x1 << 15)
#घोषणा AUDGLB_PWRDN_PERIODIC_INVERSE_SFT                 14
#घोषणा AUDGLB_PWRDN_PERIODIC_INVERSE_MASK                0x1
#घोषणा AUDGLB_PWRDN_PERIODIC_INVERSE_MASK_SFT            (0x1 << 14)
#घोषणा AUDGLB_PWRDN_PERIODIC_ON_CYCLE_SFT                0
#घोषणा AUDGLB_PWRDN_PERIODIC_ON_CYCLE_MASK               0x3fff
#घोषणा AUDGLB_PWRDN_PERIODIC_ON_CYCLE_MASK_SFT           (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG11 */
#घोषणा VOW_ON_PERIODIC_MODE_SFT                          15
#घोषणा VOW_ON_PERIODIC_MODE_MASK                         0x1
#घोषणा VOW_ON_PERIODIC_MODE_MASK_SFT                     (0x1 << 15)
#घोषणा VOW_ON_PERIODIC_INVERSE_SFT                       14
#घोषणा VOW_ON_PERIODIC_INVERSE_MASK                      0x1
#घोषणा VOW_ON_PERIODIC_INVERSE_MASK_SFT                  (0x1 << 14)
#घोषणा VOW_ON_PERIODIC_ON_CYCLE_SFT                      0
#घोषणा VOW_ON_PERIODIC_ON_CYCLE_MASK                     0x3fff
#घोषणा VOW_ON_PERIODIC_ON_CYCLE_MASK_SFT                 (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG12 */
#घोषणा DMIC_ON_PERIODIC_MODE_SFT                         15
#घोषणा DMIC_ON_PERIODIC_MODE_MASK                        0x1
#घोषणा DMIC_ON_PERIODIC_MODE_MASK_SFT                    (0x1 << 15)
#घोषणा DMIC_ON_PERIODIC_INVERSE_SFT                      14
#घोषणा DMIC_ON_PERIODIC_INVERSE_MASK                     0x1
#घोषणा DMIC_ON_PERIODIC_INVERSE_MASK_SFT                 (0x1 << 14)
#घोषणा DMIC_ON_PERIODIC_ON_CYCLE_SFT                     0
#घोषणा DMIC_ON_PERIODIC_ON_CYCLE_MASK                    0x3fff
#घोषणा DMIC_ON_PERIODIC_ON_CYCLE_MASK_SFT                (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG13 */
#घोषणा PDN_VOW_F32K_CK_SFT                               15
#घोषणा PDN_VOW_F32K_CK_MASK                              0x1
#घोषणा PDN_VOW_F32K_CK_MASK_SFT                          (0x1 << 15)
#घोषणा AUDPREAMPLON_PERIODIC_OFF_CYCLE_SFT               0
#घोषणा AUDPREAMPLON_PERIODIC_OFF_CYCLE_MASK              0x3fff
#घोषणा AUDPREAMPLON_PERIODIC_OFF_CYCLE_MASK_SFT          (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG14 */
#घोषणा VOW_SNRDET_PERIODIC_CFG_SFT                       15
#घोषणा VOW_SNRDET_PERIODIC_CFG_MASK                      0x1
#घोषणा VOW_SNRDET_PERIODIC_CFG_MASK_SFT                  (0x1 << 15)
#घोषणा AUDPREAMPLDCPRECHARGE_PERIODIC_OFF_CYCLE_SFT      0
#घोषणा AUDPREAMPLDCPRECHARGE_PERIODIC_OFF_CYCLE_MASK     0x3fff
#घोषणा AUDPREAMPLDCPRECHARGE_PERIODIC_OFF_CYCLE_MASK_SFT (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG15 */
#घोषणा AUDADCLPWRUP_PERIODIC_OFF_CYCLE_SFT               0
#घोषणा AUDADCLPWRUP_PERIODIC_OFF_CYCLE_MASK              0x3fff
#घोषणा AUDADCLPWRUP_PERIODIC_OFF_CYCLE_MASK_SFT          (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG16 */
#घोषणा AUDGLBVOWLPWEN_PERIODIC_OFF_CYCLE_SFT             0
#घोषणा AUDGLBVOWLPWEN_PERIODIC_OFF_CYCLE_MASK            0x3fff
#घोषणा AUDGLBVOWLPWEN_PERIODIC_OFF_CYCLE_MASK_SFT        (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG17 */
#घोषणा AUDDIGMICEN_PERIODIC_OFF_CYCLE_SFT                0
#घोषणा AUDDIGMICEN_PERIODIC_OFF_CYCLE_MASK               0x3fff
#घोषणा AUDDIGMICEN_PERIODIC_OFF_CYCLE_MASK_SFT           (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG18 */
#घोषणा AUDPWDBMICBIAS0_PERIODIC_OFF_CYCLE_SFT            0
#घोषणा AUDPWDBMICBIAS0_PERIODIC_OFF_CYCLE_MASK           0x3fff
#घोषणा AUDPWDBMICBIAS0_PERIODIC_OFF_CYCLE_MASK_SFT       (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG19 */
#घोषणा AUDPWDBMICBIAS1_PERIODIC_OFF_CYCLE_SFT            0
#घोषणा AUDPWDBMICBIAS1_PERIODIC_OFF_CYCLE_MASK           0x3fff
#घोषणा AUDPWDBMICBIAS1_PERIODIC_OFF_CYCLE_MASK_SFT       (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG20 */
#घोषणा CLKSQ_EN_VOW_PERIODIC_MODE_SFT                    15
#घोषणा CLKSQ_EN_VOW_PERIODIC_MODE_MASK                   0x1
#घोषणा CLKSQ_EN_VOW_PERIODIC_MODE_MASK_SFT               (0x1 << 15)
#घोषणा XO_VOW_CK_EN_PERIODIC_OFF_CYCLE_SFT               0
#घोषणा XO_VOW_CK_EN_PERIODIC_OFF_CYCLE_MASK              0x3fff
#घोषणा XO_VOW_CK_EN_PERIODIC_OFF_CYCLE_MASK_SFT          (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG21 */
#घोषणा AUDGLB_PWRDN_PERIODIC_OFF_CYCLE_SFT               0
#घोषणा AUDGLB_PWRDN_PERIODIC_OFF_CYCLE_MASK              0x3fff
#घोषणा AUDGLB_PWRDN_PERIODIC_OFF_CYCLE_MASK_SFT          (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG22 */
#घोषणा VOW_ON_PERIODIC_OFF_CYCLE_SFT                     0
#घोषणा VOW_ON_PERIODIC_OFF_CYCLE_MASK                    0x3fff
#घोषणा VOW_ON_PERIODIC_OFF_CYCLE_MASK_SFT                (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_CFG23 */
#घोषणा DMIC_ON_PERIODIC_OFF_CYCLE_SFT                    0
#घोषणा DMIC_ON_PERIODIC_OFF_CYCLE_MASK                   0x3fff
#घोषणा DMIC_ON_PERIODIC_OFF_CYCLE_MASK_SFT               (0x3fff << 0)

/* MT6358_AFE_VOW_PERIODIC_MON0 */
#घोषणा VOW_PERIODIC_MON_SFT                              0
#घोषणा VOW_PERIODIC_MON_MASK                             0xffff
#घोषणा VOW_PERIODIC_MON_MASK_SFT                         (0xffff << 0)

/* MT6358_AFE_VOW_PERIODIC_MON1 */
#घोषणा VOW_PERIODIC_COUNT_MON_SFT                        0
#घोषणा VOW_PERIODIC_COUNT_MON_MASK                       0xffff
#घोषणा VOW_PERIODIC_COUNT_MON_MASK_SFT                   (0xffff << 0)

/* MT6358_AUDENC_DSN_ID */
#घोषणा AUDENC_ANA_ID_SFT                                 0
#घोषणा AUDENC_ANA_ID_MASK                                0xff
#घोषणा AUDENC_ANA_ID_MASK_SFT                            (0xff << 0)
#घोषणा AUDENC_DIG_ID_SFT                                 8
#घोषणा AUDENC_DIG_ID_MASK                                0xff
#घोषणा AUDENC_DIG_ID_MASK_SFT                            (0xff << 8)

/* MT6358_AUDENC_DSN_REV0 */
#घोषणा AUDENC_ANA_MINOR_REV_SFT                          0
#घोषणा AUDENC_ANA_MINOR_REV_MASK                         0xf
#घोषणा AUDENC_ANA_MINOR_REV_MASK_SFT                     (0xf << 0)
#घोषणा AUDENC_ANA_MAJOR_REV_SFT                          4
#घोषणा AUDENC_ANA_MAJOR_REV_MASK                         0xf
#घोषणा AUDENC_ANA_MAJOR_REV_MASK_SFT                     (0xf << 4)
#घोषणा AUDENC_DIG_MINOR_REV_SFT                          8
#घोषणा AUDENC_DIG_MINOR_REV_MASK                         0xf
#घोषणा AUDENC_DIG_MINOR_REV_MASK_SFT                     (0xf << 8)
#घोषणा AUDENC_DIG_MAJOR_REV_SFT                          12
#घोषणा AUDENC_DIG_MAJOR_REV_MASK                         0xf
#घोषणा AUDENC_DIG_MAJOR_REV_MASK_SFT                     (0xf << 12)

/* MT6358_AUDENC_DSN_DBI */
#घोषणा AUDENC_DSN_CBS_SFT                                0
#घोषणा AUDENC_DSN_CBS_MASK                               0x3
#घोषणा AUDENC_DSN_CBS_MASK_SFT                           (0x3 << 0)
#घोषणा AUDENC_DSN_BIX_SFT                                2
#घोषणा AUDENC_DSN_BIX_MASK                               0x3
#घोषणा AUDENC_DSN_BIX_MASK_SFT                           (0x3 << 2)
#घोषणा AUDENC_DSN_ESP_SFT                                8
#घोषणा AUDENC_DSN_ESP_MASK                               0xff
#घोषणा AUDENC_DSN_ESP_MASK_SFT                           (0xff << 8)

/* MT6358_AUDENC_DSN_FPI */
#घोषणा AUDENC_DSN_FPI_SFT                                0
#घोषणा AUDENC_DSN_FPI_MASK                               0xff
#घोषणा AUDENC_DSN_FPI_MASK_SFT                           (0xff << 0)

/* MT6358_AUDENC_ANA_CON0 */
#घोषणा RG_AUDPREAMPLON_SFT                               0
#घोषणा RG_AUDPREAMPLON_MASK                              0x1
#घोषणा RG_AUDPREAMPLON_MASK_SFT                          (0x1 << 0)
#घोषणा RG_AUDPREAMPLDCCEN_SFT                            1
#घोषणा RG_AUDPREAMPLDCCEN_MASK                           0x1
#घोषणा RG_AUDPREAMPLDCCEN_MASK_SFT                       (0x1 << 1)
#घोषणा RG_AUDPREAMPLDCPRECHARGE_SFT                      2
#घोषणा RG_AUDPREAMPLDCPRECHARGE_MASK                     0x1
#घोषणा RG_AUDPREAMPLDCPRECHARGE_MASK_SFT                 (0x1 << 2)
#घोषणा RG_AUDPREAMPLPGATEST_SFT                          3
#घोषणा RG_AUDPREAMPLPGATEST_MASK                         0x1
#घोषणा RG_AUDPREAMPLPGATEST_MASK_SFT                     (0x1 << 3)
#घोषणा RG_AUDPREAMPLVSCALE_SFT                           4
#घोषणा RG_AUDPREAMPLVSCALE_MASK                          0x3
#घोषणा RG_AUDPREAMPLVSCALE_MASK_SFT                      (0x3 << 4)
#घोषणा RG_AUDPREAMPLINPUTSEL_SFT                         6
#घोषणा RG_AUDPREAMPLINPUTSEL_MASK                        0x3
#घोषणा RG_AUDPREAMPLINPUTSEL_MASK_SFT                    (0x3 << 6)
#घोषणा RG_AUDPREAMPLGAIN_SFT                             8
#घोषणा RG_AUDPREAMPLGAIN_MASK                            0x7
#घोषणा RG_AUDPREAMPLGAIN_MASK_SFT                        (0x7 << 8)
#घोषणा RG_AUDADCLPWRUP_SFT                               12
#घोषणा RG_AUDADCLPWRUP_MASK                              0x1
#घोषणा RG_AUDADCLPWRUP_MASK_SFT                          (0x1 << 12)
#घोषणा RG_AUDADCLINPUTSEL_SFT                            13
#घोषणा RG_AUDADCLINPUTSEL_MASK                           0x3
#घोषणा RG_AUDADCLINPUTSEL_MASK_SFT                       (0x3 << 13)

/* MT6358_AUDENC_ANA_CON1 */
#घोषणा RG_AUDPREAMPRON_SFT                               0
#घोषणा RG_AUDPREAMPRON_MASK                              0x1
#घोषणा RG_AUDPREAMPRON_MASK_SFT                          (0x1 << 0)
#घोषणा RG_AUDPREAMPRDCCEN_SFT                            1
#घोषणा RG_AUDPREAMPRDCCEN_MASK                           0x1
#घोषणा RG_AUDPREAMPRDCCEN_MASK_SFT                       (0x1 << 1)
#घोषणा RG_AUDPREAMPRDCPRECHARGE_SFT                      2
#घोषणा RG_AUDPREAMPRDCPRECHARGE_MASK                     0x1
#घोषणा RG_AUDPREAMPRDCPRECHARGE_MASK_SFT                 (0x1 << 2)
#घोषणा RG_AUDPREAMPRPGATEST_SFT                          3
#घोषणा RG_AUDPREAMPRPGATEST_MASK                         0x1
#घोषणा RG_AUDPREAMPRPGATEST_MASK_SFT                     (0x1 << 3)
#घोषणा RG_AUDPREAMPRVSCALE_SFT                           4
#घोषणा RG_AUDPREAMPRVSCALE_MASK                          0x3
#घोषणा RG_AUDPREAMPRVSCALE_MASK_SFT                      (0x3 << 4)
#घोषणा RG_AUDPREAMPRINPUTSEL_SFT                         6
#घोषणा RG_AUDPREAMPRINPUTSEL_MASK                        0x3
#घोषणा RG_AUDPREAMPRINPUTSEL_MASK_SFT                    (0x3 << 6)
#घोषणा RG_AUDPREAMPRGAIN_SFT                             8
#घोषणा RG_AUDPREAMPRGAIN_MASK                            0x7
#घोषणा RG_AUDPREAMPRGAIN_MASK_SFT                        (0x7 << 8)
#घोषणा RG_AUDIO_VOW_EN_SFT                               11
#घोषणा RG_AUDIO_VOW_EN_MASK                              0x1
#घोषणा RG_AUDIO_VOW_EN_MASK_SFT                          (0x1 << 11)
#घोषणा RG_AUDADCRPWRUP_SFT                               12
#घोषणा RG_AUDADCRPWRUP_MASK                              0x1
#घोषणा RG_AUDADCRPWRUP_MASK_SFT                          (0x1 << 12)
#घोषणा RG_AUDADCRINPUTSEL_SFT                            13
#घोषणा RG_AUDADCRINPUTSEL_MASK                           0x3
#घोषणा RG_AUDADCRINPUTSEL_MASK_SFT                       (0x3 << 13)
#घोषणा RG_CLKSQ_EN_VOW_SFT                               15
#घोषणा RG_CLKSQ_EN_VOW_MASK                              0x1
#घोषणा RG_CLKSQ_EN_VOW_MASK_SFT                          (0x1 << 15)

/* MT6358_AUDENC_ANA_CON2 */
#घोषणा RG_AUDULHALFBIAS_SFT                              0
#घोषणा RG_AUDULHALFBIAS_MASK                             0x1
#घोषणा RG_AUDULHALFBIAS_MASK_SFT                         (0x1 << 0)
#घोषणा RG_AUDGLBVOWLPWEN_SFT                             1
#घोषणा RG_AUDGLBVOWLPWEN_MASK                            0x1
#घोषणा RG_AUDGLBVOWLPWEN_MASK_SFT                        (0x1 << 1)
#घोषणा RG_AUDPREAMPLPEN_SFT                              2
#घोषणा RG_AUDPREAMPLPEN_MASK                             0x1
#घोषणा RG_AUDPREAMPLPEN_MASK_SFT                         (0x1 << 2)
#घोषणा RG_AUDADC1STSTAGELPEN_SFT                         3
#घोषणा RG_AUDADC1STSTAGELPEN_MASK                        0x1
#घोषणा RG_AUDADC1STSTAGELPEN_MASK_SFT                    (0x1 << 3)
#घोषणा RG_AUDADC2NDSTAGELPEN_SFT                         4
#घोषणा RG_AUDADC2NDSTAGELPEN_MASK                        0x1
#घोषणा RG_AUDADC2NDSTAGELPEN_MASK_SFT                    (0x1 << 4)
#घोषणा RG_AUDADCFLASHLPEN_SFT                            5
#घोषणा RG_AUDADCFLASHLPEN_MASK                           0x1
#घोषणा RG_AUDADCFLASHLPEN_MASK_SFT                       (0x1 << 5)
#घोषणा RG_AUDPREAMPIDDTEST_SFT                           6
#घोषणा RG_AUDPREAMPIDDTEST_MASK                          0x3
#घोषणा RG_AUDPREAMPIDDTEST_MASK_SFT                      (0x3 << 6)
#घोषणा RG_AUDADC1STSTAGEIDDTEST_SFT                      8
#घोषणा RG_AUDADC1STSTAGEIDDTEST_MASK                     0x3
#घोषणा RG_AUDADC1STSTAGEIDDTEST_MASK_SFT                 (0x3 << 8)
#घोषणा RG_AUDADC2NDSTAGEIDDTEST_SFT                      10
#घोषणा RG_AUDADC2NDSTAGEIDDTEST_MASK                     0x3
#घोषणा RG_AUDADC2NDSTAGEIDDTEST_MASK_SFT                 (0x3 << 10)
#घोषणा RG_AUDADCREFBUFIDDTEST_SFT                        12
#घोषणा RG_AUDADCREFBUFIDDTEST_MASK                       0x3
#घोषणा RG_AUDADCREFBUFIDDTEST_MASK_SFT                   (0x3 << 12)
#घोषणा RG_AUDADCFLASHIDDTEST_SFT                         14
#घोषणा RG_AUDADCFLASHIDDTEST_MASK                        0x3
#घोषणा RG_AUDADCFLASHIDDTEST_MASK_SFT                    (0x3 << 14)

/* MT6358_AUDENC_ANA_CON3 */
#घोषणा RG_AUDADCDAC0P25FS_SFT                            0
#घोषणा RG_AUDADCDAC0P25FS_MASK                           0x1
#घोषणा RG_AUDADCDAC0P25FS_MASK_SFT                       (0x1 << 0)
#घोषणा RG_AUDADCCLKSEL_SFT                               1
#घोषणा RG_AUDADCCLKSEL_MASK                              0x1
#घोषणा RG_AUDADCCLKSEL_MASK_SFT                          (0x1 << 1)
#घोषणा RG_AUDADCCLKSOURCE_SFT                            2
#घोषणा RG_AUDADCCLKSOURCE_MASK                           0x3
#घोषणा RG_AUDADCCLKSOURCE_MASK_SFT                       (0x3 << 2)
#घोषणा RG_AUDPREAMPAAFEN_SFT                             8
#घोषणा RG_AUDPREAMPAAFEN_MASK                            0x1
#घोषणा RG_AUDPREAMPAAFEN_MASK_SFT                        (0x1 << 8)
#घोषणा RG_DCCVCMBUFLPMODSEL_SFT                          9
#घोषणा RG_DCCVCMBUFLPMODSEL_MASK                         0x1
#घोषणा RG_DCCVCMBUFLPMODSEL_MASK_SFT                     (0x1 << 9)
#घोषणा RG_DCCVCMBUFLPSWEN_SFT                            10
#घोषणा RG_DCCVCMBUFLPSWEN_MASK                           0x1
#घोषणा RG_DCCVCMBUFLPSWEN_MASK_SFT                       (0x1 << 10)
#घोषणा RG_CMSTBENH_SFT                                   11
#घोषणा RG_CMSTBENH_MASK                                  0x1
#घोषणा RG_CMSTBENH_MASK_SFT                              (0x1 << 11)
#घोषणा RG_PGABODYSW_SFT                                  12
#घोषणा RG_PGABODYSW_MASK                                 0x1
#घोषणा RG_PGABODYSW_MASK_SFT                             (0x1 << 12)

/* MT6358_AUDENC_ANA_CON4 */
#घोषणा RG_AUDADC1STSTAGESDENB_SFT                        0
#घोषणा RG_AUDADC1STSTAGESDENB_MASK                       0x1
#घोषणा RG_AUDADC1STSTAGESDENB_MASK_SFT                   (0x1 << 0)
#घोषणा RG_AUDADC2NDSTAGERESET_SFT                        1
#घोषणा RG_AUDADC2NDSTAGERESET_MASK                       0x1
#घोषणा RG_AUDADC2NDSTAGERESET_MASK_SFT                   (0x1 << 1)
#घोषणा RG_AUDADC3RDSTAGERESET_SFT                        2
#घोषणा RG_AUDADC3RDSTAGERESET_MASK                       0x1
#घोषणा RG_AUDADC3RDSTAGERESET_MASK_SFT                   (0x1 << 2)
#घोषणा RG_AUDADCFSRESET_SFT                              3
#घोषणा RG_AUDADCFSRESET_MASK                             0x1
#घोषणा RG_AUDADCFSRESET_MASK_SFT                         (0x1 << 3)
#घोषणा RG_AUDADCWIDECM_SFT                               4
#घोषणा RG_AUDADCWIDECM_MASK                              0x1
#घोषणा RG_AUDADCWIDECM_MASK_SFT                          (0x1 << 4)
#घोषणा RG_AUDADCNOPATEST_SFT                             5
#घोषणा RG_AUDADCNOPATEST_MASK                            0x1
#घोषणा RG_AUDADCNOPATEST_MASK_SFT                        (0x1 << 5)
#घोषणा RG_AUDADCBYPASS_SFT                               6
#घोषणा RG_AUDADCBYPASS_MASK                              0x1
#घोषणा RG_AUDADCBYPASS_MASK_SFT                          (0x1 << 6)
#घोषणा RG_AUDADCFFBYPASS_SFT                             7
#घोषणा RG_AUDADCFFBYPASS_MASK                            0x1
#घोषणा RG_AUDADCFFBYPASS_MASK_SFT                        (0x1 << 7)
#घोषणा RG_AUDADCDACFBCURRENT_SFT                         8
#घोषणा RG_AUDADCDACFBCURRENT_MASK                        0x1
#घोषणा RG_AUDADCDACFBCURRENT_MASK_SFT                    (0x1 << 8)
#घोषणा RG_AUDADCDACIDDTEST_SFT                           9
#घोषणा RG_AUDADCDACIDDTEST_MASK                          0x3
#घोषणा RG_AUDADCDACIDDTEST_MASK_SFT                      (0x3 << 9)
#घोषणा RG_AUDADCDACNRZ_SFT                               11
#घोषणा RG_AUDADCDACNRZ_MASK                              0x1
#घोषणा RG_AUDADCDACNRZ_MASK_SFT                          (0x1 << 11)
#घोषणा RG_AUDADCNODEM_SFT                                12
#घोषणा RG_AUDADCNODEM_MASK                               0x1
#घोषणा RG_AUDADCNODEM_MASK_SFT                           (0x1 << 12)
#घोषणा RG_AUDADCDACTEST_SFT                              13
#घोषणा RG_AUDADCDACTEST_MASK                             0x1
#घोषणा RG_AUDADCDACTEST_MASK_SFT                         (0x1 << 13)

/* MT6358_AUDENC_ANA_CON5 */
#घोषणा RG_AUDRCTUNEL_SFT                                 0
#घोषणा RG_AUDRCTUNEL_MASK                                0x1f
#घोषणा RG_AUDRCTUNEL_MASK_SFT                            (0x1f << 0)
#घोषणा RG_AUDRCTUNELSEL_SFT                              5
#घोषणा RG_AUDRCTUNELSEL_MASK                             0x1
#घोषणा RG_AUDRCTUNELSEL_MASK_SFT                         (0x1 << 5)
#घोषणा RG_AUDRCTUNER_SFT                                 8
#घोषणा RG_AUDRCTUNER_MASK                                0x1f
#घोषणा RG_AUDRCTUNER_MASK_SFT                            (0x1f << 8)
#घोषणा RG_AUDRCTUNERSEL_SFT                              13
#घोषणा RG_AUDRCTUNERSEL_MASK                             0x1
#घोषणा RG_AUDRCTUNERSEL_MASK_SFT                         (0x1 << 13)

/* MT6358_AUDENC_ANA_CON6 */
#घोषणा RG_CLKSQ_EN_SFT                                   0
#घोषणा RG_CLKSQ_EN_MASK                                  0x1
#घोषणा RG_CLKSQ_EN_MASK_SFT                              (0x1 << 0)
#घोषणा RG_CLKSQ_IN_SEL_TEST_SFT                          1
#घोषणा RG_CLKSQ_IN_SEL_TEST_MASK                         0x1
#घोषणा RG_CLKSQ_IN_SEL_TEST_MASK_SFT                     (0x1 << 1)
#घोषणा RG_CM_REFGENSEL_SFT                               2
#घोषणा RG_CM_REFGENSEL_MASK                              0x1
#घोषणा RG_CM_REFGENSEL_MASK_SFT                          (0x1 << 2)
#घोषणा RG_AUDSPARE_SFT                                   4
#घोषणा RG_AUDSPARE_MASK                                  0xf
#घोषणा RG_AUDSPARE_MASK_SFT                              (0xf << 4)
#घोषणा RG_AUDENCSPARE_SFT                                8
#घोषणा RG_AUDENCSPARE_MASK                               0x3f
#घोषणा RG_AUDENCSPARE_MASK_SFT                           (0x3f << 8)

/* MT6358_AUDENC_ANA_CON7 */
#घोषणा RG_AUDENCSPARE2_SFT                               0
#घोषणा RG_AUDENCSPARE2_MASK                              0xff
#घोषणा RG_AUDENCSPARE2_MASK_SFT                          (0xff << 0)

/* MT6358_AUDENC_ANA_CON8 */
#घोषणा RG_AUDDIGMICEN_SFT                                0
#घोषणा RG_AUDDIGMICEN_MASK                               0x1
#घोषणा RG_AUDDIGMICEN_MASK_SFT                           (0x1 << 0)
#घोषणा RG_AUDDIGMICBIAS_SFT                              1
#घोषणा RG_AUDDIGMICBIAS_MASK                             0x3
#घोषणा RG_AUDDIGMICBIAS_MASK_SFT                         (0x3 << 1)
#घोषणा RG_DMICHPCLKEN_SFT                                3
#घोषणा RG_DMICHPCLKEN_MASK                               0x1
#घोषणा RG_DMICHPCLKEN_MASK_SFT                           (0x1 << 3)
#घोषणा RG_AUDDIGMICPDUTY_SFT                             4
#घोषणा RG_AUDDIGMICPDUTY_MASK                            0x3
#घोषणा RG_AUDDIGMICPDUTY_MASK_SFT                        (0x3 << 4)
#घोषणा RG_AUDDIGMICNDUTY_SFT                             6
#घोषणा RG_AUDDIGMICNDUTY_MASK                            0x3
#घोषणा RG_AUDDIGMICNDUTY_MASK_SFT                        (0x3 << 6)
#घोषणा RG_DMICMONEN_SFT                                  8
#घोषणा RG_DMICMONEN_MASK                                 0x1
#घोषणा RG_DMICMONEN_MASK_SFT                             (0x1 << 8)
#घोषणा RG_DMICMONSEL_SFT                                 9
#घोषणा RG_DMICMONSEL_MASK                                0x7
#घोषणा RG_DMICMONSEL_MASK_SFT                            (0x7 << 9)
#घोषणा RG_AUDSPAREVMIC_SFT                               12
#घोषणा RG_AUDSPAREVMIC_MASK                              0xf
#घोषणा RG_AUDSPAREVMIC_MASK_SFT                          (0xf << 12)

/* MT6358_AUDENC_ANA_CON9 */
#घोषणा RG_AUDPWDBMICBIAS0_SFT                            0
#घोषणा RG_AUDPWDBMICBIAS0_MASK                           0x1
#घोषणा RG_AUDPWDBMICBIAS0_MASK_SFT                       (0x1 << 0)
#घोषणा RG_AUDMICBIAS0BYPASSEN_SFT                        1
#घोषणा RG_AUDMICBIAS0BYPASSEN_MASK                       0x1
#घोषणा RG_AUDMICBIAS0BYPASSEN_MASK_SFT                   (0x1 << 1)
#घोषणा RG_AUDMICBIAS0LOWPEN_SFT                          2
#घोषणा RG_AUDMICBIAS0LOWPEN_MASK                         0x1
#घोषणा RG_AUDMICBIAS0LOWPEN_MASK_SFT                     (0x1 << 2)
#घोषणा RG_AUDMICBIAS0VREF_SFT                            4
#घोषणा RG_AUDMICBIAS0VREF_MASK                           0x7
#घोषणा RG_AUDMICBIAS0VREF_MASK_SFT                       (0x7 << 4)
#घोषणा RG_AUDMICBIAS0DCSW0P1EN_SFT                       8
#घोषणा RG_AUDMICBIAS0DCSW0P1EN_MASK                      0x1
#घोषणा RG_AUDMICBIAS0DCSW0P1EN_MASK_SFT                  (0x1 << 8)
#घोषणा RG_AUDMICBIAS0DCSW0P2EN_SFT                       9
#घोषणा RG_AUDMICBIAS0DCSW0P2EN_MASK                      0x1
#घोषणा RG_AUDMICBIAS0DCSW0P2EN_MASK_SFT                  (0x1 << 9)
#घोषणा RG_AUDMICBIAS0DCSW0NEN_SFT                        10
#घोषणा RG_AUDMICBIAS0DCSW0NEN_MASK                       0x1
#घोषणा RG_AUDMICBIAS0DCSW0NEN_MASK_SFT                   (0x1 << 10)
#घोषणा RG_AUDMICBIAS0DCSW2P1EN_SFT                       12
#घोषणा RG_AUDMICBIAS0DCSW2P1EN_MASK                      0x1
#घोषणा RG_AUDMICBIAS0DCSW2P1EN_MASK_SFT                  (0x1 << 12)
#घोषणा RG_AUDMICBIAS0DCSW2P2EN_SFT                       13
#घोषणा RG_AUDMICBIAS0DCSW2P2EN_MASK                      0x1
#घोषणा RG_AUDMICBIAS0DCSW2P2EN_MASK_SFT                  (0x1 << 13)
#घोषणा RG_AUDMICBIAS0DCSW2NEN_SFT                        14
#घोषणा RG_AUDMICBIAS0DCSW2NEN_MASK                       0x1
#घोषणा RG_AUDMICBIAS0DCSW2NEN_MASK_SFT                   (0x1 << 14)

/* MT6358_AUDENC_ANA_CON10 */
#घोषणा RG_AUDPWDBMICBIAS1_SFT                            0
#घोषणा RG_AUDPWDBMICBIAS1_MASK                           0x1
#घोषणा RG_AUDPWDBMICBIAS1_MASK_SFT                       (0x1 << 0)
#घोषणा RG_AUDMICBIAS1BYPASSEN_SFT                        1
#घोषणा RG_AUDMICBIAS1BYPASSEN_MASK                       0x1
#घोषणा RG_AUDMICBIAS1BYPASSEN_MASK_SFT                   (0x1 << 1)
#घोषणा RG_AUDMICBIAS1LOWPEN_SFT                          2
#घोषणा RG_AUDMICBIAS1LOWPEN_MASK                         0x1
#घोषणा RG_AUDMICBIAS1LOWPEN_MASK_SFT                     (0x1 << 2)
#घोषणा RG_AUDMICBIAS1VREF_SFT                            4
#घोषणा RG_AUDMICBIAS1VREF_MASK                           0x7
#घोषणा RG_AUDMICBIAS1VREF_MASK_SFT                       (0x7 << 4)
#घोषणा RG_AUDMICBIAS1DCSW1PEN_SFT                        8
#घोषणा RG_AUDMICBIAS1DCSW1PEN_MASK                       0x1
#घोषणा RG_AUDMICBIAS1DCSW1PEN_MASK_SFT                   (0x1 << 8)
#घोषणा RG_AUDMICBIAS1DCSW1NEN_SFT                        9
#घोषणा RG_AUDMICBIAS1DCSW1NEN_MASK                       0x1
#घोषणा RG_AUDMICBIAS1DCSW1NEN_MASK_SFT                   (0x1 << 9)
#घोषणा RG_BANDGAPGEN_SFT                                 12
#घोषणा RG_BANDGAPGEN_MASK                                0x1
#घोषणा RG_BANDGAPGEN_MASK_SFT                            (0x1 << 12)
#घोषणा RG_MTEST_EN_SFT                                   13
#घोषणा RG_MTEST_EN_MASK                                  0x1
#घोषणा RG_MTEST_EN_MASK_SFT                              (0x1 << 13)
#घोषणा RG_MTEST_SEL_SFT                                  14
#घोषणा RG_MTEST_SEL_MASK                                 0x1
#घोषणा RG_MTEST_SEL_MASK_SFT                             (0x1 << 14)
#घोषणा RG_MTEST_CURRENT_SFT                              15
#घोषणा RG_MTEST_CURRENT_MASK                             0x1
#घोषणा RG_MTEST_CURRENT_MASK_SFT                         (0x1 << 15)

/* MT6358_AUDENC_ANA_CON11 */
#घोषणा RG_AUDACCDETMICBIAS0PULLLOW_SFT                   0
#घोषणा RG_AUDACCDETMICBIAS0PULLLOW_MASK                  0x1
#घोषणा RG_AUDACCDETMICBIAS0PULLLOW_MASK_SFT              (0x1 << 0)
#घोषणा RG_AUDACCDETMICBIAS1PULLLOW_SFT                   1
#घोषणा RG_AUDACCDETMICBIAS1PULLLOW_MASK                  0x1
#घोषणा RG_AUDACCDETMICBIAS1PULLLOW_MASK_SFT              (0x1 << 1)
#घोषणा RG_AUDACCDETVIN1PULLLOW_SFT                       2
#घोषणा RG_AUDACCDETVIN1PULLLOW_MASK                      0x1
#घोषणा RG_AUDACCDETVIN1PULLLOW_MASK_SFT                  (0x1 << 2)
#घोषणा RG_AUDACCDETVTHACAL_SFT                           4
#घोषणा RG_AUDACCDETVTHACAL_MASK                          0x1
#घोषणा RG_AUDACCDETVTHACAL_MASK_SFT                      (0x1 << 4)
#घोषणा RG_AUDACCDETVTHBCAL_SFT                           5
#घोषणा RG_AUDACCDETVTHBCAL_MASK                          0x1
#घोषणा RG_AUDACCDETVTHBCAL_MASK_SFT                      (0x1 << 5)
#घोषणा RG_AUDACCDETTVDET_SFT                             6
#घोषणा RG_AUDACCDETTVDET_MASK                            0x1
#घोषणा RG_AUDACCDETTVDET_MASK_SFT                        (0x1 << 6)
#घोषणा RG_ACCDETSEL_SFT                                  7
#घोषणा RG_ACCDETSEL_MASK                                 0x1
#घोषणा RG_ACCDETSEL_MASK_SFT                             (0x1 << 7)
#घोषणा RG_SWBUFMODSEL_SFT                                8
#घोषणा RG_SWBUFMODSEL_MASK                               0x1
#घोषणा RG_SWBUFMODSEL_MASK_SFT                           (0x1 << 8)
#घोषणा RG_SWBUFSWEN_SFT                                  9
#घोषणा RG_SWBUFSWEN_MASK                                 0x1
#घोषणा RG_SWBUFSWEN_MASK_SFT                             (0x1 << 9)
#घोषणा RG_EINTCOMPVTH_SFT                                10
#घोषणा RG_EINTCOMPVTH_MASK                               0x1
#घोषणा RG_EINTCOMPVTH_MASK_SFT                           (0x1 << 10)
#घोषणा RG_EINTCONFIGACCDET_SFT                           11
#घोषणा RG_EINTCONFIGACCDET_MASK                          0x1
#घोषणा RG_EINTCONFIGACCDET_MASK_SFT                      (0x1 << 11)
#घोषणा RG_EINTHIRENB_SFT                                 12
#घोषणा RG_EINTHIRENB_MASK                                0x1
#घोषणा RG_EINTHIRENB_MASK_SFT                            (0x1 << 12)
#घोषणा RG_ACCDET2AUXRESBYPASS_SFT                        13
#घोषणा RG_ACCDET2AUXRESBYPASS_MASK                       0x1
#घोषणा RG_ACCDET2AUXRESBYPASS_MASK_SFT                   (0x1 << 13)
#घोषणा RG_ACCDET2AUXBUFFERBYPASS_SFT                     14
#घोषणा RG_ACCDET2AUXBUFFERBYPASS_MASK                    0x1
#घोषणा RG_ACCDET2AUXBUFFERBYPASS_MASK_SFT                (0x1 << 14)
#घोषणा RG_ACCDET2AUXSWEN_SFT                             15
#घोषणा RG_ACCDET2AUXSWEN_MASK                            0x1
#घोषणा RG_ACCDET2AUXSWEN_MASK_SFT                        (0x1 << 15)

/* MT6358_AUDENC_ANA_CON12 */
#घोषणा RGS_AUDRCTUNELREAD_SFT                            0
#घोषणा RGS_AUDRCTUNELREAD_MASK                           0x1f
#घोषणा RGS_AUDRCTUNELREAD_MASK_SFT                       (0x1f << 0)
#घोषणा RGS_AUDRCTUNERREAD_SFT                            8
#घोषणा RGS_AUDRCTUNERREAD_MASK                           0x1f
#घोषणा RGS_AUDRCTUNERREAD_MASK_SFT                       (0x1f << 8)

/* MT6358_AUDDEC_DSN_ID */
#घोषणा AUDDEC_ANA_ID_SFT                                 0
#घोषणा AUDDEC_ANA_ID_MASK                                0xff
#घोषणा AUDDEC_ANA_ID_MASK_SFT                            (0xff << 0)
#घोषणा AUDDEC_DIG_ID_SFT                                 8
#घोषणा AUDDEC_DIG_ID_MASK                                0xff
#घोषणा AUDDEC_DIG_ID_MASK_SFT                            (0xff << 8)

/* MT6358_AUDDEC_DSN_REV0 */
#घोषणा AUDDEC_ANA_MINOR_REV_SFT                          0
#घोषणा AUDDEC_ANA_MINOR_REV_MASK                         0xf
#घोषणा AUDDEC_ANA_MINOR_REV_MASK_SFT                     (0xf << 0)
#घोषणा AUDDEC_ANA_MAJOR_REV_SFT                          4
#घोषणा AUDDEC_ANA_MAJOR_REV_MASK                         0xf
#घोषणा AUDDEC_ANA_MAJOR_REV_MASK_SFT                     (0xf << 4)
#घोषणा AUDDEC_DIG_MINOR_REV_SFT                          8
#घोषणा AUDDEC_DIG_MINOR_REV_MASK                         0xf
#घोषणा AUDDEC_DIG_MINOR_REV_MASK_SFT                     (0xf << 8)
#घोषणा AUDDEC_DIG_MAJOR_REV_SFT                          12
#घोषणा AUDDEC_DIG_MAJOR_REV_MASK                         0xf
#घोषणा AUDDEC_DIG_MAJOR_REV_MASK_SFT                     (0xf << 12)

/* MT6358_AUDDEC_DSN_DBI */
#घोषणा AUDDEC_DSN_CBS_SFT                                0
#घोषणा AUDDEC_DSN_CBS_MASK                               0x3
#घोषणा AUDDEC_DSN_CBS_MASK_SFT                           (0x3 << 0)
#घोषणा AUDDEC_DSN_BIX_SFT                                2
#घोषणा AUDDEC_DSN_BIX_MASK                               0x3
#घोषणा AUDDEC_DSN_BIX_MASK_SFT                           (0x3 << 2)
#घोषणा AUDDEC_DSN_ESP_SFT                                8
#घोषणा AUDDEC_DSN_ESP_MASK                               0xff
#घोषणा AUDDEC_DSN_ESP_MASK_SFT                           (0xff << 8)

/* MT6358_AUDDEC_DSN_FPI */
#घोषणा AUDDEC_DSN_FPI_SFT                                0
#घोषणा AUDDEC_DSN_FPI_MASK                               0xff
#घोषणा AUDDEC_DSN_FPI_MASK_SFT                           (0xff << 0)

/* MT6358_AUDDEC_ANA_CON0 */
#घोषणा RG_AUDDACLPWRUP_VAUDP15_SFT                       0
#घोषणा RG_AUDDACLPWRUP_VAUDP15_MASK                      0x1
#घोषणा RG_AUDDACLPWRUP_VAUDP15_MASK_SFT                  (0x1 << 0)
#घोषणा RG_AUDDACRPWRUP_VAUDP15_SFT                       1
#घोषणा RG_AUDDACRPWRUP_VAUDP15_MASK                      0x1
#घोषणा RG_AUDDACRPWRUP_VAUDP15_MASK_SFT                  (0x1 << 1)
#घोषणा RG_AUD_DAC_PWR_UP_VA28_SFT                        2
#घोषणा RG_AUD_DAC_PWR_UP_VA28_MASK                       0x1
#घोषणा RG_AUD_DAC_PWR_UP_VA28_MASK_SFT                   (0x1 << 2)
#घोषणा RG_AUD_DAC_PWL_UP_VA28_SFT                        3
#घोषणा RG_AUD_DAC_PWL_UP_VA28_MASK                       0x1
#घोषणा RG_AUD_DAC_PWL_UP_VA28_MASK_SFT                   (0x1 << 3)
#घोषणा RG_AUDHPLPWRUP_VAUDP15_SFT                        4
#घोषणा RG_AUDHPLPWRUP_VAUDP15_MASK                       0x1
#घोषणा RG_AUDHPLPWRUP_VAUDP15_MASK_SFT                   (0x1 << 4)
#घोषणा RG_AUDHPRPWRUP_VAUDP15_SFT                        5
#घोषणा RG_AUDHPRPWRUP_VAUDP15_MASK                       0x1
#घोषणा RG_AUDHPRPWRUP_VAUDP15_MASK_SFT                   (0x1 << 5)
#घोषणा RG_AUDHPLPWRUP_IBIAS_VAUDP15_SFT                  6
#घोषणा RG_AUDHPLPWRUP_IBIAS_VAUDP15_MASK                 0x1
#घोषणा RG_AUDHPLPWRUP_IBIAS_VAUDP15_MASK_SFT             (0x1 << 6)
#घोषणा RG_AUDHPRPWRUP_IBIAS_VAUDP15_SFT                  7
#घोषणा RG_AUDHPRPWRUP_IBIAS_VAUDP15_MASK                 0x1
#घोषणा RG_AUDHPRPWRUP_IBIAS_VAUDP15_MASK_SFT             (0x1 << 7)
#घोषणा RG_AUDHPLMUXINPUTSEL_VAUDP15_SFT                  8
#घोषणा RG_AUDHPLMUXINPUTSEL_VAUDP15_MASK                 0x3
#घोषणा RG_AUDHPLMUXINPUTSEL_VAUDP15_MASK_SFT             (0x3 << 8)
#घोषणा RG_AUDHPRMUXINPUTSEL_VAUDP15_SFT                  10
#घोषणा RG_AUDHPRMUXINPUTSEL_VAUDP15_MASK                 0x3
#घोषणा RG_AUDHPRMUXINPUTSEL_VAUDP15_MASK_SFT             (0x3 << 10)
#घोषणा RG_AUDHPLSCDISABLE_VAUDP15_SFT                    12
#घोषणा RG_AUDHPLSCDISABLE_VAUDP15_MASK                   0x1
#घोषणा RG_AUDHPLSCDISABLE_VAUDP15_MASK_SFT               (0x1 << 12)
#घोषणा RG_AUDHPRSCDISABLE_VAUDP15_SFT                    13
#घोषणा RG_AUDHPRSCDISABLE_VAUDP15_MASK                   0x1
#घोषणा RG_AUDHPRSCDISABLE_VAUDP15_MASK_SFT               (0x1 << 13)
#घोषणा RG_AUDHPLBSCCURRENT_VAUDP15_SFT                   14
#घोषणा RG_AUDHPLBSCCURRENT_VAUDP15_MASK                  0x1
#घोषणा RG_AUDHPLBSCCURRENT_VAUDP15_MASK_SFT              (0x1 << 14)
#घोषणा RG_AUDHPRBSCCURRENT_VAUDP15_SFT                   15
#घोषणा RG_AUDHPRBSCCURRENT_VAUDP15_MASK                  0x1
#घोषणा RG_AUDHPRBSCCURRENT_VAUDP15_MASK_SFT              (0x1 << 15)

/* MT6358_AUDDEC_ANA_CON1 */
#घोषणा RG_AUDHPLOUTPWRUP_VAUDP15_SFT                     0
#घोषणा RG_AUDHPLOUTPWRUP_VAUDP15_MASK                    0x1
#घोषणा RG_AUDHPLOUTPWRUP_VAUDP15_MASK_SFT                (0x1 << 0)
#घोषणा RG_AUDHPROUTPWRUP_VAUDP15_SFT                     1
#घोषणा RG_AUDHPROUTPWRUP_VAUDP15_MASK                    0x1
#घोषणा RG_AUDHPROUTPWRUP_VAUDP15_MASK_SFT                (0x1 << 1)
#घोषणा RG_AUDHPLOUTAUXPWRUP_VAUDP15_SFT                  2
#घोषणा RG_AUDHPLOUTAUXPWRUP_VAUDP15_MASK                 0x1
#घोषणा RG_AUDHPLOUTAUXPWRUP_VAUDP15_MASK_SFT             (0x1 << 2)
#घोषणा RG_AUDHPROUTAUXPWRUP_VAUDP15_SFT                  3
#घोषणा RG_AUDHPROUTAUXPWRUP_VAUDP15_MASK                 0x1
#घोषणा RG_AUDHPROUTAUXPWRUP_VAUDP15_MASK_SFT             (0x1 << 3)
#घोषणा RG_HPLAUXFBRSW_EN_VAUDP15_SFT                     4
#घोषणा RG_HPLAUXFBRSW_EN_VAUDP15_MASK                    0x1
#घोषणा RG_HPLAUXFBRSW_EN_VAUDP15_MASK_SFT                (0x1 << 4)
#घोषणा RG_HPRAUXFBRSW_EN_VAUDP15_SFT                     5
#घोषणा RG_HPRAUXFBRSW_EN_VAUDP15_MASK                    0x1
#घोषणा RG_HPRAUXFBRSW_EN_VAUDP15_MASK_SFT                (0x1 << 5)
#घोषणा RG_HPLSHORT2HPLAUX_EN_VAUDP15_SFT                 6
#घोषणा RG_HPLSHORT2HPLAUX_EN_VAUDP15_MASK                0x1
#घोषणा RG_HPLSHORT2HPLAUX_EN_VAUDP15_MASK_SFT            (0x1 << 6)
#घोषणा RG_HPRSHORT2HPRAUX_EN_VAUDP15_SFT                 7
#घोषणा RG_HPRSHORT2HPRAUX_EN_VAUDP15_MASK                0x1
#घोषणा RG_HPRSHORT2HPRAUX_EN_VAUDP15_MASK_SFT            (0x1 << 7)
#घोषणा RG_HPLOUTSTGCTRL_VAUDP15_SFT                      8
#घोषणा RG_HPLOUTSTGCTRL_VAUDP15_MASK                     0x7
#घोषणा RG_HPLOUTSTGCTRL_VAUDP15_MASK_SFT                 (0x7 << 8)
#घोषणा RG_HPROUTSTGCTRL_VAUDP15_SFT                      11
#घोषणा RG_HPROUTSTGCTRL_VAUDP15_MASK                     0x7
#घोषणा RG_HPROUTSTGCTRL_VAUDP15_MASK_SFT                 (0x7 << 11)

/* MT6358_AUDDEC_ANA_CON2 */
#घोषणा RG_HPLOUTPUTSTBENH_VAUDP15_SFT                    0
#घोषणा RG_HPLOUTPUTSTBENH_VAUDP15_MASK                   0x7
#घोषणा RG_HPLOUTPUTSTBENH_VAUDP15_MASK_SFT               (0x7 << 0)
#घोषणा RG_HPROUTPUTSTBENH_VAUDP15_SFT                    4
#घोषणा RG_HPROUTPUTSTBENH_VAUDP15_MASK                   0x7
#घोषणा RG_HPROUTPUTSTBENH_VAUDP15_MASK_SFT               (0x7 << 4)
#घोषणा RG_AUDHPSTARTUP_VAUDP15_SFT                       13
#घोषणा RG_AUDHPSTARTUP_VAUDP15_MASK                      0x1
#घोषणा RG_AUDHPSTARTUP_VAUDP15_MASK_SFT                  (0x1 << 13)
#घोषणा RG_AUDREFN_DERES_EN_VAUDP15_SFT                   14
#घोषणा RG_AUDREFN_DERES_EN_VAUDP15_MASK                  0x1
#घोषणा RG_AUDREFN_DERES_EN_VAUDP15_MASK_SFT              (0x1 << 14)
#घोषणा RG_HPPSHORT2VCM_VAUDP15_SFT                       15
#घोषणा RG_HPPSHORT2VCM_VAUDP15_MASK                      0x1
#घोषणा RG_HPPSHORT2VCM_VAUDP15_MASK_SFT                  (0x1 << 15)

/* MT6358_AUDDEC_ANA_CON3 */
#घोषणा RG_HPINPUTSTBENH_VAUDP15_SFT                      13
#घोषणा RG_HPINPUTSTBENH_VAUDP15_MASK                     0x1
#घोषणा RG_HPINPUTSTBENH_VAUDP15_MASK_SFT                 (0x1 << 13)
#घोषणा RG_HPINPUTRESET0_VAUDP15_SFT                      14
#घोषणा RG_HPINPUTRESET0_VAUDP15_MASK                     0x1
#घोषणा RG_HPINPUTRESET0_VAUDP15_MASK_SFT                 (0x1 << 14)
#घोषणा RG_HPOUTPUTRESET0_VAUDP15_SFT                     15
#घोषणा RG_HPOUTPUTRESET0_VAUDP15_MASK                    0x1
#घोषणा RG_HPOUTPUTRESET0_VAUDP15_MASK_SFT                (0x1 << 15)

/* MT6358_AUDDEC_ANA_CON4 */
#घोषणा RG_ABIDEC_RSVD0_VAUDP28_SFT                       0
#घोषणा RG_ABIDEC_RSVD0_VAUDP28_MASK                      0xff
#घोषणा RG_ABIDEC_RSVD0_VAUDP28_MASK_SFT                  (0xff << 0)

/* MT6358_AUDDEC_ANA_CON5 */
#घोषणा RG_AUDHPDECMGAINADJ_VAUDP15_SFT                   0
#घोषणा RG_AUDHPDECMGAINADJ_VAUDP15_MASK                  0x7
#घोषणा RG_AUDHPDECMGAINADJ_VAUDP15_MASK_SFT              (0x7 << 0)
#घोषणा RG_AUDHPDEDMGAINADJ_VAUDP15_SFT                   4
#घोषणा RG_AUDHPDEDMGAINADJ_VAUDP15_MASK                  0x7
#घोषणा RG_AUDHPDEDMGAINADJ_VAUDP15_MASK_SFT              (0x7 << 4)

/* MT6358_AUDDEC_ANA_CON6 */
#घोषणा RG_AUDHSPWRUP_VAUDP15_SFT                         0
#घोषणा RG_AUDHSPWRUP_VAUDP15_MASK                        0x1
#घोषणा RG_AUDHSPWRUP_VAUDP15_MASK_SFT                    (0x1 << 0)
#घोषणा RG_AUDHSPWRUP_IBIAS_VAUDP15_SFT                   1
#घोषणा RG_AUDHSPWRUP_IBIAS_VAUDP15_MASK                  0x1
#घोषणा RG_AUDHSPWRUP_IBIAS_VAUDP15_MASK_SFT              (0x1 << 1)
#घोषणा RG_AUDHSMUXINPUTSEL_VAUDP15_SFT                   2
#घोषणा RG_AUDHSMUXINPUTSEL_VAUDP15_MASK                  0x3
#घोषणा RG_AUDHSMUXINPUTSEL_VAUDP15_MASK_SFT              (0x3 << 2)
#घोषणा RG_AUDHSSCDISABLE_VAUDP15_SFT                     4
#घोषणा RG_AUDHSSCDISABLE_VAUDP15_MASK                    0x1
#घोषणा RG_AUDHSSCDISABLE_VAUDP15_MASK_SFT                (0x1 << 4)
#घोषणा RG_AUDHSBSCCURRENT_VAUDP15_SFT                    5
#घोषणा RG_AUDHSBSCCURRENT_VAUDP15_MASK                   0x1
#घोषणा RG_AUDHSBSCCURRENT_VAUDP15_MASK_SFT               (0x1 << 5)
#घोषणा RG_AUDHSSTARTUP_VAUDP15_SFT                       6
#घोषणा RG_AUDHSSTARTUP_VAUDP15_MASK                      0x1
#घोषणा RG_AUDHSSTARTUP_VAUDP15_MASK_SFT                  (0x1 << 6)
#घोषणा RG_HSOUTPUTSTBENH_VAUDP15_SFT                     7
#घोषणा RG_HSOUTPUTSTBENH_VAUDP15_MASK                    0x1
#घोषणा RG_HSOUTPUTSTBENH_VAUDP15_MASK_SFT                (0x1 << 7)
#घोषणा RG_HSINPUTSTBENH_VAUDP15_SFT                      8
#घोषणा RG_HSINPUTSTBENH_VAUDP15_MASK                     0x1
#घोषणा RG_HSINPUTSTBENH_VAUDP15_MASK_SFT                 (0x1 << 8)
#घोषणा RG_HSINPUTRESET0_VAUDP15_SFT                      9
#घोषणा RG_HSINPUTRESET0_VAUDP15_MASK                     0x1
#घोषणा RG_HSINPUTRESET0_VAUDP15_MASK_SFT                 (0x1 << 9)
#घोषणा RG_HSOUTPUTRESET0_VAUDP15_SFT                     10
#घोषणा RG_HSOUTPUTRESET0_VAUDP15_MASK                    0x1
#घोषणा RG_HSOUTPUTRESET0_VAUDP15_MASK_SFT                (0x1 << 10)
#घोषणा RG_HSOUT_SHORTVCM_VAUDP15_SFT                     11
#घोषणा RG_HSOUT_SHORTVCM_VAUDP15_MASK                    0x1
#घोषणा RG_HSOUT_SHORTVCM_VAUDP15_MASK_SFT                (0x1 << 11)

/* MT6358_AUDDEC_ANA_CON7 */
#घोषणा RG_AUDLOLPWRUP_VAUDP15_SFT                        0
#घोषणा RG_AUDLOLPWRUP_VAUDP15_MASK                       0x1
#घोषणा RG_AUDLOLPWRUP_VAUDP15_MASK_SFT                   (0x1 << 0)
#घोषणा RG_AUDLOLPWRUP_IBIAS_VAUDP15_SFT                  1
#घोषणा RG_AUDLOLPWRUP_IBIAS_VAUDP15_MASK                 0x1
#घोषणा RG_AUDLOLPWRUP_IBIAS_VAUDP15_MASK_SFT             (0x1 << 1)
#घोषणा RG_AUDLOLMUXINPUTSEL_VAUDP15_SFT                  2
#घोषणा RG_AUDLOLMUXINPUTSEL_VAUDP15_MASK                 0x3
#घोषणा RG_AUDLOLMUXINPUTSEL_VAUDP15_MASK_SFT             (0x3 << 2)
#घोषणा RG_AUDLOLSCDISABLE_VAUDP15_SFT                    4
#घोषणा RG_AUDLOLSCDISABLE_VAUDP15_MASK                   0x1
#घोषणा RG_AUDLOLSCDISABLE_VAUDP15_MASK_SFT               (0x1 << 4)
#घोषणा RG_AUDLOLBSCCURRENT_VAUDP15_SFT                   5
#घोषणा RG_AUDLOLBSCCURRENT_VAUDP15_MASK                  0x1
#घोषणा RG_AUDLOLBSCCURRENT_VAUDP15_MASK_SFT              (0x1 << 5)
#घोषणा RG_AUDLOSTARTUP_VAUDP15_SFT                       6
#घोषणा RG_AUDLOSTARTUP_VAUDP15_MASK                      0x1
#घोषणा RG_AUDLOSTARTUP_VAUDP15_MASK_SFT                  (0x1 << 6)
#घोषणा RG_LOINPUTSTBENH_VAUDP15_SFT                      7
#घोषणा RG_LOINPUTSTBENH_VAUDP15_MASK                     0x1
#घोषणा RG_LOINPUTSTBENH_VAUDP15_MASK_SFT                 (0x1 << 7)
#घोषणा RG_LOOUTPUTSTBENH_VAUDP15_SFT                     8
#घोषणा RG_LOOUTPUTSTBENH_VAUDP15_MASK                    0x1
#घोषणा RG_LOOUTPUTSTBENH_VAUDP15_MASK_SFT                (0x1 << 8)
#घोषणा RG_LOINPUTRESET0_VAUDP15_SFT                      9
#घोषणा RG_LOINPUTRESET0_VAUDP15_MASK                     0x1
#घोषणा RG_LOINPUTRESET0_VAUDP15_MASK_SFT                 (0x1 << 9)
#घोषणा RG_LOOUTPUTRESET0_VAUDP15_SFT                     10
#घोषणा RG_LOOUTPUTRESET0_VAUDP15_MASK                    0x1
#घोषणा RG_LOOUTPUTRESET0_VAUDP15_MASK_SFT                (0x1 << 10)
#घोषणा RG_LOOUT_SHORTVCM_VAUDP15_SFT                     11
#घोषणा RG_LOOUT_SHORTVCM_VAUDP15_MASK                    0x1
#घोषणा RG_LOOUT_SHORTVCM_VAUDP15_MASK_SFT                (0x1 << 11)

/* MT6358_AUDDEC_ANA_CON8 */
#घोषणा RG_AUDTRIMBUF_INPUTMUXSEL_VAUDP15_SFT             0
#घोषणा RG_AUDTRIMBUF_INPUTMUXSEL_VAUDP15_MASK            0xf
#घोषणा RG_AUDTRIMBUF_INPUTMUXSEL_VAUDP15_MASK_SFT        (0xf << 0)
#घोषणा RG_AUDTRIMBUF_GAINSEL_VAUDP15_SFT                 4
#घोषणा RG_AUDTRIMBUF_GAINSEL_VAUDP15_MASK                0x3
#घोषणा RG_AUDTRIMBUF_GAINSEL_VAUDP15_MASK_SFT            (0x3 << 4)
#घोषणा RG_AUDTRIMBUF_EN_VAUDP15_SFT                      6
#घोषणा RG_AUDTRIMBUF_EN_VAUDP15_MASK                     0x1
#घोषणा RG_AUDTRIMBUF_EN_VAUDP15_MASK_SFT                 (0x1 << 6)
#घोषणा RG_AUDHPSPKDET_INPUTMUXSEL_VAUDP15_SFT            8
#घोषणा RG_AUDHPSPKDET_INPUTMUXSEL_VAUDP15_MASK           0x3
#घोषणा RG_AUDHPSPKDET_INPUTMUXSEL_VAUDP15_MASK_SFT       (0x3 << 8)
#घोषणा RG_AUDHPSPKDET_OUTPUTMUXSEL_VAUDP15_SFT           10
#घोषणा RG_AUDHPSPKDET_OUTPUTMUXSEL_VAUDP15_MASK          0x3
#घोषणा RG_AUDHPSPKDET_OUTPUTMUXSEL_VAUDP15_MASK_SFT      (0x3 << 10)
#घोषणा RG_AUDHPSPKDET_EN_VAUDP15_SFT                     12
#घोषणा RG_AUDHPSPKDET_EN_VAUDP15_MASK                    0x1
#घोषणा RG_AUDHPSPKDET_EN_VAUDP15_MASK_SFT                (0x1 << 12)

/* MT6358_AUDDEC_ANA_CON9 */
#घोषणा RG_ABIDEC_RSVD0_VA28_SFT                          0
#घोषणा RG_ABIDEC_RSVD0_VA28_MASK                         0xff
#घोषणा RG_ABIDEC_RSVD0_VA28_MASK_SFT                     (0xff << 0)
#घोषणा RG_ABIDEC_RSVD0_VAUDP15_SFT                       8
#घोषणा RG_ABIDEC_RSVD0_VAUDP15_MASK                      0xff
#घोषणा RG_ABIDEC_RSVD0_VAUDP15_MASK_SFT                  (0xff << 8)

/* MT6358_AUDDEC_ANA_CON10 */
#घोषणा RG_ABIDEC_RSVD1_VAUDP15_SFT                       0
#घोषणा RG_ABIDEC_RSVD1_VAUDP15_MASK                      0xff
#घोषणा RG_ABIDEC_RSVD1_VAUDP15_MASK_SFT                  (0xff << 0)
#घोषणा RG_ABIDEC_RSVD2_VAUDP15_SFT                       8
#घोषणा RG_ABIDEC_RSVD2_VAUDP15_MASK                      0xff
#घोषणा RG_ABIDEC_RSVD2_VAUDP15_MASK_SFT                  (0xff << 8)

/* MT6358_AUDDEC_ANA_CON11 */
#घोषणा RG_AUDZCDMUXSEL_VAUDP15_SFT                       0
#घोषणा RG_AUDZCDMUXSEL_VAUDP15_MASK                      0x7
#घोषणा RG_AUDZCDMUXSEL_VAUDP15_MASK_SFT                  (0x7 << 0)
#घोषणा RG_AUDZCDCLKSEL_VAUDP15_SFT                       3
#घोषणा RG_AUDZCDCLKSEL_VAUDP15_MASK                      0x1
#घोषणा RG_AUDZCDCLKSEL_VAUDP15_MASK_SFT                  (0x1 << 3)
#घोषणा RG_AUDBIASADJ_0_VAUDP15_SFT                       7
#घोषणा RG_AUDBIASADJ_0_VAUDP15_MASK                      0x1ff
#घोषणा RG_AUDBIASADJ_0_VAUDP15_MASK_SFT                  (0x1ff << 7)

/* MT6358_AUDDEC_ANA_CON12 */
#घोषणा RG_AUDBIASADJ_1_VAUDP15_SFT                       0
#घोषणा RG_AUDBIASADJ_1_VAUDP15_MASK                      0xff
#घोषणा RG_AUDBIASADJ_1_VAUDP15_MASK_SFT                  (0xff << 0)
#घोषणा RG_AUDIBIASPWRDN_VAUDP15_SFT                      8
#घोषणा RG_AUDIBIASPWRDN_VAUDP15_MASK                     0x1
#घोषणा RG_AUDIBIASPWRDN_VAUDP15_MASK_SFT                 (0x1 << 8)

/* MT6358_AUDDEC_ANA_CON13 */
#घोषणा RG_RSTB_DECODER_VA28_SFT                          0
#घोषणा RG_RSTB_DECODER_VA28_MASK                         0x1
#घोषणा RG_RSTB_DECODER_VA28_MASK_SFT                     (0x1 << 0)
#घोषणा RG_SEL_DECODER_96K_VA28_SFT                       1
#घोषणा RG_SEL_DECODER_96K_VA28_MASK                      0x1
#घोषणा RG_SEL_DECODER_96K_VA28_MASK_SFT                  (0x1 << 1)
#घोषणा RG_SEL_DELAY_VCORE_SFT                            2
#घोषणा RG_SEL_DELAY_VCORE_MASK                           0x1
#घोषणा RG_SEL_DELAY_VCORE_MASK_SFT                       (0x1 << 2)
#घोषणा RG_AUDGLB_PWRDN_VA28_SFT                          4
#घोषणा RG_AUDGLB_PWRDN_VA28_MASK                         0x1
#घोषणा RG_AUDGLB_PWRDN_VA28_MASK_SFT                     (0x1 << 4)
#घोषणा RG_RSTB_ENCODER_VA28_SFT                          5
#घोषणा RG_RSTB_ENCODER_VA28_MASK                         0x1
#घोषणा RG_RSTB_ENCODER_VA28_MASK_SFT                     (0x1 << 5)
#घोषणा RG_SEL_ENCODER_96K_VA28_SFT                       6
#घोषणा RG_SEL_ENCODER_96K_VA28_MASK                      0x1
#घोषणा RG_SEL_ENCODER_96K_VA28_MASK_SFT                  (0x1 << 6)

/* MT6358_AUDDEC_ANA_CON14 */
#घोषणा RG_HCLDO_EN_VA18_SFT                              0
#घोषणा RG_HCLDO_EN_VA18_MASK                             0x1
#घोषणा RG_HCLDO_EN_VA18_MASK_SFT                         (0x1 << 0)
#घोषणा RG_HCLDO_PDDIS_EN_VA18_SFT                        1
#घोषणा RG_HCLDO_PDDIS_EN_VA18_MASK                       0x1
#घोषणा RG_HCLDO_PDDIS_EN_VA18_MASK_SFT                   (0x1 << 1)
#घोषणा RG_HCLDO_REMOTE_SENSE_VA18_SFT                    2
#घोषणा RG_HCLDO_REMOTE_SENSE_VA18_MASK                   0x1
#घोषणा RG_HCLDO_REMOTE_SENSE_VA18_MASK_SFT               (0x1 << 2)
#घोषणा RG_LCLDO_EN_VA18_SFT                              4
#घोषणा RG_LCLDO_EN_VA18_MASK                             0x1
#घोषणा RG_LCLDO_EN_VA18_MASK_SFT                         (0x1 << 4)
#घोषणा RG_LCLDO_PDDIS_EN_VA18_SFT                        5
#घोषणा RG_LCLDO_PDDIS_EN_VA18_MASK                       0x1
#घोषणा RG_LCLDO_PDDIS_EN_VA18_MASK_SFT                   (0x1 << 5)
#घोषणा RG_LCLDO_REMOTE_SENSE_VA18_SFT                    6
#घोषणा RG_LCLDO_REMOTE_SENSE_VA18_MASK                   0x1
#घोषणा RG_LCLDO_REMOTE_SENSE_VA18_MASK_SFT               (0x1 << 6)
#घोषणा RG_LCLDO_ENC_EN_VA28_SFT                          8
#घोषणा RG_LCLDO_ENC_EN_VA28_MASK                         0x1
#घोषणा RG_LCLDO_ENC_EN_VA28_MASK_SFT                     (0x1 << 8)
#घोषणा RG_LCLDO_ENC_PDDIS_EN_VA28_SFT                    9
#घोषणा RG_LCLDO_ENC_PDDIS_EN_VA28_MASK                   0x1
#घोषणा RG_LCLDO_ENC_PDDIS_EN_VA28_MASK_SFT               (0x1 << 9)
#घोषणा RG_LCLDO_ENC_REMOTE_SENSE_VA28_SFT                10
#घोषणा RG_LCLDO_ENC_REMOTE_SENSE_VA28_MASK               0x1
#घोषणा RG_LCLDO_ENC_REMOTE_SENSE_VA28_MASK_SFT           (0x1 << 10)
#घोषणा RG_VA33REFGEN_EN_VA18_SFT                         12
#घोषणा RG_VA33REFGEN_EN_VA18_MASK                        0x1
#घोषणा RG_VA33REFGEN_EN_VA18_MASK_SFT                    (0x1 << 12)
#घोषणा RG_VA28REFGEN_EN_VA28_SFT                         13
#घोषणा RG_VA28REFGEN_EN_VA28_MASK                        0x1
#घोषणा RG_VA28REFGEN_EN_VA28_MASK_SFT                    (0x1 << 13)
#घोषणा RG_HCLDO_VOSEL_VA18_SFT                           14
#घोषणा RG_HCLDO_VOSEL_VA18_MASK                          0x1
#घोषणा RG_HCLDO_VOSEL_VA18_MASK_SFT                      (0x1 << 14)
#घोषणा RG_LCLDO_VOSEL_VA18_SFT                           15
#घोषणा RG_LCLDO_VOSEL_VA18_MASK                          0x1
#घोषणा RG_LCLDO_VOSEL_VA18_MASK_SFT                      (0x1 << 15)

/* MT6358_AUDDEC_ANA_CON15 */
#घोषणा RG_NVREG_EN_VAUDP15_SFT                           0
#घोषणा RG_NVREG_EN_VAUDP15_MASK                          0x1
#घोषणा RG_NVREG_EN_VAUDP15_MASK_SFT                      (0x1 << 0)
#घोषणा RG_NVREG_PULL0V_VAUDP15_SFT                       1
#घोषणा RG_NVREG_PULL0V_VAUDP15_MASK                      0x1
#घोषणा RG_NVREG_PULL0V_VAUDP15_MASK_SFT                  (0x1 << 1)
#घोषणा RG_AUDPMU_RSD0_VAUDP15_SFT                        4
#घोषणा RG_AUDPMU_RSD0_VAUDP15_MASK                       0xf
#घोषणा RG_AUDPMU_RSD0_VAUDP15_MASK_SFT                   (0xf << 4)
#घोषणा RG_AUDPMU_RSD0_VA18_SFT                           8
#घोषणा RG_AUDPMU_RSD0_VA18_MASK                          0xf
#घोषणा RG_AUDPMU_RSD0_VA18_MASK_SFT                      (0xf << 8)
#घोषणा RG_AUDPMU_RSD0_VA28_SFT                           12
#घोषणा RG_AUDPMU_RSD0_VA28_MASK                          0xf
#घोषणा RG_AUDPMU_RSD0_VA28_MASK_SFT                      (0xf << 12)

/* MT6358_ZCD_CON0 */
#घोषणा RG_AUDZCDENABLE_SFT                               0
#घोषणा RG_AUDZCDENABLE_MASK                              0x1
#घोषणा RG_AUDZCDENABLE_MASK_SFT                          (0x1 << 0)
#घोषणा RG_AUDZCDGAINSTEPTIME_SFT                         1
#घोषणा RG_AUDZCDGAINSTEPTIME_MASK                        0x7
#घोषणा RG_AUDZCDGAINSTEPTIME_MASK_SFT                    (0x7 << 1)
#घोषणा RG_AUDZCDGAINSTEPSIZE_SFT                         4
#घोषणा RG_AUDZCDGAINSTEPSIZE_MASK                        0x3
#घोषणा RG_AUDZCDGAINSTEPSIZE_MASK_SFT                    (0x3 << 4)
#घोषणा RG_AUDZCDTIMEOUTMODESEL_SFT                       6
#घोषणा RG_AUDZCDTIMEOUTMODESEL_MASK                      0x1
#घोषणा RG_AUDZCDTIMEOUTMODESEL_MASK_SFT                  (0x1 << 6)

/* MT6358_ZCD_CON1 */
#घोषणा RG_AUDLOLGAIN_SFT                                 0
#घोषणा RG_AUDLOLGAIN_MASK                                0x1f
#घोषणा RG_AUDLOLGAIN_MASK_SFT                            (0x1f << 0)
#घोषणा RG_AUDLORGAIN_SFT                                 7
#घोषणा RG_AUDLORGAIN_MASK                                0x1f
#घोषणा RG_AUDLORGAIN_MASK_SFT                            (0x1f << 7)

/* MT6358_ZCD_CON2 */
#घोषणा RG_AUDHPLGAIN_SFT                                 0
#घोषणा RG_AUDHPLGAIN_MASK                                0x1f
#घोषणा RG_AUDHPLGAIN_MASK_SFT                            (0x1f << 0)
#घोषणा RG_AUDHPRGAIN_SFT                                 7
#घोषणा RG_AUDHPRGAIN_MASK                                0x1f
#घोषणा RG_AUDHPRGAIN_MASK_SFT                            (0x1f << 7)

/* MT6358_ZCD_CON3 */
#घोषणा RG_AUDHSGAIN_SFT                                  0
#घोषणा RG_AUDHSGAIN_MASK                                 0x1f
#घोषणा RG_AUDHSGAIN_MASK_SFT                             (0x1f << 0)

/* MT6358_ZCD_CON4 */
#घोषणा RG_AUDIVLGAIN_SFT                                 0
#घोषणा RG_AUDIVLGAIN_MASK                                0x7
#घोषणा RG_AUDIVLGAIN_MASK_SFT                            (0x7 << 0)
#घोषणा RG_AUDIVRGAIN_SFT                                 8
#घोषणा RG_AUDIVRGAIN_MASK                                0x7
#घोषणा RG_AUDIVRGAIN_MASK_SFT                            (0x7 << 8)

/* MT6358_ZCD_CON5 */
#घोषणा RG_AUDINTGAIN1_SFT                                0
#घोषणा RG_AUDINTGAIN1_MASK                               0x3f
#घोषणा RG_AUDINTGAIN1_MASK_SFT                           (0x3f << 0)
#घोषणा RG_AUDINTGAIN2_SFT                                8
#घोषणा RG_AUDINTGAIN2_MASK                               0x3f
#घोषणा RG_AUDINTGAIN2_MASK_SFT                           (0x3f << 8)

/* audio रेजिस्टर */
#घोषणा MT6358_DRV_CON3            0x3c
#घोषणा MT6358_GPIO_सूची0           0x88

#घोषणा MT6358_GPIO_MODE2          0xd8	/* mosi */
#घोषणा MT6358_GPIO_MODE2_SET      0xda
#घोषणा MT6358_GPIO_MODE2_CLR      0xdc

#घोषणा MT6358_GPIO_MODE3          0xde	/* miso */
#घोषणा MT6358_GPIO_MODE3_SET      0xe0
#घोषणा MT6358_GPIO_MODE3_CLR      0xe2

#घोषणा MT6358_TOP_CKPDN_CON0      0x10c
#घोषणा MT6358_TOP_CKPDN_CON0_SET  0x10e
#घोषणा MT6358_TOP_CKPDN_CON0_CLR  0x110

#घोषणा MT6358_TOP_CKHWEN_CON0     0x12a
#घोषणा MT6358_TOP_CKHWEN_CON0_SET 0x12c
#घोषणा MT6358_TOP_CKHWEN_CON0_CLR 0x12e

#घोषणा MT6358_OTP_CON0            0x38a
#घोषणा MT6358_OTP_CON8            0x39a
#घोषणा MT6358_OTP_CON11           0x3a0
#घोषणा MT6358_OTP_CON12           0x3a2
#घोषणा MT6358_OTP_CON13           0x3a4

#घोषणा MT6358_DCXO_CW13           0x7aa
#घोषणा MT6358_DCXO_CW14           0x7ac

#घोषणा MT6358_AUXADC_CON10        0x11a0

/* audio रेजिस्टर */
#घोषणा MT6358_AUD_TOP_ID                    0x2200
#घोषणा MT6358_AUD_TOP_REV0                  0x2202
#घोषणा MT6358_AUD_TOP_DBI                   0x2204
#घोषणा MT6358_AUD_TOP_DXI                   0x2206
#घोषणा MT6358_AUD_TOP_CKPDN_TPM0            0x2208
#घोषणा MT6358_AUD_TOP_CKPDN_TPM1            0x220a
#घोषणा MT6358_AUD_TOP_CKPDN_CON0            0x220c
#घोषणा MT6358_AUD_TOP_CKPDN_CON0_SET        0x220e
#घोषणा MT6358_AUD_TOP_CKPDN_CON0_CLR        0x2210
#घोषणा MT6358_AUD_TOP_CKSEL_CON0            0x2212
#घोषणा MT6358_AUD_TOP_CKSEL_CON0_SET        0x2214
#घोषणा MT6358_AUD_TOP_CKSEL_CON0_CLR        0x2216
#घोषणा MT6358_AUD_TOP_CKTST_CON0            0x2218
#घोषणा MT6358_AUD_TOP_CLK_HWEN_CON0         0x221a
#घोषणा MT6358_AUD_TOP_CLK_HWEN_CON0_SET     0x221c
#घोषणा MT6358_AUD_TOP_CLK_HWEN_CON0_CLR     0x221e
#घोषणा MT6358_AUD_TOP_RST_CON0              0x2220
#घोषणा MT6358_AUD_TOP_RST_CON0_SET          0x2222
#घोषणा MT6358_AUD_TOP_RST_CON0_CLR          0x2224
#घोषणा MT6358_AUD_TOP_RST_BANK_CON0         0x2226
#घोषणा MT6358_AUD_TOP_INT_CON0              0x2228
#घोषणा MT6358_AUD_TOP_INT_CON0_SET          0x222a
#घोषणा MT6358_AUD_TOP_INT_CON0_CLR          0x222c
#घोषणा MT6358_AUD_TOP_INT_MASK_CON0         0x222e
#घोषणा MT6358_AUD_TOP_INT_MASK_CON0_SET     0x2230
#घोषणा MT6358_AUD_TOP_INT_MASK_CON0_CLR     0x2232
#घोषणा MT6358_AUD_TOP_INT_STATUS0           0x2234
#घोषणा MT6358_AUD_TOP_INT_RAW_STATUS0       0x2236
#घोषणा MT6358_AUD_TOP_INT_MISC_CON0         0x2238
#घोषणा MT6358_AUDNCP_CLKDIV_CON0            0x223a
#घोषणा MT6358_AUDNCP_CLKDIV_CON1            0x223c
#घोषणा MT6358_AUDNCP_CLKDIV_CON2            0x223e
#घोषणा MT6358_AUDNCP_CLKDIV_CON3            0x2240
#घोषणा MT6358_AUDNCP_CLKDIV_CON4            0x2242
#घोषणा MT6358_AUD_TOP_MON_CON0              0x2244
#घोषणा MT6358_AUDIO_DIG_DSN_ID              0x2280
#घोषणा MT6358_AUDIO_DIG_DSN_REV0            0x2282
#घोषणा MT6358_AUDIO_DIG_DSN_DBI             0x2284
#घोषणा MT6358_AUDIO_DIG_DSN_DXI             0x2286
#घोषणा MT6358_AFE_UL_DL_CON0                0x2288
#घोषणा MT6358_AFE_DL_SRC2_CON0_L            0x228a
#घोषणा MT6358_AFE_UL_SRC_CON0_H             0x228c
#घोषणा MT6358_AFE_UL_SRC_CON0_L             0x228e
#घोषणा MT6358_AFE_TOP_CON0                  0x2290
#घोषणा MT6358_AUDIO_TOP_CON0                0x2292
#घोषणा MT6358_AFE_MON_DEBUG0                0x2294
#घोषणा MT6358_AFUNC_AUD_CON0                0x2296
#घोषणा MT6358_AFUNC_AUD_CON1                0x2298
#घोषणा MT6358_AFUNC_AUD_CON2                0x229a
#घोषणा MT6358_AFUNC_AUD_CON3                0x229c
#घोषणा MT6358_AFUNC_AUD_CON4                0x229e
#घोषणा MT6358_AFUNC_AUD_CON5                0x22a0
#घोषणा MT6358_AFUNC_AUD_CON6                0x22a2
#घोषणा MT6358_AFUNC_AUD_MON0                0x22a4
#घोषणा MT6358_AUDRC_TUNE_MON0               0x22a6
#घोषणा MT6358_AFE_ADDA_MTKAIF_FIFO_CFG0     0x22a8
#घोषणा MT6358_AFE_ADDA_MTKAIF_FIFO_LOG_MON1 0x22aa
#घोषणा MT6358_AFE_ADDA_MTKAIF_MON0          0x22ac
#घोषणा MT6358_AFE_ADDA_MTKAIF_MON1          0x22ae
#घोषणा MT6358_AFE_ADDA_MTKAIF_MON2          0x22b0
#घोषणा MT6358_AFE_ADDA_MTKAIF_MON3          0x22b2
#घोषणा MT6358_AFE_ADDA_MTKAIF_CFG0          0x22b4
#घोषणा MT6358_AFE_ADDA_MTKAIF_RX_CFG0       0x22b6
#घोषणा MT6358_AFE_ADDA_MTKAIF_RX_CFG1       0x22b8
#घोषणा MT6358_AFE_ADDA_MTKAIF_RX_CFG2       0x22ba
#घोषणा MT6358_AFE_ADDA_MTKAIF_RX_CFG3       0x22bc
#घोषणा MT6358_AFE_ADDA_MTKAIF_TX_CFG1       0x22be
#घोषणा MT6358_AFE_SGEN_CFG0                 0x22c0
#घोषणा MT6358_AFE_SGEN_CFG1                 0x22c2
#घोषणा MT6358_AFE_ADC_ASYNC_FIFO_CFG        0x22c4
#घोषणा MT6358_AFE_DCCLK_CFG0                0x22c6
#घोषणा MT6358_AFE_DCCLK_CFG1                0x22c8
#घोषणा MT6358_AUDIO_DIG_CFG                 0x22ca
#घोषणा MT6358_AFE_AUD_PAD_TOP               0x22cc
#घोषणा MT6358_AFE_AUD_PAD_TOP_MON           0x22ce
#घोषणा MT6358_AFE_AUD_PAD_TOP_MON1          0x22d0
#घोषणा MT6358_AFE_DL_NLE_CFG                0x22d2
#घोषणा MT6358_AFE_DL_NLE_MON                0x22d4
#घोषणा MT6358_AFE_CG_EN_MON                 0x22d6
#घोषणा MT6358_AUDIO_DIG_2ND_DSN_ID          0x2300
#घोषणा MT6358_AUDIO_DIG_2ND_DSN_REV0        0x2302
#घोषणा MT6358_AUDIO_DIG_2ND_DSN_DBI         0x2304
#घोषणा MT6358_AUDIO_DIG_2ND_DSN_DXI         0x2306
#घोषणा MT6358_AFE_PMIC_NEWIF_CFG3           0x2308
#घोषणा MT6358_AFE_VOW_TOP                   0x230a
#घोषणा MT6358_AFE_VOW_CFG0                  0x230c
#घोषणा MT6358_AFE_VOW_CFG1                  0x230e
#घोषणा MT6358_AFE_VOW_CFG2                  0x2310
#घोषणा MT6358_AFE_VOW_CFG3                  0x2312
#घोषणा MT6358_AFE_VOW_CFG4                  0x2314
#घोषणा MT6358_AFE_VOW_CFG5                  0x2316
#घोषणा MT6358_AFE_VOW_CFG6                  0x2318
#घोषणा MT6358_AFE_VOW_MON0                  0x231a
#घोषणा MT6358_AFE_VOW_MON1                  0x231c
#घोषणा MT6358_AFE_VOW_MON2                  0x231e
#घोषणा MT6358_AFE_VOW_MON3                  0x2320
#घोषणा MT6358_AFE_VOW_MON4                  0x2322
#घोषणा MT6358_AFE_VOW_MON5                  0x2324
#घोषणा MT6358_AFE_VOW_SN_INI_CFG            0x2326
#घोषणा MT6358_AFE_VOW_TGEN_CFG0             0x2328
#घोषणा MT6358_AFE_VOW_POSDIV_CFG0           0x232a
#घोषणा MT6358_AFE_VOW_HPF_CFG0              0x232c
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG0         0x232e
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG1         0x2330
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG2         0x2332
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG3         0x2334
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG4         0x2336
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG5         0x2338
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG6         0x233a
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG7         0x233c
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG8         0x233e
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG9         0x2340
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG10        0x2342
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG11        0x2344
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG12        0x2346
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG13        0x2348
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG14        0x234a
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG15        0x234c
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG16        0x234e
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG17        0x2350
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG18        0x2352
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG19        0x2354
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG20        0x2356
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG21        0x2358
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG22        0x235a
#घोषणा MT6358_AFE_VOW_PERIODIC_CFG23        0x235c
#घोषणा MT6358_AFE_VOW_PERIODIC_MON0         0x235e
#घोषणा MT6358_AFE_VOW_PERIODIC_MON1         0x2360
#घोषणा MT6358_AUDENC_DSN_ID                 0x2380
#घोषणा MT6358_AUDENC_DSN_REV0               0x2382
#घोषणा MT6358_AUDENC_DSN_DBI                0x2384
#घोषणा MT6358_AUDENC_DSN_FPI                0x2386
#घोषणा MT6358_AUDENC_ANA_CON0               0x2388
#घोषणा MT6358_AUDENC_ANA_CON1               0x238a
#घोषणा MT6358_AUDENC_ANA_CON2               0x238c
#घोषणा MT6358_AUDENC_ANA_CON3               0x238e
#घोषणा MT6358_AUDENC_ANA_CON4               0x2390
#घोषणा MT6358_AUDENC_ANA_CON5               0x2392
#घोषणा MT6358_AUDENC_ANA_CON6               0x2394
#घोषणा MT6358_AUDENC_ANA_CON7               0x2396
#घोषणा MT6358_AUDENC_ANA_CON8               0x2398
#घोषणा MT6358_AUDENC_ANA_CON9               0x239a
#घोषणा MT6358_AUDENC_ANA_CON10              0x239c
#घोषणा MT6358_AUDENC_ANA_CON11              0x239e
#घोषणा MT6358_AUDENC_ANA_CON12              0x23a0
#घोषणा MT6358_AUDDEC_DSN_ID                 0x2400
#घोषणा MT6358_AUDDEC_DSN_REV0               0x2402
#घोषणा MT6358_AUDDEC_DSN_DBI                0x2404
#घोषणा MT6358_AUDDEC_DSN_FPI                0x2406
#घोषणा MT6358_AUDDEC_ANA_CON0               0x2408
#घोषणा MT6358_AUDDEC_ANA_CON1               0x240a
#घोषणा MT6358_AUDDEC_ANA_CON2               0x240c
#घोषणा MT6358_AUDDEC_ANA_CON3               0x240e
#घोषणा MT6358_AUDDEC_ANA_CON4               0x2410
#घोषणा MT6358_AUDDEC_ANA_CON5               0x2412
#घोषणा MT6358_AUDDEC_ANA_CON6               0x2414
#घोषणा MT6358_AUDDEC_ANA_CON7               0x2416
#घोषणा MT6358_AUDDEC_ANA_CON8               0x2418
#घोषणा MT6358_AUDDEC_ANA_CON9               0x241a
#घोषणा MT6358_AUDDEC_ANA_CON10              0x241c
#घोषणा MT6358_AUDDEC_ANA_CON11              0x241e
#घोषणा MT6358_AUDDEC_ANA_CON12              0x2420
#घोषणा MT6358_AUDDEC_ANA_CON13              0x2422
#घोषणा MT6358_AUDDEC_ANA_CON14              0x2424
#घोषणा MT6358_AUDDEC_ANA_CON15              0x2426
#घोषणा MT6358_AUDDEC_ELR_NUM                0x2428
#घोषणा MT6358_AUDDEC_ELR_0                  0x242a
#घोषणा MT6358_AUDZCD_DSN_ID                 0x2480
#घोषणा MT6358_AUDZCD_DSN_REV0               0x2482
#घोषणा MT6358_AUDZCD_DSN_DBI                0x2484
#घोषणा MT6358_AUDZCD_DSN_FPI                0x2486
#घोषणा MT6358_ZCD_CON0                      0x2488
#घोषणा MT6358_ZCD_CON1                      0x248a
#घोषणा MT6358_ZCD_CON2                      0x248c
#घोषणा MT6358_ZCD_CON3                      0x248e
#घोषणा MT6358_ZCD_CON4                      0x2490
#घोषणा MT6358_ZCD_CON5                      0x2492
#घोषणा MT6358_ACCDET_CON13                  0x2522

#घोषणा MT6358_MAX_REGISTER MT6358_ZCD_CON5

क्रमागत अणु
	MT6358_MTKAIF_PROTOCOL_1 = 0,
	MT6358_MTKAIF_PROTOCOL_2,
	MT6358_MTKAIF_PROTOCOL_2_CLK_P2,
पूर्ण;

/* set only during init */
पूर्णांक mt6358_set_mtkaअगर_protocol(काष्ठा snd_soc_component *cmpnt,
			       पूर्णांक mtkaअगर_protocol);
पूर्णांक mt6358_mtkaअगर_calibration_enable(काष्ठा snd_soc_component *cmpnt);
पूर्णांक mt6358_mtkaअगर_calibration_disable(काष्ठा snd_soc_component *cmpnt);
पूर्णांक mt6358_set_mtkaअगर_calibration_phase(काष्ठा snd_soc_component *cmpnt,
					पूर्णांक phase_1, पूर्णांक phase_2);
#पूर्ण_अगर /* __MT6358_H__ */
