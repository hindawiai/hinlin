<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Vidtv serves as a reference DVB driver and helps validate the existing APIs
 * in the media subप्रणाली. It can also aid developers working on userspace
 * applications.
 *
 * This file contains the logic to translate the ES data क्रम one access unit
 * from an encoder पूर्णांकo MPEG TS packets. It करोes so by first encapsulating it
 * with a PES header and then splitting it पूर्णांकo TS packets.
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 */

#अगर_अघोषित VIDTV_PES_H
#घोषणा VIDTV_PES_H

#समावेश <linux/types.h>

#समावेश "vidtv_common.h"

#घोषणा PES_MAX_LEN 65536 /* Set 'length' to 0 अगर greater. Only possible क्रम video. */
#घोषणा PES_START_CODE_PREFIX 0x001 /* 00 00 01 */

/* Used when sending PTS, but not DTS */
काष्ठा vidtv_pes_optional_pts अणु
	u8 pts1;
	__be16 pts2;
	__be16 pts3;
पूर्ण __packed;

/* Used when sending both PTS and DTS */
काष्ठा vidtv_pes_optional_pts_dts अणु
	u8 pts1;
	__be16 pts2;
	__be16 pts3;

	u8 dts1;
	__be16 dts2;
	__be16 dts3;
पूर्ण __packed;

/* PES optional flags */
काष्ठा vidtv_pes_optional अणु
	/*
	 * These flags show which components are actually
	 * present in the "optional fields" in the optional PES
	 * header and which are not
	 *
	 * u16 two:2;  //0x2
	 * u16 PES_scrambling_control:2;
	 * u16 PES_priority:1;
	 * u16 data_alignment_indicator:1; // unused
	 * u16 copyright:1;
	 * u16 original_or_copy:1;
	 * u16 PTS_DTS:2;
	 * u16 ESCR:1;
	 * u16 ES_rate:1;
	 * u16 DSM_trick_mode:1;
	 * u16 additional_copy_info:1;
	 * u16 PES_CRC:1;
	 * u16 PES_extension:1;
	 */
	__be16 bitfield;
	u8 length;
पूर्ण __packed;

/* The PES header */
काष्ठा vidtv_mpeg_pes अणु
	__be32 bitfield; /* packet_start_code_prefix:24, stream_id: 8 */
	/* after this field until the end of the PES data payload */
	__be16 length;
	काष्ठा vidtv_pes_optional optional[];
पूर्ण __packed;

/**
 * काष्ठा pes_header_ग_लिखो_args - Arguments to ग_लिखो a PES header.
 * @dest_buf: The buffer to ग_लिखो पूर्णांकo.
 * @dest_offset: where to start writing in the dest_buffer.
 * @dest_buf_sz: The size of the dest_buffer
 * @encoder_id: Encoder id (see vidtv_encoder.h)
 * @send_pts: Should we send PTS?
 * @pts: PTS value to send.
 * @send_dts: Should we send DTS?
 * @dts: DTS value to send.
 * @stream_id: The stream id to use. Ex: Audio streams (0xc0-0xdf), Video
 * streams (0xe0-0xef).
 * @n_pes_h_s_bytes: Padding bytes. Might be used by an encoder अगर needed, माला_लो
 * discarded by the decoder.
 * @access_unit_len: The size of _one_ access unit (with any headers it might need)
 */
काष्ठा pes_header_ग_लिखो_args अणु
	व्योम *dest_buf;
	u32 dest_offset;
	u32 dest_buf_sz;
	u32 encoder_id;

	bool send_pts;
	u64 pts;

	bool send_dts;
	u64 dts;

	u16 stream_id;
	/* might be used by an encoder अगर needed, माला_लो discarded by decoder */
	u32 n_pes_h_s_bytes;
	u32 access_unit_len;
पूर्ण;

/**
 * काष्ठा pes_ts_header_ग_लिखो_args - Arguments to ग_लिखो a TS header.
 * @dest_buf: The buffer to ग_लिखो पूर्णांकo.
 * @dest_offset: where to start writing in the dest_buffer.
 * @dest_buf_sz: The size of the dest_buffer
 * @pid: The PID to use क्रम the TS packets.
 * @continuity_counter: Incremented on every new TS packet.
 * @wrote_pes_header: Flag to indicate that the PES header was written
 * @n_stuffing_bytes: Padding bytes. Might be used by an encoder अगर needed, माला_लो
 * discarded by the decoder.
 * @pcr: counter driven by a 27Mhz घड़ी.
 */
काष्ठा pes_ts_header_ग_लिखो_args अणु
	व्योम *dest_buf;
	u32 dest_offset;
	u32 dest_buf_sz;
	u16 pid;
	u8 *continuity_counter;
	bool wrote_pes_header;
	u32 n_stuffing_bytes;
	u64 pcr;
पूर्ण;

/**
 * काष्ठा pes_ग_लिखो_args - Arguments क्रम the packetizer.
 * @dest_buf: The buffer to ग_लिखो पूर्णांकo.
 * @from: A poपूर्णांकer to the encoder buffer containing one access unit.
 * @access_unit_len: The size of _one_ access unit (with any headers it might need)
 * @dest_offset: where to start writing in the dest_buffer.
 * @dest_buf_sz: The size of the dest_buffer
 * @pid: The PID to use क्रम the TS packets.
 * @encoder_id: Encoder id (see vidtv_encoder.h)
 * @continuity_counter: Incremented on every new TS packet.
 * @stream_id: The stream id to use. Ex: Audio streams (0xc0-0xdf), Video
 * streams (0xe0-0xef).
 * @send_pts: Should we send PTS?
 * @pts: PTS value to send.
 * @send_dts: Should we send DTS?
 * @dts: DTS value to send.
 * @n_pes_h_s_bytes: Padding bytes. Might be used by an encoder अगर needed, माला_लो
 * discarded by the decoder.
 * @pcr: counter driven by a 27Mhz घड़ी.
 */
काष्ठा pes_ग_लिखो_args अणु
	व्योम *dest_buf;
	व्योम *from;
	u32 access_unit_len;

	u32 dest_offset;
	u32 dest_buf_sz;
	u16 pid;

	u32 encoder_id;

	u8 *continuity_counter;

	u16 stream_id;

	bool send_pts;
	u64 pts;

	bool send_dts;
	u64 dts;

	u32 n_pes_h_s_bytes;
	u64 pcr;
पूर्ण;

/**
 * vidtv_pes_ग_लिखो_पूर्णांकo - Write a PES packet as MPEG-TS packets पूर्णांकo a buffer.
 * @args: The args to use when writing
 *
 * This function translate the ES data क्रम one access unit
 * from an encoder पूर्णांकo MPEG TS packets. It करोes so by first encapsulating it
 * with a PES header and then splitting it पूर्णांकo TS packets.
 *
 * The data is then written पूर्णांकo the buffer poपूर्णांकed to by 'args.buf'
 *
 * Return: The number of bytes written पूर्णांकo the buffer. This is usually NOT
 * equal to the size of the access unit, since we need space क्रम PES headers, TS headers
 * and padding bytes, अगर any.
 */
u32 vidtv_pes_ग_लिखो_पूर्णांकo(काष्ठा pes_ग_लिखो_args *args);

#पूर्ण_अगर // VIDTV_PES_H
