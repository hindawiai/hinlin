<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * पंचांग6000.h - driver क्रम TM5600/TM6000/TM6010 USB video capture devices
 *
 * Copyright (c) 2006-2007 Mauro Carvalho Chehab <mchehab@kernel.org>
 *
 * Copyright (c) 2007 Michel Ludwig <michel.ludwig@gmail.com>
 *	- DVB-T support
 */

#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/videobuf-vदो_स्मृति.h>
#समावेश "tm6000-usb-isoc.h"
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>

#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dmxdev.h>

/* Inमाला_दो */
क्रमागत पंचांग6000_itype अणु
	TM6000_INPUT_TV	= 1,
	TM6000_INPUT_COMPOSITE1,
	TM6000_INPUT_COMPOSITE2,
	TM6000_INPUT_SVIDEO,
	TM6000_INPUT_DVB,
	TM6000_INPUT_RADIO,
पूर्ण;

क्रमागत पंचांग6000_mux अणु
	TM6000_VMUX_VIDEO_A = 1,
	TM6000_VMUX_VIDEO_B,
	TM6000_VMUX_VIDEO_AB,
	TM6000_AMUX_ADC1,
	TM6000_AMUX_ADC2,
	TM6000_AMUX_SIF1,
	TM6000_AMUX_SIF2,
	TM6000_AMUX_I2S,
पूर्ण;

क्रमागत पंचांग6000_devtype अणु
	TM6000 = 0,
	TM5600,
	TM6010,
पूर्ण;

काष्ठा पंचांग6000_input अणु
	क्रमागत पंचांग6000_itype	type;
	क्रमागत पंचांग6000_mux		vmux;
	क्रमागत पंचांग6000_mux		amux;
	अचिन्हित पूर्णांक		v_gpio;
	अचिन्हित पूर्णांक		a_gpio;
पूर्ण;

/* ------------------------------------------------------------------
 *	Basic काष्ठाures
 * ------------------------------------------------------------------
 */

काष्ठा पंचांग6000_fmt अणु
	u32   fourcc;          /* v4l2 क्रमmat id */
	पूर्णांक   depth;
पूर्ण;

/* buffer क्रम one video frame */
काष्ठा पंचांग6000_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा videobuf_buffer vb;

	काष्ठा पंचांग6000_fmt      *fmt;
पूर्ण;

काष्ठा पंचांग6000_dmaqueue अणु
	काष्ठा list_head       active;
	काष्ठा list_head       queued;

	/* thपढ़ो क्रम generating video stream*/
	काष्ठा task_काष्ठा         *kthपढ़ो;
	रुको_queue_head_t          wq;
	/* Counters to control fps rate */
	पूर्णांक                        frame;
	पूर्णांक                        ini_jअगरfies;
पूर्ण;

/* device states */
क्रमागत पंचांग6000_core_state अणु
	DEV_INITIALIZED   = 0x01,
	DEV_DISCONNECTED  = 0x02,
	DEV_MISCONFIGURED = 0x04,
पूर्ण;

/* io methods */
क्रमागत पंचांग6000_io_method अणु
	IO_NONE,
	IO_READ,
	IO_MMAP,
पूर्ण;

क्रमागत पंचांग6000_mode अणु
	TM6000_MODE_UNKNOWN = 0,
	TM6000_MODE_ANALOG,
	TM6000_MODE_DIGITAL,
पूर्ण;

काष्ठा पंचांग6000_gpio अणु
	पूर्णांक		tuner_reset;
	पूर्णांक		tuner_on;
	पूर्णांक		demod_reset;
	पूर्णांक		demod_on;
	पूर्णांक		घातer_led;
	पूर्णांक		dvb_led;
	पूर्णांक		ir;
पूर्ण;

काष्ठा पंचांग6000_capabilities अणु
	अचिन्हित पूर्णांक    has_tuner:1;
	अचिन्हित पूर्णांक    has_tda9874:1;
	अचिन्हित पूर्णांक    has_dvb:1;
	अचिन्हित पूर्णांक    has_zl10353:1;
	अचिन्हित पूर्णांक    has_eeprom:1;
	अचिन्हित पूर्णांक    has_remote:1;
	अचिन्हित पूर्णांक    has_radio:1;
पूर्ण;

काष्ठा पंचांग6000_dvb अणु
	काष्ठा dvb_adapter	adapter;
	काष्ठा dvb_demux	demux;
	काष्ठा dvb_frontend	*frontend;
	काष्ठा dmxdev		dmxdev;
	अचिन्हित पूर्णांक		streams;
	काष्ठा urb		*bulk_urb;
	काष्ठा mutex		mutex;
पूर्ण;

काष्ठा snd_पंचांग6000_card अणु
	काष्ठा snd_card			*card;
	spinlock_t			reg_lock;
	काष्ठा पंचांग6000_core		*core;
	काष्ठा snd_pcm_substream	*substream;

	/* temporary data क्रम buffer fill processing */
	अचिन्हित			buf_pos;
	अचिन्हित			period_pos;
पूर्ण;

काष्ठा पंचांग6000_endpoपूर्णांक अणु
	काष्ठा usb_host_endpoपूर्णांक	*endp;
	__u8				bInterfaceNumber;
	__u8				bAlternateSetting;
	अचिन्हित			maxsize;
पूर्ण;

#घोषणा TM6000_QUIRK_NO_USB_DELAY (1 << 0)

काष्ठा पंचांग6000_core अणु
	/* generic device properties */
	अक्षर				name[30];	/* name (including minor) of the device */
	पूर्णांक				model;		/* index in the device_data काष्ठा */
	पूर्णांक				devno;		/* marks the number of this device */
	क्रमागत पंचांग6000_devtype		dev_type;	/* type of device */
	अचिन्हित अक्षर			eedata[256];	/* Eeprom data */
	अचिन्हित			eedata_size;	/* Size of the eeprom info */

	v4l2_std_id                     norm;           /* Current norm */
	पूर्णांक				width, height;	/* Selected resolution */

	क्रमागत पंचांग6000_core_state		state;

	/* Device Capabilities*/
	काष्ठा पंचांग6000_capabilities	caps;

	/* Used to load alsa/dvb */
	काष्ठा work_काष्ठा		request_module_wk;

	/* Tuner configuration */
	पूर्णांक				tuner_type;		/* type of the tuner */
	पूर्णांक				tuner_addr;		/* tuner address */

	काष्ठा पंचांग6000_gpio		gpio;

	अक्षर				*ir_codes;

	__u8				radio;

	/* Demodulator configuration */
	पूर्णांक				demod_addr;	/* demodulator address */

	पूर्णांक				audio_bitrate;
	/* i2c i/o */
	काष्ठा i2c_adapter		i2c_adap;
	काष्ठा i2c_client		i2c_client;


	/* extension */
	काष्ठा list_head		devlist;

	/* video क्रम linux */
	पूर्णांक				users;

	/* various device info */
	काष्ठा पंचांग6000_fh		*resources;	/* Poपूर्णांकs to fh that is streaming */
	bool				is_res_पढ़ो;

	काष्ठा video_device		vfd;
	काष्ठा video_device		radio_dev;
	काष्ठा पंचांग6000_dmaqueue		vidq;
	काष्ठा v4l2_device		v4l2_dev;
	काष्ठा v4l2_ctrl_handler	ctrl_handler;
	काष्ठा v4l2_ctrl_handler	radio_ctrl_handler;

	पूर्णांक				input;
	काष्ठा पंचांग6000_input		vinput[3];	/* video input */
	काष्ठा पंचांग6000_input		rinput;		/* radio input */

	पूर्णांक				freq;
	अचिन्हित पूर्णांक			fourcc;

	क्रमागत पंचांग6000_mode		mode;

	पूर्णांक				ctl_mute;             /* audio */
	पूर्णांक				ctl_volume;
	पूर्णांक				amode;

	/* DVB-T support */
	काष्ठा पंचांग6000_dvb		*dvb;

	/* audio support */
	काष्ठा snd_पंचांग6000_card		*adev;
	काष्ठा work_काष्ठा		wq_trigger;   /* Trigger to start/stop audio क्रम alsa module */
	atomic_t			stream_started;  /* stream should be running अगर true */

	काष्ठा पंचांग6000_IR		*ir;

	/* locks */
	काष्ठा mutex			lock;
	काष्ठा mutex			usb_lock;

	/* usb transfer */
	काष्ठा usb_device		*udev;		/* the usb device */

	काष्ठा पंचांग6000_endpoपूर्णांक		bulk_in, bulk_out, isoc_in, isoc_out;
	काष्ठा पंचांग6000_endpoपूर्णांक		पूर्णांक_in, पूर्णांक_out;

	/* scaler!=0 अगर scaler is active*/
	पूर्णांक				scaler;

		/* Isoc control काष्ठा */
	काष्ठा usb_isoc_ctl          isoc_ctl;

	spinlock_t                   slock;

	/* urb dma buffers */
	अक्षर				**urb_buffer;
	dma_addr_t			*urb_dma;
	अचिन्हित पूर्णांक			urb_size;

	अचिन्हित दीर्घ quirks;
पूर्ण;

क्रमागत पंचांग6000_ops_type अणु
	TM6000_AUDIO = 0x10,
	TM6000_DVB = 0x20,
पूर्ण;

काष्ठा पंचांग6000_ops अणु
	काष्ठा list_head	next;
	अक्षर			*name;
	क्रमागत पंचांग6000_ops_type	type;
	पूर्णांक (*init)(काष्ठा पंचांग6000_core *);
	पूर्णांक (*fini)(काष्ठा पंचांग6000_core *);
	पूर्णांक (*fillbuf)(काष्ठा पंचांग6000_core *, अक्षर *buf, पूर्णांक size);
पूर्ण;

काष्ठा पंचांग6000_fh अणु
	काष्ठा v4l2_fh		     fh;
	काष्ठा पंचांग6000_core           *dev;
	अचिन्हित पूर्णांक                 radio;

	/* video capture */
	काष्ठा पंचांग6000_fmt            *fmt;
	अचिन्हित पूर्णांक                 width, height;
	काष्ठा videobuf_queue        vb_vidq;

	क्रमागत v4l2_buf_type           type;
पूर्ण;

#घोषणा TM6000_STD	(V4L2_STD_PAL|V4L2_STD_PAL_N|V4L2_STD_PAL_Nc|    \
			V4L2_STD_PAL_M|V4L2_STD_PAL_60|V4L2_STD_NTSC_M| \
			V4L2_STD_NTSC_M_JP|V4L2_STD_SECAM)

/* In पंचांग6000-cards.c */

पूर्णांक पंचांग6000_tuner_callback(व्योम *ptr, पूर्णांक component, पूर्णांक command, पूर्णांक arg);
पूर्णांक पंचांग6000_xc5000_callback(व्योम *ptr, पूर्णांक component, पूर्णांक command, पूर्णांक arg);
पूर्णांक पंचांग6000_cards_setup(काष्ठा पंचांग6000_core *dev);
व्योम पंचांग6000_flash_led(काष्ठा पंचांग6000_core *dev, u8 state);

/* In पंचांग6000-core.c */

पूर्णांक पंचांग6000_पढ़ो_ग_लिखो_usb(काष्ठा पंचांग6000_core *dev, u8 reqtype, u8 req,
			   u16 value, u16 index, u8 *buf, u16 len);
पूर्णांक पंचांग6000_get_reg(काष्ठा पंचांग6000_core *dev, u8 req, u16 value, u16 index);
पूर्णांक पंचांग6000_get_reg16(काष्ठा पंचांग6000_core *dev, u8 req, u16 value, u16 index);
पूर्णांक पंचांग6000_get_reg32(काष्ठा पंचांग6000_core *dev, u8 req, u16 value, u16 index);
पूर्णांक पंचांग6000_set_reg(काष्ठा पंचांग6000_core *dev, u8 req, u16 value, u16 index);
पूर्णांक पंचांग6000_set_reg_mask(काष्ठा पंचांग6000_core *dev, u8 req, u16 value,
						u16 index, u16 mask);
पूर्णांक पंचांग6000_i2c_reset(काष्ठा पंचांग6000_core *dev, u16 tsleep);
पूर्णांक पंचांग6000_init(काष्ठा पंचांग6000_core *dev);
पूर्णांक पंचांग6000_reset(काष्ठा पंचांग6000_core *dev);

पूर्णांक पंचांग6000_init_analog_mode(काष्ठा पंचांग6000_core *dev);
पूर्णांक पंचांग6000_init_digital_mode(काष्ठा पंचांग6000_core *dev);
पूर्णांक पंचांग6000_set_audio_bitrate(काष्ठा पंचांग6000_core *dev, पूर्णांक bitrate);
पूर्णांक पंचांग6000_set_audio_rinput(काष्ठा पंचांग6000_core *dev);
पूर्णांक पंचांग6000_tvaudio_set_mute(काष्ठा पंचांग6000_core *dev, u8 mute);
व्योम पंचांग6000_set_volume(काष्ठा पंचांग6000_core *dev, पूर्णांक vol);

पूर्णांक पंचांग6000_v4l2_रेजिस्टर(काष्ठा पंचांग6000_core *dev);
पूर्णांक पंचांग6000_v4l2_unरेजिस्टर(काष्ठा पंचांग6000_core *dev);
पूर्णांक पंचांग6000_v4l2_निकास(व्योम);
व्योम पंचांग6000_set_fourcc_क्रमmat(काष्ठा पंचांग6000_core *dev);

व्योम पंचांग6000_हटाओ_from_devlist(काष्ठा पंचांग6000_core *dev);
व्योम पंचांग6000_add_पूर्णांकo_devlist(काष्ठा पंचांग6000_core *dev);
पूर्णांक पंचांग6000_रेजिस्टर_extension(काष्ठा पंचांग6000_ops *ops);
व्योम पंचांग6000_unरेजिस्टर_extension(काष्ठा पंचांग6000_ops *ops);
व्योम पंचांग6000_init_extension(काष्ठा पंचांग6000_core *dev);
व्योम पंचांग6000_बंद_extension(काष्ठा पंचांग6000_core *dev);
पूर्णांक पंचांग6000_call_fillbuf(काष्ठा पंचांग6000_core *dev, क्रमागत पंचांग6000_ops_type type,
			अक्षर *buf, पूर्णांक size);


/* In पंचांग6000-stds.c */
व्योम पंचांग6000_get_std_res(काष्ठा पंचांग6000_core *dev);
पूर्णांक पंचांग6000_set_standard(काष्ठा पंचांग6000_core *dev);

/* In पंचांग6000-i2c.c */
पूर्णांक पंचांग6000_i2c_रेजिस्टर(काष्ठा पंचांग6000_core *dev);
पूर्णांक पंचांग6000_i2c_unरेजिस्टर(काष्ठा पंचांग6000_core *dev);

/* In पंचांग6000-queue.c */

पूर्णांक पंचांग6000_v4l2_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma);

पूर्णांक पंचांग6000_vidioc_streamon(काष्ठा file *file, व्योम *priv,
			   क्रमागत v4l2_buf_type i);
पूर्णांक पंचांग6000_vidioc_streamoff(काष्ठा file *file, व्योम *priv,
			    क्रमागत v4l2_buf_type i);
पूर्णांक पंचांग6000_vidioc_reqbufs(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_requestbuffers *rb);
पूर्णांक पंचांग6000_vidioc_querybuf(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_buffer *b);
पूर्णांक पंचांग6000_vidioc_qbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *b);
पूर्णांक पंचांग6000_vidioc_dqbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *b);
sमाप_प्रकार पंचांग6000_v4l2_पढ़ो(काष्ठा file *filp, अक्षर __user * buf, माप_प्रकार count,
			 loff_t *f_pos);
अचिन्हित पूर्णांक पंचांग6000_v4l2_poll(काष्ठा file *file,
			      काष्ठा poll_table_काष्ठा *रुको);
पूर्णांक पंचांग6000_queue_init(काष्ठा पंचांग6000_core *dev);

/* In पंचांग6000-alsa.c */
/*पूर्णांक पंचांग6000_audio_init(काष्ठा पंचांग6000_core *dev, पूर्णांक idx);*/

/* In पंचांग6000-input.c */
पूर्णांक पंचांग6000_ir_init(काष्ठा पंचांग6000_core *dev);
पूर्णांक पंचांग6000_ir_fini(काष्ठा पंचांग6000_core *dev);
व्योम पंचांग6000_ir_रुको(काष्ठा पंचांग6000_core *dev, u8 state);
पूर्णांक पंचांग6000_ir_पूर्णांक_start(काष्ठा पंचांग6000_core *dev);
व्योम पंचांग6000_ir_पूर्णांक_stop(काष्ठा पंचांग6000_core *dev);

/* Debug stuff */

बाह्य पूर्णांक पंचांग6000_debug;

#घोषणा dprपूर्णांकk(dev, level, fmt, arg...) करो अणु\
	अगर (पंचांग6000_debug & level) \
		prपूर्णांकk(KERN_INFO "(%lu) %s %s :"fmt, jअगरfies, \
			 dev->name, __func__ , ##arg); पूर्ण जबतक (0)

#घोषणा V4L2_DEBUG_REG		0x0004
#घोषणा V4L2_DEBUG_I2C		0x0008
#घोषणा V4L2_DEBUG_QUEUE	0x0010
#घोषणा V4L2_DEBUG_ISOC		0x0020
#घोषणा V4L2_DEBUG_RES_LOCK	0x0040	/* Resource locking */
#घोषणा V4L2_DEBUG_OPEN		0x0080	/* video खोलो/बंद debug */

#घोषणा पंचांग6000_err(fmt, arg...) करो अणु\
	prपूर्णांकk(KERN_ERR "tm6000 %s :"fmt, \
		__func__ , ##arg); पूर्ण जबतक (0)
