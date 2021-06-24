<शैली गुरु>
/*
 * ALSA SoC SPDIF In Audio Layer क्रम spear processors
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
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/spear_dma.h>
#समावेश <sound/spear_spdअगर.h>
#समावेश "spdif_in_regs.h"
#समावेश "spear_pcm.h"

काष्ठा spdअगर_in_params अणु
	u32 क्रमmat;
पूर्ण;

काष्ठा spdअगर_in_dev अणु
	काष्ठा clk *clk;
	काष्ठा spear_dma_data dma_params;
	काष्ठा spdअगर_in_params saved_params;
	व्योम *io_base;
	काष्ठा device *dev;
	व्योम (*reset_perip)(व्योम);
	पूर्णांक irq;
	काष्ठा snd_dmaengine_dai_dma_data dma_params_rx;
	काष्ठा snd_dmaengine_pcm_config config;
पूर्ण;

अटल व्योम spdअगर_in_configure(काष्ठा spdअगर_in_dev *host)
अणु
	u32 ctrl = SPDIF_IN_PRTYEN | SPDIF_IN_STATEN | SPDIF_IN_USREN |
		SPDIF_IN_VALEN | SPDIF_IN_BLKEN;
	ctrl |= SPDIF_MODE_16BIT | SPDIF_FIFO_THRES_16;

	ग_लिखोl(ctrl, host->io_base + SPDIF_IN_CTRL);
	ग_लिखोl(0xF, host->io_base + SPDIF_IN_IRQ_MASK);
पूर्ण

अटल पूर्णांक spdअगर_in_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा spdअगर_in_dev *host = snd_soc_dai_get_drvdata(dai);

	host->dma_params_rx.filter_data = &host->dma_params;
	dai->capture_dma_data = &host->dma_params_rx;

	वापस 0;
पूर्ण

अटल व्योम spdअगर_in_shutकरोwn(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा spdअगर_in_dev *host = snd_soc_dai_get_drvdata(dai);

	अगर (substream->stream != SNDRV_PCM_STREAM_CAPTURE)
		वापस;

	ग_लिखोl(0x0, host->io_base + SPDIF_IN_IRQ_MASK);
पूर्ण

अटल व्योम spdअगर_in_क्रमmat(काष्ठा spdअगर_in_dev *host, u32 क्रमmat)
अणु
	u32 ctrl = पढ़ोl(host->io_base + SPDIF_IN_CTRL);

	चयन (क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		ctrl |= SPDIF_XTRACT_16BIT;
		अवरोध;

	हाल SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE:
		ctrl &= ~SPDIF_XTRACT_16BIT;
		अवरोध;
	पूर्ण

	ग_लिखोl(ctrl, host->io_base + SPDIF_IN_CTRL);
पूर्ण

अटल पूर्णांक spdअगर_in_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा spdअगर_in_dev *host = snd_soc_dai_get_drvdata(dai);
	u32 क्रमmat;

	अगर (substream->stream != SNDRV_PCM_STREAM_CAPTURE)
		वापस -EINVAL;

	क्रमmat = params_क्रमmat(params);
	host->saved_params.क्रमmat = क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक spdअगर_in_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा spdअगर_in_dev *host = snd_soc_dai_get_drvdata(dai);
	u32 ctrl;
	पूर्णांक ret = 0;

	अगर (substream->stream != SNDRV_PCM_STREAM_CAPTURE)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		clk_enable(host->clk);
		spdअगर_in_configure(host);
		spdअगर_in_क्रमmat(host, host->saved_params.क्रमmat);

		ctrl = पढ़ोl(host->io_base + SPDIF_IN_CTRL);
		ctrl |= SPDIF_IN_SAMPLE | SPDIF_IN_ENB;
		ग_लिखोl(ctrl, host->io_base + SPDIF_IN_CTRL);
		ग_लिखोl(0xF, host->io_base + SPDIF_IN_IRQ_MASK);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ctrl = पढ़ोl(host->io_base + SPDIF_IN_CTRL);
		ctrl &= ~(SPDIF_IN_SAMPLE | SPDIF_IN_ENB);
		ग_लिखोl(ctrl, host->io_base + SPDIF_IN_CTRL);
		ग_लिखोl(0x0, host->io_base + SPDIF_IN_IRQ_MASK);

		अगर (host->reset_perip)
			host->reset_perip();
		clk_disable(host->clk);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops spdअगर_in_dai_ops = अणु
	.shutकरोwn	= spdअगर_in_shutकरोwn,
	.trigger	= spdअगर_in_trigger,
	.hw_params	= spdअगर_in_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver spdअगर_in_dai = अणु
	.probe = spdअगर_in_dai_probe,
	.capture = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = (SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | \
				 SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000 | \
				 SNDRV_PCM_RATE_192000),
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | \
			   SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE,
	पूर्ण,
	.ops = &spdअगर_in_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver spdअगर_in_component = अणु
	.name		= "spdif-in",
पूर्ण;

अटल irqवापस_t spdअगर_in_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा spdअगर_in_dev *host = (काष्ठा spdअगर_in_dev *)arg;

	u32 irq_status = पढ़ोl(host->io_base + SPDIF_IN_IRQ);

	अगर (!irq_status)
		वापस IRQ_NONE;

	अगर (irq_status & SPDIF_IRQ_FIFOWRITE)
		dev_err(host->dev, "spdif in: fifo write error");
	अगर (irq_status & SPDIF_IRQ_EMPTYFIFOREAD)
		dev_err(host->dev, "spdif in: empty fifo read error");
	अगर (irq_status & SPDIF_IRQ_FIFOFULL)
		dev_err(host->dev, "spdif in: fifo full error");
	अगर (irq_status & SPDIF_IRQ_OUTOFRANGE)
		dev_err(host->dev, "spdif in: out of range error");

	ग_लिखोl(0, host->io_base + SPDIF_IN_IRQ);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक spdअगर_in_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spdअगर_in_dev *host;
	काष्ठा spear_spdअगर_platक्रमm_data *pdata;
	काष्ठा resource *res_fअगरo;
	व्योम __iomem *io_base;
	पूर्णांक ret;

	io_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(io_base))
		वापस PTR_ERR(io_base);

	res_fअगरo = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!res_fअगरo)
		वापस -EINVAL;

	host = devm_kzalloc(&pdev->dev, माप(*host), GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;

	host->io_base = io_base;
	host->irq = platक्रमm_get_irq(pdev, 0);
	अगर (host->irq < 0) अणु
		dev_warn(&pdev->dev, "failed to get IRQ: %d\n", host->irq);
		वापस host->irq;
	पूर्ण

	host->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(host->clk))
		वापस PTR_ERR(host->clk);

	pdata = dev_get_platdata(&pdev->dev);

	अगर (!pdata)
		वापस -EINVAL;

	host->dma_params.data = pdata->dma_params;
	host->dma_params.addr = res_fअगरo->start;
	host->dma_params.max_burst = 16;
	host->dma_params.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	host->reset_perip = pdata->reset_perip;

	host->dev = &pdev->dev;
	dev_set_drvdata(&pdev->dev, host);

	ret = devm_request_irq(&pdev->dev, host->irq, spdअगर_in_irq, 0,
			"spdif-in", host);
	अगर (ret) अणु
		dev_warn(&pdev->dev, "request_irq failed\n");
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &spdअगर_in_component,
					      &spdअगर_in_dai, 1);
	अगर (ret)
		वापस ret;

	वापस devm_spear_pcm_platक्रमm_रेजिस्टर(&pdev->dev, &host->config,
						pdata->filter);
पूर्ण

अटल काष्ठा platक्रमm_driver spdअगर_in_driver = अणु
	.probe		= spdअगर_in_probe,
	.driver		= अणु
		.name	= "spdif-in",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(spdअगर_in_driver);

MODULE_AUTHOR("Vipin Kumar <vipin.kumar@st.com>");
MODULE_DESCRIPTION("SPEAr SPDIF IN SoC Interface");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:spdif_in");
