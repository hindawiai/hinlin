<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Pixart PAC207BCA library
 *
 * Copyright (C) 2008 Hans de Goede <hdegoede@redhat.com>
 * Copyright (C) 2005 Thomas Kaiser thomas@kaiser-linux.li
 * Copyleft (C) 2005 Michel Xhaard mxhaard@magic.fr
 *
 * V4L2 by Jean-Francois Moine <http://moinejf.मुक्त.fr>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "pac207"

#समावेश <linux/input.h>
#समावेश "gspca.h"
/* Include pac common sof detection functions */
#समावेश "pac_common.h"

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("Pixart PAC207");
MODULE_LICENSE("GPL");

#घोषणा PAC207_CTRL_TIMEOUT		100  /* ms */

#घोषणा PAC207_BRIGHTNESS_MIN		0
#घोषणा PAC207_BRIGHTNESS_MAX		255
#घोषणा PAC207_BRIGHTNESS_DEFAULT	46
#घोषणा PAC207_BRIGHTNESS_REG		0x08

#घोषणा PAC207_EXPOSURE_MIN		3
#घोषणा PAC207_EXPOSURE_MAX		90 /* 1 sec expo समय / 1 fps */
#घोषणा PAC207_EXPOSURE_DEFAULT		5 /* घातer on शेष: 3 */
#घोषणा PAC207_EXPOSURE_REG		0x02

#घोषणा PAC207_GAIN_MIN			0
#घोषणा PAC207_GAIN_MAX			31
#घोषणा PAC207_GAIN_DEFAULT		7 /* घातer on शेष: 9 */
#घोषणा PAC207_GAIN_REG			0x0e

#घोषणा PAC207_AUTOGAIN_DEADZONE	30

/* global parameters */
अटल पूर्णांक led_invert;
module_param(led_invert, पूर्णांक, 0644);
MODULE_PARM_DESC(led_invert, "Invert led");

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;		/* !! must be the first item */

	काष्ठा v4l2_ctrl *brightness;

	u8 mode;
	u8 sof_पढ़ो;
	u8 header_पढ़ो;
	u8 स्वतःgain_ignore_frames;

	atomic_t avg_lum;
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat sअगर_mode[] = अणु
	अणु176, 144, V4L2_PIX_FMT_PAC207, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = (176 + 2) * 144,
			/* uncompressed, add 2 bytes / line क्रम line header */
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1पूर्ण,
	अणु352, 288, V4L2_PIX_FMT_PAC207, V4L2_FIELD_NONE,
		.bytesperline = 352,
			/* compressed, but only when needed (not compressed
			   when the framerate is low) */
		.sizeimage = (352 + 2) * 288,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
पूर्ण;

अटल स्थिर __u8 pac207_sensor_init[][8] = अणु
	अणु0x10, 0x12, 0x0d, 0x12, 0x0c, 0x01, 0x29, 0x84पूर्ण,
	अणु0x49, 0x64, 0x64, 0x64, 0x04, 0x10, 0xf0, 0x30पूर्ण,
	अणु0x00, 0x00, 0x00, 0x70, 0xa0, 0xf8, 0x00, 0x00पूर्ण,
	अणु0x32, 0x00, 0x96, 0x00, 0xa2, 0x02, 0xaf, 0x00पूर्ण,
पूर्ण;

अटल व्योम pac207_ग_लिखो_regs(काष्ठा gspca_dev *gspca_dev, u16 index,
	स्थिर u8 *buffer, u16 length)
अणु
	काष्ठा usb_device *udev = gspca_dev->dev;
	पूर्णांक err;

	अगर (gspca_dev->usb_err < 0)
		वापस;

	स_नकल(gspca_dev->usb_buf, buffer, length);

	err = usb_control_msg(udev, usb_sndctrlpipe(udev, 0), 0x01,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			0x00, index,
			gspca_dev->usb_buf, length, PAC207_CTRL_TIMEOUT);
	अगर (err < 0) अणु
		pr_err("Failed to write registers to index 0x%04X, error %d\n",
		       index, err);
		gspca_dev->usb_err = err;
	पूर्ण
पूर्ण

अटल व्योम pac207_ग_लिखो_reg(काष्ठा gspca_dev *gspca_dev, u16 index, u16 value)
अणु
	काष्ठा usb_device *udev = gspca_dev->dev;
	पूर्णांक err;

	अगर (gspca_dev->usb_err < 0)
		वापस;

	err = usb_control_msg(udev, usb_sndctrlpipe(udev, 0), 0x00,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			value, index, शून्य, 0, PAC207_CTRL_TIMEOUT);
	अगर (err) अणु
		pr_err("Failed to write a register (index 0x%04X, value 0x%02X, error %d)\n",
		       index, value, err);
		gspca_dev->usb_err = err;
	पूर्ण
पूर्ण

अटल पूर्णांक pac207_पढ़ो_reg(काष्ठा gspca_dev *gspca_dev, u16 index)
अणु
	काष्ठा usb_device *udev = gspca_dev->dev;
	पूर्णांक res;

	अगर (gspca_dev->usb_err < 0)
		वापस 0;

	res = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0), 0x00,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			0x00, index,
			gspca_dev->usb_buf, 1, PAC207_CTRL_TIMEOUT);
	अगर (res < 0) अणु
		pr_err("Failed to read a register (index 0x%04X, error %d)\n",
		       index, res);
		gspca_dev->usb_err = res;
		वापस 0;
	पूर्ण

	वापस gspca_dev->usb_buf[0];
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा cam *cam;
	u8 idreg[2];

	idreg[0] = pac207_पढ़ो_reg(gspca_dev, 0x0000);
	idreg[1] = pac207_पढ़ो_reg(gspca_dev, 0x0001);
	idreg[0] = ((idreg[0] & 0x0f) << 4) | ((idreg[1] & 0xf0) >> 4);
	idreg[1] = idreg[1] & 0x0f;
	gspca_dbg(gspca_dev, D_PROBE, "Pixart Sensor ID 0x%02X Chips ID 0x%02X\n",
		  idreg[0], idreg[1]);

	अगर (idreg[0] != 0x27) अणु
		gspca_dbg(gspca_dev, D_PROBE, "Error invalid sensor ID!\n");
		वापस -ENODEV;
	पूर्ण

	gspca_dbg(gspca_dev, D_PROBE,
		  "Pixart PAC207BCA Image Processor and Control Chip detected (vid/pid 0x%04X:0x%04X)\n",
		  id->idVenकरोr, id->idProduct);

	cam = &gspca_dev->cam;
	cam->cam_mode = sअगर_mode;
	cam->nmodes = ARRAY_SIZE(sअगर_mode);

	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	u8 mode;

	/* mode: Image Format (Bit 0), LED (1), Compr. test mode (2) */
	अगर (led_invert)
		mode = 0x02;
	अन्यथा
		mode = 0x00;
	pac207_ग_लिखो_reg(gspca_dev, 0x41, mode);
	pac207_ग_लिखो_reg(gspca_dev, 0x0f, 0x00); /* Power Control */

	वापस gspca_dev->usb_err;
पूर्ण

अटल व्योम setcontrol(काष्ठा gspca_dev *gspca_dev, u16 reg, u16 val)
अणु
	pac207_ग_लिखो_reg(gspca_dev, reg, val);
	pac207_ग_लिखो_reg(gspca_dev, 0x13, 0x01);	/* Bit 0, स्वतः clear */
	pac207_ग_लिखो_reg(gspca_dev, 0x1c, 0x01);	/* not करोcumented */
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
		gspca_dev->exposure->val    = PAC207_EXPOSURE_DEFAULT;
		gspca_dev->gain->val        = PAC207_GAIN_DEFAULT;
		sd->स्वतःgain_ignore_frames  = PAC_AUTOGAIN_IGNORE_FRAMES;
	पूर्ण

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		setcontrol(gspca_dev, PAC207_BRIGHTNESS_REG, ctrl->val);
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		अगर (gspca_dev->exposure->is_new || (ctrl->is_new && ctrl->val))
			setcontrol(gspca_dev, PAC207_EXPOSURE_REG,
				   gspca_dev->exposure->val);
		अगर (gspca_dev->gain->is_new || (ctrl->is_new && ctrl->val))
			setcontrol(gspca_dev, PAC207_GAIN_REG,
				   gspca_dev->gain->val);
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
	v4l2_ctrl_handler_init(hdl, 4);

	sd->brightness = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				V4L2_CID_BRIGHTNESS,
				PAC207_BRIGHTNESS_MIN, PAC207_BRIGHTNESS_MAX,
				1, PAC207_BRIGHTNESS_DEFAULT);
	gspca_dev->स्वतःgain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	gspca_dev->exposure = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				V4L2_CID_EXPOSURE,
				PAC207_EXPOSURE_MIN, PAC207_EXPOSURE_MAX,
				1, PAC207_EXPOSURE_DEFAULT);
	gspca_dev->gain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				V4L2_CID_GAIN,
				PAC207_GAIN_MIN, PAC207_GAIN_MAX,
				1, PAC207_GAIN_DEFAULT);
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
	__u8 mode;

	pac207_ग_लिखो_reg(gspca_dev, 0x0f, 0x10); /* Power control (Bit 6-0) */
	pac207_ग_लिखो_regs(gspca_dev, 0x0002, pac207_sensor_init[0], 8);
	pac207_ग_लिखो_regs(gspca_dev, 0x000a, pac207_sensor_init[1], 8);
	pac207_ग_लिखो_regs(gspca_dev, 0x0012, pac207_sensor_init[2], 8);
	pac207_ग_लिखो_regs(gspca_dev, 0x0042, pac207_sensor_init[3], 8);

	/* Compression Balance */
	अगर (gspca_dev->pixfmt.width == 176)
		pac207_ग_लिखो_reg(gspca_dev, 0x4a, 0xff);
	अन्यथा
		pac207_ग_लिखो_reg(gspca_dev, 0x4a, 0x30);
	pac207_ग_लिखो_reg(gspca_dev, 0x4b, 0x00); /* Sram test value */
	pac207_ग_लिखो_reg(gspca_dev, 0x08, v4l2_ctrl_g_ctrl(sd->brightness));

	/* PGA global gain (Bit 4-0) */
	pac207_ग_लिखो_reg(gspca_dev, 0x0e,
		v4l2_ctrl_g_ctrl(gspca_dev->gain));
	pac207_ग_लिखो_reg(gspca_dev, 0x02,
		v4l2_ctrl_g_ctrl(gspca_dev->exposure)); /* PXCK = 12MHz /n */

	/* mode: Image Format (Bit 0), LED (1), Compr. test mode (2) */
	अगर (led_invert)
		mode = 0x00;
	अन्यथा
		mode = 0x02;
	अगर (gspca_dev->pixfmt.width == 176) अणु	/* 176x144 */
		mode |= 0x01;
		gspca_dbg(gspca_dev, D_STREAM, "pac207_start mode 176x144\n");
	पूर्ण अन्यथा अणु				/* 352x288 */
		gspca_dbg(gspca_dev, D_STREAM, "pac207_start mode 352x288\n");
	पूर्ण
	pac207_ग_लिखो_reg(gspca_dev, 0x41, mode);

	pac207_ग_लिखो_reg(gspca_dev, 0x13, 0x01); /* Bit 0, स्वतः clear */
	pac207_ग_लिखो_reg(gspca_dev, 0x1c, 0x01); /* not करोcumented */
	msleep(10);
	pac207_ग_लिखो_reg(gspca_dev, 0x40, 0x01); /* Start ISO pipe */

	sd->sof_पढ़ो = 0;
	sd->स्वतःgain_ignore_frames = 0;
	atomic_set(&sd->avg_lum, -1);
	वापस gspca_dev->usb_err;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	u8 mode;

	/* mode: Image Format (Bit 0), LED (1), Compr. test mode (2) */
	अगर (led_invert)
		mode = 0x02;
	अन्यथा
		mode = 0x00;
	pac207_ग_लिखो_reg(gspca_dev, 0x40, 0x00); /* Stop ISO pipe */
	pac207_ग_लिखो_reg(gspca_dev, 0x41, mode); /* Turn off LED */
	pac207_ग_लिखो_reg(gspca_dev, 0x0f, 0x00); /* Power Control */
पूर्ण


अटल व्योम pac207_करो_स्वतः_gain(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक avg_lum = atomic_पढ़ो(&sd->avg_lum);

	अगर (avg_lum == -1)
		वापस;

	अगर (sd->स्वतःgain_ignore_frames > 0)
		sd->स्वतःgain_ignore_frames--;
	अन्यथा अगर (gspca_coarse_grained_expo_स्वतःgain(gspca_dev, avg_lum,
			90, PAC207_AUTOGAIN_DEADZONE))
		sd->स्वतःgain_ignore_frames = PAC_AUTOGAIN_IGNORE_FRAMES;
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,
			पूर्णांक len)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	अचिन्हित अक्षर *sof;

	sof = pac_find_sof(gspca_dev, &sd->sof_पढ़ो, data, len);
	अगर (sof) अणु
		पूर्णांक n;

		/* finish decoding current frame */
		n = sof - data;
		अगर (n > माप pac_sof_marker)
			n -= माप pac_sof_marker;
		अन्यथा
			n = 0;
		gspca_frame_add(gspca_dev, LAST_PACKET,
				data, n);
		sd->header_पढ़ो = 0;
		gspca_frame_add(gspca_dev, FIRST_PACKET, शून्य, 0);
		len -= sof - data;
		data = sof;
	पूर्ण
	अगर (sd->header_पढ़ो < 11) अणु
		पूर्णांक needed;

		/* get average lumination from frame header (byte 5) */
		अगर (sd->header_पढ़ो < 5) अणु
			needed = 5 - sd->header_पढ़ो;
			अगर (len >= needed)
				atomic_set(&sd->avg_lum, data[needed - 1]);
		पूर्ण
		/* skip the rest of the header */
		needed = 11 - sd->header_पढ़ो;
		अगर (len <= needed) अणु
			sd->header_पढ़ो += len;
			वापस;
		पूर्ण
		data += needed;
		len -= needed;
		sd->header_पढ़ो = 11;
	पूर्ण

	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
पूर्ण

#अगर IS_ENABLED(CONFIG_INPUT)
अटल पूर्णांक sd_पूर्णांक_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,		/* पूर्णांकerrupt packet data */
			पूर्णांक len)		/* पूर्णांकerrupt packet length */
अणु
	पूर्णांक ret = -EINVAL;

	अगर (len == 2 && data[0] == 0x5a && data[1] == 0x5a) अणु
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, 1);
		input_sync(gspca_dev->input_dev);
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, 0);
		input_sync(gspca_dev->input_dev);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name = MODULE_NAME,
	.config = sd_config,
	.init = sd_init,
	.init_controls = sd_init_controls,
	.start = sd_start,
	.stopN = sd_stopN,
	.dq_callback = pac207_करो_स्वतः_gain,
	.pkt_scan = sd_pkt_scan,
#अगर IS_ENABLED(CONFIG_INPUT)
	.पूर्णांक_pkt_scan = sd_पूर्णांक_pkt_scan,
#पूर्ण_अगर
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x041e, 0x4028)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2460)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2461)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2463)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2464)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2468)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2470)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2471)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2472)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2474)पूर्ण,
	अणुUSB_DEVICE(0x093a, 0x2476)पूर्ण,
	अणुUSB_DEVICE(0x145f, 0x013a)पूर्ण,
	अणुUSB_DEVICE(0x2001, 0xf115)पूर्ण,
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
