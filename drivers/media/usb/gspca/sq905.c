<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SQ905 subdriver
 *
 * Copyright (C) 2008, 2009 Adam Baker and Theoकरोre Kilgore
 */

/*
 * History and Acknowledgments
 *
 * The original Linux driver क्रम SQ905 based cameras was written by
 * Marcell Lengyel and further developed by many other contributors
 * and is available from http://sourceक्रमge.net/projects/sqcam/
 *
 * This driver takes advantage of the reverse engineering work करोne क्रम
 * that driver and क्रम libgphoto2 but shares no code with them.
 *
 * This driver has used as a base the finepix driver and other gspca
 * based drivers and may still contain code fragments taken from those
 * drivers.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "sq905"

#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश "gspca.h"

MODULE_AUTHOR("Adam Baker <linux@baker-net.org.uk>, Theodore Kilgore <kilgota@auburn.edu>");
MODULE_DESCRIPTION("GSPCA/SQ905 USB Camera Driver");
MODULE_LICENSE("GPL");

/* Default समयouts, in ms */
#घोषणा SQ905_CMD_TIMEOUT 500
#घोषणा SQ905_DATA_TIMEOUT 1000

/* Maximum transfer size to use. */
#घोषणा SQ905_MAX_TRANSFER 0x8000
#घोषणा FRAME_HEADER_LEN 64

/* The known modes, or रेजिस्टरs. These go in the "value" slot. */

/* 00 is "none" obviously */

#घोषणा SQ905_BULK_READ	0x03	/* precedes any bulk पढ़ो */
#घोषणा SQ905_COMMAND	0x06	/* precedes the command codes below */
#घोषणा SQ905_PING	0x07	/* when पढ़ोing an "idling" command */
#घोषणा SQ905_READ_DONE 0xc0    /* ack bulk पढ़ो completed */

/* Any non-zero value in the bottom 2 bits of the 2nd byte of
 * the ID appears to indicate the camera can करो 640*480. If the
 * LSB of that byte is set the image is just upside करोwn, otherwise
 * it is rotated 180 degrees. */
#घोषणा SQ905_HIRES_MASK	0x00000300
#घोषणा SQ905_ORIENTATION_MASK	0x00000100

/* Some command codes. These go in the "index" slot. */

#घोषणा SQ905_ID      0xf0	/* asks क्रम model string */
#घोषणा SQ905_CONFIG  0x20	/* माला_लो photo alloc. table, not used here */
#घोषणा SQ905_DATA    0x30	/* accesses photo data, not used here */
#घोषणा SQ905_CLEAR   0xa0	/* clear everything */
#घोषणा SQ905_CAPTURE_LOW  0x60	/* Starts capture at 160x120 */
#घोषणा SQ905_CAPTURE_MED  0x61	/* Starts capture at 320x240 */
#घोषणा SQ905_CAPTURE_HIGH 0x62	/* Starts capture at 640x480 (some cams only) */
/* note that the capture command also controls the output dimensions */

/* Structure to hold all of our device specअगरic stuff */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */

	/*
	 * Driver stuff
	 */
	काष्ठा work_काष्ठा work_काष्ठा;
	काष्ठा workqueue_काष्ठा *work_thपढ़ो;
पूर्ण;

अटल काष्ठा v4l2_pix_क्रमmat sq905_mode[] = अणु
	अणु 160, 120, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 160,
		.sizeimage = 160 * 120,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
	अणु 320, 240, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
	अणु 640, 480, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण
पूर्ण;

/*
 * Send a command to the camera.
 */
अटल पूर्णांक sq905_command(काष्ठा gspca_dev *gspca_dev, u16 index)
अणु
	पूर्णांक ret;

	gspca_dev->usb_buf[0] = '\0';
	ret = usb_control_msg(gspca_dev->dev,
			      usb_sndctrlpipe(gspca_dev->dev, 0),
			      USB_REQ_SYNCH_FRAME,                /* request */
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      SQ905_COMMAND, index, gspca_dev->usb_buf, 1,
			      SQ905_CMD_TIMEOUT);
	अगर (ret < 0) अणु
		pr_err("%s: usb_control_msg failed (%d)\n", __func__, ret);
		वापस ret;
	पूर्ण

	ret = usb_control_msg(gspca_dev->dev,
			      usb_sndctrlpipe(gspca_dev->dev, 0),
			      USB_REQ_SYNCH_FRAME,                /* request */
			      USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      SQ905_PING, 0, gspca_dev->usb_buf, 1,
			      SQ905_CMD_TIMEOUT);
	अगर (ret < 0) अणु
		pr_err("%s: usb_control_msg failed 2 (%d)\n", __func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Acknowledge the end of a frame - see warning on sq905_command.
 */
अटल पूर्णांक sq905_ack_frame(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक ret;

	gspca_dev->usb_buf[0] = '\0';
	ret = usb_control_msg(gspca_dev->dev,
			      usb_sndctrlpipe(gspca_dev->dev, 0),
			      USB_REQ_SYNCH_FRAME,                /* request */
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      SQ905_READ_DONE, 0, gspca_dev->usb_buf, 1,
			      SQ905_CMD_TIMEOUT);
	अगर (ret < 0) अणु
		pr_err("%s: usb_control_msg failed (%d)\n", __func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *  request and पढ़ो a block of data - see warning on sq905_command.
 */
अटल पूर्णांक
sq905_पढ़ो_data(काष्ठा gspca_dev *gspca_dev, u8 *data, पूर्णांक size, पूर्णांक need_lock)
अणु
	पूर्णांक ret;
	पूर्णांक act_len = 0;

	gspca_dev->usb_buf[0] = '\0';
	अगर (need_lock)
		mutex_lock(&gspca_dev->usb_lock);
	ret = usb_control_msg(gspca_dev->dev,
			      usb_sndctrlpipe(gspca_dev->dev, 0),
			      USB_REQ_SYNCH_FRAME,                /* request */
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      SQ905_BULK_READ, size, gspca_dev->usb_buf,
			      1, SQ905_CMD_TIMEOUT);
	अगर (need_lock)
		mutex_unlock(&gspca_dev->usb_lock);
	अगर (ret < 0) अणु
		pr_err("%s: usb_control_msg failed (%d)\n", __func__, ret);
		वापस ret;
	पूर्ण
	ret = usb_bulk_msg(gspca_dev->dev,
			   usb_rcvbulkpipe(gspca_dev->dev, 0x81),
			   data, size, &act_len, SQ905_DATA_TIMEOUT);

	/* successful, it वापसs 0, otherwise  negative */
	अगर (ret < 0 || act_len != size) अणु
		pr_err("bulk read fail (%d) len %d/%d\n", ret, act_len, size);
		वापस -EIO;
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
अटल व्योम sq905_करोstream(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sd *dev = container_of(work, काष्ठा sd, work_काष्ठा);
	काष्ठा gspca_dev *gspca_dev = &dev->gspca_dev;
	पूर्णांक bytes_left; /* bytes reमुख्यing in current frame. */
	पूर्णांक data_len;   /* size to use क्रम the next पढ़ो. */
	पूर्णांक header_पढ़ो; /* true अगर we have alपढ़ोy पढ़ो the frame header. */
	पूर्णांक packet_type;
	पूर्णांक frame_sz;
	पूर्णांक ret;
	u8 *data;
	u8 *buffer;

	buffer = kदो_स्मृति(SQ905_MAX_TRANSFER, GFP_KERNEL);
	अगर (!buffer) अणु
		pr_err("Couldn't allocate USB buffer\n");
		जाओ quit_stream;
	पूर्ण

	frame_sz = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].sizeimage
			+ FRAME_HEADER_LEN;

	जबतक (gspca_dev->present && gspca_dev->streaming) अणु
#अगर_घोषित CONFIG_PM
		अगर (gspca_dev->frozen)
			अवरोध;
#पूर्ण_अगर
		/* request some data and then पढ़ो it until we have
		 * a complete frame. */
		bytes_left = frame_sz;
		header_पढ़ो = 0;

		/* Note we करो not check क्रम gspca_dev->streaming here, as
		   we must finish पढ़ोing an entire frame, otherwise the
		   next समय we stream we start पढ़ोing in the middle of a
		   frame. */
		जबतक (bytes_left > 0 && gspca_dev->present) अणु
			data_len = bytes_left > SQ905_MAX_TRANSFER ?
				SQ905_MAX_TRANSFER : bytes_left;
			ret = sq905_पढ़ो_data(gspca_dev, buffer, data_len, 1);
			अगर (ret < 0)
				जाओ quit_stream;
			gspca_dbg(gspca_dev, D_PACK,
				  "Got %d bytes out of %d for frame\n",
				  data_len, bytes_left);
			bytes_left -= data_len;
			data = buffer;
			अगर (!header_पढ़ो) अणु
				packet_type = FIRST_PACKET;
				/* The first 64 bytes of each frame are
				 * a header full of FF 00 bytes */
				data += FRAME_HEADER_LEN;
				data_len -= FRAME_HEADER_LEN;
				header_पढ़ो = 1;
			पूर्ण अन्यथा अगर (bytes_left == 0) अणु
				packet_type = LAST_PACKET;
			पूर्ण अन्यथा अणु
				packet_type = INTER_PACKET;
			पूर्ण
			gspca_frame_add(gspca_dev, packet_type,
					data, data_len);
			/* If entire frame fits in one packet we still
			   need to add a LAST_PACKET */
			अगर (packet_type == FIRST_PACKET &&
			    bytes_left == 0)
				gspca_frame_add(gspca_dev, LAST_PACKET,
						शून्य, 0);
		पूर्ण
		अगर (gspca_dev->present) अणु
			/* acknowledge the frame */
			mutex_lock(&gspca_dev->usb_lock);
			ret = sq905_ack_frame(gspca_dev);
			mutex_unlock(&gspca_dev->usb_lock);
			अगर (ret < 0)
				जाओ quit_stream;
		पूर्ण
	पूर्ण
quit_stream:
	अगर (gspca_dev->present) अणु
		mutex_lock(&gspca_dev->usb_lock);
		sq905_command(gspca_dev, SQ905_CLEAR);
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

	/* We करोn't use the buffer gspca allocates so make it small. */
	cam->bulk = 1;
	cam->bulk_size = 64;

	INIT_WORK(&dev->work_काष्ठा, sq905_करोstream);

	वापस 0;
पूर्ण

/* called on streamoff with alt==0 and on disconnect */
/* the usb_lock is held at entry - restore on निकास */
अटल व्योम sd_stop0(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *dev = (काष्ठा sd *) gspca_dev;

	/* रुको क्रम the work queue to terminate */
	mutex_unlock(&gspca_dev->usb_lock);
	/* This रुकोs क्रम sq905_करोstream to finish */
	destroy_workqueue(dev->work_thपढ़ो);
	dev->work_thपढ़ो = शून्य;
	mutex_lock(&gspca_dev->usb_lock);
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	u32 ident;
	पूर्णांक ret;

	/* connect to the camera and पढ़ो
	 * the model ID and process that and put it away.
	 */
	ret = sq905_command(gspca_dev, SQ905_CLEAR);
	अगर (ret < 0)
		वापस ret;
	ret = sq905_command(gspca_dev, SQ905_ID);
	अगर (ret < 0)
		वापस ret;
	ret = sq905_पढ़ो_data(gspca_dev, gspca_dev->usb_buf, 4, 0);
	अगर (ret < 0)
		वापस ret;
	/* usb_buf is allocated with kदो_स्मृति so is aligned.
	 * Camera model number is the right way round अगर we assume this
	 * reverse engineered ID is supposed to be big endian. */
	ident = be32_to_cpup((__be32 *)gspca_dev->usb_buf);
	ret = sq905_command(gspca_dev, SQ905_CLEAR);
	अगर (ret < 0)
		वापस ret;
	gspca_dbg(gspca_dev, D_CONF, "SQ905 camera ID %08x detected\n", ident);
	gspca_dev->cam.cam_mode = sq905_mode;
	gspca_dev->cam.nmodes = ARRAY_SIZE(sq905_mode);
	अगर (!(ident & SQ905_HIRES_MASK))
		gspca_dev->cam.nmodes--;

	अगर (ident & SQ905_ORIENTATION_MASK)
		gspca_dev->cam.input_flags = V4L2_IN_ST_VFLIP;
	अन्यथा
		gspca_dev->cam.input_flags = V4L2_IN_ST_VFLIP |
					     V4L2_IN_ST_HFLIP;
	वापस 0;
पूर्ण

/* Set up क्रम getting frames. */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *dev = (काष्ठा sd *) gspca_dev;
	पूर्णांक ret;

	/* "Open the shutter" and set size, to start capture */
	चयन (gspca_dev->curr_mode) अणु
	शेष:
/*	हाल 2: */
		gspca_dbg(gspca_dev, D_STREAM, "Start streaming at high resolution\n");
		ret = sq905_command(&dev->gspca_dev, SQ905_CAPTURE_HIGH);
		अवरोध;
	हाल 1:
		gspca_dbg(gspca_dev, D_STREAM, "Start streaming at medium resolution\n");
		ret = sq905_command(&dev->gspca_dev, SQ905_CAPTURE_MED);
		अवरोध;
	हाल 0:
		gspca_dbg(gspca_dev, D_STREAM, "Start streaming at low resolution\n");
		ret = sq905_command(&dev->gspca_dev, SQ905_CAPTURE_LOW);
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
	अणुUSB_DEVICE(0x2770, 0x9120)पूर्ण,
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
