<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ASoC driver क्रम Cirrus Logic EP93xx AC97 controller.
 *
 * Copyright (c) 2010 Mika Westerberg
 *
 * Based on s3c-ac97 ASoC driver by Jaswinder Singh.
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <sound/core.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/soc.h>

#समावेश <linux/platक्रमm_data/dma-ep93xx.h>
#समावेश <linux/soc/cirrus/ep93xx.h>

#समावेश "ep93xx-pcm.h"

/*
 * Per channel (1-4) रेजिस्टरs.
 */
#घोषणा AC97CH(n)		(((n) - 1) * 0x20)

#घोषणा AC97DR(n)		(AC97CH(n) + 0x0000)

#घोषणा AC97RXCR(n)		(AC97CH(n) + 0x0004)
#घोषणा AC97RXCR_REN		BIT(0)
#घोषणा AC97RXCR_RX3		BIT(3)
#घोषणा AC97RXCR_RX4		BIT(4)
#घोषणा AC97RXCR_CM		BIT(15)

#घोषणा AC97TXCR(n)		(AC97CH(n) + 0x0008)
#घोषणा AC97TXCR_TEN		BIT(0)
#घोषणा AC97TXCR_TX3		BIT(3)
#घोषणा AC97TXCR_TX4		BIT(4)
#घोषणा AC97TXCR_CM		BIT(15)

#घोषणा AC97SR(n)		(AC97CH(n) + 0x000c)
#घोषणा AC97SR_TXFE		BIT(1)
#घोषणा AC97SR_TXUE		BIT(6)

#घोषणा AC97RISR(n)		(AC97CH(n) + 0x0010)
#घोषणा AC97ISR(n)		(AC97CH(n) + 0x0014)
#घोषणा AC97IE(n)		(AC97CH(n) + 0x0018)

/*
 * Global AC97 controller रेजिस्टरs.
 */
#घोषणा AC97S1DATA		0x0080
#घोषणा AC97S2DATA		0x0084
#घोषणा AC97S12DATA		0x0088

#घोषणा AC97RGIS		0x008c
#घोषणा AC97GIS			0x0090
#घोषणा AC97IM			0x0094
/*
 * Common bits क्रम RGIS, GIS and IM रेजिस्टरs.
 */
#घोषणा AC97_SLOT2RXVALID	BIT(1)
#घोषणा AC97_CODECREADY		BIT(5)
#घोषणा AC97_SLOT2TXCOMPLETE	BIT(6)

#घोषणा AC97EOI			0x0098
#घोषणा AC97EOI_WINT		BIT(0)
#घोषणा AC97EOI_CODECREADY	BIT(1)

#घोषणा AC97GCR			0x009c
#घोषणा AC97GCR_AC97IFE		BIT(0)

#घोषणा AC97RESET		0x00a0
#घोषणा AC97RESET_TIMEDRESET	BIT(0)

#घोषणा AC97SYNC		0x00a4
#घोषणा AC97SYNC_TIMEDSYNC	BIT(0)

#घोषणा AC97_TIMEOUT		msecs_to_jअगरfies(5)

/**
 * काष्ठा ep93xx_ac97_info - EP93xx AC97 controller info काष्ठाure
 * @lock: mutex serializing access to the bus (slot 1 & 2 ops)
 * @dev: poपूर्णांकer to the platक्रमm device dev काष्ठाure
 * @regs: mapped AC97 controller रेजिस्टरs
 * @करोne: bus ops रुको here क्रम an पूर्णांकerrupt
 */
काष्ठा ep93xx_ac97_info अणु
	काष्ठा mutex		lock;
	काष्ठा device		*dev;
	व्योम __iomem		*regs;
	काष्ठा completion	करोne;
	काष्ठा snd_dmaengine_dai_dma_data dma_params_rx;
	काष्ठा snd_dmaengine_dai_dma_data dma_params_tx;
पूर्ण;

/* currently ALSA only supports a single AC97 device */
अटल काष्ठा ep93xx_ac97_info *ep93xx_ac97_info;

अटल काष्ठा ep93xx_dma_data ep93xx_ac97_pcm_out = अणु
	.name		= "ac97-pcm-out",
	.port		= EP93XX_DMA_AAC1,
	.direction	= DMA_MEM_TO_DEV,
पूर्ण;

अटल काष्ठा ep93xx_dma_data ep93xx_ac97_pcm_in = अणु
	.name		= "ac97-pcm-in",
	.port		= EP93XX_DMA_AAC1,
	.direction	= DMA_DEV_TO_MEM,
पूर्ण;

अटल अंतरभूत अचिन्हित ep93xx_ac97_पढ़ो_reg(काष्ठा ep93xx_ac97_info *info,
					    अचिन्हित reg)
अणु
	वापस __raw_पढ़ोl(info->regs + reg);
पूर्ण

अटल अंतरभूत व्योम ep93xx_ac97_ग_लिखो_reg(काष्ठा ep93xx_ac97_info *info,
					 अचिन्हित reg, अचिन्हित val)
अणु
	__raw_ग_लिखोl(val, info->regs + reg);
पूर्ण

अटल अचिन्हित लघु ep93xx_ac97_पढ़ो(काष्ठा snd_ac97 *ac97,
				       अचिन्हित लघु reg)
अणु
	काष्ठा ep93xx_ac97_info *info = ep93xx_ac97_info;
	अचिन्हित लघु val;

	mutex_lock(&info->lock);

	ep93xx_ac97_ग_लिखो_reg(info, AC97S1DATA, reg);
	ep93xx_ac97_ग_लिखो_reg(info, AC97IM, AC97_SLOT2RXVALID);
	अगर (!रुको_क्रम_completion_समयout(&info->करोne, AC97_TIMEOUT)) अणु
		dev_warn(info->dev, "timeout reading register %x\n", reg);
		mutex_unlock(&info->lock);
		वापस -ETIMEDOUT;
	पूर्ण
	val = (अचिन्हित लघु)ep93xx_ac97_पढ़ो_reg(info, AC97S2DATA);

	mutex_unlock(&info->lock);
	वापस val;
पूर्ण

अटल व्योम ep93xx_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97,
			      अचिन्हित लघु reg,
			      अचिन्हित लघु val)
अणु
	काष्ठा ep93xx_ac97_info *info = ep93xx_ac97_info;

	mutex_lock(&info->lock);

	/*
	 * Writes to the codec need to be करोne so that slot 2 is filled in
	 * beक्रमe slot 1.
	 */
	ep93xx_ac97_ग_लिखो_reg(info, AC97S2DATA, val);
	ep93xx_ac97_ग_लिखो_reg(info, AC97S1DATA, reg);

	ep93xx_ac97_ग_लिखो_reg(info, AC97IM, AC97_SLOT2TXCOMPLETE);
	अगर (!रुको_क्रम_completion_समयout(&info->करोne, AC97_TIMEOUT))
		dev_warn(info->dev, "timeout writing register %x\n", reg);

	mutex_unlock(&info->lock);
पूर्ण

अटल व्योम ep93xx_ac97_warm_reset(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा ep93xx_ac97_info *info = ep93xx_ac97_info;

	mutex_lock(&info->lock);

	/*
	 * We are assuming that beक्रमe this functions माला_लो called, the codec
	 * BIT_CLK is stopped by क्रमcing the codec पूर्णांकo घातerकरोwn mode. We can
	 * control the SYNC संकेत directly via AC97SYNC रेजिस्टर. Using
	 * TIMEDSYNC the controller will keep the SYNC high > 1us.
	 */
	ep93xx_ac97_ग_लिखो_reg(info, AC97SYNC, AC97SYNC_TIMEDSYNC);
	ep93xx_ac97_ग_लिखो_reg(info, AC97IM, AC97_CODECREADY);
	अगर (!रुको_क्रम_completion_समयout(&info->करोne, AC97_TIMEOUT))
		dev_warn(info->dev, "codec warm reset timeout\n");

	mutex_unlock(&info->lock);
पूर्ण

अटल व्योम ep93xx_ac97_cold_reset(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा ep93xx_ac97_info *info = ep93xx_ac97_info;

	mutex_lock(&info->lock);

	/*
	 * For करोing cold reset, we disable the AC97 controller पूर्णांकerface, clear
	 * WINT and CODECREADY bits, and finally enable the पूर्णांकerface again.
	 */
	ep93xx_ac97_ग_लिखो_reg(info, AC97GCR, 0);
	ep93xx_ac97_ग_लिखो_reg(info, AC97EOI, AC97EOI_CODECREADY | AC97EOI_WINT);
	ep93xx_ac97_ग_लिखो_reg(info, AC97GCR, AC97GCR_AC97IFE);

	/*
	 * Now, निश्चित the reset and रुको क्रम the codec to become पढ़ोy.
	 */
	ep93xx_ac97_ग_लिखो_reg(info, AC97RESET, AC97RESET_TIMEDRESET);
	ep93xx_ac97_ग_लिखो_reg(info, AC97IM, AC97_CODECREADY);
	अगर (!रुको_क्रम_completion_समयout(&info->करोne, AC97_TIMEOUT))
		dev_warn(info->dev, "codec cold reset timeout\n");

	/*
	 * Give the codec some समय to come fully out from the reset. This way
	 * we ensure that the subsequent पढ़ोs/ग_लिखोs will work.
	 */
	usleep_range(15000, 20000);

	mutex_unlock(&info->lock);
पूर्ण

अटल irqवापस_t ep93xx_ac97_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ep93xx_ac97_info *info = dev_id;
	अचिन्हित status, mask;

	/*
	 * Just mask out the पूर्णांकerrupt and wake up the रुकोing thपढ़ो.
	 * Interrupts are cleared via पढ़ोing/writing to slot 1 & 2 रेजिस्टरs by
	 * the रुकोing thपढ़ो.
	 */
	status = ep93xx_ac97_पढ़ो_reg(info, AC97GIS);
	mask = ep93xx_ac97_पढ़ो_reg(info, AC97IM);
	mask &= ~status;
	ep93xx_ac97_ग_लिखो_reg(info, AC97IM, mask);

	complete(&info->करोne);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा snd_ac97_bus_ops ep93xx_ac97_ops = अणु
	.पढ़ो		= ep93xx_ac97_पढ़ो,
	.ग_लिखो		= ep93xx_ac97_ग_लिखो,
	.reset		= ep93xx_ac97_cold_reset,
	.warm_reset	= ep93xx_ac97_warm_reset,
पूर्ण;

अटल पूर्णांक ep93xx_ac97_trigger(काष्ठा snd_pcm_substream *substream,
			       पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा ep93xx_ac97_info *info = snd_soc_dai_get_drvdata(dai);
	अचिन्हित v = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			/*
			 * Enable compact mode, TX slots 3 & 4, and the TX FIFO
			 * itself.
			 */
			v |= AC97TXCR_CM;
			v |= AC97TXCR_TX3 | AC97TXCR_TX4;
			v |= AC97TXCR_TEN;
			ep93xx_ac97_ग_लिखो_reg(info, AC97TXCR(1), v);
		पूर्ण अन्यथा अणु
			/*
			 * Enable compact mode, RX slots 3 & 4, and the RX FIFO
			 * itself.
			 */
			v |= AC97RXCR_CM;
			v |= AC97RXCR_RX3 | AC97RXCR_RX4;
			v |= AC97RXCR_REN;
			ep93xx_ac97_ग_लिखो_reg(info, AC97RXCR(1), v);
		पूर्ण
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			/*
			 * As per Cirrus EP93xx errata described below:
			 *
			 * https://www.cirrus.com/en/pubs/errata/ER667E2B.pdf
			 *
			 * we will रुको क्रम the TX FIFO to be empty beक्रमe
			 * clearing the TEN bit.
			 */
			अचिन्हित दीर्घ समयout = jअगरfies + AC97_TIMEOUT;

			करो अणु
				v = ep93xx_ac97_पढ़ो_reg(info, AC97SR(1));
				अगर (समय_after(jअगरfies, समयout)) अणु
					dev_warn(info->dev, "TX timeout\n");
					अवरोध;
				पूर्ण
			पूर्ण जबतक (!(v & (AC97SR_TXFE | AC97SR_TXUE)));

			/* disable the TX FIFO */
			ep93xx_ac97_ग_लिखो_reg(info, AC97TXCR(1), 0);
		पूर्ण अन्यथा अणु
			/* disable the RX FIFO */
			ep93xx_ac97_ग_लिखो_reg(info, AC97RXCR(1), 0);
		पूर्ण
		अवरोध;

	शेष:
		dev_warn(info->dev, "unknown command %d\n", cmd);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_ac97_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा ep93xx_ac97_info *info = snd_soc_dai_get_drvdata(dai);

	info->dma_params_tx.filter_data = &ep93xx_ac97_pcm_out;
	info->dma_params_rx.filter_data = &ep93xx_ac97_pcm_in;

	dai->playback_dma_data = &info->dma_params_tx;
	dai->capture_dma_data = &info->dma_params_rx;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops ep93xx_ac97_dai_ops = अणु
	.trigger	= ep93xx_ac97_trigger,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ep93xx_ac97_dai = अणु
	.name		= "ep93xx-ac97",
	.id		= 0,
	.probe		= ep93xx_ac97_dai_probe,
	.playback	= अणु
		.stream_name	= "AC97 Playback",
		.channels_min	= 2,
		.channels_max	= 2,
		.rates		= SNDRV_PCM_RATE_8000_48000,
		.क्रमmats	= SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture	= अणु
		.stream_name	= "AC97 Capture",
		.channels_min	= 2,
		.channels_max	= 2,
		.rates		= SNDRV_PCM_RATE_8000_48000,
		.क्रमmats	= SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.ops			= &ep93xx_ac97_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver ep93xx_ac97_component = अणु
	.name		= "ep93xx-ac97",
पूर्ण;

अटल पूर्णांक ep93xx_ac97_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ep93xx_ac97_info *info;
	पूर्णांक irq;
	पूर्णांक ret;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(info->regs))
		वापस PTR_ERR(info->regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस irq < 0 ? irq : -ENODEV;

	ret = devm_request_irq(&pdev->dev, irq, ep93xx_ac97_पूर्णांकerrupt,
			       IRQF_TRIGGER_HIGH, pdev->name, info);
	अगर (ret)
		जाओ fail;

	dev_set_drvdata(&pdev->dev, info);

	mutex_init(&info->lock);
	init_completion(&info->करोne);
	info->dev = &pdev->dev;

	ep93xx_ac97_info = info;
	platक्रमm_set_drvdata(pdev, info);

	ret = snd_soc_set_ac97_ops(&ep93xx_ac97_ops);
	अगर (ret)
		जाओ fail;

	ret = snd_soc_रेजिस्टर_component(&pdev->dev, &ep93xx_ac97_component,
					 &ep93xx_ac97_dai, 1);
	अगर (ret)
		जाओ fail;

	ret = devm_ep93xx_pcm_platक्रमm_रेजिस्टर(&pdev->dev);
	अगर (ret)
		जाओ fail_unरेजिस्टर;

	वापस 0;

fail_unरेजिस्टर:
	snd_soc_unरेजिस्टर_component(&pdev->dev);
fail:
	ep93xx_ac97_info = शून्य;
	snd_soc_set_ac97_ops(शून्य);
	वापस ret;
पूर्ण

अटल पूर्णांक ep93xx_ac97_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ep93xx_ac97_info	*info = platक्रमm_get_drvdata(pdev);

	snd_soc_unरेजिस्टर_component(&pdev->dev);

	/* disable the AC97 controller */
	ep93xx_ac97_ग_लिखो_reg(info, AC97GCR, 0);

	ep93xx_ac97_info = शून्य;

	snd_soc_set_ac97_ops(शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ep93xx_ac97_driver = अणु
	.probe	= ep93xx_ac97_probe,
	.हटाओ	= ep93xx_ac97_हटाओ,
	.driver = अणु
		.name = "ep93xx-ac97",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ep93xx_ac97_driver);

MODULE_DESCRIPTION("EP93xx AC97 ASoC Driver");
MODULE_AUTHOR("Mika Westerberg <mika.westerberg@iki.fi>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ep93xx-ac97");
