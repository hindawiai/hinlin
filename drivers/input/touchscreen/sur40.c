<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Surface2.0/SUR40/PixelSense input driver
 *
 * Copyright (c) 2014 by Florian 'floe' Echtler <floe@butterbrot.org>
 *
 * Derived from the USB Skeleton driver 1.1,
 * Copyright (c) 2003 Greg Kroah-Harपंचांगan (greg@kroah.com)
 *
 * and from the Apple USB BCM5974 multitouch driver,
 * Copyright (c) 2008 Henrik Rydberg (rydberg@euromail.se)
 *
 * and from the generic hid-multitouch driver,
 * Copyright (c) 2010-2012 Stephane Chatty <chatty@enac.fr>
 *
 * and from the v4l2-pci-skeleton driver,
 * Copyright (c) Copyright 2014 Cisco Systems, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/completion.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/usb/input.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-sg.h>

/* पढ़ो 512 bytes from endpoपूर्णांक 0x86 -> get header + blobs */
काष्ठा sur40_header अणु

	__le16 type;       /* always 0x0001 */
	__le16 count;      /* count of blobs (अगर 0: जारी prev. packet) */

	__le32 packet_id;  /* unique ID क्रम all packets in one frame */

	__le32 बारtamp;  /* milliseconds (inc. by 16 or 17 each frame) */
	__le32 unknown;    /* "epoch?" always 02/03 00 00 00 */

पूर्ण __packed;

काष्ठा sur40_blob अणु

	__le16 blob_id;

	u8 action;         /* 0x02 = enter/निकास, 0x03 = update (?) */
	u8 type;           /* biपंचांगask (0x01 blob,  0x02 touch, 0x04 tag) */

	__le16 bb_pos_x;   /* upper left corner of bounding box */
	__le16 bb_pos_y;

	__le16 bb_size_x;  /* size of bounding box */
	__le16 bb_size_y;

	__le16 pos_x;      /* finger tip position */
	__le16 pos_y;

	__le16 ctr_x;      /* centroid position */
	__le16 ctr_y;

	__le16 axis_x;     /* somehow related to major/minor axis, mostly: */
	__le16 axis_y;     /* axis_x == bb_size_y && axis_y == bb_size_x */

	__le32 angle;      /* orientation in radians relative to x axis -
	                      actually an IEEE754 भग्न, करोn't use in kernel */

	__le32 area;       /* size in pixels/pressure (?) */

	u8 padding[24];

	__le32 tag_id;     /* valid when type == 0x04 (SUR40_TAG) */
	__le32 unknown;

पूर्ण __packed;

/* combined header/blob data */
काष्ठा sur40_data अणु
	काष्ठा sur40_header header;
	काष्ठा sur40_blob   blobs[];
पूर्ण __packed;

/* पढ़ो 512 bytes from endpoपूर्णांक 0x82 -> get header below
 * जारी पढ़ोing 16k blocks until header.size bytes पढ़ो */
काष्ठा sur40_image_header अणु
	__le32 magic;     /* "SUBF" */
	__le32 packet_id;
	__le32 size;      /* always 0x0007e900 = 960x540 */
	__le32 बारtamp; /* milliseconds (increases by 16 or 17 each frame) */
	__le32 unknown;   /* "epoch?" always 02/03 00 00 00 */
पूर्ण __packed;

/* version inक्रमmation */
#घोषणा DRIVER_SHORT   "sur40"
#घोषणा DRIVER_LONG    "Samsung SUR40"
#घोषणा DRIVER_AUTHOR  "Florian 'floe' Echtler <floe@butterbrot.org>"
#घोषणा DRIVER_DESC    "Surface2.0/SUR40/PixelSense input driver"

/* venकरोr and device IDs */
#घोषणा ID_MICROSOFT 0x045e
#घोषणा ID_SUR40     0x0775

/* sensor resolution */
#घोषणा SENSOR_RES_X 1920
#घोषणा SENSOR_RES_Y 1080

/* touch data endpoपूर्णांक */
#घोषणा TOUCH_ENDPOINT 0x86

/* video data endpoपूर्णांक */
#घोषणा VIDEO_ENDPOINT 0x82

/* video header fields */
#घोषणा VIDEO_HEADER_MAGIC 0x46425553
#घोषणा VIDEO_PACKET_SIZE  16384

/* polling पूर्णांकerval (ms) */
#घोषणा POLL_INTERVAL 1

/* maximum number of contacts FIXME: this is a guess? */
#घोषणा MAX_CONTACTS 64

/* control commands */
#घोषणा SUR40_GET_VERSION 0xb0 /* 12 bytes string    */
#घोषणा SUR40_ACCEL_CAPS  0xb3 /*  5 bytes           */
#घोषणा SUR40_SENSOR_CAPS 0xc1 /* 24 bytes           */

#घोषणा SUR40_POKE        0xc5 /* poke रेजिस्टर byte */
#घोषणा SUR40_PEEK        0xc4 /* 48 bytes रेजिस्टरs */

#घोषणा SUR40_GET_STATE   0xc5 /*  4 bytes state (?) */
#घोषणा SUR40_GET_SENSORS 0xb1 /*  8 bytes sensors   */

#घोषणा SUR40_BLOB	0x01
#घोषणा SUR40_TOUCH	0x02
#घोषणा SUR40_TAG	0x04

/* video controls */
#घोषणा SUR40_BRIGHTNESS_MAX 0xff
#घोषणा SUR40_BRIGHTNESS_MIN 0x00
#घोषणा SUR40_BRIGHTNESS_DEF 0xff

#घोषणा SUR40_CONTRAST_MAX 0x0f
#घोषणा SUR40_CONTRAST_MIN 0x00
#घोषणा SUR40_CONTRAST_DEF 0x0a

#घोषणा SUR40_GAIN_MAX 0x09
#घोषणा SUR40_GAIN_MIN 0x00
#घोषणा SUR40_GAIN_DEF 0x08

#घोषणा SUR40_BACKLIGHT_MAX 0x01
#घोषणा SUR40_BACKLIGHT_MIN 0x00
#घोषणा SUR40_BACKLIGHT_DEF 0x01

#घोषणा sur40_str(s) #s
#घोषणा SUR40_PARAM_RANGE(lo, hi) " (range " sur40_str(lo) "-" sur40_str(hi) ")"

/* module parameters */
अटल uपूर्णांक brightness = SUR40_BRIGHTNESS_DEF;
module_param(brightness, uपूर्णांक, 0644);
MODULE_PARM_DESC(brightness, "set initial brightness"
	SUR40_PARAM_RANGE(SUR40_BRIGHTNESS_MIN, SUR40_BRIGHTNESS_MAX));
अटल uपूर्णांक contrast = SUR40_CONTRAST_DEF;
module_param(contrast, uपूर्णांक, 0644);
MODULE_PARM_DESC(contrast, "set initial contrast"
	SUR40_PARAM_RANGE(SUR40_CONTRAST_MIN, SUR40_CONTRAST_MAX));
अटल uपूर्णांक gain = SUR40_GAIN_DEF;
module_param(gain, uपूर्णांक, 0644);
MODULE_PARM_DESC(gain, "set initial gain"
	SUR40_PARAM_RANGE(SUR40_GAIN_MIN, SUR40_GAIN_MAX));

अटल स्थिर काष्ठा v4l2_pix_क्रमmat sur40_pix_क्रमmat[] = अणु
	अणु
		.pixelक्रमmat = V4L2_TCH_FMT_TU08,
		.width  = SENSOR_RES_X / 2,
		.height = SENSOR_RES_Y / 2,
		.field = V4L2_FIELD_NONE,
		.colorspace = V4L2_COLORSPACE_RAW,
		.bytesperline = SENSOR_RES_X / 2,
		.sizeimage = (SENSOR_RES_X/2) * (SENSOR_RES_Y/2),
	पूर्ण,
	अणु
		.pixelक्रमmat = V4L2_PIX_FMT_GREY,
		.width  = SENSOR_RES_X / 2,
		.height = SENSOR_RES_Y / 2,
		.field = V4L2_FIELD_NONE,
		.colorspace = V4L2_COLORSPACE_RAW,
		.bytesperline = SENSOR_RES_X / 2,
		.sizeimage = (SENSOR_RES_X/2) * (SENSOR_RES_Y/2),
	पूर्ण
पूर्ण;

/* master device state */
काष्ठा sur40_state अणु

	काष्ठा usb_device *usbdev;
	काष्ठा device *dev;
	काष्ठा input_dev *input;

	काष्ठा v4l2_device v4l2;
	काष्ठा video_device vdev;
	काष्ठा mutex lock;
	काष्ठा v4l2_pix_क्रमmat pix_fmt;
	काष्ठा v4l2_ctrl_handler hdl;

	काष्ठा vb2_queue queue;
	काष्ठा list_head buf_list;
	spinlock_t qlock;
	पूर्णांक sequence;

	काष्ठा sur40_data *bulk_in_buffer;
	माप_प्रकार bulk_in_size;
	u8 bulk_in_epaddr;
	u8 vsvideo;

	अक्षर phys[64];
पूर्ण;

काष्ठा sur40_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

/* क्रमward declarations */
अटल स्थिर काष्ठा video_device sur40_video_device;
अटल स्थिर काष्ठा vb2_queue sur40_queue;
अटल व्योम sur40_process_video(काष्ठा sur40_state *sur40);
अटल पूर्णांक sur40_s_ctrl(काष्ठा v4l2_ctrl *ctrl);

अटल स्थिर काष्ठा v4l2_ctrl_ops sur40_ctrl_ops = अणु
	.s_ctrl = sur40_s_ctrl,
पूर्ण;

/*
 * Note: an earlier, non-खुला version of this driver used USB_RECIP_ENDPOINT
 * here by mistake which is very likely to have corrupted the firmware EEPROM
 * on two separate SUR40 devices. Thanks to Alan Stern who spotted this bug.
 * Should you ever run पूर्णांकo a similar problem, the background story to this
 * incident and inकाष्ठाions on how to fix the corrupted EEPROM are available
 * at https://floe.butterbrot.org/matrix/hacking/surface/brick.hपंचांगl
*/

/* command wrapper */
अटल पूर्णांक sur40_command(काष्ठा sur40_state *dev,
			 u8 command, u16 index, व्योम *buffer, u16 size)
अणु
	वापस usb_control_msg(dev->usbdev, usb_rcvctrlpipe(dev->usbdev, 0),
			       command,
			       USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_IN,
			       0x00, index, buffer, size, 1000);
पूर्ण

/* poke a byte in the panel रेजिस्टर space */
अटल पूर्णांक sur40_poke(काष्ठा sur40_state *dev, u8 offset, u8 value)
अणु
	पूर्णांक result;
	u8 index = 0x96; // 0xae क्रम permanent ग_लिखो

	result = usb_control_msg(dev->usbdev, usb_sndctrlpipe(dev->usbdev, 0),
		SUR40_POKE, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
		0x32, index, शून्य, 0, 1000);
	अगर (result < 0)
		जाओ error;
	msleep(5);

	result = usb_control_msg(dev->usbdev, usb_sndctrlpipe(dev->usbdev, 0),
		SUR40_POKE, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
		0x72, offset, शून्य, 0, 1000);
	अगर (result < 0)
		जाओ error;
	msleep(5);

	result = usb_control_msg(dev->usbdev, usb_sndctrlpipe(dev->usbdev, 0),
		SUR40_POKE, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
		0xb2, value, शून्य, 0, 1000);
	अगर (result < 0)
		जाओ error;
	msleep(5);

error:
	वापस result;
पूर्ण

अटल पूर्णांक sur40_set_preprocessor(काष्ठा sur40_state *dev, u8 value)
अणु
	u8 setting_07[2] = अणु 0x01, 0x00 पूर्ण;
	u8 setting_17[2] = अणु 0x85, 0x80 पूर्ण;
	पूर्णांक result;

	अगर (value > 1)
		वापस -दुस्फल;

	result = usb_control_msg(dev->usbdev, usb_sndctrlpipe(dev->usbdev, 0),
		SUR40_POKE, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
		0x07, setting_07[value], शून्य, 0, 1000);
	अगर (result < 0)
		जाओ error;
	msleep(5);

	result = usb_control_msg(dev->usbdev, usb_sndctrlpipe(dev->usbdev, 0),
		SUR40_POKE, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_सूची_OUT,
		0x17, setting_17[value], शून्य, 0, 1000);
	अगर (result < 0)
		जाओ error;
	msleep(5);

error:
	वापस result;
पूर्ण

अटल व्योम sur40_set_vsvideo(काष्ठा sur40_state *handle, u8 value)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		sur40_poke(handle, 0x1c+i, value);
	handle->vsvideo = value;
पूर्ण

अटल व्योम sur40_set_irlevel(काष्ठा sur40_state *handle, u8 value)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		sur40_poke(handle, 0x08+(2*i), value);
पूर्ण

/* Initialization routine, called from sur40_खोलो */
अटल पूर्णांक sur40_init(काष्ठा sur40_state *dev)
अणु
	पूर्णांक result;
	u8 *buffer;

	buffer = kदो_स्मृति(24, GFP_KERNEL);
	अगर (!buffer) अणु
		result = -ENOMEM;
		जाओ error;
	पूर्ण

	/* stupidly replay the original MS driver init sequence */
	result = sur40_command(dev, SUR40_GET_VERSION, 0x00, buffer, 12);
	अगर (result < 0)
		जाओ error;

	result = sur40_command(dev, SUR40_GET_VERSION, 0x01, buffer, 12);
	अगर (result < 0)
		जाओ error;

	result = sur40_command(dev, SUR40_GET_VERSION, 0x02, buffer, 12);
	अगर (result < 0)
		जाओ error;

	result = sur40_command(dev, SUR40_SENSOR_CAPS, 0x00, buffer, 24);
	अगर (result < 0)
		जाओ error;

	result = sur40_command(dev, SUR40_ACCEL_CAPS, 0x00, buffer, 5);
	अगर (result < 0)
		जाओ error;

	result = sur40_command(dev, SUR40_GET_VERSION, 0x03, buffer, 12);
	अगर (result < 0)
		जाओ error;

	result = 0;

	/*
	 * Discard the result buffer - no known data inside except
	 * some version strings, maybe extract these someसमय...
	 */
error:
	kमुक्त(buffer);
	वापस result;
पूर्ण

/*
 * Callback routines from input_dev
 */

/* Enable the device, polling will now start. */
अटल पूर्णांक sur40_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा sur40_state *sur40 = input_get_drvdata(input);

	dev_dbg(sur40->dev, "open\n");
	वापस sur40_init(sur40);
पूर्ण

/* Disable device, polling has stopped. */
अटल व्योम sur40_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा sur40_state *sur40 = input_get_drvdata(input);

	dev_dbg(sur40->dev, "close\n");
	/*
	 * There is no known way to stop the device, so we simply
	 * stop polling.
	 */
पूर्ण

/*
 * This function is called when a whole contact has been processed,
 * so that it can assign it to a slot and store the data there.
 */
अटल व्योम sur40_report_blob(काष्ठा sur40_blob *blob, काष्ठा input_dev *input)
अणु
	पूर्णांक wide, major, minor;
	पूर्णांक bb_size_x, bb_size_y, pos_x, pos_y, ctr_x, ctr_y, slotnum;

	अगर (blob->type != SUR40_TOUCH)
		वापस;

	slotnum = input_mt_get_slot_by_key(input, blob->blob_id);
	अगर (slotnum < 0 || slotnum >= MAX_CONTACTS)
		वापस;

	bb_size_x = le16_to_cpu(blob->bb_size_x);
	bb_size_y = le16_to_cpu(blob->bb_size_y);

	pos_x = le16_to_cpu(blob->pos_x);
	pos_y = le16_to_cpu(blob->pos_y);

	ctr_x = le16_to_cpu(blob->ctr_x);
	ctr_y = le16_to_cpu(blob->ctr_y);

	input_mt_slot(input, slotnum);
	input_mt_report_slot_state(input, MT_TOOL_FINGER, 1);
	wide = (bb_size_x > bb_size_y);
	major = max(bb_size_x, bb_size_y);
	minor = min(bb_size_x, bb_size_y);

	input_report_असल(input, ABS_MT_POSITION_X, pos_x);
	input_report_असल(input, ABS_MT_POSITION_Y, pos_y);
	input_report_असल(input, ABS_MT_TOOL_X, ctr_x);
	input_report_असल(input, ABS_MT_TOOL_Y, ctr_y);

	/* TODO: use a better orientation measure */
	input_report_असल(input, ABS_MT_ORIENTATION, wide);
	input_report_असल(input, ABS_MT_TOUCH_MAJOR, major);
	input_report_असल(input, ABS_MT_TOUCH_MINOR, minor);
पूर्ण

/* core function: poll क्रम new input data */
अटल व्योम sur40_poll(काष्ठा input_dev *input)
अणु
	काष्ठा sur40_state *sur40 = input_get_drvdata(input);
	पूर्णांक result, bulk_पढ़ो, need_blobs, packet_blobs, i;
	काष्ठा sur40_header *header = &sur40->bulk_in_buffer->header;
	काष्ठा sur40_blob *inblob = &sur40->bulk_in_buffer->blobs[0];

	dev_dbg(sur40->dev, "poll\n");

	need_blobs = -1;

	करो अणु

		/* perक्रमm a blocking bulk पढ़ो to get data from the device */
		result = usb_bulk_msg(sur40->usbdev,
			usb_rcvbulkpipe(sur40->usbdev, sur40->bulk_in_epaddr),
			sur40->bulk_in_buffer, sur40->bulk_in_size,
			&bulk_पढ़ो, 1000);

		dev_dbg(sur40->dev, "received %d bytes\n", bulk_पढ़ो);

		अगर (result < 0) अणु
			dev_err(sur40->dev, "error in usb_bulk_read\n");
			वापस;
		पूर्ण

		result = bulk_पढ़ो - माप(काष्ठा sur40_header);

		अगर (result % माप(काष्ठा sur40_blob) != 0) अणु
			dev_err(sur40->dev, "transfer size mismatch\n");
			वापस;
		पूर्ण

		/* first packet? */
		अगर (need_blobs == -1) अणु
			need_blobs = le16_to_cpu(header->count);
			dev_dbg(sur40->dev, "need %d blobs\n", need_blobs);
			/* packet_id = le32_to_cpu(header->packet_id); */
		पूर्ण

		/*
		 * Sanity check. when video data is also being retrieved, the
		 * packet ID will usually increase in the middle of a series
		 * instead of at the end. However, the data is still consistent,
		 * so the packet ID is probably just valid क्रम the first packet
		 * in a series.

		अगर (packet_id != le32_to_cpu(header->packet_id))
			dev_dbg(sur40->dev, "packet ID mismatch\n");
		 */

		packet_blobs = result / माप(काष्ठा sur40_blob);
		dev_dbg(sur40->dev, "received %d blobs\n", packet_blobs);

		/* packets always contain at least 4 blobs, even अगर empty */
		अगर (packet_blobs > need_blobs)
			packet_blobs = need_blobs;

		क्रम (i = 0; i < packet_blobs; i++) अणु
			need_blobs--;
			dev_dbg(sur40->dev, "processing blob\n");
			sur40_report_blob(&(inblob[i]), input);
		पूर्ण

	पूर्ण जबतक (need_blobs > 0);

	input_mt_sync_frame(input);
	input_sync(input);

	sur40_process_video(sur40);
पूर्ण

/* deal with video data */
अटल व्योम sur40_process_video(काष्ठा sur40_state *sur40)
अणु

	काष्ठा sur40_image_header *img = (व्योम *)(sur40->bulk_in_buffer);
	काष्ठा sur40_buffer *new_buf;
	काष्ठा usb_sg_request sgr;
	काष्ठा sg_table *sgt;
	पूर्णांक result, bulk_पढ़ो;

	अगर (!vb2_start_streaming_called(&sur40->queue))
		वापस;

	/* get a new buffer from the list */
	spin_lock(&sur40->qlock);
	अगर (list_empty(&sur40->buf_list)) अणु
		dev_dbg(sur40->dev, "buffer queue empty\n");
		spin_unlock(&sur40->qlock);
		वापस;
	पूर्ण
	new_buf = list_entry(sur40->buf_list.next, काष्ठा sur40_buffer, list);
	list_del(&new_buf->list);
	spin_unlock(&sur40->qlock);

	dev_dbg(sur40->dev, "buffer acquired\n");

	/* retrieve data via bulk पढ़ो */
	result = usb_bulk_msg(sur40->usbdev,
			usb_rcvbulkpipe(sur40->usbdev, VIDEO_ENDPOINT),
			sur40->bulk_in_buffer, sur40->bulk_in_size,
			&bulk_पढ़ो, 1000);

	अगर (result < 0) अणु
		dev_err(sur40->dev, "error in usb_bulk_read\n");
		जाओ err_poll;
	पूर्ण

	अगर (bulk_पढ़ो != माप(काष्ठा sur40_image_header)) अणु
		dev_err(sur40->dev, "received %d bytes (%zd expected)\n",
			bulk_पढ़ो, माप(काष्ठा sur40_image_header));
		जाओ err_poll;
	पूर्ण

	अगर (le32_to_cpu(img->magic) != VIDEO_HEADER_MAGIC) अणु
		dev_err(sur40->dev, "image magic mismatch\n");
		जाओ err_poll;
	पूर्ण

	अगर (le32_to_cpu(img->size) != sur40->pix_fmt.sizeimage) अणु
		dev_err(sur40->dev, "image size mismatch\n");
		जाओ err_poll;
	पूर्ण

	dev_dbg(sur40->dev, "header acquired\n");

	sgt = vb2_dma_sg_plane_desc(&new_buf->vb.vb2_buf, 0);

	result = usb_sg_init(&sgr, sur40->usbdev,
		usb_rcvbulkpipe(sur40->usbdev, VIDEO_ENDPOINT), 0,
		sgt->sgl, sgt->nents, sur40->pix_fmt.sizeimage, 0);
	अगर (result < 0) अणु
		dev_err(sur40->dev, "error %d in usb_sg_init\n", result);
		जाओ err_poll;
	पूर्ण

	usb_sg_रुको(&sgr);
	अगर (sgr.status < 0) अणु
		dev_err(sur40->dev, "error %d in usb_sg_wait\n", sgr.status);
		जाओ err_poll;
	पूर्ण

	dev_dbg(sur40->dev, "image acquired\n");

	/* वापस error अगर streaming was stopped in the meanसमय */
	अगर (sur40->sequence == -1)
		वापस;

	/* mark as finished */
	new_buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
	new_buf->vb.sequence = sur40->sequence++;
	new_buf->vb.field = V4L2_FIELD_NONE;
	vb2_buffer_करोne(&new_buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
	dev_dbg(sur40->dev, "buffer marked done\n");
	वापस;

err_poll:
	vb2_buffer_करोne(&new_buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
पूर्ण

/* Initialize input device parameters. */
अटल पूर्णांक sur40_input_setup_events(काष्ठा input_dev *input_dev)
अणु
	पूर्णांक error;

	input_set_असल_params(input_dev, ABS_MT_POSITION_X,
			     0, SENSOR_RES_X, 0, 0);
	input_set_असल_params(input_dev, ABS_MT_POSITION_Y,
			     0, SENSOR_RES_Y, 0, 0);

	input_set_असल_params(input_dev, ABS_MT_TOOL_X,
			     0, SENSOR_RES_X, 0, 0);
	input_set_असल_params(input_dev, ABS_MT_TOOL_Y,
			     0, SENSOR_RES_Y, 0, 0);

	/* max value unknown, but major/minor axis
	 * can never be larger than screen */
	input_set_असल_params(input_dev, ABS_MT_TOUCH_MAJOR,
			     0, SENSOR_RES_X, 0, 0);
	input_set_असल_params(input_dev, ABS_MT_TOUCH_MINOR,
			     0, SENSOR_RES_Y, 0, 0);

	input_set_असल_params(input_dev, ABS_MT_ORIENTATION, 0, 1, 0, 0);

	error = input_mt_init_slots(input_dev, MAX_CONTACTS,
				    INPUT_MT_सूचीECT | INPUT_MT_DROP_UNUSED);
	अगर (error) अणु
		dev_err(input_dev->dev.parent, "failed to set up slots\n");
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/* Check candidate USB पूर्णांकerface. */
अटल पूर्णांक sur40_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		       स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा sur40_state *sur40;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा input_dev *input;
	पूर्णांक error;

	/* Check अगर we really have the right पूर्णांकerface. */
	अगरace_desc = पूर्णांकerface->cur_altsetting;
	अगर (अगरace_desc->desc.bInterfaceClass != 0xFF)
		वापस -ENODEV;

	अगर (अगरace_desc->desc.bNumEndpoपूर्णांकs < 5)
		वापस -ENODEV;

	/* Use endpoपूर्णांक #4 (0x86). */
	endpoपूर्णांक = &अगरace_desc->endpoपूर्णांक[4].desc;
	अगर (endpoपूर्णांक->bEndpoपूर्णांकAddress != TOUCH_ENDPOINT)
		वापस -ENODEV;

	/* Allocate memory क्रम our device state and initialize it. */
	sur40 = kzalloc(माप(काष्ठा sur40_state), GFP_KERNEL);
	अगर (!sur40)
		वापस -ENOMEM;

	input = input_allocate_device();
	अगर (!input) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_dev;
	पूर्ण

	/* initialize locks/lists */
	INIT_LIST_HEAD(&sur40->buf_list);
	spin_lock_init(&sur40->qlock);
	mutex_init(&sur40->lock);

	/* Set up regular input device काष्ठाure */
	input->name = DRIVER_LONG;
	usb_to_input_id(usbdev, &input->id);
	usb_make_path(usbdev, sur40->phys, माप(sur40->phys));
	strlcat(sur40->phys, "/input0", माप(sur40->phys));
	input->phys = sur40->phys;
	input->dev.parent = &पूर्णांकerface->dev;

	input->खोलो = sur40_खोलो;
	input->बंद = sur40_बंद;

	error = sur40_input_setup_events(input);
	अगर (error)
		जाओ err_मुक्त_input;

	input_set_drvdata(input, sur40);
	error = input_setup_polling(input, sur40_poll);
	अगर (error) अणु
		dev_err(&पूर्णांकerface->dev, "failed to set up polling");
		जाओ err_मुक्त_input;
	पूर्ण

	input_set_poll_पूर्णांकerval(input, POLL_INTERVAL);

	sur40->usbdev = usbdev;
	sur40->dev = &पूर्णांकerface->dev;
	sur40->input = input;

	/* use the bulk-in endpoपूर्णांक tested above */
	sur40->bulk_in_size = usb_endpoपूर्णांक_maxp(endpoपूर्णांक);
	sur40->bulk_in_epaddr = endpoपूर्णांक->bEndpoपूर्णांकAddress;
	sur40->bulk_in_buffer = kदो_स्मृति(sur40->bulk_in_size, GFP_KERNEL);
	अगर (!sur40->bulk_in_buffer) अणु
		dev_err(&पूर्णांकerface->dev, "Unable to allocate input buffer.");
		error = -ENOMEM;
		जाओ err_मुक्त_input;
	पूर्ण

	/* रेजिस्टर the polled input device */
	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(&पूर्णांकerface->dev,
			"Unable to register polled input device.");
		जाओ err_मुक्त_buffer;
	पूर्ण

	/* रेजिस्टर the video master device */
	snम_लिखो(sur40->v4l2.name, माप(sur40->v4l2.name), "%s", DRIVER_LONG);
	error = v4l2_device_रेजिस्टर(sur40->dev, &sur40->v4l2);
	अगर (error) अणु
		dev_err(&पूर्णांकerface->dev,
			"Unable to register video master device.");
		जाओ err_unreg_v4l2;
	पूर्ण

	/* initialize the lock and subdevice */
	sur40->queue = sur40_queue;
	sur40->queue.drv_priv = sur40;
	sur40->queue.lock = &sur40->lock;
	sur40->queue.dev = sur40->dev;

	/* initialize the queue */
	error = vb2_queue_init(&sur40->queue);
	अगर (error)
		जाओ err_unreg_v4l2;

	sur40->pix_fmt = sur40_pix_क्रमmat[0];
	sur40->vdev = sur40_video_device;
	sur40->vdev.v4l2_dev = &sur40->v4l2;
	sur40->vdev.lock = &sur40->lock;
	sur40->vdev.queue = &sur40->queue;
	video_set_drvdata(&sur40->vdev, sur40);

	/* initialize the control handler क्रम 4 controls */
	v4l2_ctrl_handler_init(&sur40->hdl, 4);
	sur40->v4l2.ctrl_handler = &sur40->hdl;
	sur40->vsvideo = (SUR40_CONTRAST_DEF << 4) | SUR40_GAIN_DEF;

	v4l2_ctrl_new_std(&sur40->hdl, &sur40_ctrl_ops, V4L2_CID_BRIGHTNESS,
	  SUR40_BRIGHTNESS_MIN, SUR40_BRIGHTNESS_MAX, 1, clamp(brightness,
	  (uपूर्णांक)SUR40_BRIGHTNESS_MIN, (uपूर्णांक)SUR40_BRIGHTNESS_MAX));

	v4l2_ctrl_new_std(&sur40->hdl, &sur40_ctrl_ops, V4L2_CID_CONTRAST,
	  SUR40_CONTRAST_MIN, SUR40_CONTRAST_MAX, 1, clamp(contrast,
	  (uपूर्णांक)SUR40_CONTRAST_MIN, (uपूर्णांक)SUR40_CONTRAST_MAX));

	v4l2_ctrl_new_std(&sur40->hdl, &sur40_ctrl_ops, V4L2_CID_GAIN,
	  SUR40_GAIN_MIN, SUR40_GAIN_MAX, 1, clamp(gain,
	  (uपूर्णांक)SUR40_GAIN_MIN, (uपूर्णांक)SUR40_GAIN_MAX));

	v4l2_ctrl_new_std(&sur40->hdl, &sur40_ctrl_ops,
	  V4L2_CID_BACKLIGHT_COMPENSATION, SUR40_BACKLIGHT_MIN,
	  SUR40_BACKLIGHT_MAX, 1, SUR40_BACKLIGHT_DEF);

	v4l2_ctrl_handler_setup(&sur40->hdl);

	अगर (sur40->hdl.error) अणु
		dev_err(&पूर्णांकerface->dev,
			"Unable to register video controls.");
		v4l2_ctrl_handler_मुक्त(&sur40->hdl);
		error = sur40->hdl.error;
		जाओ err_unreg_v4l2;
	पूर्ण

	error = video_रेजिस्टर_device(&sur40->vdev, VFL_TYPE_TOUCH, -1);
	अगर (error) अणु
		dev_err(&पूर्णांकerface->dev,
			"Unable to register video subdevice.");
		जाओ err_unreg_video;
	पूर्ण

	/* we can रेजिस्टर the device now, as it is पढ़ोy */
	usb_set_पूर्णांकfdata(पूर्णांकerface, sur40);
	dev_dbg(&पूर्णांकerface->dev, "%s is now attached\n", DRIVER_DESC);

	वापस 0;

err_unreg_video:
	video_unरेजिस्टर_device(&sur40->vdev);
err_unreg_v4l2:
	v4l2_device_unरेजिस्टर(&sur40->v4l2);
err_मुक्त_buffer:
	kमुक्त(sur40->bulk_in_buffer);
err_मुक्त_input:
	input_मुक्त_device(input);
err_मुक्त_dev:
	kमुक्त(sur40);

	वापस error;
पूर्ण

/* Unरेजिस्टर device & clean up. */
अटल व्योम sur40_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा sur40_state *sur40 = usb_get_पूर्णांकfdata(पूर्णांकerface);

	v4l2_ctrl_handler_मुक्त(&sur40->hdl);
	video_unरेजिस्टर_device(&sur40->vdev);
	v4l2_device_unरेजिस्टर(&sur40->v4l2);

	input_unरेजिस्टर_device(sur40->input);
	kमुक्त(sur40->bulk_in_buffer);
	kमुक्त(sur40);

	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	dev_dbg(&पूर्णांकerface->dev, "%s is now disconnected\n", DRIVER_DESC);
पूर्ण

/*
 * Setup the स्थिरraपूर्णांकs of the queue: besides setting the number of planes
 * per buffer and the size and allocation context of each plane, it also
 * checks अगर sufficient buffers have been allocated. Usually 3 is a good
 * minimum number: many DMA engines need a minimum of 2 buffers in the
 * queue and you need to have another available क्रम userspace processing.
 */
अटल पूर्णांक sur40_queue_setup(काष्ठा vb2_queue *q,
		       अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा sur40_state *sur40 = vb2_get_drv_priv(q);

	अगर (q->num_buffers + *nbuffers < 3)
		*nbuffers = 3 - q->num_buffers;

	अगर (*nplanes)
		वापस sizes[0] < sur40->pix_fmt.sizeimage ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = sur40->pix_fmt.sizeimage;

	वापस 0;
पूर्ण

/*
 * Prepare the buffer क्रम queueing to the DMA engine: check and set the
 * payload size.
 */
अटल पूर्णांक sur40_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा sur40_state *sur40 = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ size = sur40->pix_fmt.sizeimage;

	अगर (vb2_plane_size(vb, 0) < size) अणु
		dev_err(&sur40->usbdev->dev, "buffer too small (%lu < %lu)\n",
			 vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, size);
	वापस 0;
पूर्ण

/*
 * Queue this buffer to the DMA engine.
 */
अटल व्योम sur40_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा sur40_state *sur40 = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा sur40_buffer *buf = (काष्ठा sur40_buffer *)vb;

	spin_lock(&sur40->qlock);
	list_add_tail(&buf->list, &sur40->buf_list);
	spin_unlock(&sur40->qlock);
पूर्ण

अटल व्योम वापस_all_buffers(काष्ठा sur40_state *sur40,
			       क्रमागत vb2_buffer_state state)
अणु
	काष्ठा sur40_buffer *buf, *node;

	spin_lock(&sur40->qlock);
	list_क्रम_each_entry_safe(buf, node, &sur40->buf_list, list) अणु
		vb2_buffer_करोne(&buf->vb.vb2_buf, state);
		list_del(&buf->list);
	पूर्ण
	spin_unlock(&sur40->qlock);
पूर्ण

/*
 * Start streaming. First check अगर the minimum number of buffers have been
 * queued. If not, then वापस -ENOBUFS and the vb2 framework will call
 * this function again the next समय a buffer has been queued until enough
 * buffers are available to actually start the DMA engine.
 */
अटल पूर्णांक sur40_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा sur40_state *sur40 = vb2_get_drv_priv(vq);

	sur40->sequence = 0;
	वापस 0;
पूर्ण

/*
 * Stop the DMA engine. Any reमुख्यing buffers in the DMA queue are dequeued
 * and passed on to the vb2 framework marked as STATE_ERROR.
 */
अटल व्योम sur40_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा sur40_state *sur40 = vb2_get_drv_priv(vq);
	vb2_रुको_क्रम_all_buffers(vq);
	sur40->sequence = -1;

	/* Release all active buffers */
	वापस_all_buffers(sur40, VB2_BUF_STATE_ERROR);
पूर्ण

/* V4L ioctl */
अटल पूर्णांक sur40_vidioc_querycap(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_capability *cap)
अणु
	काष्ठा sur40_state *sur40 = video_drvdata(file);

	strlcpy(cap->driver, DRIVER_SHORT, माप(cap->driver));
	strlcpy(cap->card, DRIVER_LONG, माप(cap->card));
	usb_make_path(sur40->usbdev, cap->bus_info, माप(cap->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक sur40_vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
				   काष्ठा v4l2_input *i)
अणु
	अगर (i->index != 0)
		वापस -EINVAL;
	i->type = V4L2_INPUT_TYPE_TOUCH;
	i->std = V4L2_STD_UNKNOWN;
	strlcpy(i->name, "In-Cell Sensor", माप(i->name));
	i->capabilities = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक sur40_vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	वापस (i == 0) ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक sur40_vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक sur40_vidioc_try_fmt(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_क्रमmat *f)
अणु
	चयन (f->fmt.pix.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_GREY:
		f->fmt.pix = sur40_pix_क्रमmat[1];
		अवरोध;

	शेष:
		f->fmt.pix = sur40_pix_क्रमmat[0];
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sur40_vidioc_s_fmt(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा sur40_state *sur40 = video_drvdata(file);

	चयन (f->fmt.pix.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_GREY:
		sur40->pix_fmt = sur40_pix_क्रमmat[1];
		अवरोध;

	शेष:
		sur40->pix_fmt = sur40_pix_क्रमmat[0];
		अवरोध;
	पूर्ण

	f->fmt.pix = sur40->pix_fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक sur40_vidioc_g_fmt(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा sur40_state *sur40 = video_drvdata(file);

	f->fmt.pix = sur40->pix_fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक sur40_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा sur40_state *sur40  = container_of(ctrl->handler,
	  काष्ठा sur40_state, hdl);
	u8 value = sur40->vsvideo;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		sur40_set_irlevel(sur40, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		value = (value & 0x0f) | (ctrl->val << 4);
		sur40_set_vsvideo(sur40, value);
		अवरोध;
	हाल V4L2_CID_GAIN:
		value = (value & 0xf0) | (ctrl->val);
		sur40_set_vsvideo(sur40, value);
		अवरोध;
	हाल V4L2_CID_BACKLIGHT_COMPENSATION:
		sur40_set_preprocessor(sur40, ctrl->val);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sur40_ioctl_parm(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_streamparm *p)
अणु
	अगर (p->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	p->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	p->parm.capture.समयperframe.numerator = 1;
	p->parm.capture.समयperframe.denominator = 60;
	p->parm.capture.पढ़ोbuffers = 3;
	वापस 0;
पूर्ण

अटल पूर्णांक sur40_vidioc_क्रमागत_fmt(काष्ठा file *file, व्योम *priv,
				 काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index >= ARRAY_SIZE(sur40_pix_क्रमmat))
		वापस -EINVAL;

	f->pixelक्रमmat = sur40_pix_क्रमmat[f->index].pixelक्रमmat;
	f->flags = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक sur40_vidioc_क्रमागत_framesizes(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_frmsizeक्रमागत *f)
अणु
	काष्ठा sur40_state *sur40 = video_drvdata(file);

	अगर ((f->index != 0) || ((f->pixel_क्रमmat != V4L2_TCH_FMT_TU08)
		&& (f->pixel_क्रमmat != V4L2_PIX_FMT_GREY)))
		वापस -EINVAL;

	f->type = V4L2_FRMSIZE_TYPE_DISCRETE;
	f->discrete.width  = sur40->pix_fmt.width;
	f->discrete.height = sur40->pix_fmt.height;
	वापस 0;
पूर्ण

अटल पूर्णांक sur40_vidioc_क्रमागत_frameपूर्णांकervals(काष्ठा file *file, व्योम *priv,
					    काष्ठा v4l2_frmivalक्रमागत *f)
अणु
	काष्ठा sur40_state *sur40 = video_drvdata(file);

	अगर ((f->index > 0) || ((f->pixel_क्रमmat != V4L2_TCH_FMT_TU08)
		&& (f->pixel_क्रमmat != V4L2_PIX_FMT_GREY))
		|| (f->width  != sur40->pix_fmt.width)
		|| (f->height != sur40->pix_fmt.height))
		वापस -EINVAL;

	f->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	f->discrete.denominator  = 60;
	f->discrete.numerator = 1;
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा usb_device_id sur40_table[] = अणु
	अणु USB_DEVICE(ID_MICROSOFT, ID_SUR40) पूर्ण,  /* Samsung SUR40 */
	अणु पूर्ण                                      /* terminating null entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, sur40_table);

/* V4L2 काष्ठाures */
अटल स्थिर काष्ठा vb2_ops sur40_queue_ops = अणु
	.queue_setup		= sur40_queue_setup,
	.buf_prepare		= sur40_buffer_prepare,
	.buf_queue		= sur40_buffer_queue,
	.start_streaming	= sur40_start_streaming,
	.stop_streaming		= sur40_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

अटल स्थिर काष्ठा vb2_queue sur40_queue = अणु
	.type = V4L2_BUF_TYPE_VIDEO_CAPTURE,
	/*
	 * VB2_USERPTR in currently not enabled: passing a user poपूर्णांकer to
	 * dma-sg will result in segment sizes that are not a multiple of
	 * 512 bytes, which is required by the host controller.
	*/
	.io_modes = VB2_MMAP | VB2_READ | VB2_DMABUF,
	.buf_काष्ठा_size = माप(काष्ठा sur40_buffer),
	.ops = &sur40_queue_ops,
	.mem_ops = &vb2_dma_sg_memops,
	.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC,
	.min_buffers_needed = 3,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations sur40_video_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release,
	.unlocked_ioctl = video_ioctl2,
	.पढ़ो = vb2_fop_पढ़ो,
	.mmap = vb2_fop_mmap,
	.poll = vb2_fop_poll,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops sur40_video_ioctl_ops = अणु

	.vidioc_querycap	= sur40_vidioc_querycap,

	.vidioc_क्रमागत_fmt_vid_cap = sur40_vidioc_क्रमागत_fmt,
	.vidioc_try_fmt_vid_cap	= sur40_vidioc_try_fmt,
	.vidioc_s_fmt_vid_cap	= sur40_vidioc_s_fmt,
	.vidioc_g_fmt_vid_cap	= sur40_vidioc_g_fmt,

	.vidioc_क्रमागत_framesizes = sur40_vidioc_क्रमागत_framesizes,
	.vidioc_क्रमागत_frameपूर्णांकervals = sur40_vidioc_क्रमागत_frameपूर्णांकervals,

	.vidioc_g_parm = sur40_ioctl_parm,
	.vidioc_s_parm = sur40_ioctl_parm,

	.vidioc_क्रमागत_input	= sur40_vidioc_क्रमागत_input,
	.vidioc_g_input		= sur40_vidioc_g_input,
	.vidioc_s_input		= sur40_vidioc_s_input,

	.vidioc_reqbufs		= vb2_ioctl_reqbufs,
	.vidioc_create_bufs	= vb2_ioctl_create_bufs,
	.vidioc_querybuf	= vb2_ioctl_querybuf,
	.vidioc_qbuf		= vb2_ioctl_qbuf,
	.vidioc_dqbuf		= vb2_ioctl_dqbuf,
	.vidioc_expbuf		= vb2_ioctl_expbuf,

	.vidioc_streamon	= vb2_ioctl_streamon,
	.vidioc_streamoff	= vb2_ioctl_streamoff,
पूर्ण;

अटल स्थिर काष्ठा video_device sur40_video_device = अणु
	.name = DRIVER_LONG,
	.fops = &sur40_video_fops,
	.ioctl_ops = &sur40_video_ioctl_ops,
	.release = video_device_release_empty,
	.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_TOUCH |
		       V4L2_CAP_READWRITE | V4L2_CAP_STREAMING,
पूर्ण;

/* USB-specअगरic object needed to रेजिस्टर this driver with the USB subप्रणाली. */
अटल काष्ठा usb_driver sur40_driver = अणु
	.name = DRIVER_SHORT,
	.probe = sur40_probe,
	.disconnect = sur40_disconnect,
	.id_table = sur40_table,
पूर्ण;

module_usb_driver(sur40_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
