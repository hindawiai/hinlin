<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Au12x0/Au1550 PSC ALSA ASoC audio support.
 *
 * (c) 2007-2009 MSC Vertriebsges.m.b.H.,
 *	Manuel Lauss <manuel.lauss@gmail.com>
 *
 * Au1xxx-PSC AC97 glue.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/suspend.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_psc.h>

#समावेश "psc.h"

/* how often to retry failed codec रेजिस्टर पढ़ोs/ग_लिखोs */
#घोषणा AC97_RW_RETRIES	5

#घोषणा AC97_सूची	\
	(SND_SOC_DAIसूची_PLAYBACK | SND_SOC_DAIसूची_CAPTURE)

#घोषणा AC97_RATES	\
	SNDRV_PCM_RATE_8000_48000

#घोषणा AC97_FMTS	\
	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3BE)

#घोषणा AC97PCR_START(stype)	\
	((stype) == SNDRV_PCM_STREAM_PLAYBACK ? PSC_AC97PCR_TS : PSC_AC97PCR_RS)
#घोषणा AC97PCR_STOP(stype)	\
	((stype) == SNDRV_PCM_STREAM_PLAYBACK ? PSC_AC97PCR_TP : PSC_AC97PCR_RP)
#घोषणा AC97PCR_CLRFIFO(stype)	\
	((stype) == SNDRV_PCM_STREAM_PLAYBACK ? PSC_AC97PCR_TC : PSC_AC97PCR_RC)

#घोषणा AC97STAT_BUSY(stype)	\
	((stype) == SNDRV_PCM_STREAM_PLAYBACK ? PSC_AC97STAT_TB : PSC_AC97STAT_RB)

/* instance data. There can be only one, MacLeod!!!! */
अटल काष्ठा au1xpsc_audio_data *au1xpsc_ac97_workdata;

#अगर 0

/* this could theoretically work, but ac97->bus->card->निजी_data can be शून्य
 * when snd_ac97_mixer() is called; I करोn't know अगर the rest further करोwn the
 * chain are always valid either.
 */
अटल अंतरभूत काष्ठा au1xpsc_audio_data *ac97_to_pscdata(काष्ठा snd_ac97 *x)
अणु
	काष्ठा snd_soc_card *c = x->bus->card->निजी_data;
	वापस snd_soc_dai_get_drvdata(c->asoc_rtd_to_cpu(rtd, 0));
पूर्ण

#अन्यथा

#घोषणा ac97_to_pscdata(x)	au1xpsc_ac97_workdata

#पूर्ण_अगर

/* AC97 controller पढ़ोs codec रेजिस्टर */
अटल अचिन्हित लघु au1xpsc_ac97_पढ़ो(काष्ठा snd_ac97 *ac97,
					अचिन्हित लघु reg)
अणु
	काष्ठा au1xpsc_audio_data *pscdata = ac97_to_pscdata(ac97);
	अचिन्हित लघु retry, पंचांगo;
	अचिन्हित दीर्घ data;

	__raw_ग_लिखोl(PSC_AC97EVNT_CD, AC97_EVNT(pscdata));
	wmb(); /* drain ग_लिखोbuffer */

	retry = AC97_RW_RETRIES;
	करो अणु
		mutex_lock(&pscdata->lock);

		__raw_ग_लिखोl(PSC_AC97CDC_RD | PSC_AC97CDC_INDX(reg),
			  AC97_CDC(pscdata));
		wmb(); /* drain ग_लिखोbuffer */

		पंचांगo = 20;
		करो अणु
			udelay(21);
			अगर (__raw_पढ़ोl(AC97_EVNT(pscdata)) & PSC_AC97EVNT_CD)
				अवरोध;
		पूर्ण जबतक (--पंचांगo);

		data = __raw_पढ़ोl(AC97_CDC(pscdata));

		__raw_ग_लिखोl(PSC_AC97EVNT_CD, AC97_EVNT(pscdata));
		wmb(); /* drain ग_लिखोbuffer */

		mutex_unlock(&pscdata->lock);

		अगर (reg != ((data >> 16) & 0x7f))
			पंचांगo = 1;	/* wrong रेजिस्टर, try again */

	पूर्ण जबतक (--retry && !पंचांगo);

	वापस retry ? data & 0xffff : 0xffff;
पूर्ण

/* AC97 controller ग_लिखोs to codec रेजिस्टर */
अटल व्योम au1xpsc_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg,
				अचिन्हित लघु val)
अणु
	काष्ठा au1xpsc_audio_data *pscdata = ac97_to_pscdata(ac97);
	अचिन्हित पूर्णांक पंचांगo, retry;

	__raw_ग_लिखोl(PSC_AC97EVNT_CD, AC97_EVNT(pscdata));
	wmb(); /* drain ग_लिखोbuffer */

	retry = AC97_RW_RETRIES;
	करो अणु
		mutex_lock(&pscdata->lock);

		__raw_ग_लिखोl(PSC_AC97CDC_INDX(reg) | (val & 0xffff),
			  AC97_CDC(pscdata));
		wmb(); /* drain ग_लिखोbuffer */

		पंचांगo = 20;
		करो अणु
			udelay(21);
			अगर (__raw_पढ़ोl(AC97_EVNT(pscdata)) & PSC_AC97EVNT_CD)
				अवरोध;
		पूर्ण जबतक (--पंचांगo);

		__raw_ग_लिखोl(PSC_AC97EVNT_CD, AC97_EVNT(pscdata));
		wmb(); /* drain ग_लिखोbuffer */

		mutex_unlock(&pscdata->lock);
	पूर्ण जबतक (--retry && !पंचांगo);
पूर्ण

/* AC97 controller निश्चितs a warm reset */
अटल व्योम au1xpsc_ac97_warm_reset(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा au1xpsc_audio_data *pscdata = ac97_to_pscdata(ac97);

	__raw_ग_लिखोl(PSC_AC97RST_SNC, AC97_RST(pscdata));
	wmb(); /* drain ग_लिखोbuffer */
	msleep(10);
	__raw_ग_लिखोl(0, AC97_RST(pscdata));
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण

अटल व्योम au1xpsc_ac97_cold_reset(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा au1xpsc_audio_data *pscdata = ac97_to_pscdata(ac97);
	पूर्णांक i;

	/* disable PSC during cold reset */
	__raw_ग_लिखोl(0, AC97_CFG(au1xpsc_ac97_workdata));
	wmb(); /* drain ग_लिखोbuffer */
	__raw_ग_लिखोl(PSC_CTRL_DISABLE, PSC_CTRL(pscdata));
	wmb(); /* drain ग_लिखोbuffer */

	/* issue cold reset */
	__raw_ग_लिखोl(PSC_AC97RST_RST, AC97_RST(pscdata));
	wmb(); /* drain ग_लिखोbuffer */
	msleep(500);
	__raw_ग_लिखोl(0, AC97_RST(pscdata));
	wmb(); /* drain ग_लिखोbuffer */

	/* enable PSC */
	__raw_ग_लिखोl(PSC_CTRL_ENABLE, PSC_CTRL(pscdata));
	wmb(); /* drain ग_लिखोbuffer */

	/* रुको क्रम PSC to indicate it's पढ़ोy */
	i = 1000;
	जबतक (!((__raw_पढ़ोl(AC97_STAT(pscdata)) & PSC_AC97STAT_SR)) && (--i))
		msleep(1);

	अगर (i == 0) अणु
		prपूर्णांकk(KERN_ERR "au1xpsc-ac97: PSC not ready!\n");
		वापस;
	पूर्ण

	/* enable the ac97 function */
	__raw_ग_लिखोl(pscdata->cfg | PSC_AC97CFG_DE_ENABLE, AC97_CFG(pscdata));
	wmb(); /* drain ग_लिखोbuffer */

	/* रुको क्रम AC97 core to become पढ़ोy */
	i = 1000;
	जबतक (!((__raw_पढ़ोl(AC97_STAT(pscdata)) & PSC_AC97STAT_DR)) && (--i))
		msleep(1);
	अगर (i == 0)
		prपूर्णांकk(KERN_ERR "au1xpsc-ac97: AC97 ctrl not ready\n");
पूर्ण

/* AC97 controller operations */
अटल काष्ठा snd_ac97_bus_ops psc_ac97_ops = अणु
	.पढ़ो		= au1xpsc_ac97_पढ़ो,
	.ग_लिखो		= au1xpsc_ac97_ग_लिखो,
	.reset		= au1xpsc_ac97_cold_reset,
	.warm_reset	= au1xpsc_ac97_warm_reset,
पूर्ण;

अटल पूर्णांक au1xpsc_ac97_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा au1xpsc_audio_data *pscdata = snd_soc_dai_get_drvdata(dai);
	अचिन्हित दीर्घ r, ro, stat;
	पूर्णांक chans, t, stype = substream->stream;

	chans = params_channels(params);

	r = ro = __raw_पढ़ोl(AC97_CFG(pscdata));
	stat = __raw_पढ़ोl(AC97_STAT(pscdata));

	/* alपढ़ोy active? */
	अगर (stat & (PSC_AC97STAT_TB | PSC_AC97STAT_RB)) अणु
		/* reject parameters not currently set up */
		अगर ((PSC_AC97CFG_GET_LEN(r) != params->msbits) ||
		    (pscdata->rate != params_rate(params)))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु

		/* set sample bitdepth: REG[24:21]=(BITS-2)/2 */
		r &= ~PSC_AC97CFG_LEN_MASK;
		r |= PSC_AC97CFG_SET_LEN(params->msbits);

		/* channels: enable slots क्रम front L/R channel */
		अगर (stype == SNDRV_PCM_STREAM_PLAYBACK) अणु
			r &= ~PSC_AC97CFG_TXSLOT_MASK;
			r |= PSC_AC97CFG_TXSLOT_ENA(3);
			r |= PSC_AC97CFG_TXSLOT_ENA(4);
		पूर्ण अन्यथा अणु
			r &= ~PSC_AC97CFG_RXSLOT_MASK;
			r |= PSC_AC97CFG_RXSLOT_ENA(3);
			r |= PSC_AC97CFG_RXSLOT_ENA(4);
		पूर्ण

		/* करो we need to poke the hardware? */
		अगर (!(r ^ ro))
			जाओ out;

		/* ac97 engine is about to be disabled */
		mutex_lock(&pscdata->lock);

		/* disable AC97 device controller first... */
		__raw_ग_लिखोl(r & ~PSC_AC97CFG_DE_ENABLE, AC97_CFG(pscdata));
		wmb(); /* drain ग_लिखोbuffer */

		/* ...रुको क्रम it... */
		t = 100;
		जबतक ((__raw_पढ़ोl(AC97_STAT(pscdata)) & PSC_AC97STAT_DR) && --t)
			msleep(1);

		अगर (!t)
			prपूर्णांकk(KERN_ERR "PSC-AC97: can't disable!\n");

		/* ...ग_लिखो config... */
		__raw_ग_लिखोl(r, AC97_CFG(pscdata));
		wmb(); /* drain ग_लिखोbuffer */

		/* ...enable the AC97 controller again... */
		__raw_ग_लिखोl(r | PSC_AC97CFG_DE_ENABLE, AC97_CFG(pscdata));
		wmb(); /* drain ग_लिखोbuffer */

		/* ...and रुको क्रम पढ़ोy bit */
		t = 100;
		जबतक ((!(__raw_पढ़ोl(AC97_STAT(pscdata)) & PSC_AC97STAT_DR)) && --t)
			msleep(1);

		अगर (!t)
			prपूर्णांकk(KERN_ERR "PSC-AC97: can't enable!\n");

		mutex_unlock(&pscdata->lock);

		pscdata->cfg = r;
		pscdata->rate = params_rate(params);
	पूर्ण

out:
	वापस 0;
पूर्ण

अटल पूर्णांक au1xpsc_ac97_trigger(काष्ठा snd_pcm_substream *substream,
				पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा au1xpsc_audio_data *pscdata = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret, stype = substream->stream;

	ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		__raw_ग_लिखोl(AC97PCR_CLRFIFO(stype), AC97_PCR(pscdata));
		wmb(); /* drain ग_लिखोbuffer */
		__raw_ग_लिखोl(AC97PCR_START(stype), AC97_PCR(pscdata));
		wmb(); /* drain ग_लिखोbuffer */
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		__raw_ग_लिखोl(AC97PCR_STOP(stype), AC97_PCR(pscdata));
		wmb(); /* drain ग_लिखोbuffer */

		जबतक (__raw_पढ़ोl(AC97_STAT(pscdata)) & AC97STAT_BUSY(stype))
			यंत्र अस्थिर ("nop");

		__raw_ग_लिखोl(AC97PCR_CLRFIFO(stype), AC97_PCR(pscdata));
		wmb(); /* drain ग_लिखोbuffer */

		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक au1xpsc_ac97_startup(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा au1xpsc_audio_data *pscdata = snd_soc_dai_get_drvdata(dai);
	snd_soc_dai_set_dma_data(dai, substream, &pscdata->dmaids[0]);
	वापस 0;
पूर्ण

अटल पूर्णांक au1xpsc_ac97_probe(काष्ठा snd_soc_dai *dai)
अणु
	वापस au1xpsc_ac97_workdata ? 0 : -ENODEV;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops au1xpsc_ac97_dai_ops = अणु
	.startup	= au1xpsc_ac97_startup,
	.trigger	= au1xpsc_ac97_trigger,
	.hw_params	= au1xpsc_ac97_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_driver au1xpsc_ac97_dai_ढाँचा = अणु
	.probe			= au1xpsc_ac97_probe,
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
	.ops = &au1xpsc_ac97_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver au1xpsc_ac97_component = अणु
	.name		= "au1xpsc-ac97",
पूर्ण;

अटल पूर्णांक au1xpsc_ac97_drvprobe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा resource *dmares;
	अचिन्हित दीर्घ sel;
	काष्ठा au1xpsc_audio_data *wd;

	wd = devm_kzalloc(&pdev->dev, माप(काष्ठा au1xpsc_audio_data),
			  GFP_KERNEL);
	अगर (!wd)
		वापस -ENOMEM;

	mutex_init(&wd->lock);

	wd->mmio = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(wd->mmio))
		वापस PTR_ERR(wd->mmio);

	dmares = platक्रमm_get_resource(pdev, IORESOURCE_DMA, 0);
	अगर (!dmares)
		वापस -EBUSY;
	wd->dmaids[SNDRV_PCM_STREAM_PLAYBACK] = dmares->start;

	dmares = platक्रमm_get_resource(pdev, IORESOURCE_DMA, 1);
	अगर (!dmares)
		वापस -EBUSY;
	wd->dmaids[SNDRV_PCM_STREAM_CAPTURE] = dmares->start;

	/* configuration: max dma trigger threshold, enable ac97 */
	wd->cfg = PSC_AC97CFG_RT_FIFO8 | PSC_AC97CFG_TT_FIFO8 |
		  PSC_AC97CFG_DE_ENABLE;

	/* preserve PSC घड़ी source set up by platक्रमm	 */
	sel = __raw_पढ़ोl(PSC_SEL(wd)) & PSC_SEL_CLK_MASK;
	__raw_ग_लिखोl(PSC_CTRL_DISABLE, PSC_CTRL(wd));
	wmb(); /* drain ग_लिखोbuffer */
	__raw_ग_लिखोl(0, PSC_SEL(wd));
	wmb(); /* drain ग_लिखोbuffer */
	__raw_ग_लिखोl(PSC_SEL_PS_AC97MODE | sel, PSC_SEL(wd));
	wmb(); /* drain ग_लिखोbuffer */

	/* name the DAI like this device instance ("au1xpsc-ac97.PSCINDEX") */
	स_नकल(&wd->dai_drv, &au1xpsc_ac97_dai_ढाँचा,
	       माप(काष्ठा snd_soc_dai_driver));
	wd->dai_drv.name = dev_name(&pdev->dev);

	platक्रमm_set_drvdata(pdev, wd);

	ret = snd_soc_set_ac97_ops(&psc_ac97_ops);
	अगर (ret)
		वापस ret;

	ret = snd_soc_रेजिस्टर_component(&pdev->dev, &au1xpsc_ac97_component,
					 &wd->dai_drv, 1);
	अगर (ret)
		वापस ret;

	au1xpsc_ac97_workdata = wd;
	वापस 0;
पूर्ण

अटल पूर्णांक au1xpsc_ac97_drvहटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा au1xpsc_audio_data *wd = platक्रमm_get_drvdata(pdev);

	snd_soc_unरेजिस्टर_component(&pdev->dev);

	/* disable PSC completely */
	__raw_ग_लिखोl(0, AC97_CFG(wd));
	wmb(); /* drain ग_लिखोbuffer */
	__raw_ग_लिखोl(PSC_CTRL_DISABLE, PSC_CTRL(wd));
	wmb(); /* drain ग_लिखोbuffer */

	au1xpsc_ac97_workdata = शून्य;	/* MDEV */

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक au1xpsc_ac97_drvsuspend(काष्ठा device *dev)
अणु
	काष्ठा au1xpsc_audio_data *wd = dev_get_drvdata(dev);

	/* save पूर्णांकeresting रेजिस्टरs and disable PSC */
	wd->pm[0] = __raw_पढ़ोl(PSC_SEL(wd));

	__raw_ग_लिखोl(0, AC97_CFG(wd));
	wmb(); /* drain ग_लिखोbuffer */
	__raw_ग_लिखोl(PSC_CTRL_DISABLE, PSC_CTRL(wd));
	wmb(); /* drain ग_लिखोbuffer */

	वापस 0;
पूर्ण

अटल पूर्णांक au1xpsc_ac97_drvresume(काष्ठा device *dev)
अणु
	काष्ठा au1xpsc_audio_data *wd = dev_get_drvdata(dev);

	/* restore PSC घड़ी config */
	__raw_ग_लिखोl(wd->pm[0] | PSC_SEL_PS_AC97MODE, PSC_SEL(wd));
	wmb(); /* drain ग_लिखोbuffer */

	/* after this poपूर्णांक the ac97 core will cold-reset the codec.
	 * During cold-reset the PSC is reinitialized and the last
	 * configuration set up in hw_params() is restored.
	 */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops au1xpscac97_pmops = अणु
	.suspend	= au1xpsc_ac97_drvsuspend,
	.resume		= au1xpsc_ac97_drvresume,
पूर्ण;

#घोषणा AU1XPSCAC97_PMOPS &au1xpscac97_pmops

#अन्यथा

#घोषणा AU1XPSCAC97_PMOPS शून्य

#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver au1xpsc_ac97_driver = अणु
	.driver	= अणु
		.name	= "au1xpsc_ac97",
		.pm	= AU1XPSCAC97_PMOPS,
	पूर्ण,
	.probe		= au1xpsc_ac97_drvprobe,
	.हटाओ		= au1xpsc_ac97_drvहटाओ,
पूर्ण;

module_platक्रमm_driver(au1xpsc_ac97_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Au12x0/Au1550 PSC AC97 ALSA ASoC audio driver");
MODULE_AUTHOR("Manuel Lauss");

