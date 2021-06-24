<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * HD-audio regmap helpers
 */

#अगर_अघोषित __SOUND_HDA_REGMAP_H
#घोषणा __SOUND_HDA_REGMAP_H

#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/hdaudपन.स>

#घोषणा AC_AMP_FAKE_MUTE	0x10	/* fake mute bit set to amp verbs */

पूर्णांक snd_hdac_regmap_init(काष्ठा hdac_device *codec);
व्योम snd_hdac_regmap_निकास(काष्ठा hdac_device *codec);
पूर्णांक snd_hdac_regmap_add_venकरोr_verb(काष्ठा hdac_device *codec,
				    अचिन्हित पूर्णांक verb);
पूर्णांक snd_hdac_regmap_पढ़ो_raw(काष्ठा hdac_device *codec, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक *val);
पूर्णांक snd_hdac_regmap_पढ़ो_raw_uncached(काष्ठा hdac_device *codec,
				      अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val);
पूर्णांक snd_hdac_regmap_ग_लिखो_raw(काष्ठा hdac_device *codec, अचिन्हित पूर्णांक reg,
			      अचिन्हित पूर्णांक val);
पूर्णांक snd_hdac_regmap_update_raw(काष्ठा hdac_device *codec, अचिन्हित पूर्णांक reg,
			       अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val);
पूर्णांक snd_hdac_regmap_update_raw_once(काष्ठा hdac_device *codec, अचिन्हित पूर्णांक reg,
				    अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val);
व्योम snd_hdac_regmap_sync(काष्ठा hdac_device *codec);

/**
 * snd_hdac_regmap_encode_verb - encode the verb to a pseuकरो रेजिस्टर
 * @nid: widget NID
 * @verb: codec verb
 *
 * Returns an encoded pseuकरो रेजिस्टर.
 */
#घोषणा snd_hdac_regmap_encode_verb(nid, verb)		\
	(((verb) << 8) | 0x80000 | ((अचिन्हित पूर्णांक)(nid) << 20))

/**
 * snd_hdac_regmap_encode_amp - encode the AMP verb to a pseuकरो रेजिस्टर
 * @nid: widget NID
 * @ch: channel (left = 0, right = 1)
 * @dir: direction (#HDA_INPUT, #HDA_OUTPUT)
 * @idx: input index value
 *
 * Returns an encoded pseuकरो रेजिस्टर.
 */
#घोषणा snd_hdac_regmap_encode_amp(nid, ch, dir, idx)			\
	(snd_hdac_regmap_encode_verb(nid, AC_VERB_GET_AMP_GAIN_MUTE) |	\
	 ((ch) ? AC_AMP_GET_RIGHT : AC_AMP_GET_LEFT) |			\
	 ((dir) == HDA_OUTPUT ? AC_AMP_GET_OUTPUT : AC_AMP_GET_INPUT) | \
	 (idx))

/**
 * snd_hdac_regmap_encode_amp_stereo - encode a pseuकरो रेजिस्टर क्रम stereo AMPs
 * @nid: widget NID
 * @dir: direction (#HDA_INPUT, #HDA_OUTPUT)
 * @idx: input index value
 *
 * Returns an encoded pseuकरो रेजिस्टर.
 */
#घोषणा snd_hdac_regmap_encode_amp_stereo(nid, dir, idx)		\
	(snd_hdac_regmap_encode_verb(nid, AC_VERB_GET_AMP_GAIN_MUTE) |	\
	 AC_AMP_SET_LEFT | AC_AMP_SET_RIGHT | /* both bits set! */	\
	 ((dir) == HDA_OUTPUT ? AC_AMP_GET_OUTPUT : AC_AMP_GET_INPUT) | \
	 (idx))

/**
 * snd_hdac_regmap_ग_लिखो - Write a verb with caching
 * @nid: codec NID
 * @reg: verb to ग_लिखो
 * @val: value to ग_लिखो
 *
 * For writing an amp value, use snd_hdac_regmap_update_amp().
 */
अटल अंतरभूत पूर्णांक
snd_hdac_regmap_ग_लिखो(काष्ठा hdac_device *codec, hda_nid_t nid,
		      अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक cmd = snd_hdac_regmap_encode_verb(nid, verb);

	वापस snd_hdac_regmap_ग_लिखो_raw(codec, cmd, val);
पूर्ण

/**
 * snd_hda_regmap_update - Update a verb value with caching
 * @nid: codec NID
 * @verb: verb to update
 * @mask: bit mask to update
 * @val: value to update
 *
 * For updating an amp value, use snd_hdac_regmap_update_amp().
 */
अटल अंतरभूत पूर्णांक
snd_hdac_regmap_update(काष्ठा hdac_device *codec, hda_nid_t nid,
		       अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक mask,
		       अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक cmd = snd_hdac_regmap_encode_verb(nid, verb);

	वापस snd_hdac_regmap_update_raw(codec, cmd, mask, val);
पूर्ण

/**
 * snd_hda_regmap_पढ़ो - Read a verb with caching
 * @nid: codec NID
 * @verb: verb to पढ़ो
 * @val: poपूर्णांकer to store the value
 *
 * For पढ़ोing an amp value, use snd_hda_regmap_get_amp().
 */
अटल अंतरभूत पूर्णांक
snd_hdac_regmap_पढ़ो(काष्ठा hdac_device *codec, hda_nid_t nid,
		     अचिन्हित पूर्णांक verb, अचिन्हित पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक cmd = snd_hdac_regmap_encode_verb(nid, verb);

	वापस snd_hdac_regmap_पढ़ो_raw(codec, cmd, val);
पूर्ण

/**
 * snd_hdac_regmap_get_amp - Read AMP value
 * @codec: HD-audio codec
 * @nid: NID to पढ़ो the AMP value
 * @ch: channel (left=0 or right=1)
 * @direction: #HDA_INPUT or #HDA_OUTPUT
 * @index: the index value (only क्रम input direction)
 * @val: the poपूर्णांकer to store the value
 *
 * Read AMP value.  The volume is between 0 to 0x7f, 0x80 = mute bit.
 * Returns the value or a negative error.
 */
अटल अंतरभूत पूर्णांक
snd_hdac_regmap_get_amp(काष्ठा hdac_device *codec, hda_nid_t nid,
			पूर्णांक ch, पूर्णांक dir, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक cmd = snd_hdac_regmap_encode_amp(nid, ch, dir, idx);
	पूर्णांक err, val;

	err = snd_hdac_regmap_पढ़ो_raw(codec, cmd, &val);
	वापस err < 0 ? err : val;
पूर्ण

/**
 * snd_hdac_regmap_update_amp - update the AMP value
 * @codec: HD-audio codec
 * @nid: NID to पढ़ो the AMP value
 * @ch: channel (left=0 or right=1)
 * @direction: #HDA_INPUT or #HDA_OUTPUT
 * @idx: the index value (only क्रम input direction)
 * @mask: bit mask to set
 * @val: the bits value to set
 *
 * Update the AMP value with a bit mask.
 * Returns 0 अगर the value is unchanged, 1 अगर changed, or a negative error.
 */
अटल अंतरभूत पूर्णांक
snd_hdac_regmap_update_amp(काष्ठा hdac_device *codec, hda_nid_t nid,
			   पूर्णांक ch, पूर्णांक dir, पूर्णांक idx, पूर्णांक mask, पूर्णांक val)
अणु
	अचिन्हित पूर्णांक cmd = snd_hdac_regmap_encode_amp(nid, ch, dir, idx);

	वापस snd_hdac_regmap_update_raw(codec, cmd, mask, val);
पूर्ण

/**
 * snd_hdac_regmap_get_amp_stereo - Read stereo AMP values
 * @codec: HD-audio codec
 * @nid: NID to पढ़ो the AMP value
 * @ch: channel (left=0 or right=1)
 * @direction: #HDA_INPUT or #HDA_OUTPUT
 * @index: the index value (only क्रम input direction)
 * @val: the poपूर्णांकer to store the value
 *
 * Read stereo AMP values.  The lower byte is left, the upper byte is right.
 * Returns the value or a negative error.
 */
अटल अंतरभूत पूर्णांक
snd_hdac_regmap_get_amp_stereo(काष्ठा hdac_device *codec, hda_nid_t nid,
			       पूर्णांक dir, पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक cmd = snd_hdac_regmap_encode_amp_stereo(nid, dir, idx);
	पूर्णांक err, val;

	err = snd_hdac_regmap_पढ़ो_raw(codec, cmd, &val);
	वापस err < 0 ? err : val;
पूर्ण

/**
 * snd_hdac_regmap_update_amp_stereo - update the stereo AMP value
 * @codec: HD-audio codec
 * @nid: NID to पढ़ो the AMP value
 * @direction: #HDA_INPUT or #HDA_OUTPUT
 * @idx: the index value (only क्रम input direction)
 * @mask: bit mask to set
 * @val: the bits value to set
 *
 * Update the stereo AMP value with a bit mask.
 * The lower byte is left, the upper byte is right.
 * Returns 0 अगर the value is unchanged, 1 अगर changed, or a negative error.
 */
अटल अंतरभूत पूर्णांक
snd_hdac_regmap_update_amp_stereo(काष्ठा hdac_device *codec, hda_nid_t nid,
				  पूर्णांक dir, पूर्णांक idx, पूर्णांक mask, पूर्णांक val)
अणु
	अचिन्हित पूर्णांक cmd = snd_hdac_regmap_encode_amp_stereo(nid, dir, idx);

	वापस snd_hdac_regmap_update_raw(codec, cmd, mask, val);
पूर्ण

/**
 * snd_hdac_regmap_sync_node - sync the widget node attributes
 * @codec: HD-audio codec
 * @nid: NID to sync
 */
अटल अंतरभूत व्योम
snd_hdac_regmap_sync_node(काष्ठा hdac_device *codec, hda_nid_t nid)
अणु
	regcache_mark_dirty(codec->regmap);
	regcache_sync_region(codec->regmap, nid << 20, ((nid + 1) << 20) - 1);
पूर्ण

#पूर्ण_अगर /* __SOUND_HDA_REGMAP_H */
