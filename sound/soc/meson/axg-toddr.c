<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
//
// Copyright (c) 2018 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

/* This driver implements the frontend capture DAI of AXG based SoCs */

#समावेश <linux/clk.h>
#समावेश <linux/regmap.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश "axg-fifo.h"

#घोषणा CTRL0_TODDR_SEL_RESAMPLE	BIT(30)
#घोषणा CTRL0_TODDR_EXT_SIGNED		BIT(29)
#घोषणा CTRL0_TODDR_PP_MODE		BIT(28)
#घोषणा CTRL0_TODDR_SYNC_CH		BIT(27)
#घोषणा CTRL0_TODDR_TYPE_MASK		GENMASK(15, 13)
#घोषणा CTRL0_TODDR_TYPE(x)		((x) << 13)
#घोषणा CTRL0_TODDR_MSB_POS_MASK	GENMASK(12, 8)
#घोषणा CTRL0_TODDR_MSB_POS(x)		((x) << 8)
#घोषणा CTRL0_TODDR_LSB_POS_MASK	GENMASK(7, 3)
#घोषणा CTRL0_TODDR_LSB_POS(x)		((x) << 3)
#घोषणा CTRL1_TODDR_FORCE_FINISH	BIT(25)
#घोषणा CTRL1_SEL_SHIFT			28

#घोषणा TODDR_MSB_POS	31

अटल पूर्णांक axg_toddr_pcm_new(काष्ठा snd_soc_pcm_runसमय *rtd,
			     काष्ठा snd_soc_dai *dai)
अणु
	वापस axg_fअगरo_pcm_new(rtd, SNDRV_PCM_STREAM_CAPTURE);
पूर्ण

अटल पूर्णांक g12a_toddr_dai_prepare(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_fअगरo *fअगरo = snd_soc_dai_get_drvdata(dai);

	/* Reset the ग_लिखो poपूर्णांकer to the FIFO_INIT_ADDR */
	regmap_update_bits(fअगरo->map, FIFO_CTRL1,
			   CTRL1_TODDR_FORCE_FINISH, 0);
	regmap_update_bits(fअगरo->map, FIFO_CTRL1,
			   CTRL1_TODDR_FORCE_FINISH, CTRL1_TODDR_FORCE_FINISH);
	regmap_update_bits(fअगरo->map, FIFO_CTRL1,
			   CTRL1_TODDR_FORCE_FINISH, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक axg_toddr_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_fअगरo *fअगरo = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक type, width;

	चयन (params_physical_width(params)) अणु
	हाल 8:
		type = 0; /* 8 samples of 8 bits */
		अवरोध;
	हाल 16:
		type = 2; /* 4 samples of 16 bits - right justअगरied */
		अवरोध;
	हाल 32:
		type = 4; /* 2 samples of 32 bits - right justअगरied */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	width = params_width(params);

	regmap_update_bits(fअगरo->map, FIFO_CTRL0,
			   CTRL0_TODDR_TYPE_MASK |
			   CTRL0_TODDR_MSB_POS_MASK |
			   CTRL0_TODDR_LSB_POS_MASK,
			   CTRL0_TODDR_TYPE(type) |
			   CTRL0_TODDR_MSB_POS(TODDR_MSB_POS) |
			   CTRL0_TODDR_LSB_POS(TODDR_MSB_POS - (width - 1)));

	वापस 0;
पूर्ण

अटल पूर्णांक axg_toddr_dai_startup(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_fअगरo *fअगरo = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	/* Enable pclk to access रेजिस्टरs and घड़ी the fअगरo ip */
	ret = clk_prepare_enable(fअगरo->pclk);
	अगर (ret)
		वापस ret;

	/* Select orginal data - resampling not supported ATM */
	regmap_update_bits(fअगरo->map, FIFO_CTRL0, CTRL0_TODDR_SEL_RESAMPLE, 0);

	/* Only चिन्हित क्रमmat are supported ATM */
	regmap_update_bits(fअगरo->map, FIFO_CTRL0, CTRL0_TODDR_EXT_SIGNED,
			   CTRL0_TODDR_EXT_SIGNED);

	/* Apply single buffer mode to the पूर्णांकerface */
	regmap_update_bits(fअगरo->map, FIFO_CTRL0, CTRL0_TODDR_PP_MODE, 0);

	वापस 0;
पूर्ण

अटल व्योम axg_toddr_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_fअगरo *fअगरo = snd_soc_dai_get_drvdata(dai);

	clk_disable_unprepare(fअगरo->pclk);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops axg_toddr_ops = अणु
	.hw_params	= axg_toddr_dai_hw_params,
	.startup	= axg_toddr_dai_startup,
	.shutकरोwn	= axg_toddr_dai_shutकरोwn,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver axg_toddr_dai_drv = अणु
	.name = "TODDR",
	.capture = अणु
		.stream_name	= "Capture",
		.channels_min	= 1,
		.channels_max	= AXG_FIFO_CH_MAX,
		.rates		= AXG_FIFO_RATES,
		.क्रमmats	= AXG_FIFO_FORMATS,
	पूर्ण,
	.ops		= &axg_toddr_ops,
	.pcm_new	= axg_toddr_pcm_new,
पूर्ण;

अटल स्थिर अक्षर * स्थिर axg_toddr_sel_texts[] = अणु
	"IN 0", "IN 1", "IN 2", "IN 3", "IN 4", "IN 5", "IN 6", "IN 7"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(axg_toddr_sel_क्रमागत, FIFO_CTRL0, CTRL0_SEL_SHIFT,
			    axg_toddr_sel_texts);

अटल स्थिर काष्ठा snd_kcontrol_new axg_toddr_in_mux =
	SOC_DAPM_ENUM("Input Source", axg_toddr_sel_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget axg_toddr_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("SRC SEL", SND_SOC_NOPM, 0, 0, &axg_toddr_in_mux),
	SND_SOC_DAPM_AIF_IN("IN 0", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 1", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 2", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 3", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 4", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 5", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 6", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 7", शून्य, 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route axg_toddr_dapm_routes[] = अणु
	अणु "Capture", शून्य, "SRC SEL" पूर्ण,
	अणु "SRC SEL", "IN 0", "IN 0" पूर्ण,
	अणु "SRC SEL", "IN 1", "IN 1" पूर्ण,
	अणु "SRC SEL", "IN 2", "IN 2" पूर्ण,
	अणु "SRC SEL", "IN 3", "IN 3" पूर्ण,
	अणु "SRC SEL", "IN 4", "IN 4" पूर्ण,
	अणु "SRC SEL", "IN 5", "IN 5" पूर्ण,
	अणु "SRC SEL", "IN 6", "IN 6" पूर्ण,
	अणु "SRC SEL", "IN 7", "IN 7" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver axg_toddr_component_drv = अणु
	.dapm_widमाला_लो		= axg_toddr_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(axg_toddr_dapm_widमाला_लो),
	.dapm_routes		= axg_toddr_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(axg_toddr_dapm_routes),
	.खोलो			= axg_fअगरo_pcm_खोलो,
	.बंद			= axg_fअगरo_pcm_बंद,
	.hw_params		= axg_fअगरo_pcm_hw_params,
	.hw_मुक्त		= axg_fअगरo_pcm_hw_मुक्त,
	.poपूर्णांकer		= axg_fअगरo_pcm_poपूर्णांकer,
	.trigger		= axg_fअगरo_pcm_trigger,
पूर्ण;

अटल स्थिर काष्ठा axg_fअगरo_match_data axg_toddr_match_data = अणु
	.field_threshold	= REG_FIELD(FIFO_CTRL1, 16, 23),
	.component_drv		= &axg_toddr_component_drv,
	.dai_drv		= &axg_toddr_dai_drv
पूर्ण;

अटल पूर्णांक g12a_toddr_dai_startup(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_fअगरo *fअगरo = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	ret = axg_toddr_dai_startup(substream, dai);
	अगर (ret)
		वापस ret;

	/*
	 * Make sure the first channel ends up in the at beginning of the output
	 * As weird as it looks, without this the first channel may be misplaced
	 * in memory, with a अक्रमom shअगरt of 2 channels.
	 */
	regmap_update_bits(fअगरo->map, FIFO_CTRL0, CTRL0_TODDR_SYNC_CH,
			   CTRL0_TODDR_SYNC_CH);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops g12a_toddr_ops = अणु
	.prepare	= g12a_toddr_dai_prepare,
	.hw_params	= axg_toddr_dai_hw_params,
	.startup	= g12a_toddr_dai_startup,
	.shutकरोwn	= axg_toddr_dai_shutकरोwn,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver g12a_toddr_dai_drv = अणु
	.name = "TODDR",
	.capture = अणु
		.stream_name	= "Capture",
		.channels_min	= 1,
		.channels_max	= AXG_FIFO_CH_MAX,
		.rates		= AXG_FIFO_RATES,
		.क्रमmats	= AXG_FIFO_FORMATS,
	पूर्ण,
	.ops		= &g12a_toddr_ops,
	.pcm_new	= axg_toddr_pcm_new,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver g12a_toddr_component_drv = अणु
	.dapm_widमाला_लो		= axg_toddr_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(axg_toddr_dapm_widमाला_लो),
	.dapm_routes		= axg_toddr_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(axg_toddr_dapm_routes),
	.खोलो			= axg_fअगरo_pcm_खोलो,
	.बंद			= axg_fअगरo_pcm_बंद,
	.hw_params		= g12a_fअगरo_pcm_hw_params,
	.hw_मुक्त		= axg_fअगरo_pcm_hw_मुक्त,
	.poपूर्णांकer		= axg_fअगरo_pcm_poपूर्णांकer,
	.trigger		= axg_fअगरo_pcm_trigger,
पूर्ण;

अटल स्थिर काष्ठा axg_fअगरo_match_data g12a_toddr_match_data = अणु
	.field_threshold	= REG_FIELD(FIFO_CTRL1, 16, 23),
	.component_drv		= &g12a_toddr_component_drv,
	.dai_drv		= &g12a_toddr_dai_drv
पूर्ण;

अटल स्थिर अक्षर * स्थिर sm1_toddr_sel_texts[] = अणु
	"IN 0", "IN 1", "IN 2",  "IN 3",  "IN 4",  "IN 5",  "IN 6",  "IN 7",
	"IN 8", "IN 9", "IN 10", "IN 11", "IN 12", "IN 13", "IN 14", "IN 15"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(sm1_toddr_sel_क्रमागत, FIFO_CTRL1, CTRL1_SEL_SHIFT,
			    sm1_toddr_sel_texts);

अटल स्थिर काष्ठा snd_kcontrol_new sm1_toddr_in_mux =
	SOC_DAPM_ENUM("Input Source", sm1_toddr_sel_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget sm1_toddr_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("SRC SEL", SND_SOC_NOPM, 0, 0, &sm1_toddr_in_mux),
	SND_SOC_DAPM_AIF_IN("IN 0",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 1",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 2",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 3",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 4",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 5",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 6",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 7",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 8",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 9",  शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 10", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 11", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 12", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 13", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 14", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("IN 15", शून्य, 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sm1_toddr_dapm_routes[] = अणु
	अणु "Capture", शून्य, "SRC SEL" पूर्ण,
	अणु "SRC SEL", "IN 0",  "IN 0" पूर्ण,
	अणु "SRC SEL", "IN 1",  "IN 1" पूर्ण,
	अणु "SRC SEL", "IN 2",  "IN 2" पूर्ण,
	अणु "SRC SEL", "IN 3",  "IN 3" पूर्ण,
	अणु "SRC SEL", "IN 4",  "IN 4" पूर्ण,
	अणु "SRC SEL", "IN 5",  "IN 5" पूर्ण,
	अणु "SRC SEL", "IN 6",  "IN 6" पूर्ण,
	अणु "SRC SEL", "IN 7",  "IN 7" पूर्ण,
	अणु "SRC SEL", "IN 8",  "IN 8" पूर्ण,
	अणु "SRC SEL", "IN 9",  "IN 9" पूर्ण,
	अणु "SRC SEL", "IN 10", "IN 10" पूर्ण,
	अणु "SRC SEL", "IN 11", "IN 11" पूर्ण,
	अणु "SRC SEL", "IN 12", "IN 12" पूर्ण,
	अणु "SRC SEL", "IN 13", "IN 13" पूर्ण,
	अणु "SRC SEL", "IN 14", "IN 14" पूर्ण,
	अणु "SRC SEL", "IN 15", "IN 15" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver sm1_toddr_component_drv = अणु
	.dapm_widमाला_लो		= sm1_toddr_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(sm1_toddr_dapm_widमाला_लो),
	.dapm_routes		= sm1_toddr_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(sm1_toddr_dapm_routes),
	.खोलो			= axg_fअगरo_pcm_खोलो,
	.बंद			= axg_fअगरo_pcm_बंद,
	.hw_params		= g12a_fअगरo_pcm_hw_params,
	.hw_मुक्त		= axg_fअगरo_pcm_hw_मुक्त,
	.poपूर्णांकer		= axg_fअगरo_pcm_poपूर्णांकer,
	.trigger		= axg_fअगरo_pcm_trigger,
पूर्ण;

अटल स्थिर काष्ठा axg_fअगरo_match_data sm1_toddr_match_data = अणु
	.field_threshold	= REG_FIELD(FIFO_CTRL1, 12, 23),
	.component_drv		= &sm1_toddr_component_drv,
	.dai_drv		= &g12a_toddr_dai_drv
पूर्ण;

अटल स्थिर काष्ठा of_device_id axg_toddr_of_match[] = अणु
	अणु
		.compatible = "amlogic,axg-toddr",
		.data = &axg_toddr_match_data,
	पूर्ण, अणु
		.compatible = "amlogic,g12a-toddr",
		.data = &g12a_toddr_match_data,
	पूर्ण, अणु
		.compatible = "amlogic,sm1-toddr",
		.data = &sm1_toddr_match_data,
	पूर्ण, अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, axg_toddr_of_match);

अटल काष्ठा platक्रमm_driver axg_toddr_pdrv = अणु
	.probe = axg_fअगरo_probe,
	.driver = अणु
		.name = "axg-toddr",
		.of_match_table = axg_toddr_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(axg_toddr_pdrv);

MODULE_DESCRIPTION("Amlogic AXG capture fifo driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
