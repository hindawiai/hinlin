<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Zoran 364xx based USB webcam module version 0.73
 *
 * Allows you to use your USB webcam with V4L2 applications
 * This is still in heavy development !
 *
 * Copyright (C) 2004  Antoine Jacquet <royale@zerezo.com>
 * http://royale.zerezo.com/zr364xx/
 *
 * Heavily inspired by usb-skeleton.c, vicam.c, cpia.c and spca50x.c drivers
 * V4L2 version inspired by meye.c driver
 *
 * Some video buffer code by Lamarque based on s2255drv.c and vivi.c drivers.
 */


#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/usb.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf-vदो_स्मृति.h>


/* Version Inक्रमmation */
#घोषणा DRIVER_VERSION "0.7.4"
#घोषणा DRIVER_AUTHOR "Antoine Jacquet, http://royale.zerezo.com/"
#घोषणा DRIVER_DESC "Zoran 364xx"


/* Camera */
#घोषणा FRAMES 1
#घोषणा MAX_FRAME_SIZE 200000
#घोषणा BUFFER_SIZE 0x1000
#घोषणा CTRL_TIMEOUT 500

#घोषणा ZR364XX_DEF_BUFS	4
#घोषणा ZR364XX_READ_IDLE	0
#घोषणा ZR364XX_READ_FRAME	1

/* Debug macro */
#घोषणा DBG(fmt, args...) \
	करो अणु \
		अगर (debug) अणु \
			prपूर्णांकk(KERN_INFO KBUILD_MODNAME " " fmt, ##args); \
		पूर्ण \
	पूर्ण जबतक (0)

/*#घोषणा FULL_DEBUG 1*/
#अगर_घोषित FULL_DEBUG
#घोषणा _DBG DBG
#अन्यथा
#घोषणा _DBG(fmt, args...)
#पूर्ण_अगर

/* Init methods, need to find nicer names क्रम these
 * the exact names of the chipsets would be the best अगर someone finds it */
#घोषणा METHOD0 0
#घोषणा METHOD1 1
#घोषणा METHOD2 2
#घोषणा METHOD3 3


/* Module parameters */
अटल पूर्णांक debug;
अटल पूर्णांक mode;


/* Module parameters पूर्णांकerface */
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Debug level");
module_param(mode, पूर्णांक, 0644);
MODULE_PARM_DESC(mode, "0 = 320x240, 1 = 160x120, 2 = 640x480");


/* Devices supported by this driver
 * .driver_info contains the init method used by the camera */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x08ca, 0x0109), .driver_info = METHOD0 पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4024), .driver_info = METHOD0 पूर्ण,
	अणुUSB_DEVICE(0x0d64, 0x0108), .driver_info = METHOD0 पूर्ण,
	अणुUSB_DEVICE(0x0546, 0x3187), .driver_info = METHOD0 पूर्ण,
	अणुUSB_DEVICE(0x0d64, 0x3108), .driver_info = METHOD0 पूर्ण,
	अणुUSB_DEVICE(0x0595, 0x4343), .driver_info = METHOD0 पूर्ण,
	अणुUSB_DEVICE(0x0bb0, 0x500d), .driver_info = METHOD0 पूर्ण,
	अणुUSB_DEVICE(0x0feb, 0x2004), .driver_info = METHOD0 पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xb500), .driver_info = METHOD0 पूर्ण,
	अणुUSB_DEVICE(0x08ca, 0x2062), .driver_info = METHOD2 पूर्ण,
	अणुUSB_DEVICE(0x052b, 0x1a18), .driver_info = METHOD1 पूर्ण,
	अणुUSB_DEVICE(0x04c8, 0x0729), .driver_info = METHOD0 पूर्ण,
	अणुUSB_DEVICE(0x04f2, 0xa208), .driver_info = METHOD0 पूर्ण,
	अणुUSB_DEVICE(0x0784, 0x0040), .driver_info = METHOD1 पूर्ण,
	अणुUSB_DEVICE(0x06d6, 0x0034), .driver_info = METHOD0 पूर्ण,
	अणुUSB_DEVICE(0x0a17, 0x0062), .driver_info = METHOD2 पूर्ण,
	अणुUSB_DEVICE(0x06d6, 0x003b), .driver_info = METHOD0 पूर्ण,
	अणुUSB_DEVICE(0x0a17, 0x004e), .driver_info = METHOD2 पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x405d), .driver_info = METHOD2 पूर्ण,
	अणुUSB_DEVICE(0x08ca, 0x2102), .driver_info = METHOD3 पूर्ण,
	अणुUSB_DEVICE(0x06d6, 0x003d), .driver_info = METHOD0 पूर्ण,
	अणुपूर्ण			/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, device_table);

/* frame काष्ठाure */
काष्ठा zr364xx_framei अणु
	अचिन्हित दीर्घ ulState;	/* ulState:ZR364XX_READ_IDLE,
					   ZR364XX_READ_FRAME */
	व्योम *lpvbits;		/* image data */
	अचिन्हित दीर्घ cur_size;	/* current data copied to it */
पूर्ण;

/* image buffer काष्ठाure */
काष्ठा zr364xx_bufferi अणु
	अचिन्हित दीर्घ dwFrames;			/* number of frames in buffer */
	काष्ठा zr364xx_framei frame[FRAMES];	/* array of FRAME काष्ठाures */
पूर्ण;

काष्ठा zr364xx_dmaqueue अणु
	काष्ठा list_head	active;
	काष्ठा zr364xx_camera	*cam;
पूर्ण;

काष्ठा zr364xx_pipeinfo अणु
	u32 transfer_size;
	u8 *transfer_buffer;
	u32 state;
	व्योम *stream_urb;
	व्योम *cam;	/* back poपूर्णांकer to zr364xx_camera काष्ठा */
	u32 err_count;
	u32 idx;
पूर्ण;

काष्ठा zr364xx_fmt अणु
	u32 fourcc;
	पूर्णांक depth;
पूर्ण;

/* image क्रमmats.  */
अटल स्थिर काष्ठा zr364xx_fmt क्रमmats[] = अणु
	अणु
		.fourcc = V4L2_PIX_FMT_JPEG,
		.depth = 24
	पूर्ण
पूर्ण;

/* Camera stuff */
काष्ठा zr364xx_camera अणु
	काष्ठा usb_device *udev;	/* save off the usb device poपूर्णांकer */
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;/* the पूर्णांकerface क्रम this device */
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा video_device vdev;	/* v4l video device */
	काष्ठा v4l2_fh *owner;		/* owns the streaming */
	पूर्णांक nb;
	काष्ठा zr364xx_bufferi		buffer;
	पूर्णांक skip;
	पूर्णांक width;
	पूर्णांक height;
	पूर्णांक method;
	काष्ठा mutex lock;

	spinlock_t		slock;
	काष्ठा zr364xx_dmaqueue	vidq;
	पूर्णांक			last_frame;
	पूर्णांक			cur_frame;
	अचिन्हित दीर्घ		frame_count;
	पूर्णांक			b_acquire;
	काष्ठा zr364xx_pipeinfo	pipe[1];

	u8			पढ़ो_endpoपूर्णांक;

	स्थिर काष्ठा zr364xx_fmt *fmt;
	काष्ठा videobuf_queue	vb_vidq;
	bool was_streaming;
पूर्ण;

/* buffer क्रम one video frame */
काष्ठा zr364xx_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा videobuf_buffer vb;
	स्थिर काष्ठा zr364xx_fmt *fmt;
पूर्ण;

/* function used to send initialisation commands to the camera */
अटल पूर्णांक send_control_msg(काष्ठा usb_device *udev, u8 request, u16 value,
			    u16 index, अचिन्हित अक्षर *cp, u16 size)
अणु
	पूर्णांक status;

	अचिन्हित अक्षर *transfer_buffer = kmemdup(cp, size, GFP_KERNEL);
	अगर (!transfer_buffer)
		वापस -ENOMEM;

	status = usb_control_msg(udev,
				 usb_sndctrlpipe(udev, 0),
				 request,
				 USB_सूची_OUT | USB_TYPE_VENDOR |
				 USB_RECIP_DEVICE, value, index,
				 transfer_buffer, size, CTRL_TIMEOUT);

	kमुक्त(transfer_buffer);
	वापस status;
पूर्ण


/* Control messages sent to the camera to initialize it
 * and launch the capture */
प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक value;
	अचिन्हित पूर्णांक size;
	अचिन्हित अक्षर *bytes;
पूर्ण message;

/* method 0 */
अटल अचिन्हित अक्षर m0d1[] = अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
अटल अचिन्हित अक्षर m0d2[] = अणु 0, 0, 0, 0, 0, 0 पूर्ण;
अटल अचिन्हित अक्षर m0d3[] = अणु 0, 0 पूर्ण;
अटल message m0[] = अणु
	अणु0x1f30, 0, शून्यपूर्ण,
	अणु0xd000, 0, शून्यपूर्ण,
	अणु0x3370, माप(m0d1), m0d1पूर्ण,
	अणु0x2000, 0, शून्यपूर्ण,
	अणु0x2f0f, 0, शून्यपूर्ण,
	अणु0x2610, माप(m0d2), m0d2पूर्ण,
	अणु0xe107, 0, शून्यपूर्ण,
	अणु0x2502, 0, शून्यपूर्ण,
	अणु0x1f70, 0, शून्यपूर्ण,
	अणु0xd000, 0, शून्यपूर्ण,
	अणु0x9a01, माप(m0d3), m0d3पूर्ण,
	अणु-1, -1, शून्यपूर्ण
पूर्ण;

/* method 1 */
अटल अचिन्हित अक्षर m1d1[] = अणु 0xff, 0xff पूर्ण;
अटल अचिन्हित अक्षर m1d2[] = अणु 0x00, 0x00 पूर्ण;
अटल message m1[] = अणु
	अणु0x1f30, 0, शून्यपूर्ण,
	अणु0xd000, 0, शून्यपूर्ण,
	अणु0xf000, 0, शून्यपूर्ण,
	अणु0x2000, 0, शून्यपूर्ण,
	अणु0x2f0f, 0, शून्यपूर्ण,
	अणु0x2650, 0, शून्यपूर्ण,
	अणु0xe107, 0, शून्यपूर्ण,
	अणु0x2502, माप(m1d1), m1d1पूर्ण,
	अणु0x1f70, 0, शून्यपूर्ण,
	अणु0xd000, 0, शून्यपूर्ण,
	अणु0xd000, 0, शून्यपूर्ण,
	अणु0xd000, 0, शून्यपूर्ण,
	अणु0x9a01, माप(m1d2), m1d2पूर्ण,
	अणु-1, -1, शून्यपूर्ण
पूर्ण;

/* method 2 */
अटल अचिन्हित अक्षर m2d1[] = अणु 0xff, 0xff पूर्ण;
अटल message m2[] = अणु
	अणु0x1f30, 0, शून्यपूर्ण,
	अणु0xf000, 0, शून्यपूर्ण,
	अणु0x2000, 0, शून्यपूर्ण,
	अणु0x2f0f, 0, शून्यपूर्ण,
	अणु0x2650, 0, शून्यपूर्ण,
	अणु0xe107, 0, शून्यपूर्ण,
	अणु0x2502, माप(m2d1), m2d1पूर्ण,
	अणु0x1f70, 0, शून्यपूर्ण,
	अणु-1, -1, शून्यपूर्ण
पूर्ण;

/* init table */
अटल message *init[4] = अणु m0, m1, m2, m2 पूर्ण;


/* JPEG अटल data in header (Huffman table, etc) */
अटल अचिन्हित अक्षर header1[] = अणु
	0xFF, 0xD8,
	/*
	0xFF, 0xE0, 0x00, 0x10, 'J', 'F', 'I', 'F',
	0x00, 0x01, 0x01, 0x00, 0x33, 0x8A, 0x00, 0x00, 0x33, 0x88,
	*/
	0xFF, 0xDB, 0x00, 0x84
पूर्ण;
अटल अचिन्हित अक्षर header2[] = अणु
	0xFF, 0xC4, 0x00, 0x1F, 0x00, 0x00, 0x01, 0x05, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
	0xFF, 0xC4, 0x00, 0xB5, 0x10, 0x00, 0x02, 0x01, 0x03, 0x03, 0x02,
	0x04, 0x03, 0x05, 0x05, 0x04, 0x04, 0x00, 0x00, 0x01, 0x7D, 0x01,
	0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12, 0x21, 0x31, 0x41, 0x06,
	0x13, 0x51, 0x61, 0x07, 0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xA1,
	0x08, 0x23, 0x42, 0xB1, 0xC1, 0x15, 0x52, 0xD1, 0xF0, 0x24, 0x33,
	0x62, 0x72, 0x82, 0x09, 0x0A, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x25,
	0x26, 0x27, 0x28, 0x29, 0x2A, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
	0x3A, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x53, 0x54,
	0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67,
	0x68, 0x69, 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A,
	0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x92, 0x93, 0x94,
	0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6,
	0xA7, 0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8,
	0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA,
	0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xE1, 0xE2,
	0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF1, 0xF2, 0xF3,
	0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFF, 0xC4, 0x00, 0x1F,
	0x01, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04,
	0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xFF, 0xC4, 0x00, 0xB5,
	0x11, 0x00, 0x02, 0x01, 0x02, 0x04, 0x04, 0x03, 0x04, 0x07, 0x05,
	0x04, 0x04, 0x00, 0x01, 0x02, 0x77, 0x00, 0x01, 0x02, 0x03, 0x11,
	0x04, 0x05, 0x21, 0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
	0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91, 0xA1, 0xB1, 0xC1,
	0x09, 0x23, 0x33, 0x52, 0xF0, 0x15, 0x62, 0x72, 0xD1, 0x0A, 0x16,
	0x24, 0x34, 0xE1, 0x25, 0xF1, 0x17, 0x18, 0x19, 0x1A, 0x26, 0x27,
	0x28, 0x29, 0x2A, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44,
	0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x53, 0x54, 0x55, 0x56, 0x57,
	0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A,
	0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x82, 0x83, 0x84,
	0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x92, 0x93, 0x94, 0x95, 0x96,
	0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8,
	0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA,
	0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3,
	0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xE2, 0xE3, 0xE4, 0xE5,
	0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,
	0xF8, 0xF9, 0xFA, 0xFF, 0xC0, 0x00, 0x11, 0x08, 0x00, 0xF0, 0x01,
	0x40, 0x03, 0x01, 0x21, 0x00, 0x02, 0x11, 0x01, 0x03, 0x11, 0x01,
	0xFF, 0xDA, 0x00, 0x0C, 0x03, 0x01, 0x00, 0x02, 0x11, 0x03, 0x11,
	0x00, 0x3F, 0x00
पूर्ण;
अटल अचिन्हित अक्षर header3;

/* ------------------------------------------------------------------
   Videobuf operations
   ------------------------------------------------------------------*/

अटल पूर्णांक buffer_setup(काष्ठा videobuf_queue *vq, अचिन्हित पूर्णांक *count,
			अचिन्हित पूर्णांक *size)
अणु
	काष्ठा zr364xx_camera *cam = vq->priv_data;

	*size = cam->width * cam->height * (cam->fmt->depth >> 3);

	अगर (*count == 0)
		*count = ZR364XX_DEF_BUFS;

	अगर (*size * *count > ZR364XX_DEF_BUFS * 1024 * 1024)
		*count = (ZR364XX_DEF_BUFS * 1024 * 1024) / *size;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_buffer(काष्ठा videobuf_queue *vq, काष्ठा zr364xx_buffer *buf)
अणु
	_DBG("%s\n", __func__);

	videobuf_vदो_स्मृति_मुक्त(&buf->vb);
	buf->vb.state = VIDEOBUF_NEEDS_INIT;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा videobuf_queue *vq, काष्ठा videobuf_buffer *vb,
			  क्रमागत v4l2_field field)
अणु
	काष्ठा zr364xx_camera *cam = vq->priv_data;
	काष्ठा zr364xx_buffer *buf = container_of(vb, काष्ठा zr364xx_buffer,
						  vb);
	पूर्णांक rc;

	DBG("%s, field=%d\n", __func__, field);
	अगर (!cam->fmt)
		वापस -EINVAL;

	buf->vb.size = cam->width * cam->height * (cam->fmt->depth >> 3);

	अगर (buf->vb.baddr != 0 && buf->vb.bsize < buf->vb.size) अणु
		DBG("invalid buffer prepare\n");
		वापस -EINVAL;
	पूर्ण

	buf->fmt = cam->fmt;
	buf->vb.width = cam->width;
	buf->vb.height = cam->height;
	buf->vb.field = field;

	अगर (buf->vb.state == VIDEOBUF_NEEDS_INIT) अणु
		rc = videobuf_iolock(vq, &buf->vb, शून्य);
		अगर (rc < 0)
			जाओ fail;
	पूर्ण

	buf->vb.state = VIDEOBUF_PREPARED;
	वापस 0;
fail:
	मुक्त_buffer(vq, buf);
	वापस rc;
पूर्ण

अटल व्योम buffer_queue(काष्ठा videobuf_queue *vq, काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा zr364xx_buffer *buf = container_of(vb, काष्ठा zr364xx_buffer,
						  vb);
	काष्ठा zr364xx_camera *cam = vq->priv_data;

	_DBG("%s\n", __func__);

	buf->vb.state = VIDEOBUF_QUEUED;
	list_add_tail(&buf->vb.queue, &cam->vidq.active);
पूर्ण

अटल व्योम buffer_release(काष्ठा videobuf_queue *vq,
			   काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा zr364xx_buffer *buf = container_of(vb, काष्ठा zr364xx_buffer,
						  vb);

	_DBG("%s\n", __func__);
	मुक्त_buffer(vq, buf);
पूर्ण

अटल स्थिर काष्ठा videobuf_queue_ops zr364xx_video_qops = अणु
	.buf_setup = buffer_setup,
	.buf_prepare = buffer_prepare,
	.buf_queue = buffer_queue,
	.buf_release = buffer_release,
पूर्ण;

/********************/
/* V4L2 पूर्णांकegration */
/********************/
अटल पूर्णांक zr364xx_vidioc_streamon(काष्ठा file *file, व्योम *priv,
				   क्रमागत v4l2_buf_type type);

अटल sमाप_प्रकार zr364xx_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			    loff_t * ppos)
अणु
	काष्ठा zr364xx_camera *cam = video_drvdata(file);
	पूर्णांक err = 0;

	_DBG("%s\n", __func__);

	अगर (!buf)
		वापस -EINVAL;

	अगर (!count)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&cam->lock))
		वापस -ERESTARTSYS;

	err = zr364xx_vidioc_streamon(file, file->निजी_data,
				V4L2_BUF_TYPE_VIDEO_CAPTURE);
	अगर (err == 0) अणु
		DBG("%s: reading %d bytes at pos %d.\n", __func__,
				(पूर्णांक) count, (पूर्णांक) *ppos);

		/* NoMan Sux ! */
		err = videobuf_पढ़ो_one(&cam->vb_vidq, buf, count, ppos,
					file->f_flags & O_NONBLOCK);
	पूर्ण
	mutex_unlock(&cam->lock);
	वापस err;
पूर्ण

/* video buffer vदो_स्मृति implementation based partly on VIVI driver which is
 *          Copyright (c) 2006 by
 *                  Mauro Carvalho Chehab <mchehab--a.t--infradead.org>
 *                  Ted Walther <ted--a.t--क्रमागतera.com>
 *                  John Sokol <sokol--a.t--videotechnology.com>
 *                  http://v4l.videotechnology.com/
 *
 */
अटल व्योम zr364xx_fillbuff(काष्ठा zr364xx_camera *cam,
			     काष्ठा zr364xx_buffer *buf,
			     पूर्णांक jpgsize)
अणु
	पूर्णांक pos = 0;
	स्थिर अक्षर *पंचांगpbuf;
	अक्षर *vbuf = videobuf_to_vदो_स्मृति(&buf->vb);
	अचिन्हित दीर्घ last_frame;

	अगर (!vbuf)
		वापस;

	last_frame = cam->last_frame;
	अगर (last_frame != -1) अणु
		पंचांगpbuf = (स्थिर अक्षर *)cam->buffer.frame[last_frame].lpvbits;
		चयन (buf->fmt->fourcc) अणु
		हाल V4L2_PIX_FMT_JPEG:
			buf->vb.size = jpgsize;
			स_नकल(vbuf, पंचांगpbuf, buf->vb.size);
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_DEBUG KBUILD_MODNAME ": unknown format?\n");
		पूर्ण
		cam->last_frame = -1;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR KBUILD_MODNAME ": =======no frame\n");
		वापस;
	पूर्ण
	DBG("%s: Buffer %p size= %d\n", __func__, vbuf, pos);
	/* tell v4l buffer was filled */

	buf->vb.field_count = cam->frame_count * 2;
	buf->vb.ts = kसमय_get_ns();
	buf->vb.state = VIDEOBUF_DONE;
पूर्ण

अटल पूर्णांक zr364xx_got_frame(काष्ठा zr364xx_camera *cam, पूर्णांक jpgsize)
अणु
	काष्ठा zr364xx_dmaqueue *dma_q = &cam->vidq;
	काष्ठा zr364xx_buffer *buf;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक rc = 0;

	DBG("wakeup: %p\n", &dma_q);
	spin_lock_irqsave(&cam->slock, flags);

	अगर (list_empty(&dma_q->active)) अणु
		DBG("No active queue to serve\n");
		rc = -1;
		जाओ unlock;
	पूर्ण
	buf = list_entry(dma_q->active.next,
			 काष्ठा zr364xx_buffer, vb.queue);

	अगर (!रुकोqueue_active(&buf->vb.करोne)) अणु
		/* no one active */
		rc = -1;
		जाओ unlock;
	पूर्ण
	list_del(&buf->vb.queue);
	buf->vb.ts = kसमय_get_ns();
	DBG("[%p/%d] wakeup\n", buf, buf->vb.i);
	zr364xx_fillbuff(cam, buf, jpgsize);
	wake_up(&buf->vb.करोne);
	DBG("wakeup [buf/i] [%p/%d]\n", buf, buf->vb.i);
unlock:
	spin_unlock_irqrestore(&cam->slock, flags);
	वापस rc;
पूर्ण

/* this function moves the usb stream पढ़ो pipe data
 * पूर्णांकo the प्रणाली buffers.
 * वापसs 0 on success, EAGAIN अगर more data to process (call this
 * function again).
 */
अटल पूर्णांक zr364xx_पढ़ो_video_callback(काष्ठा zr364xx_camera *cam,
					काष्ठा zr364xx_pipeinfo *pipe_info,
					काष्ठा urb *purb)
अणु
	अचिन्हित अक्षर *pdest;
	अचिन्हित अक्षर *psrc;
	s32 idx = cam->cur_frame;
	काष्ठा zr364xx_framei *frm = &cam->buffer.frame[idx];
	पूर्णांक i = 0;
	अचिन्हित अक्षर *ptr = शून्य;

	_DBG("buffer to user\n");

	/* swap bytes अगर camera needs it */
	अगर (cam->method == METHOD0) अणु
		u16 *buf = (u16 *)pipe_info->transfer_buffer;
		क्रम (i = 0; i < purb->actual_length/2; i++)
			swab16s(buf + i);
	पूर्ण

	/* search करोne.  now find out अगर should be acquiring */
	अगर (!cam->b_acquire) अणु
		/* we found a frame, but this channel is turned off */
		frm->ulState = ZR364XX_READ_IDLE;
		वापस -EINVAL;
	पूर्ण

	psrc = (u8 *)pipe_info->transfer_buffer;
	ptr = pdest = frm->lpvbits;

	अगर (frm->ulState == ZR364XX_READ_IDLE) अणु
		अगर (purb->actual_length < 128) अणु
			/* header incomplete */
			dev_info(&cam->udev->dev,
				 "%s: buffer (%d bytes) too small to hold jpeg header. Discarding.\n",
				 __func__, purb->actual_length);
			वापस -EINVAL;
		पूर्ण

		frm->ulState = ZR364XX_READ_FRAME;
		frm->cur_size = 0;

		_DBG("jpeg header, ");
		स_नकल(ptr, header1, माप(header1));
		ptr += माप(header1);
		header3 = 0;
		स_नकल(ptr, &header3, 1);
		ptr++;
		स_नकल(ptr, psrc, 64);
		ptr += 64;
		header3 = 1;
		स_नकल(ptr, &header3, 1);
		ptr++;
		स_नकल(ptr, psrc + 64, 64);
		ptr += 64;
		स_नकल(ptr, header2, माप(header2));
		ptr += माप(header2);
		स_नकल(ptr, psrc + 128,
		       purb->actual_length - 128);
		ptr += purb->actual_length - 128;
		_DBG("header : %d %d %d %d %d %d %d %d %d\n",
		    psrc[0], psrc[1], psrc[2],
		    psrc[3], psrc[4], psrc[5],
		    psrc[6], psrc[7], psrc[8]);
		frm->cur_size = ptr - pdest;
	पूर्ण अन्यथा अणु
		अगर (frm->cur_size + purb->actual_length > MAX_FRAME_SIZE) अणु
			dev_info(&cam->udev->dev,
				 "%s: buffer (%d bytes) too small to hold frame data. Discarding frame data.\n",
				 __func__, MAX_FRAME_SIZE);
		पूर्ण अन्यथा अणु
			pdest += frm->cur_size;
			स_नकल(pdest, psrc, purb->actual_length);
			frm->cur_size += purb->actual_length;
		पूर्ण
	पूर्ण
	/*_DBG("cur_size %lu urb size %d\n", frm->cur_size,
		purb->actual_length);*/

	अगर (purb->actual_length < pipe_info->transfer_size) अणु
		_DBG("****************Buffer[%d]full*************\n", idx);
		cam->last_frame = cam->cur_frame;
		cam->cur_frame++;
		/* end of प्रणाली frame ring buffer, start at zero */
		अगर (cam->cur_frame == cam->buffer.dwFrames)
			cam->cur_frame = 0;

		/* frame पढ़ोy */
		/* go back to find the JPEG EOI marker */
		ptr = pdest = frm->lpvbits;
		ptr += frm->cur_size - 2;
		जबतक (ptr > pdest) अणु
			अगर (*ptr == 0xFF && *(ptr + 1) == 0xD9
			    && *(ptr + 2) == 0xFF)
				अवरोध;
			ptr--;
		पूर्ण
		अगर (ptr == pdest)
			DBG("No EOI marker\n");

		/* Someबार there is junk data in the middle of the picture,
		 * we want to skip this bogus frames */
		जबतक (ptr > pdest) अणु
			अगर (*ptr == 0xFF && *(ptr + 1) == 0xFF
			    && *(ptr + 2) == 0xFF)
				अवरोध;
			ptr--;
		पूर्ण
		अगर (ptr != pdest) अणु
			DBG("Bogus frame ? %d\n", ++(cam->nb));
		पूर्ण अन्यथा अगर (cam->b_acquire) अणु
			/* we skip the 2 first frames which are usually buggy */
			अगर (cam->skip)
				cam->skip--;
			अन्यथा अणु
				_DBG("jpeg(%lu): %d %d %d %d %d %d %d %d\n",
				    frm->cur_size,
				    pdest[0], pdest[1], pdest[2], pdest[3],
				    pdest[4], pdest[5], pdest[6], pdest[7]);

				zr364xx_got_frame(cam, frm->cur_size);
			पूर्ण
		पूर्ण
		cam->frame_count++;
		frm->ulState = ZR364XX_READ_IDLE;
		frm->cur_size = 0;
	पूर्ण
	/* करोne successfully */
	वापस 0;
पूर्ण

अटल पूर्णांक zr364xx_vidioc_querycap(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा zr364xx_camera *cam = video_drvdata(file);

	strscpy(cap->driver, DRIVER_DESC, माप(cap->driver));
	अगर (cam->udev->product)
		strscpy(cap->card, cam->udev->product, माप(cap->card));
	strscpy(cap->bus_info, dev_name(&cam->udev->dev),
		माप(cap->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक zr364xx_vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
				     काष्ठा v4l2_input *i)
अणु
	अगर (i->index != 0)
		वापस -EINVAL;
	strscpy(i->name, DRIVER_DESC " Camera", माप(i->name));
	i->type = V4L2_INPUT_TYPE_CAMERA;
	वापस 0;
पूर्ण

अटल पूर्णांक zr364xx_vidioc_g_input(काष्ठा file *file, व्योम *priv,
				  अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक zr364xx_vidioc_s_input(काष्ठा file *file, व्योम *priv,
				  अचिन्हित पूर्णांक i)
अणु
	अगर (i != 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक zr364xx_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा zr364xx_camera *cam =
		container_of(ctrl->handler, काष्ठा zr364xx_camera, ctrl_handler);
	पूर्णांक temp;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		/* hardware brightness */
		send_control_msg(cam->udev, 1, 0x2001, 0, शून्य, 0);
		temp = (0x60 << 8) + 127 - ctrl->val;
		send_control_msg(cam->udev, 1, temp, 0, शून्य, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zr364xx_vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file,
				       व्योम *priv, काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index > 0)
		वापस -EINVAL;
	f->pixelक्रमmat = क्रमmats[0].fourcc;
	वापस 0;
पूर्ण

अटल अक्षर *decode_fourcc(__u32 pixelक्रमmat, अक्षर *buf)
अणु
	buf[0] = pixelक्रमmat & 0xff;
	buf[1] = (pixelक्रमmat >> 8) & 0xff;
	buf[2] = (pixelक्रमmat >> 16) & 0xff;
	buf[3] = (pixelक्रमmat >> 24) & 0xff;
	buf[4] = '\0';
	वापस buf;
पूर्ण

अटल पूर्णांक zr364xx_vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				      काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा zr364xx_camera *cam = video_drvdata(file);
	अक्षर pixelक्रमmat_name[5];

	अगर (!cam)
		वापस -ENODEV;

	अगर (f->fmt.pix.pixelक्रमmat != V4L2_PIX_FMT_JPEG) अणु
		DBG("%s: unsupported pixelformat V4L2_PIX_FMT_%s\n", __func__,
		    decode_fourcc(f->fmt.pix.pixelक्रमmat, pixelक्रमmat_name));
		वापस -EINVAL;
	पूर्ण

	अगर (!(f->fmt.pix.width == 160 && f->fmt.pix.height == 120) &&
	    !(f->fmt.pix.width == 640 && f->fmt.pix.height == 480)) अणु
		f->fmt.pix.width = 320;
		f->fmt.pix.height = 240;
	पूर्ण

	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.bytesperline = f->fmt.pix.width * 2;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_JPEG;
	DBG("%s: V4L2_PIX_FMT_%s (%d) ok!\n", __func__,
	    decode_fourcc(f->fmt.pix.pixelक्रमmat, pixelक्रमmat_name),
	    f->fmt.pix.field);
	वापस 0;
पूर्ण

अटल पूर्णांक zr364xx_vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा zr364xx_camera *cam;

	अगर (!file)
		वापस -ENODEV;
	cam = video_drvdata(file);

	f->fmt.pix.pixelक्रमmat = क्रमmats[0].fourcc;
	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.width = cam->width;
	f->fmt.pix.height = cam->height;
	f->fmt.pix.bytesperline = f->fmt.pix.width * 2;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_JPEG;
	वापस 0;
पूर्ण

अटल पूर्णांक zr364xx_vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा zr364xx_camera *cam = video_drvdata(file);
	काष्ठा videobuf_queue *q = &cam->vb_vidq;
	अक्षर pixelक्रमmat_name[5];
	पूर्णांक ret = zr364xx_vidioc_try_fmt_vid_cap(file, cam, f);
	पूर्णांक i;

	अगर (ret < 0)
		वापस ret;

	mutex_lock(&q->vb_lock);

	अगर (videobuf_queue_is_busy(&cam->vb_vidq)) अणु
		DBG("%s queue busy\n", __func__);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (cam->owner) अणु
		DBG("%s can't change format after started\n", __func__);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	cam->width = f->fmt.pix.width;
	cam->height = f->fmt.pix.height;
	DBG("%s: %dx%d mode selected\n", __func__,
		 cam->width, cam->height);
	f->fmt.pix.bytesperline = f->fmt.pix.width * 2;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_JPEG;
	cam->vb_vidq.field = f->fmt.pix.field;

	अगर (f->fmt.pix.width == 160 && f->fmt.pix.height == 120)
		mode = 1;
	अन्यथा अगर (f->fmt.pix.width == 640 && f->fmt.pix.height == 480)
		mode = 2;
	अन्यथा
		mode = 0;

	m0d1[0] = mode;
	m1[2].value = 0xf000 + mode;
	m2[1].value = 0xf000 + mode;

	/* special हाल क्रम METHOD3, the modes are dअगरferent */
	अगर (cam->method == METHOD3) अणु
		चयन (mode) अणु
		हाल 1:
			m2[1].value = 0xf000 + 4;
			अवरोध;
		हाल 2:
			m2[1].value = 0xf000 + 0;
			अवरोध;
		शेष:
			m2[1].value = 0xf000 + 1;
			अवरोध;
		पूर्ण
	पूर्ण

	header2[437] = cam->height / 256;
	header2[438] = cam->height % 256;
	header2[439] = cam->width / 256;
	header2[440] = cam->width % 256;

	क्रम (i = 0; init[cam->method][i].size != -1; i++) अणु
		ret =
		    send_control_msg(cam->udev, 1, init[cam->method][i].value,
				     0, init[cam->method][i].bytes,
				     init[cam->method][i].size);
		अगर (ret < 0) अणु
			dev_err(&cam->udev->dev,
			   "error during resolution change sequence: %d\n", i);
			जाओ out;
		पूर्ण
	पूर्ण

	/* Added some delay here, since खोलोing/closing the camera quickly,
	 * like Ekiga करोes during its startup, can crash the webcam
	 */
	mdelay(100);
	cam->skip = 2;
	ret = 0;

out:
	mutex_unlock(&q->vb_lock);

	DBG("%s: V4L2_PIX_FMT_%s (%d) ok!\n", __func__,
	    decode_fourcc(f->fmt.pix.pixelक्रमmat, pixelक्रमmat_name),
	    f->fmt.pix.field);
	वापस ret;
पूर्ण

अटल पूर्णांक zr364xx_vidioc_reqbufs(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_requestbuffers *p)
अणु
	काष्ठा zr364xx_camera *cam = video_drvdata(file);

	अगर (cam->owner && cam->owner != priv)
		वापस -EBUSY;
	वापस videobuf_reqbufs(&cam->vb_vidq, p);
पूर्ण

अटल पूर्णांक zr364xx_vidioc_querybuf(काष्ठा file *file,
				व्योम *priv,
				काष्ठा v4l2_buffer *p)
अणु
	पूर्णांक rc;
	काष्ठा zr364xx_camera *cam = video_drvdata(file);
	rc = videobuf_querybuf(&cam->vb_vidq, p);
	वापस rc;
पूर्ण

अटल पूर्णांक zr364xx_vidioc_qbuf(काष्ठा file *file,
				व्योम *priv,
				काष्ठा v4l2_buffer *p)
अणु
	पूर्णांक rc;
	काष्ठा zr364xx_camera *cam = video_drvdata(file);
	_DBG("%s\n", __func__);
	अगर (cam->owner && cam->owner != priv)
		वापस -EBUSY;
	rc = videobuf_qbuf(&cam->vb_vidq, p);
	वापस rc;
पूर्ण

अटल पूर्णांक zr364xx_vidioc_dqbuf(काष्ठा file *file,
				व्योम *priv,
				काष्ठा v4l2_buffer *p)
अणु
	पूर्णांक rc;
	काष्ठा zr364xx_camera *cam = video_drvdata(file);
	_DBG("%s\n", __func__);
	अगर (cam->owner && cam->owner != priv)
		वापस -EBUSY;
	rc = videobuf_dqbuf(&cam->vb_vidq, p, file->f_flags & O_NONBLOCK);
	वापस rc;
पूर्ण

अटल व्योम पढ़ो_pipe_completion(काष्ठा urb *purb)
अणु
	काष्ठा zr364xx_pipeinfo *pipe_info;
	काष्ठा zr364xx_camera *cam;
	पूर्णांक pipe;

	pipe_info = purb->context;
	_DBG("%s %p, status %d\n", __func__, purb, purb->status);
	अगर (!pipe_info) अणु
		prपूर्णांकk(KERN_ERR KBUILD_MODNAME ": no context!\n");
		वापस;
	पूर्ण

	cam = pipe_info->cam;
	अगर (!cam) अणु
		prपूर्णांकk(KERN_ERR KBUILD_MODNAME ": no context!\n");
		वापस;
	पूर्ण

	/* अगर shutting करोwn, करो not resubmit, निकास immediately */
	अगर (purb->status == -ESHUTDOWN) अणु
		DBG("%s, err shutdown\n", __func__);
		pipe_info->err_count++;
		वापस;
	पूर्ण

	अगर (pipe_info->state == 0) अणु
		DBG("exiting USB pipe\n");
		वापस;
	पूर्ण

	अगर (purb->actual_length > pipe_info->transfer_size) अणु
		dev_err(&cam->udev->dev, "wrong number of bytes\n");
		वापस;
	पूर्ण

	अगर (purb->status == 0)
		zr364xx_पढ़ो_video_callback(cam, pipe_info, purb);
	अन्यथा अणु
		pipe_info->err_count++;
		DBG("%s: failed URB %d\n", __func__, purb->status);
	पूर्ण

	pipe = usb_rcvbulkpipe(cam->udev, cam->पढ़ो_endpoपूर्णांक);

	/* reuse urb */
	usb_fill_bulk_urb(pipe_info->stream_urb, cam->udev,
			  pipe,
			  pipe_info->transfer_buffer,
			  pipe_info->transfer_size,
			  पढ़ो_pipe_completion, pipe_info);

	अगर (pipe_info->state != 0) अणु
		purb->status = usb_submit_urb(pipe_info->stream_urb,
					      GFP_ATOMIC);

		अगर (purb->status)
			dev_err(&cam->udev->dev,
				"error submitting urb (error=%i)\n",
				purb->status);
	पूर्ण अन्यथा
		DBG("read pipe complete state 0\n");
पूर्ण

अटल पूर्णांक zr364xx_start_पढ़ोpipe(काष्ठा zr364xx_camera *cam)
अणु
	पूर्णांक pipe;
	पूर्णांक retval;
	काष्ठा zr364xx_pipeinfo *pipe_info = cam->pipe;
	pipe = usb_rcvbulkpipe(cam->udev, cam->पढ़ो_endpoपूर्णांक);
	DBG("%s: start pipe IN x%x\n", __func__, cam->पढ़ो_endpoपूर्णांक);

	pipe_info->state = 1;
	pipe_info->err_count = 0;
	pipe_info->stream_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!pipe_info->stream_urb)
		वापस -ENOMEM;
	/* transfer buffer allocated in board_init */
	usb_fill_bulk_urb(pipe_info->stream_urb, cam->udev,
			  pipe,
			  pipe_info->transfer_buffer,
			  pipe_info->transfer_size,
			  पढ़ो_pipe_completion, pipe_info);

	DBG("submitting URB %p\n", pipe_info->stream_urb);
	retval = usb_submit_urb(pipe_info->stream_urb, GFP_KERNEL);
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR KBUILD_MODNAME ": start read pipe failed\n");
		वापस retval;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम zr364xx_stop_पढ़ोpipe(काष्ठा zr364xx_camera *cam)
अणु
	काष्ठा zr364xx_pipeinfo *pipe_info;

	अगर (!cam) अणु
		prपूर्णांकk(KERN_ERR KBUILD_MODNAME ": invalid device\n");
		वापस;
	पूर्ण
	DBG("stop read pipe\n");
	pipe_info = cam->pipe;
	अगर (pipe_info) अणु
		अगर (pipe_info->state != 0)
			pipe_info->state = 0;

		अगर (pipe_info->stream_urb) अणु
			/* cancel urb */
			usb_समाप्त_urb(pipe_info->stream_urb);
			usb_मुक्त_urb(pipe_info->stream_urb);
			pipe_info->stream_urb = शून्य;
		पूर्ण
	पूर्ण
	वापस;
पूर्ण

/* starts acquisition process */
अटल पूर्णांक zr364xx_start_acquire(काष्ठा zr364xx_camera *cam)
अणु
	पूर्णांक j;

	DBG("start acquire\n");

	cam->last_frame = -1;
	cam->cur_frame = 0;
	क्रम (j = 0; j < FRAMES; j++) अणु
		cam->buffer.frame[j].ulState = ZR364XX_READ_IDLE;
		cam->buffer.frame[j].cur_size = 0;
	पूर्ण
	cam->b_acquire = 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक zr364xx_stop_acquire(काष्ठा zr364xx_camera *cam)
अणु
	cam->b_acquire = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक zr364xx_prepare(काष्ठा zr364xx_camera *cam)
अणु
	पूर्णांक res;
	पूर्णांक i, j;

	क्रम (i = 0; init[cam->method][i].size != -1; i++) अणु
		res = send_control_msg(cam->udev, 1, init[cam->method][i].value,
				     0, init[cam->method][i].bytes,
				     init[cam->method][i].size);
		अगर (res < 0) अणु
			dev_err(&cam->udev->dev,
				"error during open sequence: %d\n", i);
			वापस res;
		पूर्ण
	पूर्ण

	cam->skip = 2;
	cam->last_frame = -1;
	cam->cur_frame = 0;
	cam->frame_count = 0;
	क्रम (j = 0; j < FRAMES; j++) अणु
		cam->buffer.frame[j].ulState = ZR364XX_READ_IDLE;
		cam->buffer.frame[j].cur_size = 0;
	पूर्ण
	v4l2_ctrl_handler_setup(&cam->ctrl_handler);
	वापस 0;
पूर्ण

अटल पूर्णांक zr364xx_vidioc_streamon(काष्ठा file *file, व्योम *priv,
				   क्रमागत v4l2_buf_type type)
अणु
	काष्ठा zr364xx_camera *cam = video_drvdata(file);
	पूर्णांक res;

	DBG("%s\n", __func__);

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	अगर (cam->owner && cam->owner != priv)
		वापस -EBUSY;

	res = zr364xx_prepare(cam);
	अगर (res)
		वापस res;
	res = videobuf_streamon(&cam->vb_vidq);
	अगर (res == 0) अणु
		zr364xx_start_acquire(cam);
		cam->owner = file->निजी_data;
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक zr364xx_vidioc_streamoff(काष्ठा file *file, व्योम *priv,
				    क्रमागत v4l2_buf_type type)
अणु
	काष्ठा zr364xx_camera *cam = video_drvdata(file);

	DBG("%s\n", __func__);
	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;
	अगर (cam->owner && cam->owner != priv)
		वापस -EBUSY;
	zr364xx_stop_acquire(cam);
	वापस videobuf_streamoff(&cam->vb_vidq);
पूर्ण


/* खोलो the camera */
अटल पूर्णांक zr364xx_खोलो(काष्ठा file *file)
अणु
	काष्ठा zr364xx_camera *cam = video_drvdata(file);
	पूर्णांक err;

	DBG("%s\n", __func__);

	अगर (mutex_lock_पूर्णांकerruptible(&cam->lock))
		वापस -ERESTARTSYS;

	err = v4l2_fh_खोलो(file);
	अगर (err)
		जाओ out;

	/* Added some delay here, since खोलोing/closing the camera quickly,
	 * like Ekiga करोes during its startup, can crash the webcam
	 */
	mdelay(100);
	err = 0;

out:
	mutex_unlock(&cam->lock);
	DBG("%s: %d\n", __func__, err);
	वापस err;
पूर्ण

अटल व्योम zr364xx_board_uninit(काष्ठा zr364xx_camera *cam)
अणु
	अचिन्हित दीर्घ i;

	zr364xx_stop_पढ़ोpipe(cam);

	/* release sys buffers */
	क्रम (i = 0; i < FRAMES; i++) अणु
		अगर (cam->buffer.frame[i].lpvbits) अणु
			DBG("vfree %p\n", cam->buffer.frame[i].lpvbits);
			vमुक्त(cam->buffer.frame[i].lpvbits);
		पूर्ण
		cam->buffer.frame[i].lpvbits = शून्य;
	पूर्ण

	/* release transfer buffer */
	kमुक्त(cam->pipe->transfer_buffer);
पूर्ण

अटल व्योम zr364xx_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा zr364xx_camera *cam =
		container_of(v4l2_dev, काष्ठा zr364xx_camera, v4l2_dev);

	videobuf_mmap_मुक्त(&cam->vb_vidq);
	v4l2_ctrl_handler_मुक्त(&cam->ctrl_handler);
	zr364xx_board_uninit(cam);
	v4l2_device_unरेजिस्टर(&cam->v4l2_dev);
	kमुक्त(cam);
पूर्ण

/* release the camera */
अटल पूर्णांक zr364xx_बंद(काष्ठा file *file)
अणु
	काष्ठा zr364xx_camera *cam;
	काष्ठा usb_device *udev;
	पूर्णांक i;

	DBG("%s\n", __func__);
	cam = video_drvdata(file);

	mutex_lock(&cam->lock);
	udev = cam->udev;

	अगर (file->निजी_data == cam->owner) अणु
		/* turn off stream */
		अगर (cam->b_acquire)
			zr364xx_stop_acquire(cam);
		videobuf_streamoff(&cam->vb_vidq);

		क्रम (i = 0; i < 2; i++) अणु
			send_control_msg(udev, 1, init[cam->method][i].value,
					0, init[cam->method][i].bytes,
					init[cam->method][i].size);
		पूर्ण
		cam->owner = शून्य;
	पूर्ण

	/* Added some delay here, since खोलोing/closing the camera quickly,
	 * like Ekiga करोes during its startup, can crash the webcam
	 */
	mdelay(100);
	mutex_unlock(&cam->lock);
	वापस v4l2_fh_release(file);
पूर्ण


अटल पूर्णांक zr364xx_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा zr364xx_camera *cam = video_drvdata(file);
	पूर्णांक ret;

	अगर (!cam) अणु
		DBG("%s: cam == NULL\n", __func__);
		वापस -ENODEV;
	पूर्ण
	DBG("mmap called, vma=%p\n", vma);

	ret = videobuf_mmap_mapper(&cam->vb_vidq, vma);

	DBG("vma start=0x%08lx, size=%ld, ret=%d\n",
		(अचिन्हित दीर्घ)vma->vm_start,
		(अचिन्हित दीर्घ)vma->vm_end - (अचिन्हित दीर्घ)vma->vm_start, ret);
	वापस ret;
पूर्ण

अटल __poll_t zr364xx_poll(काष्ठा file *file,
			       काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा zr364xx_camera *cam = video_drvdata(file);
	काष्ठा videobuf_queue *q = &cam->vb_vidq;
	__poll_t res = v4l2_ctrl_poll(file, रुको);

	_DBG("%s\n", __func__);

	वापस res | videobuf_poll_stream(file, q, रुको);
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops zr364xx_ctrl_ops = अणु
	.s_ctrl = zr364xx_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations zr364xx_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = zr364xx_खोलो,
	.release = zr364xx_बंद,
	.पढ़ो = zr364xx_पढ़ो,
	.mmap = zr364xx_mmap,
	.unlocked_ioctl = video_ioctl2,
	.poll = zr364xx_poll,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops zr364xx_ioctl_ops = अणु
	.vidioc_querycap	= zr364xx_vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = zr364xx_vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap	= zr364xx_vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	= zr364xx_vidioc_s_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	= zr364xx_vidioc_g_fmt_vid_cap,
	.vidioc_क्रमागत_input	= zr364xx_vidioc_क्रमागत_input,
	.vidioc_g_input		= zr364xx_vidioc_g_input,
	.vidioc_s_input		= zr364xx_vidioc_s_input,
	.vidioc_streamon	= zr364xx_vidioc_streamon,
	.vidioc_streamoff	= zr364xx_vidioc_streamoff,
	.vidioc_reqbufs         = zr364xx_vidioc_reqbufs,
	.vidioc_querybuf        = zr364xx_vidioc_querybuf,
	.vidioc_qbuf            = zr364xx_vidioc_qbuf,
	.vidioc_dqbuf           = zr364xx_vidioc_dqbuf,
	.vidioc_log_status      = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा video_device zr364xx_ढाँचा = अणु
	.name = DRIVER_DESC,
	.fops = &zr364xx_fops,
	.ioctl_ops = &zr364xx_ioctl_ops,
	.release = video_device_release_empty,
	.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
		       V4L2_CAP_STREAMING,
पूर्ण;



/*******************/
/* USB पूर्णांकegration */
/*******************/
अटल पूर्णांक zr364xx_board_init(काष्ठा zr364xx_camera *cam)
अणु
	काष्ठा zr364xx_pipeinfo *pipe = cam->pipe;
	अचिन्हित दीर्घ i;
	पूर्णांक err;

	DBG("board init: %p\n", cam);
	स_रखो(pipe, 0, माप(*pipe));
	pipe->cam = cam;
	pipe->transfer_size = BUFFER_SIZE;

	pipe->transfer_buffer = kzalloc(pipe->transfer_size,
					GFP_KERNEL);
	अगर (!pipe->transfer_buffer) अणु
		DBG("out of memory!\n");
		वापस -ENOMEM;
	पूर्ण

	cam->b_acquire = 0;
	cam->frame_count = 0;

	/*** start create प्रणाली buffers ***/
	क्रम (i = 0; i < FRAMES; i++) अणु
		/* always allocate maximum size क्रम प्रणाली buffers */
		cam->buffer.frame[i].lpvbits = vदो_स्मृति(MAX_FRAME_SIZE);

		DBG("valloc %p, idx %lu, pdata %p\n",
			&cam->buffer.frame[i], i,
			cam->buffer.frame[i].lpvbits);
		अगर (!cam->buffer.frame[i].lpvbits) अणु
			prपूर्णांकk(KERN_INFO KBUILD_MODNAME ": out of memory. Using less frames\n");
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == 0) अणु
		prपूर्णांकk(KERN_INFO KBUILD_MODNAME ": out of memory. Aborting\n");
		err = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण अन्यथा
		cam->buffer.dwFrames = i;

	/* make sure पूर्णांकernal states are set */
	क्रम (i = 0; i < FRAMES; i++) अणु
		cam->buffer.frame[i].ulState = ZR364XX_READ_IDLE;
		cam->buffer.frame[i].cur_size = 0;
	पूर्ण

	cam->cur_frame = 0;
	cam->last_frame = -1;
	/*** end create प्रणाली buffers ***/

	/* start पढ़ो pipe */
	err = zr364xx_start_पढ़ोpipe(cam);
	अगर (err)
		जाओ err_मुक्त_frames;

	DBG(": board initialized\n");
	वापस 0;

err_मुक्त_frames:
	क्रम (i = 0; i < FRAMES; i++)
		vमुक्त(cam->buffer.frame[i].lpvbits);
err_मुक्त:
	kमुक्त(cam->pipe->transfer_buffer);
	cam->pipe->transfer_buffer = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक zr364xx_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा zr364xx_camera *cam = शून्य;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा v4l2_ctrl_handler *hdl;
	पूर्णांक err;
	पूर्णांक i;

	DBG("probing...\n");

	dev_info(&पूर्णांकf->dev, DRIVER_DESC " compatible webcam plugged\n");
	dev_info(&पूर्णांकf->dev, "model %04x:%04x detected\n",
		 le16_to_cpu(udev->descriptor.idVenकरोr),
		 le16_to_cpu(udev->descriptor.idProduct));

	cam = kzalloc(माप(*cam), GFP_KERNEL);
	अगर (!cam)
		वापस -ENOMEM;

	err = v4l2_device_रेजिस्टर(&पूर्णांकf->dev, &cam->v4l2_dev);
	अगर (err < 0) अणु
		dev_err(&udev->dev, "couldn't register v4l2_device\n");
		जाओ मुक्त_cam;
	पूर्ण
	hdl = &cam->ctrl_handler;
	v4l2_ctrl_handler_init(hdl, 1);
	v4l2_ctrl_new_std(hdl, &zr364xx_ctrl_ops,
			  V4L2_CID_BRIGHTNESS, 0, 127, 1, 64);
	अगर (hdl->error) अणु
		err = hdl->error;
		dev_err(&udev->dev, "couldn't register control\n");
		जाओ मुक्त_hdlr_and_unreg_dev;
	पूर्ण
	/* save the init method used by this camera */
	cam->method = id->driver_info;
	mutex_init(&cam->lock);
	cam->vdev = zr364xx_ढाँचा;
	cam->vdev.lock = &cam->lock;
	cam->vdev.v4l2_dev = &cam->v4l2_dev;
	cam->vdev.ctrl_handler = &cam->ctrl_handler;
	video_set_drvdata(&cam->vdev, cam);

	cam->udev = udev;

	चयन (mode) अणु
	हाल 1:
		dev_info(&udev->dev, "160x120 mode selected\n");
		cam->width = 160;
		cam->height = 120;
		अवरोध;
	हाल 2:
		dev_info(&udev->dev, "640x480 mode selected\n");
		cam->width = 640;
		cam->height = 480;
		अवरोध;
	शेष:
		dev_info(&udev->dev, "320x240 mode selected\n");
		cam->width = 320;
		cam->height = 240;
		अवरोध;
	पूर्ण

	m0d1[0] = mode;
	m1[2].value = 0xf000 + mode;
	m2[1].value = 0xf000 + mode;

	/* special हाल क्रम METHOD3, the modes are dअगरferent */
	अगर (cam->method == METHOD3) अणु
		चयन (mode) अणु
		हाल 1:
			m2[1].value = 0xf000 + 4;
			अवरोध;
		हाल 2:
			m2[1].value = 0xf000 + 0;
			अवरोध;
		शेष:
			m2[1].value = 0xf000 + 1;
			अवरोध;
		पूर्ण
	पूर्ण

	header2[437] = cam->height / 256;
	header2[438] = cam->height % 256;
	header2[439] = cam->width / 256;
	header2[440] = cam->width % 256;

	cam->nb = 0;

	DBG("dev: %p, udev %p interface %p\n", cam, cam->udev, पूर्णांकf);

	/* set up the endpoपूर्णांक inक्रमmation  */
	अगरace_desc = पूर्णांकf->cur_altsetting;
	DBG("num endpoints %d\n", अगरace_desc->desc.bNumEndpoपूर्णांकs);
	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;
		अगर (!cam->पढ़ो_endpoपूर्णांक && usb_endpoपूर्णांक_is_bulk_in(endpoपूर्णांक)) अणु
			/* we found the bulk in endpoपूर्णांक */
			cam->पढ़ो_endpoपूर्णांक = endpoपूर्णांक->bEndpoपूर्णांकAddress;
		पूर्ण
	पूर्ण

	अगर (!cam->पढ़ो_endpoपूर्णांक) अणु
		err = -ENOMEM;
		dev_err(&पूर्णांकf->dev, "Could not find bulk-in endpoint\n");
		जाओ मुक्त_hdlr_and_unreg_dev;
	पूर्ण

	/* v4l */
	INIT_LIST_HEAD(&cam->vidq.active);
	cam->vidq.cam = cam;

	usb_set_पूर्णांकfdata(पूर्णांकf, cam);

	/* load zr364xx board specअगरic */
	err = zr364xx_board_init(cam);
	अगर (err)
		जाओ मुक्त_hdlr_and_unreg_dev;
	err = v4l2_ctrl_handler_setup(hdl);
	अगर (err)
		जाओ board_uninit;

	spin_lock_init(&cam->slock);

	cam->fmt = क्रमmats;

	videobuf_queue_vदो_स्मृति_init(&cam->vb_vidq, &zr364xx_video_qops,
				    शून्य, &cam->slock,
				    V4L2_BUF_TYPE_VIDEO_CAPTURE,
				    V4L2_FIELD_NONE,
				    माप(काष्ठा zr364xx_buffer), cam, &cam->lock);

	err = video_रेजिस्टर_device(&cam->vdev, VFL_TYPE_VIDEO, -1);
	अगर (err) अणु
		dev_err(&udev->dev, "video_register_device failed\n");
		जाओ board_uninit;
	पूर्ण
	cam->v4l2_dev.release = zr364xx_release;

	dev_info(&udev->dev, DRIVER_DESC " controlling device %s\n",
		 video_device_node_name(&cam->vdev));
	वापस 0;

board_uninit:
	zr364xx_board_uninit(cam);
मुक्त_hdlr_and_unreg_dev:
	v4l2_ctrl_handler_मुक्त(hdl);
	v4l2_device_unरेजिस्टर(&cam->v4l2_dev);
मुक्त_cam:
	kमुक्त(cam);
	वापस err;
पूर्ण


अटल व्योम zr364xx_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा zr364xx_camera *cam = usb_get_पूर्णांकfdata(पूर्णांकf);

	mutex_lock(&cam->lock);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	dev_info(&पूर्णांकf->dev, DRIVER_DESC " webcam unplugged\n");
	video_unरेजिस्टर_device(&cam->vdev);
	v4l2_device_disconnect(&cam->v4l2_dev);

	/* stops the पढ़ो pipe अगर it is running */
	अगर (cam->b_acquire)
		zr364xx_stop_acquire(cam);

	zr364xx_stop_पढ़ोpipe(cam);
	mutex_unlock(&cam->lock);
	v4l2_device_put(&cam->v4l2_dev);
पूर्ण


#अगर_घोषित CONFIG_PM
अटल पूर्णांक zr364xx_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा zr364xx_camera *cam = usb_get_पूर्णांकfdata(पूर्णांकf);

	cam->was_streaming = cam->b_acquire;
	अगर (!cam->was_streaming)
		वापस 0;
	zr364xx_stop_acquire(cam);
	zr364xx_stop_पढ़ोpipe(cam);
	वापस 0;
पूर्ण

अटल पूर्णांक zr364xx_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा zr364xx_camera *cam = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक res;

	अगर (!cam->was_streaming)
		वापस 0;

	res = zr364xx_start_पढ़ोpipe(cam);
	अगर (res)
		वापस res;

	res = zr364xx_prepare(cam);
	अगर (res)
		जाओ err_prepare;

	zr364xx_start_acquire(cam);
	वापस 0;

err_prepare:
	zr364xx_stop_पढ़ोpipe(cam);
	वापस res;
पूर्ण
#पूर्ण_अगर

/**********************/
/* Module पूर्णांकegration */
/**********************/

अटल काष्ठा usb_driver zr364xx_driver = अणु
	.name = "zr364xx",
	.probe = zr364xx_probe,
	.disconnect = zr364xx_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend = zr364xx_suspend,
	.resume = zr364xx_resume,
	.reset_resume = zr364xx_resume,
#पूर्ण_अगर
	.id_table = device_table
पूर्ण;

module_usb_driver(zr364xx_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);
