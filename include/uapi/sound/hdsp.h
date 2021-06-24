<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
#अगर_अघोषित __SOUND_HDSP_H
#घोषणा __SOUND_HDSP_H

/*
 *   Copyright (C) 2003 Thomas Charbonnel (thomas@undata.org)
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

#घोषणा HDSP_MATRIX_MIXER_SIZE 2048

क्रमागत HDSP_IO_Type अणु
	Digअगरace,
	Multअगरace,
	H9652,
	H9632,
	RPM,
	Undefined,
पूर्ण;

काष्ठा hdsp_peak_rms अणु
	__u32 input_peaks[26];
	__u32 playback_peaks[26];
	__u32 output_peaks[28];
	__u64 input_rms[26];
	__u64 playback_rms[26];
	/* These are only used क्रम H96xx cards */
	__u64 output_rms[26];
पूर्ण;

#घोषणा SNDRV_HDSP_IOCTL_GET_PEAK_RMS _IOR('H', 0x40, काष्ठा hdsp_peak_rms)

काष्ठा hdsp_config_info अणु
	अचिन्हित अक्षर pref_sync_ref;
	अचिन्हित अक्षर wordघड़ी_sync_check;
	अचिन्हित अक्षर spdअगर_sync_check;
	अचिन्हित अक्षर adatsync_sync_check;
	अचिन्हित अक्षर adat_sync_check[3];
	अचिन्हित अक्षर spdअगर_in;
	अचिन्हित अक्षर spdअगर_out;
	अचिन्हित अक्षर spdअगर_professional;
	अचिन्हित अक्षर spdअगर_emphasis;
	अचिन्हित अक्षर spdअगर_nonaudio;
	अचिन्हित पूर्णांक spdअगर_sample_rate;
	अचिन्हित पूर्णांक प्रणाली_sample_rate;
	अचिन्हित पूर्णांक स्वतःsync_sample_rate;
	अचिन्हित अक्षर प्रणाली_घड़ी_mode;
	अचिन्हित अक्षर घड़ी_source;
	अचिन्हित अक्षर स्वतःsync_ref;
	अचिन्हित अक्षर line_out;
	अचिन्हित अक्षर passthru; 
	अचिन्हित अक्षर da_gain;
	अचिन्हित अक्षर ad_gain;
	अचिन्हित अक्षर phone_gain;
	अचिन्हित अक्षर xlr_अवरोधout_cable;
	अचिन्हित अक्षर analog_extension_board;
पूर्ण;

#घोषणा SNDRV_HDSP_IOCTL_GET_CONFIG_INFO _IOR('H', 0x41, काष्ठा hdsp_config_info)

काष्ठा hdsp_firmware अणु
	व्योम *firmware_data;	/* 24413 x 4 bytes */
पूर्ण;

#घोषणा SNDRV_HDSP_IOCTL_UPLOAD_FIRMWARE _IOW('H', 0x42, काष्ठा hdsp_firmware)

काष्ठा hdsp_version अणु
	क्रमागत HDSP_IO_Type io_type;
	अचिन्हित लघु firmware_rev;
पूर्ण;

#घोषणा SNDRV_HDSP_IOCTL_GET_VERSION _IOR('H', 0x43, काष्ठा hdsp_version)

काष्ठा hdsp_mixer अणु
	अचिन्हित लघु matrix[HDSP_MATRIX_MIXER_SIZE];
पूर्ण;

#घोषणा SNDRV_HDSP_IOCTL_GET_MIXER _IOR('H', 0x44, काष्ठा hdsp_mixer)

काष्ठा hdsp_9632_aeb अणु
	पूर्णांक aebi;
	पूर्णांक aebo;
पूर्ण;

#घोषणा SNDRV_HDSP_IOCTL_GET_9632_AEB _IOR('H', 0x45, काष्ठा hdsp_9632_aeb)

#पूर्ण_अगर /* __SOUND_HDSP_H */
