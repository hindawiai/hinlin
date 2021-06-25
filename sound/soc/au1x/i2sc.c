<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Au1000/Au1500/Au1100 I2S controller driver क्रम ASoC
 *
 * (c) 2011 Manuel Lauss <manuel.lauss@googlemail.com>
 *
 * Note: घड़ी supplied to the I2S controller must be 256x samplerate.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>

#समावेश "psc.h"

#घोषणा I2S_RXTX	0x00
#घोषणा I2S_CFG		0x04
#घोषणा I2S_ENABLE	0x08

#घोषणा CFG_XU		(1 << 25)	/* tx underflow */
#घोषणा CFG_XO		(1 << 24)
#घोषणा CFG_RU		(1 << 23)
#घोषणा CFG_RO		(1 << 22)
#घोषणा CFG_TR		(1 << 21)
#घोषणा CFG_TE		(1 << 20)
#घोषणा CFG_TF		(1 << 19)
#घोषणा CFG_RR		(1 << 18)
#घोषणा CFG_RF		(1 << 17)
#घोषणा CFG_ICK		(1 << 12)	/* घड़ी invert */
#घोषणा CFG_PD		(1 << 11)	/* set to make I2SDIO INPUT */
#घोषणा CFG_LB		(1 << 10)	/* loopback */
#घोषणा CFG_IC		(1 << 9)	/* word select invert */
#घोषणा CFG_FM_I2S	(0 << 7)	/* I2S क्रमmat */
#घोषणा CFG_FM_LJ	(1 << 7)	/* left-justअगरied */
#घोषणा CFG_FM_RJ	(2 << 7)	/* right-justअगरied */
#घोषणा CFG_FM_MASK	(3 << 7)
#घोषणा CFG_TN		(1 << 6)	/* tx fअगरo en */
#घोषणा CFG_RN		(1 << 5)	/* rx fअगरo en */
#घोषणा CFG_SZ_8	(0x08)
#घोषणा CFG_SZ_16	(0x10)
#घोषणा CFG_SZ_18	(0x12)
#घोषणा CFG_SZ_20	(0x14)
#घोषणा CFG_SZ_24	(0x18)
#घोषणा CFG_SZ_MASK	(0x1f)
#घोषणा EN_D		(1 << 1)	/* DISable */
#घोषणा EN_CE		(1 << 0)	/* घड़ी enable */

/* only limited by घड़ी generator and board design */
#घोषणा AU1XI2SC_RATES \
	SNDRV_PCM_RATE_CONTINUOUS

#घोषणा AU1XI2SC_FMTS \
	(SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_U8 |		\
	SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE |	\
	SNDRV_PCM_FMTBIT_U16_LE | SNDRV_PCM_FMTBIT_U16_BE |	\
	SNDRV_PCM_FMTBIT_S18_3LE | SNDRV_PCM_FMTBIT_U18_3LE |	\
	SNDRV_PCM_FMTBIT_S18_3BE | SNDRV_PCM_FMTBIT_U18_3BE |	\
	SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_U20_3LE |	\
	SNDRV_PCM_FMTBIT_S20_3BE | SNDRV_PCM_FMTBIT_U20_3BE |	\
	SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_BE |	\
	SNDRV_PCM_FMTBIT_U24_LE | SNDRV_PCM_FMTBIT_U24_BE |	\
	0)

अटल अंतरभूत अचिन्हित दीर्घ RD(काष्ठा au1xpsc_audio_data *ctx, पूर्णांक reg)
अणु
	वापस __raw_पढ़ोl(ctx->mmio + reg);
पूर्ण

अटल अंतरभूत व्योम WR(काष्ठा au1xpsc_audio_data *ctx, पूर्णांक reg, अचिन्हित दीर्घ v)
अणु
	__raw_ग_लिखोl(v, ctx->mmio + reg);
	wmb();
पूर्ण

अटल पूर्णांक au1xi2s_set_fmt(काष्ठा snd_soc_dai *cpu_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा au1xpsc_audio_data *ctx = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित दीर्घ c;
	पूर्णांक ret;

	ret = -EINVAL;
	c = ctx->cfg;

	c &= ~CFG_FM_MASK;
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		c |= CFG_FM_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_MSB:
		c |= CFG_FM_RJ;
		अवरोध;
	हाल SND_SOC_DAIFMT_LSB:
		c |= CFG_FM_LJ;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	c &= ~(CFG_IC | CFG_ICK);		/* IB-IF */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		c |= CFG_IC | CFG_ICK;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		c |= CFG_IC;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		c |= CFG_ICK;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	/* I2S controller only supports master */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:	/* CODEC slave */
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	ret = 0;
	ctx->cfg = c;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक au1xi2s_trigger(काष्ठा snd_pcm_substream *substream,
			   पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा au1xpsc_audio_data *ctx = snd_soc_dai_get_drvdata(dai);
	पूर्णांक stype = SUBSTREAM_TYPE(substream);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		/* घातer up */
		WR(ctx, I2S_ENABLE, EN_D | EN_CE);
		WR(ctx, I2S_ENABLE, EN_CE);
		ctx->cfg |= (stype == PCM_TX) ? CFG_TN : CFG_RN;
		WR(ctx, I2S_CFG, ctx->cfg);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		ctx->cfg &= ~((stype == PCM_TX) ? CFG_TN : CFG_RN);
		WR(ctx, I2S_CFG, ctx->cfg);
		WR(ctx, I2S_ENABLE, EN_D);		/* घातer off */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ msbits_to_reg(पूर्णांक msbits)
अणु
	चयन (msbits) अणु
	हाल 8:
		वापस CFG_SZ_8;
	हाल 16:
		वापस CFG_SZ_16;
	हाल 18:
		वापस CFG_SZ_18;
	हाल 20:
		वापस CFG_SZ_20;
	हाल 24:
		वापस CFG_SZ_24;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक au1xi2s_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा au1xpsc_audio_data *ctx = snd_soc_dai_get_drvdata(dai);
	अचिन्हित दीर्घ v;

	v = msbits_to_reg(params->msbits);
	अगर (!v)
		वापस -EINVAL;

	ctx->cfg &= ~CFG_SZ_MASK;
	ctx->cfg |= v;
	वापस 0;
पूर्ण

अटल पूर्णांक au1xi2s_startup(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा au1xpsc_audio_data *ctx = snd_soc_dai_get_drvdata(dai);
	snd_soc_dai_set_dma_data(dai, substream, &ctx->dmaids[0]);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops au1xi2s_dai_ops = अणु
	.startup	= au1xi2s_startup,
	.trigger	= au1xi2s_trigger,
	.hw_params	= au1xi2s_hw_params,
	.set_fmt	= au1xi2s_set_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver au1xi2s_dai_driver = अणु
	.symmetric_rate		= 1,
	.playback = अणु
		.rates		= AU1XI2SC_RATES,
		.क्रमmats	= AU1XI2SC_FMTS,
		.channels_min	= 2,
		.channels_max	= 2,
	पूर्ण,
	.capture = अणु
		.rates		= AU1XI2SC_RATES,
		.क्रमmats	= AU1XI2SC_FMTS,
		.channels_min	= 2,
		.channels_max	= 2,
	पूर्ण,
	.ops = &au1xi2s_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver au1xi2s_component = अणु
	.name		= "au1xi2s",
पूर्ण;

अटल पूर्णांक au1xi2s_drvprobe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *iores, *dmares;
	काष्ठा au1xpsc_audio_data *ctx;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	iores = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!iores)
		वापस -ENODEV;

	अगर (!devm_request_mem_region(&pdev->dev, iores->start,
				     resource_size(iores),
				     pdev->name))
		वापस -EBUSY;

	ctx->mmio = devm_ioremap(&pdev->dev, iores->start,
					 resource_size(iores));
	अगर (!ctx->mmio)
		वापस -EBUSY;

	dmares = platक्रमm_get_resource(pdev, IORESOURCE_DMA, 0);
	अगर (!dmares)
		वापस -EBUSY;
	ctx->dmaids[SNDRV_PCM_STREAM_PLAYBACK] = dmares->start;

	dmares = platक्रमm_get_resource(pdev, IORESOURCE_DMA, 1);
	अगर (!dmares)
		वापस -EBUSY;
	ctx->dmaids[SNDRV_PCM_STREAM_CAPTURE] = dmares->start;

	platक्रमm_set_drvdata(pdev, ctx);

	वापस snd_soc_रेजिस्टर_component(&pdev->dev, &au1xi2s_component,
					  &au1xi2s_dai_driver, 1);
पूर्ण

अटल पूर्णांक au1xi2s_drvहटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा au1xpsc_audio_data *ctx = platक्रमm_get_drvdata(pdev);

	snd_soc_unरेजिस्टर_component(&pdev->dev);

	WR(ctx, I2S_ENABLE, EN_D);	/* घड़ी off, disable */

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक au1xi2s_drvsuspend(काष्ठा device *dev)
अणु
	काष्ठा au1xpsc_audio_data *ctx = dev_get_drvdata(dev);

	WR(ctx, I2S_ENABLE, EN_D);	/* घड़ी off, disable */

	वापस 0;
पूर्ण

अटल पूर्णांक au1xi2s_drvresume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops au1xi2sc_pmops = अणु
	.suspend	= au1xi2s_drvsuspend,
	.resume		= au1xi2s_drvresume,
पूर्ण;

#घोषणा AU1XI2SC_PMOPS (&au1xi2sc_pmops)

#अन्यथा

#घोषणा AU1XI2SC_PMOPS शून्य

#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver au1xi2s_driver = अणु
	.driver	= अणु
		.name	= "alchemy-i2sc",
		.pm	= AU1XI2SC_PMOPS,
	पूर्ण,
	.probe		= au1xi2s_drvprobe,
	.हटाओ		= au1xi2s_drvहटाओ,
पूर्ण;

module_platक्रमm_driver(au1xi2s_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Au1000/1500/1100 I2S ASoC driver");
MODULE_AUTHOR("Manuel Lauss");
