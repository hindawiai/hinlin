<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Vidtv serves as a reference DVB driver and helps validate the existing APIs
 * in the media subप्रणाली. It can also aid developers working on userspace
 * applications.
 *
 * This file contains a generic encoder type that can provide data क्रम a stream
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 */

#अगर_अघोषित VIDTV_ENCODER_H
#घोषणा VIDTV_ENCODER_H

#समावेश <linux/types.h>

क्रमागत vidtv_encoder_id अणु
	/* add IDs here when implementing new encoders */
	S302M,
पूर्ण;

काष्ठा vidtv_access_unit अणु
	u32 num_samples;
	u64 pts;
	u64 dts;
	u32 nbytes;
	u32 offset;
	काष्ठा vidtv_access_unit *next;
पूर्ण;

/* Some musical notes, used by a tone generator. Values are in Hz */
क्रमागत musical_notes अणु
	NOTE_SILENT = 0,

	NOTE_C_2 = 65,
	NOTE_CS_2 = 69,
	NOTE_D_2 = 73,
	NOTE_DS_2 = 78,
	NOTE_E_2 = 82,
	NOTE_F_2 = 87,
	NOTE_FS_2 = 93,
	NOTE_G_2 = 98,
	NOTE_GS_2 = 104,
	NOTE_A_2 = 110,
	NOTE_AS_2 = 117,
	NOTE_B_2 = 123,
	NOTE_C_3 = 131,
	NOTE_CS_3 = 139,
	NOTE_D_3 = 147,
	NOTE_DS_3 = 156,
	NOTE_E_3 = 165,
	NOTE_F_3 = 175,
	NOTE_FS_3 = 185,
	NOTE_G_3 = 196,
	NOTE_GS_3 = 208,
	NOTE_A_3 = 220,
	NOTE_AS_3 = 233,
	NOTE_B_3 = 247,
	NOTE_C_4 = 262,
	NOTE_CS_4 = 277,
	NOTE_D_4 = 294,
	NOTE_DS_4 = 311,
	NOTE_E_4 = 330,
	NOTE_F_4 = 349,
	NOTE_FS_4 = 370,
	NOTE_G_4 = 392,
	NOTE_GS_4 = 415,
	NOTE_A_4 = 440,
	NOTE_AS_4 = 466,
	NOTE_B_4 = 494,
	NOTE_C_5 = 523,
	NOTE_CS_5 = 554,
	NOTE_D_5 = 587,
	NOTE_DS_5 = 622,
	NOTE_E_5 = 659,
	NOTE_F_5 = 698,
	NOTE_FS_5 = 740,
	NOTE_G_5 = 784,
	NOTE_GS_5 = 831,
	NOTE_A_5 = 880,
	NOTE_AS_5 = 932,
	NOTE_B_5 = 988,
	NOTE_C_6 = 1047,
	NOTE_CS_6 = 1109,
	NOTE_D_6 = 1175,
	NOTE_DS_6 = 1245,
	NOTE_E_6 = 1319,
	NOTE_F_6 = 1397,
	NOTE_FS_6 = 1480,
	NOTE_G_6 = 1568,
	NOTE_GS_6 = 1661,
	NOTE_A_6 = 1760,
	NOTE_AS_6 = 1865,
	NOTE_B_6 = 1976,
	NOTE_C_7 = 2093
पूर्ण;

/**
 * काष्ठा vidtv_encoder - A generic encoder type.
 * @id: So we can cast to a concrete implementation when needed.
 * @name: Usually the same as the stream name.
 * @encoder_buf: The encoder पूर्णांकernal buffer क्रम the access units.
 * @encoder_buf_sz: The encoder buffer size, in bytes
 * @encoder_buf_offset: Our byte position in the encoder buffer.
 * @sample_count: How many samples we have encoded in total.
 * @access_units: encoder payload units, used क्रम घड़ी references
 * @src_buf: The source of raw data to be encoded, encoder might set a
 * शेष अगर null.
 * @src_buf_sz: size of @src_buf.
 * @src_buf_offset: Our position in the source buffer.
 * @is_video_encoder: Whether this a video encoder (as opposed to audio)
 * @ctx: Encoder-specअगरic state.
 * @stream_id: Examples: Audio streams (0xc0-0xdf), Video streams
 * (0xe0-0xef).
 * @es_pid: The TS PID to use क्रम the elementary stream in this encoder.
 * @encode: Prepare enough AUs क्रम the given amount of समय.
 * @clear: Clear the encoder output.
 * @sync: Attempt to synchronize with this encoder.
 * @sampling_rate_hz: The sampling rate (or fps, अगर video) used.
 * @last_sample_cb: Called when the encoder runs out of data.This is
 *		    so the source can पढ़ो data in a
 *		    piecemeal fashion instead of having to
 *		    provide it all at once.
 * @destroy: Destroy this encoder, मुक्तing allocated resources.
 * @next: Next in the chain
 */
काष्ठा vidtv_encoder अणु
	क्रमागत vidtv_encoder_id id;
	अक्षर *name;

	u8 *encoder_buf;
	u32 encoder_buf_sz;
	u32 encoder_buf_offset;

	u64 sample_count;

	काष्ठा vidtv_access_unit *access_units;

	व्योम *src_buf;
	u32 src_buf_sz;
	u32 src_buf_offset;

	bool is_video_encoder;
	व्योम *ctx;

	__be16 stream_id;

	__be16 es_pid;

	व्योम *(*encode)(काष्ठा vidtv_encoder *e);

	u32 (*clear)(काष्ठा vidtv_encoder *e);

	काष्ठा vidtv_encoder *sync;

	u32 sampling_rate_hz;

	व्योम (*last_sample_cb)(u32 sample_no);

	व्योम (*destroy)(काष्ठा vidtv_encoder *e);

	काष्ठा vidtv_encoder *next;
पूर्ण;

#पूर्ण_अगर /* VIDTV_ENCODER_H */
