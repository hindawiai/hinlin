<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2020 Intel Corporation

/*
 *  sof_sdw_dmic - Helpers to handle dmic from generic machine driver
 */

#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-dapm.h>
#समावेश "sof_sdw_common.h"

अटल स्थिर काष्ठा snd_soc_dapm_widget dmic_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIC("SoC DMIC", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route dmic_map[] = अणु
	/* digital mics */
	अणु"DMic", शून्य, "SoC DMIC"पूर्ण,
पूर्ण;

पूर्णांक sof_sdw_dmic_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	पूर्णांक ret;

	ret = snd_soc_dapm_new_controls(&card->dapm, dmic_widमाला_लो,
					ARRAY_SIZE(dmic_widमाला_लो));
	अगर (ret) अणु
		dev_err(card->dev, "DMic widget addition failed: %d\n", ret);
		/* Don't need to add routes अगर widget addition failed */
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_add_routes(&card->dapm, dmic_map,
				      ARRAY_SIZE(dmic_map));

	अगर (ret)
		dev_err(card->dev, "DMic map addition failed: %d\n", ret);

	वापस ret;
पूर्ण

