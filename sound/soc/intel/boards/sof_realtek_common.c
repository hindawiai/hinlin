<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright(c) 2020 Intel Corporation. All rights reserved.

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-dai.h>
#समावेश <sound/soc-dapm.h>
#समावेश <uapi/sound/asound.h>
#समावेश "../../codecs/rt1011.h"
#समावेश "sof_realtek_common.h"

/*
 * Current only 2-amp configuration is supported क्रम rt1011
 */
अटल स्थिर काष्ठा snd_soc_dapm_route rt1011_dapm_routes[] = अणु
	/* speaker */
	अणु "Left Spk", शून्य, "Left SPO" पूर्ण,
	अणु "Right Spk", शून्य, "Right SPO" पूर्ण,
पूर्ण;

/*
 * Make sure device's Unique ID follows this configuration:
 *
 * Two speakers:
 *         0: left, 1: right
 * Four speakers:
 *         0: Woofer left, 1: Woofer right
 *         2: Tweeter left, 3: Tweeter right
 */
अटल काष्ठा snd_soc_codec_conf rt1011_codec_confs[] = अणु
	अणु
		.dlc = COMP_CODEC_CONF(RT1011_DEV0_NAME),
		.name_prefix = "Left",
	पूर्ण,
	अणु
		.dlc = COMP_CODEC_CONF(RT1011_DEV1_NAME),
		.name_prefix = "Right",
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_link_component rt1011_dai_link_components[] = अणु
	अणु
		.name = RT1011_DEV0_NAME,
		.dai_name = RT1011_CODEC_DAI,
	पूर्ण,
	अणु
		.name = RT1011_DEV1_NAME,
		.dai_name = RT1011_CODEC_DAI,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	अचिन्हित पूर्णांक tx;
	अचिन्हित पूर्णांक rx;
पूर्ण rt1011_tdm_mask[] = अणु
	अणु.tx = 0x4, .rx = 0x1पूर्ण,
	अणु.tx = 0x8, .rx = 0x2पूर्ण,
पूर्ण;

अटल पूर्णांक rt1011_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक srate, i, ret = 0;

	srate = params_rate(params);

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		/* 100 Fs to drive 24 bit data */
		ret = snd_soc_dai_set_pll(codec_dai, 0, RT1011_PLL1_S_BCLK,
					  100 * srate, 256 * srate);
		अगर (ret < 0) अणु
			dev_err(codec_dai->dev, "fail to set pll, ret %d\n",
				ret);
			वापस ret;
		पूर्ण

		ret = snd_soc_dai_set_sysclk(codec_dai, RT1011_FS_SYS_PRE_S_PLL1,
					     256 * srate, SND_SOC_CLOCK_IN);
		अगर (ret < 0) अणु
			dev_err(codec_dai->dev, "fail to set sysclk, ret %d\n",
				ret);
			वापस ret;
		पूर्ण

		अगर (i >= ARRAY_SIZE(rt1011_tdm_mask)) अणु
			dev_err(codec_dai->dev, "invalid codec index %d\n",
				i);
			वापस -ENODEV;
		पूर्ण

		ret = snd_soc_dai_set_tdm_slot(codec_dai, rt1011_tdm_mask[i].tx,
					       rt1011_tdm_mask[i].rx, 4,
					       params_width(params));
		अगर (ret < 0) अणु
			dev_err(codec_dai->dev, "fail to set tdm slot, ret %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops rt1011_ops = अणु
	.hw_params = rt1011_hw_params,
पूर्ण;

अटल पूर्णांक rt1011_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	पूर्णांक ret;

	ret = snd_soc_dapm_add_routes(&card->dapm, rt1011_dapm_routes,
				      ARRAY_SIZE(rt1011_dapm_routes));
	अगर (ret)
		dev_err(rtd->dev, "Speaker map addition failed: %d\n", ret);
	वापस ret;
पूर्ण

व्योम sof_rt1011_dai_link(काष्ठा snd_soc_dai_link *link)
अणु
	link->codecs = rt1011_dai_link_components;
	link->num_codecs = ARRAY_SIZE(rt1011_dai_link_components);
	link->init = rt1011_init;
	link->ops = &rt1011_ops;
पूर्ण

व्योम sof_rt1011_codec_conf(काष्ठा snd_soc_card *card)
अणु
	card->codec_conf = rt1011_codec_confs;
	card->num_configs = ARRAY_SIZE(rt1011_codec_confs);
पूर्ण

/*
 * rt1015:  i2c mode driver क्रम ALC1015 and ALC1015Q
 * rt1015p: स्वतः-mode driver क्रम ALC1015, ALC1015Q, and ALC1015Q-VB
 *
 * For stereo output, there are always two amplअगरiers on the board.
 * However, the ACPI implements only one device instance (UID=0) अगर they
 * are sharing the same enable pin. The code will detect the number of
 * device instance and use corresponding DAPM काष्ठाures क्रम
 * initialization.
 */
अटल स्थिर काष्ठा snd_soc_dapm_route rt1015p_1dev_dapm_routes[] = अणु
	/* speaker */
	अणु "Left Spk", शून्य, "Speaker" पूर्ण,
	अणु "Right Spk", शून्य, "Speaker" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt1015p_2dev_dapm_routes[] = अणु
	/* speaker */
	अणु "Left Spk", शून्य, "Left Speaker" पूर्ण,
	अणु "Right Spk", शून्य, "Right Speaker" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_codec_conf rt1015p_codec_confs[] = अणु
	अणु
		.dlc = COMP_CODEC_CONF(RT1015P_DEV0_NAME),
		.name_prefix = "Left",
	पूर्ण,
	अणु
		.dlc = COMP_CODEC_CONF(RT1015P_DEV1_NAME),
		.name_prefix = "Right",
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_link_component rt1015p_dai_link_components[] = अणु
	अणु
		.name = RT1015P_DEV0_NAME,
		.dai_name = RT1015P_CODEC_DAI,
	पूर्ण,
	अणु
		.name = RT1015P_DEV1_NAME,
		.dai_name = RT1015P_CODEC_DAI,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rt1015p_get_num_codecs(व्योम)
अणु
	अटल पूर्णांक dev_num;

	अगर (dev_num)
		वापस dev_num;

	अगर (!acpi_dev_present("RTL1015", "1", -1))
		dev_num = 1;
	अन्यथा
		dev_num = 2;

	वापस dev_num;
पूर्ण

अटल पूर्णांक rt1015p_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	/* reserved क्रम debugging purpose */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops rt1015p_ops = अणु
	.hw_params = rt1015p_hw_params,
पूर्ण;

अटल पूर्णांक rt1015p_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	पूर्णांक ret;

	अगर (rt1015p_get_num_codecs() == 1)
		ret = snd_soc_dapm_add_routes(&card->dapm, rt1015p_1dev_dapm_routes,
					      ARRAY_SIZE(rt1015p_1dev_dapm_routes));
	अन्यथा
		ret = snd_soc_dapm_add_routes(&card->dapm, rt1015p_2dev_dapm_routes,
					      ARRAY_SIZE(rt1015p_2dev_dapm_routes));
	अगर (ret)
		dev_err(rtd->dev, "Speaker map addition failed: %d\n", ret);
	वापस ret;
पूर्ण

व्योम sof_rt1015p_dai_link(काष्ठा snd_soc_dai_link *link)
अणु
	link->codecs = rt1015p_dai_link_components;
	link->num_codecs = rt1015p_get_num_codecs();
	link->init = rt1015p_init;
	link->ops = &rt1015p_ops;
पूर्ण

व्योम sof_rt1015p_codec_conf(काष्ठा snd_soc_card *card)
अणु
	अगर (rt1015p_get_num_codecs() == 1)
		वापस;

	card->codec_conf = rt1015p_codec_confs;
	card->num_configs = ARRAY_SIZE(rt1015p_codec_confs);
पूर्ण
