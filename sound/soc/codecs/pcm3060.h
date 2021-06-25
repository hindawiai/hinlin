<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * PCM3060 codec driver
 *
 * Copyright (C) 2018 Kirill Marinushkin <kmarinushkin@birdec.com>
 */

#अगर_अघोषित _SND_SOC_PCM3060_H
#घोषणा _SND_SOC_PCM3060_H

#समावेश <linux/device.h>
#समावेश <linux/regmap.h>

बाह्य स्थिर काष्ठा regmap_config pcm3060_regmap;

#घोषणा PCM3060_DAI_ID_DAC	0
#घोषणा PCM3060_DAI_ID_ADC	1
#घोषणा PCM3060_DAI_IDS_NUM	2

/* ADC and DAC can be घड़ीed from separate or same sources CLK1 and CLK2 */
#घोषणा PCM3060_CLK_DEF	0 /* शेष: CLK1->ADC, CLK2->DAC */
#घोषणा PCM3060_CLK1		1
#घोषणा PCM3060_CLK2		2

काष्ठा pcm3060_priv_dai अणु
	bool is_master;
	अचिन्हित पूर्णांक sclk_freq;
पूर्ण;

काष्ठा pcm3060_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा pcm3060_priv_dai dai[PCM3060_DAI_IDS_NUM];
	u8 out_se: 1;
पूर्ण;

पूर्णांक pcm3060_probe(काष्ठा device *dev);
पूर्णांक pcm3060_हटाओ(काष्ठा device *dev);

/* रेजिस्टरs */

#घोषणा PCM3060_REG64			0x40
#घोषणा PCM3060_REG_MRST		0x80
#घोषणा PCM3060_REG_SRST		0x40
#घोषणा PCM3060_REG_ADPSV		0x20
#घोषणा PCM3060_REG_SHIFT_ADPSV	0x05
#घोषणा PCM3060_REG_DAPSV		0x10
#घोषणा PCM3060_REG_SHIFT_DAPSV	0x04
#घोषणा PCM3060_REG_SE			0x01

#घोषणा PCM3060_REG65			0x41
#घोषणा PCM3060_REG66			0x42
#घोषणा PCM3060_REG_AT2_MIN		0x36
#घोषणा PCM3060_REG_AT2_MAX		0xFF

#घोषणा PCM3060_REG67			0x43
#घोषणा PCM3060_REG72			0x48
#घोषणा PCM3060_REG_CSEL		0x80
#घोषणा PCM3060_REG_MASK_MS		0x70
#घोषणा PCM3060_REG_MS_S		0x00
#घोषणा PCM3060_REG_MS_M768		(0x01 << 4)
#घोषणा PCM3060_REG_MS_M512		(0x02 << 4)
#घोषणा PCM3060_REG_MS_M384		(0x03 << 4)
#घोषणा PCM3060_REG_MS_M256		(0x04 << 4)
#घोषणा PCM3060_REG_MS_M192		(0x05 << 4)
#घोषणा PCM3060_REG_MS_M128		(0x06 << 4)
#घोषणा PCM3060_REG_MASK_FMT		0x03
#घोषणा PCM3060_REG_FMT_I2S		0x00
#घोषणा PCM3060_REG_FMT_LJ		0x01
#घोषणा PCM3060_REG_FMT_RJ		0x02

#घोषणा PCM3060_REG68			0x44
#घोषणा PCM3060_REG_OVER		0x40
#घोषणा PCM3060_REG_DREV2		0x04
#घोषणा PCM3060_REG_SHIFT_MUT21	0x00
#घोषणा PCM3060_REG_SHIFT_MUT22	0x01

#घोषणा PCM3060_REG69			0x45
#घोषणा PCM3060_REG_FLT		0x80
#घोषणा PCM3060_REG_MASK_DMF		0x60
#घोषणा PCM3060_REG_DMC		0x10
#घोषणा PCM3060_REG_ZREV		0x02
#घोषणा PCM3060_REG_AZRO		0x01

#घोषणा PCM3060_REG70			0x46
#घोषणा PCM3060_REG71			0x47
#घोषणा PCM3060_REG_AT1_MIN		0x0E
#घोषणा PCM3060_REG_AT1_MAX		0xFF

#घोषणा PCM3060_REG73			0x49
#घोषणा PCM3060_REG_ZCDD		0x10
#घोषणा PCM3060_REG_BYP		0x08
#घोषणा PCM3060_REG_DREV1		0x04
#घोषणा PCM3060_REG_SHIFT_MUT11	0x00
#घोषणा PCM3060_REG_SHIFT_MUT12	0x01

#पूर्ण_अगर /* _SND_SOC_PCM3060_H */
