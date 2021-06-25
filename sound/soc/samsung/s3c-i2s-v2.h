<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * ALSA Soc Audio Layer - S3C_I2SV2 I2S driver
 *
 * Copyright (c) 2007 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 */

/* This code is the core support क्रम the I2S block found in a number of
 * Samsung SoC devices which is unofficially named I2S-V2. Currently the
 * S3C2412 and the S3C64XX series use this block to provide 1 or 2 I2S
 * channels via configurable GPIO.
 */

#अगर_अघोषित __SND_SOC_S3C24XX_S3C_I2SV2_I2S_H
#घोषणा __SND_SOC_S3C24XX_S3C_I2SV2_I2S_H __खाता__

#घोषणा S3C_I2SV2_DIV_BCLK	(1)
#घोषणा S3C_I2SV2_DIV_RCLK	(2)
#घोषणा S3C_I2SV2_DIV_PRESCALER	(3)

#घोषणा S3C_I2SV2_CLKSRC_PCLK		0
#घोषणा S3C_I2SV2_CLKSRC_AUDIOBUS	1
#घोषणा S3C_I2SV2_CLKSRC_CDCLK		2

/* Set this flag क्रम I2S controllers that have the bit IISMOD[12]
 * bridge/अवरोध RCLK संकेत and बाह्यal Xi2sCDCLK pin.
 */
#घोषणा S3C_FEATURE_CDCLKCON	(1 << 0)

/**
 * काष्ठा s3c_i2sv2_info - S3C I2S-V2 inक्रमmation
 * @dev: The parent device passed to use from the probe.
 * @regs: The poपूर्णांकer to the device registe block.
 * @feature: Set of bit-flags indicating features of the controller.
 * @master: True अगर the I2S core is the I2S bit घड़ी master.
 * @dma_playback: DMA inक्रमmation क्रम playback channel.
 * @dma_capture: DMA inक्रमmation क्रम capture channel.
 * @suspend_iismod: PM save क्रम the IISMOD रेजिस्टर.
 * @suspend_iiscon: PM save क्रम the IISCON रेजिस्टर.
 * @suspend_iispsr: PM save क्रम the IISPSR रेजिस्टर.
 *
 * This is the निजी codec state क्रम the hardware associated with an
 * I2S channel such as the रेजिस्टर mappings and घड़ी sources.
 */
काष्ठा s3c_i2sv2_info अणु
	काष्ठा device	*dev;
	व्योम __iomem	*regs;

	u32		feature;

	काष्ठा clk	*iis_pclk;
	काष्ठा clk	*iis_cclk;

	अचिन्हित अक्षर	 master;

	काष्ठा snd_dmaengine_dai_dma_data *dma_playback;
	काष्ठा snd_dmaengine_dai_dma_data *dma_capture;

	u32		 suspend_iismod;
	u32		 suspend_iiscon;
	u32		 suspend_iispsr;

	अचिन्हित दीर्घ	base;
पूर्ण;

बाह्य काष्ठा clk *s3c_i2sv2_get_घड़ी(काष्ठा snd_soc_dai *cpu_dai);

काष्ठा s3c_i2sv2_rate_calc अणु
	अचिन्हित पूर्णांक	clk_भाग;	/* क्रम prescaler */
	अचिन्हित पूर्णांक	fs_भाग;		/* क्रम root frame घड़ी */
पूर्ण;

बाह्य पूर्णांक s3c_i2sv2_iis_calc_rate(काष्ठा s3c_i2sv2_rate_calc *info,
				   अचिन्हित पूर्णांक *fstab,
				   अचिन्हित पूर्णांक rate, काष्ठा clk *clk);

/**
 * s3c_i2sv2_probe - probe क्रम i2s device helper
 * @dai: The ASoC DAI काष्ठाure supplied to the original probe.
 * @i2s: Our local i2s काष्ठाure to fill in.
 * @base: The base address क्रम the रेजिस्टरs.
 */
बाह्य पूर्णांक s3c_i2sv2_probe(काष्ठा snd_soc_dai *dai,
			   काष्ठा s3c_i2sv2_info *i2s);

/**
 * s3c_i2sv2_cleanup - cleanup resources allocated in s3c_i2sv2_probe
 * @dai: The ASoC DAI काष्ठाure supplied to the original probe.
 * @i2s: Our local i2s काष्ठाure to fill in.
 */
बाह्य व्योम s3c_i2sv2_cleanup(काष्ठा snd_soc_dai *dai,
			      काष्ठा s3c_i2sv2_info *i2s);
/**
 * s3c_i2sv2_रेजिस्टर_component - रेजिस्टर component and dai with soc core
 * @dev: DAI device
 * @id: DAI ID
 * @drv: The driver काष्ठाure to रेजिस्टर
 *
 * Fill in any missing fields and then रेजिस्टर the given dai with the
 * soc core.
 */
बाह्य पूर्णांक s3c_i2sv2_रेजिस्टर_component(काष्ठा device *dev, पूर्णांक id,
					स्थिर काष्ठा snd_soc_component_driver *cmp_drv,
					काष्ठा snd_soc_dai_driver *dai_drv);

#पूर्ण_अगर /* __SND_SOC_S3C24XX_S3C_I2SV2_I2S_H */
