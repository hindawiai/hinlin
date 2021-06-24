<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright(c) 2015-18 Intel Corporation.

/*
 * Common functions used in dअगरferent Intel machine drivers
 */
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश "../../codecs/hdac_hdmi.h"
#समावेश "skl_hda_dsp_common.h"

#समावेश <sound/hda_codec.h>
#समावेश "../../codecs/hdac_hda.h"

#घोषणा NAME_SIZE	32

पूर्णांक skl_hda_hdmi_add_pcm(काष्ठा snd_soc_card *card, पूर्णांक device)
अणु
	काष्ठा skl_hda_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा skl_hda_hdmi_pcm *pcm;
	अक्षर dai_name[NAME_SIZE];

	pcm = devm_kzalloc(card->dev, माप(*pcm), GFP_KERNEL);
	अगर (!pcm)
		वापस -ENOMEM;

	snम_लिखो(dai_name, माप(dai_name), "intel-hdmi-hifi%d",
		 ctx->dai_index);
	pcm->codec_dai = snd_soc_card_get_codec_dai(card, dai_name);
	अगर (!pcm->codec_dai)
		वापस -EINVAL;

	pcm->device = device;
	list_add_tail(&pcm->head, &ctx->hdmi_pcm_list);

	वापस 0;
पूर्ण

SND_SOC_DAILINK_DEF(idisp1_cpu,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp1 Pin")));
SND_SOC_DAILINK_DEF(idisp1_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi1")));

SND_SOC_DAILINK_DEF(idisp2_cpu,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp2 Pin")));
SND_SOC_DAILINK_DEF(idisp2_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi2")));

SND_SOC_DAILINK_DEF(idisp3_cpu,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp3 Pin")));
SND_SOC_DAILINK_DEF(idisp3_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi3")));

SND_SOC_DAILINK_DEF(analog_cpu,
	DAILINK_COMP_ARRAY(COMP_CPU("Analog CPU DAI")));
SND_SOC_DAILINK_DEF(analog_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D0", "Analog Codec DAI")));

SND_SOC_DAILINK_DEF(digital_cpu,
	DAILINK_COMP_ARRAY(COMP_CPU("Digital CPU DAI")));
SND_SOC_DAILINK_DEF(digital_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D0", "Digital Codec DAI")));

SND_SOC_DAILINK_DEF(dmic_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("DMIC01 Pin")));

SND_SOC_DAILINK_DEF(dmic_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("dmic-codec", "dmic-hifi")));

SND_SOC_DAILINK_DEF(dmic16k,
	DAILINK_COMP_ARRAY(COMP_CPU("DMIC16k Pin")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("0000:00:1f.3")));

/* skl_hda_digital audio पूर्णांकerface glue - connects codec <--> CPU */
काष्ठा snd_soc_dai_link skl_hda_be_dai_links[HDA_DSP_MAX_BE_DAI_LINKS] = अणु
	/* Back End DAI links */
	अणु
		.name = "iDisp1",
		.id = 1,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp1_cpu, idisp1_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp2",
		.id = 2,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp2_cpu, idisp2_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp3",
		.id = 3,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp3_cpu, idisp3_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "Analog Playback and Capture",
		.id = 4,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(analog_cpu, analog_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "Digital Playback and Capture",
		.id = 5,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(digital_cpu, digital_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "dmic01",
		.id = 6,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(dmic_pin, dmic_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "dmic16k",
		.id = 7,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(dmic16k, dmic_codec, platक्रमm),
	पूर्ण,
पूर्ण;

पूर्णांक skl_hda_hdmi_jack_init(काष्ठा snd_soc_card *card)
अणु
	काष्ठा skl_hda_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_component *component = शून्य;
	काष्ठा skl_hda_hdmi_pcm *pcm;
	अक्षर jack_name[NAME_SIZE];
	पूर्णांक err;

	अगर (ctx->common_hdmi_codec_drv)
		वापस skl_hda_hdmi_build_controls(card);

	list_क्रम_each_entry(pcm, &ctx->hdmi_pcm_list, head) अणु
		component = pcm->codec_dai->component;
		snम_लिखो(jack_name, माप(jack_name),
			 "HDMI/DP, pcm=%d Jack", pcm->device);
		err = snd_soc_card_jack_new(card, jack_name,
					    SND_JACK_AVOUT, &pcm->hdmi_jack,
					    शून्य, 0);

		अगर (err)
			वापस err;

		err = snd_jack_add_new_kctl(pcm->hdmi_jack.jack,
					    jack_name, SND_JACK_AVOUT);
		अगर (err)
			dev_warn(component->dev, "failed creating Jack kctl\n");

		err = hdac_hdmi_jack_init(pcm->codec_dai, pcm->device,
					  &pcm->hdmi_jack);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (!component)
		वापस -EINVAL;

	वापस hdac_hdmi_jack_port_init(component, &card->dapm);
पूर्ण
