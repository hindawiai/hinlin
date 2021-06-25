<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Generic BIOS स्वतः-parser helper functions क्रम HD-audio
 *
 * Copyright (c) 2012 Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित __SOUND_HDA_GENERIC_H
#घोषणा __SOUND_HDA_GENERIC_H

#समावेश <linux/leds.h>

/* table entry क्रम multi-io paths */
काष्ठा hda_multi_io अणु
	hda_nid_t pin;		/* multi-io widget pin NID */
	hda_nid_t dac;		/* DAC to be connected */
	अचिन्हित पूर्णांक ctl_in;	/* cached input-pin control value */
पूर्ण;

/* Widget connection path
 *
 * For output, stored in the order of DAC -> ... -> pin,
 * क्रम input, pin -> ... -> ADC.
 *
 * idx[i] contains the source index number to select on of the widget path[i];
 * e.g. idx[1] is the index of the DAC (path[0]) selected by path[1] widget
 * multi[] indicates whether it's a selector widget with multi-connectors
 * (i.e. the connection selection is mandatory)
 * vol_ctl and mute_ctl contains the NIDs क्रम the asचिन्हित mixers
 */

#घोषणा MAX_NID_PATH_DEPTH	10

क्रमागत अणु
	NID_PATH_VOL_CTL,
	NID_PATH_MUTE_CTL,
	NID_PATH_BOOST_CTL,
	NID_PATH_NUM_CTLS
पूर्ण;

काष्ठा nid_path अणु
	पूर्णांक depth;
	hda_nid_t path[MAX_NID_PATH_DEPTH];
	अचिन्हित अक्षर idx[MAX_NID_PATH_DEPTH];
	अचिन्हित अक्षर multi[MAX_NID_PATH_DEPTH];
	अचिन्हित पूर्णांक ctls[NID_PATH_NUM_CTLS]; /* NID_PATH_XXX_CTL */
	bool active:1;		/* activated by driver */
	bool pin_enabled:1;	/* pins are enabled */
	bool pin_fixed:1;	/* path with fixed pin */
	bool stream_enabled:1;	/* stream is active */
पूर्ण;

/* mic/line-in स्वतः चयनing entry */

#घोषणा MAX_AUTO_MIC_PINS	3

काष्ठा स्वतःmic_entry अणु
	hda_nid_t pin;		/* pin */
	पूर्णांक idx;		/* imux index, -1 = invalid */
	अचिन्हित पूर्णांक attr;	/* pin attribute (INPUT_PIN_ATTR_*) */
पूर्ण;

/* active stream id */
क्रमागत अणु STREAM_MULTI_OUT, STREAM_INDEP_HP पूर्ण;

/* PCM hook action */
क्रमागत अणु
	HDA_GEN_PCM_ACT_OPEN,
	HDA_GEN_PCM_ACT_PREPARE,
	HDA_GEN_PCM_ACT_CLEANUP,
	HDA_GEN_PCM_ACT_CLOSE,
पूर्ण;

/* DAC assignment badness table */
काष्ठा badness_table अणु
	पूर्णांक no_primary_dac;	/* no primary DAC */
	पूर्णांक no_dac;		/* no secondary DACs */
	पूर्णांक shared_primary;	/* primary DAC is shared with मुख्य output */
	पूर्णांक shared_surr;	/* secondary DAC shared with मुख्य or primary */
	पूर्णांक shared_clfe;	/* third DAC shared with मुख्य or primary */
	पूर्णांक shared_surr_मुख्य;	/* secondary DAC sahred with मुख्य/DAC0 */
पूर्ण;

बाह्य स्थिर काष्ठा badness_table hda_मुख्य_out_badness;
बाह्य स्थिर काष्ठा badness_table hda_extra_out_badness;

काष्ठा hda_gen_spec अणु
	अक्षर stream_name_analog[32];	/* analog PCM stream */
	स्थिर काष्ठा hda_pcm_stream *stream_analog_playback;
	स्थिर काष्ठा hda_pcm_stream *stream_analog_capture;

	अक्षर stream_name_alt_analog[32]; /* alternative analog PCM stream */
	स्थिर काष्ठा hda_pcm_stream *stream_analog_alt_playback;
	स्थिर काष्ठा hda_pcm_stream *stream_analog_alt_capture;

	अक्षर stream_name_digital[32];	/* digital PCM stream */
	स्थिर काष्ठा hda_pcm_stream *stream_digital_playback;
	स्थिर काष्ठा hda_pcm_stream *stream_digital_capture;

	/* PCM */
	अचिन्हित पूर्णांक active_streams;
	काष्ठा mutex pcm_mutex;

	/* playback */
	काष्ठा hda_multi_out multiout;	/* playback set-up
					 * max_channels, dacs must be set
					 * dig_out_nid and hp_nid are optional
					 */
	hda_nid_t alt_dac_nid;
	hda_nid_t follower_dig_outs[3];	/* optional - क्रम स्वतः-parsing */
	पूर्णांक dig_out_type;

	/* capture */
	अचिन्हित पूर्णांक num_adc_nids;
	hda_nid_t adc_nids[AUTO_CFG_MAX_INS];
	hda_nid_t dig_in_nid;		/* digital-in NID; optional */
	hda_nid_t mixer_nid;		/* analog-mixer NID */
	hda_nid_t mixer_merge_nid;	/* aamix merge-poपूर्णांक NID (optional) */
	स्थिर अक्षर *input_labels[HDA_MAX_NUM_INPUTS];
	पूर्णांक input_label_idxs[HDA_MAX_NUM_INPUTS];

	/* capture setup क्रम dynamic dual-adc चयन */
	hda_nid_t cur_adc;
	अचिन्हित पूर्णांक cur_adc_stream_tag;
	अचिन्हित पूर्णांक cur_adc_क्रमmat;

	/* capture source */
	काष्ठा hda_input_mux input_mux;
	अचिन्हित पूर्णांक cur_mux[3];

	/* channel model */
	/* min_channel_count contains the minimum channel count क्रम primary
	 * outमाला_दो.  When multi_ios is set, the channels can be configured
	 * between min_channel_count and (min_channel_count + multi_ios * 2).
	 *
	 * ext_channel_count contains the current channel count of the primary
	 * out.  This varies in the range above.
	 *
	 * Meanजबतक, स्थिर_channel_count is the channel count क्रम all outमाला_दो
	 * including headphone and speakers.  It's a स्थिरant value, and the
	 * PCM is set up as max(ext_channel_count, स्थिर_channel_count).
	 */
	पूर्णांक min_channel_count;		/* min. channel count क्रम primary out */
	पूर्णांक ext_channel_count;		/* current channel count क्रम primary */
	पूर्णांक स्थिर_channel_count;	/* channel count क्रम all */

	/* PCM inक्रमmation */
	काष्ठा hda_pcm *pcm_rec[3];	/* used in build_pcms() */

	/* dynamic controls, init_verbs and input_mux */
	काष्ठा स्वतः_pin_cfg स्वतःcfg;
	काष्ठा snd_array kctls;
	hda_nid_t निजी_dac_nids[AUTO_CFG_MAX_OUTS];
	hda_nid_t imux_pins[HDA_MAX_NUM_INPUTS];
	अचिन्हित पूर्णांक dyn_adc_idx[HDA_MAX_NUM_INPUTS];
	/* shared hp/mic */
	hda_nid_t shared_mic_vref_pin;
	hda_nid_t hp_mic_pin;
	पूर्णांक hp_mic_mux_idx;

	/* DAC/ADC lists */
	पूर्णांक num_all_dacs;
	hda_nid_t all_dacs[16];
	पूर्णांक num_all_adcs;
	hda_nid_t all_adcs[AUTO_CFG_MAX_INS];

	/* path list */
	काष्ठा snd_array paths;

	/* path indices */
	पूर्णांक out_paths[AUTO_CFG_MAX_OUTS];
	पूर्णांक hp_paths[AUTO_CFG_MAX_OUTS];
	पूर्णांक speaker_paths[AUTO_CFG_MAX_OUTS];
	पूर्णांक aamix_out_paths[3];
	पूर्णांक digout_paths[AUTO_CFG_MAX_OUTS];
	पूर्णांक input_paths[HDA_MAX_NUM_INPUTS][AUTO_CFG_MAX_INS];
	पूर्णांक loopback_paths[HDA_MAX_NUM_INPUTS];
	पूर्णांक loopback_merge_path;
	पूर्णांक digin_path;

	/* स्वतः-mic stuff */
	पूर्णांक am_num_entries;
	काष्ठा स्वतःmic_entry am_entry[MAX_AUTO_MIC_PINS];

	/* क्रम pin sensing */
	/* current status; set in hda_geneic.c */
	अचिन्हित पूर्णांक hp_jack_present:1;
	अचिन्हित पूर्णांक line_jack_present:1;
	अचिन्हित पूर्णांक speaker_muted:1; /* current status of speaker mute */
	अचिन्हित पूर्णांक line_out_muted:1; /* current status of LO mute */

	/* पूर्णांकernal states of स्वतःmute / स्वतःचयन behavior */
	अचिन्हित पूर्णांक स्वतः_mic:1;
	अचिन्हित पूर्णांक स्वतःmute_speaker:1; /* स्वतःmute speaker outमाला_दो */
	अचिन्हित पूर्णांक स्वतःmute_lo:1; /* स्वतःmute LO outमाला_दो */

	/* capabilities detected by parser */
	अचिन्हित पूर्णांक detect_hp:1;	/* Headphone detection enabled */
	अचिन्हित पूर्णांक detect_lo:1;	/* Line-out detection enabled */
	अचिन्हित पूर्णांक स्वतःmute_speaker_possible:1; /* there are speakers and either LO or HP */
	अचिन्हित पूर्णांक स्वतःmute_lo_possible:1;	  /* there are line outs and HP */

	/* additional parameters set by codec drivers */
	अचिन्हित पूर्णांक master_mute:1;	/* master mute over all */
	अचिन्हित पूर्णांक keep_vref_in_स्वतःmute:1; /* Don't clear VREF in स्वतःmute */
	अचिन्हित पूर्णांक line_in_स्वतः_चयन:1; /* allow line-in स्वतः चयन */
	अचिन्हित पूर्णांक स्वतः_mute_via_amp:1; /* स्वतः-mute via amp instead of pinctl */

	/* parser behavior flags; set beक्रमe snd_hda_gen_parse_स्वतः_config() */
	अचिन्हित पूर्णांक suppress_स्वतः_mute:1; /* suppress input jack स्वतः mute */
	अचिन्हित पूर्णांक suppress_स्वतः_mic:1; /* suppress input jack स्वतः चयन */

	/* other parse behavior flags */
	अचिन्हित पूर्णांक need_dac_fix:1; /* need to limit DACs क्रम multi channels */
	अचिन्हित पूर्णांक hp_mic:1; /* Allow HP as a mic-in */
	अचिन्हित पूर्णांक suppress_hp_mic_detect:1; /* Don't detect HP/mic */
	अचिन्हित पूर्णांक no_primary_hp:1; /* Don't prefer HP pins to speaker pins */
	अचिन्हित पूर्णांक no_multi_io:1; /* Don't try multi I/O config */
	अचिन्हित पूर्णांक multi_cap_vol:1; /* allow multiple capture xxx volumes */
	अचिन्हित पूर्णांक inv_dmic_split:1; /* inverted dmic w/a क्रम conexant */
	अचिन्हित पूर्णांक own_eapd_ctl:1; /* set EAPD by own function */
	अचिन्हित पूर्णांक keep_eapd_on:1; /* करोn't turn off EAPD स्वतःmatically */
	अचिन्हित पूर्णांक vmaster_mute_led:1; /* add SPK-LED flag to vmaster mute चयन */
	अचिन्हित पूर्णांक mic_mute_led:1; /* add MIC-LED flag to capture mute चयन */
	अचिन्हित पूर्णांक indep_hp:1; /* independent HP supported */
	अचिन्हित पूर्णांक prefer_hp_amp:1; /* enable HP amp क्रम speaker अगर any */
	अचिन्हित पूर्णांक add_stereo_mix_input:2; /* add aamix as a capture src */
	अचिन्हित पूर्णांक add_jack_modes:1; /* add i/o jack mode क्रमागत ctls */
	अचिन्हित पूर्णांक घातer_करोwn_unused:1; /* घातer करोwn unused widमाला_लो */
	अचिन्हित पूर्णांक dac_min_mute:1; /* minimal = mute क्रम DACs */
	अचिन्हित पूर्णांक suppress_vmaster:1; /* करोn't create vmaster kctls */
	अचिन्हित पूर्णांक obey_preferred_dacs:1; /* obey preferred_dacs assignment */

	/* other पूर्णांकernal flags */
	अचिन्हित पूर्णांक no_analog:1; /* digital I/O only */
	अचिन्हित पूर्णांक dyn_adc_चयन:1; /* चयन ADCs (क्रम ALC275) */
	अचिन्हित पूर्णांक indep_hp_enabled:1; /* independent HP enabled */
	अचिन्हित पूर्णांक have_aamix_ctl:1;
	अचिन्हित पूर्णांक hp_mic_jack_modes:1;
	अचिन्हित पूर्णांक skip_verbs:1; /* करोn't apply verbs at snd_hda_gen_init() */

	/* additional mute flags (only effective with स्वतः_mute_via_amp=1) */
	u64 mute_bits;

	/* biपंचांगask क्रम skipping volume controls */
	u64 out_vol_mask;

	/* badness tables क्रम output path evaluations */
	स्थिर काष्ठा badness_table *मुख्य_out_badness;
	स्थिर काष्ठा badness_table *extra_out_badness;

	/* preferred pin/DAC pairs; an array of paired NIDs */
	स्थिर hda_nid_t *preferred_dacs;

	/* loopback mixing mode */
	bool aamix_mode;

	/* digital beep */
	hda_nid_t beep_nid;

	/* क्रम भव master */
	hda_nid_t vmaster_nid;
	अचिन्हित पूर्णांक vmaster_tlv[4];
	काष्ठा hda_vmaster_mute_hook vmaster_mute;

	काष्ठा hda_loopback_check loopback;
	काष्ठा snd_array loopback_list;

	/* multi-io */
	पूर्णांक multi_ios;
	काष्ठा hda_multi_io multi_io[4];

	/* hooks */
	व्योम (*init_hook)(काष्ठा hda_codec *codec);
	व्योम (*स्वतःmute_hook)(काष्ठा hda_codec *codec);
	व्योम (*cap_sync_hook)(काष्ठा hda_codec *codec,
			      काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol);

	/* PCM hooks */
	व्योम (*pcm_playback_hook)(काष्ठा hda_pcm_stream *hinfo,
				  काष्ठा hda_codec *codec,
				  काष्ठा snd_pcm_substream *substream,
				  पूर्णांक action);
	व्योम (*pcm_capture_hook)(काष्ठा hda_pcm_stream *hinfo,
				 काष्ठा hda_codec *codec,
				 काष्ठा snd_pcm_substream *substream,
				 पूर्णांक action);

	/* स्वतःmute / स्वतःचयन hooks */
	व्योम (*hp_स्वतःmute_hook)(काष्ठा hda_codec *codec,
				 काष्ठा hda_jack_callback *cb);
	व्योम (*line_स्वतःmute_hook)(काष्ठा hda_codec *codec,
				   काष्ठा hda_jack_callback *cb);
	व्योम (*mic_स्वतःचयन_hook)(काष्ठा hda_codec *codec,
				    काष्ठा hda_jack_callback *cb);
पूर्ण;

/* values क्रम add_stereo_mix_input flag */
क्रमागत अणु
	HDA_HINT_STEREO_MIX_DISABLE,	/* No stereo mix input */
	HDA_HINT_STEREO_MIX_ENABLE,	/* Add stereo mix input */
	HDA_HINT_STEREO_MIX_AUTO,	/* Add only अगर स्वतः-mic is disabled */
पूर्ण;

पूर्णांक snd_hda_gen_spec_init(काष्ठा hda_gen_spec *spec);

पूर्णांक snd_hda_gen_init(काष्ठा hda_codec *codec);
व्योम snd_hda_gen_मुक्त(काष्ठा hda_codec *codec);

पूर्णांक snd_hda_get_path_idx(काष्ठा hda_codec *codec, काष्ठा nid_path *path);
काष्ठा nid_path *snd_hda_get_path_from_idx(काष्ठा hda_codec *codec, पूर्णांक idx);
काष्ठा nid_path *
snd_hda_add_new_path(काष्ठा hda_codec *codec, hda_nid_t from_nid,
		     hda_nid_t to_nid, पूर्णांक anchor_nid);
व्योम snd_hda_activate_path(काष्ठा hda_codec *codec, काष्ठा nid_path *path,
			   bool enable, bool add_aamix);

काष्ठा snd_kcontrol_new *
snd_hda_gen_add_kctl(काष्ठा hda_gen_spec *spec, स्थिर अक्षर *name,
		     स्थिर काष्ठा snd_kcontrol_new *temp);

पूर्णांक snd_hda_gen_parse_स्वतः_config(काष्ठा hda_codec *codec,
				  काष्ठा स्वतः_pin_cfg *cfg);
पूर्णांक snd_hda_gen_build_controls(काष्ठा hda_codec *codec);
पूर्णांक snd_hda_gen_build_pcms(काष्ठा hda_codec *codec);
व्योम snd_hda_gen_reboot_notअगरy(काष्ठा hda_codec *codec);

/* standard jack event callbacks */
व्योम snd_hda_gen_hp_स्वतःmute(काष्ठा hda_codec *codec,
			     काष्ठा hda_jack_callback *jack);
व्योम snd_hda_gen_line_स्वतःmute(काष्ठा hda_codec *codec,
			       काष्ठा hda_jack_callback *jack);
व्योम snd_hda_gen_mic_स्वतःचयन(काष्ठा hda_codec *codec,
				काष्ठा hda_jack_callback *jack);
व्योम snd_hda_gen_update_outमाला_दो(काष्ठा hda_codec *codec);

#अगर_घोषित CONFIG_PM
पूर्णांक snd_hda_gen_check_घातer_status(काष्ठा hda_codec *codec, hda_nid_t nid);
#पूर्ण_अगर
अचिन्हित पूर्णांक snd_hda_gen_path_घातer_filter(काष्ठा hda_codec *codec,
					   hda_nid_t nid,
					   अचिन्हित पूर्णांक घातer_state);
व्योम snd_hda_gen_stream_pm(काष्ठा hda_codec *codec, hda_nid_t nid, bool on);
पूर्णांक snd_hda_gen_fix_pin_घातer(काष्ठा hda_codec *codec, hda_nid_t pin);

पूर्णांक snd_hda_gen_add_mute_led_cdev(काष्ठा hda_codec *codec,
				  पूर्णांक (*callback)(काष्ठा led_classdev *,
						  क्रमागत led_brightness));
पूर्णांक snd_hda_gen_add_micmute_led_cdev(काष्ठा hda_codec *codec,
				     पूर्णांक (*callback)(काष्ठा led_classdev *,
						     क्रमागत led_brightness));

#पूर्ण_अगर /* __SOUND_HDA_GENERIC_H */
