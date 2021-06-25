<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/****************************************************************************
 *
 *  Filename: cpia2.h
 *
 *  Copyright 2001, STMicrolectronics, Inc.
 *
 *  Contact:  steve.miller@st.com
 *
 *  Description:
 *     This is a USB driver क्रम CPiA2 based video cameras.
 *
 *     This driver is modelled on the cpia usb driver by
 *     Jochen Sअक्षरrlach and Johannes Erdfeldt.
 *
 ****************************************************************************/

#अगर_अघोषित __CPIA2_H__
#घोषणा __CPIA2_H__

#समावेश <linux/videodev2.h>
#समावेश <linux/usb.h>
#समावेश <linux/poll.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

#समावेश "cpia2_registers.h"

/* define क्रम verbose debug output */
//#घोषणा _CPIA2_DEBUG_

/***
 * Image defines
 ***/

/*  Misc स्थिरants */
#घोषणा ALLOW_CORRUPT 0		/* Causes collater to discard checksum */

/* USB Transfer mode */
#घोषणा XFER_ISOC 0
#घोषणा XFER_BULK 1

/* USB Alternates */
#घोषणा USBIF_CMDONLY 0
#घोषणा USBIF_BULK 1
#घोषणा USBIF_ISO_1 2	/*  128 bytes/ms */
#घोषणा USBIF_ISO_2 3	/*  384 bytes/ms */
#घोषणा USBIF_ISO_3 4	/*  640 bytes/ms */
#घोषणा USBIF_ISO_4 5	/*  768 bytes/ms */
#घोषणा USBIF_ISO_5 6	/*  896 bytes/ms */
#घोषणा USBIF_ISO_6 7	/* 1023 bytes/ms */

/* Flicker Modes */
#घोषणा NEVER_FLICKER   0
#घोषणा FLICKER_60      60
#घोषणा FLICKER_50      50

/* Debug flags */
#घोषणा DEBUG_NONE          0
#घोषणा DEBUG_REG           0x00000001
#घोषणा DEBUG_DUMP_PATCH    0x00000002
#घोषणा DEBUG_DUMP_REGS     0x00000004

/***
 * Video frame sizes
 ***/
क्रमागत अणु
	VIDEOSIZE_VGA = 0,	/* 640x480 */
	VIDEOSIZE_CIF,		/* 352x288 */
	VIDEOSIZE_QVGA,		/* 320x240 */
	VIDEOSIZE_QCIF,		/* 176x144 */
	VIDEOSIZE_288_216,
	VIDEOSIZE_256_192,
	VIDEOSIZE_224_168,
	VIDEOSIZE_192_144,
पूर्ण;

#घोषणा STV_IMAGE_CIF_ROWS    288
#घोषणा STV_IMAGE_CIF_COLS    352

#घोषणा STV_IMAGE_QCIF_ROWS   144
#घोषणा STV_IMAGE_QCIF_COLS   176

#घोषणा STV_IMAGE_VGA_ROWS    480
#घोषणा STV_IMAGE_VGA_COLS    640

#घोषणा STV_IMAGE_QVGA_ROWS   240
#घोषणा STV_IMAGE_QVGA_COLS   320

#घोषणा JPEG_MARKER_COM (1<<6)	/* Comment segment */

/***
 * Enums
 ***/
/* Sensor types available with cpia2 asics */
क्रमागत sensors अणु
	CPIA2_SENSOR_410,
	CPIA2_SENSOR_500
पूर्ण;

/* Asic types available in the CPiA2 architecture */
#घोषणा  CPIA2_ASIC_672 0x67

/* Device types (stv672, stv676, etc) */
#घोषणा  DEVICE_STV_672   0x0001
#घोषणा  DEVICE_STV_676   0x0002

क्रमागत frame_status अणु
	FRAME_EMPTY,
	FRAME_READING,		/* In the process of being grabbed पूर्णांकo */
	FRAME_READY,		/* Ready to be पढ़ो */
	FRAME_ERROR,
पूर्ण;

/***
 * Register access (क्रम USB request byte)
 ***/
क्रमागत अणु
	CAMERAACCESS_SYSTEM = 0,
	CAMERAACCESS_VC,
	CAMERAACCESS_VP,
	CAMERAACCESS_IDATA
पूर्ण;

#घोषणा CAMERAACCESS_TYPE_BLOCK    0x00
#घोषणा CAMERAACCESS_TYPE_RANDOM   0x04
#घोषणा CAMERAACCESS_TYPE_MASK     0x08
#घोषणा CAMERAACCESS_TYPE_REPEAT   0x0C

#घोषणा TRANSFER_READ 0
#घोषणा TRANSFER_WRITE 1

#घोषणा DEFAULT_ALT   USBIF_ISO_6
#घोषणा DEFAULT_BRIGHTNESS 0x46
#घोषणा DEFAULT_CONTRAST 0x93
#घोषणा DEFAULT_SATURATION 0x7f

/* Power state */
#घोषणा HI_POWER_MODE CPIA2_SYSTEM_CONTROL_HIGH_POWER
#घोषणा LO_POWER_MODE CPIA2_SYSTEM_CONTROL_LOW_POWER


/********
 * Commands
 *******/
क्रमागत अणु
	CPIA2_CMD_NONE = 0,
	CPIA2_CMD_GET_VERSION,
	CPIA2_CMD_GET_PNP_ID,
	CPIA2_CMD_GET_ASIC_TYPE,
	CPIA2_CMD_GET_SENSOR,
	CPIA2_CMD_GET_VP_DEVICE,
	CPIA2_CMD_GET_VP_BRIGHTNESS,
	CPIA2_CMD_SET_VP_BRIGHTNESS,
	CPIA2_CMD_GET_CONTRAST,
	CPIA2_CMD_SET_CONTRAST,
	CPIA2_CMD_GET_VP_SATURATION,
	CPIA2_CMD_SET_VP_SATURATION,
	CPIA2_CMD_GET_VP_GPIO_सूचीECTION,
	CPIA2_CMD_SET_VP_GPIO_सूचीECTION,
	CPIA2_CMD_GET_VP_GPIO_DATA,
	CPIA2_CMD_SET_VP_GPIO_DATA,
	CPIA2_CMD_GET_VC_MP_GPIO_सूचीECTION,
	CPIA2_CMD_SET_VC_MP_GPIO_सूचीECTION,
	CPIA2_CMD_GET_VC_MP_GPIO_DATA,
	CPIA2_CMD_SET_VC_MP_GPIO_DATA,
	CPIA2_CMD_ENABLE_PACKET_CTRL,
	CPIA2_CMD_GET_FLICKER_MODES,
	CPIA2_CMD_SET_FLICKER_MODES,
	CPIA2_CMD_RESET_FIFO,	/* clear fअगरo and enable stream block */
	CPIA2_CMD_SET_HI_POWER,
	CPIA2_CMD_SET_LOW_POWER,
	CPIA2_CMD_CLEAR_V2W_ERR,
	CPIA2_CMD_SET_USER_MODE,
	CPIA2_CMD_GET_USER_MODE,
	CPIA2_CMD_FRAMERATE_REQ,
	CPIA2_CMD_SET_COMPRESSION_STATE,
	CPIA2_CMD_GET_WAKEUP,
	CPIA2_CMD_SET_WAKEUP,
	CPIA2_CMD_GET_PW_CONTROL,
	CPIA2_CMD_SET_PW_CONTROL,
	CPIA2_CMD_GET_SYSTEM_CTRL,
	CPIA2_CMD_SET_SYSTEM_CTRL,
	CPIA2_CMD_GET_VP_SYSTEM_STATE,
	CPIA2_CMD_GET_VP_SYSTEM_CTRL,
	CPIA2_CMD_SET_VP_SYSTEM_CTRL,
	CPIA2_CMD_GET_VP_EXP_MODES,
	CPIA2_CMD_SET_VP_EXP_MODES,
	CPIA2_CMD_GET_DEVICE_CONFIG,
	CPIA2_CMD_SET_DEVICE_CONFIG,
	CPIA2_CMD_SET_SERIAL_ADDR,
	CPIA2_CMD_SET_SENSOR_CR1,
	CPIA2_CMD_GET_VC_CONTROL,
	CPIA2_CMD_SET_VC_CONTROL,
	CPIA2_CMD_SET_TARGET_KB,
	CPIA2_CMD_SET_DEF_JPEG_OPT,
	CPIA2_CMD_REHASH_VP4,
	CPIA2_CMD_GET_USER_EFFECTS,
	CPIA2_CMD_SET_USER_EFFECTS
पूर्ण;

क्रमागत user_cmd अणु
	COMMAND_NONE = 0x00000001,
	COMMAND_SET_FPS = 0x00000002,
	COMMAND_SET_COLOR_PARAMS = 0x00000004,
	COMMAND_GET_COLOR_PARAMS = 0x00000008,
	COMMAND_SET_FORMAT = 0x00000010,	/* size, etc */
	COMMAND_SET_FLICKER = 0x00000020
पूर्ण;

/***
 * Some defines specअगरic to the 676 chip
 ***/
#घोषणा CAMACC_CIF      0x01
#घोषणा CAMACC_VGA      0x02
#घोषणा CAMACC_QCIF     0x04
#घोषणा CAMACC_QVGA     0x08


काष्ठा cpia2_रेजिस्टर अणु
	u8 index;
	u8 value;
पूर्ण;

काष्ठा cpia2_reg_mask अणु
	u8 index;
	u8 and_mask;
	u8 or_mask;
	u8 fill;
पूर्ण;

काष्ठा cpia2_command अणु
	u32 command;
	u8 req_mode;		/* (Block or अक्रमom) | रेजिस्टरBank */
	u8 reg_count;
	u8 direction;
	u8 start;
	जोड़ reg_types अणु
		काष्ठा cpia2_रेजिस्टर रेजिस्टरs[32];
		काष्ठा cpia2_reg_mask masks[16];
		u8 block_data[64];
		u8 *patch_data;	/* poपूर्णांकs to function defined block */
	पूर्ण buffer;
पूर्ण;

काष्ठा camera_params अणु
	काष्ठा अणु
		u8 firmware_revision_hi; /* For प्रणाली रेजिस्टर set (bank 0) */
		u8 firmware_revision_lo;
		u8 asic_id;	/* Video Compressor set (bank 1) */
		u8 asic_rev;
		u8 vp_device_hi;	/* Video Processor set (bank 2) */
		u8 vp_device_lo;
		u8 sensor_flags;
		u8 sensor_rev;
	पूर्ण version;

	काष्ठा अणु
		u32 device_type;     /* क्रमागतerated from venकरोr/product ids.
				      * Currently, either STV_672 or STV_676 */
		u16 venकरोr;
		u16 product;
		u16 device_revision;
	पूर्ण pnp_id;

	काष्ठा अणु
		u8 brightness;	/* CPIA2_VP_EXPOSURE_TARGET */
		u8 contrast;	/* Note: this is CPIA2_VP_YRANGE */
		u8 saturation;	/*  CPIA2_VP_SATURATION */
	पूर्ण color_params;

	काष्ठा अणु
		u8 cam_रेजिस्टर;
		u8 flicker_mode_req;	/* 1 अगर flicker on, अन्यथा never flicker */
	पूर्ण flicker_control;

	काष्ठा अणु
		u8 jpeg_options;
		u8 creep_period;
		u8 user_squeeze;
		u8 inhibit_htables;
	पूर्ण compression;

	काष्ठा अणु
		u8 ohsize;	/* output image size */
		u8 ovsize;
		u8 hcrop;	/* cropping start_pos/4 */
		u8 vcrop;
		u8 hphase;	/* scaling रेजिस्टरs */
		u8 vphase;
		u8 hispan;
		u8 vispan;
		u8 hicrop;
		u8 vicrop;
		u8 hअगरraction;
		u8 vअगरraction;
	पूर्ण image_size;

	काष्ठा अणु
		पूर्णांक width;	/* actual winकरोw width */
		पूर्णांक height;	/* actual winकरोw height */
	पूर्ण roi;

	काष्ठा अणु
		u8 video_mode;
		u8 frame_rate;
		u8 video_size;	/* Not a रेजिस्टर, just a convenience क्रम cropped sizes */
		u8 gpio_direction;
		u8 gpio_data;
		u8 प्रणाली_ctrl;
		u8 प्रणाली_state;
		u8 lowlight_boost;	/* Bool: 0 = off, 1 = on */
		u8 device_config;
		u8 exposure_modes;
		u8 user_effects;
	पूर्ण vp_params;

	काष्ठा अणु
		u8 pw_control;
		u8 wakeup;
		u8 vc_control;
		u8 vc_mp_direction;
		u8 vc_mp_data;
		u8 quality;
	पूर्ण vc_params;

	काष्ठा अणु
		u8 घातer_mode;
		u8 प्रणाली_ctrl;
		u8 stream_mode;	/* This is the current alternate क्रम usb drivers */
		u8 allow_corrupt;
	पूर्ण camera_state;
पूर्ण;

#घोषणा NUM_SBUF    2

काष्ठा cpia2_sbuf अणु
	अक्षर *data;
	काष्ठा urb *urb;
पूर्ण;

काष्ठा framebuf अणु
	u64 ts;
	अचिन्हित दीर्घ seq;
	पूर्णांक num;
	पूर्णांक length;
	पूर्णांक max_length;
	अस्थिर क्रमागत frame_status status;
	u8 *data;
	काष्ठा framebuf *next;
पूर्ण;

काष्ठा camera_data अणु
	/* locks */
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा mutex v4l2_lock;	/* serialize file operations */
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा अणु
		/* Lights control cluster */
		काष्ठा v4l2_ctrl *top_light;
		काष्ठा v4l2_ctrl *bottom_light;
	पूर्ण;
	काष्ठा v4l2_ctrl *usb_alt;

	/* camera status */
	पूर्णांक first_image_seen;
	क्रमागत sensors sensor_type;
	u8 flush;
	काष्ठा v4l2_fh *stream_fh;
	u8 mmapped;
	पूर्णांक streaming;		/* 0 = no, 1 = yes */
	पूर्णांक xfer_mode;		/* XFER_BULK or XFER_ISOC */
	काष्ठा camera_params params;	/* camera settings */

	/* v4l */
	पूर्णांक video_size;			/* VIDEO_SIZE_ */
	काष्ठा video_device vdev;	/* v4l videodev */
	u32 width;
	u32 height;			/* Its size */
	__u32 pixelक्रमmat;       /* Format fourcc      */

	/* USB */
	काष्ठा usb_device *dev;
	अचिन्हित अक्षर अगरace;
	अचिन्हित पूर्णांक cur_alt;
	अचिन्हित पूर्णांक old_alt;
	काष्ठा cpia2_sbuf sbuf[NUM_SBUF];	/* Double buffering */

	रुको_queue_head_t wq_stream;

	/* Buffering */
	u32 frame_size;
	पूर्णांक num_frames;
	अचिन्हित दीर्घ frame_count;
	u8 *frame_buffer;	/* frame buffer data */
	काष्ठा framebuf *buffers;
	काष्ठा framebuf * अस्थिर curbuff;
	काष्ठा framebuf *workbuff;

	/* MJPEG Extension */
	पूर्णांक APPn;		/* Number of APP segment to be written, must be 0..15 */
	पूर्णांक APP_len;		/* Length of data in JPEG APPn segment */
	अक्षर APP_data[60];	/* Data in the JPEG APPn segment. */

	पूर्णांक COM_len;		/* Length of data in JPEG COM segment */
	अक्षर COM_data[60];	/* Data in JPEG COM segment */
पूर्ण;

/* v4l */
पूर्णांक cpia2_रेजिस्टर_camera(काष्ठा camera_data *cam);
व्योम cpia2_unरेजिस्टर_camera(काष्ठा camera_data *cam);
व्योम cpia2_camera_release(काष्ठा v4l2_device *v4l2_dev);

/* core */
पूर्णांक cpia2_reset_camera(काष्ठा camera_data *cam);
पूर्णांक cpia2_set_low_घातer(काष्ठा camera_data *cam);
व्योम cpia2_dbg_dump_रेजिस्टरs(काष्ठा camera_data *cam);
पूर्णांक cpia2_match_video_size(पूर्णांक width, पूर्णांक height);
व्योम cpia2_set_camera_state(काष्ठा camera_data *cam);
व्योम cpia2_save_camera_state(काष्ठा camera_data *cam);
व्योम cpia2_set_color_params(काष्ठा camera_data *cam);
व्योम cpia2_set_brightness(काष्ठा camera_data *cam, अचिन्हित अक्षर value);
व्योम cpia2_set_contrast(काष्ठा camera_data *cam, अचिन्हित अक्षर value);
व्योम cpia2_set_saturation(काष्ठा camera_data *cam, अचिन्हित अक्षर value);
पूर्णांक cpia2_set_flicker_mode(काष्ठा camera_data *cam, पूर्णांक mode);
व्योम cpia2_set_क्रमmat(काष्ठा camera_data *cam);
पूर्णांक cpia2_send_command(काष्ठा camera_data *cam, काष्ठा cpia2_command *cmd);
पूर्णांक cpia2_करो_command(काष्ठा camera_data *cam,
		     अचिन्हित पूर्णांक command,
		     अचिन्हित अक्षर direction, अचिन्हित अक्षर param);
काष्ठा camera_data *cpia2_init_camera_काष्ठा(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
पूर्णांक cpia2_init_camera(काष्ठा camera_data *cam);
पूर्णांक cpia2_allocate_buffers(काष्ठा camera_data *cam);
व्योम cpia2_मुक्त_buffers(काष्ठा camera_data *cam);
दीर्घ cpia2_पढ़ो(काष्ठा camera_data *cam,
		अक्षर __user *buf, अचिन्हित दीर्घ count, पूर्णांक noblock);
__poll_t cpia2_poll(काष्ठा camera_data *cam,
			काष्ठा file *filp, poll_table *रुको);
पूर्णांक cpia2_remap_buffer(काष्ठा camera_data *cam, काष्ठा vm_area_काष्ठा *vma);
व्योम cpia2_set_property_flip(काष्ठा camera_data *cam, पूर्णांक prop_val);
व्योम cpia2_set_property_mirror(काष्ठा camera_data *cam, पूर्णांक prop_val);
पूर्णांक cpia2_set_gpio(काष्ठा camera_data *cam, अचिन्हित अक्षर setting);
पूर्णांक cpia2_set_fps(काष्ठा camera_data *cam, पूर्णांक framerate);

/* usb */
पूर्णांक cpia2_usb_init(व्योम);
व्योम cpia2_usb_cleanup(व्योम);
पूर्णांक cpia2_usb_transfer_cmd(काष्ठा camera_data *cam, व्योम *रेजिस्टरs,
			   u8 request, u8 start, u8 count, u8 direction);
पूर्णांक cpia2_usb_stream_start(काष्ठा camera_data *cam, अचिन्हित पूर्णांक alternate);
पूर्णांक cpia2_usb_stream_stop(काष्ठा camera_data *cam);
पूर्णांक cpia2_usb_stream_छोड़ो(काष्ठा camera_data *cam);
पूर्णांक cpia2_usb_stream_resume(काष्ठा camera_data *cam);
पूर्णांक cpia2_usb_change_streaming_alternate(काष्ठा camera_data *cam,
					 अचिन्हित पूर्णांक alt);


/* ----------------------- debug functions ---------------------- */
#अगर_घोषित _CPIA2_DEBUG_
#घोषणा ALOG(lev, fmt, args...) prपूर्णांकk(lev "%s:%d %s(): " fmt, __खाता__, __LINE__, __func__, ## args)
#घोषणा LOG(fmt, args...) ALOG(KERN_INFO, fmt, ## args)
#घोषणा ERR(fmt, args...) ALOG(KERN_ERR, fmt, ## args)
#घोषणा DBG(fmt, args...) ALOG(KERN_DEBUG, fmt, ## args)
#अन्यथा
#घोषणा ALOG(fmt,args...) prपूर्णांकk(fmt,##args)
#घोषणा LOG(fmt,args...) ALOG(KERN_INFO "cpia2: "fmt,##args)
#घोषणा ERR(fmt,args...) ALOG(KERN_ERR "cpia2: "fmt,##args)
#घोषणा DBG(fmn,args...) करो अणुपूर्ण जबतक(0)
#पूर्ण_अगर
/* No function or lineno, क्रम लघुer lines */
#घोषणा KINFO(fmt, args...) prपूर्णांकk(KERN_INFO fmt,##args)

#पूर्ण_अगर
