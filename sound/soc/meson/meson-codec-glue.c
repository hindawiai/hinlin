<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2019 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/module.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश "meson-codec-glue.h"

अटल काष्ठा snd_soc_dapm_widget *
meson_codec_glue_get_input(काष्ठा snd_soc_dapm_widget *w)
अणु
	काष्ठा snd_soc_dapm_path *p = शून्य;
	काष्ठा snd_soc_dapm_widget *in;

	snd_soc_dapm_widget_क्रम_each_source_path(w, p) अणु
		अगर (!p->connect)
			जारी;

		/* Check that we still are in the same component */
		अगर (snd_soc_dapm_to_component(w->dapm) !=
		    snd_soc_dapm_to_component(p->source->dapm))
			जारी;

		अगर (p->source->id == snd_soc_dapm_dai_in)
			वापस p->source;

		in = meson_codec_glue_get_input(p->source);
		अगर (in)
			वापस in;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम meson_codec_glue_input_set_data(काष्ठा snd_soc_dai *dai,
					    काष्ठा meson_codec_glue_input *data)
अणु
	dai->playback_dma_data = data;
पूर्ण

काष्ठा meson_codec_glue_input *
meson_codec_glue_input_get_data(काष्ठा snd_soc_dai *dai)
अणु
	वापस dai->playback_dma_data;
पूर्ण
EXPORT_SYMBOL_GPL(meson_codec_glue_input_get_data);

अटल काष्ठा meson_codec_glue_input *
meson_codec_glue_output_get_input_data(काष्ठा snd_soc_dapm_widget *w)
अणु
	काष्ठा snd_soc_dapm_widget *in =
		meson_codec_glue_get_input(w);
	काष्ठा snd_soc_dai *dai;

	अगर (WARN_ON(!in))
		वापस शून्य;

	dai = in->priv;

	वापस meson_codec_glue_input_get_data(dai);
पूर्ण

पूर्णांक meson_codec_glue_input_hw_params(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_hw_params *params,
				     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा meson_codec_glue_input *data =
		meson_codec_glue_input_get_data(dai);

	data->params.rates = snd_pcm_rate_to_rate_bit(params_rate(params));
	data->params.rate_min = params_rate(params);
	data->params.rate_max = params_rate(params);
	data->params.क्रमmats = 1ULL << (__क्रमce पूर्णांक) params_क्रमmat(params);
	data->params.channels_min = params_channels(params);
	data->params.channels_max = params_channels(params);
	data->params.sig_bits = dai->driver->playback.sig_bits;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(meson_codec_glue_input_hw_params);

पूर्णांक meson_codec_glue_input_set_fmt(काष्ठा snd_soc_dai *dai,
				   अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा meson_codec_glue_input *data =
		meson_codec_glue_input_get_data(dai);

	/* Save the source stream क्रमmat क्रम the करोwnstream link */
	data->fmt = fmt;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(meson_codec_glue_input_set_fmt);

पूर्णांक meson_codec_glue_output_startup(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा meson_codec_glue_input *in_data =
		meson_codec_glue_output_get_input_data(dai->capture_widget);

	अगर (!in_data)
		वापस -ENODEV;

	अगर (WARN_ON(!rtd->dai_link->params)) अणु
		dev_warn(dai->dev, "codec2codec link expected\n");
		वापस -EINVAL;
	पूर्ण

	/* Replace link params with the input params */
	rtd->dai_link->params = &in_data->params;

	अगर (!in_data->fmt)
		वापस 0;

	वापस snd_soc_runसमय_set_dai_fmt(rtd, in_data->fmt);
पूर्ण
EXPORT_SYMBOL_GPL(meson_codec_glue_output_startup);

पूर्णांक meson_codec_glue_input_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा meson_codec_glue_input *data;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	meson_codec_glue_input_set_data(dai, data);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(meson_codec_glue_input_dai_probe);

पूर्णांक meson_codec_glue_input_dai_हटाओ(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा meson_codec_glue_input *data =
		meson_codec_glue_input_get_data(dai);

	kमुक्त(data);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(meson_codec_glue_input_dai_हटाओ);

MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_DESCRIPTION("Amlogic Codec Glue Helpers");
MODULE_LICENSE("GPL v2");

