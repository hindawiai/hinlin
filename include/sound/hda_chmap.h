<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * For multichannel support
 */

#अगर_अघोषित __SOUND_HDA_CHMAP_H
#घोषणा __SOUND_HDA_CHMAP_H

#समावेश <sound/pcm.h>
#समावेश <sound/hdaudपन.स>


#घोषणा SND_PRINT_CHANNEL_ALLOCATION_ADVISED_बफ_मानE 80

काष्ठा hdac_cea_channel_speaker_allocation अणु
	पूर्णांक ca_index;
	पूर्णांक speakers[8];

	/* derived values, just क्रम convenience */
	पूर्णांक channels;
	पूर्णांक spk_mask;
पूर्ण;
काष्ठा hdac_chmap;

काष्ठा hdac_chmap_ops अणु
	/*
	 * Helpers क्रम producing the channel map TLVs. These can be overridden
	 * क्रम devices that have non-standard mapping requirements.
	 */
	पूर्णांक (*chmap_cea_alloc_validate_get_type)(काष्ठा hdac_chmap *chmap,
		काष्ठा hdac_cea_channel_speaker_allocation *cap, पूर्णांक channels);
	व्योम (*cea_alloc_to_tlv_chmap)(काष्ठा hdac_chmap *hchmap,
		काष्ठा hdac_cea_channel_speaker_allocation *cap,
		अचिन्हित पूर्णांक *chmap, पूर्णांक channels);

	/* check that the user-given chmap is supported */
	पूर्णांक (*chmap_validate)(काष्ठा hdac_chmap *hchmap, पूर्णांक ca,
			पूर्णांक channels, अचिन्हित अक्षर *chmap);

	पूर्णांक (*get_spk_alloc)(काष्ठा hdac_device *hdac, पूर्णांक pcm_idx);

	व्योम (*get_chmap)(काष्ठा hdac_device *hdac, पूर्णांक pcm_idx,
					अचिन्हित अक्षर *chmap);
	व्योम (*set_chmap)(काष्ठा hdac_device *hdac, पूर्णांक pcm_idx,
			अचिन्हित अक्षर *chmap, पूर्णांक prepared);
	bool (*is_pcm_attached)(काष्ठा hdac_device *hdac, पूर्णांक pcm_idx);

	/* get and set channel asचिन्हित to each HDMI ASP (audio sample packet) slot */
	पूर्णांक (*pin_get_slot_channel)(काष्ठा hdac_device *codec,
			hda_nid_t pin_nid, पूर्णांक asp_slot);
	पूर्णांक (*pin_set_slot_channel)(काष्ठा hdac_device *codec,
			hda_nid_t pin_nid, पूर्णांक asp_slot, पूर्णांक channel);
	व्योम (*set_channel_count)(काष्ठा hdac_device *codec,
				hda_nid_t cvt_nid, पूर्णांक chs);
पूर्ण;

काष्ठा hdac_chmap अणु
	अचिन्हित पूर्णांक channels_max; /* max over all cvts */
	काष्ठा hdac_chmap_ops ops;
	काष्ठा hdac_device *hdac;
पूर्ण;

व्योम snd_hdac_रेजिस्टर_chmap_ops(काष्ठा hdac_device *hdac,
				काष्ठा hdac_chmap *chmap);
पूर्णांक snd_hdac_channel_allocation(काष्ठा hdac_device *hdac, पूर्णांक spk_alloc,
			पूर्णांक channels, bool chmap_set,
			bool non_pcm, अचिन्हित अक्षर *map);
पूर्णांक snd_hdac_get_active_channels(पूर्णांक ca);
व्योम snd_hdac_setup_channel_mapping(काष्ठा hdac_chmap *chmap,
		       hda_nid_t pin_nid, bool non_pcm, पूर्णांक ca,
		       पूर्णांक channels, अचिन्हित अक्षर *map,
		       bool chmap_set);
व्योम snd_hdac_prपूर्णांक_channel_allocation(पूर्णांक spk_alloc, अक्षर *buf, पूर्णांक buflen);
काष्ठा hdac_cea_channel_speaker_allocation *snd_hdac_get_ch_alloc_from_ca(पूर्णांक ca);
पूर्णांक snd_hdac_chmap_to_spk_mask(अचिन्हित अक्षर c);
पूर्णांक snd_hdac_spk_to_chmap(पूर्णांक spk);
पूर्णांक snd_hdac_add_chmap_ctls(काष्ठा snd_pcm *pcm, पूर्णांक pcm_idx,
				काष्ठा hdac_chmap *chmap);
#पूर्ण_अगर /* __SOUND_HDA_CHMAP_H */
