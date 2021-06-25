<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* (C) 1999-2003 Nemosoft Unv.
   (C) 2004-2006 Luc Saillard (luc@saillard.org)

   NOTE: this version of pwc is an unofficial (modअगरied) release of pwc & pcwx
   driver and thus may have bugs that are not present in the original version.
   Please send bug reports and support requests to <luc@saillard.org>.
   The decompression routines have been implemented by reverse-engineering the
   Nemosoft binary pwcx module. Caveat emptor.

*/

#अगर_अघोषित PWC_H
#घोषणा PWC_H

#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#अगर_घोषित CONFIG_USB_PWC_INPUT_EVDEV
#समावेश <linux/input.h>
#पूर्ण_अगर
#समावेश "pwc-dec1.h"
#समावेश "pwc-dec23.h"

/* Version block */
#घोषणा PWC_VERSION	"10.0.15"
#घोषणा PWC_NAME	"pwc"
#घोषणा PFX		PWC_NAME ": "


/* Trace certain actions in the driver */
#घोषणा PWC_DEBUG_LEVEL_MODULE	BIT(0)
#घोषणा PWC_DEBUG_LEVEL_PROBE	BIT(1)
#घोषणा PWC_DEBUG_LEVEL_OPEN	BIT(2)
#घोषणा PWC_DEBUG_LEVEL_READ	BIT(3)
#घोषणा PWC_DEBUG_LEVEL_MEMORY	BIT(4)
#घोषणा PWC_DEBUG_LEVEL_FLOW	BIT(5)
#घोषणा PWC_DEBUG_LEVEL_SIZE	BIT(6)
#घोषणा PWC_DEBUG_LEVEL_IOCTL	BIT(7)
#घोषणा PWC_DEBUG_LEVEL_TRACE	BIT(8)

#घोषणा PWC_DEBUG_MODULE(fmt, args...) PWC_DEBUG(MODULE, fmt, ##args)
#घोषणा PWC_DEBUG_PROBE(fmt, args...) PWC_DEBUG(PROBE, fmt, ##args)
#घोषणा PWC_DEBUG_OPEN(fmt, args...) PWC_DEBUG(OPEN, fmt, ##args)
#घोषणा PWC_DEBUG_READ(fmt, args...) PWC_DEBUG(READ, fmt, ##args)
#घोषणा PWC_DEBUG_MEMORY(fmt, args...) PWC_DEBUG(MEMORY, fmt, ##args)
#घोषणा PWC_DEBUG_FLOW(fmt, args...) PWC_DEBUG(FLOW, fmt, ##args)
#घोषणा PWC_DEBUG_SIZE(fmt, args...) PWC_DEBUG(SIZE, fmt, ##args)
#घोषणा PWC_DEBUG_IOCTL(fmt, args...) PWC_DEBUG(IOCTL, fmt, ##args)
#घोषणा PWC_DEBUG_TRACE(fmt, args...) PWC_DEBUG(TRACE, fmt, ##args)


#अगर_घोषित CONFIG_USB_PWC_DEBUG

#घोषणा PWC_DEBUG_LEVEL	(PWC_DEBUG_LEVEL_MODULE)

#घोषणा PWC_DEBUG(level, fmt, args...) करो अणु\
	अगर ((PWC_DEBUG_LEVEL_ ##level) & pwc_trace) \
		prपूर्णांकk(KERN_DEBUG PFX fmt, ##args); \
	पूर्ण जबतक (0)

#घोषणा PWC_ERROR(fmt, args...) prपूर्णांकk(KERN_ERR PFX fmt, ##args)
#घोषणा PWC_WARNING(fmt, args...) prपूर्णांकk(KERN_WARNING PFX fmt, ##args)
#घोषणा PWC_INFO(fmt, args...) prपूर्णांकk(KERN_INFO PFX fmt, ##args)
#घोषणा PWC_TRACE(fmt, args...) PWC_DEBUG(TRACE, fmt, ##args)

#अन्यथा /* अगर ! CONFIG_USB_PWC_DEBUG */

#घोषणा PWC_ERROR(fmt, args...) prपूर्णांकk(KERN_ERR PFX fmt, ##args)
#घोषणा PWC_WARNING(fmt, args...) prपूर्णांकk(KERN_WARNING PFX fmt, ##args)
#घोषणा PWC_INFO(fmt, args...) prपूर्णांकk(KERN_INFO PFX fmt, ##args)
#घोषणा PWC_TRACE(fmt, args...) करो अणु पूर्ण जबतक(0)
#घोषणा PWC_DEBUG(level, fmt, args...) करो अणु पूर्ण जबतक(0)

#घोषणा pwc_trace 0

#पूर्ण_अगर

/* Defines क्रम ToUCam cameras */
#घोषणा TOUCAM_HEADER_SIZE		8
#घोषणा TOUCAM_TRAILER_SIZE		4

#घोषणा FEATURE_MOTOR_PANTILT		0x0001
#घोषणा FEATURE_CODEC1			0x0002
#घोषणा FEATURE_CODEC2			0x0004

#घोषणा MAX_WIDTH		640
#घोषणा MAX_HEIGHT		480

/* Ignore errors in the first N frames, to allow क्रम startup delays */
#घोषणा FRAME_LOWMARK 5

/* Size and number of buffers क्रम the ISO pipe. */
#घोषणा MAX_ISO_BUFS		3
#घोषणा ISO_FRAMES_PER_DESC	10
#घोषणा ISO_MAX_FRAME_SIZE	960
#घोषणा ISO_BUFFER_SIZE		(ISO_FRAMES_PER_DESC * ISO_MAX_FRAME_SIZE)

/* Maximum size after decompression is 640x480 YUV data, 1.5 * 640 * 480 */
#घोषणा PWC_FRAME_SIZE		(460800 + TOUCAM_HEADER_SIZE + TOUCAM_TRAILER_SIZE)

/* Absolute minimum and maximum number of buffers available क्रम mmap() */
#घोषणा MIN_FRAMES		2
#घोषणा MAX_FRAMES		16

/* Some macros to quickly find the type of a webcam */
#घोषणा DEVICE_USE_CODEC1(x) ((x)<675)
#घोषणा DEVICE_USE_CODEC2(x) ((x)>=675 && (x)<700)
#घोषणा DEVICE_USE_CODEC3(x) ((x)>=700)
#घोषणा DEVICE_USE_CODEC23(x) ((x)>=675)

/* Request types: video */
#घोषणा SET_LUM_CTL			0x01
#घोषणा GET_LUM_CTL			0x02
#घोषणा SET_CHROM_CTL			0x03
#घोषणा GET_CHROM_CTL			0x04
#घोषणा SET_STATUS_CTL			0x05
#घोषणा GET_STATUS_CTL			0x06
#घोषणा SET_EP_STREAM_CTL		0x07
#घोषणा GET_EP_STREAM_CTL		0x08
#घोषणा GET_XX_CTL			0x09
#घोषणा SET_XX_CTL			0x0A
#घोषणा GET_XY_CTL			0x0B
#घोषणा SET_XY_CTL			0x0C
#घोषणा SET_MPT_CTL			0x0D
#घोषणा GET_MPT_CTL			0x0E

/* Selectors क्रम the Luminance controls [GS]ET_LUM_CTL */
#घोषणा AGC_MODE_FORMATTER			0x2000
#घोषणा PRESET_AGC_FORMATTER			0x2100
#घोषणा SHUTTER_MODE_FORMATTER			0x2200
#घोषणा PRESET_SHUTTER_FORMATTER		0x2300
#घोषणा PRESET_CONTOUR_FORMATTER		0x2400
#घोषणा AUTO_CONTOUR_FORMATTER			0x2500
#घोषणा BACK_LIGHT_COMPENSATION_FORMATTER	0x2600
#घोषणा CONTRAST_FORMATTER			0x2700
#घोषणा DYNAMIC_NOISE_CONTROL_FORMATTER		0x2800
#घोषणा FLICKERLESS_MODE_FORMATTER		0x2900
#घोषणा AE_CONTROL_SPEED			0x2A00
#घोषणा BRIGHTNESS_FORMATTER			0x2B00
#घोषणा GAMMA_FORMATTER				0x2C00

/* Selectors क्रम the Chrominance controls [GS]ET_CHROM_CTL */
#घोषणा WB_MODE_FORMATTER			0x1000
#घोषणा AWB_CONTROL_SPEED_FORMATTER		0x1100
#घोषणा AWB_CONTROL_DELAY_FORMATTER		0x1200
#घोषणा PRESET_MANUAL_RED_GAIN_FORMATTER	0x1300
#घोषणा PRESET_MANUAL_BLUE_GAIN_FORMATTER	0x1400
#घोषणा COLOUR_MODE_FORMATTER			0x1500
#घोषणा SATURATION_MODE_FORMATTER1		0x1600
#घोषणा SATURATION_MODE_FORMATTER2		0x1700

/* Selectors क्रम the Status controls [GS]ET_STATUS_CTL */
#घोषणा SAVE_USER_DEFAULTS_FORMATTER		0x0200
#घोषणा RESTORE_USER_DEFAULTS_FORMATTER		0x0300
#घोषणा RESTORE_FACTORY_DEFAULTS_FORMATTER	0x0400
#घोषणा READ_AGC_FORMATTER			0x0500
#घोषणा READ_SHUTTER_FORMATTER			0x0600
#घोषणा READ_RED_GAIN_FORMATTER			0x0700
#घोषणा READ_BLUE_GAIN_FORMATTER		0x0800

/* Formatters क्रम the motorized pan & tilt [GS]ET_MPT_CTL */
#घोषणा PT_RELATIVE_CONTROL_FORMATTER		0x01
#घोषणा PT_RESET_CONTROL_FORMATTER		0x02
#घोषणा PT_STATUS_FORMATTER			0x03

/* Enumeration of image sizes */
#घोषणा PSZ_SQCIF	0x00
#घोषणा PSZ_QSIF	0x01
#घोषणा PSZ_QCIF	0x02
#घोषणा PSZ_SIF		0x03
#घोषणा PSZ_CIF		0x04
#घोषणा PSZ_VGA		0x05
#घोषणा PSZ_MAX		6

काष्ठा pwc_raw_frame अणु
	__le16 type;		/* type of the webcam */
	__le16 vbandlength;	/* Size of 4 lines compressed (used by the
				   decompressor) */
	__u8   cmd[4];		/* the four byte of the command (in हाल of
				   nala, only the first 3 bytes is filled) */
	__u8   rawframe[];	/* frame_size = H / 4 * vbandlength */
पूर्ण __packed;

/* पूर्णांकermediate buffers with raw data from the USB cam */
काष्ठा pwc_frame_buf
अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
	व्योम *data;
	पूर्णांक filled;		/* number of bytes filled */
पूर्ण;

काष्ठा pwc_device
अणु
	काष्ठा video_device vdev;
	काष्ठा v4l2_device v4l2_dev;

	/* videobuf2 queue and queued buffers list */
	काष्ठा vb2_queue vb_queue;
	काष्ठा list_head queued_bufs;
	spinlock_t queued_bufs_lock; /* Protects queued_bufs */

	/* If taking both locks vb_queue_lock must always be locked first! */
	काष्ठा mutex v4l2_lock;      /* Protects everything अन्यथा */
	काष्ठा mutex vb_queue_lock;  /* Protects vb_queue and capt_file */

	/* Poपूर्णांकer to our usb_device, will be शून्य after unplug */
	काष्ठा usb_device *udev; /* Both mutexes most be hold when setting! */

	/* type of cam (645, 646, 675, 680, 690, 720, 730, 740, 750) */
	पूर्णांक type;
	पूर्णांक release;		/* release number */
	पूर्णांक features;		/* feature bits */

	/*** Video data ***/
	पूर्णांक vendpoपूर्णांक;		/* video isoc endpoपूर्णांक */
	पूर्णांक vcपूर्णांकerface;	/* video control पूर्णांकerface */
	पूर्णांक valternate;		/* alternate पूर्णांकerface needed */
	पूर्णांक vframes;		/* frames-per-second */
	पूर्णांक pixfmt;		/* pixelक्रमmat: V4L2_PIX_FMT_YUV420 or _PWCX */
	पूर्णांक vframe_count;	/* received frames */
	पूर्णांक vmax_packet_size;	/* USB maxpacket size */
	पूर्णांक vlast_packet_size;	/* क्रम frame synchronisation */
	पूर्णांक visoc_errors;	/* number of contiguous ISOC errors */
	पूर्णांक vbandlength;	/* compressed band length; 0 is uncompressed */
	अक्षर vsync;		/* used by isoc handler */
	अक्षर vmirror;		/* क्रम ToUCaM series */
	अक्षर घातer_save;	/* Do घातersaving क्रम this cam */

	अचिन्हित अक्षर cmd_buf[13];
	अचिन्हित अक्षर *ctrl_buf;

	काष्ठा urb *urbs[MAX_ISO_BUFS];

	/*
	 * Frame currently being filled, this only माला_लो touched by the
	 * isoc urb complete handler, and by stream start / stop since
	 * start / stop touch it beक्रमe / after starting / समाप्तing the urbs
	 * no locking is needed around this
	 */
	काष्ठा pwc_frame_buf *fill_buf;

	पूर्णांक frame_header_size, frame_trailer_size;
	पूर्णांक frame_size;
	पूर्णांक frame_total_size;	/* including header & trailer */
	पूर्णांक drop_frames;

	जोड़ अणु	/* निजी data क्रम decompression engine */
		काष्ठा pwc_dec1_निजी dec1;
		काष्ठा pwc_dec23_निजी dec23;
	पूर्ण;

	/*
	 * We have an 'image' and a 'view', where 'image' is the fixed-size img
	 * as delivered by the camera, and 'view' is the size requested by the
	 * program. The camera image is centered in this viewport, laced with
	 * a gray or black border. view_min <= image <= view <= view_max;
	 */
	पूर्णांक image_mask;				/* supported sizes */
	पूर्णांक width, height;			/* current resolution */

#अगर_घोषित CONFIG_USB_PWC_INPUT_EVDEV
	काष्ठा input_dev *button_dev;	/* webcam snapshot button input */
	अक्षर button_phys[64];
#पूर्ण_अगर

	/* controls */
	काष्ठा v4l2_ctrl_handler	ctrl_handler;
	u16				saturation_fmt;
	काष्ठा v4l2_ctrl		*brightness;
	काष्ठा v4l2_ctrl		*contrast;
	काष्ठा v4l2_ctrl		*saturation;
	काष्ठा v4l2_ctrl		*gamma;
	काष्ठा अणु
		/* awb / red-blue balance cluster */
		काष्ठा v4l2_ctrl	*स्वतः_white_balance;
		काष्ठा v4l2_ctrl	*red_balance;
		काष्ठा v4l2_ctrl	*blue_balance;
		/* usb ctrl transfers are slow, so we cache things */
		पूर्णांक			color_bal_valid;
		अचिन्हित दीर्घ		last_color_bal_update; /* In jअगरfies */
		s32			last_red_balance;
		s32			last_blue_balance;
	पूर्ण;
	काष्ठा अणु
		/* स्वतःgain / gain cluster */
		काष्ठा v4l2_ctrl	*स्वतःgain;
		काष्ठा v4l2_ctrl	*gain;
		पूर्णांक			gain_valid;
		अचिन्हित दीर्घ		last_gain_update; /* In jअगरfies */
		s32			last_gain;
	पूर्ण;
	काष्ठा अणु
		/* exposure_स्वतः / exposure cluster */
		काष्ठा v4l2_ctrl	*exposure_स्वतः;
		काष्ठा v4l2_ctrl	*exposure;
		पूर्णांक			exposure_valid;
		अचिन्हित दीर्घ		last_exposure_update; /* In jअगरfies */
		s32			last_exposure;
	पूर्ण;
	काष्ठा v4l2_ctrl		*colorfx;
	काष्ठा अणु
		/* स्वतःcontour/contour cluster */
		काष्ठा v4l2_ctrl	*स्वतःcontour;
		काष्ठा v4l2_ctrl	*contour;
	पूर्ण;
	काष्ठा v4l2_ctrl		*backlight;
	काष्ठा v4l2_ctrl		*flicker;
	काष्ठा v4l2_ctrl		*noise_reduction;
	काष्ठा v4l2_ctrl		*save_user;
	काष्ठा v4l2_ctrl		*restore_user;
	काष्ठा v4l2_ctrl		*restore_factory;
	काष्ठा v4l2_ctrl		*awb_speed;
	काष्ठा v4l2_ctrl		*awb_delay;
	काष्ठा अणु
		/* motor control cluster */
		काष्ठा v4l2_ctrl	*motor_pan;
		काष्ठा v4l2_ctrl	*motor_tilt;
		काष्ठा v4l2_ctrl	*motor_pan_reset;
		काष्ठा v4l2_ctrl	*motor_tilt_reset;
	पूर्ण;
	/* CODEC3 models have both gain and exposure controlled by स्वतःgain */
	काष्ठा v4l2_ctrl		*स्वतःgain_expo_cluster[3];
पूर्ण;

/* Global variables */
#अगर_घोषित CONFIG_USB_PWC_DEBUG
बाह्य पूर्णांक pwc_trace;
#पूर्ण_अगर

/** Functions in pwc-misc.c */
/* sizes in pixels */
बाह्य स्थिर पूर्णांक pwc_image_sizes[PSZ_MAX][2];

पूर्णांक pwc_get_size(काष्ठा pwc_device *pdev, पूर्णांक width, पूर्णांक height);
व्योम pwc_स्थिरruct(काष्ठा pwc_device *pdev);

/** Functions in pwc-ctrl.c */
/* Request a certain video mode. Returns < 0 अगर not possible */
बाह्य पूर्णांक pwc_set_video_mode(काष्ठा pwc_device *pdev, पूर्णांक width, पूर्णांक height,
	पूर्णांक pixfmt, पूर्णांक frames, पूर्णांक *compression, पूर्णांक send_to_cam);
बाह्य अचिन्हित पूर्णांक pwc_get_fps(काष्ठा pwc_device *pdev, अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक size);
बाह्य पूर्णांक pwc_set_leds(काष्ठा pwc_device *pdev, पूर्णांक on_value, पूर्णांक off_value);
बाह्य पूर्णांक pwc_get_cmos_sensor(काष्ठा pwc_device *pdev, पूर्णांक *sensor);
बाह्य पूर्णांक send_control_msg(काष्ठा pwc_device *pdev,
			    u8 request, u16 value, व्योम *buf, पूर्णांक buflen);

/* Control get / set helpers */
पूर्णांक pwc_get_u8_ctrl(काष्ठा pwc_device *pdev, u8 request, u16 value, पूर्णांक *data);
पूर्णांक pwc_set_u8_ctrl(काष्ठा pwc_device *pdev, u8 request, u16 value, u8 data);
पूर्णांक pwc_get_s8_ctrl(काष्ठा pwc_device *pdev, u8 request, u16 value, पूर्णांक *data);
#घोषणा pwc_set_s8_ctrl pwc_set_u8_ctrl
पूर्णांक pwc_get_u16_ctrl(काष्ठा pwc_device *pdev, u8 request, u16 value, पूर्णांक *dat);
पूर्णांक pwc_set_u16_ctrl(काष्ठा pwc_device *pdev, u8 request, u16 value, u16 data);
पूर्णांक pwc_button_ctrl(काष्ठा pwc_device *pdev, u16 value);
पूर्णांक pwc_init_controls(काष्ठा pwc_device *pdev);

/* Power करोwn or up the camera; not supported by all models */
बाह्य व्योम pwc_camera_घातer(काष्ठा pwc_device *pdev, पूर्णांक घातer);

बाह्य स्थिर काष्ठा v4l2_ioctl_ops pwc_ioctl_ops;

/** pwc-uncompress.c */
/* Expand frame to image, possibly including decompression. Uses पढ़ो_frame and fill_image */
पूर्णांक pwc_decompress(काष्ठा pwc_device *pdev, काष्ठा pwc_frame_buf *fbuf);

#पूर्ण_अगर
