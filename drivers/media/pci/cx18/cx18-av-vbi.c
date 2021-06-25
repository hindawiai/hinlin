<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 ADEC VBI functions
 *
 *  Derived from cx25840-vbi.c
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 */


#समावेश "cx18-driver.h"

/*
 * For sliced VBI output, we set up to use VIP-1.1, 8-bit mode,
 * NN counts 1 byte Dwords, an IDID with the VBI line # in it.
 * Thus, according to the VIP-2 Spec, our VBI ancillary data lines
 * (should!) look like:
 *	4 byte EAV code:          0xff 0x00 0x00 0xRP
 *	unknown number of possible idle bytes
 *	3 byte Anc data preamble: 0x00 0xff 0xff
 *	1 byte data identअगरier:   ne010iii (parity bits, 010, DID bits)
 *	1 byte secondary data id: nessssss (parity bits, SDID bits)
 *	1 byte data word count:   necccccc (parity bits, NN Dword count)
 *	2 byte Internal DID:	  VBI-line-# 0x80
 *	NN data bytes
 *	1 byte checksum
 *	Fill bytes needed to fil out to 4*NN bytes of payload
 *
 * The RP codes क्रम EAVs when in VIP-1.1 mode, not in raw mode, &
 * in the vertical blanking पूर्णांकerval are:
 *	0xb0 (Task         0 VerticalBlank HorizontalBlank 0 0 0 0)
 *	0xf0 (Task EvenField VerticalBlank HorizontalBlank 0 0 0 0)
 *
 * Since the V bit is only allowed to toggle in the EAV RP code, just
 * beक्रमe the first active region line and क्रम active lines, they are:
 *	0x90 (Task         0 0 HorizontalBlank 0 0 0 0)
 *	0xd0 (Task EvenField 0 HorizontalBlank 0 0 0 0)
 *
 * The user application DID bytes we care about are:
 *	0x91 (1 0 010        0 !ActiveLine AncDataPresent)
 *	0x55 (0 1 010 2ndField !ActiveLine AncDataPresent)
 *
 */
अटल स्थिर u8 sliced_vbi_did[2] = अणु 0x91, 0x55 पूर्ण;

काष्ठा vbi_anc_data अणु
	/* u8 eav[4]; */
	/* u8 idle[]; Variable number of idle bytes */
	u8 preamble[3];
	u8 did;
	u8 sdid;
	u8 data_count;
	u8 idid[2];
	u8 payload[1]; /* data_count of payload */
	/* u8 checksum; */
	/* u8 fill[]; Variable number of fill bytes */
पूर्ण;

अटल पूर्णांक odd_parity(u8 c)
अणु
	c ^= (c >> 4);
	c ^= (c >> 2);
	c ^= (c >> 1);

	वापस c & 1;
पूर्ण

अटल पूर्णांक decode_vps(u8 *dst, u8 *p)
अणु
	अटल स्थिर u8 biphase_tbl[] = अणु
		0xf0, 0x78, 0x70, 0xf0, 0xb4, 0x3c, 0x34, 0xb4,
		0xb0, 0x38, 0x30, 0xb0, 0xf0, 0x78, 0x70, 0xf0,
		0xd2, 0x5a, 0x52, 0xd2, 0x96, 0x1e, 0x16, 0x96,
		0x92, 0x1a, 0x12, 0x92, 0xd2, 0x5a, 0x52, 0xd2,
		0xd0, 0x58, 0x50, 0xd0, 0x94, 0x1c, 0x14, 0x94,
		0x90, 0x18, 0x10, 0x90, 0xd0, 0x58, 0x50, 0xd0,
		0xf0, 0x78, 0x70, 0xf0, 0xb4, 0x3c, 0x34, 0xb4,
		0xb0, 0x38, 0x30, 0xb0, 0xf0, 0x78, 0x70, 0xf0,
		0xe1, 0x69, 0x61, 0xe1, 0xa5, 0x2d, 0x25, 0xa5,
		0xa1, 0x29, 0x21, 0xa1, 0xe1, 0x69, 0x61, 0xe1,
		0xc3, 0x4b, 0x43, 0xc3, 0x87, 0x0f, 0x07, 0x87,
		0x83, 0x0b, 0x03, 0x83, 0xc3, 0x4b, 0x43, 0xc3,
		0xc1, 0x49, 0x41, 0xc1, 0x85, 0x0d, 0x05, 0x85,
		0x81, 0x09, 0x01, 0x81, 0xc1, 0x49, 0x41, 0xc1,
		0xe1, 0x69, 0x61, 0xe1, 0xa5, 0x2d, 0x25, 0xa5,
		0xa1, 0x29, 0x21, 0xa1, 0xe1, 0x69, 0x61, 0xe1,
		0xe0, 0x68, 0x60, 0xe0, 0xa4, 0x2c, 0x24, 0xa4,
		0xa0, 0x28, 0x20, 0xa0, 0xe0, 0x68, 0x60, 0xe0,
		0xc2, 0x4a, 0x42, 0xc2, 0x86, 0x0e, 0x06, 0x86,
		0x82, 0x0a, 0x02, 0x82, 0xc2, 0x4a, 0x42, 0xc2,
		0xc0, 0x48, 0x40, 0xc0, 0x84, 0x0c, 0x04, 0x84,
		0x80, 0x08, 0x00, 0x80, 0xc0, 0x48, 0x40, 0xc0,
		0xe0, 0x68, 0x60, 0xe0, 0xa4, 0x2c, 0x24, 0xa4,
		0xa0, 0x28, 0x20, 0xa0, 0xe0, 0x68, 0x60, 0xe0,
		0xf0, 0x78, 0x70, 0xf0, 0xb4, 0x3c, 0x34, 0xb4,
		0xb0, 0x38, 0x30, 0xb0, 0xf0, 0x78, 0x70, 0xf0,
		0xd2, 0x5a, 0x52, 0xd2, 0x96, 0x1e, 0x16, 0x96,
		0x92, 0x1a, 0x12, 0x92, 0xd2, 0x5a, 0x52, 0xd2,
		0xd0, 0x58, 0x50, 0xd0, 0x94, 0x1c, 0x14, 0x94,
		0x90, 0x18, 0x10, 0x90, 0xd0, 0x58, 0x50, 0xd0,
		0xf0, 0x78, 0x70, 0xf0, 0xb4, 0x3c, 0x34, 0xb4,
		0xb0, 0x38, 0x30, 0xb0, 0xf0, 0x78, 0x70, 0xf0,
	पूर्ण;

	u8 c, err = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 2 * 13; i += 2) अणु
		err |= biphase_tbl[p[i]] | biphase_tbl[p[i + 1]];
		c = (biphase_tbl[p[i + 1]] & 0xf) |
		    ((biphase_tbl[p[i]] & 0xf) << 4);
		dst[i / 2] = c;
	पूर्ण

	वापस err & 0xf0;
पूर्ण

पूर्णांक cx18_av_g_sliced_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_sliced_vbi_क्रमmat *svbi)
अणु
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);
	काष्ठा cx18_av_state *state = &cx->av_state;
	अटल स्थिर u16 lcr2vbi[] = अणु
		0, V4L2_SLICED_TELETEXT_B, 0,	/* 1 */
		0, V4L2_SLICED_WSS_625, 0,	/* 4 */
		V4L2_SLICED_CAPTION_525,	/* 6 */
		0, 0, V4L2_SLICED_VPS, 0, 0,	/* 9 */
		0, 0, 0, 0
	पूर्ण;
	पूर्णांक is_pal = !(state->std & V4L2_STD_525_60);
	पूर्णांक i;

	स_रखो(svbi->service_lines, 0, माप(svbi->service_lines));
	svbi->service_set = 0;

	/* we're करोne अगर raw VBI is active */
	अगर ((cx18_av_पढ़ो(cx, 0x404) & 0x10) == 0)
		वापस 0;

	अगर (is_pal) अणु
		क्रम (i = 7; i <= 23; i++) अणु
			u8 v = cx18_av_पढ़ो(cx, 0x424 + i - 7);

			svbi->service_lines[0][i] = lcr2vbi[v >> 4];
			svbi->service_lines[1][i] = lcr2vbi[v & 0xf];
			svbi->service_set |= svbi->service_lines[0][i] |
				svbi->service_lines[1][i];
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 10; i <= 21; i++) अणु
			u8 v = cx18_av_पढ़ो(cx, 0x424 + i - 10);

			svbi->service_lines[0][i] = lcr2vbi[v >> 4];
			svbi->service_lines[1][i] = lcr2vbi[v & 0xf];
			svbi->service_set |= svbi->service_lines[0][i] |
				svbi->service_lines[1][i];
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cx18_av_s_raw_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_vbi_क्रमmat *fmt)
अणु
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);
	काष्ठा cx18_av_state *state = &cx->av_state;

	/* Setup standard */
	cx18_av_std_setup(cx);

	/* VBI Offset */
	cx18_av_ग_लिखो(cx, 0x47f, state->slicer_line_delay);
	cx18_av_ग_लिखो(cx, 0x404, 0x2e);
	वापस 0;
पूर्ण

पूर्णांक cx18_av_s_sliced_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_sliced_vbi_क्रमmat *svbi)
अणु
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);
	काष्ठा cx18_av_state *state = &cx->av_state;
	पूर्णांक is_pal = !(state->std & V4L2_STD_525_60);
	पूर्णांक i, x;
	u8 lcr[24];

	क्रम (x = 0; x <= 23; x++)
		lcr[x] = 0x00;

	/* Setup standard */
	cx18_av_std_setup(cx);

	/* Sliced VBI */
	cx18_av_ग_लिखो(cx, 0x404, 0x32);	/* Ancillary data */
	cx18_av_ग_लिखो(cx, 0x406, 0x13);
	cx18_av_ग_लिखो(cx, 0x47f, state->slicer_line_delay);

	/* Force impossible lines to 0 */
	अगर (is_pal) अणु
		क्रम (i = 0; i <= 6; i++)
			svbi->service_lines[0][i] =
				svbi->service_lines[1][i] = 0;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i <= 9; i++)
			svbi->service_lines[0][i] =
				svbi->service_lines[1][i] = 0;

		क्रम (i = 22; i <= 23; i++)
			svbi->service_lines[0][i] =
				svbi->service_lines[1][i] = 0;
	पूर्ण

	/* Build रेजिस्टर values क्रम requested service lines */
	क्रम (i = 7; i <= 23; i++) अणु
		क्रम (x = 0; x <= 1; x++) अणु
			चयन (svbi->service_lines[1-x][i]) अणु
			हाल V4L2_SLICED_TELETEXT_B:
				lcr[i] |= 1 << (4 * x);
				अवरोध;
			हाल V4L2_SLICED_WSS_625:
				lcr[i] |= 4 << (4 * x);
				अवरोध;
			हाल V4L2_SLICED_CAPTION_525:
				lcr[i] |= 6 << (4 * x);
				अवरोध;
			हाल V4L2_SLICED_VPS:
				lcr[i] |= 9 << (4 * x);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (is_pal) अणु
		क्रम (x = 1, i = 0x424; i <= 0x434; i++, x++)
			cx18_av_ग_लिखो(cx, i, lcr[6 + x]);
	पूर्ण अन्यथा अणु
		क्रम (x = 1, i = 0x424; i <= 0x430; i++, x++)
			cx18_av_ग_लिखो(cx, i, lcr[9 + x]);
		क्रम (i = 0x431; i <= 0x434; i++)
			cx18_av_ग_लिखो(cx, i, 0);
	पूर्ण

	cx18_av_ग_लिखो(cx, 0x43c, 0x16);
	/* Should match vblank set in cx18_av_std_setup() */
	cx18_av_ग_लिखो(cx, 0x474, is_pal ? 38 : 26);
	वापस 0;
पूर्ण

पूर्णांक cx18_av_decode_vbi_line(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_decode_vbi_line *vbi)
अणु
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);
	काष्ठा cx18_av_state *state = &cx->av_state;
	काष्ठा vbi_anc_data *anc = (काष्ठा vbi_anc_data *)vbi->p;
	u8 *p;
	पूर्णांक did, sdid, l, err = 0;

	/*
	 * Check क्रम the ancillary data header क्रम sliced VBI
	 */
	अगर (anc->preamble[0] ||
			anc->preamble[1] != 0xff || anc->preamble[2] != 0xff ||
			(anc->did != sliced_vbi_did[0] &&
			 anc->did != sliced_vbi_did[1])) अणु
		vbi->line = vbi->type = 0;
		वापस 0;
	पूर्ण

	did = anc->did;
	sdid = anc->sdid & 0xf;
	l = anc->idid[0] & 0x3f;
	l += state->slicer_line_offset;
	p = anc->payload;

	/* Decode the SDID set by the slicer */
	चयन (sdid) अणु
	हाल 1:
		sdid = V4L2_SLICED_TELETEXT_B;
		अवरोध;
	हाल 4:
		sdid = V4L2_SLICED_WSS_625;
		अवरोध;
	हाल 6:
		sdid = V4L2_SLICED_CAPTION_525;
		err = !odd_parity(p[0]) || !odd_parity(p[1]);
		अवरोध;
	हाल 9:
		sdid = V4L2_SLICED_VPS;
		अगर (decode_vps(p, p) != 0)
			err = 1;
		अवरोध;
	शेष:
		sdid = 0;
		err = 1;
		अवरोध;
	पूर्ण

	vbi->type = err ? 0 : sdid;
	vbi->line = err ? 0 : l;
	vbi->is_second_field = err ? 0 : (did == sliced_vbi_did[1]);
	vbi->p = p;
	वापस 0;
पूर्ण
