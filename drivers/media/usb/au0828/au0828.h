<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम the Auvitek AU0828 USB bridge
 *
 *  Copyright (c) 2008 Steven Toth <stoth@linuxtv.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/usb.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <media/tveeprom.h>

/* Analog */
#समावेश <linux/videodev2.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/media-device.h>
#समावेश <media/media-dev-allocator.h>

/* DVB */
#समावेश <media/demux.h>
#समावेश <media/dmxdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>
#समावेश <media/dvbdev.h>

#समावेश "au0828-reg.h"
#समावेश "au0828-cards.h"

#घोषणा URB_COUNT   16
#घोषणा URB_बफ_मानE (0xe522)

/* Analog स्थिरants */
#घोषणा NTSC_STD_W      720
#घोषणा NTSC_STD_H      480

#घोषणा AU0828_INTERLACED_DEFAULT       1

/* Definition क्रम AU0828 USB transfer */
#घोषणा AU0828_MAX_ISO_BUFS    12  /* maybe resize this value in the future */
#घोषणा AU0828_ISO_PACKETS_PER_URB      128

#घोषणा AU0828_MIN_BUF 4
#घोषणा AU0828_DEF_BUF 8

#घोषणा AU0828_MAX_INPUT        4

/* au0828 resource types (used क्रम res_get/res_lock etc */
#घोषणा AU0828_RESOURCE_VIDEO 0x01
#घोषणा AU0828_RESOURCE_VBI   0x02

क्रमागत au0828_itype अणु
	AU0828_VMUX_UNDEFINED = 0,
	AU0828_VMUX_COMPOSITE,
	AU0828_VMUX_SVIDEO,
	AU0828_VMUX_CABLE,
	AU0828_VMUX_TELEVISION,
	AU0828_VMUX_DVB,
पूर्ण;

काष्ठा au0828_input अणु
	क्रमागत au0828_itype type;
	अचिन्हित पूर्णांक vmux;
	अचिन्हित पूर्णांक amux;
	व्योम (*audio_setup) (व्योम *priv, पूर्णांक enable);
पूर्ण;

काष्ठा au0828_board अणु
	अक्षर *name;
	अचिन्हित पूर्णांक tuner_type;
	अचिन्हित अक्षर tuner_addr;
	अचिन्हित अक्षर i2c_clk_भागider;
	अचिन्हित अक्षर has_ir_i2c:1;
	अचिन्हित अक्षर has_analog:1;
	काष्ठा au0828_input input[AU0828_MAX_INPUT];
पूर्ण;

काष्ठा au0828_dvb अणु
	काष्ठा mutex lock;
	काष्ठा dvb_adapter adapter;
	काष्ठा dvb_frontend *frontend;
	काष्ठा dvb_demux demux;
	काष्ठा dmxdev dmxdev;
	काष्ठा dmx_frontend fe_hw;
	काष्ठा dmx_frontend fe_mem;
	काष्ठा dvb_net net;
	पूर्णांक feeding;
	पूर्णांक start_count;
	पूर्णांक stop_count;

	पूर्णांक (*set_frontend)(काष्ठा dvb_frontend *fe);
पूर्ण;

क्रमागत au0828_stream_state अणु
	STREAM_OFF,
	STREAM_INTERRUPT,
	STREAM_ON
पूर्ण;

#घोषणा AUVI_INPUT(nr) (dev->board.input[nr])

/* device state */
क्रमागत au0828_dev_state अणु
	DEV_INITIALIZED = 0,
	DEV_DISCONNECTED = 1,
	DEV_MISCONFIGURED = 2
पूर्ण;

काष्ठा au0828_dev;

काष्ठा au0828_usb_isoc_ctl अणु
		/* max packet size of isoc transaction */
	पूर्णांक				max_pkt_size;

		/* number of allocated urbs */
	पूर्णांक				num_bufs;

		/* urb क्रम isoc transfers */
	काष्ठा urb			**urb;

		/* transfer buffers क्रम isoc transfer */
	अक्षर				**transfer_buffer;

		/* Last buffer command and region */
	u8				cmd;
	पूर्णांक				pos, size, pktsize;

		/* Last field: ODD or EVEN? */
	पूर्णांक				field;

		/* Stores incomplete commands */
	u32				पंचांगp_buf;
	पूर्णांक				पंचांगp_buf_len;

		/* Stores alपढ़ोy requested buffers */
	काष्ठा au0828_buffer		*buf;
	काष्ठा au0828_buffer		*vbi_buf;

		/* Stores the number of received fields */
	पूर्णांक				nfields;

		/* isoc urb callback */
	पूर्णांक (*isoc_copy) (काष्ठा au0828_dev *dev, काष्ठा urb *urb);

पूर्ण;

/* buffer क्रम one video frame */
काष्ठा au0828_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;

	व्योम *mem;
	अचिन्हित दीर्घ length;
	पूर्णांक top_field;
	/* poपूर्णांकer to vदो_स्मृति memory address in vb */
	अक्षर *vb_buf;
पूर्ण;

काष्ठा au0828_dmaqueue अणु
	काष्ठा list_head       active;
	/* Counters to control buffer fill */
	पूर्णांक                    pos;
पूर्ण;

काष्ठा au0828_dev अणु
	काष्ठा mutex mutex;
	काष्ठा usb_device	*usbdev;
	पूर्णांक			boardnr;
	काष्ठा au0828_board	board;
	u8			ctrlmsg[64];

	/* I2C */
	काष्ठा i2c_adapter		i2c_adap;
	काष्ठा i2c_algorithm		i2c_algo;
	काष्ठा i2c_client		i2c_client;
	u32				i2c_rc;

	/* Digital */
	काष्ठा au0828_dvb		dvb;
	काष्ठा work_काष्ठा              restart_streaming;
	काष्ठा समयr_list               bulk_समयout;
	पूर्णांक                             bulk_समयout_running;

#अगर_घोषित CONFIG_VIDEO_AU0828_V4L2
	/* Analog */
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_ctrl_handler v4l2_ctrl_hdl;
#पूर्ण_अगर
#अगर_घोषित CONFIG_VIDEO_AU0828_RC
	काष्ठा au0828_rc *ir;
#पूर्ण_अगर

	काष्ठा video_device vdev;
	काष्ठा video_device vbi_dev;

	/* Videobuf2 */
	काष्ठा vb2_queue vb_vidq;
	काष्ठा vb2_queue vb_vbiq;
	काष्ठा mutex vb_queue_lock;
	काष्ठा mutex vb_vbi_queue_lock;

	अचिन्हित पूर्णांक frame_count;
	अचिन्हित पूर्णांक vbi_frame_count;

	काष्ठा समयr_list vid_समयout;
	पूर्णांक vid_समयout_running;
	काष्ठा समयr_list vbi_समयout;
	पूर्णांक vbi_समयout_running;

	पूर्णांक users;
	पूर्णांक streaming_users;

	पूर्णांक width;
	पूर्णांक height;
	पूर्णांक vbi_width;
	पूर्णांक vbi_height;
	u32 vbi_पढ़ो;
	v4l2_std_id std;
	u32 field_size;
	u32 frame_size;
	u32 bytesperline;
	पूर्णांक type;
	u8 ctrl_ainput;
	__u8 isoc_in_endpoपूर्णांकaddr;
	u8 isoc_init_ok;
	पूर्णांक greenscreen_detected;
	पूर्णांक ctrl_freq;
	पूर्णांक input_type;
	पूर्णांक std_set_in_tuner_core;
	अचिन्हित पूर्णांक ctrl_input;
	दीर्घ अचिन्हित पूर्णांक dev_state; /* defined at क्रमागत au0828_dev_state */;
	क्रमागत au0828_stream_state stream_state;
	रुको_queue_head_t खोलो;

	काष्ठा mutex lock;

	/* Isoc control काष्ठा */
	काष्ठा au0828_dmaqueue vidq;
	काष्ठा au0828_dmaqueue vbiq;
	काष्ठा au0828_usb_isoc_ctl isoc_ctl;
	spinlock_t slock;

	/* usb transfer */
	पूर्णांक alt;		/* alternate */
	पूर्णांक max_pkt_size;	/* max packet size of isoc transaction */
	पूर्णांक num_alt;		/* Number of alternative settings */
	अचिन्हित पूर्णांक *alt_max_pkt_size;	/* array of wMaxPacketSize */
	काष्ठा urb *urb[AU0828_MAX_ISO_BUFS];	/* urb क्रम isoc transfers */
	अक्षर *transfer_buffer[AU0828_MAX_ISO_BUFS];/* transfer buffers क्रम isoc
						   transfer */

	/* DVB USB / URB Related */
	bool		urb_streaming, need_urb_start;
	काष्ठा urb	*urbs[URB_COUNT];

	/* Pपुनः_स्मृतिated transfer digital transfer buffers */

	अक्षर *dig_transfer_buffer[URB_COUNT];

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_device *media_dev;
	काष्ठा media_pad video_pad, vbi_pad;
	काष्ठा media_entity *decoder;
	काष्ठा media_entity input_ent[AU0828_MAX_INPUT];
	काष्ठा media_pad input_pad[AU0828_MAX_INPUT];
	काष्ठा media_entity_notअगरy entity_notअगरy;
	काष्ठा media_entity *tuner;
	काष्ठा media_link *active_link;
	काष्ठा media_entity *active_source;
	काष्ठा media_entity *active_sink;
	काष्ठा media_entity *active_link_owner;
	काष्ठा media_entity *active_link_user;
	काष्ठा media_pipeline *active_link_user_pipe;
	bool active_link_shared;
#पूर्ण_अगर
पूर्ण;


/* ----------------------------------------------------------- */
#घोषणा au0828_पढ़ो(dev, reg) au0828_पढ़ोreg(dev, reg)
#घोषणा au0828_ग_लिखो(dev, reg, value) au0828_ग_लिखोreg(dev, reg, value)
#घोषणा au0828_anकरोr(dev, reg, mask, value)				\
	 au0828_ग_लिखोreg(dev, reg,					\
	(au0828_पढ़ोreg(dev, reg) & ~(mask)) | ((value) & (mask)))

#घोषणा au0828_set(dev, reg, bit) au0828_anकरोr(dev, (reg), (bit), (bit))
#घोषणा au0828_clear(dev, reg, bit) au0828_anकरोr(dev, (reg), (bit), 0)

/* ----------------------------------------------------------- */
/* au0828-core.c */
बाह्य u32 au0828_पढ़ो(काष्ठा au0828_dev *dev, u16 reg);
बाह्य u32 au0828_ग_लिखो(काष्ठा au0828_dev *dev, u16 reg, u32 val);
बाह्य व्योम au0828_usb_release(काष्ठा au0828_dev *dev);
बाह्य पूर्णांक au0828_debug;

/* ----------------------------------------------------------- */
/* au0828-cards.c */
बाह्य काष्ठा au0828_board au0828_boards[];
बाह्य काष्ठा usb_device_id au0828_usb_id_table[];
बाह्य व्योम au0828_gpio_setup(काष्ठा au0828_dev *dev);
बाह्य पूर्णांक au0828_tuner_callback(व्योम *priv, पूर्णांक component,
				 पूर्णांक command, पूर्णांक arg);
बाह्य व्योम au0828_card_setup(काष्ठा au0828_dev *dev);

/* ----------------------------------------------------------- */
/* au0828-i2c.c */
बाह्य पूर्णांक au0828_i2c_रेजिस्टर(काष्ठा au0828_dev *dev);
बाह्य पूर्णांक au0828_i2c_unरेजिस्टर(काष्ठा au0828_dev *dev);

/* ----------------------------------------------------------- */
/* au0828-video.c */
बाह्य पूर्णांक au0828_start_analog_streaming(काष्ठा vb2_queue *vq,
						अचिन्हित पूर्णांक count);
बाह्य व्योम au0828_stop_vbi_streaming(काष्ठा vb2_queue *vq);
#अगर_घोषित CONFIG_VIDEO_AU0828_V4L2
बाह्य पूर्णांक au0828_v4l2_device_रेजिस्टर(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
				      काष्ठा au0828_dev *dev);

बाह्य पूर्णांक au0828_analog_रेजिस्टर(काष्ठा au0828_dev *dev,
			   काष्ठा usb_पूर्णांकerface *पूर्णांकerface);
बाह्य पूर्णांक au0828_analog_unरेजिस्टर(काष्ठा au0828_dev *dev);
बाह्य व्योम au0828_usb_v4l2_media_release(काष्ठा au0828_dev *dev);
बाह्य व्योम au0828_v4l2_suspend(काष्ठा au0828_dev *dev);
बाह्य व्योम au0828_v4l2_resume(काष्ठा au0828_dev *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक au0828_v4l2_device_रेजिस्टर(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
					      काष्ठा au0828_dev *dev)
अणु वापस 0; पूर्ण;
अटल अंतरभूत पूर्णांक au0828_analog_रेजिस्टर(काष्ठा au0828_dev *dev,
				     काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु वापस 0; पूर्ण;
अटल अंतरभूत पूर्णांक au0828_analog_unरेजिस्टर(काष्ठा au0828_dev *dev)
अणु वापस 0; पूर्ण;
अटल अंतरभूत व्योम au0828_usb_v4l2_media_release(काष्ठा au0828_dev *dev) अणु पूर्ण;
अटल अंतरभूत व्योम au0828_v4l2_suspend(काष्ठा au0828_dev *dev) अणु पूर्ण;
अटल अंतरभूत व्योम au0828_v4l2_resume(काष्ठा au0828_dev *dev) अणु पूर्ण;
#पूर्ण_अगर

/* ----------------------------------------------------------- */
/* au0828-dvb.c */
बाह्य पूर्णांक au0828_dvb_रेजिस्टर(काष्ठा au0828_dev *dev);
बाह्य व्योम au0828_dvb_unरेजिस्टर(काष्ठा au0828_dev *dev);
व्योम au0828_dvb_suspend(काष्ठा au0828_dev *dev);
व्योम au0828_dvb_resume(काष्ठा au0828_dev *dev);

/* au0828-vbi.c */
बाह्य स्थिर काष्ठा vb2_ops au0828_vbi_qops;

#घोषणा dprपूर्णांकk(level, fmt, arg...)\
	करो अणु अगर (au0828_debug & level)\
		prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ## arg);\
	पूर्ण जबतक (0)

/* au0828-input.c */
#अगर_घोषित CONFIG_VIDEO_AU0828_RC
बाह्य पूर्णांक au0828_rc_रेजिस्टर(काष्ठा au0828_dev *dev);
बाह्य व्योम au0828_rc_unरेजिस्टर(काष्ठा au0828_dev *dev);
बाह्य पूर्णांक au0828_rc_suspend(काष्ठा au0828_dev *dev);
बाह्य पूर्णांक au0828_rc_resume(काष्ठा au0828_dev *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक au0828_rc_रेजिस्टर(काष्ठा au0828_dev *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम au0828_rc_unरेजिस्टर(काष्ठा au0828_dev *dev) अणु पूर्ण
अटल अंतरभूत पूर्णांक au0828_rc_suspend(काष्ठा au0828_dev *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक au0828_rc_resume(काष्ठा au0828_dev *dev) अणु वापस 0; पूर्ण
#पूर्ण_अगर
