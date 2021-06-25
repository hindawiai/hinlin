<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
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

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s, %d: " fmt, __func__, __LINE__

#समावेश <linux/types.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/ratelimit.h>

#समावेश "vidtv_pes.h"
#समावेश "vidtv_common.h"
#समावेश "vidtv_encoder.h"
#समावेश "vidtv_ts.h"

#घोषणा PRIVATE_STREAM_1_ID 0xbd /* निजी_stream_1. See SMPTE 302M-2007 p.6 */
#घोषणा PES_HEADER_MAX_STUFFING_BYTES 32
#घोषणा PES_TS_HEADER_MAX_STUFFING_BYTES 182

अटल u32 vidtv_pes_op_get_len(bool send_pts, bool send_dts)
अणु
	u32 len = 0;

	/* the flags must always be sent */
	len += माप(काष्ठा vidtv_pes_optional);

	/* From all optionals, we might send these क्रम now */
	अगर (send_pts && send_dts)
		len += माप(काष्ठा vidtv_pes_optional_pts_dts);
	अन्यथा अगर (send_pts)
		len += माप(काष्ठा vidtv_pes_optional_pts);

	वापस len;
पूर्ण

#घोषणा SIZE_PCR (6 + माप(काष्ठा vidtv_mpeg_ts_adaption))

अटल u32 vidtv_pes_h_get_len(bool send_pts, bool send_dts)
अणु
	u32 len = 0;

	/* PES header length notwithstanding stuffing bytes */

	len += माप(काष्ठा vidtv_mpeg_pes);
	len += vidtv_pes_op_get_len(send_pts, send_dts);

	वापस len;
पूर्ण

अटल u32 vidtv_pes_ग_लिखो_header_stuffing(काष्ठा pes_header_ग_लिखो_args *args)
अणु
	/*
	 * This is a fixed 8-bit value equal to '0xFF' that can be inserted
	 * by the encoder, क्रम example to meet the requirements of the channel.
	 * It is discarded by the decoder. No more than 32 stuffing bytes shall
	 * be present in one PES packet header.
	 */
	अगर (args->n_pes_h_s_bytes > PES_HEADER_MAX_STUFFING_BYTES) अणु
		pr_warn_ratelimited("More than %d stuffing bytes in PES packet header\n",
				    PES_HEADER_MAX_STUFFING_BYTES);
		args->n_pes_h_s_bytes = PES_HEADER_MAX_STUFFING_BYTES;
	पूर्ण

	वापस vidtv_स_रखो(args->dest_buf,
			    args->dest_offset,
			    args->dest_buf_sz,
			    TS_FILL_BYTE,
			    args->n_pes_h_s_bytes);
पूर्ण

अटल u32 vidtv_pes_ग_लिखो_pts_dts(काष्ठा pes_header_ग_लिखो_args *args)
अणु
	u32 nbytes = 0;  /* the number of bytes written by this function */

	काष्ठा vidtv_pes_optional_pts pts = अणुपूर्ण;
	काष्ठा vidtv_pes_optional_pts_dts pts_dts = अणुपूर्ण;
	व्योम *op = शून्य;
	माप_प्रकार op_sz = 0;
	u64 mask1;
	u64 mask2;
	u64 mask3;

	अगर (!args->send_pts && args->send_dts)
		वापस 0;

	mask1 = GENMASK_ULL(32, 30);
	mask2 = GENMASK_ULL(29, 15);
	mask3 = GENMASK_ULL(14, 0);

	/* see ISO/IEC 13818-1 : 2000 p. 32 */
	अगर (args->send_pts && args->send_dts) अणु
		pts_dts.pts1 = (0x3 << 4) | ((args->pts & mask1) >> 29) | 0x1;
		pts_dts.pts2 = cpu_to_be16(((args->pts & mask2) >> 14) | 0x1);
		pts_dts.pts3 = cpu_to_be16(((args->pts & mask3) << 1) | 0x1);

		pts_dts.dts1 = (0x1 << 4) | ((args->dts & mask1) >> 29) | 0x1;
		pts_dts.dts2 = cpu_to_be16(((args->dts & mask2) >> 14) | 0x1);
		pts_dts.dts3 = cpu_to_be16(((args->dts & mask3) << 1) | 0x1);

		op = &pts_dts;
		op_sz = माप(pts_dts);

	पूर्ण अन्यथा अगर (args->send_pts) अणु
		pts.pts1 = (0x1 << 5) | ((args->pts & mask1) >> 29) | 0x1;
		pts.pts2 = cpu_to_be16(((args->pts & mask2) >> 14) | 0x1);
		pts.pts3 = cpu_to_be16(((args->pts & mask3) << 1) | 0x1);

		op = &pts;
		op_sz = माप(pts);
	पूर्ण

	/* copy PTS/DTS optional */
	nbytes += vidtv_स_नकल(args->dest_buf,
			       args->dest_offset + nbytes,
			       args->dest_buf_sz,
			       op,
			       op_sz);

	वापस nbytes;
पूर्ण

अटल u32 vidtv_pes_ग_लिखो_h(काष्ठा pes_header_ग_लिखो_args *args)
अणु
	u32 nbytes = 0;  /* the number of bytes written by this function */

	काष्ठा vidtv_mpeg_pes pes_header          = अणुपूर्ण;
	काष्ठा vidtv_pes_optional pes_optional    = अणुपूर्ण;
	काष्ठा pes_header_ग_लिखो_args pts_dts_args;
	u32 stream_id = (args->encoder_id == S302M) ? PRIVATE_STREAM_1_ID : args->stream_id;
	u16 pes_opt_bitfield = 0x01 << 15;

	pes_header.bitfield = cpu_to_be32((PES_START_CODE_PREFIX << 8) | stream_id);

	pes_header.length = cpu_to_be16(vidtv_pes_op_get_len(args->send_pts,
							     args->send_dts) +
							     args->access_unit_len);

	अगर (args->send_pts && args->send_dts)
		pes_opt_bitfield |= (0x3 << 6);
	अन्यथा अगर (args->send_pts)
		pes_opt_bitfield |= (0x1 << 7);

	pes_optional.bitfield = cpu_to_be16(pes_opt_bitfield);
	pes_optional.length = vidtv_pes_op_get_len(args->send_pts, args->send_dts) +
			      args->n_pes_h_s_bytes -
			      माप(काष्ठा vidtv_pes_optional);

	/* copy header */
	nbytes += vidtv_स_नकल(args->dest_buf,
			       args->dest_offset + nbytes,
			       args->dest_buf_sz,
			       &pes_header,
			       माप(pes_header));

	/* copy optional header bits */
	nbytes += vidtv_स_नकल(args->dest_buf,
			       args->dest_offset + nbytes,
			       args->dest_buf_sz,
			       &pes_optional,
			       माप(pes_optional));

	/* copy the timing inक्रमmation */
	pts_dts_args = *args;
	pts_dts_args.dest_offset = args->dest_offset + nbytes;
	nbytes += vidtv_pes_ग_लिखो_pts_dts(&pts_dts_args);

	/* ग_लिखो any PES header stuffing */
	nbytes += vidtv_pes_ग_लिखो_header_stuffing(args);

	वापस nbytes;
पूर्ण

अटल u32 vidtv_pes_ग_लिखो_pcr_bits(u8 *to, u32 to_offset, u64 pcr)
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

अटल u32 vidtv_pes_ग_लिखो_stuffing(काष्ठा pes_ts_header_ग_लिखो_args *args,
				    u32 dest_offset, bool need_pcr,
				    u64 *last_pcr)
अणु
	काष्ठा vidtv_mpeg_ts_adaption ts_adap = अणुपूर्ण;
	पूर्णांक stuff_nbytes;
	u32 nbytes = 0;

	अगर (!args->n_stuffing_bytes)
		वापस 0;

	ts_adap.अक्रमom_access = 1;

	/* length _immediately_ following 'adaptation_field_length' */
	अगर (need_pcr) अणु
		ts_adap.PCR = 1;
		ts_adap.length = SIZE_PCR;
	पूर्ण अन्यथा अणु
		ts_adap.length = माप(ts_adap);
	पूर्ण
	stuff_nbytes = args->n_stuffing_bytes - ts_adap.length;

	ts_adap.length -= माप(ts_adap.length);

	अगर (unlikely(stuff_nbytes < 0))
		stuff_nbytes = 0;

	ts_adap.length += stuff_nbytes;

	/* ग_लिखो the adap after the TS header */
	nbytes += vidtv_स_नकल(args->dest_buf,
			       dest_offset + nbytes,
			       args->dest_buf_sz,
			       &ts_adap,
			       माप(ts_adap));

	/* ग_लिखो the optional PCR */
	अगर (need_pcr) अणु
		nbytes += vidtv_pes_ग_लिखो_pcr_bits(args->dest_buf,
						   dest_offset + nbytes,
						   args->pcr);

		*last_pcr = args->pcr;
	पूर्ण

	/* ग_लिखो the stuffing bytes, अगर are there anything left */
	अगर (stuff_nbytes)
		nbytes += vidtv_स_रखो(args->dest_buf,
				       dest_offset + nbytes,
				       args->dest_buf_sz,
				       TS_FILL_BYTE,
				       stuff_nbytes);

	/*
	 * The n_stuffing_bytes contain a pre-calculated value of
	 * the amount of data that this function would पढ़ो, made from
	 * vidtv_pes_h_get_len(). If something went wrong, prपूर्णांक a warning
	 */
	अगर (nbytes != args->n_stuffing_bytes)
		pr_warn_ratelimited("write size was %d, expected %d\n",
				    nbytes, args->n_stuffing_bytes);

	वापस nbytes;
पूर्ण

अटल u32 vidtv_pes_ग_लिखो_ts_h(काष्ठा pes_ts_header_ग_लिखो_args args,
				bool need_pcr, u64 *last_pcr)
अणु
	/* number of bytes written by this function */
	u32 nbytes = 0;
	काष्ठा vidtv_mpeg_ts ts_header = अणुपूर्ण;
	u16 payload_start = !args.wrote_pes_header;

	ts_header.sync_byte        = TS_SYNC_BYTE;
	ts_header.bitfield         = cpu_to_be16((payload_start << 14) | args.pid);
	ts_header.scrambling       = 0;
	ts_header.adaptation_field = (args.n_stuffing_bytes) > 0;
	ts_header.payload          = (args.n_stuffing_bytes) < PES_TS_HEADER_MAX_STUFFING_BYTES;

	ts_header.continuity_counter = *args.continuity_counter;

	vidtv_ts_inc_cc(args.continuity_counter);

	/* ग_लिखो the TS header */
	nbytes += vidtv_स_नकल(args.dest_buf,
			       args.dest_offset + nbytes,
			       args.dest_buf_sz,
			       &ts_header,
			       माप(ts_header));

	/* ग_लिखो stuffing, अगर any */
	nbytes += vidtv_pes_ग_लिखो_stuffing(&args, args.dest_offset + nbytes,
					   need_pcr, last_pcr);

	वापस nbytes;
पूर्ण

u32 vidtv_pes_ग_लिखो_पूर्णांकo(काष्ठा pes_ग_लिखो_args *args)
अणु
	u32 unaligned_bytes = (args->dest_offset % TS_PACKET_LEN);
	काष्ठा pes_ts_header_ग_लिखो_args ts_header_args = अणु
		.dest_buf		= args->dest_buf,
		.dest_buf_sz		= args->dest_buf_sz,
		.pid			= args->pid,
		.pcr			= args->pcr,
		.continuity_counter	= args->continuity_counter,
	पूर्ण;
	काष्ठा pes_header_ग_लिखो_args pes_header_args = अणु
		.dest_buf		= args->dest_buf,
		.dest_buf_sz		= args->dest_buf_sz,
		.encoder_id		= args->encoder_id,
		.send_pts		= args->send_pts,
		.pts			= args->pts,
		.send_dts		= args->send_dts,
		.dts			= args->dts,
		.stream_id		= args->stream_id,
		.n_pes_h_s_bytes	= args->n_pes_h_s_bytes,
		.access_unit_len	= args->access_unit_len,
	पूर्ण;
	u32 reमुख्यing_len = args->access_unit_len;
	bool wrote_pes_header = false;
	u64 last_pcr = args->pcr;
	bool need_pcr = true;
	u32 available_space;
	u32 payload_size;
	u32 stuff_bytes;
	u32 nbytes = 0;

	अगर (unaligned_bytes) अणु
		pr_warn_ratelimited("buffer is misaligned, while starting PES\n");

		/* क्रमcibly align and hope क्रम the best */
		nbytes += vidtv_स_रखो(args->dest_buf,
				       args->dest_offset + nbytes,
				       args->dest_buf_sz,
				       TS_FILL_BYTE,
				       TS_PACKET_LEN - unaligned_bytes);
	पूर्ण

	जबतक (reमुख्यing_len) अणु
		available_space = TS_PAYLOAD_LEN;
		/*
		 * The amount of space initially available in the TS packet.
		 * अगर this is the beginning of the PES packet, take पूर्णांकo account
		 * the space needed क्रम the TS header _and_ क्रम the PES header
		 */
		अगर (!wrote_pes_header)
			available_space -= vidtv_pes_h_get_len(args->send_pts,
							       args->send_dts);

		/*
		 * अगर the encoder has inserted stuffing bytes in the PES
		 * header, account क्रम them.
		 */
		available_space -= args->n_pes_h_s_bytes;

		/* Take the extra adaptation पूर्णांकo account अगर need to send PCR */
		अगर (need_pcr) अणु
			available_space -= SIZE_PCR;
			stuff_bytes = SIZE_PCR;
		पूर्ण अन्यथा अणु
			stuff_bytes = 0;
		पूर्ण

		/*
		 * how much of the _actual_ payload should be written in this
		 * packet.
		 */
		अगर (reमुख्यing_len >= available_space) अणु
			payload_size = available_space;
		पूर्ण अन्यथा अणु
			/* Last frame should ensure 188-bytes PS alignment */
			payload_size = reमुख्यing_len;
			stuff_bytes += available_space - payload_size;

			/*
			 * Ensure that the stuff bytes will be within the
			 * allowed range, decrementing the number of payload
			 * bytes to ग_लिखो अगर needed.
			 */
			अगर (stuff_bytes > PES_TS_HEADER_MAX_STUFFING_BYTES) अणु
				u32 पंचांगp = stuff_bytes - PES_TS_HEADER_MAX_STUFFING_BYTES;

				stuff_bytes = PES_TS_HEADER_MAX_STUFFING_BYTES;
				payload_size -= पंचांगp;
			पूर्ण
		पूर्ण

		/* ग_लिखो ts header */
		ts_header_args.dest_offset = args->dest_offset + nbytes;
		ts_header_args.wrote_pes_header	= wrote_pes_header;
		ts_header_args.n_stuffing_bytes	= stuff_bytes;

		nbytes += vidtv_pes_ग_लिखो_ts_h(ts_header_args, need_pcr,
					       &last_pcr);

		need_pcr = false;

		अगर (!wrote_pes_header) अणु
			/* ग_लिखो the PES header only once */
			pes_header_args.dest_offset = args->dest_offset +
						      nbytes;
			nbytes += vidtv_pes_ग_लिखो_h(&pes_header_args);
			wrote_pes_header = true;
		पूर्ण

		/* ग_लिखो as much of the payload as we possibly can */
		nbytes += vidtv_स_नकल(args->dest_buf,
				       args->dest_offset + nbytes,
				       args->dest_buf_sz,
				       args->from,
				       payload_size);

		args->from += payload_size;

		reमुख्यing_len -= payload_size;
	पूर्ण

	वापस nbytes;
पूर्ण
