<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
//
// Copyright (c) 2018 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>
#समावेश <sound/pcm_params.h>

#घोषणा PDM_CTRL			0x00
#घोषणा  PDM_CTRL_EN			BIT(31)
#घोषणा  PDM_CTRL_OUT_MODE		BIT(29)
#घोषणा  PDM_CTRL_BYPASS_MODE		BIT(28)
#घोषणा  PDM_CTRL_RST_FIFO		BIT(16)
#घोषणा  PDM_CTRL_CHAN_RSTN_MASK	GENMASK(15, 8)
#घोषणा  PDM_CTRL_CHAN_RSTN(x)		((x) << 8)
#घोषणा  PDM_CTRL_CHAN_EN_MASK		GENMASK(7, 0)
#घोषणा  PDM_CTRL_CHAN_EN(x)		((x) << 0)
#घोषणा PDM_HCIC_CTRL1			0x04
#घोषणा  PDM_FILTER_EN			BIT(31)
#घोषणा  PDM_HCIC_CTRL1_GAIN_SFT_MASK	GENMASK(29, 24)
#घोषणा  PDM_HCIC_CTRL1_GAIN_SFT(x)	((x) << 24)
#घोषणा  PDM_HCIC_CTRL1_GAIN_MULT_MASK	GENMASK(23, 16)
#घोषणा  PDM_HCIC_CTRL1_GAIN_MULT(x)	((x) << 16)
#घोषणा  PDM_HCIC_CTRL1_DSR_MASK	GENMASK(8, 4)
#घोषणा  PDM_HCIC_CTRL1_DSR(x)		((x) << 4)
#घोषणा  PDM_HCIC_CTRL1_STAGE_NUM_MASK	GENMASK(3, 0)
#घोषणा  PDM_HCIC_CTRL1_STAGE_NUM(x)	((x) << 0)
#घोषणा PDM_HCIC_CTRL2			0x08
#घोषणा PDM_F1_CTRL			0x0c
#घोषणा  PDM_LPF_ROUND_MODE_MASK	GENMASK(17, 16)
#घोषणा  PDM_LPF_ROUND_MODE(x)		((x) << 16)
#घोषणा  PDM_LPF_DSR_MASK		GENMASK(15, 12)
#घोषणा  PDM_LPF_DSR(x)			((x) << 12)
#घोषणा  PDM_LPF_STAGE_NUM_MASK		GENMASK(8, 0)
#घोषणा  PDM_LPF_STAGE_NUM(x)		((x) << 0)
#घोषणा  PDM_LPF_MAX_STAGE		336
#घोषणा  PDM_LPF_NUM			3
#घोषणा PDM_F2_CTRL			0x10
#घोषणा PDM_F3_CTRL			0x14
#घोषणा PDM_HPF_CTRL			0x18
#घोषणा  PDM_HPF_SFT_STEPS_MASK		GENMASK(20, 16)
#घोषणा  PDM_HPF_SFT_STEPS(x)		((x) << 16)
#घोषणा  PDM_HPF_OUT_FACTOR_MASK	GENMASK(15, 0)
#घोषणा  PDM_HPF_OUT_FACTOR(x)		((x) << 0)
#घोषणा PDM_CHAN_CTRL			0x1c
#घोषणा  PDM_CHAN_CTRL_POINTER_WIDTH	8
#घोषणा  PDM_CHAN_CTRL_POINTER_MAX	((1 << PDM_CHAN_CTRL_POINTER_WIDTH) - 1)
#घोषणा  PDM_CHAN_CTRL_NUM		4
#घोषणा PDM_CHAN_CTRL1			0x20
#घोषणा PDM_COEFF_ADDR			0x24
#घोषणा PDM_COEFF_DATA			0x28
#घोषणा PDM_CLKG_CTRL			0x2c
#घोषणा PDM_STS				0x30

काष्ठा axg_pdm_lpf अणु
	अचिन्हित पूर्णांक ds;
	अचिन्हित पूर्णांक round_mode;
	स्थिर अचिन्हित पूर्णांक *tap;
	अचिन्हित पूर्णांक tap_num;
पूर्ण;

काष्ठा axg_pdm_hcic अणु
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक mult;
	अचिन्हित पूर्णांक steps;
	अचिन्हित पूर्णांक ds;
पूर्ण;

काष्ठा axg_pdm_hpf अणु
	अचिन्हित पूर्णांक out_factor;
	अचिन्हित पूर्णांक steps;
पूर्ण;

काष्ठा axg_pdm_filters अणु
	काष्ठा axg_pdm_hcic hcic;
	काष्ठा axg_pdm_hpf hpf;
	काष्ठा axg_pdm_lpf lpf[PDM_LPF_NUM];
पूर्ण;

काष्ठा axg_pdm_cfg अणु
	स्थिर काष्ठा axg_pdm_filters *filters;
	अचिन्हित पूर्णांक sys_rate;
पूर्ण;

काष्ठा axg_pdm अणु
	स्थिर काष्ठा axg_pdm_cfg *cfg;
	काष्ठा regmap *map;
	काष्ठा clk *dclk;
	काष्ठा clk *sysclk;
	काष्ठा clk *pclk;
पूर्ण;

अटल व्योम axg_pdm_enable(काष्ठा regmap *map)
अणु
	/* Reset AFIFO */
	regmap_update_bits(map, PDM_CTRL, PDM_CTRL_RST_FIFO, PDM_CTRL_RST_FIFO);
	regmap_update_bits(map, PDM_CTRL, PDM_CTRL_RST_FIFO, 0);

	/* Enable PDM */
	regmap_update_bits(map, PDM_CTRL, PDM_CTRL_EN, PDM_CTRL_EN);
पूर्ण

अटल व्योम axg_pdm_disable(काष्ठा regmap *map)
अणु
	regmap_update_bits(map, PDM_CTRL, PDM_CTRL_EN, 0);
पूर्ण

अटल व्योम axg_pdm_filters_enable(काष्ठा regmap *map, bool enable)
अणु
	अचिन्हित पूर्णांक val = enable ? PDM_FILTER_EN : 0;

	regmap_update_bits(map, PDM_HCIC_CTRL1, PDM_FILTER_EN, val);
	regmap_update_bits(map, PDM_F1_CTRL, PDM_FILTER_EN, val);
	regmap_update_bits(map, PDM_F2_CTRL, PDM_FILTER_EN, val);
	regmap_update_bits(map, PDM_F3_CTRL, PDM_FILTER_EN, val);
	regmap_update_bits(map, PDM_HPF_CTRL, PDM_FILTER_EN, val);
पूर्ण

अटल पूर्णांक axg_pdm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_pdm *priv = snd_soc_dai_get_drvdata(dai);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		axg_pdm_enable(priv->map);
		वापस 0;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		axg_pdm_disable(priv->map);
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक axg_pdm_get_os(काष्ठा axg_pdm *priv)
अणु
	स्थिर काष्ठा axg_pdm_filters *filters = priv->cfg->filters;
	अचिन्हित पूर्णांक os = filters->hcic.ds;
	पूर्णांक i;

	/*
	 * The global oversampling factor is defined by the करोwn sampling
	 * factor applied by each filter (HCIC and LPFs)
	 */

	क्रम (i = 0; i < PDM_LPF_NUM; i++)
		os *= filters->lpf[i].ds;

	वापस os;
पूर्ण

अटल पूर्णांक axg_pdm_set_sysclk(काष्ठा axg_pdm *priv, अचिन्हित पूर्णांक os,
			      अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक sys_rate = os * 2 * rate * PDM_CHAN_CTRL_POINTER_MAX;

	/*
	 * Set the शेष प्रणाली घड़ी rate unless it is too fast क्रम
	 * क्रम the requested sample rate. In this हाल, the sample poपूर्णांकer
	 * counter could overflow so set a lower प्रणाली घड़ी rate
	 */
	अगर (sys_rate < priv->cfg->sys_rate)
		वापस clk_set_rate(priv->sysclk, sys_rate);

	वापस clk_set_rate(priv->sysclk, priv->cfg->sys_rate);
पूर्ण

अटल पूर्णांक axg_pdm_set_sample_poपूर्णांकer(काष्ठा axg_pdm *priv)
अणु
	अचिन्हित पूर्णांक spmax, sp, val;
	पूर्णांक i;

	/* Max sample counter value per half period of dclk */
	spmax = DIV_ROUND_UP_ULL((u64)clk_get_rate(priv->sysclk),
				 clk_get_rate(priv->dclk) * 2);

	/* Check अगर sysclk is not too fast - should not happen */
	अगर (WARN_ON(spmax > PDM_CHAN_CTRL_POINTER_MAX))
		वापस -EINVAL;

	/* Capture the data when we are at 75% of the half period */
	sp = spmax * 3 / 4;

	क्रम (i = 0, val = 0; i < PDM_CHAN_CTRL_NUM; i++)
		val |= sp << (PDM_CHAN_CTRL_POINTER_WIDTH * i);

	regmap_ग_लिखो(priv->map, PDM_CHAN_CTRL, val);
	regmap_ग_लिखो(priv->map, PDM_CHAN_CTRL1, val);

	वापस 0;
पूर्ण

अटल व्योम axg_pdm_set_channel_mask(काष्ठा axg_pdm *priv,
				     अचिन्हित पूर्णांक channels)
अणु
	अचिन्हित पूर्णांक mask = GENMASK(channels - 1, 0);

	/* Put all channel in reset */
	regmap_update_bits(priv->map, PDM_CTRL,
			   PDM_CTRL_CHAN_RSTN_MASK, 0);

	/* Take the necessary channels out of reset and enable them */
	regmap_update_bits(priv->map, PDM_CTRL,
			   PDM_CTRL_CHAN_RSTN_MASK |
			   PDM_CTRL_CHAN_EN_MASK,
			   PDM_CTRL_CHAN_RSTN(mask) |
			   PDM_CTRL_CHAN_EN(mask));
पूर्ण

अटल पूर्णांक axg_pdm_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_pdm *priv = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक os = axg_pdm_get_os(priv);
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	चयन (params_width(params)) अणु
	हाल 24:
		val = PDM_CTRL_OUT_MODE;
		अवरोध;
	हाल 32:
		val = 0;
		अवरोध;
	शेष:
		dev_err(dai->dev, "unsupported sample width\n");
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(priv->map, PDM_CTRL, PDM_CTRL_OUT_MODE, val);

	ret = axg_pdm_set_sysclk(priv, os, rate);
	अगर (ret) अणु
		dev_err(dai->dev, "failed to set system clock\n");
		वापस ret;
	पूर्ण

	ret = clk_set_rate(priv->dclk, rate * os);
	अगर (ret) अणु
		dev_err(dai->dev, "failed to set dclk\n");
		वापस ret;
	पूर्ण

	ret = axg_pdm_set_sample_poपूर्णांकer(priv);
	अगर (ret) अणु
		dev_err(dai->dev, "invalid clock setting\n");
		वापस ret;
	पूर्ण

	axg_pdm_set_channel_mask(priv, params_channels(params));

	वापस 0;
पूर्ण

अटल पूर्णांक axg_pdm_startup(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_pdm *priv = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->dclk);
	अगर (ret) अणु
		dev_err(dai->dev, "enabling dclk failed\n");
		वापस ret;
	पूर्ण

	/* Enable the filters */
	axg_pdm_filters_enable(priv->map, true);

	वापस ret;
पूर्ण

अटल व्योम axg_pdm_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_pdm *priv = snd_soc_dai_get_drvdata(dai);

	axg_pdm_filters_enable(priv->map, false);
	clk_disable_unprepare(priv->dclk);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops axg_pdm_dai_ops = अणु
	.trigger	= axg_pdm_trigger,
	.hw_params	= axg_pdm_hw_params,
	.startup	= axg_pdm_startup,
	.shutकरोwn	= axg_pdm_shutकरोwn,
पूर्ण;

अटल व्योम axg_pdm_set_hcic_ctrl(काष्ठा axg_pdm *priv)
अणु
	स्थिर काष्ठा axg_pdm_hcic *hcic = &priv->cfg->filters->hcic;
	अचिन्हित पूर्णांक val;

	val = PDM_HCIC_CTRL1_STAGE_NUM(hcic->steps);
	val |= PDM_HCIC_CTRL1_DSR(hcic->ds);
	val |= PDM_HCIC_CTRL1_GAIN_MULT(hcic->mult);
	val |= PDM_HCIC_CTRL1_GAIN_SFT(hcic->shअगरt);

	regmap_update_bits(priv->map, PDM_HCIC_CTRL1,
			   PDM_HCIC_CTRL1_STAGE_NUM_MASK |
			   PDM_HCIC_CTRL1_DSR_MASK |
			   PDM_HCIC_CTRL1_GAIN_MULT_MASK |
			   PDM_HCIC_CTRL1_GAIN_SFT_MASK,
			   val);
पूर्ण

अटल व्योम axg_pdm_set_lpf_ctrl(काष्ठा axg_pdm *priv, अचिन्हित पूर्णांक index)
अणु
	स्थिर काष्ठा axg_pdm_lpf *lpf = &priv->cfg->filters->lpf[index];
	अचिन्हित पूर्णांक offset = index * regmap_get_reg_stride(priv->map)
		+ PDM_F1_CTRL;
	अचिन्हित पूर्णांक val;

	val = PDM_LPF_STAGE_NUM(lpf->tap_num);
	val |= PDM_LPF_DSR(lpf->ds);
	val |= PDM_LPF_ROUND_MODE(lpf->round_mode);

	regmap_update_bits(priv->map, offset,
			   PDM_LPF_STAGE_NUM_MASK |
			   PDM_LPF_DSR_MASK |
			   PDM_LPF_ROUND_MODE_MASK,
			   val);
पूर्ण

अटल व्योम axg_pdm_set_hpf_ctrl(काष्ठा axg_pdm *priv)
अणु
	स्थिर काष्ठा axg_pdm_hpf *hpf = &priv->cfg->filters->hpf;
	अचिन्हित पूर्णांक val;

	val = PDM_HPF_OUT_FACTOR(hpf->out_factor);
	val |= PDM_HPF_SFT_STEPS(hpf->steps);

	regmap_update_bits(priv->map, PDM_HPF_CTRL,
			   PDM_HPF_OUT_FACTOR_MASK |
			   PDM_HPF_SFT_STEPS_MASK,
			   val);
पूर्ण

अटल पूर्णांक axg_pdm_set_lpf_filters(काष्ठा axg_pdm *priv)
अणु
	स्थिर काष्ठा axg_pdm_lpf *lpf = priv->cfg->filters->lpf;
	अचिन्हित पूर्णांक count = 0;
	पूर्णांक i, j;

	क्रम (i = 0; i < PDM_LPF_NUM; i++)
		count += lpf[i].tap_num;

	/* Make sure the coeffs fit in the memory */
	अगर (count >= PDM_LPF_MAX_STAGE)
		वापस -EINVAL;

	/* Set the initial APB bus रेजिस्टर address */
	regmap_ग_लिखो(priv->map, PDM_COEFF_ADDR, 0);

	/* Set the tap filter values of all 3 filters */
	क्रम (i = 0; i < PDM_LPF_NUM; i++) अणु
		axg_pdm_set_lpf_ctrl(priv, i);

		क्रम (j = 0; j < lpf[i].tap_num; j++)
			regmap_ग_लिखो(priv->map, PDM_COEFF_DATA, lpf[i].tap[j]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axg_pdm_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_pdm *priv = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->pclk);
	अगर (ret) अणु
		dev_err(dai->dev, "enabling pclk failed\n");
		वापस ret;
	पूर्ण

	/*
	 * sysclk must be set and enabled as well to access the pdm रेजिस्टरs
	 * Accessing the रेजिस्टर w/o it will give a bus error.
	 */
	ret = clk_set_rate(priv->sysclk, priv->cfg->sys_rate);
	अगर (ret) अणु
		dev_err(dai->dev, "setting sysclk failed\n");
		जाओ err_pclk;
	पूर्ण

	ret = clk_prepare_enable(priv->sysclk);
	अगर (ret) अणु
		dev_err(dai->dev, "enabling sysclk failed\n");
		जाओ err_pclk;
	पूर्ण

	/* Make sure the device is initially disabled */
	axg_pdm_disable(priv->map);

	/* Make sure filter bypass is disabled */
	regmap_update_bits(priv->map, PDM_CTRL, PDM_CTRL_BYPASS_MODE, 0);

	/* Load filter settings */
	axg_pdm_set_hcic_ctrl(priv);
	axg_pdm_set_hpf_ctrl(priv);

	ret = axg_pdm_set_lpf_filters(priv);
	अगर (ret) अणु
		dev_err(dai->dev, "invalid filter configuration\n");
		जाओ err_sysclk;
	पूर्ण

	वापस 0;

err_sysclk:
	clk_disable_unprepare(priv->sysclk);
err_pclk:
	clk_disable_unprepare(priv->pclk);
	वापस ret;
पूर्ण

अटल पूर्णांक axg_pdm_dai_हटाओ(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_pdm *priv = snd_soc_dai_get_drvdata(dai);

	clk_disable_unprepare(priv->sysclk);
	clk_disable_unprepare(priv->pclk);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver axg_pdm_dai_drv = अणु
	.name = "PDM",
	.capture = अणु
		.stream_name	= "Capture",
		.channels_min	= 1,
		.channels_max	= 8,
		.rates		= SNDRV_PCM_RATE_CONTINUOUS,
		.rate_min	= 5512,
		.rate_max	= 48000,
		.क्रमmats	= (SNDRV_PCM_FMTBIT_S24_LE |
				   SNDRV_PCM_FMTBIT_S32_LE),
	पूर्ण,
	.ops		= &axg_pdm_dai_ops,
	.probe		= axg_pdm_dai_probe,
	.हटाओ		= axg_pdm_dai_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver axg_pdm_component_drv = अणुपूर्ण;

अटल स्थिर काष्ठा regmap_config axg_pdm_regmap_cfg = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= PDM_STS,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lpf1_शेष_tap[] = अणु
	0x000014, 0xffffb2, 0xfffed9, 0xfffdce, 0xfffd45,
	0xfffe32, 0x000147, 0x000645, 0x000b86, 0x000e21,
	0x000ae3, 0x000000, 0xffeece, 0xffdca8, 0xffd212,
	0xffd7d1, 0xfff2a7, 0x001f4c, 0x0050c2, 0x0072aa,
	0x006ff1, 0x003c32, 0xffdc4e, 0xff6a18, 0xff0fef,
	0xfefbaf, 0xff4c40, 0x000000, 0x00ebc8, 0x01c077,
	0x02209e, 0x01c1a4, 0x008e60, 0xfebe52, 0xfcd690,
	0xfb8fa5, 0xfba498, 0xfd9812, 0x0181ce, 0x06f5f3,
	0x0d112f, 0x12a958, 0x169686, 0x18000e, 0x169686,
	0x12a958, 0x0d112f, 0x06f5f3, 0x0181ce, 0xfd9812,
	0xfba498, 0xfb8fa5, 0xfcd690, 0xfebe52, 0x008e60,
	0x01c1a4, 0x02209e, 0x01c077, 0x00ebc8, 0x000000,
	0xff4c40, 0xfefbaf, 0xff0fef, 0xff6a18, 0xffdc4e,
	0x003c32, 0x006ff1, 0x0072aa, 0x0050c2, 0x001f4c,
	0xfff2a7, 0xffd7d1, 0xffd212, 0xffdca8, 0xffeece,
	0x000000, 0x000ae3, 0x000e21, 0x000b86, 0x000645,
	0x000147, 0xfffe32, 0xfffd45, 0xfffdce, 0xfffed9,
	0xffffb2, 0x000014,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lpf2_शेष_tap[] = अणु
	0x00050a, 0xfff004, 0x0002c1, 0x003c12, 0xffa818,
	0xffc87d, 0x010aef, 0xff5223, 0xfebd93, 0x028f41,
	0xff5c0e, 0xfc63f8, 0x055f81, 0x000000, 0xf478a0,
	0x11c5e3, 0x2ea74d, 0x11c5e3, 0xf478a0, 0x000000,
	0x055f81, 0xfc63f8, 0xff5c0e, 0x028f41, 0xfebd93,
	0xff5223, 0x010aef, 0xffc87d, 0xffa818, 0x003c12,
	0x0002c1, 0xfff004, 0x00050a,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lpf3_शेष_tap[] = अणु
	0x000000, 0x000081, 0x000000, 0xfffedb, 0x000000,
	0x00022d, 0x000000, 0xfffc46, 0x000000, 0x0005f7,
	0x000000, 0xfff6eb, 0x000000, 0x000d4e, 0x000000,
	0xffed1e, 0x000000, 0x001a1c, 0x000000, 0xffdcb0,
	0x000000, 0x002ede, 0x000000, 0xffc2d1, 0x000000,
	0x004ebe, 0x000000, 0xff9beb, 0x000000, 0x007dd7,
	0x000000, 0xff633a, 0x000000, 0x00c1d2, 0x000000,
	0xff11d5, 0x000000, 0x012368, 0x000000, 0xfe9c45,
	0x000000, 0x01b252, 0x000000, 0xfdebf6, 0x000000,
	0x0290b8, 0x000000, 0xfcca0d, 0x000000, 0x041d7c,
	0x000000, 0xfa8152, 0x000000, 0x07e9c6, 0x000000,
	0xf28fb5, 0x000000, 0x28b216, 0x3fffde, 0x28b216,
	0x000000, 0xf28fb5, 0x000000, 0x07e9c6, 0x000000,
	0xfa8152, 0x000000, 0x041d7c, 0x000000, 0xfcca0d,
	0x000000, 0x0290b8, 0x000000, 0xfdebf6, 0x000000,
	0x01b252, 0x000000, 0xfe9c45, 0x000000, 0x012368,
	0x000000, 0xff11d5, 0x000000, 0x00c1d2, 0x000000,
	0xff633a, 0x000000, 0x007dd7, 0x000000, 0xff9beb,
	0x000000, 0x004ebe, 0x000000, 0xffc2d1, 0x000000,
	0x002ede, 0x000000, 0xffdcb0, 0x000000, 0x001a1c,
	0x000000, 0xffed1e, 0x000000, 0x000d4e, 0x000000,
	0xfff6eb, 0x000000, 0x0005f7, 0x000000, 0xfffc46,
	0x000000, 0x00022d, 0x000000, 0xfffedb, 0x000000,
	0x000081, 0x000000,
पूर्ण;

/*
 * These values are sane शेषs क्रम the axg platक्रमm:
 * - OS = 64
 * - Latency = 38700 (?)
 *
 * TODO: There is a lot of dअगरferent HCIC, LPFs and HPF configurations possible.
 *       the configuration may depend on the dmic used by the platक्रमm, the
 *       expected tradeoff between latency and quality, etc ... If/When other
 *       settings are required, we should add a fw पूर्णांकerface to this driver to
 *       load new filter settings.
 */
अटल स्थिर काष्ठा axg_pdm_filters axg_शेष_filters = अणु
	.hcic = अणु
		.shअगरt = 0x15,
		.mult = 0x80,
		.steps = 7,
		.ds = 8,
	पूर्ण,
	.hpf = अणु
		.out_factor = 0x8000,
		.steps = 13,
	पूर्ण,
	.lpf = अणु
		[0] = अणु
			.ds = 2,
			.round_mode = 1,
			.tap = lpf1_शेष_tap,
			.tap_num = ARRAY_SIZE(lpf1_शेष_tap),
		पूर्ण,
		[1] = अणु
			.ds = 2,
			.round_mode = 0,
			.tap = lpf2_शेष_tap,
			.tap_num = ARRAY_SIZE(lpf2_शेष_tap),
		पूर्ण,
		[2] = अणु
			.ds = 2,
			.round_mode = 1,
			.tap = lpf3_शेष_tap,
			.tap_num = ARRAY_SIZE(lpf3_शेष_tap)
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा axg_pdm_cfg axg_pdm_config = अणु
	.filters = &axg_शेष_filters,
	.sys_rate = 250000000,
पूर्ण;

अटल स्थिर काष्ठा of_device_id axg_pdm_of_match[] = अणु
	अणु
		.compatible = "amlogic,axg-pdm",
		.data = &axg_pdm_config,
	पूर्ण, अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, axg_pdm_of_match);

अटल पूर्णांक axg_pdm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा axg_pdm *priv;
	व्योम __iomem *regs;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, priv);

	priv->cfg = of_device_get_match_data(dev);
	अगर (!priv->cfg) अणु
		dev_err(dev, "failed to match device\n");
		वापस -ENODEV;
	पूर्ण

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	priv->map = devm_regmap_init_mmio(dev, regs, &axg_pdm_regmap_cfg);
	अगर (IS_ERR(priv->map)) अणु
		dev_err(dev, "failed to init regmap: %ld\n",
			PTR_ERR(priv->map));
		वापस PTR_ERR(priv->map);
	पूर्ण

	priv->pclk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(priv->pclk)) अणु
		ret = PTR_ERR(priv->pclk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get pclk: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->dclk = devm_clk_get(dev, "dclk");
	अगर (IS_ERR(priv->dclk)) अणु
		ret = PTR_ERR(priv->dclk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get dclk: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->sysclk = devm_clk_get(dev, "sysclk");
	अगर (IS_ERR(priv->sysclk)) अणु
		ret = PTR_ERR(priv->sysclk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get dclk: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(dev, &axg_pdm_component_drv,
					       &axg_pdm_dai_drv, 1);
पूर्ण

अटल काष्ठा platक्रमm_driver axg_pdm_pdrv = अणु
	.probe = axg_pdm_probe,
	.driver = अणु
		.name = "axg-pdm",
		.of_match_table = axg_pdm_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(axg_pdm_pdrv);

MODULE_DESCRIPTION("Amlogic AXG PDM Input driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
