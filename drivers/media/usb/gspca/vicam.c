<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * gspca ViCam subdriver
 *
 * Copyright (C) 2011 Hans de Goede <hdegoede@redhat.com>
 *
 * Based on the usbvideo vicam driver, which is:
 *
 * Copyright (c) 2002 Joe Burks (jburks@wavicle.org),
 *                    Chris Cheney (chris.cheney@gmail.com),
 *                    Pavel Machek (pavel@ucw.cz),
 *                    John Tyner (jtyner@cs.ucr.edu),
 *                    Monroe Williams (monroe@pobox.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "vicam"
#घोषणा HEADER_SIZE 64

#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश <linux/firmware.h>
#समावेश <linux/ihex.h>
#समावेश "gspca.h"

#घोषणा VICAM_FIRMWARE "vicam/firmware.fw"

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("GSPCA ViCam USB Camera Driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(VICAM_FIRMWARE);

काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */
	काष्ठा work_काष्ठा work_काष्ठा;
पूर्ण;

/* The vicam sensor has a resolution of 512 x 244, with I believe square
   pixels, but this is क्रमced to a 4:3 ratio by optics. So it has
   non square pixels :( */
अटल काष्ठा v4l2_pix_क्रमmat vicam_mode[] = अणु
	अणु 256, 122, V4L2_PIX_FMT_SGRBG8, V4L2_FIELD_NONE,
		.bytesperline = 256,
		.sizeimage = 256 * 122,
		.colorspace = V4L2_COLORSPACE_SRGB,पूर्ण,
	/* 2 modes with somewhat more square pixels */
	अणु 256, 200, V4L2_PIX_FMT_SGRBG8, V4L2_FIELD_NONE,
		.bytesperline = 256,
		.sizeimage = 256 * 200,
		.colorspace = V4L2_COLORSPACE_SRGB,पूर्ण,
	अणु 256, 240, V4L2_PIX_FMT_SGRBG8, V4L2_FIELD_NONE,
		.bytesperline = 256,
		.sizeimage = 256 * 240,
		.colorspace = V4L2_COLORSPACE_SRGB,पूर्ण,
#अगर 0   /* This mode has extremely non square pixels, testing use only */
	अणु 512, 122, V4L2_PIX_FMT_SGRBG8, V4L2_FIELD_NONE,
		.bytesperline = 512,
		.sizeimage = 512 * 122,
		.colorspace = V4L2_COLORSPACE_SRGB,पूर्ण,
#पूर्ण_अगर
	अणु 512, 244, V4L2_PIX_FMT_SGRBG8, V4L2_FIELD_NONE,
		.bytesperline = 512,
		.sizeimage = 512 * 244,
		.colorspace = V4L2_COLORSPACE_SRGB,पूर्ण,
पूर्ण;

अटल पूर्णांक vicam_control_msg(काष्ठा gspca_dev *gspca_dev, u8 request,
	u16 value, u16 index, u8 *data, u16 len)
अणु
	पूर्णांक ret;

	ret = usb_control_msg(gspca_dev->dev,
			      usb_sndctrlpipe(gspca_dev->dev, 0),
			      request,
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      value, index, data, len, 1000);
	अगर (ret < 0)
		pr_err("control msg req %02X error %d\n", request, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक vicam_set_camera_घातer(काष्ठा gspca_dev *gspca_dev, पूर्णांक state)
अणु
	पूर्णांक ret;

	ret = vicam_control_msg(gspca_dev, 0x50, state, 0, शून्य, 0);
	अगर (ret < 0)
		वापस ret;

	अगर (state)
		ret = vicam_control_msg(gspca_dev, 0x55, 1, 0, शून्य, 0);

	वापस ret;
पूर्ण

/*
 *  request and पढ़ो a block of data
 */
अटल पूर्णांक vicam_पढ़ो_frame(काष्ठा gspca_dev *gspca_dev, u8 *data, पूर्णांक size)
अणु
	पूर्णांक ret, unscaled_height, act_len = 0;
	u8 *req_data = gspca_dev->usb_buf;
	s32 expo = v4l2_ctrl_g_ctrl(gspca_dev->exposure);
	s32 gain = v4l2_ctrl_g_ctrl(gspca_dev->gain);

	स_रखो(req_data, 0, 16);
	req_data[0] = gain;
	अगर (gspca_dev->pixfmt.width == 256)
		req_data[1] |= 0x01; /* low nibble x-scale */
	अगर (gspca_dev->pixfmt.height <= 122) अणु
		req_data[1] |= 0x10; /* high nibble y-scale */
		unscaled_height = gspca_dev->pixfmt.height * 2;
	पूर्ण अन्यथा
		unscaled_height = gspca_dev->pixfmt.height;
	req_data[2] = 0x90; /* unknown, करोes not seem to करो anything */
	अगर (unscaled_height <= 200)
		req_data[3] = 0x06; /* vend? */
	अन्यथा अगर (unscaled_height <= 242) /* Yes 242 not 240 */
		req_data[3] = 0x07; /* vend? */
	अन्यथा /* Up to 244 lines with req_data[3] == 0x08 */
		req_data[3] = 0x08; /* vend? */

	अगर (expo < 256) अणु
		/* Frame rate maxed out, use partial frame expo समय */
		req_data[4] = 255 - expo;
		req_data[5] = 0x00;
		req_data[6] = 0x00;
		req_data[7] = 0x01;
	पूर्ण अन्यथा अणु
		/* Modअगरy frame rate */
		req_data[4] = 0x00;
		req_data[5] = 0x00;
		req_data[6] = expo & 0xFF;
		req_data[7] = expo >> 8;
	पूर्ण
	req_data[8] = ((244 - unscaled_height) / 2) & ~0x01; /* vstart */
	/* bytes 9-15 करो not seem to affect exposure or image quality */

	mutex_lock(&gspca_dev->usb_lock);
	ret = vicam_control_msg(gspca_dev, 0x51, 0x80, 0, req_data, 16);
	mutex_unlock(&gspca_dev->usb_lock);
	अगर (ret < 0)
		वापस ret;

	ret = usb_bulk_msg(gspca_dev->dev,
			   usb_rcvbulkpipe(gspca_dev->dev, 0x81),
			   data, size, &act_len, 10000);
	/* successful, it वापसs 0, otherwise  negative */
	अगर (ret < 0 || act_len != size) अणु
		pr_err("bulk read fail (%d) len %d/%d\n",
		       ret, act_len, size);
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
 * as the cameras controls are only written from the workqueue.
 */
अटल व्योम vicam_करोstream(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sd *sd = container_of(work, काष्ठा sd, work_काष्ठा);
	काष्ठा gspca_dev *gspca_dev = &sd->gspca_dev;
	पूर्णांक ret, frame_sz;
	u8 *buffer;

	frame_sz = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].sizeimage +
		   HEADER_SIZE;
	buffer = kदो_स्मृति(frame_sz, GFP_KERNEL);
	अगर (!buffer) अणु
		pr_err("Couldn't allocate USB buffer\n");
		जाओ निकास;
	पूर्ण

	जबतक (gspca_dev->present && gspca_dev->streaming) अणु
#अगर_घोषित CONFIG_PM
		अगर (gspca_dev->frozen)
			अवरोध;
#पूर्ण_अगर
		ret = vicam_पढ़ो_frame(gspca_dev, buffer, frame_sz);
		अगर (ret < 0)
			अवरोध;

		/* Note the frame header contents seem to be completely
		   स्थिरant, they करो not change with either image, or
		   settings. So we simply discard it. The frames have
		   a very similar 64 byte footer, which we करोn't even
		   bother पढ़ोing from the cam */
		gspca_frame_add(gspca_dev, FIRST_PACKET,
				buffer + HEADER_SIZE,
				frame_sz - HEADER_SIZE);
		gspca_frame_add(gspca_dev, LAST_PACKET, शून्य, 0);
	पूर्ण
निकास:
	kमुक्त(buffer);
पूर्ण

/* This function is called at probe समय just beक्रमe sd_init */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा cam *cam = &gspca_dev->cam;
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;

	/* We करोn't use the buffer gspca allocates so make it small. */
	cam->bulk = 1;
	cam->bulk_size = 64;
	cam->cam_mode = vicam_mode;
	cam->nmodes = ARRAY_SIZE(vicam_mode);

	INIT_WORK(&sd->work_काष्ठा, vicam_करोstream);

	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा ihex_binrec *rec;
	स्थिर काष्ठा firmware *fw;
	u8 *firmware_buf;

	ret = request_ihex_firmware(&fw, VICAM_FIRMWARE,
				    &gspca_dev->dev->dev);
	अगर (ret) अणु
		pr_err("Failed to load \"vicam/firmware.fw\": %d\n", ret);
		वापस ret;
	पूर्ण

	firmware_buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!firmware_buf) अणु
		ret = -ENOMEM;
		जाओ निकास;
	पूर्ण
	क्रम (rec = (व्योम *)fw->data; rec; rec = ihex_next_binrec(rec)) अणु
		स_नकल(firmware_buf, rec->data, be16_to_cpu(rec->len));
		ret = vicam_control_msg(gspca_dev, 0xff, 0, 0, firmware_buf,
					be16_to_cpu(rec->len));
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	kमुक्त(firmware_buf);
निकास:
	release_firmware(fw);
	वापस ret;
पूर्ण

/* Set up क्रम getting frames. */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	पूर्णांक ret;

	ret = vicam_set_camera_घातer(gspca_dev, 1);
	अगर (ret < 0)
		वापस ret;

	schedule_work(&sd->work_काष्ठा);

	वापस 0;
पूर्ण

/* called on streamoff with alt==0 and on disconnect */
/* the usb_lock is held at entry - restore on निकास */
अटल व्योम sd_stop0(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *dev = (काष्ठा sd *)gspca_dev;

	/* रुको क्रम the work queue to terminate */
	mutex_unlock(&gspca_dev->usb_lock);
	/* This रुकोs क्रम vicam_करोstream to finish */
	flush_work(&dev->work_काष्ठा);
	mutex_lock(&gspca_dev->usb_lock);

	अगर (gspca_dev->present)
		vicam_set_camera_घातer(gspca_dev, 0);
पूर्ण

अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 2);
	gspca_dev->exposure = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_EXPOSURE, 0, 2047, 1, 256);
	gspca_dev->gain = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_GAIN, 0, 255, 1, 200);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण
	वापस 0;
पूर्ण

/* Table of supported USB devices */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x04c1, 0x009d)पूर्ण,
	अणुUSB_DEVICE(0x0602, 0x1001)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, device_table);

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name   = MODULE_NAME,
	.config = sd_config,
	.init   = sd_init,
	.init_controls = sd_init_controls,
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
