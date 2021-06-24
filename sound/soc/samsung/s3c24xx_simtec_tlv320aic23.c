<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2009 Simtec Electronics

#समावेश <linux/module.h>
#समावेश <sound/soc.h>

#समावेश "s3c24xx_simtec.h"

/* supported machines:
 *
 * Machine	Connections		AMP
 * -------	-----------		---
 * BAST		MIC, HPOUT, LOUT, LIN	TPA2001D1 (HPOUTL,R) (gain hardwired)
 * VR1000	HPOUT, LIN		None
 * VR2000	LIN, LOUT, MIC, HP	LM4871 (HPOUTL,R)
 * DePicture	LIN, LOUT, MIC, HP	LM4871 (HPOUTL,R)
 * Anubis	LIN, LOUT, MIC, HP	TPA2001D1 (HPOUTL,R)
 */

अटल स्थिर काष्ठा snd_soc_dapm_widget dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_LINE("Line In", शून्य),
	SND_SOC_DAPM_LINE("Line Out", शून्य),
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route base_map[] = अणु
	अणु "Headphone Jack", शून्य, "LHPOUT"पूर्ण,
	अणु "Headphone Jack", शून्य, "RHPOUT"पूर्ण,

	अणु "Line Out", शून्य, "LOUT" पूर्ण,
	अणु "Line Out", शून्य, "ROUT" पूर्ण,

	अणु "LLINEIN", शून्य, "Line In"पूर्ण,
	अणु "RLINEIN", शून्य, "Line In"पूर्ण,

	अणु "MICIN", शून्य, "Mic Jack"पूर्ण,
पूर्ण;

/**
 * simtec_tlv320aic23_init - initialise and add controls
 * @codec; The codec instance to attach to.
 *
 * Attach our controls and configure the necessary codec
 * mappings क्रम our sound card instance.
*/
अटल पूर्णांक simtec_tlv320aic23_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	simtec_audio_init(rtd);

	वापस 0;
पूर्ण

SND_SOC_DAILINK_DEFS(tlv320aic23,
	DAILINK_COMP_ARRAY(COMP_CPU("s3c24xx-iis")),
	DAILINK_COMP_ARRAY(COMP_CODEC("tlv320aic3x-codec.0-001a",
				      "tlv320aic3x-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("s3c24xx-iis")));

अटल काष्ठा snd_soc_dai_link simtec_dai_aic23 = अणु
	.name		= "tlv320aic23",
	.stream_name	= "TLV320AIC23",
	.init		= simtec_tlv320aic23_init,
	SND_SOC_DAILINK_REG(tlv320aic23),
पूर्ण;

/* simtec audio machine driver */
अटल काष्ठा snd_soc_card snd_soc_machine_simtec_aic23 = अणु
	.name		= "Simtec",
	.owner		= THIS_MODULE,
	.dai_link	= &simtec_dai_aic23,
	.num_links	= 1,

	.dapm_widमाला_लो	= dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(dapm_widमाला_लो),
	.dapm_routes	= base_map,
	.num_dapm_routes = ARRAY_SIZE(base_map),
पूर्ण;

अटल पूर्णांक simtec_audio_tlv320aic23_probe(काष्ठा platक्रमm_device *pd)
अणु
	वापस simtec_audio_core_probe(pd, &snd_soc_machine_simtec_aic23);
पूर्ण

अटल काष्ठा platक्रमm_driver simtec_audio_tlv320aic23_driver = अणु
	.driver	= अणु
		.name	= "s3c24xx-simtec-tlv320aic23",
		.pm	= simtec_audio_pm,
	पूर्ण,
	.probe	= simtec_audio_tlv320aic23_probe,
	.हटाओ	= simtec_audio_हटाओ,
पूर्ण;

module_platक्रमm_driver(simtec_audio_tlv320aic23_driver);

MODULE_ALIAS("platform:s3c24xx-simtec-tlv320aic23");
MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_DESCRIPTION("ALSA SoC Simtec Audio support");
MODULE_LICENSE("GPL");
