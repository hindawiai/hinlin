<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2009 Simtec Electronics

#समावेश <linux/module.h>
#समावेश <sound/soc.h>

#समावेश "s3c24xx_simtec.h"

अटल स्थिर काष्ठा snd_soc_dapm_widget dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_LINE("GSM Out", शून्य),
	SND_SOC_DAPM_LINE("GSM In", शून्य),
	SND_SOC_DAPM_LINE("Line In", शून्य),
	SND_SOC_DAPM_LINE("Line Out", शून्य),
	SND_SOC_DAPM_LINE("ZV", शून्य),
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route base_map[] = अणु
	/* Headphone connected to HPअणुL,Rपूर्णOUT and HPअणुL,Rपूर्णCOM */

	अणु "Headphone Jack", शून्य, "HPLOUT" पूर्ण,
	अणु "Headphone Jack", शून्य, "HPLCOM" पूर्ण,
	अणु "Headphone Jack", शून्य, "HPROUT" पूर्ण,
	अणु "Headphone Jack", शून्य, "HPRCOM" पूर्ण,

	/* ZV connected to Line1 */

	अणु "LINE1L", शून्य, "ZV" पूर्ण,
	अणु "LINE1R", शून्य, "ZV" पूर्ण,

	/* Line In connected to Line2 */

	अणु "LINE2L", शून्य, "Line In" पूर्ण,
	अणु "LINE2R", शून्य, "Line In" पूर्ण,

	/* Microphone connected to MIC3R and MIC_BIAS */

	अणु "MIC3L", शून्य, "Mic Jack" पूर्ण,

	/* GSM connected to MONO_LOUT and MIC3L (in) */

	अणु "GSM Out", शून्य, "MONO_LOUT" पूर्ण,
	अणु "MIC3L", शून्य, "GSM In" पूर्ण,

	/* Speaker is connected to LINEOUTअणुLN,LP,RN,RPपूर्ण, however we are
	 * not using the DAPM to घातer it up and करोwn as there it makes
	 * a click when घातering up. */
पूर्ण;

/**
 * simtec_hermes_init - initialise and add controls
 * @codec; The codec instance to attach to.
 *
 * Attach our controls and configure the necessary codec
 * mappings क्रम our sound card instance.
*/
अटल पूर्णांक simtec_hermes_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	simtec_audio_init(rtd);

	वापस 0;
पूर्ण

SND_SOC_DAILINK_DEFS(tlv320aic33,
	DAILINK_COMP_ARRAY(COMP_CPU("s3c24xx-iis")),
	DAILINK_COMP_ARRAY(COMP_CODEC("tlv320aic3x-codec.0-001a",
				      "tlv320aic3x-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("s3c24xx-iis")));

अटल काष्ठा snd_soc_dai_link simtec_dai_aic33 = अणु
	.name		= "tlv320aic33",
	.stream_name	= "TLV320AIC33",
	.init		= simtec_hermes_init,
	SND_SOC_DAILINK_REG(tlv320aic33),
पूर्ण;

/* simtec audio machine driver */
अटल काष्ठा snd_soc_card snd_soc_machine_simtec_aic33 = अणु
	.name		= "Simtec-Hermes",
	.owner		= THIS_MODULE,
	.dai_link	= &simtec_dai_aic33,
	.num_links	= 1,

	.dapm_widमाला_लो	= dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(dapm_widमाला_लो),
	.dapm_routes	= base_map,
	.num_dapm_routes = ARRAY_SIZE(base_map),
पूर्ण;

अटल पूर्णांक simtec_audio_hermes_probe(काष्ठा platक्रमm_device *pd)
अणु
	dev_info(&pd->dev, "probing....\n");
	वापस simtec_audio_core_probe(pd, &snd_soc_machine_simtec_aic33);
पूर्ण

अटल काष्ठा platक्रमm_driver simtec_audio_hermes_platdrv = अणु
	.driver	= अणु
		.name	= "s3c24xx-simtec-hermes-snd",
		.pm	= simtec_audio_pm,
	पूर्ण,
	.probe	= simtec_audio_hermes_probe,
	.हटाओ	= simtec_audio_हटाओ,
पूर्ण;

module_platक्रमm_driver(simtec_audio_hermes_platdrv);

MODULE_ALIAS("platform:s3c24xx-simtec-hermes-snd");
MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_DESCRIPTION("ALSA SoC Simtec Audio support");
MODULE_LICENSE("GPL");
