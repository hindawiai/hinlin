<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2020 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#घोषणा BLOCK_EN	0x00
#घोषणा  LORN_EN	0
#घोषणा  LORP_EN	1
#घोषणा  LOLN_EN	2
#घोषणा  LOLP_EN	3
#घोषणा  DACR_EN	4
#घोषणा  DACL_EN	5
#घोषणा  DACR_INV	20
#घोषणा  DACL_INV	21
#घोषणा  DACR_SRC	22
#घोषणा  DACL_SRC	23
#घोषणा  REFP_BUF_EN	BIT(12)
#घोषणा  BIAS_CURRENT_EN BIT(13)
#घोषणा  VMID_GEN_FAST	BIT(14)
#घोषणा  VMID_GEN_EN	BIT(15)
#घोषणा  I2S_MODE	BIT(30)
#घोषणा VOL_CTRL0	0x04
#घोषणा  GAIN_H		31
#घोषणा  GAIN_L		23
#घोषणा VOL_CTRL1	0x08
#घोषणा  DAC_MONO	8
#घोषणा  RAMP_RATE	10
#घोषणा  VC_RAMP_MODE	12
#घोषणा  MUTE_MODE	13
#घोषणा  UNMUTE_MODE	14
#घोषणा  DAC_SOFT_MUTE	15
#घोषणा  DACR_VC	16
#घोषणा  DACL_VC	24
#घोषणा LINEOUT_CFG	0x0c
#घोषणा  LORN_POL	0
#घोषणा  LORP_POL	4
#घोषणा  LOLN_POL	8
#घोषणा  LOLP_POL	12
#घोषणा POWER_CFG	0x10

काष्ठा t9015 अणु
	काष्ठा clk *pclk;
	काष्ठा regulator *avdd;
पूर्ण;

अटल पूर्णांक t9015_dai_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक val;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		val = I2S_MODE;
		अवरोध;

	हाल SND_SOC_DAIFMT_CBS_CFS:
		val = 0;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, BLOCK_EN, I2S_MODE, val);

	अगर (((fmt & SND_SOC_DAIFMT_FORMAT_MASK) != SND_SOC_DAIFMT_I2S) &&
	    ((fmt & SND_SOC_DAIFMT_FORMAT_MASK) != SND_SOC_DAIFMT_LEFT_J))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops t9015_dai_ops = अणु
	.set_fmt = t9015_dai_set_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver t9015_dai = अणु
	.name = "t9015-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = (SNDRV_PCM_FMTBIT_S8 |
			    SNDRV_PCM_FMTBIT_S16_LE |
			    SNDRV_PCM_FMTBIT_S20_LE |
			    SNDRV_PCM_FMTBIT_S24_LE),
	पूर्ण,
	.ops = &t9015_dai_ops,
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_MINMAX_MUTE(dac_vol_tlv, -9525, 0);

अटल स्थिर अक्षर * स्थिर ramp_rate_txt[] = अणु "Fast", "Slow" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(ramp_rate_क्रमागत, VOL_CTRL1, RAMP_RATE,
			    ramp_rate_txt);

अटल स्थिर अक्षर * स्थिर dacr_in_txt[] = अणु "Right", "Left" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(dacr_in_क्रमागत, BLOCK_EN, DACR_SRC, dacr_in_txt);

अटल स्थिर अक्षर * स्थिर dacl_in_txt[] = अणु "Left", "Right" पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(dacl_in_क्रमागत, BLOCK_EN, DACL_SRC, dacl_in_txt);

अटल स्थिर अक्षर * स्थिर mono_txt[] = अणु "Stereo", "Mono"पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(mono_क्रमागत, VOL_CTRL1, DAC_MONO, mono_txt);

अटल स्थिर काष्ठा snd_kcontrol_new t9015_snd_controls[] = अणु
	/* Volume Controls */
	SOC_ENUM("Playback Channel Mode", mono_क्रमागत),
	SOC_SINGLE("Playback Switch", VOL_CTRL1, DAC_SOFT_MUTE, 1, 1),
	SOC_DOUBLE_TLV("Playback Volume", VOL_CTRL1, DACL_VC, DACR_VC,
		       0xff, 0, dac_vol_tlv),

	/* Ramp Controls */
	SOC_ENUM("Ramp Rate", ramp_rate_क्रमागत),
	SOC_SINGLE("Volume Ramp Switch", VOL_CTRL1, VC_RAMP_MODE, 1, 0),
	SOC_SINGLE("Mute Ramp Switch", VOL_CTRL1, MUTE_MODE, 1, 0),
	SOC_SINGLE("Unmute Ramp Switch", VOL_CTRL1, UNMUTE_MODE, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new t9015_right_dac_mux =
	SOC_DAPM_ENUM("Right DAC Source", dacr_in_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new t9015_left_dac_mux =
	SOC_DAPM_ENUM("Left DAC Source", dacl_in_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget t9015_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("Right IN", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("Left IN", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MUX("Right DAC Sel", SND_SOC_NOPM, 0, 0,
			 &t9015_right_dac_mux),
	SND_SOC_DAPM_MUX("Left DAC Sel", SND_SOC_NOPM, 0, 0,
			 &t9015_left_dac_mux),
	SND_SOC_DAPM_DAC("Right DAC", शून्य, BLOCK_EN, DACR_EN, 0),
	SND_SOC_DAPM_DAC("Left DAC",  शून्य, BLOCK_EN, DACL_EN, 0),
	SND_SOC_DAPM_OUT_DRV("Right- Driver", BLOCK_EN, LORN_EN, 0,
			 शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("Right+ Driver", BLOCK_EN, LORP_EN, 0,
			 शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("Left- Driver",  BLOCK_EN, LOLN_EN, 0,
			 शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("Left+ Driver",  BLOCK_EN, LOLP_EN, 0,
			 शून्य, 0),
	SND_SOC_DAPM_OUTPUT("LORN"),
	SND_SOC_DAPM_OUTPUT("LORP"),
	SND_SOC_DAPM_OUTPUT("LOLN"),
	SND_SOC_DAPM_OUTPUT("LOLP"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route t9015_dapm_routes[] = अणु
	अणु "Right IN", शून्य, "Playback" पूर्ण,
	अणु "Left IN",  शून्य, "Playback" पूर्ण,
	अणु "Right DAC Sel", "Right", "Right IN" पूर्ण,
	अणु "Right DAC Sel", "Left",  "Left IN" पूर्ण,
	अणु "Left DAC Sel",  "Right", "Right IN" पूर्ण,
	अणु "Left DAC Sel",  "Left",  "Left IN" पूर्ण,
	अणु "Right DAC", शून्य, "Right DAC Sel" पूर्ण,
	अणु "Left DAC",  शून्य, "Left DAC Sel" पूर्ण,
	अणु "Right- Driver", शून्य, "Right DAC" पूर्ण,
	अणु "Right+ Driver", शून्य, "Right DAC" पूर्ण,
	अणु "Left- Driver",  शून्य, "Left DAC"  पूर्ण,
	अणु "Left+ Driver",  शून्य, "Left DAC"  पूर्ण,
	अणु "LORN", शून्य, "Right- Driver", पूर्ण,
	अणु "LORP", शून्य, "Right+ Driver", पूर्ण,
	अणु "LOLN", शून्य, "Left- Driver",  पूर्ण,
	अणु "LOLP", शून्य, "Left+ Driver",  पूर्ण,
पूर्ण;

अटल पूर्णांक t9015_set_bias_level(काष्ठा snd_soc_component *component,
				क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा t9015 *priv = snd_soc_component_get_drvdata(component);
	क्रमागत snd_soc_bias_level now =
		snd_soc_component_get_bias_level(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		snd_soc_component_update_bits(component, BLOCK_EN,
					      BIAS_CURRENT_EN,
					      BIAS_CURRENT_EN);
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		snd_soc_component_update_bits(component, BLOCK_EN,
					      BIAS_CURRENT_EN,
					      0);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		ret = regulator_enable(priv->avdd);
		अगर (ret) अणु
			dev_err(component->dev, "AVDD enable failed\n");
			वापस ret;
		पूर्ण

		अगर (now == SND_SOC_BIAS_OFF) अणु
			snd_soc_component_update_bits(component, BLOCK_EN,
				VMID_GEN_EN | VMID_GEN_FAST | REFP_BUF_EN,
				VMID_GEN_EN | VMID_GEN_FAST | REFP_BUF_EN);

			mdelay(200);
			snd_soc_component_update_bits(component, BLOCK_EN,
						      VMID_GEN_FAST,
						      0);
		पूर्ण

		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, BLOCK_EN,
			VMID_GEN_EN | VMID_GEN_FAST | REFP_BUF_EN,
			0);

		regulator_disable(priv->avdd);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver t9015_codec_driver = अणु
	.set_bias_level		= t9015_set_bias_level,
	.controls		= t9015_snd_controls,
	.num_controls		= ARRAY_SIZE(t9015_snd_controls),
	.dapm_widमाला_लो		= t9015_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(t9015_dapm_widमाला_लो),
	.dapm_routes		= t9015_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(t9015_dapm_routes),
	.suspend_bias_off	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config t9015_regmap_config = अणु
	.reg_bits		= 32,
	.reg_stride		= 4,
	.val_bits		= 32,
	.max_रेजिस्टर		= POWER_CFG,
पूर्ण;

अटल पूर्णांक t9015_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा t9015 *priv;
	व्योम __iomem *regs;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, priv);

	priv->pclk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(priv->pclk)) अणु
		अगर (PTR_ERR(priv->pclk) != -EPROBE_DEFER)
			dev_err(dev, "failed to get core clock\n");
		वापस PTR_ERR(priv->pclk);
	पूर्ण

	priv->avdd = devm_regulator_get(dev, "AVDD");
	अगर (IS_ERR(priv->avdd)) अणु
		अगर (PTR_ERR(priv->avdd) != -EPROBE_DEFER)
			dev_err(dev, "failed to AVDD\n");
		वापस PTR_ERR(priv->avdd);
	पूर्ण

	ret = clk_prepare_enable(priv->pclk);
	अगर (ret) अणु
		dev_err(dev, "core clock enable failed\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev,
			(व्योम(*)(व्योम *))clk_disable_unprepare,
			priv->pclk);
	अगर (ret)
		वापस ret;

	ret = device_reset(dev);
	अगर (ret) अणु
		dev_err(dev, "reset failed\n");
		वापस ret;
	पूर्ण

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs)) अणु
		dev_err(dev, "register map failed\n");
		वापस PTR_ERR(regs);
	पूर्ण

	regmap = devm_regmap_init_mmio(dev, regs, &t9015_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "regmap init failed\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	/*
	 * Initialize output polarity:
	 * ATM the output polarity is fixed but in the future it might useful
	 * to add DT property to set this depending on the platक्रमm needs
	 */
	regmap_ग_लिखो(regmap, LINEOUT_CFG, 0x1111);

	वापस devm_snd_soc_रेजिस्टर_component(dev, &t9015_codec_driver,
					       &t9015_dai, 1);
पूर्ण

अटल स्थिर काष्ठा of_device_id t9015_ids[] __maybe_unused = अणु
	अणु .compatible = "amlogic,t9015", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, t9015_ids);

अटल काष्ठा platक्रमm_driver t9015_driver = अणु
	.driver = अणु
		.name = "t9015-codec",
		.of_match_table = of_match_ptr(t9015_ids),
	पूर्ण,
	.probe = t9015_probe,
पूर्ण;

module_platक्रमm_driver(t9015_driver);

MODULE_DESCRIPTION("ASoC Amlogic T9015 codec driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL");
