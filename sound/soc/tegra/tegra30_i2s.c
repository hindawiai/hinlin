<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tegra30_i2s.c - Tegra30 I2S driver
 *
 * Author: Stephen Warren <swarren@nvidia.com>
 * Copyright (c) 2010-2012, NVIDIA CORPORATION.  All rights reserved.
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
#समावेश <linux/of_device.h>
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

#समावेश "tegra30_ahub.h"
#समावेश "tegra30_i2s.h"

#घोषणा DRV_NAME "tegra30-i2s"

अटल __maybe_unused पूर्णांक tegra30_i2s_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra30_i2s *i2s = dev_get_drvdata(dev);

	regcache_cache_only(i2s->regmap, true);

	clk_disable_unprepare(i2s->clk_i2s);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक tegra30_i2s_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra30_i2s *i2s = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(i2s->clk_i2s);
	अगर (ret) अणु
		dev_err(dev, "clk_enable failed: %d\n", ret);
		वापस ret;
	पूर्ण

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

अटल पूर्णांक tegra30_i2s_set_fmt(काष्ठा snd_soc_dai *dai,
				अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा tegra30_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक mask = 0, val = 0;

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mask |= TEGRA30_I2S_CTRL_MASTER_ENABLE;
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		val |= TEGRA30_I2S_CTRL_MASTER_ENABLE;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mask |= TEGRA30_I2S_CTRL_FRAME_FORMAT_MASK |
		TEGRA30_I2S_CTRL_LRCK_MASK;
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		val |= TEGRA30_I2S_CTRL_FRAME_FORMAT_FSYNC;
		val |= TEGRA30_I2S_CTRL_LRCK_L_LOW;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		val |= TEGRA30_I2S_CTRL_FRAME_FORMAT_FSYNC;
		val |= TEGRA30_I2S_CTRL_LRCK_R_LOW;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		val |= TEGRA30_I2S_CTRL_FRAME_FORMAT_LRCK;
		val |= TEGRA30_I2S_CTRL_LRCK_L_LOW;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		val |= TEGRA30_I2S_CTRL_FRAME_FORMAT_LRCK;
		val |= TEGRA30_I2S_CTRL_LRCK_L_LOW;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		val |= TEGRA30_I2S_CTRL_FRAME_FORMAT_LRCK;
		val |= TEGRA30_I2S_CTRL_LRCK_L_LOW;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	pm_runसमय_get_sync(dai->dev);
	regmap_update_bits(i2s->regmap, TEGRA30_I2S_CTRL, mask, val);
	pm_runसमय_put(dai->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra30_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा device *dev = dai->dev;
	काष्ठा tegra30_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक mask, val, reg;
	पूर्णांक ret, sample_size, srate, i2sघड़ी, bitcnt;
	काष्ठा tegra30_ahub_cअगर_conf cअगर_conf;

	अगर (params_channels(params) != 2)
		वापस -EINVAL;

	mask = TEGRA30_I2S_CTRL_BIT_SIZE_MASK;
	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		val = TEGRA30_I2S_CTRL_BIT_SIZE_16;
		sample_size = 16;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(i2s->regmap, TEGRA30_I2S_CTRL, mask, val);

	srate = params_rate(params);

	/* Final "* 2" required by Tegra hardware */
	i2sघड़ी = srate * params_channels(params) * sample_size * 2;

	bitcnt = (i2sघड़ी / (2 * srate)) - 1;
	अगर (bitcnt < 0 || bitcnt > TEGRA30_I2S_TIMING_CHANNEL_BIT_COUNT_MASK_US)
		वापस -EINVAL;

	ret = clk_set_rate(i2s->clk_i2s, i2sघड़ी);
	अगर (ret) अणु
		dev_err(dev, "Can't set I2S clock rate: %d\n", ret);
		वापस ret;
	पूर्ण

	val = bitcnt << TEGRA30_I2S_TIMING_CHANNEL_BIT_COUNT_SHIFT;

	अगर (i2sघड़ी % (2 * srate))
		val |= TEGRA30_I2S_TIMING_NON_SYM_ENABLE;

	regmap_ग_लिखो(i2s->regmap, TEGRA30_I2S_TIMING, val);

	cअगर_conf.threshold = 0;
	cअगर_conf.audio_channels = 2;
	cअगर_conf.client_channels = 2;
	cअगर_conf.audio_bits = TEGRA30_AUDIOCIF_BITS_16;
	cअगर_conf.client_bits = TEGRA30_AUDIOCIF_BITS_16;
	cअगर_conf.expand = 0;
	cअगर_conf.stereo_conv = 0;
	cअगर_conf.replicate = 0;
	cअगर_conf.truncate = 0;
	cअगर_conf.mono_conv = 0;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		cअगर_conf.direction = TEGRA30_AUDIOCIF_सूचीECTION_RX;
		reg = TEGRA30_I2S_CIF_RX_CTRL;
	पूर्ण अन्यथा अणु
		cअगर_conf.direction = TEGRA30_AUDIOCIF_सूचीECTION_TX;
		reg = TEGRA30_I2S_CIF_TX_CTRL;
	पूर्ण

	i2s->soc_data->set_audio_cअगर(i2s->regmap, reg, &cअगर_conf);

	val = (1 << TEGRA30_I2S_OFFSET_RX_DATA_OFFSET_SHIFT) |
	      (1 << TEGRA30_I2S_OFFSET_TX_DATA_OFFSET_SHIFT);
	regmap_ग_लिखो(i2s->regmap, TEGRA30_I2S_OFFSET, val);

	वापस 0;
पूर्ण

अटल व्योम tegra30_i2s_start_playback(काष्ठा tegra30_i2s *i2s)
अणु
	tegra30_ahub_enable_tx_fअगरo(i2s->playback_fअगरo_cअगर);
	regmap_update_bits(i2s->regmap, TEGRA30_I2S_CTRL,
			   TEGRA30_I2S_CTRL_XFER_EN_TX,
			   TEGRA30_I2S_CTRL_XFER_EN_TX);
पूर्ण

अटल व्योम tegra30_i2s_stop_playback(काष्ठा tegra30_i2s *i2s)
अणु
	tegra30_ahub_disable_tx_fअगरo(i2s->playback_fअगरo_cअगर);
	regmap_update_bits(i2s->regmap, TEGRA30_I2S_CTRL,
			   TEGRA30_I2S_CTRL_XFER_EN_TX, 0);
पूर्ण

अटल व्योम tegra30_i2s_start_capture(काष्ठा tegra30_i2s *i2s)
अणु
	tegra30_ahub_enable_rx_fअगरo(i2s->capture_fअगरo_cअगर);
	regmap_update_bits(i2s->regmap, TEGRA30_I2S_CTRL,
			   TEGRA30_I2S_CTRL_XFER_EN_RX,
			   TEGRA30_I2S_CTRL_XFER_EN_RX);
पूर्ण

अटल व्योम tegra30_i2s_stop_capture(काष्ठा tegra30_i2s *i2s)
अणु
	regmap_update_bits(i2s->regmap, TEGRA30_I2S_CTRL,
			   TEGRA30_I2S_CTRL_XFER_EN_RX, 0);
	tegra30_ahub_disable_rx_fअगरo(i2s->capture_fअगरo_cअगर);
पूर्ण

अटल पूर्णांक tegra30_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा tegra30_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			tegra30_i2s_start_playback(i2s);
		अन्यथा
			tegra30_i2s_start_capture(i2s);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			tegra30_i2s_stop_playback(i2s);
		अन्यथा
			tegra30_i2s_stop_capture(i2s);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra30_i2s_set_tdm(काष्ठा snd_soc_dai *dai,
			       अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
			       पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा tegra30_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक mask, val;

	dev_dbg(dai->dev, "%s: txmask=0x%08x rxmask=0x%08x slots=%d width=%d\n",
		 __func__, tx_mask, rx_mask, slots, slot_width);

	mask = TEGRA30_I2S_SLOT_CTRL_TOTAL_SLOTS_MASK |
	       TEGRA30_I2S_SLOT_CTRL_RX_SLOT_ENABLES_MASK |
	       TEGRA30_I2S_SLOT_CTRL_TX_SLOT_ENABLES_MASK;

	val = (tx_mask << TEGRA30_I2S_SLOT_CTRL_TX_SLOT_ENABLES_SHIFT) |
	      (rx_mask << TEGRA30_I2S_SLOT_CTRL_RX_SLOT_ENABLES_SHIFT) |
	      ((slots - 1) << TEGRA30_I2S_SLOT_CTRL_TOTAL_SLOTS_SHIFT);

	pm_runसमय_get_sync(dai->dev);
	regmap_update_bits(i2s->regmap, TEGRA30_I2S_SLOT_CTRL, mask, val);
	/* set the fsync width to minimum of 1 घड़ी width */
	regmap_update_bits(i2s->regmap, TEGRA30_I2S_CH_CTRL,
			   TEGRA30_I2S_CH_CTRL_FSYNC_WIDTH_MASK, 0x0);
	pm_runसमय_put(dai->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra30_i2s_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा tegra30_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	dai->capture_dma_data = &i2s->capture_dma_data;
	dai->playback_dma_data = &i2s->playback_dma_data;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops tegra30_i2s_dai_ops = अणु
	.set_fmt	= tegra30_i2s_set_fmt,
	.hw_params	= tegra30_i2s_hw_params,
	.trigger	= tegra30_i2s_trigger,
	.set_tdm_slot	= tegra30_i2s_set_tdm,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_driver tegra30_i2s_dai_ढाँचा = अणु
	.probe = tegra30_i2s_probe,
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
	.ops = &tegra30_i2s_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver tegra30_i2s_component = अणु
	.name		= DRV_NAME,
पूर्ण;

अटल bool tegra30_i2s_wr_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA30_I2S_CTRL:
	हाल TEGRA30_I2S_TIMING:
	हाल TEGRA30_I2S_OFFSET:
	हाल TEGRA30_I2S_CH_CTRL:
	हाल TEGRA30_I2S_SLOT_CTRL:
	हाल TEGRA30_I2S_CIF_RX_CTRL:
	हाल TEGRA30_I2S_CIF_TX_CTRL:
	हाल TEGRA30_I2S_FLOWCTL:
	हाल TEGRA30_I2S_TX_STEP:
	हाल TEGRA30_I2S_FLOW_STATUS:
	हाल TEGRA30_I2S_FLOW_TOTAL:
	हाल TEGRA30_I2S_FLOW_OVER:
	हाल TEGRA30_I2S_FLOW_UNDER:
	हाल TEGRA30_I2S_LCOEF_1_4_0:
	हाल TEGRA30_I2S_LCOEF_1_4_1:
	हाल TEGRA30_I2S_LCOEF_1_4_2:
	हाल TEGRA30_I2S_LCOEF_1_4_3:
	हाल TEGRA30_I2S_LCOEF_1_4_4:
	हाल TEGRA30_I2S_LCOEF_1_4_5:
	हाल TEGRA30_I2S_LCOEF_2_4_0:
	हाल TEGRA30_I2S_LCOEF_2_4_1:
	हाल TEGRA30_I2S_LCOEF_2_4_2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool tegra30_i2s_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA30_I2S_FLOW_STATUS:
	हाल TEGRA30_I2S_FLOW_TOTAL:
	हाल TEGRA30_I2S_FLOW_OVER:
	हाल TEGRA30_I2S_FLOW_UNDER:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config tegra30_i2s_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = TEGRA30_I2S_LCOEF_2_4_2,
	.ग_लिखोable_reg = tegra30_i2s_wr_rd_reg,
	.पढ़ोable_reg = tegra30_i2s_wr_rd_reg,
	.अस्थिर_reg = tegra30_i2s_अस्थिर_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा tegra30_i2s_soc_data tegra30_i2s_config = अणु
	.set_audio_cअगर = tegra30_ahub_set_cअगर,
पूर्ण;

अटल स्थिर काष्ठा tegra30_i2s_soc_data tegra124_i2s_config = अणु
	.set_audio_cअगर = tegra124_ahub_set_cअगर,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra30_i2s_of_match[] = अणु
	अणु .compatible = "nvidia,tegra124-i2s", .data = &tegra124_i2s_config पूर्ण,
	अणु .compatible = "nvidia,tegra30-i2s", .data = &tegra30_i2s_config पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक tegra30_i2s_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra30_i2s *i2s;
	स्थिर काष्ठा of_device_id *match;
	u32 cअगर_ids[2];
	व्योम __iomem *regs;
	पूर्णांक ret;

	i2s = devm_kzalloc(&pdev->dev, माप(काष्ठा tegra30_i2s), GFP_KERNEL);
	अगर (!i2s) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	dev_set_drvdata(&pdev->dev, i2s);

	match = of_match_device(tegra30_i2s_of_match, &pdev->dev);
	अगर (!match) अणु
		dev_err(&pdev->dev, "Error: No device match found\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण
	i2s->soc_data = (काष्ठा tegra30_i2s_soc_data *)match->data;

	i2s->dai = tegra30_i2s_dai_ढाँचा;
	i2s->dai.name = dev_name(&pdev->dev);

	ret = of_property_पढ़ो_u32_array(pdev->dev.of_node,
					 "nvidia,ahub-cif-ids", cअगर_ids,
					 ARRAY_SIZE(cअगर_ids));
	अगर (ret < 0)
		जाओ err;

	i2s->playback_i2s_cअगर = cअगर_ids[0];
	i2s->capture_i2s_cअगर = cअगर_ids[1];

	i2s->clk_i2s = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(i2s->clk_i2s)) अणु
		dev_err(&pdev->dev, "Can't retrieve i2s clock\n");
		ret = PTR_ERR(i2s->clk_i2s);
		जाओ err;
	पूर्ण

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs)) अणु
		ret = PTR_ERR(regs);
		जाओ err;
	पूर्ण

	i2s->regmap = devm_regmap_init_mmio(&pdev->dev, regs,
					    &tegra30_i2s_regmap_config);
	अगर (IS_ERR(i2s->regmap)) अणु
		dev_err(&pdev->dev, "regmap init failed\n");
		ret = PTR_ERR(i2s->regmap);
		जाओ err;
	पूर्ण
	regcache_cache_only(i2s->regmap, true);

	pm_runसमय_enable(&pdev->dev);

	i2s->playback_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	i2s->playback_dma_data.maxburst = 4;
	ret = tegra30_ahub_allocate_tx_fअगरo(&i2s->playback_fअगरo_cअगर,
					    i2s->playback_dma_chan,
					    माप(i2s->playback_dma_chan),
					    &i2s->playback_dma_data.addr);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not alloc TX FIFO: %d\n", ret);
		जाओ err_pm_disable;
	पूर्ण
	ret = tegra30_ahub_set_rx_cअगर_source(i2s->playback_i2s_cअगर,
					     i2s->playback_fअगरo_cअगर);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not route TX FIFO: %d\n", ret);
		जाओ err_मुक्त_tx_fअगरo;
	पूर्ण

	i2s->capture_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	i2s->capture_dma_data.maxburst = 4;
	ret = tegra30_ahub_allocate_rx_fअगरo(&i2s->capture_fअगरo_cअगर,
					    i2s->capture_dma_chan,
					    माप(i2s->capture_dma_chan),
					    &i2s->capture_dma_data.addr);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not alloc RX FIFO: %d\n", ret);
		जाओ err_unroute_tx_fअगरo;
	पूर्ण
	ret = tegra30_ahub_set_rx_cअगर_source(i2s->capture_fअगरo_cअगर,
					     i2s->capture_i2s_cअगर);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not route TX FIFO: %d\n", ret);
		जाओ err_मुक्त_rx_fअगरo;
	पूर्ण

	ret = snd_soc_रेजिस्टर_component(&pdev->dev, &tegra30_i2s_component,
				   &i2s->dai, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not register DAI: %d\n", ret);
		ret = -ENOMEM;
		जाओ err_unroute_rx_fअगरo;
	पूर्ण

	ret = tegra_pcm_platक्रमm_रेजिस्टर_with_chan_names(&pdev->dev,
				&i2s->dma_config, i2s->playback_dma_chan,
				i2s->capture_dma_chan);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not register PCM: %d\n", ret);
		जाओ err_unरेजिस्टर_component;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_component:
	snd_soc_unरेजिस्टर_component(&pdev->dev);
err_unroute_rx_fअगरo:
	tegra30_ahub_unset_rx_cअगर_source(i2s->capture_fअगरo_cअगर);
err_मुक्त_rx_fअगरo:
	tegra30_ahub_मुक्त_rx_fअगरo(i2s->capture_fअगरo_cअगर);
err_unroute_tx_fअगरo:
	tegra30_ahub_unset_rx_cअगर_source(i2s->playback_i2s_cअगर);
err_मुक्त_tx_fअगरo:
	tegra30_ahub_मुक्त_tx_fअगरo(i2s->playback_fअगरo_cअगर);
err_pm_disable:
	pm_runसमय_disable(&pdev->dev);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक tegra30_i2s_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra30_i2s *i2s = dev_get_drvdata(&pdev->dev);

	tegra_pcm_platक्रमm_unरेजिस्टर(&pdev->dev);
	snd_soc_unरेजिस्टर_component(&pdev->dev);

	tegra30_ahub_unset_rx_cअगर_source(i2s->capture_fअगरo_cअगर);
	tegra30_ahub_मुक्त_rx_fअगरo(i2s->capture_fअगरo_cअगर);

	tegra30_ahub_unset_rx_cअगर_source(i2s->playback_i2s_cअगर);
	tegra30_ahub_मुक्त_tx_fअगरo(i2s->playback_fअगरo_cअगर);

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra30_i2s_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra30_i2s_runसमय_suspend,
			   tegra30_i2s_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra30_i2s_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = tegra30_i2s_of_match,
		.pm = &tegra30_i2s_pm_ops,
	पूर्ण,
	.probe = tegra30_i2s_platक्रमm_probe,
	.हटाओ = tegra30_i2s_platक्रमm_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra30_i2s_driver);

MODULE_AUTHOR("Stephen Warren <swarren@nvidia.com>");
MODULE_DESCRIPTION("Tegra30 I2S ASoC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DEVICE_TABLE(of, tegra30_i2s_of_match);
