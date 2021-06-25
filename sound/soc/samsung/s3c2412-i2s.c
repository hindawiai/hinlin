<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// ALSA Soc Audio Layer - S3C2412 I2S driver
//
// Copyright (c) 2006 Wolfson Microelectronics PLC.
//	Graeme Gregory graeme.gregory@wolfsonmicro.com
//	linux@wolfsonmicro.com
//
// Copyright (c) 2007, 2004-2005 Simtec Electronics
//	http://armlinux.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>

#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>

#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>

#समावेश "dma.h"
#समावेश "regs-i2s-v2.h"
#समावेश "s3c2412-i2s.h"

#समावेश <linux/platक्रमm_data/asoc-s3c.h>

अटल काष्ठा snd_dmaengine_dai_dma_data s3c2412_i2s_pcm_stereo_out = अणु
	.chan_name	= "tx",
	.addr_width	= 4,
पूर्ण;

अटल काष्ठा snd_dmaengine_dai_dma_data s3c2412_i2s_pcm_stereo_in = अणु
	.chan_name	= "rx",
	.addr_width	= 4,
पूर्ण;

अटल काष्ठा s3c_i2sv2_info s3c2412_i2s;

अटल पूर्णांक s3c2412_i2s_probe(काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret;

	pr_debug("Entered %s\n", __func__);

	snd_soc_dai_init_dma_data(dai, &s3c2412_i2s_pcm_stereo_out,
					&s3c2412_i2s_pcm_stereo_in);

	ret = s3c_i2sv2_probe(dai, &s3c2412_i2s);
	अगर (ret)
		वापस ret;

	s3c2412_i2s.dma_capture = &s3c2412_i2s_pcm_stereo_in;
	s3c2412_i2s.dma_playback = &s3c2412_i2s_pcm_stereo_out;

	s3c2412_i2s.iis_cclk = devm_clk_get(dai->dev, "i2sclk");
	अगर (IS_ERR(s3c2412_i2s.iis_cclk)) अणु
		pr_err("failed to get i2sclk clock\n");
		ret = PTR_ERR(s3c2412_i2s.iis_cclk);
		जाओ err;
	पूर्ण

	/* Set MPLL as the source क्रम IIS CLK */

	clk_set_parent(s3c2412_i2s.iis_cclk, clk_get(शून्य, "mpll"));
	ret = clk_prepare_enable(s3c2412_i2s.iis_cclk);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	s3c_i2sv2_cleanup(dai, &s3c2412_i2s);

	वापस ret;
पूर्ण

अटल पूर्णांक s3c2412_i2s_हटाओ(काष्ठा snd_soc_dai *dai)
अणु
	clk_disable_unprepare(s3c2412_i2s.iis_cclk);
	s3c_i2sv2_cleanup(dai, &s3c2412_i2s);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2412_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा s3c_i2sv2_info *i2s = snd_soc_dai_get_drvdata(cpu_dai);
	u32 iismod;

	pr_debug("Entered %s\n", __func__);

	iismod = पढ़ोl(i2s->regs + S3C2412_IISMOD);
	pr_debug("%s: r: IISMOD: %x\n", __func__, iismod);

	चयन (params_width(params)) अणु
	हाल 8:
		iismod |= S3C2412_IISMOD_8BIT;
		अवरोध;
	हाल 16:
		iismod &= ~S3C2412_IISMOD_8BIT;
		अवरोध;
	पूर्ण

	ग_लिखोl(iismod, i2s->regs + S3C2412_IISMOD);
	pr_debug("%s: w: IISMOD: %x\n", __func__, iismod);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक s3c2412_i2s_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा s3c_i2sv2_info *i2s = snd_soc_component_get_drvdata(component);
	u32 iismod;

	अगर (component->active) अणु
		i2s->suspend_iismod = पढ़ोl(i2s->regs + S3C2412_IISMOD);
		i2s->suspend_iiscon = पढ़ोl(i2s->regs + S3C2412_IISCON);
		i2s->suspend_iispsr = पढ़ोl(i2s->regs + S3C2412_IISPSR);

		/* some basic suspend checks */

		iismod = पढ़ोl(i2s->regs + S3C2412_IISMOD);

		अगर (iismod & S3C2412_IISCON_RXDMA_ACTIVE)
			pr_warn("%s: RXDMA active?\n", __func__);

		अगर (iismod & S3C2412_IISCON_TXDMA_ACTIVE)
			pr_warn("%s: TXDMA active?\n", __func__);

		अगर (iismod & S3C2412_IISCON_IIS_ACTIVE)
			pr_warn("%s: IIS active\n", __func__);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2412_i2s_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा s3c_i2sv2_info *i2s = snd_soc_component_get_drvdata(component);

	pr_info("component_active %d, IISMOD %08x, IISCON %08x\n",
		component->active, i2s->suspend_iismod, i2s->suspend_iiscon);

	अगर (component->active) अणु
		ग_लिखोl(i2s->suspend_iiscon, i2s->regs + S3C2412_IISCON);
		ग_लिखोl(i2s->suspend_iismod, i2s->regs + S3C2412_IISMOD);
		ग_लिखोl(i2s->suspend_iispsr, i2s->regs + S3C2412_IISPSR);

		ग_लिखोl(S3C2412_IISFIC_RXFLUSH | S3C2412_IISFIC_TXFLUSH,
		       i2s->regs + S3C2412_IISFIC);

		ndelay(250);
		ग_लिखोl(0x0, i2s->regs + S3C2412_IISFIC);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा s3c2412_i2s_suspend शून्य
#घोषणा s3c2412_i2s_resume  शून्य
#पूर्ण_अगर

#घोषणा S3C2412_I2S_RATES \
	(SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 | SNDRV_PCM_RATE_16000 | \
	SNDRV_PCM_RATE_22050 | SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | \
	SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000)

अटल स्थिर काष्ठा snd_soc_dai_ops s3c2412_i2s_dai_ops = अणु
	.hw_params	= s3c2412_i2s_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver s3c2412_i2s_dai = अणु
	.probe		= s3c2412_i2s_probe,
	.हटाओ	= s3c2412_i2s_हटाओ,
	.playback = अणु
		.channels_min	= 2,
		.channels_max	= 2,
		.rates		= S3C2412_I2S_RATES,
		.क्रमmats	= SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.channels_min	= 2,
		.channels_max	= 2,
		.rates		= S3C2412_I2S_RATES,
		.क्रमmats	= SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.ops = &s3c2412_i2s_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver s3c2412_i2s_component = अणु
	.name		= "s3c2412-i2s",
	.suspend	= s3c2412_i2s_suspend,
	.resume		= s3c2412_i2s_resume,
पूर्ण;

अटल पूर्णांक s3c2412_iis_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा resource *res;
	काष्ठा s3c_audio_pdata *pdata = dev_get_platdata(&pdev->dev);

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "missing platform data");
		वापस -ENXIO;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	s3c2412_i2s.regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(s3c2412_i2s.regs))
		वापस PTR_ERR(s3c2412_i2s.regs);

	s3c2412_i2s_pcm_stereo_out.addr = res->start + S3C2412_IISTXD;
	s3c2412_i2s_pcm_stereo_out.filter_data = pdata->dma_playback;
	s3c2412_i2s_pcm_stereo_in.addr = res->start + S3C2412_IISRXD;
	s3c2412_i2s_pcm_stereo_in.filter_data = pdata->dma_capture;

	ret = samsung_asoc_dma_platक्रमm_रेजिस्टर(&pdev->dev,
						 pdata->dma_filter,
						 "tx", "rx", शून्य);
	अगर (ret) अणु
		pr_err("failed to register the DMA: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = s3c_i2sv2_रेजिस्टर_component(&pdev->dev, -1,
					   &s3c2412_i2s_component,
					   &s3c2412_i2s_dai);
	अगर (ret)
		pr_err("failed to register the dai\n");

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver s3c2412_iis_driver = अणु
	.probe  = s3c2412_iis_dev_probe,
	.driver = अणु
		.name = "s3c2412-iis",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(s3c2412_iis_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Ben Dooks, <ben@simtec.co.uk>");
MODULE_DESCRIPTION("S3C2412 I2S SoC Interface");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:s3c2412-iis");
