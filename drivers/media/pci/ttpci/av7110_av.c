<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * av7110_av.c: audio and video MPEG decoder stuff
 *
 * Copyright (C) 1999-2002 Ralph  Metzler
 *                       & Marcus Metzler क्रम convergence पूर्णांकegrated media GmbH
 *
 * originally based on code by:
 * Copyright (C) 1998,1999 Christian Theiss <mistert@rz.fh-augsburg.de>
 *
 * the project's page is at https://linuxtv.org
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>

#समावेश "av7110.h"
#समावेश "av7110_hw.h"
#समावेश "av7110_av.h"
#समावेश "av7110_ipack.h"

/* MPEG-2 (ISO 13818 / H.222.0) stream types */
#घोषणा PROG_STREAM_MAP  0xBC
#घोषणा PRIVATE_STREAM1  0xBD
#घोषणा PADDING_STREAM	 0xBE
#घोषणा PRIVATE_STREAM2  0xBF
#घोषणा AUDIO_STREAM_S	 0xC0
#घोषणा AUDIO_STREAM_E	 0xDF
#घोषणा VIDEO_STREAM_S	 0xE0
#घोषणा VIDEO_STREAM_E	 0xEF
#घोषणा ECM_STREAM	 0xF0
#घोषणा EMM_STREAM	 0xF1
#घोषणा DSM_CC_STREAM	 0xF2
#घोषणा ISO13522_STREAM  0xF3
#घोषणा PROG_STREAM_सूची  0xFF

#घोषणा PTS_DTS_FLAGS	 0xC0

//pts_dts flags
#घोषणा PTS_ONLY	 0x80
#घोषणा PTS_DTS		 0xC0
#घोषणा TS_SIZE		 188
#घोषणा TRANS_ERROR	 0x80
#घोषणा PAY_START	 0x40
#घोषणा TRANS_PRIO	 0x20
#घोषणा PID_MASK_HI	 0x1F
//flags
#घोषणा TRANS_SCRMBL1	 0x80
#घोषणा TRANS_SCRMBL2	 0x40
#घोषणा ADAPT_FIELD	 0x20
#घोषणा PAYLOAD		 0x10
#घोषणा COUNT_MASK	 0x0F

// adaptation flags
#घोषणा DISCON_IND	 0x80
#घोषणा RAND_ACC_IND	 0x40
#घोषणा ES_PRI_IND	 0x20
#घोषणा PCR_FLAG	 0x10
#घोषणा OPCR_FLAG	 0x08
#घोषणा SPLICE_FLAG	 0x04
#घोषणा TRANS_PRIV	 0x02
#घोषणा ADAP_EXT_FLAG	 0x01

// adaptation extension flags
#घोषणा LTW_FLAG	 0x80
#घोषणा PIECE_RATE	 0x40
#घोषणा SEAM_SPLICE	 0x20


अटल व्योम p_to_t(u8 स्थिर *buf, दीर्घ पूर्णांक length, u16 pid,
		   u8 *counter, काष्ठा dvb_demux_feed *feed);
अटल पूर्णांक ग_लिखो_ts_to_decoder(काष्ठा av7110 *av7110, पूर्णांक type, स्थिर u8 *buf, माप_प्रकार len);


पूर्णांक av7110_record_cb(काष्ठा dvb_filter_pes2ts *p2t, u8 *buf, माप_प्रकार len)
अणु
	काष्ठा dvb_demux_feed *dvbdmxfeed = (काष्ठा dvb_demux_feed *) p2t->priv;

	अगर (!(dvbdmxfeed->ts_type & TS_PACKET))
		वापस 0;
	अगर (buf[3] == 0xe0)	 // video PES करो not have a length in TS
		buf[4] = buf[5] = 0;
	अगर (dvbdmxfeed->ts_type & TS_PAYLOAD_ONLY)
		वापस dvbdmxfeed->cb.ts(buf, len, शून्य, 0,
					 &dvbdmxfeed->feed.ts, शून्य);
	अन्यथा
		वापस dvb_filter_pes2ts(p2t, buf, len, 1);
पूर्ण

अटल पूर्णांक dvb_filter_pes2ts_cb(व्योम *priv, अचिन्हित अक्षर *data)
अणु
	काष्ठा dvb_demux_feed *dvbdmxfeed = (काष्ठा dvb_demux_feed *) priv;

	dvbdmxfeed->cb.ts(data, 188, शून्य, 0,
			  &dvbdmxfeed->feed.ts, शून्य);
	वापस 0;
पूर्ण

पूर्णांक av7110_av_start_record(काष्ठा av7110 *av7110, पूर्णांक av,
			   काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	पूर्णांक ret = 0;
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;

	dprपूर्णांकk(2, "av7110:%p, , dvb_demux_feed:%p\n", av7110, dvbdmxfeed);

	अगर (av7110->playing || (av7110->rec_mode & av))
		वापस -EBUSY;
	av7110_fw_cmd(av7110, COMTYPE_REC_PLAY, __Stop, 0);
	dvbdmx->recording = 1;
	av7110->rec_mode |= av;

	चयन (av7110->rec_mode) अणु
	हाल RP_AUDIO:
		dvb_filter_pes2ts_init(&av7110->p2t[0],
				       dvbdmx->pesfilter[0]->pid,
				       dvb_filter_pes2ts_cb,
				       (व्योम *) dvbdmx->pesfilter[0]);
		ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY, __Record, 2, AudioPES, 0);
		अवरोध;

	हाल RP_VIDEO:
		dvb_filter_pes2ts_init(&av7110->p2t[1],
				       dvbdmx->pesfilter[1]->pid,
				       dvb_filter_pes2ts_cb,
				       (व्योम *) dvbdmx->pesfilter[1]);
		ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY, __Record, 2, VideoPES, 0);
		अवरोध;

	हाल RP_AV:
		dvb_filter_pes2ts_init(&av7110->p2t[0],
				       dvbdmx->pesfilter[0]->pid,
				       dvb_filter_pes2ts_cb,
				       (व्योम *) dvbdmx->pesfilter[0]);
		dvb_filter_pes2ts_init(&av7110->p2t[1],
				       dvbdmx->pesfilter[1]->pid,
				       dvb_filter_pes2ts_cb,
				       (व्योम *) dvbdmx->pesfilter[1]);
		ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY, __Record, 2, AV_PES, 0);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक av7110_av_start_play(काष्ठा av7110 *av7110, पूर्णांक av)
अणु
	पूर्णांक ret = 0;
	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	अगर (av7110->rec_mode)
		वापस -EBUSY;
	अगर (av7110->playing & av)
		वापस -EBUSY;

	av7110_fw_cmd(av7110, COMTYPE_REC_PLAY, __Stop, 0);

	अगर (av7110->playing == RP_NONE) अणु
		av7110_ipack_reset(&av7110->ipack[0]);
		av7110_ipack_reset(&av7110->ipack[1]);
	पूर्ण

	av7110->playing |= av;
	चयन (av7110->playing) अणु
	हाल RP_AUDIO:
		ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY, __Play, 2, AudioPES, 0);
		अवरोध;
	हाल RP_VIDEO:
		ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY, __Play, 2, VideoPES, 0);
		av7110->sinfo = 0;
		अवरोध;
	हाल RP_AV:
		av7110->sinfo = 0;
		ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY, __Play, 2, AV_PES, 0);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक av7110_av_stop(काष्ठा av7110 *av7110, पूर्णांक av)
अणु
	पूर्णांक ret = 0;
	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	अगर (!(av7110->playing & av) && !(av7110->rec_mode & av))
		वापस 0;
	av7110_fw_cmd(av7110, COMTYPE_REC_PLAY, __Stop, 0);
	अगर (av7110->playing) अणु
		av7110->playing &= ~av;
		चयन (av7110->playing) अणु
		हाल RP_AUDIO:
			ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY, __Play, 2, AudioPES, 0);
			अवरोध;
		हाल RP_VIDEO:
			ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY, __Play, 2, VideoPES, 0);
			अवरोध;
		हाल RP_NONE:
			ret = av7110_set_vidmode(av7110, av7110->vidmode);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		av7110->rec_mode &= ~av;
		चयन (av7110->rec_mode) अणु
		हाल RP_AUDIO:
			ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY, __Record, 2, AudioPES, 0);
			अवरोध;
		हाल RP_VIDEO:
			ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY, __Record, 2, VideoPES, 0);
			अवरोध;
		हाल RP_NONE:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण


पूर्णांक av7110_pes_play(व्योम *dest, काष्ठा dvb_ringbuffer *buf, पूर्णांक dlen)
अणु
	पूर्णांक len;
	u32 sync;
	u16 blen;

	अगर (!dlen) अणु
		wake_up(&buf->queue);
		वापस -1;
	पूर्ण
	जबतक (1) अणु
		len = dvb_ringbuffer_avail(buf);
		अगर (len < 6) अणु
			wake_up(&buf->queue);
			वापस -1;
		पूर्ण
		sync =  DVB_RINGBUFFER_PEEK(buf, 0) << 24;
		sync |= DVB_RINGBUFFER_PEEK(buf, 1) << 16;
		sync |= DVB_RINGBUFFER_PEEK(buf, 2) << 8;
		sync |= DVB_RINGBUFFER_PEEK(buf, 3);

		अगर (((sync &~ 0x0f) == 0x000001e0) ||
		    ((sync &~ 0x1f) == 0x000001c0) ||
		    (sync == 0x000001bd))
			अवरोध;
		prपूर्णांकk("resync\n");
		DVB_RINGBUFFER_SKIP(buf, 1);
	पूर्ण
	blen =  DVB_RINGBUFFER_PEEK(buf, 4) << 8;
	blen |= DVB_RINGBUFFER_PEEK(buf, 5);
	blen += 6;
	अगर (len < blen || blen > dlen) अणु
		//prपूर्णांकk("buffer empty - avail %d blen %u dlen %d\n", len, blen, dlen);
		wake_up(&buf->queue);
		वापस -1;
	पूर्ण

	dvb_ringbuffer_पढ़ो(buf, dest, (माप_प्रकार) blen);

	dprपूर्णांकk(2, "pread=0x%08lx, pwrite=0x%08lx\n",
	       (अचिन्हित दीर्घ) buf->pपढ़ो, (अचिन्हित दीर्घ) buf->pग_लिखो);
	wake_up(&buf->queue);
	वापस blen;
पूर्ण


पूर्णांक av7110_set_volume(काष्ठा av7110 *av7110, अचिन्हित पूर्णांक volleft,
		      अचिन्हित पूर्णांक volright)
अणु
	अचिन्हित पूर्णांक vol, val, balance = 0;
	पूर्णांक err;

	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	av7110->mixer.volume_left = volleft;
	av7110->mixer.volume_right = volright;

	चयन (av7110->adac_type) अणु
	हाल DVB_ADAC_TI:
		volleft = (volleft * 256) / 1036;
		volright = (volright * 256) / 1036;
		अगर (volleft > 0x3f)
			volleft = 0x3f;
		अगर (volright > 0x3f)
			volright = 0x3f;
		अगर ((err = SendDAC(av7110, 3, 0x80 + volleft)))
			वापस err;
		वापस SendDAC(av7110, 4, volright);

	हाल DVB_ADAC_CRYSTAL:
		volleft = 127 - volleft / 2;
		volright = 127 - volright / 2;
		i2c_ग_लिखोreg(av7110, 0x20, 0x03, volleft);
		i2c_ग_लिखोreg(av7110, 0x20, 0x04, volright);
		वापस 0;

	हाल DVB_ADAC_MSP34x0:
		vol  = (volleft > volright) ? volleft : volright;
		val	= (vol * 0x73 / 255) << 8;
		अगर (vol > 0)
		       balance = ((volright - volleft) * 127) / vol;
		msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0001, balance << 8);
		msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0000, val); /* loudspeaker */
		msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0006, val); /* headphonesr */
		वापस 0;

	हाल DVB_ADAC_MSP34x5:
		vol = (volleft > volright) ? volleft : volright;
		val = (vol * 0x73 / 255) << 8;
		अगर (vol > 0)
			balance = ((volright - volleft) * 127) / vol;
		msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0001, balance << 8);
		msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0000, val); /* loudspeaker */
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक av7110_set_vidmode(काष्ठा av7110 *av7110, क्रमागत av7110_video_mode mode)
अणु
	पूर्णांक ret;
	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	ret = av7110_fw_cmd(av7110, COMTYPE_ENCODER, LoadVidCode, 1, mode);

	अगर (!ret && !av7110->playing) अणु
		ret = ChangePIDs(av7110, av7110->pids[DMX_PES_VIDEO],
			   av7110->pids[DMX_PES_AUDIO],
			   av7110->pids[DMX_PES_TELETEXT],
			   0, av7110->pids[DMX_PES_PCR]);
		अगर (!ret)
			ret = av7110_fw_cmd(av7110, COMTYPE_PIDFILTER, Scan, 0);
	पूर्ण
	वापस ret;
पूर्ण


अटल क्रमागत av7110_video_mode sw2mode[16] = अणु
	AV7110_VIDEO_MODE_PAL, AV7110_VIDEO_MODE_NTSC,
	AV7110_VIDEO_MODE_NTSC, AV7110_VIDEO_MODE_PAL,
	AV7110_VIDEO_MODE_NTSC, AV7110_VIDEO_MODE_NTSC,
	AV7110_VIDEO_MODE_PAL, AV7110_VIDEO_MODE_NTSC,
	AV7110_VIDEO_MODE_PAL, AV7110_VIDEO_MODE_PAL,
	AV7110_VIDEO_MODE_PAL, AV7110_VIDEO_MODE_PAL,
	AV7110_VIDEO_MODE_PAL, AV7110_VIDEO_MODE_PAL,
	AV7110_VIDEO_MODE_PAL, AV7110_VIDEO_MODE_PAL,
पूर्ण;

अटल पूर्णांक get_video_क्रमmat(काष्ठा av7110 *av7110, u8 *buf, पूर्णांक count)
अणु
	पूर्णांक i;
	पूर्णांक hsize, vsize;
	पूर्णांक sw;
	u8 *p;
	पूर्णांक ret = 0;

	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	अगर (av7110->sinfo)
		वापस 0;
	क्रम (i = 7; i < count - 10; i++) अणु
		p = buf + i;
		अगर (p[0] || p[1] || p[2] != 0x01 || p[3] != 0xb3)
			जारी;
		p += 4;
		hsize = ((p[1] &0xF0) >> 4) | (p[0] << 4);
		vsize = ((p[1] &0x0F) << 8) | (p[2]);
		sw = (p[3] & 0x0F);
		ret = av7110_set_vidmode(av7110, sw2mode[sw]);
		अगर (!ret) अणु
			dprपूर्णांकk(2, "playback %dx%d fr=%d\n", hsize, vsize, sw);
			av7110->sinfo = 1;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण


/****************************************************************************
 * I/O buffer management and control
 ****************************************************************************/

अटल अंतरभूत दीर्घ aux_ring_buffer_ग_लिखो(काष्ठा dvb_ringbuffer *rbuf,
					 स्थिर u8 *buf, अचिन्हित दीर्घ count)
अणु
	अचिन्हित दीर्घ toकरो = count;
	पूर्णांक मुक्त;

	जबतक (toकरो > 0) अणु
		अगर (dvb_ringbuffer_मुक्त(rbuf) < 2048) अणु
			अगर (रुको_event_पूर्णांकerruptible(rbuf->queue,
						     (dvb_ringbuffer_मुक्त(rbuf) >= 2048)))
				वापस count - toकरो;
		पूर्ण
		मुक्त = dvb_ringbuffer_मुक्त(rbuf);
		अगर (मुक्त > toकरो)
			मुक्त = toकरो;
		dvb_ringbuffer_ग_लिखो(rbuf, buf, मुक्त);
		toकरो -= मुक्त;
		buf += मुक्त;
	पूर्ण

	वापस count - toकरो;
पूर्ण

अटल व्योम play_video_cb(u8 *buf, पूर्णांक count, व्योम *priv)
अणु
	काष्ठा av7110 *av7110 = (काष्ठा av7110 *) priv;
	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	अगर ((buf[3] & 0xe0) == 0xe0) अणु
		get_video_क्रमmat(av7110, buf, count);
		aux_ring_buffer_ग_लिखो(&av7110->avout, buf, count);
	पूर्ण अन्यथा
		aux_ring_buffer_ग_लिखो(&av7110->aout, buf, count);
पूर्ण

अटल व्योम play_audio_cb(u8 *buf, पूर्णांक count, व्योम *priv)
अणु
	काष्ठा av7110 *av7110 = (काष्ठा av7110 *) priv;
	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	aux_ring_buffer_ग_लिखो(&av7110->aout, buf, count);
पूर्ण


#घोषणा FREE_COND_TS (dvb_ringbuffer_मुक्त(rb) >= 4096)

अटल sमाप_प्रकार ts_play(काष्ठा av7110 *av7110, स्थिर अक्षर __user *buf,
		       अचिन्हित दीर्घ count, पूर्णांक nonblock, पूर्णांक type)
अणु
	काष्ठा dvb_ringbuffer *rb;
	u8 *kb;
	अचिन्हित दीर्घ toकरो = count;

	dprपूर्णांकk(2, "%s: type %d cnt %lu\n", __func__, type, count);

	rb = (type) ? &av7110->avout : &av7110->aout;
	kb = av7110->kbuf[type];

	अगर (!kb)
		वापस -ENOBUFS;

	अगर (nonblock && !FREE_COND_TS)
		वापस -EWOULDBLOCK;

	जबतक (toकरो >= TS_SIZE) अणु
		अगर (!FREE_COND_TS) अणु
			अगर (nonblock)
				वापस count - toकरो;
			अगर (रुको_event_पूर्णांकerruptible(rb->queue, FREE_COND_TS))
				वापस count - toकरो;
		पूर्ण
		अगर (copy_from_user(kb, buf, TS_SIZE))
			वापस -EFAULT;
		ग_लिखो_ts_to_decoder(av7110, type, kb, TS_SIZE);
		toकरो -= TS_SIZE;
		buf += TS_SIZE;
	पूर्ण

	वापस count - toकरो;
पूर्ण


#घोषणा FREE_COND (dvb_ringbuffer_मुक्त(&av7110->avout) >= 20 * 1024 && \
		   dvb_ringbuffer_मुक्त(&av7110->aout) >= 20 * 1024)

अटल sमाप_प्रकार dvb_play(काष्ठा av7110 *av7110, स्थिर अक्षर __user *buf,
			अचिन्हित दीर्घ count, पूर्णांक nonblock, पूर्णांक type)
अणु
	अचिन्हित दीर्घ toकरो = count, n;
	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	अगर (!av7110->kbuf[type])
		वापस -ENOBUFS;

	अगर (nonblock && !FREE_COND)
		वापस -EWOULDBLOCK;

	जबतक (toकरो > 0) अणु
		अगर (!FREE_COND) अणु
			अगर (nonblock)
				वापस count - toकरो;
			अगर (रुको_event_पूर्णांकerruptible(av7110->avout.queue,
						     FREE_COND))
				वापस count - toकरो;
		पूर्ण
		n = toकरो;
		अगर (n > IPACKS * 2)
			n = IPACKS * 2;
		अगर (copy_from_user(av7110->kbuf[type], buf, n))
			वापस -EFAULT;
		av7110_ipack_instant_repack(av7110->kbuf[type], n,
					    &av7110->ipack[type]);
		toकरो -= n;
		buf += n;
	पूर्ण
	वापस count - toकरो;
पूर्ण

अटल sमाप_प्रकार dvb_play_kernel(काष्ठा av7110 *av7110, स्थिर u8 *buf,
			अचिन्हित दीर्घ count, पूर्णांक nonblock, पूर्णांक type)
अणु
	अचिन्हित दीर्घ toकरो = count, n;
	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	अगर (!av7110->kbuf[type])
		वापस -ENOBUFS;

	अगर (nonblock && !FREE_COND)
		वापस -EWOULDBLOCK;

	जबतक (toकरो > 0) अणु
		अगर (!FREE_COND) अणु
			अगर (nonblock)
				वापस count - toकरो;
			अगर (रुको_event_पूर्णांकerruptible(av7110->avout.queue,
						     FREE_COND))
				वापस count - toकरो;
		पूर्ण
		n = toकरो;
		अगर (n > IPACKS * 2)
			n = IPACKS * 2;
		av7110_ipack_instant_repack(buf, n, &av7110->ipack[type]);
		toकरो -= n;
		buf += n;
	पूर्ण
	वापस count - toकरो;
पूर्ण

अटल sमाप_प्रकार dvb_aplay(काष्ठा av7110 *av7110, स्थिर अक्षर __user *buf,
			 अचिन्हित दीर्घ count, पूर्णांक nonblock, पूर्णांक type)
अणु
	अचिन्हित दीर्घ toकरो = count, n;
	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	अगर (!av7110->kbuf[type])
		वापस -ENOBUFS;
	अगर (nonblock && dvb_ringbuffer_मुक्त(&av7110->aout) < 20 * 1024)
		वापस -EWOULDBLOCK;

	जबतक (toकरो > 0) अणु
		अगर (dvb_ringbuffer_मुक्त(&av7110->aout) < 20 * 1024) अणु
			अगर (nonblock)
				वापस count - toकरो;
			अगर (रुको_event_पूर्णांकerruptible(av7110->aout.queue,
					(dvb_ringbuffer_मुक्त(&av7110->aout) >= 20 * 1024)))
				वापस count-toकरो;
		पूर्ण
		n = toकरो;
		अगर (n > IPACKS * 2)
			n = IPACKS * 2;
		अगर (copy_from_user(av7110->kbuf[type], buf, n))
			वापस -EFAULT;
		av7110_ipack_instant_repack(av7110->kbuf[type], n,
					    &av7110->ipack[type]);
		toकरो -= n;
		buf += n;
	पूर्ण
	वापस count - toकरो;
पूर्ण

व्योम av7110_p2t_init(काष्ठा av7110_p2t *p, काष्ठा dvb_demux_feed *feed)
अणु
	स_रखो(p->pes, 0, TS_SIZE);
	p->counter = 0;
	p->pos = 0;
	p->frags = 0;
	अगर (feed)
		p->feed = feed;
पूर्ण

अटल व्योम clear_p2t(काष्ठा av7110_p2t *p)
अणु
	स_रखो(p->pes, 0, TS_SIZE);
//	p->counter = 0;
	p->pos = 0;
	p->frags = 0;
पूर्ण


अटल पूर्णांक find_pes_header(u8 स्थिर *buf, दीर्घ पूर्णांक length, पूर्णांक *frags)
अणु
	पूर्णांक c = 0;
	पूर्णांक found = 0;

	*frags = 0;

	जबतक (c < length - 3 && !found) अणु
		अगर (buf[c] == 0x00 && buf[c + 1] == 0x00 &&
		    buf[c + 2] == 0x01) अणु
			चयन ( buf[c + 3] ) अणु
			हाल PROG_STREAM_MAP:
			हाल PRIVATE_STREAM2:
			हाल PROG_STREAM_सूची:
			हाल ECM_STREAM     :
			हाल EMM_STREAM     :
			हाल PADDING_STREAM :
			हाल DSM_CC_STREAM  :
			हाल ISO13522_STREAM:
			हाल PRIVATE_STREAM1:
			हाल AUDIO_STREAM_S ... AUDIO_STREAM_E:
			हाल VIDEO_STREAM_S ... VIDEO_STREAM_E:
				found = 1;
				अवरोध;

			शेष:
				c++;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा
			c++;
	पूर्ण
	अगर (c == length - 3 && !found) अणु
		अगर (buf[length - 1] == 0x00)
			*frags = 1;
		अगर (buf[length - 2] == 0x00 &&
		    buf[length - 1] == 0x00)
			*frags = 2;
		अगर (buf[length - 3] == 0x00 &&
		    buf[length - 2] == 0x00 &&
		    buf[length - 1] == 0x01)
			*frags = 3;
		वापस -1;
	पूर्ण

	वापस c;
पूर्ण

व्योम av7110_p2t_ग_लिखो(u8 स्थिर *buf, दीर्घ पूर्णांक length, u16 pid, काष्ठा av7110_p2t *p)
अणु
	पूर्णांक c, c2, l, add;
	पूर्णांक check, rest;

	c = 0;
	c2 = 0;
	अगर (p->frags)अणु
		check = 0;
		चयन(p->frags) अणु
		हाल 1:
			अगर (buf[c] == 0x00 && buf[c + 1] == 0x01) अणु
				check = 1;
				c += 2;
			पूर्ण
			अवरोध;
		हाल 2:
			अगर (buf[c] == 0x01) अणु
				check = 1;
				c++;
			पूर्ण
			अवरोध;
		हाल 3:
			check = 1;
		पूर्ण
		अगर (check) अणु
			चयन (buf[c]) अणु
			हाल PROG_STREAM_MAP:
			हाल PRIVATE_STREAM2:
			हाल PROG_STREAM_सूची:
			हाल ECM_STREAM     :
			हाल EMM_STREAM     :
			हाल PADDING_STREAM :
			हाल DSM_CC_STREAM  :
			हाल ISO13522_STREAM:
			हाल PRIVATE_STREAM1:
			हाल AUDIO_STREAM_S ... AUDIO_STREAM_E:
			हाल VIDEO_STREAM_S ... VIDEO_STREAM_E:
				p->pes[0] = 0x00;
				p->pes[1] = 0x00;
				p->pes[2] = 0x01;
				p->pes[3] = buf[c];
				p->pos = 4;
				स_नकल(p->pes + p->pos, buf + c, (TS_SIZE - 4) - p->pos);
				c += (TS_SIZE - 4) - p->pos;
				p_to_t(p->pes, (TS_SIZE - 4), pid, &p->counter, p->feed);
				clear_p2t(p);
				अवरोध;

			शेष:
				c = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		p->frags = 0;
	पूर्ण

	अगर (p->pos) अणु
		c2 = find_pes_header(buf + c, length - c, &p->frags);
		अगर (c2 >= 0 && c2 < (TS_SIZE - 4) - p->pos)
			l = c2+c;
		अन्यथा
			l = (TS_SIZE - 4) - p->pos;
		स_नकल(p->pes + p->pos, buf, l);
		c += l;
		p->pos += l;
		p_to_t(p->pes, p->pos, pid, &p->counter, p->feed);
		clear_p2t(p);
	पूर्ण

	add = 0;
	जबतक (c < length) अणु
		c2 = find_pes_header(buf + c + add, length - c - add, &p->frags);
		अगर (c2 >= 0) अणु
			c2 += c + add;
			अगर (c2 > c)अणु
				p_to_t(buf + c, c2 - c, pid, &p->counter, p->feed);
				c = c2;
				clear_p2t(p);
				add = 0;
			पूर्ण अन्यथा
				add = 1;
		पूर्ण अन्यथा अणु
			l = length - c;
			rest = l % (TS_SIZE - 4);
			l -= rest;
			p_to_t(buf + c, l, pid, &p->counter, p->feed);
			स_नकल(p->pes, buf + c + l, rest);
			p->pos = rest;
			c = length;
		पूर्ण
	पूर्ण
पूर्ण


अटल पूर्णांक ग_लिखो_ts_header2(u16 pid, u8 *counter, पूर्णांक pes_start, u8 *buf, u8 length)
अणु
	पूर्णांक i;
	पूर्णांक c = 0;
	पूर्णांक fill;
	u8 tshead[4] = अणु 0x47, 0x00, 0x00, 0x10 पूर्ण;

	fill = (TS_SIZE - 4) - length;
	अगर (pes_start)
		tshead[1] = 0x40;
	अगर (fill)
		tshead[3] = 0x30;
	tshead[1] |= (u8)((pid & 0x1F00) >> 8);
	tshead[2] |= (u8)(pid & 0x00FF);
	tshead[3] |= ((*counter)++ & 0x0F);
	स_नकल(buf, tshead, 4);
	c += 4;

	अगर (fill) अणु
		buf[4] = fill - 1;
		c++;
		अगर (fill > 1) अणु
			buf[5] = 0x00;
			c++;
		पूर्ण
		क्रम (i = 6; i < fill + 4; i++) अणु
			buf[i] = 0xFF;
			c++;
		पूर्ण
	पूर्ण

	वापस c;
पूर्ण


अटल व्योम p_to_t(u8 स्थिर *buf, दीर्घ पूर्णांक length, u16 pid, u8 *counter,
		   काष्ठा dvb_demux_feed *feed)
अणु
	पूर्णांक l, pes_start;
	u8 obuf[TS_SIZE];
	दीर्घ c = 0;

	pes_start = 0;
	अगर (length > 3 &&
	     buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x01)
		चयन (buf[3]) अणु
			हाल PROG_STREAM_MAP:
			हाल PRIVATE_STREAM2:
			हाल PROG_STREAM_सूची:
			हाल ECM_STREAM     :
			हाल EMM_STREAM     :
			हाल PADDING_STREAM :
			हाल DSM_CC_STREAM  :
			हाल ISO13522_STREAM:
			हाल PRIVATE_STREAM1:
			हाल AUDIO_STREAM_S ... AUDIO_STREAM_E:
			हाल VIDEO_STREAM_S ... VIDEO_STREAM_E:
				pes_start = 1;
				अवरोध;

			शेष:
				अवरोध;
		पूर्ण

	जबतक (c < length) अणु
		स_रखो(obuf, 0, TS_SIZE);
		अगर (length - c >= (TS_SIZE - 4))अणु
			l = ग_लिखो_ts_header2(pid, counter, pes_start,
					     obuf, (TS_SIZE - 4));
			स_नकल(obuf + l, buf + c, TS_SIZE - l);
			c += TS_SIZE - l;
		पूर्ण अन्यथा अणु
			l = ग_लिखो_ts_header2(pid, counter, pes_start,
					     obuf, length - c);
			स_नकल(obuf + l, buf + c, TS_SIZE - l);
			c = length;
		पूर्ण
		feed->cb.ts(obuf, 188, शून्य, 0, &feed->feed.ts, शून्य);
		pes_start = 0;
	पूर्ण
पूर्ण


अटल पूर्णांक ग_लिखो_ts_to_decoder(काष्ठा av7110 *av7110, पूर्णांक type, स्थिर u8 *buf, माप_प्रकार len)
अणु
	काष्ठा ipack *ipack = &av7110->ipack[type];

	अगर (buf[1] & TRANS_ERROR) अणु
		av7110_ipack_reset(ipack);
		वापस -1;
	पूर्ण

	अगर (!(buf[3] & PAYLOAD))
		वापस -1;

	अगर (buf[1] & PAY_START)
		av7110_ipack_flush(ipack);

	अगर (buf[3] & ADAPT_FIELD) अणु
		len -= buf[4] + 1;
		buf += buf[4] + 1;
		अगर (!len)
			वापस 0;
	पूर्ण

	av7110_ipack_instant_repack(buf + 4, len - 4, ipack);
	वापस 0;
पूर्ण


पूर्णांक av7110_ग_लिखो_to_decoder(काष्ठा dvb_demux_feed *feed, स्थिर u8 *buf, माप_प्रकार len)
अणु
	काष्ठा dvb_demux *demux = feed->demux;
	काष्ठा av7110 *av7110 = (काष्ठा av7110 *) demux->priv;

	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	अगर (av7110->full_ts && demux->dmx.frontend->source != DMX_MEMORY_FE)
		वापस 0;

	चयन (feed->pes_type) अणु
	हाल 0:
		अगर (av7110->audiostate.stream_source == AUDIO_SOURCE_MEMORY)
			वापस -EINVAL;
		अवरोध;
	हाल 1:
		अगर (av7110->videostate.stream_source == VIDEO_SOURCE_MEMORY)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	वापस ग_लिखो_ts_to_decoder(av7110, feed->pes_type, buf, len);
पूर्ण



/******************************************************************************
 * Video MPEG decoder events
 ******************************************************************************/
व्योम dvb_video_add_event(काष्ठा av7110 *av7110, काष्ठा video_event *event)
अणु
	काष्ठा dvb_video_events *events = &av7110->video_events;
	पूर्णांक wp;

	spin_lock_bh(&events->lock);

	wp = (events->eventw + 1) % MAX_VIDEO_EVENT;
	अगर (wp == events->eventr) अणु
		events->overflow = 1;
		events->eventr = (events->eventr + 1) % MAX_VIDEO_EVENT;
	पूर्ण

	//FIXME: बारtamp?
	स_नकल(&events->events[events->eventw], event, माप(काष्ठा video_event));
	events->eventw = wp;

	spin_unlock_bh(&events->lock);

	wake_up_पूर्णांकerruptible(&events->रुको_queue);
पूर्ण


अटल पूर्णांक dvb_video_get_event (काष्ठा av7110 *av7110, काष्ठा video_event *event, पूर्णांक flags)
अणु
	काष्ठा dvb_video_events *events = &av7110->video_events;

	अगर (events->overflow) अणु
		events->overflow = 0;
		वापस -EOVERFLOW;
	पूर्ण
	अगर (events->eventw == events->eventr) अणु
		पूर्णांक ret;

		अगर (flags & O_NONBLOCK)
			वापस -EWOULDBLOCK;

		ret = रुको_event_पूर्णांकerruptible(events->रुको_queue,
					       events->eventw != events->eventr);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	spin_lock_bh(&events->lock);

	स_नकल(event, &events->events[events->eventr],
	       माप(काष्ठा video_event));
	events->eventr = (events->eventr + 1) % MAX_VIDEO_EVENT;

	spin_unlock_bh(&events->lock);

	वापस 0;
पूर्ण

/******************************************************************************
 * DVB device file operations
 ******************************************************************************/

अटल __poll_t dvb_video_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा av7110 *av7110 = dvbdev->priv;
	__poll_t mask = 0;

	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	अगर ((file->f_flags & O_ACCMODE) != O_RDONLY)
		poll_रुको(file, &av7110->avout.queue, रुको);

	poll_रुको(file, &av7110->video_events.रुको_queue, रुको);

	अगर (av7110->video_events.eventw != av7110->video_events.eventr)
		mask = EPOLLPRI;

	अगर ((file->f_flags & O_ACCMODE) != O_RDONLY) अणु
		अगर (av7110->playing) अणु
			अगर (FREE_COND)
				mask |= (EPOLLOUT | EPOLLWRNORM);
		पूर्ण अन्यथा अणु
			/* अगर not playing: may play अगर asked क्रम */
			mask |= (EPOLLOUT | EPOLLWRNORM);
		पूर्ण
	पूर्ण

	वापस mask;
पूर्ण

अटल sमाप_प्रकार dvb_video_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा av7110 *av7110 = dvbdev->priv;
	अचिन्हित अक्षर c;

	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	अगर ((file->f_flags & O_ACCMODE) == O_RDONLY)
		वापस -EPERM;

	अगर (av7110->videostate.stream_source != VIDEO_SOURCE_MEMORY)
		वापस -EPERM;

	अगर (get_user(c, buf))
		वापस -EFAULT;
	अगर (c == 0x47 && count % TS_SIZE == 0)
		वापस ts_play(av7110, buf, count, file->f_flags & O_NONBLOCK, 1);
	अन्यथा
		वापस dvb_play(av7110, buf, count, file->f_flags & O_NONBLOCK, 1);
पूर्ण

अटल __poll_t dvb_audio_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा av7110 *av7110 = dvbdev->priv;
	__poll_t mask = 0;

	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	poll_रुको(file, &av7110->aout.queue, रुको);

	अगर (av7110->playing) अणु
		अगर (dvb_ringbuffer_मुक्त(&av7110->aout) >= 20 * 1024)
			mask |= (EPOLLOUT | EPOLLWRNORM);
	पूर्ण अन्यथा /* अगर not playing: may play अगर asked क्रम */
		mask = (EPOLLOUT | EPOLLWRNORM);

	वापस mask;
पूर्ण

अटल sमाप_प्रकार dvb_audio_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा av7110 *av7110 = dvbdev->priv;
	अचिन्हित अक्षर c;

	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	अगर (av7110->audiostate.stream_source != AUDIO_SOURCE_MEMORY) अणु
		prपूर्णांकk(KERN_ERR "not audio source memory\n");
		वापस -EPERM;
	पूर्ण

	अगर (get_user(c, buf))
		वापस -EFAULT;
	अगर (c == 0x47 && count % TS_SIZE == 0)
		वापस ts_play(av7110, buf, count, file->f_flags & O_NONBLOCK, 0);
	अन्यथा
		वापस dvb_aplay(av7110, buf, count, file->f_flags & O_NONBLOCK, 0);
पूर्ण

अटल u8 अगरrame_header[] = अणु 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x80, 0x00, 0x00 पूर्ण;

#घोषणा MIN_IFRAME 400000

अटल पूर्णांक play_अगरrame(काष्ठा av7110 *av7110, अक्षर __user *buf, अचिन्हित पूर्णांक len, पूर्णांक nonblock)
अणु
	अचिन्हित i, n;
	पूर्णांक progressive = 0;
	पूर्णांक match = 0;

	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	अगर (len == 0)
		वापस 0;

	अगर (!(av7110->playing & RP_VIDEO)) अणु
		अगर (av7110_av_start_play(av7110, RP_VIDEO) < 0)
			वापस -EBUSY;
	पूर्ण

	/* search in buf क्रम instances of 00 00 01 b5 1? */
	क्रम (i = 0; i < len; i++) अणु
		अचिन्हित अक्षर c;
		अगर (get_user(c, buf + i))
			वापस -EFAULT;
		अगर (match == 5) अणु
			progressive = c & 0x08;
			match = 0;
		पूर्ण
		अगर (c == 0x00) अणु
			match = (match == 1 || match == 2) ? 2 : 1;
			जारी;
		पूर्ण
		चयन (match++) अणु
		हाल 2: अगर (c == 0x01)
				जारी;
			अवरोध;
		हाल 3: अगर (c == 0xb5)
				जारी;
			अवरोध;
		हाल 4: अगर ((c & 0xf0) == 0x10)
				जारी;
			अवरोध;
		पूर्ण
		match = 0;
	पूर्ण

	/* setting n always > 1, fixes problems when playing stillframes
	   consisting of I- and P-Frames */
	n = MIN_IFRAME / len + 1;

	/* FIXME: nonblock? */
	dvb_play_kernel(av7110, अगरrame_header, माप(अगरrame_header), 0, 1);

	क्रम (i = 0; i < n; i++)
		dvb_play(av7110, buf, len, 0, 1);

	av7110_ipack_flush(&av7110->ipack[1]);

	अगर (progressive)
		वापस vidcom(av7110, AV_VIDEO_CMD_FREEZE, 1);
	अन्यथा
		वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_video_still_picture अणु
	compat_uptr_t iFrame;
	पूर्णांक32_t size;
पूर्ण;
#घोषणा VIDEO_STILLPICTURE32 _IOW('o', 30, काष्ठा compat_video_still_picture)

काष्ठा compat_video_event अणु
	__s32 type;
	/* unused, make sure to use atomic समय क्रम y2038 अगर it ever माला_लो used */
	compat_दीर्घ_t बारtamp;
	जोड़ अणु
		video_माप_प्रकार size;
		अचिन्हित पूर्णांक frame_rate;        /* in frames per 1000sec */
		अचिन्हित अक्षर vsync_field;      /* unknown/odd/even/progressive */
	पूर्ण u;
पूर्ण;
#घोषणा VIDEO_GET_EVENT32 _IOR('o', 28, काष्ठा compat_video_event)

अटल पूर्णांक dvb_compat_video_get_event(काष्ठा av7110 *av7110,
				      काष्ठा compat_video_event *event, पूर्णांक flags)
अणु
	काष्ठा video_event ev;
	पूर्णांक ret;

	ret = dvb_video_get_event(av7110, &ev, flags);

	*event = (काष्ठा compat_video_event) अणु
		.type = ev.type,
		.बारtamp = ev.बारtamp,
		.u.size = ev.u.size,
	पूर्ण;

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक dvb_video_ioctl(काष्ठा file *file,
			   अचिन्हित पूर्णांक cmd, व्योम *parg)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा av7110 *av7110 = dvbdev->priv;
	अचिन्हित दीर्घ arg = (अचिन्हित दीर्घ) parg;
	पूर्णांक ret = 0;

	dprपूर्णांकk(1, "av7110:%p, cmd=%04x\n", av7110,cmd);

	अगर ((file->f_flags & O_ACCMODE) == O_RDONLY) अणु
		अगर ( cmd != VIDEO_GET_STATUS && cmd != VIDEO_GET_EVENT &&
		     cmd != VIDEO_GET_SIZE ) अणु
			वापस -EPERM;
		पूर्ण
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&av7110->ioctl_mutex))
		वापस -ERESTARTSYS;

	चयन (cmd) अणु
	हाल VIDEO_STOP:
		av7110->videostate.play_state = VIDEO_STOPPED;
		अगर (av7110->videostate.stream_source == VIDEO_SOURCE_MEMORY)
			ret = av7110_av_stop(av7110, RP_VIDEO);
		अन्यथा
			ret = vidcom(av7110, AV_VIDEO_CMD_STOP,
			       av7110->videostate.video_blank ? 0 : 1);
		अगर (!ret)
			av7110->trickmode = TRICK_NONE;
		अवरोध;

	हाल VIDEO_PLAY:
		av7110->trickmode = TRICK_NONE;
		अगर (av7110->videostate.play_state == VIDEO_FREEZED) अणु
			av7110->videostate.play_state = VIDEO_PLAYING;
			ret = vidcom(av7110, AV_VIDEO_CMD_PLAY, 0);
			अगर (ret)
				अवरोध;
		पूर्ण
		अगर (av7110->videostate.stream_source == VIDEO_SOURCE_MEMORY) अणु
			अगर (av7110->playing == RP_AV) अणु
				ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY, __Stop, 0);
				अगर (ret)
					अवरोध;
				av7110->playing &= ~RP_VIDEO;
			पूर्ण
			ret = av7110_av_start_play(av7110, RP_VIDEO);
		पूर्ण
		अगर (!ret)
			ret = vidcom(av7110, AV_VIDEO_CMD_PLAY, 0);
		अगर (!ret)
			av7110->videostate.play_state = VIDEO_PLAYING;
		अवरोध;

	हाल VIDEO_FREEZE:
		av7110->videostate.play_state = VIDEO_FREEZED;
		अगर (av7110->playing & RP_VIDEO)
			ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY, __Pause, 0);
		अन्यथा
			ret = vidcom(av7110, AV_VIDEO_CMD_FREEZE, 1);
		अगर (!ret)
			av7110->trickmode = TRICK_FREEZE;
		अवरोध;

	हाल VIDEO_CONTINUE:
		अगर (av7110->playing & RP_VIDEO)
			ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY, __Continue, 0);
		अगर (!ret)
			ret = vidcom(av7110, AV_VIDEO_CMD_PLAY, 0);
		अगर (!ret) अणु
			av7110->videostate.play_state = VIDEO_PLAYING;
			av7110->trickmode = TRICK_NONE;
		पूर्ण
		अवरोध;

	हाल VIDEO_SELECT_SOURCE:
		av7110->videostate.stream_source = (video_stream_source_t) arg;
		अवरोध;

	हाल VIDEO_SET_BLANK:
		av7110->videostate.video_blank = (पूर्णांक) arg;
		अवरोध;

	हाल VIDEO_GET_STATUS:
		स_नकल(parg, &av7110->videostate, माप(काष्ठा video_status));
		अवरोध;

#अगर_घोषित CONFIG_COMPAT
	हाल VIDEO_GET_EVENT32:
		ret = dvb_compat_video_get_event(av7110, parg, file->f_flags);
		अवरोध;
#पूर्ण_अगर

	हाल VIDEO_GET_EVENT:
		ret = dvb_video_get_event(av7110, parg, file->f_flags);
		अवरोध;

	हाल VIDEO_GET_SIZE:
		स_नकल(parg, &av7110->video_size, माप(video_माप_प्रकार));
		अवरोध;

	हाल VIDEO_SET_DISPLAY_FORMAT:
	अणु
		video_displayक्रमmat_t क्रमmat = (video_displayक्रमmat_t) arg;
		चयन (क्रमmat) अणु
		हाल VIDEO_PAN_SCAN:
			av7110->display_panscan = VID_PAN_SCAN_PREF;
			अवरोध;
		हाल VIDEO_LETTER_BOX:
			av7110->display_panscan = VID_VC_AND_PS_PREF;
			अवरोध;
		हाल VIDEO_CENTER_CUT_OUT:
			av7110->display_panscan = VID_CENTRE_CUT_PREF;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		अगर (ret < 0)
			अवरोध;
		av7110->videostate.display_क्रमmat = क्रमmat;
		ret = av7110_fw_cmd(av7110, COMTYPE_ENCODER, SetPanScanType,
				    1, av7110->display_panscan);
		अवरोध;
	पूर्ण

	हाल VIDEO_SET_FORMAT:
		अगर (arg > 1) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		av7110->display_ar = arg;
		ret = av7110_fw_cmd(av7110, COMTYPE_ENCODER, SetMonitorType,
				    1, (u16) arg);
		अवरोध;

#अगर_घोषित CONFIG_COMPAT
	हाल VIDEO_STILLPICTURE32:
	अणु
		काष्ठा compat_video_still_picture *pic =
			(काष्ठा compat_video_still_picture *) parg;
		av7110->videostate.stream_source = VIDEO_SOURCE_MEMORY;
		dvb_ringbuffer_flush_spinlock_wakeup(&av7110->avout);
		ret = play_अगरrame(av7110, compat_ptr(pic->iFrame),
				  pic->size, file->f_flags & O_NONBLOCK);
		अवरोध;
	पूर्ण
#पूर्ण_अगर

	हाल VIDEO_STILLPICTURE:
	अणु
		काष्ठा video_still_picture *pic =
			(काष्ठा video_still_picture *) parg;
		av7110->videostate.stream_source = VIDEO_SOURCE_MEMORY;
		dvb_ringbuffer_flush_spinlock_wakeup(&av7110->avout);
		ret = play_अगरrame(av7110, pic->iFrame, pic->size,
				  file->f_flags & O_NONBLOCK);
		अवरोध;
	पूर्ण

	हाल VIDEO_FAST_FORWARD:
		//note: arg is ignored by firmware
		अगर (av7110->playing & RP_VIDEO)
			ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY,
					    __Scan_I, 2, AV_PES, 0);
		अन्यथा
			ret = vidcom(av7110, AV_VIDEO_CMD_FFWD, arg);
		अगर (!ret) अणु
			av7110->trickmode = TRICK_FAST;
			av7110->videostate.play_state = VIDEO_PLAYING;
		पूर्ण
		अवरोध;

	हाल VIDEO_SLOWMOTION:
		अगर (av7110->playing&RP_VIDEO) अणु
			अगर (av7110->trickmode != TRICK_SLOW)
				ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY, __Slow, 2, 0, 0);
			अगर (!ret)
				ret = vidcom(av7110, AV_VIDEO_CMD_SLOW, arg);
		पूर्ण अन्यथा अणु
			ret = vidcom(av7110, AV_VIDEO_CMD_PLAY, 0);
			अगर (!ret)
				ret = vidcom(av7110, AV_VIDEO_CMD_STOP, 0);
			अगर (!ret)
				ret = vidcom(av7110, AV_VIDEO_CMD_SLOW, arg);
		पूर्ण
		अगर (!ret) अणु
			av7110->trickmode = TRICK_SLOW;
			av7110->videostate.play_state = VIDEO_PLAYING;
		पूर्ण
		अवरोध;

	हाल VIDEO_GET_CAPABILITIES:
		*(पूर्णांक *)parg = VIDEO_CAP_MPEG1 | VIDEO_CAP_MPEG2 |
			VIDEO_CAP_SYS | VIDEO_CAP_PROG;
		अवरोध;

	हाल VIDEO_CLEAR_BUFFER:
		dvb_ringbuffer_flush_spinlock_wakeup(&av7110->avout);
		av7110_ipack_reset(&av7110->ipack[1]);
		अगर (av7110->playing == RP_AV) अणु
			ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY,
					    __Play, 2, AV_PES, 0);
			अगर (ret)
				अवरोध;
			अगर (av7110->trickmode == TRICK_FAST)
				ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY,
						    __Scan_I, 2, AV_PES, 0);
			अगर (av7110->trickmode == TRICK_SLOW) अणु
				ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY,
						    __Slow, 2, 0, 0);
				अगर (!ret)
					ret = vidcom(av7110, AV_VIDEO_CMD_SLOW, arg);
			पूर्ण
			अगर (av7110->trickmode == TRICK_FREEZE)
				ret = vidcom(av7110, AV_VIDEO_CMD_STOP, 1);
		पूर्ण
		अवरोध;

	हाल VIDEO_SET_STREAMTYPE:
		अवरोध;

	शेष:
		ret = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण

	mutex_unlock(&av7110->ioctl_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dvb_audio_ioctl(काष्ठा file *file,
			   अचिन्हित पूर्णांक cmd, व्योम *parg)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा av7110 *av7110 = dvbdev->priv;
	अचिन्हित दीर्घ arg = (अचिन्हित दीर्घ) parg;
	पूर्णांक ret = 0;

	dprपूर्णांकk(1, "av7110:%p, cmd=%04x\n", av7110,cmd);

	अगर (((file->f_flags & O_ACCMODE) == O_RDONLY) &&
	    (cmd != AUDIO_GET_STATUS))
		वापस -EPERM;

	अगर (mutex_lock_पूर्णांकerruptible(&av7110->ioctl_mutex))
		वापस -ERESTARTSYS;

	चयन (cmd) अणु
	हाल AUDIO_STOP:
		अगर (av7110->audiostate.stream_source == AUDIO_SOURCE_MEMORY)
			ret = av7110_av_stop(av7110, RP_AUDIO);
		अन्यथा
			ret = audcom(av7110, AUDIO_CMD_MUTE);
		अगर (!ret)
			av7110->audiostate.play_state = AUDIO_STOPPED;
		अवरोध;

	हाल AUDIO_PLAY:
		अगर (av7110->audiostate.stream_source == AUDIO_SOURCE_MEMORY)
			ret = av7110_av_start_play(av7110, RP_AUDIO);
		अगर (!ret)
			ret = audcom(av7110, AUDIO_CMD_UNMUTE);
		अगर (!ret)
			av7110->audiostate.play_state = AUDIO_PLAYING;
		अवरोध;

	हाल AUDIO_PAUSE:
		ret = audcom(av7110, AUDIO_CMD_MUTE);
		अगर (!ret)
			av7110->audiostate.play_state = AUDIO_PAUSED;
		अवरोध;

	हाल AUDIO_CONTINUE:
		अगर (av7110->audiostate.play_state == AUDIO_PAUSED) अणु
			av7110->audiostate.play_state = AUDIO_PLAYING;
			ret = audcom(av7110, AUDIO_CMD_UNMUTE | AUDIO_CMD_PCM16);
		पूर्ण
		अवरोध;

	हाल AUDIO_SELECT_SOURCE:
		av7110->audiostate.stream_source = (audio_stream_source_t) arg;
		अवरोध;

	हाल AUDIO_SET_MUTE:
	अणु
		ret = audcom(av7110, arg ? AUDIO_CMD_MUTE : AUDIO_CMD_UNMUTE);
		अगर (!ret)
			av7110->audiostate.mute_state = (पूर्णांक) arg;
		अवरोध;
	पूर्ण

	हाल AUDIO_SET_AV_SYNC:
		av7110->audiostate.AV_sync_state = (पूर्णांक) arg;
		ret = audcom(av7110, arg ? AUDIO_CMD_SYNC_ON : AUDIO_CMD_SYNC_OFF);
		अवरोध;

	हाल AUDIO_SET_BYPASS_MODE:
		अगर (FW_VERSION(av7110->arm_app) < 0x2621)
			ret = -EINVAL;
		av7110->audiostate.bypass_mode = (पूर्णांक)arg;
		अवरोध;

	हाल AUDIO_CHANNEL_SELECT:
		av7110->audiostate.channel_select = (audio_channel_select_t) arg;
		चयन(av7110->audiostate.channel_select) अणु
		हाल AUDIO_STEREO:
			ret = audcom(av7110, AUDIO_CMD_STEREO);
			अगर (!ret) अणु
				अगर (av7110->adac_type == DVB_ADAC_CRYSTAL)
					i2c_ग_लिखोreg(av7110, 0x20, 0x02, 0x49);
				अन्यथा अगर (av7110->adac_type == DVB_ADAC_MSP34x5)
					msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0008, 0x0220);
			पूर्ण
			अवरोध;
		हाल AUDIO_MONO_LEFT:
			ret = audcom(av7110, AUDIO_CMD_MONO_L);
			अगर (!ret) अणु
				अगर (av7110->adac_type == DVB_ADAC_CRYSTAL)
					i2c_ग_लिखोreg(av7110, 0x20, 0x02, 0x4a);
				अन्यथा अगर (av7110->adac_type == DVB_ADAC_MSP34x5)
					msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0008, 0x0200);
			पूर्ण
			अवरोध;
		हाल AUDIO_MONO_RIGHT:
			ret = audcom(av7110, AUDIO_CMD_MONO_R);
			अगर (!ret) अणु
				अगर (av7110->adac_type == DVB_ADAC_CRYSTAL)
					i2c_ग_लिखोreg(av7110, 0x20, 0x02, 0x45);
				अन्यथा अगर (av7110->adac_type == DVB_ADAC_MSP34x5)
					msp_ग_लिखोreg(av7110, MSP_WR_DSP, 0x0008, 0x0210);
			पूर्ण
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल AUDIO_GET_STATUS:
		स_नकल(parg, &av7110->audiostate, माप(काष्ठा audio_status));
		अवरोध;

	हाल AUDIO_GET_CAPABILITIES:
		अगर (FW_VERSION(av7110->arm_app) < 0x2621)
			*(अचिन्हित पूर्णांक *)parg = AUDIO_CAP_LPCM | AUDIO_CAP_MP1 | AUDIO_CAP_MP2;
		अन्यथा
			*(अचिन्हित पूर्णांक *)parg = AUDIO_CAP_LPCM | AUDIO_CAP_DTS | AUDIO_CAP_AC3 |
						AUDIO_CAP_MP1 | AUDIO_CAP_MP2;
		अवरोध;

	हाल AUDIO_CLEAR_BUFFER:
		dvb_ringbuffer_flush_spinlock_wakeup(&av7110->aout);
		av7110_ipack_reset(&av7110->ipack[0]);
		अगर (av7110->playing == RP_AV)
			ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY,
					    __Play, 2, AV_PES, 0);
		अवरोध;

	हाल AUDIO_SET_ID:
		अवरोध;

	हाल AUDIO_SET_MIXER:
	अणु
		काष्ठा audio_mixer *amix = (काष्ठा audio_mixer *)parg;
		ret = av7110_set_volume(av7110, amix->volume_left, amix->volume_right);
		अवरोध;
	पूर्ण

	हाल AUDIO_SET_STREAMTYPE:
		अवरोध;

	शेष:
		ret = -ENOIOCTLCMD;
	पूर्ण

	mutex_unlock(&av7110->ioctl_mutex);
	वापस ret;
पूर्ण


अटल पूर्णांक dvb_video_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा av7110 *av7110 = dvbdev->priv;
	पूर्णांक err;

	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	अगर ((err = dvb_generic_खोलो(inode, file)) < 0)
		वापस err;

	अगर ((file->f_flags & O_ACCMODE) != O_RDONLY) अणु
		dvb_ringbuffer_flush_spinlock_wakeup(&av7110->aout);
		dvb_ringbuffer_flush_spinlock_wakeup(&av7110->avout);
		av7110->video_blank = 1;
		av7110->audiostate.AV_sync_state = 1;
		av7110->videostate.stream_source = VIDEO_SOURCE_DEMUX;

		/*  empty event queue */
		av7110->video_events.eventr = av7110->video_events.eventw = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_video_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा av7110 *av7110 = dvbdev->priv;

	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	अगर ((file->f_flags & O_ACCMODE) != O_RDONLY) अणु
		av7110_av_stop(av7110, RP_VIDEO);
	पूर्ण

	वापस dvb_generic_release(inode, file);
पूर्ण

अटल पूर्णांक dvb_audio_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा av7110 *av7110 = dvbdev->priv;
	पूर्णांक err = dvb_generic_खोलो(inode, file);

	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	अगर (err < 0)
		वापस err;
	dvb_ringbuffer_flush_spinlock_wakeup(&av7110->aout);
	av7110->audiostate.stream_source = AUDIO_SOURCE_DEMUX;
	वापस 0;
पूर्ण

अटल पूर्णांक dvb_audio_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा av7110 *av7110 = dvbdev->priv;

	dprपूर्णांकk(2, "av7110:%p, \n", av7110);

	av7110_av_stop(av7110, RP_AUDIO);
	वापस dvb_generic_release(inode, file);
पूर्ण



/******************************************************************************
 * driver registration
 ******************************************************************************/

अटल स्थिर काष्ठा file_operations dvb_video_fops = अणु
	.owner		= THIS_MODULE,
	.ग_लिखो		= dvb_video_ग_लिखो,
	.unlocked_ioctl	= dvb_generic_ioctl,
	.compat_ioctl	= dvb_generic_ioctl,
	.खोलो		= dvb_video_खोलो,
	.release	= dvb_video_release,
	.poll		= dvb_video_poll,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा dvb_device dvbdev_video = अणु
	.priv		= शून्य,
	.users		= 6,
	.पढ़ोers	= 5,	/* arbitrary */
	.ग_लिखोrs	= 1,
	.fops		= &dvb_video_fops,
	.kernel_ioctl	= dvb_video_ioctl,
पूर्ण;

अटल स्थिर काष्ठा file_operations dvb_audio_fops = अणु
	.owner		= THIS_MODULE,
	.ग_लिखो		= dvb_audio_ग_लिखो,
	.unlocked_ioctl	= dvb_generic_ioctl,
	.compat_ioctl	= dvb_generic_ioctl,
	.खोलो		= dvb_audio_खोलो,
	.release	= dvb_audio_release,
	.poll		= dvb_audio_poll,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा dvb_device dvbdev_audio = अणु
	.priv		= शून्य,
	.users		= 1,
	.ग_लिखोrs	= 1,
	.fops		= &dvb_audio_fops,
	.kernel_ioctl	= dvb_audio_ioctl,
पूर्ण;


पूर्णांक av7110_av_रेजिस्टर(काष्ठा av7110 *av7110)
अणु
	av7110->audiostate.AV_sync_state = 0;
	av7110->audiostate.mute_state = 0;
	av7110->audiostate.play_state = AUDIO_STOPPED;
	av7110->audiostate.stream_source = AUDIO_SOURCE_DEMUX;
	av7110->audiostate.channel_select = AUDIO_STEREO;
	av7110->audiostate.bypass_mode = 0;

	av7110->videostate.video_blank = 0;
	av7110->videostate.play_state = VIDEO_STOPPED;
	av7110->videostate.stream_source = VIDEO_SOURCE_DEMUX;
	av7110->videostate.video_क्रमmat = VIDEO_FORMAT_4_3;
	av7110->videostate.display_क्रमmat = VIDEO_LETTER_BOX;
	av7110->display_ar = VIDEO_FORMAT_4_3;
	av7110->display_panscan = VID_VC_AND_PS_PREF;

	init_रुकोqueue_head(&av7110->video_events.रुको_queue);
	spin_lock_init(&av7110->video_events.lock);
	av7110->video_events.eventw = av7110->video_events.eventr = 0;
	av7110->video_events.overflow = 0;
	स_रखो(&av7110->video_size, 0, माप (video_माप_प्रकार));

	dvb_रेजिस्टर_device(&av7110->dvb_adapter, &av7110->video_dev,
			    &dvbdev_video, av7110, DVB_DEVICE_VIDEO, 0);

	dvb_रेजिस्टर_device(&av7110->dvb_adapter, &av7110->audio_dev,
			    &dvbdev_audio, av7110, DVB_DEVICE_AUDIO, 0);

	वापस 0;
पूर्ण

व्योम av7110_av_unरेजिस्टर(काष्ठा av7110 *av7110)
अणु
	dvb_unरेजिस्टर_device(av7110->audio_dev);
	dvb_unरेजिस्टर_device(av7110->video_dev);
पूर्ण

पूर्णांक av7110_av_init(काष्ठा av7110 *av7110)
अणु
	व्योम (*play[])(u8 *, पूर्णांक, व्योम *) = अणु play_audio_cb, play_video_cb पूर्ण;
	पूर्णांक i, ret;

	क्रम (i = 0; i < 2; i++) अणु
		काष्ठा ipack *ipack = av7110->ipack + i;

		ret = av7110_ipack_init(ipack, IPACKS, play[i]);
		अगर (ret < 0) अणु
			अगर (i)
				av7110_ipack_मुक्त(--ipack);
			जाओ out;
		पूर्ण
		ipack->data = av7110;
	पूर्ण

	dvb_ringbuffer_init(&av7110->avout, av7110->iobuf, AVOUTLEN);
	dvb_ringbuffer_init(&av7110->aout, av7110->iobuf + AVOUTLEN, AOUTLEN);

	av7110->kbuf[0] = (u8 *)(av7110->iobuf + AVOUTLEN + AOUTLEN + BMPLEN);
	av7110->kbuf[1] = av7110->kbuf[0] + 2 * IPACKS;
out:
	वापस ret;
पूर्ण

व्योम av7110_av_निकास(काष्ठा av7110 *av7110)
अणु
	av7110_ipack_मुक्त(&av7110->ipack[0]);
	av7110_ipack_मुक्त(&av7110->ipack[1]);
पूर्ण
