<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
//
// Copyright (c) 2018 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/clk.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश "axg-fifo.h"

/*
 * This file implements the platक्रमm operations common to the playback and
 * capture frontend DAI. The logic behind this two types of fअगरo is very
 * similar but some dअगरference exist.
 * These dअगरferences are handled in the respective DAI drivers
 */

अटल काष्ठा snd_pcm_hardware axg_fअगरo_hw = अणु
	.info = (SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_MMAP |
		 SNDRV_PCM_INFO_MMAP_VALID |
		 SNDRV_PCM_INFO_BLOCK_TRANSFER |
		 SNDRV_PCM_INFO_PAUSE |
		 SNDRV_PCM_INFO_NO_PERIOD_WAKEUP),
	.क्रमmats = AXG_FIFO_FORMATS,
	.rate_min = 5512,
	.rate_max = 192000,
	.channels_min = 1,
	.channels_max = AXG_FIFO_CH_MAX,
	.period_bytes_min = AXG_FIFO_BURST,
	.period_bytes_max = अच_पूर्णांक_उच्च,
	.periods_min = 2,
	.periods_max = अच_पूर्णांक_उच्च,

	/* No real justअगरication क्रम this */
	.buffer_bytes_max = 1 * 1024 * 1024,
पूर्ण;

अटल काष्ठा snd_soc_dai *axg_fअगरo_dai(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = ss->निजी_data;

	वापस asoc_rtd_to_cpu(rtd, 0);
पूर्ण

अटल काष्ठा axg_fअगरo *axg_fअगरo_data(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा snd_soc_dai *dai = axg_fअगरo_dai(ss);

	वापस snd_soc_dai_get_drvdata(dai);
पूर्ण

अटल काष्ठा device *axg_fअगरo_dev(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा snd_soc_dai *dai = axg_fअगरo_dai(ss);

	वापस dai->dev;
पूर्ण

अटल व्योम __dma_enable(काष्ठा axg_fअगरo *fअगरo,  bool enable)
अणु
	regmap_update_bits(fअगरo->map, FIFO_CTRL0, CTRL0_DMA_EN,
			   enable ? CTRL0_DMA_EN : 0);
पूर्ण

पूर्णांक axg_fअगरo_pcm_trigger(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *ss, पूर्णांक cmd)
अणु
	काष्ठा axg_fअगरo *fअगरo = axg_fअगरo_data(ss);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		__dma_enable(fअगरo, true);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_STOP:
		__dma_enable(fअगरo, false);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(axg_fअगरo_pcm_trigger);

snd_pcm_uframes_t axg_fअगरo_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
				       काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा axg_fअगरo *fअगरo = axg_fअगरo_data(ss);
	काष्ठा snd_pcm_runसमय *runसमय = ss->runसमय;
	अचिन्हित पूर्णांक addr;

	regmap_पढ़ो(fअगरo->map, FIFO_STATUS2, &addr);

	वापस bytes_to_frames(runसमय, addr - (अचिन्हित पूर्णांक)runसमय->dma_addr);
पूर्ण
EXPORT_SYMBOL_GPL(axg_fअगरo_pcm_poपूर्णांकer);

पूर्णांक axg_fअगरo_pcm_hw_params(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *ss,
			   काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = ss->runसमय;
	काष्ठा axg_fअगरo *fअगरo = axg_fअगरo_data(ss);
	अचिन्हित पूर्णांक burst_num, period, threshold, irq_en;
	dma_addr_t end_ptr;

	period = params_period_bytes(params);

	/* Setup dma memory poपूर्णांकers */
	end_ptr = runसमय->dma_addr + runसमय->dma_bytes - AXG_FIFO_BURST;
	regmap_ग_लिखो(fअगरo->map, FIFO_START_ADDR, runसमय->dma_addr);
	regmap_ग_लिखो(fअगरo->map, FIFO_FINISH_ADDR, end_ptr);

	/* Setup पूर्णांकerrupt periodicity */
	burst_num = period / AXG_FIFO_BURST;
	regmap_ग_लिखो(fअगरo->map, FIFO_INT_ADDR, burst_num);

	/*
	 * Start the fअगरo request on the smallest of the following:
	 * - Half the fअगरo size
	 * - Half the period size
	 */
	threshold = min(period / 2, fअगरo->depth / 2);

	/*
	 * With the threshold in bytes, रेजिस्टर value is:
	 * V = (threshold / burst) - 1
	 */
	threshold /= AXG_FIFO_BURST;
	regmap_field_ग_लिखो(fअगरo->field_threshold,
			   threshold ? threshold - 1 : 0);

	/* Enable irq अगर necessary  */
	irq_en = runसमय->no_period_wakeup ? 0 : FIFO_INT_COUNT_REPEAT;
	regmap_update_bits(fअगरo->map, FIFO_CTRL0,
			   CTRL0_INT_EN(FIFO_INT_COUNT_REPEAT),
			   CTRL0_INT_EN(irq_en));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(axg_fअगरo_pcm_hw_params);

पूर्णांक g12a_fअगरo_pcm_hw_params(काष्ठा snd_soc_component *component,
			    काष्ठा snd_pcm_substream *ss,
			    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा axg_fअगरo *fअगरo = axg_fअगरo_data(ss);
	काष्ठा snd_pcm_runसमय *runसमय = ss->runसमय;
	पूर्णांक ret;

	ret = axg_fअगरo_pcm_hw_params(component, ss, params);
	अगर (ret)
		वापस ret;

	/* Set the initial memory address of the DMA */
	regmap_ग_लिखो(fअगरo->map, FIFO_INIT_ADDR, runसमय->dma_addr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(g12a_fअगरo_pcm_hw_params);

पूर्णांक axg_fअगरo_pcm_hw_मुक्त(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा axg_fअगरo *fअगरo = axg_fअगरo_data(ss);

	/* Disable the block count irq */
	regmap_update_bits(fअगरo->map, FIFO_CTRL0,
			   CTRL0_INT_EN(FIFO_INT_COUNT_REPEAT), 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(axg_fअगरo_pcm_hw_मुक्त);

अटल व्योम axg_fअगरo_ack_irq(काष्ठा axg_fअगरo *fअगरo, u8 mask)
अणु
	regmap_update_bits(fअगरo->map, FIFO_CTRL1,
			   CTRL1_INT_CLR(FIFO_INT_MASK),
			   CTRL1_INT_CLR(mask));

	/* Clear must also be cleared */
	regmap_update_bits(fअगरo->map, FIFO_CTRL1,
			   CTRL1_INT_CLR(FIFO_INT_MASK),
			   0);
पूर्ण

अटल irqवापस_t axg_fअगरo_pcm_irq_block(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_pcm_substream *ss = dev_id;
	काष्ठा axg_fअगरo *fअगरo = axg_fअगरo_data(ss);
	अचिन्हित पूर्णांक status;

	regmap_पढ़ो(fअगरo->map, FIFO_STATUS1, &status);

	status = STATUS1_INT_STS(status) & FIFO_INT_MASK;
	अगर (status & FIFO_INT_COUNT_REPEAT)
		snd_pcm_period_elapsed(ss);
	अन्यथा
		dev_dbg(axg_fअगरo_dev(ss), "unexpected irq - STS 0x%02x\n",
			status);

	/* Ack irqs */
	axg_fअगरo_ack_irq(fअगरo, status);

	वापस IRQ_RETVAL(status);
पूर्ण

पूर्णांक axg_fअगरo_pcm_खोलो(काष्ठा snd_soc_component *component,
		      काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा axg_fअगरo *fअगरo = axg_fअगरo_data(ss);
	काष्ठा device *dev = axg_fअगरo_dev(ss);
	पूर्णांक ret;

	snd_soc_set_runसमय_hwparams(ss, &axg_fअगरo_hw);

	/*
	 * Make sure the buffer and period size are multiple of the FIFO
	 * burst
	 */
	ret = snd_pcm_hw_स्थिरraपूर्णांक_step(ss->runसमय, 0,
					 SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
					 AXG_FIFO_BURST);
	अगर (ret)
		वापस ret;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_step(ss->runसमय, 0,
					 SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
					 AXG_FIFO_BURST);
	अगर (ret)
		वापस ret;

	ret = request_irq(fअगरo->irq, axg_fअगरo_pcm_irq_block, 0,
			  dev_name(dev), ss);
	अगर (ret)
		वापस ret;

	/* Enable pclk to access रेजिस्टरs and घड़ी the fअगरo ip */
	ret = clk_prepare_enable(fअगरo->pclk);
	अगर (ret)
		जाओ मुक्त_irq;

	/* Setup status2 so it reports the memory poपूर्णांकer */
	regmap_update_bits(fअगरo->map, FIFO_CTRL1,
			   CTRL1_STATUS2_SEL_MASK,
			   CTRL1_STATUS2_SEL(STATUS2_SEL_DDR_READ));

	/* Make sure the dma is initially disabled */
	__dma_enable(fअगरo, false);

	/* Disable irqs until params are पढ़ोy */
	regmap_update_bits(fअगरo->map, FIFO_CTRL0,
			   CTRL0_INT_EN(FIFO_INT_MASK), 0);

	/* Clear any pending पूर्णांकerrupt */
	axg_fअगरo_ack_irq(fअगरo, FIFO_INT_MASK);

	/* Take memory arbitror out of reset */
	ret = reset_control_deनिश्चित(fअगरo->arb);
	अगर (ret)
		जाओ मुक्त_clk;

	वापस 0;

मुक्त_clk:
	clk_disable_unprepare(fअगरo->pclk);
मुक्त_irq:
	मुक्त_irq(fअगरo->irq, ss);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(axg_fअगरo_pcm_खोलो);

पूर्णांक axg_fअगरo_pcm_बंद(काष्ठा snd_soc_component *component,
		       काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा axg_fअगरo *fअगरo = axg_fअगरo_data(ss);
	पूर्णांक ret;

	/* Put the memory arbitror back in reset */
	ret = reset_control_निश्चित(fअगरo->arb);

	/* Disable fअगरo ip and रेजिस्टर access */
	clk_disable_unprepare(fअगरo->pclk);

	/* हटाओ IRQ */
	मुक्त_irq(fअगरo->irq, ss);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(axg_fअगरo_pcm_बंद);

पूर्णांक axg_fअगरo_pcm_new(काष्ठा snd_soc_pcm_runसमय *rtd, अचिन्हित पूर्णांक type)
अणु
	काष्ठा snd_card *card = rtd->card->snd_card;
	माप_प्रकार size = axg_fअगरo_hw.buffer_bytes_max;

	snd_pcm_set_managed_buffer(rtd->pcm->streams[type].substream,
				   SNDRV_DMA_TYPE_DEV, card->dev,
				   size, size);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(axg_fअगरo_pcm_new);

अटल स्थिर काष्ठा regmap_config axg_fअगरo_regmap_cfg = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= FIFO_CTRL2,
पूर्ण;

पूर्णांक axg_fअगरo_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा axg_fअगरo_match_data *data;
	काष्ठा axg_fअगरo *fअगरo;
	व्योम __iomem *regs;
	पूर्णांक ret;

	data = of_device_get_match_data(dev);
	अगर (!data) अणु
		dev_err(dev, "failed to match device\n");
		वापस -ENODEV;
	पूर्ण

	fअगरo = devm_kzalloc(dev, माप(*fअगरo), GFP_KERNEL);
	अगर (!fअगरo)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, fअगरo);

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	fअगरo->map = devm_regmap_init_mmio(dev, regs, &axg_fअगरo_regmap_cfg);
	अगर (IS_ERR(fअगरo->map)) अणु
		dev_err(dev, "failed to init regmap: %ld\n",
			PTR_ERR(fअगरo->map));
		वापस PTR_ERR(fअगरo->map);
	पूर्ण

	fअगरo->pclk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(fअगरo->pclk)) अणु
		अगर (PTR_ERR(fअगरo->pclk) != -EPROBE_DEFER)
			dev_err(dev, "failed to get pclk: %ld\n",
				PTR_ERR(fअगरo->pclk));
		वापस PTR_ERR(fअगरo->pclk);
	पूर्ण

	fअगरo->arb = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(fअगरo->arb)) अणु
		अगर (PTR_ERR(fअगरo->arb) != -EPROBE_DEFER)
			dev_err(dev, "failed to get arb reset: %ld\n",
				PTR_ERR(fअगरo->arb));
		वापस PTR_ERR(fअगरo->arb);
	पूर्ण

	fअगरo->irq = of_irq_get(dev->of_node, 0);
	अगर (fअगरo->irq <= 0) अणु
		dev_err(dev, "failed to get irq: %d\n", fअगरo->irq);
		वापस fअगरo->irq;
	पूर्ण

	fअगरo->field_threshold =
		devm_regmap_field_alloc(dev, fअगरo->map, data->field_threshold);
	अगर (IS_ERR(fअगरo->field_threshold))
		वापस PTR_ERR(fअगरo->field_threshold);

	ret = of_property_पढ़ो_u32(dev->of_node, "amlogic,fifo-depth",
				   &fअगरo->depth);
	अगर (ret) अणु
		/* Error out क्रम anything but a missing property */
		अगर (ret != -EINVAL)
			वापस ret;
		/*
		 * If the property is missing, it might be because of an old
		 * DT. In such हाल, assume the smallest known fअगरo depth
		 */
		fअगरo->depth = 256;
		dev_warn(dev, "fifo depth not found, assume %u bytes\n",
			 fअगरo->depth);
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(dev, data->component_drv,
					       data->dai_drv, 1);
पूर्ण
EXPORT_SYMBOL_GPL(axg_fअगरo_probe);

MODULE_DESCRIPTION("Amlogic AXG/G12A fifo driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
