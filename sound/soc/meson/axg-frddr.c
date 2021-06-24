<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
//
// Copyright (c) 2018 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

/*
 * This driver implements the frontend playback DAI of AXG and G12A based SoCs
 */

#समावेश <linux/clk.h>
#समावेश <linux/regmap.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश "axg-fifo.h"

#घोषणा CTRL0_FRDDR_PP_MODE		BIT(30)
#घोषणा CTRL0_SEL1_EN_SHIFT		3
#घोषणा CTRL0_SEL2_SHIFT		4
#घोषणा CTRL0_SEL2_EN_SHIFT		7
#घोषणा CTRL0_SEL3_SHIFT		8
#घोषणा CTRL0_SEL3_EN_SHIFT		11
#घोषणा CTRL1_FRDDR_FORCE_FINISH	BIT(12)
#घोषणा CTRL2_SEL1_SHIFT		0
#घोषणा CTRL2_SEL1_EN_SHIFT		4
#घोषणा CTRL2_SEL2_SHIFT		8
#घोषणा CTRL2_SEL2_EN_SHIFT		12
#घोषणा CTRL2_SEL3_SHIFT		16
#घोषणा CTRL2_SEL3_EN_SHIFT		20

अटल पूर्णांक g12a_frddr_dai_prepare(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_fअगरo *fअगरo = snd_soc_dai_get_drvdata(dai);

	/* Reset the पढ़ो poपूर्णांकer to the FIFO_INIT_ADDR */
	regmap_update_bits(fअगरo->map, FIFO_CTRL1,
			   CTRL1_FRDDR_FORCE_FINISH, 0);
	regmap_update_bits(fअगरo->map, FIFO_CTRL1,
			   CTRL1_FRDDR_FORCE_FINISH, CTRL1_FRDDR_FORCE_FINISH);
	regmap_update_bits(fअगरo->map, FIFO_CTRL1,
			   CTRL1_FRDDR_FORCE_FINISH, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक axg_frddr_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_fअगरo *fअगरo = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक period, depth, val;

	period = params_period_bytes(params);

	/* Trim the FIFO depth अगर the period is small to improve latency */
	depth = min(period, fअगरo->depth);
	val = (depth / AXG_FIFO_BURST) - 1;
	regmap_update_bits(fअगरo->map, FIFO_CTRL1, CTRL1_FRDDR_DEPTH_MASK,
			   CTRL1_FRDDR_DEPTH(val));

	वापस 0;
पूर्ण

अटल पूर्णांक axg_frddr_dai_startup(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_fअगरo *fअगरo = snd_soc_dai_get_drvdata(dai);
	पूर्णांक ret;

	/* Enable pclk to access रेजिस्टरs and घड़ी the fअगरo ip */
	ret = clk_prepare_enable(fअगरo->pclk);
	अगर (ret)
		वापस ret;

	/* Apply single buffer mode to the पूर्णांकerface */
	regmap_update_bits(fअगरo->map, FIFO_CTRL0, CTRL0_FRDDR_PP_MODE, 0);

	वापस 0;
पूर्ण

अटल व्योम axg_frddr_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा axg_fअगरo *fअगरo = snd_soc_dai_get_drvdata(dai);

	clk_disable_unprepare(fअगरo->pclk);
पूर्ण

अटल पूर्णांक axg_frddr_pcm_new(काष्ठा snd_soc_pcm_runसमय *rtd,
			     काष्ठा snd_soc_dai *dai)
अणु
	वापस axg_fअगरo_pcm_new(rtd, SNDRV_PCM_STREAM_PLAYBACK);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops axg_frddr_ops = अणु
	.hw_params	= axg_frddr_dai_hw_params,
	.startup	= axg_frddr_dai_startup,
	.shutकरोwn	= axg_frddr_dai_shutकरोwn,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver axg_frddr_dai_drv = अणु
	.name = "FRDDR",
	.playback = अणु
		.stream_name	= "Playback",
		.channels_min	= 1,
		.channels_max	= AXG_FIFO_CH_MAX,
		.rates		= AXG_FIFO_RATES,
		.क्रमmats	= AXG_FIFO_FORMATS,
	पूर्ण,
	.ops		= &axg_frddr_ops,
	.pcm_new	= axg_frddr_pcm_new,
पूर्ण;

अटल स्थिर अक्षर * स्थिर axg_frddr_sel_texts[] = अणु
	"OUT 0", "OUT 1", "OUT 2", "OUT 3", "OUT 4", "OUT 5", "OUT 6", "OUT 7",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(axg_frddr_sel_क्रमागत, FIFO_CTRL0, CTRL0_SEL_SHIFT,
			    axg_frddr_sel_texts);

अटल स्थिर काष्ठा snd_kcontrol_new axg_frddr_out_demux =
	SOC_DAPM_ENUM("Output Sink", axg_frddr_sel_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget axg_frddr_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DEMUX("SINK SEL", SND_SOC_NOPM, 0, 0,
			   &axg_frddr_out_demux),
	SND_SOC_DAPM_AIF_OUT("OUT 0", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 1", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 2", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 3", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 4", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 5", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 6", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 7", शून्य, 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route axg_frddr_dapm_routes[] = अणु
	अणु "SINK SEL", शून्य, "Playback" पूर्ण,
	अणु "OUT 0", "OUT 0",  "SINK SEL" पूर्ण,
	अणु "OUT 1", "OUT 1",  "SINK SEL" पूर्ण,
	अणु "OUT 2", "OUT 2",  "SINK SEL" पूर्ण,
	अणु "OUT 3", "OUT 3",  "SINK SEL" पूर्ण,
	अणु "OUT 4", "OUT 4",  "SINK SEL" पूर्ण,
	अणु "OUT 5", "OUT 5",  "SINK SEL" पूर्ण,
	अणु "OUT 6", "OUT 6",  "SINK SEL" पूर्ण,
	अणु "OUT 7", "OUT 7",  "SINK SEL" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver axg_frddr_component_drv = अणु
	.dapm_widमाला_लो		= axg_frddr_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(axg_frddr_dapm_widमाला_लो),
	.dapm_routes		= axg_frddr_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(axg_frddr_dapm_routes),
	.खोलो			= axg_fअगरo_pcm_खोलो,
	.बंद			= axg_fअगरo_pcm_बंद,
	.hw_params		= axg_fअगरo_pcm_hw_params,
	.hw_मुक्त		= axg_fअगरo_pcm_hw_मुक्त,
	.poपूर्णांकer		= axg_fअगरo_pcm_poपूर्णांकer,
	.trigger		= axg_fअगरo_pcm_trigger,
पूर्ण;

अटल स्थिर काष्ठा axg_fअगरo_match_data axg_frddr_match_data = अणु
	.field_threshold	= REG_FIELD(FIFO_CTRL1, 16, 23),
	.component_drv		= &axg_frddr_component_drv,
	.dai_drv		= &axg_frddr_dai_drv
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops g12a_frddr_ops = अणु
	.prepare	= g12a_frddr_dai_prepare,
	.hw_params	= axg_frddr_dai_hw_params,
	.startup	= axg_frddr_dai_startup,
	.shutकरोwn	= axg_frddr_dai_shutकरोwn,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver g12a_frddr_dai_drv = अणु
	.name = "FRDDR",
	.playback = अणु
		.stream_name	= "Playback",
		.channels_min	= 1,
		.channels_max	= AXG_FIFO_CH_MAX,
		.rates		= AXG_FIFO_RATES,
		.क्रमmats	= AXG_FIFO_FORMATS,
	पूर्ण,
	.ops		= &g12a_frddr_ops,
	.pcm_new	= axg_frddr_pcm_new,
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(g12a_frddr_sel1_क्रमागत, FIFO_CTRL0, CTRL0_SEL_SHIFT,
			    axg_frddr_sel_texts);
अटल SOC_ENUM_SINGLE_DECL(g12a_frddr_sel2_क्रमागत, FIFO_CTRL0, CTRL0_SEL2_SHIFT,
			    axg_frddr_sel_texts);
अटल SOC_ENUM_SINGLE_DECL(g12a_frddr_sel3_क्रमागत, FIFO_CTRL0, CTRL0_SEL3_SHIFT,
			    axg_frddr_sel_texts);

अटल स्थिर काष्ठा snd_kcontrol_new g12a_frddr_out1_demux =
	SOC_DAPM_ENUM("Output Src 1", g12a_frddr_sel1_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new g12a_frddr_out2_demux =
	SOC_DAPM_ENUM("Output Src 2", g12a_frddr_sel2_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new g12a_frddr_out3_demux =
	SOC_DAPM_ENUM("Output Src 3", g12a_frddr_sel3_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new g12a_frddr_out1_enable =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", FIFO_CTRL0,
				    CTRL0_SEL1_EN_SHIFT, 1, 0);
अटल स्थिर काष्ठा snd_kcontrol_new g12a_frddr_out2_enable =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", FIFO_CTRL0,
				    CTRL0_SEL2_EN_SHIFT, 1, 0);
अटल स्थिर काष्ठा snd_kcontrol_new g12a_frddr_out3_enable =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", FIFO_CTRL0,
				    CTRL0_SEL3_EN_SHIFT, 1, 0);

अटल स्थिर काष्ठा snd_soc_dapm_widget g12a_frddr_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_OUT("SRC 1", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SRC 2", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SRC 3", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SWITCH("SRC 1 EN", SND_SOC_NOPM, 0, 0,
			    &g12a_frddr_out1_enable),
	SND_SOC_DAPM_SWITCH("SRC 2 EN", SND_SOC_NOPM, 0, 0,
			    &g12a_frddr_out2_enable),
	SND_SOC_DAPM_SWITCH("SRC 3 EN", SND_SOC_NOPM, 0, 0,
			    &g12a_frddr_out3_enable),
	SND_SOC_DAPM_DEMUX("SINK 1 SEL", SND_SOC_NOPM, 0, 0,
			   &g12a_frddr_out1_demux),
	SND_SOC_DAPM_DEMUX("SINK 2 SEL", SND_SOC_NOPM, 0, 0,
			   &g12a_frddr_out2_demux),
	SND_SOC_DAPM_DEMUX("SINK 3 SEL", SND_SOC_NOPM, 0, 0,
			   &g12a_frddr_out3_demux),
	SND_SOC_DAPM_AIF_OUT("OUT 0", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 1", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 2", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 3", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 4", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 5", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 6", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 7", शून्य, 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route g12a_frddr_dapm_routes[] = अणु
	अणु "SRC 1", शून्य, "Playback" पूर्ण,
	अणु "SRC 2", शून्य, "Playback" पूर्ण,
	अणु "SRC 3", शून्य, "Playback" पूर्ण,
	अणु "SRC 1 EN", "Switch", "SRC 1" पूर्ण,
	अणु "SRC 2 EN", "Switch", "SRC 2" पूर्ण,
	अणु "SRC 3 EN", "Switch", "SRC 3" पूर्ण,
	अणु "SINK 1 SEL", शून्य, "SRC 1 EN" पूर्ण,
	अणु "SINK 2 SEL", शून्य, "SRC 2 EN" पूर्ण,
	अणु "SINK 3 SEL", शून्य, "SRC 3 EN" पूर्ण,
	अणु "OUT 0", "OUT 0", "SINK 1 SEL" पूर्ण,
	अणु "OUT 1", "OUT 1", "SINK 1 SEL" पूर्ण,
	अणु "OUT 2", "OUT 2", "SINK 1 SEL" पूर्ण,
	अणु "OUT 3", "OUT 3", "SINK 1 SEL" पूर्ण,
	अणु "OUT 4", "OUT 4", "SINK 1 SEL" पूर्ण,
	अणु "OUT 5", "OUT 5", "SINK 1 SEL" पूर्ण,
	अणु "OUT 6", "OUT 6", "SINK 1 SEL" पूर्ण,
	अणु "OUT 7", "OUT 7", "SINK 1 SEL" पूर्ण,
	अणु "OUT 0", "OUT 0", "SINK 2 SEL" पूर्ण,
	अणु "OUT 1", "OUT 1", "SINK 2 SEL" पूर्ण,
	अणु "OUT 2", "OUT 2", "SINK 2 SEL" पूर्ण,
	अणु "OUT 3", "OUT 3", "SINK 2 SEL" पूर्ण,
	अणु "OUT 4", "OUT 4", "SINK 2 SEL" पूर्ण,
	अणु "OUT 5", "OUT 5", "SINK 2 SEL" पूर्ण,
	अणु "OUT 6", "OUT 6", "SINK 2 SEL" पूर्ण,
	अणु "OUT 7", "OUT 7", "SINK 2 SEL" पूर्ण,
	अणु "OUT 0", "OUT 0", "SINK 3 SEL" पूर्ण,
	अणु "OUT 1", "OUT 1", "SINK 3 SEL" पूर्ण,
	अणु "OUT 2", "OUT 2", "SINK 3 SEL" पूर्ण,
	अणु "OUT 3", "OUT 3", "SINK 3 SEL" पूर्ण,
	अणु "OUT 4", "OUT 4", "SINK 3 SEL" पूर्ण,
	अणु "OUT 5", "OUT 5", "SINK 3 SEL" पूर्ण,
	अणु "OUT 6", "OUT 6", "SINK 3 SEL" पूर्ण,
	अणु "OUT 7", "OUT 7", "SINK 3 SEL" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver g12a_frddr_component_drv = अणु
	.dapm_widमाला_लो		= g12a_frddr_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(g12a_frddr_dapm_widमाला_लो),
	.dapm_routes		= g12a_frddr_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(g12a_frddr_dapm_routes),
	.खोलो			= axg_fअगरo_pcm_खोलो,
	.बंद			= axg_fअगरo_pcm_बंद,
	.hw_params		= g12a_fअगरo_pcm_hw_params,
	.hw_मुक्त		= axg_fअगरo_pcm_hw_मुक्त,
	.poपूर्णांकer		= axg_fअगरo_pcm_poपूर्णांकer,
	.trigger		= axg_fअगरo_pcm_trigger,
पूर्ण;

अटल स्थिर काष्ठा axg_fअगरo_match_data g12a_frddr_match_data = अणु
	.field_threshold	= REG_FIELD(FIFO_CTRL1, 16, 23),
	.component_drv		= &g12a_frddr_component_drv,
	.dai_drv		= &g12a_frddr_dai_drv
पूर्ण;

/* On SM1, the output selection in on CTRL2 */
अटल स्थिर काष्ठा snd_kcontrol_new sm1_frddr_out1_enable =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", FIFO_CTRL2,
				    CTRL2_SEL1_EN_SHIFT, 1, 0);
अटल स्थिर काष्ठा snd_kcontrol_new sm1_frddr_out2_enable =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", FIFO_CTRL2,
				    CTRL2_SEL2_EN_SHIFT, 1, 0);
अटल स्थिर काष्ठा snd_kcontrol_new sm1_frddr_out3_enable =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", FIFO_CTRL2,
				    CTRL2_SEL3_EN_SHIFT, 1, 0);

अटल SOC_ENUM_SINGLE_DECL(sm1_frddr_sel1_क्रमागत, FIFO_CTRL2, CTRL2_SEL1_SHIFT,
			    axg_frddr_sel_texts);
अटल SOC_ENUM_SINGLE_DECL(sm1_frddr_sel2_क्रमागत, FIFO_CTRL2, CTRL2_SEL2_SHIFT,
			    axg_frddr_sel_texts);
अटल SOC_ENUM_SINGLE_DECL(sm1_frddr_sel3_क्रमागत, FIFO_CTRL2, CTRL2_SEL3_SHIFT,
			    axg_frddr_sel_texts);

अटल स्थिर काष्ठा snd_kcontrol_new sm1_frddr_out1_demux =
	SOC_DAPM_ENUM("Output Src 1", sm1_frddr_sel1_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new sm1_frddr_out2_demux =
	SOC_DAPM_ENUM("Output Src 2", sm1_frddr_sel2_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new sm1_frddr_out3_demux =
	SOC_DAPM_ENUM("Output Src 3", sm1_frddr_sel3_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget sm1_frddr_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_OUT("SRC 1", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SRC 2", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SRC 3", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SWITCH("SRC 1 EN", SND_SOC_NOPM, 0, 0,
			    &sm1_frddr_out1_enable),
	SND_SOC_DAPM_SWITCH("SRC 2 EN", SND_SOC_NOPM, 0, 0,
			    &sm1_frddr_out2_enable),
	SND_SOC_DAPM_SWITCH("SRC 3 EN", SND_SOC_NOPM, 0, 0,
			    &sm1_frddr_out3_enable),
	SND_SOC_DAPM_DEMUX("SINK 1 SEL", SND_SOC_NOPM, 0, 0,
			   &sm1_frddr_out1_demux),
	SND_SOC_DAPM_DEMUX("SINK 2 SEL", SND_SOC_NOPM, 0, 0,
			   &sm1_frddr_out2_demux),
	SND_SOC_DAPM_DEMUX("SINK 3 SEL", SND_SOC_NOPM, 0, 0,
			   &sm1_frddr_out3_demux),
	SND_SOC_DAPM_AIF_OUT("OUT 0", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 1", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 2", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 3", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 4", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 5", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 6", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("OUT 7", शून्य, 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver sm1_frddr_component_drv = अणु
	.dapm_widमाला_लो		= sm1_frddr_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(sm1_frddr_dapm_widमाला_लो),
	.dapm_routes		= g12a_frddr_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(g12a_frddr_dapm_routes),
	.खोलो			= axg_fअगरo_pcm_खोलो,
	.बंद			= axg_fअगरo_pcm_बंद,
	.hw_params		= g12a_fअगरo_pcm_hw_params,
	.hw_मुक्त		= axg_fअगरo_pcm_hw_मुक्त,
	.poपूर्णांकer		= axg_fअगरo_pcm_poपूर्णांकer,
	.trigger		= axg_fअगरo_pcm_trigger,
पूर्ण;

अटल स्थिर काष्ठा axg_fअगरo_match_data sm1_frddr_match_data = अणु
	.field_threshold	= REG_FIELD(FIFO_CTRL1, 16, 23),
	.component_drv		= &sm1_frddr_component_drv,
	.dai_drv		= &g12a_frddr_dai_drv
पूर्ण;

अटल स्थिर काष्ठा of_device_id axg_frddr_of_match[] = अणु
	अणु
		.compatible = "amlogic,axg-frddr",
		.data = &axg_frddr_match_data,
	पूर्ण, अणु
		.compatible = "amlogic,g12a-frddr",
		.data = &g12a_frddr_match_data,
	पूर्ण, अणु
		.compatible = "amlogic,sm1-frddr",
		.data = &sm1_frddr_match_data,
	पूर्ण, अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, axg_frddr_of_match);

अटल काष्ठा platक्रमm_driver axg_frddr_pdrv = अणु
	.probe = axg_fअगरo_probe,
	.driver = अणु
		.name = "axg-frddr",
		.of_match_table = axg_frddr_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(axg_frddr_pdrv);

MODULE_DESCRIPTION("Amlogic AXG/G12A playback fifo driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
