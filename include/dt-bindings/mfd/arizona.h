<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Device Tree defines क्रम Arizona devices
 *
 * Copyright 2015 Cirrus Logic Inc.
 *
 * Author: Charles Keepax <ckeepax@खोलोsource.wolfsonmicro.com>
 */

#अगर_अघोषित _DT_BINDINGS_MFD_ARIZONA_H
#घोषणा _DT_BINDINGS_MFD_ARIZONA_H

/* GPIO Function Definitions */
#घोषणा ARIZONA_GP_FN_TXLRCLK                    0x00
#घोषणा ARIZONA_GP_FN_GPIO                       0x01
#घोषणा ARIZONA_GP_FN_IRQ1                       0x02
#घोषणा ARIZONA_GP_FN_IRQ2                       0x03
#घोषणा ARIZONA_GP_FN_OPCLK                      0x04
#घोषणा ARIZONA_GP_FN_FLL1_OUT                   0x05
#घोषणा ARIZONA_GP_FN_FLL2_OUT                   0x06
#घोषणा ARIZONA_GP_FN_PWM1                       0x08
#घोषणा ARIZONA_GP_FN_PWM2                       0x09
#घोषणा ARIZONA_GP_FN_SYSCLK_UNDERCLOCKED        0x0A
#घोषणा ARIZONA_GP_FN_ASYNCCLK_UNDERCLOCKED      0x0B
#घोषणा ARIZONA_GP_FN_FLL1_LOCK                  0x0C
#घोषणा ARIZONA_GP_FN_FLL2_LOCK                  0x0D
#घोषणा ARIZONA_GP_FN_FLL1_CLOCK_OK              0x0F
#घोषणा ARIZONA_GP_FN_FLL2_CLOCK_OK              0x10
#घोषणा ARIZONA_GP_FN_HEADPHONE_DET              0x12
#घोषणा ARIZONA_GP_FN_MIC_DET                    0x13
#घोषणा ARIZONA_GP_FN_WSEQ_STATUS                0x15
#घोषणा ARIZONA_GP_FN_CIF_ADDRESS_ERROR          0x16
#घोषणा ARIZONA_GP_FN_ASRC1_LOCK                 0x1A
#घोषणा ARIZONA_GP_FN_ASRC2_LOCK                 0x1B
#घोषणा ARIZONA_GP_FN_ASRC_CONFIG_ERROR          0x1C
#घोषणा ARIZONA_GP_FN_DRC1_SIGNAL_DETECT         0x1D
#घोषणा ARIZONA_GP_FN_DRC1_ANTICLIP              0x1E
#घोषणा ARIZONA_GP_FN_DRC1_DECAY                 0x1F
#घोषणा ARIZONA_GP_FN_DRC1_NOISE                 0x20
#घोषणा ARIZONA_GP_FN_DRC1_QUICK_RELEASE         0x21
#घोषणा ARIZONA_GP_FN_DRC2_SIGNAL_DETECT         0x22
#घोषणा ARIZONA_GP_FN_DRC2_ANTICLIP              0x23
#घोषणा ARIZONA_GP_FN_DRC2_DECAY                 0x24
#घोषणा ARIZONA_GP_FN_DRC2_NOISE                 0x25
#घोषणा ARIZONA_GP_FN_DRC2_QUICK_RELEASE         0x26
#घोषणा ARIZONA_GP_FN_MIXER_DROPPED_SAMPLE       0x27
#घोषणा ARIZONA_GP_FN_AIF1_CONFIG_ERROR          0x28
#घोषणा ARIZONA_GP_FN_AIF2_CONFIG_ERROR          0x29
#घोषणा ARIZONA_GP_FN_AIF3_CONFIG_ERROR          0x2A
#घोषणा ARIZONA_GP_FN_SPK_TEMP_SHUTDOWN          0x2B
#घोषणा ARIZONA_GP_FN_SPK_TEMP_WARNING           0x2C
#घोषणा ARIZONA_GP_FN_UNDERCLOCKED               0x2D
#घोषणा ARIZONA_GP_FN_OVERCLOCKED                0x2E
#घोषणा ARIZONA_GP_FN_DSP_IRQ1                   0x35
#घोषणा ARIZONA_GP_FN_DSP_IRQ2                   0x36
#घोषणा ARIZONA_GP_FN_ASYNC_OPCLK                0x3D
#घोषणा ARIZONA_GP_FN_BOOT_DONE                  0x44
#घोषणा ARIZONA_GP_FN_DSP1_RAM_READY             0x45
#घोषणा ARIZONA_GP_FN_SYSCLK_ENA_STATUS          0x4B
#घोषणा ARIZONA_GP_FN_ASYNCCLK_ENA_STATUS        0x4C

/* GPIO Configuration Bits */
#घोषणा ARIZONA_GPN_सूची                          0x8000
#घोषणा ARIZONA_GPN_PU                           0x4000
#घोषणा ARIZONA_GPN_PD                           0x2000
#घोषणा ARIZONA_GPN_LVL                          0x0800
#घोषणा ARIZONA_GPN_POL                          0x0400
#घोषणा ARIZONA_GPN_OP_CFG                       0x0200
#घोषणा ARIZONA_GPN_DB                           0x0100

/* Provide some defines क्रम the most common configs */
#घोषणा ARIZONA_GP_DEFAULT             0xffffffff
#घोषणा ARIZONA_GP_OUTPUT              (ARIZONA_GP_FN_GPIO)
#घोषणा ARIZONA_GP_INPUT               (ARIZONA_GP_FN_GPIO | \
					ARIZONA_GPN_सूची)

#घोषणा ARIZONA_32KZ_MCLK1 1
#घोषणा ARIZONA_32KZ_MCLK2 2
#घोषणा ARIZONA_32KZ_NONE  3

#घोषणा ARIZONA_DMIC_MICVDD   0
#घोषणा ARIZONA_DMIC_MICBIAS1 1
#घोषणा ARIZONA_DMIC_MICBIAS2 2
#घोषणा ARIZONA_DMIC_MICBIAS3 3

#घोषणा ARIZONA_INMODE_DIFF 0
#घोषणा ARIZONA_INMODE_SE   1
#घोषणा ARIZONA_INMODE_DMIC 2

#घोषणा ARIZONA_MICD_TIME_CONTINUOUS                 0
#घोषणा ARIZONA_MICD_TIME_250US                      1
#घोषणा ARIZONA_MICD_TIME_500US                      2
#घोषणा ARIZONA_MICD_TIME_1MS                        3
#घोषणा ARIZONA_MICD_TIME_2MS                        4
#घोषणा ARIZONA_MICD_TIME_4MS                        5
#घोषणा ARIZONA_MICD_TIME_8MS                        6
#घोषणा ARIZONA_MICD_TIME_16MS                       7
#घोषणा ARIZONA_MICD_TIME_32MS                       8
#घोषणा ARIZONA_MICD_TIME_64MS                       9
#घोषणा ARIZONA_MICD_TIME_128MS                      10
#घोषणा ARIZONA_MICD_TIME_256MS                      11
#घोषणा ARIZONA_MICD_TIME_512MS                      12

#घोषणा ARIZONA_ACCDET_MODE_MIC 0
#घोषणा ARIZONA_ACCDET_MODE_HPL 1
#घोषणा ARIZONA_ACCDET_MODE_HPR 2
#घोषणा ARIZONA_ACCDET_MODE_HPM 4
#घोषणा ARIZONA_ACCDET_MODE_ADC 7

#घोषणा ARIZONA_GPSW_OPEN           0
#घोषणा ARIZONA_GPSW_CLOSED         1
#घोषणा ARIZONA_GPSW_CLAMP_ENABLED  2
#घोषणा ARIZONA_GPSW_CLAMP_DISABLED 3

#पूर्ण_अगर
