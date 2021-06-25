<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * The Virtual DVB test driver serves as a reference DVB driver and helps
 * validate the existing APIs in the media subप्रणाली. It can also aid
 * developers working on userspace applications.
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s, %d: " fmt, __func__, __LINE__

#समावेश <linux/math64.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/types.h>

#समावेश "vidtv_common.h"
#समावेश "vidtv_ts.h"

अटल u32 vidtv_ts_ग_लिखो_pcr_bits(u8 *to, u32 to_offset, u64 pcr)
अणु
	/* Exact same from ffmpeg. PCR is a counter driven by a 27Mhz घड़ी */
	u64 भाग;
	u64 rem;
	u8 *buf = to + to_offset;
	u64 pcr_low;
	u64 pcr_high;

	भाग = भाग64_u64_rem(pcr, 300, &rem);

	pcr_low = rem; /* pcr_low = pcr % 300 */
	pcr_high = भाग; /* pcr_high = pcr / 300 */

	*buf++ = pcr_high >> 25;
	*buf++ = pcr_high >> 17;
	*buf++ = pcr_high >>  9;
	*buf++ = pcr_high >>  1;
	*buf++ = pcr_high <<  7 | pcr_low >> 8 | 0x7e;
	*buf++ = pcr_low;

	वापस 6;
पूर्ण

व्योम vidtv_ts_inc_cc(u8 *continuity_counter)
अणु
	++*continuity_counter;
	अगर (*continuity_counter > TS_CC_MAX_VAL)
		*continuity_counter = 0;
पूर्ण

u32 vidtv_ts_null_ग_लिखो_पूर्णांकo(काष्ठा null_packet_ग_लिखो_args args)
अणु
	u32 nbytes = 0;
	काष्ठा vidtv_mpeg_ts ts_header = अणुपूर्ण;

	ts_header.sync_byte          = TS_SYNC_BYTE;
	ts_header.bitfield           = cpu_to_be16(TS_शून्य_PACKET_PID);
	ts_header.payload            = 1;
	ts_header.continuity_counter = *args.continuity_counter;

	/* copy TS header */
	nbytes += vidtv_स_नकल(args.dest_buf,
			       args.dest_offset + nbytes,
			       args.buf_sz,
			       &ts_header,
			       माप(ts_header));

	vidtv_ts_inc_cc(args.continuity_counter);

	/* fill the rest with empty data */
	nbytes += vidtv_स_रखो(args.dest_buf,
			       args.dest_offset + nbytes,
			       args.buf_sz,
			       TS_FILL_BYTE,
			       TS_PACKET_LEN - nbytes);

	/* we should have written exactly _one_ 188byte packet */
	अगर (nbytes != TS_PACKET_LEN)
		pr_warn_ratelimited("Expected exactly %d bytes, got %d\n",
				    TS_PACKET_LEN,
				    nbytes);

	वापस nbytes;
पूर्ण

u32 vidtv_ts_pcr_ग_लिखो_पूर्णांकo(काष्ठा pcr_ग_लिखो_args args)
अणु
	u32 nbytes = 0;
	काष्ठा vidtv_mpeg_ts ts_header = अणुपूर्ण;
	काष्ठा vidtv_mpeg_ts_adaption ts_adap = अणुपूर्ण;

	ts_header.sync_byte     = TS_SYNC_BYTE;
	ts_header.bitfield      = cpu_to_be16(args.pid);
	ts_header.scrambling    = 0;
	/* cc is not incremented, but it is needed. see 13818-1 clause 2.4.3.3 */
	ts_header.continuity_counter = *args.continuity_counter;
	ts_header.payload            = 0;
	ts_header.adaptation_field   = 1;

	/* 13818-1 clause 2.4.3.5 */
	ts_adap.length = 183;
	ts_adap.PCR    = 1;

	/* copy TS header */
	nbytes += vidtv_स_नकल(args.dest_buf,
			       args.dest_offset + nbytes,
			       args.buf_sz,
			       &ts_header,
			       माप(ts_header));

	/* ग_लिखो the adap after the TS header */
	nbytes += vidtv_स_नकल(args.dest_buf,
			       args.dest_offset + nbytes,
			       args.buf_sz,
			       &ts_adap,
			       माप(ts_adap));

	/* ग_लिखो the PCR optional */
	nbytes += vidtv_ts_ग_लिखो_pcr_bits(args.dest_buf,
					  args.dest_offset + nbytes,
					  args.pcr);

	nbytes += vidtv_स_रखो(args.dest_buf,
			       args.dest_offset + nbytes,
			       args.buf_sz,
			       TS_FILL_BYTE,
			       TS_PACKET_LEN - nbytes);

	/* we should have written exactly _one_ 188byte packet */
	अगर (nbytes != TS_PACKET_LEN)
		pr_warn_ratelimited("Expected exactly %d bytes, got %d\n",
				    TS_PACKET_LEN,
				    nbytes);

	वापस nbytes;
पूर्ण
