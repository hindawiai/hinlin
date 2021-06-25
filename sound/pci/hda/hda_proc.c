<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Universal Interface क्रम Intel High Definition Audio Codec
 * 
 * Generic proc पूर्णांकerface
 *
 * Copyright (c) 2004 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <linux/module.h>
#समावेश <sound/hda_codec.h>
#समावेश "hda_local.h"

अटल पूर्णांक dump_coef = -1;
module_param(dump_coef, पूर्णांक, 0644);
MODULE_PARM_DESC(dump_coef, "Dump processing coefficients in codec proc file (-1=auto, 0=disable, 1=enable)");

/* always use noncached version */
#घोषणा param_पढ़ो(codec, nid, parm) \
	snd_hdac_पढ़ो_parm_uncached(&(codec)->core, nid, parm)

अटल स्थिर अक्षर *get_wid_type_name(अचिन्हित पूर्णांक wid_value)
अणु
	अटल स्थिर अक्षर * स्थिर names[16] = अणु
		[AC_WID_AUD_OUT] = "Audio Output",
		[AC_WID_AUD_IN] = "Audio Input",
		[AC_WID_AUD_MIX] = "Audio Mixer",
		[AC_WID_AUD_SEL] = "Audio Selector",
		[AC_WID_PIN] = "Pin Complex",
		[AC_WID_POWER] = "Power Widget",
		[AC_WID_VOL_KNB] = "Volume Knob Widget",
		[AC_WID_BEEP] = "Beep Generator Widget",
		[AC_WID_VENDOR] = "Vendor Defined Widget",
	पूर्ण;
	अगर (wid_value == -1)
		वापस "UNKNOWN Widget";
	wid_value &= 0xf;
	अगर (names[wid_value])
		वापस names[wid_value];
	अन्यथा
		वापस "UNKNOWN Widget";
पूर्ण

अटल व्योम prपूर्णांक_nid_array(काष्ठा snd_info_buffer *buffer,
			    काष्ठा hda_codec *codec, hda_nid_t nid,
			    काष्ठा snd_array *array)
अणु
	पूर्णांक i;
	काष्ठा hda_nid_item *items = array->list, *item;
	काष्ठा snd_kcontrol *kctl;
	क्रम (i = 0; i < array->used; i++) अणु
		item = &items[i];
		अगर (item->nid == nid) अणु
			kctl = item->kctl;
			snd_iम_लिखो(buffer,
			  "  Control: name=\"%s\", index=%i, device=%i\n",
			  kctl->id.name, kctl->id.index + item->index,
			  kctl->id.device);
			अगर (item->flags & HDA_NID_ITEM_AMP)
				snd_iम_लिखो(buffer,
				  "    ControlAmp: chs=%lu, dir=%s, "
				  "idx=%lu, ofs=%lu\n",
				  get_amp_channels(kctl),
				  get_amp_direction(kctl) ? "Out" : "In",
				  get_amp_index(kctl),
				  get_amp_offset(kctl));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_nid_pcms(काष्ठा snd_info_buffer *buffer,
			   काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	पूर्णांक type;
	काष्ठा hda_pcm *cpcm;

	list_क्रम_each_entry(cpcm, &codec->pcm_list_head, list) अणु
		क्रम (type = 0; type < 2; type++) अणु
			अगर (cpcm->stream[type].nid != nid || cpcm->pcm == शून्य)
				जारी;
			snd_iम_लिखो(buffer, "  Device: name=\"%s\", "
				    "type=\"%s\", device=%i\n",
				    cpcm->name,
				    snd_hda_pcm_type_name[cpcm->pcm_type],
				    cpcm->pcm->device);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_amp_caps(काष्ठा snd_info_buffer *buffer,
			   काष्ठा hda_codec *codec, hda_nid_t nid, पूर्णांक dir)
अणु
	अचिन्हित पूर्णांक caps;
	caps = param_पढ़ो(codec, nid, dir == HDA_OUTPUT ?
			  AC_PAR_AMP_OUT_CAP : AC_PAR_AMP_IN_CAP);
	अगर (caps == -1 || caps == 0) अणु
		snd_iम_लिखो(buffer, "N/A\n");
		वापस;
	पूर्ण
	snd_iम_लिखो(buffer, "ofs=0x%02x, nsteps=0x%02x, stepsize=0x%02x, "
		    "mute=%x\n",
		    caps & AC_AMPCAP_OFFSET,
		    (caps & AC_AMPCAP_NUM_STEPS) >> AC_AMPCAP_NUM_STEPS_SHIFT,
		    (caps & AC_AMPCAP_STEP_SIZE) >> AC_AMPCAP_STEP_SIZE_SHIFT,
		    (caps & AC_AMPCAP_MUTE) >> AC_AMPCAP_MUTE_SHIFT);
पूर्ण

/* is this a stereo widget or a stereo-to-mono mix? */
अटल bool is_stereo_amps(काष्ठा hda_codec *codec, hda_nid_t nid,
			   पूर्णांक dir, अचिन्हित पूर्णांक wcaps, पूर्णांक indices)
अणु
	hda_nid_t conn;

	अगर (wcaps & AC_WCAP_STEREO)
		वापस true;
	/* check क्रम a stereo-to-mono mix; it must be:
	 * only a single connection, only क्रम input, and only a mixer widget
	 */
	अगर (indices != 1 || dir != HDA_INPUT ||
	    get_wcaps_type(wcaps) != AC_WID_AUD_MIX)
		वापस false;

	अगर (snd_hda_get_raw_connections(codec, nid, &conn, 1) < 0)
		वापस false;
	/* the connection source is a stereo? */
	wcaps = snd_hda_param_पढ़ो(codec, conn, AC_PAR_AUDIO_WIDGET_CAP);
	वापस !!(wcaps & AC_WCAP_STEREO);
पूर्ण

अटल व्योम prपूर्णांक_amp_vals(काष्ठा snd_info_buffer *buffer,
			   काष्ठा hda_codec *codec, hda_nid_t nid,
			   पूर्णांक dir, अचिन्हित पूर्णांक wcaps, पूर्णांक indices)
अणु
	अचिन्हित पूर्णांक val;
	bool stereo;
	पूर्णांक i;

	stereo = is_stereo_amps(codec, nid, dir, wcaps, indices);

	dir = dir == HDA_OUTPUT ? AC_AMP_GET_OUTPUT : AC_AMP_GET_INPUT;
	क्रम (i = 0; i < indices; i++) अणु
		snd_iम_लिखो(buffer, " [");
		val = snd_hda_codec_पढ़ो(codec, nid, 0,
					 AC_VERB_GET_AMP_GAIN_MUTE,
					 AC_AMP_GET_LEFT | dir | i);
		snd_iम_लिखो(buffer, "0x%02x", val);
		अगर (stereo) अणु
			val = snd_hda_codec_पढ़ो(codec, nid, 0,
						 AC_VERB_GET_AMP_GAIN_MUTE,
						 AC_AMP_GET_RIGHT | dir | i);
			snd_iम_लिखो(buffer, " 0x%02x", val);
		पूर्ण
		snd_iम_लिखो(buffer, "]");
	पूर्ण
	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल व्योम prपूर्णांक_pcm_rates(काष्ठा snd_info_buffer *buffer, अचिन्हित पूर्णांक pcm)
अणु
	अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु
		8000, 11025, 16000, 22050, 32000, 44100, 48000, 88200,
		96000, 176400, 192000, 384000
	पूर्ण;
	पूर्णांक i;

	pcm &= AC_SUPPCM_RATES;
	snd_iम_लिखो(buffer, "    rates [0x%x]:", pcm);
	क्रम (i = 0; i < ARRAY_SIZE(rates); i++)
		अगर (pcm & (1 << i))
			snd_iम_लिखो(buffer,  " %d", rates[i]);
	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल व्योम prपूर्णांक_pcm_bits(काष्ठा snd_info_buffer *buffer, अचिन्हित पूर्णांक pcm)
अणु
	अक्षर buf[SND_PRINT_BITS_ADVISED_बफ_मानE];

	snd_iम_लिखो(buffer, "    bits [0x%x]:", (pcm >> 16) & 0xff);
	snd_prपूर्णांक_pcm_bits(pcm, buf, माप(buf));
	snd_iम_लिखो(buffer, "%s\n", buf);
पूर्ण

अटल व्योम prपूर्णांक_pcm_क्रमmats(काष्ठा snd_info_buffer *buffer,
			      अचिन्हित पूर्णांक streams)
अणु
	snd_iम_लिखो(buffer, "    formats [0x%x]:", streams & 0xf);
	अगर (streams & AC_SUPFMT_PCM)
		snd_iम_लिखो(buffer, " PCM");
	अगर (streams & AC_SUPFMT_FLOAT32)
		snd_iम_लिखो(buffer, " FLOAT");
	अगर (streams & AC_SUPFMT_AC3)
		snd_iम_लिखो(buffer, " AC3");
	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल व्योम prपूर्णांक_pcm_caps(काष्ठा snd_info_buffer *buffer,
			   काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अचिन्हित पूर्णांक pcm = param_पढ़ो(codec, nid, AC_PAR_PCM);
	अचिन्हित पूर्णांक stream = param_पढ़ो(codec, nid, AC_PAR_STREAM);
	अगर (pcm == -1 || stream == -1) अणु
		snd_iम_लिखो(buffer, "N/A\n");
		वापस;
	पूर्ण
	prपूर्णांक_pcm_rates(buffer, pcm);
	prपूर्णांक_pcm_bits(buffer, pcm);
	prपूर्णांक_pcm_क्रमmats(buffer, stream);
पूर्ण

अटल स्थिर अक्षर *get_jack_connection(u32 cfg)
अणु
	अटल स्थिर अक्षर * स्थिर names[16] = अणु
		"Unknown", "1/8", "1/4", "ATAPI",
		"RCA", "Optical","Digital", "Analog",
		"DIN", "XLR", "RJ11", "Comb",
		शून्य, शून्य, शून्य, "Other"
	पूर्ण;
	cfg = (cfg & AC_DEFCFG_CONN_TYPE) >> AC_DEFCFG_CONN_TYPE_SHIFT;
	अगर (names[cfg])
		वापस names[cfg];
	अन्यथा
		वापस "UNKNOWN";
पूर्ण

अटल स्थिर अक्षर *get_jack_color(u32 cfg)
अणु
	अटल स्थिर अक्षर * स्थिर names[16] = अणु
		"Unknown", "Black", "Grey", "Blue",
		"Green", "Red", "Orange", "Yellow",
		"Purple", "Pink", शून्य, शून्य,
		शून्य, शून्य, "White", "Other",
	पूर्ण;
	cfg = (cfg & AC_DEFCFG_COLOR) >> AC_DEFCFG_COLOR_SHIFT;
	अगर (names[cfg])
		वापस names[cfg];
	अन्यथा
		वापस "UNKNOWN";
पूर्ण

/*
 * Parse the pin शेष config value and वापसs the string of the
 * jack location, e.g. "Rear", "Front", etc.
 */
अटल स्थिर अक्षर *get_jack_location(u32 cfg)
अणु
	अटल स्थिर अक्षर * स्थिर bases[7] = अणु
		"N/A", "Rear", "Front", "Left", "Right", "Top", "Bottom",
	पूर्ण;
	अटल स्थिर अचिन्हित अक्षर specials_idx[] = अणु
		0x07, 0x08,
		0x17, 0x18, 0x19,
		0x37, 0x38
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर specials[] = अणु
		"Rear Panel", "Drive Bar",
		"Riser", "HDMI", "ATAPI",
		"Mobile-In", "Mobile-Out"
	पूर्ण;
	पूर्णांक i;

	cfg = (cfg & AC_DEFCFG_LOCATION) >> AC_DEFCFG_LOCATION_SHIFT;
	अगर ((cfg & 0x0f) < 7)
		वापस bases[cfg & 0x0f];
	क्रम (i = 0; i < ARRAY_SIZE(specials_idx); i++) अणु
		अगर (cfg == specials_idx[i])
			वापस specials[i];
	पूर्ण
	वापस "UNKNOWN";
पूर्ण

/*
 * Parse the pin शेष config value and वापसs the string of the
 * jack connectivity, i.e. बाह्यal or पूर्णांकernal connection.
 */
अटल स्थिर अक्षर *get_jack_connectivity(u32 cfg)
अणु
	अटल स्थिर अक्षर * स्थिर jack_locations[4] = अणु
		"Ext", "Int", "Sep", "Oth"
	पूर्ण;

	वापस jack_locations[(cfg >> (AC_DEFCFG_LOCATION_SHIFT + 4)) & 3];
पूर्ण

/*
 * Parse the pin शेष config value and वापसs the string of the
 * jack type, i.e. the purpose of the jack, such as Line-Out or CD.
 */
अटल स्थिर अक्षर *get_jack_type(u32 cfg)
अणु
	अटल स्थिर अक्षर * स्थिर jack_types[16] = अणु
		"Line Out", "Speaker", "HP Out", "CD",
		"SPDIF Out", "Digital Out", "Modem Line", "Modem Hand",
		"Line In", "Aux", "Mic", "Telephony",
		"SPDIF In", "Digital In", "Reserved", "Other"
	पूर्ण;

	वापस jack_types[(cfg & AC_DEFCFG_DEVICE)
				>> AC_DEFCFG_DEVICE_SHIFT];
पूर्ण

अटल व्योम prपूर्णांक_pin_caps(काष्ठा snd_info_buffer *buffer,
			   काष्ठा hda_codec *codec, hda_nid_t nid,
			   पूर्णांक *supports_vref)
अणु
	अटल स्थिर अक्षर * स्थिर jack_conns[4] = अणु
		"Jack", "N/A", "Fixed", "Both"
	पूर्ण;
	अचिन्हित पूर्णांक caps, val;

	caps = param_पढ़ो(codec, nid, AC_PAR_PIN_CAP);
	snd_iम_लिखो(buffer, "  Pincap 0x%08x:", caps);
	अगर (caps & AC_PINCAP_IN)
		snd_iम_लिखो(buffer, " IN");
	अगर (caps & AC_PINCAP_OUT)
		snd_iम_लिखो(buffer, " OUT");
	अगर (caps & AC_PINCAP_HP_DRV)
		snd_iम_लिखो(buffer, " HP");
	अगर (caps & AC_PINCAP_EAPD)
		snd_iम_लिखो(buffer, " EAPD");
	अगर (caps & AC_PINCAP_PRES_DETECT)
		snd_iम_लिखो(buffer, " Detect");
	अगर (caps & AC_PINCAP_BALANCE)
		snd_iम_लिखो(buffer, " Balanced");
	अगर (caps & AC_PINCAP_HDMI) अणु
		/* Realtek uses this bit as a dअगरferent meaning */
		अगर ((codec->core.venकरोr_id >> 16) == 0x10ec)
			snd_iम_लिखो(buffer, " R/L");
		अन्यथा अणु
			अगर (caps & AC_PINCAP_HBR)
				snd_iम_लिखो(buffer, " HBR");
			snd_iम_लिखो(buffer, " HDMI");
		पूर्ण
	पूर्ण
	अगर (caps & AC_PINCAP_DP)
		snd_iम_लिखो(buffer, " DP");
	अगर (caps & AC_PINCAP_TRIG_REQ)
		snd_iम_लिखो(buffer, " Trigger");
	अगर (caps & AC_PINCAP_IMP_SENSE)
		snd_iम_लिखो(buffer, " ImpSense");
	snd_iम_लिखो(buffer, "\n");
	अगर (caps & AC_PINCAP_VREF) अणु
		अचिन्हित पूर्णांक vref =
			(caps & AC_PINCAP_VREF) >> AC_PINCAP_VREF_SHIFT;
		snd_iम_लिखो(buffer, "    Vref caps:");
		अगर (vref & AC_PINCAP_VREF_HIZ)
			snd_iम_लिखो(buffer, " HIZ");
		अगर (vref & AC_PINCAP_VREF_50)
			snd_iम_लिखो(buffer, " 50");
		अगर (vref & AC_PINCAP_VREF_GRD)
			snd_iम_लिखो(buffer, " GRD");
		अगर (vref & AC_PINCAP_VREF_80)
			snd_iम_लिखो(buffer, " 80");
		अगर (vref & AC_PINCAP_VREF_100)
			snd_iम_लिखो(buffer, " 100");
		snd_iम_लिखो(buffer, "\n");
		*supports_vref = 1;
	पूर्ण अन्यथा
		*supports_vref = 0;
	अगर (caps & AC_PINCAP_EAPD) अणु
		val = snd_hda_codec_पढ़ो(codec, nid, 0,
					 AC_VERB_GET_EAPD_BTLENABLE, 0);
		snd_iम_लिखो(buffer, "  EAPD 0x%x:", val);
		अगर (val & AC_EAPDBTL_BALANCED)
			snd_iम_लिखो(buffer, " BALANCED");
		अगर (val & AC_EAPDBTL_EAPD)
			snd_iम_लिखो(buffer, " EAPD");
		अगर (val & AC_EAPDBTL_LR_SWAP)
			snd_iम_लिखो(buffer, " R/L");
		snd_iम_लिखो(buffer, "\n");
	पूर्ण
	caps = snd_hda_codec_पढ़ो(codec, nid, 0, AC_VERB_GET_CONFIG_DEFAULT, 0);
	snd_iम_लिखो(buffer, "  Pin Default 0x%08x: [%s] %s at %s %s\n", caps,
		    jack_conns[(caps & AC_DEFCFG_PORT_CONN) >> AC_DEFCFG_PORT_CONN_SHIFT],
		    get_jack_type(caps),
		    get_jack_connectivity(caps),
		    get_jack_location(caps));
	snd_iम_लिखो(buffer, "    Conn = %s, Color = %s\n",
		    get_jack_connection(caps),
		    get_jack_color(caps));
	/* Default association and sequence values refer to शेष grouping
	 * of pin complexes and their sequence within the group. This is used
	 * क्रम priority and resource allocation.
	 */
	snd_iम_लिखो(buffer, "    DefAssociation = 0x%x, Sequence = 0x%x\n",
		    (caps & AC_DEFCFG_DEF_ASSOC) >> AC_DEFCFG_ASSOC_SHIFT,
		    caps & AC_DEFCFG_SEQUENCE);
	अगर (((caps & AC_DEFCFG_MISC) >> AC_DEFCFG_MISC_SHIFT) &
	    AC_DEFCFG_MISC_NO_PRESENCE) अणु
		/* Miscellaneous bit indicates बाह्यal hardware करोes not
		 * support presence detection even अगर the pin complex
		 * indicates it is supported.
		 */
		snd_iम_लिखो(buffer, "    Misc = NO_PRESENCE\n");
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_pin_ctls(काष्ठा snd_info_buffer *buffer,
			   काष्ठा hda_codec *codec, hda_nid_t nid,
			   पूर्णांक supports_vref)
अणु
	अचिन्हित पूर्णांक pinctls;

	pinctls = snd_hda_codec_पढ़ो(codec, nid, 0,
				     AC_VERB_GET_PIN_WIDGET_CONTROL, 0);
	snd_iम_लिखो(buffer, "  Pin-ctls: 0x%02x:", pinctls);
	अगर (pinctls & AC_PINCTL_IN_EN)
		snd_iम_लिखो(buffer, " IN");
	अगर (pinctls & AC_PINCTL_OUT_EN)
		snd_iम_लिखो(buffer, " OUT");
	अगर (pinctls & AC_PINCTL_HP_EN)
		snd_iम_लिखो(buffer, " HP");
	अगर (supports_vref) अणु
		पूर्णांक vref = pinctls & AC_PINCTL_VREFEN;
		चयन (vref) अणु
		हाल AC_PINCTL_VREF_HIZ:
			snd_iम_लिखो(buffer, " VREF_HIZ");
			अवरोध;
		हाल AC_PINCTL_VREF_50:
			snd_iम_लिखो(buffer, " VREF_50");
			अवरोध;
		हाल AC_PINCTL_VREF_GRD:
			snd_iम_लिखो(buffer, " VREF_GRD");
			अवरोध;
		हाल AC_PINCTL_VREF_80:
			snd_iम_लिखो(buffer, " VREF_80");
			अवरोध;
		हाल AC_PINCTL_VREF_100:
			snd_iम_लिखो(buffer, " VREF_100");
			अवरोध;
		पूर्ण
	पूर्ण
	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल व्योम prपूर्णांक_vol_knob(काष्ठा snd_info_buffer *buffer,
			   काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अचिन्हित पूर्णांक cap = param_पढ़ो(codec, nid, AC_PAR_VOL_KNB_CAP);
	snd_iम_लिखो(buffer, "  Volume-Knob: delta=%d, steps=%d, ",
		    (cap >> 7) & 1, cap & 0x7f);
	cap = snd_hda_codec_पढ़ो(codec, nid, 0,
				 AC_VERB_GET_VOLUME_KNOB_CONTROL, 0);
	snd_iम_लिखो(buffer, "direct=%d, val=%d\n",
		    (cap >> 7) & 1, cap & 0x7f);
पूर्ण

अटल व्योम prपूर्णांक_audio_io(काष्ठा snd_info_buffer *buffer,
			   काष्ठा hda_codec *codec, hda_nid_t nid,
			   अचिन्हित पूर्णांक wid_type)
अणु
	पूर्णांक conv = snd_hda_codec_पढ़ो(codec, nid, 0, AC_VERB_GET_CONV, 0);
	snd_iम_लिखो(buffer,
		    "  Converter: stream=%d, channel=%d\n",
		    (conv & AC_CONV_STREAM) >> AC_CONV_STREAM_SHIFT,
		    conv & AC_CONV_CHANNEL);

	अगर (wid_type == AC_WID_AUD_IN && (conv & AC_CONV_CHANNEL) == 0) अणु
		पूर्णांक sdi = snd_hda_codec_पढ़ो(codec, nid, 0,
					     AC_VERB_GET_SDI_SELECT, 0);
		snd_iम_लिखो(buffer, "  SDI-Select: %d\n",
			    sdi & AC_SDI_SELECT);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_digital_conv(काष्ठा snd_info_buffer *buffer,
			       काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अचिन्हित पूर्णांक digi1 = snd_hda_codec_पढ़ो(codec, nid, 0,
						AC_VERB_GET_DIGI_CONVERT_1, 0);
	अचिन्हित अक्षर digi2 = digi1 >> 8;
	अचिन्हित अक्षर digi3 = digi1 >> 16;

	snd_iम_लिखो(buffer, "  Digital:");
	अगर (digi1 & AC_DIG1_ENABLE)
		snd_iम_लिखो(buffer, " Enabled");
	अगर (digi1 & AC_DIG1_V)
		snd_iम_लिखो(buffer, " Validity");
	अगर (digi1 & AC_DIG1_VCFG)
		snd_iम_लिखो(buffer, " ValidityCfg");
	अगर (digi1 & AC_DIG1_EMPHASIS)
		snd_iम_लिखो(buffer, " Preemphasis");
	अगर (digi1 & AC_DIG1_COPYRIGHT)
		snd_iम_लिखो(buffer, " Non-Copyright");
	अगर (digi1 & AC_DIG1_NONAUDIO)
		snd_iम_लिखो(buffer, " Non-Audio");
	अगर (digi1 & AC_DIG1_PROFESSIONAL)
		snd_iम_लिखो(buffer, " Pro");
	अगर (digi1 & AC_DIG1_LEVEL)
		snd_iम_लिखो(buffer, " GenLevel");
	अगर (digi3 & AC_DIG3_KAE)
		snd_iम_लिखो(buffer, " KAE");
	snd_iम_लिखो(buffer, "\n");
	snd_iम_लिखो(buffer, "  Digital category: 0x%x\n",
		    digi2 & AC_DIG2_CC);
	snd_iम_लिखो(buffer, "  IEC Coding Type: 0x%x\n",
			digi3 & AC_DIG3_ICT);
पूर्ण

अटल स्थिर अक्षर *get_pwr_state(u32 state)
अणु
	अटल स्थिर अक्षर * स्थिर buf[] = अणु
		"D0", "D1", "D2", "D3", "D3cold"
	पूर्ण;
	अगर (state < ARRAY_SIZE(buf))
		वापस buf[state];
	वापस "UNKNOWN";
पूर्ण

अटल व्योम prपूर्णांक_घातer_state(काष्ठा snd_info_buffer *buffer,
			      काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अटल स्थिर अक्षर * स्थिर names[] = अणु
		[ilog2(AC_PWRST_D0SUP)]		= "D0",
		[ilog2(AC_PWRST_D1SUP)]		= "D1",
		[ilog2(AC_PWRST_D2SUP)]		= "D2",
		[ilog2(AC_PWRST_D3SUP)]		= "D3",
		[ilog2(AC_PWRST_D3COLDSUP)]	= "D3cold",
		[ilog2(AC_PWRST_S3D3COLDSUP)]	= "S3D3cold",
		[ilog2(AC_PWRST_CLKSTOP)]	= "CLKSTOP",
		[ilog2(AC_PWRST_EPSS)]		= "EPSS",
	पूर्ण;

	पूर्णांक sup = param_पढ़ो(codec, nid, AC_PAR_POWER_STATE);
	पूर्णांक pwr = snd_hda_codec_पढ़ो(codec, nid, 0,
				     AC_VERB_GET_POWER_STATE, 0);
	अगर (sup != -1) अणु
		पूर्णांक i;

		snd_iम_लिखो(buffer, "  Power states: ");
		क्रम (i = 0; i < ARRAY_SIZE(names); i++) अणु
			अगर (sup & (1U << i))
				snd_iम_लिखो(buffer, " %s", names[i]);
		पूर्ण
		snd_iम_लिखो(buffer, "\n");
	पूर्ण

	snd_iम_लिखो(buffer, "  Power: setting=%s, actual=%s",
		    get_pwr_state(pwr & AC_PWRST_SETTING),
		    get_pwr_state((pwr & AC_PWRST_ACTUAL) >>
				  AC_PWRST_ACTUAL_SHIFT));
	अगर (pwr & AC_PWRST_ERROR)
		snd_iम_लिखो(buffer, ", Error");
	अगर (pwr & AC_PWRST_CLK_STOP_OK)
		snd_iम_लिखो(buffer, ", Clock-stop-OK");
	अगर (pwr & AC_PWRST_SETTING_RESET)
		snd_iम_लिखो(buffer, ", Setting-reset");
	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल व्योम prपूर्णांक_unsol_cap(काष्ठा snd_info_buffer *buffer,
			      काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	पूर्णांक unsol = snd_hda_codec_पढ़ो(codec, nid, 0,
				       AC_VERB_GET_UNSOLICITED_RESPONSE, 0);
	snd_iम_लिखो(buffer,
		    "  Unsolicited: tag=%02x, enabled=%d\n",
		    unsol & AC_UNSOL_TAG,
		    (unsol & AC_UNSOL_ENABLED) ? 1 : 0);
पूर्ण

अटल अंतरभूत bool can_dump_coef(काष्ठा hda_codec *codec)
अणु
	चयन (dump_coef) अणु
	हाल 0: वापस false;
	हाल 1: वापस true;
	शेष: वापस codec->dump_coef;
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_proc_caps(काष्ठा snd_info_buffer *buffer,
			    काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अचिन्हित पूर्णांक i, ncoeff, oldindex;
	अचिन्हित पूर्णांक proc_caps = param_पढ़ो(codec, nid, AC_PAR_PROC_CAP);
	ncoeff = (proc_caps & AC_PCAP_NUM_COEF) >> AC_PCAP_NUM_COEF_SHIFT;
	snd_iम_लिखो(buffer, "  Processing caps: benign=%d, ncoeff=%d\n",
		    proc_caps & AC_PCAP_BENIGN, ncoeff);

	अगर (!can_dump_coef(codec))
		वापस;

	/* Note: This is racy - another process could run in parallel and change
	   the coef index too. */
	oldindex = snd_hda_codec_पढ़ो(codec, nid, 0, AC_VERB_GET_COEF_INDEX, 0);
	क्रम (i = 0; i < ncoeff; i++) अणु
		अचिन्हित पूर्णांक val;
		snd_hda_codec_ग_लिखो(codec, nid, 0, AC_VERB_SET_COEF_INDEX, i);
		val = snd_hda_codec_पढ़ो(codec, nid, 0, AC_VERB_GET_PROC_COEF,
					 0);
		snd_iम_लिखो(buffer, "    Coeff 0x%02x: 0x%04x\n", i, val);
	पूर्ण
	snd_hda_codec_ग_लिखो(codec, nid, 0, AC_VERB_SET_COEF_INDEX, oldindex);
पूर्ण

अटल व्योम prपूर्णांक_conn_list(काष्ठा snd_info_buffer *buffer,
			    काष्ठा hda_codec *codec, hda_nid_t nid,
			    अचिन्हित पूर्णांक wid_type, hda_nid_t *conn,
			    पूर्णांक conn_len)
अणु
	पूर्णांक c, curr = -1;
	स्थिर hda_nid_t *list;
	पूर्णांक cache_len;

	अगर (conn_len > 1 &&
	    wid_type != AC_WID_AUD_MIX &&
	    wid_type != AC_WID_VOL_KNB &&
	    wid_type != AC_WID_POWER)
		curr = snd_hda_codec_पढ़ो(codec, nid, 0,
					  AC_VERB_GET_CONNECT_SEL, 0);
	snd_iम_लिखो(buffer, "  Connection: %d\n", conn_len);
	अगर (conn_len > 0) अणु
		snd_iम_लिखो(buffer, "    ");
		क्रम (c = 0; c < conn_len; c++) अणु
			snd_iम_लिखो(buffer, " 0x%02x", conn[c]);
			अगर (c == curr)
				snd_iम_लिखो(buffer, "*");
		पूर्ण
		snd_iम_लिखो(buffer, "\n");
	पूर्ण

	/* Get Cache connections info */
	cache_len = snd_hda_get_conn_list(codec, nid, &list);
	अगर (cache_len >= 0 && (cache_len != conn_len ||
			      स_भेद(list, conn, conn_len) != 0)) अणु
		snd_iम_लिखो(buffer, "  In-driver Connection: %d\n", cache_len);
		अगर (cache_len > 0) अणु
			snd_iम_लिखो(buffer, "    ");
			क्रम (c = 0; c < cache_len; c++)
				snd_iम_लिखो(buffer, " 0x%02x", list[c]);
			snd_iम_लिखो(buffer, "\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_gpio(काष्ठा snd_info_buffer *buffer,
		       काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	अचिन्हित पूर्णांक gpio =
		param_पढ़ो(codec, codec->core.afg, AC_PAR_GPIO_CAP);
	अचिन्हित पूर्णांक enable, direction, wake, unsol, sticky, data;
	पूर्णांक i, max;
	snd_iम_लिखो(buffer, "GPIO: io=%d, o=%d, i=%d, "
		    "unsolicited=%d, wake=%d\n",
		    gpio & AC_GPIO_IO_COUNT,
		    (gpio & AC_GPIO_O_COUNT) >> AC_GPIO_O_COUNT_SHIFT,
		    (gpio & AC_GPIO_I_COUNT) >> AC_GPIO_I_COUNT_SHIFT,
		    (gpio & AC_GPIO_UNSOLICITED) ? 1 : 0,
		    (gpio & AC_GPIO_WAKE) ? 1 : 0);
	max = gpio & AC_GPIO_IO_COUNT;
	अगर (!max || max > 8)
		वापस;
	enable = snd_hda_codec_पढ़ो(codec, nid, 0,
				    AC_VERB_GET_GPIO_MASK, 0);
	direction = snd_hda_codec_पढ़ो(codec, nid, 0,
				       AC_VERB_GET_GPIO_सूचीECTION, 0);
	wake = snd_hda_codec_पढ़ो(codec, nid, 0,
				  AC_VERB_GET_GPIO_WAKE_MASK, 0);
	unsol  = snd_hda_codec_पढ़ो(codec, nid, 0,
				    AC_VERB_GET_GPIO_UNSOLICITED_RSP_MASK, 0);
	sticky = snd_hda_codec_पढ़ो(codec, nid, 0,
				    AC_VERB_GET_GPIO_STICKY_MASK, 0);
	data = snd_hda_codec_पढ़ो(codec, nid, 0,
				  AC_VERB_GET_GPIO_DATA, 0);
	क्रम (i = 0; i < max; ++i)
		snd_iम_लिखो(buffer,
			    "  IO[%d]: enable=%d, dir=%d, wake=%d, "
			    "sticky=%d, data=%d, unsol=%d\n", i,
			    (enable & (1<<i)) ? 1 : 0,
			    (direction & (1<<i)) ? 1 : 0,
			    (wake & (1<<i)) ? 1 : 0,
			    (sticky & (1<<i)) ? 1 : 0,
			    (data & (1<<i)) ? 1 : 0,
			    (unsol & (1<<i)) ? 1 : 0);
	/* FIXME: add GPO and GPI pin inक्रमmation */
	prपूर्णांक_nid_array(buffer, codec, nid, &codec->mixers);
	prपूर्णांक_nid_array(buffer, codec, nid, &codec->nids);
पूर्ण

अटल व्योम prपूर्णांक_dpmst_connections(काष्ठा snd_info_buffer *buffer, काष्ठा hda_codec *codec,
				    hda_nid_t nid, पूर्णांक dev_num)
अणु
	पूर्णांक c, conn_len, curr, dev_id_saved;
	hda_nid_t *conn;

	conn_len = snd_hda_get_num_raw_conns(codec, nid);
	अगर (conn_len <= 0)
		वापस;

	conn = kदो_स्मृति_array(conn_len, माप(hda_nid_t), GFP_KERNEL);
	अगर (!conn)
		वापस;

	dev_id_saved = snd_hda_get_dev_select(codec, nid);

	snd_hda_set_dev_select(codec, nid, dev_num);
	curr = snd_hda_codec_पढ़ो(codec, nid, 0, AC_VERB_GET_CONNECT_SEL, 0);
	अगर (snd_hda_get_raw_connections(codec, nid, conn, conn_len) < 0)
		जाओ out;

	क्रम (c = 0; c < conn_len; c++) अणु
		snd_iम_लिखो(buffer, " 0x%02x", conn[c]);
		अगर (c == curr)
			snd_iम_लिखो(buffer, "*");
	पूर्ण

out:
	kमुक्त(conn);
	snd_hda_set_dev_select(codec, nid, dev_id_saved);
पूर्ण

अटल व्योम prपूर्णांक_device_list(काष्ठा snd_info_buffer *buffer,
			    काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	पूर्णांक i, curr = -1;
	u8 dev_list[AC_MAX_DEV_LIST_LEN];
	पूर्णांक devlist_len;

	devlist_len = snd_hda_get_devices(codec, nid, dev_list,
					AC_MAX_DEV_LIST_LEN);
	snd_iम_लिखो(buffer, "  Devices: %d\n", devlist_len);
	अगर (devlist_len <= 0)
		वापस;

	curr = snd_hda_codec_पढ़ो(codec, nid, 0,
				AC_VERB_GET_DEVICE_SEL, 0);

	क्रम (i = 0; i < devlist_len; i++) अणु
		अगर (i == curr)
			snd_iम_लिखो(buffer, "    *");
		अन्यथा
			snd_iम_लिखो(buffer, "     ");

		snd_iम_लिखो(buffer,
			"Dev %02d: PD = %d, ELDV = %d, IA = %d, Connections [", i,
			!!(dev_list[i] & AC_DE_PD),
			!!(dev_list[i] & AC_DE_ELDV),
			!!(dev_list[i] & AC_DE_IA));

		prपूर्णांक_dpmst_connections(buffer, codec, nid, i);

		snd_iम_लिखो(buffer, " ]\n");
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_codec_core_info(काष्ठा hdac_device *codec,
				  काष्ठा snd_info_buffer *buffer)
अणु
	snd_iम_लिखो(buffer, "Codec: ");
	अगर (codec->venकरोr_name && codec->chip_name)
		snd_iम_लिखो(buffer, "%s %s\n",
			    codec->venकरोr_name, codec->chip_name);
	अन्यथा
		snd_iम_लिखो(buffer, "Not Set\n");
	snd_iम_लिखो(buffer, "Address: %d\n", codec->addr);
	अगर (codec->afg)
		snd_iम_लिखो(buffer, "AFG Function Id: 0x%x (unsol %u)\n",
			codec->afg_function_id, codec->afg_unsol);
	अगर (codec->mfg)
		snd_iम_लिखो(buffer, "MFG Function Id: 0x%x (unsol %u)\n",
			codec->mfg_function_id, codec->mfg_unsol);
	snd_iम_लिखो(buffer, "Vendor Id: 0x%08x\n", codec->venकरोr_id);
	snd_iम_लिखो(buffer, "Subsystem Id: 0x%08x\n", codec->subप्रणाली_id);
	snd_iम_लिखो(buffer, "Revision Id: 0x%x\n", codec->revision_id);

	अगर (codec->mfg)
		snd_iम_लिखो(buffer, "Modem Function Group: 0x%x\n", codec->mfg);
	अन्यथा
		snd_iम_लिखो(buffer, "No Modem Function Group found\n");
पूर्ण

अटल व्योम prपूर्णांक_codec_info(काष्ठा snd_info_entry *entry,
			     काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा hda_codec *codec = entry->निजी_data;
	hda_nid_t nid, fg;
	पूर्णांक i, nodes;

	prपूर्णांक_codec_core_info(&codec->core, buffer);
	fg = codec->core.afg;
	अगर (!fg)
		वापस;
	snd_hda_घातer_up(codec);
	snd_iम_लिखो(buffer, "Default PCM:\n");
	prपूर्णांक_pcm_caps(buffer, codec, fg);
	snd_iम_लिखो(buffer, "Default Amp-In caps: ");
	prपूर्णांक_amp_caps(buffer, codec, fg, HDA_INPUT);
	snd_iम_लिखो(buffer, "Default Amp-Out caps: ");
	prपूर्णांक_amp_caps(buffer, codec, fg, HDA_OUTPUT);
	snd_iम_लिखो(buffer, "State of AFG node 0x%02x:\n", fg);
	prपूर्णांक_घातer_state(buffer, codec, fg);

	nodes = snd_hda_get_sub_nodes(codec, fg, &nid);
	अगर (! nid || nodes < 0) अणु
		snd_iम_लिखो(buffer, "Invalid AFG subtree\n");
		snd_hda_घातer_करोwn(codec);
		वापस;
	पूर्ण

	prपूर्णांक_gpio(buffer, codec, fg);
	अगर (codec->proc_widget_hook)
		codec->proc_widget_hook(buffer, codec, fg);

	क्रम (i = 0; i < nodes; i++, nid++) अणु
		अचिन्हित पूर्णांक wid_caps =
			param_पढ़ो(codec, nid, AC_PAR_AUDIO_WIDGET_CAP);
		अचिन्हित पूर्णांक wid_type = get_wcaps_type(wid_caps);
		hda_nid_t *conn = शून्य;
		पूर्णांक conn_len = 0;

		snd_iम_लिखो(buffer, "Node 0x%02x [%s] wcaps 0x%x:", nid,
			    get_wid_type_name(wid_type), wid_caps);
		अगर (wid_caps & AC_WCAP_STEREO) अणु
			अचिन्हित पूर्णांक chans = get_wcaps_channels(wid_caps);
			अगर (chans == 2)
				snd_iम_लिखो(buffer, " Stereo");
			अन्यथा
				snd_iम_लिखो(buffer, " %d-Channels", chans);
		पूर्ण अन्यथा
			snd_iम_लिखो(buffer, " Mono");
		अगर (wid_caps & AC_WCAP_DIGITAL)
			snd_iम_लिखो(buffer, " Digital");
		अगर (wid_caps & AC_WCAP_IN_AMP)
			snd_iम_लिखो(buffer, " Amp-In");
		अगर (wid_caps & AC_WCAP_OUT_AMP)
			snd_iम_लिखो(buffer, " Amp-Out");
		अगर (wid_caps & AC_WCAP_STRIPE)
			snd_iम_लिखो(buffer, " Stripe");
		अगर (wid_caps & AC_WCAP_LR_SWAP)
			snd_iम_लिखो(buffer, " R/L");
		अगर (wid_caps & AC_WCAP_CP_CAPS)
			snd_iम_लिखो(buffer, " CP");
		snd_iम_लिखो(buffer, "\n");

		prपूर्णांक_nid_array(buffer, codec, nid, &codec->mixers);
		prपूर्णांक_nid_array(buffer, codec, nid, &codec->nids);
		prपूर्णांक_nid_pcms(buffer, codec, nid);

		/* volume knob is a special widget that always have connection
		 * list
		 */
		अगर (wid_type == AC_WID_VOL_KNB)
			wid_caps |= AC_WCAP_CONN_LIST;

		अगर (wid_caps & AC_WCAP_CONN_LIST) अणु
			conn_len = snd_hda_get_num_raw_conns(codec, nid);
			अगर (conn_len > 0) अणु
				conn = kदो_स्मृति_array(conn_len,
						     माप(hda_nid_t),
						     GFP_KERNEL);
				अगर (!conn)
					वापस;
				अगर (snd_hda_get_raw_connections(codec, nid, conn,
								conn_len) < 0)
					conn_len = 0;
			पूर्ण
		पूर्ण

		अगर (wid_caps & AC_WCAP_IN_AMP) अणु
			snd_iम_लिखो(buffer, "  Amp-In caps: ");
			prपूर्णांक_amp_caps(buffer, codec, nid, HDA_INPUT);
			snd_iम_लिखो(buffer, "  Amp-In vals: ");
			अगर (wid_type == AC_WID_PIN ||
			    (codec->single_adc_amp &&
			     wid_type == AC_WID_AUD_IN))
				prपूर्णांक_amp_vals(buffer, codec, nid, HDA_INPUT,
					       wid_caps, 1);
			अन्यथा
				prपूर्णांक_amp_vals(buffer, codec, nid, HDA_INPUT,
					       wid_caps, conn_len);
		पूर्ण
		अगर (wid_caps & AC_WCAP_OUT_AMP) अणु
			snd_iम_लिखो(buffer, "  Amp-Out caps: ");
			prपूर्णांक_amp_caps(buffer, codec, nid, HDA_OUTPUT);
			snd_iम_लिखो(buffer, "  Amp-Out vals: ");
			अगर (wid_type == AC_WID_PIN &&
			    codec->pin_amp_workaround)
				prपूर्णांक_amp_vals(buffer, codec, nid, HDA_OUTPUT,
					       wid_caps, conn_len);
			अन्यथा
				prपूर्णांक_amp_vals(buffer, codec, nid, HDA_OUTPUT,
					       wid_caps, 1);
		पूर्ण

		चयन (wid_type) अणु
		हाल AC_WID_PIN: अणु
			पूर्णांक supports_vref;
			prपूर्णांक_pin_caps(buffer, codec, nid, &supports_vref);
			prपूर्णांक_pin_ctls(buffer, codec, nid, supports_vref);
			अवरोध;
		पूर्ण
		हाल AC_WID_VOL_KNB:
			prपूर्णांक_vol_knob(buffer, codec, nid);
			अवरोध;
		हाल AC_WID_AUD_OUT:
		हाल AC_WID_AUD_IN:
			prपूर्णांक_audio_io(buffer, codec, nid, wid_type);
			अगर (wid_caps & AC_WCAP_DIGITAL)
				prपूर्णांक_digital_conv(buffer, codec, nid);
			अगर (wid_caps & AC_WCAP_FORMAT_OVRD) अणु
				snd_iम_लिखो(buffer, "  PCM:\n");
				prपूर्णांक_pcm_caps(buffer, codec, nid);
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (wid_caps & AC_WCAP_UNSOL_CAP)
			prपूर्णांक_unsol_cap(buffer, codec, nid);

		अगर (wid_caps & AC_WCAP_POWER)
			prपूर्णांक_घातer_state(buffer, codec, nid);

		अगर (wid_caps & AC_WCAP_DELAY)
			snd_iम_लिखो(buffer, "  Delay: %d samples\n",
				    (wid_caps & AC_WCAP_DELAY) >>
				    AC_WCAP_DELAY_SHIFT);

		अगर (wid_type == AC_WID_PIN && codec->dp_mst)
			prपूर्णांक_device_list(buffer, codec, nid);

		अगर (wid_caps & AC_WCAP_CONN_LIST)
			prपूर्णांक_conn_list(buffer, codec, nid, wid_type,
					conn, conn_len);

		अगर (wid_caps & AC_WCAP_PROC_WID)
			prपूर्णांक_proc_caps(buffer, codec, nid);

		अगर (codec->proc_widget_hook)
			codec->proc_widget_hook(buffer, codec, nid);

		kमुक्त(conn);
	पूर्ण
	snd_hda_घातer_करोwn(codec);
पूर्ण

/*
 * create a proc पढ़ो
 */
पूर्णांक snd_hda_codec_proc_new(काष्ठा hda_codec *codec)
अणु
	अक्षर name[32];

	snम_लिखो(name, माप(name), "codec#%d", codec->core.addr);
	वापस snd_card_ro_proc_new(codec->card, name, codec, prपूर्णांक_codec_info);
पूर्ण

