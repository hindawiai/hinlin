<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2020 Intel Corporation

/*
 *  sof_sdw_hdmi - Helpers to handle HDMI from generic machine driver
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/jack.h>
#समावेश "sof_sdw_common.h"
#समावेश "../../codecs/hdac_hdmi.h"
#समावेश "hda_dsp_common.h"

अटल काष्ठा snd_soc_jack hdmi[MAX_HDMI_NUM];

काष्ठा hdmi_pcm अणु
	काष्ठा list_head head;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक device;
पूर्ण;

पूर्णांक sof_sdw_hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा mc_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_dai *dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा hdmi_pcm *pcm;

	pcm = devm_kzalloc(rtd->card->dev, माप(*pcm), GFP_KERNEL);
	अगर (!pcm)
		वापस -ENOMEM;

	/* dai_link id is 1:1 mapped to the PCM device */
	pcm->device = rtd->dai_link->id;
	pcm->codec_dai = dai;

	list_add_tail(&pcm->head, &ctx->hdmi_pcm_list);

	वापस 0;
पूर्ण

#घोषणा NAME_SIZE	32
पूर्णांक sof_sdw_hdmi_card_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा mc_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा hdmi_pcm *pcm;
	काष्ठा snd_soc_component *component = शून्य;
	पूर्णांक err, i = 0;
	अक्षर jack_name[NAME_SIZE];

	अगर (!ctx->idisp_codec)
		वापस 0;

	अगर (list_empty(&ctx->hdmi_pcm_list))
		वापस -EINVAL;

	pcm = list_first_entry(&ctx->hdmi_pcm_list, काष्ठा hdmi_pcm,
			       head);
	component = pcm->codec_dai->component;

	अगर (ctx->common_hdmi_codec_drv)
		वापस hda_dsp_hdmi_build_controls(card, component);

	list_क्रम_each_entry(pcm, &ctx->hdmi_pcm_list, head) अणु
		component = pcm->codec_dai->component;
		snम_लिखो(jack_name, माप(jack_name),
			 "HDMI/DP, pcm=%d Jack", pcm->device);
		err = snd_soc_card_jack_new(card, jack_name,
					    SND_JACK_AVOUT, &hdmi[i],
					    शून्य, 0);

		अगर (err)
			वापस err;

		err = snd_jack_add_new_kctl(hdmi[i].jack,
					    jack_name, SND_JACK_AVOUT);
		अगर (err)
			dev_warn(component->dev, "failed creating Jack kctl\n");

		err = hdac_hdmi_jack_init(pcm->codec_dai, pcm->device,
					  &hdmi[i]);
		अगर (err < 0)
			वापस err;

		i++;
	पूर्ण

	अगर (!component)
		वापस -EINVAL;

	वापस hdac_hdmi_jack_port_init(component, &card->dapm);
पूर्ण
