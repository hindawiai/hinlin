<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2005-2006 Micronas USA Inc.
 */

/*
 * This is the निजी include file क्रम the go7007 driver.  It should not
 * be included by anybody but the driver itself, and especially not by
 * user-space applications.
 */

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/videobuf2-v4l2.h>

काष्ठा go7007;

/* IDs to activate board-specअगरic support code */
#घोषणा GO7007_BOARDID_MATRIX_II	0
#घोषणा GO7007_BOARDID_MATRIX_RELOAD	1
#घोषणा GO7007_BOARDID_STAR_TREK	2
#घोषणा GO7007_BOARDID_PCI_VOYAGER	3
#घोषणा GO7007_BOARDID_XMEN		4
#घोषणा GO7007_BOARDID_XMEN_II		5
#घोषणा GO7007_BOARDID_XMEN_III		6
#घोषणा GO7007_BOARDID_MATRIX_REV	7
#घोषणा GO7007_BOARDID_PX_M402U		8
#घोषणा GO7007_BOARDID_PX_TV402U	9
#घोषणा GO7007_BOARDID_LIFEVIEW_LR192	10 /* TV Walker Ultra */
#घोषणा GO7007_BOARDID_ENDURA		11
#घोषणा GO7007_BOARDID_ADLINK_MPG24	12
#घोषणा GO7007_BOARDID_SENSORAY_2250	13 /* Sensoray 2250/2251 */
#घोषणा GO7007_BOARDID_ADS_USBAV_709    14

/* Various अक्षरacteristics of each board */
#घोषणा GO7007_BOARD_HAS_AUDIO		(1<<0)
#घोषणा GO7007_BOARD_USE_ONBOARD_I2C	(1<<1)
#घोषणा GO7007_BOARD_HAS_TUNER		(1<<2)

/* Characteristics of sensor devices */
#घोषणा GO7007_SENSOR_VALID_POLAR	(1<<0)
#घोषणा GO7007_SENSOR_HREF_POLAR	(1<<1)
#घोषणा GO7007_SENSOR_VREF_POLAR	(1<<2)
#घोषणा GO7007_SENSOR_FIELD_ID_POLAR	(1<<3)
#घोषणा GO7007_SENSOR_BIT_WIDTH		(1<<4)
#घोषणा GO7007_SENSOR_VALID_ENABLE	(1<<5)
#घोषणा GO7007_SENSOR_656		(1<<6)
#घोषणा GO7007_SENSOR_CONFIG_MASK	0x7f
#घोषणा GO7007_SENSOR_TV		(1<<7)
#घोषणा GO7007_SENSOR_VBI		(1<<8)
#घोषणा GO7007_SENSOR_SCALING		(1<<9)
#घोषणा GO7007_SENSOR_SAA7115		(1<<10)

/* Characteristics of audio sensor devices */
#घोषणा GO7007_AUDIO_I2S_MODE_1		(1)
#घोषणा GO7007_AUDIO_I2S_MODE_2		(2)
#घोषणा GO7007_AUDIO_I2S_MODE_3		(3)
#घोषणा GO7007_AUDIO_BCLK_POLAR		(1<<2)
#घोषणा GO7007_AUDIO_WORD_14		(14<<4)
#घोषणा GO7007_AUDIO_WORD_16		(16<<4)
#घोषणा GO7007_AUDIO_ONE_CHANNEL	(1<<11)
#घोषणा GO7007_AUDIO_I2S_MASTER		(1<<16)
#घोषणा GO7007_AUDIO_OKI_MODE		(1<<17)

#घोषणा GO7007_CID_CUSTOM_BASE		(V4L2_CID_DETECT_CLASS_BASE + 0x1000)
#घोषणा V4L2_CID_PIXEL_THRESHOLD0	(GO7007_CID_CUSTOM_BASE+1)
#घोषणा V4L2_CID_MOTION_THRESHOLD0	(GO7007_CID_CUSTOM_BASE+2)
#घोषणा V4L2_CID_MB_THRESHOLD0		(GO7007_CID_CUSTOM_BASE+3)
#घोषणा V4L2_CID_PIXEL_THRESHOLD1	(GO7007_CID_CUSTOM_BASE+4)
#घोषणा V4L2_CID_MOTION_THRESHOLD1	(GO7007_CID_CUSTOM_BASE+5)
#घोषणा V4L2_CID_MB_THRESHOLD1		(GO7007_CID_CUSTOM_BASE+6)
#घोषणा V4L2_CID_PIXEL_THRESHOLD2	(GO7007_CID_CUSTOM_BASE+7)
#घोषणा V4L2_CID_MOTION_THRESHOLD2	(GO7007_CID_CUSTOM_BASE+8)
#घोषणा V4L2_CID_MB_THRESHOLD2		(GO7007_CID_CUSTOM_BASE+9)
#घोषणा V4L2_CID_PIXEL_THRESHOLD3	(GO7007_CID_CUSTOM_BASE+10)
#घोषणा V4L2_CID_MOTION_THRESHOLD3	(GO7007_CID_CUSTOM_BASE+11)
#घोषणा V4L2_CID_MB_THRESHOLD3		(GO7007_CID_CUSTOM_BASE+12)

काष्ठा go7007_board_info अणु
	अचिन्हित पूर्णांक flags;
	पूर्णांक hpi_buffer_cap;
	अचिन्हित पूर्णांक sensor_flags;
	पूर्णांक sensor_width;
	पूर्णांक sensor_height;
	पूर्णांक sensor_framerate;
	पूर्णांक sensor_h_offset;
	पूर्णांक sensor_v_offset;
	अचिन्हित पूर्णांक audio_flags;
	पूर्णांक audio_rate;
	पूर्णांक audio_bclk_भाग;
	पूर्णांक audio_मुख्य_भाग;
	पूर्णांक num_i2c_devs;
	काष्ठा go_i2c अणु
		स्थिर अक्षर *type;
		अचिन्हित पूर्णांक is_video:1;
		अचिन्हित पूर्णांक is_audio:1;
		पूर्णांक addr;
		u32 flags;
	पूर्ण i2c_devs[5];
	पूर्णांक num_inमाला_दो;
	काष्ठा अणु
		पूर्णांक video_input;
		पूर्णांक audio_index;
		अक्षर *name;
	पूर्ण inमाला_दो[4];
	पूर्णांक video_config;
	पूर्णांक num_aud_inमाला_दो;
	काष्ठा अणु
		पूर्णांक audio_input;
		अक्षर *name;
	पूर्ण aud_inमाला_दो[3];
पूर्ण;

काष्ठा go7007_hpi_ops अणु
	पूर्णांक (*पूर्णांकerface_reset)(काष्ठा go7007 *go);
	पूर्णांक (*ग_लिखो_पूर्णांकerrupt)(काष्ठा go7007 *go, पूर्णांक addr, पूर्णांक data);
	पूर्णांक (*पढ़ो_पूर्णांकerrupt)(काष्ठा go7007 *go);
	पूर्णांक (*stream_start)(काष्ठा go7007 *go);
	पूर्णांक (*stream_stop)(काष्ठा go7007 *go);
	पूर्णांक (*send_firmware)(काष्ठा go7007 *go, u8 *data, पूर्णांक len);
	पूर्णांक (*send_command)(काष्ठा go7007 *go, अचिन्हित पूर्णांक cmd, व्योम *arg);
	व्योम (*release)(काष्ठा go7007 *go);
पूर्ण;

/* The video buffer size must be a multiple of PAGE_SIZE */
#घोषणा	GO7007_BUF_PAGES	(128 * 1024 / PAGE_SIZE)
#घोषणा	GO7007_BUF_SIZE		(GO7007_BUF_PAGES << PAGE_SHIFT)

काष्ठा go7007_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
	अचिन्हित पूर्णांक frame_offset;
	u32 modet_active;
पूर्ण;

#घोषणा GO7007_RATIO_1_1	0
#घोषणा GO7007_RATIO_4_3	1
#घोषणा GO7007_RATIO_16_9	2

क्रमागत go7007_parser_state अणु
	STATE_DATA,
	STATE_00,
	STATE_00_00,
	STATE_00_00_01,
	STATE_FF,
	STATE_VBI_LEN_A,
	STATE_VBI_LEN_B,
	STATE_MODET_MAP,
	STATE_UNPARSED,
पूर्ण;

काष्ठा go7007 अणु
	काष्ठा device *dev;
	u8 bus_info[32];
	स्थिर काष्ठा go7007_board_info *board_info;
	अचिन्हित पूर्णांक board_id;
	पूर्णांक tuner_type;
	पूर्णांक channel_number; /* क्रम multi-channel boards like Adlink PCI-MPG24 */
	अक्षर name[64];
	काष्ठा video_device vdev;
	व्योम *boot_fw;
	अचिन्हित boot_fw_len;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा v4l2_ctrl *mpeg_video_encoding;
	काष्ठा v4l2_ctrl *mpeg_video_gop_size;
	काष्ठा v4l2_ctrl *mpeg_video_gop_closure;
	काष्ठा v4l2_ctrl *mpeg_video_bitrate;
	काष्ठा v4l2_ctrl *mpeg_video_aspect_ratio;
	काष्ठा v4l2_ctrl *mpeg_video_b_frames;
	काष्ठा v4l2_ctrl *mpeg_video_rep_seqheader;
	काष्ठा v4l2_ctrl *modet_mode;
	क्रमागत अणु STATUS_INIT, STATUS_ONLINE, STATUS_SHUTDOWN पूर्ण status;
	spinlock_t spinlock;
	काष्ठा mutex hw_lock;
	काष्ठा mutex serialize_lock;
	पूर्णांक audio_enabled;
	काष्ठा v4l2_subdev *sd_video;
	काष्ठा v4l2_subdev *sd_audio;
	u8 usb_buf[16];

	/* Video input */
	पूर्णांक input;
	पूर्णांक aud_input;
	क्रमागत अणु GO7007_STD_NTSC, GO7007_STD_PAL, GO7007_STD_OTHER पूर्ण standard;
	v4l2_std_id std;
	पूर्णांक sensor_framerate;
	पूर्णांक width;
	पूर्णांक height;
	पूर्णांक encoder_h_offset;
	पूर्णांक encoder_v_offset;
	अचिन्हित पूर्णांक encoder_h_halve:1;
	अचिन्हित पूर्णांक encoder_v_halve:1;
	अचिन्हित पूर्णांक encoder_subsample:1;

	/* Encoder config */
	u32 क्रमmat;
	पूर्णांक bitrate;
	पूर्णांक fps_scale;
	पूर्णांक pali;
	पूर्णांक aspect_ratio;
	पूर्णांक gop_size;
	अचिन्हित पूर्णांक ipb:1;
	अचिन्हित पूर्णांक बंदd_gop:1;
	अचिन्हित पूर्णांक repeat_seqhead:1;
	अचिन्हित पूर्णांक seq_header_enable:1;
	अचिन्हित पूर्णांक gop_header_enable:1;
	अचिन्हित पूर्णांक dvd_mode:1;
	अचिन्हित पूर्णांक पूर्णांकerlace_coding:1;

	/* Motion detection */
	अचिन्हित पूर्णांक modet_enable:1;
	काष्ठा अणु
		अचिन्हित पूर्णांक enable:1;
		पूर्णांक pixel_threshold;
		पूर्णांक motion_threshold;
		पूर्णांक mb_threshold;
	पूर्ण modet[4];
	अचिन्हित अक्षर modet_map[1624];
	अचिन्हित अक्षर active_map[216];
	u32 modet_event_status;

	/* Video streaming */
	काष्ठा mutex queue_lock;
	काष्ठा vb2_queue vidq;
	क्रमागत go7007_parser_state state;
	पूर्णांक parse_length;
	u16 modet_word;
	पूर्णांक seen_frame;
	u32 next_seq;
	काष्ठा list_head vidq_active;
	रुको_queue_head_t frame_रुकोq;
	काष्ठा go7007_buffer *active_buf;

	/* Audio streaming */
	व्योम (*audio_deliver)(काष्ठा go7007 *go, u8 *buf, पूर्णांक length);
	व्योम *snd_context;

	/* I2C */
	पूर्णांक i2c_adapter_online;
	काष्ठा i2c_adapter i2c_adapter;

	/* HPI driver */
	स्थिर काष्ठा go7007_hpi_ops *hpi_ops;
	व्योम *hpi_context;
	पूर्णांक पूर्णांकerrupt_available;
	रुको_queue_head_t पूर्णांकerrupt_रुकोq;
	अचिन्हित लघु पूर्णांकerrupt_value;
	अचिन्हित लघु पूर्णांकerrupt_data;
पूर्ण;

अटल अंतरभूत काष्ठा go7007 *to_go7007(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा go7007, v4l2_dev);
पूर्ण

/* All of these must be called with the hpi_lock mutex held! */
#घोषणा go7007_पूर्णांकerface_reset(go) \
			((go)->hpi_ops->पूर्णांकerface_reset(go))
#घोषणा	go7007_ग_लिखो_पूर्णांकerrupt(go, x, y) \
			((go)->hpi_ops->ग_लिखो_पूर्णांकerrupt)((go), (x), (y))
#घोषणा go7007_stream_start(go) \
			((go)->hpi_ops->stream_start(go))
#घोषणा go7007_stream_stop(go) \
			((go)->hpi_ops->stream_stop(go))
#घोषणा	go7007_send_firmware(go, x, y) \
			((go)->hpi_ops->send_firmware)((go), (x), (y))
#घोषणा go7007_ग_लिखो_addr(go, x, y) \
			((go)->hpi_ops->ग_लिखो_पूर्णांकerrupt)((go), (x)|0x8000, (y))

/* go7007-driver.c */
पूर्णांक go7007_पढ़ो_addr(काष्ठा go7007 *go, u16 addr, u16 *data);
पूर्णांक go7007_पढ़ो_पूर्णांकerrupt(काष्ठा go7007 *go, u16 *value, u16 *data);
पूर्णांक go7007_boot_encoder(काष्ठा go7007 *go, पूर्णांक init_i2c);
पूर्णांक go7007_reset_encoder(काष्ठा go7007 *go);
पूर्णांक go7007_रेजिस्टर_encoder(काष्ठा go7007 *go, अचिन्हित num_i2c_devs);
पूर्णांक go7007_start_encoder(काष्ठा go7007 *go);
व्योम go7007_parse_video_stream(काष्ठा go7007 *go, u8 *buf, पूर्णांक length);
काष्ठा go7007 *go7007_alloc(स्थिर काष्ठा go7007_board_info *board,
					काष्ठा device *dev);
व्योम go7007_update_board(काष्ठा go7007 *go);

/* go7007-fw.c */
पूर्णांक go7007_स्थिरruct_fw_image(काष्ठा go7007 *go, u8 **fw, पूर्णांक *fwlen);

/* go7007-i2c.c */
पूर्णांक go7007_i2c_init(काष्ठा go7007 *go);
पूर्णांक go7007_i2c_हटाओ(काष्ठा go7007 *go);

/* go7007-v4l2.c */
पूर्णांक go7007_v4l2_init(काष्ठा go7007 *go);
पूर्णांक go7007_v4l2_ctrl_init(काष्ठा go7007 *go);
व्योम go7007_v4l2_हटाओ(काष्ठा go7007 *go);

/* snd-go7007.c */
पूर्णांक go7007_snd_init(काष्ठा go7007 *go);
पूर्णांक go7007_snd_हटाओ(काष्ठा go7007 *go);
