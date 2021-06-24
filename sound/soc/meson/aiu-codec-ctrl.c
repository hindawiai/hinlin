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

#घोषणा CTRL_CLK_SEL		GENMASK(1, 0)
#घोषणा CTRL_DATA_SEL_SHIFT	4
#घोषणा CTRL_DATA_SEL		(0x3 << CTRL_DATA_SEL_SHIFT)

अटल स्थिर अक्षर * स्थिर aiu_codec_ctrl_mux_texts[] = अणु
	"DISABLED", "PCM", "I2S",
पूर्ण;

अटल पूर्णांक aiu_codec_ctrl_mux_put_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
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
					      CTRL_DATA_SEL,
					      FIELD_PREP(CTRL_DATA_SEL, mux));

	अगर (!changed)
		वापस 0;

	/* Force disconnect of the mux जबतक updating */
	snd_soc_dapm_mux_update_घातer(dapm, kcontrol, 0, शून्य, शून्य);

	/* Reset the source first */
	snd_soc_component_update_bits(component, e->reg,
				      CTRL_CLK_SEL |
				      CTRL_DATA_SEL,
				      FIELD_PREP(CTRL_CLK_SEL, 0) |
				      FIELD_PREP(CTRL_DATA_SEL, 0));

	/* Set the appropriate source */
	snd_soc_component_update_bits(component, e->reg,
				      CTRL_CLK_SEL |
				      CTRL_DATA_SEL,
				      FIELD_PREP(CTRL_CLK_SEL, mux) |
				      FIELD_PREP(CTRL_DATA_SEL, mux));

	snd_soc_dapm_mux_update_घातer(dapm, kcontrol, mux, e, शून्य);

	वापस 0;
पूर्ण

अटल SOC_ENUM_SINGLE_DECL(aiu_hdmi_ctrl_mux_क्रमागत, AIU_HDMI_CLK_DATA_CTRL,
			    CTRL_DATA_SEL_SHIFT,
			    aiu_codec_ctrl_mux_texts);

अटल स्थिर काष्ठा snd_kcontrol_new aiu_hdmi_ctrl_mux =
	SOC_DAPM_ENUM_EXT("HDMI Source", aiu_hdmi_ctrl_mux_क्रमागत,
			  snd_soc_dapm_get_क्रमागत_द्विगुन,
			  aiu_codec_ctrl_mux_put_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_widget aiu_hdmi_ctrl_widमाला_लो[] = अणु
	SND_SOC_DAPM_MUX("HDMI CTRL SRC", SND_SOC_NOPM, 0, 0,
			 &aiu_hdmi_ctrl_mux),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops aiu_codec_ctrl_input_ops = अणु
	.hw_params	= meson_codec_glue_input_hw_params,
	.set_fmt	= meson_codec_glue_input_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops aiu_codec_ctrl_output_ops = अणु
	.startup	= meson_codec_glue_output_startup,
पूर्ण;

#घोषणा AIU_CODEC_CTRL_FORMATS					\
	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |	\
	 SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_LE |	\
	 SNDRV_PCM_FMTBIT_S32_LE)

#घोषणा AIU_CODEC_CTRL_STREAM(xname, xsuffix)			\
अणु								\
	.stream_name	= xname " " xsuffix,			\
	.channels_min	= 1,					\
	.channels_max	= 8,					\
	.rate_min       = 5512,					\
	.rate_max	= 192000,				\
	.क्रमmats	= AIU_CODEC_CTRL_FORMATS,		\
पूर्ण

#घोषणा AIU_CODEC_CTRL_INPUT(xname) अणु				\
	.name = "CODEC CTRL " xname,				\
	.playback = AIU_CODEC_CTRL_STREAM(xname, "Playback"),	\
	.ops = &aiu_codec_ctrl_input_ops,			\
	.probe = meson_codec_glue_input_dai_probe,		\
	.हटाओ = meson_codec_glue_input_dai_हटाओ,		\
पूर्ण

#घोषणा AIU_CODEC_CTRL_OUTPUT(xname) अणु				\
	.name = "CODEC CTRL " xname,				\
	.capture = AIU_CODEC_CTRL_STREAM(xname, "Capture"),	\
	.ops = &aiu_codec_ctrl_output_ops,			\
पूर्ण

अटल काष्ठा snd_soc_dai_driver aiu_hdmi_ctrl_dai_drv[] = अणु
	[CTRL_I2S] = AIU_CODEC_CTRL_INPUT("HDMI I2S IN"),
	[CTRL_PCM] = AIU_CODEC_CTRL_INPUT("HDMI PCM IN"),
	[CTRL_OUT] = AIU_CODEC_CTRL_OUTPUT("HDMI OUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route aiu_hdmi_ctrl_routes[] = अणु
	अणु "HDMI CTRL SRC", "I2S", "HDMI I2S IN Playback" पूर्ण,
	अणु "HDMI CTRL SRC", "PCM", "HDMI PCM IN Playback" पूर्ण,
	अणु "HDMI OUT Capture", शून्य, "HDMI CTRL SRC" पूर्ण,
पूर्ण;

अटल पूर्णांक aiu_hdmi_of_xlate_dai_name(काष्ठा snd_soc_component *component,
				      स्थिर काष्ठा of_phandle_args *args,
				      स्थिर अक्षर **dai_name)
अणु
	वापस aiu_of_xlate_dai_name(component, args, dai_name, AIU_HDMI);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver aiu_hdmi_ctrl_component = अणु
	.name			= "AIU HDMI Codec Control",
	.dapm_widमाला_लो		= aiu_hdmi_ctrl_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(aiu_hdmi_ctrl_widमाला_लो),
	.dapm_routes		= aiu_hdmi_ctrl_routes,
	.num_dapm_routes	= ARRAY_SIZE(aiu_hdmi_ctrl_routes),
	.of_xlate_dai_name	= aiu_hdmi_of_xlate_dai_name,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

पूर्णांक aiu_hdmi_ctrl_रेजिस्टर_component(काष्ठा device *dev)
अणु
	वापस snd_soc_रेजिस्टर_component(dev, &aiu_hdmi_ctrl_component,
					  aiu_hdmi_ctrl_dai_drv,
					  ARRAY_SIZE(aiu_hdmi_ctrl_dai_drv));
पूर्ण

