<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  compress_offload.h - compress offload header definations
 *
 *  Copyright (C) 2011 Intel Corporation
 *  Authors:	Vinod Koul <vinod.koul@linux.पूर्णांकel.com>
 *		Pierre-Louis Bossart <pierre-louis.bossart@linux.पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 */
#अगर_अघोषित __COMPRESS_OFFLOAD_H
#घोषणा __COMPRESS_OFFLOAD_H

#समावेश <linux/types.h>
#समावेश <sound/asound.h>
#समावेश <sound/compress_params.h>


#घोषणा SNDRV_COMPRESS_VERSION SNDRV_PROTOCOL_VERSION(0, 2, 0)
/**
 * काष्ठा snd_compressed_buffer - compressed buffer
 * @fragment_size: size of buffer fragment in bytes
 * @fragments: number of such fragments
 */
काष्ठा snd_compressed_buffer अणु
	__u32 fragment_size;
	__u32 fragments;
पूर्ण __attribute__((packed, aligned(4)));

/**
 * काष्ठा snd_compr_params - compressed stream params
 * @buffer: buffer description
 * @codec: codec parameters
 * @no_wake_mode: करोnt wake on fragment elapsed
 */
काष्ठा snd_compr_params अणु
	काष्ठा snd_compressed_buffer buffer;
	काष्ठा snd_codec codec;
	__u8 no_wake_mode;
पूर्ण __attribute__((packed, aligned(4)));

/**
 * काष्ठा snd_compr_tstamp - बारtamp descriptor
 * @byte_offset: Byte offset in ring buffer to DSP
 * @copied_total: Total number of bytes copied from/to ring buffer to/by DSP
 * @pcm_frames: Frames decoded or encoded by DSP. This field will evolve by
 *	large steps and should only be used to monitor encoding/decoding
 *	progress. It shall not be used क्रम timing estimates.
 * @pcm_io_frames: Frames rendered or received by DSP पूर्णांकo a mixer or an audio
 * output/input. This field should be used क्रम A/V sync or समय estimates.
 * @sampling_rate: sampling rate of audio
 */
काष्ठा snd_compr_tstamp अणु
	__u32 byte_offset;
	__u32 copied_total;
	__u32 pcm_frames;
	__u32 pcm_io_frames;
	__u32 sampling_rate;
पूर्ण __attribute__((packed, aligned(4)));

/**
 * काष्ठा snd_compr_avail - avail descriptor
 * @avail: Number of bytes available in ring buffer क्रम writing/पढ़ोing
 * @tstamp: बारtamp inक्रमmation
 */
काष्ठा snd_compr_avail अणु
	__u64 avail;
	काष्ठा snd_compr_tstamp tstamp;
पूर्ण __attribute__((packed, aligned(4)));

क्रमागत snd_compr_direction अणु
	SND_COMPRESS_PLAYBACK = 0,
	SND_COMPRESS_CAPTURE
पूर्ण;

/**
 * काष्ठा snd_compr_caps - caps descriptor
 * @codecs: poपूर्णांकer to array of codecs
 * @direction: direction supported. Of type snd_compr_direction
 * @min_fragment_size: minimum fragment supported by DSP
 * @max_fragment_size: maximum fragment supported by DSP
 * @min_fragments: min fragments supported by DSP
 * @max_fragments: max fragments supported by DSP
 * @num_codecs: number of codecs supported
 * @reserved: reserved field
 */
काष्ठा snd_compr_caps अणु
	__u32 num_codecs;
	__u32 direction;
	__u32 min_fragment_size;
	__u32 max_fragment_size;
	__u32 min_fragments;
	__u32 max_fragments;
	__u32 codecs[MAX_NUM_CODECS];
	__u32 reserved[11];
पूर्ण __attribute__((packed, aligned(4)));

/**
 * काष्ठा snd_compr_codec_caps - query capability of codec
 * @codec: codec क्रम which capability is queried
 * @num_descriptors: number of codec descriptors
 * @descriptor: array of codec capability descriptor
 */
काष्ठा snd_compr_codec_caps अणु
	__u32 codec;
	__u32 num_descriptors;
	काष्ठा snd_codec_desc descriptor[MAX_NUM_CODEC_DESCRIPTORS];
पूर्ण __attribute__((packed, aligned(4)));

/**
 * क्रमागत sndrv_compress_encoder
 * @SNDRV_COMPRESS_ENCODER_PADDING: no of samples appended by the encoder at the
 * end of the track
 * @SNDRV_COMPRESS_ENCODER_DELAY: no of samples inserted by the encoder at the
 * beginning of the track
 */
क्रमागत sndrv_compress_encoder अणु
	SNDRV_COMPRESS_ENCODER_PADDING = 1,
	SNDRV_COMPRESS_ENCODER_DELAY = 2,
पूर्ण;

/**
 * काष्ठा snd_compr_metadata - compressed stream metadata
 * @key: key id
 * @value: key value
 */
काष्ठा snd_compr_metadata अणु
	 __u32 key;
	 __u32 value[8];
पूर्ण __attribute__((packed, aligned(4)));

/*
 * compress path ioctl definitions
 * SNDRV_COMPRESS_GET_CAPS: Query capability of DSP
 * SNDRV_COMPRESS_GET_CODEC_CAPS: Query capability of a codec
 * SNDRV_COMPRESS_SET_PARAMS: Set codec and stream parameters
 * Note: only codec params can be changed runसमय and stream params cant be
 * SNDRV_COMPRESS_GET_PARAMS: Query codec params
 * SNDRV_COMPRESS_TSTAMP: get the current बारtamp value
 * SNDRV_COMPRESS_AVAIL: get the current buffer avail value.
 * This also queries the tstamp properties
 * SNDRV_COMPRESS_PAUSE: Pause the running stream
 * SNDRV_COMPRESS_RESUME: resume a छोड़ोd stream
 * SNDRV_COMPRESS_START: Start a stream
 * SNDRV_COMPRESS_STOP: stop a running stream, discarding ring buffer content
 * and the buffers currently with DSP
 * SNDRV_COMPRESS_DRAIN: Play till end of buffers and stop after that
 * SNDRV_COMPRESS_IOCTL_VERSION: Query the API version
 */
#घोषणा SNDRV_COMPRESS_IOCTL_VERSION	_IOR('C', 0x00, पूर्णांक)
#घोषणा SNDRV_COMPRESS_GET_CAPS		_IOWR('C', 0x10, काष्ठा snd_compr_caps)
#घोषणा SNDRV_COMPRESS_GET_CODEC_CAPS	_IOWR('C', 0x11,\
						काष्ठा snd_compr_codec_caps)
#घोषणा SNDRV_COMPRESS_SET_PARAMS	_IOW('C', 0x12, काष्ठा snd_compr_params)
#घोषणा SNDRV_COMPRESS_GET_PARAMS	_IOR('C', 0x13, काष्ठा snd_codec)
#घोषणा SNDRV_COMPRESS_SET_METADATA	_IOW('C', 0x14,\
						 काष्ठा snd_compr_metadata)
#घोषणा SNDRV_COMPRESS_GET_METADATA	_IOWR('C', 0x15,\
						 काष्ठा snd_compr_metadata)
#घोषणा SNDRV_COMPRESS_TSTAMP		_IOR('C', 0x20, काष्ठा snd_compr_tstamp)
#घोषणा SNDRV_COMPRESS_AVAIL		_IOR('C', 0x21, काष्ठा snd_compr_avail)
#घोषणा SNDRV_COMPRESS_PAUSE		_IO('C', 0x30)
#घोषणा SNDRV_COMPRESS_RESUME		_IO('C', 0x31)
#घोषणा SNDRV_COMPRESS_START		_IO('C', 0x32)
#घोषणा SNDRV_COMPRESS_STOP		_IO('C', 0x33)
#घोषणा SNDRV_COMPRESS_DRAIN		_IO('C', 0x34)
#घोषणा SNDRV_COMPRESS_NEXT_TRACK	_IO('C', 0x35)
#घोषणा SNDRV_COMPRESS_PARTIAL_DRAIN	_IO('C', 0x36)
/*
 * TODO
 * 1. add mmap support
 *
 */
#घोषणा SND_COMPR_TRIGGER_DRAIN 7 /*FIXME move this to pcm.h */
#घोषणा SND_COMPR_TRIGGER_NEXT_TRACK 8
#घोषणा SND_COMPR_TRIGGER_PARTIAL_DRAIN 9
#पूर्ण_अगर
