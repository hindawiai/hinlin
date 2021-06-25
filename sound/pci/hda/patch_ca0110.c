<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HD audio पूर्णांकerface patch क्रम Creative X-Fi CA0110-IBG chip
 *
 * Copyright (c) 2008 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/hda_codec.h>
#समावेश "hda_local.h"
#समावेश "hda_auto_parser.h"
#समावेश "hda_jack.h"
#समावेश "hda_generic.h"


अटल स्थिर काष्ठा hda_codec_ops ca0110_patch_ops = अणु
	.build_controls = snd_hda_gen_build_controls,
	.build_pcms = snd_hda_gen_build_pcms,
	.init = snd_hda_gen_init,
	.मुक्त = snd_hda_gen_मुक्त,
	.unsol_event = snd_hda_jack_unsol_event,
पूर्ण;

अटल पूर्णांक ca0110_parse_स्वतः_config(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec = codec->spec;
	पूर्णांक err;

	err = snd_hda_parse_pin_defcfg(codec, &spec->स्वतःcfg, शून्य, 0);
	अगर (err < 0)
		वापस err;
	err = snd_hda_gen_parse_स्वतः_config(codec, &spec->स्वतःcfg);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण


अटल पूर्णांक patch_ca0110(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_gen_spec *spec;
	पूर्णांक err;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	snd_hda_gen_spec_init(spec);
	codec->spec = spec;
	codec->patch_ops = ca0110_patch_ops;

	spec->multi_cap_vol = 1;
	codec->bus->core.needs_damn_दीर्घ_delay = 1;

	err = ca0110_parse_स्वतः_config(codec);
	अगर (err < 0)
		जाओ error;

	वापस 0;

 error:
	snd_hda_gen_मुक्त(codec);
	वापस err;
पूर्ण


/*
 * patch entries
 */
अटल स्थिर काष्ठा hda_device_id snd_hda_id_ca0110[] = अणु
	HDA_CODEC_ENTRY(0x1102000a, "CA0110-IBG", patch_ca0110),
	HDA_CODEC_ENTRY(0x1102000b, "CA0110-IBG", patch_ca0110),
	HDA_CODEC_ENTRY(0x1102000d, "SB0880 X-Fi", patch_ca0110),
	अणुपूर्ण /* terminator */
पूर्ण;
MODULE_DEVICE_TABLE(hdaudio, snd_hda_id_ca0110);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Creative CA0110-IBG HD-audio codec");

अटल काष्ठा hda_codec_driver ca0110_driver = अणु
	.id = snd_hda_id_ca0110,
पूर्ण;

module_hda_codec_driver(ca0110_driver);
