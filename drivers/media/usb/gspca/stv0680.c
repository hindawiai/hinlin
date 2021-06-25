<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * STV0680 USB Camera Driver
 *
 * Copyright (C) 2009 Hans de Goede <hdegoede@redhat.com>
 *
 * This module is adapted from the in kernel v4l1 stv680 driver:
 *
 *  STV0680 USB Camera Driver, by Kevin Sisson (kjsisson@bellsouth.net)
 *
 * Thanks to STMicroelectronics क्रम inक्रमmation on the usb commands, and
 * to Steve Miller at STM क्रम his help and encouragement जबतक I was
 * writing this driver.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "stv0680"

#समावेश "gspca.h"

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("STV0680 USB Camera Driver");
MODULE_LICENSE("GPL");

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;		/* !! must be the first item */
	काष्ठा v4l2_pix_क्रमmat mode;
	u8 orig_mode;
	u8 video_mode;
	u8 current_mode;
पूर्ण;

अटल पूर्णांक stv_sndctrl(काष्ठा gspca_dev *gspca_dev, पूर्णांक set, u8 req, u16 val,
		       पूर्णांक size)
अणु
	पूर्णांक ret;
	u8 req_type = 0;
	अचिन्हित पूर्णांक pipe = 0;

	चयन (set) अणु
	हाल 0: /*  0xc1  */
		req_type = USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_ENDPOINT;
		pipe = usb_rcvctrlpipe(gspca_dev->dev, 0);
		अवरोध;
	हाल 1: /*  0x41  */
		req_type = USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_ENDPOINT;
		pipe = usb_sndctrlpipe(gspca_dev->dev, 0);
		अवरोध;
	हाल 2:	/*  0x80  */
		req_type = USB_सूची_IN | USB_RECIP_DEVICE;
		pipe = usb_rcvctrlpipe(gspca_dev->dev, 0);
		अवरोध;
	हाल 3:	/*  0x40  */
		req_type = USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE;
		pipe = usb_sndctrlpipe(gspca_dev->dev, 0);
		अवरोध;
	पूर्ण

	ret = usb_control_msg(gspca_dev->dev, pipe,
			      req, req_type,
			      val, 0, gspca_dev->usb_buf, size, 500);

	अगर ((ret < 0) && (req != 0x0a))
		pr_err("usb_control_msg error %i, request = 0x%x, error = %i\n",
		       set, req, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक stv0680_handle_error(काष्ठा gspca_dev *gspca_dev, पूर्णांक ret)
अणु
	stv_sndctrl(gspca_dev, 0, 0x80, 0, 0x02); /* Get Last Error */
	gspca_err(gspca_dev, "last error: %i,  command = 0x%x\n",
		  gspca_dev->usb_buf[0], gspca_dev->usb_buf[1]);
	वापस ret;
पूर्ण

अटल पूर्णांक stv0680_get_video_mode(काष्ठा gspca_dev *gspca_dev)
अणु
	/* Note not sure अगर this init of usb_buf is really necessary */
	स_रखो(gspca_dev->usb_buf, 0, 8);
	gspca_dev->usb_buf[0] = 0x0f;

	अगर (stv_sndctrl(gspca_dev, 0, 0x87, 0, 0x08) != 0x08) अणु
		gspca_err(gspca_dev, "Get_Camera_Mode failed\n");
		वापस stv0680_handle_error(gspca_dev, -EIO);
	पूर्ण

	वापस gspca_dev->usb_buf[0]; /* 01 = VGA, 03 = QVGA, 00 = CIF */
पूर्ण

अटल पूर्णांक stv0680_set_video_mode(काष्ठा gspca_dev *gspca_dev, u8 mode)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->current_mode == mode)
		वापस 0;

	स_रखो(gspca_dev->usb_buf, 0, 8);
	gspca_dev->usb_buf[0] = mode;

	अगर (stv_sndctrl(gspca_dev, 3, 0x07, 0x0100, 0x08) != 0x08) अणु
		gspca_err(gspca_dev, "Set_Camera_Mode failed\n");
		वापस stv0680_handle_error(gspca_dev, -EIO);
	पूर्ण

	/* Verअगरy we got what we've asked क्रम */
	अगर (stv0680_get_video_mode(gspca_dev) != mode) अणु
		gspca_err(gspca_dev, "Error setting camera video mode!\n");
		वापस -EIO;
	पूर्ण

	sd->current_mode = mode;

	वापस 0;
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam = &gspca_dev->cam;

	/* Give the camera some समय to settle, otherwise initialization will
	   fail on hotplug, and yes it really needs a full second. */
	msleep(1000);

	/* ping camera to be sure STV0680 is present */
	अगर (stv_sndctrl(gspca_dev, 0, 0x88, 0x5678, 0x02) != 0x02 ||
	    gspca_dev->usb_buf[0] != 0x56 || gspca_dev->usb_buf[1] != 0x78) अणु
		gspca_err(gspca_dev, "STV(e): camera ping failed!!\n");
		वापस stv0680_handle_error(gspca_dev, -ENODEV);
	पूर्ण

	/* get camera descriptor */
	अगर (stv_sndctrl(gspca_dev, 2, 0x06, 0x0200, 0x09) != 0x09)
		वापस stv0680_handle_error(gspca_dev, -ENODEV);

	अगर (stv_sndctrl(gspca_dev, 2, 0x06, 0x0200, 0x22) != 0x22 ||
	    gspca_dev->usb_buf[7] != 0xa0 || gspca_dev->usb_buf[8] != 0x23) अणु
		gspca_err(gspca_dev, "Could not get descriptor 0200\n");
		वापस stv0680_handle_error(gspca_dev, -ENODEV);
	पूर्ण
	अगर (stv_sndctrl(gspca_dev, 0, 0x8a, 0, 0x02) != 0x02)
		वापस stv0680_handle_error(gspca_dev, -ENODEV);
	अगर (stv_sndctrl(gspca_dev, 0, 0x8b, 0, 0x24) != 0x24)
		वापस stv0680_handle_error(gspca_dev, -ENODEV);
	अगर (stv_sndctrl(gspca_dev, 0, 0x85, 0, 0x10) != 0x10)
		वापस stv0680_handle_error(gspca_dev, -ENODEV);

	अगर (!(gspca_dev->usb_buf[7] & 0x09)) अणु
		gspca_err(gspca_dev, "Camera supports neither CIF nor QVGA mode\n");
		वापस -ENODEV;
	पूर्ण
	अगर (gspca_dev->usb_buf[7] & 0x01)
		gspca_dbg(gspca_dev, D_PROBE, "Camera supports CIF mode\n");
	अगर (gspca_dev->usb_buf[7] & 0x02)
		gspca_dbg(gspca_dev, D_PROBE, "Camera supports VGA mode\n");
	अगर (gspca_dev->usb_buf[7] & 0x04)
		gspca_dbg(gspca_dev, D_PROBE, "Camera supports QCIF mode\n");
	अगर (gspca_dev->usb_buf[7] & 0x08)
		gspca_dbg(gspca_dev, D_PROBE, "Camera supports QVGA mode\n");

	अगर (gspca_dev->usb_buf[7] & 0x01)
		sd->video_mode = 0x00; /* CIF */
	अन्यथा
		sd->video_mode = 0x03; /* QVGA */

	/* FW rev, ASIC rev, sensor ID  */
	gspca_dbg(gspca_dev, D_PROBE, "Firmware rev is %i.%i\n",
		  gspca_dev->usb_buf[0], gspca_dev->usb_buf[1]);
	gspca_dbg(gspca_dev, D_PROBE, "ASIC rev is %i.%i",
		  gspca_dev->usb_buf[2], gspca_dev->usb_buf[3]);
	gspca_dbg(gspca_dev, D_PROBE, "Sensor ID is %i",
		  (gspca_dev->usb_buf[4]*16) + (gspca_dev->usb_buf[5]>>4));


	ret = stv0680_get_video_mode(gspca_dev);
	अगर (ret < 0)
		वापस ret;
	sd->current_mode = sd->orig_mode = ret;

	ret = stv0680_set_video_mode(gspca_dev, sd->video_mode);
	अगर (ret < 0)
		वापस ret;

	/* Get mode details */
	अगर (stv_sndctrl(gspca_dev, 0, 0x8f, 0, 0x10) != 0x10)
		वापस stv0680_handle_error(gspca_dev, -EIO);

	cam->bulk = 1;
	cam->bulk_nurbs = 1; /* The cam cannot handle more */
	cam->bulk_size = (gspca_dev->usb_buf[0] << 24) |
			 (gspca_dev->usb_buf[1] << 16) |
			 (gspca_dev->usb_buf[2] << 8) |
			 (gspca_dev->usb_buf[3]);
	sd->mode.width = (gspca_dev->usb_buf[4] << 8) |
			 (gspca_dev->usb_buf[5]);  /* 322, 356, 644 */
	sd->mode.height = (gspca_dev->usb_buf[6] << 8) |
			  (gspca_dev->usb_buf[7]); /* 242, 292, 484 */
	sd->mode.pixelक्रमmat = V4L2_PIX_FMT_STV0680;
	sd->mode.field = V4L2_FIELD_NONE;
	sd->mode.bytesperline = sd->mode.width;
	sd->mode.sizeimage = cam->bulk_size;
	sd->mode.colorspace = V4L2_COLORSPACE_SRGB;

	/* origGain = gspca_dev->usb_buf[12]; */

	cam->cam_mode = &sd->mode;
	cam->nmodes = 1;


	ret = stv0680_set_video_mode(gspca_dev, sd->orig_mode);
	अगर (ret < 0)
		वापस ret;

	अगर (stv_sndctrl(gspca_dev, 2, 0x06, 0x0100, 0x12) != 0x12 ||
	    gspca_dev->usb_buf[8] != 0x53 || gspca_dev->usb_buf[9] != 0x05) अणु
		pr_err("Could not get descriptor 0100\n");
		वापस stv0680_handle_error(gspca_dev, -EIO);
	पूर्ण

	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	वापस 0;
पूर्ण

/* -- start the camera -- */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक ret;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	ret = stv0680_set_video_mode(gspca_dev, sd->video_mode);
	अगर (ret < 0)
		वापस ret;

	अगर (stv_sndctrl(gspca_dev, 0, 0x85, 0, 0x10) != 0x10)
		वापस stv0680_handle_error(gspca_dev, -EIO);

	/* Start stream at:
	   0x0000 = CIF (352x288)
	   0x0100 = VGA (640x480)
	   0x0300 = QVGA (320x240) */
	अगर (stv_sndctrl(gspca_dev, 1, 0x09, sd->video_mode << 8, 0x0) != 0x0)
		वापस stv0680_handle_error(gspca_dev, -EIO);

	वापस 0;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	/* This is a high priority command; it stops all lower order cmds */
	अगर (stv_sndctrl(gspca_dev, 1, 0x04, 0x0000, 0x0) != 0x0)
		stv0680_handle_error(gspca_dev, -EIO);
पूर्ण

अटल व्योम sd_stop0(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (!sd->gspca_dev.present)
		वापस;

	stv0680_set_video_mode(gspca_dev, sd->orig_mode);
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,
			पूर्णांक len)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/* Every now and then the camera sends a 16 byte packet, no idea
	   what it contains, but it is not image data, when this
	   happens the frame received beक्रमe this packet is corrupt,
	   so discard it. */
	अगर (len != sd->mode.sizeimage) अणु
		gspca_dev->last_packet_type = DISCARD_PACKET;
		वापस;
	पूर्ण

	/* Finish the previous frame, we करो this upon reception of the next
	   packet, even though it is alपढ़ोy complete so that the strange 16
	   byte packets send after a corrupt frame can discard it. */
	gspca_frame_add(gspca_dev, LAST_PACKET, शून्य, 0);

	/* Store the just received frame */
	gspca_frame_add(gspca_dev, FIRST_PACKET, data, len);
पूर्ण

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name = MODULE_NAME,
	.config = sd_config,
	.init = sd_init,
	.start = sd_start,
	.stopN = sd_stopN,
	.stop0 = sd_stop0,
	.pkt_scan = sd_pkt_scan,
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x0553, 0x0202)पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4007)पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, device_table);

/* -- device connect -- */
अटल पूर्णांक sd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	वापस gspca_dev_probe(पूर्णांकf, id, &sd_desc, माप(काष्ठा sd),
				THIS_MODULE);
पूर्ण

अटल काष्ठा usb_driver sd_driver = अणु
	.name = MODULE_NAME,
	.id_table = device_table,
	.probe = sd_probe,
	.disconnect = gspca_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend = gspca_suspend,
	.resume = gspca_resume,
	.reset_resume = gspca_resume,
#पूर्ण_अगर
पूर्ण;

module_usb_driver(sd_driver);
