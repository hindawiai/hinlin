<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2020 Intel Corporation
//
// sof_sdw_max98373 - Helpers to handle 2x MAX98373
// codec devices from generic machine driver

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <sound/control.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-dapm.h>
#समावेश "sof_sdw_common.h"
#समावेश "sof_maxim_common.h"

अटल स्थिर काष्ठा snd_soc_dapm_widget mx8373_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Left Spk", शून्य),
	SND_SOC_DAPM_SPK("Right Spk", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mx8373_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Left Spk"),
	SOC_DAPM_PIN_SWITCH("Right Spk"),
पूर्ण;

अटल पूर्णांक spk_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	पूर्णांक ret;

	card->components = devm_kaप्र_लिखो(card->dev, GFP_KERNEL,
					  "%s spk:mx8373",
					  card->components);
	अगर (!card->components)
		वापस -ENOMEM;

	ret = snd_soc_add_card_controls(card, mx8373_controls,
					ARRAY_SIZE(mx8373_controls));
	अगर (ret) अणु
		dev_err(card->dev, "mx8373 ctrls addition failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_new_controls(&card->dapm, mx8373_widमाला_लो,
					ARRAY_SIZE(mx8373_widमाला_लो));
	अगर (ret) अणु
		dev_err(card->dev, "mx8373 widgets addition failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_add_routes(&card->dapm, max_98373_dapm_routes, 2);
	अगर (ret)
		dev_err(rtd->dev, "failed to add first SPK map: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक max98373_sdw_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		/* enable max98373 first */
		ret = max98373_trigger(substream, cmd);
		अगर (ret < 0)
			अवरोध;

		ret = sdw_trigger(substream, cmd);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ret = sdw_trigger(substream, cmd);
		अगर (ret < 0)
			अवरोध;

		ret = max98373_trigger(substream, cmd);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops max_98373_sdw_ops = अणु
	.startup = sdw_startup,
	.prepare = sdw_prepare,
	.trigger = max98373_sdw_trigger,
	.hw_मुक्त = sdw_hw_मुक्त,
	.shutकरोwn = sdw_shutकरोwn,
पूर्ण;

पूर्णांक sof_sdw_mx8373_init(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
			काष्ठा snd_soc_dai_link *dai_links,
			काष्ठा sof_sdw_codec_info *info,
			bool playback)
अणु
	info->amp_num++;
	अगर (info->amp_num == 2)
		dai_links->init = spk_init;

	info->late_probe = true;

	dai_links->ops = &max_98373_sdw_ops;

	वापस 0;
पूर्ण

पूर्णांक sof_sdw_mx8373_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dapm_context *dapm = &card->dapm;

	/* Disable Left and Right Spk pin after boot */
	snd_soc_dapm_disable_pin(dapm, "Left Spk");
	snd_soc_dapm_disable_pin(dapm, "Right Spk");
	वापस snd_soc_dapm_sync(dapm);
पूर्ण
