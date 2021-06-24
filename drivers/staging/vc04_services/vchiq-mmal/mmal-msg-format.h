<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Broadcom BM2835 V4L2 driver
 *
 * Copyright तऊ 2013 Raspberry Pi (Trading) Ltd.
 *
 * Authors: Vincent Sanders @ Collabora
 *          Dave Stevenson @ Broadcom
 *		(now dave.stevenson@raspberrypi.org)
 *          Simon Mellor @ Broadcom
 *          Luke Diamand @ Broadcom
 */

#अगर_अघोषित MMAL_MSG_FORMAT_H
#घोषणा MMAL_MSG_FORMAT_H

#समावेश "mmal-msg-common.h"

/* MMAL_ES_FORMAT_T */

काष्ठा mmal_audio_क्रमmat अणु
	u32 channels;		/* Number of audio channels */
	u32 sample_rate;	/* Sample rate */

	u32 bits_per_sample;	/* Bits per sample */
	u32 block_align;	/* Size of a block of data */
पूर्ण;

काष्ठा mmal_video_क्रमmat अणु
	u32 width;		/* Width of frame in pixels */
	u32 height;		/* Height of frame in rows of pixels */
	काष्ठा mmal_rect crop;	/* Visible region of the frame */
	काष्ठा mmal_rational frame_rate;	/* Frame rate */
	काष्ठा mmal_rational par;		/* Pixel aspect ratio */

	/*
	 * FourCC specअगरying the color space of the video stream. See the
	 * MmalColorSpace "pre-defined color spaces" क्रम some examples.
	 */
	u32 color_space;
पूर्ण;

काष्ठा mmal_subpicture_क्रमmat अणु
	u32 x_offset;
	u32 y_offset;
पूर्ण;

जोड़ mmal_es_specअगरic_क्रमmat अणु
	काष्ठा mmal_audio_क्रमmat audio;
	काष्ठा mmal_video_क्रमmat video;
	काष्ठा mmal_subpicture_क्रमmat subpicture;
पूर्ण;

/* Definition of an elementary stream क्रमmat (MMAL_ES_FORMAT_T) */
काष्ठा mmal_es_क्रमmat_local अणु
	u32 type;	/* क्रमागत mmal_es_type */

	u32 encoding;	/* FourCC specअगरying encoding of the elementary
			 * stream.
			 */
	u32 encoding_variant;	/* FourCC specअगरying the specअगरic
				 * encoding variant of the elementary
				 * stream.
				 */

	जोड़ mmal_es_specअगरic_क्रमmat *es;	/* Type specअगरic
						 * inक्रमmation क्रम the
						 * elementary stream
						 */

	u32 bitrate;	/* Bitrate in bits per second */
	u32 flags;	/* Flags describing properties of the elementary
			 * stream.
			 */

	u32 extradata_size;	/* Size of the codec specअगरic data */
	u8  *extradata;		/* Codec specअगरic data */
पूर्ण;

/* Remote definition of an elementary stream क्रमmat (MMAL_ES_FORMAT_T) */
काष्ठा mmal_es_क्रमmat अणु
	u32 type;	/* क्रमागत mmal_es_type */

	u32 encoding;	/* FourCC specअगरying encoding of the elementary
			 * stream.
			 */
	u32 encoding_variant;	/* FourCC specअगरying the specअगरic
				 * encoding variant of the elementary
				 * stream.
				 */

	u32 es;	/* Type specअगरic
		 * inक्रमmation क्रम the
		 * elementary stream
		 */

	u32 bitrate;	/* Bitrate in bits per second */
	u32 flags;	/* Flags describing properties of the elementary
			 * stream.
			 */

	u32 extradata_size;	/* Size of the codec specअगरic data */
	u32 extradata;		/* Codec specअगरic data */
पूर्ण;

#पूर्ण_अगर /* MMAL_MSG_FORMAT_H */
