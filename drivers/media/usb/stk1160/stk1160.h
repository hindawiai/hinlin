<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * STK1160 driver
 *
 * Copyright (C) 2012 Ezequiel Garcia
 * <elezegarcia--a.t--gmail.com>
 *
 * Based on Easycap driver by R.M. Thomas
 *	Copyright (C) 2010 R.M. Thomas
 *	<rmthomas--a.t--sciolus.org>
 */

#समावेश <linux/i2c.h>
#समावेश <sound/core.h>
#समावेश <sound/ac97_codec.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

#घोषणा STK1160_VERSION		"0.9.5"
#घोषणा STK1160_VERSION_NUM	0x000905

/* Decide on number of packets क्रम each buffer */
#घोषणा STK1160_NUM_PACKETS 64

/* Number of buffers क्रम isoc transfers */
#घोषणा STK1160_NUM_BUFS 16
#घोषणा STK1160_MIN_BUFS 1

/* TODO: This endpoपूर्णांक address should be retrieved */
#घोषणा STK1160_EP_VIDEO 0x82
#घोषणा STK1160_EP_AUDIO 0x81

/* Max and min video buffers */
#घोषणा STK1160_MIN_VIDEO_BUFFERS 8
#घोषणा STK1160_MAX_VIDEO_BUFFERS 32

#घोषणा STK1160_MIN_PKT_SIZE 3072

#घोषणा STK1160_MAX_INPUT 4
#घोषणा STK1160_SVIDEO_INPUT 4

#घोषणा STK1160_AC97_TIMEOUT 50

#घोषणा STK1160_I2C_TIMEOUT 100

/* TODO: Prपूर्णांक helpers
 * I could use dev_xxx, pr_xxx, v4l2_xxx or prपूर्णांकk.
 * However, there isn't a solid consensus on which
 * new drivers should use.
 *
 */
#अगर_घोषित DEBUG
#घोषणा stk1160_dbg(fmt, args...) \
	prपूर्णांकk(KERN_DEBUG "stk1160: " fmt,  ## args)
#अन्यथा
#घोषणा stk1160_dbg(fmt, args...)
#पूर्ण_अगर

#घोषणा stk1160_info(fmt, args...) \
	pr_info("stk1160: " fmt, ## args)

#घोषणा stk1160_warn(fmt, args...) \
	pr_warn("stk1160: " fmt, ## args)

#घोषणा stk1160_err(fmt, args...) \
	pr_err("stk1160: " fmt, ## args)

/* Buffer क्रम one video frame */
काष्ठा stk1160_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;

	व्योम *mem;
	अचिन्हित पूर्णांक length;		/* buffer length */
	अचिन्हित पूर्णांक bytesused;		/* bytes written */
	पूर्णांक odd;			/* current oddity */

	/*
	 * Since we पूर्णांकerlace two fields per frame,
	 * this is dअगरferent from bytesused.
	 */
	अचिन्हित पूर्णांक pos;		/* current pos inside buffer */
पूर्ण;

काष्ठा stk1160_isoc_ctl अणु
	/* max packet size of isoc transaction */
	पूर्णांक max_pkt_size;

	/* number of allocated urbs */
	पूर्णांक num_bufs;

	/* urb क्रम isoc transfers */
	काष्ठा urb **urb;

	/* transfer buffers क्रम isoc transfer */
	अक्षर **transfer_buffer;

	/* current buffer */
	काष्ठा stk1160_buffer *buf;
पूर्ण;

काष्ठा stk1160_fmt अणु
	u32   fourcc;          /* v4l2 क्रमmat id */
	पूर्णांक   depth;
पूर्ण;

काष्ठा stk1160 अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा video_device vdev;
	काष्ठा v4l2_ctrl_handler ctrl_handler;

	काष्ठा device *dev;
	काष्ठा usb_device *udev;

	/* saa7115 subdev */
	काष्ठा v4l2_subdev *sd_saa7115;

	/* isoc control काष्ठा */
	काष्ठा list_head avail_bufs;

	/* video capture */
	काष्ठा vb2_queue vb_vidq;

	/* max packet size of isoc transaction */
	पूर्णांक max_pkt_size;
	/* array of wMaxPacketSize */
	अचिन्हित पूर्णांक *alt_max_pkt_size;
	/* alternate */
	पूर्णांक alt;
	/* Number of alternative settings */
	पूर्णांक num_alt;

	काष्ठा stk1160_isoc_ctl isoc_ctl;

	/* frame properties */
	पूर्णांक width;		  /* current frame width */
	पूर्णांक height;		  /* current frame height */
	अचिन्हित पूर्णांक ctl_input;	  /* selected input */
	v4l2_std_id norm;	  /* current norm */
	काष्ठा stk1160_fmt *fmt;  /* selected क्रमmat */

	अचिन्हित पूर्णांक sequence;

	/* i2c i/o */
	काष्ठा i2c_adapter i2c_adap;
	काष्ठा i2c_client i2c_client;

	काष्ठा mutex v4l_lock;
	काष्ठा mutex vb_queue_lock;
	spinlock_t buf_lock;

	काष्ठा file *fh_owner;	/* filehandle ownership */

	/* EXPERIMENTAL */
	काष्ठा snd_card *snd_card;
पूर्ण;

काष्ठा regval अणु
	u16 reg;
	u16 val;
पूर्ण;

/* Provided by stk1160-v4l.c */
पूर्णांक stk1160_vb2_setup(काष्ठा stk1160 *dev);
पूर्णांक stk1160_video_रेजिस्टर(काष्ठा stk1160 *dev);
व्योम stk1160_video_unरेजिस्टर(काष्ठा stk1160 *dev);
व्योम stk1160_clear_queue(काष्ठा stk1160 *dev);

/* Provided by stk1160-video.c */
पूर्णांक stk1160_alloc_isoc(काष्ठा stk1160 *dev);
व्योम stk1160_मुक्त_isoc(काष्ठा stk1160 *dev);
व्योम stk1160_cancel_isoc(काष्ठा stk1160 *dev);
व्योम stk1160_uninit_isoc(काष्ठा stk1160 *dev);

/* Provided by stk1160-i2c.c */
पूर्णांक stk1160_i2c_रेजिस्टर(काष्ठा stk1160 *dev);
पूर्णांक stk1160_i2c_unरेजिस्टर(काष्ठा stk1160 *dev);

/* Provided by stk1160-core.c */
पूर्णांक stk1160_पढ़ो_reg(काष्ठा stk1160 *dev, u16 reg, u8 *value);
पूर्णांक stk1160_ग_लिखो_reg(काष्ठा stk1160 *dev, u16 reg, u16 value);
पूर्णांक stk1160_ग_लिखो_regs_req(काष्ठा stk1160 *dev, u8 req, u16 reg,
		अक्षर *buf, पूर्णांक len);
पूर्णांक stk1160_पढ़ो_reg_req_len(काष्ठा stk1160 *dev, u8 req, u16 reg,
		अक्षर *buf, पूर्णांक len);
व्योम stk1160_select_input(काष्ठा stk1160 *dev);

/* Provided by stk1160-ac97.c */
व्योम stk1160_ac97_setup(काष्ठा stk1160 *dev);
