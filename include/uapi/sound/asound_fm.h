<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
#अगर_अघोषित __SOUND_ASOUND_FM_H
#घोषणा __SOUND_ASOUND_FM_H

/*
 *  Advanced Linux Sound Architecture - ALSA
 *
 *  Interface file between ALSA driver & user space
 *  Copyright (c) 1994-98 by Jaroslav Kysela <perex@perex.cz>,
 *                           4Front Technologies
 *
 *  Direct FM control
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

#घोषणा SNDRV_DM_FM_MODE_OPL2	0x00
#घोषणा SNDRV_DM_FM_MODE_OPL3	0x01

काष्ठा snd_dm_fm_info अणु
	अचिन्हित अक्षर fm_mode;		/* OPL mode, see SNDRV_DM_FM_MODE_XXX */
	अचिन्हित अक्षर rhythm;		/* percussion mode flag */
पूर्ण;

/*
 *  Data काष्ठाure composing an FM "note" or sound event.
 */

काष्ठा snd_dm_fm_voice अणु
	अचिन्हित अक्षर op;		/* चालक cell (0 or 1) */
	अचिन्हित अक्षर voice;		/* FM voice (0 to 17) */

	अचिन्हित अक्षर am;		/* amplitude modulation */
	अचिन्हित अक्षर vibrato;		/* vibrato effect */
	अचिन्हित अक्षर करो_sustain;	/* sustain phase */
	अचिन्हित अक्षर kbd_scale;	/* keyboard scaling */
	अचिन्हित अक्षर harmonic;		/* 4 bits: harmonic and multiplier */
	अचिन्हित अक्षर scale_level;	/* 2 bits: decrease output freq rises */
	अचिन्हित अक्षर volume;		/* 6 bits: volume */

	अचिन्हित अक्षर attack;		/* 4 bits: attack rate */
	अचिन्हित अक्षर decay;		/* 4 bits: decay rate */
	अचिन्हित अक्षर sustain;		/* 4 bits: sustain level */
	अचिन्हित अक्षर release;		/* 4 bits: release rate */

	अचिन्हित अक्षर feedback;		/* 3 bits: feedback क्रम op0 */
	अचिन्हित अक्षर connection;	/* 0 क्रम serial, 1 क्रम parallel */
	अचिन्हित अक्षर left;		/* stereo left */
	अचिन्हित अक्षर right;		/* stereo right */
	अचिन्हित अक्षर waveक्रमm;		/* 3 bits: waveक्रमm shape */
पूर्ण;

/*
 *  This describes an FM note by its voice, octave, frequency number (10bit)
 *  and key on/off.
 */

काष्ठा snd_dm_fm_note अणु
	अचिन्हित अक्षर voice;	/* 0-17 voice channel */
	अचिन्हित अक्षर octave;	/* 3 bits: what octave to play */
	अचिन्हित पूर्णांक fnum;	/* 10 bits: frequency number */
	अचिन्हित अक्षर key_on;	/* set क्रम active, clear क्रम silent */
पूर्ण;

/*
 *  FM parameters that apply globally to all voices, and thus are not "notes"
 */

काष्ठा snd_dm_fm_params अणु
	अचिन्हित अक्षर am_depth;		/* amplitude modulation depth (1=hi) */
	अचिन्हित अक्षर vib_depth;	/* vibrato depth (1=hi) */
	अचिन्हित अक्षर kbd_split;	/* keyboard split */
	अचिन्हित अक्षर rhythm;		/* percussion mode select */

	/* This block is the percussion instrument data */
	अचिन्हित अक्षर bass;
	अचिन्हित अक्षर snare;
	अचिन्हित अक्षर tomtom;
	अचिन्हित अक्षर cymbal;
	अचिन्हित अक्षर hihat;
पूर्ण;

/*
 *  FM mode ioctl settings
 */

#घोषणा SNDRV_DM_FM_IOCTL_INFO		_IOR('H', 0x20, काष्ठा snd_dm_fm_info)
#घोषणा SNDRV_DM_FM_IOCTL_RESET		_IO ('H', 0x21)
#घोषणा SNDRV_DM_FM_IOCTL_PLAY_NOTE	_IOW('H', 0x22, काष्ठा snd_dm_fm_note)
#घोषणा SNDRV_DM_FM_IOCTL_SET_VOICE	_IOW('H', 0x23, काष्ठा snd_dm_fm_voice)
#घोषणा SNDRV_DM_FM_IOCTL_SET_PARAMS	_IOW('H', 0x24, काष्ठा snd_dm_fm_params)
#घोषणा SNDRV_DM_FM_IOCTL_SET_MODE	_IOW('H', 0x25, पूर्णांक)
/* क्रम OPL3 only */
#घोषणा SNDRV_DM_FM_IOCTL_SET_CONNECTION	_IOW('H', 0x26, पूर्णांक)
/* SBI patch management */
#घोषणा SNDRV_DM_FM_IOCTL_CLEAR_PATCHES	_IO ('H', 0x40)

#घोषणा SNDRV_DM_FM_OSS_IOCTL_RESET		0x20
#घोषणा SNDRV_DM_FM_OSS_IOCTL_PLAY_NOTE		0x21
#घोषणा SNDRV_DM_FM_OSS_IOCTL_SET_VOICE		0x22
#घोषणा SNDRV_DM_FM_OSS_IOCTL_SET_PARAMS	0x23
#घोषणा SNDRV_DM_FM_OSS_IOCTL_SET_MODE		0x24
#घोषणा SNDRV_DM_FM_OSS_IOCTL_SET_OPL		0x25

/*
 * Patch Record - fixed size क्रम ग_लिखो
 */

#घोषणा FM_KEY_SBI	"SBI\032"
#घोषणा FM_KEY_2OP	"2OP\032"
#घोषणा FM_KEY_4OP	"4OP\032"

काष्ठा sbi_patch अणु
	अचिन्हित अक्षर prog;
	अचिन्हित अक्षर bank;
	अक्षर key[4];
	अक्षर name[25];
	अक्षर extension[7];
	अचिन्हित अक्षर data[32];
पूर्ण;

#पूर्ण_अगर /* __SOUND_ASOUND_FM_H */
