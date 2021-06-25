<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Universal Interface क्रम Intel High Definition Audio Codec
 *
 * Local helper functions
 *
 * Copyright (c) 2004 Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित __SOUND_HDA_LOCAL_H
#घोषणा __SOUND_HDA_LOCAL_H

/* We abuse kcontrol_new.subdev field to pass the NID corresponding to
 * the given new control.  If id.subdev has a bit flag HDA_SUBDEV_NID_FLAG,
 * snd_hda_ctl_add() takes the lower-bit subdev value as a valid NID.
 * 
 * Note that the subdevice field is cleared again beक्रमe the real registration
 * in snd_hda_ctl_add(), so that this value won't appear in the outside.
 */
#घोषणा HDA_SUBDEV_NID_FLAG	(1U << 31)
#घोषणा HDA_SUBDEV_AMP_FLAG	(1U << 30)

/*
 * क्रम mixer controls
 */
#घोषणा HDA_COMPOSE_AMP_VAL_OFS(nid,chs,idx,dir,ofs)		\
	((nid) | ((chs)<<16) | ((dir)<<18) | ((idx)<<19) | ((ofs)<<23))
#घोषणा HDA_AMP_VAL_MIN_MUTE (1<<29)
#घोषणा HDA_COMPOSE_AMP_VAL(nid,chs,idx,dir) \
	HDA_COMPOSE_AMP_VAL_OFS(nid, chs, idx, dir, 0)
/* mono volume with index (index=0,1,...) (channel=1,2) */
#घोषणा HDA_CODEC_VOLUME_MONO_IDX(xname, xcidx, nid, channel, xindex, dir, flags) \
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xcidx,  \
	  .subdevice = HDA_SUBDEV_AMP_FLAG, \
	  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | \
	  	    SNDRV_CTL_ELEM_ACCESS_TLV_READ | \
	  	    SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK, \
	  .info = snd_hda_mixer_amp_volume_info, \
	  .get = snd_hda_mixer_amp_volume_get, \
	  .put = snd_hda_mixer_amp_volume_put, \
	  .tlv = अणु .c = snd_hda_mixer_amp_tlv पूर्ण,		\
	  .निजी_value = HDA_COMPOSE_AMP_VAL(nid, channel, xindex, dir) | flags पूर्ण
/* stereo volume with index */
#घोषणा HDA_CODEC_VOLUME_IDX(xname, xcidx, nid, xindex, direction) \
	HDA_CODEC_VOLUME_MONO_IDX(xname, xcidx, nid, 3, xindex, direction, 0)
/* mono volume */
#घोषणा HDA_CODEC_VOLUME_MONO(xname, nid, channel, xindex, direction) \
	HDA_CODEC_VOLUME_MONO_IDX(xname, 0, nid, channel, xindex, direction, 0)
/* stereo volume */
#घोषणा HDA_CODEC_VOLUME(xname, nid, xindex, direction) \
	HDA_CODEC_VOLUME_MONO(xname, nid, 3, xindex, direction)
/* stereo volume with min=mute */
#घोषणा HDA_CODEC_VOLUME_MIN_MUTE(xname, nid, xindex, direction) \
	HDA_CODEC_VOLUME_MONO_IDX(xname, 0, nid, 3, xindex, direction, \
				  HDA_AMP_VAL_MIN_MUTE)
/* mono mute चयन with index (index=0,1,...) (channel=1,2) */
#घोषणा HDA_CODEC_MUTE_MONO_IDX(xname, xcidx, nid, channel, xindex, direction) \
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xcidx, \
	  .subdevice = HDA_SUBDEV_AMP_FLAG, \
	  .info = snd_hda_mixer_amp_चयन_info, \
	  .get = snd_hda_mixer_amp_चयन_get, \
	  .put = snd_hda_mixer_amp_चयन_put, \
	  .निजी_value = HDA_COMPOSE_AMP_VAL(nid, channel, xindex, direction) पूर्ण
/* stereo mute चयन with index */
#घोषणा HDA_CODEC_MUTE_IDX(xname, xcidx, nid, xindex, direction) \
	HDA_CODEC_MUTE_MONO_IDX(xname, xcidx, nid, 3, xindex, direction)
/* mono mute चयन */
#घोषणा HDA_CODEC_MUTE_MONO(xname, nid, channel, xindex, direction) \
	HDA_CODEC_MUTE_MONO_IDX(xname, 0, nid, channel, xindex, direction)
/* stereo mute चयन */
#घोषणा HDA_CODEC_MUTE(xname, nid, xindex, direction) \
	HDA_CODEC_MUTE_MONO(xname, nid, 3, xindex, direction)
#अगर_घोषित CONFIG_SND_HDA_INPUT_BEEP
/* special beep mono mute चयन with index (index=0,1,...) (channel=1,2) */
#घोषणा HDA_CODEC_MUTE_BEEP_MONO_IDX(xname, xcidx, nid, channel, xindex, direction) \
	अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xcidx, \
	  .subdevice = HDA_SUBDEV_AMP_FLAG, \
	  .info = snd_hda_mixer_amp_चयन_info, \
	  .get = snd_hda_mixer_amp_चयन_get_beep, \
	  .put = snd_hda_mixer_amp_चयन_put_beep, \
	  .निजी_value = HDA_COMPOSE_AMP_VAL(nid, channel, xindex, direction) पूर्ण
#अन्यथा
/* no digital beep - just the standard one */
#घोषणा HDA_CODEC_MUTE_BEEP_MONO_IDX(xname, xcidx, nid, ch, xidx, dir) \
	HDA_CODEC_MUTE_MONO_IDX(xname, xcidx, nid, ch, xidx, dir)
#पूर्ण_अगर /* CONFIG_SND_HDA_INPUT_BEEP */
/* special beep mono mute चयन */
#घोषणा HDA_CODEC_MUTE_BEEP_MONO(xname, nid, channel, xindex, direction) \
	HDA_CODEC_MUTE_BEEP_MONO_IDX(xname, 0, nid, channel, xindex, direction)
/* special beep stereo mute चयन */
#घोषणा HDA_CODEC_MUTE_BEEP(xname, nid, xindex, direction) \
	HDA_CODEC_MUTE_BEEP_MONO(xname, nid, 3, xindex, direction)

बाह्य स्थिर अक्षर *snd_hda_pcm_type_name[];

पूर्णांक snd_hda_mixer_amp_volume_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo);
पूर्णांक snd_hda_mixer_amp_volume_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_hda_mixer_amp_volume_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_hda_mixer_amp_tlv(काष्ठा snd_kcontrol *kcontrol, पूर्णांक op_flag,
			  अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक __user *_tlv);
पूर्णांक snd_hda_mixer_amp_चयन_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo);
पूर्णांक snd_hda_mixer_amp_चयन_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_hda_mixer_amp_चयन_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol);
#अगर_घोषित CONFIG_SND_HDA_INPUT_BEEP
पूर्णांक snd_hda_mixer_amp_चयन_get_beep(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_hda_mixer_amp_चयन_put_beep(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol);
#पूर्ण_अगर
/* lowlevel accessor with caching; use carefully */
#घोषणा snd_hda_codec_amp_पढ़ो(codec, nid, ch, dir, idx) \
	snd_hdac_regmap_get_amp(&(codec)->core, nid, ch, dir, idx)
पूर्णांक snd_hda_codec_amp_update(काष्ठा hda_codec *codec, hda_nid_t nid,
			     पूर्णांक ch, पूर्णांक dir, पूर्णांक idx, पूर्णांक mask, पूर्णांक val);
पूर्णांक snd_hda_codec_amp_stereo(काष्ठा hda_codec *codec, hda_nid_t nid,
			     पूर्णांक direction, पूर्णांक idx, पूर्णांक mask, पूर्णांक val);
पूर्णांक snd_hda_codec_amp_init(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक ch,
			   पूर्णांक direction, पूर्णांक idx, पूर्णांक mask, पूर्णांक val);
पूर्णांक snd_hda_codec_amp_init_stereo(काष्ठा hda_codec *codec, hda_nid_t nid,
				  पूर्णांक dir, पूर्णांक idx, पूर्णांक mask, पूर्णांक val);
व्योम snd_hda_set_vmaster_tlv(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dir,
			     अचिन्हित पूर्णांक *tlv);
काष्ठा snd_kcontrol *snd_hda_find_mixer_ctl(काष्ठा hda_codec *codec,
					    स्थिर अक्षर *name);
पूर्णांक __snd_hda_add_vmaster(काष्ठा hda_codec *codec, अक्षर *name,
			  अचिन्हित पूर्णांक *tlv, स्थिर अक्षर * स्थिर *followers,
			  स्थिर अक्षर *suffix, bool init_follower_vol,
			  अचिन्हित पूर्णांक access, काष्ठा snd_kcontrol **ctl_ret);
#घोषणा snd_hda_add_vmaster(codec, name, tlv, followers, suffix, access) \
	__snd_hda_add_vmaster(codec, name, tlv, followers, suffix, true, access, शून्य)
पूर्णांक snd_hda_codec_reset(काष्ठा hda_codec *codec);
व्योम snd_hda_codec_रेजिस्टर(काष्ठा hda_codec *codec);
व्योम snd_hda_codec_cleanup_क्रम_unbind(काष्ठा hda_codec *codec);

#घोषणा snd_hda_regmap_sync(codec)	snd_hdac_regmap_sync(&(codec)->core)

काष्ठा hda_vmaster_mute_hook अणु
	/* below two fields must be filled by the caller of
	 * snd_hda_add_vmaster_hook() beक्रमehand
	 */
	काष्ठा snd_kcontrol *sw_kctl;
	व्योम (*hook)(व्योम *, पूर्णांक);
	/* below are initialized स्वतःmatically */
	काष्ठा hda_codec *codec;
पूर्ण;

पूर्णांक snd_hda_add_vmaster_hook(काष्ठा hda_codec *codec,
			     काष्ठा hda_vmaster_mute_hook *hook);
व्योम snd_hda_sync_vmaster_hook(काष्ठा hda_vmaster_mute_hook *hook);

/* amp value bits */
#घोषणा HDA_AMP_MUTE	0x80
#घोषणा HDA_AMP_UNMUTE	0x00
#घोषणा HDA_AMP_VOLMASK	0x7f

/*
 * SPDIF I/O
 */
पूर्णांक snd_hda_create_dig_out_ctls(काष्ठा hda_codec *codec,
				hda_nid_t associated_nid,
				hda_nid_t cvt_nid, पूर्णांक type);
#घोषणा snd_hda_create_spdअगर_out_ctls(codec, anid, cnid) \
	snd_hda_create_dig_out_ctls(codec, anid, cnid, HDA_PCM_TYPE_SPDIF)
पूर्णांक snd_hda_create_spdअगर_in_ctls(काष्ठा hda_codec *codec, hda_nid_t nid);

/*
 * input MUX helper
 */
#घोषणा HDA_MAX_NUM_INPUTS	36
काष्ठा hda_input_mux_item अणु
	अक्षर label[32];
	अचिन्हित पूर्णांक index;
पूर्ण;
काष्ठा hda_input_mux अणु
	अचिन्हित पूर्णांक num_items;
	काष्ठा hda_input_mux_item items[HDA_MAX_NUM_INPUTS];
पूर्ण;

पूर्णांक snd_hda_input_mux_info(स्थिर काष्ठा hda_input_mux *imux,
			   काष्ठा snd_ctl_elem_info *uinfo);
पूर्णांक snd_hda_input_mux_put(काष्ठा hda_codec *codec,
			  स्थिर काष्ठा hda_input_mux *imux,
			  काष्ठा snd_ctl_elem_value *ucontrol, hda_nid_t nid,
			  अचिन्हित पूर्णांक *cur_val);
पूर्णांक snd_hda_add_imux_item(काष्ठा hda_codec *codec,
			  काष्ठा hda_input_mux *imux, स्थिर अक्षर *label,
			  पूर्णांक index, पूर्णांक *type_idx);

/*
 * Multi-channel / digital-out PCM helper
 */

क्रमागत अणु HDA_FRONT, HDA_REAR, HDA_CLFE, HDA_SIDE पूर्ण; /* index क्रम dac_nidx */
क्रमागत अणु HDA_DIG_NONE, HDA_DIG_EXCLUSIVE, HDA_DIG_ANALOG_DUP पूर्ण; /* dig_out_used */

#घोषणा HDA_MAX_OUTS	5

काष्ठा hda_multi_out अणु
	पूर्णांक num_dacs;		/* # of DACs, must be more than 1 */
	स्थिर hda_nid_t *dac_nids;	/* DAC list */
	hda_nid_t hp_nid;	/* optional DAC क्रम HP, 0 when not exists */
	hda_nid_t hp_out_nid[HDA_MAX_OUTS];	/* DACs क्रम multiple HPs */
	hda_nid_t extra_out_nid[HDA_MAX_OUTS];	/* other (e.g. speaker) DACs */
	hda_nid_t dig_out_nid;	/* digital out audio widget */
	स्थिर hda_nid_t *follower_dig_outs;
	पूर्णांक max_channels;	/* currently supported analog channels */
	पूर्णांक dig_out_used;	/* current usage of digital out (HDA_DIG_XXX) */
	पूर्णांक no_share_stream;	/* करोn't share a stream with multiple pins */
	पूर्णांक share_spdअगर;	/* share SPDIF pin */
	/* PCM inक्रमmation क्रम both analog and SPDIF DACs */
	अचिन्हित पूर्णांक analog_rates;
	अचिन्हित पूर्णांक analog_maxbps;
	u64 analog_क्रमmats;
	अचिन्हित पूर्णांक spdअगर_rates;
	अचिन्हित पूर्णांक spdअगर_maxbps;
	u64 spdअगर_क्रमmats;
पूर्ण;

पूर्णांक snd_hda_create_spdअगर_share_sw(काष्ठा hda_codec *codec,
				  काष्ठा hda_multi_out *mout);
पूर्णांक snd_hda_multi_out_dig_खोलो(काष्ठा hda_codec *codec,
			       काष्ठा hda_multi_out *mout);
पूर्णांक snd_hda_multi_out_dig_बंद(काष्ठा hda_codec *codec,
				काष्ठा hda_multi_out *mout);
पूर्णांक snd_hda_multi_out_dig_prepare(काष्ठा hda_codec *codec,
				  काष्ठा hda_multi_out *mout,
				  अचिन्हित पूर्णांक stream_tag,
				  अचिन्हित पूर्णांक क्रमmat,
				  काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_hda_multi_out_dig_cleanup(काष्ठा hda_codec *codec,
				  काष्ठा hda_multi_out *mout);
पूर्णांक snd_hda_multi_out_analog_खोलो(काष्ठा hda_codec *codec,
				  काष्ठा hda_multi_out *mout,
				  काष्ठा snd_pcm_substream *substream,
				  काष्ठा hda_pcm_stream *hinfo);
पूर्णांक snd_hda_multi_out_analog_prepare(काष्ठा hda_codec *codec,
				     काष्ठा hda_multi_out *mout,
				     अचिन्हित पूर्णांक stream_tag,
				     अचिन्हित पूर्णांक क्रमmat,
				     काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_hda_multi_out_analog_cleanup(काष्ठा hda_codec *codec,
				     काष्ठा hda_multi_out *mout);

/*
 * generic proc पूर्णांकerface
 */
#अगर_घोषित CONFIG_SND_PROC_FS
पूर्णांक snd_hda_codec_proc_new(काष्ठा hda_codec *codec);
#अन्यथा
अटल अंतरभूत पूर्णांक snd_hda_codec_proc_new(काष्ठा hda_codec *codec) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#घोषणा SND_PRINT_BITS_ADVISED_बफ_मानE	16
व्योम snd_prपूर्णांक_pcm_bits(पूर्णांक pcm, अक्षर *buf, पूर्णांक buflen);

/*
 * Misc
 */
पूर्णांक snd_hda_add_new_ctls(काष्ठा hda_codec *codec,
			 स्थिर काष्ठा snd_kcontrol_new *knew);

/*
 * Fix-up pin शेष configurations and add शेष verbs
 */

काष्ठा hda_pपूर्णांकbl अणु
	hda_nid_t nid;
	u32 val;
पूर्ण;

काष्ठा hda_model_fixup अणु
	स्थिर पूर्णांक id;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा hda_fixup अणु
	पूर्णांक type;
	bool chained:1;		/* call the chained fixup(s) after this */
	bool chained_beक्रमe:1;	/* call the chained fixup(s) beक्रमe this */
	पूर्णांक chain_id;
	जोड़ अणु
		स्थिर काष्ठा hda_pपूर्णांकbl *pins;
		स्थिर काष्ठा hda_verb *verbs;
		व्योम (*func)(काष्ठा hda_codec *codec,
			     स्थिर काष्ठा hda_fixup *fix,
			     पूर्णांक action);
	पूर्ण v;
पूर्ण;

काष्ठा snd_hda_pin_quirk अणु
	अचिन्हित पूर्णांक codec;             /* Codec venकरोr/device ID */
	अचिन्हित लघु subvenकरोr;	/* PCI subvenकरोr ID */
	स्थिर काष्ठा hda_pपूर्णांकbl *pins;  /* list of matching pins */
#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
	स्थिर अक्षर *name;
#पूर्ण_अगर
	पूर्णांक value;			/* quirk value */
पूर्ण;

#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE

#घोषणा SND_HDA_PIN_QUIRK(_codec, _subvenकरोr, _name, _value, _pins...) \
	अणु .codec = _codec,\
	  .subvenकरोr = _subvenकरोr,\
	  .name = _name,\
	  .value = _value,\
	  .pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु _pins, अणु0, 0पूर्णपूर्ण \
	पूर्ण
#अन्यथा

#घोषणा SND_HDA_PIN_QUIRK(_codec, _subvenकरोr, _name, _value, _pins...) \
	अणु .codec = _codec,\
	  .subvenकरोr = _subvenकरोr,\
	  .value = _value,\
	  .pins = (स्थिर काष्ठा hda_pपूर्णांकbl[]) अणु _pins, अणु0, 0पूर्णपूर्ण \
	पूर्ण

#पूर्ण_अगर

#घोषणा HDA_FIXUP_ID_NOT_SET -1
#घोषणा HDA_FIXUP_ID_NO_FIXUP -2

/* fixup types */
क्रमागत अणु
	HDA_FIXUP_INVALID,
	HDA_FIXUP_PINS,
	HDA_FIXUP_VERBS,
	HDA_FIXUP_FUNC,
	HDA_FIXUP_PINCTLS,
पूर्ण;

/* fixup action definitions */
क्रमागत अणु
	HDA_FIXUP_ACT_PRE_PROBE,
	HDA_FIXUP_ACT_PROBE,
	HDA_FIXUP_ACT_INIT,
	HDA_FIXUP_ACT_BUILD,
	HDA_FIXUP_ACT_FREE,
पूर्ण;

पूर्णांक snd_hda_add_verbs(काष्ठा hda_codec *codec, स्थिर काष्ठा hda_verb *list);
व्योम snd_hda_apply_verbs(काष्ठा hda_codec *codec);
व्योम snd_hda_apply_pincfgs(काष्ठा hda_codec *codec,
			   स्थिर काष्ठा hda_pपूर्णांकbl *cfg);
व्योम snd_hda_apply_fixup(काष्ठा hda_codec *codec, पूर्णांक action);
व्योम snd_hda_pick_fixup(काष्ठा hda_codec *codec,
			स्थिर काष्ठा hda_model_fixup *models,
			स्थिर काष्ठा snd_pci_quirk *quirk,
			स्थिर काष्ठा hda_fixup *fixlist);
व्योम snd_hda_pick_pin_fixup(काष्ठा hda_codec *codec,
			    स्थिर काष्ठा snd_hda_pin_quirk *pin_quirk,
			    स्थिर काष्ठा hda_fixup *fixlist,
			    bool match_all_pins);

/* helper macros to retrieve pin शेष-config values */
#घोषणा get_defcfg_connect(cfg) \
	((cfg & AC_DEFCFG_PORT_CONN) >> AC_DEFCFG_PORT_CONN_SHIFT)
#घोषणा get_defcfg_association(cfg) \
	((cfg & AC_DEFCFG_DEF_ASSOC) >> AC_DEFCFG_ASSOC_SHIFT)
#घोषणा get_defcfg_location(cfg) \
	((cfg & AC_DEFCFG_LOCATION) >> AC_DEFCFG_LOCATION_SHIFT)
#घोषणा get_defcfg_sequence(cfg) \
	(cfg & AC_DEFCFG_SEQUENCE)
#घोषणा get_defcfg_device(cfg) \
	((cfg & AC_DEFCFG_DEVICE) >> AC_DEFCFG_DEVICE_SHIFT)
#घोषणा get_defcfg_misc(cfg) \
	((cfg & AC_DEFCFG_MISC) >> AC_DEFCFG_MISC_SHIFT)

/* amp values */
#घोषणा AMP_IN_MUTE(idx)	(0x7080 | ((idx)<<8))
#घोषणा AMP_IN_UNMUTE(idx)	(0x7000 | ((idx)<<8))
#घोषणा AMP_OUT_MUTE		0xb080
#घोषणा AMP_OUT_UNMUTE		0xb000
#घोषणा AMP_OUT_ZERO		0xb000
/* pinctl values */
#घोषणा PIN_IN			(AC_PINCTL_IN_EN)
#घोषणा PIN_VREFHIZ		(AC_PINCTL_IN_EN | AC_PINCTL_VREF_HIZ)
#घोषणा PIN_VREF50		(AC_PINCTL_IN_EN | AC_PINCTL_VREF_50)
#घोषणा PIN_VREFGRD		(AC_PINCTL_IN_EN | AC_PINCTL_VREF_GRD)
#घोषणा PIN_VREF80		(AC_PINCTL_IN_EN | AC_PINCTL_VREF_80)
#घोषणा PIN_VREF100		(AC_PINCTL_IN_EN | AC_PINCTL_VREF_100)
#घोषणा PIN_OUT			(AC_PINCTL_OUT_EN)
#घोषणा PIN_HP			(AC_PINCTL_OUT_EN | AC_PINCTL_HP_EN)
#घोषणा PIN_HP_AMP		(AC_PINCTL_HP_EN)

अचिन्हित पूर्णांक snd_hda_get_शेष_vref(काष्ठा hda_codec *codec, hda_nid_t pin);
अचिन्हित पूर्णांक snd_hda_correct_pin_ctl(काष्ठा hda_codec *codec,
				     hda_nid_t pin, अचिन्हित पूर्णांक val);
पूर्णांक _snd_hda_set_pin_ctl(काष्ठा hda_codec *codec, hda_nid_t pin,
			 अचिन्हित पूर्णांक val, bool cached);

/**
 * _snd_hda_set_pin_ctl - Set a pin-control value safely
 * @codec: the codec instance
 * @pin: the pin NID to set the control
 * @val: the pin-control value (AC_PINCTL_* bits)
 *
 * This function sets the pin-control value to the given pin, but
 * filters out the invalid pin-control bits when the pin has no such
 * capabilities.  For example, when PIN_HP is passed but the pin has no
 * HP-drive capability, the HP bit is omitted.
 *
 * The function करोesn't check the input VREF capability bits, though.
 * Use snd_hda_get_शेष_vref() to guess the right value.
 * Also, this function is only क्रम analog pins, not क्रम HDMI pins.
 */
अटल अंतरभूत पूर्णांक
snd_hda_set_pin_ctl(काष्ठा hda_codec *codec, hda_nid_t pin, अचिन्हित पूर्णांक val)
अणु
	वापस _snd_hda_set_pin_ctl(codec, pin, val, false);
पूर्ण

/**
 * snd_hda_set_pin_ctl_cache - Set a pin-control value safely
 * @codec: the codec instance
 * @pin: the pin NID to set the control
 * @val: the pin-control value (AC_PINCTL_* bits)
 *
 * Just like snd_hda_set_pin_ctl() but ग_लिखो to cache as well.
 */
अटल अंतरभूत पूर्णांक
snd_hda_set_pin_ctl_cache(काष्ठा hda_codec *codec, hda_nid_t pin,
			  अचिन्हित पूर्णांक val)
अणु
	वापस _snd_hda_set_pin_ctl(codec, pin, val, true);
पूर्ण

पूर्णांक snd_hda_codec_get_pin_target(काष्ठा hda_codec *codec, hda_nid_t nid);
पूर्णांक snd_hda_codec_set_pin_target(काष्ठा hda_codec *codec, hda_nid_t nid,
				 अचिन्हित पूर्णांक val);

#घोषणा क्रम_each_hda_codec_node(nid, codec) \
	क्रम ((nid) = (codec)->core.start_nid; (nid) < (codec)->core.end_nid; (nid)++)

/*
 * get widget capabilities
 */
अटल अंतरभूत u32 get_wcaps(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अगर (nid < codec->core.start_nid ||
	    nid >= codec->core.start_nid + codec->core.num_nodes)
		वापस 0;
	वापस codec->wcaps[nid - codec->core.start_nid];
पूर्ण

/* get the widget type from widget capability bits */
अटल अंतरभूत पूर्णांक get_wcaps_type(अचिन्हित पूर्णांक wcaps)
अणु
	अगर (!wcaps)
		वापस -1; /* invalid type */
	वापस (wcaps & AC_WCAP_TYPE) >> AC_WCAP_TYPE_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_wcaps_channels(u32 wcaps)
अणु
	अचिन्हित पूर्णांक chans;

	chans = (wcaps & AC_WCAP_CHAN_CNT_EXT) >> 13;
	chans = ((chans << 1) | 1) + 1;

	वापस chans;
पूर्ण

अटल अंतरभूत व्योम snd_hda_override_wcaps(काष्ठा hda_codec *codec,
					  hda_nid_t nid, u32 val)
अणु
	अगर (nid >= codec->core.start_nid &&
	    nid < codec->core.start_nid + codec->core.num_nodes)
		codec->wcaps[nid - codec->core.start_nid] = val;
पूर्ण

u32 query_amp_caps(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक direction);
पूर्णांक snd_hda_override_amp_caps(काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dir,
			      अचिन्हित पूर्णांक caps);
/**
 * snd_hda_query_pin_caps - Query PIN capabilities
 * @codec: the HD-auio codec
 * @nid: the NID to query
 *
 * Query PIN capabilities क्रम the given widget.
 * Returns the obtained capability bits.
 *
 * When cap bits have been alपढ़ोy पढ़ो, this करोesn't पढ़ो again but
 * वापसs the cached value.
 */
अटल अंतरभूत u32
snd_hda_query_pin_caps(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	वापस snd_hda_param_पढ़ो(codec, nid, AC_PAR_PIN_CAP);

पूर्ण

/**
 * snd_hda_override_pin_caps - Override the pin capabilities
 * @codec: the CODEC
 * @nid: the NID to override
 * @caps: the capability bits to set
 *
 * Override the cached PIN capabilitiy bits value by the given one.
 *
 * Returns zero अगर successful or a negative error code.
 */
अटल अंतरभूत पूर्णांक
snd_hda_override_pin_caps(काष्ठा hda_codec *codec, hda_nid_t nid,
			  अचिन्हित पूर्णांक caps)
अणु
	वापस snd_hdac_override_parm(&codec->core, nid, AC_PAR_PIN_CAP, caps);
पूर्ण

bool snd_hda_check_amp_caps(काष्ठा hda_codec *codec, hda_nid_t nid,
			   पूर्णांक dir, अचिन्हित पूर्णांक bits);

#घोषणा nid_has_mute(codec, nid, dir) \
	snd_hda_check_amp_caps(codec, nid, dir, (AC_AMPCAP_MUTE | AC_AMPCAP_MIN_MUTE))
#घोषणा nid_has_volume(codec, nid, dir) \
	snd_hda_check_amp_caps(codec, nid, dir, AC_AMPCAP_NUM_STEPS)


/* flags क्रम hda_nid_item */
#घोषणा HDA_NID_ITEM_AMP	(1<<0)

काष्ठा hda_nid_item अणु
	काष्ठा snd_kcontrol *kctl;
	अचिन्हित पूर्णांक index;
	hda_nid_t nid;
	अचिन्हित लघु flags;
पूर्ण;

पूर्णांक snd_hda_ctl_add(काष्ठा hda_codec *codec, hda_nid_t nid,
		    काष्ठा snd_kcontrol *kctl);
पूर्णांक snd_hda_add_nid(काष्ठा hda_codec *codec, काष्ठा snd_kcontrol *kctl,
		    अचिन्हित पूर्णांक index, hda_nid_t nid);
व्योम snd_hda_ctls_clear(काष्ठा hda_codec *codec);

/*
 * hwdep पूर्णांकerface
 */
#अगर_घोषित CONFIG_SND_HDA_HWDEP
पूर्णांक snd_hda_create_hwdep(काष्ठा hda_codec *codec);
#अन्यथा
अटल अंतरभूत पूर्णांक snd_hda_create_hwdep(काष्ठा hda_codec *codec) अणु वापस 0; पूर्ण
#पूर्ण_अगर

व्योम snd_hda_sysfs_init(काष्ठा hda_codec *codec);
व्योम snd_hda_sysfs_clear(काष्ठा hda_codec *codec);

बाह्य स्थिर काष्ठा attribute_group *snd_hda_dev_attr_groups[];

#अगर_घोषित CONFIG_SND_HDA_RECONFIG
स्थिर अक्षर *snd_hda_get_hपूर्णांक(काष्ठा hda_codec *codec, स्थिर अक्षर *key);
पूर्णांक snd_hda_get_bool_hपूर्णांक(काष्ठा hda_codec *codec, स्थिर अक्षर *key);
पूर्णांक snd_hda_get_पूर्णांक_hपूर्णांक(काष्ठा hda_codec *codec, स्थिर अक्षर *key, पूर्णांक *valp);
#अन्यथा
अटल अंतरभूत
स्थिर अक्षर *snd_hda_get_hपूर्णांक(काष्ठा hda_codec *codec, स्थिर अक्षर *key)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत
पूर्णांक snd_hda_get_bool_hपूर्णांक(काष्ठा hda_codec *codec, स्थिर अक्षर *key)
अणु
	वापस -ENOENT;
पूर्ण

अटल अंतरभूत
पूर्णांक snd_hda_get_पूर्णांक_hपूर्णांक(काष्ठा hda_codec *codec, स्थिर अक्षर *key, पूर्णांक *valp)
अणु
	वापस -ENOENT;
पूर्ण
#पूर्ण_अगर

/*
 * घातer-management
 */

व्योम snd_hda_schedule_घातer_save(काष्ठा hda_codec *codec);

काष्ठा hda_amp_list अणु
	hda_nid_t nid;
	अचिन्हित अक्षर dir;
	अचिन्हित अक्षर idx;
पूर्ण;

काष्ठा hda_loopback_check अणु
	स्थिर काष्ठा hda_amp_list *amplist;
	पूर्णांक घातer_on;
पूर्ण;

पूर्णांक snd_hda_check_amp_list_घातer(काष्ठा hda_codec *codec,
				 काष्ठा hda_loopback_check *check,
				 hda_nid_t nid);

/* check whether the actual घातer state matches with the target state */
अटल अंतरभूत bool
snd_hda_check_घातer_state(काष्ठा hda_codec *codec, hda_nid_t nid,
			  अचिन्हित पूर्णांक target_state)
अणु
	वापस snd_hdac_check_घातer_state(&codec->core, nid, target_state);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक snd_hda_sync_घातer_state(काष्ठा hda_codec *codec,
						    hda_nid_t nid,
						    अचिन्हित पूर्णांक target_state)
अणु
	वापस snd_hdac_sync_घातer_state(&codec->core, nid, target_state);
पूर्ण
अचिन्हित पूर्णांक snd_hda_codec_eapd_घातer_filter(काष्ठा hda_codec *codec,
					     hda_nid_t nid,
					     अचिन्हित पूर्णांक घातer_state);

/*
 * AMP control callbacks
 */
/* retrieve parameters from निजी_value */
#घोषणा get_amp_nid_(pv)	((pv) & 0xffff)
#घोषणा get_amp_nid(kc)		get_amp_nid_((kc)->निजी_value)
#घोषणा get_amp_channels(kc)	(((kc)->निजी_value >> 16) & 0x3)
#घोषणा get_amp_direction_(pv)	(((pv) >> 18) & 0x1)
#घोषणा get_amp_direction(kc)	get_amp_direction_((kc)->निजी_value)
#घोषणा get_amp_index_(pv)	(((pv) >> 19) & 0xf)
#घोषणा get_amp_index(kc)	get_amp_index_((kc)->निजी_value)
#घोषणा get_amp_offset(kc)	(((kc)->निजी_value >> 23) & 0x3f)
#घोषणा get_amp_min_mute(kc)	(((kc)->निजी_value >> 29) & 0x1)

/*
 * क्रमागत control helper
 */
पूर्णांक snd_hda_क्रमागत_helper_info(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_info *uinfo,
			     पूर्णांक num_items, स्थिर अक्षर * स्थिर *texts);
#घोषणा snd_hda_क्रमागत_bool_helper_info(kcontrol, uinfo) \
	snd_hda_क्रमागत_helper_info(kcontrol, uinfo, 0, शून्य)

/*
 * CEA Short Audio Descriptor data
 */
काष्ठा cea_sad अणु
	पूर्णांक	channels;
	पूर्णांक	क्रमmat;		/* (क्रमmat == 0) indicates invalid SAD */
	पूर्णांक	rates;
	पूर्णांक	sample_bits;	/* क्रम LPCM */
	पूर्णांक	max_bitrate;	/* क्रम AC3...ATRAC */
	पूर्णांक	profile;	/* क्रम WMAPRO */
पूर्ण;

#घोषणा ELD_FIXED_BYTES	20
#घोषणा ELD_MAX_SIZE    256
#घोषणा ELD_MAX_MNL	16
#घोषणा ELD_MAX_SAD	16

/*
 * ELD: EDID Like Data
 */
काष्ठा parsed_hdmi_eld अणु
	/*
	 * all fields will be cleared beक्रमe updating ELD
	 */
	पूर्णांक	baseline_len;
	पूर्णांक	eld_ver;
	पूर्णांक	cea_edid_ver;
	अक्षर	monitor_name[ELD_MAX_MNL + 1];
	पूर्णांक	manufacture_id;
	पूर्णांक	product_id;
	u64	port_id;
	पूर्णांक	support_hdcp;
	पूर्णांक	support_ai;
	पूर्णांक	conn_type;
	पूर्णांक	aud_synch_delay;
	पूर्णांक	spk_alloc;
	पूर्णांक	sad_count;
	काष्ठा cea_sad sad[ELD_MAX_SAD];
पूर्ण;

काष्ठा hdmi_eld अणु
	bool	monitor_present;
	bool	eld_valid;
	पूर्णांक	eld_size;
	अक्षर    eld_buffer[ELD_MAX_SIZE];
	काष्ठा parsed_hdmi_eld info;
पूर्ण;

पूर्णांक snd_hdmi_get_eld_size(काष्ठा hda_codec *codec, hda_nid_t nid);
पूर्णांक snd_hdmi_get_eld(काष्ठा hda_codec *codec, hda_nid_t nid,
		     अचिन्हित अक्षर *buf, पूर्णांक *eld_size);
पूर्णांक snd_hdmi_parse_eld(काष्ठा hda_codec *codec, काष्ठा parsed_hdmi_eld *e,
		       स्थिर अचिन्हित अक्षर *buf, पूर्णांक size);
व्योम snd_hdmi_show_eld(काष्ठा hda_codec *codec, काष्ठा parsed_hdmi_eld *e);
व्योम snd_hdmi_eld_update_pcm_info(काष्ठा parsed_hdmi_eld *e,
			      काष्ठा hda_pcm_stream *hinfo);

पूर्णांक snd_hdmi_get_eld_ati(काष्ठा hda_codec *codec, hda_nid_t nid,
			 अचिन्हित अक्षर *buf, पूर्णांक *eld_size,
			 bool rev3_or_later);

#अगर_घोषित CONFIG_SND_PROC_FS
व्योम snd_hdmi_prपूर्णांक_eld_info(काष्ठा hdmi_eld *eld,
			     काष्ठा snd_info_buffer *buffer);
व्योम snd_hdmi_ग_लिखो_eld_info(काष्ठा hdmi_eld *eld,
			     काष्ठा snd_info_buffer *buffer);
#पूर्ण_अगर

#घोषणा SND_PRINT_CHANNEL_ALLOCATION_ADVISED_बफ_मानE 80
व्योम snd_prपूर्णांक_channel_allocation(पूर्णांक spk_alloc, अक्षर *buf, पूर्णांक buflen);

/*
 */
#घोषणा codec_err(codec, fmt, args...) \
	dev_err(hda_codec_dev(codec), fmt, ##args)
#घोषणा codec_warn(codec, fmt, args...) \
	dev_warn(hda_codec_dev(codec), fmt, ##args)
#घोषणा codec_info(codec, fmt, args...) \
	dev_info(hda_codec_dev(codec), fmt, ##args)
#घोषणा codec_dbg(codec, fmt, args...) \
	dev_dbg(hda_codec_dev(codec), fmt, ##args)

#पूर्ण_अगर /* __SOUND_HDA_LOCAL_H */
