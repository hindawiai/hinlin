<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
#अगर_अघोषित __SOUND_HDSPM_H
#घोषणा __SOUND_HDSPM_H
/*
 *   Copyright (C) 2003 Winfried Ritsch (IEM)
 *   based on hdsp.h from Thomas Charbonnel (thomas@undata.org)
 *
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
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#अगर_घोषित __linux__
#समावेश <linux/types.h>
#पूर्ण_अगर

/* Maximum channels is 64 even on 56Mode you have 64playbacks to matrix */
#घोषणा HDSPM_MAX_CHANNELS      64

क्रमागत hdspm_io_type अणु
	MADI,
	MADIface,
	AIO,
	AES32,
	RayDAT
पूर्ण;

क्रमागत hdspm_speed अणु
	ss,
	ds,
	qs
पूर्ण;

/* -------------------- IOCTL Peak/RMS Meters -------------------- */

काष्ठा hdspm_peak_rms अणु
	__u32 input_peaks[64];
	__u32 playback_peaks[64];
	__u32 output_peaks[64];

	__u64 input_rms[64];
	__u64 playback_rms[64];
	__u64 output_rms[64];

	__u8 speed; /* क्रमागत अणुss, ds, qsपूर्ण */
	पूर्णांक status2;
पूर्ण;

#घोषणा SNDRV_HDSPM_IOCTL_GET_PEAK_RMS \
	_IOR('H', 0x42, काष्ठा hdspm_peak_rms)

/* ------------ CONFIG block IOCTL ---------------------- */

काष्ठा hdspm_config अणु
	अचिन्हित अक्षर pref_sync_ref;
	अचिन्हित अक्षर wordघड़ी_sync_check;
	अचिन्हित अक्षर madi_sync_check;
	अचिन्हित पूर्णांक प्रणाली_sample_rate;
	अचिन्हित पूर्णांक स्वतःsync_sample_rate;
	अचिन्हित अक्षर प्रणाली_घड़ी_mode;
	अचिन्हित अक्षर घड़ी_source;
	अचिन्हित अक्षर स्वतःsync_ref;
	अचिन्हित अक्षर line_out;
	अचिन्हित पूर्णांक passthru;
	अचिन्हित पूर्णांक analog_out;
पूर्ण;

#घोषणा SNDRV_HDSPM_IOCTL_GET_CONFIG \
	_IOR('H', 0x41, काष्ठा hdspm_config)

/*
 * If there's a TCO (TimeCode Option) board installed,
 * there are further options and status data available.
 * The hdspm_ltc काष्ठाure contains the current SMPTE
 * समयcode and some status inक्रमmation and can be
 * obtained via SNDRV_HDSPM_IOCTL_GET_LTC or in the
 * hdspm_status काष्ठा.
 */

क्रमागत hdspm_ltc_क्रमmat अणु
	क्रमmat_invalid,
	fps_24,
	fps_25,
	fps_2997,
	fps_30
पूर्ण;

क्रमागत hdspm_ltc_frame अणु
	frame_invalid,
	drop_frame,
	full_frame
पूर्ण;

क्रमागत hdspm_ltc_input_क्रमmat अणु
	ntsc,
	pal,
	no_video
पूर्ण;

काष्ठा hdspm_ltc अणु
	अचिन्हित पूर्णांक ltc;

	क्रमागत hdspm_ltc_क्रमmat क्रमmat;
	क्रमागत hdspm_ltc_frame frame;
	क्रमागत hdspm_ltc_input_क्रमmat input_क्रमmat;
पूर्ण;

#घोषणा SNDRV_HDSPM_IOCTL_GET_LTC _IOR('H', 0x46, काष्ठा hdspm_ltc)

/*
 * The status data reflects the device's current state
 * as determined by the card's configuration and
 * connection status.
 */

क्रमागत hdspm_sync अणु
	hdspm_sync_no_lock = 0,
	hdspm_sync_lock = 1,
	hdspm_sync_sync = 2
पूर्ण;

क्रमागत hdspm_madi_input अणु
	hdspm_input_optical = 0,
	hdspm_input_coax = 1
पूर्ण;

क्रमागत hdspm_madi_channel_क्रमmat अणु
	hdspm_क्रमmat_ch_64 = 0,
	hdspm_क्रमmat_ch_56 = 1
पूर्ण;

क्रमागत hdspm_madi_frame_क्रमmat अणु
	hdspm_frame_48 = 0,
	hdspm_frame_96 = 1
पूर्ण;

क्रमागत hdspm_syncsource अणु
	syncsource_wc = 0,
	syncsource_madi = 1,
	syncsource_tco = 2,
	syncsource_sync = 3,
	syncsource_none = 4
पूर्ण;

काष्ठा hdspm_status अणु
	__u8 card_type; /* क्रमागत hdspm_io_type */
	क्रमागत hdspm_syncsource स्वतःsync_source;

	__u64 card_घड़ी;
	__u32 master_period;

	जोड़ अणु
		काष्ठा अणु
			__u8 sync_wc; /* क्रमागत hdspm_sync */
			__u8 sync_madi; /* क्रमागत hdspm_sync */
			__u8 sync_tco; /* क्रमागत hdspm_sync */
			__u8 sync_in; /* क्रमागत hdspm_sync */
			__u8 madi_input; /* क्रमागत hdspm_madi_input */
			__u8 channel_क्रमmat; /* क्रमागत hdspm_madi_channel_क्रमmat */
			__u8 frame_क्रमmat; /* क्रमागत hdspm_madi_frame_क्रमmat */
		पूर्ण madi;
	पूर्ण card_specअगरic;
पूर्ण;

#घोषणा SNDRV_HDSPM_IOCTL_GET_STATUS \
	_IOR('H', 0x47, काष्ठा hdspm_status)

/*
 * Get inक्रमmation about the card and its add-ons.
 */

#घोषणा HDSPM_ADDON_TCO 1

काष्ठा hdspm_version अणु
	__u8 card_type; /* क्रमागत hdspm_io_type */
	अक्षर cardname[20];
	अचिन्हित पूर्णांक serial;
	अचिन्हित लघु firmware_rev;
	पूर्णांक adकरोns;
पूर्ण;

#घोषणा SNDRV_HDSPM_IOCTL_GET_VERSION _IOR('H', 0x48, काष्ठा hdspm_version)

/* ------------- get Matrix Mixer IOCTL --------------- */

/* MADI mixer: 64inमाला_दो+64playback in 64outमाला_दो = 8192 => *4Byte =
 * 32768 Bytes
 */

/* organisation is 64 channelfader in a continuous memory block */
/* equivalent to hardware definition, maybe क्रम future feature of mmap of
 * them
 */
/* each of 64 outमाला_दो has 64 infader and 64 outfader:
   Ins to Outs mixer[out].in[in], Outstreams to Outs mixer[out].pb[pb] */

#घोषणा HDSPM_MIXER_CHANNELS HDSPM_MAX_CHANNELS

काष्ठा hdspm_channelfader अणु
	अचिन्हित पूर्णांक in[HDSPM_MIXER_CHANNELS];
	अचिन्हित पूर्णांक pb[HDSPM_MIXER_CHANNELS];
पूर्ण;

काष्ठा hdspm_mixer अणु
	काष्ठा hdspm_channelfader ch[HDSPM_MIXER_CHANNELS];
पूर्ण;

काष्ठा hdspm_mixer_ioctl अणु
	काष्ठा hdspm_mixer *mixer;
पूर्ण;

/* use indirect access due to the limit of ioctl bit size */
#घोषणा SNDRV_HDSPM_IOCTL_GET_MIXER _IOR('H', 0x44, काष्ठा hdspm_mixer_ioctl)

#पूर्ण_अगर
