<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// tegra186_dspk.c - Tegra186 DSPK driver
//
// Copyright (c) 2020 NVIDIA CORPORATION. All rights reserved.

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश "tegra186_dspk.h"
#समावेश "tegra_cif.h"

अटल स्थिर काष्ठा reg_शेष tegra186_dspk_reg_शेषs[] = अणु
	अणु TEGRA186_DSPK_RX_INT_MASK, 0x00000007 पूर्ण,
	अणु TEGRA186_DSPK_RX_CIF_CTRL, 0x00007700 पूर्ण,
	अणु TEGRA186_DSPK_CG,	     0x00000001 पूर्ण,
	अणु TEGRA186_DSPK_CORE_CTRL,   0x00000310 पूर्ण,
	अणु TEGRA186_DSPK_CODEC_CTRL,  0x03000000 पूर्ण,
पूर्ण;

अटल पूर्णांक tegra186_dspk_get_control(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *codec = snd_soc_kcontrol_component(kcontrol);
	काष्ठा tegra186_dspk *dspk = snd_soc_component_get_drvdata(codec);

	अगर (म_माला(kcontrol->id.name, "FIFO Threshold"))
		ucontrol->value.पूर्णांकeger.value[0] = dspk->rx_fअगरo_th;
	अन्यथा अगर (म_माला(kcontrol->id.name, "OSR Value"))
		ucontrol->value.पूर्णांकeger.value[0] = dspk->osr_val;
	अन्यथा अगर (म_माला(kcontrol->id.name, "LR Polarity Select"))
		ucontrol->value.पूर्णांकeger.value[0] = dspk->lrsel;
	अन्यथा अगर (म_माला(kcontrol->id.name, "Channel Select"))
		ucontrol->value.पूर्णांकeger.value[0] = dspk->ch_sel;
	अन्यथा अगर (म_माला(kcontrol->id.name, "Mono To Stereo"))
		ucontrol->value.पूर्णांकeger.value[0] = dspk->mono_to_stereo;
	अन्यथा अगर (म_माला(kcontrol->id.name, "Stereo To Mono"))
		ucontrol->value.पूर्णांकeger.value[0] = dspk->stereo_to_mono;

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_dspk_put_control(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *codec = snd_soc_kcontrol_component(kcontrol);
	काष्ठा tegra186_dspk *dspk = snd_soc_component_get_drvdata(codec);
	पूर्णांक val = ucontrol->value.पूर्णांकeger.value[0];

	अगर (म_माला(kcontrol->id.name, "FIFO Threshold"))
		dspk->rx_fअगरo_th = val;
	अन्यथा अगर (म_माला(kcontrol->id.name, "OSR Value"))
		dspk->osr_val = val;
	अन्यथा अगर (म_माला(kcontrol->id.name, "LR Polarity Select"))
		dspk->lrsel = val;
	अन्यथा अगर (म_माला(kcontrol->id.name, "Channel Select"))
		dspk->ch_sel = val;
	अन्यथा अगर (म_माला(kcontrol->id.name, "Mono To Stereo"))
		dspk->mono_to_stereo = val;
	अन्यथा अगर (म_माला(kcontrol->id.name, "Stereo To Mono"))
		dspk->stereo_to_mono = val;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra186_dspk_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra186_dspk *dspk = dev_get_drvdata(dev);

	regcache_cache_only(dspk->regmap, true);
	regcache_mark_dirty(dspk->regmap);

	clk_disable_unprepare(dspk->clk_dspk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra186_dspk_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra186_dspk *dspk = dev_get_drvdata(dev);
	पूर्णांक err;

	err = clk_prepare_enable(dspk->clk_dspk);
	अगर (err) अणु
		dev_err(dev, "failed to enable DSPK clock, err: %d\n", err);
		वापस err;
	पूर्ण

	regcache_cache_only(dspk->regmap, false);
	regcache_sync(dspk->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_dspk_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा tegra186_dspk *dspk = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक channels, srate, dspk_clk;
	काष्ठा device *dev = dai->dev;
	काष्ठा tegra_cअगर_conf cअगर_conf;
	अचिन्हित पूर्णांक max_th;
	पूर्णांक err;

	स_रखो(&cअगर_conf, 0, माप(काष्ठा tegra_cअगर_conf));

	channels = params_channels(params);
	cअगर_conf.audio_ch = channels;

	/* Client channel */
	चयन (dspk->ch_sel) अणु
	हाल DSPK_CH_SELECT_LEFT:
	हाल DSPK_CH_SELECT_RIGHT:
		cअगर_conf.client_ch = 1;
		अवरोध;
	हाल DSPK_CH_SELECT_STEREO:
		cअगर_conf.client_ch = 2;
		अवरोध;
	शेष:
		dev_err(dev, "Invalid DSPK client channels\n");
		वापस -EINVAL;
	पूर्ण

	cअगर_conf.client_bits = TEGRA_ACIF_BITS_24;

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		cअगर_conf.audio_bits = TEGRA_ACIF_BITS_16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		cअगर_conf.audio_bits = TEGRA_ACIF_BITS_32;
		अवरोध;
	शेष:
		dev_err(dev, "unsupported format!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	srate = params_rate(params);

	/* RX FIFO threshold in terms of frames */
	max_th = (TEGRA186_DSPK_RX_FIFO_DEPTH / cअगर_conf.audio_ch) - 1;

	अगर (dspk->rx_fअगरo_th > max_th)
		dspk->rx_fअगरo_th = max_th;

	cअगर_conf.threshold = dspk->rx_fअगरo_th;
	cअगर_conf.mono_conv = dspk->mono_to_stereo;
	cअगर_conf.stereo_conv = dspk->stereo_to_mono;

	tegra_set_cअगर(dspk->regmap, TEGRA186_DSPK_RX_CIF_CTRL,
		      &cअगर_conf);

	/*
	 * DSPK घड़ी and PDM codec घड़ी should be synchronous with 4:1 ratio,
	 * this is because it takes 4 घड़ी cycles to send out one sample to
	 * codec by sigma delta modulator. Finally the घड़ी rate is a multiple
	 * of 'Over Sampling Ratio', 'Sample Rate' and 'Interface Clock Ratio'.
	 */
	dspk_clk = (DSPK_OSR_FACTOR << dspk->osr_val) * srate * DSPK_CLK_RATIO;

	err = clk_set_rate(dspk->clk_dspk, dspk_clk);
	अगर (err) अणु
		dev_err(dev, "can't set DSPK clock rate %u, err: %d\n",
			dspk_clk, err);

		वापस err;
	पूर्ण

	regmap_update_bits(dspk->regmap,
			   /* Reg */
			   TEGRA186_DSPK_CORE_CTRL,
			   /* Mask */
			   TEGRA186_DSPK_OSR_MASK |
			   TEGRA186_DSPK_CHANNEL_SELECT_MASK |
			   TEGRA186_DSPK_CTRL_LRSEL_POLARITY_MASK,
			   /* Value */
			   (dspk->osr_val << DSPK_OSR_SHIFT) |
			   ((dspk->ch_sel + 1) << CH_SEL_SHIFT) |
			   (dspk->lrsel << LRSEL_POL_SHIFT));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops tegra186_dspk_dai_ops = अणु
	.hw_params	= tegra186_dspk_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver tegra186_dspk_dais[] = अणु
	अणु
	    .name = "DSPK-CIF",
	    .playback = अणु
		.stream_name = "CIF-Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
			   SNDRV_PCM_FMTBIT_S32_LE,
	    पूर्ण,
	पूर्ण,
	अणु
	    .name = "DSPK-DAP",
	    .playback = अणु
		.stream_name = "DAP-Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
			   SNDRV_PCM_FMTBIT_S32_LE,
	    पूर्ण,
	    .ops = &tegra186_dspk_dai_ops,
	    .symmetric_rate = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tegra186_dspk_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("RX", शून्य, 0, TEGRA186_DSPK_ENABLE, 0, 0),
	SND_SOC_DAPM_SPK("SPK", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tegra186_dspk_routes[] = अणु
	अणु "XBAR-Playback",	शून्य,	"XBAR-TX" पूर्ण,
	अणु "CIF-Playback",	शून्य,	"XBAR-Playback" पूर्ण,
	अणु "RX",			शून्य,	"CIF-Playback" पूर्ण,
	अणु "DAP-Playback",	शून्य,	"RX" पूर्ण,
	अणु "SPK",		शून्य,	"DAP-Playback" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra186_dspk_ch_sel_text[] = अणु
	"Left", "Right", "Stereo",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत tegra186_dspk_ch_sel_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 0, ARRAY_SIZE(tegra186_dspk_ch_sel_text),
			tegra186_dspk_ch_sel_text);

अटल स्थिर अक्षर * स्थिर tegra186_dspk_osr_text[] = अणु
	"OSR_32", "OSR_64", "OSR_128", "OSR_256",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत tegra186_dspk_osr_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 0, ARRAY_SIZE(tegra186_dspk_osr_text),
			tegra186_dspk_osr_text);

अटल स्थिर अक्षर * स्थिर tegra186_dspk_lrsel_text[] = अणु
	"Left", "Right",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tegra186_dspk_mono_conv_text[] = अणु
	"Zero", "Copy",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत tegra186_dspk_mono_conv_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 0,
			ARRAY_SIZE(tegra186_dspk_mono_conv_text),
			tegra186_dspk_mono_conv_text);

अटल स्थिर अक्षर * स्थिर tegra186_dspk_stereo_conv_text[] = अणु
	"CH0", "CH1", "AVG",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत tegra186_dspk_stereo_conv_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 0,
			ARRAY_SIZE(tegra186_dspk_stereo_conv_text),
			tegra186_dspk_stereo_conv_text);

अटल स्थिर काष्ठा soc_क्रमागत tegra186_dspk_lrsel_क्रमागत =
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 0, ARRAY_SIZE(tegra186_dspk_lrsel_text),
			tegra186_dspk_lrsel_text);

अटल स्थिर काष्ठा snd_kcontrol_new tegrat186_dspk_controls[] = अणु
	SOC_SINGLE_EXT("FIFO Threshold", SND_SOC_NOPM, 0,
		       TEGRA186_DSPK_RX_FIFO_DEPTH - 1, 0,
		       tegra186_dspk_get_control, tegra186_dspk_put_control),
	SOC_ENUM_EXT("OSR Value", tegra186_dspk_osr_क्रमागत,
		     tegra186_dspk_get_control, tegra186_dspk_put_control),
	SOC_ENUM_EXT("LR Polarity Select", tegra186_dspk_lrsel_क्रमागत,
		     tegra186_dspk_get_control, tegra186_dspk_put_control),
	SOC_ENUM_EXT("Channel Select", tegra186_dspk_ch_sel_क्रमागत,
		     tegra186_dspk_get_control, tegra186_dspk_put_control),
	SOC_ENUM_EXT("Mono To Stereo", tegra186_dspk_mono_conv_क्रमागत,
		     tegra186_dspk_get_control, tegra186_dspk_put_control),
	SOC_ENUM_EXT("Stereo To Mono", tegra186_dspk_stereo_conv_क्रमागत,
		     tegra186_dspk_get_control, tegra186_dspk_put_control),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver tegra186_dspk_cmpnt = अणु
	.dapm_widमाला_लो = tegra186_dspk_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(tegra186_dspk_widमाला_लो),
	.dapm_routes = tegra186_dspk_routes,
	.num_dapm_routes = ARRAY_SIZE(tegra186_dspk_routes),
	.controls = tegrat186_dspk_controls,
	.num_controls = ARRAY_SIZE(tegrat186_dspk_controls),
पूर्ण;

अटल bool tegra186_dspk_wr_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA186_DSPK_RX_INT_MASK ... TEGRA186_DSPK_RX_CIF_CTRL:
	हाल TEGRA186_DSPK_ENABLE ... TEGRA186_DSPK_CG:
	हाल TEGRA186_DSPK_CORE_CTRL ... TEGRA186_DSPK_CODEC_CTRL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool tegra186_dspk_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (tegra186_dspk_wr_reg(dev, reg))
		वापस true;

	चयन (reg) अणु
	हाल TEGRA186_DSPK_RX_STATUS:
	हाल TEGRA186_DSPK_RX_INT_STATUS:
	हाल TEGRA186_DSPK_STATUS:
	हाल TEGRA186_DSPK_INT_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool tegra186_dspk_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TEGRA186_DSPK_RX_STATUS:
	हाल TEGRA186_DSPK_RX_INT_STATUS:
	हाल TEGRA186_DSPK_STATUS:
	हाल TEGRA186_DSPK_INT_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config tegra186_dspk_regmap = अणु
	.reg_bits		= 32,
	.reg_stride		= 4,
	.val_bits		= 32,
	.max_रेजिस्टर		= TEGRA186_DSPK_CODEC_CTRL,
	.ग_लिखोable_reg		= tegra186_dspk_wr_reg,
	.पढ़ोable_reg		= tegra186_dspk_rd_reg,
	.अस्थिर_reg		= tegra186_dspk_अस्थिर_reg,
	.reg_शेषs		= tegra186_dspk_reg_शेषs,
	.num_reg_शेषs	= ARRAY_SIZE(tegra186_dspk_reg_शेषs),
	.cache_type		= REGCACHE_FLAT,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra186_dspk_of_match[] = अणु
	अणु .compatible = "nvidia,tegra186-dspk" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra186_dspk_of_match);

अटल पूर्णांक tegra186_dspk_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा tegra186_dspk *dspk;
	व्योम __iomem *regs;
	पूर्णांक err;

	dspk = devm_kzalloc(dev, माप(*dspk), GFP_KERNEL);
	अगर (!dspk)
		वापस -ENOMEM;

	dspk->osr_val = DSPK_OSR_64;
	dspk->lrsel = DSPK_LRSEL_LEFT;
	dspk->ch_sel = DSPK_CH_SELECT_STEREO;
	dspk->mono_to_stereo = 0; /* "Zero" */

	dev_set_drvdata(dev, dspk);

	dspk->clk_dspk = devm_clk_get(dev, "dspk");
	अगर (IS_ERR(dspk->clk_dspk)) अणु
		dev_err(dev, "can't retrieve DSPK clock\n");
		वापस PTR_ERR(dspk->clk_dspk);
	पूर्ण

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	dspk->regmap = devm_regmap_init_mmio(dev, regs, &tegra186_dspk_regmap);
	अगर (IS_ERR(dspk->regmap)) अणु
		dev_err(dev, "regmap init failed\n");
		वापस PTR_ERR(dspk->regmap);
	पूर्ण

	regcache_cache_only(dspk->regmap, true);

	err = devm_snd_soc_रेजिस्टर_component(dev, &tegra186_dspk_cmpnt,
					      tegra186_dspk_dais,
					      ARRAY_SIZE(tegra186_dspk_dais));
	अगर (err) अणु
		dev_err(dev, "can't register DSPK component, err: %d\n",
			err);
		वापस err;
	पूर्ण

	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra186_dspk_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra186_dspk_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra186_dspk_runसमय_suspend,
			   tegra186_dspk_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra186_dspk_driver = अणु
	.driver = अणु
		.name = "tegra186-dspk",
		.of_match_table = tegra186_dspk_of_match,
		.pm = &tegra186_dspk_pm_ops,
	पूर्ण,
	.probe = tegra186_dspk_platक्रमm_probe,
	.हटाओ = tegra186_dspk_platक्रमm_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra186_dspk_driver);

MODULE_AUTHOR("Mohan Kumar <mkumard@nvidia.com>");
MODULE_AUTHOR("Sameer Pujar <spujar@nvidia.com>");
MODULE_DESCRIPTION("Tegra186 ASoC DSPK driver");
MODULE_LICENSE("GPL v2");
