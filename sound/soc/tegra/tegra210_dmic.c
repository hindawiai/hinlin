<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// tegra210_dmic.c - Tegra210 DMIC driver
//
// Copyright (c) 2020 NVIDIA CORPORATION.  All rights reserved.

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश "tegra210_dmic.h"
#समावेश "tegra_cif.h"

अटल स्थिर काष्ठा reg_शेष tegra210_dmic_reg_शेषs[] = अणु
	अणु TEGRA210_DMIC_TX_INT_MASK, 0x00000001 पूर्ण,
	अणु TEGRA210_DMIC_TX_CIF_CTRL, 0x00007700 पूर्ण,
	अणु TEGRA210_DMIC_CG, 0x1 पूर्ण,
	अणु TEGRA210_DMIC_CTRL, 0x00000301 पूर्ण,
	/* Below enables all filters - DCR, LP and SC */
	अणु TEGRA210_DMIC_DBG_CTRL, 0xe पूर्ण,
	/* Below as per latest POR value */
	अणु TEGRA210_DMIC_DCR_BIQUAD_0_COEF_4, 0x0 पूर्ण,
	/* LP filter is configured क्रम pass through and used to apply gain */
	अणु TEGRA210_DMIC_LP_BIQUAD_0_COEF_0, 0x00800000 पूर्ण,
	अणु TEGRA210_DMIC_LP_BIQUAD_0_COEF_1, 0x0 पूर्ण,
	अणु TEGRA210_DMIC_LP_BIQUAD_0_COEF_2, 0x0 पूर्ण,
	अणु TEGRA210_DMIC_LP_BIQUAD_0_COEF_3, 0x0 पूर्ण,
	अणु TEGRA210_DMIC_LP_BIQUAD_0_COEF_4, 0x0 पूर्ण,
	अणु TEGRA210_DMIC_LP_BIQUAD_1_COEF_0, 0x00800000 पूर्ण,
	अणु TEGRA210_DMIC_LP_BIQUAD_1_COEF_1, 0x0 पूर्ण,
	अणु TEGRA210_DMIC_LP_BIQUAD_1_COEF_2, 0x0 पूर्ण,
	अणु TEGRA210_DMIC_LP_BIQUAD_1_COEF_3, 0x0 पूर्ण,
	अणु TEGRA210_DMIC_LP_BIQUAD_1_COEF_4, 0x0 पूर्ण,
पूर्ण;

अटल पूर्णांक __maybe_unused tegra210_dmic_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra210_dmic *dmic = dev_get_drvdata(dev);

	regcache_cache_only(dmic->regmap, true);
	regcache_mark_dirty(dmic->regmap);

	clk_disable_unprepare(dmic->clk_dmic);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra210_dmic_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra210_dmic *dmic = dev_get_drvdata(dev);
	पूर्णांक err;

	err = clk_prepare_enable(dmic->clk_dmic);
	अगर (err) अणु
		dev_err(dev, "failed to enable DMIC clock, err: %d\n", err);
		वापस err;
	पूर्ण

	regcache_cache_only(dmic->regmap, false);
	regcache_sync(dmic->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_dmic_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा tegra210_dmic *dmic = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक srate, clk_rate, channels;
	काष्ठा tegra_cअगर_conf cअगर_conf;
	अचिन्हित दीर्घ दीर्घ gain_q23 = DEFAULT_GAIN_Q23;
	पूर्णांक err;

	स_रखो(&cअगर_conf, 0, माप(काष्ठा tegra_cअगर_conf));

	channels = params_channels(params);

	cअगर_conf.audio_ch = channels;

	चयन (dmic->ch_select) अणु
	हाल DMIC_CH_SELECT_LEFT:
	हाल DMIC_CH_SELECT_RIGHT:
		cअगर_conf.client_ch = 1;
		अवरोध;
	हाल DMIC_CH_SELECT_STEREO:
		cअगर_conf.client_ch = 2;
		अवरोध;
	शेष:
		dev_err(dai->dev, "invalid DMIC client channels\n");
		वापस -EINVAL;
	पूर्ण

	srate = params_rate(params);

	/*
	 * DMIC घड़ी rate is a multiple of 'Over Sampling Ratio' and
	 * 'Sample Rate'. The supported OSR values are 64, 128 and 256.
	 */
	clk_rate = (DMIC_OSR_FACTOR << dmic->osr_val) * srate;

	err = clk_set_rate(dmic->clk_dmic, clk_rate);
	अगर (err) अणु
		dev_err(dai->dev, "can't set DMIC clock rate %u, err: %d\n",
			clk_rate, err);
		वापस err;
	पूर्ण

	regmap_update_bits(dmic->regmap,
			   /* Reg */
			   TEGRA210_DMIC_CTRL,
			   /* Mask */
			   TEGRA210_DMIC_CTRL_LRSEL_POLARITY_MASK |
			   TEGRA210_DMIC_CTRL_OSR_MASK |
			   TEGRA210_DMIC_CTRL_CHANNEL_SELECT_MASK,
			   /* Value */
			   (dmic->lrsel << LRSEL_POL_SHIFT) |
			   (dmic->osr_val << OSR_SHIFT) |
			   ((dmic->ch_select + 1) << CH_SEL_SHIFT));

	/*
	 * Use LP filter gain रेजिस्टर to apply boost.
	 * Boost Gain Volume control has 100x factor.
	 */
	अगर (dmic->boost_gain)
		gain_q23 = भाग_u64(gain_q23 * dmic->boost_gain, 100);

	regmap_ग_लिखो(dmic->regmap, TEGRA210_DMIC_LP_FILTER_GAIN,
		     (अचिन्हित पूर्णांक)gain_q23);

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		cअगर_conf.audio_bits = TEGRA_ACIF_BITS_16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		cअगर_conf.audio_bits = TEGRA_ACIF_BITS_32;
		अवरोध;
	शेष:
		dev_err(dai->dev, "unsupported format!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	cअगर_conf.client_bits = TEGRA_ACIF_BITS_24;
	cअगर_conf.mono_conv = dmic->mono_to_stereo;
	cअगर_conf.stereo_conv = dmic->stereo_to_mono;

	tegra_set_cअगर(dmic->regmap, TEGRA210_DMIC_TX_CIF_CTRL, &cअगर_conf);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_dmic_get_control(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_kcontrol_component(kcontrol);
	काष्ठा tegra210_dmic *dmic = snd_soc_component_get_drvdata(comp);

	अगर (म_माला(kcontrol->id.name, "Boost Gain Volume"))
		ucontrol->value.पूर्णांकeger.value[0] = dmic->boost_gain;
	अन्यथा अगर (म_माला(kcontrol->id.name, "Channel Select"))
		ucontrol->value.पूर्णांकeger.value[0] = dmic->ch_select;
	अन्यथा अगर (म_माला(kcontrol->id.name, "Mono To Stereo"))
		ucontrol->value.पूर्णांकeger.value[0] = dmic->mono_to_stereo;
	अन्यथा अगर (म_माला(kcontrol->id.name, "Stereo To Mono"))
		ucontrol->value.पूर्णांकeger.value[0] = dmic->stereo_to_mono;
	अन्यथा अगर (म_माला(kcontrol->id.name, "OSR Value"))
		ucontrol->value.पूर्णांकeger.value[0] = dmic->osr_val;
	अन्यथा अगर (म_माला(kcontrol->id.name, "LR Polarity Select"))
		ucontrol->value.पूर्णांकeger.value[0] = dmic->lrsel;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_dmic_put_control(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *comp = snd_soc_kcontrol_component(kcontrol);
	काष्ठा tegra210_dmic *dmic = snd_soc_component_get_drvdata(comp);
	पूर्णांक value = ucontrol->value.पूर्णांकeger.value[0];

	अगर (म_माला(kcontrol->id.name, "Boost Gain Volume"))
		dmic->boost_gain = value;
	अन्यथा अगर (म_माला(kcontrol->id.name, "Channel Select"))
		dmic->ch_select = ucontrol->value.पूर्णांकeger.value[0];
	अन्यथा अगर (म_माला(kcontrol->id.name, "Mono To Stereo"))
		dmic->mono_to_stereo = value;
	अन्यथा अगर (म_माला(kcontrol->id.name, "Stereo To Mono"))
		dmic->stereo_to_mono = value;
	अन्यथा अगर (म_माला(kcontrol->id.name, "OSR Value"))
		dmic->osr_val = value;
	अन्यथा अगर (म_माला(kcontrol->id.name, "LR Polarity Select"))
		dmic->lrsel = value;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops tegra210_dmic_dai_ops = अणु
	.hw_params	= tegra210_dmic_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver tegra210_dmic_dais[] = अणु
	अणु
		.name = "DMIC-CIF",
		.capture = अणु
			.stream_name = "CIF-Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S32_LE,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "DMIC-DAP",
		.capture = अणु
			.stream_name = "DAP-Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S32_LE,
		पूर्ण,
		.ops = &tegra210_dmic_dai_ops,
		.symmetric_rate = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tegra210_dmic_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_OUT("TX", शून्य, 0, TEGRA210_DMIC_ENABLE, 0, 0),
	SND_SOC_DAPM_MIC("MIC", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tegra210_dmic_routes[] = अणु
	अणु "XBAR-RX",		शून्य,	"XBAR-Capture" पूर्ण,
	अणु "XBAR-Capture",	शून्य,	"CIF-Capture" पूर्ण,
	अणु "CIF-Capture",	शून्य,	"TX" पूर्ण,
	अणु "TX",			शून्य,	"DAP-Capture" पूर्ण,
	अणु "DAP-Capture",	शून्य,	"MIC" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra210_dmic_ch_select[] = अणु
	"Left", "Right", "Stereo",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत tegra210_dmic_ch_क्रमागत =
	SOC_ENUM_SINGLE(0, 0, ARRAY_SIZE(tegra210_dmic_ch_select),
			tegra210_dmic_ch_select);

अटल स्थिर अक्षर * स्थिर tegra210_dmic_mono_conv_text[] = अणु
	"Zero", "Copy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra210_dmic_stereo_conv_text[] = अणु
	"CH0", "CH1", "AVG",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत tegra210_dmic_mono_conv_क्रमागत =
	SOC_ENUM_SINGLE(0, 0, ARRAY_SIZE(tegra210_dmic_mono_conv_text),
			tegra210_dmic_mono_conv_text);

अटल स्थिर काष्ठा soc_क्रमागत tegra210_dmic_stereo_conv_क्रमागत =
	SOC_ENUM_SINGLE(0, 0, ARRAY_SIZE(tegra210_dmic_stereo_conv_text),
			tegra210_dmic_stereo_conv_text);

अटल स्थिर अक्षर * स्थिर tegra210_dmic_osr_text[] = अणु
	"OSR_64", "OSR_128", "OSR_256",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत tegra210_dmic_osr_क्रमागत =
	SOC_ENUM_SINGLE(0, 0, ARRAY_SIZE(tegra210_dmic_osr_text),
			tegra210_dmic_osr_text);

अटल स्थिर अक्षर * स्थिर tegra210_dmic_lrsel_text[] = अणु
	"Left", "Right",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत tegra210_dmic_lrsel_क्रमागत =
	SOC_ENUM_SINGLE(0, 0, ARRAY_SIZE(tegra210_dmic_lrsel_text),
			tegra210_dmic_lrsel_text);

अटल स्थिर काष्ठा snd_kcontrol_new tegra210_dmic_controls[] = अणु
	SOC_SINGLE_EXT("Boost Gain Volume", 0, 0, MAX_BOOST_GAIN, 0,
		       tegra210_dmic_get_control, tegra210_dmic_put_control),
	SOC_ENUM_EXT("Channel Select", tegra210_dmic_ch_क्रमागत,
		     tegra210_dmic_get_control, tegra210_dmic_put_control),
	SOC_ENUM_EXT("Mono To Stereo",
		     tegra210_dmic_mono_conv_क्रमागत, tegra210_dmic_get_control,
		     tegra210_dmic_put_control),
	SOC_ENUM_EXT("Stereo To Mono",
		     tegra210_dmic_stereo_conv_क्रमागत, tegra210_dmic_get_control,
		     tegra210_dmic_put_control),
	SOC_ENUM_EXT("OSR Value", tegra210_dmic_osr_क्रमागत,
		     tegra210_dmic_get_control, tegra210_dmic_put_control),
	SOC_ENUM_EXT("LR Polarity Select", tegra210_dmic_lrsel_क्रमागत,
		     tegra210_dmic_get_control, tegra210_dmic_put_control),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver tegra210_dmic_compnt = अणु
	.dapm_widमाला_लो		= tegra210_dmic_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tegra210_dmic_widमाला_लो),
	.dapm_routes		= tegra210_dmic_routes,
	.num_dapm_routes	= ARRAY_SIZE(tegra210_dmic_routes),
	.controls		= tegra210_dmic_controls,
	.num_controls		= ARRAY_SIZE(tegra210_dmic_controls),
पूर्ण;

अटल bool tegra210_dmic_wr_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA210_DMIC_TX_INT_MASK ... TEGRA210_DMIC_TX_CIF_CTRL:
	हाल TEGRA210_DMIC_ENABLE ... TEGRA210_DMIC_CG:
	हाल TEGRA210_DMIC_CTRL:
	हाल TEGRA210_DMIC_DBG_CTRL:
	हाल TEGRA210_DMIC_DCR_BIQUAD_0_COEF_4 ... TEGRA210_DMIC_LP_BIQUAD_1_COEF_4:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool tegra210_dmic_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (tegra210_dmic_wr_reg(dev, reg))
		वापस true;

	चयन (reg) अणु
	हाल TEGRA210_DMIC_TX_STATUS:
	हाल TEGRA210_DMIC_TX_INT_STATUS:
	हाल TEGRA210_DMIC_STATUS:
	हाल TEGRA210_DMIC_INT_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool tegra210_dmic_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA210_DMIC_TX_STATUS:
	हाल TEGRA210_DMIC_TX_INT_STATUS:
	हाल TEGRA210_DMIC_TX_INT_SET:
	हाल TEGRA210_DMIC_SOFT_RESET:
	हाल TEGRA210_DMIC_STATUS:
	हाल TEGRA210_DMIC_INT_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config tegra210_dmic_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = TEGRA210_DMIC_LP_BIQUAD_1_COEF_4,
	.ग_लिखोable_reg = tegra210_dmic_wr_reg,
	.पढ़ोable_reg = tegra210_dmic_rd_reg,
	.अस्थिर_reg = tegra210_dmic_अस्थिर_reg,
	.reg_शेषs = tegra210_dmic_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(tegra210_dmic_reg_शेषs),
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक tegra210_dmic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा tegra210_dmic *dmic;
	व्योम __iomem *regs;
	पूर्णांक err;

	dmic = devm_kzalloc(dev, माप(*dmic), GFP_KERNEL);
	अगर (!dmic)
		वापस -ENOMEM;

	dmic->osr_val = DMIC_OSR_64;
	dmic->ch_select = DMIC_CH_SELECT_STEREO;
	dmic->lrsel = DMIC_LRSEL_LEFT;
	dmic->boost_gain = 0;
	dmic->stereo_to_mono = 0; /* "CH0" */

	dev_set_drvdata(dev, dmic);

	dmic->clk_dmic = devm_clk_get(dev, "dmic");
	अगर (IS_ERR(dmic->clk_dmic)) अणु
		dev_err(dev, "can't retrieve DMIC clock\n");
		वापस PTR_ERR(dmic->clk_dmic);
	पूर्ण

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	dmic->regmap = devm_regmap_init_mmio(dev, regs,
					     &tegra210_dmic_regmap_config);
	अगर (IS_ERR(dmic->regmap)) अणु
		dev_err(dev, "regmap init failed\n");
		वापस PTR_ERR(dmic->regmap);
	पूर्ण

	regcache_cache_only(dmic->regmap, true);

	err = devm_snd_soc_रेजिस्टर_component(dev, &tegra210_dmic_compnt,
					      tegra210_dmic_dais,
					      ARRAY_SIZE(tegra210_dmic_dais));
	अगर (err) अणु
		dev_err(dev, "can't register DMIC component, err: %d\n", err);
		वापस err;
	पूर्ण

	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra210_dmic_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra210_dmic_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra210_dmic_runसमय_suspend,
			   tegra210_dmic_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra210_dmic_of_match[] = अणु
	अणु .compatible = "nvidia,tegra210-dmic" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra210_dmic_of_match);

अटल काष्ठा platक्रमm_driver tegra210_dmic_driver = अणु
	.driver = अणु
		.name = "tegra210-dmic",
		.of_match_table = tegra210_dmic_of_match,
		.pm = &tegra210_dmic_pm_ops,
	पूर्ण,
	.probe = tegra210_dmic_probe,
	.हटाओ = tegra210_dmic_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra210_dmic_driver)

MODULE_AUTHOR("Rahul Mittal <rmittal@nvidia.com>");
MODULE_DESCRIPTION("Tegra210 ASoC DMIC driver");
MODULE_LICENSE("GPL v2");
