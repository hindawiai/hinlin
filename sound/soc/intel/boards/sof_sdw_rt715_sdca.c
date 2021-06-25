<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2020 Intel Corporation

/*
 *  sof_sdw_rt715_sdca - Helpers to handle RT715-SDCA from generic machine driver
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश "sof_sdw_common.h"

अटल पूर्णांक rt715_sdca_rtd_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;

	card->components = devm_kaप्र_लिखो(card->dev, GFP_KERNEL,
					  "%s mic:rt715-sdca",
					  card->components);
	अगर (!card->components)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक sof_sdw_rt715_sdca_init(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
			    काष्ठा snd_soc_dai_link *dai_links,
			    काष्ठा sof_sdw_codec_info *info,
			    bool playback)
अणु
	/*
	 * DAI ID is fixed at SDW_DMIC_DAI_ID क्रम 715-SDCA to
	 * keep sdw DMIC and HDMI setting अटल in UCM
	 */
	अगर (sof_sdw_quirk & SOF_RT715_DAI_ID_FIX)
		dai_links->id = SDW_DMIC_DAI_ID;

	dai_links->init = rt715_sdca_rtd_init;

	वापस 0;
पूर्ण
