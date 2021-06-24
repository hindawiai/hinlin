<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * V4L2 JPEG header parser helpers.
 *
 * Copyright (C) 2019 Pengutronix, Philipp Zabel <kernel@pengutronix.de>
 *
 * For reference, see JPEG ITU-T.81 (ISO/IEC 10918-1) [1]
 *
 * [1] https://www.w3.org/Graphics/JPEG/itu-t81.pdf
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <media/v4l2-jpeg.h>

MODULE_DESCRIPTION("V4L2 JPEG header parser helpers");
MODULE_AUTHOR("Philipp Zabel <kernel@pengutronix.de>");
MODULE_LICENSE("GPL");

/* Table B.1 - Marker code assignments */
#घोषणा SOF0	0xffc0	/* start of frame */
#घोषणा SOF1	0xffc1
#घोषणा SOF2	0xffc2
#घोषणा SOF3	0xffc3
#घोषणा SOF5	0xffc5
#घोषणा SOF7	0xffc7
#घोषणा JPG	0xffc8	/* extensions */
#घोषणा SOF9	0xffc9
#घोषणा SOF11	0xffcb
#घोषणा SOF13	0xffcd
#घोषणा SOF15	0xffcf
#घोषणा DHT	0xffc4	/* huffman table */
#घोषणा DAC	0xffcc	/* arithmetic coding conditioning */
#घोषणा RST0	0xffd0	/* restart */
#घोषणा RST7	0xffd7
#घोषणा SOI	0xffd8	/* start of image */
#घोषणा EOI	0xffd9	/* end of image */
#घोषणा SOS	0xffda	/* start of stream */
#घोषणा DQT	0xffdb	/* quantization table */
#घोषणा DNL	0xffdc	/* number of lines */
#घोषणा DRI	0xffdd	/* restart पूर्णांकerval */
#घोषणा DHP	0xffde	/* hierarchical progression */
#घोषणा EXP	0xffdf	/* expand reference */
#घोषणा APP0	0xffe0	/* application data */
#घोषणा APP14	0xffee	/* application data क्रम colour encoding */
#घोषणा APP15	0xffef
#घोषणा JPG0	0xfff0	/* extensions */
#घोषणा JPG13	0xfffd
#घोषणा COM	0xfffe	/* comment */
#घोषणा TEM	0xff01	/* temporary */

/**
 * काष्ठा jpeg_stream - JPEG byte stream
 * @curr: current position in stream
 * @end: end position, after last byte
 */
काष्ठा jpeg_stream अणु
	u8 *curr;
	u8 *end;
पूर्ण;

/* वापसs a value that fits पूर्णांकo u8, or negative error */
अटल पूर्णांक jpeg_get_byte(काष्ठा jpeg_stream *stream)
अणु
	अगर (stream->curr >= stream->end)
		वापस -EINVAL;

	वापस *stream->curr++;
पूर्ण

/* वापसs a value that fits पूर्णांकo u16, or negative error */
अटल पूर्णांक jpeg_get_word_be(काष्ठा jpeg_stream *stream)
अणु
	u16 word;

	अगर (stream->curr + माप(__be16) > stream->end)
		वापस -EINVAL;

	word = get_unaligned_be16(stream->curr);
	stream->curr += माप(__be16);

	वापस word;
पूर्ण

अटल पूर्णांक jpeg_skip(काष्ठा jpeg_stream *stream, माप_प्रकार len)
अणु
	अगर (stream->curr + len > stream->end)
		वापस -EINVAL;

	stream->curr += len;

	वापस 0;
पूर्ण

अटल पूर्णांक jpeg_next_marker(काष्ठा jpeg_stream *stream)
अणु
	पूर्णांक byte;
	u16 marker = 0;

	जबतक ((byte = jpeg_get_byte(stream)) >= 0) अणु
		marker = (marker << 8) | byte;
		/* skip stuffing bytes and REServed markers */
		अगर (marker == TEM || (marker > 0xffbf && marker < 0xffff))
			वापस marker;
	पूर्ण

	वापस byte;
पूर्ण

/* this करोes not advance the current position in the stream */
अटल पूर्णांक jpeg_reference_segment(काष्ठा jpeg_stream *stream,
				  काष्ठा v4l2_jpeg_reference *segment)
अणु
	u16 len;

	अगर (stream->curr + माप(__be16) > stream->end)
		वापस -EINVAL;

	len = get_unaligned_be16(stream->curr);
	अगर (stream->curr + len > stream->end)
		वापस -EINVAL;

	segment->start = stream->curr;
	segment->length = len;

	वापस 0;
पूर्ण

अटल पूर्णांक v4l2_jpeg_decode_subsampling(u8 nf, u8 h_v)
अणु
	अगर (nf == 1)
		वापस V4L2_JPEG_CHROMA_SUBSAMPLING_GRAY;

	/* no chroma subsampling क्रम 4-component images */
	अगर (nf == 4 && h_v != 0x11)
		वापस -EINVAL;

	चयन (h_v) अणु
	हाल 0x11:
		वापस V4L2_JPEG_CHROMA_SUBSAMPLING_444;
	हाल 0x21:
		वापस V4L2_JPEG_CHROMA_SUBSAMPLING_422;
	हाल 0x22:
		वापस V4L2_JPEG_CHROMA_SUBSAMPLING_420;
	हाल 0x41:
		वापस V4L2_JPEG_CHROMA_SUBSAMPLING_411;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक jpeg_parse_frame_header(काष्ठा jpeg_stream *stream, u16 sof_marker,
				   काष्ठा v4l2_jpeg_frame_header *frame_header)
अणु
	पूर्णांक len = jpeg_get_word_be(stream);

	अगर (len < 0)
		वापस len;
	/* Lf = 8 + 3 * Nf, Nf >= 1 */
	अगर (len < 8 + 3)
		वापस -EINVAL;

	अगर (frame_header) अणु
		/* Table B.2 - Frame header parameter sizes and values */
		पूर्णांक p, y, x, nf;
		पूर्णांक i;

		p = jpeg_get_byte(stream);
		अगर (p < 0)
			वापस p;
		/*
		 * Baseline DCT only supports 8-bit precision.
		 * Extended sequential DCT also supports 12-bit precision.
		 */
		अगर (p != 8 && (p != 12 || sof_marker != SOF1))
			वापस -EINVAL;

		y = jpeg_get_word_be(stream);
		अगर (y < 0)
			वापस y;
		अगर (y == 0)
			वापस -EINVAL;

		x = jpeg_get_word_be(stream);
		अगर (x < 0)
			वापस x;
		अगर (x == 0)
			वापस -EINVAL;

		nf = jpeg_get_byte(stream);
		अगर (nf < 0)
			वापस nf;
		/*
		 * The spec allows 1 <= Nf <= 255, but we only support up to 4
		 * components.
		 */
		अगर (nf < 1 || nf > V4L2_JPEG_MAX_COMPONENTS)
			वापस -EINVAL;
		अगर (len != 8 + 3 * nf)
			वापस -EINVAL;

		frame_header->precision = p;
		frame_header->height = y;
		frame_header->width = x;
		frame_header->num_components = nf;

		क्रम (i = 0; i < nf; i++) अणु
			काष्ठा v4l2_jpeg_frame_component_spec *component;
			पूर्णांक c, h_v, tq;

			c = jpeg_get_byte(stream);
			अगर (c < 0)
				वापस c;

			h_v = jpeg_get_byte(stream);
			अगर (h_v < 0)
				वापस h_v;
			अगर (i == 0) अणु
				पूर्णांक subs;

				subs = v4l2_jpeg_decode_subsampling(nf, h_v);
				अगर (subs < 0)
					वापस subs;
				frame_header->subsampling = subs;
			पूर्ण अन्यथा अगर (h_v != 0x11) अणु
				/* all chroma sampling factors must be 1 */
				वापस -EINVAL;
			पूर्ण

			tq = jpeg_get_byte(stream);
			अगर (tq < 0)
				वापस tq;

			component = &frame_header->component[i];
			component->component_identअगरier = c;
			component->horizontal_sampling_factor =
				(h_v >> 4) & 0xf;
			component->vertical_sampling_factor = h_v & 0xf;
			component->quantization_table_selector = tq;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस jpeg_skip(stream, len - 2);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jpeg_parse_scan_header(काष्ठा jpeg_stream *stream,
				  काष्ठा v4l2_jpeg_scan_header *scan_header)
अणु
	माप_प्रकार skip;
	पूर्णांक len = jpeg_get_word_be(stream);

	अगर (len < 0)
		वापस len;
	/* Ls = 8 + 3 * Ns, Ns >= 1 */
	अगर (len < 6 + 2)
		वापस -EINVAL;

	अगर (scan_header) अणु
		पूर्णांक ns;
		पूर्णांक i;

		ns = jpeg_get_byte(stream);
		अगर (ns < 0)
			वापस ns;
		अगर (ns < 1 || ns > 4 || len != 6 + 2 * ns)
			वापस -EINVAL;

		scan_header->num_components = ns;

		क्रम (i = 0; i < ns; i++) अणु
			काष्ठा v4l2_jpeg_scan_component_spec *component;
			पूर्णांक cs, td_ta;

			cs = jpeg_get_byte(stream);
			अगर (cs < 0)
				वापस cs;

			td_ta = jpeg_get_byte(stream);
			अगर (td_ta < 0)
				वापस td_ta;

			component = &scan_header->component[i];
			component->component_selector = cs;
			component->dc_entropy_coding_table_selector =
				(td_ta >> 4) & 0xf;
			component->ac_entropy_coding_table_selector =
				td_ta & 0xf;
		पूर्ण

		skip = 3; /* skip Ss, Se, Ah, and Al */
	पूर्ण अन्यथा अणु
		skip = len - 2;
	पूर्ण

	वापस jpeg_skip(stream, skip);
पूर्ण

/* B.2.4.1 Quantization table-specअगरication syntax */
अटल पूर्णांक jpeg_parse_quantization_tables(काष्ठा jpeg_stream *stream,
					  u8 precision,
					  काष्ठा v4l2_jpeg_reference *tables)
अणु
	पूर्णांक len = jpeg_get_word_be(stream);

	अगर (len < 0)
		वापस len;
	/* Lq = 2 + n * 65 (क्रम baseline DCT), n >= 1 */
	अगर (len < 2 + 65)
		वापस -EINVAL;

	len -= 2;
	जबतक (len >= 65) अणु
		u8 pq, tq, *qk;
		पूर्णांक ret;
		पूर्णांक pq_tq = jpeg_get_byte(stream);

		अगर (pq_tq < 0)
			वापस pq_tq;

		/* quantization table element precision */
		pq = (pq_tq >> 4) & 0xf;
		/*
		 * Only 8-bit Qk values क्रम 8-bit sample precision. Extended
		 * sequential DCT with 12-bit sample precision also supports
		 * 16-bit Qk values.
		 */
		अगर (pq != 0 && (pq != 1 || precision != 12))
			वापस -EINVAL;

		/* quantization table destination identअगरier */
		tq = pq_tq & 0xf;
		अगर (tq > 3)
			वापस -EINVAL;

		/* quantization table element */
		qk = stream->curr;
		ret = jpeg_skip(stream, pq ? 128 : 64);
		अगर (ret < 0)
			वापस -EINVAL;

		अगर (tables) अणु
			tables[tq].start = qk;
			tables[tq].length = pq ? 128 : 64;
		पूर्ण

		len -= pq ? 129 : 65;
	पूर्ण

	वापस 0;
पूर्ण

/* B.2.4.2 Huffman table-specअगरication syntax */
अटल पूर्णांक jpeg_parse_huffman_tables(काष्ठा jpeg_stream *stream,
				     काष्ठा v4l2_jpeg_reference *tables)
अणु
	पूर्णांक mt;
	पूर्णांक len = jpeg_get_word_be(stream);

	अगर (len < 0)
		वापस len;
	/* Table B.5 - Huffman table specअगरication parameter sizes and values */
	अगर (len < 2 + 17)
		वापस -EINVAL;

	क्रम (len -= 2; len >= 17; len -= 17 + mt) अणु
		u8 tc, th, *table;
		पूर्णांक tc_th = jpeg_get_byte(stream);
		पूर्णांक i, ret;

		अगर (tc_th < 0)
			वापस tc_th;

		/* table class - 0 = DC, 1 = AC */
		tc = (tc_th >> 4) & 0xf;
		अगर (tc > 1)
			वापस -EINVAL;

		/* huffman table destination identअगरier */
		th = tc_th & 0xf;
		/* only two Huffman tables क्रम baseline DCT */
		अगर (th > 1)
			वापस -EINVAL;

		/* BITS - number of Huffman codes with length i */
		table = stream->curr;
		mt = 0;
		क्रम (i = 0; i < 16; i++) अणु
			पूर्णांक li;

			li = jpeg_get_byte(stream);
			अगर (li < 0)
				वापस li;

			mt += li;
		पूर्ण
		/* HUFFVAL - values associated with each Huffman code */
		ret = jpeg_skip(stream, mt);
		अगर (ret < 0)
			वापस ret;

		अगर (tables) अणु
			tables[(tc << 1) | th].start = table;
			tables[(tc << 1) | th].length = stream->curr - table;
		पूर्ण
	पूर्ण

	वापस jpeg_skip(stream, len - 2);
पूर्ण

/* B.2.4.4 Restart पूर्णांकerval definition syntax */
अटल पूर्णांक jpeg_parse_restart_पूर्णांकerval(काष्ठा jpeg_stream *stream,
				       u16 *restart_पूर्णांकerval)
अणु
	पूर्णांक len = jpeg_get_word_be(stream);
	पूर्णांक ri;

	अगर (len < 0)
		वापस len;
	अगर (len != 4)
		वापस -EINVAL;

	ri = jpeg_get_word_be(stream);
	अगर (ri < 0)
		वापस ri;

	*restart_पूर्णांकerval = ri;

	वापस 0;
पूर्ण

अटल पूर्णांक jpeg_skip_segment(काष्ठा jpeg_stream *stream)
अणु
	पूर्णांक len = jpeg_get_word_be(stream);

	अगर (len < 0)
		वापस len;
	अगर (len < 2)
		वापस -EINVAL;

	वापस jpeg_skip(stream, len - 2);
पूर्ण

/* Rec. ITU-T T.872 (06/2012) 6.5.3 */
अटल पूर्णांक jpeg_parse_app14_data(काष्ठा jpeg_stream *stream,
				 क्रमागत v4l2_jpeg_app14_tf *tf)
अणु
	पूर्णांक ret;
	पूर्णांक lp;
	पूर्णांक skip;

	lp = jpeg_get_word_be(stream);
	अगर (lp < 0)
		वापस lp;

	/* Check क्रम "Adobe\0" in Ap1..6 */
	अगर (stream->curr + 6 > stream->end ||
	    म_भेदन(stream->curr, "Adobe\0", 6))
		वापस -EINVAL;

	/* get to Ap12 */
	ret = jpeg_skip(stream, 11);
	अगर (ret < 0)
		वापस ret;

	ret = jpeg_get_byte(stream);
	अगर (ret < 0)
		वापस ret;

	*tf = ret;

	/* skip the rest of the segment, this ensures at least it is complete */
	skip = lp - 2 - 11;
	वापस jpeg_skip(stream, skip);
पूर्ण

/**
 * v4l2_jpeg_parse_header - locate marker segments and optionally parse headers
 * @buf: address of the JPEG buffer, should start with a SOI marker
 * @len: length of the JPEG buffer
 * @out: वापसs marker segment positions and optionally parsed headers
 *
 * The out->scan_header poपूर्णांकer must be initialized to शून्य or poपूर्णांक to a valid
 * v4l2_jpeg_scan_header काष्ठाure. The out->huffman_tables and
 * out->quantization_tables poपूर्णांकers must be initialized to शून्य or poपूर्णांक to a
 * valid array of 4 v4l2_jpeg_reference काष्ठाures each.
 *
 * Returns 0 or negative error अगर parsing failed.
 */
पूर्णांक v4l2_jpeg_parse_header(व्योम *buf, माप_प्रकार len, काष्ठा v4l2_jpeg_header *out)
अणु
	काष्ठा jpeg_stream stream;
	पूर्णांक marker;
	पूर्णांक ret = 0;

	stream.curr = buf;
	stream.end = stream.curr + len;

	out->num_dht = 0;
	out->num_dqt = 0;

	/* the first bytes must be SOI, B.2.1 High-level syntax */
	अगर (jpeg_get_word_be(&stream) != SOI)
		वापस -EINVAL;

	/* init value to संकेत अगर this marker is not present */
	out->app14_tf = V4L2_JPEG_APP14_TF_UNKNOWN;

	/* loop through marker segments */
	जबतक ((marker = jpeg_next_marker(&stream)) >= 0) अणु
		चयन (marker) अणु
		/* baseline DCT, extended sequential DCT */
		हाल SOF0 ... SOF1:
			ret = jpeg_reference_segment(&stream, &out->sof);
			अगर (ret < 0)
				वापस ret;
			ret = jpeg_parse_frame_header(&stream, marker,
						      &out->frame);
			अवरोध;
		/* progressive, lossless */
		हाल SOF2 ... SOF3:
		/* dअगरferential coding */
		हाल SOF5 ... SOF7:
		/* arithmetic coding */
		हाल SOF9 ... SOF11:
		हाल SOF13 ... SOF15:
		हाल DAC:
		हाल TEM:
			वापस -EINVAL;

		हाल DHT:
			ret = jpeg_reference_segment(&stream,
					&out->dht[out->num_dht++ % 4]);
			अगर (ret < 0)
				वापस ret;
			अगर (!out->huffman_tables) अणु
				ret = jpeg_skip_segment(&stream);
				अवरोध;
			पूर्ण
			ret = jpeg_parse_huffman_tables(&stream,
							out->huffman_tables);
			अवरोध;
		हाल DQT:
			ret = jpeg_reference_segment(&stream,
					&out->dqt[out->num_dqt++ % 4]);
			अगर (ret < 0)
				वापस ret;
			अगर (!out->quantization_tables) अणु
				ret = jpeg_skip_segment(&stream);
				अवरोध;
			पूर्ण
			ret = jpeg_parse_quantization_tables(&stream,
					out->frame.precision,
					out->quantization_tables);
			अवरोध;
		हाल DRI:
			ret = jpeg_parse_restart_पूर्णांकerval(&stream,
							&out->restart_पूर्णांकerval);
			अवरोध;
		हाल APP14:
			ret = jpeg_parse_app14_data(&stream,
						    &out->app14_tf);
			अवरोध;
		हाल SOS:
			ret = jpeg_reference_segment(&stream, &out->sos);
			अगर (ret < 0)
				वापस ret;
			ret = jpeg_parse_scan_header(&stream, out->scan);
			/*
			 * stop parsing, the scan header marks the beginning of
			 * the entropy coded segment
			 */
			out->ecs_offset = stream.curr - (u8 *)buf;
			वापस ret;

		/* markers without parameters */
		हाल RST0 ... RST7: /* restart */
		हाल SOI: /* start of image */
		हाल EOI: /* end of image */
			अवरोध;

		/* skip unknown or unsupported marker segments */
		शेष:
			ret = jpeg_skip_segment(&stream);
			अवरोध;
		पूर्ण
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस marker;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_jpeg_parse_header);

/**
 * v4l2_jpeg_parse_frame_header - parse frame header
 * @buf: address of the frame header, after the SOF0 marker
 * @len: length of the frame header
 * @frame_header: वापसs the parsed frame header
 *
 * Returns 0 or negative error अगर parsing failed.
 */
पूर्णांक v4l2_jpeg_parse_frame_header(व्योम *buf, माप_प्रकार len,
				 काष्ठा v4l2_jpeg_frame_header *frame_header)
अणु
	काष्ठा jpeg_stream stream;

	stream.curr = buf;
	stream.end = stream.curr + len;
	वापस jpeg_parse_frame_header(&stream, SOF0, frame_header);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_jpeg_parse_frame_header);

/**
 * v4l2_jpeg_parse_scan_header - parse scan header
 * @buf: address of the scan header, after the SOS marker
 * @len: length of the scan header
 * @scan_header: वापसs the parsed scan header
 *
 * Returns 0 or negative error अगर parsing failed.
 */
पूर्णांक v4l2_jpeg_parse_scan_header(व्योम *buf, माप_प्रकार len,
				काष्ठा v4l2_jpeg_scan_header *scan_header)
अणु
	काष्ठा jpeg_stream stream;

	stream.curr = buf;
	stream.end = stream.curr + len;
	वापस jpeg_parse_scan_header(&stream, scan_header);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_jpeg_parse_scan_header);

/**
 * v4l2_jpeg_parse_quantization_tables - parse quantization tables segment
 * @buf: address of the quantization table segment, after the DQT marker
 * @len: length of the quantization table segment
 * @precision: sample precision (P) in bits per component
 * @q_tables: वापसs four references पूर्णांकo the buffer क्रम the
 *            four possible quantization table destinations
 *
 * Returns 0 or negative error अगर parsing failed.
 */
पूर्णांक v4l2_jpeg_parse_quantization_tables(व्योम *buf, माप_प्रकार len, u8 precision,
					काष्ठा v4l2_jpeg_reference *q_tables)
अणु
	काष्ठा jpeg_stream stream;

	stream.curr = buf;
	stream.end = stream.curr + len;
	वापस jpeg_parse_quantization_tables(&stream, precision, q_tables);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_jpeg_parse_quantization_tables);

/**
 * v4l2_jpeg_parse_huffman_tables - parse huffman tables segment
 * @buf: address of the Huffman table segment, after the DHT marker
 * @len: length of the Huffman table segment
 * @huffman_tables: वापसs four references पूर्णांकo the buffer क्रम the
 *                  four possible Huffman table destinations, in
 *                  the order DC0, DC1, AC0, AC1
 *
 * Returns 0 or negative error अगर parsing failed.
 */
पूर्णांक v4l2_jpeg_parse_huffman_tables(व्योम *buf, माप_प्रकार len,
				   काष्ठा v4l2_jpeg_reference *huffman_tables)
अणु
	काष्ठा jpeg_stream stream;

	stream.curr = buf;
	stream.end = stream.curr + len;
	वापस jpeg_parse_huffman_tables(&stream, huffman_tables);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_jpeg_parse_huffman_tables);
