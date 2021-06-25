<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Jack-detection handling क्रम HD-audio
 *
 * Copyright (c) 2011 Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित __SOUND_HDA_JACK_H
#घोषणा __SOUND_HDA_JACK_H

#समावेश <linux/err.h>
#समावेश <sound/jack.h>

काष्ठा स्वतः_pin_cfg;
काष्ठा hda_jack_tbl;
काष्ठा hda_jack_callback;

प्रकार व्योम (*hda_jack_callback_fn) (काष्ठा hda_codec *, काष्ठा hda_jack_callback *);

काष्ठा hda_jack_callback अणु
	hda_nid_t nid;
	पूर्णांक dev_id;
	hda_jack_callback_fn func;
	अचिन्हित पूर्णांक निजी_data;	/* arbitrary data */
	अचिन्हित पूर्णांक unsol_res;		/* unsolicited event bits */
	काष्ठा hda_jack_tbl *jack;	/* associated jack entry */
	काष्ठा hda_jack_callback *next;
पूर्ण;

काष्ठा hda_jack_tbl अणु
	hda_nid_t nid;
	पूर्णांक dev_id;
	अचिन्हित अक्षर tag;		/* unsol event tag */
	काष्ठा hda_jack_callback *callback;
	/* jack-detection stuff */
	अचिन्हित पूर्णांक pin_sense;		/* cached pin-sense value */
	अचिन्हित पूर्णांक jack_detect:1;	/* capable of jack-detection? */
	अचिन्हित पूर्णांक jack_dirty:1;	/* needs to update? */
	अचिन्हित पूर्णांक phantom_jack:1;    /* a fixed, always present port? */
	अचिन्हित पूर्णांक block_report:1;    /* in a transitional state - करो not report to userspace */
	hda_nid_t gating_jack;		/* valid when gating jack plugged */
	hda_nid_t gated_jack;		/* gated is dependent on this jack */
	hda_nid_t key_report_jack;	/* key reports to this jack */
	पूर्णांक type;
	पूर्णांक button_state;
	काष्ठा snd_jack *jack;
पूर्ण;

काष्ठा hda_jack_keymap अणु
	क्रमागत snd_jack_types type;
	पूर्णांक key;
पूर्ण;

काष्ठा hda_jack_tbl *
snd_hda_jack_tbl_get_mst(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dev_id);

/**
 * snd_hda_jack_tbl_get - query the jack-table entry क्रम the given NID
 * @codec: the HDA codec
 * @nid: pin NID to refer to
 */
अटल अंतरभूत काष्ठा hda_jack_tbl *
snd_hda_jack_tbl_get(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	वापस snd_hda_jack_tbl_get_mst(codec, nid, 0);
पूर्ण

काष्ठा hda_jack_tbl *
snd_hda_jack_tbl_get_from_tag(काष्ठा hda_codec *codec,
			      अचिन्हित अक्षर tag, पूर्णांक dev_id);

व्योम snd_hda_jack_tbl_clear(काष्ठा hda_codec *codec);

व्योम snd_hda_jack_set_dirty_all(काष्ठा hda_codec *codec);

पूर्णांक snd_hda_jack_detect_enable(काष्ठा hda_codec *codec, hda_nid_t nid,
			       पूर्णांक dev_id);

काष्ठा hda_jack_callback *
snd_hda_jack_detect_enable_callback_mst(काष्ठा hda_codec *codec, hda_nid_t nid,
					पूर्णांक dev_id, hda_jack_callback_fn func);

/**
 * snd_hda_jack_detect_enable - enable the jack-detection
 * @codec: the HDA codec
 * @nid: pin NID to enable
 * @func: callback function to रेजिस्टर
 *
 * In the हाल of error, the वापस value will be a poपूर्णांकer embedded with
 * त्रुटि_सं.  Check and handle the वापस value appropriately with standard
 * macros such as @IS_ERR() and @PTR_ERR().
 */
अटल अंतरभूत काष्ठा hda_jack_callback *
snd_hda_jack_detect_enable_callback(काष्ठा hda_codec *codec, hda_nid_t nid,
				    hda_jack_callback_fn cb)
अणु
	वापस snd_hda_jack_detect_enable_callback_mst(codec, nid, 0, cb);
पूर्ण

पूर्णांक snd_hda_jack_set_gating_jack(काष्ठा hda_codec *codec, hda_nid_t gated_nid,
				 hda_nid_t gating_nid);

पूर्णांक snd_hda_jack_bind_keymap(काष्ठा hda_codec *codec, hda_nid_t key_nid,
			     स्थिर काष्ठा hda_jack_keymap *keymap,
			     hda_nid_t jack_nid);

व्योम snd_hda_jack_set_button_state(काष्ठा hda_codec *codec, hda_nid_t jack_nid,
				   पूर्णांक button_state);

u32 snd_hda_jack_pin_sense(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dev_id);

/* the jack state वापसed from snd_hda_jack_detect_state() */
क्रमागत अणु
	HDA_JACK_NOT_PRESENT, HDA_JACK_PRESENT, HDA_JACK_PHANTOM,
पूर्ण;

पूर्णांक snd_hda_jack_detect_state_mst(काष्ठा hda_codec *codec, hda_nid_t nid,
				  पूर्णांक dev_id);

/**
 * snd_hda_jack_detect_state - query pin Presence Detect status
 * @codec: the CODEC to sense
 * @nid: the pin NID to sense
 *
 * Query and वापस the pin's Presence Detect status, as either
 * HDA_JACK_NOT_PRESENT, HDA_JACK_PRESENT or HDA_JACK_PHANTOM.
 */
अटल अंतरभूत पूर्णांक
snd_hda_jack_detect_state(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	वापस snd_hda_jack_detect_state_mst(codec, nid, 0);
पूर्ण

/**
 * snd_hda_jack_detect_mst - Detect the jack
 * @codec: the HDA codec
 * @nid: pin NID to check jack detection
 * @dev_id: pin device entry id
 */
अटल अंतरभूत bool
snd_hda_jack_detect_mst(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dev_id)
अणु
	वापस snd_hda_jack_detect_state_mst(codec, nid, dev_id) !=
			HDA_JACK_NOT_PRESENT;
पूर्ण

/**
 * snd_hda_jack_detect - Detect the jack
 * @codec: the HDA codec
 * @nid: pin NID to check jack detection
 */
अटल अंतरभूत bool
snd_hda_jack_detect(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	वापस snd_hda_jack_detect_mst(codec, nid, 0);
पूर्ण

bool is_jack_detectable(काष्ठा hda_codec *codec, hda_nid_t nid);

पूर्णांक snd_hda_jack_add_kctl_mst(काष्ठा hda_codec *codec, hda_nid_t nid,
			      पूर्णांक dev_id, स्थिर अक्षर *name, bool phantom_jack,
			      पूर्णांक type, स्थिर काष्ठा hda_jack_keymap *keymap);

/**
 * snd_hda_jack_add_kctl - Add a kctl क्रम the given pin
 * @codec: the HDA codec
 * @nid: pin NID to assign
 * @name: string name क्रम the jack
 * @phantom_jack: flag to deal as a phantom jack
 * @type: jack type bits to be reported, 0 क्रम guessing from pincfg
 * @keymap: optional jack / key mapping
 *
 * This assigns a jack-detection kctl to the given pin.  The kcontrol
 * will have the given name and index.
 */
अटल अंतरभूत पूर्णांक
snd_hda_jack_add_kctl(काष्ठा hda_codec *codec, hda_nid_t nid,
		      स्थिर अक्षर *name, bool phantom_jack,
		      पूर्णांक type, स्थिर काष्ठा hda_jack_keymap *keymap)
अणु
	वापस snd_hda_jack_add_kctl_mst(codec, nid, 0,
					 name, phantom_jack, type, keymap);
पूर्ण

पूर्णांक snd_hda_jack_add_kctls(काष्ठा hda_codec *codec,
			   स्थिर काष्ठा स्वतः_pin_cfg *cfg);

व्योम snd_hda_jack_report_sync(काष्ठा hda_codec *codec);

व्योम snd_hda_jack_unsol_event(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक res);

व्योम snd_hda_jack_poll_all(काष्ठा hda_codec *codec);

#पूर्ण_अगर /* __SOUND_HDA_JACK_H */
