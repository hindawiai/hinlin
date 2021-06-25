<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HD audio पूर्णांकerface patch क्रम Conexant HDA audio codec
 *
 * Copyright (c) 2006 Pototskiy Akex <alex.pototskiy@gmail.com>
 * 		      Takashi Iwai <tiwai@suse.de>
 * 		      Tobin Davis  <tdavis@dsl-only.net>
 */

#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>

#समावेश <sound/hda_codec.h>
#समावेश "hda_local.h"
#समावेश "hda_auto_parser.h"
#समावेश "hda_beep.h"
#समावेश "hda_jack.h"
#समावेश "hda_generic.h"

काष्ठा conexant_spec अणु
	काष्ठा hda_gen_spec gen;

	/* extra EAPD pins */
	अचिन्हित पूर्णांक num_eapds;
	hda_nid_t eapds[4];
	bool dynamic_eapd;
	hda_nid_t mute_led_eapd;

	अचिन्हित पूर्णांक parse_flags; /* flag क्रम snd_hda_parse_pin_defcfg() */

	/* OPLC XO specअगरic */
	bool recording;
	bool dc_enable;
	अचिन्हित पूर्णांक dc_input_bias; /* offset पूर्णांकo olpc_xo_dc_bias */
	काष्ठा nid_path *dc_mode_path;

	पूर्णांक mute_led_polarity;
	अचिन्हित पूर्णांक gpio_led;
	अचिन्हित पूर्णांक gpio_mute_led_mask;
	अचिन्हित पूर्णांक gpio_mic_led_mask;

पूर्ण;


#अगर_घोषित CONFIG_SND_HDA_INPUT_BEEP
/* additional beep mixers; निजी_value will be overwritten */
अटल स्थिर काष्ठा snd_kcontrol_new cxt_beep_mixer[] = अणु
	HDA_CODEC_VOLUME_MONO("Beep Playback Volume", 0, 1, 0, HDA_OUTPUT),
	HDA_CODEC_MUTE_BEEP_MONO("Beep Playback Switch", 0, 1, 0, HDA_OUTPUT),
पूर्ण;

अटल पूर्णांक set_beep_amp(काष्ठा conexant_spec *spec, hda_nid_t nid,
			पूर्णांक idx, पूर्णांक dir)
अणु
	काष्ठा snd_kcontrol_new *knew;
	अचिन्हित पूर्णांक beep_amp = HDA_COMPOSE_AMP_VAL(nid, 1, idx, dir);
	पूर्णांक i;

	spec->gen.beep_nid = nid;
	क्रम (i = 0; i < ARRAY_SIZE(cxt_beep_mixer); i++) अणु
		knew = snd_hda_gen_add_kctl(&spec->gen, शून्य,
					    &cxt_beep_mixer[i]);
		अगर (!knew)
			वापस -ENOMEM;
		knew->निजी_value = beep_amp;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx_स्वतः_parse_beep(काष्ठा hda_codec *codec)
अणु
	काष्ठा conexant_spec *spec = codec->spec;
	hda_nid_t nid;

	क्रम_each_hda_codec_node(nid, codec)
		अगर (get_wcaps_type(get_wcaps(codec, nid)) == AC_WID_BEEP)
			वापस set_beep_amp(spec, nid, 0, HDA_OUTPUT);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा cx_स्वतः_parse_beep(codec)	0
#पूर्ण_अगर

/*
 * Automatic parser क्रम CX20641 & co
 */

/* parse EAPDs */
अटल व्योम cx_स्वतः_parse_eapd(काष्ठा hda_codec *codec)
अणु
	काष्ठा conexant_spec *spec = codec->spec;
	hda_nid_t nid;

	क्रम_each_hda_codec_node(nid, codec) अणु
		अगर (get_wcaps_type(get_wcaps(codec, nid)) != AC_WID_PIN)
			जारी;
		अगर (!(snd_hda_query_pin_caps(codec, nid) & AC_PINCAP_EAPD))
			जारी;
		spec->eapds[spec->num_eapds++] = nid;
		अगर (spec->num_eapds >= ARRAY_SIZE(spec->eapds))
			अवरोध;
	पूर्ण

	/* NOTE: below is a wild guess; अगर we have more than two EAPDs,
	 * it's a new chip, where EAPDs are supposed to be associated to
	 * pins, and we can control EAPD per pin.
	 * OTOH, अगर only one or two EAPDs are found, it's an old chip,
	 * thus it might control over all pins.
	 */
	अगर (spec->num_eapds > 2)
		spec->dynamic_eapd = 1;
पूर्ण

अटल व्योम cx_स्वतः_turn_eapd(काष्ठा hda_codec *codec, पूर्णांक num_pins,
			      स्थिर hda_nid_t *pins, bool on)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < num_pins; i++) अणु
		अगर (snd_hda_query_pin_caps(codec, pins[i]) & AC_PINCAP_EAPD)
			snd_hda_codec_ग_लिखो(codec, pins[i], 0,
					    AC_VERB_SET_EAPD_BTLENABLE,
					    on ? 0x02 : 0);
	पूर्ण
पूर्ण

/* turn on/off EAPD according to Master चयन */
अटल व्योम cx_स्वतः_vmaster_hook(व्योम *निजी_data, पूर्णांक enabled)
अणु
	काष्ठा hda_codec *codec = निजी_data;
	काष्ठा conexant_spec *spec = codec->spec;

	cx_स्वतः_turn_eapd(codec, spec->num_eapds, spec->eapds, enabled);
पूर्ण

/* turn on/off EAPD according to Master चयन (inversely!) क्रम mute LED */
अटल पूर्णांक cx_स्वतः_vmaster_mute_led(काष्ठा led_classdev *led_cdev,
				    क्रमागत led_brightness brightness)
अणु
	काष्ठा hda_codec *codec = dev_to_hda_codec(led_cdev->dev->parent);
	काष्ठा conexant_spec *spec = codec->spec;

	snd_hda_codec_ग_लिखो(codec, spec->mute_led_eapd, 0,
			    AC_VERB_SET_EAPD_BTLENABLE,
			    brightness ? 0x02 : 0x00);
	वापस 0;
पूर्ण

अटल व्योम cxt_init_gpio_led(काष्ठा hda_codec *codec)
अणु
	काष्ठा conexant_spec *spec = codec->spec;
	अचिन्हित पूर्णांक mask = spec->gpio_mute_led_mask | spec->gpio_mic_led_mask;

	अगर (mask) अणु
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, AC_VERB_SET_GPIO_MASK,
				    mask);
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, AC_VERB_SET_GPIO_सूचीECTION,
				    mask);
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, AC_VERB_SET_GPIO_DATA,
				    spec->gpio_led);
	पूर्ण
पूर्ण

अटल पूर्णांक cx_स्वतः_init(काष्ठा hda_codec *codec)
अणु
	काष्ठा conexant_spec *spec = codec->spec;
	snd_hda_gen_init(codec);
	अगर (!spec->dynamic_eapd)
		cx_स्वतः_turn_eapd(codec, spec->num_eapds, spec->eapds, true);

	cxt_init_gpio_led(codec);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_INIT);

	वापस 0;
पूर्ण

अटल व्योम cx_स्वतः_reboot_notअगरy(काष्ठा hda_codec *codec)
अणु
	काष्ठा conexant_spec *spec = codec->spec;

	/* Turn the problematic codec पूर्णांकo D3 to aव्योम spurious noises
	   from the पूर्णांकernal speaker during (and after) reboot */
	cx_स्वतः_turn_eapd(codec, spec->num_eapds, spec->eapds, false);
	snd_hda_gen_reboot_notअगरy(codec);
पूर्ण

अटल व्योम cx_स्वतः_मुक्त(काष्ठा hda_codec *codec)
अणु
	cx_स्वतः_reboot_notअगरy(codec);
	snd_hda_gen_मुक्त(codec);
पूर्ण

अटल स्थिर काष्ठा hda_codec_ops cx_स्वतः_patch_ops = अणु
	.build_controls = snd_hda_gen_build_controls,
	.build_pcms = snd_hda_gen_build_pcms,
	.init = cx_स्वतः_init,
	.reboot_notअगरy = cx_स्वतः_reboot_notअगरy,
	.मुक्त = cx_स्वतः_मुक्त,
	.unsol_event = snd_hda_jack_unsol_event,
#अगर_घोषित CONFIG_PM
	.check_घातer_status = snd_hda_gen_check_घातer_status,
#पूर्ण_अगर
पूर्ण;

/*
 * pin fix-up
 */
क्रमागत अणु
	CXT_PINCFG_LENOVO_X200,
	CXT_PINCFG_LENOVO_TP410,
	CXT_PINCFG_LEMOTE_A1004,
	CXT_PINCFG_LEMOTE_A1205,
	CXT_PINCFG_COMPAQ_CQ60,
	CXT_FIXUP_STEREO_DMIC,
	CXT_FIXUP_INC_MIC_BOOST,
	CXT_FIXUP_HEADPHONE_MIC_PIN,
	CXT_FIXUP_HEADPHONE_MIC,
	CXT_FIXUP_GPIO1,
	CXT_FIXUP_ASPIRE_DMIC,
	CXT_FIXUP_THINKPAD_ACPI,
	CXT_FIXUP_OLPC_XO,
	CXT_FIXUP_CAP_MIX_AMP,
	CXT_FIXUP_TOSHIBA_P105,
	CXT_FIXUP_HP_530,
	CXT_FIXUP_CAP_MIX_AMP_5047,
	CXT_FIXUP_MUTE_LED_EAPD,
	CXT_FIXUP_HP_DOCK,
	CXT_FIXUP_HP_SPECTRE,
	CXT_FIXUP_HP_GATE_MIC,
	CXT_FIXUP_MUTE_LED_GPIO,
	CXT_FIXUP_HP_ZBOOK_MUTE_LED,
	CXT_FIXUP_HEADSET_MIC,
	CXT_FIXUP_HP_MIC_NO_PRESENCE,
पूर्ण;

/* क्रम hda_fixup_thinkpad_acpi() */
#समावेश "thinkpad_helper.c"

अटल व्योम cxt_fixup_stereo_dmic(काष्ठा hda_codec *codec,
				  स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा conexant_spec *spec = codec->spec;
	spec->gen.inv_dmic_split = 1;
पूर्ण

अटल व्योम cxt5066_increase_mic_boost(काष्ठा hda_codec *codec,
				   स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	snd_hda_override_amp_caps(codec, 0x17, HDA_OUTPUT,
				  (0x3 << AC_AMPCAP_OFFSET_SHIFT) |
				  (0x4 << AC_AMPCAP_NUM_STEPS_SHIFT) |
				  (0x27 << AC_AMPCAP_STEP_SIZE_SHIFT) |
				  (0 << AC_AMPCAP_MUTE_SHIFT));
पूर्ण

अटल व्योम cxt_update_headset_mode(काष्ठा hda_codec *codec)
अणु
	/* The verbs used in this function were tested on a Conexant CX20751/2 codec. */
	पूर्णांक i;
	bool mic_mode = false;
	काष्ठा conexant_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->gen.स्वतःcfg;

	hda_nid_t mux_pin = spec->gen.imux_pins[spec->gen.cur_mux[0]];

	क्रम (i = 0; i < cfg->num_inमाला_दो; i++)
		अगर (cfg->inमाला_दो[i].pin == mux_pin) अणु
			mic_mode = !!cfg->inमाला_दो[i].is_headphone_mic;
			अवरोध;
		पूर्ण

	अगर (mic_mode) अणु
		snd_hda_codec_ग_लिखो_cache(codec, 0x1c, 0, 0x410, 0x7c); /* enable merged mode क्रम analog पूर्णांक-mic */
		spec->gen.hp_jack_present = false;
	पूर्ण अन्यथा अणु
		snd_hda_codec_ग_लिखो_cache(codec, 0x1c, 0, 0x410, 0x54); /* disable merged mode क्रम analog पूर्णांक-mic */
		spec->gen.hp_jack_present = snd_hda_jack_detect(codec, spec->gen.स्वतःcfg.hp_pins[0]);
	पूर्ण

	snd_hda_gen_update_outमाला_दो(codec);
पूर्ण

अटल व्योम cxt_update_headset_mode_hook(काष्ठा hda_codec *codec,
					 काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	cxt_update_headset_mode(codec);
पूर्ण

अटल व्योम cxt_fixup_headphone_mic(काष्ठा hda_codec *codec,
				    स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा conexant_spec *spec = codec->spec;

	चयन (action) अणु
	हाल HDA_FIXUP_ACT_PRE_PROBE:
		spec->parse_flags |= HDA_PINCFG_HEADPHONE_MIC;
		snd_hdac_regmap_add_venकरोr_verb(&codec->core, 0x410);
		अवरोध;
	हाल HDA_FIXUP_ACT_PROBE:
		WARN_ON(spec->gen.cap_sync_hook);
		spec->gen.cap_sync_hook = cxt_update_headset_mode_hook;
		spec->gen.स्वतःmute_hook = cxt_update_headset_mode;
		अवरोध;
	हाल HDA_FIXUP_ACT_INIT:
		cxt_update_headset_mode(codec);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम cxt_fixup_headset_mic(काष्ठा hda_codec *codec,
				    स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा conexant_spec *spec = codec->spec;

	चयन (action) अणु
	हाल HDA_FIXUP_ACT_PRE_PROBE:
		spec->parse_flags |= HDA_PINCFG_HEADSET_MIC;
		अवरोध;
	पूर्ण
पूर्ण

/* OPLC XO 1.5 fixup */

/* OLPC XO-1.5 supports DC input mode (e.g. क्रम use with analog sensors)
 * through the microphone jack.
 * When the user enables this through a mixer चयन, both पूर्णांकernal and
 * बाह्यal microphones are disabled. Gain is fixed at 0dB. In this mode,
 * we also allow the bias to be configured through a separate mixer
 * control. */

#घोषणा update_mic_pin(codec, nid, val)					\
	snd_hda_codec_ग_लिखो_cache(codec, nid, 0,			\
				   AC_VERB_SET_PIN_WIDGET_CONTROL, val)

अटल स्थिर काष्ठा hda_input_mux olpc_xo_dc_bias = अणु
	.num_items = 3,
	.items = अणु
		अणु "Off", PIN_IN पूर्ण,
		अणु "50%", PIN_VREF50 पूर्ण,
		अणु "80%", PIN_VREF80 पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम olpc_xo_update_mic_boost(काष्ठा hda_codec *codec)
अणु
	काष्ठा conexant_spec *spec = codec->spec;
	पूर्णांक ch, val;

	क्रम (ch = 0; ch < 2; ch++) अणु
		val = AC_AMP_SET_OUTPUT |
			(ch ? AC_AMP_SET_RIGHT : AC_AMP_SET_LEFT);
		अगर (!spec->dc_enable)
			val |= snd_hda_codec_amp_पढ़ो(codec, 0x17, ch, HDA_OUTPUT, 0);
		snd_hda_codec_ग_लिखो(codec, 0x17, 0,
				    AC_VERB_SET_AMP_GAIN_MUTE, val);
	पूर्ण
पूर्ण

अटल व्योम olpc_xo_update_mic_pins(काष्ठा hda_codec *codec)
अणु
	काष्ठा conexant_spec *spec = codec->spec;
	पूर्णांक cur_input, val;
	काष्ठा nid_path *path;

	cur_input = spec->gen.input_paths[0][spec->gen.cur_mux[0]];

	/* Set up mic pins क्रम port-B, C and F dynamically as the recording
	 * LED is turned on/off by these pin controls
	 */
	अगर (!spec->dc_enable) अणु
		/* disable DC bias path and pin क्रम port F */
		update_mic_pin(codec, 0x1e, 0);
		snd_hda_activate_path(codec, spec->dc_mode_path, false, false);

		/* update port B (ext mic) and C (पूर्णांक mic) */
		/* OLPC defers mic widget control until when capture is
		 * started because the microphone LED comes on as soon as
		 * these settings are put in place. अगर we did this beक्रमe
		 * recording, it would give the false indication that
		 * recording is happening when it is not.
		 */
		update_mic_pin(codec, 0x1a, spec->recording ?
			       snd_hda_codec_get_pin_target(codec, 0x1a) : 0);
		update_mic_pin(codec, 0x1b, spec->recording ?
			       snd_hda_codec_get_pin_target(codec, 0x1b) : 0);
		/* enable normal mic path */
		path = snd_hda_get_path_from_idx(codec, cur_input);
		अगर (path)
			snd_hda_activate_path(codec, path, true, false);
	पूर्ण अन्यथा अणु
		/* disable normal mic path */
		path = snd_hda_get_path_from_idx(codec, cur_input);
		अगर (path)
			snd_hda_activate_path(codec, path, false, false);

		/* Even though port F is the DC input, the bias is controlled
		 * on port B.  We also leave that port as an active input (but
		 * unselected) in DC mode just in हाल that is necessary to
		 * make the bias setting take effect.
		 */
		अगर (spec->recording)
			val = olpc_xo_dc_bias.items[spec->dc_input_bias].index;
		अन्यथा
			val = 0;
		update_mic_pin(codec, 0x1a, val);
		update_mic_pin(codec, 0x1b, 0);
		/* enable DC bias path and pin */
		update_mic_pin(codec, 0x1e, spec->recording ? PIN_IN : 0);
		snd_hda_activate_path(codec, spec->dc_mode_path, true, false);
	पूर्ण
पूर्ण

/* mic_स्वतःचयन hook */
अटल व्योम olpc_xo_स्वतःmic(काष्ठा hda_codec *codec,
			    काष्ठा hda_jack_callback *jack)
अणु
	काष्ठा conexant_spec *spec = codec->spec;

	/* in DC mode, we करोn't handle स्वतःmic */
	अगर (!spec->dc_enable)
		snd_hda_gen_mic_स्वतःचयन(codec, jack);
	olpc_xo_update_mic_pins(codec);
	अगर (spec->dc_enable)
		olpc_xo_update_mic_boost(codec);
पूर्ण

/* pcm_capture hook */
अटल व्योम olpc_xo_capture_hook(काष्ठा hda_pcm_stream *hinfo,
				 काष्ठा hda_codec *codec,
				 काष्ठा snd_pcm_substream *substream,
				 पूर्णांक action)
अणु
	काष्ठा conexant_spec *spec = codec->spec;

	/* toggle spec->recording flag and update mic pins accordingly
	 * क्रम turning on/off LED
	 */
	चयन (action) अणु
	हाल HDA_GEN_PCM_ACT_PREPARE:
		spec->recording = 1;
		olpc_xo_update_mic_pins(codec);
		अवरोध;
	हाल HDA_GEN_PCM_ACT_CLEANUP:
		spec->recording = 0;
		olpc_xo_update_mic_pins(codec);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक olpc_xo_dc_mode_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा conexant_spec *spec = codec->spec;
	ucontrol->value.पूर्णांकeger.value[0] = spec->dc_enable;
	वापस 0;
पूर्ण

अटल पूर्णांक olpc_xo_dc_mode_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा conexant_spec *spec = codec->spec;
	पूर्णांक dc_enable = !!ucontrol->value.पूर्णांकeger.value[0];

	अगर (dc_enable == spec->dc_enable)
		वापस 0;

	spec->dc_enable = dc_enable;
	olpc_xo_update_mic_pins(codec);
	olpc_xo_update_mic_boost(codec);
	वापस 1;
पूर्ण

अटल पूर्णांक olpc_xo_dc_bias_क्रमागत_get(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा conexant_spec *spec = codec->spec;
	ucontrol->value.क्रमागतerated.item[0] = spec->dc_input_bias;
	वापस 0;
पूर्ण

अटल पूर्णांक olpc_xo_dc_bias_क्रमागत_info(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	वापस snd_hda_input_mux_info(&olpc_xo_dc_bias, uinfo);
पूर्ण

अटल पूर्णांक olpc_xo_dc_bias_क्रमागत_put(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा conexant_spec *spec = codec->spec;
	स्थिर काष्ठा hda_input_mux *imux = &olpc_xo_dc_bias;
	अचिन्हित पूर्णांक idx;

	idx = ucontrol->value.क्रमागतerated.item[0];
	अगर (idx >= imux->num_items)
		idx = imux->num_items - 1;
	अगर (spec->dc_input_bias == idx)
		वापस 0;

	spec->dc_input_bias = idx;
	अगर (spec->dc_enable)
		olpc_xo_update_mic_pins(codec);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new olpc_xo_mixers[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "DC Mode Enable Switch",
		.info = snd_ctl_boolean_mono_info,
		.get = olpc_xo_dc_mode_get,
		.put = olpc_xo_dc_mode_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "DC Input Bias Enum",
		.info = olpc_xo_dc_bias_क्रमागत_info,
		.get = olpc_xo_dc_bias_क्रमागत_get,
		.put = olpc_xo_dc_bias_क्रमागत_put,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

/* overriding mic boost put callback; update mic boost volume only when
 * DC mode is disabled
 */
अटल पूर्णांक olpc_xo_mic_boost_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा conexant_spec *spec = codec->spec;
	पूर्णांक ret = snd_hda_mixer_amp_volume_put(kcontrol, ucontrol);
	अगर (ret > 0 && spec->dc_enable)
		olpc_xo_update_mic_boost(codec);
	वापस ret;
पूर्ण

अटल व्योम cxt_fixup_olpc_xo(काष्ठा hda_codec *codec,
				    स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा conexant_spec *spec = codec->spec;
	काष्ठा snd_kcontrol_new *kctl;
	पूर्णांक i;

	अगर (action != HDA_FIXUP_ACT_PROBE)
		वापस;

	spec->gen.mic_स्वतःचयन_hook = olpc_xo_स्वतःmic;
	spec->gen.pcm_capture_hook = olpc_xo_capture_hook;
	spec->dc_mode_path = snd_hda_add_new_path(codec, 0x1e, 0x14, 0);

	snd_hda_add_new_ctls(codec, olpc_xo_mixers);

	/* OLPC's microphone port is DC coupled क्रम use with बाह्यal sensors,
	 * thereक्रमe we use a 50% mic bias in order to center the input संकेत
	 * with the DC input range of the codec.
	 */
	snd_hda_codec_set_pin_target(codec, 0x1a, PIN_VREF50);

	/* override mic boost control */
	snd_array_क्रम_each(&spec->gen.kctls, i, kctl) अणु
		अगर (!म_भेद(kctl->name, "Mic Boost Volume")) अणु
			kctl->put = olpc_xo_mic_boost_put;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cxt_fixup_mute_led_eapd(काष्ठा hda_codec *codec,
				    स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा conexant_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		spec->mute_led_eapd = 0x1b;
		spec->dynamic_eapd = true;
		snd_hda_gen_add_mute_led_cdev(codec, cx_स्वतः_vmaster_mute_led);
	पूर्ण
पूर्ण

/*
 * Fix max input level on mixer widget to 0dB
 * (originally it has 0x2b steps with 0dB offset 0x14)
 */
अटल व्योम cxt_fixup_cap_mix_amp(काष्ठा hda_codec *codec,
				  स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	snd_hda_override_amp_caps(codec, 0x17, HDA_INPUT,
				  (0x14 << AC_AMPCAP_OFFSET_SHIFT) |
				  (0x14 << AC_AMPCAP_NUM_STEPS_SHIFT) |
				  (0x05 << AC_AMPCAP_STEP_SIZE_SHIFT) |
				  (1 << AC_AMPCAP_MUTE_SHIFT));
पूर्ण

/*
 * Fix max input level on mixer widget to 0dB
 * (originally it has 0x1e steps with 0 dB offset 0x17)
 */
अटल व्योम cxt_fixup_cap_mix_amp_5047(काष्ठा hda_codec *codec,
				  स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	snd_hda_override_amp_caps(codec, 0x10, HDA_INPUT,
				  (0x17 << AC_AMPCAP_OFFSET_SHIFT) |
				  (0x17 << AC_AMPCAP_NUM_STEPS_SHIFT) |
				  (0x05 << AC_AMPCAP_STEP_SIZE_SHIFT) |
				  (1 << AC_AMPCAP_MUTE_SHIFT));
पूर्ण

अटल व्योम cxt_fixup_hp_gate_mic_jack(काष्ठा hda_codec *codec,
				       स्थिर काष्ठा hda_fixup *fix,
				       पूर्णांक action)
अणु
	/* the mic pin (0x19) करोesn't give an unsolicited event;
	 * probe the mic pin together with the headphone pin (0x16)
	 */
	अगर (action == HDA_FIXUP_ACT_PROBE)
		snd_hda_jack_set_gating_jack(codec, 0x19, 0x16);
पूर्ण

/* update LED status via GPIO */
अटल व्योम cxt_update_gpio_led(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक mask,
				bool led_on)
अणु
	काष्ठा conexant_spec *spec = codec->spec;
	अचिन्हित पूर्णांक oldval = spec->gpio_led;

	अगर (spec->mute_led_polarity)
		led_on = !led_on;

	अगर (led_on)
		spec->gpio_led |= mask;
	अन्यथा
		spec->gpio_led &= ~mask;
	codec_dbg(codec, "mask:%d enabled:%d gpio_led:%d\n",
			mask, led_on, spec->gpio_led);
	अगर (spec->gpio_led != oldval)
		snd_hda_codec_ग_लिखो(codec, 0x01, 0, AC_VERB_SET_GPIO_DATA,
				    spec->gpio_led);
पूर्ण

/* turn on/off mute LED via GPIO per vmaster hook */
अटल पूर्णांक cxt_gpio_mute_update(काष्ठा led_classdev *led_cdev,
				क्रमागत led_brightness brightness)
अणु
	काष्ठा hda_codec *codec = dev_to_hda_codec(led_cdev->dev->parent);
	काष्ठा conexant_spec *spec = codec->spec;

	cxt_update_gpio_led(codec, spec->gpio_mute_led_mask, brightness);
	वापस 0;
पूर्ण

/* turn on/off mic-mute LED via GPIO per capture hook */
अटल पूर्णांक cxt_gpio_micmute_update(काष्ठा led_classdev *led_cdev,
				   क्रमागत led_brightness brightness)
अणु
	काष्ठा hda_codec *codec = dev_to_hda_codec(led_cdev->dev->parent);
	काष्ठा conexant_spec *spec = codec->spec;

	cxt_update_gpio_led(codec, spec->gpio_mic_led_mask, brightness);
	वापस 0;
पूर्ण

अटल व्योम cxt_setup_mute_led(काष्ठा hda_codec *codec,
			       अचिन्हित पूर्णांक mute, अचिन्हित पूर्णांक mic_mute)
अणु
	काष्ठा conexant_spec *spec = codec->spec;

	spec->gpio_led = 0;
	spec->mute_led_polarity = 0;
	अगर (mute) अणु
		snd_hda_gen_add_mute_led_cdev(codec, cxt_gpio_mute_update);
		spec->gpio_mute_led_mask = mute;
	पूर्ण
	अगर (mic_mute) अणु
		snd_hda_gen_add_micmute_led_cdev(codec, cxt_gpio_micmute_update);
		spec->gpio_mic_led_mask = mic_mute;
	पूर्ण
पूर्ण

अटल व्योम cxt_fixup_mute_led_gpio(काष्ठा hda_codec *codec,
				स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action == HDA_FIXUP_ACT_PRE_PROBE)
		cxt_setup_mute_led(codec, 0x01, 0x02);
पूर्ण

अटल व्योम cxt_fixup_hp_zbook_mute_led(काष्ठा hda_codec *codec,
					स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action == HDA_FIXUP_ACT_PRE_PROBE)
		cxt_setup_mute_led(codec, 0x10, 0x20);
पूर्ण

/* ThinkPad X200 & co with cxt5051 */
अटल स्थिर काष्ठा hda_pपूर्णांकbl cxt_pincfg_lenovo_x200[] = अणु
	अणु 0x16, 0x042140ff पूर्ण, /* HP (seq# overridden) */
	अणु 0x17, 0x21a11000 पूर्ण, /* करोck-mic */
	अणु 0x19, 0x2121103f पूर्ण, /* करोck-HP */
	अणु 0x1c, 0x21440100 पूर्ण, /* करोck SPDIF out */
	अणुपूर्ण
पूर्ण;

/* ThinkPad 410/420/510/520, X201 & co with cxt5066 */
अटल स्थिर काष्ठा hda_pपूर्णांकbl cxt_pincfg_lenovo_tp410[] = अणु
	अणु 0x19, 0x042110ff पूर्ण, /* HP (seq# overridden) */
	अणु 0x1a, 0x21a190f0 पूर्ण, /* करोck-mic */
	अणु 0x1c, 0x212140ff पूर्ण, /* करोck-HP */
	अणुपूर्ण
पूर्ण;

/* Lemote A1004/A1205 with cxt5066 */
अटल स्थिर काष्ठा hda_pपूर्णांकbl cxt_pincfg_lemote[] = अणु
	अणु 0x1a, 0x90a10020 पूर्ण, /* Internal mic */
	अणु 0x1b, 0x03a11020 पूर्ण, /* External mic */
	अणु 0x1d, 0x400101f0 पूर्ण, /* Not used */
	अणु 0x1e, 0x40a701f0 पूर्ण, /* Not used */
	अणु 0x20, 0x404501f0 पूर्ण, /* Not used */
	अणु 0x22, 0x404401f0 पूर्ण, /* Not used */
	अणु 0x23, 0x40a701f0 पूर्ण, /* Not used */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_fixup cxt_fixups[] = अणु
	[CXT_PINCFG_LENOVO_X200] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = cxt_pincfg_lenovo_x200,
	पूर्ण,
	[CXT_PINCFG_LENOVO_TP410] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = cxt_pincfg_lenovo_tp410,
		.chained = true,
		.chain_id = CXT_FIXUP_THINKPAD_ACPI,
	पूर्ण,
	[CXT_PINCFG_LEMOTE_A1004] = अणु
		.type = HDA_FIXUP_PINS,
		.chained = true,
		.chain_id = CXT_FIXUP_INC_MIC_BOOST,
		.v.pins = cxt_pincfg_lemote,
	पूर्ण,
	[CXT_PINCFG_LEMOTE_A1205] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = cxt_pincfg_lemote,
	पूर्ण,
	[CXT_PINCFG_COMPAQ_CQ60] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			/* 0x17 was falsely set up as a mic, it should 0x1d */
			अणु 0x17, 0x400001f0 पूर्ण,
			अणु 0x1d, 0x97a70120 पूर्ण,
			अणु पूर्ण
		पूर्ण
	पूर्ण,
	[CXT_FIXUP_STEREO_DMIC] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_stereo_dmic,
	पूर्ण,
	[CXT_FIXUP_INC_MIC_BOOST] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt5066_increase_mic_boost,
	पूर्ण,
	[CXT_FIXUP_HEADPHONE_MIC_PIN] = अणु
		.type = HDA_FIXUP_PINS,
		.chained = true,
		.chain_id = CXT_FIXUP_HEADPHONE_MIC,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			अणु 0x18, 0x03a1913d पूर्ण, /* use as headphone mic, without its own jack detect */
			अणु पूर्ण
		पूर्ण
	पूर्ण,
	[CXT_FIXUP_HEADPHONE_MIC] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_headphone_mic,
	पूर्ण,
	[CXT_FIXUP_GPIO1] = अणु
		.type = HDA_FIXUP_VERBS,
		.v.verbs = (स्थिर काष्ठा hda_verb[]) अणु
			अणु 0x01, AC_VERB_SET_GPIO_MASK, 0x01 पूर्ण,
			अणु 0x01, AC_VERB_SET_GPIO_सूचीECTION, 0x01 पूर्ण,
			अणु 0x01, AC_VERB_SET_GPIO_DATA, 0x01 पूर्ण,
			अणु पूर्ण
		पूर्ण,
	पूर्ण,
	[CXT_FIXUP_ASPIRE_DMIC] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_stereo_dmic,
		.chained = true,
		.chain_id = CXT_FIXUP_GPIO1,
	पूर्ण,
	[CXT_FIXUP_THINKPAD_ACPI] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = hda_fixup_thinkpad_acpi,
	पूर्ण,
	[CXT_FIXUP_OLPC_XO] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_olpc_xo,
	पूर्ण,
	[CXT_FIXUP_CAP_MIX_AMP] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_cap_mix_amp,
	पूर्ण,
	[CXT_FIXUP_TOSHIBA_P105] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			अणु 0x10, 0x961701f0 पूर्ण, /* speaker/hp */
			अणु 0x12, 0x02a1901e पूर्ण, /* ext mic */
			अणु 0x14, 0x95a70110 पूर्ण, /* पूर्णांक mic */
			अणुपूर्ण
		पूर्ण,
	पूर्ण,
	[CXT_FIXUP_HP_530] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			अणु 0x12, 0x90a60160 पूर्ण, /* पूर्णांक mic */
			अणुपूर्ण
		पूर्ण,
		.chained = true,
		.chain_id = CXT_FIXUP_CAP_MIX_AMP,
	पूर्ण,
	[CXT_FIXUP_CAP_MIX_AMP_5047] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_cap_mix_amp_5047,
	पूर्ण,
	[CXT_FIXUP_MUTE_LED_EAPD] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_mute_led_eapd,
	पूर्ण,
	[CXT_FIXUP_HP_DOCK] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			अणु 0x16, 0x21011020 पूर्ण, /* line-out */
			अणु 0x18, 0x2181103f पूर्ण, /* line-in */
			अणु पूर्ण
		पूर्ण,
		.chained = true,
		.chain_id = CXT_FIXUP_MUTE_LED_GPIO,
	पूर्ण,
	[CXT_FIXUP_HP_SPECTRE] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			/* enable NID 0x1d क्रम the speaker on top */
			अणु 0x1d, 0x91170111 पूर्ण,
			अणु पूर्ण
		पूर्ण
	पूर्ण,
	[CXT_FIXUP_HP_GATE_MIC] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_hp_gate_mic_jack,
	पूर्ण,
	[CXT_FIXUP_MUTE_LED_GPIO] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_mute_led_gpio,
	पूर्ण,
	[CXT_FIXUP_HP_ZBOOK_MUTE_LED] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_hp_zbook_mute_led,
	पूर्ण,
	[CXT_FIXUP_HEADSET_MIC] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = cxt_fixup_headset_mic,
	पूर्ण,
	[CXT_FIXUP_HP_MIC_NO_PRESENCE] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			अणु 0x1a, 0x02a1113c पूर्ण,
			अणु पूर्ण
		पूर्ण,
		.chained = true,
		.chain_id = CXT_FIXUP_HEADSET_MIC,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk cxt5045_fixups[] = अणु
	SND_PCI_QUIRK(0x103c, 0x30d5, "HP 530", CXT_FIXUP_HP_530),
	SND_PCI_QUIRK(0x1179, 0xff31, "Toshiba P105", CXT_FIXUP_TOSHIBA_P105),
	/* HP, Packard Bell, Fujitsu-Siemens & Lenovo laptops have
	 * really bad sound over 0dB on NID 0x17.
	 */
	SND_PCI_QUIRK_VENDOR(0x103c, "HP", CXT_FIXUP_CAP_MIX_AMP),
	SND_PCI_QUIRK_VENDOR(0x1631, "Packard Bell", CXT_FIXUP_CAP_MIX_AMP),
	SND_PCI_QUIRK_VENDOR(0x1734, "Fujitsu", CXT_FIXUP_CAP_MIX_AMP),
	SND_PCI_QUIRK_VENDOR(0x17aa, "Lenovo", CXT_FIXUP_CAP_MIX_AMP),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_model_fixup cxt5045_fixup_models[] = अणु
	अणु .id = CXT_FIXUP_CAP_MIX_AMP, .name = "cap-mix-amp" पूर्ण,
	अणु .id = CXT_FIXUP_TOSHIBA_P105, .name = "toshiba-p105" पूर्ण,
	अणु .id = CXT_FIXUP_HP_530, .name = "hp-530" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk cxt5047_fixups[] = अणु
	/* HP laptops have really bad sound over 0 dB on NID 0x10.
	 */
	SND_PCI_QUIRK_VENDOR(0x103c, "HP", CXT_FIXUP_CAP_MIX_AMP_5047),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_model_fixup cxt5047_fixup_models[] = अणु
	अणु .id = CXT_FIXUP_CAP_MIX_AMP_5047, .name = "cap-mix-amp" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk cxt5051_fixups[] = अणु
	SND_PCI_QUIRK(0x103c, 0x360b, "Compaq CQ60", CXT_PINCFG_COMPAQ_CQ60),
	SND_PCI_QUIRK(0x17aa, 0x20f2, "Lenovo X200", CXT_PINCFG_LENOVO_X200),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_model_fixup cxt5051_fixup_models[] = अणु
	अणु .id = CXT_PINCFG_LENOVO_X200, .name = "lenovo-x200" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk cxt5066_fixups[] = अणु
	SND_PCI_QUIRK(0x1025, 0x0543, "Acer Aspire One 522", CXT_FIXUP_STEREO_DMIC),
	SND_PCI_QUIRK(0x1025, 0x054c, "Acer Aspire 3830TG", CXT_FIXUP_ASPIRE_DMIC),
	SND_PCI_QUIRK(0x1025, 0x054f, "Acer Aspire 4830T", CXT_FIXUP_ASPIRE_DMIC),
	SND_PCI_QUIRK(0x103c, 0x8079, "HP EliteBook 840 G3", CXT_FIXUP_HP_DOCK),
	SND_PCI_QUIRK(0x103c, 0x807C, "HP EliteBook 820 G3", CXT_FIXUP_HP_DOCK),
	SND_PCI_QUIRK(0x103c, 0x80FD, "HP ProBook 640 G2", CXT_FIXUP_HP_DOCK),
	SND_PCI_QUIRK(0x103c, 0x8115, "HP Z1 Gen3", CXT_FIXUP_HP_GATE_MIC),
	SND_PCI_QUIRK(0x103c, 0x814f, "HP ZBook 15u G3", CXT_FIXUP_MUTE_LED_GPIO),
	SND_PCI_QUIRK(0x103c, 0x8174, "HP Spectre x360", CXT_FIXUP_HP_SPECTRE),
	SND_PCI_QUIRK(0x103c, 0x822e, "HP ProBook 440 G4", CXT_FIXUP_MUTE_LED_GPIO),
	SND_PCI_QUIRK(0x103c, 0x828c, "HP EliteBook 840 G4", CXT_FIXUP_HP_DOCK),
	SND_PCI_QUIRK(0x103c, 0x8299, "HP 800 G3 SFF", CXT_FIXUP_HP_MIC_NO_PRESENCE),
	SND_PCI_QUIRK(0x103c, 0x829a, "HP 800 G3 DM", CXT_FIXUP_HP_MIC_NO_PRESENCE),
	SND_PCI_QUIRK(0x103c, 0x836e, "HP ProBook 455 G5", CXT_FIXUP_MUTE_LED_GPIO),
	SND_PCI_QUIRK(0x103c, 0x837f, "HP ProBook 470 G5", CXT_FIXUP_MUTE_LED_GPIO),
	SND_PCI_QUIRK(0x103c, 0x83b2, "HP EliteBook 840 G5", CXT_FIXUP_HP_DOCK),
	SND_PCI_QUIRK(0x103c, 0x83b3, "HP EliteBook 830 G5", CXT_FIXUP_HP_DOCK),
	SND_PCI_QUIRK(0x103c, 0x83d3, "HP ProBook 640 G4", CXT_FIXUP_HP_DOCK),
	SND_PCI_QUIRK(0x103c, 0x8402, "HP ProBook 645 G4", CXT_FIXUP_MUTE_LED_GPIO),
	SND_PCI_QUIRK(0x103c, 0x8427, "HP ZBook Studio G5", CXT_FIXUP_HP_ZBOOK_MUTE_LED),
	SND_PCI_QUIRK(0x103c, 0x844f, "HP ZBook Studio G5", CXT_FIXUP_HP_ZBOOK_MUTE_LED),
	SND_PCI_QUIRK(0x103c, 0x8455, "HP Z2 G4", CXT_FIXUP_HP_MIC_NO_PRESENCE),
	SND_PCI_QUIRK(0x103c, 0x8456, "HP Z2 G4 SFF", CXT_FIXUP_HP_MIC_NO_PRESENCE),
	SND_PCI_QUIRK(0x103c, 0x8457, "HP Z2 G4 mini", CXT_FIXUP_HP_MIC_NO_PRESENCE),
	SND_PCI_QUIRK(0x103c, 0x8458, "HP Z2 G4 mini premium", CXT_FIXUP_HP_MIC_NO_PRESENCE),
	SND_PCI_QUIRK(0x1043, 0x138d, "Asus", CXT_FIXUP_HEADPHONE_MIC_PIN),
	SND_PCI_QUIRK(0x152d, 0x0833, "OLPC XO-1.5", CXT_FIXUP_OLPC_XO),
	SND_PCI_QUIRK(0x17aa, 0x20f2, "Lenovo T400", CXT_PINCFG_LENOVO_TP410),
	SND_PCI_QUIRK(0x17aa, 0x215e, "Lenovo T410", CXT_PINCFG_LENOVO_TP410),
	SND_PCI_QUIRK(0x17aa, 0x215f, "Lenovo T510", CXT_PINCFG_LENOVO_TP410),
	SND_PCI_QUIRK(0x17aa, 0x21ce, "Lenovo T420", CXT_PINCFG_LENOVO_TP410),
	SND_PCI_QUIRK(0x17aa, 0x21cf, "Lenovo T520", CXT_PINCFG_LENOVO_TP410),
	SND_PCI_QUIRK(0x17aa, 0x21d2, "Lenovo T420s", CXT_PINCFG_LENOVO_TP410),
	SND_PCI_QUIRK(0x17aa, 0x21da, "Lenovo X220", CXT_PINCFG_LENOVO_TP410),
	SND_PCI_QUIRK(0x17aa, 0x21db, "Lenovo X220-tablet", CXT_PINCFG_LENOVO_TP410),
	SND_PCI_QUIRK(0x17aa, 0x38af, "Lenovo IdeaPad Z560", CXT_FIXUP_MUTE_LED_EAPD),
	SND_PCI_QUIRK(0x17aa, 0x3905, "Lenovo G50-30", CXT_FIXUP_STEREO_DMIC),
	SND_PCI_QUIRK(0x17aa, 0x390b, "Lenovo G50-80", CXT_FIXUP_STEREO_DMIC),
	SND_PCI_QUIRK(0x17aa, 0x3975, "Lenovo U300s", CXT_FIXUP_STEREO_DMIC),
	SND_PCI_QUIRK(0x17aa, 0x3977, "Lenovo IdeaPad U310", CXT_FIXUP_STEREO_DMIC),
	SND_PCI_QUIRK(0x17aa, 0x3978, "Lenovo G50-70", CXT_FIXUP_STEREO_DMIC),
	SND_PCI_QUIRK(0x17aa, 0x397b, "Lenovo S205", CXT_FIXUP_STEREO_DMIC),
	SND_PCI_QUIRK_VENDOR(0x17aa, "Thinkpad", CXT_FIXUP_THINKPAD_ACPI),
	SND_PCI_QUIRK(0x1c06, 0x2011, "Lemote A1004", CXT_PINCFG_LEMOTE_A1004),
	SND_PCI_QUIRK(0x1c06, 0x2012, "Lemote A1205", CXT_PINCFG_LEMOTE_A1205),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_model_fixup cxt5066_fixup_models[] = अणु
	अणु .id = CXT_FIXUP_STEREO_DMIC, .name = "stereo-dmic" पूर्ण,
	अणु .id = CXT_FIXUP_GPIO1, .name = "gpio1" पूर्ण,
	अणु .id = CXT_FIXUP_HEADPHONE_MIC_PIN, .name = "headphone-mic-pin" पूर्ण,
	अणु .id = CXT_PINCFG_LENOVO_TP410, .name = "tp410" पूर्ण,
	अणु .id = CXT_FIXUP_THINKPAD_ACPI, .name = "thinkpad" पूर्ण,
	अणु .id = CXT_PINCFG_LEMOTE_A1004, .name = "lemote-a1004" पूर्ण,
	अणु .id = CXT_PINCFG_LEMOTE_A1205, .name = "lemote-a1205" पूर्ण,
	अणु .id = CXT_FIXUP_OLPC_XO, .name = "olpc-xo" पूर्ण,
	अणु .id = CXT_FIXUP_MUTE_LED_EAPD, .name = "mute-led-eapd" पूर्ण,
	अणु .id = CXT_FIXUP_HP_DOCK, .name = "hp-dock" पूर्ण,
	अणु .id = CXT_FIXUP_MUTE_LED_GPIO, .name = "mute-led-gpio" पूर्ण,
	अणु .id = CXT_FIXUP_HP_ZBOOK_MUTE_LED, .name = "hp-zbook-mute-led" पूर्ण,
	अणु .id = CXT_FIXUP_HP_MIC_NO_PRESENCE, .name = "hp-mic-fix" पूर्ण,
	अणुपूर्ण
पूर्ण;

/* add "fake" mute amp-caps to DACs on cx5051 so that mixer mute चयनes
 * can be created (bko#42825)
 */
अटल व्योम add_cx5051_fake_mutes(काष्ठा hda_codec *codec)
अणु
	काष्ठा conexant_spec *spec = codec->spec;
	अटल स्थिर hda_nid_t out_nids[] = अणु
		0x10, 0x11, 0
	पूर्ण;
	स्थिर hda_nid_t *p;

	क्रम (p = out_nids; *p; p++)
		snd_hda_override_amp_caps(codec, *p, HDA_OUTPUT,
					  AC_AMPCAP_MIN_MUTE |
					  query_amp_caps(codec, *p, HDA_OUTPUT));
	spec->gen.dac_min_mute = true;
पूर्ण

अटल पूर्णांक patch_conexant_स्वतः(काष्ठा hda_codec *codec)
अणु
	काष्ठा conexant_spec *spec;
	पूर्णांक err;

	codec_info(codec, "%s: BIOS auto-probing.\n", codec->core.chip_name);

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	snd_hda_gen_spec_init(&spec->gen);
	codec->spec = spec;
	codec->patch_ops = cx_स्वतः_patch_ops;

	cx_स्वतः_parse_eapd(codec);
	spec->gen.own_eapd_ctl = 1;

	चयन (codec->core.venकरोr_id) अणु
	हाल 0x14f15045:
		codec->single_adc_amp = 1;
		spec->gen.mixer_nid = 0x17;
		spec->gen.add_stereo_mix_input = HDA_HINT_STEREO_MIX_AUTO;
		snd_hda_pick_fixup(codec, cxt5045_fixup_models,
				   cxt5045_fixups, cxt_fixups);
		अवरोध;
	हाल 0x14f15047:
		codec->pin_amp_workaround = 1;
		spec->gen.mixer_nid = 0x19;
		spec->gen.add_stereo_mix_input = HDA_HINT_STEREO_MIX_AUTO;
		snd_hda_pick_fixup(codec, cxt5047_fixup_models,
				   cxt5047_fixups, cxt_fixups);
		अवरोध;
	हाल 0x14f15051:
		add_cx5051_fake_mutes(codec);
		codec->pin_amp_workaround = 1;
		snd_hda_pick_fixup(codec, cxt5051_fixup_models,
				   cxt5051_fixups, cxt_fixups);
		अवरोध;
	हाल 0x14f150f2:
		codec->घातer_save_node = 1;
		fallthrough;
	शेष:
		codec->pin_amp_workaround = 1;
		snd_hda_pick_fixup(codec, cxt5066_fixup_models,
				   cxt5066_fixups, cxt_fixups);
		अवरोध;
	पूर्ण

	अगर (!spec->gen.vmaster_mute.hook && spec->dynamic_eapd)
		spec->gen.vmaster_mute.hook = cx_स्वतः_vmaster_hook;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	err = snd_hda_parse_pin_defcfg(codec, &spec->gen.स्वतःcfg, शून्य,
				       spec->parse_flags);
	अगर (err < 0)
		जाओ error;

	err = snd_hda_gen_parse_स्वतः_config(codec, &spec->gen.स्वतःcfg);
	अगर (err < 0)
		जाओ error;

	err = cx_स्वतः_parse_beep(codec);
	अगर (err < 0)
		जाओ error;

	/* Some laptops with Conexant chips show stalls in S3 resume,
	 * which falls पूर्णांकo the single-cmd mode.
	 * Better to make reset, then.
	 */
	अगर (!codec->bus->core.sync_ग_लिखो) अणु
		codec_info(codec,
			   "Enable sync_write for stable communication\n");
		codec->bus->core.sync_ग_लिखो = 1;
		codec->bus->allow_bus_reset = 1;
	पूर्ण

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;

 error:
	cx_स्वतः_मुक्त(codec);
	वापस err;
पूर्ण

/*
 */

अटल स्थिर काष्ठा hda_device_id snd_hda_id_conexant[] = अणु
	HDA_CODEC_ENTRY(0x14f11f86, "CX8070", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f12008, "CX8200", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f120d0, "CX11970", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f15045, "CX20549 (Venice)", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f15047, "CX20551 (Waikiki)", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f15051, "CX20561 (Hermosa)", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f15066, "CX20582 (Pebble)", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f15067, "CX20583 (Pebble HSF)", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f15068, "CX20584", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f15069, "CX20585", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f1506c, "CX20588", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f1506e, "CX20590", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f15097, "CX20631", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f15098, "CX20632", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f150a1, "CX20641", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f150a2, "CX20642", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f150ab, "CX20651", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f150ac, "CX20652", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f150b8, "CX20664", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f150b9, "CX20665", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f150f1, "CX21722", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f150f2, "CX20722", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f150f3, "CX21724", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f150f4, "CX20724", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f1510f, "CX20751/2", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f15110, "CX20751/2", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f15111, "CX20753/4", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f15113, "CX20755", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f15114, "CX20756", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f15115, "CX20757", patch_conexant_स्वतः),
	HDA_CODEC_ENTRY(0x14f151d7, "CX20952", patch_conexant_स्वतः),
	अणुपूर्ण /* terminator */
पूर्ण;
MODULE_DEVICE_TABLE(hdaudio, snd_hda_id_conexant);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Conexant HD-audio codec");

अटल काष्ठा hda_codec_driver conexant_driver = अणु
	.id = snd_hda_id_conexant,
पूर्ण;

module_hda_codec_driver(conexant_driver);
