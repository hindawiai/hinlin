<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम the sensor part which is पूर्णांकegrated (I think) पूर्णांकo the
 * st6422 stv06xx alike bridge, as its पूर्णांकegrated there are no i2c ग_लिखोs
 * but instead direct bridge ग_लिखोs.
 *
 * Copyright (c) 2009 Hans de Goede <hdegoede@redhat.com>
 *
 * Strongly based on qc-usb-messenger, which is:
 * Copyright (c) 2001 Jean-Fredric Clere, Nikolas Zimmermann, Georg Acher
 *		      Mark Cave-Ayland, Carlo E Prelz, Dick Streefland
 * Copyright (c) 2002, 2003 Tuukka Toivonen
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "stv06xx_st6422.h"

अटल काष्ठा v4l2_pix_क्रमmat st6422_mode[] = अणु
	/* Note we actually get 124 lines of data, of which we skip the 4st
	   4 as they are garbage */
	अणु
		162,
		120,
		V4L2_PIX_FMT_SGRBG8,
		V4L2_FIELD_NONE,
		.sizeimage = 162 * 120,
		.bytesperline = 162,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1
	पूर्ण,
	/* Note we actually get 248 lines of data, of which we skip the 4st
	   4 as they are garbage, and we tell the app it only माला_लो the
	   first 240 of the 244 lines it actually माला_लो, so that it ignores
	   the last 4. */
	अणु
		324,
		240,
		V4L2_PIX_FMT_SGRBG8,
		V4L2_FIELD_NONE,
		.sizeimage = 324 * 244,
		.bytesperline = 324,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0
	पूर्ण,
पूर्ण;

/* V4L2 controls supported by the driver */
अटल पूर्णांक setbrightness(काष्ठा sd *sd, s32 val);
अटल पूर्णांक setcontrast(काष्ठा sd *sd, s32 val);
अटल पूर्णांक setgain(काष्ठा sd *sd, u8 gain);
अटल पूर्णांक setexposure(काष्ठा sd *sd, s16 expo);

अटल पूर्णांक st6422_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	पूर्णांक err = -EINVAL;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		err = setbrightness(sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		err = setcontrast(sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_GAIN:
		err = setgain(sd, ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE:
		err = setexposure(sd, ctrl->val);
		अवरोध;
	पूर्ण

	/* commit settings */
	अगर (err >= 0)
		err = stv06xx_ग_लिखो_bridge(sd, 0x143f, 0x01);
	sd->gspca_dev.usb_err = err;
	वापस err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops st6422_ctrl_ops = अणु
	.s_ctrl = st6422_s_ctrl,
पूर्ण;

अटल पूर्णांक st6422_init_controls(काष्ठा sd *sd)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &sd->gspca_dev.ctrl_handler;

	v4l2_ctrl_handler_init(hdl, 4);
	v4l2_ctrl_new_std(hdl, &st6422_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 31, 1, 3);
	v4l2_ctrl_new_std(hdl, &st6422_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 15, 1, 11);
	v4l2_ctrl_new_std(hdl, &st6422_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 1023, 1, 256);
	v4l2_ctrl_new_std(hdl, &st6422_ctrl_ops,
			V4L2_CID_GAIN, 0, 255, 1, 64);

	वापस hdl->error;
पूर्ण

अटल पूर्णांक st6422_probe(काष्ठा sd *sd)
अणु
	अगर (sd->bridge != BRIDGE_ST6422)
		वापस -ENODEV;

	pr_info("st6422 sensor detected\n");

	sd->gspca_dev.cam.cam_mode = st6422_mode;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(st6422_mode);
	वापस 0;
पूर्ण

अटल पूर्णांक st6422_init(काष्ठा sd *sd)
अणु
	पूर्णांक err = 0, i;

	अटल स्थिर u16 st6422_bridge_init[][2] = अणु
		अणु STV_ISO_ENABLE, 0x00 पूर्ण, /* disable capture */
		अणु 0x1436, 0x00 पूर्ण,
		अणु 0x1432, 0x03 पूर्ण,	/* 0x00-0x1F brightness */
		अणु 0x143a, 0xf9 पूर्ण,	/* 0x00-0x0F contrast */
		अणु 0x0509, 0x38 पूर्ण,	/* R */
		अणु 0x050a, 0x38 पूर्ण,	/* G */
		अणु 0x050b, 0x38 पूर्ण,	/* B */
		अणु 0x050c, 0x2a पूर्ण,
		अणु 0x050d, 0x01 पूर्ण,


		अणु 0x1431, 0x00 पूर्ण,	/* 0x00-0x07 ??? */
		अणु 0x1433, 0x34 पूर्ण,	/* 160x120, 0x00-0x01 night filter */
		अणु 0x1438, 0x18 पूर्ण,	/* 640x480 */
/* 18 bayes */
/* 10 compressed? */

		अणु 0x1439, 0x00 पूर्ण,
/* anti-noise?  0xa2 gives a perfect image */

		अणु 0x143b, 0x05 पूर्ण,
		अणु 0x143c, 0x00 पूर्ण,	/* 0x00-0x01 - ??? */


/* shutter समय 0x0000-0x03FF */
/* low value  give good picures on moving objects (but requires much light) */
/* high value gives good picures in darkness (but tends to be overexposed) */
		अणु 0x143e, 0x01 पूर्ण,
		अणु 0x143d, 0x00 पूर्ण,

		अणु 0x1442, 0xe2 पूर्ण,
/* ग_लिखो: 1x1x xxxx */
/* पढ़ो:  1x1x xxxx */
/*        bit 5 == button pressed and hold अगर 0 */
/* ग_लिखो 0xe2,0xea */

/* 0x144a */
/* 0x00 init */
/* bit 7 == button has been pressed, but not handled */

/* पूर्णांकerrupt */
/* अगर(urb->iso_frame_desc[i].status == 0x80) अणु */
/* अगर(urb->iso_frame_desc[i].status == 0x88) अणु */

		अणु 0x1500, 0xd0 पूर्ण,
		अणु 0x1500, 0xd0 पूर्ण,
		अणु 0x1500, 0x50 पूर्ण,	/* 0x00 - 0xFF  0x80 == compr ? */

		अणु 0x1501, 0xaf पूर्ण,
/* high val-> light area माला_लो darker */
/* low val -> light area माला_लो lighter */
		अणु 0x1502, 0xc2 पूर्ण,
/* high val-> light area माला_लो darker */
/* low val -> light area माला_लो lighter */
		अणु 0x1503, 0x45 पूर्ण,
/* high val-> light area माला_लो darker */
/* low val -> light area माला_लो lighter */
		अणु 0x1505, 0x02 पूर्ण,
/* 2  : 324x248  80352 bytes */
/* 7  : 248x162  40176 bytes */
/* c+f: 162*124  20088 bytes */

		अणु 0x150e, 0x8e पूर्ण,
		अणु 0x150f, 0x37 पूर्ण,
		अणु 0x15c0, 0x00 पूर्ण,
		अणु 0x15c3, 0x08 पूर्ण,	/* 0x04/0x14 ... test pictures ??? */


		अणु 0x143f, 0x01 पूर्ण,	/* commit settings */

	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(st6422_bridge_init) && !err; i++) अणु
		err = stv06xx_ग_लिखो_bridge(sd, st6422_bridge_init[i][0],
					       st6422_bridge_init[i][1]);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक setbrightness(काष्ठा sd *sd, s32 val)
अणु
	/* val goes from 0 -> 31 */
	वापस stv06xx_ग_लिखो_bridge(sd, 0x1432, val);
पूर्ण

अटल पूर्णांक setcontrast(काष्ठा sd *sd, s32 val)
अणु
	/* Val goes from 0 -> 15 */
	वापस stv06xx_ग_लिखो_bridge(sd, 0x143a, val | 0xf0);
पूर्ण

अटल पूर्णांक setgain(काष्ठा sd *sd, u8 gain)
अणु
	पूर्णांक err;

	/* Set red, green, blue, gain */
	err = stv06xx_ग_लिखो_bridge(sd, 0x0509, gain);
	अगर (err < 0)
		वापस err;

	err = stv06xx_ग_लिखो_bridge(sd, 0x050a, gain);
	अगर (err < 0)
		वापस err;

	err = stv06xx_ग_लिखो_bridge(sd, 0x050b, gain);
	अगर (err < 0)
		वापस err;

	/* 2 mystery ग_लिखोs */
	err = stv06xx_ग_लिखो_bridge(sd, 0x050c, 0x2a);
	अगर (err < 0)
		वापस err;

	वापस stv06xx_ग_लिखो_bridge(sd, 0x050d, 0x01);
पूर्ण

अटल पूर्णांक setexposure(काष्ठा sd *sd, s16 expo)
अणु
	पूर्णांक err;

	err = stv06xx_ग_लिखो_bridge(sd, 0x143d, expo & 0xff);
	अगर (err < 0)
		वापस err;

	वापस stv06xx_ग_लिखो_bridge(sd, 0x143e, expo >> 8);
पूर्ण

अटल पूर्णांक st6422_start(काष्ठा sd *sd)
अणु
	पूर्णांक err;
	काष्ठा cam *cam = &sd->gspca_dev.cam;

	अगर (cam->cam_mode[sd->gspca_dev.curr_mode].priv)
		err = stv06xx_ग_लिखो_bridge(sd, 0x1505, 0x0f);
	अन्यथा
		err = stv06xx_ग_लिखो_bridge(sd, 0x1505, 0x02);
	अगर (err < 0)
		वापस err;

	/* commit settings */
	err = stv06xx_ग_लिखो_bridge(sd, 0x143f, 0x01);
	वापस (err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक st6422_stop(काष्ठा sd *sd)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;

	gspca_dbg(gspca_dev, D_STREAM, "Halting stream\n");

	वापस 0;
पूर्ण
