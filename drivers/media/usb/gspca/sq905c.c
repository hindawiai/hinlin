<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SQ905C subdriver
 *
 * Copyright (C) 2009 Theoकरोre Kilgore
 */

/*
 *
 * This driver uses work करोne in
 * libgphoto2/camlibs/digigr8, Copyright (C) Theoकरोre Kilgore.
 *
 * This driver has also used as a base the sq905c driver
 * and may contain code fragments from it.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "sq905c"

#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश "gspca.h"

MODULE_AUTHOR("Theodore Kilgore <kilgota@auburn.edu>");
MODULE_DESCRIPTION("GSPCA/SQ905C USB Camera Driver");
MODULE_LICENSE("GPL");

/* Default समयouts, in ms */
#घोषणा SQ905C_CMD_TIMEOUT 500
#घोषणा SQ905C_DATA_TIMEOUT 1000

/* Maximum transfer size to use. */
#घोषणा SQ905C_MAX_TRANSFER 0x8000

#घोषणा FRAME_HEADER_LEN 0x50

/* Commands. These go in the "value" slot. */
#घोषणा SQ905C_CLEAR   0xa0		/* clear everything */
#घोषणा SQ905C_GET_ID  0x14f4		/* Read version number */
#घोषणा SQ905C_CAPTURE_LOW 0xa040	/* Starts capture at 160x120 */
#घोषणा SQ905C_CAPTURE_MED 0x1440	/* Starts capture at 320x240 */
#घोषणा SQ905C_CAPTURE_HI 0x2840	/* Starts capture at 320x240 */

/* For capture, this must go in the "index" slot. */
#घोषणा SQ905C_CAPTURE_INDEX 0x110f

/* Structure to hold all of our device specअगरic stuff */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */
	स्थिर काष्ठा v4l2_pix_क्रमmat *cap_mode;
	/* Driver stuff */
	काष्ठा work_काष्ठा work_काष्ठा;
	काष्ठा workqueue_काष्ठा *work_thपढ़ो;
पूर्ण;

/*
 * Most of these cameras will करो 640x480 and 320x240. 160x120 works
 * in theory but gives very poor output. Thereक्रमe, not supported.
 * The 0x2770:0x9050 cameras have max resolution of 320x240.
 */
अटल काष्ठा v4l2_pix_क्रमmat sq905c_mode[] = अणु
	अणु 320, 240, V4L2_PIX_FMT_SQ905C, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
	अणु 640, 480, V4L2_PIX_FMT_SQ905C, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण
पूर्ण;

/* Send a command to the camera. */
अटल पूर्णांक sq905c_command(काष्ठा gspca_dev *gspca_dev, u16 command, u16 index)
अणु
	पूर्णांक ret;

	ret = usb_control_msg(gspca_dev->dev,
			      usb_sndctrlpipe(gspca_dev->dev, 0),
			      USB_REQ_SYNCH_FRAME,                /* request */
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      command, index, शून्य, 0,
			      SQ905C_CMD_TIMEOUT);
	अगर (ret < 0) अणु
		pr_err("%s: usb_control_msg failed (%d)\n", __func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sq905c_पढ़ो(काष्ठा gspca_dev *gspca_dev, u16 command, u16 index,
		       पूर्णांक size)
अणु
	पूर्णांक ret;

	ret = usb_control_msg(gspca_dev->dev,
			      usb_rcvctrlpipe(gspca_dev->dev, 0),
			      USB_REQ_SYNCH_FRAME,		/* request */
			      USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      command, index, gspca_dev->usb_buf, size,
			      SQ905C_CMD_TIMEOUT);
	अगर (ret < 0) अणु
		pr_err("%s: usb_control_msg failed (%d)\n", __func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function is called as a workqueue function and runs whenever the camera
 * is streaming data. Because it is a workqueue function it is allowed to sleep
 * so we can use synchronous USB calls. To aव्योम possible collisions with other
 * thपढ़ोs attempting to use gspca_dev->usb_buf we take the usb_lock when
 * perक्रमming USB operations using it. In practice we करोn't really need this
 * as the camera करोesn't provide any controls.
 */
अटल व्योम sq905c_करोstream(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sd *dev = container_of(work, काष्ठा sd, work_काष्ठा);
	काष्ठा gspca_dev *gspca_dev = &dev->gspca_dev;
	पूर्णांक bytes_left; /* bytes reमुख्यing in current frame. */
	पूर्णांक data_len;   /* size to use क्रम the next पढ़ो. */
	पूर्णांक act_len;
	पूर्णांक packet_type;
	पूर्णांक ret;
	u8 *buffer;

	buffer = kदो_स्मृति(SQ905C_MAX_TRANSFER, GFP_KERNEL);
	अगर (!buffer) अणु
		pr_err("Couldn't allocate USB buffer\n");
		जाओ quit_stream;
	पूर्ण

	जबतक (gspca_dev->present && gspca_dev->streaming) अणु
#अगर_घोषित CONFIG_PM
		अगर (gspca_dev->frozen)
			अवरोध;
#पूर्ण_अगर
		/* Request the header, which tells the size to करोwnload */
		ret = usb_bulk_msg(gspca_dev->dev,
				usb_rcvbulkpipe(gspca_dev->dev, 0x81),
				buffer, FRAME_HEADER_LEN, &act_len,
				SQ905C_DATA_TIMEOUT);
		gspca_dbg(gspca_dev, D_STREAM,
			  "Got %d bytes out of %d for header\n",
			  act_len, FRAME_HEADER_LEN);
		अगर (ret < 0 || act_len < FRAME_HEADER_LEN)
			जाओ quit_stream;
		/* size is पढ़ो from 4 bytes starting 0x40, little endian */
		bytes_left = buffer[0x40]|(buffer[0x41]<<8)|(buffer[0x42]<<16)
					|(buffer[0x43]<<24);
		gspca_dbg(gspca_dev, D_STREAM, "bytes_left = 0x%x\n",
			  bytes_left);
		/* We keep the header. It has other inक्रमmation, too. */
		packet_type = FIRST_PACKET;
		gspca_frame_add(gspca_dev, packet_type,
				buffer, FRAME_HEADER_LEN);
		जबतक (bytes_left > 0 && gspca_dev->present) अणु
			data_len = bytes_left > SQ905C_MAX_TRANSFER ?
				SQ905C_MAX_TRANSFER : bytes_left;
			ret = usb_bulk_msg(gspca_dev->dev,
				usb_rcvbulkpipe(gspca_dev->dev, 0x81),
				buffer, data_len, &act_len,
				SQ905C_DATA_TIMEOUT);
			अगर (ret < 0 || act_len < data_len)
				जाओ quit_stream;
			gspca_dbg(gspca_dev, D_STREAM,
				  "Got %d bytes out of %d for frame\n",
				  data_len, bytes_left);
			bytes_left -= data_len;
			अगर (bytes_left == 0)
				packet_type = LAST_PACKET;
			अन्यथा
				packet_type = INTER_PACKET;
			gspca_frame_add(gspca_dev, packet_type,
					buffer, data_len);
		पूर्ण
	पूर्ण
quit_stream:
	अगर (gspca_dev->present) अणु
		mutex_lock(&gspca_dev->usb_lock);
		sq905c_command(gspca_dev, SQ905C_CLEAR, 0);
		mutex_unlock(&gspca_dev->usb_lock);
	पूर्ण
	kमुक्त(buffer);
पूर्ण

/* This function is called at probe समय just beक्रमe sd_init */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा cam *cam = &gspca_dev->cam;
	काष्ठा sd *dev = (काष्ठा sd *) gspca_dev;
	पूर्णांक ret;

	gspca_dbg(gspca_dev, D_PROBE,
		  "SQ9050 camera detected (vid/pid 0x%04X:0x%04X)\n",
		  id->idVenकरोr, id->idProduct);

	ret = sq905c_command(gspca_dev, SQ905C_GET_ID, 0);
	अगर (ret < 0) अणु
		gspca_err(gspca_dev, "Get version command failed\n");
		वापस ret;
	पूर्ण

	ret = sq905c_पढ़ो(gspca_dev, 0xf5, 0, 20);
	अगर (ret < 0) अणु
		gspca_err(gspca_dev, "Reading version command failed\n");
		वापस ret;
	पूर्ण
	/* Note we leave out the usb id and the manufacturing date */
	gspca_dbg(gspca_dev, D_PROBE,
		  "SQ9050 ID string: %02x - %*ph\n",
		  gspca_dev->usb_buf[3], 6, gspca_dev->usb_buf + 14);

	cam->cam_mode = sq905c_mode;
	cam->nmodes = 2;
	अगर (gspca_dev->usb_buf[15] == 0)
		cam->nmodes = 1;
	/* We करोn't use the buffer gspca allocates so make it small. */
	cam->bulk_size = 32;
	cam->bulk = 1;
	INIT_WORK(&dev->work_काष्ठा, sq905c_करोstream);
	वापस 0;
पूर्ण

/* called on streamoff with alt==0 and on disconnect */
/* the usb_lock is held at entry - restore on निकास */
अटल व्योम sd_stop0(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *dev = (काष्ठा sd *) gspca_dev;

	/* रुको क्रम the work queue to terminate */
	mutex_unlock(&gspca_dev->usb_lock);
	/* This रुकोs क्रम sq905c_करोstream to finish */
	destroy_workqueue(dev->work_thपढ़ो);
	dev->work_thपढ़ो = शून्य;
	mutex_lock(&gspca_dev->usb_lock);
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	/* connect to the camera and reset it. */
	वापस sq905c_command(gspca_dev, SQ905C_CLEAR, 0);
पूर्ण

/* Set up क्रम getting frames. */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *dev = (काष्ठा sd *) gspca_dev;
	पूर्णांक ret;

	dev->cap_mode = gspca_dev->cam.cam_mode;
	/* "Open the shutter" and set size, to start capture */
	चयन (gspca_dev->pixfmt.width) अणु
	हाल 640:
		gspca_dbg(gspca_dev, D_STREAM, "Start streaming at high resolution\n");
		dev->cap_mode++;
		ret = sq905c_command(gspca_dev, SQ905C_CAPTURE_HI,
						SQ905C_CAPTURE_INDEX);
		अवरोध;
	शेष: /* 320 */
		gspca_dbg(gspca_dev, D_STREAM, "Start streaming at medium resolution\n");
		ret = sq905c_command(gspca_dev, SQ905C_CAPTURE_MED,
						SQ905C_CAPTURE_INDEX);
	पूर्ण

	अगर (ret < 0) अणु
		gspca_err(gspca_dev, "Start streaming command failed\n");
		वापस ret;
	पूर्ण
	/* Start the workqueue function to करो the streaming */
	dev->work_thपढ़ो = create_singlethपढ़ो_workqueue(MODULE_NAME);
	अगर (!dev->work_thपढ़ो)
		वापस -ENOMEM;

	queue_work(dev->work_thपढ़ो, &dev->work_काष्ठा);

	वापस 0;
पूर्ण

/* Table of supported USB devices */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x2770, 0x905c)पूर्ण,
	अणुUSB_DEVICE(0x2770, 0x9050)पूर्ण,
	अणुUSB_DEVICE(0x2770, 0x9051)पूर्ण,
	अणुUSB_DEVICE(0x2770, 0x9052)पूर्ण,
	अणुUSB_DEVICE(0x2770, 0x913d)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, device_table);

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name   = MODULE_NAME,
	.config = sd_config,
	.init   = sd_init,
	.start  = sd_start,
	.stop0  = sd_stop0,
पूर्ण;

/* -- device connect -- */
अटल पूर्णांक sd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	वापस gspca_dev_probe(पूर्णांकf, id,
			&sd_desc,
			माप(काष्ठा sd),
			THIS_MODULE);
पूर्ण

अटल काष्ठा usb_driver sd_driver = अणु
	.name       = MODULE_NAME,
	.id_table   = device_table,
	.probe      = sd_probe,
	.disconnect = gspca_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend = gspca_suspend,
	.resume  = gspca_resume,
	.reset_resume = gspca_resume,
#पूर्ण_अगर
पूर्ण;

module_usb_driver(sd_driver);
