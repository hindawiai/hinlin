<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Syntek DV4000 (STK014) subdriver
 *
 * Copyright (C) 2008 Jean-Francois Moine (http://moinejf.मुक्त.fr)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "stk014"

#समावेश "gspca.h"
#समावेश "jpeg.h"

MODULE_AUTHOR("Jean-Francois Moine <http://moinejf.free.fr>");
MODULE_DESCRIPTION("Syntek DV4000 (STK014) USB Camera Driver");
MODULE_LICENSE("GPL");

#घोषणा QUALITY 50

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */
	u8 jpeg_hdr[JPEG_HDR_SZ];
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_mode[] = अणु
	अणु320, 240, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
	अणु640, 480, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 0पूर्ण,
पूर्ण;

/* -- पढ़ो a रेजिस्टर -- */
अटल u8 reg_r(काष्ठा gspca_dev *gspca_dev,
			__u16 index)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस 0;
	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			0x00,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0x00,
			index,
			gspca_dev->usb_buf, 1,
			500);
	अगर (ret < 0) अणु
		pr_err("reg_r err %d\n", ret);
		gspca_dev->usb_err = ret;
		वापस 0;
	पूर्ण
	वापस gspca_dev->usb_buf[0];
पूर्ण

/* -- ग_लिखो a रेजिस्टर -- */
अटल व्योम reg_w(काष्ठा gspca_dev *gspca_dev,
			__u16 index, __u16 value)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			0x01,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value,
			index,
			शून्य,
			0,
			500);
	अगर (ret < 0) अणु
		pr_err("reg_w err %d\n", ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण

/* -- get a bulk value (4 bytes) -- */
अटल व्योम rcv_val(काष्ठा gspca_dev *gspca_dev,
			पूर्णांक ads)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;
	पूर्णांक alen, ret;

	reg_w(gspca_dev, 0x634, (ads >> 16) & 0xff);
	reg_w(gspca_dev, 0x635, (ads >> 8) & 0xff);
	reg_w(gspca_dev, 0x636, ads & 0xff);
	reg_w(gspca_dev, 0x637, 0);
	reg_w(gspca_dev, 0x638, 4);	/* len & 0xff */
	reg_w(gspca_dev, 0x639, 0);	/* len >> 8 */
	reg_w(gspca_dev, 0x63a, 0);
	reg_w(gspca_dev, 0x63b, 0);
	reg_w(gspca_dev, 0x630, 5);
	अगर (gspca_dev->usb_err < 0)
		वापस;
	ret = usb_bulk_msg(dev,
			usb_rcvbulkpipe(dev, 0x05),
			gspca_dev->usb_buf,
			4,		/* length */
			&alen,
			500);		/* समयout in milliseconds */
	अगर (ret < 0) अणु
		pr_err("rcv_val err %d\n", ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण

/* -- send a bulk value -- */
अटल व्योम snd_val(काष्ठा gspca_dev *gspca_dev,
			पूर्णांक ads,
			अचिन्हित पूर्णांक val)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;
	पूर्णांक alen, ret;
	__u8 seq = 0;

	अगर (ads == 0x003f08) अणु
		reg_r(gspca_dev, 0x0704);
		seq = reg_r(gspca_dev, 0x0705);
		reg_r(gspca_dev, 0x0650);
		reg_w(gspca_dev, 0x654, seq);
	पूर्ण अन्यथा अणु
		reg_w(gspca_dev, 0x654, (ads >> 16) & 0xff);
	पूर्ण
	reg_w(gspca_dev, 0x655, (ads >> 8) & 0xff);
	reg_w(gspca_dev, 0x656, ads & 0xff);
	reg_w(gspca_dev, 0x657, 0);
	reg_w(gspca_dev, 0x658, 0x04);	/* size */
	reg_w(gspca_dev, 0x659, 0);
	reg_w(gspca_dev, 0x65a, 0);
	reg_w(gspca_dev, 0x65b, 0);
	reg_w(gspca_dev, 0x650, 5);
	अगर (gspca_dev->usb_err < 0)
		वापस;
	gspca_dev->usb_buf[0] = val >> 24;
	gspca_dev->usb_buf[1] = val >> 16;
	gspca_dev->usb_buf[2] = val >> 8;
	gspca_dev->usb_buf[3] = val;
	ret = usb_bulk_msg(dev,
			usb_sndbulkpipe(dev, 6),
			gspca_dev->usb_buf,
			4,
			&alen,
			500);	/* समयout in milliseconds */
	अगर (ret < 0) अणु
		pr_err("snd_val err %d\n", ret);
		gspca_dev->usb_err = ret;
	पूर्ण अन्यथा अणु
		अगर (ads == 0x003f08) अणु
			seq += 4;
			seq &= 0x3f;
			reg_w(gspca_dev, 0x705, seq);
		पूर्ण
	पूर्ण
पूर्ण

/* set a camera parameter */
अटल व्योम set_par(काष्ठा gspca_dev *gspca_dev,
		   पूर्णांक parval)
अणु
	snd_val(gspca_dev, 0x003f08, parval);
पूर्ण

अटल व्योम setbrightness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	पूर्णांक parval;

	parval = 0x06000000		/* whiteness */
		+ (val << 16);
	set_par(gspca_dev, parval);
पूर्ण

अटल व्योम setcontrast(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	पूर्णांक parval;

	parval = 0x07000000		/* contrast */
		+ (val << 16);
	set_par(gspca_dev, parval);
पूर्ण

अटल व्योम setcolors(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	पूर्णांक parval;

	parval = 0x08000000		/* saturation */
		+ (val << 16);
	set_par(gspca_dev, parval);
पूर्ण

अटल व्योम setlightfreq(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	set_par(gspca_dev, val == 1
			? 0x33640000		/* 50 Hz */
			: 0x33780000);		/* 60 Hz */
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	gspca_dev->cam.cam_mode = vga_mode;
	gspca_dev->cam.nmodes = ARRAY_SIZE(vga_mode);
	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	u8 ret;

	/* check अगर the device responds */
	usb_set_पूर्णांकerface(gspca_dev->dev, gspca_dev->अगरace, 1);
	ret = reg_r(gspca_dev, 0x0740);
	अगर (gspca_dev->usb_err >= 0) अणु
		अगर (ret != 0xff) अणु
			pr_err("init reg: 0x%02x\n", ret);
			gspca_dev->usb_err = -EIO;
		पूर्ण
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

/* -- start the camera -- */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक ret, value;

	/* create the JPEG header */
	jpeg_define(sd->jpeg_hdr, gspca_dev->pixfmt.height,
			gspca_dev->pixfmt.width,
			0x22);		/* JPEG 411 */
	jpeg_set_qual(sd->jpeg_hdr, QUALITY);

	/* work on alternate 1 */
	usb_set_पूर्णांकerface(gspca_dev->dev, gspca_dev->अगरace, 1);

	set_par(gspca_dev, 0x10000000);
	set_par(gspca_dev, 0x00000000);
	set_par(gspca_dev, 0x8002e001);
	set_par(gspca_dev, 0x14000000);
	अगर (gspca_dev->pixfmt.width > 320)
		value = 0x8002e001;		/* 640x480 */
	अन्यथा
		value = 0x4001f000;		/* 320x240 */
	set_par(gspca_dev, value);
	ret = usb_set_पूर्णांकerface(gspca_dev->dev,
					gspca_dev->अगरace,
					gspca_dev->alt);
	अगर (ret < 0) अणु
		pr_err("set intf %d %d failed\n",
		       gspca_dev->अगरace, gspca_dev->alt);
		gspca_dev->usb_err = ret;
		जाओ out;
	पूर्ण
	reg_r(gspca_dev, 0x0630);
	rcv_val(gspca_dev, 0x000020);	/* << (value ff ff ff ff) */
	reg_r(gspca_dev, 0x0650);
	snd_val(gspca_dev, 0x000020, 0xffffffff);
	reg_w(gspca_dev, 0x0620, 0);
	reg_w(gspca_dev, 0x0630, 0);
	reg_w(gspca_dev, 0x0640, 0);
	reg_w(gspca_dev, 0x0650, 0);
	reg_w(gspca_dev, 0x0660, 0);
	set_par(gspca_dev, 0x09800000);		/* Red ? */
	set_par(gspca_dev, 0x0a800000);		/* Green ? */
	set_par(gspca_dev, 0x0b800000);		/* Blue ? */
	set_par(gspca_dev, 0x0d030000);		/* Gamma ? */

	/* start the video flow */
	set_par(gspca_dev, 0x01000000);
	set_par(gspca_dev, 0x01000000);
	अगर (gspca_dev->usb_err >= 0)
		gspca_dbg(gspca_dev, D_STREAM, "camera started alt: 0x%02x\n",
			  gspca_dev->alt);
out:
	वापस gspca_dev->usb_err;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;

	set_par(gspca_dev, 0x02000000);
	set_par(gspca_dev, 0x02000000);
	usb_set_पूर्णांकerface(dev, gspca_dev->अगरace, 1);
	reg_r(gspca_dev, 0x0630);
	rcv_val(gspca_dev, 0x000020);	/* << (value ff ff ff ff) */
	reg_r(gspca_dev, 0x0650);
	snd_val(gspca_dev, 0x000020, 0xffffffff);
	reg_w(gspca_dev, 0x0620, 0);
	reg_w(gspca_dev, 0x0630, 0);
	reg_w(gspca_dev, 0x0640, 0);
	reg_w(gspca_dev, 0x0650, 0);
	reg_w(gspca_dev, 0x0660, 0);
	gspca_dbg(gspca_dev, D_STREAM, "camera stopped\n");
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	अटल अचिन्हित अक्षर ffd9[] = अणु0xff, 0xd9पूर्ण;

	/* a frame starts with:
	 *	- 0xff 0xfe
	 *	- 0x08 0x00	- length (little endian ?!)
	 *	- 4 bytes = size of whole frame (BE - including header)
	 *	- 0x00 0x0c
	 *	- 0xff 0xd8
	 *	- ..	JPEG image with escape sequences (ff 00)
	 *		(without ending - ff d9)
	 */
	अगर (data[0] == 0xff && data[1] == 0xfe) अणु
		gspca_frame_add(gspca_dev, LAST_PACKET,
				ffd9, 2);

		/* put the JPEG 411 header */
		gspca_frame_add(gspca_dev, FIRST_PACKET,
			sd->jpeg_hdr, JPEG_HDR_SZ);

		/* beginning of the frame */
#घोषणा STKHDRSZ 12
		data += STKHDRSZ;
		len -= STKHDRSZ;
	पूर्ण
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
पूर्ण

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);

	gspca_dev->usb_err = 0;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		setbrightness(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		setcontrast(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		setcolors(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		setlightfreq(gspca_dev, ctrl->val);
		अवरोध;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.s_ctrl = sd_s_ctrl,
पूर्ण;

अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 4);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 127);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1, 127);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SATURATION, 0, 255, 1, 127);
	v4l2_ctrl_new_std_menu(hdl, &sd_ctrl_ops,
			V4L2_CID_POWER_LINE_FREQUENCY,
			V4L2_CID_POWER_LINE_FREQUENCY_60HZ, 1,
			V4L2_CID_POWER_LINE_FREQUENCY_50HZ);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण
	वापस 0;
पूर्ण

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name = MODULE_NAME,
	.config = sd_config,
	.init = sd_init,
	.init_controls = sd_init_controls,
	.start = sd_start,
	.stopN = sd_stopN,
	.pkt_scan = sd_pkt_scan,
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x05e1, 0x0893)पूर्ण,
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
