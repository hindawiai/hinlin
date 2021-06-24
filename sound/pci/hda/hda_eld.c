<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Generic routines and proc पूर्णांकerface क्रम ELD(EDID Like Data) inक्रमmation
 *
 * Copyright(c) 2008 Intel Corporation.
 * Copyright (c) 2013 Anssi Hannula <anssi.hannula@iki.fi>
 *
 * Authors:
 * 		Wu Fengguang <wfg@linux.पूर्णांकel.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <sound/hda_chmap.h>
#समावेश <sound/hda_codec.h>
#समावेश "hda_local.h"

क्रमागत eld_versions अणु
	ELD_VER_CEA_861D	= 2,
	ELD_VER_PARTIAL		= 31,
पूर्ण;

क्रमागत cea_edid_versions अणु
	CEA_EDID_VER_NONE	= 0,
	CEA_EDID_VER_CEA861	= 1,
	CEA_EDID_VER_CEA861A	= 2,
	CEA_EDID_VER_CEA861BCD	= 3,
	CEA_EDID_VER_RESERVED	= 4,
पूर्ण;

अटल स्थिर अक्षर * स्थिर eld_connection_type_names[4] = अणु
	"HDMI",
	"DisplayPort",
	"2-reserved",
	"3-reserved"
पूर्ण;

क्रमागत cea_audio_coding_types अणु
	AUDIO_CODING_TYPE_REF_STREAM_HEADER	=  0,
	AUDIO_CODING_TYPE_LPCM			=  1,
	AUDIO_CODING_TYPE_AC3			=  2,
	AUDIO_CODING_TYPE_MPEG1			=  3,
	AUDIO_CODING_TYPE_MP3			=  4,
	AUDIO_CODING_TYPE_MPEG2			=  5,
	AUDIO_CODING_TYPE_AACLC			=  6,
	AUDIO_CODING_TYPE_DTS			=  7,
	AUDIO_CODING_TYPE_ATRAC			=  8,
	AUDIO_CODING_TYPE_SACD			=  9,
	AUDIO_CODING_TYPE_EAC3			= 10,
	AUDIO_CODING_TYPE_DTS_HD		= 11,
	AUDIO_CODING_TYPE_MLP			= 12,
	AUDIO_CODING_TYPE_DST			= 13,
	AUDIO_CODING_TYPE_WMAPRO		= 14,
	AUDIO_CODING_TYPE_REF_CXT		= 15,
	/* also include valid xtypes below */
	AUDIO_CODING_TYPE_HE_AAC		= 15,
	AUDIO_CODING_TYPE_HE_AAC2		= 16,
	AUDIO_CODING_TYPE_MPEG_SURROUND		= 17,
पूर्ण;

क्रमागत cea_audio_coding_xtypes अणु
	AUDIO_CODING_XTYPE_HE_REF_CT		= 0,
	AUDIO_CODING_XTYPE_HE_AAC		= 1,
	AUDIO_CODING_XTYPE_HE_AAC2		= 2,
	AUDIO_CODING_XTYPE_MPEG_SURROUND	= 3,
	AUDIO_CODING_XTYPE_FIRST_RESERVED	= 4,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cea_audio_coding_type_names[] = अणु
	/*  0 */ "undefined",
	/*  1 */ "LPCM",
	/*  2 */ "AC-3",
	/*  3 */ "MPEG1",
	/*  4 */ "MP3",
	/*  5 */ "MPEG2",
	/*  6 */ "AAC-LC",
	/*  7 */ "DTS",
	/*  8 */ "ATRAC",
	/*  9 */ "DSD (One Bit Audio)",
	/* 10 */ "E-AC-3/DD+ (Dolby Digital Plus)",
	/* 11 */ "DTS-HD",
	/* 12 */ "MLP (Dolby TrueHD)",
	/* 13 */ "DST",
	/* 14 */ "WMAPro",
	/* 15 */ "HE-AAC",
	/* 16 */ "HE-AACv2",
	/* 17 */ "MPEG Surround",
पूर्ण;

/*
 * The following two lists are shared between
 * 	- HDMI audio InfoFrame (source to sink)
 * 	- CEA E-EDID Extension (sink to source)
 */

/*
 * SS1:SS0 index => sample size
 */
अटल स्थिर पूर्णांक cea_sample_sizes[4] = अणु
	0,	 		/* 0: Refer to Stream Header */
	AC_SUPPCM_BITS_16,	/* 1: 16 bits */
	AC_SUPPCM_BITS_20,	/* 2: 20 bits */
	AC_SUPPCM_BITS_24,	/* 3: 24 bits */
पूर्ण;

/*
 * SF2:SF1:SF0 index => sampling frequency
 */
अटल स्थिर पूर्णांक cea_sampling_frequencies[8] = अणु
	0,			/* 0: Refer to Stream Header */
	SNDRV_PCM_RATE_32000,	/* 1:  32000Hz */
	SNDRV_PCM_RATE_44100,	/* 2:  44100Hz */
	SNDRV_PCM_RATE_48000,	/* 3:  48000Hz */
	SNDRV_PCM_RATE_88200,	/* 4:  88200Hz */
	SNDRV_PCM_RATE_96000,	/* 5:  96000Hz */
	SNDRV_PCM_RATE_176400,	/* 6: 176400Hz */
	SNDRV_PCM_RATE_192000,	/* 7: 192000Hz */
पूर्ण;

अटल अचिन्हित पूर्णांक hdmi_get_eld_data(काष्ठा hda_codec *codec, hda_nid_t nid,
					पूर्णांक byte_index)
अणु
	अचिन्हित पूर्णांक val;

	val = snd_hda_codec_पढ़ो(codec, nid, 0,
					AC_VERB_GET_HDMI_ELDD, byte_index);
#अगर_घोषित BE_PARANOID
	codec_info(codec, "HDMI: ELD data byte %d: 0x%x\n", byte_index, val);
#पूर्ण_अगर
	वापस val;
पूर्ण

#घोषणा GRAB_BITS(buf, byte, lowbit, bits) 		\
(अणु							\
	BUILD_BUG_ON(lowbit > 7);			\
	BUILD_BUG_ON(bits > 8);				\
	BUILD_BUG_ON(bits <= 0);			\
							\
	(buf[byte] >> (lowbit)) & ((1 << (bits)) - 1);	\
पूर्ण)

अटल व्योम hdmi_update_लघु_audio_desc(काष्ठा hda_codec *codec,
					 काष्ठा cea_sad *a,
					 स्थिर अचिन्हित अक्षर *buf)
अणु
	पूर्णांक i;
	पूर्णांक val;

	val = GRAB_BITS(buf, 1, 0, 7);
	a->rates = 0;
	क्रम (i = 0; i < 7; i++)
		अगर (val & (1 << i))
			a->rates |= cea_sampling_frequencies[i + 1];

	a->channels = GRAB_BITS(buf, 0, 0, 3);
	a->channels++;

	a->sample_bits = 0;
	a->max_bitrate = 0;

	a->क्रमmat = GRAB_BITS(buf, 0, 3, 4);
	चयन (a->क्रमmat) अणु
	हाल AUDIO_CODING_TYPE_REF_STREAM_HEADER:
		codec_info(codec, "HDMI: audio coding type 0 not expected\n");
		अवरोध;

	हाल AUDIO_CODING_TYPE_LPCM:
		val = GRAB_BITS(buf, 2, 0, 3);
		क्रम (i = 0; i < 3; i++)
			अगर (val & (1 << i))
				a->sample_bits |= cea_sample_sizes[i + 1];
		अवरोध;

	हाल AUDIO_CODING_TYPE_AC3:
	हाल AUDIO_CODING_TYPE_MPEG1:
	हाल AUDIO_CODING_TYPE_MP3:
	हाल AUDIO_CODING_TYPE_MPEG2:
	हाल AUDIO_CODING_TYPE_AACLC:
	हाल AUDIO_CODING_TYPE_DTS:
	हाल AUDIO_CODING_TYPE_ATRAC:
		a->max_bitrate = GRAB_BITS(buf, 2, 0, 8);
		a->max_bitrate *= 8000;
		अवरोध;

	हाल AUDIO_CODING_TYPE_SACD:
		अवरोध;

	हाल AUDIO_CODING_TYPE_EAC3:
		अवरोध;

	हाल AUDIO_CODING_TYPE_DTS_HD:
		अवरोध;

	हाल AUDIO_CODING_TYPE_MLP:
		अवरोध;

	हाल AUDIO_CODING_TYPE_DST:
		अवरोध;

	हाल AUDIO_CODING_TYPE_WMAPRO:
		a->profile = GRAB_BITS(buf, 2, 0, 3);
		अवरोध;

	हाल AUDIO_CODING_TYPE_REF_CXT:
		a->क्रमmat = GRAB_BITS(buf, 2, 3, 5);
		अगर (a->क्रमmat == AUDIO_CODING_XTYPE_HE_REF_CT ||
		    a->क्रमmat >= AUDIO_CODING_XTYPE_FIRST_RESERVED) अणु
			codec_info(codec,
				   "HDMI: audio coding xtype %d not expected\n",
				   a->क्रमmat);
			a->क्रमmat = 0;
		पूर्ण अन्यथा
			a->क्रमmat += AUDIO_CODING_TYPE_HE_AAC -
				     AUDIO_CODING_XTYPE_HE_AAC;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Be careful, ELD buf could be totally rubbish!
 */
पूर्णांक snd_hdmi_parse_eld(काष्ठा hda_codec *codec, काष्ठा parsed_hdmi_eld *e,
			  स्थिर अचिन्हित अक्षर *buf, पूर्णांक size)
अणु
	पूर्णांक mnl;
	पूर्णांक i;

	स_रखो(e, 0, माप(*e));
	e->eld_ver = GRAB_BITS(buf, 0, 3, 5);
	अगर (e->eld_ver != ELD_VER_CEA_861D &&
	    e->eld_ver != ELD_VER_PARTIAL) अणु
		codec_info(codec, "HDMI: Unknown ELD version %d\n", e->eld_ver);
		जाओ out_fail;
	पूर्ण

	e->baseline_len = GRAB_BITS(buf, 2, 0, 8);
	mnl		= GRAB_BITS(buf, 4, 0, 5);
	e->cea_edid_ver	= GRAB_BITS(buf, 4, 5, 3);

	e->support_hdcp	= GRAB_BITS(buf, 5, 0, 1);
	e->support_ai	= GRAB_BITS(buf, 5, 1, 1);
	e->conn_type	= GRAB_BITS(buf, 5, 2, 2);
	e->sad_count	= GRAB_BITS(buf, 5, 4, 4);

	e->aud_synch_delay = GRAB_BITS(buf, 6, 0, 8) * 2;
	e->spk_alloc	= GRAB_BITS(buf, 7, 0, 7);

	e->port_id	  = get_unaligned_le64(buf + 8);

	/* not specअगरied, but the spec's tendency is little endian */
	e->manufacture_id = get_unaligned_le16(buf + 16);
	e->product_id	  = get_unaligned_le16(buf + 18);

	अगर (mnl > ELD_MAX_MNL) अणु
		codec_info(codec, "HDMI: MNL is reserved value %d\n", mnl);
		जाओ out_fail;
	पूर्ण अन्यथा अगर (ELD_FIXED_BYTES + mnl > size) अणु
		codec_info(codec, "HDMI: out of range MNL %d\n", mnl);
		जाओ out_fail;
	पूर्ण अन्यथा
		strscpy(e->monitor_name, buf + ELD_FIXED_BYTES, mnl + 1);

	क्रम (i = 0; i < e->sad_count; i++) अणु
		अगर (ELD_FIXED_BYTES + mnl + 3 * (i + 1) > size) अणु
			codec_info(codec, "HDMI: out of range SAD %d\n", i);
			जाओ out_fail;
		पूर्ण
		hdmi_update_लघु_audio_desc(codec, e->sad + i,
					buf + ELD_FIXED_BYTES + mnl + 3 * i);
	पूर्ण

	/*
	 * HDMI sink's ELD info cannot always be retrieved क्रम now, e.g.
	 * in console or क्रम audio devices. Assume the highest speakers
	 * configuration, to _not_ prohibit multi-channel audio playback.
	 */
	अगर (!e->spk_alloc)
		e->spk_alloc = 0xffff;

	वापस 0;

out_fail:
	वापस -EINVAL;
पूर्ण

पूर्णांक snd_hdmi_get_eld_size(काष्ठा hda_codec *codec, hda_nid_t nid)
अणु
	वापस snd_hda_codec_पढ़ो(codec, nid, 0, AC_VERB_GET_HDMI_DIP_SIZE,
						 AC_DIPSIZE_ELD_BUF);
पूर्ण

पूर्णांक snd_hdmi_get_eld(काष्ठा hda_codec *codec, hda_nid_t nid,
		     अचिन्हित अक्षर *buf, पूर्णांक *eld_size)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	पूर्णांक size;

	/*
	 * ELD size is initialized to zero in caller function. If no errors and
	 * ELD is valid, actual eld_size is asचिन्हित.
	 */

	size = snd_hdmi_get_eld_size(codec, nid);
	अगर (size == 0) अणु
		/* wfg: workaround क्रम ASUS P5E-VM HDMI board */
		codec_info(codec, "HDMI: ELD buf size is 0, force 128\n");
		size = 128;
	पूर्ण
	अगर (size < ELD_FIXED_BYTES || size > ELD_MAX_SIZE) अणु
		codec_info(codec, "HDMI: invalid ELD buf size %d\n", size);
		वापस -दुस्फल;
	पूर्ण

	/* set ELD buffer */
	क्रम (i = 0; i < size; i++) अणु
		अचिन्हित पूर्णांक val = hdmi_get_eld_data(codec, nid, i);
		/*
		 * Graphics driver might be writing to ELD buffer right now.
		 * Just पात. The caller will repoll after a जबतक.
		 */
		अगर (!(val & AC_ELDD_ELD_VALID)) अणु
			codec_info(codec, "HDMI: invalid ELD data byte %d\n", i);
			ret = -EINVAL;
			जाओ error;
		पूर्ण
		val &= AC_ELDD_ELD_DATA;
		/*
		 * The first byte cannot be zero. This can happen on some DVI
		 * connections. Some Intel chips may also need some 250ms delay
		 * to वापस non-zero ELD data, even when the graphics driver
		 * correctly ग_लिखोs ELD content beक्रमe setting ELD_valid bit.
		 */
		अगर (!val && !i) अणु
			codec_dbg(codec, "HDMI: 0 ELD data\n");
			ret = -EINVAL;
			जाओ error;
		पूर्ण
		buf[i] = val;
	पूर्ण

	*eld_size = size;
error:
	वापस ret;
पूर्ण

/*
 * SNDRV_PCM_RATE_* and AC_PAR_PCM values करोn't match, prपूर्णांक correct rates with
 * hdmi-specअगरic routine.
 */
अटल व्योम hdmi_prपूर्णांक_pcm_rates(पूर्णांक pcm, अक्षर *buf, पूर्णांक buflen)
अणु
	अटल स्थिर अचिन्हित पूर्णांक alsa_rates[] = अणु
		5512, 8000, 11025, 16000, 22050, 32000, 44100, 48000, 64000,
		88200, 96000, 176400, 192000, 384000
	पूर्ण;
	पूर्णांक i, j;

	क्रम (i = 0, j = 0; i < ARRAY_SIZE(alsa_rates); i++)
		अगर (pcm & (1 << i))
			j += scnम_लिखो(buf + j, buflen - j,  " %d",
				alsa_rates[i]);

	buf[j] = '\0'; /* necessary when j == 0 */
पूर्ण

#घोषणा SND_PRINT_RATES_ADVISED_बफ_मानE	80

अटल व्योम hdmi_show_लघु_audio_desc(काष्ठा hda_codec *codec,
				       काष्ठा cea_sad *a)
अणु
	अक्षर buf[SND_PRINT_RATES_ADVISED_बफ_मानE];
	अक्षर buf2[8 + SND_PRINT_BITS_ADVISED_बफ_मानE] = ", bits =";

	अगर (!a->क्रमmat)
		वापस;

	hdmi_prपूर्णांक_pcm_rates(a->rates, buf, माप(buf));

	अगर (a->क्रमmat == AUDIO_CODING_TYPE_LPCM)
		snd_prपूर्णांक_pcm_bits(a->sample_bits, buf2 + 8, माप(buf2) - 8);
	अन्यथा अगर (a->max_bitrate)
		snम_लिखो(buf2, माप(buf2),
				", max bitrate = %d", a->max_bitrate);
	अन्यथा
		buf2[0] = '\0';

	codec_dbg(codec,
		  "HDMI: supports coding type %s: channels = %d, rates =%s%s\n",
		  cea_audio_coding_type_names[a->क्रमmat],
		  a->channels, buf, buf2);
पूर्ण

व्योम snd_hdmi_show_eld(काष्ठा hda_codec *codec, काष्ठा parsed_hdmi_eld *e)
अणु
	पूर्णांक i;

	codec_dbg(codec, "HDMI: detected monitor %s at connection type %s\n",
			e->monitor_name,
			eld_connection_type_names[e->conn_type]);

	अगर (e->spk_alloc) अणु
		अक्षर buf[SND_PRINT_CHANNEL_ALLOCATION_ADVISED_बफ_मानE];
		snd_hdac_prपूर्णांक_channel_allocation(e->spk_alloc, buf, माप(buf));
		codec_dbg(codec, "HDMI: available speakers:%s\n", buf);
	पूर्ण

	क्रम (i = 0; i < e->sad_count; i++)
		hdmi_show_लघु_audio_desc(codec, e->sad + i);
पूर्ण

#अगर_घोषित CONFIG_SND_PROC_FS

अटल व्योम hdmi_prपूर्णांक_sad_info(पूर्णांक i, काष्ठा cea_sad *a,
				काष्ठा snd_info_buffer *buffer)
अणु
	अक्षर buf[SND_PRINT_RATES_ADVISED_बफ_मानE];

	snd_iम_लिखो(buffer, "sad%d_coding_type\t[0x%x] %s\n",
			i, a->क्रमmat, cea_audio_coding_type_names[a->क्रमmat]);
	snd_iम_लिखो(buffer, "sad%d_channels\t\t%d\n", i, a->channels);

	hdmi_prपूर्णांक_pcm_rates(a->rates, buf, माप(buf));
	snd_iम_लिखो(buffer, "sad%d_rates\t\t[0x%x]%s\n", i, a->rates, buf);

	अगर (a->क्रमmat == AUDIO_CODING_TYPE_LPCM) अणु
		snd_prपूर्णांक_pcm_bits(a->sample_bits, buf, माप(buf));
		snd_iम_लिखो(buffer, "sad%d_bits\t\t[0x%x]%s\n",
							i, a->sample_bits, buf);
	पूर्ण

	अगर (a->max_bitrate)
		snd_iम_लिखो(buffer, "sad%d_max_bitrate\t%d\n",
							i, a->max_bitrate);

	अगर (a->profile)
		snd_iम_लिखो(buffer, "sad%d_profile\t\t%d\n", i, a->profile);
पूर्ण

व्योम snd_hdmi_prपूर्णांक_eld_info(काष्ठा hdmi_eld *eld,
			     काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा parsed_hdmi_eld *e = &eld->info;
	अक्षर buf[SND_PRINT_CHANNEL_ALLOCATION_ADVISED_बफ_मानE];
	पूर्णांक i;
	अटल स्थिर अक्षर * स्थिर eld_version_names[32] = अणु
		"reserved",
		"reserved",
		"CEA-861D or below",
		[3 ... 30] = "reserved",
		[31] = "partial"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर cea_edid_version_names[8] = अणु
		"no CEA EDID Timing Extension block present",
		"CEA-861",
		"CEA-861-A",
		"CEA-861-B, C or D",
		[4 ... 7] = "reserved"
	पूर्ण;

	snd_iम_लिखो(buffer, "monitor_present\t\t%d\n", eld->monitor_present);
	snd_iम_लिखो(buffer, "eld_valid\t\t%d\n", eld->eld_valid);
	अगर (!eld->eld_valid)
		वापस;
	snd_iम_लिखो(buffer, "monitor_name\t\t%s\n", e->monitor_name);
	snd_iम_लिखो(buffer, "connection_type\t\t%s\n",
				eld_connection_type_names[e->conn_type]);
	snd_iम_लिखो(buffer, "eld_version\t\t[0x%x] %s\n", e->eld_ver,
					eld_version_names[e->eld_ver]);
	snd_iम_लिखो(buffer, "edid_version\t\t[0x%x] %s\n", e->cea_edid_ver,
				cea_edid_version_names[e->cea_edid_ver]);
	snd_iम_लिखो(buffer, "manufacture_id\t\t0x%x\n", e->manufacture_id);
	snd_iम_लिखो(buffer, "product_id\t\t0x%x\n", e->product_id);
	snd_iम_लिखो(buffer, "port_id\t\t\t0x%llx\n", (दीर्घ दीर्घ)e->port_id);
	snd_iम_लिखो(buffer, "support_hdcp\t\t%d\n", e->support_hdcp);
	snd_iम_लिखो(buffer, "support_ai\t\t%d\n", e->support_ai);
	snd_iम_लिखो(buffer, "audio_sync_delay\t%d\n", e->aud_synch_delay);

	snd_hdac_prपूर्णांक_channel_allocation(e->spk_alloc, buf, माप(buf));
	snd_iम_लिखो(buffer, "speakers\t\t[0x%x]%s\n", e->spk_alloc, buf);

	snd_iम_लिखो(buffer, "sad_count\t\t%d\n", e->sad_count);

	क्रम (i = 0; i < e->sad_count; i++)
		hdmi_prपूर्णांक_sad_info(i, e->sad + i, buffer);
पूर्ण

व्योम snd_hdmi_ग_लिखो_eld_info(काष्ठा hdmi_eld *eld,
			     काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा parsed_hdmi_eld *e = &eld->info;
	अक्षर line[64];
	अक्षर name[64];
	अक्षर *sname;
	दीर्घ दीर्घ val;
	अचिन्हित पूर्णांक n;

	जबतक (!snd_info_get_line(buffer, line, माप(line))) अणु
		अगर (माला_पूछो(line, "%s %llx", name, &val) != 2)
			जारी;
		/*
		 * We करोn't allow modअगरication to these fields:
		 * 	monitor_name manufacture_id product_id
		 * 	eld_version edid_version
		 */
		अगर (!म_भेद(name, "monitor_present"))
			eld->monitor_present = val;
		अन्यथा अगर (!म_भेद(name, "eld_valid"))
			eld->eld_valid = val;
		अन्यथा अगर (!म_भेद(name, "connection_type"))
			e->conn_type = val;
		अन्यथा अगर (!म_भेद(name, "port_id"))
			e->port_id = val;
		अन्यथा अगर (!म_भेद(name, "support_hdcp"))
			e->support_hdcp = val;
		अन्यथा अगर (!म_भेद(name, "support_ai"))
			e->support_ai = val;
		अन्यथा अगर (!म_भेद(name, "audio_sync_delay"))
			e->aud_synch_delay = val;
		अन्यथा अगर (!म_भेद(name, "speakers"))
			e->spk_alloc = val;
		अन्यथा अगर (!म_भेद(name, "sad_count"))
			e->sad_count = val;
		अन्यथा अगर (!म_भेदन(name, "sad", 3)) अणु
			sname = name + 4;
			n = name[3] - '0';
			अगर (name[4] >= '0' && name[4] <= '9') अणु
				sname++;
				n = 10 * n + name[4] - '0';
			पूर्ण
			अगर (n >= ELD_MAX_SAD)
				जारी;
			अगर (!म_भेद(sname, "_coding_type"))
				e->sad[n].क्रमmat = val;
			अन्यथा अगर (!म_भेद(sname, "_channels"))
				e->sad[n].channels = val;
			अन्यथा अगर (!म_भेद(sname, "_rates"))
				e->sad[n].rates = val;
			अन्यथा अगर (!म_भेद(sname, "_bits"))
				e->sad[n].sample_bits = val;
			अन्यथा अगर (!म_भेद(sname, "_max_bitrate"))
				e->sad[n].max_bitrate = val;
			अन्यथा अगर (!म_भेद(sname, "_profile"))
				e->sad[n].profile = val;
			अगर (n >= e->sad_count)
				e->sad_count = n + 1;
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_PROC_FS */

/* update PCM info based on ELD */
व्योम snd_hdmi_eld_update_pcm_info(काष्ठा parsed_hdmi_eld *e,
			      काष्ठा hda_pcm_stream *hinfo)
अणु
	u32 rates;
	u64 क्रमmats;
	अचिन्हित पूर्णांक maxbps;
	अचिन्हित पूर्णांक channels_max;
	पूर्णांक i;

	/* assume basic audio support (the basic audio flag is not in ELD;
	 * however, all audio capable sinks are required to support basic
	 * audio) */
	rates = SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |
		SNDRV_PCM_RATE_48000;
	क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
	maxbps = 16;
	channels_max = 2;
	क्रम (i = 0; i < e->sad_count; i++) अणु
		काष्ठा cea_sad *a = &e->sad[i];
		rates |= a->rates;
		अगर (a->channels > channels_max)
			channels_max = a->channels;
		अगर (a->क्रमmat == AUDIO_CODING_TYPE_LPCM) अणु
			अगर (a->sample_bits & AC_SUPPCM_BITS_20) अणु
				क्रमmats |= SNDRV_PCM_FMTBIT_S32_LE;
				अगर (maxbps < 20)
					maxbps = 20;
			पूर्ण
			अगर (a->sample_bits & AC_SUPPCM_BITS_24) अणु
				क्रमmats |= SNDRV_PCM_FMTBIT_S32_LE;
				अगर (maxbps < 24)
					maxbps = 24;
			पूर्ण
		पूर्ण
	पूर्ण

	/* restrict the parameters by the values the codec provides */
	hinfo->rates &= rates;
	hinfo->क्रमmats &= क्रमmats;
	hinfo->maxbps = min(hinfo->maxbps, maxbps);
	hinfo->channels_max = min(hinfo->channels_max, channels_max);
पूर्ण


/* ATI/AMD specअगरic stuff (ELD emulation) */

#घोषणा ATI_VERB_SET_AUDIO_DESCRIPTOR	0x776
#घोषणा ATI_VERB_SET_SINK_INFO_INDEX	0x780
#घोषणा ATI_VERB_GET_SPEAKER_ALLOCATION	0xf70
#घोषणा ATI_VERB_GET_AUDIO_DESCRIPTOR	0xf76
#घोषणा ATI_VERB_GET_AUDIO_VIDEO_DELAY	0xf7b
#घोषणा ATI_VERB_GET_SINK_INFO_INDEX	0xf80
#घोषणा ATI_VERB_GET_SINK_INFO_DATA	0xf81

#घोषणा ATI_SPKALLOC_SPKALLOC		0x007f
#घोषणा ATI_SPKALLOC_TYPE_HDMI		0x0100
#घोषणा ATI_SPKALLOC_TYPE_DISPLAYPORT	0x0200

/* first three bytes are just standard SAD */
#घोषणा ATI_AUDIODESC_CHANNELS		0x00000007
#घोषणा ATI_AUDIODESC_RATES		0x0000ff00
#घोषणा ATI_AUDIODESC_LPCM_STEREO_RATES	0xff000000

/* in standard HDMI VSDB क्रमmat */
#घोषणा ATI_DELAY_VIDEO_LATENCY		0x000000ff
#घोषणा ATI_DELAY_AUDIO_LATENCY		0x0000ff00

क्रमागत ati_sink_info_idx अणु
	ATI_INFO_IDX_MANUFACTURER_ID	= 0,
	ATI_INFO_IDX_PRODUCT_ID		= 1,
	ATI_INFO_IDX_SINK_DESC_LEN	= 2,
	ATI_INFO_IDX_PORT_ID_LOW	= 3,
	ATI_INFO_IDX_PORT_ID_HIGH	= 4,
	ATI_INFO_IDX_SINK_DESC_FIRST	= 5,
	ATI_INFO_IDX_SINK_DESC_LAST	= 22, /* max len 18 bytes */
पूर्ण;

पूर्णांक snd_hdmi_get_eld_ati(काष्ठा hda_codec *codec, hda_nid_t nid,
			 अचिन्हित अक्षर *buf, पूर्णांक *eld_size, bool rev3_or_later)
अणु
	पूर्णांक spkalloc, ati_sad, aud_synch;
	पूर्णांक sink_desc_len = 0;
	पूर्णांक pos, i;

	/* ATI/AMD करोes not have ELD, emulate it */

	spkalloc = snd_hda_codec_पढ़ो(codec, nid, 0, ATI_VERB_GET_SPEAKER_ALLOCATION, 0);

	अगर (spkalloc <= 0) अणु
		codec_info(codec, "HDMI ATI/AMD: no speaker allocation for ELD\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(buf, 0, ELD_FIXED_BYTES + ELD_MAX_MNL + ELD_MAX_SAD * 3);

	/* version */
	buf[0] = ELD_VER_CEA_861D << 3;

	/* speaker allocation from EDID */
	buf[7] = spkalloc & ATI_SPKALLOC_SPKALLOC;

	/* is DisplayPort? */
	अगर (spkalloc & ATI_SPKALLOC_TYPE_DISPLAYPORT)
		buf[5] |= 0x04;

	pos = ELD_FIXED_BYTES;

	अगर (rev3_or_later) अणु
		पूर्णांक sink_info;

		snd_hda_codec_ग_लिखो(codec, nid, 0, ATI_VERB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_PORT_ID_LOW);
		sink_info = snd_hda_codec_पढ़ो(codec, nid, 0, ATI_VERB_GET_SINK_INFO_DATA, 0);
		put_unaligned_le32(sink_info, buf + 8);

		snd_hda_codec_ग_लिखो(codec, nid, 0, ATI_VERB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_PORT_ID_HIGH);
		sink_info = snd_hda_codec_पढ़ो(codec, nid, 0, ATI_VERB_GET_SINK_INFO_DATA, 0);
		put_unaligned_le32(sink_info, buf + 12);

		snd_hda_codec_ग_लिखो(codec, nid, 0, ATI_VERB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_MANUFACTURER_ID);
		sink_info = snd_hda_codec_पढ़ो(codec, nid, 0, ATI_VERB_GET_SINK_INFO_DATA, 0);
		put_unaligned_le16(sink_info, buf + 16);

		snd_hda_codec_ग_लिखो(codec, nid, 0, ATI_VERB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_PRODUCT_ID);
		sink_info = snd_hda_codec_पढ़ो(codec, nid, 0, ATI_VERB_GET_SINK_INFO_DATA, 0);
		put_unaligned_le16(sink_info, buf + 18);

		snd_hda_codec_ग_लिखो(codec, nid, 0, ATI_VERB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_SINK_DESC_LEN);
		sink_desc_len = snd_hda_codec_पढ़ो(codec, nid, 0, ATI_VERB_GET_SINK_INFO_DATA, 0);

		अगर (sink_desc_len > ELD_MAX_MNL) अणु
			codec_info(codec, "HDMI ATI/AMD: Truncating HDMI sink description with length %d\n",
				   sink_desc_len);
			sink_desc_len = ELD_MAX_MNL;
		पूर्ण

		buf[4] |= sink_desc_len;

		क्रम (i = 0; i < sink_desc_len; i++) अणु
			snd_hda_codec_ग_लिखो(codec, nid, 0, ATI_VERB_SET_SINK_INFO_INDEX, ATI_INFO_IDX_SINK_DESC_FIRST + i);
			buf[pos++] = snd_hda_codec_पढ़ो(codec, nid, 0, ATI_VERB_GET_SINK_INFO_DATA, 0);
		पूर्ण
	पूर्ण

	क्रम (i = AUDIO_CODING_TYPE_LPCM; i <= AUDIO_CODING_TYPE_WMAPRO; i++) अणु
		अगर (i == AUDIO_CODING_TYPE_SACD || i == AUDIO_CODING_TYPE_DST)
			जारी; /* not handled by ATI/AMD */

		snd_hda_codec_ग_लिखो(codec, nid, 0, ATI_VERB_SET_AUDIO_DESCRIPTOR, i << 3);
		ati_sad = snd_hda_codec_पढ़ो(codec, nid, 0, ATI_VERB_GET_AUDIO_DESCRIPTOR, 0);

		अगर (ati_sad <= 0)
			जारी;

		अगर (ati_sad & ATI_AUDIODESC_RATES) अणु
			/* क्रमmat is supported, copy SAD as-is */
			buf[pos++] = (ati_sad & 0x0000ff) >> 0;
			buf[pos++] = (ati_sad & 0x00ff00) >> 8;
			buf[pos++] = (ati_sad & 0xff0000) >> 16;
		पूर्ण

		अगर (i == AUDIO_CODING_TYPE_LPCM
		    && (ati_sad & ATI_AUDIODESC_LPCM_STEREO_RATES)
		    && (ati_sad & ATI_AUDIODESC_LPCM_STEREO_RATES) >> 16 != (ati_sad & ATI_AUDIODESC_RATES)) अणु
			/* क्रम PCM there is a separate stereo rate mask */
			buf[pos++] = ((ati_sad & 0x000000ff) & ~ATI_AUDIODESC_CHANNELS) | 0x1;
			/* rates from the extra byte */
			buf[pos++] = (ati_sad & 0xff000000) >> 24;
			buf[pos++] = (ati_sad & 0x00ff0000) >> 16;
		पूर्ण
	पूर्ण

	अगर (pos == ELD_FIXED_BYTES + sink_desc_len) अणु
		codec_info(codec, "HDMI ATI/AMD: no audio descriptors for ELD\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * HDMI VSDB latency क्रमmat:
	 * separately क्रम both audio and video:
	 *  0          field not valid or unknown latency
	 *  [1..251]   msecs = (x-1)*2  (max 500ms with x = 251 = 0xfb)
	 *  255        audio/video not supported
	 *
	 * HDA latency क्रमmat:
	 * single value indicating video latency relative to audio:
	 *  0          unknown or 0ms
	 *  [1..250]   msecs = x*2  (max 500ms with x = 250 = 0xfa)
	 *  [251..255] reserved
	 */
	aud_synch = snd_hda_codec_पढ़ो(codec, nid, 0, ATI_VERB_GET_AUDIO_VIDEO_DELAY, 0);
	अगर ((aud_synch & ATI_DELAY_VIDEO_LATENCY) && (aud_synch & ATI_DELAY_AUDIO_LATENCY)) अणु
		पूर्णांक video_latency_hdmi = (aud_synch & ATI_DELAY_VIDEO_LATENCY);
		पूर्णांक audio_latency_hdmi = (aud_synch & ATI_DELAY_AUDIO_LATENCY) >> 8;

		अगर (video_latency_hdmi <= 0xfb && audio_latency_hdmi <= 0xfb &&
		    video_latency_hdmi > audio_latency_hdmi)
			buf[6] = video_latency_hdmi - audio_latency_hdmi;
		/* अन्यथा unknown/invalid or 0ms or video ahead of audio, so use zero */
	पूर्ण

	/* SAD count */
	buf[5] |= ((pos - ELD_FIXED_BYTES - sink_desc_len) / 3) << 4;

	/* Baseline ELD block length is 4-byte aligned */
	pos = round_up(pos, 4);

	/* Baseline ELD length (4-byte header is not counted in) */
	buf[2] = (pos - 4) / 4;

	*eld_size = pos;

	वापस 0;
पूर्ण
