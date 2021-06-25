<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * The Virtual DVB test driver serves as a reference DVB driver and helps
 * validate the existing APIs in the media subप्रणाली. It can also aid
 * developers working on userspace applications.
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 */

#अगर_अघोषित VIDTV_TS_H
#घोषणा VIDTV_TS_H

#समावेश <linux/types.h>

#घोषणा TS_SYNC_BYTE 0x47
#घोषणा TS_PACKET_LEN 188
#घोषणा TS_PAYLOAD_LEN 184
#घोषणा TS_शून्य_PACKET_PID 0x1fff
#घोषणा TS_CC_MAX_VAL 0x0f /* 4 bits */
#घोषणा TS_LAST_VALID_PID 8191
#घोषणा TS_FILL_BYTE 0xff /* the byte used in packet stuffing */

काष्ठा vidtv_mpeg_ts_adaption अणु
	u8 length;
	काष्ठा अणु
		u8 extension:1;
		u8 निजी_data:1;
		u8 splicing_poपूर्णांक:1;
		u8 OPCR:1;
		u8 PCR:1;
		u8 priority:1;
		u8 अक्रमom_access:1;
		u8 disजारीd:1;
	पूर्ण __packed;
	u8 data[];
पूर्ण __packed;

काष्ठा vidtv_mpeg_ts अणु
	u8 sync_byte;
	__be16 bitfield; /* tei: 1, payload_start:1 priority: 1, pid:13 */
	काष्ठा अणु
		u8 continuity_counter:4;
		u8 payload:1;
		u8 adaptation_field:1;
		u8 scrambling:2;
	पूर्ण __packed;
पूर्ण __packed;

/**
 * काष्ठा pcr_ग_लिखो_args - Arguments क्रम the pcr_ग_लिखो_पूर्णांकo function.
 * @dest_buf: The buffer to ग_लिखो पूर्णांकo.
 * @dest_offset: The byte offset पूर्णांकo the buffer.
 * @pid: The TS PID क्रम the PCR packets.
 * @buf_sz: The size of the buffer in bytes.
 * @continuity_counter: The TS continuity_counter.
 * @pcr: A sample from the प्रणाली घड़ी.
 */
काष्ठा pcr_ग_लिखो_args अणु
	व्योम *dest_buf;
	u32 dest_offset;
	u16 pid;
	u32 buf_sz;
	u8 *continuity_counter;
	u64 pcr;
पूर्ण;

/**
 * काष्ठा null_packet_ग_लिखो_args - Arguments क्रम the null_ग_लिखो_पूर्णांकo function
 * @dest_buf: The buffer to ग_लिखो पूर्णांकo.
 * @dest_offset: The byte offset पूर्णांकo the buffer.
 * @buf_sz: The size of the buffer in bytes.
 * @continuity_counter: The TS continuity_counter.
 */
काष्ठा null_packet_ग_लिखो_args अणु
	व्योम *dest_buf;
	u32 dest_offset;
	u32 buf_sz;
	u8 *continuity_counter;
पूर्ण;

/* Increment the continuity counter */
व्योम vidtv_ts_inc_cc(u8 *continuity_counter);

/**
 * vidtv_ts_null_ग_लिखो_पूर्णांकo - Write a TS null packet पूर्णांकo a buffer.
 * @args: the arguments to use when writing.
 *
 * This function will ग_लिखो a null packet पूर्णांकo a buffer. This is usually used to
 * pad TS streams.
 *
 * Return: The number of bytes written पूर्णांकo the buffer.
 */
u32 vidtv_ts_null_ग_लिखो_पूर्णांकo(काष्ठा null_packet_ग_लिखो_args args);

/**
 * vidtv_ts_pcr_ग_लिखो_पूर्णांकo - Write a PCR  packet पूर्णांकo a buffer.
 * @args: the arguments to use when writing.
 *
 * This function will ग_लिखो a PCR packet पूर्णांकo a buffer. This is used to
 * synchronize the घड़ीs between encoders and decoders.
 *
 * Return: The number of bytes written पूर्णांकo the buffer.
 */
u32 vidtv_ts_pcr_ग_लिखो_पूर्णांकo(काष्ठा pcr_ग_लिखो_args args);

#पूर्ण_अगर //VIDTV_TS_H
