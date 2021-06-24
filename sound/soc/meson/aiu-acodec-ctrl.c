<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2020 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/bitfield.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश <dt-bindings/sound/meson-aiu.h>
#समावेश "aiu.h"
#समावेश "meson-codec-glue.h"

#घोषणा CTRL_DIN_EN			15
#घोषणा CTRL_CLK_INV			BIT(14)
#घोषणा CTRL_LRCLK_INV			BIT(13)
#घोषणा CTRL_I2S_IN_BCLK_SRC		BIT(11)
#घोषणा CTRL_DIN_LRCLK_SRC_SHIFT	6
#घोषणा CTRL_DIN_LRCLK_SRC		(0x3 << CTRL_DIN_LRCLK_SRC_SHIFT)
#घोषणा CTRL_BCLK_MCLK_SRC		GENMASK(5, 4)
#घोषणा CTRL_DIN_SKEW			GENMASK(3, 2)
#घोषणा CTRL_I2S_OUT_LANE_SRC		0

#घोषणा AIU_ACODEC_OUT_CHMAX		2

अटल स्थिर अक्षर * स्थिर aiu_acodec_ctrl_mux_texts[] = अणु
	"DISABLED", "I2S", "PCM",
पूर्ण;

अटल पूर्णांक aiu_acodec_ctrl_mux_put_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक mux, changed;

	mux = snd_soc_क्रमागत_item_to_val(e, ucontrol->value.क्रमागतerated.item[0]);
	changed = snd_soc_component_test_bits(component, e->reg,
					      CTRL_DIN_LRCLK_SRC,
					      FIELD_PREP(CTRL_DIN_LRCLK_SRC,
							 mux));

	अगर (!changed)
		वापस 0;

	/* Force disconnect of the mux जबतक updating */
	snd_soc_dapm_mux_update_घातer(dapm, kcontrol, 0, शून्य, शून्य);

	snd_soc_component_update_bits(component, e->reg,
				      CTRL_DIN_LRCLK_SRC |
				      CTRL_BCLK_MCLK_SRC,
				      FIELD_PREP(CTRL_DIN_LRCLK_SRC, mux) |
				      FIELD_PREP(CTRL_BCLK_MCLK_SRC, mux));

	snd_soc_dapm_mux_update_घातer(dapm, kcontrol, mux, e, शून्य);

	वापस 0;
पूर्ण

अटल SOC_ENUM_SINGLE_DECL(aiu_acodec_ctrl_mux_क्रमागत, AIU_ACODEC_CTRL,
			    CTRL_DIN_LRCLK_SRC_SHIFT,
			    aiu_acodec_ctrl_mux_texts);

अटल स्थिर काष्ठा snd_kcontrol_new aiu_acodec_ctrl_mux =
	SOC_DAPM_ENUM_EXT("ACodec Source", aiu_acodec_ctrl_mux_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  aiu_acodec_ctrl_mux_put_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new aiu_acodec_ctrl_out_enable =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", AIU_ACODEC_CTRL,
				    CTRL_DIN_EN, 1, 0);

अटल स्थिर काष्ठा snd_soc_dapm_widget aiu_acodec_ctrl_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("ACODEC SRC", SND_SOC_NOPM, 0, 0,
			 &aiu_acodec_ctrl_mux),
	SND_SOC_DAPM_SWITCH("ACODEC OUT EN", SND_SOC_NOPM, 0, 0,
			    &aiu_acodec_ctrl_out_enable),
पूर्ण;

अटल पूर्णांक aiu_acodec_ctrl_input_hw_params(काष्ठा snd_pcm_substream *substream,
					   काष्ठा snd_pcm_hw_params *params,
					   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा meson_codec_glue_input *data;
	पूर्णांक ret;

	ret = meson_codec_glue_input_hw_params(substream, params, dai);
	अगर (ret)
		वापस ret;

	/* The glue will provide 1 lane out of the 4 to the output */
	data = meson_codec_glue_input_get_data(dai);
	data->params.channels_min = min_t(अचिन्हित पूर्णांक, AIU_ACODEC_OUT_CHMAX,
					  data->params.channels_min);
	data->params.channels_max = min_t(अचिन्हित पूर्णांक, AIU_ACODEC_OUT_CHMAX,
					  data->params.channels_max);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops aiu_acodec_ctrl_input_ops = अणु
	.hw_params	= aiu_acodec_ctrl_input_hw_params,
	.set_fmt	= meson_codec_glue_input_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops aiu_acodec_ctrl_output_ops = अणु
	.startup	= meson_codec_glue_output_startup,
पूर्ण;

#घोषणा AIU_ACODEC_CTRL_FORMATS					\
	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |	\
	 SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_LE |	\
	 SNDRV_PCM_FMTBIT_S32_LE)

#घोषणा AIU_ACODEC_STREAM(xname, xsuffix, xchmax)		\
अणु								\
	.stream_name	= xname " " xsuffix,			\
	.channels_min	= 1,					\
	.channels_max	= (xchmax),				\
	.rate_min       = 5512,					\
	.rate_max	= 192000,				\
	.क्रमmats	= AIU_ACODEC_CTRL_FORMATS,		\
पूर्ण

#घोषणा AIU_ACODEC_INPUT(xname) अणु				\
	.name = "ACODEC CTRL " xname,				\
	.playback = AIU_ACODEC_STREAM(xname, "Playback", 8),	\
	.ops = &aiu_acodec_ctrl_input_ops,			\
	.probe = meson_codec_glue_input_dai_probe,		\
	.हटाओ = meson_codec_glue_input_dai_हटाओ,		\
पूर्ण

#घोषणा AIU_ACODEC_OUTPUT(xname) अणु				\
	.name = "ACODEC CTRL " xname,				\
	.capture = AIU_ACODEC_STREAM(xname, "Capture", AIU_ACODEC_OUT_CHMAX), \
	.ops = &aiu_acodec_ctrl_output_ops,			\
पूर्ण

अटल काष्ठा snd_soc_dai_driver aiu_acodec_ctrl_dai_drv[] = अणु
	[CTRL_I2S] = AIU_ACODEC_INPUT("ACODEC I2S IN"),
	[CTRL_PCM] = AIU_ACODEC_INPUT("ACODEC PCM IN"),
	[CTRL_OUT] = AIU_ACODEC_OUTPUT("ACODEC OUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route aiu_acodec_ctrl_routes[] = अणु
	अणु "ACODEC SRC", "I2S", "ACODEC I2S IN Playback" पूर्ण,
	अणु "ACODEC SRC", "PCM", "ACODEC PCM IN Playback" पूर्ण,
	अणु "ACODEC OUT EN", "Switch", "ACODEC SRC" पूर्ण,
	अणु "ACODEC OUT Capture", शून्य, "ACODEC OUT EN" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aiu_acodec_ctrl_controls[] = अणु
	SOC_SINGLE("ACODEC I2S Lane Select", AIU_ACODEC_CTRL,
		   CTRL_I2S_OUT_LANE_SRC, 3, 0),
पूर्ण;

अटल पूर्णांक aiu_acodec_of_xlate_dai_name(काष्ठा snd_soc_component *component,
					स्थिर काष्ठा of_phandle_args *args,
					स्थिर अक्षर **dai_name)
अणु
	वापस aiu_of_xlate_dai_name(component, args, dai_name, AIU_ACODEC);
पूर्ण

अटल पूर्णांक aiu_acodec_ctrl_component_probe(काष्ठा snd_soc_component *component)
अणु
	/*
	 * NOTE: Din Skew setting
	 * According to the करोcumentation, the following update adds one delay
	 * to the din line. Without this, the output saturates. This happens
	 * regardless of the link क्रमmat (i2s or left_j) so it is not clear what
	 * it actually करोes but it seems to be required
	 */
	snd_soc_component_update_bits(component, AIU_ACODEC_CTRL,
				      CTRL_DIN_SKEW,
				      FIELD_PREP(CTRL_DIN_SKEW, 2));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver aiu_acodec_ctrl_component = अणु
	.name			= "AIU Internal DAC Codec Control",
	.probe			= aiu_acodec_ctrl_component_probe,
	.controls		= aiu_acodec_ctrl_controls,
	.num_controls		= ARRAY_SIZE(aiu_acodec_ctrl_controls),
	.dapm_widमाला_लो		= aiu_acodec_ctrl_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(aiu_acodec_ctrl_widमाला_लो),
	.dapm_routes		= aiu_acodec_ctrl_routes,
	.num_dapm_routes	= ARRAY_SIZE(aiu_acodec_ctrl_routes),
	.of_xlate_dai_name	= aiu_acodec_of_xlate_dai_name,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

पूर्णांक aiu_acodec_ctrl_रेजिस्टर_component(काष्ठा device *dev)
अणु
	वापस snd_soc_रेजिस्टर_component(dev, &aiu_acodec_ctrl_component,
					  aiu_acodec_ctrl_dai_drv,
					  ARRAY_SIZE(aiu_acodec_ctrl_dai_drv));
पूर्ण
