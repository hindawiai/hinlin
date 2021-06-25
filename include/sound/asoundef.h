<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_ASOUNDEF_H
#घोषणा __SOUND_ASOUNDEF_H

/*
 *  Advanced Linux Sound Architecture - ALSA - Driver
 *  Copyright (c) 1994-2000 by Jaroslav Kysela <perex@perex.cz>
 */

/****************************************************************************
 *                                                                          *
 *        Digital audio पूर्णांकerface					    *
 *                                                                          *
 ****************************************************************************/

/* AES/IEC958 channel status bits */
#घोषणा IEC958_AES0_PROFESSIONAL	(1<<0)	/* 0 = consumer, 1 = professional */
#घोषणा IEC958_AES0_NONAUDIO		(1<<1)	/* 0 = audio, 1 = non-audio */
#घोषणा IEC958_AES0_PRO_EMPHASIS	(7<<2)	/* mask - emphasis */
#घोषणा IEC958_AES0_PRO_EMPHASIS_NOTID	(0<<2)	/* emphasis not indicated */
#घोषणा IEC958_AES0_PRO_EMPHASIS_NONE	(1<<2)	/* none emphasis */
#घोषणा IEC958_AES0_PRO_EMPHASIS_5015	(3<<2)	/* 50/15us emphasis */
#घोषणा IEC958_AES0_PRO_EMPHASIS_CCITT	(7<<2)	/* CCITT J.17 emphasis */
#घोषणा IEC958_AES0_PRO_FREQ_UNLOCKED	(1<<5)	/* source sample frequency: 0 = locked, 1 = unlocked */
#घोषणा IEC958_AES0_PRO_FS		(3<<6)	/* mask - sample frequency */
#घोषणा IEC958_AES0_PRO_FS_NOTID	(0<<6)	/* fs not indicated */
#घोषणा IEC958_AES0_PRO_FS_44100	(1<<6)	/* 44.1kHz */
#घोषणा IEC958_AES0_PRO_FS_48000	(2<<6)	/* 48kHz */
#घोषणा IEC958_AES0_PRO_FS_32000	(3<<6)	/* 32kHz */
#घोषणा IEC958_AES0_CON_NOT_COPYRIGHT	(1<<2)	/* 0 = copyright, 1 = not copyright */
#घोषणा IEC958_AES0_CON_EMPHASIS	(7<<3)	/* mask - emphasis */
#घोषणा IEC958_AES0_CON_EMPHASIS_NONE	(0<<3)	/* none emphasis */
#घोषणा IEC958_AES0_CON_EMPHASIS_5015	(1<<3)	/* 50/15us emphasis */
#घोषणा IEC958_AES0_CON_MODE		(3<<6)	/* mask - mode */
#घोषणा IEC958_AES1_PRO_MODE		(15<<0)	/* mask - channel mode */
#घोषणा IEC958_AES1_PRO_MODE_NOTID	(0<<0)	/* not indicated */
#घोषणा IEC958_AES1_PRO_MODE_STEREOPHONIC (2<<0) /* stereophonic - ch A is left */
#घोषणा IEC958_AES1_PRO_MODE_SINGLE	(4<<0)	/* single channel */
#घोषणा IEC958_AES1_PRO_MODE_TWO	(8<<0)	/* two channels */
#घोषणा IEC958_AES1_PRO_MODE_PRIMARY	(12<<0)	/* primary/secondary */
#घोषणा IEC958_AES1_PRO_MODE_BYTE3	(15<<0)	/* vector to byte 3 */
#घोषणा IEC958_AES1_PRO_USERBITS	(15<<4)	/* mask - user bits */
#घोषणा IEC958_AES1_PRO_USERBITS_NOTID	(0<<4)	/* not indicated */
#घोषणा IEC958_AES1_PRO_USERBITS_192	(8<<4)	/* 192-bit काष्ठाure */
#घोषणा IEC958_AES1_PRO_USERBITS_UDEF	(12<<4)	/* user defined application */
#घोषणा IEC958_AES1_CON_CATEGORY	0x7f
#घोषणा IEC958_AES1_CON_GENERAL		0x00
#घोषणा IEC958_AES1_CON_LASEROPT_MASK	0x07
#घोषणा IEC958_AES1_CON_LASEROPT_ID	0x01
#घोषणा IEC958_AES1_CON_IEC908_CD	(IEC958_AES1_CON_LASEROPT_ID|0x00)
#घोषणा IEC958_AES1_CON_NON_IEC908_CD	(IEC958_AES1_CON_LASEROPT_ID|0x08)
#घोषणा IEC958_AES1_CON_MINI_DISC	(IEC958_AES1_CON_LASEROPT_ID|0x48)
#घोषणा IEC958_AES1_CON_DVD		(IEC958_AES1_CON_LASEROPT_ID|0x18)
#घोषणा IEC958_AES1_CON_LASTEROPT_OTHER	(IEC958_AES1_CON_LASEROPT_ID|0x78)
#घोषणा IEC958_AES1_CON_DIGDIGCONV_MASK 0x07
#घोषणा IEC958_AES1_CON_DIGDIGCONV_ID	0x02
#घोषणा IEC958_AES1_CON_PCM_CODER	(IEC958_AES1_CON_DIGDIGCONV_ID|0x00)
#घोषणा IEC958_AES1_CON_MIXER		(IEC958_AES1_CON_DIGDIGCONV_ID|0x10)
#घोषणा IEC958_AES1_CON_RATE_CONVERTER	(IEC958_AES1_CON_DIGDIGCONV_ID|0x18)
#घोषणा IEC958_AES1_CON_SAMPLER		(IEC958_AES1_CON_DIGDIGCONV_ID|0x20)
#घोषणा IEC958_AES1_CON_DSP		(IEC958_AES1_CON_DIGDIGCONV_ID|0x28)
#घोषणा IEC958_AES1_CON_DIGDIGCONV_OTHER (IEC958_AES1_CON_DIGDIGCONV_ID|0x78)
#घोषणा IEC958_AES1_CON_MAGNETIC_MASK	0x07
#घोषणा IEC958_AES1_CON_MAGNETIC_ID	0x03
#घोषणा IEC958_AES1_CON_DAT		(IEC958_AES1_CON_MAGNETIC_ID|0x00)
#घोषणा IEC958_AES1_CON_VCR		(IEC958_AES1_CON_MAGNETIC_ID|0x08)
#घोषणा IEC958_AES1_CON_DCC		(IEC958_AES1_CON_MAGNETIC_ID|0x40)
#घोषणा IEC958_AES1_CON_MAGNETIC_DISC	(IEC958_AES1_CON_MAGNETIC_ID|0x18)
#घोषणा IEC958_AES1_CON_MAGNETIC_OTHER	(IEC958_AES1_CON_MAGNETIC_ID|0x78)
#घोषणा IEC958_AES1_CON_BROADCAST1_MASK 0x07
#घोषणा IEC958_AES1_CON_BROADCAST1_ID	0x04
#घोषणा IEC958_AES1_CON_DAB_JAPAN	(IEC958_AES1_CON_BROADCAST1_ID|0x00)
#घोषणा IEC958_AES1_CON_DAB_EUROPE	(IEC958_AES1_CON_BROADCAST1_ID|0x08)
#घोषणा IEC958_AES1_CON_DAB_USA		(IEC958_AES1_CON_BROADCAST1_ID|0x60)
#घोषणा IEC958_AES1_CON_SOFTWARE	(IEC958_AES1_CON_BROADCAST1_ID|0x40)
#घोषणा IEC958_AES1_CON_IEC62105	(IEC958_AES1_CON_BROADCAST1_ID|0x20)
#घोषणा IEC958_AES1_CON_BROADCAST1_OTHER (IEC958_AES1_CON_BROADCAST1_ID|0x78)
#घोषणा IEC958_AES1_CON_BROADCAST2_MASK 0x0f
#घोषणा IEC958_AES1_CON_BROADCAST2_ID	0x0e
#घोषणा IEC958_AES1_CON_MUSICAL_MASK	0x07
#घोषणा IEC958_AES1_CON_MUSICAL_ID	0x05
#घोषणा IEC958_AES1_CON_SYNTHESIZER	(IEC958_AES1_CON_MUSICAL_ID|0x00)
#घोषणा IEC958_AES1_CON_MICROPHONE	(IEC958_AES1_CON_MUSICAL_ID|0x08)
#घोषणा IEC958_AES1_CON_MUSICAL_OTHER	(IEC958_AES1_CON_MUSICAL_ID|0x78)
#घोषणा IEC958_AES1_CON_ADC_MASK	0x1f
#घोषणा IEC958_AES1_CON_ADC_ID		0x06
#घोषणा IEC958_AES1_CON_ADC		(IEC958_AES1_CON_ADC_ID|0x00)
#घोषणा IEC958_AES1_CON_ADC_OTHER	(IEC958_AES1_CON_ADC_ID|0x60)
#घोषणा IEC958_AES1_CON_ADC_COPYRIGHT_MASK 0x1f
#घोषणा IEC958_AES1_CON_ADC_COPYRIGHT_ID 0x16
#घोषणा IEC958_AES1_CON_ADC_COPYRIGHT	(IEC958_AES1_CON_ADC_COPYRIGHT_ID|0x00)
#घोषणा IEC958_AES1_CON_ADC_COPYRIGHT_OTHER (IEC958_AES1_CON_ADC_COPYRIGHT_ID|0x60)
#घोषणा IEC958_AES1_CON_SOLIDMEM_MASK	0x0f
#घोषणा IEC958_AES1_CON_SOLIDMEM_ID	0x08
#घोषणा IEC958_AES1_CON_SOLIDMEM_DIGITAL_RECORDER_PLAYER (IEC958_AES1_CON_SOLIDMEM_ID|0x00)
#घोषणा IEC958_AES1_CON_SOLIDMEM_OTHER	(IEC958_AES1_CON_SOLIDMEM_ID|0x70)
#घोषणा IEC958_AES1_CON_EXPERIMENTAL	0x40
#घोषणा IEC958_AES1_CON_ORIGINAL	(1<<7)	/* this bits depends on the category code */
#घोषणा IEC958_AES2_PRO_SBITS		(7<<0)	/* mask - sample bits */
#घोषणा IEC958_AES2_PRO_SBITS_20	(2<<0)	/* 20-bit - coordination */
#घोषणा IEC958_AES2_PRO_SBITS_24	(4<<0)	/* 24-bit - मुख्य audio */
#घोषणा IEC958_AES2_PRO_SBITS_UDEF	(6<<0)	/* user defined application */
#घोषणा IEC958_AES2_PRO_WORDLEN		(7<<3)	/* mask - source word length */
#घोषणा IEC958_AES2_PRO_WORDLEN_NOTID	(0<<3)	/* not indicated */
#घोषणा IEC958_AES2_PRO_WORDLEN_22_18	(2<<3)	/* 22-bit or 18-bit */
#घोषणा IEC958_AES2_PRO_WORDLEN_23_19	(4<<3)	/* 23-bit or 19-bit */
#घोषणा IEC958_AES2_PRO_WORDLEN_24_20	(5<<3)	/* 24-bit or 20-bit */
#घोषणा IEC958_AES2_PRO_WORDLEN_20_16	(6<<3)	/* 20-bit or 16-bit */
#घोषणा IEC958_AES2_CON_SOURCE		(15<<0)	/* mask - source number */
#घोषणा IEC958_AES2_CON_SOURCE_UNSPEC	(0<<0)	/* unspecअगरied */
#घोषणा IEC958_AES2_CON_CHANNEL		(15<<4)	/* mask - channel number */
#घोषणा IEC958_AES2_CON_CHANNEL_UNSPEC	(0<<4)	/* unspecअगरied */
#घोषणा IEC958_AES3_CON_FS		(15<<0)	/* mask - sample frequency */
#घोषणा IEC958_AES3_CON_FS_44100	(0<<0)	/* 44.1kHz */
#घोषणा IEC958_AES3_CON_FS_NOTID	(1<<0)	/* non indicated */
#घोषणा IEC958_AES3_CON_FS_48000	(2<<0)	/* 48kHz */
#घोषणा IEC958_AES3_CON_FS_32000	(3<<0)	/* 32kHz */
#घोषणा IEC958_AES3_CON_FS_22050	(4<<0)	/* 22.05kHz */
#घोषणा IEC958_AES3_CON_FS_24000	(6<<0)	/* 24kHz */
#घोषणा IEC958_AES3_CON_FS_88200	(8<<0)	/* 88.2kHz */
#घोषणा IEC958_AES3_CON_FS_768000	(9<<0)	/* 768kHz */
#घोषणा IEC958_AES3_CON_FS_96000	(10<<0)	/* 96kHz */
#घोषणा IEC958_AES3_CON_FS_176400	(12<<0)	/* 176.4kHz */
#घोषणा IEC958_AES3_CON_FS_192000	(14<<0)	/* 192kHz */
#घोषणा IEC958_AES3_CON_CLOCK		(3<<4)	/* mask - घड़ी accuracy */
#घोषणा IEC958_AES3_CON_CLOCK_1000PPM	(0<<4)	/* 1000 ppm */
#घोषणा IEC958_AES3_CON_CLOCK_50PPM	(1<<4)	/* 50 ppm */
#घोषणा IEC958_AES3_CON_CLOCK_VARIABLE	(2<<4)	/* variable pitch */
#घोषणा IEC958_AES4_CON_MAX_WORDLEN_24	(1<<0)	/* 0 = 20-bit, 1 = 24-bit */
#घोषणा IEC958_AES4_CON_WORDLEN		(7<<1)	/* mask - sample word length */
#घोषणा IEC958_AES4_CON_WORDLEN_NOTID	(0<<1)	/* not indicated */
#घोषणा IEC958_AES4_CON_WORDLEN_20_16	(1<<1)	/* 20-bit or 16-bit */
#घोषणा IEC958_AES4_CON_WORDLEN_22_18	(2<<1)	/* 22-bit or 18-bit */
#घोषणा IEC958_AES4_CON_WORDLEN_23_19	(4<<1)	/* 23-bit or 19-bit */
#घोषणा IEC958_AES4_CON_WORDLEN_24_20	(5<<1)	/* 24-bit or 20-bit */
#घोषणा IEC958_AES4_CON_WORDLEN_21_17	(6<<1)	/* 21-bit or 17-bit */
#घोषणा IEC958_AES4_CON_ORIGFS		(15<<4)	/* mask - original sample frequency */
#घोषणा IEC958_AES4_CON_ORIGFS_NOTID	(0<<4)	/* not indicated */
#घोषणा IEC958_AES4_CON_ORIGFS_192000	(1<<4)	/* 192kHz */
#घोषणा IEC958_AES4_CON_ORIGFS_12000	(2<<4)	/* 12kHz */
#घोषणा IEC958_AES4_CON_ORIGFS_176400	(3<<4)	/* 176.4kHz */
#घोषणा IEC958_AES4_CON_ORIGFS_96000	(5<<4)	/* 96kHz */
#घोषणा IEC958_AES4_CON_ORIGFS_8000	(6<<4)	/* 8kHz */
#घोषणा IEC958_AES4_CON_ORIGFS_88200	(7<<4)	/* 88.2kHz */
#घोषणा IEC958_AES4_CON_ORIGFS_16000	(8<<4)	/* 16kHz */
#घोषणा IEC958_AES4_CON_ORIGFS_24000	(9<<4)	/* 24kHz */
#घोषणा IEC958_AES4_CON_ORIGFS_11025	(10<<4)	/* 11.025kHz */
#घोषणा IEC958_AES4_CON_ORIGFS_22050	(11<<4)	/* 22.05kHz */
#घोषणा IEC958_AES4_CON_ORIGFS_32000	(12<<4)	/* 32kHz */
#घोषणा IEC958_AES4_CON_ORIGFS_48000	(13<<4)	/* 48kHz */
#घोषणा IEC958_AES4_CON_ORIGFS_44100	(15<<4)	/* 44.1kHz */
#घोषणा IEC958_AES5_CON_CGMSA		(3<<0)	/* mask - CGMS-A */
#घोषणा IEC958_AES5_CON_CGMSA_COPYFREELY (0<<0)	/* copying is permitted without restriction */
#घोषणा IEC958_AES5_CON_CGMSA_COPYONCE	(1<<0)	/* one generation of copies may be made */
#घोषणा IEC958_AES5_CON_CGMSA_COPYNOMORE (2<<0)	/* condition not be used */
#घोषणा IEC958_AES5_CON_CGMSA_COPYNEVER	(3<<0)	/* no copying is permitted */

/****************************************************************************
 *                                                                          *
 *        CEA-861 Audio InfoFrame. Used in HDMI and DisplayPort		    *
 *                                                                          *
 ****************************************************************************/
#घोषणा CEA861_AUDIO_INFOFRAME_DB1CC		(7<<0) /* mask - channel count */
#घोषणा CEA861_AUDIO_INFOFRAME_DB1CT		(0xf<<4) /* mask - coding type */
#घोषणा CEA861_AUDIO_INFOFRAME_DB1CT_FROM_STREAM (0<<4) /* refer to stream */
#घोषणा CEA861_AUDIO_INFOFRAME_DB1CT_IEC60958	(1<<4) /* IEC-60958 L-PCM */
#घोषणा CEA861_AUDIO_INFOFRAME_DB1CT_AC3	(2<<4) /* AC-3 */
#घोषणा CEA861_AUDIO_INFOFRAME_DB1CT_MPEG1	(3<<4) /* MPEG1 Layers 1 & 2 */
#घोषणा CEA861_AUDIO_INFOFRAME_DB1CT_MP3	(4<<4) /* MPEG1 Layer 3 */
#घोषणा CEA861_AUDIO_INFOFRAME_DB1CT_MPEG2_MULTICH (5<<4) /* MPEG2 Multichannel */
#घोषणा CEA861_AUDIO_INFOFRAME_DB1CT_AAC	(6<<4) /* AAC */
#घोषणा CEA861_AUDIO_INFOFRAME_DB1CT_DTS	(7<<4) /* DTS */
#घोषणा CEA861_AUDIO_INFOFRAME_DB1CT_ATRAC	(8<<4) /* ATRAC */
#घोषणा CEA861_AUDIO_INFOFRAME_DB1CT_ONEBIT	(9<<4) /* One Bit Audio */
#घोषणा CEA861_AUDIO_INFOFRAME_DB1CT_DOLBY_DIG_PLUS (10<<4) /* Dolby Digital + */
#घोषणा CEA861_AUDIO_INFOFRAME_DB1CT_DTS_HD	(11<<4) /* DTS-HD */
#घोषणा CEA861_AUDIO_INFOFRAME_DB1CT_MAT	(12<<4) /* MAT (MLP) */
#घोषणा CEA861_AUDIO_INFOFRAME_DB1CT_DST	(13<<4) /* DST */
#घोषणा CEA861_AUDIO_INFOFRAME_DB1CT_WMA_PRO	(14<<4) /* WMA Pro */
#घोषणा CEA861_AUDIO_INFOFRAME_DB2SF		(7<<2) /* mask - sample frequency */
#घोषणा CEA861_AUDIO_INFOFRAME_DB2SF_FROM_STREAM (0<<2) /* refer to stream */
#घोषणा CEA861_AUDIO_INFOFRAME_DB2SF_32000	(1<<2) /* 32kHz */
#घोषणा CEA861_AUDIO_INFOFRAME_DB2SF_44100	(2<<2) /* 44.1kHz */
#घोषणा CEA861_AUDIO_INFOFRAME_DB2SF_48000	(3<<2) /* 48kHz */
#घोषणा CEA861_AUDIO_INFOFRAME_DB2SF_88200	(4<<2) /* 88.2kHz */
#घोषणा CEA861_AUDIO_INFOFRAME_DB2SF_96000	(5<<2) /* 96kHz */
#घोषणा CEA861_AUDIO_INFOFRAME_DB2SF_176400	(6<<2) /* 176.4kHz */
#घोषणा CEA861_AUDIO_INFOFRAME_DB2SF_192000	(7<<2) /* 192kHz */
#घोषणा CEA861_AUDIO_INFOFRAME_DB2SS		(3<<0) /* mask - sample size */
#घोषणा CEA861_AUDIO_INFOFRAME_DB2SS_FROM_STREAM (0<<0) /* refer to stream */
#घोषणा CEA861_AUDIO_INFOFRAME_DB2SS_16BIT	(1<<0) /* 16 bits */
#घोषणा CEA861_AUDIO_INFOFRAME_DB2SS_20BIT	(2<<0) /* 20 bits */
#घोषणा CEA861_AUDIO_INFOFRAME_DB2SS_24BIT	(3<<0) /* 24 bits */
#घोषणा CEA861_AUDIO_INFOFRAME_DB5_DM_INH	(1<<7) /* mask - inhibit करोwnmixing */
#घोषणा CEA861_AUDIO_INFOFRAME_DB5_DM_INH_PERMITTED (0<<7) /* stereo करोwnmix permitted */
#घोषणा CEA861_AUDIO_INFOFRAME_DB5_DM_INH_PROHIBITED (1<<7) /* stereo करोwnmis prohibited */
#घोषणा CEA861_AUDIO_INFOFRAME_DB5_LSV		(0xf<<3) /* mask - level-shअगरt values */

/*****************************************************************************
 *                                                                           *
 *                            MIDI v1.0 पूर्णांकerface                            *
 *                                                                           *
 *****************************************************************************/

#घोषणा MIDI_CHANNELS			16
#घोषणा MIDI_GM_DRUM_CHANNEL		(10-1)

/*
 *  MIDI commands
 */

#घोषणा MIDI_CMD_NOTE_OFF		0x80
#घोषणा MIDI_CMD_NOTE_ON		0x90
#घोषणा MIDI_CMD_NOTE_PRESSURE		0xa0
#घोषणा MIDI_CMD_CONTROL		0xb0
#घोषणा MIDI_CMD_PGM_CHANGE		0xc0
#घोषणा MIDI_CMD_CHANNEL_PRESSURE	0xd0
#घोषणा MIDI_CMD_BENDER			0xe0

#घोषणा MIDI_CMD_COMMON_SYSEX		0xf0
#घोषणा MIDI_CMD_COMMON_MTC_QUARTER	0xf1
#घोषणा MIDI_CMD_COMMON_SONG_POS	0xf2
#घोषणा MIDI_CMD_COMMON_SONG_SELECT	0xf3
#घोषणा MIDI_CMD_COMMON_TUNE_REQUEST	0xf6
#घोषणा MIDI_CMD_COMMON_SYSEX_END	0xf7
#घोषणा MIDI_CMD_COMMON_CLOCK		0xf8
#घोषणा MIDI_CMD_COMMON_START		0xfa
#घोषणा MIDI_CMD_COMMON_CONTINUE	0xfb
#घोषणा MIDI_CMD_COMMON_STOP		0xfc
#घोषणा MIDI_CMD_COMMON_SENSING		0xfe
#घोषणा MIDI_CMD_COMMON_RESET		0xff

/*
 *  MIDI controllers
 */

#घोषणा MIDI_CTL_MSB_BANK		0x00
#घोषणा MIDI_CTL_MSB_MODWHEEL         	0x01
#घोषणा MIDI_CTL_MSB_BREATH           	0x02
#घोषणा MIDI_CTL_MSB_FOOT             	0x04
#घोषणा MIDI_CTL_MSB_PORTAMENTO_TIME 	0x05
#घोषणा MIDI_CTL_MSB_DATA_ENTRY		0x06
#घोषणा MIDI_CTL_MSB_MAIN_VOLUME      	0x07
#घोषणा MIDI_CTL_MSB_BALANCE          	0x08
#घोषणा MIDI_CTL_MSB_PAN              	0x0a
#घोषणा MIDI_CTL_MSB_EXPRESSION       	0x0b
#घोषणा MIDI_CTL_MSB_EFFECT1		0x0c
#घोषणा MIDI_CTL_MSB_EFFECT2		0x0d
#घोषणा MIDI_CTL_MSB_GENERAL_PURPOSE1 	0x10
#घोषणा MIDI_CTL_MSB_GENERAL_PURPOSE2 	0x11
#घोषणा MIDI_CTL_MSB_GENERAL_PURPOSE3 	0x12
#घोषणा MIDI_CTL_MSB_GENERAL_PURPOSE4 	0x13
#घोषणा MIDI_CTL_LSB_BANK		0x20
#घोषणा MIDI_CTL_LSB_MODWHEEL        	0x21
#घोषणा MIDI_CTL_LSB_BREATH           	0x22
#घोषणा MIDI_CTL_LSB_FOOT             	0x24
#घोषणा MIDI_CTL_LSB_PORTAMENTO_TIME 	0x25
#घोषणा MIDI_CTL_LSB_DATA_ENTRY		0x26
#घोषणा MIDI_CTL_LSB_MAIN_VOLUME      	0x27
#घोषणा MIDI_CTL_LSB_BALANCE          	0x28
#घोषणा MIDI_CTL_LSB_PAN              	0x2a
#घोषणा MIDI_CTL_LSB_EXPRESSION       	0x2b
#घोषणा MIDI_CTL_LSB_EFFECT1		0x2c
#घोषणा MIDI_CTL_LSB_EFFECT2		0x2d
#घोषणा MIDI_CTL_LSB_GENERAL_PURPOSE1 	0x30
#घोषणा MIDI_CTL_LSB_GENERAL_PURPOSE2 	0x31
#घोषणा MIDI_CTL_LSB_GENERAL_PURPOSE3 	0x32
#घोषणा MIDI_CTL_LSB_GENERAL_PURPOSE4 	0x33
#घोषणा MIDI_CTL_SUSTAIN              	0x40
#घोषणा MIDI_CTL_PORTAMENTO           	0x41
#घोषणा MIDI_CTL_SOSTENUTO            	0x42
#घोषणा MIDI_CTL_SOFT_PEDAL           	0x43
#घोषणा MIDI_CTL_LEGATO_FOOTSWITCH	0x44
#घोषणा MIDI_CTL_HOLD2                	0x45
#घोषणा MIDI_CTL_SC1_SOUND_VARIATION	0x46
#घोषणा MIDI_CTL_SC2_TIMBRE		0x47
#घोषणा MIDI_CTL_SC3_RELEASE_TIME	0x48
#घोषणा MIDI_CTL_SC4_ATTACK_TIME	0x49
#घोषणा MIDI_CTL_SC5_BRIGHTNESS		0x4a
#घोषणा MIDI_CTL_SC6			0x4b
#घोषणा MIDI_CTL_SC7			0x4c
#घोषणा MIDI_CTL_SC8			0x4d
#घोषणा MIDI_CTL_SC9			0x4e
#घोषणा MIDI_CTL_SC10			0x4f
#घोषणा MIDI_CTL_GENERAL_PURPOSE5     	0x50
#घोषणा MIDI_CTL_GENERAL_PURPOSE6     	0x51
#घोषणा MIDI_CTL_GENERAL_PURPOSE7     	0x52
#घोषणा MIDI_CTL_GENERAL_PURPOSE8     	0x53
#घोषणा MIDI_CTL_PORTAMENTO_CONTROL	0x54
#घोषणा MIDI_CTL_E1_REVERB_DEPTH	0x5b
#घोषणा MIDI_CTL_E2_TREMOLO_DEPTH	0x5c
#घोषणा MIDI_CTL_E3_CHORUS_DEPTH	0x5d
#घोषणा MIDI_CTL_E4_DETUNE_DEPTH	0x5e
#घोषणा MIDI_CTL_E5_PHASER_DEPTH	0x5f
#घोषणा MIDI_CTL_DATA_INCREMENT       	0x60
#घोषणा MIDI_CTL_DATA_DECREMENT       	0x61
#घोषणा MIDI_CTL_NONREG_PARM_NUM_LSB  	0x62
#घोषणा MIDI_CTL_NONREG_PARM_NUM_MSB  	0x63
#घोषणा MIDI_CTL_REGIST_PARM_NUM_LSB  	0x64
#घोषणा MIDI_CTL_REGIST_PARM_NUM_MSB	0x65
#घोषणा MIDI_CTL_ALL_SOUNDS_OFF		0x78
#घोषणा MIDI_CTL_RESET_CONTROLLERS	0x79
#घोषणा MIDI_CTL_LOCAL_CONTROL_SWITCH	0x7a
#घोषणा MIDI_CTL_ALL_NOTES_OFF		0x7b
#घोषणा MIDI_CTL_OMNI_OFF		0x7c
#घोषणा MIDI_CTL_OMNI_ON		0x7d
#घोषणा MIDI_CTL_MONO1			0x7e
#घोषणा MIDI_CTL_MONO2			0x7f

#पूर्ण_अगर /* __SOUND_ASOUNDEF_H */
