<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * GSPCA sub driver क्रम W996[78]CF JPEG USB Dual Mode Camera Chip.
 *
 * Copyright (C) 2009 Hans de Goede <hdegoede@redhat.com>
 *
 * This module is adapted from the in kernel v4l1 w9968cf driver:
 *
 * Copyright (C) 2002-2004 by Luca Risolia <luca.risolia@studio.unibo.it>
 */

/* Note this is not a stand alone driver, it माला_लो included in ov519.c, this
   is a bit of a hack, but it needs the driver code क्रम a lot of dअगरferent
   ov sensors which is alपढ़ोy present in ov519.c (the old v4l1 driver used
   the ovchipcam framework). When we have the समय we really should move
   the sensor drivers to v4l2 sub drivers, and properly split of this
   driver from ov519.c */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा W9968CF_I2C_BUS_DELAY    4 /* delay in us क्रम I2C bit r/w operations */

#घोषणा Y_QUANTABLE (&sd->jpeg_hdr[JPEG_QT0_OFFSET])
#घोषणा UV_QUANTABLE (&sd->jpeg_hdr[JPEG_QT1_OFFSET])

अटल स्थिर काष्ठा v4l2_pix_क्रमmat w9968cf_vga_mode[] = अणु
	अणु160, 120, V4L2_PIX_FMT_UYVY, V4L2_FIELD_NONE,
		.bytesperline = 160 * 2,
		.sizeimage = 160 * 120 * 2,
		.colorspace = V4L2_COLORSPACE_JPEGपूर्ण,
	अणु176, 144, V4L2_PIX_FMT_UYVY, V4L2_FIELD_NONE,
		.bytesperline = 176 * 2,
		.sizeimage = 176 * 144 * 2,
		.colorspace = V4L2_COLORSPACE_JPEGपूर्ण,
	अणु320, 240, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320 * 2,
		.sizeimage = 320 * 240 * 2,
		.colorspace = V4L2_COLORSPACE_JPEGपूर्ण,
	अणु352, 288, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 352 * 2,
		.sizeimage = 352 * 288 * 2,
		.colorspace = V4L2_COLORSPACE_JPEGपूर्ण,
	अणु640, 480, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 640 * 2,
		.sizeimage = 640 * 480 * 2,
		.colorspace = V4L2_COLORSPACE_JPEGपूर्ण,
पूर्ण;

अटल व्योम reg_w(काष्ठा sd *sd, u16 index, u16 value);

/*--------------------------------------------------------------------------
  Write 64-bit data to the fast serial bus रेजिस्टरs.
  Return 0 on success, -1 otherwise.
  --------------------------------------------------------------------------*/
अटल व्योम w9968cf_ग_लिखो_fsb(काष्ठा sd *sd, u16* data)
अणु
	काष्ठा usb_device *udev = sd->gspca_dev.dev;
	u16 value;
	पूर्णांक ret;

	अगर (sd->gspca_dev.usb_err < 0)
		वापस;

	value = *data++;
	स_नकल(sd->gspca_dev.usb_buf, data, 6);

	/* Aव्योम things going to fast क्रम the bridge with a xhci host */
	udelay(150);
	ret = usb_control_msg(udev, usb_sndctrlpipe(udev, 0), 0,
			      USB_TYPE_VENDOR | USB_सूची_OUT | USB_RECIP_DEVICE,
			      value, 0x06, sd->gspca_dev.usb_buf, 6, 500);
	अगर (ret < 0) अणु
		pr_err("Write FSB registers failed (%d)\n", ret);
		sd->gspca_dev.usb_err = ret;
	पूर्ण
पूर्ण

/*--------------------------------------------------------------------------
  Write data to the serial bus control रेजिस्टर.
  Return 0 on success, a negative number otherwise.
  --------------------------------------------------------------------------*/
अटल व्योम w9968cf_ग_लिखो_sb(काष्ठा sd *sd, u16 value)
अणु
	पूर्णांक ret;

	अगर (sd->gspca_dev.usb_err < 0)
		वापस;

	/* Aव्योम things going to fast क्रम the bridge with a xhci host */
	udelay(150);

	/* We करोn't use reg_w here, as that would cause all ग_लिखोs when
	   bitbanging i2c to be logged, making the logs impossible to पढ़ो */
	ret = usb_control_msg(sd->gspca_dev.dev,
		usb_sndctrlpipe(sd->gspca_dev.dev, 0),
		0,
		USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		value, 0x01, शून्य, 0, 500);

	udelay(W9968CF_I2C_BUS_DELAY);

	अगर (ret < 0) अणु
		pr_err("Write SB reg [01] %04x failed\n", value);
		sd->gspca_dev.usb_err = ret;
	पूर्ण
पूर्ण

/*--------------------------------------------------------------------------
  Read data from the serial bus control रेजिस्टर.
  Return 0 on success, a negative number otherwise.
  --------------------------------------------------------------------------*/
अटल पूर्णांक w9968cf_पढ़ो_sb(काष्ठा sd *sd)
अणु
	पूर्णांक ret;

	अगर (sd->gspca_dev.usb_err < 0)
		वापस -1;

	/* Aव्योम things going to fast क्रम the bridge with a xhci host */
	udelay(150);

	/* We करोn't use reg_r here, as the w9968cf is special and has 16
	   bit रेजिस्टरs instead of 8 bit */
	ret = usb_control_msg(sd->gspca_dev.dev,
			usb_rcvctrlpipe(sd->gspca_dev.dev, 0),
			1,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, 0x01, sd->gspca_dev.usb_buf, 2, 500);
	अगर (ret >= 0) अणु
		ret = sd->gspca_dev.usb_buf[0] |
		      (sd->gspca_dev.usb_buf[1] << 8);
	पूर्ण अन्यथा अणु
		pr_err("Read SB reg [01] failed\n");
		sd->gspca_dev.usb_err = ret;
		/*
		 * Make sure the buffer is zeroed to aव्योम uninitialized
		 * values.
		 */
		स_रखो(sd->gspca_dev.usb_buf, 0, 2);
	पूर्ण

	udelay(W9968CF_I2C_BUS_DELAY);

	वापस ret;
पूर्ण

/*--------------------------------------------------------------------------
  Upload quantization tables क्रम the JPEG compression.
  This function is called by w9968cf_start_transfer().
  Return 0 on success, a negative number otherwise.
  --------------------------------------------------------------------------*/
अटल व्योम w9968cf_upload_quantizationtables(काष्ठा sd *sd)
अणु
	u16 a, b;
	पूर्णांक i, j;

	reg_w(sd, 0x39, 0x0010); /* JPEG घड़ी enable */

	क्रम (i = 0, j = 0; i < 32; i++, j += 2) अणु
		a = Y_QUANTABLE[j] | ((अचिन्हित)(Y_QUANTABLE[j + 1]) << 8);
		b = UV_QUANTABLE[j] | ((अचिन्हित)(UV_QUANTABLE[j + 1]) << 8);
		reg_w(sd, 0x40 + i, a);
		reg_w(sd, 0x60 + i, b);
	पूर्ण
	reg_w(sd, 0x39, 0x0012); /* JPEG encoder enable */
पूर्ण

/****************************************************************************
 * Low-level I2C I/O functions.                                             *
 * The adapter supports the following I2C transfer functions:               *
 * i2c_adap_fastग_लिखो_byte_data() (at 400 kHz bit frequency only)           *
 * i2c_adap_पढ़ो_byte_data()                                                *
 * i2c_adap_पढ़ो_byte()                                                     *
 ****************************************************************************/

अटल व्योम w9968cf_smbus_start(काष्ठा sd *sd)
अणु
	w9968cf_ग_लिखो_sb(sd, 0x0011); /* SDE=1, SDA=0, SCL=1 */
	w9968cf_ग_लिखो_sb(sd, 0x0010); /* SDE=1, SDA=0, SCL=0 */
पूर्ण

अटल व्योम w9968cf_smbus_stop(काष्ठा sd *sd)
अणु
	w9968cf_ग_लिखो_sb(sd, 0x0010); /* SDE=1, SDA=0, SCL=0 */
	w9968cf_ग_लिखो_sb(sd, 0x0011); /* SDE=1, SDA=0, SCL=1 */
	w9968cf_ग_लिखो_sb(sd, 0x0013); /* SDE=1, SDA=1, SCL=1 */
पूर्ण

अटल व्योम w9968cf_smbus_ग_लिखो_byte(काष्ठा sd *sd, u8 v)
अणु
	u8 bit;
	पूर्णांक sda;

	क्रम (bit = 0 ; bit < 8 ; bit++) अणु
		sda = (v & 0x80) ? 2 : 0;
		v <<= 1;
		/* SDE=1, SDA=sda, SCL=0 */
		w9968cf_ग_लिखो_sb(sd, 0x10 | sda);
		/* SDE=1, SDA=sda, SCL=1 */
		w9968cf_ग_लिखो_sb(sd, 0x11 | sda);
		/* SDE=1, SDA=sda, SCL=0 */
		w9968cf_ग_लिखो_sb(sd, 0x10 | sda);
	पूर्ण
पूर्ण

अटल व्योम w9968cf_smbus_पढ़ो_byte(काष्ठा sd *sd, u8 *v)
अणु
	u8 bit;

	/* No need to ensure SDA is high as we are always called after
	   पढ़ो_ack which ends with SDA high */
	*v = 0;
	क्रम (bit = 0 ; bit < 8 ; bit++) अणु
		*v <<= 1;
		/* SDE=1, SDA=1, SCL=1 */
		w9968cf_ग_लिखो_sb(sd, 0x0013);
		*v |= (w9968cf_पढ़ो_sb(sd) & 0x0008) ? 1 : 0;
		/* SDE=1, SDA=1, SCL=0 */
		w9968cf_ग_लिखो_sb(sd, 0x0012);
	पूर्ण
पूर्ण

अटल व्योम w9968cf_smbus_ग_लिखो_nack(काष्ठा sd *sd)
अणु
	/* No need to ensure SDA is high as we are always called after
	   पढ़ो_byte which ends with SDA high */
	w9968cf_ग_लिखो_sb(sd, 0x0013); /* SDE=1, SDA=1, SCL=1 */
	w9968cf_ग_लिखो_sb(sd, 0x0012); /* SDE=1, SDA=1, SCL=0 */
पूर्ण

अटल व्योम w9968cf_smbus_पढ़ो_ack(काष्ठा sd *sd)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक sda;

	/* Ensure SDA is high beक्रमe raising घड़ी to aव्योम a spurious stop */
	w9968cf_ग_लिखो_sb(sd, 0x0012); /* SDE=1, SDA=1, SCL=0 */
	w9968cf_ग_लिखो_sb(sd, 0x0013); /* SDE=1, SDA=1, SCL=1 */
	sda = w9968cf_पढ़ो_sb(sd);
	w9968cf_ग_लिखो_sb(sd, 0x0012); /* SDE=1, SDA=1, SCL=0 */
	अगर (sda >= 0 && (sda & 0x08)) अणु
		gspca_dbg(gspca_dev, D_USBI, "Did not receive i2c ACK\n");
		sd->gspca_dev.usb_err = -EIO;
	पूर्ण
पूर्ण

/* SMBus protocol: S Addr Wr [A] Subaddr [A] Value [A] P */
अटल व्योम w9968cf_i2c_w(काष्ठा sd *sd, u8 reg, u8 value)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	u16* data = (u16 *)sd->gspca_dev.usb_buf;

	data[0] = 0x082f | ((sd->sensor_addr & 0x80) ? 0x1500 : 0x0);
	data[0] |= (sd->sensor_addr & 0x40) ? 0x4000 : 0x0;
	data[1] = 0x2082 | ((sd->sensor_addr & 0x40) ? 0x0005 : 0x0);
	data[1] |= (sd->sensor_addr & 0x20) ? 0x0150 : 0x0;
	data[1] |= (sd->sensor_addr & 0x10) ? 0x5400 : 0x0;
	data[2] = 0x8208 | ((sd->sensor_addr & 0x08) ? 0x0015 : 0x0);
	data[2] |= (sd->sensor_addr & 0x04) ? 0x0540 : 0x0;
	data[2] |= (sd->sensor_addr & 0x02) ? 0x5000 : 0x0;
	data[3] = 0x1d20 | ((sd->sensor_addr & 0x02) ? 0x0001 : 0x0);
	data[3] |= (sd->sensor_addr & 0x01) ? 0x0054 : 0x0;

	w9968cf_ग_लिखो_fsb(sd, data);

	data[0] = 0x8208 | ((reg & 0x80) ? 0x0015 : 0x0);
	data[0] |= (reg & 0x40) ? 0x0540 : 0x0;
	data[0] |= (reg & 0x20) ? 0x5000 : 0x0;
	data[1] = 0x0820 | ((reg & 0x20) ? 0x0001 : 0x0);
	data[1] |= (reg & 0x10) ? 0x0054 : 0x0;
	data[1] |= (reg & 0x08) ? 0x1500 : 0x0;
	data[1] |= (reg & 0x04) ? 0x4000 : 0x0;
	data[2] = 0x2082 | ((reg & 0x04) ? 0x0005 : 0x0);
	data[2] |= (reg & 0x02) ? 0x0150 : 0x0;
	data[2] |= (reg & 0x01) ? 0x5400 : 0x0;
	data[3] = 0x001d;

	w9968cf_ग_लिखो_fsb(sd, data);

	data[0] = 0x8208 | ((value & 0x80) ? 0x0015 : 0x0);
	data[0] |= (value & 0x40) ? 0x0540 : 0x0;
	data[0] |= (value & 0x20) ? 0x5000 : 0x0;
	data[1] = 0x0820 | ((value & 0x20) ? 0x0001 : 0x0);
	data[1] |= (value & 0x10) ? 0x0054 : 0x0;
	data[1] |= (value & 0x08) ? 0x1500 : 0x0;
	data[1] |= (value & 0x04) ? 0x4000 : 0x0;
	data[2] = 0x2082 | ((value & 0x04) ? 0x0005 : 0x0);
	data[2] |= (value & 0x02) ? 0x0150 : 0x0;
	data[2] |= (value & 0x01) ? 0x5400 : 0x0;
	data[3] = 0xfe1d;

	w9968cf_ग_लिखो_fsb(sd, data);

	gspca_dbg(gspca_dev, D_USBO, "i2c 0x%02x -> [0x%02x]\n", value, reg);
पूर्ण

/* SMBus protocol: S Addr Wr [A] Subaddr [A] P S Addr+1 Rd [A] [Value] NA P */
अटल पूर्णांक w9968cf_i2c_r(काष्ठा sd *sd, u8 reg)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक ret = 0;
	u8 value;

	/* Fast serial bus data control disable */
	w9968cf_ग_लिखो_sb(sd, 0x0013); /* करोn't change ! */

	w9968cf_smbus_start(sd);
	w9968cf_smbus_ग_लिखो_byte(sd, sd->sensor_addr);
	w9968cf_smbus_पढ़ो_ack(sd);
	w9968cf_smbus_ग_लिखो_byte(sd, reg);
	w9968cf_smbus_पढ़ो_ack(sd);
	w9968cf_smbus_stop(sd);
	w9968cf_smbus_start(sd);
	w9968cf_smbus_ग_लिखो_byte(sd, sd->sensor_addr + 1);
	w9968cf_smbus_पढ़ो_ack(sd);
	w9968cf_smbus_पढ़ो_byte(sd, &value);
	/* संकेत we करोn't want to पढ़ो anymore, the v4l1 driver used to
	   send an ack here which is very wrong! (and then fixed
	   the issues this gave by retrying पढ़ोs) */
	w9968cf_smbus_ग_लिखो_nack(sd);
	w9968cf_smbus_stop(sd);

	/* Fast serial bus data control re-enable */
	w9968cf_ग_लिखो_sb(sd, 0x0030);

	अगर (sd->gspca_dev.usb_err >= 0) अणु
		ret = value;
		gspca_dbg(gspca_dev, D_USBI, "i2c [0x%02X] -> 0x%02X\n",
			  reg, value);
	पूर्ण अन्यथा
		gspca_err(gspca_dev, "i2c read [0x%02x] failed\n", reg);

	वापस ret;
पूर्ण

/*--------------------------------------------------------------------------
  Turn on the LED on some webcams. A beep should be heard too.
  Return 0 on success, a negative number otherwise.
  --------------------------------------------------------------------------*/
अटल व्योम w9968cf_configure(काष्ठा sd *sd)
अणु
	reg_w(sd, 0x00, 0xff00); /* घातer-करोwn */
	reg_w(sd, 0x00, 0xbf17); /* reset everything */
	reg_w(sd, 0x00, 0xbf10); /* normal operation */
	reg_w(sd, 0x01, 0x0010); /* serial bus, SDS high */
	reg_w(sd, 0x01, 0x0000); /* serial bus, SDS low */
	reg_w(sd, 0x01, 0x0010); /* ..high 'beep-beep' */
	reg_w(sd, 0x01, 0x0030); /* Set sda scl to FSB mode */

	sd->stopped = 1;
पूर्ण

अटल व्योम w9968cf_init(काष्ठा sd *sd)
अणु
	अचिन्हित दीर्घ hw_bufsize = sd->sअगर ? (352 * 288 * 2) : (640 * 480 * 2),
		      y0 = 0x0000,
		      u0 = y0 + hw_bufsize / 2,
		      v0 = u0 + hw_bufsize / 4,
		      y1 = v0 + hw_bufsize / 4,
		      u1 = y1 + hw_bufsize / 2,
		      v1 = u1 + hw_bufsize / 4;

	reg_w(sd, 0x00, 0xff00); /* घातer off */
	reg_w(sd, 0x00, 0xbf10); /* घातer on */

	reg_w(sd, 0x03, 0x405d); /* DRAM timings */
	reg_w(sd, 0x04, 0x0030); /* SDRAM timings */

	reg_w(sd, 0x20, y0 & 0xffff); /* Y buf.0, low */
	reg_w(sd, 0x21, y0 >> 16);    /* Y buf.0, high */
	reg_w(sd, 0x24, u0 & 0xffff); /* U buf.0, low */
	reg_w(sd, 0x25, u0 >> 16);    /* U buf.0, high */
	reg_w(sd, 0x28, v0 & 0xffff); /* V buf.0, low */
	reg_w(sd, 0x29, v0 >> 16);    /* V buf.0, high */

	reg_w(sd, 0x22, y1 & 0xffff); /* Y buf.1, low */
	reg_w(sd, 0x23, y1 >> 16);    /* Y buf.1, high */
	reg_w(sd, 0x26, u1 & 0xffff); /* U buf.1, low */
	reg_w(sd, 0x27, u1 >> 16);    /* U buf.1, high */
	reg_w(sd, 0x2a, v1 & 0xffff); /* V buf.1, low */
	reg_w(sd, 0x2b, v1 >> 16);    /* V buf.1, high */

	reg_w(sd, 0x32, y1 & 0xffff); /* JPEG buf 0 low */
	reg_w(sd, 0x33, y1 >> 16);    /* JPEG buf 0 high */

	reg_w(sd, 0x34, y1 & 0xffff); /* JPEG buf 1 low */
	reg_w(sd, 0x35, y1 >> 16);    /* JPEG bug 1 high */

	reg_w(sd, 0x36, 0x0000);/* JPEG restart पूर्णांकerval */
	reg_w(sd, 0x37, 0x0804);/*JPEG VLE FIFO threshold*/
	reg_w(sd, 0x38, 0x0000);/* disable hw up-scaling */
	reg_w(sd, 0x3f, 0x0000); /* JPEG/MCTL test data */
पूर्ण

अटल व्योम w9968cf_set_crop_winकरोw(काष्ठा sd *sd)
अणु
	पूर्णांक start_cropx, start_cropy,  x, y, fw, fh, cw, ch,
	    max_width, max_height;

	अगर (sd->sअगर) अणु
		max_width  = 352;
		max_height = 288;
	पूर्ण अन्यथा अणु
		max_width  = 640;
		max_height = 480;
	पूर्ण

	अगर (sd->sensor == SEN_OV7620) अणु
		/*
		 * Sigh, this is dependend on the घड़ी / framerate changes
		 * made by the frequency control, sick.
		 *
		 * Note we cannot use v4l2_ctrl_g_ctrl here, as we get called
		 * from ov519.c:setfreq() with the ctrl lock held!
		 */
		अगर (sd->freq->val == 1) अणु
			start_cropx = 277;
			start_cropy = 37;
		पूर्ण अन्यथा अणु
			start_cropx = 105;
			start_cropy = 37;
		पूर्ण
	पूर्ण अन्यथा अणु
		start_cropx = 320;
		start_cropy = 35;
	पूर्ण

	/* Work around to aव्योम FP arithmetic */
	#घोषणा SC(x) ((x) << 10)

	/* Scaling factors */
	fw = SC(sd->gspca_dev.pixfmt.width) / max_width;
	fh = SC(sd->gspca_dev.pixfmt.height) / max_height;

	cw = (fw >= fh) ? max_width : SC(sd->gspca_dev.pixfmt.width) / fh;
	ch = (fw >= fh) ? SC(sd->gspca_dev.pixfmt.height) / fw : max_height;

	sd->sensor_width = max_width;
	sd->sensor_height = max_height;

	x = (max_width - cw) / 2;
	y = (max_height - ch) / 2;

	reg_w(sd, 0x10, start_cropx + x);
	reg_w(sd, 0x11, start_cropy + y);
	reg_w(sd, 0x12, start_cropx + x + cw);
	reg_w(sd, 0x13, start_cropy + y + ch);
पूर्ण

अटल व्योम w9968cf_mode_init_regs(काष्ठा sd *sd)
अणु
	पूर्णांक val, vs_polarity, hs_polarity;

	w9968cf_set_crop_winकरोw(sd);

	reg_w(sd, 0x14, sd->gspca_dev.pixfmt.width);
	reg_w(sd, 0x15, sd->gspca_dev.pixfmt.height);

	/* JPEG width & height */
	reg_w(sd, 0x30, sd->gspca_dev.pixfmt.width);
	reg_w(sd, 0x31, sd->gspca_dev.pixfmt.height);

	/* Y & UV frame buffer strides (in WORD) */
	अगर (w9968cf_vga_mode[sd->gspca_dev.curr_mode].pixelक्रमmat ==
	    V4L2_PIX_FMT_JPEG) अणु
		reg_w(sd, 0x2c, sd->gspca_dev.pixfmt.width / 2);
		reg_w(sd, 0x2d, sd->gspca_dev.pixfmt.width / 4);
	पूर्ण अन्यथा
		reg_w(sd, 0x2c, sd->gspca_dev.pixfmt.width);

	reg_w(sd, 0x00, 0xbf17); /* reset everything */
	reg_w(sd, 0x00, 0xbf10); /* normal operation */

	/* Transfer size in WORDS (क्रम UYVY क्रमmat only) */
	val = sd->gspca_dev.pixfmt.width * sd->gspca_dev.pixfmt.height;
	reg_w(sd, 0x3d, val & 0xffff); /* low bits */
	reg_w(sd, 0x3e, val >> 16);    /* high bits */

	अगर (w9968cf_vga_mode[sd->gspca_dev.curr_mode].pixelक्रमmat ==
	    V4L2_PIX_FMT_JPEG) अणु
		/* We may get called multiple बार (usb isoc bw negotiat.) */
		jpeg_define(sd->jpeg_hdr, sd->gspca_dev.pixfmt.height,
			    sd->gspca_dev.pixfmt.width, 0x22); /* JPEG 420 */
		jpeg_set_qual(sd->jpeg_hdr, v4l2_ctrl_g_ctrl(sd->jpegqual));
		w9968cf_upload_quantizationtables(sd);
		v4l2_ctrl_grab(sd->jpegqual, true);
	पूर्ण

	/* Video Capture Control Register */
	अगर (sd->sensor == SEN_OV7620) अणु
		/* Seems to work around a bug in the image sensor */
		vs_polarity = 1;
		hs_polarity = 1;
	पूर्ण अन्यथा अणु
		vs_polarity = 1;
		hs_polarity = 0;
	पूर्ण

	val = (vs_polarity << 12) | (hs_polarity << 11);

	/* NOTE: We may not have enough memory to करो द्विगुन buffering जबतक
	   करोing compression (amount of memory dअगरfers per model cam).
	   So we use the second image buffer also as jpeg stream buffer
	   (see w9968cf_init), and disable द्विगुन buffering. */
	अगर (w9968cf_vga_mode[sd->gspca_dev.curr_mode].pixelक्रमmat ==
	    V4L2_PIX_FMT_JPEG) अणु
		/* val |= 0x0002; YUV422P */
		val |= 0x0003; /* YUV420P */
	पूर्ण अन्यथा
		val |= 0x0080; /* Enable HW द्विगुन buffering */

	/* val |= 0x0020; enable clamping */
	/* val |= 0x0008; enable (1-2-1) filter */
	/* val |= 0x000c; enable (2-3-6-3-2) filter */

	val |= 0x8000; /* capt. enable */

	reg_w(sd, 0x16, val);

	sd->gspca_dev.empty_packet = 0;
पूर्ण

अटल व्योम w9968cf_stop0(काष्ठा sd *sd)
अणु
	v4l2_ctrl_grab(sd->jpegqual, false);
	reg_w(sd, 0x39, 0x0000); /* disable JPEG encoder */
	reg_w(sd, 0x16, 0x0000); /* stop video capture */
पूर्ण

/* The w9968cf करोcs say that a 0 sized packet means खातापूर्ण (and also SOF
   क्रम the next frame). This seems to simply not be true when operating
   in JPEG mode, in this हाल there may be empty packets within the
   frame. So in JPEG mode use the JPEG SOI marker to detect SOF.

   Note to make things even more पूर्णांकeresting the w9968cf sends *PLANAR* jpeg,
   to be precise it sends: SOI, SOF, DRI, SOS, Y-data, SOS, U-data, SOS,
   V-data, EOI. */
अटल व्योम w9968cf_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (w9968cf_vga_mode[gspca_dev->curr_mode].pixelक्रमmat ==
	    V4L2_PIX_FMT_JPEG) अणु
		अगर (len >= 2 &&
		    data[0] == 0xff &&
		    data[1] == 0xd8) अणु
			gspca_frame_add(gspca_dev, LAST_PACKET,
					शून्य, 0);
			gspca_frame_add(gspca_dev, FIRST_PACKET,
					sd->jpeg_hdr, JPEG_HDR_SZ);
			/* Strip the ff d8, our own header (which adds
			   huffman and quantization tables) alपढ़ोy has this */
			len -= 2;
			data += 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* In UYVY mode an empty packet संकेतs खातापूर्ण */
		अगर (gspca_dev->empty_packet) अणु
			gspca_frame_add(gspca_dev, LAST_PACKET,
						शून्य, 0);
			gspca_frame_add(gspca_dev, FIRST_PACKET,
					शून्य, 0);
			gspca_dev->empty_packet = 0;
		पूर्ण
	पूर्ण
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
पूर्ण
