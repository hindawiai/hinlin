<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mt6351.h  --  mt6351 ALSA SoC audio codec driver
 *
 * Copyright (c) 2018 MediaTek Inc.
 * Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>
 */

#अगर_अघोषित __MT6351_H__
#घोषणा __MT6351_H__

#घोषणा MT6351_AFE_UL_DL_CON0               (0x2000 + 0x0000)
#घोषणा MT6351_AFE_DL_SRC2_CON0_H           (0x2000 + 0x0002)
#घोषणा MT6351_AFE_DL_SRC2_CON0_L           (0x2000 + 0x0004)
#घोषणा MT6351_AFE_DL_SDM_CON0              (0x2000 + 0x0006)
#घोषणा MT6351_AFE_DL_SDM_CON1              (0x2000 + 0x0008)
#घोषणा MT6351_AFE_UL_SRC_CON0_H            (0x2000 + 0x000a)
#घोषणा MT6351_AFE_UL_SRC_CON0_L            (0x2000 + 0x000c)
#घोषणा MT6351_AFE_UL_SRC_CON1_H            (0x2000 + 0x000e)
#घोषणा MT6351_AFE_UL_SRC_CON1_L            (0x2000 + 0x0010)
#घोषणा MT6351_AFE_TOP_CON0                 (0x2000 + 0x0012)
#घोषणा MT6351_AUDIO_TOP_CON0               (0x2000 + 0x0014)
#घोषणा MT6351_AFE_DL_SRC_MON0              (0x2000 + 0x0016)
#घोषणा MT6351_AFE_DL_SDM_TEST0             (0x2000 + 0x0018)
#घोषणा MT6351_AFE_MON_DEBUG0               (0x2000 + 0x001a)
#घोषणा MT6351_AFUNC_AUD_CON0               (0x2000 + 0x001c)
#घोषणा MT6351_AFUNC_AUD_CON1               (0x2000 + 0x001e)
#घोषणा MT6351_AFUNC_AUD_CON2               (0x2000 + 0x0020)
#घोषणा MT6351_AFUNC_AUD_CON3               (0x2000 + 0x0022)
#घोषणा MT6351_AFUNC_AUD_CON4               (0x2000 + 0x0024)
#घोषणा MT6351_AFUNC_AUD_MON0               (0x2000 + 0x0026)
#घोषणा MT6351_AFUNC_AUD_MON1               (0x2000 + 0x0028)
#घोषणा MT6351_AFE_UP8X_FIFO_CFG0           (0x2000 + 0x002c)
#घोषणा MT6351_AFE_UP8X_FIFO_LOG_MON0       (0x2000 + 0x002e)
#घोषणा MT6351_AFE_UP8X_FIFO_LOG_MON1       (0x2000 + 0x0030)
#घोषणा MT6351_AFE_DL_DC_COMP_CFG0          (0x2000 + 0x0032)
#घोषणा MT6351_AFE_DL_DC_COMP_CFG1          (0x2000 + 0x0034)
#घोषणा MT6351_AFE_DL_DC_COMP_CFG2          (0x2000 + 0x0036)
#घोषणा MT6351_AFE_PMIC_NEWIF_CFG0          (0x2000 + 0x0038)
#घोषणा MT6351_AFE_PMIC_NEWIF_CFG1          (0x2000 + 0x003a)
#घोषणा MT6351_AFE_PMIC_NEWIF_CFG2          (0x2000 + 0x003c)
#घोषणा MT6351_AFE_PMIC_NEWIF_CFG3          (0x2000 + 0x003e)
#घोषणा MT6351_AFE_SGEN_CFG0                (0x2000 + 0x0040)
#घोषणा MT6351_AFE_SGEN_CFG1                (0x2000 + 0x0042)
#घोषणा MT6351_AFE_ADDA2_UP8X_FIFO_LOG_MON0 (0x2000 + 0x004c)
#घोषणा MT6351_AFE_ADDA2_UP8X_FIFO_LOG_MON1 (0x2000 + 0x004e)
#घोषणा MT6351_AFE_ADDA2_PMIC_NEWIF_CFG0    (0x2000 + 0x0050)
#घोषणा MT6351_AFE_ADDA2_PMIC_NEWIF_CFG1    (0x2000 + 0x0052)
#घोषणा MT6351_AFE_ADDA2_PMIC_NEWIF_CFG2    (0x2000 + 0x0054)
#घोषणा MT6351_AFE_DCCLK_CFG0               (0x2000 + 0x0090)
#घोषणा MT6351_AFE_DCCLK_CFG1               (0x2000 + 0x0092)
#घोषणा MT6351_AFE_HPANC_CFG0               (0x2000 + 0x0094)
#घोषणा MT6351_AFE_NCP_CFG0                 (0x2000 + 0x0096)
#घोषणा MT6351_AFE_NCP_CFG1                 (0x2000 + 0x0098)

#घोषणा MT6351_TOP_CKPDN_CON0      0x023A
#घोषणा MT6351_TOP_CKPDN_CON0_SET  0x023C
#घोषणा MT6351_TOP_CKPDN_CON0_CLR  0x023E

#घोषणा MT6351_TOP_CLKSQ           0x029A
#घोषणा MT6351_TOP_CLKSQ_SET       0x029C
#घोषणा MT6351_TOP_CLKSQ_CLR       0x029E

#घोषणा MT6351_ZCD_CON0            0x0800
#घोषणा MT6351_ZCD_CON1            0x0802
#घोषणा MT6351_ZCD_CON2            0x0804
#घोषणा MT6351_ZCD_CON3            0x0806
#घोषणा MT6351_ZCD_CON4            0x0808
#घोषणा MT6351_ZCD_CON5            0x080A

#घोषणा MT6351_LDO_VA18_CON0       0x0A00
#घोषणा MT6351_LDO_VA18_CON1       0x0A02
#घोषणा MT6351_LDO_VUSB33_CON0     0x0A16
#घोषणा MT6351_LDO_VUSB33_CON1     0x0A18

#घोषणा MT6351_AUDDEC_ANA_CON0     0x0CF2
#घोषणा MT6351_AUDDEC_ANA_CON1     0x0CF4
#घोषणा MT6351_AUDDEC_ANA_CON2     0x0CF6
#घोषणा MT6351_AUDDEC_ANA_CON3     0x0CF8
#घोषणा MT6351_AUDDEC_ANA_CON4     0x0CFA
#घोषणा MT6351_AUDDEC_ANA_CON5     0x0CFC
#घोषणा MT6351_AUDDEC_ANA_CON6     0x0CFE
#घोषणा MT6351_AUDDEC_ANA_CON7     0x0D00
#घोषणा MT6351_AUDDEC_ANA_CON8     0x0D02
#घोषणा MT6351_AUDDEC_ANA_CON9     0x0D04
#घोषणा MT6351_AUDDEC_ANA_CON10    0x0D06

#घोषणा MT6351_AUDENC_ANA_CON0     0x0D08
#घोषणा MT6351_AUDENC_ANA_CON1     0x0D0A
#घोषणा MT6351_AUDENC_ANA_CON2     0x0D0C
#घोषणा MT6351_AUDENC_ANA_CON3     0x0D0E
#घोषणा MT6351_AUDENC_ANA_CON4     0x0D10
#घोषणा MT6351_AUDENC_ANA_CON5     0x0D12
#घोषणा MT6351_AUDENC_ANA_CON6     0x0D14
#घोषणा MT6351_AUDENC_ANA_CON7     0x0D16
#घोषणा MT6351_AUDENC_ANA_CON8     0x0D18
#घोषणा MT6351_AUDENC_ANA_CON9     0x0D1A
#घोषणा MT6351_AUDENC_ANA_CON10    0x0D1C
#घोषणा MT6351_AUDENC_ANA_CON11    0x0D1E
#घोषणा MT6351_AUDENC_ANA_CON12    0x0D20
#घोषणा MT6351_AUDENC_ANA_CON13    0x0D22
#घोषणा MT6351_AUDENC_ANA_CON14    0x0D24
#घोषणा MT6351_AUDENC_ANA_CON15    0x0D26
#घोषणा MT6351_AUDENC_ANA_CON16    0x0D28
#पूर्ण_अगर
