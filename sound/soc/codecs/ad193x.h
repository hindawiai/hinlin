<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * AD193X Audio Codec driver
 *
 * Copyright 2010 Analog Devices Inc.
 */

#अगर_अघोषित __AD193X_H__
#घोषणा __AD193X_H__

#समावेश <linux/regmap.h>

काष्ठा device;

क्रमागत ad193x_type अणु
	AD193X,
	AD1933,
	AD1934,
पूर्ण;

बाह्य स्थिर काष्ठा regmap_config ad193x_regmap_config;
पूर्णांक ad193x_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
		 क्रमागत ad193x_type type);

#घोषणा AD193X_PLL_CLK_CTRL0    0x00
#घोषणा AD193X_PLL_POWERDOWN           0x01
#घोषणा AD193X_PLL_INPUT_MASK   0x6
#घोषणा AD193X_PLL_INPUT_256    (0 << 1)
#घोषणा AD193X_PLL_INPUT_384    (1 << 1)
#घोषणा AD193X_PLL_INPUT_512    (2 << 1)
#घोषणा AD193X_PLL_INPUT_768    (3 << 1)
#घोषणा AD193X_PLL_CLK_CTRL1    0x01
#घोषणा AD193X_PLL_SRC_MASK	0x03
#घोषणा AD193X_PLL_DAC_SRC_PLL  0
#घोषणा AD193X_PLL_DAC_SRC_MCLK 1
#घोषणा AD193X_PLL_CLK_SRC_PLL  (0 << 1)
#घोषणा AD193X_PLL_CLK_SRC_MCLK	(1 << 1)
#घोषणा AD193X_DAC_CTRL0        0x02
#घोषणा AD193X_DAC_POWERDOWN           0x01
#घोषणा AD193X_DAC_SERFMT_MASK		0xC0
#घोषणा AD193X_DAC_SERFMT_STEREO	(0 << 6)
#घोषणा AD193X_DAC_SERFMT_TDM		(1 << 6)
#घोषणा AD193X_DAC_CTRL1        0x03
#घोषणा AD193X_DAC_CHAN_SHFT    1
#घोषणा AD193X_DAC_CHAN_MASK    (3 << AD193X_DAC_CHAN_SHFT)
#घोषणा AD193X_DAC_LCR_MASTER   (1 << 4)
#घोषणा AD193X_DAC_BCLK_MASTER  (1 << 5)
#घोषणा AD193X_DAC_LEFT_HIGH    (1 << 3)
#घोषणा AD193X_DAC_BCLK_INV     (1 << 7)
#घोषणा AD193X_DAC_FMT_MASK	(AD193X_DAC_LCR_MASTER | \
	AD193X_DAC_BCLK_MASTER | AD193X_DAC_LEFT_HIGH | AD193X_DAC_BCLK_INV)
#घोषणा AD193X_DAC_CTRL2        0x04
#घोषणा AD193X_DAC_WORD_LEN_SHFT        3
#घोषणा AD193X_DAC_WORD_LEN_MASK        0x18
#घोषणा AD193X_DAC_MASTER_MUTE  1
#घोषणा AD193X_DAC_CHNL_MUTE    0x05
#घोषणा AD193X_DACL1_MUTE       0
#घोषणा AD193X_DACR1_MUTE       1
#घोषणा AD193X_DACL2_MUTE       2
#घोषणा AD193X_DACR2_MUTE       3
#घोषणा AD193X_DACL3_MUTE       4
#घोषणा AD193X_DACR3_MUTE       5
#घोषणा AD193X_DACL4_MUTE       6
#घोषणा AD193X_DACR4_MUTE       7
#घोषणा AD193X_DAC_L1_VOL       0x06
#घोषणा AD193X_DAC_R1_VOL       0x07
#घोषणा AD193X_DAC_L2_VOL       0x08
#घोषणा AD193X_DAC_R2_VOL       0x09
#घोषणा AD193X_DAC_L3_VOL       0x0a
#घोषणा AD193X_DAC_R3_VOL       0x0b
#घोषणा AD193X_DAC_L4_VOL       0x0c
#घोषणा AD193X_DAC_R4_VOL       0x0d
#घोषणा AD193X_ADC_CTRL0        0x0e
#घोषणा AD193X_ADC_POWERDOWN           0x01
#घोषणा AD193X_ADC_HIGHPASS_FILTER	1
#घोषणा AD193X_ADCL1_MUTE 		2
#घोषणा AD193X_ADCR1_MUTE 		3
#घोषणा AD193X_ADCL2_MUTE 		4
#घोषणा AD193X_ADCR2_MUTE 		5
#घोषणा AD193X_ADC_CTRL1        0x0f
#घोषणा AD193X_ADC_SERFMT_MASK		0x60
#घोषणा AD193X_ADC_SERFMT_STEREO	(0 << 5)
#घोषणा AD193X_ADC_SERFMT_TDM		(1 << 5)
#घोषणा AD193X_ADC_SERFMT_AUX		(2 << 5)
#घोषणा AD193X_ADC_WORD_LEN_MASK	0x3
#घोषणा AD193X_ADC_CTRL2        0x10
#घोषणा AD193X_ADC_CHAN_SHFT    4
#घोषणा AD193X_ADC_CHAN_MASK    (3 << AD193X_ADC_CHAN_SHFT)
#घोषणा AD193X_ADC_LCR_MASTER   (1 << 3)
#घोषणा AD193X_ADC_BCLK_MASTER  (1 << 6)
#घोषणा AD193X_ADC_LEFT_HIGH    (1 << 2)
#घोषणा AD193X_ADC_BCLK_INV     (1 << 1)
#घोषणा AD193X_ADC_FMT_MASK	(AD193X_ADC_LCR_MASTER | \
	AD193X_ADC_BCLK_MASTER | AD193X_ADC_LEFT_HIGH | AD193X_ADC_BCLK_INV)

#घोषणा AD193X_2_CHANNELS   0
#घोषणा AD193X_4_CHANNELS   1
#घोषणा AD193X_8_CHANNELS   2
#घोषणा AD193X_16_CHANNELS  3

#घोषणा AD193X_NUM_REGS          17

#घोषणा AD193X_SYSCLK_PLL	0
#घोषणा AD193X_SYSCLK_MCLK	1

#पूर्ण_अगर
