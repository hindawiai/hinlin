<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PS3 AV backend support.
 *
 *  Copyright (C) 2007 Sony Computer Entertainment Inc.
 *  Copyright 2007 Sony Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/fb.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/ps3av.h>
#समावेश <यंत्र/ps3.h>

#समावेश "vuart.h"

#घोषणा बफ_मानE          4096	/* vuart buf size */
#घोषणा PS3AV_BUF_SIZE   512	/* max packet size */

अटल पूर्णांक safe_mode;

अटल पूर्णांक समयout = 5000;	/* in msec ( 5 sec ) */
module_param(समयout, पूर्णांक, 0644);

अटल काष्ठा ps3av अणु
	काष्ठा mutex mutex;
	काष्ठा work_काष्ठा work;
	काष्ठा completion करोne;
	पूर्णांक खोलो_count;
	काष्ठा ps3_प्रणाली_bus_device *dev;

	पूर्णांक region;
	काष्ठा ps3av_pkt_av_get_hw_conf av_hw_conf;
	u32 av_port[PS3AV_AV_PORT_MAX + PS3AV_OPT_PORT_MAX];
	u32 opt_port[PS3AV_OPT_PORT_MAX];
	u32 head[PS3AV_HEAD_MAX];
	u32 audio_port;
	पूर्णांक ps3av_mode;
	पूर्णांक ps3av_mode_old;
	जोड़ अणु
		काष्ठा ps3av_reply_hdr reply_hdr;
		u8 raw[PS3AV_BUF_SIZE];
	पूर्ण recv_buf;
पूर्ण *ps3av;

/* color space */
#घोषणा YUV444 PS3AV_CMD_VIDEO_CS_YUV444_8
#घोषणा RGB8   PS3AV_CMD_VIDEO_CS_RGB_8
/* क्रमmat */
#घोषणा XRGB   PS3AV_CMD_VIDEO_FMT_X8R8G8B8
/* aspect */
#घोषणा A_N    PS3AV_CMD_AV_ASPECT_4_3
#घोषणा A_W    PS3AV_CMD_AV_ASPECT_16_9
अटल स्थिर काष्ठा avset_video_mode अणु
	u32 cs;
	u32 fmt;
	u32 vid;
	u32 aspect;
	u32 x;
	u32 y;
पूर्ण video_mode_table[] = अणु
	अणु     0, पूर्ण, /* स्वतः */
	अणुYUV444, XRGB, PS3AV_CMD_VIDEO_VID_480I,       A_N,  720,  480पूर्ण,
	अणुYUV444, XRGB, PS3AV_CMD_VIDEO_VID_480P,       A_N,  720,  480पूर्ण,
	अणुYUV444, XRGB, PS3AV_CMD_VIDEO_VID_720P_60HZ,  A_W, 1280,  720पूर्ण,
	अणुYUV444, XRGB, PS3AV_CMD_VIDEO_VID_1080I_60HZ, A_W, 1920, 1080पूर्ण,
	अणुYUV444, XRGB, PS3AV_CMD_VIDEO_VID_1080P_60HZ, A_W, 1920, 1080पूर्ण,
	अणुYUV444, XRGB, PS3AV_CMD_VIDEO_VID_576I,       A_N,  720,  576पूर्ण,
	अणुYUV444, XRGB, PS3AV_CMD_VIDEO_VID_576P,       A_N,  720,  576पूर्ण,
	अणुYUV444, XRGB, PS3AV_CMD_VIDEO_VID_720P_50HZ,  A_W, 1280,  720पूर्ण,
	अणुYUV444, XRGB, PS3AV_CMD_VIDEO_VID_1080I_50HZ, A_W, 1920, 1080पूर्ण,
	अणुYUV444, XRGB, PS3AV_CMD_VIDEO_VID_1080P_50HZ, A_W, 1920, 1080पूर्ण,
	अणु  RGB8, XRGB, PS3AV_CMD_VIDEO_VID_WXGA,       A_W, 1280,  768पूर्ण,
	अणु  RGB8, XRGB, PS3AV_CMD_VIDEO_VID_SXGA,       A_N, 1280, 1024पूर्ण,
	अणु  RGB8, XRGB, PS3AV_CMD_VIDEO_VID_WUXGA,      A_W, 1920, 1200पूर्ण,
पूर्ण;

/* supported CIDs */
अटल u32 cmd_table[] = अणु
	/* init */
	PS3AV_CID_AV_INIT,
	PS3AV_CID_AV_FIN,
	PS3AV_CID_VIDEO_INIT,
	PS3AV_CID_AUDIO_INIT,

	/* set */
	PS3AV_CID_AV_ENABLE_EVENT,
	PS3AV_CID_AV_DISABLE_EVENT,

	PS3AV_CID_AV_VIDEO_CS,
	PS3AV_CID_AV_VIDEO_MUTE,
	PS3AV_CID_AV_VIDEO_DISABLE_SIG,
	PS3AV_CID_AV_AUDIO_PARAM,
	PS3AV_CID_AV_AUDIO_MUTE,
	PS3AV_CID_AV_HDMI_MODE,
	PS3AV_CID_AV_TV_MUTE,

	PS3AV_CID_VIDEO_MODE,
	PS3AV_CID_VIDEO_FORMAT,
	PS3AV_CID_VIDEO_PITCH,

	PS3AV_CID_AUDIO_MODE,
	PS3AV_CID_AUDIO_MUTE,
	PS3AV_CID_AUDIO_ACTIVE,
	PS3AV_CID_AUDIO_INACTIVE,
	PS3AV_CID_AVB_PARAM,

	/* get */
	PS3AV_CID_AV_GET_HW_CONF,
	PS3AV_CID_AV_GET_MONITOR_INFO,

	/* event */
	PS3AV_CID_EVENT_UNPLUGGED,
	PS3AV_CID_EVENT_PLUGGED,
	PS3AV_CID_EVENT_HDCP_DONE,
	PS3AV_CID_EVENT_HDCP_FAIL,
	PS3AV_CID_EVENT_HDCP_AUTH,
	PS3AV_CID_EVENT_HDCP_ERROR,

	0
पूर्ण;

#घोषणा PS3AV_EVENT_CMD_MASK           0x10000000
#घोषणा PS3AV_EVENT_ID_MASK            0x0000ffff
#घोषणा PS3AV_CID_MASK                 0xffffffff
#घोषणा PS3AV_REPLY_BIT                0x80000000

#घोषणा ps3av_event_get_port_id(cid)   ((cid >> 16) & 0xff)

अटल u32 *ps3av_search_cmd_table(u32 cid, u32 mask)
अणु
	u32 *table;
	पूर्णांक i;

	table = cmd_table;
	क्रम (i = 0;; table++, i++) अणु
		अगर ((*table & mask) == (cid & mask))
			अवरोध;
		अगर (*table == 0)
			वापस शून्य;
	पूर्ण
	वापस table;
पूर्ण

अटल पूर्णांक ps3av_parse_event_packet(स्थिर काष्ठा ps3av_reply_hdr *hdr)
अणु
	u32 *table;

	अगर (hdr->cid & PS3AV_EVENT_CMD_MASK) अणु
		table = ps3av_search_cmd_table(hdr->cid, PS3AV_EVENT_CMD_MASK);
		अगर (table)
			dev_dbg(&ps3av->dev->core,
				"recv event packet cid:%08x port:0x%x size:%d\n",
				hdr->cid, ps3av_event_get_port_id(hdr->cid),
				hdr->size);
		अन्यथा
			prपूर्णांकk(KERN_ERR
			       "%s: failed event packet, cid:%08x size:%d\n",
			       __func__, hdr->cid, hdr->size);
		वापस 1;	/* receive event packet */
	पूर्ण
	वापस 0;
पूर्ण


#घोषणा POLLING_INTERVAL  25	/* in msec */

अटल पूर्णांक ps3av_vuart_ग_लिखो(काष्ठा ps3_प्रणाली_bus_device *dev,
			     स्थिर व्योम *buf, अचिन्हित दीर्घ size)
अणु
	पूर्णांक error;
	dev_dbg(&dev->core, " -> %s:%d\n", __func__, __LINE__);
	error = ps3_vuart_ग_लिखो(dev, buf, size);
	dev_dbg(&dev->core, " <- %s:%d\n", __func__, __LINE__);
	वापस error ? error : size;
पूर्ण

अटल पूर्णांक ps3av_vuart_पढ़ो(काष्ठा ps3_प्रणाली_bus_device *dev, व्योम *buf,
			    अचिन्हित दीर्घ size, पूर्णांक समयout)
अणु
	पूर्णांक error;
	पूर्णांक loopcnt = 0;

	dev_dbg(&dev->core, " -> %s:%d\n", __func__, __LINE__);
	समयout = (समयout + POLLING_INTERVAL - 1) / POLLING_INTERVAL;
	जबतक (loopcnt++ <= समयout) अणु
		error = ps3_vuart_पढ़ो(dev, buf, size);
		अगर (!error)
			वापस size;
		अगर (error != -EAGAIN) अणु
			prपूर्णांकk(KERN_ERR "%s: ps3_vuart_read failed %d\n",
			       __func__, error);
			वापस error;
		पूर्ण
		msleep(POLLING_INTERVAL);
	पूर्ण
	वापस -EWOULDBLOCK;
पूर्ण

अटल पूर्णांक ps3av_send_cmd_pkt(स्थिर काष्ठा ps3av_send_hdr *send_buf,
			      काष्ठा ps3av_reply_hdr *recv_buf, पूर्णांक ग_लिखो_len,
			      पूर्णांक पढ़ो_len)
अणु
	पूर्णांक res;
	u32 cmd;
	पूर्णांक event;

	अगर (!ps3av)
		वापस -ENODEV;

	/* send pkt */
	res = ps3av_vuart_ग_लिखो(ps3av->dev, send_buf, ग_लिखो_len);
	अगर (res < 0) अणु
		dev_dbg(&ps3av->dev->core,
			"%s: ps3av_vuart_write() failed (result=%d)\n",
			__func__, res);
		वापस res;
	पूर्ण

	/* recv pkt */
	cmd = send_buf->cid;
	करो अणु
		/* पढ़ो header */
		res = ps3av_vuart_पढ़ो(ps3av->dev, recv_buf, PS3AV_HDR_SIZE,
				       समयout);
		अगर (res != PS3AV_HDR_SIZE) अणु
			dev_dbg(&ps3av->dev->core,
				"%s: ps3av_vuart_read() failed (result=%d)\n",
				__func__, res);
			वापस res;
		पूर्ण

		/* पढ़ो body */
		res = ps3av_vuart_पढ़ो(ps3av->dev, &recv_buf->cid,
				       recv_buf->size, समयout);
		अगर (res < 0) अणु
			dev_dbg(&ps3av->dev->core,
				"%s: ps3av_vuart_read() failed (result=%d)\n",
				__func__, res);
			वापस res;
		पूर्ण
		res += PS3AV_HDR_SIZE;	/* total len */
		event = ps3av_parse_event_packet(recv_buf);
		/* ret > 0 event packet */
	पूर्ण जबतक (event);

	अगर ((cmd | PS3AV_REPLY_BIT) != recv_buf->cid) अणु
		dev_dbg(&ps3av->dev->core, "%s: reply err (result=%x)\n",
			__func__, recv_buf->cid);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ps3av_process_reply_packet(काष्ठा ps3av_send_hdr *cmd_buf,
				      स्थिर काष्ठा ps3av_reply_hdr *recv_buf,
				      पूर्णांक user_buf_size)
अणु
	पूर्णांक वापस_len;

	अगर (recv_buf->version != PS3AV_VERSION) अणु
		dev_dbg(&ps3av->dev->core, "reply_packet invalid version:%x\n",
			recv_buf->version);
		वापस -EFAULT;
	पूर्ण
	वापस_len = recv_buf->size + PS3AV_HDR_SIZE;
	अगर (वापस_len > user_buf_size)
		वापस_len = user_buf_size;
	स_नकल(cmd_buf, recv_buf, वापस_len);
	वापस 0;		/* success */
पूर्ण

व्योम ps3av_set_hdr(u32 cid, u16 size, काष्ठा ps3av_send_hdr *hdr)
अणु
	hdr->version = PS3AV_VERSION;
	hdr->size = size - PS3AV_HDR_SIZE;
	hdr->cid = cid;
पूर्ण

पूर्णांक ps3av_करो_pkt(u32 cid, u16 send_len, माप_प्रकार usr_buf_size,
		 काष्ठा ps3av_send_hdr *buf)
अणु
	पूर्णांक res = 0;
	u32 *table;

	BUG_ON(!ps3av);

	mutex_lock(&ps3av->mutex);

	table = ps3av_search_cmd_table(cid, PS3AV_CID_MASK);
	BUG_ON(!table);
	BUG_ON(send_len < PS3AV_HDR_SIZE);
	BUG_ON(usr_buf_size < send_len);
	BUG_ON(usr_buf_size > PS3AV_BUF_SIZE);

	/* create header */
	ps3av_set_hdr(cid, send_len, buf);

	/* send packet via vuart */
	res = ps3av_send_cmd_pkt(buf, &ps3av->recv_buf.reply_hdr, send_len,
				 usr_buf_size);
	अगर (res < 0) अणु
		prपूर्णांकk(KERN_ERR
		       "%s: ps3av_send_cmd_pkt() failed (result=%d)\n",
		       __func__, res);
		जाओ err;
	पूर्ण

	/* process reply packet */
	res = ps3av_process_reply_packet(buf, &ps3av->recv_buf.reply_hdr,
					 usr_buf_size);
	अगर (res < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: put_return_status() failed (result=%d)\n",
		       __func__, res);
		जाओ err;
	पूर्ण

	mutex_unlock(&ps3av->mutex);
	वापस 0;

err:
	mutex_unlock(&ps3av->mutex);
	prपूर्णांकk(KERN_ERR "%s: failed cid:%x res:%d\n", __func__, cid, res);
	वापस res;
पूर्ण

अटल पूर्णांक ps3av_set_av_video_mute(u32 mute)
अणु
	पूर्णांक i, num_of_av_port, res;

	num_of_av_port = ps3av->av_hw_conf.num_of_hdmi +
			 ps3av->av_hw_conf.num_of_avmulti;
	/* video mute on */
	क्रम (i = 0; i < num_of_av_port; i++) अणु
		res = ps3av_cmd_av_video_mute(1, &ps3av->av_port[i], mute);
		अगर (res < 0)
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ps3av_set_video_disable_sig(व्योम)
अणु
	पूर्णांक i, num_of_hdmi_port, num_of_av_port, res;

	num_of_hdmi_port = ps3av->av_hw_conf.num_of_hdmi;
	num_of_av_port = ps3av->av_hw_conf.num_of_hdmi +
			 ps3av->av_hw_conf.num_of_avmulti;

	/* tv mute */
	क्रम (i = 0; i < num_of_hdmi_port; i++) अणु
		res = ps3av_cmd_av_tv_mute(ps3av->av_port[i],
					   PS3AV_CMD_MUTE_ON);
		अगर (res < 0)
			वापस -1;
	पूर्ण
	msleep(100);

	/* video mute on */
	क्रम (i = 0; i < num_of_av_port; i++) अणु
		res = ps3av_cmd_av_video_disable_sig(ps3av->av_port[i]);
		अगर (res < 0)
			वापस -1;
		अगर (i < num_of_hdmi_port) अणु
			res = ps3av_cmd_av_tv_mute(ps3av->av_port[i],
						   PS3AV_CMD_MUTE_OFF);
			अगर (res < 0)
				वापस -1;
		पूर्ण
	पूर्ण
	msleep(300);

	वापस 0;
पूर्ण

अटल पूर्णांक ps3av_set_audio_mute(u32 mute)
अणु
	पूर्णांक i, num_of_av_port, num_of_opt_port, res;

	num_of_av_port = ps3av->av_hw_conf.num_of_hdmi +
			 ps3av->av_hw_conf.num_of_avmulti;
	num_of_opt_port = ps3av->av_hw_conf.num_of_spdअगर;

	क्रम (i = 0; i < num_of_av_port; i++) अणु
		res = ps3av_cmd_av_audio_mute(1, &ps3av->av_port[i], mute);
		अगर (res < 0)
			वापस -1;
	पूर्ण
	क्रम (i = 0; i < num_of_opt_port; i++) अणु
		res = ps3av_cmd_audio_mute(1, &ps3av->opt_port[i], mute);
		अगर (res < 0)
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ps3av_set_audio_mode(u32 ch, u32 fs, u32 word_bits, u32 क्रमmat, u32 source)
अणु
	काष्ठा ps3av_pkt_avb_param avb_param;
	पूर्णांक i, num_of_audio, vid, res;
	काष्ठा ps3av_pkt_audio_mode audio_mode;
	u32 len = 0;

	num_of_audio = ps3av->av_hw_conf.num_of_hdmi +
		       ps3av->av_hw_conf.num_of_avmulti +
		       ps3av->av_hw_conf.num_of_spdअगर;

	avb_param.num_of_video_pkt = 0;
	avb_param.num_of_audio_pkt = PS3AV_AVB_NUM_AUDIO;	/* always 0 */
	avb_param.num_of_av_video_pkt = 0;
	avb_param.num_of_av_audio_pkt = ps3av->av_hw_conf.num_of_hdmi;

	vid = video_mode_table[ps3av->ps3av_mode].vid;

	/* audio mute */
	ps3av_set_audio_mute(PS3AV_CMD_MUTE_ON);

	/* audio inactive */
	res = ps3av_cmd_audio_active(0, ps3av->audio_port);
	अगर (res < 0)
		dev_dbg(&ps3av->dev->core,
			"ps3av_cmd_audio_active OFF failed\n");

	/* audio_pkt */
	क्रम (i = 0; i < num_of_audio; i++) अणु
		ps3av_cmd_set_audio_mode(&audio_mode, ps3av->av_port[i], ch,
					 fs, word_bits, क्रमmat, source);
		अगर (i < ps3av->av_hw_conf.num_of_hdmi) अणु
			/* hdmi only */
			len += ps3av_cmd_set_av_audio_param(&avb_param.buf[len],
							    ps3av->av_port[i],
							    &audio_mode, vid);
		पूर्ण
		/* audio_mode pkt should be sent separately */
		res = ps3av_cmd_audio_mode(&audio_mode);
		अगर (res < 0)
			dev_dbg(&ps3av->dev->core,
				"ps3av_cmd_audio_mode failed, port:%x\n", i);
	पूर्ण

	/* send command using avb pkt */
	len += दुरत्व(काष्ठा ps3av_pkt_avb_param, buf);
	res = ps3av_cmd_avb_param(&avb_param, len);
	अगर (res < 0)
		dev_dbg(&ps3av->dev->core, "ps3av_cmd_avb_param failed\n");

	/* audio mute */
	ps3av_set_audio_mute(PS3AV_CMD_MUTE_OFF);

	/* audio active */
	res = ps3av_cmd_audio_active(1, ps3av->audio_port);
	अगर (res < 0)
		dev_dbg(&ps3av->dev->core,
			"ps3av_cmd_audio_active ON failed\n");

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3av_set_audio_mode);

अटल पूर्णांक ps3av_set_videomode(व्योम)
अणु
	/* av video mute */
	ps3av_set_av_video_mute(PS3AV_CMD_MUTE_ON);

	/* wake up ps3avd to करो the actual video mode setting */
	schedule_work(&ps3av->work);

	वापस 0;
पूर्ण

अटल व्योम ps3av_set_videomode_packet(u32 id)
अणु
	काष्ठा ps3av_pkt_avb_param avb_param;
	अचिन्हित पूर्णांक i;
	u32 len = 0, av_video_cs;
	स्थिर काष्ठा avset_video_mode *video_mode;
	पूर्णांक res;

	video_mode = &video_mode_table[id & PS3AV_MODE_MASK];

	avb_param.num_of_video_pkt = PS3AV_AVB_NUM_VIDEO; /* num of head */
	avb_param.num_of_audio_pkt = 0;
	avb_param.num_of_av_video_pkt = ps3av->av_hw_conf.num_of_hdmi +
					ps3av->av_hw_conf.num_of_avmulti;
	avb_param.num_of_av_audio_pkt = 0;

	/* video_pkt */
	क्रम (i = 0; i < avb_param.num_of_video_pkt; i++)
		len += ps3av_cmd_set_video_mode(&avb_param.buf[len],
						ps3av->head[i], video_mode->vid,
						video_mode->fmt, id);
	/* av_video_pkt */
	क्रम (i = 0; i < avb_param.num_of_av_video_pkt; i++) अणु
		अगर (id & PS3AV_MODE_DVI || id & PS3AV_MODE_RGB)
			av_video_cs = RGB8;
		अन्यथा
			av_video_cs = video_mode->cs;
#अगर_अघोषित PS3AV_HDMI_YUV
		अगर (ps3av->av_port[i] == PS3AV_CMD_AVPORT_HDMI_0 ||
		    ps3av->av_port[i] == PS3AV_CMD_AVPORT_HDMI_1)
			av_video_cs = RGB8; /* use RGB क्रम HDMI */
#पूर्ण_अगर
		len += ps3av_cmd_set_av_video_cs(&avb_param.buf[len],
						 ps3av->av_port[i],
						 video_mode->vid, av_video_cs,
						 video_mode->aspect, id);
	पूर्ण
	/* send command using avb pkt */
	len += दुरत्व(काष्ठा ps3av_pkt_avb_param, buf);
	res = ps3av_cmd_avb_param(&avb_param, len);
	अगर (res == PS3AV_STATUS_NO_SYNC_HEAD)
		prपूर्णांकk(KERN_WARNING
		       "%s: Command failed. Please try your request again.\n",
		       __func__);
	अन्यथा अगर (res)
		dev_dbg(&ps3av->dev->core, "ps3av_cmd_avb_param failed\n");
पूर्ण

अटल व्योम ps3av_set_videomode_cont(u32 id, u32 old_id)
अणु
	अटल पूर्णांक vesa;
	पूर्णांक res;

	/* video संकेत off */
	ps3av_set_video_disable_sig();

	/*
	 * AV backend needs non-VESA mode setting at least one समय
	 * when VESA mode is used.
	 */
	अगर (vesa == 0 && (id & PS3AV_MODE_MASK) >= PS3AV_MODE_WXGA) अणु
		/* vesa mode */
		ps3av_set_videomode_packet(PS3AV_MODE_480P);
	पूर्ण
	vesa = 1;

	/* Retail PS3 product करोesn't support this */
	अगर (id & PS3AV_MODE_HDCP_OFF) अणु
		res = ps3av_cmd_av_hdmi_mode(PS3AV_CMD_AV_HDMI_HDCP_OFF);
		अगर (res == PS3AV_STATUS_UNSUPPORTED_HDMI_MODE)
			dev_dbg(&ps3av->dev->core, "Not supported\n");
		अन्यथा अगर (res)
			dev_dbg(&ps3av->dev->core,
				"ps3av_cmd_av_hdmi_mode failed\n");
	पूर्ण अन्यथा अगर (old_id & PS3AV_MODE_HDCP_OFF) अणु
		res = ps3av_cmd_av_hdmi_mode(PS3AV_CMD_AV_HDMI_MODE_NORMAL);
		अगर (res < 0 && res != PS3AV_STATUS_UNSUPPORTED_HDMI_MODE)
			dev_dbg(&ps3av->dev->core,
				"ps3av_cmd_av_hdmi_mode failed\n");
	पूर्ण

	ps3av_set_videomode_packet(id);

	msleep(1500);
	/* av video mute */
	ps3av_set_av_video_mute(PS3AV_CMD_MUTE_OFF);
पूर्ण

अटल व्योम ps3avd(काष्ठा work_काष्ठा *work)
अणु
	ps3av_set_videomode_cont(ps3av->ps3av_mode, ps3av->ps3av_mode_old);
	complete(&ps3av->करोne);
पूर्ण

#घोषणा SHIFT_50	0
#घोषणा SHIFT_60	4
#घोषणा SHIFT_VESA	8

अटल स्थिर काष्ठा अणु
	अचिन्हित mask:19;
	अचिन्हित id:4;
पूर्ण ps3av_preferred_modes[] = अणु
	अणु PS3AV_RESBIT_WUXGA      << SHIFT_VESA, PS3AV_MODE_WUXGA   पूर्ण,
	अणु PS3AV_RESBIT_1920x1080P << SHIFT_60,   PS3AV_MODE_1080P60 पूर्ण,
	अणु PS3AV_RESBIT_1920x1080P << SHIFT_50,   PS3AV_MODE_1080P50 पूर्ण,
	अणु PS3AV_RESBIT_1920x1080I << SHIFT_60,   PS3AV_MODE_1080I60 पूर्ण,
	अणु PS3AV_RESBIT_1920x1080I << SHIFT_50,   PS3AV_MODE_1080I50 पूर्ण,
	अणु PS3AV_RESBIT_SXGA       << SHIFT_VESA, PS3AV_MODE_SXGA    पूर्ण,
	अणु PS3AV_RESBIT_WXGA       << SHIFT_VESA, PS3AV_MODE_WXGA    पूर्ण,
	अणु PS3AV_RESBIT_1280x720P  << SHIFT_60,   PS3AV_MODE_720P60  पूर्ण,
	अणु PS3AV_RESBIT_1280x720P  << SHIFT_50,   PS3AV_MODE_720P50  पूर्ण,
	अणु PS3AV_RESBIT_720x480P   << SHIFT_60,   PS3AV_MODE_480P    पूर्ण,
	अणु PS3AV_RESBIT_720x576P   << SHIFT_50,   PS3AV_MODE_576P    पूर्ण,
पूर्ण;

अटल क्रमागत ps3av_mode_num ps3av_resbit2id(u32 res_50, u32 res_60,
					   u32 res_vesa)
अणु
	अचिन्हित पूर्णांक i;
	u32 res_all;

	/*
	 * We mask off the resolution bits we care about and combine the
	 * results in one bitfield, so make sure there's no overlap
	 */
	BUILD_BUG_ON(PS3AV_RES_MASK_50 << SHIFT_50 &
		     PS3AV_RES_MASK_60 << SHIFT_60);
	BUILD_BUG_ON(PS3AV_RES_MASK_50 << SHIFT_50 &
		     PS3AV_RES_MASK_VESA << SHIFT_VESA);
	BUILD_BUG_ON(PS3AV_RES_MASK_60 << SHIFT_60 &
		     PS3AV_RES_MASK_VESA << SHIFT_VESA);
	res_all = (res_50 & PS3AV_RES_MASK_50) << SHIFT_50 |
		  (res_60 & PS3AV_RES_MASK_60) << SHIFT_60 |
		  (res_vesa & PS3AV_RES_MASK_VESA) << SHIFT_VESA;

	अगर (!res_all)
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(ps3av_preferred_modes); i++)
		अगर (res_all & ps3av_preferred_modes[i].mask)
			वापस ps3av_preferred_modes[i].id;

	वापस 0;
पूर्ण

अटल क्रमागत ps3av_mode_num ps3av_hdmi_get_id(काष्ठा ps3av_info_monitor *info)
अणु
	क्रमागत ps3av_mode_num id;

	अगर (safe_mode)
		वापस PS3AV_DEFAULT_HDMI_MODE_ID_REG_60;

	/* check native resolution */
	id = ps3av_resbit2id(info->res_50.native, info->res_60.native,
			     info->res_vesa.native);
	अगर (id) अणु
		pr_debug("%s: Using native mode %d\n", __func__, id);
		वापस id;
	पूर्ण

	/* check supported resolutions */
	id = ps3av_resbit2id(info->res_50.res_bits, info->res_60.res_bits,
			     info->res_vesa.res_bits);
	अगर (id) अणु
		pr_debug("%s: Using supported mode %d\n", __func__, id);
		वापस id;
	पूर्ण

	अगर (ps3av->region & PS3AV_REGION_60)
		id = PS3AV_DEFAULT_HDMI_MODE_ID_REG_60;
	अन्यथा
		id = PS3AV_DEFAULT_HDMI_MODE_ID_REG_50;
	pr_debug("%s: Using default mode %d\n", __func__, id);
	वापस id;
पूर्ण

अटल व्योम ps3av_monitor_info_dump(
	स्थिर काष्ठा ps3av_pkt_av_get_monitor_info *monitor_info)
अणु
	स्थिर काष्ठा ps3av_info_monitor *info = &monitor_info->info;
	स्थिर काष्ठा ps3av_info_audio *audio = info->audio;
	अक्षर id[माप(info->monitor_id)*3+1];
	पूर्णांक i;

	pr_debug("Monitor Info: size %u\n", monitor_info->send_hdr.size);

	pr_debug("avport: %02x\n", info->avport);
	क्रम (i = 0; i < माप(info->monitor_id); i++)
		प्र_लिखो(&id[i*3], " %02x", info->monitor_id[i]);
	pr_debug("monitor_id: %s\n", id);
	pr_debug("monitor_type: %02x\n", info->monitor_type);
	pr_debug("monitor_name: %.*s\n", (पूर्णांक)माप(info->monitor_name),
		 info->monitor_name);

	/* resolution */
	pr_debug("resolution_60: bits: %08x native: %08x\n",
		 info->res_60.res_bits, info->res_60.native);
	pr_debug("resolution_50: bits: %08x native: %08x\n",
		 info->res_50.res_bits, info->res_50.native);
	pr_debug("resolution_other: bits: %08x native: %08x\n",
		 info->res_other.res_bits, info->res_other.native);
	pr_debug("resolution_vesa: bits: %08x native: %08x\n",
		 info->res_vesa.res_bits, info->res_vesa.native);

	/* color space */
	pr_debug("color space    rgb: %02x\n", info->cs.rgb);
	pr_debug("color space yuv444: %02x\n", info->cs.yuv444);
	pr_debug("color space yuv422: %02x\n", info->cs.yuv422);

	/* color info */
	pr_debug("color info   red: X %04x Y %04x\n", info->color.red_x,
		 info->color.red_y);
	pr_debug("color info green: X %04x Y %04x\n", info->color.green_x,
		 info->color.green_y);
	pr_debug("color info  blue: X %04x Y %04x\n", info->color.blue_x,
		 info->color.blue_y);
	pr_debug("color info white: X %04x Y %04x\n", info->color.white_x,
		 info->color.white_y);
	pr_debug("color info gamma:  %08x\n", info->color.gamma);

	/* other info */
	pr_debug("supported_AI: %02x\n", info->supported_ai);
	pr_debug("speaker_info: %02x\n", info->speaker_info);
	pr_debug("num of audio: %02x\n", info->num_of_audio_block);

	/* audio block */
	क्रम (i = 0; i < info->num_of_audio_block; i++) अणु
		pr_debug(
			"audio[%d] type: %02x max_ch: %02x fs: %02x sbit: %02x\n",
			 i, audio->type, audio->max_num_of_ch, audio->fs,
			 audio->sbit);
		audio++;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ps3av_monitor_quirk अणु
	स्थिर अक्षर *monitor_name;
	u32 clear_60;
पूर्ण ps3av_monitor_quirks[] = अणु
	अणु
		.monitor_name	= "DELL 2007WFP",
		.clear_60	= PS3AV_RESBIT_1920x1080I
	पूर्ण, अणु
		.monitor_name	= "L226WTQ",
		.clear_60	= PS3AV_RESBIT_1920x1080I |
				  PS3AV_RESBIT_1920x1080P
	पूर्ण, अणु
		.monitor_name	= "SyncMaster",
		.clear_60	= PS3AV_RESBIT_1920x1080I
	पूर्ण
पूर्ण;

अटल व्योम ps3av_fixup_monitor_info(काष्ठा ps3av_info_monitor *info)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर काष्ठा ps3av_monitor_quirk *quirk;

	क्रम (i = 0; i < ARRAY_SIZE(ps3av_monitor_quirks); i++) अणु
		quirk = &ps3av_monitor_quirks[i];
		अगर (!म_भेदन(info->monitor_name, quirk->monitor_name,
			     माप(info->monitor_name))) अणु
			pr_info("%s: Applying quirk for %s\n", __func__,
				quirk->monitor_name);
			info->res_60.res_bits &= ~quirk->clear_60;
			info->res_60.native &= ~quirk->clear_60;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ps3av_स्वतः_videomode(काष्ठा ps3av_pkt_av_get_hw_conf *av_hw_conf)
अणु
	पूर्णांक i, res, id = 0, dvi = 0, rgb = 0;
	काष्ठा ps3av_pkt_av_get_monitor_info monitor_info;
	काष्ठा ps3av_info_monitor *info;

	/* get mode id क्रम hdmi */
	क्रम (i = 0; i < av_hw_conf->num_of_hdmi && !id; i++) अणु
		res = ps3av_cmd_video_get_monitor_info(&monitor_info,
						       PS3AV_CMD_AVPORT_HDMI_0 +
						       i);
		अगर (res < 0)
			वापस -1;

		ps3av_monitor_info_dump(&monitor_info);

		info = &monitor_info.info;
		ps3av_fixup_monitor_info(info);

		चयन (info->monitor_type) अणु
		हाल PS3AV_MONITOR_TYPE_DVI:
			dvi = PS3AV_MODE_DVI;
			fallthrough;
		हाल PS3AV_MONITOR_TYPE_HDMI:
			id = ps3av_hdmi_get_id(info);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!id) अणु
		/* no HDMI पूर्णांकerface or HDMI is off */
		अगर (ps3av->region & PS3AV_REGION_60)
			id = PS3AV_DEFAULT_AVMULTI_MODE_ID_REG_60;
		अन्यथा
			id = PS3AV_DEFAULT_AVMULTI_MODE_ID_REG_50;
		अगर (ps3av->region & PS3AV_REGION_RGB)
			rgb = PS3AV_MODE_RGB;
		pr_debug("%s: Using avmulti mode %d\n", __func__, id);
	पूर्ण

	वापस id | dvi | rgb;
पूर्ण

अटल पूर्णांक ps3av_get_hw_conf(काष्ठा ps3av *ps3av)
अणु
	पूर्णांक i, j, k, res;
	स्थिर काष्ठा ps3av_pkt_av_get_hw_conf *hw_conf;

	/* get av_hw_conf */
	res = ps3av_cmd_av_get_hw_conf(&ps3av->av_hw_conf);
	अगर (res < 0)
		वापस -1;

	hw_conf = &ps3av->av_hw_conf;
	pr_debug("av_h_conf: num of hdmi: %u\n", hw_conf->num_of_hdmi);
	pr_debug("av_h_conf: num of avmulti: %u\n", hw_conf->num_of_avmulti);
	pr_debug("av_h_conf: num of spdif: %u\n", hw_conf->num_of_spdअगर);

	क्रम (i = 0; i < PS3AV_HEAD_MAX; i++)
		ps3av->head[i] = PS3AV_CMD_VIDEO_HEAD_A + i;
	क्रम (i = 0; i < PS3AV_OPT_PORT_MAX; i++)
		ps3av->opt_port[i] = PS3AV_CMD_AVPORT_SPDIF_0 + i;
	क्रम (i = 0; i < hw_conf->num_of_hdmi; i++)
		ps3av->av_port[i] = PS3AV_CMD_AVPORT_HDMI_0 + i;
	क्रम (j = 0; j < hw_conf->num_of_avmulti; j++)
		ps3av->av_port[i + j] = PS3AV_CMD_AVPORT_AVMULTI_0 + j;
	क्रम (k = 0; k < hw_conf->num_of_spdअगर; k++)
		ps3av->av_port[i + j + k] = PS3AV_CMD_AVPORT_SPDIF_0 + k;

	/* set all audio port */
	ps3av->audio_port = PS3AV_CMD_AUDIO_PORT_HDMI_0
	    | PS3AV_CMD_AUDIO_PORT_HDMI_1
	    | PS3AV_CMD_AUDIO_PORT_AVMULTI_0
	    | PS3AV_CMD_AUDIO_PORT_SPDIF_0 | PS3AV_CMD_AUDIO_PORT_SPDIF_1;

	वापस 0;
पूर्ण

/* set mode using id */
पूर्णांक ps3av_set_video_mode(पूर्णांक id)
अणु
	पूर्णांक size;
	u32 option;

	size = ARRAY_SIZE(video_mode_table);
	अगर ((id & PS3AV_MODE_MASK) > size - 1 || id < 0) अणु
		dev_dbg(&ps3av->dev->core, "%s: error id :%d\n", __func__, id);
		वापस -EINVAL;
	पूर्ण

	/* स्वतः mode */
	option = id & ~PS3AV_MODE_MASK;
	अगर ((id & PS3AV_MODE_MASK) == PS3AV_MODE_AUTO) अणु
		id = ps3av_स्वतः_videomode(&ps3av->av_hw_conf);
		अगर (id < 1) अणु
			prपूर्णांकk(KERN_ERR "%s: invalid id :%d\n", __func__, id);
			वापस -EINVAL;
		पूर्ण
		id |= option;
	पूर्ण

	/* set videomode */
	रुको_क्रम_completion(&ps3av->करोne);
	ps3av->ps3av_mode_old = ps3av->ps3av_mode;
	ps3av->ps3av_mode = id;
	अगर (ps3av_set_videomode())
		ps3av->ps3av_mode = ps3av->ps3av_mode_old;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3av_set_video_mode);

पूर्णांक ps3av_get_स्वतः_mode(व्योम)
अणु
	वापस ps3av_स्वतः_videomode(&ps3av->av_hw_conf);
पूर्ण
EXPORT_SYMBOL_GPL(ps3av_get_स्वतः_mode);

पूर्णांक ps3av_get_mode(व्योम)
अणु
	वापस ps3av ? ps3av->ps3av_mode : 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3av_get_mode);

/* get resolution by video_mode */
पूर्णांक ps3av_video_mode2res(u32 id, u32 *xres, u32 *yres)
अणु
	पूर्णांक size;

	id = id & PS3AV_MODE_MASK;
	size = ARRAY_SIZE(video_mode_table);
	अगर (id > size - 1 || id < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: invalid mode %d\n", __func__, id);
		वापस -EINVAL;
	पूर्ण
	*xres = video_mode_table[id].x;
	*yres = video_mode_table[id].y;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3av_video_mode2res);

/* mute */
पूर्णांक ps3av_video_mute(पूर्णांक mute)
अणु
	वापस ps3av_set_av_video_mute(mute ? PS3AV_CMD_MUTE_ON
					    : PS3AV_CMD_MUTE_OFF);
पूर्ण
EXPORT_SYMBOL_GPL(ps3av_video_mute);

/* mute analog output only */
पूर्णांक ps3av_audio_mute_analog(पूर्णांक mute)
अणु
	पूर्णांक i, res;

	क्रम (i = 0; i < ps3av->av_hw_conf.num_of_avmulti; i++) अणु
		res = ps3av_cmd_av_audio_mute(1,
			&ps3av->av_port[i + ps3av->av_hw_conf.num_of_hdmi],
			mute);
		अगर (res < 0)
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ps3av_audio_mute_analog);

पूर्णांक ps3av_audio_mute(पूर्णांक mute)
अणु
	वापस ps3av_set_audio_mute(mute ? PS3AV_CMD_MUTE_ON
					 : PS3AV_CMD_MUTE_OFF);
पूर्ण
EXPORT_SYMBOL_GPL(ps3av_audio_mute);

अटल पूर्णांक ps3av_probe(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	पूर्णांक res;
	पूर्णांक id;

	dev_dbg(&dev->core, " -> %s:%d\n", __func__, __LINE__);
	dev_dbg(&dev->core, "  timeout=%d\n", समयout);

	अगर (ps3av) अणु
		dev_err(&dev->core, "Only one ps3av device is supported\n");
		वापस -EBUSY;
	पूर्ण

	ps3av = kzalloc(माप(*ps3av), GFP_KERNEL);
	अगर (!ps3av)
		वापस -ENOMEM;

	mutex_init(&ps3av->mutex);
	ps3av->ps3av_mode = PS3AV_MODE_AUTO;
	ps3av->dev = dev;

	INIT_WORK(&ps3av->work, ps3avd);
	init_completion(&ps3av->करोne);
	complete(&ps3av->करोne);

	चयन (ps3_os_area_get_av_multi_out()) अणु
	हाल PS3_PARAM_AV_MULTI_OUT_NTSC:
		ps3av->region = PS3AV_REGION_60;
		अवरोध;
	हाल PS3_PARAM_AV_MULTI_OUT_PAL_YCBCR:
	हाल PS3_PARAM_AV_MULTI_OUT_SECAM:
		ps3av->region = PS3AV_REGION_50;
		अवरोध;
	हाल PS3_PARAM_AV_MULTI_OUT_PAL_RGB:
		ps3av->region = PS3AV_REGION_50 | PS3AV_REGION_RGB;
		अवरोध;
	शेष:
		ps3av->region = PS3AV_REGION_60;
		अवरोध;
	पूर्ण

	/* init avsetting modules */
	res = ps3av_cmd_init();
	अगर (res < 0)
		prपूर्णांकk(KERN_ERR "%s: ps3av_cmd_init failed %d\n", __func__,
		       res);

	ps3av_get_hw_conf(ps3av);

#अगर_घोषित CONFIG_FB
	अगर (fb_mode_option && !म_भेद(fb_mode_option, "safe"))
		safe_mode = 1;
#पूर्ण_अगर /* CONFIG_FB */
	id = ps3av_स्वतः_videomode(&ps3av->av_hw_conf);
	अगर (id < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: invalid id :%d\n", __func__, id);
		res = -EINVAL;
		जाओ fail;
	पूर्ण

	safe_mode = 0;

	mutex_lock(&ps3av->mutex);
	ps3av->ps3av_mode = id;
	mutex_unlock(&ps3av->mutex);

	dev_dbg(&dev->core, " <- %s:%d\n", __func__, __LINE__);

	वापस 0;

fail:
	kमुक्त(ps3av);
	ps3av = शून्य;
	वापस res;
पूर्ण

अटल पूर्णांक ps3av_हटाओ(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	dev_dbg(&dev->core, " -> %s:%d\n", __func__, __LINE__);
	अगर (ps3av) अणु
		ps3av_cmd_fin();
		flush_work(&ps3av->work);
		kमुक्त(ps3av);
		ps3av = शून्य;
	पूर्ण

	dev_dbg(&dev->core, " <- %s:%d\n", __func__, __LINE__);
	वापस 0;
पूर्ण

अटल व्योम ps3av_shutकरोwn(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	dev_dbg(&dev->core, " -> %s:%d\n", __func__, __LINE__);
	ps3av_हटाओ(dev);
	dev_dbg(&dev->core, " <- %s:%d\n", __func__, __LINE__);
पूर्ण

अटल काष्ठा ps3_vuart_port_driver ps3av_driver = अणु
	.core.match_id = PS3_MATCH_ID_AV_SETTINGS,
	.core.core.name = "ps3_av",
	.probe = ps3av_probe,
	.हटाओ = ps3av_हटाओ,
	.shutकरोwn = ps3av_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init ps3av_module_init(व्योम)
अणु
	पूर्णांक error;

	अगर (!firmware_has_feature(FW_FEATURE_PS3_LV1))
		वापस -ENODEV;

	pr_debug(" -> %s:%d\n", __func__, __LINE__);

	error = ps3_vuart_port_driver_रेजिस्टर(&ps3av_driver);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR
		       "%s: ps3_vuart_port_driver_register failed %d\n",
		       __func__, error);
		वापस error;
	पूर्ण

	pr_debug(" <- %s:%d\n", __func__, __LINE__);
	वापस error;
पूर्ण

अटल व्योम __निकास ps3av_module_निकास(व्योम)
अणु
	pr_debug(" -> %s:%d\n", __func__, __LINE__);
	ps3_vuart_port_driver_unरेजिस्टर(&ps3av_driver);
	pr_debug(" <- %s:%d\n", __func__, __LINE__);
पूर्ण

subsys_initcall(ps3av_module_init);
module_निकास(ps3av_module_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("PS3 AV Settings Driver");
MODULE_AUTHOR("Sony Computer Entertainment Inc.");
MODULE_ALIAS(PS3_MODULE_ALIAS_AV_SETTINGS);
