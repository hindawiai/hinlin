<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// s3c24xx-i2s.c  --  ALSA Soc Audio Layer
//
// (c) 2006 Wolfson Microelectronics PLC.
// Graeme Gregory graeme.gregory@wolfsonmicro.com or linux@wolfsonmicro.com
//
// Copyright 2004-2005 Simtec Electronics
//	http://armlinux.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>

#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>

#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>

#समावेश "regs-iis.h"
#समावेश "dma.h"
#समावेश "s3c24xx-i2s.h"

अटल काष्ठा snd_dmaengine_dai_dma_data s3c24xx_i2s_pcm_stereo_out = अणु
	.chan_name	= "tx",
	.addr_width	= 2,
पूर्ण;

अटल काष्ठा snd_dmaengine_dai_dma_data s3c24xx_i2s_pcm_stereo_in = अणु
	.chan_name	= "rx",
	.addr_width	= 2,
पूर्ण;

काष्ठा s3c24xx_i2s_info अणु
	व्योम __iomem	*regs;
	काष्ठा clk	*iis_clk;
	u32		iiscon;
	u32		iismod;
	u32		iisfcon;
	u32		iispsr;
पूर्ण;
अटल काष्ठा s3c24xx_i2s_info s3c24xx_i2s;

अटल व्योम s3c24xx_snd_txctrl(पूर्णांक on)
अणु
	u32 iisfcon;
	u32 iiscon;
	u32 iismod;

	iisfcon = पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISFCON);
	iiscon  = पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISCON);
	iismod  = पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISMOD);

	pr_debug("r: IISCON: %x IISMOD: %x IISFCON: %x\n", iiscon, iismod, iisfcon);

	अगर (on) अणु
		iisfcon |= S3C2410_IISFCON_TXDMA | S3C2410_IISFCON_TXENABLE;
		iiscon  |= S3C2410_IISCON_TXDMAEN | S3C2410_IISCON_IISEN;
		iiscon  &= ~S3C2410_IISCON_TXIDLE;
		iismod  |= S3C2410_IISMOD_TXMODE;

		ग_लिखोl(iismod,  s3c24xx_i2s.regs + S3C2410_IISMOD);
		ग_लिखोl(iisfcon, s3c24xx_i2s.regs + S3C2410_IISFCON);
		ग_लिखोl(iiscon,  s3c24xx_i2s.regs + S3C2410_IISCON);
	पूर्ण अन्यथा अणु
		/* note, we have to disable the FIFOs otherwise bad things
		 * seem to happen when the DMA stops. According to the
		 * Samsung supplied kernel, this should allow the DMA
		 * engine and FIFOs to reset. If this isn't allowed, the
		 * DMA engine will simply मुक्तze अक्रमomly.
		 */

		iisfcon &= ~S3C2410_IISFCON_TXENABLE;
		iisfcon &= ~S3C2410_IISFCON_TXDMA;
		iiscon  |=  S3C2410_IISCON_TXIDLE;
		iiscon  &= ~S3C2410_IISCON_TXDMAEN;
		iismod  &= ~S3C2410_IISMOD_TXMODE;

		ग_लिखोl(iiscon,  s3c24xx_i2s.regs + S3C2410_IISCON);
		ग_लिखोl(iisfcon, s3c24xx_i2s.regs + S3C2410_IISFCON);
		ग_लिखोl(iismod,  s3c24xx_i2s.regs + S3C2410_IISMOD);
	पूर्ण

	pr_debug("w: IISCON: %x IISMOD: %x IISFCON: %x\n", iiscon, iismod, iisfcon);
पूर्ण

अटल व्योम s3c24xx_snd_rxctrl(पूर्णांक on)
अणु
	u32 iisfcon;
	u32 iiscon;
	u32 iismod;

	iisfcon = पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISFCON);
	iiscon  = पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISCON);
	iismod  = पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISMOD);

	pr_debug("r: IISCON: %x IISMOD: %x IISFCON: %x\n", iiscon, iismod, iisfcon);

	अगर (on) अणु
		iisfcon |= S3C2410_IISFCON_RXDMA | S3C2410_IISFCON_RXENABLE;
		iiscon  |= S3C2410_IISCON_RXDMAEN | S3C2410_IISCON_IISEN;
		iiscon  &= ~S3C2410_IISCON_RXIDLE;
		iismod  |= S3C2410_IISMOD_RXMODE;

		ग_लिखोl(iismod,  s3c24xx_i2s.regs + S3C2410_IISMOD);
		ग_लिखोl(iisfcon, s3c24xx_i2s.regs + S3C2410_IISFCON);
		ग_लिखोl(iiscon,  s3c24xx_i2s.regs + S3C2410_IISCON);
	पूर्ण अन्यथा अणु
		/* note, we have to disable the FIFOs otherwise bad things
		 * seem to happen when the DMA stops. According to the
		 * Samsung supplied kernel, this should allow the DMA
		 * engine and FIFOs to reset. If this isn't allowed, the
		 * DMA engine will simply मुक्तze अक्रमomly.
		 */

		iisfcon &= ~S3C2410_IISFCON_RXENABLE;
		iisfcon &= ~S3C2410_IISFCON_RXDMA;
		iiscon  |= S3C2410_IISCON_RXIDLE;
		iiscon  &= ~S3C2410_IISCON_RXDMAEN;
		iismod  &= ~S3C2410_IISMOD_RXMODE;

		ग_लिखोl(iisfcon, s3c24xx_i2s.regs + S3C2410_IISFCON);
		ग_लिखोl(iiscon,  s3c24xx_i2s.regs + S3C2410_IISCON);
		ग_लिखोl(iismod,  s3c24xx_i2s.regs + S3C2410_IISMOD);
	पूर्ण

	pr_debug("w: IISCON: %x IISMOD: %x IISFCON: %x\n", iiscon, iismod, iisfcon);
पूर्ण

/*
 * Wait क्रम the LR संकेत to allow synchronisation to the L/R घड़ी
 * from the codec. May only be needed क्रम slave mode.
 */
अटल पूर्णांक s3c24xx_snd_lrsync(व्योम)
अणु
	u32 iiscon;
	पूर्णांक समयout = 50; /* 5ms */

	जबतक (1) अणु
		iiscon = पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISCON);
		अगर (iiscon & S3C2410_IISCON_LRINDEX)
			अवरोध;

		अगर (!समयout--)
			वापस -ETIMEDOUT;
		udelay(100);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Check whether CPU is the master or slave
 */
अटल अंतरभूत पूर्णांक s3c24xx_snd_is_clkmaster(व्योम)
अणु
	वापस (पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISMOD) & S3C2410_IISMOD_SLAVE) ? 0:1;
पूर्ण

/*
 * Set S3C24xx I2S DAI क्रमmat
 */
अटल पूर्णांक s3c24xx_i2s_set_fmt(काष्ठा snd_soc_dai *cpu_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	u32 iismod;

	iismod = पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISMOD);
	pr_debug("hw_params r: IISMOD: %x \n", iismod);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		iismod |= S3C2410_IISMOD_SLAVE;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		iismod &= ~S3C2410_IISMOD_SLAVE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_LEFT_J:
		iismod |= S3C2410_IISMOD_MSB;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		iismod &= ~S3C2410_IISMOD_MSB;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(iismod, s3c24xx_i2s.regs + S3C2410_IISMOD);
	pr_debug("hw_params w: IISMOD: %x \n", iismod);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c24xx_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;
	u32 iismod;

	dma_data = snd_soc_dai_get_dma_data(dai, substream);

	/* Working copies of रेजिस्टर */
	iismod = पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISMOD);
	pr_debug("hw_params r: IISMOD: %x\n", iismod);

	चयन (params_width(params)) अणु
	हाल 8:
		iismod &= ~S3C2410_IISMOD_16BIT;
		dma_data->addr_width = 1;
		अवरोध;
	हाल 16:
		iismod |= S3C2410_IISMOD_16BIT;
		dma_data->addr_width = 2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(iismod, s3c24xx_i2s.regs + S3C2410_IISMOD);
	pr_debug("hw_params w: IISMOD: %x\n", iismod);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c24xx_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			       काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (!s3c24xx_snd_is_clkmaster()) अणु
			ret = s3c24xx_snd_lrsync();
			अगर (ret)
				जाओ निकास_err;
		पूर्ण

		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			s3c24xx_snd_rxctrl(1);
		अन्यथा
			s3c24xx_snd_txctrl(1);

		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			s3c24xx_snd_rxctrl(0);
		अन्यथा
			s3c24xx_snd_txctrl(0);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

निकास_err:
	वापस ret;
पूर्ण

/*
 * Set S3C24xx Clock source
 */
अटल पूर्णांक s3c24xx_i2s_set_sysclk(काष्ठा snd_soc_dai *cpu_dai,
	पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	u32 iismod = पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISMOD);

	iismod &= ~S3C2440_IISMOD_MPLL;

	चयन (clk_id) अणु
	हाल S3C24XX_CLKSRC_PCLK:
		अवरोध;
	हाल S3C24XX_CLKSRC_MPLL:
		iismod |= S3C2440_IISMOD_MPLL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(iismod, s3c24xx_i2s.regs + S3C2410_IISMOD);
	वापस 0;
पूर्ण

/*
 * Set S3C24xx Clock भागiders
 */
अटल पूर्णांक s3c24xx_i2s_set_clkभाग(काष्ठा snd_soc_dai *cpu_dai,
	पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	u32 reg;

	चयन (भाग_id) अणु
	हाल S3C24XX_DIV_BCLK:
		reg = पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISMOD) & ~S3C2410_IISMOD_FS_MASK;
		ग_लिखोl(reg | भाग, s3c24xx_i2s.regs + S3C2410_IISMOD);
		अवरोध;
	हाल S3C24XX_DIV_MCLK:
		reg = पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISMOD) & ~(S3C2410_IISMOD_384FS);
		ग_लिखोl(reg | भाग, s3c24xx_i2s.regs + S3C2410_IISMOD);
		अवरोध;
	हाल S3C24XX_DIV_PRESCALER:
		ग_लिखोl(भाग, s3c24xx_i2s.regs + S3C2410_IISPSR);
		reg = पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISCON);
		ग_लिखोl(reg | S3C2410_IISCON_PSCEN, s3c24xx_i2s.regs + S3C2410_IISCON);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * To aव्योम duplicating घड़ी code, allow machine driver to
 * get the घड़ीrate from here.
 */
u32 s3c24xx_i2s_get_घड़ीrate(व्योम)
अणु
	वापस clk_get_rate(s3c24xx_i2s.iis_clk);
पूर्ण
EXPORT_SYMBOL_GPL(s3c24xx_i2s_get_घड़ीrate);

अटल पूर्णांक s3c24xx_i2s_probe(काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret;
	snd_soc_dai_init_dma_data(dai, &s3c24xx_i2s_pcm_stereo_out,
					&s3c24xx_i2s_pcm_stereo_in);

	s3c24xx_i2s.iis_clk = devm_clk_get(dai->dev, "iis");
	अगर (IS_ERR(s3c24xx_i2s.iis_clk)) अणु
		pr_err("failed to get iis_clock\n");
		वापस PTR_ERR(s3c24xx_i2s.iis_clk);
	पूर्ण
	ret = clk_prepare_enable(s3c24xx_i2s.iis_clk);
	अगर (ret)
		वापस ret;

	ग_लिखोl(S3C2410_IISCON_IISEN, s3c24xx_i2s.regs + S3C2410_IISCON);

	s3c24xx_snd_txctrl(0);
	s3c24xx_snd_rxctrl(0);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक s3c24xx_i2s_suspend(काष्ठा snd_soc_component *component)
अणु
	s3c24xx_i2s.iiscon = पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISCON);
	s3c24xx_i2s.iismod = पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISMOD);
	s3c24xx_i2s.iisfcon = पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISFCON);
	s3c24xx_i2s.iispsr = पढ़ोl(s3c24xx_i2s.regs + S3C2410_IISPSR);

	clk_disable_unprepare(s3c24xx_i2s.iis_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c24xx_i2s_resume(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(s3c24xx_i2s.iis_clk);
	अगर (ret)
		वापस ret;

	ग_लिखोl(s3c24xx_i2s.iiscon, s3c24xx_i2s.regs + S3C2410_IISCON);
	ग_लिखोl(s3c24xx_i2s.iismod, s3c24xx_i2s.regs + S3C2410_IISMOD);
	ग_लिखोl(s3c24xx_i2s.iisfcon, s3c24xx_i2s.regs + S3C2410_IISFCON);
	ग_लिखोl(s3c24xx_i2s.iispsr, s3c24xx_i2s.regs + S3C2410_IISPSR);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा s3c24xx_i2s_suspend शून्य
#घोषणा s3c24xx_i2s_resume शून्य
#पूर्ण_अगर

#घोषणा S3C24XX_I2S_RATES \
	(SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 | SNDRV_PCM_RATE_16000 | \
	SNDRV_PCM_RATE_22050 | SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | \
	SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000)

अटल स्थिर काष्ठा snd_soc_dai_ops s3c24xx_i2s_dai_ops = अणु
	.trigger	= s3c24xx_i2s_trigger,
	.hw_params	= s3c24xx_i2s_hw_params,
	.set_fmt	= s3c24xx_i2s_set_fmt,
	.set_clkभाग	= s3c24xx_i2s_set_clkभाग,
	.set_sysclk	= s3c24xx_i2s_set_sysclk,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver s3c24xx_i2s_dai = अणु
	.probe = s3c24xx_i2s_probe,
	.playback = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = S3C24XX_I2S_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_S16_LE,पूर्ण,
	.capture = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = S3C24XX_I2S_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_S16_LE,पूर्ण,
	.ops = &s3c24xx_i2s_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver s3c24xx_i2s_component = अणु
	.name		= "s3c24xx-i2s",
	.suspend	= s3c24xx_i2s_suspend,
	.resume		= s3c24xx_i2s_resume,
पूर्ण;

अटल पूर्णांक s3c24xx_iis_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	s3c24xx_i2s.regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(s3c24xx_i2s.regs))
		वापस PTR_ERR(s3c24xx_i2s.regs);

	s3c24xx_i2s_pcm_stereo_out.addr = res->start + S3C2410_IISFIFO;
	s3c24xx_i2s_pcm_stereo_in.addr = res->start + S3C2410_IISFIFO;

	ret = samsung_asoc_dma_platक्रमm_रेजिस्टर(&pdev->dev, शून्य,
						 "tx", "rx", शून्य);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register the DMA: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&s3c24xx_i2s_component, &s3c24xx_i2s_dai, 1);
	अगर (ret)
		dev_err(&pdev->dev, "Failed to register the DAI\n");

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver s3c24xx_iis_driver = अणु
	.probe  = s3c24xx_iis_dev_probe,
	.driver = अणु
		.name = "s3c24xx-iis",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(s3c24xx_iis_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Ben Dooks, <ben@simtec.co.uk>");
MODULE_DESCRIPTION("s3c24xx I2S SoC Interface");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:s3c24xx-iis");
