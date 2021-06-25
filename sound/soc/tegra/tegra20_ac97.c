<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tegra20_ac97.c - Tegra20 AC97 platक्रमm driver
 *
 * Copyright (c) 2012 Lucas Stach <dev@lynxeye.de>
 *
 * Partly based on code copyright/by:
 *
 * Copyright (c) 2011,2012 Toradex Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "tegra20_ac97.h"

#घोषणा DRV_NAME "tegra20-ac97"

अटल काष्ठा tegra20_ac97 *workdata;

अटल व्योम tegra20_ac97_codec_reset(काष्ठा snd_ac97 *ac97)
अणु
	u32 पढ़ोback;
	अचिन्हित दीर्घ समयout;

	/* reset line is not driven by DAC pad group, have to toggle GPIO */
	gpio_set_value(workdata->reset_gpio, 0);
	udelay(2);

	gpio_set_value(workdata->reset_gpio, 1);
	udelay(2);

	समयout = jअगरfies + msecs_to_jअगरfies(100);

	करो अणु
		regmap_पढ़ो(workdata->regmap, TEGRA20_AC97_STATUS1, &पढ़ोback);
		अगर (पढ़ोback & TEGRA20_AC97_STATUS1_CODEC1_RDY)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण जबतक (!समय_after(jअगरfies, समयout));
पूर्ण

अटल व्योम tegra20_ac97_codec_warm_reset(काष्ठा snd_ac97 *ac97)
अणु
	u32 पढ़ोback;
	अचिन्हित दीर्घ समयout;

	/*
	 * although sync line is driven by the DAC pad group warm reset using
	 * the controller cmd is not working, have to toggle sync line
	 * manually.
	 */
	gpio_request(workdata->sync_gpio, "codec-sync");

	gpio_direction_output(workdata->sync_gpio, 1);

	udelay(2);
	gpio_set_value(workdata->sync_gpio, 0);
	udelay(2);
	gpio_मुक्त(workdata->sync_gpio);

	समयout = jअगरfies + msecs_to_jअगरfies(100);

	करो अणु
		regmap_पढ़ो(workdata->regmap, TEGRA20_AC97_STATUS1, &पढ़ोback);
		अगर (पढ़ोback & TEGRA20_AC97_STATUS1_CODEC1_RDY)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण जबतक (!समय_after(jअगरfies, समयout));
पूर्ण

अटल अचिन्हित लघु tegra20_ac97_codec_पढ़ो(काष्ठा snd_ac97 *ac97_snd,
					      अचिन्हित लघु reg)
अणु
	u32 पढ़ोback;
	अचिन्हित दीर्घ समयout;

	regmap_ग_लिखो(workdata->regmap, TEGRA20_AC97_CMD,
		     (((reg | 0x80) << TEGRA20_AC97_CMD_CMD_ADDR_SHIFT) &
		      TEGRA20_AC97_CMD_CMD_ADDR_MASK) |
		     TEGRA20_AC97_CMD_BUSY);

	समयout = jअगरfies + msecs_to_jअगरfies(100);

	करो अणु
		regmap_पढ़ो(workdata->regmap, TEGRA20_AC97_STATUS1, &पढ़ोback);
		अगर (पढ़ोback & TEGRA20_AC97_STATUS1_STA_VALID1)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण जबतक (!समय_after(jअगरfies, समयout));

	वापस ((पढ़ोback & TEGRA20_AC97_STATUS1_STA_DATA1_MASK) >>
		TEGRA20_AC97_STATUS1_STA_DATA1_SHIFT);
पूर्ण

अटल व्योम tegra20_ac97_codec_ग_लिखो(काष्ठा snd_ac97 *ac97_snd,
				     अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	u32 पढ़ोback;
	अचिन्हित दीर्घ समयout;

	regmap_ग_लिखो(workdata->regmap, TEGRA20_AC97_CMD,
		     ((reg << TEGRA20_AC97_CMD_CMD_ADDR_SHIFT) &
		      TEGRA20_AC97_CMD_CMD_ADDR_MASK) |
		     ((val << TEGRA20_AC97_CMD_CMD_DATA_SHIFT) &
		      TEGRA20_AC97_CMD_CMD_DATA_MASK) |
		     TEGRA20_AC97_CMD_BUSY);

	समयout = jअगरfies + msecs_to_jअगरfies(100);

	करो अणु
		regmap_पढ़ो(workdata->regmap, TEGRA20_AC97_CMD, &पढ़ोback);
		अगर (!(पढ़ोback & TEGRA20_AC97_CMD_BUSY))
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण जबतक (!समय_after(jअगरfies, समयout));
पूर्ण

अटल काष्ठा snd_ac97_bus_ops tegra20_ac97_ops = अणु
	.पढ़ो		= tegra20_ac97_codec_पढ़ो,
	.ग_लिखो		= tegra20_ac97_codec_ग_लिखो,
	.reset		= tegra20_ac97_codec_reset,
	.warm_reset	= tegra20_ac97_codec_warm_reset,
पूर्ण;

अटल अंतरभूत व्योम tegra20_ac97_start_playback(काष्ठा tegra20_ac97 *ac97)
अणु
	regmap_update_bits(ac97->regmap, TEGRA20_AC97_FIFO1_SCR,
			   TEGRA20_AC97_FIFO_SCR_PB_QRT_MT_EN,
			   TEGRA20_AC97_FIFO_SCR_PB_QRT_MT_EN);

	regmap_update_bits(ac97->regmap, TEGRA20_AC97_CTRL,
			   TEGRA20_AC97_CTRL_PCM_DAC_EN |
			   TEGRA20_AC97_CTRL_STM_EN,
			   TEGRA20_AC97_CTRL_PCM_DAC_EN |
			   TEGRA20_AC97_CTRL_STM_EN);
पूर्ण

अटल अंतरभूत व्योम tegra20_ac97_stop_playback(काष्ठा tegra20_ac97 *ac97)
अणु
	regmap_update_bits(ac97->regmap, TEGRA20_AC97_FIFO1_SCR,
			   TEGRA20_AC97_FIFO_SCR_PB_QRT_MT_EN, 0);

	regmap_update_bits(ac97->regmap, TEGRA20_AC97_CTRL,
			   TEGRA20_AC97_CTRL_PCM_DAC_EN, 0);
पूर्ण

अटल अंतरभूत व्योम tegra20_ac97_start_capture(काष्ठा tegra20_ac97 *ac97)
अणु
	regmap_update_bits(ac97->regmap, TEGRA20_AC97_FIFO1_SCR,
			   TEGRA20_AC97_FIFO_SCR_REC_FULL_EN,
			   TEGRA20_AC97_FIFO_SCR_REC_FULL_EN);
पूर्ण

अटल अंतरभूत व्योम tegra20_ac97_stop_capture(काष्ठा tegra20_ac97 *ac97)
अणु
	regmap_update_bits(ac97->regmap, TEGRA20_AC97_FIFO1_SCR,
			   TEGRA20_AC97_FIFO_SCR_REC_FULL_EN, 0);
पूर्ण

अटल पूर्णांक tegra20_ac97_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा tegra20_ac97 *ac97 = snd_soc_dai_get_drvdata(dai);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			tegra20_ac97_start_playback(ac97);
		अन्यथा
			tegra20_ac97_start_capture(ac97);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			tegra20_ac97_stop_playback(ac97);
		अन्यथा
			tegra20_ac97_stop_capture(ac97);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops tegra20_ac97_dai_ops = अणु
	.trigger	= tegra20_ac97_trigger,
पूर्ण;

अटल पूर्णांक tegra20_ac97_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा tegra20_ac97 *ac97 = snd_soc_dai_get_drvdata(dai);

	dai->capture_dma_data = &ac97->capture_dma_data;
	dai->playback_dma_data = &ac97->playback_dma_data;

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver tegra20_ac97_dai = अणु
	.name = "tegra-ac97-pcm",
	.probe = tegra20_ac97_probe,
	.playback = अणु
		.stream_name = "PCM Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "PCM Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.ops = &tegra20_ac97_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver tegra20_ac97_component = अणु
	.name		= DRV_NAME,
पूर्ण;

अटल bool tegra20_ac97_wr_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA20_AC97_CTRL:
	हाल TEGRA20_AC97_CMD:
	हाल TEGRA20_AC97_STATUS1:
	हाल TEGRA20_AC97_FIFO1_SCR:
	हाल TEGRA20_AC97_FIFO_TX1:
	हाल TEGRA20_AC97_FIFO_RX1:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल bool tegra20_ac97_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA20_AC97_STATUS1:
	हाल TEGRA20_AC97_FIFO1_SCR:
	हाल TEGRA20_AC97_FIFO_TX1:
	हाल TEGRA20_AC97_FIFO_RX1:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल bool tegra20_ac97_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA20_AC97_FIFO_TX1:
	हाल TEGRA20_AC97_FIFO_RX1:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config tegra20_ac97_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = TEGRA20_AC97_FIFO_RX1,
	.ग_लिखोable_reg = tegra20_ac97_wr_rd_reg,
	.पढ़ोable_reg = tegra20_ac97_wr_rd_reg,
	.अस्थिर_reg = tegra20_ac97_अस्थिर_reg,
	.precious_reg = tegra20_ac97_precious_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक tegra20_ac97_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra20_ac97 *ac97;
	काष्ठा resource *mem;
	व्योम __iomem *regs;
	पूर्णांक ret = 0;

	ac97 = devm_kzalloc(&pdev->dev, माप(काष्ठा tegra20_ac97),
			    GFP_KERNEL);
	अगर (!ac97) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	dev_set_drvdata(&pdev->dev, ac97);

	ac97->reset = devm_reset_control_get_exclusive(&pdev->dev, "ac97");
	अगर (IS_ERR(ac97->reset)) अणु
		dev_err(&pdev->dev, "Can't retrieve ac97 reset\n");
		वापस PTR_ERR(ac97->reset);
	पूर्ण

	ac97->clk_ac97 = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(ac97->clk_ac97)) अणु
		dev_err(&pdev->dev, "Can't retrieve ac97 clock\n");
		ret = PTR_ERR(ac97->clk_ac97);
		जाओ err;
	पूर्ण

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(regs)) अणु
		ret = PTR_ERR(regs);
		जाओ err_clk_put;
	पूर्ण

	ac97->regmap = devm_regmap_init_mmio(&pdev->dev, regs,
					    &tegra20_ac97_regmap_config);
	अगर (IS_ERR(ac97->regmap)) अणु
		dev_err(&pdev->dev, "regmap init failed\n");
		ret = PTR_ERR(ac97->regmap);
		जाओ err_clk_put;
	पूर्ण

	ac97->reset_gpio = of_get_named_gpio(pdev->dev.of_node,
					     "nvidia,codec-reset-gpio", 0);
	अगर (gpio_is_valid(ac97->reset_gpio)) अणु
		ret = devm_gpio_request_one(&pdev->dev, ac97->reset_gpio,
					    GPIOF_OUT_INIT_HIGH, "codec-reset");
		अगर (ret) अणु
			dev_err(&pdev->dev, "could not get codec-reset GPIO\n");
			जाओ err_clk_put;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "no codec-reset GPIO supplied\n");
		जाओ err_clk_put;
	पूर्ण

	ac97->sync_gpio = of_get_named_gpio(pdev->dev.of_node,
					    "nvidia,codec-sync-gpio", 0);
	अगर (!gpio_is_valid(ac97->sync_gpio)) अणु
		dev_err(&pdev->dev, "no codec-sync GPIO supplied\n");
		जाओ err_clk_put;
	पूर्ण

	ac97->capture_dma_data.addr = mem->start + TEGRA20_AC97_FIFO_RX1;
	ac97->capture_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	ac97->capture_dma_data.maxburst = 4;

	ac97->playback_dma_data.addr = mem->start + TEGRA20_AC97_FIFO_TX1;
	ac97->playback_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	ac97->playback_dma_data.maxburst = 4;

	ret = reset_control_निश्चित(ac97->reset);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to assert AC'97 reset: %d\n", ret);
		जाओ err_clk_put;
	पूर्ण

	ret = clk_prepare_enable(ac97->clk_ac97);
	अगर (ret) अणु
		dev_err(&pdev->dev, "clk_enable failed: %d\n", ret);
		जाओ err_clk_put;
	पूर्ण

	usleep_range(10, 100);

	ret = reset_control_deनिश्चित(ac97->reset);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to deassert AC'97 reset: %d\n", ret);
		जाओ err_clk_disable_unprepare;
	पूर्ण

	ret = snd_soc_set_ac97_ops(&tegra20_ac97_ops);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to set AC'97 ops: %d\n", ret);
		जाओ err_clk_disable_unprepare;
	पूर्ण

	ret = snd_soc_रेजिस्टर_component(&pdev->dev, &tegra20_ac97_component,
					 &tegra20_ac97_dai, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not register DAI: %d\n", ret);
		ret = -ENOMEM;
		जाओ err_clk_disable_unprepare;
	पूर्ण

	ret = tegra_pcm_platक्रमm_रेजिस्टर(&pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not register PCM: %d\n", ret);
		जाओ err_unरेजिस्टर_component;
	पूर्ण

	/* XXX: crufty ASoC AC97 API - only one AC97 codec allowed */
	workdata = ac97;

	वापस 0;

err_unरेजिस्टर_component:
	snd_soc_unरेजिस्टर_component(&pdev->dev);
err_clk_disable_unprepare:
	clk_disable_unprepare(ac97->clk_ac97);
err_clk_put:
err:
	snd_soc_set_ac97_ops(शून्य);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra20_ac97_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra20_ac97 *ac97 = dev_get_drvdata(&pdev->dev);

	tegra_pcm_platक्रमm_unरेजिस्टर(&pdev->dev);
	snd_soc_unरेजिस्टर_component(&pdev->dev);

	clk_disable_unprepare(ac97->clk_ac97);

	snd_soc_set_ac97_ops(शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra20_ac97_of_match[] = अणु
	अणु .compatible = "nvidia,tegra20-ac97", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra20_ac97_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = tegra20_ac97_of_match,
	पूर्ण,
	.probe = tegra20_ac97_platक्रमm_probe,
	.हटाओ = tegra20_ac97_platक्रमm_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra20_ac97_driver);

MODULE_AUTHOR("Lucas Stach");
MODULE_DESCRIPTION("Tegra20 AC97 ASoC driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DEVICE_TABLE(of, tegra20_ac97_of_match);
