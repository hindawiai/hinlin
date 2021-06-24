<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-vbi-gen.c - vbi generator support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/माला.स>
#समावेश <linux/videodev2.h>

#समावेश "vivid-vbi-gen.h"

अटल व्योम wss_insert(u8 *wss, u32 val, अचिन्हित size)
अणु
	जबतक (size--)
		*wss++ = (val & (1 << size)) ? 0xc0 : 0x10;
पूर्ण

अटल व्योम vivid_vbi_gen_wss_raw(स्थिर काष्ठा v4l2_sliced_vbi_data *data,
		u8 *buf, अचिन्हित sampling_rate)
अणु
	स्थिर अचिन्हित rate = 5000000;	/* WSS has a 5 MHz transmission rate */
	u8 wss[29 + 24 + 24 + 24 + 18 + 18] = अणु 0 पूर्ण;
	स्थिर अचिन्हित zero = 0x07;
	स्थिर अचिन्हित one = 0x38;
	अचिन्हित bit = 0;
	u16 wss_data;
	पूर्णांक i;

	wss_insert(wss + bit, 0x1f1c71c7, 29); bit += 29;
	wss_insert(wss + bit, 0x1e3c1f, 24); bit += 24;

	wss_data = (data->data[1] << 8) | data->data[0];
	क्रम (i = 0; i <= 13; i++, bit += 6)
		wss_insert(wss + bit, (wss_data & (1 << i)) ? one : zero, 6);

	क्रम (i = 0, bit = 0; bit < माप(wss); bit++) अणु
		अचिन्हित n = ((bit + 1) * sampling_rate) / rate;

		जबतक (i < n)
			buf[i++] = wss[bit];
	पूर्ण
पूर्ण

अटल व्योम vivid_vbi_gen_teletext_raw(स्थिर काष्ठा v4l2_sliced_vbi_data *data,
		u8 *buf, अचिन्हित sampling_rate)
अणु
	स्थिर अचिन्हित rate = 6937500 / 10;	/* Teletext has a 6.9375 MHz transmission rate */
	u8 teletext[45] = अणु 0x55, 0x55, 0x27 पूर्ण;
	अचिन्हित bit = 0;
	पूर्णांक i;

	स_नकल(teletext + 3, data->data, माप(teletext) - 3);
	/* prevents 32 bit overflow */
	sampling_rate /= 10;

	क्रम (i = 0, bit = 0; bit < माप(teletext) * 8; bit++) अणु
		अचिन्हित n = ((bit + 1) * sampling_rate) / rate;
		u8 val = (teletext[bit / 8] & (1 << (bit & 7))) ? 0xc0 : 0x10;

		जबतक (i < n)
			buf[i++] = val;
	पूर्ण
पूर्ण

अटल व्योम cc_insert(u8 *cc, u8 ch)
अणु
	अचिन्हित tot = 0;
	अचिन्हित i;

	क्रम (i = 0; i < 7; i++) अणु
		cc[2 * i] = cc[2 * i + 1] = (ch & (1 << i)) ? 1 : 0;
		tot += cc[2 * i];
	पूर्ण
	cc[14] = cc[15] = !(tot & 1);
पूर्ण

#घोषणा CC_PREAMBLE_BITS (14 + 4 + 2)

अटल व्योम vivid_vbi_gen_cc_raw(स्थिर काष्ठा v4l2_sliced_vbi_data *data,
		u8 *buf, अचिन्हित sampling_rate)
अणु
	स्थिर अचिन्हित rate = 1000000;	/* CC has a 1 MHz transmission rate */

	u8 cc[CC_PREAMBLE_BITS + 2 * 16] = अणु
		/* Clock run-in: 7 cycles */
		0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
		/* 2 cycles of 0 */
		0, 0, 0, 0,
		/* Start bit of 1 (each bit is two cycles) */
		1, 1
	पूर्ण;
	अचिन्हित bit, i;

	cc_insert(cc + CC_PREAMBLE_BITS, data->data[0]);
	cc_insert(cc + CC_PREAMBLE_BITS + 16, data->data[1]);

	क्रम (i = 0, bit = 0; bit < माप(cc); bit++) अणु
		अचिन्हित n = ((bit + 1) * sampling_rate) / rate;

		जबतक (i < n)
			buf[i++] = cc[bit] ? 0xc0 : 0x10;
	पूर्ण
पूर्ण

व्योम vivid_vbi_gen_raw(स्थिर काष्ठा vivid_vbi_gen_data *vbi,
		स्थिर काष्ठा v4l2_vbi_क्रमmat *vbi_fmt, u8 *buf)
अणु
	अचिन्हित idx;

	क्रम (idx = 0; idx < 25; idx++) अणु
		स्थिर काष्ठा v4l2_sliced_vbi_data *data = vbi->data + idx;
		अचिन्हित start_2nd_field;
		अचिन्हित line = data->line;
		u8 *linebuf = buf;

		start_2nd_field = (data->id & V4L2_SLICED_VBI_525) ? 263 : 313;
		अगर (data->field)
			line += start_2nd_field;
		line -= vbi_fmt->start[data->field];

		अगर (vbi_fmt->flags & V4L2_VBI_INTERLACED)
			linebuf += (line * 2 + data->field) *
				vbi_fmt->samples_per_line;
		अन्यथा
			linebuf += (line + data->field * vbi_fmt->count[0]) *
				vbi_fmt->samples_per_line;
		अगर (data->id == V4L2_SLICED_CAPTION_525)
			vivid_vbi_gen_cc_raw(data, linebuf, vbi_fmt->sampling_rate);
		अन्यथा अगर (data->id == V4L2_SLICED_WSS_625)
			vivid_vbi_gen_wss_raw(data, linebuf, vbi_fmt->sampling_rate);
		अन्यथा अगर (data->id == V4L2_SLICED_TELETEXT_B)
			vivid_vbi_gen_teletext_raw(data, linebuf, vbi_fmt->sampling_rate);
	पूर्ण
पूर्ण

अटल स्थिर u8 vivid_cc_sequence1[30] = अणु
	0x14, 0x20,	/* Resume Caption Loading */
	'H',  'e',
	'l',  'l',
	'o',  ' ',
	'w',  'o',
	'r',  'l',
	'd',  '!',
	0x14, 0x2f,	/* End of Caption */
पूर्ण;

अटल स्थिर u8 vivid_cc_sequence2[30] = अणु
	0x14, 0x20,	/* Resume Caption Loading */
	'C',  'l',
	'o',  's',
	'e',  'd',
	' ',  'c',
	'a',  'p',
	't',  'i',
	'o',  'n',
	's',  ' ',
	't',  'e',
	's',  't',
	0x14, 0x2f,	/* End of Caption */
पूर्ण;

अटल u8 calc_parity(u8 val)
अणु
	अचिन्हित i;
	अचिन्हित tot = 0;

	क्रम (i = 0; i < 7; i++)
		tot += (val & (1 << i)) ? 1 : 0;
	वापस val | ((tot & 1) ? 0 : 0x80);
पूर्ण

अटल व्योम vivid_vbi_gen_set_समय_of_day(u8 *packet)
अणु
	काष्ठा पंचांग पंचांग;
	u8 checksum, i;

	समय64_to_पंचांग(kसमय_get_real_seconds(), 0, &पंचांग);
	packet[0] = calc_parity(0x07);
	packet[1] = calc_parity(0x01);
	packet[2] = calc_parity(0x40 | पंचांग.पंचांग_min);
	packet[3] = calc_parity(0x40 | पंचांग.पंचांग_hour);
	packet[4] = calc_parity(0x40 | पंचांग.पंचांग_mday);
	अगर (पंचांग.पंचांग_mday == 1 && पंचांग.पंचांग_mon == 2 &&
	    sys_tz.tz_minuteswest > पंचांग.पंचांग_min + पंचांग.पंचांग_hour * 60)
		packet[4] = calc_parity(0x60 | पंचांग.पंचांग_mday);
	packet[5] = calc_parity(0x40 | (1 + पंचांग.पंचांग_mon));
	packet[6] = calc_parity(0x40 | (1 + पंचांग.पंचांग_wday));
	packet[7] = calc_parity(0x40 | ((पंचांग.पंचांग_year - 90) & 0x3f));
	packet[8] = calc_parity(0x0f);
	क्रम (checksum = i = 0; i <= 8; i++)
		checksum += packet[i] & 0x7f;
	packet[9] = calc_parity(0x100 - checksum);
	checksum = 0;
	packet[10] = calc_parity(0x07);
	packet[11] = calc_parity(0x04);
	अगर (sys_tz.tz_minuteswest >= 0)
		packet[12] = calc_parity(0x40 | ((sys_tz.tz_minuteswest / 60) & 0x1f));
	अन्यथा
		packet[12] = calc_parity(0x40 | ((24 + sys_tz.tz_minuteswest / 60) & 0x1f));
	packet[13] = calc_parity(0);
	packet[14] = calc_parity(0x0f);
	क्रम (checksum = 0, i = 10; i <= 14; i++)
		checksum += packet[i] & 0x7f;
	packet[15] = calc_parity(0x100 - checksum);
पूर्ण

अटल स्थिर u8 hamming[16] = अणु
	0x15, 0x02, 0x49, 0x5e, 0x64, 0x73, 0x38, 0x2f,
	0xd0, 0xc7, 0x8c, 0x9b, 0xa1, 0xb6, 0xfd, 0xea
पूर्ण;

अटल व्योम vivid_vbi_gen_teletext(u8 *packet, अचिन्हित line, अचिन्हित frame)
अणु
	अचिन्हित offset = 2;
	अचिन्हित i;

	packet[0] = hamming[1 + ((line & 1) << 3)];
	packet[1] = hamming[line >> 1];
	स_रखो(packet + 2, 0x20, 40);
	अगर (line == 0) अणु
		/* subcode */
		packet[2] = hamming[frame % 10];
		packet[3] = hamming[frame / 10];
		packet[4] = hamming[0];
		packet[5] = hamming[0];
		packet[6] = hamming[0];
		packet[7] = hamming[0];
		packet[8] = hamming[0];
		packet[9] = hamming[1];
		offset = 10;
	पूर्ण
	packet += offset;
	स_नकल(packet, "Page: 100 Row: 10", 17);
	packet[7] = '0' + frame / 10;
	packet[8] = '0' + frame % 10;
	packet[15] = '0' + line / 10;
	packet[16] = '0' + line % 10;
	क्रम (i = 0; i < 42 - offset; i++)
		packet[i] = calc_parity(packet[i]);
पूर्ण

व्योम vivid_vbi_gen_sliced(काष्ठा vivid_vbi_gen_data *vbi,
		bool is_60hz, अचिन्हित seqnr)
अणु
	काष्ठा v4l2_sliced_vbi_data *data0 = vbi->data;
	काष्ठा v4l2_sliced_vbi_data *data1 = vbi->data + 1;
	अचिन्हित frame = seqnr % 60;

	स_रखो(vbi->data, 0, माप(vbi->data));

	अगर (!is_60hz) अणु
		अचिन्हित i;

		क्रम (i = 0; i <= 11; i++) अणु
			data0->id = V4L2_SLICED_TELETEXT_B;
			data0->line = 7 + i;
			vivid_vbi_gen_teletext(data0->data, i, frame);
			data0++;
		पूर्ण
		data0->id = V4L2_SLICED_WSS_625;
		data0->line = 23;
		/* 4x3 video aspect ratio */
		data0->data[0] = 0x08;
		data0++;
		क्रम (i = 0; i <= 11; i++) अणु
			data0->id = V4L2_SLICED_TELETEXT_B;
			data0->field = 1;
			data0->line = 7 + i;
			vivid_vbi_gen_teletext(data0->data, 12 + i, frame);
			data0++;
		पूर्ण
		वापस;
	पूर्ण

	data0->id = V4L2_SLICED_CAPTION_525;
	data0->line = 21;
	data1->id = V4L2_SLICED_CAPTION_525;
	data1->field = 1;
	data1->line = 21;

	अगर (frame < 15) अणु
		data0->data[0] = calc_parity(vivid_cc_sequence1[2 * frame]);
		data0->data[1] = calc_parity(vivid_cc_sequence1[2 * frame + 1]);
	पूर्ण अन्यथा अगर (frame >= 30 && frame < 45) अणु
		frame -= 30;
		data0->data[0] = calc_parity(vivid_cc_sequence2[2 * frame]);
		data0->data[1] = calc_parity(vivid_cc_sequence2[2 * frame + 1]);
	पूर्ण अन्यथा अणु
		data0->data[0] = calc_parity(0);
		data0->data[1] = calc_parity(0);
	पूर्ण

	frame = seqnr % (30 * 60);
	चयन (frame) अणु
	हाल 0:
		vivid_vbi_gen_set_समय_of_day(vbi->समय_of_day_packet);
		fallthrough;
	हाल 1 ... 7:
		data1->data[0] = vbi->समय_of_day_packet[frame * 2];
		data1->data[1] = vbi->समय_of_day_packet[frame * 2 + 1];
		अवरोध;
	शेष:
		data1->data[0] = calc_parity(0);
		data1->data[1] = calc_parity(0);
		अवरोध;
	पूर्ण
पूर्ण
