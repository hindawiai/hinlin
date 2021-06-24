<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Universal Interface क्रम Intel High Definition Audio Codec
 *
 * HD audio पूर्णांकerface patch क्रम VIA VT17xx/VT18xx/VT20xx codec
 *
 *  (C) 2006-2009 VIA Technology, Inc.
 *  (C) 2006-2008 Takashi Iwai <tiwai@suse.de>
 */

/* * * * * * * * * * * * * * Release History * * * * * * * * * * * * * * * * */
/*									     */
/* 2006-03-03  Lydia Wang  Create the basic patch to support VT1708 codec    */
/* 2006-03-14  Lydia Wang  Modअगरy hard code क्रम some pin widget nid	     */
/* 2006-08-02  Lydia Wang  Add support to VT1709 codec			     */
/* 2006-09-08  Lydia Wang  Fix पूर्णांकernal loopback recording source select bug */
/* 2007-09-12  Lydia Wang  Add EAPD enable during driver initialization	     */
/* 2007-09-17  Lydia Wang  Add VT1708B codec support			    */
/* 2007-11-14  Lydia Wang  Add VT1708A codec HP and CD pin connect config    */
/* 2008-02-03  Lydia Wang  Fix Rear channels and Back channels inverse issue */
/* 2008-03-06  Lydia Wang  Add VT1702 codec and VT1708S codec support	     */
/* 2008-04-09  Lydia Wang  Add mute front speaker when HP plugin	     */
/* 2008-04-09  Lydia Wang  Add Independent HP feature			     */
/* 2008-05-28  Lydia Wang  Add second S/PDIF Out support क्रम VT1702	     */
/* 2008-09-15  Logan Li	   Add VT1708S Mic Boost workaround/backकरोor	     */
/* 2009-02-16  Logan Li	   Add support क्रम VT1718S			     */
/* 2009-03-13  Logan Li	   Add support क्रम VT1716S			     */
/* 2009-04-14  Lydai Wang  Add support क्रम VT1828S and VT2020		     */
/* 2009-07-08  Lydia Wang  Add support क्रम VT2002P			     */
/* 2009-07-21  Lydia Wang  Add support क्रम VT1812			     */
/* 2009-09-19  Lydia Wang  Add support क्रम VT1818S			     */
/*									     */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/hda_codec.h>
#समावेश "hda_local.h"
#समावेश "hda_auto_parser.h"
#समावेश "hda_jack.h"
#समावेश "hda_generic.h"

/* Pin Widget NID */
#घोषणा VT1708_HP_PIN_NID	0x20
#घोषणा VT1708_CD_PIN_NID	0x24

क्रमागत VIA_HDA_CODEC अणु
	UNKNOWN = -1,
	VT1708,
	VT1709_10CH,
	VT1709_6CH,
	VT1708B_8CH,
	VT1708B_4CH,
	VT1708S,
	VT1708BCE,
	VT1702,
	VT1718S,
	VT1716S,
	VT2002P,
	VT1812,
	VT1802,
	VT1705CF,
	VT1808,
	CODEC_TYPES,
पूर्ण;

#घोषणा VT2002P_COMPATIBLE(spec) \
	((spec)->codec_type == VT2002P ||\
	 (spec)->codec_type == VT1812 ||\
	 (spec)->codec_type == VT1802)

काष्ठा via_spec अणु
	काष्ठा hda_gen_spec gen;

	/* HP mode source */
	अचिन्हित पूर्णांक dmic_enabled;
	क्रमागत VIA_HDA_CODEC codec_type;

	/* analog low-घातer control */
	bool alc_mode;

	/* work to check hp jack state */
	पूर्णांक hp_work_active;
	पूर्णांक vt1708_jack_detect;
पूर्ण;

अटल क्रमागत VIA_HDA_CODEC get_codec_type(काष्ठा hda_codec *codec);
अटल व्योम via_playback_pcm_hook(काष्ठा hda_pcm_stream *hinfo,
				  काष्ठा hda_codec *codec,
				  काष्ठा snd_pcm_substream *substream,
				  पूर्णांक action);

अटल स्थिर काष्ठा hda_codec_ops via_patch_ops; /* defined below */

अटल काष्ठा via_spec *via_new_spec(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (spec == शून्य)
		वापस शून्य;

	codec->spec = spec;
	snd_hda_gen_spec_init(&spec->gen);
	spec->codec_type = get_codec_type(codec);
	/* VT1708BCE & VT1708S are almost same */
	अगर (spec->codec_type == VT1708BCE)
		spec->codec_type = VT1708S;
	spec->gen.indep_hp = 1;
	spec->gen.keep_eapd_on = 1;
	spec->gen.dac_min_mute = 1;
	spec->gen.pcm_playback_hook = via_playback_pcm_hook;
	spec->gen.add_stereo_mix_input = HDA_HINT_STEREO_MIX_AUTO;
	codec->घातer_save_node = 1;
	spec->gen.घातer_करोwn_unused = 1;
	codec->patch_ops = via_patch_ops;
	वापस spec;
पूर्ण

अटल क्रमागत VIA_HDA_CODEC get_codec_type(काष्ठा hda_codec *codec)
अणु
	u32 venकरोr_id = codec->core.venकरोr_id;
	u16 ven_id = venकरोr_id >> 16;
	u16 dev_id = venकरोr_id & 0xffff;
	क्रमागत VIA_HDA_CODEC codec_type;

	/* get codec type */
	अगर (ven_id != 0x1106)
		codec_type = UNKNOWN;
	अन्यथा अगर (dev_id >= 0x1708 && dev_id <= 0x170b)
		codec_type = VT1708;
	अन्यथा अगर (dev_id >= 0xe710 && dev_id <= 0xe713)
		codec_type = VT1709_10CH;
	अन्यथा अगर (dev_id >= 0xe714 && dev_id <= 0xe717)
		codec_type = VT1709_6CH;
	अन्यथा अगर (dev_id >= 0xe720 && dev_id <= 0xe723) अणु
		codec_type = VT1708B_8CH;
		अगर (snd_hda_param_पढ़ो(codec, 0x16, AC_PAR_CONNLIST_LEN) == 0x7)
			codec_type = VT1708BCE;
	पूर्ण अन्यथा अगर (dev_id >= 0xe724 && dev_id <= 0xe727)
		codec_type = VT1708B_4CH;
	अन्यथा अगर ((dev_id & 0xfff) == 0x397
		 && (dev_id >> 12) < 8)
		codec_type = VT1708S;
	अन्यथा अगर ((dev_id & 0xfff) == 0x398
		 && (dev_id >> 12) < 8)
		codec_type = VT1702;
	अन्यथा अगर ((dev_id & 0xfff) == 0x428
		 && (dev_id >> 12) < 8)
		codec_type = VT1718S;
	अन्यथा अगर (dev_id == 0x0433 || dev_id == 0xa721)
		codec_type = VT1716S;
	अन्यथा अगर (dev_id == 0x0441 || dev_id == 0x4441)
		codec_type = VT1718S;
	अन्यथा अगर (dev_id == 0x0438 || dev_id == 0x4438)
		codec_type = VT2002P;
	अन्यथा अगर (dev_id == 0x0448)
		codec_type = VT1812;
	अन्यथा अगर (dev_id == 0x0440)
		codec_type = VT1708S;
	अन्यथा अगर ((dev_id & 0xfff) == 0x446)
		codec_type = VT1802;
	अन्यथा अगर (dev_id == 0x4760)
		codec_type = VT1705CF;
	अन्यथा अगर (dev_id == 0x4761 || dev_id == 0x4762)
		codec_type = VT1808;
	अन्यथा
		codec_type = UNKNOWN;
	वापस codec_type;
पूर्ण;

अटल व्योम analog_low_current_mode(काष्ठा hda_codec *codec);
अटल bool is_aa_path_mute(काष्ठा hda_codec *codec);

#घोषणा hp_detect_with_aa(codec) \
	(snd_hda_get_bool_hपूर्णांक(codec, "analog_loopback_hp_detect") == 1 && \
	 !is_aa_path_mute(codec))

अटल व्योम vt1708_stop_hp_work(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec = codec->spec;
	अगर (spec->codec_type != VT1708 || !spec->gen.स्वतःcfg.hp_outs)
		वापस;
	अगर (spec->hp_work_active) अणु
		snd_hda_codec_ग_लिखो(codec, 0x1, 0, 0xf81, 1);
		codec->jackpoll_पूर्णांकerval = 0;
		cancel_delayed_work_sync(&codec->jackpoll_work);
		spec->hp_work_active = false;
	पूर्ण
पूर्ण

अटल व्योम vt1708_update_hp_work(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec = codec->spec;
	अगर (spec->codec_type != VT1708 || !spec->gen.स्वतःcfg.hp_outs)
		वापस;
	अगर (spec->vt1708_jack_detect) अणु
		अगर (!spec->hp_work_active) अणु
			codec->jackpoll_पूर्णांकerval = msecs_to_jअगरfies(100);
			snd_hda_codec_ग_लिखो(codec, 0x1, 0, 0xf81, 0);
			schedule_delayed_work(&codec->jackpoll_work, 0);
			spec->hp_work_active = true;
		पूर्ण
	पूर्ण अन्यथा अगर (!hp_detect_with_aa(codec))
		vt1708_stop_hp_work(codec);
पूर्ण

अटल पूर्णांक via_pin_घातer_ctl_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	वापस snd_hda_क्रमागत_bool_helper_info(kcontrol, uinfo);
पूर्ण

अटल पूर्णांक via_pin_घातer_ctl_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा via_spec *spec = codec->spec;

	ucontrol->value.क्रमागतerated.item[0] = spec->gen.घातer_करोwn_unused;
	वापस 0;
पूर्ण

अटल पूर्णांक via_pin_घातer_ctl_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा via_spec *spec = codec->spec;
	bool val = !!ucontrol->value.क्रमागतerated.item[0];

	अगर (val == spec->gen.घातer_करोwn_unused)
		वापस 0;
	/* codec->घातer_save_node = val; */ /* widget PM seems yet broken */
	spec->gen.घातer_करोwn_unused = val;
	analog_low_current_mode(codec);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new via_pin_घातer_ctl_क्रमागत = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Dynamic Power-Control",
	.info = via_pin_घातer_ctl_info,
	.get = via_pin_घातer_ctl_get,
	.put = via_pin_घातer_ctl_put,
पूर्ण;

#अगर_घोषित CONFIG_SND_HDA_INPUT_BEEP
/* additional beep mixers; the actual parameters are overwritten at build */
अटल स्थिर काष्ठा snd_kcontrol_new via_beep_mixer[] = अणु
	HDA_CODEC_VOLUME_MONO("Beep Playback Volume", 0, 1, 0, HDA_OUTPUT),
	HDA_CODEC_MUTE_BEEP_MONO("Beep Playback Switch", 0, 1, 0, HDA_OUTPUT),
पूर्ण;

अटल पूर्णांक set_beep_amp(काष्ठा via_spec *spec, hda_nid_t nid,
			पूर्णांक idx, पूर्णांक dir)
अणु
	काष्ठा snd_kcontrol_new *knew;
	अचिन्हित पूर्णांक beep_amp = HDA_COMPOSE_AMP_VAL(nid, 1, idx, dir);
	पूर्णांक i;

	spec->gen.beep_nid = nid;
	क्रम (i = 0; i < ARRAY_SIZE(via_beep_mixer); i++) अणु
		knew = snd_hda_gen_add_kctl(&spec->gen, शून्य,
					    &via_beep_mixer[i]);
		अगर (!knew)
			वापस -ENOMEM;
		knew->निजी_value = beep_amp;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक स्वतः_parse_beep(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec = codec->spec;
	hda_nid_t nid;

	क्रम_each_hda_codec_node(nid, codec)
		अगर (get_wcaps_type(get_wcaps(codec, nid)) == AC_WID_BEEP)
			वापस set_beep_amp(spec, nid, 0, HDA_OUTPUT);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा स्वतः_parse_beep(codec)	0
#पूर्ण_अगर

/* check AA path's mute status */
अटल bool is_aa_path_mute(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec = codec->spec;
	स्थिर काष्ठा hda_amp_list *p;
	पूर्णांक ch, v;

	p = spec->gen.loopback.amplist;
	अगर (!p)
		वापस true;
	क्रम (; p->nid; p++) अणु
		क्रम (ch = 0; ch < 2; ch++) अणु
			v = snd_hda_codec_amp_पढ़ो(codec, p->nid, ch, p->dir,
						   p->idx);
			अगर (!(v & HDA_AMP_MUTE) && v > 0)
				वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

/* enter/निकास analog low-current mode */
अटल व्योम __analog_low_current_mode(काष्ठा hda_codec *codec, bool क्रमce)
अणु
	काष्ठा via_spec *spec = codec->spec;
	bool enable;
	अचिन्हित पूर्णांक verb, parm;

	अगर (!codec->घातer_save_node)
		enable = false;
	अन्यथा
		enable = is_aa_path_mute(codec) && !spec->gen.active_streams;
	अगर (enable == spec->alc_mode && !क्रमce)
		वापस;
	spec->alc_mode = enable;

	/* decide low current mode's verb & parameter */
	चयन (spec->codec_type) अणु
	हाल VT1708B_8CH:
	हाल VT1708B_4CH:
		verb = 0xf70;
		parm = enable ? 0x02 : 0x00; /* 0x02: 2/3x, 0x00: 1x */
		अवरोध;
	हाल VT1708S:
	हाल VT1718S:
	हाल VT1716S:
		verb = 0xf73;
		parm = enable ? 0x51 : 0xe1; /* 0x51: 4/28x, 0xe1: 1x */
		अवरोध;
	हाल VT1702:
		verb = 0xf73;
		parm = enable ? 0x01 : 0x1d; /* 0x01: 4/40x, 0x1d: 1x */
		अवरोध;
	हाल VT2002P:
	हाल VT1812:
	हाल VT1802:
		verb = 0xf93;
		parm = enable ? 0x00 : 0xe0; /* 0x00: 4/40x, 0xe0: 1x */
		अवरोध;
	हाल VT1705CF:
	हाल VT1808:
		verb = 0xf82;
		parm = enable ? 0x00 : 0xe0;  /* 0x00: 4/40x, 0xe0: 1x */
		अवरोध;
	शेष:
		वापस;		/* other codecs are not supported */
	पूर्ण
	/* send verb */
	snd_hda_codec_ग_लिखो(codec, codec->core.afg, 0, verb, parm);
पूर्ण

अटल व्योम analog_low_current_mode(काष्ठा hda_codec *codec)
अणु
	वापस __analog_low_current_mode(codec, false);
पूर्ण

अटल व्योम via_playback_pcm_hook(काष्ठा hda_pcm_stream *hinfo,
				  काष्ठा hda_codec *codec,
				  काष्ठा snd_pcm_substream *substream,
				  पूर्णांक action)
अणु
	analog_low_current_mode(codec);
	vt1708_update_hp_work(codec);
पूर्ण

अटल व्योम via_मुक्त(काष्ठा hda_codec *codec)
अणु
	vt1708_stop_hp_work(codec);
	snd_hda_gen_मुक्त(codec);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक via_suspend(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec = codec->spec;
	vt1708_stop_hp_work(codec);

	/* Fix pop noise on headphones */
	अगर (spec->codec_type == VT1802)
		snd_hda_shutup_pins(codec);

	वापस 0;
पूर्ण

अटल पूर्णांक via_resume(काष्ठा hda_codec *codec)
अणु
	/* some delay here to make jack detection working (bko#98921) */
	msleep(10);
	codec->patch_ops.init(codec);
	snd_hda_regmap_sync(codec);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक via_check_घातer_status(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	काष्ठा via_spec *spec = codec->spec;
	analog_low_current_mode(codec);
	vt1708_update_hp_work(codec);
	वापस snd_hda_check_amp_list_घातer(codec, &spec->gen.loopback, nid);
पूर्ण
#पूर्ण_अगर

/*
 */

अटल पूर्णांक via_init(काष्ठा hda_codec *codec);

अटल स्थिर काष्ठा hda_codec_ops via_patch_ops = अणु
	.build_controls = snd_hda_gen_build_controls,
	.build_pcms = snd_hda_gen_build_pcms,
	.init = via_init,
	.मुक्त = via_मुक्त,
	.unsol_event = snd_hda_jack_unsol_event,
#अगर_घोषित CONFIG_PM
	.suspend = via_suspend,
	.resume = via_resume,
	.check_घातer_status = via_check_घातer_status,
#पूर्ण_अगर
पूर्ण;


अटल स्थिर काष्ठा hda_verb vt1708_init_verbs[] = अणु
	/* घातer करोwn jack detect function */
	अणु0x1, 0xf81, 0x1पूर्ण,
	अणु पूर्ण
पूर्ण;
अटल व्योम vt1708_set_pinconfig_connect(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अचिन्हित पूर्णांक def_conf;
	अचिन्हित अक्षर seqassoc;

	def_conf = snd_hda_codec_get_pincfg(codec, nid);
	seqassoc = (अचिन्हित अक्षर) get_defcfg_association(def_conf);
	seqassoc = (seqassoc << 4) | get_defcfg_sequence(def_conf);
	अगर (get_defcfg_connect(def_conf) == AC_JACK_PORT_NONE
	    && (seqassoc == 0xf0 || seqassoc == 0xff)) अणु
		def_conf = def_conf & (~(AC_JACK_PORT_BOTH << 30));
		snd_hda_codec_set_pincfg(codec, nid, def_conf);
	पूर्ण

	वापस;
पूर्ण

अटल पूर्णांक vt1708_jack_detect_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा via_spec *spec = codec->spec;

	अगर (spec->codec_type != VT1708)
		वापस 0;
	ucontrol->value.पूर्णांकeger.value[0] = spec->vt1708_jack_detect;
	वापस 0;
पूर्ण

अटल पूर्णांक vt1708_jack_detect_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा via_spec *spec = codec->spec;
	पूर्णांक val;

	अगर (spec->codec_type != VT1708)
		वापस 0;
	val = !!ucontrol->value.पूर्णांकeger.value[0];
	अगर (spec->vt1708_jack_detect == val)
		वापस 0;
	spec->vt1708_jack_detect = val;
	vt1708_update_hp_work(codec);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new vt1708_jack_detect_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Jack Detect",
	.count = 1,
	.info = snd_ctl_boolean_mono_info,
	.get = vt1708_jack_detect_get,
	.put = vt1708_jack_detect_put,
पूर्ण;

अटल स्थिर काष्ठा badness_table via_मुख्य_out_badness = अणु
	.no_primary_dac = 0x10000,
	.no_dac = 0x4000,
	.shared_primary = 0x10000,
	.shared_surr = 0x20,
	.shared_clfe = 0x20,
	.shared_surr_मुख्य = 0x20,
पूर्ण;
अटल स्थिर काष्ठा badness_table via_extra_out_badness = अणु
	.no_primary_dac = 0x4000,
	.no_dac = 0x4000,
	.shared_primary = 0x12,
	.shared_surr = 0x20,
	.shared_clfe = 0x20,
	.shared_surr_मुख्य = 0x10,
पूर्ण;

अटल पूर्णांक via_parse_स्वतः_config(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec = codec->spec;
	पूर्णांक err;

	spec->gen.मुख्य_out_badness = &via_मुख्य_out_badness;
	spec->gen.extra_out_badness = &via_extra_out_badness;

	err = snd_hda_parse_pin_defcfg(codec, &spec->gen.स्वतःcfg, शून्य, 0);
	अगर (err < 0)
		वापस err;

	err = snd_hda_gen_parse_स्वतः_config(codec, &spec->gen.स्वतःcfg);
	अगर (err < 0)
		वापस err;

	err = स्वतः_parse_beep(codec);
	अगर (err < 0)
		वापस err;

	अगर (!snd_hda_gen_add_kctl(&spec->gen, शून्य, &via_pin_घातer_ctl_क्रमागत))
		वापस -ENOMEM;

	/* disable widget PM at start क्रम compatibility */
	codec->घातer_save_node = 0;
	spec->gen.घातer_करोwn_unused = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक via_init(काष्ठा hda_codec *codec)
अणु
	/* init घातer states */
	__analog_low_current_mode(codec, true);

	snd_hda_gen_init(codec);

	vt1708_update_hp_work(codec);

	वापस 0;
पूर्ण

अटल पूर्णांक vt1708_build_controls(काष्ठा hda_codec *codec)
अणु
	/* In order not to create "Phantom Jack" controls,
	   temporary enable jackpoll */
	पूर्णांक err;
	पूर्णांक old_पूर्णांकerval = codec->jackpoll_पूर्णांकerval;
	codec->jackpoll_पूर्णांकerval = msecs_to_jअगरfies(100);
	err = snd_hda_gen_build_controls(codec);
	codec->jackpoll_पूर्णांकerval = old_पूर्णांकerval;
	वापस err;
पूर्ण

अटल पूर्णांक vt1708_build_pcms(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec = codec->spec;
	पूर्णांक i, err;

	err = snd_hda_gen_build_pcms(codec);
	अगर (err < 0 || codec->core.venकरोr_id != 0x11061708)
		वापस err;

	/* We got noisy outमाला_दो on the right channel on VT1708 when
	 * 24bit samples are used.  Until any workaround is found,
	 * disable the 24bit क्रमmat, so far.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(spec->gen.pcm_rec); i++) अणु
		काष्ठा hda_pcm *info = spec->gen.pcm_rec[i];
		अगर (!info)
			जारी;
		अगर (!info->stream[SNDRV_PCM_STREAM_PLAYBACK].substreams ||
		    info->pcm_type != HDA_PCM_TYPE_AUDIO)
			जारी;
		info->stream[SNDRV_PCM_STREAM_PLAYBACK].क्रमmats =
			SNDRV_PCM_FMTBIT_S16_LE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक patch_vt1708(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec;
	पूर्णांक err;

	/* create a codec specअगरic record */
	spec = via_new_spec(codec);
	अगर (spec == शून्य)
		वापस -ENOMEM;

	/* override some patch_ops */
	codec->patch_ops.build_controls = vt1708_build_controls;
	codec->patch_ops.build_pcms = vt1708_build_pcms;
	spec->gen.mixer_nid = 0x17;

	/* set jackpoll_पूर्णांकerval जबतक parsing the codec */
	codec->jackpoll_पूर्णांकerval = msecs_to_jअगरfies(100);
	spec->vt1708_jack_detect = 1;

	/* करोn't support the input jack चयनing due to lack of unsol event */
	/* (it may work with polling, though, but it needs testing) */
	spec->gen.suppress_स्वतः_mic = 1;
	/* Some machines show the broken speaker mute */
	spec->gen.स्वतः_mute_via_amp = 1;

	/* Add HP and CD pin config connect bit re-config action */
	vt1708_set_pinconfig_connect(codec, VT1708_HP_PIN_NID);
	vt1708_set_pinconfig_connect(codec, VT1708_CD_PIN_NID);

	err = snd_hda_add_verbs(codec, vt1708_init_verbs);
	अगर (err < 0)
		जाओ error;

	/* स्वतःmatic parse from the BIOS config */
	err = via_parse_स्वतः_config(codec);
	अगर (err < 0)
		जाओ error;

	/* add jack detect on/off control */
	अगर (!snd_hda_gen_add_kctl(&spec->gen, शून्य, &vt1708_jack_detect_ctl)) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण

	/* clear jackpoll_पूर्णांकerval again; it's set dynamically */
	codec->jackpoll_पूर्णांकerval = 0;

	वापस 0;

 error:
	via_मुक्त(codec);
	वापस err;
पूर्ण

अटल पूर्णांक patch_vt1709(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec;
	पूर्णांक err;

	/* create a codec specअगरic record */
	spec = via_new_spec(codec);
	अगर (spec == शून्य)
		वापस -ENOMEM;

	spec->gen.mixer_nid = 0x18;

	err = via_parse_स्वतः_config(codec);
	अगर (err < 0)
		जाओ error;

	वापस 0;

 error:
	via_मुक्त(codec);
	वापस err;
पूर्ण

अटल पूर्णांक patch_vt1708S(काष्ठा hda_codec *codec);
अटल पूर्णांक patch_vt1708B(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec;
	पूर्णांक err;

	अगर (get_codec_type(codec) == VT1708BCE)
		वापस patch_vt1708S(codec);

	/* create a codec specअगरic record */
	spec = via_new_spec(codec);
	अगर (spec == शून्य)
		वापस -ENOMEM;

	spec->gen.mixer_nid = 0x16;

	/* स्वतःmatic parse from the BIOS config */
	err = via_parse_स्वतः_config(codec);
	अगर (err < 0)
		जाओ error;

	वापस 0;

 error:
	via_मुक्त(codec);
	वापस err;
पूर्ण

/* Patch क्रम VT1708S */
अटल स्थिर काष्ठा hda_verb vt1708S_init_verbs[] = अणु
	/* Enable Mic Boost Volume backकरोor */
	अणु0x1, 0xf98, 0x1पूर्ण,
	/* करोn't bybass mixer */
	अणु0x1, 0xf88, 0xc0पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम override_mic_boost(काष्ठा hda_codec *codec, hda_nid_t pin,
			       पूर्णांक offset, पूर्णांक num_steps, पूर्णांक step_size)
अणु
	snd_hda_override_wcaps(codec, pin,
			       get_wcaps(codec, pin) | AC_WCAP_IN_AMP);
	snd_hda_override_amp_caps(codec, pin, HDA_INPUT,
				  (offset << AC_AMPCAP_OFFSET_SHIFT) |
				  (num_steps << AC_AMPCAP_NUM_STEPS_SHIFT) |
				  (step_size << AC_AMPCAP_STEP_SIZE_SHIFT) |
				  (0 << AC_AMPCAP_MUTE_SHIFT));
पूर्ण

अटल पूर्णांक patch_vt1708S(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec;
	पूर्णांक err;

	/* create a codec specअगरic record */
	spec = via_new_spec(codec);
	अगर (spec == शून्य)
		वापस -ENOMEM;

	spec->gen.mixer_nid = 0x16;
	override_mic_boost(codec, 0x1a, 0, 3, 40);
	override_mic_boost(codec, 0x1e, 0, 3, 40);

	/* correct names क्रम VT1708BCE */
	अगर (get_codec_type(codec) == VT1708BCE)
		snd_hda_codec_set_name(codec, "VT1708BCE");
	/* correct names क्रम VT1705 */
	अगर (codec->core.venकरोr_id == 0x11064397)
		snd_hda_codec_set_name(codec, "VT1705");

	err = snd_hda_add_verbs(codec, vt1708S_init_verbs);
	अगर (err < 0)
		जाओ error;

	/* स्वतःmatic parse from the BIOS config */
	err = via_parse_स्वतः_config(codec);
	अगर (err < 0)
		जाओ error;

	वापस 0;

 error:
	via_मुक्त(codec);
	वापस err;
पूर्ण

/* Patch क्रम VT1702 */

अटल स्थिर काष्ठा hda_verb vt1702_init_verbs[] = अणु
	/* mixer enable */
	अणु0x1, 0xF88, 0x3पूर्ण,
	/* GPIO 0~2 */
	अणु0x1, 0xF82, 0x3Fपूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक patch_vt1702(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec;
	पूर्णांक err;

	/* create a codec specअगरic record */
	spec = via_new_spec(codec);
	अगर (spec == शून्य)
		वापस -ENOMEM;

	spec->gen.mixer_nid = 0x1a;

	/* limit AA path volume to 0 dB */
	snd_hda_override_amp_caps(codec, 0x1A, HDA_INPUT,
				  (0x17 << AC_AMPCAP_OFFSET_SHIFT) |
				  (0x17 << AC_AMPCAP_NUM_STEPS_SHIFT) |
				  (0x5 << AC_AMPCAP_STEP_SIZE_SHIFT) |
				  (1 << AC_AMPCAP_MUTE_SHIFT));

	err = snd_hda_add_verbs(codec, vt1702_init_verbs);
	अगर (err < 0)
		जाओ error;

	/* स्वतःmatic parse from the BIOS config */
	err = via_parse_स्वतः_config(codec);
	अगर (err < 0)
		जाओ error;

	वापस 0;

 error:
	via_मुक्त(codec);
	वापस err;
पूर्ण

/* Patch क्रम VT1718S */

अटल स्थिर काष्ठा hda_verb vt1718S_init_verbs[] = अणु
	/* Enable MW0 adjust Gain 5 */
	अणु0x1, 0xfb2, 0x10पूर्ण,
	/* Enable Boost Volume backकरोor */
	अणु0x1, 0xf88, 0x8पूर्ण,

	अणु पूर्ण
पूर्ण;

/* Add a connection to the primary DAC from AA-mixer क्रम some codecs
 * This isn't listed from the raw info, but the chip has a secret connection.
 */
अटल पूर्णांक add_secret_dac_path(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec = codec->spec;
	पूर्णांक i, nums;
	hda_nid_t conn[8];
	hda_nid_t nid;

	अगर (!spec->gen.mixer_nid)
		वापस 0;
	nums = snd_hda_get_connections(codec, spec->gen.mixer_nid, conn,
				       ARRAY_SIZE(conn) - 1);
	क्रम (i = 0; i < nums; i++) अणु
		अगर (get_wcaps_type(get_wcaps(codec, conn[i])) == AC_WID_AUD_OUT)
			वापस 0;
	पूर्ण

	/* find the primary DAC and add to the connection list */
	क्रम_each_hda_codec_node(nid, codec) अणु
		अचिन्हित पूर्णांक caps = get_wcaps(codec, nid);
		अगर (get_wcaps_type(caps) == AC_WID_AUD_OUT &&
		    !(caps & AC_WCAP_DIGITAL)) अणु
			conn[nums++] = nid;
			वापस snd_hda_override_conn_list(codec,
							  spec->gen.mixer_nid,
							  nums, conn);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक patch_vt1718S(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec;
	पूर्णांक err;

	/* create a codec specअगरic record */
	spec = via_new_spec(codec);
	अगर (spec == शून्य)
		वापस -ENOMEM;

	spec->gen.mixer_nid = 0x21;
	override_mic_boost(codec, 0x2b, 0, 3, 40);
	override_mic_boost(codec, 0x29, 0, 3, 40);
	add_secret_dac_path(codec);

	err = snd_hda_add_verbs(codec, vt1718S_init_verbs);
	अगर (err < 0)
		जाओ error;

	/* स्वतःmatic parse from the BIOS config */
	err = via_parse_स्वतः_config(codec);
	अगर (err < 0)
		जाओ error;

	वापस 0;

 error:
	via_मुक्त(codec);
	वापस err;
पूर्ण

/* Patch क्रम VT1716S */

अटल पूर्णांक vt1716s_dmic_info(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक vt1716s_dmic_get(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	पूर्णांक index = 0;

	index = snd_hda_codec_पढ़ो(codec, 0x26, 0,
					       AC_VERB_GET_CONNECT_SEL, 0);
	अगर (index != -1)
		*ucontrol->value.पूर्णांकeger.value = index;

	वापस 0;
पूर्ण

अटल पूर्णांक vt1716s_dmic_put(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा via_spec *spec = codec->spec;
	पूर्णांक index = *ucontrol->value.पूर्णांकeger.value;

	snd_hda_codec_ग_लिखो(codec, 0x26, 0,
					       AC_VERB_SET_CONNECT_SEL, index);
	spec->dmic_enabled = index;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new vt1716s_dmic_mixer_vol =
	HDA_CODEC_VOLUME("Digital Mic Capture Volume", 0x22, 0x0, HDA_INPUT);
अटल स्थिर काष्ठा snd_kcontrol_new vt1716s_dmic_mixer_sw = अणु
	 .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	 .name = "Digital Mic Capture Switch",
	 .subdevice = HDA_SUBDEV_NID_FLAG | 0x26,
	 .count = 1,
	 .info = vt1716s_dmic_info,
	 .get = vt1716s_dmic_get,
	 .put = vt1716s_dmic_put,
पूर्ण;


/* mono-out mixer elements */
अटल स्थिर काष्ठा snd_kcontrol_new vt1716S_mono_out_mixer =
	HDA_CODEC_MUTE("Mono Playback Switch", 0x2a, 0x0, HDA_OUTPUT);

अटल स्थिर काष्ठा hda_verb vt1716S_init_verbs[] = अणु
	/* Enable Boost Volume backकरोor */
	अणु0x1, 0xf8a, 0x80पूर्ण,
	/* करोn't bybass mixer */
	अणु0x1, 0xf88, 0xc0पूर्ण,
	/* Enable mono output */
	अणु0x1, 0xf90, 0x08पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक patch_vt1716S(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec;
	पूर्णांक err;

	/* create a codec specअगरic record */
	spec = via_new_spec(codec);
	अगर (spec == शून्य)
		वापस -ENOMEM;

	spec->gen.mixer_nid = 0x16;
	override_mic_boost(codec, 0x1a, 0, 3, 40);
	override_mic_boost(codec, 0x1e, 0, 3, 40);

	err = snd_hda_add_verbs(codec, vt1716S_init_verbs);
	अगर (err < 0)
		जाओ error;

	/* स्वतःmatic parse from the BIOS config */
	err = via_parse_स्वतः_config(codec);
	अगर (err < 0)
		जाओ error;

	अगर (!snd_hda_gen_add_kctl(&spec->gen, शून्य, &vt1716s_dmic_mixer_vol) ||
	    !snd_hda_gen_add_kctl(&spec->gen, शून्य, &vt1716s_dmic_mixer_sw) ||
	    !snd_hda_gen_add_kctl(&spec->gen, शून्य, &vt1716S_mono_out_mixer)) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण

	वापस 0;

 error:
	via_मुक्त(codec);
	वापस err;
पूर्ण

/* क्रम vt2002P */

अटल स्थिर काष्ठा hda_verb vt2002P_init_verbs[] = अणु
	/* Class-D speaker related verbs */
	अणु0x1, 0xfe0, 0x4पूर्ण,
	अणु0x1, 0xfe9, 0x80पूर्ण,
	अणु0x1, 0xfe2, 0x22पूर्ण,
	/* Enable Boost Volume backकरोor */
	अणु0x1, 0xfb9, 0x24पूर्ण,
	/* Enable AOW0 to MW9 */
	अणु0x1, 0xfb8, 0x88पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_verb vt1802_init_verbs[] = अणु
	/* Enable Boost Volume backकरोor */
	अणु0x1, 0xfb9, 0x24पूर्ण,
	/* Enable AOW0 to MW9 */
	अणु0x1, 0xfb8, 0x88पूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 * pin fix-up
 */
क्रमागत अणु
	VIA_FIXUP_INTMIC_BOOST,
	VIA_FIXUP_ASUS_G75,
	VIA_FIXUP_POWER_SAVE,
पूर्ण;

अटल व्योम via_fixup_पूर्णांकmic_boost(काष्ठा hda_codec *codec,
				  स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action == HDA_FIXUP_ACT_PRE_PROBE)
		override_mic_boost(codec, 0x30, 0, 2, 40);
पूर्ण

अटल व्योम via_fixup_घातer_save(काष्ठा hda_codec *codec,
				 स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action == HDA_FIXUP_ACT_PRE_PROBE)
		codec->घातer_save_node = 0;
पूर्ण

अटल स्थिर काष्ठा hda_fixup via_fixups[] = अणु
	[VIA_FIXUP_INTMIC_BOOST] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = via_fixup_पूर्णांकmic_boost,
	पूर्ण,
	[VIA_FIXUP_ASUS_G75] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			/* set 0x24 and 0x33 as speakers */
			अणु 0x24, 0x991301f0 पूर्ण,
			अणु 0x33, 0x991301f1 पूर्ण, /* subwoofer */
			अणु पूर्ण
		पूर्ण
	पूर्ण,
	[VIA_FIXUP_POWER_SAVE] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = via_fixup_घातer_save,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk vt2002p_fixups[] = अणु
	SND_PCI_QUIRK(0x1043, 0x1487, "Asus G75", VIA_FIXUP_ASUS_G75),
	SND_PCI_QUIRK(0x1043, 0x8532, "Asus X202E", VIA_FIXUP_INTMIC_BOOST),
	SND_PCI_QUIRK_VENDOR(0x1558, "Clevo", VIA_FIXUP_POWER_SAVE),
	अणुपूर्ण
पूर्ण;

/* NIDs 0x24 and 0x33 on VT1802 have connections to non-existing NID 0x3e
 * Replace this with mixer NID 0x1c
 */
अटल व्योम fix_vt1802_connections(काष्ठा hda_codec *codec)
अणु
	अटल स्थिर hda_nid_t conn_24[] = अणु 0x14, 0x1c पूर्ण;
	अटल स्थिर hda_nid_t conn_33[] = अणु 0x1c पूर्ण;

	snd_hda_override_conn_list(codec, 0x24, ARRAY_SIZE(conn_24), conn_24);
	snd_hda_override_conn_list(codec, 0x33, ARRAY_SIZE(conn_33), conn_33);
पूर्ण

/* patch क्रम vt2002P */
अटल पूर्णांक patch_vt2002P(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec;
	पूर्णांक err;

	/* create a codec specअगरic record */
	spec = via_new_spec(codec);
	अगर (spec == शून्य)
		वापस -ENOMEM;

	spec->gen.mixer_nid = 0x21;
	override_mic_boost(codec, 0x2b, 0, 3, 40);
	override_mic_boost(codec, 0x29, 0, 3, 40);
	अगर (spec->codec_type == VT1802)
		fix_vt1802_connections(codec);
	add_secret_dac_path(codec);

	snd_hda_pick_fixup(codec, शून्य, vt2002p_fixups, via_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	अगर (spec->codec_type == VT1802)
		err = snd_hda_add_verbs(codec, vt1802_init_verbs);
	अन्यथा
		err = snd_hda_add_verbs(codec, vt2002P_init_verbs);
	अगर (err < 0)
		जाओ error;

	/* स्वतःmatic parse from the BIOS config */
	err = via_parse_स्वतः_config(codec);
	अगर (err < 0)
		जाओ error;

	वापस 0;

 error:
	via_मुक्त(codec);
	वापस err;
पूर्ण

/* क्रम vt1812 */

अटल स्थिर काष्ठा hda_verb vt1812_init_verbs[] = अणु
	/* Enable Boost Volume backकरोor */
	अणु0x1, 0xfb9, 0x24पूर्ण,
	/* Enable AOW0 to MW9 */
	अणु0x1, 0xfb8, 0xa8पूर्ण,
	अणु पूर्ण
पूर्ण;

/* patch क्रम vt1812 */
अटल पूर्णांक patch_vt1812(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec;
	पूर्णांक err;

	/* create a codec specअगरic record */
	spec = via_new_spec(codec);
	अगर (spec == शून्य)
		वापस -ENOMEM;

	spec->gen.mixer_nid = 0x21;
	override_mic_boost(codec, 0x2b, 0, 3, 40);
	override_mic_boost(codec, 0x29, 0, 3, 40);
	add_secret_dac_path(codec);

	err = snd_hda_add_verbs(codec, vt1812_init_verbs);
	अगर (err < 0)
		जाओ error;

	/* स्वतःmatic parse from the BIOS config */
	err = via_parse_स्वतः_config(codec);
	अगर (err < 0)
		जाओ error;

	वापस 0;

 error:
	via_मुक्त(codec);
	वापस err;
पूर्ण

/* patch क्रम vt3476 */

अटल स्थिर काष्ठा hda_verb vt3476_init_verbs[] = अणु
	/* Enable DMic 8/16/32K */
	अणु0x1, 0xF7B, 0x30पूर्ण,
	/* Enable Boost Volume backकरोor */
	अणु0x1, 0xFB9, 0x20पूर्ण,
	/* Enable AOW-MW9 path */
	अणु0x1, 0xFB8, 0x10पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक patch_vt3476(काष्ठा hda_codec *codec)
अणु
	काष्ठा via_spec *spec;
	पूर्णांक err;

	/* create a codec specअगरic record */
	spec = via_new_spec(codec);
	अगर (spec == शून्य)
		वापस -ENOMEM;

	spec->gen.mixer_nid = 0x3f;
	add_secret_dac_path(codec);

	err = snd_hda_add_verbs(codec, vt3476_init_verbs);
	अगर (err < 0)
		जाओ error;

	/* स्वतःmatic parse from the BIOS config */
	err = via_parse_स्वतः_config(codec);
	अगर (err < 0)
		जाओ error;

	वापस 0;

 error:
	via_मुक्त(codec);
	वापस err;
पूर्ण

/*
 * patch entries
 */
अटल स्थिर काष्ठा hda_device_id snd_hda_id_via[] = अणु
	HDA_CODEC_ENTRY(0x11061708, "VT1708", patch_vt1708),
	HDA_CODEC_ENTRY(0x11061709, "VT1708", patch_vt1708),
	HDA_CODEC_ENTRY(0x1106170a, "VT1708", patch_vt1708),
	HDA_CODEC_ENTRY(0x1106170b, "VT1708", patch_vt1708),
	HDA_CODEC_ENTRY(0x1106e710, "VT1709 10-Ch", patch_vt1709),
	HDA_CODEC_ENTRY(0x1106e711, "VT1709 10-Ch", patch_vt1709),
	HDA_CODEC_ENTRY(0x1106e712, "VT1709 10-Ch", patch_vt1709),
	HDA_CODEC_ENTRY(0x1106e713, "VT1709 10-Ch", patch_vt1709),
	HDA_CODEC_ENTRY(0x1106e714, "VT1709 6-Ch", patch_vt1709),
	HDA_CODEC_ENTRY(0x1106e715, "VT1709 6-Ch", patch_vt1709),
	HDA_CODEC_ENTRY(0x1106e716, "VT1709 6-Ch", patch_vt1709),
	HDA_CODEC_ENTRY(0x1106e717, "VT1709 6-Ch", patch_vt1709),
	HDA_CODEC_ENTRY(0x1106e720, "VT1708B 8-Ch", patch_vt1708B),
	HDA_CODEC_ENTRY(0x1106e721, "VT1708B 8-Ch", patch_vt1708B),
	HDA_CODEC_ENTRY(0x1106e722, "VT1708B 8-Ch", patch_vt1708B),
	HDA_CODEC_ENTRY(0x1106e723, "VT1708B 8-Ch", patch_vt1708B),
	HDA_CODEC_ENTRY(0x1106e724, "VT1708B 4-Ch", patch_vt1708B),
	HDA_CODEC_ENTRY(0x1106e725, "VT1708B 4-Ch", patch_vt1708B),
	HDA_CODEC_ENTRY(0x1106e726, "VT1708B 4-Ch", patch_vt1708B),
	HDA_CODEC_ENTRY(0x1106e727, "VT1708B 4-Ch", patch_vt1708B),
	HDA_CODEC_ENTRY(0x11060397, "VT1708S", patch_vt1708S),
	HDA_CODEC_ENTRY(0x11061397, "VT1708S", patch_vt1708S),
	HDA_CODEC_ENTRY(0x11062397, "VT1708S", patch_vt1708S),
	HDA_CODEC_ENTRY(0x11063397, "VT1708S", patch_vt1708S),
	HDA_CODEC_ENTRY(0x11064397, "VT1705", patch_vt1708S),
	HDA_CODEC_ENTRY(0x11065397, "VT1708S", patch_vt1708S),
	HDA_CODEC_ENTRY(0x11066397, "VT1708S", patch_vt1708S),
	HDA_CODEC_ENTRY(0x11067397, "VT1708S", patch_vt1708S),
	HDA_CODEC_ENTRY(0x11060398, "VT1702", patch_vt1702),
	HDA_CODEC_ENTRY(0x11061398, "VT1702", patch_vt1702),
	HDA_CODEC_ENTRY(0x11062398, "VT1702", patch_vt1702),
	HDA_CODEC_ENTRY(0x11063398, "VT1702", patch_vt1702),
	HDA_CODEC_ENTRY(0x11064398, "VT1702", patch_vt1702),
	HDA_CODEC_ENTRY(0x11065398, "VT1702", patch_vt1702),
	HDA_CODEC_ENTRY(0x11066398, "VT1702", patch_vt1702),
	HDA_CODEC_ENTRY(0x11067398, "VT1702", patch_vt1702),
	HDA_CODEC_ENTRY(0x11060428, "VT1718S", patch_vt1718S),
	HDA_CODEC_ENTRY(0x11064428, "VT1718S", patch_vt1718S),
	HDA_CODEC_ENTRY(0x11060441, "VT2020", patch_vt1718S),
	HDA_CODEC_ENTRY(0x11064441, "VT1828S", patch_vt1718S),
	HDA_CODEC_ENTRY(0x11060433, "VT1716S", patch_vt1716S),
	HDA_CODEC_ENTRY(0x1106a721, "VT1716S", patch_vt1716S),
	HDA_CODEC_ENTRY(0x11060438, "VT2002P", patch_vt2002P),
	HDA_CODEC_ENTRY(0x11064438, "VT2002P", patch_vt2002P),
	HDA_CODEC_ENTRY(0x11060448, "VT1812", patch_vt1812),
	HDA_CODEC_ENTRY(0x11060440, "VT1818S", patch_vt1708S),
	HDA_CODEC_ENTRY(0x11060446, "VT1802", patch_vt2002P),
	HDA_CODEC_ENTRY(0x11068446, "VT1802", patch_vt2002P),
	HDA_CODEC_ENTRY(0x11064760, "VT1705CF", patch_vt3476),
	HDA_CODEC_ENTRY(0x11064761, "VT1708SCE", patch_vt3476),
	HDA_CODEC_ENTRY(0x11064762, "VT1808", patch_vt3476),
	अणुपूर्ण /* terminator */
पूर्ण;
MODULE_DEVICE_TABLE(hdaudio, snd_hda_id_via);

अटल काष्ठा hda_codec_driver via_driver = अणु
	.id = snd_hda_id_via,
पूर्ण;

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("VIA HD-audio codec");

module_hda_codec_driver(via_driver);
