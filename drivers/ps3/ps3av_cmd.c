<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006 Sony Computer Entertainment Inc.
 * Copyright 2006, 2007 Sony Corporation
 *
 * AV backend support क्रम PS3
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/ps3av.h>
#समावेश <यंत्र/ps3.h>
#समावेश <यंत्र/ps3gpu.h>

#समावेश "vuart.h"

अटल स्थिर काष्ठा video_fmt अणु
	u32 क्रमmat;
	u32 order;
पूर्ण ps3av_video_fmt_table[] = अणु
	अणु PS3AV_CMD_VIDEO_FORMAT_ARGB_8BIT, PS3AV_CMD_VIDEO_ORDER_RGB पूर्ण,
	अणु PS3AV_CMD_VIDEO_FORMAT_ARGB_8BIT, PS3AV_CMD_VIDEO_ORDER_BGR पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक cs;
	u32 av;
	u32 bl;
पूर्ण ps3av_cs_video2av_table[] = अणु
	अणु
		.cs = PS3AV_CMD_VIDEO_CS_RGB_8,
		.av = PS3AV_CMD_AV_CS_RGB_8,
		.bl = PS3AV_CMD_AV_CS_8
	पूर्ण, अणु
		.cs = PS3AV_CMD_VIDEO_CS_RGB_10,
		.av = PS3AV_CMD_AV_CS_RGB_8,
		.bl = PS3AV_CMD_AV_CS_8
	पूर्ण, अणु
		.cs = PS3AV_CMD_VIDEO_CS_RGB_12,
		.av = PS3AV_CMD_AV_CS_RGB_8,
		.bl = PS3AV_CMD_AV_CS_8
	पूर्ण, अणु
		.cs = PS3AV_CMD_VIDEO_CS_YUV444_8,
		.av = PS3AV_CMD_AV_CS_YUV444_8,
		.bl = PS3AV_CMD_AV_CS_8
	पूर्ण, अणु
		.cs = PS3AV_CMD_VIDEO_CS_YUV444_10,
		.av = PS3AV_CMD_AV_CS_YUV444_8,
		.bl = PS3AV_CMD_AV_CS_10
	पूर्ण, अणु
		.cs = PS3AV_CMD_VIDEO_CS_YUV444_12,
		.av = PS3AV_CMD_AV_CS_YUV444_8,
		.bl = PS3AV_CMD_AV_CS_10
	पूर्ण, अणु
		.cs = PS3AV_CMD_VIDEO_CS_YUV422_8,
		.av = PS3AV_CMD_AV_CS_YUV422_8,
		.bl = PS3AV_CMD_AV_CS_10
	पूर्ण, अणु
		.cs = PS3AV_CMD_VIDEO_CS_YUV422_10,
		.av = PS3AV_CMD_AV_CS_YUV422_8,
		.bl = PS3AV_CMD_AV_CS_10
	पूर्ण, अणु
		.cs = PS3AV_CMD_VIDEO_CS_YUV422_12,
		.av = PS3AV_CMD_AV_CS_YUV422_8,
		.bl = PS3AV_CMD_AV_CS_12
	पूर्ण, अणु
		.cs = PS3AV_CMD_VIDEO_CS_XVYCC_8,
		.av = PS3AV_CMD_AV_CS_XVYCC_8,
		.bl = PS3AV_CMD_AV_CS_12
	पूर्ण, अणु
		.cs = PS3AV_CMD_VIDEO_CS_XVYCC_10,
		.av = PS3AV_CMD_AV_CS_XVYCC_8,
		.bl = PS3AV_CMD_AV_CS_12
	पूर्ण, अणु
		.cs = PS3AV_CMD_VIDEO_CS_XVYCC_12,
		.av = PS3AV_CMD_AV_CS_XVYCC_8,
		.bl = PS3AV_CMD_AV_CS_12
	पूर्ण
पूर्ण;

अटल u32 ps3av_cs_video2av(पूर्णांक cs)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ps3av_cs_video2av_table); i++)
		अगर (ps3av_cs_video2av_table[i].cs == cs)
			वापस ps3av_cs_video2av_table[i].av;

	वापस PS3AV_CMD_AV_CS_RGB_8;
पूर्ण

अटल u32 ps3av_cs_video2av_bitlen(पूर्णांक cs)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ps3av_cs_video2av_table); i++)
		अगर (ps3av_cs_video2av_table[i].cs == cs)
			वापस ps3av_cs_video2av_table[i].bl;

	वापस PS3AV_CMD_AV_CS_8;
पूर्ण

अटल स्थिर काष्ठा अणु
	पूर्णांक vid;
	u32 av;
पूर्ण ps3av_vid_video2av_table[] = अणु
	अणु PS3AV_CMD_VIDEO_VID_480I, PS3AV_CMD_AV_VID_480I पूर्ण,
	अणु PS3AV_CMD_VIDEO_VID_480P, PS3AV_CMD_AV_VID_480P पूर्ण,
	अणु PS3AV_CMD_VIDEO_VID_576I, PS3AV_CMD_AV_VID_576I पूर्ण,
	अणु PS3AV_CMD_VIDEO_VID_576P, PS3AV_CMD_AV_VID_576P पूर्ण,
	अणु PS3AV_CMD_VIDEO_VID_1080I_60HZ, PS3AV_CMD_AV_VID_1080I_60HZ पूर्ण,
	अणु PS3AV_CMD_VIDEO_VID_720P_60HZ, PS3AV_CMD_AV_VID_720P_60HZ पूर्ण,
	अणु PS3AV_CMD_VIDEO_VID_1080P_60HZ, PS3AV_CMD_AV_VID_1080P_60HZ पूर्ण,
	अणु PS3AV_CMD_VIDEO_VID_1080I_50HZ, PS3AV_CMD_AV_VID_1080I_50HZ पूर्ण,
	अणु PS3AV_CMD_VIDEO_VID_720P_50HZ, PS3AV_CMD_AV_VID_720P_50HZ पूर्ण,
	अणु PS3AV_CMD_VIDEO_VID_1080P_50HZ, PS3AV_CMD_AV_VID_1080P_50HZ पूर्ण,
	अणु PS3AV_CMD_VIDEO_VID_WXGA, PS3AV_CMD_AV_VID_WXGA पूर्ण,
	अणु PS3AV_CMD_VIDEO_VID_SXGA, PS3AV_CMD_AV_VID_SXGA पूर्ण,
	अणु PS3AV_CMD_VIDEO_VID_WUXGA, PS3AV_CMD_AV_VID_WUXGA पूर्ण
पूर्ण;

अटल u32 ps3av_vid_video2av(पूर्णांक vid)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ps3av_vid_video2av_table); i++)
		अगर (ps3av_vid_video2av_table[i].vid == vid)
			वापस ps3av_vid_video2av_table[i].av;

	वापस PS3AV_CMD_AV_VID_480P;
पूर्ण

अटल पूर्णांक ps3av_hdmi_range(व्योम)
अणु
	अगर (ps3_compare_firmware_version(1, 8, 0) < 0)
		वापस 0;
	अन्यथा
		वापस 1; /* supported */
पूर्ण

पूर्णांक ps3av_cmd_init(व्योम)
अणु
	पूर्णांक res;
	काष्ठा ps3av_pkt_av_init av_init;
	काष्ठा ps3av_pkt_video_init video_init;
	काष्ठा ps3av_pkt_audio_init audio_init;

	/* video init */
	स_रखो(&video_init, 0, माप(video_init));

	res = ps3av_करो_pkt(PS3AV_CID_VIDEO_INIT, माप(video_init.send_hdr),
			   माप(video_init), &video_init.send_hdr);
	अगर (res < 0)
		वापस res;

	res = get_status(&video_init);
	अगर (res) अणु
		prपूर्णांकk(KERN_ERR "PS3AV_CID_VIDEO_INIT: failed %x\n", res);
		वापस res;
	पूर्ण

	/* audio init */
	स_रखो(&audio_init, 0, माप(audio_init));

	res = ps3av_करो_pkt(PS3AV_CID_AUDIO_INIT, माप(audio_init.send_hdr),
			   माप(audio_init), &audio_init.send_hdr);
	अगर (res < 0)
		वापस res;

	res = get_status(&audio_init);
	अगर (res) अणु
		prपूर्णांकk(KERN_ERR "PS3AV_CID_AUDIO_INIT: failed %x\n", res);
		वापस res;
	पूर्ण

	/* av init */
	स_रखो(&av_init, 0, माप(av_init));
	av_init.event_bit = 0;

	res = ps3av_करो_pkt(PS3AV_CID_AV_INIT, माप(av_init), माप(av_init),
			   &av_init.send_hdr);
	अगर (res < 0)
		वापस res;

	res = get_status(&av_init);
	अगर (res)
		prपूर्णांकk(KERN_ERR "PS3AV_CID_AV_INIT: failed %x\n", res);

	वापस res;
पूर्ण

पूर्णांक ps3av_cmd_fin(व्योम)
अणु
	पूर्णांक res;
	काष्ठा ps3av_pkt_av_fin av_fin;

	स_रखो(&av_fin, 0, माप(av_fin));

	res = ps3av_करो_pkt(PS3AV_CID_AV_FIN, माप(av_fin.send_hdr),
			   माप(av_fin), &av_fin.send_hdr);
	अगर (res < 0)
		वापस res;

	res = get_status(&av_fin);
	अगर (res)
		prपूर्णांकk(KERN_ERR "PS3AV_CID_AV_FIN: failed %x\n", res);

	वापस res;
पूर्ण

पूर्णांक ps3av_cmd_av_video_mute(पूर्णांक num_of_port, u32 *port, u32 mute)
अणु
	पूर्णांक i, send_len, res;
	काष्ठा ps3av_pkt_av_video_mute av_video_mute;

	अगर (num_of_port > PS3AV_MUTE_PORT_MAX)
		वापस -EINVAL;

	स_रखो(&av_video_mute, 0, माप(av_video_mute));
	क्रम (i = 0; i < num_of_port; i++) अणु
		av_video_mute.mute[i].avport = port[i];
		av_video_mute.mute[i].mute = mute;
	पूर्ण

	send_len = माप(av_video_mute.send_hdr) +
	    माप(काष्ठा ps3av_av_mute) * num_of_port;
	res = ps3av_करो_pkt(PS3AV_CID_AV_VIDEO_MUTE, send_len,
			   माप(av_video_mute), &av_video_mute.send_hdr);
	अगर (res < 0)
		वापस res;

	res = get_status(&av_video_mute);
	अगर (res)
		prपूर्णांकk(KERN_ERR "PS3AV_CID_AV_VIDEO_MUTE: failed %x\n", res);

	वापस res;
पूर्ण

पूर्णांक ps3av_cmd_av_video_disable_sig(u32 port)
अणु
	पूर्णांक res;
	काष्ठा ps3av_pkt_av_video_disable_sig av_video_sig;

	स_रखो(&av_video_sig, 0, माप(av_video_sig));
	av_video_sig.avport = port;

	res = ps3av_करो_pkt(PS3AV_CID_AV_VIDEO_DISABLE_SIG,
			   माप(av_video_sig), माप(av_video_sig),
			   &av_video_sig.send_hdr);
	अगर (res < 0)
		वापस res;

	res = get_status(&av_video_sig);
	अगर (res)
		prपूर्णांकk(KERN_ERR
		       "PS3AV_CID_AV_VIDEO_DISABLE_SIG: failed %x port:%x\n",
		       res, port);

	वापस res;
पूर्ण

पूर्णांक ps3av_cmd_av_tv_mute(u32 avport, u32 mute)
अणु
	पूर्णांक res;
	काष्ठा ps3av_pkt_av_tv_mute tv_mute;

	स_रखो(&tv_mute, 0, माप(tv_mute));
	tv_mute.avport = avport;
	tv_mute.mute = mute;

	res = ps3av_करो_pkt(PS3AV_CID_AV_TV_MUTE, माप(tv_mute),
			   माप(tv_mute), &tv_mute.send_hdr);
	अगर (res < 0)
		वापस res;

	res = get_status(&tv_mute);
	अगर (res)
		prपूर्णांकk(KERN_ERR "PS3AV_CID_AV_TV_MUTE: failed %x port:%x\n",
		       res, avport);

	वापस res;
पूर्ण

पूर्णांक ps3av_cmd_enable_event(व्योम)
अणु
	पूर्णांक res;
	काष्ठा ps3av_pkt_av_event av_event;

	स_रखो(&av_event, 0, माप(av_event));
	av_event.event_bit = PS3AV_CMD_EVENT_BIT_UNPLUGGED |
	    PS3AV_CMD_EVENT_BIT_PLUGGED | PS3AV_CMD_EVENT_BIT_HDCP_DONE;

	res = ps3av_करो_pkt(PS3AV_CID_AV_ENABLE_EVENT, माप(av_event),
			   माप(av_event), &av_event.send_hdr);
	अगर (res < 0)
		वापस res;

	res = get_status(&av_event);
	अगर (res)
		prपूर्णांकk(KERN_ERR "PS3AV_CID_AV_ENABLE_EVENT: failed %x\n", res);

	वापस res;
पूर्ण

पूर्णांक ps3av_cmd_av_hdmi_mode(u8 mode)
अणु
	पूर्णांक res;
	काष्ठा ps3av_pkt_av_hdmi_mode hdmi_mode;

	स_रखो(&hdmi_mode, 0, माप(hdmi_mode));
	hdmi_mode.mode = mode;

	res = ps3av_करो_pkt(PS3AV_CID_AV_HDMI_MODE, माप(hdmi_mode),
			   माप(hdmi_mode), &hdmi_mode.send_hdr);
	अगर (res < 0)
		वापस res;

	res = get_status(&hdmi_mode);
	अगर (res && res != PS3AV_STATUS_UNSUPPORTED_HDMI_MODE)
		prपूर्णांकk(KERN_ERR "PS3AV_CID_AV_HDMI_MODE: failed %x\n", res);

	वापस res;
पूर्ण

u32 ps3av_cmd_set_av_video_cs(व्योम *p, u32 avport, पूर्णांक video_vid, पूर्णांक cs_out,
			      पूर्णांक aspect, u32 id)
अणु
	काष्ठा ps3av_pkt_av_video_cs *av_video_cs;

	av_video_cs = (काष्ठा ps3av_pkt_av_video_cs *)p;
	अगर (video_vid == -1)
		video_vid = PS3AV_CMD_VIDEO_VID_720P_60HZ;
	अगर (cs_out == -1)
		cs_out = PS3AV_CMD_VIDEO_CS_YUV444_8;
	अगर (aspect == -1)
		aspect = 0;

	स_रखो(av_video_cs, 0, माप(*av_video_cs));
	ps3av_set_hdr(PS3AV_CID_AV_VIDEO_CS, माप(*av_video_cs),
		      &av_video_cs->send_hdr);
	av_video_cs->avport = avport;
	/* should be same as video_mode.resolution */
	av_video_cs->av_vid = ps3av_vid_video2av(video_vid);
	av_video_cs->av_cs_out = ps3av_cs_video2av(cs_out);
	/* should be same as video_mode.video_cs_out */
	av_video_cs->av_cs_in = ps3av_cs_video2av(PS3AV_CMD_VIDEO_CS_RGB_8);
	av_video_cs->bitlen_out = ps3av_cs_video2av_bitlen(cs_out);
	अगर ((id & PS3AV_MODE_WHITE) && ps3av_hdmi_range())
		av_video_cs->super_white = PS3AV_CMD_AV_SUPER_WHITE_ON;
	अन्यथा /* शेष off */
		av_video_cs->super_white = PS3AV_CMD_AV_SUPER_WHITE_OFF;
	av_video_cs->aspect = aspect;
	अगर (id & PS3AV_MODE_DITHER) अणु
		av_video_cs->dither = PS3AV_CMD_AV_DITHER_ON
		    | PS3AV_CMD_AV_DITHER_8BIT;
	पूर्ण अन्यथा अणु
		/* शेष off */
		av_video_cs->dither = PS3AV_CMD_AV_DITHER_OFF;
	पूर्ण

	वापस माप(*av_video_cs);
पूर्ण

u32 ps3av_cmd_set_video_mode(व्योम *p, u32 head, पूर्णांक video_vid, पूर्णांक video_fmt,
			     u32 id)
अणु
	काष्ठा ps3av_pkt_video_mode *video_mode;
	u32 x, y;

	video_mode = (काष्ठा ps3av_pkt_video_mode *)p;
	अगर (video_vid == -1)
		video_vid = PS3AV_CMD_VIDEO_VID_720P_60HZ;
	अगर (video_fmt == -1)
		video_fmt = PS3AV_CMD_VIDEO_FMT_X8R8G8B8;

	अगर (ps3av_video_mode2res(id, &x, &y))
		वापस 0;

	/* video mode */
	स_रखो(video_mode, 0, माप(*video_mode));
	ps3av_set_hdr(PS3AV_CID_VIDEO_MODE, माप(*video_mode),
		      &video_mode->send_hdr);
	video_mode->video_head = head;
	अगर (video_vid == PS3AV_CMD_VIDEO_VID_480I
	    && head == PS3AV_CMD_VIDEO_HEAD_B)
		video_mode->video_vid = PS3AV_CMD_VIDEO_VID_480I_A;
	अन्यथा
		video_mode->video_vid = video_vid;
	video_mode->width = (u16) x;
	video_mode->height = (u16) y;
	video_mode->pitch = video_mode->width * 4;	/* line_length */
	video_mode->video_out_क्रमmat = PS3AV_CMD_VIDEO_OUT_FORMAT_RGB_12BIT;
	video_mode->video_क्रमmat = ps3av_video_fmt_table[video_fmt].क्रमmat;
	अगर ((id & PS3AV_MODE_COLOR) && ps3av_hdmi_range())
		video_mode->video_cl_cnv = PS3AV_CMD_VIDEO_CL_CNV_DISABLE_LUT;
	अन्यथा /* शेष enable */
		video_mode->video_cl_cnv = PS3AV_CMD_VIDEO_CL_CNV_ENABLE_LUT;
	video_mode->video_order = ps3av_video_fmt_table[video_fmt].order;

	pr_debug("%s: video_mode:vid:%x width:%d height:%d pitch:%d out_format:%d format:%x order:%x\n",
		__func__, video_vid, video_mode->width, video_mode->height,
		video_mode->pitch, video_mode->video_out_क्रमmat,
		video_mode->video_क्रमmat, video_mode->video_order);
	वापस माप(*video_mode);
पूर्ण

पूर्णांक ps3av_cmd_video_क्रमmat_black(u32 head, u32 video_fmt, u32 mute)
अणु
	पूर्णांक res;
	काष्ठा ps3av_pkt_video_क्रमmat video_क्रमmat;

	स_रखो(&video_क्रमmat, 0, माप(video_क्रमmat));
	video_क्रमmat.video_head = head;
	अगर (mute != PS3AV_CMD_MUTE_OFF)
		video_क्रमmat.video_क्रमmat = PS3AV_CMD_VIDEO_FORMAT_BLACK;
	अन्यथा
		video_क्रमmat.video_क्रमmat =
		    ps3av_video_fmt_table[video_fmt].क्रमmat;
	video_क्रमmat.video_order = ps3av_video_fmt_table[video_fmt].order;

	res = ps3av_करो_pkt(PS3AV_CID_VIDEO_FORMAT, माप(video_क्रमmat),
			   माप(video_क्रमmat), &video_क्रमmat.send_hdr);
	अगर (res < 0)
		वापस res;

	res = get_status(&video_क्रमmat);
	अगर (res)
		prपूर्णांकk(KERN_ERR "PS3AV_CID_VIDEO_FORMAT: failed %x\n", res);

	वापस res;
पूर्ण


पूर्णांक ps3av_cmd_av_audio_mute(पूर्णांक num_of_port, u32 *port, u32 mute)
अणु
	पूर्णांक i, res;
	काष्ठा ps3av_pkt_av_audio_mute av_audio_mute;

	अगर (num_of_port > PS3AV_MUTE_PORT_MAX)
		वापस -EINVAL;

	/* audio mute */
	स_रखो(&av_audio_mute, 0, माप(av_audio_mute));
	क्रम (i = 0; i < num_of_port; i++) अणु
		av_audio_mute.mute[i].avport = port[i];
		av_audio_mute.mute[i].mute = mute;
	पूर्ण

	res = ps3av_करो_pkt(PS3AV_CID_AV_AUDIO_MUTE,
			   माप(av_audio_mute.send_hdr) +
			   माप(काष्ठा ps3av_av_mute) * num_of_port,
			   माप(av_audio_mute), &av_audio_mute.send_hdr);
	अगर (res < 0)
		वापस res;

	res = get_status(&av_audio_mute);
	अगर (res)
		prपूर्णांकk(KERN_ERR "PS3AV_CID_AV_AUDIO_MUTE: failed %x\n", res);

	वापस res;
पूर्ण

अटल स्थिर काष्ठा अणु
	u32 fs;
	u8 mclk;
पूर्ण ps3av_cnv_mclk_table[] = अणु
	अणु PS3AV_CMD_AUDIO_FS_44K, PS3AV_CMD_AV_MCLK_512 पूर्ण,
	अणु PS3AV_CMD_AUDIO_FS_48K, PS3AV_CMD_AV_MCLK_512 पूर्ण,
	अणु PS3AV_CMD_AUDIO_FS_88K, PS3AV_CMD_AV_MCLK_256 पूर्ण,
	अणु PS3AV_CMD_AUDIO_FS_96K, PS3AV_CMD_AV_MCLK_256 पूर्ण,
	अणु PS3AV_CMD_AUDIO_FS_176K, PS3AV_CMD_AV_MCLK_128 पूर्ण,
	अणु PS3AV_CMD_AUDIO_FS_192K, PS3AV_CMD_AV_MCLK_128 पूर्ण
पूर्ण;

अटल u8 ps3av_cnv_mclk(u32 fs)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ps3av_cnv_mclk_table); i++)
		अगर (ps3av_cnv_mclk_table[i].fs == fs)
			वापस ps3av_cnv_mclk_table[i].mclk;

	prपूर्णांकk(KERN_ERR "%s failed, fs:%x\n", __func__, fs);
	वापस 0;
पूर्ण

#घोषणा BASE	PS3AV_CMD_AUDIO_FS_44K

अटल स्थिर u32 ps3av_ns_table[][5] = अणु
					/*   D1,    D2,    D3,    D4,    D5 */
	[PS3AV_CMD_AUDIO_FS_44K-BASE] =	अणु  6272,  6272, 17836, 17836,  8918 पूर्ण,
	[PS3AV_CMD_AUDIO_FS_48K-BASE] =	अणु  6144,  6144, 11648, 11648,  5824 पूर्ण,
	[PS3AV_CMD_AUDIO_FS_88K-BASE] =	अणु 12544, 12544, 35672, 35672, 17836 पूर्ण,
	[PS3AV_CMD_AUDIO_FS_96K-BASE] =	अणु 12288, 12288, 23296, 23296, 11648 पूर्ण,
	[PS3AV_CMD_AUDIO_FS_176K-BASE] =	अणु 25088, 25088, 71344, 71344, 35672 पूर्ण,
	[PS3AV_CMD_AUDIO_FS_192K-BASE] =	अणु 24576, 24576, 46592, 46592, 23296 पूर्ण
पूर्ण;

अटल व्योम ps3av_cnv_ns(u8 *ns, u32 fs, u32 video_vid)
अणु
	u32 av_vid, ns_val;
	पूर्णांक d;

	d = ns_val = 0;
	av_vid = ps3av_vid_video2av(video_vid);
	चयन (av_vid) अणु
	हाल PS3AV_CMD_AV_VID_480I:
	हाल PS3AV_CMD_AV_VID_576I:
		d = 0;
		अवरोध;
	हाल PS3AV_CMD_AV_VID_480P:
	हाल PS3AV_CMD_AV_VID_576P:
		d = 1;
		अवरोध;
	हाल PS3AV_CMD_AV_VID_1080I_60HZ:
	हाल PS3AV_CMD_AV_VID_1080I_50HZ:
		d = 2;
		अवरोध;
	हाल PS3AV_CMD_AV_VID_720P_60HZ:
	हाल PS3AV_CMD_AV_VID_720P_50HZ:
		d = 3;
		अवरोध;
	हाल PS3AV_CMD_AV_VID_1080P_60HZ:
	हाल PS3AV_CMD_AV_VID_1080P_50HZ:
	हाल PS3AV_CMD_AV_VID_WXGA:
	हाल PS3AV_CMD_AV_VID_SXGA:
	हाल PS3AV_CMD_AV_VID_WUXGA:
		d = 4;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s failed, vid:%x\n", __func__, video_vid);
		अवरोध;
	पूर्ण

	अगर (fs < PS3AV_CMD_AUDIO_FS_44K || fs > PS3AV_CMD_AUDIO_FS_192K)
		prपूर्णांकk(KERN_ERR "%s failed, fs:%x\n", __func__, fs);
	अन्यथा
		ns_val = ps3av_ns_table[PS3AV_CMD_AUDIO_FS_44K-BASE][d];

	*ns++ = ns_val & 0x000000FF;
	*ns++ = (ns_val & 0x0000FF00) >> 8;
	*ns = (ns_val & 0x00FF0000) >> 16;
पूर्ण

#अघोषित BASE

अटल u8 ps3av_cnv_enable(u32 source, स्थिर u8 *enable)
अणु
	u8 ret = 0;

	अगर (source == PS3AV_CMD_AUDIO_SOURCE_SPDIF) अणु
		ret = 0x03;
	पूर्ण अन्यथा अगर (source == PS3AV_CMD_AUDIO_SOURCE_SERIAL) अणु
		ret = ((enable[0] << 4) + (enable[1] << 5) + (enable[2] << 6) +
		       (enable[3] << 7)) | 0x01;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR "%s failed, source:%x\n", __func__, source);
	वापस ret;
पूर्ण

अटल u8 ps3av_cnv_fअगरomap(स्थिर u8 *map)
अणु
	u8 ret = 0;

	ret = map[0] + (map[1] << 2) + (map[2] << 4) + (map[3] << 6);
	वापस ret;
पूर्ण

अटल u8 ps3av_cnv_inputlen(u32 word_bits)
अणु
	u8 ret = 0;

	चयन (word_bits) अणु
	हाल PS3AV_CMD_AUDIO_WORD_BITS_16:
		ret = PS3AV_CMD_AV_INPUTLEN_16;
		अवरोध;
	हाल PS3AV_CMD_AUDIO_WORD_BITS_20:
		ret = PS3AV_CMD_AV_INPUTLEN_20;
		अवरोध;
	हाल PS3AV_CMD_AUDIO_WORD_BITS_24:
		ret = PS3AV_CMD_AV_INPUTLEN_24;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s failed, word_bits:%x\n", __func__,
		       word_bits);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल u8 ps3av_cnv_layout(u32 num_of_ch)
अणु
	अगर (num_of_ch > PS3AV_CMD_AUDIO_NUM_OF_CH_8) अणु
		prपूर्णांकk(KERN_ERR "%s failed, num_of_ch:%x\n", __func__,
		       num_of_ch);
		वापस 0;
	पूर्ण

	वापस num_of_ch == PS3AV_CMD_AUDIO_NUM_OF_CH_2 ? 0x0 : 0x1;
पूर्ण

अटल व्योम ps3av_cnv_info(काष्ठा ps3av_audio_info_frame *info,
			   स्थिर काष्ठा ps3av_pkt_audio_mode *mode)
अणु
	info->pb1.cc = mode->audio_num_of_ch + 1;	/* CH2:0x01 --- CH8:0x07 */
	info->pb1.ct = 0;
	info->pb2.sf = 0;
	info->pb2.ss = 0;

	info->pb3 = 0;		/* check mode->audio_क्रमmat ?? */
	info->pb4 = mode->audio_layout;
	info->pb5.dm = mode->audio_करोwnmix;
	info->pb5.lsv = mode->audio_करोwnmix_level;
पूर्ण

अटल व्योम ps3av_cnv_chstat(u8 *chstat, स्थिर u8 *cs_info)
अणु
	स_नकल(chstat, cs_info, 5);
पूर्ण

u32 ps3av_cmd_set_av_audio_param(व्योम *p, u32 port,
				 स्थिर काष्ठा ps3av_pkt_audio_mode *audio_mode,
				 u32 video_vid)
अणु
	काष्ठा ps3av_pkt_av_audio_param *param;

	param = (काष्ठा ps3av_pkt_av_audio_param *)p;

	स_रखो(param, 0, माप(*param));
	ps3av_set_hdr(PS3AV_CID_AV_AUDIO_PARAM, माप(*param),
		      &param->send_hdr);

	param->avport = port;
	param->mclk = ps3av_cnv_mclk(audio_mode->audio_fs) | 0x80;
	ps3av_cnv_ns(param->ns, audio_mode->audio_fs, video_vid);
	param->enable = ps3av_cnv_enable(audio_mode->audio_source,
					 audio_mode->audio_enable);
	param->swaplr = 0x09;
	param->fअगरomap = ps3av_cnv_fअगरomap(audio_mode->audio_map);
	param->inअ_दोtrl = 0x49;
	param->inputlen = ps3av_cnv_inputlen(audio_mode->audio_word_bits);
	param->layout = ps3av_cnv_layout(audio_mode->audio_num_of_ch);
	ps3av_cnv_info(&param->info, audio_mode);
	ps3av_cnv_chstat(param->chstat, audio_mode->audio_cs_info);

	वापस माप(*param);
पूर्ण

/* शेष cs val */
u8 ps3av_mode_cs_info[] = अणु
	0x00, 0x09, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00
पूर्ण;
EXPORT_SYMBOL_GPL(ps3av_mode_cs_info);

#घोषणा CS_44	0x00
#घोषणा CS_48	0x02
#घोषणा CS_88	0x08
#घोषणा CS_96	0x0a
#घोषणा CS_176	0x0c
#घोषणा CS_192	0x0e
#घोषणा CS_MASK	0x0f
#घोषणा CS_BIT	0x40

व्योम ps3av_cmd_set_audio_mode(काष्ठा ps3av_pkt_audio_mode *audio, u32 avport,
			      u32 ch, u32 fs, u32 word_bits, u32 क्रमmat,
			      u32 source)
अणु
	पूर्णांक spdअगर_through;
	पूर्णांक i;

	अगर (!(ch | fs | क्रमmat | word_bits | source)) अणु
		ch = PS3AV_CMD_AUDIO_NUM_OF_CH_2;
		fs = PS3AV_CMD_AUDIO_FS_48K;
		word_bits = PS3AV_CMD_AUDIO_WORD_BITS_16;
		क्रमmat = PS3AV_CMD_AUDIO_FORMAT_PCM;
		source = PS3AV_CMD_AUDIO_SOURCE_SERIAL;
	पूर्ण

	/* audio mode */
	स_रखो(audio, 0, माप(*audio));
	ps3av_set_hdr(PS3AV_CID_AUDIO_MODE, माप(*audio), &audio->send_hdr);

	audio->avport = (u8) avport;
	audio->mask = 0x0FFF;	/* XXX set all */
	audio->audio_num_of_ch = ch;
	audio->audio_fs = fs;
	audio->audio_word_bits = word_bits;
	audio->audio_क्रमmat = क्रमmat;
	audio->audio_source = source;

	चयन (ch) अणु
	हाल PS3AV_CMD_AUDIO_NUM_OF_CH_8:
		audio->audio_enable[3] = 1;
		fallthrough;
	हाल PS3AV_CMD_AUDIO_NUM_OF_CH_6:
		audio->audio_enable[2] = 1;
		audio->audio_enable[1] = 1;
		fallthrough;
	हाल PS3AV_CMD_AUDIO_NUM_OF_CH_2:
	शेष:
		audio->audio_enable[0] = 1;
	पूर्ण

	/* audio swap L/R */
	क्रम (i = 0; i < 4; i++)
		audio->audio_swap[i] = PS3AV_CMD_AUDIO_SWAP_0;	/* no swap */

	/* audio serial input mapping */
	audio->audio_map[0] = PS3AV_CMD_AUDIO_MAP_OUTPUT_0;
	audio->audio_map[1] = PS3AV_CMD_AUDIO_MAP_OUTPUT_1;
	audio->audio_map[2] = PS3AV_CMD_AUDIO_MAP_OUTPUT_2;
	audio->audio_map[3] = PS3AV_CMD_AUDIO_MAP_OUTPUT_3;

	/* audio speaker layout */
	अगर (avport == PS3AV_CMD_AVPORT_HDMI_0 ||
	    avport == PS3AV_CMD_AVPORT_HDMI_1) अणु
		चयन (ch) अणु
		हाल PS3AV_CMD_AUDIO_NUM_OF_CH_8:
			audio->audio_layout = PS3AV_CMD_AUDIO_LAYOUT_8CH;
			अवरोध;
		हाल PS3AV_CMD_AUDIO_NUM_OF_CH_6:
			audio->audio_layout = PS3AV_CMD_AUDIO_LAYOUT_6CH;
			अवरोध;
		हाल PS3AV_CMD_AUDIO_NUM_OF_CH_2:
		शेष:
			audio->audio_layout = PS3AV_CMD_AUDIO_LAYOUT_2CH;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		audio->audio_layout = PS3AV_CMD_AUDIO_LAYOUT_2CH;
	पूर्ण

	/* audio करोwnmix permission */
	audio->audio_करोwnmix = PS3AV_CMD_AUDIO_DOWNMIX_PERMITTED;
	/* audio करोwnmix level shअगरt (0:0dB to 15:15dB) */
	audio->audio_करोwnmix_level = 0;	/* 0dB */

	/* set ch status */
	क्रम (i = 0; i < 8; i++)
		audio->audio_cs_info[i] = ps3av_mode_cs_info[i];

	चयन (fs) अणु
	हाल PS3AV_CMD_AUDIO_FS_44K:
		audio->audio_cs_info[3] &= ~CS_MASK;
		audio->audio_cs_info[3] |= CS_44;
		अवरोध;
	हाल PS3AV_CMD_AUDIO_FS_88K:
		audio->audio_cs_info[3] &= ~CS_MASK;
		audio->audio_cs_info[3] |= CS_88;
		अवरोध;
	हाल PS3AV_CMD_AUDIO_FS_96K:
		audio->audio_cs_info[3] &= ~CS_MASK;
		audio->audio_cs_info[3] |= CS_96;
		अवरोध;
	हाल PS3AV_CMD_AUDIO_FS_176K:
		audio->audio_cs_info[3] &= ~CS_MASK;
		audio->audio_cs_info[3] |= CS_176;
		अवरोध;
	हाल PS3AV_CMD_AUDIO_FS_192K:
		audio->audio_cs_info[3] &= ~CS_MASK;
		audio->audio_cs_info[3] |= CS_192;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* non-audio bit */
	spdअगर_through = audio->audio_cs_info[0] & 0x02;

	/* pass through setting */
	अगर (spdअगर_through &&
	    (avport == PS3AV_CMD_AVPORT_SPDIF_0 ||
	     avport == PS3AV_CMD_AVPORT_SPDIF_1 ||
	     avport == PS3AV_CMD_AVPORT_HDMI_0 ||
	     avport == PS3AV_CMD_AVPORT_HDMI_1)) अणु
		audio->audio_word_bits = PS3AV_CMD_AUDIO_WORD_BITS_16;
		audio->audio_क्रमmat = PS3AV_CMD_AUDIO_FORMAT_BITSTREAM;
	पूर्ण
पूर्ण

पूर्णांक ps3av_cmd_audio_mode(काष्ठा ps3av_pkt_audio_mode *audio_mode)
अणु
	पूर्णांक res;

	res = ps3av_करो_pkt(PS3AV_CID_AUDIO_MODE, माप(*audio_mode),
			   माप(*audio_mode), &audio_mode->send_hdr);
	अगर (res < 0)
		वापस res;

	res = get_status(audio_mode);
	अगर (res)
		prपूर्णांकk(KERN_ERR "PS3AV_CID_AUDIO_MODE: failed %x\n", res);

	वापस res;
पूर्ण

पूर्णांक ps3av_cmd_audio_mute(पूर्णांक num_of_port, u32 *port, u32 mute)
अणु
	पूर्णांक i, res;
	काष्ठा ps3av_pkt_audio_mute audio_mute;

	अगर (num_of_port > PS3AV_OPT_PORT_MAX)
		वापस -EINVAL;

	/* audio mute */
	स_रखो(&audio_mute, 0, माप(audio_mute));
	क्रम (i = 0; i < num_of_port; i++) अणु
		audio_mute.mute[i].avport = port[i];
		audio_mute.mute[i].mute = mute;
	पूर्ण

	res = ps3av_करो_pkt(PS3AV_CID_AUDIO_MUTE,
			   माप(audio_mute.send_hdr) +
			   माप(काष्ठा ps3av_audio_mute) * num_of_port,
			   माप(audio_mute), &audio_mute.send_hdr);
	अगर (res < 0)
		वापस res;

	res = get_status(&audio_mute);
	अगर (res)
		prपूर्णांकk(KERN_ERR "PS3AV_CID_AUDIO_MUTE: failed %x\n", res);

	वापस res;
पूर्ण

पूर्णांक ps3av_cmd_audio_active(पूर्णांक active, u32 port)
अणु
	पूर्णांक res;
	काष्ठा ps3av_pkt_audio_active audio_active;
	u32 cid;

	/* audio active */
	स_रखो(&audio_active, 0, माप(audio_active));
	audio_active.audio_port = port;
	cid = active ? PS3AV_CID_AUDIO_ACTIVE : PS3AV_CID_AUDIO_INACTIVE;

	res = ps3av_करो_pkt(cid, माप(audio_active), माप(audio_active),
			   &audio_active.send_hdr);
	अगर (res < 0)
		वापस res;

	res = get_status(&audio_active);
	अगर (res)
		prपूर्णांकk(KERN_ERR "PS3AV_CID_AUDIO_ACTIVE:%x failed %x\n", cid,
		       res);

	वापस res;
पूर्ण

पूर्णांक ps3av_cmd_avb_param(काष्ठा ps3av_pkt_avb_param *avb, u32 send_len)
अणु
	पूर्णांक res;

	mutex_lock(&ps3_gpu_mutex);

	/* avb packet */
	res = ps3av_करो_pkt(PS3AV_CID_AVB_PARAM, send_len, माप(*avb),
			   &avb->send_hdr);
	अगर (res < 0)
		जाओ out;

	res = get_status(avb);
	अगर (res)
		pr_debug("%s: PS3AV_CID_AVB_PARAM: failed %x\n", __func__,
			 res);

      out:
	mutex_unlock(&ps3_gpu_mutex);
	वापस res;
पूर्ण

पूर्णांक ps3av_cmd_av_get_hw_conf(काष्ठा ps3av_pkt_av_get_hw_conf *hw_conf)
अणु
	पूर्णांक res;

	स_रखो(hw_conf, 0, माप(*hw_conf));

	res = ps3av_करो_pkt(PS3AV_CID_AV_GET_HW_CONF, माप(hw_conf->send_hdr),
			   माप(*hw_conf), &hw_conf->send_hdr);
	अगर (res < 0)
		वापस res;

	res = get_status(hw_conf);
	अगर (res)
		prपूर्णांकk(KERN_ERR "PS3AV_CID_AV_GET_HW_CONF: failed %x\n", res);

	वापस res;
पूर्ण

पूर्णांक ps3av_cmd_video_get_monitor_info(काष्ठा ps3av_pkt_av_get_monitor_info *info,
				     u32 avport)
अणु
	पूर्णांक res;

	स_रखो(info, 0, माप(*info));
	info->avport = avport;

	res = ps3av_करो_pkt(PS3AV_CID_AV_GET_MONITOR_INFO,
			   माप(info->send_hdr) + माप(info->avport) +
			   माप(info->reserved),
			   माप(*info), &info->send_hdr);
	अगर (res < 0)
		वापस res;

	res = get_status(info);
	अगर (res)
		prपूर्णांकk(KERN_ERR "PS3AV_CID_AV_GET_MONITOR_INFO: failed %x\n",
		       res);

	वापस res;
पूर्ण

#घोषणा PS3AV_AV_LAYOUT_0 (PS3AV_CMD_AV_LAYOUT_32 \
		| PS3AV_CMD_AV_LAYOUT_44 \
		| PS3AV_CMD_AV_LAYOUT_48)

#घोषणा PS3AV_AV_LAYOUT_1 (PS3AV_AV_LAYOUT_0 \
		| PS3AV_CMD_AV_LAYOUT_88 \
		| PS3AV_CMD_AV_LAYOUT_96 \
		| PS3AV_CMD_AV_LAYOUT_176 \
		| PS3AV_CMD_AV_LAYOUT_192)

