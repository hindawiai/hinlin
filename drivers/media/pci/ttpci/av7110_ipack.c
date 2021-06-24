<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "dvb_filter.h"
#समावेश "av7110_ipack.h"
#समावेश <linux/माला.स>	/* क्रम स_नकल() */
#समावेश <linux/vदो_स्मृति.h>


व्योम av7110_ipack_reset(काष्ठा ipack *p)
अणु
	p->found = 0;
	p->cid = 0;
	p->plength = 0;
	p->flag1 = 0;
	p->flag2 = 0;
	p->hlength = 0;
	p->mpeg = 0;
	p->check = 0;
	p->which = 0;
	p->करोne = 0;
	p->count = 0;
पूर्ण


पूर्णांक av7110_ipack_init(काष्ठा ipack *p, पूर्णांक size,
		      व्योम (*func)(u8 *buf, पूर्णांक size, व्योम *priv))
अणु
	अगर (!(p->buf = vदो_स्मृति(size))) अणु
		prपूर्णांकk(KERN_WARNING "Couldn't allocate memory for ipack\n");
		वापस -ENOMEM;
	पूर्ण
	p->size = size;
	p->func = func;
	p->repack_subids = 0;
	av7110_ipack_reset(p);
	वापस 0;
पूर्ण


व्योम av7110_ipack_मुक्त(काष्ठा ipack *p)
अणु
	vमुक्त(p->buf);
पूर्ण


अटल व्योम send_ipack(काष्ठा ipack *p)
अणु
	पूर्णांक off;
	काष्ठा dvb_audio_info ai;
	पूर्णांक ac3_off = 0;
	पूर्णांक streamid = 0;
	पूर्णांक nframes = 0;
	पूर्णांक f = 0;

	चयन (p->mpeg) अणु
	हाल 2:
		अगर (p->count < 10)
			वापस;
		p->buf[3] = p->cid;
		p->buf[4] = (u8)(((p->count - 6) & 0xff00) >> 8);
		p->buf[5] = (u8)((p->count - 6) & 0x00ff);
		अगर (p->repack_subids && p->cid == PRIVATE_STREAM1) अणु
			off = 9 + p->buf[8];
			streamid = p->buf[off];
			अगर ((streamid & 0xf8) == 0x80) अणु
				ai.off = 0;
				ac3_off = ((p->buf[off + 2] << 8)|
					   p->buf[off + 3]);
				अगर (ac3_off < p->count)
					f = dvb_filter_get_ac3info(p->buf + off + 3 + ac3_off,
								   p->count - ac3_off, &ai, 0);
				अगर (!f) अणु
					nframes = (p->count - off - 3 - ac3_off) /
						ai.framesize + 1;
					p->buf[off + 2] = (ac3_off >> 8) & 0xff;
					p->buf[off + 3] = (ac3_off) & 0xff;
					p->buf[off + 1] = nframes;
					ac3_off +=  nframes * ai.framesize - p->count;
				पूर्ण
			पूर्ण
		पूर्ण
		p->func(p->buf, p->count, p->data);

		p->buf[6] = 0x80;
		p->buf[7] = 0x00;
		p->buf[8] = 0x00;
		p->count = 9;
		अगर (p->repack_subids && p->cid == PRIVATE_STREAM1
		    && (streamid & 0xf8) == 0x80) अणु
			p->count += 4;
			p->buf[9] = streamid;
			p->buf[10] = (ac3_off >> 8) & 0xff;
			p->buf[11] = (ac3_off) & 0xff;
			p->buf[12] = 0;
		पूर्ण
		अवरोध;

	हाल 1:
		अगर (p->count < 8)
			वापस;
		p->buf[3] = p->cid;
		p->buf[4] = (u8)(((p->count - 6) & 0xff00) >> 8);
		p->buf[5] = (u8)((p->count - 6) & 0x00ff);
		p->func(p->buf, p->count, p->data);

		p->buf[6] = 0x0f;
		p->count = 7;
		अवरोध;
	पूर्ण
पूर्ण


व्योम av7110_ipack_flush(काष्ठा ipack *p)
अणु
	अगर (p->plength != MMAX_PLENGTH - 6 || p->found <= 6)
		वापस;
	p->plength = p->found - 6;
	p->found = 0;
	send_ipack(p);
	av7110_ipack_reset(p);
पूर्ण


अटल व्योम ग_लिखो_ipack(काष्ठा ipack *p, स्थिर u8 *data, पूर्णांक count)
अणु
	u8 headr[3] = अणु 0x00, 0x00, 0x01 पूर्ण;

	अगर (p->count < 6) अणु
		स_नकल(p->buf, headr, 3);
		p->count = 6;
	पूर्ण

	अगर (p->count + count < p->size)अणु
		स_नकल(p->buf+p->count, data, count);
		p->count += count;
	पूर्ण अन्यथा अणु
		पूर्णांक rest = p->size - p->count;
		स_नकल(p->buf+p->count, data, rest);
		p->count += rest;
		send_ipack(p);
		अगर (count - rest > 0)
			ग_लिखो_ipack(p, data + rest, count - rest);
	पूर्ण
पूर्ण


पूर्णांक av7110_ipack_instant_repack (स्थिर u8 *buf, पूर्णांक count, काष्ठा ipack *p)
अणु
	पूर्णांक l;
	पूर्णांक c = 0;

	जबतक (c < count && (p->mpeg == 0 ||
			     (p->mpeg == 1 && p->found < 7) ||
			     (p->mpeg == 2 && p->found < 9))
	       &&  (p->found < 5 || !p->करोne)) अणु
		चयन (p->found) अणु
		हाल 0:
		हाल 1:
			अगर (buf[c] == 0x00)
				p->found++;
			अन्यथा
				p->found = 0;
			c++;
			अवरोध;
		हाल 2:
			अगर (buf[c] == 0x01)
				p->found++;
			अन्यथा अगर (buf[c] == 0)
				p->found = 2;
			अन्यथा
				p->found = 0;
			c++;
			अवरोध;
		हाल 3:
			p->cid = 0;
			चयन (buf[c]) अणु
			हाल PROG_STREAM_MAP:
			हाल PRIVATE_STREAM2:
			हाल PROG_STREAM_सूची:
			हाल ECM_STREAM     :
			हाल EMM_STREAM     :
			हाल PADDING_STREAM :
			हाल DSM_CC_STREAM  :
			हाल ISO13522_STREAM:
				p->करोne = 1;
				fallthrough;
			हाल PRIVATE_STREAM1:
			हाल VIDEO_STREAM_S ... VIDEO_STREAM_E:
			हाल AUDIO_STREAM_S ... AUDIO_STREAM_E:
				p->found++;
				p->cid = buf[c];
				c++;
				अवरोध;
			शेष:
				p->found = 0;
				अवरोध;
			पूर्ण
			अवरोध;

		हाल 4:
			अगर (count-c > 1) अणु
				p->plen[0] = buf[c];
				c++;
				p->plen[1] = buf[c];
				c++;
				p->found += 2;
				p->plength = (p->plen[0] << 8) | p->plen[1];
			पूर्ण अन्यथा अणु
				p->plen[0] = buf[c];
				p->found++;
				वापस count;
			पूर्ण
			अवरोध;
		हाल 5:
			p->plen[1] = buf[c];
			c++;
			p->found++;
			p->plength = (p->plen[0] << 8) | p->plen[1];
			अवरोध;
		हाल 6:
			अगर (!p->करोne) अणु
				p->flag1 = buf[c];
				c++;
				p->found++;
				अगर ((p->flag1 & 0xc0) == 0x80)
					p->mpeg = 2;
				अन्यथा अणु
					p->hlength = 0;
					p->which = 0;
					p->mpeg = 1;
					p->flag2 = 0;
				पूर्ण
			पूर्ण
			अवरोध;

		हाल 7:
			अगर (!p->करोne && p->mpeg == 2) अणु
				p->flag2 = buf[c];
				c++;
				p->found++;
			पूर्ण
			अवरोध;

		हाल 8:
			अगर (!p->करोne && p->mpeg == 2) अणु
				p->hlength = buf[c];
				c++;
				p->found++;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (c == count)
		वापस count;

	अगर (!p->plength)
		p->plength = MMAX_PLENGTH - 6;

	अगर (p->करोne || ((p->mpeg == 2 && p->found >= 9) ||
			(p->mpeg == 1 && p->found >= 7))) अणु
		चयन (p->cid) अणु
		हाल AUDIO_STREAM_S ... AUDIO_STREAM_E:
		हाल VIDEO_STREAM_S ... VIDEO_STREAM_E:
		हाल PRIVATE_STREAM1:
			अगर (p->mpeg == 2 && p->found == 9) अणु
				ग_लिखो_ipack(p, &p->flag1, 1);
				ग_लिखो_ipack(p, &p->flag2, 1);
				ग_लिखो_ipack(p, &p->hlength, 1);
			पूर्ण

			अगर (p->mpeg == 1 && p->found == 7)
				ग_लिखो_ipack(p, &p->flag1, 1);

			अगर (p->mpeg == 2 && (p->flag2 & PTS_ONLY) &&
			    p->found < 14) अणु
				जबतक (c < count && p->found < 14) अणु
					p->pts[p->found - 9] = buf[c];
					ग_लिखो_ipack(p, buf + c, 1);
					c++;
					p->found++;
				पूर्ण
				अगर (c == count)
					वापस count;
			पूर्ण

			अगर (p->mpeg == 1 && p->which < 2000) अणु

				अगर (p->found == 7) अणु
					p->check = p->flag1;
					p->hlength = 1;
				पूर्ण

				जबतक (!p->which && c < count &&
				       p->check == 0xff)अणु
					p->check = buf[c];
					ग_लिखो_ipack(p, buf + c, 1);
					c++;
					p->found++;
					p->hlength++;
				पूर्ण

				अगर (c == count)
					वापस count;

				अगर ((p->check & 0xc0) == 0x40 && !p->which) अणु
					p->check = buf[c];
					ग_लिखो_ipack(p, buf + c, 1);
					c++;
					p->found++;
					p->hlength++;

					p->which = 1;
					अगर (c == count)
						वापस count;
					p->check = buf[c];
					ग_लिखो_ipack(p, buf + c, 1);
					c++;
					p->found++;
					p->hlength++;
					p->which = 2;
					अगर (c == count)
						वापस count;
				पूर्ण

				अगर (p->which == 1) अणु
					p->check = buf[c];
					ग_लिखो_ipack(p, buf + c, 1);
					c++;
					p->found++;
					p->hlength++;
					p->which = 2;
					अगर (c == count)
						वापस count;
				पूर्ण

				अगर ((p->check & 0x30) && p->check != 0xff) अणु
					p->flag2 = (p->check & 0xf0) << 2;
					p->pts[0] = p->check;
					p->which = 3;
				पूर्ण

				अगर (c == count)
					वापस count;
				अगर (p->which > 2)अणु
					अगर ((p->flag2 & PTS_DTS_FLAGS) == PTS_ONLY) अणु
						जबतक (c < count && p->which < 7) अणु
							p->pts[p->which - 2] = buf[c];
							ग_लिखो_ipack(p, buf + c, 1);
							c++;
							p->found++;
							p->which++;
							p->hlength++;
						पूर्ण
						अगर (c == count)
							वापस count;
					पूर्ण अन्यथा अगर ((p->flag2 & PTS_DTS_FLAGS) == PTS_DTS) अणु
						जबतक (c < count && p->which < 12) अणु
							अगर (p->which < 7)
								p->pts[p->which - 2] = buf[c];
							ग_लिखो_ipack(p, buf + c, 1);
							c++;
							p->found++;
							p->which++;
							p->hlength++;
						पूर्ण
						अगर (c == count)
							वापस count;
					पूर्ण
					p->which = 2000;
				पूर्ण

			पूर्ण

			जबतक (c < count && p->found < p->plength + 6) अणु
				l = count - c;
				अगर (l + p->found > p->plength + 6)
					l = p->plength + 6 - p->found;
				ग_लिखो_ipack(p, buf + c, l);
				p->found += l;
				c += l;
			पूर्ण
			अवरोध;
		पूर्ण


		अगर (p->करोne) अणु
			अगर (p->found + count - c < p->plength + 6) अणु
				p->found += count - c;
				c = count;
			पूर्ण अन्यथा अणु
				c += p->plength + 6 - p->found;
				p->found = p->plength + 6;
			पूर्ण
		पूर्ण

		अगर (p->plength && p->found == p->plength + 6) अणु
			send_ipack(p);
			av7110_ipack_reset(p);
			अगर (c < count)
				av7110_ipack_instant_repack(buf + c, count - c, p);
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण
