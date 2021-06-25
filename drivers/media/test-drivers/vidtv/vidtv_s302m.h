<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Vidtv serves as a reference DVB driver and helps validate the existing APIs
 * in the media subप्रणाली. It can also aid developers working on userspace
 * applications.
 *
 * This file contains the code क्रम an AES3 (also known as AES/EBU) encoder.
 * It is based on EBU Tech 3250 and SMPTE 302M technical करोcuments.
 *
 * This encoder currently supports 16bit AES3 subframes using 16bit चिन्हित
 * पूर्णांकegers.
 *
 * Note: AU stands क्रम Access Unit, and AAU stands क्रम Audio Access Unit
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 */

#अगर_अघोषित VIDTV_S302M_H
#घोषणा VIDTV_S302M_H

#समावेश <linux/types.h>

#समावेश "vidtv_encoder.h"

/* see SMPTE 302M 2007 clause 7.3 */
#घोषणा VIDTV_S302M_BUF_SZ 65024

/* see ETSI TS 102 154 v.1.2.1 clause 7.3.5 */
#घोषणा VIDTV_S302M_FORMAT_IDENTIFIER 0x42535344

/**
 * काष्ठा vidtv_s302m_ctx - s302m encoder context.
 * @enc: A poपूर्णांकer to the containing encoder काष्ठाure.
 * @frame_index: The current frame in a block
 * @au_count: The total number of access units encoded up to now
 * @last_duration: Duration of the tone currently being played
 * @note_offset: Position at the music tone array
 * @last_tone: Tone currently being played
 */
काष्ठा vidtv_s302m_ctx अणु
	काष्ठा vidtv_encoder *enc;
	u32 frame_index;
	u32 au_count;
	पूर्णांक last_duration;
	अचिन्हित पूर्णांक note_offset;
	क्रमागत musical_notes last_tone;
पूर्ण;

/*
 * काष्ठा vidtv_smpte_s302m_es - s302m MPEG Elementary Stream header.
 *
 * See SMPTE 302M 2007 table 1.
 */
काष्ठा vidtv_smpte_s302m_es अणु
	/*
	 *
	 * audio_packet_size:16;
	 * num_channels:2;
	 * channel_identअगरication:8;
	 * bits_per_sample:2; // 0x0 क्रम 16bits
	 * zero:4;
	 */
	__be32 bitfield;
पूर्ण __packed;

काष्ठा vidtv_s302m_frame_16 अणु
	u8 data[5];
पूर्ण __packed;

/**
 * काष्ठा vidtv_s302m_encoder_init_args - Args क्रम the s302m encoder.
 *
 * @name: A name to identअगरy this particular instance
 * @src_buf: The source buffer, encoder will शेष to a sine wave अगर this is शून्य.
 * @src_buf_sz: The size of the source buffer.
 * @es_pid: The MPEG Elementary Stream PID to use.
 * @sync: Attempt to synchronize audio with this video encoder, अगर not शून्य.
 * @last_sample_cb: A callback called when the encoder runs out of data.
 * @head: Add to this chain
 */
काष्ठा vidtv_s302m_encoder_init_args अणु
	अक्षर *name;
	व्योम *src_buf;
	u32 src_buf_sz;
	u16 es_pid;
	काष्ठा vidtv_encoder *sync;
	व्योम (*last_sample_cb)(u32 sample_no);

	काष्ठा vidtv_encoder *head;
पूर्ण;

काष्ठा vidtv_encoder
*vidtv_s302m_encoder_init(काष्ठा vidtv_s302m_encoder_init_args args);

व्योम vidtv_s302m_encoder_destroy(काष्ठा vidtv_encoder *encoder);

#पूर्ण_अगर /* VIDTV_S302M_H */
