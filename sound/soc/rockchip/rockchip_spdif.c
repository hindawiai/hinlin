<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* sound/soc/rockchip/rk_spdअगर.c
 *
 * ALSA SoC Audio Layer - Rockchip I2S Controller driver
 *
 * Copyright (c) 2014 Rockchip Electronics Co. Ltd.
 * Author: Jianqun <jay.xu@rock-chips.com>
 * Copyright (c) 2015 Collabora Ltd.
 * Author: Sjoerd Simons <sjoerd.simons@collabora.co.uk>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/clk.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "rockchip_spdif.h"

क्रमागत rk_spdअगर_type अणु
	RK_SPDIF_RK3066,
	RK_SPDIF_RK3188,
	RK_SPDIF_RK3288,
	RK_SPDIF_RK3366,
पूर्ण;

#घोषणा RK3288_GRF_SOC_CON2 0x24c

काष्ठा rk_spdअगर_dev अणु
	काष्ठा device *dev;

	काष्ठा clk *mclk;
	काष्ठा clk *hclk;

	काष्ठा snd_dmaengine_dai_dma_data playback_dma_data;

	काष्ठा regmap *regmap;
पूर्ण;

अटल स्थिर काष्ठा of_device_id rk_spdअगर_match[] __maybe_unused = अणु
	अणु .compatible = "rockchip,rk3066-spdif",
	  .data = (व्योम *)RK_SPDIF_RK3066 पूर्ण,
	अणु .compatible = "rockchip,rk3188-spdif",
	  .data = (व्योम *)RK_SPDIF_RK3188 पूर्ण,
	अणु .compatible = "rockchip,rk3228-spdif",
	  .data = (व्योम *)RK_SPDIF_RK3366 पूर्ण,
	अणु .compatible = "rockchip,rk3288-spdif",
	  .data = (व्योम *)RK_SPDIF_RK3288 पूर्ण,
	अणु .compatible = "rockchip,rk3328-spdif",
	  .data = (व्योम *)RK_SPDIF_RK3366 पूर्ण,
	अणु .compatible = "rockchip,rk3366-spdif",
	  .data = (व्योम *)RK_SPDIF_RK3366 पूर्ण,
	अणु .compatible = "rockchip,rk3368-spdif",
	  .data = (व्योम *)RK_SPDIF_RK3366 पूर्ण,
	अणु .compatible = "rockchip,rk3399-spdif",
	  .data = (व्योम *)RK_SPDIF_RK3366 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rk_spdअगर_match);

अटल पूर्णांक __maybe_unused rk_spdअगर_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा rk_spdअगर_dev *spdअगर = dev_get_drvdata(dev);

	regcache_cache_only(spdअगर->regmap, true);
	clk_disable_unprepare(spdअगर->mclk);
	clk_disable_unprepare(spdअगर->hclk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rk_spdअगर_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा rk_spdअगर_dev *spdअगर = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(spdअगर->mclk);
	अगर (ret) अणु
		dev_err(spdअगर->dev, "mclk clock enable failed %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(spdअगर->hclk);
	अगर (ret) अणु
		dev_err(spdअगर->dev, "hclk clock enable failed %d\n", ret);
		वापस ret;
	पूर्ण

	regcache_cache_only(spdअगर->regmap, false);
	regcache_mark_dirty(spdअगर->regmap);

	ret = regcache_sync(spdअगर->regmap);
	अगर (ret) अणु
		clk_disable_unprepare(spdअगर->mclk);
		clk_disable_unprepare(spdअगर->hclk);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rk_spdअगर_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rk_spdअगर_dev *spdअगर = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक val = SPDIF_CFGR_HALFWORD_ENABLE;
	पूर्णांक srate, mclk;
	पूर्णांक ret;

	srate = params_rate(params);
	mclk = srate * 128;

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		val |= SPDIF_CFGR_VDW_16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S20_3LE:
		val |= SPDIF_CFGR_VDW_20;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		val |= SPDIF_CFGR_VDW_24;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Set घड़ी and calculate भागider */
	ret = clk_set_rate(spdअगर->mclk, mclk);
	अगर (ret != 0) अणु
		dev_err(spdअगर->dev, "Failed to set module clock rate: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(spdअगर->regmap, SPDIF_CFGR,
		SPDIF_CFGR_CLK_DIV_MASK | SPDIF_CFGR_HALFWORD_ENABLE |
		SDPIF_CFGR_VDW_MASK,
		val);

	वापस ret;
पूर्ण

अटल पूर्णांक rk_spdअगर_trigger(काष्ठा snd_pcm_substream *substream,
				पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rk_spdअगर_dev *spdअगर = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ret = regmap_update_bits(spdअगर->regmap, SPDIF_DMACR,
				   SPDIF_DMACR_TDE_ENABLE |
				   SPDIF_DMACR_TDL_MASK,
				   SPDIF_DMACR_TDE_ENABLE |
				   SPDIF_DMACR_TDL(16));

		अगर (ret != 0)
			वापस ret;

		ret = regmap_update_bits(spdअगर->regmap, SPDIF_XFER,
				   SPDIF_XFER_TXS_START,
				   SPDIF_XFER_TXS_START);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ret = regmap_update_bits(spdअगर->regmap, SPDIF_DMACR,
				   SPDIF_DMACR_TDE_ENABLE,
				   SPDIF_DMACR_TDE_DISABLE);

		अगर (ret != 0)
			वापस ret;

		ret = regmap_update_bits(spdअगर->regmap, SPDIF_XFER,
				   SPDIF_XFER_TXS_START,
				   SPDIF_XFER_TXS_STOP);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rk_spdअगर_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rk_spdअगर_dev *spdअगर = snd_soc_dai_get_drvdata(dai);

	dai->playback_dma_data = &spdअगर->playback_dma_data;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops rk_spdअगर_dai_ops = अणु
	.hw_params = rk_spdअगर_hw_params,
	.trigger = rk_spdअगर_trigger,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rk_spdअगर_dai = अणु
	.probe = rk_spdअगर_dai_probe,
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = (SNDRV_PCM_RATE_32000 |
			  SNDRV_PCM_RATE_44100 |
			  SNDRV_PCM_RATE_48000 |
			  SNDRV_PCM_RATE_96000 |
			  SNDRV_PCM_RATE_192000),
		.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE |
			    SNDRV_PCM_FMTBIT_S20_3LE |
			    SNDRV_PCM_FMTBIT_S24_LE),
	पूर्ण,
	.ops = &rk_spdअगर_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver rk_spdअगर_component = अणु
	.name = "rockchip-spdif",
पूर्ण;

अटल bool rk_spdअगर_wr_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SPDIF_CFGR:
	हाल SPDIF_DMACR:
	हाल SPDIF_INTCR:
	हाल SPDIF_XFER:
	हाल SPDIF_SMPDR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rk_spdअगर_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SPDIF_CFGR:
	हाल SPDIF_SDBLR:
	हाल SPDIF_INTCR:
	हाल SPDIF_INTSR:
	हाल SPDIF_XFER:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rk_spdअगर_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SPDIF_INTSR:
	हाल SPDIF_SDBLR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config rk_spdअगर_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = SPDIF_SMPDR,
	.ग_लिखोable_reg = rk_spdअगर_wr_reg,
	.पढ़ोable_reg = rk_spdअगर_rd_reg,
	.अस्थिर_reg = rk_spdअगर_अस्थिर_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक rk_spdअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा rk_spdअगर_dev *spdअगर;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा resource *res;
	व्योम __iomem *regs;
	पूर्णांक ret;

	match = of_match_node(rk_spdअगर_match, np);
	अगर (match->data == (व्योम *)RK_SPDIF_RK3288) अणु
		काष्ठा regmap *grf;

		grf = syscon_regmap_lookup_by_phandle(np, "rockchip,grf");
		अगर (IS_ERR(grf)) अणु
			dev_err(&pdev->dev,
				"rockchip_spdif missing 'rockchip,grf' \n");
			वापस PTR_ERR(grf);
		पूर्ण

		/* Select the 8 channel SPDIF solution on RK3288 as
		 * the 2 channel one करोes not appear to work
		 */
		regmap_ग_लिखो(grf, RK3288_GRF_SOC_CON2, BIT(1) << 16);
	पूर्ण

	spdअगर = devm_kzalloc(&pdev->dev, माप(*spdअगर), GFP_KERNEL);
	अगर (!spdअगर)
		वापस -ENOMEM;

	spdअगर->hclk = devm_clk_get(&pdev->dev, "hclk");
	अगर (IS_ERR(spdअगर->hclk))
		वापस PTR_ERR(spdअगर->hclk);

	spdअगर->mclk = devm_clk_get(&pdev->dev, "mclk");
	अगर (IS_ERR(spdअगर->mclk))
		वापस PTR_ERR(spdअगर->mclk);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	spdअगर->regmap = devm_regmap_init_mmio_clk(&pdev->dev, "hclk", regs,
						  &rk_spdअगर_regmap_config);
	अगर (IS_ERR(spdअगर->regmap))
		वापस PTR_ERR(spdअगर->regmap);

	spdअगर->playback_dma_data.addr = res->start + SPDIF_SMPDR;
	spdअगर->playback_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	spdअगर->playback_dma_data.maxburst = 4;

	spdअगर->dev = &pdev->dev;
	dev_set_drvdata(&pdev->dev, spdअगर);

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = rk_spdअगर_runसमय_resume(&pdev->dev);
		अगर (ret)
			जाओ err_pm_runसमय;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &rk_spdअगर_component,
					      &rk_spdअगर_dai, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not register DAI\n");
		जाओ err_pm_suspend;
	पूर्ण

	ret = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य, 0);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not register PCM\n");
		जाओ err_pm_suspend;
	पूर्ण

	वापस 0;

err_pm_suspend:
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		rk_spdअगर_runसमय_suspend(&pdev->dev);
err_pm_runसमय:
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक rk_spdअगर_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		rk_spdअगर_runसमय_suspend(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rk_spdअगर_pm_ops = अणु
	SET_RUNTIME_PM_OPS(rk_spdअगर_runसमय_suspend, rk_spdअगर_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver rk_spdअगर_driver = अणु
	.probe = rk_spdअगर_probe,
	.हटाओ = rk_spdअगर_हटाओ,
	.driver = अणु
		.name = "rockchip-spdif",
		.of_match_table = of_match_ptr(rk_spdअगर_match),
		.pm = &rk_spdअगर_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rk_spdअगर_driver);

MODULE_ALIAS("platform:rockchip-spdif");
MODULE_DESCRIPTION("ROCKCHIP SPDIF transceiver Interface");
MODULE_AUTHOR("Sjoerd Simons <sjoerd.simons@collabora.co.uk>");
MODULE_LICENSE("GPL v2");
