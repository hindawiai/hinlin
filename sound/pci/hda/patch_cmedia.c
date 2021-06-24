<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Universal Interface क्रम Intel High Definition Audio Codec
 *
 * HD audio पूर्णांकerface patch क्रम C-Media CMI9880
 *
 * Copyright (c) 2004 Takashi Iwai <tiwai@suse.de>
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

काष्ठा cmi_spec अणु
	काष्ठा hda_gen_spec gen;
पूर्ण;

/*
 * stuff क्रम स्वतः-parser
 */
अटल स्थिर काष्ठा hda_codec_ops cmi_स्वतः_patch_ops = अणु
	.build_controls = snd_hda_gen_build_controls,
	.build_pcms = snd_hda_gen_build_pcms,
	.init = snd_hda_gen_init,
	.मुक्त = snd_hda_gen_मुक्त,
	.unsol_event = snd_hda_jack_unsol_event,
पूर्ण;

अटल पूर्णांक patch_cmi9880(काष्ठा hda_codec *codec)
अणु
	काष्ठा cmi_spec *spec;
	काष्ठा स्वतः_pin_cfg *cfg;
	पूर्णांक err;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (spec == शून्य)
		वापस -ENOMEM;

	codec->spec = spec;
	codec->patch_ops = cmi_स्वतः_patch_ops;
	cfg = &spec->gen.स्वतःcfg;
	snd_hda_gen_spec_init(&spec->gen);

	err = snd_hda_parse_pin_defcfg(codec, cfg, शून्य, 0);
	अगर (err < 0)
		जाओ error;
	err = snd_hda_gen_parse_स्वतः_config(codec, cfg);
	अगर (err < 0)
		जाओ error;

	वापस 0;

 error:
	snd_hda_gen_मुक्त(codec);
	वापस err;
पूर्ण

अटल पूर्णांक patch_cmi8888(काष्ठा hda_codec *codec)
अणु
	काष्ठा cmi_spec *spec;
	काष्ठा स्वतः_pin_cfg *cfg;
	पूर्णांक err;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;

	codec->spec = spec;
	codec->patch_ops = cmi_स्वतः_patch_ops;
	cfg = &spec->gen.स्वतःcfg;
	snd_hda_gen_spec_init(&spec->gen);

	/* mask NID 0x10 from the playback volume selection;
	 * it's a headphone boost volume handled manually below
	 */
	spec->gen.out_vol_mask = (1ULL << 0x10);

	err = snd_hda_parse_pin_defcfg(codec, cfg, शून्य, 0);
	अगर (err < 0)
		जाओ error;
	err = snd_hda_gen_parse_स्वतः_config(codec, cfg);
	अगर (err < 0)
		जाओ error;

	अगर (get_defcfg_device(snd_hda_codec_get_pincfg(codec, 0x10)) ==
	    AC_JACK_HP_OUT) अणु
		अटल स्थिर काष्ठा snd_kcontrol_new amp_kctl =
			HDA_CODEC_VOLUME("Headphone Amp Playback Volume",
					 0x10, 0, HDA_OUTPUT);
		अगर (!snd_hda_gen_add_kctl(&spec->gen, शून्य, &amp_kctl)) अणु
			err = -ENOMEM;
			जाओ error;
		पूर्ण
	पूर्ण

	वापस 0;

 error:
	snd_hda_gen_मुक्त(codec);
	वापस err;
पूर्ण

/*
 * patch entries
 */
अटल स्थिर काष्ठा hda_device_id snd_hda_id_cmedia[] = अणु
	HDA_CODEC_ENTRY(0x13f68888, "CMI8888", patch_cmi8888),
	HDA_CODEC_ENTRY(0x13f69880, "CMI9880", patch_cmi9880),
	HDA_CODEC_ENTRY(0x434d4980, "CMI9880", patch_cmi9880),
	अणुपूर्ण /* terminator */
पूर्ण;
MODULE_DEVICE_TABLE(hdaudio, snd_hda_id_cmedia);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("C-Media HD-audio codec");

अटल काष्ठा hda_codec_driver cmedia_driver = अणु
	.id = snd_hda_id_cmedia,
पूर्ण;

module_hda_codec_driver(cmedia_driver);
