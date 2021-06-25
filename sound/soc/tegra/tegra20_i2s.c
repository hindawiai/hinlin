<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tegra20_i2s.c - Tegra20 I2S driver
 *
 * Author: Stephen Warren <swarren@nvidia.com>
 * Copyright (C) 2010,2012 - NVIDIA, Inc.
 *
 * Based on code copyright/by:
 *
 * Copyright (c) 2009-2010, NVIDIA Corporation.
 * Scott Peterson <speterson@nvidia.com>
 *
 * Copyright (C) 2010 Google, Inc.
 * Iliyan Malchev <malchev@google.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
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

#समावेश "tegra20_i2s.h"

#घोषणा DRV_NAME "tegra20-i2s"

अटल __maybe_unused पूर्णांक tegra20_i2s_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra20_i2s *i2s = dev_get_drvdata(dev);

	regcache_cache_only(i2s->regmap, true);

	clk_disable_unprepare(i2s->clk_i2s);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक tegra20_i2s_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra20_i2s *i2s = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = reset_control_निश्चित(i2s->reset);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(i2s->clk_i2s);
	अगर (ret) अणु
		dev_err(dev, "clk_enable failed: %d\n", ret);
		वापस ret;
	पूर्ण

	usleep_range(10, 100);

	ret = reset_control_deनिश्चित(i2s->reset);
	अगर (ret)
		जाओ disable_घड़ीs;

	regcache_cache_only(i2s->regmap, false);
	regcache_mark_dirty(i2s->regmap);

	ret = regcache_sync(i2s->regmap);
	अगर (ret)
		जाओ disable_घड़ीs;

	वापस 0;

disable_घड़ीs:
	clk_disable_unprepare(i2s->clk_i2s);

	वापस ret;
पूर्ण

अटल पूर्णांक tegra20_i2s_set_fmt(काष्ठा snd_soc_dai *dai,
				अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा tegra20_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक mask = 0, val = 0;

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mask |= TEGRA20_I2S_CTRL_MASTER_ENABLE;
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		val |= TEGRA20_I2S_CTRL_MASTER_ENABLE;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mask |= TEGRA20_I2S_CTRL_BIT_FORMAT_MASK |
		TEGRA20_I2S_CTRL_LRCK_MASK;
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		val |= TEGRA20_I2S_CTRL_BIT_FORMAT_DSP;
		val |= TEGRA20_I2S_CTRL_LRCK_L_LOW;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		val |= TEGRA20_I2S_CTRL_BIT_FORMAT_DSP;
		val |= TEGRA20_I2S_CTRL_LRCK_R_LOW;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		val |= TEGRA20_I2S_CTRL_BIT_FORMAT_I2S;
		val |= TEGRA20_I2S_CTRL_LRCK_L_LOW;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		val |= TEGRA20_I2S_CTRL_BIT_FORMAT_RJM;
		val |= TEGRA20_I2S_CTRL_LRCK_L_LOW;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		val |= TEGRA20_I2S_CTRL_BIT_FORMAT_LJM;
		val |= TEGRA20_I2S_CTRL_LRCK_L_LOW;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, TEGRA20_I2S_CTRL, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra20_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा device *dev = dai->dev;
	काष्ठा tegra20_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक mask, val;
	पूर्णांक ret, sample_size, srate, i2sघड़ी, bitcnt;

	mask = TEGRA20_I2S_CTRL_BIT_SIZE_MASK;
	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		val = TEGRA20_I2S_CTRL_BIT_SIZE_16;
		sample_size = 16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		val = TEGRA20_I2S_CTRL_BIT_SIZE_24;
		sample_size = 24;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		val = TEGRA20_I2S_CTRL_BIT_SIZE_32;
		sample_size = 32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mask |= TEGRA20_I2S_CTRL_FIFO_FORMAT_MASK;
	val |= TEGRA20_I2S_CTRL_FIFO_FORMAT_PACKED;

	regmap_update_bits(i2s->regmap, TEGRA20_I2S_CTRL, mask, val);

	srate = params_rate(params);

	/* Final "* 2" required by Tegra hardware */
	i2sघड़ी = srate * params_channels(params) * sample_size * 2;

	ret = clk_set_rate(i2s->clk_i2s, i2sघड़ी);
	अगर (ret) अणु
		dev_err(dev, "Can't set I2S clock rate: %d\n", ret);
		वापस ret;
	पूर्ण

	bitcnt = (i2sघड़ी / (2 * srate)) - 1;
	अगर (bitcnt < 0 || bitcnt > TEGRA20_I2S_TIMING_CHANNEL_BIT_COUNT_MASK_US)
		वापस -EINVAL;
	val = bitcnt << TEGRA20_I2S_TIMING_CHANNEL_BIT_COUNT_SHIFT;

	अगर (i2sघड़ी % (2 * srate))
		val |= TEGRA20_I2S_TIMING_NON_SYM_ENABLE;

	regmap_ग_लिखो(i2s->regmap, TEGRA20_I2S_TIMING, val);

	regmap_ग_लिखो(i2s->regmap, TEGRA20_I2S_FIFO_SCR,
		     TEGRA20_I2S_FIFO_SCR_FIFO2_ATN_LVL_FOUR_SLOTS |
		     TEGRA20_I2S_FIFO_SCR_FIFO1_ATN_LVL_FOUR_SLOTS);

	वापस 0;
पूर्ण

अटल व्योम tegra20_i2s_start_playback(काष्ठा tegra20_i2s *i2s)
अणु
	regmap_update_bits(i2s->regmap, TEGRA20_I2S_CTRL,
			   TEGRA20_I2S_CTRL_FIFO1_ENABLE,
			   TEGRA20_I2S_CTRL_FIFO1_ENABLE);
पूर्ण

अटल व्योम tegra20_i2s_stop_playback(काष्ठा tegra20_i2s *i2s)
अणु
	regmap_update_bits(i2s->regmap, TEGRA20_I2S_CTRL,
			   TEGRA20_I2S_CTRL_FIFO1_ENABLE, 0);
पूर्ण

अटल व्योम tegra20_i2s_start_capture(काष्ठा tegra20_i2s *i2s)
अणु
	regmap_update_bits(i2s->regmap, TEGRA20_I2S_CTRL,
			   TEGRA20_I2S_CTRL_FIFO2_ENABLE,
			   TEGRA20_I2S_CTRL_FIFO2_ENABLE);
पूर्ण

अटल व्योम tegra20_i2s_stop_capture(काष्ठा tegra20_i2s *i2s)
अणु
	regmap_update_bits(i2s->regmap, TEGRA20_I2S_CTRL,
			   TEGRA20_I2S_CTRL_FIFO2_ENABLE, 0);
पूर्ण

अटल पूर्णांक tegra20_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा tegra20_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			tegra20_i2s_start_playback(i2s);
		अन्यथा
			tegra20_i2s_start_capture(i2s);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			tegra20_i2s_stop_playback(i2s);
		अन्यथा
			tegra20_i2s_stop_capture(i2s);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra20_i2s_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा tegra20_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	dai->capture_dma_data = &i2s->capture_dma_data;
	dai->playback_dma_data = &i2s->playback_dma_data;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops tegra20_i2s_dai_ops = अणु
	.set_fmt	= tegra20_i2s_set_fmt,
	.hw_params	= tegra20_i2s_hw_params,
	.trigger	= tegra20_i2s_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_driver tegra20_i2s_dai_ढाँचा = अणु
	.probe = tegra20_i2s_probe,
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.ops = &tegra20_i2s_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver tegra20_i2s_component = अणु
	.name		= DRV_NAME,
पूर्ण;

अटल bool tegra20_i2s_wr_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA20_I2S_CTRL:
	हाल TEGRA20_I2S_STATUS:
	हाल TEGRA20_I2S_TIMING:
	हाल TEGRA20_I2S_FIFO_SCR:
	हाल TEGRA20_I2S_PCM_CTRL:
	हाल TEGRA20_I2S_NW_CTRL:
	हाल TEGRA20_I2S_TDM_CTRL:
	हाल TEGRA20_I2S_TDM_TX_RX_CTRL:
	हाल TEGRA20_I2S_FIFO1:
	हाल TEGRA20_I2S_FIFO2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool tegra20_i2s_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA20_I2S_STATUS:
	हाल TEGRA20_I2S_FIFO_SCR:
	हाल TEGRA20_I2S_FIFO1:
	हाल TEGRA20_I2S_FIFO2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool tegra20_i2s_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA20_I2S_FIFO1:
	हाल TEGRA20_I2S_FIFO2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config tegra20_i2s_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = TEGRA20_I2S_FIFO2,
	.ग_लिखोable_reg = tegra20_i2s_wr_rd_reg,
	.पढ़ोable_reg = tegra20_i2s_wr_rd_reg,
	.अस्थिर_reg = tegra20_i2s_अस्थिर_reg,
	.precious_reg = tegra20_i2s_precious_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक tegra20_i2s_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra20_i2s *i2s;
	काष्ठा resource *mem;
	व्योम __iomem *regs;
	पूर्णांक ret;

	i2s = devm_kzalloc(&pdev->dev, माप(काष्ठा tegra20_i2s), GFP_KERNEL);
	अगर (!i2s) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	dev_set_drvdata(&pdev->dev, i2s);

	i2s->dai = tegra20_i2s_dai_ढाँचा;
	i2s->dai.name = dev_name(&pdev->dev);

	i2s->reset = devm_reset_control_get_exclusive(&pdev->dev, "i2s");
	अगर (IS_ERR(i2s->reset)) अणु
		dev_err(&pdev->dev, "Can't retrieve i2s reset\n");
		वापस PTR_ERR(i2s->reset);
	पूर्ण

	i2s->clk_i2s = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(i2s->clk_i2s)) अणु
		dev_err(&pdev->dev, "Can't retrieve i2s clock\n");
		ret = PTR_ERR(i2s->clk_i2s);
		जाओ err;
	पूर्ण

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(regs)) अणु
		ret = PTR_ERR(regs);
		जाओ err;
	पूर्ण

	i2s->regmap = devm_regmap_init_mmio(&pdev->dev, regs,
					    &tegra20_i2s_regmap_config);
	अगर (IS_ERR(i2s->regmap)) अणु
		dev_err(&pdev->dev, "regmap init failed\n");
		ret = PTR_ERR(i2s->regmap);
		जाओ err;
	पूर्ण

	i2s->capture_dma_data.addr = mem->start + TEGRA20_I2S_FIFO2;
	i2s->capture_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	i2s->capture_dma_data.maxburst = 4;

	i2s->playback_dma_data.addr = mem->start + TEGRA20_I2S_FIFO1;
	i2s->playback_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	i2s->playback_dma_data.maxburst = 4;

	pm_runसमय_enable(&pdev->dev);

	ret = snd_soc_रेजिस्टर_component(&pdev->dev, &tegra20_i2s_component,
					 &i2s->dai, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not register DAI: %d\n", ret);
		ret = -ENOMEM;
		जाओ err_pm_disable;
	पूर्ण

	ret = tegra_pcm_platक्रमm_रेजिस्टर(&pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not register PCM: %d\n", ret);
		जाओ err_unरेजिस्टर_component;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_component:
	snd_soc_unरेजिस्टर_component(&pdev->dev);
err_pm_disable:
	pm_runसमय_disable(&pdev->dev);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक tegra20_i2s_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	tegra_pcm_platक्रमm_unरेजिस्टर(&pdev->dev);
	snd_soc_unरेजिस्टर_component(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra20_i2s_of_match[] = अणु
	अणु .compatible = "nvidia,tegra20-i2s", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops tegra20_i2s_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra20_i2s_runसमय_suspend,
			   tegra20_i2s_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra20_i2s_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = tegra20_i2s_of_match,
		.pm = &tegra20_i2s_pm_ops,
	पूर्ण,
	.probe = tegra20_i2s_platक्रमm_probe,
	.हटाओ = tegra20_i2s_platक्रमm_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra20_i2s_driver);

MODULE_AUTHOR("Stephen Warren <swarren@nvidia.com>");
MODULE_DESCRIPTION("Tegra20 I2S ASoC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DEVICE_TABLE(of, tegra20_i2s_of_match);
