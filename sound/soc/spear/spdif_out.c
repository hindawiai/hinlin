<शैली गुरु>
/*
 * ALSA SoC SPDIF Out Audio Layer क्रम spear processors
 *
 * Copyright (C) 2012 ST Microelectronics
 * Vipin Kumar <vipin.kumar@st.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/spear_dma.h>
#समावेश <sound/spear_spdअगर.h>
#समावेश "spdif_out_regs.h"
#समावेश "spear_pcm.h"

काष्ठा spdअगर_out_params अणु
	u32 rate;
	u32 core_freq;
	u32 mute;
पूर्ण;

काष्ठा spdअगर_out_dev अणु
	काष्ठा clk *clk;
	काष्ठा spear_dma_data dma_params;
	काष्ठा spdअगर_out_params saved_params;
	u32 running;
	व्योम __iomem *io_base;
	काष्ठा snd_dmaengine_dai_dma_data dma_params_tx;
	काष्ठा snd_dmaengine_pcm_config config;
पूर्ण;

अटल व्योम spdअगर_out_configure(काष्ठा spdअगर_out_dev *host)
अणु
	ग_लिखोl(SPDIF_OUT_RESET, host->io_base + SPDIF_OUT_SOFT_RST);
	mdelay(1);
	ग_लिखोl(पढ़ोl(host->io_base + SPDIF_OUT_SOFT_RST) & ~SPDIF_OUT_RESET,
			host->io_base + SPDIF_OUT_SOFT_RST);

	ग_लिखोl(SPDIF_OUT_FDMA_TRIG_16 | SPDIF_OUT_MEMFMT_16_16 |
			SPDIF_OUT_VALID_HW | SPDIF_OUT_USER_HW |
			SPDIF_OUT_CHNLSTA_HW | SPDIF_OUT_PARITY_HW,
			host->io_base + SPDIF_OUT_CFG);

	ग_लिखोl(0x7F, host->io_base + SPDIF_OUT_INT_STA_CLR);
	ग_लिखोl(0x7F, host->io_base + SPDIF_OUT_INT_EN_CLR);
पूर्ण

अटल पूर्णांक spdअगर_out_startup(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा spdअगर_out_dev *host = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक ret;

	अगर (substream->stream != SNDRV_PCM_STREAM_PLAYBACK)
		वापस -EINVAL;

	ret = clk_enable(host->clk);
	अगर (ret)
		वापस ret;

	host->running = true;
	spdअगर_out_configure(host);

	वापस 0;
पूर्ण

अटल व्योम spdअगर_out_shutकरोwn(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा spdअगर_out_dev *host = snd_soc_dai_get_drvdata(dai);

	अगर (substream->stream != SNDRV_PCM_STREAM_PLAYBACK)
		वापस;

	clk_disable(host->clk);
	host->running = false;
पूर्ण

अटल व्योम spdअगर_out_घड़ी(काष्ठा spdअगर_out_dev *host, u32 core_freq,
		u32 rate)
अणु
	u32 भागider, ctrl;

	clk_set_rate(host->clk, core_freq);
	भागider = DIV_ROUND_CLOSEST(clk_get_rate(host->clk), (rate * 128));

	ctrl = पढ़ोl(host->io_base + SPDIF_OUT_CTRL);
	ctrl &= ~SPDIF_DIVIDER_MASK;
	ctrl |= (भागider << SPDIF_DIVIDER_SHIFT) & SPDIF_DIVIDER_MASK;
	ग_लिखोl(ctrl, host->io_base + SPDIF_OUT_CTRL);
पूर्ण

अटल पूर्णांक spdअगर_out_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा spdअगर_out_dev *host = snd_soc_dai_get_drvdata(dai);
	u32 rate, core_freq;

	अगर (substream->stream != SNDRV_PCM_STREAM_PLAYBACK)
		वापस -EINVAL;

	rate = params_rate(params);

	चयन (rate) अणु
	हाल 8000:
	हाल 16000:
	हाल 32000:
	हाल 64000:
		/*
		 * The घड़ी is multiplied by 10 to bring it to feasible range
		 * of frequencies क्रम sscg
		 */
		core_freq = 64000 * 128 * 10;	/* 81.92 MHz */
		अवरोध;
	हाल 5512:
	हाल 11025:
	हाल 22050:
	हाल 44100:
	हाल 88200:
	हाल 176400:
		core_freq = 176400 * 128;	/* 22.5792 MHz */
		अवरोध;
	हाल 48000:
	हाल 96000:
	हाल 192000:
	शेष:
		core_freq = 192000 * 128;	/* 24.576 MHz */
		अवरोध;
	पूर्ण

	spdअगर_out_घड़ी(host, core_freq, rate);
	host->saved_params.core_freq = core_freq;
	host->saved_params.rate = rate;

	वापस 0;
पूर्ण

अटल पूर्णांक spdअगर_out_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा spdअगर_out_dev *host = snd_soc_dai_get_drvdata(dai);
	u32 ctrl;
	पूर्णांक ret = 0;

	अगर (substream->stream != SNDRV_PCM_STREAM_PLAYBACK)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
			ctrl = पढ़ोl(host->io_base + SPDIF_OUT_CTRL);
			ctrl &= ~SPDIF_OPMODE_MASK;
			अगर (!host->saved_params.mute)
				ctrl |= SPDIF_OPMODE_AUD_DATA |
					SPDIF_STATE_NORMAL;
			अन्यथा
				ctrl |= SPDIF_OPMODE_MUTE_PCM;
			ग_लिखोl(ctrl, host->io_base + SPDIF_OUT_CTRL);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ctrl = पढ़ोl(host->io_base + SPDIF_OUT_CTRL);
		ctrl &= ~SPDIF_OPMODE_MASK;
		ctrl |= SPDIF_OPMODE_OFF;
		ग_लिखोl(ctrl, host->io_base + SPDIF_OUT_CTRL);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक spdअगर_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा spdअगर_out_dev *host = snd_soc_dai_get_drvdata(dai);
	u32 val;

	host->saved_params.mute = mute;
	val = पढ़ोl(host->io_base + SPDIF_OUT_CTRL);
	val &= ~SPDIF_OPMODE_MASK;

	अगर (mute)
		val |= SPDIF_OPMODE_MUTE_PCM;
	अन्यथा अणु
		अगर (host->running)
			val |= SPDIF_OPMODE_AUD_DATA | SPDIF_STATE_NORMAL;
		अन्यथा
			val |= SPDIF_OPMODE_OFF;
	पूर्ण

	ग_लिखोl(val, host->io_base + SPDIF_OUT_CTRL);
	वापस 0;
पूर्ण

अटल पूर्णांक spdअगर_mute_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा spdअगर_out_dev *host = snd_soc_dai_get_drvdata(cpu_dai);

	ucontrol->value.पूर्णांकeger.value[0] = host->saved_params.mute;
	वापस 0;
पूर्ण

अटल पूर्णांक spdअगर_mute_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dai *cpu_dai = snd_kcontrol_chip(kcontrol);
	काष्ठा spdअगर_out_dev *host = snd_soc_dai_get_drvdata(cpu_dai);

	अगर (host->saved_params.mute == ucontrol->value.पूर्णांकeger.value[0])
		वापस 0;

	spdअगर_mute(cpu_dai, ucontrol->value.पूर्णांकeger.value[0],
		   SNDRV_PCM_STREAM_PLAYBACK);

	वापस 1;
पूर्ण
अटल स्थिर काष्ठा snd_kcontrol_new spdअगर_out_controls[] = अणु
	SOC_SINGLE_BOOL_EXT("IEC958 Playback Switch", 0,
			spdअगर_mute_get, spdअगर_mute_put),
पूर्ण;

अटल पूर्णांक spdअगर_soc_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा spdअगर_out_dev *host = snd_soc_dai_get_drvdata(dai);

	host->dma_params_tx.filter_data = &host->dma_params;
	dai->playback_dma_data = &host->dma_params_tx;

	वापस snd_soc_add_dai_controls(dai, spdअगर_out_controls,
				ARRAY_SIZE(spdअगर_out_controls));
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops spdअगर_out_dai_ops = अणु
	.mute_stream	= spdअगर_mute,
	.startup	= spdअगर_out_startup,
	.shutकरोwn	= spdअगर_out_shutकरोwn,
	.trigger	= spdअगर_out_trigger,
	.hw_params	= spdअगर_out_hw_params,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver spdअगर_out_dai = अणु
	.playback = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = (SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | \
				 SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000 | \
				 SNDRV_PCM_RATE_192000),
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.probe = spdअगर_soc_dai_probe,
	.ops = &spdअगर_out_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver spdअगर_out_component = अणु
	.name		= "spdif-out",
पूर्ण;

अटल पूर्णांक spdअगर_out_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spdअगर_out_dev *host;
	काष्ठा spear_spdअगर_platक्रमm_data *pdata;
	काष्ठा resource *res;
	पूर्णांक ret;

	host = devm_kzalloc(&pdev->dev, माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	host->io_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(host->io_base))
		वापस PTR_ERR(host->io_base);

	host->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(host->clk))
		वापस PTR_ERR(host->clk);

	pdata = dev_get_platdata(&pdev->dev);

	host->dma_params.data = pdata->dma_params;
	host->dma_params.addr = res->start + SPDIF_OUT_FIFO_DATA;
	host->dma_params.max_burst = 16;
	host->dma_params.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;

	dev_set_drvdata(&pdev->dev, host);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &spdअगर_out_component,
					      &spdअगर_out_dai, 1);
	अगर (ret)
		वापस ret;

	वापस devm_spear_pcm_platक्रमm_रेजिस्टर(&pdev->dev, &host->config,
						pdata->filter);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक spdअगर_out_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा spdअगर_out_dev *host = dev_get_drvdata(&pdev->dev);

	अगर (host->running)
		clk_disable(host->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक spdअगर_out_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा spdअगर_out_dev *host = dev_get_drvdata(&pdev->dev);

	अगर (host->running) अणु
		clk_enable(host->clk);
		spdअगर_out_configure(host);
		spdअगर_out_घड़ी(host, host->saved_params.core_freq,
				host->saved_params.rate);
	पूर्ण
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(spdअगर_out_dev_pm_ops, spdअगर_out_suspend, \
		spdअगर_out_resume);

#घोषणा SPDIF_OUT_DEV_PM_OPS (&spdअगर_out_dev_pm_ops)

#अन्यथा
#घोषणा SPDIF_OUT_DEV_PM_OPS शून्य

#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver spdअगर_out_driver = अणु
	.probe		= spdअगर_out_probe,
	.driver		= अणु
		.name	= "spdif-out",
		.pm	= SPDIF_OUT_DEV_PM_OPS,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(spdअगर_out_driver);

MODULE_AUTHOR("Vipin Kumar <vipin.kumar@st.com>");
MODULE_DESCRIPTION("SPEAr SPDIF OUT SoC Interface");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:spdif_out");
