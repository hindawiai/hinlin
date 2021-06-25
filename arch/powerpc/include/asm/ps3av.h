<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  PS3 AV backend support.
 *
 *  Copyright (C) 2007 Sony Computer Entertainment Inc.
 *  Copyright 2007 Sony Corp.
 */

#अगर_अघोषित _ASM_POWERPC_PS3AV_H_
#घोषणा _ASM_POWERPC_PS3AV_H_

/** command क्रम ioctl() **/
#घोषणा PS3AV_VERSION 0x205	/* version of ps3av command */

#घोषणा PS3AV_CID_AV_INIT              0x00000001
#घोषणा PS3AV_CID_AV_FIN               0x00000002
#घोषणा PS3AV_CID_AV_GET_HW_CONF       0x00000003
#घोषणा PS3AV_CID_AV_GET_MONITOR_INFO  0x00000004
#घोषणा PS3AV_CID_AV_ENABLE_EVENT      0x00000006
#घोषणा PS3AV_CID_AV_DISABLE_EVENT     0x00000007
#घोषणा PS3AV_CID_AV_TV_MUTE           0x0000000a

#घोषणा PS3AV_CID_AV_VIDEO_CS          0x00010001
#घोषणा PS3AV_CID_AV_VIDEO_MUTE        0x00010002
#घोषणा PS3AV_CID_AV_VIDEO_DISABLE_SIG 0x00010003
#घोषणा PS3AV_CID_AV_AUDIO_PARAM       0x00020001
#घोषणा PS3AV_CID_AV_AUDIO_MUTE        0x00020002
#घोषणा PS3AV_CID_AV_HDMI_MODE         0x00040001

#घोषणा PS3AV_CID_VIDEO_INIT           0x01000001
#घोषणा PS3AV_CID_VIDEO_MODE           0x01000002
#घोषणा PS3AV_CID_VIDEO_FORMAT         0x01000004
#घोषणा PS3AV_CID_VIDEO_PITCH          0x01000005

#घोषणा PS3AV_CID_AUDIO_INIT           0x02000001
#घोषणा PS3AV_CID_AUDIO_MODE           0x02000002
#घोषणा PS3AV_CID_AUDIO_MUTE           0x02000003
#घोषणा PS3AV_CID_AUDIO_ACTIVE         0x02000004
#घोषणा PS3AV_CID_AUDIO_INACTIVE       0x02000005
#घोषणा PS3AV_CID_AUDIO_SPDIF_BIT      0x02000006
#घोषणा PS3AV_CID_AUDIO_CTRL           0x02000007

#घोषणा PS3AV_CID_EVENT_UNPLUGGED      0x10000001
#घोषणा PS3AV_CID_EVENT_PLUGGED        0x10000002
#घोषणा PS3AV_CID_EVENT_HDCP_DONE      0x10000003
#घोषणा PS3AV_CID_EVENT_HDCP_FAIL      0x10000004
#घोषणा PS3AV_CID_EVENT_HDCP_AUTH      0x10000005
#घोषणा PS3AV_CID_EVENT_HDCP_ERROR     0x10000006

#घोषणा PS3AV_CID_AVB_PARAM            0x04000001

/* max backend ports */
#घोषणा PS3AV_HDMI_MAX                 2	/* HDMI_0 HDMI_1 */
#घोषणा PS3AV_AVMULTI_MAX              1	/* AVMULTI_0 */
#घोषणा PS3AV_AV_PORT_MAX              (PS3AV_HDMI_MAX + PS3AV_AVMULTI_MAX)
#घोषणा PS3AV_OPT_PORT_MAX             1	/* SPDIF0 */
#घोषणा PS3AV_HEAD_MAX                 2	/* HEAD_A HEAD_B */

/* num of pkt क्रम PS3AV_CID_AVB_PARAM */
#घोषणा PS3AV_AVB_NUM_VIDEO            PS3AV_HEAD_MAX
#घोषणा PS3AV_AVB_NUM_AUDIO            0	/* not supported */
#घोषणा PS3AV_AVB_NUM_AV_VIDEO         PS3AV_AV_PORT_MAX
#घोषणा PS3AV_AVB_NUM_AV_AUDIO         PS3AV_HDMI_MAX

#घोषणा PS3AV_MUTE_PORT_MAX            1	/* num of ports in mute pkt */

/* event_bit */
#घोषणा PS3AV_CMD_EVENT_BIT_UNPLUGGED			(1 << 0)
#घोषणा PS3AV_CMD_EVENT_BIT_PLUGGED			(1 << 1)
#घोषणा PS3AV_CMD_EVENT_BIT_HDCP_DONE			(1 << 2)
#घोषणा PS3AV_CMD_EVENT_BIT_HDCP_FAIL			(1 << 3)
#घोषणा PS3AV_CMD_EVENT_BIT_HDCP_REAUTH			(1 << 4)
#घोषणा PS3AV_CMD_EVENT_BIT_HDCP_TOPOLOGY		(1 << 5)

/* common params */
/* mute */
#घोषणा PS3AV_CMD_MUTE_OFF				0x0000
#घोषणा PS3AV_CMD_MUTE_ON				0x0001
/* avport */
#घोषणा PS3AV_CMD_AVPORT_HDMI_0				0x0000
#घोषणा PS3AV_CMD_AVPORT_HDMI_1				0x0001
#घोषणा PS3AV_CMD_AVPORT_AVMULTI_0			0x0010
#घोषणा PS3AV_CMD_AVPORT_SPDIF_0			0x0020
#घोषणा PS3AV_CMD_AVPORT_SPDIF_1			0x0021

/* क्रम av backend */
/* av_mclk */
#घोषणा PS3AV_CMD_AV_MCLK_128				0x0000
#घोषणा PS3AV_CMD_AV_MCLK_256				0x0001
#घोषणा PS3AV_CMD_AV_MCLK_512				0x0003
/* av_inputlen */
#घोषणा PS3AV_CMD_AV_INPUTLEN_16			0x02
#घोषणा PS3AV_CMD_AV_INPUTLEN_20			0x0a
#घोषणा PS3AV_CMD_AV_INPUTLEN_24			0x0b
/* av_layout */
#घोषणा PS3AV_CMD_AV_LAYOUT_32				(1 << 0)
#घोषणा PS3AV_CMD_AV_LAYOUT_44				(1 << 1)
#घोषणा PS3AV_CMD_AV_LAYOUT_48				(1 << 2)
#घोषणा PS3AV_CMD_AV_LAYOUT_88				(1 << 3)
#घोषणा PS3AV_CMD_AV_LAYOUT_96				(1 << 4)
#घोषणा PS3AV_CMD_AV_LAYOUT_176				(1 << 5)
#घोषणा PS3AV_CMD_AV_LAYOUT_192				(1 << 6)
/* hdmi_mode */
#घोषणा PS3AV_CMD_AV_HDMI_MODE_NORMAL			0xff
#घोषणा PS3AV_CMD_AV_HDMI_HDCP_OFF			0x01
#घोषणा PS3AV_CMD_AV_HDMI_EDID_PASS			0x80
#घोषणा PS3AV_CMD_AV_HDMI_DVI				0x40

/* क्रम video module */
/* video_head */
#घोषणा PS3AV_CMD_VIDEO_HEAD_A				0x0000
#घोषणा PS3AV_CMD_VIDEO_HEAD_B				0x0001
/* video_cs_out video_cs_in */
#घोषणा PS3AV_CMD_VIDEO_CS_NONE				0x0000
#घोषणा PS3AV_CMD_VIDEO_CS_RGB_8			0x0001
#घोषणा PS3AV_CMD_VIDEO_CS_YUV444_8			0x0002
#घोषणा PS3AV_CMD_VIDEO_CS_YUV422_8			0x0003
#घोषणा PS3AV_CMD_VIDEO_CS_XVYCC_8			0x0004
#घोषणा PS3AV_CMD_VIDEO_CS_RGB_10			0x0005
#घोषणा PS3AV_CMD_VIDEO_CS_YUV444_10			0x0006
#घोषणा PS3AV_CMD_VIDEO_CS_YUV422_10			0x0007
#घोषणा PS3AV_CMD_VIDEO_CS_XVYCC_10			0x0008
#घोषणा PS3AV_CMD_VIDEO_CS_RGB_12			0x0009
#घोषणा PS3AV_CMD_VIDEO_CS_YUV444_12			0x000a
#घोषणा PS3AV_CMD_VIDEO_CS_YUV422_12			0x000b
#घोषणा PS3AV_CMD_VIDEO_CS_XVYCC_12			0x000c
/* video_vid */
#घोषणा PS3AV_CMD_VIDEO_VID_NONE			0x0000
#घोषणा PS3AV_CMD_VIDEO_VID_480I			0x0001
#घोषणा PS3AV_CMD_VIDEO_VID_576I			0x0003
#घोषणा PS3AV_CMD_VIDEO_VID_480P			0x0005
#घोषणा PS3AV_CMD_VIDEO_VID_576P			0x0006
#घोषणा PS3AV_CMD_VIDEO_VID_1080I_60HZ			0x0007
#घोषणा PS3AV_CMD_VIDEO_VID_1080I_50HZ			0x0008
#घोषणा PS3AV_CMD_VIDEO_VID_720P_60HZ			0x0009
#घोषणा PS3AV_CMD_VIDEO_VID_720P_50HZ			0x000a
#घोषणा PS3AV_CMD_VIDEO_VID_1080P_60HZ			0x000b
#घोषणा PS3AV_CMD_VIDEO_VID_1080P_50HZ			0x000c
#घोषणा PS3AV_CMD_VIDEO_VID_WXGA			0x000d
#घोषणा PS3AV_CMD_VIDEO_VID_SXGA			0x000e
#घोषणा PS3AV_CMD_VIDEO_VID_WUXGA			0x000f
#घोषणा PS3AV_CMD_VIDEO_VID_480I_A			0x0010
/* video_क्रमmat */
#घोषणा PS3AV_CMD_VIDEO_FORMAT_BLACK			0x0000
#घोषणा PS3AV_CMD_VIDEO_FORMAT_ARGB_8BIT		0x0007
/* video_order */
#घोषणा PS3AV_CMD_VIDEO_ORDER_RGB			0x0000
#घोषणा PS3AV_CMD_VIDEO_ORDER_BGR			0x0001
/* video_fmt */
#घोषणा PS3AV_CMD_VIDEO_FMT_X8R8G8B8			0x0000
/* video_out_क्रमmat */
#घोषणा PS3AV_CMD_VIDEO_OUT_FORMAT_RGB_12BIT		0x0000
/* video_cl_cnv */
#घोषणा PS3AV_CMD_VIDEO_CL_CNV_ENABLE_LUT		0x0000
#घोषणा PS3AV_CMD_VIDEO_CL_CNV_DISABLE_LUT		0x0010
/* video_sync */
#घोषणा PS3AV_CMD_VIDEO_SYNC_VSYNC			0x0001
#घोषणा PS3AV_CMD_VIDEO_SYNC_CSYNC			0x0004
#घोषणा PS3AV_CMD_VIDEO_SYNC_HSYNC			0x0010

/* क्रम audio module */
/* num_of_ch */
#घोषणा PS3AV_CMD_AUDIO_NUM_OF_CH_2			0x0000
#घोषणा PS3AV_CMD_AUDIO_NUM_OF_CH_3			0x0001
#घोषणा PS3AV_CMD_AUDIO_NUM_OF_CH_4			0x0002
#घोषणा PS3AV_CMD_AUDIO_NUM_OF_CH_5			0x0003
#घोषणा PS3AV_CMD_AUDIO_NUM_OF_CH_6			0x0004
#घोषणा PS3AV_CMD_AUDIO_NUM_OF_CH_7			0x0005
#घोषणा PS3AV_CMD_AUDIO_NUM_OF_CH_8			0x0006
/* audio_fs */
#घोषणा PS3AV_CMD_AUDIO_FS_32K				0x0001
#घोषणा PS3AV_CMD_AUDIO_FS_44K				0x0002
#घोषणा PS3AV_CMD_AUDIO_FS_48K				0x0003
#घोषणा PS3AV_CMD_AUDIO_FS_88K				0x0004
#घोषणा PS3AV_CMD_AUDIO_FS_96K				0x0005
#घोषणा PS3AV_CMD_AUDIO_FS_176K				0x0006
#घोषणा PS3AV_CMD_AUDIO_FS_192K				0x0007
/* audio_word_bits */
#घोषणा PS3AV_CMD_AUDIO_WORD_BITS_16			0x0001
#घोषणा PS3AV_CMD_AUDIO_WORD_BITS_20			0x0002
#घोषणा PS3AV_CMD_AUDIO_WORD_BITS_24			0x0003
/* audio_क्रमmat */
#घोषणा PS3AV_CMD_AUDIO_FORMAT_PCM			0x0001
#घोषणा PS3AV_CMD_AUDIO_FORMAT_BITSTREAM		0x00ff
/* audio_source */
#घोषणा PS3AV_CMD_AUDIO_SOURCE_SERIAL			0x0000
#घोषणा PS3AV_CMD_AUDIO_SOURCE_SPDIF			0x0001
/* audio_swap */
#घोषणा PS3AV_CMD_AUDIO_SWAP_0				0x0000
#घोषणा PS3AV_CMD_AUDIO_SWAP_1				0x0000
/* audio_map */
#घोषणा PS3AV_CMD_AUDIO_MAP_OUTPUT_0			0x0000
#घोषणा PS3AV_CMD_AUDIO_MAP_OUTPUT_1			0x0001
#घोषणा PS3AV_CMD_AUDIO_MAP_OUTPUT_2			0x0002
#घोषणा PS3AV_CMD_AUDIO_MAP_OUTPUT_3			0x0003
/* audio_layout */
#घोषणा PS3AV_CMD_AUDIO_LAYOUT_2CH			0x0000
#घोषणा PS3AV_CMD_AUDIO_LAYOUT_6CH			0x000b	/* LREClr */
#घोषणा PS3AV_CMD_AUDIO_LAYOUT_8CH			0x001f	/* LREClrXY */
/* audio_करोwnmix */
#घोषणा PS3AV_CMD_AUDIO_DOWNMIX_PERMITTED		0x0000
#घोषणा PS3AV_CMD_AUDIO_DOWNMIX_PROHIBITED		0x0001

/* audio_port */
#घोषणा PS3AV_CMD_AUDIO_PORT_HDMI_0			( 1 << 0 )
#घोषणा PS3AV_CMD_AUDIO_PORT_HDMI_1			( 1 << 1 )
#घोषणा PS3AV_CMD_AUDIO_PORT_AVMULTI_0			( 1 << 10 )
#घोषणा PS3AV_CMD_AUDIO_PORT_SPDIF_0			( 1 << 20 )
#घोषणा PS3AV_CMD_AUDIO_PORT_SPDIF_1			( 1 << 21 )

/* audio_ctrl_id */
#घोषणा PS3AV_CMD_AUDIO_CTRL_ID_DAC_RESET		0x0000
#घोषणा PS3AV_CMD_AUDIO_CTRL_ID_DAC_DE_EMPHASIS		0x0001
#घोषणा PS3AV_CMD_AUDIO_CTRL_ID_AVCLK			0x0002
/* audio_ctrl_data[0] reset */
#घोषणा PS3AV_CMD_AUDIO_CTRL_RESET_NEGATE		0x0000
#घोषणा PS3AV_CMD_AUDIO_CTRL_RESET_ASSERT		0x0001
/* audio_ctrl_data[0] de-emphasis */
#घोषणा PS3AV_CMD_AUDIO_CTRL_DE_EMPHASIS_OFF		0x0000
#घोषणा PS3AV_CMD_AUDIO_CTRL_DE_EMPHASIS_ON		0x0001
/* audio_ctrl_data[0] avclk */
#घोषणा PS3AV_CMD_AUDIO_CTRL_AVCLK_22			0x0000
#घोषणा PS3AV_CMD_AUDIO_CTRL_AVCLK_18			0x0001

/* av_vid */
/* करो not use these params directly, use vid_video2av */
#घोषणा PS3AV_CMD_AV_VID_480I				0x0000
#घोषणा PS3AV_CMD_AV_VID_480P				0x0001
#घोषणा PS3AV_CMD_AV_VID_720P_60HZ			0x0002
#घोषणा PS3AV_CMD_AV_VID_1080I_60HZ			0x0003
#घोषणा PS3AV_CMD_AV_VID_1080P_60HZ			0x0004
#घोषणा PS3AV_CMD_AV_VID_576I				0x0005
#घोषणा PS3AV_CMD_AV_VID_576P				0x0006
#घोषणा PS3AV_CMD_AV_VID_720P_50HZ			0x0007
#घोषणा PS3AV_CMD_AV_VID_1080I_50HZ			0x0008
#घोषणा PS3AV_CMD_AV_VID_1080P_50HZ			0x0009
#घोषणा PS3AV_CMD_AV_VID_WXGA				0x000a
#घोषणा PS3AV_CMD_AV_VID_SXGA				0x000b
#घोषणा PS3AV_CMD_AV_VID_WUXGA				0x000c
/* av_cs_out av_cs_in */
/* use cs_video2av() */
#घोषणा PS3AV_CMD_AV_CS_RGB_8				0x0000
#घोषणा PS3AV_CMD_AV_CS_YUV444_8			0x0001
#घोषणा PS3AV_CMD_AV_CS_YUV422_8			0x0002
#घोषणा PS3AV_CMD_AV_CS_XVYCC_8				0x0003
#घोषणा PS3AV_CMD_AV_CS_RGB_10				0x0004
#घोषणा PS3AV_CMD_AV_CS_YUV444_10			0x0005
#घोषणा PS3AV_CMD_AV_CS_YUV422_10			0x0006
#घोषणा PS3AV_CMD_AV_CS_XVYCC_10			0x0007
#घोषणा PS3AV_CMD_AV_CS_RGB_12				0x0008
#घोषणा PS3AV_CMD_AV_CS_YUV444_12			0x0009
#घोषणा PS3AV_CMD_AV_CS_YUV422_12			0x000a
#घोषणा PS3AV_CMD_AV_CS_XVYCC_12			0x000b
#घोषणा PS3AV_CMD_AV_CS_8				0x0000
#घोषणा PS3AV_CMD_AV_CS_10				0x0001
#घोषणा PS3AV_CMD_AV_CS_12				0x0002
/* dither */
#घोषणा PS3AV_CMD_AV_DITHER_OFF				0x0000
#घोषणा PS3AV_CMD_AV_DITHER_ON				0x0001
#घोषणा PS3AV_CMD_AV_DITHER_8BIT			0x0000
#घोषणा PS3AV_CMD_AV_DITHER_10BIT			0x0002
#घोषणा PS3AV_CMD_AV_DITHER_12BIT			0x0004
/* super_white */
#घोषणा PS3AV_CMD_AV_SUPER_WHITE_OFF			0x0000
#घोषणा PS3AV_CMD_AV_SUPER_WHITE_ON			0x0001
/* aspect */
#घोषणा PS3AV_CMD_AV_ASPECT_16_9			0x0000
#घोषणा PS3AV_CMD_AV_ASPECT_4_3				0x0001
/* video_cs_cnv() */
#घोषणा PS3AV_CMD_VIDEO_CS_RGB				0x0001
#घोषणा PS3AV_CMD_VIDEO_CS_YUV422			0x0002
#घोषणा PS3AV_CMD_VIDEO_CS_YUV444			0x0003

/* क्रम broadcast स्वतःmode */
#घोषणा PS3AV_RESBIT_720x480P			0x0003	/* 0x0001 | 0x0002 */
#घोषणा PS3AV_RESBIT_720x576P			0x0003	/* 0x0001 | 0x0002 */
#घोषणा PS3AV_RESBIT_1280x720P			0x0004
#घोषणा PS3AV_RESBIT_1920x1080I			0x0008
#घोषणा PS3AV_RESBIT_1920x1080P			0x4000
#घोषणा PS3AV_RES_MASK_60			(PS3AV_RESBIT_720x480P \
						| PS3AV_RESBIT_1280x720P \
						| PS3AV_RESBIT_1920x1080I \
						| PS3AV_RESBIT_1920x1080P)
#घोषणा PS3AV_RES_MASK_50			(PS3AV_RESBIT_720x576P \
						| PS3AV_RESBIT_1280x720P \
						| PS3AV_RESBIT_1920x1080I \
						| PS3AV_RESBIT_1920x1080P)

/* क्रम VESA स्वतःmode */
#घोषणा PS3AV_RESBIT_VGA			0x0001
#घोषणा PS3AV_RESBIT_WXGA			0x0002
#घोषणा PS3AV_RESBIT_SXGA			0x0004
#घोषणा PS3AV_RESBIT_WUXGA			0x0008
#घोषणा PS3AV_RES_MASK_VESA			(PS3AV_RESBIT_WXGA |\
						 PS3AV_RESBIT_SXGA |\
						 PS3AV_RESBIT_WUXGA)

#घोषणा PS3AV_MONITOR_TYPE_HDMI			1	/* HDMI */
#घोषणा PS3AV_MONITOR_TYPE_DVI			2	/* DVI */


/* क्रम video mode */
क्रमागत ps3av_mode_num अणु
	PS3AV_MODE_AUTO				= 0,
	PS3AV_MODE_480I				= 1,
	PS3AV_MODE_480P				= 2,
	PS3AV_MODE_720P60			= 3,
	PS3AV_MODE_1080I60			= 4,
	PS3AV_MODE_1080P60			= 5,
	PS3AV_MODE_576I				= 6,
	PS3AV_MODE_576P				= 7,
	PS3AV_MODE_720P50			= 8,
	PS3AV_MODE_1080I50			= 9,
	PS3AV_MODE_1080P50			= 10,
	PS3AV_MODE_WXGA				= 11,
	PS3AV_MODE_SXGA				= 12,
	PS3AV_MODE_WUXGA			= 13,
पूर्ण;

#घोषणा PS3AV_MODE_MASK				0x000F
#घोषणा PS3AV_MODE_HDCP_OFF			0x1000	/* Retail PS3 product करोesn't support this */
#घोषणा PS3AV_MODE_DITHER			0x0800
#घोषणा PS3AV_MODE_COLOR			0x0400
#घोषणा PS3AV_MODE_WHITE			0x0200
#घोषणा PS3AV_MODE_FULL				0x0080
#घोषणा PS3AV_MODE_DVI				0x0040
#घोषणा PS3AV_MODE_RGB				0x0020


#घोषणा PS3AV_DEFAULT_HDMI_MODE_ID_REG_60	PS3AV_MODE_480P
#घोषणा PS3AV_DEFAULT_AVMULTI_MODE_ID_REG_60	PS3AV_MODE_480I
#घोषणा PS3AV_DEFAULT_HDMI_MODE_ID_REG_50	PS3AV_MODE_576P
#घोषणा PS3AV_DEFAULT_AVMULTI_MODE_ID_REG_50	PS3AV_MODE_576I

#घोषणा PS3AV_REGION_60				0x01
#घोषणा PS3AV_REGION_50				0x02
#घोषणा PS3AV_REGION_RGB			0x10

#घोषणा get_status(buf)				(((__u32 *)buf)[2])
#घोषणा PS3AV_HDR_SIZE				4	/* version + size */


/** command packet काष्ठाure **/
काष्ठा ps3av_send_hdr अणु
	u16 version;
	u16 size;		/* size of command packet */
	u32 cid;		/* command id */
पूर्ण;

काष्ठा ps3av_reply_hdr अणु
	u16 version;
	u16 size;
	u32 cid;
	u32 status;
पूर्ण;

/* backend: initialization */
काष्ठा ps3av_pkt_av_init अणु
	काष्ठा ps3av_send_hdr send_hdr;
	u32 event_bit;
पूर्ण;

/* backend: finalize */
काष्ठा ps3av_pkt_av_fin अणु
	काष्ठा ps3av_send_hdr send_hdr;
	/* recv */
	u32 reserved;
पूर्ण;

/* backend: get port */
काष्ठा ps3av_pkt_av_get_hw_conf अणु
	काष्ठा ps3av_send_hdr send_hdr;
	/* recv */
	u32 status;
	u16 num_of_hdmi;	/* out: number of hdmi */
	u16 num_of_avmulti;	/* out: number of avmulti */
	u16 num_of_spdअगर;	/* out: number of hdmi */
	u16 reserved;
पूर्ण;

/* backend: get monitor info */
काष्ठा ps3av_info_resolution अणु
	u32 res_bits;
	u32 native;
पूर्ण;

काष्ठा ps3av_info_cs अणु
	u8 rgb;
	u8 yuv444;
	u8 yuv422;
	u8 reserved;
पूर्ण;

काष्ठा ps3av_info_color अणु
	u16 red_x;
	u16 red_y;
	u16 green_x;
	u16 green_y;
	u16 blue_x;
	u16 blue_y;
	u16 white_x;
	u16 white_y;
	u32 gamma;
पूर्ण;

काष्ठा ps3av_info_audio अणु
	u8 type;
	u8 max_num_of_ch;
	u8 fs;
	u8 sbit;
पूर्ण;

काष्ठा ps3av_info_monitor अणु
	u8 avport;
	u8 monitor_id[10];
	u8 monitor_type;
	u8 monitor_name[16];
	काष्ठा ps3av_info_resolution res_60;
	काष्ठा ps3av_info_resolution res_50;
	काष्ठा ps3av_info_resolution res_other;
	काष्ठा ps3av_info_resolution res_vesa;
	काष्ठा ps3av_info_cs cs;
	काष्ठा ps3av_info_color color;
	u8 supported_ai;
	u8 speaker_info;
	u8 num_of_audio_block;
	काष्ठा ps3av_info_audio audio[0];	/* 0 or more audio blocks */
	u8 reserved[169];
पूर्ण __attribute__ ((packed));

काष्ठा ps3av_pkt_av_get_monitor_info अणु
	काष्ठा ps3av_send_hdr send_hdr;
	u16 avport;		/* in: avport */
	u16 reserved;
	/* recv */
	काष्ठा ps3av_info_monitor info;	/* out: monitor info */
पूर्ण;

/* backend: enable/disable event */
काष्ठा ps3av_pkt_av_event अणु
	काष्ठा ps3av_send_hdr send_hdr;
	u32 event_bit;		/* in */
पूर्ण;

/* backend: video cs param */
काष्ठा ps3av_pkt_av_video_cs अणु
	काष्ठा ps3av_send_hdr send_hdr;
	u16 avport;		/* in: avport */
	u16 av_vid;		/* in: video resolution */
	u16 av_cs_out;		/* in: output color space */
	u16 av_cs_in;		/* in: input color space */
	u8 dither;		/* in: dither bit length */
	u8 bitlen_out;		/* in: bit length */
	u8 super_white;		/* in: super white */
	u8 aspect;		/* in: aspect ratio */
पूर्ण;

/* backend: video mute */
काष्ठा ps3av_av_mute अणु
	u16 avport;		/* in: avport */
	u16 mute;		/* in: mute on/off */
पूर्ण;

काष्ठा ps3av_pkt_av_video_mute अणु
	काष्ठा ps3av_send_hdr send_hdr;
	काष्ठा ps3av_av_mute mute[PS3AV_MUTE_PORT_MAX];
पूर्ण;

/* backend: video disable संकेत */
काष्ठा ps3av_pkt_av_video_disable_sig अणु
	काष्ठा ps3av_send_hdr send_hdr;
	u16 avport;		/* in: avport */
	u16 reserved;
पूर्ण;

/* backend: audio param */
काष्ठा ps3av_audio_info_frame अणु
	काष्ठा pb1_bit अणु
		u8 ct:4;
		u8 rsv:1;
		u8 cc:3;
	पूर्ण pb1;
	काष्ठा pb2_bit अणु
		u8 rsv:3;
		u8 sf:3;
		u8 ss:2;
	पूर्ण pb2;
	u8 pb3;
	u8 pb4;
	काष्ठा pb5_bit अणु
		u8 dm:1;
		u8 lsv:4;
		u8 rsv:3;
	पूर्ण pb5;
पूर्ण;

काष्ठा ps3av_pkt_av_audio_param अणु
	काष्ठा ps3av_send_hdr send_hdr;
	u16 avport;		/* in: avport */
	u16 reserved;
	u8 mclk;		/* in: audio mclk */
	u8 ns[3];		/* in: audio ns val */
	u8 enable;		/* in: audio enable */
	u8 swaplr;		/* in: audio swap */
	u8 fअगरomap;		/* in: audio fअगरomap */
	u8 inअ_दोtrl;		/* in: audio input ctrl */
	u8 inputlen;		/* in: sample bit size */
	u8 layout;		/* in: speaker layout param */
	काष्ठा ps3av_audio_info_frame info;	/* in: info */
	u8 chstat[5];		/* in: ch stat */
पूर्ण;

/* backend: audio_mute */
काष्ठा ps3av_pkt_av_audio_mute अणु
	काष्ठा ps3av_send_hdr send_hdr;
	काष्ठा ps3av_av_mute mute[PS3AV_MUTE_PORT_MAX];
पूर्ण;

/* backend: hdmi_mode */
काष्ठा ps3av_pkt_av_hdmi_mode अणु
	काष्ठा ps3av_send_hdr send_hdr;
	u8 mode;		/* in: hdmi_mode */
	u8 reserved0;
	u8 reserved1;
	u8 reserved2;
पूर्ण;

/* backend: tv_mute */
काष्ठा ps3av_pkt_av_tv_mute अणु
	काष्ठा ps3av_send_hdr send_hdr;
	u16 avport;		/* in: avport HDMI only */
	u16 mute;		/* in: mute */
पूर्ण;

/* video: initialize */
काष्ठा ps3av_pkt_video_init अणु
	काष्ठा ps3av_send_hdr send_hdr;
	/* recv */
	u32 reserved;
पूर्ण;

/* video: mode setting */
काष्ठा ps3av_pkt_video_mode अणु
	काष्ठा ps3av_send_hdr send_hdr;
	u32 video_head;		/* in: head */
	u32 reserved;
	u32 video_vid;		/* in: video resolution */
	u16 reserved1;
	u16 width;		/* in: width in pixel */
	u16 reserved2;
	u16 height;		/* in: height in pixel */
	u32 pitch;		/* in: line size in byte */
	u32 video_out_क्रमmat;	/* in: out क्रमmat */
	u32 video_क्रमmat;	/* in: input frame buffer क्रमmat */
	u8 reserved3;
	u8 video_cl_cnv;	/* in: color conversion */
	u16 video_order;	/* in: input RGB order */
	u32 reserved4;
पूर्ण;

/* video: क्रमmat */
काष्ठा ps3av_pkt_video_क्रमmat अणु
	काष्ठा ps3av_send_hdr send_hdr;
	u32 video_head;		/* in: head */
	u32 video_क्रमmat;	/* in: frame buffer क्रमmat */
	u8 reserved;
	u8 video_cl_cnv;	/* in: color conversion */
	u16 video_order;	/* in: input RGB order */
पूर्ण;

/* video: pitch */
काष्ठा ps3av_pkt_video_pitch अणु
	u16 version;
	u16 size;		/* size of command packet */
	u32 cid;		/* command id */
	u32 video_head;		/* in: head */
	u32 pitch;		/* in: line size in byte */
पूर्ण;

/* audio: initialize */
काष्ठा ps3av_pkt_audio_init अणु
	काष्ठा ps3av_send_hdr send_hdr;
	/* recv */
	u32 reserved;
पूर्ण;

/* audio: mode setting */
काष्ठा ps3av_pkt_audio_mode अणु
	काष्ठा ps3av_send_hdr send_hdr;
	u8 avport;		/* in: avport */
	u8 reserved0[3];
	u32 mask;		/* in: mask */
	u32 audio_num_of_ch;	/* in: number of ch */
	u32 audio_fs;		/* in: sampling freq */
	u32 audio_word_bits;	/* in: sample bit size */
	u32 audio_क्रमmat;	/* in: audio output क्रमmat */
	u32 audio_source;	/* in: audio source */
	u8 audio_enable[4];	/* in: audio enable */
	u8 audio_swap[4];	/* in: audio swap */
	u8 audio_map[4];	/* in: audio map */
	u32 audio_layout;	/* in: speaker layout */
	u32 audio_करोwnmix;	/* in: audio करोwnmix permission */
	u32 audio_करोwnmix_level;
	u8 audio_cs_info[8];	/* in: IEC channel status */
पूर्ण;

/* audio: mute */
काष्ठा ps3av_audio_mute अणु
	u8 avport;		/* in: opt_port optical */
	u8 reserved[3];
	u32 mute;		/* in: mute */
पूर्ण;

काष्ठा ps3av_pkt_audio_mute अणु
	काष्ठा ps3av_send_hdr send_hdr;
	काष्ठा ps3av_audio_mute mute[PS3AV_OPT_PORT_MAX];
पूर्ण;

/* audio: active/inactive */
काष्ठा ps3av_pkt_audio_active अणु
	काष्ठा ps3av_send_hdr send_hdr;
	u32 audio_port;		/* in: audio active/inactive port */
पूर्ण;

/* audio: SPDIF user bit */
काष्ठा ps3av_pkt_audio_spdअगर_bit अणु
	u16 version;
	u16 size;		/* size of command packet */
	u32 cid;		/* command id */
	u8 avport;		/* in: avport SPDIF only */
	u8 reserved[3];
	u32 audio_port;		/* in: SPDIF only */
	u32 spdअगर_bit_data[12];	/* in: user bit data */
पूर्ण;

/* audio: audio control */
काष्ठा ps3av_pkt_audio_ctrl अणु
	u16 version;
	u16 size;		/* size of command packet */
	u32 cid;		/* command id */
	u32 audio_ctrl_id;	/* in: control id */
	u32 audio_ctrl_data[4];	/* in: control data */
पूर्ण;

/* avb:param */
#घोषणा PS3AV_PKT_AVB_PARAM_MAX_BUF_SIZE	\
	(PS3AV_AVB_NUM_VIDEO*माप(काष्ठा ps3av_pkt_video_mode) + \
	 PS3AV_AVB_NUM_AUDIO*माप(काष्ठा ps3av_pkt_audio_mode) + \
	 PS3AV_AVB_NUM_AV_VIDEO*माप(काष्ठा ps3av_pkt_av_video_cs) + \
	 PS3AV_AVB_NUM_AV_AUDIO*माप(काष्ठा ps3av_pkt_av_audio_param))

काष्ठा ps3av_pkt_avb_param अणु
	काष्ठा ps3av_send_hdr send_hdr;
	u16 num_of_video_pkt;
	u16 num_of_audio_pkt;
	u16 num_of_av_video_pkt;
	u16 num_of_av_audio_pkt;
	/*
	 * The actual buffer layout depends on the fields above:
	 *
	 * काष्ठा ps3av_pkt_video_mode video[num_of_video_pkt];
	 * काष्ठा ps3av_pkt_audio_mode audio[num_of_audio_pkt];
	 * काष्ठा ps3av_pkt_av_video_cs av_video[num_of_av_video_pkt];
	 * काष्ठा ps3av_pkt_av_audio_param av_audio[num_of_av_audio_pkt];
	 */
	u8 buf[PS3AV_PKT_AVB_PARAM_MAX_BUF_SIZE];
पूर्ण;

/* channel status */
बाह्य u8 ps3av_mode_cs_info[];

/** command status **/
#घोषणा PS3AV_STATUS_SUCCESS			0x0000	/* success */
#घोषणा PS3AV_STATUS_RECEIVE_VUART_ERROR	0x0001	/* receive vuart error */
#घोषणा PS3AV_STATUS_SYSCON_COMMUNICATE_FAIL	0x0002	/* syscon communication error */
#घोषणा PS3AV_STATUS_INVALID_COMMAND		0x0003	/* obsolete invalid CID */
#घोषणा PS3AV_STATUS_INVALID_PORT		0x0004	/* invalid port number */
#घोषणा PS3AV_STATUS_INVALID_VID		0x0005	/* invalid video क्रमmat */
#घोषणा PS3AV_STATUS_INVALID_COLOR_SPACE	0x0006	/* invalid video colose space */
#घोषणा PS3AV_STATUS_INVALID_FS			0x0007	/* invalid audio sampling freq */
#घोषणा PS3AV_STATUS_INVALID_AUDIO_CH		0x0008	/* invalid audio channel number */
#घोषणा PS3AV_STATUS_UNSUPPORTED_VERSION	0x0009	/* version mismatch  */
#घोषणा PS3AV_STATUS_INVALID_SAMPLE_SIZE	0x000a	/* invalid audio sample bit size */
#घोषणा PS3AV_STATUS_FAILURE			0x000b	/* other failures */
#घोषणा PS3AV_STATUS_UNSUPPORTED_COMMAND	0x000c	/* unsupported cid */
#घोषणा PS3AV_STATUS_BUFFER_OVERFLOW		0x000d	/* ग_लिखो buffer overflow */
#घोषणा PS3AV_STATUS_INVALID_VIDEO_PARAM	0x000e	/* invalid video param */
#घोषणा PS3AV_STATUS_NO_SEL			0x000f	/* not exist selector */
#घोषणा PS3AV_STATUS_INVALID_AV_PARAM		0x0010	/* invalid backend param */
#घोषणा PS3AV_STATUS_INVALID_AUDIO_PARAM	0x0011	/* invalid audio param */
#घोषणा PS3AV_STATUS_UNSUPPORTED_HDMI_MODE	0x0012	/* unsupported hdmi mode */
#घोषणा PS3AV_STATUS_NO_SYNC_HEAD		0x0013	/* sync head failed */

बाह्य व्योम ps3av_set_hdr(u32, u16, काष्ठा ps3av_send_hdr *);
बाह्य पूर्णांक ps3av_करो_pkt(u32, u16, माप_प्रकार, काष्ठा ps3av_send_hdr *);

बाह्य पूर्णांक ps3av_cmd_init(व्योम);
बाह्य पूर्णांक ps3av_cmd_fin(व्योम);
बाह्य पूर्णांक ps3av_cmd_av_video_mute(पूर्णांक, u32 *, u32);
बाह्य पूर्णांक ps3av_cmd_av_video_disable_sig(u32);
बाह्य पूर्णांक ps3av_cmd_av_tv_mute(u32, u32);
बाह्य पूर्णांक ps3av_cmd_enable_event(व्योम);
बाह्य पूर्णांक ps3av_cmd_av_hdmi_mode(u8);
बाह्य u32 ps3av_cmd_set_av_video_cs(व्योम *, u32, पूर्णांक, पूर्णांक, पूर्णांक, u32);
बाह्य u32 ps3av_cmd_set_video_mode(व्योम *, u32, पूर्णांक, पूर्णांक, u32);
बाह्य पूर्णांक ps3av_cmd_video_क्रमmat_black(u32, u32, u32);
बाह्य पूर्णांक ps3av_cmd_av_audio_mute(पूर्णांक, u32 *, u32);
बाह्य u32 ps3av_cmd_set_av_audio_param(व्योम *, u32,
					स्थिर काष्ठा ps3av_pkt_audio_mode *,
					u32);
बाह्य व्योम ps3av_cmd_set_audio_mode(काष्ठा ps3av_pkt_audio_mode *, u32, u32,
				     u32, u32, u32, u32);
बाह्य पूर्णांक ps3av_cmd_audio_mode(काष्ठा ps3av_pkt_audio_mode *);
बाह्य पूर्णांक ps3av_cmd_audio_mute(पूर्णांक, u32 *, u32);
बाह्य पूर्णांक ps3av_cmd_audio_active(पूर्णांक, u32);
बाह्य पूर्णांक ps3av_cmd_avb_param(काष्ठा ps3av_pkt_avb_param *, u32);
बाह्य पूर्णांक ps3av_cmd_av_get_hw_conf(काष्ठा ps3av_pkt_av_get_hw_conf *);
बाह्य पूर्णांक ps3av_cmd_video_get_monitor_info(काष्ठा ps3av_pkt_av_get_monitor_info *,
					    u32);

बाह्य पूर्णांक ps3av_set_video_mode(पूर्णांक);
बाह्य पूर्णांक ps3av_set_audio_mode(u32, u32, u32, u32, u32);
बाह्य पूर्णांक ps3av_get_स्वतः_mode(व्योम);
बाह्य पूर्णांक ps3av_get_mode(व्योम);
बाह्य पूर्णांक ps3av_video_mode2res(u32, u32 *, u32 *);
बाह्य पूर्णांक ps3av_video_mute(पूर्णांक);
बाह्य पूर्णांक ps3av_audio_mute(पूर्णांक);
बाह्य पूर्णांक ps3av_audio_mute_analog(पूर्णांक);
बाह्य पूर्णांक ps3av_dev_खोलो(व्योम);
बाह्य पूर्णांक ps3av_dev_बंद(व्योम);
#पूर्ण_अगर	/* _ASM_POWERPC_PS3AV_H_ */
