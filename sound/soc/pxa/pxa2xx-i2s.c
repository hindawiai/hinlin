<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pxa2xx-i2s.c  --  ALSA Soc Audio Layer
 *
 * Copyright 2005 Wolfson Microelectronics PLC.
 * Author: Liam Girdwood
 *         lrg@slimlogic.co.uk
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/pxa2xx-lib.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश <mach/hardware.h>
#समावेश <mach/audपन.स>

#समावेश "pxa2xx-i2s.h"

/*
 * I2S Controller Register and Bit Definitions
 */
#घोषणा SACR0		__REG(0x40400000)  /* Global Control Register */
#घोषणा SACR1		__REG(0x40400004)  /* Serial Audio I 2 S/MSB-Justअगरied Control Register */
#घोषणा SASR0		__REG(0x4040000C)  /* Serial Audio I 2 S/MSB-Justअगरied Interface and FIFO Status Register */
#घोषणा SAIMR		__REG(0x40400014)  /* Serial Audio Interrupt Mask Register */
#घोषणा SAICR		__REG(0x40400018)  /* Serial Audio Interrupt Clear Register */
#घोषणा SADIV		__REG(0x40400060)  /* Audio Clock Divider Register. */
#घोषणा SADR		__REG(0x40400080)  /* Serial Audio Data Register (TX and RX FIFO access Register). */

#घोषणा SACR0_RFTH(x)	((x) << 12)	/* Rx FIFO Interrupt or DMA Trigger Threshold */
#घोषणा SACR0_TFTH(x)	((x) << 8)	/* Tx FIFO Interrupt or DMA Trigger Threshold */
#घोषणा SACR0_STRF	(1 << 5)	/* FIFO Select क्रम EFWR Special Function */
#घोषणा SACR0_EFWR	(1 << 4)	/* Enable EFWR Function  */
#घोषणा SACR0_RST	(1 << 3)	/* FIFO, i2s Register Reset */
#घोषणा SACR0_BCKD	(1 << 2)	/* Bit Clock Direction */
#घोषणा SACR0_ENB	(1 << 0)	/* Enable I2S Link */
#घोषणा SACR1_ENLBF	(1 << 5)	/* Enable Loopback */
#घोषणा SACR1_DRPL	(1 << 4)	/* Disable Replaying Function */
#घोषणा SACR1_DREC	(1 << 3)	/* Disable Recording Function */
#घोषणा SACR1_AMSL	(1 << 0)	/* Specअगरy Alternate Mode */

#घोषणा SASR0_I2SOFF	(1 << 7)	/* Controller Status */
#घोषणा SASR0_ROR	(1 << 6)	/* Rx FIFO Overrun */
#घोषणा SASR0_TUR	(1 << 5)	/* Tx FIFO Underrun */
#घोषणा SASR0_RFS	(1 << 4)	/* Rx FIFO Service Request */
#घोषणा SASR0_TFS	(1 << 3)	/* Tx FIFO Service Request */
#घोषणा SASR0_BSY	(1 << 2)	/* I2S Busy */
#घोषणा SASR0_RNE	(1 << 1)	/* Rx FIFO Not Empty */
#घोषणा SASR0_TNF	(1 << 0)	/* Tx FIFO Not Empty */

#घोषणा SAICR_ROR	(1 << 6)	/* Clear Rx FIFO Overrun Interrupt */
#घोषणा SAICR_TUR	(1 << 5)	/* Clear Tx FIFO Underrun Interrupt */

#घोषणा SAIMR_ROR	(1 << 6)	/* Enable Rx FIFO Overrun Condition Interrupt */
#घोषणा SAIMR_TUR	(1 << 5)	/* Enable Tx FIFO Underrun Condition Interrupt */
#घोषणा SAIMR_RFS	(1 << 4)	/* Enable Rx FIFO Service Interrupt */
#घोषणा SAIMR_TFS	(1 << 3)	/* Enable Tx FIFO Service Interrupt */

काष्ठा pxa_i2s_port अणु
	u32 saभाग;
	u32 sacr0;
	u32 sacr1;
	u32 saimr;
	पूर्णांक master;
	u32 fmt;
पूर्ण;
अटल काष्ठा pxa_i2s_port pxa_i2s;
अटल काष्ठा clk *clk_i2s;
अटल पूर्णांक clk_ena = 0;

अटल काष्ठा snd_dmaengine_dai_dma_data pxa2xx_i2s_pcm_stereo_out = अणु
	.addr		= __PREG(SADR),
	.addr_width	= DMA_SLAVE_BUSWIDTH_4_BYTES,
	.chan_name	= "tx",
	.maxburst	= 32,
पूर्ण;

अटल काष्ठा snd_dmaengine_dai_dma_data pxa2xx_i2s_pcm_stereo_in = अणु
	.addr		= __PREG(SADR),
	.addr_width	= DMA_SLAVE_BUSWIDTH_4_BYTES,
	.chan_name	= "rx",
	.maxburst	= 32,
पूर्ण;

अटल पूर्णांक pxa2xx_i2s_startup(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);

	अगर (IS_ERR(clk_i2s))
		वापस PTR_ERR(clk_i2s);

	अगर (!snd_soc_dai_active(cpu_dai))
		SACR0 = 0;

	वापस 0;
पूर्ण

/* रुको क्रम I2S controller to be पढ़ोy */
अटल पूर्णांक pxa_i2s_रुको(व्योम)
अणु
	पूर्णांक i;

	/* flush the Rx FIFO */
	क्रम (i = 0; i < 16; i++)
		SADR;
	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_i2s_set_dai_fmt(काष्ठा snd_soc_dai *cpu_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		pxa_i2s.fmt = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		pxa_i2s.fmt = SACR1_AMSL;
		अवरोध;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		pxa_i2s.master = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		pxa_i2s.master = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_i2s_set_dai_sysclk(काष्ठा snd_soc_dai *cpu_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	अगर (clk_id != PXA2XX_I2S_SYSCLK)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;

	अगर (WARN_ON(IS_ERR(clk_i2s)))
		वापस -EINVAL;
	clk_prepare_enable(clk_i2s);
	clk_ena = 1;
	pxa_i2s_रुको();

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dma_data = &pxa2xx_i2s_pcm_stereo_out;
	अन्यथा
		dma_data = &pxa2xx_i2s_pcm_stereo_in;

	snd_soc_dai_set_dma_data(dai, substream, dma_data);

	/* is port used by another stream */
	अगर (!(SACR0 & SACR0_ENB)) अणु
		SACR0 = 0;
		अगर (pxa_i2s.master)
			SACR0 |= SACR0_BCKD;

		SACR0 |= SACR0_RFTH(14) | SACR0_TFTH(1);
		SACR1 |= pxa_i2s.fmt;
	पूर्ण
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		SAIMR |= SAIMR_TFS;
	अन्यथा
		SAIMR |= SAIMR_RFS;

	चयन (params_rate(params)) अणु
	हाल 8000:
		SADIV = 0x48;
		अवरोध;
	हाल 11025:
		SADIV = 0x34;
		अवरोध;
	हाल 16000:
		SADIV = 0x24;
		अवरोध;
	हाल 22050:
		SADIV = 0x1a;
		अवरोध;
	हाल 44100:
		SADIV = 0xd;
		अवरोध;
	हाल 48000:
		SADIV = 0xc;
		अवरोध;
	हाल 96000: /* not in manual and possibly slightly inaccurate */
		SADIV = 0x6;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			      काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			SACR1 &= ~SACR1_DRPL;
		अन्यथा
			SACR1 &= ~SACR1_DREC;
		SACR0 |= SACR0_ENB;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम pxa2xx_i2s_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		SACR1 |= SACR1_DRPL;
		SAIMR &= ~SAIMR_TFS;
	पूर्ण अन्यथा अणु
		SACR1 |= SACR1_DREC;
		SAIMR &= ~SAIMR_RFS;
	पूर्ण

	अगर ((SACR1 & (SACR1_DREC | SACR1_DRPL)) == (SACR1_DREC | SACR1_DRPL)) अणु
		SACR0 &= ~SACR0_ENB;
		pxa_i2s_रुको();
		अगर (clk_ena) अणु
			clk_disable_unprepare(clk_i2s);
			clk_ena = 0;
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pxa2xx_soc_pcm_suspend(काष्ठा snd_soc_component *component)
अणु
	/* store रेजिस्टरs */
	pxa_i2s.sacr0 = SACR0;
	pxa_i2s.sacr1 = SACR1;
	pxa_i2s.saimr = SAIMR;
	pxa_i2s.saभाग = SADIV;

	/* deactivate link */
	SACR0 &= ~SACR0_ENB;
	pxa_i2s_रुको();
	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_soc_pcm_resume(काष्ठा snd_soc_component *component)
अणु
	pxa_i2s_रुको();

	SACR0 = pxa_i2s.sacr0 & ~SACR0_ENB;
	SACR1 = pxa_i2s.sacr1;
	SAIMR = pxa_i2s.saimr;
	SADIV = pxa_i2s.saभाग;

	SACR0 = pxa_i2s.sacr0;

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा pxa2xx_soc_pcm_suspend	शून्य
#घोषणा pxa2xx_soc_pcm_resume	शून्य
#पूर्ण_अगर

अटल पूर्णांक pxa2xx_i2s_probe(काष्ठा snd_soc_dai *dai)
अणु
	clk_i2s = clk_get(dai->dev, "I2SCLK");
	अगर (IS_ERR(clk_i2s))
		वापस PTR_ERR(clk_i2s);

	/*
	 * PXA Developer's Manual:
	 * If SACR0[ENB] is toggled in the middle of a normal operation,
	 * the SACR0[RST] bit must also be set and cleared to reset all
	 * I2S controller रेजिस्टरs.
	 */
	SACR0 = SACR0_RST;
	SACR0 = 0;
	/* Make sure RPL and REC are disabled */
	SACR1 = SACR1_DRPL | SACR1_DREC;
	/* Aदीर्घ with FIFO servicing */
	SAIMR &= ~(SAIMR_RFS | SAIMR_TFS);

	snd_soc_dai_init_dma_data(dai, &pxa2xx_i2s_pcm_stereo_out,
		&pxa2xx_i2s_pcm_stereo_in);

	वापस 0;
पूर्ण

अटल पूर्णांक  pxa2xx_i2s_हटाओ(काष्ठा snd_soc_dai *dai)
अणु
	clk_put(clk_i2s);
	clk_i2s = ERR_PTR(-ENOENT);
	वापस 0;
पूर्ण

#घोषणा PXA2XX_I2S_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 |\
		SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 | SNDRV_PCM_RATE_44100 | \
		SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000)

अटल स्थिर काष्ठा snd_soc_dai_ops pxa_i2s_dai_ops = अणु
	.startup	= pxa2xx_i2s_startup,
	.shutकरोwn	= pxa2xx_i2s_shutकरोwn,
	.trigger	= pxa2xx_i2s_trigger,
	.hw_params	= pxa2xx_i2s_hw_params,
	.set_fmt	= pxa2xx_i2s_set_dai_fmt,
	.set_sysclk	= pxa2xx_i2s_set_dai_sysclk,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver pxa_i2s_dai = अणु
	.probe = pxa2xx_i2s_probe,
	.हटाओ = pxa2xx_i2s_हटाओ,
	.playback = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = PXA2XX_I2S_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,पूर्ण,
	.capture = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = PXA2XX_I2S_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,पूर्ण,
	.ops = &pxa_i2s_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver pxa_i2s_component = अणु
	.name		= "pxa-i2s",
	.pcm_स्थिरruct	= pxa2xx_soc_pcm_new,
	.pcm_deकाष्ठा	= pxa2xx_soc_pcm_मुक्त,
	.खोलो		= pxa2xx_soc_pcm_खोलो,
	.बंद		= pxa2xx_soc_pcm_बंद,
	.hw_params	= pxa2xx_soc_pcm_hw_params,
	.hw_मुक्त	= pxa2xx_soc_pcm_hw_मुक्त,
	.prepare	= pxa2xx_soc_pcm_prepare,
	.trigger	= pxa2xx_soc_pcm_trigger,
	.poपूर्णांकer	= pxa2xx_soc_pcm_poपूर्णांकer,
	.mmap		= pxa2xx_soc_pcm_mmap,
	.suspend	= pxa2xx_soc_pcm_suspend,
	.resume		= pxa2xx_soc_pcm_resume,
पूर्ण;

अटल पूर्णांक pxa2xx_i2s_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev, &pxa_i2s_component,
					       &pxa_i2s_dai, 1);
पूर्ण

अटल काष्ठा platक्रमm_driver pxa2xx_i2s_driver = अणु
	.probe = pxa2xx_i2s_drv_probe,

	.driver = अणु
		.name = "pxa2xx-i2s",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init pxa2xx_i2s_init(व्योम)
अणु
	clk_i2s = ERR_PTR(-ENOENT);
	वापस platक्रमm_driver_रेजिस्टर(&pxa2xx_i2s_driver);
पूर्ण

अटल व्योम __निकास pxa2xx_i2s_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&pxa2xx_i2s_driver);
पूर्ण

module_init(pxa2xx_i2s_init);
module_निकास(pxa2xx_i2s_निकास);

/* Module inक्रमmation */
MODULE_AUTHOR("Liam Girdwood, lrg@slimlogic.co.uk");
MODULE_DESCRIPTION("pxa2xx I2S SoC Interface");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pxa2xx-i2s");
