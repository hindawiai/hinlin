<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Fujअगरilm Finepix subdriver
 *
 * Copyright (C) 2008 Frank Zago
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "finepix"

#समावेश "gspca.h"

MODULE_AUTHOR("Frank Zago <frank@zago.net>");
MODULE_DESCRIPTION("Fujifilm FinePix USB V4L2 driver");
MODULE_LICENSE("GPL");

/* Default समयout, in ms */
#घोषणा FPIX_TIMEOUT 250

/* Maximum transfer size to use. The winकरोws driver पढ़ोs by chunks of
 * 0x2000 bytes, so करो the same. Note: पढ़ोing more seems to work
 * too. */
#घोषणा FPIX_MAX_TRANSFER 0x2000

/* Structure to hold all of our device specअगरic stuff */
काष्ठा usb_fpix अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */

	काष्ठा work_काष्ठा work_काष्ठा;
पूर्ण;

/* Delay after which claim the next frame. If the delay is too small,
 * the camera will वापस old frames. On the 4800Z, 20ms is bad, 25ms
 * will fail every 4 or 5 frames, but 30ms is perfect. On the A210,
 * 30ms is bad जबतक 35ms is perfect. */
#घोषणा NEXT_FRAME_DELAY 35

/* These cameras only support 320x200. */
अटल स्थिर काष्ठा v4l2_pix_क्रमmat fpix_mode[1] = अणु
	अणु 320, 240, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण
पूर्ण;

/* send a command to the webcam */
अटल पूर्णांक command(काष्ठा gspca_dev *gspca_dev,
		पूर्णांक order)	/* 0: reset, 1: frame request */
अणु
	अटल u8 order_values[2][12] = अणु
		अणु0xc6, 0, 0, 0, 0, 0, 0,    0, 0x20, 0, 0, 0पूर्ण,	/* reset */
		अणु0xd3, 0, 0, 0, 0, 0, 0, 0x01,    0, 0, 0, 0पूर्ण,	/* fr req */
	पूर्ण;

	स_नकल(gspca_dev->usb_buf, order_values[order], 12);
	वापस usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			USB_REQ_GET_STATUS,
			USB_सूची_OUT | USB_TYPE_CLASS |
			USB_RECIP_INTERFACE, 0, 0, gspca_dev->usb_buf,
			12, FPIX_TIMEOUT);
पूर्ण

/*
 * This function is called as a workqueue function and runs whenever the camera
 * is streaming data. Because it is a workqueue function it is allowed to sleep
 * so we can use synchronous USB calls. To aव्योम possible collisions with other
 * thपढ़ोs attempting to use gspca_dev->usb_buf we take the usb_lock when
 * perक्रमming USB operations using it. In practice we करोn't really need this
 * as the camera करोesn't provide any controls.
 */
अटल व्योम करोstream(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usb_fpix *dev = container_of(work, काष्ठा usb_fpix, work_काष्ठा);
	काष्ठा gspca_dev *gspca_dev = &dev->gspca_dev;
	काष्ठा urb *urb = gspca_dev->urb[0];
	u8 *data = urb->transfer_buffer;
	पूर्णांक ret = 0;
	पूर्णांक len;

	gspca_dbg(gspca_dev, D_STREAM, "dostream started\n");

	/* loop पढ़ोing a frame */
again:
	जबतक (gspca_dev->present && gspca_dev->streaming) अणु
#अगर_घोषित CONFIG_PM
		अगर (gspca_dev->frozen)
			अवरोध;
#पूर्ण_अगर

		/* request a frame */
		mutex_lock(&gspca_dev->usb_lock);
		ret = command(gspca_dev, 1);
		mutex_unlock(&gspca_dev->usb_lock);
		अगर (ret < 0)
			अवरोध;
#अगर_घोषित CONFIG_PM
		अगर (gspca_dev->frozen)
			अवरोध;
#पूर्ण_अगर
		अगर (!gspca_dev->present || !gspca_dev->streaming)
			अवरोध;

		/* the frame comes in parts */
		क्रम (;;) अणु
			ret = usb_bulk_msg(gspca_dev->dev,
					urb->pipe,
					data,
					FPIX_MAX_TRANSFER,
					&len, FPIX_TIMEOUT);
			अगर (ret < 0) अणु
				/* Most of the समय we get a समयout
				 * error. Just restart. */
				जाओ again;
			पूर्ण
#अगर_घोषित CONFIG_PM
			अगर (gspca_dev->frozen)
				जाओ out;
#पूर्ण_अगर
			अगर (!gspca_dev->present || !gspca_dev->streaming)
				जाओ out;
			अगर (len < FPIX_MAX_TRANSFER ||
				(data[len - 2] == 0xff &&
					data[len - 1] == 0xd9)) अणु

				/* If the result is less than what was asked
				 * क्रम, then it's the end of the
				 * frame. Someबार the jpeg is not complete,
				 * but there's nothing we can करो. We also end
				 * here अगर the the jpeg ends right at the end
				 * of the frame. */
				gspca_frame_add(gspca_dev, LAST_PACKET,
						data, len);
				अवरोध;
			पूर्ण

			/* got a partial image */
			gspca_frame_add(gspca_dev,
					gspca_dev->last_packet_type
						== LAST_PACKET
					? FIRST_PACKET : INTER_PACKET,
					data, len);
		पूर्ण

		/* We must रुको beक्रमe trying पढ़ोing the next
		 * frame. If we करोn't, or अगर the delay is too लघु,
		 * the camera will disconnect. */
		msleep(NEXT_FRAME_DELAY);
	पूर्ण

out:
	gspca_dbg(gspca_dev, D_STREAM, "dostream stopped\n");
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_fpix *dev = (काष्ठा usb_fpix *) gspca_dev;
	काष्ठा cam *cam = &gspca_dev->cam;

	cam->cam_mode = fpix_mode;
	cam->nmodes = 1;
	cam->bulk = 1;
	cam->bulk_size = FPIX_MAX_TRANSFER;

	INIT_WORK(&dev->work_काष्ठा, करोstream);

	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	वापस 0;
पूर्ण

/* start the camera */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा usb_fpix *dev = (काष्ठा usb_fpix *) gspca_dev;
	पूर्णांक ret, len;

	/* Init the device */
	ret = command(gspca_dev, 0);
	अगर (ret < 0) अणु
		pr_err("init failed %d\n", ret);
		वापस ret;
	पूर्ण

	/* Read the result of the command. Ignore the result, क्रम it
	 * varies with the device. */
	ret = usb_bulk_msg(gspca_dev->dev,
			gspca_dev->urb[0]->pipe,
			gspca_dev->urb[0]->transfer_buffer,
			FPIX_MAX_TRANSFER, &len,
			FPIX_TIMEOUT);
	अगर (ret < 0) अणु
		pr_err("usb_bulk_msg failed %d\n", ret);
		वापस ret;
	पूर्ण

	/* Request a frame, but करोn't पढ़ो it */
	ret = command(gspca_dev, 1);
	अगर (ret < 0) अणु
		pr_err("frame request failed %d\n", ret);
		वापस ret;
	पूर्ण

	/* Again, reset bulk in endpoपूर्णांक */
	usb_clear_halt(gspca_dev->dev, gspca_dev->urb[0]->pipe);

	schedule_work(&dev->work_काष्ठा);

	वापस 0;
पूर्ण

/* called on streamoff with alt==0 and on disconnect */
/* the usb_lock is held at entry - restore on निकास */
अटल व्योम sd_stop0(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा usb_fpix *dev = (काष्ठा usb_fpix *) gspca_dev;

	/* रुको क्रम the work queue to terminate */
	mutex_unlock(&gspca_dev->usb_lock);
	flush_work(&dev->work_काष्ठा);
	mutex_lock(&gspca_dev->usb_lock);
पूर्ण

/* Table of supported USB devices */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x04cb, 0x0104)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x0109)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x010b)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x010f)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x0111)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x0113)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x0115)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x0117)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x0119)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x011b)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x011d)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x0121)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x0123)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x0125)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x0127)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x0129)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x012b)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x012d)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x012f)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x0131)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x013b)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x013d)पूर्ण,
	अणुUSB_DEVICE(0x04cb, 0x013f)पूर्ण,
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
			माप(काष्ठा usb_fpix),
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
