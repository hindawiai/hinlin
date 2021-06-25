<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2020 Intel Corporation

/*
 *  sof_sdw_rt1308 - Helpers to handle RT1308 from generic machine driver
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <sound/control.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-dapm.h>
#समावेश "sof_sdw_common.h"
#समावेश "../../codecs/rt1308.h"

अटल स्थिर काष्ठा snd_soc_dapm_widget rt1308_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Speaker", शून्य),
पूर्ण;

/*
 * dapm routes क्रम rt1308 will be रेजिस्टरed dynamically according
 * to the number of rt1308 used. The first two entries will be रेजिस्टरed
 * क्रम one codec हाल, and the last two entries are also रेजिस्टरed
 * अगर two 1308s are used.
 */
अटल स्थिर काष्ठा snd_soc_dapm_route rt1308_map[] = अणु
	अणु "Speaker", शून्य, "rt1308-1 SPOL" पूर्ण,
	अणु "Speaker", शून्य, "rt1308-1 SPOR" पूर्ण,
	अणु "Speaker", शून्य, "rt1308-2 SPOL" पूर्ण,
	अणु "Speaker", शून्य, "rt1308-2 SPOR" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt1308_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Speaker"),
पूर्ण;

अटल पूर्णांक first_spk_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	पूर्णांक ret;

	card->components = devm_kaप्र_लिखो(card->dev, GFP_KERNEL,
					  "%s spk:rt1308",
					  card->components);
	अगर (!card->components)
		वापस -ENOMEM;

	ret = snd_soc_add_card_controls(card, rt1308_controls,
					ARRAY_SIZE(rt1308_controls));
	अगर (ret) अणु
		dev_err(card->dev, "rt1308 controls addition failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_new_controls(&card->dapm, rt1308_widमाला_लो,
					ARRAY_SIZE(rt1308_widमाला_लो));
	अगर (ret) अणु
		dev_err(card->dev, "rt1308 widgets addition failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_add_routes(&card->dapm, rt1308_map, 2);
	अगर (ret)
		dev_err(rtd->dev, "failed to add first SPK map: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक second_spk_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	पूर्णांक ret;

	ret = snd_soc_dapm_add_routes(&card->dapm, rt1308_map + 2, 2);
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

अटल पूर्णांक rt1308_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक clk_id, clk_freq, pll_out;
	पूर्णांक err;

	clk_id = RT1308_PLL_S_MCLK;
	clk_freq = 38400000;

	pll_out = params_rate(params) * 512;

	/* Set rt1308 pll */
	err = snd_soc_dai_set_pll(codec_dai, 0, clk_id, clk_freq, pll_out);
	अगर (err < 0) अणु
		dev_err(card->dev, "Failed to set RT1308 PLL: %d\n", err);
		वापस err;
	पूर्ण

	/* Set rt1308 sysclk */
	err = snd_soc_dai_set_sysclk(codec_dai, RT1308_FS_SYS_S_PLL, pll_out,
				     SND_SOC_CLOCK_IN);
	अगर (err < 0) अणु
		dev_err(card->dev, "Failed to set RT1308 SYSCLK: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* machine stream operations */
काष्ठा snd_soc_ops sof_sdw_rt1308_i2s_ops = अणु
	.hw_params = rt1308_i2s_hw_params,
पूर्ण;

पूर्णांक sof_sdw_rt1308_init(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
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
		 * अगर two 1308s are in one dai link, the init function
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
