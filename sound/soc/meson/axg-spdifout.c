<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
//
// Copyright (c) 2018 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/pcm_iec958.h>

/*
 * NOTE:
 * The meaning of bits SPDIFOUT_CTRL0_XXX_SEL is actually the opposite
 * of what the करोcumentation says. Manual control on V, U and C bits is
 * applied when the related sel bits are cleared
 */

#घोषणा SPDIFOUT_STAT			0x00
#घोषणा SPDIFOUT_GAIN0			0x04
#घोषणा SPDIFOUT_GAIN1			0x08
#घोषणा SPDIFOUT_CTRL0			0x0c
#घोषणा  SPDIFOUT_CTRL0_EN		BIT(31)
#घोषणा  SPDIFOUT_CTRL0_RST_OUT		BIT(29)
#घोषणा  SPDIFOUT_CTRL0_RST_IN		BIT(28)
#घोषणा  SPDIFOUT_CTRL0_USEL		BIT(26)
#घोषणा  SPDIFOUT_CTRL0_USET		BIT(25)
#घोषणा  SPDIFOUT_CTRL0_CHSTS_SEL	BIT(24)
#घोषणा  SPDIFOUT_CTRL0_DATA_SEL	BIT(20)
#घोषणा  SPDIFOUT_CTRL0_MSB_FIRST	BIT(19)
#घोषणा  SPDIFOUT_CTRL0_VSEL		BIT(18)
#घोषणा  SPDIFOUT_CTRL0_VSET		BIT(17)
#घोषणा  SPDIFOUT_CTRL0_MASK_MASK	GENMASK(11, 4)
#घोषणा  SPDIFOUT_CTRL0_MASK(x)		((x) << 4)
#घोषणा SPDIFOUT_CTRL1			0x10
#घोषणा  SPDIFOUT_CTRL1_MSB_POS_MASK	GENMASK(12, 8)
#घोषणा  SPDIFOUT_CTRL1_MSB_POS(x)	((x) << 8)
#घोषणा  SPDIFOUT_CTRL1_TYPE_MASK	GENMASK(6, 4)
#घोषणा  SPDIFOUT_CTRL1_TYPE(x)		((x) << 4)
#घोषणा SPDIFOUT_PREAMB			0x14
#घोषणा SPDIFOUT_SWAP			0x18
#घोषणा SPDIFOUT_CHSTS0			0x1c
#घोषणा SPDIFOUT_CHSTS1			0x20
#घोषणा SPDIFOUT_CHSTS2			0x24
#घोषणा SPDIFOUT_CHSTS3			0x28
#घोषणा SPDIFOUT_CHSTS4			0x2c
#घोषणा SPDIFOUT_CHSTS5			0x30
#घोषणा SPDIFOUT_CHSTS6			0x34
#घोषणा SPDIFOUT_CHSTS7			0x38
#घोषणा SPDIFOUT_CHSTS8			0x3c
#घोषणा SPDIFOUT_CHSTS9			0x40
#घोषणा SPDIFOUT_CHSTSA			0x44
#घोषणा SPDIFOUT_CHSTSB			0x48
#घोषणा SPDIFOUT_MUTE_VAL		0x4c

काष्ठा axg_spdअगरout अणु
	काष्ठा regmap *map;
	काष्ठा clk *mclk;
	काष्ठा clk *pclk;
पूर्ण;

अटल व्योम axg_spdअगरout_enable(काष्ठा regmap *map)
अणु
	/* Apply both reset */
	regmap_update_bits(map, SPDIFOUT_CTRL0,
			   SPDIFOUT_CTRL0_RST_OUT | SPDIFOUT_CTRL0_RST_IN,
			   0);

	/* Clear out reset beक्रमe in reset */
	regmap_update_bits(map, SPDIFOUT_CTRL0,
			   SPDIFOUT_CTRL0_RST_OUT, SPDIFOUT_CTRL0_RST_OUT);
	regmap_update_bits(map, SPDIFOUT_CTRL0,
			   SPDIFOUT_CTRL0_RST_IN,  SPDIFOUT_CTRL0_RST_IN);

	/* Enable spdअगरout */
	regmap_update_bits(map, SPDIFOUT_CTRL0, SPDIFOUT_CTRL0_EN,
			   SPDIFOUT_CTRL0_EN);
पूर्ण

अटल व्योम axg_spdअगरout_disable(काष्ठा regmap *map)
अणु
	regmap_update_bits(map, SPDIFOUT_CTRL0, SPDIFOUT_CTRL0_EN, 0);
पूर्ण

अटल पूर्णांक axg_spdअगरout_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_spdअगरout *priv = snd_soc_dai_get_drvdata(dai);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		axg_spdअगरout_enable(priv->map);
		वापस 0;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		axg_spdअगरout_disable(priv->map);
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक axg_spdअगरout_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा axg_spdअगरout *priv = snd_soc_dai_get_drvdata(dai);

	/* Use spdअगर valid bit to perक्रमm digital mute */
	regmap_update_bits(priv->map, SPDIFOUT_CTRL0, SPDIFOUT_CTRL0_VSET,
			   mute ? SPDIFOUT_CTRL0_VSET : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक axg_spdअगरout_sample_fmt(काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_spdअगरout *priv = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक val;

	/* Set the samples spdअगरout will pull from the FIFO */
	चयन (params_channels(params)) अणु
	हाल 1:
		val = SPDIFOUT_CTRL0_MASK(0x1);
		अवरोध;
	हाल 2:
		val = SPDIFOUT_CTRL0_MASK(0x3);
		अवरोध;
	शेष:
		dev_err(dai->dev, "too many channels for spdif dai: %u\n",
			params_channels(params));
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(priv->map, SPDIFOUT_CTRL0,
			   SPDIFOUT_CTRL0_MASK_MASK, val);

	/* FIFO data are arranged in chunks of 64bits */
	चयन (params_physical_width(params)) अणु
	हाल 8:
		/* 8 samples of 8 bits */
		val = SPDIFOUT_CTRL1_TYPE(0);
		अवरोध;
	हाल 16:
		/* 4 samples of 16 bits - right justअगरied */
		val = SPDIFOUT_CTRL1_TYPE(2);
		अवरोध;
	हाल 32:
		/* 2 samples of 32 bits - right justअगरied */
		val = SPDIFOUT_CTRL1_TYPE(4);
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unsupported physical width: %u\n",
			params_physical_width(params));
		वापस -EINVAL;
	पूर्ण

	/* Position of the MSB in FIFO samples */
	val |= SPDIFOUT_CTRL1_MSB_POS(params_width(params) - 1);

	regmap_update_bits(priv->map, SPDIFOUT_CTRL1,
			   SPDIFOUT_CTRL1_MSB_POS_MASK |
			   SPDIFOUT_CTRL1_TYPE_MASK, val);

	regmap_update_bits(priv->map, SPDIFOUT_CTRL0,
			   SPDIFOUT_CTRL0_MSB_FIRST | SPDIFOUT_CTRL0_DATA_SEL,
			   0);

	वापस 0;
पूर्ण

अटल पूर्णांक axg_spdअगरout_set_chsts(काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_spdअगरout *priv = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक offset;
	पूर्णांक ret;
	u8 cs[4];
	u32 val;

	ret = snd_pcm_create_iec958_consumer_hw_params(params, cs, 4);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "Creating IEC958 channel status failed %d\n",
			ret);
		वापस ret;
	पूर्ण
	val = cs[0] | cs[1] << 8 | cs[2] << 16 | cs[3] << 24;

	/* Setup channel status A bits [31 - 0]*/
	regmap_ग_लिखो(priv->map, SPDIFOUT_CHSTS0, val);

	/* Clear channel status A bits [191 - 32] */
	क्रम (offset = SPDIFOUT_CHSTS1; offset <= SPDIFOUT_CHSTS5;
	     offset += regmap_get_reg_stride(priv->map))
		regmap_ग_लिखो(priv->map, offset, 0);

	/* Setup channel status B bits [31 - 0]*/
	regmap_ग_लिखो(priv->map, SPDIFOUT_CHSTS6, val);

	/* Clear channel status B bits [191 - 32] */
	क्रम (offset = SPDIFOUT_CHSTS7; offset <= SPDIFOUT_CHSTSB;
	     offset += regmap_get_reg_stride(priv->map))
		regmap_ग_लिखो(priv->map, offset, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक axg_spdअगरout_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_spdअगरout *priv = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक rate = params_rate(params);
	पूर्णांक ret;

	/* 2 * 32bits per subframe * 2 channels = 128 */
	ret = clk_set_rate(priv->mclk, rate * 128);
	अगर (ret) अणु
		dev_err(dai->dev, "failed to set spdif clock\n");
		वापस ret;
	पूर्ण

	ret = axg_spdअगरout_sample_fmt(params, dai);
	अगर (ret) अणु
		dev_err(dai->dev, "failed to setup sample format\n");
		वापस ret;
	पूर्ण

	ret = axg_spdअगरout_set_chsts(params, dai);
	अगर (ret) अणु
		dev_err(dai->dev, "failed to setup channel status words\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axg_spdअगरout_startup(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_spdअगरout *priv = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	/* Clock the spdअगर output block */
	ret = clk_prepare_enable(priv->pclk);
	अगर (ret) अणु
		dev_err(dai->dev, "failed to enable pclk\n");
		वापस ret;
	पूर्ण

	/* Make sure the block is initially stopped */
	axg_spdअगरout_disable(priv->map);

	/* Insert data from bit 27 lsb first */
	regmap_update_bits(priv->map, SPDIFOUT_CTRL0,
			   SPDIFOUT_CTRL0_MSB_FIRST | SPDIFOUT_CTRL0_DATA_SEL,
			   0);

	/* Manual control of V, C and U, U = 0 */
	regmap_update_bits(priv->map, SPDIFOUT_CTRL0,
			   SPDIFOUT_CTRL0_CHSTS_SEL | SPDIFOUT_CTRL0_VSEL |
			   SPDIFOUT_CTRL0_USEL | SPDIFOUT_CTRL0_USET,
			   0);

	/* Static SWAP configuration ATM */
	regmap_ग_लिखो(priv->map, SPDIFOUT_SWAP, 0x10);

	वापस 0;
पूर्ण

अटल व्योम axg_spdअगरout_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_spdअगरout *priv = snd_soc_dai_get_drvdata(dai);

	clk_disable_unprepare(priv->pclk);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops axg_spdअगरout_ops = अणु
	.trigger	= axg_spdअगरout_trigger,
	.mute_stream	= axg_spdअगरout_mute,
	.hw_params	= axg_spdअगरout_hw_params,
	.startup	= axg_spdअगरout_startup,
	.shutकरोwn	= axg_spdअगरout_shutकरोwn,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver axg_spdअगरout_dai_drv[] = अणु
	अणु
		.name = "SPDIF Output",
		.playback = अणु
			.stream_name	= "Playback",
			.channels_min	= 1,
			.channels_max	= 2,
			.rates		= (SNDRV_PCM_RATE_32000  |
					   SNDRV_PCM_RATE_44100  |
					   SNDRV_PCM_RATE_48000  |
					   SNDRV_PCM_RATE_88200  |
					   SNDRV_PCM_RATE_96000  |
					   SNDRV_PCM_RATE_176400 |
					   SNDRV_PCM_RATE_192000),
			.क्रमmats	= (SNDRV_PCM_FMTBIT_S8     |
					   SNDRV_PCM_FMTBIT_S16_LE |
					   SNDRV_PCM_FMTBIT_S20_LE |
					   SNDRV_PCM_FMTBIT_S24_LE),
		पूर्ण,
		.ops = &axg_spdअगरout_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर spdअगरout_sel_texts[] = अणु
	"IN 0", "IN 1", "IN 2",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(axg_spdअगरout_sel_क्रमागत, SPDIFOUT_CTRL1, 24,
			    spdअगरout_sel_texts);

अटल स्थिर काष्ठा snd_kcontrol_new axg_spdअगरout_in_mux =
	SOC_DAPM_ENUM("Input Source", axg_spdअगरout_sel_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget axg_spdअगरout_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("IN 0", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 1", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 2", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("SRC SEL", SND_SOC_NOPM, 0, 0, &axg_spdअगरout_in_mux),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route axg_spdअगरout_dapm_routes[] = अणु
	अणु "SRC SEL", "IN 0", "IN 0" पूर्ण,
	अणु "SRC SEL", "IN 1", "IN 1" पूर्ण,
	अणु "SRC SEL", "IN 2", "IN 2" पूर्ण,
	अणु "Playback", शून्य, "SRC SEL" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new axg_spdअगरout_controls[] = अणु
	SOC_DOUBLE("Playback Volume", SPDIFOUT_GAIN0,  0,  8, 255, 0),
	SOC_DOUBLE("Playback Switch", SPDIFOUT_CTRL0, 22, 21, 1, 1),
	SOC_SINGLE("Playback Gain Enable Switch",
		   SPDIFOUT_CTRL1, 26, 1, 0),
	SOC_SINGLE("Playback Channels Mix Switch",
		   SPDIFOUT_CTRL0, 23, 1, 0),
पूर्ण;

अटल पूर्णांक axg_spdअगरout_set_bias_level(काष्ठा snd_soc_component *component,
				       क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा axg_spdअगरout *priv = snd_soc_component_get_drvdata(component);
	क्रमागत snd_soc_bias_level now =
		snd_soc_component_get_bias_level(component);
	पूर्णांक ret = 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		अगर (now == SND_SOC_BIAS_STANDBY)
			ret = clk_prepare_enable(priv->mclk);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (now == SND_SOC_BIAS_PREPARE)
			clk_disable_unprepare(priv->mclk);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver axg_spdअगरout_component_drv = अणु
	.controls		= axg_spdअगरout_controls,
	.num_controls		= ARRAY_SIZE(axg_spdअगरout_controls),
	.dapm_widमाला_लो		= axg_spdअगरout_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(axg_spdअगरout_dapm_widमाला_लो),
	.dapm_routes		= axg_spdअगरout_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(axg_spdअगरout_dapm_routes),
	.set_bias_level		= axg_spdअगरout_set_bias_level,
पूर्ण;

अटल स्थिर काष्ठा regmap_config axg_spdअगरout_regmap_cfg = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= SPDIFOUT_MUTE_VAL,
पूर्ण;

अटल स्थिर काष्ठा of_device_id axg_spdअगरout_of_match[] = अणु
	अणु .compatible = "amlogic,axg-spdifout", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, axg_spdअगरout_of_match);

अटल पूर्णांक axg_spdअगरout_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा axg_spdअगरout *priv;
	व्योम __iomem *regs;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, priv);

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	priv->map = devm_regmap_init_mmio(dev, regs, &axg_spdअगरout_regmap_cfg);
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

	priv->mclk = devm_clk_get(dev, "mclk");
	अगर (IS_ERR(priv->mclk)) अणु
		ret = PTR_ERR(priv->mclk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get mclk: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(dev, &axg_spdअगरout_component_drv,
			axg_spdअगरout_dai_drv, ARRAY_SIZE(axg_spdअगरout_dai_drv));
पूर्ण

अटल काष्ठा platक्रमm_driver axg_spdअगरout_pdrv = अणु
	.probe = axg_spdअगरout_probe,
	.driver = अणु
		.name = "axg-spdifout",
		.of_match_table = axg_spdअगरout_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(axg_spdअगरout_pdrv);

MODULE_DESCRIPTION("Amlogic AXG SPDIF Output driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
