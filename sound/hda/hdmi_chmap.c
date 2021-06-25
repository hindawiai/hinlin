<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HDMI Channel map support helpers
 */

#समावेश <linux/module.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश <sound/hda_chmap.h>

/*
 * CEA speaker placement:
 *
 *        FLH       FCH        FRH
 *  FLW    FL  FLC   FC   FRC   FR   FRW
 *
 *                                  LFE
 *                     TC
 *
 *          RL  RLC   RC   RRC   RR
 *
 * The Left/Right Surround channel _notions_ LS/RS in SMPTE 320M corresponds to
 * CEA RL/RR; The SMPTE channel _assignment_ C/LFE is swapped to CEA LFE/FC.
 */
क्रमागत cea_speaker_placement अणु
	FL  = (1 <<  0),	/* Front Left           */
	FC  = (1 <<  1),	/* Front Center         */
	FR  = (1 <<  2),	/* Front Right          */
	FLC = (1 <<  3),	/* Front Left Center    */
	FRC = (1 <<  4),	/* Front Right Center   */
	RL  = (1 <<  5),	/* Rear Left            */
	RC  = (1 <<  6),	/* Rear Center          */
	RR  = (1 <<  7),	/* Rear Right           */
	RLC = (1 <<  8),	/* Rear Left Center     */
	RRC = (1 <<  9),	/* Rear Right Center    */
	LFE = (1 << 10),	/* Low Frequency Effect */
	FLW = (1 << 11),	/* Front Left Wide      */
	FRW = (1 << 12),	/* Front Right Wide     */
	FLH = (1 << 13),	/* Front Left High      */
	FCH = (1 << 14),	/* Front Center High    */
	FRH = (1 << 15),	/* Front Right High     */
	TC  = (1 << 16),	/* Top Center           */
पूर्ण;

अटल स्थिर अक्षर * स्थिर cea_speaker_allocation_names[] = अणु
	/*  0 */ "FL/FR",
	/*  1 */ "LFE",
	/*  2 */ "FC",
	/*  3 */ "RL/RR",
	/*  4 */ "RC",
	/*  5 */ "FLC/FRC",
	/*  6 */ "RLC/RRC",
	/*  7 */ "FLW/FRW",
	/*  8 */ "FLH/FRH",
	/*  9 */ "TC",
	/* 10 */ "FCH",
पूर्ण;

/*
 * ELD SA bits in the CEA Speaker Allocation data block
 */
अटल स्थिर पूर्णांक eld_speaker_allocation_bits[] = अणु
	[0] = FL | FR,
	[1] = LFE,
	[2] = FC,
	[3] = RL | RR,
	[4] = RC,
	[5] = FLC | FRC,
	[6] = RLC | RRC,
	/* the following are not defined in ELD yet */
	[7] = FLW | FRW,
	[8] = FLH | FRH,
	[9] = TC,
	[10] = FCH,
पूर्ण;

/*
 * ALSA sequence is:
 *
 *       surround40   surround41   surround50   surround51   surround71
 * ch0   front left   =            =            =            =
 * ch1   front right  =            =            =            =
 * ch2   rear left    =            =            =            =
 * ch3   rear right   =            =            =            =
 * ch4                LFE          center       center       center
 * ch5                                          LFE          LFE
 * ch6                                                       side left
 * ch7                                                       side right
 *
 * surround71 = अणुFL, FR, RLC, RRC, FC, LFE, RL, RRपूर्ण
 */
अटल पूर्णांक hdmi_channel_mapping[0x32][8] = अणु
	/* stereo */
	[0x00] = अणु 0x00, 0x11, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7 पूर्ण,
	/* 2.1 */
	[0x01] = अणु 0x00, 0x11, 0x22, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7 पूर्ण,
	/* Dolby Surround */
	[0x02] = अणु 0x00, 0x11, 0x23, 0xf2, 0xf4, 0xf5, 0xf6, 0xf7 पूर्ण,
	/* surround40 */
	[0x08] = अणु 0x00, 0x11, 0x24, 0x35, 0xf3, 0xf2, 0xf6, 0xf7 पूर्ण,
	/* 4ch */
	[0x03] = अणु 0x00, 0x11, 0x23, 0x32, 0x44, 0xf5, 0xf6, 0xf7 पूर्ण,
	/* surround41 */
	[0x09] = अणु 0x00, 0x11, 0x24, 0x35, 0x42, 0xf3, 0xf6, 0xf7 पूर्ण,
	/* surround50 */
	[0x0a] = अणु 0x00, 0x11, 0x24, 0x35, 0x43, 0xf2, 0xf6, 0xf7 पूर्ण,
	/* surround51 */
	[0x0b] = अणु 0x00, 0x11, 0x24, 0x35, 0x43, 0x52, 0xf6, 0xf7 पूर्ण,
	/* 7.1 */
	[0x13] = अणु 0x00, 0x11, 0x26, 0x37, 0x43, 0x52, 0x64, 0x75 पूर्ण,
पूर्ण;

/*
 * This is an ordered list!
 *
 * The preceding ones have better chances to be selected by
 * hdmi_channel_allocation().
 */
अटल काष्ठा hdac_cea_channel_speaker_allocation channel_allocations[] = अणु
/*			  channel:   7     6    5    4    3     2    1    0  */
अणु .ca_index = 0x00,  .speakers = अणु   0,    0,   0,   0,   0,    0,  FR,  FL पूर्ण पूर्ण,
				 /* 2.1 */
अणु .ca_index = 0x01,  .speakers = अणु   0,    0,   0,   0,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
				 /* Dolby Surround */
अणु .ca_index = 0x02,  .speakers = अणु   0,    0,   0,   0,  FC,    0,  FR,  FL पूर्ण पूर्ण,
				 /* surround40 */
अणु .ca_index = 0x08,  .speakers = अणु   0,    0,  RR,  RL,   0,    0,  FR,  FL पूर्ण पूर्ण,
				 /* surround41 */
अणु .ca_index = 0x09,  .speakers = अणु   0,    0,  RR,  RL,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
				 /* surround50 */
अणु .ca_index = 0x0a,  .speakers = अणु   0,    0,  RR,  RL,  FC,    0,  FR,  FL पूर्ण पूर्ण,
				 /* surround51 */
अणु .ca_index = 0x0b,  .speakers = अणु   0,    0,  RR,  RL,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
				 /* 6.1 */
अणु .ca_index = 0x0f,  .speakers = अणु   0,   RC,  RR,  RL,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
				 /* surround71 */
अणु .ca_index = 0x13,  .speakers = अणु RRC,  RLC,  RR,  RL,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,

अणु .ca_index = 0x03,  .speakers = अणु   0,    0,   0,   0,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x04,  .speakers = अणु   0,    0,   0,  RC,   0,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x05,  .speakers = अणु   0,    0,   0,  RC,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x06,  .speakers = अणु   0,    0,   0,  RC,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x07,  .speakers = अणु   0,    0,   0,  RC,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x0c,  .speakers = अणु   0,   RC,  RR,  RL,   0,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x0d,  .speakers = अणु   0,   RC,  RR,  RL,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x0e,  .speakers = अणु   0,   RC,  RR,  RL,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x10,  .speakers = अणु RRC,  RLC,  RR,  RL,   0,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x11,  .speakers = अणु RRC,  RLC,  RR,  RL,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x12,  .speakers = अणु RRC,  RLC,  RR,  RL,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x14,  .speakers = अणु FRC,  FLC,   0,   0,   0,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x15,  .speakers = अणु FRC,  FLC,   0,   0,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x16,  .speakers = अणु FRC,  FLC,   0,   0,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x17,  .speakers = अणु FRC,  FLC,   0,   0,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x18,  .speakers = अणु FRC,  FLC,   0,  RC,   0,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x19,  .speakers = अणु FRC,  FLC,   0,  RC,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x1a,  .speakers = अणु FRC,  FLC,   0,  RC,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x1b,  .speakers = अणु FRC,  FLC,   0,  RC,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x1c,  .speakers = अणु FRC,  FLC,  RR,  RL,   0,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x1d,  .speakers = अणु FRC,  FLC,  RR,  RL,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x1e,  .speakers = अणु FRC,  FLC,  RR,  RL,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x1f,  .speakers = अणु FRC,  FLC,  RR,  RL,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x20,  .speakers = अणु   0,  FCH,  RR,  RL,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x21,  .speakers = अणु   0,  FCH,  RR,  RL,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x22,  .speakers = अणु  TC,    0,  RR,  RL,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x23,  .speakers = अणु  TC,    0,  RR,  RL,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x24,  .speakers = अणु FRH,  FLH,  RR,  RL,   0,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x25,  .speakers = अणु FRH,  FLH,  RR,  RL,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x26,  .speakers = अणु FRW,  FLW,  RR,  RL,   0,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x27,  .speakers = अणु FRW,  FLW,  RR,  RL,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x28,  .speakers = अणु  TC,   RC,  RR,  RL,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x29,  .speakers = अणु  TC,   RC,  RR,  RL,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x2a,  .speakers = अणु FCH,   RC,  RR,  RL,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x2b,  .speakers = अणु FCH,   RC,  RR,  RL,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x2c,  .speakers = अणु  TC,  FCH,  RR,  RL,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x2d,  .speakers = अणु  TC,  FCH,  RR,  RL,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x2e,  .speakers = अणु FRH,  FLH,  RR,  RL,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x2f,  .speakers = अणु FRH,  FLH,  RR,  RL,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x30,  .speakers = अणु FRW,  FLW,  RR,  RL,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x31,  .speakers = अणु FRW,  FLW,  RR,  RL,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
पूर्ण;

अटल पूर्णांक hdmi_pin_set_slot_channel(काष्ठा hdac_device *codec,
		hda_nid_t pin_nid, पूर्णांक asp_slot, पूर्णांक channel)
अणु
	वापस snd_hdac_codec_ग_लिखो(codec, pin_nid, 0,
				AC_VERB_SET_HDMI_CHAN_SLOT,
				(channel << 4) | asp_slot);
पूर्ण

अटल पूर्णांक hdmi_pin_get_slot_channel(काष्ठा hdac_device *codec,
			hda_nid_t pin_nid, पूर्णांक asp_slot)
अणु
	वापस (snd_hdac_codec_पढ़ो(codec, pin_nid, 0,
				   AC_VERB_GET_HDMI_CHAN_SLOT,
				   asp_slot) & 0xf0) >> 4;
पूर्ण

अटल पूर्णांक hdmi_get_channel_count(काष्ठा hdac_device *codec, hda_nid_t cvt_nid)
अणु
	वापस 1 + snd_hdac_codec_पढ़ो(codec, cvt_nid, 0,
					AC_VERB_GET_CVT_CHAN_COUNT, 0);
पूर्ण

अटल व्योम hdmi_set_channel_count(काष्ठा hdac_device *codec,
				   hda_nid_t cvt_nid, पूर्णांक chs)
अणु
	अगर (chs != hdmi_get_channel_count(codec, cvt_nid))
		snd_hdac_codec_ग_लिखो(codec, cvt_nid, 0,
				    AC_VERB_SET_CVT_CHAN_COUNT, chs - 1);
पूर्ण

/*
 * Channel mapping routines
 */

/*
 * Compute derived values in channel_allocations[].
 */
अटल व्योम init_channel_allocations(व्योम)
अणु
	पूर्णांक i, j;
	काष्ठा hdac_cea_channel_speaker_allocation *p;

	क्रम (i = 0; i < ARRAY_SIZE(channel_allocations); i++) अणु
		p = channel_allocations + i;
		p->channels = 0;
		p->spk_mask = 0;
		क्रम (j = 0; j < ARRAY_SIZE(p->speakers); j++)
			अगर (p->speakers[j]) अणु
				p->channels++;
				p->spk_mask |= p->speakers[j];
			पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक get_channel_allocation_order(पूर्णांक ca)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(channel_allocations); i++) अणु
		अगर (channel_allocations[i].ca_index == ca)
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

व्योम snd_hdac_prपूर्णांक_channel_allocation(पूर्णांक spk_alloc, अक्षर *buf, पूर्णांक buflen)
अणु
	पूर्णांक i, j;

	क्रम (i = 0, j = 0; i < ARRAY_SIZE(cea_speaker_allocation_names); i++) अणु
		अगर (spk_alloc & (1 << i))
			j += scnम_लिखो(buf + j, buflen - j,  " %s",
					cea_speaker_allocation_names[i]);
	पूर्ण
	buf[j] = '\0';	/* necessary when j == 0 */
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_prपूर्णांक_channel_allocation);

/*
 * The transक्रमmation takes two steps:
 *
 *	eld->spk_alloc => (eld_speaker_allocation_bits[]) => spk_mask
 *	      spk_mask => (channel_allocations[])         => ai->CA
 *
 * TODO: it could select the wrong CA from multiple candidates.
*/
अटल पूर्णांक hdmi_channel_allocation_spk_alloc_blk(काष्ठा hdac_device *codec,
				   पूर्णांक spk_alloc, पूर्णांक channels)
अणु
	पूर्णांक i;
	पूर्णांक ca = 0;
	पूर्णांक spk_mask = 0;
	अक्षर buf[SND_PRINT_CHANNEL_ALLOCATION_ADVISED_बफ_मानE];

	/*
	 * CA शेषs to 0 क्रम basic stereo audio
	 */
	अगर (channels <= 2)
		वापस 0;

	/*
	 * expand ELD's speaker allocation mask
	 *
	 * ELD tells the speaker mask in a compact(paired) क्रमm,
	 * expand ELD's notions to match the ones used by Audio InfoFrame.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(eld_speaker_allocation_bits); i++) अणु
		अगर (spk_alloc & (1 << i))
			spk_mask |= eld_speaker_allocation_bits[i];
	पूर्ण

	/* search क्रम the first working match in the CA table */
	क्रम (i = 0; i < ARRAY_SIZE(channel_allocations); i++) अणु
		अगर (channels == channel_allocations[i].channels &&
		    (spk_mask & channel_allocations[i].spk_mask) ==
				channel_allocations[i].spk_mask) अणु
			ca = channel_allocations[i].ca_index;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ca) अणु
		/*
		 * अगर there was no match, select the regular ALSA channel
		 * allocation with the matching number of channels
		 */
		क्रम (i = 0; i < ARRAY_SIZE(channel_allocations); i++) अणु
			अगर (channels == channel_allocations[i].channels) अणु
				ca = channel_allocations[i].ca_index;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	snd_hdac_prपूर्णांक_channel_allocation(spk_alloc, buf, माप(buf));
	dev_dbg(&codec->dev, "HDMI: select CA 0x%x for %d-channel allocation: %s\n",
		    ca, channels, buf);

	वापस ca;
पूर्ण

अटल व्योम hdmi_debug_channel_mapping(काष्ठा hdac_chmap *chmap,
				       hda_nid_t pin_nid)
अणु
#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
	पूर्णांक i;
	पूर्णांक channel;

	क्रम (i = 0; i < 8; i++) अणु
		channel = chmap->ops.pin_get_slot_channel(
				chmap->hdac, pin_nid, i);
		dev_dbg(&chmap->hdac->dev, "HDMI: ASP channel %d => slot %d\n",
						channel, i);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम hdmi_std_setup_channel_mapping(काष्ठा hdac_chmap *chmap,
				       hda_nid_t pin_nid,
				       bool non_pcm,
				       पूर्णांक ca)
अणु
	काष्ठा hdac_cea_channel_speaker_allocation *ch_alloc;
	पूर्णांक i;
	पूर्णांक err;
	पूर्णांक order;
	पूर्णांक non_pcm_mapping[8];

	order = get_channel_allocation_order(ca);
	ch_alloc = &channel_allocations[order];

	अगर (hdmi_channel_mapping[ca][1] == 0) अणु
		पूर्णांक hdmi_slot = 0;
		/* fill actual channel mappings in ALSA channel (i) order */
		क्रम (i = 0; i < ch_alloc->channels; i++) अणु
			जबतक (!WARN_ON(hdmi_slot >= 8) &&
			       !ch_alloc->speakers[7 - hdmi_slot])
				hdmi_slot++; /* skip zero slots */

			hdmi_channel_mapping[ca][i] = (i << 4) | hdmi_slot++;
		पूर्ण
		/* fill the rest of the slots with ALSA channel 0xf */
		क्रम (hdmi_slot = 0; hdmi_slot < 8; hdmi_slot++)
			अगर (!ch_alloc->speakers[7 - hdmi_slot])
				hdmi_channel_mapping[ca][i++] = (0xf << 4) | hdmi_slot;
	पूर्ण

	अगर (non_pcm) अणु
		क्रम (i = 0; i < ch_alloc->channels; i++)
			non_pcm_mapping[i] = (i << 4) | i;
		क्रम (; i < 8; i++)
			non_pcm_mapping[i] = (0xf << 4) | i;
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		पूर्णांक slotsetup = non_pcm ? non_pcm_mapping[i] : hdmi_channel_mapping[ca][i];
		पूर्णांक hdmi_slot = slotsetup & 0x0f;
		पूर्णांक channel = (slotsetup & 0xf0) >> 4;

		err = chmap->ops.pin_set_slot_channel(chmap->hdac,
				pin_nid, hdmi_slot, channel);
		अगर (err) अणु
			dev_dbg(&chmap->hdac->dev, "HDMI: channel mapping failed\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा channel_map_table अणु
	अचिन्हित अक्षर map;		/* ALSA API channel map position */
	पूर्णांक spk_mask;			/* speaker position bit mask */
पूर्ण;

अटल काष्ठा channel_map_table map_tables[] = अणु
	अणु SNDRV_CHMAP_FL,	FL पूर्ण,
	अणु SNDRV_CHMAP_FR,	FR पूर्ण,
	अणु SNDRV_CHMAP_RL,	RL पूर्ण,
	अणु SNDRV_CHMAP_RR,	RR पूर्ण,
	अणु SNDRV_CHMAP_LFE,	LFE पूर्ण,
	अणु SNDRV_CHMAP_FC,	FC पूर्ण,
	अणु SNDRV_CHMAP_RLC,	RLC पूर्ण,
	अणु SNDRV_CHMAP_RRC,	RRC पूर्ण,
	अणु SNDRV_CHMAP_RC,	RC पूर्ण,
	अणु SNDRV_CHMAP_FLC,	FLC पूर्ण,
	अणु SNDRV_CHMAP_FRC,	FRC पूर्ण,
	अणु SNDRV_CHMAP_TFL,	FLH पूर्ण,
	अणु SNDRV_CHMAP_TFR,	FRH पूर्ण,
	अणु SNDRV_CHMAP_FLW,	FLW पूर्ण,
	अणु SNDRV_CHMAP_FRW,	FRW पूर्ण,
	अणु SNDRV_CHMAP_TC,	TC पूर्ण,
	अणु SNDRV_CHMAP_TFC,	FCH पूर्ण,
	अणुपूर्ण /* terminator */
पूर्ण;

/* from ALSA API channel position to speaker bit mask */
पूर्णांक snd_hdac_chmap_to_spk_mask(अचिन्हित अक्षर c)
अणु
	काष्ठा channel_map_table *t = map_tables;

	क्रम (; t->map; t++) अणु
		अगर (t->map == c)
			वापस t->spk_mask;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_chmap_to_spk_mask);

/* from ALSA API channel position to CEA slot */
अटल पूर्णांक to_cea_slot(पूर्णांक ordered_ca, अचिन्हित अक्षर pos)
अणु
	पूर्णांक mask = snd_hdac_chmap_to_spk_mask(pos);
	पूर्णांक i;

	/* Add sanity check to pass klockwork check.
	 * This should never happen.
	 */
	अगर (ordered_ca >= ARRAY_SIZE(channel_allocations))
		वापस -1;

	अगर (mask) अणु
		क्रम (i = 0; i < 8; i++) अणु
			अगर (channel_allocations[ordered_ca].speakers[7 - i] == mask)
				वापस i;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

/* from speaker bit mask to ALSA API channel position */
पूर्णांक snd_hdac_spk_to_chmap(पूर्णांक spk)
अणु
	काष्ठा channel_map_table *t = map_tables;

	क्रम (; t->map; t++) अणु
		अगर (t->spk_mask == spk)
			वापस t->map;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_spk_to_chmap);

/* from CEA slot to ALSA API channel position */
अटल पूर्णांक from_cea_slot(पूर्णांक ordered_ca, अचिन्हित अक्षर slot)
अणु
	पूर्णांक mask;

	/* Add sanity check to pass klockwork check.
	 * This should never happen.
	 */
	अगर (slot >= 8)
		वापस 0;

	mask = channel_allocations[ordered_ca].speakers[7 - slot];

	वापस snd_hdac_spk_to_chmap(mask);
पूर्ण

/* get the CA index corresponding to the given ALSA API channel map */
अटल पूर्णांक hdmi_manual_channel_allocation(पूर्णांक chs, अचिन्हित अक्षर *map)
अणु
	पूर्णांक i, spks = 0, spk_mask = 0;

	क्रम (i = 0; i < chs; i++) अणु
		पूर्णांक mask = snd_hdac_chmap_to_spk_mask(map[i]);

		अगर (mask) अणु
			spk_mask |= mask;
			spks++;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(channel_allocations); i++) अणु
		अगर ((chs == channel_allocations[i].channels ||
		     spks == channel_allocations[i].channels) &&
		    (spk_mask & channel_allocations[i].spk_mask) ==
				channel_allocations[i].spk_mask)
			वापस channel_allocations[i].ca_index;
	पूर्ण
	वापस -1;
पूर्ण

/* set up the channel slots क्रम the given ALSA API channel map */
अटल पूर्णांक hdmi_manual_setup_channel_mapping(काष्ठा hdac_chmap *chmap,
					     hda_nid_t pin_nid,
					     पूर्णांक chs, अचिन्हित अक्षर *map,
					     पूर्णांक ca)
अणु
	पूर्णांक ordered_ca = get_channel_allocation_order(ca);
	पूर्णांक alsa_pos, hdmi_slot;
	पूर्णांक assignments[8] = अणु[0 ... 7] = 0xfपूर्ण;

	क्रम (alsa_pos = 0; alsa_pos < chs; alsa_pos++) अणु

		hdmi_slot = to_cea_slot(ordered_ca, map[alsa_pos]);

		अगर (hdmi_slot < 0)
			जारी; /* unasचिन्हित channel */

		assignments[hdmi_slot] = alsa_pos;
	पूर्ण

	क्रम (hdmi_slot = 0; hdmi_slot < 8; hdmi_slot++) अणु
		पूर्णांक err;

		err = chmap->ops.pin_set_slot_channel(chmap->hdac,
				pin_nid, hdmi_slot, assignments[hdmi_slot]);
		अगर (err)
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* store ALSA API channel map from the current शेष map */
अटल व्योम hdmi_setup_fake_chmap(अचिन्हित अक्षर *map, पूर्णांक ca)
अणु
	पूर्णांक i;
	पूर्णांक ordered_ca = get_channel_allocation_order(ca);

	क्रम (i = 0; i < 8; i++) अणु
		अगर (ordered_ca < ARRAY_SIZE(channel_allocations) &&
		    i < channel_allocations[ordered_ca].channels)
			map[i] = from_cea_slot(ordered_ca, hdmi_channel_mapping[ca][i] & 0x0f);
		अन्यथा
			map[i] = 0;
	पूर्ण
पूर्ण

व्योम snd_hdac_setup_channel_mapping(काष्ठा hdac_chmap *chmap,
				       hda_nid_t pin_nid, bool non_pcm, पूर्णांक ca,
				       पूर्णांक channels, अचिन्हित अक्षर *map,
				       bool chmap_set)
अणु
	अगर (!non_pcm && chmap_set) अणु
		hdmi_manual_setup_channel_mapping(chmap, pin_nid,
						  channels, map, ca);
	पूर्ण अन्यथा अणु
		hdmi_std_setup_channel_mapping(chmap, pin_nid, non_pcm, ca);
		hdmi_setup_fake_chmap(map, ca);
	पूर्ण

	hdmi_debug_channel_mapping(chmap, pin_nid);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_setup_channel_mapping);

पूर्णांक snd_hdac_get_active_channels(पूर्णांक ca)
अणु
	पूर्णांक ordered_ca = get_channel_allocation_order(ca);

	/* Add sanity check to pass klockwork check.
	 * This should never happen.
	 */
	अगर (ordered_ca >= ARRAY_SIZE(channel_allocations))
		ordered_ca = 0;

	वापस channel_allocations[ordered_ca].channels;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_get_active_channels);

काष्ठा hdac_cea_channel_speaker_allocation *snd_hdac_get_ch_alloc_from_ca(पूर्णांक ca)
अणु
	वापस &channel_allocations[get_channel_allocation_order(ca)];
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_get_ch_alloc_from_ca);

पूर्णांक snd_hdac_channel_allocation(काष्ठा hdac_device *hdac, पूर्णांक spk_alloc,
		पूर्णांक channels, bool chmap_set, bool non_pcm, अचिन्हित अक्षर *map)
अणु
	पूर्णांक ca;

	अगर (!non_pcm && chmap_set)
		ca = hdmi_manual_channel_allocation(channels, map);
	अन्यथा
		ca = hdmi_channel_allocation_spk_alloc_blk(hdac,
					spk_alloc, channels);

	अगर (ca < 0)
		ca = 0;

	वापस ca;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_channel_allocation);

/*
 * ALSA API channel-map control callbacks
 */
अटल पूर्णांक hdmi_chmap_ctl_info(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_pcm_chmap *info = snd_kcontrol_chip(kcontrol);
	काष्ठा hdac_chmap *chmap = info->निजी_data;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = chmap->channels_max;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = SNDRV_CHMAP_LAST;
	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_chmap_cea_alloc_validate_get_type(काष्ठा hdac_chmap *chmap,
		काष्ठा hdac_cea_channel_speaker_allocation *cap, पूर्णांक channels)
अणु
	/* If the speaker allocation matches the channel count, it is OK.*/
	अगर (cap->channels != channels)
		वापस -1;

	/* all channels are remappable मुक्तly */
	वापस SNDRV_CTL_TLVT_CHMAP_VAR;
पूर्ण

अटल व्योम hdmi_cea_alloc_to_tlv_chmap(काष्ठा hdac_chmap *hchmap,
		काष्ठा hdac_cea_channel_speaker_allocation *cap,
		अचिन्हित पूर्णांक *chmap, पूर्णांक channels)
अणु
	पूर्णांक count = 0;
	पूर्णांक c;

	क्रम (c = 7; c >= 0; c--) अणु
		पूर्णांक spk = cap->speakers[c];

		अगर (!spk)
			जारी;

		chmap[count++] = snd_hdac_spk_to_chmap(spk);
	पूर्ण

	WARN_ON(count != channels);
पूर्ण

अटल पूर्णांक spk_mask_from_spk_alloc(पूर्णांक spk_alloc)
अणु
	पूर्णांक i;
	पूर्णांक spk_mask = eld_speaker_allocation_bits[0];

	क्रम (i = 0; i < ARRAY_SIZE(eld_speaker_allocation_bits); i++) अणु
		अगर (spk_alloc & (1 << i))
			spk_mask |= eld_speaker_allocation_bits[i];
	पूर्ण

	वापस spk_mask;
पूर्ण

अटल पूर्णांक hdmi_chmap_ctl_tlv(काष्ठा snd_kcontrol *kcontrol, पूर्णांक op_flag,
			      अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक __user *tlv)
अणु
	काष्ठा snd_pcm_chmap *info = snd_kcontrol_chip(kcontrol);
	काष्ठा hdac_chmap *chmap = info->निजी_data;
	पूर्णांक pcm_idx = kcontrol->निजी_value;
	अचिन्हित पूर्णांक __user *dst;
	पूर्णांक chs, count = 0;
	अचिन्हित दीर्घ max_chs;
	पूर्णांक type;
	पूर्णांक spk_alloc, spk_mask;

	अगर (size < 8)
		वापस -ENOMEM;
	अगर (put_user(SNDRV_CTL_TLVT_CONTAINER, tlv))
		वापस -EFAULT;
	size -= 8;
	dst = tlv + 2;

	spk_alloc = chmap->ops.get_spk_alloc(chmap->hdac, pcm_idx);
	spk_mask = spk_mask_from_spk_alloc(spk_alloc);

	max_chs = hweight_दीर्घ(spk_mask);

	क्रम (chs = 2; chs <= max_chs; chs++) अणु
		पूर्णांक i;
		काष्ठा hdac_cea_channel_speaker_allocation *cap;

		cap = channel_allocations;
		क्रम (i = 0; i < ARRAY_SIZE(channel_allocations); i++, cap++) अणु
			पूर्णांक chs_bytes = chs * 4;
			अचिन्हित पूर्णांक tlv_chmap[8];

			अगर (cap->channels != chs)
				जारी;

			अगर (!(cap->spk_mask == (spk_mask & cap->spk_mask)))
				जारी;

			type = chmap->ops.chmap_cea_alloc_validate_get_type(
							chmap, cap, chs);
			अगर (type < 0)
				वापस -ENODEV;
			अगर (size < 8)
				वापस -ENOMEM;

			अगर (put_user(type, dst) ||
			    put_user(chs_bytes, dst + 1))
				वापस -EFAULT;

			dst += 2;
			size -= 8;
			count += 8;

			अगर (size < chs_bytes)
				वापस -ENOMEM;

			size -= chs_bytes;
			count += chs_bytes;
			chmap->ops.cea_alloc_to_tlv_chmap(chmap, cap,
						tlv_chmap, chs);

			अगर (copy_to_user(dst, tlv_chmap, chs_bytes))
				वापस -EFAULT;
			dst += chs;
		पूर्ण
	पूर्ण

	अगर (put_user(count, tlv + 1))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_chmap_ctl_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcm_chmap *info = snd_kcontrol_chip(kcontrol);
	काष्ठा hdac_chmap *chmap = info->निजी_data;
	पूर्णांक pcm_idx = kcontrol->निजी_value;
	अचिन्हित अक्षर pcm_chmap[8];
	पूर्णांक i;

	स_रखो(pcm_chmap, 0, माप(pcm_chmap));
	chmap->ops.get_chmap(chmap->hdac, pcm_idx, pcm_chmap);

	क्रम (i = 0; i < ARRAY_SIZE(pcm_chmap); i++)
		ucontrol->value.पूर्णांकeger.value[i] = pcm_chmap[i];

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_chmap_ctl_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcm_chmap *info = snd_kcontrol_chip(kcontrol);
	काष्ठा hdac_chmap *hchmap = info->निजी_data;
	पूर्णांक pcm_idx = kcontrol->निजी_value;
	अचिन्हित पूर्णांक ctl_idx;
	काष्ठा snd_pcm_substream *substream;
	अचिन्हित अक्षर chmap[8], per_pin_chmap[8];
	पूर्णांक i, err, ca, prepared = 0;

	/* No monitor is connected in dyn_pcm_assign.
	 * It's invalid to setup the chmap
	 */
	अगर (!hchmap->ops.is_pcm_attached(hchmap->hdac, pcm_idx))
		वापस 0;

	ctl_idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	substream = snd_pcm_chmap_substream(info, ctl_idx);
	अगर (!substream || !substream->runसमय)
		वापस 0; /* just क्रम aव्योमing error from alsactl restore */
	चयन (substream->runसमय->status->state) अणु
	हाल SNDRV_PCM_STATE_OPEN:
	हाल SNDRV_PCM_STATE_SETUP:
		अवरोध;
	हाल SNDRV_PCM_STATE_PREPARED:
		prepared = 1;
		अवरोध;
	शेष:
		वापस -EBUSY;
	पूर्ण
	स_रखो(chmap, 0, माप(chmap));
	क्रम (i = 0; i < ARRAY_SIZE(chmap); i++)
		chmap[i] = ucontrol->value.पूर्णांकeger.value[i];

	hchmap->ops.get_chmap(hchmap->hdac, pcm_idx, per_pin_chmap);
	अगर (!स_भेद(chmap, per_pin_chmap, माप(chmap)))
		वापस 0;
	ca = hdmi_manual_channel_allocation(ARRAY_SIZE(chmap), chmap);
	अगर (ca < 0)
		वापस -EINVAL;
	अगर (hchmap->ops.chmap_validate) अणु
		err = hchmap->ops.chmap_validate(hchmap, ca,
				ARRAY_SIZE(chmap), chmap);
		अगर (err)
			वापस err;
	पूर्ण

	hchmap->ops.set_chmap(hchmap->hdac, pcm_idx, chmap, prepared);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hdac_chmap_ops chmap_ops = अणु
	.chmap_cea_alloc_validate_get_type	= hdmi_chmap_cea_alloc_validate_get_type,
	.cea_alloc_to_tlv_chmap			= hdmi_cea_alloc_to_tlv_chmap,
	.pin_get_slot_channel			= hdmi_pin_get_slot_channel,
	.pin_set_slot_channel			= hdmi_pin_set_slot_channel,
	.set_channel_count			= hdmi_set_channel_count,
पूर्ण;

व्योम snd_hdac_रेजिस्टर_chmap_ops(काष्ठा hdac_device *hdac,
				काष्ठा hdac_chmap *chmap)
अणु
	chmap->ops = chmap_ops;
	chmap->hdac = hdac;
	init_channel_allocations();
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_रेजिस्टर_chmap_ops);

पूर्णांक snd_hdac_add_chmap_ctls(काष्ठा snd_pcm *pcm, पूर्णांक pcm_idx,
				काष्ठा hdac_chmap *hchmap)
अणु
	काष्ठा snd_pcm_chmap *chmap;
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक err, i;

	err = snd_pcm_add_chmap_ctls(pcm,
				     SNDRV_PCM_STREAM_PLAYBACK,
				     शून्य, 0, pcm_idx, &chmap);
	अगर (err < 0)
		वापस err;
	/* override handlers */
	chmap->निजी_data = hchmap;
	kctl = chmap->kctl;
	क्रम (i = 0; i < kctl->count; i++)
		kctl->vd[i].access |= SNDRV_CTL_ELEM_ACCESS_WRITE;
	kctl->info = hdmi_chmap_ctl_info;
	kctl->get = hdmi_chmap_ctl_get;
	kctl->put = hdmi_chmap_ctl_put;
	kctl->tlv.c = hdmi_chmap_ctl_tlv;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_add_chmap_ctls);
