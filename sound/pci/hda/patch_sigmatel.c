<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Universal Interface क्रम Intel High Definition Audio Codec
 *
 * HD audio पूर्णांकerface patch क्रम SigmaTel STAC92xx
 *
 * Copyright (c) 2005 Embedded Alley Solutions, Inc.
 * Matt Porter <mporter@embeddedalley.com>
 *
 * Based on patch_cmedia.c and patch_realtek.c
 * Copyright (c) 2004 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/dmi.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/hda_codec.h>
#समावेश "hda_local.h"
#समावेश "hda_auto_parser.h"
#समावेश "hda_beep.h"
#समावेश "hda_jack.h"
#समावेश "hda_generic.h"

क्रमागत अणु
	STAC_REF,
	STAC_9200_OQO,
	STAC_9200_DELL_D21,
	STAC_9200_DELL_D22,
	STAC_9200_DELL_D23,
	STAC_9200_DELL_M21,
	STAC_9200_DELL_M22,
	STAC_9200_DELL_M23,
	STAC_9200_DELL_M24,
	STAC_9200_DELL_M25,
	STAC_9200_DELL_M26,
	STAC_9200_DELL_M27,
	STAC_9200_M4,
	STAC_9200_M4_2,
	STAC_9200_PANASONIC,
	STAC_9200_EAPD_INIT,
	STAC_9200_MODELS
पूर्ण;

क्रमागत अणु
	STAC_9205_REF,
	STAC_9205_DELL_M42,
	STAC_9205_DELL_M43,
	STAC_9205_DELL_M44,
	STAC_9205_EAPD,
	STAC_9205_MODELS
पूर्ण;

क्रमागत अणु
	STAC_92HD73XX_NO_JD, /* no jack-detection */
	STAC_92HD73XX_REF,
	STAC_92HD73XX_INTEL,
	STAC_DELL_M6_AMIC,
	STAC_DELL_M6_DMIC,
	STAC_DELL_M6_BOTH,
	STAC_DELL_EQ,
	STAC_ALIENWARE_M17X,
	STAC_ELO_VUPOINT_15MX,
	STAC_92HD89XX_HP_FRONT_JACK,
	STAC_92HD89XX_HP_Z1_G2_RIGHT_MIC_JACK,
	STAC_92HD73XX_ASUS_MOBO,
	STAC_92HD73XX_MODELS
पूर्ण;

क्रमागत अणु
	STAC_92HD83XXX_REF,
	STAC_92HD83XXX_PWR_REF,
	STAC_DELL_S14,
	STAC_DELL_VOSTRO_3500,
	STAC_92HD83XXX_HP_cNB11_INTQUAD,
	STAC_HP_DV7_4000,
	STAC_HP_ZEPHYR,
	STAC_92HD83XXX_HP_LED,
	STAC_92HD83XXX_HP_INV_LED,
	STAC_92HD83XXX_HP_MIC_LED,
	STAC_HP_LED_GPIO10,
	STAC_92HD83XXX_HEADSET_JACK,
	STAC_92HD83XXX_HP,
	STAC_HP_ENVY_BASS,
	STAC_HP_BNB13_EQ,
	STAC_HP_ENVY_TS_BASS,
	STAC_HP_ENVY_TS_DAC_BIND,
	STAC_92HD83XXX_GPIO10_EAPD,
	STAC_92HD83XXX_MODELS
पूर्ण;

क्रमागत अणु
	STAC_92HD71BXX_REF,
	STAC_DELL_M4_1,
	STAC_DELL_M4_2,
	STAC_DELL_M4_3,
	STAC_HP_M4,
	STAC_HP_DV4,
	STAC_HP_DV5,
	STAC_HP_HDX,
	STAC_92HD71BXX_HP,
	STAC_92HD71BXX_NO_DMIC,
	STAC_92HD71BXX_NO_SMUX,
	STAC_92HD71BXX_MODELS
पूर्ण;

क्रमागत अणु
	STAC_92HD95_HP_LED,
	STAC_92HD95_HP_BASS,
	STAC_92HD95_MODELS
पूर्ण;

क्रमागत अणु
	STAC_925x_REF,
	STAC_M1,
	STAC_M1_2,
	STAC_M2,
	STAC_M2_2,
	STAC_M3,
	STAC_M5,
	STAC_M6,
	STAC_925x_MODELS
पूर्ण;

क्रमागत अणु
	STAC_D945_REF,
	STAC_D945GTP3,
	STAC_D945GTP5,
	STAC_INTEL_MAC_V1,
	STAC_INTEL_MAC_V2,
	STAC_INTEL_MAC_V3,
	STAC_INTEL_MAC_V4,
	STAC_INTEL_MAC_V5,
	STAC_INTEL_MAC_AUTO,
	STAC_ECS_202,
	STAC_922X_DELL_D81,
	STAC_922X_DELL_D82,
	STAC_922X_DELL_M81,
	STAC_922X_DELL_M82,
	STAC_922X_INTEL_MAC_GPIO,
	STAC_922X_MODELS
पूर्ण;

क्रमागत अणु
	STAC_D965_REF_NO_JD, /* no jack-detection */
	STAC_D965_REF,
	STAC_D965_3ST,
	STAC_D965_5ST,
	STAC_D965_5ST_NO_FP,
	STAC_D965_VERBS,
	STAC_DELL_3ST,
	STAC_DELL_BIOS,
	STAC_NEMO_DEFAULT,
	STAC_DELL_BIOS_AMIC,
	STAC_DELL_BIOS_SPDIF,
	STAC_927X_DELL_DMIC,
	STAC_927X_VOLKNOB,
	STAC_927X_MODELS
पूर्ण;

क्रमागत अणु
	STAC_9872_VAIO,
	STAC_9872_MODELS
पूर्ण;

काष्ठा sigmatel_spec अणु
	काष्ठा hda_gen_spec gen;

	अचिन्हित पूर्णांक eapd_चयन: 1;
	अचिन्हित पूर्णांक linear_tone_beep:1;
	अचिन्हित पूर्णांक headset_jack:1; /* 4-pin headset jack (hp + mono mic) */
	अचिन्हित पूर्णांक volknob_init:1; /* special volume-knob initialization */
	अचिन्हित पूर्णांक घातerकरोwn_adcs:1;
	अचिन्हित पूर्णांक have_spdअगर_mux:1;

	/* gpio lines */
	अचिन्हित पूर्णांक eapd_mask;
	अचिन्हित पूर्णांक gpio_mask;
	अचिन्हित पूर्णांक gpio_dir;
	अचिन्हित पूर्णांक gpio_data;
	अचिन्हित पूर्णांक gpio_mute;
	अचिन्हित पूर्णांक gpio_led;
	अचिन्हित पूर्णांक gpio_led_polarity;
	अचिन्हित पूर्णांक vref_mute_led_nid; /* pin NID क्रम mute-LED vref control */
	अचिन्हित पूर्णांक vref_led;
	पूर्णांक शेष_polarity;

	अचिन्हित पूर्णांक mic_mute_led_gpio; /* capture mute LED GPIO */
	अचिन्हित पूर्णांक mic_enabled; /* current mic mute state (biपंचांगask) */

	/* stream */
	अचिन्हित पूर्णांक stream_delay;

	/* analog loopback */
	स्थिर काष्ठा snd_kcontrol_new *aloopback_ctl;
	अचिन्हित पूर्णांक aloopback;
	अचिन्हित अक्षर aloopback_mask;
	अचिन्हित अक्षर aloopback_shअगरt;

	/* घातer management */
	अचिन्हित पूर्णांक घातer_map_bits;
	अचिन्हित पूर्णांक num_pwrs;
	स्थिर hda_nid_t *pwr_nids;
	अचिन्हित पूर्णांक active_adcs;

	/* beep widमाला_लो */
	hda_nid_t anabeep_nid;

	/* SPDIF-out mux */
	स्थिर अक्षर * स्थिर *spdअगर_labels;
	काष्ठा hda_input_mux spdअगर_mux;
	अचिन्हित पूर्णांक cur_smux[2];
पूर्ण;

#घोषणा AC_VERB_IDT_SET_POWER_MAP	0x7ec
#घोषणा AC_VERB_IDT_GET_POWER_MAP	0xfec

अटल स्थिर hda_nid_t stac92hd73xx_pwr_nids[8] = अणु
	0x0a, 0x0b, 0x0c, 0xd, 0x0e,
	0x0f, 0x10, 0x11
पूर्ण;

अटल स्थिर hda_nid_t stac92hd83xxx_pwr_nids[7] = अणु
	0x0a, 0x0b, 0x0c, 0xd, 0x0e,
	0x0f, 0x10
पूर्ण;

अटल स्थिर hda_nid_t stac92hd71bxx_pwr_nids[3] = अणु
	0x0a, 0x0d, 0x0f
पूर्ण;


/*
 * PCM hooks
 */
अटल व्योम stac_playback_pcm_hook(काष्ठा hda_pcm_stream *hinfo,
				   काष्ठा hda_codec *codec,
				   काष्ठा snd_pcm_substream *substream,
				   पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;
	अगर (action == HDA_GEN_PCM_ACT_OPEN && spec->stream_delay)
		msleep(spec->stream_delay);
पूर्ण

अटल व्योम stac_capture_pcm_hook(काष्ठा hda_pcm_stream *hinfo,
				  काष्ठा hda_codec *codec,
				  काष्ठा snd_pcm_substream *substream,
				  पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;
	पूर्णांक i, idx = 0;

	अगर (!spec->घातerकरोwn_adcs)
		वापस;

	क्रम (i = 0; i < spec->gen.num_all_adcs; i++) अणु
		अगर (spec->gen.all_adcs[i] == hinfo->nid) अणु
			idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (action) अणु
	हाल HDA_GEN_PCM_ACT_OPEN:
		msleep(40);
		snd_hda_codec_ग_लिखो(codec, hinfo->nid, 0,
				    AC_VERB_SET_POWER_STATE, AC_PWRST_D0);
		spec->active_adcs |= (1 << idx);
		अवरोध;
	हाल HDA_GEN_PCM_ACT_CLOSE:
		snd_hda_codec_ग_लिखो(codec, hinfo->nid, 0,
				    AC_VERB_SET_POWER_STATE, AC_PWRST_D3);
		spec->active_adcs &= ~(1 << idx);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Early 2006 Intel Macपूर्णांकoshes with STAC9220X5 codecs seem to have a
 * funky बाह्यal mute control using GPIO pins.
 */

अटल व्योम stac_gpio_set(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक mask,
			  अचिन्हित पूर्णांक dir_mask, अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक gpiostate, gpiomask, gpiodir;
	hda_nid_t fg = codec->core.afg;

	codec_dbg(codec, "%s msk %x dir %x gpio %x\n", __func__, mask, dir_mask, data);

	gpiostate = snd_hda_codec_पढ़ो(codec, fg, 0,
				       AC_VERB_GET_GPIO_DATA, 0);
	gpiostate = (gpiostate & ~dir_mask) | (data & dir_mask);

	gpiomask = snd_hda_codec_पढ़ो(codec, fg, 0,
				      AC_VERB_GET_GPIO_MASK, 0);
	gpiomask |= mask;

	gpiodir = snd_hda_codec_पढ़ो(codec, fg, 0,
				     AC_VERB_GET_GPIO_सूचीECTION, 0);
	gpiodir |= dir_mask;

	/* Configure GPIOx as CMOS */
	snd_hda_codec_ग_लिखो(codec, fg, 0, 0x7e7, 0);

	snd_hda_codec_ग_लिखो(codec, fg, 0,
			    AC_VERB_SET_GPIO_MASK, gpiomask);
	snd_hda_codec_पढ़ो(codec, fg, 0,
			   AC_VERB_SET_GPIO_सूचीECTION, gpiodir); /* sync */

	msleep(1);

	snd_hda_codec_पढ़ो(codec, fg, 0,
			   AC_VERB_SET_GPIO_DATA, gpiostate); /* sync */
पूर्ण

/* hook क्रम controlling mic-mute LED GPIO */
अटल पूर्णांक stac_capture_led_update(काष्ठा led_classdev *led_cdev,
				   क्रमागत led_brightness brightness)
अणु
	काष्ठा hda_codec *codec = dev_to_hda_codec(led_cdev->dev->parent);
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (brightness)
		spec->gpio_data |= spec->mic_mute_led_gpio;
	अन्यथा
		spec->gpio_data &= ~spec->mic_mute_led_gpio;
	stac_gpio_set(codec, spec->gpio_mask, spec->gpio_dir, spec->gpio_data);
	वापस 0;
पूर्ण

अटल पूर्णांक stac_vrefout_set(काष्ठा hda_codec *codec,
					hda_nid_t nid, अचिन्हित पूर्णांक new_vref)
अणु
	पूर्णांक error, pinctl;

	codec_dbg(codec, "%s, nid %x ctl %x\n", __func__, nid, new_vref);
	pinctl = snd_hda_codec_पढ़ो(codec, nid, 0,
				AC_VERB_GET_PIN_WIDGET_CONTROL, 0);

	अगर (pinctl < 0)
		वापस pinctl;

	pinctl &= 0xff;
	pinctl &= ~AC_PINCTL_VREFEN;
	pinctl |= (new_vref & AC_PINCTL_VREFEN);

	error = snd_hda_set_pin_ctl_cache(codec, nid, pinctl);
	अगर (error < 0)
		वापस error;

	वापस 1;
पूर्ण

/* prevent codec AFG to D3 state when vref-out pin is used क्रम mute LED */
/* this hook is set in stac_setup_gpio() */
अटल अचिन्हित पूर्णांक stac_vref_led_घातer_filter(काष्ठा hda_codec *codec,
					       hda_nid_t nid,
					       अचिन्हित पूर्णांक घातer_state)
अणु
	अगर (nid == codec->core.afg && घातer_state == AC_PWRST_D3)
		वापस AC_PWRST_D1;
	वापस snd_hda_gen_path_घातer_filter(codec, nid, घातer_state);
पूर्ण

/* update mute-LED accoring to the master चयन */
अटल व्योम stac_update_led_status(काष्ठा hda_codec *codec, bool muted)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (!spec->gpio_led)
		वापस;

	/* LED state is inverted on these प्रणालीs */
	अगर (spec->gpio_led_polarity)
		muted = !muted;

	अगर (!spec->vref_mute_led_nid) अणु
		अगर (muted)
			spec->gpio_data |= spec->gpio_led;
		अन्यथा
			spec->gpio_data &= ~spec->gpio_led;
		stac_gpio_set(codec, spec->gpio_mask,
				spec->gpio_dir, spec->gpio_data);
	पूर्ण अन्यथा अणु
		spec->vref_led = muted ? AC_PINCTL_VREF_50 : AC_PINCTL_VREF_GRD;
		stac_vrefout_set(codec,	spec->vref_mute_led_nid,
				 spec->vref_led);
	पूर्ण
पूर्ण

/* vmaster hook to update mute LED */
अटल पूर्णांक stac_vmaster_hook(काष्ठा led_classdev *led_cdev,
			     क्रमागत led_brightness brightness)
अणु
	काष्ठा hda_codec *codec = dev_to_hda_codec(led_cdev->dev->parent);

	stac_update_led_status(codec, brightness);
	वापस 0;
पूर्ण

/* स्वतःmute hook to handle GPIO mute and EAPD updates */
अटल व्योम stac_update_outमाला_दो(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (spec->gpio_mute)
		spec->gen.master_mute =
			!(snd_hda_codec_पढ़ो(codec, codec->core.afg, 0,
				AC_VERB_GET_GPIO_DATA, 0) & spec->gpio_mute);

	snd_hda_gen_update_outमाला_दो(codec);

	अगर (spec->eapd_mask && spec->eapd_चयन) अणु
		अचिन्हित पूर्णांक val = spec->gpio_data;
		अगर (spec->gen.speaker_muted)
			val &= ~spec->eapd_mask;
		अन्यथा
			val |= spec->eapd_mask;
		अगर (spec->gpio_data != val) अणु
			spec->gpio_data = val;
			stac_gpio_set(codec, spec->gpio_mask, spec->gpio_dir,
				      val);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम stac_toggle_घातer_map(काष्ठा hda_codec *codec, hda_nid_t nid,
				  bool enable, bool करो_ग_लिखो)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;
	अचिन्हित पूर्णांक idx, val;

	क्रम (idx = 0; idx < spec->num_pwrs; idx++) अणु
		अगर (spec->pwr_nids[idx] == nid)
			अवरोध;
	पूर्ण
	अगर (idx >= spec->num_pwrs)
		वापस;

	idx = 1 << idx;

	val = spec->घातer_map_bits;
	अगर (enable)
		val &= ~idx;
	अन्यथा
		val |= idx;

	/* घातer करोwn unused output ports */
	अगर (val != spec->घातer_map_bits) अणु
		spec->घातer_map_bits = val;
		अगर (करो_ग_लिखो)
			snd_hda_codec_ग_लिखो(codec, codec->core.afg, 0,
					    AC_VERB_IDT_SET_POWER_MAP, val);
	पूर्ण
पूर्ण

/* update घातer bit per jack plug/unplug */
अटल व्योम jack_update_घातer(काष्ठा hda_codec *codec,
			      काष्ठा hda_jack_callback *jack)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;
	पूर्णांक i;

	अगर (!spec->num_pwrs)
		वापस;

	अगर (jack && jack->nid) अणु
		stac_toggle_घातer_map(codec, jack->nid,
				      snd_hda_jack_detect(codec, jack->nid),
				      true);
		वापस;
	पूर्ण

	/* update all jacks */
	क्रम (i = 0; i < spec->num_pwrs; i++) अणु
		hda_nid_t nid = spec->pwr_nids[i];
		अगर (!snd_hda_jack_tbl_get(codec, nid))
			जारी;
		stac_toggle_घातer_map(codec, nid,
				      snd_hda_jack_detect(codec, nid),
				      false);
	पूर्ण

	snd_hda_codec_ग_लिखो(codec, codec->core.afg, 0,
			    AC_VERB_IDT_SET_POWER_MAP,
			    spec->घातer_map_bits);
पूर्ण

अटल व्योम stac_vref_event(काष्ठा hda_codec *codec,
			    काष्ठा hda_jack_callback *event)
अणु
	अचिन्हित पूर्णांक data;

	data = snd_hda_codec_पढ़ो(codec, codec->core.afg, 0,
				  AC_VERB_GET_GPIO_DATA, 0);
	/* toggle VREF state based on GPIOx status */
	snd_hda_codec_ग_लिखो(codec, codec->core.afg, 0, 0x7e0,
			    !!(data & (1 << event->निजी_data)));
पूर्ण

/* initialize the घातer map and enable the घातer event to jacks that
 * haven't been asचिन्हित to स्वतःmute
 */
अटल व्योम stac_init_घातer_map(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;
	पूर्णांक i;

	क्रम (i = 0; i < spec->num_pwrs; i++)  अणु
		hda_nid_t nid = spec->pwr_nids[i];
		अचिन्हित पूर्णांक def_conf = snd_hda_codec_get_pincfg(codec, nid);
		def_conf = get_defcfg_connect(def_conf);
		अगर (def_conf == AC_JACK_PORT_COMPLEX &&
		    spec->vref_mute_led_nid != nid &&
		    is_jack_detectable(codec, nid)) अणु
			snd_hda_jack_detect_enable_callback(codec, nid,
							    jack_update_घातer);
		पूर्ण अन्यथा अणु
			अगर (def_conf == AC_JACK_PORT_NONE)
				stac_toggle_घातer_map(codec, nid, false, false);
			अन्यथा
				stac_toggle_घातer_map(codec, nid, true, false);
		पूर्ण
	पूर्ण
पूर्ण

/*
 */

अटल अंतरभूत bool get_पूर्णांक_hपूर्णांक(काष्ठा hda_codec *codec, स्थिर अक्षर *key,
				पूर्णांक *valp)
अणु
	वापस !snd_hda_get_पूर्णांक_hपूर्णांक(codec, key, valp);
पूर्ण

/* override some hपूर्णांकs from the hwdep entry */
अटल व्योम stac_store_hपूर्णांकs(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;
	पूर्णांक val;

	अगर (get_पूर्णांक_hपूर्णांक(codec, "gpio_mask", &spec->gpio_mask)) अणु
		spec->eapd_mask = spec->gpio_dir = spec->gpio_data =
			spec->gpio_mask;
	पूर्ण
	अगर (get_पूर्णांक_hपूर्णांक(codec, "gpio_dir", &spec->gpio_dir))
		spec->gpio_dir &= spec->gpio_mask;
	अगर (get_पूर्णांक_hपूर्णांक(codec, "gpio_data", &spec->gpio_data))
		spec->gpio_data &= spec->gpio_mask;
	अगर (get_पूर्णांक_hपूर्णांक(codec, "eapd_mask", &spec->eapd_mask))
		spec->eapd_mask &= spec->gpio_mask;
	अगर (get_पूर्णांक_hपूर्णांक(codec, "gpio_mute", &spec->gpio_mute))
		spec->gpio_mute &= spec->gpio_mask;
	val = snd_hda_get_bool_hपूर्णांक(codec, "eapd_switch");
	अगर (val >= 0)
		spec->eapd_चयन = val;
पूर्ण

/*
 * loopback controls
 */

#घोषणा stac_aloopback_info snd_ctl_boolean_mono_info

अटल पूर्णांक stac_aloopback_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	काष्ठा sigmatel_spec *spec = codec->spec;

	ucontrol->value.पूर्णांकeger.value[0] = !!(spec->aloopback &
					      (spec->aloopback_mask << idx));
	वापस 0;
पूर्ण

अटल पूर्णांक stac_aloopback_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा sigmatel_spec *spec = codec->spec;
	अचिन्हित पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	अचिन्हित पूर्णांक dac_mode;
	अचिन्हित पूर्णांक val, idx_val;

	idx_val = spec->aloopback_mask << idx;
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		val = spec->aloopback | idx_val;
	अन्यथा
		val = spec->aloopback & ~idx_val;
	अगर (spec->aloopback == val)
		वापस 0;

	spec->aloopback = val;

	/* Only वापस the bits defined by the shअगरt value of the
	 * first two bytes of the mask
	 */
	dac_mode = snd_hda_codec_पढ़ो(codec, codec->core.afg, 0,
				      kcontrol->निजी_value & 0xFFFF, 0x0);
	dac_mode >>= spec->aloopback_shअगरt;

	अगर (spec->aloopback & idx_val) अणु
		snd_hda_घातer_up(codec);
		dac_mode |= idx_val;
	पूर्ण अन्यथा अणु
		snd_hda_घातer_करोwn(codec);
		dac_mode &= ~idx_val;
	पूर्ण

	snd_hda_codec_ग_लिखो_cache(codec, codec->core.afg, 0,
		kcontrol->निजी_value >> 16, dac_mode);

	वापस 1;
पूर्ण

#घोषणा STAC_ANALOG_LOOPBACK(verb_पढ़ो, verb_ग_लिखो, cnt) \
	अणु \
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
		.name  = "Analog Loopback", \
		.count = cnt, \
		.info  = stac_aloopback_info, \
		.get   = stac_aloopback_get, \
		.put   = stac_aloopback_put, \
		.निजी_value = verb_पढ़ो | (verb_ग_लिखो << 16), \
	पूर्ण

/*
 * Mute LED handling on HP laptops
 */

/* check whether it's a HP laptop with a करोcking port */
अटल bool hp_bnb2011_with_करोck(काष्ठा hda_codec *codec)
अणु
	अगर (codec->core.venकरोr_id != 0x111d7605 &&
	    codec->core.venकरोr_id != 0x111d76d1)
		वापस false;

	चयन (codec->core.subप्रणाली_id) अणु
	हाल 0x103c1618:
	हाल 0x103c1619:
	हाल 0x103c161a:
	हाल 0x103c161b:
	हाल 0x103c161c:
	हाल 0x103c161d:
	हाल 0x103c161e:
	हाल 0x103c161f:

	हाल 0x103c162a:
	हाल 0x103c162b:

	हाल 0x103c1630:
	हाल 0x103c1631:

	हाल 0x103c1633:
	हाल 0x103c1634:
	हाल 0x103c1635:

	हाल 0x103c3587:
	हाल 0x103c3588:
	हाल 0x103c3589:
	हाल 0x103c358a:

	हाल 0x103c3667:
	हाल 0x103c3668:
	हाल 0x103c3669:

		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool hp_blike_प्रणाली(u32 subप्रणाली_id)
अणु
	चयन (subप्रणाली_id) अणु
	हाल 0x103c1473: /* HP ProBook 6550b */
	हाल 0x103c1520:
	हाल 0x103c1521:
	हाल 0x103c1523:
	हाल 0x103c1524:
	हाल 0x103c1525:
	हाल 0x103c1722:
	हाल 0x103c1723:
	हाल 0x103c1724:
	हाल 0x103c1725:
	हाल 0x103c1726:
	हाल 0x103c1727:
	हाल 0x103c1728:
	हाल 0x103c1729:
	हाल 0x103c172a:
	हाल 0x103c172b:
	हाल 0x103c307e:
	हाल 0x103c307f:
	हाल 0x103c3080:
	हाल 0x103c3081:
	हाल 0x103c7007:
	हाल 0x103c7008:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम set_hp_led_gpio(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;
	अचिन्हित पूर्णांक gpio;

	अगर (spec->gpio_led)
		वापस;

	gpio = snd_hda_param_पढ़ो(codec, codec->core.afg, AC_PAR_GPIO_CAP);
	gpio &= AC_GPIO_IO_COUNT;
	अगर (gpio > 3)
		spec->gpio_led = 0x08; /* GPIO 3 */
	अन्यथा
		spec->gpio_led = 0x01; /* GPIO 0 */
पूर्ण

/*
 * This method searches क्रम the mute LED GPIO configuration
 * provided as OEM string in SMBIOS. The क्रमmat of that string
 * is HP_Mute_LED_P_G or HP_Mute_LED_P
 * where P can be 0 or 1 and defines mute LED GPIO control state (low/high)
 * that corresponds to the NOT muted state of the master volume
 * and G is the index of the GPIO to use as the mute LED control (0..9)
 * If _G portion is missing it is asचिन्हित based on the codec ID
 *
 * So, HP B-series like प्रणालीs may have HP_Mute_LED_0 (current models)
 * or  HP_Mute_LED_0_3 (future models) OEM SMBIOS strings
 *
 *
 * The dv-series laptops करोn't seem to have the HP_Mute_LED* strings in
 * SMBIOS - at least the ones I have seen करो not have them - which include
 * my own प्रणाली (HP Pavilion dv6-1110ax) and my cousin's
 * HP Pavilion dv9500t CTO.
 * Need more inक्रमmation on whether it is true across the entire series.
 * -- kunal
 */
अटल पूर्णांक find_mute_led_cfg(काष्ठा hda_codec *codec, पूर्णांक शेष_polarity)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;
	स्थिर काष्ठा dmi_device *dev = शून्य;

	अगर (get_पूर्णांक_hपूर्णांक(codec, "gpio_led", &spec->gpio_led)) अणु
		get_पूर्णांक_hपूर्णांक(codec, "gpio_led_polarity",
			     &spec->gpio_led_polarity);
		वापस 1;
	पूर्ण

	जबतक ((dev = dmi_find_device(DMI_DEV_TYPE_OEM_STRING, शून्य, dev))) अणु
		अगर (माला_पूछो(dev->name, "HP_Mute_LED_%u_%x",
			   &spec->gpio_led_polarity,
			   &spec->gpio_led) == 2) अणु
			अचिन्हित पूर्णांक max_gpio;
			max_gpio = snd_hda_param_पढ़ो(codec, codec->core.afg,
						      AC_PAR_GPIO_CAP);
			max_gpio &= AC_GPIO_IO_COUNT;
			अगर (spec->gpio_led < max_gpio)
				spec->gpio_led = 1 << spec->gpio_led;
			अन्यथा
				spec->vref_mute_led_nid = spec->gpio_led;
			वापस 1;
		पूर्ण
		अगर (माला_पूछो(dev->name, "HP_Mute_LED_%u",
			   &spec->gpio_led_polarity) == 1) अणु
			set_hp_led_gpio(codec);
			वापस 1;
		पूर्ण
		/* BIOS bug: unfilled OEM string */
		अगर (म_माला(dev->name, "HP_Mute_LED_P_G")) अणु
			set_hp_led_gpio(codec);
			अगर (शेष_polarity >= 0)
				spec->gpio_led_polarity = शेष_polarity;
			अन्यथा
				spec->gpio_led_polarity = 1;
			वापस 1;
		पूर्ण
	पूर्ण

	/*
	 * Fallback हाल - अगर we करोn't find the DMI strings,
	 * we अटलally set the GPIO - अगर not a B-series प्रणाली
	 * and शेष polarity is provided
	 */
	अगर (!hp_blike_प्रणाली(codec->core.subप्रणाली_id) &&
	    (शेष_polarity == 0 || शेष_polarity == 1)) अणु
		set_hp_led_gpio(codec);
		spec->gpio_led_polarity = शेष_polarity;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* check whether a built-in speaker is included in parsed pins */
अटल bool has_builtin_speaker(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;
	स्थिर hda_nid_t *nid_pin;
	पूर्णांक nids, i;

	अगर (spec->gen.स्वतःcfg.line_out_type == AUTO_PIN_SPEAKER_OUT) अणु
		nid_pin = spec->gen.स्वतःcfg.line_out_pins;
		nids = spec->gen.स्वतःcfg.line_outs;
	पूर्ण अन्यथा अणु
		nid_pin = spec->gen.स्वतःcfg.speaker_pins;
		nids = spec->gen.स्वतःcfg.speaker_outs;
	पूर्ण

	क्रम (i = 0; i < nids; i++) अणु
		अचिन्हित पूर्णांक def_conf = snd_hda_codec_get_pincfg(codec, nid_pin[i]);
		अगर (snd_hda_get_input_pin_attr(def_conf) == INPUT_PIN_ATTR_INT)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * PC beep controls
 */

/* create PC beep volume controls */
अटल पूर्णांक stac_स्वतः_create_beep_ctls(काष्ठा hda_codec *codec,
						hda_nid_t nid)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;
	u32 caps = query_amp_caps(codec, nid, HDA_OUTPUT);
	काष्ठा snd_kcontrol_new *knew;
	अटल स्थिर काष्ठा snd_kcontrol_new abeep_mute_ctl =
		HDA_CODEC_MUTE(शून्य, 0, 0, 0);
	अटल स्थिर काष्ठा snd_kcontrol_new dbeep_mute_ctl =
		HDA_CODEC_MUTE_BEEP(शून्य, 0, 0, 0);
	अटल स्थिर काष्ठा snd_kcontrol_new beep_vol_ctl =
		HDA_CODEC_VOLUME(शून्य, 0, 0, 0);

	/* check क्रम mute support क्रम the amp */
	अगर ((caps & AC_AMPCAP_MUTE) >> AC_AMPCAP_MUTE_SHIFT) अणु
		स्थिर काष्ठा snd_kcontrol_new *temp;
		अगर (spec->anabeep_nid == nid)
			temp = &abeep_mute_ctl;
		अन्यथा
			temp = &dbeep_mute_ctl;
		knew = snd_hda_gen_add_kctl(&spec->gen,
					    "Beep Playback Switch", temp);
		अगर (!knew)
			वापस -ENOMEM;
		knew->निजी_value =
			HDA_COMPOSE_AMP_VAL(nid, 1, 0, HDA_OUTPUT);
	पूर्ण

	/* check to see अगर there is volume support क्रम the amp */
	अगर ((caps & AC_AMPCAP_NUM_STEPS) >> AC_AMPCAP_NUM_STEPS_SHIFT) अणु
		knew = snd_hda_gen_add_kctl(&spec->gen,
					    "Beep Playback Volume",
					    &beep_vol_ctl);
		अगर (!knew)
			वापस -ENOMEM;
		knew->निजी_value =
			HDA_COMPOSE_AMP_VAL(nid, 1, 0, HDA_OUTPUT);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SND_HDA_INPUT_BEEP
#घोषणा stac_dig_beep_चयन_info snd_ctl_boolean_mono_info

अटल पूर्णांक stac_dig_beep_चयन_get(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = codec->beep->enabled;
	वापस 0;
पूर्ण

अटल पूर्णांक stac_dig_beep_चयन_put(काष्ठा snd_kcontrol *kcontrol,
				    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	वापस snd_hda_enable_beep_device(codec, ucontrol->value.पूर्णांकeger.value[0]);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new stac_dig_beep_ctrl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Beep Playback Switch",
	.info = stac_dig_beep_चयन_info,
	.get = stac_dig_beep_चयन_get,
	.put = stac_dig_beep_चयन_put,
पूर्ण;

अटल पूर्णांक stac_beep_चयन_ctl(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (!snd_hda_gen_add_kctl(&spec->gen, शून्य, &stac_dig_beep_ctrl))
		वापस -ENOMEM;
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * SPDIF-out mux controls
 */

अटल पूर्णांक stac_smux_क्रमागत_info(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा sigmatel_spec *spec = codec->spec;
	वापस snd_hda_input_mux_info(&spec->spdअगर_mux, uinfo);
पूर्ण

अटल पूर्णांक stac_smux_क्रमागत_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा sigmatel_spec *spec = codec->spec;
	अचिन्हित पूर्णांक smux_idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);

	ucontrol->value.क्रमागतerated.item[0] = spec->cur_smux[smux_idx];
	वापस 0;
पूर्ण

अटल पूर्णांक stac_smux_क्रमागत_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा sigmatel_spec *spec = codec->spec;
	अचिन्हित पूर्णांक smux_idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);

	वापस snd_hda_input_mux_put(codec, &spec->spdअगर_mux, ucontrol,
				     spec->gen.स्वतःcfg.dig_out_pins[smux_idx],
				     &spec->cur_smux[smux_idx]);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new stac_smux_mixer = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "IEC958 Playback Source",
	/* count set later */
	.info = stac_smux_क्रमागत_info,
	.get = stac_smux_क्रमागत_get,
	.put = stac_smux_क्रमागत_put,
पूर्ण;

अटल स्थिर अक्षर * स्थिर stac_spdअगर_labels[] = अणु
	"Digital Playback", "Analog Mux 1", "Analog Mux 2", शून्य
पूर्ण;

अटल पूर्णांक stac_create_spdअगर_mux_ctls(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;
	काष्ठा स्वतः_pin_cfg *cfg = &spec->gen.स्वतःcfg;
	स्थिर अक्षर * स्थिर *labels = spec->spdअगर_labels;
	काष्ठा snd_kcontrol_new *kctl;
	पूर्णांक i, num_cons;

	अगर (cfg->dig_outs < 1)
		वापस 0;

	num_cons = snd_hda_get_num_conns(codec, cfg->dig_out_pins[0]);
	अगर (num_cons <= 1)
		वापस 0;

	अगर (!labels)
		labels = stac_spdअगर_labels;
	क्रम (i = 0; i < num_cons; i++) अणु
		अगर (snd_BUG_ON(!labels[i]))
			वापस -EINVAL;
		snd_hda_add_imux_item(codec, &spec->spdअगर_mux, labels[i], i, शून्य);
	पूर्ण

	kctl = snd_hda_gen_add_kctl(&spec->gen, शून्य, &stac_smux_mixer);
	अगर (!kctl)
		वापस -ENOMEM;
	kctl->count = cfg->dig_outs;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hda_verb stac9200_eapd_init[] = अणु
	/* set dac0mux क्रम dac converter */
	अणु0x07, AC_VERB_SET_CONNECT_SEL, 0x00पूर्ण,
	अणु0x08, AC_VERB_SET_EAPD_BTLENABLE, 0x02पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_verb dell_eq_core_init[] = अणु
	/* set master volume to max value without distortion
	 * and direct control */
	अणु 0x1f, AC_VERB_SET_VOLUME_KNOB_CONTROL, 0xecपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_verb stac92hd73xx_core_init[] = अणु
	/* set master volume and direct control */
	अणु 0x1f, AC_VERB_SET_VOLUME_KNOB_CONTROL, 0xffपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_verb stac92hd83xxx_core_init[] = अणु
	/* घातer state controls amps */
	अणु 0x01, AC_VERB_SET_EAPD, 1 << 2पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_verb stac92hd83xxx_hp_zephyr_init[] = अणु
	अणु 0x22, 0x785, 0x43 पूर्ण,
	अणु 0x22, 0x782, 0xe0 पूर्ण,
	अणु 0x22, 0x795, 0x00 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_verb stac92hd71bxx_core_init[] = अणु
	/* set master volume and direct control */
	अणु 0x28, AC_VERB_SET_VOLUME_KNOB_CONTROL, 0xffपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर hda_nid_t stac92hd71bxx_unmute_nids[] = अणु
	/* unmute right and left channels क्रम nodes 0x0f, 0xa, 0x0d */
	0x0f, 0x0a, 0x0d, 0
पूर्ण;

अटल स्थिर काष्ठा hda_verb stac925x_core_init[] = अणु
	/* set dac0mux क्रम dac converter */
	अणु 0x06, AC_VERB_SET_CONNECT_SEL, 0x00पूर्ण,
	/* mute the master volume */
	अणु 0x0e, AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_MUTE पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_verb stac922x_core_init[] = अणु
	/* set master volume and direct control */
	अणु 0x16, AC_VERB_SET_VOLUME_KNOB_CONTROL, 0xffपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_verb d965_core_init[] = अणु
	/* unmute node 0x1b */
	अणु 0x1b, AC_VERB_SET_AMP_GAIN_MUTE, 0xb000पूर्ण,
	/* select node 0x03 as DAC */
	अणु 0x0b, AC_VERB_SET_CONNECT_SEL, 0x01पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_verb dell_3st_core_init[] = अणु
	/* करोn't set delta bit */
	अणु0x24, AC_VERB_SET_VOLUME_KNOB_CONTROL, 0x7fपूर्ण,
	/* unmute node 0x1b */
	अणु0x1b, AC_VERB_SET_AMP_GAIN_MUTE, 0xb000पूर्ण,
	/* select node 0x03 as DAC */
	अणु0x0b, AC_VERB_SET_CONNECT_SEL, 0x01पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_verb stac927x_core_init[] = अणु
	/* set master volume and direct control */
	अणु 0x24, AC_VERB_SET_VOLUME_KNOB_CONTROL, 0xffपूर्ण,
	/* enable analog pc beep path */
	अणु 0x01, AC_VERB_SET_DIGI_CONVERT_2, 1 << 5पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_verb stac927x_volknob_core_init[] = अणु
	/* करोn't set delta bit */
	अणु0x24, AC_VERB_SET_VOLUME_KNOB_CONTROL, 0x7fपूर्ण,
	/* enable analog pc beep path */
	अणु0x01, AC_VERB_SET_DIGI_CONVERT_2, 1 << 5पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_verb stac9205_core_init[] = अणु
	/* set master volume and direct control */
	अणु 0x24, AC_VERB_SET_VOLUME_KNOB_CONTROL, 0xffपूर्ण,
	/* enable analog pc beep path */
	अणु 0x01, AC_VERB_SET_DIGI_CONVERT_2, 1 << 5पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new stac92hd73xx_6ch_loopback =
	STAC_ANALOG_LOOPBACK(0xFA0, 0x7A1, 3);

अटल स्थिर काष्ठा snd_kcontrol_new stac92hd73xx_8ch_loopback =
	STAC_ANALOG_LOOPBACK(0xFA0, 0x7A1, 4);

अटल स्थिर काष्ठा snd_kcontrol_new stac92hd73xx_10ch_loopback =
	STAC_ANALOG_LOOPBACK(0xFA0, 0x7A1, 5);

अटल स्थिर काष्ठा snd_kcontrol_new stac92hd71bxx_loopback =
	STAC_ANALOG_LOOPBACK(0xFA0, 0x7A0, 2);

अटल स्थिर काष्ठा snd_kcontrol_new stac9205_loopback =
	STAC_ANALOG_LOOPBACK(0xFE0, 0x7E0, 1);

अटल स्थिर काष्ठा snd_kcontrol_new stac927x_loopback =
	STAC_ANALOG_LOOPBACK(0xFEB, 0x7EB, 1);

अटल स्थिर काष्ठा hda_pपूर्णांकbl ref9200_pin_configs[] = अणु
	अणु 0x08, 0x01c47010 पूर्ण,
	अणु 0x09, 0x01447010 पूर्ण,
	अणु 0x0d, 0x0221401f पूर्ण,
	अणु 0x0e, 0x01114010 पूर्ण,
	अणु 0x0f, 0x02a19020 पूर्ण,
	अणु 0x10, 0x01a19021 पूर्ण,
	अणु 0x11, 0x90100140 पूर्ण,
	अणु 0x12, 0x01813122 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl gateway9200_m4_pin_configs[] = अणु
	अणु 0x08, 0x400000fe पूर्ण,
	अणु 0x09, 0x404500f4 पूर्ण,
	अणु 0x0d, 0x400100f0 पूर्ण,
	अणु 0x0e, 0x90110010 पूर्ण,
	अणु 0x0f, 0x400100f1 पूर्ण,
	अणु 0x10, 0x02a1902e पूर्ण,
	अणु 0x11, 0x500000f2 पूर्ण,
	अणु 0x12, 0x500000f3 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl gateway9200_m4_2_pin_configs[] = अणु
	अणु 0x08, 0x400000fe पूर्ण,
	अणु 0x09, 0x404500f4 पूर्ण,
	अणु 0x0d, 0x400100f0 पूर्ण,
	अणु 0x0e, 0x90110010 पूर्ण,
	अणु 0x0f, 0x400100f1 पूर्ण,
	अणु 0x10, 0x02a1902e पूर्ण,
	अणु 0x11, 0x500000f2 पूर्ण,
	अणु 0x12, 0x500000f3 पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
    STAC 9200 pin configs क्रम
    102801A8
    102801DE
    102801E8
*/
अटल स्थिर काष्ठा hda_pपूर्णांकbl dell9200_d21_pin_configs[] = अणु
	अणु 0x08, 0x400001f0 पूर्ण,
	अणु 0x09, 0x400001f1 पूर्ण,
	अणु 0x0d, 0x02214030 पूर्ण,
	अणु 0x0e, 0x01014010 पूर्ण,
	अणु 0x0f, 0x02a19020 पूर्ण,
	अणु 0x10, 0x01a19021 पूर्ण,
	अणु 0x11, 0x90100140 पूर्ण,
	अणु 0x12, 0x01813122 पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
    STAC 9200 pin configs क्रम
    102801C0
    102801C1
*/
अटल स्थिर काष्ठा hda_pपूर्णांकbl dell9200_d22_pin_configs[] = अणु
	अणु 0x08, 0x400001f0 पूर्ण,
	अणु 0x09, 0x400001f1 पूर्ण,
	अणु 0x0d, 0x0221401f पूर्ण,
	अणु 0x0e, 0x01014010 पूर्ण,
	अणु 0x0f, 0x01813020 पूर्ण,
	अणु 0x10, 0x02a19021 पूर्ण,
	अणु 0x11, 0x90100140 पूर्ण,
	अणु 0x12, 0x400001f2 पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
    STAC 9200 pin configs क्रम
    102801C4 (Dell Dimension E310)
    102801C5
    102801C7
    102801D9
    102801DA
    102801E3
*/
अटल स्थिर काष्ठा hda_pपूर्णांकbl dell9200_d23_pin_configs[] = अणु
	अणु 0x08, 0x400001f0 पूर्ण,
	अणु 0x09, 0x400001f1 पूर्ण,
	अणु 0x0d, 0x0221401f पूर्ण,
	अणु 0x0e, 0x01014010 पूर्ण,
	अणु 0x0f, 0x01813020 पूर्ण,
	अणु 0x10, 0x01a19021 पूर्ण,
	अणु 0x11, 0x90100140 पूर्ण,
	अणु 0x12, 0x400001f2 पूर्ण,
	अणुपूर्ण
पूर्ण;


/* 
    STAC 9200-32 pin configs क्रम
    102801B5 (Dell Inspiron 630m)
    102801D8 (Dell Inspiron 640m)
*/
अटल स्थिर काष्ठा hda_pपूर्णांकbl dell9200_m21_pin_configs[] = अणु
	अणु 0x08, 0x40c003fa पूर्ण,
	अणु 0x09, 0x03441340 पूर्ण,
	अणु 0x0d, 0x0321121f पूर्ण,
	अणु 0x0e, 0x90170310 पूर्ण,
	अणु 0x0f, 0x408003fb पूर्ण,
	अणु 0x10, 0x03a11020 पूर्ण,
	अणु 0x11, 0x401003fc पूर्ण,
	अणु 0x12, 0x403003fd पूर्ण,
	अणुपूर्ण
पूर्ण;

/* 
    STAC 9200-32 pin configs क्रम
    102801C2 (Dell Latitude D620)
    102801C8 
    102801CC (Dell Latitude D820)
    102801D4 
    102801D6 
*/
अटल स्थिर काष्ठा hda_pपूर्णांकbl dell9200_m22_pin_configs[] = अणु
	अणु 0x08, 0x40c003fa पूर्ण,
	अणु 0x09, 0x0144131f पूर्ण,
	अणु 0x0d, 0x0321121f पूर्ण,
	अणु 0x0e, 0x90170310 पूर्ण,
	अणु 0x0f, 0x90a70321 पूर्ण,
	अणु 0x10, 0x03a11020 पूर्ण,
	अणु 0x11, 0x401003fb पूर्ण,
	अणु 0x12, 0x40f000fc पूर्ण,
	अणुपूर्ण
पूर्ण;

/* 
    STAC 9200-32 pin configs क्रम
    102801CE (Dell XPS M1710)
    102801CF (Dell Precision M90)
*/
अटल स्थिर काष्ठा hda_pपूर्णांकbl dell9200_m23_pin_configs[] = अणु
	अणु 0x08, 0x40c003fa पूर्ण,
	अणु 0x09, 0x01441340 पूर्ण,
	अणु 0x0d, 0x0421421f पूर्ण,
	अणु 0x0e, 0x90170310 पूर्ण,
	अणु 0x0f, 0x408003fb पूर्ण,
	अणु 0x10, 0x04a1102e पूर्ण,
	अणु 0x11, 0x90170311 पूर्ण,
	अणु 0x12, 0x403003fc पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
    STAC 9200-32 pin configs क्रम 
    102801C9
    102801CA
    102801CB (Dell Latitude 120L)
    102801D3
*/
अटल स्थिर काष्ठा hda_pपूर्णांकbl dell9200_m24_pin_configs[] = अणु
	अणु 0x08, 0x40c003fa पूर्ण,
	अणु 0x09, 0x404003fb पूर्ण,
	अणु 0x0d, 0x0321121f पूर्ण,
	अणु 0x0e, 0x90170310 पूर्ण,
	अणु 0x0f, 0x408003fc पूर्ण,
	अणु 0x10, 0x03a11020 पूर्ण,
	अणु 0x11, 0x401003fd पूर्ण,
	अणु 0x12, 0x403003fe पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
    STAC 9200-32 pin configs क्रम
    102801BD (Dell Inspiron E1505n)
    102801EE
    102801EF
*/
अटल स्थिर काष्ठा hda_pपूर्णांकbl dell9200_m25_pin_configs[] = अणु
	अणु 0x08, 0x40c003fa पूर्ण,
	अणु 0x09, 0x01441340 पूर्ण,
	अणु 0x0d, 0x0421121f पूर्ण,
	अणु 0x0e, 0x90170310 पूर्ण,
	अणु 0x0f, 0x408003fb पूर्ण,
	अणु 0x10, 0x04a11020 पूर्ण,
	अणु 0x11, 0x401003fc पूर्ण,
	अणु 0x12, 0x403003fd पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
    STAC 9200-32 pin configs क्रम
    102801F5 (Dell Inspiron 1501)
    102801F6
*/
अटल स्थिर काष्ठा hda_pपूर्णांकbl dell9200_m26_pin_configs[] = अणु
	अणु 0x08, 0x40c003fa पूर्ण,
	अणु 0x09, 0x404003fb पूर्ण,
	अणु 0x0d, 0x0421121f पूर्ण,
	अणु 0x0e, 0x90170310 पूर्ण,
	अणु 0x0f, 0x408003fc पूर्ण,
	अणु 0x10, 0x04a11020 पूर्ण,
	अणु 0x11, 0x401003fd पूर्ण,
	अणु 0x12, 0x403003fe पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
    STAC 9200-32
    102801CD (Dell Inspiron E1705/9400)
*/
अटल स्थिर काष्ठा hda_pपूर्णांकbl dell9200_m27_pin_configs[] = अणु
	अणु 0x08, 0x40c003fa पूर्ण,
	अणु 0x09, 0x01441340 पूर्ण,
	अणु 0x0d, 0x0421121f पूर्ण,
	अणु 0x0e, 0x90170310 पूर्ण,
	अणु 0x0f, 0x90170310 पूर्ण,
	अणु 0x10, 0x04a11020 पूर्ण,
	अणु 0x11, 0x90170310 पूर्ण,
	अणु 0x12, 0x40f003fc पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl oqo9200_pin_configs[] = अणु
	अणु 0x08, 0x40c000f0 पूर्ण,
	अणु 0x09, 0x404000f1 पूर्ण,
	अणु 0x0d, 0x0221121f पूर्ण,
	अणु 0x0e, 0x02211210 पूर्ण,
	अणु 0x0f, 0x90170111 पूर्ण,
	अणु 0x10, 0x90a70120 पूर्ण,
	अणु 0x11, 0x400000f2 पूर्ण,
	अणु 0x12, 0x400000f3 पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 *  STAC 92HD700
 *  18881000 Amigaone X1000
 */
अटल स्थिर काष्ठा hda_pपूर्णांकbl nemo_pin_configs[] = अणु
	अणु 0x0a, 0x02214020 पूर्ण,	/* Front panel HP socket */
	अणु 0x0b, 0x02a19080 पूर्ण,	/* Front Mic */
	अणु 0x0c, 0x0181304e पूर्ण,	/* Line in */
	अणु 0x0d, 0x01014010 पूर्ण,	/* Line out */
	अणु 0x0e, 0x01a19040 पूर्ण,	/* Rear Mic */
	अणु 0x0f, 0x01011012 पूर्ण,	/* Rear speakers */
	अणु 0x10, 0x01016011 पूर्ण,	/* Center speaker */
	अणु 0x11, 0x01012014 पूर्ण,	/* Side speakers (7.1) */
	अणु 0x12, 0x103301f0 पूर्ण,	/* Motherboard CD line in connector */
	अणु 0x13, 0x411111f0 पूर्ण,	/* Unused */
	अणु 0x14, 0x411111f0 पूर्ण,	/* Unused */
	अणु 0x21, 0x01442170 पूर्ण,	/* S/PDIF line out */
	अणु 0x22, 0x411111f0 पूर्ण,	/* Unused */
	अणु 0x23, 0x411111f0 पूर्ण,	/* Unused */
	अणुपूर्ण
पूर्ण;

अटल व्योम stac9200_fixup_panasonic(काष्ठा hda_codec *codec,
				     स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		spec->gpio_mask = spec->gpio_dir = 0x09;
		spec->gpio_data = 0x00;
		/* CF-74 has no headphone detection, and the driver should *NOT*
		 * करो detection and HP/speaker toggle because the hardware करोes it.
		 */
		spec->gen.suppress_स्वतः_mute = 1;
	पूर्ण
पूर्ण


अटल स्थिर काष्ठा hda_fixup stac9200_fixups[] = अणु
	[STAC_REF] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = ref9200_pin_configs,
	पूर्ण,
	[STAC_9200_OQO] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = oqo9200_pin_configs,
		.chained = true,
		.chain_id = STAC_9200_EAPD_INIT,
	पूर्ण,
	[STAC_9200_DELL_D21] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell9200_d21_pin_configs,
	पूर्ण,
	[STAC_9200_DELL_D22] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell9200_d22_pin_configs,
	पूर्ण,
	[STAC_9200_DELL_D23] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell9200_d23_pin_configs,
	पूर्ण,
	[STAC_9200_DELL_M21] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell9200_m21_pin_configs,
	पूर्ण,
	[STAC_9200_DELL_M22] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell9200_m22_pin_configs,
	पूर्ण,
	[STAC_9200_DELL_M23] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell9200_m23_pin_configs,
	पूर्ण,
	[STAC_9200_DELL_M24] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell9200_m24_pin_configs,
	पूर्ण,
	[STAC_9200_DELL_M25] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell9200_m25_pin_configs,
	पूर्ण,
	[STAC_9200_DELL_M26] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell9200_m26_pin_configs,
	पूर्ण,
	[STAC_9200_DELL_M27] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell9200_m27_pin_configs,
	पूर्ण,
	[STAC_9200_M4] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = gateway9200_m4_pin_configs,
		.chained = true,
		.chain_id = STAC_9200_EAPD_INIT,
	पूर्ण,
	[STAC_9200_M4_2] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = gateway9200_m4_2_pin_configs,
		.chained = true,
		.chain_id = STAC_9200_EAPD_INIT,
	पूर्ण,
	[STAC_9200_PANASONIC] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac9200_fixup_panasonic,
	पूर्ण,
	[STAC_9200_EAPD_INIT] = अणु
		.type = HDA_FIXUP_VERBS,
		.v.verbs = (स्थिर काष्ठा hda_verb[]) अणु
			अणु0x08, AC_VERB_SET_EAPD_BTLENABLE, 0x02पूर्ण,
			अणुपूर्ण
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_model_fixup stac9200_models[] = अणु
	अणु .id = STAC_REF, .name = "ref" पूर्ण,
	अणु .id = STAC_9200_OQO, .name = "oqo" पूर्ण,
	अणु .id = STAC_9200_DELL_D21, .name = "dell-d21" पूर्ण,
	अणु .id = STAC_9200_DELL_D22, .name = "dell-d22" पूर्ण,
	अणु .id = STAC_9200_DELL_D23, .name = "dell-d23" पूर्ण,
	अणु .id = STAC_9200_DELL_M21, .name = "dell-m21" पूर्ण,
	अणु .id = STAC_9200_DELL_M22, .name = "dell-m22" पूर्ण,
	अणु .id = STAC_9200_DELL_M23, .name = "dell-m23" पूर्ण,
	अणु .id = STAC_9200_DELL_M24, .name = "dell-m24" पूर्ण,
	अणु .id = STAC_9200_DELL_M25, .name = "dell-m25" पूर्ण,
	अणु .id = STAC_9200_DELL_M26, .name = "dell-m26" पूर्ण,
	अणु .id = STAC_9200_DELL_M27, .name = "dell-m27" पूर्ण,
	अणु .id = STAC_9200_M4, .name = "gateway-m4" पूर्ण,
	अणु .id = STAC_9200_M4_2, .name = "gateway-m4-2" पूर्ण,
	अणु .id = STAC_9200_PANASONIC, .name = "panasonic" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk stac9200_fixup_tbl[] = अणु
	/* SigmaTel reference board */
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x2668,
		      "DFI LanParty", STAC_REF),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DFI, 0x3101,
		      "DFI LanParty", STAC_REF),
	/* Dell laptops have BIOS problem */
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01a8,
		      "unknown Dell", STAC_9200_DELL_D21),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01b5,
		      "Dell Inspiron 630m", STAC_9200_DELL_M21),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01bd,
		      "Dell Inspiron E1505n", STAC_9200_DELL_M25),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01c0,
		      "unknown Dell", STAC_9200_DELL_D22),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01c1,
		      "unknown Dell", STAC_9200_DELL_D22),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01c2,
		      "Dell Latitude D620", STAC_9200_DELL_M22),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01c5,
		      "unknown Dell", STAC_9200_DELL_D23),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01c7,
		      "unknown Dell", STAC_9200_DELL_D23),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01c8,
		      "unknown Dell", STAC_9200_DELL_M22),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01c9,
		      "unknown Dell", STAC_9200_DELL_M24),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01ca,
		      "unknown Dell", STAC_9200_DELL_M24),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01cb,
		      "Dell Latitude 120L", STAC_9200_DELL_M24),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01cc,
		      "Dell Latitude D820", STAC_9200_DELL_M22),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01cd,
		      "Dell Inspiron E1705/9400", STAC_9200_DELL_M27),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01ce,
		      "Dell XPS M1710", STAC_9200_DELL_M23),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01cf,
		      "Dell Precision M90", STAC_9200_DELL_M23),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01d3,
		      "unknown Dell", STAC_9200_DELL_M22),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01d4,
		      "unknown Dell", STAC_9200_DELL_M22),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01d6,
		      "unknown Dell", STAC_9200_DELL_M22),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01d8,
		      "Dell Inspiron 640m", STAC_9200_DELL_M21),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01d9,
		      "unknown Dell", STAC_9200_DELL_D23),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01da,
		      "unknown Dell", STAC_9200_DELL_D23),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01de,
		      "unknown Dell", STAC_9200_DELL_D21),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01e3,
		      "unknown Dell", STAC_9200_DELL_D23),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01e8,
		      "unknown Dell", STAC_9200_DELL_D21),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01ee,
		      "unknown Dell", STAC_9200_DELL_M25),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01ef,
		      "unknown Dell", STAC_9200_DELL_M25),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01f5,
		      "Dell Inspiron 1501", STAC_9200_DELL_M26),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01f6,
		      "unknown Dell", STAC_9200_DELL_M26),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0201,
		      "Dell Latitude D430", STAC_9200_DELL_M22),
	/* Panasonic */
	SND_PCI_QUIRK(0x10f7, 0x8338, "Panasonic CF-74", STAC_9200_PANASONIC),
	/* Gateway machines needs EAPD to be set on resume */
	SND_PCI_QUIRK(0x107b, 0x0205, "Gateway S-7110M", STAC_9200_M4),
	SND_PCI_QUIRK(0x107b, 0x0317, "Gateway MT3423, MX341*", STAC_9200_M4_2),
	SND_PCI_QUIRK(0x107b, 0x0318, "Gateway ML3019, MT3707", STAC_9200_M4_2),
	/* OQO Mobile */
	SND_PCI_QUIRK(0x1106, 0x3288, "OQO Model 2", STAC_9200_OQO),
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl ref925x_pin_configs[] = अणु
	अणु 0x07, 0x40c003f0 पूर्ण,
	अणु 0x08, 0x424503f2 पूर्ण,
	अणु 0x0a, 0x01813022 पूर्ण,
	अणु 0x0b, 0x02a19021 पूर्ण,
	अणु 0x0c, 0x90a70320 पूर्ण,
	अणु 0x0d, 0x02214210 पूर्ण,
	अणु 0x10, 0x01019020 पूर्ण,
	अणु 0x11, 0x9033032e पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl stac925xM1_pin_configs[] = अणु
	अणु 0x07, 0x40c003f4 पूर्ण,
	अणु 0x08, 0x424503f2 पूर्ण,
	अणु 0x0a, 0x400000f3 पूर्ण,
	अणु 0x0b, 0x02a19020 पूर्ण,
	अणु 0x0c, 0x40a000f0 पूर्ण,
	अणु 0x0d, 0x90100210 पूर्ण,
	अणु 0x10, 0x400003f1 पूर्ण,
	अणु 0x11, 0x9033032e पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl stac925xM1_2_pin_configs[] = अणु
	अणु 0x07, 0x40c003f4 पूर्ण,
	अणु 0x08, 0x424503f2 पूर्ण,
	अणु 0x0a, 0x400000f3 पूर्ण,
	अणु 0x0b, 0x02a19020 पूर्ण,
	अणु 0x0c, 0x40a000f0 पूर्ण,
	अणु 0x0d, 0x90100210 पूर्ण,
	अणु 0x10, 0x400003f1 पूर्ण,
	अणु 0x11, 0x9033032e पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl stac925xM2_pin_configs[] = अणु
	अणु 0x07, 0x40c003f4 पूर्ण,
	अणु 0x08, 0x424503f2 पूर्ण,
	अणु 0x0a, 0x400000f3 पूर्ण,
	अणु 0x0b, 0x02a19020 पूर्ण,
	अणु 0x0c, 0x40a000f0 पूर्ण,
	अणु 0x0d, 0x90100210 पूर्ण,
	अणु 0x10, 0x400003f1 पूर्ण,
	अणु 0x11, 0x9033032e पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl stac925xM2_2_pin_configs[] = अणु
	अणु 0x07, 0x40c003f4 पूर्ण,
	अणु 0x08, 0x424503f2 पूर्ण,
	अणु 0x0a, 0x400000f3 पूर्ण,
	अणु 0x0b, 0x02a19020 पूर्ण,
	अणु 0x0c, 0x40a000f0 पूर्ण,
	अणु 0x0d, 0x90100210 पूर्ण,
	अणु 0x10, 0x400003f1 पूर्ण,
	अणु 0x11, 0x9033032e पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl stac925xM3_pin_configs[] = अणु
	अणु 0x07, 0x40c003f4 पूर्ण,
	अणु 0x08, 0x424503f2 पूर्ण,
	अणु 0x0a, 0x400000f3 पूर्ण,
	अणु 0x0b, 0x02a19020 पूर्ण,
	अणु 0x0c, 0x40a000f0 पूर्ण,
	अणु 0x0d, 0x90100210 पूर्ण,
	अणु 0x10, 0x400003f1 पूर्ण,
	अणु 0x11, 0x503303f3 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl stac925xM5_pin_configs[] = अणु
	अणु 0x07, 0x40c003f4 पूर्ण,
	अणु 0x08, 0x424503f2 पूर्ण,
	अणु 0x0a, 0x400000f3 पूर्ण,
	अणु 0x0b, 0x02a19020 पूर्ण,
	अणु 0x0c, 0x40a000f0 पूर्ण,
	अणु 0x0d, 0x90100210 पूर्ण,
	अणु 0x10, 0x400003f1 पूर्ण,
	अणु 0x11, 0x9033032e पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl stac925xM6_pin_configs[] = अणु
	अणु 0x07, 0x40c003f4 पूर्ण,
	अणु 0x08, 0x424503f2 पूर्ण,
	अणु 0x0a, 0x400000f3 पूर्ण,
	अणु 0x0b, 0x02a19020 पूर्ण,
	अणु 0x0c, 0x40a000f0 पूर्ण,
	अणु 0x0d, 0x90100210 पूर्ण,
	अणु 0x10, 0x400003f1 पूर्ण,
	अणु 0x11, 0x90330320 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_fixup stac925x_fixups[] = अणु
	[STAC_REF] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = ref925x_pin_configs,
	पूर्ण,
	[STAC_M1] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = stac925xM1_pin_configs,
	पूर्ण,
	[STAC_M1_2] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = stac925xM1_2_pin_configs,
	पूर्ण,
	[STAC_M2] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = stac925xM2_pin_configs,
	पूर्ण,
	[STAC_M2_2] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = stac925xM2_2_pin_configs,
	पूर्ण,
	[STAC_M3] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = stac925xM3_pin_configs,
	पूर्ण,
	[STAC_M5] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = stac925xM5_pin_configs,
	पूर्ण,
	[STAC_M6] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = stac925xM6_pin_configs,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_model_fixup stac925x_models[] = अणु
	अणु .id = STAC_REF, .name = "ref" पूर्ण,
	अणु .id = STAC_M1, .name = "m1" पूर्ण,
	अणु .id = STAC_M1_2, .name = "m1-2" पूर्ण,
	अणु .id = STAC_M2, .name = "m2" पूर्ण,
	अणु .id = STAC_M2_2, .name = "m2-2" पूर्ण,
	अणु .id = STAC_M3, .name = "m3" पूर्ण,
	अणु .id = STAC_M5, .name = "m5" पूर्ण,
	अणु .id = STAC_M6, .name = "m6" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk stac925x_fixup_tbl[] = अणु
	/* SigmaTel reference board */
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x2668, "DFI LanParty", STAC_REF),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DFI, 0x3101, "DFI LanParty", STAC_REF),
	SND_PCI_QUIRK(0x8384, 0x7632, "Stac9202 Reference Board", STAC_REF),

	/* Default table क्रम unknown ID */
	SND_PCI_QUIRK(0x1002, 0x437b, "Gateway mobile", STAC_M2_2),

	/* gateway machines are checked via codec ssid */
	SND_PCI_QUIRK(0x107b, 0x0316, "Gateway M255", STAC_M2),
	SND_PCI_QUIRK(0x107b, 0x0366, "Gateway MP6954", STAC_M5),
	SND_PCI_QUIRK(0x107b, 0x0461, "Gateway NX560XL", STAC_M1),
	SND_PCI_QUIRK(0x107b, 0x0681, "Gateway NX860", STAC_M2),
	SND_PCI_QUIRK(0x107b, 0x0367, "Gateway MX6453", STAC_M1_2),
	/* Not sure about the bअक्रम name क्रम those */
	SND_PCI_QUIRK(0x107b, 0x0281, "Gateway mobile", STAC_M1),
	SND_PCI_QUIRK(0x107b, 0x0507, "Gateway mobile", STAC_M3),
	SND_PCI_QUIRK(0x107b, 0x0281, "Gateway mobile", STAC_M6),
	SND_PCI_QUIRK(0x107b, 0x0685, "Gateway mobile", STAC_M2_2),
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl ref92hd73xx_pin_configs[] = अणु
	अणु 0x0a, 0x02214030 पूर्ण,
	अणु 0x0b, 0x02a19040 पूर्ण,
	अणु 0x0c, 0x01a19020 पूर्ण,
	अणु 0x0d, 0x02214030 पूर्ण,
	अणु 0x0e, 0x0181302e पूर्ण,
	अणु 0x0f, 0x01014010 पूर्ण,
	अणु 0x10, 0x01014020 पूर्ण,
	अणु 0x11, 0x01014030 पूर्ण,
	अणु 0x12, 0x02319040 पूर्ण,
	अणु 0x13, 0x90a000f0 पूर्ण,
	अणु 0x14, 0x90a000f0 पूर्ण,
	अणु 0x22, 0x01452050 पूर्ण,
	अणु 0x23, 0x01452050 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl dell_m6_pin_configs[] = अणु
	अणु 0x0a, 0x0321101f पूर्ण,
	अणु 0x0b, 0x4f00000f पूर्ण,
	अणु 0x0c, 0x4f0000f0 पूर्ण,
	अणु 0x0d, 0x90170110 पूर्ण,
	अणु 0x0e, 0x03a11020 पूर्ण,
	अणु 0x0f, 0x0321101f पूर्ण,
	अणु 0x10, 0x4f0000f0 पूर्ण,
	अणु 0x11, 0x4f0000f0 पूर्ण,
	अणु 0x12, 0x4f0000f0 पूर्ण,
	अणु 0x13, 0x90a60160 पूर्ण,
	अणु 0x14, 0x4f0000f0 पूर्ण,
	अणु 0x22, 0x4f0000f0 पूर्ण,
	अणु 0x23, 0x4f0000f0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl alienware_m17x_pin_configs[] = अणु
	अणु 0x0a, 0x0321101f पूर्ण,
	अणु 0x0b, 0x0321101f पूर्ण,
	अणु 0x0c, 0x03a11020 पूर्ण,
	अणु 0x0d, 0x03014020 पूर्ण,
	अणु 0x0e, 0x90170110 पूर्ण,
	अणु 0x0f, 0x4f0000f0 पूर्ण,
	अणु 0x10, 0x4f0000f0 पूर्ण,
	अणु 0x11, 0x4f0000f0 पूर्ण,
	अणु 0x12, 0x4f0000f0 पूर्ण,
	अणु 0x13, 0x90a60160 पूर्ण,
	अणु 0x14, 0x4f0000f0 पूर्ण,
	अणु 0x22, 0x4f0000f0 पूर्ण,
	अणु 0x23, 0x904601b0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl पूर्णांकel_dg45id_pin_configs[] = अणु
	अणु 0x0a, 0x02214230 पूर्ण,
	अणु 0x0b, 0x02A19240 पूर्ण,
	अणु 0x0c, 0x01013214 पूर्ण,
	अणु 0x0d, 0x01014210 पूर्ण,
	अणु 0x0e, 0x01A19250 पूर्ण,
	अणु 0x0f, 0x01011212 पूर्ण,
	अणु 0x10, 0x01016211 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl stac92hd89xx_hp_front_jack_pin_configs[] = अणु
	अणु 0x0a, 0x02214030 पूर्ण,
	अणु 0x0b, 0x02A19010 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl stac92hd89xx_hp_z1_g2_right_mic_jack_pin_configs[] = अणु
	अणु 0x0e, 0x400000f0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम stac92hd73xx_fixup_ref(काष्ठा hda_codec *codec,
				   स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	snd_hda_apply_pincfgs(codec, ref92hd73xx_pin_configs);
	spec->gpio_mask = spec->gpio_dir = spec->gpio_data = 0;
पूर्ण

अटल व्योम stac92hd73xx_fixup_dell(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	snd_hda_apply_pincfgs(codec, dell_m6_pin_configs);
	spec->eapd_चयन = 0;
पूर्ण

अटल व्योम stac92hd73xx_fixup_dell_eq(काष्ठा hda_codec *codec,
				       स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	stac92hd73xx_fixup_dell(codec);
	snd_hda_add_verbs(codec, dell_eq_core_init);
	spec->volknob_init = 1;
पूर्ण

/* Analog Mics */
अटल व्योम stac92hd73xx_fixup_dell_m6_amic(काष्ठा hda_codec *codec,
				    स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	stac92hd73xx_fixup_dell(codec);
	snd_hda_codec_set_pincfg(codec, 0x0b, 0x90A70170);
पूर्ण

/* Digital Mics */
अटल व्योम stac92hd73xx_fixup_dell_m6_dmic(काष्ठा hda_codec *codec,
				    स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	stac92hd73xx_fixup_dell(codec);
	snd_hda_codec_set_pincfg(codec, 0x13, 0x90A60160);
पूर्ण

/* Both */
अटल व्योम stac92hd73xx_fixup_dell_m6_both(काष्ठा hda_codec *codec,
				    स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	stac92hd73xx_fixup_dell(codec);
	snd_hda_codec_set_pincfg(codec, 0x0b, 0x90A70170);
	snd_hda_codec_set_pincfg(codec, 0x13, 0x90A60160);
पूर्ण

अटल व्योम stac92hd73xx_fixup_alienware_m17x(काष्ठा hda_codec *codec,
				    स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	snd_hda_apply_pincfgs(codec, alienware_m17x_pin_configs);
	spec->eapd_चयन = 0;
पूर्ण

अटल व्योम stac92hd73xx_fixup_no_jd(काष्ठा hda_codec *codec,
				     स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action == HDA_FIXUP_ACT_PRE_PROBE)
		codec->no_jack_detect = 1;
पूर्ण


अटल व्योम stac92hd73xx_disable_स्वतःmute(काष्ठा hda_codec *codec,
				     स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	spec->gen.suppress_स्वतः_mute = 1;
पूर्ण

अटल स्थिर काष्ठा hda_fixup stac92hd73xx_fixups[] = अणु
	[STAC_92HD73XX_REF] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd73xx_fixup_ref,
	पूर्ण,
	[STAC_DELL_M6_AMIC] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd73xx_fixup_dell_m6_amic,
	पूर्ण,
	[STAC_DELL_M6_DMIC] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd73xx_fixup_dell_m6_dmic,
	पूर्ण,
	[STAC_DELL_M6_BOTH] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd73xx_fixup_dell_m6_both,
	पूर्ण,
	[STAC_DELL_EQ]	= अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd73xx_fixup_dell_eq,
	पूर्ण,
	[STAC_ALIENWARE_M17X] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd73xx_fixup_alienware_m17x,
	पूर्ण,
	[STAC_ELO_VUPOINT_15MX] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd73xx_disable_स्वतःmute,
	पूर्ण,
	[STAC_92HD73XX_INTEL] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = पूर्णांकel_dg45id_pin_configs,
	पूर्ण,
	[STAC_92HD73XX_NO_JD] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd73xx_fixup_no_jd,
	पूर्ण,
	[STAC_92HD89XX_HP_FRONT_JACK] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = stac92hd89xx_hp_front_jack_pin_configs,
	पूर्ण,
	[STAC_92HD89XX_HP_Z1_G2_RIGHT_MIC_JACK] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = stac92hd89xx_hp_z1_g2_right_mic_jack_pin_configs,
	पूर्ण,
	[STAC_92HD73XX_ASUS_MOBO] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			/* enable 5.1 and SPDIF out */
			अणु 0x0c, 0x01014411 पूर्ण,
			अणु 0x0d, 0x01014410 पूर्ण,
			अणु 0x0e, 0x01014412 पूर्ण,
			अणु 0x22, 0x014b1180 पूर्ण,
			अणु पूर्ण
		पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_model_fixup stac92hd73xx_models[] = अणु
	अणु .id = STAC_92HD73XX_NO_JD, .name = "no-jd" पूर्ण,
	अणु .id = STAC_92HD73XX_REF, .name = "ref" पूर्ण,
	अणु .id = STAC_92HD73XX_INTEL, .name = "intel" पूर्ण,
	अणु .id = STAC_DELL_M6_AMIC, .name = "dell-m6-amic" पूर्ण,
	अणु .id = STAC_DELL_M6_DMIC, .name = "dell-m6-dmic" पूर्ण,
	अणु .id = STAC_DELL_M6_BOTH, .name = "dell-m6" पूर्ण,
	अणु .id = STAC_DELL_EQ, .name = "dell-eq" पूर्ण,
	अणु .id = STAC_ALIENWARE_M17X, .name = "alienware" पूर्ण,
	अणु .id = STAC_ELO_VUPOINT_15MX, .name = "elo-vupoint-15mx" पूर्ण,
	अणु .id = STAC_92HD73XX_ASUS_MOBO, .name = "asus-mobo" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk stac92hd73xx_fixup_tbl[] = अणु
	/* SigmaTel reference board */
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x2668,
				"DFI LanParty", STAC_92HD73XX_REF),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DFI, 0x3101,
				"DFI LanParty", STAC_92HD73XX_REF),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x5002,
				"Intel DG45ID", STAC_92HD73XX_INTEL),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x5003,
				"Intel DG45FC", STAC_92HD73XX_INTEL),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0254,
				"Dell Studio 1535", STAC_DELL_M6_DMIC),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0255,
				"unknown Dell", STAC_DELL_M6_DMIC),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0256,
				"unknown Dell", STAC_DELL_M6_BOTH),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0257,
				"unknown Dell", STAC_DELL_M6_BOTH),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x025e,
				"unknown Dell", STAC_DELL_M6_AMIC),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x025f,
				"unknown Dell", STAC_DELL_M6_AMIC),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0271,
				"unknown Dell", STAC_DELL_M6_DMIC),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0272,
				"unknown Dell", STAC_DELL_M6_DMIC),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x029f,
				"Dell Studio 1537", STAC_DELL_M6_DMIC),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x02a0,
				"Dell Studio 17", STAC_DELL_M6_DMIC),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x02be,
				"Dell Studio 1555", STAC_DELL_M6_DMIC),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x02bd,
				"Dell Studio 1557", STAC_DELL_M6_DMIC),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x02fe,
				"Dell Studio XPS 1645", STAC_DELL_M6_DMIC),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0413,
				"Dell Studio 1558", STAC_DELL_M6_DMIC),
	/* codec SSID matching */
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x02a1,
		      "Alienware M17x", STAC_ALIENWARE_M17X),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x043a,
		      "Alienware M17x", STAC_ALIENWARE_M17X),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0490,
		      "Alienware M17x R3", STAC_DELL_EQ),
	SND_PCI_QUIRK(0x1059, 0x1011,
		      "ELO VuPoint 15MX", STAC_ELO_VUPOINT_15MX),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1927,
				"HP Z1 G2", STAC_92HD89XX_HP_Z1_G2_RIGHT_MIC_JACK),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x2b17,
				"unknown HP", STAC_92HD89XX_HP_FRONT_JACK),
	SND_PCI_QUIRK(PCI_VENDOR_ID_ASUSTEK, 0x83f8, "ASUS AT4NM10",
		      STAC_92HD73XX_ASUS_MOBO),
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl ref92hd83xxx_pin_configs[] = अणु
	अणु 0x0a, 0x02214030 पूर्ण,
	अणु 0x0b, 0x02211010 पूर्ण,
	अणु 0x0c, 0x02a19020 पूर्ण,
	अणु 0x0d, 0x02170130 पूर्ण,
	अणु 0x0e, 0x01014050 पूर्ण,
	अणु 0x0f, 0x01819040 पूर्ण,
	अणु 0x10, 0x01014020 पूर्ण,
	अणु 0x11, 0x90a3014e पूर्ण,
	अणु 0x1f, 0x01451160 पूर्ण,
	अणु 0x20, 0x98560170 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl dell_s14_pin_configs[] = अणु
	अणु 0x0a, 0x0221403f पूर्ण,
	अणु 0x0b, 0x0221101f पूर्ण,
	अणु 0x0c, 0x02a19020 पूर्ण,
	अणु 0x0d, 0x90170110 पूर्ण,
	अणु 0x0e, 0x40f000f0 पूर्ण,
	अणु 0x0f, 0x40f000f0 पूर्ण,
	अणु 0x10, 0x40f000f0 पूर्ण,
	अणु 0x11, 0x90a60160 पूर्ण,
	अणु 0x1f, 0x40f000f0 पूर्ण,
	अणु 0x20, 0x40f000f0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl dell_vostro_3500_pin_configs[] = अणु
	अणु 0x0a, 0x02a11020 पूर्ण,
	अणु 0x0b, 0x0221101f पूर्ण,
	अणु 0x0c, 0x400000f0 पूर्ण,
	अणु 0x0d, 0x90170110 पूर्ण,
	अणु 0x0e, 0x400000f1 पूर्ण,
	अणु 0x0f, 0x400000f2 पूर्ण,
	अणु 0x10, 0x400000f3 पूर्ण,
	अणु 0x11, 0x90a60160 पूर्ण,
	अणु 0x1f, 0x400000f4 पूर्ण,
	अणु 0x20, 0x400000f5 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl hp_dv7_4000_pin_configs[] = अणु
	अणु 0x0a, 0x03a12050 पूर्ण,
	अणु 0x0b, 0x0321201f पूर्ण,
	अणु 0x0c, 0x40f000f0 पूर्ण,
	अणु 0x0d, 0x90170110 पूर्ण,
	अणु 0x0e, 0x40f000f0 पूर्ण,
	अणु 0x0f, 0x40f000f0 पूर्ण,
	अणु 0x10, 0x90170110 पूर्ण,
	अणु 0x11, 0xd5a30140 पूर्ण,
	अणु 0x1f, 0x40f000f0 पूर्ण,
	अणु 0x20, 0x40f000f0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl hp_zephyr_pin_configs[] = अणु
	अणु 0x0a, 0x01813050 पूर्ण,
	अणु 0x0b, 0x0421201f पूर्ण,
	अणु 0x0c, 0x04a1205e पूर्ण,
	अणु 0x0d, 0x96130310 पूर्ण,
	अणु 0x0e, 0x96130310 पूर्ण,
	अणु 0x0f, 0x0101401f पूर्ण,
	अणु 0x10, 0x1111611f पूर्ण,
	अणु 0x11, 0xd5a30130 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl hp_cNB11_पूर्णांकquad_pin_configs[] = अणु
	अणु 0x0a, 0x40f000f0 पूर्ण,
	अणु 0x0b, 0x0221101f पूर्ण,
	अणु 0x0c, 0x02a11020 पूर्ण,
	अणु 0x0d, 0x92170110 पूर्ण,
	अणु 0x0e, 0x40f000f0 पूर्ण,
	अणु 0x0f, 0x92170110 पूर्ण,
	अणु 0x10, 0x40f000f0 पूर्ण,
	अणु 0x11, 0xd5a30130 पूर्ण,
	अणु 0x1f, 0x40f000f0 पूर्ण,
	अणु 0x20, 0x40f000f0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम stac92hd83xxx_fixup_hp(काष्ठा hda_codec *codec,
				   स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	अगर (hp_bnb2011_with_करोck(codec)) अणु
		snd_hda_codec_set_pincfg(codec, 0xa, 0x2101201f);
		snd_hda_codec_set_pincfg(codec, 0xf, 0x2181205e);
	पूर्ण

	अगर (find_mute_led_cfg(codec, spec->शेष_polarity))
		codec_dbg(codec, "mute LED gpio %d polarity %d\n",
				spec->gpio_led,
				spec->gpio_led_polarity);

	/* allow स्वतः-चयनing of करोck line-in */
	spec->gen.line_in_स्वतः_चयन = true;
पूर्ण

अटल व्योम stac92hd83xxx_fixup_hp_zephyr(काष्ठा hda_codec *codec,
				   स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	snd_hda_apply_pincfgs(codec, hp_zephyr_pin_configs);
	snd_hda_add_verbs(codec, stac92hd83xxx_hp_zephyr_init);
पूर्ण

अटल व्योम stac92hd83xxx_fixup_hp_led(काष्ठा hda_codec *codec,
				   स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE)
		spec->शेष_polarity = 0;
पूर्ण

अटल व्योम stac92hd83xxx_fixup_hp_inv_led(काष्ठा hda_codec *codec,
				   स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE)
		spec->शेष_polarity = 1;
पूर्ण

अटल व्योम stac92hd83xxx_fixup_hp_mic_led(काष्ठा hda_codec *codec,
				   स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		spec->mic_mute_led_gpio = 0x08; /* GPIO3 */
#अगर_घोषित CONFIG_PM
		/* resetting controller clears GPIO, so we need to keep on */
		codec->core.घातer_caps &= ~AC_PWRST_CLKSTOP;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल व्योम stac92hd83xxx_fixup_hp_led_gpio10(काष्ठा hda_codec *codec,
				   स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		spec->gpio_led = 0x10; /* GPIO4 */
		spec->शेष_polarity = 0;
	पूर्ण
पूर्ण

अटल व्योम stac92hd83xxx_fixup_headset_jack(काष्ठा hda_codec *codec,
				   स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE)
		spec->headset_jack = 1;
पूर्ण

अटल व्योम stac92hd83xxx_fixup_gpio10_eapd(काष्ठा hda_codec *codec,
					    स्थिर काष्ठा hda_fixup *fix,
					    पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;
	spec->eapd_mask = spec->gpio_mask = spec->gpio_dir =
		spec->gpio_data = 0x10;
	spec->eapd_चयन = 0;
पूर्ण

अटल व्योम hp_envy_ts_fixup_dac_bind(काष्ठा hda_codec *codec,
					    स्थिर काष्ठा hda_fixup *fix,
					    पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;
	अटल स्थिर hda_nid_t preferred_pairs[] = अणु
		0xd, 0x13,
		0
	पूर्ण;

	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	spec->gen.preferred_dacs = preferred_pairs;
पूर्ण

अटल स्थिर काष्ठा hda_verb hp_bnb13_eq_verbs[] = अणु
	/* 44.1KHz base */
	अणु 0x22, 0x7A6, 0x3E पूर्ण,
	अणु 0x22, 0x7A7, 0x68 पूर्ण,
	अणु 0x22, 0x7A8, 0x17 पूर्ण,
	अणु 0x22, 0x7A9, 0x3E पूर्ण,
	अणु 0x22, 0x7AA, 0x68 पूर्ण,
	अणु 0x22, 0x7AB, 0x17 पूर्ण,
	अणु 0x22, 0x7AC, 0x00 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x83 पूर्ण,
	अणु 0x22, 0x7A7, 0x2F पूर्ण,
	अणु 0x22, 0x7A8, 0xD1 पूर्ण,
	अणु 0x22, 0x7A9, 0x83 पूर्ण,
	अणु 0x22, 0x7AA, 0x2F पूर्ण,
	अणु 0x22, 0x7AB, 0xD1 पूर्ण,
	अणु 0x22, 0x7AC, 0x01 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x3E पूर्ण,
	अणु 0x22, 0x7A7, 0x68 पूर्ण,
	अणु 0x22, 0x7A8, 0x17 पूर्ण,
	अणु 0x22, 0x7A9, 0x3E पूर्ण,
	अणु 0x22, 0x7AA, 0x68 पूर्ण,
	अणु 0x22, 0x7AB, 0x17 पूर्ण,
	अणु 0x22, 0x7AC, 0x02 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x7C पूर्ण,
	अणु 0x22, 0x7A7, 0xC6 पूर्ण,
	अणु 0x22, 0x7A8, 0x0C पूर्ण,
	अणु 0x22, 0x7A9, 0x7C पूर्ण,
	अणु 0x22, 0x7AA, 0xC6 पूर्ण,
	अणु 0x22, 0x7AB, 0x0C पूर्ण,
	अणु 0x22, 0x7AC, 0x03 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0xC3 पूर्ण,
	अणु 0x22, 0x7A7, 0x25 पूर्ण,
	अणु 0x22, 0x7A8, 0xAF पूर्ण,
	अणु 0x22, 0x7A9, 0xC3 पूर्ण,
	अणु 0x22, 0x7AA, 0x25 पूर्ण,
	अणु 0x22, 0x7AB, 0xAF पूर्ण,
	अणु 0x22, 0x7AC, 0x04 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x3E पूर्ण,
	अणु 0x22, 0x7A7, 0x85 पूर्ण,
	अणु 0x22, 0x7A8, 0x73 पूर्ण,
	अणु 0x22, 0x7A9, 0x3E पूर्ण,
	अणु 0x22, 0x7AA, 0x85 पूर्ण,
	अणु 0x22, 0x7AB, 0x73 पूर्ण,
	अणु 0x22, 0x7AC, 0x05 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x85 पूर्ण,
	अणु 0x22, 0x7A7, 0x39 पूर्ण,
	अणु 0x22, 0x7A8, 0xC7 पूर्ण,
	अणु 0x22, 0x7A9, 0x85 पूर्ण,
	अणु 0x22, 0x7AA, 0x39 पूर्ण,
	अणु 0x22, 0x7AB, 0xC7 पूर्ण,
	अणु 0x22, 0x7AC, 0x06 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x3C पूर्ण,
	अणु 0x22, 0x7A7, 0x90 पूर्ण,
	अणु 0x22, 0x7A8, 0xB0 पूर्ण,
	अणु 0x22, 0x7A9, 0x3C पूर्ण,
	अणु 0x22, 0x7AA, 0x90 पूर्ण,
	अणु 0x22, 0x7AB, 0xB0 पूर्ण,
	अणु 0x22, 0x7AC, 0x07 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x7A पूर्ण,
	अणु 0x22, 0x7A7, 0xC6 पूर्ण,
	अणु 0x22, 0x7A8, 0x39 पूर्ण,
	अणु 0x22, 0x7A9, 0x7A पूर्ण,
	अणु 0x22, 0x7AA, 0xC6 पूर्ण,
	अणु 0x22, 0x7AB, 0x39 पूर्ण,
	अणु 0x22, 0x7AC, 0x08 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0xC4 पूर्ण,
	अणु 0x22, 0x7A7, 0xE9 पूर्ण,
	अणु 0x22, 0x7A8, 0xDC पूर्ण,
	अणु 0x22, 0x7A9, 0xC4 पूर्ण,
	अणु 0x22, 0x7AA, 0xE9 पूर्ण,
	अणु 0x22, 0x7AB, 0xDC पूर्ण,
	अणु 0x22, 0x7AC, 0x09 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x3D पूर्ण,
	अणु 0x22, 0x7A7, 0xE1 पूर्ण,
	अणु 0x22, 0x7A8, 0x0D पूर्ण,
	अणु 0x22, 0x7A9, 0x3D पूर्ण,
	अणु 0x22, 0x7AA, 0xE1 पूर्ण,
	अणु 0x22, 0x7AB, 0x0D पूर्ण,
	अणु 0x22, 0x7AC, 0x0A पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x89 पूर्ण,
	अणु 0x22, 0x7A7, 0xB6 पूर्ण,
	अणु 0x22, 0x7A8, 0xEB पूर्ण,
	अणु 0x22, 0x7A9, 0x89 पूर्ण,
	अणु 0x22, 0x7AA, 0xB6 पूर्ण,
	अणु 0x22, 0x7AB, 0xEB पूर्ण,
	अणु 0x22, 0x7AC, 0x0B पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x39 पूर्ण,
	अणु 0x22, 0x7A7, 0x9D पूर्ण,
	अणु 0x22, 0x7A8, 0xFE पूर्ण,
	अणु 0x22, 0x7A9, 0x39 पूर्ण,
	अणु 0x22, 0x7AA, 0x9D पूर्ण,
	अणु 0x22, 0x7AB, 0xFE पूर्ण,
	अणु 0x22, 0x7AC, 0x0C पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x76 पूर्ण,
	अणु 0x22, 0x7A7, 0x49 पूर्ण,
	अणु 0x22, 0x7A8, 0x15 पूर्ण,
	अणु 0x22, 0x7A9, 0x76 पूर्ण,
	अणु 0x22, 0x7AA, 0x49 पूर्ण,
	अणु 0x22, 0x7AB, 0x15 पूर्ण,
	अणु 0x22, 0x7AC, 0x0D पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0xC8 पूर्ण,
	अणु 0x22, 0x7A7, 0x80 पूर्ण,
	अणु 0x22, 0x7A8, 0xF5 पूर्ण,
	अणु 0x22, 0x7A9, 0xC8 पूर्ण,
	अणु 0x22, 0x7AA, 0x80 पूर्ण,
	अणु 0x22, 0x7AB, 0xF5 पूर्ण,
	अणु 0x22, 0x7AC, 0x0E पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x40 पूर्ण,
	अणु 0x22, 0x7A7, 0x00 पूर्ण,
	अणु 0x22, 0x7A8, 0x00 पूर्ण,
	अणु 0x22, 0x7A9, 0x40 पूर्ण,
	अणु 0x22, 0x7AA, 0x00 पूर्ण,
	अणु 0x22, 0x7AB, 0x00 पूर्ण,
	अणु 0x22, 0x7AC, 0x0F पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x90 पूर्ण,
	अणु 0x22, 0x7A7, 0x68 पूर्ण,
	अणु 0x22, 0x7A8, 0xF1 पूर्ण,
	अणु 0x22, 0x7A9, 0x90 पूर्ण,
	अणु 0x22, 0x7AA, 0x68 पूर्ण,
	अणु 0x22, 0x7AB, 0xF1 पूर्ण,
	अणु 0x22, 0x7AC, 0x10 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x34 पूर्ण,
	अणु 0x22, 0x7A7, 0x47 पूर्ण,
	अणु 0x22, 0x7A8, 0x6C पूर्ण,
	अणु 0x22, 0x7A9, 0x34 पूर्ण,
	अणु 0x22, 0x7AA, 0x47 पूर्ण,
	अणु 0x22, 0x7AB, 0x6C पूर्ण,
	अणु 0x22, 0x7AC, 0x11 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x6F पूर्ण,
	अणु 0x22, 0x7A7, 0x97 पूर्ण,
	अणु 0x22, 0x7A8, 0x0F पूर्ण,
	अणु 0x22, 0x7A9, 0x6F पूर्ण,
	अणु 0x22, 0x7AA, 0x97 पूर्ण,
	अणु 0x22, 0x7AB, 0x0F पूर्ण,
	अणु 0x22, 0x7AC, 0x12 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0xCB पूर्ण,
	अणु 0x22, 0x7A7, 0xB8 पूर्ण,
	अणु 0x22, 0x7A8, 0x94 पूर्ण,
	अणु 0x22, 0x7A9, 0xCB पूर्ण,
	अणु 0x22, 0x7AA, 0xB8 पूर्ण,
	अणु 0x22, 0x7AB, 0x94 पूर्ण,
	अणु 0x22, 0x7AC, 0x13 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x40 पूर्ण,
	अणु 0x22, 0x7A7, 0x00 पूर्ण,
	अणु 0x22, 0x7A8, 0x00 पूर्ण,
	अणु 0x22, 0x7A9, 0x40 पूर्ण,
	अणु 0x22, 0x7AA, 0x00 पूर्ण,
	अणु 0x22, 0x7AB, 0x00 पूर्ण,
	अणु 0x22, 0x7AC, 0x14 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x95 पूर्ण,
	अणु 0x22, 0x7A7, 0x76 पूर्ण,
	अणु 0x22, 0x7A8, 0x5B पूर्ण,
	अणु 0x22, 0x7A9, 0x95 पूर्ण,
	अणु 0x22, 0x7AA, 0x76 पूर्ण,
	अणु 0x22, 0x7AB, 0x5B पूर्ण,
	अणु 0x22, 0x7AC, 0x15 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x31 पूर्ण,
	अणु 0x22, 0x7A7, 0xAC पूर्ण,
	अणु 0x22, 0x7A8, 0x31 पूर्ण,
	अणु 0x22, 0x7A9, 0x31 पूर्ण,
	अणु 0x22, 0x7AA, 0xAC पूर्ण,
	अणु 0x22, 0x7AB, 0x31 पूर्ण,
	अणु 0x22, 0x7AC, 0x16 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x6A पूर्ण,
	अणु 0x22, 0x7A7, 0x89 पूर्ण,
	अणु 0x22, 0x7A8, 0xA5 पूर्ण,
	अणु 0x22, 0x7A9, 0x6A पूर्ण,
	अणु 0x22, 0x7AA, 0x89 पूर्ण,
	अणु 0x22, 0x7AB, 0xA5 पूर्ण,
	अणु 0x22, 0x7AC, 0x17 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0xCE पूर्ण,
	अणु 0x22, 0x7A7, 0x53 पूर्ण,
	अणु 0x22, 0x7A8, 0xCF पूर्ण,
	अणु 0x22, 0x7A9, 0xCE पूर्ण,
	अणु 0x22, 0x7AA, 0x53 पूर्ण,
	अणु 0x22, 0x7AB, 0xCF पूर्ण,
	अणु 0x22, 0x7AC, 0x18 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x40 पूर्ण,
	अणु 0x22, 0x7A7, 0x00 पूर्ण,
	अणु 0x22, 0x7A8, 0x00 पूर्ण,
	अणु 0x22, 0x7A9, 0x40 पूर्ण,
	अणु 0x22, 0x7AA, 0x00 पूर्ण,
	अणु 0x22, 0x7AB, 0x00 पूर्ण,
	अणु 0x22, 0x7AC, 0x19 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	/* 48KHz base */
	अणु 0x22, 0x7A6, 0x3E पूर्ण,
	अणु 0x22, 0x7A7, 0x88 पूर्ण,
	अणु 0x22, 0x7A8, 0xDC पूर्ण,
	अणु 0x22, 0x7A9, 0x3E पूर्ण,
	अणु 0x22, 0x7AA, 0x88 पूर्ण,
	अणु 0x22, 0x7AB, 0xDC पूर्ण,
	अणु 0x22, 0x7AC, 0x1A पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x82 पूर्ण,
	अणु 0x22, 0x7A7, 0xEE पूर्ण,
	अणु 0x22, 0x7A8, 0x46 पूर्ण,
	अणु 0x22, 0x7A9, 0x82 पूर्ण,
	अणु 0x22, 0x7AA, 0xEE पूर्ण,
	अणु 0x22, 0x7AB, 0x46 पूर्ण,
	अणु 0x22, 0x7AC, 0x1B पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x3E पूर्ण,
	अणु 0x22, 0x7A7, 0x88 पूर्ण,
	अणु 0x22, 0x7A8, 0xDC पूर्ण,
	अणु 0x22, 0x7A9, 0x3E पूर्ण,
	अणु 0x22, 0x7AA, 0x88 पूर्ण,
	अणु 0x22, 0x7AB, 0xDC पूर्ण,
	अणु 0x22, 0x7AC, 0x1C पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x7D पूर्ण,
	अणु 0x22, 0x7A7, 0x09 पूर्ण,
	अणु 0x22, 0x7A8, 0x28 पूर्ण,
	अणु 0x22, 0x7A9, 0x7D पूर्ण,
	अणु 0x22, 0x7AA, 0x09 पूर्ण,
	अणु 0x22, 0x7AB, 0x28 पूर्ण,
	अणु 0x22, 0x7AC, 0x1D पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0xC2 पूर्ण,
	अणु 0x22, 0x7A7, 0xE5 पूर्ण,
	अणु 0x22, 0x7A8, 0xB4 पूर्ण,
	अणु 0x22, 0x7A9, 0xC2 पूर्ण,
	अणु 0x22, 0x7AA, 0xE5 पूर्ण,
	अणु 0x22, 0x7AB, 0xB4 पूर्ण,
	अणु 0x22, 0x7AC, 0x1E पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x3E पूर्ण,
	अणु 0x22, 0x7A7, 0xA3 पूर्ण,
	अणु 0x22, 0x7A8, 0x1F पूर्ण,
	अणु 0x22, 0x7A9, 0x3E पूर्ण,
	अणु 0x22, 0x7AA, 0xA3 पूर्ण,
	अणु 0x22, 0x7AB, 0x1F पूर्ण,
	अणु 0x22, 0x7AC, 0x1F पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x84 पूर्ण,
	अणु 0x22, 0x7A7, 0xCA पूर्ण,
	अणु 0x22, 0x7A8, 0xF1 पूर्ण,
	अणु 0x22, 0x7A9, 0x84 पूर्ण,
	अणु 0x22, 0x7AA, 0xCA पूर्ण,
	अणु 0x22, 0x7AB, 0xF1 पूर्ण,
	अणु 0x22, 0x7AC, 0x20 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x3C पूर्ण,
	अणु 0x22, 0x7A7, 0xD5 पूर्ण,
	अणु 0x22, 0x7A8, 0x9C पूर्ण,
	अणु 0x22, 0x7A9, 0x3C पूर्ण,
	अणु 0x22, 0x7AA, 0xD5 पूर्ण,
	अणु 0x22, 0x7AB, 0x9C पूर्ण,
	अणु 0x22, 0x7AC, 0x21 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x7B पूर्ण,
	अणु 0x22, 0x7A7, 0x35 पूर्ण,
	अणु 0x22, 0x7A8, 0x0F पूर्ण,
	अणु 0x22, 0x7A9, 0x7B पूर्ण,
	अणु 0x22, 0x7AA, 0x35 पूर्ण,
	अणु 0x22, 0x7AB, 0x0F पूर्ण,
	अणु 0x22, 0x7AC, 0x22 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0xC4 पूर्ण,
	अणु 0x22, 0x7A7, 0x87 पूर्ण,
	अणु 0x22, 0x7A8, 0x45 पूर्ण,
	अणु 0x22, 0x7A9, 0xC4 पूर्ण,
	अणु 0x22, 0x7AA, 0x87 पूर्ण,
	अणु 0x22, 0x7AB, 0x45 पूर्ण,
	अणु 0x22, 0x7AC, 0x23 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x3E पूर्ण,
	अणु 0x22, 0x7A7, 0x0A पूर्ण,
	अणु 0x22, 0x7A8, 0x78 पूर्ण,
	अणु 0x22, 0x7A9, 0x3E पूर्ण,
	अणु 0x22, 0x7AA, 0x0A पूर्ण,
	अणु 0x22, 0x7AB, 0x78 पूर्ण,
	अणु 0x22, 0x7AC, 0x24 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x88 पूर्ण,
	अणु 0x22, 0x7A7, 0xE2 पूर्ण,
	अणु 0x22, 0x7A8, 0x05 पूर्ण,
	अणु 0x22, 0x7A9, 0x88 पूर्ण,
	अणु 0x22, 0x7AA, 0xE2 पूर्ण,
	अणु 0x22, 0x7AB, 0x05 पूर्ण,
	अणु 0x22, 0x7AC, 0x25 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x3A पूर्ण,
	अणु 0x22, 0x7A7, 0x1A पूर्ण,
	अणु 0x22, 0x7A8, 0xA3 पूर्ण,
	अणु 0x22, 0x7A9, 0x3A पूर्ण,
	अणु 0x22, 0x7AA, 0x1A पूर्ण,
	अणु 0x22, 0x7AB, 0xA3 पूर्ण,
	अणु 0x22, 0x7AC, 0x26 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x77 पूर्ण,
	अणु 0x22, 0x7A7, 0x1D पूर्ण,
	अणु 0x22, 0x7A8, 0xFB पूर्ण,
	अणु 0x22, 0x7A9, 0x77 पूर्ण,
	अणु 0x22, 0x7AA, 0x1D पूर्ण,
	अणु 0x22, 0x7AB, 0xFB पूर्ण,
	अणु 0x22, 0x7AC, 0x27 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0xC7 पूर्ण,
	अणु 0x22, 0x7A7, 0xDA पूर्ण,
	अणु 0x22, 0x7A8, 0xE5 पूर्ण,
	अणु 0x22, 0x7A9, 0xC7 पूर्ण,
	अणु 0x22, 0x7AA, 0xDA पूर्ण,
	अणु 0x22, 0x7AB, 0xE5 पूर्ण,
	अणु 0x22, 0x7AC, 0x28 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x40 पूर्ण,
	अणु 0x22, 0x7A7, 0x00 पूर्ण,
	अणु 0x22, 0x7A8, 0x00 पूर्ण,
	अणु 0x22, 0x7A9, 0x40 पूर्ण,
	अणु 0x22, 0x7AA, 0x00 पूर्ण,
	अणु 0x22, 0x7AB, 0x00 पूर्ण,
	अणु 0x22, 0x7AC, 0x29 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x8E पूर्ण,
	अणु 0x22, 0x7A7, 0xD7 पूर्ण,
	अणु 0x22, 0x7A8, 0x22 पूर्ण,
	अणु 0x22, 0x7A9, 0x8E पूर्ण,
	अणु 0x22, 0x7AA, 0xD7 पूर्ण,
	अणु 0x22, 0x7AB, 0x22 पूर्ण,
	अणु 0x22, 0x7AC, 0x2A पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x35 पूर्ण,
	अणु 0x22, 0x7A7, 0x26 पूर्ण,
	अणु 0x22, 0x7A8, 0xC6 पूर्ण,
	अणु 0x22, 0x7A9, 0x35 पूर्ण,
	अणु 0x22, 0x7AA, 0x26 पूर्ण,
	अणु 0x22, 0x7AB, 0xC6 पूर्ण,
	अणु 0x22, 0x7AC, 0x2B पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x71 पूर्ण,
	अणु 0x22, 0x7A7, 0x28 पूर्ण,
	अणु 0x22, 0x7A8, 0xDE पूर्ण,
	अणु 0x22, 0x7A9, 0x71 पूर्ण,
	अणु 0x22, 0x7AA, 0x28 पूर्ण,
	अणु 0x22, 0x7AB, 0xDE पूर्ण,
	अणु 0x22, 0x7AC, 0x2C पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0xCA पूर्ण,
	अणु 0x22, 0x7A7, 0xD9 पूर्ण,
	अणु 0x22, 0x7A8, 0x3A पूर्ण,
	अणु 0x22, 0x7A9, 0xCA पूर्ण,
	अणु 0x22, 0x7AA, 0xD9 पूर्ण,
	अणु 0x22, 0x7AB, 0x3A पूर्ण,
	अणु 0x22, 0x7AC, 0x2D पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x40 पूर्ण,
	अणु 0x22, 0x7A7, 0x00 पूर्ण,
	अणु 0x22, 0x7A8, 0x00 पूर्ण,
	अणु 0x22, 0x7A9, 0x40 पूर्ण,
	अणु 0x22, 0x7AA, 0x00 पूर्ण,
	अणु 0x22, 0x7AB, 0x00 पूर्ण,
	अणु 0x22, 0x7AC, 0x2E पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x93 पूर्ण,
	अणु 0x22, 0x7A7, 0x5E पूर्ण,
	अणु 0x22, 0x7A8, 0xD8 पूर्ण,
	अणु 0x22, 0x7A9, 0x93 पूर्ण,
	अणु 0x22, 0x7AA, 0x5E पूर्ण,
	अणु 0x22, 0x7AB, 0xD8 पूर्ण,
	अणु 0x22, 0x7AC, 0x2F पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x32 पूर्ण,
	अणु 0x22, 0x7A7, 0xB7 पूर्ण,
	अणु 0x22, 0x7A8, 0xB1 पूर्ण,
	अणु 0x22, 0x7A9, 0x32 पूर्ण,
	अणु 0x22, 0x7AA, 0xB7 पूर्ण,
	अणु 0x22, 0x7AB, 0xB1 पूर्ण,
	अणु 0x22, 0x7AC, 0x30 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x6C पूर्ण,
	अणु 0x22, 0x7A7, 0xA1 पूर्ण,
	अणु 0x22, 0x7A8, 0x28 पूर्ण,
	अणु 0x22, 0x7A9, 0x6C पूर्ण,
	अणु 0x22, 0x7AA, 0xA1 पूर्ण,
	अणु 0x22, 0x7AB, 0x28 पूर्ण,
	अणु 0x22, 0x7AC, 0x31 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0xCD पूर्ण,
	अणु 0x22, 0x7A7, 0x48 पूर्ण,
	अणु 0x22, 0x7A8, 0x4F पूर्ण,
	अणु 0x22, 0x7A9, 0xCD पूर्ण,
	अणु 0x22, 0x7AA, 0x48 पूर्ण,
	अणु 0x22, 0x7AB, 0x4F पूर्ण,
	अणु 0x22, 0x7AC, 0x32 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	अणु 0x22, 0x7A6, 0x40 पूर्ण,
	अणु 0x22, 0x7A7, 0x00 पूर्ण,
	अणु 0x22, 0x7A8, 0x00 पूर्ण,
	अणु 0x22, 0x7A9, 0x40 पूर्ण,
	अणु 0x22, 0x7AA, 0x00 पूर्ण,
	अणु 0x22, 0x7AB, 0x00 पूर्ण,
	अणु 0x22, 0x7AC, 0x33 पूर्ण,
	अणु 0x22, 0x7AD, 0x80 पूर्ण,
	/* common */
	अणु 0x22, 0x782, 0xC1 पूर्ण,
	अणु 0x22, 0x771, 0x2C पूर्ण,
	अणु 0x22, 0x772, 0x2C पूर्ण,
	अणु 0x22, 0x788, 0x04 पूर्ण,
	अणु 0x01, 0x7B0, 0x08 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_fixup stac92hd83xxx_fixups[] = अणु
	[STAC_92HD83XXX_REF] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = ref92hd83xxx_pin_configs,
	पूर्ण,
	[STAC_92HD83XXX_PWR_REF] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = ref92hd83xxx_pin_configs,
	पूर्ण,
	[STAC_DELL_S14] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell_s14_pin_configs,
	पूर्ण,
	[STAC_DELL_VOSTRO_3500] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell_vostro_3500_pin_configs,
	पूर्ण,
	[STAC_92HD83XXX_HP_cNB11_INTQUAD] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = hp_cNB11_पूर्णांकquad_pin_configs,
		.chained = true,
		.chain_id = STAC_92HD83XXX_HP,
	पूर्ण,
	[STAC_92HD83XXX_HP] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd83xxx_fixup_hp,
	पूर्ण,
	[STAC_HP_DV7_4000] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = hp_dv7_4000_pin_configs,
		.chained = true,
		.chain_id = STAC_92HD83XXX_HP,
	पूर्ण,
	[STAC_HP_ZEPHYR] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd83xxx_fixup_hp_zephyr,
		.chained = true,
		.chain_id = STAC_92HD83XXX_HP,
	पूर्ण,
	[STAC_92HD83XXX_HP_LED] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd83xxx_fixup_hp_led,
		.chained = true,
		.chain_id = STAC_92HD83XXX_HP,
	पूर्ण,
	[STAC_92HD83XXX_HP_INV_LED] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd83xxx_fixup_hp_inv_led,
		.chained = true,
		.chain_id = STAC_92HD83XXX_HP,
	पूर्ण,
	[STAC_92HD83XXX_HP_MIC_LED] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd83xxx_fixup_hp_mic_led,
		.chained = true,
		.chain_id = STAC_92HD83XXX_HP,
	पूर्ण,
	[STAC_HP_LED_GPIO10] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd83xxx_fixup_hp_led_gpio10,
		.chained = true,
		.chain_id = STAC_92HD83XXX_HP,
	पूर्ण,
	[STAC_92HD83XXX_HEADSET_JACK] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd83xxx_fixup_headset_jack,
	पूर्ण,
	[STAC_HP_ENVY_BASS] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			अणु 0x0f, 0x90170111 पूर्ण,
			अणुपूर्ण
		पूर्ण,
	पूर्ण,
	[STAC_HP_BNB13_EQ] = अणु
		.type = HDA_FIXUP_VERBS,
		.v.verbs = hp_bnb13_eq_verbs,
		.chained = true,
		.chain_id = STAC_92HD83XXX_HP_MIC_LED,
	पूर्ण,
	[STAC_HP_ENVY_TS_BASS] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			अणु 0x10, 0x92170111 पूर्ण,
			अणुपूर्ण
		पूर्ण,
	पूर्ण,
	[STAC_HP_ENVY_TS_DAC_BIND] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = hp_envy_ts_fixup_dac_bind,
		.chained = true,
		.chain_id = STAC_HP_ENVY_TS_BASS,
	पूर्ण,
	[STAC_92HD83XXX_GPIO10_EAPD] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd83xxx_fixup_gpio10_eapd,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_model_fixup stac92hd83xxx_models[] = अणु
	अणु .id = STAC_92HD83XXX_REF, .name = "ref" पूर्ण,
	अणु .id = STAC_92HD83XXX_PWR_REF, .name = "mic-ref" पूर्ण,
	अणु .id = STAC_DELL_S14, .name = "dell-s14" पूर्ण,
	अणु .id = STAC_DELL_VOSTRO_3500, .name = "dell-vostro-3500" पूर्ण,
	अणु .id = STAC_92HD83XXX_HP_cNB11_INTQUAD, .name = "hp_cNB11_intquad" पूर्ण,
	अणु .id = STAC_HP_DV7_4000, .name = "hp-dv7-4000" पूर्ण,
	अणु .id = STAC_HP_ZEPHYR, .name = "hp-zephyr" पूर्ण,
	अणु .id = STAC_92HD83XXX_HP_LED, .name = "hp-led" पूर्ण,
	अणु .id = STAC_92HD83XXX_HP_INV_LED, .name = "hp-inv-led" पूर्ण,
	अणु .id = STAC_92HD83XXX_HP_MIC_LED, .name = "hp-mic-led" पूर्ण,
	अणु .id = STAC_92HD83XXX_HEADSET_JACK, .name = "headset-jack" पूर्ण,
	अणु .id = STAC_HP_ENVY_BASS, .name = "hp-envy-bass" पूर्ण,
	अणु .id = STAC_HP_BNB13_EQ, .name = "hp-bnb13-eq" पूर्ण,
	अणु .id = STAC_HP_ENVY_TS_BASS, .name = "hp-envy-ts-bass" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk stac92hd83xxx_fixup_tbl[] = अणु
	/* SigmaTel reference board */
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x2668,
		      "DFI LanParty", STAC_92HD83XXX_REF),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DFI, 0x3101,
		      "DFI LanParty", STAC_92HD83XXX_REF),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x02ba,
		      "unknown Dell", STAC_DELL_S14),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0532,
		      "Dell Latitude E6230", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0533,
		      "Dell Latitude E6330", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0534,
		      "Dell Latitude E6430", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0535,
		      "Dell Latitude E6530", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x053c,
		      "Dell Latitude E5430", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x053d,
		      "Dell Latitude E5530", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0549,
		      "Dell Latitude E5430", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x057d,
		      "Dell Latitude E6430s", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0584,
		      "Dell Latitude E6430U", STAC_92HD83XXX_HEADSET_JACK),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x1028,
		      "Dell Vostro 3500", STAC_DELL_VOSTRO_3500),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1656,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1657,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1658,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1659,
			  "HP Pavilion dv7", STAC_HP_DV7_4000),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x165A,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x165B,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1888,
			  "HP Envy Spectre", STAC_HP_ENVY_BASS),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1899,
			  "HP Folio 13", STAC_HP_LED_GPIO10),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x18df,
			  "HP Folio", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x18F8,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1909,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x190A,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x190e,
			  "HP ENVY TS", STAC_HP_ENVY_TS_BASS),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1967,
			  "HP ENVY TS", STAC_HP_ENVY_TS_DAC_BIND),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1940,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1941,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1942,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1943,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1944,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1945,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1946,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1948,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1949,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x194A,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x194B,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x194C,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x194E,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x194F,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1950,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1951,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x195A,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x195B,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x195C,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1991,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x2103,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x2104,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x2105,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x2106,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x2107,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x2108,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x2109,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x210A,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x210B,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x211C,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x211D,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x211E,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x211F,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x2120,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x2121,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x2122,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x2123,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x213E,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x213F,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x2140,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x21B2,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x21B3,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x21B5,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x21B6,
			  "HP bNB13", STAC_HP_BNB13_EQ),
	SND_PCI_QUIRK_MASK(PCI_VENDOR_ID_HP, 0xff00, 0x1900,
			  "HP", STAC_92HD83XXX_HP_MIC_LED),
	SND_PCI_QUIRK_MASK(PCI_VENDOR_ID_HP, 0xff00, 0x2000,
			  "HP", STAC_92HD83XXX_HP_MIC_LED),
	SND_PCI_QUIRK_MASK(PCI_VENDOR_ID_HP, 0xff00, 0x2100,
			  "HP", STAC_92HD83XXX_HP_MIC_LED),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x3388,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x3389,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x355B,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x355C,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x355D,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x355E,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x355F,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x3560,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x358B,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x358C,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x358D,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x3591,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x3592,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x3593,
			  "HP", STAC_92HD83XXX_HP_cNB11_INTQUAD),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x3561,
			  "HP", STAC_HP_ZEPHYR),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x3660,
			  "HP Mini", STAC_92HD83XXX_HP_LED),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x144E,
			  "HP Pavilion dv5", STAC_92HD83XXX_HP_INV_LED),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x148a,
		      "HP Mini", STAC_92HD83XXX_HP_LED),
	SND_PCI_QUIRK_VENDOR(PCI_VENDOR_ID_HP, "HP", STAC_92HD83XXX_HP),
	/* match both क्रम 0xfa91 and 0xfa93 */
	SND_PCI_QUIRK_MASK(PCI_VENDOR_ID_TOSHIBA, 0xfffd, 0xfa91,
		      "Toshiba Satellite S50D", STAC_92HD83XXX_GPIO10_EAPD),
	अणुपूर्ण /* terminator */
पूर्ण;

/* HP dv7 bass चयन - GPIO5 */
#घोषणा stac_hp_bass_gpio_info	snd_ctl_boolean_mono_info
अटल पूर्णांक stac_hp_bass_gpio_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा sigmatel_spec *spec = codec->spec;
	ucontrol->value.पूर्णांकeger.value[0] = !!(spec->gpio_data & 0x20);
	वापस 0;
पूर्ण

अटल पूर्णांक stac_hp_bass_gpio_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा sigmatel_spec *spec = codec->spec;
	अचिन्हित पूर्णांक gpio_data;

	gpio_data = (spec->gpio_data & ~0x20) |
		(ucontrol->value.पूर्णांकeger.value[0] ? 0x20 : 0);
	अगर (gpio_data == spec->gpio_data)
		वापस 0;
	spec->gpio_data = gpio_data;
	stac_gpio_set(codec, spec->gpio_mask, spec->gpio_dir, spec->gpio_data);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new stac_hp_bass_sw_ctrl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.info = stac_hp_bass_gpio_info,
	.get = stac_hp_bass_gpio_get,
	.put = stac_hp_bass_gpio_put,
पूर्ण;

अटल पूर्णांक stac_add_hp_bass_चयन(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (!snd_hda_gen_add_kctl(&spec->gen, "Bass Speaker Playback Switch",
				  &stac_hp_bass_sw_ctrl))
		वापस -ENOMEM;

	spec->gpio_mask |= 0x20;
	spec->gpio_dir |= 0x20;
	spec->gpio_data |= 0x20;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hda_pपूर्णांकbl ref92hd71bxx_pin_configs[] = अणु
	अणु 0x0a, 0x02214030 पूर्ण,
	अणु 0x0b, 0x02a19040 पूर्ण,
	अणु 0x0c, 0x01a19020 पूर्ण,
	अणु 0x0d, 0x01014010 पूर्ण,
	अणु 0x0e, 0x0181302e पूर्ण,
	अणु 0x0f, 0x01014010 पूर्ण,
	अणु 0x14, 0x01019020 पूर्ण,
	अणु 0x18, 0x90a000f0 पूर्ण,
	अणु 0x19, 0x90a000f0 पूर्ण,
	अणु 0x1e, 0x01452050 पूर्ण,
	अणु 0x1f, 0x01452050 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl dell_m4_1_pin_configs[] = अणु
	अणु 0x0a, 0x0421101f पूर्ण,
	अणु 0x0b, 0x04a11221 पूर्ण,
	अणु 0x0c, 0x40f000f0 पूर्ण,
	अणु 0x0d, 0x90170110 पूर्ण,
	अणु 0x0e, 0x23a1902e पूर्ण,
	अणु 0x0f, 0x23014250 पूर्ण,
	अणु 0x14, 0x40f000f0 पूर्ण,
	अणु 0x18, 0x90a000f0 पूर्ण,
	अणु 0x19, 0x40f000f0 पूर्ण,
	अणु 0x1e, 0x4f0000f0 पूर्ण,
	अणु 0x1f, 0x4f0000f0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl dell_m4_2_pin_configs[] = अणु
	अणु 0x0a, 0x0421101f पूर्ण,
	अणु 0x0b, 0x04a11221 पूर्ण,
	अणु 0x0c, 0x90a70330 पूर्ण,
	अणु 0x0d, 0x90170110 पूर्ण,
	अणु 0x0e, 0x23a1902e पूर्ण,
	अणु 0x0f, 0x23014250 पूर्ण,
	अणु 0x14, 0x40f000f0 पूर्ण,
	अणु 0x18, 0x40f000f0 पूर्ण,
	अणु 0x19, 0x40f000f0 पूर्ण,
	अणु 0x1e, 0x044413b0 पूर्ण,
	अणु 0x1f, 0x044413b0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl dell_m4_3_pin_configs[] = अणु
	अणु 0x0a, 0x0421101f पूर्ण,
	अणु 0x0b, 0x04a11221 पूर्ण,
	अणु 0x0c, 0x90a70330 पूर्ण,
	अणु 0x0d, 0x90170110 पूर्ण,
	अणु 0x0e, 0x40f000f0 पूर्ण,
	अणु 0x0f, 0x40f000f0 पूर्ण,
	अणु 0x14, 0x40f000f0 पूर्ण,
	अणु 0x18, 0x90a000f0 पूर्ण,
	अणु 0x19, 0x40f000f0 पूर्ण,
	अणु 0x1e, 0x044413b0 पूर्ण,
	अणु 0x1f, 0x044413b0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम stac92hd71bxx_fixup_ref(काष्ठा hda_codec *codec,
				    स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	snd_hda_apply_pincfgs(codec, ref92hd71bxx_pin_configs);
	spec->gpio_mask = spec->gpio_dir = spec->gpio_data = 0;
पूर्ण

अटल व्योम stac92hd71bxx_fixup_hp_m4(काष्ठा hda_codec *codec,
				      स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;
	काष्ठा hda_jack_callback *jack;

	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	/* Enable VREF घातer saving on GPIO1 detect */
	snd_hda_codec_ग_लिखो_cache(codec, codec->core.afg, 0,
				  AC_VERB_SET_GPIO_UNSOLICITED_RSP_MASK, 0x02);
	jack = snd_hda_jack_detect_enable_callback(codec, codec->core.afg,
						   stac_vref_event);
	अगर (!IS_ERR(jack))
		jack->निजी_data = 0x02;

	spec->gpio_mask |= 0x02;

	/* enable पूर्णांकernal microphone */
	snd_hda_codec_set_pincfg(codec, 0x0e, 0x01813040);
पूर्ण

अटल व्योम stac92hd71bxx_fixup_hp_dv4(काष्ठा hda_codec *codec,
				       स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;
	spec->gpio_led = 0x01;
पूर्ण

अटल व्योम stac92hd71bxx_fixup_hp_dv5(काष्ठा hda_codec *codec,
				       स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	अचिन्हित पूर्णांक cap;

	चयन (action) अणु
	हाल HDA_FIXUP_ACT_PRE_PROBE:
		snd_hda_codec_set_pincfg(codec, 0x0d, 0x90170010);
		अवरोध;

	हाल HDA_FIXUP_ACT_PROBE:
		/* enable bass on HP dv7 */
		cap = snd_hda_param_पढ़ो(codec, 0x1, AC_PAR_GPIO_CAP);
		cap &= AC_GPIO_IO_COUNT;
		अगर (cap >= 6)
			stac_add_hp_bass_चयन(codec);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम stac92hd71bxx_fixup_hp_hdx(काष्ठा hda_codec *codec,
				       स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;
	spec->gpio_led = 0x08;
पूर्ण

अटल bool is_hp_output(काष्ठा hda_codec *codec, hda_nid_t pin)
अणु
	अचिन्हित पूर्णांक pin_cfg = snd_hda_codec_get_pincfg(codec, pin);

	/* count line-out, too, as BIOS sets often so */
	वापस get_defcfg_connect(pin_cfg) != AC_JACK_PORT_NONE &&
		(get_defcfg_device(pin_cfg) == AC_JACK_LINE_OUT ||
		 get_defcfg_device(pin_cfg) == AC_JACK_HP_OUT);
पूर्ण

अटल व्योम fixup_hp_headphone(काष्ठा hda_codec *codec, hda_nid_t pin)
अणु
	अचिन्हित पूर्णांक pin_cfg = snd_hda_codec_get_pincfg(codec, pin);

	/* It was changed in the BIOS to just satisfy MS DTM.
	 * Lets turn it back पूर्णांकo follower HP
	 */
	pin_cfg = (pin_cfg & (~AC_DEFCFG_DEVICE)) |
		(AC_JACK_HP_OUT << AC_DEFCFG_DEVICE_SHIFT);
	pin_cfg = (pin_cfg & (~(AC_DEFCFG_DEF_ASSOC | AC_DEFCFG_SEQUENCE))) |
		0x1f;
	snd_hda_codec_set_pincfg(codec, pin, pin_cfg);
पूर्ण

अटल व्योम stac92hd71bxx_fixup_hp(काष्ठा hda_codec *codec,
				   स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	/* when both output A and F are asचिन्हित, these are supposedly
	 * करोck and built-in headphones; fix both pin configs
	 */
	अगर (is_hp_output(codec, 0x0a) && is_hp_output(codec, 0x0f)) अणु
		fixup_hp_headphone(codec, 0x0a);
		fixup_hp_headphone(codec, 0x0f);
	पूर्ण

	अगर (find_mute_led_cfg(codec, 1))
		codec_dbg(codec, "mute LED gpio %d polarity %d\n",
				spec->gpio_led,
				spec->gpio_led_polarity);

पूर्ण

अटल स्थिर काष्ठा hda_fixup stac92hd71bxx_fixups[] = अणु
	[STAC_92HD71BXX_REF] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd71bxx_fixup_ref,
	पूर्ण,
	[STAC_DELL_M4_1] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell_m4_1_pin_configs,
	पूर्ण,
	[STAC_DELL_M4_2] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell_m4_2_pin_configs,
	पूर्ण,
	[STAC_DELL_M4_3] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell_m4_3_pin_configs,
	पूर्ण,
	[STAC_HP_M4] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd71bxx_fixup_hp_m4,
		.chained = true,
		.chain_id = STAC_92HD71BXX_HP,
	पूर्ण,
	[STAC_HP_DV4] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd71bxx_fixup_hp_dv4,
		.chained = true,
		.chain_id = STAC_HP_DV5,
	पूर्ण,
	[STAC_HP_DV5] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd71bxx_fixup_hp_dv5,
		.chained = true,
		.chain_id = STAC_92HD71BXX_HP,
	पूर्ण,
	[STAC_HP_HDX] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd71bxx_fixup_hp_hdx,
		.chained = true,
		.chain_id = STAC_92HD71BXX_HP,
	पूर्ण,
	[STAC_92HD71BXX_HP] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd71bxx_fixup_hp,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_model_fixup stac92hd71bxx_models[] = अणु
	अणु .id = STAC_92HD71BXX_REF, .name = "ref" पूर्ण,
	अणु .id = STAC_DELL_M4_1, .name = "dell-m4-1" पूर्ण,
	अणु .id = STAC_DELL_M4_2, .name = "dell-m4-2" पूर्ण,
	अणु .id = STAC_DELL_M4_3, .name = "dell-m4-3" पूर्ण,
	अणु .id = STAC_HP_M4, .name = "hp-m4" पूर्ण,
	अणु .id = STAC_HP_DV4, .name = "hp-dv4" पूर्ण,
	अणु .id = STAC_HP_DV5, .name = "hp-dv5" पूर्ण,
	अणु .id = STAC_HP_HDX, .name = "hp-hdx" पूर्ण,
	अणु .id = STAC_HP_DV4, .name = "hp-dv4-1222nr" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk stac92hd71bxx_fixup_tbl[] = अणु
	/* SigmaTel reference board */
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x2668,
		      "DFI LanParty", STAC_92HD71BXX_REF),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DFI, 0x3101,
		      "DFI LanParty", STAC_92HD71BXX_REF),
	SND_PCI_QUIRK_MASK(PCI_VENDOR_ID_HP, 0xfff0, 0x1720,
			  "HP", STAC_HP_DV5),
	SND_PCI_QUIRK_MASK(PCI_VENDOR_ID_HP, 0xfff0, 0x3080,
		      "HP", STAC_HP_DV5),
	SND_PCI_QUIRK_MASK(PCI_VENDOR_ID_HP, 0xfff0, 0x30f0,
		      "HP dv4-7", STAC_HP_DV4),
	SND_PCI_QUIRK_MASK(PCI_VENDOR_ID_HP, 0xfff0, 0x3600,
		      "HP dv4-7", STAC_HP_DV5),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x3610,
		      "HP HDX", STAC_HP_HDX),  /* HDX18 */
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x361a,
		      "HP mini 1000", STAC_HP_M4),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x361b,
		      "HP HDX", STAC_HP_HDX),  /* HDX16 */
	SND_PCI_QUIRK_MASK(PCI_VENDOR_ID_HP, 0xfff0, 0x3620,
		      "HP dv6", STAC_HP_DV5),
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x3061,
		      "HP dv6", STAC_HP_DV5), /* HP dv6-1110ax */
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x363e,
		      "HP DV6", STAC_HP_DV5),
	SND_PCI_QUIRK_MASK(PCI_VENDOR_ID_HP, 0xfff0, 0x7010,
		      "HP", STAC_HP_DV5),
	SND_PCI_QUIRK_VENDOR(PCI_VENDOR_ID_HP, "HP", STAC_92HD71BXX_HP),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0233,
				"unknown Dell", STAC_DELL_M4_1),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0234,
				"unknown Dell", STAC_DELL_M4_1),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0250,
				"unknown Dell", STAC_DELL_M4_1),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x024f,
				"unknown Dell", STAC_DELL_M4_1),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x024d,
				"unknown Dell", STAC_DELL_M4_1),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0251,
				"unknown Dell", STAC_DELL_M4_1),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0277,
				"unknown Dell", STAC_DELL_M4_1),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0263,
				"unknown Dell", STAC_DELL_M4_2),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0265,
				"unknown Dell", STAC_DELL_M4_2),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0262,
				"unknown Dell", STAC_DELL_M4_2),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0264,
				"unknown Dell", STAC_DELL_M4_2),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x02aa,
				"unknown Dell", STAC_DELL_M4_3),
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl ref922x_pin_configs[] = अणु
	अणु 0x0a, 0x01014010 पूर्ण,
	अणु 0x0b, 0x01016011 पूर्ण,
	अणु 0x0c, 0x01012012 पूर्ण,
	अणु 0x0d, 0x0221401f पूर्ण,
	अणु 0x0e, 0x01813122 पूर्ण,
	अणु 0x0f, 0x01011014 पूर्ण,
	अणु 0x10, 0x01441030 पूर्ण,
	अणु 0x11, 0x01c41030 पूर्ण,
	अणु 0x15, 0x40000100 पूर्ण,
	अणु 0x1b, 0x40000100 पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
    STAC 922X pin configs क्रम
    102801A7
    102801AB
    102801A9
    102801D1
    102801D2
*/
अटल स्थिर काष्ठा hda_pपूर्णांकbl dell_922x_d81_pin_configs[] = अणु
	अणु 0x0a, 0x02214030 पूर्ण,
	अणु 0x0b, 0x01a19021 पूर्ण,
	अणु 0x0c, 0x01111012 पूर्ण,
	अणु 0x0d, 0x01114010 पूर्ण,
	अणु 0x0e, 0x02a19020 पूर्ण,
	अणु 0x0f, 0x01117011 पूर्ण,
	अणु 0x10, 0x400001f0 पूर्ण,
	अणु 0x11, 0x400001f1 पूर्ण,
	अणु 0x15, 0x01813122 पूर्ण,
	अणु 0x1b, 0x400001f2 पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
    STAC 922X pin configs क्रम
    102801AC
    102801D0
*/
अटल स्थिर काष्ठा hda_pपूर्णांकbl dell_922x_d82_pin_configs[] = अणु
	अणु 0x0a, 0x02214030 पूर्ण,
	अणु 0x0b, 0x01a19021 पूर्ण,
	अणु 0x0c, 0x01111012 पूर्ण,
	अणु 0x0d, 0x01114010 पूर्ण,
	अणु 0x0e, 0x02a19020 पूर्ण,
	अणु 0x0f, 0x01117011 पूर्ण,
	अणु 0x10, 0x01451140 पूर्ण,
	अणु 0x11, 0x400001f0 पूर्ण,
	अणु 0x15, 0x01813122 पूर्ण,
	अणु 0x1b, 0x400001f1 पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
    STAC 922X pin configs क्रम
    102801BF
*/
अटल स्थिर काष्ठा hda_pपूर्णांकbl dell_922x_m81_pin_configs[] = अणु
	अणु 0x0a, 0x0321101f पूर्ण,
	अणु 0x0b, 0x01112024 पूर्ण,
	अणु 0x0c, 0x01111222 पूर्ण,
	अणु 0x0d, 0x91174220 पूर्ण,
	अणु 0x0e, 0x03a11050 पूर्ण,
	अणु 0x0f, 0x01116221 पूर्ण,
	अणु 0x10, 0x90a70330 पूर्ण,
	अणु 0x11, 0x01452340 पूर्ण,
	अणु 0x15, 0x40C003f1 पूर्ण,
	अणु 0x1b, 0x405003f0 पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
    STAC 9221 A1 pin configs क्रम
    102801D7 (Dell XPS M1210)
*/
अटल स्थिर काष्ठा hda_pपूर्णांकbl dell_922x_m82_pin_configs[] = अणु
	अणु 0x0a, 0x02211211 पूर्ण,
	अणु 0x0b, 0x408103ff पूर्ण,
	अणु 0x0c, 0x02a1123e पूर्ण,
	अणु 0x0d, 0x90100310 पूर्ण,
	अणु 0x0e, 0x408003f1 पूर्ण,
	अणु 0x0f, 0x0221121f पूर्ण,
	अणु 0x10, 0x03451340 पूर्ण,
	अणु 0x11, 0x40c003f2 पूर्ण,
	अणु 0x15, 0x508003f3 पूर्ण,
	अणु 0x1b, 0x405003f4 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl d945gtp3_pin_configs[] = अणु
	अणु 0x0a, 0x0221401f पूर्ण,
	अणु 0x0b, 0x01a19022 पूर्ण,
	अणु 0x0c, 0x01813021 पूर्ण,
	अणु 0x0d, 0x01014010 पूर्ण,
	अणु 0x0e, 0x40000100 पूर्ण,
	अणु 0x0f, 0x40000100 पूर्ण,
	अणु 0x10, 0x40000100 पूर्ण,
	अणु 0x11, 0x40000100 पूर्ण,
	अणु 0x15, 0x02a19120 पूर्ण,
	अणु 0x1b, 0x40000100 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl d945gtp5_pin_configs[] = अणु
	अणु 0x0a, 0x0221401f पूर्ण,
	अणु 0x0b, 0x01011012 पूर्ण,
	अणु 0x0c, 0x01813024 पूर्ण,
	अणु 0x0d, 0x01014010 पूर्ण,
	अणु 0x0e, 0x01a19021 पूर्ण,
	अणु 0x0f, 0x01016011 पूर्ण,
	अणु 0x10, 0x01452130 पूर्ण,
	अणु 0x11, 0x40000100 पूर्ण,
	अणु 0x15, 0x02a19320 पूर्ण,
	अणु 0x1b, 0x40000100 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl पूर्णांकel_mac_v1_pin_configs[] = अणु
	अणु 0x0a, 0x0121e21f पूर्ण,
	अणु 0x0b, 0x400000ff पूर्ण,
	अणु 0x0c, 0x9017e110 पूर्ण,
	अणु 0x0d, 0x400000fd पूर्ण,
	अणु 0x0e, 0x400000fe पूर्ण,
	अणु 0x0f, 0x0181e020 पूर्ण,
	अणु 0x10, 0x1145e030 पूर्ण,
	अणु 0x11, 0x11c5e240 पूर्ण,
	अणु 0x15, 0x400000fc पूर्ण,
	अणु 0x1b, 0x400000fb पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl पूर्णांकel_mac_v2_pin_configs[] = अणु
	अणु 0x0a, 0x0121e21f पूर्ण,
	अणु 0x0b, 0x90a7012e पूर्ण,
	अणु 0x0c, 0x9017e110 पूर्ण,
	अणु 0x0d, 0x400000fd पूर्ण,
	अणु 0x0e, 0x400000fe पूर्ण,
	अणु 0x0f, 0x0181e020 पूर्ण,
	अणु 0x10, 0x1145e230 पूर्ण,
	अणु 0x11, 0x500000fa पूर्ण,
	अणु 0x15, 0x400000fc पूर्ण,
	अणु 0x1b, 0x400000fb पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl पूर्णांकel_mac_v3_pin_configs[] = अणु
	अणु 0x0a, 0x0121e21f पूर्ण,
	अणु 0x0b, 0x90a7012e पूर्ण,
	अणु 0x0c, 0x9017e110 पूर्ण,
	अणु 0x0d, 0x400000fd पूर्ण,
	अणु 0x0e, 0x400000fe पूर्ण,
	अणु 0x0f, 0x0181e020 पूर्ण,
	अणु 0x10, 0x1145e230 पूर्ण,
	अणु 0x11, 0x11c5e240 पूर्ण,
	अणु 0x15, 0x400000fc पूर्ण,
	अणु 0x1b, 0x400000fb पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl पूर्णांकel_mac_v4_pin_configs[] = अणु
	अणु 0x0a, 0x0321e21f पूर्ण,
	अणु 0x0b, 0x03a1e02e पूर्ण,
	अणु 0x0c, 0x9017e110 पूर्ण,
	अणु 0x0d, 0x9017e11f पूर्ण,
	अणु 0x0e, 0x400000fe पूर्ण,
	अणु 0x0f, 0x0381e020 पूर्ण,
	अणु 0x10, 0x1345e230 पूर्ण,
	अणु 0x11, 0x13c5e240 पूर्ण,
	अणु 0x15, 0x400000fc पूर्ण,
	अणु 0x1b, 0x400000fb पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl पूर्णांकel_mac_v5_pin_configs[] = अणु
	अणु 0x0a, 0x0321e21f पूर्ण,
	अणु 0x0b, 0x03a1e02e पूर्ण,
	अणु 0x0c, 0x9017e110 पूर्ण,
	अणु 0x0d, 0x9017e11f पूर्ण,
	अणु 0x0e, 0x400000fe पूर्ण,
	अणु 0x0f, 0x0381e020 पूर्ण,
	अणु 0x10, 0x1345e230 पूर्ण,
	अणु 0x11, 0x13c5e240 पूर्ण,
	अणु 0x15, 0x400000fc पूर्ण,
	अणु 0x1b, 0x400000fb पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl ecs202_pin_configs[] = अणु
	अणु 0x0a, 0x0221401f पूर्ण,
	अणु 0x0b, 0x02a19020 पूर्ण,
	अणु 0x0c, 0x01a19020 पूर्ण,
	अणु 0x0d, 0x01114010 पूर्ण,
	अणु 0x0e, 0x408000f0 पूर्ण,
	अणु 0x0f, 0x01813022 पूर्ण,
	अणु 0x10, 0x074510a0 पूर्ण,
	अणु 0x11, 0x40c400f1 पूर्ण,
	अणु 0x15, 0x9037012e पूर्ण,
	अणु 0x1b, 0x40e000f2 पूर्ण,
	अणुपूर्ण
पूर्ण;

/* codec SSIDs क्रम Intel Mac sharing the same PCI SSID 8384:7680 */
अटल स्थिर काष्ठा snd_pci_quirk stac922x_पूर्णांकel_mac_fixup_tbl[] = अणु
	SND_PCI_QUIRK(0x0000, 0x0100, "Mac Mini", STAC_INTEL_MAC_V3),
	SND_PCI_QUIRK(0x106b, 0x0800, "Mac", STAC_INTEL_MAC_V1),
	SND_PCI_QUIRK(0x106b, 0x0600, "Mac", STAC_INTEL_MAC_V2),
	SND_PCI_QUIRK(0x106b, 0x0700, "Mac", STAC_INTEL_MAC_V2),
	SND_PCI_QUIRK(0x106b, 0x0e00, "Mac", STAC_INTEL_MAC_V3),
	SND_PCI_QUIRK(0x106b, 0x0f00, "Mac", STAC_INTEL_MAC_V3),
	SND_PCI_QUIRK(0x106b, 0x1600, "Mac", STAC_INTEL_MAC_V3),
	SND_PCI_QUIRK(0x106b, 0x1700, "Mac", STAC_INTEL_MAC_V3),
	SND_PCI_QUIRK(0x106b, 0x0200, "Mac", STAC_INTEL_MAC_V3),
	SND_PCI_QUIRK(0x106b, 0x1e00, "Mac", STAC_INTEL_MAC_V3),
	SND_PCI_QUIRK(0x106b, 0x1a00, "Mac", STAC_INTEL_MAC_V4),
	SND_PCI_QUIRK(0x106b, 0x0a00, "Mac", STAC_INTEL_MAC_V5),
	SND_PCI_QUIRK(0x106b, 0x2200, "Mac", STAC_INTEL_MAC_V5),
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_fixup stac922x_fixups[];

/* remap the fixup from codec SSID and apply it */
अटल व्योम stac922x_fixup_पूर्णांकel_mac_स्वतः(काष्ठा hda_codec *codec,
					  स्थिर काष्ठा hda_fixup *fix,
					  पूर्णांक action)
अणु
	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	codec->fixup_id = HDA_FIXUP_ID_NOT_SET;
	snd_hda_pick_fixup(codec, शून्य, stac922x_पूर्णांकel_mac_fixup_tbl,
			   stac922x_fixups);
	अगर (codec->fixup_id != HDA_FIXUP_ID_NOT_SET)
		snd_hda_apply_fixup(codec, action);
पूर्ण

अटल व्योम stac922x_fixup_पूर्णांकel_mac_gpio(काष्ठा hda_codec *codec,
					  स्थिर काष्ठा hda_fixup *fix,
					  पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		spec->gpio_mask = spec->gpio_dir = 0x03;
		spec->gpio_data = 0x03;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hda_fixup stac922x_fixups[] = अणु
	[STAC_D945_REF] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = ref922x_pin_configs,
	पूर्ण,
	[STAC_D945GTP3] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = d945gtp3_pin_configs,
	पूर्ण,
	[STAC_D945GTP5] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = d945gtp5_pin_configs,
	पूर्ण,
	[STAC_INTEL_MAC_AUTO] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac922x_fixup_पूर्णांकel_mac_स्वतः,
	पूर्ण,
	[STAC_INTEL_MAC_V1] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = पूर्णांकel_mac_v1_pin_configs,
		.chained = true,
		.chain_id = STAC_922X_INTEL_MAC_GPIO,
	पूर्ण,
	[STAC_INTEL_MAC_V2] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = पूर्णांकel_mac_v2_pin_configs,
		.chained = true,
		.chain_id = STAC_922X_INTEL_MAC_GPIO,
	पूर्ण,
	[STAC_INTEL_MAC_V3] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = पूर्णांकel_mac_v3_pin_configs,
		.chained = true,
		.chain_id = STAC_922X_INTEL_MAC_GPIO,
	पूर्ण,
	[STAC_INTEL_MAC_V4] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = पूर्णांकel_mac_v4_pin_configs,
		.chained = true,
		.chain_id = STAC_922X_INTEL_MAC_GPIO,
	पूर्ण,
	[STAC_INTEL_MAC_V5] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = पूर्णांकel_mac_v5_pin_configs,
		.chained = true,
		.chain_id = STAC_922X_INTEL_MAC_GPIO,
	पूर्ण,
	[STAC_922X_INTEL_MAC_GPIO] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac922x_fixup_पूर्णांकel_mac_gpio,
	पूर्ण,
	[STAC_ECS_202] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = ecs202_pin_configs,
	पूर्ण,
	[STAC_922X_DELL_D81] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell_922x_d81_pin_configs,
	पूर्ण,
	[STAC_922X_DELL_D82] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell_922x_d82_pin_configs,
	पूर्ण,
	[STAC_922X_DELL_M81] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell_922x_m81_pin_configs,
	पूर्ण,
	[STAC_922X_DELL_M82] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell_922x_m82_pin_configs,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_model_fixup stac922x_models[] = अणु
	अणु .id = STAC_D945_REF, .name = "ref" पूर्ण,
	अणु .id = STAC_D945GTP5, .name = "5stack" पूर्ण,
	अणु .id = STAC_D945GTP3, .name = "3stack" पूर्ण,
	अणु .id = STAC_INTEL_MAC_V1, .name = "intel-mac-v1" पूर्ण,
	अणु .id = STAC_INTEL_MAC_V2, .name = "intel-mac-v2" पूर्ण,
	अणु .id = STAC_INTEL_MAC_V3, .name = "intel-mac-v3" पूर्ण,
	अणु .id = STAC_INTEL_MAC_V4, .name = "intel-mac-v4" पूर्ण,
	अणु .id = STAC_INTEL_MAC_V5, .name = "intel-mac-v5" पूर्ण,
	अणु .id = STAC_INTEL_MAC_AUTO, .name = "intel-mac-auto" पूर्ण,
	अणु .id = STAC_ECS_202, .name = "ecs202" पूर्ण,
	अणु .id = STAC_922X_DELL_D81, .name = "dell-d81" पूर्ण,
	अणु .id = STAC_922X_DELL_D82, .name = "dell-d82" पूर्ण,
	अणु .id = STAC_922X_DELL_M81, .name = "dell-m81" पूर्ण,
	अणु .id = STAC_922X_DELL_M82, .name = "dell-m82" पूर्ण,
	/* क्रम backward compatibility */
	अणु .id = STAC_INTEL_MAC_V3, .name = "macmini" पूर्ण,
	अणु .id = STAC_INTEL_MAC_V5, .name = "macbook" पूर्ण,
	अणु .id = STAC_INTEL_MAC_V3, .name = "macbook-pro-v1" पूर्ण,
	अणु .id = STAC_INTEL_MAC_V3, .name = "macbook-pro" पूर्ण,
	अणु .id = STAC_INTEL_MAC_V2, .name = "imac-intel" पूर्ण,
	अणु .id = STAC_INTEL_MAC_V3, .name = "imac-intel-20" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk stac922x_fixup_tbl[] = अणु
	/* SigmaTel reference board */
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x2668,
		      "DFI LanParty", STAC_D945_REF),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DFI, 0x3101,
		      "DFI LanParty", STAC_D945_REF),
	/* Intel 945G based प्रणालीs */
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x0101,
		      "Intel D945G", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x0202,
		      "Intel D945G", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x0606,
		      "Intel D945G", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x0601,
		      "Intel D945G", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x0111,
		      "Intel D945G", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x1115,
		      "Intel D945G", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x1116,
		      "Intel D945G", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x1117,
		      "Intel D945G", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x1118,
		      "Intel D945G", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x1119,
		      "Intel D945G", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x8826,
		      "Intel D945G", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x5049,
		      "Intel D945G", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x5055,
		      "Intel D945G", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x5048,
		      "Intel D945G", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x0110,
		      "Intel D945G", STAC_D945GTP3),
	/* Intel D945G 5-stack प्रणालीs */
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x0404,
		      "Intel D945G", STAC_D945GTP5),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x0303,
		      "Intel D945G", STAC_D945GTP5),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x0013,
		      "Intel D945G", STAC_D945GTP5),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x0417,
		      "Intel D945G", STAC_D945GTP5),
	/* Intel 945P based प्रणालीs */
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x0b0b,
		      "Intel D945P", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x0112,
		      "Intel D945P", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x0d0d,
		      "Intel D945P", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x0909,
		      "Intel D945P", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x0505,
		      "Intel D945P", STAC_D945GTP3),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x0707,
		      "Intel D945P", STAC_D945GTP5),
	/* other पूर्णांकel */
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x0204,
		      "Intel D945", STAC_D945_REF),
	/* other प्रणालीs  */

	/* Apple Intel Mac (Mac Mini, MacBook, MacBook Pro...) */
	SND_PCI_QUIRK(0x8384, 0x7680, "Mac", STAC_INTEL_MAC_AUTO),

	/* Dell प्रणालीs  */
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01a7,
		      "unknown Dell", STAC_922X_DELL_D81),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01a9,
		      "unknown Dell", STAC_922X_DELL_D81),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01ab,
		      "unknown Dell", STAC_922X_DELL_D81),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01ac,
		      "unknown Dell", STAC_922X_DELL_D82),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01bf,
		      "unknown Dell", STAC_922X_DELL_M81),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01d0,
		      "unknown Dell", STAC_922X_DELL_D82),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01d1,
		      "unknown Dell", STAC_922X_DELL_D81),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01d2,
		      "unknown Dell", STAC_922X_DELL_D81),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01d7,
		      "Dell XPS M1210", STAC_922X_DELL_M82),
	/* ECS/PC Chips boards */
	SND_PCI_QUIRK_MASK(0x1019, 0xf000, 0x2000,
		      "ECS/PC chips", STAC_ECS_202),
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl ref927x_pin_configs[] = अणु
	अणु 0x0a, 0x02214020 पूर्ण,
	अणु 0x0b, 0x02a19080 पूर्ण,
	अणु 0x0c, 0x0181304e पूर्ण,
	अणु 0x0d, 0x01014010 पूर्ण,
	अणु 0x0e, 0x01a19040 पूर्ण,
	अणु 0x0f, 0x01011012 पूर्ण,
	अणु 0x10, 0x01016011 पूर्ण,
	अणु 0x11, 0x0101201f पूर्ण,
	अणु 0x12, 0x183301f0 पूर्ण,
	अणु 0x13, 0x18a001f0 पूर्ण,
	अणु 0x14, 0x18a001f0 पूर्ण,
	अणु 0x21, 0x01442070 पूर्ण,
	अणु 0x22, 0x01c42190 पूर्ण,
	अणु 0x23, 0x40000100 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl d965_3st_pin_configs[] = अणु
	अणु 0x0a, 0x0221401f पूर्ण,
	अणु 0x0b, 0x02a19120 पूर्ण,
	अणु 0x0c, 0x40000100 पूर्ण,
	अणु 0x0d, 0x01014011 पूर्ण,
	अणु 0x0e, 0x01a19021 पूर्ण,
	अणु 0x0f, 0x01813024 पूर्ण,
	अणु 0x10, 0x40000100 पूर्ण,
	अणु 0x11, 0x40000100 पूर्ण,
	अणु 0x12, 0x40000100 पूर्ण,
	अणु 0x13, 0x40000100 पूर्ण,
	अणु 0x14, 0x40000100 पूर्ण,
	अणु 0x21, 0x40000100 पूर्ण,
	अणु 0x22, 0x40000100 पूर्ण,
	अणु 0x23, 0x40000100 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl d965_5st_pin_configs[] = अणु
	अणु 0x0a, 0x02214020 पूर्ण,
	अणु 0x0b, 0x02a19080 पूर्ण,
	अणु 0x0c, 0x0181304e पूर्ण,
	अणु 0x0d, 0x01014010 पूर्ण,
	अणु 0x0e, 0x01a19040 पूर्ण,
	अणु 0x0f, 0x01011012 पूर्ण,
	अणु 0x10, 0x01016011 पूर्ण,
	अणु 0x11, 0x40000100 पूर्ण,
	अणु 0x12, 0x40000100 पूर्ण,
	अणु 0x13, 0x40000100 पूर्ण,
	अणु 0x14, 0x40000100 पूर्ण,
	अणु 0x21, 0x01442070 पूर्ण,
	अणु 0x22, 0x40000100 पूर्ण,
	अणु 0x23, 0x40000100 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl d965_5st_no_fp_pin_configs[] = अणु
	अणु 0x0a, 0x40000100 पूर्ण,
	अणु 0x0b, 0x40000100 पूर्ण,
	अणु 0x0c, 0x0181304e पूर्ण,
	अणु 0x0d, 0x01014010 पूर्ण,
	अणु 0x0e, 0x01a19040 पूर्ण,
	अणु 0x0f, 0x01011012 पूर्ण,
	अणु 0x10, 0x01016011 पूर्ण,
	अणु 0x11, 0x40000100 पूर्ण,
	अणु 0x12, 0x40000100 पूर्ण,
	अणु 0x13, 0x40000100 पूर्ण,
	अणु 0x14, 0x40000100 पूर्ण,
	अणु 0x21, 0x01442070 पूर्ण,
	अणु 0x22, 0x40000100 पूर्ण,
	अणु 0x23, 0x40000100 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl dell_3st_pin_configs[] = अणु
	अणु 0x0a, 0x02211230 पूर्ण,
	अणु 0x0b, 0x02a11220 पूर्ण,
	अणु 0x0c, 0x01a19040 पूर्ण,
	अणु 0x0d, 0x01114210 पूर्ण,
	अणु 0x0e, 0x01111212 पूर्ण,
	अणु 0x0f, 0x01116211 पूर्ण,
	अणु 0x10, 0x01813050 पूर्ण,
	अणु 0x11, 0x01112214 पूर्ण,
	अणु 0x12, 0x403003fa पूर्ण,
	अणु 0x13, 0x90a60040 पूर्ण,
	अणु 0x14, 0x90a60040 पूर्ण,
	अणु 0x21, 0x404003fb पूर्ण,
	अणु 0x22, 0x40c003fc पूर्ण,
	अणु 0x23, 0x40000100 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम stac927x_fixup_ref_no_jd(काष्ठा hda_codec *codec,
				     स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	/* no jack detecion क्रम ref-no-jd model */
	अगर (action == HDA_FIXUP_ACT_PRE_PROBE)
		codec->no_jack_detect = 1;
पूर्ण

अटल व्योम stac927x_fixup_ref(काष्ठा hda_codec *codec,
			       स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		snd_hda_apply_pincfgs(codec, ref927x_pin_configs);
		spec->eapd_mask = spec->gpio_mask = 0;
		spec->gpio_dir = spec->gpio_data = 0;
	पूर्ण
पूर्ण

अटल व्योम stac927x_fixup_dell_dmic(काष्ठा hda_codec *codec,
				     स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	अगर (codec->core.subप्रणाली_id != 0x1028022f) अणु
		/* GPIO2 High = Enable EAPD */
		spec->eapd_mask = spec->gpio_mask = 0x04;
		spec->gpio_dir = spec->gpio_data = 0x04;
	पूर्ण

	snd_hda_add_verbs(codec, dell_3st_core_init);
	spec->volknob_init = 1;
पूर्ण

अटल व्योम stac927x_fixup_volknob(काष्ठा hda_codec *codec,
				   स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		snd_hda_add_verbs(codec, stac927x_volknob_core_init);
		spec->volknob_init = 1;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hda_fixup stac927x_fixups[] = अणु
	[STAC_D965_REF_NO_JD] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac927x_fixup_ref_no_jd,
		.chained = true,
		.chain_id = STAC_D965_REF,
	पूर्ण,
	[STAC_D965_REF] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac927x_fixup_ref,
	पूर्ण,
	[STAC_D965_3ST] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = d965_3st_pin_configs,
		.chained = true,
		.chain_id = STAC_D965_VERBS,
	पूर्ण,
	[STAC_D965_5ST] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = d965_5st_pin_configs,
		.chained = true,
		.chain_id = STAC_D965_VERBS,
	पूर्ण,
	[STAC_D965_VERBS] = अणु
		.type = HDA_FIXUP_VERBS,
		.v.verbs = d965_core_init,
	पूर्ण,
	[STAC_D965_5ST_NO_FP] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = d965_5st_no_fp_pin_configs,
	पूर्ण,
	[STAC_NEMO_DEFAULT] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = nemo_pin_configs,
	पूर्ण,
	[STAC_DELL_3ST] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell_3st_pin_configs,
		.chained = true,
		.chain_id = STAC_927X_DELL_DMIC,
	पूर्ण,
	[STAC_DELL_BIOS] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			/* correct the front output jack as a hp out */
			अणु 0x0f, 0x0221101f पूर्ण,
			/* correct the front input jack as a mic */
			अणु 0x0e, 0x02a79130 पूर्ण,
			अणुपूर्ण
		पूर्ण,
		.chained = true,
		.chain_id = STAC_927X_DELL_DMIC,
	पूर्ण,
	[STAC_DELL_BIOS_AMIC] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			/* configure the analog microphone on some laptops */
			अणु 0x0c, 0x90a79130 पूर्ण,
			अणुपूर्ण
		पूर्ण,
		.chained = true,
		.chain_id = STAC_DELL_BIOS,
	पूर्ण,
	[STAC_DELL_BIOS_SPDIF] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु
			/* correct the device field to SPDIF out */
			अणु 0x21, 0x01442070 पूर्ण,
			अणुपूर्ण
		पूर्ण,
		.chained = true,
		.chain_id = STAC_DELL_BIOS,
	पूर्ण,
	[STAC_927X_DELL_DMIC] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac927x_fixup_dell_dmic,
	पूर्ण,
	[STAC_927X_VOLKNOB] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac927x_fixup_volknob,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_model_fixup stac927x_models[] = अणु
	अणु .id = STAC_D965_REF_NO_JD, .name = "ref-no-jd" पूर्ण,
	अणु .id = STAC_D965_REF, .name = "ref" पूर्ण,
	अणु .id = STAC_D965_3ST, .name = "3stack" पूर्ण,
	अणु .id = STAC_D965_5ST, .name = "5stack" पूर्ण,
	अणु .id = STAC_D965_5ST_NO_FP, .name = "5stack-no-fp" पूर्ण,
	अणु .id = STAC_DELL_3ST, .name = "dell-3stack" पूर्ण,
	अणु .id = STAC_DELL_BIOS, .name = "dell-bios" पूर्ण,
	अणु .id = STAC_NEMO_DEFAULT, .name = "nemo-default" पूर्ण,
	अणु .id = STAC_DELL_BIOS_AMIC, .name = "dell-bios-amic" पूर्ण,
	अणु .id = STAC_927X_VOLKNOB, .name = "volknob" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk stac927x_fixup_tbl[] = अणु
	/* SigmaTel reference board */
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x2668,
		      "DFI LanParty", STAC_D965_REF),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DFI, 0x3101,
		      "DFI LanParty", STAC_D965_REF),
	 /* Intel 946 based प्रणालीs */
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x3d01, "Intel D946", STAC_D965_3ST),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0xa301, "Intel D946", STAC_D965_3ST),
	/* 965 based 3 stack प्रणालीs */
	SND_PCI_QUIRK_MASK(PCI_VENDOR_ID_INTEL, 0xff00, 0x2100,
			   "Intel D965", STAC_D965_3ST),
	SND_PCI_QUIRK_MASK(PCI_VENDOR_ID_INTEL, 0xff00, 0x2000,
			   "Intel D965", STAC_D965_3ST),
	/* Dell 3 stack प्रणालीs */
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL,  0x01dd, "Dell Dimension E520", STAC_DELL_3ST),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL,  0x01ed, "Dell     ", STAC_DELL_3ST),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL,  0x01f4, "Dell     ", STAC_DELL_3ST),
	/* Dell 3 stack प्रणालीs with verb table in BIOS */
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL,  0x01f3, "Dell Inspiron 1420", STAC_DELL_BIOS),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL,  0x01f7, "Dell XPS M1730", STAC_DELL_BIOS),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL,  0x0227, "Dell Vostro 1400  ", STAC_DELL_BIOS),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL,  0x022e, "Dell     ", STAC_DELL_BIOS_SPDIF),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL,  0x022f, "Dell Inspiron 1525", STAC_DELL_BIOS),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL,  0x0242, "Dell     ", STAC_DELL_BIOS),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL,  0x0243, "Dell     ", STAC_DELL_BIOS),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL,  0x02ff, "Dell     ", STAC_DELL_BIOS),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL,  0x0209, "Dell XPS 1330", STAC_DELL_BIOS_SPDIF),
	/* 965 based 5 stack प्रणालीs */
	SND_PCI_QUIRK_MASK(PCI_VENDOR_ID_INTEL, 0xff00, 0x2300,
			   "Intel D965", STAC_D965_5ST),
	SND_PCI_QUIRK_MASK(PCI_VENDOR_ID_INTEL, 0xff00, 0x2500,
			   "Intel D965", STAC_D965_5ST),
	/* Nemo */
	SND_PCI_QUIRK(0x1888, 0x1000, "AmigaOne X1000", STAC_NEMO_DEFAULT),
	/* volume-knob fixes */
	SND_PCI_QUIRK_VENDOR(0x10cf, "FSC", STAC_927X_VOLKNOB),
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl ref9205_pin_configs[] = अणु
	अणु 0x0a, 0x40000100 पूर्ण,
	अणु 0x0b, 0x40000100 पूर्ण,
	अणु 0x0c, 0x01016011 पूर्ण,
	अणु 0x0d, 0x01014010 पूर्ण,
	अणु 0x0e, 0x01813122 पूर्ण,
	अणु 0x0f, 0x01a19021 पूर्ण,
	अणु 0x14, 0x01019020 पूर्ण,
	अणु 0x16, 0x40000100 पूर्ण,
	अणु 0x17, 0x90a000f0 पूर्ण,
	अणु 0x18, 0x90a000f0 पूर्ण,
	अणु 0x21, 0x01441030 पूर्ण,
	अणु 0x22, 0x01c41030 पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
    STAC 9205 pin configs क्रम
    102801F1
    102801F2
    102801FC
    102801FD
    10280204
    1028021F
    10280228 (Dell Vostro 1500)
    10280229 (Dell Vostro 1700)
*/
अटल स्थिर काष्ठा hda_pपूर्णांकbl dell_9205_m42_pin_configs[] = अणु
	अणु 0x0a, 0x0321101F पूर्ण,
	अणु 0x0b, 0x03A11020 पूर्ण,
	अणु 0x0c, 0x400003FA पूर्ण,
	अणु 0x0d, 0x90170310 पूर्ण,
	अणु 0x0e, 0x400003FB पूर्ण,
	अणु 0x0f, 0x400003FC पूर्ण,
	अणु 0x14, 0x400003FD पूर्ण,
	अणु 0x16, 0x40F000F9 पूर्ण,
	अणु 0x17, 0x90A60330 पूर्ण,
	अणु 0x18, 0x400003FF पूर्ण,
	अणु 0x21, 0x0144131F पूर्ण,
	अणु 0x22, 0x40C003FE पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
    STAC 9205 pin configs क्रम
    102801F9
    102801FA
    102801FE
    102801FF (Dell Precision M4300)
    10280206
    10280200
    10280201
*/
अटल स्थिर काष्ठा hda_pपूर्णांकbl dell_9205_m43_pin_configs[] = अणु
	अणु 0x0a, 0x0321101f पूर्ण,
	अणु 0x0b, 0x03a11020 पूर्ण,
	अणु 0x0c, 0x90a70330 पूर्ण,
	अणु 0x0d, 0x90170310 पूर्ण,
	अणु 0x0e, 0x400000fe पूर्ण,
	अणु 0x0f, 0x400000ff पूर्ण,
	अणु 0x14, 0x400000fd पूर्ण,
	अणु 0x16, 0x40f000f9 पूर्ण,
	अणु 0x17, 0x400000fa पूर्ण,
	अणु 0x18, 0x400000fc पूर्ण,
	अणु 0x21, 0x0144131f पूर्ण,
	अणु 0x22, 0x40c003f8 पूर्ण,
	/* Enable SPDIF in/out */
	अणु 0x1f, 0x01441030 पूर्ण,
	अणु 0x20, 0x1c410030 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl dell_9205_m44_pin_configs[] = अणु
	अणु 0x0a, 0x0421101f पूर्ण,
	अणु 0x0b, 0x04a11020 पूर्ण,
	अणु 0x0c, 0x400003fa पूर्ण,
	अणु 0x0d, 0x90170310 पूर्ण,
	अणु 0x0e, 0x400003fb पूर्ण,
	अणु 0x0f, 0x400003fc पूर्ण,
	अणु 0x14, 0x400003fd पूर्ण,
	अणु 0x16, 0x400003f9 पूर्ण,
	अणु 0x17, 0x90a60330 पूर्ण,
	अणु 0x18, 0x400003ff पूर्ण,
	अणु 0x21, 0x01441340 पूर्ण,
	अणु 0x22, 0x40c003fe पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम stac9205_fixup_ref(काष्ठा hda_codec *codec,
			       स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		snd_hda_apply_pincfgs(codec, ref9205_pin_configs);
		/* SPDIF-In enabled */
		spec->eapd_mask = spec->gpio_mask = spec->gpio_dir = 0;
	पूर्ण
पूर्ण

अटल व्योम stac9205_fixup_dell_m43(काष्ठा hda_codec *codec,
				    स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;
	काष्ठा hda_jack_callback *jack;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE) अणु
		snd_hda_apply_pincfgs(codec, dell_9205_m43_pin_configs);

		/* Enable unsol response क्रम GPIO4/Dock HP connection */
		snd_hda_codec_ग_लिखो_cache(codec, codec->core.afg, 0,
			AC_VERB_SET_GPIO_UNSOLICITED_RSP_MASK, 0x10);
		jack = snd_hda_jack_detect_enable_callback(codec, codec->core.afg,
							   stac_vref_event);
		अगर (!IS_ERR(jack))
			jack->निजी_data = 0x01;

		spec->gpio_dir = 0x0b;
		spec->eapd_mask = 0x01;
		spec->gpio_mask = 0x1b;
		spec->gpio_mute = 0x10;
		/* GPIO0 High = EAPD, GPIO1 Low = Headphone Mute,
		 * GPIO3 Low = DRM
		 */
		spec->gpio_data = 0x01;
	पूर्ण
पूर्ण

अटल व्योम stac9205_fixup_eapd(काष्ठा hda_codec *codec,
				स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action == HDA_FIXUP_ACT_PRE_PROBE)
		spec->eapd_चयन = 0;
पूर्ण

अटल स्थिर काष्ठा hda_fixup stac9205_fixups[] = अणु
	[STAC_9205_REF] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac9205_fixup_ref,
	पूर्ण,
	[STAC_9205_DELL_M42] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell_9205_m42_pin_configs,
	पूर्ण,
	[STAC_9205_DELL_M43] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac9205_fixup_dell_m43,
	पूर्ण,
	[STAC_9205_DELL_M44] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = dell_9205_m44_pin_configs,
	पूर्ण,
	[STAC_9205_EAPD] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac9205_fixup_eapd,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_model_fixup stac9205_models[] = अणु
	अणु .id = STAC_9205_REF, .name = "ref" पूर्ण,
	अणु .id = STAC_9205_DELL_M42, .name = "dell-m42" पूर्ण,
	अणु .id = STAC_9205_DELL_M43, .name = "dell-m43" पूर्ण,
	अणु .id = STAC_9205_DELL_M44, .name = "dell-m44" पूर्ण,
	अणु .id = STAC_9205_EAPD, .name = "eapd" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk stac9205_fixup_tbl[] = अणु
	/* SigmaTel reference board */
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0x2668,
		      "DFI LanParty", STAC_9205_REF),
	SND_PCI_QUIRK(PCI_VENDOR_ID_INTEL, 0xfb30,
		      "SigmaTel", STAC_9205_REF),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DFI, 0x3101,
		      "DFI LanParty", STAC_9205_REF),
	/* Dell */
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01f1,
		      "unknown Dell", STAC_9205_DELL_M42),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01f2,
		      "unknown Dell", STAC_9205_DELL_M42),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01f8,
		      "Dell Precision", STAC_9205_DELL_M43),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01f9,
		      "Dell Precision", STAC_9205_DELL_M43),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01fa,
		      "Dell Precision", STAC_9205_DELL_M43),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01fc,
		      "unknown Dell", STAC_9205_DELL_M42),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01fd,
		      "unknown Dell", STAC_9205_DELL_M42),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01fe,
		      "Dell Precision", STAC_9205_DELL_M43),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x01ff,
		      "Dell Precision M4300", STAC_9205_DELL_M43),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0204,
		      "unknown Dell", STAC_9205_DELL_M42),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0206,
		      "Dell Precision", STAC_9205_DELL_M43),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x021b,
		      "Dell Precision", STAC_9205_DELL_M43),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x021c,
		      "Dell Precision", STAC_9205_DELL_M43),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x021f,
		      "Dell Inspiron", STAC_9205_DELL_M44),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0228,
		      "Dell Vostro 1500", STAC_9205_DELL_M42),
	SND_PCI_QUIRK(PCI_VENDOR_ID_DELL, 0x0229,
		      "Dell Vostro 1700", STAC_9205_DELL_M42),
	/* Gateway */
	SND_PCI_QUIRK(0x107b, 0x0560, "Gateway T6834c", STAC_9205_EAPD),
	SND_PCI_QUIRK(0x107b, 0x0565, "Gateway T1616", STAC_9205_EAPD),
	अणुपूर्ण /* terminator */
पूर्ण;

अटल व्योम stac92hd95_fixup_hp_led(काष्ठा hda_codec *codec,
				    स्थिर काष्ठा hda_fixup *fix, पूर्णांक action)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	अगर (action != HDA_FIXUP_ACT_PRE_PROBE)
		वापस;

	अगर (find_mute_led_cfg(codec, spec->शेष_polarity))
		codec_dbg(codec, "mute LED gpio %d polarity %d\n",
				spec->gpio_led,
				spec->gpio_led_polarity);
पूर्ण

अटल स्थिर काष्ठा hda_fixup stac92hd95_fixups[] = अणु
	[STAC_92HD95_HP_LED] = अणु
		.type = HDA_FIXUP_FUNC,
		.v.func = stac92hd95_fixup_hp_led,
	पूर्ण,
	[STAC_92HD95_HP_BASS] = अणु
		.type = HDA_FIXUP_VERBS,
		.v.verbs = (स्थिर काष्ठा hda_verb[]) अणु
			अणु0x1a, 0x795, 0x00पूर्ण, /* HPF to 100Hz */
			अणुपूर्ण
		पूर्ण,
		.chained = true,
		.chain_id = STAC_92HD95_HP_LED,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk stac92hd95_fixup_tbl[] = अणु
	SND_PCI_QUIRK(PCI_VENDOR_ID_HP, 0x1911, "HP Spectre 13", STAC_92HD95_HP_BASS),
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_model_fixup stac92hd95_models[] = अणु
	अणु .id = STAC_92HD95_HP_LED, .name = "hp-led" पूर्ण,
	अणु .id = STAC_92HD95_HP_BASS, .name = "hp-bass" पूर्ण,
	अणुपूर्ण
पूर्ण;


अटल पूर्णांक stac_parse_स्वतः_config(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;
	पूर्णांक err;
	पूर्णांक flags = 0;

	अगर (spec->headset_jack)
		flags |= HDA_PINCFG_HEADSET_MIC;

	err = snd_hda_parse_pin_defcfg(codec, &spec->gen.स्वतःcfg, शून्य, flags);
	अगर (err < 0)
		वापस err;

	/* add hooks */
	spec->gen.pcm_playback_hook = stac_playback_pcm_hook;
	spec->gen.pcm_capture_hook = stac_capture_pcm_hook;

	spec->gen.स्वतःmute_hook = stac_update_outमाला_दो;

	अगर (spec->gpio_led)
		snd_hda_gen_add_mute_led_cdev(codec, stac_vmaster_hook);

	err = snd_hda_gen_parse_स्वतः_config(codec, &spec->gen.स्वतःcfg);
	अगर (err < 0)
		वापस err;

	अगर (spec->vref_mute_led_nid) अणु
		err = snd_hda_gen_fix_pin_घातer(codec, spec->vref_mute_led_nid);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* setup analog beep controls */
	अगर (spec->anabeep_nid > 0) अणु
		err = stac_स्वतः_create_beep_ctls(codec,
						 spec->anabeep_nid);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* setup digital beep controls and input device */
#अगर_घोषित CONFIG_SND_HDA_INPUT_BEEP
	अगर (spec->gen.beep_nid) अणु
		hda_nid_t nid = spec->gen.beep_nid;
		अचिन्हित पूर्णांक caps;

		err = stac_स्वतः_create_beep_ctls(codec, nid);
		अगर (err < 0)
			वापस err;
		अगर (codec->beep) अणु
			/* IDT/STAC codecs have linear beep tone parameter */
			codec->beep->linear_tone = spec->linear_tone_beep;
			/* अगर no beep चयन is available, make its own one */
			caps = query_amp_caps(codec, nid, HDA_OUTPUT);
			अगर (!(caps & AC_AMPCAP_MUTE)) अणु
				err = stac_beep_चयन_ctl(codec);
				अगर (err < 0)
					वापस err;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (spec->aloopback_ctl &&
	    snd_hda_get_bool_hपूर्णांक(codec, "loopback") == 1) अणु
		अचिन्हित पूर्णांक wr_verb =
			spec->aloopback_ctl->निजी_value >> 16;
		अगर (snd_hdac_regmap_add_venकरोr_verb(&codec->core, wr_verb))
			वापस -ENOMEM;
		अगर (!snd_hda_gen_add_kctl(&spec->gen, शून्य, spec->aloopback_ctl))
			वापस -ENOMEM;
	पूर्ण

	अगर (spec->have_spdअगर_mux) अणु
		err = stac_create_spdअगर_mux_ctls(codec);
		अगर (err < 0)
			वापस err;
	पूर्ण

	stac_init_घातer_map(codec);

	वापस 0;
पूर्ण

अटल पूर्णांक stac_init(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;
	पूर्णांक i;

	/* override some hपूर्णांकs */
	stac_store_hपूर्णांकs(codec);

	/* set up GPIO */
	/* turn on EAPD अटलally when spec->eapd_चयन isn't set.
	 * otherwise, unsol event will turn it on/off dynamically
	 */
	अगर (!spec->eapd_चयन)
		spec->gpio_data |= spec->eapd_mask;
	stac_gpio_set(codec, spec->gpio_mask, spec->gpio_dir, spec->gpio_data);

	snd_hda_gen_init(codec);

	/* sync the घातer-map */
	अगर (spec->num_pwrs)
		snd_hda_codec_ग_लिखो(codec, codec->core.afg, 0,
				    AC_VERB_IDT_SET_POWER_MAP,
				    spec->घातer_map_bits);

	/* घातer करोwn inactive ADCs */
	अगर (spec->घातerकरोwn_adcs) अणु
		क्रम (i = 0; i < spec->gen.num_all_adcs; i++) अणु
			अगर (spec->active_adcs & (1 << i))
				जारी;
			snd_hda_codec_ग_लिखो(codec, spec->gen.all_adcs[i], 0,
					    AC_VERB_SET_POWER_STATE,
					    AC_PWRST_D3);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम stac_shutup(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	snd_hda_shutup_pins(codec);

	अगर (spec->eapd_mask)
		stac_gpio_set(codec, spec->gpio_mask,
				spec->gpio_dir, spec->gpio_data &
				~spec->eapd_mask);
पूर्ण

#घोषणा stac_मुक्त	snd_hda_gen_मुक्त

#अगर_घोषित CONFIG_SND_PROC_FS
अटल व्योम stac92hd_proc_hook(काष्ठा snd_info_buffer *buffer,
			       काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अगर (nid == codec->core.afg)
		snd_iम_लिखो(buffer, "Power-Map: 0x%02x\n", 
			    snd_hda_codec_पढ़ो(codec, nid, 0,
					       AC_VERB_IDT_GET_POWER_MAP, 0));
पूर्ण

अटल व्योम analog_loop_proc_hook(काष्ठा snd_info_buffer *buffer,
				  काष्ठा hda_codec *codec,
				  अचिन्हित पूर्णांक verb)
अणु
	snd_iम_लिखो(buffer, "Analog Loopback: 0x%02x\n",
		    snd_hda_codec_पढ़ो(codec, codec->core.afg, 0, verb, 0));
पूर्ण

/* stac92hd71bxx, stac92hd73xx */
अटल व्योम stac92hd7x_proc_hook(काष्ठा snd_info_buffer *buffer,
				 काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	stac92hd_proc_hook(buffer, codec, nid);
	अगर (nid == codec->core.afg)
		analog_loop_proc_hook(buffer, codec, 0xfa0);
पूर्ण

अटल व्योम stac9205_proc_hook(काष्ठा snd_info_buffer *buffer,
			       काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अगर (nid == codec->core.afg)
		analog_loop_proc_hook(buffer, codec, 0xfe0);
पूर्ण

अटल व्योम stac927x_proc_hook(काष्ठा snd_info_buffer *buffer,
			       काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अगर (nid == codec->core.afg)
		analog_loop_proc_hook(buffer, codec, 0xfeb);
पूर्ण
#अन्यथा
#घोषणा stac92hd_proc_hook	शून्य
#घोषणा stac92hd7x_proc_hook	शून्य
#घोषणा stac9205_proc_hook	शून्य
#घोषणा stac927x_proc_hook	शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक stac_suspend(काष्ठा hda_codec *codec)
अणु
	stac_shutup(codec);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा stac_suspend		शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा hda_codec_ops stac_patch_ops = अणु
	.build_controls = snd_hda_gen_build_controls,
	.build_pcms = snd_hda_gen_build_pcms,
	.init = stac_init,
	.मुक्त = stac_मुक्त,
	.unsol_event = snd_hda_jack_unsol_event,
#अगर_घोषित CONFIG_PM
	.suspend = stac_suspend,
#पूर्ण_अगर
	.reboot_notअगरy = stac_shutup,
पूर्ण;

अटल पूर्णांक alloc_stac_spec(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	snd_hda_gen_spec_init(&spec->gen);
	codec->spec = spec;
	codec->no_trigger_sense = 1; /* seems common with STAC/IDT codecs */
	spec->gen.dac_min_mute = true;
	codec->patch_ops = stac_patch_ops;
	वापस 0;
पूर्ण

अटल पूर्णांक patch_stac9200(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec;
	पूर्णांक err;

	err = alloc_stac_spec(codec);
	अगर (err < 0)
		वापस err;

	spec = codec->spec;
	spec->linear_tone_beep = 1;
	spec->gen.own_eapd_ctl = 1;

	codec->घातer_filter = snd_hda_codec_eapd_घातer_filter;

	snd_hda_add_verbs(codec, stac9200_eapd_init);

	snd_hda_pick_fixup(codec, stac9200_models, stac9200_fixup_tbl,
			   stac9200_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	err = stac_parse_स्वतः_config(codec);
	अगर (err < 0) अणु
		stac_मुक्त(codec);
		वापस err;
	पूर्ण

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;
पूर्ण

अटल पूर्णांक patch_stac925x(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec;
	पूर्णांक err;

	err = alloc_stac_spec(codec);
	अगर (err < 0)
		वापस err;

	spec = codec->spec;
	spec->linear_tone_beep = 1;
	spec->gen.own_eapd_ctl = 1;

	snd_hda_add_verbs(codec, stac925x_core_init);

	snd_hda_pick_fixup(codec, stac925x_models, stac925x_fixup_tbl,
			   stac925x_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	err = stac_parse_स्वतः_config(codec);
	अगर (err < 0) अणु
		stac_मुक्त(codec);
		वापस err;
	पूर्ण

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;
पूर्ण

अटल पूर्णांक patch_stac92hd73xx(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec;
	पूर्णांक err;
	पूर्णांक num_dacs;

	err = alloc_stac_spec(codec);
	अगर (err < 0)
		वापस err;

	spec = codec->spec;
	/* enable घातer_save_node only क्रम new 92HD89xx chips, as it causes
	 * click noises on old 92HD73xx chips.
	 */
	अगर ((codec->core.venकरोr_id & 0xfffffff0) != 0x111d7670)
		codec->घातer_save_node = 1;
	spec->linear_tone_beep = 0;
	spec->gen.mixer_nid = 0x1d;
	spec->have_spdअगर_mux = 1;

	num_dacs = snd_hda_get_num_conns(codec, 0x0a) - 1;
	अगर (num_dacs < 3 || num_dacs > 5) अणु
		codec_warn(codec,
			   "Could not determine number of channels defaulting to DAC count\n");
		num_dacs = 5;
	पूर्ण

	चयन (num_dacs) अणु
	हाल 0x3: /* 6 Channel */
		spec->aloopback_ctl = &stac92hd73xx_6ch_loopback;
		अवरोध;
	हाल 0x4: /* 8 Channel */
		spec->aloopback_ctl = &stac92hd73xx_8ch_loopback;
		अवरोध;
	हाल 0x5: /* 10 Channel */
		spec->aloopback_ctl = &stac92hd73xx_10ch_loopback;
		अवरोध;
	पूर्ण

	spec->aloopback_mask = 0x01;
	spec->aloopback_shअगरt = 8;

	spec->gen.beep_nid = 0x1c; /* digital beep */

	/* GPIO0 High = Enable EAPD */
	spec->eapd_mask = spec->gpio_mask = spec->gpio_dir = 0x1;
	spec->gpio_data = 0x01;

	spec->eapd_चयन = 1;

	spec->num_pwrs = ARRAY_SIZE(stac92hd73xx_pwr_nids);
	spec->pwr_nids = stac92hd73xx_pwr_nids;

	spec->gen.own_eapd_ctl = 1;
	spec->gen.घातer_करोwn_unused = 1;

	snd_hda_pick_fixup(codec, stac92hd73xx_models, stac92hd73xx_fixup_tbl,
			   stac92hd73xx_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	अगर (!spec->volknob_init)
		snd_hda_add_verbs(codec, stac92hd73xx_core_init);

	err = stac_parse_स्वतः_config(codec);
	अगर (err < 0) अणु
		stac_मुक्त(codec);
		वापस err;
	पूर्ण

	/* Don't GPIO-mute speakers अगर there are no पूर्णांकernal speakers, because
	 * the GPIO might be necessary क्रम Headphone
	 */
	अगर (spec->eapd_चयन && !has_builtin_speaker(codec))
		spec->eapd_चयन = 0;

	codec->proc_widget_hook = stac92hd7x_proc_hook;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;
पूर्ण

अटल व्योम stac_setup_gpio(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec = codec->spec;

	spec->gpio_mask |= spec->eapd_mask;
	अगर (spec->gpio_led) अणु
		अगर (!spec->vref_mute_led_nid) अणु
			spec->gpio_mask |= spec->gpio_led;
			spec->gpio_dir |= spec->gpio_led;
			spec->gpio_data |= spec->gpio_led;
		पूर्ण अन्यथा अणु
			codec->घातer_filter = stac_vref_led_घातer_filter;
		पूर्ण
	पूर्ण

	अगर (spec->mic_mute_led_gpio) अणु
		spec->gpio_mask |= spec->mic_mute_led_gpio;
		spec->gpio_dir |= spec->mic_mute_led_gpio;
		spec->mic_enabled = 0;
		spec->gpio_data |= spec->mic_mute_led_gpio;
		snd_hda_gen_add_micmute_led_cdev(codec, stac_capture_led_update);
	पूर्ण
पूर्ण

अटल पूर्णांक patch_stac92hd83xxx(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec;
	पूर्णांक err;

	err = alloc_stac_spec(codec);
	अगर (err < 0)
		वापस err;

	/* दीर्घer delay needed क्रम D3 */
	codec->core.घातer_caps &= ~AC_PWRST_EPSS;

	spec = codec->spec;
	codec->घातer_save_node = 1;
	spec->linear_tone_beep = 0;
	spec->gen.own_eapd_ctl = 1;
	spec->gen.घातer_करोwn_unused = 1;
	spec->gen.mixer_nid = 0x1b;

	spec->gen.beep_nid = 0x21; /* digital beep */
	spec->pwr_nids = stac92hd83xxx_pwr_nids;
	spec->num_pwrs = ARRAY_SIZE(stac92hd83xxx_pwr_nids);
	spec->शेष_polarity = -1; /* no शेष cfg */

	snd_hda_add_verbs(codec, stac92hd83xxx_core_init);

	snd_hda_pick_fixup(codec, stac92hd83xxx_models, stac92hd83xxx_fixup_tbl,
			   stac92hd83xxx_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	stac_setup_gpio(codec);

	err = stac_parse_स्वतः_config(codec);
	अगर (err < 0) अणु
		stac_मुक्त(codec);
		वापस err;
	पूर्ण

	codec->proc_widget_hook = stac92hd_proc_hook;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;
पूर्ण

अटल स्थिर hda_nid_t stac92hd95_pwr_nids[] = अणु
	0x0a, 0x0b, 0x0c, 0x0d
पूर्ण;

अटल पूर्णांक patch_stac92hd95(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec;
	पूर्णांक err;

	err = alloc_stac_spec(codec);
	अगर (err < 0)
		वापस err;

	/* दीर्घer delay needed क्रम D3 */
	codec->core.घातer_caps &= ~AC_PWRST_EPSS;

	spec = codec->spec;
	codec->घातer_save_node = 1;
	spec->linear_tone_beep = 0;
	spec->gen.own_eapd_ctl = 1;
	spec->gen.घातer_करोwn_unused = 1;

	spec->gen.beep_nid = 0x19; /* digital beep */
	spec->pwr_nids = stac92hd95_pwr_nids;
	spec->num_pwrs = ARRAY_SIZE(stac92hd95_pwr_nids);
	spec->शेष_polarity = 0;

	snd_hda_pick_fixup(codec, stac92hd95_models, stac92hd95_fixup_tbl,
			   stac92hd95_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	stac_setup_gpio(codec);

	err = stac_parse_स्वतः_config(codec);
	अगर (err < 0) अणु
		stac_मुक्त(codec);
		वापस err;
	पूर्ण

	codec->proc_widget_hook = stac92hd_proc_hook;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;
पूर्ण

अटल पूर्णांक patch_stac92hd71bxx(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec;
	स्थिर hda_nid_t *unmute_nids = stac92hd71bxx_unmute_nids;
	पूर्णांक err;

	err = alloc_stac_spec(codec);
	अगर (err < 0)
		वापस err;

	spec = codec->spec;
	/* disabled घातer_save_node since it causes noises on a Dell machine */
	/* codec->घातer_save_node = 1; */
	spec->linear_tone_beep = 0;
	spec->gen.own_eapd_ctl = 1;
	spec->gen.घातer_करोwn_unused = 1;
	spec->gen.mixer_nid = 0x17;
	spec->have_spdअगर_mux = 1;

	/* GPIO0 = EAPD */
	spec->gpio_mask = 0x01;
	spec->gpio_dir = 0x01;
	spec->gpio_data = 0x01;

	चयन (codec->core.venकरोr_id) अणु
	हाल 0x111d76b6: /* 4 Port without Analog Mixer */
	हाल 0x111d76b7:
		unmute_nids++;
		अवरोध;
	हाल 0x111d7608: /* 5 Port with Analog Mixer */
		अगर ((codec->core.revision_id & 0xf) == 0 ||
		    (codec->core.revision_id & 0xf) == 1)
			spec->stream_delay = 40; /* 40 milliseconds */

		/* disable VSW */
		unmute_nids++;
		snd_hda_codec_set_pincfg(codec, 0x0f, 0x40f000f0);
		snd_hda_codec_set_pincfg(codec, 0x19, 0x40f000f3);
		अवरोध;
	हाल 0x111d7603: /* 6 Port with Analog Mixer */
		अगर ((codec->core.revision_id & 0xf) == 1)
			spec->stream_delay = 40; /* 40 milliseconds */

		अवरोध;
	पूर्ण

	अगर (get_wcaps_type(get_wcaps(codec, 0x28)) == AC_WID_VOL_KNB)
		snd_hda_add_verbs(codec, stac92hd71bxx_core_init);

	अगर (get_wcaps(codec, 0xa) & AC_WCAP_IN_AMP) अणु
		स्थिर hda_nid_t *p;
		क्रम (p = unmute_nids; *p; p++)
			snd_hda_codec_amp_init_stereo(codec, *p, HDA_INPUT, 0,
						      0xff, 0x00);
	पूर्ण

	spec->aloopback_ctl = &stac92hd71bxx_loopback;
	spec->aloopback_mask = 0x50;
	spec->aloopback_shअगरt = 0;

	spec->घातerकरोwn_adcs = 1;
	spec->gen.beep_nid = 0x26; /* digital beep */
	spec->num_pwrs = ARRAY_SIZE(stac92hd71bxx_pwr_nids);
	spec->pwr_nids = stac92hd71bxx_pwr_nids;

	snd_hda_pick_fixup(codec, stac92hd71bxx_models, stac92hd71bxx_fixup_tbl,
			   stac92hd71bxx_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	stac_setup_gpio(codec);

	err = stac_parse_स्वतः_config(codec);
	अगर (err < 0) अणु
		stac_मुक्त(codec);
		वापस err;
	पूर्ण

	codec->proc_widget_hook = stac92hd7x_proc_hook;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;
पूर्ण

अटल पूर्णांक patch_stac922x(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec;
	पूर्णांक err;

	err = alloc_stac_spec(codec);
	अगर (err < 0)
		वापस err;

	spec = codec->spec;
	spec->linear_tone_beep = 1;
	spec->gen.own_eapd_ctl = 1;

	snd_hda_add_verbs(codec, stac922x_core_init);

	/* Fix Mux capture level; max to 2 */
	snd_hda_override_amp_caps(codec, 0x12, HDA_OUTPUT,
				  (0 << AC_AMPCAP_OFFSET_SHIFT) |
				  (2 << AC_AMPCAP_NUM_STEPS_SHIFT) |
				  (0x27 << AC_AMPCAP_STEP_SIZE_SHIFT) |
				  (0 << AC_AMPCAP_MUTE_SHIFT));

	snd_hda_pick_fixup(codec, stac922x_models, stac922x_fixup_tbl,
			   stac922x_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	err = stac_parse_स्वतः_config(codec);
	अगर (err < 0) अणु
		stac_मुक्त(codec);
		वापस err;
	पूर्ण

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर stac927x_spdअगर_labels[] = अणु
	"Digital Playback", "ADAT", "Analog Mux 1",
	"Analog Mux 2", "Analog Mux 3", शून्य
पूर्ण;

अटल पूर्णांक patch_stac927x(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec;
	पूर्णांक err;

	err = alloc_stac_spec(codec);
	अगर (err < 0)
		वापस err;

	spec = codec->spec;
	spec->linear_tone_beep = 1;
	spec->gen.own_eapd_ctl = 1;
	spec->have_spdअगर_mux = 1;
	spec->spdअगर_labels = stac927x_spdअगर_labels;

	spec->gen.beep_nid = 0x23; /* digital beep */

	/* GPIO0 High = Enable EAPD */
	spec->eapd_mask = spec->gpio_mask = 0x01;
	spec->gpio_dir = spec->gpio_data = 0x01;

	spec->aloopback_ctl = &stac927x_loopback;
	spec->aloopback_mask = 0x40;
	spec->aloopback_shअगरt = 0;
	spec->eapd_चयन = 1;

	snd_hda_pick_fixup(codec, stac927x_models, stac927x_fixup_tbl,
			   stac927x_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	अगर (!spec->volknob_init)
		snd_hda_add_verbs(codec, stac927x_core_init);

	err = stac_parse_स्वतः_config(codec);
	अगर (err < 0) अणु
		stac_मुक्त(codec);
		वापस err;
	पूर्ण

	codec->proc_widget_hook = stac927x_proc_hook;

	/*
	 * !!FIXME!!
	 * The STAC927x seem to require fairly दीर्घ delays क्रम certain
	 * command sequences.  With too लघु delays (even अगर the answer
	 * is set to RIRB properly), it results in the silence output
	 * on some hardwares like Dell.
	 *
	 * The below flag enables the दीर्घer delay (see get_response
	 * in hda_पूर्णांकel.c).
	 */
	codec->bus->core.needs_damn_दीर्घ_delay = 1;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;
पूर्ण

अटल पूर्णांक patch_stac9205(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec;
	पूर्णांक err;

	err = alloc_stac_spec(codec);
	अगर (err < 0)
		वापस err;

	spec = codec->spec;
	spec->linear_tone_beep = 1;
	spec->gen.own_eapd_ctl = 1;
	spec->have_spdअगर_mux = 1;

	spec->gen.beep_nid = 0x23; /* digital beep */

	snd_hda_add_verbs(codec, stac9205_core_init);
	spec->aloopback_ctl = &stac9205_loopback;

	spec->aloopback_mask = 0x40;
	spec->aloopback_shअगरt = 0;
	
	/* GPIO0 High = EAPD */
	spec->eapd_mask = spec->gpio_mask = spec->gpio_dir = 0x1;
	spec->gpio_data = 0x01;

	/* Turn on/off EAPD per HP plugging */
	spec->eapd_चयन = 1;

	snd_hda_pick_fixup(codec, stac9205_models, stac9205_fixup_tbl,
			   stac9205_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	err = stac_parse_स्वतः_config(codec);
	अगर (err < 0) अणु
		stac_मुक्त(codec);
		वापस err;
	पूर्ण

	codec->proc_widget_hook = stac9205_proc_hook;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;
पूर्ण

/*
 * STAC9872 hack
 */

अटल स्थिर काष्ठा hda_verb stac9872_core_init[] = अणु
	अणु0x15, AC_VERB_SET_CONNECT_SEL, 0x1पूर्ण, /* mic-sel: 0a,0d,14,02 */
	अणु0x15, AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_UNMUTEपूर्ण, /* Mic-in -> 0x9 */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_pपूर्णांकbl stac9872_vaio_pin_configs[] = अणु
	अणु 0x0a, 0x03211020 पूर्ण,
	अणु 0x0b, 0x411111f0 पूर्ण,
	अणु 0x0c, 0x411111f0 पूर्ण,
	अणु 0x0d, 0x03a15030 पूर्ण,
	अणु 0x0e, 0x411111f0 पूर्ण,
	अणु 0x0f, 0x90170110 पूर्ण,
	अणु 0x11, 0x411111f0 पूर्ण,
	अणु 0x13, 0x411111f0 पूर्ण,
	अणु 0x14, 0x90a7013e पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_model_fixup stac9872_models[] = अणु
	अणु .id = STAC_9872_VAIO, .name = "vaio" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा hda_fixup stac9872_fixups[] = अणु
	[STAC_9872_VAIO] = अणु
		.type = HDA_FIXUP_PINS,
		.v.pins = stac9872_vaio_pin_configs,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk stac9872_fixup_tbl[] = अणु
	SND_PCI_QUIRK_MASK(0x104d, 0xfff0, 0x81e0,
			   "Sony VAIO F/S", STAC_9872_VAIO),
	अणुपूर्ण /* terminator */
पूर्ण;

अटल पूर्णांक patch_stac9872(काष्ठा hda_codec *codec)
अणु
	काष्ठा sigmatel_spec *spec;
	पूर्णांक err;

	err = alloc_stac_spec(codec);
	अगर (err < 0)
		वापस err;

	spec = codec->spec;
	spec->linear_tone_beep = 1;
	spec->gen.own_eapd_ctl = 1;

	snd_hda_add_verbs(codec, stac9872_core_init);

	snd_hda_pick_fixup(codec, stac9872_models, stac9872_fixup_tbl,
			   stac9872_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	err = stac_parse_स्वतः_config(codec);
	अगर (err < 0) अणु
		stac_मुक्त(codec);
		वापस -EINVAL;
	पूर्ण

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	वापस 0;
पूर्ण


/*
 * patch entries
 */
अटल स्थिर काष्ठा hda_device_id snd_hda_id_sigmatel[] = अणु
	HDA_CODEC_ENTRY(0x83847690, "STAC9200", patch_stac9200),
	HDA_CODEC_ENTRY(0x83847882, "STAC9220 A1", patch_stac922x),
	HDA_CODEC_ENTRY(0x83847680, "STAC9221 A1", patch_stac922x),
	HDA_CODEC_ENTRY(0x83847880, "STAC9220 A2", patch_stac922x),
	HDA_CODEC_ENTRY(0x83847681, "STAC9220D/9223D A2", patch_stac922x),
	HDA_CODEC_ENTRY(0x83847682, "STAC9221 A2", patch_stac922x),
	HDA_CODEC_ENTRY(0x83847683, "STAC9221D A2", patch_stac922x),
	HDA_CODEC_ENTRY(0x83847618, "STAC9227", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847619, "STAC9227", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847638, "STAC92HD700", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847616, "STAC9228", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847617, "STAC9228", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847614, "STAC9229", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847615, "STAC9229", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847620, "STAC9274", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847621, "STAC9274D", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847622, "STAC9273X", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847623, "STAC9273D", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847624, "STAC9272X", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847625, "STAC9272D", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847626, "STAC9271X", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847627, "STAC9271D", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847628, "STAC9274X5NH", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847629, "STAC9274D5NH", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847632, "STAC9202",  patch_stac925x),
	HDA_CODEC_ENTRY(0x83847633, "STAC9202D", patch_stac925x),
	HDA_CODEC_ENTRY(0x83847634, "STAC9250", patch_stac925x),
	HDA_CODEC_ENTRY(0x83847635, "STAC9250D", patch_stac925x),
	HDA_CODEC_ENTRY(0x83847636, "STAC9251", patch_stac925x),
	HDA_CODEC_ENTRY(0x83847637, "STAC9250D", patch_stac925x),
	HDA_CODEC_ENTRY(0x83847645, "92HD206X", patch_stac927x),
	HDA_CODEC_ENTRY(0x83847646, "92HD206D", patch_stac927x),
	/* The following करोes not take पूर्णांकo account .id=0x83847661 when subsys =
	 * 104D0C00 which is STAC9225s. Because of this, some SZ Notebooks are
	 * currently not fully supported.
	 */
	HDA_CODEC_ENTRY(0x83847661, "CXD9872RD/K", patch_stac9872),
	HDA_CODEC_ENTRY(0x83847662, "STAC9872AK", patch_stac9872),
	HDA_CODEC_ENTRY(0x83847664, "CXD9872AKD", patch_stac9872),
	HDA_CODEC_ENTRY(0x83847698, "STAC9205", patch_stac9205),
	HDA_CODEC_ENTRY(0x838476a0, "STAC9205", patch_stac9205),
	HDA_CODEC_ENTRY(0x838476a1, "STAC9205D", patch_stac9205),
	HDA_CODEC_ENTRY(0x838476a2, "STAC9204", patch_stac9205),
	HDA_CODEC_ENTRY(0x838476a3, "STAC9204D", patch_stac9205),
	HDA_CODEC_ENTRY(0x838476a4, "STAC9255", patch_stac9205),
	HDA_CODEC_ENTRY(0x838476a5, "STAC9255D", patch_stac9205),
	HDA_CODEC_ENTRY(0x838476a6, "STAC9254", patch_stac9205),
	HDA_CODEC_ENTRY(0x838476a7, "STAC9254D", patch_stac9205),
	HDA_CODEC_ENTRY(0x111d7603, "92HD75B3X5", patch_stac92hd71bxx),
	HDA_CODEC_ENTRY(0x111d7604, "92HD83C1X5", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76d4, "92HD83C1C5", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d7605, "92HD81B1X5", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76d5, "92HD81B1C5", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76d1, "92HD87B1/3", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76d9, "92HD87B2/4", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d7666, "92HD88B3", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d7667, "92HD88B1", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d7668, "92HD88B2", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d7669, "92HD88B4", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d7608, "92HD75B2X5", patch_stac92hd71bxx),
	HDA_CODEC_ENTRY(0x111d7674, "92HD73D1X5", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d7675, "92HD73C1X5", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d7676, "92HD73E1X5", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d7695, "92HD95", patch_stac92hd95),
	HDA_CODEC_ENTRY(0x111d76b0, "92HD71B8X", patch_stac92hd71bxx),
	HDA_CODEC_ENTRY(0x111d76b1, "92HD71B8X", patch_stac92hd71bxx),
	HDA_CODEC_ENTRY(0x111d76b2, "92HD71B7X", patch_stac92hd71bxx),
	HDA_CODEC_ENTRY(0x111d76b3, "92HD71B7X", patch_stac92hd71bxx),
	HDA_CODEC_ENTRY(0x111d76b4, "92HD71B6X", patch_stac92hd71bxx),
	HDA_CODEC_ENTRY(0x111d76b5, "92HD71B6X", patch_stac92hd71bxx),
	HDA_CODEC_ENTRY(0x111d76b6, "92HD71B5X", patch_stac92hd71bxx),
	HDA_CODEC_ENTRY(0x111d76b7, "92HD71B5X", patch_stac92hd71bxx),
	HDA_CODEC_ENTRY(0x111d76c0, "92HD89C3", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d76c1, "92HD89C2", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d76c2, "92HD89C1", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d76c3, "92HD89B3", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d76c4, "92HD89B2", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d76c5, "92HD89B1", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d76c6, "92HD89E3", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d76c7, "92HD89E2", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d76c8, "92HD89E1", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d76c9, "92HD89D3", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d76ca, "92HD89D2", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d76cb, "92HD89D1", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d76cc, "92HD89F3", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d76cd, "92HD89F2", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d76ce, "92HD89F1", patch_stac92hd73xx),
	HDA_CODEC_ENTRY(0x111d76df, "92HD93BXX", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76e0, "92HD91BXX", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76e3, "92HD98BXX", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76e5, "92HD99BXX", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76e7, "92HD90BXX", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76e8, "92HD66B1X5", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76e9, "92HD66B2X5", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76ea, "92HD66B3X5", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76eb, "92HD66C1X5", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76ec, "92HD66C2X5", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76ed, "92HD66C3X5", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76ee, "92HD66B1X3", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76ef, "92HD66B2X3", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76f0, "92HD66B3X3", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76f1, "92HD66C1X3", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76f2, "92HD66C2X3", patch_stac92hd83xxx),
	HDA_CODEC_ENTRY(0x111d76f3, "92HD66C3/65", patch_stac92hd83xxx),
	अणुपूर्ण /* terminator */
पूर्ण;
MODULE_DEVICE_TABLE(hdaudio, snd_hda_id_sigmatel);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("IDT/Sigmatel HD-audio codec");

अटल काष्ठा hda_codec_driver sigmatel_driver = अणु
	.id = snd_hda_id_sigmatel,
पूर्ण;

module_hda_codec_driver(sigmatel_driver);
