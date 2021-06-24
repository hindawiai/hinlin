<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Hauppauge HD PVR USB driver
 *
 * Copyright (C) 2008      Janne Grunau (j@jannau.net)
 */

#समावेश <linux/usb.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/i2c/ir-kbd-i2c.h>

#घोषणा HDPVR_MAX 8
#घोषणा HDPVR_I2C_MAX_SIZE 128

/* Define these values to match your devices */
#घोषणा HD_PVR_VENDOR_ID	0x2040
#घोषणा HD_PVR_PRODUCT_ID	0x4900
#घोषणा HD_PVR_PRODUCT_ID1	0x4901
#घोषणा HD_PVR_PRODUCT_ID2	0x4902
#घोषणा HD_PVR_PRODUCT_ID4	0x4903
#घोषणा HD_PVR_PRODUCT_ID3	0x4982

#घोषणा UNSET    (-1U)

#घोषणा NUM_BUFFERS 64

#घोषणा HDPVR_FIRMWARE_VERSION		0x08
#घोषणा HDPVR_FIRMWARE_VERSION_AC3	0x0d
#घोषणा HDPVR_FIRMWARE_VERSION_0X12	0x12
#घोषणा HDPVR_FIRMWARE_VERSION_0X15	0x15
#घोषणा HDPVR_FIRMWARE_VERSION_0X1E	0x1e

/* #घोषणा HDPVR_DEBUG */

बाह्य पूर्णांक hdpvr_debug;

#घोषणा MSG_INFO	1
#घोषणा MSG_BUFFER	2

काष्ठा hdpvr_options अणु
	u8	video_std;
	u8	video_input;
	u8	audio_input;
	u8	bitrate;	/* in 100kbps */
	u8	peak_bitrate;	/* in 100kbps */
	u8	bitrate_mode;
	u8	gop_mode;
	क्रमागत v4l2_mpeg_audio_encoding	audio_codec;
	u8	brightness;
	u8	contrast;
	u8	hue;
	u8	saturation;
	u8	sharpness;
पूर्ण;

/* Structure to hold all of our device specअगरic stuff */
काष्ठा hdpvr_device अणु
	/* the v4l device क्रम this device */
	काष्ठा video_device	video_dev;
	/* the control handler क्रम this device */
	काष्ठा v4l2_ctrl_handler hdl;
	/* the usb device क्रम this device */
	काष्ठा usb_device	*udev;
	/* v4l2-device unused */
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा अणु /* video mode/bitrate control cluster */
		काष्ठा v4l2_ctrl *video_mode;
		काष्ठा v4l2_ctrl *video_bitrate;
		काष्ठा v4l2_ctrl *video_bitrate_peak;
	पूर्ण;
	/* v4l2 क्रमmat */
	uपूर्णांक width, height;

	/* the max packet size of the bulk endpoपूर्णांक */
	माप_प्रकार			bulk_in_size;
	/* the address of the bulk in endpoपूर्णांक */
	__u8			bulk_in_endpoपूर्णांकAddr;

	/* holds the current device status */
	__u8			status;

	/* holds the current set options */
	काष्ठा hdpvr_options	options;
	v4l2_std_id		cur_std;
	काष्ठा v4l2_dv_timings	cur_dv_timings;

	uपूर्णांक			flags;

	/* synchronize I/O */
	काष्ठा mutex		io_mutex;
	/* available buffers */
	काष्ठा list_head	मुक्त_buff_list;
	/* in progress buffers */
	काष्ठा list_head	rec_buff_list;
	/* रुकोqueue क्रम buffers */
	रुको_queue_head_t	रुको_buffer;
	/* रुकोqueue क्रम data */
	रुको_queue_head_t	रुको_data;
	/**/
	काष्ठा work_काष्ठा	worker;
	/* current stream owner */
	काष्ठा v4l2_fh		*owner;

	/* I2C adapter */
	काष्ठा i2c_adapter	i2c_adapter;
	/* I2C lock */
	काष्ठा mutex		i2c_mutex;
	/* I2C message buffer space */
	अक्षर			i2c_buf[HDPVR_I2C_MAX_SIZE];

	/* For passing data to ir-kbd-i2c */
	काष्ठा IR_i2c_init_data	ir_i2c_init_data;

	/* usb control transfer buffer and lock */
	काष्ठा mutex		usbc_mutex;
	u8			*usbc_buf;
	u8			fw_ver;
पूर्ण;

अटल अंतरभूत काष्ठा hdpvr_device *to_hdpvr_dev(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा hdpvr_device, v4l2_dev);
पूर्ण


/* buffer one bulk urb of data */
काष्ठा hdpvr_buffer अणु
	काष्ठा list_head	buff_list;

	काष्ठा urb		*urb;

	काष्ठा hdpvr_device	*dev;

	uपूर्णांक			pos;

	__u8			status;
पूर्ण;

/* */

काष्ठा hdpvr_video_info अणु
	u16	width;
	u16	height;
	u8	fps;
	bool	valid;
पूर्ण;

क्रमागत अणु
	STATUS_UNINITIALIZED	= 0,
	STATUS_IDLE,
	STATUS_STARTING,
	STATUS_SHUTTING_DOWN,
	STATUS_STREAMING,
	STATUS_ERROR,
	STATUS_DISCONNECTED,
पूर्ण;

क्रमागत अणु
	HDPVR_FLAG_AC3_CAP = 1,
पूर्ण;

क्रमागत अणु
	BUFSTAT_UNINITIALIZED = 0,
	BUFSTAT_AVAILABLE,
	BUFSTAT_INPROGRESS,
	BUFSTAT_READY,
पूर्ण;

#घोषणा CTRL_START_STREAMING_VALUE	0x0700
#घोषणा CTRL_STOP_STREAMING_VALUE	0x0800
#घोषणा CTRL_BITRATE_VALUE		0x1000
#घोषणा CTRL_BITRATE_MODE_VALUE		0x1200
#घोषणा CTRL_GOP_MODE_VALUE		0x1300
#घोषणा CTRL_VIDEO_INPUT_VALUE		0x1500
#घोषणा CTRL_VIDEO_STD_TYPE		0x1700
#घोषणा CTRL_AUDIO_INPUT_VALUE		0x2500
#घोषणा CTRL_BRIGHTNESS			0x2900
#घोषणा CTRL_CONTRAST			0x2a00
#घोषणा CTRL_HUE			0x2b00
#घोषणा CTRL_SATURATION			0x2c00
#घोषणा CTRL_SHARPNESS			0x2d00
#घोषणा CTRL_LOW_PASS_FILTER_VALUE	0x3100

#घोषणा CTRL_DEFAULT_INDEX		0x0003


	/* :0 s 38 01 1000 0003 0004 4 = 0a00ca00
	 * BITRATE SETTING
	 *   1st and 2nd byte (little endian): average bitrate in 100 000 bit/s
	 *                                     min: 1 mbit/s, max: 13.5 mbit/s
	 *   3rd and 4th byte (little endian): peak bitrate in 100 000 bit/s
	 *                                     min: average + 100kbit/s,
	 *                                      max: 20.2 mbit/s
	 */

	/* :0 s 38 01 1200 0003 0001 1 = 02
	 * BIT RATE MODE
	 *  स्थिरant = 1, variable (peak) = 2, variable (average) = 3
	 */

	/* :0 s 38 01 1300 0003 0001 1 = 03
	 * GOP MODE (2 bit)
	 *    low bit 0/1: advanced/simple GOP
	 *   high bit 0/1: IDR(4/32/128) / no IDR (4/32/0)
	 */

	/* :0 s 38 01 1700 0003 0001 1 = 00
	 * VIDEO STANDARD or FREQUENCY 0 = 60hz, 1 = 50hz
	 */

	/* :0 s 38 01 3100 0003 0004 4 = 03030000
	 * FILTER CONTROL
	 *   1st byte luma low pass filter strength,
	 *   2nd byte chroma low pass filter strength,
	 *   3rd byte MF enable chroma, min=0, max=1
	 *   4th byte n
	 */


	/* :0 s 38 b9 0001 0000 0000 0 */



/* :0 s 38 d3 0000 0000 0001 1 = 00 */
/*		ret = usb_control_msg(dev->udev, */
/*				      usb_sndctrlpipe(dev->udev, 0), */
/*				      0xd3, 0x38, */
/*				      0, 0, */
/*				      "\0", 1, */
/*				      1000); */

/*		info("control request returned %d", ret); */
/*		msleep(5000); */


	/* :0 s b8 81 1400 0003 0005 5 <
	 * :0 0 5 = d0024002 19
	 * QUERY FRAME SIZE AND RATE
	 *   1st and 2nd byte (little endian): horizontal resolution
	 *   3rd and 4th byte (little endian): vertical resolution
	 *   5th byte: frame rate
	 */

	/* :0 s b8 81 1800 0003 0003 3 <
	 * :0 0 3 = 030104
	 * QUERY SIGNAL AND DETECTED LINES, maybe INPUT
	 */

क्रमागत hdpvr_video_std अणु
	HDPVR_60HZ = 0,
	HDPVR_50HZ,
पूर्ण;

क्रमागत hdpvr_video_input अणु
	HDPVR_COMPONENT = 0,
	HDPVR_SVIDEO,
	HDPVR_COMPOSITE,
	HDPVR_VIDEO_INPUTS
पूर्ण;

क्रमागत hdpvr_audio_inमाला_दो अणु
	HDPVR_RCA_BACK = 0,
	HDPVR_RCA_FRONT,
	HDPVR_SPDIF,
	HDPVR_AUDIO_INPUTS
पूर्ण;

क्रमागत hdpvr_bitrate_mode अणु
	HDPVR_CONSTANT = 1,
	HDPVR_VARIABLE_PEAK,
	HDPVR_VARIABLE_AVERAGE,
पूर्ण;

क्रमागत hdpvr_gop_mode अणु
	HDPVR_ADVANCED_IDR_GOP = 0,
	HDPVR_SIMPLE_IDR_GOP,
	HDPVR_ADVANCED_NOIDR_GOP,
	HDPVR_SIMPLE_NOIDR_GOP,
पूर्ण;

व्योम hdpvr_delete(काष्ठा hdpvr_device *dev);

/*========================================================================*/
/* hardware control functions */
पूर्णांक hdpvr_set_options(काष्ठा hdpvr_device *dev);

पूर्णांक hdpvr_set_bitrate(काष्ठा hdpvr_device *dev);

पूर्णांक hdpvr_set_audio(काष्ठा hdpvr_device *dev, u8 input,
		    क्रमागत v4l2_mpeg_audio_encoding codec);

पूर्णांक hdpvr_config_call(काष्ठा hdpvr_device *dev, uपूर्णांक value,
		      अचिन्हित अक्षर valbuf);

पूर्णांक get_video_info(काष्ठा hdpvr_device *dev, काष्ठा hdpvr_video_info *vid_info);

/* :0 s b8 81 1800 0003 0003 3 < */
/* :0 0 3 = 0301ff */
पूर्णांक get_input_lines_info(काष्ठा hdpvr_device *dev);


/*========================================================================*/
/* v4l2 registration */
पूर्णांक hdpvr_रेजिस्टर_videodev(काष्ठा hdpvr_device *dev, काष्ठा device *parent,
			    पूर्णांक devnumber);

पूर्णांक hdpvr_cancel_queue(काष्ठा hdpvr_device *dev);

/*========================================================================*/
/* i2c adapter registration */
पूर्णांक hdpvr_रेजिस्टर_i2c_adapter(काष्ठा hdpvr_device *dev);

काष्ठा i2c_client *hdpvr_रेजिस्टर_ir_i2c(काष्ठा hdpvr_device *dev);

/*========================================================================*/
/* buffer management */
पूर्णांक hdpvr_मुक्त_buffers(काष्ठा hdpvr_device *dev);
पूर्णांक hdpvr_alloc_buffers(काष्ठा hdpvr_device *dev, uपूर्णांक count);
