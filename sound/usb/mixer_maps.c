<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Additional mixer mapping
 *
 *   Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

काष्ठा usbmix_dB_map अणु
	u32 min;
	u32 max;
पूर्ण;

काष्ठा usbmix_name_map अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
	पूर्णांक control;
	स्थिर काष्ठा usbmix_dB_map *dB;
पूर्ण;

काष्ठा usbmix_selector_map अणु
	पूर्णांक id;
	पूर्णांक count;
	स्थिर अक्षर **names;
पूर्ण;

काष्ठा usbmix_ctl_map अणु
	u32 id;
	स्थिर काष्ठा usbmix_name_map *map;
	स्थिर काष्ठा usbmix_selector_map *selector_map;
	स्थिर काष्ठा usbmix_connector_map *connector_map;
	पूर्णांक ignore_ctl_error;
पूर्ण;

/*
 * USB control mappers क्रम SB Exitigy
 */

/*
 * Topology of SB Extigy (see on the wide screen :)

USB_IN[1] --->FU[2]------------------------------+->MU[16]-->PU[17]-+->FU[18]--+->EU[27]--+->EU[21]-->FU[22]--+->FU[23] > Dig_OUT[24]
                                                 ^                  |          |          |                   |
USB_IN[3] -+->SU[5]-->FU[6]--+->MU[14] ->PU[15]->+                  |          |          |                   +->FU[25] > Dig_OUT[26]
           ^                 ^                   |                  |          |          |
Dig_IN[4] -+                 |                   |                  |          |          +->FU[28]---------------------> Spk_OUT[19]
                             |                   |                  |          |
Lin-IN[7] -+-->FU[8]---------+                   |                  |          +----------------------------------------> Hph_OUT[20]
           |                                     |                  |
Mic-IN[9] --+->FU[10]----------------------------+                  |
           ||                                                       |
           ||  +----------------------------------------------------+
           VV  V
           ++--+->SU[11]-->FU[12] --------------------------------------------------------------------------------------> USB_OUT[13]
*/

अटल स्थिर काष्ठा usbmix_name_map extigy_map[] = अणु
	/* 1: IT pcm */
	अणु 2, "PCM Playback" पूर्ण, /* FU */
	/* 3: IT pcm */
	/* 4: IT digital in */
	अणु 5, शून्य पूर्ण, /* DISABLED: this seems to be bogus on some firmware */
	अणु 6, "Digital In" पूर्ण, /* FU */
	/* 7: IT line */
	अणु 8, "Line Playback" पूर्ण, /* FU */
	/* 9: IT mic */
	अणु 10, "Mic Playback" पूर्ण, /* FU */
	अणु 11, "Capture Source" पूर्ण, /* SU */
	अणु 12, "Capture" पूर्ण, /* FU */
	/* 13: OT pcm capture */
	/* 14: MU (w/o controls) */
	/* 15: PU (3D enh) */
	/* 16: MU (w/o controls) */
	अणु 17, शून्य, 1 पूर्ण, /* DISABLED: PU-चयन (any effect?) */
	अणु 17, "Channel Routing", 2 पूर्ण,	/* PU: mode select */
	अणु 18, "Tone Control - Bass", UAC_FU_BASS पूर्ण, /* FU */
	अणु 18, "Tone Control - Treble", UAC_FU_TREBLE पूर्ण, /* FU */
	अणु 18, "Master Playback" पूर्ण, /* FU; others */
	/* 19: OT speaker */
	/* 20: OT headphone */
	अणु 21, शून्य पूर्ण, /* DISABLED: EU (क्रम what?) */
	अणु 22, "Digital Out Playback" पूर्ण, /* FU */
	अणु 23, "Digital Out1 Playback" पूर्ण, /* FU */  /* FIXME: corresponds to 24 */
	/* 24: OT digital out */
	अणु 25, "IEC958 Optical Playback" पूर्ण, /* FU */
	अणु 26, "IEC958 Optical Playback" पूर्ण, /* OT */
	अणु 27, शून्य पूर्ण, /* DISABLED: EU (क्रम what?) */
	/* 28: FU speaker (mute) */
	अणु 29, शून्य पूर्ण, /* Digital Input Playback Source? */
	अणु 0 पूर्ण /* terminator */
पूर्ण;

/* Sound Blaster MP3+ controls mapping
 * The शेष mixer channels have totally misleading names,
 * e.g. no Master and fake PCM volume
 *			Pavel Mihaylov <bin@bash.info>
 */
अटल स्थिर काष्ठा usbmix_dB_map mp3plus_dB_1 = अणु.min = -4781, .max = 0पूर्ण;
						/* just guess */
अटल स्थिर काष्ठा usbmix_dB_map mp3plus_dB_2 = अणु.min = -1781, .max = 618पूर्ण;
						/* just guess */

अटल स्थिर काष्ठा usbmix_name_map mp3plus_map[] = अणु
	/* 1: IT pcm */
	/* 2: IT mic */
	/* 3: IT line */
	/* 4: IT digital in */
	/* 5: OT digital out */
	/* 6: OT speaker */
	/* 7: OT pcm capture */
	अणु 8, "Capture Source" पूर्ण, /* FU, शेष PCM Capture Source */
		/* (Mic, Input 1 = Line input, Input 2 = Optical input) */
	अणु 9, "Master Playback" पूर्ण, /* FU, शेष Speaker 1 */
	/* अणु 10, "Mic Capture", 1 पूर्ण, */ /* FU, Mic Capture */
	अणु 10, /* "Mic Capture", */ शून्य, 2, .dB = &mp3plus_dB_2 पूर्ण,
		/* FU, Mic Capture */
	अणु 10, "Mic Boost", 7 पूर्ण, /* FU, शेष Auto Gain Input */
	अणु 11, "Line Capture", .dB = &mp3plus_dB_2 पूर्ण,
		/* FU, शेष PCM Capture */
	अणु 12, "Digital In Playback" पूर्ण, /* FU, शेष PCM 1 */
	अणु 13, /* "Mic Playback", */ .dB = &mp3plus_dB_1 पूर्ण,
		/* FU, शेष Mic Playback */
	अणु 14, "Line Playback", .dB = &mp3plus_dB_1 पूर्ण, /* FU, शेष Speaker */
	/* 15: MU */
	अणु 0 पूर्ण /* terminator */
पूर्ण;

/* Topology of SB Audigy 2 NX

          +----------------------------->EU[27]--+
          |                                      v
          | +----------------------------------->SU[29]---->FU[22]-->Dig_OUT[24]
          | |                                    ^
USB_IN[1]-+------------+              +->EU[17]->+->FU[11]-+
            |          v              |          v         |
Dig_IN[4]---+->FU[6]-->MU[16]->FU[18]-+->EU[21]->SU[31]----->FU[30]->Hph_OUT[20]
            |          ^              |                    |
Lin_IN[7]-+--->FU[8]---+              +->EU[23]->FU[28]------------->Spk_OUT[19]
          | |                                              v
          +--->FU[12]------------------------------------->SU[14]--->USB_OUT[15]
            |                                              ^
            +->FU[13]--------------------------------------+
*/
अटल स्थिर काष्ठा usbmix_name_map audigy2nx_map[] = अणु
	/* 1: IT pcm playback */
	/* 4: IT digital in */
	अणु 6, "Digital In Playback" पूर्ण, /* FU */
	/* 7: IT line in */
	अणु 8, "Line Playback" पूर्ण, /* FU */
	अणु 11, "What-U-Hear Capture" पूर्ण, /* FU */
	अणु 12, "Line Capture" पूर्ण, /* FU */
	अणु 13, "Digital In Capture" पूर्ण, /* FU */
	अणु 14, "Capture Source" पूर्ण, /* SU */
	/* 15: OT pcm capture */
	/* 16: MU w/o controls */
	अणु 17, शून्य पूर्ण, /* DISABLED: EU (क्रम what?) */
	अणु 18, "Master Playback" पूर्ण, /* FU */
	/* 19: OT speaker */
	/* 20: OT headphone */
	अणु 21, शून्य पूर्ण, /* DISABLED: EU (क्रम what?) */
	अणु 22, "Digital Out Playback" पूर्ण, /* FU */
	अणु 23, शून्य पूर्ण, /* DISABLED: EU (क्रम what?) */
	/* 24: OT digital out */
	अणु 27, शून्य पूर्ण, /* DISABLED: EU (क्रम what?) */
	अणु 28, "Speaker Playback" पूर्ण, /* FU */
	अणु 29, "Digital Out Source" पूर्ण, /* SU */
	अणु 30, "Headphone Playback" पूर्ण, /* FU */
	अणु 31, "Headphone Source" पूर्ण, /* SU */
	अणु 0 पूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा usbmix_name_map mbox1_map[] = अणु
	अणु 1, "Clock" पूर्ण,
	अणु 0 पूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा usbmix_selector_map c400_selectors[] = अणु
	अणु
		.id = 0x80,
		.count = 2,
		.names = (स्थिर अक्षर*[]) अणु"Internal", "SPDIF"पूर्ण
	पूर्ण,
	अणु 0 पूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा usbmix_selector_map audigy2nx_selectors[] = अणु
	अणु
		.id = 14, /* Capture Source */
		.count = 3,
		.names = (स्थिर अक्षर*[]) अणु"Line", "Digital In", "What-U-Hear"पूर्ण
	पूर्ण,
	अणु
		.id = 29, /* Digital Out Source */
		.count = 3,
		.names = (स्थिर अक्षर*[]) अणु"Front", "PCM", "Digital In"पूर्ण
	पूर्ण,
	अणु
		.id = 31, /* Headphone Source */
		.count = 2,
		.names = (स्थिर अक्षर*[]) अणु"Front", "Side"पूर्ण
	पूर्ण,
	अणु 0 पूर्ण /* terminator */
पूर्ण;

/* Creative SoundBlaster Live! 24-bit External */
अटल स्थिर काष्ठा usbmix_name_map live24ext_map[] = अणु
	/* 2: PCM Playback Volume */
	अणु 5, "Mic Capture" पूर्ण, /* FU, शेष PCM Capture Volume */
	अणु 0 पूर्ण /* terminator */
पूर्ण;

/* LineX FM Transmitter entry - needed to bypass controls bug */
अटल स्थिर काष्ठा usbmix_name_map linex_map[] = अणु
	/* 1: IT pcm */
	/* 2: OT Speaker */ 
	अणु 3, "Master" पूर्ण, /* FU: master volume - left / right / mute */
	अणु 0 पूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा usbmix_name_map maya44_map[] = अणु
	/* 1: IT line */
	अणु 2, "Line Playback" पूर्ण, /* FU */
	/* 3: IT line */
	अणु 4, "Line Playback" पूर्ण, /* FU */
	/* 5: IT pcm playback */
	/* 6: MU */
	अणु 7, "Master Playback" पूर्ण, /* FU */
	/* 8: OT speaker */
	/* 9: IT line */
	अणु 10, "Line Capture" पूर्ण, /* FU */
	/* 11: MU */
	/* 12: OT pcm capture */
	अणु पूर्ण
पूर्ण;

/* Section "justlink_map" below added by James Courtier-Dutton <James@superbug.demon.co.uk>
 * sourced from Maplin Electronics (https://www.maplin.co.uk), part number A56AK
 * Part has 2 connectors that act as a single output. (TOSLINK Optical क्रम digital out, and 3.5mm Jack क्रम Analogue out.)
 * The USB Mixer publishes a Microphone and extra Volume controls क्रम it, but none exist on the device,
 * so this map हटाओs all unwanted sliders from alsamixer
 */

अटल स्थिर काष्ठा usbmix_name_map justlink_map[] = अणु
	/* 1: IT pcm playback */
	/* 2: Not present */
	अणु 3, शून्यपूर्ण, /* IT mic (No mic input on device) */
	/* 4: Not present */
	/* 5: OT speacker */
	/* 6: OT pcm capture */
	अणु 7, "Master Playback" पूर्ण, /* Mute/volume क्रम speaker */
	अणु 8, शून्य पूर्ण, /* Capture Switch (No capture inमाला_दो on device) */
	अणु 9, शून्य पूर्ण, /* Capture Mute/volume (No capture inमाला_दो on device */
	/* 0xa: Not present */
	/* 0xb: MU (w/o controls) */
	अणु 0xc, शून्य पूर्ण, /* Mic feedback Mute/volume (No capture inमाला_दो on device) */
	अणु 0 पूर्ण /* terminator */
पूर्ण;

/* TerraTec Aureon 5.1 MkII USB */
अटल स्थिर काष्ठा usbmix_name_map aureon_51_2_map[] = अणु
	/* 1: IT USB */
	/* 2: IT Mic */
	/* 3: IT Line */
	/* 4: IT SPDIF */
	/* 5: OT SPDIF */
	/* 6: OT Speaker */
	/* 7: OT USB */
	अणु 8, "Capture Source" पूर्ण, /* SU */
	अणु 9, "Master Playback" पूर्ण, /* FU */
	अणु 10, "Mic Capture" पूर्ण, /* FU */
	अणु 11, "Line Capture" पूर्ण, /* FU */
	अणु 12, "IEC958 In Capture" पूर्ण, /* FU */
	अणु 13, "Mic Playback" पूर्ण, /* FU */
	अणु 14, "Line Playback" पूर्ण, /* FU */
	/* 15: MU */
	अणुपूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा usbmix_name_map scratch_live_map[] = अणु
	/* 1: IT Line 1 (USB streaming) */
	/* 2: OT Line 1 (Speaker) */
	/* 3: IT Line 1 (Line connector) */
	अणु 4, "Line 1 In" पूर्ण, /* FU */
	/* 5: OT Line 1 (USB streaming) */
	/* 6: IT Line 2 (USB streaming) */
	/* 7: OT Line 2 (Speaker) */
	/* 8: IT Line 2 (Line connector) */
	अणु 9, "Line 2 In" पूर्ण, /* FU */
	/* 10: OT Line 2 (USB streaming) */
	/* 11: IT Mic (Line connector) */
	/* 12: OT Mic (USB streaming) */
	अणु 0 पूर्ण /* terminator */
पूर्ण;

अटल स्थिर काष्ठा usbmix_name_map ebox44_map[] = अणु
	अणु 4, शून्य पूर्ण, /* FU */
	अणु 6, शून्य पूर्ण, /* MU */
	अणु 7, शून्य पूर्ण, /* FU */
	अणु 10, शून्य पूर्ण, /* FU */
	अणु 11, शून्य पूर्ण, /* MU */
	अणु 0 पूर्ण
पूर्ण;

/* "Gamesurround Muse Pocket LT" looks same like "Sound Blaster MP3+"
 *  most importand dअगरference is SU[8], it should be set to "Capture Source"
 *  to make alsamixer and PA working properly.
 *  FIXME: or mp3plus_map should use "Capture Source" too,
 *  so this maps can be merget
 */
अटल स्थिर काष्ठा usbmix_name_map hercules_usb51_map[] = अणु
	अणु 8, "Capture Source" पूर्ण,	/* SU, शेष "PCM Capture Source" */
	अणु 9, "Master Playback" पूर्ण,	/* FU, शेष "Speaker Playback" */
	अणु 10, "Mic Boost", 7 पूर्ण,		/* FU, शेष "Auto Gain Input" */
	अणु 11, "Line Capture" पूर्ण,		/* FU, शेष "PCM Capture" */
	अणु 13, "Mic Bypass Playback" पूर्ण,	/* FU, शेष "Mic Playback" */
	अणु 14, "Line Bypass Playback" पूर्ण,	/* FU, शेष "Line Playback" */
	अणु 0 पूर्ण				/* terminator */
पूर्ण;

/* Plantronics Gamecom 780 has a broken volume control, better to disable it */
अटल स्थिर काष्ठा usbmix_name_map gamecom780_map[] = अणु
	अणु 9, शून्य पूर्ण, /* FU, speaker out */
	अणुपूर्ण
पूर्ण;

/* some (all?) SCMS USB3318 devices are affected by a firmware lock up
 * when anything attempts to access FU 10 (control)
 */
अटल स्थिर काष्ठा usbmix_name_map scms_usb3318_map[] = अणु
	अणु 10, शून्य पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

/* Bose companion 5, the dB conversion factor is 16 instead of 256 */
अटल स्थिर काष्ठा usbmix_dB_map bose_companion5_dB = अणु-5006, -6पूर्ण;
अटल स्थिर काष्ठा usbmix_name_map bose_companion5_map[] = अणु
	अणु 3, शून्य, .dB = &bose_companion5_dB पूर्ण,
	अणु 0 पूर्ण	/* terminator */
पूर्ण;

/* Sennheiser Communications Headset [PC 8], the dB value is reported as -6 negative maximum  */
अटल स्थिर काष्ठा usbmix_dB_map sennheiser_pc8_dB = अणु-9500, 0पूर्ण;
अटल स्थिर काष्ठा usbmix_name_map sennheiser_pc8_map[] = अणु
	अणु 9, शून्य, .dB = &sennheiser_pc8_dB पूर्ण,
	अणु 0 पूर्ण   /* terminator */
पूर्ण;

/*
 * Dell usb करोck with ALC4020 codec had a firmware problem where it got
 * screwed up when zero volume is passed; just skip it as a workaround
 *
 * Also the extension unit gives an access error, so skip it as well.
 */
अटल स्थिर काष्ठा usbmix_name_map dell_alc4020_map[] = अणु
	अणु 4, शून्य पूर्ण,	/* extension unit */
	अणु 16, शून्य पूर्ण,
	अणु 19, शून्य पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

/*
 * Corsair Virtuoso calls everything "Headset" without this, leading to
 * applications moving the sidetone control instead of the मुख्य one.
 */
अटल स्थिर काष्ठा usbmix_name_map corsair_virtuoso_map[] = अणु
	अणु 3, "Mic Capture" पूर्ण,
	अणु 6, "Sidetone Playback" पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

/* Some mobos shipped with a dummy HD-audio show the invalid GET_MIN/GET_MAX
 * response क्रम Input Gain Pad (id=19, control=12) and the connector status
 * क्रम SPDIF terminal (id=18).  Skip them.
 */
अटल स्थिर काष्ठा usbmix_name_map asus_rog_map[] = अणु
	अणु 18, शून्य पूर्ण, /* OT, connector control */
	अणु 19, शून्य, 12 पूर्ण, /* FU, Input Gain Pad */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usbmix_name_map lenovo_p620_rear_map[] = अणु
	अणु 19, शून्य, 12 पूर्ण, /* FU, Input Gain Pad */
	अणुपूर्ण
पूर्ण;

/* TRX40 mobos with Realtek ALC1220-VB */
अटल स्थिर काष्ठा usbmix_name_map trx40_mobo_map[] = अणु
	अणु 18, शून्य पूर्ण, /* OT, IEC958 - broken response, disabled */
	अणु 19, शून्य, 12 पूर्ण, /* FU, Input Gain Pad - broken response, disabled */
	अणु 16, "Speaker" पूर्ण,		/* OT */
	अणु 22, "Speaker Playback" पूर्ण,	/* FU */
	अणु 7, "Line" पूर्ण,			/* IT */
	अणु 19, "Line Capture" पूर्ण,		/* FU */
	अणु 17, "Front Headphone" पूर्ण,	/* OT */
	अणु 23, "Front Headphone Playback" पूर्ण,	/* FU */
	अणु 8, "Mic" पूर्ण,			/* IT */
	अणु 20, "Mic Capture" पूर्ण,		/* FU */
	अणु 9, "Front Mic" पूर्ण,		/* IT */
	अणु 21, "Front Mic Capture" पूर्ण,	/* FU */
	अणु 24, "IEC958 Playback" पूर्ण,	/* FU */
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा usbmix_connector_map trx40_mobo_connector_map[] = अणु
	अणु 10, 16 पूर्ण,	/* (Back) Speaker */
	अणु 11, 17 पूर्ण,	/* Front Headphone */
	अणु 13, 7 पूर्ण,	/* Line */
	अणु 14, 8 पूर्ण,	/* Mic */
	अणु 15, 9 पूर्ण,	/* Front Mic */
	अणुपूर्ण
पूर्ण;

/* Rear panel + front mic on Gigabyte TRX40 Aorus Master with ALC1220-VB */
अटल स्थिर काष्ठा usbmix_name_map aorus_master_alc1220vb_map[] = अणु
	अणु 17, शून्य पूर्ण,			/* OT, IEC958?, disabled */
	अणु 19, शून्य, 12 पूर्ण, /* FU, Input Gain Pad - broken response, disabled */
	अणु 16, "Line Out" पूर्ण,		/* OT */
	अणु 22, "Line Out Playback" पूर्ण,	/* FU */
	अणु 7, "Line" पूर्ण,			/* IT */
	अणु 19, "Line Capture" पूर्ण,		/* FU */
	अणु 8, "Mic" पूर्ण,			/* IT */
	अणु 20, "Mic Capture" पूर्ण,		/* FU */
	अणु 9, "Front Mic" पूर्ण,		/* IT */
	अणु 21, "Front Mic Capture" पूर्ण,	/* FU */
	अणुपूर्ण
पूर्ण;

/*
 * Control map entries
 */

अटल स्थिर काष्ठा usbmix_ctl_map usbmix_ctl_maps[] = अणु
	अणु
		.id = USB_ID(0x041e, 0x3000),
		.map = extigy_map,
		.ignore_ctl_error = 1,
	पूर्ण,
	अणु
		.id = USB_ID(0x041e, 0x3010),
		.map = mp3plus_map,
	पूर्ण,
	अणु
		.id = USB_ID(0x041e, 0x3020),
		.map = audigy2nx_map,
		.selector_map = audigy2nx_selectors,
	पूर्ण,
 	अणु
		.id = USB_ID(0x041e, 0x3040),
		.map = live24ext_map,
	पूर्ण,
	अणु
		.id = USB_ID(0x041e, 0x3048),
		.map = audigy2nx_map,
		.selector_map = audigy2nx_selectors,
	पूर्ण,
	अणु	/* Logitech, Inc. QuickCam Pro क्रम Notebooks */
		.id = USB_ID(0x046d, 0x0991),
		.ignore_ctl_error = 1,
	पूर्ण,
	अणु	/* Logitech, Inc. QuickCam E 3500 */
		.id = USB_ID(0x046d, 0x09a4),
		.ignore_ctl_error = 1,
	पूर्ण,
	अणु	/* Plantronics GameCom 780 */
		.id = USB_ID(0x047f, 0xc010),
		.map = gamecom780_map,
	पूर्ण,
	अणु
		/* Hercules DJ Console (Winकरोws Edition) */
		.id = USB_ID(0x06f8, 0xb000),
		.ignore_ctl_error = 1,
	पूर्ण,
	अणु
		/* Hercules DJ Console (Macपूर्णांकosh Edition) */
		.id = USB_ID(0x06f8, 0xd002),
		.ignore_ctl_error = 1,
	पूर्ण,
	अणु
		/* Hercules Gamesurround Muse Pocket LT
		 * (USB 5.1 Channel Audio Adapter)
		 */
		.id = USB_ID(0x06f8, 0xc000),
		.map = hercules_usb51_map,
	पूर्ण,
	अणु
		.id = USB_ID(0x0763, 0x2030),
		.selector_map = c400_selectors,
	पूर्ण,
	अणु
		.id = USB_ID(0x0763, 0x2031),
		.selector_map = c400_selectors,
	पूर्ण,
	अणु
		.id = USB_ID(0x08bb, 0x2702),
		.map = linex_map,
		.ignore_ctl_error = 1,
	पूर्ण,
	अणु
		.id = USB_ID(0x0a92, 0x0091),
		.map = maya44_map,
	पूर्ण,
	अणु
		.id = USB_ID(0x0c45, 0x1158),
		.map = justlink_map,
	पूर्ण,
	अणु
		.id = USB_ID(0x0ccd, 0x0028),
		.map = aureon_51_2_map,
	पूर्ण,
	अणु
		.id = USB_ID(0x0bda, 0x4014),
		.map = dell_alc4020_map,
	पूर्ण,
	अणु
		.id = USB_ID(0x0dba, 0x1000),
		.map = mbox1_map,
	पूर्ण,
	अणु
		.id = USB_ID(0x13e5, 0x0001),
		.map = scratch_live_map,
		.ignore_ctl_error = 1,
	पूर्ण,
	अणु
		.id = USB_ID(0x200c, 0x1018),
		.map = ebox44_map,
	पूर्ण,
	अणु
		/* MAYA44 USB+ */
		.id = USB_ID(0x2573, 0x0008),
		.map = maya44_map,
	पूर्ण,
	अणु
		/* KEF X300A */
		.id = USB_ID(0x27ac, 0x1000),
		.map = scms_usb3318_map,
	पूर्ण,
	अणु
		/* Arcam rPAC */
		.id = USB_ID(0x25c4, 0x0003),
		.map = scms_usb3318_map,
	पूर्ण,
	अणु
		/* Bose Companion 5 */
		.id = USB_ID(0x05a7, 0x1020),
		.map = bose_companion5_map,
	पूर्ण,
	अणु
		/* Corsair Virtuoso SE (wired mode) */
		.id = USB_ID(0x1b1c, 0x0a3d),
		.map = corsair_virtuoso_map,
	पूर्ण,
	अणु
		/* Corsair Virtuoso SE (wireless mode) */
		.id = USB_ID(0x1b1c, 0x0a3e),
		.map = corsair_virtuoso_map,
	पूर्ण,
	अणु
		/* Corsair Virtuoso (wired mode) */
		.id = USB_ID(0x1b1c, 0x0a41),
		.map = corsair_virtuoso_map,
	पूर्ण,
	अणु
		/* Corsair Virtuoso (wireless mode) */
		.id = USB_ID(0x1b1c, 0x0a42),
		.map = corsair_virtuoso_map,
	पूर्ण,
	अणु	/* Gigabyte TRX40 Aorus Master (rear panel + front mic) */
		.id = USB_ID(0x0414, 0xa001),
		.map = aorus_master_alc1220vb_map,
	पूर्ण,
	अणु	/* Gigabyte TRX40 Aorus Pro WiFi */
		.id = USB_ID(0x0414, 0xa002),
		.map = trx40_mobo_map,
		.connector_map = trx40_mobo_connector_map,
	पूर्ण,
	अणु	/* ASUS ROG Zenith II */
		.id = USB_ID(0x0b05, 0x1916),
		.map = asus_rog_map,
	पूर्ण,
	अणु	/* ASUS ROG Strix */
		.id = USB_ID(0x0b05, 0x1917),
		.map = trx40_mobo_map,
		.connector_map = trx40_mobo_connector_map,
	पूर्ण,
	अणु	/* MSI TRX40 Creator */
		.id = USB_ID(0x0db0, 0x0d64),
		.map = trx40_mobo_map,
		.connector_map = trx40_mobo_connector_map,
	पूर्ण,
	अणु	/* MSI TRX40 */
		.id = USB_ID(0x0db0, 0x543d),
		.map = trx40_mobo_map,
		.connector_map = trx40_mobo_connector_map,
	पूर्ण,
	अणु	/* Asrock TRX40 Creator */
		.id = USB_ID(0x26ce, 0x0a01),
		.map = trx40_mobo_map,
		.connector_map = trx40_mobo_connector_map,
	पूर्ण,
	अणु	/* Lenovo ThinkStation P620 Rear */
		.id = USB_ID(0x17aa, 0x1046),
		.map = lenovo_p620_rear_map,
	पूर्ण,
	अणु
		/* Sennheiser Communications Headset [PC 8] */
		.id = USB_ID(0x1395, 0x0025),
		.map = sennheiser_pc8_map,
	पूर्ण,
	अणु 0 पूर्ण /* terminator */
पूर्ण;

/*
 * Control map entries क्रम UAC3 BADD profiles
 */

अटल स्थिर काष्ठा usbmix_name_map uac3_badd_generic_io_map[] = अणु
	अणु UAC3_BADD_FU_ID2, "Generic Out Playback" पूर्ण,
	अणु UAC3_BADD_FU_ID5, "Generic In Capture" पूर्ण,
	अणु 0 पूर्ण					/* terminator */
पूर्ण;
अटल स्थिर काष्ठा usbmix_name_map uac3_badd_headphone_map[] = अणु
	अणु UAC3_BADD_FU_ID2, "Headphone Playback" पूर्ण,
	अणु 0 पूर्ण					/* terminator */
पूर्ण;
अटल स्थिर काष्ठा usbmix_name_map uac3_badd_speaker_map[] = अणु
	अणु UAC3_BADD_FU_ID2, "Speaker Playback" पूर्ण,
	अणु 0 पूर्ण					/* terminator */
पूर्ण;
अटल स्थिर काष्ठा usbmix_name_map uac3_badd_microphone_map[] = अणु
	अणु UAC3_BADD_FU_ID5, "Mic Capture" पूर्ण,
	अणु 0 पूर्ण					/* terminator */
पूर्ण;
/* Covers also 'headset adapter' profile */
अटल स्थिर काष्ठा usbmix_name_map uac3_badd_headset_map[] = अणु
	अणु UAC3_BADD_FU_ID2, "Headset Playback" पूर्ण,
	अणु UAC3_BADD_FU_ID5, "Headset Capture" पूर्ण,
	अणु UAC3_BADD_FU_ID7, "Sidetone Mixing" पूर्ण,
	अणु 0 पूर्ण					/* terminator */
पूर्ण;
अटल स्थिर काष्ठा usbmix_name_map uac3_badd_speakerphone_map[] = अणु
	अणु UAC3_BADD_FU_ID2, "Speaker Playback" पूर्ण,
	अणु UAC3_BADD_FU_ID5, "Mic Capture" पूर्ण,
	अणु 0 पूर्ण					/* terminator */
पूर्ण;

अटल स्थिर काष्ठा usbmix_ctl_map uac3_badd_usbmix_ctl_maps[] = अणु
	अणु
		.id = UAC3_FUNCTION_SUBCLASS_GENERIC_IO,
		.map = uac3_badd_generic_io_map,
	पूर्ण,
	अणु
		.id = UAC3_FUNCTION_SUBCLASS_HEADPHONE,
		.map = uac3_badd_headphone_map,
	पूर्ण,
	अणु
		.id = UAC3_FUNCTION_SUBCLASS_SPEAKER,
		.map = uac3_badd_speaker_map,
	पूर्ण,
	अणु
		.id = UAC3_FUNCTION_SUBCLASS_MICROPHONE,
		.map = uac3_badd_microphone_map,
	पूर्ण,
	अणु
		.id = UAC3_FUNCTION_SUBCLASS_HEADSET,
		.map = uac3_badd_headset_map,
	पूर्ण,
	अणु
		.id = UAC3_FUNCTION_SUBCLASS_HEADSET_ADAPTER,
		.map = uac3_badd_headset_map,
	पूर्ण,
	अणु
		.id = UAC3_FUNCTION_SUBCLASS_SPEAKERPHONE,
		.map = uac3_badd_speakerphone_map,
	पूर्ण,
	अणु 0 पूर्ण /* terminator */
पूर्ण;
