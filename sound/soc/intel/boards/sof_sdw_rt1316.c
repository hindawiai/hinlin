<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2020 Intel Corporation

/*
 *  sof_sdw_rt1316 - Helpers to handle RT1316 from generic machine driver
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <sound/control.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-dapm.h>
#समावेश "sof_sdw_common.h"

अटल स्थिर काष्ठा snd_soc_dapm_widget rt1316_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Speaker", शून्य),
पूर्ण;

/*
 * dapm routes क्रम rt1316 will be रेजिस्टरed dynamically according
 * to the number of rt1316 used. The first two entries will be रेजिस्टरed
 * क्रम one codec हाल, and the last two entries are also रेजिस्टरed
 * अगर two 1316s are used.
 */
अटल स्थिर काष्ठा snd_soc_dapm_route rt1316_map[] = अणु
	अणु "Speaker", शून्य, "rt1316-1 SPOL" पूर्ण,
	अणु "Speaker", शून्य, "rt1316-1 SPOR" पूर्ण,
	अणु "Speaker", शून्य, "rt1316-2 SPOL" पूर्ण,
	अणु "Speaker", शून्य, "rt1316-2 SPOR" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt1316_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Speaker"),
पूर्ण;

अटल पूर्णांक first_spk_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	पूर्णांक ret;

	card->components = devm_kaप्र_लिखो(card->dev, GFP_KERNEL,
					  "%s spk:rt1316",
					  card->components);
	अगर (!card->components)
		वापस -ENOMEM;

	ret = snd_soc_add_card_controls(card, rt1316_controls,
					ARRAY_SIZE(rt1316_controls));
	अगर (ret) अणु
		dev_err(card->dev, "rt1316 controls addition failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_new_controls(&card->dapm, rt1316_widमाला_लो,
					ARRAY_SIZE(rt1316_widमाला_लो));
	अगर (ret) अणु
		dev_err(card->dev, "rt1316 widgets addition failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_add_routes(&card->dapm, rt1316_map, 2);
	अगर (ret)
		dev_err(rtd->dev, "failed to add first SPK map: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक second_spk_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	पूर्णांक ret;

	ret = snd_soc_dapm_add_routes(&card->dapm, rt1316_map + 2, 2);
	अगर (ret)
		dev_err(rtd->dev, "failed to add second SPK map: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक all_spk_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	पूर्णांक ret;

	ret = first_spk_init(rtd);
	अगर (ret)
		वापस ret;

	वापस second_spk_init(rtd);
पूर्ण

पूर्णांक sof_sdw_rt1316_init(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
			काष्ठा snd_soc_dai_link *dai_links,
			काष्ठा sof_sdw_codec_info *info,
			bool playback)
अणु
	/* Count amp number and करो init on playback link only. */
	अगर (!playback)
		वापस 0;

	info->amp_num++;
	अगर (info->amp_num == 1)
		dai_links->init = first_spk_init;

	अगर (info->amp_num == 2) अणु
		/*
		 * अगर two 1316s are in one dai link, the init function
		 * in this dai link will be first set क्रम the first speaker,
		 * and it should be reset to initialize all speakers when
		 * the second speaker is found.
		 */
		अगर (dai_links->init)
			dai_links->init = all_spk_init;
		अन्यथा
			dai_links->init = second_spk_init;
	पूर्ण

	वापस 0;
पूर्ण
