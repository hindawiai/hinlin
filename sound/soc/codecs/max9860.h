<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Driver क्रम the MAX9860 Mono Audio Voice Codec
 *
 * Author: Peter Rosin <peda@axentia.s>
 *         Copyright 2016 Axentia Technologies
 */

#अगर_अघोषित _SND_SOC_MAX9860
#घोषणा _SND_SOC_MAX9860

#घोषणा MAX9860_INTRSTATUS   0x00
#घोषणा MAX9860_MICREADBACK  0x01
#घोषणा MAX9860_INTEN        0x02
#घोषणा MAX9860_SYSCLK       0x03
#घोषणा MAX9860_AUDIOCLKHIGH 0x04
#घोषणा MAX9860_AUDIOCLKLOW  0x05
#घोषणा MAX9860_IFC1A        0x06
#घोषणा MAX9860_IFC1B        0x07
#घोषणा MAX9860_VOICEFLTR    0x08
#घोषणा MAX9860_DACATTN      0x09
#घोषणा MAX9860_ADCLEVEL     0x0a
#घोषणा MAX9860_DACGAIN      0x0b
#घोषणा MAX9860_MICGAIN      0x0c
#घोषणा MAX9860_RESERVED     0x0d
#घोषणा MAX9860_MICADC       0x0e
#घोषणा MAX9860_NOISEGATE    0x0f
#घोषणा MAX9860_PWRMAN       0x10
#घोषणा MAX9860_REVISION     0xff

#घोषणा MAX9860_MAX_REGISTER 0xff

/* INTRSTATUS */
#घोषणा MAX9860_CLD          0x80
#घोषणा MAX9860_SLD          0x40
#घोषणा MAX9860_ULK          0x20

/* MICREADBACK */
#घोषणा MAX9860_NG           0xe0
#घोषणा MAX9860_AGC          0x1f

/* INTEN */
#घोषणा MAX9860_ICLD         0x80
#घोषणा MAX9860_ISLD         0x40
#घोषणा MAX9860_IULK         0x20

/* SYSCLK */
#घोषणा MAX9860_PSCLK        0x30
#घोषणा MAX9860_PSCLK_OFF    0x00
#घोषणा MAX9860_PSCLK_SHIFT  4
#घोषणा MAX9860_FREQ         0x06
#घोषणा MAX9860_FREQ_NORMAL  0x00
#घोषणा MAX9860_FREQ_12MHZ   0x02
#घोषणा MAX9860_FREQ_13MHZ   0x04
#घोषणा MAX9860_FREQ_19_2MHZ 0x06
#घोषणा MAX9860_16KHZ        0x01

/* AUDIOCLKHIGH */
#घोषणा MAX9860_PLL          0x80
#घोषणा MAX9860_NHI          0x7f

/* AUDIOCLKLOW */
#घोषणा MAX9860_NLO          0xff

/* IFC1A */
#घोषणा MAX9860_MASTER       0x80
#घोषणा MAX9860_WCI          0x40
#घोषणा MAX9860_DBCI         0x20
#घोषणा MAX9860_DDLY         0x10
#घोषणा MAX9860_HIZ          0x08
#घोषणा MAX9860_TDM          0x04

/* IFC1B */
#घोषणा MAX9860_ABCI         0x20
#घोषणा MAX9860_ADLY         0x10
#घोषणा MAX9860_ST           0x08
#घोषणा MAX9860_BSEL         0x07
#घोषणा MAX9860_BSEL_OFF     0x00
#घोषणा MAX9860_BSEL_64X     0x01
#घोषणा MAX9860_BSEL_48X     0x02
#घोषणा MAX9860_BSEL_PCLK_2  0x04
#घोषणा MAX9860_BSEL_PCLK_4  0x05
#घोषणा MAX9860_BSEL_PCLK_8  0x06
#घोषणा MAX9860_BSEL_PCLK_16 0x07

/* VOICEFLTR */
#घोषणा MAX9860_AVFLT        0xf0
#घोषणा MAX9860_AVFLT_SHIFT  4
#घोषणा MAX9860_AVFLT_COUNT  6
#घोषणा MAX9860_DVFLT        0x0f
#घोषणा MAX9860_DVFLT_SHIFT  0
#घोषणा MAX9860_DVFLT_COUNT  6

/* DACATTN */
#घोषणा MAX9860_DVA          0xfe
#घोषणा MAX9860_DVA_SHIFT    1
#घोषणा MAX9860_DVA_MUTE     0x5e

/* ADCLEVEL */
#घोषणा MAX9860_ADCRL        0xf0
#घोषणा MAX9860_ADCRL_SHIFT  4
#घोषणा MAX9860_ADCLL        0x0f
#घोषणा MAX9860_ADCLL_SHIFT  0
#घोषणा MAX9860_ADCxL_MIN    15

/* DACGAIN */
#घोषणा MAX9860_DVG          0x60
#घोषणा MAX9860_DVG_SHIFT    5
#घोषणा MAX9860_DVG_MAX      3
#घोषणा MAX9860_DVST         0x1f
#घोषणा MAX9860_DVST_SHIFT   0
#घोषणा MAX9860_DVST_MIN     31

/* MICGAIN */
#घोषणा MAX9860_PAM          0x60
#घोषणा MAX9860_PAM_SHIFT    5
#घोषणा MAX9860_PAM_MAX      3
#घोषणा MAX9860_PGAM         0x1f
#घोषणा MAX9860_PGAM_SHIFT   0
#घोषणा MAX9860_PGAM_MIN     20

/* MICADC */
#घोषणा MAX9860_AGCSRC       0x80
#घोषणा MAX9860_AGCSRC_SHIFT 7
#घोषणा MAX9860_AGCSRC_COUNT 2
#घोषणा MAX9860_AGCRLS       0x70
#घोषणा MAX9860_AGCRLS_SHIFT 4
#घोषणा MAX9860_AGCRLS_COUNT 8
#घोषणा MAX9860_AGCATK       0x0c
#घोषणा MAX9860_AGCATK_SHIFT 2
#घोषणा MAX9860_AGCATK_COUNT 4
#घोषणा MAX9860_AGCHLD       0x03
#घोषणा MAX9860_AGCHLD_OFF   0x00
#घोषणा MAX9860_AGCHLD_SHIFT 0
#घोषणा MAX9860_AGCHLD_COUNT 4

/* NOISEGATE */
#घोषणा MAX9860_ANTH         0xf0
#घोषणा MAX9860_ANTH_SHIFT   4
#घोषणा MAX9860_ANTH_MAX     15
#घोषणा MAX9860_AGCTH        0x0f
#घोषणा MAX9860_AGCTH_SHIFT  0
#घोषणा MAX9860_AGCTH_MIN    15

/* PWRMAN */
#घोषणा MAX9860_SHDN         0x80
#घोषणा MAX9860_DACEN        0x08
#घोषणा MAX9860_DACEN_SHIFT  3
#घोषणा MAX9860_ADCLEN       0x02
#घोषणा MAX9860_ADCLEN_SHIFT 1
#घोषणा MAX9860_ADCREN       0x01
#घोषणा MAX9860_ADCREN_SHIFT 0

#पूर्ण_अगर /* _SND_SOC_MAX9860 */
