<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Rockchip PDM ALSA SoC Digital Audio Interface(DAI)  driver
 *
 * Copyright (C) 2017 Fuzhou Rockchip Electronics Co., Ltd
 */

#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/rational.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "rockchip_pdm.h"

#घोषणा PDM_DMA_BURST_SIZE	(8) /* size * width: 8*4 = 32 bytes */
#घोषणा PDM_SIGNOFF_CLK_RATE	(100000000)

क्रमागत rk_pdm_version अणु
	RK_PDM_RK3229,
	RK_PDM_RK3308,
पूर्ण;

काष्ठा rk_pdm_dev अणु
	काष्ठा device *dev;
	काष्ठा clk *clk;
	काष्ठा clk *hclk;
	काष्ठा regmap *regmap;
	काष्ठा snd_dmaengine_dai_dma_data capture_dma_data;
	काष्ठा reset_control *reset;
	क्रमागत rk_pdm_version version;
पूर्ण;

काष्ठा rk_pdm_clkref अणु
	अचिन्हित पूर्णांक sr;
	अचिन्हित पूर्णांक clk;
	अचिन्हित पूर्णांक clk_out;
पूर्ण;

काष्ठा rk_pdm_ds_ratio अणु
	अचिन्हित पूर्णांक ratio;
	अचिन्हित पूर्णांक sr;
पूर्ण;

अटल काष्ठा rk_pdm_clkref clkref[] = अणु
	अणु 8000, 40960000, 2048000 पूर्ण,
	अणु 11025, 56448000, 2822400 पूर्ण,
	अणु 12000, 61440000, 3072000 पूर्ण,
	अणु 8000, 98304000, 2048000 पूर्ण,
	अणु 12000, 98304000, 3072000 पूर्ण,
पूर्ण;

अटल काष्ठा rk_pdm_ds_ratio ds_ratio[] = अणु
	अणु 0, 192000 पूर्ण,
	अणु 0, 176400 पूर्ण,
	अणु 0, 128000 पूर्ण,
	अणु 1, 96000 पूर्ण,
	अणु 1, 88200 पूर्ण,
	अणु 1, 64000 पूर्ण,
	अणु 2, 48000 पूर्ण,
	अणु 2, 44100 पूर्ण,
	अणु 2, 32000 पूर्ण,
	अणु 3, 24000 पूर्ण,
	अणु 3, 22050 पूर्ण,
	अणु 3, 16000 पूर्ण,
	अणु 4, 12000 पूर्ण,
	अणु 4, 11025 पूर्ण,
	अणु 4, 8000 पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक get_pdm_clk(काष्ठा rk_pdm_dev *pdm, अचिन्हित पूर्णांक sr,
				अचिन्हित पूर्णांक *clk_src, अचिन्हित पूर्णांक *clk_out)
अणु
	अचिन्हित पूर्णांक i, count, clk, भाग, rate;

	clk = 0;
	अगर (!sr)
		वापस clk;

	count = ARRAY_SIZE(clkref);
	क्रम (i = 0; i < count; i++) अणु
		अगर (sr % clkref[i].sr)
			जारी;
		भाग = sr / clkref[i].sr;
		अगर ((भाग & (भाग - 1)) == 0) अणु
			*clk_out = clkref[i].clk_out;
			rate = clk_round_rate(pdm->clk, clkref[i].clk);
			अगर (rate != clkref[i].clk)
				जारी;
			clk = clkref[i].clk;
			*clk_src = clkref[i].clk;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!clk) अणु
		clk = clk_round_rate(pdm->clk, PDM_SIGNOFF_CLK_RATE);
		*clk_src = clk;
	पूर्ण
	वापस clk;
पूर्ण

अटल अचिन्हित पूर्णांक get_pdm_ds_ratio(अचिन्हित पूर्णांक sr)
अणु
	अचिन्हित पूर्णांक i, count, ratio;

	ratio = 0;
	अगर (!sr)
		वापस ratio;

	count = ARRAY_SIZE(ds_ratio);
	क्रम (i = 0; i < count; i++) अणु
		अगर (sr == ds_ratio[i].sr)
			ratio = ds_ratio[i].ratio;
	पूर्ण
	वापस ratio;
पूर्ण

अटल अंतरभूत काष्ठा rk_pdm_dev *to_info(काष्ठा snd_soc_dai *dai)
अणु
	वापस snd_soc_dai_get_drvdata(dai);
पूर्ण

अटल व्योम rockchip_pdm_rxctrl(काष्ठा rk_pdm_dev *pdm, पूर्णांक on)
अणु
	अगर (on) अणु
		regmap_update_bits(pdm->regmap, PDM_DMA_CTRL,
				   PDM_DMA_RD_MSK, PDM_DMA_RD_EN);
		regmap_update_bits(pdm->regmap, PDM_SYSCONFIG,
				   PDM_RX_MASK, PDM_RX_START);
	पूर्ण अन्यथा अणु
		regmap_update_bits(pdm->regmap, PDM_DMA_CTRL,
				   PDM_DMA_RD_MSK, PDM_DMA_RD_DIS);
		regmap_update_bits(pdm->regmap, PDM_SYSCONFIG,
				   PDM_RX_MASK | PDM_RX_CLR_MASK,
				   PDM_RX_STOP | PDM_RX_CLR_WR);
	पूर्ण
पूर्ण

अटल पूर्णांक rockchip_pdm_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rk_pdm_dev *pdm = to_info(dai);
	अचिन्हित पूर्णांक val = 0;
	अचिन्हित पूर्णांक clk_rate, clk_भाग, samplerate;
	अचिन्हित पूर्णांक clk_src, clk_out = 0;
	अचिन्हित दीर्घ m, n;
	bool change;
	पूर्णांक ret;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		वापस 0;

	samplerate = params_rate(params);
	clk_rate = get_pdm_clk(pdm, samplerate, &clk_src, &clk_out);
	अगर (!clk_rate)
		वापस -EINVAL;

	ret = clk_set_rate(pdm->clk, clk_src);
	अगर (ret)
		वापस -EINVAL;

	अगर (pdm->version == RK_PDM_RK3308) अणु
		rational_best_approximation(clk_out, clk_src,
					    GENMASK(16 - 1, 0),
					    GENMASK(16 - 1, 0),
					    &m, &n);

		val = (m << PDM_FD_NUMERATOR_SFT) |
			(n << PDM_FD_DENOMINATOR_SFT);
		regmap_update_bits_check(pdm->regmap, PDM_CTRL1,
					 PDM_FD_NUMERATOR_MSK |
					 PDM_FD_DENOMINATOR_MSK,
					 val, &change);
		अगर (change) अणु
			reset_control_निश्चित(pdm->reset);
			reset_control_deनिश्चित(pdm->reset);
			rockchip_pdm_rxctrl(pdm, 0);
		पूर्ण
		clk_भाग = n / m;
		अगर (clk_भाग >= 40)
			val = PDM_CLK_FD_RATIO_40;
		अन्यथा अगर (clk_भाग <= 35)
			val = PDM_CLK_FD_RATIO_35;
		अन्यथा
			वापस -EINVAL;
		regmap_update_bits(pdm->regmap, PDM_CLK_CTRL,
				   PDM_CLK_FD_RATIO_MSK,
				   val);
	पूर्ण
	val = get_pdm_ds_ratio(samplerate);
	regmap_update_bits(pdm->regmap, PDM_CLK_CTRL, PDM_DS_RATIO_MSK, val);
	regmap_update_bits(pdm->regmap, PDM_HPF_CTRL,
			   PDM_HPF_CF_MSK, PDM_HPF_60HZ);
	regmap_update_bits(pdm->regmap, PDM_HPF_CTRL,
			   PDM_HPF_LE | PDM_HPF_RE, PDM_HPF_LE | PDM_HPF_RE);
	regmap_update_bits(pdm->regmap, PDM_CLK_CTRL, PDM_CLK_EN, PDM_CLK_EN);
	अगर (pdm->version != RK_PDM_RK3229)
		regmap_update_bits(pdm->regmap, PDM_CTRL0,
				   PDM_MODE_MSK, PDM_MODE_LJ);

	val = 0;
	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S8:
		val |= PDM_VDW(8);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		val |= PDM_VDW(16);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S20_3LE:
		val |= PDM_VDW(20);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		val |= PDM_VDW(24);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		val |= PDM_VDW(32);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (params_channels(params)) अणु
	हाल 8:
		val |= PDM_PATH3_EN;
		fallthrough;
	हाल 6:
		val |= PDM_PATH2_EN;
		fallthrough;
	हाल 4:
		val |= PDM_PATH1_EN;
		fallthrough;
	हाल 2:
		val |= PDM_PATH0_EN;
		अवरोध;
	शेष:
		dev_err(pdm->dev, "invalid channel: %d\n",
			params_channels(params));
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(pdm->regmap, PDM_CTRL0,
			   PDM_PATH_MSK | PDM_VDW_MSK,
			   val);
	/* all channels share the single FIFO */
	regmap_update_bits(pdm->regmap, PDM_DMA_CTRL, PDM_DMA_RDL_MSK,
			   PDM_DMA_RDL(8 * params_channels(params)));

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pdm_set_fmt(काष्ठा snd_soc_dai *cpu_dai,
				अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा rk_pdm_dev *pdm = to_info(cpu_dai);
	अचिन्हित पूर्णांक mask = 0, val = 0;

	mask = PDM_CKP_MSK;
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		val = PDM_CKP_NORMAL;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		val = PDM_CKP_INVERTED;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	pm_runसमय_get_sync(cpu_dai->dev);
	regmap_update_bits(pdm->regmap, PDM_CLK_CTRL, mask, val);
	pm_runसमय_put(cpu_dai->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pdm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rk_pdm_dev *pdm = to_info(dai);
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			rockchip_pdm_rxctrl(pdm, 1);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			rockchip_pdm_rxctrl(pdm, 0);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_pdm_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा rk_pdm_dev *pdm = to_info(dai);

	dai->capture_dma_data = &pdm->capture_dma_data;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops rockchip_pdm_dai_ops = अणु
	.set_fmt = rockchip_pdm_set_fmt,
	.trigger = rockchip_pdm_trigger,
	.hw_params = rockchip_pdm_hw_params,
पूर्ण;

#घोषणा ROCKCHIP_PDM_RATES SNDRV_PCM_RATE_8000_192000
#घोषणा ROCKCHIP_PDM_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | \
			      SNDRV_PCM_FMTBIT_S20_3LE | \
			      SNDRV_PCM_FMTBIT_S24_LE | \
			      SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver rockchip_pdm_dai = अणु
	.probe = rockchip_pdm_dai_probe,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 8,
		.rates = ROCKCHIP_PDM_RATES,
		.क्रमmats = ROCKCHIP_PDM_FORMATS,
	पूर्ण,
	.ops = &rockchip_pdm_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver rockchip_pdm_component = अणु
	.name = "rockchip-pdm",
पूर्ण;

अटल पूर्णांक rockchip_pdm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा rk_pdm_dev *pdm = dev_get_drvdata(dev);

	clk_disable_unprepare(pdm->clk);
	clk_disable_unprepare(pdm->hclk);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pdm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा rk_pdm_dev *pdm = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(pdm->clk);
	अगर (ret) अणु
		dev_err(pdm->dev, "clock enable failed %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(pdm->hclk);
	अगर (ret) अणु
		dev_err(pdm->dev, "hclock enable failed %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool rockchip_pdm_wr_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल PDM_SYSCONFIG:
	हाल PDM_CTRL0:
	हाल PDM_CTRL1:
	हाल PDM_CLK_CTRL:
	हाल PDM_HPF_CTRL:
	हाल PDM_FIFO_CTRL:
	हाल PDM_DMA_CTRL:
	हाल PDM_INT_EN:
	हाल PDM_INT_CLR:
	हाल PDM_DATA_VALID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rockchip_pdm_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल PDM_SYSCONFIG:
	हाल PDM_CTRL0:
	हाल PDM_CTRL1:
	हाल PDM_CLK_CTRL:
	हाल PDM_HPF_CTRL:
	हाल PDM_FIFO_CTRL:
	हाल PDM_DMA_CTRL:
	हाल PDM_INT_EN:
	हाल PDM_INT_CLR:
	हाल PDM_INT_ST:
	हाल PDM_DATA_VALID:
	हाल PDM_RXFIFO_DATA:
	हाल PDM_VERSION:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rockchip_pdm_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल PDM_SYSCONFIG:
	हाल PDM_FIFO_CTRL:
	हाल PDM_INT_CLR:
	हाल PDM_INT_ST:
	हाल PDM_RXFIFO_DATA:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool rockchip_pdm_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल PDM_RXFIFO_DATA:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा reg_शेष rockchip_pdm_reg_शेषs[] = अणु
	अणु0x04, 0x78000017पूर्ण,
	अणु0x08, 0x0bb8ea60पूर्ण,
	अणु0x18, 0x0000001fपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rockchip_pdm_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = PDM_VERSION,
	.reg_शेषs = rockchip_pdm_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(rockchip_pdm_reg_शेषs),
	.ग_लिखोable_reg = rockchip_pdm_wr_reg,
	.पढ़ोable_reg = rockchip_pdm_rd_reg,
	.अस्थिर_reg = rockchip_pdm_अस्थिर_reg,
	.precious_reg = rockchip_pdm_precious_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_pdm_match[] __maybe_unused = अणु
	अणु .compatible = "rockchip,pdm",
	  .data = (व्योम *)RK_PDM_RK3229 पूर्ण,
	अणु .compatible = "rockchip,px30-pdm",
	  .data = (व्योम *)RK_PDM_RK3308 पूर्ण,
	अणु .compatible = "rockchip,rk1808-pdm",
	  .data = (व्योम *)RK_PDM_RK3308 पूर्ण,
	अणु .compatible = "rockchip,rk3308-pdm",
	  .data = (व्योम *)RK_PDM_RK3308 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rockchip_pdm_match);

अटल पूर्णांक rockchip_pdm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा rk_pdm_dev *pdm;
	काष्ठा resource *res;
	व्योम __iomem *regs;
	पूर्णांक ret;

	pdm = devm_kzalloc(&pdev->dev, माप(*pdm), GFP_KERNEL);
	अगर (!pdm)
		वापस -ENOMEM;

	match = of_match_device(rockchip_pdm_match, &pdev->dev);
	अगर (match)
		pdm->version = (क्रमागत rk_pdm_version)match->data;

	अगर (pdm->version == RK_PDM_RK3308) अणु
		pdm->reset = devm_reset_control_get(&pdev->dev, "pdm-m");
		अगर (IS_ERR(pdm->reset))
			वापस PTR_ERR(pdm->reset);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	pdm->regmap = devm_regmap_init_mmio(&pdev->dev, regs,
					    &rockchip_pdm_regmap_config);
	अगर (IS_ERR(pdm->regmap))
		वापस PTR_ERR(pdm->regmap);

	pdm->capture_dma_data.addr = res->start + PDM_RXFIFO_DATA;
	pdm->capture_dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	pdm->capture_dma_data.maxburst = PDM_DMA_BURST_SIZE;

	pdm->dev = &pdev->dev;
	dev_set_drvdata(&pdev->dev, pdm);

	pdm->clk = devm_clk_get(&pdev->dev, "pdm_clk");
	अगर (IS_ERR(pdm->clk))
		वापस PTR_ERR(pdm->clk);

	pdm->hclk = devm_clk_get(&pdev->dev, "pdm_hclk");
	अगर (IS_ERR(pdm->hclk))
		वापस PTR_ERR(pdm->hclk);

	ret = clk_prepare_enable(pdm->hclk);
	अगर (ret)
		वापस ret;

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = rockchip_pdm_runसमय_resume(&pdev->dev);
		अगर (ret)
			जाओ err_pm_disable;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &rockchip_pdm_component,
					      &rockchip_pdm_dai, 1);

	अगर (ret) अणु
		dev_err(&pdev->dev, "could not register dai: %d\n", ret);
		जाओ err_suspend;
	पूर्ण

	rockchip_pdm_rxctrl(pdm, 0);
	ret = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य, 0);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not register pcm: %d\n", ret);
		जाओ err_suspend;
	पूर्ण

	वापस 0;

err_suspend:
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		rockchip_pdm_runसमय_suspend(&pdev->dev);
err_pm_disable:
	pm_runसमय_disable(&pdev->dev);

	clk_disable_unprepare(pdm->hclk);

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_pdm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rk_pdm_dev *pdm = dev_get_drvdata(&pdev->dev);

	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		rockchip_pdm_runसमय_suspend(&pdev->dev);

	clk_disable_unprepare(pdm->clk);
	clk_disable_unprepare(pdm->hclk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rockchip_pdm_suspend(काष्ठा device *dev)
अणु
	काष्ठा rk_pdm_dev *pdm = dev_get_drvdata(dev);

	regcache_mark_dirty(pdm->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pdm_resume(काष्ठा device *dev)
अणु
	काष्ठा rk_pdm_dev *pdm = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put(dev);
		वापस ret;
	पूर्ण

	ret = regcache_sync(pdm->regmap);

	pm_runसमय_put(dev);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops rockchip_pdm_pm_ops = अणु
	SET_RUNTIME_PM_OPS(rockchip_pdm_runसमय_suspend,
			   rockchip_pdm_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(rockchip_pdm_suspend, rockchip_pdm_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver rockchip_pdm_driver = अणु
	.probe  = rockchip_pdm_probe,
	.हटाओ = rockchip_pdm_हटाओ,
	.driver = अणु
		.name = "rockchip-pdm",
		.of_match_table = of_match_ptr(rockchip_pdm_match),
		.pm = &rockchip_pdm_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rockchip_pdm_driver);

MODULE_AUTHOR("Sugar <sugar.zhang@rock-chips.com>");
MODULE_DESCRIPTION("Rockchip PDM Controller Driver");
MODULE_LICENSE("GPL v2");
