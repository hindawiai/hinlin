<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tegra20_spdअगर.c - Tegra20 SPDIF driver
 *
 * Author: Stephen Warren <swarren@nvidia.com>
 * Copyright (C) 2011-2012 - NVIDIA, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "tegra20_spdif.h"

#घोषणा DRV_NAME "tegra20-spdif"

अटल __maybe_unused पूर्णांक tegra20_spdअगर_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra20_spdअगर *spdअगर = dev_get_drvdata(dev);

	clk_disable_unprepare(spdअगर->clk_spdअगर_out);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक tegra20_spdअगर_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra20_spdअगर *spdअगर = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(spdअगर->clk_spdअगर_out);
	अगर (ret) अणु
		dev_err(dev, "clk_enable failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra20_spdअगर_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा device *dev = dai->dev;
	काष्ठा tegra20_spdअगर *spdअगर = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक mask = 0, val = 0;
	पूर्णांक ret, spdअगरघड़ी;

	mask |= TEGRA20_SPDIF_CTRL_PACK |
		TEGRA20_SPDIF_CTRL_BIT_MODE_MASK;
	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		val |= TEGRA20_SPDIF_CTRL_PACK |
		       TEGRA20_SPDIF_CTRL_BIT_MODE_16BIT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(spdअगर->regmap, TEGRA20_SPDIF_CTRL, mask, val);

	चयन (params_rate(params)) अणु
	हाल 32000:
		spdअगरघड़ी = 4096000;
		अवरोध;
	हाल 44100:
		spdअगरघड़ी = 5644800;
		अवरोध;
	हाल 48000:
		spdअगरघड़ी = 6144000;
		अवरोध;
	हाल 88200:
		spdअगरघड़ी = 11289600;
		अवरोध;
	हाल 96000:
		spdअगरघड़ी = 12288000;
		अवरोध;
	हाल 176400:
		spdअगरघड़ी = 22579200;
		अवरोध;
	हाल 192000:
		spdअगरघड़ी = 24576000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = clk_set_rate(spdअगर->clk_spdअगर_out, spdअगरघड़ी);
	अगर (ret) अणु
		dev_err(dev, "Can't set SPDIF clock rate: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tegra20_spdअगर_start_playback(काष्ठा tegra20_spdअगर *spdअगर)
अणु
	regmap_update_bits(spdअगर->regmap, TEGRA20_SPDIF_CTRL,
			   TEGRA20_SPDIF_CTRL_TX_EN,
			   TEGRA20_SPDIF_CTRL_TX_EN);
पूर्ण

अटल व्योम tegra20_spdअगर_stop_playback(काष्ठा tegra20_spdअगर *spdअगर)
अणु
	regmap_update_bits(spdअगर->regmap, TEGRA20_SPDIF_CTRL,
			   TEGRA20_SPDIF_CTRL_TX_EN, 0);
पूर्ण

अटल पूर्णांक tegra20_spdअगर_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा tegra20_spdअगर *spdअगर = snd_soc_dai_get_drvdata(dai);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		tegra20_spdअगर_start_playback(spdअगर);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		tegra20_spdअगर_stop_playback(spdअगर);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra20_spdअगर_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा tegra20_spdअगर *spdअगर = snd_soc_dai_get_drvdata(dai);

	dai->capture_dma_data = शून्य;
	dai->playback_dma_data = &spdअगर->playback_dma_data;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops tegra20_spdअगर_dai_ops = अणु
	.hw_params	= tegra20_spdअगर_hw_params,
	.trigger	= tegra20_spdअगर_trigger,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver tegra20_spdअगर_dai = अणु
	.name = DRV_NAME,
	.probe = tegra20_spdअगर_probe,
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |
				SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.ops = &tegra20_spdअगर_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver tegra20_spdअगर_component = अणु
	.name		= DRV_NAME,
पूर्ण;

अटल bool tegra20_spdअगर_wr_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA20_SPDIF_CTRL:
	हाल TEGRA20_SPDIF_STATUS:
	हाल TEGRA20_SPDIF_STROBE_CTRL:
	हाल TEGRA20_SPDIF_DATA_FIFO_CSR:
	हाल TEGRA20_SPDIF_DATA_OUT:
	हाल TEGRA20_SPDIF_DATA_IN:
	हाल TEGRA20_SPDIF_CH_STA_RX_A:
	हाल TEGRA20_SPDIF_CH_STA_RX_B:
	हाल TEGRA20_SPDIF_CH_STA_RX_C:
	हाल TEGRA20_SPDIF_CH_STA_RX_D:
	हाल TEGRA20_SPDIF_CH_STA_RX_E:
	हाल TEGRA20_SPDIF_CH_STA_RX_F:
	हाल TEGRA20_SPDIF_CH_STA_TX_A:
	हाल TEGRA20_SPDIF_CH_STA_TX_B:
	हाल TEGRA20_SPDIF_CH_STA_TX_C:
	हाल TEGRA20_SPDIF_CH_STA_TX_D:
	हाल TEGRA20_SPDIF_CH_STA_TX_E:
	हाल TEGRA20_SPDIF_CH_STA_TX_F:
	हाल TEGRA20_SPDIF_USR_STA_RX_A:
	हाल TEGRA20_SPDIF_USR_DAT_TX_A:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool tegra20_spdअगर_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA20_SPDIF_STATUS:
	हाल TEGRA20_SPDIF_DATA_FIFO_CSR:
	हाल TEGRA20_SPDIF_DATA_OUT:
	हाल TEGRA20_SPDIF_DATA_IN:
	हाल TEGRA20_SPDIF_CH_STA_RX_A:
	हाल TEGRA20_SPDIF_CH_STA_RX_B:
	हाल TEGRA20_SPDIF_CH_STA_RX_C:
	हाल TEGRA20_SPDIF_CH_STA_RX_D:
	हाल TEGRA20_SPDIF_CH_STA_RX_E:
	हाल TEGRA20_SPDIF_CH_STA_RX_F:
	हाल TEGRA20_SPDIF_USR_STA_RX_A:
	हाल TEGRA20_SPDIF_USR_DAT_TX_A:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool tegra20_spdअगर_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA20_SPDIF_DATA_OUT:
	हाल TEGRA20_SPDIF_DATA_IN:
	हाल TEGRA20_SPDIF_USR_STA_RX_A:
	हाल TEGRA20_SPDIF_USR_DAT_TX_A:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config tegra20_spdअगर_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = TEGRA20_SPDIF_USR_DAT_TX_A,
	.ग_लिखोable_reg = tegra20_spdअगर_wr_rd_reg,
	.पढ़ोable_reg = tegra20_spdअगर_wr_rd_reg,
	.अस्थिर_reg = tegra20_spdअगर_अस्थिर_reg,
	.precious_reg = tegra20_spdअगर_precious_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक tegra20_spdअगर_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra20_spdअगर *spdअगर;
	काष्ठा resource *mem, *dmareq;
	व्योम __iomem *regs;
	पूर्णांक ret;

	spdअगर = devm_kzalloc(&pdev->dev, माप(काष्ठा tegra20_spdअगर),
			     GFP_KERNEL);
	अगर (!spdअगर)
		वापस -ENOMEM;

	dev_set_drvdata(&pdev->dev, spdअगर);

	spdअगर->clk_spdअगर_out = devm_clk_get(&pdev->dev, "spdif_out");
	अगर (IS_ERR(spdअगर->clk_spdअगर_out)) अणु
		pr_err("Can't retrieve spdif clock\n");
		ret = PTR_ERR(spdअगर->clk_spdअगर_out);
		वापस ret;
	पूर्ण

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	dmareq = platक्रमm_get_resource(pdev, IORESOURCE_DMA, 0);
	अगर (!dmareq) अणु
		dev_err(&pdev->dev, "No DMA resource\n");
		वापस -ENODEV;
	पूर्ण

	spdअगर->regmap = devm_regmap_init_mmio(&pdev->dev, regs,
					    &tegra20_spdअगर_regmap_config);
	अगर (IS_ERR(spdअगर->regmap)) अणु
		dev_err(&pdev->dev, "regmap init failed\n");
		ret = PTR_ERR(spdअगर->regmap);
		वापस ret;
	पूर्ण

	spdअगर->playback_dma_data.addr = mem->start + TEGRA20_SPDIF_DATA_OUT;
	spdअगर->playback_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	spdअगर->playback_dma_data.maxburst = 4;
	spdअगर->playback_dma_data.slave_id = dmareq->start;

	pm_runसमय_enable(&pdev->dev);

	ret = snd_soc_रेजिस्टर_component(&pdev->dev, &tegra20_spdअगर_component,
					 &tegra20_spdअगर_dai, 1);
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

	वापस ret;
पूर्ण

अटल पूर्णांक tegra20_spdअगर_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	tegra_pcm_platक्रमm_unरेजिस्टर(&pdev->dev);
	snd_soc_unरेजिस्टर_component(&pdev->dev);

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra20_spdअगर_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra20_spdअगर_runसमय_suspend,
			   tegra20_spdअगर_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra20_spdअगर_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.pm = &tegra20_spdअगर_pm_ops,
	पूर्ण,
	.probe = tegra20_spdअगर_platक्रमm_probe,
	.हटाओ = tegra20_spdअगर_platक्रमm_हटाओ,
पूर्ण;

module_platक्रमm_driver(tegra20_spdअगर_driver);

MODULE_AUTHOR("Stephen Warren <swarren@nvidia.com>");
MODULE_DESCRIPTION("Tegra20 SPDIF ASoC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
