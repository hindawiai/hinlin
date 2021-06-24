<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1+ WITH Linux-syscall-note */
/*
 * audपन.स - DEPRECATED MPEG-TS audio decoder API
 *
 * NOTE: should not be used on future drivers
 *
 * Copyright (C) 2000 Ralph  Metzler <ralph@convergence.de>
 *                  & Marcus Metzler <marcus@convergence.de>
 *                    क्रम convergence पूर्णांकegrated media GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Lesser Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#अगर_अघोषित _DVBAUDIO_H_
#घोषणा _DVBAUDIO_H_

#समावेश <linux/types.h>

प्रकार क्रमागत अणु
	AUDIO_SOURCE_DEMUX, /* Select the demux as the मुख्य source */
	AUDIO_SOURCE_MEMORY /* Select पूर्णांकernal memory as the मुख्य source */
पूर्ण audio_stream_source_t;


प्रकार क्रमागत अणु
	AUDIO_STOPPED,      /* Device is stopped */
	AUDIO_PLAYING,      /* Device is currently playing */
	AUDIO_PAUSED        /* Device is छोड़ोd */
पूर्ण audio_play_state_t;


प्रकार क्रमागत अणु
	AUDIO_STEREO,
	AUDIO_MONO_LEFT,
	AUDIO_MONO_RIGHT,
	AUDIO_MONO,
	AUDIO_STEREO_SWAPPED
पूर्ण audio_channel_select_t;


प्रकार काष्ठा audio_mixer अणु
	अचिन्हित पूर्णांक volume_left;
	अचिन्हित पूर्णांक volume_right;
  /* what अन्यथा करो we need? bass, pass-through, ... */
पूर्ण audio_mixer_t;


प्रकार काष्ठा audio_status अणु
	पूर्णांक                    AV_sync_state;  /* sync audio and video? */
	पूर्णांक                    mute_state;     /* audio is muted */
	audio_play_state_t     play_state;     /* current playback state */
	audio_stream_source_t  stream_source;  /* current stream source */
	audio_channel_select_t channel_select; /* currently selected channel */
	पूर्णांक                    bypass_mode;    /* pass on audio data to */
	audio_mixer_t	       mixer_state;    /* current mixer state */
पूर्ण audio_status_t;                              /* separate decoder hardware */


/* क्रम GET_CAPABILITIES and SET_FORMAT, the latter should only set one bit */
#घोषणा AUDIO_CAP_DTS    1
#घोषणा AUDIO_CAP_LPCM   2
#घोषणा AUDIO_CAP_MP1    4
#घोषणा AUDIO_CAP_MP2    8
#घोषणा AUDIO_CAP_MP3   16
#घोषणा AUDIO_CAP_AAC   32
#घोषणा AUDIO_CAP_OGG   64
#घोषणा AUDIO_CAP_SDDS 128
#घोषणा AUDIO_CAP_AC3  256

#घोषणा AUDIO_STOP                 _IO('o', 1)
#घोषणा AUDIO_PLAY                 _IO('o', 2)
#घोषणा AUDIO_PAUSE                _IO('o', 3)
#घोषणा AUDIO_CONTINUE             _IO('o', 4)
#घोषणा AUDIO_SELECT_SOURCE        _IO('o', 5)
#घोषणा AUDIO_SET_MUTE             _IO('o', 6)
#घोषणा AUDIO_SET_AV_SYNC          _IO('o', 7)
#घोषणा AUDIO_SET_BYPASS_MODE      _IO('o', 8)
#घोषणा AUDIO_CHANNEL_SELECT       _IO('o', 9)
#घोषणा AUDIO_GET_STATUS           _IOR('o', 10, audio_status_t)

#घोषणा AUDIO_GET_CAPABILITIES     _IOR('o', 11, अचिन्हित पूर्णांक)
#घोषणा AUDIO_CLEAR_BUFFER         _IO('o',  12)
#घोषणा AUDIO_SET_ID               _IO('o', 13)
#घोषणा AUDIO_SET_MIXER            _IOW('o', 14, audio_mixer_t)
#घोषणा AUDIO_SET_STREAMTYPE       _IO('o', 15)
#घोषणा AUDIO_BILINGUAL_CHANNEL_SELECT _IO('o', 20)

#पूर्ण_अगर /* _DVBAUDIO_H_ */
