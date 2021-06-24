<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/sound/soc/ep93xx-i2s.c
 * EP93xx I2S driver
 *
 * Copyright (C) 2010 Ryan Mallon
 *
 * Based on the original driver by:
 *   Copyright (C) 2007 Chase Douglas <chaseकरोuglas@gmail>
 *   Copyright (C) 2006 Lennert Buytenhek <buytenh@wantstofly.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#समावेश <sound/core.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>

#समावेश <linux/platक्रमm_data/dma-ep93xx.h>
#समावेश <linux/soc/cirrus/ep93xx.h>

#समावेश "ep93xx-pcm.h"

#घोषणा EP93XX_I2S_TXCLKCFG		0x00
#घोषणा EP93XX_I2S_RXCLKCFG		0x04
#घोषणा EP93XX_I2S_GLSTS		0x08
#घोषणा EP93XX_I2S_GLCTRL		0x0C

#घोषणा EP93XX_I2S_I2STX0LFT		0x10
#घोषणा EP93XX_I2S_I2STX0RT		0x14

#घोषणा EP93XX_I2S_TXLINCTRLDATA	0x28
#घोषणा EP93XX_I2S_TXCTRL		0x2C
#घोषणा EP93XX_I2S_TXWRDLEN		0x30
#घोषणा EP93XX_I2S_TX0EN		0x34

#घोषणा EP93XX_I2S_RXLINCTRLDATA	0x58
#घोषणा EP93XX_I2S_RXCTRL		0x5C
#घोषणा EP93XX_I2S_RXWRDLEN		0x60
#घोषणा EP93XX_I2S_RX0EN		0x64

#घोषणा EP93XX_I2S_WRDLEN_16		(0 << 0)
#घोषणा EP93XX_I2S_WRDLEN_24		(1 << 0)
#घोषणा EP93XX_I2S_WRDLEN_32		(2 << 0)

#घोषणा EP93XX_I2S_RXLINCTRLDATA_R_JUST	BIT(1) /* Right justअगरy */

#घोषणा EP93XX_I2S_TXLINCTRLDATA_R_JUST	BIT(2) /* Right justअगरy */

/*
 * Transmit empty पूर्णांकerrupt level select:
 * 0 - Generate पूर्णांकerrupt when FIFO is half empty
 * 1 - Generate पूर्णांकerrupt when FIFO is empty
 */
#घोषणा EP93XX_I2S_TXCTRL_TXEMPTY_LVL	BIT(0)
#घोषणा EP93XX_I2S_TXCTRL_TXUFIE	BIT(1) /* Transmit पूर्णांकerrupt enable */

#घोषणा EP93XX_I2S_CLKCFG_LRS		(1 << 0) /* lrclk polarity */
#घोषणा EP93XX_I2S_CLKCFG_CKP		(1 << 1) /* Bit घड़ी polarity */
#घोषणा EP93XX_I2S_CLKCFG_REL		(1 << 2) /* First bit transition */
#घोषणा EP93XX_I2S_CLKCFG_MASTER	(1 << 3) /* Master mode */
#घोषणा EP93XX_I2S_CLKCFG_NBCG		(1 << 4) /* Not bit घड़ी gating */

#घोषणा EP93XX_I2S_GLSTS_TX0_FIFO_FULL	BIT(12)

काष्ठा ep93xx_i2s_info अणु
	काष्ठा clk			*mclk;
	काष्ठा clk			*sclk;
	काष्ठा clk			*lrclk;
	व्योम __iomem			*regs;
	काष्ठा snd_dmaengine_dai_dma_data dma_params_rx;
	काष्ठा snd_dmaengine_dai_dma_data dma_params_tx;
पूर्ण;

अटल काष्ठा ep93xx_dma_data ep93xx_i2s_dma_data[] = अणु
	[SNDRV_PCM_STREAM_PLAYBACK] = अणु
		.name		= "i2s-pcm-out",
		.port		= EP93XX_DMA_I2S1,
		.direction	= DMA_MEM_TO_DEV,
	पूर्ण,
	[SNDRV_PCM_STREAM_CAPTURE] = अणु
		.name		= "i2s-pcm-in",
		.port		= EP93XX_DMA_I2S1,
		.direction	= DMA_DEV_TO_MEM,
	पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम ep93xx_i2s_ग_लिखो_reg(काष्ठा ep93xx_i2s_info *info,
					अचिन्हित reg, अचिन्हित val)
अणु
	__raw_ग_लिखोl(val, info->regs + reg);
पूर्ण

अटल अंतरभूत अचिन्हित ep93xx_i2s_पढ़ो_reg(काष्ठा ep93xx_i2s_info *info,
					   अचिन्हित reg)
अणु
	वापस __raw_पढ़ोl(info->regs + reg);
पूर्ण

अटल व्योम ep93xx_i2s_enable(काष्ठा ep93xx_i2s_info *info, पूर्णांक stream)
अणु
	अचिन्हित base_reg;

	अगर ((ep93xx_i2s_पढ़ो_reg(info, EP93XX_I2S_TX0EN) & 0x1) == 0 &&
	    (ep93xx_i2s_पढ़ो_reg(info, EP93XX_I2S_RX0EN) & 0x1) == 0) अणु
		/* Enable घड़ीs */
		clk_enable(info->mclk);
		clk_enable(info->sclk);
		clk_enable(info->lrclk);

		/* Enable i2s */
		ep93xx_i2s_ग_लिखो_reg(info, EP93XX_I2S_GLCTRL, 1);
	पूर्ण

	/* Enable fअगरo */
	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK)
		base_reg = EP93XX_I2S_TX0EN;
	अन्यथा
		base_reg = EP93XX_I2S_RX0EN;
	ep93xx_i2s_ग_लिखो_reg(info, base_reg, 1);

	/* Enable TX IRQs (FIFO empty or underflow) */
	अगर (IS_ENABLED(CONFIG_SND_EP93XX_SOC_I2S_WATCHDOG) &&
	    stream == SNDRV_PCM_STREAM_PLAYBACK)
		ep93xx_i2s_ग_लिखो_reg(info, EP93XX_I2S_TXCTRL,
				     EP93XX_I2S_TXCTRL_TXEMPTY_LVL |
				     EP93XX_I2S_TXCTRL_TXUFIE);
पूर्ण

अटल व्योम ep93xx_i2s_disable(काष्ठा ep93xx_i2s_info *info, पूर्णांक stream)
अणु
	अचिन्हित base_reg;

	/* Disable IRQs */
	अगर (IS_ENABLED(CONFIG_SND_EP93XX_SOC_I2S_WATCHDOG) &&
	    stream == SNDRV_PCM_STREAM_PLAYBACK)
		ep93xx_i2s_ग_लिखो_reg(info, EP93XX_I2S_TXCTRL, 0);

	/* Disable fअगरo */
	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK)
		base_reg = EP93XX_I2S_TX0EN;
	अन्यथा
		base_reg = EP93XX_I2S_RX0EN;
	ep93xx_i2s_ग_लिखो_reg(info, base_reg, 0);

	अगर ((ep93xx_i2s_पढ़ो_reg(info, EP93XX_I2S_TX0EN) & 0x1) == 0 &&
	    (ep93xx_i2s_पढ़ो_reg(info, EP93XX_I2S_RX0EN) & 0x1) == 0) अणु
		/* Disable i2s */
		ep93xx_i2s_ग_लिखो_reg(info, EP93XX_I2S_GLCTRL, 0);

		/* Disable घड़ीs */
		clk_disable(info->lrclk);
		clk_disable(info->sclk);
		clk_disable(info->mclk);
	पूर्ण
पूर्ण

/*
 * According to करोcumentation I2S controller can handle underflow conditions
 * just fine, but in reality the state machine is someबार confused so that
 * the whole stream is shअगरted by one byte. The watchकरोg below disables the TX
 * FIFO, fills the buffer with zeroes and re-enables the FIFO. State machine
 * is being reset and by filling the buffer we get some समय beक्रमe next
 * underflow happens.
 */
अटल irqवापस_t ep93xx_i2s_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ep93xx_i2s_info *info = dev_id;

	/* Disable FIFO */
	ep93xx_i2s_ग_लिखो_reg(info, EP93XX_I2S_TX0EN, 0);
	/*
	 * Fill TX FIFO with zeroes, this way we can defer next IRQs as much as
	 * possible and get more समय क्रम DMA to catch up. Actually there are
	 * only 8 samples in this FIFO, so even on 8kHz maximum deferral here is
	 * 1ms.
	 */
	जबतक (!(ep93xx_i2s_पढ़ो_reg(info, EP93XX_I2S_GLSTS) &
		 EP93XX_I2S_GLSTS_TX0_FIFO_FULL)) अणु
		ep93xx_i2s_ग_लिखो_reg(info, EP93XX_I2S_I2STX0LFT, 0);
		ep93xx_i2s_ग_लिखो_reg(info, EP93XX_I2S_I2STX0RT, 0);
	पूर्ण
	/* Re-enable FIFO */
	ep93xx_i2s_ग_लिखो_reg(info, EP93XX_I2S_TX0EN, 1);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ep93xx_i2s_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा ep93xx_i2s_info *info = snd_soc_dai_get_drvdata(dai);

	info->dma_params_tx.filter_data =
		&ep93xx_i2s_dma_data[SNDRV_PCM_STREAM_PLAYBACK];
	info->dma_params_rx.filter_data =
		&ep93xx_i2s_dma_data[SNDRV_PCM_STREAM_CAPTURE];

	dai->playback_dma_data = &info->dma_params_tx;
	dai->capture_dma_data = &info->dma_params_rx;

	वापस 0;
पूर्ण

अटल व्योम ep93xx_i2s_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा ep93xx_i2s_info *info = snd_soc_dai_get_drvdata(dai);

	ep93xx_i2s_disable(info, substream->stream);
पूर्ण

अटल पूर्णांक ep93xx_i2s_set_dai_fmt(काष्ठा snd_soc_dai *cpu_dai,
				  अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा ep93xx_i2s_info *info = snd_soc_dai_get_drvdata(cpu_dai);
	अचिन्हित पूर्णांक clk_cfg;
	अचिन्हित पूर्णांक txlin_ctrl = 0;
	अचिन्हित पूर्णांक rxlin_ctrl = 0;

	clk_cfg  = ep93xx_i2s_पढ़ो_reg(info, EP93XX_I2S_RXCLKCFG);

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		clk_cfg |= EP93XX_I2S_CLKCFG_REL;
		अवरोध;

	हाल SND_SOC_DAIFMT_LEFT_J:
		clk_cfg &= ~EP93XX_I2S_CLKCFG_REL;
		अवरोध;

	हाल SND_SOC_DAIFMT_RIGHT_J:
		clk_cfg &= ~EP93XX_I2S_CLKCFG_REL;
		rxlin_ctrl |= EP93XX_I2S_RXLINCTRLDATA_R_JUST;
		txlin_ctrl |= EP93XX_I2S_TXLINCTRLDATA_R_JUST;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/* CPU is master */
		clk_cfg |= EP93XX_I2S_CLKCFG_MASTER;
		अवरोध;

	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* Codec is master */
		clk_cfg &= ~EP93XX_I2S_CLKCFG_MASTER;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		/* Negative bit घड़ी, lrclk low on left word */
		clk_cfg &= ~(EP93XX_I2S_CLKCFG_CKP | EP93XX_I2S_CLKCFG_LRS);
		अवरोध;

	हाल SND_SOC_DAIFMT_NB_IF:
		/* Negative bit घड़ी, lrclk low on right word */
		clk_cfg &= ~EP93XX_I2S_CLKCFG_CKP;
		clk_cfg |= EP93XX_I2S_CLKCFG_LRS;
		अवरोध;

	हाल SND_SOC_DAIFMT_IB_NF:
		/* Positive bit घड़ी, lrclk low on left word */
		clk_cfg |= EP93XX_I2S_CLKCFG_CKP;
		clk_cfg &= ~EP93XX_I2S_CLKCFG_LRS;
		अवरोध;

	हाल SND_SOC_DAIFMT_IB_IF:
		/* Positive bit घड़ी, lrclk low on right word */
		clk_cfg |= EP93XX_I2S_CLKCFG_CKP | EP93XX_I2S_CLKCFG_LRS;
		अवरोध;
	पूर्ण

	/* Write new रेजिस्टर values */
	ep93xx_i2s_ग_लिखो_reg(info, EP93XX_I2S_RXCLKCFG, clk_cfg);
	ep93xx_i2s_ग_लिखो_reg(info, EP93XX_I2S_TXCLKCFG, clk_cfg);
	ep93xx_i2s_ग_लिखो_reg(info, EP93XX_I2S_RXLINCTRLDATA, rxlin_ctrl);
	ep93xx_i2s_ग_लिखो_reg(info, EP93XX_I2S_TXLINCTRLDATA, txlin_ctrl);
	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा ep93xx_i2s_info *info = snd_soc_dai_get_drvdata(dai);
	अचिन्हित word_len, भाग, sभाग, lrभाग;
	पूर्णांक err;

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		word_len = EP93XX_I2S_WRDLEN_16;
		अवरोध;

	हाल SNDRV_PCM_FORMAT_S24_LE:
		word_len = EP93XX_I2S_WRDLEN_24;
		अवरोध;

	हाल SNDRV_PCM_FORMAT_S32_LE:
		word_len = EP93XX_I2S_WRDLEN_32;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		ep93xx_i2s_ग_लिखो_reg(info, EP93XX_I2S_TXWRDLEN, word_len);
	अन्यथा
		ep93xx_i2s_ग_लिखो_reg(info, EP93XX_I2S_RXWRDLEN, word_len);

	/*
	 * EP93xx I2S module can be setup so SCLK / LRCLK value can be
	 * 32, 64, 128. MCLK / SCLK value can be 2 and 4.
	 * We set LRCLK equal to `rate' and minimum SCLK / LRCLK 
	 * value is 64, because our sample size is 32 bit * 2 channels.
	 * I2S standard permits us to transmit more bits than
	 * the codec uses.
	 */
	भाग = clk_get_rate(info->mclk) / params_rate(params);
	sभाग = 4;
	अगर (भाग > (256 + 512) / 2) अणु
		lrभाग = 128;
	पूर्ण अन्यथा अणु
		lrभाग = 64;
		अगर (भाग < (128 + 256) / 2)
			sभाग = 2;
	पूर्ण

	err = clk_set_rate(info->sclk, clk_get_rate(info->mclk) / sभाग);
	अगर (err)
		वापस err;

	err = clk_set_rate(info->lrclk, clk_get_rate(info->sclk) / lrभाग);
	अगर (err)
		वापस err;

	ep93xx_i2s_enable(info, substream->stream);
	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_i2s_set_sysclk(काष्ठा snd_soc_dai *cpu_dai, पूर्णांक clk_id,
				 अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा ep93xx_i2s_info *info = snd_soc_dai_get_drvdata(cpu_dai);

	अगर (dir == SND_SOC_CLOCK_IN || clk_id != 0)
		वापस -EINVAL;

	वापस clk_set_rate(info->mclk, freq);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ep93xx_i2s_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ep93xx_i2s_info *info = snd_soc_component_get_drvdata(component);

	अगर (!snd_soc_component_active(component))
		वापस 0;

	ep93xx_i2s_disable(info, SNDRV_PCM_STREAM_PLAYBACK);
	ep93xx_i2s_disable(info, SNDRV_PCM_STREAM_CAPTURE);

	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_i2s_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ep93xx_i2s_info *info = snd_soc_component_get_drvdata(component);

	अगर (!snd_soc_component_active(component))
		वापस 0;

	ep93xx_i2s_enable(info, SNDRV_PCM_STREAM_PLAYBACK);
	ep93xx_i2s_enable(info, SNDRV_PCM_STREAM_CAPTURE);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ep93xx_i2s_suspend	शून्य
#घोषणा ep93xx_i2s_resume	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_soc_dai_ops ep93xx_i2s_dai_ops = अणु
	.shutकरोwn	= ep93xx_i2s_shutकरोwn,
	.hw_params	= ep93xx_i2s_hw_params,
	.set_sysclk	= ep93xx_i2s_set_sysclk,
	.set_fmt	= ep93xx_i2s_set_dai_fmt,
पूर्ण;

#घोषणा EP93XX_I2S_FORMATS (SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver ep93xx_i2s_dai = अणु
	.symmetric_rate	= 1,
	.probe		= ep93xx_i2s_dai_probe,
	.playback	= अणु
		.channels_min	= 2,
		.channels_max	= 2,
		.rates		= SNDRV_PCM_RATE_8000_192000,
		.क्रमmats	= EP93XX_I2S_FORMATS,
	पूर्ण,
	.capture	= अणु
		 .channels_min	= 2,
		 .channels_max	= 2,
		 .rates		= SNDRV_PCM_RATE_8000_192000,
		 .क्रमmats	= EP93XX_I2S_FORMATS,
	पूर्ण,
	.ops		= &ep93xx_i2s_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver ep93xx_i2s_component = अणु
	.name		= "ep93xx-i2s",
	.suspend	= ep93xx_i2s_suspend,
	.resume		= ep93xx_i2s_resume,
पूर्ण;

अटल पूर्णांक ep93xx_i2s_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ep93xx_i2s_info *info;
	पूर्णांक err;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(info->regs))
		वापस PTR_ERR(info->regs);

	अगर (IS_ENABLED(CONFIG_SND_EP93XX_SOC_I2S_WATCHDOG)) अणु
		पूर्णांक irq = platक्रमm_get_irq(pdev, 0);
		अगर (irq <= 0)
			वापस irq < 0 ? irq : -ENODEV;

		err = devm_request_irq(&pdev->dev, irq, ep93xx_i2s_पूर्णांकerrupt, 0,
				       pdev->name, info);
		अगर (err)
			वापस err;
	पूर्ण

	info->mclk = clk_get(&pdev->dev, "mclk");
	अगर (IS_ERR(info->mclk)) अणु
		err = PTR_ERR(info->mclk);
		जाओ fail;
	पूर्ण

	info->sclk = clk_get(&pdev->dev, "sclk");
	अगर (IS_ERR(info->sclk)) अणु
		err = PTR_ERR(info->sclk);
		जाओ fail_put_mclk;
	पूर्ण

	info->lrclk = clk_get(&pdev->dev, "lrclk");
	अगर (IS_ERR(info->lrclk)) अणु
		err = PTR_ERR(info->lrclk);
		जाओ fail_put_sclk;
	पूर्ण

	dev_set_drvdata(&pdev->dev, info);

	err = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &ep93xx_i2s_component,
					 &ep93xx_i2s_dai, 1);
	अगर (err)
		जाओ fail_put_lrclk;

	err = devm_ep93xx_pcm_platक्रमm_रेजिस्टर(&pdev->dev);
	अगर (err)
		जाओ fail_put_lrclk;

	वापस 0;

fail_put_lrclk:
	clk_put(info->lrclk);
fail_put_sclk:
	clk_put(info->sclk);
fail_put_mclk:
	clk_put(info->mclk);
fail:
	वापस err;
पूर्ण

अटल पूर्णांक ep93xx_i2s_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ep93xx_i2s_info *info = dev_get_drvdata(&pdev->dev);

	clk_put(info->lrclk);
	clk_put(info->sclk);
	clk_put(info->mclk);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ep93xx_i2s_driver = अणु
	.probe	= ep93xx_i2s_probe,
	.हटाओ	= ep93xx_i2s_हटाओ,
	.driver	= अणु
		.name	= "ep93xx-i2s",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ep93xx_i2s_driver);

MODULE_ALIAS("platform:ep93xx-i2s");
MODULE_AUTHOR("Ryan Mallon");
MODULE_DESCRIPTION("EP93XX I2S driver");
MODULE_LICENSE("GPL");
