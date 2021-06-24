<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Mars MR97310A library
 *
 * The original mr97310a driver, which supported the Aiptek Pencam VGA+, is
 * Copyright (C) 2009 Kyle Guinn <elyk03@gmail.com>
 *
 * Support क्रम the MR97310A cameras in addition to the Aiptek Pencam VGA+
 * and क्रम the routines क्रम detecting and classअगरying these various cameras,
 * is Copyright (C) 2009 Theoकरोre Kilgore <kilgota@auburn.edu>
 *
 * Support क्रम the control settings क्रम the CIF cameras is
 * Copyright (C) 2009 Hans de Goede <hdegoede@redhat.com> and
 * Thomas Kaiser <thomas@kaiser-linux.li>
 *
 * Support क्रम the control settings क्रम the VGA cameras is
 * Copyright (C) 2009 Theoकरोre Kilgore <kilgota@auburn.edu>
 *
 * Several previously unsupported cameras are owned and have been tested by
 * Hans de Goede <hdegoede@redhat.com> and
 * Thomas Kaiser <thomas@kaiser-linux.li> and
 * Theoकरोre Kilgore <kilgota@auburn.edu> and
 * Edmond Rodriguez <erodrig_97@yahoo.com> and
 * Aurelien Jacobs <aurel@gnuage.org>
 *
 * The MR97311A support in gspca/mars.c has been helpful in understanding some
 * of the रेजिस्टरs in these cameras.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "mr97310a"

#समावेश "gspca.h"

#घोषणा CAM_TYPE_CIF			0
#घोषणा CAM_TYPE_VGA			1

#घोषणा MR97310A_BRIGHTNESS_DEFAULT	0

#घोषणा MR97310A_EXPOSURE_MIN		0
#घोषणा MR97310A_EXPOSURE_MAX		4095
#घोषणा MR97310A_EXPOSURE_DEFAULT	1000

#घोषणा MR97310A_GAIN_MIN		0
#घोषणा MR97310A_GAIN_MAX		31
#घोषणा MR97310A_GAIN_DEFAULT		25

#घोषणा MR97310A_CONTRAST_MIN		0
#घोषणा MR97310A_CONTRAST_MAX		31
#घोषणा MR97310A_CONTRAST_DEFAULT	23

#घोषणा MR97310A_CS_GAIN_MIN		0
#घोषणा MR97310A_CS_GAIN_MAX		0x7ff
#घोषणा MR97310A_CS_GAIN_DEFAULT	0x110

#घोषणा MR97310A_CID_CLOCKDIV (V4L2_CTRL_CLASS_USER + 0x1000)
#घोषणा MR97310A_MIN_CLOCKDIV_MIN	3
#घोषणा MR97310A_MIN_CLOCKDIV_MAX	8
#घोषणा MR97310A_MIN_CLOCKDIV_DEFAULT	3

MODULE_AUTHOR("Kyle Guinn <elyk03@gmail.com>,Theodore Kilgore <kilgota@auburn.edu>");
MODULE_DESCRIPTION("GSPCA/Mars-Semi MR97310A USB Camera Driver");
MODULE_LICENSE("GPL");

/* global parameters */
अटल पूर्णांक क्रमce_sensor_type = -1;
module_param(क्रमce_sensor_type, पूर्णांक, 0644);
MODULE_PARM_DESC(क्रमce_sensor_type, "Force sensor type (-1 (auto), 0 or 1)");

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;  /* !! must be the first item */
	काष्ठा अणु /* exposure/min_घड़ीभाग control cluster */
		काष्ठा v4l2_ctrl *exposure;
		काष्ठा v4l2_ctrl *min_घड़ीभाग;
	पूर्ण;
	u8 sof_पढ़ो;
	u8 cam_type;	/* 0 is CIF and 1 is VGA */
	u8 sensor_type;	/* We use 0 and 1 here, too. */
	u8 करो_lcd_stop;
	u8 adj_colors;
पूर्ण;

काष्ठा sensor_w_data अणु
	u8 reg;
	u8 flags;
	u8 data[16];
	पूर्णांक len;
पूर्ण;

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev);

अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_mode[] = अणु
	अणु160, 120, V4L2_PIX_FMT_MR97310A, V4L2_FIELD_NONE,
		.bytesperline = 160,
		.sizeimage = 160 * 120,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 4पूर्ण,
	अणु176, 144, V4L2_PIX_FMT_MR97310A, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 3पूर्ण,
	अणु320, 240, V4L2_PIX_FMT_MR97310A, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 2पूर्ण,
	अणु352, 288, V4L2_PIX_FMT_MR97310A, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 352 * 288,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1पूर्ण,
	अणु640, 480, V4L2_PIX_FMT_MR97310A, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
पूर्ण;

/* the bytes to ग_लिखो are in gspca_dev->usb_buf */
अटल पूर्णांक mr_ग_लिखो(काष्ठा gspca_dev *gspca_dev, पूर्णांक len)
अणु
	पूर्णांक rc;

	rc = usb_bulk_msg(gspca_dev->dev,
			  usb_sndbulkpipe(gspca_dev->dev, 4),
			  gspca_dev->usb_buf, len, शून्य, 500);
	अगर (rc < 0)
		pr_err("reg write [%02x] error %d\n",
		       gspca_dev->usb_buf[0], rc);
	वापस rc;
पूर्ण

/* the bytes are पढ़ो पूर्णांकo gspca_dev->usb_buf */
अटल पूर्णांक mr_पढ़ो(काष्ठा gspca_dev *gspca_dev, पूर्णांक len)
अणु
	पूर्णांक rc;

	rc = usb_bulk_msg(gspca_dev->dev,
			  usb_rcvbulkpipe(gspca_dev->dev, 3),
			  gspca_dev->usb_buf, len, शून्य, 500);
	अगर (rc < 0)
		pr_err("reg read [%02x] error %d\n",
		       gspca_dev->usb_buf[0], rc);
	वापस rc;
पूर्ण

अटल पूर्णांक sensor_ग_लिखो_reg(काष्ठा gspca_dev *gspca_dev, u8 reg, u8 flags,
	स्थिर u8 *data, पूर्णांक len)
अणु
	gspca_dev->usb_buf[0] = 0x1f;
	gspca_dev->usb_buf[1] = flags;
	gspca_dev->usb_buf[2] = reg;
	स_नकल(gspca_dev->usb_buf + 3, data, len);

	वापस mr_ग_लिखो(gspca_dev, len + 3);
पूर्ण

अटल पूर्णांक sensor_ग_लिखो_regs(काष्ठा gspca_dev *gspca_dev,
	स्थिर काष्ठा sensor_w_data *data, पूर्णांक len)
अणु
	पूर्णांक i, rc;

	क्रम (i = 0; i < len; i++) अणु
		rc = sensor_ग_लिखो_reg(gspca_dev, data[i].reg, data[i].flags,
					  data[i].data, data[i].len);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sensor_ग_लिखो1(काष्ठा gspca_dev *gspca_dev, u8 reg, u8 data)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 buf, confirm_reg;
	पूर्णांक rc;

	buf = data;
	अगर (sd->cam_type == CAM_TYPE_CIF) अणु
		rc = sensor_ग_लिखो_reg(gspca_dev, reg, 0x01, &buf, 1);
		confirm_reg = sd->sensor_type ? 0x13 : 0x11;
	पूर्ण अन्यथा अणु
		rc = sensor_ग_लिखो_reg(gspca_dev, reg, 0x00, &buf, 1);
		confirm_reg = 0x11;
	पूर्ण
	अगर (rc < 0)
		वापस rc;

	buf = 0x01;
	rc = sensor_ग_लिखो_reg(gspca_dev, confirm_reg, 0x00, &buf, 1);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक cam_get_response16(काष्ठा gspca_dev *gspca_dev, u8 reg, पूर्णांक verbose)
अणु
	पूर्णांक err_code;

	gspca_dev->usb_buf[0] = reg;
	err_code = mr_ग_लिखो(gspca_dev, 1);
	अगर (err_code < 0)
		वापस err_code;

	err_code = mr_पढ़ो(gspca_dev, 16);
	अगर (err_code < 0)
		वापस err_code;

	अगर (verbose)
		gspca_dbg(gspca_dev, D_PROBE, "Register: %02x reads %02x%02x%02x\n",
			  reg,
			  gspca_dev->usb_buf[0],
			  gspca_dev->usb_buf[1],
			  gspca_dev->usb_buf[2]);

	वापस 0;
पूर्ण

अटल पूर्णांक zero_the_poपूर्णांकer(काष्ठा gspca_dev *gspca_dev)
अणु
	__u8 *data = gspca_dev->usb_buf;
	पूर्णांक err_code;
	u8 status = 0;
	पूर्णांक tries = 0;

	err_code = cam_get_response16(gspca_dev, 0x21, 0);
	अगर (err_code < 0)
		वापस err_code;

	data[0] = 0x19;
	data[1] = 0x51;
	err_code = mr_ग_लिखो(gspca_dev, 2);
	अगर (err_code < 0)
		वापस err_code;

	err_code = cam_get_response16(gspca_dev, 0x21, 0);
	अगर (err_code < 0)
		वापस err_code;

	data[0] = 0x19;
	data[1] = 0xba;
	err_code = mr_ग_लिखो(gspca_dev, 2);
	अगर (err_code < 0)
		वापस err_code;

	err_code = cam_get_response16(gspca_dev, 0x21, 0);
	अगर (err_code < 0)
		वापस err_code;

	data[0] = 0x19;
	data[1] = 0x00;
	err_code = mr_ग_लिखो(gspca_dev, 2);
	अगर (err_code < 0)
		वापस err_code;

	err_code = cam_get_response16(gspca_dev, 0x21, 0);
	अगर (err_code < 0)
		वापस err_code;

	data[0] = 0x19;
	data[1] = 0x00;
	err_code = mr_ग_लिखो(gspca_dev, 2);
	अगर (err_code < 0)
		वापस err_code;

	जबतक (status != 0x0a && tries < 256) अणु
		err_code = cam_get_response16(gspca_dev, 0x21, 0);
		status = data[0];
		tries++;
		अगर (err_code < 0)
			वापस err_code;
	पूर्ण
	अगर (status != 0x0a)
		gspca_err(gspca_dev, "status is %02x\n", status);

	tries = 0;
	जबतक (tries < 4) अणु
		data[0] = 0x19;
		data[1] = 0x00;
		err_code = mr_ग_लिखो(gspca_dev, 2);
		अगर (err_code < 0)
			वापस err_code;

		err_code = cam_get_response16(gspca_dev, 0x21, 0);
		tries++;
		अगर (err_code < 0)
			वापस err_code;
	पूर्ण

	data[0] = 0x19;
	err_code = mr_ग_लिखो(gspca_dev, 1);
	अगर (err_code < 0)
		वापस err_code;

	err_code = mr_पढ़ो(gspca_dev, 16);
	अगर (err_code < 0)
		वापस err_code;

	वापस 0;
पूर्ण

अटल पूर्णांक stream_start(काष्ठा gspca_dev *gspca_dev)
अणु
	gspca_dev->usb_buf[0] = 0x01;
	gspca_dev->usb_buf[1] = 0x01;
	वापस mr_ग_लिखो(gspca_dev, 2);
पूर्ण

अटल व्योम stream_stop(काष्ठा gspca_dev *gspca_dev)
अणु
	gspca_dev->usb_buf[0] = 0x01;
	gspca_dev->usb_buf[1] = 0x00;
	अगर (mr_ग_लिखो(gspca_dev, 2) < 0)
		gspca_err(gspca_dev, "Stream Stop failed\n");
पूर्ण

अटल व्योम lcd_stop(काष्ठा gspca_dev *gspca_dev)
अणु
	gspca_dev->usb_buf[0] = 0x19;
	gspca_dev->usb_buf[1] = 0x54;
	अगर (mr_ग_लिखो(gspca_dev, 2) < 0)
		gspca_err(gspca_dev, "LCD Stop failed\n");
पूर्ण

अटल पूर्णांक isoc_enable(काष्ठा gspca_dev *gspca_dev)
अणु
	gspca_dev->usb_buf[0] = 0x00;
	gspca_dev->usb_buf[1] = 0x4d;  /* ISOC transferring enable... */
	वापस mr_ग_लिखो(gspca_dev, 2);
पूर्ण

/* This function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam;
	पूर्णांक err_code;

	cam = &gspca_dev->cam;
	cam->cam_mode = vga_mode;
	cam->nmodes = ARRAY_SIZE(vga_mode);
	sd->करो_lcd_stop = 0;

	/* Several of the supported CIF cameras share the same USB ID but
	 * require dअगरferent initializations and dअगरferent control settings.
	 * The same is true of the VGA cameras. Thereक्रमe, we are क्रमced
	 * to start the initialization process in order to determine which
	 * camera is present. Some of the supported cameras require the
	 * memory poपूर्णांकer to be set to 0 as the very first item of business
	 * or अन्यथा they will not stream. So we करो that immediately.
	 */
	err_code = zero_the_poपूर्णांकer(gspca_dev);
	अगर (err_code < 0)
		वापस err_code;

	err_code = stream_start(gspca_dev);
	अगर (err_code < 0)
		वापस err_code;

	/* Now, the query क्रम sensor type. */
	err_code = cam_get_response16(gspca_dev, 0x07, 1);
	अगर (err_code < 0)
		वापस err_code;

	अगर (id->idProduct == 0x0110 || id->idProduct == 0x010e) अणु
		sd->cam_type = CAM_TYPE_CIF;
		cam->nmodes--;
		/*
		 * All but one of the known CIF cameras share the same USB ID,
		 * but two dअगरferent init routines are in use, and the control
		 * settings are dअगरferent, too. We need to detect which camera
		 * of the two known varieties is connected!
		 *
		 * A list of known CIF cameras follows. They all report either
		 * 0200 क्रम type 0 or 0300 क्रम type 1.
		 * If you have another to report, please करो
		 *
		 * Name		sd->sensor_type		reported by
		 *
		 * Sakar 56379 Spy-shot	0		T. Kilgore
		 * Innovage		0		T. Kilgore
		 * Vivitar Mini		0		H. De Goede
		 * Vivitar Mini		0		E. Rodriguez
		 * Vivitar Mini		1		T. Kilgore
		 * Elta-Media 8212dc	1		T. Kaiser
		 * Philips dig. keych.	1		T. Kilgore
		 * Trust Spyc@m 100	1		A. Jacobs
		 */
		चयन (gspca_dev->usb_buf[0]) अणु
		हाल 2:
			sd->sensor_type = 0;
			अवरोध;
		हाल 3:
			sd->sensor_type = 1;
			अवरोध;
		शेष:
			pr_err("Unknown CIF Sensor id : %02x\n",
			       gspca_dev->usb_buf[1]);
			वापस -ENODEV;
		पूर्ण
		gspca_dbg(gspca_dev, D_PROBE, "MR97310A CIF camera detected, sensor: %d\n",
			  sd->sensor_type);
	पूर्ण अन्यथा अणु
		sd->cam_type = CAM_TYPE_VGA;

		/*
		 * Here is a table of the responses to the query क्रम sensor
		 * type, from the known MR97310A VGA cameras. Six dअगरferent
		 * cameras of which five share the same USB ID.
		 *
		 * Name			gspca_dev->usb_buf[]	sd->sensor_type
		 *				sd->करो_lcd_stop
		 * Aiptek Pencam VGA+	0300		0		1
		 * ION digital		0300		0		1
		 * Argus DC-1620	0450		1		0
		 * Argus QuickClix	0420		1		1
		 * Sakar 77379 Digital	0350		0		1
		 * Sakar 1638x CyberPix	0120		0		2
		 *
		 * Based upon these results, we assume शेष settings
		 * and then correct as necessary, as follows.
		 *
		 */

		sd->sensor_type = 1;
		sd->करो_lcd_stop = 0;
		sd->adj_colors = 0;
		अगर (gspca_dev->usb_buf[0] == 0x01) अणु
			sd->sensor_type = 2;
		पूर्ण अन्यथा अगर ((gspca_dev->usb_buf[0] != 0x03) &&
					(gspca_dev->usb_buf[0] != 0x04)) अणु
			pr_err("Unknown VGA Sensor id Byte 0: %02x\n",
			       gspca_dev->usb_buf[0]);
			pr_err("Defaults assumed, may not work\n");
			pr_err("Please report this\n");
		पूर्ण
		/* Sakar Digital color needs to be adjusted. */
		अगर ((gspca_dev->usb_buf[0] == 0x03) &&
					(gspca_dev->usb_buf[1] == 0x50))
			sd->adj_colors = 1;
		अगर (gspca_dev->usb_buf[0] == 0x04) अणु
			sd->करो_lcd_stop = 1;
			चयन (gspca_dev->usb_buf[1]) अणु
			हाल 0x50:
				sd->sensor_type = 0;
				gspca_dbg(gspca_dev, D_PROBE, "sensor_type corrected to 0\n");
				अवरोध;
			हाल 0x20:
				/* Nothing to करो here. */
				अवरोध;
			शेष:
				pr_err("Unknown VGA Sensor id Byte 1: %02x\n",
				       gspca_dev->usb_buf[1]);
				pr_err("Defaults assumed, may not work\n");
				pr_err("Please report this\n");
			पूर्ण
		पूर्ण
		gspca_dbg(gspca_dev, D_PROBE, "MR97310A VGA camera detected, sensor: %d\n",
			  sd->sensor_type);
	पूर्ण
	/* Stop streaming as we've started it only to probe the sensor type. */
	sd_stopN(gspca_dev);

	अगर (क्रमce_sensor_type != -1) अणु
		sd->sensor_type = !!क्रमce_sensor_type;
		gspca_dbg(gspca_dev, D_PROBE, "Forcing sensor type to: %d\n",
			  sd->sensor_type);
	पूर्ण

	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक start_cअगर_cam(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	__u8 *data = gspca_dev->usb_buf;
	पूर्णांक err_code;
	अटल स्थिर __u8 startup_string[] = अणु
		0x00,
		0x0d,
		0x01,
		0x00, /* Hsize/8 क्रम 352 or 320 */
		0x00, /* Vsize/4 क्रम 288 or 240 */
		0x13, /* or 0xbb, depends on sensor */
		0x00, /* Hstart, depends on res. */
		0x00, /* reserved ? */
		0x00, /* Vstart, depends on res. and sensor */
		0x50, /* 0x54 to get 176 or 160 */
		0xc0
	पूर्ण;

	/* Note: Some of the above descriptions guessed from MR97113A driver */

	स_नकल(data, startup_string, 11);
	अगर (sd->sensor_type)
		data[5] = 0xbb;

	चयन (gspca_dev->pixfmt.width) अणु
	हाल 160:
		data[9] |= 0x04;  /* reg 8, 2:1 scale करोwn from 320 */
		fallthrough;
	हाल 320:
	शेष:
		data[3] = 0x28;			   /* reg 2, H size/8 */
		data[4] = 0x3c;			   /* reg 3, V size/4 */
		data[6] = 0x14;			   /* reg 5, H start  */
		data[8] = 0x1a + sd->sensor_type;  /* reg 7, V start  */
		अवरोध;
	हाल 176:
		data[9] |= 0x04;  /* reg 8, 2:1 scale करोwn from 352 */
		fallthrough;
	हाल 352:
		data[3] = 0x2c;			   /* reg 2, H size/8 */
		data[4] = 0x48;			   /* reg 3, V size/4 */
		data[6] = 0x06;			   /* reg 5, H start  */
		data[8] = 0x06 - sd->sensor_type;  /* reg 7, V start  */
		अवरोध;
	पूर्ण
	err_code = mr_ग_लिखो(gspca_dev, 11);
	अगर (err_code < 0)
		वापस err_code;

	अगर (!sd->sensor_type) अणु
		अटल स्थिर काष्ठा sensor_w_data cअगर_sensor0_init_data[] = अणु
			अणु0x02, 0x00, अणु0x03, 0x5a, 0xb5, 0x01,
				      0x0f, 0x14, 0x0f, 0x10पूर्ण, 8पूर्ण,
			अणु0x0c, 0x00, अणु0x04, 0x01, 0x01, 0x00, 0x1fपूर्ण, 5पूर्ण,
			अणु0x12, 0x00, अणु0x07पूर्ण, 1पूर्ण,
			अणु0x1f, 0x00, अणु0x06पूर्ण, 1पूर्ण,
			अणु0x27, 0x00, अणु0x04पूर्ण, 1पूर्ण,
			अणु0x29, 0x00, अणु0x0cपूर्ण, 1पूर्ण,
			अणु0x40, 0x00, अणु0x40, 0x00, 0x04पूर्ण, 3पूर्ण,
			अणु0x50, 0x00, अणु0x60पूर्ण, 1पूर्ण,
			अणु0x60, 0x00, अणु0x06पूर्ण, 1पूर्ण,
			अणु0x6b, 0x00, अणु0x85, 0x85, 0xc8, 0xc8, 0xc8, 0xc8पूर्ण, 6पूर्ण,
			अणु0x72, 0x00, अणु0x1e, 0x56पूर्ण, 2पूर्ण,
			अणु0x75, 0x00, अणु0x58, 0x40, 0xa2, 0x02, 0x31, 0x02,
				      0x31, 0x80, 0x00पूर्ण, 9पूर्ण,
			अणु0x11, 0x00, अणु0x01पूर्ण, 1पूर्ण,
			अणु0, 0, अणु0पूर्ण, 0पूर्ण
		पूर्ण;
		err_code = sensor_ग_लिखो_regs(gspca_dev, cअगर_sensor0_init_data,
					 ARRAY_SIZE(cअगर_sensor0_init_data));
	पूर्ण अन्यथा अणु	/* sd->sensor_type = 1 */
		अटल स्थिर काष्ठा sensor_w_data cअगर_sensor1_init_data[] = अणु
			/* Reg 3,4, 7,8 get set by the controls */
			अणु0x02, 0x00, अणु0x10पूर्ण, 1पूर्ण,
			अणु0x05, 0x01, अणु0x22पूर्ण, 1पूर्ण, /* 5/6 also seen as 65h/32h */
			अणु0x06, 0x01, अणु0x00पूर्ण, 1पूर्ण,
			अणु0x09, 0x02, अणु0x0eपूर्ण, 1पूर्ण,
			अणु0x0a, 0x02, अणु0x05पूर्ण, 1पूर्ण,
			अणु0x0b, 0x02, अणु0x05पूर्ण, 1पूर्ण,
			अणु0x0c, 0x02, अणु0x0fपूर्ण, 1पूर्ण,
			अणु0x0d, 0x02, अणु0x07पूर्ण, 1पूर्ण,
			अणु0x0e, 0x02, अणु0x0cपूर्ण, 1पूर्ण,
			अणु0x0f, 0x00, अणु0x00पूर्ण, 1पूर्ण,
			अणु0x10, 0x00, अणु0x06पूर्ण, 1पूर्ण,
			अणु0x11, 0x00, अणु0x07पूर्ण, 1पूर्ण,
			अणु0x12, 0x00, अणु0x00पूर्ण, 1पूर्ण,
			अणु0x13, 0x00, अणु0x01पूर्ण, 1पूर्ण,
			अणु0, 0, अणु0पूर्ण, 0पूर्ण
		पूर्ण;
		/* Without this command the cam won't work with USB-UHCI */
		gspca_dev->usb_buf[0] = 0x0a;
		gspca_dev->usb_buf[1] = 0x00;
		err_code = mr_ग_लिखो(gspca_dev, 2);
		अगर (err_code < 0)
			वापस err_code;
		err_code = sensor_ग_लिखो_regs(gspca_dev, cअगर_sensor1_init_data,
					 ARRAY_SIZE(cअगर_sensor1_init_data));
	पूर्ण
	वापस err_code;
पूर्ण

अटल पूर्णांक start_vga_cam(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	__u8 *data = gspca_dev->usb_buf;
	पूर्णांक err_code;
	अटल स्थिर __u8 startup_string[] =
		अणु0x00, 0x0d, 0x01, 0x00, 0x00, 0x2b, 0x00, 0x00,
		 0x00, 0x50, 0xc0पूर्ण;
	/* What some of these mean is explained in start_cअगर_cam(), above */

	स_नकल(data, startup_string, 11);
	अगर (!sd->sensor_type) अणु
		data[5]  = 0x00;
		data[10] = 0x91;
	पूर्ण
	अगर (sd->sensor_type == 2) अणु
		data[5]  = 0x00;
		data[10] = 0x18;
	पूर्ण

	चयन (gspca_dev->pixfmt.width) अणु
	हाल 160:
		data[9] |= 0x0c;  /* reg 8, 4:1 scale करोwn */
		fallthrough;
	हाल 320:
		data[9] |= 0x04;  /* reg 8, 2:1 scale करोwn */
		fallthrough;
	हाल 640:
	शेष:
		data[3] = 0x50;  /* reg 2, H size/8 */
		data[4] = 0x78;  /* reg 3, V size/4 */
		data[6] = 0x04;  /* reg 5, H start */
		data[8] = 0x03;  /* reg 7, V start */
		अगर (sd->sensor_type == 2) अणु
			data[6] = 2;
			data[8] = 1;
		पूर्ण
		अगर (sd->करो_lcd_stop)
			data[8] = 0x04;  /* Bayer tile shअगरted */
		अवरोध;

	हाल 176:
		data[9] |= 0x04;  /* reg 8, 2:1 scale करोwn */
		fallthrough;
	हाल 352:
		data[3] = 0x2c;  /* reg 2, H size */
		data[4] = 0x48;  /* reg 3, V size */
		data[6] = 0x94;  /* reg 5, H start */
		data[8] = 0x63;  /* reg 7, V start */
		अगर (sd->करो_lcd_stop)
			data[8] = 0x64;  /* Bayer tile shअगरted */
		अवरोध;
	पूर्ण

	err_code = mr_ग_लिखो(gspca_dev, 11);
	अगर (err_code < 0)
		वापस err_code;

	अगर (!sd->sensor_type) अणु
		अटल स्थिर काष्ठा sensor_w_data vga_sensor0_init_data[] = अणु
			अणु0x01, 0x00, अणु0x0c, 0x00, 0x04पूर्ण, 3पूर्ण,
			अणु0x14, 0x00, अणु0x01, 0xe4, 0x02, 0x84पूर्ण, 4पूर्ण,
			अणु0x20, 0x00, अणु0x00, 0x80, 0x00, 0x08पूर्ण, 4पूर्ण,
			अणु0x25, 0x00, अणु0x03, 0xa9, 0x80पूर्ण, 3पूर्ण,
			अणु0x30, 0x00, अणु0x30, 0x18, 0x10, 0x18पूर्ण, 4पूर्ण,
			अणु0, 0, अणु0पूर्ण, 0पूर्ण
		पूर्ण;
		err_code = sensor_ग_लिखो_regs(gspca_dev, vga_sensor0_init_data,
					 ARRAY_SIZE(vga_sensor0_init_data));
	पूर्ण अन्यथा अगर (sd->sensor_type == 1) अणु
		अटल स्थिर काष्ठा sensor_w_data color_adj[] = अणु
			अणु0x02, 0x00, अणु0x06, 0x59, 0x0c, 0x16, 0x00,
				/* adjusted blue, green, red gain correct
				   too much blue from the Sakar Digital */
				0x05, 0x01, 0x04पूर्ण, 8पूर्ण
		पूर्ण;

		अटल स्थिर काष्ठा sensor_w_data color_no_adj[] = अणु
			अणु0x02, 0x00, अणु0x06, 0x59, 0x0c, 0x16, 0x00,
				/* शेष blue, green, red gain settings */
				0x07, 0x00, 0x01पूर्ण, 8पूर्ण
		पूर्ण;

		अटल स्थिर काष्ठा sensor_w_data vga_sensor1_init_data[] = अणु
			अणु0x11, 0x04, अणु0x01पूर्ण, 1पूर्ण,
			अणु0x0a, 0x00, अणु0x00, 0x01, 0x00, 0x00, 0x01,
			/* These settings may be better क्रम some cameras */
			/* अणु0x0a, 0x00, अणु0x01, 0x06, 0x00, 0x00, 0x01, */
				0x00, 0x0aपूर्ण, 7पूर्ण,
			अणु0x11, 0x04, अणु0x01पूर्ण, 1पूर्ण,
			अणु0x12, 0x00, अणु0x00, 0x63, 0x00, 0x70, 0x00, 0x00पूर्ण, 6पूर्ण,
			अणु0x11, 0x04, अणु0x01पूर्ण, 1पूर्ण,
			अणु0, 0, अणु0पूर्ण, 0पूर्ण
		पूर्ण;

		अगर (sd->adj_colors)
			err_code = sensor_ग_लिखो_regs(gspca_dev, color_adj,
					 ARRAY_SIZE(color_adj));
		अन्यथा
			err_code = sensor_ग_लिखो_regs(gspca_dev, color_no_adj,
					 ARRAY_SIZE(color_no_adj));

		अगर (err_code < 0)
			वापस err_code;

		err_code = sensor_ग_लिखो_regs(gspca_dev, vga_sensor1_init_data,
					 ARRAY_SIZE(vga_sensor1_init_data));
	पूर्ण अन्यथा अणु	/* sensor type == 2 */
		अटल स्थिर काष्ठा sensor_w_data vga_sensor2_init_data[] = अणु

			अणु0x01, 0x00, अणु0x48पूर्ण, 1पूर्ण,
			अणु0x02, 0x00, अणु0x22पूर्ण, 1पूर्ण,
			/* Reg 3 msb and 4 is lsb of the exposure setting*/
			अणु0x05, 0x00, अणु0x10पूर्ण, 1पूर्ण,
			अणु0x06, 0x00, अणु0x00पूर्ण, 1पूर्ण,
			अणु0x07, 0x00, अणु0x00पूर्ण, 1पूर्ण,
			अणु0x08, 0x00, अणु0x00पूर्ण, 1पूर्ण,
			अणु0x09, 0x00, अणु0x00पूर्ण, 1पूर्ण,
			/* The following are used in the gain control
			 * which is BTW completely borked in the OEM driver
			 * The values क्रम each color go from 0 to 0x7ff
			 *अणु0x0a, 0x00, अणु0x01पूर्ण, 1पूर्ण,  green1 gain msb
			 *अणु0x0b, 0x00, अणु0x10पूर्ण, 1पूर्ण,  green1 gain lsb
			 *अणु0x0c, 0x00, अणु0x01पूर्ण, 1पूर्ण,  red gain msb
			 *अणु0x0d, 0x00, अणु0x10पूर्ण, 1पूर्ण,  red gain lsb
			 *अणु0x0e, 0x00, अणु0x01पूर्ण, 1पूर्ण,  blue gain msb
			 *अणु0x0f, 0x00, अणु0x10पूर्ण, 1पूर्ण,  blue gain lsb
			 *अणु0x10, 0x00, अणु0x01पूर्ण, 1पूर्ण, green2 gain msb
			 *अणु0x11, 0x00, अणु0x10पूर्ण, 1पूर्ण, green2 gain lsb
			 */
			अणु0x12, 0x00, अणु0x00पूर्ण, 1पूर्ण,
			अणु0x13, 0x00, अणु0x04पूर्ण, 1पूर्ण, /* weird effect on colors */
			अणु0x14, 0x00, अणु0x00पूर्ण, 1पूर्ण,
			अणु0x15, 0x00, अणु0x06पूर्ण, 1पूर्ण,
			अणु0x16, 0x00, अणु0x01पूर्ण, 1पूर्ण,
			अणु0x17, 0x00, अणु0xe2पूर्ण, 1पूर्ण, /* vertical alignment */
			अणु0x18, 0x00, अणु0x02पूर्ण, 1पूर्ण,
			अणु0x19, 0x00, अणु0x82पूर्ण, 1पूर्ण, /* करोn't mess with */
			अणु0x1a, 0x00, अणु0x00पूर्ण, 1पूर्ण,
			अणु0x1b, 0x00, अणु0x20पूर्ण, 1पूर्ण,
			/* अणु0x1c, 0x00, अणु0x17पूर्ण, 1पूर्ण, contrast control */
			अणु0x1d, 0x00, अणु0x80पूर्ण, 1पूर्ण, /* moving causes a mess */
			अणु0x1e, 0x00, अणु0x08पूर्ण, 1पूर्ण, /* moving jams the camera */
			अणु0x1f, 0x00, अणु0x0cपूर्ण, 1पूर्ण,
			अणु0x20, 0x00, अणु0x00पूर्ण, 1पूर्ण,
			अणु0, 0, अणु0पूर्ण, 0पूर्ण
		पूर्ण;
		err_code = sensor_ग_लिखो_regs(gspca_dev, vga_sensor2_init_data,
					 ARRAY_SIZE(vga_sensor2_init_data));
	पूर्ण
	वापस err_code;
पूर्ण

अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक err_code;

	sd->sof_पढ़ो = 0;

	/* Some of the VGA cameras require the memory poपूर्णांकer
	 * to be set to 0 again. We have been क्रमced to start the
	 * stream in sd_config() to detect the hardware, and बंदd it.
	 * Thus, we need here to करो a completely fresh and clean start. */
	err_code = zero_the_poपूर्णांकer(gspca_dev);
	अगर (err_code < 0)
		वापस err_code;

	err_code = stream_start(gspca_dev);
	अगर (err_code < 0)
		वापस err_code;

	अगर (sd->cam_type == CAM_TYPE_CIF) अणु
		err_code = start_cअगर_cam(gspca_dev);
	पूर्ण अन्यथा अणु
		err_code = start_vga_cam(gspca_dev);
	पूर्ण
	अगर (err_code < 0)
		वापस err_code;

	वापस isoc_enable(gspca_dev);
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	stream_stop(gspca_dev);
	/* Not all the cams need this, but even अगर not, probably a good idea */
	zero_the_poपूर्णांकer(gspca_dev);
	अगर (sd->करो_lcd_stop)
		lcd_stop(gspca_dev);
पूर्ण

अटल व्योम setbrightness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 sign_reg = 7;  /* This reg and the next one used on CIF cams. */
	u8 value_reg = 8; /* VGA cams seem to use regs 0x0b and 0x0c */
	अटल स्थिर u8 quick_clix_table[] =
	/*	  0  1  2   3  4  5  6  7  8  9  10  11  12  13  14  15 */
		अणु 0, 4, 8, 12, 1, 2, 3, 5, 6, 9,  7, 10, 13, 11, 14, 15पूर्ण;
	अगर (sd->cam_type == CAM_TYPE_VGA) अणु
		sign_reg += 4;
		value_reg += 4;
	पूर्ण

	/* Note रेजिस्टर 7 is also seen as 0x8x or 0xCx in some dumps */
	अगर (val > 0) अणु
		sensor_ग_लिखो1(gspca_dev, sign_reg, 0x00);
	पूर्ण अन्यथा अणु
		sensor_ग_लिखो1(gspca_dev, sign_reg, 0x01);
		val = 257 - val;
	पूर्ण
	/* Use lookup table क्रम funky Argus QuickClix brightness */
	अगर (sd->करो_lcd_stop)
		val = quick_clix_table[val];

	sensor_ग_लिखो1(gspca_dev, value_reg, val);
पूर्ण

अटल व्योम setexposure(काष्ठा gspca_dev *gspca_dev, s32 expo, s32 min_घड़ीभाग)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक exposure = MR97310A_EXPOSURE_DEFAULT;
	u8 buf[2];

	अगर (sd->cam_type == CAM_TYPE_CIF && sd->sensor_type == 1) अणु
		/* This cam करोes not like exposure settings < 300,
		   so scale 0 - 4095 to 300 - 4095 */
		exposure = (expo * 9267) / 10000 + 300;
		sensor_ग_लिखो1(gspca_dev, 3, exposure >> 4);
		sensor_ग_लिखो1(gspca_dev, 4, exposure & 0x0f);
	पूर्ण अन्यथा अगर (sd->sensor_type == 2) अणु
		exposure = expo;
		exposure >>= 3;
		sensor_ग_लिखो1(gspca_dev, 3, exposure >> 8);
		sensor_ग_लिखो1(gspca_dev, 4, exposure & 0xff);
	पूर्ण अन्यथा अणु
		/* We have both a घड़ी भागider and an exposure रेजिस्टर.
		   We first calculate the घड़ी भागider, as that determines
		   the maximum exposure and then we calculate the exposure
		   रेजिस्टर setting (which goes from 0 - 511).

		   Note our 0 - 4095 exposure is mapped to 0 - 511
		   milliseconds exposure समय */
		u8 घड़ीभाग = (60 * expo + 7999) / 8000;

		/* Limit framerate to not exceed usb bandwidth */
		अगर (घड़ीभाग < min_घड़ीभाग && gspca_dev->pixfmt.width >= 320)
			घड़ीभाग = min_घड़ीभाग;
		अन्यथा अगर (घड़ीभाग < 2)
			घड़ीभाग = 2;

		अगर (sd->cam_type == CAM_TYPE_VGA && घड़ीभाग < 4)
			घड़ीभाग = 4;

		/* Frame exposure समय in ms = 1000 * घड़ीभाग / 60 ->
		exposure = (sd->exposure / 8) * 511 / (1000 * घड़ीभाग / 60) */
		exposure = (60 * 511 * expo) / (8000 * घड़ीभाग);
		अगर (exposure > 511)
			exposure = 511;

		/* exposure रेजिस्टर value is reversed! */
		exposure = 511 - exposure;

		buf[0] = exposure & 0xff;
		buf[1] = exposure >> 8;
		sensor_ग_लिखो_reg(gspca_dev, 0x0e, 0, buf, 2);
		sensor_ग_लिखो1(gspca_dev, 0x02, घड़ीभाग);
	पूर्ण
पूर्ण

अटल व्योम setgain(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 gainreg;

	अगर (sd->cam_type == CAM_TYPE_CIF && sd->sensor_type == 1)
		sensor_ग_लिखो1(gspca_dev, 0x0e, val);
	अन्यथा अगर (sd->cam_type == CAM_TYPE_VGA && sd->sensor_type == 2)
		क्रम (gainreg = 0x0a; gainreg < 0x11; gainreg += 2) अणु
			sensor_ग_लिखो1(gspca_dev, gainreg, val >> 8);
			sensor_ग_लिखो1(gspca_dev, gainreg + 1, val & 0xff);
		पूर्ण
	अन्यथा
		sensor_ग_लिखो1(gspca_dev, 0x10, val);
पूर्ण

अटल व्योम setcontrast(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	sensor_ग_लिखो1(gspca_dev, 0x1c, val);
पूर्ण

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;

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
	हाल V4L2_CID_EXPOSURE:
		setexposure(gspca_dev, sd->exposure->val,
			    sd->min_घड़ीभाग ? sd->min_घड़ीभाग->val : 0);
		अवरोध;
	हाल V4L2_CID_GAIN:
		setgain(gspca_dev, ctrl->val);
		अवरोध;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.s_ctrl = sd_s_ctrl,
पूर्ण;

अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;
	अटल स्थिर काष्ठा v4l2_ctrl_config घड़ीभाग = अणु
		.ops = &sd_ctrl_ops,
		.id = MR97310A_CID_CLOCKDIV,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Minimum Clock Divider",
		.min = MR97310A_MIN_CLOCKDIV_MIN,
		.max = MR97310A_MIN_CLOCKDIV_MAX,
		.step = 1,
		.def = MR97310A_MIN_CLOCKDIV_DEFAULT,
	पूर्ण;
	bool has_brightness = false;
	bool has_argus_brightness = false;
	bool has_contrast = false;
	bool has_gain = false;
	bool has_cs_gain = false;
	bool has_exposure = false;
	bool has_घड़ीभाग = false;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 4);

	/* Setup controls depending on camera type */
	अगर (sd->cam_type == CAM_TYPE_CIF) अणु
		/* No brightness क्रम sensor_type 0 */
		अगर (sd->sensor_type == 0)
			has_exposure = has_gain = has_घड़ीभाग = true;
		अन्यथा
			has_exposure = has_gain = has_brightness = true;
	पूर्ण अन्यथा अणु
		/* All controls need to be disabled अगर VGA sensor_type is 0 */
		अगर (sd->sensor_type == 0)
			; /* no controls! */
		अन्यथा अगर (sd->sensor_type == 2)
			has_exposure = has_cs_gain = has_contrast = true;
		अन्यथा अगर (sd->करो_lcd_stop)
			has_exposure = has_gain = has_argus_brightness =
				has_घड़ीभाग = true;
		अन्यथा
			has_exposure = has_gain = has_brightness =
				has_घड़ीभाग = true;
	पूर्ण

	/* Separate brightness control description क्रम Argus QuickClix as it has
	 * dअगरferent limits from the other mr97310a cameras, and separate gain
	 * control क्रम Sakar CyberPix camera. */
	/*
	 * This control is disabled क्रम CIF type 1 and VGA type 0 cameras.
	 * It करोes not quite act linearly क्रम the Argus QuickClix camera,
	 * but it करोes control brightness. The values are 0 - 15 only, and
	 * the table above makes them act consecutively.
	 */
	अगर (has_brightness)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, -254, 255, 1,
			MR97310A_BRIGHTNESS_DEFAULT);
	अन्यथा अगर (has_argus_brightness)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 15, 1,
			MR97310A_BRIGHTNESS_DEFAULT);
	अगर (has_contrast)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_CONTRAST, MR97310A_CONTRAST_MIN,
			MR97310A_CONTRAST_MAX, 1, MR97310A_CONTRAST_DEFAULT);
	अगर (has_gain)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_GAIN, MR97310A_GAIN_MIN, MR97310A_GAIN_MAX,
			1, MR97310A_GAIN_DEFAULT);
	अन्यथा अगर (has_cs_gain)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops, V4L2_CID_GAIN,
			MR97310A_CS_GAIN_MIN, MR97310A_CS_GAIN_MAX,
			1, MR97310A_CS_GAIN_DEFAULT);
	अगर (has_exposure)
		sd->exposure = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_EXPOSURE, MR97310A_EXPOSURE_MIN,
			MR97310A_EXPOSURE_MAX, 1, MR97310A_EXPOSURE_DEFAULT);
	अगर (has_घड़ीभाग)
		sd->min_घड़ीभाग = v4l2_ctrl_new_custom(hdl, &घड़ीभाग, शून्य);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण
	अगर (has_exposure && has_घड़ीभाग)
		v4l2_ctrl_cluster(2, &sd->exposure);
	वापस 0;
पूर्ण

/* Include pac common sof detection functions */
#समावेश "pac_common.h"

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,		/* isoc packet */
			पूर्णांक len)		/* iso packet length */
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
		/* Start next frame. */
		gspca_frame_add(gspca_dev, FIRST_PACKET,
			pac_sof_marker, माप pac_sof_marker);
		len -= sof - data;
		data = sof;
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
	अणुUSB_DEVICE(0x08ca, 0x0110)पूर्ण,	/* Trust Spyc@m 100 */
	अणुUSB_DEVICE(0x08ca, 0x0111)पूर्ण,	/* Aiptek Pencam VGA+ */
	अणुUSB_DEVICE(0x093a, 0x010f)पूर्ण,	/* All other known MR97310A VGA cams */
	अणुUSB_DEVICE(0x093a, 0x010e)पूर्ण,	/* All known MR97310A CIF cams */
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
