<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *		Pixart PAC7311 library
 *		Copyright (C) 2005 Thomas Kaiser thomas@kaiser-linux.li
 *
 * V4L2 by Jean-Francois Moine <http://moinejf.मुक्त.fr>
 */

/* Some करोcumentation about various रेजिस्टरs as determined by trial and error.
 *
 * Register page 1:
 *
 * Address	Description
 * 0x08		Unknown compressor related, must always be 8 except when not
 *		in 640x480 resolution and page 4 reg 2 <= 3 then set it to 9 !
 * 0x1b		Auto white balance related, bit 0 is AWB enable (inverted)
 *		bits 345 seem to toggle per color gains on/off (inverted)
 * 0x78		Global control, bit 6 controls the LED (inverted)
 * 0x80		Compression balance, पूर्णांकeresting settings:
 *		0x01 Use this to allow the camera to चयन to higher compr.
 *		     on the fly. Needed to stay within bandwidth @ 640x480@30
 *		0x1c From usb captures under Winकरोws क्रम 640x480
 *		0x2a Values >= this चयन the camera to a lower compression,
 *		     using the same table क्रम both luminance and chrominance.
 *		     This gives a sharper picture. Usable only at 640x480@ <
 *		     15 fps or 320x240 / 160x120. Note currently the driver
 *		     करोes not use this as the quality gain is small and the
 *		     generated JPG-s are only understood by v4l-utils >= 0.8.9
 *		0x3f From usb captures under Winकरोws क्रम 320x240
 *		0x69 From usb captures under Winकरोws क्रम 160x120
 *
 * Register page 4:
 *
 * Address	Description
 * 0x02		Clock भागider 2-63, fps =~ 60 / val. Must be a multiple of 3 on
 *		the 7302, so one of 3, 6, 9, ..., except when between 6 and 12?
 * 0x0f		Master gain 1-245, low value = high gain
 * 0x10		Another gain 0-15, limited influence (1-2x gain I guess)
 * 0x21		Bitfield: 0-1 unused, 2-3 vflip/hflip, 4-5 unknown, 6-7 unused
 *		Note setting vflip disabled leads to a much lower image quality,
 *		so we always vflip, and tell userspace to flip it back
 * 0x27		Seems to toggle various gains on / off, Setting bit 7 seems to
 *		completely disable the analog amplअगरication block. Set to 0x68
 *		क्रम max gain, 0x14 क्रम minimal gain.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "pac7311"

#समावेश <linux/input.h>
#समावेश "gspca.h"
/* Include pac common sof detection functions */
#समावेश "pac_common.h"

#घोषणा PAC7311_GAIN_DEFAULT     122
#घोषणा PAC7311_EXPOSURE_DEFAULT   3 /* 20 fps, aव्योम using high compr. */

MODULE_AUTHOR("Thomas Kaiser thomas@kaiser-linux.li");
MODULE_DESCRIPTION("Pixart PAC7311");
MODULE_LICENSE("GPL");

काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;		/* !! must be the first item */

	काष्ठा v4l2_ctrl *contrast;
	काष्ठा v4l2_ctrl *hflip;

	u8 sof_पढ़ो;
	u8 स्वतःgain_ignore_frames;

	atomic_t avg_lum;
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_mode[] = अणु
	अणु160, 120, V4L2_PIX_FMT_PJPG, V4L2_FIELD_NONE,
		.bytesperline = 160,
		.sizeimage = 160 * 120 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 2पूर्ण,
	अणु320, 240, V4L2_PIX_FMT_PJPG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
	अणु640, 480, V4L2_PIX_FMT_PJPG, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 0पूर्ण,
पूर्ण;

#घोषणा LOAD_PAGE4		254
#घोषणा END_OF_SEQUENCE		0

अटल स्थिर __u8 init_7311[] = अणु
	0xff, 0x01,
	0x78, 0x40,	/* Bit_0=start stream, Bit_6=LED */
	0x78, 0x40,	/* Bit_0=start stream, Bit_6=LED */
	0x78, 0x44,	/* Bit_0=start stream, Bit_6=LED */
	0xff, 0x04,
	0x27, 0x80,
	0x28, 0xca,
	0x29, 0x53,
	0x2a, 0x0e,
	0xff, 0x01,
	0x3e, 0x20,
पूर्ण;

अटल स्थिर __u8 start_7311[] = अणु
/*	index, len, [value]* */
	0xff, 1,	0x01,		/* page 1 */
	0x02, 43,	0x48, 0x0a, 0x40, 0x08, 0x00, 0x00, 0x08, 0x00,
			0x06, 0xff, 0x11, 0xff, 0x5a, 0x30, 0x90, 0x4c,
			0x00, 0x07, 0x00, 0x0a, 0x10, 0x00, 0xa0, 0x10,
			0x02, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x01, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00,
	0x3e, 42,	0x00, 0x00, 0x78, 0x52, 0x4a, 0x52, 0x78, 0x6e,
			0x48, 0x46, 0x48, 0x6e, 0x5f, 0x49, 0x42, 0x49,
			0x5f, 0x5f, 0x49, 0x42, 0x49, 0x5f, 0x6e, 0x48,
			0x46, 0x48, 0x6e, 0x78, 0x52, 0x4a, 0x52, 0x78,
			0x00, 0x00, 0x09, 0x1b, 0x34, 0x49, 0x5c, 0x9b,
			0xd0, 0xff,
	0x78, 6,	0x44, 0x00, 0xf2, 0x01, 0x01, 0x80,
	0x7f, 18,	0x2a, 0x1c, 0x00, 0xc8, 0x02, 0x58, 0x03, 0x84,
			0x12, 0x00, 0x1a, 0x04, 0x08, 0x0c, 0x10, 0x14,
			0x18, 0x20,
	0x96, 3,	0x01, 0x08, 0x04,
	0xa0, 4,	0x44, 0x44, 0x44, 0x04,
	0xf0, 13,	0x01, 0x00, 0x00, 0x00, 0x22, 0x00, 0x20, 0x00,
			0x3f, 0x00, 0x0a, 0x01, 0x00,
	0xff, 1,	0x04,		/* page 4 */
	0, LOAD_PAGE4,			/* load the page 4 */
	0x11, 1,	0x01,
	0, END_OF_SEQUENCE		/* end of sequence */
पूर्ण;

#घोषणा SKIP		0xaa
/* page 4 - the value SKIP says skip the index - see reg_w_page() */
अटल स्थिर __u8 page4_7311[] = अणु
	SKIP, SKIP, 0x04, 0x54, 0x07, 0x2b, 0x09, 0x0f,
	0x09, 0x00, SKIP, SKIP, 0x07, 0x00, 0x00, 0x62,
	0x08, SKIP, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x03, 0xa0, 0x01, 0xf4, SKIP,
	SKIP, 0x00, 0x08, SKIP, 0x03, SKIP, 0x00, 0x68,
	0xca, 0x10, 0x06, 0x78, 0x00, 0x00, 0x00, 0x00,
	0x23, 0x28, 0x04, 0x11, 0x00, 0x00
पूर्ण;

अटल व्योम reg_w_buf(काष्ठा gspca_dev *gspca_dev,
		  __u8 index,
		  स्थिर u8 *buffer, पूर्णांक len)
अणु
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	स_नकल(gspca_dev->usb_buf, buffer, len);
	ret = usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0,		/* request */
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0,		/* value */
			index, gspca_dev->usb_buf, len,
			500);
	अगर (ret < 0) अणु
		pr_err("reg_w_buf() failed index 0x%02x, error %d\n",
		       index, ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण


अटल व्योम reg_w(काष्ठा gspca_dev *gspca_dev,
		  __u8 index,
		  __u8 value)
अणु
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	gspca_dev->usb_buf[0] = value;
	ret = usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0,			/* request */
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, index, gspca_dev->usb_buf, 1,
			500);
	अगर (ret < 0) अणु
		pr_err("reg_w() failed index 0x%02x, value 0x%02x, error %d\n",
		       index, value, ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण

अटल व्योम reg_w_seq(काष्ठा gspca_dev *gspca_dev,
		स्थिर __u8 *seq, पूर्णांक len)
अणु
	जबतक (--len >= 0) अणु
		reg_w(gspca_dev, seq[0], seq[1]);
		seq += 2;
	पूर्ण
पूर्ण

/* load the beginning of a page */
अटल व्योम reg_w_page(काष्ठा gspca_dev *gspca_dev,
			स्थिर __u8 *page, पूर्णांक len)
अणु
	पूर्णांक index;
	पूर्णांक ret = 0;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	क्रम (index = 0; index < len; index++) अणु
		अगर (page[index] == SKIP)		/* skip this index */
			जारी;
		gspca_dev->usb_buf[0] = page[index];
		ret = usb_control_msg(gspca_dev->dev,
				usb_sndctrlpipe(gspca_dev->dev, 0),
				0,			/* request */
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0, index, gspca_dev->usb_buf, 1,
				500);
		अगर (ret < 0) अणु
			pr_err("reg_w_page() failed index 0x%02x, value 0x%02x, error %d\n",
			       index, page[index], ret);
			gspca_dev->usb_err = ret;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* output a variable sequence */
अटल व्योम reg_w_var(काष्ठा gspca_dev *gspca_dev,
			स्थिर __u8 *seq,
			स्थिर __u8 *page4, अचिन्हित पूर्णांक page4_len)
अणु
	पूर्णांक index, len;

	क्रम (;;) अणु
		index = *seq++;
		len = *seq++;
		चयन (len) अणु
		हाल END_OF_SEQUENCE:
			वापस;
		हाल LOAD_PAGE4:
			reg_w_page(gspca_dev, page4, page4_len);
			अवरोध;
		शेष:
			अगर (len > USB_BUF_SZ) अणु
				gspca_err(gspca_dev, "Incorrect variable sequence\n");
				वापस;
			पूर्ण
			जबतक (len > 0) अणु
				अगर (len < 8) अणु
					reg_w_buf(gspca_dev,
						index, seq, len);
					seq += len;
					अवरोध;
				पूर्ण
				reg_w_buf(gspca_dev, index, seq, 8);
				seq += 8;
				index += 8;
				len -= 8;
			पूर्ण
		पूर्ण
	पूर्ण
	/* not reached */
पूर्ण

/* this function is called at probe समय क्रम pac7311 */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा cam *cam = &gspca_dev->cam;

	cam->cam_mode = vga_mode;
	cam->nmodes = ARRAY_SIZE(vga_mode);
	cam->input_flags = V4L2_IN_ST_VFLIP;

	वापस 0;
पूर्ण

अटल व्योम setcontrast(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	reg_w(gspca_dev, 0xff, 0x04);
	reg_w(gspca_dev, 0x10, val);
	/* load रेजिस्टरs to sensor (Bit 0, स्वतः clear) */
	reg_w(gspca_dev, 0x11, 0x01);
पूर्ण

अटल व्योम setgain(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	reg_w(gspca_dev, 0xff, 0x04);			/* page 4 */
	reg_w(gspca_dev, 0x0e, 0x00);
	reg_w(gspca_dev, 0x0f, gspca_dev->gain->maximum - val + 1);

	/* load रेजिस्टरs to sensor (Bit 0, स्वतः clear) */
	reg_w(gspca_dev, 0x11, 0x01);
पूर्ण

अटल व्योम setexposure(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	reg_w(gspca_dev, 0xff, 0x04);			/* page 4 */
	reg_w(gspca_dev, 0x02, val);

	/* load रेजिस्टरs to sensor (Bit 0, स्वतः clear) */
	reg_w(gspca_dev, 0x11, 0x01);

	/*
	 * Page 1 रेजिस्टर 8 must always be 0x08 except when not in
	 *  640x480 mode and page 4 reg 2 <= 3 then it must be 9
	 */
	reg_w(gspca_dev, 0xff, 0x01);
	अगर (gspca_dev->pixfmt.width != 640 && val <= 3)
		reg_w(gspca_dev, 0x08, 0x09);
	अन्यथा
		reg_w(gspca_dev, 0x08, 0x08);

	/*
	 * Page1 रेजिस्टर 80 sets the compression balance, normally we
	 * want / use 0x1c, but क्रम 640x480@30fps we must allow the
	 * camera to use higher compression or we may run out of
	 * bandwidth.
	 */
	अगर (gspca_dev->pixfmt.width == 640 && val == 2)
		reg_w(gspca_dev, 0x80, 0x01);
	अन्यथा
		reg_w(gspca_dev, 0x80, 0x1c);

	/* load रेजिस्टरs to sensor (Bit 0, स्वतः clear) */
	reg_w(gspca_dev, 0x11, 0x01);
पूर्ण

अटल व्योम sethvflip(काष्ठा gspca_dev *gspca_dev, s32 hflip, s32 vflip)
अणु
	__u8 data;

	reg_w(gspca_dev, 0xff, 0x04);			/* page 4 */
	data = (hflip ? 0x04 : 0x00) |
	       (vflip ? 0x08 : 0x00);
	reg_w(gspca_dev, 0x21, data);

	/* load रेजिस्टरs to sensor (Bit 0, स्वतः clear) */
	reg_w(gspca_dev, 0x11, 0x01);
पूर्ण

/* this function is called at probe and resume समय क्रम pac7311 */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	reg_w_seq(gspca_dev, init_7311, माप(init_7311)/2);
	वापस gspca_dev->usb_err;
पूर्ण

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;

	gspca_dev->usb_err = 0;

	अगर (ctrl->id == V4L2_CID_AUTOGAIN && ctrl->is_new && ctrl->val) अणु
		/* when चयनing to स्वतःgain set शेषs to make sure
		   we are on a valid poपूर्णांक of the स्वतःgain gain /
		   exposure knee graph, and give this change समय to
		   take effect beक्रमe करोing स्वतःgain. */
		gspca_dev->exposure->val    = PAC7311_EXPOSURE_DEFAULT;
		gspca_dev->gain->val        = PAC7311_GAIN_DEFAULT;
		sd->स्वतःgain_ignore_frames  = PAC_AUTOGAIN_IGNORE_FRAMES;
	पूर्ण

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_CONTRAST:
		setcontrast(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		अगर (gspca_dev->exposure->is_new || (ctrl->is_new && ctrl->val))
			setexposure(gspca_dev, gspca_dev->exposure->val);
		अगर (gspca_dev->gain->is_new || (ctrl->is_new && ctrl->val))
			setgain(gspca_dev, gspca_dev->gain->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		sethvflip(gspca_dev, sd->hflip->val, 1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.s_ctrl = sd_s_ctrl,
पूर्ण;

/* this function is called at probe समय */
अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 5);

	sd->contrast = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_CONTRAST, 0, 15, 1, 7);
	gspca_dev->स्वतःgain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	gspca_dev->exposure = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_EXPOSURE, 2, 63, 1,
					PAC7311_EXPOSURE_DEFAULT);
	gspca_dev->gain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
					V4L2_CID_GAIN, 0, 244, 1,
					PAC7311_GAIN_DEFAULT);
	sd->hflip = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
		V4L2_CID_HFLIP, 0, 1, 1, 0);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण

	v4l2_ctrl_स्वतः_cluster(3, &gspca_dev->स्वतःgain, 0, false);
	वापस 0;
पूर्ण

/* -- start the camera -- */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	sd->sof_पढ़ो = 0;

	reg_w_var(gspca_dev, start_7311,
		page4_7311, माप(page4_7311));
	setcontrast(gspca_dev, v4l2_ctrl_g_ctrl(sd->contrast));
	setgain(gspca_dev, v4l2_ctrl_g_ctrl(gspca_dev->gain));
	setexposure(gspca_dev, v4l2_ctrl_g_ctrl(gspca_dev->exposure));
	sethvflip(gspca_dev, v4l2_ctrl_g_ctrl(sd->hflip), 1);

	/* set correct resolution */
	चयन (gspca_dev->cam.cam_mode[(पूर्णांक) gspca_dev->curr_mode].priv) अणु
	हाल 2:					/* 160x120 */
		reg_w(gspca_dev, 0xff, 0x01);
		reg_w(gspca_dev, 0x17, 0x20);
		reg_w(gspca_dev, 0x87, 0x10);
		अवरोध;
	हाल 1:					/* 320x240 */
		reg_w(gspca_dev, 0xff, 0x01);
		reg_w(gspca_dev, 0x17, 0x30);
		reg_w(gspca_dev, 0x87, 0x11);
		अवरोध;
	हाल 0:					/* 640x480 */
		reg_w(gspca_dev, 0xff, 0x01);
		reg_w(gspca_dev, 0x17, 0x00);
		reg_w(gspca_dev, 0x87, 0x12);
		अवरोध;
	पूर्ण

	sd->sof_पढ़ो = 0;
	sd->स्वतःgain_ignore_frames = 0;
	atomic_set(&sd->avg_lum, -1);

	/* start stream */
	reg_w(gspca_dev, 0xff, 0x01);
	reg_w(gspca_dev, 0x78, 0x05);

	वापस gspca_dev->usb_err;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	reg_w(gspca_dev, 0xff, 0x04);
	reg_w(gspca_dev, 0x27, 0x80);
	reg_w(gspca_dev, 0x28, 0xca);
	reg_w(gspca_dev, 0x29, 0x53);
	reg_w(gspca_dev, 0x2a, 0x0e);
	reg_w(gspca_dev, 0xff, 0x01);
	reg_w(gspca_dev, 0x3e, 0x20);
	reg_w(gspca_dev, 0x78, 0x44); /* Bit_0=start stream, Bit_6=LED */
	reg_w(gspca_dev, 0x78, 0x44); /* Bit_0=start stream, Bit_6=LED */
	reg_w(gspca_dev, 0x78, 0x44); /* Bit_0=start stream, Bit_6=LED */
पूर्ण

अटल व्योम करो_स्वतःgain(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक avg_lum = atomic_पढ़ो(&sd->avg_lum);
	पूर्णांक desired_lum, deadzone;

	अगर (avg_lum == -1)
		वापस;

	desired_lum = 170;
	deadzone = 20;

	अगर (sd->स्वतःgain_ignore_frames > 0)
		sd->स्वतःgain_ignore_frames--;
	अन्यथा अगर (gspca_coarse_grained_expo_स्वतःgain(gspca_dev, avg_lum,
						    desired_lum, deadzone))
		sd->स्वतःgain_ignore_frames = PAC_AUTOGAIN_IGNORE_FRAMES;
पूर्ण

/* JPEG header, part 1 */
अटल स्थिर अचिन्हित अक्षर pac_jpeg_header1[] = अणु
  0xff, 0xd8,		/* SOI: Start of Image */

  0xff, 0xc0,		/* SOF0: Start of Frame (Baseline DCT) */
  0x00, 0x11,		/* length = 17 bytes (including this length field) */
  0x08			/* Precision: 8 */
  /* 2 bytes is placed here: number of image lines */
  /* 2 bytes is placed here: samples per line */
पूर्ण;

/* JPEG header, जारीd */
अटल स्थिर अचिन्हित अक्षर pac_jpeg_header2[] = अणु
  0x03,			/* Number of image components: 3 */
  0x01, 0x21, 0x00,	/* ID=1, Subsampling 1x1, Quantization table: 0 */
  0x02, 0x11, 0x01,	/* ID=2, Subsampling 2x1, Quantization table: 1 */
  0x03, 0x11, 0x01,	/* ID=3, Subsampling 2x1, Quantization table: 1 */

  0xff, 0xda,		/* SOS: Start Of Scan */
  0x00, 0x0c,		/* length = 12 bytes (including this length field) */
  0x03,			/* number of components: 3 */
  0x01, 0x00,		/* selector 1, table 0x00 */
  0x02, 0x11,		/* selector 2, table 0x11 */
  0x03, 0x11,		/* selector 3, table 0x11 */
  0x00, 0x3f,		/* Spectral selection: 0 .. 63 */
  0x00			/* Successive approximation: 0 */
पूर्ण;

अटल व्योम pac_start_frame(काष्ठा gspca_dev *gspca_dev,
		__u16 lines, __u16 samples_per_line)
अणु
	अचिन्हित अक्षर पंचांगpbuf[4];

	gspca_frame_add(gspca_dev, FIRST_PACKET,
		pac_jpeg_header1, माप(pac_jpeg_header1));

	पंचांगpbuf[0] = lines >> 8;
	पंचांगpbuf[1] = lines & 0xff;
	पंचांगpbuf[2] = samples_per_line >> 8;
	पंचांगpbuf[3] = samples_per_line & 0xff;

	gspca_frame_add(gspca_dev, INTER_PACKET,
		पंचांगpbuf, माप(पंचांगpbuf));
	gspca_frame_add(gspca_dev, INTER_PACKET,
		pac_jpeg_header2, माप(pac_jpeg_header2));
पूर्ण

/* this function is run at पूर्णांकerrupt level */
अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 *image;
	अचिन्हित अक्षर *sof;

	sof = pac_find_sof(gspca_dev, &sd->sof_पढ़ो, data, len);
	अगर (sof) अणु
		पूर्णांक n, lum_offset, footer_length;

		/*
		 * 6 bytes after the FF D9 खातापूर्ण marker a number of lumination
		 * bytes are send corresponding to dअगरferent parts of the
		 * image, the 14th and 15th byte after the खातापूर्ण seem to
		 * correspond to the center of the image.
		 */
		lum_offset = 24 + माप pac_sof_marker;
		footer_length = 26;

		/* Finish decoding current frame */
		n = (sof - data) - (footer_length + माप pac_sof_marker);
		अगर (n < 0) अणु
			gspca_dev->image_len += n;
			n = 0;
		पूर्ण अन्यथा अणु
			gspca_frame_add(gspca_dev, INTER_PACKET, data, n);
		पूर्ण
		image = gspca_dev->image;
		अगर (image != शून्य
		 && image[gspca_dev->image_len - 2] == 0xff
		 && image[gspca_dev->image_len - 1] == 0xd9)
			gspca_frame_add(gspca_dev, LAST_PACKET, शून्य, 0);

		n = sof - data;
		len -= n;
		data = sof;

		/* Get average lumination */
		अगर (gspca_dev->last_packet_type == LAST_PACKET &&
				n >= lum_offset)
			atomic_set(&sd->avg_lum, data[-lum_offset] +
						data[-lum_offset + 1]);
		अन्यथा
			atomic_set(&sd->avg_lum, -1);

		/* Start the new frame with the jpeg header */
		pac_start_frame(gspca_dev,
			gspca_dev->pixfmt.height, gspca_dev->pixfmt.width);
	पूर्ण
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
पूर्ण

#अगर IS_ENABLED(CONFIG_INPUT)
अटल पूर्णांक sd_पूर्णांक_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,		/* पूर्णांकerrupt packet data */
			पूर्णांक len)		/* पूर्णांकerrupt packet length */
अणु
	पूर्णांक ret = -EINVAL;
	u8 data0, data1;

	अगर (len == 2) अणु
		data0 = data[0];
		data1 = data[1];
		अगर ((data0 == 0x00 && data1 == 0x11) ||
		    (data0 == 0x22 && data1 == 0x33) ||
		    (data0 == 0x44 && data1 == 0x55) ||
		    (data0 == 0x66 && data1 == 0x77) ||
		    (data0 == 0x88 && data1 == 0x99) ||
		    (data0 == 0xaa && data1 == 0xbb) ||
		    (data0 == 0xcc && data1 == 0xdd) ||
		    (data0 == 0xee && data1 == 0xff)) अणु
			input_report_key(gspca_dev->input_dev, KEY_CAMERA, 1);
			input_sync(gspca_dev->input_dev);
			input_report_key(gspca_dev->input_dev, KEY_CAMERA, 0);
			input_sync(gspca_dev->input_dev);
			ret = 0;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name = MODULE_NAME,
	.config = sd_config,
	.init = sd_init,
	.init_controls = sd_init_controls,
	.start = sd_start,
	.stopN = sd_stopN,
	.pkt_scan = sd_pkt_scan,
	.dq_callback = करो_स्वतःgain,
#अगर IS_ENABLED(CONFIG_INPUT)
	.पूर्णांक_pkt_scan = sd_पूर्णांक_pkt_scan,
#पूर्ण_अगर
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x093a, 0x2600)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2601)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2603)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2608)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x260e)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x260f)पूर्ण,
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
