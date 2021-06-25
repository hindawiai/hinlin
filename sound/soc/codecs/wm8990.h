<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * wm8990.h  --  audio driver क्रम WM8990
 *
 * Copyright 2007 Wolfson Microelectronics PLC.
 * Author: Graeme Gregory
 *         graeme.gregory@wolfsonmicro.com or linux@wolfsonmicro.com
 */

#अगर_अघोषित __WM8990REGISTERDEFS_H__
#घोषणा __WM8990REGISTERDEFS_H__

/*
 * Register values.
 */
#घोषणा WM8990_RESET                            0x00
#घोषणा WM8990_POWER_MANAGEMENT_1               0x01
#घोषणा WM8990_POWER_MANAGEMENT_2               0x02
#घोषणा WM8990_POWER_MANAGEMENT_3               0x03
#घोषणा WM8990_AUDIO_INTERFACE_1                0x04
#घोषणा WM8990_AUDIO_INTERFACE_2                0x05
#घोषणा WM8990_CLOCKING_1                       0x06
#घोषणा WM8990_CLOCKING_2                       0x07
#घोषणा WM8990_AUDIO_INTERFACE_3                0x08
#घोषणा WM8990_AUDIO_INTERFACE_4                0x09
#घोषणा WM8990_DAC_CTRL                         0x0A
#घोषणा WM8990_LEFT_DAC_DIGITAL_VOLUME          0x0B
#घोषणा WM8990_RIGHT_DAC_DIGITAL_VOLUME         0x0C
#घोषणा WM8990_DIGITAL_SIDE_TONE                0x0D
#घोषणा WM8990_ADC_CTRL                         0x0E
#घोषणा WM8990_LEFT_ADC_DIGITAL_VOLUME          0x0F
#घोषणा WM8990_RIGHT_ADC_DIGITAL_VOLUME         0x10
#घोषणा WM8990_GPIO_CTRL_1                      0x12
#घोषणा WM8990_GPIO1_GPIO2                      0x13
#घोषणा WM8990_GPIO3_GPIO4                      0x14
#घोषणा WM8990_GPIO5_GPIO6                      0x15
#घोषणा WM8990_GPIOCTRL_2                       0x16
#घोषणा WM8990_GPIO_POL                         0x17
#घोषणा WM8990_LEFT_LINE_INPUT_1_2_VOLUME       0x18
#घोषणा WM8990_LEFT_LINE_INPUT_3_4_VOLUME       0x19
#घोषणा WM8990_RIGHT_LINE_INPUT_1_2_VOLUME      0x1A
#घोषणा WM8990_RIGHT_LINE_INPUT_3_4_VOLUME      0x1B
#घोषणा WM8990_LEFT_OUTPUT_VOLUME               0x1C
#घोषणा WM8990_RIGHT_OUTPUT_VOLUME              0x1D
#घोषणा WM8990_LINE_OUTPUTS_VOLUME              0x1E
#घोषणा WM8990_OUT3_4_VOLUME                    0x1F
#घोषणा WM8990_LEFT_OPGA_VOLUME                 0x20
#घोषणा WM8990_RIGHT_OPGA_VOLUME                0x21
#घोषणा WM8990_SPEAKER_VOLUME                   0x22
#घोषणा WM8990_CLASSD1                          0x23
#घोषणा WM8990_CLASSD3                          0x25
#घोषणा WM8990_CLASSD4                          0x26
#घोषणा WM8990_INPUT_MIXER1                     0x27
#घोषणा WM8990_INPUT_MIXER2                     0x28
#घोषणा WM8990_INPUT_MIXER3                     0x29
#घोषणा WM8990_INPUT_MIXER4                     0x2A
#घोषणा WM8990_INPUT_MIXER5                     0x2B
#घोषणा WM8990_INPUT_MIXER6                     0x2C
#घोषणा WM8990_OUTPUT_MIXER1                    0x2D
#घोषणा WM8990_OUTPUT_MIXER2                    0x2E
#घोषणा WM8990_OUTPUT_MIXER3                    0x2F
#घोषणा WM8990_OUTPUT_MIXER4                    0x30
#घोषणा WM8990_OUTPUT_MIXER5                    0x31
#घोषणा WM8990_OUTPUT_MIXER6                    0x32
#घोषणा WM8990_OUT3_4_MIXER                     0x33
#घोषणा WM8990_LINE_MIXER1                      0x34
#घोषणा WM8990_LINE_MIXER2                      0x35
#घोषणा WM8990_SPEAKER_MIXER                    0x36
#घोषणा WM8990_ADDITIONAL_CONTROL               0x37
#घोषणा WM8990_ANTIPOP1                         0x38
#घोषणा WM8990_ANTIPOP2                         0x39
#घोषणा WM8990_MICBIAS                          0x3A
#घोषणा WM8990_PLL1                             0x3C
#घोषणा WM8990_PLL2                             0x3D
#घोषणा WM8990_PLL3                             0x3E

#घोषणा WM8990_EXT_ACCESS_ENA			0x75
#घोषणा WM8990_EXT_CTL1				0x7a

/*
 * Field Definitions.
 */

/*
 * R0 (0x00) - Reset
 */
#घोषणा WM8990_SW_RESET_CHIP_ID_MASK            0xFFFF  /* SW_RESET_CHIP_ID */

/*
 * R1 (0x01) - Power Management (1)
 */
#घोषणा WM8990_SPK_ENA                          0x1000  /* SPK_ENA */
#घोषणा WM8990_SPK_ENA_BIT			12
#घोषणा WM8990_OUT3_ENA                         0x0800  /* OUT3_ENA */
#घोषणा WM8990_OUT3_ENA_BIT			11
#घोषणा WM8990_OUT4_ENA                         0x0400  /* OUT4_ENA */
#घोषणा WM8990_OUT4_ENA_BIT			10
#घोषणा WM8990_LOUT_ENA                         0x0200  /* LOUT_ENA */
#घोषणा WM8990_LOUT_ENA_BIT			9
#घोषणा WM8990_ROUT_ENA                         0x0100  /* ROUT_ENA */
#घोषणा WM8990_ROUT_ENA_BIT			8
#घोषणा WM8990_MICBIAS_ENA                      0x0010  /* MICBIAS_ENA */
#घोषणा WM8990_MICBIAS_ENA_BIT			4
#घोषणा WM8990_VMID_MODE_MASK                   0x0006  /* VMID_MODE - [2:1] */
#घोषणा WM8990_VREF_ENA                         0x0001  /* VREF_ENA */
#घोषणा WM8990_VREF_ENA_BIT			0

/*
 * R2 (0x02) - Power Management (2)
 */
#घोषणा WM8990_PLL_ENA                          0x8000  /* PLL_ENA */
#घोषणा WM8990_PLL_ENA_BIT			15
#घोषणा WM8990_TSHUT_ENA                        0x4000  /* TSHUT_ENA */
#घोषणा WM8990_TSHUT_ENA_BIT			14
#घोषणा WM8990_TSHUT_OPDIS                      0x2000  /* TSHUT_OPDIS */
#घोषणा WM8990_TSHUT_OPDIS_BIT			13
#घोषणा WM8990_OPCLK_ENA                        0x0800  /* OPCLK_ENA */
#घोषणा WM8990_OPCLK_ENA_BIT			11
#घोषणा WM8990_AINL_ENA                         0x0200  /* AINL_ENA */
#घोषणा WM8990_AINL_ENA_BIT			9
#घोषणा WM8990_AINR_ENA                         0x0100  /* AINR_ENA */
#घोषणा WM8990_AINR_ENA_BIT			8
#घोषणा WM8990_LIN34_ENA                        0x0080  /* LIN34_ENA */
#घोषणा WM8990_LIN34_ENA_BIT			7
#घोषणा WM8990_LIN12_ENA                        0x0040  /* LIN12_ENA */
#घोषणा WM8990_LIN12_ENA_BIT			6
#घोषणा WM8990_RIN34_ENA                        0x0020  /* RIN34_ENA */
#घोषणा WM8990_RIN34_ENA_BIT			5
#घोषणा WM8990_RIN12_ENA                        0x0010  /* RIN12_ENA */
#घोषणा WM8990_RIN12_ENA_BIT			4
#घोषणा WM8990_ADCL_ENA                         0x0002  /* ADCL_ENA */
#घोषणा WM8990_ADCL_ENA_BIT			1
#घोषणा WM8990_ADCR_ENA                         0x0001  /* ADCR_ENA */
#घोषणा WM8990_ADCR_ENA_BIT			0

/*
 * R3 (0x03) - Power Management (3)
 */
#घोषणा WM8990_LON_ENA                          0x2000  /* LON_ENA */
#घोषणा WM8990_LON_ENA_BIT			13
#घोषणा WM8990_LOP_ENA                          0x1000  /* LOP_ENA */
#घोषणा WM8990_LOP_ENA_BIT			12
#घोषणा WM8990_RON_ENA                          0x0800  /* RON_ENA */
#घोषणा WM8990_RON_ENA_BIT			11
#घोषणा WM8990_ROP_ENA                          0x0400  /* ROP_ENA */
#घोषणा WM8990_ROP_ENA_BIT			10
#घोषणा WM8990_LOPGA_ENA                        0x0080  /* LOPGA_ENA */
#घोषणा WM8990_LOPGA_ENA_BIT			7
#घोषणा WM8990_ROPGA_ENA                        0x0040  /* ROPGA_ENA */
#घोषणा WM8990_ROPGA_ENA_BIT			6
#घोषणा WM8990_LOMIX_ENA                        0x0020  /* LOMIX_ENA */
#घोषणा WM8990_LOMIX_ENA_BIT			5
#घोषणा WM8990_ROMIX_ENA                        0x0010  /* ROMIX_ENA */
#घोषणा WM8990_ROMIX_ENA_BIT			4
#घोषणा WM8990_DACL_ENA                         0x0002  /* DACL_ENA */
#घोषणा WM8990_DACL_ENA_BIT			1
#घोषणा WM8990_DACR_ENA                         0x0001  /* DACR_ENA */
#घोषणा WM8990_DACR_ENA_BIT			0

/*
 * R4 (0x04) - Audio Interface (1)
 */
#घोषणा WM8990_AIFADCL_SRC                      0x8000  /* AIFADCL_SRC */
#घोषणा WM8990_AIFADCR_SRC                      0x4000  /* AIFADCR_SRC */
#घोषणा WM8990_AIFADC_TDM                       0x2000  /* AIFADC_TDM */
#घोषणा WM8990_AIFADC_TDM_CHAN                  0x1000  /* AIFADC_TDM_CHAN */
#घोषणा WM8990_AIF_BCLK_INV                     0x0100  /* AIF_BCLK_INV */
#घोषणा WM8990_AIF_LRCLK_INV                    0x0080  /* AIF_LRCLK_INV */
#घोषणा WM8990_AIF_WL_MASK                      0x0060  /* AIF_WL - [6:5] */
#घोषणा WM8990_AIF_WL_16BITS			(0 << 5)
#घोषणा WM8990_AIF_WL_20BITS			(1 << 5)
#घोषणा WM8990_AIF_WL_24BITS			(2 << 5)
#घोषणा WM8990_AIF_WL_32BITS			(3 << 5)
#घोषणा WM8990_AIF_FMT_MASK                     0x0018  /* AIF_FMT - [4:3] */
#घोषणा WM8990_AIF_TMF_RIGHTJ			(0 << 3)
#घोषणा WM8990_AIF_TMF_LEFTJ			(1 << 3)
#घोषणा WM8990_AIF_TMF_I2S			(2 << 3)
#घोषणा WM8990_AIF_TMF_DSP			(3 << 3)

/*
 * R5 (0x05) - Audio Interface (2)
 */
#घोषणा WM8990_DACL_SRC                         0x8000  /* DACL_SRC */
#घोषणा WM8990_DACR_SRC                         0x4000  /* DACR_SRC */
#घोषणा WM8990_AIFDAC_TDM                       0x2000  /* AIFDAC_TDM */
#घोषणा WM8990_AIFDAC_TDM_CHAN                  0x1000  /* AIFDAC_TDM_CHAN */
#घोषणा WM8990_DAC_BOOST_MASK                   0x0C00  /* DAC_BOOST */
#घोषणा WM8990_DAC_COMP                         0x0010  /* DAC_COMP */
#घोषणा WM8990_DAC_COMPMODE                     0x0008  /* DAC_COMPMODE */
#घोषणा WM8990_ADC_COMP                         0x0004  /* ADC_COMP */
#घोषणा WM8990_ADC_COMPMODE                     0x0002  /* ADC_COMPMODE */
#घोषणा WM8990_LOOPBACK                         0x0001  /* LOOPBACK */

/*
 * R6 (0x06) - Clocking (1)
 */
#घोषणा WM8990_TOCLK_RATE                       0x8000  /* TOCLK_RATE */
#घोषणा WM8990_TOCLK_ENA                        0x4000  /* TOCLK_ENA */
#घोषणा WM8990_OPCLKDIV_MASK                    0x1E00  /* OPCLKDIV - [12:9] */
#घोषणा WM8990_DCLKDIV_MASK                     0x01C0  /* DCLKDIV - [8:6] */
#घोषणा WM8990_BCLK_DIV_MASK                    0x001E  /* BCLK_DIV - [4:1] */
#घोषणा WM8990_BCLK_DIV_1			(0x0 << 1)
#घोषणा WM8990_BCLK_DIV_1_5			(0x1 << 1)
#घोषणा WM8990_BCLK_DIV_2			(0x2 << 1)
#घोषणा WM8990_BCLK_DIV_3			(0x3 << 1)
#घोषणा WM8990_BCLK_DIV_4			(0x4 << 1)
#घोषणा WM8990_BCLK_DIV_5_5			(0x5 << 1)
#घोषणा WM8990_BCLK_DIV_6			(0x6 << 1)
#घोषणा WM8990_BCLK_DIV_8			(0x7 << 1)
#घोषणा WM8990_BCLK_DIV_11			(0x8 << 1)
#घोषणा WM8990_BCLK_DIV_12			(0x9 << 1)
#घोषणा WM8990_BCLK_DIV_16			(0xA << 1)
#घोषणा WM8990_BCLK_DIV_22			(0xB << 1)
#घोषणा WM8990_BCLK_DIV_24			(0xC << 1)
#घोषणा WM8990_BCLK_DIV_32			(0xD << 1)
#घोषणा WM8990_BCLK_DIV_44			(0xE << 1)
#घोषणा WM8990_BCLK_DIV_48			(0xF << 1)

/*
 * R7 (0x07) - Clocking (2)
 */
#घोषणा WM8990_MCLK_SRC                         0x8000  /* MCLK_SRC */
#घोषणा WM8990_SYSCLK_SRC                       0x4000  /* SYSCLK_SRC */
#घोषणा WM8990_CLK_FORCE                        0x2000  /* CLK_FORCE */
#घोषणा WM8990_MCLK_DIV_MASK                    0x1800  /* MCLK_DIV - [12:11] */
#घोषणा WM8990_MCLK_DIV_1			(0 << 11)
#घोषणा WM8990_MCLK_DIV_2			(2 << 11)
#घोषणा WM8990_MCLK_INV                         0x0400  /* MCLK_INV */
#घोषणा WM8990_ADC_CLKDIV_MASK                  0x00E0  /* ADC_CLKDIV */
#घोषणा WM8990_ADC_CLKDIV_1			(0 << 5)
#घोषणा WM8990_ADC_CLKDIV_1_5			(1 << 5)
#घोषणा WM8990_ADC_CLKDIV_2			(2 << 5)
#घोषणा WM8990_ADC_CLKDIV_3			(3 << 5)
#घोषणा WM8990_ADC_CLKDIV_4			(4 << 5)
#घोषणा WM8990_ADC_CLKDIV_5_5			(5 << 5)
#घोषणा WM8990_ADC_CLKDIV_6			(6 << 5)
#घोषणा WM8990_DAC_CLKDIV_MASK                  0x001C  /* DAC_CLKDIV - [4:2] */
#घोषणा WM8990_DAC_CLKDIV_1			(0 << 2)
#घोषणा WM8990_DAC_CLKDIV_1_5			(1 << 2)
#घोषणा WM8990_DAC_CLKDIV_2			(2 << 2)
#घोषणा WM8990_DAC_CLKDIV_3			(3 << 2)
#घोषणा WM8990_DAC_CLKDIV_4			(4 << 2)
#घोषणा WM8990_DAC_CLKDIV_5_5			(5 << 2)
#घोषणा WM8990_DAC_CLKDIV_6			(6 << 2)

/*
 * R8 (0x08) - Audio Interface (3)
 */
#घोषणा WM8990_AIF_MSTR1                        0x8000  /* AIF_MSTR1 */
#घोषणा WM8990_AIF_MSTR2                        0x4000  /* AIF_MSTR2 */
#घोषणा WM8990_AIF_SEL                          0x2000  /* AIF_SEL */
#घोषणा WM8990_ADCLRC_सूची                       0x0800  /* ADCLRC_सूची */
#घोषणा WM8990_ADCLRC_RATE_MASK                 0x07FF  /* ADCLRC_RATE */

/*
 * R9 (0x09) - Audio Interface (4)
 */
#घोषणा WM8990_ALRCGPIO1                        0x8000  /* ALRCGPIO1 */
#घोषणा WM8990_ALRCBGPIO6                       0x4000  /* ALRCBGPIO6 */
#घोषणा WM8990_AIF_TRIS                         0x2000  /* AIF_TRIS */
#घोषणा WM8990_DACLRC_सूची                       0x0800  /* DACLRC_सूची */
#घोषणा WM8990_DACLRC_RATE_MASK                 0x07FF  /* DACLRC_RATE */

/*
 * R10 (0x0A) - DAC CTRL
 */
#घोषणा WM8990_AIF_LRCLKRATE                    0x0400  /* AIF_LRCLKRATE */
#घोषणा WM8990_DAC_MONO                         0x0200  /* DAC_MONO */
#घोषणा WM8990_DAC_SB_FILT                      0x0100  /* DAC_SB_FILT */
#घोषणा WM8990_DAC_MUTERATE                     0x0080  /* DAC_MUTERATE */
#घोषणा WM8990_DAC_MUTEMODE                     0x0040  /* DAC_MUTEMODE */
#घोषणा WM8990_DEEMP_MASK                       0x0030  /* DEEMP - [5:4] */
#घोषणा WM8990_DAC_MUTE                         0x0004  /* DAC_MUTE */
#घोषणा WM8990_DACL_DATINV                      0x0002  /* DACL_DATINV */
#घोषणा WM8990_DACR_DATINV                      0x0001  /* DACR_DATINV */

/*
 * R11 (0x0B) - Left DAC Digital Volume
 */
#घोषणा WM8990_DAC_VU                           0x0100  /* DAC_VU */
#घोषणा WM8990_DACL_VOL_MASK                    0x00FF  /* DACL_VOL - [7:0] */
#घोषणा WM8990_DACL_VOL_SHIFT			0
/*
 * R12 (0x0C) - Right DAC Digital Volume
 */
#घोषणा WM8990_DAC_VU                           0x0100  /* DAC_VU */
#घोषणा WM8990_DACR_VOL_MASK                    0x00FF  /* DACR_VOL - [7:0] */
#घोषणा WM8990_DACR_VOL_SHIFT			0
/*
 * R13 (0x0D) - Digital Side Tone
 */
#घोषणा WM8990_ADCL_DAC_SVOL_MASK               0x0F  /* ADCL_DAC_SVOL */
#घोषणा WM8990_ADCL_DAC_SVOL_SHIFT		9
#घोषणा WM8990_ADCR_DAC_SVOL_MASK               0x0F  /* ADCR_DAC_SVOL */
#घोषणा WM8990_ADCR_DAC_SVOL_SHIFT		5
#घोषणा WM8990_ADC_TO_DACL_MASK                 0x03  /* ADC_TO_DACL - [3:2] */
#घोषणा WM8990_ADC_TO_DACL_SHIFT		2
#घोषणा WM8990_ADC_TO_DACR_MASK                 0x03  /* ADC_TO_DACR - [1:0] */
#घोषणा WM8990_ADC_TO_DACR_SHIFT		0

/*
 * R14 (0x0E) - ADC CTRL
 */
#घोषणा WM8990_ADC_HPF_ENA                      0x0100  /* ADC_HPF_ENA */
#घोषणा WM8990_ADC_HPF_ENA_BIT			8
#घोषणा WM8990_ADC_HPF_CUT_MASK                 0x03  /* ADC_HPF_CUT - [6:5] */
#घोषणा WM8990_ADC_HPF_CUT_SHIFT		5
#घोषणा WM8990_ADCL_DATINV                      0x0002  /* ADCL_DATINV */
#घोषणा WM8990_ADCL_DATINV_BIT			1
#घोषणा WM8990_ADCR_DATINV                      0x0001  /* ADCR_DATINV */
#घोषणा WM8990_ADCR_DATINV_BIT			0

/*
 * R15 (0x0F) - Left ADC Digital Volume
 */
#घोषणा WM8990_ADC_VU                           0x0100  /* ADC_VU */
#घोषणा WM8990_ADCL_VOL_MASK                    0x00FF  /* ADCL_VOL - [7:0] */
#घोषणा WM8990_ADCL_VOL_SHIFT			0

/*
 * R16 (0x10) - Right ADC Digital Volume
 */
#घोषणा WM8990_ADC_VU                           0x0100  /* ADC_VU */
#घोषणा WM8990_ADCR_VOL_MASK                    0x00FF  /* ADCR_VOL - [7:0] */
#घोषणा WM8990_ADCR_VOL_SHIFT			0

/*
 * R18 (0x12) - GPIO CTRL 1
 */
#घोषणा WM8990_IRQ                              0x1000  /* IRQ */
#घोषणा WM8990_TEMPOK                           0x0800  /* TEMPOK */
#घोषणा WM8990_MICSHRT                          0x0400  /* MICSHRT */
#घोषणा WM8990_MICDET                           0x0200  /* MICDET */
#घोषणा WM8990_PLL_LCK                          0x0100  /* PLL_LCK */
#घोषणा WM8990_GPI8_STATUS                      0x0080  /* GPI8_STATUS */
#घोषणा WM8990_GPI7_STATUS                      0x0040  /* GPI7_STATUS */
#घोषणा WM8990_GPIO6_STATUS                     0x0020  /* GPIO6_STATUS */
#घोषणा WM8990_GPIO5_STATUS                     0x0010  /* GPIO5_STATUS */
#घोषणा WM8990_GPIO4_STATUS                     0x0008  /* GPIO4_STATUS */
#घोषणा WM8990_GPIO3_STATUS                     0x0004  /* GPIO3_STATUS */
#घोषणा WM8990_GPIO2_STATUS                     0x0002  /* GPIO2_STATUS */
#घोषणा WM8990_GPIO1_STATUS                     0x0001  /* GPIO1_STATUS */

/*
 * R19 (0x13) - GPIO1 & GPIO2
 */
#घोषणा WM8990_GPIO2_DEB_ENA                    0x8000  /* GPIO2_DEB_ENA */
#घोषणा WM8990_GPIO2_IRQ_ENA                    0x4000  /* GPIO2_IRQ_ENA */
#घोषणा WM8990_GPIO2_PU                         0x2000  /* GPIO2_PU */
#घोषणा WM8990_GPIO2_PD                         0x1000  /* GPIO2_PD */
#घोषणा WM8990_GPIO2_SEL_MASK                   0x0F00  /* GPIO2_SEL - [11:8] */
#घोषणा WM8990_GPIO1_DEB_ENA                    0x0080  /* GPIO1_DEB_ENA */
#घोषणा WM8990_GPIO1_IRQ_ENA                    0x0040  /* GPIO1_IRQ_ENA */
#घोषणा WM8990_GPIO1_PU                         0x0020  /* GPIO1_PU */
#घोषणा WM8990_GPIO1_PD                         0x0010  /* GPIO1_PD */
#घोषणा WM8990_GPIO1_SEL_MASK                   0x000F  /* GPIO1_SEL - [3:0] */

/*
 * R20 (0x14) - GPIO3 & GPIO4
 */
#घोषणा WM8990_GPIO4_DEB_ENA                    0x8000  /* GPIO4_DEB_ENA */
#घोषणा WM8990_GPIO4_IRQ_ENA                    0x4000  /* GPIO4_IRQ_ENA */
#घोषणा WM8990_GPIO4_PU                         0x2000  /* GPIO4_PU */
#घोषणा WM8990_GPIO4_PD                         0x1000  /* GPIO4_PD */
#घोषणा WM8990_GPIO4_SEL_MASK                   0x0F00  /* GPIO4_SEL - [11:8] */
#घोषणा WM8990_GPIO3_DEB_ENA                    0x0080  /* GPIO3_DEB_ENA */
#घोषणा WM8990_GPIO3_IRQ_ENA                    0x0040  /* GPIO3_IRQ_ENA */
#घोषणा WM8990_GPIO3_PU                         0x0020  /* GPIO3_PU */
#घोषणा WM8990_GPIO3_PD                         0x0010  /* GPIO3_PD */
#घोषणा WM8990_GPIO3_SEL_MASK                   0x000F  /* GPIO3_SEL - [3:0] */

/*
 * R21 (0x15) - GPIO5 & GPIO6
 */
#घोषणा WM8990_GPIO6_DEB_ENA                    0x8000  /* GPIO6_DEB_ENA */
#घोषणा WM8990_GPIO6_IRQ_ENA                    0x4000  /* GPIO6_IRQ_ENA */
#घोषणा WM8990_GPIO6_PU                         0x2000  /* GPIO6_PU */
#घोषणा WM8990_GPIO6_PD                         0x1000  /* GPIO6_PD */
#घोषणा WM8990_GPIO6_SEL_MASK                   0x0F00  /* GPIO6_SEL - [11:8] */
#घोषणा WM8990_GPIO5_DEB_ENA                    0x0080  /* GPIO5_DEB_ENA */
#घोषणा WM8990_GPIO5_IRQ_ENA                    0x0040  /* GPIO5_IRQ_ENA */
#घोषणा WM8990_GPIO5_PU                         0x0020  /* GPIO5_PU */
#घोषणा WM8990_GPIO5_PD                         0x0010  /* GPIO5_PD */
#घोषणा WM8990_GPIO5_SEL_MASK                   0x000F  /* GPIO5_SEL - [3:0] */

/*
 * R22 (0x16) - GPIOCTRL 2
 */
#घोषणा WM8990_RD_3W_ENA                        0x8000  /* RD_3W_ENA */
#घोषणा WM8990_MODE_3W4W                        0x4000  /* MODE_3W4W */
#घोषणा WM8990_TEMPOK_IRQ_ENA                   0x0800  /* TEMPOK_IRQ_ENA */
#घोषणा WM8990_MICSHRT_IRQ_ENA                  0x0400  /* MICSHRT_IRQ_ENA */
#घोषणा WM8990_MICDET_IRQ_ENA                   0x0200  /* MICDET_IRQ_ENA */
#घोषणा WM8990_PLL_LCK_IRQ_ENA                  0x0100  /* PLL_LCK_IRQ_ENA */
#घोषणा WM8990_GPI8_DEB_ENA                     0x0080  /* GPI8_DEB_ENA */
#घोषणा WM8990_GPI8_IRQ_ENA                     0x0040  /* GPI8_IRQ_ENA */
#घोषणा WM8990_GPI8_ENA                         0x0010  /* GPI8_ENA */
#घोषणा WM8990_GPI7_DEB_ENA                     0x0008  /* GPI7_DEB_ENA */
#घोषणा WM8990_GPI7_IRQ_ENA                     0x0004  /* GPI7_IRQ_ENA */
#घोषणा WM8990_GPI7_ENA                         0x0001  /* GPI7_ENA */

/*
 * R23 (0x17) - GPIO_POL
 */
#घोषणा WM8990_IRQ_INV                          0x1000  /* IRQ_INV */
#घोषणा WM8990_TEMPOK_POL                       0x0800  /* TEMPOK_POL */
#घोषणा WM8990_MICSHRT_POL                      0x0400  /* MICSHRT_POL */
#घोषणा WM8990_MICDET_POL                       0x0200  /* MICDET_POL */
#घोषणा WM8990_PLL_LCK_POL                      0x0100  /* PLL_LCK_POL */
#घोषणा WM8990_GPI8_POL                         0x0080  /* GPI8_POL */
#घोषणा WM8990_GPI7_POL                         0x0040  /* GPI7_POL */
#घोषणा WM8990_GPIO6_POL                        0x0020  /* GPIO6_POL */
#घोषणा WM8990_GPIO5_POL                        0x0010  /* GPIO5_POL */
#घोषणा WM8990_GPIO4_POL                        0x0008  /* GPIO4_POL */
#घोषणा WM8990_GPIO3_POL                        0x0004  /* GPIO3_POL */
#घोषणा WM8990_GPIO2_POL                        0x0002  /* GPIO2_POL */
#घोषणा WM8990_GPIO1_POL                        0x0001  /* GPIO1_POL */

/*
 * R24 (0x18) - Left Line Input 1&2 Volume
 */
#घोषणा WM8990_IPVU                             0x0100  /* IPVU */
#घोषणा WM8990_LI12MUTE                         0x0080  /* LI12MUTE */
#घोषणा WM8990_LI12MUTE_BIT			7
#घोषणा WM8990_LI12ZC                           0x0040  /* LI12ZC */
#घोषणा WM8990_LI12ZC_BIT			6
#घोषणा WM8990_LIN12VOL_MASK                    0x001F  /* LIN12VOL - [4:0] */
#घोषणा WM8990_LIN12VOL_SHIFT			0
/*
 * R25 (0x19) - Left Line Input 3&4 Volume
 */
#घोषणा WM8990_IPVU                             0x0100  /* IPVU */
#घोषणा WM8990_LI34MUTE                         0x0080  /* LI34MUTE */
#घोषणा WM8990_LI34MUTE_BIT			7
#घोषणा WM8990_LI34ZC                           0x0040  /* LI34ZC */
#घोषणा WM8990_LI34ZC_BIT			6
#घोषणा WM8990_LIN34VOL_MASK                    0x001F  /* LIN34VOL - [4:0] */
#घोषणा WM8990_LIN34VOL_SHIFT			0

/*
 * R26 (0x1A) - Right Line Input 1&2 Volume
 */
#घोषणा WM8990_IPVU                             0x0100  /* IPVU */
#घोषणा WM8990_RI12MUTE                         0x0080  /* RI12MUTE */
#घोषणा WM8990_RI12MUTE_BIT			7
#घोषणा WM8990_RI12ZC                           0x0040  /* RI12ZC */
#घोषणा WM8990_RI12ZC_BIT			6
#घोषणा WM8990_RIN12VOL_MASK                    0x001F  /* RIN12VOL - [4:0] */
#घोषणा WM8990_RIN12VOL_SHIFT			0

/*
 * R27 (0x1B) - Right Line Input 3&4 Volume
 */
#घोषणा WM8990_IPVU                             0x0100  /* IPVU */
#घोषणा WM8990_RI34MUTE                         0x0080  /* RI34MUTE */
#घोषणा WM8990_RI34MUTE_BIT			7
#घोषणा WM8990_RI34ZC                           0x0040  /* RI34ZC */
#घोषणा WM8990_RI34ZC_BIT			6
#घोषणा WM8990_RIN34VOL_MASK                    0x001F  /* RIN34VOL - [4:0] */
#घोषणा WM8990_RIN34VOL_SHIFT			0

/*
 * R28 (0x1C) - Left Output Volume
 */
#घोषणा WM8990_OPVU                             0x0100  /* OPVU */
#घोषणा WM8990_LOZC                             0x0080  /* LOZC */
#घोषणा WM8990_LOZC_BIT				7
#घोषणा WM8990_LOUTVOL_MASK                     0x007F  /* LOUTVOL - [6:0] */
#घोषणा WM8990_LOUTVOL_SHIFT			0
/*
 * R29 (0x1D) - Right Output Volume
 */
#घोषणा WM8990_OPVU                             0x0100  /* OPVU */
#घोषणा WM8990_ROZC                             0x0080  /* ROZC */
#घोषणा WM8990_ROZC_BIT				7
#घोषणा WM8990_ROUTVOL_MASK                     0x007F  /* ROUTVOL - [6:0] */
#घोषणा WM8990_ROUTVOL_SHIFT			0
/*
 * R30 (0x1E) - Line Outमाला_दो Volume
 */
#घोषणा WM8990_LONMUTE                          0x0040  /* LONMUTE */
#घोषणा WM8990_LONMUTE_BIT			6
#घोषणा WM8990_LOPMUTE                          0x0020  /* LOPMUTE */
#घोषणा WM8990_LOPMUTE_BIT			5
#घोषणा WM8990_LOATTN                           0x0010  /* LOATTN */
#घोषणा WM8990_LOATTN_BIT			4
#घोषणा WM8990_RONMUTE                          0x0004  /* RONMUTE */
#घोषणा WM8990_RONMUTE_BIT			2
#घोषणा WM8990_ROPMUTE                          0x0002  /* ROPMUTE */
#घोषणा WM8990_ROPMUTE_BIT			1
#घोषणा WM8990_ROATTN                           0x0001  /* ROATTN */
#घोषणा WM8990_ROATTN_BIT			0

/*
 * R31 (0x1F) - Out3/4 Volume
 */
#घोषणा WM8990_OUT3MUTE                         0x0020  /* OUT3MUTE */
#घोषणा WM8990_OUT3MUTE_BIT			5
#घोषणा WM8990_OUT3ATTN                         0x0010  /* OUT3ATTN */
#घोषणा WM8990_OUT3ATTN_BIT			4
#घोषणा WM8990_OUT4MUTE                         0x0002  /* OUT4MUTE */
#घोषणा WM8990_OUT4MUTE_BIT			1
#घोषणा WM8990_OUT4ATTN                         0x0001  /* OUT4ATTN */
#घोषणा WM8990_OUT4ATTN_BIT			0

/*
 * R32 (0x20) - Left OPGA Volume
 */
#घोषणा WM8990_OPVU                             0x0100  /* OPVU */
#घोषणा WM8990_LOPGAZC                          0x0080  /* LOPGAZC */
#घोषणा WM8990_LOPGAZC_BIT			7
#घोषणा WM8990_LOPGAVOL_MASK                    0x007F  /* LOPGAVOL - [6:0] */
#घोषणा WM8990_LOPGAVOL_SHIFT			0

/*
 * R33 (0x21) - Right OPGA Volume
 */
#घोषणा WM8990_OPVU                             0x0100  /* OPVU */
#घोषणा WM8990_ROPGAZC                          0x0080  /* ROPGAZC */
#घोषणा WM8990_ROPGAZC_BIT			7
#घोषणा WM8990_ROPGAVOL_MASK                    0x007F  /* ROPGAVOL - [6:0] */
#घोषणा WM8990_ROPGAVOL_SHIFT			0
/*
 * R34 (0x22) - Speaker Volume
 */
#घोषणा WM8990_SPKATTN_MASK                      0x0003  /* SPKATTN - [1:0] */
#घोषणा WM8990_SPKATTN_SHIFT			 0

/*
 * R35 (0x23) - ClassD1
 */
#घोषणा WM8990_CDMODE                           0x0100  /* CDMODE */
#घोषणा WM8990_CDMODE_BIT			8

/*
 * R37 (0x25) - ClassD3
 */
#घोषणा WM8990_DCGAIN_MASK                      0x0007  /* DCGAIN - [5:3] */
#घोषणा WM8990_DCGAIN_SHIFT			3
#घोषणा WM8990_ACGAIN_MASK                      0x0007  /* ACGAIN - [2:0] */
#घोषणा WM8990_ACGAIN_SHIFT			0

/*
 * R38 (0x26) - ClassD4
 */
#घोषणा WM8990_SPKZC_MASK                       0x0001  /* SPKZC */
#घोषणा WM8990_SPKZC_SHIFT                           7  /* SPKZC */
#घोषणा WM8990_SPKVOL_MASK                      0x007F  /* SPKVOL - [6:0] */
#घोषणा WM8990_SPKVOL_SHIFT                          0  /* SPKVOL - [6:0] */

/*
 * R39 (0x27) - Input Mixer1
 */
#घोषणा WM8990_AINLMODE_MASK                    0x000C  /* AINLMODE - [3:2] */
#घोषणा WM8990_AINLMODE_SHIFT			2
#घोषणा WM8990_AINRMODE_MASK                    0x0003  /* AINRMODE - [1:0] */
#घोषणा WM8990_AINRMODE_SHIFT			0

/*
 * R40 (0x28) - Input Mixer2
 */
#घोषणा WM8990_LMP4				0x0080	/* LMP4 */
#घोषणा WM8990_LMP4_BIT                         7	/* LMP4 */
#घोषणा WM8990_LMN3                             0x0040  /* LMN3 */
#घोषणा WM8990_LMN3_BIT                         6       /* LMN3 */
#घोषणा WM8990_LMP2                             0x0020  /* LMP2 */
#घोषणा WM8990_LMP2_BIT                         5       /* LMP2 */
#घोषणा WM8990_LMN1                             0x0010  /* LMN1 */
#घोषणा WM8990_LMN1_BIT                         4       /* LMN1 */
#घोषणा WM8990_RMP4                             0x0008  /* RMP4 */
#घोषणा WM8990_RMP4_BIT                         3       /* RMP4 */
#घोषणा WM8990_RMN3                             0x0004  /* RMN3 */
#घोषणा WM8990_RMN3_BIT                         2       /* RMN3 */
#घोषणा WM8990_RMP2                             0x0002  /* RMP2 */
#घोषणा WM8990_RMP2_BIT                         1       /* RMP2 */
#घोषणा WM8990_RMN1                             0x0001  /* RMN1 */
#घोषणा WM8990_RMN1_BIT                         0       /* RMN1 */

/*
 * R41 (0x29) - Input Mixer3
 */
#घोषणा WM8990_L34MNB                           0x0100  /* L34MNB */
#घोषणा WM8990_L34MNB_BIT			8
#घोषणा WM8990_L34MNBST                         0x0080  /* L34MNBST */
#घोषणा WM8990_L34MNBST_BIT			7
#घोषणा WM8990_L12MNB                           0x0020  /* L12MNB */
#घोषणा WM8990_L12MNB_BIT			5
#घोषणा WM8990_L12MNBST                         0x0010  /* L12MNBST */
#घोषणा WM8990_L12MNBST_BIT			4
#घोषणा WM8990_LDBVOL_MASK                      0x0007  /* LDBVOL - [2:0] */
#घोषणा WM8990_LDBVOL_SHIFT			0

/*
 * R42 (0x2A) - Input Mixer4
 */
#घोषणा WM8990_R34MNB                           0x0100  /* R34MNB */
#घोषणा WM8990_R34MNB_BIT			8
#घोषणा WM8990_R34MNBST                         0x0080  /* R34MNBST */
#घोषणा WM8990_R34MNBST_BIT			7
#घोषणा WM8990_R12MNB                           0x0020  /* R12MNB */
#घोषणा WM8990_R12MNB_BIT			5
#घोषणा WM8990_R12MNBST                         0x0010  /* R12MNBST */
#घोषणा WM8990_R12MNBST_BIT			4
#घोषणा WM8990_RDBVOL_MASK                      0x0007  /* RDBVOL - [2:0] */
#घोषणा WM8990_RDBVOL_SHIFT			0

/*
 * R43 (0x2B) - Input Mixer5
 */
#घोषणा WM8990_LI2BVOL_MASK                     0x07  /* LI2BVOL - [8:6] */
#घोषणा WM8990_LI2BVOL_SHIFT			6
#घोषणा WM8990_LR4BVOL_MASK                     0x07  /* LR4BVOL - [5:3] */
#घोषणा WM8990_LR4BVOL_SHIFT			3
#घोषणा WM8990_LL4BVOL_MASK                     0x07  /* LL4BVOL - [2:0] */
#घोषणा WM8990_LL4BVOL_SHIFT			0

/*
 * R44 (0x2C) - Input Mixer6
 */
#घोषणा WM8990_RI2BVOL_MASK                     0x07  /* RI2BVOL - [8:6] */
#घोषणा WM8990_RI2BVOL_SHIFT			6
#घोषणा WM8990_RL4BVOL_MASK                     0x07  /* RL4BVOL - [5:3] */
#घोषणा WM8990_RL4BVOL_SHIFT			3
#घोषणा WM8990_RR4BVOL_MASK                     0x07  /* RR4BVOL - [2:0] */
#घोषणा WM8990_RR4BVOL_SHIFT			0

/*
 * R45 (0x2D) - Output Mixer1
 */
#घोषणा WM8990_LRBLO                            0x0080  /* LRBLO */
#घोषणा WM8990_LRBLO_BIT			7
#घोषणा WM8990_LLBLO                            0x0040  /* LLBLO */
#घोषणा WM8990_LLBLO_BIT			6
#घोषणा WM8990_LRI3LO                           0x0020  /* LRI3LO */
#घोषणा WM8990_LRI3LO_BIT			5
#घोषणा WM8990_LLI3LO                           0x0010  /* LLI3LO */
#घोषणा WM8990_LLI3LO_BIT			4
#घोषणा WM8990_LR12LO                           0x0008  /* LR12LO */
#घोषणा WM8990_LR12LO_BIT			3
#घोषणा WM8990_LL12LO                           0x0004  /* LL12LO */
#घोषणा WM8990_LL12LO_BIT			2
#घोषणा WM8990_LDLO                             0x0001  /* LDLO */
#घोषणा WM8990_LDLO_BIT				0

/*
 * R46 (0x2E) - Output Mixer2
 */
#घोषणा WM8990_RLBRO                            0x0080  /* RLBRO */
#घोषणा WM8990_RLBRO_BIT			7
#घोषणा WM8990_RRBRO                            0x0040  /* RRBRO */
#घोषणा WM8990_RRBRO_BIT			6
#घोषणा WM8990_RLI3RO                           0x0020  /* RLI3RO */
#घोषणा WM8990_RLI3RO_BIT			5
#घोषणा WM8990_RRI3RO                           0x0010  /* RRI3RO */
#घोषणा WM8990_RRI3RO_BIT			4
#घोषणा WM8990_RL12RO                           0x0008  /* RL12RO */
#घोषणा WM8990_RL12RO_BIT			3
#घोषणा WM8990_RR12RO                           0x0004  /* RR12RO */
#घोषणा WM8990_RR12RO_BIT			2
#घोषणा WM8990_RDRO                             0x0001  /* RDRO */
#घोषणा WM8990_RDRO_BIT				0

/*
 * R47 (0x2F) - Output Mixer3
 */
#घोषणा WM8990_LLI3LOVOL_MASK                   0x07  /* LLI3LOVOL - [8:6] */
#घोषणा WM8990_LLI3LOVOL_SHIFT			6
#घोषणा WM8990_LR12LOVOL_MASK                   0x07  /* LR12LOVOL - [5:3] */
#घोषणा WM8990_LR12LOVOL_SHIFT			3
#घोषणा WM8990_LL12LOVOL_MASK                   0x07  /* LL12LOVOL - [2:0] */
#घोषणा WM8990_LL12LOVOL_SHIFT			0

/*
 * R48 (0x30) - Output Mixer4
 */
#घोषणा WM8990_RRI3ROVOL_MASK                   0x07  /* RRI3ROVOL - [8:6] */
#घोषणा WM8990_RRI3ROVOL_SHIFT			6
#घोषणा WM8990_RL12ROVOL_MASK                   0x07  /* RL12ROVOL - [5:3] */
#घोषणा WM8990_RL12ROVOL_SHIFT			3
#घोषणा WM8990_RR12ROVOL_MASK                   0x07  /* RR12ROVOL - [2:0] */
#घोषणा WM8990_RR12ROVOL_SHIFT			0

/*
 * R49 (0x31) - Output Mixer5
 */
#घोषणा WM8990_LRI3LOVOL_MASK                   0x07  /* LRI3LOVOL - [8:6] */
#घोषणा WM8990_LRI3LOVOL_SHIFT			6
#घोषणा WM8990_LRBLOVOL_MASK                    0x07  /* LRBLOVOL - [5:3] */
#घोषणा WM8990_LRBLOVOL_SHIFT			3
#घोषणा WM8990_LLBLOVOL_MASK                    0x07  /* LLBLOVOL - [2:0] */
#घोषणा WM8990_LLBLOVOL_SHIFT			0

/*
 * R50 (0x32) - Output Mixer6
 */
#घोषणा WM8990_RLI3ROVOL_MASK                   0x07  /* RLI3ROVOL - [8:6] */
#घोषणा WM8990_RLI3ROVOL_SHIFT			6
#घोषणा WM8990_RLBROVOL_MASK                    0x07  /* RLBROVOL - [5:3] */
#घोषणा WM8990_RLBROVOL_SHIFT			3
#घोषणा WM8990_RRBROVOL_MASK                    0x07  /* RRBROVOL - [2:0] */
#घोषणा WM8990_RRBROVOL_SHIFT			0

/*
 * R51 (0x33) - Out3/4 Mixer
 */
#घोषणा WM8990_VSEL_MASK                        0x0180  /* VSEL - [8:7] */
#घोषणा WM8990_LI4O3                            0x0020  /* LI4O3 */
#घोषणा WM8990_LI4O3_BIT			5
#घोषणा WM8990_LPGAO3                           0x0010  /* LPGAO3 */
#घोषणा WM8990_LPGAO3_BIT			4
#घोषणा WM8990_RI4O4                            0x0002  /* RI4O4 */
#घोषणा WM8990_RI4O4_BIT			1
#घोषणा WM8990_RPGAO4                           0x0001  /* RPGAO4 */
#घोषणा WM8990_RPGAO4_BIT			0
/*
 * R52 (0x34) - Line Mixer1
 */
#घोषणा WM8990_LLOPGALON                        0x0040  /* LLOPGALON */
#घोषणा WM8990_LLOPGALON_BIT			6
#घोषणा WM8990_LROPGALON                        0x0020  /* LROPGALON */
#घोषणा WM8990_LROPGALON_BIT			5
#घोषणा WM8990_LOPLON                           0x0010  /* LOPLON */
#घोषणा WM8990_LOPLON_BIT			4
#घोषणा WM8990_LR12LOP                          0x0004  /* LR12LOP */
#घोषणा WM8990_LR12LOP_BIT			2
#घोषणा WM8990_LL12LOP                          0x0002  /* LL12LOP */
#घोषणा WM8990_LL12LOP_BIT			1
#घोषणा WM8990_LLOPGALOP                        0x0001  /* LLOPGALOP */
#घोषणा WM8990_LLOPGALOP_BIT			0
/*
 * R53 (0x35) - Line Mixer2
 */
#घोषणा WM8990_RROPGARON                        0x0040  /* RROPGARON */
#घोषणा WM8990_RROPGARON_BIT			6
#घोषणा WM8990_RLOPGARON                        0x0020  /* RLOPGARON */
#घोषणा WM8990_RLOPGARON_BIT			5
#घोषणा WM8990_ROPRON                           0x0010  /* ROPRON */
#घोषणा WM8990_ROPRON_BIT			4
#घोषणा WM8990_RL12ROP                          0x0004  /* RL12ROP */
#घोषणा WM8990_RL12ROP_BIT			2
#घोषणा WM8990_RR12ROP                          0x0002  /* RR12ROP */
#घोषणा WM8990_RR12ROP_BIT			1
#घोषणा WM8990_RROPGAROP                        0x0001  /* RROPGAROP */
#घोषणा WM8990_RROPGAROP_BIT			0

/*
 * R54 (0x36) - Speaker Mixer
 */
#घोषणा WM8990_LB2SPK                           0x0080  /* LB2SPK */
#घोषणा WM8990_LB2SPK_BIT			7
#घोषणा WM8990_RB2SPK                           0x0040  /* RB2SPK */
#घोषणा WM8990_RB2SPK_BIT			6
#घोषणा WM8990_LI2SPK                           0x0020  /* LI2SPK */
#घोषणा WM8990_LI2SPK_BIT			5
#घोषणा WM8990_RI2SPK                           0x0010  /* RI2SPK */
#घोषणा WM8990_RI2SPK_BIT			4
#घोषणा WM8990_LOPGASPK                         0x0008  /* LOPGASPK */
#घोषणा WM8990_LOPGASPK_BIT			3
#घोषणा WM8990_ROPGASPK                         0x0004  /* ROPGASPK */
#घोषणा WM8990_ROPGASPK_BIT			2
#घोषणा WM8990_LDSPK                            0x0002  /* LDSPK */
#घोषणा WM8990_LDSPK_BIT			1
#घोषणा WM8990_RDSPK                            0x0001  /* RDSPK */
#घोषणा WM8990_RDSPK_BIT			0

/*
 * R55 (0x37) - Additional Control
 */
#घोषणा WM8990_VROI                             0x0001  /* VROI */

/*
 * R56 (0x38) - AntiPOP1
 */
#घोषणा WM8990_DIS_LLINE                        0x0020  /* DIS_LLINE */
#घोषणा WM8990_DIS_RLINE                        0x0010  /* DIS_RLINE */
#घोषणा WM8990_DIS_OUT3                         0x0008  /* DIS_OUT3 */
#घोषणा WM8990_DIS_OUT4                         0x0004  /* DIS_OUT4 */
#घोषणा WM8990_DIS_LOUT                         0x0002  /* DIS_LOUT */
#घोषणा WM8990_DIS_ROUT                         0x0001  /* DIS_ROUT */

/*
 * R57 (0x39) - AntiPOP2
 */
#घोषणा WM8990_SOFTST                           0x0040  /* SOFTST */
#घोषणा WM8990_BUFIOEN                          0x0008  /* BUFIOEN */
#घोषणा WM8990_BUFDCOPEN                        0x0004  /* BUFDCOPEN */
#घोषणा WM8990_POBCTRL                          0x0002  /* POBCTRL */
#घोषणा WM8990_VMIDTOG                          0x0001  /* VMIDTOG */

/*
 * R58 (0x3A) - MICBIAS
 */
#घोषणा WM8990_MCDSCTH_MASK                     0x00C0  /* MCDSCTH - [7:6] */
#घोषणा WM8990_MCDTHR_MASK                      0x0038  /* MCDTHR - [5:3] */
#घोषणा WM8990_MCD                              0x0004  /* MCD */
#घोषणा WM8990_MBSEL                            0x0001  /* MBSEL */

/*
 * R60 (0x3C) - PLL1
 */
#घोषणा WM8990_SDM                              0x0080  /* SDM */
#घोषणा WM8990_PRESCALE                         0x0040  /* PRESCALE */
#घोषणा WM8990_PLLN_MASK                        0x000F  /* PLLN - [3:0] */

/*
 * R61 (0x3D) - PLL2
 */
#घोषणा WM8990_PLLK1_MASK                       0x00FF  /* PLLK1 - [7:0] */

/*
 * R62 (0x3E) - PLL3
 */
#घोषणा WM8990_PLLK2_MASK                       0x00FF  /* PLLK2 - [7:0] */

#घोषणा WM8990_MCLK_DIV 0
#घोषणा WM8990_DACCLK_DIV 1
#घोषणा WM8990_ADCCLK_DIV 2
#घोषणा WM8990_BCLK_DIV 3

#पूर्ण_अगर	/* __WM8990REGISTERDEFS_H__ */
/*------------------------------ END OF खाता ---------------------------------*/
