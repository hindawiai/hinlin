<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  s2255drv.c - a driver क्रम the Sensoray 2255 USB video capture device
 *
 *   Copyright (C) 2007-2014 by Sensoray Company Inc.
 *                              Dean Anderson
 *
 * Some video buffer code based on vivi driver:
 *
 * Sensoray 2255 device supports 4 simultaneous channels.
 * The channels are not "crossbar" inमाला_दो, they are physically
 * attached to separate video decoders.
 *
 * Because of USB2.0 bandwidth limitations. There is only a
 * certain amount of data which may be transferred at one समय.
 *
 * Example maximum bandwidth utilization:
 *
 * -full size, color mode YUYV or YUV422P: 2 channels at once
 * -full or half size Grey scale: all 4 channels at once
 * -half size, color mode YUYV or YUV422P: all 4 channels at once
 * -full size, color mode YUYV or YUV422P 1/2 frame rate: all 4 channels
 *  at once.
 */

#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/usb.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-event.h>

#घोषणा S2255_VERSION		"1.25.1"
#घोषणा FIRMWARE_खाता_NAME "f2255usb.bin"

/* शेष JPEG quality */
#घोषणा S2255_DEF_JPEG_QUAL     50
/* venकरोr request in */
#घोषणा S2255_VR_IN		0
/* venकरोr request out */
#घोषणा S2255_VR_OUT		1
/* firmware query */
#घोषणा S2255_VR_FW		0x30
/* USB endpoपूर्णांक number क्रम configuring the device */
#घोषणा S2255_CONFIG_EP         2
/* maximum समय क्रम DSP to start responding after last FW word loaded(ms) */
#घोषणा S2255_DSP_BOOTTIME      800
/* maximum समय to रुको क्रम firmware to load (ms) */
#घोषणा S2255_LOAD_TIMEOUT      (5000 + S2255_DSP_BOOTTIME)
#घोषणा S2255_MIN_BUFS          2
#घोषणा S2255_SETMODE_TIMEOUT   500
#घोषणा S2255_VIDSTATUS_TIMEOUT 350
#घोषणा S2255_MARKER_FRAME	cpu_to_le32(0x2255DA4AL)
#घोषणा S2255_MARKER_RESPONSE	cpu_to_le32(0x2255ACACL)
#घोषणा S2255_RESPONSE_SETMODE  cpu_to_le32(0x01)
#घोषणा S2255_RESPONSE_FW       cpu_to_le32(0x10)
#घोषणा S2255_RESPONSE_STATUS   cpu_to_le32(0x20)
#घोषणा S2255_USB_XFER_SIZE	(16 * 1024)
#घोषणा MAX_CHANNELS		4
#घोषणा SYS_FRAMES		4
/* maximum size is PAL full size plus room क्रम the marker header(s) */
#घोषणा SYS_FRAMES_MAXSIZE	(720*288*2*2 + 4096)
#घोषणा DEF_USB_BLOCK		S2255_USB_XFER_SIZE
#घोषणा LINE_SZ_4CIFS_NTSC	640
#घोषणा LINE_SZ_2CIFS_NTSC	640
#घोषणा LINE_SZ_1CIFS_NTSC	320
#घोषणा LINE_SZ_4CIFS_PAL	704
#घोषणा LINE_SZ_2CIFS_PAL	704
#घोषणा LINE_SZ_1CIFS_PAL	352
#घोषणा NUM_LINES_4CIFS_NTSC	240
#घोषणा NUM_LINES_2CIFS_NTSC	240
#घोषणा NUM_LINES_1CIFS_NTSC	240
#घोषणा NUM_LINES_4CIFS_PAL	288
#घोषणा NUM_LINES_2CIFS_PAL	288
#घोषणा NUM_LINES_1CIFS_PAL	288
#घोषणा LINE_SZ_DEF		640
#घोषणा NUM_LINES_DEF		240


/* predefined settings */
#घोषणा FORMAT_NTSC	1
#घोषणा FORMAT_PAL	2

#घोषणा SCALE_4CIFS	1	/* 640x480(NTSC) or 704x576(PAL) */
#घोषणा SCALE_2CIFS	2	/* 640x240(NTSC) or 704x288(PAL) */
#घोषणा SCALE_1CIFS	3	/* 320x240(NTSC) or 352x288(PAL) */
/* SCALE_4CIFSI is the 2 fields पूर्णांकerpolated पूर्णांकo one */
#घोषणा SCALE_4CIFSI	4	/* 640x480(NTSC) or 704x576(PAL) high quality */

#घोषणा COLOR_YUVPL	1	/* YUV planar */
#घोषणा COLOR_YUVPK	2	/* YUV packed */
#घोषणा COLOR_Y8	4	/* monochrome */
#घोषणा COLOR_JPG       5       /* JPEG */

#घोषणा MASK_COLOR       0x000000ff
#घोषणा MASK_JPG_QUALITY 0x0000ff00
#घोषणा MASK_INPUT_TYPE  0x000f0000
/* frame decimation. */
#घोषणा FDEC_1		1	/* capture every frame. शेष */
#घोषणा FDEC_2		2	/* capture every 2nd frame */
#घोषणा FDEC_3		3	/* capture every 3rd frame */
#घोषणा FDEC_5		5	/* capture every 5th frame */

/*-------------------------------------------------------
 * Default mode parameters.
 *-------------------------------------------------------*/
#घोषणा DEF_SCALE	SCALE_4CIFS
#घोषणा DEF_COLOR	COLOR_YUVPL
#घोषणा DEF_FDEC	FDEC_1
#घोषणा DEF_BRIGHT	0
#घोषणा DEF_CONTRAST	0x5c
#घोषणा DEF_SATURATION	0x80
#घोषणा DEF_HUE		0

/* usb config commands */
#घोषणा IN_DATA_TOKEN	cpu_to_le32(0x2255c0de)
#घोषणा CMD_2255	0xc2255000
#घोषणा CMD_SET_MODE	cpu_to_le32((CMD_2255 | 0x10))
#घोषणा CMD_START	cpu_to_le32((CMD_2255 | 0x20))
#घोषणा CMD_STOP	cpu_to_le32((CMD_2255 | 0x30))
#घोषणा CMD_STATUS	cpu_to_le32((CMD_2255 | 0x40))

काष्ठा s2255_mode अणु
	u32 क्रमmat;	/* input video क्रमmat (NTSC, PAL) */
	u32 scale;	/* output video scale */
	u32 color;	/* output video color क्रमmat */
	u32 fdec;	/* frame decimation */
	u32 bright;	/* brightness */
	u32 contrast;	/* contrast */
	u32 saturation;	/* saturation */
	u32 hue;	/* hue (NTSC only)*/
	u32 single;	/* capture 1 frame at a समय (!=0), continuously (==0)*/
	u32 usb_block;	/* block size. should be 4096 of DEF_USB_BLOCK */
	u32 restart;	/* अगर DSP requires restart */
पूर्ण;


#घोषणा S2255_READ_IDLE		0
#घोषणा S2255_READ_FRAME	1

/* frame काष्ठाure */
काष्ठा s2255_framei अणु
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ ulState;	/* ulState:S2255_READ_IDLE, S2255_READ_FRAME*/
	व्योम *lpvbits;		/* image data */
	अचिन्हित दीर्घ cur_size;	/* current data copied to it */
पूर्ण;

/* image buffer काष्ठाure */
काष्ठा s2255_bufferi अणु
	अचिन्हित दीर्घ dwFrames;			/* number of frames in buffer */
	काष्ठा s2255_framei frame[SYS_FRAMES];	/* array of FRAME काष्ठाures */
पूर्ण;

#घोषणा DEF_MODEI_NTSC_CONT	अणुFORMAT_NTSC, DEF_SCALE, DEF_COLOR,	\
			DEF_FDEC, DEF_BRIGHT, DEF_CONTRAST, DEF_SATURATION, \
			DEF_HUE, 0, DEF_USB_BLOCK, 0पूर्ण

/* क्रम firmware loading, fw_state */
#घोषणा S2255_FW_NOTLOADED	0
#घोषणा S2255_FW_LOADED_DSPWAIT	1
#घोषणा S2255_FW_SUCCESS	2
#घोषणा S2255_FW_FAILED		3
#घोषणा S2255_FW_DISCONNECTING  4
#घोषणा S2255_FW_MARKER		cpu_to_le32(0x22552f2f)
/* 2255 पढ़ो states */
#घोषणा S2255_READ_IDLE         0
#घोषणा S2255_READ_FRAME        1
काष्ठा s2255_fw अणु
	पूर्णांक		      fw_loaded;
	पूर्णांक		      fw_size;
	काष्ठा urb	      *fw_urb;
	atomic_t	      fw_state;
	व्योम		      *pfw_data;
	रुको_queue_head_t     रुको_fw;
	स्थिर काष्ठा firmware *fw;
पूर्ण;

काष्ठा s2255_pipeinfo अणु
	u32 max_transfer_size;
	u32 cur_transfer_size;
	u8 *transfer_buffer;
	u32 state;
	व्योम *stream_urb;
	व्योम *dev;	/* back poपूर्णांकer to s2255_dev काष्ठा*/
	u32 err_count;
	u32 idx;
पूर्ण;

काष्ठा s2255_fmt; /*क्रमward declaration */
काष्ठा s2255_dev;

/* 2255 video channel */
काष्ठा s2255_vc अणु
	काष्ठा s2255_dev        *dev;
	काष्ठा video_device	vdev;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा v4l2_ctrl	*jpegqual_ctrl;
	पूर्णांक			resources;
	काष्ठा list_head        buf_list;
	काष्ठा s2255_bufferi	buffer;
	काष्ठा s2255_mode	mode;
	v4l2_std_id		std;
	/* jpeg compression */
	अचिन्हित		jpegqual;
	/* capture parameters (क्रम high quality mode full size) */
	काष्ठा v4l2_captureparm cap_parm;
	पूर्णांक			cur_frame;
	पूर्णांक			last_frame;
	/* allocated image size */
	अचिन्हित दीर्घ		req_image_size;
	/* received packet size */
	अचिन्हित दीर्घ		pkt_size;
	पूर्णांक			bad_payload;
	अचिन्हित दीर्घ		frame_count;
	/* अगर JPEG image */
	पूर्णांक                     jpg_size;
	/* अगर channel configured to शेष state */
	पूर्णांक                     configured;
	रुको_queue_head_t       रुको_seपंचांगode;
	पूर्णांक                     seपंचांगode_पढ़ोy;
	/* video status items */
	पूर्णांक                     vidstatus;
	रुको_queue_head_t       रुको_vidstatus;
	पूर्णांक                     vidstatus_पढ़ोy;
	अचिन्हित पूर्णांक		width;
	अचिन्हित पूर्णांक		height;
	क्रमागत v4l2_field         field;
	स्थिर काष्ठा s2255_fmt	*fmt;
	पूर्णांक idx; /* channel number on device, 0-3 */
	काष्ठा vb2_queue vb_vidq;
	काष्ठा mutex vb_lock; /* streaming lock */
	spinlock_t qlock;
पूर्ण;


काष्ठा s2255_dev अणु
	काष्ठा s2255_vc         vc[MAX_CHANNELS];
	काष्ठा v4l2_device      v4l2_dev;
	atomic_t                num_channels;
	पूर्णांक			frames;
	काष्ठा mutex		lock;	/* channels[].vdev.lock */
	काष्ठा mutex		cmdlock; /* protects cmdbuf */
	काष्ठा usb_device	*udev;
	काष्ठा usb_पूर्णांकerface	*पूर्णांकerface;
	u8			पढ़ो_endpoपूर्णांक;
	काष्ठा समयr_list	समयr;
	काष्ठा s2255_fw	*fw_data;
	काष्ठा s2255_pipeinfo	pipe;
	u32			cc;	/* current channel */
	पूर्णांक			frame_पढ़ोy;
	पूर्णांक                     chn_पढ़ोy;
	/* dsp firmware version (f2255usb.bin) */
	पूर्णांक                     dsp_fw_ver;
	u16                     pid; /* product id */
#घोषणा S2255_CMDBUF_SIZE 512
	__le32                  *cmdbuf;
पूर्ण;

अटल अंतरभूत काष्ठा s2255_dev *to_s2255_dev(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा s2255_dev, v4l2_dev);
पूर्ण

काष्ठा s2255_fmt अणु
	u32 fourcc;
	पूर्णांक depth;
पूर्ण;

/* buffer क्रम one video frame */
काष्ठा s2255_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;


/* current cypress EEPROM firmware version */
#घोषणा S2255_CUR_USB_FWVER	((3 << 8) | 12)
/* current DSP FW version */
#घोषणा S2255_CUR_DSP_FWVER     10104
/* Need DSP version 5+ क्रम video status feature */
#घोषणा S2255_MIN_DSP_STATUS      5
#घोषणा S2255_MIN_DSP_COLORFILTER 8
#घोषणा S2255_NORMS		(V4L2_STD_ALL)

/* निजी V4L2 controls */

/*
 * The following अक्षरt displays how COLORFILTER should be set
 *  =========================================================
 *  =     fourcc              =     COLORFILTER             =
 *  =                         ===============================
 *  =                         =   0             =    1      =
 *  =========================================================
 *  =  V4L2_PIX_FMT_GREY(Y8)  = monochrome from = monochrome=
 *  =                         = s-video or      = composite =
 *  =                         = B/W camera      = input     =
 *  =========================================================
 *  =    other                = color, svideo   = color,    =
 *  =                         =                 = composite =
 *  =========================================================
 *
 * Notes:
 *   channels 0-3 on 2255 are composite
 *   channels 0-1 on 2257 are composite, 2-3 are s-video
 * If COLORFILTER is 0 with a composite color camera connected,
 * the output will appear monochrome but hatching
 * will occur.
 * COLORFILTER is dअगरferent from "color killer" and "color effects"
 * क्रम reasons above.
 */
#घोषणा S2255_V4L2_YC_ON  1
#घोषणा S2255_V4L2_YC_OFF 0
#घोषणा V4L2_CID_S2255_COLORFILTER (V4L2_CID_USER_S2255_BASE + 0)

/* frame prefix size (sent once every frame) */
#घोषणा PREFIX_SIZE		512

/* Channels on box are in reverse order */
अटल अचिन्हित दीर्घ G_chnmap[MAX_CHANNELS] = अणु3, 2, 1, 0पूर्ण;

अटल पूर्णांक debug;

अटल पूर्णांक s2255_start_पढ़ोpipe(काष्ठा s2255_dev *dev);
अटल व्योम s2255_stop_पढ़ोpipe(काष्ठा s2255_dev *dev);
अटल पूर्णांक s2255_start_acquire(काष्ठा s2255_vc *vc);
अटल पूर्णांक s2255_stop_acquire(काष्ठा s2255_vc *vc);
अटल व्योम s2255_fillbuff(काष्ठा s2255_vc *vc, काष्ठा s2255_buffer *buf,
			   पूर्णांक jpgsize);
अटल पूर्णांक s2255_set_mode(काष्ठा s2255_vc *vc, काष्ठा s2255_mode *mode);
अटल पूर्णांक s2255_board_shutकरोwn(काष्ठा s2255_dev *dev);
अटल व्योम s2255_fwload_start(काष्ठा s2255_dev *dev);
अटल व्योम s2255_destroy(काष्ठा s2255_dev *dev);
अटल दीर्घ s2255_venकरोr_req(काष्ठा s2255_dev *dev, अचिन्हित अक्षर req,
			     u16 index, u16 value, व्योम *buf,
			     s32 buf_len, पूर्णांक bOut);

/* dev_err macro with driver name */
#घोषणा S2255_DRIVER_NAME "s2255"
#घोषणा s2255_dev_err(dev, fmt, arg...)					\
		dev_err(dev, S2255_DRIVER_NAME " - " fmt, ##arg)

#घोषणा dprपूर्णांकk(dev, level, fmt, arg...) \
	v4l2_dbg(level, debug, &dev->v4l2_dev, fmt, ## arg)

अटल काष्ठा usb_driver s2255_driver;

/* start video number */
अटल पूर्णांक video_nr = -1;	/* /dev/videoN, -1 क्रम स्वतःdetect */

/* Enable jpeg capture. */
अटल पूर्णांक jpeg_enable = 1;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Debug level(0-100) default 0");
module_param(video_nr, पूर्णांक, 0644);
MODULE_PARM_DESC(video_nr, "start video minor(-1 default autodetect)");
module_param(jpeg_enable, पूर्णांक, 0644);
MODULE_PARM_DESC(jpeg_enable, "Jpeg enable(1-on 0-off) default 1");

/* USB device table */
#घोषणा USB_SENSORAY_VID	0x1943
अटल स्थिर काष्ठा usb_device_id s2255_table[] = अणु
	अणुUSB_DEVICE(USB_SENSORAY_VID, 0x2255)पूर्ण,
	अणुUSB_DEVICE(USB_SENSORAY_VID, 0x2257)पूर्ण, /*same family as 2255*/
	अणु पूर्ण			/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, s2255_table);

#घोषणा BUFFER_TIMEOUT msecs_to_jअगरfies(400)

/* image क्रमmats.  */
/* JPEG क्रमmats must be defined last to support jpeg_enable parameter */
अटल स्थिर काष्ठा s2255_fmt क्रमmats[] = अणु
	अणु
		.fourcc = V4L2_PIX_FMT_YUYV,
		.depth = 16

	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_UYVY,
		.depth = 16
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_YUV422P,
		.depth = 16

	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_GREY,
		.depth = 8
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_JPEG,
		.depth = 24
	पूर्ण, अणु
		.fourcc = V4L2_PIX_FMT_MJPEG,
		.depth = 24
	पूर्ण
पूर्ण;

अटल पूर्णांक norm_maxw(काष्ठा s2255_vc *vc)
अणु
	वापस (vc->std & V4L2_STD_525_60) ?
	    LINE_SZ_4CIFS_NTSC : LINE_SZ_4CIFS_PAL;
पूर्ण

अटल पूर्णांक norm_maxh(काष्ठा s2255_vc *vc)
अणु
	वापस (vc->std & V4L2_STD_525_60) ?
	    (NUM_LINES_1CIFS_NTSC * 2) : (NUM_LINES_1CIFS_PAL * 2);
पूर्ण

अटल पूर्णांक norm_minw(काष्ठा s2255_vc *vc)
अणु
	वापस (vc->std & V4L2_STD_525_60) ?
	    LINE_SZ_1CIFS_NTSC : LINE_SZ_1CIFS_PAL;
पूर्ण

अटल पूर्णांक norm_minh(काष्ठा s2255_vc *vc)
अणु
	वापस (vc->std & V4L2_STD_525_60) ?
	    (NUM_LINES_1CIFS_NTSC) : (NUM_LINES_1CIFS_PAL);
पूर्ण


/*
 * TODO: fixme: move YUV reordering to hardware
 * converts 2255 planar क्रमmat to yuyv or uyvy
 */
अटल व्योम planar422p_to_yuv_packed(स्थिर अचिन्हित अक्षर *in,
				     अचिन्हित अक्षर *out,
				     पूर्णांक width, पूर्णांक height,
				     पूर्णांक fmt)
अणु
	अचिन्हित अक्षर *pY;
	अचिन्हित अक्षर *pCb;
	अचिन्हित अक्षर *pCr;
	अचिन्हित दीर्घ size = height * width;
	अचिन्हित पूर्णांक i;
	pY = (अचिन्हित अक्षर *)in;
	pCr = (अचिन्हित अक्षर *)in + height * width;
	pCb = (अचिन्हित अक्षर *)in + height * width + (height * width / 2);
	क्रम (i = 0; i < size * 2; i += 4) अणु
		out[i] = (fmt == V4L2_PIX_FMT_YUYV) ? *pY++ : *pCr++;
		out[i + 1] = (fmt == V4L2_PIX_FMT_YUYV) ? *pCr++ : *pY++;
		out[i + 2] = (fmt == V4L2_PIX_FMT_YUYV) ? *pY++ : *pCb++;
		out[i + 3] = (fmt == V4L2_PIX_FMT_YUYV) ? *pCb++ : *pY++;
	पूर्ण
	वापस;
पूर्ण

अटल व्योम s2255_reset_dspघातer(काष्ठा s2255_dev *dev)
अणु
	s2255_venकरोr_req(dev, 0x40, 0x0000, 0x0001, शून्य, 0, 1);
	msleep(50);
	s2255_venकरोr_req(dev, 0x50, 0x0000, 0x0000, शून्य, 0, 1);
	msleep(600);
	s2255_venकरोr_req(dev, 0x10, 0x0000, 0x0000, शून्य, 0, 1);
	वापस;
पूर्ण

/* kickstarts the firmware loading. from probe
 */
अटल व्योम s2255_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा s2255_dev *dev = from_समयr(dev, t, समयr);
	काष्ठा s2255_fw *data = dev->fw_data;
	अगर (usb_submit_urb(data->fw_urb, GFP_ATOMIC) < 0) अणु
		pr_err("s2255: can't submit urb\n");
		atomic_set(&data->fw_state, S2255_FW_FAILED);
		/* wake up anything रुकोing क्रम the firmware */
		wake_up(&data->रुको_fw);
		वापस;
	पूर्ण
पूर्ण


/* this loads the firmware asynchronously.
   Originally this was करोne synchronously in probe.
   But it is better to load it asynchronously here than block
   inside the probe function. Blocking inside probe affects boot समय.
   FW loading is triggered by the समयr in the probe function
*/
अटल व्योम s2255_fwchunk_complete(काष्ठा urb *urb)
अणु
	काष्ठा s2255_fw *data = urb->context;
	काष्ठा usb_device *udev = urb->dev;
	पूर्णांक len;
	अगर (urb->status) अणु
		dev_err(&udev->dev, "URB failed with status %d\n", urb->status);
		atomic_set(&data->fw_state, S2255_FW_FAILED);
		/* wake up anything रुकोing क्रम the firmware */
		wake_up(&data->रुको_fw);
		वापस;
	पूर्ण
	अगर (data->fw_urb == शून्य) अणु
		s2255_dev_err(&udev->dev, "disconnected\n");
		atomic_set(&data->fw_state, S2255_FW_FAILED);
		/* wake up anything रुकोing क्रम the firmware */
		wake_up(&data->रुको_fw);
		वापस;
	पूर्ण
#घोषणा CHUNK_SIZE 512
	/* all USB transfers must be करोne with continuous kernel memory.
	   can't allocate more than 128k in current linux kernel, so
	   upload the firmware in chunks
	 */
	अगर (data->fw_loaded < data->fw_size) अणु
		len = (data->fw_loaded + CHUNK_SIZE) > data->fw_size ?
		    data->fw_size % CHUNK_SIZE : CHUNK_SIZE;

		अगर (len < CHUNK_SIZE)
			स_रखो(data->pfw_data, 0, CHUNK_SIZE);

		स_नकल(data->pfw_data,
		       (अक्षर *) data->fw->data + data->fw_loaded, len);

		usb_fill_bulk_urb(data->fw_urb, udev, usb_sndbulkpipe(udev, 2),
				  data->pfw_data, CHUNK_SIZE,
				  s2255_fwchunk_complete, data);
		अगर (usb_submit_urb(data->fw_urb, GFP_ATOMIC) < 0) अणु
			dev_err(&udev->dev, "failed submit URB\n");
			atomic_set(&data->fw_state, S2255_FW_FAILED);
			/* wake up anything रुकोing क्रम the firmware */
			wake_up(&data->रुको_fw);
			वापस;
		पूर्ण
		data->fw_loaded += len;
	पूर्ण अन्यथा
		atomic_set(&data->fw_state, S2255_FW_LOADED_DSPWAIT);
	वापस;

पूर्ण

अटल व्योम s2255_got_frame(काष्ठा s2255_vc *vc, पूर्णांक jpgsize)
अणु
	काष्ठा s2255_buffer *buf;
	काष्ठा s2255_dev *dev = to_s2255_dev(vc->vdev.v4l2_dev);
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&vc->qlock, flags);
	अगर (list_empty(&vc->buf_list)) अणु
		dprपूर्णांकk(dev, 1, "No active queue to serve\n");
		spin_unlock_irqrestore(&vc->qlock, flags);
		वापस;
	पूर्ण
	buf = list_entry(vc->buf_list.next,
			 काष्ठा s2255_buffer, list);
	list_del(&buf->list);
	buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
	buf->vb.field = vc->field;
	buf->vb.sequence = vc->frame_count;
	spin_unlock_irqrestore(&vc->qlock, flags);

	s2255_fillbuff(vc, buf, jpgsize);
	/* tell v4l buffer was filled */
	vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
	dprपूर्णांकk(dev, 2, "%s: [buf] [%p]\n", __func__, buf);
पूर्ण

अटल स्थिर काष्ठा s2255_fmt *क्रमmat_by_fourcc(पूर्णांक fourcc)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); i++) अणु
		अगर (-1 == क्रमmats[i].fourcc)
			जारी;
		अगर (!jpeg_enable && ((क्रमmats[i].fourcc == V4L2_PIX_FMT_JPEG) ||
				     (क्रमmats[i].fourcc == V4L2_PIX_FMT_MJPEG)))
			जारी;
		अगर (क्रमmats[i].fourcc == fourcc)
			वापस क्रमmats + i;
	पूर्ण
	वापस शून्य;
पूर्ण

/* video buffer vदो_स्मृति implementation based partly on VIVI driver which is
 *          Copyright (c) 2006 by
 *                  Mauro Carvalho Chehab <mchehab--a.t--infradead.org>
 *                  Ted Walther <ted--a.t--क्रमागतera.com>
 *                  John Sokol <sokol--a.t--videotechnology.com>
 *                  http://v4l.videotechnology.com/
 *
 */
अटल व्योम s2255_fillbuff(काष्ठा s2255_vc *vc,
			   काष्ठा s2255_buffer *buf, पूर्णांक jpgsize)
अणु
	पूर्णांक pos = 0;
	स्थिर अक्षर *पंचांगpbuf;
	अक्षर *vbuf = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);
	अचिन्हित दीर्घ last_frame;
	काष्ठा s2255_dev *dev = vc->dev;

	अगर (!vbuf)
		वापस;
	last_frame = vc->last_frame;
	अगर (last_frame != -1) अणु
		पंचांगpbuf =
		    (स्थिर अक्षर *)vc->buffer.frame[last_frame].lpvbits;
		चयन (vc->fmt->fourcc) अणु
		हाल V4L2_PIX_FMT_YUYV:
		हाल V4L2_PIX_FMT_UYVY:
			planar422p_to_yuv_packed((स्थिर अचिन्हित अक्षर *)पंचांगpbuf,
						 vbuf, vc->width,
						 vc->height,
						 vc->fmt->fourcc);
			अवरोध;
		हाल V4L2_PIX_FMT_GREY:
			स_नकल(vbuf, पंचांगpbuf, vc->width * vc->height);
			अवरोध;
		हाल V4L2_PIX_FMT_JPEG:
		हाल V4L2_PIX_FMT_MJPEG:
			vb2_set_plane_payload(&buf->vb.vb2_buf, 0, jpgsize);
			स_नकल(vbuf, पंचांगpbuf, jpgsize);
			अवरोध;
		हाल V4L2_PIX_FMT_YUV422P:
			स_नकल(vbuf, पंचांगpbuf,
			       vc->width * vc->height * 2);
			अवरोध;
		शेष:
			pr_info("s2255: unknown format?\n");
		पूर्ण
		vc->last_frame = -1;
	पूर्ण अन्यथा अणु
		pr_err("s2255: =======no frame\n");
		वापस;
	पूर्ण
	dprपूर्णांकk(dev, 2, "s2255fill at : Buffer %p size= %d\n",
		vbuf, pos);
पूर्ण


/* ------------------------------------------------------------------
   Videobuf operations
   ------------------------------------------------------------------*/

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा s2255_vc *vc = vb2_get_drv_priv(vq);
	अगर (*nbuffers < S2255_MIN_BUFS)
		*nbuffers = S2255_MIN_BUFS;
	*nplanes = 1;
	sizes[0] = vc->width * vc->height * (vc->fmt->depth >> 3);
	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा s2255_vc *vc = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा s2255_buffer *buf = container_of(vbuf, काष्ठा s2255_buffer, vb);
	पूर्णांक w = vc->width;
	पूर्णांक h = vc->height;
	अचिन्हित दीर्घ size;

	dprपूर्णांकk(vc->dev, 4, "%s\n", __func__);
	अगर (vc->fmt == शून्य)
		वापस -EINVAL;

	अगर ((w < norm_minw(vc)) ||
	    (w > norm_maxw(vc)) ||
	    (h < norm_minh(vc)) ||
	    (h > norm_maxh(vc))) अणु
		dprपूर्णांकk(vc->dev, 4, "invalid buffer prepare\n");
		वापस -EINVAL;
	पूर्ण
	size = w * h * (vc->fmt->depth >> 3);
	अगर (vb2_plane_size(vb, 0) < size) अणु
		dprपूर्णांकk(vc->dev, 4, "invalid buffer prepare\n");
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(&buf->vb.vb2_buf, 0, size);
	वापस 0;
पूर्ण

अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा s2255_buffer *buf = container_of(vbuf, काष्ठा s2255_buffer, vb);
	काष्ठा s2255_vc *vc = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ flags = 0;
	dprपूर्णांकk(vc->dev, 1, "%s\n", __func__);
	spin_lock_irqsave(&vc->qlock, flags);
	list_add_tail(&buf->list, &vc->buf_list);
	spin_unlock_irqrestore(&vc->qlock, flags);
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count);
अटल व्योम stop_streaming(काष्ठा vb2_queue *vq);

अटल स्थिर काष्ठा vb2_ops s2255_video_qops = अणु
	.queue_setup = queue_setup,
	.buf_prepare = buffer_prepare,
	.buf_queue = buffer_queue,
	.start_streaming = start_streaming,
	.stop_streaming = stop_streaming,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा s2255_vc *vc = video_drvdata(file);
	काष्ठा s2255_dev *dev = vc->dev;

	strscpy(cap->driver, "s2255", माप(cap->driver));
	strscpy(cap->card, "s2255", माप(cap->card));
	usb_make_path(dev->udev, cap->bus_info, माप(cap->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			       काष्ठा v4l2_fmtdesc *f)
अणु
	पूर्णांक index = f->index;

	अगर (index >= ARRAY_SIZE(क्रमmats))
		वापस -EINVAL;
	अगर (!jpeg_enable && ((क्रमmats[index].fourcc == V4L2_PIX_FMT_JPEG) ||
			(क्रमmats[index].fourcc == V4L2_PIX_FMT_MJPEG)))
		वापस -EINVAL;
	f->pixelक्रमmat = क्रमmats[index].fourcc;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा s2255_vc *vc = video_drvdata(file);
	पूर्णांक is_ntsc = vc->std & V4L2_STD_525_60;

	f->fmt.pix.width = vc->width;
	f->fmt.pix.height = vc->height;
	अगर (f->fmt.pix.height >=
	    (is_ntsc ? NUM_LINES_1CIFS_NTSC : NUM_LINES_1CIFS_PAL) * 2)
		f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	अन्यथा
		f->fmt.pix.field = V4L2_FIELD_TOP;
	f->fmt.pix.pixelक्रमmat = vc->fmt->fourcc;
	f->fmt.pix.bytesperline = f->fmt.pix.width * (vc->fmt->depth >> 3);
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_क्रमmat *f)
अणु
	स्थिर काष्ठा s2255_fmt *fmt;
	क्रमागत v4l2_field field;
	काष्ठा s2255_vc *vc = video_drvdata(file);
	पूर्णांक is_ntsc = vc->std & V4L2_STD_525_60;

	fmt = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);

	अगर (fmt == शून्य)
		वापस -EINVAL;

	field = f->fmt.pix.field;

	dprपूर्णांकk(vc->dev, 50, "%s NTSC: %d suggested width: %d, height: %d\n",
		__func__, is_ntsc, f->fmt.pix.width, f->fmt.pix.height);
	अगर (is_ntsc) अणु
		/* NTSC */
		अगर (f->fmt.pix.height >= NUM_LINES_1CIFS_NTSC * 2) अणु
			f->fmt.pix.height = NUM_LINES_1CIFS_NTSC * 2;
			field = V4L2_FIELD_INTERLACED;
		पूर्ण अन्यथा अणु
			f->fmt.pix.height = NUM_LINES_1CIFS_NTSC;
			field = V4L2_FIELD_TOP;
		पूर्ण
		अगर (f->fmt.pix.width >= LINE_SZ_4CIFS_NTSC)
			f->fmt.pix.width = LINE_SZ_4CIFS_NTSC;
		अन्यथा
			f->fmt.pix.width = LINE_SZ_1CIFS_NTSC;
	पूर्ण अन्यथा अणु
		/* PAL */
		अगर (f->fmt.pix.height >= NUM_LINES_1CIFS_PAL * 2) अणु
			f->fmt.pix.height = NUM_LINES_1CIFS_PAL * 2;
			field = V4L2_FIELD_INTERLACED;
		पूर्ण अन्यथा अणु
			f->fmt.pix.height = NUM_LINES_1CIFS_PAL;
			field = V4L2_FIELD_TOP;
		पूर्ण
		अगर (f->fmt.pix.width >= LINE_SZ_4CIFS_PAL)
			f->fmt.pix.width = LINE_SZ_4CIFS_PAL;
		अन्यथा
			f->fmt.pix.width = LINE_SZ_1CIFS_PAL;
	पूर्ण
	f->fmt.pix.field = field;
	f->fmt.pix.bytesperline = (f->fmt.pix.width * fmt->depth) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	dprपूर्णांकk(vc->dev, 50, "%s: set width %d height %d field %d\n", __func__,
		f->fmt.pix.width, f->fmt.pix.height, f->fmt.pix.field);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा s2255_vc *vc = video_drvdata(file);
	स्थिर काष्ठा s2255_fmt *fmt;
	काष्ठा vb2_queue *q = &vc->vb_vidq;
	काष्ठा s2255_mode mode;
	पूर्णांक ret;

	ret = vidioc_try_fmt_vid_cap(file, vc, f);

	अगर (ret < 0)
		वापस ret;

	fmt = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);

	अगर (fmt == शून्य)
		वापस -EINVAL;

	अगर (vb2_is_busy(q)) अणु
		dprपूर्णांकk(vc->dev, 1, "queue busy\n");
		वापस -EBUSY;
	पूर्ण

	mode = vc->mode;
	vc->fmt = fmt;
	vc->width = f->fmt.pix.width;
	vc->height = f->fmt.pix.height;
	vc->field = f->fmt.pix.field;
	अगर (vc->width > norm_minw(vc)) अणु
		अगर (vc->height > norm_minh(vc)) अणु
			अगर (vc->cap_parm.capturemode &
			    V4L2_MODE_HIGHQUALITY)
				mode.scale = SCALE_4CIFSI;
			अन्यथा
				mode.scale = SCALE_4CIFS;
		पूर्ण अन्यथा
			mode.scale = SCALE_2CIFS;

	पूर्ण अन्यथा अणु
		mode.scale = SCALE_1CIFS;
	पूर्ण
	/* color mode */
	चयन (vc->fmt->fourcc) अणु
	हाल V4L2_PIX_FMT_GREY:
		mode.color &= ~MASK_COLOR;
		mode.color |= COLOR_Y8;
		अवरोध;
	हाल V4L2_PIX_FMT_JPEG:
	हाल V4L2_PIX_FMT_MJPEG:
		mode.color &= ~MASK_COLOR;
		mode.color |= COLOR_JPG;
		mode.color |= (vc->jpegqual << 8);
		अवरोध;
	हाल V4L2_PIX_FMT_YUV422P:
		mode.color &= ~MASK_COLOR;
		mode.color |= COLOR_YUVPL;
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_UYVY:
	शेष:
		mode.color &= ~MASK_COLOR;
		mode.color |= COLOR_YUVPK;
		अवरोध;
	पूर्ण
	अगर ((mode.color & MASK_COLOR) != (vc->mode.color & MASK_COLOR))
		mode.restart = 1;
	अन्यथा अगर (mode.scale != vc->mode.scale)
		mode.restart = 1;
	अन्यथा अगर (mode.क्रमmat != vc->mode.क्रमmat)
		mode.restart = 1;
	vc->mode = mode;
	(व्योम) s2255_set_mode(vc, &mode);
	वापस 0;
पूर्ण


/* ग_लिखो to the configuration pipe, synchronously */
अटल पूर्णांक s2255_ग_लिखो_config(काष्ठा usb_device *udev, अचिन्हित अक्षर *pbuf,
			      पूर्णांक size)
अणु
	पूर्णांक pipe;
	पूर्णांक करोne;
	दीर्घ retval = -1;
	अगर (udev) अणु
		pipe = usb_sndbulkpipe(udev, S2255_CONFIG_EP);
		retval = usb_bulk_msg(udev, pipe, pbuf, size, &करोne, 500);
	पूर्ण
	वापस retval;
पूर्ण

अटल u32 get_transfer_size(काष्ठा s2255_mode *mode)
अणु
	पूर्णांक linesPerFrame = LINE_SZ_DEF;
	पूर्णांक pixelsPerLine = NUM_LINES_DEF;
	u32 outImageSize;
	u32 usbInSize;
	अचिन्हित पूर्णांक mask_mult;

	अगर (mode == शून्य)
		वापस 0;

	अगर (mode->क्रमmat == FORMAT_NTSC) अणु
		चयन (mode->scale) अणु
		हाल SCALE_4CIFS:
		हाल SCALE_4CIFSI:
			linesPerFrame = NUM_LINES_4CIFS_NTSC * 2;
			pixelsPerLine = LINE_SZ_4CIFS_NTSC;
			अवरोध;
		हाल SCALE_2CIFS:
			linesPerFrame = NUM_LINES_2CIFS_NTSC;
			pixelsPerLine = LINE_SZ_2CIFS_NTSC;
			अवरोध;
		हाल SCALE_1CIFS:
			linesPerFrame = NUM_LINES_1CIFS_NTSC;
			pixelsPerLine = LINE_SZ_1CIFS_NTSC;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (mode->क्रमmat == FORMAT_PAL) अणु
		चयन (mode->scale) अणु
		हाल SCALE_4CIFS:
		हाल SCALE_4CIFSI:
			linesPerFrame = NUM_LINES_4CIFS_PAL * 2;
			pixelsPerLine = LINE_SZ_4CIFS_PAL;
			अवरोध;
		हाल SCALE_2CIFS:
			linesPerFrame = NUM_LINES_2CIFS_PAL;
			pixelsPerLine = LINE_SZ_2CIFS_PAL;
			अवरोध;
		हाल SCALE_1CIFS:
			linesPerFrame = NUM_LINES_1CIFS_PAL;
			pixelsPerLine = LINE_SZ_1CIFS_PAL;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	outImageSize = linesPerFrame * pixelsPerLine;
	अगर ((mode->color & MASK_COLOR) != COLOR_Y8) अणु
		/* 2 bytes/pixel अगर not monochrome */
		outImageSize *= 2;
	पूर्ण

	/* total bytes to send including prefix and 4K padding;
	   must be a multiple of USB_READ_SIZE */
	usbInSize = outImageSize + PREFIX_SIZE;	/* always send prefix */
	mask_mult = 0xffffffffUL - DEF_USB_BLOCK + 1;
	/* अगर size not a multiple of USB_READ_SIZE */
	अगर (usbInSize & ~mask_mult)
		usbInSize = (usbInSize & mask_mult) + (DEF_USB_BLOCK);
	वापस usbInSize;
पूर्ण

अटल व्योम s2255_prपूर्णांक_cfg(काष्ठा s2255_dev *sdev, काष्ठा s2255_mode *mode)
अणु
	काष्ठा device *dev = &sdev->udev->dev;
	dev_info(dev, "------------------------------------------------\n");
	dev_info(dev, "format: %d\nscale %d\n", mode->क्रमmat, mode->scale);
	dev_info(dev, "fdec: %d\ncolor %d\n", mode->fdec, mode->color);
	dev_info(dev, "bright: 0x%x\n", mode->bright);
	dev_info(dev, "------------------------------------------------\n");
पूर्ण

/*
 * set mode is the function which controls the DSP.
 * the restart parameter in काष्ठा s2255_mode should be set whenever
 * the image size could change via color क्रमmat, video प्रणाली or image
 * size.
 * When the restart parameter is set, we sleep क्रम ONE frame to allow the
 * DSP समय to get the new frame
 */
अटल पूर्णांक s2255_set_mode(काष्ठा s2255_vc *vc,
			  काष्ठा s2255_mode *mode)
अणु
	पूर्णांक res;
	अचिन्हित दीर्घ chn_rev;
	काष्ठा s2255_dev *dev = to_s2255_dev(vc->vdev.v4l2_dev);
	पूर्णांक i;
	__le32 *buffer = dev->cmdbuf;

	mutex_lock(&dev->cmdlock);
	chn_rev = G_chnmap[vc->idx];
	dprपूर्णांकk(dev, 3, "%s channel: %d\n", __func__, vc->idx);
	/* अगर JPEG, set the quality */
	अगर ((mode->color & MASK_COLOR) == COLOR_JPG) अणु
		mode->color &= ~MASK_COLOR;
		mode->color |= COLOR_JPG;
		mode->color &= ~MASK_JPG_QUALITY;
		mode->color |= (vc->jpegqual << 8);
	पूर्ण
	/* save the mode */
	vc->mode = *mode;
	vc->req_image_size = get_transfer_size(mode);
	dprपूर्णांकk(dev, 1, "%s: reqsize %ld\n", __func__, vc->req_image_size);
	/* set the mode */
	buffer[0] = IN_DATA_TOKEN;
	buffer[1] = (__le32) cpu_to_le32(chn_rev);
	buffer[2] = CMD_SET_MODE;
	क्रम (i = 0; i < माप(काष्ठा s2255_mode) / माप(u32); i++)
		buffer[3 + i] = cpu_to_le32(((u32 *)&vc->mode)[i]);
	vc->seपंचांगode_पढ़ोy = 0;
	res = s2255_ग_लिखो_config(dev->udev, (अचिन्हित अक्षर *)buffer, 512);
	अगर (debug)
		s2255_prपूर्णांक_cfg(dev, mode);
	/* रुको at least 3 frames beक्रमe continuing */
	अगर (mode->restart) अणु
		रुको_event_समयout(vc->रुको_seपंचांगode,
				   (vc->seपंचांगode_पढ़ोy != 0),
				   msecs_to_jअगरfies(S2255_SETMODE_TIMEOUT));
		अगर (vc->seपंचांगode_पढ़ोy != 1) अणु
			dprपूर्णांकk(dev, 0, "s2255: no set mode response\n");
			res = -EFAULT;
		पूर्ण
	पूर्ण
	/* clear the restart flag */
	vc->mode.restart = 0;
	dprपूर्णांकk(dev, 1, "%s chn %d, result: %d\n", __func__, vc->idx, res);
	mutex_unlock(&dev->cmdlock);
	वापस res;
पूर्ण

अटल पूर्णांक s2255_cmd_status(काष्ठा s2255_vc *vc, u32 *pstatus)
अणु
	पूर्णांक res;
	u32 chn_rev;
	काष्ठा s2255_dev *dev = to_s2255_dev(vc->vdev.v4l2_dev);
	__le32 *buffer = dev->cmdbuf;

	mutex_lock(&dev->cmdlock);
	chn_rev = G_chnmap[vc->idx];
	dprपूर्णांकk(dev, 4, "%s chan %d\n", __func__, vc->idx);
	/* क्रमm the get vid status command */
	buffer[0] = IN_DATA_TOKEN;
	buffer[1] = (__le32) cpu_to_le32(chn_rev);
	buffer[2] = CMD_STATUS;
	*pstatus = 0;
	vc->vidstatus_पढ़ोy = 0;
	res = s2255_ग_लिखो_config(dev->udev, (अचिन्हित अक्षर *)buffer, 512);
	रुको_event_समयout(vc->रुको_vidstatus,
			   (vc->vidstatus_पढ़ोy != 0),
			   msecs_to_jअगरfies(S2255_VIDSTATUS_TIMEOUT));
	अगर (vc->vidstatus_पढ़ोy != 1) अणु
		dprपूर्णांकk(dev, 0, "s2255: no vidstatus response\n");
		res = -EFAULT;
	पूर्ण
	*pstatus = vc->vidstatus;
	dprपूर्णांकk(dev, 4, "%s, vid status %d\n", __func__, *pstatus);
	mutex_unlock(&dev->cmdlock);
	वापस res;
पूर्ण

अटल पूर्णांक start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा s2255_vc *vc = vb2_get_drv_priv(vq);
	पूर्णांक j;

	vc->last_frame = -1;
	vc->bad_payload = 0;
	vc->cur_frame = 0;
	vc->frame_count = 0;
	क्रम (j = 0; j < SYS_FRAMES; j++) अणु
		vc->buffer.frame[j].ulState = S2255_READ_IDLE;
		vc->buffer.frame[j].cur_size = 0;
	पूर्ण
	वापस s2255_start_acquire(vc);
पूर्ण

/* पात streaming and रुको क्रम last buffer */
अटल व्योम stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा s2255_vc *vc = vb2_get_drv_priv(vq);
	काष्ठा s2255_buffer *buf, *node;
	अचिन्हित दीर्घ flags;
	(व्योम) s2255_stop_acquire(vc);
	spin_lock_irqsave(&vc->qlock, flags);
	list_क्रम_each_entry_safe(buf, node, &vc->buf_list, list) अणु
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		dprपूर्णांकk(vc->dev, 2, "[%p/%d] done\n",
			buf, buf->vb.vb2_buf.index);
	पूर्ण
	spin_unlock_irqrestore(&vc->qlock, flags);
पूर्ण

अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id i)
अणु
	काष्ठा s2255_vc *vc = video_drvdata(file);
	काष्ठा s2255_mode mode;
	काष्ठा vb2_queue *q = &vc->vb_vidq;

	/*
	 * Changing the standard implies a क्रमmat change, which is not allowed
	 * जबतक buffers क्रम use with streaming have alपढ़ोy been allocated.
	 */
	अगर (vb2_is_busy(q))
		वापस -EBUSY;

	mode = vc->mode;
	अगर (i & V4L2_STD_525_60) अणु
		dprपूर्णांकk(vc->dev, 4, "%s 60 Hz\n", __func__);
		/* अगर changing क्रमmat, reset frame decimation/पूर्णांकervals */
		अगर (mode.क्रमmat != FORMAT_NTSC) अणु
			mode.restart = 1;
			mode.क्रमmat = FORMAT_NTSC;
			mode.fdec = FDEC_1;
			vc->width = LINE_SZ_4CIFS_NTSC;
			vc->height = NUM_LINES_4CIFS_NTSC * 2;
		पूर्ण
	पूर्ण अन्यथा अगर (i & V4L2_STD_625_50) अणु
		dprपूर्णांकk(vc->dev, 4, "%s 50 Hz\n", __func__);
		अगर (mode.क्रमmat != FORMAT_PAL) अणु
			mode.restart = 1;
			mode.क्रमmat = FORMAT_PAL;
			mode.fdec = FDEC_1;
			vc->width = LINE_SZ_4CIFS_PAL;
			vc->height = NUM_LINES_4CIFS_PAL * 2;
		पूर्ण
	पूर्ण अन्यथा
		वापस -EINVAL;
	vc->std = i;
	अगर (mode.restart)
		s2255_set_mode(vc, &mode);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *i)
अणु
	काष्ठा s2255_vc *vc = video_drvdata(file);

	*i = vc->std;
	वापस 0;
पूर्ण

/* Sensoray 2255 is a multiple channel capture device.
   It करोes not have a "crossbar" of inमाला_दो.
   We use one V4L device per channel. The user must
   be aware that certain combinations are not allowed.
   For instance, you cannot करो full FPS on more than 2 channels(2 videodevs)
   at once in color(you can करो full fps on 4 channels with greyscale.
*/
अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_input *inp)
अणु
	काष्ठा s2255_vc *vc = video_drvdata(file);
	काष्ठा s2255_dev *dev = vc->dev;
	u32 status = 0;

	अगर (inp->index != 0)
		वापस -EINVAL;
	inp->type = V4L2_INPUT_TYPE_CAMERA;
	inp->std = S2255_NORMS;
	inp->status = 0;
	अगर (dev->dsp_fw_ver >= S2255_MIN_DSP_STATUS) अणु
		पूर्णांक rc;
		rc = s2255_cmd_status(vc, &status);
		dprपूर्णांकk(dev, 4, "s2255_cmd_status rc: %d status %x\n",
			rc, status);
		अगर (rc == 0)
			inp->status =  (status & 0x01) ? 0
				: V4L2_IN_ST_NO_SIGNAL;
	पूर्ण
	चयन (dev->pid) अणु
	हाल 0x2255:
	शेष:
		strscpy(inp->name, "Composite", माप(inp->name));
		अवरोध;
	हाल 0x2257:
		strscpy(inp->name, (vc->idx < 2) ? "Composite" : "S-Video",
			माप(inp->name));
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण
अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	अगर (i > 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक s2255_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा s2255_vc *vc =
		container_of(ctrl->handler, काष्ठा s2255_vc, hdl);
	काष्ठा s2255_mode mode;
	mode = vc->mode;
	/* update the mode to the corresponding value */
	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		mode.bright = ctrl->val;
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		mode.contrast = ctrl->val;
		अवरोध;
	हाल V4L2_CID_HUE:
		mode.hue = ctrl->val;
		अवरोध;
	हाल V4L2_CID_SATURATION:
		mode.saturation = ctrl->val;
		अवरोध;
	हाल V4L2_CID_S2255_COLORFILTER:
		mode.color &= ~MASK_INPUT_TYPE;
		mode.color |= !ctrl->val << 16;
		अवरोध;
	हाल V4L2_CID_JPEG_COMPRESSION_QUALITY:
		vc->jpegqual = ctrl->val;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
	mode.restart = 0;
	/* set mode here.  Note: stream करोes not need restarted.
	   some V4L programs restart stream unnecessarily
	   after a s_crtl.
	*/
	s2255_set_mode(vc, &mode);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_jpegcomp(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_jpegcompression *jc)
अणु
	काष्ठा s2255_vc *vc = video_drvdata(file);

	स_रखो(jc, 0, माप(*jc));
	jc->quality = vc->jpegqual;
	dprपूर्णांकk(vc->dev, 2, "%s: quality %d\n", __func__, jc->quality);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_jpegcomp(काष्ठा file *file, व्योम *priv,
			 स्थिर काष्ठा v4l2_jpegcompression *jc)
अणु
	काष्ठा s2255_vc *vc = video_drvdata(file);

	अगर (jc->quality < 0 || jc->quality > 100)
		वापस -EINVAL;
	v4l2_ctrl_s_ctrl(vc->jpegqual_ctrl, jc->quality);
	dprपूर्णांकk(vc->dev, 2, "%s: quality %d\n", __func__, jc->quality);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_parm(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_streamparm *sp)
अणु
	__u32 def_num, def_dem;
	काष्ठा s2255_vc *vc = video_drvdata(file);

	अगर (sp->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;
	sp->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	sp->parm.capture.capturemode = vc->cap_parm.capturemode;
	sp->parm.capture.पढ़ोbuffers = S2255_MIN_BUFS;
	def_num = (vc->mode.क्रमmat == FORMAT_NTSC) ? 1001 : 1000;
	def_dem = (vc->mode.क्रमmat == FORMAT_NTSC) ? 30000 : 25000;
	sp->parm.capture.समयperframe.denominator = def_dem;
	चयन (vc->mode.fdec) अणु
	शेष:
	हाल FDEC_1:
		sp->parm.capture.समयperframe.numerator = def_num;
		अवरोध;
	हाल FDEC_2:
		sp->parm.capture.समयperframe.numerator = def_num * 2;
		अवरोध;
	हाल FDEC_3:
		sp->parm.capture.समयperframe.numerator = def_num * 3;
		अवरोध;
	हाल FDEC_5:
		sp->parm.capture.समयperframe.numerator = def_num * 5;
		अवरोध;
	पूर्ण
	dprपूर्णांकk(vc->dev, 4, "%s capture mode, %d timeperframe %d/%d\n",
		__func__,
		sp->parm.capture.capturemode,
		sp->parm.capture.समयperframe.numerator,
		sp->parm.capture.समयperframe.denominator);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_parm(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_streamparm *sp)
अणु
	काष्ठा s2255_vc *vc = video_drvdata(file);
	काष्ठा s2255_mode mode;
	पूर्णांक fdec = FDEC_1;
	__u32 def_num, def_dem;
	अगर (sp->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;
	mode = vc->mode;
	/* high quality capture mode requires a stream restart */
	अगर ((vc->cap_parm.capturemode != sp->parm.capture.capturemode)
	    && vb2_is_streaming(&vc->vb_vidq))
		वापस -EBUSY;
	def_num = (mode.क्रमmat == FORMAT_NTSC) ? 1001 : 1000;
	def_dem = (mode.क्रमmat == FORMAT_NTSC) ? 30000 : 25000;
	अगर (def_dem != sp->parm.capture.समयperframe.denominator)
		sp->parm.capture.समयperframe.numerator = def_num;
	अन्यथा अगर (sp->parm.capture.समयperframe.numerator <= def_num)
		sp->parm.capture.समयperframe.numerator = def_num;
	अन्यथा अगर (sp->parm.capture.समयperframe.numerator <= (def_num * 2)) अणु
		sp->parm.capture.समयperframe.numerator = def_num * 2;
		fdec = FDEC_2;
	पूर्ण अन्यथा अगर (sp->parm.capture.समयperframe.numerator <= (def_num * 3)) अणु
		sp->parm.capture.समयperframe.numerator = def_num * 3;
		fdec = FDEC_3;
	पूर्ण अन्यथा अणु
		sp->parm.capture.समयperframe.numerator = def_num * 5;
		fdec = FDEC_5;
	पूर्ण
	mode.fdec = fdec;
	sp->parm.capture.समयperframe.denominator = def_dem;
	sp->parm.capture.पढ़ोbuffers = S2255_MIN_BUFS;
	s2255_set_mode(vc, &mode);
	dprपूर्णांकk(vc->dev, 4, "%s capture mode, %d timeperframe %d/%d, fdec %d\n",
		__func__,
		sp->parm.capture.capturemode,
		sp->parm.capture.समयperframe.numerator,
		sp->parm.capture.समयperframe.denominator, fdec);
	वापस 0;
पूर्ण

#घोषणा NUM_SIZE_ENUMS 3
अटल स्थिर काष्ठा v4l2_frmsize_discrete ntsc_sizes[] = अणु
	अणु 640, 480 पूर्ण,
	अणु 640, 240 पूर्ण,
	अणु 320, 240 पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा v4l2_frmsize_discrete pal_sizes[] = अणु
	अणु 704, 576 पूर्ण,
	अणु 704, 288 पूर्ण,
	अणु 352, 288 पूर्ण,
पूर्ण;

अटल पूर्णांक vidioc_क्रमागत_framesizes(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_frmsizeक्रमागत *fe)
अणु
	काष्ठा s2255_vc *vc = video_drvdata(file);
	पूर्णांक is_ntsc = vc->std & V4L2_STD_525_60;
	स्थिर काष्ठा s2255_fmt *fmt;

	अगर (fe->index >= NUM_SIZE_ENUMS)
		वापस -EINVAL;

	fmt = क्रमmat_by_fourcc(fe->pixel_क्रमmat);
	अगर (fmt == शून्य)
		वापस -EINVAL;
	fe->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	fe->discrete = is_ntsc ?  ntsc_sizes[fe->index] : pal_sizes[fe->index];
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_frmivalक्रमागत *fe)
अणु
	काष्ठा s2255_vc *vc = video_drvdata(file);
	स्थिर काष्ठा s2255_fmt *fmt;
	स्थिर काष्ठा v4l2_frmsize_discrete *sizes;
	पूर्णांक is_ntsc = vc->std & V4L2_STD_525_60;
#घोषणा NUM_FRAME_ENUMS 4
	पूर्णांक frm_dec[NUM_FRAME_ENUMS] = अणु1, 2, 3, 5पूर्ण;
	पूर्णांक i;

	अगर (fe->index >= NUM_FRAME_ENUMS)
		वापस -EINVAL;

	fmt = क्रमmat_by_fourcc(fe->pixel_क्रमmat);
	अगर (fmt == शून्य)
		वापस -EINVAL;

	sizes = is_ntsc ? ntsc_sizes : pal_sizes;
	क्रम (i = 0; i < NUM_SIZE_ENUMS; i++, sizes++)
		अगर (fe->width == sizes->width &&
		    fe->height == sizes->height)
			अवरोध;
	अगर (i == NUM_SIZE_ENUMS)
		वापस -EINVAL;

	fe->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fe->discrete.denominator = is_ntsc ? 30000 : 25000;
	fe->discrete.numerator = (is_ntsc ? 1001 : 1000) * frm_dec[fe->index];
	dprपूर्णांकk(vc->dev, 4, "%s discrete %d/%d\n", __func__,
		fe->discrete.numerator,
		fe->discrete.denominator);
	वापस 0;
पूर्ण

अटल पूर्णांक s2255_खोलो(काष्ठा file *file)
अणु
	काष्ठा s2255_vc *vc = video_drvdata(file);
	काष्ठा s2255_dev *dev = vc->dev;
	पूर्णांक state;
	पूर्णांक rc = 0;

	rc = v4l2_fh_खोलो(file);
	अगर (rc != 0)
		वापस rc;

	dprपूर्णांकk(dev, 1, "s2255: %s\n", __func__);
	state = atomic_पढ़ो(&dev->fw_data->fw_state);
	चयन (state) अणु
	हाल S2255_FW_DISCONNECTING:
		वापस -ENODEV;
	हाल S2255_FW_FAILED:
		s2255_dev_err(&dev->udev->dev,
			"firmware load failed. retrying.\n");
		s2255_fwload_start(dev);
		रुको_event_समयout(dev->fw_data->रुको_fw,
				   ((atomic_पढ़ो(&dev->fw_data->fw_state)
				     == S2255_FW_SUCCESS) ||
				    (atomic_पढ़ो(&dev->fw_data->fw_state)
				     == S2255_FW_DISCONNECTING)),
				   msecs_to_jअगरfies(S2255_LOAD_TIMEOUT));
		/* state may have changed, re-पढ़ो */
		state = atomic_पढ़ो(&dev->fw_data->fw_state);
		अवरोध;
	हाल S2255_FW_NOTLOADED:
	हाल S2255_FW_LOADED_DSPWAIT:
		/* give S2255_LOAD_TIMEOUT समय क्रम firmware to load in हाल
		   driver loaded and then device immediately खोलोed */
		pr_info("%s waiting for firmware load\n", __func__);
		रुको_event_समयout(dev->fw_data->रुको_fw,
				   ((atomic_पढ़ो(&dev->fw_data->fw_state)
				     == S2255_FW_SUCCESS) ||
				    (atomic_पढ़ो(&dev->fw_data->fw_state)
				     == S2255_FW_DISCONNECTING)),
				   msecs_to_jअगरfies(S2255_LOAD_TIMEOUT));
		/* state may have changed, re-पढ़ो */
		state = atomic_पढ़ो(&dev->fw_data->fw_state);
		अवरोध;
	हाल S2255_FW_SUCCESS:
	शेष:
		अवरोध;
	पूर्ण
	/* state may have changed in above चयन statement */
	चयन (state) अणु
	हाल S2255_FW_SUCCESS:
		अवरोध;
	हाल S2255_FW_FAILED:
		pr_info("2255 firmware load failed.\n");
		वापस -ENODEV;
	हाल S2255_FW_DISCONNECTING:
		pr_info("%s: disconnecting\n", __func__);
		वापस -ENODEV;
	हाल S2255_FW_LOADED_DSPWAIT:
	हाल S2255_FW_NOTLOADED:
		pr_info("%s: firmware not loaded, please retry\n",
			__func__);
		/*
		 * Timeout on firmware load means device unusable.
		 * Set firmware failure state.
		 * On next s2255_खोलो the firmware will be reloaded.
		 */
		atomic_set(&dev->fw_data->fw_state,
			   S2255_FW_FAILED);
		वापस -EAGAIN;
	शेष:
		pr_info("%s: unknown state\n", __func__);
		वापस -EFAULT;
	पूर्ण
	अगर (!vc->configured) अणु
		/* configure channel to शेष state */
		vc->fmt = &क्रमmats[0];
		s2255_set_mode(vc, &vc->mode);
		vc->configured = 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम s2255_destroy(काष्ठा s2255_dev *dev)
अणु
	dprपूर्णांकk(dev, 1, "%s", __func__);
	/* board shutकरोwn stops the पढ़ो pipe अगर it is running */
	s2255_board_shutकरोwn(dev);
	/* make sure firmware still not trying to load */
	del_समयr_sync(&dev->समयr);  /* only started in .probe and .खोलो */
	अगर (dev->fw_data->fw_urb) अणु
		usb_समाप्त_urb(dev->fw_data->fw_urb);
		usb_मुक्त_urb(dev->fw_data->fw_urb);
		dev->fw_data->fw_urb = शून्य;
	पूर्ण
	release_firmware(dev->fw_data->fw);
	kमुक्त(dev->fw_data->pfw_data);
	kमुक्त(dev->fw_data);
	/* reset the DSP so firmware can be reloaded next समय */
	s2255_reset_dspघातer(dev);
	mutex_destroy(&dev->lock);
	usb_put_dev(dev->udev);
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	kमुक्त(dev->cmdbuf);
	kमुक्त(dev);
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations s2255_fops_v4l = अणु
	.owner = THIS_MODULE,
	.खोलो = s2255_खोलो,
	.release = vb2_fop_release,
	.poll = vb2_fop_poll,
	.unlocked_ioctl = video_ioctl2,	/* V4L2 ioctl handler */
	.mmap = vb2_fop_mmap,
	.पढ़ो = vb2_fop_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops s2255_ioctl_ops = अणु
	.vidioc_querycap = vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap = vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap = vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = vidioc_s_fmt_vid_cap,
	.vidioc_reqbufs = vb2_ioctl_reqbufs,
	.vidioc_querybuf = vb2_ioctl_querybuf,
	.vidioc_qbuf = vb2_ioctl_qbuf,
	.vidioc_dqbuf = vb2_ioctl_dqbuf,
	.vidioc_s_std = vidioc_s_std,
	.vidioc_g_std = vidioc_g_std,
	.vidioc_क्रमागत_input = vidioc_क्रमागत_input,
	.vidioc_g_input = vidioc_g_input,
	.vidioc_s_input = vidioc_s_input,
	.vidioc_streamon = vb2_ioctl_streamon,
	.vidioc_streamoff = vb2_ioctl_streamoff,
	.vidioc_s_jpegcomp = vidioc_s_jpegcomp,
	.vidioc_g_jpegcomp = vidioc_g_jpegcomp,
	.vidioc_s_parm = vidioc_s_parm,
	.vidioc_g_parm = vidioc_g_parm,
	.vidioc_क्रमागत_framesizes = vidioc_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals = vidioc_क्रमागत_frameपूर्णांकervals,
	.vidioc_log_status  = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल व्योम s2255_video_device_release(काष्ठा video_device *vdev)
अणु
	काष्ठा s2255_dev *dev = to_s2255_dev(vdev->v4l2_dev);
	काष्ठा s2255_vc *vc =
		container_of(vdev, काष्ठा s2255_vc, vdev);

	dprपूर्णांकk(dev, 4, "%s, chnls: %d\n", __func__,
		atomic_पढ़ो(&dev->num_channels));

	v4l2_ctrl_handler_मुक्त(&vc->hdl);

	अगर (atomic_dec_and_test(&dev->num_channels))
		s2255_destroy(dev);
	वापस;
पूर्ण

अटल स्थिर काष्ठा video_device ढाँचा = अणु
	.name = "s2255v",
	.fops = &s2255_fops_v4l,
	.ioctl_ops = &s2255_ioctl_ops,
	.release = s2255_video_device_release,
	.tvnorms = S2255_NORMS,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops s2255_ctrl_ops = अणु
	.s_ctrl = s2255_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config color_filter_ctrl = अणु
	.ops = &s2255_ctrl_ops,
	.name = "Color Filter",
	.id = V4L2_CID_S2255_COLORFILTER,
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.max = 1,
	.step = 1,
	.def = 1,
पूर्ण;

अटल पूर्णांक s2255_probe_v4l(काष्ठा s2255_dev *dev)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक cur_nr = video_nr;
	काष्ठा s2255_vc *vc;
	काष्ठा vb2_queue *q;

	ret = v4l2_device_रेजिस्टर(&dev->पूर्णांकerface->dev, &dev->v4l2_dev);
	अगर (ret)
		वापस ret;
	/* initialize all video 4 linux */
	/* रेजिस्टर 4 video devices */
	क्रम (i = 0; i < MAX_CHANNELS; i++) अणु
		vc = &dev->vc[i];
		INIT_LIST_HEAD(&vc->buf_list);

		v4l2_ctrl_handler_init(&vc->hdl, 6);
		v4l2_ctrl_new_std(&vc->hdl, &s2255_ctrl_ops,
				V4L2_CID_BRIGHTNESS, -127, 127, 1, DEF_BRIGHT);
		v4l2_ctrl_new_std(&vc->hdl, &s2255_ctrl_ops,
				V4L2_CID_CONTRAST, 0, 255, 1, DEF_CONTRAST);
		v4l2_ctrl_new_std(&vc->hdl, &s2255_ctrl_ops,
				V4L2_CID_SATURATION, 0, 255, 1, DEF_SATURATION);
		v4l2_ctrl_new_std(&vc->hdl, &s2255_ctrl_ops,
				V4L2_CID_HUE, 0, 255, 1, DEF_HUE);
		vc->jpegqual_ctrl = v4l2_ctrl_new_std(&vc->hdl,
				&s2255_ctrl_ops,
				V4L2_CID_JPEG_COMPRESSION_QUALITY,
				0, 100, 1, S2255_DEF_JPEG_QUAL);
		अगर (dev->dsp_fw_ver >= S2255_MIN_DSP_COLORFILTER &&
		    (dev->pid != 0x2257 || vc->idx <= 1))
			v4l2_ctrl_new_custom(&vc->hdl, &color_filter_ctrl,
					     शून्य);
		अगर (vc->hdl.error) अणु
			ret = vc->hdl.error;
			v4l2_ctrl_handler_मुक्त(&vc->hdl);
			dev_err(&dev->udev->dev, "couldn't register control\n");
			अवरोध;
		पूर्ण
		q = &vc->vb_vidq;
		q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		q->io_modes = VB2_MMAP | VB2_READ | VB2_USERPTR;
		q->drv_priv = vc;
		q->lock = &vc->vb_lock;
		q->buf_काष्ठा_size = माप(काष्ठा s2255_buffer);
		q->mem_ops = &vb2_vदो_स्मृति_memops;
		q->ops = &s2255_video_qops;
		q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
		ret = vb2_queue_init(q);
		अगर (ret != 0) अणु
			dev_err(&dev->udev->dev,
				"%s vb2_queue_init 0x%x\n", __func__, ret);
			अवरोध;
		पूर्ण
		/* रेजिस्टर video devices */
		vc->vdev = ढाँचा;
		vc->vdev.queue = q;
		vc->vdev.ctrl_handler = &vc->hdl;
		vc->vdev.lock = &dev->lock;
		vc->vdev.v4l2_dev = &dev->v4l2_dev;
		vc->vdev.device_caps = V4L2_CAP_VIDEO_CAPTURE |
				       V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;
		video_set_drvdata(&vc->vdev, vc);
		अगर (video_nr == -1)
			ret = video_रेजिस्टर_device(&vc->vdev,
						    VFL_TYPE_VIDEO,
						    video_nr);
		अन्यथा
			ret = video_रेजिस्टर_device(&vc->vdev,
						    VFL_TYPE_VIDEO,
						    cur_nr + i);

		अगर (ret) अणु
			dev_err(&dev->udev->dev,
				"failed to register video device!\n");
			अवरोध;
		पूर्ण
		atomic_inc(&dev->num_channels);
		v4l2_info(&dev->v4l2_dev, "V4L2 device registered as %s\n",
			  video_device_node_name(&vc->vdev));

	पूर्ण
	pr_info("Sensoray 2255 V4L driver Revision: %s\n",
		S2255_VERSION);
	/* अगर no channels रेजिस्टरed, वापस error and probe will fail*/
	अगर (atomic_पढ़ो(&dev->num_channels) == 0) अणु
		v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
		वापस ret;
	पूर्ण
	अगर (atomic_पढ़ो(&dev->num_channels) != MAX_CHANNELS)
		pr_warn("s2255: Not all channels available.\n");
	वापस 0;
पूर्ण

/* this function moves the usb stream पढ़ो pipe data
 * पूर्णांकo the प्रणाली buffers.
 * वापसs 0 on success, EAGAIN अगर more data to process( call this
 * function again).
 *
 * Received frame काष्ठाure:
 * bytes 0-3:  marker : 0x2255DA4AL (S2255_MARKER_FRAME)
 * bytes 4-7:  channel: 0-3
 * bytes 8-11: payload size:  size of the frame
 * bytes 12-payloadsize+12:  frame data
 */
अटल पूर्णांक save_frame(काष्ठा s2255_dev *dev, काष्ठा s2255_pipeinfo *pipe_info)
अणु
	अक्षर *pdest;
	u32 offset = 0;
	पूर्णांक bframe = 0;
	अक्षर *psrc;
	अचिन्हित दीर्घ copy_size;
	अचिन्हित दीर्घ size;
	s32 idx = -1;
	काष्ठा s2255_framei *frm;
	अचिन्हित अक्षर *pdata;
	काष्ठा s2255_vc *vc;
	dprपूर्णांकk(dev, 100, "buffer to user\n");
	vc = &dev->vc[dev->cc];
	idx = vc->cur_frame;
	frm = &vc->buffer.frame[idx];
	अगर (frm->ulState == S2255_READ_IDLE) अणु
		पूर्णांक jj;
		अचिन्हित पूर्णांक cc;
		__le32 *pdword; /*data from dsp is little endian */
		पूर्णांक payload;
		/* search क्रम marker codes */
		pdata = (अचिन्हित अक्षर *)pipe_info->transfer_buffer;
		pdword = (__le32 *)pdata;
		क्रम (jj = 0; jj < (pipe_info->cur_transfer_size - 12); jj++) अणु
			चयन (*pdword) अणु
			हाल S2255_MARKER_FRAME:
				dprपूर्णांकk(dev, 4, "marker @ offset: %d [%x %x]\n",
					jj, pdata[0], pdata[1]);
				offset = jj + PREFIX_SIZE;
				bframe = 1;
				cc = le32_to_cpu(pdword[1]);
				अगर (cc >= MAX_CHANNELS) अणु
					dprपूर्णांकk(dev, 0,
						"bad channel\n");
					वापस -EINVAL;
				पूर्ण
				/* reverse it */
				dev->cc = G_chnmap[cc];
				vc = &dev->vc[dev->cc];
				payload =  le32_to_cpu(pdword[3]);
				अगर (payload > vc->req_image_size) अणु
					vc->bad_payload++;
					/* discard the bad frame */
					वापस -EINVAL;
				पूर्ण
				vc->pkt_size = payload;
				vc->jpg_size = le32_to_cpu(pdword[4]);
				अवरोध;
			हाल S2255_MARKER_RESPONSE:

				pdata += DEF_USB_BLOCK;
				jj += DEF_USB_BLOCK;
				अगर (le32_to_cpu(pdword[1]) >= MAX_CHANNELS)
					अवरोध;
				cc = G_chnmap[le32_to_cpu(pdword[1])];
				अगर (cc >= MAX_CHANNELS)
					अवरोध;
				vc = &dev->vc[cc];
				चयन (pdword[2]) अणु
				हाल S2255_RESPONSE_SETMODE:
					/* check अगर channel valid */
					/* set mode पढ़ोy */
					vc->seपंचांगode_पढ़ोy = 1;
					wake_up(&vc->रुको_seपंचांगode);
					dprपूर्णांकk(dev, 5, "setmode rdy %d\n", cc);
					अवरोध;
				हाल S2255_RESPONSE_FW:
					dev->chn_पढ़ोy |= (1 << cc);
					अगर ((dev->chn_पढ़ोy & 0x0f) != 0x0f)
						अवरोध;
					/* all channels पढ़ोy */
					pr_info("s2255: fw loaded\n");
					atomic_set(&dev->fw_data->fw_state,
						   S2255_FW_SUCCESS);
					wake_up(&dev->fw_data->रुको_fw);
					अवरोध;
				हाल S2255_RESPONSE_STATUS:
					vc->vidstatus = le32_to_cpu(pdword[3]);
					vc->vidstatus_पढ़ोy = 1;
					wake_up(&vc->रुको_vidstatus);
					dprपूर्णांकk(dev, 5, "vstat %x chan %d\n",
						le32_to_cpu(pdword[3]), cc);
					अवरोध;
				शेष:
					pr_info("s2255 unknown resp\n");
				पूर्ण
				pdata++;
				अवरोध;
			शेष:
				pdata++;
				अवरोध;
			पूर्ण
			अगर (bframe)
				अवरोध;
		पूर्ण /* क्रम */
		अगर (!bframe)
			वापस -EINVAL;
	पूर्ण
	vc = &dev->vc[dev->cc];
	idx = vc->cur_frame;
	frm = &vc->buffer.frame[idx];
	/* search करोne.  now find out अगर should be acquiring on this channel */
	अगर (!vb2_is_streaming(&vc->vb_vidq)) अणु
		/* we found a frame, but this channel is turned off */
		frm->ulState = S2255_READ_IDLE;
		वापस -EINVAL;
	पूर्ण

	अगर (frm->ulState == S2255_READ_IDLE) अणु
		frm->ulState = S2255_READ_FRAME;
		frm->cur_size = 0;
	पूर्ण

	/* skip the marker 512 bytes (and offset अगर out of sync) */
	psrc = (u8 *)pipe_info->transfer_buffer + offset;


	अगर (frm->lpvbits == शून्य) अणु
		dprपूर्णांकk(dev, 1, "s2255 frame buffer == NULL.%p %p %d %d",
			frm, dev, dev->cc, idx);
		वापस -ENOMEM;
	पूर्ण

	pdest = frm->lpvbits + frm->cur_size;

	copy_size = (pipe_info->cur_transfer_size - offset);

	size = vc->pkt_size - PREFIX_SIZE;

	/* sanity check on pdest */
	अगर ((copy_size + frm->cur_size) < vc->req_image_size)
		स_नकल(pdest, psrc, copy_size);

	frm->cur_size += copy_size;
	dprपूर्णांकk(dev, 4, "cur_size: %lu, size: %lu\n", frm->cur_size, size);

	अगर (frm->cur_size >= size) अणु
		dprपूर्णांकk(dev, 2, "******[%d]Buffer[%d]full*******\n",
			dev->cc, idx);
		vc->last_frame = vc->cur_frame;
		vc->cur_frame++;
		/* end of प्रणाली frame ring buffer, start at zero */
		अगर ((vc->cur_frame == SYS_FRAMES) ||
		    (vc->cur_frame == vc->buffer.dwFrames))
			vc->cur_frame = 0;
		/* frame पढ़ोy */
		अगर (vb2_is_streaming(&vc->vb_vidq))
			s2255_got_frame(vc, vc->jpg_size);
		vc->frame_count++;
		frm->ulState = S2255_READ_IDLE;
		frm->cur_size = 0;

	पूर्ण
	/* करोne successfully */
	वापस 0;
पूर्ण

अटल व्योम s2255_पढ़ो_video_callback(काष्ठा s2255_dev *dev,
				      काष्ठा s2255_pipeinfo *pipe_info)
अणु
	पूर्णांक res;
	dprपूर्णांकk(dev, 50, "callback read video\n");

	अगर (dev->cc >= MAX_CHANNELS) अणु
		dev->cc = 0;
		dev_err(&dev->udev->dev, "invalid channel\n");
		वापस;
	पूर्ण
	/* otherwise copy to the प्रणाली buffers */
	res = save_frame(dev, pipe_info);
	अगर (res != 0)
		dprपूर्णांकk(dev, 4, "s2255: read callback failed\n");

	dprपूर्णांकk(dev, 50, "callback read video done\n");
	वापस;
पूर्ण

अटल दीर्घ s2255_venकरोr_req(काष्ठा s2255_dev *dev, अचिन्हित अक्षर Request,
			     u16 Index, u16 Value, व्योम *TransferBuffer,
			     s32 TransferBufferLength, पूर्णांक bOut)
अणु
	पूर्णांक r;
	अचिन्हित अक्षर *buf;

	buf = kदो_स्मृति(TransferBufferLength, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (!bOut) अणु
		r = usb_control_msg(dev->udev, usb_rcvctrlpipe(dev->udev, 0),
				    Request,
				    USB_TYPE_VENDOR | USB_RECIP_DEVICE |
				    USB_सूची_IN,
				    Value, Index, buf,
				    TransferBufferLength, HZ * 5);

		अगर (r >= 0)
			स_नकल(TransferBuffer, buf, TransferBufferLength);
	पूर्ण अन्यथा अणु
		स_नकल(buf, TransferBuffer, TransferBufferLength);
		r = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, 0),
				    Request, USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				    Value, Index, buf,
				    TransferBufferLength, HZ * 5);
	पूर्ण
	kमुक्त(buf);
	वापस r;
पूर्ण

/*
 * retrieve FX2 firmware version. future use.
 * @param dev poपूर्णांकer to device extension
 * @वापस -1 क्रम fail, अन्यथा वापसs firmware version as an पूर्णांक(16 bits)
 */
अटल पूर्णांक s2255_get_fx2fw(काष्ठा s2255_dev *dev)
अणु
	पूर्णांक fw;
	पूर्णांक ret;
	अचिन्हित अक्षर transBuffer[64];
	ret = s2255_venकरोr_req(dev, S2255_VR_FW, 0, 0, transBuffer, 2,
			       S2255_VR_IN);
	अगर (ret < 0)
		dprपूर्णांकk(dev, 2, "get fw error: %x\n", ret);
	fw = transBuffer[0] + (transBuffer[1] << 8);
	dprपूर्णांकk(dev, 2, "Get FW %x %x\n", transBuffer[0], transBuffer[1]);
	वापस fw;
पूर्ण

/*
 * Create the प्रणाली ring buffer to copy frames पूर्णांकo from the
 * usb पढ़ो pipe.
 */
अटल पूर्णांक s2255_create_sys_buffers(काष्ठा s2255_vc *vc)
अणु
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ reqsize;
	vc->buffer.dwFrames = SYS_FRAMES;
	/* always allocate maximum size(PAL) क्रम प्रणाली buffers */
	reqsize = SYS_FRAMES_MAXSIZE;

	अगर (reqsize > SYS_FRAMES_MAXSIZE)
		reqsize = SYS_FRAMES_MAXSIZE;

	क्रम (i = 0; i < SYS_FRAMES; i++) अणु
		/* allocate the frames */
		vc->buffer.frame[i].lpvbits = vदो_स्मृति(reqsize);
		vc->buffer.frame[i].size = reqsize;
		अगर (vc->buffer.frame[i].lpvbits == शून्य) अणु
			pr_info("out of memory.  using less frames\n");
			vc->buffer.dwFrames = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/* make sure पूर्णांकernal states are set */
	क्रम (i = 0; i < SYS_FRAMES; i++) अणु
		vc->buffer.frame[i].ulState = 0;
		vc->buffer.frame[i].cur_size = 0;
	पूर्ण

	vc->cur_frame = 0;
	vc->last_frame = -1;
	वापस 0;
पूर्ण

अटल पूर्णांक s2255_release_sys_buffers(काष्ठा s2255_vc *vc)
अणु
	अचिन्हित दीर्घ i;
	क्रम (i = 0; i < SYS_FRAMES; i++) अणु
		vमुक्त(vc->buffer.frame[i].lpvbits);
		vc->buffer.frame[i].lpvbits = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s2255_board_init(काष्ठा s2255_dev *dev)
अणु
	काष्ठा s2255_mode mode_def = DEF_MODEI_NTSC_CONT;
	पूर्णांक fw_ver;
	पूर्णांक j;
	काष्ठा s2255_pipeinfo *pipe = &dev->pipe;
	dprपूर्णांकk(dev, 4, "board init: %p", dev);
	स_रखो(pipe, 0, माप(*pipe));
	pipe->dev = dev;
	pipe->cur_transfer_size = S2255_USB_XFER_SIZE;
	pipe->max_transfer_size = S2255_USB_XFER_SIZE;

	pipe->transfer_buffer = kzalloc(pipe->max_transfer_size,
					GFP_KERNEL);
	अगर (pipe->transfer_buffer == शून्य) अणु
		dprपूर्णांकk(dev, 1, "out of memory!\n");
		वापस -ENOMEM;
	पूर्ण
	/* query the firmware */
	fw_ver = s2255_get_fx2fw(dev);

	pr_info("s2255: usb firmware version %d.%d\n",
		(fw_ver >> 8) & 0xff,
		fw_ver & 0xff);

	अगर (fw_ver < S2255_CUR_USB_FWVER)
		pr_info("s2255: newer USB firmware available\n");

	क्रम (j = 0; j < MAX_CHANNELS; j++) अणु
		काष्ठा s2255_vc *vc = &dev->vc[j];
		vc->mode = mode_def;
		अगर (dev->pid == 0x2257 && j > 1)
			vc->mode.color |= (1 << 16);
		vc->jpegqual = S2255_DEF_JPEG_QUAL;
		vc->width = LINE_SZ_4CIFS_NTSC;
		vc->height = NUM_LINES_4CIFS_NTSC * 2;
		vc->std = V4L2_STD_NTSC_M;
		vc->fmt = &क्रमmats[0];
		vc->mode.restart = 1;
		vc->req_image_size = get_transfer_size(&mode_def);
		vc->frame_count = 0;
		/* create the प्रणाली buffers */
		s2255_create_sys_buffers(vc);
	पूर्ण
	/* start पढ़ो pipe */
	s2255_start_पढ़ोpipe(dev);
	dprपूर्णांकk(dev, 1, "%s: success\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक s2255_board_shutकरोwn(काष्ठा s2255_dev *dev)
अणु
	u32 i;
	dprपूर्णांकk(dev, 1, "%s: dev: %p", __func__,  dev);

	क्रम (i = 0; i < MAX_CHANNELS; i++) अणु
		अगर (vb2_is_streaming(&dev->vc[i].vb_vidq))
			s2255_stop_acquire(&dev->vc[i]);
	पूर्ण
	s2255_stop_पढ़ोpipe(dev);
	क्रम (i = 0; i < MAX_CHANNELS; i++)
		s2255_release_sys_buffers(&dev->vc[i]);
	/* release transfer buffer */
	kमुक्त(dev->pipe.transfer_buffer);
	वापस 0;
पूर्ण

अटल व्योम पढ़ो_pipe_completion(काष्ठा urb *purb)
अणु
	काष्ठा s2255_pipeinfo *pipe_info;
	काष्ठा s2255_dev *dev;
	पूर्णांक status;
	पूर्णांक pipe;
	pipe_info = purb->context;
	अगर (pipe_info == शून्य) अणु
		dev_err(&purb->dev->dev, "no context!\n");
		वापस;
	पूर्ण
	dev = pipe_info->dev;
	अगर (dev == शून्य) अणु
		dev_err(&purb->dev->dev, "no context!\n");
		वापस;
	पूर्ण
	status = purb->status;
	/* अगर shutting करोwn, करो not resubmit, निकास immediately */
	अगर (status == -ESHUTDOWN) अणु
		dprपूर्णांकk(dev, 2, "%s: err shutdown\n", __func__);
		pipe_info->err_count++;
		वापस;
	पूर्ण

	अगर (pipe_info->state == 0) अणु
		dprपूर्णांकk(dev, 2, "%s: exiting USB pipe", __func__);
		वापस;
	पूर्ण

	अगर (status == 0)
		s2255_पढ़ो_video_callback(dev, pipe_info);
	अन्यथा अणु
		pipe_info->err_count++;
		dprपूर्णांकk(dev, 1, "%s: failed URB %d\n", __func__, status);
	पूर्ण

	pipe = usb_rcvbulkpipe(dev->udev, dev->पढ़ो_endpoपूर्णांक);
	/* reuse urb */
	usb_fill_bulk_urb(pipe_info->stream_urb, dev->udev,
			  pipe,
			  pipe_info->transfer_buffer,
			  pipe_info->cur_transfer_size,
			  पढ़ो_pipe_completion, pipe_info);

	अगर (pipe_info->state != 0) अणु
		अगर (usb_submit_urb(pipe_info->stream_urb, GFP_ATOMIC))
			dev_err(&dev->udev->dev, "error submitting urb\n");
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(dev, 2, "%s :complete state 0\n", __func__);
	पूर्ण
	वापस;
पूर्ण

अटल पूर्णांक s2255_start_पढ़ोpipe(काष्ठा s2255_dev *dev)
अणु
	पूर्णांक pipe;
	पूर्णांक retval;
	काष्ठा s2255_pipeinfo *pipe_info = &dev->pipe;
	pipe = usb_rcvbulkpipe(dev->udev, dev->पढ़ो_endpoपूर्णांक);
	dprपूर्णांकk(dev, 2, "%s: IN %d\n", __func__, dev->पढ़ो_endpoपूर्णांक);
	pipe_info->state = 1;
	pipe_info->err_count = 0;
	pipe_info->stream_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!pipe_info->stream_urb)
		वापस -ENOMEM;
	/* transfer buffer allocated in board_init */
	usb_fill_bulk_urb(pipe_info->stream_urb, dev->udev,
			  pipe,
			  pipe_info->transfer_buffer,
			  pipe_info->cur_transfer_size,
			  पढ़ो_pipe_completion, pipe_info);
	retval = usb_submit_urb(pipe_info->stream_urb, GFP_KERNEL);
	अगर (retval) अणु
		pr_err("s2255: start read pipe failed\n");
		वापस retval;
	पूर्ण
	वापस 0;
पूर्ण

/* starts acquisition process */
अटल पूर्णांक s2255_start_acquire(काष्ठा s2255_vc *vc)
अणु
	पूर्णांक res;
	अचिन्हित दीर्घ chn_rev;
	पूर्णांक j;
	काष्ठा s2255_dev *dev = to_s2255_dev(vc->vdev.v4l2_dev);
	__le32 *buffer = dev->cmdbuf;

	mutex_lock(&dev->cmdlock);
	chn_rev = G_chnmap[vc->idx];
	vc->last_frame = -1;
	vc->bad_payload = 0;
	vc->cur_frame = 0;
	क्रम (j = 0; j < SYS_FRAMES; j++) अणु
		vc->buffer.frame[j].ulState = 0;
		vc->buffer.frame[j].cur_size = 0;
	पूर्ण

	/* send the start command */
	buffer[0] = IN_DATA_TOKEN;
	buffer[1] = (__le32) cpu_to_le32(chn_rev);
	buffer[2] = CMD_START;
	res = s2255_ग_लिखो_config(dev->udev, (अचिन्हित अक्षर *)buffer, 512);
	अगर (res != 0)
		dev_err(&dev->udev->dev, "CMD_START error\n");

	dprपूर्णांकk(dev, 2, "start acquire exit[%d] %d\n", vc->idx, res);
	mutex_unlock(&dev->cmdlock);
	वापस res;
पूर्ण

अटल पूर्णांक s2255_stop_acquire(काष्ठा s2255_vc *vc)
अणु
	पूर्णांक res;
	अचिन्हित दीर्घ chn_rev;
	काष्ठा s2255_dev *dev = to_s2255_dev(vc->vdev.v4l2_dev);
	__le32 *buffer = dev->cmdbuf;

	mutex_lock(&dev->cmdlock);
	chn_rev = G_chnmap[vc->idx];
	/* send the stop command */
	buffer[0] = IN_DATA_TOKEN;
	buffer[1] = (__le32) cpu_to_le32(chn_rev);
	buffer[2] = CMD_STOP;

	res = s2255_ग_लिखो_config(dev->udev, (अचिन्हित अक्षर *)buffer, 512);
	अगर (res != 0)
		dev_err(&dev->udev->dev, "CMD_STOP error\n");

	dprपूर्णांकk(dev, 4, "%s: chn %d, res %d\n", __func__, vc->idx, res);
	mutex_unlock(&dev->cmdlock);
	वापस res;
पूर्ण

अटल व्योम s2255_stop_पढ़ोpipe(काष्ठा s2255_dev *dev)
अणु
	काष्ठा s2255_pipeinfo *pipe = &dev->pipe;

	pipe->state = 0;
	अगर (pipe->stream_urb) अणु
		/* cancel urb */
		usb_समाप्त_urb(pipe->stream_urb);
		usb_मुक्त_urb(pipe->stream_urb);
		pipe->stream_urb = शून्य;
	पूर्ण
	dprपूर्णांकk(dev, 4, "%s", __func__);
	वापस;
पूर्ण

अटल व्योम s2255_fwload_start(काष्ठा s2255_dev *dev)
अणु
	s2255_reset_dspघातer(dev);
	dev->fw_data->fw_size = dev->fw_data->fw->size;
	atomic_set(&dev->fw_data->fw_state, S2255_FW_NOTLOADED);
	स_नकल(dev->fw_data->pfw_data,
	       dev->fw_data->fw->data, CHUNK_SIZE);
	dev->fw_data->fw_loaded = CHUNK_SIZE;
	usb_fill_bulk_urb(dev->fw_data->fw_urb, dev->udev,
			  usb_sndbulkpipe(dev->udev, 2),
			  dev->fw_data->pfw_data,
			  CHUNK_SIZE, s2255_fwchunk_complete,
			  dev->fw_data);
	mod_समयr(&dev->समयr, jअगरfies + HZ);
पूर्ण

/* standard usb probe function */
अटल पूर्णांक s2255_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		       स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा s2255_dev *dev = शून्य;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	पूर्णांक i;
	पूर्णांक retval = -ENOMEM;
	__le32 *pdata;
	पूर्णांक fw_size;

	/* allocate memory क्रम our device state and initialize it to zero */
	dev = kzalloc(माप(काष्ठा s2255_dev), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		s2255_dev_err(&पूर्णांकerface->dev, "out of memory\n");
		वापस -ENOMEM;
	पूर्ण

	dev->cmdbuf = kzalloc(S2255_CMDBUF_SIZE, GFP_KERNEL);
	अगर (dev->cmdbuf == शून्य) अणु
		s2255_dev_err(&पूर्णांकerface->dev, "out of memory\n");
		जाओ errorFWDATA1;
	पूर्ण

	atomic_set(&dev->num_channels, 0);
	dev->pid = id->idProduct;
	dev->fw_data = kzalloc(माप(काष्ठा s2255_fw), GFP_KERNEL);
	अगर (!dev->fw_data)
		जाओ errorFWDATA1;
	mutex_init(&dev->lock);
	mutex_init(&dev->cmdlock);
	/* grab usb_device and save it */
	dev->udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));
	अगर (dev->udev == शून्य) अणु
		dev_err(&पूर्णांकerface->dev, "null usb device\n");
		retval = -ENODEV;
		जाओ errorUDEV;
	पूर्ण
	dev_dbg(&पूर्णांकerface->dev, "dev: %p, udev %p interface %p\n",
		dev, dev->udev, पूर्णांकerface);
	dev->पूर्णांकerface = पूर्णांकerface;
	/* set up the endpoपूर्णांक inक्रमmation  */
	अगरace_desc = पूर्णांकerface->cur_altsetting;
	dev_dbg(&पूर्णांकerface->dev, "num EP: %d\n",
		अगरace_desc->desc.bNumEndpoपूर्णांकs);
	क्रम (i = 0; i < अगरace_desc->desc.bNumEndpoपूर्णांकs; ++i) अणु
		endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[i].desc;
		अगर (!dev->पढ़ो_endpoपूर्णांक && usb_endpoपूर्णांक_is_bulk_in(endpoपूर्णांक)) अणु
			/* we found the bulk in endpoपूर्णांक */
			dev->पढ़ो_endpoपूर्णांक = endpoपूर्णांक->bEndpoपूर्णांकAddress;
		पूर्ण
	पूर्ण

	अगर (!dev->पढ़ो_endpoपूर्णांक) अणु
		dev_err(&पूर्णांकerface->dev, "Could not find bulk-in endpoint\n");
		जाओ errorEP;
	पूर्ण
	समयr_setup(&dev->समयr, s2255_समयr, 0);
	init_रुकोqueue_head(&dev->fw_data->रुको_fw);
	क्रम (i = 0; i < MAX_CHANNELS; i++) अणु
		काष्ठा s2255_vc *vc = &dev->vc[i];
		vc->idx = i;
		vc->dev = dev;
		init_रुकोqueue_head(&vc->रुको_seपंचांगode);
		init_रुकोqueue_head(&vc->रुको_vidstatus);
		spin_lock_init(&vc->qlock);
		mutex_init(&vc->vb_lock);
	पूर्ण

	dev->fw_data->fw_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->fw_data->fw_urb)
		जाओ errorFWURB;

	dev->fw_data->pfw_data = kzalloc(CHUNK_SIZE, GFP_KERNEL);
	अगर (!dev->fw_data->pfw_data) अणु
		dev_err(&पूर्णांकerface->dev, "out of memory!\n");
		जाओ errorFWDATA2;
	पूर्ण
	/* load the first chunk */
	अगर (request_firmware(&dev->fw_data->fw,
			     FIRMWARE_खाता_NAME, &dev->udev->dev)) अणु
		dev_err(&पूर्णांकerface->dev, "sensoray 2255 failed to get firmware\n");
		जाओ errorREQFW;
	पूर्ण
	/* check the firmware is valid */
	fw_size = dev->fw_data->fw->size;
	pdata = (__le32 *) &dev->fw_data->fw->data[fw_size - 8];

	अगर (*pdata != S2255_FW_MARKER) अणु
		dev_err(&पूर्णांकerface->dev, "Firmware invalid.\n");
		retval = -ENODEV;
		जाओ errorFWMARKER;
	पूर्ण अन्यथा अणु
		/* make sure firmware is the latest */
		__le32 *pRel;
		pRel = (__le32 *) &dev->fw_data->fw->data[fw_size - 4];
		pr_info("s2255 dsp fw version %x\n", le32_to_cpu(*pRel));
		dev->dsp_fw_ver = le32_to_cpu(*pRel);
		अगर (dev->dsp_fw_ver < S2255_CUR_DSP_FWVER)
			pr_info("s2255: f2255usb.bin out of date.\n");
		अगर (dev->pid == 0x2257 &&
				dev->dsp_fw_ver < S2255_MIN_DSP_COLORFILTER)
			pr_warn("2257 needs firmware %d or above.\n",
				S2255_MIN_DSP_COLORFILTER);
	पूर्ण
	usb_reset_device(dev->udev);
	/* load 2255 board specअगरic */
	retval = s2255_board_init(dev);
	अगर (retval)
		जाओ errorBOARDINIT;
	s2255_fwload_start(dev);
	/* loads v4l specअगरic */
	retval = s2255_probe_v4l(dev);
	अगर (retval)
		जाओ errorBOARDINIT;
	dev_info(&पूर्णांकerface->dev, "Sensoray 2255 detected\n");
	वापस 0;
errorBOARDINIT:
	s2255_board_shutकरोwn(dev);
errorFWMARKER:
	release_firmware(dev->fw_data->fw);
errorREQFW:
	kमुक्त(dev->fw_data->pfw_data);
errorFWDATA2:
	usb_मुक्त_urb(dev->fw_data->fw_urb);
errorFWURB:
	del_समयr_sync(&dev->समयr);
errorEP:
	usb_put_dev(dev->udev);
errorUDEV:
	kमुक्त(dev->fw_data);
	mutex_destroy(&dev->lock);
errorFWDATA1:
	kमुक्त(dev->cmdbuf);
	kमुक्त(dev);
	pr_warn("Sensoray 2255 driver load failed: 0x%x\n", retval);
	वापस retval;
पूर्ण

/* disconnect routine. when board is हटाओd physically or with rmmod */
अटल व्योम s2255_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा s2255_dev *dev = to_s2255_dev(usb_get_पूर्णांकfdata(पूर्णांकerface));
	पूर्णांक i;
	पूर्णांक channels = atomic_पढ़ो(&dev->num_channels);
	mutex_lock(&dev->lock);
	v4l2_device_disconnect(&dev->v4l2_dev);
	mutex_unlock(&dev->lock);
	/*see comments in the uvc_driver.c usb disconnect function */
	atomic_inc(&dev->num_channels);
	/* unरेजिस्टर each video device. */
	क्रम (i = 0; i < channels; i++)
		video_unरेजिस्टर_device(&dev->vc[i].vdev);
	/* wake up any of our समयrs */
	atomic_set(&dev->fw_data->fw_state, S2255_FW_DISCONNECTING);
	wake_up(&dev->fw_data->रुको_fw);
	क्रम (i = 0; i < MAX_CHANNELS; i++) अणु
		dev->vc[i].seपंचांगode_पढ़ोy = 1;
		wake_up(&dev->vc[i].रुको_seपंचांगode);
		dev->vc[i].vidstatus_पढ़ोy = 1;
		wake_up(&dev->vc[i].रुको_vidstatus);
	पूर्ण
	अगर (atomic_dec_and_test(&dev->num_channels))
		s2255_destroy(dev);
	dev_info(&पूर्णांकerface->dev, "%s\n", __func__);
पूर्ण

अटल काष्ठा usb_driver s2255_driver = अणु
	.name = S2255_DRIVER_NAME,
	.probe = s2255_probe,
	.disconnect = s2255_disconnect,
	.id_table = s2255_table,
पूर्ण;

module_usb_driver(s2255_driver);

MODULE_DESCRIPTION("Sensoray 2255 Video for Linux driver");
MODULE_AUTHOR("Dean Anderson (Sensoray Company Inc.)");
MODULE_LICENSE("GPL");
MODULE_VERSION(S2255_VERSION);
MODULE_FIRMWARE(FIRMWARE_खाता_NAME);
