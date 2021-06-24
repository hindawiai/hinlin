<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
   cx231xx.h - driver क्रम Conexant Cx23100/101/102 USB video capture devices

   Copyright (C) 2008 <srinivasa.deevi at conexant करोt com>
	Based on em28xx driver

 */

#अगर_अघोषित _CX231XX_H
#घोषणा _CX231XX_H

#समावेश <linux/videodev2.h>
#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/i2c.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <linux/usb.h>

#समावेश <media/drv-पूर्णांकf/cx2341x.h>

#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/rc-core.h>
#समावेश <media/i2c/ir-kbd-i2c.h>

#समावेश "cx231xx-reg.h"
#समावेश "cx231xx-pcb-cfg.h"
#समावेश "cx231xx-conf-reg.h"

#घोषणा DRIVER_NAME                     "cx231xx"
#घोषणा PWR_SLEEP_INTERVAL              10

/* I2C addresses क्रम control block in Cx231xx */
#घोषणा     AFE_DEVICE_ADDRESS		0x60
#घोषणा     I2S_BLK_DEVICE_ADDRESS	0x98
#घोषणा     VID_BLK_I2C_ADDRESS		0x88
#घोषणा     VERVE_I2C_ADDRESS           0x40
#घोषणा     DIF_USE_BASEBAND            0xFFFFFFFF

/* Boards supported by driver */
#घोषणा CX231XX_BOARD_UNKNOWN		    0
#घोषणा CX231XX_BOARD_CNXT_CARRAERA	1
#घोषणा CX231XX_BOARD_CNXT_SHELBY	2
#घोषणा CX231XX_BOARD_CNXT_RDE_253S	3
#घोषणा CX231XX_BOARD_CNXT_RDU_253S	4
#घोषणा CX231XX_BOARD_CNXT_VIDEO_GRABBER	5
#घोषणा CX231XX_BOARD_CNXT_RDE_250	6
#घोषणा CX231XX_BOARD_CNXT_RDU_250	7
#घोषणा CX231XX_BOARD_HAUPPAUGE_EXETER  8
#घोषणा CX231XX_BOARD_HAUPPAUGE_USBLIVE2 9
#घोषणा CX231XX_BOARD_PV_PLAYTV_USB_HYBRID 10
#घोषणा CX231XX_BOARD_PV_XCAPTURE_USB 11
#घोषणा CX231XX_BOARD_KWORLD_UB430_USB_HYBRID 12
#घोषणा CX231XX_BOARD_ICONBIT_U100 13
#घोषणा CX231XX_BOARD_HAUPPAUGE_USB2_FM_PAL 14
#घोषणा CX231XX_BOARD_HAUPPAUGE_USB2_FM_NTSC 15
#घोषणा CX231XX_BOARD_ELGATO_VIDEO_CAPTURE_V2 16
#घोषणा CX231XX_BOARD_OTG102 17
#घोषणा CX231XX_BOARD_KWORLD_UB445_USB_HYBRID 18
#घोषणा CX231XX_BOARD_HAUPPAUGE_930C_HD_1113xx 19
#घोषणा CX231XX_BOARD_HAUPPAUGE_930C_HD_1114xx 20
#घोषणा CX231XX_BOARD_HAUPPAUGE_955Q 21
#घोषणा CX231XX_BOARD_TERRATEC_GRABBY 22
#घोषणा CX231XX_BOARD_EVROMEDIA_FULL_HYBRID_FULLHD 23
#घोषणा CX231XX_BOARD_ASTROMETA_T2HYBRID 24
#घोषणा CX231XX_BOARD_THE_IMAGING_SOURCE_DFG_USB2_PRO 25
#घोषणा CX231XX_BOARD_HAUPPAUGE_935C 26
#घोषणा CX231XX_BOARD_HAUPPAUGE_975 27

/* Limits minimum and शेष number of buffers */
#घोषणा CX231XX_MIN_BUF                 4
#घोषणा CX231XX_DEF_BUF                 12
#घोषणा CX231XX_DEF_VBI_BUF             6

#घोषणा VBI_LINE_COUNT                  17
#घोषणा VBI_LINE_LENGTH                 1440

/*Limits the max URB message size */
#घोषणा URB_MAX_CTRL_SIZE               80

/* Params क्रम validated field */
#घोषणा CX231XX_BOARD_NOT_VALIDATED     1
#घोषणा CX231XX_BOARD_VALIDATED		0

/* maximum number of cx231xx boards */
#घोषणा CX231XX_MAXBOARDS               8

/* maximum number of frames that can be queued */
#घोषणा CX231XX_NUM_FRAMES              5

/* number of buffers क्रम isoc transfers */
#घोषणा CX231XX_NUM_BUFS                8

/* number of packets क्रम each buffer
   winकरोws requests only 40 packets .. so we better करो the same
   this is what I found out क्रम all alternate numbers there!
 */
#घोषणा CX231XX_NUM_PACKETS             40

/* शेष alternate; 0 means choose the best */
#घोषणा CX231XX_PINOUT                  0

#घोषणा CX231XX_INTERLACED_DEFAULT      1

/* समय to रुको when stopping the isoc transfer */
#घोषणा CX231XX_URB_TIMEOUT		\
		msecs_to_jअगरfies(CX231XX_NUM_BUFS * CX231XX_NUM_PACKETS)

#घोषणा CX231xx_NORMS (\
	V4L2_STD_NTSC_M |  V4L2_STD_NTSC_M_JP |  V4L2_STD_NTSC_443 | \
	V4L2_STD_PAL_BG |  V4L2_STD_PAL_DK    |  V4L2_STD_PAL_I    | \
	V4L2_STD_PAL_M  |  V4L2_STD_PAL_N     |  V4L2_STD_PAL_Nc   | \
	V4L2_STD_PAL_60 |  V4L2_STD_SECAM_L   |  V4L2_STD_SECAM_DK)

#घोषणा SLEEP_S5H1432    30
#घोषणा CX23417_OSC_EN   8
#घोषणा CX23417_RESET    9

काष्ठा cx23417_fmt अणु
	u32   fourcc;          /* v4l2 क्रमmat id */
	पूर्णांक   depth;
	पूर्णांक   flags;
	u32   cxक्रमmat;
पूर्ण;
क्रमागत cx231xx_mode अणु
	CX231XX_SUSPEND,
	CX231XX_ANALOG_MODE,
	CX231XX_DIGITAL_MODE,
पूर्ण;

क्रमागत cx231xx_std_mode अणु
	CX231XX_TV_AIR = 0,
	CX231XX_TV_CABLE
पूर्ण;

क्रमागत cx231xx_stream_state अणु
	STREAM_OFF,
	STREAM_INTERRUPT,
	STREAM_ON,
पूर्ण;

काष्ठा cx231xx;

काष्ठा cx231xx_isoc_ctl अणु
	/* max packet size of isoc transaction */
	पूर्णांक max_pkt_size;

	/* number of allocated urbs */
	पूर्णांक num_bufs;

	/* urb क्रम isoc transfers */
	काष्ठा urb **urb;

	/* transfer buffers क्रम isoc transfer */
	अक्षर **transfer_buffer;

	/* Last buffer command and region */
	u8 cmd;
	पूर्णांक pos, size, pktsize;

	/* Last field: ODD or EVEN? */
	पूर्णांक field;

	/* Stores incomplete commands */
	u32 पंचांगp_buf;
	पूर्णांक पंचांगp_buf_len;

	/* Stores alपढ़ोy requested buffers */
	काष्ठा cx231xx_buffer *buf;

	/* Stores the number of received fields */
	पूर्णांक nfields;

	/* isoc urb callback */
	पूर्णांक (*isoc_copy) (काष्ठा cx231xx *dev, काष्ठा urb *urb);
पूर्ण;

काष्ठा cx231xx_bulk_ctl अणु
	/* max packet size of bulk transaction */
	पूर्णांक max_pkt_size;

	/* number of allocated urbs */
	पूर्णांक num_bufs;

	/* urb क्रम bulk transfers */
	काष्ठा urb **urb;

	/* transfer buffers क्रम bulk transfer */
	अक्षर **transfer_buffer;

	/* Last buffer command and region */
	u8 cmd;
	पूर्णांक pos, size, pktsize;

	/* Last field: ODD or EVEN? */
	पूर्णांक field;

	/* Stores incomplete commands */
	u32 पंचांगp_buf;
	पूर्णांक पंचांगp_buf_len;

	/* Stores alपढ़ोy requested buffers */
	काष्ठा cx231xx_buffer *buf;

	/* Stores the number of received fields */
	पूर्णांक nfields;

	/* bulk urb callback */
	पूर्णांक (*bulk_copy) (काष्ठा cx231xx *dev, काष्ठा urb *urb);
पूर्ण;

काष्ठा cx231xx_fmt अणु
	अक्षर *name;
	u32 fourcc;		/* v4l2 क्रमmat id */
	पूर्णांक depth;
	पूर्णांक reg;
पूर्ण;

/* buffer क्रम one video frame */
काष्ठा cx231xx_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
	काष्ठा list_head frame;
	पूर्णांक top_field;
	पूर्णांक receiving;
पूर्ण;

क्रमागत ps_package_head अणु
	CX231XX_NEED_ADD_PS_PACKAGE_HEAD = 0,
	CX231XX_NONEED_PS_PACKAGE_HEAD
पूर्ण;

काष्ठा cx231xx_dmaqueue अणु
	काष्ठा list_head active;

	रुको_queue_head_t wq;

	/* Counters to control buffer fill */
	पूर्णांक pos;
	u8 is_partial_line;
	u8 partial_buf[8];
	u8 last_sav;
	पूर्णांक current_field;
	u32 bytes_left_in_line;
	u32 lines_completed;
	u8 field1_करोne;
	u32 lines_per_field;
	u32 sequence;

	/*Mpeg2 control buffer*/
	u8 *p_left_data;
	u32 left_data_count;
	u8 mpeg_buffer_करोne;
	u32 mpeg_buffer_completed;
	क्रमागत ps_package_head add_ps_package_head;
	अक्षर ps_head[10];
पूर्ण;

/* inमाला_दो */

#घोषणा MAX_CX231XX_INPUT               4

क्रमागत cx231xx_itype अणु
	CX231XX_VMUX_COMPOSITE1 = 1,
	CX231XX_VMUX_SVIDEO,
	CX231XX_VMUX_TELEVISION,
	CX231XX_VMUX_CABLE,
	CX231XX_RADIO,
	CX231XX_VMUX_DVB,
पूर्ण;

क्रमागत cx231xx_v_input अणु
	CX231XX_VIN_1_1 = 0x1,
	CX231XX_VIN_2_1,
	CX231XX_VIN_3_1,
	CX231XX_VIN_4_1,
	CX231XX_VIN_1_2 = 0x01,
	CX231XX_VIN_2_2,
	CX231XX_VIN_3_2,
	CX231XX_VIN_1_3 = 0x1,
	CX231XX_VIN_2_3,
	CX231XX_VIN_3_3,
पूर्ण;

/* cx231xx has two audio inमाला_दो: tuner and line in */
क्रमागत cx231xx_amux अणु
	/* This is the only entry क्रम cx231xx tuner input */
	CX231XX_AMUX_VIDEO,	/* cx231xx tuner */
	CX231XX_AMUX_LINE_IN,	/* Line In */
पूर्ण;

काष्ठा cx231xx_reg_seq अणु
	अचिन्हित अक्षर bit;
	अचिन्हित अक्षर val;
	पूर्णांक sleep;
पूर्ण;

काष्ठा cx231xx_input अणु
	क्रमागत cx231xx_itype type;
	अचिन्हित पूर्णांक vmux;
	क्रमागत cx231xx_amux amux;
	काष्ठा cx231xx_reg_seq *gpio;
पूर्ण;

#घोषणा INPUT(nr) (&cx231xx_boards[dev->model].input[nr])

क्रमागत cx231xx_decoder अणु
	CX231XX_NODECODER,
	CX231XX_AVDECODER
पूर्ण;

क्रमागत CX231XX_I2C_MASTER_PORT अणु
	I2C_0 = 0,       /* master 0 - पूर्णांकernal connection */
	I2C_1 = 1,       /* master 1 - used with mux */
	I2C_2 = 2,       /* master 2 */
	I2C_1_MUX_1 = 3, /* master 1 - port 1 (I2C_DEMOD_EN = 0) */
	I2C_1_MUX_3 = 4  /* master 1 - port 3 (I2C_DEMOD_EN = 1) */
पूर्ण;

काष्ठा cx231xx_board अणु
	अक्षर *name;
	पूर्णांक vchannels;
	पूर्णांक tuner_type;
	पूर्णांक tuner_addr;
	v4l2_std_id norm;	/* tv norm */

	/* demod related */
	पूर्णांक demod_addr;
	पूर्णांक demod_addr2;
	u8 demod_xfer_mode;	/* 0 - Serial; 1 - parallel */

	/* GPIO Pins */
	काष्ठा cx231xx_reg_seq *dvb_gpio;
	काष्ठा cx231xx_reg_seq *suspend_gpio;
	काष्ठा cx231xx_reg_seq *tuner_gpio;
		/* Negative means करोn't use it */
	s8 tuner_sअगर_gpio;
	s8 tuner_scl_gpio;
	s8 tuner_sda_gpio;

	/* PIN ctrl */
	u32 ctl_pin_status_mask;
	u8 agc_analog_digital_select_gpio;
	u32 gpio_pin_status_mask;

	/* i2c masters */
	u8 tuner_i2c_master;
	u8 demod_i2c_master;
	u8 ir_i2c_master;

	/* क्रम devices with I2C chips क्रम IR */
	अक्षर *rc_map_name;

	अचिन्हित पूर्णांक max_range_640_480:1;
	अचिन्हित पूर्णांक has_dvb:1;
	अचिन्हित पूर्णांक has_417:1;
	अचिन्हित पूर्णांक valid:1;
	अचिन्हित पूर्णांक no_alt_vanc:1;
	अचिन्हित पूर्णांक बाह्यal_av:1;

	अचिन्हित अक्षर xclk, i2c_speed;

	क्रमागत cx231xx_decoder decoder;
	पूर्णांक output_mode;

	काष्ठा cx231xx_input input[MAX_CX231XX_INPUT];
	काष्ठा cx231xx_input radio;
	काष्ठा rc_map *ir_codes;
पूर्ण;

/* device states */
क्रमागत cx231xx_dev_state अणु
	DEV_INITIALIZED = 0x01,
	DEV_DISCONNECTED = 0x02,
पूर्ण;

क्रमागत AFE_MODE अणु
	AFE_MODE_LOW_IF,
	AFE_MODE_BASEBAND,
	AFE_MODE_EU_HI_IF,
	AFE_MODE_US_HI_IF,
	AFE_MODE_JAPAN_HI_IF
पूर्ण;

क्रमागत AUDIO_INPUT अणु
	AUDIO_INPUT_MUTE,
	AUDIO_INPUT_LINE,
	AUDIO_INPUT_TUNER_TV,
	AUDIO_INPUT_SPDIF,
	AUDIO_INPUT_TUNER_FM
पूर्ण;

#घोषणा CX231XX_AUDIO_BUFS              5
#घोषणा CX231XX_NUM_AUDIO_PACKETS       16
#घोषणा CX231XX_ISO_NUM_AUDIO_PACKETS	64

/* cx231xx extensions */
#घोषणा CX231XX_AUDIO                   0x10
#घोषणा CX231XX_DVB                     0x20

काष्ठा cx231xx_audio अणु
	अक्षर name[50];
	अक्षर *transfer_buffer[CX231XX_AUDIO_BUFS];
	काष्ठा urb *urb[CX231XX_AUDIO_BUFS];
	काष्ठा usb_device *udev;
	अचिन्हित पूर्णांक capture_transfer_करोne;
	काष्ठा snd_pcm_substream *capture_pcm_substream;

	अचिन्हित पूर्णांक hwptr_करोne_capture;
	काष्ठा snd_card *sndcard;

	पूर्णांक users, shutकरोwn;
	/* locks */
	spinlock_t slock;

	पूर्णांक alt;		/* alternate */
	पूर्णांक max_pkt_size;	/* max packet size of isoc transaction */
	पूर्णांक num_alt;		/* Number of alternative settings */
	अचिन्हित पूर्णांक *alt_max_pkt_size;	/* array of wMaxPacketSize */
	u16 end_poपूर्णांक_addr;
पूर्ण;

/*****************************************************************/
/* set/get i2c */
/* 00--1Mb/s, 01-400kb/s, 10--100kb/s, 11--5Mb/s */
#घोषणा I2C_SPEED_1M            0x0
#घोषणा I2C_SPEED_400K          0x1
#घोषणा I2C_SPEED_100K          0x2
#घोषणा I2C_SPEED_5M            0x3

/* 0-- STOP transaction */
#घोषणा I2C_STOP                0x0
/* 1-- करो not transmit STOP at end of transaction */
#घोषणा I2C_NOSTOP              0x1
/* 1--allow slave to insert घड़ी रुको states */
#घोषणा I2C_SYNC                0x1

काष्ठा cx231xx_i2c अणु
	काष्ठा cx231xx *dev;

	पूर्णांक nr;

	/* i2c i/o */
	काष्ठा i2c_adapter i2c_adap;
	पूर्णांक i2c_rc;

	/* dअगरferent settings क्रम each bus */
	u8 i2c_period;
	u8 i2c_nostop;
	u8 i2c_reserve;
पूर्ण;

काष्ठा cx231xx_i2c_xfer_data अणु
	u8 dev_addr;
	u8 direction;		/* 1 - IN, 0 - OUT */
	u8 saddr_len;		/* sub address len */
	u16 saddr_dat;		/* sub addr data */
	u8 buf_size;		/* buffer size */
	u8 *p_buffer;		/* poपूर्णांकer to the buffer */
पूर्ण;

काष्ठा VENDOR_REQUEST_IN अणु
	u8 bRequest;
	u16 wValue;
	u16 wIndex;
	u16 wLength;
	u8 direction;
	u8 bData;
	u8 *pBuff;
पूर्ण;

काष्ठा cx231xx_tvnorm अणु
	अक्षर		*name;
	v4l2_std_id	id;
	u32		cxअगरormat;
	u32		cxoक्रमmat;
पूर्ण;

क्रमागत TRANSFER_TYPE अणु
	Raw_Video = 0,
	Audio,
	Vbi,			/* VANC */
	Sliced_cc,		/* HANC */
	TS1_serial_mode,
	TS2,
	TS1_parallel_mode
पूर्ण ;

काष्ठा cx231xx_video_mode अणु
	/* Isoc control काष्ठा */
	काष्ठा cx231xx_dmaqueue vidq;
	काष्ठा cx231xx_isoc_ctl isoc_ctl;
	काष्ठा cx231xx_bulk_ctl bulk_ctl;
	/* locks */
	spinlock_t slock;

	/* usb transfer */
	पूर्णांक alt;		/* alternate */
	पूर्णांक max_pkt_size;	/* max packet size of isoc transaction */
	पूर्णांक num_alt;		/* Number of alternative settings */
	अचिन्हित पूर्णांक *alt_max_pkt_size;	/* array of wMaxPacketSize */
	u16 end_poपूर्णांक_addr;
पूर्ण;

काष्ठा cx231xx_tsport अणु
	काष्ठा cx231xx *dev;

	पूर्णांक                        nr;
	पूर्णांक                        sram_chno;

	/* dma queues */

	u32                        ts_packet_size;
	u32                        ts_packet_count;

	पूर्णांक                        width;
	पूर्णांक                        height;

	/* locks */
	spinlock_t                 slock;

	/* रेजिस्टरs */
	u32                        reg_gpcnt;
	u32                        reg_gpcnt_ctl;
	u32                        reg_dma_ctl;
	u32                        reg_lngth;
	u32                        reg_hw_sop_ctrl;
	u32                        reg_gen_ctrl;
	u32                        reg_bd_pkt_status;
	u32                        reg_sop_status;
	u32                        reg_fअगरo_ovfl_stat;
	u32                        reg_vld_misc;
	u32                        reg_ts_clk_en;
	u32                        reg_ts_पूर्णांक_msk;
	u32                        reg_ts_पूर्णांक_stat;
	u32                        reg_src_sel;

	/* Default रेजिस्टर vals */
	पूर्णांक                        pci_irqmask;
	u32                        dma_ctl_val;
	u32                        ts_पूर्णांक_msk_val;
	u32                        gen_ctrl_val;
	u32                        ts_clk_en_val;
	u32                        src_sel_val;
	u32                        vld_misc_val;
	u32                        hw_sop_ctrl_val;

	/* Allow a single tsport to have multiple frontends */
	u32                        num_frontends;
	व्योम                       *port_priv;
पूर्ण;

/* मुख्य device काष्ठा */
काष्ठा cx231xx अणु
	/* generic device properties */
	अक्षर name[30];		/* name (including minor) of the device */
	पूर्णांक model;		/* index in the device_data काष्ठा */
	पूर्णांक devno;		/* marks the number of this device */
	काष्ठा device *dev;	/* poपूर्णांकer to USB पूर्णांकerface's dev */

	काष्ठा cx231xx_board board;

	/* For I2C IR support */
	काष्ठा IR_i2c_init_data    init_data;
	काष्ठा i2c_client          *ir_i2c_client;

	अचिन्हित पूर्णांक stream_on:1;	/* Locks streams */
	अचिन्हित पूर्णांक vbi_stream_on:1;	/* Locks streams क्रम VBI */
	अचिन्हित पूर्णांक has_audio_class:1;
	अचिन्हित पूर्णांक has_alsa_audio:1;

	अचिन्हित पूर्णांक i2c_scan_running:1; /* true only during i2c_scan */

	काष्ठा cx231xx_fmt *क्रमmat;

	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_subdev *sd_cx25840;
	काष्ठा v4l2_subdev *sd_tuner;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_ctrl_handler radio_ctrl_handler;
	काष्ठा cx2341x_handler mpeg_ctrl_handler;

	काष्ठा work_काष्ठा wq_trigger;		/* Trigger to start/stop audio क्रम alsa module */
	atomic_t	   stream_started;	/* stream should be running अगर true */

	काष्ठा list_head devlist;

	पूर्णांक tuner_type;		/* type of the tuner */
	पूर्णांक tuner_addr;		/* tuner address */

	/* I2C adapters: Master 1 & 2 (External) & Master 3 (Internal only) */
	काष्ठा cx231xx_i2c i2c_bus[3];
	काष्ठा i2c_mux_core *muxc;
	काष्ठा i2c_adapter *i2c_mux_adap[2];

	अचिन्हित पूर्णांक xc_fw_load_करोne:1;
	अचिन्हित पूर्णांक port_3_चयन_enabled:1;
	/* locks */
	काष्ठा mutex gpio_i2c_lock;
	काष्ठा mutex i2c_lock;

	/* video क्रम linux */
	पूर्णांक users;		/* user count क्रम exclusive use */
	काष्ठा video_device vdev;	/* video क्रम linux device काष्ठा */
	v4l2_std_id norm;	/* selected tv norm */
	पूर्णांक ctl_freq;		/* selected frequency */
	अचिन्हित पूर्णांक ctl_ainput;	/* selected audio input */

	/* frame properties */
	पूर्णांक width;		/* current frame width */
	पूर्णांक height;		/* current frame height */
	पूर्णांक पूर्णांकerlaced;		/* 1=पूर्णांकerlace fields, 0=just top fields */
	अचिन्हित पूर्णांक size;

	काष्ठा cx231xx_audio adev;

	/* states */
	क्रमागत cx231xx_dev_state state;

	काष्ठा work_काष्ठा request_module_wk;

	/* locks */
	काष्ठा mutex lock;
	काष्ठा mutex ctrl_urb_lock;	/* protects urb_buf */
	काष्ठा list_head inqueue, outqueue;
	रुको_queue_head_t खोलो, रुको_frame, रुको_stream;
	काष्ठा video_device vbi_dev;
	काष्ठा video_device radio_dev;

#अगर defined(CONFIG_MEDIA_CONTROLLER)
	काष्ठा media_device *media_dev;
	काष्ठा media_pad video_pad, vbi_pad;
	काष्ठा media_entity input_ent[MAX_CX231XX_INPUT];
	काष्ठा media_pad input_pad[MAX_CX231XX_INPUT];
#पूर्ण_अगर

	काष्ठा vb2_queue vidq;
	काष्ठा vb2_queue vbiq;

	अचिन्हित अक्षर eedata[256];

	काष्ठा cx231xx_video_mode video_mode;
	काष्ठा cx231xx_video_mode vbi_mode;
	काष्ठा cx231xx_video_mode sliced_cc_mode;
	काष्ठा cx231xx_video_mode ts1_mode;

	atomic_t devlist_count;

	काष्ठा usb_device *udev;	/* the usb device */
	अक्षर urb_buf[URB_MAX_CTRL_SIZE];	/* urb control msg buffer */

	/* helper funcs that call usb_control_msg */
	पूर्णांक (*cx231xx_पढ़ो_ctrl_reg) (काष्ठा cx231xx *dev, u8 req, u16 reg,
				      अक्षर *buf, पूर्णांक len);
	पूर्णांक (*cx231xx_ग_लिखो_ctrl_reg) (काष्ठा cx231xx *dev, u8 req, u16 reg,
				       अक्षर *buf, पूर्णांक len);
	पूर्णांक (*cx231xx_send_usb_command) (काष्ठा cx231xx_i2c *i2c_bus,
				काष्ठा cx231xx_i2c_xfer_data *req_data);
	पूर्णांक (*cx231xx_gpio_i2c_पढ़ो) (काष्ठा cx231xx *dev, u8 dev_addr,
				      u8 *buf, u8 len);
	पूर्णांक (*cx231xx_gpio_i2c_ग_लिखो) (काष्ठा cx231xx *dev, u8 dev_addr,
				       u8 *buf, u8 len);

	पूर्णांक (*cx231xx_set_analog_freq) (काष्ठा cx231xx *dev, u32 freq);
	पूर्णांक (*cx231xx_reset_analog_tuner) (काष्ठा cx231xx *dev);

	क्रमागत cx231xx_mode mode;

	काष्ठा cx231xx_dvb *dvb;

	/* Cx231xx supported PCB config's */
	काष्ठा pcb_config current_pcb_config;
	u8 current_scenario_idx;
	u8 पूर्णांकerface_count;
	u8 max_iad_पूर्णांकerface_count;

	/* GPIO related रेजिस्टर direction and values */
	u32 gpio_dir;
	u32 gpio_val;

	/* Power Modes */
	पूर्णांक घातer_mode;

	/* afe parameters */
	क्रमागत AFE_MODE afe_mode;
	u32 afe_ref_count;

	/* video related parameters */
	u32 video_input;
	u32 active_mode;
	u8 vbi_or_sliced_cc_mode;	/* 0 - vbi ; 1 - sliced cc mode */
	क्रमागत cx231xx_std_mode std_mode;	/* 0 - Air; 1 - cable */

	/*mode: digital=1 or analog=0*/
	u8 mode_tv;

	u8 USE_ISO;
	काष्ठा cx231xx_tvnorm      encodernorm;
	काष्ठा cx231xx_tsport      ts1, ts2;
	काष्ठा vb2_queue	   mpegq;
	काष्ठा video_device        v4l_device;
	atomic_t                   v4l_पढ़ोer_count;
	u32                        freq;
	अचिन्हित पूर्णांक               input;
	u32                        cx23417_mailbox;
	u32                        __iomem *lmmio;
	u8                         __iomem *bmmio;
पूर्ण;

बाह्य काष्ठा list_head cx231xx_devlist;

#घोषणा cx25840_call(cx231xx, o, f, args...) \
	v4l2_subdev_call(cx231xx->sd_cx25840, o, f, ##args)
#घोषणा tuner_call(cx231xx, o, f, args...) \
	v4l2_subdev_call(cx231xx->sd_tuner, o, f, ##args)
#घोषणा call_all(dev, o, f, args...) \
	v4l2_device_call_until_err(&dev->v4l2_dev, 0, o, f, ##args)

काष्ठा cx231xx_ops अणु
	काष्ठा list_head next;
	अक्षर *name;
	पूर्णांक id;
	पूर्णांक (*init) (काष्ठा cx231xx *);
	पूर्णांक (*fini) (काष्ठा cx231xx *);
पूर्ण;

/* call back functions in dvb module */
पूर्णांक cx231xx_set_analog_freq(काष्ठा cx231xx *dev, u32 freq);
पूर्णांक cx231xx_reset_analog_tuner(काष्ठा cx231xx *dev);

/* Provided by cx231xx-i2c.c */
व्योम cx231xx_करो_i2c_scan(काष्ठा cx231xx *dev, पूर्णांक i2c_port);
पूर्णांक cx231xx_i2c_रेजिस्टर(काष्ठा cx231xx_i2c *bus);
व्योम cx231xx_i2c_unरेजिस्टर(काष्ठा cx231xx_i2c *bus);
पूर्णांक cx231xx_i2c_mux_create(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_i2c_mux_रेजिस्टर(काष्ठा cx231xx *dev, पूर्णांक mux_no);
व्योम cx231xx_i2c_mux_unरेजिस्टर(काष्ठा cx231xx *dev);
काष्ठा i2c_adapter *cx231xx_get_i2c_adap(काष्ठा cx231xx *dev, पूर्णांक i2c_port);

/* Internal block control functions */
पूर्णांक cx231xx_पढ़ो_i2c_master(काष्ठा cx231xx *dev, u8 dev_addr, u16 saddr,
		 u8 saddr_len, u32 *data, u8 data_len, पूर्णांक master);
पूर्णांक cx231xx_ग_लिखो_i2c_master(काष्ठा cx231xx *dev, u8 dev_addr, u16 saddr,
		 u8 saddr_len, u32 data, u8 data_len, पूर्णांक master);
पूर्णांक cx231xx_पढ़ो_i2c_data(काष्ठा cx231xx *dev, u8 dev_addr,
			  u16 saddr, u8 saddr_len, u32 *data, u8 data_len);
पूर्णांक cx231xx_ग_लिखो_i2c_data(काष्ठा cx231xx *dev, u8 dev_addr,
			   u16 saddr, u8 saddr_len, u32 data, u8 data_len);
पूर्णांक cx231xx_reg_mask_ग_लिखो(काष्ठा cx231xx *dev, u8 dev_addr, u8 size,
			   u16 रेजिस्टर_address, u8 bit_start, u8 bit_end,
			   u32 value);
पूर्णांक cx231xx_पढ़ो_modअगरy_ग_लिखो_i2c_dword(काष्ठा cx231xx *dev, u8 dev_addr,
					u16 saddr, u32 mask, u32 value);
u32 cx231xx_set_field(u32 field_mask, u32 data);

/*verve r/w*/
व्योम initGPIO(काष्ठा cx231xx *dev);
व्योम uninitGPIO(काष्ठा cx231xx *dev);
/* afe related functions */
पूर्णांक cx231xx_afe_init_super_block(काष्ठा cx231xx *dev, u32 ref_count);
पूर्णांक cx231xx_afe_init_channels(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_afe_setup_AFE_क्रम_baseband(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_afe_set_input_mux(काष्ठा cx231xx *dev, u32 input_mux);
पूर्णांक cx231xx_afe_set_mode(काष्ठा cx231xx *dev, क्रमागत AFE_MODE mode);
पूर्णांक cx231xx_afe_update_घातer_control(काष्ठा cx231xx *dev,
					क्रमागत AV_MODE avmode);
पूर्णांक cx231xx_afe_adjust_ref_count(काष्ठा cx231xx *dev, u32 video_input);

/* i2s block related functions */
पूर्णांक cx231xx_i2s_blk_initialize(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_i2s_blk_update_घातer_control(काष्ठा cx231xx *dev,
					क्रमागत AV_MODE avmode);
पूर्णांक cx231xx_i2s_blk_set_audio_input(काष्ठा cx231xx *dev, u8 audio_input);

/* DIF related functions */
पूर्णांक cx231xx_dअगर_configure_C2HH_क्रम_low_IF(काष्ठा cx231xx *dev, u32 mode,
					  u32 function_mode, u32 standard);
व्योम cx231xx_set_Colibri_For_LowIF(काष्ठा cx231xx *dev, u32 अगर_freq,
					 u8 spectral_invert, u32 mode);
u32 cx231xx_Get_Colibri_CarrierOffset(u32 mode, u32 standerd);
व्योम cx231xx_set_DIF_bandpass(काष्ठा cx231xx *dev, u32 अगर_freq,
					 u8 spectral_invert, u32 mode);
व्योम cx231xx_Setup_AFE_क्रम_LowIF(काष्ठा cx231xx *dev);
व्योम reset_s5h1432_demod(काष्ठा cx231xx *dev);
व्योम cx231xx_dump_HH_reg(काष्ठा cx231xx *dev);
व्योम update_HH_रेजिस्टर_after_set_DIF(काष्ठा cx231xx *dev);



पूर्णांक cx231xx_dअगर_set_standard(काष्ठा cx231xx *dev, u32 standard);
पूर्णांक cx231xx_tuner_pre_channel_change(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_tuner_post_channel_change(काष्ठा cx231xx *dev);

/* video parser functions */
u8 cx231xx_find_next_SAV_EAV(u8 *p_buffer, u32 buffer_size,
			     u32 *p_bytes_used);
u8 cx231xx_find_boundary_SAV_EAV(u8 *p_buffer, u8 *partial_buf,
				 u32 *p_bytes_used);
पूर्णांक cx231xx_करो_copy(काष्ठा cx231xx *dev, काष्ठा cx231xx_dmaqueue *dma_q,
		    u8 *p_buffer, u32 bytes_to_copy);
व्योम cx231xx_reset_video_buffer(काष्ठा cx231xx *dev,
				काष्ठा cx231xx_dmaqueue *dma_q);
u8 cx231xx_is_buffer_करोne(काष्ठा cx231xx *dev, काष्ठा cx231xx_dmaqueue *dma_q);
u32 cx231xx_copy_video_line(काष्ठा cx231xx *dev, काष्ठा cx231xx_dmaqueue *dma_q,
			    u8 *p_line, u32 length, पूर्णांक field_number);
u32 cx231xx_get_video_line(काष्ठा cx231xx *dev, काष्ठा cx231xx_dmaqueue *dma_q,
			   u8 sav_eav, u8 *p_buffer, u32 buffer_size);
व्योम cx231xx_swab(u16 *from, u16 *to, u16 len);

/* Provided by cx231xx-core.c */

u32 cx231xx_request_buffers(काष्ठा cx231xx *dev, u32 count);
व्योम cx231xx_queue_unusedframes(काष्ठा cx231xx *dev);
व्योम cx231xx_release_buffers(काष्ठा cx231xx *dev);

/* पढ़ो from control pipe */
पूर्णांक cx231xx_पढ़ो_ctrl_reg(काष्ठा cx231xx *dev, u8 req, u16 reg,
			  अक्षर *buf, पूर्णांक len);

/* ग_लिखो to control pipe */
पूर्णांक cx231xx_ग_लिखो_ctrl_reg(काष्ठा cx231xx *dev, u8 req, u16 reg,
			   अक्षर *buf, पूर्णांक len);
पूर्णांक cx231xx_mode_रेजिस्टर(काष्ठा cx231xx *dev, u16 address, u32 mode);

पूर्णांक cx231xx_send_venकरोr_cmd(काष्ठा cx231xx *dev,
				काष्ठा VENDOR_REQUEST_IN *ven_req);
पूर्णांक cx231xx_send_usb_command(काष्ठा cx231xx_i2c *i2c_bus,
				काष्ठा cx231xx_i2c_xfer_data *req_data);

/* Gpio related functions */
पूर्णांक cx231xx_send_gpio_cmd(काष्ठा cx231xx *dev, u32 gpio_bit, u8 *gpio_val,
			  u8 len, u8 request, u8 direction);
पूर्णांक cx231xx_set_gpio_value(काष्ठा cx231xx *dev, पूर्णांक pin_number, पूर्णांक pin_value);
पूर्णांक cx231xx_set_gpio_direction(काष्ठा cx231xx *dev, पूर्णांक pin_number,
			       पूर्णांक pin_value);

पूर्णांक cx231xx_gpio_i2c_start(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_gpio_i2c_end(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_gpio_i2c_ग_लिखो_byte(काष्ठा cx231xx *dev, u8 data);
पूर्णांक cx231xx_gpio_i2c_पढ़ो_byte(काष्ठा cx231xx *dev, u8 *buf);
पूर्णांक cx231xx_gpio_i2c_पढ़ो_ack(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_gpio_i2c_ग_लिखो_ack(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_gpio_i2c_ग_लिखो_nak(काष्ठा cx231xx *dev);

पूर्णांक cx231xx_gpio_i2c_पढ़ो(काष्ठा cx231xx *dev, u8 dev_addr, u8 *buf, u8 len);
पूर्णांक cx231xx_gpio_i2c_ग_लिखो(काष्ठा cx231xx *dev, u8 dev_addr, u8 *buf, u8 len);

/* audio related functions */
पूर्णांक cx231xx_set_audio_decoder_input(काष्ठा cx231xx *dev,
				    क्रमागत AUDIO_INPUT audio_input);

पूर्णांक cx231xx_capture_start(काष्ठा cx231xx *dev, पूर्णांक start, u8 media_type);
पूर्णांक cx231xx_set_video_alternate(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_set_alt_setting(काष्ठा cx231xx *dev, u8 index, u8 alt);
पूर्णांक is_fw_load(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_check_fw(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_init_isoc(काष्ठा cx231xx *dev, पूर्णांक max_packets,
		      पूर्णांक num_bufs, पूर्णांक max_pkt_size,
		      पूर्णांक (*isoc_copy) (काष्ठा cx231xx *dev,
					काष्ठा urb *urb));
पूर्णांक cx231xx_init_bulk(काष्ठा cx231xx *dev, पूर्णांक max_packets,
		      पूर्णांक num_bufs, पूर्णांक max_pkt_size,
		      पूर्णांक (*bulk_copy) (काष्ठा cx231xx *dev,
					काष्ठा urb *urb));
व्योम cx231xx_stop_TS1(काष्ठा cx231xx *dev);
व्योम cx231xx_start_TS1(काष्ठा cx231xx *dev);
व्योम cx231xx_uninit_isoc(काष्ठा cx231xx *dev);
व्योम cx231xx_uninit_bulk(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_set_mode(काष्ठा cx231xx *dev, क्रमागत cx231xx_mode set_mode);
पूर्णांक cx231xx_unmute_audio(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_ep5_bulkout(काष्ठा cx231xx *dev, u8 *firmware, u16 size);
व्योम cx231xx_disable656(काष्ठा cx231xx *dev);
व्योम cx231xx_enable656(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_demod_reset(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_gpio_set(काष्ठा cx231xx *dev, काष्ठा cx231xx_reg_seq *gpio);

/* Device list functions */
व्योम cx231xx_release_resources(काष्ठा cx231xx *dev);
व्योम cx231xx_release_analog_resources(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_रेजिस्टर_analog_devices(काष्ठा cx231xx *dev);
व्योम cx231xx_हटाओ_from_devlist(काष्ठा cx231xx *dev);
व्योम cx231xx_add_पूर्णांकo_devlist(काष्ठा cx231xx *dev);
व्योम cx231xx_init_extension(काष्ठा cx231xx *dev);
व्योम cx231xx_बंद_extension(काष्ठा cx231xx *dev);

/* hardware init functions */
पूर्णांक cx231xx_dev_init(काष्ठा cx231xx *dev);
व्योम cx231xx_dev_uninit(काष्ठा cx231xx *dev);
व्योम cx231xx_config_i2c(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_config(काष्ठा cx231xx *dev);

/* Stream control functions */
पूर्णांक cx231xx_start_stream(काष्ठा cx231xx *dev, u32 ep_mask);
पूर्णांक cx231xx_stop_stream(काष्ठा cx231xx *dev, u32 ep_mask);

पूर्णांक cx231xx_initialize_stream_xfer(काष्ठा cx231xx *dev, u32 media_type);

/* Power control functions */
पूर्णांक cx231xx_set_घातer_mode(काष्ठा cx231xx *dev, क्रमागत AV_MODE mode);
पूर्णांक cx231xx_घातer_suspend(काष्ठा cx231xx *dev);

/* chip specअगरic control functions */
पूर्णांक cx231xx_init_ctrl_pin_status(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_set_agc_analog_digital_mux_select(काष्ठा cx231xx *dev,
					      u8 analog_or_digital);
पूर्णांक cx231xx_enable_i2c_port_3(काष्ठा cx231xx *dev, bool is_port_3);

/* video audio decoder related functions */
व्योम video_mux(काष्ठा cx231xx *dev, पूर्णांक index);
पूर्णांक cx231xx_set_video_input_mux(काष्ठा cx231xx *dev, u8 input);
पूर्णांक cx231xx_set_decoder_video_input(काष्ठा cx231xx *dev, u8 pin_type, u8 input);
पूर्णांक cx231xx_करो_mode_ctrl_overrides(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_set_audio_input(काष्ठा cx231xx *dev, u8 input);

/* Provided by cx231xx-video.c */
पूर्णांक cx231xx_रेजिस्टर_extension(काष्ठा cx231xx_ops *dev);
व्योम cx231xx_unरेजिस्टर_extension(काष्ठा cx231xx_ops *dev);
व्योम cx231xx_init_extension(काष्ठा cx231xx *dev);
व्योम cx231xx_बंद_extension(काष्ठा cx231xx *dev);
व्योम cx231xx_v4l2_create_entities(काष्ठा cx231xx *dev);
पूर्णांक cx231xx_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap);
पूर्णांक cx231xx_g_tuner(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_tuner *t);
पूर्णांक cx231xx_s_tuner(काष्ठा file *file, व्योम *priv, स्थिर काष्ठा v4l2_tuner *t);
पूर्णांक cx231xx_g_frequency(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_frequency *f);
पूर्णांक cx231xx_s_frequency(काष्ठा file *file, व्योम *priv,
			      स्थिर काष्ठा v4l2_frequency *f);
पूर्णांक cx231xx_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_input *i);
पूर्णांक cx231xx_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i);
पूर्णांक cx231xx_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i);
पूर्णांक cx231xx_g_chip_info(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_dbg_chip_info *chip);
पूर्णांक cx231xx_g_रेजिस्टर(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_dbg_रेजिस्टर *reg);
पूर्णांक cx231xx_s_रेजिस्टर(काष्ठा file *file, व्योम *priv,
			     स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg);

/* Provided by cx231xx-cards.c */
बाह्य व्योम cx231xx_pre_card_setup(काष्ठा cx231xx *dev);
बाह्य व्योम cx231xx_card_setup(काष्ठा cx231xx *dev);
बाह्य काष्ठा cx231xx_board cx231xx_boards[];
बाह्य काष्ठा usb_device_id cx231xx_id_table[];
बाह्य स्थिर अचिन्हित पूर्णांक cx231xx_bcount;
पूर्णांक cx231xx_tuner_callback(व्योम *ptr, पूर्णांक component, पूर्णांक command, पूर्णांक arg);

/* cx23885-417.c                                               */
बाह्य पूर्णांक cx231xx_417_रेजिस्टर(काष्ठा cx231xx *dev);
बाह्य व्योम cx231xx_417_unरेजिस्टर(काष्ठा cx231xx *dev);

/* cx23885-input.c                                             */

#अगर defined(CONFIG_VIDEO_CX231XX_RC)
पूर्णांक cx231xx_ir_init(काष्ठा cx231xx *dev);
व्योम cx231xx_ir_निकास(काष्ठा cx231xx *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक cx231xx_ir_init(काष्ठा cx231xx *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम cx231xx_ir_निकास(काष्ठा cx231xx *dev) अणुपूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित पूर्णांक norm_maxw(काष्ठा cx231xx *dev)
अणु
	अगर (dev->board.max_range_640_480)
		वापस 640;
	अन्यथा
		वापस 720;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक norm_maxh(काष्ठा cx231xx *dev)
अणु
	अगर (dev->board.max_range_640_480)
		वापस 480;
	अन्यथा
		वापस (dev->norm & V4L2_STD_625_50) ? 576 : 480;
पूर्ण
#पूर्ण_अगर
