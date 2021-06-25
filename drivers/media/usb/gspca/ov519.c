<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OV519 driver
 *
 * Copyright (C) 2008-2011 Jean-Franथईois Moine <moinejf@मुक्त.fr>
 * Copyright (C) 2009 Hans de Goede <hdegoede@redhat.com>
 *
 * This module is adapted from the ov51x-jpeg package, which itself
 * was adapted from the ov511 driver.
 *
 * Original copyright क्रम the ov511 driver is:
 *
 * Copyright (c) 1999-2006 Mark W. McClelland
 * Support क्रम OV519, OV8610 Copyright (c) 2003 Joerg Heckenbach
 * Many improvements by Bret Wallach <bwallac1@san.rr.com>
 * Color fixes by by Orion Sky Lawlor <olawlor@acm.org> (2/26/2000)
 * OV7620 fixes by Charl P. Botha <cpbotha@ieee.org>
 * Changes by Claudio Matsuoka <claudio@conectiva.com>
 *
 * ov51x-jpeg original copyright is:
 *
 * Copyright (c) 2004-2007 Roमुख्य Beauxis <toots@rastageeks.org>
 * Support क्रम OV7670 sensors was contributed by Sam Skipsey <aoanla@yahoo.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "ov519"

#समावेश <linux/input.h>
#समावेश "gspca.h"

/* The jpeg_hdr is used by w996Xcf only */
/* The CONEX_CAM define क्रम jpeg.h needs renaming, now its used here too */
#घोषणा CONEX_CAM
#समावेश "jpeg.h"

MODULE_AUTHOR("Jean-Francois Moine <http://moinejf.free.fr>");
MODULE_DESCRIPTION("OV519 USB Camera Driver");
MODULE_LICENSE("GPL");

/* global parameters */
अटल पूर्णांक frame_rate;

/* Number of बार to retry a failed I2C transaction. Increase this अगर you
 * are getting "Failed to read sensor ID..." */
अटल पूर्णांक i2c_detect_tries = 10;

/* ov519 device descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;		/* !! must be the first item */

	काष्ठा v4l2_ctrl *jpegqual;
	काष्ठा v4l2_ctrl *freq;
	काष्ठा अणु /* h/vflip control cluster */
		काष्ठा v4l2_ctrl *hflip;
		काष्ठा v4l2_ctrl *vflip;
	पूर्ण;
	काष्ठा अणु /* स्वतःbrightness/brightness control cluster */
		काष्ठा v4l2_ctrl *स्वतःbright;
		काष्ठा v4l2_ctrl *brightness;
	पूर्ण;

	u8 revision;

	u8 packet_nr;

	अक्षर bridge;
#घोषणा BRIDGE_OV511		0
#घोषणा BRIDGE_OV511PLUS	1
#घोषणा BRIDGE_OV518		2
#घोषणा BRIDGE_OV518PLUS	3
#घोषणा BRIDGE_OV519		4		/* = ov530 */
#घोषणा BRIDGE_OVFX2		5
#घोषणा BRIDGE_W9968CF		6
#घोषणा BRIDGE_MASK		7

	अक्षर invert_led;
#घोषणा BRIDGE_INVERT_LED	8

	अक्षर snapshot_pressed;
	अक्षर snapshot_needs_reset;

	/* Determined by sensor type */
	u8 sअगर;

#घोषणा QUALITY_MIN 50
#घोषणा QUALITY_MAX 70
#घोषणा QUALITY_DEF 50

	u8 stopped;		/* Streaming is temporarily छोड़ोd */
	u8 first_frame;

	u8 frame_rate;		/* current Framerate */
	u8 घड़ीभाग;		/* घड़ीभाग override */

	s8 sensor;		/* Type of image sensor chip (SEN_*) */

	u8 sensor_addr;
	u16 sensor_width;
	u16 sensor_height;
	s16 sensor_reg_cache[256];

	u8 jpeg_hdr[JPEG_HDR_SZ];
पूर्ण;
क्रमागत sensors अणु
	SEN_OV2610,
	SEN_OV2610AE,
	SEN_OV3610,
	SEN_OV6620,
	SEN_OV6630,
	SEN_OV66308AF,
	SEN_OV7610,
	SEN_OV7620,
	SEN_OV7620AE,
	SEN_OV7640,
	SEN_OV7648,
	SEN_OV7660,
	SEN_OV7670,
	SEN_OV76BE,
	SEN_OV8610,
	SEN_OV9600,
पूर्ण;

/* Note this is a bit of a hack, but the w9968cf driver needs the code क्रम all
   the ov sensors which is alपढ़ोy present here. When we have the समय we
   really should move the sensor drivers to v4l2 sub drivers. */
#समावेश "w996Xcf.c"

/* table of the disabled controls */
काष्ठा ctrl_valid अणु
	अचिन्हित पूर्णांक has_brightness:1;
	अचिन्हित पूर्णांक has_contrast:1;
	अचिन्हित पूर्णांक has_exposure:1;
	अचिन्हित पूर्णांक has_स्वतःgain:1;
	अचिन्हित पूर्णांक has_sat:1;
	अचिन्हित पूर्णांक has_hvflip:1;
	अचिन्हित पूर्णांक has_स्वतःbright:1;
	अचिन्हित पूर्णांक has_freq:1;
पूर्ण;

अटल स्थिर काष्ठा ctrl_valid valid_controls[] = अणु
	[SEN_OV2610] = अणु
		.has_exposure = 1,
		.has_स्वतःgain = 1,
	पूर्ण,
	[SEN_OV2610AE] = अणु
		.has_exposure = 1,
		.has_स्वतःgain = 1,
	पूर्ण,
	[SEN_OV3610] = अणु
		/* No controls */
	पूर्ण,
	[SEN_OV6620] = अणु
		.has_brightness = 1,
		.has_contrast = 1,
		.has_sat = 1,
		.has_स्वतःbright = 1,
		.has_freq = 1,
	पूर्ण,
	[SEN_OV6630] = अणु
		.has_brightness = 1,
		.has_contrast = 1,
		.has_sat = 1,
		.has_स्वतःbright = 1,
		.has_freq = 1,
	पूर्ण,
	[SEN_OV66308AF] = अणु
		.has_brightness = 1,
		.has_contrast = 1,
		.has_sat = 1,
		.has_स्वतःbright = 1,
		.has_freq = 1,
	पूर्ण,
	[SEN_OV7610] = अणु
		.has_brightness = 1,
		.has_contrast = 1,
		.has_sat = 1,
		.has_स्वतःbright = 1,
		.has_freq = 1,
	पूर्ण,
	[SEN_OV7620] = अणु
		.has_brightness = 1,
		.has_contrast = 1,
		.has_sat = 1,
		.has_स्वतःbright = 1,
		.has_freq = 1,
	पूर्ण,
	[SEN_OV7620AE] = अणु
		.has_brightness = 1,
		.has_contrast = 1,
		.has_sat = 1,
		.has_स्वतःbright = 1,
		.has_freq = 1,
	पूर्ण,
	[SEN_OV7640] = अणु
		.has_brightness = 1,
		.has_sat = 1,
		.has_freq = 1,
	पूर्ण,
	[SEN_OV7648] = अणु
		.has_brightness = 1,
		.has_sat = 1,
		.has_freq = 1,
	पूर्ण,
	[SEN_OV7660] = अणु
		.has_brightness = 1,
		.has_contrast = 1,
		.has_sat = 1,
		.has_hvflip = 1,
		.has_freq = 1,
	पूर्ण,
	[SEN_OV7670] = अणु
		.has_brightness = 1,
		.has_contrast = 1,
		.has_hvflip = 1,
		.has_freq = 1,
	पूर्ण,
	[SEN_OV76BE] = अणु
		.has_brightness = 1,
		.has_contrast = 1,
		.has_sat = 1,
		.has_स्वतःbright = 1,
		.has_freq = 1,
	पूर्ण,
	[SEN_OV8610] = अणु
		.has_brightness = 1,
		.has_contrast = 1,
		.has_sat = 1,
		.has_स्वतःbright = 1,
	पूर्ण,
	[SEN_OV9600] = अणु
		.has_exposure = 1,
		.has_स्वतःgain = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat ov519_vga_mode[] = अणु
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
अटल स्थिर काष्ठा v4l2_pix_क्रमmat ov519_sअगर_mode[] = अणु
	अणु160, 120, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 160,
		.sizeimage = 160 * 120 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 3पूर्ण,
	अणु176, 144, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
	अणु320, 240, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 2पूर्ण,
	अणु352, 288, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 352 * 288 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 0पूर्ण,
पूर्ण;

/* Note some of the sizeimage values क्रम the ov511 / ov518 may seem
   larger then necessary, however they need to be this big as the ov511 /
   ov518 always fills the entire isoc frame, using 0 padding bytes when
   it करोesn't have any data. So with low framerates the amount of data
   transferred can become quite large (libv4l will हटाओ all the 0 padding
   in userspace). */
अटल स्थिर काष्ठा v4l2_pix_क्रमmat ov518_vga_mode[] = अणु
	अणु320, 240, V4L2_PIX_FMT_OV518, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
	अणु640, 480, V4L2_PIX_FMT_OV518, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480 * 2,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 0पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा v4l2_pix_क्रमmat ov518_sअगर_mode[] = अणु
	अणु160, 120, V4L2_PIX_FMT_OV518, V4L2_FIELD_NONE,
		.bytesperline = 160,
		.sizeimage = 70000,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 3पूर्ण,
	अणु176, 144, V4L2_PIX_FMT_OV518, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 70000,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
	अणु320, 240, V4L2_PIX_FMT_OV518, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 2पूर्ण,
	अणु352, 288, V4L2_PIX_FMT_OV518, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 352 * 288 * 3,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat ov511_vga_mode[] = अणु
	अणु320, 240, V4L2_PIX_FMT_OV511, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
	अणु640, 480, V4L2_PIX_FMT_OV511, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480 * 2,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 0पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा v4l2_pix_क्रमmat ov511_sअगर_mode[] = अणु
	अणु160, 120, V4L2_PIX_FMT_OV511, V4L2_FIELD_NONE,
		.bytesperline = 160,
		.sizeimage = 70000,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 3पूर्ण,
	अणु176, 144, V4L2_PIX_FMT_OV511, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 70000,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
	अणु320, 240, V4L2_PIX_FMT_OV511, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 2पूर्ण,
	अणु352, 288, V4L2_PIX_FMT_OV511, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 352 * 288 * 3,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat ovfx2_ov2610_mode[] = अणु
	अणु800, 600, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 800,
		.sizeimage = 800 * 600,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1पूर्ण,
	अणु1600, 1200, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 1600,
		.sizeimage = 1600 * 1200,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
पूर्ण;
अटल स्थिर काष्ठा v4l2_pix_क्रमmat ovfx2_ov3610_mode[] = अणु
	अणु640, 480, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1पूर्ण,
	अणु800, 600, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 800,
		.sizeimage = 800 * 600,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1पूर्ण,
	अणु1024, 768, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 1024,
		.sizeimage = 1024 * 768,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1पूर्ण,
	अणु1600, 1200, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 1600,
		.sizeimage = 1600 * 1200,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
	अणु2048, 1536, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 2048,
		.sizeimage = 2048 * 1536,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा v4l2_pix_क्रमmat ovfx2_ov9600_mode[] = अणु
	अणु640, 480, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1पूर्ण,
	अणु1280, 1024, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 1280,
		.sizeimage = 1280 * 1024,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
पूर्ण;

/* Registers common to OV511 / OV518 */
#घोषणा R51x_FIFO_PSIZE			0x30	/* 2 bytes wide w/ OV518(+) */
#घोषणा R51x_SYS_RESET			0x50
	/* Reset type flags */
	#घोषणा	OV511_RESET_OMNICE	0x08
#घोषणा R51x_SYS_INIT			0x53
#घोषणा R51x_SYS_SNAP			0x52
#घोषणा R51x_SYS_CUST_ID		0x5f
#घोषणा R51x_COMP_LUT_BEGIN		0x80

/* OV511 Camera पूर्णांकerface रेजिस्टर numbers */
#घोषणा R511_CAM_DELAY			0x10
#घोषणा R511_CAM_EDGE			0x11
#घोषणा R511_CAM_PXCNT			0x12
#घोषणा R511_CAM_LNCNT			0x13
#घोषणा R511_CAM_PXDIV			0x14
#घोषणा R511_CAM_LNDIV			0x15
#घोषणा R511_CAM_UV_EN			0x16
#घोषणा R511_CAM_LINE_MODE		0x17
#घोषणा R511_CAM_OPTS			0x18

#घोषणा R511_SNAP_FRAME			0x19
#घोषणा R511_SNAP_PXCNT			0x1a
#घोषणा R511_SNAP_LNCNT			0x1b
#घोषणा R511_SNAP_PXDIV			0x1c
#घोषणा R511_SNAP_LNDIV			0x1d
#घोषणा R511_SNAP_UV_EN			0x1e
#घोषणा R511_SNAP_OPTS			0x1f

#घोषणा R511_DRAM_FLOW_CTL		0x20
#घोषणा R511_FIFO_OPTS			0x31
#घोषणा R511_I2C_CTL			0x40
#घोषणा R511_SYS_LED_CTL		0x55	/* OV511+ only */
#घोषणा R511_COMP_EN			0x78
#घोषणा R511_COMP_LUT_EN		0x79

/* OV518 Camera पूर्णांकerface रेजिस्टर numbers */
#घोषणा R518_GPIO_OUT			0x56	/* OV518(+) only */
#घोषणा R518_GPIO_CTL			0x57	/* OV518(+) only */

/* OV519 Camera पूर्णांकerface रेजिस्टर numbers */
#घोषणा OV519_R10_H_SIZE		0x10
#घोषणा OV519_R11_V_SIZE		0x11
#घोषणा OV519_R12_X_OFFSETL		0x12
#घोषणा OV519_R13_X_OFFSETH		0x13
#घोषणा OV519_R14_Y_OFFSETL		0x14
#घोषणा OV519_R15_Y_OFFSETH		0x15
#घोषणा OV519_R16_DIVIDER		0x16
#घोषणा OV519_R20_DFR			0x20
#घोषणा OV519_R25_FORMAT		0x25

/* OV519 System Controller रेजिस्टर numbers */
#घोषणा OV519_R51_RESET1		0x51
#घोषणा OV519_R54_EN_CLK1		0x54
#घोषणा OV519_R57_SNAPSHOT		0x57

#घोषणा OV519_GPIO_DATA_OUT0		0x71
#घोषणा OV519_GPIO_IO_CTRL0		0x72

/*#घोषणा OV511_ENDPOINT_ADDRESS 1	 * Isoc endpoपूर्णांक number */

/*
 * The FX2 chip करोes not give us a zero length पढ़ो at end of frame.
 * It करोes, however, give a लघु पढ़ो at the end of a frame, अगर
 * necessary, rather than run two frames together.
 *
 * By choosing the right bulk transfer size, we are guaranteed to always
 * get a लघु पढ़ो क्रम the last पढ़ो of each frame.  Frame sizes are
 * always a composite number (width * height, or a multiple) so अगर we
 * choose a prime number, we are guaranteed that the last पढ़ो of a
 * frame will be लघु.
 *
 * But it isn't that easy: the 2.6 kernel requires a multiple of 4KB,
 * otherwise EOVERFLOW "babbling" errors occur.  I have not been able
 * to figure out why.  [PMiller]
 *
 * The स्थिरant (13 * 4096) is the largest "prime enough" number less than 64KB.
 *
 * It isn't enough to know the number of bytes per frame, in हाल we
 * have data dropouts or buffer overruns (even though the FX2 द्विगुन
 * buffers, there are some pretty strict real समय स्थिरraपूर्णांकs क्रम
 * isochronous transfer क्रम larger frame sizes).
 */
/*jfm: this value करोes not work क्रम 800x600 - see isoc_init */
#घोषणा OVFX2_BULK_SIZE (13 * 4096)

/* I2C रेजिस्टरs */
#घोषणा R51x_I2C_W_SID		0x41
#घोषणा R51x_I2C_SADDR_3	0x42
#घोषणा R51x_I2C_SADDR_2	0x43
#घोषणा R51x_I2C_R_SID		0x44
#घोषणा R51x_I2C_DATA		0x45
#घोषणा R518_I2C_CTL		0x47	/* OV518(+) only */
#घोषणा OVFX2_I2C_ADDR		0x00

/* I2C ADDRESSES */
#घोषणा OV7xx0_SID   0x42
#घोषणा OV_HIRES_SID 0x60		/* OV9xxx / OV2xxx / OV3xxx */
#घोषणा OV8xx0_SID   0xa0
#घोषणा OV6xx0_SID   0xc0

/* OV7610 रेजिस्टरs */
#घोषणा OV7610_REG_GAIN		0x00	/* gain setting (5:0) */
#घोषणा OV7610_REG_BLUE		0x01	/* blue channel balance */
#घोषणा OV7610_REG_RED		0x02	/* red channel balance */
#घोषणा OV7610_REG_SAT		0x03	/* saturation */
#घोषणा OV8610_REG_HUE		0x04	/* 04 reserved */
#घोषणा OV7610_REG_CNT		0x05	/* Y contrast */
#घोषणा OV7610_REG_BRT		0x06	/* Y brightness */
#घोषणा OV7610_REG_COM_C	0x14	/* misc common regs */
#घोषणा OV7610_REG_ID_HIGH	0x1c	/* manufacturer ID MSB */
#घोषणा OV7610_REG_ID_LOW	0x1d	/* manufacturer ID LSB */
#घोषणा OV7610_REG_COM_I	0x29	/* misc settings */

/* OV7660 and OV7670 रेजिस्टरs */
#घोषणा OV7670_R00_GAIN		0x00	/* Gain lower 8 bits (rest in vref) */
#घोषणा OV7670_R01_BLUE		0x01	/* blue gain */
#घोषणा OV7670_R02_RED		0x02	/* red gain */
#घोषणा OV7670_R03_VREF		0x03	/* Pieces of GAIN, VSTART, VSTOP */
#घोषणा OV7670_R04_COM1		0x04	/* Control 1 */
/*#घोषणा OV7670_R07_AECHH	0x07	 * AEC MS 5 bits */
#घोषणा OV7670_R0C_COM3		0x0c	/* Control 3 */
#घोषणा OV7670_R0D_COM4		0x0d	/* Control 4 */
#घोषणा OV7670_R0E_COM5		0x0e	/* All "reserved" */
#घोषणा OV7670_R0F_COM6		0x0f	/* Control 6 */
#घोषणा OV7670_R10_AECH		0x10	/* More bits of AEC value */
#घोषणा OV7670_R11_CLKRC	0x11	/* Clock control */
#घोषणा OV7670_R12_COM7		0x12	/* Control 7 */
#घोषणा   OV7670_COM7_FMT_VGA	 0x00
/*#घोषणा   OV7670_COM7_YUV	 0x00	 * YUV */
#घोषणा   OV7670_COM7_FMT_QVGA	 0x10	/* QVGA क्रमmat */
#घोषणा   OV7670_COM7_FMT_MASK	 0x38
#घोषणा   OV7670_COM7_RESET	 0x80	/* Register reset */
#घोषणा OV7670_R13_COM8		0x13	/* Control 8 */
#घोषणा   OV7670_COM8_AEC	 0x01	/* Auto exposure enable */
#घोषणा   OV7670_COM8_AWB	 0x02	/* White balance enable */
#घोषणा   OV7670_COM8_AGC	 0x04	/* Auto gain enable */
#घोषणा   OV7670_COM8_BFILT	 0x20	/* Band filter enable */
#घोषणा   OV7670_COM8_AECSTEP	 0x40	/* Unlimited AEC step size */
#घोषणा   OV7670_COM8_FASTAEC	 0x80	/* Enable fast AGC/AEC */
#घोषणा OV7670_R14_COM9		0x14	/* Control 9 - gain उच्चमानing */
#घोषणा OV7670_R15_COM10	0x15	/* Control 10 */
#घोषणा OV7670_R17_HSTART	0x17	/* Horiz start high bits */
#घोषणा OV7670_R18_HSTOP	0x18	/* Horiz stop high bits */
#घोषणा OV7670_R19_VSTART	0x19	/* Vert start high bits */
#घोषणा OV7670_R1A_VSTOP	0x1a	/* Vert stop high bits */
#घोषणा OV7670_R1E_MVFP		0x1e	/* Mirror / vflip */
#घोषणा   OV7670_MVFP_VFLIP	 0x10	/* vertical flip */
#घोषणा   OV7670_MVFP_MIRROR	 0x20	/* Mirror image */
#घोषणा OV7670_R24_AEW		0x24	/* AGC upper limit */
#घोषणा OV7670_R25_AEB		0x25	/* AGC lower limit */
#घोषणा OV7670_R26_VPT		0x26	/* AGC/AEC fast mode op region */
#घोषणा OV7670_R32_HREF		0x32	/* HREF pieces */
#घोषणा OV7670_R3A_TSLB		0x3a	/* lots of stuff */
#घोषणा OV7670_R3B_COM11	0x3b	/* Control 11 */
#घोषणा   OV7670_COM11_EXP	 0x02
#घोषणा   OV7670_COM11_HZAUTO	 0x10	/* Auto detect 50/60 Hz */
#घोषणा OV7670_R3C_COM12	0x3c	/* Control 12 */
#घोषणा OV7670_R3D_COM13	0x3d	/* Control 13 */
#घोषणा   OV7670_COM13_GAMMA	 0x80	/* Gamma enable */
#घोषणा   OV7670_COM13_UVSAT	 0x40	/* UV saturation स्वतः adjusपंचांगent */
#घोषणा OV7670_R3E_COM14	0x3e	/* Control 14 */
#घोषणा OV7670_R3F_EDGE		0x3f	/* Edge enhancement factor */
#घोषणा OV7670_R40_COM15	0x40	/* Control 15 */
/*#घोषणा   OV7670_COM15_R00FF	 0xc0	 *	00 to FF */
#घोषणा OV7670_R41_COM16	0x41	/* Control 16 */
#घोषणा   OV7670_COM16_AWBGAIN	 0x08	/* AWB gain enable */
/* end of ov7660 common रेजिस्टरs */
#घोषणा OV7670_R55_BRIGHT	0x55	/* Brightness */
#घोषणा OV7670_R56_CONTRAS	0x56	/* Contrast control */
#घोषणा OV7670_R69_GFIX		0x69	/* Fix gain control */
/*#घोषणा OV7670_R8C_RGB444	0x8c	 * RGB 444 control */
#घोषणा OV7670_R9F_HAECC1	0x9f	/* Hist AEC/AGC control 1 */
#घोषणा OV7670_RA0_HAECC2	0xa0	/* Hist AEC/AGC control 2 */
#घोषणा OV7670_RA5_BD50MAX	0xa5	/* 50hz banding step limit */
#घोषणा OV7670_RA6_HAECC3	0xa6	/* Hist AEC/AGC control 3 */
#घोषणा OV7670_RA7_HAECC4	0xa7	/* Hist AEC/AGC control 4 */
#घोषणा OV7670_RA8_HAECC5	0xa8	/* Hist AEC/AGC control 5 */
#घोषणा OV7670_RA9_HAECC6	0xa9	/* Hist AEC/AGC control 6 */
#घोषणा OV7670_RAA_HAECC7	0xaa	/* Hist AEC/AGC control 7 */
#घोषणा OV7670_RAB_BD60MAX	0xab	/* 60hz banding step limit */

काष्ठा ov_regvals अणु
	u8 reg;
	u8 val;
पूर्ण;
काष्ठा ov_i2c_regvals अणु
	u8 reg;
	u8 val;
पूर्ण;

/* Settings क्रम OV2610 camera chip */
अटल स्थिर काष्ठा ov_i2c_regvals norm_2610[] = अणु
	अणु 0x12, 0x80 पूर्ण,	/* reset */
पूर्ण;

अटल स्थिर काष्ठा ov_i2c_regvals norm_2610ae[] = अणु
	अणु0x12, 0x80पूर्ण,	/* reset */
	अणु0x13, 0xcdपूर्ण,
	अणु0x09, 0x01पूर्ण,
	अणु0x0d, 0x00पूर्ण,
	अणु0x11, 0x80पूर्ण,
	अणु0x12, 0x20पूर्ण,	/* 1600x1200 */
	अणु0x33, 0x0cपूर्ण,
	अणु0x35, 0x90पूर्ण,
	अणु0x36, 0x37पूर्ण,
/* ms-win traces */
	अणु0x11, 0x83पूर्ण,	/* घड़ी / 3 ? */
	अणु0x2d, 0x00पूर्ण,	/* 60 Hz filter */
	अणु0x24, 0xb0पूर्ण,	/* normal colors */
	अणु0x25, 0x90पूर्ण,
	अणु0x10, 0x43पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov_i2c_regvals norm_3620b[] = अणु
	/*
	 * From the datasheet: "Note that after writing to रेजिस्टर COMH
	 * (0x12) to change the sensor mode, रेजिस्टरs related to the
	 * sensorै s cropping winकरोw will be reset back to their शेष
	 * values."
	 *
	 * "रुको 4096 बाह्यal घड़ी ... to make sure the sensor is
	 * stable and पढ़ोy to access रेजिस्टरs" i.e. 160us at 24MHz
	 */
	अणु 0x12, 0x80 पूर्ण, /* COMH reset */
	अणु 0x12, 0x00 पूर्ण, /* QXGA, master */

	/*
	 * 11 CLKRC "Clock Rate Control"
	 * [7] पूर्णांकernal frequency द्विगुनrs: on
	 * [6] video port mode: master
	 * [5:0] घड़ी भागider: 1
	 */
	अणु 0x11, 0x80 पूर्ण,

	/*
	 * 13 COMI "Common Control I"
	 *                  = 192 (0xC0) 11000000
	 *    COMI[7] "AEC speed selection"
	 *                  =   1 (0x01) 1....... "Faster AEC correction"
	 *    COMI[6] "AEC speed step selection"
	 *                  =   1 (0x01) .1...... "Big steps, fast"
	 *    COMI[5] "Banding filter on off"
	 *                  =   0 (0x00) ..0..... "Off"
	 *    COMI[4] "Banding filter option"
	 *                  =   0 (0x00) ...0.... "Main घड़ी is 48 MHz and
	 *                                         the PLL is ON"
	 *    COMI[3] "Reserved"
	 *                  =   0 (0x00) ....0...
	 *    COMI[2] "AGC auto manual control selection"
	 *                  =   0 (0x00) .....0.. "Manual"
	 *    COMI[1] "AWB auto manual control selection"
	 *                  =   0 (0x00) ......0. "Manual"
	 *    COMI[0] "Exposure control"
	 *                  =   0 (0x00) .......0 "Manual"
	 */
	अणु 0x13, 0xc0 पूर्ण,

	/*
	 * 09 COMC "Common Control C"
	 *                  =   8 (0x08) 00001000
	 *    COMC[7:5] "Reserved"
	 *                  =   0 (0x00) 000.....
	 *    COMC[4] "Sleep Mode Enable"
	 *                  =   0 (0x00) ...0.... "Normal mode"
	 *    COMC[3:2] "Sensor sampling reset timing selection"
	 *                  =   2 (0x02) ....10.. "Longer reset time"
	 *    COMC[1:0] "Output drive current select"
	 *                  =   0 (0x00) ......00 "Weakest"
	 */
	अणु 0x09, 0x08 पूर्ण,

	/*
	 * 0C COMD "Common Control D"
	 *                  =   8 (0x08) 00001000
	 *    COMD[7] "Reserved"
	 *                  =   0 (0x00) 0.......
	 *    COMD[6] "Swap MSB and LSB at the output port"
	 *                  =   0 (0x00) .0...... "False"
	 *    COMD[5:3] "Reserved"
	 *                  =   1 (0x01) ..001...
	 *    COMD[2] "Output Average On Off"
	 *                  =   0 (0x00) .....0.. "Output Normal"
	 *    COMD[1] "Sensor precharge voltage selection"
	 *                  =   0 (0x00) ......0. "Selects पूर्णांकernal
	 *                                         reference preअक्षरge
	 *                                         voltage"
	 *    COMD[0] "Snapshot option"
	 *                  =   0 (0x00) .......0 "Enable live video output
	 *                                         after snapshot sequence"
	 */
	अणु 0x0c, 0x08 पूर्ण,

	/*
	 * 0D COME "Common Control E"
	 *                  = 161 (0xA1) 10100001
	 *    COME[7] "Output average option"
	 *                  =   1 (0x01) 1....... "Output average of 4 pixels"
	 *    COME[6] "Anti-blooming control"
	 *                  =   0 (0x00) .0...... "Off"
	 *    COME[5:3] "Reserved"
	 *                  =   4 (0x04) ..100...
	 *    COME[2] "Clock output power down pin status"
	 *                  =   0 (0x00) .....0.. "Tri-state data output pin
	 *                                         on घातer करोwn"
	 *    COME[1] "Data output pin status selection at power down"
	 *                  =   0 (0x00) ......0. "Tri-state VSYNC, PCLK,
	 *                                         HREF, and CHSYNC pins on
	 *                                         घातer करोwn"
	 *    COME[0] "Auto zero circuit select"
	 *                  =   1 (0x01) .......1 "On"
	 */
	अणु 0x0d, 0xa1 पूर्ण,

	/*
	 * 0E COMF "Common Control F"
	 *                  = 112 (0x70) 01110000
	 *    COMF[7] "System clock selection"
	 *                  =   0 (0x00) 0....... "Use 24 MHz system clock"
	 *    COMF[6:4] "Reserved"
	 *                  =   7 (0x07) .111....
	 *    COMF[3] "Manual auto negative offset canceling selection"
	 *                  =   0 (0x00) ....0... "Auto detect negative
	 *                                         offset and cancel it"
	 *    COMF[2:0] "Reserved"
	 *                  =   0 (0x00) .....000
	 */
	अणु 0x0e, 0x70 पूर्ण,

	/*
	 * 0F COMG "Common Control G"
	 *                  =  66 (0x42) 01000010
	 *    COMG[7] "Optical black output selection"
	 *                  =   0 (0x00) 0....... "Disable"
	 *    COMG[6] "Black level calibrate selection"
	 *                  =   1 (0x01) .1...... "Use optical black pixels
	 *                                         to calibrate"
	 *    COMG[5:4] "Reserved"
	 *                  =   0 (0x00) ..00....
	 *    COMG[3] "Channel offset adjustment"
	 *                  =   0 (0x00) ....0... "Disable offset adjustment"
	 *    COMG[2] "ADC black level calibration option"
	 *                  =   0 (0x00) .....0.. "Use B/G line and G/R
	 *                                         line to calibrate each
	 *                                         channel's black level"
	 *    COMG[1] "Reserved"
	 *                  =   1 (0x01) ......1.
	 *    COMG[0] "ADC black level calibration enable"
	 *                  =   0 (0x00) .......0 "Disable"
	 */
	अणु 0x0f, 0x42 पूर्ण,

	/*
	 * 14 COMJ "Common Control J"
	 *                  = 198 (0xC6) 11000110
	 *    COMJ[7:6] "AGC gain ceiling"
	 *                  =   3 (0x03) 11...... "8x"
	 *    COMJ[5:4] "Reserved"
	 *                  =   0 (0x00) ..00....
	 *    COMJ[3] "Auto banding filter"
	 *                  =   0 (0x00) ....0... "Banding filter is always
	 *                                         on off depending on
	 *                                         COMI[5] setting"
	 *    COMJ[2] "VSYNC drop option"
	 *                  =   1 (0x01) .....1.. "SYNC is dropped अगर frame
	 *                                         data is dropped"
	 *    COMJ[1] "Frame data drop"
	 *                  =   1 (0x01) ......1. "Drop frame data अगर
	 *                                         exposure is not within
	 *                                         tolerance.  In AEC mode,
	 *                                         data is normally dropped
	 *                                         when data is out of
	 *                                         range."
	 *    COMJ[0] "Reserved"
	 *                  =   0 (0x00) .......0
	 */
	अणु 0x14, 0xc6 पूर्ण,

	/*
	 * 15 COMK "Common Control K"
	 *                  =   2 (0x02) 00000010
	 *    COMK[7] "CHSYNC pin output swap"
	 *                  =   0 (0x00) 0....... "CHSYNC"
	 *    COMK[6] "HREF pin output swap"
	 *                  =   0 (0x00) .0...... "HREF"
	 *    COMK[5] "PCLK output selection"
	 *                  =   0 (0x00) ..0..... "PCLK always output"
	 *    COMK[4] "PCLK edge selection"
	 *                  =   0 (0x00) ...0.... "Data valid on falling edge"
	 *    COMK[3] "HREF output polarity"
	 *                  =   0 (0x00) ....0... "positive"
	 *    COMK[2] "Reserved"
	 *                  =   0 (0x00) .....0..
	 *    COMK[1] "VSYNC polarity"
	 *                  =   1 (0x01) ......1. "negative"
	 *    COMK[0] "HSYNC polarity"
	 *                  =   0 (0x00) .......0 "positive"
	 */
	अणु 0x15, 0x02 पूर्ण,

	/*
	 * 33 CHLF "Current Control"
	 *                  =   9 (0x09) 00001001
	 *    CHLF[7:6] "Sensor current control"
	 *                  =   0 (0x00) 00......
	 *    CHLF[5] "Sensor current range control"
	 *                  =   0 (0x00) ..0..... "normal range"
	 *    CHLF[4] "Sensor current"
	 *                  =   0 (0x00) ...0.... "normal current"
	 *    CHLF[3] "Sensor buffer current control"
	 *                  =   1 (0x01) ....1... "half current"
	 *    CHLF[2] "Column buffer current control"
	 *                  =   0 (0x00) .....0.. "normal current"
	 *    CHLF[1] "Analog DSP current control"
	 *                  =   0 (0x00) ......0. "normal current"
	 *    CHLF[1] "ADC current control"
	 *                  =   0 (0x00) ......0. "normal current"
	 */
	अणु 0x33, 0x09 पूर्ण,

	/*
	 * 34 VBLM "Blooming Control"
	 *                  =  80 (0x50) 01010000
	 *    VBLM[7] "Hard soft reset switch"
	 *                  =   0 (0x00) 0....... "Hard reset"
	 *    VBLM[6:4] "Blooming voltage selection"
	 *                  =   5 (0x05) .101....
	 *    VBLM[3:0] "Sensor current control"
	 *                  =   0 (0x00) ....0000
	 */
	अणु 0x34, 0x50 पूर्ण,

	/*
	 * 36 VCHG "Sensor Precharge Voltage Control"
	 *                  =   0 (0x00) 00000000
	 *    VCHG[7] "Reserved"
	 *                  =   0 (0x00) 0.......
	 *    VCHG[6:4] "Sensor precharge voltage control"
	 *                  =   0 (0x00) .000....
	 *    VCHG[3:0] "Sensor array common reference"
	 *                  =   0 (0x00) ....0000
	 */
	अणु 0x36, 0x00 पूर्ण,

	/*
	 * 37 ADC "ADC Reference Control"
	 *                  =   4 (0x04) 00000100
	 *    ADC[7:4] "Reserved"
	 *                  =   0 (0x00) 0000....
	 *    ADC[3] "ADC input signal range"
	 *                  =   0 (0x00) ....0... "Input signal 1.0x"
	 *    ADC[2:0] "ADC range control"
	 *                  =   4 (0x04) .....100
	 */
	अणु 0x37, 0x04 पूर्ण,

	/*
	 * 38 ACOM "Analog Common Ground"
	 *                  =  82 (0x52) 01010010
	 *    ACOM[7] "Analog gain control"
	 *                  =   0 (0x00) 0....... "Gain 1x"
	 *    ACOM[6] "Analog black level calibration"
	 *                  =   1 (0x01) .1...... "On"
	 *    ACOM[5:0] "Reserved"
	 *                  =  18 (0x12) ..010010
	 */
	अणु 0x38, 0x52 पूर्ण,

	/*
	 * 3A FREFA "Internal Reference Adjustment"
	 *                  =   0 (0x00) 00000000
	 *    FREFA[7:0] "Range"
	 *                  =   0 (0x00) 00000000
	 */
	अणु 0x3a, 0x00 पूर्ण,

	/*
	 * 3C FVOPT "Internal Reference Adjustment"
	 *                  =  31 (0x1F) 00011111
	 *    FVOPT[7:0] "Range"
	 *                  =  31 (0x1F) 00011111
	 */
	अणु 0x3c, 0x1f पूर्ण,

	/*
	 * 44 Unकरोcumented  =   0 (0x00) 00000000
	 *    44[7:0] "It's a secret"
	 *                  =   0 (0x00) 00000000
	 */
	अणु 0x44, 0x00 पूर्ण,

	/*
	 * 40 Unकरोcumented  =   0 (0x00) 00000000
	 *    40[7:0] "It's a secret"
	 *                  =   0 (0x00) 00000000
	 */
	अणु 0x40, 0x00 पूर्ण,

	/*
	 * 41 Unकरोcumented  =   0 (0x00) 00000000
	 *    41[7:0] "It's a secret"
	 *                  =   0 (0x00) 00000000
	 */
	अणु 0x41, 0x00 पूर्ण,

	/*
	 * 42 Unकरोcumented  =   0 (0x00) 00000000
	 *    42[7:0] "It's a secret"
	 *                  =   0 (0x00) 00000000
	 */
	अणु 0x42, 0x00 पूर्ण,

	/*
	 * 43 Unकरोcumented  =   0 (0x00) 00000000
	 *    43[7:0] "It's a secret"
	 *                  =   0 (0x00) 00000000
	 */
	अणु 0x43, 0x00 पूर्ण,

	/*
	 * 45 Unकरोcumented  = 128 (0x80) 10000000
	 *    45[7:0] "It's a secret"
	 *                  = 128 (0x80) 10000000
	 */
	अणु 0x45, 0x80 पूर्ण,

	/*
	 * 48 Unकरोcumented  = 192 (0xC0) 11000000
	 *    48[7:0] "It's a secret"
	 *                  = 192 (0xC0) 11000000
	 */
	अणु 0x48, 0xc0 पूर्ण,

	/*
	 * 49 Unकरोcumented  =  25 (0x19) 00011001
	 *    49[7:0] "It's a secret"
	 *                  =  25 (0x19) 00011001
	 */
	अणु 0x49, 0x19 पूर्ण,

	/*
	 * 4B Unकरोcumented  = 128 (0x80) 10000000
	 *    4B[7:0] "It's a secret"
	 *                  = 128 (0x80) 10000000
	 */
	अणु 0x4b, 0x80 पूर्ण,

	/*
	 * 4D Unकरोcumented  = 196 (0xC4) 11000100
	 *    4D[7:0] "It's a secret"
	 *                  = 196 (0xC4) 11000100
	 */
	अणु 0x4d, 0xc4 पूर्ण,

	/*
	 * 35 VREF "Reference Voltage Control"
	 *                  =  76 (0x4c) 01001100
	 *    VREF[7:5] "Column high reference control"
	 *                  =   2 (0x02) 010..... "higher voltage"
	 *    VREF[4:2] "Column low reference control"
	 *                  =   3 (0x03) ...011.. "Highest voltage"
	 *    VREF[1:0] "Reserved"
	 *                  =   0 (0x00) ......00
	 */
	अणु 0x35, 0x4c पूर्ण,

	/*
	 * 3D Unकरोcumented  =   0 (0x00) 00000000
	 *    3D[7:0] "It's a secret"
	 *                  =   0 (0x00) 00000000
	 */
	अणु 0x3d, 0x00 पूर्ण,

	/*
	 * 3E Unकरोcumented  =   0 (0x00) 00000000
	 *    3E[7:0] "It's a secret"
	 *                  =   0 (0x00) 00000000
	 */
	अणु 0x3e, 0x00 पूर्ण,

	/*
	 * 3B FREFB "Internal Reference Adjustment"
	 *                  =  24 (0x18) 00011000
	 *    FREFB[7:0] "Range"
	 *                  =  24 (0x18) 00011000
	 */
	अणु 0x3b, 0x18 पूर्ण,

	/*
	 * 33 CHLF "Current Control"
	 *                  =  25 (0x19) 00011001
	 *    CHLF[7:6] "Sensor current control"
	 *                  =   0 (0x00) 00......
	 *    CHLF[5] "Sensor current range control"
	 *                  =   0 (0x00) ..0..... "normal range"
	 *    CHLF[4] "Sensor current"
	 *                  =   1 (0x01) ...1.... "double current"
	 *    CHLF[3] "Sensor buffer current control"
	 *                  =   1 (0x01) ....1... "half current"
	 *    CHLF[2] "Column buffer current control"
	 *                  =   0 (0x00) .....0.. "normal current"
	 *    CHLF[1] "Analog DSP current control"
	 *                  =   0 (0x00) ......0. "normal current"
	 *    CHLF[1] "ADC current control"
	 *                  =   0 (0x00) ......0. "normal current"
	 */
	अणु 0x33, 0x19 पूर्ण,

	/*
	 * 34 VBLM "Blooming Control"
	 *                  =  90 (0x5A) 01011010
	 *    VBLM[7] "Hard soft reset switch"
	 *                  =   0 (0x00) 0....... "Hard reset"
	 *    VBLM[6:4] "Blooming voltage selection"
	 *                  =   5 (0x05) .101....
	 *    VBLM[3:0] "Sensor current control"
	 *                  =  10 (0x0A) ....1010
	 */
	अणु 0x34, 0x5a पूर्ण,

	/*
	 * 3B FREFB "Internal Reference Adjustment"
	 *                  =   0 (0x00) 00000000
	 *    FREFB[7:0] "Range"
	 *                  =   0 (0x00) 00000000
	 */
	अणु 0x3b, 0x00 पूर्ण,

	/*
	 * 33 CHLF "Current Control"
	 *                  =   9 (0x09) 00001001
	 *    CHLF[7:6] "Sensor current control"
	 *                  =   0 (0x00) 00......
	 *    CHLF[5] "Sensor current range control"
	 *                  =   0 (0x00) ..0..... "normal range"
	 *    CHLF[4] "Sensor current"
	 *                  =   0 (0x00) ...0.... "normal current"
	 *    CHLF[3] "Sensor buffer current control"
	 *                  =   1 (0x01) ....1... "half current"
	 *    CHLF[2] "Column buffer current control"
	 *                  =   0 (0x00) .....0.. "normal current"
	 *    CHLF[1] "Analog DSP current control"
	 *                  =   0 (0x00) ......0. "normal current"
	 *    CHLF[1] "ADC current control"
	 *                  =   0 (0x00) ......0. "normal current"
	 */
	अणु 0x33, 0x09 पूर्ण,

	/*
	 * 34 VBLM "Blooming Control"
	 *                  =  80 (0x50) 01010000
	 *    VBLM[7] "Hard soft reset switch"
	 *                  =   0 (0x00) 0....... "Hard reset"
	 *    VBLM[6:4] "Blooming voltage selection"
	 *                  =   5 (0x05) .101....
	 *    VBLM[3:0] "Sensor current control"
	 *                  =   0 (0x00) ....0000
	 */
	अणु 0x34, 0x50 पूर्ण,

	/*
	 * 12 COMH "Common Control H"
	 *                  =  64 (0x40) 01000000
	 *    COMH[7] "SRST"
	 *                  =   0 (0x00) 0....... "No-op"
	 *    COMH[6:4] "Resolution selection"
	 *                  =   4 (0x04) .100.... "XGA"
	 *    COMH[3] "Master slave selection"
	 *                  =   0 (0x00) ....0... "Master mode"
	 *    COMH[2] "Internal B/R channel option"
	 *                  =   0 (0x00) .....0.. "B/R use same channel"
	 *    COMH[1] "Color bar test pattern"
	 *                  =   0 (0x00) ......0. "Off"
	 *    COMH[0] "Reserved"
	 *                  =   0 (0x00) .......0
	 */
	अणु 0x12, 0x40 पूर्ण,

	/*
	 * 17 HREFST "Horizontal window start"
	 *                  =  31 (0x1F) 00011111
	 *    HREFST[7:0] "Horizontal window start, 8 MSBs"
	 *                  =  31 (0x1F) 00011111
	 */
	अणु 0x17, 0x1f पूर्ण,

	/*
	 * 18 HREFEND "Horizontal window end"
	 *                  =  95 (0x5F) 01011111
	 *    HREFEND[7:0] "Horizontal Window End, 8 MSBs"
	 *                  =  95 (0x5F) 01011111
	 */
	अणु 0x18, 0x5f पूर्ण,

	/*
	 * 19 VSTRT "Vertical window start"
	 *                  =   0 (0x00) 00000000
	 *    VSTRT[7:0] "Vertical Window Start, 8 MSBs"
	 *                  =   0 (0x00) 00000000
	 */
	अणु 0x19, 0x00 पूर्ण,

	/*
	 * 1A VEND "Vertical window end"
	 *                  =  96 (0x60) 01100000
	 *    VEND[7:0] "Vertical Window End, 8 MSBs"
	 *                  =  96 (0x60) 01100000
	 */
	अणु 0x1a, 0x60 पूर्ण,

	/*
	 * 32 COMM "Common Control M"
	 *                  =  18 (0x12) 00010010
	 *    COMM[7:6] "Pixel clock divide option"
	 *                  =   0 (0x00) 00...... "/1"
	 *    COMM[5:3] "Horizontal window end position, 3 LSBs"
	 *                  =   2 (0x02) ..010...
	 *    COMM[2:0] "Horizontal window start position, 3 LSBs"
	 *                  =   2 (0x02) .....010
	 */
	अणु 0x32, 0x12 पूर्ण,

	/*
	 * 03 COMA "Common Control A"
	 *                  =  74 (0x4A) 01001010
	 *    COMA[7:4] "AWB Update Threshold"
	 *                  =   4 (0x04) 0100....
	 *    COMA[3:2] "Vertical window end line control 2 LSBs"
	 *                  =   2 (0x02) ....10..
	 *    COMA[1:0] "Vertical window start line control 2 LSBs"
	 *                  =   2 (0x02) ......10
	 */
	अणु 0x03, 0x4a पूर्ण,

	/*
	 * 11 CLKRC "Clock Rate Control"
	 *                  = 128 (0x80) 10000000
	 *    CLKRC[7] "Internal frequency doublers on off seclection"
	 *                  =   1 (0x01) 1....... "On"
	 *    CLKRC[6] "Digital video master slave selection"
	 *                  =   0 (0x00) .0...... "Master mode, sensor
	 *                                         provides PCLK"
	 *    CLKRC[5:0] "Clock divider { CLK = PCLK/(1+CLKRC[5:0]) }"
	 *                  =   0 (0x00) ..000000
	 */
	अणु 0x11, 0x80 पूर्ण,

	/*
	 * 12 COMH "Common Control H"
	 *                  =   0 (0x00) 00000000
	 *    COMH[7] "SRST"
	 *                  =   0 (0x00) 0....... "No-op"
	 *    COMH[6:4] "Resolution selection"
	 *                  =   0 (0x00) .000.... "QXGA"
	 *    COMH[3] "Master slave selection"
	 *                  =   0 (0x00) ....0... "Master mode"
	 *    COMH[2] "Internal B/R channel option"
	 *                  =   0 (0x00) .....0.. "B/R use same channel"
	 *    COMH[1] "Color bar test pattern"
	 *                  =   0 (0x00) ......0. "Off"
	 *    COMH[0] "Reserved"
	 *                  =   0 (0x00) .......0
	 */
	अणु 0x12, 0x00 पूर्ण,

	/*
	 * 12 COMH "Common Control H"
	 *                  =  64 (0x40) 01000000
	 *    COMH[7] "SRST"
	 *                  =   0 (0x00) 0....... "No-op"
	 *    COMH[6:4] "Resolution selection"
	 *                  =   4 (0x04) .100.... "XGA"
	 *    COMH[3] "Master slave selection"
	 *                  =   0 (0x00) ....0... "Master mode"
	 *    COMH[2] "Internal B/R channel option"
	 *                  =   0 (0x00) .....0.. "B/R use same channel"
	 *    COMH[1] "Color bar test pattern"
	 *                  =   0 (0x00) ......0. "Off"
	 *    COMH[0] "Reserved"
	 *                  =   0 (0x00) .......0
	 */
	अणु 0x12, 0x40 पूर्ण,

	/*
	 * 17 HREFST "Horizontal window start"
	 *                  =  31 (0x1F) 00011111
	 *    HREFST[7:0] "Horizontal window start, 8 MSBs"
	 *                  =  31 (0x1F) 00011111
	 */
	अणु 0x17, 0x1f पूर्ण,

	/*
	 * 18 HREFEND "Horizontal window end"
	 *                  =  95 (0x5F) 01011111
	 *    HREFEND[7:0] "Horizontal Window End, 8 MSBs"
	 *                  =  95 (0x5F) 01011111
	 */
	अणु 0x18, 0x5f पूर्ण,

	/*
	 * 19 VSTRT "Vertical window start"
	 *                  =   0 (0x00) 00000000
	 *    VSTRT[7:0] "Vertical Window Start, 8 MSBs"
	 *                  =   0 (0x00) 00000000
	 */
	अणु 0x19, 0x00 पूर्ण,

	/*
	 * 1A VEND "Vertical window end"
	 *                  =  96 (0x60) 01100000
	 *    VEND[7:0] "Vertical Window End, 8 MSBs"
	 *                  =  96 (0x60) 01100000
	 */
	अणु 0x1a, 0x60 पूर्ण,

	/*
	 * 32 COMM "Common Control M"
	 *                  =  18 (0x12) 00010010
	 *    COMM[7:6] "Pixel clock divide option"
	 *                  =   0 (0x00) 00...... "/1"
	 *    COMM[5:3] "Horizontal window end position, 3 LSBs"
	 *                  =   2 (0x02) ..010...
	 *    COMM[2:0] "Horizontal window start position, 3 LSBs"
	 *                  =   2 (0x02) .....010
	 */
	अणु 0x32, 0x12 पूर्ण,

	/*
	 * 03 COMA "Common Control A"
	 *                  =  74 (0x4A) 01001010
	 *    COMA[7:4] "AWB Update Threshold"
	 *                  =   4 (0x04) 0100....
	 *    COMA[3:2] "Vertical window end line control 2 LSBs"
	 *                  =   2 (0x02) ....10..
	 *    COMA[1:0] "Vertical window start line control 2 LSBs"
	 *                  =   2 (0x02) ......10
	 */
	अणु 0x03, 0x4a पूर्ण,

	/*
	 * 02 RED "Red Gain Control"
	 *                  = 175 (0xAF) 10101111
	 *    RED[7] "Action"
	 *                  =   1 (0x01) 1....... "gain = 1/(1+bitrev([6:0]))"
	 *    RED[6:0] "Value"
	 *                  =  47 (0x2F) .0101111
	 */
	अणु 0x02, 0xaf पूर्ण,

	/*
	 * 2D ADDVSL "VSYNC Pulse Width"
	 *                  = 210 (0xD2) 11010010
	 *    ADDVSL[7:0] "VSYNC pulse width, LSB"
	 *                  = 210 (0xD2) 11010010
	 */
	अणु 0x2d, 0xd2 पूर्ण,

	/*
	 * 00 GAIN          =  24 (0x18) 00011000
	 *    GAIN[7:6] "Reserved"
	 *                  =   0 (0x00) 00......
	 *    GAIN[5] "Double"
	 *                  =   0 (0x00) ..0..... "False"
	 *    GAIN[4] "Double"
	 *                  =   1 (0x01) ...1.... "True"
	 *    GAIN[3:0] "Range"
	 *                  =   8 (0x08) ....1000
	 */
	अणु 0x00, 0x18 पूर्ण,

	/*
	 * 01 BLUE "Blue Gain Control"
	 *                  = 240 (0xF0) 11110000
	 *    BLUE[7] "Action"
	 *                  =   1 (0x01) 1....... "gain = 1/(1+bitrev([6:0]))"
	 *    BLUE[6:0] "Value"
	 *                  = 112 (0x70) .1110000
	 */
	अणु 0x01, 0xf0 पूर्ण,

	/*
	 * 10 AEC "Automatic Exposure Control"
	 *                  =  10 (0x0A) 00001010
	 *    AEC[7:0] "Automatic Exposure Control, 8 MSBs"
	 *                  =  10 (0x0A) 00001010
	 */
	अणु 0x10, 0x0a पूर्ण,

	अणु 0xe1, 0x67 पूर्ण,
	अणु 0xe3, 0x03 पूर्ण,
	अणु 0xe4, 0x26 पूर्ण,
	अणु 0xe5, 0x3e पूर्ण,
	अणु 0xf8, 0x01 पूर्ण,
	अणु 0xff, 0x01 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov_i2c_regvals norm_6x20[] = अणु
	अणु 0x12, 0x80 पूर्ण, /* reset */
	अणु 0x11, 0x01 पूर्ण,
	अणु 0x03, 0x60 पूर्ण,
	अणु 0x05, 0x7f पूर्ण, /* For when स्वतःadjust is off */
	अणु 0x07, 0xa8 पूर्ण,
	/* The ratio of 0x0c and 0x0d controls the white poपूर्णांक */
	अणु 0x0c, 0x24 पूर्ण,
	अणु 0x0d, 0x24 पूर्ण,
	अणु 0x0f, 0x15 पूर्ण, /* COMS */
	अणु 0x10, 0x75 पूर्ण, /* AEC Exposure समय */
	अणु 0x12, 0x24 पूर्ण, /* Enable AGC */
	अणु 0x14, 0x04 पूर्ण,
	/* 0x16: 0x06 helps frame stability with moving objects */
	अणु 0x16, 0x06 पूर्ण,
/*	अणु 0x20, 0x30 पूर्ण,  * Aperture correction enable */
	अणु 0x26, 0xb2 पूर्ण, /* BLC enable */
	/* 0x28: 0x05 Selects RGB क्रमmat अगर RGB on */
	अणु 0x28, 0x05 पूर्ण,
	अणु 0x2a, 0x04 पूर्ण, /* Disable framerate adjust */
/*	अणु 0x2b, 0xac पूर्ण,  * Framerate; Set 2a[7] first */
	अणु 0x2d, 0x85 पूर्ण,
	अणु 0x33, 0xa0 पूर्ण, /* Color Processing Parameter */
	अणु 0x34, 0xd2 पूर्ण, /* Max A/D range */
	अणु 0x38, 0x8b पूर्ण,
	अणु 0x39, 0x40 पूर्ण,

	अणु 0x3c, 0x39 पूर्ण, /* Enable AEC mode changing */
	अणु 0x3c, 0x3c पूर्ण, /* Change AEC mode */
	अणु 0x3c, 0x24 पूर्ण, /* Disable AEC mode changing */

	अणु 0x3d, 0x80 पूर्ण,
	/* These next two रेजिस्टरs (0x4a, 0x4b) are unकरोcumented.
	 * They control the color balance */
	अणु 0x4a, 0x80 पूर्ण,
	अणु 0x4b, 0x80 पूर्ण,
	अणु 0x4d, 0xd2 पूर्ण, /* This reduces noise a bit */
	अणु 0x4e, 0xc1 पूर्ण,
	अणु 0x4f, 0x04 पूर्ण,
/* Do 50-53 have any effect? */
/* Toggle 0x12[2] off and on here? */
पूर्ण;

अटल स्थिर काष्ठा ov_i2c_regvals norm_6x30[] = अणु
	अणु 0x12, 0x80 पूर्ण, /* Reset */
	अणु 0x00, 0x1f पूर्ण, /* Gain */
	अणु 0x01, 0x99 पूर्ण, /* Blue gain */
	अणु 0x02, 0x7c पूर्ण, /* Red gain */
	अणु 0x03, 0xc0 पूर्ण, /* Saturation */
	अणु 0x05, 0x0a पूर्ण, /* Contrast */
	अणु 0x06, 0x95 पूर्ण, /* Brightness */
	अणु 0x07, 0x2d पूर्ण, /* Sharpness */
	अणु 0x0c, 0x20 पूर्ण,
	अणु 0x0d, 0x20 पूर्ण,
	अणु 0x0e, 0xa0 पूर्ण, /* Was 0x20, bit7 enables a 2x gain which we need */
	अणु 0x0f, 0x05 पूर्ण,
	अणु 0x10, 0x9a पूर्ण,
	अणु 0x11, 0x00 पूर्ण, /* Pixel घड़ी = fastest */
	अणु 0x12, 0x24 पूर्ण, /* Enable AGC and AWB */
	अणु 0x13, 0x21 पूर्ण,
	अणु 0x14, 0x80 पूर्ण,
	अणु 0x15, 0x01 पूर्ण,
	अणु 0x16, 0x03 पूर्ण,
	अणु 0x17, 0x38 पूर्ण,
	अणु 0x18, 0xea पूर्ण,
	अणु 0x19, 0x04 पूर्ण,
	अणु 0x1a, 0x93 पूर्ण,
	अणु 0x1b, 0x00 पूर्ण,
	अणु 0x1e, 0xc4 पूर्ण,
	अणु 0x1f, 0x04 पूर्ण,
	अणु 0x20, 0x20 पूर्ण,
	अणु 0x21, 0x10 पूर्ण,
	अणु 0x22, 0x88 पूर्ण,
	अणु 0x23, 0xc0 पूर्ण, /* Crystal circuit घातer level */
	अणु 0x25, 0x9a पूर्ण, /* Increase AEC black ratio */
	अणु 0x26, 0xb2 पूर्ण, /* BLC enable */
	अणु 0x27, 0xa2 पूर्ण,
	अणु 0x28, 0x00 पूर्ण,
	अणु 0x29, 0x00 पूर्ण,
	अणु 0x2a, 0x84 पूर्ण, /* 60 Hz घातer */
	अणु 0x2b, 0xa8 पूर्ण, /* 60 Hz घातer */
	अणु 0x2c, 0xa0 पूर्ण,
	अणु 0x2d, 0x95 पूर्ण, /* Enable स्वतः-brightness */
	अणु 0x2e, 0x88 पूर्ण,
	अणु 0x33, 0x26 पूर्ण,
	अणु 0x34, 0x03 पूर्ण,
	अणु 0x36, 0x8f पूर्ण,
	अणु 0x37, 0x80 पूर्ण,
	अणु 0x38, 0x83 पूर्ण,
	अणु 0x39, 0x80 पूर्ण,
	अणु 0x3a, 0x0f पूर्ण,
	अणु 0x3b, 0x3c पूर्ण,
	अणु 0x3c, 0x1a पूर्ण,
	अणु 0x3d, 0x80 पूर्ण,
	अणु 0x3e, 0x80 पूर्ण,
	अणु 0x3f, 0x0e पूर्ण,
	अणु 0x40, 0x00 पूर्ण, /* White bal */
	अणु 0x41, 0x00 पूर्ण, /* White bal */
	अणु 0x42, 0x80 पूर्ण,
	अणु 0x43, 0x3f पूर्ण, /* White bal */
	अणु 0x44, 0x80 पूर्ण,
	अणु 0x45, 0x20 पूर्ण,
	अणु 0x46, 0x20 पूर्ण,
	अणु 0x47, 0x80 पूर्ण,
	अणु 0x48, 0x7f पूर्ण,
	अणु 0x49, 0x00 पूर्ण,
	अणु 0x4a, 0x00 पूर्ण,
	अणु 0x4b, 0x80 पूर्ण,
	अणु 0x4c, 0xd0 पूर्ण,
	अणु 0x4d, 0x10 पूर्ण, /* U = 0.563u, V = 0.714v */
	अणु 0x4e, 0x40 पूर्ण,
	अणु 0x4f, 0x07 पूर्ण, /* UV avg., col. समाप्तer: max */
	अणु 0x50, 0xff पूर्ण,
	अणु 0x54, 0x23 पूर्ण, /* Max AGC gain: 18dB */
	अणु 0x55, 0xff पूर्ण,
	अणु 0x56, 0x12 पूर्ण,
	अणु 0x57, 0x81 पूर्ण,
	अणु 0x58, 0x75 पूर्ण,
	अणु 0x59, 0x01 पूर्ण, /* AGC dark current comp.: +1 */
	अणु 0x5a, 0x2c पूर्ण,
	अणु 0x5b, 0x0f पूर्ण, /* AWB chrominance levels */
	अणु 0x5c, 0x10 पूर्ण,
	अणु 0x3d, 0x80 पूर्ण,
	अणु 0x27, 0xa6 पूर्ण,
	अणु 0x12, 0x20 पूर्ण, /* Toggle AWB */
	अणु 0x12, 0x24 पूर्ण,
पूर्ण;

/* Lawrence Glaister <lg@jfm.bc.ca> reports:
 *
 * Register 0x0f in the 7610 has the following effects:
 *
 * 0x85 (AEC method 1): Best overall, good contrast range
 * 0x45 (AEC method 2): Very overexposed
 * 0xa5 (spec sheet शेष): Ok, but the black level is
 *	shअगरted resulting in loss of contrast
 * 0x05 (old driver setting): very overexposed, too much
 *	contrast
 */
अटल स्थिर काष्ठा ov_i2c_regvals norm_7610[] = अणु
	अणु 0x10, 0xff पूर्ण,
	अणु 0x16, 0x06 पूर्ण,
	अणु 0x28, 0x24 पूर्ण,
	अणु 0x2b, 0xac पूर्ण,
	अणु 0x12, 0x00 पूर्ण,
	अणु 0x38, 0x81 पूर्ण,
	अणु 0x28, 0x24 पूर्ण,	/* 0c */
	अणु 0x0f, 0x85 पूर्ण,	/* lg's setting */
	अणु 0x15, 0x01 पूर्ण,
	अणु 0x20, 0x1c पूर्ण,
	अणु 0x23, 0x2a पूर्ण,
	अणु 0x24, 0x10 पूर्ण,
	अणु 0x25, 0x8a पूर्ण,
	अणु 0x26, 0xa2 पूर्ण,
	अणु 0x27, 0xc2 पूर्ण,
	अणु 0x2a, 0x04 पूर्ण,
	अणु 0x2c, 0xfe पूर्ण,
	अणु 0x2d, 0x93 पूर्ण,
	अणु 0x30, 0x71 पूर्ण,
	अणु 0x31, 0x60 पूर्ण,
	अणु 0x32, 0x26 पूर्ण,
	अणु 0x33, 0x20 पूर्ण,
	अणु 0x34, 0x48 पूर्ण,
	अणु 0x12, 0x24 पूर्ण,
	अणु 0x11, 0x01 पूर्ण,
	अणु 0x0c, 0x24 पूर्ण,
	अणु 0x0d, 0x24 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov_i2c_regvals norm_7620[] = अणु
	अणु 0x12, 0x80 पूर्ण,		/* reset */
	अणु 0x00, 0x00 पूर्ण,		/* gain */
	अणु 0x01, 0x80 पूर्ण,		/* blue gain */
	अणु 0x02, 0x80 पूर्ण,		/* red gain */
	अणु 0x03, 0xc0 पूर्ण,		/* OV7670_R03_VREF */
	अणु 0x06, 0x60 पूर्ण,
	अणु 0x07, 0x00 पूर्ण,
	अणु 0x0c, 0x24 पूर्ण,
	अणु 0x0c, 0x24 पूर्ण,
	अणु 0x0d, 0x24 पूर्ण,
	अणु 0x11, 0x01 पूर्ण,
	अणु 0x12, 0x24 पूर्ण,
	अणु 0x13, 0x01 पूर्ण,
	अणु 0x14, 0x84 पूर्ण,
	अणु 0x15, 0x01 पूर्ण,
	अणु 0x16, 0x03 पूर्ण,
	अणु 0x17, 0x2f पूर्ण,
	अणु 0x18, 0xcf पूर्ण,
	अणु 0x19, 0x06 पूर्ण,
	अणु 0x1a, 0xf5 पूर्ण,
	अणु 0x1b, 0x00 पूर्ण,
	अणु 0x20, 0x18 पूर्ण,
	अणु 0x21, 0x80 पूर्ण,
	अणु 0x22, 0x80 पूर्ण,
	अणु 0x23, 0x00 पूर्ण,
	अणु 0x26, 0xa2 पूर्ण,
	अणु 0x27, 0xea पूर्ण,
	अणु 0x28, 0x22 पूर्ण, /* Was 0x20, bit1 enables a 2x gain which we need */
	अणु 0x29, 0x00 पूर्ण,
	अणु 0x2a, 0x10 पूर्ण,
	अणु 0x2b, 0x00 पूर्ण,
	अणु 0x2c, 0x88 पूर्ण,
	अणु 0x2d, 0x91 पूर्ण,
	अणु 0x2e, 0x80 पूर्ण,
	अणु 0x2f, 0x44 पूर्ण,
	अणु 0x60, 0x27 पूर्ण,
	अणु 0x61, 0x02 पूर्ण,
	अणु 0x62, 0x5f पूर्ण,
	अणु 0x63, 0xd5 पूर्ण,
	अणु 0x64, 0x57 पूर्ण,
	अणु 0x65, 0x83 पूर्ण,
	अणु 0x66, 0x55 पूर्ण,
	अणु 0x67, 0x92 पूर्ण,
	अणु 0x68, 0xcf पूर्ण,
	अणु 0x69, 0x76 पूर्ण,
	अणु 0x6a, 0x22 पूर्ण,
	अणु 0x6b, 0x00 पूर्ण,
	अणु 0x6c, 0x02 पूर्ण,
	अणु 0x6d, 0x44 पूर्ण,
	अणु 0x6e, 0x80 पूर्ण,
	अणु 0x6f, 0x1d पूर्ण,
	अणु 0x70, 0x8b पूर्ण,
	अणु 0x71, 0x00 पूर्ण,
	अणु 0x72, 0x14 पूर्ण,
	अणु 0x73, 0x54 पूर्ण,
	अणु 0x74, 0x00 पूर्ण,
	अणु 0x75, 0x8e पूर्ण,
	अणु 0x76, 0x00 पूर्ण,
	अणु 0x77, 0xff पूर्ण,
	अणु 0x78, 0x80 पूर्ण,
	अणु 0x79, 0x80 पूर्ण,
	अणु 0x7a, 0x80 पूर्ण,
	अणु 0x7b, 0xe2 पूर्ण,
	अणु 0x7c, 0x00 पूर्ण,
पूर्ण;

/* 7640 and 7648. The शेषs should be OK क्रम most रेजिस्टरs. */
अटल स्थिर काष्ठा ov_i2c_regvals norm_7640[] = अणु
	अणु 0x12, 0x80 पूर्ण,
	अणु 0x12, 0x14 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov_regvals init_519_ov7660[] = अणु
	अणु 0x5d,	0x03 पूर्ण, /* Turn off suspend mode */
	अणु 0x53,	0x9b पूर्ण, /* 0x9f enables the (unused) microcontroller */
	अणु 0x54,	0x0f पूर्ण, /* bit2 (jpeg enable) */
	अणु 0xa2,	0x20 पूर्ण, /* a2-a5 are unकरोcumented */
	अणु 0xa3,	0x18 पूर्ण,
	अणु 0xa4,	0x04 पूर्ण,
	अणु 0xa5,	0x28 पूर्ण,
	अणु 0x37,	0x00 पूर्ण,	/* SetUsbInit */
	अणु 0x55,	0x02 पूर्ण, /* 4.096 Mhz audio घड़ी */
	/* Enable both fields, YUV Input, disable defect comp (why?) */
	अणु 0x20,	0x0c पूर्ण,	/* 0x0d करोes U <-> V swap */
	अणु 0x21,	0x38 पूर्ण,
	अणु 0x22,	0x1d पूर्ण,
	अणु 0x17,	0x50 पूर्ण, /* unकरोcumented */
	अणु 0x37,	0x00 पूर्ण, /* unकरोcumented */
	अणु 0x40,	0xff पूर्ण, /* I2C समयout counter */
	अणु 0x46,	0x00 पूर्ण, /* I2C घड़ी prescaler */
पूर्ण;
अटल स्थिर काष्ठा ov_i2c_regvals norm_7660[] = अणु
	अणुOV7670_R12_COM7, OV7670_COM7_RESETपूर्ण,
	अणुOV7670_R11_CLKRC, 0x81पूर्ण,
	अणु0x92, 0x00पूर्ण,			/* DM_LNL */
	अणु0x93, 0x00पूर्ण,			/* DM_LNH */
	अणु0x9d, 0x4cपूर्ण,			/* BD50ST */
	अणु0x9e, 0x3fपूर्ण,			/* BD60ST */
	अणुOV7670_R3B_COM11, 0x02पूर्ण,
	अणुOV7670_R13_COM8, 0xf5पूर्ण,
	अणुOV7670_R10_AECH, 0x00पूर्ण,
	अणुOV7670_R00_GAIN, 0x00पूर्ण,
	अणुOV7670_R01_BLUE, 0x7cपूर्ण,
	अणुOV7670_R02_RED, 0x9dपूर्ण,
	अणुOV7670_R12_COM7, 0x00पूर्ण,
	अणुOV7670_R04_COM1, 00पूर्ण,
	अणुOV7670_R18_HSTOP, 0x01पूर्ण,
	अणुOV7670_R17_HSTART, 0x13पूर्ण,
	अणुOV7670_R32_HREF, 0x92पूर्ण,
	अणुOV7670_R19_VSTART, 0x02पूर्ण,
	अणुOV7670_R1A_VSTOP, 0x7aपूर्ण,
	अणुOV7670_R03_VREF, 0x00पूर्ण,
	अणुOV7670_R0E_COM5, 0x04पूर्ण,
	अणुOV7670_R0F_COM6, 0x62पूर्ण,
	अणुOV7670_R15_COM10, 0x00पूर्ण,
	अणु0x16, 0x02पूर्ण,			/* RSVD */
	अणु0x1b, 0x00पूर्ण,			/* PSHFT */
	अणुOV7670_R1E_MVFP, 0x01पूर्ण,
	अणु0x29, 0x3cपूर्ण,			/* RSVD */
	अणु0x33, 0x00पूर्ण,			/* CHLF */
	अणु0x34, 0x07पूर्ण,			/* ARBLM */
	अणु0x35, 0x84पूर्ण,			/* RSVD */
	अणु0x36, 0x00पूर्ण,			/* RSVD */
	अणु0x37, 0x04पूर्ण,			/* ADC */
	अणु0x39, 0x43पूर्ण,			/* OFON */
	अणुOV7670_R3A_TSLB, 0x00पूर्ण,
	अणुOV7670_R3C_COM12, 0x6cपूर्ण,
	अणुOV7670_R3D_COM13, 0x98पूर्ण,
	अणुOV7670_R3F_EDGE, 0x23पूर्ण,
	अणुOV7670_R40_COM15, 0xc1पूर्ण,
	अणुOV7670_R41_COM16, 0x22पूर्ण,
	अणु0x6b, 0x0aपूर्ण,			/* DBLV */
	अणु0xa1, 0x08पूर्ण,			/* RSVD */
	अणु0x69, 0x80पूर्ण,			/* HV */
	अणु0x43, 0xf0पूर्ण,			/* RSVD.. */
	अणु0x44, 0x10पूर्ण,
	अणु0x45, 0x78पूर्ण,
	अणु0x46, 0xa8पूर्ण,
	अणु0x47, 0x60पूर्ण,
	अणु0x48, 0x80पूर्ण,
	अणु0x59, 0xbaपूर्ण,
	अणु0x5a, 0x9aपूर्ण,
	अणु0x5b, 0x22पूर्ण,
	अणु0x5c, 0xb9पूर्ण,
	अणु0x5d, 0x9bपूर्ण,
	अणु0x5e, 0x10पूर्ण,
	अणु0x5f, 0xe0पूर्ण,
	अणु0x60, 0x85पूर्ण,
	अणु0x61, 0x60पूर्ण,
	अणु0x9f, 0x9dपूर्ण,			/* RSVD */
	अणु0xa0, 0xa0पूर्ण,			/* DSPC2 */
	अणु0x4f, 0x60पूर्ण,			/* matrix */
	अणु0x50, 0x64पूर्ण,
	अणु0x51, 0x04पूर्ण,
	अणु0x52, 0x18पूर्ण,
	अणु0x53, 0x3cपूर्ण,
	अणु0x54, 0x54पूर्ण,
	अणु0x55, 0x40पूर्ण,
	अणु0x56, 0x40पूर्ण,
	अणु0x57, 0x40पूर्ण,
	अणु0x58, 0x0dपूर्ण,			/* matrix sign */
	अणु0x8b, 0xccपूर्ण,			/* RSVD */
	अणु0x8c, 0xccपूर्ण,
	अणु0x8d, 0xcfपूर्ण,
	अणु0x6c, 0x40पूर्ण,			/* gamma curve */
	अणु0x6d, 0xe0पूर्ण,
	अणु0x6e, 0xa0पूर्ण,
	अणु0x6f, 0x80पूर्ण,
	अणु0x70, 0x70पूर्ण,
	अणु0x71, 0x80पूर्ण,
	अणु0x72, 0x60पूर्ण,
	अणु0x73, 0x60पूर्ण,
	अणु0x74, 0x50पूर्ण,
	अणु0x75, 0x40पूर्ण,
	अणु0x76, 0x38पूर्ण,
	अणु0x77, 0x3cपूर्ण,
	अणु0x78, 0x32पूर्ण,
	अणु0x79, 0x1aपूर्ण,
	अणु0x7a, 0x28पूर्ण,
	अणु0x7b, 0x24पूर्ण,
	अणु0x7c, 0x04पूर्ण,			/* gamma curve */
	अणु0x7d, 0x12पूर्ण,
	अणु0x7e, 0x26पूर्ण,
	अणु0x7f, 0x46पूर्ण,
	अणु0x80, 0x54पूर्ण,
	अणु0x81, 0x64पूर्ण,
	अणु0x82, 0x70पूर्ण,
	अणु0x83, 0x7cपूर्ण,
	अणु0x84, 0x86पूर्ण,
	अणु0x85, 0x8eपूर्ण,
	अणु0x86, 0x9cपूर्ण,
	अणु0x87, 0xabपूर्ण,
	अणु0x88, 0xc4पूर्ण,
	अणु0x89, 0xd1पूर्ण,
	अणु0x8a, 0xe5पूर्ण,
	अणुOV7670_R14_COM9, 0x1eपूर्ण,
	अणुOV7670_R24_AEW, 0x80पूर्ण,
	अणुOV7670_R25_AEB, 0x72पूर्ण,
	अणुOV7670_R26_VPT, 0xb3पूर्ण,
	अणु0x62, 0x80पूर्ण,			/* LCC1 */
	अणु0x63, 0x80पूर्ण,			/* LCC2 */
	अणु0x64, 0x06पूर्ण,			/* LCC3 */
	अणु0x65, 0x00पूर्ण,			/* LCC4 */
	अणु0x66, 0x01पूर्ण,			/* LCC5 */
	अणु0x94, 0x0eपूर्ण,			/* RSVD.. */
	अणु0x95, 0x14पूर्ण,
	अणुOV7670_R13_COM8, OV7670_COM8_FASTAEC
			| OV7670_COM8_AECSTEP
			| OV7670_COM8_BFILT
			| 0x10
			| OV7670_COM8_AGC
			| OV7670_COM8_AWB
			| OV7670_COM8_AECपूर्ण,
	अणु0xa1, 0xc8पूर्ण
पूर्ण;
अटल स्थिर काष्ठा ov_i2c_regvals norm_9600[] = अणु
	अणु0x12, 0x80पूर्ण,
	अणु0x0c, 0x28पूर्ण,
	अणु0x11, 0x80पूर्ण,
	अणु0x13, 0xb5पूर्ण,
	अणु0x14, 0x3eपूर्ण,
	अणु0x1b, 0x04पूर्ण,
	अणु0x24, 0xb0पूर्ण,
	अणु0x25, 0x90पूर्ण,
	अणु0x26, 0x94पूर्ण,
	अणु0x35, 0x90पूर्ण,
	अणु0x37, 0x07पूर्ण,
	अणु0x38, 0x08पूर्ण,
	अणु0x01, 0x8eपूर्ण,
	अणु0x02, 0x85पूर्ण
पूर्ण;

/* 7670. Defaults taken from OmniVision provided data,
*  as provided by Jonathan Corbet of OLPC		*/
अटल स्थिर काष्ठा ov_i2c_regvals norm_7670[] = अणु
	अणु OV7670_R12_COM7, OV7670_COM7_RESET पूर्ण,
	अणु OV7670_R3A_TSLB, 0x04 पूर्ण,		/* OV */
	अणु OV7670_R12_COM7, OV7670_COM7_FMT_VGA पूर्ण, /* VGA */
	अणु OV7670_R11_CLKRC, 0x01 पूर्ण,
/*
 * Set the hardware winकरोw.  These values from OV करोn't entirely
 * make sense - hstop is less than hstart.  But they work...
 */
	अणु OV7670_R17_HSTART, 0x13 पूर्ण,
	अणु OV7670_R18_HSTOP, 0x01 पूर्ण,
	अणु OV7670_R32_HREF, 0xb6 पूर्ण,
	अणु OV7670_R19_VSTART, 0x02 पूर्ण,
	अणु OV7670_R1A_VSTOP, 0x7a पूर्ण,
	अणु OV7670_R03_VREF, 0x0a पूर्ण,

	अणु OV7670_R0C_COM3, 0x00 पूर्ण,
	अणु OV7670_R3E_COM14, 0x00 पूर्ण,
/* Mystery scaling numbers */
	अणु 0x70, 0x3a पूर्ण,
	अणु 0x71, 0x35 पूर्ण,
	अणु 0x72, 0x11 पूर्ण,
	अणु 0x73, 0xf0 पूर्ण,
	अणु 0xa2, 0x02 पूर्ण,
/*	अणु OV7670_R15_COM10, 0x0 पूर्ण, */

/* Gamma curve values */
	अणु 0x7a, 0x20 पूर्ण,
	अणु 0x7b, 0x10 पूर्ण,
	अणु 0x7c, 0x1e पूर्ण,
	अणु 0x7d, 0x35 पूर्ण,
	अणु 0x7e, 0x5a पूर्ण,
	अणु 0x7f, 0x69 पूर्ण,
	अणु 0x80, 0x76 पूर्ण,
	अणु 0x81, 0x80 पूर्ण,
	अणु 0x82, 0x88 पूर्ण,
	अणु 0x83, 0x8f पूर्ण,
	अणु 0x84, 0x96 पूर्ण,
	अणु 0x85, 0xa3 पूर्ण,
	अणु 0x86, 0xaf पूर्ण,
	अणु 0x87, 0xc4 पूर्ण,
	अणु 0x88, 0xd7 पूर्ण,
	अणु 0x89, 0xe8 पूर्ण,

/* AGC and AEC parameters.  Note we start by disabling those features,
   then turn them only after tweaking the values. */
	अणु OV7670_R13_COM8, OV7670_COM8_FASTAEC
			 | OV7670_COM8_AECSTEP
			 | OV7670_COM8_BFILT पूर्ण,
	अणु OV7670_R00_GAIN, 0x00 पूर्ण,
	अणु OV7670_R10_AECH, 0x00 पूर्ण,
	अणु OV7670_R0D_COM4, 0x40 पूर्ण, /* magic reserved bit */
	अणु OV7670_R14_COM9, 0x18 पूर्ण, /* 4x gain + magic rsvd bit */
	अणु OV7670_RA5_BD50MAX, 0x05 पूर्ण,
	अणु OV7670_RAB_BD60MAX, 0x07 पूर्ण,
	अणु OV7670_R24_AEW, 0x95 पूर्ण,
	अणु OV7670_R25_AEB, 0x33 पूर्ण,
	अणु OV7670_R26_VPT, 0xe3 पूर्ण,
	अणु OV7670_R9F_HAECC1, 0x78 पूर्ण,
	अणु OV7670_RA0_HAECC2, 0x68 पूर्ण,
	अणु 0xa1, 0x03 पूर्ण, /* magic */
	अणु OV7670_RA6_HAECC3, 0xd8 पूर्ण,
	अणु OV7670_RA7_HAECC4, 0xd8 पूर्ण,
	अणु OV7670_RA8_HAECC5, 0xf0 पूर्ण,
	अणु OV7670_RA9_HAECC6, 0x90 पूर्ण,
	अणु OV7670_RAA_HAECC7, 0x94 पूर्ण,
	अणु OV7670_R13_COM8, OV7670_COM8_FASTAEC
			| OV7670_COM8_AECSTEP
			| OV7670_COM8_BFILT
			| OV7670_COM8_AGC
			| OV7670_COM8_AEC पूर्ण,

/* Almost all of these are magic "reserved" values.  */
	अणु OV7670_R0E_COM5, 0x61 पूर्ण,
	अणु OV7670_R0F_COM6, 0x4b पूर्ण,
	अणु 0x16, 0x02 पूर्ण,
	अणु OV7670_R1E_MVFP, 0x07 पूर्ण,
	अणु 0x21, 0x02 पूर्ण,
	अणु 0x22, 0x91 पूर्ण,
	अणु 0x29, 0x07 पूर्ण,
	अणु 0x33, 0x0b पूर्ण,
	अणु 0x35, 0x0b पूर्ण,
	अणु 0x37, 0x1d पूर्ण,
	अणु 0x38, 0x71 पूर्ण,
	अणु 0x39, 0x2a पूर्ण,
	अणु OV7670_R3C_COM12, 0x78 पूर्ण,
	अणु 0x4d, 0x40 पूर्ण,
	अणु 0x4e, 0x20 पूर्ण,
	अणु OV7670_R69_GFIX, 0x00 पूर्ण,
	अणु 0x6b, 0x4a पूर्ण,
	अणु 0x74, 0x10 पूर्ण,
	अणु 0x8d, 0x4f पूर्ण,
	अणु 0x8e, 0x00 पूर्ण,
	अणु 0x8f, 0x00 पूर्ण,
	अणु 0x90, 0x00 पूर्ण,
	अणु 0x91, 0x00 पूर्ण,
	अणु 0x96, 0x00 पूर्ण,
	अणु 0x9a, 0x00 पूर्ण,
	अणु 0xb0, 0x84 पूर्ण,
	अणु 0xb1, 0x0c पूर्ण,
	अणु 0xb2, 0x0e पूर्ण,
	अणु 0xb3, 0x82 पूर्ण,
	अणु 0xb8, 0x0a पूर्ण,

/* More reserved magic, some of which tweaks white balance */
	अणु 0x43, 0x0a पूर्ण,
	अणु 0x44, 0xf0 पूर्ण,
	अणु 0x45, 0x34 पूर्ण,
	अणु 0x46, 0x58 पूर्ण,
	अणु 0x47, 0x28 पूर्ण,
	अणु 0x48, 0x3a पूर्ण,
	अणु 0x59, 0x88 पूर्ण,
	अणु 0x5a, 0x88 पूर्ण,
	अणु 0x5b, 0x44 पूर्ण,
	अणु 0x5c, 0x67 पूर्ण,
	अणु 0x5d, 0x49 पूर्ण,
	अणु 0x5e, 0x0e पूर्ण,
	अणु 0x6c, 0x0a पूर्ण,
	अणु 0x6d, 0x55 पूर्ण,
	अणु 0x6e, 0x11 पूर्ण,
	अणु 0x6f, 0x9f पूर्ण,			/* "9e for advance AWB" */
	अणु 0x6a, 0x40 पूर्ण,
	अणु OV7670_R01_BLUE, 0x40 पूर्ण,
	अणु OV7670_R02_RED, 0x60 पूर्ण,
	अणु OV7670_R13_COM8, OV7670_COM8_FASTAEC
			| OV7670_COM8_AECSTEP
			| OV7670_COM8_BFILT
			| OV7670_COM8_AGC
			| OV7670_COM8_AEC
			| OV7670_COM8_AWB पूर्ण,

/* Matrix coefficients */
	अणु 0x4f, 0x80 पूर्ण,
	अणु 0x50, 0x80 पूर्ण,
	अणु 0x51, 0x00 पूर्ण,
	अणु 0x52, 0x22 पूर्ण,
	अणु 0x53, 0x5e पूर्ण,
	अणु 0x54, 0x80 पूर्ण,
	अणु 0x58, 0x9e पूर्ण,

	अणु OV7670_R41_COM16, OV7670_COM16_AWBGAIN पूर्ण,
	अणु OV7670_R3F_EDGE, 0x00 पूर्ण,
	अणु 0x75, 0x05 पूर्ण,
	अणु 0x76, 0xe1 पूर्ण,
	अणु 0x4c, 0x00 पूर्ण,
	अणु 0x77, 0x01 पूर्ण,
	अणु OV7670_R3D_COM13, OV7670_COM13_GAMMA
			  | OV7670_COM13_UVSAT
			  | 2पूर्ण,		/* was 3 */
	अणु 0x4b, 0x09 पूर्ण,
	अणु 0xc9, 0x60 पूर्ण,
	अणु OV7670_R41_COM16, 0x38 पूर्ण,
	अणु 0x56, 0x40 पूर्ण,

	अणु 0x34, 0x11 पूर्ण,
	अणु OV7670_R3B_COM11, OV7670_COM11_EXP|OV7670_COM11_HZAUTO पूर्ण,
	अणु 0xa4, 0x88 पूर्ण,
	अणु 0x96, 0x00 पूर्ण,
	अणु 0x97, 0x30 पूर्ण,
	अणु 0x98, 0x20 पूर्ण,
	अणु 0x99, 0x30 पूर्ण,
	अणु 0x9a, 0x84 पूर्ण,
	अणु 0x9b, 0x29 पूर्ण,
	अणु 0x9c, 0x03 पूर्ण,
	अणु 0x9d, 0x4c पूर्ण,
	अणु 0x9e, 0x3f पूर्ण,
	अणु 0x78, 0x04 पूर्ण,

/* Extra-weird stuff.  Some sort of multiplexor रेजिस्टर */
	अणु 0x79, 0x01 पूर्ण,
	अणु 0xc8, 0xf0 पूर्ण,
	अणु 0x79, 0x0f पूर्ण,
	अणु 0xc8, 0x00 पूर्ण,
	अणु 0x79, 0x10 पूर्ण,
	अणु 0xc8, 0x7e पूर्ण,
	अणु 0x79, 0x0a पूर्ण,
	अणु 0xc8, 0x80 पूर्ण,
	अणु 0x79, 0x0b पूर्ण,
	अणु 0xc8, 0x01 पूर्ण,
	अणु 0x79, 0x0c पूर्ण,
	अणु 0xc8, 0x0f पूर्ण,
	अणु 0x79, 0x0d पूर्ण,
	अणु 0xc8, 0x20 पूर्ण,
	अणु 0x79, 0x09 पूर्ण,
	अणु 0xc8, 0x80 पूर्ण,
	अणु 0x79, 0x02 पूर्ण,
	अणु 0xc8, 0xc0 पूर्ण,
	अणु 0x79, 0x03 पूर्ण,
	अणु 0xc8, 0x40 पूर्ण,
	अणु 0x79, 0x05 पूर्ण,
	अणु 0xc8, 0x30 पूर्ण,
	अणु 0x79, 0x26 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov_i2c_regvals norm_8610[] = अणु
	अणु 0x12, 0x80 पूर्ण,
	अणु 0x00, 0x00 पूर्ण,
	अणु 0x01, 0x80 पूर्ण,
	अणु 0x02, 0x80 पूर्ण,
	अणु 0x03, 0xc0 पूर्ण,
	अणु 0x04, 0x30 पूर्ण,
	अणु 0x05, 0x30 पूर्ण, /* was 0x10, new from windrv 090403 */
	अणु 0x06, 0x70 पूर्ण, /* was 0x80, new from windrv 090403 */
	अणु 0x0a, 0x86 पूर्ण,
	अणु 0x0b, 0xb0 पूर्ण,
	अणु 0x0c, 0x20 पूर्ण,
	अणु 0x0d, 0x20 पूर्ण,
	अणु 0x11, 0x01 पूर्ण,
	अणु 0x12, 0x25 पूर्ण,
	अणु 0x13, 0x01 पूर्ण,
	अणु 0x14, 0x04 पूर्ण,
	अणु 0x15, 0x01 पूर्ण, /* Lin and Win think dअगरferent about UV order */
	अणु 0x16, 0x03 पूर्ण,
	अणु 0x17, 0x38 पूर्ण, /* was 0x2f, new from windrv 090403 */
	अणु 0x18, 0xea पूर्ण, /* was 0xcf, new from windrv 090403 */
	अणु 0x19, 0x02 पूर्ण, /* was 0x06, new from windrv 090403 */
	अणु 0x1a, 0xf5 पूर्ण,
	अणु 0x1b, 0x00 पूर्ण,
	अणु 0x20, 0xd0 पूर्ण, /* was 0x90, new from windrv 090403 */
	अणु 0x23, 0xc0 पूर्ण, /* was 0x00, new from windrv 090403 */
	अणु 0x24, 0x30 पूर्ण, /* was 0x1d, new from windrv 090403 */
	अणु 0x25, 0x50 पूर्ण, /* was 0x57, new from windrv 090403 */
	अणु 0x26, 0xa2 पूर्ण,
	अणु 0x27, 0xea पूर्ण,
	अणु 0x28, 0x00 पूर्ण,
	अणु 0x29, 0x00 पूर्ण,
	अणु 0x2a, 0x80 पूर्ण,
	अणु 0x2b, 0xc8 पूर्ण, /* was 0xcc, new from windrv 090403 */
	अणु 0x2c, 0xac पूर्ण,
	अणु 0x2d, 0x45 पूर्ण, /* was 0xd5, new from windrv 090403 */
	अणु 0x2e, 0x80 पूर्ण,
	अणु 0x2f, 0x14 पूर्ण, /* was 0x01, new from windrv 090403 */
	अणु 0x4c, 0x00 पूर्ण,
	अणु 0x4d, 0x30 पूर्ण, /* was 0x10, new from windrv 090403 */
	अणु 0x60, 0x02 पूर्ण, /* was 0x01, new from windrv 090403 */
	अणु 0x61, 0x00 पूर्ण, /* was 0x09, new from windrv 090403 */
	अणु 0x62, 0x5f पूर्ण, /* was 0xd7, new from windrv 090403 */
	अणु 0x63, 0xff पूर्ण,
	अणु 0x64, 0x53 पूर्ण, /* new windrv 090403 says 0x57,
			 * maybe that's wrong */
	अणु 0x65, 0x00 पूर्ण,
	अणु 0x66, 0x55 पूर्ण,
	अणु 0x67, 0xb0 पूर्ण,
	अणु 0x68, 0xc0 पूर्ण, /* was 0xaf, new from windrv 090403 */
	अणु 0x69, 0x02 पूर्ण,
	अणु 0x6a, 0x22 पूर्ण,
	अणु 0x6b, 0x00 पूर्ण,
	अणु 0x6c, 0x99 पूर्ण, /* was 0x80, old windrv says 0x00, but
			 * deleting bit7 colors the first images red */
	अणु 0x6d, 0x11 पूर्ण, /* was 0x00, new from windrv 090403 */
	अणु 0x6e, 0x11 पूर्ण, /* was 0x00, new from windrv 090403 */
	अणु 0x6f, 0x01 पूर्ण,
	अणु 0x70, 0x8b पूर्ण,
	अणु 0x71, 0x00 पूर्ण,
	अणु 0x72, 0x14 पूर्ण,
	अणु 0x73, 0x54 पूर्ण,
	अणु 0x74, 0x00 पूर्ण,/* 0x60? - was 0x00, new from windrv 090403 */
	अणु 0x75, 0x0e पूर्ण,
	अणु 0x76, 0x02 पूर्ण, /* was 0x02, new from windrv 090403 */
	अणु 0x77, 0xff पूर्ण,
	अणु 0x78, 0x80 पूर्ण,
	अणु 0x79, 0x80 पूर्ण,
	अणु 0x7a, 0x80 पूर्ण,
	अणु 0x7b, 0x10 पूर्ण, /* was 0x13, new from windrv 090403 */
	अणु 0x7c, 0x00 पूर्ण,
	अणु 0x7d, 0x08 पूर्ण, /* was 0x09, new from windrv 090403 */
	अणु 0x7e, 0x08 पूर्ण, /* was 0xc0, new from windrv 090403 */
	अणु 0x7f, 0xfb पूर्ण,
	अणु 0x80, 0x28 पूर्ण,
	अणु 0x81, 0x00 पूर्ण,
	अणु 0x82, 0x23 पूर्ण,
	अणु 0x83, 0x0b पूर्ण,
	अणु 0x84, 0x00 पूर्ण,
	अणु 0x85, 0x62 पूर्ण, /* was 0x61, new from windrv 090403 */
	अणु 0x86, 0xc9 पूर्ण,
	अणु 0x87, 0x00 पूर्ण,
	अणु 0x88, 0x00 पूर्ण,
	अणु 0x89, 0x01 पूर्ण,
	अणु 0x12, 0x20 पूर्ण,
	अणु 0x12, 0x25 पूर्ण, /* was 0x24, new from windrv 090403 */
पूर्ण;

अटल अचिन्हित अक्षर ov7670_असल_to_sm(अचिन्हित अक्षर v)
अणु
	अगर (v > 127)
		वापस v & 0x7f;
	वापस (128 - v) | 0x80;
पूर्ण

/* Write a OV519 रेजिस्टर */
अटल व्योम reg_w(काष्ठा sd *sd, u16 index, u16 value)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक ret, req = 0;

	अगर (sd->gspca_dev.usb_err < 0)
		वापस;

	/* Aव्योम things going to fast क्रम the bridge with a xhci host */
	udelay(150);

	चयन (sd->bridge) अणु
	हाल BRIDGE_OV511:
	हाल BRIDGE_OV511PLUS:
		req = 2;
		अवरोध;
	हाल BRIDGE_OVFX2:
		req = 0x0a;
		fallthrough;
	हाल BRIDGE_W9968CF:
		gspca_dbg(gspca_dev, D_USBO, "SET %02x %04x %04x\n",
			  req, value, index);
		ret = usb_control_msg(sd->gspca_dev.dev,
			usb_sndctrlpipe(sd->gspca_dev.dev, 0),
			req,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index, शून्य, 0, 500);
		जाओ leave;
	शेष:
		req = 1;
	पूर्ण

	gspca_dbg(gspca_dev, D_USBO, "SET %02x 0000 %04x %02x\n",
		  req, index, value);
	sd->gspca_dev.usb_buf[0] = value;
	ret = usb_control_msg(sd->gspca_dev.dev,
			usb_sndctrlpipe(sd->gspca_dev.dev, 0),
			req,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, index,
			sd->gspca_dev.usb_buf, 1, 500);
leave:
	अगर (ret < 0) अणु
		gspca_err(gspca_dev, "reg_w %02x failed %d\n", index, ret);
		sd->gspca_dev.usb_err = ret;
		वापस;
	पूर्ण
पूर्ण

/* Read from a OV519 रेजिस्टर, note not valid क्रम the w9968cf!! */
/* वापसs: negative is error, pos or zero is data */
अटल पूर्णांक reg_r(काष्ठा sd *sd, u16 index)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक ret;
	पूर्णांक req;

	अगर (sd->gspca_dev.usb_err < 0)
		वापस -1;

	चयन (sd->bridge) अणु
	हाल BRIDGE_OV511:
	हाल BRIDGE_OV511PLUS:
		req = 3;
		अवरोध;
	हाल BRIDGE_OVFX2:
		req = 0x0b;
		अवरोध;
	शेष:
		req = 1;
	पूर्ण

	/* Aव्योम things going to fast क्रम the bridge with a xhci host */
	udelay(150);
	ret = usb_control_msg(sd->gspca_dev.dev,
			usb_rcvctrlpipe(sd->gspca_dev.dev, 0),
			req,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, index, sd->gspca_dev.usb_buf, 1, 500);

	अगर (ret >= 0) अणु
		ret = sd->gspca_dev.usb_buf[0];
		gspca_dbg(gspca_dev, D_USBI, "GET %02x 0000 %04x %02x\n",
			  req, index, ret);
	पूर्ण अन्यथा अणु
		gspca_err(gspca_dev, "reg_r %02x failed %d\n", index, ret);
		sd->gspca_dev.usb_err = ret;
		/*
		 * Make sure the result is zeroed to aव्योम uninitialized
		 * values.
		 */
		gspca_dev->usb_buf[0] = 0;
	पूर्ण

	वापस ret;
पूर्ण

/* Read 8 values from a OV519 रेजिस्टर */
अटल पूर्णांक reg_r8(काष्ठा sd *sd,
		  u16 index)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक ret;

	अगर (sd->gspca_dev.usb_err < 0)
		वापस -1;

	/* Aव्योम things going to fast क्रम the bridge with a xhci host */
	udelay(150);
	ret = usb_control_msg(sd->gspca_dev.dev,
			usb_rcvctrlpipe(sd->gspca_dev.dev, 0),
			1,			/* REQ_IO */
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, index, sd->gspca_dev.usb_buf, 8, 500);

	अगर (ret >= 0) अणु
		ret = sd->gspca_dev.usb_buf[0];
	पूर्ण अन्यथा अणु
		gspca_err(gspca_dev, "reg_r8 %02x failed %d\n", index, ret);
		sd->gspca_dev.usb_err = ret;
		/*
		 * Make sure the buffer is zeroed to aव्योम uninitialized
		 * values.
		 */
		स_रखो(gspca_dev->usb_buf, 0, 8);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Writes bits at positions specअगरied by mask to an OV51x reg. Bits that are in
 * the same position as 1's in "mask" are cleared and set to "value". Bits
 * that are in the same position as 0's in "mask" are preserved, regardless
 * of their respective state in "value".
 */
अटल व्योम reg_w_mask(काष्ठा sd *sd,
			u16 index,
			u8 value,
			u8 mask)
अणु
	पूर्णांक ret;
	u8 oldval;

	अगर (mask != 0xff) अणु
		value &= mask;			/* Enक्रमce mask on value */
		ret = reg_r(sd, index);
		अगर (ret < 0)
			वापस;

		oldval = ret & ~mask;		/* Clear the masked bits */
		value |= oldval;		/* Set the desired bits */
	पूर्ण
	reg_w(sd, index, value);
पूर्ण

/*
 * Writes multiple (n) byte value to a single रेजिस्टर. Only valid with certain
 * रेजिस्टरs (0x30 and 0xc4 - 0xce).
 */
अटल व्योम ov518_reg_w32(काष्ठा sd *sd, u16 index, u32 value, पूर्णांक n)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक ret;

	अगर (sd->gspca_dev.usb_err < 0)
		वापस;

	*((__le32 *) sd->gspca_dev.usb_buf) = __cpu_to_le32(value);

	/* Aव्योम things going to fast क्रम the bridge with a xhci host */
	udelay(150);
	ret = usb_control_msg(sd->gspca_dev.dev,
			usb_sndctrlpipe(sd->gspca_dev.dev, 0),
			1 /* REG_IO */,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, index,
			sd->gspca_dev.usb_buf, n, 500);
	अगर (ret < 0) अणु
		gspca_err(gspca_dev, "reg_w32 %02x failed %d\n", index, ret);
		sd->gspca_dev.usb_err = ret;
	पूर्ण
पूर्ण

अटल व्योम ov511_i2c_w(काष्ठा sd *sd, u8 reg, u8 value)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक rc, retries;

	gspca_dbg(gspca_dev, D_USBO, "ov511_i2c_w %02x %02x\n", reg, value);

	/* Three byte ग_लिखो cycle */
	क्रम (retries = 6; ; ) अणु
		/* Select camera रेजिस्टर */
		reg_w(sd, R51x_I2C_SADDR_3, reg);

		/* Write "value" to I2C data port of OV511 */
		reg_w(sd, R51x_I2C_DATA, value);

		/* Initiate 3-byte ग_लिखो cycle */
		reg_w(sd, R511_I2C_CTL, 0x01);

		करो अणु
			rc = reg_r(sd, R511_I2C_CTL);
		पूर्ण जबतक (rc > 0 && ((rc & 1) == 0)); /* Retry until idle */

		अगर (rc < 0)
			वापस;

		अगर ((rc & 2) == 0) /* Ack? */
			अवरोध;
		अगर (--retries < 0) अणु
			gspca_dbg(gspca_dev, D_USBO, "i2c write retries exhausted\n");
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ov511_i2c_r(काष्ठा sd *sd, u8 reg)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक rc, value, retries;

	/* Two byte ग_लिखो cycle */
	क्रम (retries = 6; ; ) अणु
		/* Select camera रेजिस्टर */
		reg_w(sd, R51x_I2C_SADDR_2, reg);

		/* Initiate 2-byte ग_लिखो cycle */
		reg_w(sd, R511_I2C_CTL, 0x03);

		करो अणु
			rc = reg_r(sd, R511_I2C_CTL);
		पूर्ण जबतक (rc > 0 && ((rc & 1) == 0)); /* Retry until idle */

		अगर (rc < 0)
			वापस rc;

		अगर ((rc & 2) == 0) /* Ack? */
			अवरोध;

		/* I2C पात */
		reg_w(sd, R511_I2C_CTL, 0x10);

		अगर (--retries < 0) अणु
			gspca_dbg(gspca_dev, D_USBI, "i2c write retries exhausted\n");
			वापस -1;
		पूर्ण
	पूर्ण

	/* Two byte पढ़ो cycle */
	क्रम (retries = 6; ; ) अणु
		/* Initiate 2-byte पढ़ो cycle */
		reg_w(sd, R511_I2C_CTL, 0x05);

		करो अणु
			rc = reg_r(sd, R511_I2C_CTL);
		पूर्ण जबतक (rc > 0 && ((rc & 1) == 0)); /* Retry until idle */

		अगर (rc < 0)
			वापस rc;

		अगर ((rc & 2) == 0) /* Ack? */
			अवरोध;

		/* I2C पात */
		reg_w(sd, R511_I2C_CTL, 0x10);

		अगर (--retries < 0) अणु
			gspca_dbg(gspca_dev, D_USBI, "i2c read retries exhausted\n");
			वापस -1;
		पूर्ण
	पूर्ण

	value = reg_r(sd, R51x_I2C_DATA);

	gspca_dbg(gspca_dev, D_USBI, "ov511_i2c_r %02x %02x\n", reg, value);

	/* This is needed to make i2c_w() work */
	reg_w(sd, R511_I2C_CTL, 0x05);

	वापस value;
पूर्ण

/*
 * The OV518 I2C I/O procedure is dअगरferent, hence, this function.
 * This is normally only called from i2c_w(). Note that this function
 * always succeeds regardless of whether the sensor is present and working.
 */
अटल व्योम ov518_i2c_w(काष्ठा sd *sd,
		u8 reg,
		u8 value)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;

	gspca_dbg(gspca_dev, D_USBO, "ov518_i2c_w %02x %02x\n", reg, value);

	/* Select camera रेजिस्टर */
	reg_w(sd, R51x_I2C_SADDR_3, reg);

	/* Write "value" to I2C data port of OV511 */
	reg_w(sd, R51x_I2C_DATA, value);

	/* Initiate 3-byte ग_लिखो cycle */
	reg_w(sd, R518_I2C_CTL, 0x01);

	/* रुको क्रम ग_लिखो complete */
	msleep(4);
	reg_r8(sd, R518_I2C_CTL);
पूर्ण

/*
 * वापसs: negative is error, pos or zero is data
 *
 * The OV518 I2C I/O procedure is dअगरferent, hence, this function.
 * This is normally only called from i2c_r(). Note that this function
 * always succeeds regardless of whether the sensor is present and working.
 */
अटल पूर्णांक ov518_i2c_r(काष्ठा sd *sd, u8 reg)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक value;

	/* Select camera रेजिस्टर */
	reg_w(sd, R51x_I2C_SADDR_2, reg);

	/* Initiate 2-byte ग_लिखो cycle */
	reg_w(sd, R518_I2C_CTL, 0x03);
	reg_r8(sd, R518_I2C_CTL);

	/* Initiate 2-byte पढ़ो cycle */
	reg_w(sd, R518_I2C_CTL, 0x05);
	reg_r8(sd, R518_I2C_CTL);

	value = reg_r(sd, R51x_I2C_DATA);
	gspca_dbg(gspca_dev, D_USBI, "ov518_i2c_r %02x %02x\n", reg, value);
	वापस value;
पूर्ण

अटल व्योम ovfx2_i2c_w(काष्ठा sd *sd, u8 reg, u8 value)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक ret;

	अगर (sd->gspca_dev.usb_err < 0)
		वापस;

	ret = usb_control_msg(sd->gspca_dev.dev,
			usb_sndctrlpipe(sd->gspca_dev.dev, 0),
			0x02,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			(u16) value, (u16) reg, शून्य, 0, 500);

	अगर (ret < 0) अणु
		gspca_err(gspca_dev, "ovfx2_i2c_w %02x failed %d\n", reg, ret);
		sd->gspca_dev.usb_err = ret;
	पूर्ण

	gspca_dbg(gspca_dev, D_USBO, "ovfx2_i2c_w %02x %02x\n", reg, value);
पूर्ण

अटल पूर्णांक ovfx2_i2c_r(काष्ठा sd *sd, u8 reg)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक ret;

	अगर (sd->gspca_dev.usb_err < 0)
		वापस -1;

	ret = usb_control_msg(sd->gspca_dev.dev,
			usb_rcvctrlpipe(sd->gspca_dev.dev, 0),
			0x03,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, (u16) reg, sd->gspca_dev.usb_buf, 1, 500);

	अगर (ret >= 0) अणु
		ret = sd->gspca_dev.usb_buf[0];
		gspca_dbg(gspca_dev, D_USBI, "ovfx2_i2c_r %02x %02x\n",
			  reg, ret);
	पूर्ण अन्यथा अणु
		gspca_err(gspca_dev, "ovfx2_i2c_r %02x failed %d\n", reg, ret);
		sd->gspca_dev.usb_err = ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम i2c_w(काष्ठा sd *sd, u8 reg, u8 value)
अणु
	अगर (sd->sensor_reg_cache[reg] == value)
		वापस;

	चयन (sd->bridge) अणु
	हाल BRIDGE_OV511:
	हाल BRIDGE_OV511PLUS:
		ov511_i2c_w(sd, reg, value);
		अवरोध;
	हाल BRIDGE_OV518:
	हाल BRIDGE_OV518PLUS:
	हाल BRIDGE_OV519:
		ov518_i2c_w(sd, reg, value);
		अवरोध;
	हाल BRIDGE_OVFX2:
		ovfx2_i2c_w(sd, reg, value);
		अवरोध;
	हाल BRIDGE_W9968CF:
		w9968cf_i2c_w(sd, reg, value);
		अवरोध;
	पूर्ण

	अगर (sd->gspca_dev.usb_err >= 0) अणु
		/* Up on sensor reset empty the रेजिस्टर cache */
		अगर (reg == 0x12 && (value & 0x80))
			स_रखो(sd->sensor_reg_cache, -1,
				माप(sd->sensor_reg_cache));
		अन्यथा
			sd->sensor_reg_cache[reg] = value;
	पूर्ण
पूर्ण

अटल पूर्णांक i2c_r(काष्ठा sd *sd, u8 reg)
अणु
	पूर्णांक ret = -1;

	अगर (sd->sensor_reg_cache[reg] != -1)
		वापस sd->sensor_reg_cache[reg];

	चयन (sd->bridge) अणु
	हाल BRIDGE_OV511:
	हाल BRIDGE_OV511PLUS:
		ret = ov511_i2c_r(sd, reg);
		अवरोध;
	हाल BRIDGE_OV518:
	हाल BRIDGE_OV518PLUS:
	हाल BRIDGE_OV519:
		ret = ov518_i2c_r(sd, reg);
		अवरोध;
	हाल BRIDGE_OVFX2:
		ret = ovfx2_i2c_r(sd, reg);
		अवरोध;
	हाल BRIDGE_W9968CF:
		ret = w9968cf_i2c_r(sd, reg);
		अवरोध;
	पूर्ण

	अगर (ret >= 0)
		sd->sensor_reg_cache[reg] = ret;

	वापस ret;
पूर्ण

/* Writes bits at positions specअगरied by mask to an I2C reg. Bits that are in
 * the same position as 1's in "mask" are cleared and set to "value". Bits
 * that are in the same position as 0's in "mask" are preserved, regardless
 * of their respective state in "value".
 */
अटल व्योम i2c_w_mask(काष्ठा sd *sd,
			u8 reg,
			u8 value,
			u8 mask)
अणु
	पूर्णांक rc;
	u8 oldval;

	value &= mask;			/* Enक्रमce mask on value */
	rc = i2c_r(sd, reg);
	अगर (rc < 0)
		वापस;
	oldval = rc & ~mask;		/* Clear the masked bits */
	value |= oldval;		/* Set the desired bits */
	i2c_w(sd, reg, value);
पूर्ण

/* Temporarily stops OV511 from functioning. Must करो this beक्रमe changing
 * रेजिस्टरs जबतक the camera is streaming */
अटल अंतरभूत व्योम ov51x_stop(काष्ठा sd *sd)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;

	gspca_dbg(gspca_dev, D_STREAM, "stopping\n");
	sd->stopped = 1;
	चयन (sd->bridge) अणु
	हाल BRIDGE_OV511:
	हाल BRIDGE_OV511PLUS:
		reg_w(sd, R51x_SYS_RESET, 0x3d);
		अवरोध;
	हाल BRIDGE_OV518:
	हाल BRIDGE_OV518PLUS:
		reg_w_mask(sd, R51x_SYS_RESET, 0x3a, 0x3a);
		अवरोध;
	हाल BRIDGE_OV519:
		reg_w(sd, OV519_R51_RESET1, 0x0f);
		reg_w(sd, OV519_R51_RESET1, 0x00);
		reg_w(sd, 0x22, 0x00);		/* FRAR */
		अवरोध;
	हाल BRIDGE_OVFX2:
		reg_w_mask(sd, 0x0f, 0x00, 0x02);
		अवरोध;
	हाल BRIDGE_W9968CF:
		reg_w(sd, 0x3c, 0x0a05); /* stop USB transfer */
		अवरोध;
	पूर्ण
पूर्ण

/* Restarts OV511 after ov511_stop() is called. Has no effect अगर it is not
 * actually stopped (क्रम perक्रमmance). */
अटल अंतरभूत व्योम ov51x_restart(काष्ठा sd *sd)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;

	gspca_dbg(gspca_dev, D_STREAM, "restarting\n");
	अगर (!sd->stopped)
		वापस;
	sd->stopped = 0;

	/* Reinitialize the stream */
	चयन (sd->bridge) अणु
	हाल BRIDGE_OV511:
	हाल BRIDGE_OV511PLUS:
		reg_w(sd, R51x_SYS_RESET, 0x00);
		अवरोध;
	हाल BRIDGE_OV518:
	हाल BRIDGE_OV518PLUS:
		reg_w(sd, 0x2f, 0x80);
		reg_w(sd, R51x_SYS_RESET, 0x00);
		अवरोध;
	हाल BRIDGE_OV519:
		reg_w(sd, OV519_R51_RESET1, 0x0f);
		reg_w(sd, OV519_R51_RESET1, 0x00);
		reg_w(sd, 0x22, 0x1d);		/* FRAR */
		अवरोध;
	हाल BRIDGE_OVFX2:
		reg_w_mask(sd, 0x0f, 0x02, 0x02);
		अवरोध;
	हाल BRIDGE_W9968CF:
		reg_w(sd, 0x3c, 0x8a05); /* USB FIFO enable */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ov51x_set_slave_ids(काष्ठा sd *sd, u8 slave);

/* This करोes an initial reset of an OmniVision sensor and ensures that I2C
 * is synchronized. Returns <0 on failure.
 */
अटल पूर्णांक init_ov_sensor(काष्ठा sd *sd, u8 slave)
अणु
	पूर्णांक i;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;

	ov51x_set_slave_ids(sd, slave);

	/* Reset the sensor */
	i2c_w(sd, 0x12, 0x80);

	/* Wait क्रम it to initialize */
	msleep(150);

	क्रम (i = 0; i < i2c_detect_tries; i++) अणु
		अगर (i2c_r(sd, OV7610_REG_ID_HIGH) == 0x7f &&
		    i2c_r(sd, OV7610_REG_ID_LOW) == 0xa2) अणु
			gspca_dbg(gspca_dev, D_PROBE, "I2C synced in %d attempt(s)\n",
				  i);
			वापस 0;
		पूर्ण

		/* Reset the sensor */
		i2c_w(sd, 0x12, 0x80);

		/* Wait क्रम it to initialize */
		msleep(150);

		/* Dummy पढ़ो to sync I2C */
		अगर (i2c_r(sd, 0x00) < 0)
			वापस -1;
	पूर्ण
	वापस -1;
पूर्ण

/* Set the पढ़ो and ग_लिखो slave IDs. The "slave" argument is the ग_लिखो slave,
 * and the पढ़ो slave will be set to (slave + 1).
 * This should not be called from outside the i2c I/O functions.
 * Sets I2C पढ़ो and ग_लिखो slave IDs. Returns <0 क्रम error
 */
अटल व्योम ov51x_set_slave_ids(काष्ठा sd *sd,
				u8 slave)
अणु
	चयन (sd->bridge) अणु
	हाल BRIDGE_OVFX2:
		reg_w(sd, OVFX2_I2C_ADDR, slave);
		वापस;
	हाल BRIDGE_W9968CF:
		sd->sensor_addr = slave;
		वापस;
	पूर्ण

	reg_w(sd, R51x_I2C_W_SID, slave);
	reg_w(sd, R51x_I2C_R_SID, slave + 1);
पूर्ण

अटल व्योम ग_लिखो_regvals(काष्ठा sd *sd,
			 स्थिर काष्ठा ov_regvals *regvals,
			 पूर्णांक n)
अणु
	जबतक (--n >= 0) अणु
		reg_w(sd, regvals->reg, regvals->val);
		regvals++;
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_i2c_regvals(काष्ठा sd *sd,
			स्थिर काष्ठा ov_i2c_regvals *regvals,
			पूर्णांक n)
अणु
	जबतक (--n >= 0) अणु
		i2c_w(sd, regvals->reg, regvals->val);
		regvals++;
	पूर्ण
पूर्ण

/****************************************************************************
 *
 * OV511 and sensor configuration
 *
 ***************************************************************************/

/* This initializes the OV2x10 / OV3610 / OV3620 / OV9600 */
अटल व्योम ov_hires_configure(काष्ठा sd *sd)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक high, low;

	अगर (sd->bridge != BRIDGE_OVFX2) अणु
		gspca_err(gspca_dev, "error hires sensors only supported with ovfx2\n");
		वापस;
	पूर्ण

	gspca_dbg(gspca_dev, D_PROBE, "starting ov hires configuration\n");

	/* Detect sensor (sub)type */
	high = i2c_r(sd, 0x0a);
	low = i2c_r(sd, 0x0b);
	/* info("%x, %x", high, low); */
	चयन (high) अणु
	हाल 0x96:
		चयन (low) अणु
		हाल 0x40:
			gspca_dbg(gspca_dev, D_PROBE, "Sensor is a OV2610\n");
			sd->sensor = SEN_OV2610;
			वापस;
		हाल 0x41:
			gspca_dbg(gspca_dev, D_PROBE, "Sensor is a OV2610AE\n");
			sd->sensor = SEN_OV2610AE;
			वापस;
		हाल 0xb1:
			gspca_dbg(gspca_dev, D_PROBE, "Sensor is a OV9600\n");
			sd->sensor = SEN_OV9600;
			वापस;
		पूर्ण
		अवरोध;
	हाल 0x36:
		अगर ((low & 0x0f) == 0x00) अणु
			gspca_dbg(gspca_dev, D_PROBE, "Sensor is a OV3610\n");
			sd->sensor = SEN_OV3610;
			वापस;
		पूर्ण
		अवरोध;
	पूर्ण
	gspca_err(gspca_dev, "Error unknown sensor type: %02x%02x\n",
		  high, low);
पूर्ण

/* This initializes the OV8110, OV8610 sensor. The OV8110 uses
 * the same रेजिस्टर settings as the OV8610, since they are very similar.
 */
अटल व्योम ov8xx0_configure(काष्ठा sd *sd)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक rc;

	gspca_dbg(gspca_dev, D_PROBE, "starting ov8xx0 configuration\n");

	/* Detect sensor (sub)type */
	rc = i2c_r(sd, OV7610_REG_COM_I);
	अगर (rc < 0) अणु
		gspca_err(gspca_dev, "Error detecting sensor type\n");
		वापस;
	पूर्ण
	अगर ((rc & 3) == 1)
		sd->sensor = SEN_OV8610;
	अन्यथा
		gspca_err(gspca_dev, "Unknown image sensor version: %d\n",
			  rc & 3);
पूर्ण

/* This initializes the OV7610, OV7620, or OV76BE sensor. The OV76BE uses
 * the same रेजिस्टर settings as the OV7610, since they are very similar.
 */
अटल व्योम ov7xx0_configure(काष्ठा sd *sd)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक rc, high, low;

	gspca_dbg(gspca_dev, D_PROBE, "starting OV7xx0 configuration\n");

	/* Detect sensor (sub)type */
	rc = i2c_r(sd, OV7610_REG_COM_I);

	/* add OV7670 here
	 * it appears to be wrongly detected as a 7610 by शेष */
	अगर (rc < 0) अणु
		gspca_err(gspca_dev, "Error detecting sensor type\n");
		वापस;
	पूर्ण
	अगर ((rc & 3) == 3) अणु
		/* quick hack to make OV7670s work */
		high = i2c_r(sd, 0x0a);
		low = i2c_r(sd, 0x0b);
		/* info("%x, %x", high, low); */
		अगर (high == 0x76 && (low & 0xf0) == 0x70) अणु
			gspca_dbg(gspca_dev, D_PROBE, "Sensor is an OV76%02x\n",
				  low);
			sd->sensor = SEN_OV7670;
		पूर्ण अन्यथा अणु
			gspca_dbg(gspca_dev, D_PROBE, "Sensor is an OV7610\n");
			sd->sensor = SEN_OV7610;
		पूर्ण
	पूर्ण अन्यथा अगर ((rc & 3) == 1) अणु
		/* I करोn't know what's dअगरferent about the 76BE yet. */
		अगर (i2c_r(sd, 0x15) & 1) अणु
			gspca_dbg(gspca_dev, D_PROBE, "Sensor is an OV7620AE\n");
			sd->sensor = SEN_OV7620AE;
		पूर्ण अन्यथा अणु
			gspca_dbg(gspca_dev, D_PROBE, "Sensor is an OV76BE\n");
			sd->sensor = SEN_OV76BE;
		पूर्ण
	पूर्ण अन्यथा अगर ((rc & 3) == 0) अणु
		/* try to पढ़ो product id रेजिस्टरs */
		high = i2c_r(sd, 0x0a);
		अगर (high < 0) अणु
			gspca_err(gspca_dev, "Error detecting camera chip PID\n");
			वापस;
		पूर्ण
		low = i2c_r(sd, 0x0b);
		अगर (low < 0) अणु
			gspca_err(gspca_dev, "Error detecting camera chip VER\n");
			वापस;
		पूर्ण
		अगर (high == 0x76) अणु
			चयन (low) अणु
			हाल 0x30:
				gspca_err(gspca_dev, "Sensor is an OV7630/OV7635\n");
				gspca_err(gspca_dev, "7630 is not supported by this driver\n");
				वापस;
			हाल 0x40:
				gspca_dbg(gspca_dev, D_PROBE, "Sensor is an OV7645\n");
				sd->sensor = SEN_OV7640; /* FIXME */
				अवरोध;
			हाल 0x45:
				gspca_dbg(gspca_dev, D_PROBE, "Sensor is an OV7645B\n");
				sd->sensor = SEN_OV7640; /* FIXME */
				अवरोध;
			हाल 0x48:
				gspca_dbg(gspca_dev, D_PROBE, "Sensor is an OV7648\n");
				sd->sensor = SEN_OV7648;
				अवरोध;
			हाल 0x60:
				gspca_dbg(gspca_dev, D_PROBE, "Sensor is a OV7660\n");
				sd->sensor = SEN_OV7660;
				अवरोध;
			शेष:
				gspca_err(gspca_dev, "Unknown sensor: 0x76%02x\n",
					  low);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			gspca_dbg(gspca_dev, D_PROBE, "Sensor is an OV7620\n");
			sd->sensor = SEN_OV7620;
		पूर्ण
	पूर्ण अन्यथा अणु
		gspca_err(gspca_dev, "Unknown image sensor version: %d\n",
			  rc & 3);
	पूर्ण
पूर्ण

/* This initializes the OV6620, OV6630, OV6630AE, or OV6630AF sensor. */
अटल व्योम ov6xx0_configure(काष्ठा sd *sd)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक rc;

	gspca_dbg(gspca_dev, D_PROBE, "starting OV6xx0 configuration\n");

	/* Detect sensor (sub)type */
	rc = i2c_r(sd, OV7610_REG_COM_I);
	अगर (rc < 0) अणु
		gspca_err(gspca_dev, "Error detecting sensor type\n");
		वापस;
	पूर्ण

	/* Ugh. The first two bits are the version bits, but
	 * the entire रेजिस्टर value must be used. I guess OVT
	 * underestimated how many variants they would make. */
	चयन (rc) अणु
	हाल 0x00:
		sd->sensor = SEN_OV6630;
		pr_warn("WARNING: Sensor is an OV66308. Your camera may have been misdetected in previous driver versions.\n");
		अवरोध;
	हाल 0x01:
		sd->sensor = SEN_OV6620;
		gspca_dbg(gspca_dev, D_PROBE, "Sensor is an OV6620\n");
		अवरोध;
	हाल 0x02:
		sd->sensor = SEN_OV6630;
		gspca_dbg(gspca_dev, D_PROBE, "Sensor is an OV66308AE\n");
		अवरोध;
	हाल 0x03:
		sd->sensor = SEN_OV66308AF;
		gspca_dbg(gspca_dev, D_PROBE, "Sensor is an OV66308AF\n");
		अवरोध;
	हाल 0x90:
		sd->sensor = SEN_OV6630;
		pr_warn("WARNING: Sensor is an OV66307. Your camera may have been misdetected in previous driver versions.\n");
		अवरोध;
	शेष:
		gspca_err(gspca_dev, "FATAL: Unknown sensor version: 0x%02x\n",
			  rc);
		वापस;
	पूर्ण

	/* Set sensor-specअगरic vars */
	sd->sअगर = 1;
पूर्ण

/* Turns on or off the LED. Only has an effect with OV511+/OV518(+)/OV519 */
अटल व्योम ov51x_led_control(काष्ठा sd *sd, पूर्णांक on)
अणु
	अगर (sd->invert_led)
		on = !on;

	चयन (sd->bridge) अणु
	/* OV511 has no LED control */
	हाल BRIDGE_OV511PLUS:
		reg_w(sd, R511_SYS_LED_CTL, on);
		अवरोध;
	हाल BRIDGE_OV518:
	हाल BRIDGE_OV518PLUS:
		reg_w_mask(sd, R518_GPIO_OUT, 0x02 * on, 0x02);
		अवरोध;
	हाल BRIDGE_OV519:
		reg_w_mask(sd, OV519_GPIO_DATA_OUT0, on, 1);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sd_reset_snapshot(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (!sd->snapshot_needs_reset)
		वापस;

	/* Note it is important that we clear sd->snapshot_needs_reset,
	   beक्रमe actually clearing the snapshot state in the bridge
	   otherwise we might race with the pkt_scan पूर्णांकerrupt handler */
	sd->snapshot_needs_reset = 0;

	चयन (sd->bridge) अणु
	हाल BRIDGE_OV511:
	हाल BRIDGE_OV511PLUS:
		reg_w(sd, R51x_SYS_SNAP, 0x02);
		reg_w(sd, R51x_SYS_SNAP, 0x00);
		अवरोध;
	हाल BRIDGE_OV518:
	हाल BRIDGE_OV518PLUS:
		reg_w(sd, R51x_SYS_SNAP, 0x02); /* Reset */
		reg_w(sd, R51x_SYS_SNAP, 0x01); /* Enable */
		अवरोध;
	हाल BRIDGE_OV519:
		reg_w(sd, R51x_SYS_RESET, 0x40);
		reg_w(sd, R51x_SYS_RESET, 0x00);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ov51x_upload_quan_tables(काष्ठा sd *sd)
अणु
	अटल स्थिर अचिन्हित अक्षर yQuanTable511[] = अणु
		0, 1, 1, 2, 2, 3, 3, 4,
		1, 1, 1, 2, 2, 3, 4, 4,
		1, 1, 2, 2, 3, 4, 4, 4,
		2, 2, 2, 3, 4, 4, 4, 4,
		2, 2, 3, 4, 4, 5, 5, 5,
		3, 3, 4, 4, 5, 5, 5, 5,
		3, 4, 4, 4, 5, 5, 5, 5,
		4, 4, 4, 4, 5, 5, 5, 5
	पूर्ण;

	अटल स्थिर अचिन्हित अक्षर uvQuanTable511[] = अणु
		0, 2, 2, 3, 4, 4, 4, 4,
		2, 2, 2, 4, 4, 4, 4, 4,
		2, 2, 3, 4, 4, 4, 4, 4,
		3, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4
	पूर्ण;

	/* OV518 quantization tables are 8x4 (instead of 8x8) */
	अटल स्थिर अचिन्हित अक्षर yQuanTable518[] = अणु
		5, 4, 5, 6, 6, 7, 7, 7,
		5, 5, 5, 5, 6, 7, 7, 7,
		6, 6, 6, 6, 7, 7, 7, 8,
		7, 7, 6, 7, 7, 7, 8, 8
	पूर्ण;
	अटल स्थिर अचिन्हित अक्षर uvQuanTable518[] = अणु
		6, 6, 6, 7, 7, 7, 7, 7,
		6, 6, 6, 7, 7, 7, 7, 7,
		6, 6, 6, 7, 7, 7, 7, 8,
		7, 7, 7, 7, 7, 7, 8, 8
	पूर्ण;

	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	स्थिर अचिन्हित अक्षर *pYTable, *pUVTable;
	अचिन्हित अक्षर val0, val1;
	पूर्णांक i, size, reg = R51x_COMP_LUT_BEGIN;

	gspca_dbg(gspca_dev, D_PROBE, "Uploading quantization tables\n");

	अगर (sd->bridge == BRIDGE_OV511 || sd->bridge == BRIDGE_OV511PLUS) अणु
		pYTable = yQuanTable511;
		pUVTable = uvQuanTable511;
		size = 32;
	पूर्ण अन्यथा अणु
		pYTable = yQuanTable518;
		pUVTable = uvQuanTable518;
		size = 16;
	पूर्ण

	क्रम (i = 0; i < size; i++) अणु
		val0 = *pYTable++;
		val1 = *pYTable++;
		val0 &= 0x0f;
		val1 &= 0x0f;
		val0 |= val1 << 4;
		reg_w(sd, reg, val0);

		val0 = *pUVTable++;
		val1 = *pUVTable++;
		val0 &= 0x0f;
		val1 &= 0x0f;
		val0 |= val1 << 4;
		reg_w(sd, reg + size, val0);

		reg++;
	पूर्ण
पूर्ण

/* This initializes the OV511/OV511+ and the sensor */
अटल व्योम ov511_configure(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/* For 511 and 511+ */
	अटल स्थिर काष्ठा ov_regvals init_511[] = अणु
		अणु R51x_SYS_RESET,	0x7f पूर्ण,
		अणु R51x_SYS_INIT,	0x01 पूर्ण,
		अणु R51x_SYS_RESET,	0x7f पूर्ण,
		अणु R51x_SYS_INIT,	0x01 पूर्ण,
		अणु R51x_SYS_RESET,	0x3f पूर्ण,
		अणु R51x_SYS_INIT,	0x01 पूर्ण,
		अणु R51x_SYS_RESET,	0x3d पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा ov_regvals norm_511[] = अणु
		अणु R511_DRAM_FLOW_CTL,	0x01 पूर्ण,
		अणु R51x_SYS_SNAP,	0x00 पूर्ण,
		अणु R51x_SYS_SNAP,	0x02 पूर्ण,
		अणु R51x_SYS_SNAP,	0x00 पूर्ण,
		अणु R511_FIFO_OPTS,	0x1f पूर्ण,
		अणु R511_COMP_EN,		0x00 पूर्ण,
		अणु R511_COMP_LUT_EN,	0x03 पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा ov_regvals norm_511_p[] = अणु
		अणु R511_DRAM_FLOW_CTL,	0xff पूर्ण,
		अणु R51x_SYS_SNAP,	0x00 पूर्ण,
		अणु R51x_SYS_SNAP,	0x02 पूर्ण,
		अणु R51x_SYS_SNAP,	0x00 पूर्ण,
		अणु R511_FIFO_OPTS,	0xff पूर्ण,
		अणु R511_COMP_EN,		0x00 पूर्ण,
		अणु R511_COMP_LUT_EN,	0x03 पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा ov_regvals compress_511[] = अणु
		अणु 0x70, 0x1f पूर्ण,
		अणु 0x71, 0x05 पूर्ण,
		अणु 0x72, 0x06 पूर्ण,
		अणु 0x73, 0x06 पूर्ण,
		अणु 0x74, 0x14 पूर्ण,
		अणु 0x75, 0x03 पूर्ण,
		अणु 0x76, 0x04 पूर्ण,
		अणु 0x77, 0x04 पूर्ण,
	पूर्ण;

	gspca_dbg(gspca_dev, D_PROBE, "Device custom id %x\n",
		  reg_r(sd, R51x_SYS_CUST_ID));

	ग_लिखो_regvals(sd, init_511, ARRAY_SIZE(init_511));

	चयन (sd->bridge) अणु
	हाल BRIDGE_OV511:
		ग_लिखो_regvals(sd, norm_511, ARRAY_SIZE(norm_511));
		अवरोध;
	हाल BRIDGE_OV511PLUS:
		ग_लिखो_regvals(sd, norm_511_p, ARRAY_SIZE(norm_511_p));
		अवरोध;
	पूर्ण

	/* Init compression */
	ग_लिखो_regvals(sd, compress_511, ARRAY_SIZE(compress_511));

	ov51x_upload_quan_tables(sd);
पूर्ण

/* This initializes the OV518/OV518+ and the sensor */
अटल व्योम ov518_configure(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/* For 518 and 518+ */
	अटल स्थिर काष्ठा ov_regvals init_518[] = अणु
		अणु R51x_SYS_RESET,	0x40 पूर्ण,
		अणु R51x_SYS_INIT,	0xe1 पूर्ण,
		अणु R51x_SYS_RESET,	0x3e पूर्ण,
		अणु R51x_SYS_INIT,	0xe1 पूर्ण,
		अणु R51x_SYS_RESET,	0x00 पूर्ण,
		अणु R51x_SYS_INIT,	0xe1 पूर्ण,
		अणु 0x46,			0x00 पूर्ण,
		अणु 0x5d,			0x03 पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा ov_regvals norm_518[] = अणु
		अणु R51x_SYS_SNAP,	0x02 पूर्ण, /* Reset */
		अणु R51x_SYS_SNAP,	0x01 पूर्ण, /* Enable */
		अणु 0x31,			0x0f पूर्ण,
		अणु 0x5d,			0x03 पूर्ण,
		अणु 0x24,			0x9f पूर्ण,
		अणु 0x25,			0x90 पूर्ण,
		अणु 0x20,			0x00 पूर्ण,
		अणु 0x51,			0x04 पूर्ण,
		अणु 0x71,			0x19 पूर्ण,
		अणु 0x2f,			0x80 पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा ov_regvals norm_518_p[] = अणु
		अणु R51x_SYS_SNAP,	0x02 पूर्ण, /* Reset */
		अणु R51x_SYS_SNAP,	0x01 पूर्ण, /* Enable */
		अणु 0x31,			0x0f पूर्ण,
		अणु 0x5d,			0x03 पूर्ण,
		अणु 0x24,			0x9f पूर्ण,
		अणु 0x25,			0x90 पूर्ण,
		अणु 0x20,			0x60 पूर्ण,
		अणु 0x51,			0x02 पूर्ण,
		अणु 0x71,			0x19 पूर्ण,
		अणु 0x40,			0xff पूर्ण,
		अणु 0x41,			0x42 पूर्ण,
		अणु 0x46,			0x00 पूर्ण,
		अणु 0x33,			0x04 पूर्ण,
		अणु 0x21,			0x19 पूर्ण,
		अणु 0x3f,			0x10 पूर्ण,
		अणु 0x2f,			0x80 पूर्ण,
	पूर्ण;

	/* First 5 bits of custom ID reg are a revision ID on OV518 */
	sd->revision = reg_r(sd, R51x_SYS_CUST_ID) & 0x1f;
	gspca_dbg(gspca_dev, D_PROBE, "Device revision %d\n", sd->revision);

	ग_लिखो_regvals(sd, init_518, ARRAY_SIZE(init_518));

	/* Set LED GPIO pin to output mode */
	reg_w_mask(sd, R518_GPIO_CTL, 0x00, 0x02);

	चयन (sd->bridge) अणु
	हाल BRIDGE_OV518:
		ग_लिखो_regvals(sd, norm_518, ARRAY_SIZE(norm_518));
		अवरोध;
	हाल BRIDGE_OV518PLUS:
		ग_लिखो_regvals(sd, norm_518_p, ARRAY_SIZE(norm_518_p));
		अवरोध;
	पूर्ण

	ov51x_upload_quan_tables(sd);

	reg_w(sd, 0x2f, 0x80);
पूर्ण

अटल व्योम ov519_configure(काष्ठा sd *sd)
अणु
	अटल स्थिर काष्ठा ov_regvals init_519[] = अणु
		अणु 0x5a, 0x6d पूर्ण, /* EnableSystem */
		अणु 0x53, 0x9b पूर्ण, /* करोn't enable the microcontroller */
		अणु OV519_R54_EN_CLK1, 0xff पूर्ण, /* set bit2 to enable jpeg */
		अणु 0x5d, 0x03 पूर्ण,
		अणु 0x49, 0x01 पूर्ण,
		अणु 0x48, 0x00 पूर्ण,
		/* Set LED pin to output mode. Bit 4 must be cleared or sensor
		 * detection will fail. This deserves further investigation. */
		अणु OV519_GPIO_IO_CTRL0,   0xee पूर्ण,
		अणु OV519_R51_RESET1, 0x0f पूर्ण,
		अणु OV519_R51_RESET1, 0x00 पूर्ण,
		अणु 0x22, 0x00 पूर्ण,
		/* winकरोws पढ़ोs 0x55 at this poपूर्णांक*/
	पूर्ण;

	ग_लिखो_regvals(sd, init_519, ARRAY_SIZE(init_519));
पूर्ण

अटल व्योम ovfx2_configure(काष्ठा sd *sd)
अणु
	अटल स्थिर काष्ठा ov_regvals init_fx2[] = अणु
		अणु 0x00, 0x60 पूर्ण,
		अणु 0x02, 0x01 पूर्ण,
		अणु 0x0f, 0x1d पूर्ण,
		अणु 0xe9, 0x82 पूर्ण,
		अणु 0xea, 0xc7 पूर्ण,
		अणु 0xeb, 0x10 पूर्ण,
		अणु 0xec, 0xf6 पूर्ण,
	पूर्ण;

	sd->stopped = 1;

	ग_लिखो_regvals(sd, init_fx2, ARRAY_SIZE(init_fx2));
पूर्ण

/* set the mode */
/* This function works क्रम ov7660 only */
अटल व्योम ov519_set_mode(काष्ठा sd *sd)
अणु
	अटल स्थिर काष्ठा ov_regvals bridge_ov7660[2][10] = अणु
		अणुअणु0x10, 0x14पूर्ण, अणु0x11, 0x1eपूर्ण, अणु0x12, 0x00पूर्ण, अणु0x13, 0x00पूर्ण,
		 अणु0x14, 0x00पूर्ण, अणु0x15, 0x00पूर्ण, अणु0x16, 0x00पूर्ण, अणु0x20, 0x0cपूर्ण,
		 अणु0x25, 0x01पूर्ण, अणु0x26, 0x00पूर्णपूर्ण,
		अणुअणु0x10, 0x28पूर्ण, अणु0x11, 0x3cपूर्ण, अणु0x12, 0x00पूर्ण, अणु0x13, 0x00पूर्ण,
		 अणु0x14, 0x00पूर्ण, अणु0x15, 0x00पूर्ण, अणु0x16, 0x00पूर्ण, अणु0x20, 0x0cपूर्ण,
		 अणु0x25, 0x03पूर्ण, अणु0x26, 0x00पूर्णपूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा ov_i2c_regvals sensor_ov7660[2][3] = अणु
		अणुअणु0x12, 0x00पूर्ण, अणु0x24, 0x00पूर्ण, अणु0x0c, 0x0cपूर्णपूर्ण,
		अणुअणु0x12, 0x00पूर्ण, अणु0x04, 0x00पूर्ण, अणु0x0c, 0x00पूर्णपूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा ov_i2c_regvals sensor_ov7660_2[] = अणु
		अणुOV7670_R17_HSTART, 0x13पूर्ण,
		अणुOV7670_R18_HSTOP, 0x01पूर्ण,
		अणुOV7670_R32_HREF, 0x92पूर्ण,
		अणुOV7670_R19_VSTART, 0x02पूर्ण,
		अणुOV7670_R1A_VSTOP, 0x7aपूर्ण,
		अणुOV7670_R03_VREF, 0x00पूर्ण,
/*		अणु0x33, 0x00पूर्ण, */
/*		अणु0x34, 0x07पूर्ण, */
/*		अणु0x36, 0x00पूर्ण, */
/*		अणु0x6b, 0x0aपूर्ण, */
	पूर्ण;

	ग_लिखो_regvals(sd, bridge_ov7660[sd->gspca_dev.curr_mode],
			ARRAY_SIZE(bridge_ov7660[0]));
	ग_लिखो_i2c_regvals(sd, sensor_ov7660[sd->gspca_dev.curr_mode],
			ARRAY_SIZE(sensor_ov7660[0]));
	ग_लिखो_i2c_regvals(sd, sensor_ov7660_2,
			ARRAY_SIZE(sensor_ov7660_2));
पूर्ण

/* set the frame rate */
/* This function works क्रम sensors ov7640, ov7648 ov7660 and ov7670 only */
अटल व्योम ov519_set_fr(काष्ठा sd *sd)
अणु
	पूर्णांक fr;
	u8 घड़ी;
	/* frame rate table with indices:
	 *	- mode = 0: 320x240, 1: 640x480
	 *	- fr rate = 0: 30, 1: 25, 2: 20, 3: 15, 4: 10, 5: 5
	 *	- reg = 0: bridge a4, 1: bridge 23, 2: sensor 11 (घड़ी)
	 */
	अटल स्थिर u8 fr_tb[2][6][3] = अणु
		अणुअणु0x04, 0xff, 0x00पूर्ण,
		 अणु0x04, 0x1f, 0x00पूर्ण,
		 अणु0x04, 0x1b, 0x00पूर्ण,
		 अणु0x04, 0x15, 0x00पूर्ण,
		 अणु0x04, 0x09, 0x00पूर्ण,
		 अणु0x04, 0x01, 0x00पूर्णपूर्ण,
		अणुअणु0x0c, 0xff, 0x00पूर्ण,
		 अणु0x0c, 0x1f, 0x00पूर्ण,
		 अणु0x0c, 0x1b, 0x00पूर्ण,
		 अणु0x04, 0xff, 0x01पूर्ण,
		 अणु0x04, 0x1f, 0x01पूर्ण,
		 अणु0x04, 0x1b, 0x01पूर्णपूर्ण,
	पूर्ण;

	अगर (frame_rate > 0)
		sd->frame_rate = frame_rate;
	अगर (sd->frame_rate >= 30)
		fr = 0;
	अन्यथा अगर (sd->frame_rate >= 25)
		fr = 1;
	अन्यथा अगर (sd->frame_rate >= 20)
		fr = 2;
	अन्यथा अगर (sd->frame_rate >= 15)
		fr = 3;
	अन्यथा अगर (sd->frame_rate >= 10)
		fr = 4;
	अन्यथा
		fr = 5;
	reg_w(sd, 0xa4, fr_tb[sd->gspca_dev.curr_mode][fr][0]);
	reg_w(sd, 0x23, fr_tb[sd->gspca_dev.curr_mode][fr][1]);
	घड़ी = fr_tb[sd->gspca_dev.curr_mode][fr][2];
	अगर (sd->sensor == SEN_OV7660)
		घड़ी |= 0x80;		/* enable द्विगुन घड़ी */
	ov518_i2c_w(sd, OV7670_R11_CLKRC, घड़ी);
पूर्ण

अटल व्योम setस्वतःgain(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	i2c_w_mask(sd, 0x13, val ? 0x05 : 0x00, 0x05);
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam = &gspca_dev->cam;

	sd->bridge = id->driver_info & BRIDGE_MASK;
	sd->invert_led = (id->driver_info & BRIDGE_INVERT_LED) != 0;

	चयन (sd->bridge) अणु
	हाल BRIDGE_OV511:
	हाल BRIDGE_OV511PLUS:
		cam->cam_mode = ov511_vga_mode;
		cam->nmodes = ARRAY_SIZE(ov511_vga_mode);
		अवरोध;
	हाल BRIDGE_OV518:
	हाल BRIDGE_OV518PLUS:
		cam->cam_mode = ov518_vga_mode;
		cam->nmodes = ARRAY_SIZE(ov518_vga_mode);
		अवरोध;
	हाल BRIDGE_OV519:
		cam->cam_mode = ov519_vga_mode;
		cam->nmodes = ARRAY_SIZE(ov519_vga_mode);
		अवरोध;
	हाल BRIDGE_OVFX2:
		cam->cam_mode = ov519_vga_mode;
		cam->nmodes = ARRAY_SIZE(ov519_vga_mode);
		cam->bulk_size = OVFX2_BULK_SIZE;
		cam->bulk_nurbs = MAX_NURBS;
		cam->bulk = 1;
		अवरोध;
	हाल BRIDGE_W9968CF:
		cam->cam_mode = w9968cf_vga_mode;
		cam->nmodes = ARRAY_SIZE(w9968cf_vga_mode);
		अवरोध;
	पूर्ण

	sd->frame_rate = 15;

	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam = &gspca_dev->cam;

	चयन (sd->bridge) अणु
	हाल BRIDGE_OV511:
	हाल BRIDGE_OV511PLUS:
		ov511_configure(gspca_dev);
		अवरोध;
	हाल BRIDGE_OV518:
	हाल BRIDGE_OV518PLUS:
		ov518_configure(gspca_dev);
		अवरोध;
	हाल BRIDGE_OV519:
		ov519_configure(sd);
		अवरोध;
	हाल BRIDGE_OVFX2:
		ovfx2_configure(sd);
		अवरोध;
	हाल BRIDGE_W9968CF:
		w9968cf_configure(sd);
		अवरोध;
	पूर्ण

	/* The OV519 must be more aggressive about sensor detection since
	 * I2C ग_लिखो will never fail अगर the sensor is not present. We have
	 * to try to initialize the sensor to detect its presence */
	sd->sensor = -1;

	/* Test क्रम 76xx */
	अगर (init_ov_sensor(sd, OV7xx0_SID) >= 0) अणु
		ov7xx0_configure(sd);

	/* Test क्रम 6xx0 */
	पूर्ण अन्यथा अगर (init_ov_sensor(sd, OV6xx0_SID) >= 0) अणु
		ov6xx0_configure(sd);

	/* Test क्रम 8xx0 */
	पूर्ण अन्यथा अगर (init_ov_sensor(sd, OV8xx0_SID) >= 0) अणु
		ov8xx0_configure(sd);

	/* Test क्रम 3xxx / 2xxx */
	पूर्ण अन्यथा अगर (init_ov_sensor(sd, OV_HIRES_SID) >= 0) अणु
		ov_hires_configure(sd);
	पूर्ण अन्यथा अणु
		gspca_err(gspca_dev, "Can't determine sensor slave IDs\n");
		जाओ error;
	पूर्ण

	अगर (sd->sensor < 0)
		जाओ error;

	ov51x_led_control(sd, 0);	/* turn LED off */

	चयन (sd->bridge) अणु
	हाल BRIDGE_OV511:
	हाल BRIDGE_OV511PLUS:
		अगर (sd->sअगर) अणु
			cam->cam_mode = ov511_sअगर_mode;
			cam->nmodes = ARRAY_SIZE(ov511_sअगर_mode);
		पूर्ण
		अवरोध;
	हाल BRIDGE_OV518:
	हाल BRIDGE_OV518PLUS:
		अगर (sd->sअगर) अणु
			cam->cam_mode = ov518_sअगर_mode;
			cam->nmodes = ARRAY_SIZE(ov518_sअगर_mode);
		पूर्ण
		अवरोध;
	हाल BRIDGE_OV519:
		अगर (sd->sअगर) अणु
			cam->cam_mode = ov519_sअगर_mode;
			cam->nmodes = ARRAY_SIZE(ov519_sअगर_mode);
		पूर्ण
		अवरोध;
	हाल BRIDGE_OVFX2:
		चयन (sd->sensor) अणु
		हाल SEN_OV2610:
		हाल SEN_OV2610AE:
			cam->cam_mode = ovfx2_ov2610_mode;
			cam->nmodes = ARRAY_SIZE(ovfx2_ov2610_mode);
			अवरोध;
		हाल SEN_OV3610:
			cam->cam_mode = ovfx2_ov3610_mode;
			cam->nmodes = ARRAY_SIZE(ovfx2_ov3610_mode);
			अवरोध;
		हाल SEN_OV9600:
			cam->cam_mode = ovfx2_ov9600_mode;
			cam->nmodes = ARRAY_SIZE(ovfx2_ov9600_mode);
			अवरोध;
		शेष:
			अगर (sd->sअगर) अणु
				cam->cam_mode = ov519_sअगर_mode;
				cam->nmodes = ARRAY_SIZE(ov519_sअगर_mode);
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;
	हाल BRIDGE_W9968CF:
		अगर (sd->sअगर)
			cam->nmodes = ARRAY_SIZE(w9968cf_vga_mode) - 1;

		/* w9968cf needs initialisation once the sensor is known */
		w9968cf_init(sd);
		अवरोध;
	पूर्ण

	/* initialize the sensor */
	चयन (sd->sensor) अणु
	हाल SEN_OV2610:
		ग_लिखो_i2c_regvals(sd, norm_2610, ARRAY_SIZE(norm_2610));

		/* Enable स्वतःgain, स्वतःexpo, awb, bandfilter */
		i2c_w_mask(sd, 0x13, 0x27, 0x27);
		अवरोध;
	हाल SEN_OV2610AE:
		ग_लिखो_i2c_regvals(sd, norm_2610ae, ARRAY_SIZE(norm_2610ae));

		/* enable स्वतःexpo */
		i2c_w_mask(sd, 0x13, 0x05, 0x05);
		अवरोध;
	हाल SEN_OV3610:
		ग_लिखो_i2c_regvals(sd, norm_3620b, ARRAY_SIZE(norm_3620b));

		/* Enable स्वतःgain, स्वतःexpo, awb, bandfilter */
		i2c_w_mask(sd, 0x13, 0x27, 0x27);
		अवरोध;
	हाल SEN_OV6620:
		ग_लिखो_i2c_regvals(sd, norm_6x20, ARRAY_SIZE(norm_6x20));
		अवरोध;
	हाल SEN_OV6630:
	हाल SEN_OV66308AF:
		ग_लिखो_i2c_regvals(sd, norm_6x30, ARRAY_SIZE(norm_6x30));
		अवरोध;
	शेष:
/*	हाल SEN_OV7610: */
/*	हाल SEN_OV76BE: */
		ग_लिखो_i2c_regvals(sd, norm_7610, ARRAY_SIZE(norm_7610));
		i2c_w_mask(sd, 0x0e, 0x00, 0x40);
		अवरोध;
	हाल SEN_OV7620:
	हाल SEN_OV7620AE:
		ग_लिखो_i2c_regvals(sd, norm_7620, ARRAY_SIZE(norm_7620));
		अवरोध;
	हाल SEN_OV7640:
	हाल SEN_OV7648:
		ग_लिखो_i2c_regvals(sd, norm_7640, ARRAY_SIZE(norm_7640));
		अवरोध;
	हाल SEN_OV7660:
		i2c_w(sd, OV7670_R12_COM7, OV7670_COM7_RESET);
		msleep(14);
		reg_w(sd, OV519_R57_SNAPSHOT, 0x23);
		ग_लिखो_regvals(sd, init_519_ov7660,
				ARRAY_SIZE(init_519_ov7660));
		ग_लिखो_i2c_regvals(sd, norm_7660, ARRAY_SIZE(norm_7660));
		sd->gspca_dev.curr_mode = 1;	/* 640x480 */
		ov519_set_mode(sd);
		ov519_set_fr(sd);
		sd_reset_snapshot(gspca_dev);
		ov51x_restart(sd);
		ov51x_stop(sd);			/* not in win traces */
		ov51x_led_control(sd, 0);
		अवरोध;
	हाल SEN_OV7670:
		ग_लिखो_i2c_regvals(sd, norm_7670, ARRAY_SIZE(norm_7670));
		अवरोध;
	हाल SEN_OV8610:
		ग_लिखो_i2c_regvals(sd, norm_8610, ARRAY_SIZE(norm_8610));
		अवरोध;
	हाल SEN_OV9600:
		ग_लिखो_i2c_regvals(sd, norm_9600, ARRAY_SIZE(norm_9600));

		/* enable स्वतःexpo */
/*		i2c_w_mask(sd, 0x13, 0x05, 0x05); */
		अवरोध;
	पूर्ण
	वापस gspca_dev->usb_err;
error:
	gspca_err(gspca_dev, "OV519 Config failed\n");
	वापस -EINVAL;
पूर्ण

/* function called at start समय beक्रमe URB creation */
अटल पूर्णांक sd_isoc_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	चयन (sd->bridge) अणु
	हाल BRIDGE_OVFX2:
		अगर (gspca_dev->pixfmt.width != 800)
			gspca_dev->cam.bulk_size = OVFX2_BULK_SIZE;
		अन्यथा
			gspca_dev->cam.bulk_size = 7 * 4096;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* Set up the OV511/OV511+ with the given image parameters.
 *
 * Do not put any sensor-specअगरic code in here (including I2C I/O functions)
 */
अटल व्योम ov511_mode_init_regs(काष्ठा sd *sd)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक hsegs, vsegs, packet_size, fps, needed;
	पूर्णांक पूर्णांकerlaced = 0;
	काष्ठा usb_host_पूर्णांकerface *alt;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;

	पूर्णांकf = usb_अगरnum_to_अगर(sd->gspca_dev.dev, sd->gspca_dev.अगरace);
	alt = usb_altnum_to_altsetting(पूर्णांकf, sd->gspca_dev.alt);
	अगर (!alt) अणु
		gspca_err(gspca_dev, "Couldn't get altsetting\n");
		sd->gspca_dev.usb_err = -EIO;
		वापस;
	पूर्ण

	अगर (alt->desc.bNumEndpoपूर्णांकs < 1) अणु
		sd->gspca_dev.usb_err = -ENODEV;
		वापस;
	पूर्ण

	packet_size = le16_to_cpu(alt->endpoपूर्णांक[0].desc.wMaxPacketSize);
	reg_w(sd, R51x_FIFO_PSIZE, packet_size >> 5);

	reg_w(sd, R511_CAM_UV_EN, 0x01);
	reg_w(sd, R511_SNAP_UV_EN, 0x01);
	reg_w(sd, R511_SNAP_OPTS, 0x03);

	/* Here I'm assuming that snapshot size == image size.
	 * I hope that's always true. --claudio
	 */
	hsegs = (sd->gspca_dev.pixfmt.width >> 3) - 1;
	vsegs = (sd->gspca_dev.pixfmt.height >> 3) - 1;

	reg_w(sd, R511_CAM_PXCNT, hsegs);
	reg_w(sd, R511_CAM_LNCNT, vsegs);
	reg_w(sd, R511_CAM_PXDIV, 0x00);
	reg_w(sd, R511_CAM_LNDIV, 0x00);

	/* YUV420, low pass filter on */
	reg_w(sd, R511_CAM_OPTS, 0x03);

	/* Snapshot additions */
	reg_w(sd, R511_SNAP_PXCNT, hsegs);
	reg_w(sd, R511_SNAP_LNCNT, vsegs);
	reg_w(sd, R511_SNAP_PXDIV, 0x00);
	reg_w(sd, R511_SNAP_LNDIV, 0x00);

	/******** Set the framerate ********/
	अगर (frame_rate > 0)
		sd->frame_rate = frame_rate;

	चयन (sd->sensor) अणु
	हाल SEN_OV6620:
		/* No framerate control, करोesn't like higher rates yet */
		sd->घड़ीभाग = 3;
		अवरोध;

	/* Note once the FIXME's in mode_init_ov_sensor_regs() are fixed
	   क्रम more sensors we need to करो this क्रम them too */
	हाल SEN_OV7620:
	हाल SEN_OV7620AE:
	हाल SEN_OV7640:
	हाल SEN_OV7648:
	हाल SEN_OV76BE:
		अगर (sd->gspca_dev.pixfmt.width == 320)
			पूर्णांकerlaced = 1;
		fallthrough;
	हाल SEN_OV6630:
	हाल SEN_OV7610:
	हाल SEN_OV7670:
		चयन (sd->frame_rate) अणु
		हाल 30:
		हाल 25:
			/* Not enough bandwidth to करो 640x480 @ 30 fps */
			अगर (sd->gspca_dev.pixfmt.width != 640) अणु
				sd->घड़ीभाग = 0;
				अवरोध;
			पूर्ण
			/* For 640x480 हाल */
			fallthrough;
		शेष:
/*		हाल 20: */
/*		हाल 15: */
			sd->घड़ीभाग = 1;
			अवरोध;
		हाल 10:
			sd->घड़ीभाग = 2;
			अवरोध;
		हाल 5:
			sd->घड़ीभाग = 5;
			अवरोध;
		पूर्ण
		अगर (पूर्णांकerlaced) अणु
			sd->घड़ीभाग = (sd->घड़ीभाग + 1) * 2 - 1;
			/* Higher then 10 करोes not work */
			अगर (sd->घड़ीभाग > 10)
				sd->घड़ीभाग = 10;
		पूर्ण
		अवरोध;

	हाल SEN_OV8610:
		/* No framerate control ?? */
		sd->घड़ीभाग = 0;
		अवरोध;
	पूर्ण

	/* Check अगर we have enough bandwidth to disable compression */
	fps = (पूर्णांकerlaced ? 60 : 30) / (sd->घड़ीभाग + 1) + 1;
	needed = fps * sd->gspca_dev.pixfmt.width *
			sd->gspca_dev.pixfmt.height * 3 / 2;
	/* 1000 isoc packets/sec */
	अगर (needed > 1000 * packet_size) अणु
		/* Enable Y and UV quantization and compression */
		reg_w(sd, R511_COMP_EN, 0x07);
		reg_w(sd, R511_COMP_LUT_EN, 0x03);
	पूर्ण अन्यथा अणु
		reg_w(sd, R511_COMP_EN, 0x06);
		reg_w(sd, R511_COMP_LUT_EN, 0x00);
	पूर्ण

	reg_w(sd, R51x_SYS_RESET, OV511_RESET_OMNICE);
	reg_w(sd, R51x_SYS_RESET, 0);
पूर्ण

/* Sets up the OV518/OV518+ with the given image parameters
 *
 * OV518 needs a completely dअगरferent approach, until we can figure out what
 * the inभागidual रेजिस्टरs करो. Also, only 15 FPS is supported now.
 *
 * Do not put any sensor-specअगरic code in here (including I2C I/O functions)
 */
अटल व्योम ov518_mode_init_regs(काष्ठा sd *sd)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक hsegs, vsegs, packet_size;
	काष्ठा usb_host_पूर्णांकerface *alt;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;

	पूर्णांकf = usb_अगरnum_to_अगर(sd->gspca_dev.dev, sd->gspca_dev.अगरace);
	alt = usb_altnum_to_altsetting(पूर्णांकf, sd->gspca_dev.alt);
	अगर (!alt) अणु
		gspca_err(gspca_dev, "Couldn't get altsetting\n");
		sd->gspca_dev.usb_err = -EIO;
		वापस;
	पूर्ण

	अगर (alt->desc.bNumEndpoपूर्णांकs < 1) अणु
		sd->gspca_dev.usb_err = -ENODEV;
		वापस;
	पूर्ण

	packet_size = le16_to_cpu(alt->endpoपूर्णांक[0].desc.wMaxPacketSize);
	ov518_reg_w32(sd, R51x_FIFO_PSIZE, packet_size & ~7, 2);

	/******** Set the mode ********/
	reg_w(sd, 0x2b, 0);
	reg_w(sd, 0x2c, 0);
	reg_w(sd, 0x2d, 0);
	reg_w(sd, 0x2e, 0);
	reg_w(sd, 0x3b, 0);
	reg_w(sd, 0x3c, 0);
	reg_w(sd, 0x3d, 0);
	reg_w(sd, 0x3e, 0);

	अगर (sd->bridge == BRIDGE_OV518) अणु
		/* Set 8-bit (YVYU) input क्रमmat */
		reg_w_mask(sd, 0x20, 0x08, 0x08);

		/* Set 12-bit (4:2:0) output क्रमmat */
		reg_w_mask(sd, 0x28, 0x80, 0xf0);
		reg_w_mask(sd, 0x38, 0x80, 0xf0);
	पूर्ण अन्यथा अणु
		reg_w(sd, 0x28, 0x80);
		reg_w(sd, 0x38, 0x80);
	पूर्ण

	hsegs = sd->gspca_dev.pixfmt.width / 16;
	vsegs = sd->gspca_dev.pixfmt.height / 4;

	reg_w(sd, 0x29, hsegs);
	reg_w(sd, 0x2a, vsegs);

	reg_w(sd, 0x39, hsegs);
	reg_w(sd, 0x3a, vsegs);

	/* Winकरोws driver करोes this here; who knows why */
	reg_w(sd, 0x2f, 0x80);

	/******** Set the framerate ********/
	अगर (sd->bridge == BRIDGE_OV518PLUS && sd->revision == 0 &&
					      sd->sensor == SEN_OV7620AE)
		sd->घड़ीभाग = 0;
	अन्यथा
		sd->घड़ीभाग = 1;

	/* Mode independent, but framerate dependent, regs */
	/* 0x51: Clock भागider; Only works on some cams which use 2 crystals */
	reg_w(sd, 0x51, 0x04);
	reg_w(sd, 0x22, 0x18);
	reg_w(sd, 0x23, 0xff);

	अगर (sd->bridge == BRIDGE_OV518PLUS) अणु
		चयन (sd->sensor) अणु
		हाल SEN_OV7620AE:
			/*
			 * HdG: 640x480 needs special handling on device
			 * revision 2, we check क्रम device revision > 0 to
			 * aव्योम regressions, as we करोn't know the correct
			 * thing toकरो क्रम revision 1.
			 *
			 * Also this likely means we करोn't need to
			 * dअगरferentiate between the OV7620 and OV7620AE,
			 * earlier testing hitting this same problem likely
			 * happened to be with revision < 2 cams using an
			 * OV7620 and revision 2 cams using an OV7620AE.
			 */
			अगर (sd->revision > 0 &&
					sd->gspca_dev.pixfmt.width == 640) अणु
				reg_w(sd, 0x20, 0x60);
				reg_w(sd, 0x21, 0x1f);
			पूर्ण अन्यथा अणु
				reg_w(sd, 0x20, 0x00);
				reg_w(sd, 0x21, 0x19);
			पूर्ण
			अवरोध;
		हाल SEN_OV7620:
			reg_w(sd, 0x20, 0x00);
			reg_w(sd, 0x21, 0x19);
			अवरोध;
		शेष:
			reg_w(sd, 0x21, 0x19);
		पूर्ण
	पूर्ण अन्यथा
		reg_w(sd, 0x71, 0x17);	/* Compression-related? */

	/* FIXME: Sensor-specअगरic */
	/* Bit 5 is what matters here. Of course, it is "reserved" */
	i2c_w(sd, 0x54, 0x23);

	reg_w(sd, 0x2f, 0x80);

	अगर (sd->bridge == BRIDGE_OV518PLUS) अणु
		reg_w(sd, 0x24, 0x94);
		reg_w(sd, 0x25, 0x90);
		ov518_reg_w32(sd, 0xc4,    400, 2);	/* 190h   */
		ov518_reg_w32(sd, 0xc6,    540, 2);	/* 21ch   */
		ov518_reg_w32(sd, 0xc7,    540, 2);	/* 21ch   */
		ov518_reg_w32(sd, 0xc8,    108, 2);	/* 6ch    */
		ov518_reg_w32(sd, 0xca, 131098, 3);	/* 2001ah */
		ov518_reg_w32(sd, 0xcb,    532, 2);	/* 214h   */
		ov518_reg_w32(sd, 0xcc,   2400, 2);	/* 960h   */
		ov518_reg_w32(sd, 0xcd,     32, 2);	/* 20h    */
		ov518_reg_w32(sd, 0xce,    608, 2);	/* 260h   */
	पूर्ण अन्यथा अणु
		reg_w(sd, 0x24, 0x9f);
		reg_w(sd, 0x25, 0x90);
		ov518_reg_w32(sd, 0xc4,    400, 2);	/* 190h   */
		ov518_reg_w32(sd, 0xc6,    381, 2);	/* 17dh   */
		ov518_reg_w32(sd, 0xc7,    381, 2);	/* 17dh   */
		ov518_reg_w32(sd, 0xc8,    128, 2);	/* 80h    */
		ov518_reg_w32(sd, 0xca, 183331, 3);	/* 2cc23h */
		ov518_reg_w32(sd, 0xcb,    746, 2);	/* 2eah   */
		ov518_reg_w32(sd, 0xcc,   1750, 2);	/* 6d6h   */
		ov518_reg_w32(sd, 0xcd,     45, 2);	/* 2dh    */
		ov518_reg_w32(sd, 0xce,    851, 2);	/* 353h   */
	पूर्ण

	reg_w(sd, 0x2f, 0x80);
पूर्ण

/* Sets up the OV519 with the given image parameters
 *
 * OV519 needs a completely dअगरferent approach, until we can figure out what
 * the inभागidual रेजिस्टरs करो.
 *
 * Do not put any sensor-specअगरic code in here (including I2C I/O functions)
 */
अटल व्योम ov519_mode_init_regs(काष्ठा sd *sd)
अणु
	अटल स्थिर काष्ठा ov_regvals mode_init_519_ov7670[] = अणु
		अणु 0x5d,	0x03 पूर्ण, /* Turn off suspend mode */
		अणु 0x53,	0x9f पूर्ण, /* was 9b in 1.65-1.08 */
		अणु OV519_R54_EN_CLK1, 0x0f पूर्ण, /* bit2 (jpeg enable) */
		अणु 0xa2,	0x20 पूर्ण, /* a2-a5 are unकरोcumented */
		अणु 0xa3,	0x18 पूर्ण,
		अणु 0xa4,	0x04 पूर्ण,
		अणु 0xa5,	0x28 पूर्ण,
		अणु 0x37,	0x00 पूर्ण,	/* SetUsbInit */
		अणु 0x55,	0x02 पूर्ण, /* 4.096 Mhz audio घड़ी */
		/* Enable both fields, YUV Input, disable defect comp (why?) */
		अणु 0x20,	0x0c पूर्ण,
		अणु 0x21,	0x38 पूर्ण,
		अणु 0x22,	0x1d पूर्ण,
		अणु 0x17,	0x50 पूर्ण, /* unकरोcumented */
		अणु 0x37,	0x00 पूर्ण, /* unकरोcumented */
		अणु 0x40,	0xff पूर्ण, /* I2C समयout counter */
		अणु 0x46,	0x00 पूर्ण, /* I2C घड़ी prescaler */
		अणु 0x59,	0x04 पूर्ण,	/* new from windrv 090403 */
		अणु 0xff,	0x00 पूर्ण, /* unकरोcumented */
		/* winकरोws पढ़ोs 0x55 at this poपूर्णांक, why? */
	पूर्ण;

	अटल स्थिर काष्ठा ov_regvals mode_init_519[] = अणु
		अणु 0x5d,	0x03 पूर्ण, /* Turn off suspend mode */
		अणु 0x53,	0x9f पूर्ण, /* was 9b in 1.65-1.08 */
		अणु OV519_R54_EN_CLK1, 0x0f पूर्ण, /* bit2 (jpeg enable) */
		अणु 0xa2,	0x20 पूर्ण, /* a2-a5 are unकरोcumented */
		अणु 0xa3,	0x18 पूर्ण,
		अणु 0xa4,	0x04 पूर्ण,
		अणु 0xa5,	0x28 पूर्ण,
		अणु 0x37,	0x00 पूर्ण,	/* SetUsbInit */
		अणु 0x55,	0x02 पूर्ण, /* 4.096 Mhz audio घड़ी */
		/* Enable both fields, YUV Input, disable defect comp (why?) */
		अणु 0x22,	0x1d पूर्ण,
		अणु 0x17,	0x50 पूर्ण, /* unकरोcumented */
		अणु 0x37,	0x00 पूर्ण, /* unकरोcumented */
		अणु 0x40,	0xff पूर्ण, /* I2C समयout counter */
		अणु 0x46,	0x00 पूर्ण, /* I2C घड़ी prescaler */
		अणु 0x59,	0x04 पूर्ण,	/* new from windrv 090403 */
		अणु 0xff,	0x00 पूर्ण, /* unकरोcumented */
		/* winकरोws पढ़ोs 0x55 at this poपूर्णांक, why? */
	पूर्ण;

	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;

	/******** Set the mode ********/
	चयन (sd->sensor) अणु
	शेष:
		ग_लिखो_regvals(sd, mode_init_519, ARRAY_SIZE(mode_init_519));
		अगर (sd->sensor == SEN_OV7640 ||
		    sd->sensor == SEN_OV7648) अणु
			/* Select 8-bit input mode */
			reg_w_mask(sd, OV519_R20_DFR, 0x10, 0x10);
		पूर्ण
		अवरोध;
	हाल SEN_OV7660:
		वापस;		/* करोne by ov519_set_mode/fr() */
	हाल SEN_OV7670:
		ग_लिखो_regvals(sd, mode_init_519_ov7670,
				ARRAY_SIZE(mode_init_519_ov7670));
		अवरोध;
	पूर्ण

	reg_w(sd, OV519_R10_H_SIZE,	sd->gspca_dev.pixfmt.width >> 4);
	reg_w(sd, OV519_R11_V_SIZE,	sd->gspca_dev.pixfmt.height >> 3);
	अगर (sd->sensor == SEN_OV7670 &&
	    sd->gspca_dev.cam.cam_mode[sd->gspca_dev.curr_mode].priv)
		reg_w(sd, OV519_R12_X_OFFSETL, 0x04);
	अन्यथा अगर (sd->sensor == SEN_OV7648 &&
	    sd->gspca_dev.cam.cam_mode[sd->gspca_dev.curr_mode].priv)
		reg_w(sd, OV519_R12_X_OFFSETL, 0x01);
	अन्यथा
		reg_w(sd, OV519_R12_X_OFFSETL, 0x00);
	reg_w(sd, OV519_R13_X_OFFSETH,	0x00);
	reg_w(sd, OV519_R14_Y_OFFSETL,	0x00);
	reg_w(sd, OV519_R15_Y_OFFSETH,	0x00);
	reg_w(sd, OV519_R16_DIVIDER,	0x00);
	reg_w(sd, OV519_R25_FORMAT,	0x03); /* YUV422 */
	reg_w(sd, 0x26,			0x00); /* Unकरोcumented */

	/******** Set the framerate ********/
	अगर (frame_rate > 0)
		sd->frame_rate = frame_rate;

/* FIXME: These are only valid at the max resolution. */
	sd->घड़ीभाग = 0;
	चयन (sd->sensor) अणु
	हाल SEN_OV7640:
	हाल SEN_OV7648:
		चयन (sd->frame_rate) अणु
		शेष:
/*		हाल 30: */
			reg_w(sd, 0xa4, 0x0c);
			reg_w(sd, 0x23, 0xff);
			अवरोध;
		हाल 25:
			reg_w(sd, 0xa4, 0x0c);
			reg_w(sd, 0x23, 0x1f);
			अवरोध;
		हाल 20:
			reg_w(sd, 0xa4, 0x0c);
			reg_w(sd, 0x23, 0x1b);
			अवरोध;
		हाल 15:
			reg_w(sd, 0xa4, 0x04);
			reg_w(sd, 0x23, 0xff);
			sd->घड़ीभाग = 1;
			अवरोध;
		हाल 10:
			reg_w(sd, 0xa4, 0x04);
			reg_w(sd, 0x23, 0x1f);
			sd->घड़ीभाग = 1;
			अवरोध;
		हाल 5:
			reg_w(sd, 0xa4, 0x04);
			reg_w(sd, 0x23, 0x1b);
			sd->घड़ीभाग = 1;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SEN_OV8610:
		चयन (sd->frame_rate) अणु
		शेष:	/* 15 fps */
/*		हाल 15: */
			reg_w(sd, 0xa4, 0x06);
			reg_w(sd, 0x23, 0xff);
			अवरोध;
		हाल 10:
			reg_w(sd, 0xa4, 0x06);
			reg_w(sd, 0x23, 0x1f);
			अवरोध;
		हाल 5:
			reg_w(sd, 0xa4, 0x06);
			reg_w(sd, 0x23, 0x1b);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SEN_OV7670:		/* guesses, based on 7640 */
		gspca_dbg(gspca_dev, D_STREAM, "Setting framerate to %d fps\n",
			  (sd->frame_rate == 0) ? 15 : sd->frame_rate);
		reg_w(sd, 0xa4, 0x10);
		चयन (sd->frame_rate) अणु
		हाल 30:
			reg_w(sd, 0x23, 0xff);
			अवरोध;
		हाल 20:
			reg_w(sd, 0x23, 0x1b);
			अवरोध;
		शेष:
/*		हाल 15: */
			reg_w(sd, 0x23, 0xff);
			sd->घड़ीभाग = 1;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mode_init_ov_sensor_regs(काष्ठा sd *sd)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक qvga, xstart, xend, ystart, yend;
	u8 v;

	qvga = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv & 1;

	/******** Mode (VGA/QVGA) and sensor specअगरic regs ********/
	चयन (sd->sensor) अणु
	हाल SEN_OV2610:
		i2c_w_mask(sd, 0x14, qvga ? 0x20 : 0x00, 0x20);
		i2c_w_mask(sd, 0x28, qvga ? 0x00 : 0x20, 0x20);
		i2c_w(sd, 0x24, qvga ? 0x20 : 0x3a);
		i2c_w(sd, 0x25, qvga ? 0x30 : 0x60);
		i2c_w_mask(sd, 0x2d, qvga ? 0x40 : 0x00, 0x40);
		i2c_w_mask(sd, 0x67, qvga ? 0xf0 : 0x90, 0xf0);
		i2c_w_mask(sd, 0x74, qvga ? 0x20 : 0x00, 0x20);
		वापस;
	हाल SEN_OV2610AE: अणु
		u8 v;

		/* frame rates:
		 *	10fps / 5 fps क्रम 1600x1200
		 *	40fps / 20fps क्रम 800x600
		 */
		v = 80;
		अगर (qvga) अणु
			अगर (sd->frame_rate < 25)
				v = 0x81;
		पूर्ण अन्यथा अणु
			अगर (sd->frame_rate < 10)
				v = 0x81;
		पूर्ण
		i2c_w(sd, 0x11, v);
		i2c_w(sd, 0x12, qvga ? 0x60 : 0x20);
		वापस;
	    पूर्ण
	हाल SEN_OV3610:
		अगर (qvga) अणु
			xstart = (1040 - gspca_dev->pixfmt.width) / 2 +
				(0x1f << 4);
			ystart = (776 - gspca_dev->pixfmt.height) / 2;
		पूर्ण अन्यथा अणु
			xstart = (2076 - gspca_dev->pixfmt.width) / 2 +
				(0x10 << 4);
			ystart = (1544 - gspca_dev->pixfmt.height) / 2;
		पूर्ण
		xend = xstart + gspca_dev->pixfmt.width;
		yend = ystart + gspca_dev->pixfmt.height;
		/* Writing to the COMH रेजिस्टर resets the other winकरोwing regs
		   to their शेष values, so we must करो this first. */
		i2c_w_mask(sd, 0x12, qvga ? 0x40 : 0x00, 0xf0);
		i2c_w_mask(sd, 0x32,
			   (((xend >> 1) & 7) << 3) | ((xstart >> 1) & 7),
			   0x3f);
		i2c_w_mask(sd, 0x03,
			   (((yend >> 1) & 3) << 2) | ((ystart >> 1) & 3),
			   0x0f);
		i2c_w(sd, 0x17, xstart >> 4);
		i2c_w(sd, 0x18, xend >> 4);
		i2c_w(sd, 0x19, ystart >> 3);
		i2c_w(sd, 0x1a, yend >> 3);
		वापस;
	हाल SEN_OV8610:
		/* For OV8610 qvga means qsvga */
		i2c_w_mask(sd, OV7610_REG_COM_C, qvga ? (1 << 5) : 0, 1 << 5);
		i2c_w_mask(sd, 0x13, 0x00, 0x20); /* Select 16 bit data bus */
		i2c_w_mask(sd, 0x12, 0x04, 0x06); /* AWB: 1 Test pattern: 0 */
		i2c_w_mask(sd, 0x2d, 0x00, 0x40); /* from windrv 090403 */
		i2c_w_mask(sd, 0x28, 0x20, 0x20); /* progressive mode on */
		अवरोध;
	हाल SEN_OV7610:
		i2c_w_mask(sd, 0x14, qvga ? 0x20 : 0x00, 0x20);
		i2c_w(sd, 0x35, qvga ? 0x1e : 0x9e);
		i2c_w_mask(sd, 0x13, 0x00, 0x20); /* Select 16 bit data bus */
		i2c_w_mask(sd, 0x12, 0x04, 0x06); /* AWB: 1 Test pattern: 0 */
		अवरोध;
	हाल SEN_OV7620:
	हाल SEN_OV7620AE:
	हाल SEN_OV76BE:
		i2c_w_mask(sd, 0x14, qvga ? 0x20 : 0x00, 0x20);
		i2c_w_mask(sd, 0x28, qvga ? 0x00 : 0x20, 0x20);
		i2c_w(sd, 0x24, qvga ? 0x20 : 0x3a);
		i2c_w(sd, 0x25, qvga ? 0x30 : 0x60);
		i2c_w_mask(sd, 0x2d, qvga ? 0x40 : 0x00, 0x40);
		i2c_w_mask(sd, 0x67, qvga ? 0xb0 : 0x90, 0xf0);
		i2c_w_mask(sd, 0x74, qvga ? 0x20 : 0x00, 0x20);
		i2c_w_mask(sd, 0x13, 0x00, 0x20); /* Select 16 bit data bus */
		i2c_w_mask(sd, 0x12, 0x04, 0x06); /* AWB: 1 Test pattern: 0 */
		अगर (sd->sensor == SEN_OV76BE)
			i2c_w(sd, 0x35, qvga ? 0x1e : 0x9e);
		अवरोध;
	हाल SEN_OV7640:
	हाल SEN_OV7648:
		i2c_w_mask(sd, 0x14, qvga ? 0x20 : 0x00, 0x20);
		i2c_w_mask(sd, 0x28, qvga ? 0x00 : 0x20, 0x20);
		/* Setting this unकरोcumented bit in qvga mode हटाओs a very
		   annoying vertical shaking of the image */
		i2c_w_mask(sd, 0x2d, qvga ? 0x40 : 0x00, 0x40);
		/* Unknown */
		i2c_w_mask(sd, 0x67, qvga ? 0xf0 : 0x90, 0xf0);
		/* Allow higher स्वतःmatic gain (to allow higher framerates) */
		i2c_w_mask(sd, 0x74, qvga ? 0x20 : 0x00, 0x20);
		i2c_w_mask(sd, 0x12, 0x04, 0x04); /* AWB: 1 */
		अवरोध;
	हाल SEN_OV7670:
		/* set COM7_FMT_VGA or COM7_FMT_QVGA
		 * करो we need to set anything अन्यथा?
		 *	HSTART etc are set in set_ov_sensor_winकरोw itself */
		i2c_w_mask(sd, OV7670_R12_COM7,
			 qvga ? OV7670_COM7_FMT_QVGA : OV7670_COM7_FMT_VGA,
			 OV7670_COM7_FMT_MASK);
		i2c_w_mask(sd, 0x13, 0x00, 0x20); /* Select 16 bit data bus */
		i2c_w_mask(sd, OV7670_R13_COM8, OV7670_COM8_AWB,
				OV7670_COM8_AWB);
		अगर (qvga) अणु		/* QVGA from ov7670.c by
					 * Jonathan Corbet */
			xstart = 164;
			xend = 28;
			ystart = 14;
			yend = 494;
		पूर्ण अन्यथा अणु		/* VGA */
			xstart = 158;
			xend = 14;
			ystart = 10;
			yend = 490;
		पूर्ण
		/* OV7670 hardware winकरोw रेजिस्टरs are split across
		 * multiple locations */
		i2c_w(sd, OV7670_R17_HSTART, xstart >> 3);
		i2c_w(sd, OV7670_R18_HSTOP, xend >> 3);
		v = i2c_r(sd, OV7670_R32_HREF);
		v = (v & 0xc0) | ((xend & 0x7) << 3) | (xstart & 0x07);
		msleep(10);	/* need to sleep between पढ़ो and ग_लिखो to
				 * same reg! */
		i2c_w(sd, OV7670_R32_HREF, v);

		i2c_w(sd, OV7670_R19_VSTART, ystart >> 2);
		i2c_w(sd, OV7670_R1A_VSTOP, yend >> 2);
		v = i2c_r(sd, OV7670_R03_VREF);
		v = (v & 0xc0) | ((yend & 0x3) << 2) | (ystart & 0x03);
		msleep(10);	/* need to sleep between पढ़ो and ग_लिखो to
				 * same reg! */
		i2c_w(sd, OV7670_R03_VREF, v);
		अवरोध;
	हाल SEN_OV6620:
		i2c_w_mask(sd, 0x14, qvga ? 0x20 : 0x00, 0x20);
		i2c_w_mask(sd, 0x13, 0x00, 0x20); /* Select 16 bit data bus */
		i2c_w_mask(sd, 0x12, 0x04, 0x06); /* AWB: 1 Test pattern: 0 */
		अवरोध;
	हाल SEN_OV6630:
	हाल SEN_OV66308AF:
		i2c_w_mask(sd, 0x14, qvga ? 0x20 : 0x00, 0x20);
		i2c_w_mask(sd, 0x12, 0x04, 0x06); /* AWB: 1 Test pattern: 0 */
		अवरोध;
	हाल SEN_OV9600: अणु
		स्थिर काष्ठा ov_i2c_regvals *vals;
		अटल स्थिर काष्ठा ov_i2c_regvals sxga_15[] = अणु
			अणु0x11, 0x80पूर्ण, अणु0x14, 0x3eपूर्ण, अणु0x24, 0x85पूर्ण, अणु0x25, 0x75पूर्ण
		पूर्ण;
		अटल स्थिर काष्ठा ov_i2c_regvals sxga_7_5[] = अणु
			अणु0x11, 0x81पूर्ण, अणु0x14, 0x3eपूर्ण, अणु0x24, 0x85पूर्ण, अणु0x25, 0x75पूर्ण
		पूर्ण;
		अटल स्थिर काष्ठा ov_i2c_regvals vga_30[] = अणु
			अणु0x11, 0x81पूर्ण, अणु0x14, 0x7eपूर्ण, अणु0x24, 0x70पूर्ण, अणु0x25, 0x60पूर्ण
		पूर्ण;
		अटल स्थिर काष्ठा ov_i2c_regvals vga_15[] = अणु
			अणु0x11, 0x83पूर्ण, अणु0x14, 0x3eपूर्ण, अणु0x24, 0x80पूर्ण, अणु0x25, 0x70पूर्ण
		पूर्ण;

		/* frame rates:
		 *	15fps / 7.5 fps क्रम 1280x1024
		 *	30fps / 15fps क्रम 640x480
		 */
		i2c_w_mask(sd, 0x12, qvga ? 0x40 : 0x00, 0x40);
		अगर (qvga)
			vals = sd->frame_rate < 30 ? vga_15 : vga_30;
		अन्यथा
			vals = sd->frame_rate < 15 ? sxga_7_5 : sxga_15;
		ग_लिखो_i2c_regvals(sd, vals, ARRAY_SIZE(sxga_15));
		वापस;
	    पूर्ण
	शेष:
		वापस;
	पूर्ण

	/******** Clock programming ********/
	i2c_w(sd, 0x11, sd->घड़ीभाग);
पूर्ण

/* this function works क्रम bridge ov519 and sensors ov7660 and ov7670 only */
अटल व्योम sethvflip(काष्ठा gspca_dev *gspca_dev, s32 hflip, s32 vflip)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->gspca_dev.streaming)
		reg_w(sd, OV519_R51_RESET1, 0x0f);	/* block stream */
	i2c_w_mask(sd, OV7670_R1E_MVFP,
		OV7670_MVFP_MIRROR * hflip | OV7670_MVFP_VFLIP * vflip,
		OV7670_MVFP_MIRROR | OV7670_MVFP_VFLIP);
	अगर (sd->gspca_dev.streaming)
		reg_w(sd, OV519_R51_RESET1, 0x00);	/* restart stream */
पूर्ण

अटल व्योम set_ov_sensor_winकरोw(काष्ठा sd *sd)
अणु
	काष्ठा gspca_dev *gspca_dev;
	पूर्णांक qvga, crop;
	पूर्णांक hwsbase, hwebase, vwsbase, vwebase, hwscale, vwscale;

	/* mode setup is fully handled in mode_init_ov_sensor_regs क्रम these */
	चयन (sd->sensor) अणु
	हाल SEN_OV2610:
	हाल SEN_OV2610AE:
	हाल SEN_OV3610:
	हाल SEN_OV7670:
	हाल SEN_OV9600:
		mode_init_ov_sensor_regs(sd);
		वापस;
	हाल SEN_OV7660:
		ov519_set_mode(sd);
		ov519_set_fr(sd);
		वापस;
	पूर्ण

	gspca_dev = &sd->gspca_dev;
	qvga = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv & 1;
	crop = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv & 2;

	/* The dअगरferent sensor ICs handle setting up of winकरोw dअगरferently.
	 * IF YOU SET IT WRONG, YOU WILL GET ALL ZERO ISOC DATA FROM OV51x!! */
	चयन (sd->sensor) अणु
	हाल SEN_OV8610:
		hwsbase = 0x1e;
		hwebase = 0x1e;
		vwsbase = 0x02;
		vwebase = 0x02;
		अवरोध;
	हाल SEN_OV7610:
	हाल SEN_OV76BE:
		hwsbase = 0x38;
		hwebase = 0x3a;
		vwsbase = vwebase = 0x05;
		अवरोध;
	हाल SEN_OV6620:
	हाल SEN_OV6630:
	हाल SEN_OV66308AF:
		hwsbase = 0x38;
		hwebase = 0x3a;
		vwsbase = 0x05;
		vwebase = 0x06;
		अगर (sd->sensor == SEN_OV66308AF && qvga)
			/* HDG: this fixes U and V getting swapped */
			hwsbase++;
		अगर (crop) अणु
			hwsbase += 8;
			hwebase += 8;
			vwsbase += 11;
			vwebase += 11;
		पूर्ण
		अवरोध;
	हाल SEN_OV7620:
	हाल SEN_OV7620AE:
		hwsbase = 0x2f;		/* From 7620.SET (spec is wrong) */
		hwebase = 0x2f;
		vwsbase = vwebase = 0x05;
		अवरोध;
	हाल SEN_OV7640:
	हाल SEN_OV7648:
		hwsbase = 0x1a;
		hwebase = 0x1a;
		vwsbase = vwebase = 0x03;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	चयन (sd->sensor) अणु
	हाल SEN_OV6620:
	हाल SEN_OV6630:
	हाल SEN_OV66308AF:
		अगर (qvga) अणु		/* QCIF */
			hwscale = 0;
			vwscale = 0;
		पूर्ण अन्यथा अणु		/* CIF */
			hwscale = 1;
			vwscale = 1;	/* The datasheet says 0;
					 * it's wrong */
		पूर्ण
		अवरोध;
	हाल SEN_OV8610:
		अगर (qvga) अणु		/* QSVGA */
			hwscale = 1;
			vwscale = 1;
		पूर्ण अन्यथा अणु		/* SVGA */
			hwscale = 2;
			vwscale = 2;
		पूर्ण
		अवरोध;
	शेष:			/* SEN_OV7xx0 */
		अगर (qvga) अणु		/* QVGA */
			hwscale = 1;
			vwscale = 0;
		पूर्ण अन्यथा अणु		/* VGA */
			hwscale = 2;
			vwscale = 1;
		पूर्ण
	पूर्ण

	mode_init_ov_sensor_regs(sd);

	i2c_w(sd, 0x17, hwsbase);
	i2c_w(sd, 0x18, hwebase + (sd->sensor_width >> hwscale));
	i2c_w(sd, 0x19, vwsbase);
	i2c_w(sd, 0x1a, vwebase + (sd->sensor_height >> vwscale));
पूर्ण

/* -- start the camera -- */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/* Default क्रम most bridges, allow bridge_mode_init_regs to override */
	sd->sensor_width = sd->gspca_dev.pixfmt.width;
	sd->sensor_height = sd->gspca_dev.pixfmt.height;

	चयन (sd->bridge) अणु
	हाल BRIDGE_OV511:
	हाल BRIDGE_OV511PLUS:
		ov511_mode_init_regs(sd);
		अवरोध;
	हाल BRIDGE_OV518:
	हाल BRIDGE_OV518PLUS:
		ov518_mode_init_regs(sd);
		अवरोध;
	हाल BRIDGE_OV519:
		ov519_mode_init_regs(sd);
		अवरोध;
	/* हाल BRIDGE_OVFX2: nothing to करो */
	हाल BRIDGE_W9968CF:
		w9968cf_mode_init_regs(sd);
		अवरोध;
	पूर्ण

	set_ov_sensor_winकरोw(sd);

	/* Force clear snapshot state in हाल the snapshot button was
	   pressed जबतक we weren't streaming */
	sd->snapshot_needs_reset = 1;
	sd_reset_snapshot(gspca_dev);

	sd->first_frame = 3;

	ov51x_restart(sd);
	ov51x_led_control(sd, 1);
	वापस gspca_dev->usb_err;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	ov51x_stop(sd);
	ov51x_led_control(sd, 0);
पूर्ण

अटल व्योम sd_stop0(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (!sd->gspca_dev.present)
		वापस;
	अगर (sd->bridge == BRIDGE_W9968CF)
		w9968cf_stop0(sd);

#अगर IS_ENABLED(CONFIG_INPUT)
	/* If the last button state is pressed, release it now! */
	अगर (sd->snapshot_pressed) अणु
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, 0);
		input_sync(gspca_dev->input_dev);
		sd->snapshot_pressed = 0;
	पूर्ण
#पूर्ण_अगर
	अगर (sd->bridge == BRIDGE_OV519)
		reg_w(sd, OV519_R57_SNAPSHOT, 0x23);
पूर्ण

अटल व्योम ov51x_handle_button(काष्ठा gspca_dev *gspca_dev, u8 state)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->snapshot_pressed != state) अणु
#अगर IS_ENABLED(CONFIG_INPUT)
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, state);
		input_sync(gspca_dev->input_dev);
#पूर्ण_अगर
		अगर (state)
			sd->snapshot_needs_reset = 1;

		sd->snapshot_pressed = state;
	पूर्ण अन्यथा अणु
		/* On the ov511 / ov519 we need to reset the button state
		   multiple बार, as resetting करोes not work as दीर्घ as the
		   button stays pressed */
		चयन (sd->bridge) अणु
		हाल BRIDGE_OV511:
		हाल BRIDGE_OV511PLUS:
		हाल BRIDGE_OV519:
			अगर (state)
				sd->snapshot_needs_reset = 1;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ov511_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *in,			/* isoc packet */
			पूर्णांक len)		/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/* SOF/खातापूर्ण packets have 1st to 8th bytes zeroed and the 9th
	 * byte non-zero. The खातापूर्ण packet has image width/height in the
	 * 10th and 11th bytes. The 9th byte is given as follows:
	 *
	 * bit 7: खातापूर्ण
	 *     6: compression enabled
	 *     5: 422/420/400 modes
	 *     4: 422/420/400 modes
	 *     3: 1
	 *     2: snapshot button on
	 *     1: snapshot frame
	 *     0: even/odd field
	 */
	अगर (!(in[0] | in[1] | in[2] | in[3] | in[4] | in[5] | in[6] | in[7]) &&
	    (in[8] & 0x08)) अणु
		ov51x_handle_button(gspca_dev, (in[8] >> 2) & 1);
		अगर (in[8] & 0x80) अणु
			/* Frame end */
			अगर ((in[9] + 1) * 8 != gspca_dev->pixfmt.width ||
			    (in[10] + 1) * 8 != gspca_dev->pixfmt.height) अणु
				gspca_err(gspca_dev, "Invalid frame size, got: %dx%d, requested: %dx%d\n",
					  (in[9] + 1) * 8, (in[10] + 1) * 8,
					  gspca_dev->pixfmt.width,
					  gspca_dev->pixfmt.height);
				gspca_dev->last_packet_type = DISCARD_PACKET;
				वापस;
			पूर्ण
			/* Add 11 byte footer to frame, might be useful */
			gspca_frame_add(gspca_dev, LAST_PACKET, in, 11);
			वापस;
		पूर्ण अन्यथा अणु
			/* Frame start */
			gspca_frame_add(gspca_dev, FIRST_PACKET, in, 0);
			sd->packet_nr = 0;
		पूर्ण
	पूर्ण

	/* Ignore the packet number */
	len--;

	/* पूर्णांकermediate packet */
	gspca_frame_add(gspca_dev, INTER_PACKET, in, len);
पूर्ण

अटल व्योम ov518_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/* A false positive here is likely, until OVT gives me
	 * the definitive SOF/खातापूर्ण क्रमmat */
	अगर ((!(data[0] | data[1] | data[2] | data[3] | data[5])) && data[6]) अणु
		ov51x_handle_button(gspca_dev, (data[6] >> 1) & 1);
		gspca_frame_add(gspca_dev, LAST_PACKET, शून्य, 0);
		gspca_frame_add(gspca_dev, FIRST_PACKET, शून्य, 0);
		sd->packet_nr = 0;
	पूर्ण

	अगर (gspca_dev->last_packet_type == DISCARD_PACKET)
		वापस;

	/* Does this device use packet numbers ? */
	अगर (len & 7) अणु
		len--;
		अगर (sd->packet_nr == data[len])
			sd->packet_nr++;
		/* The last few packets of the frame (which are all 0's
		   except that they may contain part of the footer), are
		   numbered 0 */
		अन्यथा अगर (sd->packet_nr == 0 || data[len]) अणु
			gspca_err(gspca_dev, "Invalid packet nr: %d (expect: %d)\n",
				  (पूर्णांक)data[len], (पूर्णांक)sd->packet_nr);
			gspca_dev->last_packet_type = DISCARD_PACKET;
			वापस;
		पूर्ण
	पूर्ण

	/* पूर्णांकermediate packet */
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
पूर्ण

अटल व्योम ov519_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	/* Header of ov519 is 16 bytes:
	 *     Byte     Value      Description
	 *	0	0xff	magic
	 *	1	0xff	magic
	 *	2	0xff	magic
	 *	3	0xXX	0x50 = SOF, 0x51 = खातापूर्ण
	 *	9	0xXX	0x01 initial frame without data,
	 *			0x00 standard frame with image
	 *	14	Lo	in खातापूर्ण: length of image data / 8
	 *	15	Hi
	 */

	अगर (data[0] == 0xff && data[1] == 0xff && data[2] == 0xff) अणु
		चयन (data[3]) अणु
		हाल 0x50:		/* start of frame */
			/* Don't check the button state here, as the state
			   usually (always ?) changes at खातापूर्ण and checking it
			   here leads to unnecessary snapshot state resets. */
#घोषणा HDRSZ 16
			data += HDRSZ;
			len -= HDRSZ;
#अघोषित HDRSZ
			अगर (data[0] == 0xff || data[1] == 0xd8)
				gspca_frame_add(gspca_dev, FIRST_PACKET,
						data, len);
			अन्यथा
				gspca_dev->last_packet_type = DISCARD_PACKET;
			वापस;
		हाल 0x51:		/* end of frame */
			ov51x_handle_button(gspca_dev, data[11] & 1);
			अगर (data[9] != 0)
				gspca_dev->last_packet_type = DISCARD_PACKET;
			gspca_frame_add(gspca_dev, LAST_PACKET,
					शून्य, 0);
			वापस;
		पूर्ण
	पूर्ण

	/* पूर्णांकermediate packet */
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
पूर्ण

अटल व्योम ovfx2_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);

	/* A लघु पढ़ो संकेतs खातापूर्ण */
	अगर (len < gspca_dev->cam.bulk_size) अणु
		/* If the frame is लघु, and it is one of the first ones
		   the sensor and bridge are still syncing, so drop it. */
		अगर (sd->first_frame) अणु
			sd->first_frame--;
			अगर (gspca_dev->image_len <
				  sd->gspca_dev.pixfmt.width *
					sd->gspca_dev.pixfmt.height)
				gspca_dev->last_packet_type = DISCARD_PACKET;
		पूर्ण
		gspca_frame_add(gspca_dev, LAST_PACKET, शून्य, 0);
		gspca_frame_add(gspca_dev, FIRST_PACKET, शून्य, 0);
	पूर्ण
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	चयन (sd->bridge) अणु
	हाल BRIDGE_OV511:
	हाल BRIDGE_OV511PLUS:
		ov511_pkt_scan(gspca_dev, data, len);
		अवरोध;
	हाल BRIDGE_OV518:
	हाल BRIDGE_OV518PLUS:
		ov518_pkt_scan(gspca_dev, data, len);
		अवरोध;
	हाल BRIDGE_OV519:
		ov519_pkt_scan(gspca_dev, data, len);
		अवरोध;
	हाल BRIDGE_OVFX2:
		ovfx2_pkt_scan(gspca_dev, data, len);
		अवरोध;
	हाल BRIDGE_W9968CF:
		w9968cf_pkt_scan(gspca_dev, data, len);
		अवरोध;
	पूर्ण
पूर्ण

/* -- management routines -- */

अटल व्योम setbrightness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	अटल स्थिर काष्ठा ov_i2c_regvals brit_7660[][7] = अणु
		अणुअणु0x0f, 0x6aपूर्ण, अणु0x24, 0x40पूर्ण, अणु0x25, 0x2bपूर्ण, अणु0x26, 0x90पूर्ण,
			अणु0x27, 0xe0पूर्ण, अणु0x28, 0xe0पूर्ण, अणु0x2c, 0xe0पूर्णपूर्ण,
		अणुअणु0x0f, 0x6aपूर्ण, अणु0x24, 0x50पूर्ण, अणु0x25, 0x40पूर्ण, अणु0x26, 0xa1पूर्ण,
			अणु0x27, 0xc0पूर्ण, अणु0x28, 0xc0पूर्ण, अणु0x2c, 0xc0पूर्णपूर्ण,
		अणुअणु0x0f, 0x6aपूर्ण, अणु0x24, 0x68पूर्ण, अणु0x25, 0x58पूर्ण, अणु0x26, 0xc2पूर्ण,
			अणु0x27, 0xa0पूर्ण, अणु0x28, 0xa0पूर्ण, अणु0x2c, 0xa0पूर्णपूर्ण,
		अणुअणु0x0f, 0x6aपूर्ण, अणु0x24, 0x70पूर्ण, अणु0x25, 0x68पूर्ण, अणु0x26, 0xd3पूर्ण,
			अणु0x27, 0x80पूर्ण, अणु0x28, 0x80पूर्ण, अणु0x2c, 0x80पूर्णपूर्ण,
		अणुअणु0x0f, 0x6aपूर्ण, अणु0x24, 0x80पूर्ण, अणु0x25, 0x70पूर्ण, अणु0x26, 0xd3पूर्ण,
			अणु0x27, 0x20पूर्ण, अणु0x28, 0x20पूर्ण, अणु0x2c, 0x20पूर्णपूर्ण,
		अणुअणु0x0f, 0x6aपूर्ण, अणु0x24, 0x88पूर्ण, अणु0x25, 0x78पूर्ण, अणु0x26, 0xd3पूर्ण,
			अणु0x27, 0x40पूर्ण, अणु0x28, 0x40पूर्ण, अणु0x2c, 0x40पूर्णपूर्ण,
		अणुअणु0x0f, 0x6aपूर्ण, अणु0x24, 0x90पूर्ण, अणु0x25, 0x80पूर्ण, अणु0x26, 0xd4पूर्ण,
			अणु0x27, 0x60पूर्ण, अणु0x28, 0x60पूर्ण, अणु0x2c, 0x60पूर्णपूर्ण
	पूर्ण;

	चयन (sd->sensor) अणु
	हाल SEN_OV8610:
	हाल SEN_OV7610:
	हाल SEN_OV76BE:
	हाल SEN_OV6620:
	हाल SEN_OV6630:
	हाल SEN_OV66308AF:
	हाल SEN_OV7640:
	हाल SEN_OV7648:
		i2c_w(sd, OV7610_REG_BRT, val);
		अवरोध;
	हाल SEN_OV7620:
	हाल SEN_OV7620AE:
		i2c_w(sd, OV7610_REG_BRT, val);
		अवरोध;
	हाल SEN_OV7660:
		ग_लिखो_i2c_regvals(sd, brit_7660[val],
				ARRAY_SIZE(brit_7660[0]));
		अवरोध;
	हाल SEN_OV7670:
/*win trace
 *		i2c_w_mask(sd, OV7670_R13_COM8, 0, OV7670_COM8_AEC); */
		i2c_w(sd, OV7670_R55_BRIGHT, ov7670_असल_to_sm(val));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम setcontrast(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	अटल स्थिर काष्ठा ov_i2c_regvals contrast_7660[][31] = अणु
		अणुअणु0x6c, 0xf0पूर्ण, अणु0x6d, 0xf0पूर्ण, अणु0x6e, 0xf8पूर्ण, अणु0x6f, 0xa0पूर्ण,
		 अणु0x70, 0x58पूर्ण, अणु0x71, 0x38पूर्ण, अणु0x72, 0x30पूर्ण, अणु0x73, 0x30पूर्ण,
		 अणु0x74, 0x28पूर्ण, अणु0x75, 0x28पूर्ण, अणु0x76, 0x24पूर्ण, अणु0x77, 0x24पूर्ण,
		 अणु0x78, 0x22पूर्ण, अणु0x79, 0x28पूर्ण, अणु0x7a, 0x2aपूर्ण, अणु0x7b, 0x34पूर्ण,
		 अणु0x7c, 0x0fपूर्ण, अणु0x7d, 0x1eपूर्ण, अणु0x7e, 0x3dपूर्ण, अणु0x7f, 0x65पूर्ण,
		 अणु0x80, 0x70पूर्ण, अणु0x81, 0x77पूर्ण, अणु0x82, 0x7dपूर्ण, अणु0x83, 0x83पूर्ण,
		 अणु0x84, 0x88पूर्ण, अणु0x85, 0x8dपूर्ण, अणु0x86, 0x96पूर्ण, अणु0x87, 0x9fपूर्ण,
		 अणु0x88, 0xb0पूर्ण, अणु0x89, 0xc4पूर्ण, अणु0x8a, 0xd9पूर्णपूर्ण,
		अणुअणु0x6c, 0xf0पूर्ण, अणु0x6d, 0xf0पूर्ण, अणु0x6e, 0xf8पूर्ण, अणु0x6f, 0x94पूर्ण,
		 अणु0x70, 0x58पूर्ण, अणु0x71, 0x40पूर्ण, अणु0x72, 0x30पूर्ण, अणु0x73, 0x30पूर्ण,
		 अणु0x74, 0x30पूर्ण, अणु0x75, 0x30पूर्ण, अणु0x76, 0x2cपूर्ण, अणु0x77, 0x24पूर्ण,
		 अणु0x78, 0x22पूर्ण, अणु0x79, 0x28पूर्ण, अणु0x7a, 0x2aपूर्ण, अणु0x7b, 0x31पूर्ण,
		 अणु0x7c, 0x0fपूर्ण, अणु0x7d, 0x1eपूर्ण, अणु0x7e, 0x3dपूर्ण, अणु0x7f, 0x62पूर्ण,
		 अणु0x80, 0x6dपूर्ण, अणु0x81, 0x75पूर्ण, अणु0x82, 0x7bपूर्ण, अणु0x83, 0x81पूर्ण,
		 अणु0x84, 0x87पूर्ण, अणु0x85, 0x8dपूर्ण, अणु0x86, 0x98पूर्ण, अणु0x87, 0xa1पूर्ण,
		 अणु0x88, 0xb2पूर्ण, अणु0x89, 0xc6पूर्ण, अणु0x8a, 0xdbपूर्णपूर्ण,
		अणुअणु0x6c, 0xf0पूर्ण, अणु0x6d, 0xf0पूर्ण, अणु0x6e, 0xf0पूर्ण, अणु0x6f, 0x84पूर्ण,
		 अणु0x70, 0x58पूर्ण, अणु0x71, 0x48पूर्ण, अणु0x72, 0x40पूर्ण, अणु0x73, 0x40पूर्ण,
		 अणु0x74, 0x28पूर्ण, अणु0x75, 0x28पूर्ण, अणु0x76, 0x28पूर्ण, अणु0x77, 0x24पूर्ण,
		 अणु0x78, 0x26पूर्ण, अणु0x79, 0x28पूर्ण, अणु0x7a, 0x28पूर्ण, अणु0x7b, 0x34पूर्ण,
		 अणु0x7c, 0x0fपूर्ण, अणु0x7d, 0x1eपूर्ण, अणु0x7e, 0x3cपूर्ण, अणु0x7f, 0x5dपूर्ण,
		 अणु0x80, 0x68पूर्ण, अणु0x81, 0x71पूर्ण, अणु0x82, 0x79पूर्ण, अणु0x83, 0x81पूर्ण,
		 अणु0x84, 0x86पूर्ण, अणु0x85, 0x8bपूर्ण, अणु0x86, 0x95पूर्ण, अणु0x87, 0x9eपूर्ण,
		 अणु0x88, 0xb1पूर्ण, अणु0x89, 0xc5पूर्ण, अणु0x8a, 0xd9पूर्णपूर्ण,
		अणुअणु0x6c, 0xf0पूर्ण, अणु0x6d, 0xf0पूर्ण, अणु0x6e, 0xf0पूर्ण, अणु0x6f, 0x70पूर्ण,
		 अणु0x70, 0x58पूर्ण, अणु0x71, 0x58पूर्ण, अणु0x72, 0x48पूर्ण, अणु0x73, 0x48पूर्ण,
		 अणु0x74, 0x38पूर्ण, अणु0x75, 0x40पूर्ण, अणु0x76, 0x34पूर्ण, अणु0x77, 0x34पूर्ण,
		 अणु0x78, 0x2eपूर्ण, अणु0x79, 0x28पूर्ण, अणु0x7a, 0x24पूर्ण, अणु0x7b, 0x22पूर्ण,
		 अणु0x7c, 0x0fपूर्ण, अणु0x7d, 0x1eपूर्ण, अणु0x7e, 0x3cपूर्ण, अणु0x7f, 0x58पूर्ण,
		 अणु0x80, 0x63पूर्ण, अणु0x81, 0x6eपूर्ण, अणु0x82, 0x77पूर्ण, अणु0x83, 0x80पूर्ण,
		 अणु0x84, 0x87पूर्ण, अणु0x85, 0x8fपूर्ण, अणु0x86, 0x9cपूर्ण, अणु0x87, 0xa9पूर्ण,
		 अणु0x88, 0xc0पूर्ण, अणु0x89, 0xd4पूर्ण, अणु0x8a, 0xe6पूर्णपूर्ण,
		अणुअणु0x6c, 0xa0पूर्ण, अणु0x6d, 0xf0पूर्ण, अणु0x6e, 0x90पूर्ण, अणु0x6f, 0x80पूर्ण,
		 अणु0x70, 0x70पूर्ण, अणु0x71, 0x80पूर्ण, अणु0x72, 0x60पूर्ण, अणु0x73, 0x60पूर्ण,
		 अणु0x74, 0x58पूर्ण, अणु0x75, 0x60पूर्ण, अणु0x76, 0x4cपूर्ण, अणु0x77, 0x38पूर्ण,
		 अणु0x78, 0x38पूर्ण, अणु0x79, 0x2aपूर्ण, अणु0x7a, 0x20पूर्ण, अणु0x7b, 0x0eपूर्ण,
		 अणु0x7c, 0x0aपूर्ण, अणु0x7d, 0x14पूर्ण, अणु0x7e, 0x26पूर्ण, अणु0x7f, 0x46पूर्ण,
		 अणु0x80, 0x54पूर्ण, अणु0x81, 0x64पूर्ण, अणु0x82, 0x70पूर्ण, अणु0x83, 0x7cपूर्ण,
		 अणु0x84, 0x87पूर्ण, अणु0x85, 0x93पूर्ण, अणु0x86, 0xa6पूर्ण, अणु0x87, 0xb4पूर्ण,
		 अणु0x88, 0xd0पूर्ण, अणु0x89, 0xe5पूर्ण, अणु0x8a, 0xf5पूर्णपूर्ण,
		अणुअणु0x6c, 0x60पूर्ण, अणु0x6d, 0x80पूर्ण, अणु0x6e, 0x60पूर्ण, अणु0x6f, 0x80पूर्ण,
		 अणु0x70, 0x80पूर्ण, अणु0x71, 0x80पूर्ण, अणु0x72, 0x88पूर्ण, अणु0x73, 0x30पूर्ण,
		 अणु0x74, 0x70पूर्ण, अणु0x75, 0x68पूर्ण, अणु0x76, 0x64पूर्ण, अणु0x77, 0x50पूर्ण,
		 अणु0x78, 0x3cपूर्ण, अणु0x79, 0x22पूर्ण, अणु0x7a, 0x10पूर्ण, अणु0x7b, 0x08पूर्ण,
		 अणु0x7c, 0x06पूर्ण, अणु0x7d, 0x0eपूर्ण, अणु0x7e, 0x1aपूर्ण, अणु0x7f, 0x3aपूर्ण,
		 अणु0x80, 0x4aपूर्ण, अणु0x81, 0x5aपूर्ण, अणु0x82, 0x6bपूर्ण, अणु0x83, 0x7bपूर्ण,
		 अणु0x84, 0x89पूर्ण, अणु0x85, 0x96पूर्ण, अणु0x86, 0xafपूर्ण, अणु0x87, 0xc3पूर्ण,
		 अणु0x88, 0xe1पूर्ण, अणु0x89, 0xf2पूर्ण, अणु0x8a, 0xfaपूर्णपूर्ण,
		अणुअणु0x6c, 0x20पूर्ण, अणु0x6d, 0x40पूर्ण, अणु0x6e, 0x20पूर्ण, अणु0x6f, 0x60पूर्ण,
		 अणु0x70, 0x88पूर्ण, अणु0x71, 0xc8पूर्ण, अणु0x72, 0xc0पूर्ण, अणु0x73, 0xb8पूर्ण,
		 अणु0x74, 0xa8पूर्ण, अणु0x75, 0xb8पूर्ण, अणु0x76, 0x80पूर्ण, अणु0x77, 0x5cपूर्ण,
		 अणु0x78, 0x26पूर्ण, अणु0x79, 0x10पूर्ण, अणु0x7a, 0x08पूर्ण, अणु0x7b, 0x04पूर्ण,
		 अणु0x7c, 0x02पूर्ण, अणु0x7d, 0x06पूर्ण, अणु0x7e, 0x0aपूर्ण, अणु0x7f, 0x22पूर्ण,
		 अणु0x80, 0x33पूर्ण, अणु0x81, 0x4cपूर्ण, अणु0x82, 0x64पूर्ण, अणु0x83, 0x7bपूर्ण,
		 अणु0x84, 0x90पूर्ण, अणु0x85, 0xa7पूर्ण, अणु0x86, 0xc7पूर्ण, अणु0x87, 0xdeपूर्ण,
		 अणु0x88, 0xf1पूर्ण, अणु0x89, 0xf9पूर्ण, अणु0x8a, 0xfdपूर्णपूर्ण,
	पूर्ण;

	चयन (sd->sensor) अणु
	हाल SEN_OV7610:
	हाल SEN_OV6620:
		i2c_w(sd, OV7610_REG_CNT, val);
		अवरोध;
	हाल SEN_OV6630:
	हाल SEN_OV66308AF:
		i2c_w_mask(sd, OV7610_REG_CNT, val >> 4, 0x0f);
		अवरोध;
	हाल SEN_OV8610: अणु
		अटल स्थिर u8 ctab[] = अणु
			0x03, 0x09, 0x0b, 0x0f, 0x53, 0x6f, 0x35, 0x7f
		पूर्ण;

		/* Use Y gamma control instead. Bit 0 enables it. */
		i2c_w(sd, 0x64, ctab[val >> 5]);
		अवरोध;
	    पूर्ण
	हाल SEN_OV7620:
	हाल SEN_OV7620AE: अणु
		अटल स्थिर u8 ctab[] = अणु
			0x01, 0x05, 0x09, 0x11, 0x15, 0x35, 0x37, 0x57,
			0x5b, 0xa5, 0xa7, 0xc7, 0xc9, 0xcf, 0xef, 0xff
		पूर्ण;

		/* Use Y gamma control instead. Bit 0 enables it. */
		i2c_w(sd, 0x64, ctab[val >> 4]);
		अवरोध;
	    पूर्ण
	हाल SEN_OV7660:
		ग_लिखो_i2c_regvals(sd, contrast_7660[val],
					ARRAY_SIZE(contrast_7660[0]));
		अवरोध;
	हाल SEN_OV7670:
		/* check that this isn't just the same as ov7610 */
		i2c_w(sd, OV7670_R56_CONTRAS, val >> 1);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम setexposure(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	i2c_w(sd, 0x10, val);
पूर्ण

अटल व्योम setcolors(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	अटल स्थिर काष्ठा ov_i2c_regvals colors_7660[][6] = अणु
		अणुअणु0x4f, 0x28पूर्ण, अणु0x50, 0x2aपूर्ण, अणु0x51, 0x02पूर्ण, अणु0x52, 0x0aपूर्ण,
		 अणु0x53, 0x19पूर्ण, अणु0x54, 0x23पूर्णपूर्ण,
		अणुअणु0x4f, 0x47पूर्ण, अणु0x50, 0x4aपूर्ण, अणु0x51, 0x03पूर्ण, अणु0x52, 0x11पूर्ण,
		 अणु0x53, 0x2cपूर्ण, अणु0x54, 0x3eपूर्णपूर्ण,
		अणुअणु0x4f, 0x66पूर्ण, अणु0x50, 0x6bपूर्ण, अणु0x51, 0x05पूर्ण, अणु0x52, 0x19पूर्ण,
		 अणु0x53, 0x40पूर्ण, अणु0x54, 0x59पूर्णपूर्ण,
		अणुअणु0x4f, 0x84पूर्ण, अणु0x50, 0x8bपूर्ण, अणु0x51, 0x06पूर्ण, अणु0x52, 0x20पूर्ण,
		 अणु0x53, 0x53पूर्ण, अणु0x54, 0x73पूर्णपूर्ण,
		अणुअणु0x4f, 0xa3पूर्ण, अणु0x50, 0xabपूर्ण, अणु0x51, 0x08पूर्ण, अणु0x52, 0x28पूर्ण,
		 अणु0x53, 0x66पूर्ण, अणु0x54, 0x8eपूर्णपूर्ण,
	पूर्ण;

	चयन (sd->sensor) अणु
	हाल SEN_OV8610:
	हाल SEN_OV7610:
	हाल SEN_OV76BE:
	हाल SEN_OV6620:
	हाल SEN_OV6630:
	हाल SEN_OV66308AF:
		i2c_w(sd, OV7610_REG_SAT, val);
		अवरोध;
	हाल SEN_OV7620:
	हाल SEN_OV7620AE:
		/* Use UV gamma control instead. Bits 0 & 7 are reserved. */
/*		rc = ov_i2c_ग_लिखो(sd->dev, 0x62, (val >> 9) & 0x7e);
		अगर (rc < 0)
			जाओ out; */
		i2c_w(sd, OV7610_REG_SAT, val);
		अवरोध;
	हाल SEN_OV7640:
	हाल SEN_OV7648:
		i2c_w(sd, OV7610_REG_SAT, val & 0xf0);
		अवरोध;
	हाल SEN_OV7660:
		ग_लिखो_i2c_regvals(sd, colors_7660[val],
					ARRAY_SIZE(colors_7660[0]));
		अवरोध;
	हाल SEN_OV7670:
		/* supported later once I work out how to करो it
		 * transparently fail now! */
		/* set REG_COM13 values क्रम UV sat स्वतः mode */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम setस्वतःbright(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	i2c_w_mask(sd, 0x2d, val ? 0x10 : 0x00, 0x10);
पूर्ण

अटल व्योम setfreq_i(काष्ठा sd *sd, s32 val)
अणु
	अगर (sd->sensor == SEN_OV7660
	 || sd->sensor == SEN_OV7670) अणु
		चयन (val) अणु
		हाल 0: /* Banding filter disabled */
			i2c_w_mask(sd, OV7670_R13_COM8, 0, OV7670_COM8_BFILT);
			अवरोध;
		हाल 1: /* 50 hz */
			i2c_w_mask(sd, OV7670_R13_COM8, OV7670_COM8_BFILT,
				   OV7670_COM8_BFILT);
			i2c_w_mask(sd, OV7670_R3B_COM11, 0x08, 0x18);
			अवरोध;
		हाल 2: /* 60 hz */
			i2c_w_mask(sd, OV7670_R13_COM8, OV7670_COM8_BFILT,
				   OV7670_COM8_BFILT);
			i2c_w_mask(sd, OV7670_R3B_COM11, 0x00, 0x18);
			अवरोध;
		हाल 3: /* Auto hz - ov7670 only */
			i2c_w_mask(sd, OV7670_R13_COM8, OV7670_COM8_BFILT,
				   OV7670_COM8_BFILT);
			i2c_w_mask(sd, OV7670_R3B_COM11, OV7670_COM11_HZAUTO,
				   0x18);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (val) अणु
		हाल 0: /* Banding filter disabled */
			i2c_w_mask(sd, 0x2d, 0x00, 0x04);
			i2c_w_mask(sd, 0x2a, 0x00, 0x80);
			अवरोध;
		हाल 1: /* 50 hz (filter on and framerate adj) */
			i2c_w_mask(sd, 0x2d, 0x04, 0x04);
			i2c_w_mask(sd, 0x2a, 0x80, 0x80);
			/* 20 fps -> 16.667 fps */
			अगर (sd->sensor == SEN_OV6620 ||
			    sd->sensor == SEN_OV6630 ||
			    sd->sensor == SEN_OV66308AF)
				i2c_w(sd, 0x2b, 0x5e);
			अन्यथा
				i2c_w(sd, 0x2b, 0xac);
			अवरोध;
		हाल 2: /* 60 hz (filter on, ...) */
			i2c_w_mask(sd, 0x2d, 0x04, 0x04);
			अगर (sd->sensor == SEN_OV6620 ||
			    sd->sensor == SEN_OV6630 ||
			    sd->sensor == SEN_OV66308AF) अणु
				/* 20 fps -> 15 fps */
				i2c_w_mask(sd, 0x2a, 0x80, 0x80);
				i2c_w(sd, 0x2b, 0xa8);
			पूर्ण अन्यथा अणु
				/* no framerate adj. */
				i2c_w_mask(sd, 0x2a, 0x00, 0x80);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम setfreq(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	setfreq_i(sd, val);

	/* Ugly but necessary */
	अगर (sd->bridge == BRIDGE_W9968CF)
		w9968cf_set_crop_winकरोw(sd);
पूर्ण

अटल पूर्णांक sd_get_jcomp(काष्ठा gspca_dev *gspca_dev,
			काष्ठा v4l2_jpegcompression *jcomp)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->bridge != BRIDGE_W9968CF)
		वापस -ENOTTY;

	स_रखो(jcomp, 0, माप *jcomp);
	jcomp->quality = v4l2_ctrl_g_ctrl(sd->jpegqual);
	jcomp->jpeg_markers = V4L2_JPEG_MARKER_DHT | V4L2_JPEG_MARKER_DQT |
			      V4L2_JPEG_MARKER_DRI;
	वापस 0;
पूर्ण

अटल पूर्णांक sd_set_jcomp(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा v4l2_jpegcompression *jcomp)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->bridge != BRIDGE_W9968CF)
		वापस -ENOTTY;

	v4l2_ctrl_s_ctrl(sd->jpegqual, jcomp->quality);
	वापस 0;
पूर्ण

अटल पूर्णांक sd_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;

	gspca_dev->usb_err = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTOGAIN:
		gspca_dev->exposure->val = i2c_r(sd, 0x10);
		अवरोध;
	पूर्ण
	वापस 0;
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
	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		setfreq(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_AUTOBRIGHTNESS:
		अगर (ctrl->is_new)
			setस्वतःbright(gspca_dev, ctrl->val);
		अगर (!ctrl->val && sd->brightness->is_new)
			setbrightness(gspca_dev, sd->brightness->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		setcolors(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		sethvflip(gspca_dev, ctrl->val, sd->vflip->val);
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		अगर (ctrl->is_new)
			setस्वतःgain(gspca_dev, ctrl->val);
		अगर (!ctrl->val && gspca_dev->exposure->is_new)
			setexposure(gspca_dev, gspca_dev->exposure->val);
		अवरोध;
	हाल V4L2_CID_JPEG_COMPRESSION_QUALITY:
		वापस -EBUSY; /* Should never happen, as we grab the ctrl */
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.g_अस्थिर_ctrl = sd_g_अस्थिर_ctrl,
	.s_ctrl = sd_s_ctrl,
पूर्ण;

अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 10);
	अगर (valid_controls[sd->sensor].has_brightness)
		sd->brightness = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0,
			sd->sensor == SEN_OV7660 ? 6 : 255, 1,
			sd->sensor == SEN_OV7660 ? 3 : 127);
	अगर (valid_controls[sd->sensor].has_contrast) अणु
		अगर (sd->sensor == SEN_OV7660)
			v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				V4L2_CID_CONTRAST, 0, 6, 1, 3);
		अन्यथा
			v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				V4L2_CID_CONTRAST, 0, 255, 1,
				(sd->sensor == SEN_OV6630 ||
				 sd->sensor == SEN_OV66308AF) ? 200 : 127);
	पूर्ण
	अगर (valid_controls[sd->sensor].has_sat)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SATURATION, 0,
			sd->sensor == SEN_OV7660 ? 4 : 255, 1,
			sd->sensor == SEN_OV7660 ? 2 : 127);
	अगर (valid_controls[sd->sensor].has_exposure)
		gspca_dev->exposure = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 255, 1, 127);
	अगर (valid_controls[sd->sensor].has_hvflip) अणु
		sd->hflip = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
		sd->vflip = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	पूर्ण
	अगर (valid_controls[sd->sensor].has_स्वतःbright)
		sd->स्वतःbright = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_AUTOBRIGHTNESS, 0, 1, 1, 1);
	अगर (valid_controls[sd->sensor].has_स्वतःgain)
		gspca_dev->स्वतःgain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	अगर (valid_controls[sd->sensor].has_freq) अणु
		अगर (sd->sensor == SEN_OV7670)
			sd->freq = v4l2_ctrl_new_std_menu(hdl, &sd_ctrl_ops,
				V4L2_CID_POWER_LINE_FREQUENCY,
				V4L2_CID_POWER_LINE_FREQUENCY_AUTO, 0,
				V4L2_CID_POWER_LINE_FREQUENCY_AUTO);
		अन्यथा
			sd->freq = v4l2_ctrl_new_std_menu(hdl, &sd_ctrl_ops,
				V4L2_CID_POWER_LINE_FREQUENCY,
				V4L2_CID_POWER_LINE_FREQUENCY_60HZ, 0, 0);
	पूर्ण
	अगर (sd->bridge == BRIDGE_W9968CF)
		sd->jpegqual = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_JPEG_COMPRESSION_QUALITY,
			QUALITY_MIN, QUALITY_MAX, 1, QUALITY_DEF);

	अगर (hdl->error) अणु
		gspca_err(gspca_dev, "Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण
	अगर (gspca_dev->स्वतःgain)
		v4l2_ctrl_स्वतः_cluster(3, &gspca_dev->स्वतःgain, 0, true);
	अगर (sd->स्वतःbright)
		v4l2_ctrl_स्वतः_cluster(2, &sd->स्वतःbright, 0, false);
	अगर (sd->hflip)
		v4l2_ctrl_cluster(2, &sd->hflip);
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
	.stop0 = sd_stop0,
	.pkt_scan = sd_pkt_scan,
	.dq_callback = sd_reset_snapshot,
	.get_jcomp = sd_get_jcomp,
	.set_jcomp = sd_set_jcomp,
#अगर IS_ENABLED(CONFIG_INPUT)
	.other_input = 1,
#पूर्ण_अगर
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x041e, 0x4003), .driver_info = BRIDGE_W9968CF पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4052),
		.driver_info = BRIDGE_OV519 | BRIDGE_INVERT_LED पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x405f), .driver_info = BRIDGE_OV519 पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4060), .driver_info = BRIDGE_OV519 पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4061), .driver_info = BRIDGE_OV519 पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4064), .driver_info = BRIDGE_OV519 पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4067), .driver_info = BRIDGE_OV519 पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4068), .driver_info = BRIDGE_OV519 पूर्ण,
	अणुUSB_DEVICE(0x045e, 0x028c),
		.driver_info = BRIDGE_OV519 | BRIDGE_INVERT_LED पूर्ण,
	अणुUSB_DEVICE(0x054c, 0x0154), .driver_info = BRIDGE_OV519 पूर्ण,
	अणुUSB_DEVICE(0x054c, 0x0155), .driver_info = BRIDGE_OV519 पूर्ण,
	अणुUSB_DEVICE(0x05a9, 0x0511), .driver_info = BRIDGE_OV511 पूर्ण,
	अणुUSB_DEVICE(0x05a9, 0x0518), .driver_info = BRIDGE_OV518 पूर्ण,
	अणुUSB_DEVICE(0x05a9, 0x0519),
		.driver_info = BRIDGE_OV519 | BRIDGE_INVERT_LED पूर्ण,
	अणुUSB_DEVICE(0x05a9, 0x0530),
		.driver_info = BRIDGE_OV519 | BRIDGE_INVERT_LED पूर्ण,
	अणुUSB_DEVICE(0x05a9, 0x2800), .driver_info = BRIDGE_OVFX2 पूर्ण,
	अणुUSB_DEVICE(0x05a9, 0x4519), .driver_info = BRIDGE_OV519 पूर्ण,
	अणुUSB_DEVICE(0x05a9, 0x8519), .driver_info = BRIDGE_OV519 पूर्ण,
	अणुUSB_DEVICE(0x05a9, 0xa511), .driver_info = BRIDGE_OV511PLUS पूर्ण,
	अणुUSB_DEVICE(0x05a9, 0xa518), .driver_info = BRIDGE_OV518PLUS पूर्ण,
	अणुUSB_DEVICE(0x0813, 0x0002), .driver_info = BRIDGE_OV511PLUS पूर्ण,
	अणुUSB_DEVICE(0x0b62, 0x0059), .driver_info = BRIDGE_OVFX2 पूर्ण,
	अणुUSB_DEVICE(0x0e96, 0xc001), .driver_info = BRIDGE_OVFX2 पूर्ण,
	अणुUSB_DEVICE(0x1046, 0x9967), .driver_info = BRIDGE_W9968CF पूर्ण,
	अणुUSB_DEVICE(0x8020, 0xef04), .driver_info = BRIDGE_OVFX2 पूर्ण,
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

module_param(frame_rate, पूर्णांक, 0644);
MODULE_PARM_DESC(frame_rate, "Frame rate (5, 10, 15, 20 or 30 fps)");
