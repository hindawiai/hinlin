<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Jack-detection handling क्रम HD-audio
 *
 * Copyright (c) 2011 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/jack.h>
#समावेश <sound/hda_codec.h>
#समावेश "hda_local.h"
#समावेश "hda_auto_parser.h"
#समावेश "hda_jack.h"

/**
 * is_jack_detectable - Check whether the given pin is jack-detectable
 * @codec: the HDA codec
 * @nid: pin NID
 *
 * Check whether the given pin is capable to report the jack detection.
 * The jack detection might not work by various reasons, e.g. the jack
 * detection is prohibited in the codec level, the pin config has
 * AC_DEFCFG_MISC_NO_PRESENCE bit, no unsol support, etc.
 */
bool is_jack_detectable(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अगर (codec->no_jack_detect)
		वापस false;
	अगर (!(snd_hda_query_pin_caps(codec, nid) & AC_PINCAP_PRES_DETECT))
		वापस false;
	अगर (get_defcfg_misc(snd_hda_codec_get_pincfg(codec, nid)) &
	     AC_DEFCFG_MISC_NO_PRESENCE)
		वापस false;
	अगर (!(get_wcaps(codec, nid) & AC_WCAP_UNSOL_CAP) &&
	    !codec->jackpoll_पूर्णांकerval)
		वापस false;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(is_jack_detectable);

/* execute pin sense measurement */
अटल u32 पढ़ो_pin_sense(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dev_id)
अणु
	u32 pincap;
	u32 val;

	अगर (!codec->no_trigger_sense) अणु
		pincap = snd_hda_query_pin_caps(codec, nid);
		अगर (pincap & AC_PINCAP_TRIG_REQ) /* need trigger? */
			snd_hda_codec_पढ़ो(codec, nid, 0,
					AC_VERB_SET_PIN_SENSE, 0);
	पूर्ण
	val = snd_hda_codec_पढ़ो(codec, nid, 0,
				  AC_VERB_GET_PIN_SENSE, dev_id);
	अगर (codec->inv_jack_detect)
		val ^= AC_PINSENSE_PRESENCE;
	वापस val;
पूर्ण

/**
 * snd_hda_jack_tbl_get_mst - query the jack-table entry क्रम the given NID
 * @codec: the HDA codec
 * @nid: pin NID to refer to
 * @dev_id: pin device entry id
 */
काष्ठा hda_jack_tbl *
snd_hda_jack_tbl_get_mst(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dev_id)
अणु
	काष्ठा hda_jack_tbl *jack = codec->jacktbl.list;
	पूर्णांक i;

	अगर (!nid || !jack)
		वापस शून्य;
	क्रम (i = 0; i < codec->jacktbl.used; i++, jack++)
		अगर (jack->nid == nid && jack->dev_id == dev_id)
			वापस jack;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_jack_tbl_get_mst);

/**
 * snd_hda_jack_tbl_get_from_tag - query the jack-table entry क्रम the given tag
 * @codec: the HDA codec
 * @tag: tag value to refer to
 * @dev_id: pin device entry id
 */
काष्ठा hda_jack_tbl *
snd_hda_jack_tbl_get_from_tag(काष्ठा hda_codec *codec,
			      अचिन्हित अक्षर tag, पूर्णांक dev_id)
अणु
	काष्ठा hda_jack_tbl *jack = codec->jacktbl.list;
	पूर्णांक i;

	अगर (!tag || !jack)
		वापस शून्य;
	क्रम (i = 0; i < codec->jacktbl.used; i++, jack++)
		अगर (jack->tag == tag && jack->dev_id == dev_id)
			वापस jack;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_jack_tbl_get_from_tag);

अटल काष्ठा hda_jack_tbl *
any_jack_tbl_get_from_nid(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	काष्ठा hda_jack_tbl *jack = codec->jacktbl.list;
	पूर्णांक i;

	अगर (!nid || !jack)
		वापस शून्य;
	क्रम (i = 0; i < codec->jacktbl.used; i++, jack++)
		अगर (jack->nid == nid)
			वापस jack;
	वापस शून्य;
पूर्ण

/**
 * snd_hda_jack_tbl_new - create a jack-table entry क्रम the given NID
 * @codec: the HDA codec
 * @nid: pin NID to assign
 * @dev_id: pin device entry id
 */
अटल काष्ठा hda_jack_tbl *
snd_hda_jack_tbl_new(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dev_id)
अणु
	काष्ठा hda_jack_tbl *jack =
		snd_hda_jack_tbl_get_mst(codec, nid, dev_id);
	काष्ठा hda_jack_tbl *existing_nid_jack =
		any_jack_tbl_get_from_nid(codec, nid);

	WARN_ON(dev_id != 0 && !codec->dp_mst);

	अगर (jack)
		वापस jack;
	jack = snd_array_new(&codec->jacktbl);
	अगर (!jack)
		वापस शून्य;
	jack->nid = nid;
	jack->dev_id = dev_id;
	jack->jack_dirty = 1;
	अगर (existing_nid_jack) अणु
		jack->tag = existing_nid_jack->tag;

		/*
		 * Copy jack_detect from existing_nid_jack to aव्योम
		 * snd_hda_jack_detect_enable_callback_mst() making multiple
		 * SET_UNSOLICITED_ENABLE calls on the same pin.
		 */
		jack->jack_detect = existing_nid_jack->jack_detect;
	पूर्ण अन्यथा अणु
		jack->tag = codec->jacktbl.used;
	पूर्ण

	वापस jack;
पूर्ण

व्योम snd_hda_jack_tbl_clear(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_jack_tbl *jack = codec->jacktbl.list;
	पूर्णांक i;

	क्रम (i = 0; i < codec->jacktbl.used; i++, jack++) अणु
		काष्ठा hda_jack_callback *cb, *next;

		/* मुक्त jack instances manually when clearing/reconfiguring */
		अगर (!codec->bus->shutकरोwn && jack->jack)
			snd_device_मुक्त(codec->card, jack->jack);

		क्रम (cb = jack->callback; cb; cb = next) अणु
			next = cb->next;
			kमुक्त(cb);
		पूर्ण
	पूर्ण
	snd_array_मुक्त(&codec->jacktbl);
पूर्ण

#घोषणा get_jack_plug_state(sense) !!(sense & AC_PINSENSE_PRESENCE)

/* update the cached value and notअगरication flag अगर needed */
अटल व्योम jack_detect_update(काष्ठा hda_codec *codec,
			       काष्ठा hda_jack_tbl *jack)
अणु
	अगर (!jack->jack_dirty)
		वापस;

	अगर (jack->phantom_jack)
		jack->pin_sense = AC_PINSENSE_PRESENCE;
	अन्यथा
		jack->pin_sense = पढ़ो_pin_sense(codec, jack->nid,
						 jack->dev_id);

	/* A gating jack indicates the jack is invalid अगर gating is unplugged */
	अगर (jack->gating_jack &&
	    !snd_hda_jack_detect_mst(codec, jack->gating_jack, jack->dev_id))
		jack->pin_sense &= ~AC_PINSENSE_PRESENCE;

	jack->jack_dirty = 0;

	/* If a jack is gated by this one update it. */
	अगर (jack->gated_jack) अणु
		काष्ठा hda_jack_tbl *gated =
			snd_hda_jack_tbl_get_mst(codec, jack->gated_jack,
						 jack->dev_id);
		अगर (gated) अणु
			gated->jack_dirty = 1;
			jack_detect_update(codec, gated);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * snd_hda_jack_set_dirty_all - Mark all the cached as dirty
 * @codec: the HDA codec
 *
 * This function sets the dirty flag to all entries of jack table.
 * It's called from the resume path in hda_codec.c.
 */
व्योम snd_hda_jack_set_dirty_all(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_jack_tbl *jack = codec->jacktbl.list;
	पूर्णांक i;

	क्रम (i = 0; i < codec->jacktbl.used; i++, jack++)
		अगर (jack->nid)
			jack->jack_dirty = 1;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_jack_set_dirty_all);

/**
 * snd_hda_jack_pin_sense - execute pin sense measurement
 * @codec: the CODEC to sense
 * @nid: the pin NID to sense
 * @dev_id: pin device entry id
 *
 * Execute necessary pin sense measurement and वापस its Presence Detect,
 * Impedance, ELD Valid etc. status bits.
 */
u32 snd_hda_jack_pin_sense(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dev_id)
अणु
	काष्ठा hda_jack_tbl *jack =
		snd_hda_jack_tbl_get_mst(codec, nid, dev_id);
	अगर (jack) अणु
		jack_detect_update(codec, jack);
		वापस jack->pin_sense;
	पूर्ण
	वापस पढ़ो_pin_sense(codec, nid, dev_id);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_jack_pin_sense);

/**
 * snd_hda_jack_detect_state_mst - query pin Presence Detect status
 * @codec: the CODEC to sense
 * @nid: the pin NID to sense
 * @dev_id: pin device entry id
 *
 * Query and वापस the pin's Presence Detect status, as either
 * HDA_JACK_NOT_PRESENT, HDA_JACK_PRESENT or HDA_JACK_PHANTOM.
 */
पूर्णांक snd_hda_jack_detect_state_mst(काष्ठा hda_codec *codec,
				  hda_nid_t nid, पूर्णांक dev_id)
अणु
	काष्ठा hda_jack_tbl *jack =
		snd_hda_jack_tbl_get_mst(codec, nid, dev_id);
	अगर (jack && jack->phantom_jack)
		वापस HDA_JACK_PHANTOM;
	अन्यथा अगर (snd_hda_jack_pin_sense(codec, nid, dev_id) &
		 AC_PINSENSE_PRESENCE)
		वापस HDA_JACK_PRESENT;
	अन्यथा
		वापस HDA_JACK_NOT_PRESENT;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_jack_detect_state_mst);

अटल काष्ठा hda_jack_callback *
find_callback_from_list(काष्ठा hda_jack_tbl *jack,
			hda_jack_callback_fn func)
अणु
	काष्ठा hda_jack_callback *cb;

	अगर (!func)
		वापस शून्य;

	क्रम (cb = jack->callback; cb; cb = cb->next) अणु
		अगर (cb->func == func)
			वापस cb;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * snd_hda_jack_detect_enable_callback_mst - enable the jack-detection
 * @codec: the HDA codec
 * @nid: pin NID to enable
 * @func: callback function to रेजिस्टर
 * @dev_id: pin device entry id
 *
 * In the हाल of error, the वापस value will be a poपूर्णांकer embedded with
 * त्रुटि_सं.  Check and handle the वापस value appropriately with standard
 * macros such as @IS_ERR() and @PTR_ERR().
 */
काष्ठा hda_jack_callback *
snd_hda_jack_detect_enable_callback_mst(काष्ठा hda_codec *codec, hda_nid_t nid,
					पूर्णांक dev_id, hda_jack_callback_fn func)
अणु
	काष्ठा hda_jack_tbl *jack;
	काष्ठा hda_jack_callback *callback = शून्य;
	पूर्णांक err;

	jack = snd_hda_jack_tbl_new(codec, nid, dev_id);
	अगर (!jack)
		वापस ERR_PTR(-ENOMEM);

	callback = find_callback_from_list(jack, func);

	अगर (func && !callback) अणु
		callback = kzalloc(माप(*callback), GFP_KERNEL);
		अगर (!callback)
			वापस ERR_PTR(-ENOMEM);
		callback->func = func;
		callback->nid = jack->nid;
		callback->dev_id = jack->dev_id;
		callback->next = jack->callback;
		jack->callback = callback;
	पूर्ण

	अगर (jack->jack_detect)
		वापस callback; /* alपढ़ोy रेजिस्टरed */
	jack->jack_detect = 1;
	अगर (codec->jackpoll_पूर्णांकerval > 0)
		वापस callback; /* No unsol अगर we're polling instead */
	err = snd_hda_codec_ग_लिखो_cache(codec, nid, 0,
					 AC_VERB_SET_UNSOLICITED_ENABLE,
					 AC_USRSP_EN | jack->tag);
	अगर (err < 0)
		वापस ERR_PTR(err);
	वापस callback;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_jack_detect_enable_callback_mst);

/**
 * snd_hda_jack_detect_enable - Enable the jack detection on the given pin
 * @codec: the HDA codec
 * @nid: pin NID to enable jack detection
 * @dev_id: pin device entry id
 *
 * Enable the jack detection with the शेष callback.  Returns zero अगर
 * successful or a negative error code.
 */
पूर्णांक snd_hda_jack_detect_enable(काष्ठा hda_codec *codec, hda_nid_t nid,
			       पूर्णांक dev_id)
अणु
	वापस PTR_ERR_OR_ZERO(snd_hda_jack_detect_enable_callback_mst(codec,
								       nid,
								       dev_id,
								       शून्य));
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_jack_detect_enable);

/**
 * snd_hda_jack_set_gating_jack - Set gating jack.
 * @codec: the HDA codec
 * @gated_nid: gated pin NID
 * @gating_nid: gating pin NID
 *
 * Indicates the gated jack is only valid when the gating jack is plugged.
 */
पूर्णांक snd_hda_jack_set_gating_jack(काष्ठा hda_codec *codec, hda_nid_t gated_nid,
				 hda_nid_t gating_nid)
अणु
	काष्ठा hda_jack_tbl *gated = snd_hda_jack_tbl_new(codec, gated_nid, 0);
	काष्ठा hda_jack_tbl *gating =
		snd_hda_jack_tbl_new(codec, gating_nid, 0);

	WARN_ON(codec->dp_mst);

	अगर (!gated || !gating)
		वापस -EINVAL;

	gated->gating_jack = gating_nid;
	gating->gated_jack = gated_nid;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_jack_set_gating_jack);

/**
 * snd_hda_jack_bind_keymap - bind keys generated from one NID to another jack.
 * @codec: the HDA codec
 * @key_nid: key event is generated by this pin NID
 * @keymap: map of key type and key code
 * @jack_nid: key reports to the jack of this pin NID
 *
 * This function is used in the हाल of key is generated from one NID जबतक is
 * reported to the jack of another NID.
 */
पूर्णांक snd_hda_jack_bind_keymap(काष्ठा hda_codec *codec, hda_nid_t key_nid,
			     स्थिर काष्ठा hda_jack_keymap *keymap,
			     hda_nid_t jack_nid)
अणु
	स्थिर काष्ठा hda_jack_keymap *map;
	काष्ठा hda_jack_tbl *key_gen = snd_hda_jack_tbl_get(codec, key_nid);
	काष्ठा hda_jack_tbl *report_to = snd_hda_jack_tbl_get(codec, jack_nid);

	WARN_ON(codec->dp_mst);

	अगर (!key_gen || !report_to || !report_to->jack)
		वापस -EINVAL;

	key_gen->key_report_jack = jack_nid;

	अगर (keymap)
		क्रम (map = keymap; map->type; map++)
			snd_jack_set_key(report_to->jack, map->type, map->key);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_jack_bind_keymap);

/**
 * snd_hda_jack_set_button_state - report button event to the hda_jack_tbl button_state.
 * @codec: the HDA codec
 * @jack_nid: the button event reports to the jack_tbl of this NID
 * @button_state: the button event captured by codec
 *
 * Codec driver calls this function to report the button event.
 */
व्योम snd_hda_jack_set_button_state(काष्ठा hda_codec *codec, hda_nid_t jack_nid,
				   पूर्णांक button_state)
अणु
	काष्ठा hda_jack_tbl *jack = snd_hda_jack_tbl_get(codec, jack_nid);

	अगर (!jack)
		वापस;

	अगर (jack->key_report_jack) अणु
		काष्ठा hda_jack_tbl *report_to =
			snd_hda_jack_tbl_get(codec, jack->key_report_jack);

		अगर (report_to) अणु
			report_to->button_state = button_state;
			वापस;
		पूर्ण
	पूर्ण

	jack->button_state = button_state;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_jack_set_button_state);

/**
 * snd_hda_jack_report_sync - sync the states of all jacks and report अगर changed
 * @codec: the HDA codec
 */
व्योम snd_hda_jack_report_sync(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_jack_tbl *jack;
	पूर्णांक i, state;

	/* update all jacks at first */
	jack = codec->jacktbl.list;
	क्रम (i = 0; i < codec->jacktbl.used; i++, jack++)
		अगर (jack->nid)
			jack_detect_update(codec, jack);

	/* report the updated jacks; it's करोne after updating all jacks
	 * to make sure that all gating jacks properly have been set
	 */
	jack = codec->jacktbl.list;
	क्रम (i = 0; i < codec->jacktbl.used; i++, jack++)
		अगर (jack->nid) अणु
			अगर (!jack->jack || jack->block_report)
				जारी;
			state = jack->button_state;
			अगर (get_jack_plug_state(jack->pin_sense))
				state |= jack->type;
			snd_jack_report(jack->jack, state);
			अगर (jack->button_state) अणु
				snd_jack_report(jack->jack,
						state & ~jack->button_state);
				jack->button_state = 0; /* button released */
			पूर्ण
		पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_jack_report_sync);

/* guess the jack type from the pin-config */
अटल पूर्णांक get_input_jack_type(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अचिन्हित पूर्णांक def_conf = snd_hda_codec_get_pincfg(codec, nid);
	चयन (get_defcfg_device(def_conf)) अणु
	हाल AC_JACK_LINE_OUT:
	हाल AC_JACK_SPEAKER:
		वापस SND_JACK_LINEOUT;
	हाल AC_JACK_HP_OUT:
		वापस SND_JACK_HEADPHONE;
	हाल AC_JACK_SPDIF_OUT:
	हाल AC_JACK_DIG_OTHER_OUT:
		वापस SND_JACK_AVOUT;
	हाल AC_JACK_MIC_IN:
		वापस SND_JACK_MICROPHONE;
	शेष:
		वापस SND_JACK_LINEIN;
	पूर्ण
पूर्ण

अटल व्योम hda_मुक्त_jack_priv(काष्ठा snd_jack *jack)
अणु
	काष्ठा hda_jack_tbl *jacks = jack->निजी_data;
	jacks->nid = 0;
	jacks->jack = शून्य;
पूर्ण

/**
 * snd_hda_jack_add_kctl_mst - Add a kctl क्रम the given pin
 * @codec: the HDA codec
 * @nid: pin NID to assign
 * @dev_id : pin device entry id
 * @name: string name क्रम the jack
 * @phantom_jack: flag to deal as a phantom jack
 * @type: jack type bits to be reported, 0 क्रम guessing from pincfg
 * @keymap: optional jack / key mapping
 *
 * This assigns a jack-detection kctl to the given pin.  The kcontrol
 * will have the given name and index.
 */
पूर्णांक snd_hda_jack_add_kctl_mst(काष्ठा hda_codec *codec, hda_nid_t nid,
			      पूर्णांक dev_id, स्थिर अक्षर *name, bool phantom_jack,
			      पूर्णांक type, स्थिर काष्ठा hda_jack_keymap *keymap)
अणु
	काष्ठा hda_jack_tbl *jack;
	स्थिर काष्ठा hda_jack_keymap *map;
	पूर्णांक err, state, buttons;

	jack = snd_hda_jack_tbl_new(codec, nid, dev_id);
	अगर (!jack)
		वापस 0;
	अगर (jack->jack)
		वापस 0; /* alपढ़ोy created */

	अगर (!type)
		type = get_input_jack_type(codec, nid);

	buttons = 0;
	अगर (keymap) अणु
		क्रम (map = keymap; map->type; map++)
			buttons |= map->type;
	पूर्ण

	err = snd_jack_new(codec->card, name, type | buttons,
			   &jack->jack, true, phantom_jack);
	अगर (err < 0)
		वापस err;

	jack->phantom_jack = !!phantom_jack;
	jack->type = type;
	jack->button_state = 0;
	jack->jack->निजी_data = jack;
	jack->jack->निजी_मुक्त = hda_मुक्त_jack_priv;
	अगर (keymap) अणु
		क्रम (map = keymap; map->type; map++)
			snd_jack_set_key(jack->jack, map->type, map->key);
	पूर्ण

	state = snd_hda_jack_detect_mst(codec, nid, dev_id);
	snd_jack_report(jack->jack, state ? jack->type : 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_jack_add_kctl_mst);

अटल पूर्णांक add_jack_kctl(काष्ठा hda_codec *codec, hda_nid_t nid,
			 स्थिर काष्ठा स्वतः_pin_cfg *cfg,
			 स्थिर अक्षर *base_name)
अणु
	अचिन्हित पूर्णांक def_conf, conn;
	अक्षर name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
	पूर्णांक err;
	bool phantom_jack;

	WARN_ON(codec->dp_mst);

	अगर (!nid)
		वापस 0;
	def_conf = snd_hda_codec_get_pincfg(codec, nid);
	conn = get_defcfg_connect(def_conf);
	अगर (conn == AC_JACK_PORT_NONE)
		वापस 0;
	phantom_jack = (conn != AC_JACK_PORT_COMPLEX) ||
		       !is_jack_detectable(codec, nid);

	अगर (base_name)
		strscpy(name, base_name, माप(name));
	अन्यथा
		snd_hda_get_pin_label(codec, nid, cfg, name, माप(name), शून्य);
	अगर (phantom_jack)
		/* Example final name: "Internal Mic Phantom Jack" */
		म_जोड़न(name, " Phantom", माप(name) - म_माप(name) - 1);
	err = snd_hda_jack_add_kctl(codec, nid, name, phantom_jack, 0, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!phantom_jack)
		वापस snd_hda_jack_detect_enable(codec, nid, 0);
	वापस 0;
पूर्ण

/**
 * snd_hda_jack_add_kctls - Add kctls क्रम all pins included in the given pincfg
 * @codec: the HDA codec
 * @cfg: pin config table to parse
 */
पूर्णांक snd_hda_jack_add_kctls(काष्ठा hda_codec *codec,
			   स्थिर काष्ठा स्वतः_pin_cfg *cfg)
अणु
	स्थिर hda_nid_t *p;
	पूर्णांक i, err;

	क्रम (i = 0; i < cfg->num_inमाला_दो; i++) अणु
		/* If we have headphone mics; make sure they get the right name
		   beक्रमe grabbed by output pins */
		अगर (cfg->inमाला_दो[i].is_headphone_mic) अणु
			अगर (स्वतः_cfg_hp_outs(cfg) == 1)
				err = add_jack_kctl(codec, स्वतः_cfg_hp_pins(cfg)[0],
						    cfg, "Headphone Mic");
			अन्यथा
				err = add_jack_kctl(codec, cfg->inमाला_दो[i].pin,
						    cfg, "Headphone Mic");
		पूर्ण अन्यथा
			err = add_jack_kctl(codec, cfg->inमाला_दो[i].pin, cfg,
					    शून्य);
		अगर (err < 0)
			वापस err;
	पूर्ण

	क्रम (i = 0, p = cfg->line_out_pins; i < cfg->line_outs; i++, p++) अणु
		err = add_jack_kctl(codec, *p, cfg, शून्य);
		अगर (err < 0)
			वापस err;
	पूर्ण
	क्रम (i = 0, p = cfg->hp_pins; i < cfg->hp_outs; i++, p++) अणु
		अगर (*p == *cfg->line_out_pins) /* might be duplicated */
			अवरोध;
		err = add_jack_kctl(codec, *p, cfg, शून्य);
		अगर (err < 0)
			वापस err;
	पूर्ण
	क्रम (i = 0, p = cfg->speaker_pins; i < cfg->speaker_outs; i++, p++) अणु
		अगर (*p == *cfg->line_out_pins) /* might be duplicated */
			अवरोध;
		err = add_jack_kctl(codec, *p, cfg, शून्य);
		अगर (err < 0)
			वापस err;
	पूर्ण
	क्रम (i = 0, p = cfg->dig_out_pins; i < cfg->dig_outs; i++, p++) अणु
		err = add_jack_kctl(codec, *p, cfg, शून्य);
		अगर (err < 0)
			वापस err;
	पूर्ण
	err = add_jack_kctl(codec, cfg->dig_in_pin, cfg, शून्य);
	अगर (err < 0)
		वापस err;
	err = add_jack_kctl(codec, cfg->mono_out_pin, cfg, शून्य);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_jack_add_kctls);

अटल व्योम call_jack_callback(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक res,
			       काष्ठा hda_jack_tbl *jack)
अणु
	काष्ठा hda_jack_callback *cb;

	क्रम (cb = jack->callback; cb; cb = cb->next) अणु
		cb->jack = jack;
		cb->unsol_res = res;
		cb->func(codec, cb);
	पूर्ण
	अगर (jack->gated_jack) अणु
		काष्ठा hda_jack_tbl *gated =
			snd_hda_jack_tbl_get_mst(codec, jack->gated_jack,
						 jack->dev_id);
		अगर (gated) अणु
			क्रम (cb = gated->callback; cb; cb = cb->next) अणु
				cb->jack = gated;
				cb->unsol_res = res;
				cb->func(codec, cb);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * snd_hda_jack_unsol_event - Handle an unsolicited event
 * @codec: the HDA codec
 * @res: the unsolicited event data
 */
व्योम snd_hda_jack_unsol_event(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक res)
अणु
	काष्ठा hda_jack_tbl *event;
	पूर्णांक tag = (res & AC_UNSOL_RES_TAG) >> AC_UNSOL_RES_TAG_SHIFT;

	अगर (codec->dp_mst) अणु
		पूर्णांक dev_entry =
			(res & AC_UNSOL_RES_DE) >> AC_UNSOL_RES_DE_SHIFT;

		event = snd_hda_jack_tbl_get_from_tag(codec, tag, dev_entry);
	पूर्ण अन्यथा अणु
		event = snd_hda_jack_tbl_get_from_tag(codec, tag, 0);
	पूर्ण
	अगर (!event)
		वापस;

	अगर (event->key_report_jack) अणु
		काष्ठा hda_jack_tbl *report_to =
			snd_hda_jack_tbl_get_mst(codec, event->key_report_jack,
						 event->dev_id);
		अगर (report_to)
			report_to->jack_dirty = 1;
	पूर्ण अन्यथा
		event->jack_dirty = 1;

	call_jack_callback(codec, res, event);
	snd_hda_jack_report_sync(codec);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_jack_unsol_event);

/**
 * snd_hda_jack_poll_all - Poll all jacks
 * @codec: the HDA codec
 *
 * Poll all detectable jacks with dirty flag, update the status, call
 * callbacks and call snd_hda_jack_report_sync() अगर any changes are found.
 */
व्योम snd_hda_jack_poll_all(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_jack_tbl *jack = codec->jacktbl.list;
	पूर्णांक i, changes = 0;

	क्रम (i = 0; i < codec->jacktbl.used; i++, jack++) अणु
		अचिन्हित पूर्णांक old_sense;
		अगर (!jack->nid || !jack->jack_dirty || jack->phantom_jack)
			जारी;
		old_sense = get_jack_plug_state(jack->pin_sense);
		jack_detect_update(codec, jack);
		अगर (old_sense == get_jack_plug_state(jack->pin_sense))
			जारी;
		changes = 1;
		call_jack_callback(codec, 0, jack);
	पूर्ण
	अगर (changes)
		snd_hda_jack_report_sync(codec);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_jack_poll_all);

