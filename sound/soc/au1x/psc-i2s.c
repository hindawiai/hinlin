<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Au12x0/Au1550 PSC ALSA ASoC audio support.
 *
 * (c) 2007-2008 MSC Vertriebsges.m.b.H.,
 *	Manuel Lauss <manuel.lauss@gmail.com>
 *
 * Au1xxx-PSC I2S glue.
 *
 * NOTE: so far only PSC slave mode (bit- and frameघड़ी) is supported.
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
#समावेश <यंत्र/mach-au1x00/au1xxx_psc.h>

#समावेश "psc.h"

/* supported I2S DAI hardware क्रमmats */
#घोषणा AU1XPSC_I2S_DAIFMT \
	(SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_LEFT_J |	\
	 SND_SOC_DAIFMT_NB_NF)

/* supported I2S direction */
#घोषणा AU1XPSC_I2S_सूची \
	(SND_SOC_DAIसूची_PLAYBACK | SND_SOC_DAIसूची_CAPTURE)

#घोषणा AU1XPSC_I2S_RATES \
	SNDRV_PCM_RATE_8000_192000

#घोषणा AU1XPSC_I2S_FMTS \
	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE)

#घोषणा I2SSTAT_BUSY(stype)	\
	((stype) == SNDRV_PCM_STREAM_PLAYBACK ? PSC_I2SSTAT_TB : PSC_I2SSTAT_RB)
#घोषणा I2SPCR_START(stype)	\
	((stype) == SNDRV_PCM_STREAM_PLAYBACK ? PSC_I2SPCR_TS : PSC_I2SPCR_RS)
#घोषणा I2SPCR_STOP(stype)	\
	((stype) == SNDRV_PCM_STREAM_PLAYBACK ? PSC_I2SPCR_TP : PSC_I2SPCR_RP)
#घोषणा I2SPCR_CLRFIFO(stype)	\
	((stype) == SNDRV_PCM_STREAM_PLAYBACK ? PSC_I2SPCR_TC : PSC_I2SPCR_RC)


अटल पूर्णांक au1xpsc_i2s_set_fmt(काष्ठा snd_soc_dai *cpu_dai,
			       अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा au1xpsc_audio_data *pscdata = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित दीर्घ ct;
	पूर्णांक ret;

	ret = -EINVAL;

	ct = pscdata->cfg;

	ct &= ~(PSC_I2SCFG_XM | PSC_I2SCFG_MLJ);	/* left-justअगरied */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		ct |= PSC_I2SCFG_XM;	/* enable I2S mode */
		अवरोध;
	हाल SND_SOC_DAIFMT_MSB:
		अवरोध;
	हाल SND_SOC_DAIFMT_LSB:
		ct |= PSC_I2SCFG_MLJ;	/* LSB (right-) justअगरied */
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	ct &= ~(PSC_I2SCFG_BI | PSC_I2SCFG_WI);		/* IB-IF */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		ct |= PSC_I2SCFG_BI | PSC_I2SCFG_WI;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		ct |= PSC_I2SCFG_BI;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		ct |= PSC_I2SCFG_WI;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:	/* CODEC master */
		ct |= PSC_I2SCFG_MS;	/* PSC I2S slave mode */
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:	/* CODEC slave */
		ct &= ~PSC_I2SCFG_MS;	/* PSC I2S Master mode */
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	pscdata->cfg = ct;
	ret = 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक au1xpsc_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा au1xpsc_audio_data *pscdata = snd_soc_dai_get_drvdata(dai);

	पूर्णांक cfgbits;
	अचिन्हित दीर्घ stat;

	/* check अगर the PSC is alपढ़ोy streaming data */
	stat = __raw_पढ़ोl(I2S_STAT(pscdata));
	अगर (stat & (PSC_I2SSTAT_TB | PSC_I2SSTAT_RB)) अणु
		/* reject parameters not currently set up in hardware */
		cfgbits = __raw_पढ़ोl(I2S_CFG(pscdata));
		अगर ((PSC_I2SCFG_GET_LEN(cfgbits) != params->msbits) ||
		    (params_rate(params) != pscdata->rate))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* set sample bitdepth */
		pscdata->cfg &= ~(0x1f << 4);
		pscdata->cfg |= PSC_I2SCFG_SET_LEN(params->msbits);
		/* remember current rate क्रम other stream */
		pscdata->rate = params_rate(params);
	पूर्ण
	वापस 0;
पूर्ण

/* Configure PSC late:  on my devel प्रणालीs the codec  is I2S master and
 * supplies the i2sbitघड़ी __AND__ i2sMclk (!) to the PSC unit.  ASoC
 * uses aggressive PM and  चयनes the codec off  when it is not in use
 * which also means the PSC unit करोesn't get any घड़ीs and is thereक्रमe
 * dead. That's why this chunk here माला_लो called from the trigger callback
 * because I can be reasonably certain the codec is driving the घड़ीs.
 */
अटल पूर्णांक au1xpsc_i2s_configure(काष्ठा au1xpsc_audio_data *pscdata)
अणु
	अचिन्हित दीर्घ पंचांगo;

	/* bring PSC out of sleep, and configure I2S unit */
	__raw_ग_लिखोl(PSC_CTRL_ENABLE, PSC_CTRL(pscdata));
	wmb(); /* drain ग_लिखोbuffer */

	पंचांगo = 1000000;
	जबतक (!(__raw_पढ़ोl(I2S_STAT(pscdata)) & PSC_I2SSTAT_SR) && पंचांगo)
		पंचांगo--;

	अगर (!पंचांगo)
		जाओ psc_err;

	__raw_ग_लिखोl(0, I2S_CFG(pscdata));
	wmb(); /* drain ग_लिखोbuffer */
	__raw_ग_लिखोl(pscdata->cfg | PSC_I2SCFG_DE_ENABLE, I2S_CFG(pscdata));
	wmb(); /* drain ग_लिखोbuffer */

	/* रुको क्रम I2S controller to become पढ़ोy */
	पंचांगo = 1000000;
	जबतक (!(__raw_पढ़ोl(I2S_STAT(pscdata)) & PSC_I2SSTAT_DR) && पंचांगo)
		पंचांगo--;

	अगर (पंचांगo)
		वापस 0;

psc_err:
	__raw_ग_लिखोl(0, I2S_CFG(pscdata));
	__raw_ग_लिखोl(PSC_CTRL_SUSPEND, PSC_CTRL(pscdata));
	wmb(); /* drain ग_लिखोbuffer */
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक au1xpsc_i2s_start(काष्ठा au1xpsc_audio_data *pscdata, पूर्णांक stype)
अणु
	अचिन्हित दीर्घ पंचांगo, stat;
	पूर्णांक ret;

	ret = 0;

	/* अगर both TX and RX are idle, configure the PSC  */
	stat = __raw_पढ़ोl(I2S_STAT(pscdata));
	अगर (!(stat & (PSC_I2SSTAT_TB | PSC_I2SSTAT_RB))) अणु
		ret = au1xpsc_i2s_configure(pscdata);
		अगर (ret)
			जाओ out;
	पूर्ण

	__raw_ग_लिखोl(I2SPCR_CLRFIFO(stype), I2S_PCR(pscdata));
	wmb(); /* drain ग_लिखोbuffer */
	__raw_ग_लिखोl(I2SPCR_START(stype), I2S_PCR(pscdata));
	wmb(); /* drain ग_लिखोbuffer */

	/* रुको क्रम start confirmation */
	पंचांगo = 1000000;
	जबतक (!(__raw_पढ़ोl(I2S_STAT(pscdata)) & I2SSTAT_BUSY(stype)) && पंचांगo)
		पंचांगo--;

	अगर (!पंचांगo) अणु
		__raw_ग_लिखोl(I2SPCR_STOP(stype), I2S_PCR(pscdata));
		wmb(); /* drain ग_लिखोbuffer */
		ret = -ETIMEDOUT;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक au1xpsc_i2s_stop(काष्ठा au1xpsc_audio_data *pscdata, पूर्णांक stype)
अणु
	अचिन्हित दीर्घ पंचांगo, stat;

	__raw_ग_लिखोl(I2SPCR_STOP(stype), I2S_PCR(pscdata));
	wmb(); /* drain ग_लिखोbuffer */

	/* रुको क्रम stop confirmation */
	पंचांगo = 1000000;
	जबतक ((__raw_पढ़ोl(I2S_STAT(pscdata)) & I2SSTAT_BUSY(stype)) && पंचांगo)
		पंचांगo--;

	/* अगर both TX and RX are idle, disable PSC */
	stat = __raw_पढ़ोl(I2S_STAT(pscdata));
	अगर (!(stat & (PSC_I2SSTAT_TB | PSC_I2SSTAT_RB))) अणु
		__raw_ग_लिखोl(0, I2S_CFG(pscdata));
		wmb(); /* drain ग_लिखोbuffer */
		__raw_ग_लिखोl(PSC_CTRL_SUSPEND, PSC_CTRL(pscdata));
		wmb(); /* drain ग_लिखोbuffer */
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक au1xpsc_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा au1xpsc_audio_data *pscdata = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret, stype = substream->stream;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		ret = au1xpsc_i2s_start(pscdata, stype);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		ret = au1xpsc_i2s_stop(pscdata, stype);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक au1xpsc_i2s_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा au1xpsc_audio_data *pscdata = snd_soc_dai_get_drvdata(dai);
	snd_soc_dai_set_dma_data(dai, substream, &pscdata->dmaids[0]);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops au1xpsc_i2s_dai_ops = अणु
	.startup	= au1xpsc_i2s_startup,
	.trigger	= au1xpsc_i2s_trigger,
	.hw_params	= au1xpsc_i2s_hw_params,
	.set_fmt	= au1xpsc_i2s_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_driver au1xpsc_i2s_dai_ढाँचा = अणु
	.playback = अणु
		.rates		= AU1XPSC_I2S_RATES,
		.क्रमmats	= AU1XPSC_I2S_FMTS,
		.channels_min	= 2,
		.channels_max	= 8,	/* 2 without बाह्यal help */
	पूर्ण,
	.capture = अणु
		.rates		= AU1XPSC_I2S_RATES,
		.क्रमmats	= AU1XPSC_I2S_FMTS,
		.channels_min	= 2,
		.channels_max	= 8,	/* 2 without बाह्यal help */
	पूर्ण,
	.ops = &au1xpsc_i2s_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver au1xpsc_i2s_component = अणु
	.name		= "au1xpsc-i2s",
पूर्ण;

अटल पूर्णांक au1xpsc_i2s_drvprobe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *dmares;
	अचिन्हित दीर्घ sel;
	काष्ठा au1xpsc_audio_data *wd;

	wd = devm_kzalloc(&pdev->dev, माप(काष्ठा au1xpsc_audio_data),
			  GFP_KERNEL);
	अगर (!wd)
		वापस -ENOMEM;

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

	/* preserve PSC घड़ी source set up by platक्रमm (dev.platक्रमm_data
	 * is alपढ़ोy occupied by soc layer)
	 */
	sel = __raw_पढ़ोl(PSC_SEL(wd)) & PSC_SEL_CLK_MASK;
	__raw_ग_लिखोl(PSC_CTRL_DISABLE, PSC_CTRL(wd));
	wmb(); /* drain ग_लिखोbuffer */
	__raw_ग_लिखोl(PSC_SEL_PS_I2SMODE | sel, PSC_SEL(wd));
	__raw_ग_लिखोl(0, I2S_CFG(wd));
	wmb(); /* drain ग_लिखोbuffer */

	/* preconfigure: set max rx/tx fअगरo depths */
	wd->cfg |= PSC_I2SCFG_RT_FIFO8 | PSC_I2SCFG_TT_FIFO8;

	/* करोn't रुको क्रम I2S core to become पढ़ोy now; घड़ीs may not
	 * be running yet; depending on घड़ी input क्रम PSC a रुको might
	 * समय out.
	 */

	/* name the DAI like this device instance ("au1xpsc-i2s.PSCINDEX") */
	स_नकल(&wd->dai_drv, &au1xpsc_i2s_dai_ढाँचा,
	       माप(काष्ठा snd_soc_dai_driver));
	wd->dai_drv.name = dev_name(&pdev->dev);

	platक्रमm_set_drvdata(pdev, wd);

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
				&au1xpsc_i2s_component, &wd->dai_drv, 1);
पूर्ण

अटल पूर्णांक au1xpsc_i2s_drvहटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा au1xpsc_audio_data *wd = platक्रमm_get_drvdata(pdev);

	__raw_ग_लिखोl(0, I2S_CFG(wd));
	wmb(); /* drain ग_लिखोbuffer */
	__raw_ग_लिखोl(PSC_CTRL_DISABLE, PSC_CTRL(wd));
	wmb(); /* drain ग_लिखोbuffer */

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक au1xpsc_i2s_drvsuspend(काष्ठा device *dev)
अणु
	काष्ठा au1xpsc_audio_data *wd = dev_get_drvdata(dev);

	/* save पूर्णांकeresting रेजिस्टर and disable PSC */
	wd->pm[0] = __raw_पढ़ोl(PSC_SEL(wd));

	__raw_ग_लिखोl(0, I2S_CFG(wd));
	wmb(); /* drain ग_लिखोbuffer */
	__raw_ग_लिखोl(PSC_CTRL_DISABLE, PSC_CTRL(wd));
	wmb(); /* drain ग_लिखोbuffer */

	वापस 0;
पूर्ण

अटल पूर्णांक au1xpsc_i2s_drvresume(काष्ठा device *dev)
अणु
	काष्ठा au1xpsc_audio_data *wd = dev_get_drvdata(dev);

	/* select I2S mode and PSC घड़ी */
	__raw_ग_लिखोl(PSC_CTRL_DISABLE, PSC_CTRL(wd));
	wmb(); /* drain ग_लिखोbuffer */
	__raw_ग_लिखोl(0, PSC_SEL(wd));
	wmb(); /* drain ग_लिखोbuffer */
	__raw_ग_लिखोl(wd->pm[0], PSC_SEL(wd));
	wmb(); /* drain ग_लिखोbuffer */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops au1xpsci2s_pmops = अणु
	.suspend	= au1xpsc_i2s_drvsuspend,
	.resume		= au1xpsc_i2s_drvresume,
पूर्ण;

#घोषणा AU1XPSCI2S_PMOPS &au1xpsci2s_pmops

#अन्यथा

#घोषणा AU1XPSCI2S_PMOPS शून्य

#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver au1xpsc_i2s_driver = अणु
	.driver		= अणु
		.name	= "au1xpsc_i2s",
		.pm	= AU1XPSCI2S_PMOPS,
	पूर्ण,
	.probe		= au1xpsc_i2s_drvprobe,
	.हटाओ		= au1xpsc_i2s_drvहटाओ,
पूर्ण;

module_platक्रमm_driver(au1xpsc_i2s_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Au12x0/Au1550 PSC I2S ALSA ASoC audio driver");
MODULE_AUTHOR("Manuel Lauss");
