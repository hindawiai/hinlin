<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश "dvb_filter.h"

अटल u32 freq[4] = अणु480, 441, 320, 0पूर्ण;

अटल अचिन्हित पूर्णांक ac3_bitrates[32] =
    अणु32,40,48,56,64,80,96,112,128,160,192,224,256,320,384,448,512,576,640,
     0,0,0,0,0,0,0,0,0,0,0,0,0पूर्ण;

अटल u32 ac3_frames[3][32] =
    अणुअणु64,80,96,112,128,160,192,224,256,320,384,448,512,640,768,896,1024,
      1152,1280,0,0,0,0,0,0,0,0,0,0,0,0,0पूर्ण,
     अणु69,87,104,121,139,174,208,243,278,348,417,487,557,696,835,975,1114,
      1253,1393,0,0,0,0,0,0,0,0,0,0,0,0,0पूर्ण,
     अणु96,120,144,168,192,240,288,336,384,480,576,672,768,960,1152,1344,
      1536,1728,1920,0,0,0,0,0,0,0,0,0,0,0,0,0पूर्णपूर्ण;

पूर्णांक dvb_filter_get_ac3info(u8 *mbuf, पूर्णांक count, काष्ठा dvb_audio_info *ai, पूर्णांक pr)
अणु
	u8 *headr;
	पूर्णांक found = 0;
	पूर्णांक c = 0;
	u8 frame = 0;
	पूर्णांक fr = 0;

	जबतक ( !found  && c < count)अणु
		u8 *b = mbuf+c;

		अगर ( b[0] == 0x0b &&  b[1] == 0x77 )
			found = 1;
		अन्यथा अणु
			c++;
		पूर्ण
	पूर्ण

	अगर (!found) वापस -1;
	अगर (pr)
		prपूर्णांकk(KERN_DEBUG "Audiostream: AC3");

	ai->off = c;
	अगर (c+5 >= count) वापस -1;

	ai->layer = 0;  // 0 क्रम AC3
	headr = mbuf+c+2;

	frame = (headr[2]&0x3f);
	ai->bit_rate = ac3_bitrates[frame >> 1]*1000;

	अगर (pr)
		prपूर्णांकk(KERN_CONT "  BRate: %d kb/s", (पूर्णांक) ai->bit_rate/1000);

	ai->frequency = (headr[2] & 0xc0 ) >> 6;
	fr = (headr[2] & 0xc0 ) >> 6;
	ai->frequency = freq[fr]*100;
	अगर (pr)
		prपूर्णांकk(KERN_CONT "  Freq: %d Hz\n", (पूर्णांक) ai->frequency);

	ai->framesize = ac3_frames[fr][frame >> 1];
	अगर ((frame & 1) &&  (fr == 1)) ai->framesize++;
	ai->framesize = ai->framesize << 1;
	अगर (pr)
		prपूर्णांकk(KERN_DEBUG "  Framesize %d\n", (पूर्णांक) ai->framesize);

	वापस 0;
पूर्ण

व्योम dvb_filter_pes2ts_init(काष्ठा dvb_filter_pes2ts *p2ts, अचिन्हित लघु pid,
			    dvb_filter_pes2ts_cb_t *cb, व्योम *priv)
अणु
	अचिन्हित अक्षर *buf=p2ts->buf;

	buf[0]=0x47;
	buf[1]=(pid>>8);
	buf[2]=pid&0xff;
	p2ts->cc=0;
	p2ts->cb=cb;
	p2ts->priv=priv;
पूर्ण

पूर्णांक dvb_filter_pes2ts(काष्ठा dvb_filter_pes2ts *p2ts, अचिन्हित अक्षर *pes,
		      पूर्णांक len, पूर्णांक payload_start)
अणु
	अचिन्हित अक्षर *buf=p2ts->buf;
	पूर्णांक ret=0, rest;

	//len=6+((pes[4]<<8)|pes[5]);

	अगर (payload_start)
		buf[1]|=0x40;
	अन्यथा
		buf[1]&=~0x40;
	जबतक (len>=184) अणु
		buf[3]=0x10|((p2ts->cc++)&0x0f);
		स_नकल(buf+4, pes, 184);
		अगर ((ret=p2ts->cb(p2ts->priv, buf)))
			वापस ret;
		len-=184; pes+=184;
		buf[1]&=~0x40;
	पूर्ण
	अगर (!len)
		वापस 0;
	buf[3]=0x30|((p2ts->cc++)&0x0f);
	rest=183-len;
	अगर (rest) अणु
		buf[5]=0x00;
		अगर (rest-1)
			स_रखो(buf+6, 0xff, rest-1);
	पूर्ण
	buf[4]=rest;
	स_नकल(buf+5+rest, pes, len);
	वापस p2ts->cb(p2ts->priv, buf);
पूर्ण
