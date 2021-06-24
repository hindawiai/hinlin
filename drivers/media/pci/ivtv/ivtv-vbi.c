<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Vertical Blank Interval support functions
    Copyright (C) 2004-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-i2c.h"
#समावेश "ivtv-ioctl.h"
#समावेश "ivtv-queue.h"
#समावेश "ivtv-cards.h"
#समावेश "ivtv-vbi.h"

अटल व्योम ivtv_set_vps(काष्ठा ivtv *itv, पूर्णांक enabled)
अणु
	काष्ठा v4l2_sliced_vbi_data data;

	अगर (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		वापस;
	data.id = V4L2_SLICED_VPS;
	data.field = 0;
	data.line = enabled ? 16 : 0;
	data.data[2] = itv->vbi.vps_payload.data[0];
	data.data[8] = itv->vbi.vps_payload.data[1];
	data.data[9] = itv->vbi.vps_payload.data[2];
	data.data[10] = itv->vbi.vps_payload.data[3];
	data.data[11] = itv->vbi.vps_payload.data[4];
	ivtv_call_hw(itv, IVTV_HW_SAA7127, vbi, s_vbi_data, &data);
पूर्ण

अटल व्योम ivtv_set_cc(काष्ठा ivtv *itv, पूर्णांक mode, स्थिर काष्ठा vbi_cc *cc)
अणु
	काष्ठा v4l2_sliced_vbi_data data;

	अगर (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		वापस;
	data.id = V4L2_SLICED_CAPTION_525;
	data.field = 0;
	data.line = (mode & 1) ? 21 : 0;
	data.data[0] = cc->odd[0];
	data.data[1] = cc->odd[1];
	ivtv_call_hw(itv, IVTV_HW_SAA7127, vbi, s_vbi_data, &data);
	data.field = 1;
	data.line = (mode & 2) ? 21 : 0;
	data.data[0] = cc->even[0];
	data.data[1] = cc->even[1];
	ivtv_call_hw(itv, IVTV_HW_SAA7127, vbi, s_vbi_data, &data);
पूर्ण

अटल व्योम ivtv_set_wss(काष्ठा ivtv *itv, पूर्णांक enabled, पूर्णांक mode)
अणु
	काष्ठा v4l2_sliced_vbi_data data;

	अगर (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		वापस;
	/* When using a 50 Hz प्रणाली, always turn on the
	   wide screen संकेत with 4x3 ratio as the शेष.
	   Turning this संकेत on and off can confuse certain
	   TVs. As far as I can tell there is no reason not to
	   transmit this संकेत. */
	अगर ((itv->std_out & V4L2_STD_625_50) && !enabled) अणु
		enabled = 1;
		mode = 0x08;  /* 4x3 full क्रमmat */
	पूर्ण
	data.id = V4L2_SLICED_WSS_625;
	data.field = 0;
	data.line = enabled ? 23 : 0;
	data.data[0] = mode & 0xff;
	data.data[1] = (mode >> 8) & 0xff;
	ivtv_call_hw(itv, IVTV_HW_SAA7127, vbi, s_vbi_data, &data);
पूर्ण

अटल पूर्णांक odd_parity(u8 c)
अणु
	c ^= (c >> 4);
	c ^= (c >> 2);
	c ^= (c >> 1);

	वापस c & 1;
पूर्ण

अटल व्योम ivtv_ग_लिखो_vbi_line(काष्ठा ivtv *itv,
				स्थिर काष्ठा v4l2_sliced_vbi_data *d,
				काष्ठा vbi_cc *cc, पूर्णांक *found_cc)
अणु
	काष्ठा vbi_info *vi = &itv->vbi;

	अगर (d->id == V4L2_SLICED_CAPTION_525 && d->line == 21) अणु
		अगर (d->field) अणु
			cc->even[0] = d->data[0];
			cc->even[1] = d->data[1];
		पूर्ण अन्यथा अणु
			cc->odd[0] = d->data[0];
			cc->odd[1] = d->data[1];
		पूर्ण
		*found_cc = 1;
	पूर्ण अन्यथा अगर (d->id == V4L2_SLICED_VPS && d->line == 16 && d->field == 0) अणु
		काष्ठा vbi_vps vps;

		vps.data[0] = d->data[2];
		vps.data[1] = d->data[8];
		vps.data[2] = d->data[9];
		vps.data[3] = d->data[10];
		vps.data[4] = d->data[11];
		अगर (स_भेद(&vps, &vi->vps_payload, माप(vps))) अणु
			vi->vps_payload = vps;
			set_bit(IVTV_F_I_UPDATE_VPS, &itv->i_flags);
		पूर्ण
	पूर्ण अन्यथा अगर (d->id == V4L2_SLICED_WSS_625 &&
		   d->line == 23 && d->field == 0) अणु
		पूर्णांक wss = d->data[0] | d->data[1] << 8;

		अगर (vi->wss_payload != wss) अणु
			vi->wss_payload = wss;
			set_bit(IVTV_F_I_UPDATE_WSS, &itv->i_flags);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ivtv_ग_लिखो_vbi_cc_lines(काष्ठा ivtv *itv, स्थिर काष्ठा vbi_cc *cc)
अणु
	काष्ठा vbi_info *vi = &itv->vbi;

	अगर (vi->cc_payload_idx < ARRAY_SIZE(vi->cc_payload)) अणु
		स_नकल(&vi->cc_payload[vi->cc_payload_idx], cc,
		       माप(काष्ठा vbi_cc));
		vi->cc_payload_idx++;
		set_bit(IVTV_F_I_UPDATE_CC, &itv->i_flags);
	पूर्ण
पूर्ण

अटल व्योम ivtv_ग_लिखो_vbi(काष्ठा ivtv *itv,
			   स्थिर काष्ठा v4l2_sliced_vbi_data *sliced,
			   माप_प्रकार cnt)
अणु
	काष्ठा vbi_cc cc = अणु .odd = अणु 0x80, 0x80 पूर्ण, .even = अणु 0x80, 0x80 पूर्ण पूर्ण;
	पूर्णांक found_cc = 0;
	माप_प्रकार i;

	क्रम (i = 0; i < cnt; i++)
		ivtv_ग_लिखो_vbi_line(itv, sliced + i, &cc, &found_cc);

	अगर (found_cc)
		ivtv_ग_लिखो_vbi_cc_lines(itv, &cc);
पूर्ण

sमाप_प्रकार
ivtv_ग_लिखो_vbi_from_user(काष्ठा ivtv *itv,
			 स्थिर काष्ठा v4l2_sliced_vbi_data __user *sliced,
			 माप_प्रकार cnt)
अणु
	काष्ठा vbi_cc cc = अणु .odd = अणु 0x80, 0x80 पूर्ण, .even = अणु 0x80, 0x80 पूर्ण पूर्ण;
	पूर्णांक found_cc = 0;
	माप_प्रकार i;
	काष्ठा v4l2_sliced_vbi_data d;
	sमाप_प्रकार ret = cnt * माप(काष्ठा v4l2_sliced_vbi_data);

	क्रम (i = 0; i < cnt; i++) अणु
		अगर (copy_from_user(&d, sliced + i,
				   माप(काष्ठा v4l2_sliced_vbi_data))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		ivtv_ग_लिखो_vbi_line(itv, &d, &cc, &found_cc);
	पूर्ण

	अगर (found_cc)
		ivtv_ग_लिखो_vbi_cc_lines(itv, &cc);

	वापस ret;
पूर्ण

अटल व्योम copy_vbi_data(काष्ठा ivtv *itv, पूर्णांक lines, u32 pts_stamp)
अणु
	पूर्णांक line = 0;
	पूर्णांक i;
	u32 linemask[2] = अणु 0, 0 पूर्ण;
	अचिन्हित लघु size;
	अटल स्थिर u8 mpeg_hdr_data[] = अणु
		0x00, 0x00, 0x01, 0xba, 0x44, 0x00, 0x0c, 0x66,
		0x24, 0x01, 0x01, 0xd1, 0xd3, 0xfa, 0xff, 0xff,
		0x00, 0x00, 0x01, 0xbd, 0x00, 0x1a, 0x84, 0x80,
		0x07, 0x21, 0x00, 0x5d, 0x63, 0xa7, 0xff, 0xff
	पूर्ण;
	स्थिर पूर्णांक sd = माप(mpeg_hdr_data);	/* start of vbi data */
	पूर्णांक idx = itv->vbi.frame % IVTV_VBI_FRAMES;
	u8 *dst = &itv->vbi.sliced_mpeg_data[idx][0];

	क्रम (i = 0; i < lines; i++) अणु
		पूर्णांक f, l;

		अगर (itv->vbi.sliced_data[i].id == 0)
			जारी;

		l = itv->vbi.sliced_data[i].line - 6;
		f = itv->vbi.sliced_data[i].field;
		अगर (f)
			l += 18;
		अगर (l < 32)
			linemask[0] |= (1 << l);
		अन्यथा
			linemask[1] |= (1 << (l - 32));
		dst[sd + 12 + line * 43] =
			ivtv_service2vbi(itv->vbi.sliced_data[i].id);
		स_नकल(dst + sd + 12 + line * 43 + 1, itv->vbi.sliced_data[i].data, 42);
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
	itv->vbi.sliced_mpeg_size[idx] = sd + size;
पूर्ण

अटल पूर्णांक ivtv_convert_ivtv_vbi(काष्ठा ivtv *itv, u8 *p)
अणु
	u32 linemask[2];
	पूर्णांक i, l, id2;
	पूर्णांक line = 0;

	अगर (!स_भेद(p, "itv0", 4)) अणु
		स_नकल(linemask, p + 4, 8);
		p += 12;
	पूर्ण अन्यथा अगर (!स_भेद(p, "ITV0", 4)) अणु
		linemask[0] = 0xffffffff;
		linemask[1] = 0xf;
		p += 4;
	पूर्ण अन्यथा अणु
		/* unknown VBI data, convert to empty VBI frame */
		linemask[0] = linemask[1] = 0;
	पूर्ण
	क्रम (i = 0; i < 36; i++) अणु
		पूर्णांक err = 0;

		अगर (i < 32 && !(linemask[0] & (1 << i)))
			जारी;
		अगर (i >= 32 && !(linemask[1] & (1 << (i - 32))))
			जारी;
		id2 = *p & 0xf;
		चयन (id2) अणु
		हाल IVTV_SLICED_TYPE_TELETEXT_B:
			id2 = V4L2_SLICED_TELETEXT_B;
			अवरोध;
		हाल IVTV_SLICED_TYPE_CAPTION_525:
			id2 = V4L2_SLICED_CAPTION_525;
			err = !odd_parity(p[1]) || !odd_parity(p[2]);
			अवरोध;
		हाल IVTV_SLICED_TYPE_VPS:
			id2 = V4L2_SLICED_VPS;
			अवरोध;
		हाल IVTV_SLICED_TYPE_WSS_625:
			id2 = V4L2_SLICED_WSS_625;
			अवरोध;
		शेष:
			id2 = 0;
			अवरोध;
		पूर्ण
		अगर (err == 0) अणु
			l = (i < 18) ? i + 6 : i - 18 + 6;
			itv->vbi.sliced_dec_data[line].line = l;
			itv->vbi.sliced_dec_data[line].field = i >= 18;
			itv->vbi.sliced_dec_data[line].id = id2;
			स_नकल(itv->vbi.sliced_dec_data[line].data, p + 1, 42);
			line++;
		पूर्ण
		p += 43;
	पूर्ण
	जबतक (line < 36) अणु
		itv->vbi.sliced_dec_data[line].id = 0;
		itv->vbi.sliced_dec_data[line].line = 0;
		itv->vbi.sliced_dec_data[line].field = 0;
		line++;
	पूर्ण
	वापस line * माप(itv->vbi.sliced_dec_data[0]);
पूर्ण

/* Compress raw VBI क्रमmat, हटाओs leading SAV codes and surplus space after the
   field.
   Returns new compressed size. */
अटल u32 compress_raw_buf(काष्ठा ivtv *itv, u8 *buf, u32 size)
अणु
	u32 line_size = itv->vbi.raw_decoder_line_size;
	u32 lines = itv->vbi.count;
	u8 sav1 = itv->vbi.raw_decoder_sav_odd_field;
	u8 sav2 = itv->vbi.raw_decoder_sav_even_field;
	u8 *q = buf;
	u8 *p;
	पूर्णांक i;

	क्रम (i = 0; i < lines; i++) अणु
		p = buf + i * line_size;

		/* Look क्रम SAV code */
		अगर (p[0] != 0xff || p[1] || p[2] || (p[3] != sav1 && p[3] != sav2)) अणु
			अवरोध;
		पूर्ण
		स_नकल(q, p + 4, line_size - 4);
		q += line_size - 4;
	पूर्ण
	वापस lines * (line_size - 4);
पूर्ण


/* Compressed VBI क्रमmat, all found sliced blocks put next to one another
   Returns new compressed size */
अटल u32 compress_sliced_buf(काष्ठा ivtv *itv, u32 line, u8 *buf, u32 size, u8 sav)
अणु
	u32 line_size = itv->vbi.sliced_decoder_line_size;
	काष्ठा v4l2_decode_vbi_line vbi = अणुपूर्ण;
	पूर्णांक i;
	अचिन्हित lines = 0;

	/* find the first valid line */
	क्रम (i = 0; i < size; i++, buf++) अणु
		अगर (buf[0] == 0xff && !buf[1] && !buf[2] && buf[3] == sav)
			अवरोध;
	पूर्ण

	size -= i;
	अगर (size < line_size) अणु
		वापस line;
	पूर्ण
	क्रम (i = 0; i < size / line_size; i++) अणु
		u8 *p = buf + i * line_size;

		/* Look क्रम SAV code  */
		अगर (p[0] != 0xff || p[1] || p[2] || p[3] != sav) अणु
			जारी;
		पूर्ण
		vbi.p = p + 4;
		v4l2_subdev_call(itv->sd_video, vbi, decode_vbi_line, &vbi);
		अगर (vbi.type && !(lines & (1 << vbi.line))) अणु
			lines |= 1 << vbi.line;
			itv->vbi.sliced_data[line].id = vbi.type;
			itv->vbi.sliced_data[line].field = vbi.is_second_field;
			itv->vbi.sliced_data[line].line = vbi.line;
			स_नकल(itv->vbi.sliced_data[line].data, vbi.p, 42);
			line++;
		पूर्ण
	पूर्ण
	वापस line;
पूर्ण

व्योम ivtv_process_vbi_data(काष्ठा ivtv *itv, काष्ठा ivtv_buffer *buf,
			   u64 pts_stamp, पूर्णांक streamtype)
अणु
	u8 *p = (u8 *) buf->buf;
	u32 size = buf->bytesused;
	पूर्णांक y;

	/* Raw VBI data */
	अगर (streamtype == IVTV_ENC_STREAM_TYPE_VBI && ivtv_raw_vbi(itv)) अणु
		u8 type;

		ivtv_buf_swap(buf);

		type = p[3];

		size = buf->bytesused = compress_raw_buf(itv, p, size);

		/* second field of the frame? */
		अगर (type == itv->vbi.raw_decoder_sav_even_field) अणु
			/* Dirty hack needed क्रम backwards
			   compatibility of old VBI software. */
			p += size - 4;
			स_नकल(p, &itv->vbi.frame, 4);
			itv->vbi.frame++;
		पूर्ण
		वापस;
	पूर्ण

	/* Sliced VBI data with data insertion */
	अगर (streamtype == IVTV_ENC_STREAM_TYPE_VBI) अणु
		पूर्णांक lines;

		ivtv_buf_swap(buf);

		/* first field */
		lines = compress_sliced_buf(itv, 0, p, size / 2,
			itv->vbi.sliced_decoder_sav_odd_field);
		/* second field */
		/* experimentation shows that the second half करोes not always begin
		   at the exact address. So start a bit earlier (hence 32). */
		lines = compress_sliced_buf(itv, lines, p + size / 2 - 32, size / 2 + 32,
			itv->vbi.sliced_decoder_sav_even_field);
		/* always वापस at least one empty line */
		अगर (lines == 0) अणु
			itv->vbi.sliced_data[0].id = 0;
			itv->vbi.sliced_data[0].line = 0;
			itv->vbi.sliced_data[0].field = 0;
			lines = 1;
		पूर्ण
		buf->bytesused = size = lines * माप(itv->vbi.sliced_data[0]);
		स_नकल(p, &itv->vbi.sliced_data[0], size);

		अगर (itv->vbi.insert_mpeg) अणु
			copy_vbi_data(itv, lines, pts_stamp);
		पूर्ण
		itv->vbi.frame++;
		वापस;
	पूर्ण

	/* Sliced VBI re-inserted from an MPEG stream */
	अगर (streamtype == IVTV_DEC_STREAM_TYPE_VBI) अणु
		/* If the size is not 4-byte aligned, then the starting address
		   क्रम the swapping is also shअगरted. After swapping the data the
		   real start address of the VBI data is exactly 4 bytes after the
		   original start. It's a bit fiddly but it works like a अक्षरm.
		   Non-4-byte alignment happens when an lseek is करोne on the input
		   mpeg file to a non-4-byte aligned position. So on arrival here
		   the VBI data is also non-4-byte aligned. */
		पूर्णांक offset = size & 3;
		पूर्णांक cnt;

		अगर (offset) अणु
			p += 4 - offset;
		पूर्ण
		/* Swap Buffer */
		क्रम (y = 0; y < size; y += 4) अणु
		       swab32s((u32 *)(p + y));
		पूर्ण

		cnt = ivtv_convert_ivtv_vbi(itv, p + offset);
		स_नकल(buf->buf, itv->vbi.sliced_dec_data, cnt);
		buf->bytesused = cnt;

		ivtv_ग_लिखो_vbi(itv, itv->vbi.sliced_dec_data,
			       cnt / माप(itv->vbi.sliced_dec_data[0]));
		वापस;
	पूर्ण
पूर्ण

व्योम ivtv_disable_cc(काष्ठा ivtv *itv)
अणु
	काष्ठा vbi_cc cc = अणु .odd = अणु 0x80, 0x80 पूर्ण, .even = अणु 0x80, 0x80 पूर्ण पूर्ण;

	clear_bit(IVTV_F_I_UPDATE_CC, &itv->i_flags);
	ivtv_set_cc(itv, 0, &cc);
	itv->vbi.cc_payload_idx = 0;
पूर्ण


व्योम ivtv_vbi_work_handler(काष्ठा ivtv *itv)
अणु
	काष्ठा vbi_info *vi = &itv->vbi;
	काष्ठा v4l2_sliced_vbi_data data;
	काष्ठा vbi_cc cc = अणु .odd = अणु 0x80, 0x80 पूर्ण, .even = अणु 0x80, 0x80 पूर्ण पूर्ण;

	/* Lock */
	अगर (itv->output_mode == OUT_PASSTHROUGH) अणु
		अगर (itv->is_50hz) अणु
			data.id = V4L2_SLICED_WSS_625;
			data.field = 0;

			अगर (v4l2_subdev_call(itv->sd_video, vbi, g_vbi_data, &data) == 0) अणु
				ivtv_set_wss(itv, 1, data.data[0] & 0xf);
				vi->wss_missing_cnt = 0;
			पूर्ण अन्यथा अगर (vi->wss_missing_cnt == 4) अणु
				ivtv_set_wss(itv, 1, 0x8);  /* 4x3 full क्रमmat */
			पूर्ण अन्यथा अणु
				vi->wss_missing_cnt++;
			पूर्ण
		पूर्ण
		अन्यथा अणु
			पूर्णांक mode = 0;

			data.id = V4L2_SLICED_CAPTION_525;
			data.field = 0;
			अगर (v4l2_subdev_call(itv->sd_video, vbi, g_vbi_data, &data) == 0) अणु
				mode |= 1;
				cc.odd[0] = data.data[0];
				cc.odd[1] = data.data[1];
			पूर्ण
			data.field = 1;
			अगर (v4l2_subdev_call(itv->sd_video, vbi, g_vbi_data, &data) == 0) अणु
				mode |= 2;
				cc.even[0] = data.data[0];
				cc.even[1] = data.data[1];
			पूर्ण
			अगर (mode) अणु
				vi->cc_missing_cnt = 0;
				ivtv_set_cc(itv, mode, &cc);
			पूर्ण अन्यथा अगर (vi->cc_missing_cnt == 4) अणु
				ivtv_set_cc(itv, 0, &cc);
			पूर्ण अन्यथा अणु
				vi->cc_missing_cnt++;
			पूर्ण
		पूर्ण
		वापस;
	पूर्ण

	अगर (test_and_clear_bit(IVTV_F_I_UPDATE_WSS, &itv->i_flags)) अणु
		ivtv_set_wss(itv, 1, vi->wss_payload & 0xf);
	पूर्ण

	अगर (test_bit(IVTV_F_I_UPDATE_CC, &itv->i_flags)) अणु
		अगर (vi->cc_payload_idx == 0) अणु
			clear_bit(IVTV_F_I_UPDATE_CC, &itv->i_flags);
			ivtv_set_cc(itv, 3, &cc);
		पूर्ण
		जबतक (vi->cc_payload_idx) अणु
			cc = vi->cc_payload[0];

			स_हटाओ(vi->cc_payload, vi->cc_payload + 1,
					माप(vi->cc_payload) - माप(vi->cc_payload[0]));
			vi->cc_payload_idx--;
			अगर (vi->cc_payload_idx && cc.odd[0] == 0x80 && cc.odd[1] == 0x80)
				जारी;

			ivtv_set_cc(itv, 3, &cc);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (test_and_clear_bit(IVTV_F_I_UPDATE_VPS, &itv->i_flags)) अणु
		ivtv_set_vps(itv, 1);
	पूर्ण
पूर्ण
