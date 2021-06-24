<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2015-18 Intel Corporation.
 */

/*
 * This file defines data काष्ठाures used in Machine Driver क्रम Intel
 * platक्रमms with HDA Codecs.
 */

#अगर_अघोषित __SKL_HDA_DSP_COMMON_H
#घोषणा __SKL_HDA_DSP_COMMON_H
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/hda_codec.h>
#समावेश "../../codecs/hdac_hda.h"
#समावेश "hda_dsp_common.h"

#घोषणा HDA_DSP_MAX_BE_DAI_LINKS 7

काष्ठा skl_hda_hdmi_pcm अणु
	काष्ठा list_head head;
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा snd_soc_jack hdmi_jack;
	पूर्णांक device;
पूर्ण;

काष्ठा skl_hda_निजी अणु
	काष्ठा list_head hdmi_pcm_list;
	पूर्णांक pcm_count;
	पूर्णांक dai_index;
	स्थिर अक्षर *platक्रमm_name;
	bool common_hdmi_codec_drv;
	bool idisp_codec;
पूर्ण;

बाह्य काष्ठा snd_soc_dai_link skl_hda_be_dai_links[HDA_DSP_MAX_BE_DAI_LINKS];
पूर्णांक skl_hda_hdmi_jack_init(काष्ठा snd_soc_card *card);
पूर्णांक skl_hda_hdmi_add_pcm(काष्ठा snd_soc_card *card, पूर्णांक device);

/*
 * Search card topology and रेजिस्टर HDMI PCM related controls
 * to codec driver.
 */
अटल अंतरभूत पूर्णांक skl_hda_hdmi_build_controls(काष्ठा snd_soc_card *card)
अणु
	काष्ठा skl_hda_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_component *component;
	काष्ठा skl_hda_hdmi_pcm *pcm;

	/* HDMI disabled, करो not create controls */
	अगर (list_empty(&ctx->hdmi_pcm_list))
		वापस 0;

	pcm = list_first_entry(&ctx->hdmi_pcm_list, काष्ठा skl_hda_hdmi_pcm,
			       head);
	component = pcm->codec_dai->component;
	अगर (!component)
		वापस -EINVAL;

	वापस hda_dsp_hdmi_build_controls(card, component);
पूर्ण

#पूर्ण_अगर /* __SOUND_SOC_HDA_DSP_COMMON_H */
