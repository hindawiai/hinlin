<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TTUSB DEC Driver
 *
 * Copyright (C) 2003-2004 Alex Woods <linux-dvb@giblets.org>
 * IR support by Peter Beutner <p.beutner@gmx.net>
 */

#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/usb.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/firmware.h>
#समावेश <linux/crc32.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>

#समावेश <linux/mutex.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>
#समावेश "ttusbdecfe.h"

अटल पूर्णांक debug;
अटल पूर्णांक output_pva;
अटल पूर्णांक enable_rc;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off debugging (default:off).");
module_param(output_pva, पूर्णांक, 0444);
MODULE_PARM_DESC(output_pva, "Output PVA from dvr device (default:off)");
module_param(enable_rc, पूर्णांक, 0644);
MODULE_PARM_DESC(enable_rc, "Turn on/off IR remote control(default: off)");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

#घोषणा dprपूर्णांकk	अगर (debug) prपूर्णांकk

#घोषणा DRIVER_NAME		"TechnoTrend/Hauppauge DEC USB"

#घोषणा COMMAND_PIPE		0x03
#घोषणा RESULT_PIPE		0x04
#घोषणा IN_PIPE			0x08
#घोषणा OUT_PIPE		0x07
#घोषणा IRQ_PIPE		0x0A

#घोषणा COMMAND_PACKET_SIZE	0x3c
#घोषणा ARM_PACKET_SIZE		0x1000
#घोषणा IRQ_PACKET_SIZE		0x8

#घोषणा ISO_BUF_COUNT		0x04
#घोषणा FRAMES_PER_ISO_BUF	0x04
#घोषणा ISO_FRAME_SIZE		0x0380

#घोषणा	MAX_PVA_LENGTH		6144

क्रमागत ttusb_dec_model अणु
	TTUSB_DEC2000T,
	TTUSB_DEC2540T,
	TTUSB_DEC3000S
पूर्ण;

क्रमागत ttusb_dec_packet_type अणु
	TTUSB_DEC_PACKET_PVA,
	TTUSB_DEC_PACKET_SECTION,
	TTUSB_DEC_PACKET_EMPTY
पूर्ण;

क्रमागत ttusb_dec_पूर्णांकerface अणु
	TTUSB_DEC_INTERFACE_INITIAL,
	TTUSB_DEC_INTERFACE_IN,
	TTUSB_DEC_INTERFACE_OUT
पूर्ण;

प्रकार पूर्णांक (dvb_filter_pes2ts_cb_t) (व्योम *, अचिन्हित अक्षर *);

काष्ठा dvb_filter_pes2ts अणु
	अचिन्हित अक्षर buf[188];
	अचिन्हित अक्षर cc;
	dvb_filter_pes2ts_cb_t *cb;
	व्योम *priv;
पूर्ण;

काष्ठा ttusb_dec अणु
	क्रमागत ttusb_dec_model		model;
	अक्षर				*model_name;
	अक्षर				*firmware_name;
	पूर्णांक				can_playback;

	/* DVB bits */
	काष्ठा dvb_adapter		adapter;
	काष्ठा dmxdev			dmxdev;
	काष्ठा dvb_demux		demux;
	काष्ठा dmx_frontend		frontend;
	काष्ठा dvb_net			dvb_net;
	काष्ठा dvb_frontend*		fe;

	u16			pid[DMX_PES_OTHER];

	/* USB bits */
	काष्ठा usb_device		*udev;
	u8				trans_count;
	अचिन्हित पूर्णांक			command_pipe;
	अचिन्हित पूर्णांक			result_pipe;
	अचिन्हित पूर्णांक			in_pipe;
	अचिन्हित पूर्णांक			out_pipe;
	अचिन्हित पूर्णांक			irq_pipe;
	क्रमागत ttusb_dec_पूर्णांकerface	पूर्णांकerface;
	काष्ठा mutex			usb_mutex;

	व्योम			*irq_buffer;
	काष्ठा urb		*irq_urb;
	dma_addr_t		irq_dma_handle;
	व्योम			*iso_buffer;
	काष्ठा urb		*iso_urb[ISO_BUF_COUNT];
	पूर्णांक			iso_stream_count;
	काष्ठा mutex		iso_mutex;

	u8				packet[MAX_PVA_LENGTH + 4];
	क्रमागत ttusb_dec_packet_type	packet_type;
	पूर्णांक				packet_state;
	पूर्णांक				packet_length;
	पूर्णांक				packet_payload_length;
	u16				next_packet_id;

	पूर्णांक				pva_stream_count;
	पूर्णांक				filter_stream_count;

	काष्ठा dvb_filter_pes2ts	a_pes2ts;
	काष्ठा dvb_filter_pes2ts	v_pes2ts;

	u8			v_pes[16 + MAX_PVA_LENGTH];
	पूर्णांक			v_pes_length;
	पूर्णांक			v_pes_postbytes;

	काष्ठा list_head	urb_frame_list;
	काष्ठा tasklet_काष्ठा	urb_tasklet;
	spinlock_t		urb_frame_list_lock;

	काष्ठा dvb_demux_filter	*audio_filter;
	काष्ठा dvb_demux_filter	*video_filter;
	काष्ठा list_head	filter_info_list;
	spinlock_t		filter_info_list_lock;

	काष्ठा input_dev	*rc_input_dev;
	अक्षर			rc_phys[64];

	पूर्णांक			active; /* Loaded successfully */
पूर्ण;

काष्ठा urb_frame अणु
	u8			data[ISO_FRAME_SIZE];
	पूर्णांक			length;
	काष्ठा list_head	urb_frame_list;
पूर्ण;

काष्ठा filter_info अणु
	u8			stream_id;
	काष्ठा dvb_demux_filter	*filter;
	काष्ठा list_head	filter_info_list;
पूर्ण;

अटल u16 rc_keys[] = अणु
	KEY_POWER,
	KEY_MUTE,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,
	KEY_CHANNELUP,
	KEY_VOLUMEDOWN,
	KEY_OK,
	KEY_VOLUMEUP,
	KEY_CHANNELDOWN,
	KEY_PREVIOUS,
	KEY_ESC,
	KEY_RED,
	KEY_GREEN,
	KEY_YELLOW,
	KEY_BLUE,
	KEY_OPTION,
	KEY_M,
	KEY_RADIO
पूर्ण;

अटल व्योम dvb_filter_pes2ts_init(काष्ठा dvb_filter_pes2ts *p2ts,
				   अचिन्हित लघु pid,
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

अटल पूर्णांक dvb_filter_pes2ts(काष्ठा dvb_filter_pes2ts *p2ts,
			     अचिन्हित अक्षर *pes, पूर्णांक len, पूर्णांक payload_start)
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

अटल व्योम ttusb_dec_set_model(काष्ठा ttusb_dec *dec,
				क्रमागत ttusb_dec_model model);

अटल व्योम ttusb_dec_handle_irq( काष्ठा urb *urb)
अणु
	काष्ठा ttusb_dec *dec = urb->context;
	अक्षर *buffer = dec->irq_buffer;
	पूर्णांक retval;
	पूर्णांक index = buffer[4];

	चयन(urb->status) अणु
		हाल 0: /*success*/
			अवरोध;
		हाल -ECONNRESET:
		हाल -ENOENT:
		हाल -ESHUTDOWN:
		हाल -ETIME:
			/* this urb is dead, cleanup */
			dprपूर्णांकk("%s:urb shutting down with status: %d\n",
					__func__, urb->status);
			वापस;
		शेष:
			dprपूर्णांकk("%s:nonzero status received: %d\n",
					__func__,urb->status);
			जाओ निकास;
	पूर्ण

	अगर ((buffer[0] == 0x1) && (buffer[2] == 0x15))  अणु
		/*
		 * IR - Event
		 *
		 * this is an fact a bit too simple implementation;
		 * the box also reports a keyrepeat संकेत
		 * (with buffer[3] == 0x40) in an पूर्णांकerval of ~100ms.
		 * But to handle this correctly we had to imlemenent some
		 * kind of समयr which संकेतs a 'key up' event अगर no
		 * keyrepeat संकेत is received क्रम lets say 200ms.
		 * this should/could be added later ...
		 * क्रम now lets report each संकेत as a key करोwn and up
		 */
		अगर (index - 1 < ARRAY_SIZE(rc_keys)) अणु
			dprपूर्णांकk("%s:rc signal:%d\n", __func__, index);
			input_report_key(dec->rc_input_dev, rc_keys[index - 1], 1);
			input_sync(dec->rc_input_dev);
			input_report_key(dec->rc_input_dev, rc_keys[index - 1], 0);
			input_sync(dec->rc_input_dev);
		पूर्ण
	पूर्ण

निकास:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		prपूर्णांकk("%s - usb_commit_urb failed with result: %d\n",
			__func__, retval);
पूर्ण

अटल u16 crc16(u16 crc, स्थिर u8 *buf, माप_प्रकार len)
अणु
	u16 पंचांगp;

	जबतक (len--) अणु
		crc ^= *buf++;
		crc ^= (u8)crc >> 4;
		पंचांगp = (u8)crc;
		crc ^= (पंचांगp ^ (पंचांगp << 1)) << 4;
	पूर्ण
	वापस crc;
पूर्ण

अटल पूर्णांक ttusb_dec_send_command(काष्ठा ttusb_dec *dec, स्थिर u8 command,
				  पूर्णांक param_length, स्थिर u8 params[],
				  पूर्णांक *result_length, u8 cmd_result[])
अणु
	पूर्णांक result, actual_len;
	u8 *b;

	dprपूर्णांकk("%s\n", __func__);

	b = kzalloc(COMMAND_PACKET_SIZE + 4, GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;

	अगर ((result = mutex_lock_पूर्णांकerruptible(&dec->usb_mutex))) अणु
		kमुक्त(b);
		prपूर्णांकk("%s: Failed to lock usb mutex.\n", __func__);
		वापस result;
	पूर्ण

	b[0] = 0xaa;
	b[1] = ++dec->trans_count;
	b[2] = command;
	b[3] = param_length;

	अगर (params)
		स_नकल(&b[4], params, param_length);

	अगर (debug) अणु
		prपूर्णांकk(KERN_DEBUG "%s: command: %*ph\n",
		       __func__, param_length, b);
	पूर्ण

	result = usb_bulk_msg(dec->udev, dec->command_pipe, b,
			      COMMAND_PACKET_SIZE + 4, &actual_len, 1000);

	अगर (result) अणु
		prपूर्णांकk("%s: command bulk message failed: error %d\n",
		       __func__, result);
		mutex_unlock(&dec->usb_mutex);
		kमुक्त(b);
		वापस result;
	पूर्ण

	result = usb_bulk_msg(dec->udev, dec->result_pipe, b,
			      COMMAND_PACKET_SIZE + 4, &actual_len, 1000);

	अगर (result) अणु
		prपूर्णांकk("%s: result bulk message failed: error %d\n",
		       __func__, result);
		mutex_unlock(&dec->usb_mutex);
		kमुक्त(b);
		वापस result;
	पूर्ण अन्यथा अणु
		अगर (debug) अणु
			prपूर्णांकk(KERN_DEBUG "%s: result: %*ph\n",
			       __func__, actual_len, b);
		पूर्ण

		अगर (result_length)
			*result_length = b[3];
		अगर (cmd_result && b[3] > 0)
			स_नकल(cmd_result, &b[4], b[3]);

		mutex_unlock(&dec->usb_mutex);

		kमुक्त(b);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ttusb_dec_get_stb_state (काष्ठा ttusb_dec *dec, अचिन्हित पूर्णांक *mode,
				    अचिन्हित पूर्णांक *model, अचिन्हित पूर्णांक *version)
अणु
	u8 c[COMMAND_PACKET_SIZE];
	पूर्णांक c_length;
	पूर्णांक result;
	__be32 पंचांगp;

	dprपूर्णांकk("%s\n", __func__);

	result = ttusb_dec_send_command(dec, 0x08, 0, शून्य, &c_length, c);
	अगर (result)
		वापस result;

	अगर (c_length >= 0x0c) अणु
		अगर (mode != शून्य) अणु
			स_नकल(&पंचांगp, c, 4);
			*mode = ntohl(पंचांगp);
		पूर्ण
		अगर (model != शून्य) अणु
			स_नकल(&पंचांगp, &c[4], 4);
			*model = ntohl(पंचांगp);
		पूर्ण
		अगर (version != शून्य) अणु
			स_नकल(&पंचांगp, &c[8], 4);
			*version = ntohl(पंचांगp);
		पूर्ण
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -ENOENT;
	पूर्ण
पूर्ण

अटल पूर्णांक ttusb_dec_audio_pes2ts_cb(व्योम *priv, अचिन्हित अक्षर *data)
अणु
	काष्ठा ttusb_dec *dec = priv;

	dec->audio_filter->feed->cb.ts(data, 188, शून्य, 0,
				       &dec->audio_filter->feed->feed.ts, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक ttusb_dec_video_pes2ts_cb(व्योम *priv, अचिन्हित अक्षर *data)
अणु
	काष्ठा ttusb_dec *dec = priv;

	dec->video_filter->feed->cb.ts(data, 188, शून्य, 0,
				       &dec->video_filter->feed->feed.ts, शून्य);

	वापस 0;
पूर्ण

अटल व्योम ttusb_dec_set_pids(काष्ठा ttusb_dec *dec)
अणु
	u8 b[] = अणु 0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00, 0xff, 0xff,
		   0xff, 0xff, 0xff, 0xff पूर्ण;

	__be16 pcr = htons(dec->pid[DMX_PES_PCR]);
	__be16 audio = htons(dec->pid[DMX_PES_AUDIO]);
	__be16 video = htons(dec->pid[DMX_PES_VIDEO]);

	dprपूर्णांकk("%s\n", __func__);

	स_नकल(&b[0], &pcr, 2);
	स_नकल(&b[2], &audio, 2);
	स_नकल(&b[4], &video, 2);

	ttusb_dec_send_command(dec, 0x50, माप(b), b, शून्य, शून्य);

	dvb_filter_pes2ts_init(&dec->a_pes2ts, dec->pid[DMX_PES_AUDIO],
			       ttusb_dec_audio_pes2ts_cb, dec);
	dvb_filter_pes2ts_init(&dec->v_pes2ts, dec->pid[DMX_PES_VIDEO],
			       ttusb_dec_video_pes2ts_cb, dec);
	dec->v_pes_length = 0;
	dec->v_pes_postbytes = 0;
पूर्ण

अटल व्योम ttusb_dec_process_pva(काष्ठा ttusb_dec *dec, u8 *pva, पूर्णांक length)
अणु
	अगर (length < 8) अणु
		prपूर्णांकk("%s: packet too short - discarding\n", __func__);
		वापस;
	पूर्ण

	अगर (length > 8 + MAX_PVA_LENGTH) अणु
		prपूर्णांकk("%s: packet too long - discarding\n", __func__);
		वापस;
	पूर्ण

	चयन (pva[2]) अणु

	हाल 0x01: अणु		/* VideoStream */
		पूर्णांक prebytes = pva[5] & 0x03;
		पूर्णांक postbytes = (pva[5] & 0x0c) >> 2;
		__be16 v_pes_payload_length;

		अगर (output_pva) अणु
			dec->video_filter->feed->cb.ts(pva, length, शून्य, 0,
				&dec->video_filter->feed->feed.ts, शून्य);
			वापस;
		पूर्ण

		अगर (dec->v_pes_postbytes > 0 &&
		    dec->v_pes_postbytes == prebytes) अणु
			स_नकल(&dec->v_pes[dec->v_pes_length],
			       &pva[12], prebytes);

			dvb_filter_pes2ts(&dec->v_pes2ts, dec->v_pes,
					  dec->v_pes_length + prebytes, 1);
		पूर्ण

		अगर (pva[5] & 0x10) अणु
			dec->v_pes[7] = 0x80;
			dec->v_pes[8] = 0x05;

			dec->v_pes[9] = 0x21 | ((pva[8] & 0xc0) >> 5);
			dec->v_pes[10] = ((pva[8] & 0x3f) << 2) |
					 ((pva[9] & 0xc0) >> 6);
			dec->v_pes[11] = 0x01 |
					 ((pva[9] & 0x3f) << 2) |
					 ((pva[10] & 0x80) >> 6);
			dec->v_pes[12] = ((pva[10] & 0x7f) << 1) |
					 ((pva[11] & 0xc0) >> 7);
			dec->v_pes[13] = 0x01 | ((pva[11] & 0x7f) << 1);

			स_नकल(&dec->v_pes[14], &pva[12 + prebytes],
			       length - 12 - prebytes);
			dec->v_pes_length = 14 + length - 12 - prebytes;
		पूर्ण अन्यथा अणु
			dec->v_pes[7] = 0x00;
			dec->v_pes[8] = 0x00;

			स_नकल(&dec->v_pes[9], &pva[8], length - 8);
			dec->v_pes_length = 9 + length - 8;
		पूर्ण

		dec->v_pes_postbytes = postbytes;

		अगर (dec->v_pes[9 + dec->v_pes[8]] == 0x00 &&
		    dec->v_pes[10 + dec->v_pes[8]] == 0x00 &&
		    dec->v_pes[11 + dec->v_pes[8]] == 0x01)
			dec->v_pes[6] = 0x84;
		अन्यथा
			dec->v_pes[6] = 0x80;

		v_pes_payload_length = htons(dec->v_pes_length - 6 +
					     postbytes);
		स_नकल(&dec->v_pes[4], &v_pes_payload_length, 2);

		अगर (postbytes == 0)
			dvb_filter_pes2ts(&dec->v_pes2ts, dec->v_pes,
					  dec->v_pes_length, 1);

		अवरोध;
	पूर्ण

	हाल 0x02:		/* MainAudioStream */
		अगर (output_pva) अणु
			dec->audio_filter->feed->cb.ts(pva, length, शून्य, 0,
				&dec->audio_filter->feed->feed.ts, शून्य);
			वापस;
		पूर्ण

		dvb_filter_pes2ts(&dec->a_pes2ts, &pva[8], length - 8,
				  pva[5] & 0x10);
		अवरोध;

	शेष:
		prपूर्णांकk("%s: unknown PVA type: %02x.\n", __func__,
		       pva[2]);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ttusb_dec_process_filter(काष्ठा ttusb_dec *dec, u8 *packet,
				     पूर्णांक length)
अणु
	काष्ठा list_head *item;
	काष्ठा filter_info *finfo;
	काष्ठा dvb_demux_filter *filter = शून्य;
	अचिन्हित दीर्घ flags;
	u8 sid;

	sid = packet[1];
	spin_lock_irqsave(&dec->filter_info_list_lock, flags);
	क्रम (item = dec->filter_info_list.next; item != &dec->filter_info_list;
	     item = item->next) अणु
		finfo = list_entry(item, काष्ठा filter_info, filter_info_list);
		अगर (finfo->stream_id == sid) अणु
			filter = finfo->filter;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dec->filter_info_list_lock, flags);

	अगर (filter)
		filter->feed->cb.sec(&packet[2], length - 2, शून्य, 0,
				     &filter->filter, शून्य);
पूर्ण

अटल व्योम ttusb_dec_process_packet(काष्ठा ttusb_dec *dec)
अणु
	पूर्णांक i;
	u16 csum = 0;
	u16 packet_id;

	अगर (dec->packet_length % 2) अणु
		prपूर्णांकk("%s: odd sized packet - discarding\n", __func__);
		वापस;
	पूर्ण

	क्रम (i = 0; i < dec->packet_length; i += 2)
		csum ^= ((dec->packet[i] << 8) + dec->packet[i + 1]);

	अगर (csum) अणु
		prपूर्णांकk("%s: checksum failed - discarding\n", __func__);
		वापस;
	पूर्ण

	packet_id = dec->packet[dec->packet_length - 4] << 8;
	packet_id += dec->packet[dec->packet_length - 3];

	अगर ((packet_id != dec->next_packet_id) && dec->next_packet_id) अणु
		prपूर्णांकk("%s: warning: lost packets between %u and %u\n",
		       __func__, dec->next_packet_id - 1, packet_id);
	पूर्ण

	अगर (packet_id == 0xffff)
		dec->next_packet_id = 0x8000;
	अन्यथा
		dec->next_packet_id = packet_id + 1;

	चयन (dec->packet_type) अणु
	हाल TTUSB_DEC_PACKET_PVA:
		अगर (dec->pva_stream_count)
			ttusb_dec_process_pva(dec, dec->packet,
					      dec->packet_payload_length);
		अवरोध;

	हाल TTUSB_DEC_PACKET_SECTION:
		अगर (dec->filter_stream_count)
			ttusb_dec_process_filter(dec, dec->packet,
						 dec->packet_payload_length);
		अवरोध;

	हाल TTUSB_DEC_PACKET_EMPTY:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम swap_bytes(u8 *b, पूर्णांक length)
अणु
	length -= length % 2;
	क्रम (; length; b += 2, length -= 2)
		swap(*b, *(b + 1));
पूर्ण

अटल व्योम ttusb_dec_process_urb_frame(काष्ठा ttusb_dec *dec, u8 *b,
					पूर्णांक length)
अणु
	swap_bytes(b, length);

	जबतक (length) अणु
		चयन (dec->packet_state) अणु

		हाल 0:
		हाल 1:
		हाल 2:
			अगर (*b++ == 0xaa)
				dec->packet_state++;
			अन्यथा
				dec->packet_state = 0;

			length--;
			अवरोध;

		हाल 3:
			अगर (*b == 0x00) अणु
				dec->packet_state++;
				dec->packet_length = 0;
			पूर्ण अन्यथा अगर (*b != 0xaa) अणु
				dec->packet_state = 0;
			पूर्ण

			b++;
			length--;
			अवरोध;

		हाल 4:
			dec->packet[dec->packet_length++] = *b++;

			अगर (dec->packet_length == 2) अणु
				अगर (dec->packet[0] == 'A' &&
				    dec->packet[1] == 'V') अणु
					dec->packet_type =
						TTUSB_DEC_PACKET_PVA;
					dec->packet_state++;
				पूर्ण अन्यथा अगर (dec->packet[0] == 'S') अणु
					dec->packet_type =
						TTUSB_DEC_PACKET_SECTION;
					dec->packet_state++;
				पूर्ण अन्यथा अगर (dec->packet[0] == 0x00) अणु
					dec->packet_type =
						TTUSB_DEC_PACKET_EMPTY;
					dec->packet_payload_length = 2;
					dec->packet_state = 7;
				पूर्ण अन्यथा अणु
					prपूर्णांकk("%s: unknown packet type: %02x%02x\n",
					       __func__,
					       dec->packet[0], dec->packet[1]);
					dec->packet_state = 0;
				पूर्ण
			पूर्ण

			length--;
			अवरोध;

		हाल 5:
			dec->packet[dec->packet_length++] = *b++;

			अगर (dec->packet_type == TTUSB_DEC_PACKET_PVA &&
			    dec->packet_length == 8) अणु
				dec->packet_state++;
				dec->packet_payload_length = 8 +
					(dec->packet[6] << 8) +
					dec->packet[7];
			पूर्ण अन्यथा अगर (dec->packet_type ==
					TTUSB_DEC_PACKET_SECTION &&
				   dec->packet_length == 5) अणु
				dec->packet_state++;
				dec->packet_payload_length = 5 +
					((dec->packet[3] & 0x0f) << 8) +
					dec->packet[4];
			पूर्ण

			length--;
			अवरोध;

		हाल 6: अणु
			पूर्णांक reमुख्यder = dec->packet_payload_length -
					dec->packet_length;

			अगर (length >= reमुख्यder) अणु
				स_नकल(dec->packet + dec->packet_length,
				       b, reमुख्यder);
				dec->packet_length += reमुख्यder;
				b += reमुख्यder;
				length -= reमुख्यder;
				dec->packet_state++;
			पूर्ण अन्यथा अणु
				स_नकल(&dec->packet[dec->packet_length],
				       b, length);
				dec->packet_length += length;
				length = 0;
			पूर्ण

			अवरोध;
		पूर्ण

		हाल 7: अणु
			पूर्णांक tail = 4;

			dec->packet[dec->packet_length++] = *b++;

			अगर (dec->packet_type == TTUSB_DEC_PACKET_SECTION &&
			    dec->packet_payload_length % 2)
				tail++;

			अगर (dec->packet_length ==
			    dec->packet_payload_length + tail) अणु
				ttusb_dec_process_packet(dec);
				dec->packet_state = 0;
			पूर्ण

			length--;
			अवरोध;
		पूर्ण

		शेष:
			prपूर्णांकk("%s: illegal packet state encountered.\n",
			       __func__);
			dec->packet_state = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ttusb_dec_process_urb_frame_list(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ttusb_dec *dec = from_tasklet(dec, t, urb_tasklet);
	काष्ठा list_head *item;
	काष्ठा urb_frame *frame;
	अचिन्हित दीर्घ flags;

	जबतक (1) अणु
		spin_lock_irqsave(&dec->urb_frame_list_lock, flags);
		अगर ((item = dec->urb_frame_list.next) != &dec->urb_frame_list) अणु
			frame = list_entry(item, काष्ठा urb_frame,
					   urb_frame_list);
			list_del(&frame->urb_frame_list);
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&dec->urb_frame_list_lock,
					       flags);
			वापस;
		पूर्ण
		spin_unlock_irqrestore(&dec->urb_frame_list_lock, flags);

		ttusb_dec_process_urb_frame(dec, frame->data, frame->length);
		kमुक्त(frame);
	पूर्ण
पूर्ण

अटल व्योम ttusb_dec_process_urb(काष्ठा urb *urb)
अणु
	काष्ठा ttusb_dec *dec = urb->context;

	अगर (!urb->status) अणु
		पूर्णांक i;

		क्रम (i = 0; i < FRAMES_PER_ISO_BUF; i++) अणु
			काष्ठा usb_iso_packet_descriptor *d;
			u8 *b;
			पूर्णांक length;
			काष्ठा urb_frame *frame;

			d = &urb->iso_frame_desc[i];
			b = urb->transfer_buffer + d->offset;
			length = d->actual_length;

			अगर ((frame = kदो_स्मृति(माप(काष्ठा urb_frame),
					     GFP_ATOMIC))) अणु
				अचिन्हित दीर्घ flags;

				स_नकल(frame->data, b, length);
				frame->length = length;

				spin_lock_irqsave(&dec->urb_frame_list_lock,
						     flags);
				list_add_tail(&frame->urb_frame_list,
					      &dec->urb_frame_list);
				spin_unlock_irqrestore(&dec->urb_frame_list_lock,
						       flags);

				tasklet_schedule(&dec->urb_tasklet);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		 /* -ENOENT is expected when unlinking urbs */
		अगर (urb->status != -ENOENT)
			dprपूर्णांकk("%s: urb error: %d\n", __func__,
				urb->status);
	पूर्ण

	अगर (dec->iso_stream_count)
		usb_submit_urb(urb, GFP_ATOMIC);
पूर्ण

अटल व्योम ttusb_dec_setup_urbs(काष्ठा ttusb_dec *dec)
अणु
	पूर्णांक i, j, buffer_offset = 0;

	dprपूर्णांकk("%s\n", __func__);

	क्रम (i = 0; i < ISO_BUF_COUNT; i++) अणु
		पूर्णांक frame_offset = 0;
		काष्ठा urb *urb = dec->iso_urb[i];

		urb->dev = dec->udev;
		urb->context = dec;
		urb->complete = ttusb_dec_process_urb;
		urb->pipe = dec->in_pipe;
		urb->transfer_flags = URB_ISO_ASAP;
		urb->पूर्णांकerval = 1;
		urb->number_of_packets = FRAMES_PER_ISO_BUF;
		urb->transfer_buffer_length = ISO_FRAME_SIZE *
					      FRAMES_PER_ISO_BUF;
		urb->transfer_buffer = dec->iso_buffer + buffer_offset;
		buffer_offset += ISO_FRAME_SIZE * FRAMES_PER_ISO_BUF;

		क्रम (j = 0; j < FRAMES_PER_ISO_BUF; j++) अणु
			urb->iso_frame_desc[j].offset = frame_offset;
			urb->iso_frame_desc[j].length = ISO_FRAME_SIZE;
			frame_offset += ISO_FRAME_SIZE;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ttusb_dec_stop_iso_xfer(काष्ठा ttusb_dec *dec)
अणु
	पूर्णांक i;

	dprपूर्णांकk("%s\n", __func__);

	अगर (mutex_lock_पूर्णांकerruptible(&dec->iso_mutex))
		वापस;

	dec->iso_stream_count--;

	अगर (!dec->iso_stream_count) अणु
		क्रम (i = 0; i < ISO_BUF_COUNT; i++)
			usb_समाप्त_urb(dec->iso_urb[i]);
	पूर्ण

	mutex_unlock(&dec->iso_mutex);
पूर्ण

/* Setting the पूर्णांकerface of the DEC tends to take करोwn the USB communications
 * क्रम a लघु period, so it's important not to call this function just beक्रमe
 * trying to talk to it.
 */
अटल पूर्णांक ttusb_dec_set_पूर्णांकerface(काष्ठा ttusb_dec *dec,
				   क्रमागत ttusb_dec_पूर्णांकerface पूर्णांकerface)
अणु
	पूर्णांक result = 0;
	u8 b[] = अणु 0x05 पूर्ण;

	अगर (पूर्णांकerface != dec->पूर्णांकerface) अणु
		चयन (पूर्णांकerface) अणु
		हाल TTUSB_DEC_INTERFACE_INITIAL:
			result = usb_set_पूर्णांकerface(dec->udev, 0, 0);
			अवरोध;
		हाल TTUSB_DEC_INTERFACE_IN:
			result = ttusb_dec_send_command(dec, 0x80, माप(b),
							b, शून्य, शून्य);
			अगर (result)
				वापस result;
			result = usb_set_पूर्णांकerface(dec->udev, 0, 8);
			अवरोध;
		हाल TTUSB_DEC_INTERFACE_OUT:
			result = usb_set_पूर्णांकerface(dec->udev, 0, 1);
			अवरोध;
		पूर्ण

		अगर (result)
			वापस result;

		dec->पूर्णांकerface = पूर्णांकerface;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ttusb_dec_start_iso_xfer(काष्ठा ttusb_dec *dec)
अणु
	पूर्णांक i, result;

	dprपूर्णांकk("%s\n", __func__);

	अगर (mutex_lock_पूर्णांकerruptible(&dec->iso_mutex))
		वापस -EAGAIN;

	अगर (!dec->iso_stream_count) अणु
		ttusb_dec_setup_urbs(dec);

		dec->packet_state = 0;
		dec->v_pes_postbytes = 0;
		dec->next_packet_id = 0;

		क्रम (i = 0; i < ISO_BUF_COUNT; i++) अणु
			अगर ((result = usb_submit_urb(dec->iso_urb[i],
						     GFP_ATOMIC))) अणु
				prपूर्णांकk("%s: failed urb submission %d: error %d\n",
				       __func__, i, result);

				जबतक (i) अणु
					usb_समाप्त_urb(dec->iso_urb[i - 1]);
					i--;
				पूर्ण

				mutex_unlock(&dec->iso_mutex);
				वापस result;
			पूर्ण
		पूर्ण
	पूर्ण

	dec->iso_stream_count++;

	mutex_unlock(&dec->iso_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ttusb_dec_start_ts_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;
	काष्ठा ttusb_dec *dec = dvbdmx->priv;
	u8 b0[] = अणु 0x05 पूर्ण;
	पूर्णांक result = 0;

	dprपूर्णांकk("%s\n", __func__);

	dprपूर्णांकk("  ts_type:");

	अगर (dvbdmxfeed->ts_type & TS_DECODER)
		dprपूर्णांकk(" TS_DECODER");

	अगर (dvbdmxfeed->ts_type & TS_PACKET)
		dprपूर्णांकk(" TS_PACKET");

	अगर (dvbdmxfeed->ts_type & TS_PAYLOAD_ONLY)
		dprपूर्णांकk(" TS_PAYLOAD_ONLY");

	dprपूर्णांकk("\n");

	चयन (dvbdmxfeed->pes_type) अणु

	हाल DMX_PES_VIDEO:
		dprपूर्णांकk("  pes_type: DMX_PES_VIDEO\n");
		dec->pid[DMX_PES_PCR] = dvbdmxfeed->pid;
		dec->pid[DMX_PES_VIDEO] = dvbdmxfeed->pid;
		dec->video_filter = dvbdmxfeed->filter;
		ttusb_dec_set_pids(dec);
		अवरोध;

	हाल DMX_PES_AUDIO:
		dprपूर्णांकk("  pes_type: DMX_PES_AUDIO\n");
		dec->pid[DMX_PES_AUDIO] = dvbdmxfeed->pid;
		dec->audio_filter = dvbdmxfeed->filter;
		ttusb_dec_set_pids(dec);
		अवरोध;

	हाल DMX_PES_TELETEXT:
		dec->pid[DMX_PES_TELETEXT] = dvbdmxfeed->pid;
		dprपूर्णांकk("  pes_type: DMX_PES_TELETEXT(not supported)\n");
		वापस -ENOSYS;

	हाल DMX_PES_PCR:
		dprपूर्णांकk("  pes_type: DMX_PES_PCR\n");
		dec->pid[DMX_PES_PCR] = dvbdmxfeed->pid;
		ttusb_dec_set_pids(dec);
		अवरोध;

	हाल DMX_PES_OTHER:
		dprपूर्णांकk("  pes_type: DMX_PES_OTHER(not supported)\n");
		वापस -ENOSYS;

	शेष:
		dprपूर्णांकk("  pes_type: unknown (%d)\n", dvbdmxfeed->pes_type);
		वापस -EINVAL;

	पूर्ण

	result = ttusb_dec_send_command(dec, 0x80, माप(b0), b0, शून्य, शून्य);
	अगर (result)
		वापस result;

	dec->pva_stream_count++;
	वापस ttusb_dec_start_iso_xfer(dec);
पूर्ण

अटल पूर्णांक ttusb_dec_start_sec_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा ttusb_dec *dec = dvbdmxfeed->demux->priv;
	u8 b0[] = अणु 0x00, 0x00, 0x00, 0x01,
		    0x00, 0x00, 0x00, 0x00,
		    0x00, 0x00, 0x00, 0x00,
		    0x00, 0x00, 0x00, 0x00,
		    0x00, 0xff, 0x00, 0x00,
		    0x00, 0x00, 0x00, 0x00,
		    0x00, 0x00, 0x00, 0x00,
		    0x00 पूर्ण;
	__be16 pid;
	u8 c[COMMAND_PACKET_SIZE];
	पूर्णांक c_length;
	पूर्णांक result;
	काष्ठा filter_info *finfo;
	अचिन्हित दीर्घ flags;
	u8 x = 1;

	dprपूर्णांकk("%s\n", __func__);

	pid = htons(dvbdmxfeed->pid);
	स_नकल(&b0[0], &pid, 2);
	स_नकल(&b0[4], &x, 1);
	स_नकल(&b0[5], &dvbdmxfeed->filter->filter.filter_value[0], 1);

	result = ttusb_dec_send_command(dec, 0x60, माप(b0), b0,
					&c_length, c);

	अगर (!result) अणु
		अगर (c_length == 2) अणु
			अगर (!(finfo = kदो_स्मृति(माप(काष्ठा filter_info),
					      GFP_ATOMIC)))
				वापस -ENOMEM;

			finfo->stream_id = c[1];
			finfo->filter = dvbdmxfeed->filter;

			spin_lock_irqsave(&dec->filter_info_list_lock, flags);
			list_add_tail(&finfo->filter_info_list,
				      &dec->filter_info_list);
			spin_unlock_irqrestore(&dec->filter_info_list_lock,
					       flags);

			dvbdmxfeed->priv = finfo;

			dec->filter_stream_count++;
			वापस ttusb_dec_start_iso_xfer(dec);
		पूर्ण

		वापस -EAGAIN;
	पूर्ण अन्यथा
		वापस result;
पूर्ण

अटल पूर्णांक ttusb_dec_start_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा dvb_demux *dvbdmx = dvbdmxfeed->demux;

	dprपूर्णांकk("%s\n", __func__);

	अगर (!dvbdmx->dmx.frontend)
		वापस -EINVAL;

	dprपूर्णांकk("  pid: 0x%04X\n", dvbdmxfeed->pid);

	चयन (dvbdmxfeed->type) अणु

	हाल DMX_TYPE_TS:
		वापस ttusb_dec_start_ts_feed(dvbdmxfeed);

	हाल DMX_TYPE_SEC:
		वापस ttusb_dec_start_sec_feed(dvbdmxfeed);

	शेष:
		dprपूर्णांकk("  type: unknown (%d)\n", dvbdmxfeed->type);
		वापस -EINVAL;

	पूर्ण
पूर्ण

अटल पूर्णांक ttusb_dec_stop_ts_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा ttusb_dec *dec = dvbdmxfeed->demux->priv;
	u8 b0[] = अणु 0x00 पूर्ण;

	ttusb_dec_send_command(dec, 0x81, माप(b0), b0, शून्य, शून्य);

	dec->pva_stream_count--;

	ttusb_dec_stop_iso_xfer(dec);

	वापस 0;
पूर्ण

अटल पूर्णांक ttusb_dec_stop_sec_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	काष्ठा ttusb_dec *dec = dvbdmxfeed->demux->priv;
	u8 b0[] = अणु 0x00, 0x00 पूर्ण;
	काष्ठा filter_info *finfo = (काष्ठा filter_info *)dvbdmxfeed->priv;
	अचिन्हित दीर्घ flags;

	b0[1] = finfo->stream_id;
	spin_lock_irqsave(&dec->filter_info_list_lock, flags);
	list_del(&finfo->filter_info_list);
	spin_unlock_irqrestore(&dec->filter_info_list_lock, flags);
	kमुक्त(finfo);
	ttusb_dec_send_command(dec, 0x62, माप(b0), b0, शून्य, शून्य);

	dec->filter_stream_count--;

	ttusb_dec_stop_iso_xfer(dec);

	वापस 0;
पूर्ण

अटल पूर्णांक ttusb_dec_stop_feed(काष्ठा dvb_demux_feed *dvbdmxfeed)
अणु
	dprपूर्णांकk("%s\n", __func__);

	चयन (dvbdmxfeed->type) अणु
	हाल DMX_TYPE_TS:
		वापस ttusb_dec_stop_ts_feed(dvbdmxfeed);

	हाल DMX_TYPE_SEC:
		वापस ttusb_dec_stop_sec_feed(dvbdmxfeed);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ttusb_dec_मुक्त_iso_urbs(काष्ठा ttusb_dec *dec)
अणु
	पूर्णांक i;

	dprपूर्णांकk("%s\n", __func__);

	क्रम (i = 0; i < ISO_BUF_COUNT; i++)
		usb_मुक्त_urb(dec->iso_urb[i]);
	kमुक्त(dec->iso_buffer);
पूर्ण

अटल पूर्णांक ttusb_dec_alloc_iso_urbs(काष्ठा ttusb_dec *dec)
अणु
	पूर्णांक i;

	dprपूर्णांकk("%s\n", __func__);

	dec->iso_buffer = kसुस्मृति(FRAMES_PER_ISO_BUF * ISO_BUF_COUNT,
			ISO_FRAME_SIZE, GFP_KERNEL);
	अगर (!dec->iso_buffer)
		वापस -ENOMEM;

	क्रम (i = 0; i < ISO_BUF_COUNT; i++) अणु
		काष्ठा urb *urb;

		अगर (!(urb = usb_alloc_urb(FRAMES_PER_ISO_BUF, GFP_ATOMIC))) अणु
			ttusb_dec_मुक्त_iso_urbs(dec);
			वापस -ENOMEM;
		पूर्ण

		dec->iso_urb[i] = urb;
	पूर्ण

	ttusb_dec_setup_urbs(dec);

	वापस 0;
पूर्ण

अटल व्योम ttusb_dec_init_tasklet(काष्ठा ttusb_dec *dec)
अणु
	spin_lock_init(&dec->urb_frame_list_lock);
	INIT_LIST_HEAD(&dec->urb_frame_list);
	tasklet_setup(&dec->urb_tasklet, ttusb_dec_process_urb_frame_list);
पूर्ण

अटल पूर्णांक ttusb_init_rc( काष्ठा ttusb_dec *dec)
अणु
	काष्ठा input_dev *input_dev;
	u8 b[] = अणु 0x00, 0x01 पूर्ण;
	पूर्णांक i;
	पूर्णांक err;

	usb_make_path(dec->udev, dec->rc_phys, माप(dec->rc_phys));
	strlcat(dec->rc_phys, "/input0", माप(dec->rc_phys));

	input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस -ENOMEM;

	input_dev->name = "ttusb_dec remote control";
	input_dev->phys = dec->rc_phys;
	input_dev->evbit[0] = BIT_MASK(EV_KEY);
	input_dev->keycodesize = माप(u16);
	input_dev->keycodemax = 0x1a;
	input_dev->keycode = rc_keys;

	क्रम (i = 0; i < ARRAY_SIZE(rc_keys); i++)
		  set_bit(rc_keys[i], input_dev->keybit);

	err = input_रेजिस्टर_device(input_dev);
	अगर (err) अणु
		input_मुक्त_device(input_dev);
		वापस err;
	पूर्ण

	dec->rc_input_dev = input_dev;
	अगर (usb_submit_urb(dec->irq_urb, GFP_KERNEL))
		prपूर्णांकk("%s: usb_submit_urb failed\n",__func__);
	/* enable irq pipe */
	ttusb_dec_send_command(dec,0xb0,माप(b),b,शून्य,शून्य);

	वापस 0;
पूर्ण

अटल व्योम ttusb_dec_init_v_pes(काष्ठा ttusb_dec *dec)
अणु
	dprपूर्णांकk("%s\n", __func__);

	dec->v_pes[0] = 0x00;
	dec->v_pes[1] = 0x00;
	dec->v_pes[2] = 0x01;
	dec->v_pes[3] = 0xe0;
पूर्ण

अटल पूर्णांक ttusb_dec_init_usb(काष्ठा ttusb_dec *dec)
अणु
	पूर्णांक result;

	dprपूर्णांकk("%s\n", __func__);

	mutex_init(&dec->usb_mutex);
	mutex_init(&dec->iso_mutex);

	dec->command_pipe = usb_sndbulkpipe(dec->udev, COMMAND_PIPE);
	dec->result_pipe = usb_rcvbulkpipe(dec->udev, RESULT_PIPE);
	dec->in_pipe = usb_rcvisocpipe(dec->udev, IN_PIPE);
	dec->out_pipe = usb_sndisocpipe(dec->udev, OUT_PIPE);
	dec->irq_pipe = usb_rcvपूर्णांकpipe(dec->udev, IRQ_PIPE);

	अगर(enable_rc) अणु
		dec->irq_urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर(!dec->irq_urb) अणु
			वापस -ENOMEM;
		पूर्ण
		dec->irq_buffer = usb_alloc_coherent(dec->udev,IRQ_PACKET_SIZE,
					GFP_KERNEL, &dec->irq_dma_handle);
		अगर(!dec->irq_buffer) अणु
			usb_मुक्त_urb(dec->irq_urb);
			वापस -ENOMEM;
		पूर्ण
		usb_fill_पूर्णांक_urb(dec->irq_urb, dec->udev,dec->irq_pipe,
				 dec->irq_buffer, IRQ_PACKET_SIZE,
				 ttusb_dec_handle_irq, dec, 1);
		dec->irq_urb->transfer_dma = dec->irq_dma_handle;
		dec->irq_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	पूर्ण

	result = ttusb_dec_alloc_iso_urbs(dec);
	अगर (result) अणु
		usb_मुक्त_urb(dec->irq_urb);
		usb_मुक्त_coherent(dec->udev, IRQ_PACKET_SIZE,
				  dec->irq_buffer, dec->irq_dma_handle);
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक ttusb_dec_boot_dsp(काष्ठा ttusb_dec *dec)
अणु
	पूर्णांक i, j, actual_len, result, size, trans_count;
	u8 b0[] = अणु 0x00, 0x00, 0x00, 0x00,
		    0x00, 0x00, 0x00, 0x00,
		    0x61, 0x00 पूर्ण;
	u8 b1[] = अणु 0x61 पूर्ण;
	u8 *b;
	अक्षर idstring[21];
	स्थिर u8 *firmware = शून्य;
	माप_प्रकार firmware_size = 0;
	u16 firmware_csum = 0;
	__be16 firmware_csum_ns;
	__be32 firmware_size_nl;
	u32 crc32_csum, crc32_check;
	__be32 पंचांगp;
	स्थिर काष्ठा firmware *fw_entry = शून्य;

	dprपूर्णांकk("%s\n", __func__);

	result = request_firmware(&fw_entry, dec->firmware_name, &dec->udev->dev);
	अगर (result) अणु
		prपूर्णांकk(KERN_ERR "%s: Firmware (%s) unavailable.\n",
		       __func__, dec->firmware_name);
		वापस result;
	पूर्ण

	firmware = fw_entry->data;
	firmware_size = fw_entry->size;

	अगर (firmware_size < 60) अणु
		prपूर्णांकk("%s: firmware size too small for DSP code (%zu < 60).\n",
			__func__, firmware_size);
		release_firmware(fw_entry);
		वापस -ENOENT;
	पूर्ण

	/* a 32 bit checksum over the first 56 bytes of the DSP Code is stored
	   at offset 56 of file, so use it to check अगर the firmware file is
	   valid. */
	crc32_csum = crc32(~0L, firmware, 56) ^ ~0L;
	स_नकल(&पंचांगp, &firmware[56], 4);
	crc32_check = ntohl(पंचांगp);
	अगर (crc32_csum != crc32_check) अणु
		prपूर्णांकk("%s: crc32 check of DSP code failed (calculated 0x%08x != 0x%08x in file), file invalid.\n",
			__func__, crc32_csum, crc32_check);
		release_firmware(fw_entry);
		वापस -ENOENT;
	पूर्ण
	स_नकल(idstring, &firmware[36], 20);
	idstring[20] = '\0';
	prपूर्णांकk(KERN_INFO "ttusb_dec: found DSP code \"%s\".\n", idstring);

	firmware_size_nl = htonl(firmware_size);
	स_नकल(b0, &firmware_size_nl, 4);
	firmware_csum = crc16(~0, firmware, firmware_size) ^ ~0;
	firmware_csum_ns = htons(firmware_csum);
	स_नकल(&b0[6], &firmware_csum_ns, 2);

	result = ttusb_dec_send_command(dec, 0x41, माप(b0), b0, शून्य, शून्य);

	अगर (result) अणु
		release_firmware(fw_entry);
		वापस result;
	पूर्ण

	trans_count = 0;
	j = 0;

	b = kदो_स्मृति(ARM_PACKET_SIZE, GFP_KERNEL);
	अगर (b == शून्य) अणु
		release_firmware(fw_entry);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < firmware_size; i += COMMAND_PACKET_SIZE) अणु
		size = firmware_size - i;
		अगर (size > COMMAND_PACKET_SIZE)
			size = COMMAND_PACKET_SIZE;

		b[j + 0] = 0xaa;
		b[j + 1] = trans_count++;
		b[j + 2] = 0xf0;
		b[j + 3] = size;
		स_नकल(&b[j + 4], &firmware[i], size);

		j += COMMAND_PACKET_SIZE + 4;

		अगर (j >= ARM_PACKET_SIZE) अणु
			result = usb_bulk_msg(dec->udev, dec->command_pipe, b,
					      ARM_PACKET_SIZE, &actual_len,
					      100);
			j = 0;
		पूर्ण अन्यथा अगर (size < COMMAND_PACKET_SIZE) अणु
			result = usb_bulk_msg(dec->udev, dec->command_pipe, b,
					      j - COMMAND_PACKET_SIZE + size,
					      &actual_len, 100);
		पूर्ण
	पूर्ण

	result = ttusb_dec_send_command(dec, 0x43, माप(b1), b1, शून्य, शून्य);

	release_firmware(fw_entry);
	kमुक्त(b);

	वापस result;
पूर्ण

अटल पूर्णांक ttusb_dec_init_stb(काष्ठा ttusb_dec *dec)
अणु
	पूर्णांक result;
	अचिन्हित पूर्णांक mode = 0, model = 0, version = 0;

	dprपूर्णांकk("%s\n", __func__);

	result = ttusb_dec_get_stb_state(dec, &mode, &model, &version);
	अगर (result)
		वापस result;

	अगर (!mode) अणु
		अगर (version == 0xABCDEFAB)
			prपूर्णांकk(KERN_INFO "ttusb_dec: no version info in Firmware\n");
		अन्यथा
			prपूर्णांकk(KERN_INFO "ttusb_dec: Firmware %x.%02x%c%c\n",
			       version >> 24, (version >> 16) & 0xff,
			       (version >> 8) & 0xff, version & 0xff);

		result = ttusb_dec_boot_dsp(dec);
		अगर (result)
			वापस result;
	पूर्ण अन्यथा अणु
		/* We can't trust the USB IDs that some firmwares
		   give the box */
		चयन (model) अणु
		हाल 0x00070001:
		हाल 0x00070008:
		हाल 0x0007000c:
			ttusb_dec_set_model(dec, TTUSB_DEC3000S);
			अवरोध;
		हाल 0x00070009:
		हाल 0x00070013:
			ttusb_dec_set_model(dec, TTUSB_DEC2000T);
			अवरोध;
		हाल 0x00070011:
			ttusb_dec_set_model(dec, TTUSB_DEC2540T);
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_ERR "%s: unknown model returned by firmware (%08x) - please report\n",
			       __func__, model);
			वापस -ENOENT;
		पूर्ण
		अगर (version >= 0x01770000)
			dec->can_playback = 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ttusb_dec_init_dvb(काष्ठा ttusb_dec *dec)
अणु
	पूर्णांक result;

	dprपूर्णांकk("%s\n", __func__);

	अगर ((result = dvb_रेजिस्टर_adapter(&dec->adapter,
					   dec->model_name, THIS_MODULE,
					   &dec->udev->dev,
					   adapter_nr)) < 0) अणु
		prपूर्णांकk("%s: dvb_register_adapter failed: error %d\n",
		       __func__, result);

		वापस result;
	पूर्ण

	dec->demux.dmx.capabilities = DMX_TS_FILTERING | DMX_SECTION_FILTERING;

	dec->demux.priv = (व्योम *)dec;
	dec->demux.filternum = 31;
	dec->demux.feednum = 31;
	dec->demux.start_feed = ttusb_dec_start_feed;
	dec->demux.stop_feed = ttusb_dec_stop_feed;
	dec->demux.ग_लिखो_to_decoder = शून्य;

	अगर ((result = dvb_dmx_init(&dec->demux)) < 0) अणु
		prपूर्णांकk("%s: dvb_dmx_init failed: error %d\n", __func__,
		       result);

		dvb_unरेजिस्टर_adapter(&dec->adapter);

		वापस result;
	पूर्ण

	dec->dmxdev.filternum = 32;
	dec->dmxdev.demux = &dec->demux.dmx;
	dec->dmxdev.capabilities = 0;

	अगर ((result = dvb_dmxdev_init(&dec->dmxdev, &dec->adapter)) < 0) अणु
		prपूर्णांकk("%s: dvb_dmxdev_init failed: error %d\n",
		       __func__, result);

		dvb_dmx_release(&dec->demux);
		dvb_unरेजिस्टर_adapter(&dec->adapter);

		वापस result;
	पूर्ण

	dec->frontend.source = DMX_FRONTEND_0;

	अगर ((result = dec->demux.dmx.add_frontend(&dec->demux.dmx,
						  &dec->frontend)) < 0) अणु
		prपूर्णांकk("%s: dvb_dmx_init failed: error %d\n", __func__,
		       result);

		dvb_dmxdev_release(&dec->dmxdev);
		dvb_dmx_release(&dec->demux);
		dvb_unरेजिस्टर_adapter(&dec->adapter);

		वापस result;
	पूर्ण

	अगर ((result = dec->demux.dmx.connect_frontend(&dec->demux.dmx,
						      &dec->frontend)) < 0) अणु
		prपूर्णांकk("%s: dvb_dmx_init failed: error %d\n", __func__,
		       result);

		dec->demux.dmx.हटाओ_frontend(&dec->demux.dmx, &dec->frontend);
		dvb_dmxdev_release(&dec->dmxdev);
		dvb_dmx_release(&dec->demux);
		dvb_unरेजिस्टर_adapter(&dec->adapter);

		वापस result;
	पूर्ण

	dvb_net_init(&dec->adapter, &dec->dvb_net, &dec->demux.dmx);

	वापस 0;
पूर्ण

अटल व्योम ttusb_dec_निकास_dvb(काष्ठा ttusb_dec *dec)
अणु
	dprपूर्णांकk("%s\n", __func__);

	dvb_net_release(&dec->dvb_net);
	dec->demux.dmx.बंद(&dec->demux.dmx);
	dec->demux.dmx.हटाओ_frontend(&dec->demux.dmx, &dec->frontend);
	dvb_dmxdev_release(&dec->dmxdev);
	dvb_dmx_release(&dec->demux);
	अगर (dec->fe) अणु
		dvb_unरेजिस्टर_frontend(dec->fe);
		अगर (dec->fe->ops.release)
			dec->fe->ops.release(dec->fe);
	पूर्ण
	dvb_unरेजिस्टर_adapter(&dec->adapter);
पूर्ण

अटल व्योम ttusb_dec_निकास_rc(काष्ठा ttusb_dec *dec)
अणु
	dprपूर्णांकk("%s\n", __func__);

	अगर (dec->rc_input_dev) अणु
		input_unरेजिस्टर_device(dec->rc_input_dev);
		dec->rc_input_dev = शून्य;
	पूर्ण
पूर्ण


अटल व्योम ttusb_dec_निकास_usb(काष्ठा ttusb_dec *dec)
अणु
	पूर्णांक i;

	dprपूर्णांकk("%s\n", __func__);

	अगर (enable_rc) अणु
		/* we have to check whether the irq URB is alपढ़ोy submitted.
		 * As the irq is submitted after the पूर्णांकerface is changed,
		 * this is the best method i figured out.
		 * Any others?*/
		अगर (dec->पूर्णांकerface == TTUSB_DEC_INTERFACE_IN)
			usb_समाप्त_urb(dec->irq_urb);

		usb_मुक्त_urb(dec->irq_urb);

		usb_मुक्त_coherent(dec->udev, IRQ_PACKET_SIZE,
				  dec->irq_buffer, dec->irq_dma_handle);
	पूर्ण

	dec->iso_stream_count = 0;

	क्रम (i = 0; i < ISO_BUF_COUNT; i++)
		usb_समाप्त_urb(dec->iso_urb[i]);

	ttusb_dec_मुक्त_iso_urbs(dec);
पूर्ण

अटल व्योम ttusb_dec_निकास_tasklet(काष्ठा ttusb_dec *dec)
अणु
	काष्ठा list_head *item;
	काष्ठा urb_frame *frame;

	tasklet_समाप्त(&dec->urb_tasklet);

	जबतक ((item = dec->urb_frame_list.next) != &dec->urb_frame_list) अणु
		frame = list_entry(item, काष्ठा urb_frame, urb_frame_list);
		list_del(&frame->urb_frame_list);
		kमुक्त(frame);
	पूर्ण
पूर्ण

अटल व्योम ttusb_dec_init_filters(काष्ठा ttusb_dec *dec)
अणु
	INIT_LIST_HEAD(&dec->filter_info_list);
	spin_lock_init(&dec->filter_info_list_lock);
पूर्ण

अटल व्योम ttusb_dec_निकास_filters(काष्ठा ttusb_dec *dec)
अणु
	काष्ठा list_head *item;
	काष्ठा filter_info *finfo;

	जबतक ((item = dec->filter_info_list.next) != &dec->filter_info_list) अणु
		finfo = list_entry(item, काष्ठा filter_info, filter_info_list);
		list_del(&finfo->filter_info_list);
		kमुक्त(finfo);
	पूर्ण
पूर्ण

अटल पूर्णांक fe_send_command(काष्ठा dvb_frontend* fe, स्थिर u8 command,
			   पूर्णांक param_length, स्थिर u8 params[],
			   पूर्णांक *result_length, u8 cmd_result[])
अणु
	काष्ठा ttusb_dec* dec = fe->dvb->priv;
	वापस ttusb_dec_send_command(dec, command, param_length, params, result_length, cmd_result);
पूर्ण

अटल स्थिर काष्ठा ttusbdecfe_config fe_config = अणु
	.send_command = fe_send_command
पूर्ण;

अटल पूर्णांक ttusb_dec_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			   स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev;
	काष्ठा ttusb_dec *dec;
	पूर्णांक result;

	dprपूर्णांकk("%s\n", __func__);

	udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	अगर (!(dec = kzalloc(माप(काष्ठा ttusb_dec), GFP_KERNEL))) अणु
		prपूर्णांकk("%s: couldn't allocate memory.\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, (व्योम *)dec);

	चयन (id->idProduct) अणु
	हाल 0x1006:
		ttusb_dec_set_model(dec, TTUSB_DEC3000S);
		अवरोध;

	हाल 0x1008:
		ttusb_dec_set_model(dec, TTUSB_DEC2000T);
		अवरोध;

	हाल 0x1009:
		ttusb_dec_set_model(dec, TTUSB_DEC2540T);
		अवरोध;
	पूर्ण

	dec->udev = udev;

	result = ttusb_dec_init_usb(dec);
	अगर (result)
		जाओ err_usb;
	result = ttusb_dec_init_stb(dec);
	अगर (result)
		जाओ err_stb;
	result = ttusb_dec_init_dvb(dec);
	अगर (result)
		जाओ err_stb;

	dec->adapter.priv = dec;
	चयन (id->idProduct) अणु
	हाल 0x1006:
		dec->fe = ttusbdecfe_dvbs_attach(&fe_config);
		अवरोध;

	हाल 0x1008:
	हाल 0x1009:
		dec->fe = ttusbdecfe_dvbt_attach(&fe_config);
		अवरोध;
	पूर्ण

	अगर (dec->fe == शून्य) अणु
		prपूर्णांकk("dvb-ttusb-dec: A frontend driver was not found for device [%04x:%04x]\n",
		       le16_to_cpu(dec->udev->descriptor.idVenकरोr),
		       le16_to_cpu(dec->udev->descriptor.idProduct));
	पूर्ण अन्यथा अणु
		अगर (dvb_रेजिस्टर_frontend(&dec->adapter, dec->fe)) अणु
			prपूर्णांकk("budget-ci: Frontend registration failed!\n");
			अगर (dec->fe->ops.release)
				dec->fe->ops.release(dec->fe);
			dec->fe = शून्य;
		पूर्ण
	पूर्ण

	ttusb_dec_init_v_pes(dec);
	ttusb_dec_init_filters(dec);
	ttusb_dec_init_tasklet(dec);

	dec->active = 1;

	ttusb_dec_set_पूर्णांकerface(dec, TTUSB_DEC_INTERFACE_IN);

	अगर (enable_rc)
		ttusb_init_rc(dec);

	वापस 0;
err_stb:
	ttusb_dec_निकास_usb(dec);
err_usb:
	kमुक्त(dec);
	वापस result;
पूर्ण

अटल व्योम ttusb_dec_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ttusb_dec *dec = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	dprपूर्णांकk("%s\n", __func__);

	अगर (dec->active) अणु
		ttusb_dec_निकास_tasklet(dec);
		ttusb_dec_निकास_filters(dec);
		अगर(enable_rc)
			ttusb_dec_निकास_rc(dec);
		ttusb_dec_निकास_usb(dec);
		ttusb_dec_निकास_dvb(dec);
	पूर्ण

	kमुक्त(dec);
पूर्ण

अटल व्योम ttusb_dec_set_model(काष्ठा ttusb_dec *dec,
				क्रमागत ttusb_dec_model model)
अणु
	dec->model = model;

	चयन (model) अणु
	हाल TTUSB_DEC2000T:
		dec->model_name = "DEC2000-t";
		dec->firmware_name = "dvb-ttusb-dec-2000t.fw";
		अवरोध;

	हाल TTUSB_DEC2540T:
		dec->model_name = "DEC2540-t";
		dec->firmware_name = "dvb-ttusb-dec-2540t.fw";
		अवरोध;

	हाल TTUSB_DEC3000S:
		dec->model_name = "DEC3000-s";
		dec->firmware_name = "dvb-ttusb-dec-3000s.fw";
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा usb_device_id ttusb_dec_table[] = अणु
	अणुUSB_DEVICE(0x0b48, 0x1006)पूर्ण,	/* DEC3000-s */
	/*अणुUSB_DEVICE(0x0b48, 0x1007)पूर्ण,	   Unconfirmed */
	अणुUSB_DEVICE(0x0b48, 0x1008)पूर्ण,	/* DEC2000-t */
	अणुUSB_DEVICE(0x0b48, 0x1009)पूर्ण,	/* DEC2540-t */
	अणुपूर्ण
पूर्ण;

अटल काष्ठा usb_driver ttusb_dec_driver = अणु
	.name		= "ttusb-dec",
	.probe		= ttusb_dec_probe,
	.disconnect	= ttusb_dec_disconnect,
	.id_table	= ttusb_dec_table,
पूर्ण;

module_usb_driver(ttusb_dec_driver);

MODULE_AUTHOR("Alex Woods <linux-dvb@giblets.org>");
MODULE_DESCRIPTION(DRIVER_NAME);
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(usb, ttusb_dec_table);
