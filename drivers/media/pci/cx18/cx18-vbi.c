<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 Vertical Blank Interval support functions
 *
 *  Derived from ivtv-vbi.c
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 */

#समावेश "cx18-driver.h"
#समावेश "cx18-vbi.h"
#समावेश "cx18-ioctl.h"
#समावेश "cx18-queue.h"

/*
 * Raster Reference/Protection (RP) bytes, used in Start/End Active
 * Video codes emitted from the digitzer in VIP 1.x mode, that flag the start
 * of VBI sample or VBI ancillary data regions in the digital ratser line.
 *
 * Task FieldEven VerticalBlank HorizontalBlank 0 0 0 0
 */
अटल स्थिर u8 raw_vbi_sav_rp[2] = अणु 0x20, 0x60 पूर्ण;    /* __V_, _FV_ */
अटल स्थिर u8 sliced_vbi_eav_rp[2] = अणु 0xb0, 0xf0 पूर्ण; /* T_VH, TFVH */

अटल व्योम copy_vbi_data(काष्ठा cx18 *cx, पूर्णांक lines, u32 pts_stamp)
अणु
	पूर्णांक line = 0;
	पूर्णांक i;
	u32 linemask[2] = अणु 0, 0 पूर्ण;
	अचिन्हित लघु size;
	अटल स्थिर u8 mpeg_hdr_data[] = अणु
		/* MPEG-2 Program Pack */
		0x00, 0x00, 0x01, 0xba,		    /* Prog Pack start code */
		0x44, 0x00, 0x0c, 0x66, 0x24, 0x01, /* SCR, SCR Ext, markers */
		0x01, 0xd1, 0xd3,		    /* Mux Rate, markers */
		0xfa, 0xff, 0xff,		    /* Res, Suff cnt, Stuff */
		/* MPEG-2 Private Stream 1 PES Packet */
		0x00, 0x00, 0x01, 0xbd,		    /* Priv Stream 1 start */
		0x00, 0x1a,			    /* length */
		0x84, 0x80, 0x07,		    /* flags, hdr data len */
		0x21, 0x00, 0x5d, 0x63, 0xa7,	    /* PTS, markers */
		0xff, 0xff			    /* stuffing */
	पूर्ण;
	स्थिर पूर्णांक sd = माप(mpeg_hdr_data);	/* start of vbi data */
	पूर्णांक idx = cx->vbi.frame % CX18_VBI_FRAMES;
	u8 *dst = &cx->vbi.sliced_mpeg_data[idx][0];

	क्रम (i = 0; i < lines; i++) अणु
		काष्ठा v4l2_sliced_vbi_data *sdata = cx->vbi.sliced_data + i;
		पूर्णांक f, l;

		अगर (sdata->id == 0)
			जारी;

		l = sdata->line - 6;
		f = sdata->field;
		अगर (f)
			l += 18;
		अगर (l < 32)
			linemask[0] |= (1 << l);
		अन्यथा
			linemask[1] |= (1 << (l - 32));
		dst[sd + 12 + line * 43] = cx18_service2vbi(sdata->id);
		स_नकल(dst + sd + 12 + line * 43 + 1, sdata->data, 42);
		line++;
	पूर्ण
	स_नकल(dst, mpeg_hdr_data, माप(mpeg_hdr_data));
	अगर (line == 36) अणु
		/* All lines are used, so there is no space क्रम the linemask
		   (the max size of the VBI data is 36 * 43 + 4 bytes).
		   So in this हाल we use the magic number 'ITV0'. */
		स_नकल(dst + sd, "ITV0", 4);
		स_हटाओ(dst + sd + 4, dst + sd + 12, line * 43);
		size = 4 + ((43 * line + 3) & ~3);
	पूर्ण अन्यथा अणु
		स_नकल(dst + sd, "itv0", 4);
		cpu_to_le32s(&linemask[0]);
		cpu_to_le32s(&linemask[1]);
		स_नकल(dst + sd + 4, &linemask[0], 8);
		size = 12 + ((43 * line + 3) & ~3);
	पूर्ण
	dst[4+16] = (size + 10) >> 8;
	dst[5+16] = (size + 10) & 0xff;
	dst[9+16] = 0x21 | ((pts_stamp >> 29) & 0x6);
	dst[10+16] = (pts_stamp >> 22) & 0xff;
	dst[11+16] = 1 | ((pts_stamp >> 14) & 0xff);
	dst[12+16] = (pts_stamp >> 7) & 0xff;
	dst[13+16] = 1 | ((pts_stamp & 0x7f) << 1);
	cx->vbi.sliced_mpeg_size[idx] = sd + size;
पूर्ण

/* Compress raw VBI क्रमmat, हटाओs leading SAV codes and surplus space
   after the frame.  Returns new compressed size. */
/* FIXME - this function ignores the input size. */
अटल u32 compress_raw_buf(काष्ठा cx18 *cx, u8 *buf, u32 size, u32 hdr_size)
अणु
	u32 line_size = VBI_ACTIVE_SAMPLES;
	u32 lines = cx->vbi.count * 2;
	u8 *q = buf;
	u8 *p;
	पूर्णांक i;

	/* Skip the header */
	buf += hdr_size;

	क्रम (i = 0; i < lines; i++) अणु
		p = buf + i * line_size;

		/* Look क्रम SAV code */
		अगर (p[0] != 0xff || p[1] || p[2] ||
		    (p[3] != raw_vbi_sav_rp[0] &&
		     p[3] != raw_vbi_sav_rp[1]))
			अवरोध;
		अगर (i == lines - 1) अणु
			/* last line is hdr_size bytes लघु - extrapolate it */
			स_नकल(q, p + 4, line_size - 4 - hdr_size);
			q += line_size - 4 - hdr_size;
			p += line_size - hdr_size - 1;
			स_रखो(q, (पूर्णांक) *p, hdr_size);
		पूर्ण अन्यथा अणु
			स_नकल(q, p + 4, line_size - 4);
			q += line_size - 4;
		पूर्ण
	पूर्ण
	वापस lines * (line_size - 4);
पूर्ण

अटल u32 compress_sliced_buf(काष्ठा cx18 *cx, u8 *buf, u32 size,
			       स्थिर u32 hdr_size)
अणु
	काष्ठा v4l2_decode_vbi_line vbi;
	पूर्णांक i;
	u32 line = 0;
	u32 line_size = cx->is_60hz ? VBI_HBLANK_SAMPLES_60HZ
				    : VBI_HBLANK_SAMPLES_50HZ;

	/* find the first valid line */
	क्रम (i = hdr_size, buf += hdr_size; i < size; i++, buf++) अणु
		अगर (buf[0] == 0xff && !buf[1] && !buf[2] &&
		    (buf[3] == sliced_vbi_eav_rp[0] ||
		     buf[3] == sliced_vbi_eav_rp[1]))
			अवरोध;
	पूर्ण

	/*
	 * The last line is लघु by hdr_size bytes, but क्रम the reमुख्यing
	 * checks against size, we pretend that it is not, by counting the
	 * header bytes we knowingly skipped
	 */
	size -= (i - hdr_size);
	अगर (size < line_size)
		वापस line;

	क्रम (i = 0; i < size / line_size; i++) अणु
		u8 *p = buf + i * line_size;

		/* Look क्रम EAV code  */
		अगर (p[0] != 0xff || p[1] || p[2] ||
		    (p[3] != sliced_vbi_eav_rp[0] &&
		     p[3] != sliced_vbi_eav_rp[1]))
			जारी;
		vbi.p = p + 4;
		v4l2_subdev_call(cx->sd_av, vbi, decode_vbi_line, &vbi);
		अगर (vbi.type) अणु
			cx->vbi.sliced_data[line].id = vbi.type;
			cx->vbi.sliced_data[line].field = vbi.is_second_field;
			cx->vbi.sliced_data[line].line = vbi.line;
			स_नकल(cx->vbi.sliced_data[line].data, vbi.p, 42);
			line++;
		पूर्ण
	पूर्ण
	वापस line;
पूर्ण

अटल व्योम _cx18_process_vbi_data(काष्ठा cx18 *cx, काष्ठा cx18_buffer *buf)
अणु
	/*
	 * The CX23418 provides a 12 byte header in its raw VBI buffers to us:
	 * 0x3fffffff [4 bytes of something] [4 byte presentation समय stamp]
	 */
	काष्ठा vbi_data_hdr अणु
		__be32 magic;
		__be32 unknown;
		__be32 pts;
	पूर्ण *hdr = (काष्ठा vbi_data_hdr *) buf->buf;

	u8 *p = (u8 *) buf->buf;
	u32 size = buf->bytesused;
	u32 pts;
	पूर्णांक lines;

	/*
	 * The CX23418 sends us data that is 32 bit little-endian swapped,
	 * but we want the raw VBI bytes in the order they were in the raster
	 * line.  This has a side effect of making the header big endian
	 */
	cx18_buf_swap(buf);

	/* Raw VBI data */
	अगर (cx18_raw_vbi(cx)) अणु

		size = buf->bytesused =
		     compress_raw_buf(cx, p, size, माप(काष्ठा vbi_data_hdr));

		/*
		 * Hack needed क्रम compatibility with old VBI software.
		 * Write the frame # at the last 4 bytes of the frame
		 */
		p += size - 4;
		स_नकल(p, &cx->vbi.frame, 4);
		cx->vbi.frame++;
		वापस;
	पूर्ण

	/* Sliced VBI data with data insertion */

	pts = (be32_to_cpu(hdr->magic) == 0x3fffffff) ? be32_to_cpu(hdr->pts)
						      : 0;

	lines = compress_sliced_buf(cx, p, size, माप(काष्ठा vbi_data_hdr));

	/* always वापस at least one empty line */
	अगर (lines == 0) अणु
		cx->vbi.sliced_data[0].id = 0;
		cx->vbi.sliced_data[0].line = 0;
		cx->vbi.sliced_data[0].field = 0;
		lines = 1;
	पूर्ण
	buf->bytesused = size = lines * माप(cx->vbi.sliced_data[0]);
	स_नकल(p, &cx->vbi.sliced_data[0], size);

	अगर (cx->vbi.insert_mpeg)
		copy_vbi_data(cx, lines, pts);
	cx->vbi.frame++;
पूर्ण

व्योम cx18_process_vbi_data(काष्ठा cx18 *cx, काष्ठा cx18_mdl *mdl,
			   पूर्णांक streamtype)
अणु
	काष्ठा cx18_buffer *buf;
	u32 orig_used;

	अगर (streamtype != CX18_ENC_STREAM_TYPE_VBI)
		वापस;

	/*
	 * Big assumption here:
	 * Every buffer hooked to the MDL's buf_list is a complete VBI frame
	 * that ends at the end of the buffer.
	 *
	 * To assume anything अन्यथा would make the code in this file
	 * more complex, or require extra स_नकल()'s to make the
	 * buffers satisfy the above assumption.  It's just simpler to set
	 * up the encoder buffer transfers to make the assumption true.
	 */
	list_क्रम_each_entry(buf, &mdl->buf_list, list) अणु
		orig_used = buf->bytesused;
		अगर (orig_used == 0)
			अवरोध;
		_cx18_process_vbi_data(cx, buf);
		mdl->bytesused -= (orig_used - buf->bytesused);
	पूर्ण
पूर्ण
