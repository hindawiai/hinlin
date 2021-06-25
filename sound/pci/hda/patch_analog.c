<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HD audio पूर्णांकerface patch क्रम AD1882, AD1884, AD1981HD, AD1983, AD1984,
 *   AD1986A, AD1988
 *
 * Copyright (c) 2005-2007 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश <sound/core.h>
#समावेश <sound/hda_codec.h>
#समावेश "hda_local.h"
#समावेश "hda_auto_parser.h"
#समावेश "hda_beep.h"
#समावेश "hda_jack.h"
#समावेश "hda_generic.h"


काष्ठा ad198x_spec अणु
	काष्ठा hda_gen_spec gen;

	/* क्रम स्वतः parser */
	पूर्णांक smux_paths[4];
	अचिन्हित पूर्णांक cur_smux;
	hda_nid_t eapd_nid;

	अचिन्हित पूर्णांक beep_amp;	/* beep amp value, set via set_beep_amp() */
	पूर्णांक num_smux_conns;
पूर्ण;


#अगर_घोषित CONFIG_SND_HDA_INPUT_BEEP
/* additional beep mixers; the actual parameters are overwritten at build */
अटल स्थिर काष्ठा snd_kcontrol_new ad_beep_mixer[] = अणु
	HDA_CODEC_VOLUME("Beep Playback Volume", 0, 0, HDA_OUTPUT),
	HDA_CODEC_MUTE_BEEP("Beep Playback Switch", 0, 0, HDA_OUTPUT),
	अणु पूर्ण /* end */
पूर्ण;

#घोषणा set_beep_amp(spec, nid, idx, dir) \
	((spec)->beep_amp = HDA_COMPOSE_AMP_VAL(nid, 1, idx, dir)) /* mono */
#अन्यथा
#घोषणा set_beep_amp(spec, nid, idx, dir) /* NOP */
#पूर्ण_अगर

#अगर_घोषित CONFIG_SND_HDA_INPUT_BEEP
अटल पूर्णांक create_beep_ctls(काष्ठा hda_codec *codec)
अणु
	काष्ठा ad198x_spec *spec = codec->spec;
	स्थिर काष्ठा snd_kcontrol_new *knew;

	अगर (!spec->beep_amp)
		वापस 0;

	क्रम (knew = ad_beep_mixer ; knew->name; knew++) अणु
		पूर्णांक err;
		काष्ठा snd_kcontrol *kctl;
		kctl = snd_ctl_new1(knew, codec);
		अगर (!kctl)
			वापस -ENOMEM;
		kctl->निजी_value = spec->beep_amp;
		err = snd_hda_ctl_add(codec, 0, kctl);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा create_beep_ctls(codec)		0
#पूर्ण_अगर


अटल व्योम ad198x_घातer_eapd_ग_लिखो(काष्ठा hda_codec *codec, hda_nid_t front,
				hda_nid_t hp)
अणु
	अगर (snd_hda_query_pin_caps(codec, front) & AC_PINCAP_EAPD)
		snd_hda_codec_ग_लिखो(codec, front, 0, AC_VERB_SET_EAPD_BTLENABLE,
			    !codec->inv_eapd ? 0x00 : 0x02);
	अगर (snd_hda_query_pin_caps(codec, hp) & AC_PINCAP_EAPD)
		snd_hda_codec_ग_लिखो(codec, hp, 0, AC_VERB_SET_EAPD_BTLENABLE,
			    !codec->inv_eapd ? 0x00 : 0x02);
पूर्ण

अटल व्योम ad198x_घातer_eapd(काष्ठा hda_codec *codec)
अणु
	/* We currently only handle front, HP */
	चयन (codec->core.venकरोr_id) अणु
	हाल 0x11d41882:
	हाल 0x11d4882a:
	हाल 0x11d41884:
	हाल 0x11d41984:
	हाल 0x11d41883:
	हाल 0x11d4184a:
	हाल 0x11d4194a:
	हाल 0x11d4194b:
	हाल 0x11d41988:
	हाल 0x11d4198b:
	हाल 0x11d4989a:
	हाल 0x11d4989b:
		ad198x_घातer_eapd_ग_लिखो(codec, 0x12, 0x11);
		अवरोध;
	हाल 0x11d41981:
	हाल 0x11d41983:
		ad198x_घातer_eapd_ग_लिखो(codec, 0x05, 0x06);
		अवरोध;
	हाल 0x11d41986:
		ad198x_घातer_eapd_ग_लिखो(codec, 0x1b, 0x1a);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ad198x_shutup(काष्ठा hda_codec *codec)
अणु
	snd_hda_shutup_pins(codec);
	ad198x_घातer_eapd(codec);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ad198x_suspend(काष्ठा hda_codec *codec)
अणु
	ad198x_shutup(codec);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* follow EAPD via vmaster hook */
अटल व्योम ad_vmaster_eapd_hook(व्योम *निजी_data, पूर्णांक enabled)
अणु
	काष्ठा hda_codec *codec = निजी_data;
	काष्ठा ad198x_spec *spec = codec->spec;

	अगर (!spec->eapd_nid)
		वापस;
	अगर (codec->inv_eapd)
		enabled = !enabled;
	snd_hda_codec_ग_लिखो_cache(codec, spec->eapd_nid, 0,
				   AC_VERB_SET_EAPD_BTLENABLE,
				   enabled ? 0x02 : 0x00);
पूर्ण

/*
 * Automatic parse of I/O pins from the BIOS configuration
 */

अटल पूर्णांक ad198x_स्वतः_build_controls(काष्ठा hda_codec *codec)
अणु
	पूर्णांक err;

	err = snd_hda_gen_build_controls(codec);
	अगर (err < 0)
		वापस err;
	err = create_beep_ctls(codec);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hda_codec_ops ad198x_स्वतः_patch_ops = अणु
	.build_controls = ad198x_स्वतः_build_controls,
	.build_pcms = snd_hda_gen_build_pcms,
	.init = snd_hda_gen_init,
	.मुक्त = snd_hda_gen_मुक्त,
	.unsol_event = snd_hda_jack_unsol_event,
#अगर_घोषित CONFIG_PM
	.check_घातer_status = snd_hda_gen_check_घातer_status,
	.suspend = ad198x_suspend,
#पूर्ण_अगर
	.reboot_notअगरy = ad198x_shutup,
पूर्ण;


अटल पूर्णांक ad198x_parse_स्वतः_config(काष्ठा hda_codec *codec, bool indep_hp)
अणु
	काष्ठा ad198x_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->gen.स्वतःcfg;
	पूर्णांक err;

	codec->spdअगर_status_reset = 1;
	codec->no_trigger_sense = 1;
	codec->no_sticky_stream = 1;

	spec->gen.indep_hp = indep_hp;
	अगर (!spec->gen.add_stereo_mix_input)
		spec->gen.add_stereo_mix_input = HDA_HINT_STEREO_MIX_AUTO;

	err = snd_hda_parse_pin_defcfg(codec, cfg, शून्य, 0);
	अगर (err < 0)
		वापस err;
	err = snd_hda_gen_parse_स्वतः_config(codec, cfg);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

/*
 * AD1986A specअगरic
 */

अटल पूर्णांक alloc_ad_spec(काष्ठा hda_codec *codec)
अणु
	काष्ठा ad198x_spec *spec;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	codec->spec = spec;
	snd_hda_gen_spec_init(&spec->gen);
	codec->patch_ops = ad198x_स्वतः_patch_ops;
	वापस 0;
पूर्ण

/*
 * AD1986A fixup codes
 */

/* Lenovo N100 seems to report the reversed bit क्रम HP jack-sensing */
अटल व्योम ad_fixup_inv_jack_detect(काष्ठा hda_codec *codec,
				     स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा ad198x_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		codec->inv_jack_detect = 1;
		spec->gen.keep_eapd_on = 1;
		spec->gen.vmaster_mute.hook = ad_vmaster_eapd_hook;
		spec->eapd_nid = 0x1b;
	पूर्ण
पूर्ण

/* Toshiba Satellite L40 implements EAPD in a standard way unlike others */
अटल व्योम ad1986a_fixup_eapd(काष्ठा hda_codec *codec,
			       स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा ad198x_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		codec->inv_eapd = 0;
		spec->gen.keep_eapd_on = 1;
		spec->eapd_nid = 0x1b;
	पूर्ण
पूर्ण

/* enable stereo-mix input क्रम aव्योमing regression on KDE (bko#88251) */
अटल व्योम ad1986a_fixup_eapd_mix_in(काष्ठा hda_codec *codec,
				      स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा ad198x_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		ad1986a_fixup_eapd(codec, fix, action);
		spec->gen.add_stereo_mix_input = HDA_HINT_STEREO_MIX_ENABLE;
	पूर्ण
पूर्ण

क्रमागत अणु
	AD1986A_FIXUP_INV_JACK_DETECT,
	AD1986A_FIXUP_ULTRA,
	AD1986A_FIXUP_SAMSUNG,
	AD1986A_FIXUP_3STACK,
	AD1986A_FIXUP_LAPTOP,
	AD1986A_FIXUP_LAPTOP_IMIC,
	AD1986A_FIXUP_EAPD,
	AD1986A_FIXUP_EAPD_MIX_IN,
	AD1986A_FIXUP_EASYNOTE,
पूर्ण;

अटल स्थिर काष्ठा hda_fixup ad1986a_fixups[] = अणु
	[AD1986A_FIXUP_INV_JACK_DETECT] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = ad_fixup_inv_jack_detect,
	पूर्ण,
	[AD1986A_FIXUP_ULTRA] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			अणु 0x1b, 0x90170110 पूर्ण, /* speaker */
			अणु 0x1d, 0x90a7013e पूर्ण, /* पूर्णांक mic */
			अणुपूर्ण
		पूर्ण,
	पूर्ण,
	[AD1986A_FIXUP_SAMSUNG] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			अणु 0x1b, 0x90170110 पूर्ण, /* speaker */
			अणु 0x1d, 0x90a7013e पूर्ण, /* पूर्णांक mic */
			अणु 0x20, 0x411111f0 पूर्ण, /* N/A */
			अणु 0x24, 0x411111f0 पूर्ण, /* N/A */
			अणुपूर्ण
		पूर्ण,
	पूर्ण,
	[AD1986A_FIXUP_3STACK] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			अणु 0x1a, 0x02214021 पूर्ण, /* headphone */
			अणु 0x1b, 0x01014011 पूर्ण, /* front */
			अणु 0x1c, 0x01813030 पूर्ण, /* line-in */
			अणु 0x1d, 0x01a19020 पूर्ण, /* rear mic */
			अणु 0x1e, 0x411111f0 पूर्ण, /* N/A */
			अणु 0x1f, 0x02a190f0 पूर्ण, /* mic */
			अणु 0x20, 0x411111f0 पूर्ण, /* N/A */
			अणुपूर्ण
		पूर्ण,
	पूर्ण,
	[AD1986A_FIXUP_LAPTOP] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			अणु 0x1a, 0x02214021 पूर्ण, /* headphone */
			अणु 0x1b, 0x90170110 पूर्ण, /* speaker */
			अणु 0x1c, 0x411111f0 पूर्ण, /* N/A */
			अणु 0x1d, 0x411111f0 पूर्ण, /* N/A */
			अणु 0x1e, 0x411111f0 पूर्ण, /* N/A */
			अणु 0x1f, 0x02a191f0 पूर्ण, /* mic */
			अणु 0x20, 0x411111f0 पूर्ण, /* N/A */
			अणुपूर्ण
		पूर्ण,
	पूर्ण,
	[AD1986A_FIXUP_LAPTOP_IMIC] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			अणु 0x1d, 0x90a7013e पूर्ण, /* पूर्णांक mic */
			अणुपूर्ण
		पूर्ण,
		.chained_beक्रमe = 1,
		.chain_id = AD1986A_FIXUP_LAPTOP,
	पूर्ण,
	[AD1986A_FIXUP_EAPD] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = ad1986a_fixup_eapd,
	पूर्ण,
	[AD1986A_FIXUP_EAPD_MIX_IN] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = ad1986a_fixup_eapd_mix_in,
	पूर्ण,
	[AD1986A_FIXUP_EASYNOTE] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			अणु 0x1a, 0x0421402f पूर्ण, /* headphone */
			अणु 0x1b, 0x90170110 पूर्ण, /* speaker */
			अणु 0x1c, 0x411111f0 पूर्ण, /* N/A */
			अणु 0x1d, 0x90a70130 पूर्ण, /* पूर्णांक mic */
			अणु 0x1e, 0x411111f0 पूर्ण, /* N/A */
			अणु 0x1f, 0x04a19040 पूर्ण, /* mic */
			अणु 0x20, 0x411111f0 पूर्ण, /* N/A */
			अणु 0x21, 0x411111f0 पूर्ण, /* N/A */
			अणु 0x22, 0x411111f0 पूर्ण, /* N/A */
			अणु 0x23, 0x411111f0 पूर्ण, /* N/A */
			अणु 0x24, 0x411111f0 पूर्ण, /* N/A */
			अणु 0x25, 0x411111f0 पूर्ण, /* N/A */
			अणुपूर्ण
		पूर्ण,
		.chained = true,
		.chain_id = AD1986A_FIXUP_EAPD_MIX_IN,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk ad1986a_fixup_tbl[] = अणु
	SND_PCI_QUIRK(0x103c, 0x30af, "HP B2800", AD1986A_FIXUP_LAPTOP_IMIC),
	SND_PCI_QUIRK(0x1043, 0x1153, "ASUS M9V", AD1986A_FIXUP_LAPTOP_IMIC),
	SND_PCI_QUIRK(0x1043, 0x1443, "ASUS Z99He", AD1986A_FIXUP_EAPD),
	SND_PCI_QUIRK(0x1043, 0x1447, "ASUS A8JN", AD1986A_FIXUP_EAPD),
	SND_PCI_QUIRK_MASK(0x1043, 0xff00, 0x8100, "ASUS P5", AD1986A_FIXUP_3STACK),
	SND_PCI_QUIRK_MASK(0x1043, 0xff00, 0x8200, "ASUS M2", AD1986A_FIXUP_3STACK),
	SND_PCI_QUIRK(0x10de, 0xcb84, "ASUS A8N-VM", AD1986A_FIXUP_3STACK),
	SND_PCI_QUIRK(0x1179, 0xff40, "Toshiba Satellite L40", AD1986A_FIXUP_EAPD),
	SND_PCI_QUIRK(0x144d, 0xc01e, "FSC V2060", AD1986A_FIXUP_LAPTOP),
	SND_PCI_QUIRK_MASK(0x144d, 0xff00, 0xc000, "Samsung", AD1986A_FIXUP_SAMSUNG),
	SND_PCI_QUIRK(0x144d, 0xc027, "Samsung Q1", AD1986A_FIXUP_ULTRA),
	SND_PCI_QUIRK(0x1631, 0xc022, "PackardBell EasyNote MX65", AD1986A_FIXUP_EASYNOTE),
	SND_PCI_QUIRK(0x17aa, 0x2066, "Lenovo N100", AD1986A_FIXUP_INV_JACK_DETECT),
	SND_PCI_QUIRK(0x17aa, 0x1011, "Lenovo M55", AD1986A_FIXUP_3STACK),
	SND_PCI_QUIRK(0x17aa, 0x1017, "Lenovo A60", AD1986A_FIXUP_3STACK),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_model_fixup ad1986a_fixup_models[] = अणु
	अणु .id = AD1986A_FIXUP_3STACK, .name = "3stack" पूर्ण,
	अणु .id = AD1986A_FIXUP_LAPTOP, .name = "laptop" पूर्ण,
	अणु .id = AD1986A_FIXUP_LAPTOP_IMIC, .name = "laptop-imic" पूर्ण,
	अणु .id = AD1986A_FIXUP_LAPTOP_IMIC, .name = "laptop-eapd" पूर्ण, /* alias */
	अणु .id = AD1986A_FIXUP_EAPD, .name = "eapd" पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 */
अटल पूर्णांक patch_ad1986a(काष्ठा hda_codec *codec)
अणु
	पूर्णांक err;
	काष्ठा ad198x_spec *spec;
	अटल स्थिर hda_nid_t preferred_pairs[] = अणु
		0x1a, 0x03,
		0x1b, 0x03,
		0x1c, 0x04,
		0x1d, 0x05,
		0x1e, 0x03,
		0
	पूर्ण;

	err = alloc_ad_spec(codec);
	अगर (err < 0)
		वापस err;
	spec = codec->spec;

	/* AD1986A has the inverted EAPD implementation */
	codec->inv_eapd = 1;

	spec->gen.mixer_nid = 0x07;
	spec->gen.beep_nid = 0x19;
	set_beep_amp(spec, 0x18, 0, HDA_OUTPUT);

	/* AD1986A has a hardware problem that it can't share a stream
	 * with multiple output pins.  The copy of front to surrounds
	 * causes noisy or silent outमाला_दो at a certain timing, e.g.
	 * changing the volume.
	 * So, let's disable the shared stream.
	 */
	spec->gen.multiout.no_share_stream = 1;
	/* give fixed DAC/pin pairs */
	spec->gen.preferred_dacs = preferred_pairs;

	/* AD1986A can't manage the dynamic pin on/off smoothly */
	spec->gen.स्वतः_mute_via_amp = 1;

	snd_hda_pick_fixup(codec, ad1986a_fixup_models, ad1986a_fixup_tbl,
			   ad1986a_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	err = ad198x_parse_स्वतः_config(codec, false);
	अगर (err < 0) अणु
		snd_hda_gen_मुक्त(codec);
		वापस err;
	पूर्ण

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;
पूर्ण


/*
 * AD1983 specअगरic
 */

/*
 * SPDIF mux control क्रम AD1983 स्वतः-parser
 */
अटल पूर्णांक ad1983_स्वतः_smux_क्रमागत_info(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ad198x_spec *spec = codec->spec;
	अटल स्थिर अक्षर * स्थिर texts2[] = अणु "PCM", "ADC" पूर्ण;
	अटल स्थिर अक्षर * स्थिर texts3[] = अणु "PCM", "ADC1", "ADC2" पूर्ण;
	पूर्णांक num_conns = spec->num_smux_conns;

	अगर (num_conns == 2)
		वापस snd_hda_क्रमागत_helper_info(kcontrol, uinfo, 2, texts2);
	अन्यथा अगर (num_conns == 3)
		वापस snd_hda_क्रमागत_helper_info(kcontrol, uinfo, 3, texts3);
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad1983_स्वतः_smux_क्रमागत_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ad198x_spec *spec = codec->spec;

	ucontrol->value.क्रमागतerated.item[0] = spec->cur_smux;
	वापस 0;
पूर्ण

अटल पूर्णांक ad1983_स्वतः_smux_क्रमागत_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ad198x_spec *spec = codec->spec;
	अचिन्हित पूर्णांक val = ucontrol->value.क्रमागतerated.item[0];
	hda_nid_t dig_out = spec->gen.multiout.dig_out_nid;
	पूर्णांक num_conns = spec->num_smux_conns;

	अगर (val >= num_conns)
		वापस -EINVAL;
	अगर (spec->cur_smux == val)
		वापस 0;
	spec->cur_smux = val;
	snd_hda_codec_ग_लिखो_cache(codec, dig_out, 0,
				  AC_VERB_SET_CONNECT_SEL, val);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new ad1983_स्वतः_smux_mixer = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "IEC958 Playback Source",
	.info = ad1983_स्वतः_smux_क्रमागत_info,
	.get = ad1983_स्वतः_smux_क्रमागत_get,
	.put = ad1983_स्वतः_smux_क्रमागत_put,
पूर्ण;

अटल पूर्णांक ad1983_add_spdअगर_mux_ctl(काष्ठा hda_codec *codec)
अणु
	काष्ठा ad198x_spec *spec = codec->spec;
	hda_nid_t dig_out = spec->gen.multiout.dig_out_nid;
	पूर्णांक num_conns;

	अगर (!dig_out)
		वापस 0;
	num_conns = snd_hda_get_num_conns(codec, dig_out);
	अगर (num_conns != 2 && num_conns != 3)
		वापस 0;
	spec->num_smux_conns = num_conns;
	अगर (!snd_hda_gen_add_kctl(&spec->gen, शून्य, &ad1983_स्वतः_smux_mixer))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक patch_ad1983(काष्ठा hda_codec *codec)
अणु
	अटल स्थिर hda_nid_t conn_0c[] = अणु 0x08 पूर्ण;
	अटल स्थिर hda_nid_t conn_0d[] = अणु 0x09 पूर्ण;
	काष्ठा ad198x_spec *spec;
	पूर्णांक err;

	err = alloc_ad_spec(codec);
	अगर (err < 0)
		वापस err;
	spec = codec->spec;

	spec->gen.mixer_nid = 0x0e;
	spec->gen.beep_nid = 0x10;
	set_beep_amp(spec, 0x10, 0, HDA_OUTPUT);

	/* limit the loopback routes not to confuse the parser */
	snd_hda_override_conn_list(codec, 0x0c, ARRAY_SIZE(conn_0c), conn_0c);
	snd_hda_override_conn_list(codec, 0x0d, ARRAY_SIZE(conn_0d), conn_0d);

	err = ad198x_parse_स्वतः_config(codec, false);
	अगर (err < 0)
		जाओ error;
	err = ad1983_add_spdअगर_mux_ctl(codec);
	अगर (err < 0)
		जाओ error;
	वापस 0;

 error:
	snd_hda_gen_मुक्त(codec);
	वापस err;
पूर्ण


/*
 * AD1981 HD specअगरic
 */

अटल व्योम ad1981_fixup_hp_eapd(काष्ठा hda_codec *codec,
				 स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा ad198x_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		spec->gen.vmaster_mute.hook = ad_vmaster_eapd_hook;
		spec->eapd_nid = 0x05;
	पूर्ण
पूर्ण

/* set the upper-limit क्रम mixer amp to 0dB क्रम aव्योमing the possible
 * damage by overloading
 */
अटल व्योम ad1981_fixup_amp_override(काष्ठा hda_codec *codec,
				      स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action == HDA_FIXUP_ACT_PRE_PROBE)
		snd_hda_override_amp_caps(codec, 0x11, HDA_INPUT,
					  (0x17 << AC_AMPCAP_OFFSET_SHIFT) |
					  (0x17 << AC_AMPCAP_NUM_STEPS_SHIFT) |
					  (0x05 << AC_AMPCAP_STEP_SIZE_SHIFT) |
					  (1 << AC_AMPCAP_MUTE_SHIFT));
पूर्ण

क्रमागत अणु
	AD1981_FIXUP_AMP_OVERRIDE,
	AD1981_FIXUP_HP_EAPD,
पूर्ण;

अटल स्थिर काष्ठा hda_fixup ad1981_fixups[] = अणु
	[AD1981_FIXUP_AMP_OVERRIDE] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = ad1981_fixup_amp_override,
	पूर्ण,
	[AD1981_FIXUP_HP_EAPD] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = ad1981_fixup_hp_eapd,
		.chained = true,
		.chain_id = AD1981_FIXUP_AMP_OVERRIDE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk ad1981_fixup_tbl[] = अणु
	SND_PCI_QUIRK_VENDOR(0x1014, "Lenovo", AD1981_FIXUP_AMP_OVERRIDE),
	SND_PCI_QUIRK_VENDOR(0x103c, "HP", AD1981_FIXUP_HP_EAPD),
	SND_PCI_QUIRK_VENDOR(0x17aa, "Lenovo", AD1981_FIXUP_AMP_OVERRIDE),
	/* HP nx6320 (reversed SSID, H/W bug) */
	SND_PCI_QUIRK(0x30b0, 0x103c, "HP nx6320", AD1981_FIXUP_HP_EAPD),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक patch_ad1981(काष्ठा hda_codec *codec)
अणु
	काष्ठा ad198x_spec *spec;
	पूर्णांक err;

	err = alloc_ad_spec(codec);
	अगर (err < 0)
		वापस -ENOMEM;
	spec = codec->spec;

	spec->gen.mixer_nid = 0x0e;
	spec->gen.beep_nid = 0x10;
	set_beep_amp(spec, 0x0d, 0, HDA_OUTPUT);

	snd_hda_pick_fixup(codec, शून्य, ad1981_fixup_tbl, ad1981_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	err = ad198x_parse_स्वतः_config(codec, false);
	अगर (err < 0)
		जाओ error;
	err = ad1983_add_spdअगर_mux_ctl(codec);
	अगर (err < 0)
		जाओ error;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;

 error:
	snd_hda_gen_मुक्त(codec);
	वापस err;
पूर्ण


/*
 * AD1988
 *
 * Output pins and routes
 *
 *        Pin               Mix     Sel     DAC (*)
 * port-A 0x11 (mute/hp) <- 0x22 <- 0x37 <- 03/04/06
 * port-B 0x14 (mute/hp) <- 0x2b <- 0x30 <- 03/04/06
 * port-C 0x15 (mute)    <- 0x2c <- 0x31 <- 05/0a
 * port-D 0x12 (mute/hp) <- 0x29         <- 04
 * port-E 0x17 (mute/hp) <- 0x26 <- 0x32 <- 05/0a
 * port-F 0x16 (mute)    <- 0x2a         <- 06
 * port-G 0x24 (mute)    <- 0x27         <- 05
 * port-H 0x25 (mute)    <- 0x28         <- 0a
 * mono   0x13 (mute/amp)<- 0x1e <- 0x36 <- 03/04/06
 *
 * DAC0 = 03h, DAC1 = 04h, DAC2 = 05h, DAC3 = 06h, DAC4 = 0ah
 * (*) DAC2/3/4 are swapped to DAC3/4/2 on AD198A rev.2 due to a h/w bug.
 *
 * Input pins and routes
 *
 *        pin     boost   mix input # / adc input #
 * port-A 0x11 -> 0x38 -> mix 2, ADC 0
 * port-B 0x14 -> 0x39 -> mix 0, ADC 1
 * port-C 0x15 -> 0x3a -> 33:0 - mix 1, ADC 2
 * port-D 0x12 -> 0x3d -> mix 3, ADC 8
 * port-E 0x17 -> 0x3c -> 34:0 - mix 4, ADC 4
 * port-F 0x16 -> 0x3b -> mix 5, ADC 3
 * port-G 0x24 -> N/A  -> 33:1 - mix 1, 34:1 - mix 4, ADC 6
 * port-H 0x25 -> N/A  -> 33:2 - mix 1, 34:2 - mix 4, ADC 7
 *
 *
 * DAC assignment
 *   6stack - front/surr/CLFE/side/opt DACs - 04/06/05/0a/03
 *   3stack - front/surr/CLFE/opt DACs - 04/05/0a/03
 *
 * Inमाला_दो of Analog Mix (0x20)
 *   0:Port-B (front mic)
 *   1:Port-C/G/H (line-in)
 *   2:Port-A
 *   3:Port-D (line-in/2)
 *   4:Port-E/G/H (mic-in)
 *   5:Port-F (mic2-in)
 *   6:CD
 *   7:Beep
 *
 * ADC selection
 *   0:Port-A
 *   1:Port-B (front mic-in)
 *   2:Port-C (line-in)
 *   3:Port-F (mic2-in)
 *   4:Port-E (mic-in)
 *   5:CD
 *   6:Port-G
 *   7:Port-H
 *   8:Port-D (line-in/2)
 *   9:Mix
 *
 * Proposed pin assignments by the datasheet
 *
 * 6-stack
 * Port-A front headphone
 *      B front mic-in
 *      C rear line-in
 *      D rear front-out
 *      E rear mic-in
 *      F rear surround
 *      G rear CLFE
 *      H rear side
 *
 * 3-stack
 * Port-A front headphone
 *      B front mic
 *      C rear line-in/surround
 *      D rear front-out
 *      E rear mic-in/CLFE
 *
 * laptop
 * Port-A headphone
 *      B mic-in
 *      C करोcking station
 *      D पूर्णांकernal speaker (with EAPD)
 *      E/F quad mic array
 */

अटल पूर्णांक ad1988_स्वतः_smux_क्रमागत_info(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ad198x_spec *spec = codec->spec;
	अटल स्थिर अक्षर * स्थिर texts[] = अणु
		"PCM", "ADC1", "ADC2", "ADC3",
	पूर्ण;
	पूर्णांक num_conns = spec->num_smux_conns;

	अगर (num_conns > 4)
		num_conns = 4;
	वापस snd_hda_क्रमागत_helper_info(kcontrol, uinfo, num_conns, texts);
पूर्ण

अटल पूर्णांक ad1988_स्वतः_smux_क्रमागत_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ad198x_spec *spec = codec->spec;

	ucontrol->value.क्रमागतerated.item[0] = spec->cur_smux;
	वापस 0;
पूर्ण

अटल पूर्णांक ad1988_स्वतः_smux_क्रमागत_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा ad198x_spec *spec = codec->spec;
	अचिन्हित पूर्णांक val = ucontrol->value.क्रमागतerated.item[0];
	काष्ठा nid_path *path;
	पूर्णांक num_conns = spec->num_smux_conns;

	अगर (val >= num_conns)
		वापस -EINVAL;
	अगर (spec->cur_smux == val)
		वापस 0;

	mutex_lock(&codec->control_mutex);
	path = snd_hda_get_path_from_idx(codec,
					 spec->smux_paths[spec->cur_smux]);
	अगर (path)
		snd_hda_activate_path(codec, path, false, true);
	path = snd_hda_get_path_from_idx(codec, spec->smux_paths[val]);
	अगर (path)
		snd_hda_activate_path(codec, path, true, true);
	spec->cur_smux = val;
	mutex_unlock(&codec->control_mutex);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new ad1988_स्वतः_smux_mixer = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "IEC958 Playback Source",
	.info = ad1988_स्वतः_smux_क्रमागत_info,
	.get = ad1988_स्वतः_smux_क्रमागत_get,
	.put = ad1988_स्वतः_smux_क्रमागत_put,
पूर्ण;

अटल पूर्णांक ad1988_स्वतः_init(काष्ठा hda_codec *codec)
अणु
	काष्ठा ad198x_spec *spec = codec->spec;
	पूर्णांक i, err;

	err = snd_hda_gen_init(codec);
	अगर (err < 0)
		वापस err;
	अगर (!spec->gen.स्वतःcfg.dig_outs)
		वापस 0;

	क्रम (i = 0; i < 4; i++) अणु
		काष्ठा nid_path *path;
		path = snd_hda_get_path_from_idx(codec, spec->smux_paths[i]);
		अगर (path)
			snd_hda_activate_path(codec, path, path->active, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad1988_add_spdअगर_mux_ctl(काष्ठा hda_codec *codec)
अणु
	काष्ठा ad198x_spec *spec = codec->spec;
	पूर्णांक i, num_conns;
	/* we create four अटल faked paths, since AD codecs have odd
	 * widget connections regarding the SPDIF out source
	 */
	अटल स्थिर काष्ठा nid_path fake_paths[4] = अणु
		अणु
			.depth = 3,
			.path = अणु 0x02, 0x1d, 0x1b पूर्ण,
			.idx = अणु 0, 0, 0 पूर्ण,
			.multi = अणु 0, 0, 0 पूर्ण,
		पूर्ण,
		अणु
			.depth = 4,
			.path = अणु 0x08, 0x0b, 0x1d, 0x1b पूर्ण,
			.idx = अणु 0, 0, 1, 0 पूर्ण,
			.multi = अणु 0, 1, 0, 0 पूर्ण,
		पूर्ण,
		अणु
			.depth = 4,
			.path = अणु 0x09, 0x0b, 0x1d, 0x1b पूर्ण,
			.idx = अणु 0, 1, 1, 0 पूर्ण,
			.multi = अणु 0, 1, 0, 0 पूर्ण,
		पूर्ण,
		अणु
			.depth = 4,
			.path = अणु 0x0f, 0x0b, 0x1d, 0x1b पूर्ण,
			.idx = अणु 0, 2, 1, 0 पूर्ण,
			.multi = अणु 0, 1, 0, 0 पूर्ण,
		पूर्ण,
	पूर्ण;

	/* SPDIF source mux appears to be present only on AD1988A */
	अगर (!spec->gen.स्वतःcfg.dig_outs ||
	    get_wcaps_type(get_wcaps(codec, 0x1d)) != AC_WID_AUD_MIX)
		वापस 0;

	num_conns = snd_hda_get_num_conns(codec, 0x0b) + 1;
	अगर (num_conns != 3 && num_conns != 4)
		वापस 0;
	spec->num_smux_conns = num_conns;

	क्रम (i = 0; i < num_conns; i++) अणु
		काष्ठा nid_path *path = snd_array_new(&spec->gen.paths);
		अगर (!path)
			वापस -ENOMEM;
		*path = fake_paths[i];
		अगर (!i)
			path->active = 1;
		spec->smux_paths[i] = snd_hda_get_path_idx(codec, path);
	पूर्ण

	अगर (!snd_hda_gen_add_kctl(&spec->gen, शून्य, &ad1988_स्वतः_smux_mixer))
		वापस -ENOMEM;

	codec->patch_ops.init = ad1988_स्वतः_init;

	वापस 0;
पूर्ण

/*
 */

क्रमागत अणु
	AD1988_FIXUP_6STACK_DIG,
पूर्ण;

अटल स्थिर काष्ठा hda_fixup ad1988_fixups[] = अणु
	[AD1988_FIXUP_6STACK_DIG] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			अणु 0x11, 0x02214130 पूर्ण, /* front-hp */
			अणु 0x12, 0x01014010 पूर्ण, /* line-out */
			अणु 0x14, 0x02a19122 पूर्ण, /* front-mic */
			अणु 0x15, 0x01813021 पूर्ण, /* line-in */
			अणु 0x16, 0x01011012 पूर्ण, /* line-out */
			अणु 0x17, 0x01a19020 पूर्ण, /* mic */
			अणु 0x1b, 0x0145f1f0 पूर्ण, /* SPDIF */
			अणु 0x24, 0x01016011 पूर्ण, /* line-out */
			अणु 0x25, 0x01012013 पूर्ण, /* line-out */
			अणु पूर्ण
		पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_model_fixup ad1988_fixup_models[] = अणु
	अणु .id = AD1988_FIXUP_6STACK_DIG, .name = "6stack-dig" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक patch_ad1988(काष्ठा hda_codec *codec)
अणु
	काष्ठा ad198x_spec *spec;
	पूर्णांक err;

	err = alloc_ad_spec(codec);
	अगर (err < 0)
		वापस err;
	spec = codec->spec;

	spec->gen.mixer_nid = 0x20;
	spec->gen.mixer_merge_nid = 0x21;
	spec->gen.beep_nid = 0x10;
	set_beep_amp(spec, 0x10, 0, HDA_OUTPUT);

	snd_hda_pick_fixup(codec, ad1988_fixup_models, शून्य, ad1988_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	err = ad198x_parse_स्वतः_config(codec, true);
	अगर (err < 0)
		जाओ error;
	err = ad1988_add_spdअगर_mux_ctl(codec);
	अगर (err < 0)
		जाओ error;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;

 error:
	snd_hda_gen_मुक्त(codec);
	वापस err;
पूर्ण


/*
 * AD1884 / AD1984
 *
 * port-B - front line/mic-in
 * port-E - aux in/out
 * port-F - aux in/out
 * port-C - rear line/mic-in
 * port-D - rear line/hp-out
 * port-A - front line/hp-out
 *
 * AD1984 = AD1884 + two digital mic-ins
 *
 * AD1883 / AD1884A / AD1984A / AD1984B
 *
 * port-B (0x14) - front mic-in
 * port-E (0x1c) - rear mic-in
 * port-F (0x16) - CD / ext out
 * port-C (0x15) - rear line-in
 * port-D (0x12) - rear line-out
 * port-A (0x11) - front hp-out
 *
 * AD1984A = AD1884A + digital-mic
 * AD1883 = equivalent with AD1984A
 * AD1984B = AD1984A + extra SPDIF-out
 */

/* set the upper-limit क्रम mixer amp to 0dB क्रम aव्योमing the possible
 * damage by overloading
 */
अटल व्योम ad1884_fixup_amp_override(काष्ठा hda_codec *codec,
				      स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action == HDA_FIXUP_ACT_PRE_PROBE)
		snd_hda_override_amp_caps(codec, 0x20, HDA_INPUT,
					  (0x17 << AC_AMPCAP_OFFSET_SHIFT) |
					  (0x17 << AC_AMPCAP_NUM_STEPS_SHIFT) |
					  (0x05 << AC_AMPCAP_STEP_SIZE_SHIFT) |
					  (1 << AC_AMPCAP_MUTE_SHIFT));
पूर्ण

/* toggle GPIO1 according to the mute state */
अटल व्योम ad1884_vmaster_hp_gpio_hook(व्योम *निजी_data, पूर्णांक enabled)
अणु
	काष्ठा hda_codec *codec = निजी_data;
	काष्ठा ad198x_spec *spec = codec->spec;

	अगर (spec->eapd_nid)
		ad_vmaster_eapd_hook(निजी_data, enabled);
	snd_hda_codec_ग_लिखो_cache(codec, 0x01, 0,
				   AC_VERB_SET_GPIO_DATA,
				   enabled ? 0x00 : 0x02);
पूर्ण

अटल व्योम ad1884_fixup_hp_eapd(काष्ठा hda_codec *codec,
				 स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा ad198x_spec *spec = codec->spec;

	चयन (action) अणु
	हाल HDA_FIXUP_ACT_PRE_PROBE:
		spec->gen.vmaster_mute.hook = ad1884_vmaster_hp_gpio_hook;
		spec->gen.own_eapd_ctl = 1;
		snd_hda_codec_ग_लिखो_cache(codec, 0x01, 0,
					  AC_VERB_SET_GPIO_MASK, 0x02);
		snd_hda_codec_ग_लिखो_cache(codec, 0x01, 0,
					  AC_VERB_SET_GPIO_सूचीECTION, 0x02);
		snd_hda_codec_ग_लिखो_cache(codec, 0x01, 0,
					  AC_VERB_SET_GPIO_DATA, 0x02);
		अवरोध;
	हाल HDA_FIXUP_ACT_PROBE:
		अगर (spec->gen.स्वतःcfg.line_out_type == AUTO_PIN_SPEAKER_OUT)
			spec->eapd_nid = spec->gen.स्वतःcfg.line_out_pins[0];
		अन्यथा
			spec->eapd_nid = spec->gen.स्वतःcfg.speaker_pins[0];
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ad1884_fixup_thinkpad(काष्ठा hda_codec *codec,
				  स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा ad198x_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		spec->gen.keep_eapd_on = 1;
		spec->gen.vmaster_mute.hook = ad_vmaster_eapd_hook;
		spec->eapd_nid = 0x12;
		/* Analog PC Beeper - allow firmware/ACPI beeps */
		spec->beep_amp = HDA_COMPOSE_AMP_VAL(0x20, 3, 3, HDA_INPUT);
		spec->gen.beep_nid = 0; /* no digital beep */
	पूर्ण
पूर्ण

/* set magic COEFs क्रम dmic */
अटल स्थिर काष्ठा hda_verb ad1884_dmic_init_verbs[] = अणु
	अणु0x01, AC_VERB_SET_COEF_INDEX, 0x13f7पूर्ण,
	अणु0x01, AC_VERB_SET_PROC_COEF, 0x08पूर्ण,
	अणुपूर्ण
पूर्ण;

क्रमागत अणु
	AD1884_FIXUP_AMP_OVERRIDE,
	AD1884_FIXUP_HP_EAPD,
	AD1884_FIXUP_DMIC_COEF,
	AD1884_FIXUP_THINKPAD,
	AD1884_FIXUP_HP_TOUCHSMART,
पूर्ण;

अटल स्थिर काष्ठा hda_fixup ad1884_fixups[] = अणु
	[AD1884_FIXUP_AMP_OVERRIDE] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = ad1884_fixup_amp_override,
	पूर्ण,
	[AD1884_FIXUP_HP_EAPD] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = ad1884_fixup_hp_eapd,
		.chained = true,
		.chain_id = AD1884_FIXUP_AMP_OVERRIDE,
	पूर्ण,
	[AD1884_FIXUP_DMIC_COEF] = अणु
		.type = HDA_FIXUP_VERBS,
		.v.verbs = ad1884_dmic_init_verbs,
	पूर्ण,
	[AD1884_FIXUP_THINKPAD] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = ad1884_fixup_thinkpad,
		.chained = true,
		.chain_id = AD1884_FIXUP_DMIC_COEF,
	पूर्ण,
	[AD1884_FIXUP_HP_TOUCHSMART] = अणु
		.type = HDA_FIXUP_VERBS,
		.v.verbs = ad1884_dmic_init_verbs,
		.chained = true,
		.chain_id = AD1884_FIXUP_HP_EAPD,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk ad1884_fixup_tbl[] = अणु
	SND_PCI_QUIRK(0x103c, 0x2a82, "HP Touchsmart", AD1884_FIXUP_HP_TOUCHSMART),
	SND_PCI_QUIRK_VENDOR(0x103c, "HP", AD1884_FIXUP_HP_EAPD),
	SND_PCI_QUIRK_VENDOR(0x17aa, "Lenovo Thinkpad", AD1884_FIXUP_THINKPAD),
	अणुपूर्ण
पूर्ण;


अटल पूर्णांक patch_ad1884(काष्ठा hda_codec *codec)
अणु
	काष्ठा ad198x_spec *spec;
	पूर्णांक err;

	err = alloc_ad_spec(codec);
	अगर (err < 0)
		वापस err;
	spec = codec->spec;

	spec->gen.mixer_nid = 0x20;
	spec->gen.mixer_merge_nid = 0x21;
	spec->gen.beep_nid = 0x10;
	set_beep_amp(spec, 0x10, 0, HDA_OUTPUT);

	snd_hda_pick_fixup(codec, शून्य, ad1884_fixup_tbl, ad1884_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	err = ad198x_parse_स्वतः_config(codec, true);
	अगर (err < 0)
		जाओ error;
	err = ad1983_add_spdअगर_mux_ctl(codec);
	अगर (err < 0)
		जाओ error;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;

 error:
	snd_hda_gen_मुक्त(codec);
	वापस err;
पूर्ण

/*
 * AD1882 / AD1882A
 *
 * port-A - front hp-out
 * port-B - front mic-in
 * port-C - rear line-in, shared surr-out (3stack)
 * port-D - rear line-out
 * port-E - rear mic-in, shared clfe-out (3stack)
 * port-F - rear surr-out (6stack)
 * port-G - rear clfe-out (6stack)
 */

अटल पूर्णांक patch_ad1882(काष्ठा hda_codec *codec)
अणु
	काष्ठा ad198x_spec *spec;
	पूर्णांक err;

	err = alloc_ad_spec(codec);
	अगर (err < 0)
		वापस err;
	spec = codec->spec;

	spec->gen.mixer_nid = 0x20;
	spec->gen.mixer_merge_nid = 0x21;
	spec->gen.beep_nid = 0x10;
	set_beep_amp(spec, 0x10, 0, HDA_OUTPUT);
	err = ad198x_parse_स्वतः_config(codec, true);
	अगर (err < 0)
		जाओ error;
	err = ad1988_add_spdअगर_mux_ctl(codec);
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
अटल स्थिर काष्ठा hda_device_id snd_hda_id_analog[] = अणु
	HDA_CODEC_ENTRY(0x11d4184a, "AD1884A", patch_ad1884),
	HDA_CODEC_ENTRY(0x11d41882, "AD1882", patch_ad1882),
	HDA_CODEC_ENTRY(0x11d41883, "AD1883", patch_ad1884),
	HDA_CODEC_ENTRY(0x11d41884, "AD1884", patch_ad1884),
	HDA_CODEC_ENTRY(0x11d4194a, "AD1984A", patch_ad1884),
	HDA_CODEC_ENTRY(0x11d4194b, "AD1984B", patch_ad1884),
	HDA_CODEC_ENTRY(0x11d41981, "AD1981", patch_ad1981),
	HDA_CODEC_ENTRY(0x11d41983, "AD1983", patch_ad1983),
	HDA_CODEC_ENTRY(0x11d41984, "AD1984", patch_ad1884),
	HDA_CODEC_ENTRY(0x11d41986, "AD1986A", patch_ad1986a),
	HDA_CODEC_ENTRY(0x11d41988, "AD1988", patch_ad1988),
	HDA_CODEC_ENTRY(0x11d4198b, "AD1988B", patch_ad1988),
	HDA_CODEC_ENTRY(0x11d4882a, "AD1882A", patch_ad1882),
	HDA_CODEC_ENTRY(0x11d4989a, "AD1989A", patch_ad1988),
	HDA_CODEC_ENTRY(0x11d4989b, "AD1989B", patch_ad1988),
	अणुपूर्ण /* terminator */
पूर्ण;
MODULE_DEVICE_TABLE(hdaudio, snd_hda_id_analog);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Analog Devices HD-audio codec");

अटल काष्ठा hda_codec_driver analog_driver = अणु
	.id = snd_hda_id_analog,
पूर्ण;

module_hda_codec_driver(analog_driver);
