<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2020 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश <dt-bindings/sound/meson-aiu.h>
#समावेश "aiu.h"
#समावेश "aiu-fifo.h"

#घोषणा AIU_I2S_MISC_958_SRC_SHIFT 3

अटल स्थिर अक्षर * स्थिर aiu_spdअगर_encode_sel_texts[] = अणु
	"SPDIF", "I2S",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(aiu_spdअगर_encode_sel_क्रमागत, AIU_I2S_MISC,
			    AIU_I2S_MISC_958_SRC_SHIFT,
			    aiu_spdअगर_encode_sel_texts);

अटल स्थिर काष्ठा snd_kcontrol_new aiu_spdअगर_encode_mux =
	SOC_DAPM_ENUM("SPDIF Buffer Src", aiu_spdअगर_encode_sel_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget aiu_cpu_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("SPDIF SRC SEL", SND_SOC_NOPM, 0, 0,
			 &aiu_spdअगर_encode_mux),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route aiu_cpu_dapm_routes[] = अणु
	अणु "I2S Encoder Playback", शून्य, "I2S FIFO Playback" पूर्ण,
	अणु "SPDIF SRC SEL", "SPDIF", "SPDIF FIFO Playback" पूर्ण,
	अणु "SPDIF SRC SEL", "I2S", "I2S FIFO Playback" पूर्ण,
	अणु "SPDIF Encoder Playback", शून्य, "SPDIF SRC SEL" पूर्ण,
पूर्ण;

पूर्णांक aiu_of_xlate_dai_name(काष्ठा snd_soc_component *component,
			  स्थिर काष्ठा of_phandle_args *args,
			  स्थिर अक्षर **dai_name,
			  अचिन्हित पूर्णांक component_id)
अणु
	काष्ठा snd_soc_dai *dai;
	पूर्णांक id;

	अगर (args->args_count != 2)
		वापस -EINVAL;

	अगर (args->args[0] != component_id)
		वापस -EINVAL;

	id = args->args[1];

	अगर (id < 0 || id >= component->num_dai)
		वापस -EINVAL;

	क्रम_each_component_dais(component, dai) अणु
		अगर (id == 0)
			अवरोध;
		id--;
	पूर्ण

	*dai_name = dai->driver->name;

	वापस 0;
पूर्ण

अटल पूर्णांक aiu_cpu_of_xlate_dai_name(काष्ठा snd_soc_component *component,
				     स्थिर काष्ठा of_phandle_args *args,
				     स्थिर अक्षर **dai_name)
अणु
	वापस aiu_of_xlate_dai_name(component, args, dai_name, AIU_CPU);
पूर्ण

अटल पूर्णांक aiu_cpu_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा aiu *aiu = snd_soc_component_get_drvdata(component);

	/* Required क्रम the SPDIF Source control operation */
	वापस clk_prepare_enable(aiu->i2s.clks[PCLK].clk);
पूर्ण

अटल व्योम aiu_cpu_component_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा aiu *aiu = snd_soc_component_get_drvdata(component);

	clk_disable_unprepare(aiu->i2s.clks[PCLK].clk);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver aiu_cpu_component = अणु
	.name			= "AIU CPU",
	.dapm_widमाला_लो		= aiu_cpu_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(aiu_cpu_dapm_widमाला_लो),
	.dapm_routes		= aiu_cpu_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(aiu_cpu_dapm_routes),
	.of_xlate_dai_name	= aiu_cpu_of_xlate_dai_name,
	.poपूर्णांकer		= aiu_fअगरo_poपूर्णांकer,
	.probe			= aiu_cpu_component_probe,
	.हटाओ			= aiu_cpu_component_हटाओ,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver aiu_cpu_dai_drv[] = अणु
	[CPU_I2S_FIFO] = अणु
		.name = "I2S FIFO",
		.playback = अणु
			.stream_name	= "I2S FIFO Playback",
			.channels_min	= 2,
			.channels_max	= 8,
			.rates		= SNDRV_PCM_RATE_CONTINUOUS,
			.rate_min	= 5512,
			.rate_max	= 192000,
			.क्रमmats	= AIU_FORMATS,
		पूर्ण,
		.ops		= &aiu_fअगरo_i2s_dai_ops,
		.pcm_new	= aiu_fअगरo_pcm_new,
		.probe		= aiu_fअगरo_i2s_dai_probe,
		.हटाओ		= aiu_fअगरo_dai_हटाओ,
	पूर्ण,
	[CPU_SPDIF_FIFO] = अणु
		.name = "SPDIF FIFO",
		.playback = अणु
			.stream_name	= "SPDIF FIFO Playback",
			.channels_min	= 2,
			.channels_max	= 2,
			.rates		= SNDRV_PCM_RATE_CONTINUOUS,
			.rate_min	= 5512,
			.rate_max	= 192000,
			.क्रमmats	= AIU_FORMATS,
		पूर्ण,
		.ops		= &aiu_fअगरo_spdअगर_dai_ops,
		.pcm_new	= aiu_fअगरo_pcm_new,
		.probe		= aiu_fअगरo_spdअगर_dai_probe,
		.हटाओ		= aiu_fअगरo_dai_हटाओ,
	पूर्ण,
	[CPU_I2S_ENCODER] = अणु
		.name = "I2S Encoder",
		.playback = अणु
			.stream_name = "I2S Encoder Playback",
			.channels_min = 2,
			.channels_max = 8,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = AIU_FORMATS,
		पूर्ण,
		.ops = &aiu_encoder_i2s_dai_ops,
	पूर्ण,
	[CPU_SPDIF_ENCODER] = अणु
		.name = "SPDIF Encoder",
		.playback = अणु
			.stream_name = "SPDIF Encoder Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = (SNDRV_PCM_RATE_32000  |
				  SNDRV_PCM_RATE_44100  |
				  SNDRV_PCM_RATE_48000  |
				  SNDRV_PCM_RATE_88200  |
				  SNDRV_PCM_RATE_96000  |
				  SNDRV_PCM_RATE_176400 |
				  SNDRV_PCM_RATE_192000),
			.क्रमmats = AIU_FORMATS,
		पूर्ण,
		.ops = &aiu_encoder_spdअगर_dai_ops,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा regmap_config aiu_regmap_cfg = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= 0x2ac,
पूर्ण;

अटल पूर्णांक aiu_clk_bulk_get(काष्ठा device *dev,
			    स्थिर अक्षर * स्थिर *ids,
			    अचिन्हित पूर्णांक num,
			    काष्ठा aiu_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा clk_bulk_data *clks;
	पूर्णांक i, ret;

	clks = devm_kसुस्मृति(dev, num, माप(*clks), GFP_KERNEL);
	अगर (!clks)
		वापस -ENOMEM;

	क्रम (i = 0; i < num; i++)
		clks[i].id = ids[i];

	ret = devm_clk_bulk_get(dev, num, clks);
	अगर (ret < 0)
		वापस ret;

	पूर्णांकerface->clks = clks;
	पूर्णांकerface->clk_num = num;
	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर aiu_i2s_ids[] = अणु
	[PCLK]	= "i2s_pclk",
	[AOCLK]	= "i2s_aoclk",
	[MCLK]	= "i2s_mclk",
	[MIXER]	= "i2s_mixer",
पूर्ण;

अटल स्थिर अक्षर * स्थिर aiu_spdअगर_ids[] = अणु
	[PCLK]	= "spdif_pclk",
	[AOCLK]	= "spdif_aoclk",
	[MCLK]	= "spdif_mclk_sel"
पूर्ण;

अटल पूर्णांक aiu_clk_get(काष्ठा device *dev)
अणु
	काष्ठा aiu *aiu = dev_get_drvdata(dev);
	पूर्णांक ret;

	aiu->pclk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(aiu->pclk)) अणु
		अगर (PTR_ERR(aiu->pclk) != -EPROBE_DEFER)
			dev_err(dev, "Can't get the aiu pclk\n");
		वापस PTR_ERR(aiu->pclk);
	पूर्ण

	aiu->spdअगर_mclk = devm_clk_get(dev, "spdif_mclk");
	अगर (IS_ERR(aiu->spdअगर_mclk)) अणु
		अगर (PTR_ERR(aiu->spdअगर_mclk) != -EPROBE_DEFER)
			dev_err(dev, "Can't get the aiu spdif master clock\n");
		वापस PTR_ERR(aiu->spdअगर_mclk);
	पूर्ण

	ret = aiu_clk_bulk_get(dev, aiu_i2s_ids, ARRAY_SIZE(aiu_i2s_ids),
			       &aiu->i2s);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Can't get the i2s clocks\n");
		वापस ret;
	पूर्ण

	ret = aiu_clk_bulk_get(dev, aiu_spdअगर_ids, ARRAY_SIZE(aiu_spdअगर_ids),
			       &aiu->spdअगर);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Can't get the spdif clocks\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(aiu->pclk);
	अगर (ret) अणु
		dev_err(dev, "peripheral clock enable failed\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev,
				       (व्योम(*)(व्योम *))clk_disable_unprepare,
				       aiu->pclk);
	अगर (ret)
		dev_err(dev, "failed to add reset action on pclk");

	वापस ret;
पूर्ण

अटल पूर्णांक aiu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem *regs;
	काष्ठा regmap *map;
	काष्ठा aiu *aiu;
	पूर्णांक ret;

	aiu = devm_kzalloc(dev, माप(*aiu), GFP_KERNEL);
	अगर (!aiu)
		वापस -ENOMEM;

	aiu->platक्रमm = device_get_match_data(dev);
	अगर (!aiu->platक्रमm)
		वापस -ENODEV;

	platक्रमm_set_drvdata(pdev, aiu);

	ret = device_reset(dev);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to reset device\n");
		वापस ret;
	पूर्ण

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	map = devm_regmap_init_mmio(dev, regs, &aiu_regmap_cfg);
	अगर (IS_ERR(map)) अणु
		dev_err(dev, "failed to init regmap: %ld\n",
			PTR_ERR(map));
		वापस PTR_ERR(map);
	पूर्ण

	aiu->i2s.irq = platक्रमm_get_irq_byname(pdev, "i2s");
	अगर (aiu->i2s.irq < 0)
		वापस aiu->i2s.irq;

	aiu->spdअगर.irq = platक्रमm_get_irq_byname(pdev, "spdif");
	अगर (aiu->spdअगर.irq < 0)
		वापस aiu->spdअगर.irq;

	ret = aiu_clk_get(dev);
	अगर (ret)
		वापस ret;

	/* Register the cpu component of the aiu */
	ret = snd_soc_रेजिस्टर_component(dev, &aiu_cpu_component,
					 aiu_cpu_dai_drv,
					 ARRAY_SIZE(aiu_cpu_dai_drv));
	अगर (ret) अणु
		dev_err(dev, "Failed to register cpu component\n");
		वापस ret;
	पूर्ण

	/* Register the hdmi codec control component */
	ret = aiu_hdmi_ctrl_रेजिस्टर_component(dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register hdmi control component\n");
		जाओ err;
	पूर्ण

	/* Register the पूर्णांकernal dac control component on gxl */
	अगर (aiu->platक्रमm->has_acodec) अणु
		ret = aiu_acodec_ctrl_रेजिस्टर_component(dev);
		अगर (ret) अणु
			dev_err(dev,
			    "Failed to register acodec control component\n");
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	snd_soc_unरेजिस्टर_component(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक aiu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	snd_soc_unरेजिस्टर_component(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा aiu_platक्रमm_data aiu_gxbb_pdata = अणु
	.has_acodec = false,
	.has_clk_ctrl_more_i2s_भाग = true,
पूर्ण;

अटल स्थिर काष्ठा aiu_platक्रमm_data aiu_gxl_pdata = अणु
	.has_acodec = true,
	.has_clk_ctrl_more_i2s_भाग = true,
पूर्ण;

अटल स्थिर काष्ठा aiu_platक्रमm_data aiu_meson8_pdata = अणु
	.has_acodec = false,
	.has_clk_ctrl_more_i2s_भाग = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aiu_of_match[] = अणु
	अणु .compatible = "amlogic,aiu-gxbb", .data = &aiu_gxbb_pdata पूर्ण,
	अणु .compatible = "amlogic,aiu-gxl", .data = &aiu_gxl_pdata पूर्ण,
	अणु .compatible = "amlogic,aiu-meson8", .data = &aiu_meson8_pdata पूर्ण,
	अणु .compatible = "amlogic,aiu-meson8b", .data = &aiu_meson8_pdata पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aiu_of_match);

अटल काष्ठा platक्रमm_driver aiu_pdrv = अणु
	.probe = aiu_probe,
	.हटाओ = aiu_हटाओ,
	.driver = अणु
		.name = "meson-aiu",
		.of_match_table = aiu_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(aiu_pdrv);

MODULE_DESCRIPTION("Meson AIU Driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
