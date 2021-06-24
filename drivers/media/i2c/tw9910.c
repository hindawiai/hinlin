<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * tw9910 Video Driver
 *
 * Copyright (C) 2017 Jacopo Mondi <jacopo+renesas@jmondi.org>
 *
 * Copyright (C) 2008 Renesas Solutions Corp.
 * Kuninori Morimoto <morimoto.kuninori@renesas.com>
 *
 * Based on ov772x driver,
 *
 * Copyright (C) 2008 Kuninori Morimoto <morimoto.kuninori@renesas.com>
 * Copyright 2006-7 Jonathan Corbet <corbet@lwn.net>
 * Copyright (C) 2008 Magnus Damm
 * Copyright (C) 2008, Guennadi Liakhovetski <kernel@pengutronix.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <linux/videodev2.h>

#समावेश <media/i2c/tw9910.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा GET_ID(val)  ((val & 0xF8) >> 3)
#घोषणा GET_REV(val) (val & 0x07)

/*
 * रेजिस्टर offset
 */
#घोषणा ID		0x00 /* Product ID Code Register */
#घोषणा STATUS1		0x01 /* Chip Status Register I */
#घोषणा INFORM		0x02 /* Input Format */
#घोषणा OPFORM		0x03 /* Output Format Control Register */
#घोषणा DLYCTR		0x04 /* Hysteresis and HSYNC Delay Control */
#घोषणा OUTCTR1		0x05 /* Output Control I */
#घोषणा ACNTL1		0x06 /* Analog Control Register 1 */
#घोषणा CROP_HI		0x07 /* Cropping Register, High */
#घोषणा VDELAY_LO	0x08 /* Vertical Delay Register, Low */
#घोषणा VACTIVE_LO	0x09 /* Vertical Active Register, Low */
#घोषणा HDELAY_LO	0x0A /* Horizontal Delay Register, Low */
#घोषणा HACTIVE_LO	0x0B /* Horizontal Active Register, Low */
#घोषणा CNTRL1		0x0C /* Control Register I */
#घोषणा VSCALE_LO	0x0D /* Vertical Scaling Register, Low */
#घोषणा SCALE_HI	0x0E /* Scaling Register, High */
#घोषणा HSCALE_LO	0x0F /* Horizontal Scaling Register, Low */
#घोषणा BRIGHT		0x10 /* BRIGHTNESS Control Register */
#घोषणा CONTRAST	0x11 /* CONTRAST Control Register */
#घोषणा SHARPNESS	0x12 /* SHARPNESS Control Register I */
#घोषणा SAT_U		0x13 /* Chroma (U) Gain Register */
#घोषणा SAT_V		0x14 /* Chroma (V) Gain Register */
#घोषणा HUE		0x15 /* Hue Control Register */
#घोषणा CORING1		0x17
#घोषणा CORING2		0x18 /* Coring and IF compensation */
#घोषणा VBICNTL		0x19 /* VBI Control Register */
#घोषणा ACNTL2		0x1A /* Analog Control 2 */
#घोषणा OUTCTR2		0x1B /* Output Control 2 */
#घोषणा SDT		0x1C /* Standard Selection */
#घोषणा SDTR		0x1D /* Standard Recognition */
#घोषणा TEST		0x1F /* Test Control Register */
#घोषणा CLMPG		0x20 /* Clamping Gain */
#घोषणा IAGC		0x21 /* Inभागidual AGC Gain */
#घोषणा AGCGAIN		0x22 /* AGC Gain */
#घोषणा PEAKWT		0x23 /* White Peak Threshold */
#घोषणा CLMPL		0x24 /* Clamp level */
#घोषणा SYNCT		0x25 /* Sync Amplitude */
#घोषणा MISSCNT		0x26 /* Sync Miss Count Register */
#घोषणा PCLAMP		0x27 /* Clamp Position Register */
#घोषणा VCNTL1		0x28 /* Vertical Control I */
#घोषणा VCNTL2		0x29 /* Vertical Control II */
#घोषणा CKILL		0x2A /* Color Killer Level Control */
#घोषणा COMB		0x2B /* Comb Filter Control */
#घोषणा LDLY		0x2C /* Luma Delay and H Filter Control */
#घोषणा MISC1		0x2D /* Miscellaneous Control I */
#घोषणा LOOP		0x2E /* LOOP Control Register */
#घोषणा MISC2		0x2F /* Miscellaneous Control II */
#घोषणा MVSN		0x30 /* Macrovision Detection */
#घोषणा STATUS2		0x31 /* Chip STATUS II */
#घोषणा HFREF		0x32 /* H monitor */
#घोषणा CLMD		0x33 /* CLAMP MODE */
#घोषणा IDCNTL		0x34 /* ID Detection Control */
#घोषणा CLCNTL1		0x35 /* Clamp Control I */
#घोषणा ANAPLLCTL	0x4C
#घोषणा VBIMIN		0x4D
#घोषणा HSLOWCTL	0x4E
#घोषणा WSS3		0x4F
#घोषणा FILLDATA	0x50
#घोषणा SDID		0x51
#घोषणा DID		0x52
#घोषणा WSS1		0x53
#घोषणा WSS2		0x54
#घोषणा VVBI		0x55
#घोषणा LCTL6		0x56
#घोषणा LCTL7		0x57
#घोषणा LCTL8		0x58
#घोषणा LCTL9		0x59
#घोषणा LCTL10		0x5A
#घोषणा LCTL11		0x5B
#घोषणा LCTL12		0x5C
#घोषणा LCTL13		0x5D
#घोषणा LCTL14		0x5E
#घोषणा LCTL15		0x5F
#घोषणा LCTL16		0x60
#घोषणा LCTL17		0x61
#घोषणा LCTL18		0x62
#घोषणा LCTL19		0x63
#घोषणा LCTL20		0x64
#घोषणा LCTL21		0x65
#घोषणा LCTL22		0x66
#घोषणा LCTL23		0x67
#घोषणा LCTL24		0x68
#घोषणा LCTL25		0x69
#घोषणा LCTL26		0x6A
#घोषणा HSBEGIN		0x6B
#घोषणा HSEND		0x6C
#घोषणा OVSDLY		0x6D
#घोषणा OVSEND		0x6E
#घोषणा VBIDELAY	0x6F

/*
 * रेजिस्टर detail
 */

/* INFORM */
#घोषणा FC27_ON     0x40 /* 1 : Input crystal घड़ी frequency is 27MHz */
#घोषणा FC27_FF     0x00 /* 0 : Square pixel mode. */
			 /*     Must use 24.54MHz क्रम 60Hz field rate */
			 /*     source or 29.5MHz क्रम 50Hz field rate */
#घोषणा IFSEL_S     0x10 /* 01 : S-video decoding */
#घोषणा IFSEL_C     0x00 /* 00 : Composite video decoding */
			 /* Y input video selection */
#घोषणा YSEL_M0     0x00 /*  00 : Mux0 selected */
#घोषणा YSEL_M1     0x04 /*  01 : Mux1 selected */
#घोषणा YSEL_M2     0x08 /*  10 : Mux2 selected */
#घोषणा YSEL_M3     0x10 /*  11 : Mux3 selected */

/* OPFORM */
#घोषणा MODE        0x80 /* 0 : CCIR601 compatible YCrCb 4:2:2 क्रमmat */
			 /* 1 : ITU-R-656 compatible data sequence क्रमmat */
#घोषणा LEN         0x40 /* 0 : 8-bit YCrCb 4:2:2 output क्रमmat */
			 /* 1 : 16-bit YCrCb 4:2:2 output क्रमmat.*/
#घोषणा LLCMODE     0x20 /* 1 : LLC output mode. */
			 /* 0 : मुक्त-run output mode */
#घोषणा AINC        0x10 /* Serial पूर्णांकerface स्वतः-indexing control */
			 /* 0 : स्वतः-increment */
			 /* 1 : non-स्वतः */
#घोषणा VSCTL       0x08 /* 1 : Vertical out ctrl by DVALID */
			 /* 0 : Vertical out ctrl by HACTIVE and DVALID */
#घोषणा OEN_TRI_SEL_MASK	0x07
#घोषणा OEN_TRI_SEL_ALL_ON	0x00 /* Enable output क्रम Rev0/Rev1 */
#घोषणा OEN_TRI_SEL_ALL_OFF_r0	0x06 /* All tri-stated क्रम Rev0 */
#घोषणा OEN_TRI_SEL_ALL_OFF_r1	0x07 /* All tri-stated क्रम Rev1 */

/* OUTCTR1 */
#घोषणा VSP_LO      0x00 /* 0 : VS pin output polarity is active low */
#घोषणा VSP_HI      0x80 /* 1 : VS pin output polarity is active high. */
			 /* VS pin output control */
#घोषणा VSSL_VSYNC  0x00 /*   0 : VSYNC  */
#घोषणा VSSL_VACT   0x10 /*   1 : VACT   */
#घोषणा VSSL_FIELD  0x20 /*   2 : FIELD  */
#घोषणा VSSL_VVALID 0x30 /*   3 : VVALID */
#घोषणा VSSL_ZERO   0x70 /*   7 : 0      */
#घोषणा HSP_LOW     0x00 /* 0 : HS pin output polarity is active low */
#घोषणा HSP_HI      0x08 /* 1 : HS pin output polarity is active high.*/
			 /* HS pin output control */
#घोषणा HSSL_HACT   0x00 /*   0 : HACT   */
#घोषणा HSSL_HSYNC  0x01 /*   1 : HSYNC  */
#घोषणा HSSL_DVALID 0x02 /*   2 : DVALID */
#घोषणा HSSL_HLOCK  0x03 /*   3 : HLOCK  */
#घोषणा HSSL_ASYNCW 0x04 /*   4 : ASYNCW */
#घोषणा HSSL_ZERO   0x07 /*   7 : 0      */

/* ACNTL1 */
#घोषणा SRESET      0x80 /* resets the device to its शेष state
			  * but all रेजिस्टर content reमुख्य unchanged.
			  * This bit is self-resetting.
			  */
#घोषणा ACNTL1_PDN_MASK	0x0e
#घोषणा CLK_PDN		0x08 /* प्रणाली घड़ी घातer करोwn */
#घोषणा Y_PDN		0x04 /* Luma ADC घातer करोwn */
#घोषणा C_PDN		0x02 /* Chroma ADC घातer करोwn */

/* ACNTL2 */
#घोषणा ACNTL2_PDN_MASK	0x40
#घोषणा PLL_PDN		0x40 /* PLL घातer करोwn */

/* VBICNTL */

/* RTSEL : control the real समय संकेत output from the MPOUT pin */
#घोषणा RTSEL_MASK  0x07
#घोषणा RTSEL_VLOSS 0x00 /* 0000 = Video loss */
#घोषणा RTSEL_HLOCK 0x01 /* 0001 = H-lock */
#घोषणा RTSEL_SLOCK 0x02 /* 0010 = S-lock */
#घोषणा RTSEL_VLOCK 0x03 /* 0011 = V-lock */
#घोषणा RTSEL_MONO  0x04 /* 0100 = MONO */
#घोषणा RTSEL_DET50 0x05 /* 0101 = DET50 */
#घोषणा RTSEL_FIELD 0x06 /* 0110 = FIELD */
#घोषणा RTSEL_RTCO  0x07 /* 0111 = RTCO ( Real Time Control ) */

/* HSYNC start and end are स्थिरant क्रम now */
#घोषणा HSYNC_START	0x0260
#घोषणा HSYNC_END	0x0300

/*
 * काष्ठाure
 */

काष्ठा regval_list अणु
	अचिन्हित अक्षर reg_num;
	अचिन्हित अक्षर value;
पूर्ण;

काष्ठा tw9910_scale_ctrl अणु
	अक्षर           *name;
	अचिन्हित लघु  width;
	अचिन्हित लघु  height;
	u16             hscale;
	u16             vscale;
पूर्ण;

काष्ठा tw9910_priv अणु
	काष्ठा v4l2_subdev		subdev;
	काष्ठा clk			*clk;
	काष्ठा tw9910_video_info	*info;
	काष्ठा gpio_desc		*pdn_gpio;
	काष्ठा gpio_desc		*rstb_gpio;
	स्थिर काष्ठा tw9910_scale_ctrl	*scale;
	v4l2_std_id			norm;
	u32				revision;
पूर्ण;

अटल स्थिर काष्ठा tw9910_scale_ctrl tw9910_ntsc_scales[] = अणु
	अणु
		.name   = "NTSC SQ",
		.width  = 640,
		.height = 480,
		.hscale = 0x0100,
		.vscale = 0x0100,
	पूर्ण,
	अणु
		.name   = "NTSC CCIR601",
		.width  = 720,
		.height = 480,
		.hscale = 0x0100,
		.vscale = 0x0100,
	पूर्ण,
	अणु
		.name   = "NTSC SQ (CIF)",
		.width  = 320,
		.height = 240,
		.hscale = 0x0200,
		.vscale = 0x0200,
	पूर्ण,
	अणु
		.name   = "NTSC CCIR601 (CIF)",
		.width  = 360,
		.height = 240,
		.hscale = 0x0200,
		.vscale = 0x0200,
	पूर्ण,
	अणु
		.name   = "NTSC SQ (QCIF)",
		.width  = 160,
		.height = 120,
		.hscale = 0x0400,
		.vscale = 0x0400,
	पूर्ण,
	अणु
		.name   = "NTSC CCIR601 (QCIF)",
		.width  = 180,
		.height = 120,
		.hscale = 0x0400,
		.vscale = 0x0400,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tw9910_scale_ctrl tw9910_pal_scales[] = अणु
	अणु
		.name   = "PAL SQ",
		.width  = 768,
		.height = 576,
		.hscale = 0x0100,
		.vscale = 0x0100,
	पूर्ण,
	अणु
		.name   = "PAL CCIR601",
		.width  = 720,
		.height = 576,
		.hscale = 0x0100,
		.vscale = 0x0100,
	पूर्ण,
	अणु
		.name   = "PAL SQ (CIF)",
		.width  = 384,
		.height = 288,
		.hscale = 0x0200,
		.vscale = 0x0200,
	पूर्ण,
	अणु
		.name   = "PAL CCIR601 (CIF)",
		.width  = 360,
		.height = 288,
		.hscale = 0x0200,
		.vscale = 0x0200,
	पूर्ण,
	अणु
		.name   = "PAL SQ (QCIF)",
		.width  = 192,
		.height = 144,
		.hscale = 0x0400,
		.vscale = 0x0400,
	पूर्ण,
	अणु
		.name   = "PAL CCIR601 (QCIF)",
		.width  = 180,
		.height = 144,
		.hscale = 0x0400,
		.vscale = 0x0400,
	पूर्ण,
पूर्ण;

/*
 * general function
 */
अटल काष्ठा tw9910_priv *to_tw9910(स्थिर काष्ठा i2c_client *client)
अणु
	वापस container_of(i2c_get_clientdata(client), काष्ठा tw9910_priv,
			    subdev);
पूर्ण

अटल पूर्णांक tw9910_mask_set(काष्ठा i2c_client *client, u8 command,
			   u8 mask, u8 set)
अणु
	s32 val = i2c_smbus_पढ़ो_byte_data(client, command);

	अगर (val < 0)
		वापस val;

	val &= ~mask;
	val |= set & mask;

	वापस i2c_smbus_ग_लिखो_byte_data(client, command, val);
पूर्ण

अटल पूर्णांक tw9910_set_scale(काष्ठा i2c_client *client,
			    स्थिर काष्ठा tw9910_scale_ctrl *scale)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, SCALE_HI,
					(scale->vscale & 0x0F00) >> 4 |
					(scale->hscale & 0x0F00) >> 8);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, HSCALE_LO,
					scale->hscale & 0x00FF);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, VSCALE_LO,
					scale->vscale & 0x00FF);

	वापस ret;
पूर्ण

अटल पूर्णांक tw9910_set_hsync(काष्ठा i2c_client *client)
अणु
	काष्ठा tw9910_priv *priv = to_tw9910(client);
	पूर्णांक ret;

	/* bit 10 - 3 */
	ret = i2c_smbus_ग_लिखो_byte_data(client, HSBEGIN,
					(HSYNC_START & 0x07F8) >> 3);
	अगर (ret < 0)
		वापस ret;

	/* bit 10 - 3 */
	ret = i2c_smbus_ग_लिखो_byte_data(client, HSEND,
					(HSYNC_END & 0x07F8) >> 3);
	अगर (ret < 0)
		वापस ret;

	/* So far only revisions 0 and 1 have been seen. */
	/* bit 2 - 0 */
	अगर (priv->revision == 1)
		ret = tw9910_mask_set(client, HSLOWCTL, 0x77,
				      (HSYNC_START & 0x0007) << 4 |
				      (HSYNC_END   & 0x0007));

	वापस ret;
पूर्ण

अटल व्योम tw9910_reset(काष्ठा i2c_client *client)
अणु
	tw9910_mask_set(client, ACNTL1, SRESET, SRESET);
	usleep_range(1000, 5000);
पूर्ण

अटल पूर्णांक tw9910_घातer(काष्ठा i2c_client *client, पूर्णांक enable)
अणु
	पूर्णांक ret;
	u8 acntl1;
	u8 acntl2;

	अगर (enable) अणु
		acntl1 = 0;
		acntl2 = 0;
	पूर्ण अन्यथा अणु
		acntl1 = CLK_PDN | Y_PDN | C_PDN;
		acntl2 = PLL_PDN;
	पूर्ण

	ret = tw9910_mask_set(client, ACNTL1, ACNTL1_PDN_MASK, acntl1);
	अगर (ret < 0)
		वापस ret;

	वापस tw9910_mask_set(client, ACNTL2, ACNTL2_PDN_MASK, acntl2);
पूर्ण

अटल स्थिर काष्ठा tw9910_scale_ctrl *tw9910_select_norm(v4l2_std_id norm,
							  u32 width, u32 height)
अणु
	स्थिर काष्ठा tw9910_scale_ctrl *scale;
	स्थिर काष्ठा tw9910_scale_ctrl *ret = शून्य;
	__u32 dअगरf = 0xffffffff, पंचांगp;
	पूर्णांक size, i;

	अगर (norm & V4L2_STD_NTSC) अणु
		scale = tw9910_ntsc_scales;
		size = ARRAY_SIZE(tw9910_ntsc_scales);
	पूर्ण अन्यथा अगर (norm & V4L2_STD_PAL) अणु
		scale = tw9910_pal_scales;
		size = ARRAY_SIZE(tw9910_pal_scales);
	पूर्ण अन्यथा अणु
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < size; i++) अणु
		पंचांगp = असल(width - scale[i].width) +
		      असल(height - scale[i].height);
		अगर (पंचांगp < dअगरf) अणु
			dअगरf = पंचांगp;
			ret = scale + i;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * subdevice operations
 */
अटल पूर्णांक tw9910_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा tw9910_priv *priv = to_tw9910(client);
	u8 val;
	पूर्णांक ret;

	अगर (!enable) अणु
		चयन (priv->revision) अणु
		हाल 0:
			val = OEN_TRI_SEL_ALL_OFF_r0;
			अवरोध;
		हाल 1:
			val = OEN_TRI_SEL_ALL_OFF_r1;
			अवरोध;
		शेष:
			dev_err(&client->dev, "un-supported revision\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		val = OEN_TRI_SEL_ALL_ON;

		अगर (!priv->scale) अणु
			dev_err(&client->dev, "norm select error\n");
			वापस -EPERM;
		पूर्ण

		dev_dbg(&client->dev, "%s %dx%d\n",
			priv->scale->name,
			priv->scale->width,
			priv->scale->height);
	पूर्ण

	ret = tw9910_mask_set(client, OPFORM, OEN_TRI_SEL_MASK, val);
	अगर (ret < 0)
		वापस ret;

	वापस tw9910_घातer(client, enable);
पूर्ण

अटल पूर्णांक tw9910_g_std(काष्ठा v4l2_subdev *sd, v4l2_std_id *norm)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा tw9910_priv *priv = to_tw9910(client);

	*norm = priv->norm;

	वापस 0;
पूर्ण

अटल पूर्णांक tw9910_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id norm)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा tw9910_priv *priv = to_tw9910(client);
	स्थिर अचिन्हित पूर्णांक hact = 720;
	स्थिर अचिन्हित पूर्णांक hdelay = 15;
	अचिन्हित पूर्णांक vact;
	अचिन्हित पूर्णांक vdelay;
	पूर्णांक ret;

	अगर (!(norm & (V4L2_STD_NTSC | V4L2_STD_PAL)))
		वापस -EINVAL;

	priv->norm = norm;
	अगर (norm & V4L2_STD_525_60) अणु
		vact = 240;
		vdelay = 18;
		ret = tw9910_mask_set(client, VVBI, 0x10, 0x10);
	पूर्ण अन्यथा अणु
		vact = 288;
		vdelay = 24;
		ret = tw9910_mask_set(client, VVBI, 0x10, 0x00);
	पूर्ण
	अगर (!ret)
		ret = i2c_smbus_ग_लिखो_byte_data(client, CROP_HI,
						((vdelay >> 2) & 0xc0)	|
						((vact >> 4) & 0x30)	|
						((hdelay >> 6) & 0x0c)	|
						((hact >> 8) & 0x03));
	अगर (!ret)
		ret = i2c_smbus_ग_लिखो_byte_data(client, VDELAY_LO,
						vdelay & 0xff);
	अगर (!ret)
		ret = i2c_smbus_ग_लिखो_byte_data(client, VACTIVE_LO,
						vact & 0xff);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक tw9910_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	अगर (reg->reg > 0xff)
		वापस -EINVAL;

	reg->size = 1;
	ret = i2c_smbus_पढ़ो_byte_data(client, reg->reg);
	अगर (ret < 0)
		वापस ret;

	/*
	 * ret      = पूर्णांक
	 * reg->val = __u64
	 */
	reg->val = (__u64)ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tw9910_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			     स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	अगर (reg->reg > 0xff ||
	    reg->val > 0xff)
		वापस -EINVAL;

	वापस i2c_smbus_ग_लिखो_byte_data(client, reg->reg, reg->val);
पूर्ण
#पूर्ण_अगर

अटल व्योम tw9910_set_gpio_value(काष्ठा gpio_desc *desc, पूर्णांक value)
अणु
	अगर (desc) अणु
		gpiod_set_value(desc, value);
		usleep_range(500, 1000);
	पूर्ण
पूर्ण

अटल पूर्णांक tw9910_घातer_on(काष्ठा tw9910_priv *priv)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&priv->subdev);
	पूर्णांक ret;

	अगर (priv->clk) अणु
		ret = clk_prepare_enable(priv->clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	tw9910_set_gpio_value(priv->pdn_gpio, 0);

	/*
	 * FIXME: The reset संकेत is connected to a shared GPIO on some
	 * platक्रमms (namely the SuperH Migo-R). Until a framework becomes
	 * available to handle this cleanly, request the GPIO temporarily
	 * to aव्योम conflicts.
	 */
	priv->rstb_gpio = gpiod_get_optional(&client->dev, "rstb",
					     GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->rstb_gpio)) अणु
		dev_info(&client->dev, "Unable to get GPIO \"rstb\"");
		clk_disable_unprepare(priv->clk);
		tw9910_set_gpio_value(priv->pdn_gpio, 1);
		वापस PTR_ERR(priv->rstb_gpio);
	पूर्ण

	अगर (priv->rstb_gpio) अणु
		tw9910_set_gpio_value(priv->rstb_gpio, 1);
		tw9910_set_gpio_value(priv->rstb_gpio, 0);

		gpiod_put(priv->rstb_gpio);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tw9910_घातer_off(काष्ठा tw9910_priv *priv)
अणु
	clk_disable_unprepare(priv->clk);
	tw9910_set_gpio_value(priv->pdn_gpio, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक tw9910_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा tw9910_priv *priv = to_tw9910(client);

	वापस on ? tw9910_घातer_on(priv) : tw9910_घातer_off(priv);
पूर्ण

अटल पूर्णांक tw9910_set_frame(काष्ठा v4l2_subdev *sd, u32 *width, u32 *height)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा tw9910_priv *priv = to_tw9910(client);
	पूर्णांक ret = -EINVAL;
	u8 val;

	/* Select suitable norm. */
	priv->scale = tw9910_select_norm(priv->norm, *width, *height);
	अगर (!priv->scale)
		जाओ tw9910_set_fmt_error;

	/* Reset hardware. */
	tw9910_reset(client);

	/* Set bus width. */
	val = 0x00;
	अगर (priv->info->buswidth == 16)
		val = LEN;

	ret = tw9910_mask_set(client, OPFORM, LEN, val);
	अगर (ret < 0)
		जाओ tw9910_set_fmt_error;

	/* Select MPOUT behavior. */
	चयन (priv->info->mpout) अणु
	हाल TW9910_MPO_VLOSS:
		val = RTSEL_VLOSS; अवरोध;
	हाल TW9910_MPO_HLOCK:
		val = RTSEL_HLOCK; अवरोध;
	हाल TW9910_MPO_SLOCK:
		val = RTSEL_SLOCK; अवरोध;
	हाल TW9910_MPO_VLOCK:
		val = RTSEL_VLOCK; अवरोध;
	हाल TW9910_MPO_MONO:
		val = RTSEL_MONO;  अवरोध;
	हाल TW9910_MPO_DET50:
		val = RTSEL_DET50; अवरोध;
	हाल TW9910_MPO_FIELD:
		val = RTSEL_FIELD; अवरोध;
	हाल TW9910_MPO_RTCO:
		val = RTSEL_RTCO;  अवरोध;
	शेष:
		val = 0;
	पूर्ण

	ret = tw9910_mask_set(client, VBICNTL, RTSEL_MASK, val);
	अगर (ret < 0)
		जाओ tw9910_set_fmt_error;

	/* Set scale. */
	ret = tw9910_set_scale(client, priv->scale);
	अगर (ret < 0)
		जाओ tw9910_set_fmt_error;

	/* Set hsync. */
	ret = tw9910_set_hsync(client);
	अगर (ret < 0)
		जाओ tw9910_set_fmt_error;

	*width = priv->scale->width;
	*height = priv->scale->height;

	वापस ret;

tw9910_set_fmt_error:

	tw9910_reset(client);
	priv->scale = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक tw9910_get_selection(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा tw9910_priv *priv = to_tw9910(client);

	अगर (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस -EINVAL;
	/* Only CROP, CROP_DEFAULT and CROP_BOUNDS are supported. */
	अगर (sel->target > V4L2_SEL_TGT_CROP_BOUNDS)
		वापस -EINVAL;

	sel->r.left	= 0;
	sel->r.top	= 0;
	अगर (priv->norm & V4L2_STD_NTSC) अणु
		sel->r.width	= 640;
		sel->r.height	= 480;
	पूर्ण अन्यथा अणु
		sel->r.width	= 768;
		sel->r.height	= 576;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tw9910_get_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा tw9910_priv *priv = to_tw9910(client);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	अगर (!priv->scale) अणु
		priv->scale = tw9910_select_norm(priv->norm, 640, 480);
		अगर (!priv->scale)
			वापस -EINVAL;
	पूर्ण

	mf->width	= priv->scale->width;
	mf->height	= priv->scale->height;
	mf->code	= MEDIA_BUS_FMT_UYVY8_2X8;
	mf->colorspace	= V4L2_COLORSPACE_SMPTE170M;
	mf->field	= V4L2_FIELD_INTERLACED_BT;

	वापस 0;
पूर्ण

अटल पूर्णांक tw9910_s_fmt(काष्ठा v4l2_subdev *sd,
			काष्ठा v4l2_mbus_framefmt *mf)
अणु
	u32 width = mf->width, height = mf->height;
	पूर्णांक ret;

	WARN_ON(mf->field != V4L2_FIELD_ANY &&
		mf->field != V4L2_FIELD_INTERLACED_BT);

	/* Check color क्रमmat. */
	अगर (mf->code != MEDIA_BUS_FMT_UYVY8_2X8)
		वापस -EINVAL;

	mf->colorspace = V4L2_COLORSPACE_SMPTE170M;

	ret = tw9910_set_frame(sd, &width, &height);
	अगर (ret)
		वापस ret;

	mf->width	= width;
	mf->height	= height;

	वापस 0;
पूर्ण

अटल पूर्णांक tw9910_set_fmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा tw9910_priv *priv = to_tw9910(client);
	स्थिर काष्ठा tw9910_scale_ctrl *scale;

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	अगर (mf->field == V4L2_FIELD_ANY) अणु
		mf->field = V4L2_FIELD_INTERLACED_BT;
	पूर्ण अन्यथा अगर (mf->field != V4L2_FIELD_INTERLACED_BT) अणु
		dev_err(&client->dev, "Field type %d invalid\n", mf->field);
		वापस -EINVAL;
	पूर्ण

	mf->code = MEDIA_BUS_FMT_UYVY8_2X8;
	mf->colorspace = V4L2_COLORSPACE_SMPTE170M;

	/* Select suitable norm. */
	scale = tw9910_select_norm(priv->norm, mf->width, mf->height);
	अगर (!scale)
		वापस -EINVAL;

	mf->width	= scale->width;
	mf->height	= scale->height;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस tw9910_s_fmt(sd, mf);

	cfg->try_fmt = *mf;

	वापस 0;
पूर्ण

अटल पूर्णांक tw9910_video_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा tw9910_priv *priv = to_tw9910(client);
	s32 id;
	पूर्णांक ret;

	/* TW9910 only use 8 or 16 bit bus width. */
	अगर (priv->info->buswidth != 16 && priv->info->buswidth != 8) अणु
		dev_err(&client->dev, "bus width error\n");
		वापस -ENODEV;
	पूर्ण

	ret = tw9910_s_घातer(&priv->subdev, 1);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Check and show Product ID.
	 * So far only revisions 0 and 1 have been seen.
	 */
	id = i2c_smbus_पढ़ो_byte_data(client, ID);
	priv->revision = GET_REV(id);
	id = GET_ID(id);

	अगर (id != 0x0b || priv->revision > 0x01) अणु
		dev_err(&client->dev, "Product ID error %x:%x\n",
			id, priv->revision);
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	dev_info(&client->dev, "tw9910 Product ID %0x:%0x\n",
		 id, priv->revision);

	priv->norm = V4L2_STD_NTSC;
	priv->scale = &tw9910_ntsc_scales[0];

करोne:
	tw9910_s_घातer(&priv->subdev, 0);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops tw9910_subdev_core_ops = अणु
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर	= tw9910_g_रेजिस्टर,
	.s_रेजिस्टर	= tw9910_s_रेजिस्टर,
#पूर्ण_अगर
	.s_घातer	= tw9910_s_घातer,
पूर्ण;

अटल पूर्णांक tw9910_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index)
		वापस -EINVAL;

	code->code = MEDIA_BUS_FMT_UYVY8_2X8;

	वापस 0;
पूर्ण

अटल पूर्णांक tw9910_g_tvnorms(काष्ठा v4l2_subdev *sd, v4l2_std_id *norm)
अणु
	*norm = V4L2_STD_NTSC | V4L2_STD_PAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops tw9910_subdev_video_ops = अणु
	.s_std		= tw9910_s_std,
	.g_std		= tw9910_g_std,
	.s_stream	= tw9910_s_stream,
	.g_tvnorms	= tw9910_g_tvnorms,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops tw9910_subdev_pad_ops = अणु
	.क्रमागत_mbus_code = tw9910_क्रमागत_mbus_code,
	.get_selection	= tw9910_get_selection,
	.get_fmt	= tw9910_get_fmt,
	.set_fmt	= tw9910_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops tw9910_subdev_ops = अणु
	.core	= &tw9910_subdev_core_ops,
	.video	= &tw9910_subdev_video_ops,
	.pad	= &tw9910_subdev_pad_ops,
पूर्ण;

/*
 * i2c_driver function
 */

अटल पूर्णांक tw9910_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *did)

अणु
	काष्ठा tw9910_priv		*priv;
	काष्ठा tw9910_video_info	*info;
	काष्ठा i2c_adapter		*adapter = client->adapter;
	पूर्णांक ret;

	अगर (!client->dev.platक्रमm_data) अणु
		dev_err(&client->dev, "TW9910: missing platform data!\n");
		वापस -EINVAL;
	पूर्ण

	info = client->dev.platक्रमm_data;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(&client->dev,
			"I2C-Adapter doesn't support I2C_FUNC_SMBUS_BYTE_DATA\n");
		वापस -EIO;
	पूर्ण

	priv = devm_kzalloc(&client->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->info = info;

	v4l2_i2c_subdev_init(&priv->subdev, client, &tw9910_subdev_ops);

	priv->clk = clk_get(&client->dev, "xti");
	अगर (PTR_ERR(priv->clk) == -ENOENT) अणु
		priv->clk = शून्य;
	पूर्ण अन्यथा अगर (IS_ERR(priv->clk)) अणु
		dev_err(&client->dev, "Unable to get xti clock\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	priv->pdn_gpio = gpiod_get_optional(&client->dev, "pdn",
					    GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->pdn_gpio)) अणु
		dev_info(&client->dev, "Unable to get GPIO \"pdn\"");
		ret = PTR_ERR(priv->pdn_gpio);
		जाओ error_clk_put;
	पूर्ण

	ret = tw9910_video_probe(client);
	अगर (ret < 0)
		जाओ error_gpio_put;

	ret = v4l2_async_रेजिस्टर_subdev(&priv->subdev);
	अगर (ret)
		जाओ error_gpio_put;

	वापस ret;

error_gpio_put:
	अगर (priv->pdn_gpio)
		gpiod_put(priv->pdn_gpio);
error_clk_put:
	clk_put(priv->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक tw9910_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tw9910_priv *priv = to_tw9910(client);

	अगर (priv->pdn_gpio)
		gpiod_put(priv->pdn_gpio);
	clk_put(priv->clk);
	v4l2_async_unरेजिस्टर_subdev(&priv->subdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tw9910_id[] = अणु
	अणु "tw9910", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tw9910_id);

अटल काष्ठा i2c_driver tw9910_i2c_driver = अणु
	.driver = अणु
		.name = "tw9910",
	पूर्ण,
	.probe    = tw9910_probe,
	.हटाओ   = tw9910_हटाओ,
	.id_table = tw9910_id,
पूर्ण;

module_i2c_driver(tw9910_i2c_driver);

MODULE_DESCRIPTION("V4L2 driver for TW9910 video decoder");
MODULE_AUTHOR("Kuninori Morimoto");
MODULE_LICENSE("GPL v2");
