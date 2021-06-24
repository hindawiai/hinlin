<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ALSA SoC SPDIF Audio Layer
 *
 * Copyright 2015 Andrea Venturi <be17068@iperbole.bo.it>
 * Copyright 2015 Marcus Cooper <codekipper@gmail.com>
 *
 * Based on the Allwinner SDK driver, released under the GPL.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#घोषणा	SUN4I_SPDIF_CTL		(0x00)
	#घोषणा SUN4I_SPDIF_CTL_MCLKDIV(v)		((v) << 4) /* v even */
	#घोषणा SUN4I_SPDIF_CTL_MCLKOUTEN		BIT(2)
	#घोषणा SUN4I_SPDIF_CTL_GEN			BIT(1)
	#घोषणा SUN4I_SPDIF_CTL_RESET			BIT(0)

#घोषणा SUN4I_SPDIF_TXCFG	(0x04)
	#घोषणा SUN4I_SPDIF_TXCFG_SINGLEMOD		BIT(31)
	#घोषणा SUN4I_SPDIF_TXCFG_ASS			BIT(17)
	#घोषणा SUN4I_SPDIF_TXCFG_NONAUDIO		BIT(16)
	#घोषणा SUN4I_SPDIF_TXCFG_TXRATIO(v)		((v) << 4)
	#घोषणा SUN4I_SPDIF_TXCFG_TXRATIO_MASK		GENMASK(8, 4)
	#घोषणा SUN4I_SPDIF_TXCFG_FMTRVD		GENMASK(3, 2)
	#घोषणा SUN4I_SPDIF_TXCFG_FMT16BIT		(0 << 2)
	#घोषणा SUN4I_SPDIF_TXCFG_FMT20BIT		(1 << 2)
	#घोषणा SUN4I_SPDIF_TXCFG_FMT24BIT		(2 << 2)
	#घोषणा SUN4I_SPDIF_TXCFG_CHSTMODE		BIT(1)
	#घोषणा SUN4I_SPDIF_TXCFG_TXEN			BIT(0)

#घोषणा SUN4I_SPDIF_RXCFG	(0x08)
	#घोषणा SUN4I_SPDIF_RXCFG_LOCKFLAG		BIT(4)
	#घोषणा SUN4I_SPDIF_RXCFG_CHSTSRC		BIT(3)
	#घोषणा SUN4I_SPDIF_RXCFG_CHSTCP		BIT(1)
	#घोषणा SUN4I_SPDIF_RXCFG_RXEN			BIT(0)

#घोषणा SUN4I_SPDIF_TXFIFO	(0x0C)

#घोषणा SUN4I_SPDIF_RXFIFO	(0x10)

#घोषणा SUN4I_SPDIF_FCTL	(0x14)
	#घोषणा SUN4I_SPDIF_FCTL_FIFOSRC		BIT(31)
	#घोषणा SUN4I_SPDIF_FCTL_FTX			BIT(17)
	#घोषणा SUN4I_SPDIF_FCTL_FRX			BIT(16)
	#घोषणा SUN4I_SPDIF_FCTL_TXTL(v)		((v) << 8)
	#घोषणा SUN4I_SPDIF_FCTL_TXTL_MASK		GENMASK(12, 8)
	#घोषणा SUN4I_SPDIF_FCTL_RXTL(v)		((v) << 3)
	#घोषणा SUN4I_SPDIF_FCTL_RXTL_MASK		GENMASK(7, 3)
	#घोषणा SUN4I_SPDIF_FCTL_TXIM			BIT(2)
	#घोषणा SUN4I_SPDIF_FCTL_RXOM(v)		((v) << 0)
	#घोषणा SUN4I_SPDIF_FCTL_RXOM_MASK		GENMASK(1, 0)

#घोषणा SUN50I_H6_SPDIF_FCTL (0x14)
	#घोषणा SUN50I_H6_SPDIF_FCTL_HUB_EN		BIT(31)
	#घोषणा SUN50I_H6_SPDIF_FCTL_FTX		BIT(30)
	#घोषणा SUN50I_H6_SPDIF_FCTL_FRX		BIT(29)
	#घोषणा SUN50I_H6_SPDIF_FCTL_TXTL(v)		((v) << 12)
	#घोषणा SUN50I_H6_SPDIF_FCTL_TXTL_MASK		GENMASK(19, 12)
	#घोषणा SUN50I_H6_SPDIF_FCTL_RXTL(v)		((v) << 4)
	#घोषणा SUN50I_H6_SPDIF_FCTL_RXTL_MASK		GENMASK(10, 4)
	#घोषणा SUN50I_H6_SPDIF_FCTL_TXIM		BIT(2)
	#घोषणा SUN50I_H6_SPDIF_FCTL_RXOM(v)		((v) << 0)
	#घोषणा SUN50I_H6_SPDIF_FCTL_RXOM_MASK		GENMASK(1, 0)

#घोषणा SUN4I_SPDIF_FSTA	(0x18)
	#घोषणा SUN4I_SPDIF_FSTA_TXE			BIT(14)
	#घोषणा SUN4I_SPDIF_FSTA_TXECNTSHT		(8)
	#घोषणा SUN4I_SPDIF_FSTA_RXA			BIT(6)
	#घोषणा SUN4I_SPDIF_FSTA_RXACNTSHT		(0)

#घोषणा SUN4I_SPDIF_INT		(0x1C)
	#घोषणा SUN4I_SPDIF_INT_RXLOCKEN		BIT(18)
	#घोषणा SUN4I_SPDIF_INT_RXUNLOCKEN		BIT(17)
	#घोषणा SUN4I_SPDIF_INT_RXPARERREN		BIT(16)
	#घोषणा SUN4I_SPDIF_INT_TXDRQEN			BIT(7)
	#घोषणा SUN4I_SPDIF_INT_TXUIEN			BIT(6)
	#घोषणा SUN4I_SPDIF_INT_TXOIEN			BIT(5)
	#घोषणा SUN4I_SPDIF_INT_TXEIEN			BIT(4)
	#घोषणा SUN4I_SPDIF_INT_RXDRQEN			BIT(2)
	#घोषणा SUN4I_SPDIF_INT_RXOIEN			BIT(1)
	#घोषणा SUN4I_SPDIF_INT_RXAIEN			BIT(0)

#घोषणा SUN4I_SPDIF_ISTA	(0x20)
	#घोषणा SUN4I_SPDIF_ISTA_RXLOCKSTA		BIT(18)
	#घोषणा SUN4I_SPDIF_ISTA_RXUNLOCKSTA		BIT(17)
	#घोषणा SUN4I_SPDIF_ISTA_RXPARERRSTA		BIT(16)
	#घोषणा SUN4I_SPDIF_ISTA_TXUSTA			BIT(6)
	#घोषणा SUN4I_SPDIF_ISTA_TXOSTA			BIT(5)
	#घोषणा SUN4I_SPDIF_ISTA_TXESTA			BIT(4)
	#घोषणा SUN4I_SPDIF_ISTA_RXOSTA			BIT(1)
	#घोषणा SUN4I_SPDIF_ISTA_RXASTA			BIT(0)

#घोषणा SUN8I_SPDIF_TXFIFO	(0x20)

#घोषणा SUN4I_SPDIF_TXCNT	(0x24)

#घोषणा SUN4I_SPDIF_RXCNT	(0x28)

#घोषणा SUN4I_SPDIF_TXCHSTA0	(0x2C)
	#घोषणा SUN4I_SPDIF_TXCHSTA0_CLK(v)		((v) << 28)
	#घोषणा SUN4I_SPDIF_TXCHSTA0_SAMFREQ(v)		((v) << 24)
	#घोषणा SUN4I_SPDIF_TXCHSTA0_SAMFREQ_MASK	GENMASK(27, 24)
	#घोषणा SUN4I_SPDIF_TXCHSTA0_CHNUM(v)		((v) << 20)
	#घोषणा SUN4I_SPDIF_TXCHSTA0_CHNUM_MASK		GENMASK(23, 20)
	#घोषणा SUN4I_SPDIF_TXCHSTA0_SRCNUM(v)		((v) << 16)
	#घोषणा SUN4I_SPDIF_TXCHSTA0_CATACOD(v)		((v) << 8)
	#घोषणा SUN4I_SPDIF_TXCHSTA0_MODE(v)		((v) << 6)
	#घोषणा SUN4I_SPDIF_TXCHSTA0_EMPHASIS(v)	((v) << 3)
	#घोषणा SUN4I_SPDIF_TXCHSTA0_CP			BIT(2)
	#घोषणा SUN4I_SPDIF_TXCHSTA0_AUDIO		BIT(1)
	#घोषणा SUN4I_SPDIF_TXCHSTA0_PRO		BIT(0)

#घोषणा SUN4I_SPDIF_TXCHSTA1	(0x30)
	#घोषणा SUN4I_SPDIF_TXCHSTA1_CGMSA(v)		((v) << 8)
	#घोषणा SUN4I_SPDIF_TXCHSTA1_ORISAMFREQ(v)	((v) << 4)
	#घोषणा SUN4I_SPDIF_TXCHSTA1_ORISAMFREQ_MASK	GENMASK(7, 4)
	#घोषणा SUN4I_SPDIF_TXCHSTA1_SAMWORDLEN(v)	((v) << 1)
	#घोषणा SUN4I_SPDIF_TXCHSTA1_MAXWORDLEN		BIT(0)

#घोषणा SUN4I_SPDIF_RXCHSTA0	(0x34)
	#घोषणा SUN4I_SPDIF_RXCHSTA0_CLK(v)		((v) << 28)
	#घोषणा SUN4I_SPDIF_RXCHSTA0_SAMFREQ(v)		((v) << 24)
	#घोषणा SUN4I_SPDIF_RXCHSTA0_CHNUM(v)		((v) << 20)
	#घोषणा SUN4I_SPDIF_RXCHSTA0_SRCNUM(v)		((v) << 16)
	#घोषणा SUN4I_SPDIF_RXCHSTA0_CATACOD(v)		((v) << 8)
	#घोषणा SUN4I_SPDIF_RXCHSTA0_MODE(v)		((v) << 6)
	#घोषणा SUN4I_SPDIF_RXCHSTA0_EMPHASIS(v)	((v) << 3)
	#घोषणा SUN4I_SPDIF_RXCHSTA0_CP			BIT(2)
	#घोषणा SUN4I_SPDIF_RXCHSTA0_AUDIO		BIT(1)
	#घोषणा SUN4I_SPDIF_RXCHSTA0_PRO		BIT(0)

#घोषणा SUN4I_SPDIF_RXCHSTA1	(0x38)
	#घोषणा SUN4I_SPDIF_RXCHSTA1_CGMSA(v)		((v) << 8)
	#घोषणा SUN4I_SPDIF_RXCHSTA1_ORISAMFREQ(v)	((v) << 4)
	#घोषणा SUN4I_SPDIF_RXCHSTA1_SAMWORDLEN(v)	((v) << 1)
	#घोषणा SUN4I_SPDIF_RXCHSTA1_MAXWORDLEN		BIT(0)

/* Defines क्रम Sampling Frequency */
#घोषणा SUN4I_SPDIF_SAMFREQ_44_1KHZ		0x0
#घोषणा SUN4I_SPDIF_SAMFREQ_NOT_INDICATED	0x1
#घोषणा SUN4I_SPDIF_SAMFREQ_48KHZ		0x2
#घोषणा SUN4I_SPDIF_SAMFREQ_32KHZ		0x3
#घोषणा SUN4I_SPDIF_SAMFREQ_22_05KHZ		0x4
#घोषणा SUN4I_SPDIF_SAMFREQ_24KHZ		0x6
#घोषणा SUN4I_SPDIF_SAMFREQ_88_2KHZ		0x8
#घोषणा SUN4I_SPDIF_SAMFREQ_76_8KHZ		0x9
#घोषणा SUN4I_SPDIF_SAMFREQ_96KHZ		0xa
#घोषणा SUN4I_SPDIF_SAMFREQ_176_4KHZ		0xc
#घोषणा SUN4I_SPDIF_SAMFREQ_192KHZ		0xe

/**
 * काष्ठा sun4i_spdअगर_quirks - Dअगरferences between SoC variants.
 *
 * @reg_dac_txdata: TX FIFO offset क्रम DMA config.
 * @has_reset: SoC needs reset deनिश्चितed.
 * @val_fctl_ftx: TX FIFO flush biपंचांगask.
 */
काष्ठा sun4i_spdअगर_quirks अणु
	अचिन्हित पूर्णांक reg_dac_txdata;
	bool has_reset;
	अचिन्हित पूर्णांक val_fctl_ftx;
पूर्ण;

काष्ठा sun4i_spdअगर_dev अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा clk *spdअगर_clk;
	काष्ठा clk *apb_clk;
	काष्ठा reset_control *rst;
	काष्ठा snd_soc_dai_driver cpu_dai_drv;
	काष्ठा regmap *regmap;
	काष्ठा snd_dmaengine_dai_dma_data dma_params_tx;
	स्थिर काष्ठा sun4i_spdअगर_quirks *quirks;
पूर्ण;

अटल व्योम sun4i_spdअगर_configure(काष्ठा sun4i_spdअगर_dev *host)
अणु
	स्थिर काष्ठा sun4i_spdअगर_quirks *quirks = host->quirks;

	/* soft reset SPDIF */
	regmap_ग_लिखो(host->regmap, SUN4I_SPDIF_CTL, SUN4I_SPDIF_CTL_RESET);

	/* flush TX FIFO */
	regmap_update_bits(host->regmap, SUN4I_SPDIF_FCTL,
			   quirks->val_fctl_ftx, quirks->val_fctl_ftx);

	/* clear TX counter */
	regmap_ग_लिखो(host->regmap, SUN4I_SPDIF_TXCNT, 0);
पूर्ण

अटल व्योम sun4i_snd_txctrl_on(काष्ठा snd_pcm_substream *substream,
				काष्ठा sun4i_spdअगर_dev *host)
अणु
	अगर (substream->runसमय->channels == 1)
		regmap_update_bits(host->regmap, SUN4I_SPDIF_TXCFG,
				   SUN4I_SPDIF_TXCFG_SINGLEMOD,
				   SUN4I_SPDIF_TXCFG_SINGLEMOD);

	/* SPDIF TX ENABLE */
	regmap_update_bits(host->regmap, SUN4I_SPDIF_TXCFG,
			   SUN4I_SPDIF_TXCFG_TXEN, SUN4I_SPDIF_TXCFG_TXEN);

	/* DRQ ENABLE */
	regmap_update_bits(host->regmap, SUN4I_SPDIF_INT,
			   SUN4I_SPDIF_INT_TXDRQEN, SUN4I_SPDIF_INT_TXDRQEN);

	/* Global enable */
	regmap_update_bits(host->regmap, SUN4I_SPDIF_CTL,
			   SUN4I_SPDIF_CTL_GEN, SUN4I_SPDIF_CTL_GEN);
पूर्ण

अटल व्योम sun4i_snd_txctrl_off(काष्ठा snd_pcm_substream *substream,
				 काष्ठा sun4i_spdअगर_dev *host)
अणु
	/* SPDIF TX DISABLE */
	regmap_update_bits(host->regmap, SUN4I_SPDIF_TXCFG,
			   SUN4I_SPDIF_TXCFG_TXEN, 0);

	/* DRQ DISABLE */
	regmap_update_bits(host->regmap, SUN4I_SPDIF_INT,
			   SUN4I_SPDIF_INT_TXDRQEN, 0);

	/* Global disable */
	regmap_update_bits(host->regmap, SUN4I_SPDIF_CTL,
			   SUN4I_SPDIF_CTL_GEN, 0);
पूर्ण

अटल पूर्णांक sun4i_spdअगर_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा sun4i_spdअगर_dev *host = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));

	अगर (substream->stream != SNDRV_PCM_STREAM_PLAYBACK)
		वापस -EINVAL;

	sun4i_spdअगर_configure(host);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_spdअगर_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *cpu_dai)
अणु
	पूर्णांक ret = 0;
	पूर्णांक fmt;
	अचिन्हित दीर्घ rate = params_rate(params);
	u32 mclk_भाग = 0;
	अचिन्हित पूर्णांक mclk = 0;
	u32 reg_val;
	काष्ठा sun4i_spdअगर_dev *host = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा platक्रमm_device *pdev = host->pdev;

	/* Add the PCM and raw data select पूर्णांकerface */
	चयन (params_channels(params)) अणु
	हाल 1: /* PCM mode */
	हाल 2:
		fmt = 0;
		अवरोध;
	हाल 4: /* raw data mode */
		fmt = SUN4I_SPDIF_TXCFG_NONAUDIO;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		fmt |= SUN4I_SPDIF_TXCFG_FMT16BIT;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S20_3LE:
		fmt |= SUN4I_SPDIF_TXCFG_FMT20BIT;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		fmt |= SUN4I_SPDIF_TXCFG_FMT24BIT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (rate) अणु
	हाल 22050:
	हाल 44100:
	हाल 88200:
	हाल 176400:
		mclk = 22579200;
		अवरोध;
	हाल 24000:
	हाल 32000:
	हाल 48000:
	हाल 96000:
	हाल 192000:
		mclk = 24576000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = clk_set_rate(host->spdअगर_clk, mclk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"Setting SPDIF clock rate for %d Hz failed!\n", mclk);
		वापस ret;
	पूर्ण

	regmap_update_bits(host->regmap, SUN4I_SPDIF_FCTL,
			   SUN4I_SPDIF_FCTL_TXIM, SUN4I_SPDIF_FCTL_TXIM);

	चयन (rate) अणु
	हाल 22050:
	हाल 24000:
		mclk_भाग = 8;
		अवरोध;
	हाल 32000:
		mclk_भाग = 6;
		अवरोध;
	हाल 44100:
	हाल 48000:
		mclk_भाग = 4;
		अवरोध;
	हाल 88200:
	हाल 96000:
		mclk_भाग = 2;
		अवरोध;
	हाल 176400:
	हाल 192000:
		mclk_भाग = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	reg_val = 0;
	reg_val |= SUN4I_SPDIF_TXCFG_ASS;
	reg_val |= fmt; /* set non audio and bit depth */
	reg_val |= SUN4I_SPDIF_TXCFG_CHSTMODE;
	reg_val |= SUN4I_SPDIF_TXCFG_TXRATIO(mclk_भाग - 1);
	regmap_ग_लिखो(host->regmap, SUN4I_SPDIF_TXCFG, reg_val);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_spdअगर_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			       काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret = 0;
	काष्ठा sun4i_spdअगर_dev *host = snd_soc_dai_get_drvdata(dai);

	अगर (substream->stream != SNDRV_PCM_STREAM_PLAYBACK)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		sun4i_snd_txctrl_on(substream, host);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		sun4i_snd_txctrl_off(substream, host);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_spdअगर_soc_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sun4i_spdअगर_dev *host = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, &host->dma_params_tx, शून्य);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops sun4i_spdअगर_dai_ops = अणु
	.startup	= sun4i_spdअगर_startup,
	.trigger	= sun4i_spdअगर_trigger,
	.hw_params	= sun4i_spdअगर_hw_params,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun4i_spdअगर_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = SUN4I_SPDIF_RXCHSTA1,
पूर्ण;

#घोषणा SUN4I_RATES	SNDRV_PCM_RATE_8000_192000

#घोषणा SUN4I_FORMATS	(SNDRV_PCM_FORMAT_S16_LE | \
				SNDRV_PCM_FORMAT_S20_3LE | \
				SNDRV_PCM_FORMAT_S24_LE)

अटल काष्ठा snd_soc_dai_driver sun4i_spdअगर_dai = अणु
	.playback = अणु
		.channels_min = 1,
		.channels_max = 2,
		.rates = SUN4I_RATES,
		.क्रमmats = SUN4I_FORMATS,
	पूर्ण,
	.probe = sun4i_spdअगर_soc_dai_probe,
	.ops = &sun4i_spdअगर_dai_ops,
	.name = "spdif",
पूर्ण;

अटल स्थिर काष्ठा sun4i_spdअगर_quirks sun4i_a10_spdअगर_quirks = अणु
	.reg_dac_txdata	= SUN4I_SPDIF_TXFIFO,
	.val_fctl_ftx   = SUN4I_SPDIF_FCTL_FTX,
पूर्ण;

अटल स्थिर काष्ठा sun4i_spdअगर_quirks sun6i_a31_spdअगर_quirks = अणु
	.reg_dac_txdata	= SUN4I_SPDIF_TXFIFO,
	.val_fctl_ftx   = SUN4I_SPDIF_FCTL_FTX,
	.has_reset	= true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_spdअगर_quirks sun8i_h3_spdअगर_quirks = अणु
	.reg_dac_txdata	= SUN8I_SPDIF_TXFIFO,
	.val_fctl_ftx   = SUN4I_SPDIF_FCTL_FTX,
	.has_reset	= true,
पूर्ण;

अटल स्थिर काष्ठा sun4i_spdअगर_quirks sun50i_h6_spdअगर_quirks = अणु
	.reg_dac_txdata = SUN8I_SPDIF_TXFIFO,
	.val_fctl_ftx   = SUN50I_H6_SPDIF_FCTL_FTX,
	.has_reset      = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun4i_spdअगर_of_match[] = अणु
	अणु
		.compatible = "allwinner,sun4i-a10-spdif",
		.data = &sun4i_a10_spdअगर_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun6i-a31-spdif",
		.data = &sun6i_a31_spdअगर_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun8i-h3-spdif",
		.data = &sun8i_h3_spdअगर_quirks,
	पूर्ण,
	अणु
		.compatible = "allwinner,sun50i-h6-spdif",
		.data = &sun50i_h6_spdअगर_quirks,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun4i_spdअगर_of_match);

अटल स्थिर काष्ठा snd_soc_component_driver sun4i_spdअगर_component = अणु
	.name		= "sun4i-spdif",
पूर्ण;

अटल पूर्णांक sun4i_spdअगर_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sun4i_spdअगर_dev *host  = dev_get_drvdata(dev);

	clk_disable_unprepare(host->spdअगर_clk);
	clk_disable_unprepare(host->apb_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_spdअगर_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sun4i_spdअगर_dev *host  = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(host->spdअगर_clk);
	अगर (ret)
		वापस ret;
	ret = clk_prepare_enable(host->apb_clk);
	अगर (ret)
		clk_disable_unprepare(host->spdअगर_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_spdअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun4i_spdअगर_dev *host;
	काष्ठा resource *res;
	स्थिर काष्ठा sun4i_spdअगर_quirks *quirks;
	पूर्णांक ret;
	व्योम __iomem *base;

	dev_dbg(&pdev->dev, "Entered %s\n", __func__);

	host = devm_kzalloc(&pdev->dev, माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;

	host->pdev = pdev;

	/* Initialize this copy of the CPU DAI driver काष्ठाure */
	स_नकल(&host->cpu_dai_drv, &sun4i_spdअगर_dai, माप(sun4i_spdअगर_dai));
	host->cpu_dai_drv.name = dev_name(&pdev->dev);

	/* Get the addresses */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	quirks = of_device_get_match_data(&pdev->dev);
	अगर (quirks == शून्य) अणु
		dev_err(&pdev->dev, "Failed to determine the quirks to use\n");
		वापस -ENODEV;
	पूर्ण
	host->quirks = quirks;

	host->regmap = devm_regmap_init_mmio(&pdev->dev, base,
						&sun4i_spdअगर_regmap_config);

	/* Clocks */
	host->apb_clk = devm_clk_get(&pdev->dev, "apb");
	अगर (IS_ERR(host->apb_clk)) अणु
		dev_err(&pdev->dev, "failed to get a apb clock.\n");
		वापस PTR_ERR(host->apb_clk);
	पूर्ण

	host->spdअगर_clk = devm_clk_get(&pdev->dev, "spdif");
	अगर (IS_ERR(host->spdअगर_clk)) अणु
		dev_err(&pdev->dev, "failed to get a spdif clock.\n");
		वापस PTR_ERR(host->spdअगर_clk);
	पूर्ण

	host->dma_params_tx.addr = res->start + quirks->reg_dac_txdata;
	host->dma_params_tx.maxburst = 8;
	host->dma_params_tx.addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;

	platक्रमm_set_drvdata(pdev, host);

	अगर (quirks->has_reset) अणु
		host->rst = devm_reset_control_get_optional_exclusive(&pdev->dev,
								      शून्य);
		अगर (PTR_ERR(host->rst) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			dev_err(&pdev->dev, "Failed to get reset: %d\n", ret);
			वापस ret;
		पूर्ण
		अगर (!IS_ERR(host->rst))
			reset_control_deनिश्चित(host->rst);
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
				&sun4i_spdअगर_component, &sun4i_spdअगर_dai, 1);
	अगर (ret)
		वापस ret;

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = sun4i_spdअगर_runसमय_resume(&pdev->dev);
		अगर (ret)
			जाओ err_unरेजिस्टर;
	पूर्ण

	ret = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य, 0);
	अगर (ret)
		जाओ err_suspend;
	वापस 0;
err_suspend:
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		sun4i_spdअगर_runसमय_suspend(&pdev->dev);
err_unरेजिस्टर:
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_spdअगर_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		sun4i_spdअगर_runसमय_suspend(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sun4i_spdअगर_pm = अणु
	SET_RUNTIME_PM_OPS(sun4i_spdअगर_runसमय_suspend,
			   sun4i_spdअगर_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sun4i_spdअगर_driver = अणु
	.driver		= अणु
		.name	= "sun4i-spdif",
		.of_match_table = of_match_ptr(sun4i_spdअगर_of_match),
		.pm	= &sun4i_spdअगर_pm,
	पूर्ण,
	.probe		= sun4i_spdअगर_probe,
	.हटाओ		= sun4i_spdअगर_हटाओ,
पूर्ण;

module_platक्रमm_driver(sun4i_spdअगर_driver);

MODULE_AUTHOR("Marcus Cooper <codekipper@gmail.com>");
MODULE_AUTHOR("Andrea Venturi <be17068@iperbole.bo.it>");
MODULE_DESCRIPTION("Allwinner sun4i SPDIF SoC Interface");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:sun4i-spdif");
