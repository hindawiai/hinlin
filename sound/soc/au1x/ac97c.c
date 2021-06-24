<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Au1000/Au1500/Au1100 AC97C controller driver क्रम ASoC
 *
 * (c) 2011 Manuel Lauss <manuel.lauss@googlemail.com>
 *
 * based on the old ALSA driver originally written by
 *			Charles Eidsness <अक्षरles@cooper-street.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/suspend.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>

#समावेश "psc.h"

/* रेजिस्टर offsets and bits */
#घोषणा AC97_CONFIG	0x00
#घोषणा AC97_STATUS	0x04
#घोषणा AC97_DATA	0x08
#घोषणा AC97_CMDRESP	0x0c
#घोषणा AC97_ENABLE	0x10

#घोषणा CFG_RC(x)	(((x) & 0x3ff) << 13)	/* valid rx slots mask */
#घोषणा CFG_XS(x)	(((x) & 0x3ff) << 3)	/* valid tx slots mask */
#घोषणा CFG_SG		(1 << 2)	/* sync gate */
#घोषणा CFG_SN		(1 << 1)	/* sync control */
#घोषणा CFG_RS		(1 << 0)	/* acrst# control */
#घोषणा STAT_XU		(1 << 11)	/* tx underflow */
#घोषणा STAT_XO		(1 << 10)	/* tx overflow */
#घोषणा STAT_RU		(1 << 9)	/* rx underflow */
#घोषणा STAT_RO		(1 << 8)	/* rx overflow */
#घोषणा STAT_RD		(1 << 7)	/* codec पढ़ोy */
#घोषणा STAT_CP		(1 << 6)	/* command pending */
#घोषणा STAT_TE		(1 << 4)	/* tx fअगरo empty */
#घोषणा STAT_TF		(1 << 3)	/* tx fअगरo full */
#घोषणा STAT_RE		(1 << 1)	/* rx fअगरo empty */
#घोषणा STAT_RF		(1 << 0)	/* rx fअगरo full */
#घोषणा CMD_SET_DATA(x)	(((x) & 0xffff) << 16)
#घोषणा CMD_GET_DATA(x)	((x) & 0xffff)
#घोषणा CMD_READ	(1 << 7)
#घोषणा CMD_WRITE	(0 << 7)
#घोषणा CMD_IDX(x)	((x) & 0x7f)
#घोषणा EN_D		(1 << 1)	/* DISable bit */
#घोषणा EN_CE		(1 << 0)	/* घड़ी enable bit */

/* how often to retry failed codec रेजिस्टर पढ़ोs/ग_लिखोs */
#घोषणा AC97_RW_RETRIES	5

#घोषणा AC97_RATES	\
	SNDRV_PCM_RATE_CONTINUOUS

#घोषणा AC97_FMTS	\
	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE)

/* instance data. There can be only one, MacLeod!!!!, क्रमtunately there IS only
 * once AC97C on early Alchemy chips. The newer ones aren't so lucky.
 */
अटल काष्ठा au1xpsc_audio_data *ac97c_workdata;
#घोषणा ac97_to_ctx(x)		ac97c_workdata

अटल अंतरभूत अचिन्हित दीर्घ RD(काष्ठा au1xpsc_audio_data *ctx, पूर्णांक reg)
अणु
	वापस __raw_पढ़ोl(ctx->mmio + reg);
पूर्ण

अटल अंतरभूत व्योम WR(काष्ठा au1xpsc_audio_data *ctx, पूर्णांक reg, अचिन्हित दीर्घ v)
अणु
	__raw_ग_लिखोl(v, ctx->mmio + reg);
	wmb();
पूर्ण

अटल अचिन्हित लघु au1xac97c_ac97_पढ़ो(काष्ठा snd_ac97 *ac97,
					  अचिन्हित लघु r)
अणु
	काष्ठा au1xpsc_audio_data *ctx = ac97_to_ctx(ac97);
	अचिन्हित पूर्णांक पंचांगo, retry;
	अचिन्हित दीर्घ data;

	data = ~0;
	retry = AC97_RW_RETRIES;
	करो अणु
		mutex_lock(&ctx->lock);

		पंचांगo = 6;
		जबतक ((RD(ctx, AC97_STATUS) & STAT_CP) && --पंचांगo)
			udelay(21);	/* रुको an ac97 frame समय */
		अगर (!पंचांगo) अणु
			pr_debug("ac97rd timeout #1\n");
			जाओ next;
		पूर्ण

		WR(ctx, AC97_CMDRESP, CMD_IDX(r) | CMD_READ);

		/* stupid errata: data is only valid क्रम 21us, so
		 * poll, Forrest, poll...
		 */
		पंचांगo = 0x10000;
		जबतक ((RD(ctx, AC97_STATUS) & STAT_CP) && --पंचांगo)
			यंत्र अस्थिर ("nop");
		data = RD(ctx, AC97_CMDRESP);

		अगर (!पंचांगo)
			pr_debug("ac97rd timeout #2\n");

next:
		mutex_unlock(&ctx->lock);
	पूर्ण जबतक (--retry && !पंचांगo);

	pr_debug("AC97RD %04x %04lx %d\n", r, data, retry);

	वापस retry ? data & 0xffff : 0xffff;
पूर्ण

अटल व्योम au1xac97c_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु r,
				 अचिन्हित लघु v)
अणु
	काष्ठा au1xpsc_audio_data *ctx = ac97_to_ctx(ac97);
	अचिन्हित पूर्णांक पंचांगo, retry;

	retry = AC97_RW_RETRIES;
	करो अणु
		mutex_lock(&ctx->lock);

		क्रम (पंचांगo = 5; (RD(ctx, AC97_STATUS) & STAT_CP) && पंचांगo; पंचांगo--)
			udelay(21);
		अगर (!पंचांगo) अणु
			pr_debug("ac97wr timeout #1\n");
			जाओ next;
		पूर्ण

		WR(ctx, AC97_CMDRESP, CMD_WRITE | CMD_IDX(r) | CMD_SET_DATA(v));

		क्रम (पंचांगo = 10; (RD(ctx, AC97_STATUS) & STAT_CP) && पंचांगo; पंचांगo--)
			udelay(21);
		अगर (!पंचांगo)
			pr_debug("ac97wr timeout #2\n");
next:
		mutex_unlock(&ctx->lock);
	पूर्ण जबतक (--retry && !पंचांगo);

	pr_debug("AC97WR %04x %04x %d\n", r, v, retry);
पूर्ण

अटल व्योम au1xac97c_ac97_warm_reset(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा au1xpsc_audio_data *ctx = ac97_to_ctx(ac97);

	WR(ctx, AC97_CONFIG, ctx->cfg | CFG_SG | CFG_SN);
	msleep(20);
	WR(ctx, AC97_CONFIG, ctx->cfg | CFG_SG);
	WR(ctx, AC97_CONFIG, ctx->cfg);
पूर्ण

अटल व्योम au1xac97c_ac97_cold_reset(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा au1xpsc_audio_data *ctx = ac97_to_ctx(ac97);
	पूर्णांक i;

	WR(ctx, AC97_CONFIG, ctx->cfg | CFG_RS);
	msleep(500);
	WR(ctx, AC97_CONFIG, ctx->cfg);

	/* रुको क्रम codec पढ़ोy */
	i = 50;
	जबतक (((RD(ctx, AC97_STATUS) & STAT_RD) == 0) && --i)
		msleep(20);
	अगर (!i)
		prपूर्णांकk(KERN_ERR "ac97c: codec not ready after cold reset\n");
पूर्ण

/* AC97 controller operations */
अटल काष्ठा snd_ac97_bus_ops ac97c_bus_ops = अणु
	.पढ़ो		= au1xac97c_ac97_पढ़ो,
	.ग_लिखो		= au1xac97c_ac97_ग_लिखो,
	.reset		= au1xac97c_ac97_cold_reset,
	.warm_reset	= au1xac97c_ac97_warm_reset,
पूर्ण;

अटल पूर्णांक alchemy_ac97c_startup(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा au1xpsc_audio_data *ctx = snd_soc_dai_get_drvdata(dai);
	snd_soc_dai_set_dma_data(dai, substream, &ctx->dmaids[0]);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops alchemy_ac97c_ops = अणु
	.startup		= alchemy_ac97c_startup,
पूर्ण;

अटल पूर्णांक au1xac97c_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	वापस ac97c_workdata ? 0 : -ENODEV;
पूर्ण

अटल काष्ठा snd_soc_dai_driver au1xac97c_dai_driver = अणु
	.name			= "alchemy-ac97c",
	.probe			= au1xac97c_dai_probe,
	.playback = अणु
		.rates		= AC97_RATES,
		.क्रमmats	= AC97_FMTS,
		.channels_min	= 2,
		.channels_max	= 2,
	पूर्ण,
	.capture = अणु
		.rates		= AC97_RATES,
		.क्रमmats	= AC97_FMTS,
		.channels_min	= 2,
		.channels_max	= 2,
	पूर्ण,
	.ops			= &alchemy_ac97c_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver au1xac97c_component = अणु
	.name		= "au1xac97c",
पूर्ण;

अटल पूर्णांक au1xac97c_drvprobe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा resource *iores, *dmares;
	काष्ठा au1xpsc_audio_data *ctx;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	mutex_init(&ctx->lock);

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

	/* चयन it on */
	WR(ctx, AC97_ENABLE, EN_D | EN_CE);
	WR(ctx, AC97_ENABLE, EN_CE);

	ctx->cfg = CFG_RC(3) | CFG_XS(3);
	WR(ctx, AC97_CONFIG, ctx->cfg);

	platक्रमm_set_drvdata(pdev, ctx);

	ret = snd_soc_set_ac97_ops(&ac97c_bus_ops);
	अगर (ret)
		वापस ret;

	ret = snd_soc_रेजिस्टर_component(&pdev->dev, &au1xac97c_component,
					 &au1xac97c_dai_driver, 1);
	अगर (ret)
		वापस ret;

	ac97c_workdata = ctx;
	वापस 0;
पूर्ण

अटल पूर्णांक au1xac97c_drvहटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा au1xpsc_audio_data *ctx = platक्रमm_get_drvdata(pdev);

	snd_soc_unरेजिस्टर_component(&pdev->dev);

	WR(ctx, AC97_ENABLE, EN_D);	/* घड़ी off, disable */

	ac97c_workdata = शून्य;	/* MDEV */

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक au1xac97c_drvsuspend(काष्ठा device *dev)
अणु
	काष्ठा au1xpsc_audio_data *ctx = dev_get_drvdata(dev);

	WR(ctx, AC97_ENABLE, EN_D);	/* घड़ी off, disable */

	वापस 0;
पूर्ण

अटल पूर्णांक au1xac97c_drvresume(काष्ठा device *dev)
अणु
	काष्ठा au1xpsc_audio_data *ctx = dev_get_drvdata(dev);

	WR(ctx, AC97_ENABLE, EN_D | EN_CE);
	WR(ctx, AC97_ENABLE, EN_CE);
	WR(ctx, AC97_CONFIG, ctx->cfg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops au1xpscac97_pmops = अणु
	.suspend	= au1xac97c_drvsuspend,
	.resume		= au1xac97c_drvresume,
पूर्ण;

#घोषणा AU1XPSCAC97_PMOPS (&au1xpscac97_pmops)

#अन्यथा

#घोषणा AU1XPSCAC97_PMOPS शून्य

#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver au1xac97c_driver = अणु
	.driver	= अणु
		.name	= "alchemy-ac97c",
		.pm	= AU1XPSCAC97_PMOPS,
	पूर्ण,
	.probe		= au1xac97c_drvprobe,
	.हटाओ		= au1xac97c_drvहटाओ,
पूर्ण;

module_platक्रमm_driver(au1xac97c_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Au1000/1500/1100 AC97C ASoC driver");
MODULE_AUTHOR("Manuel Lauss");
