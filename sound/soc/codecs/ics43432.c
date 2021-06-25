<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2S MEMS microphone driver क्रम InvenSense ICS-43432
 *
 * - Non configurable.
 * - I2S पूर्णांकerface, 64 BCLs per frame, 32 bits per channel, 24 bit data
 *
 * Copyright (c) 2015 Axis Communications AB
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#घोषणा ICS43432_RATE_MIN 7190 /* Hz, from data sheet */
#घोषणा ICS43432_RATE_MAX 52800  /* Hz, from data sheet */

#घोषणा ICS43432_FORMATS (SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32)

अटल काष्ठा snd_soc_dai_driver ics43432_dai = अणु
	.name = "ics43432-hifi",
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rate_min = ICS43432_RATE_MIN,
		.rate_max = ICS43432_RATE_MAX,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.क्रमmats = ICS43432_FORMATS,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver ics43432_component_driver = अणु
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक ics43432_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&ics43432_component_driver,
			&ics43432_dai, 1);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ics43432_ids[] = अणु
	अणु .compatible = "invensense,ics43432", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ics43432_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver ics43432_driver = अणु
	.driver = अणु
		.name = "ics43432",
		.of_match_table = of_match_ptr(ics43432_ids),
	पूर्ण,
	.probe = ics43432_probe,
पूर्ण;

module_platक्रमm_driver(ics43432_driver);

MODULE_DESCRIPTION("ASoC ICS43432 driver");
MODULE_AUTHOR("Ricard Wanderlof <ricardw@axis.com>");
MODULE_LICENSE("GPL v2");
