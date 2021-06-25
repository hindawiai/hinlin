<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Subdriver क्रम Scopium astro-camera (DTCS033, 0547:7303)
 *
 * Copyright (C) 2014 Robert Butora (robert.butora.fi@gmail.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#घोषणा MODULE_NAME "dtcs033"
#समावेश "gspca.h"

MODULE_AUTHOR("Robert Butora <robert.butora.fi@gmail.com>");
MODULE_DESCRIPTION("Scopium DTCS033 astro-cam USB Camera Driver");
MODULE_LICENSE("GPL");

काष्ठा dtcs033_usb_requests अणु
	u8 bRequestType;
	u8 bRequest;
	u16 wValue;
	u16 wIndex;
	u16 wLength;
पूर्ण;

/* send a usb request */
अटल व्योम reg_rw(काष्ठा gspca_dev *gspca_dev,
		u8 bRequestType, u8 bRequest,
		u16 wValue, u16 wIndex, u16 wLength)
अणु
	काष्ठा usb_device *udev = gspca_dev->dev;
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;

	ret = usb_control_msg(udev,
		usb_rcvctrlpipe(udev, 0),
		bRequest,
		bRequestType,
		wValue, wIndex,
		gspca_dev->usb_buf, wLength, 500);

	अगर (ret < 0) अणु
		gspca_dev->usb_err = ret;
		pr_err("usb_control_msg error %d\n", ret);
	पूर्ण

	वापस;
पूर्ण
/* send several usb in/out requests */
अटल पूर्णांक reg_reqs(काष्ठा gspca_dev *gspca_dev,
		    स्थिर काष्ठा dtcs033_usb_requests *preqs, पूर्णांक n_reqs)
अणु
	पूर्णांक i = 0;
	स्थिर काष्ठा dtcs033_usb_requests *preq;

	जबतक ((i < n_reqs) && (gspca_dev->usb_err >= 0)) अणु

		preq = &preqs[i];

		reg_rw(gspca_dev, preq->bRequestType, preq->bRequest,
			preq->wValue, preq->wIndex, preq->wLength);

		अगर (gspca_dev->usb_err < 0) अणु

			gspca_err(gspca_dev, "usb error request no: %d / %d\n",
				  i, n_reqs);
		पूर्ण अन्यथा अगर (preq->bRequestType & USB_सूची_IN) अणु

			gspca_dbg(gspca_dev, D_STREAM,
				  "USB IN (%d) returned[%d] %3ph %s",
				  i,
				  preq->wLength,
				  gspca_dev->usb_buf,
				  preq->wLength > 3 ? "...\n" : "\n");
		पूर्ण

		i++;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

/* -- subdriver पूर्णांकerface implementation -- */

#घोषणा DT_COLS (640)
अटल स्थिर काष्ठा v4l2_pix_क्रमmat dtcs033_mode[] = अणु
	/* raw Bayer patterned output */
	अणुDT_COLS, 480, V4L2_PIX_FMT_GREY, V4L2_FIELD_NONE,
		.bytesperline = DT_COLS,
		.sizeimage = DT_COLS*480,
		.colorspace = V4L2_COLORSPACE_SRGB,
	पूर्ण,
	/* this mode will demosaic the Bayer pattern */
	अणुDT_COLS, 480, V4L2_PIX_FMT_SRGGB8, V4L2_FIELD_NONE,
		.bytesperline = DT_COLS,
		.sizeimage = DT_COLS*480,
		.colorspace = V4L2_COLORSPACE_SRGB,
	पूर्ण
पूर्ण;

/* config called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
		स्थिर काष्ठा usb_device_id *id)
अणु
	gspca_dev->cam.cam_mode = dtcs033_mode;
	gspca_dev->cam.nmodes = ARRAY_SIZE(dtcs033_mode);

	gspca_dev->cam.bulk = 1;
	gspca_dev->cam.bulk_nurbs = 1;
	gspca_dev->cam.bulk_size = DT_COLS*512;

	वापस 0;
पूर्ण

/* init called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	वापस 0;
पूर्ण

/* start stop the camera */
अटल पूर्णांक  dtcs033_start(काष्ठा gspca_dev *gspca_dev);
अटल व्योम dtcs033_stopN(काष्ठा gspca_dev *gspca_dev);

/* पूर्णांकercept camera image data */
अटल व्योम dtcs033_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,  /* packet data */
			पूर्णांक len)   /* packet data length */
अणु
	/* drop incomplete frames */
	अगर (len != DT_COLS*512) अणु
		gspca_dev->last_packet_type = DISCARD_PACKET;
		/* gspca.c: discard invalidates the whole frame. */
		वापस;
	पूर्ण

	/* क्रमward complete frames */
	gspca_frame_add(gspca_dev, FIRST_PACKET, शून्य, 0);
	gspca_frame_add(gspca_dev, INTER_PACKET,
		data + 16*DT_COLS,
		len  - 32*DT_COLS); /* skip first & last 16 lines */
	gspca_frame_add(gspca_dev, LAST_PACKET,  शून्य, 0);

	वापस;
पूर्ण

/* -- controls: exposure and gain -- */

अटल व्योम dtcs033_setexposure(काष्ठा gspca_dev *gspca_dev,
			s32 expo, s32 gain)
अणु
	/* gain [dB] encoding */
	u16 sGain   = (u16)gain;
	u16 gainVal = 224+(sGain-14)*(768-224)/(33-14);
	u16 wIndex =  0x0100|(0x00FF&gainVal);
	u16 wValue = (0xFF00&gainVal)>>8;

	/* exposure समय [msec] encoding */
	u16 sXTime   = (u16)expo;
	u16 xसमयVal = (524*(150-(sXTime-1)))/150;

	स्थिर u8 bRequestType =
		USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE;
	स्थिर u8 bRequest = 0x18;

	reg_rw(gspca_dev,
		bRequestType, bRequest, wValue, wIndex, 0);
	अगर (gspca_dev->usb_err < 0)
		gspca_err(gspca_dev, "usb error in setexposure(gain) sequence\n");

	reg_rw(gspca_dev,
		bRequestType, bRequest, (xसमयVal<<4), 0x6300, 0);
	अगर (gspca_dev->usb_err < 0)
		gspca_err(gspca_dev, "usb error in setexposure(time) sequence\n");
पूर्ण

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;/* !! must be the first item */

	/* exposure & gain controls */
	काष्ठा अणु
		काष्ठा v4l2_ctrl *exposure;
		काष्ठा v4l2_ctrl *gain;
	पूर्ण;
पूर्ण;

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
	container_of(ctrl->handler,
		काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dev->usb_err = 0;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE:
		dtcs033_setexposure(gspca_dev,
				ctrl->val, sd->gain->val);
		अवरोध;
	हाल V4L2_CID_GAIN:
		dtcs033_setexposure(gspca_dev,
				sd->exposure->val, ctrl->val);
		अवरोध;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.s_ctrl = sd_s_ctrl,
पूर्ण;

अटल पूर्णांक dtcs033_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 2);
	/*                               min max step शेष */
	sd->exposure = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				V4L2_CID_EXPOSURE,
				1,  150,  1,  75);/* [msec] */
	sd->gain     = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				V4L2_CID_GAIN,
				14,  33,  1,  24);/* [dB] */
	अगर (hdl->error) अणु
		gspca_err(gspca_dev, "Could not initialize controls: %d\n",
			  hdl->error);
		वापस hdl->error;
	पूर्ण

	v4l2_ctrl_cluster(2, &sd->exposure);
	वापस 0;
पूर्ण

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name     = MODULE_NAME,
	.config   = sd_config,
	.init     = sd_init,
	.start    = dtcs033_start,
	.stopN    = dtcs033_stopN,
	.pkt_scan = dtcs033_pkt_scan,
	.init_controls = dtcs033_init_controls,
पूर्ण;

/* -- module initialisation -- */

अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x0547, 0x7303)पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, device_table);

/* device connect */
अटल पूर्णांक sd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	वापस gspca_dev_probe(पूर्णांकf, id,
			&sd_desc, माप(काष्ठा sd),
			THIS_MODULE);
पूर्ण

अटल काष्ठा usb_driver sd_driver = अणु
	.name       = MODULE_NAME,
	.id_table   = device_table,
	.probe      = sd_probe,
	.disconnect   = gspca_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend      = gspca_suspend,
	.resume       = gspca_resume,
	.reset_resume = gspca_resume,
#पूर्ण_अगर
पूर्ण;
module_usb_driver(sd_driver);


/* ---------------------------------------------------------
 USB requests to start/stop the camera [USB 2.0 spec Ch.9].

 bRequestType :
 0x40 =  USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
 0xC0 =  USB_सूची_IN  | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
*/
अटल स्थिर काष्ठा dtcs033_usb_requests dtcs033_start_reqs[] = अणु
/* -- bRequest,wValue,wIndex,wLength */
अणु 0x40, 0x01, 0x0001, 0x000F, 0x0000 पूर्ण,
अणु 0x40, 0x01, 0x0000, 0x000F, 0x0000 पूर्ण,
अणु 0x40, 0x01, 0x0001, 0x000F, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x7F00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x1001, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x0004, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x7F01, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x30E0, 0x0009, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0500, 0x012C, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0380, 0x0200, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x035C, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x05C0, 0x0438, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0440, 0x0500, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x0668, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x0700, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x0800, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x0900, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x0A00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x0B00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x30E0, 0x6009, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0500, 0x612C, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x2090, 0x6274, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x05C0, 0x6338, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6400, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x05C0, 0x6538, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6600, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0680, 0x6744, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6800, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6900, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6A00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6B00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6C00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6D00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6E00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x808C, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0010, 0x8101, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x30E0, 0x8200, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0810, 0x832C, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0680, 0x842B, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x8500, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x8600, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0280, 0x8715, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x880C, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0010, 0x8901, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x30E0, 0x8A00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0810, 0x8B2C, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0680, 0x8C2B, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x8D00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x8E00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0280, 0x8F15, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0010, 0xD040, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0xD100, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x00B0, 0xD20A, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0xD300, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x30E2, 0xD40D, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0001, 0xD5C0, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x00A0, 0xD60A, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0xD700, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x7F00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x1501, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0001, 0x01FF, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x0200, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x0304, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x1101, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x1201, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x1300, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x1400, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x1601, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x1800, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x1900, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x1A00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x2000, 0x1B00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x1C00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x2100, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x00C0, 0x228E, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x3001, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0010, 0x3101, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0008, 0x3301, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x3400, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0012, 0x3549, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x3620, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0001, 0x3700, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x4000, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0xFFFF, 0x41FF, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0xFFFF, 0x42FF, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x500F, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x2272, 0x5108, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x2272, 0x5208, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0xFFFF, 0x53FF, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0xFFFF, 0x54FF, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6000, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6102, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0010, 0x6214, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0C80, 0x6300, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6401, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0680, 0x6551, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0xFFFF, 0x66FF, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6702, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0010, 0x6800, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6900, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6A00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6B00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6C00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6D01, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6E00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x6F00, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x7000, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0001, 0x7118, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x2001, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x1101, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x1301, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x1300, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x1501, 0x0000 पूर्ण,
अणु 0xC0, 0x11, 0x0000, 0x24C0, 0x0003 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x3000, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x3620, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x1501, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0010, 0x6300, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0002, 0x01F0, 0x0000 पूर्ण,
अणु 0x40, 0x01, 0x0003, 0x000F, 0x0000 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dtcs033_usb_requests dtcs033_stop_reqs[] = अणु
/* -- bRequest,wValue,wIndex,wLength */
अणु 0x40, 0x01, 0x0001, 0x000F, 0x0000 पूर्ण,
अणु 0x40, 0x01, 0x0000, 0x000F, 0x0000 पूर्ण,
अणु 0x40, 0x18, 0x0000, 0x0003, 0x0000 पूर्ण
पूर्ण;
अटल पूर्णांक dtcs033_start(काष्ठा gspca_dev *gspca_dev)
अणु
	वापस reg_reqs(gspca_dev, dtcs033_start_reqs,
		ARRAY_SIZE(dtcs033_start_reqs));
पूर्ण

अटल व्योम dtcs033_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	reg_reqs(gspca_dev, dtcs033_stop_reqs,
		ARRAY_SIZE(dtcs033_stop_reqs));
	वापस;
पूर्ण
