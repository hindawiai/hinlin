<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * device driver क्रम philips saa7134 based TV cards
 * card-specअगरic stuff.
 *
 * (c) 2001-04 Gerd Knorr <kraxel@bytesex.org> [SuSE Lअसल]
 */

#समावेश "saa7134.h"
#समावेश "saa7134-reg.h"

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>

#समावेश "tuner-xc2028.h"
#समावेश <media/v4l2-common.h>
#समावेश <media/tveeprom.h>
#समावेश "tea5767.h"
#समावेश "tda18271.h"
#समावेश "xc5000.h"
#समावेश "s5h1411.h"

/* Input names */
स्थिर अक्षर * स्थिर saa7134_input_name[] = अणु
	[SAA7134_INPUT_MUTE]       = "mute",
	[SAA7134_INPUT_RADIO]      = "Radio",
	[SAA7134_INPUT_TV]         = "Television",
	[SAA7134_INPUT_TV_MONO]    = "TV (mono only)",
	[SAA7134_INPUT_COMPOSITE]  = "Composite",
	[SAA7134_INPUT_COMPOSITE0] = "Composite0",
	[SAA7134_INPUT_COMPOSITE1] = "Composite1",
	[SAA7134_INPUT_COMPOSITE2] = "Composite2",
	[SAA7134_INPUT_COMPOSITE3] = "Composite3",
	[SAA7134_INPUT_COMPOSITE4] = "Composite4",
	[SAA7134_INPUT_SVIDEO]     = "S-Video",
	[SAA7134_INPUT_SVIDEO0]    = "S-Video0",
	[SAA7134_INPUT_SVIDEO1]    = "S-Video1",
	[SAA7134_INPUT_COMPOSITE_OVER_SVIDEO] = "Composite over S-Video",
पूर्ण;

/* ------------------------------------------------------------------ */
/* board config info                                                  */

अटल काष्ठा tda18271_std_map aver_a706_std_map = अणु
	.fm_radio = अणु .अगर_freq = 5500, .fm_rfn = 0, .agc_mode = 3, .std = 0,
		      .अगर_lvl = 0, .rfagc_top = 0x2c, पूर्ण,
पूर्ण;

/* If radio_type !=UNSET, radio_addr should be specअगरied
 */

काष्ठा saa7134_board saa7134_boards[] = अणु
	[SAA7134_BOARD_UNKNOWN] = अणु
		.name		= "UNKNOWN/GENERIC",
		.audio_घड़ी	= 0x00187de7,
		.tuner_type	= TUNER_ABSENT,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,

		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE,
			.vmux = 0,
			.amux = LINE1,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_PROTEUS_PRO] = अणु
		/* /me */
		.name		= "Proteus Pro [philips reference design]",
		.audio_घड़ी	= 0x00187de7,
		.tuner_type	= TUNER_PHILIPS_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,

		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 1,
			.amux = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_FLYVIDEO3000] = अणु
		/* "Marco d'Itri" <md@Linux.IT> */
		.name		= "LifeView FlyVIDEO3000",
		.audio_घड़ी	= 0x00200000,
		.tuner_type	= TUNER_PHILIPS_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,

		.gpiomask       = 0xe000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x8000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 1,
			.amux = LINE2,
			.gpio = 0x0000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
			.gpio = 0x4000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE2,
			.gpio = 0x4000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
			.gpio = 0x4000,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
			.gpio = 0x2000,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
			.gpio = 0x8000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_FLYVIDEO2000] = अणु
		/* "TC Wan" <tcwan@cs.usm.my> */
		.name           = "LifeView/Typhoon FlyVIDEO2000",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_LG_PAL_NEW_TAPC,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,

		.gpiomask       = 0xe000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2,
			.gpio = 0x0000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
			.gpio = 0x4000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE2,
			.gpio = 0x4000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
			.gpio = 0x4000,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
			.gpio = 0x2000,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE2,
			.gpio = 0x8000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_FLYTVPLATINUM_MINI] = अणु
		/* "Arnaud Quette" <aquette@मुक्त.fr> */
		.name           = "LifeView FlyTV Platinum Mini",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,

		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_FLYTVPLATINUM_FM] = अणु
		/* LअगरeView FlyTV Platinum FM (LR214WF) */
		/* "Peter Missel <peter.missel@onlinehome.de> */
		.name           = "LifeView FlyTV Platinum FM / Gold",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,

		.gpiomask       = 0x1E000,	/* Set GP16 and unused 15,14,13 to Output */
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x10000,	/* GP16=1 selects TV input */
		पूर्ण,अणु
/*			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 1,
			.amux = LINE2,
			.gpio = 0x0000,
		पूर्ण,अणु
*/			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux = 0,
			.amux = LINE2,
/*			.gpio = 0x4000,         */
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE,
			.vmux = 3,
			.amux = LINE2,
/*			.gpio = 0x4000,         */
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
/*			.gpio = 0x4000,         */
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x00000,	/* GP16=0 selects FM radio antenna */
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
			.gpio = 0x10000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ROVERMEDIA_LINK_PRO_FM] = अणु
		/* RoverMedia TV Link Pro FM (LR138 REV:I) */
		/* Eugene Yudin <Eugene.Yudin@gmail.com> */
		.name		= "RoverMedia TV Link Pro FM",
		.audio_घड़ी	= 0x00200000,
		.tuner_type	= TUNER_PHILIPS_FM1216ME_MK3, /* TCL MFPE05 2 */
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0xe000,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x8000,
		पूर्ण, अणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 1,
			.amux = LINE2,
			.gpio = 0x0000,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
			.gpio = 0x4000,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE2,
			.gpio = 0x4000,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
			.gpio = 0x4000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
			.gpio = 0x2000,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
			.gpio = 0x8000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_EMPRESS] = अणु
		/* "Gert Vervoort" <gert.vervoort@philips.com> */
		.name		= "EMPRESS",
		.audio_घड़ी	= 0x00187de7,
		.tuner_type	= TUNER_PHILIPS_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.empress_addr	= 0x20,

		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
		.mpeg      = SAA7134_MPEG_EMPRESS,
		.video_out = CCIR656,
	पूर्ण,
	[SAA7134_BOARD_MONSTERTV] = अणु
		/* "K.Ohta" <alpha292@bremen.or.jp> */
		.name           = "SKNet Monster TV",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_NTSC_M,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,

		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_MD9717] = अणु
		.name		= "Tevion MD 9717",
		.audio_घड़ी	= 0x00200000,
		.tuner_type	= TUNER_PHILIPS_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			/* workaround क्रम problems with normal TV sound */
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	       .mute = अणु
		       .type = SAA7134_INPUT_MUTE,
		       .amux = TV,
	       पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_TVSTATION_RDS] = अणु
		/* Typhoon TV Tuner RDS: Art.Nr. 50694 */
		.name		= "KNC One TV-Station RDS / Typhoon TV Tuner RDS",
		.audio_घड़ी	= 0x00200000,
		.tuner_type	= TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 1,
			.amux   = LINE2,
		पूर्ण,अणु

			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण,अणु

			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux = 0,
			.amux = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_TVSTATION_DVR] = अणु
		.name		= "KNC One TV-Station DVR",
		.audio_घड़ी	= 0x00200000,
		.tuner_type	= TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.empress_addr	= 0x20,
		.tda9887_conf	= TDA9887_PRESENT,
		.gpiomask	= 0x820000,
		.inमाला_दो		= अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x20000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
			.gpio = 0x20000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
			.gpio = 0x20000,
		पूर्णपूर्ण,
		.radio		= अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
			.gpio = 0x20000,
		पूर्ण,
		.mpeg           = SAA7134_MPEG_EMPRESS,
		.video_out	= CCIR656,
	पूर्ण,
	[SAA7134_BOARD_CINERGY400] = अणु
		.name           = "Terratec Cinergy 400 TV",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE,
			.vmux = 4,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux = 0,
			.amux = LINE1,
		पूर्णपूर्ण
	पूर्ण,
	[SAA7134_BOARD_MD5044] = अणु
		.name           = "Medion 5044",
		.audio_घड़ी    = 0x00187de7, /* was: 0x00200000, */
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			/* workaround क्रम problems with normal TV sound */
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_KWORLD] = अणु
		.name           = "Kworld/KuroutoShikou SAA7130-TVPCI",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_NTSC_M,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_CINERGY600] = अणु
		.name           = "Terratec Cinergy 600 TV",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 4,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux = 0,
			.amux = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_MD7134] = अणु
		.name           = "Medion 7134",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FMD1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 0,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = LINE2,
	       पूर्ण,
	       .mute = अणु
		       .type = SAA7134_INPUT_MUTE,
		       .amux = TV,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_TYPHOON_90031] = अणु
		/* aka Typhoon "TV+Radio", Art.Nr 90031 */
		/* Tom Zoerner <tomzo at users sourceक्रमge net> */
		.name           = "Typhoon TV+Radio 90031",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 3,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ELSA] = अणु
		.name           = "ELSA EX-VISION 300TV",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_HITACHI_NTSC,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 0,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 4,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ELSA_500TV] = अणु
		.name           = "ELSA EX-VISION 500TV",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_HITACHI_NTSC,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 7,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 8,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ELSA_700TV] = अणु
		.name           = "ELSA EX-VISION 700TV",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_HITACHI_NTSC,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 4,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 6,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 7,
			.amux = LINE1,
		पूर्णपूर्ण,
		.mute           = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ASUSTeK_TVFM7134] = अणु
		.name           = "ASUS TV-FM 7134",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 4,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 6,
			.amux = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE1,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ASUSTeK_TVFM7135] = अणु
		.name           = "ASUS TV-FM 7135",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask       = 0x200000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x0000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 4,
			.amux = LINE2,
			.gpio = 0x0000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 6,
			.amux = LINE2,
			.gpio = 0x0000,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x200000,
		पूर्ण,
		.mute  = अणु
			.type = SAA7134_INPUT_MUTE,
			.gpio = 0x0000,
		पूर्ण,

	पूर्ण,
	[SAA7134_BOARD_VA1000POWER] = अणु
		.name           = "AOPEN VA1000 POWER",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_NTSC,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_10MOONSTVMASTER] = अणु
		/* "lilicheng" <llc@linuxfans.org> */
		.name           = "10MOONS PCI TV CAPTURE CARD",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_LG_PAL_NEW_TAPC,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask       = 0xe000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2,
			.gpio = 0x0000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
			.gpio = 0x4000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE2,
			.gpio = 0x4000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
			.gpio = 0x4000,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
			.gpio = 0x2000,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE2,
			.gpio = 0x8000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BMK_MPEX_NOTUNER] = अणु
		/* "Andrew de Quincey" <adq@lidskialf.net> */
		.name		= "BMK MPEX No Tuner",
		.audio_घड़ी	= 0x200000,
		.tuner_type	= TUNER_ABSENT,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.empress_addr	= 0x20,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 4,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE3,
			.vmux = 0,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE4,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्णपूर्ण,
		.mpeg      = SAA7134_MPEG_EMPRESS,
		.video_out = CCIR656,
	पूर्ण,
	[SAA7134_BOARD_VIDEOMATE_TV] = अणु
		.name           = "Compro VideoMate TV",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_NTSC_M,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_VIDEOMATE_TV_GOLD_PLUS] = अणु
		.name           = "Compro VideoMate TV Gold+",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_NTSC_M,
		.gpiomask       = 0x800c0000,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
			.gpio = 0x06c00012,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
			.gpio = 0x0ac20012,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2,
			.gpio = 0x08c20012,
		पूर्णपूर्ण,				/* radio and probably mute is missing */
	पूर्ण,
	[SAA7134_BOARD_CRONOS_PLUS] = अणु
		/*
		gpio pins:
			0  .. 3   BASE_ID
			4  .. 7   PROTECT_ID
			8  .. 11  USER_OUT
			12 .. 13  USER_IN
			14 .. 15  VIDIN_SEL
		*/
		.name           = "Matrox CronosPlus",
		.tuner_type     = TUNER_ABSENT,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask       = 0xcf00,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.gpio = 2 << 14,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 0,
			.gpio = 1 << 14,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE3,
			.vmux = 0,
			.gpio = 0 << 14,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE4,
			.vmux = 0,
			.gpio = 3 << 14,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.gpio = 2 << 14,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_MD2819] = अणु
		.name           = "AverMedia M156 / Medion 2819",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask	= 0x03,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x00,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
			.gpio = 0x02,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 0,
			.amux = LINE1,
			.gpio = 0x02,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
			.gpio = 0x02,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE1,
			.gpio = 0x01,
		पूर्ण,
		.mute  = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
			.gpio = 0x00,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BMK_MPEX_TUNER] = अणु
		/* "Greg Wickham <greg.wickham@grangenet.net> */
		.name           = "BMK MPEX Tuner",
		.audio_घड़ी    = 0x200000,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.empress_addr	= 0x20,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्णपूर्ण,
		.mpeg      = SAA7134_MPEG_EMPRESS,
		.video_out = CCIR656,
	पूर्ण,
	[SAA7134_BOARD_ASUSTEK_TVFM7133] = अणु
		.name           = "ASUS TV-FM 7133",
		.audio_घड़ी    = 0x00187de7,
		/* probably wrong, the 7133 one is the NTSC version ...
		* .tuner_type  = TUNER_PHILIPS_FM1236_MK3 */
		.tuner_type     = TUNER_LG_NTSC_NEW_TAPC,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,

		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 4,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 6,
			.amux = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE1,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_PINNACLE_PCTV_STEREO] = अणु
		.name           = "Pinnacle PCTV Stereo (saa7134)",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_MT2032,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT | TDA9887_INTERCARRIER | TDA9887_PORT2_INACTIVE,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_MANLI_MTV002] = अणु
		/* Ognjen Nastic <ognjen@logosoft.ba> */
		.name           = "Manli MuchTV M-TV002",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 1,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_MANLI_MTV001] = अणु
		/* Ognjen Nastic <ognjen@logosoft.ba> UNTESTED */
		.name           = "Manli MuchTV M-TV001",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = LINE2,
		पूर्णपूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE1,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_TG3000TV] = अणु
		/* TransGear 3000TV */
		.name           = "Nagase Sangyo TransGear 3000TV",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_NTSC_M,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ECS_TVP3XP] = अणु
		.name           = "Elitegroup ECS TVP3XP FM1216 Tuner Card(PAL-BG,FM) ",
		.audio_घड़ी    = 0x187de7,  /* xtal 32.1 MHz */
		.tuner_type     = TUNER_PHILIPS_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux   = 1,
			.amux   = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 3,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux   = 0,
			.amux   = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ECS_TVP3XP_4CB5] = अणु
		.name           = "Elitegroup ECS TVP3XP FM1236 Tuner Card (NTSC,FM)",
		.audio_घड़ी    = 0x187de7,
		.tuner_type     = TUNER_PHILIPS_NTSC,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux   = 1,
			.amux   = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 3,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux   = 0,
			.amux   = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = LINE2,
		पूर्ण,
	पूर्ण,
    [SAA7134_BOARD_ECS_TVP3XP_4CB6] = अणु
		/* Barry Scott <barry.scott@onelan.co.uk> */
		.name		= "Elitegroup ECS TVP3XP FM1246 Tuner Card (PAL,FM)",
		.audio_घड़ी    = 0x187de7,
		.tuner_type     = TUNER_PHILIPS_PAL_I,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux   = 1,
			.amux   = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 3,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux   = 0,
			.amux   = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVACSSMARTTV] = अणु
		/* Roman Pszonczenko <romka@kolos.math.uni.lodz.pl> */
		.name           = "AVACS SmartTV",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
			.gpio = 0x200000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_DVD_EZMAKER] = अणु
		/* Michael Smith <msmith@cbnco.com> */
		.name           = "AVerMedia DVD EZMaker",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_ABSENT,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_M103] = अणु
		/* Massimo Piccioni <dafastidio@libero.it> */
		.name           = "AVerMedia MiniPCI DVB-T Hybrid M103",
		.audio_घड़ी    = 0x187de7,
		.tuner_type     = TUNER_XC2028,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		 .mpeg           = SAA7134_MPEG_DVB,
		 .inमाला_दो         = अणुअणु
			 .type = SAA7134_INPUT_TV,
			 .vmux = 1,
			 .amux = TV,
		 पूर्ण पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_NOVAC_PRIMETV7133] = अणु
		/* toshii@netbsd.org */
		.name           = "Noval Prime TV 7133",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_ALPS_TSBH1_NTSC,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_STUDIO_305] = अणु
		.name           = "AverMedia AverTV Studio 305",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1256_IH3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE1,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_STUDIO_505] = अणु
		/* Vasiliy Temnikov <vaka@newmail.ru> */
		.name           = "AverMedia AverTV Studio 505",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE1,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_UPMOST_PURPLE_TV] = अणु
		.name           = "UPMOST PURPLE TV",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1236_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 7,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 7,
			.amux = LINE1,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ITEMS_MTV005] = अणु
		/* Norman Jonas <normanjonas@arcor.de> */
		.name           = "Items MuchTV Plus / IT-005",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 1,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_CINERGY200] = अणु
		.name           = "Terratec Cinergy 200 TV",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 4,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux = 0,
			.amux = LINE1,
		पूर्णपूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_VIDEOMATE_TV_PVR] = अणु
		/* Alain St-Denis <alain@topaze.homeip.net> */
		.name           = "Compro VideoMate TV PVR/FM",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_NTSC_M,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask	= 0x808c0080,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
			.gpio = 0x00080,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
			.gpio = 0x00080,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2_LEFT,
			.gpio = 0x00080,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
			.gpio = 0x80000,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE2,
			.gpio = 0x40000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_SABRENT_SBTTVFM] = अणु
		/* Michael Rodriguez-Torrent <mrtorrent@asu.edu> */
		.name           = "Sabrent SBT-TVFM (saa7130)",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_NTSC_M,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ZOLID_XPERT_TV7134] = अणु
		/* Helge Jensen <helge.jensen@slog.dk> */
		.name           = ":Zolid Xpert TV7134",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_NTSC,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_EMPIRE_PCI_TV_RADIO_LE] = अणु
		/* "Matteo Az" <matte.az@nospam.libero.it> ;-) */
		.name           = "Empire PCI TV-Radio LE",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask       = 0x4000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 1,
			.amux = LINE2,
			.gpio = 0x8000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
			.gpio = 0x8000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 6,
			.amux = LINE1,
			.gpio = 0x8000,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE1,
			.gpio = 0x8000,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
			.gpio =0x8000,
		पूर्ण
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_STUDIO_307] = अणु
		/*
		Nickolay V. Shmyrev <nshmyrev@yandex.ru>
		Lots of thanks to Andrey Zolotarev <zolotarev_andrey@mail.ru>
		*/
		.name           = "Avermedia AVerTV Studio 307",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1256_IH3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0x03,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x00,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE,
			.vmux = 3,
			.amux = LINE1,
			.gpio = 0x02,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
			.gpio = 0x02,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE1,
			.gpio = 0x01,
		पूर्ण,
		.mute  = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE1,
			.gpio = 0x00,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_GO_007_FM] = अणु
		.name           = "Avermedia AVerTV GO 007 FM",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask       = 0x00300003,
		/* .gpiomask       = 0x8c240003, */
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x01,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE1,
			.gpio = 0x02,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 6,
			.amux = LINE1,
			.gpio = 0x02,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x00300001,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
			.gpio = 0x01,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_CARDBUS] = अणु
		/* Kees.Blom@cwi.nl */
		.name           = "AVerMedia Cardbus TV/Radio (E500)",
		.audio_घड़ी    = 0x187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE1,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_CARDBUS_501] = अणु
		/* Oldrich Jedlicka <oldium.pro@seznam.cz> */
		.name           = "AVerMedia Cardbus TV/Radio (E501R)",
		.audio_घड़ी    = 0x187de7,
		.tuner_type     = TUNER_ALPS_TSBE5_PAL,
		.radio_type     = TUNER_TEA5767,
		.tuner_addr	= 0x61,
		.radio_addr	= 0x60,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0x08000000,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x08000000,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
			.gpio = 0x08000000,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
			.gpio = 0x08000000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
			.gpio = 0x00000000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_CINERGY400_CARDBUS] = अणु
		.name           = "Terratec Cinergy 400 mobile",
		.audio_घड़ी    = 0x187de7,
		.tuner_type     = TUNER_ALPS_TSBE5_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_CINERGY600_MK3] = अणु
		.name           = "Terratec Cinergy 600 TV MK3",
		.audio_घड़ी    = 0x00200000,
		.tuner_type	= TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.rds_addr	= 0x10,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 4,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux = 0,
			.amux = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_VIDEOMATE_GOLD_PLUS] = अणु
		/* Dylan Walkden <dylan_walkden@hoपंचांगail.com> */
		.name		= "Compro VideoMate Gold+ Pal",
		.audio_घड़ी	= 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_PAL,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask	= 0x1ce780,
		.inमाला_दो		= अणुअणु
			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux = 0,
			.amux = LINE1,
			.gpio = 0x008080,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
			.gpio = 0x008080,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x008080,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
			.gpio = 0x80000,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE2,
			.gpio = 0x0c8000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_PINNACLE_300I_DVBT_PAL] = अणु
		.name           = "Pinnacle PCTV 300i DVB-T + PAL",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_MT2032,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT | TDA9887_INTERCARRIER | TDA9887_PORT2_INACTIVE,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_PROVIDEO_PV952] = अणु
		/* andreas.kretschmer@web.de */
		.name		= "ProVideo PV952",
		.audio_घड़ी	= 0x00187de7,
		.tuner_type	= TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 1,
			.amux = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_305] = अणु
		/* much like the "studio" version but without radio
		* and another tuner (sirspiritus@yandex.ru) */
		.name           = "AverMedia AverTV/305",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FQ1216ME,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE1,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_FLYDVBTDUO] = अणु
		/* LअगरeView FlyDVB-T DUO */
		/* "Nico Sabbi <nsabbi@tiscali.it>  Harपंचांगut Hackmann harपंचांगut.hackmann@t-online.de*/
		.name           = "LifeView FlyDVB-T DUO / MSI TV@nywhere Duo",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask	= 0x00200000,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x200000,	/* GPIO21=High क्रम TV input */
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x000000,	/* GPIO21=Low क्रम FM radio antenna */
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_PHILIPS_TOUGH] = अणु
		.name           = "Philips TOUGH DVB-T reference design",
		.tuner_type	= TUNER_ABSENT,
		.audio_घड़ी    = 0x00187de7,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 0,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_307] = अणु
		/*
		Davyकरोv Vladimir <vladimir@iqmedia.com>
		*/
		.name           = "Avermedia AVerTV 307",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FQ1216ME,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ADS_INSTANT_TV] = अणु
		.name           = "ADS Tech Instant TV (saa7135)",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_KWORLD_VSTREAM_XPERT] = अणु
		.name           = "Kworld/Tevion V-Stream Xpert TV PVR7134",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_PAL_I,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask	= 0x0700,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
			.gpio   = 0x000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 3,
			.amux   = LINE1,
			.gpio   = 0x200,		/* gpio by DScaler */
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 0,
			.amux   = LINE1,
			.gpio   = 0x200,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = LINE1,
			.gpio   = 0x100,
		पूर्ण,
		.mute  = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
			.gpio = 0x000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_FLYDVBT_DUO_CARDBUS] = अणु
		.name		= "LifeView/Typhoon/Genius FlyDVB-T Duo Cardbus",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.gpiomask	= 0x00200000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x200000,	/* GPIO21=High क्रम TV input */
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x000000,	/* GPIO21=Low क्रम FM radio antenna */
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_VIDEOMATE_TV_GOLD_PLUSII] = अणु
		.name           = "Compro VideoMate TV Gold+II",
		.audio_घड़ी    = 0x002187de7,
		.tuner_type     = TUNER_LG_PAL_NEW_TAPC,
		.radio_type     = TUNER_TEA5767,
		.tuner_addr     = 0x63,
		.radio_addr     = 0x60,
		.gpiomask       = 0x8c1880,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 0,
			.amux = LINE1,
			.gpio = 0x800800,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
			.gpio = 0x801000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x800000,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x880000,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE2,
			.gpio = 0x840000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_KWORLD_XPERT] = अणु
		/*
		FIXME:
		- Remote control करोesn't initialize properly.
		- Audio volume starts muted,
		then gradually increases after channel change.
		- Overlay scaling problems (application error?)
		- Composite S-Video untested.
		From: Konrad Rzepecki <hannibal@megapolis.pl>
		*/
		.name           = "Kworld Xpert TV PVR7134",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_TENA_9533_DI,
		.radio_type     = TUNER_TEA5767,
		.tuner_addr	= 0x61,
		.radio_addr	= 0x60,
		.gpiomask	= 0x0700,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
			.gpio   = 0x000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 3,
			.amux   = LINE1,
			.gpio   = 0x200,		/* gpio by DScaler */
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 0,
			.amux   = LINE1,
			.gpio   = 0x200,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = LINE1,
			.gpio   = 0x100,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
			.gpio = 0x000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_FLYTV_DIGIMATRIX] = अणु
		.name		= "FlyTV mini Asus Digimatrix",
		.audio_घड़ी	= 0x00200000,
		.tuner_type	= TUNER_LG_TALN,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,		/* radio unconfirmed */
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_KWORLD_TERMINATOR] = अणु
		/* Kworld V-Stream Studio TV Terminator */
		/* "James Webb <jrwebb@qwest.net> */
		.name           = "V-Stream Studio TV Terminator",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.gpiomask       = 1 << 21,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x0000000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE2,
			.gpio = 0x0000000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
			.gpio = 0x0000000,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x0200000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_YUAN_TUN900] = अणु
		/* FIXME:
		 * S-Video and composite sources untested.
		 * Radio not working.
		 * Remote control not yet implemented.
		 * From : codemaster@webgeeks.be */
		.name           = "Yuan TUN-900 (saa7135)",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr= ADDR_UNSET,
		.radio_addr= ADDR_UNSET,
		.gpiomask       = 0x00010003,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x01,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
			.gpio = 0x02,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 6,
			.amux = LINE2,
			.gpio = 0x02,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE1,
			.gpio = 0x00010003,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
			.gpio = 0x01,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_409FM] = अणु
		/* <http://tuner.beholder.ru>, Sergey <skiv@orel.ru> */
		/*       Beholder Intl. Ltd. 2008      */
		/*Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV 409 FM",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0x00008000,
		.inमाला_दो         = अणुअणु
			  .type = SAA7134_INPUT_TV,
			  .vmux = 3,
			  .amux = TV,
		पूर्ण,अणु
			  .type = SAA7134_INPUT_COMPOSITE1,
			  .vmux = 1,
			  .amux = LINE1,
		पूर्ण,अणु
			  .type = SAA7134_INPUT_SVIDEO,
			  .vmux = 8,
			  .amux = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			  .type = SAA7134_INPUT_RADIO,
			  .amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_GOTVIEW_7135] = अणु
		/* Mike Baikov <mike@baikov.com> */
		/* Andrey Cvetcov <ays14@yandex.ru> */
		.name            = "GoTView 7135 PCI",
		.audio_घड़ी     = 0x00187de7,
		.tuner_type      = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type      = UNSET,
		.tuner_addr      = ADDR_UNSET,
		.radio_addr      = ADDR_UNSET,
		.tda9887_conf    = TDA9887_PRESENT,
		.gpiomask        = 0x00200003,
		.inमाला_दो          = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x00200003,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 1,
			.amux = LINE2,
			.gpio = 0x00200003,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
			.gpio = 0x00200003,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
			.gpio = 0x00200003,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
			.gpio = 0x00200003,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
			.gpio = 0x00200003,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_PHILIPS_EUROPA] = अणु
		.name           = "Philips EUROPA V3 reference design",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TD1316,
		.radio_type     = UNSET,
		.tuner_addr	= 0x61,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT | TDA9887_PORT1_ACTIVE,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 3,
			.amux   = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 0,
			.amux   = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_VIDEOMATE_DVBT_300] = अणु
		.name           = "Compro Videomate DVB-T300",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TD1316,
		.radio_type     = UNSET,
		.tuner_addr	= 0x61,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT | TDA9887_PORT1_ACTIVE,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 3,
			.amux   = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 1,
			.amux   = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_VIDEOMATE_DVBT_200] = अणु
		.name           = "Compro Videomate DVB-T200",
		.tuner_type	= TUNER_ABSENT,
		.audio_घड़ी    = 0x00187de7,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 0,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_RTD_VFG7350] = अणु
		.name		= "RTD Embedded Technologies VFG7350",
		.audio_घड़ी	= 0x00200000,
		.tuner_type	= TUNER_ABSENT,
		.radio_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.empress_addr	= 0x21,
		.inमाला_दो		= अणुअणु
			.type = SAA7134_INPUT_COMPOSITE0,
			.vmux   = 0,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 1,
			.amux   = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux   = 2,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE3,
			.vmux   = 3,
			.amux   = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO0,

			.vmux   = 8,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO1,
			.vmux   = 9,
			.amux   = LINE2,
		पूर्णपूर्ण,
		.mpeg           = SAA7134_MPEG_EMPRESS,
		.video_out      = CCIR656,
		.vid_port_opts  = ( SET_T_CODE_POLARITY_NON_INVERTED |
				    SET_CLOCK_NOT_DELAYED |
				    SET_CLOCK_INVERTED |
				    SET_VSYNC_OFF ),
	पूर्ण,
	[SAA7134_BOARD_RTD_VFG7330] = अणु
		.name		= "RTD Embedded Technologies VFG7330",
		.audio_घड़ी	= 0x00200000,
		.tuner_type	= TUNER_ABSENT,
		.radio_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो		= अणुअणु
			.type = SAA7134_INPUT_COMPOSITE0,
			.vmux   = 0,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 1,
			.amux   = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux   = 2,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE3,
			.vmux   = 3,
			.amux   = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO0,
			.vmux   = 8,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO1,
			.vmux   = 9,
			.amux   = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_FLYTVPLATINUM_MINI2] = अणु
		.name           = "LifeView FlyTV Platinum Mini2",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,

		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_AVERTVHD_A180] = अणु
		/* Michael Krufky <mkrufky@linuxtv.org>
		 * Uses Alps Electric TDHU2, containing NXT2004 ATSC Decoder
		 * AFAIK, there is no analog demod, thus,
		 * no support क्रम analog television.
		 */
		.name           = "AVerMedia AVerTVHD MCE A180",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_ABSENT,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_MONSTERTV_MOBILE] = अणु
		.name           = "SKNet MonsterTV Mobile",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,

		.inमाला_दो         = अणुअणु
			  .type = SAA7134_INPUT_TV,
			  .vmux = 1,
			  .amux = TV,
		पूर्ण,अणु
			  .type = SAA7134_INPUT_COMPOSITE1,
			  .vmux = 3,
			  .amux = LINE1,
		पूर्ण,अणु
			  .type = SAA7134_INPUT_SVIDEO,
			  .vmux = 6,
			  .amux = LINE1,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_PINNACLE_PCTV_110i] = अणु
	       .name           = "Pinnacle PCTV 40i/50i/110i (saa7133)",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.gpiomask       = 0x080200000,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 4,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x0200000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ASUSTeK_P7131_DUAL] = अणु
		.name           = "ASUSTeK P7131 Dual",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask	= 1 << 21,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x0000000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE2,
			.gpio = 0x0200000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 0,
			.amux = LINE2,
			.gpio = 0x0200000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
			.gpio = 0x0200000,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x0200000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_SEDNA_PC_TV_CARDBUS] = अणु
		/* Paul Tom Zalac <pzalac@gmail.com> */
		/* Pavel Mihaylov <bin@bash.info> */
		.name           = "Sedna/MuchTV PC TV Cardbus TV/Radio (ITO25 Rev:2B)",
				/* Sedna/MuchTV (OEM) Cardbus TV Tuner */
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.gpiomask       = 0xe880c0,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 6,
			.amux = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ASUSTEK_DIGIMATRIX_TV] = अणु
		/* "Cyril Lacoux (Yack)" <clacoux@अगरeelgood.org> */
		.name           = "ASUS Digimatrix TV",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_FQ1216ME,
		.tda9887_conf   = TDA9887_PRESENT,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_PHILIPS_TIGER] = अणु
		.name           = "Philips Tiger reference design",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda829x_conf   = अणु .lna_cfg = TDA8290_LNA_OFF पूर्ण,
		.mpeg           = SAA7134_MPEG_DVB,
		.gpiomask       = 0x0200000,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 3,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = TV,
			.gpio   = 0x0200000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_MSI_TVATANYWHERE_PLUS] = अणु
		.name           = "MSI TV@Anywhere plus",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask       = 1 << 21,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE,
			.vmux   = 3,
			.amux   = LINE2,	/* unconfirmed, taken from Philips driver */
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux   = 0,		/* untested */
			.amux   = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = TV,
			.gpio   = 0x0200000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_CINERGY250PCI] = अणु
		/* remote-control करोes not work. The संकेत about a
		   key press comes in via gpio, but the key code
		   करोesn't. Neither करोes it have an i2c remote control
		   पूर्णांकerface. */
		.name           = "Terratec Cinergy 250 PCI TV",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask       = 0x80200000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,  /* NOT tested */
			.vmux = 8,
			.amux = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = TV,
			.gpio   = 0x0200000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_FLYDVB_TRIO] = अणु
		/* LअगरeView LR319 FlyDVB Trio */
		/* Peter Missel <peter.missel@onlinehome.de> */
		.name           = "LifeView FlyDVB Trio",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask	= 0x00200000,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,	/* Analog broadcast/cable TV */
			.vmux = 1,
			.amux = TV,
			.gpio = 0x200000,	/* GPIO21=High क्रम TV input */
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x000000,	/* GPIO21=Low क्रम FM radio antenna */
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_777] = अणु
		.name           = "AverTV DVB-T 777",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_ABSENT,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 1,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_FLYDVBT_LR301] = अणु
		/* LअगरeView FlyDVB-T */
		/* Giampiero Giancipoli <gianci@libero.it> */
		.name           = "LifeView FlyDVB-T / Genius VideoWonder DVB-T",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_ABSENT,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ADS_DUO_CARDBUS_PTV331] = अणु
		.name           = "ADS Instant TV Duo Cardbus PTV331",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.gpiomask       = 0x00600000, /* Bit 21 0=Radio, Bit 22 0=TV */
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
			.gpio   = 0x00200000,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_TEVION_DVBT_220RF] = अणु
		.name           = "Tevion/KWorld DVB-T 220RF",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.gpiomask       = 1 << 21,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 3,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux   = 0,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = TV,
			.gpio   = 0x0200000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_KWORLD_DVBT_210] = अणु
		.name           = "KWorld DVB-T 210",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.gpiomask       = 1 << 21,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 3,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = TV,
			.gpio   = 0x0200000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_KWORLD_ATSC110] = अणु
		.name           = "Kworld ATSC110/115",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TUV1236D,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_A169_B] = अणु
		/* AVerMedia A169  */
		/* Rickard Osser <ricky@osser.se>  */
		/* This card has two saa7134 chips on it,
		   but only one of them is currently working. */
		.name		= "AVerMedia A169 B",
		.audio_घड़ी    = 0x02187de7,
		.tuner_type	= TUNER_LG_TALN,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0x0a60000,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_A169_B1] = अणु
		/* AVerMedia A169 */
		/* Rickard Osser <ricky@osser.se> */
		.name		= "AVerMedia A169 B1",
		.audio_घड़ी    = 0x02187de7,
		.tuner_type	= TUNER_LG_TALN,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0xca60000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 4,
			.amux = TV,
			.gpio = 0x04a61000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 9,           /* 9 is correct as S-VIDEO1 according to a169.inf! */
			.amux = LINE1,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_MD7134_BRIDGE_2] = अणु
		/* The second saa7134 on this card only serves as DVB-S host bridge */
		.name           = "Medion 7134 Bridge #2",
		.audio_घड़ी    = 0x00187de7,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
	पूर्ण,
	[SAA7134_BOARD_FLYDVBT_HYBRID_CARDBUS] = अणु
		.name		= "LifeView FlyDVB-T Hybrid Cardbus/MSI TV @nywhere A/D NB",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.gpiomask       = 0x00600000, /* Bit 21 0=Radio, Bit 22 0=TV */
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x200000,	/* GPIO21=High क्रम TV input */
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE,
			.vmux = 3,
			.amux = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x000000,	/* GPIO21=Low क्रम FM radio antenna */
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_FLYVIDEO3000_NTSC] = अणु
		/* "Zac Bowling" <zac@zacbowling.com> */
		.name           = "LifeView FlyVIDEO3000 (NTSC)",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_NTSC,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,

		.gpiomask       = 0xe000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x8000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 1,
			.amux = LINE2,
			.gpio = 0x0000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
			.gpio = 0x4000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE2,
			.gpio = 0x4000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
			.gpio = 0x4000,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
			.gpio = 0x2000,
		पूर्ण,
			.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
			.gpio = 0x8000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_MEDION_MD8800_QUADRO] = अणु
		.name           = "Medion Md8800 Quadro",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 0,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_FLYDVBS_LR300] = अणु
		/* LअगरeView FlyDVB-s */
		/* Igor M. Liplianin <liplianin@tut.by> */
		.name           = "LifeView FlyDVB-S /Acorp TV134DS",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_ABSENT,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_PROTEUS_2309] = अणु
		.name           = "Proteus Pro 2309",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type	= TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE1,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_A16AR] = अणु
		/* Petr Baudis <pasky@ucw.cz> */
		.name           = "AVerMedia TV Hybrid A16AR",
		.audio_घड़ी    = 0x187de7,
		.tuner_type     = TUNER_PHILIPS_TD1316, /* untested */
		.radio_type     = TUNER_TEA5767, /* untested */
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = 0x60,
		.tda9887_conf   = TDA9887_PRESENT,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE1,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ASUS_EUROPA2_HYBRID] = अणु
		.name           = "Asus Europa2 OEM",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FMD1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT| TDA9887_PORT1_ACTIVE | TDA9887_PORT2_ACTIVE,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 3,
			.amux   = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 4,
			.amux   = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = LINE1,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_PINNACLE_PCTV_310i] = अणु
		.name           = "Pinnacle PCTV 310i",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda829x_conf   = अणु .lna_cfg = TDA8290_LNA_GP0_HIGH_ON पूर्ण,
		.mpeg           = SAA7134_MPEG_DVB,
		.gpiomask       = 0x000200000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 4,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = TV,
			.gpio   = 0x0200000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_STUDIO_507] = अणु
		/* Mikhail Feकरोtov <mo_feकरोtov@mail.ru> */
		.name           = "Avermedia AVerTV Studio 507",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1256_IH3,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0x03,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x00,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
			.gpio = 0x00,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE2,
			.gpio = 0x00,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
			.gpio = 0x00,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
			.gpio = 0x01,
		पूर्ण,
		.mute  = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE1,
			.gpio = 0x00,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_VIDEOMATE_DVBT_200A] = अणु
		/* Francis Barber <feकरोra@barber-family.id.au> */
		.name           = "Compro Videomate DVB-T200A",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_ABSENT,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT | TDA9887_PORT1_ACTIVE,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 3,
			.amux   = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 1,
			.amux   = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_HAUPPAUGE_HVR1110] = अणु
		/* Thomas Genty <tomlohave@gmail.com> */
		/* David Bentham <db260179@hoपंचांगail.com> */
		.name           = "Hauppauge WinTV-HVR1110 DVB-T/Hybrid",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda829x_conf   = अणु .lna_cfg = TDA8290_LNA_GP0_HIGH_ON पूर्ण,
		.mpeg           = SAA7134_MPEG_DVB,
		.gpiomask       = 0x0200100,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x0000100,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x0200100,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_HAUPPAUGE_HVR1150] = अणु
		.name           = "Hauppauge WinTV-HVR1150 ATSC/QAM-Hybrid",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda829x_conf   = अणु .lna_cfg = TDA8290_LNA_ON_BRIDGE पूर्ण,
		.mpeg           = SAA7134_MPEG_DVB,
		.ts_type	= SAA7134_MPEG_TS_SERIAL,
		.ts_क्रमce_val   = 1,
		.gpiomask       = 0x0800100, /* GPIO 21 is an INPUT */
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x0000100,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x0800100, /* GPIO 23 HI क्रम FM */
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_HAUPPAUGE_HVR1120] = अणु
		.name           = "Hauppauge WinTV-HVR1120 DVB-T/Hybrid",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda829x_conf   = अणु .lna_cfg = TDA8290_LNA_ON_BRIDGE पूर्ण,
		.mpeg           = SAA7134_MPEG_DVB,
		.ts_type	= SAA7134_MPEG_TS_SERIAL,
		.gpiomask       = 0x0800100, /* GPIO 21 is an INPUT */
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x0000100,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x0800100, /* GPIO 23 HI क्रम FM */
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_CINERGY_HT_PCMCIA] = अणु
		.name           = "Terratec Cinergy HT PCMCIA",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 0,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 6,
			.amux   = LINE1,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ENCORE_ENLTV] = अणु
	/* Steven Walter <stevenrwalter@gmail.com>
	   Juan Pablo Sormani <sorman@gmail.com> */
		.name           = "Encore ENLTV",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_TNF_5335MF,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = 3,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 7,
			.amux = 4,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = 2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 0,
			.amux = 2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
/*			.gpio = 0x00300001,*/
			.gpio = 0x20000,

		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = 0,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ENCORE_ENLTV_FM] = अणु
  /*	Juan Pablo Sormani <sorman@gmail.com> */
		.name           = "Encore ENLTV-FM",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_FCV1236D,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = 3,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 7,
			.amux = 4,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = 2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 0,
			.amux = 2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
			.gpio = 0x20000,

		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = 0,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ENCORE_ENLTV_FM53] = अणु
		.name           = "Encore ENLTV-FM v5.3",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_TNF_5335MF,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask	= 0x7000,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = 1,
			.gpio = 0x50000,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = 2,
			.gpio = 0x2000,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = 2,
			.gpio = 0x2000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.vmux = 1,
			.amux = 1,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.gpio = 0xf000,
			.amux = 0,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ENCORE_ENLTV_FM3] = अणु
		.name           = "Encore ENLTV-FM 3",
		.audio_घड़ी    = 0x02187de7,
		.tuner_type     = TUNER_TENA_TNF_5337,
		.radio_type     = TUNER_TEA5767,
		.tuner_addr	= 0x61,
		.radio_addr	= 0x60,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE1,
			.gpio = 0x43000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_CINERGY_HT_PCI] = अणु
		.name           = "Terratec Cinergy HT PCI",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 0,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 6,
			.amux   = LINE1,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_PHILIPS_TIGER_S] = अणु
		.name           = "Philips Tiger - S Reference design",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda829x_conf   = अणु .lna_cfg = TDA8290_LNA_GP0_HIGH_OFF पूर्ण,
		.mpeg           = SAA7134_MPEG_DVB,
		.gpiomask       = 0x0200000,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 3,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = TV,
			.gpio   = 0x0200000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_M102] = अणु
		.name           = "Avermedia M102",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask       = 1<<21,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 6,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ASUS_P7131_4871] = अणु
		.name           = "ASUS P7131 4871",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda829x_conf   = अणु .lna_cfg = TDA8290_LNA_GP0_HIGH_OFF पूर्ण,
		.mpeg           = SAA7134_MPEG_DVB,
		.gpiomask       = 0x0200000,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
			.gpio   = 0x0200000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE2,
			.gpio = 0x0200000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 0,
			.amux = LINE2,
			.gpio = 0x0200000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
			.gpio = 0x0200000,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ASUSTeK_P7131_HYBRID_LNA] = अणु
		.name           = "ASUSTeK P7131 Hybrid",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda829x_conf   = अणु .lna_cfg = TDA8290_LNA_GP0_HIGH_OFF पूर्ण,
		.gpiomask	= 1 << 21,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x0000000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE2,
			.gpio = 0x0200000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 0,
			.amux = LINE2,
			.gpio = 0x0200000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
			.gpio = 0x0200000,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x0200000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ASUSTeK_P7131_ANALOG] = अणु
	       .name           = "ASUSTeK P7131 Analog",
	       .audio_घड़ी    = 0x00187de7,
	       .tuner_type     = TUNER_PHILIPS_TDA8290,
	       .radio_type     = UNSET,
	       .tuner_addr     = ADDR_UNSET,
	       .radio_addr     = ADDR_UNSET,
	       .gpiomask       = 1 << 21,
	       .inमाला_दो         = अणुअणु
		       .type = SAA7134_INPUT_TV,
		       .vmux = 1,
		       .amux = TV,
		       .gpio = 0x0000000,
	       पूर्ण, अणु
		       .type = SAA7134_INPUT_COMPOSITE1,
		       .vmux = 3,
		       .amux = LINE2,
	       पूर्ण, अणु
		       .type = SAA7134_INPUT_COMPOSITE2,
		       .vmux = 0,
		       .amux = LINE2,
	       पूर्ण, अणु
		       .type = SAA7134_INPUT_SVIDEO,
		       .vmux = 8,
		       .amux = LINE2,
	       पूर्ण पूर्ण,
	       .radio = अणु
		       .type = SAA7134_INPUT_RADIO,
		       .amux = TV,
		       .gpio = 0x0200000,
	       पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_SABRENT_TV_PCB05] = अणु
		.name           = "Sabrent PCMCIA TV-PCB05",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 0,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्णपूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_10MOONSTVMASTER3] = अणु
		/* Tony Wan <aloha_cn@hoपंचांगail.com> */
		.name           = "10MOONS TM300 TV Card",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_LG_PAL_NEW_TAPC,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.gpiomask       = 0x7000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2,
			.gpio = 0x0000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
			.gpio = 0x2000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
			.gpio = 0x2000,
		पूर्णपूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE2,
			.gpio = 0x3000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_SUPER_007] = अणु
		.name           = "Avermedia Super 007",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda829x_conf   = अणु .lna_cfg = TDA8290_LNA_OFF पूर्ण,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV, /* FIXME: analog tv untested */
			.vmux   = 1,
			.amux   = TV,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_M135A] = अणु
		.name           = "Avermedia PCI pure analog (M135A)",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda829x_conf   = अणु .lna_cfg = TDA8290_LNA_GP0_HIGH_OFF पूर्ण,
		.gpiomask       = 0x020200000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x00200000,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
			.gpio = 0x01,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_M733A] = अणु
		.name		= "Avermedia PCI M733A",
		.audio_घड़ी	= 0x00187de7,
		.tuner_type	= TUNER_PHILIPS_TDA8290,
		.radio_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda829x_conf	= अणु .lna_cfg = TDA8290_LNA_OFF पूर्ण,
		.gpiomask	= 0x020200000,
		.inमाला_दो		= अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x00200000,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
			.gpio = 0x01,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_401] = अणु
		/*       Beholder Intl. Ltd. 2008      */
		/*Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV 401",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FQ1216ME,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask       = 0x00008000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = LINE2,
		पूर्णपूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE1,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_403] = अणु
		/*       Beholder Intl. Ltd. 2008      */
		/*Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV 403",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FQ1216ME,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask       = 0x00008000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 1,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_403FM] = अणु
		/*       Beholder Intl. Ltd. 2008      */
		/*Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV 403 FM",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FQ1216ME,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask       = 0x00008000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 1,
			.amux   = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_405] = अणु
		/*       Beholder Intl. Ltd. 2008      */
		/*Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV 405",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0x00008000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = LINE2,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_405FM] = अणु
		/* Sergey <skiv@orel.ru> */
		/*       Beholder Intl. Ltd. 2008      */
		/*Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV 405 FM",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0x00008000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = LINE2,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_407] = अणु
		/*       Beholder Intl. Ltd. 2008      */
		/*Dmitry Belimov <d.belimov@gmail.com> */
		.name		= "Beholder BeholdTV 407",
		.audio_घड़ी	= 0x00187de7,
		.tuner_type	= TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf	= TDA9887_PRESENT,
		.gpiomask       = 0x00008000,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
			.gpio = 0xc0c000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
			.gpio = 0xc0c000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
			.gpio = 0xc0c000,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_407FM] = अणु
		/*       Beholder Intl. Ltd. 2008      */
		/*Dmitry Belimov <d.belimov@gmail.com> */
		.name		= "Beholder BeholdTV 407 FM",
		.audio_घड़ी	= 0x00187de7,
		.tuner_type	= TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf	= TDA9887_PRESENT,
		.gpiomask       = 0x00008000,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
			.gpio = 0xc0c000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
			.gpio = 0xc0c000,
		पूर्ण,अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
			.gpio = 0xc0c000,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
			.gpio = 0xc0c000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_409] = अणु
		/*       Beholder Intl. Ltd. 2008      */
		/*Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV 409",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0x00008000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्णपूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_505FM] = अणु
		/*       Beholder Intl. Ltd. 2008      */
		/*Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV 505 FM",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0x00008000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE1,
		पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_505RDS_MK5] = अणु
		/*       Beholder Intl. Ltd. 2008      */
		/*Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV 505 RDS",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_FM1216MK5,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.rds_addr	= 0x10,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0x00008000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्णपूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE1,
		पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_507_9FM] = अणु
		/*       Beholder Intl. Ltd. 2008      */
		/*Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV 507 FM / BeholdTV 509 FM",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0x00008000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्णपूर्ण,
			.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_507RDS_MK5] = अणु
		/*       Beholder Intl. Ltd. 2008      */
		/*Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV 507 RDS",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216MK5,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.rds_addr	= 0x10,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0x00008000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
			.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_507RDS_MK3] = अणु
		/*       Beholder Intl. Ltd. 2008      */
		/*Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV 507 RDS",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.rds_addr	= 0x10,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0x00008000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
			.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_COLUMBUS_TVFM] = अणु
		/*       Beholder Intl. Ltd. 2008      */
		/* Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV Columbus TV/FM",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_ALPS_TSBE5_PAL,
		.radio_type     = TUNER_TEA5767,
		.tuner_addr     = 0xc2 >> 1,
		.radio_addr     = 0xc0 >> 1,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0x000A8004,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
			.gpio = 0x000A8004,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
			.gpio = 0x000A8000,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
			.gpio = 0x000A8000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
			.gpio = 0x000A8000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_607FM_MK3] = अणु
		/* Andrey Melnikoff <temnota@kmv.ru> */
		.name           = "Beholder BeholdTV 607 FM",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_609FM_MK3] = अणु
		/* Andrey Melnikoff <temnota@kmv.ru> */
		.name           = "Beholder BeholdTV 609 FM",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_607FM_MK5] = अणु
		/* Andrey Melnikoff <temnota@kmv.ru> */
		.name           = "Beholder BeholdTV 607 FM",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216MK5,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_609FM_MK5] = अणु
		/* Andrey Melnikoff <temnota@kmv.ru> */
		.name           = "Beholder BeholdTV 609 FM",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216MK5,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_607RDS_MK3] = अणु
		/* Andrey Melnikoff <temnota@kmv.ru> */
		.name           = "Beholder BeholdTV 607 RDS",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.rds_addr	= 0x10,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_609RDS_MK3] = अणु
		/* Andrey Melnikoff <temnota@kmv.ru> */
		.name           = "Beholder BeholdTV 609 RDS",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.rds_addr	= 0x10,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_607RDS_MK5] = अणु
		/* Andrey Melnikoff <temnota@kmv.ru> */
		.name           = "Beholder BeholdTV 607 RDS",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216MK5,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.rds_addr	= 0x10,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_609RDS_MK5] = अणु
		/* Andrey Melnikoff <temnota@kmv.ru> */
		.name           = "Beholder BeholdTV 609 RDS",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216MK5,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.rds_addr	= 0x10,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण,अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण,अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्णपूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_M6] = अणु
		/* Igor Kuznetsov <igk@igk.ru> */
		/* Andrey Melnikoff <temnota@kmv.ru> */
		/* Beholder Intl. Ltd. Dmitry Belimov <d.belimov@gmail.com> */
		/* Alexey Osipov <lion-simba@pridelands.ru> */
		.name           = "Beholder BeholdTV M6",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.empress_addr	= 0x20,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
		.mpeg  = SAA7134_MPEG_EMPRESS,
		.video_out = CCIR656,
		.vid_port_opts  = (SET_T_CODE_POLARITY_NON_INVERTED |
					SET_CLOCK_NOT_DELAYED |
					SET_CLOCK_INVERTED |
					SET_VSYNC_OFF),
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_M63] = अणु
		/* Igor Kuznetsov <igk@igk.ru> */
		/* Andrey Melnikoff <temnota@kmv.ru> */
		/* Beholder Intl. Ltd. Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV M63",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.empress_addr	= 0x20,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
		.mpeg  = SAA7134_MPEG_EMPRESS,
		.video_out = CCIR656,
		.vid_port_opts  = (SET_T_CODE_POLARITY_NON_INVERTED |
					SET_CLOCK_NOT_DELAYED |
					SET_CLOCK_INVERTED |
					SET_VSYNC_OFF),
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_M6_EXTRA] = अणु
		/* Igor Kuznetsov <igk@igk.ru> */
		/* Andrey Melnikoff <temnota@kmv.ru> */
		/* Beholder Intl. Ltd. Dmitry Belimov <d.belimov@gmail.com> */
		/* Alexey Osipov <lion-simba@pridelands.ru> */
		.name           = "Beholder BeholdTV M6 Extra",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216MK5,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.rds_addr	= 0x10,
		.empress_addr	= 0x20,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
		.mpeg  = SAA7134_MPEG_EMPRESS,
		.video_out = CCIR656,
		.vid_port_opts  = (SET_T_CODE_POLARITY_NON_INVERTED |
					SET_CLOCK_NOT_DELAYED |
					SET_CLOCK_INVERTED |
					SET_VSYNC_OFF),
	पूर्ण,
	[SAA7134_BOARD_TWINHAN_DTV_DVB_3056] = अणु
		.name           = "Twinhan Hybrid DTV-DVB 3056 PCI",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda829x_conf   = अणु .lna_cfg = TDA8290_LNA_GP0_HIGH_OFF पूर्ण,
		.mpeg           = SAA7134_MPEG_DVB,
		.gpiomask       = 0x0200000,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 3,
			.amux   = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,		/* untested */
			.amux   = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = TV,
			.gpio   = 0x0200000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_GENIUS_TVGO_A11MCE] = अणु
		/* Adrian Pardini <parकरो.bsso@gmail.com> */
		.name		= "Genius TVGO AM11MCE",
		.audio_घड़ी	= 0x00200000,
		.tuner_type	= TUNER_TNF_5335MF,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask       = 0xf000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 1,
			.amux = LINE2,
			.gpio = 0x0000,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
			.gpio = 0x2000,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
			.gpio = 0x2000,
	पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
			.gpio = 0x1000,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE2,
			.gpio = 0x6000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_PHILIPS_SNAKE] = अणु
		.name           = "NXP Snake DVB-S reference design",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_ABSENT,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 3,
			.amux   = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_CREATIX_CTX953] = अणु
		.name         = "Medion/Creatix CTX953 Hybrid",
		.audio_घड़ी  = 0x00187de7,
		.tuner_type   = TUNER_PHILIPS_TDA8290,
		.radio_type   = UNSET,
		.tuner_addr   = ADDR_UNSET,
		.radio_addr   = ADDR_UNSET,
		.tda829x_conf = अणु .lna_cfg = TDA8290_LNA_OFF पूर्ण,
		.mpeg         = SAA7134_MPEG_DVB,
		.inमाला_दो       = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_MSI_TVANYWHERE_AD11] = अणु
		.name           = "MSI TV@nywhere A/D v1.1",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda829x_conf   = अणु .lna_cfg = TDA8290_LNA_GP0_HIGH_OFF पूर्ण,
		.mpeg           = SAA7134_MPEG_DVB,
		.gpiomask       = 0x0200000,
		.inमाला_दो = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 3,
			.amux   = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = TV,
			.gpio   = 0x0200000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_CARDBUS_506] = अणु
		.name           = "AVerMedia Cardbus TV/Radio (E506R)",
		.audio_घड़ी    = 0x187de7,
		.tuner_type     = TUNER_XC2028,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		 .mpeg           = SAA7134_MPEG_DVB,
		 .inमाला_दो         = अणुअणु
			 .type = SAA7134_INPUT_TV,
			 .vmux = 1,
			 .amux = TV,
		 पूर्ण, अणु
			 .type = SAA7134_INPUT_COMPOSITE1,
			 .vmux = 3,
			 .amux = LINE1,
		 पूर्ण, अणु
			 .type = SAA7134_INPUT_SVIDEO,
			 .vmux = 8,
			 .amux = LINE2,
		 पूर्ण पूर्ण,
		 .radio = अणु
			 .type = SAA7134_INPUT_RADIO,
			 .amux = TV,
		 पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_A16D] = अणु
		.name           = "AVerMedia Hybrid TV/Radio (A16D)",
		.audio_घड़ी    = 0x187de7,
		.tuner_type     = TUNER_XC2028,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE,
			.vmux = 0,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_M115] = अणु
		.name           = "Avermedia M115",
		.audio_घड़ी    = 0x187de7,
		.tuner_type     = TUNER_XC2028,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_VIDEOMATE_T750] = अणु
		/* John Newbigin <jn@it.swin.edu.au> */
		.name           = "Compro VideoMate T750",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_XC2028,
		.radio_type     = UNSET,
		.tuner_addr	= 0x61,
		.radio_addr	= ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 3,
			.amux   = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 1,
			.amux   = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE2,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
		पूर्ण
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_A700_PRO] = अणु
		/* Matthias Schwarzott <zzam@gentoo.org> */
		.name           = "Avermedia DVB-S Pro A700",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_ABSENT,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_COMPOSITE,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 6,
			.amux = LINE1,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_A700_HYBRID] = अणु
		/* Matthias Schwarzott <zzam@gentoo.org> */
		.name           = "Avermedia DVB-S Hybrid+FM A700",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_XC2028,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 4,
			.amux   = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 6,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_H6] = अणु
		/* Igor Kuznetsov <igk@igk.ru> */
		.name           = "Beholder BeholdTV H6",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FMD1216MEX_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ASUSTeK_TIGER_3IN1] = अणु
		.name           = "Asus Tiger 3in1",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda829x_conf   = अणु .lna_cfg = TDA8290_LNA_GP0_HIGH_OFF पूर्ण,
		.gpiomask       = 1 << 21,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x0200000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ASUSTeK_PS3_100] = अणु
		.name           = "Asus My Cinema PS3-100",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda829x_conf   = अणु .lna_cfg = TDA8290_LNA_GP0_HIGH_OFF पूर्ण,
		.gpiomask       = 1 << 21,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x0200000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_REAL_ANGEL_220] = अणु
		.name           = "Zogis Real Angel 220",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_TNF_5335MF,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.gpiomask       = 0x801a8087,
		.inमाला_दो = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 3,
			.amux   = LINE2,
			.gpio   = 0x624000,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 1,
			.amux   = LINE1,
			.gpio   = 0x624000,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 1,
			.amux   = LINE1,
			.gpio   = 0x624000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = LINE2,
			.gpio   = 0x624001,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ADS_INSTANT_HDTV_PCI] = अणु
		.name           = "ADS Tech Instant HDTV",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TUV1236D,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE,
			.vmux = 4,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ASUSTeK_TIGER] = अणु
		.name           = "Asus Tiger Rev:1.00",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda829x_conf   = अणु .lna_cfg = TDA8290_LNA_OFF पूर्ण,
		.mpeg           = SAA7134_MPEG_DVB,
		.gpiomask       = 0x0200000,
		.inमाला_दो = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 3,
			.amux   = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux   = 0,
			.amux   = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE2,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = TV,
			.gpio   = 0x0200000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_KWORLD_PLUS_TV_ANALOG] = अणु
		.name           = "Kworld Plus TV Analog Lite PCI",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_YMEC_TVF_5533MF,
		.radio_type     = TUNER_TEA5767,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = 0x60,
		.gpiomask       = 0x80000700,
		.inमाला_दो = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = LINE2,
			.gpio   = 0x100,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 3,
			.amux   = LINE1,
			.gpio   = 0x200,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
			.gpio   = 0x200,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.vmux   = 1,
			.amux   = LINE1,
			.gpio   = 0x100,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.vmux = 8,
			.amux = 2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_KWORLD_PCI_SBTVD_FULLSEG] = अणु
		.name           = "Kworld PCI SBTVD/ISDB-T Full-Seg Hybrid",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.tuner_addr     = ADDR_UNSET,
		.radio_type     = UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask       = 0x8e054000,
		.mpeg           = SAA7134_MPEG_DVB,
		.ts_type	= SAA7134_MPEG_TS_PARALLEL,
		.inमाला_दो = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
#अगर 0	/* FIXME */
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 3,
			.amux   = LINE1,
			.gpio   = 0x200,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
			.gpio   = 0x200,
#पूर्ण_अगर
		पूर्ण पूर्ण,
#अगर 0
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.vmux   = 1,
			.amux   = LINE1,
			.gpio   = 0x100,
		पूर्ण,
#पूर्ण_अगर
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.vmux = 0,
			.amux = TV,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_GO_007_FM_PLUS] = अणु
		.name           = "Avermedia AVerTV GO 007 FM Plus",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask       = 0x00300003,
		/* .gpiomask       = 0x8c240003, */
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x01,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 6,
			.amux = LINE1,
			.gpio = 0x02,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x00300001,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
			.gpio = 0x01,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_STUDIO_507UA] = अणु
		/* Andy Shevchenko <andy@smile.org.ua> */
		.name           = "Avermedia AVerTV Studio 507UA",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3, /* Should be MK5 */
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0x03,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x00,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
			.gpio = 0x00,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
			.gpio = 0x00,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
			.gpio = 0x01,
		पूर्ण,
		.mute  = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE1,
			.gpio = 0x00,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_VIDEOMATE_S350] = अणु
		/* Jan D. Louw <jd.louw@mweb.co.za */
		.name		= "Compro VideoMate S350/S300",
		.audio_घड़ी	= 0x00187de7,
		.tuner_type	= TUNER_ABSENT,
		.radio_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.mpeg		= SAA7134_MPEG_DVB,
		.inमाला_दो = अणु अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux	= 0,
			.amux	= LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux	= 8, /* Not tested */
			.amux	= LINE1
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_X7] = अणु
		/* Beholder Intl. Ltd. Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV X7",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_XC5000,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 2,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 9,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ZOLID_HYBRID_PCI] = अणु
		.name           = "Zolid Hybrid TV Tuner PCI",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda829x_conf   = अणु .lna_cfg = TDA8290_LNA_OFF पूर्ण,
		.mpeg           = SAA7134_MPEG_DVB,
		.ts_type	= SAA7134_MPEG_TS_PARALLEL,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण पूर्ण,
		.radio = अणु	/* untested */
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_ASUS_EUROPA_HYBRID] = अणु
		.name           = "Asus Europa Hybrid OEM",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TD1316,
		.radio_type     = UNSET,
		.tuner_addr	= 0x61,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT | TDA9887_PORT1_ACTIVE,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 3,
			.amux   = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 4,
			.amux   = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE2,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_LEADTEK_WINFAST_DTV1000S] = अणु
		.name           = "Leadtek Winfast DTV1000S",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_505RDS_MK3] = अणु
		/*       Beholder Intl. Ltd. 2008      */
		/*Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV 505 RDS",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_PHILIPS_FM1216ME_MK3,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.rds_addr	= 0x10,
		.tda9887_conf   = TDA9887_PRESENT,
		.gpiomask       = 0x00008000,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE1,
		पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE2,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_HAWELL_HW_404M7] = अणु
		/* Hawell HW-404M7 & Hawell HW-808M7  */
		/* Bogoslovskiy Viktor <bogovic@bk.ru> */
		.name         = "Hawell HW-404M7",
		.audio_घड़ी   = 0x00200000,
		.tuner_type    = UNSET,
		.radio_type    = UNSET,
		.tuner_addr   = ADDR_UNSET,
		.radio_addr   = ADDR_UNSET,
		.gpiomask      = 0x389c00,
		.inमाला_दो       = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
			.gpio = 0x01fc00,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_H7] = अणु
		/* Beholder Intl. Ltd. Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV H7",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_XC5000,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.ts_type	= SAA7134_MPEG_TS_PARALLEL,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 2,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 9,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_A7] = अणु
		/* Beholder Intl. Ltd. Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV A7",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_XC5000,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 2,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 9,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_TECHNOTREND_BUDGET_T3000] = अणु
		.name           = "TechoTrend TT-budget T-3000",
		.tuner_type     = TUNER_PHILIPS_TD1316,
		.audio_घड़ी    = 0x00187de7,
		.radio_type     = UNSET,
		.tuner_addr     = 0x63,
		.radio_addr     = ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT | TDA9887_PORT1_ACTIVE,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 3,
			.amux   = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 0,
			.amux   = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE2,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_VIDEOMATE_M1F] = अणु
		/* Pavel Osnova <pvosnova@gmail.com> */
		.name           = "Compro VideoMate Vista M1F",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_LG_PAL_NEW_TAPC,
		.radio_type     = TUNER_TEA5767,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = 0x60,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE1,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = TV,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_MAGICPRO_PROHDTV_PRO2] = अणु
		/* Timothy Lee <timothy.lee@siriushk.com> */
		.name		= "MagicPro ProHDTV Pro2 DMB-TH/Hybrid",
		.audio_घड़ी	= 0x00187de7,
		.tuner_type	= TUNER_PHILIPS_TDA8290,
		.radio_type	= UNSET,
		.tda829x_conf	= अणु .lna_cfg = TDA8290_LNA_ON_BRIDGE पूर्ण,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask	= 0x02050000,
		.mpeg		= SAA7134_MPEG_DVB,
		.ts_type	= SAA7134_MPEG_TS_PARALLEL,
		.inमाला_दो		= अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
			.gpio   = 0x00050000,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 3,
			.amux   = LINE1,
			.gpio   = 0x00050000,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
			.gpio   = 0x00050000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = TV,
			.gpio   = 0x00050000,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.vmux   = 0,
			.amux   = TV,
			.gpio   = 0x00050000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_501] = अणु
		/*       Beholder Intl. Ltd. 2010       */
		/* Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV 501",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_ABSENT,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.gpiomask       = 0x00008000,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE1,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_BEHOLD_503FM] = अणु
		/*       Beholder Intl. Ltd. 2010       */
		/* Dmitry Belimov <d.belimov@gmail.com> */
		.name           = "Beholder BeholdTV 503 FM",
		.audio_घड़ी    = 0x00200000,
		.tuner_type     = TUNER_ABSENT,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.gpiomask       = 0x00008000,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 1,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE1,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_SENSORAY811_911] = अणु
		.name		= "Sensoray 811/911",
		.audio_घड़ी	= 0x00200000,
		.tuner_type	= TUNER_ABSENT,
		.radio_type	= UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.inमाला_दो		= अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux   = 0,
			.amux   = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE3,
			.vmux   = 2,
			.amux   = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE1,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_KWORLD_PC150U] = अणु
		.name           = "Kworld PC150-U",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.mpeg           = SAA7134_MPEG_DVB,
		.gpiomask       = 1 << 21,
		.ts_type	= SAA7134_MPEG_TS_PARALLEL,
		.inमाला_दो = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux   = 1,
			.amux   = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE,
			.vmux   = 3,
			.amux   = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux   = 8,
			.amux   = LINE2,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux   = TV,
			.gpio	= 0x0000000,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_HAWELL_HW_9004V1] = अणु
		/* Hawell HW-9004V1 */
		/* Vadim Frolov <fralik@gmail.com> */
		.name         = "Hawell HW-9004V1",
		.audio_घड़ी   = 0x00200000,
		.tuner_type    = UNSET,
		.radio_type    = UNSET,
		.tuner_addr   = ADDR_UNSET,
		.radio_addr   = ADDR_UNSET,
		.gpiomask      = 0x618E700,
		.inमाला_दो       = अणुअणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE1,
			.gpio = 0x6010000,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_A706] = अणु
		.name           = "AverMedia AverTV Satellite Hybrid+FM A706",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.tda829x_conf   = अणु .lna_cfg = TDA8290_LNA_OFF,
				    .no_i2c_gate = 1,
				    .tda18271_std_map = &aver_a706_std_map पूर्ण,
		.gpiomask       = 1 << 11,
		.mpeg           = SAA7134_MPEG_DVB,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE,
			.vmux = 4,
			.amux = LINE1,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE1,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x0000800,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_WIS_VOYAGER] = अणु
		.name           = "WIS Voyager or compatible",
		.audio_घड़ी    = 0x00200000,
		.tuner_type	= TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.mpeg		= SAA7134_MPEG_GO7007,
		.inमाला_दो		= अणु अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 3,
			.amux = TV,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 6,
		.amux = LINE1,
		पूर्ण पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_AVERMEDIA_505] = अणु
		/* much like the "studio" version but without radio
		* and another tuner (dbaryshkov@gmail.com) */
		.name           = "AverMedia AverTV/505",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_FQ1216ME,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.tda9887_conf   = TDA9887_PRESENT,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 0,
			.amux = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE2,
			.vmux = 3,
			.amux = LINE2,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
		पूर्ण पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE1,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_LEADTEK_WINFAST_TV2100_FM] = अणु
		.name           = "Leadtek Winfast TV2100 FM",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_TNF_5335MF,
		.radio_type     = UNSET,
		.tuner_addr	= ADDR_UNSET,
		.radio_addr	= ADDR_UNSET,
		.gpiomask       = 0x0d,
		.inमाला_दो         = अणुअणु
			.type = SAA7134_INPUT_TV_MONO,
			.vmux = 1,
			.amux = LINE1,
			.gpio = 0x00,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE2,
			.gpio = 0x08,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
			.gpio = 0x08,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = LINE1,
			.gpio = 0x04,
		पूर्ण,
		.mute = अणु
			.type = SAA7134_INPUT_MUTE,
			.amux = LINE1,
			.gpio = 0x08,
		पूर्ण,
	पूर्ण,
	[SAA7134_BOARD_SNAZIO_TVPVR_PRO] = अणु
		.name           = "SnaZio* TVPVR PRO",
		.audio_घड़ी    = 0x00187de7,
		.tuner_type     = TUNER_PHILIPS_TDA8290,
		.radio_type     = UNSET,
		.tuner_addr     = ADDR_UNSET,
		.radio_addr     = ADDR_UNSET,
		.gpiomask       = 1 << 21,
		.inमाला_दो         = अणु अणु
			.type = SAA7134_INPUT_TV,
			.vmux = 1,
			.amux = TV,
			.gpio = 0x0000000,
		पूर्ण, अणु
			.type = SAA7134_INPUT_COMPOSITE1,
			.vmux = 3,
			.amux = LINE2,
			.gpio = 0x0000000,
		पूर्ण, अणु
			.type = SAA7134_INPUT_SVIDEO,
			.vmux = 8,
			.amux = LINE2,
			.gpio = 0x0000000,
		पूर्ण पूर्ण,
		.radio = अणु
			.type = SAA7134_INPUT_RADIO,
			.amux = TV,
			.gpio = 0x0200000,
		पूर्ण,
	पूर्ण,
पूर्ण;

स्थिर अचिन्हित पूर्णांक saa7134_bcount = ARRAY_SIZE(saa7134_boards);

/* ------------------------------------------------------------------ */
/* PCI ids + subप्रणाली IDs                                            */

काष्ठा pci_device_id saa7134_pci_tbl[] = अणु
	अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = PCI_VENDOR_ID_PHILIPS,
		.subdevice    = 0x2001,
		.driver_data  = SAA7134_BOARD_PROTEUS_PRO,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = PCI_VENDOR_ID_PHILIPS,
		.subdevice    = 0x2001,
		.driver_data  = SAA7134_BOARD_PROTEUS_PRO,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = PCI_VENDOR_ID_PHILIPS,
		.subdevice    = 0x6752,
		.driver_data  = SAA7134_BOARD_EMPRESS,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1131,
		.subdevice    = 0x4e85,
		.driver_data  = SAA7134_BOARD_MONSTERTV,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x153b,
		.subdevice    = 0x1142,
		.driver_data  = SAA7134_BOARD_CINERGY400,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x153b,
		.subdevice    = 0x1143,
		.driver_data  = SAA7134_BOARD_CINERGY600,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x153b,
		.subdevice    = 0x1158,
		.driver_data  = SAA7134_BOARD_CINERGY600_MK3,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x153b,
		.subdevice    = 0x1162,
		.driver_data  = SAA7134_BOARD_CINERGY400_CARDBUS,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x5169,
		.subdevice    = 0x0138,
		.driver_data  = SAA7134_BOARD_FLYVIDEO3000_NTSC,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x5168,
		.subdevice    = 0x0138,
		.driver_data  = SAA7134_BOARD_FLYVIDEO3000,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x4e42,				/* "Typhoon PCI Capture TV Card" Art.No. 50673 */
		.subdevice    = 0x0138,
		.driver_data  = SAA7134_BOARD_FLYVIDEO3000,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x5168,
		.subdevice    = 0x0138,
		.driver_data  = SAA7134_BOARD_FLYVIDEO2000,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x4e42,		/* Typhoon */
		.subdevice    = 0x0138,		/* LअगरeView FlyTV Prime30 OEM */
		.driver_data  = SAA7134_BOARD_FLYVIDEO2000,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5168,
		.subdevice    = 0x0212, /* minipci, LR212 */
		.driver_data  = SAA7134_BOARD_FLYTVPLATINUM_MINI,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x14c0,
		.subdevice    = 0x1212, /* minipci, LR1212 */
		.driver_data  = SAA7134_BOARD_FLYTVPLATINUM_MINI2,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x4e42,
		.subdevice    = 0x0212, /* OEM minipci, LR212 */
		.driver_data  = SAA7134_BOARD_FLYTVPLATINUM_MINI,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5168,	/* Animation Technologies (LअगरeView) */
		.subdevice    = 0x0214, /* Standard PCI, LR214 Rev E and earlier (SAA7135) */
		.driver_data  = SAA7134_BOARD_FLYTVPLATINUM_FM,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5168,	/* Animation Technologies (LअगरeView) */
		.subdevice    = 0x5214, /* Standard PCI, LR214 Rev F onwards (SAA7131) */
		.driver_data  = SAA7134_BOARD_FLYTVPLATINUM_FM,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1489, /* KYE */
		.subdevice    = 0x0214, /* Genius VideoWonder ProTV */
		.driver_data  = SAA7134_BOARD_FLYTVPLATINUM_FM, /* is an LR214WF actually */
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x16be,
		.subdevice    = 0x0003,
		.driver_data  = SAA7134_BOARD_MD7134,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x16be, /* CTX946 analog TV, HW mpeg, DVB-T */
		.subdevice    = 0x5000, /* only analog TV and DVB-T क्रम now */
		.driver_data  = SAA7134_BOARD_MD7134,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x1048,
		.subdevice    = 0x226b,
		.driver_data  = SAA7134_BOARD_ELSA,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x1048,
		.subdevice    = 0x226a,
		.driver_data  = SAA7134_BOARD_ELSA_500TV,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x1048,
		.subdevice    = 0x226c,
		.driver_data  = SAA7134_BOARD_ELSA_700TV,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = PCI_VENDOR_ID_ASUSTEK,
		.subdevice    = 0x4842,
		.driver_data  = SAA7134_BOARD_ASUSTeK_TVFM7134,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = PCI_VENDOR_ID_ASUSTEK,
		.subdevice    = 0x4845,
		.driver_data  = SAA7134_BOARD_ASUSTeK_TVFM7135,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = PCI_VENDOR_ID_ASUSTEK,
		.subdevice    = 0x4830,
		.driver_data  = SAA7134_BOARD_ASUSTeK_TVFM7134,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = PCI_VENDOR_ID_ASUSTEK,
		.subdevice    = 0x4843,
		.driver_data  = SAA7134_BOARD_ASUSTEK_TVFM7133,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = PCI_VENDOR_ID_ASUSTEK,
		.subdevice    = 0x4840,
		.driver_data  = SAA7134_BOARD_ASUSTeK_TVFM7134,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = PCI_VENDOR_ID_PHILIPS,
		.subdevice    = 0xfe01,
		.driver_data  = SAA7134_BOARD_TVSTATION_RDS,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1894,
		.subdevice    = 0xfe01,
		.driver_data  = SAA7134_BOARD_TVSTATION_RDS,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1894,
		.subdevice    = 0xa006,
		.driver_data  = SAA7134_BOARD_TVSTATION_DVR,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1131,
		.subdevice    = 0x7133,
		.driver_data  = SAA7134_BOARD_VA1000POWER,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = PCI_VENDOR_ID_PHILIPS,
		.subdevice    = 0x2001,
		.driver_data  = SAA7134_BOARD_10MOONSTVMASTER,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x185b,
		.subdevice    = 0xc100,
		.driver_data  = SAA7134_BOARD_VIDEOMATE_TV,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x185b,
		.subdevice    = 0xc100,
		.driver_data  = SAA7134_BOARD_VIDEOMATE_TV_GOLD_PLUS,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = PCI_VENDOR_ID_MATROX,
		.subdevice    = 0x48d0,
		.driver_data  = SAA7134_BOARD_CRONOS_PLUS,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xa70b,
		.driver_data  = SAA7134_BOARD_MD2819,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xa7a1,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_A700_PRO,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xa7a2,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_A700_HYBRID,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0x2115,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_STUDIO_305,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xa115,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_STUDIO_505,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0x2108,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_305,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0x10ff,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_DVD_EZMAKER,
	पूर्ण,अणु
		/* AVerMedia CardBus */
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xd6ee,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_CARDBUS,
	पूर्ण,अणु
		/* AVerMedia CardBus */
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xb7e9,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_CARDBUS_501,
	पूर्ण, अणु
		/* TransGear 3000TV */
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0x050c,
		.driver_data  = SAA7134_BOARD_TG3000TV,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x11bd,
		.subdevice    = 0x002b,
		.driver_data  = SAA7134_BOARD_PINNACLE_PCTV_STEREO,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x11bd,
		.subdevice    = 0x002d,
		.driver_data  = SAA7134_BOARD_PINNACLE_300I_DVBT_PAL,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1019,
		.subdevice    = 0x4cb4,
		.driver_data  = SAA7134_BOARD_ECS_TVP3XP,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1019,
		.subdevice    = 0x4cb5,
		.driver_data  = SAA7134_BOARD_ECS_TVP3XP_4CB5,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1019,
		.subdevice    = 0x4cb6,
		.driver_data  = SAA7134_BOARD_ECS_TVP3XP_4CB6,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x12ab,
		.subdevice    = 0x0800,
		.driver_data  = SAA7134_BOARD_UPMOST_PURPLE_TV,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x153b,
		.subdevice    = 0x1152,
		.driver_data  = SAA7134_BOARD_CINERGY200,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x185b,
		.subdevice    = 0xc100,
		.driver_data  = SAA7134_BOARD_VIDEOMATE_TV_PVR,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0x9715,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_STUDIO_307,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xa70a,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_307,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x185b,
		.subdevice    = 0xc200,
		.driver_data  = SAA7134_BOARD_VIDEOMATE_GOLD_PLUS,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1540,
		.subdevice    = 0x9524,
		.driver_data  = SAA7134_BOARD_PROVIDEO_PV952,

	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5168,
		.subdevice    = 0x0502,                /* Cardbus version */
		.driver_data  = SAA7134_BOARD_FLYDVBT_DUO_CARDBUS,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5168,
		.subdevice    = 0x0306,                /* PCI version */
		.driver_data  = SAA7134_BOARD_FLYDVBTDUO,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xf31f,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_GO_007_FM,

	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xf11d,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_M135A,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0x4155,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_M733A,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0x4255,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_M733A,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = PCI_VENDOR_ID_PHILIPS,
		.subdevice    = 0x2004,
		.driver_data  = SAA7134_BOARD_PHILIPS_TOUGH,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1421,
		.subdevice    = 0x0350,		/* PCI version */
		.driver_data  = SAA7134_BOARD_ADS_INSTANT_TV,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1421,
		.subdevice    = 0x0351,		/* PCI version, new revision */
		.driver_data  = SAA7134_BOARD_ADS_INSTANT_TV,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1421,
		.subdevice    = 0x0370,		/* cardbus version */
		.driver_data  = SAA7134_BOARD_ADS_INSTANT_TV,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1421,
		.subdevice    = 0x1370,        /* cardbus version */
		.driver_data  = SAA7134_BOARD_ADS_INSTANT_TV,

	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x4e42,		/* Typhoon */
		.subdevice    = 0x0502,		/* LअगरeView LR502 OEM */
		.driver_data  = SAA7134_BOARD_FLYDVBT_DUO_CARDBUS,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1043,
		.subdevice    = 0x0210,		/* mini pci NTSC version */
		.driver_data  = SAA7134_BOARD_FLYTV_DIGIMATRIX,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1043,
		.subdevice    = 0x0210,		/* mini pci PAL/SECAM version */
		.driver_data  = SAA7134_BOARD_ASUSTEK_DIGIMATRIX_TV,

	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x0000, /* It shouldn't अवरोध anything, since subdevice id seems unique */
		.subdevice    = 0x4091,
		.driver_data  = SAA7134_BOARD_BEHOLD_409FM,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5456, /* GoTView */
		.subdevice    = 0x7135,
		.driver_data  = SAA7134_BOARD_GOTVIEW_7135,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = PCI_VENDOR_ID_PHILIPS,
		.subdevice    = 0x2004,
		.driver_data  = SAA7134_BOARD_PHILIPS_EUROPA,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x185b,
		.subdevice    = 0xc900,
		.driver_data  = SAA7134_BOARD_VIDEOMATE_DVBT_300,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x185b,
		.subdevice    = 0xc901,
		.driver_data  = SAA7134_BOARD_VIDEOMATE_DVBT_200,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1435,
		.subdevice    = 0x7350,
		.driver_data  = SAA7134_BOARD_RTD_VFG7350,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1435,
		.subdevice    = 0x7330,
		.driver_data  = SAA7134_BOARD_RTD_VFG7330,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461,
		.subdevice    = 0x1044,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_AVERTVHD_A180,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1131,
		.subdevice    = 0x4ee9,
		.driver_data  = SAA7134_BOARD_MONSTERTV_MOBILE,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x11bd,
		.subdevice    = 0x002e,
		.driver_data  = SAA7134_BOARD_PINNACLE_PCTV_110i,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1043,
		.subdevice    = 0x4862,
		.driver_data  = SAA7134_BOARD_ASUSTeK_P7131_DUAL,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = PCI_VENDOR_ID_PHILIPS,
		.subdevice    = 0x2018,
		.driver_data  = SAA7134_BOARD_PHILIPS_TIGER,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1462,
		.subdevice    = 0x6231, /* tda8275a, ks003 IR */
		.driver_data  = SAA7134_BOARD_MSI_TVATANYWHERE_PLUS,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1462,
		.subdevice    = 0x8624, /* tda8275, ks003 IR */
		.driver_data  = SAA7134_BOARD_MSI_TVATANYWHERE_PLUS,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x153b,
		.subdevice    = 0x1160,
		.driver_data  = SAA7134_BOARD_CINERGY250PCI,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,	/* SAA 7131E */
		.subvenकरोr    = 0x5168,
		.subdevice    = 0x0319,
		.driver_data  = SAA7134_BOARD_FLYDVB_TRIO,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1461,
		.subdevice    = 0x2c05,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_777,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x5168,
		.subdevice    = 0x0301,
		.driver_data  = SAA7134_BOARD_FLYDVBT_LR301,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x0331,
		.subdevice    = 0x1421,
		.driver_data  = SAA7134_BOARD_ADS_DUO_CARDBUS_PTV331,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x17de,
		.subdevice    = 0x7201,
		.driver_data  = SAA7134_BOARD_TEVION_DVBT_220RF,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x17de,
		.subdevice    = 0x7250,
		.driver_data  = SAA7134_BOARD_KWORLD_DVBT_210,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133, /* SAA7135HL */
		.subvenकरोr    = 0x17de,
		.subdevice    = 0x7350,
		.driver_data  = SAA7134_BOARD_KWORLD_ATSC110,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133, /* SAA7135HL */
		.subvenकरोr    = 0x17de,
		.subdevice    = 0x7352,
		.driver_data  = SAA7134_BOARD_KWORLD_ATSC110, /* ATSC 115 */
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133, /* SAA7135HL */
		.subvenकरोr    = 0x17de,
		.subdevice    = 0xa134,
		.driver_data  = SAA7134_BOARD_KWORLD_PC150U,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1461,
		.subdevice    = 0x7360,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_A169_B,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1461,
		.subdevice    = 0x6360,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_A169_B1,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x16be,
		.subdevice    = 0x0005,
		.driver_data  = SAA7134_BOARD_MD7134_BRIDGE_2,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x5168,
		.subdevice    = 0x0300,
		.driver_data  = SAA7134_BOARD_FLYDVBS_LR300,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x4e42,
		.subdevice    = 0x0300,/* LR300 */
		.driver_data  = SAA7134_BOARD_FLYDVBS_LR300,
	पूर्ण,अणु
		.venकरोr = PCI_VENDOR_ID_PHILIPS,
		.device = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr = 0x1489,
		.subdevice = 0x0301,
		.driver_data = SAA7134_BOARD_FLYDVBT_LR301,
	पूर्ण,अणु
		.venकरोr = PCI_VENDOR_ID_PHILIPS,
		.device = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr = 0x5168, /* Animation Technologies (LअगरeView) */
		.subdevice = 0x0304,
		.driver_data = SAA7134_BOARD_FLYTVPLATINUM_FM,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5168,
		.subdevice    = 0x3306,
		.driver_data  = SAA7134_BOARD_FLYDVBT_HYBRID_CARDBUS,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5168,
		.subdevice    = 0x3502,  /* what's the dअगरference to 0x3306 ?*/
		.driver_data  = SAA7134_BOARD_FLYDVBT_HYBRID_CARDBUS,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5168,
		.subdevice    = 0x3307, /* FlyDVB-T Hybrid Mini PCI */
		.driver_data  = SAA7134_BOARD_FLYDVBT_HYBRID_CARDBUS,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x16be,
		.subdevice    = 0x0007,
		.driver_data  = SAA7134_BOARD_MEDION_MD8800_QUADRO,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x16be,
		.subdevice    = 0x0008,
		.driver_data  = SAA7134_BOARD_MEDION_MD8800_QUADRO,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x16be,
		.subdevice    = 0x000d, /* triple CTX948_V1.1.1 */
		.driver_data  = SAA7134_BOARD_MEDION_MD8800_QUADRO,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461,
		.subdevice    = 0x2c05,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_777,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1489,
		.subdevice    = 0x0502,                /* Cardbus version */
		.driver_data  = SAA7134_BOARD_FLYDVBT_DUO_CARDBUS,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x0919, /* Philips Proteus PRO 2309 */
		.subdevice    = 0x2003,
		.driver_data  = SAA7134_BOARD_PROTEUS_2309,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1461,
		.subdevice    = 0x2c00,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_A16AR,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1043,
		.subdevice    = 0x4860,
		.driver_data  = SAA7134_BOARD_ASUS_EUROPA2_HYBRID,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x11bd,
		.subdevice    = 0x002f,
		.driver_data  = SAA7134_BOARD_PINNACLE_PCTV_310i,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0x9715,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_STUDIO_507,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xa11b,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_STUDIO_507UA,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1043,
		.subdevice    = 0x4876,
		.driver_data  = SAA7134_BOARD_ASUSTeK_P7131_HYBRID_LNA,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x0070,
		.subdevice    = 0x6700,
		.driver_data  = SAA7134_BOARD_HAUPPAUGE_HVR1110,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x0070,
		.subdevice    = 0x6701,
		.driver_data  = SAA7134_BOARD_HAUPPAUGE_HVR1110,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x0070,
		.subdevice    = 0x6702,
		.driver_data  = SAA7134_BOARD_HAUPPAUGE_HVR1110,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x0070,
		.subdevice    = 0x6703,
		.driver_data  = SAA7134_BOARD_HAUPPAUGE_HVR1110,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x0070,
		.subdevice    = 0x6704,
		.driver_data  = SAA7134_BOARD_HAUPPAUGE_HVR1110,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x0070,
		.subdevice    = 0x6705,
		.driver_data  = SAA7134_BOARD_HAUPPAUGE_HVR1110,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x0070,
		.subdevice    = 0x6706,
		.driver_data  = SAA7134_BOARD_HAUPPAUGE_HVR1150,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x0070,
		.subdevice    = 0x6707,
		.driver_data  = SAA7134_BOARD_HAUPPAUGE_HVR1120,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x0070,
		.subdevice    = 0x6708,
		.driver_data  = SAA7134_BOARD_HAUPPAUGE_HVR1150,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x0070,
		.subdevice    = 0x6709,
		.driver_data  = SAA7134_BOARD_HAUPPAUGE_HVR1120,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x0070,
		.subdevice    = 0x670a,
		.driver_data  = SAA7134_BOARD_HAUPPAUGE_HVR1120,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x153b,
		.subdevice    = 0x1172,
		.driver_data  = SAA7134_BOARD_CINERGY_HT_PCMCIA,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = PCI_VENDOR_ID_PHILIPS,
		.subdevice    = 0x2342,
		.driver_data  = SAA7134_BOARD_ENCORE_ENLTV,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x1131,
		.subdevice    = 0x2341,
		.driver_data  = SAA7134_BOARD_ENCORE_ENLTV,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x3016,
		.subdevice    = 0x2344,
		.driver_data  = SAA7134_BOARD_ENCORE_ENLTV,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x1131,
		.subdevice    = 0x230f,
		.driver_data  = SAA7134_BOARD_ENCORE_ENLTV_FM,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x1a7f,
		.subdevice    = 0x2008,
		.driver_data  = SAA7134_BOARD_ENCORE_ENLTV_FM53,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1a7f,
		.subdevice    = 0x2108,
		.driver_data  = SAA7134_BOARD_ENCORE_ENLTV_FM3,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x153b,
		.subdevice    = 0x1175,
		.driver_data  = SAA7134_BOARD_CINERGY_HT_PCI,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xf31e,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_M102,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x4E42,         /* MSI */
		.subdevice    = 0x0306,         /* TV@nywhere DUO */
		.driver_data  = SAA7134_BOARD_FLYDVBTDUO,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1043,
		.subdevice    = 0x4871,
		.driver_data  = SAA7134_BOARD_ASUS_P7131_4871,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1043,
		.subdevice    = 0x4857,		/* REV:1.00 */
		.driver_data  = SAA7134_BOARD_ASUSTeK_TIGER,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x0919, /* SinoVideo PCI 2309 Proteus (7134) */
		.subdevice    = 0x2003, /* OEM cardbus */
		.driver_data  = SAA7134_BOARD_SABRENT_TV_PCB05,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = PCI_VENDOR_ID_PHILIPS,
		.subdevice    = 0x2304,
		.driver_data  = SAA7134_BOARD_10MOONSTVMASTER3,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xf01d, /* AVerTV DVB-T Super 007 */
		.driver_data  = SAA7134_BOARD_AVERMEDIA_SUPER_007,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x0000,
		.subdevice    = 0x4016,
		.driver_data  = SAA7134_BOARD_BEHOLD_401,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x0000,
		.subdevice    = 0x4036,
		.driver_data  = SAA7134_BOARD_BEHOLD_403,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x0000,
		.subdevice    = 0x4037,
		.driver_data  = SAA7134_BOARD_BEHOLD_403FM,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x0000,
		.subdevice    = 0x4050,
		.driver_data  = SAA7134_BOARD_BEHOLD_405,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x0000,
		.subdevice    = 0x4051,
		.driver_data  = SAA7134_BOARD_BEHOLD_405FM,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x0000,
		.subdevice    = 0x4070,
		.driver_data  = SAA7134_BOARD_BEHOLD_407,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x0000,
		.subdevice    = 0x4071,
		.driver_data  = SAA7134_BOARD_BEHOLD_407FM,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x0000,
		.subdevice    = 0x4090,
		.driver_data  = SAA7134_BOARD_BEHOLD_409,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x0000,
		.subdevice    = 0x505B,
		.driver_data  = SAA7134_BOARD_BEHOLD_505RDS_MK5,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x0000,
		.subdevice    = 0x5051,
		.driver_data  = SAA7134_BOARD_BEHOLD_505RDS_MK3,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x5ace,
		.subdevice    = 0x5050,
		.driver_data  = SAA7134_BOARD_BEHOLD_505FM,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x0000,
		.subdevice    = 0x5071,
		.driver_data  = SAA7134_BOARD_BEHOLD_507RDS_MK3,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x0000,
		.subdevice    = 0x507B,
		.driver_data  = SAA7134_BOARD_BEHOLD_507RDS_MK5,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x5ace,
		.subdevice    = 0x5070,
		.driver_data  = SAA7134_BOARD_BEHOLD_507_9FM,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5ace,
		.subdevice    = 0x5090,
		.driver_data  = SAA7134_BOARD_BEHOLD_507_9FM,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x0000,
		.subdevice    = 0x5201,
		.driver_data  = SAA7134_BOARD_BEHOLD_COLUMBUS_TVFM,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x5ace,
		.subdevice    = 0x6070,
		.driver_data  = SAA7134_BOARD_BEHOLD_607FM_MK3,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x5ace,
		.subdevice    = 0x6071,
		.driver_data  = SAA7134_BOARD_BEHOLD_607FM_MK5,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x5ace,
		.subdevice    = 0x6072,
		.driver_data  = SAA7134_BOARD_BEHOLD_607RDS_MK3,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x5ace,
		.subdevice    = 0x6073,
		.driver_data  = SAA7134_BOARD_BEHOLD_607RDS_MK5,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5ace,
		.subdevice    = 0x6090,
		.driver_data  = SAA7134_BOARD_BEHOLD_609FM_MK3,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5ace,
		.subdevice    = 0x6091,
		.driver_data  = SAA7134_BOARD_BEHOLD_609FM_MK5,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5ace,
		.subdevice    = 0x6092,
		.driver_data  = SAA7134_BOARD_BEHOLD_609RDS_MK3,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5ace,
		.subdevice    = 0x6093,
		.driver_data  = SAA7134_BOARD_BEHOLD_609RDS_MK5,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5ace,
		.subdevice    = 0x6190,
		.driver_data  = SAA7134_BOARD_BEHOLD_M6,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5ace,
		.subdevice    = 0x6193,
		.driver_data  = SAA7134_BOARD_BEHOLD_M6_EXTRA,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5ace,
		.subdevice    = 0x6191,
		.driver_data  = SAA7134_BOARD_BEHOLD_M63,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x4e42,
		.subdevice    = 0x3502,
		.driver_data  = SAA7134_BOARD_FLYDVBT_HYBRID_CARDBUS,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1822, /*Twinhan Technology Co. Ltd*/
		.subdevice    = 0x0022,
		.driver_data  = SAA7134_BOARD_TWINHAN_DTV_DVB_3056,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x16be,
		.subdevice    = 0x0010, /* Medion version CTX953_V.1.4.3 */
		.driver_data  = SAA7134_BOARD_CREATIX_CTX953,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1462, /* MSI */
		.subdevice    = 0x8625, /* TV@nywhere A/D v1.1 */
		.driver_data  = SAA7134_BOARD_MSI_TVANYWHERE_AD11,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xf436,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_CARDBUS_506,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xf936,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_A16D,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xa836,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_M115,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x185b,
		.subdevice    = 0xc900,
		.driver_data  = SAA7134_BOARD_VIDEOMATE_T750,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133, /* SAA7135HL */
		.subvenकरोr    = 0x1421,
		.subdevice    = 0x0380,
		.driver_data  = SAA7134_BOARD_ADS_INSTANT_HDTV_PCI,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5169,
		.subdevice    = 0x1502,
		.driver_data  = SAA7134_BOARD_FLYTVPLATINUM_MINI,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5ace,
		.subdevice    = 0x6290,
		.driver_data  = SAA7134_BOARD_BEHOLD_H6,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xf636,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_M103,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xf736,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_M103,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1043,
		.subdevice    = 0x4878, /* REV:1.02G */
		.driver_data  = SAA7134_BOARD_ASUSTeK_TIGER_3IN1,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1043,
		.subdevice    = 0x48cd,
		.driver_data  = SAA7134_BOARD_ASUSTeK_PS3_100,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x17de,
		.subdevice    = 0x7128,
		.driver_data  = SAA7134_BOARD_KWORLD_PLUS_TV_ANALOG,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x17de,
		.subdevice    = 0xb136,
		.driver_data  = SAA7134_BOARD_KWORLD_PCI_SBTVD_FULLSEG,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xf31d,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_GO_007_FM_PLUS,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x185b,
		.subdevice    = 0xc900,
		.driver_data  = SAA7134_BOARD_VIDEOMATE_S350,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5ace, /* Beholder Intl. Ltd. */
		.subdevice    = 0x7595,
		.driver_data  = SAA7134_BOARD_BEHOLD_X7,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x19d1, /* RoverMedia */
		.subdevice    = 0x0138, /* LअगरeView FlyTV Prime30 OEM */
		.driver_data  = SAA7134_BOARD_ROVERMEDIA_LINK_PRO_FM,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = PCI_VENDOR_ID_PHILIPS,
		.subdevice    = 0x2004,
		.driver_data  = SAA7134_BOARD_ZOLID_HYBRID_PCI,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x1043,
		.subdevice    = 0x4847,
		.driver_data  = SAA7134_BOARD_ASUS_EUROPA_HYBRID,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x107d,
		.subdevice    = 0x6655,
		.driver_data  = SAA7134_BOARD_LEADTEK_WINFAST_DTV1000S,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x13c2,
		.subdevice    = 0x2804,
		.driver_data  = SAA7134_BOARD_TECHNOTREND_BUDGET_T3000,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5ace, /* Beholder Intl. Ltd. */
		.subdevice    = 0x7190,
		.driver_data  = SAA7134_BOARD_BEHOLD_H7,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5ace, /* Beholder Intl. Ltd. */
		.subdevice    = 0x7090,
		.driver_data  = SAA7134_BOARD_BEHOLD_A7,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7135,
		.subvenकरोr    = 0x185b,
		.subdevice    = 0xc900,
		.driver_data  = SAA7134_BOARD_VIDEOMATE_M1F,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x5ace,
		.subdevice    = 0x5030,
		.driver_data  = SAA7134_BOARD_BEHOLD_503FM,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x5ace,
		.subdevice    = 0x5010,
		.driver_data  = SAA7134_BOARD_BEHOLD_501,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = 0x17de,
		.subdevice    = 0xd136,
		.driver_data  = SAA7134_BOARD_MAGICPRO_PROHDTV_PRO2,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x6000,
		.subdevice    = 0x0811,
		.driver_data  = SAA7134_BOARD_SENSORAY811_911,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x6000,
		.subdevice    = 0x0911,
		.driver_data  = SAA7134_BOARD_SENSORAY811_911,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0x2055, /* AverTV Satellite Hybrid+FM A706 */
		.driver_data  = SAA7134_BOARD_AVERMEDIA_A706,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1905, /* WIS */
		.subdevice    = 0x7007,
		.driver_data  = SAA7134_BOARD_WIS_VOYAGER,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x1461, /* Avermedia Technologies Inc */
		.subdevice    = 0xa10a,
		.driver_data  = SAA7134_BOARD_AVERMEDIA_505,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = 0x107d,
		.subdevice    = 0x6f3a,
		.driver_data  = SAA7134_BOARD_LEADTEK_WINFAST_TV2100_FM,
	पूर्ण, अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = 0x1779, /* V One Mulसमयdia PTE Ltd */
		.subdevice    = 0x13cf,
		.driver_data  = SAA7134_BOARD_SNAZIO_TVPVR_PRO,
	पूर्ण, अणु
		/* --- boards without eeprom + subप्रणाली ID --- */
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = PCI_VENDOR_ID_PHILIPS,
		.subdevice    = 0,
		.driver_data  = SAA7134_BOARD_NOAUTO,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = PCI_VENDOR_ID_PHILIPS,
		.subdevice    = 0,
		.driver_data  = SAA7134_BOARD_NOAUTO,
	पूर्ण,अणु
		/* --- शेष catch --- */
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7130,
		.subvenकरोr    = PCI_ANY_ID,
		.subdevice    = PCI_ANY_ID,
		.driver_data  = SAA7134_BOARD_UNKNOWN,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7133,
		.subvenकरोr    = PCI_ANY_ID,
		.subdevice    = PCI_ANY_ID,
		.driver_data  = SAA7134_BOARD_UNKNOWN,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7134,
		.subvenकरोr    = PCI_ANY_ID,
		.subdevice    = PCI_ANY_ID,
		.driver_data  = SAA7134_BOARD_UNKNOWN,
	पूर्ण,अणु
		.venकरोr       = PCI_VENDOR_ID_PHILIPS,
		.device       = PCI_DEVICE_ID_PHILIPS_SAA7135,
		.subvenकरोr    = PCI_ANY_ID,
		.subdevice    = PCI_ANY_ID,
		.driver_data  = SAA7134_BOARD_UNKNOWN,
	पूर्ण,अणु
		/* --- end of list --- */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, saa7134_pci_tbl);

/* ----------------------------------------------------------- */
/* flyvideo tweaks                                             */


अटल व्योम board_flyvideo(काष्ठा saa7134_dev *dev)
अणु
	pr_warn("%s: there are different flyvideo cards with different tuners\n"
		"%s: out there, you might have to use the tuner=<nr> insmod\n"
		"%s: option to override the default value.\n",
		dev->name, dev->name, dev->name);
पूर्ण

अटल पूर्णांक saa7134_xc2028_callback(काष्ठा saa7134_dev *dev,
				   पूर्णांक command, पूर्णांक arg)
अणु
	चयन (command) अणु
	हाल XC2028_TUNER_RESET:
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x00008000, 0x00000000);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x00008000, 0x00008000);
		चयन (dev->board) अणु
		हाल SAA7134_BOARD_AVERMEDIA_CARDBUS_506:
		हाल SAA7134_BOARD_AVERMEDIA_M103:
			saa7134_set_gpio(dev, 23, 0);
			msleep(10);
			saa7134_set_gpio(dev, 23, 1);
		अवरोध;
		हाल SAA7134_BOARD_AVERMEDIA_A16D:
			saa7134_set_gpio(dev, 21, 0);
			msleep(10);
			saa7134_set_gpio(dev, 21, 1);
		अवरोध;
		हाल SAA7134_BOARD_AVERMEDIA_A700_HYBRID:
			saa7134_set_gpio(dev, 18, 0);
			msleep(10);
			saa7134_set_gpio(dev, 18, 1);
		अवरोध;
		हाल SAA7134_BOARD_VIDEOMATE_T750:
			saa7134_set_gpio(dev, 20, 0);
			msleep(10);
			saa7134_set_gpio(dev, 20, 1);
		अवरोध;
		पूर्ण
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक saa7134_xc5000_callback(काष्ठा saa7134_dev *dev,
				   पूर्णांक command, पूर्णांक arg)
अणु
	चयन (dev->board) अणु
	हाल SAA7134_BOARD_BEHOLD_X7:
	हाल SAA7134_BOARD_BEHOLD_H7:
	हाल SAA7134_BOARD_BEHOLD_A7:
		अगर (command == XC5000_TUNER_RESET) अणु
		/* Down and UP pheripherial RESET pin क्रम reset all chips */
			saa_ग_लिखोb(SAA7134_SPECIAL_MODE, 0x00);
			msleep(10);
			saa_ग_लिखोb(SAA7134_SPECIAL_MODE, 0x01);
			msleep(10);
		पूर्ण
		अवरोध;
	शेष:
		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2, 0x06e20000, 0x06e20000);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x06a20000, 0x06a20000);
		saa_anकरोrl(SAA7133_ANALOG_IO_SELECT >> 2, 0x02, 0x02);
		saa_anकरोrl(SAA7134_ANALOG_IN_CTRL1 >> 2, 0x81, 0x81);
		saa_anकरोrl(SAA7134_AUDIO_CLOCK0 >> 2, 0x03187de7, 0x03187de7);
		saa_anकरोrl(SAA7134_AUDIO_PLL_CTRL >> 2, 0x03, 0x03);
		saa_anकरोrl(SAA7134_AUDIO_CLOCKS_PER_FIELD0 >> 2,
			   0x0001e000, 0x0001e000);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_tda8290_827x_callback(काष्ठा saa7134_dev *dev,
					 पूर्णांक command, पूर्णांक arg)
अणु
	u8 sync_control;

	चयन (command) अणु
	हाल 0: /* चयन LNA gain through GPIO 22*/
		saa7134_set_gpio(dev, 22, arg) ;
		अवरोध;
	हाल 1: /* vsync output at GPIO22. 50 / 60Hz */
		saa_anकरोrb(SAA7134_VIDEO_PORT_CTRL3, 0x80, 0x80);
		saa_anकरोrb(SAA7134_VIDEO_PORT_CTRL6, 0x0f, 0x03);
		अगर (arg == 1)
			sync_control = 11;
		अन्यथा
			sync_control = 17;
		saa_ग_लिखोb(SAA7134_VGATE_START, sync_control);
		saa_ग_लिखोb(SAA7134_VGATE_STOP, sync_control + 1);
		saa_anकरोrb(SAA7134_MISC_VGATE_MSB, 0x03, 0x00);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक saa7134_tda18271_hvr11x0_toggle_agc(काष्ठा saa7134_dev *dev,
						      क्रमागत tda18271_mode mode)
अणु
	/* toggle AGC चयन through GPIO 26 */
	चयन (mode) अणु
	हाल TDA18271_ANALOG:
		saa7134_set_gpio(dev, 26, 0);
		अवरोध;
	हाल TDA18271_DIGITAL:
		saa7134_set_gpio(dev, 26, 1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक saa7134_kworld_sbtvd_toggle_agc(काष्ठा saa7134_dev *dev,
						  क्रमागत tda18271_mode mode)
अणु
	/* toggle AGC चयन through GPIO 27 */
	चयन (mode) अणु
	हाल TDA18271_ANALOG:
		saa_ग_लिखोl(SAA7134_GPIO_GPMODE0 >> 2, 0x4000);
		saa_ग_लिखोl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x4000);
		msleep(20);
		अवरोध;
	हाल TDA18271_DIGITAL:
		saa_ग_लिखोl(SAA7134_GPIO_GPMODE0 >> 2, 0x14000);
		saa_ग_लिखोl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x14000);
		msleep(20);
		saa_ग_लिखोl(SAA7134_GPIO_GPMODE0 >> 2, 0x54000);
		saa_ग_लिखोl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x54000);
		msleep(30);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_kworld_pc150u_toggle_agc(काष्ठा saa7134_dev *dev,
					    क्रमागत tda18271_mode mode)
अणु
	चयन (mode) अणु
	हाल TDA18271_ANALOG:
		saa7134_set_gpio(dev, 18, 0);
		अवरोध;
	हाल TDA18271_DIGITAL:
		saa7134_set_gpio(dev, 18, 1);
		msleep(30);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_tda8290_18271_callback(काष्ठा saa7134_dev *dev,
					  पूर्णांक command, पूर्णांक arg)
अणु
	पूर्णांक ret = 0;

	चयन (command) अणु
	हाल TDA18271_CALLBACK_CMD_AGC_ENABLE: /* 0 */
		चयन (dev->board) अणु
		हाल SAA7134_BOARD_HAUPPAUGE_HVR1150:
		हाल SAA7134_BOARD_HAUPPAUGE_HVR1120:
		हाल SAA7134_BOARD_MAGICPRO_PROHDTV_PRO2:
			ret = saa7134_tda18271_hvr11x0_toggle_agc(dev, arg);
			अवरोध;
		हाल SAA7134_BOARD_KWORLD_PCI_SBTVD_FULLSEG:
			ret = saa7134_kworld_sbtvd_toggle_agc(dev, arg);
			अवरोध;
		हाल SAA7134_BOARD_KWORLD_PC150U:
			ret = saa7134_kworld_pc150u_toggle_agc(dev, arg);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक saa7134_tda8290_callback(काष्ठा saa7134_dev *dev,
				    पूर्णांक command, पूर्णांक arg)
अणु
	पूर्णांक ret;

	चयन (dev->board) अणु
	हाल SAA7134_BOARD_HAUPPAUGE_HVR1150:
	हाल SAA7134_BOARD_HAUPPAUGE_HVR1120:
	हाल SAA7134_BOARD_AVERMEDIA_M733A:
	हाल SAA7134_BOARD_KWORLD_PCI_SBTVD_FULLSEG:
	हाल SAA7134_BOARD_KWORLD_PC150U:
	हाल SAA7134_BOARD_MAGICPRO_PROHDTV_PRO2:
		/* tda8290 + tda18271 */
		ret = saa7134_tda8290_18271_callback(dev, command, arg);
		अवरोध;
	शेष:
		/* tda8290 + tda827x */
		ret = saa7134_tda8290_827x_callback(dev, command, arg);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक saa7134_tuner_callback(व्योम *priv, पूर्णांक component, पूर्णांक command, पूर्णांक arg)
अणु
	काष्ठा saa7134_dev *dev = priv;

	अगर (dev != शून्य) अणु
		चयन (dev->tuner_type) अणु
		हाल TUNER_PHILIPS_TDA8290:
			वापस saa7134_tda8290_callback(dev, command, arg);
		हाल TUNER_XC2028:
			वापस saa7134_xc2028_callback(dev, command, arg);
		हाल TUNER_XC5000:
			वापस saa7134_xc5000_callback(dev, command, arg);
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_err("saa7134: Error - device struct undefined.\n");
		वापस -EINVAL;
	पूर्ण
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(saa7134_tuner_callback);

/* ----------------------------------------------------------- */

अटल व्योम hauppauge_eeprom(काष्ठा saa7134_dev *dev, u8 *eeprom_data)
अणु
	काष्ठा tveeprom tv;

	tveeprom_hauppauge_analog(&tv, eeprom_data);

	/* Make sure we support the board model */
	चयन (tv.model) अणु
	हाल 67019: /* WinTV-HVR1110 (Retail, IR Blaster, hybrid, FM, SVid/Comp, 3.5mm audio in) */
	हाल 67109: /* WinTV-HVR1000 (Retail, IR Receive, analog, no FM, SVid/Comp, 3.5mm audio in) */
	हाल 67201: /* WinTV-HVR1150 (Retail, IR Receive, hybrid, FM, SVid/Comp, 3.5mm audio in) */
	हाल 67301: /* WinTV-HVR1000 (Retail, IR Receive, analog, no FM, SVid/Comp, 3.5mm audio in) */
	हाल 67209: /* WinTV-HVR1110 (Retail, IR Receive, hybrid, FM, SVid/Comp, 3.5mm audio in) */
	हाल 67559: /* WinTV-HVR1110 (OEM, no IR, hybrid, FM, SVid/Comp, RCA aud) */
	हाल 67569: /* WinTV-HVR1110 (OEM, no IR, hybrid, FM) */
	हाल 67579: /* WinTV-HVR1110 (OEM, no IR, hybrid, no FM) */
	हाल 67589: /* WinTV-HVR1110 (OEM, no IR, hybrid, no FM, SVid/Comp, RCA aud) */
	हाल 67599: /* WinTV-HVR1110 (OEM, no IR, hybrid, no FM, SVid/Comp, RCA aud) */
	हाल 67651: /* WinTV-HVR1150 (OEM, no IR, hybrid, FM, SVid/Comp, RCA aud) */
	हाल 67659: /* WinTV-HVR1110 (OEM, no IR, hybrid, FM, SVid/Comp, RCA aud) */
		अवरोध;
	शेष:
		pr_warn("%s: warning: unknown hauppauge model #%d\n",
			dev->name, tv.model);
		अवरोध;
	पूर्ण

	pr_info("%s: hauppauge eeprom: model=%d\n",
	       dev->name, tv.model);
पूर्ण

/* ----------------------------------------------------------- */

पूर्णांक saa7134_board_init1(काष्ठा saa7134_dev *dev)
अणु
	/* Always prपूर्णांक gpio, often manufacturers encode tuner type and other info. */
	saa_ग_लिखोl(SAA7134_GPIO_GPMODE0 >> 2, 0);
	dev->gpio_value = saa_पढ़ोl(SAA7134_GPIO_GPSTATUS0 >> 2);
	pr_info("%s: board init: gpio is %x\n", dev->name, dev->gpio_value);

	चयन (dev->board) अणु
	हाल SAA7134_BOARD_FLYVIDEO2000:
	हाल SAA7134_BOARD_FLYVIDEO3000:
	हाल SAA7134_BOARD_FLYVIDEO3000_NTSC:
		dev->has_remote = SAA7134_REMOTE_GPIO;
		board_flyvideo(dev);
		अवरोध;
	हाल SAA7134_BOARD_FLYTVPLATINUM_MINI2:
	हाल SAA7134_BOARD_FLYTVPLATINUM_FM:
	हाल SAA7134_BOARD_CINERGY400:
	हाल SAA7134_BOARD_CINERGY600:
	हाल SAA7134_BOARD_CINERGY600_MK3:
	हाल SAA7134_BOARD_ECS_TVP3XP:
	हाल SAA7134_BOARD_ECS_TVP3XP_4CB5:
	हाल SAA7134_BOARD_ECS_TVP3XP_4CB6:
	हाल SAA7134_BOARD_MD2819:
	हाल SAA7134_BOARD_KWORLD_VSTREAM_XPERT:
	हाल SAA7134_BOARD_KWORLD_XPERT:
	हाल SAA7134_BOARD_AVERMEDIA_STUDIO_305:
	हाल SAA7134_BOARD_AVERMEDIA_305:
	हाल SAA7134_BOARD_AVERMEDIA_STUDIO_505:
	हाल SAA7134_BOARD_AVERMEDIA_505:
	हाल SAA7134_BOARD_AVERMEDIA_STUDIO_307:
	हाल SAA7134_BOARD_AVERMEDIA_307:
	हाल SAA7134_BOARD_AVERMEDIA_STUDIO_507:
	हाल SAA7134_BOARD_AVERMEDIA_GO_007_FM:
	हाल SAA7134_BOARD_AVERMEDIA_777:
	हाल SAA7134_BOARD_AVERMEDIA_M135A:
/*      हाल SAA7134_BOARD_SABRENT_SBTTVFM:  */ /* not finished yet */
	हाल SAA7134_BOARD_VIDEOMATE_TV_PVR:
	हाल SAA7134_BOARD_VIDEOMATE_GOLD_PLUS:
	हाल SAA7134_BOARD_VIDEOMATE_TV_GOLD_PLUSII:
	हाल SAA7134_BOARD_VIDEOMATE_M1F:
	हाल SAA7134_BOARD_VIDEOMATE_DVBT_300:
	हाल SAA7134_BOARD_VIDEOMATE_DVBT_200:
	हाल SAA7134_BOARD_VIDEOMATE_DVBT_200A:
	हाल SAA7134_BOARD_MANLI_MTV001:
	हाल SAA7134_BOARD_MANLI_MTV002:
	हाल SAA7134_BOARD_BEHOLD_409FM:
	हाल SAA7134_BOARD_AVACSSMARTTV:
	हाल SAA7134_BOARD_GOTVIEW_7135:
	हाल SAA7134_BOARD_KWORLD_TERMINATOR:
	हाल SAA7134_BOARD_SEDNA_PC_TV_CARDBUS:
	हाल SAA7134_BOARD_FLYDVBT_LR301:
	हाल SAA7134_BOARD_ASUSTeK_PS3_100:
	हाल SAA7134_BOARD_ASUSTeK_P7131_DUAL:
	हाल SAA7134_BOARD_ASUSTeK_P7131_HYBRID_LNA:
	हाल SAA7134_BOARD_ASUSTeK_P7131_ANALOG:
	हाल SAA7134_BOARD_FLYDVBTDUO:
	हाल SAA7134_BOARD_PROTEUS_2309:
	हाल SAA7134_BOARD_AVERMEDIA_A16AR:
	हाल SAA7134_BOARD_ENCORE_ENLTV:
	हाल SAA7134_BOARD_ENCORE_ENLTV_FM:
	हाल SAA7134_BOARD_ENCORE_ENLTV_FM53:
	हाल SAA7134_BOARD_ENCORE_ENLTV_FM3:
	हाल SAA7134_BOARD_10MOONSTVMASTER3:
	हाल SAA7134_BOARD_BEHOLD_401:
	हाल SAA7134_BOARD_BEHOLD_403:
	हाल SAA7134_BOARD_BEHOLD_403FM:
	हाल SAA7134_BOARD_BEHOLD_405:
	हाल SAA7134_BOARD_BEHOLD_405FM:
	हाल SAA7134_BOARD_BEHOLD_407:
	हाल SAA7134_BOARD_BEHOLD_407FM:
	हाल SAA7134_BOARD_BEHOLD_409:
	हाल SAA7134_BOARD_BEHOLD_505FM:
	हाल SAA7134_BOARD_BEHOLD_505RDS_MK5:
	हाल SAA7134_BOARD_BEHOLD_505RDS_MK3:
	हाल SAA7134_BOARD_BEHOLD_507_9FM:
	हाल SAA7134_BOARD_BEHOLD_507RDS_MK3:
	हाल SAA7134_BOARD_BEHOLD_507RDS_MK5:
	हाल SAA7134_BOARD_GENIUS_TVGO_A11MCE:
	हाल SAA7134_BOARD_REAL_ANGEL_220:
	हाल SAA7134_BOARD_KWORLD_PLUS_TV_ANALOG:
	हाल SAA7134_BOARD_AVERMEDIA_GO_007_FM_PLUS:
	हाल SAA7134_BOARD_ROVERMEDIA_LINK_PRO_FM:
	हाल SAA7134_BOARD_LEADTEK_WINFAST_DTV1000S:
	हाल SAA7134_BOARD_LEADTEK_WINFAST_TV2100_FM:
		dev->has_remote = SAA7134_REMOTE_GPIO;
		अवरोध;
	हाल SAA7134_BOARD_FLYDVBS_LR300:
		saa_ग_लिखोb(SAA7134_GPIO_GPMODE3, 0x80);
		saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS2, 0x40);
		dev->has_remote = SAA7134_REMOTE_GPIO;
		अवरोध;
	हाल SAA7134_BOARD_MD5044:
		pr_warn("%s: seems there are two different versions of the MD5044\n"
			"%s: (with the same ID) out there.  If sound doesn't work for\n"
			"%s: you try the audio_clock_override=0x200000 insmod option.\n",
			dev->name, dev->name, dev->name);
		अवरोध;
	हाल SAA7134_BOARD_CINERGY400_CARDBUS:
		/* घातer-up tuner chip */
		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2,   0x00040000, 0x00040000);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x00040000, 0x00000000);
		अवरोध;
	हाल SAA7134_BOARD_PINNACLE_300I_DVBT_PAL:
		/* this turns the remote control chip off to work around a bug in it */
		saa_ग_लिखोb(SAA7134_GPIO_GPMODE1, 0x80);
		saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS1, 0x80);
		अवरोध;
	हाल SAA7134_BOARD_MONSTERTV_MOBILE:
		/* घातer-up tuner chip */
		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2,   0x00040000, 0x00040000);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x00040000, 0x00000004);
		अवरोध;
	हाल SAA7134_BOARD_FLYDVBT_DUO_CARDBUS:
		/* turn the fan on */
		saa_ग_लिखोb(SAA7134_GPIO_GPMODE3, 0x08);
		saa_ग_लिखोb(SAA7134_GPIO_GPSTATUS3, 0x06);
		अवरोध;
	हाल SAA7134_BOARD_ADS_DUO_CARDBUS_PTV331:
	हाल SAA7134_BOARD_FLYDVBT_HYBRID_CARDBUS:
		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2, 0x08000000, 0x08000000);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x08000000, 0x00000000);
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_CARDBUS:
	हाल SAA7134_BOARD_AVERMEDIA_M115:
		/* घातer-करोwn tuner chip */
		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2,   0xffffffff, 0);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, 0xffffffff, 0);
		msleep(10);
		/* घातer-up tuner chip */
		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2,   0xffffffff, 0xffffffff);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, 0xffffffff, 0xffffffff);
		msleep(10);
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_CARDBUS_501:
		/* घातer-करोwn tuner chip */
		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2,   0x08400000, 0x08400000);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x08400000, 0);
		msleep(10);
		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2,   0x08400000, 0x08400000);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x08400000, 0x08400000);
		msleep(10);
		dev->has_remote = SAA7134_REMOTE_I2C;
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_CARDBUS_506:
		saa7134_set_gpio(dev, 23, 0);
		msleep(10);
		saa7134_set_gpio(dev, 23, 1);
		dev->has_remote = SAA7134_REMOTE_I2C;
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_M103:
		saa7134_set_gpio(dev, 23, 0);
		msleep(10);
		saa7134_set_gpio(dev, 23, 1);
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_A16D:
		saa7134_set_gpio(dev, 21, 0);
		msleep(10);
		saa7134_set_gpio(dev, 21, 1);
		msleep(1);
		dev->has_remote = SAA7134_REMOTE_GPIO;
		अवरोध;
	हाल SAA7134_BOARD_BEHOLD_COLUMBUS_TVFM:
		/* घातer-करोwn tuner chip */
		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2,   0x000A8004, 0x000A8004);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x000A8004, 0);
		msleep(10);
		/* घातer-up tuner chip */
		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2,   0x000A8004, 0x000A8004);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x000A8004, 0x000A8004);
		msleep(10);
		/* remote via GPIO */
		dev->has_remote = SAA7134_REMOTE_GPIO;
		अवरोध;
	हाल SAA7134_BOARD_RTD_VFG7350:

		/*
		 * Make sure Production Test Register at offset 0x1D1 is cleared
		 * to take chip out of test mode.  Clearing bit 4 (TST_EN_AOUT)
		 * prevents pin 105 from reमुख्यing low; keeping pin 105 low
		 * continually resets the SAA6752 chip.
		 */

		saa_ग_लिखोb (SAA7134_PRODUCTION_TEST_MODE, 0x00);
		अवरोध;
	हाल SAA7134_BOARD_HAUPPAUGE_HVR1150:
	हाल SAA7134_BOARD_HAUPPAUGE_HVR1120:
		dev->has_remote = SAA7134_REMOTE_GPIO;
		/* GPIO 26 high क्रम digital, low क्रम analog */
		saa7134_set_gpio(dev, 26, 0);
		msleep(1);

		saa7134_set_gpio(dev, 22, 0);
		msleep(10);
		saa7134_set_gpio(dev, 22, 1);
		अवरोध;
	/* i2c remotes */
	हाल SAA7134_BOARD_PINNACLE_PCTV_110i:
	हाल SAA7134_BOARD_PINNACLE_PCTV_310i:
	हाल SAA7134_BOARD_UPMOST_PURPLE_TV:
	हाल SAA7134_BOARD_MSI_TVATANYWHERE_PLUS:
	हाल SAA7134_BOARD_HAUPPAUGE_HVR1110:
	हाल SAA7134_BOARD_BEHOLD_607FM_MK3:
	हाल SAA7134_BOARD_BEHOLD_607FM_MK5:
	हाल SAA7134_BOARD_BEHOLD_609FM_MK3:
	हाल SAA7134_BOARD_BEHOLD_609FM_MK5:
	हाल SAA7134_BOARD_BEHOLD_607RDS_MK3:
	हाल SAA7134_BOARD_BEHOLD_607RDS_MK5:
	हाल SAA7134_BOARD_BEHOLD_609RDS_MK3:
	हाल SAA7134_BOARD_BEHOLD_609RDS_MK5:
	हाल SAA7134_BOARD_BEHOLD_M6:
	हाल SAA7134_BOARD_BEHOLD_M63:
	हाल SAA7134_BOARD_BEHOLD_M6_EXTRA:
	हाल SAA7134_BOARD_BEHOLD_H6:
	हाल SAA7134_BOARD_BEHOLD_X7:
	हाल SAA7134_BOARD_BEHOLD_H7:
	हाल SAA7134_BOARD_BEHOLD_A7:
	हाल SAA7134_BOARD_KWORLD_PC150U:
	हाल SAA7134_BOARD_SNAZIO_TVPVR_PRO:
		dev->has_remote = SAA7134_REMOTE_I2C;
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_A169_B:
		pr_warn("%s: %s: dual saa713x broadcast decoders\n"
			"%s: Sorry, none of the inputs to this chip are supported yet.\n"
			"%s: Dual decoder functionality is disabled for now, use the other chip.\n",
			dev->name, card(dev).name, dev->name, dev->name);
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_M102:
		/* enable tuner */
	       dev->has_remote = SAA7134_REMOTE_GPIO;
		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2,   0x8c040007, 0x8c040007);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x0c0007cd, 0x0c0007cd);
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_A700_HYBRID:
	हाल SAA7134_BOARD_AVERMEDIA_A700_PRO:
		/* ग_लिखो winकरोws gpio values */
		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2,   0x80040100, 0x80040100);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x80040100, 0x00040100);
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_A706:
		/* radio antenna select: tristate both as in Winकरोws driver */
		saa7134_set_gpio(dev, 12, 3);	/* TV antenna */
		saa7134_set_gpio(dev, 13, 3);	/* FM antenna */
		dev->has_remote = SAA7134_REMOTE_I2C;
		/*
		 * Disable CE5039 DVB-S tuner now (SLEEP pin high) to prevent
		 * it from पूर्णांकerfering with analog tuner detection
		 */
		saa7134_set_gpio(dev, 23, 1);
		अवरोध;
	हाल SAA7134_BOARD_VIDEOMATE_S350:
		dev->has_remote = SAA7134_REMOTE_GPIO;
		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2,   0x0000C000, 0x0000C000);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x0000C000, 0x0000C000);
		अवरोध;
	हाल SAA7134_BOARD_AVERMEDIA_M733A:
		saa7134_set_gpio(dev, 1, 1);
		msleep(10);
		saa7134_set_gpio(dev, 1, 0);
		msleep(10);
		saa7134_set_gpio(dev, 1, 1);
		dev->has_remote = SAA7134_REMOTE_GPIO;
		अवरोध;
	हाल SAA7134_BOARD_MAGICPRO_PROHDTV_PRO2:
		/* enable LGS-8G75 */
		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2,   0x0e050000, 0x0c050000);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x0e050000, 0x0c050000);
		अवरोध;
	हाल SAA7134_BOARD_VIDEOMATE_T750:
		/* enable the analog tuner */
		saa_anकरोrl(SAA7134_GPIO_GPMODE0 >> 2,   0x00008000, 0x00008000);
		saa_anकरोrl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x00008000, 0x00008000);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम saa7134_tuner_setup(काष्ठा saa7134_dev *dev)
अणु
	काष्ठा tuner_setup tun_setup;
	अचिन्हित पूर्णांक mode_mask = T_RADIO | T_ANALOG_TV;

	स_रखो(&tun_setup, 0, माप(tun_setup));
	tun_setup.tuner_callback = saa7134_tuner_callback;

	अगर (saa7134_boards[dev->board].radio_type != UNSET) अणु
		tun_setup.type = saa7134_boards[dev->board].radio_type;
		tun_setup.addr = saa7134_boards[dev->board].radio_addr;

		tun_setup.mode_mask = T_RADIO;

		saa_call_all(dev, tuner, s_type_addr, &tun_setup);
		mode_mask &= ~T_RADIO;
	पूर्ण

	अगर ((dev->tuner_type != TUNER_ABSENT) && (dev->tuner_type != UNSET)) अणु
		tun_setup.type = dev->tuner_type;
		tun_setup.addr = dev->tuner_addr;
		tun_setup.config = &saa7134_boards[dev->board].tda829x_conf;
		tun_setup.tuner_callback = saa7134_tuner_callback;

		tun_setup.mode_mask = mode_mask;

		saa_call_all(dev, tuner, s_type_addr, &tun_setup);
	पूर्ण

	अगर (dev->tda9887_conf) अणु
		काष्ठा v4l2_priv_tun_config tda9887_cfg;

		tda9887_cfg.tuner = TUNER_TDA9887;
		tda9887_cfg.priv = &dev->tda9887_conf;

		saa_call_all(dev, tuner, s_config, &tda9887_cfg);
	पूर्ण

	अगर (dev->tuner_type == TUNER_XC2028) अणु
		काष्ठा v4l2_priv_tun_config  xc2028_cfg;
		काष्ठा xc2028_ctrl           ctl;

		स_रखो(&xc2028_cfg, 0, माप(xc2028_cfg));
		स_रखो(&ctl, 0, माप(ctl));

		ctl.fname   = XC2028_DEFAULT_FIRMWARE;
		ctl.max_len = 64;

		चयन (dev->board) अणु
		हाल SAA7134_BOARD_AVERMEDIA_A16D:
		हाल SAA7134_BOARD_AVERMEDIA_CARDBUS_506:
		हाल SAA7134_BOARD_AVERMEDIA_M103:
		हाल SAA7134_BOARD_AVERMEDIA_A700_HYBRID:
			ctl.demod = XC3028_FE_ZARLINK456;
			अवरोध;
		शेष:
			ctl.demod = XC3028_FE_OREN538;
			ctl.mts = 1;
		पूर्ण

		xc2028_cfg.tuner = TUNER_XC2028;
		xc2028_cfg.priv  = &ctl;

		saa_call_all(dev, tuner, s_config, &xc2028_cfg);
	पूर्ण
पूर्ण

/* stuff which needs working i2c */
पूर्णांक saa7134_board_init2(काष्ठा saa7134_dev *dev)
अणु
	अचिन्हित अक्षर buf;
	पूर्णांक board;

	/* Put here the code that enables the chips that are needed
	   क्रम analog mode and करोesn't depend on the tuner attachment.
	   It is also a good idea to get tuner type from eeprom, etc beक्रमe
	   initializing tuner, since we can aव्योम loading tuner driver
	   on devices that has TUNER_ABSENT
	 */
	चयन (dev->board) अणु
	हाल SAA7134_BOARD_BMK_MPEX_NOTUNER:
	हाल SAA7134_BOARD_BMK_MPEX_TUNER:
		/* Checks अगर the device has a tuner at 0x60 addr
		   If the device करोesn't have a tuner, TUNER_ABSENT
		   will be used at tuner_type, aव्योमing loading tuner
		   without needing it
		 */
		dev->i2c_client.addr = 0x60;
		board = (i2c_master_recv(&dev->i2c_client, &buf, 0) < 0)
			? SAA7134_BOARD_BMK_MPEX_NOTUNER
			: SAA7134_BOARD_BMK_MPEX_TUNER;
		अगर (board == dev->board)
			अवरोध;
		dev->board = board;
		pr_warn("%s: board type fixup: %s\n", dev->name,
		saa7134_boards[dev->board].name);
		dev->tuner_type = saa7134_boards[dev->board].tuner_type;

		अवरोध;
	हाल SAA7134_BOARD_MD7134:
	अणु
		u8 subaddr;
		u8 data[3], data1[] = अणु 0x09, 0x9f, 0x86, 0x11पूर्ण;
		पूर्णांक ret, tuner_t;
		काष्ठा i2c_msg msg[] = अणुअणु.addr = 0x50, .flags = 0, .buf = &subaddr, .len = 1पूर्ण,
					अणु.addr = 0x50, .flags = I2C_M_RD, .buf = data, .len = 3पूर्णपूर्ण,
				msg1 = अणु.addr = 0x61, .flags = 0, .buf = data1, .len = माप(data1)पूर्ण;

		subaddr= 0x14;
		tuner_t = 0;

		/* Retrieve device data from eeprom, checking क्रम the
		   proper tuner_type.
		 */
		ret = i2c_transfer(&dev->i2c_adap, msg, 2);
		अगर (ret != 2) अणु
			pr_err("EEPROM read failure\n");
		पूर्ण अन्यथा अगर ((data[0] != 0) && (data[0] != 0xff)) अणु
			/* old config काष्ठाure */
			subaddr = data[0] + 2;
			msg[1].len = 2;
			i2c_transfer(&dev->i2c_adap, msg, 2);
			tuner_t = (data[0] << 8) + data[1];
			चयन (tuner_t)अणु
			हाल 0x0103:
				dev->tuner_type = TUNER_PHILIPS_PAL;
				अवरोध;
			हाल 0x010C:
				dev->tuner_type = TUNER_PHILIPS_FM1216ME_MK3;
				अवरोध;
			शेष:
				pr_err("%s Can't determine tuner type %x from EEPROM\n",
				       dev->name, tuner_t);
			पूर्ण
		पूर्ण अन्यथा अगर ((data[1] != 0) && (data[1] != 0xff)) अणु
			/* new config काष्ठाure */
			subaddr = data[1] + 1;
			msg[1].len = 1;
			i2c_transfer(&dev->i2c_adap, msg, 2);
			subaddr = data[0] + 1;
			msg[1].len = 2;
			i2c_transfer(&dev->i2c_adap, msg, 2);
			tuner_t = (data[1] << 8) + data[0];
			चयन (tuner_t) अणु
			हाल 0x0005:
				dev->tuner_type = TUNER_PHILIPS_FM1216ME_MK3;
				अवरोध;
			हाल 0x001d:
				dev->tuner_type = TUNER_PHILIPS_FMD1216ME_MK3;
				pr_info("%s Board has DVB-T\n",
				       dev->name);
				अवरोध;
			शेष:
				pr_err("%s Can't determine tuner type %x from EEPROM\n",
				       dev->name, tuner_t);
			पूर्ण
		पूर्ण अन्यथा अणु
			pr_err("%s unexpected config structure\n", dev->name);
		पूर्ण

		pr_info("%s Tuner type is %d\n", dev->name, dev->tuner_type);

		/* The tuner TUNER_PHILIPS_FMD1216ME_MK3 after hardware    */
		/* start has disabled IF and enabled DVB-T. When saa7134   */
		/* scan I2C devices it will not detect IF tda9887 and can`t*/
		/* watch TV without software reboot. To solve this problem */
		/* चयन the tuner to analog TV mode manually.            */
		अगर (dev->tuner_type == TUNER_PHILIPS_FMD1216ME_MK3) अणु
			अगर (i2c_transfer(&dev->i2c_adap, &msg1, 1) != 1)
				prपूर्णांकk(KERN_WARNING "%s: Unable to enable IF of the tuner.\n", dev->name);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल SAA7134_BOARD_PHILIPS_EUROPA:
		अगर (dev->स्वतःdetected && (dev->eedata[0x41] == 0x1c)) अणु
			/* Reconfigure board as Snake reference design */
			dev->board = SAA7134_BOARD_PHILIPS_SNAKE;
			dev->tuner_type = saa7134_boards[dev->board].tuner_type;
			pr_info("%s: Reconfigured board as %s\n",
				dev->name, saa7134_boards[dev->board].name);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल SAA7134_BOARD_VIDEOMATE_DVBT_300:
	हाल SAA7134_BOARD_ASUS_EUROPA2_HYBRID:
	हाल SAA7134_BOARD_ASUS_EUROPA_HYBRID:
	हाल SAA7134_BOARD_TECHNOTREND_BUDGET_T3000:
	अणु

		/* The Philips EUROPA based hybrid boards have the tuner
		   connected through the channel decoder. We have to make it
		   transparent to find it
		 */
		u8 data[] = अणु 0x07, 0x02पूर्ण;
		काष्ठा i2c_msg msg = अणु.addr=0x08, .flags=0, .buf=data, .len = माप(data)पूर्ण;
		i2c_transfer(&dev->i2c_adap, &msg, 1);

		अवरोध;
	पूर्ण
	हाल SAA7134_BOARD_PHILIPS_TIGER:
	हाल SAA7134_BOARD_PHILIPS_TIGER_S:
	अणु
		u8 data[] = अणु 0x3c, 0x33, 0x60पूर्ण;
		काष्ठा i2c_msg msg = अणु.addr=0x08, .flags=0, .buf=data, .len = माप(data)पूर्ण;
		अगर (dev->स्वतःdetected && (dev->eedata[0x49] == 0x50)) अणु
			dev->board = SAA7134_BOARD_PHILIPS_TIGER_S;
			pr_info("%s: Reconfigured board as %s\n",
				dev->name, saa7134_boards[dev->board].name);
		पूर्ण
		अगर (dev->board == SAA7134_BOARD_PHILIPS_TIGER_S) अणु
			dev->tuner_type = TUNER_PHILIPS_TDA8290;

			data[2] = 0x68;
			i2c_transfer(&dev->i2c_adap, &msg, 1);
			अवरोध;
		पूर्ण
		i2c_transfer(&dev->i2c_adap, &msg, 1);
		अवरोध;
	पूर्ण
	हाल SAA7134_BOARD_ASUSTeK_TVFM7135:
	/* The card below is detected as card=53, but is dअगरferent */
	       अगर (dev->स्वतःdetected && (dev->eedata[0x27] == 0x03)) अणु
			dev->board = SAA7134_BOARD_ASUSTeK_P7131_ANALOG;
			pr_info("%s: P7131 analog only, using entry of %s\n",
				dev->name, saa7134_boards[dev->board].name);

			/*
			 * IR init has alपढ़ोy happened क्रम other cards, so
			 * we have to catch up.
			 */
			dev->has_remote = SAA7134_REMOTE_GPIO;
			saa7134_input_init1(dev);
	       पूर्ण
	       अवरोध;
	हाल SAA7134_BOARD_HAUPPAUGE_HVR1150:
	हाल SAA7134_BOARD_HAUPPAUGE_HVR1120:
		hauppauge_eeprom(dev, dev->eedata+0x80);
		अवरोध;
	हाल SAA7134_BOARD_HAUPPAUGE_HVR1110:
		hauppauge_eeprom(dev, dev->eedata+0x80);
		fallthrough;
	हाल SAA7134_BOARD_PINNACLE_PCTV_310i:
	हाल SAA7134_BOARD_KWORLD_DVBT_210:
	हाल SAA7134_BOARD_TEVION_DVBT_220RF:
	हाल SAA7134_BOARD_ASUSTeK_TIGER:
	हाल SAA7134_BOARD_ASUSTeK_P7131_DUAL:
	हाल SAA7134_BOARD_ASUSTeK_P7131_HYBRID_LNA:
	हाल SAA7134_BOARD_MEDION_MD8800_QUADRO:
	हाल SAA7134_BOARD_AVERMEDIA_SUPER_007:
	हाल SAA7134_BOARD_TWINHAN_DTV_DVB_3056:
	हाल SAA7134_BOARD_CREATIX_CTX953:
	अणु
		/* this is a hybrid board, initialize to analog mode
		 * and configure firmware eeprom address
		 */
		u8 data[] = अणु 0x3c, 0x33, 0x60पूर्ण;
		काष्ठा i2c_msg msg = अणु.addr=0x08, .flags=0, .buf=data, .len = माप(data)पूर्ण;
		i2c_transfer(&dev->i2c_adap, &msg, 1);
		अवरोध;
	पूर्ण
	हाल SAA7134_BOARD_ASUSTeK_TIGER_3IN1:
	अणु
		u8 data[] = अणु 0x3c, 0x33, 0x60पूर्ण;
		काष्ठा i2c_msg msg = अणु.addr = 0x0b, .flags = 0, .buf = data,
							.len = माप(data)पूर्ण;
		i2c_transfer(&dev->i2c_adap, &msg, 1);
		अवरोध;
	पूर्ण
	हाल SAA7134_BOARD_ASUSTeK_PS3_100:
	अणु
		u8 data[] = अणु 0x3c, 0x33, 0x60पूर्ण;
		काष्ठा i2c_msg msg = अणु.addr = 0x0b, .flags = 0, .buf = data,
						       .len = माप(data)पूर्ण;
		i2c_transfer(&dev->i2c_adap, &msg, 1);
		अवरोध;
	पूर्ण
	हाल SAA7134_BOARD_FLYDVB_TRIO:
	अणु
		u8 temp = 0;
		पूर्णांक rc;
		u8 data[] = अणु 0x3c, 0x33, 0x62पूर्ण;
		काष्ठा i2c_msg msg = अणु.addr=0x09, .flags=0, .buf=data, .len = माप(data)पूर्ण;
		i2c_transfer(&dev->i2c_adap, &msg, 1);

		/*
		 * send weak up message to pic16C505 chip
		 * @ LअगरeView FlyDVB Trio
		 */
		msg.buf = &temp;
		msg.addr = 0x0b;
		msg.len = 1;
		अगर (1 != i2c_transfer(&dev->i2c_adap, &msg, 1)) अणु
			pr_warn("%s: send wake up byte to pic16C505(IR chip) failed\n",
				dev->name);
		पूर्ण अन्यथा अणु
			msg.flags = I2C_M_RD;
			rc = i2c_transfer(&dev->i2c_adap, &msg, 1);
			pr_info("%s: probe IR chip @ i2c 0x%02x: %s\n",
				   dev->name, msg.addr,
				   (1 == rc) ? "yes" : "no");
			अगर (rc == 1)
				dev->has_remote = SAA7134_REMOTE_I2C;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल SAA7134_BOARD_ADS_DUO_CARDBUS_PTV331:
	हाल SAA7134_BOARD_FLYDVBT_HYBRID_CARDBUS:
	अणु
		/* initialize analog mode  */
		u8 data[] = अणु 0x3c, 0x33, 0x6aपूर्ण;
		काष्ठा i2c_msg msg = अणु.addr=0x08, .flags=0, .buf=data, .len = माप(data)पूर्ण;
		i2c_transfer(&dev->i2c_adap, &msg, 1);
		अवरोध;
	पूर्ण
	हाल SAA7134_BOARD_CINERGY_HT_PCMCIA:
	हाल SAA7134_BOARD_CINERGY_HT_PCI:
	अणु
		/* initialize analog mode */
		u8 data[] = अणु 0x3c, 0x33, 0x68पूर्ण;
		काष्ठा i2c_msg msg = अणु.addr=0x08, .flags=0, .buf=data, .len = माप(data)पूर्ण;
		i2c_transfer(&dev->i2c_adap, &msg, 1);
		अवरोध;
	पूर्ण
	हाल SAA7134_BOARD_VIDEOMATE_DVBT_200:
	हाल SAA7134_BOARD_VIDEOMATE_DVBT_200A:
		/* The T200 and the T200A share the same pci id.  Consequently,
		 * we are going to query eeprom to try to find out which one we
		 * are actually looking at. */

		/* Don't करो this अगर the board was specअगरically selected with an
		 * insmod option or अगर we have the शेष configuration T200*/
		अगर (!dev->स्वतःdetected || (dev->eedata[0x41] == 0xd0))
			अवरोध;
		अगर (dev->eedata[0x41] == 0x02) अणु
			/* Reconfigure board  as T200A */
			dev->board = SAA7134_BOARD_VIDEOMATE_DVBT_200A;
			dev->tuner_type   = saa7134_boards[dev->board].tuner_type;
			dev->tda9887_conf = saa7134_boards[dev->board].tda9887_conf;
			pr_info("%s: Reconfigured board as %s\n",
				dev->name, saa7134_boards[dev->board].name);
		पूर्ण अन्यथा अणु
			pr_warn("%s: Unexpected tuner type info: %x in eeprom\n",
				dev->name, dev->eedata[0x41]);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SAA7134_BOARD_ADS_INSTANT_HDTV_PCI:
	हाल SAA7134_BOARD_KWORLD_ATSC110:
	अणु
		काष्ठा i2c_msg msg = अणु .addr = 0x0a, .flags = 0 पूर्ण;
		पूर्णांक i;
		अटल u8 buffer[][2] = अणु
			अणु 0x10, 0x12 पूर्ण,
			अणु 0x13, 0x04 पूर्ण,
			अणु 0x16, 0x00 पूर्ण,
			अणु 0x14, 0x04 पूर्ण,
			अणु 0x17, 0x00 पूर्ण,
		पूर्ण;

		क्रम (i = 0; i < ARRAY_SIZE(buffer); i++) अणु
			msg.buf = &buffer[i][0];
			msg.len = ARRAY_SIZE(buffer[0]);
			अगर (i2c_transfer(&dev->i2c_adap, &msg, 1) != 1)
				pr_warn("%s: Unable to enable tuner(%i).\n",
					dev->name, i);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल SAA7134_BOARD_BEHOLD_H6:
	अणु
		u8 data[] = अणु 0x09, 0x9f, 0x86, 0x11पूर्ण;
		काष्ठा i2c_msg msg = अणु.addr = 0x61, .flags = 0, .buf = data,
							.len = माप(data)पूर्ण;

		/* The tuner TUNER_PHILIPS_FMD1216MEX_MK3 after hardware    */
		/* start has disabled IF and enabled DVB-T. When saa7134    */
		/* scan I2C devices it not detect IF tda9887 and can`t      */
		/* watch TV without software reboot. For solve this problem */
		/* चयन the tuner to analog TV mode manually.             */
		अगर (i2c_transfer(&dev->i2c_adap, &msg, 1) != 1)
			pr_warn("%s: Unable to enable IF of the tuner.\n",
				dev->name);
		अवरोध;
	पूर्ण
	हाल SAA7134_BOARD_KWORLD_PCI_SBTVD_FULLSEG:
		saa_ग_लिखोl(SAA7134_GPIO_GPMODE0 >> 2, 0x4000);
		saa_ग_लिखोl(SAA7134_GPIO_GPSTATUS0 >> 2, 0x4000);

		saa7134_set_gpio(dev, 27, 0);
		अवरोध;
	पूर्ण /* चयन() */

	/* initialize tuner (करोn't करो this when resuming) */
	अगर (!dev->insuspend && TUNER_ABSENT != dev->tuner_type) अणु
		पूर्णांक has_demod = (dev->tda9887_conf & TDA9887_PRESENT);

		/* Note: radio tuner address is always filled in,
		   so we करो not need to probe क्रम a radio tuner device. */
		अगर (dev->radio_type != UNSET)
			v4l2_i2c_new_subdev(&dev->v4l2_dev,
				&dev->i2c_adap, "tuner",
				dev->radio_addr, शून्य);
		अगर (has_demod)
			v4l2_i2c_new_subdev(&dev->v4l2_dev,
				&dev->i2c_adap, "tuner",
				0, v4l2_i2c_tuner_addrs(ADDRS_DEMOD));
		अगर (dev->tuner_addr == ADDR_UNSET) अणु
			क्रमागत v4l2_i2c_tuner_type type =
				has_demod ? ADDRS_TV_WITH_DEMOD : ADDRS_TV;

			v4l2_i2c_new_subdev(&dev->v4l2_dev,
				&dev->i2c_adap, "tuner",
				0, v4l2_i2c_tuner_addrs(type));
		पूर्ण अन्यथा अणु
			v4l2_i2c_new_subdev(&dev->v4l2_dev,
				&dev->i2c_adap, "tuner",
				dev->tuner_addr, शून्य);
		पूर्ण
	पूर्ण

	saa7134_tuner_setup(dev);

	चयन (dev->board) अणु
	हाल SAA7134_BOARD_BEHOLD_COLUMBUS_TVFM:
	हाल SAA7134_BOARD_AVERMEDIA_CARDBUS_501:
	अणु
		काष्ठा v4l2_priv_tun_config tea5767_cfg;
		काष्ठा tea5767_ctrl ctl;

		dev->i2c_client.addr = 0xC0;
		/* set TEA5767(analog FM) defines */
		स_रखो(&ctl, 0, माप(ctl));
		ctl.xtal_freq = TEA5767_HIGH_LO_13MHz;
		tea5767_cfg.tuner = TUNER_TEA5767;
		tea5767_cfg.priv  = &ctl;
		saa_call_all(dev, tuner, s_config, &tea5767_cfg);
		अवरोध;
	पूर्ण
	पूर्ण /* चयन() */

	वापस 0;
पूर्ण
