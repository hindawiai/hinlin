<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * spca1528 subdriver
 *
 * Copyright (C) 2010-2011 Jean-Francois Moine (http://moinejf.मुक्त.fr)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "spca1528"

#समावेश "gspca.h"
#समावेश "jpeg.h"

MODULE_AUTHOR("Jean-Francois Moine <http://moinejf.free.fr>");
MODULE_DESCRIPTION("SPCA1528 USB Camera Driver");
MODULE_LICENSE("GPL");

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */

	u8 pkt_seq;

	u8 jpeg_hdr[JPEG_HDR_SZ];
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_mode[] = अणु
/*		(करोes not work correctly)
	अणु176, 144, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144 * 5 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 3पूर्ण,
*/
	अणु320, 240, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 4 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 2पूर्ण,
	अणु640, 480, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
पूर्ण;

/* पढ़ो <len> bytes to gspca usb_buf */
अटल व्योम reg_r(काष्ठा gspca_dev *gspca_dev,
			u8 req,
			u16 index,
			पूर्णांक len)
अणु
#अगर USB_BUF_SZ < 64
#त्रुटि "USB buffer too small"
#पूर्ण_अगर
	काष्ठा usb_device *dev = gspca_dev->dev;
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			req,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0x0000,			/* value */
			index,
			gspca_dev->usb_buf, len,
			500);
	gspca_dbg(gspca_dev, D_USBI, "GET %02x 0000 %04x %02x\n", req, index,
		  gspca_dev->usb_buf[0]);
	अगर (ret < 0) अणु
		pr_err("reg_r err %d\n", ret);
		gspca_dev->usb_err = ret;
		/*
		 * Make sure the buffer is zeroed to aव्योम uninitialized
		 * values.
		 */
		स_रखो(gspca_dev->usb_buf, 0, USB_BUF_SZ);
	पूर्ण
पूर्ण

अटल व्योम reg_w(काष्ठा gspca_dev *gspca_dev,
			u8 req,
			u16 value,
			u16 index)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	gspca_dbg(gspca_dev, D_USBO, "SET %02x %04x %04x\n", req, value, index);
	ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			req,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index,
			शून्य, 0, 500);
	अगर (ret < 0) अणु
		pr_err("reg_w err %d\n", ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण

अटल व्योम reg_wb(काष्ठा gspca_dev *gspca_dev,
			u8 req,
			u16 value,
			u16 index,
			u8 byte)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	gspca_dbg(gspca_dev, D_USBO, "SET %02x %04x %04x %02x\n",
		  req, value, index, byte);
	gspca_dev->usb_buf[0] = byte;
	ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			req,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index,
			gspca_dev->usb_buf, 1, 500);
	अगर (ret < 0) अणु
		pr_err("reg_w err %d\n", ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण

अटल व्योम रुको_status_0(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक i, w;

	i = 16;
	w = 0;
	करो अणु
		reg_r(gspca_dev, 0x21, 0x0000, 1);
		अगर (gspca_dev->usb_buf[0] == 0)
			वापस;
		w += 15;
		msleep(w);
	पूर्ण जबतक (--i > 0);
	gspca_err(gspca_dev, "wait_status_0 timeout\n");
	gspca_dev->usb_err = -ETIME;
पूर्ण

अटल व्योम रुको_status_1(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक i;

	i = 10;
	करो अणु
		reg_r(gspca_dev, 0x21, 0x0001, 1);
		msleep(10);
		अगर (gspca_dev->usb_buf[0] == 1) अणु
			reg_wb(gspca_dev, 0x21, 0x0000, 0x0001, 0x00);
			reg_r(gspca_dev, 0x21, 0x0001, 1);
			वापस;
		पूर्ण
	पूर्ण जबतक (--i > 0);
	gspca_err(gspca_dev, "wait_status_1 timeout\n");
	gspca_dev->usb_err = -ETIME;
पूर्ण

अटल व्योम setbrightness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	reg_wb(gspca_dev, 0xc0, 0x0000, 0x00c0, val);
पूर्ण

अटल व्योम setcontrast(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	reg_wb(gspca_dev, 0xc1, 0x0000, 0x00c1, val);
पूर्ण

अटल व्योम sethue(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	reg_wb(gspca_dev, 0xc2, 0x0000, 0x0000, val);
पूर्ण

अटल व्योम setcolor(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	reg_wb(gspca_dev, 0xc3, 0x0000, 0x00c3, val);
पूर्ण

अटल व्योम setsharpness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	reg_wb(gspca_dev, 0xc4, 0x0000, 0x00c4, val);
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	gspca_dev->cam.cam_mode = vga_mode;
	gspca_dev->cam.nmodes = ARRAY_SIZE(vga_mode);
	gspca_dev->cam.npkt = 128; /* number of packets per ISOC message */
			/*fixme: 256 in ms-win traces*/

	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	reg_w(gspca_dev, 0x00, 0x0001, 0x2067);
	reg_w(gspca_dev, 0x00, 0x00d0, 0x206b);
	reg_w(gspca_dev, 0x00, 0x0000, 0x206c);
	reg_w(gspca_dev, 0x00, 0x0001, 0x2069);
	msleep(8);
	reg_w(gspca_dev, 0x00, 0x00c0, 0x206b);
	reg_w(gspca_dev, 0x00, 0x0000, 0x206c);
	reg_w(gspca_dev, 0x00, 0x0001, 0x2069);

	reg_r(gspca_dev, 0x20, 0x0000, 1);
	reg_r(gspca_dev, 0x20, 0x0000, 5);
	reg_r(gspca_dev, 0x23, 0x0000, 64);
	gspca_dbg(gspca_dev, D_PROBE, "%s%s\n", &gspca_dev->usb_buf[0x1c],
		  &gspca_dev->usb_buf[0x30]);
	reg_r(gspca_dev, 0x23, 0x0001, 64);
	वापस gspca_dev->usb_err;
पूर्ण

/* function called at start समय beक्रमe URB creation */
अटल पूर्णांक sd_isoc_init(काष्ठा gspca_dev *gspca_dev)
अणु
	u8 mode;

	reg_r(gspca_dev, 0x00, 0x2520, 1);
	रुको_status_0(gspca_dev);
	reg_w(gspca_dev, 0xc5, 0x0003, 0x0000);
	रुको_status_1(gspca_dev);

	रुको_status_0(gspca_dev);
	mode = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
	reg_wb(gspca_dev, 0x25, 0x0000, 0x0004, mode);
	reg_r(gspca_dev, 0x25, 0x0004, 1);
	reg_wb(gspca_dev, 0x27, 0x0000, 0x0000, 0x06);	/* 420 */
	reg_r(gspca_dev, 0x27, 0x0000, 1);

/* not useful..
	gspca_dev->alt = 4;		* use alternate setting 3 */

	वापस gspca_dev->usb_err;
पूर्ण

/* -- start the camera -- */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/* initialize the JPEG header */
	jpeg_define(sd->jpeg_hdr, gspca_dev->pixfmt.height,
			gspca_dev->pixfmt.width,
			0x22);		/* JPEG 411 */

	/* the JPEG quality shall be 85% */
	jpeg_set_qual(sd->jpeg_hdr, 85);

	reg_r(gspca_dev, 0x00, 0x2520, 1);
	msleep(8);

	/* start the capture */
	रुको_status_0(gspca_dev);
	reg_w(gspca_dev, 0x31, 0x0000, 0x0004);	/* start request */
	रुको_status_1(gspca_dev);
	रुको_status_0(gspca_dev);
	msleep(200);

	sd->pkt_seq = 0;
	वापस gspca_dev->usb_err;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	/* stop the capture */
	रुको_status_0(gspca_dev);
	reg_w(gspca_dev, 0x31, 0x0000, 0x0000);	/* stop request */
	रुको_status_1(gspca_dev);
	रुको_status_0(gspca_dev);
पूर्ण

/* move a packet adding 0x00 after 0xff */
अटल व्योम add_packet(काष्ठा gspca_dev *gspca_dev,
			u8 *data,
			पूर्णांक len)
अणु
	पूर्णांक i;

	i = 0;
	करो अणु
		अगर (data[i] == 0xff) अणु
			gspca_frame_add(gspca_dev, INTER_PACKET,
					data, i + 1);
			len -= i;
			data += i;
			*data = 0x00;
			i = 0;
		पूर्ण
	पूर्ण जबतक (++i < len);
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	अटल स्थिर u8 ffd9[] = अणु0xff, 0xd9पूर्ण;

	/* image packets start with:
	 *	02 8n
	 * with <n> bit:
	 *	0x01: even (0) / odd (1) image
	 *	0x02: end of image when set
	 */
	अगर (len < 3)
		वापस;				/* empty packet */
	अगर (*data == 0x02) अणु
		अगर (data[1] & 0x02) अणु
			sd->pkt_seq = !(data[1] & 1);
			add_packet(gspca_dev, data + 2, len - 2);
			gspca_frame_add(gspca_dev, LAST_PACKET,
					ffd9, 2);
			वापस;
		पूर्ण
		अगर ((data[1] & 1) != sd->pkt_seq)
			जाओ err;
		अगर (gspca_dev->last_packet_type == LAST_PACKET)
			gspca_frame_add(gspca_dev, FIRST_PACKET,
					sd->jpeg_hdr, JPEG_HDR_SZ);
		add_packet(gspca_dev, data + 2, len - 2);
		वापस;
	पूर्ण
err:
	gspca_dev->last_packet_type = DISCARD_PACKET;
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
	हाल V4L2_CID_HUE:
		sethue(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		setcolor(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SHARPNESS:
		setsharpness(gspca_dev, ctrl->val);
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
	v4l2_ctrl_handler_init(hdl, 5);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 8, 1, 1);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_HUE, 0, 255, 1, 0);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SATURATION, 0, 8, 1, 1);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SHARPNESS, 0, 255, 1, 0);

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
	.isoc_init = sd_isoc_init,
	.start = sd_start,
	.stopN = sd_stopN,
	.pkt_scan = sd_pkt_scan,
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x04fc, 0x1528)पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, device_table);

/* -- device connect -- */
अटल पूर्णांक sd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	/* the video पूर्णांकerface क्रम isochronous transfer is 1 */
	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber != 1)
		वापस -ENODEV;

	वापस gspca_dev_probe2(पूर्णांकf, id, &sd_desc, माप(काष्ठा sd),
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
