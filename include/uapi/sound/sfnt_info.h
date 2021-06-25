<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
#अगर_अघोषित __SOUND_SFNT_INFO_H
#घोषणा __SOUND_SFNT_INFO_H

/*
 *  Patch record compatible with AWE driver on OSS
 *
 *  Copyright (C) 1999-2000 Takashi Iwai
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#समावेश <sound/asound.h>

/*
 * patch inक्रमmation record
 */

#अगर_घोषित SNDRV_BIG_ENDIAN
#घोषणा SNDRV_OSS_PATCHKEY(id) (0xfd00|id)
#अन्यथा
#घोषणा SNDRV_OSS_PATCHKEY(id) ((id<<8)|0xfd)
#पूर्ण_अगर

/* patch पूर्णांकerface header: 16 bytes */
काष्ठा soundfont_patch_info अणु
	अचिन्हित लघु key;		/* use the key below */
#घोषणा SNDRV_OSS_SOUNDFONT_PATCH		SNDRV_OSS_PATCHKEY(0x07)

	लघु device_no;		/* synthesizer number */
	अचिन्हित लघु sf_id;		/* file id (should be zero) */
	लघु optarg;			/* optional argument */
	पूर्णांक len;			/* data length (without this header) */

	लघु type;			/* patch operation type */
#घोषणा SNDRV_SFNT_LOAD_INFO		0	/* awe_voice_rec */
#घोषणा SNDRV_SFNT_LOAD_DATA		1	/* awe_sample_info */
#घोषणा SNDRV_SFNT_OPEN_PATCH	2	/* awe_खोलो_parm */
#घोषणा SNDRV_SFNT_CLOSE_PATCH	3	/* none */
	/* 4 is obsolete */
#घोषणा SNDRV_SFNT_REPLACE_DATA	5	/* awe_sample_info (optarg=#channels)*/
#घोषणा SNDRV_SFNT_MAP_PRESET	6	/* awe_voice_map */
	/* 7 is not used */
#घोषणा SNDRV_SFNT_PROBE_DATA		8	/* optarg=sample */
#घोषणा SNDRV_SFNT_REMOVE_INFO		9	/* optarg=(bank<<8)|instr */

	लघु reserved;			/* word alignment data */

	/* the actual patch data begins after this */
पूर्ण;


/*
 * खोलो patch
 */

#घोषणा SNDRV_SFNT_PATCH_NAME_LEN	32

काष्ठा soundfont_खोलो_parm अणु
	अचिन्हित लघु type;		/* sample type */
#घोषणा SNDRV_SFNT_PAT_TYPE_MISC	0
#घोषणा SNDRV_SFNT_PAT_TYPE_GUS	6
#घोषणा SNDRV_SFNT_PAT_TYPE_MAP	7
#घोषणा SNDRV_SFNT_PAT_LOCKED	0x100	/* lock the samples */
#घोषणा SNDRV_SFNT_PAT_SHARED	0x200	/* sample is shared */

	लघु reserved;
	अक्षर name[SNDRV_SFNT_PATCH_NAME_LEN];
पूर्ण;


/*
 * raw voice inक्रमmation record
 */

/* wave table envelope & effect parameters to control EMU8000 */
काष्ठा soundfont_voice_parm अणु
	अचिन्हित लघु moddelay;	/* modulation delay (0x8000) */
	अचिन्हित लघु modatkhld;	/* modulation attack & hold समय (0x7f7f) */
	अचिन्हित लघु moddcysus;	/* modulation decay & sustain (0x7f7f) */
	अचिन्हित लघु modrelease;	/* modulation release समय (0x807f) */
	लघु modkeyhold, modkeydecay;	/* envelope change per key (not used) */
	अचिन्हित लघु voldelay;	/* volume delay (0x8000) */
	अचिन्हित लघु volatkhld;	/* volume attack & hold समय (0x7f7f) */
	अचिन्हित लघु voldcysus;	/* volume decay & sustain (0x7f7f) */
	अचिन्हित लघु volrelease;	/* volume release समय (0x807f) */
	लघु volkeyhold, volkeydecay;	/* envelope change per key (not used) */
	अचिन्हित लघु lfo1delay;	/* LFO1 delay (0x8000) */
	अचिन्हित लघु lfo2delay;	/* LFO2 delay (0x8000) */
	अचिन्हित लघु pefe;		/* modulation pitch & cutoff (0x0000) */
	अचिन्हित लघु fmmod;		/* LFO1 pitch & cutoff (0x0000) */
	अचिन्हित लघु tremfrq;		/* LFO1 volume & freq (0x0000) */
	अचिन्हित लघु fm2frq2;		/* LFO2 pitch & freq (0x0000) */
	अचिन्हित अक्षर cutoff;		/* initial cutoff (0xff) */
	अचिन्हित अक्षर filterQ;		/* initial filter Q [0-15] (0x0) */
	अचिन्हित अक्षर chorus;		/* chorus send (0x00) */
	अचिन्हित अक्षर reverb;		/* reverb send (0x00) */
	अचिन्हित लघु reserved[4];	/* not used */
पूर्ण;


/* wave table parameters: 92 bytes */
काष्ठा soundfont_voice_info अणु
	अचिन्हित लघु sf_id;		/* file id (should be zero) */
	अचिन्हित लघु sample;		/* sample id */
	पूर्णांक start, end;			/* sample offset correction */
	पूर्णांक loopstart, loखोलोd;		/* loop offset correction */
	लघु rate_offset;		/* sample rate pitch offset */
	अचिन्हित लघु mode;		/* sample mode */
#घोषणा SNDRV_SFNT_MODE_ROMSOUND		0x8000
#घोषणा SNDRV_SFNT_MODE_STEREO		1
#घोषणा SNDRV_SFNT_MODE_LOOPING		2
#घोषणा SNDRV_SFNT_MODE_NORELEASE		4	/* obsolete */
#घोषणा SNDRV_SFNT_MODE_INIT_PARM		8

	लघु root;			/* midi root key */
	लघु tune;			/* pitch tuning (in cents) */
	अचिन्हित अक्षर low, high;	/* key note range */
	अचिन्हित अक्षर vellow, velhigh;	/* velocity range */
	चिन्हित अक्षर fixkey, fixvel;	/* fixed key, velocity */
	चिन्हित अक्षर pan, fixpan;	/* panning, fixed panning */
	लघु exclusiveClass;		/* exclusive class (0 = none) */
	अचिन्हित अक्षर amplitude;	/* sample volume (127 max) */
	अचिन्हित अक्षर attenuation;	/* attenuation (0.375dB) */
	लघु scaleTuning;		/* pitch scale tuning(%), normally 100 */
	काष्ठा soundfont_voice_parm parm;	/* voice envelope parameters */
	अचिन्हित लघु sample_mode;	/* sample mode_flag (set by driver) */
पूर्ण;


/* instrument info header: 4 bytes */
काष्ठा soundfont_voice_rec_hdr अणु
	अचिन्हित अक्षर bank;		/* midi bank number */
	अचिन्हित अक्षर instr;		/* midi preset number */
	अक्षर nvoices;			/* number of voices */
	अक्षर ग_लिखो_mode;		/* ग_लिखो mode; normally 0 */
#घोषणा SNDRV_SFNT_WR_APPEND		0	/* append anyway */
#घोषणा SNDRV_SFNT_WR_EXCLUSIVE		1	/* skip अगर alपढ़ोy exists */
#घोषणा SNDRV_SFNT_WR_REPLACE		2	/* replace अगर alपढ़ोy exists */
पूर्ण;


/*
 * sample wave inक्रमmation
 */

/* wave table sample header: 32 bytes */
काष्ठा soundfont_sample_info अणु
	अचिन्हित लघु sf_id;		/* file id (should be zero) */
	अचिन्हित लघु sample;		/* sample id */
	पूर्णांक start, end;			/* start & end offset */
	पूर्णांक loopstart, loखोलोd;		/* loop start & end offset */
	पूर्णांक size;			/* size (0 = ROM) */
	लघु dummy;			/* not used */
	अचिन्हित लघु mode_flags;	/* mode flags */
#घोषणा SNDRV_SFNT_SAMPLE_8BITS		1	/* wave data is 8bits */
#घोषणा SNDRV_SFNT_SAMPLE_UNSIGNED	2	/* wave data is अचिन्हित */
#घोषणा SNDRV_SFNT_SAMPLE_NO_BLANK	4	/* no blank loop is attached */
#घोषणा SNDRV_SFNT_SAMPLE_SINGLESHOT	8	/* single-shot w/o loop */
#घोषणा SNDRV_SFNT_SAMPLE_BIसूची_LOOP	16	/* bidirectional looping */
#घोषणा SNDRV_SFNT_SAMPLE_STEREO_LEFT	32	/* stereo left sound */
#घोषणा SNDRV_SFNT_SAMPLE_STEREO_RIGHT	64	/* stereo right sound */
#घोषणा SNDRV_SFNT_SAMPLE_REVERSE_LOOP	128	/* reverse looping */
	अचिन्हित पूर्णांक truesize;		/* used memory size (set by driver) */
पूर्ण;


/*
 * voice preset mapping (aliasing)
 */

काष्ठा soundfont_voice_map अणु
	पूर्णांक map_bank, map_instr, map_key;	/* key = -1 means all keys */
	पूर्णांक src_bank, src_instr, src_key;
पूर्ण;


/*
 * ioctls क्रम hwdep
 */

#घोषणा SNDRV_EMUX_HWDEP_NAME	"Emux WaveTable"

#घोषणा SNDRV_EMUX_VERSION	((1 << 16) | (0 << 8) | 0)	/* 1.0.0 */

काष्ठा snd_emux_misc_mode अणु
	पूर्णांक port;	/* -1 = all */
	पूर्णांक mode;
	पूर्णांक value;
	पूर्णांक value2;	/* reserved */
पूर्ण;

#घोषणा SNDRV_EMUX_IOCTL_VERSION	_IOR('H', 0x80, अचिन्हित पूर्णांक)
#घोषणा SNDRV_EMUX_IOCTL_LOAD_PATCH	_IOWR('H', 0x81, काष्ठा soundfont_patch_info)
#घोषणा SNDRV_EMUX_IOCTL_RESET_SAMPLES	_IO('H', 0x82)
#घोषणा SNDRV_EMUX_IOCTL_REMOVE_LAST_SAMPLES _IO('H', 0x83)
#घोषणा SNDRV_EMUX_IOCTL_MEM_AVAIL	_IOW('H', 0x84, पूर्णांक)
#घोषणा SNDRV_EMUX_IOCTL_MISC_MODE	_IOWR('H', 0x84, काष्ठा snd_emux_misc_mode)

#पूर्ण_अगर /* __SOUND_SFNT_INFO_H */
