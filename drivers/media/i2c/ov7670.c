<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * A V4L2 driver क्रम OmniVision OV7670 cameras.
 *
 * Copyright 2006 One Laptop Per Child Association, Inc.  Written
 * by Jonathan Corbet with substantial inspiration from Mark
 * McClelland's ovcamchip code.
 *
 * Copyright 2006-7 Jonathan Corbet <corbet@lwn.net>
 */
#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/v4l2-image-sizes.h>
#समावेश <media/i2c/ov7670.h>

MODULE_AUTHOR("Jonathan Corbet <corbet@lwn.net>");
MODULE_DESCRIPTION("A low-level driver for OmniVision ov7670 sensors");
MODULE_LICENSE("GPL");

अटल bool debug;
module_param(debug, bool, 0644);
MODULE_PARM_DESC(debug, "Debug level (0-1)");

/*
 * The 7670 sits on i2c with ID 0x42
 */
#घोषणा OV7670_I2C_ADDR 0x42

#घोषणा PLL_FACTOR	4

/* Registers */
#घोषणा REG_GAIN	0x00	/* Gain lower 8 bits (rest in vref) */
#घोषणा REG_BLUE	0x01	/* blue gain */
#घोषणा REG_RED		0x02	/* red gain */
#घोषणा REG_VREF	0x03	/* Pieces of GAIN, VSTART, VSTOP */
#घोषणा REG_COM1	0x04	/* Control 1 */
#घोषणा  COM1_CCIR656	  0x40  /* CCIR656 enable */
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
#घोषणा REG_CLKRC	0x11	/* Clocl control */
#घोषणा   CLK_EXT	  0x40	  /* Use बाह्यal घड़ी directly */
#घोषणा   CLK_SCALE	  0x3f	  /* Mask क्रम पूर्णांकernal घड़ी scale */
#घोषणा REG_COM7	0x12	/* Control 7 */
#घोषणा   COM7_RESET	  0x80	  /* Register reset */
#घोषणा   COM7_FMT_MASK	  0x38
#घोषणा   COM7_FMT_VGA	  0x00
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
#घोषणा REG_HSYST	0x30	/* HSYNC rising edge delay */
#घोषणा REG_HSYEN	0x31	/* HSYNC falling edge delay */
#घोषणा REG_HREF	0x32	/* HREF pieces */
#घोषणा REG_TSLB	0x3a	/* lots of stuff */
#घोषणा   TSLB_YLAST	  0x04	  /* UYVY or VYUY - see com13 */
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
#घोषणा   COM13_UVSWAP	  0x01	  /* V beक्रमe U - w/TSLB */
#घोषणा REG_COM14	0x3e	/* Control 14 */
#घोषणा   COM14_DCWEN	  0x10	  /* DCW/PCLK-scale enable */
#घोषणा REG_EDGE	0x3f	/* Edge enhancement factor */
#घोषणा REG_COM15	0x40	/* Control 15 */
#घोषणा   COM15_R10F0	  0x00	  /* Data range 10 to F0 */
#घोषणा	  COM15_R01FE	  0x80	  /*            01 to FE */
#घोषणा   COM15_R00FF	  0xc0	  /*            00 to FF */
#घोषणा   COM15_RGB565	  0x10	  /* RGB565 output */
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

#घोषणा REG_DBLV	0x6b	/* PLL control an debugging */
#घोषणा   DBLV_BYPASS	  0x0a	  /* Bypass PLL */
#घोषणा   DBLV_X4	  0x4a	  /* घड़ी x4 */
#घोषणा   DBLV_X6	  0x8a	  /* घड़ी x6 */
#घोषणा   DBLV_X8	  0xca	  /* घड़ी x8 */

#घोषणा REG_SCALING_XSC	0x70	/* Test pattern and horizontal scale factor */
#घोषणा   TEST_PATTTERN_0 0x80
#घोषणा REG_SCALING_YSC	0x71	/* Test pattern and vertical scale factor */
#घोषणा   TEST_PATTTERN_1 0x80

#घोषणा REG_REG76	0x76	/* OV's name */
#घोषणा   R76_BLKPCOR	  0x80	  /* Black pixel correction enable */
#घोषणा   R76_WHTPCOR	  0x40	  /* White pixel correction enable */

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

क्रमागत ov7670_model अणु
	MODEL_OV7670 = 0,
	MODEL_OV7675,
पूर्ण;

काष्ठा ov7670_win_size अणु
	पूर्णांक	width;
	पूर्णांक	height;
	अचिन्हित अक्षर com7_bit;
	पूर्णांक	hstart;		/* Start/stop values क्रम the camera.  Note */
	पूर्णांक	hstop;		/* that they करो not always make complete */
	पूर्णांक	vstart;		/* sense to humans, but evidently the sensor */
	पूर्णांक	vstop;		/* will करो the right thing... */
	काष्ठा regval_list *regs; /* Regs to tweak */
पूर्ण;

काष्ठा ov7670_devtype अणु
	/* क्रमmats supported क्रम each model */
	काष्ठा ov7670_win_size *win_sizes;
	अचिन्हित पूर्णांक n_win_sizes;
	/* callbacks क्रम frame rate control */
	पूर्णांक (*set_framerate)(काष्ठा v4l2_subdev *, काष्ठा v4l2_fract *);
	व्योम (*get_framerate)(काष्ठा v4l2_subdev *, काष्ठा v4l2_fract *);
पूर्ण;

/*
 * Inक्रमmation we मुख्यtain about a known sensor.
 */
काष्ठा ov7670_क्रमmat_काष्ठा;  /* coming later */
काष्ठा ov7670_info अणु
	काष्ठा v4l2_subdev sd;
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	काष्ठा media_pad pad;
#पूर्ण_अगर
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा अणु
		/* gain cluster */
		काष्ठा v4l2_ctrl *स्वतः_gain;
		काष्ठा v4l2_ctrl *gain;
	पूर्ण;
	काष्ठा अणु
		/* exposure cluster */
		काष्ठा v4l2_ctrl *स्वतः_exposure;
		काष्ठा v4l2_ctrl *exposure;
	पूर्ण;
	काष्ठा अणु
		/* saturation/hue cluster */
		काष्ठा v4l2_ctrl *saturation;
		काष्ठा v4l2_ctrl *hue;
	पूर्ण;
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	काष्ठा ov7670_क्रमmat_काष्ठा *fmt;  /* Current क्रमmat */
	काष्ठा ov7670_win_size *wsize;
	काष्ठा clk *clk;
	पूर्णांक on;
	काष्ठा gpio_desc *resetb_gpio;
	काष्ठा gpio_desc *pwdn_gpio;
	अचिन्हित पूर्णांक mbus_config;	/* Media bus configuration flags */
	पूर्णांक min_width;			/* Filter out smaller sizes */
	पूर्णांक min_height;			/* Filter out smaller sizes */
	पूर्णांक घड़ी_speed;		/* External घड़ी speed (MHz) */
	u8 clkrc;			/* Clock भागider value */
	bool use_smbus;			/* Use smbus I/O instead of I2C */
	bool pll_bypass;
	bool pclk_hb_disable;
	स्थिर काष्ठा ov7670_devtype *devtype; /* Device specअगरics */
पूर्ण;

अटल अंतरभूत काष्ठा ov7670_info *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा ov7670_info, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा ov7670_info, hdl)->sd;
पूर्ण



/*
 * The शेष रेजिस्टर settings, as obtained from OmniVision.  There
 * is really no making sense of most of these - lots of "reserved" values
 * and such.
 *
 * These settings give VGA YUYV.
 */

काष्ठा regval_list अणु
	अचिन्हित अक्षर reg_num;
	अचिन्हित अक्षर value;
पूर्ण;

अटल काष्ठा regval_list ov7670_शेष_regs[] = अणु
	अणु REG_COM7, COM7_RESET पूर्ण,
/*
 * Clock scale: 3 = 15fps
 *              2 = 20fps
 *              1 = 30fps
 */
	अणु REG_CLKRC, 0x1 पूर्ण,	/* OV: घड़ी scale (30 fps) */
	अणु REG_TSLB,  0x04 पूर्ण,	/* OV */
	अणु REG_COM7, 0 पूर्ण,	/* VGA */
	/*
	 * Set the hardware winकरोw.  These values from OV करोn't entirely
	 * make sense - hstop is less than hstart.  But they work...
	 */
	अणु REG_HSTART, 0x13 पूर्ण,	अणु REG_HSTOP, 0x01 पूर्ण,
	अणु REG_HREF, 0xb6 पूर्ण,	अणु REG_VSTART, 0x02 पूर्ण,
	अणु REG_VSTOP, 0x7a पूर्ण,	अणु REG_VREF, 0x0a पूर्ण,

	अणु REG_COM3, 0 पूर्ण,	अणु REG_COM14, 0 पूर्ण,
	/* Mystery scaling numbers */
	अणु REG_SCALING_XSC, 0x3a पूर्ण,
	अणु REG_SCALING_YSC, 0x35 पूर्ण,
	अणु 0x72, 0x11 पूर्ण,		अणु 0x73, 0xf0 पूर्ण,
	अणु 0xa2, 0x02 पूर्ण,		अणु REG_COM10, 0x0 पूर्ण,

	/* Gamma curve values */
	अणु 0x7a, 0x20 पूर्ण,		अणु 0x7b, 0x10 पूर्ण,
	अणु 0x7c, 0x1e पूर्ण,		अणु 0x7d, 0x35 पूर्ण,
	अणु 0x7e, 0x5a पूर्ण,		अणु 0x7f, 0x69 पूर्ण,
	अणु 0x80, 0x76 पूर्ण,		अणु 0x81, 0x80 पूर्ण,
	अणु 0x82, 0x88 पूर्ण,		अणु 0x83, 0x8f पूर्ण,
	अणु 0x84, 0x96 पूर्ण,		अणु 0x85, 0xa3 पूर्ण,
	अणु 0x86, 0xaf पूर्ण,		अणु 0x87, 0xc4 पूर्ण,
	अणु 0x88, 0xd7 पूर्ण,		अणु 0x89, 0xe8 पूर्ण,

	/* AGC and AEC parameters.  Note we start by disabling those features,
	   then turn them only after tweaking the values. */
	अणु REG_COM8, COM8_FASTAEC | COM8_AECSTEP | COM8_BFILT पूर्ण,
	अणु REG_GAIN, 0 पूर्ण,	अणु REG_AECH, 0 पूर्ण,
	अणु REG_COM4, 0x40 पूर्ण, /* magic reserved bit */
	अणु REG_COM9, 0x18 पूर्ण, /* 4x gain + magic rsvd bit */
	अणु REG_BD50MAX, 0x05 पूर्ण,	अणु REG_BD60MAX, 0x07 पूर्ण,
	अणु REG_AEW, 0x95 पूर्ण,	अणु REG_AEB, 0x33 पूर्ण,
	अणु REG_VPT, 0xe3 पूर्ण,	अणु REG_HAECC1, 0x78 पूर्ण,
	अणु REG_HAECC2, 0x68 पूर्ण,	अणु 0xa1, 0x03 पूर्ण, /* magic */
	अणु REG_HAECC3, 0xd8 पूर्ण,	अणु REG_HAECC4, 0xd8 पूर्ण,
	अणु REG_HAECC5, 0xf0 पूर्ण,	अणु REG_HAECC6, 0x90 पूर्ण,
	अणु REG_HAECC7, 0x94 पूर्ण,
	अणु REG_COM8, COM8_FASTAEC|COM8_AECSTEP|COM8_BFILT|COM8_AGC|COM8_AEC पूर्ण,

	/* Almost all of these are magic "reserved" values.  */
	अणु REG_COM5, 0x61 पूर्ण,	अणु REG_COM6, 0x4b पूर्ण,
	अणु 0x16, 0x02 पूर्ण,		अणु REG_MVFP, 0x07 पूर्ण,
	अणु 0x21, 0x02 पूर्ण,		अणु 0x22, 0x91 पूर्ण,
	अणु 0x29, 0x07 पूर्ण,		अणु 0x33, 0x0b पूर्ण,
	अणु 0x35, 0x0b पूर्ण,		अणु 0x37, 0x1d पूर्ण,
	अणु 0x38, 0x71 पूर्ण,		अणु 0x39, 0x2a पूर्ण,
	अणु REG_COM12, 0x78 पूर्ण,	अणु 0x4d, 0x40 पूर्ण,
	अणु 0x4e, 0x20 पूर्ण,		अणु REG_GFIX, 0 पूर्ण,
	अणु 0x6b, 0x4a पूर्ण,		अणु 0x74, 0x10 पूर्ण,
	अणु 0x8d, 0x4f पूर्ण,		अणु 0x8e, 0 पूर्ण,
	अणु 0x8f, 0 पूर्ण,		अणु 0x90, 0 पूर्ण,
	अणु 0x91, 0 पूर्ण,		अणु 0x96, 0 पूर्ण,
	अणु 0x9a, 0 पूर्ण,		अणु 0xb0, 0x84 पूर्ण,
	अणु 0xb1, 0x0c पूर्ण,		अणु 0xb2, 0x0e पूर्ण,
	अणु 0xb3, 0x82 पूर्ण,		अणु 0xb8, 0x0a पूर्ण,

	/* More reserved magic, some of which tweaks white balance */
	अणु 0x43, 0x0a पूर्ण,		अणु 0x44, 0xf0 पूर्ण,
	अणु 0x45, 0x34 पूर्ण,		अणु 0x46, 0x58 पूर्ण,
	अणु 0x47, 0x28 पूर्ण,		अणु 0x48, 0x3a पूर्ण,
	अणु 0x59, 0x88 पूर्ण,		अणु 0x5a, 0x88 पूर्ण,
	अणु 0x5b, 0x44 पूर्ण,		अणु 0x5c, 0x67 पूर्ण,
	अणु 0x5d, 0x49 पूर्ण,		अणु 0x5e, 0x0e पूर्ण,
	अणु 0x6c, 0x0a पूर्ण,		अणु 0x6d, 0x55 पूर्ण,
	अणु 0x6e, 0x11 पूर्ण,		अणु 0x6f, 0x9f पूर्ण, /* "9e for advance AWB" */
	अणु 0x6a, 0x40 पूर्ण,		अणु REG_BLUE, 0x40 पूर्ण,
	अणु REG_RED, 0x60 पूर्ण,
	अणु REG_COM8, COM8_FASTAEC|COM8_AECSTEP|COM8_BFILT|COM8_AGC|COM8_AEC|COM8_AWB पूर्ण,

	/* Matrix coefficients */
	अणु 0x4f, 0x80 पूर्ण,		अणु 0x50, 0x80 पूर्ण,
	अणु 0x51, 0 पूर्ण,		अणु 0x52, 0x22 पूर्ण,
	अणु 0x53, 0x5e पूर्ण,		अणु 0x54, 0x80 पूर्ण,
	अणु 0x58, 0x9e पूर्ण,

	अणु REG_COM16, COM16_AWBGAIN पूर्ण,	अणु REG_EDGE, 0 पूर्ण,
	अणु 0x75, 0x05 पूर्ण,		अणु 0x76, 0xe1 पूर्ण,
	अणु 0x4c, 0 पूर्ण,		अणु 0x77, 0x01 पूर्ण,
	अणु REG_COM13, 0xc3 पूर्ण,	अणु 0x4b, 0x09 पूर्ण,
	अणु 0xc9, 0x60 पूर्ण,		अणु REG_COM16, 0x38 पूर्ण,
	अणु 0x56, 0x40 पूर्ण,

	अणु 0x34, 0x11 पूर्ण,		अणु REG_COM11, COM11_EXP|COM11_HZAUTO पूर्ण,
	अणु 0xa4, 0x88 पूर्ण,		अणु 0x96, 0 पूर्ण,
	अणु 0x97, 0x30 पूर्ण,		अणु 0x98, 0x20 पूर्ण,
	अणु 0x99, 0x30 पूर्ण,		अणु 0x9a, 0x84 पूर्ण,
	अणु 0x9b, 0x29 पूर्ण,		अणु 0x9c, 0x03 पूर्ण,
	अणु 0x9d, 0x4c पूर्ण,		अणु 0x9e, 0x3f पूर्ण,
	अणु 0x78, 0x04 पूर्ण,

	/* Extra-weird stuff.  Some sort of multiplexor रेजिस्टर */
	अणु 0x79, 0x01 पूर्ण,		अणु 0xc8, 0xf0 पूर्ण,
	अणु 0x79, 0x0f पूर्ण,		अणु 0xc8, 0x00 पूर्ण,
	अणु 0x79, 0x10 पूर्ण,		अणु 0xc8, 0x7e पूर्ण,
	अणु 0x79, 0x0a पूर्ण,		अणु 0xc8, 0x80 पूर्ण,
	अणु 0x79, 0x0b पूर्ण,		अणु 0xc8, 0x01 पूर्ण,
	अणु 0x79, 0x0c पूर्ण,		अणु 0xc8, 0x0f पूर्ण,
	अणु 0x79, 0x0d पूर्ण,		अणु 0xc8, 0x20 पूर्ण,
	अणु 0x79, 0x09 पूर्ण,		अणु 0xc8, 0x80 पूर्ण,
	अणु 0x79, 0x02 पूर्ण,		अणु 0xc8, 0xc0 पूर्ण,
	अणु 0x79, 0x03 पूर्ण,		अणु 0xc8, 0x40 पूर्ण,
	अणु 0x79, 0x05 पूर्ण,		अणु 0xc8, 0x30 पूर्ण,
	अणु 0x79, 0x26 पूर्ण,

	अणु 0xff, 0xff पूर्ण,	/* END MARKER */
पूर्ण;


/*
 * Here we'll try to encapsulate the changes क्रम just the output
 * video क्रमmat.
 *
 * RGB656 and YUV422 come from OV; RGB444 is homebrewed.
 *
 * IMPORTANT RULE: the first entry must be क्रम COM7, see ov7670_s_fmt क्रम why.
 */


अटल काष्ठा regval_list ov7670_fmt_yuv422[] = अणु
	अणु REG_COM7, 0x0 पूर्ण,  /* Selects YUV mode */
	अणु REG_RGB444, 0 पूर्ण,	/* No RGB444 please */
	अणु REG_COM1, 0 पूर्ण,	/* CCIR601 */
	अणु REG_COM15, COM15_R00FF पूर्ण,
	अणु REG_COM9, 0x48 पूर्ण, /* 32x gain उच्चमानing; 0x8 is reserved bit */
	अणु 0x4f, 0x80 पूर्ण,		/* "matrix coefficient 1" */
	अणु 0x50, 0x80 पूर्ण,		/* "matrix coefficient 2" */
	अणु 0x51, 0    पूर्ण,		/* vb */
	अणु 0x52, 0x22 पूर्ण,		/* "matrix coefficient 4" */
	अणु 0x53, 0x5e पूर्ण,		/* "matrix coefficient 5" */
	अणु 0x54, 0x80 पूर्ण,		/* "matrix coefficient 6" */
	अणु REG_COM13, COM13_GAMMA|COM13_UVSAT पूर्ण,
	अणु 0xff, 0xff पूर्ण,
पूर्ण;

अटल काष्ठा regval_list ov7670_fmt_rgb565[] = अणु
	अणु REG_COM7, COM7_RGB पूर्ण,	/* Selects RGB mode */
	अणु REG_RGB444, 0 पूर्ण,	/* No RGB444 please */
	अणु REG_COM1, 0x0 पूर्ण,	/* CCIR601 */
	अणु REG_COM15, COM15_RGB565 पूर्ण,
	अणु REG_COM9, 0x38 पूर्ण,	/* 16x gain उच्चमानing; 0x8 is reserved bit */
	अणु 0x4f, 0xb3 पूर्ण,		/* "matrix coefficient 1" */
	अणु 0x50, 0xb3 पूर्ण,		/* "matrix coefficient 2" */
	अणु 0x51, 0    पूर्ण,		/* vb */
	अणु 0x52, 0x3d पूर्ण,		/* "matrix coefficient 4" */
	अणु 0x53, 0xa7 पूर्ण,		/* "matrix coefficient 5" */
	अणु 0x54, 0xe4 पूर्ण,		/* "matrix coefficient 6" */
	अणु REG_COM13, COM13_GAMMA|COM13_UVSAT पूर्ण,
	अणु 0xff, 0xff पूर्ण,
पूर्ण;

अटल काष्ठा regval_list ov7670_fmt_rgb444[] = अणु
	अणु REG_COM7, COM7_RGB पूर्ण,	/* Selects RGB mode */
	अणु REG_RGB444, R444_ENABLE पूर्ण,	/* Enable xxxxrrrr ggggbbbb */
	अणु REG_COM1, 0x0 पूर्ण,	/* CCIR601 */
	अणु REG_COM15, COM15_R01FE|COM15_RGB565 पूर्ण, /* Data range needed? */
	अणु REG_COM9, 0x38 पूर्ण,	/* 16x gain उच्चमानing; 0x8 is reserved bit */
	अणु 0x4f, 0xb3 पूर्ण,		/* "matrix coefficient 1" */
	अणु 0x50, 0xb3 पूर्ण,		/* "matrix coefficient 2" */
	अणु 0x51, 0    पूर्ण,		/* vb */
	अणु 0x52, 0x3d पूर्ण,		/* "matrix coefficient 4" */
	अणु 0x53, 0xa7 पूर्ण,		/* "matrix coefficient 5" */
	अणु 0x54, 0xe4 पूर्ण,		/* "matrix coefficient 6" */
	अणु REG_COM13, COM13_GAMMA|COM13_UVSAT|0x2 पूर्ण,  /* Magic rsvd bit */
	अणु 0xff, 0xff पूर्ण,
पूर्ण;

अटल काष्ठा regval_list ov7670_fmt_raw[] = अणु
	अणु REG_COM7, COM7_BAYER पूर्ण,
	अणु REG_COM13, 0x08 पूर्ण, /* No gamma, magic rsvd bit */
	अणु REG_COM16, 0x3d पूर्ण, /* Edge enhancement, denoise */
	अणु REG_REG76, 0xe1 पूर्ण, /* Pix correction, magic rsvd */
	अणु 0xff, 0xff पूर्ण,
पूर्ण;



/*
 * Low-level रेजिस्टर I/O.
 *
 * Note that there are two versions of these.  On the XO 1, the
 * i2c controller only करोes SMBUS, so that's what we use.  The
 * ov7670 is not really an SMBUS device, though, so the communication
 * is not always entirely reliable.
 */
अटल पूर्णांक ov7670_पढ़ो_smbus(काष्ठा v4l2_subdev *sd, अचिन्हित अक्षर reg,
		अचिन्हित अक्षर *value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (ret >= 0) अणु
		*value = (अचिन्हित अक्षर)ret;
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण


अटल पूर्णांक ov7670_ग_लिखो_smbus(काष्ठा v4l2_subdev *sd, अचिन्हित अक्षर reg,
		अचिन्हित अक्षर value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = i2c_smbus_ग_लिखो_byte_data(client, reg, value);

	अगर (reg == REG_COM7 && (value & COM7_RESET))
		msleep(5);  /* Wait क्रम reset to run */
	वापस ret;
पूर्ण

/*
 * On most platक्रमms, we'd rather करो straight i2c I/O.
 */
अटल पूर्णांक ov7670_पढ़ो_i2c(काष्ठा v4l2_subdev *sd, अचिन्हित अक्षर reg,
		अचिन्हित अक्षर *value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u8 data = reg;
	काष्ठा i2c_msg msg;
	पूर्णांक ret;

	/*
	 * Send out the रेजिस्टर address...
	 */
	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = 1;
	msg.buf = &data;
	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "Error %d on register write\n", ret);
		वापस ret;
	पूर्ण
	/*
	 * ...then पढ़ो back the result.
	 */
	msg.flags = I2C_M_RD;
	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret >= 0) अणु
		*value = data;
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण


अटल पूर्णांक ov7670_ग_लिखो_i2c(काष्ठा v4l2_subdev *sd, अचिन्हित अक्षर reg,
		अचिन्हित अक्षर value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा i2c_msg msg;
	अचिन्हित अक्षर data[2] = अणु reg, value पूर्ण;
	पूर्णांक ret;

	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = 2;
	msg.buf = data;
	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret > 0)
		ret = 0;
	अगर (reg == REG_COM7 && (value & COM7_RESET))
		msleep(5);  /* Wait क्रम reset to run */
	वापस ret;
पूर्ण

अटल पूर्णांक ov7670_पढ़ो(काष्ठा v4l2_subdev *sd, अचिन्हित अक्षर reg,
		अचिन्हित अक्षर *value)
अणु
	काष्ठा ov7670_info *info = to_state(sd);

	अगर (info->use_smbus)
		वापस ov7670_पढ़ो_smbus(sd, reg, value);
	अन्यथा
		वापस ov7670_पढ़ो_i2c(sd, reg, value);
पूर्ण

अटल पूर्णांक ov7670_ग_लिखो(काष्ठा v4l2_subdev *sd, अचिन्हित अक्षर reg,
		अचिन्हित अक्षर value)
अणु
	काष्ठा ov7670_info *info = to_state(sd);

	अगर (info->use_smbus)
		वापस ov7670_ग_लिखो_smbus(sd, reg, value);
	अन्यथा
		वापस ov7670_ग_लिखो_i2c(sd, reg, value);
पूर्ण

अटल पूर्णांक ov7670_update_bits(काष्ठा v4l2_subdev *sd, अचिन्हित अक्षर reg,
		अचिन्हित अक्षर mask, अचिन्हित अक्षर value)
अणु
	अचिन्हित अक्षर orig;
	पूर्णांक ret;

	ret = ov7670_पढ़ो(sd, reg, &orig);
	अगर (ret)
		वापस ret;

	वापस ov7670_ग_लिखो(sd, reg, (orig & ~mask) | (value & mask));
पूर्ण

/*
 * Write a list of रेजिस्टर settings; ff/ff stops the process.
 */
अटल पूर्णांक ov7670_ग_लिखो_array(काष्ठा v4l2_subdev *sd, काष्ठा regval_list *vals)
अणु
	जबतक (vals->reg_num != 0xff || vals->value != 0xff) अणु
		पूर्णांक ret = ov7670_ग_लिखो(sd, vals->reg_num, vals->value);

		अगर (ret < 0)
			वापस ret;
		vals++;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * Stuff that knows about the sensor.
 */
अटल पूर्णांक ov7670_reset(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	ov7670_ग_लिखो(sd, REG_COM7, COM7_RESET);
	msleep(1);
	वापस 0;
पूर्ण


अटल पूर्णांक ov7670_init(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	वापस ov7670_ग_लिखो_array(sd, ov7670_शेष_regs);
पूर्ण

अटल पूर्णांक ov7670_detect(काष्ठा v4l2_subdev *sd)
अणु
	अचिन्हित अक्षर v;
	पूर्णांक ret;

	ret = ov7670_init(sd, 0);
	अगर (ret < 0)
		वापस ret;
	ret = ov7670_पढ़ो(sd, REG_MIDH, &v);
	अगर (ret < 0)
		वापस ret;
	अगर (v != 0x7f) /* OV manuf. id. */
		वापस -ENODEV;
	ret = ov7670_पढ़ो(sd, REG_MIDL, &v);
	अगर (ret < 0)
		वापस ret;
	अगर (v != 0xa2)
		वापस -ENODEV;
	/*
	 * OK, we know we have an OmniVision chip...but which one?
	 */
	ret = ov7670_पढ़ो(sd, REG_PID, &v);
	अगर (ret < 0)
		वापस ret;
	अगर (v != 0x76)  /* PID + VER = 0x76 / 0x73 */
		वापस -ENODEV;
	ret = ov7670_पढ़ो(sd, REG_VER, &v);
	अगर (ret < 0)
		वापस ret;
	अगर (v != 0x73)  /* PID + VER = 0x76 / 0x73 */
		वापस -ENODEV;
	वापस 0;
पूर्ण


/*
 * Store inक्रमmation about the video data क्रमmat.  The color matrix
 * is deeply tied पूर्णांकo the क्रमmat, so keep the relevant values here.
 * The magic matrix numbers come from OmniVision.
 */
अटल काष्ठा ov7670_क्रमmat_काष्ठा अणु
	u32 mbus_code;
	क्रमागत v4l2_colorspace colorspace;
	काष्ठा regval_list *regs;
	पूर्णांक cmatrix[CMATRIX_LEN];
पूर्ण ov7670_क्रमmats[] = अणु
	अणु
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.regs		= ov7670_fmt_yuv422,
		.cmatrix	= अणु 128, -128, 0, -34, -94, 128 पूर्ण,
	पूर्ण,
	अणु
		.mbus_code	= MEDIA_BUS_FMT_RGB444_2X8_PADHI_LE,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.regs		= ov7670_fmt_rgb444,
		.cmatrix	= अणु 179, -179, 0, -61, -176, 228 पूर्ण,
	पूर्ण,
	अणु
		.mbus_code	= MEDIA_BUS_FMT_RGB565_2X8_LE,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.regs		= ov7670_fmt_rgb565,
		.cmatrix	= अणु 179, -179, 0, -61, -176, 228 पूर्ण,
	पूर्ण,
	अणु
		.mbus_code	= MEDIA_BUS_FMT_SBGGR8_1X8,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.regs		= ov7670_fmt_raw,
		.cmatrix	= अणु 0, 0, 0, 0, 0, 0 पूर्ण,
	पूर्ण,
पूर्ण;
#घोषणा N_OV7670_FMTS ARRAY_SIZE(ov7670_क्रमmats)


/*
 * Then there is the issue of winकरोw sizes.  Try to capture the info here.
 */

/*
 * QCIF mode is करोne (by OV) in a very strange way - it actually looks like
 * VGA with weird scaling options - they करो *not* use the canned QCIF mode
 * which is allegedly provided by the sensor.  So here's the weird रेजिस्टर
 * settings.
 */
अटल काष्ठा regval_list ov7670_qcअगर_regs[] = अणु
	अणु REG_COM3, COM3_SCALEEN|COM3_DCWEN पूर्ण,
	अणु REG_COM3, COM3_DCWEN पूर्ण,
	अणु REG_COM14, COM14_DCWEN | 0x01पूर्ण,
	अणु 0x73, 0xf1 पूर्ण,
	अणु 0xa2, 0x52 पूर्ण,
	अणु 0x7b, 0x1c पूर्ण,
	अणु 0x7c, 0x28 पूर्ण,
	अणु 0x7d, 0x3c पूर्ण,
	अणु 0x7f, 0x69 पूर्ण,
	अणु REG_COM9, 0x38 पूर्ण,
	अणु 0xa1, 0x0b पूर्ण,
	अणु 0x74, 0x19 पूर्ण,
	अणु 0x9a, 0x80 पूर्ण,
	अणु 0x43, 0x14 पूर्ण,
	अणु REG_COM13, 0xc0 पूर्ण,
	अणु 0xff, 0xff पूर्ण,
पूर्ण;

अटल काष्ठा ov7670_win_size ov7670_win_sizes[] = अणु
	/* VGA */
	अणु
		.width		= VGA_WIDTH,
		.height		= VGA_HEIGHT,
		.com7_bit	= COM7_FMT_VGA,
		.hstart		= 158,	/* These values from */
		.hstop		=  14,	/* Omnivision */
		.vstart		=  10,
		.vstop		= 490,
		.regs		= शून्य,
	पूर्ण,
	/* CIF */
	अणु
		.width		= CIF_WIDTH,
		.height		= CIF_HEIGHT,
		.com7_bit	= COM7_FMT_CIF,
		.hstart		= 170,	/* Empirically determined */
		.hstop		=  90,
		.vstart		=  14,
		.vstop		= 494,
		.regs		= शून्य,
	पूर्ण,
	/* QVGA */
	अणु
		.width		= QVGA_WIDTH,
		.height		= QVGA_HEIGHT,
		.com7_bit	= COM7_FMT_QVGA,
		.hstart		= 168,	/* Empirically determined */
		.hstop		=  24,
		.vstart		=  12,
		.vstop		= 492,
		.regs		= शून्य,
	पूर्ण,
	/* QCIF */
	अणु
		.width		= QCIF_WIDTH,
		.height		= QCIF_HEIGHT,
		.com7_bit	= COM7_FMT_VGA, /* see comment above */
		.hstart		= 456,	/* Empirically determined */
		.hstop		=  24,
		.vstart		=  14,
		.vstop		= 494,
		.regs		= ov7670_qcअगर_regs,
	पूर्ण
पूर्ण;

अटल काष्ठा ov7670_win_size ov7675_win_sizes[] = अणु
	/*
	 * Currently, only VGA is supported. Theoretically it could be possible
	 * to support CIF, QVGA and QCIF too. Taking values क्रम ov7670 as a
	 * base and tweak them empirically could be required.
	 */
	अणु
		.width		= VGA_WIDTH,
		.height		= VGA_HEIGHT,
		.com7_bit	= COM7_FMT_VGA,
		.hstart		= 158,	/* These values from */
		.hstop		=  14,	/* Omnivision */
		.vstart		=  14,  /* Empirically determined */
		.vstop		= 494,
		.regs		= शून्य,
	पूर्ण
पूर्ण;

अटल व्योम ov7675_get_framerate(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_fract *tpf)
अणु
	काष्ठा ov7670_info *info = to_state(sd);
	u32 clkrc = info->clkrc;
	पूर्णांक pll_factor;

	अगर (info->pll_bypass)
		pll_factor = 1;
	अन्यथा
		pll_factor = PLL_FACTOR;

	clkrc++;
	अगर (info->fmt->mbus_code == MEDIA_BUS_FMT_SBGGR8_1X8)
		clkrc = (clkrc >> 1);

	tpf->numerator = 1;
	tpf->denominator = (5 * pll_factor * info->घड़ी_speed) /
			(4 * clkrc);
पूर्ण

अटल पूर्णांक ov7675_apply_framerate(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ov7670_info *info = to_state(sd);
	पूर्णांक ret;

	ret = ov7670_ग_लिखो(sd, REG_CLKRC, info->clkrc);
	अगर (ret < 0)
		वापस ret;

	वापस ov7670_ग_लिखो(sd, REG_DBLV,
			    info->pll_bypass ? DBLV_BYPASS : DBLV_X4);
पूर्ण

अटल पूर्णांक ov7675_set_framerate(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_fract *tpf)
अणु
	काष्ठा ov7670_info *info = to_state(sd);
	u32 clkrc;
	पूर्णांक pll_factor;

	/*
	 * The क्रमmula is fps = 5/4*pixclk क्रम YUV/RGB and
	 * fps = 5/2*pixclk क्रम RAW.
	 *
	 * pixclk = घड़ी_speed / (clkrc + 1) * PLLfactor
	 *
	 */
	अगर (tpf->numerator == 0 || tpf->denominator == 0) अणु
		clkrc = 0;
	पूर्ण अन्यथा अणु
		pll_factor = info->pll_bypass ? 1 : PLL_FACTOR;
		clkrc = (5 * pll_factor * info->घड़ी_speed * tpf->numerator) /
			(4 * tpf->denominator);
		अगर (info->fmt->mbus_code == MEDIA_BUS_FMT_SBGGR8_1X8)
			clkrc = (clkrc << 1);
		clkrc--;
	पूर्ण

	/*
	 * The datasheet claims that clkrc = 0 will भागide the input घड़ी by 1
	 * but we've checked with an oscilloscope that it भागides by 2 instead.
	 * So, अगर clkrc = 0 just bypass the भागider.
	 */
	अगर (clkrc <= 0)
		clkrc = CLK_EXT;
	अन्यथा अगर (clkrc > CLK_SCALE)
		clkrc = CLK_SCALE;
	info->clkrc = clkrc;

	/* Recalculate frame rate */
	ov7675_get_framerate(sd, tpf);

	/*
	 * If the device is not घातered up by the host driver करो
	 * not apply any changes to H/W at this समय. Instead
	 * the framerate will be restored right after घातer-up.
	 */
	अगर (info->on)
		वापस ov7675_apply_framerate(sd);

	वापस 0;
पूर्ण

अटल व्योम ov7670_get_framerate_legacy(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_fract *tpf)
अणु
	काष्ठा ov7670_info *info = to_state(sd);

	tpf->numerator = 1;
	tpf->denominator = info->घड़ी_speed;
	अगर ((info->clkrc & CLK_EXT) == 0 && (info->clkrc & CLK_SCALE) > 1)
		tpf->denominator /= (info->clkrc & CLK_SCALE);
पूर्ण

अटल पूर्णांक ov7670_set_framerate_legacy(काष्ठा v4l2_subdev *sd,
					काष्ठा v4l2_fract *tpf)
अणु
	काष्ठा ov7670_info *info = to_state(sd);
	पूर्णांक भाग;

	अगर (tpf->numerator == 0 || tpf->denominator == 0)
		भाग = 1;  /* Reset to full rate */
	अन्यथा
		भाग = (tpf->numerator * info->घड़ी_speed) / tpf->denominator;
	अगर (भाग == 0)
		भाग = 1;
	अन्यथा अगर (भाग > CLK_SCALE)
		भाग = CLK_SCALE;
	info->clkrc = (info->clkrc & 0x80) | भाग;
	tpf->numerator = 1;
	tpf->denominator = info->घड़ी_speed / भाग;

	/*
	 * If the device is not घातered up by the host driver करो
	 * not apply any changes to H/W at this समय. Instead
	 * the framerate will be restored right after घातer-up.
	 */
	अगर (info->on)
		वापस ov7670_ग_लिखो(sd, REG_CLKRC, info->clkrc);

	वापस 0;
पूर्ण

/*
 * Store a set of start/stop values पूर्णांकo the camera.
 */
अटल पूर्णांक ov7670_set_hw(काष्ठा v4l2_subdev *sd, पूर्णांक hstart, पूर्णांक hstop,
		पूर्णांक vstart, पूर्णांक vstop)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर v;
	/*
	 * Horizontal: 11 bits, top 8 live in hstart and hstop.  Bottom 3 of
	 * hstart are in href[2:0], bottom 3 of hstop in href[5:3].  There is
	 * a mystery "edge offset" value in the top two bits of href.
	 */
	ret = ov7670_ग_लिखो(sd, REG_HSTART, (hstart >> 3) & 0xff);
	अगर (ret)
		वापस ret;
	ret = ov7670_ग_लिखो(sd, REG_HSTOP, (hstop >> 3) & 0xff);
	अगर (ret)
		वापस ret;
	ret = ov7670_पढ़ो(sd, REG_HREF, &v);
	अगर (ret)
		वापस ret;
	v = (v & 0xc0) | ((hstop & 0x7) << 3) | (hstart & 0x7);
	msleep(10);
	ret = ov7670_ग_लिखो(sd, REG_HREF, v);
	अगर (ret)
		वापस ret;
	/* Vertical: similar arrangement, but only 10 bits. */
	ret = ov7670_ग_लिखो(sd, REG_VSTART, (vstart >> 2) & 0xff);
	अगर (ret)
		वापस ret;
	ret = ov7670_ग_लिखो(sd, REG_VSTOP, (vstop >> 2) & 0xff);
	अगर (ret)
		वापस ret;
	ret = ov7670_पढ़ो(sd, REG_VREF, &v);
	अगर (ret)
		वापस ret;
	v = (v & 0xf0) | ((vstop & 0x3) << 2) | (vstart & 0x3);
	msleep(10);
	वापस ov7670_ग_लिखो(sd, REG_VREF, v);
पूर्ण


अटल पूर्णांक ov7670_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index >= N_OV7670_FMTS)
		वापस -EINVAL;

	code->code = ov7670_क्रमmats[code->index].mbus_code;
	वापस 0;
पूर्ण

अटल पूर्णांक ov7670_try_fmt_पूर्णांकernal(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_mbus_framefmt *fmt,
		काष्ठा ov7670_क्रमmat_काष्ठा **ret_fmt,
		काष्ठा ov7670_win_size **ret_wsize)
अणु
	पूर्णांक index, i;
	काष्ठा ov7670_win_size *wsize;
	काष्ठा ov7670_info *info = to_state(sd);
	अचिन्हित पूर्णांक n_win_sizes = info->devtype->n_win_sizes;
	अचिन्हित पूर्णांक win_sizes_limit = n_win_sizes;

	क्रम (index = 0; index < N_OV7670_FMTS; index++)
		अगर (ov7670_क्रमmats[index].mbus_code == fmt->code)
			अवरोध;
	अगर (index >= N_OV7670_FMTS) अणु
		/* शेष to first क्रमmat */
		index = 0;
		fmt->code = ov7670_क्रमmats[0].mbus_code;
	पूर्ण
	अगर (ret_fmt != शून्य)
		*ret_fmt = ov7670_क्रमmats + index;
	/*
	 * Fields: the OV devices claim to be progressive.
	 */
	fmt->field = V4L2_FIELD_NONE;

	/*
	 * Don't consider values that don't match min_height and min_width
	 * स्थिरraपूर्णांकs.
	 */
	अगर (info->min_width || info->min_height)
		क्रम (i = 0; i < n_win_sizes; i++) अणु
			wsize = info->devtype->win_sizes + i;

			अगर (wsize->width < info->min_width ||
				wsize->height < info->min_height) अणु
				win_sizes_limit = i;
				अवरोध;
			पूर्ण
		पूर्ण
	/*
	 * Round requested image size करोwn to the nearest
	 * we support, but not below the smallest.
	 */
	क्रम (wsize = info->devtype->win_sizes;
	     wsize < info->devtype->win_sizes + win_sizes_limit; wsize++)
		अगर (fmt->width >= wsize->width && fmt->height >= wsize->height)
			अवरोध;
	अगर (wsize >= info->devtype->win_sizes + win_sizes_limit)
		wsize--;   /* Take the smallest one */
	अगर (ret_wsize != शून्य)
		*ret_wsize = wsize;
	/*
	 * Note the size we'll actually handle.
	 */
	fmt->width = wsize->width;
	fmt->height = wsize->height;
	fmt->colorspace = ov7670_क्रमmats[index].colorspace;

	info->क्रमmat = *fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक ov7670_apply_fmt(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ov7670_info *info = to_state(sd);
	काष्ठा ov7670_win_size *wsize = info->wsize;
	अचिन्हित अक्षर com7, com10 = 0;
	पूर्णांक ret;

	/*
	 * COM7 is a pain in the ass, it करोesn't like to be पढ़ो then
	 * quickly written afterward.  But we have everything we need
	 * to set it असलolutely here, as दीर्घ as the क्रमmat-specअगरic
	 * रेजिस्टर sets list it first.
	 */
	com7 = info->fmt->regs[0].value;
	com7 |= wsize->com7_bit;
	ret = ov7670_ग_लिखो(sd, REG_COM7, com7);
	अगर (ret)
		वापस ret;

	/*
	 * Configure the media bus through COM10 रेजिस्टर
	 */
	अगर (info->mbus_config & V4L2_MBUS_VSYNC_ACTIVE_LOW)
		com10 |= COM10_VS_NEG;
	अगर (info->mbus_config & V4L2_MBUS_HSYNC_ACTIVE_LOW)
		com10 |= COM10_HREF_REV;
	अगर (info->pclk_hb_disable)
		com10 |= COM10_PCLK_HB;
	ret = ov7670_ग_लिखो(sd, REG_COM10, com10);
	अगर (ret)
		वापस ret;

	/*
	 * Now ग_लिखो the rest of the array.  Also store start/stops
	 */
	ret = ov7670_ग_लिखो_array(sd, info->fmt->regs + 1);
	अगर (ret)
		वापस ret;

	ret = ov7670_set_hw(sd, wsize->hstart, wsize->hstop, wsize->vstart,
			    wsize->vstop);
	अगर (ret)
		वापस ret;

	अगर (wsize->regs) अणु
		ret = ov7670_ग_लिखो_array(sd, wsize->regs);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * If we're running RGB565, we must reग_लिखो clkrc after setting
	 * the other parameters or the image looks poor.  If we're *not*
	 * करोing RGB565, we must not reग_लिखो clkrc or the image looks
	 * *really* poor.
	 *
	 * (Update) Now that we retain clkrc state, we should be able
	 * to ग_लिखो it unconditionally, and that will make the frame
	 * rate persistent too.
	 */
	ret = ov7670_ग_लिखो(sd, REG_CLKRC, info->clkrc);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * Set a क्रमmat.
 */
अटल पूर्णांक ov7670_set_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ov7670_info *info = to_state(sd);
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
	काष्ठा v4l2_mbus_framefmt *mbus_fmt;
#पूर्ण_अगर
	पूर्णांक ret;

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		ret = ov7670_try_fmt_पूर्णांकernal(sd, &क्रमmat->क्रमmat, शून्य, शून्य);
		अगर (ret)
			वापस ret;
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
		mbus_fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, क्रमmat->pad);
		*mbus_fmt = क्रमmat->क्रमmat;
#पूर्ण_अगर
		वापस 0;
	पूर्ण

	ret = ov7670_try_fmt_पूर्णांकernal(sd, &क्रमmat->क्रमmat, &info->fmt, &info->wsize);
	अगर (ret)
		वापस ret;

	/*
	 * If the device is not घातered up by the host driver करो
	 * not apply any changes to H/W at this समय. Instead
	 * the frame क्रमmat will be restored right after घातer-up.
	 */
	अगर (info->on)
		वापस ov7670_apply_fmt(sd);

	वापस 0;
पूर्ण

अटल पूर्णांक ov7670_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा ov7670_info *info = to_state(sd);
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
	काष्ठा v4l2_mbus_framefmt *mbus_fmt;
#पूर्ण_अगर

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
		mbus_fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
		क्रमmat->क्रमmat = *mbus_fmt;
		वापस 0;
#अन्यथा
		वापस -EINVAL;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		क्रमmat->क्रमmat = info->क्रमmat;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Implement G/S_PARM.  There is a "high quality" mode we could try
 * to करो someday; क्रम now, we just करो the frame rate tweak.
 */
अटल पूर्णांक ov7670_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *ival)
अणु
	काष्ठा ov7670_info *info = to_state(sd);


	info->devtype->get_framerate(sd, &ival->पूर्णांकerval);

	वापस 0;
पूर्ण

अटल पूर्णांक ov7670_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *ival)
अणु
	काष्ठा v4l2_fract *tpf = &ival->पूर्णांकerval;
	काष्ठा ov7670_info *info = to_state(sd);


	वापस info->devtype->set_framerate(sd, tpf);
पूर्ण


/*
 * Frame पूर्णांकervals.  Since frame rates are controlled with the घड़ी
 * भागider, we can only करो 30/n क्रम पूर्णांकeger n values.  So no continuous
 * or stepwise options.  Here we just pick a handful of logical values.
 */

अटल पूर्णांक ov7670_frame_rates[] = अणु 30, 15, 10, 5, 1 पूर्ण;

अटल पूर्णांक ov7670_क्रमागत_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_subdev_pad_config *cfg,
				      काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie)
अणु
	काष्ठा ov7670_info *info = to_state(sd);
	अचिन्हित पूर्णांक n_win_sizes = info->devtype->n_win_sizes;
	पूर्णांक i;

	अगर (fie->pad)
		वापस -EINVAL;
	अगर (fie->index >= ARRAY_SIZE(ov7670_frame_rates))
		वापस -EINVAL;

	/*
	 * Check अगर the width/height is valid.
	 *
	 * If a minimum width/height was requested, filter out the capture
	 * winकरोws that fall outside that.
	 */
	क्रम (i = 0; i < n_win_sizes; i++) अणु
		काष्ठा ov7670_win_size *win = &info->devtype->win_sizes[i];

		अगर (info->min_width && win->width < info->min_width)
			जारी;
		अगर (info->min_height && win->height < info->min_height)
			जारी;
		अगर (fie->width == win->width && fie->height == win->height)
			अवरोध;
	पूर्ण
	अगर (i == n_win_sizes)
		वापस -EINVAL;
	fie->पूर्णांकerval.numerator = 1;
	fie->पूर्णांकerval.denominator = ov7670_frame_rates[fie->index];
	वापस 0;
पूर्ण

/*
 * Frame size क्रमागतeration
 */
अटल पूर्णांक ov7670_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	काष्ठा ov7670_info *info = to_state(sd);
	पूर्णांक i;
	पूर्णांक num_valid = -1;
	__u32 index = fse->index;
	अचिन्हित पूर्णांक n_win_sizes = info->devtype->n_win_sizes;

	अगर (fse->pad)
		वापस -EINVAL;

	/*
	 * If a minimum width/height was requested, filter out the capture
	 * winकरोws that fall outside that.
	 */
	क्रम (i = 0; i < n_win_sizes; i++) अणु
		काष्ठा ov7670_win_size *win = &info->devtype->win_sizes[i];

		अगर (info->min_width && win->width < info->min_width)
			जारी;
		अगर (info->min_height && win->height < info->min_height)
			जारी;
		अगर (index == ++num_valid) अणु
			fse->min_width = fse->max_width = win->width;
			fse->min_height = fse->max_height = win->height;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * Code क्रम dealing with controls.
 */

अटल पूर्णांक ov7670_store_cmatrix(काष्ठा v4l2_subdev *sd,
		पूर्णांक matrix[CMATRIX_LEN])
अणु
	पूर्णांक i, ret;
	अचिन्हित अक्षर signbits = 0;

	/*
	 * Weird crap seems to exist in the upper part of
	 * the sign bits रेजिस्टर, so let's preserve it.
	 */
	ret = ov7670_पढ़ो(sd, REG_CMATRIX_SIGN, &signbits);
	signbits &= 0xc0;

	क्रम (i = 0; i < CMATRIX_LEN; i++) अणु
		अचिन्हित अक्षर raw;

		अगर (matrix[i] < 0) अणु
			signbits |= (1 << i);
			अगर (matrix[i] < -255)
				raw = 0xff;
			अन्यथा
				raw = (-1 * matrix[i]) & 0xff;
		पूर्ण अन्यथा अणु
			अगर (matrix[i] > 255)
				raw = 0xff;
			अन्यथा
				raw = matrix[i] & 0xff;
		पूर्ण
		ret = ov7670_ग_लिखो(sd, REG_CMATRIX_BASE + i, raw);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस ov7670_ग_लिखो(sd, REG_CMATRIX_SIGN, signbits);
पूर्ण


/*
 * Hue also requires messing with the color matrix.  It also requires
 * trig functions, which tend not to be well supported in the kernel.
 * So here is a simple table of sine values, 0-90 degrees, in steps
 * of five degrees.  Values are multiplied by 1000.
 *
 * The following naive approximate trig functions require an argument
 * carefully limited to -180 <= theta <= 180.
 */
#घोषणा SIN_STEP 5
अटल स्थिर पूर्णांक ov7670_sin_table[] = अणु
	   0,	 87,   173,   258,   342,   422,
	 499,	573,   642,   707,   766,   819,
	 866,	906,   939,   965,   984,   996,
	1000
पूर्ण;

अटल पूर्णांक ov7670_sine(पूर्णांक theta)
अणु
	पूर्णांक chs = 1;
	पूर्णांक sine;

	अगर (theta < 0) अणु
		theta = -theta;
		chs = -1;
	पूर्ण
	अगर (theta <= 90)
		sine = ov7670_sin_table[theta/SIN_STEP];
	अन्यथा अणु
		theta -= 90;
		sine = 1000 - ov7670_sin_table[theta/SIN_STEP];
	पूर्ण
	वापस sine*chs;
पूर्ण

अटल पूर्णांक ov7670_cosine(पूर्णांक theta)
अणु
	theta = 90 - theta;
	अगर (theta > 180)
		theta -= 360;
	अन्यथा अगर (theta < -180)
		theta += 360;
	वापस ov7670_sine(theta);
पूर्ण




अटल व्योम ov7670_calc_cmatrix(काष्ठा ov7670_info *info,
		पूर्णांक matrix[CMATRIX_LEN], पूर्णांक sat, पूर्णांक hue)
अणु
	पूर्णांक i;
	/*
	 * Apply the current saturation setting first.
	 */
	क्रम (i = 0; i < CMATRIX_LEN; i++)
		matrix[i] = (info->fmt->cmatrix[i] * sat) >> 7;
	/*
	 * Then, अगर need be, rotate the hue value.
	 */
	अगर (hue != 0) अणु
		पूर्णांक sपूर्णांकh, costh, पंचांगpmatrix[CMATRIX_LEN];

		स_नकल(पंचांगpmatrix, matrix, CMATRIX_LEN*माप(पूर्णांक));
		sपूर्णांकh = ov7670_sine(hue);
		costh = ov7670_cosine(hue);

		matrix[0] = (matrix[3]*sपूर्णांकh + matrix[0]*costh)/1000;
		matrix[1] = (matrix[4]*sपूर्णांकh + matrix[1]*costh)/1000;
		matrix[2] = (matrix[5]*sपूर्णांकh + matrix[2]*costh)/1000;
		matrix[3] = (matrix[3]*costh - matrix[0]*sपूर्णांकh)/1000;
		matrix[4] = (matrix[4]*costh - matrix[1]*sपूर्णांकh)/1000;
		matrix[5] = (matrix[5]*costh - matrix[2]*sपूर्णांकh)/1000;
	पूर्ण
पूर्ण



अटल पूर्णांक ov7670_s_sat_hue(काष्ठा v4l2_subdev *sd, पूर्णांक sat, पूर्णांक hue)
अणु
	काष्ठा ov7670_info *info = to_state(sd);
	पूर्णांक matrix[CMATRIX_LEN];

	ov7670_calc_cmatrix(info, matrix, sat, hue);
	वापस ov7670_store_cmatrix(sd, matrix);
पूर्ण


/*
 * Some weird रेजिस्टरs seem to store values in a sign/magnitude क्रमmat!
 */

अटल अचिन्हित अक्षर ov7670_असल_to_sm(अचिन्हित अक्षर v)
अणु
	अगर (v > 127)
		वापस v & 0x7f;
	वापस (128 - v) | 0x80;
पूर्ण

अटल पूर्णांक ov7670_s_brightness(काष्ठा v4l2_subdev *sd, पूर्णांक value)
अणु
	अचिन्हित अक्षर com8 = 0, v;

	ov7670_पढ़ो(sd, REG_COM8, &com8);
	com8 &= ~COM8_AEC;
	ov7670_ग_लिखो(sd, REG_COM8, com8);
	v = ov7670_असल_to_sm(value);
	वापस ov7670_ग_लिखो(sd, REG_BRIGHT, v);
पूर्ण

अटल पूर्णांक ov7670_s_contrast(काष्ठा v4l2_subdev *sd, पूर्णांक value)
अणु
	वापस ov7670_ग_लिखो(sd, REG_CONTRAS, (अचिन्हित अक्षर) value);
पूर्ण

अटल पूर्णांक ov7670_s_hflip(काष्ठा v4l2_subdev *sd, पूर्णांक value)
अणु
	अचिन्हित अक्षर v = 0;
	पूर्णांक ret;

	ret = ov7670_पढ़ो(sd, REG_MVFP, &v);
	अगर (ret)
		वापस ret;
	अगर (value)
		v |= MVFP_MIRROR;
	अन्यथा
		v &= ~MVFP_MIRROR;
	msleep(10);  /* FIXME */
	वापस ov7670_ग_लिखो(sd, REG_MVFP, v);
पूर्ण

अटल पूर्णांक ov7670_s_vflip(काष्ठा v4l2_subdev *sd, पूर्णांक value)
अणु
	अचिन्हित अक्षर v = 0;
	पूर्णांक ret;

	ret = ov7670_पढ़ो(sd, REG_MVFP, &v);
	अगर (ret)
		वापस ret;
	अगर (value)
		v |= MVFP_FLIP;
	अन्यथा
		v &= ~MVFP_FLIP;
	msleep(10);  /* FIXME */
	वापस ov7670_ग_लिखो(sd, REG_MVFP, v);
पूर्ण

/*
 * GAIN is split between REG_GAIN and REG_VREF[7:6].  If one believes
 * the data sheet, the VREF parts should be the most signअगरicant, but
 * experience shows otherwise.  There seems to be little value in
 * messing with the VREF bits, so we leave them alone.
 */
अटल पूर्णांक ov7670_g_gain(काष्ठा v4l2_subdev *sd, __s32 *value)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर gain;

	ret = ov7670_पढ़ो(sd, REG_GAIN, &gain);
	अगर (ret)
		वापस ret;
	*value = gain;
	वापस 0;
पूर्ण

अटल पूर्णांक ov7670_s_gain(काष्ठा v4l2_subdev *sd, पूर्णांक value)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर com8;

	ret = ov7670_ग_लिखो(sd, REG_GAIN, value & 0xff);
	अगर (ret)
		वापस ret;
	/* Have to turn off AGC as well */
	ret = ov7670_पढ़ो(sd, REG_COM8, &com8);
	अगर (ret)
		वापस ret;
	वापस ov7670_ग_लिखो(sd, REG_COM8, com8 & ~COM8_AGC);
पूर्ण

/*
 * Tweak स्वतःgain.
 */
अटल पूर्णांक ov7670_s_स्वतःgain(काष्ठा v4l2_subdev *sd, पूर्णांक value)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर com8;

	ret = ov7670_पढ़ो(sd, REG_COM8, &com8);
	अगर (ret == 0) अणु
		अगर (value)
			com8 |= COM8_AGC;
		अन्यथा
			com8 &= ~COM8_AGC;
		ret = ov7670_ग_लिखो(sd, REG_COM8, com8);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ov7670_s_exp(काष्ठा v4l2_subdev *sd, पूर्णांक value)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर com1, com8, aech, aechh;

	ret = ov7670_पढ़ो(sd, REG_COM1, &com1) +
		ov7670_पढ़ो(sd, REG_COM8, &com8) +
		ov7670_पढ़ो(sd, REG_AECHH, &aechh);
	अगर (ret)
		वापस ret;

	com1 = (com1 & 0xfc) | (value & 0x03);
	aech = (value >> 2) & 0xff;
	aechh = (aechh & 0xc0) | ((value >> 10) & 0x3f);
	ret = ov7670_ग_लिखो(sd, REG_COM1, com1) +
		ov7670_ग_लिखो(sd, REG_AECH, aech) +
		ov7670_ग_लिखो(sd, REG_AECHH, aechh);
	/* Have to turn off AEC as well */
	अगर (ret == 0)
		ret = ov7670_ग_लिखो(sd, REG_COM8, com8 & ~COM8_AEC);
	वापस ret;
पूर्ण

/*
 * Tweak स्वतःexposure.
 */
अटल पूर्णांक ov7670_s_स्वतःexp(काष्ठा v4l2_subdev *sd,
		क्रमागत v4l2_exposure_स्वतः_type value)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर com8;

	ret = ov7670_पढ़ो(sd, REG_COM8, &com8);
	अगर (ret == 0) अणु
		अगर (value == V4L2_EXPOSURE_AUTO)
			com8 |= COM8_AEC;
		अन्यथा
			com8 &= ~COM8_AEC;
		ret = ov7670_ग_लिखो(sd, REG_COM8, com8);
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर अक्षर * स्थिर ov7670_test_pattern_menu[] = अणु
	"No test output",
	"Shifting \"1\"",
	"8-bar color bar",
	"Fade to gray color bar",
पूर्ण;

अटल पूर्णांक ov7670_s_test_pattern(काष्ठा v4l2_subdev *sd, पूर्णांक value)
अणु
	पूर्णांक ret;

	ret = ov7670_update_bits(sd, REG_SCALING_XSC, TEST_PATTTERN_0,
				value & BIT(0) ? TEST_PATTTERN_0 : 0);
	अगर (ret)
		वापस ret;

	वापस ov7670_update_bits(sd, REG_SCALING_YSC, TEST_PATTTERN_1,
				value & BIT(1) ? TEST_PATTTERN_1 : 0);
पूर्ण

अटल पूर्णांक ov7670_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा ov7670_info *info = to_state(sd);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTOGAIN:
		वापस ov7670_g_gain(sd, &info->gain->val);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ov7670_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा ov7670_info *info = to_state(sd);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		वापस ov7670_s_brightness(sd, ctrl->val);
	हाल V4L2_CID_CONTRAST:
		वापस ov7670_s_contrast(sd, ctrl->val);
	हाल V4L2_CID_SATURATION:
		वापस ov7670_s_sat_hue(sd,
				info->saturation->val, info->hue->val);
	हाल V4L2_CID_VFLIP:
		वापस ov7670_s_vflip(sd, ctrl->val);
	हाल V4L2_CID_HFLIP:
		वापस ov7670_s_hflip(sd, ctrl->val);
	हाल V4L2_CID_AUTOGAIN:
		/* Only set manual gain अगर स्वतः gain is not explicitly
		   turned on. */
		अगर (!ctrl->val) अणु
			/* ov7670_s_gain turns off स्वतः gain */
			वापस ov7670_s_gain(sd, info->gain->val);
		पूर्ण
		वापस ov7670_s_स्वतःgain(sd, ctrl->val);
	हाल V4L2_CID_EXPOSURE_AUTO:
		/* Only set manual exposure अगर स्वतः exposure is not explicitly
		   turned on. */
		अगर (ctrl->val == V4L2_EXPOSURE_MANUAL) अणु
			/* ov7670_s_exp turns off स्वतः exposure */
			वापस ov7670_s_exp(sd, info->exposure->val);
		पूर्ण
		वापस ov7670_s_स्वतःexp(sd, ctrl->val);
	हाल V4L2_CID_TEST_PATTERN:
		वापस ov7670_s_test_pattern(sd, ctrl->val);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov7670_ctrl_ops = अणु
	.s_ctrl = ov7670_s_ctrl,
	.g_अस्थिर_ctrl = ov7670_g_अस्थिर_ctrl,
पूर्ण;

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक ov7670_g_रेजिस्टर(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	अचिन्हित अक्षर val = 0;
	पूर्णांक ret;

	ret = ov7670_पढ़ो(sd, reg->reg & 0xff, &val);
	reg->val = val;
	reg->size = 1;
	वापस ret;
पूर्ण

अटल पूर्णांक ov7670_s_रेजिस्टर(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	ov7670_ग_लिखो(sd, reg->reg & 0xff, reg->val & 0xff);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम ov7670_घातer_on(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ov7670_info *info = to_state(sd);

	अगर (info->on)
		वापस;

	clk_prepare_enable(info->clk);

	अगर (info->pwdn_gpio)
		gpiod_set_value(info->pwdn_gpio, 0);
	अगर (info->resetb_gpio) अणु
		gpiod_set_value(info->resetb_gpio, 1);
		usleep_range(500, 1000);
		gpiod_set_value(info->resetb_gpio, 0);
	पूर्ण
	अगर (info->pwdn_gpio || info->resetb_gpio || info->clk)
		usleep_range(3000, 5000);

	info->on = true;
पूर्ण

अटल व्योम ov7670_घातer_off(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा ov7670_info *info = to_state(sd);

	अगर (!info->on)
		वापस;

	clk_disable_unprepare(info->clk);

	अगर (info->pwdn_gpio)
		gpiod_set_value(info->pwdn_gpio, 1);

	info->on = false;
पूर्ण

अटल पूर्णांक ov7670_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा ov7670_info *info = to_state(sd);

	अगर (info->on == on)
		वापस 0;

	अगर (on) अणु
		ov7670_घातer_on(sd);
		ov7670_init(sd, 0);
		ov7670_apply_fmt(sd);
		ov7675_apply_framerate(sd);
		v4l2_ctrl_handler_setup(&info->hdl);
	पूर्ण अन्यथा अणु
		ov7670_घातer_off(sd);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ov7670_get_शेष_क्रमmat(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_mbus_framefmt *क्रमmat)
अणु
	काष्ठा ov7670_info *info = to_state(sd);

	क्रमmat->width = info->devtype->win_sizes[0].width;
	क्रमmat->height = info->devtype->win_sizes[0].height;
	क्रमmat->colorspace = info->fmt->colorspace;
	क्रमmat->code = info->fmt->mbus_code;
	क्रमmat->field = V4L2_FIELD_NONE;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
अटल पूर्णांक ov7670_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat =
				v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0);

	ov7670_get_शेष_क्रमmat(sd, क्रमmat);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_core_ops ov7670_core_ops = अणु
	.reset = ov7670_reset,
	.init = ov7670_init,
	.s_घातer = ov7670_s_घातer,
	.log_status = v4l2_ctrl_subdev_log_status,
	.subscribe_event = v4l2_ctrl_subdev_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = ov7670_g_रेजिस्टर,
	.s_रेजिस्टर = ov7670_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov7670_video_ops = अणु
	.s_frame_पूर्णांकerval = ov7670_s_frame_पूर्णांकerval,
	.g_frame_पूर्णांकerval = ov7670_g_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov7670_pad_ops = अणु
	.क्रमागत_frame_पूर्णांकerval = ov7670_क्रमागत_frame_पूर्णांकerval,
	.क्रमागत_frame_size = ov7670_क्रमागत_frame_size,
	.क्रमागत_mbus_code = ov7670_क्रमागत_mbus_code,
	.get_fmt = ov7670_get_fmt,
	.set_fmt = ov7670_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov7670_ops = अणु
	.core = &ov7670_core_ops,
	.video = &ov7670_video_ops,
	.pad = &ov7670_pad_ops,
पूर्ण;

#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ov7670_subdev_पूर्णांकernal_ops = अणु
	.खोलो = ov7670_खोलो,
पूर्ण;
#पूर्ण_अगर

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा ov7670_devtype ov7670_devdata[] = अणु
	[MODEL_OV7670] = अणु
		.win_sizes = ov7670_win_sizes,
		.n_win_sizes = ARRAY_SIZE(ov7670_win_sizes),
		.set_framerate = ov7670_set_framerate_legacy,
		.get_framerate = ov7670_get_framerate_legacy,
	पूर्ण,
	[MODEL_OV7675] = अणु
		.win_sizes = ov7675_win_sizes,
		.n_win_sizes = ARRAY_SIZE(ov7675_win_sizes),
		.set_framerate = ov7675_set_framerate,
		.get_framerate = ov7675_get_framerate,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ov7670_init_gpio(काष्ठा i2c_client *client, काष्ठा ov7670_info *info)
अणु
	info->pwdn_gpio = devm_gpiod_get_optional(&client->dev, "powerdown",
			GPIOD_OUT_LOW);
	अगर (IS_ERR(info->pwdn_gpio)) अणु
		dev_info(&client->dev, "can't get %s GPIO\n", "powerdown");
		वापस PTR_ERR(info->pwdn_gpio);
	पूर्ण

	info->resetb_gpio = devm_gpiod_get_optional(&client->dev, "reset",
			GPIOD_OUT_LOW);
	अगर (IS_ERR(info->resetb_gpio)) अणु
		dev_info(&client->dev, "can't get %s GPIO\n", "reset");
		वापस PTR_ERR(info->resetb_gpio);
	पूर्ण

	usleep_range(3000, 5000);

	वापस 0;
पूर्ण

/*
 * ov7670_parse_dt() - Parse device tree to collect mbus configuration
 *			properties
 */
अटल पूर्णांक ov7670_parse_dt(काष्ठा device *dev,
			   काष्ठा ov7670_info *info)
अणु
	काष्ठा fwnode_handle *fwnode = dev_fwnode(dev);
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु .bus_type = 0 पूर्ण;
	काष्ठा fwnode_handle *ep;
	पूर्णांक ret;

	अगर (!fwnode)
		वापस -EINVAL;

	info->pclk_hb_disable = false;
	अगर (fwnode_property_present(fwnode, "ov7670,pclk-hb-disable"))
		info->pclk_hb_disable = true;

	ep = fwnode_graph_get_next_endpoपूर्णांक(fwnode, शून्य);
	अगर (!ep)
		वापस -EINVAL;

	ret = v4l2_fwnode_endpoपूर्णांक_parse(ep, &bus_cfg);
	fwnode_handle_put(ep);
	अगर (ret)
		वापस ret;

	अगर (bus_cfg.bus_type != V4L2_MBUS_PARALLEL) अणु
		dev_err(dev, "Unsupported media bus type\n");
		वापस ret;
	पूर्ण
	info->mbus_config = bus_cfg.bus.parallel.flags;

	वापस 0;
पूर्ण

अटल पूर्णांक ov7670_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा v4l2_fract tpf;
	काष्ठा v4l2_subdev *sd;
	काष्ठा ov7670_info *info;
	पूर्णांक ret;

	info = devm_kzalloc(&client->dev, माप(*info), GFP_KERNEL);
	अगर (info == शून्य)
		वापस -ENOMEM;
	sd = &info->sd;
	v4l2_i2c_subdev_init(sd, client, &ov7670_ops);

#अगर_घोषित CONFIG_VIDEO_V4L2_SUBDEV_API
	sd->पूर्णांकernal_ops = &ov7670_subdev_पूर्णांकernal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;
#पूर्ण_अगर

	info->घड़ी_speed = 30; /* शेष: a guess */

	अगर (dev_fwnode(&client->dev)) अणु
		ret = ov7670_parse_dt(&client->dev, info);
		अगर (ret)
			वापस ret;

	पूर्ण अन्यथा अगर (client->dev.platक्रमm_data) अणु
		काष्ठा ov7670_config *config = client->dev.platक्रमm_data;

		/*
		 * Must apply configuration beक्रमe initializing device, because it
		 * selects I/O method.
		 */
		info->min_width = config->min_width;
		info->min_height = config->min_height;
		info->use_smbus = config->use_smbus;

		अगर (config->घड़ी_speed)
			info->घड़ी_speed = config->घड़ी_speed;

		अगर (config->pll_bypass)
			info->pll_bypass = true;

		अगर (config->pclk_hb_disable)
			info->pclk_hb_disable = true;
	पूर्ण

	info->clk = devm_clk_get(&client->dev, "xclk"); /* optional */
	अगर (IS_ERR(info->clk)) अणु
		ret = PTR_ERR(info->clk);
		अगर (ret == -ENOENT)
			info->clk = शून्य;
		अन्यथा
			वापस ret;
	पूर्ण

	ret = ov7670_init_gpio(client, info);
	अगर (ret)
		वापस ret;

	ov7670_घातer_on(sd);

	अगर (info->clk) अणु
		info->घड़ी_speed = clk_get_rate(info->clk) / 1000000;
		अगर (info->घड़ी_speed < 10 || info->घड़ी_speed > 48) अणु
			ret = -EINVAL;
			जाओ घातer_off;
		पूर्ण
	पूर्ण

	/* Make sure it's an ov7670 */
	ret = ov7670_detect(sd);
	अगर (ret) अणु
		v4l_dbg(1, debug, client,
			"chip found @ 0x%x (%s) is not an ov7670 chip.\n",
			client->addr << 1, client->adapter->name);
		जाओ घातer_off;
	पूर्ण
	v4l_info(client, "chip found @ 0x%02x (%s)\n",
			client->addr << 1, client->adapter->name);

	info->devtype = &ov7670_devdata[id->driver_data];
	info->fmt = &ov7670_क्रमmats[0];
	info->wsize = &info->devtype->win_sizes[0];

	ov7670_get_शेष_क्रमmat(sd, &info->क्रमmat);

	info->clkrc = 0;

	/* Set शेष frame rate to 30 fps */
	tpf.numerator = 1;
	tpf.denominator = 30;
	info->devtype->set_framerate(sd, &tpf);

	v4l2_ctrl_handler_init(&info->hdl, 10);
	v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 127, 1, 64);
	v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
	info->saturation = v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_SATURATION, 0, 256, 1, 128);
	info->hue = v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_HUE, -180, 180, 5, 0);
	info->gain = v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_GAIN, 0, 255, 1, 128);
	info->स्वतः_gain = v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	info->exposure = v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 65535, 1, 500);
	info->स्वतः_exposure = v4l2_ctrl_new_std_menu(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_EXPOSURE_AUTO, V4L2_EXPOSURE_MANUAL, 0,
			V4L2_EXPOSURE_AUTO);
	v4l2_ctrl_new_std_menu_items(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_TEST_PATTERN,
			ARRAY_SIZE(ov7670_test_pattern_menu) - 1, 0, 0,
			ov7670_test_pattern_menu);
	sd->ctrl_handler = &info->hdl;
	अगर (info->hdl.error) अणु
		ret = info->hdl.error;

		जाओ hdl_मुक्त;
	पूर्ण
	/*
	 * We have checked empirically that hw allows to पढ़ो back the gain
	 * value chosen by स्वतः gain but that's not the हाल क्रम स्वतः exposure.
	 */
	v4l2_ctrl_स्वतः_cluster(2, &info->स्वतः_gain, 0, true);
	v4l2_ctrl_स्वतः_cluster(2, &info->स्वतः_exposure,
			       V4L2_EXPOSURE_MANUAL, false);
	v4l2_ctrl_cluster(2, &info->saturation);

#अगर defined(CONFIG_MEDIA_CONTROLLER)
	info->pad.flags = MEDIA_PAD_FL_SOURCE;
	info->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&info->sd.entity, 1, &info->pad);
	अगर (ret < 0)
		जाओ hdl_मुक्त;
#पूर्ण_अगर

	v4l2_ctrl_handler_setup(&info->hdl);

	ret = v4l2_async_रेजिस्टर_subdev(&info->sd);
	अगर (ret < 0)
		जाओ entity_cleanup;

	ov7670_घातer_off(sd);
	वापस 0;

entity_cleanup:
	media_entity_cleanup(&info->sd.entity);
hdl_मुक्त:
	v4l2_ctrl_handler_मुक्त(&info->hdl);
घातer_off:
	ov7670_घातer_off(sd);
	वापस ret;
पूर्ण

अटल पूर्णांक ov7670_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov7670_info *info = to_state(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&info->hdl);
	media_entity_cleanup(&info->sd.entity);
	ov7670_घातer_off(sd);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ov7670_id[] = अणु
	अणु "ov7670", MODEL_OV7670 पूर्ण,
	अणु "ov7675", MODEL_OV7675 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ov7670_id);

#अगर IS_ENABLED(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id ov7670_of_match[] = अणु
	अणु .compatible = "ovti,ov7670", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ov7670_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver ov7670_driver = अणु
	.driver = अणु
		.name	= "ov7670",
		.of_match_table = of_match_ptr(ov7670_of_match),
	पूर्ण,
	.probe		= ov7670_probe,
	.हटाओ		= ov7670_हटाओ,
	.id_table	= ov7670_id,
पूर्ण;

module_i2c_driver(ov7670_driver);
