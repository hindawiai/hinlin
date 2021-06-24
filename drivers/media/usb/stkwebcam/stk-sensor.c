<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* stk-sensor.c: Driver क्रम ov96xx sensor (used in some Syntek webcams)
 *
 * Copyright 2007-2008 Jaime Velasco Juan <jsagarribay@gmail.com>
 *
 * Some parts derived from ov7670.c:
 * Copyright 2006 One Laptop Per Child Association, Inc.  Written
 * by Jonathan Corbet with substantial inspiration from Mark
 * McClelland's ovcamchip code.
 *
 * Copyright 2006-7 Jonathan Corbet <corbet@lwn.net>
 *
 * This file may be distributed under the terms of the GNU General
 */

/* Controlling the sensor via the STK1125 venकरोr specअगरic control पूर्णांकerface:
 * The camera uses an OmniVision sensor and the stk1125 provides an
 * SCCB(i2c)-USB bridge which let us program the sensor.
 * In my हाल the sensor id is 0x9652, it can be पढ़ो from sensor's रेजिस्टर
 * 0x0A and 0x0B as follows:
 * - पढ़ो रेजिस्टर #R:
 *   output #R to index 0x0208
 *   output 0x0070 to index 0x0200
 *   input 1 byte from index 0x0201 (some kind of status रेजिस्टर)
 *     until its value is 0x01
 *   input 1 byte from index 0x0209. This is the value of #R
 * - ग_लिखो value V to रेजिस्टर #R
 *   output #R to index 0x0204
 *   output V to index 0x0205
 *   output 0x0005 to index 0x0200
 *   input 1 byte from index 0x0201 until its value becomes 0x04
 */

/* It seems the i2c bus is controlled with these रेजिस्टरs */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "stk-webcam.h"

#घोषणा STK_IIC_BASE		(0x0200)
#  define STK_IIC_OP		(STK_IIC_BASE)
#    define STK_IIC_OP_TX	(0x05)
#    define STK_IIC_OP_RX	(0x70)
#  define STK_IIC_STAT		(STK_IIC_BASE+1)
#    define STK_IIC_STAT_TX_OK	(0x04)
#    define STK_IIC_STAT_RX_OK	(0x01)
/* I करोn't know what करोes this रेजिस्टर.
 * when it is 0x00 or 0x01, we cannot talk to the sensor,
 * other values work */
#  define STK_IIC_ENABLE	(STK_IIC_BASE+2)
#    define STK_IIC_ENABLE_NO	(0x00)
/* This is what the driver ग_लिखोs in winकरोws */
#    define STK_IIC_ENABLE_YES	(0x1e)
/*
 * Address of the slave. Seems like the binary driver look क्रम the
 * sensor in multiple places, attempting a reset sequence.
 * We only know about the ov9650
 */
#  define STK_IIC_ADDR		(STK_IIC_BASE+3)
#  define STK_IIC_TX_INDEX	(STK_IIC_BASE+4)
#  define STK_IIC_TX_VALUE	(STK_IIC_BASE+5)
#  define STK_IIC_RX_INDEX	(STK_IIC_BASE+8)
#  define STK_IIC_RX_VALUE	(STK_IIC_BASE+9)

#घोषणा MAX_RETRIES		(50)

#घोषणा SENSOR_ADDRESS		(0x60)

/* From ov7670.c (These रेजिस्टरs aren't fully accurate) */

/* Registers */
#घोषणा REG_GAIN	0x00	/* Gain lower 8 bits (rest in vref) */
#घोषणा REG_BLUE	0x01	/* blue gain */
#घोषणा REG_RED		0x02	/* red gain */
#घोषणा REG_VREF	0x03	/* Pieces of GAIN, VSTART, VSTOP */
#घोषणा REG_COM1	0x04	/* Control 1 */
#घोषणा  COM1_CCIR656	  0x40  /* CCIR656 enable */
#घोषणा  COM1_QFMT	  0x20  /* QVGA/QCIF क्रमmat */
#घोषणा  COM1_SKIP_0	  0x00  /* Do not skip any row */
#घोषणा  COM1_SKIP_2	  0x04  /* Skip 2 rows of 4 */
#घोषणा  COM1_SKIP_3	  0x08  /* Skip 3 rows of 4 */
#घोषणा REG_BAVE	0x05	/* U/B Average level */
#घोषणा REG_GbAVE	0x06	/* Y/Gb Average level */
#घोषणा REG_AECHH	0x07	/* AEC MS 5 bits */
#घोषणा REG_RAVE	0x08	/* V/R Average level */
#घोषणा REG_COM2	0x09	/* Control 2 */
#घोषणा  COM2_SSLEEP	  0x10	/* Soft sleep mode */
#घोषणा REG_PID		0x0a	/* Product ID MSB */
#घोषणा REG_VER		0x0b	/* Product ID LSB */
#घोषणा REG_COM3	0x0c	/* Control 3 */
#घोषणा  COM3_SWAP	  0x40	  /* Byte swap */
#घोषणा  COM3_SCALEEN	  0x08	  /* Enable scaling */
#घोषणा  COM3_DCWEN	  0x04	  /* Enable करोwnsamp/crop/winकरोw */
#घोषणा REG_COM4	0x0d	/* Control 4 */
#घोषणा REG_COM5	0x0e	/* All "reserved" */
#घोषणा REG_COM6	0x0f	/* Control 6 */
#घोषणा REG_AECH	0x10	/* More bits of AEC value */
#घोषणा REG_CLKRC	0x11	/* Clock control */
#घोषणा   CLK_PLL	  0x80	  /* Enable पूर्णांकernal PLL */
#घोषणा   CLK_EXT	  0x40	  /* Use बाह्यal घड़ी directly */
#घोषणा   CLK_SCALE	  0x3f	  /* Mask क्रम पूर्णांकernal घड़ी scale */
#घोषणा REG_COM7	0x12	/* Control 7 */
#घोषणा   COM7_RESET	  0x80	  /* Register reset */
#घोषणा   COM7_FMT_MASK	  0x38
#घोषणा   COM7_FMT_SXGA	  0x00
#घोषणा   COM7_FMT_VGA	  0x40
#घोषणा	  COM7_FMT_CIF	  0x20	  /* CIF क्रमmat */
#घोषणा   COM7_FMT_QVGA	  0x10	  /* QVGA क्रमmat */
#घोषणा   COM7_FMT_QCIF	  0x08	  /* QCIF क्रमmat */
#घोषणा	  COM7_RGB	  0x04	  /* bits 0 and 2 - RGB क्रमmat */
#घोषणा	  COM7_YUV	  0x00	  /* YUV */
#घोषणा	  COM7_BAYER	  0x01	  /* Bayer क्रमmat */
#घोषणा	  COM7_PBAYER	  0x05	  /* "Processed bayer" */
#घोषणा REG_COM8	0x13	/* Control 8 */
#घोषणा   COM8_FASTAEC	  0x80	  /* Enable fast AGC/AEC */
#घोषणा   COM8_AECSTEP	  0x40	  /* Unlimited AEC step size */
#घोषणा   COM8_BFILT	  0x20	  /* Band filter enable */
#घोषणा   COM8_AGC	  0x04	  /* Auto gain enable */
#घोषणा   COM8_AWB	  0x02	  /* White balance enable */
#घोषणा   COM8_AEC	  0x01	  /* Auto exposure enable */
#घोषणा REG_COM9	0x14	/* Control 9  - gain उच्चमानing */
#घोषणा REG_COM10	0x15	/* Control 10 */
#घोषणा   COM10_HSYNC	  0x40	  /* HSYNC instead of HREF */
#घोषणा   COM10_PCLK_HB	  0x20	  /* Suppress PCLK on horiz blank */
#घोषणा   COM10_HREF_REV  0x08	  /* Reverse HREF */
#घोषणा   COM10_VS_LEAD	  0x04	  /* VSYNC on घड़ी leading edge */
#घोषणा   COM10_VS_NEG	  0x02	  /* VSYNC negative */
#घोषणा   COM10_HS_NEG	  0x01	  /* HSYNC negative */
#घोषणा REG_HSTART	0x17	/* Horiz start high bits */
#घोषणा REG_HSTOP	0x18	/* Horiz stop high bits */
#घोषणा REG_VSTART	0x19	/* Vert start high bits */
#घोषणा REG_VSTOP	0x1a	/* Vert stop high bits */
#घोषणा REG_PSHFT	0x1b	/* Pixel delay after HREF */
#घोषणा REG_MIDH	0x1c	/* Manuf. ID high */
#घोषणा REG_MIDL	0x1d	/* Manuf. ID low */
#घोषणा REG_MVFP	0x1e	/* Mirror / vflip */
#घोषणा   MVFP_MIRROR	  0x20	  /* Mirror image */
#घोषणा   MVFP_FLIP	  0x10	  /* Vertical flip */

#घोषणा REG_AEW		0x24	/* AGC upper limit */
#घोषणा REG_AEB		0x25	/* AGC lower limit */
#घोषणा REG_VPT		0x26	/* AGC/AEC fast mode op region */
#घोषणा REG_ADVFL	0x2d	/* Insert dummy lines (LSB) */
#घोषणा REG_ADVFH	0x2e	/* Insert dummy lines (MSB) */
#घोषणा REG_HSYST	0x30	/* HSYNC rising edge delay */
#घोषणा REG_HSYEN	0x31	/* HSYNC falling edge delay */
#घोषणा REG_HREF	0x32	/* HREF pieces */
#घोषणा REG_TSLB	0x3a	/* lots of stuff */
#घोषणा   TSLB_YLAST	  0x04	  /* UYVY or VYUY - see com13 */
#घोषणा   TSLB_BYTEORD	  0x08	  /* swap bytes in 16bit mode? */
#घोषणा REG_COM11	0x3b	/* Control 11 */
#घोषणा   COM11_NIGHT	  0x80	  /* NIght mode enable */
#घोषणा   COM11_NMFR	  0x60	  /* Two bit NM frame rate */
#घोषणा   COM11_HZAUTO	  0x10	  /* Auto detect 50/60 Hz */
#घोषणा	  COM11_50HZ	  0x08	  /* Manual 50Hz select */
#घोषणा   COM11_EXP	  0x02
#घोषणा REG_COM12	0x3c	/* Control 12 */
#घोषणा   COM12_HREF	  0x80	  /* HREF always */
#घोषणा REG_COM13	0x3d	/* Control 13 */
#घोषणा   COM13_GAMMA	  0x80	  /* Gamma enable */
#घोषणा	  COM13_UVSAT	  0x40	  /* UV saturation स्वतः adjusपंचांगent */
#घोषणा	  COM13_CMATRIX	  0x10	  /* Enable color matrix क्रम RGB or YUV */
#घोषणा   COM13_UVSWAP	  0x01	  /* V beक्रमe U - w/TSLB */
#घोषणा REG_COM14	0x3e	/* Control 14 */
#घोषणा   COM14_DCWEN	  0x10	  /* DCW/PCLK-scale enable */
#घोषणा REG_EDGE	0x3f	/* Edge enhancement factor */
#घोषणा REG_COM15	0x40	/* Control 15 */
#घोषणा   COM15_R10F0	  0x00	  /* Data range 10 to F0 */
#घोषणा	  COM15_R01FE	  0x80	  /*            01 to FE */
#घोषणा   COM15_R00FF	  0xc0	  /*            00 to FF */
#घोषणा   COM15_RGB565	  0x10	  /* RGB565 output */
#घोषणा   COM15_RGBFIXME	  0x20	  /* FIXME  */
#घोषणा   COM15_RGB555	  0x30	  /* RGB555 output */
#घोषणा REG_COM16	0x41	/* Control 16 */
#घोषणा   COM16_AWBGAIN   0x08	  /* AWB gain enable */
#घोषणा REG_COM17	0x42	/* Control 17 */
#घोषणा   COM17_AECWIN	  0xc0	  /* AEC winकरोw - must match COM4 */
#घोषणा   COM17_CBAR	  0x08	  /* DSP Color bar */

/*
 * This matrix defines how the colors are generated, must be
 * tweaked to adjust hue and saturation.
 *
 * Order: v-red, v-green, v-blue, u-red, u-green, u-blue
 *
 * They are nine-bit चिन्हित quantities, with the sign bit
 * stored in 0x58.  Sign क्रम v-red is bit 0, and up from there.
 */
#घोषणा	REG_CMATRIX_BASE 0x4f
#घोषणा   CMATRIX_LEN 6
#घोषणा REG_CMATRIX_SIGN 0x58


#घोषणा REG_BRIGHT	0x55	/* Brightness */
#घोषणा REG_CONTRAS	0x56	/* Contrast control */

#घोषणा REG_GFIX	0x69	/* Fix gain control */

#घोषणा REG_RGB444	0x8c	/* RGB 444 control */
#घोषणा   R444_ENABLE	  0x02	  /* Turn on RGB444, overrides 5x5 */
#घोषणा   R444_RGBX	  0x01	  /* Empty nibble at end */

#घोषणा REG_HAECC1	0x9f	/* Hist AEC/AGC control 1 */
#घोषणा REG_HAECC2	0xa0	/* Hist AEC/AGC control 2 */

#घोषणा REG_BD50MAX	0xa5	/* 50hz banding step limit */
#घोषणा REG_HAECC3	0xa6	/* Hist AEC/AGC control 3 */
#घोषणा REG_HAECC4	0xa7	/* Hist AEC/AGC control 4 */
#घोषणा REG_HAECC5	0xa8	/* Hist AEC/AGC control 5 */
#घोषणा REG_HAECC6	0xa9	/* Hist AEC/AGC control 6 */
#घोषणा REG_HAECC7	0xaa	/* Hist AEC/AGC control 7 */
#घोषणा REG_BD60MAX	0xab	/* 60hz banding step limit */




/* Returns 0 अगर OK */
अटल पूर्णांक stk_sensor_outb(काष्ठा stk_camera *dev, u8 reg, u8 val)
अणु
	पूर्णांक i = 0;
	u8 पंचांगpval = 0;

	अगर (stk_camera_ग_लिखो_reg(dev, STK_IIC_TX_INDEX, reg))
		वापस 1;
	अगर (stk_camera_ग_लिखो_reg(dev, STK_IIC_TX_VALUE, val))
		वापस 1;
	अगर (stk_camera_ग_लिखो_reg(dev, STK_IIC_OP, STK_IIC_OP_TX))
		वापस 1;
	करो अणु
		अगर (stk_camera_पढ़ो_reg(dev, STK_IIC_STAT, &पंचांगpval))
			वापस 1;
		i++;
	पूर्ण जबतक (पंचांगpval == 0 && i < MAX_RETRIES);
	अगर (पंचांगpval != STK_IIC_STAT_TX_OK) अणु
		अगर (पंचांगpval)
			pr_err("stk_sensor_outb failed, status=0x%02x\n",
			       पंचांगpval);
		वापस 1;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक stk_sensor_inb(काष्ठा stk_camera *dev, u8 reg, u8 *val)
अणु
	पूर्णांक i = 0;
	u8 पंचांगpval = 0;

	अगर (stk_camera_ग_लिखो_reg(dev, STK_IIC_RX_INDEX, reg))
		वापस 1;
	अगर (stk_camera_ग_लिखो_reg(dev, STK_IIC_OP, STK_IIC_OP_RX))
		वापस 1;
	करो अणु
		अगर (stk_camera_पढ़ो_reg(dev, STK_IIC_STAT, &पंचांगpval))
			वापस 1;
		i++;
	पूर्ण जबतक (पंचांगpval == 0 && i < MAX_RETRIES);
	अगर (पंचांगpval != STK_IIC_STAT_RX_OK) अणु
		अगर (पंचांगpval)
			pr_err("stk_sensor_inb failed, status=0x%02x\n",
			       पंचांगpval);
		वापस 1;
	पूर्ण

	अगर (stk_camera_पढ़ो_reg(dev, STK_IIC_RX_VALUE, &पंचांगpval))
		वापस 1;

	*val = पंचांगpval;
	वापस 0;
पूर्ण

अटल पूर्णांक stk_sensor_ग_लिखो_regvals(काष्ठा stk_camera *dev,
		काष्ठा regval *rv)
अणु
	पूर्णांक ret;
	अगर (rv == शून्य)
		वापस 0;
	जबतक (rv->reg != 0xff || rv->val != 0xff) अणु
		ret = stk_sensor_outb(dev, rv->reg, rv->val);
		अगर (ret != 0)
			वापस ret;
		rv++;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक stk_sensor_sleep(काष्ठा stk_camera *dev)
अणु
	u8 पंचांगp;
	वापस stk_sensor_inb(dev, REG_COM2, &पंचांगp)
		|| stk_sensor_outb(dev, REG_COM2, पंचांगp|COM2_SSLEEP);
पूर्ण

पूर्णांक stk_sensor_wakeup(काष्ठा stk_camera *dev)
अणु
	u8 पंचांगp;
	वापस stk_sensor_inb(dev, REG_COM2, &पंचांगp)
		|| stk_sensor_outb(dev, REG_COM2, पंचांगp&~COM2_SSLEEP);
पूर्ण

अटल काष्ठा regval ov_initvals[] = अणु
	अणुREG_CLKRC, CLK_PLLपूर्ण,
	अणुREG_COM11, 0x01पूर्ण,
	अणु0x6a, 0x7dपूर्ण,
	अणुREG_AECH, 0x40पूर्ण,
	अणुREG_GAIN, 0x00पूर्ण,
	अणुREG_BLUE, 0x80पूर्ण,
	अणुREG_RED, 0x80पूर्ण,
	/* Do not enable fast AEC क्रम now */
	/*अणुREG_COM8, COM8_FASTAEC|COM8_AECSTEP|COM8_BFILT|COM8_AGC|COM8_AECपूर्ण,*/
	अणुREG_COM8, COM8_AECSTEP|COM8_BFILT|COM8_AGC|COM8_AECपूर्ण,
	अणु0x39, 0x50पूर्ण, अणु0x38, 0x93पूर्ण,
	अणु0x37, 0x00पूर्ण, अणु0x35, 0x81पूर्ण,
	अणुREG_COM5, 0x20पूर्ण,
	अणुREG_COM1, 0x00पूर्ण,
	अणुREG_COM3, 0x00पूर्ण,
	अणुREG_COM4, 0x00पूर्ण,
	अणुREG_PSHFT, 0x00पूर्ण,
	अणु0x16, 0x07पूर्ण,
	अणु0x33, 0xe2पूर्ण, अणु0x34, 0xbfपूर्ण,
	अणुREG_COM16, 0x00पूर्ण,
	अणु0x96, 0x04पूर्ण,
	/* Gamma curve values */
/*	अणु 0x7a, 0x20 पूर्ण,		अणु 0x7b, 0x10 पूर्ण,
	अणु 0x7c, 0x1e पूर्ण,		अणु 0x7d, 0x35 पूर्ण,
	अणु 0x7e, 0x5a पूर्ण,		अणु 0x7f, 0x69 पूर्ण,
	अणु 0x80, 0x76 पूर्ण,		अणु 0x81, 0x80 पूर्ण,
	अणु 0x82, 0x88 पूर्ण,		अणु 0x83, 0x8f पूर्ण,
	अणु 0x84, 0x96 पूर्ण,		अणु 0x85, 0xa3 पूर्ण,
	अणु 0x86, 0xaf पूर्ण,		अणु 0x87, 0xc4 पूर्ण,
	अणु 0x88, 0xd7 पूर्ण,		अणु 0x89, 0xe8 पूर्ण,
*/
	अणुREG_GFIX, 0x40पूर्ण,
	अणु0x8e, 0x00पूर्ण,
	अणुREG_COM12, 0x73पूर्ण,
	अणु0x8f, 0xdfपूर्ण, अणु0x8b, 0x06पूर्ण,
	अणु0x8c, 0x20पूर्ण,
	अणु0x94, 0x88पूर्ण, अणु0x95, 0x88पूर्ण,
/*	अणुREG_COM15, 0xc1पूर्ण, TODO */
	अणु0x29, 0x3fपूर्ण,
	अणुREG_COM6, 0x42पूर्ण,
	अणुREG_BD50MAX, 0x80पूर्ण,
	अणुREG_HAECC6, 0xb8पूर्ण, अणुREG_HAECC7, 0x92पूर्ण,
	अणुREG_BD60MAX, 0x0aपूर्ण,
	अणु0x90, 0x00पूर्ण, अणु0x91, 0x00पूर्ण,
	अणुREG_HAECC1, 0x00पूर्ण, अणुREG_HAECC2, 0x00पूर्ण,
	अणुREG_AEW, 0x68पूर्ण, अणुREG_AEB, 0x5cपूर्ण,
	अणुREG_VPT, 0xc3पूर्ण,
	अणुREG_COM9, 0x2eपूर्ण,
	अणु0x2a, 0x00पूर्ण, अणु0x2b, 0x00पूर्ण,

	अणु0xff, 0xffपूर्ण, /* END MARKER */
पूर्ण;

/* Probe the I2C bus and initialise the sensor chip */
पूर्णांक stk_sensor_init(काष्ठा stk_camera *dev)
अणु
	u8 idl = 0;
	u8 idh = 0;

	अगर (stk_camera_ग_लिखो_reg(dev, STK_IIC_ENABLE, STK_IIC_ENABLE_YES)
		|| stk_camera_ग_लिखो_reg(dev, STK_IIC_ADDR, SENSOR_ADDRESS)
		|| stk_sensor_outb(dev, REG_COM7, COM7_RESET)) अणु
		pr_err("Sensor resetting failed\n");
		वापस -ENODEV;
	पूर्ण
	msleep(10);
	/* Read the manufacturer ID: ov = 0x7FA2 */
	अगर (stk_sensor_inb(dev, REG_MIDH, &idh)
	    || stk_sensor_inb(dev, REG_MIDL, &idl)) अणु
		pr_err("Strange error reading sensor ID\n");
		वापस -ENODEV;
	पूर्ण
	अगर (idh != 0x7f || idl != 0xa2) अणु
		pr_err("Huh? you don't have a sensor from ovt\n");
		वापस -ENODEV;
	पूर्ण
	अगर (stk_sensor_inb(dev, REG_PID, &idh)
	    || stk_sensor_inb(dev, REG_VER, &idl)) अणु
		pr_err("Could not read sensor model\n");
		वापस -ENODEV;
	पूर्ण
	stk_sensor_ग_लिखो_regvals(dev, ov_initvals);
	msleep(10);
	pr_info("OmniVision sensor detected, id %02X%02X at address %x\n",
		idh, idl, SENSOR_ADDRESS);
	वापस 0;
पूर्ण

/* V4L2_PIX_FMT_UYVY */
अटल काष्ठा regval ov_fmt_uyvy[] = अणु
	अणुREG_TSLB, TSLB_YLAST|0x08 पूर्ण,
	अणु 0x4f, 0x80 पूर्ण,		/* "matrix coefficient 1" */
	अणु 0x50, 0x80 पूर्ण,		/* "matrix coefficient 2" */
	अणु 0x51, 0    पूर्ण,		/* vb */
	अणु 0x52, 0x22 पूर्ण,		/* "matrix coefficient 4" */
	अणु 0x53, 0x5e पूर्ण,		/* "matrix coefficient 5" */
	अणु 0x54, 0x80 पूर्ण,		/* "matrix coefficient 6" */
	अणुREG_COM13, COM13_UVSAT|COM13_CMATRIXपूर्ण,
	अणुREG_COM15, COM15_R00FF पूर्ण,
	अणु0xff, 0xffपूर्ण, /* END MARKER */
पूर्ण;
/* V4L2_PIX_FMT_YUYV */
अटल काष्ठा regval ov_fmt_yuyv[] = अणु
	अणुREG_TSLB, 0 पूर्ण,
	अणु 0x4f, 0x80 पूर्ण,		/* "matrix coefficient 1" */
	अणु 0x50, 0x80 पूर्ण,		/* "matrix coefficient 2" */
	अणु 0x51, 0    पूर्ण,		/* vb */
	अणु 0x52, 0x22 पूर्ण,		/* "matrix coefficient 4" */
	अणु 0x53, 0x5e पूर्ण,		/* "matrix coefficient 5" */
	अणु 0x54, 0x80 पूर्ण,		/* "matrix coefficient 6" */
	अणुREG_COM13, COM13_UVSAT|COM13_CMATRIXपूर्ण,
	अणुREG_COM15, COM15_R00FF पूर्ण,
	अणु0xff, 0xffपूर्ण, /* END MARKER */
पूर्ण;

/* V4L2_PIX_FMT_RGB565X rrrrrggg gggbbbbb */
अटल काष्ठा regval ov_fmt_rgbr[] = अणु
	अणु REG_RGB444, 0 पूर्ण,	/* No RGB444 please */
	अणुREG_TSLB, 0x00पूर्ण,
	अणु REG_COM1, 0x0 पूर्ण,
	अणु REG_COM9, 0x38 पूर्ण,	/* 16x gain उच्चमानing; 0x8 is reserved bit */
	अणु 0x4f, 0xb3 पूर्ण,		/* "matrix coefficient 1" */
	अणु 0x50, 0xb3 पूर्ण,		/* "matrix coefficient 2" */
	अणु 0x51, 0    पूर्ण,		/* vb */
	अणु 0x52, 0x3d पूर्ण,		/* "matrix coefficient 4" */
	अणु 0x53, 0xa7 पूर्ण,		/* "matrix coefficient 5" */
	अणु 0x54, 0xe4 पूर्ण,		/* "matrix coefficient 6" */
	अणु REG_COM13, COM13_GAMMA पूर्ण,
	अणु REG_COM15, COM15_RGB565|COM15_R00FF पूर्ण,
	अणु 0xff, 0xff पूर्ण,
पूर्ण;

/* V4L2_PIX_FMT_RGB565 gggbbbbb rrrrrggg */
अटल काष्ठा regval ov_fmt_rgbp[] = अणु
	अणु REG_RGB444, 0 पूर्ण,	/* No RGB444 please */
	अणुREG_TSLB, TSLB_BYTEORD पूर्ण,
	अणु REG_COM1, 0x0 पूर्ण,
	अणु REG_COM9, 0x38 पूर्ण,	/* 16x gain उच्चमानing; 0x8 is reserved bit */
	अणु 0x4f, 0xb3 पूर्ण,		/* "matrix coefficient 1" */
	अणु 0x50, 0xb3 पूर्ण,		/* "matrix coefficient 2" */
	अणु 0x51, 0    पूर्ण,		/* vb */
	अणु 0x52, 0x3d पूर्ण,		/* "matrix coefficient 4" */
	अणु 0x53, 0xa7 पूर्ण,		/* "matrix coefficient 5" */
	अणु 0x54, 0xe4 पूर्ण,		/* "matrix coefficient 6" */
	अणु REG_COM13, COM13_GAMMA पूर्ण,
	अणु REG_COM15, COM15_RGB565|COM15_R00FF पूर्ण,
	अणु 0xff, 0xff पूर्ण,
पूर्ण;

/* V4L2_PIX_FMT_SRGGB8 */
अटल काष्ठा regval ov_fmt_bayer[] = अणु
	/* This changes color order */
	अणुREG_TSLB, 0x40पूर्ण, /* BGGR */
	/* अणुREG_TSLB, 0x08पूर्ण, */ /* BGGR with vertical image flipping */
	अणुREG_COM15, COM15_R00FF पूर्ण,
	अणु0xff, 0xffपूर्ण, /* END MARKER */
पूर्ण;
/*
 * Store a set of start/stop values पूर्णांकo the camera.
 */
अटल पूर्णांक stk_sensor_set_hw(काष्ठा stk_camera *dev,
		पूर्णांक hstart, पूर्णांक hstop, पूर्णांक vstart, पूर्णांक vstop)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर v;
/*
 * Horizontal: 11 bits, top 8 live in hstart and hstop.  Bottom 3 of
 * hstart are in href[2:0], bottom 3 of hstop in href[5:3].  There is
 * a mystery "edge offset" value in the top two bits of href.
 */
	ret =  stk_sensor_outb(dev, REG_HSTART, (hstart >> 3) & 0xff);
	ret += stk_sensor_outb(dev, REG_HSTOP, (hstop >> 3) & 0xff);
	ret += stk_sensor_inb(dev, REG_HREF, &v);
	v = (v & 0xc0) | ((hstop & 0x7) << 3) | (hstart & 0x7);
	msleep(10);
	ret += stk_sensor_outb(dev, REG_HREF, v);
/*
 * Vertical: similar arrangement (note: this is dअगरferent from ov7670.c)
 */
	ret += stk_sensor_outb(dev, REG_VSTART, (vstart >> 3) & 0xff);
	ret += stk_sensor_outb(dev, REG_VSTOP, (vstop >> 3) & 0xff);
	ret += stk_sensor_inb(dev, REG_VREF, &v);
	v = (v & 0xc0) | ((vstop & 0x7) << 3) | (vstart & 0x7);
	msleep(10);
	ret += stk_sensor_outb(dev, REG_VREF, v);
	वापस ret;
पूर्ण


पूर्णांक stk_sensor_configure(काष्ठा stk_camera *dev)
अणु
	पूर्णांक com7;
	/*
	 * We setup the sensor to output dummy lines in low-res modes,
	 * so we करोn't get असलurdly hight framerates.
	 */
	अचिन्हित dummylines;
	पूर्णांक flip;
	काष्ठा regval *rv;

	चयन (dev->vsettings.mode) अणु
	हाल MODE_QCIF: com7 = COM7_FMT_QCIF;
		dummylines = 604;
		अवरोध;
	हाल MODE_QVGA: com7 = COM7_FMT_QVGA;
		dummylines = 267;
		अवरोध;
	हाल MODE_CIF: com7 = COM7_FMT_CIF;
		dummylines = 412;
		अवरोध;
	हाल MODE_VGA: com7 = COM7_FMT_VGA;
		dummylines = 11;
		अवरोध;
	हाल MODE_SXGA: com7 = COM7_FMT_SXGA;
		dummylines = 0;
		अवरोध;
	शेष:
		pr_err("Unsupported mode %d\n", dev->vsettings.mode);
		वापस -EFAULT;
	पूर्ण
	चयन (dev->vsettings.palette) अणु
	हाल V4L2_PIX_FMT_UYVY:
		com7 |= COM7_YUV;
		rv = ov_fmt_uyvy;
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
		com7 |= COM7_YUV;
		rv = ov_fmt_yuyv;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565:
		com7 |= COM7_RGB;
		rv = ov_fmt_rgbp;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565X:
		com7 |= COM7_RGB;
		rv = ov_fmt_rgbr;
		अवरोध;
	हाल V4L2_PIX_FMT_SBGGR8:
		com7 |= COM7_PBAYER;
		rv = ov_fmt_bayer;
		अवरोध;
	शेष:
		pr_err("Unsupported colorspace\n");
		वापस -EFAULT;
	पूर्ण
	/*FIXME someबार the sensor go to a bad state
	stk_sensor_ग_लिखो_regvals(dev, ov_initvals); */
	stk_sensor_outb(dev, REG_COM7, com7);
	msleep(50);
	stk_sensor_ग_लिखो_regvals(dev, rv);
	flip = (dev->vsettings.vflip?MVFP_FLIP:0)
		| (dev->vsettings.hflip?MVFP_MIRROR:0);
	stk_sensor_outb(dev, REG_MVFP, flip);
	अगर (dev->vsettings.palette == V4L2_PIX_FMT_SBGGR8
			&& !dev->vsettings.vflip)
		stk_sensor_outb(dev, REG_TSLB, 0x08);
	stk_sensor_outb(dev, REG_ADVFH, dummylines >> 8);
	stk_sensor_outb(dev, REG_ADVFL, dummylines & 0xff);
	msleep(50);
	चयन (dev->vsettings.mode) अणु
	हाल MODE_VGA:
		अगर (stk_sensor_set_hw(dev, 302, 1582, 6, 486))
			pr_err("stk_sensor_set_hw failed (VGA)\n");
		अवरोध;
	हाल MODE_SXGA:
	हाल MODE_CIF:
	हाल MODE_QVGA:
	हाल MODE_QCIF:
		/*FIXME These settings seem ignored by the sensor
		अगर (stk_sensor_set_hw(dev, 220, 1500, 10, 1034))
			pr_err("stk_sensor_set_hw failed (SXGA)\n");
		*/
		अवरोध;
	पूर्ण
	msleep(10);
	वापस 0;
पूर्ण

पूर्णांक stk_sensor_set_brightness(काष्ठा stk_camera *dev, पूर्णांक br)
अणु
	अगर (br < 0 || br > 0xff)
		वापस -EINVAL;
	stk_sensor_outb(dev, REG_AEB, max(0x00, br - 6));
	stk_sensor_outb(dev, REG_AEW, min(0xff, br + 6));
	वापस 0;
पूर्ण

