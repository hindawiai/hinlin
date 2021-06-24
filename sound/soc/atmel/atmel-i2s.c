<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Aपंचांगel I2S controller
 *
 * Copyright (C) 2015 Aपंचांगel Corporation
 *
 * Author: Cyrille Pitchen <cyrille.pitchen@aपंचांगel.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/mfd/syscon.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#घोषणा ATMEL_I2SC_MAX_TDM_CHANNELS	8

/*
 * ---- I2S Controller Register map ----
 */
#घोषणा ATMEL_I2SC_CR		0x0000	/* Control Register */
#घोषणा ATMEL_I2SC_MR		0x0004	/* Mode Register */
#घोषणा ATMEL_I2SC_SR		0x0008	/* Status Register */
#घोषणा ATMEL_I2SC_SCR		0x000c	/* Status Clear Register */
#घोषणा ATMEL_I2SC_SSR		0x0010	/* Status Set Register */
#घोषणा ATMEL_I2SC_IER		0x0014	/* Interrupt Enable Register */
#घोषणा ATMEL_I2SC_IDR		0x0018	/* Interrupt Disable Register */
#घोषणा ATMEL_I2SC_IMR		0x001c	/* Interrupt Mask Register */
#घोषणा ATMEL_I2SC_RHR		0x0020	/* Receiver Holding Register */
#घोषणा ATMEL_I2SC_THR		0x0024	/* Transmitter Holding Register */
#घोषणा ATMEL_I2SC_VERSION	0x0028	/* Version Register */

/*
 * ---- Control Register (Write-only) ----
 */
#घोषणा ATMEL_I2SC_CR_RXEN	BIT(0)	/* Receiver Enable */
#घोषणा ATMEL_I2SC_CR_RXDIS	BIT(1)	/* Receiver Disable */
#घोषणा ATMEL_I2SC_CR_CKEN	BIT(2)	/* Clock Enable */
#घोषणा ATMEL_I2SC_CR_CKDIS	BIT(3)	/* Clock Disable */
#घोषणा ATMEL_I2SC_CR_TXEN	BIT(4)	/* Transmitter Enable */
#घोषणा ATMEL_I2SC_CR_TXDIS	BIT(5)	/* Transmitter Disable */
#घोषणा ATMEL_I2SC_CR_SWRST	BIT(7)	/* Software Reset */

/*
 * ---- Mode Register (Read/Write) ----
 */
#घोषणा ATMEL_I2SC_MR_MODE_MASK		GENMASK(0, 0)
#घोषणा ATMEL_I2SC_MR_MODE_SLAVE	(0 << 0)
#घोषणा ATMEL_I2SC_MR_MODE_MASTER	(1 << 0)

#घोषणा ATMEL_I2SC_MR_DATALENGTH_MASK		GENMASK(4, 2)
#घोषणा ATMEL_I2SC_MR_DATALENGTH_32_BITS	(0 << 2)
#घोषणा ATMEL_I2SC_MR_DATALENGTH_24_BITS	(1 << 2)
#घोषणा ATMEL_I2SC_MR_DATALENGTH_20_BITS	(2 << 2)
#घोषणा ATMEL_I2SC_MR_DATALENGTH_18_BITS	(3 << 2)
#घोषणा ATMEL_I2SC_MR_DATALENGTH_16_BITS	(4 << 2)
#घोषणा ATMEL_I2SC_MR_DATALENGTH_16_BITS_COMPACT	(5 << 2)
#घोषणा ATMEL_I2SC_MR_DATALENGTH_8_BITS		(6 << 2)
#घोषणा ATMEL_I2SC_MR_DATALENGTH_8_BITS_COMPACT	(7 << 2)

#घोषणा ATMEL_I2SC_MR_FORMAT_MASK	GENMASK(7, 6)
#घोषणा ATMEL_I2SC_MR_FORMAT_I2S	(0 << 6)
#घोषणा ATMEL_I2SC_MR_FORMAT_LJ		(1 << 6)  /* Left Justअगरied */
#घोषणा ATMEL_I2SC_MR_FORMAT_TDM	(2 << 6)
#घोषणा ATMEL_I2SC_MR_FORMAT_TDMLJ	(3 << 6)

/* Left audio samples duplicated to right audio channel */
#घोषणा ATMEL_I2SC_MR_RXMONO		BIT(8)

/* Receiver uses one DMA channel ... */
#घोषणा ATMEL_I2SC_MR_RXDMA_MASK	GENMASK(9, 9)
#घोषणा ATMEL_I2SC_MR_RXDMA_SINGLE	(0 << 9)  /* क्रम all audio channels */
#घोषणा ATMEL_I2SC_MR_RXDMA_MULTIPLE	(1 << 9)  /* per audio channel */

/* I2SDO output of I2SC is पूर्णांकernally connected to I2SDI input */
#घोषणा ATMEL_I2SC_MR_RXLOOP		BIT(10)

/* Left audio samples duplicated to right audio channel */
#घोषणा ATMEL_I2SC_MR_TXMONO		BIT(12)

/* Transmitter uses one DMA channel ... */
#घोषणा ATMEL_I2SC_MR_TXDMA_MASK	GENMASK(13, 13)
#घोषणा ATMEL_I2SC_MR_TXDMA_SINGLE	(0 << 13)  /* क्रम all audio channels */
#घोषणा ATMEL_I2SC_MR_TXDME_MULTIPLE	(1 << 13)  /* per audio channel */

/* x sample transmitted when underrun */
#घोषणा ATMEL_I2SC_MR_TXSAME_MASK	GENMASK(14, 14)
#घोषणा ATMEL_I2SC_MR_TXSAME_ZERO	(0 << 14)  /* Zero sample */
#घोषणा ATMEL_I2SC_MR_TXSAME_PREVIOUS	(1 << 14)  /* Previous sample */

/* Audio Clock to I2SC Master Clock ratio */
#घोषणा ATMEL_I2SC_MR_IMCKDIV_MASK	GENMASK(21, 16)
#घोषणा ATMEL_I2SC_MR_IMCKDIV(भाग) \
	(((भाग) << 16) & ATMEL_I2SC_MR_IMCKDIV_MASK)

/* Master Clock to fs ratio */
#घोषणा ATMEL_I2SC_MR_IMCKFS_MASK	GENMASK(29, 24)
#घोषणा ATMEL_I2SC_MR_IMCKFS(fs) \
	(((fs) << 24) & ATMEL_I2SC_MR_IMCKFS_MASK)

/* Master Clock mode */
#घोषणा ATMEL_I2SC_MR_IMCKMODE_MASK	GENMASK(30, 30)
/* 0: No master घड़ी generated (selected घड़ी drives I2SCK pin) */
#घोषणा ATMEL_I2SC_MR_IMCKMODE_I2SCK	(0 << 30)
/* 1: master घड़ी generated (पूर्णांकernally generated घड़ी drives I2SMCK pin) */
#घोषणा ATMEL_I2SC_MR_IMCKMODE_I2SMCK	(1 << 30)

/* Slot Width */
/* 0: slot is 32 bits wide क्रम DATALENGTH = 18/20/24 bits. */
/* 1: slot is 24 bits wide क्रम DATALENGTH = 18/20/24 bits. */
#घोषणा ATMEL_I2SC_MR_IWS		BIT(31)

/*
 * ---- Status Registers ----
 */
#घोषणा ATMEL_I2SC_SR_RXEN	BIT(0)	/* Receiver Enabled */
#घोषणा ATMEL_I2SC_SR_RXRDY	BIT(1)	/* Receive Ready */
#घोषणा ATMEL_I2SC_SR_RXOR	BIT(2)	/* Receive Overrun */

#घोषणा ATMEL_I2SC_SR_TXEN	BIT(4)	/* Transmitter Enabled */
#घोषणा ATMEL_I2SC_SR_TXRDY	BIT(5)	/* Transmit Ready */
#घोषणा ATMEL_I2SC_SR_TXUR	BIT(6)	/* Transmit Underrun */

/* Receive Overrun Channel */
#घोषणा ATMEL_I2SC_SR_RXORCH_MASK	GENMASK(15, 8)
#घोषणा ATMEL_I2SC_SR_RXORCH(ch)	(1 << (((ch) & 0x7) + 8))

/* Transmit Underrun Channel */
#घोषणा ATMEL_I2SC_SR_TXURCH_MASK	GENMASK(27, 20)
#घोषणा ATMEL_I2SC_SR_TXURCH(ch)	(1 << (((ch) & 0x7) + 20))

/*
 * ---- Interrupt Enable/Disable/Mask Registers ----
 */
#घोषणा ATMEL_I2SC_INT_RXRDY	ATMEL_I2SC_SR_RXRDY
#घोषणा ATMEL_I2SC_INT_RXOR	ATMEL_I2SC_SR_RXOR
#घोषणा ATMEL_I2SC_INT_TXRDY	ATMEL_I2SC_SR_TXRDY
#घोषणा ATMEL_I2SC_INT_TXUR	ATMEL_I2SC_SR_TXUR

अटल स्थिर काष्ठा regmap_config aपंचांगel_i2s_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = ATMEL_I2SC_VERSION,
पूर्ण;

काष्ठा aपंचांगel_i2s_gck_param अणु
	पूर्णांक		fs;
	अचिन्हित दीर्घ	mck;
	पूर्णांक		imckभाग;
	पूर्णांक		imckfs;
पूर्ण;

#घोषणा I2S_MCK_12M288		12288000UL
#घोषणा I2S_MCK_11M2896		11289600UL

/* mck = (32 * (imckfs+1) / (imckभाग+1)) * fs */
अटल स्थिर काष्ठा aपंचांगel_i2s_gck_param gck_params[] = अणु
	/* mck = 12.288MHz */
	अणु  8000, I2S_MCK_12M288, 0, 47पूर्ण,	/* mck = 1536 fs */
	अणु 16000, I2S_MCK_12M288, 1, 47पूर्ण,	/* mck =  768 fs */
	अणु 24000, I2S_MCK_12M288, 3, 63पूर्ण,	/* mck =  512 fs */
	अणु 32000, I2S_MCK_12M288, 3, 47पूर्ण,	/* mck =  384 fs */
	अणु 48000, I2S_MCK_12M288, 7, 63पूर्ण,	/* mck =  256 fs */
	अणु 64000, I2S_MCK_12M288, 7, 47पूर्ण,	/* mck =  192 fs */
	अणु 96000, I2S_MCK_12M288, 7, 31पूर्ण,	/* mck =  128 fs */
	अणु192000, I2S_MCK_12M288, 7, 15पूर्ण,	/* mck =   64 fs */

	/* mck = 11.2896MHz */
	अणु 11025, I2S_MCK_11M2896, 1, 63पूर्ण,	/* mck = 1024 fs */
	अणु 22050, I2S_MCK_11M2896, 3, 63पूर्ण,	/* mck =  512 fs */
	अणु 44100, I2S_MCK_11M2896, 7, 63पूर्ण,	/* mck =  256 fs */
	अणु 88200, I2S_MCK_11M2896, 7, 31पूर्ण,	/* mck =  128 fs */
	अणु176400, I2S_MCK_11M2896, 7, 15पूर्ण,	/* mck =   64 fs */
पूर्ण;

काष्ठा aपंचांगel_i2s_dev;

काष्ठा aपंचांगel_i2s_caps अणु
	पूर्णांक	(*mck_init)(काष्ठा aपंचांगel_i2s_dev *, काष्ठा device_node *np);
पूर्ण;

काष्ठा aपंचांगel_i2s_dev अणु
	काष्ठा device				*dev;
	काष्ठा regmap				*regmap;
	काष्ठा clk				*pclk;
	काष्ठा clk				*gclk;
	काष्ठा snd_dmaengine_dai_dma_data	playback;
	काष्ठा snd_dmaengine_dai_dma_data	capture;
	अचिन्हित पूर्णांक				fmt;
	स्थिर काष्ठा aपंचांगel_i2s_gck_param	*gck_param;
	स्थिर काष्ठा aपंचांगel_i2s_caps		*caps;
पूर्ण;

अटल irqवापस_t aपंचांगel_i2s_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा aपंचांगel_i2s_dev *dev = dev_id;
	अचिन्हित पूर्णांक sr, imr, pending, ch, mask;
	irqवापस_t ret = IRQ_NONE;

	regmap_पढ़ो(dev->regmap, ATMEL_I2SC_SR, &sr);
	regmap_पढ़ो(dev->regmap, ATMEL_I2SC_IMR, &imr);
	pending = sr & imr;

	अगर (!pending)
		वापस IRQ_NONE;

	अगर (pending & ATMEL_I2SC_INT_RXOR) अणु
		mask = ATMEL_I2SC_SR_RXOR;

		क्रम (ch = 0; ch < ATMEL_I2SC_MAX_TDM_CHANNELS; ++ch) अणु
			अगर (sr & ATMEL_I2SC_SR_RXORCH(ch)) अणु
				mask |= ATMEL_I2SC_SR_RXORCH(ch);
				dev_err(dev->dev,
					"RX overrun on channel %d\n", ch);
			पूर्ण
		पूर्ण
		regmap_ग_लिखो(dev->regmap, ATMEL_I2SC_SCR, mask);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (pending & ATMEL_I2SC_INT_TXUR) अणु
		mask = ATMEL_I2SC_SR_TXUR;

		क्रम (ch = 0; ch < ATMEL_I2SC_MAX_TDM_CHANNELS; ++ch) अणु
			अगर (sr & ATMEL_I2SC_SR_TXURCH(ch)) अणु
				mask |= ATMEL_I2SC_SR_TXURCH(ch);
				dev_err(dev->dev,
					"TX underrun on channel %d\n", ch);
			पूर्ण
		पूर्ण
		regmap_ग_लिखो(dev->regmap, ATMEL_I2SC_SCR, mask);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा ATMEL_I2S_RATES		SNDRV_PCM_RATE_8000_192000

#घोषणा ATMEL_I2S_FORMATS	(SNDRV_PCM_FMTBIT_S8 |		\
				 SNDRV_PCM_FMTBIT_S16_LE |	\
				 SNDRV_PCM_FMTBIT_S18_3LE |	\
				 SNDRV_PCM_FMTBIT_S20_3LE |	\
				 SNDRV_PCM_FMTBIT_S24_3LE |	\
				 SNDRV_PCM_FMTBIT_S24_LE |	\
				 SNDRV_PCM_FMTBIT_S32_LE)

अटल पूर्णांक aपंचांगel_i2s_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा aपंचांगel_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);

	dev->fmt = fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_i2s_prepare(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा aपंचांगel_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);
	bool is_playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	अचिन्हित पूर्णांक rhr, sr = 0;

	अगर (is_playback) अणु
		regmap_पढ़ो(dev->regmap, ATMEL_I2SC_SR, &sr);
		अगर (sr & ATMEL_I2SC_SR_RXRDY) अणु
			/*
			 * The RX Ready flag should not be set. However अगर here,
			 * we flush (पढ़ो) the Receive Holding Register to start
			 * from a clean state.
			 */
			dev_dbg(dev->dev, "RXRDY is set\n");
			regmap_पढ़ो(dev->regmap, ATMEL_I2SC_RHR, &rhr);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_i2s_get_gck_param(काष्ठा aपंचांगel_i2s_dev *dev, पूर्णांक fs)
अणु
	पूर्णांक i, best;

	अगर (!dev->gclk) अणु
		dev_err(dev->dev, "cannot generate the I2S Master Clock\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Find the best possible settings to generate the I2S Master Clock
	 * from the PLL Audio.
	 */
	dev->gck_param = शून्य;
	best = पूर्णांक_उच्च;
	क्रम (i = 0; i < ARRAY_SIZE(gck_params); ++i) अणु
		स्थिर काष्ठा aपंचांगel_i2s_gck_param *gck_param = &gck_params[i];
		पूर्णांक val = असल(fs - gck_param->fs);

		अगर (val < best) अणु
			best = val;
			dev->gck_param = gck_param;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *params,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा aपंचांगel_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);
	bool is_playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	अचिन्हित पूर्णांक mr = 0;
	पूर्णांक ret;

	चयन (dev->fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		mr |= ATMEL_I2SC_MR_FORMAT_I2S;
		अवरोध;

	शेष:
		dev_err(dev->dev, "unsupported bus format\n");
		वापस -EINVAL;
	पूर्ण

	चयन (dev->fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/* codec is slave, so cpu is master */
		mr |= ATMEL_I2SC_MR_MODE_MASTER;
		ret = aपंचांगel_i2s_get_gck_param(dev, params_rate(params));
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* codec is master, so cpu is slave */
		mr |= ATMEL_I2SC_MR_MODE_SLAVE;
		dev->gck_param = शून्य;
		अवरोध;

	शेष:
		dev_err(dev->dev, "unsupported master/slave mode\n");
		वापस -EINVAL;
	पूर्ण

	चयन (params_channels(params)) अणु
	हाल 1:
		अगर (is_playback)
			mr |= ATMEL_I2SC_MR_TXMONO;
		अन्यथा
			mr |= ATMEL_I2SC_MR_RXMONO;
		अवरोध;
	हाल 2:
		अवरोध;
	शेष:
		dev_err(dev->dev, "unsupported number of audio channels\n");
		वापस -EINVAL;
	पूर्ण

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S8:
		mr |= ATMEL_I2SC_MR_DATALENGTH_8_BITS;
		अवरोध;

	हाल SNDRV_PCM_FORMAT_S16_LE:
		mr |= ATMEL_I2SC_MR_DATALENGTH_16_BITS;
		अवरोध;

	हाल SNDRV_PCM_FORMAT_S18_3LE:
		mr |= ATMEL_I2SC_MR_DATALENGTH_18_BITS | ATMEL_I2SC_MR_IWS;
		अवरोध;

	हाल SNDRV_PCM_FORMAT_S20_3LE:
		mr |= ATMEL_I2SC_MR_DATALENGTH_20_BITS | ATMEL_I2SC_MR_IWS;
		अवरोध;

	हाल SNDRV_PCM_FORMAT_S24_3LE:
		mr |= ATMEL_I2SC_MR_DATALENGTH_24_BITS | ATMEL_I2SC_MR_IWS;
		अवरोध;

	हाल SNDRV_PCM_FORMAT_S24_LE:
		mr |= ATMEL_I2SC_MR_DATALENGTH_24_BITS;
		अवरोध;

	हाल SNDRV_PCM_FORMAT_S32_LE:
		mr |= ATMEL_I2SC_MR_DATALENGTH_32_BITS;
		अवरोध;

	शेष:
		dev_err(dev->dev, "unsupported size/endianness for audio samples\n");
		वापस -EINVAL;
	पूर्ण

	वापस regmap_ग_लिखो(dev->regmap, ATMEL_I2SC_MR, mr);
पूर्ण

अटल पूर्णांक aपंचांगel_i2s_चयन_mck_generator(काष्ठा aपंचांगel_i2s_dev *dev,
					  bool enabled)
अणु
	अचिन्हित पूर्णांक mr, mr_mask;
	अचिन्हित दीर्घ gclk_rate;
	पूर्णांक ret;

	mr = 0;
	mr_mask = (ATMEL_I2SC_MR_IMCKDIV_MASK |
		   ATMEL_I2SC_MR_IMCKFS_MASK |
		   ATMEL_I2SC_MR_IMCKMODE_MASK);

	अगर (!enabled) अणु
		/* Disable the I2S Master Clock generator. */
		ret = regmap_ग_लिखो(dev->regmap, ATMEL_I2SC_CR,
				   ATMEL_I2SC_CR_CKDIS);
		अगर (ret)
			वापस ret;

		/* Reset the I2S Master Clock generator settings. */
		ret = regmap_update_bits(dev->regmap, ATMEL_I2SC_MR,
					 mr_mask, mr);
		अगर (ret)
			वापस ret;

		/* Disable/unprepare the PMC generated घड़ी. */
		clk_disable_unprepare(dev->gclk);

		वापस 0;
	पूर्ण

	अगर (!dev->gck_param)
		वापस -EINVAL;

	gclk_rate = dev->gck_param->mck * (dev->gck_param->imckभाग + 1);

	ret = clk_set_rate(dev->gclk, gclk_rate);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(dev->gclk);
	अगर (ret)
		वापस ret;

	/* Update the Mode Register to generate the I2S Master Clock. */
	mr |= ATMEL_I2SC_MR_IMCKDIV(dev->gck_param->imckभाग);
	mr |= ATMEL_I2SC_MR_IMCKFS(dev->gck_param->imckfs);
	mr |= ATMEL_I2SC_MR_IMCKMODE_I2SMCK;
	ret = regmap_update_bits(dev->regmap, ATMEL_I2SC_MR, mr_mask, mr);
	अगर (ret)
		वापस ret;

	/* Finally enable the I2S Master Clock generator. */
	वापस regmap_ग_लिखो(dev->regmap, ATMEL_I2SC_CR,
			    ATMEL_I2SC_CR_CKEN);
पूर्ण

अटल पूर्णांक aपंचांगel_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा aपंचांगel_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);
	bool is_playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	bool is_master, mck_enabled;
	अचिन्हित पूर्णांक cr, mr;
	पूर्णांक err;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		cr = is_playback ? ATMEL_I2SC_CR_TXEN : ATMEL_I2SC_CR_RXEN;
		mck_enabled = true;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		cr = is_playback ? ATMEL_I2SC_CR_TXDIS : ATMEL_I2SC_CR_RXDIS;
		mck_enabled = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Read the Mode Register to retrieve the master/slave state. */
	err = regmap_पढ़ो(dev->regmap, ATMEL_I2SC_MR, &mr);
	अगर (err)
		वापस err;
	is_master = (mr & ATMEL_I2SC_MR_MODE_MASK) == ATMEL_I2SC_MR_MODE_MASTER;

	/* If master starts, enable the audio घड़ी. */
	अगर (is_master && mck_enabled)
		err = aपंचांगel_i2s_चयन_mck_generator(dev, true);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(dev->regmap, ATMEL_I2SC_CR, cr);
	अगर (err)
		वापस err;

	/* If master stops, disable the audio घड़ी. */
	अगर (is_master && !mck_enabled)
		err = aपंचांगel_i2s_चयन_mck_generator(dev, false);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops aपंचांगel_i2s_dai_ops = अणु
	.prepare	= aपंचांगel_i2s_prepare,
	.trigger	= aपंचांगel_i2s_trigger,
	.hw_params	= aपंचांगel_i2s_hw_params,
	.set_fmt	= aपंचांगel_i2s_set_dai_fmt,
पूर्ण;

अटल पूर्णांक aपंचांगel_i2s_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा aपंचांगel_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, &dev->playback, &dev->capture);
	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver aपंचांगel_i2s_dai = अणु
	.probe	= aपंचांगel_i2s_dai_probe,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 2,
		.rates = ATMEL_I2S_RATES,
		.क्रमmats = ATMEL_I2S_FORMATS,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 2,
		.rates = ATMEL_I2S_RATES,
		.क्रमmats = ATMEL_I2S_FORMATS,
	पूर्ण,
	.ops = &aपंचांगel_i2s_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver aपंचांगel_i2s_component = अणु
	.name	= "atmel-i2s",
पूर्ण;

अटल पूर्णांक aपंचांगel_i2s_sama5d2_mck_init(काष्ठा aपंचांगel_i2s_dev *dev,
				      काष्ठा device_node *np)
अणु
	काष्ठा clk *muxclk;
	पूर्णांक err;

	अगर (!dev->gclk)
		वापस 0;

	/* muxclk is optional, so we वापस error क्रम probe defer only */
	muxclk = devm_clk_get(dev->dev, "muxclk");
	अगर (IS_ERR(muxclk)) अणु
		err = PTR_ERR(muxclk);
		अगर (err == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_dbg(dev->dev,
			"failed to get the I2S clock control: %d\n", err);
		वापस 0;
	पूर्ण

	वापस clk_set_parent(muxclk, dev->gclk);
पूर्ण

अटल स्थिर काष्ठा aपंचांगel_i2s_caps aपंचांगel_i2s_sama5d2_caps = अणु
	.mck_init = aपंचांगel_i2s_sama5d2_mck_init,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_i2s_dt_ids[] = अणु
	अणु
		.compatible = "atmel,sama5d2-i2s",
		.data = (व्योम *)&aपंचांगel_i2s_sama5d2_caps,
	पूर्ण,

	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, aपंचांगel_i2s_dt_ids);

अटल पूर्णांक aपंचांगel_i2s_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा aपंचांगel_i2s_dev *dev;
	काष्ठा resource *mem;
	काष्ठा regmap *regmap;
	व्योम __iomem *base;
	पूर्णांक irq;
	पूर्णांक err;
	अचिन्हित पूर्णांक pcm_flags = 0;
	अचिन्हित पूर्णांक version;

	/* Get memory क्रम driver data. */
	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	/* Get hardware capabilities. */
	match = of_match_node(aपंचांगel_i2s_dt_ids, np);
	अगर (match)
		dev->caps = match->data;

	/* Map I/O रेजिस्टरs. */
	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio(&pdev->dev, base,
				       &aपंचांगel_i2s_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* Request IRQ. */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	err = devm_request_irq(&pdev->dev, irq, aपंचांगel_i2s_पूर्णांकerrupt, 0,
			       dev_name(&pdev->dev), dev);
	अगर (err)
		वापस err;

	/* Get the peripheral घड़ी. */
	dev->pclk = devm_clk_get(&pdev->dev, "pclk");
	अगर (IS_ERR(dev->pclk)) अणु
		err = PTR_ERR(dev->pclk);
		dev_err(&pdev->dev,
			"failed to get the peripheral clock: %d\n", err);
		वापस err;
	पूर्ण

	/* Get audio घड़ी to generate the I2S Master Clock (I2S_MCK) */
	dev->gclk = devm_clk_get(&pdev->dev, "gclk");
	अगर (IS_ERR(dev->gclk)) अणु
		अगर (PTR_ERR(dev->gclk) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		/* Master Mode not supported */
		dev->gclk = शून्य;
	पूर्ण
	dev->dev = &pdev->dev;
	dev->regmap = regmap;
	platक्रमm_set_drvdata(pdev, dev);

	/* Do hardware specअगरic settings to initialize I2S_MCK generator */
	अगर (dev->caps && dev->caps->mck_init) अणु
		err = dev->caps->mck_init(dev, np);
		अगर (err)
			वापस err;
	पूर्ण

	/* Enable the peripheral घड़ी. */
	err = clk_prepare_enable(dev->pclk);
	अगर (err)
		वापस err;

	/* Get IP version. */
	regmap_पढ़ो(dev->regmap, ATMEL_I2SC_VERSION, &version);
	dev_info(&pdev->dev, "hw version: %#x\n", version);

	/* Enable error पूर्णांकerrupts. */
	regmap_ग_लिखो(dev->regmap, ATMEL_I2SC_IER,
		     ATMEL_I2SC_INT_RXOR | ATMEL_I2SC_INT_TXUR);

	err = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &aपंचांगel_i2s_component,
					      &aपंचांगel_i2s_dai, 1);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register DAI: %d\n", err);
		clk_disable_unprepare(dev->pclk);
		वापस err;
	पूर्ण

	/* Prepare DMA config. */
	dev->playback.addr	= (dma_addr_t)mem->start + ATMEL_I2SC_THR;
	dev->playback.maxburst	= 1;
	dev->capture.addr	= (dma_addr_t)mem->start + ATMEL_I2SC_RHR;
	dev->capture.maxburst	= 1;

	अगर (of_property_match_string(np, "dma-names", "rx-tx") == 0)
		pcm_flags |= SND_DMAENGINE_PCM_FLAG_HALF_DUPLEX;
	err = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य, pcm_flags);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register PCM: %d\n", err);
		clk_disable_unprepare(dev->pclk);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_i2s_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_i2s_dev *dev = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(dev->pclk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aपंचांगel_i2s_driver = अणु
	.driver		= अणु
		.name	= "atmel_i2s",
		.of_match_table	= of_match_ptr(aपंचांगel_i2s_dt_ids),
	पूर्ण,
	.probe		= aपंचांगel_i2s_probe,
	.हटाओ		= aपंचांगel_i2s_हटाओ,
पूर्ण;
module_platक्रमm_driver(aपंचांगel_i2s_driver);

MODULE_DESCRIPTION("Atmel I2S Controller driver");
MODULE_AUTHOR("Cyrille Pitchen <cyrille.pitchen@atmel.com>");
MODULE_LICENSE("GPL v2");
