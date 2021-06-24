<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright(c) 2020 Intel Corporation. All rights reserved.
#समावेश <linux/माला.स>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>
#समावेश <sound/soc-dapm.h>
#समावेश <uapi/sound/asound.h>
#समावेश "sof_maxim_common.h"

#घोषणा MAX_98373_PIN_NAME 16

स्थिर काष्ठा snd_soc_dapm_route max_98373_dapm_routes[] = अणु
	/* speaker */
	अणु "Left Spk", शून्य, "Left BE_OUT" पूर्ण,
	अणु "Right Spk", शून्य, "Right BE_OUT" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_codec_conf max_98373_codec_conf[] = अणु
	अणु
		.dlc = COMP_CODEC_CONF(MAX_98373_DEV0_NAME),
		.name_prefix = "Right",
	पूर्ण,
	अणु
		.dlc = COMP_CODEC_CONF(MAX_98373_DEV1_NAME),
		.name_prefix = "Left",
	पूर्ण,
पूर्ण;

काष्ठा snd_soc_dai_link_component max_98373_components[] = अणु
	अणु  /* For Right */
		.name = MAX_98373_DEV0_NAME,
		.dai_name = MAX_98373_CODEC_DAI,
	पूर्ण,
	अणु  /* For Left */
		.name = MAX_98373_DEV1_NAME,
		.dai_name = MAX_98373_CODEC_DAI,
	पूर्ण,
पूर्ण;

अटल पूर्णांक max98373_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक j;

	क्रम_each_rtd_codec_dais(rtd, j, codec_dai) अणु
		अगर (!म_भेद(codec_dai->component->name, MAX_98373_DEV0_NAME)) अणु
			/* DEV0 tdm slot configuration */
			snd_soc_dai_set_tdm_slot(codec_dai, 0x03, 3, 8, 32);
		पूर्ण
		अगर (!म_भेद(codec_dai->component->name, MAX_98373_DEV1_NAME)) अणु
			/* DEV1 tdm slot configuration */
			snd_soc_dai_set_tdm_slot(codec_dai, 0x0C, 3, 8, 32);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक max98373_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा snd_soc_dai *cpu_dai;
	पूर्णांक j;
	पूर्णांक ret = 0;

	/* set spk pin by playback only */
	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		वापस 0;

	cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	क्रम_each_rtd_codec_dais(rtd, j, codec_dai) अणु
		काष्ठा snd_soc_dapm_context *dapm =
				snd_soc_component_get_dapm(cpu_dai->component);
		अक्षर pin_name[MAX_98373_PIN_NAME];

		snम_लिखो(pin_name, ARRAY_SIZE(pin_name), "%s Spk",
			 codec_dai->component->name_prefix);

		चयन (cmd) अणु
		हाल SNDRV_PCM_TRIGGER_START:
		हाल SNDRV_PCM_TRIGGER_RESUME:
		हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
			ret = snd_soc_dapm_enable_pin(dapm, pin_name);
			अगर (!ret)
				snd_soc_dapm_sync(dapm);
			अवरोध;
		हाल SNDRV_PCM_TRIGGER_STOP:
		हाल SNDRV_PCM_TRIGGER_SUSPEND:
		हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
			ret = snd_soc_dapm_disable_pin(dapm, pin_name);
			अगर (!ret)
				snd_soc_dapm_sync(dapm);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा snd_soc_ops max_98373_ops = अणु
	.hw_params = max98373_hw_params,
	.trigger = max98373_trigger,
पूर्ण;

पूर्णांक max98373_spk_codec_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	पूर्णांक ret;

	ret = snd_soc_dapm_add_routes(&card->dapm, max_98373_dapm_routes,
				      ARRAY_SIZE(max_98373_dapm_routes));
	अगर (ret)
		dev_err(rtd->dev, "Speaker map addition failed: %d\n", ret);
	वापस ret;
पूर्ण

व्योम sof_max98373_codec_conf(काष्ठा snd_soc_card *card)
अणु
	card->codec_conf = max_98373_codec_conf;
	card->num_configs = ARRAY_SIZE(max_98373_codec_conf);
पूर्ण
