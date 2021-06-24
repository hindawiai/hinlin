<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  patch_hdmi.c - routines क्रम HDMI/DisplayPort codecs
 *
 *  Copyright(c) 2008-2010 Intel Corporation. All rights reserved.
 *  Copyright (c) 2006 ATI Technologies Inc.
 *  Copyright (c) 2008 NVIDIA Corp.  All rights reserved.
 *  Copyright (c) 2008 Wei Ni <wni@nvidia.com>
 *  Copyright (c) 2013 Anssi Hannula <anssi.hannula@iki.fi>
 *
 *  Authors:
 *			Wu Fengguang <wfg@linux.पूर्णांकel.com>
 *
 *  Maपूर्णांकained by:
 *			Wu Fengguang <wfg@linux.पूर्णांकel.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/tlv.h>
#समावेश <sound/hdaudपन.स>
#समावेश <sound/hda_i915.h>
#समावेश <sound/hda_chmap.h>
#समावेश <sound/hda_codec.h>
#समावेश "hda_local.h"
#समावेश "hda_jack.h"
#समावेश "hda_controller.h"

अटल bool अटल_hdmi_pcm;
module_param(अटल_hdmi_pcm, bool, 0644);
MODULE_PARM_DESC(अटल_hdmi_pcm, "Don't restrict PCM parameters per ELD info");

अटल bool enable_acomp = true;
module_param(enable_acomp, bool, 0444);
MODULE_PARM_DESC(enable_acomp, "Enable audio component binding (default=yes)");

अटल bool enable_silent_stream =
IS_ENABLED(CONFIG_SND_HDA_INTEL_HDMI_SILENT_STREAM);
module_param(enable_silent_stream, bool, 0644);
MODULE_PARM_DESC(enable_silent_stream, "Enable Silent Stream for HDMI devices");

काष्ठा hdmi_spec_per_cvt अणु
	hda_nid_t cvt_nid;
	पूर्णांक asचिन्हित;
	अचिन्हित पूर्णांक channels_min;
	अचिन्हित पूर्णांक channels_max;
	u32 rates;
	u64 क्रमmats;
	अचिन्हित पूर्णांक maxbps;
पूर्ण;

/* max. connections to a widget */
#घोषणा HDA_MAX_CONNECTIONS	32

काष्ठा hdmi_spec_per_pin अणु
	hda_nid_t pin_nid;
	पूर्णांक dev_id;
	/* pin idx, dअगरferent device entries on the same pin use the same idx */
	पूर्णांक pin_nid_idx;
	पूर्णांक num_mux_nids;
	hda_nid_t mux_nids[HDA_MAX_CONNECTIONS];
	पूर्णांक mux_idx;
	hda_nid_t cvt_nid;

	काष्ठा hda_codec *codec;
	काष्ठा hdmi_eld sink_eld;
	काष्ठा mutex lock;
	काष्ठा delayed_work work;
	काष्ठा hdmi_pcm *pcm; /* poपूर्णांकer to spec->pcm_rec[n] dynamically*/
	पूर्णांक pcm_idx; /* which pcm is attached. -1 means no pcm is attached */
	पूर्णांक repoll_count;
	bool setup; /* the stream has been set up by prepare callback */
	bool silent_stream;
	पूर्णांक channels; /* current number of channels */
	bool non_pcm;
	bool chmap_set;		/* channel-map override by ALSA API? */
	अचिन्हित अक्षर chmap[8]; /* ALSA API channel-map */
#अगर_घोषित CONFIG_SND_PROC_FS
	काष्ठा snd_info_entry *proc_entry;
#पूर्ण_अगर
पूर्ण;

/* operations used by generic code that can be overridden by patches */
काष्ठा hdmi_ops अणु
	पूर्णांक (*pin_get_eld)(काष्ठा hda_codec *codec, hda_nid_t pin_nid,
			   पूर्णांक dev_id, अचिन्हित अक्षर *buf, पूर्णांक *eld_size);

	व्योम (*pin_setup_infoframe)(काष्ठा hda_codec *codec, hda_nid_t pin_nid,
				    पूर्णांक dev_id,
				    पूर्णांक ca, पूर्णांक active_channels, पूर्णांक conn_type);

	/* enable/disable HBR (HD passthrough) */
	पूर्णांक (*pin_hbr_setup)(काष्ठा hda_codec *codec, hda_nid_t pin_nid,
			     पूर्णांक dev_id, bool hbr);

	पूर्णांक (*setup_stream)(काष्ठा hda_codec *codec, hda_nid_t cvt_nid,
			    hda_nid_t pin_nid, पूर्णांक dev_id, u32 stream_tag,
			    पूर्णांक क्रमmat);

	व्योम (*pin_cvt_fixup)(काष्ठा hda_codec *codec,
			      काष्ठा hdmi_spec_per_pin *per_pin,
			      hda_nid_t cvt_nid);
पूर्ण;

काष्ठा hdmi_pcm अणु
	काष्ठा hda_pcm *pcm;
	काष्ठा snd_jack *jack;
	काष्ठा snd_kcontrol *eld_ctl;
पूर्ण;

काष्ठा hdmi_spec अणु
	काष्ठा hda_codec *codec;
	पूर्णांक num_cvts;
	काष्ठा snd_array cvts; /* काष्ठा hdmi_spec_per_cvt */
	hda_nid_t cvt_nids[4]; /* only क्रम haswell fix */

	/*
	 * num_pins is the number of भव pins
	 * क्रम example, there are 3 pins, and each pin
	 * has 4 device entries, then the num_pins is 12
	 */
	पूर्णांक num_pins;
	/*
	 * num_nids is the number of real pins
	 * In the above example, num_nids is 3
	 */
	पूर्णांक num_nids;
	/*
	 * dev_num is the number of device entries
	 * on each pin.
	 * In the above example, dev_num is 4
	 */
	पूर्णांक dev_num;
	काष्ठा snd_array pins; /* काष्ठा hdmi_spec_per_pin */
	काष्ठा hdmi_pcm pcm_rec[16];
	काष्ठा mutex pcm_lock;
	काष्ठा mutex bind_lock; /* क्रम audio component binding */
	/* pcm_biपंचांगap means which pcms have been asचिन्हित to pins*/
	अचिन्हित दीर्घ pcm_biपंचांगap;
	पूर्णांक pcm_used;	/* counter of pcm_rec[] */
	/* biपंचांगap shows whether the pcm is खोलोed in user space
	 * bit 0 means the first playback PCM (PCM3);
	 * bit 1 means the second playback PCM, and so on.
	 */
	अचिन्हित दीर्घ pcm_in_use;

	काष्ठा hdmi_eld temp_eld;
	काष्ठा hdmi_ops ops;

	bool dyn_pin_out;
	bool dyn_pcm_assign;
	bool dyn_pcm_no_legacy;
	bool पूर्णांकel_hsw_fixup;	/* apply Intel platक्रमm-specअगरic fixups */
	/*
	 * Non-generic VIA/NVIDIA specअगरic
	 */
	काष्ठा hda_multi_out multiout;
	काष्ठा hda_pcm_stream pcm_playback;

	bool use_acomp_notअगरier; /* use eld_notअगरy callback क्रम hotplug */
	bool acomp_रेजिस्टरed; /* audio component रेजिस्टरed in this driver */
	bool क्रमce_connect; /* क्रमce connectivity */
	काष्ठा drm_audio_component_audio_ops drm_audio_ops;
	पूर्णांक (*port2pin)(काष्ठा hda_codec *, पूर्णांक); /* reverse port/pin mapping */

	काष्ठा hdac_chmap chmap;
	hda_nid_t venकरोr_nid;
	स्थिर पूर्णांक *port_map;
	पूर्णांक port_num;
	bool send_silent_stream; /* Flag to enable silent stream feature */
पूर्ण;

#अगर_घोषित CONFIG_SND_HDA_COMPONENT
अटल अंतरभूत bool codec_has_acomp(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	वापस spec->use_acomp_notअगरier;
पूर्ण
#अन्यथा
#घोषणा codec_has_acomp(codec)	false
#पूर्ण_अगर

काष्ठा hdmi_audio_infoframe अणु
	u8 type; /* 0x84 */
	u8 ver;  /* 0x01 */
	u8 len;  /* 0x0a */

	u8 checksum;

	u8 CC02_CT47;	/* CC in bits 0:2, CT in 4:7 */
	u8 SS01_SF24;
	u8 CXT04;
	u8 CA;
	u8 LFEPBL01_LSV36_DM_INH7;
पूर्ण;

काष्ठा dp_audio_infoframe अणु
	u8 type; /* 0x84 */
	u8 len;  /* 0x1b */
	u8 ver;  /* 0x11 << 2 */

	u8 CC02_CT47;	/* match with HDMI infoframe from this on */
	u8 SS01_SF24;
	u8 CXT04;
	u8 CA;
	u8 LFEPBL01_LSV36_DM_INH7;
पूर्ण;

जोड़ audio_infoframe अणु
	काष्ठा hdmi_audio_infoframe hdmi;
	काष्ठा dp_audio_infoframe dp;
	u8 bytes[0];
पूर्ण;

/*
 * HDMI routines
 */

#घोषणा get_pin(spec, idx) \
	((काष्ठा hdmi_spec_per_pin *)snd_array_elem(&spec->pins, idx))
#घोषणा get_cvt(spec, idx) \
	((काष्ठा hdmi_spec_per_cvt  *)snd_array_elem(&spec->cvts, idx))
/* obtain hdmi_pcm object asचिन्हित to idx */
#घोषणा get_hdmi_pcm(spec, idx)	(&(spec)->pcm_rec[idx])
/* obtain hda_pcm object asचिन्हित to idx */
#घोषणा get_pcm_rec(spec, idx)	(get_hdmi_pcm(spec, idx)->pcm)

अटल पूर्णांक pin_id_to_pin_index(काष्ठा hda_codec *codec,
			       hda_nid_t pin_nid, पूर्णांक dev_id)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक pin_idx;
	काष्ठा hdmi_spec_per_pin *per_pin;

	/*
	 * (dev_id == -1) means it is NON-MST pin
	 * वापस the first भव pin on this port
	 */
	अगर (dev_id == -1)
		dev_id = 0;

	क्रम (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) अणु
		per_pin = get_pin(spec, pin_idx);
		अगर ((per_pin->pin_nid == pin_nid) &&
			(per_pin->dev_id == dev_id))
			वापस pin_idx;
	पूर्ण

	codec_warn(codec, "HDMI: pin NID 0x%x not registered\n", pin_nid);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hinfo_to_pcm_index(काष्ठा hda_codec *codec,
			काष्ठा hda_pcm_stream *hinfo)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक pcm_idx;

	क्रम (pcm_idx = 0; pcm_idx < spec->pcm_used; pcm_idx++)
		अगर (get_pcm_rec(spec, pcm_idx)->stream == hinfo)
			वापस pcm_idx;

	codec_warn(codec, "HDMI: hinfo %p not tied to a PCM\n", hinfo);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hinfo_to_pin_index(काष्ठा hda_codec *codec,
			      काष्ठा hda_pcm_stream *hinfo)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdmi_spec_per_pin *per_pin;
	पूर्णांक pin_idx;

	क्रम (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) अणु
		per_pin = get_pin(spec, pin_idx);
		अगर (per_pin->pcm &&
			per_pin->pcm->pcm->stream == hinfo)
			वापस pin_idx;
	पूर्ण

	codec_dbg(codec, "HDMI: hinfo %p (pcm %d) not registered\n", hinfo,
		  hinfo_to_pcm_index(codec, hinfo));
	वापस -EINVAL;
पूर्ण

अटल काष्ठा hdmi_spec_per_pin *pcm_idx_to_pin(काष्ठा hdmi_spec *spec,
						पूर्णांक pcm_idx)
अणु
	पूर्णांक i;
	काष्ठा hdmi_spec_per_pin *per_pin;

	क्रम (i = 0; i < spec->num_pins; i++) अणु
		per_pin = get_pin(spec, i);
		अगर (per_pin->pcm_idx == pcm_idx)
			वापस per_pin;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक cvt_nid_to_cvt_index(काष्ठा hda_codec *codec, hda_nid_t cvt_nid)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक cvt_idx;

	क्रम (cvt_idx = 0; cvt_idx < spec->num_cvts; cvt_idx++)
		अगर (get_cvt(spec, cvt_idx)->cvt_nid == cvt_nid)
			वापस cvt_idx;

	codec_warn(codec, "HDMI: cvt NID 0x%x not registered\n", cvt_nid);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hdmi_eld_ctl_info(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdmi_spec_per_pin *per_pin;
	काष्ठा hdmi_eld *eld;
	पूर्णांक pcm_idx;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;

	pcm_idx = kcontrol->निजी_value;
	mutex_lock(&spec->pcm_lock);
	per_pin = pcm_idx_to_pin(spec, pcm_idx);
	अगर (!per_pin) अणु
		/* no pin is bound to the pcm */
		uinfo->count = 0;
		जाओ unlock;
	पूर्ण
	eld = &per_pin->sink_eld;
	uinfo->count = eld->eld_valid ? eld->eld_size : 0;

 unlock:
	mutex_unlock(&spec->pcm_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_eld_ctl_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा hda_codec *codec = snd_kcontrol_chip(kcontrol);
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdmi_spec_per_pin *per_pin;
	काष्ठा hdmi_eld *eld;
	पूर्णांक pcm_idx;
	पूर्णांक err = 0;

	pcm_idx = kcontrol->निजी_value;
	mutex_lock(&spec->pcm_lock);
	per_pin = pcm_idx_to_pin(spec, pcm_idx);
	अगर (!per_pin) अणु
		/* no pin is bound to the pcm */
		स_रखो(ucontrol->value.bytes.data, 0,
		       ARRAY_SIZE(ucontrol->value.bytes.data));
		जाओ unlock;
	पूर्ण

	eld = &per_pin->sink_eld;
	अगर (eld->eld_size > ARRAY_SIZE(ucontrol->value.bytes.data) ||
	    eld->eld_size > ELD_MAX_SIZE) अणु
		snd_BUG();
		err = -EINVAL;
		जाओ unlock;
	पूर्ण

	स_रखो(ucontrol->value.bytes.data, 0,
	       ARRAY_SIZE(ucontrol->value.bytes.data));
	अगर (eld->eld_valid)
		स_नकल(ucontrol->value.bytes.data, eld->eld_buffer,
		       eld->eld_size);

 unlock:
	mutex_unlock(&spec->pcm_lock);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new eld_bytes_ctl = अणु
	.access = SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE |
		SNDRV_CTL_ELEM_ACCESS_SKIP_CHECK,
	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
	.name = "ELD",
	.info = hdmi_eld_ctl_info,
	.get = hdmi_eld_ctl_get,
पूर्ण;

अटल पूर्णांक hdmi_create_eld_ctl(काष्ठा hda_codec *codec, पूर्णांक pcm_idx,
			पूर्णांक device)
अणु
	काष्ठा snd_kcontrol *kctl;
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक err;

	kctl = snd_ctl_new1(&eld_bytes_ctl, codec);
	अगर (!kctl)
		वापस -ENOMEM;
	kctl->निजी_value = pcm_idx;
	kctl->id.device = device;

	/* no pin nid is associated with the kctl now
	 * tbd: associate pin nid to eld ctl later
	 */
	err = snd_hda_ctl_add(codec, 0, kctl);
	अगर (err < 0)
		वापस err;

	get_hdmi_pcm(spec, pcm_idx)->eld_ctl = kctl;
	वापस 0;
पूर्ण

#अगर_घोषित BE_PARANOID
अटल व्योम hdmi_get_dip_index(काष्ठा hda_codec *codec, hda_nid_t pin_nid,
				पूर्णांक *packet_index, पूर्णांक *byte_index)
अणु
	पूर्णांक val;

	val = snd_hda_codec_पढ़ो(codec, pin_nid, 0,
				 AC_VERB_GET_HDMI_DIP_INDEX, 0);

	*packet_index = val >> 5;
	*byte_index = val & 0x1f;
पूर्ण
#पूर्ण_अगर

अटल व्योम hdmi_set_dip_index(काष्ठा hda_codec *codec, hda_nid_t pin_nid,
				पूर्णांक packet_index, पूर्णांक byte_index)
अणु
	पूर्णांक val;

	val = (packet_index << 5) | (byte_index & 0x1f);

	snd_hda_codec_ग_लिखो(codec, pin_nid, 0, AC_VERB_SET_HDMI_DIP_INDEX, val);
पूर्ण

अटल व्योम hdmi_ग_लिखो_dip_byte(काष्ठा hda_codec *codec, hda_nid_t pin_nid,
				अचिन्हित अक्षर val)
अणु
	snd_hda_codec_ग_लिखो(codec, pin_nid, 0, AC_VERB_SET_HDMI_DIP_DATA, val);
पूर्ण

अटल व्योम hdmi_init_pin(काष्ठा hda_codec *codec, hda_nid_t pin_nid)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक pin_out;

	/* Unmute */
	अगर (get_wcaps(codec, pin_nid) & AC_WCAP_OUT_AMP)
		snd_hda_codec_ग_लिखो(codec, pin_nid, 0,
				AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_UNMUTE);

	अगर (spec->dyn_pin_out)
		/* Disable pin out until stream is active */
		pin_out = 0;
	अन्यथा
		/* Enable pin out: some machines with GM965 माला_लो broken output
		 * when the pin is disabled or changed जबतक using with HDMI
		 */
		pin_out = PIN_OUT;

	snd_hda_codec_ग_लिखो(codec, pin_nid, 0,
			    AC_VERB_SET_PIN_WIDGET_CONTROL, pin_out);
पूर्ण

/*
 * ELD proc files
 */

#अगर_घोषित CONFIG_SND_PROC_FS
अटल व्योम prपूर्णांक_eld_info(काष्ठा snd_info_entry *entry,
			   काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा hdmi_spec_per_pin *per_pin = entry->निजी_data;

	mutex_lock(&per_pin->lock);
	snd_hdmi_prपूर्णांक_eld_info(&per_pin->sink_eld, buffer);
	mutex_unlock(&per_pin->lock);
पूर्ण

अटल व्योम ग_लिखो_eld_info(काष्ठा snd_info_entry *entry,
			   काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा hdmi_spec_per_pin *per_pin = entry->निजी_data;

	mutex_lock(&per_pin->lock);
	snd_hdmi_ग_लिखो_eld_info(&per_pin->sink_eld, buffer);
	mutex_unlock(&per_pin->lock);
पूर्ण

अटल पूर्णांक eld_proc_new(काष्ठा hdmi_spec_per_pin *per_pin, पूर्णांक index)
अणु
	अक्षर name[32];
	काष्ठा hda_codec *codec = per_pin->codec;
	काष्ठा snd_info_entry *entry;
	पूर्णांक err;

	snम_लिखो(name, माप(name), "eld#%d.%d", codec->addr, index);
	err = snd_card_proc_new(codec->card, name, &entry);
	अगर (err < 0)
		वापस err;

	snd_info_set_text_ops(entry, per_pin, prपूर्णांक_eld_info);
	entry->c.text.ग_लिखो = ग_लिखो_eld_info;
	entry->mode |= 0200;
	per_pin->proc_entry = entry;

	वापस 0;
पूर्ण

अटल व्योम eld_proc_मुक्त(काष्ठा hdmi_spec_per_pin *per_pin)
अणु
	अगर (!per_pin->codec->bus->shutकरोwn) अणु
		snd_info_मुक्त_entry(per_pin->proc_entry);
		per_pin->proc_entry = शून्य;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक eld_proc_new(काष्ठा hdmi_spec_per_pin *per_pin,
			       पूर्णांक index)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम eld_proc_मुक्त(काष्ठा hdmi_spec_per_pin *per_pin)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * Audio InfoFrame routines
 */

/*
 * Enable Audio InfoFrame Transmission
 */
अटल व्योम hdmi_start_infoframe_trans(काष्ठा hda_codec *codec,
				       hda_nid_t pin_nid)
अणु
	hdmi_set_dip_index(codec, pin_nid, 0x0, 0x0);
	snd_hda_codec_ग_लिखो(codec, pin_nid, 0, AC_VERB_SET_HDMI_DIP_XMIT,
						AC_DIPXMIT_BEST);
पूर्ण

/*
 * Disable Audio InfoFrame Transmission
 */
अटल व्योम hdmi_stop_infoframe_trans(काष्ठा hda_codec *codec,
				      hda_nid_t pin_nid)
अणु
	hdmi_set_dip_index(codec, pin_nid, 0x0, 0x0);
	snd_hda_codec_ग_लिखो(codec, pin_nid, 0, AC_VERB_SET_HDMI_DIP_XMIT,
						AC_DIPXMIT_DISABLE);
पूर्ण

अटल व्योम hdmi_debug_dip_size(काष्ठा hda_codec *codec, hda_nid_t pin_nid)
अणु
#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
	पूर्णांक i;
	पूर्णांक size;

	size = snd_hdmi_get_eld_size(codec, pin_nid);
	codec_dbg(codec, "HDMI: ELD buf size is %d\n", size);

	क्रम (i = 0; i < 8; i++) अणु
		size = snd_hda_codec_पढ़ो(codec, pin_nid, 0,
						AC_VERB_GET_HDMI_DIP_SIZE, i);
		codec_dbg(codec, "HDMI: DIP GP[%d] buf size is %d\n", i, size);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम hdmi_clear_dip_buffers(काष्ठा hda_codec *codec, hda_nid_t pin_nid)
अणु
#अगर_घोषित BE_PARANOID
	पूर्णांक i, j;
	पूर्णांक size;
	पूर्णांक pi, bi;
	क्रम (i = 0; i < 8; i++) अणु
		size = snd_hda_codec_पढ़ो(codec, pin_nid, 0,
						AC_VERB_GET_HDMI_DIP_SIZE, i);
		अगर (size == 0)
			जारी;

		hdmi_set_dip_index(codec, pin_nid, i, 0x0);
		क्रम (j = 1; j < 1000; j++) अणु
			hdmi_ग_लिखो_dip_byte(codec, pin_nid, 0x0);
			hdmi_get_dip_index(codec, pin_nid, &pi, &bi);
			अगर (pi != i)
				codec_dbg(codec, "dip index %d: %d != %d\n",
						bi, pi, i);
			अगर (bi == 0) /* byte index wrapped around */
				अवरोध;
		पूर्ण
		codec_dbg(codec,
			"HDMI: DIP GP[%d] buf reported size=%d, written=%d\n",
			i, size, j);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम hdmi_checksum_audio_infoframe(काष्ठा hdmi_audio_infoframe *hdmi_ai)
अणु
	u8 *bytes = (u8 *)hdmi_ai;
	u8 sum = 0;
	पूर्णांक i;

	hdmi_ai->checksum = 0;

	क्रम (i = 0; i < माप(*hdmi_ai); i++)
		sum += bytes[i];

	hdmi_ai->checksum = -sum;
पूर्ण

अटल व्योम hdmi_fill_audio_infoframe(काष्ठा hda_codec *codec,
				      hda_nid_t pin_nid,
				      u8 *dip, पूर्णांक size)
अणु
	पूर्णांक i;

	hdmi_debug_dip_size(codec, pin_nid);
	hdmi_clear_dip_buffers(codec, pin_nid); /* be paranoid */

	hdmi_set_dip_index(codec, pin_nid, 0x0, 0x0);
	क्रम (i = 0; i < size; i++)
		hdmi_ग_लिखो_dip_byte(codec, pin_nid, dip[i]);
पूर्ण

अटल bool hdmi_infoframe_uptodate(काष्ठा hda_codec *codec, hda_nid_t pin_nid,
				    u8 *dip, पूर्णांक size)
अणु
	u8 val;
	पूर्णांक i;

	hdmi_set_dip_index(codec, pin_nid, 0x0, 0x0);
	अगर (snd_hda_codec_पढ़ो(codec, pin_nid, 0, AC_VERB_GET_HDMI_DIP_XMIT, 0)
							    != AC_DIPXMIT_BEST)
		वापस false;

	क्रम (i = 0; i < size; i++) अणु
		val = snd_hda_codec_पढ़ो(codec, pin_nid, 0,
					 AC_VERB_GET_HDMI_DIP_DATA, 0);
		अगर (val != dip[i])
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक hdmi_pin_get_eld(काष्ठा hda_codec *codec, hda_nid_t nid,
			    पूर्णांक dev_id, अचिन्हित अक्षर *buf, पूर्णांक *eld_size)
अणु
	snd_hda_set_dev_select(codec, nid, dev_id);

	वापस snd_hdmi_get_eld(codec, nid, buf, eld_size);
पूर्ण

अटल व्योम hdmi_pin_setup_infoframe(काष्ठा hda_codec *codec,
				     hda_nid_t pin_nid, पूर्णांक dev_id,
				     पूर्णांक ca, पूर्णांक active_channels,
				     पूर्णांक conn_type)
अणु
	जोड़ audio_infoframe ai;

	स_रखो(&ai, 0, माप(ai));
	अगर (conn_type == 0) अणु /* HDMI */
		काष्ठा hdmi_audio_infoframe *hdmi_ai = &ai.hdmi;

		hdmi_ai->type		= 0x84;
		hdmi_ai->ver		= 0x01;
		hdmi_ai->len		= 0x0a;
		hdmi_ai->CC02_CT47	= active_channels - 1;
		hdmi_ai->CA		= ca;
		hdmi_checksum_audio_infoframe(hdmi_ai);
	पूर्ण अन्यथा अगर (conn_type == 1) अणु /* DisplayPort */
		काष्ठा dp_audio_infoframe *dp_ai = &ai.dp;

		dp_ai->type		= 0x84;
		dp_ai->len		= 0x1b;
		dp_ai->ver		= 0x11 << 2;
		dp_ai->CC02_CT47	= active_channels - 1;
		dp_ai->CA		= ca;
	पूर्ण अन्यथा अणु
		codec_dbg(codec, "HDMI: unknown connection type at pin NID 0x%x\n", pin_nid);
		वापस;
	पूर्ण

	snd_hda_set_dev_select(codec, pin_nid, dev_id);

	/*
	 * माप(ai) is used instead of माप(*hdmi_ai) or
	 * माप(*dp_ai) to aव्योम partial match/update problems when
	 * the user चयनes between HDMI/DP monitors.
	 */
	अगर (!hdmi_infoframe_uptodate(codec, pin_nid, ai.bytes,
					माप(ai))) अणु
		codec_dbg(codec, "%s: pin NID=0x%x channels=%d ca=0x%02x\n",
			  __func__, pin_nid, active_channels, ca);
		hdmi_stop_infoframe_trans(codec, pin_nid);
		hdmi_fill_audio_infoframe(codec, pin_nid,
					    ai.bytes, माप(ai));
		hdmi_start_infoframe_trans(codec, pin_nid);
	पूर्ण
पूर्ण

अटल व्योम hdmi_setup_audio_infoframe(काष्ठा hda_codec *codec,
				       काष्ठा hdmi_spec_per_pin *per_pin,
				       bool non_pcm)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdac_chmap *chmap = &spec->chmap;
	hda_nid_t pin_nid = per_pin->pin_nid;
	पूर्णांक dev_id = per_pin->dev_id;
	पूर्णांक channels = per_pin->channels;
	पूर्णांक active_channels;
	काष्ठा hdmi_eld *eld;
	पूर्णांक ca;

	अगर (!channels)
		वापस;

	snd_hda_set_dev_select(codec, pin_nid, dev_id);

	/* some HW (e.g. HSW+) needs reprogramming the amp at each समय */
	अगर (get_wcaps(codec, pin_nid) & AC_WCAP_OUT_AMP)
		snd_hda_codec_ग_लिखो(codec, pin_nid, 0,
					    AC_VERB_SET_AMP_GAIN_MUTE,
					    AMP_OUT_UNMUTE);

	eld = &per_pin->sink_eld;

	ca = snd_hdac_channel_allocation(&codec->core,
			eld->info.spk_alloc, channels,
			per_pin->chmap_set, non_pcm, per_pin->chmap);

	active_channels = snd_hdac_get_active_channels(ca);

	chmap->ops.set_channel_count(&codec->core, per_pin->cvt_nid,
						active_channels);

	/*
	 * always configure channel mapping, it may have been changed by the
	 * user in the meanसमय
	 */
	snd_hdac_setup_channel_mapping(&spec->chmap,
				pin_nid, non_pcm, ca, channels,
				per_pin->chmap, per_pin->chmap_set);

	spec->ops.pin_setup_infoframe(codec, pin_nid, dev_id,
				      ca, active_channels, eld->info.conn_type);

	per_pin->non_pcm = non_pcm;
पूर्ण

/*
 * Unsolicited events
 */

अटल व्योम hdmi_present_sense(काष्ठा hdmi_spec_per_pin *per_pin, पूर्णांक repoll);

अटल व्योम check_presence_and_report(काष्ठा hda_codec *codec, hda_nid_t nid,
				      पूर्णांक dev_id)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक pin_idx = pin_id_to_pin_index(codec, nid, dev_id);

	अगर (pin_idx < 0)
		वापस;
	mutex_lock(&spec->pcm_lock);
	hdmi_present_sense(get_pin(spec, pin_idx), 1);
	mutex_unlock(&spec->pcm_lock);
पूर्ण

अटल व्योम jack_callback(काष्ठा hda_codec *codec,
			  काष्ठा hda_jack_callback *jack)
अणु
	/* stop polling when notअगरication is enabled */
	अगर (codec_has_acomp(codec))
		वापस;

	check_presence_and_report(codec, jack->nid, jack->dev_id);
पूर्ण

अटल व्योम hdmi_पूर्णांकrinsic_event(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक res,
				 काष्ठा hda_jack_tbl *jack)
अणु
	jack->jack_dirty = 1;

	codec_dbg(codec,
		"HDMI hot plug event: Codec=%d NID=0x%x Device=%d Inactive=%d Presence_Detect=%d ELD_Valid=%d\n",
		codec->addr, jack->nid, jack->dev_id, !!(res & AC_UNSOL_RES_IA),
		!!(res & AC_UNSOL_RES_PD), !!(res & AC_UNSOL_RES_ELDV));

	check_presence_and_report(codec, jack->nid, jack->dev_id);
पूर्ण

अटल व्योम hdmi_non_पूर्णांकrinsic_event(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक res)
अणु
	पूर्णांक tag = res >> AC_UNSOL_RES_TAG_SHIFT;
	पूर्णांक subtag = (res & AC_UNSOL_RES_SUBTAG) >> AC_UNSOL_RES_SUBTAG_SHIFT;
	पूर्णांक cp_state = !!(res & AC_UNSOL_RES_CP_STATE);
	पूर्णांक cp_पढ़ोy = !!(res & AC_UNSOL_RES_CP_READY);

	codec_info(codec,
		"HDMI CP event: CODEC=%d TAG=%d SUBTAG=0x%x CP_STATE=%d CP_READY=%d\n",
		codec->addr,
		tag,
		subtag,
		cp_state,
		cp_पढ़ोy);

	/* TODO */
	अगर (cp_state) अणु
		;
	पूर्ण
	अगर (cp_पढ़ोy) अणु
		;
	पूर्ण
पूर्ण


अटल व्योम hdmi_unsol_event(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक res)
अणु
	पूर्णांक tag = res >> AC_UNSOL_RES_TAG_SHIFT;
	पूर्णांक subtag = (res & AC_UNSOL_RES_SUBTAG) >> AC_UNSOL_RES_SUBTAG_SHIFT;
	काष्ठा hda_jack_tbl *jack;

	अगर (codec_has_acomp(codec))
		वापस;

	अगर (codec->dp_mst) अणु
		पूर्णांक dev_entry =
			(res & AC_UNSOL_RES_DE) >> AC_UNSOL_RES_DE_SHIFT;

		jack = snd_hda_jack_tbl_get_from_tag(codec, tag, dev_entry);
	पूर्ण अन्यथा अणु
		jack = snd_hda_jack_tbl_get_from_tag(codec, tag, 0);
	पूर्ण

	अगर (!jack) अणु
		codec_dbg(codec, "Unexpected HDMI event tag 0x%x\n", tag);
		वापस;
	पूर्ण

	अगर (subtag == 0)
		hdmi_पूर्णांकrinsic_event(codec, res, jack);
	अन्यथा
		hdmi_non_पूर्णांकrinsic_event(codec, res);
पूर्ण

अटल व्योम haswell_verअगरy_D0(काष्ठा hda_codec *codec,
		hda_nid_t cvt_nid, hda_nid_t nid)
अणु
	पूर्णांक pwr;

	/* For Haswell, the converter 1/2 may keep in D3 state after bootup,
	 * thus pins could only choose converter 0 क्रम use. Make sure the
	 * converters are in correct घातer state */
	अगर (!snd_hda_check_घातer_state(codec, cvt_nid, AC_PWRST_D0))
		snd_hda_codec_ग_लिखो(codec, cvt_nid, 0, AC_VERB_SET_POWER_STATE, AC_PWRST_D0);

	अगर (!snd_hda_check_घातer_state(codec, nid, AC_PWRST_D0)) अणु
		snd_hda_codec_ग_लिखो(codec, nid, 0, AC_VERB_SET_POWER_STATE,
				    AC_PWRST_D0);
		msleep(40);
		pwr = snd_hda_codec_पढ़ो(codec, nid, 0, AC_VERB_GET_POWER_STATE, 0);
		pwr = (pwr & AC_PWRST_ACTUAL) >> AC_PWRST_ACTUAL_SHIFT;
		codec_dbg(codec, "Haswell HDMI audio: Power for NID 0x%x is now D%d\n", nid, pwr);
	पूर्ण
पूर्ण

/*
 * Callbacks
 */

/* HBR should be Non-PCM, 8 channels */
#घोषणा is_hbr_क्रमmat(क्रमmat) \
	((क्रमmat & AC_FMT_TYPE_NON_PCM) && (क्रमmat & AC_FMT_CHAN_MASK) == 7)

अटल पूर्णांक hdmi_pin_hbr_setup(काष्ठा hda_codec *codec, hda_nid_t pin_nid,
			      पूर्णांक dev_id, bool hbr)
अणु
	पूर्णांक pinctl, new_pinctl;

	अगर (snd_hda_query_pin_caps(codec, pin_nid) & AC_PINCAP_HBR) अणु
		snd_hda_set_dev_select(codec, pin_nid, dev_id);
		pinctl = snd_hda_codec_पढ़ो(codec, pin_nid, 0,
					    AC_VERB_GET_PIN_WIDGET_CONTROL, 0);

		अगर (pinctl < 0)
			वापस hbr ? -EINVAL : 0;

		new_pinctl = pinctl & ~AC_PINCTL_EPT;
		अगर (hbr)
			new_pinctl |= AC_PINCTL_EPT_HBR;
		अन्यथा
			new_pinctl |= AC_PINCTL_EPT_NATIVE;

		codec_dbg(codec,
			  "hdmi_pin_hbr_setup: NID=0x%x, %spinctl=0x%x\n",
			    pin_nid,
			    pinctl == new_pinctl ? "" : "new-",
			    new_pinctl);

		अगर (pinctl != new_pinctl)
			snd_hda_codec_ग_लिखो(codec, pin_nid, 0,
					    AC_VERB_SET_PIN_WIDGET_CONTROL,
					    new_pinctl);
	पूर्ण अन्यथा अगर (hbr)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_setup_stream(काष्ठा hda_codec *codec, hda_nid_t cvt_nid,
			      hda_nid_t pin_nid, पूर्णांक dev_id,
			      u32 stream_tag, पूर्णांक क्रमmat)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	अचिन्हित पूर्णांक param;
	पूर्णांक err;

	err = spec->ops.pin_hbr_setup(codec, pin_nid, dev_id,
				      is_hbr_क्रमmat(क्रमmat));

	अगर (err) अणु
		codec_dbg(codec, "hdmi_setup_stream: HBR is not supported\n");
		वापस err;
	पूर्ण

	अगर (spec->पूर्णांकel_hsw_fixup) अणु

		/*
		 * on recent platक्रमms IEC Coding Type is required क्रम HBR
		 * support, पढ़ो current Digital Converter settings and set
		 * ICT bitfield अगर needed.
		 */
		param = snd_hda_codec_पढ़ो(codec, cvt_nid, 0,
					   AC_VERB_GET_DIGI_CONVERT_1, 0);

		param = (param >> 16) & ~(AC_DIG3_ICT);

		/* on recent platक्रमms ICT mode is required क्रम HBR support */
		अगर (is_hbr_क्रमmat(क्रमmat))
			param |= 0x1;

		snd_hda_codec_ग_लिखो(codec, cvt_nid, 0,
				    AC_VERB_SET_DIGI_CONVERT_3, param);
	पूर्ण

	snd_hda_codec_setup_stream(codec, cvt_nid, stream_tag, 0, क्रमmat);
	वापस 0;
पूर्ण

/* Try to find an available converter
 * If pin_idx is less then zero, just try to find an available converter.
 * Otherwise, try to find an available converter and get the cvt mux index
 * of the pin.
 */
अटल पूर्णांक hdmi_choose_cvt(काष्ठा hda_codec *codec,
			   पूर्णांक pin_idx, पूर्णांक *cvt_id)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdmi_spec_per_pin *per_pin;
	काष्ठा hdmi_spec_per_cvt *per_cvt = शून्य;
	पूर्णांक cvt_idx, mux_idx = 0;

	/* pin_idx < 0 means no pin will be bound to the converter */
	अगर (pin_idx < 0)
		per_pin = शून्य;
	अन्यथा
		per_pin = get_pin(spec, pin_idx);

	अगर (per_pin && per_pin->silent_stream) अणु
		cvt_idx = cvt_nid_to_cvt_index(codec, per_pin->cvt_nid);
		अगर (cvt_id)
			*cvt_id = cvt_idx;
		वापस 0;
	पूर्ण

	/* Dynamically assign converter to stream */
	क्रम (cvt_idx = 0; cvt_idx < spec->num_cvts; cvt_idx++) अणु
		per_cvt = get_cvt(spec, cvt_idx);

		/* Must not alपढ़ोy be asचिन्हित */
		अगर (per_cvt->asचिन्हित)
			जारी;
		अगर (per_pin == शून्य)
			अवरोध;
		/* Must be in pin's mux's list of converters */
		क्रम (mux_idx = 0; mux_idx < per_pin->num_mux_nids; mux_idx++)
			अगर (per_pin->mux_nids[mux_idx] == per_cvt->cvt_nid)
				अवरोध;
		/* Not in mux list */
		अगर (mux_idx == per_pin->num_mux_nids)
			जारी;
		अवरोध;
	पूर्ण

	/* No मुक्त converters */
	अगर (cvt_idx == spec->num_cvts)
		वापस -EBUSY;

	अगर (per_pin != शून्य)
		per_pin->mux_idx = mux_idx;

	अगर (cvt_id)
		*cvt_id = cvt_idx;

	वापस 0;
पूर्ण

/* Assure the pin select the right convetor */
अटल व्योम पूर्णांकel_verअगरy_pin_cvt_connect(काष्ठा hda_codec *codec,
			काष्ठा hdmi_spec_per_pin *per_pin)
अणु
	hda_nid_t pin_nid = per_pin->pin_nid;
	पूर्णांक mux_idx, curr;

	mux_idx = per_pin->mux_idx;
	curr = snd_hda_codec_पढ़ो(codec, pin_nid, 0,
					  AC_VERB_GET_CONNECT_SEL, 0);
	अगर (curr != mux_idx)
		snd_hda_codec_ग_लिखो_cache(codec, pin_nid, 0,
					    AC_VERB_SET_CONNECT_SEL,
					    mux_idx);
पूर्ण

/* get the mux index क्रम the converter of the pins
 * converter's mux index is the same क्रम all pins on Intel platक्रमm
 */
अटल पूर्णांक पूर्णांकel_cvt_id_to_mux_idx(काष्ठा hdmi_spec *spec,
			hda_nid_t cvt_nid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < spec->num_cvts; i++)
		अगर (spec->cvt_nids[i] == cvt_nid)
			वापस i;
	वापस -EINVAL;
पूर्ण

/* Intel HDMI workaround to fix audio routing issue:
 * For some Intel display codecs, pins share the same connection list.
 * So a conveter can be selected by multiple pins and playback on any of these
 * pins will generate sound on the बाह्यal display, because audio flows from
 * the same converter to the display pipeline. Also muting one pin may make
 * other pins have no sound output.
 * So this function assures that an asचिन्हित converter क्रम a pin is not selected
 * by any other pins.
 */
अटल व्योम पूर्णांकel_not_share_asचिन्हित_cvt(काष्ठा hda_codec *codec,
					 hda_nid_t pin_nid,
					 पूर्णांक dev_id, पूर्णांक mux_idx)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	hda_nid_t nid;
	पूर्णांक cvt_idx, curr;
	काष्ठा hdmi_spec_per_cvt *per_cvt;
	काष्ठा hdmi_spec_per_pin *per_pin;
	पूर्णांक pin_idx;

	/* configure the pins connections */
	क्रम (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) अणु
		पूर्णांक dev_id_saved;
		पूर्णांक dev_num;

		per_pin = get_pin(spec, pin_idx);
		/*
		 * pin not connected to monitor
		 * no need to operate on it
		 */
		अगर (!per_pin->pcm)
			जारी;

		अगर ((per_pin->pin_nid == pin_nid) &&
			(per_pin->dev_id == dev_id))
			जारी;

		/*
		 * अगर per_pin->dev_id >= dev_num,
		 * snd_hda_get_dev_select() will fail,
		 * and the following operation is unpredictable.
		 * So skip this situation.
		 */
		dev_num = snd_hda_get_num_devices(codec, per_pin->pin_nid) + 1;
		अगर (per_pin->dev_id >= dev_num)
			जारी;

		nid = per_pin->pin_nid;

		/*
		 * Calling this function should not impact
		 * on the device entry selection
		 * So let's save the dev id क्रम each pin,
		 * and restore it when वापस
		 */
		dev_id_saved = snd_hda_get_dev_select(codec, nid);
		snd_hda_set_dev_select(codec, nid, per_pin->dev_id);
		curr = snd_hda_codec_पढ़ो(codec, nid, 0,
					  AC_VERB_GET_CONNECT_SEL, 0);
		अगर (curr != mux_idx) अणु
			snd_hda_set_dev_select(codec, nid, dev_id_saved);
			जारी;
		पूर्ण


		/* choose an unasचिन्हित converter. The conveters in the
		 * connection list are in the same order as in the codec.
		 */
		क्रम (cvt_idx = 0; cvt_idx < spec->num_cvts; cvt_idx++) अणु
			per_cvt = get_cvt(spec, cvt_idx);
			अगर (!per_cvt->asचिन्हित) अणु
				codec_dbg(codec,
					  "choose cvt %d for pin NID 0x%x\n",
					  cvt_idx, nid);
				snd_hda_codec_ग_लिखो_cache(codec, nid, 0,
					    AC_VERB_SET_CONNECT_SEL,
					    cvt_idx);
				अवरोध;
			पूर्ण
		पूर्ण
		snd_hda_set_dev_select(codec, nid, dev_id_saved);
	पूर्ण
पूर्ण

/* A wrapper of पूर्णांकel_not_share_aचिन्हित_cvt() */
अटल व्योम पूर्णांकel_not_share_asचिन्हित_cvt_nid(काष्ठा hda_codec *codec,
			hda_nid_t pin_nid, पूर्णांक dev_id, hda_nid_t cvt_nid)
अणु
	पूर्णांक mux_idx;
	काष्ठा hdmi_spec *spec = codec->spec;

	/* On Intel platक्रमm, the mapping of converter nid to
	 * mux index of the pins are always the same.
	 * The pin nid may be 0, this means all pins will not
	 * share the converter.
	 */
	mux_idx = पूर्णांकel_cvt_id_to_mux_idx(spec, cvt_nid);
	अगर (mux_idx >= 0)
		पूर्णांकel_not_share_asचिन्हित_cvt(codec, pin_nid, dev_id, mux_idx);
पूर्ण

/* skeleton caller of pin_cvt_fixup ops */
अटल व्योम pin_cvt_fixup(काष्ठा hda_codec *codec,
			  काष्ठा hdmi_spec_per_pin *per_pin,
			  hda_nid_t cvt_nid)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;

	अगर (spec->ops.pin_cvt_fixup)
		spec->ops.pin_cvt_fixup(codec, per_pin, cvt_nid);
पूर्ण

/* called in hdmi_pcm_खोलो when no pin is asचिन्हित to the PCM
 * in dyn_pcm_assign mode.
 */
अटल पूर्णांक hdmi_pcm_खोलो_no_pin(काष्ठा hda_pcm_stream *hinfo,
			 काष्ठा hda_codec *codec,
			 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक cvt_idx, pcm_idx;
	काष्ठा hdmi_spec_per_cvt *per_cvt = शून्य;
	पूर्णांक err;

	pcm_idx = hinfo_to_pcm_index(codec, hinfo);
	अगर (pcm_idx < 0)
		वापस -EINVAL;

	err = hdmi_choose_cvt(codec, -1, &cvt_idx);
	अगर (err)
		वापस err;

	per_cvt = get_cvt(spec, cvt_idx);
	per_cvt->asचिन्हित = 1;
	hinfo->nid = per_cvt->cvt_nid;

	pin_cvt_fixup(codec, शून्य, per_cvt->cvt_nid);

	set_bit(pcm_idx, &spec->pcm_in_use);
	/* toकरो: setup spdअगर ctls assign */

	/* Initially set the converter's capabilities */
	hinfo->channels_min = per_cvt->channels_min;
	hinfo->channels_max = per_cvt->channels_max;
	hinfo->rates = per_cvt->rates;
	hinfo->क्रमmats = per_cvt->क्रमmats;
	hinfo->maxbps = per_cvt->maxbps;

	/* Store the updated parameters */
	runसमय->hw.channels_min = hinfo->channels_min;
	runसमय->hw.channels_max = hinfo->channels_max;
	runसमय->hw.क्रमmats = hinfo->क्रमmats;
	runसमय->hw.rates = hinfo->rates;

	snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
				   SNDRV_PCM_HW_PARAM_CHANNELS, 2);
	वापस 0;
पूर्ण

/*
 * HDA PCM callbacks
 */
अटल पूर्णांक hdmi_pcm_खोलो(काष्ठा hda_pcm_stream *hinfo,
			 काष्ठा hda_codec *codec,
			 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक pin_idx, cvt_idx, pcm_idx;
	काष्ठा hdmi_spec_per_pin *per_pin;
	काष्ठा hdmi_eld *eld;
	काष्ठा hdmi_spec_per_cvt *per_cvt = शून्य;
	पूर्णांक err;

	/* Validate hinfo */
	pcm_idx = hinfo_to_pcm_index(codec, hinfo);
	अगर (pcm_idx < 0)
		वापस -EINVAL;

	mutex_lock(&spec->pcm_lock);
	pin_idx = hinfo_to_pin_index(codec, hinfo);
	अगर (!spec->dyn_pcm_assign) अणु
		अगर (snd_BUG_ON(pin_idx < 0)) अणु
			err = -EINVAL;
			जाओ unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* no pin is asचिन्हित to the PCM
		 * PA need pcm खोलो successfully when probe
		 */
		अगर (pin_idx < 0) अणु
			err = hdmi_pcm_खोलो_no_pin(hinfo, codec, substream);
			जाओ unlock;
		पूर्ण
	पूर्ण

	err = hdmi_choose_cvt(codec, pin_idx, &cvt_idx);
	अगर (err < 0)
		जाओ unlock;

	per_cvt = get_cvt(spec, cvt_idx);
	/* Claim converter */
	per_cvt->asचिन्हित = 1;

	set_bit(pcm_idx, &spec->pcm_in_use);
	per_pin = get_pin(spec, pin_idx);
	per_pin->cvt_nid = per_cvt->cvt_nid;
	hinfo->nid = per_cvt->cvt_nid;

	/* flip stripe flag क्रम the asचिन्हित stream अगर supported */
	अगर (get_wcaps(codec, per_cvt->cvt_nid) & AC_WCAP_STRIPE)
		azx_stream(get_azx_dev(substream))->stripe = 1;

	snd_hda_set_dev_select(codec, per_pin->pin_nid, per_pin->dev_id);
	snd_hda_codec_ग_लिखो_cache(codec, per_pin->pin_nid, 0,
			    AC_VERB_SET_CONNECT_SEL,
			    per_pin->mux_idx);

	/* configure unused pins to choose other converters */
	pin_cvt_fixup(codec, per_pin, 0);

	snd_hda_spdअगर_ctls_assign(codec, pcm_idx, per_cvt->cvt_nid);

	/* Initially set the converter's capabilities */
	hinfo->channels_min = per_cvt->channels_min;
	hinfo->channels_max = per_cvt->channels_max;
	hinfo->rates = per_cvt->rates;
	hinfo->क्रमmats = per_cvt->क्रमmats;
	hinfo->maxbps = per_cvt->maxbps;

	eld = &per_pin->sink_eld;
	/* Restrict capabilities by ELD अगर this isn't disabled */
	अगर (!अटल_hdmi_pcm && eld->eld_valid) अणु
		snd_hdmi_eld_update_pcm_info(&eld->info, hinfo);
		अगर (hinfo->channels_min > hinfo->channels_max ||
		    !hinfo->rates || !hinfo->क्रमmats) अणु
			per_cvt->asचिन्हित = 0;
			hinfo->nid = 0;
			snd_hda_spdअगर_ctls_unassign(codec, pcm_idx);
			err = -ENODEV;
			जाओ unlock;
		पूर्ण
	पूर्ण

	/* Store the updated parameters */
	runसमय->hw.channels_min = hinfo->channels_min;
	runसमय->hw.channels_max = hinfo->channels_max;
	runसमय->hw.क्रमmats = hinfo->क्रमmats;
	runसमय->hw.rates = hinfo->rates;

	snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
				   SNDRV_PCM_HW_PARAM_CHANNELS, 2);
 unlock:
	mutex_unlock(&spec->pcm_lock);
	वापस err;
पूर्ण

/*
 * HDA/HDMI स्वतः parsing
 */
अटल पूर्णांक hdmi_पढ़ो_pin_conn(काष्ठा hda_codec *codec, पूर्णांक pin_idx)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdmi_spec_per_pin *per_pin = get_pin(spec, pin_idx);
	hda_nid_t pin_nid = per_pin->pin_nid;
	पूर्णांक dev_id = per_pin->dev_id;
	पूर्णांक conns;

	अगर (!(get_wcaps(codec, pin_nid) & AC_WCAP_CONN_LIST)) अणु
		codec_warn(codec,
			   "HDMI: pin NID 0x%x wcaps %#x does not support connection list\n",
			   pin_nid, get_wcaps(codec, pin_nid));
		वापस -EINVAL;
	पूर्ण

	snd_hda_set_dev_select(codec, pin_nid, dev_id);

	अगर (spec->पूर्णांकel_hsw_fixup) अणु
		conns = spec->num_cvts;
		स_नकल(per_pin->mux_nids, spec->cvt_nids,
		       माप(hda_nid_t) * conns);
	पूर्ण अन्यथा अणु
		conns = snd_hda_get_raw_connections(codec, pin_nid,
						    per_pin->mux_nids,
						    HDA_MAX_CONNECTIONS);
	पूर्ण

	/* all the device entries on the same pin have the same conn list */
	per_pin->num_mux_nids = conns;

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_find_pcm_slot(काष्ठा hdmi_spec *spec,
			      काष्ठा hdmi_spec_per_pin *per_pin)
अणु
	पूर्णांक i;

	/* on the new machines, try to assign the pcm slot dynamically,
	 * not use the preferred fixed map (legacy way) anymore.
	 */
	अगर (spec->dyn_pcm_no_legacy)
		जाओ last_try;

	/*
	 * generic_hdmi_build_pcms() may allocate extra PCMs on some
	 * platक्रमms (with maximum of 'num_nids + dev_num - 1')
	 *
	 * The per_pin of pin_nid_idx=n and dev_id=m prefers to get pcm-n
	 * अगर m==0. This guarantees that dynamic pcm assignments are compatible
	 * with the legacy अटल per_pin-pcm assignment that existed in the
	 * days beक्रमe DP-MST.
	 *
	 * Intel DP-MST prefers this legacy behavior क्रम compatibility, too.
	 *
	 * per_pin of m!=0 prefers to get pcm=(num_nids + (m - 1)).
	 */

	अगर (per_pin->dev_id == 0 || spec->पूर्णांकel_hsw_fixup) अणु
		अगर (!test_bit(per_pin->pin_nid_idx, &spec->pcm_biपंचांगap))
			वापस per_pin->pin_nid_idx;
	पूर्ण अन्यथा अणु
		i = spec->num_nids + (per_pin->dev_id - 1);
		अगर (i < spec->pcm_used && !(test_bit(i, &spec->pcm_biपंचांगap)))
			वापस i;
	पूर्ण

	/* have a second try; check the area over num_nids */
	क्रम (i = spec->num_nids; i < spec->pcm_used; i++) अणु
		अगर (!test_bit(i, &spec->pcm_biपंचांगap))
			वापस i;
	पूर्ण

 last_try:
	/* the last try; check the empty slots in pins */
	क्रम (i = 0; i < spec->num_nids; i++) अणु
		अगर (!test_bit(i, &spec->pcm_biपंचांगap))
			वापस i;
	पूर्ण
	वापस -EBUSY;
पूर्ण

अटल व्योम hdmi_attach_hda_pcm(काष्ठा hdmi_spec *spec,
				काष्ठा hdmi_spec_per_pin *per_pin)
अणु
	पूर्णांक idx;

	/* pcm alपढ़ोy be attached to the pin */
	अगर (per_pin->pcm)
		वापस;
	idx = hdmi_find_pcm_slot(spec, per_pin);
	अगर (idx == -EBUSY)
		वापस;
	per_pin->pcm_idx = idx;
	per_pin->pcm = get_hdmi_pcm(spec, idx);
	set_bit(idx, &spec->pcm_biपंचांगap);
पूर्ण

अटल व्योम hdmi_detach_hda_pcm(काष्ठा hdmi_spec *spec,
				काष्ठा hdmi_spec_per_pin *per_pin)
अणु
	पूर्णांक idx;

	/* pcm alपढ़ोy be detached from the pin */
	अगर (!per_pin->pcm)
		वापस;
	idx = per_pin->pcm_idx;
	per_pin->pcm_idx = -1;
	per_pin->pcm = शून्य;
	अगर (idx >= 0 && idx < spec->pcm_used)
		clear_bit(idx, &spec->pcm_biपंचांगap);
पूर्ण

अटल पूर्णांक hdmi_get_pin_cvt_mux(काष्ठा hdmi_spec *spec,
		काष्ठा hdmi_spec_per_pin *per_pin, hda_nid_t cvt_nid)
अणु
	पूर्णांक mux_idx;

	क्रम (mux_idx = 0; mux_idx < per_pin->num_mux_nids; mux_idx++)
		अगर (per_pin->mux_nids[mux_idx] == cvt_nid)
			अवरोध;
	वापस mux_idx;
पूर्ण

अटल bool check_non_pcm_per_cvt(काष्ठा hda_codec *codec, hda_nid_t cvt_nid);

अटल व्योम hdmi_pcm_setup_pin(काष्ठा hdmi_spec *spec,
			   काष्ठा hdmi_spec_per_pin *per_pin)
अणु
	काष्ठा hda_codec *codec = per_pin->codec;
	काष्ठा hda_pcm *pcm;
	काष्ठा hda_pcm_stream *hinfo;
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक mux_idx;
	bool non_pcm;

	अगर (per_pin->pcm_idx >= 0 && per_pin->pcm_idx < spec->pcm_used)
		pcm = get_pcm_rec(spec, per_pin->pcm_idx);
	अन्यथा
		वापस;
	अगर (!pcm->pcm)
		वापस;
	अगर (!test_bit(per_pin->pcm_idx, &spec->pcm_in_use))
		वापस;

	/* hdmi audio only uses playback and one substream */
	hinfo = pcm->stream;
	substream = pcm->pcm->streams[0].substream;

	per_pin->cvt_nid = hinfo->nid;

	mux_idx = hdmi_get_pin_cvt_mux(spec, per_pin, hinfo->nid);
	अगर (mux_idx < per_pin->num_mux_nids) अणु
		snd_hda_set_dev_select(codec, per_pin->pin_nid,
				   per_pin->dev_id);
		snd_hda_codec_ग_लिखो_cache(codec, per_pin->pin_nid, 0,
				AC_VERB_SET_CONNECT_SEL,
				mux_idx);
	पूर्ण
	snd_hda_spdअगर_ctls_assign(codec, per_pin->pcm_idx, hinfo->nid);

	non_pcm = check_non_pcm_per_cvt(codec, hinfo->nid);
	अगर (substream->runसमय)
		per_pin->channels = substream->runसमय->channels;
	per_pin->setup = true;
	per_pin->mux_idx = mux_idx;

	hdmi_setup_audio_infoframe(codec, per_pin, non_pcm);
पूर्ण

अटल व्योम hdmi_pcm_reset_pin(काष्ठा hdmi_spec *spec,
			   काष्ठा hdmi_spec_per_pin *per_pin)
अणु
	अगर (per_pin->pcm_idx >= 0 && per_pin->pcm_idx < spec->pcm_used)
		snd_hda_spdअगर_ctls_unassign(per_pin->codec, per_pin->pcm_idx);

	per_pin->chmap_set = false;
	स_रखो(per_pin->chmap, 0, माप(per_pin->chmap));

	per_pin->setup = false;
	per_pin->channels = 0;
पूर्ण

अटल काष्ठा snd_jack *pin_idx_to_pcm_jack(काष्ठा hda_codec *codec,
					    काष्ठा hdmi_spec_per_pin *per_pin)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;

	अगर (per_pin->pcm_idx >= 0)
		वापस spec->pcm_rec[per_pin->pcm_idx].jack;
	अन्यथा
		वापस शून्य;
पूर्ण

/* update per_pin ELD from the given new ELD;
 * setup info frame and notअगरication accordingly
 * also notअगरy ELD kctl and report jack status changes
 */
अटल व्योम update_eld(काष्ठा hda_codec *codec,
		       काष्ठा hdmi_spec_per_pin *per_pin,
		       काष्ठा hdmi_eld *eld,
		       पूर्णांक repoll)
अणु
	काष्ठा hdmi_eld *pin_eld = &per_pin->sink_eld;
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा snd_jack *pcm_jack;
	bool old_eld_valid = pin_eld->eld_valid;
	bool eld_changed;
	पूर्णांक pcm_idx;

	अगर (eld->eld_valid) अणु
		अगर (eld->eld_size <= 0 ||
		    snd_hdmi_parse_eld(codec, &eld->info, eld->eld_buffer,
				       eld->eld_size) < 0) अणु
			eld->eld_valid = false;
			अगर (repoll) अणु
				schedule_delayed_work(&per_pin->work,
						      msecs_to_jअगरfies(300));
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!eld->eld_valid || eld->eld_size <= 0) अणु
		eld->eld_valid = false;
		eld->eld_size = 0;
	पूर्ण

	/* क्रम monitor disconnection, save pcm_idx firstly */
	pcm_idx = per_pin->pcm_idx;

	/*
	 * pcm_idx >=0 beक्रमe update_eld() means it is in monitor
	 * disconnected event. Jack must be fetched beक्रमe update_eld().
	 */
	pcm_jack = pin_idx_to_pcm_jack(codec, per_pin);

	अगर (spec->dyn_pcm_assign) अणु
		अगर (eld->eld_valid) अणु
			hdmi_attach_hda_pcm(spec, per_pin);
			hdmi_pcm_setup_pin(spec, per_pin);
		पूर्ण अन्यथा अणु
			hdmi_pcm_reset_pin(spec, per_pin);
			hdmi_detach_hda_pcm(spec, per_pin);
		पूर्ण
	पूर्ण
	/* अगर pcm_idx == -1, it means this is in monitor connection event
	 * we can get the correct pcm_idx now.
	 */
	अगर (pcm_idx == -1)
		pcm_idx = per_pin->pcm_idx;
	अगर (!pcm_jack)
		pcm_jack = pin_idx_to_pcm_jack(codec, per_pin);

	अगर (eld->eld_valid)
		snd_hdmi_show_eld(codec, &eld->info);

	eld_changed = (pin_eld->eld_valid != eld->eld_valid);
	eld_changed |= (pin_eld->monitor_present != eld->monitor_present);
	अगर (!eld_changed && eld->eld_valid && pin_eld->eld_valid)
		अगर (pin_eld->eld_size != eld->eld_size ||
		    स_भेद(pin_eld->eld_buffer, eld->eld_buffer,
			   eld->eld_size) != 0)
			eld_changed = true;

	अगर (eld_changed) अणु
		pin_eld->monitor_present = eld->monitor_present;
		pin_eld->eld_valid = eld->eld_valid;
		pin_eld->eld_size = eld->eld_size;
		अगर (eld->eld_valid)
			स_नकल(pin_eld->eld_buffer, eld->eld_buffer,
			       eld->eld_size);
		pin_eld->info = eld->info;
	पूर्ण

	/*
	 * Re-setup pin and infoframe. This is needed e.g. when
	 * - sink is first plugged-in
	 * - transcoder can change during stream playback on Haswell
	 *   and this can make HW reset converter selection on a pin.
	 */
	अगर (eld->eld_valid && !old_eld_valid && per_pin->setup) अणु
		pin_cvt_fixup(codec, per_pin, 0);
		hdmi_setup_audio_infoframe(codec, per_pin, per_pin->non_pcm);
	पूर्ण

	अगर (eld_changed && pcm_idx >= 0)
		snd_ctl_notअगरy(codec->card,
			       SNDRV_CTL_EVENT_MASK_VALUE |
			       SNDRV_CTL_EVENT_MASK_INFO,
			       &get_hdmi_pcm(spec, pcm_idx)->eld_ctl->id);

	अगर (eld_changed && pcm_jack)
		snd_jack_report(pcm_jack,
				(eld->monitor_present && eld->eld_valid) ?
				SND_JACK_AVOUT : 0);
पूर्ण

/* update ELD and jack state via HD-audio verbs */
अटल व्योम hdmi_present_sense_via_verbs(काष्ठा hdmi_spec_per_pin *per_pin,
					 पूर्णांक repoll)
अणु
	काष्ठा hda_codec *codec = per_pin->codec;
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdmi_eld *eld = &spec->temp_eld;
	hda_nid_t pin_nid = per_pin->pin_nid;
	पूर्णांक dev_id = per_pin->dev_id;
	/*
	 * Always execute a GetPinSense verb here, even when called from
	 * hdmi_पूर्णांकrinsic_event; क्रम some NVIDIA HW, the unsolicited
	 * response's PD bit is not the real PD value, but indicates that
	 * the real PD value changed. An older version of the HD-audio
	 * specअगरication worked this way. Hence, we just ignore the data in
	 * the unsolicited response to aव्योम custom WARs.
	 */
	पूर्णांक present;
	पूर्णांक ret;

	ret = snd_hda_घातer_up_pm(codec);
	अगर (ret < 0 && pm_runसमय_suspended(hda_codec_dev(codec)))
		जाओ out;

	present = snd_hda_jack_pin_sense(codec, pin_nid, dev_id);

	mutex_lock(&per_pin->lock);
	eld->monitor_present = !!(present & AC_PINSENSE_PRESENCE);
	अगर (eld->monitor_present)
		eld->eld_valid  = !!(present & AC_PINSENSE_ELDV);
	अन्यथा
		eld->eld_valid = false;

	codec_dbg(codec,
		"HDMI status: Codec=%d NID=0x%x Presence_Detect=%d ELD_Valid=%d\n",
		codec->addr, pin_nid, eld->monitor_present, eld->eld_valid);

	अगर (eld->eld_valid) अणु
		अगर (spec->ops.pin_get_eld(codec, pin_nid, dev_id,
					  eld->eld_buffer, &eld->eld_size) < 0)
			eld->eld_valid = false;
	पूर्ण

	update_eld(codec, per_pin, eld, repoll);
	mutex_unlock(&per_pin->lock);
 out:
	snd_hda_घातer_करोwn_pm(codec);
पूर्ण

#घोषणा I915_SILENT_RATE		48000
#घोषणा I915_SILENT_CHANNELS		2
#घोषणा I915_SILENT_FORMAT		SNDRV_PCM_FORMAT_S16_LE
#घोषणा I915_SILENT_FORMAT_BITS	16
#घोषणा I915_SILENT_FMT_MASK		0xf

अटल व्योम silent_stream_enable(काष्ठा hda_codec *codec,
				 काष्ठा hdmi_spec_per_pin *per_pin)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdmi_spec_per_cvt *per_cvt;
	पूर्णांक cvt_idx, pin_idx, err;
	अचिन्हित पूर्णांक क्रमmat;

	mutex_lock(&per_pin->lock);

	अगर (per_pin->setup) अणु
		codec_dbg(codec, "hdmi: PCM already open, no silent stream\n");
		जाओ unlock_out;
	पूर्ण

	pin_idx = pin_id_to_pin_index(codec, per_pin->pin_nid, per_pin->dev_id);
	err = hdmi_choose_cvt(codec, pin_idx, &cvt_idx);
	अगर (err) अणु
		codec_err(codec, "hdmi: no free converter to enable silent mode\n");
		जाओ unlock_out;
	पूर्ण

	per_cvt = get_cvt(spec, cvt_idx);
	per_cvt->asचिन्हित = 1;
	per_pin->cvt_nid = per_cvt->cvt_nid;
	per_pin->silent_stream = true;

	codec_dbg(codec, "hdmi: enabling silent stream pin-NID=0x%x cvt-NID=0x%x\n",
		  per_pin->pin_nid, per_cvt->cvt_nid);

	snd_hda_set_dev_select(codec, per_pin->pin_nid, per_pin->dev_id);
	snd_hda_codec_ग_लिखो_cache(codec, per_pin->pin_nid, 0,
				  AC_VERB_SET_CONNECT_SEL,
				  per_pin->mux_idx);

	/* configure unused pins to choose other converters */
	pin_cvt_fixup(codec, per_pin, 0);

	snd_hdac_sync_audio_rate(&codec->core, per_pin->pin_nid,
				 per_pin->dev_id, I915_SILENT_RATE);

	/* trigger silent stream generation in hw */
	क्रमmat = snd_hdac_calc_stream_क्रमmat(I915_SILENT_RATE, I915_SILENT_CHANNELS,
					     I915_SILENT_FORMAT, I915_SILENT_FORMAT_BITS, 0);
	snd_hda_codec_setup_stream(codec, per_pin->cvt_nid,
				   I915_SILENT_FMT_MASK, I915_SILENT_FMT_MASK, क्रमmat);
	usleep_range(100, 200);
	snd_hda_codec_setup_stream(codec, per_pin->cvt_nid, I915_SILENT_FMT_MASK, 0, क्रमmat);

	per_pin->channels = I915_SILENT_CHANNELS;
	hdmi_setup_audio_infoframe(codec, per_pin, per_pin->non_pcm);

 unlock_out:
	mutex_unlock(&per_pin->lock);
पूर्ण

अटल व्योम silent_stream_disable(काष्ठा hda_codec *codec,
				  काष्ठा hdmi_spec_per_pin *per_pin)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdmi_spec_per_cvt *per_cvt;
	पूर्णांक cvt_idx;

	mutex_lock(&per_pin->lock);
	अगर (!per_pin->silent_stream)
		जाओ unlock_out;

	codec_dbg(codec, "HDMI: disable silent stream on pin-NID=0x%x cvt-NID=0x%x\n",
		  per_pin->pin_nid, per_pin->cvt_nid);

	cvt_idx = cvt_nid_to_cvt_index(codec, per_pin->cvt_nid);
	अगर (cvt_idx >= 0 && cvt_idx < spec->num_cvts) अणु
		per_cvt = get_cvt(spec, cvt_idx);
		per_cvt->asचिन्हित = 0;
	पूर्ण

	per_pin->cvt_nid = 0;
	per_pin->silent_stream = false;

 unlock_out:
	mutex_unlock(&per_pin->lock);
पूर्ण

/* update ELD and jack state via audio component */
अटल व्योम sync_eld_via_acomp(काष्ठा hda_codec *codec,
			       काष्ठा hdmi_spec_per_pin *per_pin)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdmi_eld *eld = &spec->temp_eld;
	bool monitor_prev, monitor_next;

	mutex_lock(&per_pin->lock);
	eld->monitor_present = false;
	monitor_prev = per_pin->sink_eld.monitor_present;
	eld->eld_size = snd_hdac_acomp_get_eld(&codec->core, per_pin->pin_nid,
				      per_pin->dev_id, &eld->monitor_present,
				      eld->eld_buffer, ELD_MAX_SIZE);
	eld->eld_valid = (eld->eld_size > 0);
	update_eld(codec, per_pin, eld, 0);
	monitor_next = per_pin->sink_eld.monitor_present;
	mutex_unlock(&per_pin->lock);

	/*
	 * Power-up will call hdmi_present_sense, so the PM calls
	 * have to be करोne without mutex held.
	 */

	अगर (spec->send_silent_stream) अणु
		पूर्णांक pm_ret;

		अगर (!monitor_prev && monitor_next) अणु
			pm_ret = snd_hda_घातer_up_pm(codec);
			अगर (pm_ret < 0)
				codec_err(codec,
				"Monitor plugged-in, Failed to power up codec ret=[%d]\n",
				pm_ret);
			silent_stream_enable(codec, per_pin);
		पूर्ण अन्यथा अगर (monitor_prev && !monitor_next) अणु
			silent_stream_disable(codec, per_pin);
			pm_ret = snd_hda_घातer_करोwn_pm(codec);
			अगर (pm_ret < 0)
				codec_err(codec,
				"Monitor plugged-out, Failed to power down codec ret=[%d]\n",
				pm_ret);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hdmi_present_sense(काष्ठा hdmi_spec_per_pin *per_pin, पूर्णांक repoll)
अणु
	काष्ठा hda_codec *codec = per_pin->codec;

	अगर (!codec_has_acomp(codec))
		hdmi_present_sense_via_verbs(per_pin, repoll);
	अन्यथा
		sync_eld_via_acomp(codec, per_pin);
पूर्ण

अटल व्योम hdmi_repoll_eld(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hdmi_spec_per_pin *per_pin =
	container_of(to_delayed_work(work), काष्ठा hdmi_spec_per_pin, work);
	काष्ठा hda_codec *codec = per_pin->codec;
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hda_jack_tbl *jack;

	jack = snd_hda_jack_tbl_get_mst(codec, per_pin->pin_nid,
					per_pin->dev_id);
	अगर (jack)
		jack->jack_dirty = 1;

	अगर (per_pin->repoll_count++ > 6)
		per_pin->repoll_count = 0;

	mutex_lock(&spec->pcm_lock);
	hdmi_present_sense(per_pin, per_pin->repoll_count);
	mutex_unlock(&spec->pcm_lock);
पूर्ण

अटल पूर्णांक hdmi_add_pin(काष्ठा hda_codec *codec, hda_nid_t pin_nid)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	अचिन्हित पूर्णांक caps, config;
	पूर्णांक pin_idx;
	काष्ठा hdmi_spec_per_pin *per_pin;
	पूर्णांक err;
	पूर्णांक dev_num, i;

	caps = snd_hda_query_pin_caps(codec, pin_nid);
	अगर (!(caps & (AC_PINCAP_HDMI | AC_PINCAP_DP)))
		वापस 0;

	/*
	 * For DP MST audio, Configuration Default is the same क्रम
	 * all device entries on the same pin
	 */
	config = snd_hda_codec_get_pincfg(codec, pin_nid);
	अगर (get_defcfg_connect(config) == AC_JACK_PORT_NONE &&
	    !spec->क्रमce_connect)
		वापस 0;

	/*
	 * To simplअगरy the implementation, दो_स्मृति all
	 * the भव pins in the initialization अटलally
	 */
	अगर (spec->पूर्णांकel_hsw_fixup) अणु
		/*
		 * On Intel platक्रमms, device entries count वापसed
		 * by AC_PAR_DEVLIST_LEN is dynamic, and depends on
		 * the type of receiver that is connected. Allocate pin
		 * काष्ठाures based on worst हाल.
		 */
		dev_num = spec->dev_num;
	पूर्ण अन्यथा अगर (spec->dyn_pcm_assign && codec->dp_mst) अणु
		dev_num = snd_hda_get_num_devices(codec, pin_nid) + 1;
		/*
		 * spec->dev_num is the maxinum number of device entries
		 * among all the pins
		 */
		spec->dev_num = (spec->dev_num > dev_num) ?
			spec->dev_num : dev_num;
	पूर्ण अन्यथा अणु
		/*
		 * If the platक्रमm करोesn't support DP MST,
		 * manually set dev_num to 1. This means
		 * the pin has only one device entry.
		 */
		dev_num = 1;
		spec->dev_num = 1;
	पूर्ण

	क्रम (i = 0; i < dev_num; i++) अणु
		pin_idx = spec->num_pins;
		per_pin = snd_array_new(&spec->pins);

		अगर (!per_pin)
			वापस -ENOMEM;

		अगर (spec->dyn_pcm_assign) अणु
			per_pin->pcm = शून्य;
			per_pin->pcm_idx = -1;
		पूर्ण अन्यथा अणु
			per_pin->pcm = get_hdmi_pcm(spec, pin_idx);
			per_pin->pcm_idx = pin_idx;
		पूर्ण
		per_pin->pin_nid = pin_nid;
		per_pin->pin_nid_idx = spec->num_nids;
		per_pin->dev_id = i;
		per_pin->non_pcm = false;
		snd_hda_set_dev_select(codec, pin_nid, i);
		err = hdmi_पढ़ो_pin_conn(codec, pin_idx);
		अगर (err < 0)
			वापस err;
		spec->num_pins++;
	पूर्ण
	spec->num_nids++;

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_add_cvt(काष्ठा hda_codec *codec, hda_nid_t cvt_nid)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdmi_spec_per_cvt *per_cvt;
	अचिन्हित पूर्णांक chans;
	पूर्णांक err;

	chans = get_wcaps(codec, cvt_nid);
	chans = get_wcaps_channels(chans);

	per_cvt = snd_array_new(&spec->cvts);
	अगर (!per_cvt)
		वापस -ENOMEM;

	per_cvt->cvt_nid = cvt_nid;
	per_cvt->channels_min = 2;
	अगर (chans <= 16) अणु
		per_cvt->channels_max = chans;
		अगर (chans > spec->chmap.channels_max)
			spec->chmap.channels_max = chans;
	पूर्ण

	err = snd_hda_query_supported_pcm(codec, cvt_nid,
					  &per_cvt->rates,
					  &per_cvt->क्रमmats,
					  &per_cvt->maxbps);
	अगर (err < 0)
		वापस err;

	अगर (spec->num_cvts < ARRAY_SIZE(spec->cvt_nids))
		spec->cvt_nids[spec->num_cvts] = cvt_nid;
	spec->num_cvts++;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pci_quirk क्रमce_connect_list[] = अणु
	SND_PCI_QUIRK(0x103c, 0x870f, "HP", 1),
	SND_PCI_QUIRK(0x103c, 0x871a, "HP", 1),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक hdmi_parse_codec(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	hda_nid_t start_nid;
	अचिन्हित पूर्णांक caps;
	पूर्णांक i, nodes;
	स्थिर काष्ठा snd_pci_quirk *q;

	nodes = snd_hda_get_sub_nodes(codec, codec->core.afg, &start_nid);
	अगर (!start_nid || nodes < 0) अणु
		codec_warn(codec, "HDMI: failed to get afg sub nodes\n");
		वापस -EINVAL;
	पूर्ण

	q = snd_pci_quirk_lookup(codec->bus->pci, क्रमce_connect_list);

	अगर (q && q->value)
		spec->क्रमce_connect = true;

	/*
	 * hdmi_add_pin() assumes total amount of converters to
	 * be known, so first discover all converters
	 */
	क्रम (i = 0; i < nodes; i++) अणु
		hda_nid_t nid = start_nid + i;

		caps = get_wcaps(codec, nid);

		अगर (!(caps & AC_WCAP_DIGITAL))
			जारी;

		अगर (get_wcaps_type(caps) == AC_WID_AUD_OUT)
			hdmi_add_cvt(codec, nid);
	पूर्ण

	/* discover audio pins */
	क्रम (i = 0; i < nodes; i++) अणु
		hda_nid_t nid = start_nid + i;

		caps = get_wcaps(codec, nid);

		अगर (!(caps & AC_WCAP_DIGITAL))
			जारी;

		अगर (get_wcaps_type(caps) == AC_WID_PIN)
			hdmi_add_pin(codec, nid);
	पूर्ण

	वापस 0;
पूर्ण

/*
 */
अटल bool check_non_pcm_per_cvt(काष्ठा hda_codec *codec, hda_nid_t cvt_nid)
अणु
	काष्ठा hda_spdअगर_out *spdअगर;
	bool non_pcm;

	mutex_lock(&codec->spdअगर_mutex);
	spdअगर = snd_hda_spdअगर_out_of_nid(codec, cvt_nid);
	/* Add sanity check to pass klockwork check.
	 * This should never happen.
	 */
	अगर (WARN_ON(spdअगर == शून्य)) अणु
		mutex_unlock(&codec->spdअगर_mutex);
		वापस true;
	पूर्ण
	non_pcm = !!(spdअगर->status & IEC958_AES0_NONAUDIO);
	mutex_unlock(&codec->spdअगर_mutex);
	वापस non_pcm;
पूर्ण

/*
 * HDMI callbacks
 */

अटल पूर्णांक generic_hdmi_playback_pcm_prepare(काष्ठा hda_pcm_stream *hinfo,
					   काष्ठा hda_codec *codec,
					   अचिन्हित पूर्णांक stream_tag,
					   अचिन्हित पूर्णांक क्रमmat,
					   काष्ठा snd_pcm_substream *substream)
अणु
	hda_nid_t cvt_nid = hinfo->nid;
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक pin_idx;
	काष्ठा hdmi_spec_per_pin *per_pin;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	bool non_pcm;
	पूर्णांक pinctl, stripe;
	पूर्णांक err = 0;

	mutex_lock(&spec->pcm_lock);
	pin_idx = hinfo_to_pin_index(codec, hinfo);
	अगर (spec->dyn_pcm_assign && pin_idx < 0) अणु
		/* when dyn_pcm_assign and pcm is not bound to a pin
		 * skip pin setup and वापस 0 to make audio playback
		 * be ongoing
		 */
		pin_cvt_fixup(codec, शून्य, cvt_nid);
		snd_hda_codec_setup_stream(codec, cvt_nid,
					stream_tag, 0, क्रमmat);
		जाओ unlock;
	पूर्ण

	अगर (snd_BUG_ON(pin_idx < 0)) अणु
		err = -EINVAL;
		जाओ unlock;
	पूर्ण
	per_pin = get_pin(spec, pin_idx);

	/* Verअगरy pin:cvt selections to aव्योम silent audio after S3.
	 * After S3, the audio driver restores pin:cvt selections
	 * but this can happen beक्रमe gfx is पढ़ोy and such selection
	 * is overlooked by HW. Thus multiple pins can share a same
	 * शेष convertor and mute control will affect each other,
	 * which can cause a resumed audio playback become silent
	 * after S3.
	 */
	pin_cvt_fixup(codec, per_pin, 0);

	/* Call sync_audio_rate to set the N/CTS/M manually अगर necessary */
	/* Toकरो: add DP1.2 MST audio support later */
	अगर (codec_has_acomp(codec))
		snd_hdac_sync_audio_rate(&codec->core, per_pin->pin_nid,
					 per_pin->dev_id, runसमय->rate);

	non_pcm = check_non_pcm_per_cvt(codec, cvt_nid);
	mutex_lock(&per_pin->lock);
	per_pin->channels = substream->runसमय->channels;
	per_pin->setup = true;

	अगर (get_wcaps(codec, cvt_nid) & AC_WCAP_STRIPE) अणु
		stripe = snd_hdac_get_stream_stripe_ctl(&codec->bus->core,
							substream);
		snd_hda_codec_ग_लिखो(codec, cvt_nid, 0,
				    AC_VERB_SET_STRIPE_CONTROL,
				    stripe);
	पूर्ण

	hdmi_setup_audio_infoframe(codec, per_pin, non_pcm);
	mutex_unlock(&per_pin->lock);
	अगर (spec->dyn_pin_out) अणु
		snd_hda_set_dev_select(codec, per_pin->pin_nid,
				       per_pin->dev_id);
		pinctl = snd_hda_codec_पढ़ो(codec, per_pin->pin_nid, 0,
					    AC_VERB_GET_PIN_WIDGET_CONTROL, 0);
		snd_hda_codec_ग_लिखो(codec, per_pin->pin_nid, 0,
				    AC_VERB_SET_PIN_WIDGET_CONTROL,
				    pinctl | PIN_OUT);
	पूर्ण

	/* snd_hda_set_dev_select() has been called beक्रमe */
	err = spec->ops.setup_stream(codec, cvt_nid, per_pin->pin_nid,
				     per_pin->dev_id, stream_tag, क्रमmat);
 unlock:
	mutex_unlock(&spec->pcm_lock);
	वापस err;
पूर्ण

अटल पूर्णांक generic_hdmi_playback_pcm_cleanup(काष्ठा hda_pcm_stream *hinfo,
					     काष्ठा hda_codec *codec,
					     काष्ठा snd_pcm_substream *substream)
अणु
	snd_hda_codec_cleanup_stream(codec, hinfo->nid);
	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_pcm_बंद(काष्ठा hda_pcm_stream *hinfo,
			  काष्ठा hda_codec *codec,
			  काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक cvt_idx, pin_idx, pcm_idx;
	काष्ठा hdmi_spec_per_cvt *per_cvt;
	काष्ठा hdmi_spec_per_pin *per_pin;
	पूर्णांक pinctl;
	पूर्णांक err = 0;

	mutex_lock(&spec->pcm_lock);
	अगर (hinfo->nid) अणु
		pcm_idx = hinfo_to_pcm_index(codec, hinfo);
		अगर (snd_BUG_ON(pcm_idx < 0)) अणु
			err = -EINVAL;
			जाओ unlock;
		पूर्ण
		cvt_idx = cvt_nid_to_cvt_index(codec, hinfo->nid);
		अगर (snd_BUG_ON(cvt_idx < 0)) अणु
			err = -EINVAL;
			जाओ unlock;
		पूर्ण
		per_cvt = get_cvt(spec, cvt_idx);
		per_cvt->asचिन्हित = 0;
		hinfo->nid = 0;

		azx_stream(get_azx_dev(substream))->stripe = 0;

		snd_hda_spdअगर_ctls_unassign(codec, pcm_idx);
		clear_bit(pcm_idx, &spec->pcm_in_use);
		pin_idx = hinfo_to_pin_index(codec, hinfo);
		अगर (spec->dyn_pcm_assign && pin_idx < 0)
			जाओ unlock;

		अगर (snd_BUG_ON(pin_idx < 0)) अणु
			err = -EINVAL;
			जाओ unlock;
		पूर्ण
		per_pin = get_pin(spec, pin_idx);

		अगर (spec->dyn_pin_out) अणु
			snd_hda_set_dev_select(codec, per_pin->pin_nid,
					       per_pin->dev_id);
			pinctl = snd_hda_codec_पढ़ो(codec, per_pin->pin_nid, 0,
					AC_VERB_GET_PIN_WIDGET_CONTROL, 0);
			snd_hda_codec_ग_लिखो(codec, per_pin->pin_nid, 0,
					    AC_VERB_SET_PIN_WIDGET_CONTROL,
					    pinctl & ~PIN_OUT);
		पूर्ण

		mutex_lock(&per_pin->lock);
		per_pin->chmap_set = false;
		स_रखो(per_pin->chmap, 0, माप(per_pin->chmap));

		per_pin->setup = false;
		per_pin->channels = 0;
		mutex_unlock(&per_pin->lock);
	पूर्ण

unlock:
	mutex_unlock(&spec->pcm_lock);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा hda_pcm_ops generic_ops = अणु
	.खोलो = hdmi_pcm_खोलो,
	.बंद = hdmi_pcm_बंद,
	.prepare = generic_hdmi_playback_pcm_prepare,
	.cleanup = generic_hdmi_playback_pcm_cleanup,
पूर्ण;

अटल पूर्णांक hdmi_get_spk_alloc(काष्ठा hdac_device *hdac, पूर्णांक pcm_idx)
अणु
	काष्ठा hda_codec *codec = hdac_to_hda_codec(hdac);
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdmi_spec_per_pin *per_pin = pcm_idx_to_pin(spec, pcm_idx);

	अगर (!per_pin)
		वापस 0;

	वापस per_pin->sink_eld.info.spk_alloc;
पूर्ण

अटल व्योम hdmi_get_chmap(काष्ठा hdac_device *hdac, पूर्णांक pcm_idx,
					अचिन्हित अक्षर *chmap)
अणु
	काष्ठा hda_codec *codec = hdac_to_hda_codec(hdac);
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdmi_spec_per_pin *per_pin = pcm_idx_to_pin(spec, pcm_idx);

	/* chmap is alपढ़ोy set to 0 in caller */
	अगर (!per_pin)
		वापस;

	स_नकल(chmap, per_pin->chmap, ARRAY_SIZE(per_pin->chmap));
पूर्ण

अटल व्योम hdmi_set_chmap(काष्ठा hdac_device *hdac, पूर्णांक pcm_idx,
				अचिन्हित अक्षर *chmap, पूर्णांक prepared)
अणु
	काष्ठा hda_codec *codec = hdac_to_hda_codec(hdac);
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdmi_spec_per_pin *per_pin = pcm_idx_to_pin(spec, pcm_idx);

	अगर (!per_pin)
		वापस;
	mutex_lock(&per_pin->lock);
	per_pin->chmap_set = true;
	स_नकल(per_pin->chmap, chmap, ARRAY_SIZE(per_pin->chmap));
	अगर (prepared)
		hdmi_setup_audio_infoframe(codec, per_pin, per_pin->non_pcm);
	mutex_unlock(&per_pin->lock);
पूर्ण

अटल bool is_hdmi_pcm_attached(काष्ठा hdac_device *hdac, पूर्णांक pcm_idx)
अणु
	काष्ठा hda_codec *codec = hdac_to_hda_codec(hdac);
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdmi_spec_per_pin *per_pin = pcm_idx_to_pin(spec, pcm_idx);

	वापस per_pin ? true:false;
पूर्ण

अटल पूर्णांक generic_hdmi_build_pcms(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक idx, pcm_num;

	/*
	 * क्रम non-mst mode, pcm number is the same as beक्रमe
	 * क्रम DP MST mode without extra PCM, pcm number is same
	 * क्रम DP MST mode with extra PCMs, pcm number is
	 *  (nid number + dev_num - 1)
	 * dev_num is the device entry number in a pin
	 */

	अगर (codec->mst_no_extra_pcms)
		pcm_num = spec->num_nids;
	अन्यथा
		pcm_num = spec->num_nids + spec->dev_num - 1;

	codec_dbg(codec, "hdmi: pcm_num set to %d\n", pcm_num);

	क्रम (idx = 0; idx < pcm_num; idx++) अणु
		काष्ठा hda_pcm *info;
		काष्ठा hda_pcm_stream *pstr;

		info = snd_hda_codec_pcm_new(codec, "HDMI %d", idx);
		अगर (!info)
			वापस -ENOMEM;

		spec->pcm_rec[idx].pcm = info;
		spec->pcm_used++;
		info->pcm_type = HDA_PCM_TYPE_HDMI;
		info->own_chmap = true;

		pstr = &info->stream[SNDRV_PCM_STREAM_PLAYBACK];
		pstr->substreams = 1;
		pstr->ops = generic_ops;
		/* pcm number is less than 16 */
		अगर (spec->pcm_used >= 16)
			अवरोध;
		/* other pstr fields are set in खोलो */
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम मुक्त_hdmi_jack_priv(काष्ठा snd_jack *jack)
अणु
	काष्ठा hdmi_pcm *pcm = jack->निजी_data;

	pcm->jack = शून्य;
पूर्ण

अटल पूर्णांक generic_hdmi_build_jack(काष्ठा hda_codec *codec, पूर्णांक pcm_idx)
अणु
	अक्षर hdmi_str[32] = "HDMI/DP";
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdmi_spec_per_pin *per_pin = get_pin(spec, pcm_idx);
	काष्ठा snd_jack *jack;
	पूर्णांक pcmdev = get_pcm_rec(spec, pcm_idx)->device;
	पूर्णांक err;

	अगर (pcmdev > 0)
		प्र_लिखो(hdmi_str + म_माप(hdmi_str), ",pcm=%d", pcmdev);
	अगर (!spec->dyn_pcm_assign &&
	    !is_jack_detectable(codec, per_pin->pin_nid))
		म_जोड़न(hdmi_str, " Phantom",
			माप(hdmi_str) - म_माप(hdmi_str) - 1);

	err = snd_jack_new(codec->card, hdmi_str, SND_JACK_AVOUT, &jack,
			   true, false);
	अगर (err < 0)
		वापस err;

	spec->pcm_rec[pcm_idx].jack = jack;
	jack->निजी_data = &spec->pcm_rec[pcm_idx];
	jack->निजी_मुक्त = मुक्त_hdmi_jack_priv;
	वापस 0;
पूर्ण

अटल पूर्णांक generic_hdmi_build_controls(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक dev, err;
	पूर्णांक pin_idx, pcm_idx;

	क्रम (pcm_idx = 0; pcm_idx < spec->pcm_used; pcm_idx++) अणु
		अगर (!get_pcm_rec(spec, pcm_idx)->pcm) अणु
			/* no PCM: mark this क्रम skipping permanently */
			set_bit(pcm_idx, &spec->pcm_biपंचांगap);
			जारी;
		पूर्ण

		err = generic_hdmi_build_jack(codec, pcm_idx);
		अगर (err < 0)
			वापस err;

		/* create the spdअगर क्रम each pcm
		 * pin will be bound when monitor is connected
		 */
		अगर (spec->dyn_pcm_assign)
			err = snd_hda_create_dig_out_ctls(codec,
					  0, spec->cvt_nids[0],
					  HDA_PCM_TYPE_HDMI);
		अन्यथा अणु
			काष्ठा hdmi_spec_per_pin *per_pin =
				get_pin(spec, pcm_idx);
			err = snd_hda_create_dig_out_ctls(codec,
						  per_pin->pin_nid,
						  per_pin->mux_nids[0],
						  HDA_PCM_TYPE_HDMI);
		पूर्ण
		अगर (err < 0)
			वापस err;
		snd_hda_spdअगर_ctls_unassign(codec, pcm_idx);

		dev = get_pcm_rec(spec, pcm_idx)->device;
		अगर (dev != SNDRV_PCM_INVALID_DEVICE) अणु
			/* add control क्रम ELD Bytes */
			err = hdmi_create_eld_ctl(codec, pcm_idx, dev);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	क्रम (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) अणु
		काष्ठा hdmi_spec_per_pin *per_pin = get_pin(spec, pin_idx);
		काष्ठा hdmi_eld *pin_eld = &per_pin->sink_eld;

		pin_eld->eld_valid = false;
		hdmi_present_sense(per_pin, 0);
	पूर्ण

	/* add channel maps */
	क्रम (pcm_idx = 0; pcm_idx < spec->pcm_used; pcm_idx++) अणु
		काष्ठा hda_pcm *pcm;

		pcm = get_pcm_rec(spec, pcm_idx);
		अगर (!pcm || !pcm->pcm)
			अवरोध;
		err = snd_hdac_add_chmap_ctls(pcm->pcm, pcm_idx, &spec->chmap);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक generic_hdmi_init_per_pins(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक pin_idx;

	क्रम (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) अणु
		काष्ठा hdmi_spec_per_pin *per_pin = get_pin(spec, pin_idx);

		per_pin->codec = codec;
		mutex_init(&per_pin->lock);
		INIT_DELAYED_WORK(&per_pin->work, hdmi_repoll_eld);
		eld_proc_new(per_pin, pin_idx);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक generic_hdmi_init(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक pin_idx;

	mutex_lock(&spec->bind_lock);
	क्रम (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) अणु
		काष्ठा hdmi_spec_per_pin *per_pin = get_pin(spec, pin_idx);
		hda_nid_t pin_nid = per_pin->pin_nid;
		पूर्णांक dev_id = per_pin->dev_id;

		snd_hda_set_dev_select(codec, pin_nid, dev_id);
		hdmi_init_pin(codec, pin_nid);
		अगर (codec_has_acomp(codec))
			जारी;
		snd_hda_jack_detect_enable_callback_mst(codec, pin_nid, dev_id,
							jack_callback);
	पूर्ण
	mutex_unlock(&spec->bind_lock);
	वापस 0;
पूर्ण

अटल व्योम hdmi_array_init(काष्ठा hdmi_spec *spec, पूर्णांक nums)
अणु
	snd_array_init(&spec->pins, माप(काष्ठा hdmi_spec_per_pin), nums);
	snd_array_init(&spec->cvts, माप(काष्ठा hdmi_spec_per_cvt), nums);
पूर्ण

अटल व्योम hdmi_array_मुक्त(काष्ठा hdmi_spec *spec)
अणु
	snd_array_मुक्त(&spec->pins);
	snd_array_मुक्त(&spec->cvts);
पूर्ण

अटल व्योम generic_spec_मुक्त(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;

	अगर (spec) अणु
		hdmi_array_मुक्त(spec);
		kमुक्त(spec);
		codec->spec = शून्य;
	पूर्ण
	codec->dp_mst = false;
पूर्ण

अटल व्योम generic_hdmi_मुक्त(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक pin_idx, pcm_idx;

	अगर (spec->acomp_रेजिस्टरed) अणु
		snd_hdac_acomp_निकास(&codec->bus->core);
	पूर्ण अन्यथा अगर (codec_has_acomp(codec)) अणु
		snd_hdac_acomp_रेजिस्टर_notअगरier(&codec->bus->core, शून्य);
	पूर्ण
	codec->relaxed_resume = 0;

	क्रम (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) अणु
		काष्ठा hdmi_spec_per_pin *per_pin = get_pin(spec, pin_idx);
		cancel_delayed_work_sync(&per_pin->work);
		eld_proc_मुक्त(per_pin);
	पूर्ण

	क्रम (pcm_idx = 0; pcm_idx < spec->pcm_used; pcm_idx++) अणु
		अगर (spec->pcm_rec[pcm_idx].jack == शून्य)
			जारी;
		अगर (spec->dyn_pcm_assign)
			snd_device_मुक्त(codec->card,
					spec->pcm_rec[pcm_idx].jack);
		अन्यथा
			spec->pcm_rec[pcm_idx].jack = शून्य;
	पूर्ण

	generic_spec_मुक्त(codec);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक generic_hdmi_suspend(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक pin_idx;

	क्रम (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) अणु
		काष्ठा hdmi_spec_per_pin *per_pin = get_pin(spec, pin_idx);
		cancel_delayed_work_sync(&per_pin->work);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक generic_hdmi_resume(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक pin_idx;

	codec->patch_ops.init(codec);
	snd_hda_regmap_sync(codec);

	क्रम (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) अणु
		काष्ठा hdmi_spec_per_pin *per_pin = get_pin(spec, pin_idx);
		hdmi_present_sense(per_pin, 1);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा hda_codec_ops generic_hdmi_patch_ops = अणु
	.init			= generic_hdmi_init,
	.मुक्त			= generic_hdmi_मुक्त,
	.build_pcms		= generic_hdmi_build_pcms,
	.build_controls		= generic_hdmi_build_controls,
	.unsol_event		= hdmi_unsol_event,
#अगर_घोषित CONFIG_PM
	.suspend		= generic_hdmi_suspend,
	.resume			= generic_hdmi_resume,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा hdmi_ops generic_standard_hdmi_ops = अणु
	.pin_get_eld				= hdmi_pin_get_eld,
	.pin_setup_infoframe			= hdmi_pin_setup_infoframe,
	.pin_hbr_setup				= hdmi_pin_hbr_setup,
	.setup_stream				= hdmi_setup_stream,
पूर्ण;

/* allocate codec->spec and assign/initialize generic parser ops */
अटल पूर्णांक alloc_generic_hdmi(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;

	spec->codec = codec;
	spec->ops = generic_standard_hdmi_ops;
	spec->dev_num = 1;	/* initialize to 1 */
	mutex_init(&spec->pcm_lock);
	mutex_init(&spec->bind_lock);
	snd_hdac_रेजिस्टर_chmap_ops(&codec->core, &spec->chmap);

	spec->chmap.ops.get_chmap = hdmi_get_chmap;
	spec->chmap.ops.set_chmap = hdmi_set_chmap;
	spec->chmap.ops.is_pcm_attached = is_hdmi_pcm_attached;
	spec->chmap.ops.get_spk_alloc = hdmi_get_spk_alloc;

	codec->spec = spec;
	hdmi_array_init(spec, 4);

	codec->patch_ops = generic_hdmi_patch_ops;

	वापस 0;
पूर्ण

/* generic HDMI parser */
अटल पूर्णांक patch_generic_hdmi(काष्ठा hda_codec *codec)
अणु
	पूर्णांक err;

	err = alloc_generic_hdmi(codec);
	अगर (err < 0)
		वापस err;

	err = hdmi_parse_codec(codec);
	अगर (err < 0) अणु
		generic_spec_मुक्त(codec);
		वापस err;
	पूर्ण

	generic_hdmi_init_per_pins(codec);
	वापस 0;
पूर्ण

/*
 * generic audio component binding
 */

/* turn on / off the unsol event jack detection dynamically */
अटल व्योम reprogram_jack_detect(काष्ठा hda_codec *codec, hda_nid_t nid,
				  पूर्णांक dev_id, bool use_acomp)
अणु
	काष्ठा hda_jack_tbl *tbl;

	tbl = snd_hda_jack_tbl_get_mst(codec, nid, dev_id);
	अगर (tbl) अणु
		/* clear unsol even अगर component notअगरier is used, or re-enable
		 * अगर notअगरier is cleared
		 */
		अचिन्हित पूर्णांक val = use_acomp ? 0 : (AC_USRSP_EN | tbl->tag);
		snd_hda_codec_ग_लिखो_cache(codec, nid, 0,
					  AC_VERB_SET_UNSOLICITED_ENABLE, val);
	पूर्ण
पूर्ण

/* set up / clear component notअगरier dynamically */
अटल व्योम generic_acomp_notअगरier_set(काष्ठा drm_audio_component *acomp,
				       bool use_acomp)
अणु
	काष्ठा hdmi_spec *spec;
	पूर्णांक i;

	spec = container_of(acomp->audio_ops, काष्ठा hdmi_spec, drm_audio_ops);
	mutex_lock(&spec->bind_lock);
	spec->use_acomp_notअगरier = use_acomp;
	spec->codec->relaxed_resume = use_acomp;
	spec->codec->bus->keep_घातer = 0;
	/* reprogram each jack detection logic depending on the notअगरier */
	क्रम (i = 0; i < spec->num_pins; i++)
		reprogram_jack_detect(spec->codec,
				      get_pin(spec, i)->pin_nid,
				      get_pin(spec, i)->dev_id,
				      use_acomp);
	mutex_unlock(&spec->bind_lock);
पूर्ण

/* enable / disable the notअगरier via master bind / unbind */
अटल पूर्णांक generic_acomp_master_bind(काष्ठा device *dev,
				     काष्ठा drm_audio_component *acomp)
अणु
	generic_acomp_notअगरier_set(acomp, true);
	वापस 0;
पूर्ण

अटल व्योम generic_acomp_master_unbind(काष्ठा device *dev,
					काष्ठा drm_audio_component *acomp)
अणु
	generic_acomp_notअगरier_set(acomp, false);
पूर्ण

/* check whether both HD-audio and DRM PCI devices beदीर्घ to the same bus */
अटल पूर्णांक match_bound_vga(काष्ठा device *dev, पूर्णांक subtype, व्योम *data)
अणु
	काष्ठा hdac_bus *bus = data;
	काष्ठा pci_dev *pci, *master;

	अगर (!dev_is_pci(dev) || !dev_is_pci(bus->dev))
		वापस 0;
	master = to_pci_dev(bus->dev);
	pci = to_pci_dev(dev);
	वापस master->bus == pci->bus;
पूर्ण

/* audio component notअगरier क्रम AMD/Nvidia HDMI codecs */
अटल व्योम generic_acomp_pin_eld_notअगरy(व्योम *audio_ptr, पूर्णांक port, पूर्णांक dev_id)
अणु
	काष्ठा hda_codec *codec = audio_ptr;
	काष्ठा hdmi_spec *spec = codec->spec;
	hda_nid_t pin_nid = spec->port2pin(codec, port);

	अगर (!pin_nid)
		वापस;
	अगर (get_wcaps_type(get_wcaps(codec, pin_nid)) != AC_WID_PIN)
		वापस;
	/* skip notअगरication during प्रणाली suspend (but not in runसमय PM);
	 * the state will be updated at resume
	 */
	अगर (codec->core.dev.घातer.घातer_state.event == PM_EVENT_SUSPEND)
		वापस;
	/* ditto during suspend/resume process itself */
	अगर (snd_hdac_is_in_pm(&codec->core))
		वापस;

	check_presence_and_report(codec, pin_nid, dev_id);
पूर्ण

/* set up the निजी drm_audio_ops from the ढाँचा */
अटल व्योम setup_drm_audio_ops(काष्ठा hda_codec *codec,
				स्थिर काष्ठा drm_audio_component_audio_ops *ops)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;

	spec->drm_audio_ops.audio_ptr = codec;
	/* पूर्णांकel_audio_codec_enable() or पूर्णांकel_audio_codec_disable()
	 * will call pin_eld_notअगरy with using audio_ptr poपूर्णांकer
	 * We need make sure audio_ptr is really setup
	 */
	wmb();
	spec->drm_audio_ops.pin2port = ops->pin2port;
	spec->drm_audio_ops.pin_eld_notअगरy = ops->pin_eld_notअगरy;
	spec->drm_audio_ops.master_bind = ops->master_bind;
	spec->drm_audio_ops.master_unbind = ops->master_unbind;
पूर्ण

/* initialize the generic HDMI audio component */
अटल व्योम generic_acomp_init(काष्ठा hda_codec *codec,
			       स्थिर काष्ठा drm_audio_component_audio_ops *ops,
			       पूर्णांक (*port2pin)(काष्ठा hda_codec *, पूर्णांक))
अणु
	काष्ठा hdmi_spec *spec = codec->spec;

	अगर (!enable_acomp) अणु
		codec_info(codec, "audio component disabled by module option\n");
		वापस;
	पूर्ण

	spec->port2pin = port2pin;
	setup_drm_audio_ops(codec, ops);
	अगर (!snd_hdac_acomp_init(&codec->bus->core, &spec->drm_audio_ops,
				 match_bound_vga, 0)) अणु
		spec->acomp_रेजिस्टरed = true;
	पूर्ण
पूर्ण

/*
 * Intel codec parsers and helpers
 */

#घोषणा INTEL_GET_VENDOR_VERB	0xf81
#घोषणा INTEL_SET_VENDOR_VERB	0x781
#घोषणा INTEL_EN_DP12		0x02	/* enable DP 1.2 features */
#घोषणा INTEL_EN_ALL_PIN_CVTS	0x01	/* enable 2nd & 3rd pins and convertors */

अटल व्योम पूर्णांकel_haswell_enable_all_pins(काष्ठा hda_codec *codec,
					  bool update_tree)
अणु
	अचिन्हित पूर्णांक venकरोr_param;
	काष्ठा hdmi_spec *spec = codec->spec;

	venकरोr_param = snd_hda_codec_पढ़ो(codec, spec->venकरोr_nid, 0,
				INTEL_GET_VENDOR_VERB, 0);
	अगर (venकरोr_param == -1 || venकरोr_param & INTEL_EN_ALL_PIN_CVTS)
		वापस;

	venकरोr_param |= INTEL_EN_ALL_PIN_CVTS;
	venकरोr_param = snd_hda_codec_पढ़ो(codec, spec->venकरोr_nid, 0,
				INTEL_SET_VENDOR_VERB, venकरोr_param);
	अगर (venकरोr_param == -1)
		वापस;

	अगर (update_tree)
		snd_hda_codec_update_widमाला_लो(codec);
पूर्ण

अटल व्योम पूर्णांकel_haswell_fixup_enable_dp12(काष्ठा hda_codec *codec)
अणु
	अचिन्हित पूर्णांक venकरोr_param;
	काष्ठा hdmi_spec *spec = codec->spec;

	venकरोr_param = snd_hda_codec_पढ़ो(codec, spec->venकरोr_nid, 0,
				INTEL_GET_VENDOR_VERB, 0);
	अगर (venकरोr_param == -1 || venकरोr_param & INTEL_EN_DP12)
		वापस;

	/* enable DP1.2 mode */
	venकरोr_param |= INTEL_EN_DP12;
	snd_hdac_regmap_add_venकरोr_verb(&codec->core, INTEL_SET_VENDOR_VERB);
	snd_hda_codec_ग_लिखो_cache(codec, spec->venकरोr_nid, 0,
				INTEL_SET_VENDOR_VERB, venकरोr_param);
पूर्ण

/* Haswell needs to re-issue the venकरोr-specअगरic verbs beक्रमe turning to D0.
 * Otherwise you may get severe h/w communication errors.
 */
अटल व्योम haswell_set_घातer_state(काष्ठा hda_codec *codec, hda_nid_t fg,
				अचिन्हित पूर्णांक घातer_state)
अणु
	अगर (घातer_state == AC_PWRST_D0) अणु
		पूर्णांकel_haswell_enable_all_pins(codec, false);
		पूर्णांकel_haswell_fixup_enable_dp12(codec);
	पूर्ण

	snd_hda_codec_पढ़ो(codec, fg, 0, AC_VERB_SET_POWER_STATE, घातer_state);
	snd_hda_codec_set_घातer_to_all(codec, fg, घातer_state);
पूर्ण

/* There is a fixed mapping between audio pin node and display port.
 * on SNB, IVY, HSW, BSW, SKL, BXT, KBL:
 * Pin Widget 5 - PORT B (port = 1 in i915 driver)
 * Pin Widget 6 - PORT C (port = 2 in i915 driver)
 * Pin Widget 7 - PORT D (port = 3 in i915 driver)
 *
 * on VLV, ILK:
 * Pin Widget 4 - PORT B (port = 1 in i915 driver)
 * Pin Widget 5 - PORT C (port = 2 in i915 driver)
 * Pin Widget 6 - PORT D (port = 3 in i915 driver)
 */
अटल पूर्णांक पूर्णांकel_base_nid(काष्ठा hda_codec *codec)
अणु
	चयन (codec->core.venकरोr_id) अणु
	हाल 0x80860054: /* ILK */
	हाल 0x80862804: /* ILK */
	हाल 0x80862882: /* VLV */
		वापस 4;
	शेष:
		वापस 5;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_pin2port(व्योम *audio_ptr, पूर्णांक pin_nid)
अणु
	काष्ठा hda_codec *codec = audio_ptr;
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक base_nid, i;

	अगर (!spec->port_num) अणु
		base_nid = पूर्णांकel_base_nid(codec);
		अगर (WARN_ON(pin_nid < base_nid || pin_nid >= base_nid + 3))
			वापस -1;
		वापस pin_nid - base_nid + 1;
	पूर्ण

	/*
	 * looking क्रम the pin number in the mapping table and वापस
	 * the index which indicate the port number
	 */
	क्रम (i = 0; i < spec->port_num; i++) अणु
		अगर (pin_nid == spec->port_map[i])
			वापस i;
	पूर्ण

	codec_info(codec, "Can't find the HDMI/DP port for pin NID 0x%x\n", pin_nid);
	वापस -1;
पूर्ण

अटल पूर्णांक पूर्णांकel_port2pin(काष्ठा hda_codec *codec, पूर्णांक port)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;

	अगर (!spec->port_num) अणु
		/* we assume only from port-B to port-D */
		अगर (port < 1 || port > 3)
			वापस 0;
		वापस port + पूर्णांकel_base_nid(codec) - 1;
	पूर्ण

	अगर (port < 0 || port >= spec->port_num)
		वापस 0;
	वापस spec->port_map[port];
पूर्ण

अटल व्योम पूर्णांकel_pin_eld_notअगरy(व्योम *audio_ptr, पूर्णांक port, पूर्णांक pipe)
अणु
	काष्ठा hda_codec *codec = audio_ptr;
	पूर्णांक pin_nid;
	पूर्णांक dev_id = pipe;

	pin_nid = पूर्णांकel_port2pin(codec, port);
	अगर (!pin_nid)
		वापस;
	/* skip notअगरication during प्रणाली suspend (but not in runसमय PM);
	 * the state will be updated at resume
	 */
	अगर (codec->core.dev.घातer.घातer_state.event == PM_EVENT_SUSPEND)
		वापस;
	/* ditto during suspend/resume process itself */
	अगर (snd_hdac_is_in_pm(&codec->core))
		वापस;

	snd_hdac_i915_set_bclk(&codec->bus->core);
	check_presence_and_report(codec, pin_nid, dev_id);
पूर्ण

अटल स्थिर काष्ठा drm_audio_component_audio_ops पूर्णांकel_audio_ops = अणु
	.pin2port = पूर्णांकel_pin2port,
	.pin_eld_notअगरy = पूर्णांकel_pin_eld_notअगरy,
पूर्ण;

/* रेजिस्टर i915 component pin_eld_notअगरy callback */
अटल व्योम रेजिस्टर_i915_notअगरier(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;

	spec->use_acomp_notअगरier = true;
	spec->port2pin = पूर्णांकel_port2pin;
	setup_drm_audio_ops(codec, &पूर्णांकel_audio_ops);
	snd_hdac_acomp_रेजिस्टर_notअगरier(&codec->bus->core,
					&spec->drm_audio_ops);
	/* no need क्रम क्रमcible resume क्रम jack check thanks to notअगरier */
	codec->relaxed_resume = 1;
पूर्ण

/* setup_stream ops override क्रम HSW+ */
अटल पूर्णांक i915_hsw_setup_stream(काष्ठा hda_codec *codec, hda_nid_t cvt_nid,
				 hda_nid_t pin_nid, पूर्णांक dev_id, u32 stream_tag,
				 पूर्णांक क्रमmat)
अणु
	haswell_verअगरy_D0(codec, cvt_nid, pin_nid);
	वापस hdmi_setup_stream(codec, cvt_nid, pin_nid, dev_id,
				 stream_tag, क्रमmat);
पूर्ण

/* pin_cvt_fixup ops override क्रम HSW+ and VLV+ */
अटल व्योम i915_pin_cvt_fixup(काष्ठा hda_codec *codec,
			       काष्ठा hdmi_spec_per_pin *per_pin,
			       hda_nid_t cvt_nid)
अणु
	अगर (per_pin) अणु
		haswell_verअगरy_D0(codec, per_pin->cvt_nid, per_pin->pin_nid);
		snd_hda_set_dev_select(codec, per_pin->pin_nid,
			       per_pin->dev_id);
		पूर्णांकel_verअगरy_pin_cvt_connect(codec, per_pin);
		पूर्णांकel_not_share_asचिन्हित_cvt(codec, per_pin->pin_nid,
				     per_pin->dev_id, per_pin->mux_idx);
	पूर्ण अन्यथा अणु
		पूर्णांकel_not_share_asचिन्हित_cvt_nid(codec, 0, 0, cvt_nid);
	पूर्ण
पूर्ण

/* precondition and allocation क्रम Intel codecs */
अटल पूर्णांक alloc_पूर्णांकel_hdmi(काष्ठा hda_codec *codec)
अणु
	पूर्णांक err;

	/* requires i915 binding */
	अगर (!codec->bus->core.audio_component) अणु
		codec_info(codec, "No i915 binding for Intel HDMI/DP codec\n");
		/* set probe_id here to prevent generic fallback binding */
		codec->probe_id = HDA_CODEC_ID_SKIP_PROBE;
		वापस -ENODEV;
	पूर्ण

	err = alloc_generic_hdmi(codec);
	अगर (err < 0)
		वापस err;
	/* no need to handle unsol events */
	codec->patch_ops.unsol_event = शून्य;
	वापस 0;
पूर्ण

/* parse and post-process क्रम Intel codecs */
अटल पूर्णांक parse_पूर्णांकel_hdmi(काष्ठा hda_codec *codec)
अणु
	पूर्णांक err, retries = 3;

	करो अणु
		err = hdmi_parse_codec(codec);
	पूर्ण जबतक (err < 0 && retries--);

	अगर (err < 0) अणु
		generic_spec_मुक्त(codec);
		वापस err;
	पूर्ण

	generic_hdmi_init_per_pins(codec);
	रेजिस्टर_i915_notअगरier(codec);
	वापस 0;
पूर्ण

/* Intel Haswell and onwards; audio component with eld notअगरier */
अटल पूर्णांक पूर्णांकel_hsw_common_init(काष्ठा hda_codec *codec, hda_nid_t venकरोr_nid,
				 स्थिर पूर्णांक *port_map, पूर्णांक port_num, पूर्णांक dev_num)
अणु
	काष्ठा hdmi_spec *spec;
	पूर्णांक err;

	err = alloc_पूर्णांकel_hdmi(codec);
	अगर (err < 0)
		वापस err;
	spec = codec->spec;
	codec->dp_mst = true;
	spec->dyn_pcm_assign = true;
	spec->venकरोr_nid = venकरोr_nid;
	spec->port_map = port_map;
	spec->port_num = port_num;
	spec->पूर्णांकel_hsw_fixup = true;
	spec->dev_num = dev_num;

	पूर्णांकel_haswell_enable_all_pins(codec, true);
	पूर्णांकel_haswell_fixup_enable_dp12(codec);

	codec->display_घातer_control = 1;

	codec->patch_ops.set_घातer_state = haswell_set_घातer_state;
	codec->depop_delay = 0;
	codec->स्वतः_runसमय_pm = 1;

	spec->ops.setup_stream = i915_hsw_setup_stream;
	spec->ops.pin_cvt_fixup = i915_pin_cvt_fixup;

	/*
	 * Enable silent stream feature, अगर it is enabled via
	 * module param or Kconfig option
	 */
	अगर (enable_silent_stream)
		spec->send_silent_stream = true;

	वापस parse_पूर्णांकel_hdmi(codec);
पूर्ण

अटल पूर्णांक patch_i915_hsw_hdmi(काष्ठा hda_codec *codec)
अणु
	वापस पूर्णांकel_hsw_common_init(codec, 0x08, शून्य, 0, 3);
पूर्ण

अटल पूर्णांक patch_i915_glk_hdmi(काष्ठा hda_codec *codec)
अणु
	वापस पूर्णांकel_hsw_common_init(codec, 0x0b, शून्य, 0, 3);
पूर्ण

अटल पूर्णांक patch_i915_icl_hdmi(काष्ठा hda_codec *codec)
अणु
	/*
	 * pin to port mapping table where the value indicate the pin number and
	 * the index indicate the port number.
	 */
	अटल स्थिर पूर्णांक map[] = अणु0x0, 0x4, 0x6, 0x8, 0xa, 0xbपूर्ण;

	वापस पूर्णांकel_hsw_common_init(codec, 0x02, map, ARRAY_SIZE(map), 3);
पूर्ण

अटल पूर्णांक patch_i915_tgl_hdmi(काष्ठा hda_codec *codec)
अणु
	/*
	 * pin to port mapping table where the value indicate the pin number and
	 * the index indicate the port number.
	 */
	अटल स्थिर पूर्णांक map[] = अणु0x4, 0x6, 0x8, 0xa, 0xb, 0xc, 0xd, 0xe, 0xfपूर्ण;
	पूर्णांक ret;

	ret = पूर्णांकel_hsw_common_init(codec, 0x02, map, ARRAY_SIZE(map), 4);
	अगर (!ret) अणु
		काष्ठा hdmi_spec *spec = codec->spec;

		spec->dyn_pcm_no_legacy = true;
	पूर्ण

	वापस ret;
पूर्ण

/* Intel Baytrail and Braswell; with eld notअगरier */
अटल पूर्णांक patch_i915_byt_hdmi(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec;
	पूर्णांक err;

	err = alloc_पूर्णांकel_hdmi(codec);
	अगर (err < 0)
		वापस err;
	spec = codec->spec;

	/* For Valleyview/Cherryview, only the display codec is in the display
	 * घातer well and can use link_घातer ops to request/release the घातer.
	 */
	codec->display_घातer_control = 1;

	codec->depop_delay = 0;
	codec->स्वतः_runसमय_pm = 1;

	spec->ops.pin_cvt_fixup = i915_pin_cvt_fixup;

	वापस parse_पूर्णांकel_hdmi(codec);
पूर्ण

/* Intel IronLake, SandyBridge and IvyBridge; with eld notअगरier */
अटल पूर्णांक patch_i915_cpt_hdmi(काष्ठा hda_codec *codec)
अणु
	पूर्णांक err;

	err = alloc_पूर्णांकel_hdmi(codec);
	अगर (err < 0)
		वापस err;
	वापस parse_पूर्णांकel_hdmi(codec);
पूर्ण

/*
 * Shared non-generic implementations
 */

अटल पूर्णांक simple_playback_build_pcms(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hda_pcm *info;
	अचिन्हित पूर्णांक chans;
	काष्ठा hda_pcm_stream *pstr;
	काष्ठा hdmi_spec_per_cvt *per_cvt;

	per_cvt = get_cvt(spec, 0);
	chans = get_wcaps(codec, per_cvt->cvt_nid);
	chans = get_wcaps_channels(chans);

	info = snd_hda_codec_pcm_new(codec, "HDMI 0");
	अगर (!info)
		वापस -ENOMEM;
	spec->pcm_rec[0].pcm = info;
	info->pcm_type = HDA_PCM_TYPE_HDMI;
	pstr = &info->stream[SNDRV_PCM_STREAM_PLAYBACK];
	*pstr = spec->pcm_playback;
	pstr->nid = per_cvt->cvt_nid;
	अगर (pstr->channels_max <= 2 && chans && chans <= 16)
		pstr->channels_max = chans;

	वापस 0;
पूर्ण

/* unsolicited event क्रम jack sensing */
अटल व्योम simple_hdmi_unsol_event(काष्ठा hda_codec *codec,
				    अचिन्हित पूर्णांक res)
अणु
	snd_hda_jack_set_dirty_all(codec);
	snd_hda_jack_report_sync(codec);
पूर्ण

/* generic_hdmi_build_jack can be used क्रम simple_hdmi, too,
 * as दीर्घ as spec->pins[] is set correctly
 */
#घोषणा simple_hdmi_build_jack	generic_hdmi_build_jack

अटल पूर्णांक simple_playback_build_controls(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdmi_spec_per_cvt *per_cvt;
	पूर्णांक err;

	per_cvt = get_cvt(spec, 0);
	err = snd_hda_create_dig_out_ctls(codec, per_cvt->cvt_nid,
					  per_cvt->cvt_nid,
					  HDA_PCM_TYPE_HDMI);
	अगर (err < 0)
		वापस err;
	वापस simple_hdmi_build_jack(codec, 0);
पूर्ण

अटल पूर्णांक simple_playback_init(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hdmi_spec_per_pin *per_pin = get_pin(spec, 0);
	hda_nid_t pin = per_pin->pin_nid;

	snd_hda_codec_ग_लिखो(codec, pin, 0,
			    AC_VERB_SET_PIN_WIDGET_CONTROL, PIN_OUT);
	/* some codecs require to unmute the pin */
	अगर (get_wcaps(codec, pin) & AC_WCAP_OUT_AMP)
		snd_hda_codec_ग_लिखो(codec, pin, 0, AC_VERB_SET_AMP_GAIN_MUTE,
				    AMP_OUT_UNMUTE);
	snd_hda_jack_detect_enable(codec, pin, per_pin->dev_id);
	वापस 0;
पूर्ण

अटल व्योम simple_playback_मुक्त(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;

	hdmi_array_मुक्त(spec);
	kमुक्त(spec);
पूर्ण

/*
 * Nvidia specअगरic implementations
 */

#घोषणा Nv_VERB_SET_Channel_Allocation          0xF79
#घोषणा Nv_VERB_SET_Info_Frame_Checksum         0xF7A
#घोषणा Nv_VERB_SET_Audio_Protection_On         0xF98
#घोषणा Nv_VERB_SET_Audio_Protection_Off        0xF99

#घोषणा nvhdmi_master_con_nid_7x	0x04
#घोषणा nvhdmi_master_pin_nid_7x	0x05

अटल स्थिर hda_nid_t nvhdmi_con_nids_7x[4] = अणु
	/*front, rear, clfe, rear_surr */
	0x6, 0x8, 0xa, 0xc,
पूर्ण;

अटल स्थिर काष्ठा hda_verb nvhdmi_basic_init_7x_2ch[] = अणु
	/* set audio protect on */
	अणु 0x1, Nv_VERB_SET_Audio_Protection_On, 0x1पूर्ण,
	/* enable digital output on pin widget */
	अणु 0x5, AC_VERB_SET_PIN_WIDGET_CONTROL, PIN_OUT | 0x5 पूर्ण,
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा hda_verb nvhdmi_basic_init_7x_8ch[] = अणु
	/* set audio protect on */
	अणु 0x1, Nv_VERB_SET_Audio_Protection_On, 0x1पूर्ण,
	/* enable digital output on pin widget */
	अणु 0x5, AC_VERB_SET_PIN_WIDGET_CONTROL, PIN_OUT | 0x5 पूर्ण,
	अणु 0x7, AC_VERB_SET_PIN_WIDGET_CONTROL, PIN_OUT | 0x5 पूर्ण,
	अणु 0x9, AC_VERB_SET_PIN_WIDGET_CONTROL, PIN_OUT | 0x5 पूर्ण,
	अणु 0xb, AC_VERB_SET_PIN_WIDGET_CONTROL, PIN_OUT | 0x5 पूर्ण,
	अणु 0xd, AC_VERB_SET_PIN_WIDGET_CONTROL, PIN_OUT | 0x5 पूर्ण,
	अणुपूर्ण /* terminator */
पूर्ण;

#अगर_घोषित LIMITED_RATE_FMT_SUPPORT
/* support only the safe क्रमmat and rate */
#घोषणा SUPPORTED_RATES		SNDRV_PCM_RATE_48000
#घोषणा SUPPORTED_MAXBPS	16
#घोषणा SUPPORTED_FORMATS	SNDRV_PCM_FMTBIT_S16_LE
#अन्यथा
/* support all rates and क्रमmats */
#घोषणा SUPPORTED_RATES \
	(SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 |\
	SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_176400 |\
	 SNDRV_PCM_RATE_192000)
#घोषणा SUPPORTED_MAXBPS	24
#घोषणा SUPPORTED_FORMATS \
	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE)
#पूर्ण_अगर

अटल पूर्णांक nvhdmi_7x_init_2ch(काष्ठा hda_codec *codec)
अणु
	snd_hda_sequence_ग_लिखो(codec, nvhdmi_basic_init_7x_2ch);
	वापस 0;
पूर्ण

अटल पूर्णांक nvhdmi_7x_init_8ch(काष्ठा hda_codec *codec)
अणु
	snd_hda_sequence_ग_लिखो(codec, nvhdmi_basic_init_7x_8ch);
	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक channels_2_6_8[] = अणु
	2, 6, 8
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक channels_2_8[] = अणु
	2, 8
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_2_6_8_channels = अणु
	.count = ARRAY_SIZE(channels_2_6_8),
	.list = channels_2_6_8,
	.mask = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_2_8_channels = अणु
	.count = ARRAY_SIZE(channels_2_8),
	.list = channels_2_8,
	.mask = 0,
पूर्ण;

अटल पूर्णांक simple_playback_pcm_खोलो(काष्ठा hda_pcm_stream *hinfo,
				    काष्ठा hda_codec *codec,
				    काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *hw_स्थिरraपूर्णांकs_channels = शून्य;

	चयन (codec->preset->venकरोr_id) अणु
	हाल 0x10de0002:
	हाल 0x10de0003:
	हाल 0x10de0005:
	हाल 0x10de0006:
		hw_स्थिरraपूर्णांकs_channels = &hw_स्थिरraपूर्णांकs_2_8_channels;
		अवरोध;
	हाल 0x10de0007:
		hw_स्थिरraपूर्णांकs_channels = &hw_स्थिरraपूर्णांकs_2_6_8_channels;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (hw_स्थिरraपूर्णांकs_channels != शून्य) अणु
		snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				SNDRV_PCM_HW_PARAM_CHANNELS,
				hw_स्थिरraपूर्णांकs_channels);
	पूर्ण अन्यथा अणु
		snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
					   SNDRV_PCM_HW_PARAM_CHANNELS, 2);
	पूर्ण

	वापस snd_hda_multi_out_dig_खोलो(codec, &spec->multiout);
पूर्ण

अटल पूर्णांक simple_playback_pcm_बंद(काष्ठा hda_pcm_stream *hinfo,
				     काष्ठा hda_codec *codec,
				     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	वापस snd_hda_multi_out_dig_बंद(codec, &spec->multiout);
पूर्ण

अटल पूर्णांक simple_playback_pcm_prepare(काष्ठा hda_pcm_stream *hinfo,
				       काष्ठा hda_codec *codec,
				       अचिन्हित पूर्णांक stream_tag,
				       अचिन्हित पूर्णांक क्रमmat,
				       काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	वापस snd_hda_multi_out_dig_prepare(codec, &spec->multiout,
					     stream_tag, क्रमmat, substream);
पूर्ण

अटल स्थिर काष्ठा hda_pcm_stream simple_pcm_playback = अणु
	.substreams = 1,
	.channels_min = 2,
	.channels_max = 2,
	.ops = अणु
		.खोलो = simple_playback_pcm_खोलो,
		.बंद = simple_playback_pcm_बंद,
		.prepare = simple_playback_pcm_prepare
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hda_codec_ops simple_hdmi_patch_ops = अणु
	.build_controls = simple_playback_build_controls,
	.build_pcms = simple_playback_build_pcms,
	.init = simple_playback_init,
	.मुक्त = simple_playback_मुक्त,
	.unsol_event = simple_hdmi_unsol_event,
पूर्ण;

अटल पूर्णांक patch_simple_hdmi(काष्ठा hda_codec *codec,
			     hda_nid_t cvt_nid, hda_nid_t pin_nid)
अणु
	काष्ठा hdmi_spec *spec;
	काष्ठा hdmi_spec_per_cvt *per_cvt;
	काष्ठा hdmi_spec_per_pin *per_pin;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;

	spec->codec = codec;
	codec->spec = spec;
	hdmi_array_init(spec, 1);

	spec->multiout.num_dacs = 0;  /* no analog */
	spec->multiout.max_channels = 2;
	spec->multiout.dig_out_nid = cvt_nid;
	spec->num_cvts = 1;
	spec->num_pins = 1;
	per_pin = snd_array_new(&spec->pins);
	per_cvt = snd_array_new(&spec->cvts);
	अगर (!per_pin || !per_cvt) अणु
		simple_playback_मुक्त(codec);
		वापस -ENOMEM;
	पूर्ण
	per_cvt->cvt_nid = cvt_nid;
	per_pin->pin_nid = pin_nid;
	spec->pcm_playback = simple_pcm_playback;

	codec->patch_ops = simple_hdmi_patch_ops;

	वापस 0;
पूर्ण

अटल व्योम nvhdmi_8ch_7x_set_info_frame_parameters(काष्ठा hda_codec *codec,
						    पूर्णांक channels)
अणु
	अचिन्हित पूर्णांक chanmask;
	पूर्णांक chan = channels ? (channels - 1) : 1;

	चयन (channels) अणु
	शेष:
	हाल 0:
	हाल 2:
		chanmask = 0x00;
		अवरोध;
	हाल 4:
		chanmask = 0x08;
		अवरोध;
	हाल 6:
		chanmask = 0x0b;
		अवरोध;
	हाल 8:
		chanmask = 0x13;
		अवरोध;
	पूर्ण

	/* Set the audio infoframe channel allocation and checksum fields.  The
	 * channel count is computed implicitly by the hardware. */
	snd_hda_codec_ग_लिखो(codec, 0x1, 0,
			Nv_VERB_SET_Channel_Allocation, chanmask);

	snd_hda_codec_ग_लिखो(codec, 0x1, 0,
			Nv_VERB_SET_Info_Frame_Checksum,
			(0x71 - chan - chanmask));
पूर्ण

अटल पूर्णांक nvhdmi_8ch_7x_pcm_बंद(काष्ठा hda_pcm_stream *hinfo,
				   काष्ठा hda_codec *codec,
				   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक i;

	snd_hda_codec_ग_लिखो(codec, nvhdmi_master_con_nid_7x,
			0, AC_VERB_SET_CHANNEL_STREAMID, 0);
	क्रम (i = 0; i < 4; i++) अणु
		/* set the stream id */
		snd_hda_codec_ग_लिखो(codec, nvhdmi_con_nids_7x[i], 0,
				AC_VERB_SET_CHANNEL_STREAMID, 0);
		/* set the stream क्रमmat */
		snd_hda_codec_ग_लिखो(codec, nvhdmi_con_nids_7x[i], 0,
				AC_VERB_SET_STREAM_FORMAT, 0);
	पूर्ण

	/* The audio hardware sends a channel count of 0x7 (8ch) when all the
	 * streams are disabled. */
	nvhdmi_8ch_7x_set_info_frame_parameters(codec, 8);

	वापस snd_hda_multi_out_dig_बंद(codec, &spec->multiout);
पूर्ण

अटल पूर्णांक nvhdmi_8ch_7x_pcm_prepare(काष्ठा hda_pcm_stream *hinfo,
				     काष्ठा hda_codec *codec,
				     अचिन्हित पूर्णांक stream_tag,
				     अचिन्हित पूर्णांक क्रमmat,
				     काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक chs;
	अचिन्हित पूर्णांक dataDCC2, channel_id;
	पूर्णांक i;
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hda_spdअगर_out *spdअगर;
	काष्ठा hdmi_spec_per_cvt *per_cvt;

	mutex_lock(&codec->spdअगर_mutex);
	per_cvt = get_cvt(spec, 0);
	spdअगर = snd_hda_spdअगर_out_of_nid(codec, per_cvt->cvt_nid);

	chs = substream->runसमय->channels;

	dataDCC2 = 0x2;

	/* turn off SPDIF once; otherwise the IEC958 bits won't be updated */
	अगर (codec->spdअगर_status_reset && (spdअगर->ctls & AC_DIG1_ENABLE))
		snd_hda_codec_ग_लिखो(codec,
				nvhdmi_master_con_nid_7x,
				0,
				AC_VERB_SET_DIGI_CONVERT_1,
				spdअगर->ctls & ~AC_DIG1_ENABLE & 0xff);

	/* set the stream id */
	snd_hda_codec_ग_लिखो(codec, nvhdmi_master_con_nid_7x, 0,
			AC_VERB_SET_CHANNEL_STREAMID, (stream_tag << 4) | 0x0);

	/* set the stream क्रमmat */
	snd_hda_codec_ग_लिखो(codec, nvhdmi_master_con_nid_7x, 0,
			AC_VERB_SET_STREAM_FORMAT, क्रमmat);

	/* turn on again (अगर needed) */
	/* enable and set the channel status audio/data flag */
	अगर (codec->spdअगर_status_reset && (spdअगर->ctls & AC_DIG1_ENABLE)) अणु
		snd_hda_codec_ग_लिखो(codec,
				nvhdmi_master_con_nid_7x,
				0,
				AC_VERB_SET_DIGI_CONVERT_1,
				spdअगर->ctls & 0xff);
		snd_hda_codec_ग_लिखो(codec,
				nvhdmi_master_con_nid_7x,
				0,
				AC_VERB_SET_DIGI_CONVERT_2, dataDCC2);
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		अगर (chs == 2)
			channel_id = 0;
		अन्यथा
			channel_id = i * 2;

		/* turn off SPDIF once;
		 *otherwise the IEC958 bits won't be updated
		 */
		अगर (codec->spdअगर_status_reset &&
		(spdअगर->ctls & AC_DIG1_ENABLE))
			snd_hda_codec_ग_लिखो(codec,
				nvhdmi_con_nids_7x[i],
				0,
				AC_VERB_SET_DIGI_CONVERT_1,
				spdअगर->ctls & ~AC_DIG1_ENABLE & 0xff);
		/* set the stream id */
		snd_hda_codec_ग_लिखो(codec,
				nvhdmi_con_nids_7x[i],
				0,
				AC_VERB_SET_CHANNEL_STREAMID,
				(stream_tag << 4) | channel_id);
		/* set the stream क्रमmat */
		snd_hda_codec_ग_लिखो(codec,
				nvhdmi_con_nids_7x[i],
				0,
				AC_VERB_SET_STREAM_FORMAT,
				क्रमmat);
		/* turn on again (अगर needed) */
		/* enable and set the channel status audio/data flag */
		अगर (codec->spdअगर_status_reset &&
		(spdअगर->ctls & AC_DIG1_ENABLE)) अणु
			snd_hda_codec_ग_लिखो(codec,
					nvhdmi_con_nids_7x[i],
					0,
					AC_VERB_SET_DIGI_CONVERT_1,
					spdअगर->ctls & 0xff);
			snd_hda_codec_ग_लिखो(codec,
					nvhdmi_con_nids_7x[i],
					0,
					AC_VERB_SET_DIGI_CONVERT_2, dataDCC2);
		पूर्ण
	पूर्ण

	nvhdmi_8ch_7x_set_info_frame_parameters(codec, chs);

	mutex_unlock(&codec->spdअगर_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hda_pcm_stream nvhdmi_pcm_playback_8ch_7x = अणु
	.substreams = 1,
	.channels_min = 2,
	.channels_max = 8,
	.nid = nvhdmi_master_con_nid_7x,
	.rates = SUPPORTED_RATES,
	.maxbps = SUPPORTED_MAXBPS,
	.क्रमmats = SUPPORTED_FORMATS,
	.ops = अणु
		.खोलो = simple_playback_pcm_खोलो,
		.बंद = nvhdmi_8ch_7x_pcm_बंद,
		.prepare = nvhdmi_8ch_7x_pcm_prepare
	पूर्ण,
पूर्ण;

अटल पूर्णांक patch_nvhdmi_2ch(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec;
	पूर्णांक err = patch_simple_hdmi(codec, nvhdmi_master_con_nid_7x,
				    nvhdmi_master_pin_nid_7x);
	अगर (err < 0)
		वापस err;

	codec->patch_ops.init = nvhdmi_7x_init_2ch;
	/* override the PCM rates, etc, as the codec करोesn't give full list */
	spec = codec->spec;
	spec->pcm_playback.rates = SUPPORTED_RATES;
	spec->pcm_playback.maxbps = SUPPORTED_MAXBPS;
	spec->pcm_playback.क्रमmats = SUPPORTED_FORMATS;
	वापस 0;
पूर्ण

अटल पूर्णांक nvhdmi_7x_8ch_build_pcms(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक err = simple_playback_build_pcms(codec);
	अगर (!err) अणु
		काष्ठा hda_pcm *info = get_pcm_rec(spec, 0);
		info->own_chmap = true;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक nvhdmi_7x_8ch_build_controls(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	काष्ठा hda_pcm *info;
	काष्ठा snd_pcm_chmap *chmap;
	पूर्णांक err;

	err = simple_playback_build_controls(codec);
	अगर (err < 0)
		वापस err;

	/* add channel maps */
	info = get_pcm_rec(spec, 0);
	err = snd_pcm_add_chmap_ctls(info->pcm,
				     SNDRV_PCM_STREAM_PLAYBACK,
				     snd_pcm_alt_chmaps, 8, 0, &chmap);
	अगर (err < 0)
		वापस err;
	चयन (codec->preset->venकरोr_id) अणु
	हाल 0x10de0002:
	हाल 0x10de0003:
	हाल 0x10de0005:
	हाल 0x10de0006:
		chmap->channel_mask = (1U << 2) | (1U << 8);
		अवरोध;
	हाल 0x10de0007:
		chmap->channel_mask = (1U << 2) | (1U << 6) | (1U << 8);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक patch_nvhdmi_8ch_7x(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec;
	पूर्णांक err = patch_nvhdmi_2ch(codec);
	अगर (err < 0)
		वापस err;
	spec = codec->spec;
	spec->multiout.max_channels = 8;
	spec->pcm_playback = nvhdmi_pcm_playback_8ch_7x;
	codec->patch_ops.init = nvhdmi_7x_init_8ch;
	codec->patch_ops.build_pcms = nvhdmi_7x_8ch_build_pcms;
	codec->patch_ops.build_controls = nvhdmi_7x_8ch_build_controls;

	/* Initialize the audio infoframe channel mask and checksum to something
	 * valid */
	nvhdmi_8ch_7x_set_info_frame_parameters(codec, 8);

	वापस 0;
पूर्ण

/*
 * NVIDIA codecs ignore ASP mapping क्रम 2ch - confirmed on:
 * - 0x10de0015
 * - 0x10de0040
 */
अटल पूर्णांक nvhdmi_chmap_cea_alloc_validate_get_type(काष्ठा hdac_chmap *chmap,
		काष्ठा hdac_cea_channel_speaker_allocation *cap, पूर्णांक channels)
अणु
	अगर (cap->ca_index == 0x00 && channels == 2)
		वापस SNDRV_CTL_TLVT_CHMAP_FIXED;

	/* If the speaker allocation matches the channel count, it is OK. */
	अगर (cap->channels != channels)
		वापस -1;

	/* all channels are remappable मुक्तly */
	वापस SNDRV_CTL_TLVT_CHMAP_VAR;
पूर्ण

अटल पूर्णांक nvhdmi_chmap_validate(काष्ठा hdac_chmap *chmap,
		पूर्णांक ca, पूर्णांक chs, अचिन्हित अक्षर *map)
अणु
	अगर (ca == 0x00 && (map[0] != SNDRV_CHMAP_FL || map[1] != SNDRV_CHMAP_FR))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* map from pin NID to port; port is 0-based */
/* क्रम Nvidia: assume widget NID starting from 4, with step 1 (4, 5, 6, ...) */
अटल पूर्णांक nvhdmi_pin2port(व्योम *audio_ptr, पूर्णांक pin_nid)
अणु
	वापस pin_nid - 4;
पूर्ण

/* reverse-map from port to pin NID: see above */
अटल पूर्णांक nvhdmi_port2pin(काष्ठा hda_codec *codec, पूर्णांक port)
अणु
	वापस port + 4;
पूर्ण

अटल स्थिर काष्ठा drm_audio_component_audio_ops nvhdmi_audio_ops = अणु
	.pin2port = nvhdmi_pin2port,
	.pin_eld_notअगरy = generic_acomp_pin_eld_notअगरy,
	.master_bind = generic_acomp_master_bind,
	.master_unbind = generic_acomp_master_unbind,
पूर्ण;

अटल पूर्णांक patch_nvhdmi(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec;
	पूर्णांक err;

	err = alloc_generic_hdmi(codec);
	अगर (err < 0)
		वापस err;
	codec->dp_mst = true;

	spec = codec->spec;
	spec->dyn_pcm_assign = true;

	err = hdmi_parse_codec(codec);
	अगर (err < 0) अणु
		generic_spec_मुक्त(codec);
		वापस err;
	पूर्ण

	generic_hdmi_init_per_pins(codec);

	spec->dyn_pin_out = true;

	spec->chmap.ops.chmap_cea_alloc_validate_get_type =
		nvhdmi_chmap_cea_alloc_validate_get_type;
	spec->chmap.ops.chmap_validate = nvhdmi_chmap_validate;

	codec->link_करोwn_at_suspend = 1;

	generic_acomp_init(codec, &nvhdmi_audio_ops, nvhdmi_port2pin);

	वापस 0;
पूर्ण

अटल पूर्णांक patch_nvhdmi_legacy(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec;
	पूर्णांक err;

	err = patch_generic_hdmi(codec);
	अगर (err)
		वापस err;

	spec = codec->spec;
	spec->dyn_pin_out = true;

	spec->chmap.ops.chmap_cea_alloc_validate_get_type =
		nvhdmi_chmap_cea_alloc_validate_get_type;
	spec->chmap.ops.chmap_validate = nvhdmi_chmap_validate;

	codec->link_करोwn_at_suspend = 1;

	वापस 0;
पूर्ण

/*
 * The HDA codec on NVIDIA Tegra contains two scratch रेजिस्टरs that are
 * accessed using venकरोr-defined verbs. These रेजिस्टरs can be used क्रम
 * पूर्णांकeroperability between the HDA and HDMI drivers.
 */

/* Audio Function Group node */
#घोषणा NVIDIA_AFG_NID 0x01

/*
 * The SCRATCH0 रेजिस्टर is used to notअगरy the HDMI codec of changes in audio
 * क्रमmat. On Tegra, bit 31 is used as a trigger that causes an पूर्णांकerrupt to
 * be उठाओd in the HDMI codec. The reमुख्यder of the bits is arbitrary. This
 * implementation stores the HDA क्रमmat (see AC_FMT_*) in bits [15:0] and an
 * additional bit (at position 30) to संकेत the validity of the क्रमmat.
 *
 * | 31      | 30    | 29  16 | 15   0 |
 * +---------+-------+--------+--------+
 * | TRIGGER | VALID | UNUSED | FORMAT |
 * +-----------------------------------|
 *
 * Note that क्रम the trigger bit to take effect it needs to change value
 * (i.e. it needs to be toggled).
 */
#घोषणा NVIDIA_GET_SCRATCH0		0xfa6
#घोषणा NVIDIA_SET_SCRATCH0_BYTE0	0xfa7
#घोषणा NVIDIA_SET_SCRATCH0_BYTE1	0xfa8
#घोषणा NVIDIA_SET_SCRATCH0_BYTE2	0xfa9
#घोषणा NVIDIA_SET_SCRATCH0_BYTE3	0xfaa
#घोषणा NVIDIA_SCRATCH_TRIGGER (1 << 7)
#घोषणा NVIDIA_SCRATCH_VALID   (1 << 6)

#घोषणा NVIDIA_GET_SCRATCH1		0xfab
#घोषणा NVIDIA_SET_SCRATCH1_BYTE0	0xfac
#घोषणा NVIDIA_SET_SCRATCH1_BYTE1	0xfad
#घोषणा NVIDIA_SET_SCRATCH1_BYTE2	0xfae
#घोषणा NVIDIA_SET_SCRATCH1_BYTE3	0xfaf

/*
 * The क्रमmat parameter is the HDA audio क्रमmat (see AC_FMT_*). If set to 0,
 * the क्रमmat is invalidated so that the HDMI codec can be disabled.
 */
अटल व्योम tegra_hdmi_set_क्रमmat(काष्ठा hda_codec *codec, अचिन्हित पूर्णांक क्रमmat)
अणु
	अचिन्हित पूर्णांक value;

	/* bits [31:30] contain the trigger and valid bits */
	value = snd_hda_codec_पढ़ो(codec, NVIDIA_AFG_NID, 0,
				   NVIDIA_GET_SCRATCH0, 0);
	value = (value >> 24) & 0xff;

	/* bits [15:0] are used to store the HDA क्रमmat */
	snd_hda_codec_ग_लिखो(codec, NVIDIA_AFG_NID, 0,
			    NVIDIA_SET_SCRATCH0_BYTE0,
			    (क्रमmat >> 0) & 0xff);
	snd_hda_codec_ग_लिखो(codec, NVIDIA_AFG_NID, 0,
			    NVIDIA_SET_SCRATCH0_BYTE1,
			    (क्रमmat >> 8) & 0xff);

	/* bits [16:24] are unused */
	snd_hda_codec_ग_लिखो(codec, NVIDIA_AFG_NID, 0,
			    NVIDIA_SET_SCRATCH0_BYTE2, 0);

	/*
	 * Bit 30 संकेतs that the data is valid and hence that HDMI audio can
	 * be enabled.
	 */
	अगर (क्रमmat == 0)
		value &= ~NVIDIA_SCRATCH_VALID;
	अन्यथा
		value |= NVIDIA_SCRATCH_VALID;

	/*
	 * Whenever the trigger bit is toggled, an पूर्णांकerrupt is उठाओd in the
	 * HDMI codec. The HDMI driver will use that as trigger to update its
	 * configuration.
	 */
	value ^= NVIDIA_SCRATCH_TRIGGER;

	snd_hda_codec_ग_लिखो(codec, NVIDIA_AFG_NID, 0,
			    NVIDIA_SET_SCRATCH0_BYTE3, value);
पूर्ण

अटल पूर्णांक tegra_hdmi_pcm_prepare(काष्ठा hda_pcm_stream *hinfo,
				  काष्ठा hda_codec *codec,
				  अचिन्हित पूर्णांक stream_tag,
				  अचिन्हित पूर्णांक क्रमmat,
				  काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक err;

	err = generic_hdmi_playback_pcm_prepare(hinfo, codec, stream_tag,
						क्रमmat, substream);
	अगर (err < 0)
		वापस err;

	/* notअगरy the HDMI codec of the क्रमmat change */
	tegra_hdmi_set_क्रमmat(codec, क्रमmat);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_hdmi_pcm_cleanup(काष्ठा hda_pcm_stream *hinfo,
				  काष्ठा hda_codec *codec,
				  काष्ठा snd_pcm_substream *substream)
अणु
	/* invalidate the क्रमmat in the HDMI codec */
	tegra_hdmi_set_क्रमmat(codec, 0);

	वापस generic_hdmi_playback_pcm_cleanup(hinfo, codec, substream);
पूर्ण

अटल काष्ठा hda_pcm *hda_find_pcm_by_type(काष्ठा hda_codec *codec, पूर्णांक type)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < spec->num_pins; i++) अणु
		काष्ठा hda_pcm *pcm = get_pcm_rec(spec, i);

		अगर (pcm->pcm_type == type)
			वापस pcm;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक tegra_hdmi_build_pcms(काष्ठा hda_codec *codec)
अणु
	काष्ठा hda_pcm_stream *stream;
	काष्ठा hda_pcm *pcm;
	पूर्णांक err;

	err = generic_hdmi_build_pcms(codec);
	अगर (err < 0)
		वापस err;

	pcm = hda_find_pcm_by_type(codec, HDA_PCM_TYPE_HDMI);
	अगर (!pcm)
		वापस -ENODEV;

	/*
	 * Override ->prepare() and ->cleanup() operations to notअगरy the HDMI
	 * codec about क्रमmat changes.
	 */
	stream = &pcm->stream[SNDRV_PCM_STREAM_PLAYBACK];
	stream->ops.prepare = tegra_hdmi_pcm_prepare;
	stream->ops.cleanup = tegra_hdmi_pcm_cleanup;

	वापस 0;
पूर्ण

अटल पूर्णांक patch_tegra_hdmi(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec;
	पूर्णांक err;

	err = patch_generic_hdmi(codec);
	अगर (err)
		वापस err;

	codec->patch_ops.build_pcms = tegra_hdmi_build_pcms;
	spec = codec->spec;
	spec->chmap.ops.chmap_cea_alloc_validate_get_type =
		nvhdmi_chmap_cea_alloc_validate_get_type;
	spec->chmap.ops.chmap_validate = nvhdmi_chmap_validate;

	वापस 0;
पूर्ण

/*
 * ATI/AMD-specअगरic implementations
 */

#घोषणा is_amdhdmi_rev3_or_later(codec) \
	((codec)->core.venकरोr_id == 0x1002aa01 && \
	 ((codec)->core.revision_id & 0xff00) >= 0x0300)
#घोषणा has_amd_full_remap_support(codec) is_amdhdmi_rev3_or_later(codec)

/* ATI/AMD specअगरic HDA pin verbs, see the AMD HDA Verbs specअगरication */
#घोषणा ATI_VERB_SET_CHANNEL_ALLOCATION	0x771
#घोषणा ATI_VERB_SET_DOWNMIX_INFO	0x772
#घोषणा ATI_VERB_SET_MULTICHANNEL_01	0x777
#घोषणा ATI_VERB_SET_MULTICHANNEL_23	0x778
#घोषणा ATI_VERB_SET_MULTICHANNEL_45	0x779
#घोषणा ATI_VERB_SET_MULTICHANNEL_67	0x77a
#घोषणा ATI_VERB_SET_HBR_CONTROL	0x77c
#घोषणा ATI_VERB_SET_MULTICHANNEL_1	0x785
#घोषणा ATI_VERB_SET_MULTICHANNEL_3	0x786
#घोषणा ATI_VERB_SET_MULTICHANNEL_5	0x787
#घोषणा ATI_VERB_SET_MULTICHANNEL_7	0x788
#घोषणा ATI_VERB_SET_MULTICHANNEL_MODE	0x789
#घोषणा ATI_VERB_GET_CHANNEL_ALLOCATION	0xf71
#घोषणा ATI_VERB_GET_DOWNMIX_INFO	0xf72
#घोषणा ATI_VERB_GET_MULTICHANNEL_01	0xf77
#घोषणा ATI_VERB_GET_MULTICHANNEL_23	0xf78
#घोषणा ATI_VERB_GET_MULTICHANNEL_45	0xf79
#घोषणा ATI_VERB_GET_MULTICHANNEL_67	0xf7a
#घोषणा ATI_VERB_GET_HBR_CONTROL	0xf7c
#घोषणा ATI_VERB_GET_MULTICHANNEL_1	0xf85
#घोषणा ATI_VERB_GET_MULTICHANNEL_3	0xf86
#घोषणा ATI_VERB_GET_MULTICHANNEL_5	0xf87
#घोषणा ATI_VERB_GET_MULTICHANNEL_7	0xf88
#घोषणा ATI_VERB_GET_MULTICHANNEL_MODE	0xf89

/* AMD specअगरic HDA cvt verbs */
#घोषणा ATI_VERB_SET_RAMP_RATE		0x770
#घोषणा ATI_VERB_GET_RAMP_RATE		0xf70

#घोषणा ATI_OUT_ENABLE 0x1

#घोषणा ATI_MULTICHANNEL_MODE_PAIRED	0
#घोषणा ATI_MULTICHANNEL_MODE_SINGLE	1

#घोषणा ATI_HBR_CAPABLE 0x01
#घोषणा ATI_HBR_ENABLE 0x10

अटल पूर्णांक atihdmi_pin_get_eld(काष्ठा hda_codec *codec, hda_nid_t nid,
			       पूर्णांक dev_id, अचिन्हित अक्षर *buf, पूर्णांक *eld_size)
अणु
	WARN_ON(dev_id != 0);
	/* call hda_eld.c ATI/AMD-specअगरic function */
	वापस snd_hdmi_get_eld_ati(codec, nid, buf, eld_size,
				    is_amdhdmi_rev3_or_later(codec));
पूर्ण

अटल व्योम atihdmi_pin_setup_infoframe(काष्ठा hda_codec *codec,
					hda_nid_t pin_nid, पूर्णांक dev_id, पूर्णांक ca,
					पूर्णांक active_channels, पूर्णांक conn_type)
अणु
	WARN_ON(dev_id != 0);
	snd_hda_codec_ग_लिखो(codec, pin_nid, 0, ATI_VERB_SET_CHANNEL_ALLOCATION, ca);
पूर्ण

अटल पूर्णांक atihdmi_paired_swap_fc_lfe(पूर्णांक pos)
अणु
	/*
	 * ATI/AMD have स्वतःmatic FC/LFE swap built-in
	 * when in pairwise mapping mode.
	 */

	चयन (pos) अणु
		/* see channel_allocations[].speakers[] */
		हाल 2: वापस 3;
		हाल 3: वापस 2;
		शेष: अवरोध;
	पूर्ण

	वापस pos;
पूर्ण

अटल पूर्णांक atihdmi_paired_chmap_validate(काष्ठा hdac_chmap *chmap,
			पूर्णांक ca, पूर्णांक chs, अचिन्हित अक्षर *map)
अणु
	काष्ठा hdac_cea_channel_speaker_allocation *cap;
	पूर्णांक i, j;

	/* check that only channel pairs need to be remapped on old pre-rev3 ATI/AMD */

	cap = snd_hdac_get_ch_alloc_from_ca(ca);
	क्रम (i = 0; i < chs; ++i) अणु
		पूर्णांक mask = snd_hdac_chmap_to_spk_mask(map[i]);
		bool ok = false;
		bool companion_ok = false;

		अगर (!mask)
			जारी;

		क्रम (j = 0 + i % 2; j < 8; j += 2) अणु
			पूर्णांक chan_idx = 7 - atihdmi_paired_swap_fc_lfe(j);
			अगर (cap->speakers[chan_idx] == mask) अणु
				/* channel is in a supported position */
				ok = true;

				अगर (i % 2 == 0 && i + 1 < chs) अणु
					/* even channel, check the odd companion */
					पूर्णांक comp_chan_idx = 7 - atihdmi_paired_swap_fc_lfe(j + 1);
					पूर्णांक comp_mask_req = snd_hdac_chmap_to_spk_mask(map[i+1]);
					पूर्णांक comp_mask_act = cap->speakers[comp_chan_idx];

					अगर (comp_mask_req == comp_mask_act)
						companion_ok = true;
					अन्यथा
						वापस -EINVAL;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!ok)
			वापस -EINVAL;

		अगर (companion_ok)
			i++; /* companion channel alपढ़ोy checked */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक atihdmi_pin_set_slot_channel(काष्ठा hdac_device *hdac,
		hda_nid_t pin_nid, पूर्णांक hdmi_slot, पूर्णांक stream_channel)
अणु
	काष्ठा hda_codec *codec = hdac_to_hda_codec(hdac);
	पूर्णांक verb;
	पूर्णांक ati_channel_setup = 0;

	अगर (hdmi_slot > 7)
		वापस -EINVAL;

	अगर (!has_amd_full_remap_support(codec)) अणु
		hdmi_slot = atihdmi_paired_swap_fc_lfe(hdmi_slot);

		/* In हाल this is an odd slot but without stream channel, करो not
		 * disable the slot since the corresponding even slot could have a
		 * channel. In हाल neither have a channel, the slot pair will be
		 * disabled when this function is called क्रम the even slot. */
		अगर (hdmi_slot % 2 != 0 && stream_channel == 0xf)
			वापस 0;

		hdmi_slot -= hdmi_slot % 2;

		अगर (stream_channel != 0xf)
			stream_channel -= stream_channel % 2;
	पूर्ण

	verb = ATI_VERB_SET_MULTICHANNEL_01 + hdmi_slot/2 + (hdmi_slot % 2) * 0x00e;

	/* ati_channel_setup क्रमmat: [7..4] = stream_channel_id, [1] = mute, [0] = enable */

	अगर (stream_channel != 0xf)
		ati_channel_setup = (stream_channel << 4) | ATI_OUT_ENABLE;

	वापस snd_hda_codec_ग_लिखो(codec, pin_nid, 0, verb, ati_channel_setup);
पूर्ण

अटल पूर्णांक atihdmi_pin_get_slot_channel(काष्ठा hdac_device *hdac,
				hda_nid_t pin_nid, पूर्णांक asp_slot)
अणु
	काष्ठा hda_codec *codec = hdac_to_hda_codec(hdac);
	bool was_odd = false;
	पूर्णांक ati_asp_slot = asp_slot;
	पूर्णांक verb;
	पूर्णांक ati_channel_setup;

	अगर (asp_slot > 7)
		वापस -EINVAL;

	अगर (!has_amd_full_remap_support(codec)) अणु
		ati_asp_slot = atihdmi_paired_swap_fc_lfe(asp_slot);
		अगर (ati_asp_slot % 2 != 0) अणु
			ati_asp_slot -= 1;
			was_odd = true;
		पूर्ण
	पूर्ण

	verb = ATI_VERB_GET_MULTICHANNEL_01 + ati_asp_slot/2 + (ati_asp_slot % 2) * 0x00e;

	ati_channel_setup = snd_hda_codec_पढ़ो(codec, pin_nid, 0, verb, 0);

	अगर (!(ati_channel_setup & ATI_OUT_ENABLE))
		वापस 0xf;

	वापस ((ati_channel_setup & 0xf0) >> 4) + !!was_odd;
पूर्ण

अटल पूर्णांक atihdmi_paired_chmap_cea_alloc_validate_get_type(
		काष्ठा hdac_chmap *chmap,
		काष्ठा hdac_cea_channel_speaker_allocation *cap,
		पूर्णांक channels)
अणु
	पूर्णांक c;

	/*
	 * Pre-rev3 ATI/AMD codecs operate in a paired channel mode, so
	 * we need to take that पूर्णांकo account (a single channel may take 2
	 * channel slots अगर we need to carry a silent channel next to it).
	 * On Rev3+ AMD codecs this function is not used.
	 */
	पूर्णांक chanpairs = 0;

	/* We only produce even-numbered channel count TLVs */
	अगर ((channels % 2) != 0)
		वापस -1;

	क्रम (c = 0; c < 7; c += 2) अणु
		अगर (cap->speakers[c] || cap->speakers[c+1])
			chanpairs++;
	पूर्ण

	अगर (chanpairs * 2 != channels)
		वापस -1;

	वापस SNDRV_CTL_TLVT_CHMAP_PAIRED;
पूर्ण

अटल व्योम atihdmi_paired_cea_alloc_to_tlv_chmap(काष्ठा hdac_chmap *hchmap,
		काष्ठा hdac_cea_channel_speaker_allocation *cap,
		अचिन्हित पूर्णांक *chmap, पूर्णांक channels)
अणु
	/* produce paired maps क्रम pre-rev3 ATI/AMD codecs */
	पूर्णांक count = 0;
	पूर्णांक c;

	क्रम (c = 7; c >= 0; c--) अणु
		पूर्णांक chan = 7 - atihdmi_paired_swap_fc_lfe(7 - c);
		पूर्णांक spk = cap->speakers[chan];
		अगर (!spk) अणु
			/* add N/A channel अगर the companion channel is occupied */
			अगर (cap->speakers[chan + (chan % 2 ? -1 : 1)])
				chmap[count++] = SNDRV_CHMAP_NA;

			जारी;
		पूर्ण

		chmap[count++] = snd_hdac_spk_to_chmap(spk);
	पूर्ण

	WARN_ON(count != channels);
पूर्ण

अटल पूर्णांक atihdmi_pin_hbr_setup(काष्ठा hda_codec *codec, hda_nid_t pin_nid,
				 पूर्णांक dev_id, bool hbr)
अणु
	पूर्णांक hbr_ctl, hbr_ctl_new;

	WARN_ON(dev_id != 0);

	hbr_ctl = snd_hda_codec_पढ़ो(codec, pin_nid, 0, ATI_VERB_GET_HBR_CONTROL, 0);
	अगर (hbr_ctl >= 0 && (hbr_ctl & ATI_HBR_CAPABLE)) अणु
		अगर (hbr)
			hbr_ctl_new = hbr_ctl | ATI_HBR_ENABLE;
		अन्यथा
			hbr_ctl_new = hbr_ctl & ~ATI_HBR_ENABLE;

		codec_dbg(codec,
			  "atihdmi_pin_hbr_setup: NID=0x%x, %shbr-ctl=0x%x\n",
				pin_nid,
				hbr_ctl == hbr_ctl_new ? "" : "new-",
				hbr_ctl_new);

		अगर (hbr_ctl != hbr_ctl_new)
			snd_hda_codec_ग_लिखो(codec, pin_nid, 0,
						ATI_VERB_SET_HBR_CONTROL,
						hbr_ctl_new);

	पूर्ण अन्यथा अगर (hbr)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक atihdmi_setup_stream(काष्ठा hda_codec *codec, hda_nid_t cvt_nid,
				hda_nid_t pin_nid, पूर्णांक dev_id,
				u32 stream_tag, पूर्णांक क्रमmat)
अणु
	अगर (is_amdhdmi_rev3_or_later(codec)) अणु
		पूर्णांक ramp_rate = 180; /* शेष as per AMD spec */
		/* disable ramp-up/करोwn क्रम non-pcm as per AMD spec */
		अगर (क्रमmat & AC_FMT_TYPE_NON_PCM)
			ramp_rate = 0;

		snd_hda_codec_ग_लिखो(codec, cvt_nid, 0, ATI_VERB_SET_RAMP_RATE, ramp_rate);
	पूर्ण

	वापस hdmi_setup_stream(codec, cvt_nid, pin_nid, dev_id,
				 stream_tag, क्रमmat);
पूर्ण


अटल पूर्णांक atihdmi_init(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec = codec->spec;
	पूर्णांक pin_idx, err;

	err = generic_hdmi_init(codec);

	अगर (err)
		वापस err;

	क्रम (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) अणु
		काष्ठा hdmi_spec_per_pin *per_pin = get_pin(spec, pin_idx);

		/* make sure करोwnmix inक्रमmation in infoframe is zero */
		snd_hda_codec_ग_लिखो(codec, per_pin->pin_nid, 0, ATI_VERB_SET_DOWNMIX_INFO, 0);

		/* enable channel-wise remap mode अगर supported */
		अगर (has_amd_full_remap_support(codec))
			snd_hda_codec_ग_लिखो(codec, per_pin->pin_nid, 0,
					    ATI_VERB_SET_MULTICHANNEL_MODE,
					    ATI_MULTICHANNEL_MODE_SINGLE);
	पूर्ण
	codec->स्वतः_runसमय_pm = 1;

	वापस 0;
पूर्ण

/* map from pin NID to port; port is 0-based */
/* क्रम AMD: assume widget NID starting from 3, with step 2 (3, 5, 7, ...) */
अटल पूर्णांक atihdmi_pin2port(व्योम *audio_ptr, पूर्णांक pin_nid)
अणु
	वापस pin_nid / 2 - 1;
पूर्ण

/* reverse-map from port to pin NID: see above */
अटल पूर्णांक atihdmi_port2pin(काष्ठा hda_codec *codec, पूर्णांक port)
अणु
	वापस port * 2 + 3;
पूर्ण

अटल स्थिर काष्ठा drm_audio_component_audio_ops atihdmi_audio_ops = अणु
	.pin2port = atihdmi_pin2port,
	.pin_eld_notअगरy = generic_acomp_pin_eld_notअगरy,
	.master_bind = generic_acomp_master_bind,
	.master_unbind = generic_acomp_master_unbind,
पूर्ण;

अटल पूर्णांक patch_atihdmi(काष्ठा hda_codec *codec)
अणु
	काष्ठा hdmi_spec *spec;
	काष्ठा hdmi_spec_per_cvt *per_cvt;
	पूर्णांक err, cvt_idx;

	err = patch_generic_hdmi(codec);

	अगर (err)
		वापस err;

	codec->patch_ops.init = atihdmi_init;

	spec = codec->spec;

	spec->ops.pin_get_eld = atihdmi_pin_get_eld;
	spec->ops.pin_setup_infoframe = atihdmi_pin_setup_infoframe;
	spec->ops.pin_hbr_setup = atihdmi_pin_hbr_setup;
	spec->ops.setup_stream = atihdmi_setup_stream;

	spec->chmap.ops.pin_get_slot_channel = atihdmi_pin_get_slot_channel;
	spec->chmap.ops.pin_set_slot_channel = atihdmi_pin_set_slot_channel;

	अगर (!has_amd_full_remap_support(codec)) अणु
		/* override to ATI/AMD-specअगरic versions with pairwise mapping */
		spec->chmap.ops.chmap_cea_alloc_validate_get_type =
			atihdmi_paired_chmap_cea_alloc_validate_get_type;
		spec->chmap.ops.cea_alloc_to_tlv_chmap =
				atihdmi_paired_cea_alloc_to_tlv_chmap;
		spec->chmap.ops.chmap_validate = atihdmi_paired_chmap_validate;
	पूर्ण

	/* ATI/AMD converters करो not advertise all of their capabilities */
	क्रम (cvt_idx = 0; cvt_idx < spec->num_cvts; cvt_idx++) अणु
		per_cvt = get_cvt(spec, cvt_idx);
		per_cvt->channels_max = max(per_cvt->channels_max, 8u);
		per_cvt->rates |= SUPPORTED_RATES;
		per_cvt->क्रमmats |= SUPPORTED_FORMATS;
		per_cvt->maxbps = max(per_cvt->maxbps, 24u);
	पूर्ण

	spec->chmap.channels_max = max(spec->chmap.channels_max, 8u);

	/* AMD GPUs have neither EPSS nor CLKSTOP bits, hence preventing
	 * the link-करोwn as is.  Tell the core to allow it.
	 */
	codec->link_करोwn_at_suspend = 1;

	generic_acomp_init(codec, &atihdmi_audio_ops, atihdmi_port2pin);

	वापस 0;
पूर्ण

/* VIA HDMI Implementation */
#घोषणा VIAHDMI_CVT_NID	0x02	/* audio converter1 */
#घोषणा VIAHDMI_PIN_NID	0x03	/* HDMI output pin1 */

अटल पूर्णांक patch_via_hdmi(काष्ठा hda_codec *codec)
अणु
	वापस patch_simple_hdmi(codec, VIAHDMI_CVT_NID, VIAHDMI_PIN_NID);
पूर्ण

/*
 * patch entries
 */
अटल स्थिर काष्ठा hda_device_id snd_hda_id_hdmi[] = अणु
HDA_CODEC_ENTRY(0x1002793c, "RS600 HDMI",	patch_atihdmi),
HDA_CODEC_ENTRY(0x10027919, "RS600 HDMI",	patch_atihdmi),
HDA_CODEC_ENTRY(0x1002791a, "RS690/780 HDMI",	patch_atihdmi),
HDA_CODEC_ENTRY(0x1002aa01, "R6xx HDMI",	patch_atihdmi),
HDA_CODEC_ENTRY(0x10951390, "SiI1390 HDMI",	patch_generic_hdmi),
HDA_CODEC_ENTRY(0x10951392, "SiI1392 HDMI",	patch_generic_hdmi),
HDA_CODEC_ENTRY(0x17e80047, "Chrontel HDMI",	patch_generic_hdmi),
HDA_CODEC_ENTRY(0x10de0001, "MCP73 HDMI",	patch_nvhdmi_2ch),
HDA_CODEC_ENTRY(0x10de0002, "MCP77/78 HDMI",	patch_nvhdmi_8ch_7x),
HDA_CODEC_ENTRY(0x10de0003, "MCP77/78 HDMI",	patch_nvhdmi_8ch_7x),
HDA_CODEC_ENTRY(0x10de0004, "GPU 04 HDMI",	patch_nvhdmi_8ch_7x),
HDA_CODEC_ENTRY(0x10de0005, "MCP77/78 HDMI",	patch_nvhdmi_8ch_7x),
HDA_CODEC_ENTRY(0x10de0006, "MCP77/78 HDMI",	patch_nvhdmi_8ch_7x),
HDA_CODEC_ENTRY(0x10de0007, "MCP79/7A HDMI",	patch_nvhdmi_8ch_7x),
HDA_CODEC_ENTRY(0x10de0008, "GPU 08 HDMI/DP",	patch_nvhdmi_legacy),
HDA_CODEC_ENTRY(0x10de0009, "GPU 09 HDMI/DP",	patch_nvhdmi_legacy),
HDA_CODEC_ENTRY(0x10de000a, "GPU 0a HDMI/DP",	patch_nvhdmi_legacy),
HDA_CODEC_ENTRY(0x10de000b, "GPU 0b HDMI/DP",	patch_nvhdmi_legacy),
HDA_CODEC_ENTRY(0x10de000c, "MCP89 HDMI",	patch_nvhdmi_legacy),
HDA_CODEC_ENTRY(0x10de000d, "GPU 0d HDMI/DP",	patch_nvhdmi_legacy),
HDA_CODEC_ENTRY(0x10de0010, "GPU 10 HDMI/DP",	patch_nvhdmi_legacy),
HDA_CODEC_ENTRY(0x10de0011, "GPU 11 HDMI/DP",	patch_nvhdmi_legacy),
HDA_CODEC_ENTRY(0x10de0012, "GPU 12 HDMI/DP",	patch_nvhdmi_legacy),
HDA_CODEC_ENTRY(0x10de0013, "GPU 13 HDMI/DP",	patch_nvhdmi_legacy),
HDA_CODEC_ENTRY(0x10de0014, "GPU 14 HDMI/DP",	patch_nvhdmi_legacy),
HDA_CODEC_ENTRY(0x10de0015, "GPU 15 HDMI/DP",	patch_nvhdmi_legacy),
HDA_CODEC_ENTRY(0x10de0016, "GPU 16 HDMI/DP",	patch_nvhdmi_legacy),
/* 17 is known to be असलent */
HDA_CODEC_ENTRY(0x10de0018, "GPU 18 HDMI/DP",	patch_nvhdmi_legacy),
HDA_CODEC_ENTRY(0x10de0019, "GPU 19 HDMI/DP",	patch_nvhdmi_legacy),
HDA_CODEC_ENTRY(0x10de001a, "GPU 1a HDMI/DP",	patch_nvhdmi_legacy),
HDA_CODEC_ENTRY(0x10de001b, "GPU 1b HDMI/DP",	patch_nvhdmi_legacy),
HDA_CODEC_ENTRY(0x10de001c, "GPU 1c HDMI/DP",	patch_nvhdmi_legacy),
HDA_CODEC_ENTRY(0x10de0020, "Tegra30 HDMI",	patch_tegra_hdmi),
HDA_CODEC_ENTRY(0x10de0022, "Tegra114 HDMI",	patch_tegra_hdmi),
HDA_CODEC_ENTRY(0x10de0028, "Tegra124 HDMI",	patch_tegra_hdmi),
HDA_CODEC_ENTRY(0x10de0029, "Tegra210 HDMI/DP",	patch_tegra_hdmi),
HDA_CODEC_ENTRY(0x10de002d, "Tegra186 HDMI/DP0", patch_tegra_hdmi),
HDA_CODEC_ENTRY(0x10de002e, "Tegra186 HDMI/DP1", patch_tegra_hdmi),
HDA_CODEC_ENTRY(0x10de002f, "Tegra194 HDMI/DP2", patch_tegra_hdmi),
HDA_CODEC_ENTRY(0x10de0030, "Tegra194 HDMI/DP3", patch_tegra_hdmi),
HDA_CODEC_ENTRY(0x10de0040, "GPU 40 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0041, "GPU 41 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0042, "GPU 42 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0043, "GPU 43 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0044, "GPU 44 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0045, "GPU 45 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0050, "GPU 50 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0051, "GPU 51 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0052, "GPU 52 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0060, "GPU 60 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0061, "GPU 61 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0062, "GPU 62 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0067, "MCP67 HDMI",	patch_nvhdmi_2ch),
HDA_CODEC_ENTRY(0x10de0070, "GPU 70 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0071, "GPU 71 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0072, "GPU 72 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0073, "GPU 73 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0074, "GPU 74 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0076, "GPU 76 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de007b, "GPU 7b HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de007c, "GPU 7c HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de007d, "GPU 7d HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de007e, "GPU 7e HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0080, "GPU 80 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0081, "GPU 81 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0082, "GPU 82 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0083, "GPU 83 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0084, "GPU 84 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0090, "GPU 90 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0091, "GPU 91 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0092, "GPU 92 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0093, "GPU 93 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0094, "GPU 94 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0095, "GPU 95 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0097, "GPU 97 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0098, "GPU 98 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de0099, "GPU 99 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de009a, "GPU 9a HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de009d, "GPU 9d HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de009e, "GPU 9e HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de009f, "GPU 9f HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de00a0, "GPU a0 HDMI/DP",	patch_nvhdmi),
HDA_CODEC_ENTRY(0x10de8001, "MCP73 HDMI",	patch_nvhdmi_2ch),
HDA_CODEC_ENTRY(0x10de8067, "MCP67/68 HDMI",	patch_nvhdmi_2ch),
HDA_CODEC_ENTRY(0x11069f80, "VX900 HDMI/DP",	patch_via_hdmi),
HDA_CODEC_ENTRY(0x11069f81, "VX900 HDMI/DP",	patch_via_hdmi),
HDA_CODEC_ENTRY(0x11069f84, "VX11 HDMI/DP",	patch_generic_hdmi),
HDA_CODEC_ENTRY(0x11069f85, "VX11 HDMI/DP",	patch_generic_hdmi),
HDA_CODEC_ENTRY(0x80860054, "IbexPeak HDMI",	patch_i915_cpt_hdmi),
HDA_CODEC_ENTRY(0x80862800, "Geminilake HDMI",	patch_i915_glk_hdmi),
HDA_CODEC_ENTRY(0x80862801, "Bearlake HDMI",	patch_generic_hdmi),
HDA_CODEC_ENTRY(0x80862802, "Cantiga HDMI",	patch_generic_hdmi),
HDA_CODEC_ENTRY(0x80862803, "Eaglelake HDMI",	patch_generic_hdmi),
HDA_CODEC_ENTRY(0x80862804, "IbexPeak HDMI",	patch_i915_cpt_hdmi),
HDA_CODEC_ENTRY(0x80862805, "CougarPoint HDMI",	patch_i915_cpt_hdmi),
HDA_CODEC_ENTRY(0x80862806, "PantherPoint HDMI", patch_i915_cpt_hdmi),
HDA_CODEC_ENTRY(0x80862807, "Haswell HDMI",	patch_i915_hsw_hdmi),
HDA_CODEC_ENTRY(0x80862808, "Broadwell HDMI",	patch_i915_hsw_hdmi),
HDA_CODEC_ENTRY(0x80862809, "Skylake HDMI",	patch_i915_hsw_hdmi),
HDA_CODEC_ENTRY(0x8086280a, "Broxton HDMI",	patch_i915_hsw_hdmi),
HDA_CODEC_ENTRY(0x8086280b, "Kabylake HDMI",	patch_i915_hsw_hdmi),
HDA_CODEC_ENTRY(0x8086280c, "Cannonlake HDMI",	patch_i915_glk_hdmi),
HDA_CODEC_ENTRY(0x8086280d, "Geminilake HDMI",	patch_i915_glk_hdmi),
HDA_CODEC_ENTRY(0x8086280f, "Icelake HDMI",	patch_i915_icl_hdmi),
HDA_CODEC_ENTRY(0x80862812, "Tigerlake HDMI",	patch_i915_tgl_hdmi),
HDA_CODEC_ENTRY(0x80862814, "DG1 HDMI",	patch_i915_tgl_hdmi),
HDA_CODEC_ENTRY(0x80862815, "Alderlake HDMI",	patch_i915_tgl_hdmi),
HDA_CODEC_ENTRY(0x8086281c, "Alderlake-P HDMI", patch_i915_tgl_hdmi),
HDA_CODEC_ENTRY(0x80862816, "Rocketlake HDMI",	patch_i915_tgl_hdmi),
HDA_CODEC_ENTRY(0x8086281a, "Jasperlake HDMI",	patch_i915_icl_hdmi),
HDA_CODEC_ENTRY(0x8086281b, "Elkhartlake HDMI",	patch_i915_icl_hdmi),
HDA_CODEC_ENTRY(0x80862880, "CedarTrail HDMI",	patch_generic_hdmi),
HDA_CODEC_ENTRY(0x80862882, "Valleyview2 HDMI",	patch_i915_byt_hdmi),
HDA_CODEC_ENTRY(0x80862883, "Braswell HDMI",	patch_i915_byt_hdmi),
HDA_CODEC_ENTRY(0x808629fb, "Crestline HDMI",	patch_generic_hdmi),
/* special ID क्रम generic HDMI */
HDA_CODEC_ENTRY(HDA_CODEC_ID_GENERIC_HDMI, "Generic HDMI", patch_generic_hdmi),
अणुपूर्ण /* terminator */
पूर्ण;
MODULE_DEVICE_TABLE(hdaudio, snd_hda_id_hdmi);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HDMI HD-audio codec");
MODULE_ALIAS("snd-hda-codec-intelhdmi");
MODULE_ALIAS("snd-hda-codec-nvhdmi");
MODULE_ALIAS("snd-hda-codec-atihdmi");

अटल काष्ठा hda_codec_driver hdmi_driver = अणु
	.id = snd_hda_id_hdmi,
पूर्ण;

module_hda_codec_driver(hdmi_driver);
