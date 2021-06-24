<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *		Mars-Semi MR97311A library
 *		Copyright (C) 2005 <bradlch@hoपंचांगail.com>
 *
 * V4L2 by Jean-Francois Moine <http://moinejf.मुक्त.fr>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "mars"

#समावेश "gspca.h"
#समावेश "jpeg.h"

MODULE_AUTHOR("Michel Xhaard <mxhaard@users.sourceforge.net>");
MODULE_DESCRIPTION("GSPCA/Mars USB Camera Driver");
MODULE_LICENSE("GPL");

#घोषणा QUALITY 50

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */

	काष्ठा v4l2_ctrl *brightness;
	काष्ठा v4l2_ctrl *saturation;
	काष्ठा v4l2_ctrl *sharpness;
	काष्ठा v4l2_ctrl *gamma;
	काष्ठा अणु /* illuminator control cluster */
		काष्ठा v4l2_ctrl *illum_top;
		काष्ठा v4l2_ctrl *illum_bottom;
	पूर्ण;
	u8 jpeg_hdr[JPEG_HDR_SZ];
पूर्ण;

/* V4L2 controls supported by the driver */
अटल व्योम setbrightness(काष्ठा gspca_dev *gspca_dev, s32 val);
अटल व्योम setcolors(काष्ठा gspca_dev *gspca_dev, s32 val);
अटल व्योम setgamma(काष्ठा gspca_dev *gspca_dev, s32 val);
अटल व्योम setsharpness(काष्ठा gspca_dev *gspca_dev, s32 val);

अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_mode[] = अणु
	अणु320, 240, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 2पूर्ण,
	अणु640, 480, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
पूर्ण;

अटल स्थिर __u8 mi_data[0x20] = अणु
/*	 01    02   03     04    05    06    07    08 */
	0x48, 0x22, 0x01, 0x47, 0x10, 0x00, 0x00, 0x00,
/*	 09    0a   0b     0c    0d    0e    0f    10 */
	0x00, 0x01, 0x30, 0x01, 0x30, 0x01, 0x30, 0x01,
/*	 11    12   13     14    15    16    17    18 */
	0x30, 0x00, 0x04, 0x00, 0x06, 0x01, 0xe2, 0x02,
/*	 19    1a   1b     1c    1d    1e    1f    20 */
	0x82, 0x00, 0x20, 0x17, 0x80, 0x08, 0x0c, 0x00
पूर्ण;

/* ग_लिखो <len> bytes from gspca_dev->usb_buf */
अटल व्योम reg_w(काष्ठा gspca_dev *gspca_dev,
		 पूर्णांक len)
अणु
	पूर्णांक alen, ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;

	ret = usb_bulk_msg(gspca_dev->dev,
			usb_sndbulkpipe(gspca_dev->dev, 4),
			gspca_dev->usb_buf,
			len,
			&alen,
			500);	/* समयout in milliseconds */
	अगर (ret < 0) अणु
		pr_err("reg write [%02x] error %d\n",
		       gspca_dev->usb_buf[0], ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण

अटल व्योम mi_w(काष्ठा gspca_dev *gspca_dev,
		 u8 addr,
		 u8 value)
अणु
	gspca_dev->usb_buf[0] = 0x1f;
	gspca_dev->usb_buf[1] = 0;			/* control byte */
	gspca_dev->usb_buf[2] = addr;
	gspca_dev->usb_buf[3] = value;

	reg_w(gspca_dev, 4);
पूर्ण

अटल व्योम setbrightness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	gspca_dev->usb_buf[0] = 0x61;
	gspca_dev->usb_buf[1] = val;
	reg_w(gspca_dev, 2);
पूर्ण

अटल व्योम setcolors(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	gspca_dev->usb_buf[0] = 0x5f;
	gspca_dev->usb_buf[1] = val << 3;
	gspca_dev->usb_buf[2] = ((val >> 2) & 0xf8) | 0x04;
	reg_w(gspca_dev, 3);
पूर्ण

अटल व्योम setgamma(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	gspca_dev->usb_buf[0] = 0x06;
	gspca_dev->usb_buf[1] = val * 0x40;
	reg_w(gspca_dev, 2);
पूर्ण

अटल व्योम setsharpness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	gspca_dev->usb_buf[0] = 0x67;
	gspca_dev->usb_buf[1] = val * 4 + 3;
	reg_w(gspca_dev, 2);
पूर्ण

अटल व्योम setilluminators(काष्ठा gspca_dev *gspca_dev, bool top, bool bottom)
अणु
	/* both are off अगर not streaming */
	gspca_dev->usb_buf[0] = 0x22;
	अगर (top)
		gspca_dev->usb_buf[1] = 0x76;
	अन्यथा अगर (bottom)
		gspca_dev->usb_buf[1] = 0x7a;
	अन्यथा
		gspca_dev->usb_buf[1] = 0x7e;
	reg_w(gspca_dev, 2);
पूर्ण

अटल पूर्णांक mars_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;

	gspca_dev->usb_err = 0;

	अगर (ctrl->id == V4L2_CID_ILLUMINATORS_1) अणु
		/* only one can be on at a समय */
		अगर (ctrl->is_new && ctrl->val)
			sd->illum_bottom->val = 0;
		अगर (sd->illum_bottom->is_new && sd->illum_bottom->val)
			sd->illum_top->val = 0;
	पूर्ण

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		setbrightness(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		setcolors(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_GAMMA:
		setgamma(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_ILLUMINATORS_1:
		setilluminators(gspca_dev, sd->illum_top->val,
					   sd->illum_bottom->val);
		अवरोध;
	हाल V4L2_CID_SHARPNESS:
		setsharpness(gspca_dev, ctrl->val);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops mars_ctrl_ops = अणु
	.s_ctrl = mars_s_ctrl,
पूर्ण;

/* this function is called at probe समय */
अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 6);
	sd->brightness = v4l2_ctrl_new_std(hdl, &mars_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 30, 1, 15);
	sd->saturation = v4l2_ctrl_new_std(hdl, &mars_ctrl_ops,
			V4L2_CID_SATURATION, 0, 255, 1, 200);
	sd->gamma = v4l2_ctrl_new_std(hdl, &mars_ctrl_ops,
			V4L2_CID_GAMMA, 0, 3, 1, 1);
	sd->sharpness = v4l2_ctrl_new_std(hdl, &mars_ctrl_ops,
			V4L2_CID_SHARPNESS, 0, 2, 1, 1);
	sd->illum_top = v4l2_ctrl_new_std(hdl, &mars_ctrl_ops,
			V4L2_CID_ILLUMINATORS_1, 0, 1, 1, 0);
	sd->illum_top->flags |= V4L2_CTRL_FLAG_UPDATE;
	sd->illum_bottom = v4l2_ctrl_new_std(hdl, &mars_ctrl_ops,
			V4L2_CID_ILLUMINATORS_2, 0, 1, 1, 0);
	sd->illum_bottom->flags |= V4L2_CTRL_FLAG_UPDATE;
	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण
	v4l2_ctrl_cluster(2, &sd->illum_top);
	वापस 0;
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा cam *cam;

	cam = &gspca_dev->cam;
	cam->cam_mode = vga_mode;
	cam->nmodes = ARRAY_SIZE(vga_mode);
	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 *data;
	पूर्णांक i;

	/* create the JPEG header */
	jpeg_define(sd->jpeg_hdr, gspca_dev->pixfmt.height,
			gspca_dev->pixfmt.width,
			0x21);		/* JPEG 422 */
	jpeg_set_qual(sd->jpeg_hdr, QUALITY);

	data = gspca_dev->usb_buf;

	data[0] = 0x01;		/* address */
	data[1] = 0x01;
	reg_w(gspca_dev, 2);

	/*
	   Initialize the MR97113 chip रेजिस्टर
	 */
	data[0] = 0x00;		/* address */
	data[1] = 0x0c | 0x01;	/* reg 0 */
	data[2] = 0x01;		/* reg 1 */
	data[3] = gspca_dev->pixfmt.width / 8;	/* h_size , reg 2 */
	data[4] = gspca_dev->pixfmt.height / 8;	/* v_size , reg 3 */
	data[5] = 0x30;		/* reg 4, MI, PAS5101 :
				 *	0x30 क्रम 24mhz , 0x28 क्रम 12mhz */
	data[6] = 0x02;		/* reg 5, H start - was 0x04 */
	data[7] = v4l2_ctrl_g_ctrl(sd->gamma) * 0x40;	/* reg 0x06: gamma */
	data[8] = 0x01;		/* reg 7, V start - was 0x03 */
/*	अगर (h_size == 320 ) */
/*		data[9]= 0x56;	 * reg 8, 24MHz, 2:1 scale करोwn */
/*	अन्यथा */
	data[9] = 0x52;		/* reg 8, 24MHz, no scale करोwn */
/*jfm: from win trace*/
	data[10] = 0x18;

	reg_w(gspca_dev, 11);

	data[0] = 0x23;		/* address */
	data[1] = 0x09;		/* reg 35, append frame header */

	reg_w(gspca_dev, 2);

	data[0] = 0x3c;		/* address */
/*	अगर (gspca_dev->width == 1280) */
/*		data[1] = 200;	 * reg 60, pc-cam frame size
				 *	(unit: 4KB) 800KB */
/*	अन्यथा */
	data[1] = 50;		/* 50 reg 60, pc-cam frame size
				 *	(unit: 4KB) 200KB */
	reg_w(gspca_dev, 2);

	/* स्वतः dark-gain */
	data[0] = 0x5e;		/* address */
	data[1] = 0;		/* reg 94, Y Gain (स्वतः) */
/*jfm: from win trace*/
				/* reg 0x5f/0x60 (LE) = saturation */
				/* h (60): xxxx x100
				 * l (5f): xxxx x000 */
	data[2] = v4l2_ctrl_g_ctrl(sd->saturation) << 3;
	data[3] = ((v4l2_ctrl_g_ctrl(sd->saturation) >> 2) & 0xf8) | 0x04;
	data[4] = v4l2_ctrl_g_ctrl(sd->brightness); /* reg 0x61 = brightness */
	data[5] = 0x00;

	reg_w(gspca_dev, 6);

	data[0] = 0x67;
/*jfm: from win trace*/
	data[1] = v4l2_ctrl_g_ctrl(sd->sharpness) * 4 + 3;
	data[2] = 0x14;
	reg_w(gspca_dev, 3);

	data[0] = 0x69;
	data[1] = 0x2f;
	data[2] = 0x28;
	data[3] = 0x42;
	reg_w(gspca_dev, 4);

	data[0] = 0x63;
	data[1] = 0x07;
	reg_w(gspca_dev, 2);
/*jfm: win trace - many ग_लिखोs here to reg 0x64*/

	/* initialize the MI sensor */
	क्रम (i = 0; i < माप mi_data; i++)
		mi_w(gspca_dev, i + 1, mi_data[i]);

	data[0] = 0x00;
	data[1] = 0x4d;		/* ISOC transferring enable... */
	reg_w(gspca_dev, 2);

	setilluminators(gspca_dev, v4l2_ctrl_g_ctrl(sd->illum_top),
				   v4l2_ctrl_g_ctrl(sd->illum_bottom));

	वापस gspca_dev->usb_err;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (v4l2_ctrl_g_ctrl(sd->illum_top) ||
	    v4l2_ctrl_g_ctrl(sd->illum_bottom)) अणु
		setilluminators(gspca_dev, false, false);
		msleep(20);
	पूर्ण

	gspca_dev->usb_buf[0] = 1;
	gspca_dev->usb_buf[1] = 0;
	reg_w(gspca_dev, 2);
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक p;

	अगर (len < 6) अणु
/*		gspca_dev->last_packet_type = DISCARD_PACKET; */
		वापस;
	पूर्ण
	क्रम (p = 0; p < len - 6; p++) अणु
		अगर (data[0 + p] == 0xff
		    && data[1 + p] == 0xff
		    && data[2 + p] == 0x00
		    && data[3 + p] == 0xff
		    && data[4 + p] == 0x96) अणु
			अगर (data[5 + p] == 0x64
			    || data[5 + p] == 0x65
			    || data[5 + p] == 0x66
			    || data[5 + p] == 0x67) अणु
				gspca_dbg(gspca_dev, D_PACK, "sof offset: %d len: %d\n",
					  p, len);
				gspca_frame_add(gspca_dev, LAST_PACKET,
						data, p);

				/* put the JPEG header */
				gspca_frame_add(gspca_dev, FIRST_PACKET,
					sd->jpeg_hdr, JPEG_HDR_SZ);
				data += p + 16;
				len -= p + 16;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
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
	अणुUSB_DEVICE(0x093a, 0x050f)पूर्ण,
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
