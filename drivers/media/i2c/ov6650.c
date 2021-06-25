<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * V4L2 subdevice driver क्रम OmniVision OV6650 Camera Sensor
 *
 * Copyright (C) 2010 Janusz Krzysztofik <jkrzyszt@tis.icnet.pl>
 *
 * Based on OmniVision OV96xx Camera Driver
 * Copyright (C) 2009 Marek Vasut <marek.vasut@gmail.com>
 *
 * Based on ov772x camera driver:
 * Copyright (C) 2008 Renesas Solutions Corp.
 * Kuninori Morimoto <morimoto.kuninori@renesas.com>
 *
 * Based on ov7670 and soc_camera_platक्रमm driver,
 * Copyright 2006-7 Jonathan Corbet <corbet@lwn.net>
 * Copyright (C) 2008 Magnus Damm
 * Copyright (C) 2008, Guennadi Liakhovetski <kernel@pengutronix.de>
 *
 * Hardware specअगरic bits initially based on क्रमmer work by Matt Callow
 * drivers/media/video/omap/sensor_ov6650.c
 * Copyright (C) 2006 Matt Callow
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <linux/module.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>

/* Register definitions */
#घोषणा REG_GAIN		0x00	/* range 00 - 3F */
#घोषणा REG_BLUE		0x01
#घोषणा REG_RED			0x02
#घोषणा REG_SAT			0x03	/* [7:4] saturation [0:3] reserved */
#घोषणा REG_HUE			0x04	/* [7:6] rsrvd [5] hue en [4:0] hue */

#घोषणा REG_BRT			0x06

#घोषणा REG_PIDH		0x0a
#घोषणा REG_PIDL		0x0b

#घोषणा REG_AECH		0x10
#घोषणा REG_CLKRC		0x11	/* Data Format and Internal Clock */
					/* [7:6] Input प्रणाली घड़ी (MHz)*/
					/*   00=8, 01=12, 10=16, 11=24 */
					/* [5:0]: Internal Clock Pre-Scaler */
#घोषणा REG_COMA		0x12	/* [7] Reset */
#घोषणा REG_COMB		0x13
#घोषणा REG_COMC		0x14
#घोषणा REG_COMD		0x15
#घोषणा REG_COML		0x16
#घोषणा REG_HSTRT		0x17
#घोषणा REG_HSTOP		0x18
#घोषणा REG_VSTRT		0x19
#घोषणा REG_VSTOP		0x1a
#घोषणा REG_PSHFT		0x1b
#घोषणा REG_MIDH		0x1c
#घोषणा REG_MIDL		0x1d
#घोषणा REG_HSYNS		0x1e
#घोषणा REG_HSYNE		0x1f
#घोषणा REG_COME		0x20
#घोषणा REG_YOFF		0x21
#घोषणा REG_UOFF		0x22
#घोषणा REG_VOFF		0x23
#घोषणा REG_AEW			0x24
#घोषणा REG_AEB			0x25
#घोषणा REG_COMF		0x26
#घोषणा REG_COMG		0x27
#घोषणा REG_COMH		0x28
#घोषणा REG_COMI		0x29

#घोषणा REG_FRARL		0x2b
#घोषणा REG_COMJ		0x2c
#घोषणा REG_COMK		0x2d
#घोषणा REG_AVGY		0x2e
#घोषणा REG_REF0		0x2f
#घोषणा REG_REF1		0x30
#घोषणा REG_REF2		0x31
#घोषणा REG_FRAJH		0x32
#घोषणा REG_FRAJL		0x33
#घोषणा REG_FACT		0x34
#घोषणा REG_L1AEC		0x35
#घोषणा REG_AVGU		0x36
#घोषणा REG_AVGV		0x37

#घोषणा REG_SPCB		0x60
#घोषणा REG_SPCC		0x61
#घोषणा REG_GAM1		0x62
#घोषणा REG_GAM2		0x63
#घोषणा REG_GAM3		0x64
#घोषणा REG_SPCD		0x65

#घोषणा REG_SPCE		0x68
#घोषणा REG_ADCL		0x69

#घोषणा REG_RMCO		0x6c
#घोषणा REG_GMCO		0x6d
#घोषणा REG_BMCO		0x6e


/* Register bits, values, etc. */
#घोषणा OV6650_PIDH		0x66	/* high byte of product ID number */
#घोषणा OV6650_PIDL		0x50	/* low byte of product ID number */
#घोषणा OV6650_MIDH		0x7F	/* high byte of mfg ID */
#घोषणा OV6650_MIDL		0xA2	/* low byte of mfg ID */

#घोषणा DEF_GAIN		0x00
#घोषणा DEF_BLUE		0x80
#घोषणा DEF_RED			0x80

#घोषणा SAT_SHIFT		4
#घोषणा SAT_MASK		(0xf << SAT_SHIFT)
#घोषणा SET_SAT(x)		(((x) << SAT_SHIFT) & SAT_MASK)

#घोषणा HUE_EN			BIT(5)
#घोषणा HUE_MASK		0x1f
#घोषणा DEF_HUE			0x10
#घोषणा SET_HUE(x)		(HUE_EN | ((x) & HUE_MASK))

#घोषणा DEF_AECH		0x4D

#घोषणा CLKRC_8MHz		0x00
#घोषणा CLKRC_12MHz		0x40
#घोषणा CLKRC_16MHz		0x80
#घोषणा CLKRC_24MHz		0xc0
#घोषणा CLKRC_DIV_MASK		0x3f
#घोषणा GET_CLKRC_DIV(x)	(((x) & CLKRC_DIV_MASK) + 1)
#घोषणा DEF_CLKRC		0x00

#घोषणा COMA_RESET		BIT(7)
#घोषणा COMA_QCIF		BIT(5)
#घोषणा COMA_RAW_RGB		BIT(4)
#घोषणा COMA_RGB		BIT(3)
#घोषणा COMA_BW			BIT(2)
#घोषणा COMA_WORD_SWAP		BIT(1)
#घोषणा COMA_BYTE_SWAP		BIT(0)
#घोषणा DEF_COMA		0x00

#घोषणा COMB_FLIP_V		BIT(7)
#घोषणा COMB_FLIP_H		BIT(5)
#घोषणा COMB_BAND_FILTER	BIT(4)
#घोषणा COMB_AWB		BIT(2)
#घोषणा COMB_AGC		BIT(1)
#घोषणा COMB_AEC		BIT(0)
#घोषणा DEF_COMB		0x5f

#घोषणा COML_ONE_CHANNEL	BIT(7)

#घोषणा DEF_HSTRT		0x24
#घोषणा DEF_HSTOP		0xd4
#घोषणा DEF_VSTRT		0x04
#घोषणा DEF_VSTOP		0x94

#घोषणा COMF_HREF_LOW		BIT(4)

#घोषणा COMJ_PCLK_RISING	BIT(4)
#घोषणा COMJ_VSYNC_HIGH		BIT(0)

/* supported resolutions */
#घोषणा W_QCIF			(DEF_HSTOP - DEF_HSTRT)
#घोषणा W_CIF			(W_QCIF << 1)
#घोषणा H_QCIF			(DEF_VSTOP - DEF_VSTRT)
#घोषणा H_CIF			(H_QCIF << 1)

#घोषणा FRAME_RATE_MAX		30


काष्ठा ov6650_reg अणु
	u8	reg;
	u8	val;
पूर्ण;

काष्ठा ov6650 अणु
	काष्ठा v4l2_subdev	subdev;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा अणु
		/* exposure/स्वतःexposure cluster */
		काष्ठा v4l2_ctrl *स्वतःexposure;
		काष्ठा v4l2_ctrl *exposure;
	पूर्ण;
	काष्ठा अणु
		/* gain/स्वतःgain cluster */
		काष्ठा v4l2_ctrl *स्वतःgain;
		काष्ठा v4l2_ctrl *gain;
	पूर्ण;
	काष्ठा अणु
		/* blue/red/स्वतःwhitebalance cluster */
		काष्ठा v4l2_ctrl *स्वतःwb;
		काष्ठा v4l2_ctrl *blue;
		काष्ठा v4l2_ctrl *red;
	पूर्ण;
	काष्ठा clk		*clk;
	bool			half_scale;	/* scale करोwn output by 2 */
	काष्ठा v4l2_rect	rect;		/* sensor cropping winकरोw */
	काष्ठा v4l2_fract	tpf;		/* as requested with s_frame_पूर्णांकerval */
	u32 code;
पूर्ण;

काष्ठा ov6650_xclk अणु
	अचिन्हित दीर्घ	rate;
	u8		clkrc;
पूर्ण;

अटल स्थिर काष्ठा ov6650_xclk ov6650_xclk[] = अणु
अणु
	.rate	= 8000000,
	.clkrc	= CLKRC_8MHz,
पूर्ण,
अणु
	.rate	= 12000000,
	.clkrc	= CLKRC_12MHz,
पूर्ण,
अणु
	.rate	= 16000000,
	.clkrc	= CLKRC_16MHz,
पूर्ण,
अणु
	.rate	= 24000000,
	.clkrc	= CLKRC_24MHz,
पूर्ण,
पूर्ण;

अटल u32 ov6650_codes[] = अणु
	MEDIA_BUS_FMT_YUYV8_2X8,
	MEDIA_BUS_FMT_UYVY8_2X8,
	MEDIA_BUS_FMT_YVYU8_2X8,
	MEDIA_BUS_FMT_VYUY8_2X8,
	MEDIA_BUS_FMT_SBGGR8_1X8,
	MEDIA_BUS_FMT_Y8_1X8,
पूर्ण;

अटल स्थिर काष्ठा v4l2_mbus_framefmt ov6650_def_fmt = अणु
	.width		= W_CIF,
	.height		= H_CIF,
	.code		= MEDIA_BUS_FMT_SBGGR8_1X8,
	.colorspace	= V4L2_COLORSPACE_SRGB,
	.field		= V4L2_FIELD_NONE,
	.ycbcr_enc	= V4L2_YCBCR_ENC_DEFAULT,
	.quantization	= V4L2_QUANTIZATION_DEFAULT,
	.xfer_func	= V4L2_XFER_FUNC_DEFAULT,
पूर्ण;

/* पढ़ो a रेजिस्टर */
अटल पूर्णांक ov6650_reg_पढ़ो(काष्ठा i2c_client *client, u8 reg, u8 *val)
अणु
	पूर्णांक ret;
	u8 data = reg;
	काष्ठा i2c_msg msg = अणु
		.addr	= client->addr,
		.flags	= 0,
		.len	= 1,
		.buf	= &data,
	पूर्ण;

	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret < 0)
		जाओ err;

	msg.flags = I2C_M_RD;
	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret < 0)
		जाओ err;

	*val = data;
	वापस 0;

err:
	dev_err(&client->dev, "Failed reading register 0x%02x!\n", reg);
	वापस ret;
पूर्ण

/* ग_लिखो a रेजिस्टर */
अटल पूर्णांक ov6650_reg_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 val)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर data[2] = अणु reg, val पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr	= client->addr,
		.flags	= 0,
		.len	= 2,
		.buf	= data,
	पूर्ण;

	ret = i2c_transfer(client->adapter, &msg, 1);
	udelay(100);

	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed writing register 0x%02x!\n", reg);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण


/* Read a रेजिस्टर, alter its bits, ग_लिखो it back */
अटल पूर्णांक ov6650_reg_rmw(काष्ठा i2c_client *client, u8 reg, u8 set, u8 mask)
अणु
	u8 val;
	पूर्णांक ret;

	ret = ov6650_reg_पढ़ो(client, reg, &val);
	अगर (ret) अणु
		dev_err(&client->dev,
			"[Read]-Modify-Write of register 0x%02x failed!\n",
			reg);
		वापस ret;
	पूर्ण

	val &= ~mask;
	val |= set;

	ret = ov6650_reg_ग_लिखो(client, reg, val);
	अगर (ret)
		dev_err(&client->dev,
			"Read-Modify-[Write] of register 0x%02x failed!\n",
			reg);

	वापस ret;
पूर्ण

अटल काष्ठा ov6650 *to_ov6650(स्थिर काष्ठा i2c_client *client)
अणु
	वापस container_of(i2c_get_clientdata(client), काष्ठा ov6650, subdev);
पूर्ण

/* Start/Stop streaming from the device */
अटल पूर्णांक ov6650_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	वापस 0;
पूर्ण

/* Get status of additional camera capabilities */
अटल पूर्णांक ov6550_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov6650 *priv = container_of(ctrl->handler, काष्ठा ov6650, hdl);
	काष्ठा v4l2_subdev *sd = &priv->subdev;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	uपूर्णांक8_t reg, reg2;
	पूर्णांक ret;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTOGAIN:
		ret = ov6650_reg_पढ़ो(client, REG_GAIN, &reg);
		अगर (!ret)
			priv->gain->val = reg;
		वापस ret;
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		ret = ov6650_reg_पढ़ो(client, REG_BLUE, &reg);
		अगर (!ret)
			ret = ov6650_reg_पढ़ो(client, REG_RED, &reg2);
		अगर (!ret) अणु
			priv->blue->val = reg;
			priv->red->val = reg2;
		पूर्ण
		वापस ret;
	हाल V4L2_CID_EXPOSURE_AUTO:
		ret = ov6650_reg_पढ़ो(client, REG_AECH, &reg);
		अगर (!ret)
			priv->exposure->val = reg;
		वापस ret;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* Set status of additional camera capabilities */
अटल पूर्णांक ov6550_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov6650 *priv = container_of(ctrl->handler, काष्ठा ov6650, hdl);
	काष्ठा v4l2_subdev *sd = &priv->subdev;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTOGAIN:
		ret = ov6650_reg_rmw(client, REG_COMB,
				ctrl->val ? COMB_AGC : 0, COMB_AGC);
		अगर (!ret && !ctrl->val)
			ret = ov6650_reg_ग_लिखो(client, REG_GAIN, priv->gain->val);
		वापस ret;
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		ret = ov6650_reg_rmw(client, REG_COMB,
				ctrl->val ? COMB_AWB : 0, COMB_AWB);
		अगर (!ret && !ctrl->val) अणु
			ret = ov6650_reg_ग_लिखो(client, REG_BLUE, priv->blue->val);
			अगर (!ret)
				ret = ov6650_reg_ग_लिखो(client, REG_RED,
							priv->red->val);
		पूर्ण
		वापस ret;
	हाल V4L2_CID_SATURATION:
		वापस ov6650_reg_rmw(client, REG_SAT, SET_SAT(ctrl->val),
				SAT_MASK);
	हाल V4L2_CID_HUE:
		वापस ov6650_reg_rmw(client, REG_HUE, SET_HUE(ctrl->val),
				HUE_MASK);
	हाल V4L2_CID_BRIGHTNESS:
		वापस ov6650_reg_ग_लिखो(client, REG_BRT, ctrl->val);
	हाल V4L2_CID_EXPOSURE_AUTO:
		ret = ov6650_reg_rmw(client, REG_COMB, ctrl->val ==
				V4L2_EXPOSURE_AUTO ? COMB_AEC : 0, COMB_AEC);
		अगर (!ret && ctrl->val == V4L2_EXPOSURE_MANUAL)
			ret = ov6650_reg_ग_लिखो(client, REG_AECH,
						priv->exposure->val);
		वापस ret;
	हाल V4L2_CID_GAMMA:
		वापस ov6650_reg_ग_लिखो(client, REG_GAM1, ctrl->val);
	हाल V4L2_CID_VFLIP:
		वापस ov6650_reg_rmw(client, REG_COMB,
				ctrl->val ? COMB_FLIP_V : 0, COMB_FLIP_V);
	हाल V4L2_CID_HFLIP:
		वापस ov6650_reg_rmw(client, REG_COMB,
				ctrl->val ? COMB_FLIP_H : 0, COMB_FLIP_H);
	पूर्ण

	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक ov6650_get_रेजिस्टर(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;
	u8 val;

	अगर (reg->reg & ~0xff)
		वापस -EINVAL;

	reg->size = 1;

	ret = ov6650_reg_पढ़ो(client, reg->reg, &val);
	अगर (!ret)
		reg->val = (__u64)val;

	वापस ret;
पूर्ण

अटल पूर्णांक ov6650_set_रेजिस्टर(काष्ठा v4l2_subdev *sd,
				स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	अगर (reg->reg & ~0xff || reg->val & ~0xff)
		वापस -EINVAL;

	वापस ov6650_reg_ग_लिखो(client, reg->reg, reg->val);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ov6650_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov6650 *priv = to_ov6650(client);
	पूर्णांक ret = 0;

	अगर (on)
		ret = clk_prepare_enable(priv->clk);
	अन्यथा
		clk_disable_unprepare(priv->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक ov6650_get_selection(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov6650 *priv = to_ov6650(client);

	अगर (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.left = DEF_HSTRT << 1;
		sel->r.top = DEF_VSTRT << 1;
		sel->r.width = W_CIF;
		sel->r.height = H_CIF;
		वापस 0;
	हाल V4L2_SEL_TGT_CROP:
		sel->r = priv->rect;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ov6650_set_selection(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov6650 *priv = to_ov6650(client);
	पूर्णांक ret;

	अगर (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE ||
	    sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	v4l_bound_align_image(&sel->r.width, 2, W_CIF, 1,
			      &sel->r.height, 2, H_CIF, 1, 0);
	v4l_bound_align_image(&sel->r.left, DEF_HSTRT << 1,
			      (DEF_HSTRT << 1) + W_CIF - (__s32)sel->r.width, 1,
			      &sel->r.top, DEF_VSTRT << 1,
			      (DEF_VSTRT << 1) + H_CIF - (__s32)sel->r.height,
			      1, 0);

	ret = ov6650_reg_ग_लिखो(client, REG_HSTRT, sel->r.left >> 1);
	अगर (!ret) अणु
		priv->rect.width += priv->rect.left - sel->r.left;
		priv->rect.left = sel->r.left;
		ret = ov6650_reg_ग_लिखो(client, REG_HSTOP,
				       (sel->r.left + sel->r.width) >> 1);
	पूर्ण
	अगर (!ret) अणु
		priv->rect.width = sel->r.width;
		ret = ov6650_reg_ग_लिखो(client, REG_VSTRT, sel->r.top >> 1);
	पूर्ण
	अगर (!ret) अणु
		priv->rect.height += priv->rect.top - sel->r.top;
		priv->rect.top = sel->r.top;
		ret = ov6650_reg_ग_लिखो(client, REG_VSTOP,
				       (sel->r.top + sel->r.height) >> 1);
	पूर्ण
	अगर (!ret)
		priv->rect.height = sel->r.height;

	वापस ret;
पूर्ण

अटल पूर्णांक ov6650_get_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov6650 *priv = to_ov6650(client);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	/* initialize response with शेष media bus frame क्रमmat */
	*mf = ov6650_def_fmt;

	/* update media bus क्रमmat code and frame size */
	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		mf->width = cfg->try_fmt.width;
		mf->height = cfg->try_fmt.height;
		mf->code = cfg->try_fmt.code;

	पूर्ण अन्यथा अणु
		mf->width = priv->rect.width >> priv->half_scale;
		mf->height = priv->rect.height >> priv->half_scale;
		mf->code = priv->code;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool is_unscaled_ok(पूर्णांक width, पूर्णांक height, काष्ठा v4l2_rect *rect)
अणु
	वापस width > rect->width >> 1 || height > rect->height >> 1;
पूर्ण

#घोषणा to_clkrc(भाग)	((भाग) - 1)

/* set the क्रमmat we will capture in */
अटल पूर्णांक ov6650_s_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_mbus_framefmt *mf)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov6650 *priv = to_ov6650(client);
	bool half_scale = !is_unscaled_ok(mf->width, mf->height, &priv->rect);
	काष्ठा v4l2_subdev_selection sel = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		.target = V4L2_SEL_TGT_CROP,
		.r.left = priv->rect.left + (priv->rect.width >> 1) -
			(mf->width >> (1 - half_scale)),
		.r.top = priv->rect.top + (priv->rect.height >> 1) -
			(mf->height >> (1 - half_scale)),
		.r.width = mf->width << half_scale,
		.r.height = mf->height << half_scale,
	पूर्ण;
	u32 code = mf->code;
	u8 coma_set = 0, coma_mask = 0, coml_set, coml_mask;
	पूर्णांक ret;

	/* select color matrix configuration क्रम given color encoding */
	चयन (code) अणु
	हाल MEDIA_BUS_FMT_Y8_1X8:
		dev_dbg(&client->dev, "pixel format GREY8_1X8\n");
		coma_mask |= COMA_RGB | COMA_WORD_SWAP | COMA_BYTE_SWAP;
		coma_set |= COMA_BW;
		अवरोध;
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
		dev_dbg(&client->dev, "pixel format YUYV8_2X8_LE\n");
		coma_mask |= COMA_RGB | COMA_BW | COMA_BYTE_SWAP;
		coma_set |= COMA_WORD_SWAP;
		अवरोध;
	हाल MEDIA_BUS_FMT_YVYU8_2X8:
		dev_dbg(&client->dev, "pixel format YVYU8_2X8_LE (untested)\n");
		coma_mask |= COMA_RGB | COMA_BW | COMA_WORD_SWAP |
				COMA_BYTE_SWAP;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
		dev_dbg(&client->dev, "pixel format YUYV8_2X8_BE\n");
		अगर (half_scale) अणु
			coma_mask |= COMA_RGB | COMA_BW | COMA_WORD_SWAP;
			coma_set |= COMA_BYTE_SWAP;
		पूर्ण अन्यथा अणु
			coma_mask |= COMA_RGB | COMA_BW;
			coma_set |= COMA_BYTE_SWAP | COMA_WORD_SWAP;
		पूर्ण
		अवरोध;
	हाल MEDIA_BUS_FMT_VYUY8_2X8:
		dev_dbg(&client->dev, "pixel format YVYU8_2X8_BE (untested)\n");
		अगर (half_scale) अणु
			coma_mask |= COMA_RGB | COMA_BW;
			coma_set |= COMA_BYTE_SWAP | COMA_WORD_SWAP;
		पूर्ण अन्यथा अणु
			coma_mask |= COMA_RGB | COMA_BW | COMA_WORD_SWAP;
			coma_set |= COMA_BYTE_SWAP;
		पूर्ण
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
		dev_dbg(&client->dev, "pixel format SBGGR8_1X8 (untested)\n");
		coma_mask |= COMA_BW | COMA_BYTE_SWAP | COMA_WORD_SWAP;
		coma_set |= COMA_RAW_RGB | COMA_RGB;
		अवरोध;
	शेष:
		dev_err(&client->dev, "Pixel format not handled: 0x%x\n", code);
		वापस -EINVAL;
	पूर्ण

	अगर (code == MEDIA_BUS_FMT_Y8_1X8 ||
			code == MEDIA_BUS_FMT_SBGGR8_1X8) अणु
		coml_mask = COML_ONE_CHANNEL;
		coml_set = 0;
	पूर्ण अन्यथा अणु
		coml_mask = 0;
		coml_set = COML_ONE_CHANNEL;
	पूर्ण

	अगर (half_scale) अणु
		dev_dbg(&client->dev, "max resolution: QCIF\n");
		coma_set |= COMA_QCIF;
	पूर्ण अन्यथा अणु
		dev_dbg(&client->dev, "max resolution: CIF\n");
		coma_mask |= COMA_QCIF;
	पूर्ण

	ret = ov6650_set_selection(sd, शून्य, &sel);
	अगर (!ret)
		ret = ov6650_reg_rmw(client, REG_COMA, coma_set, coma_mask);
	अगर (!ret) अणु
		priv->half_scale = half_scale;

		ret = ov6650_reg_rmw(client, REG_COML, coml_set, coml_mask);
	पूर्ण
	अगर (!ret)
		priv->code = code;

	वापस ret;
पूर्ण

अटल पूर्णांक ov6650_set_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov6650 *priv = to_ov6650(client);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	अगर (is_unscaled_ok(mf->width, mf->height, &priv->rect))
		v4l_bound_align_image(&mf->width, 2, W_CIF, 1,
				&mf->height, 2, H_CIF, 1, 0);

	चयन (mf->code) अणु
	हाल MEDIA_BUS_FMT_Y10_1X10:
		mf->code = MEDIA_BUS_FMT_Y8_1X8;
		fallthrough;
	हाल MEDIA_BUS_FMT_Y8_1X8:
	हाल MEDIA_BUS_FMT_YVYU8_2X8:
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
	हाल MEDIA_BUS_FMT_VYUY8_2X8:
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
		अवरोध;
	शेष:
		mf->code = MEDIA_BUS_FMT_SBGGR8_1X8;
		fallthrough;
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
		अवरोध;
	पूर्ण

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		/* store media bus क्रमmat code and frame size in pad config */
		cfg->try_fmt.width = mf->width;
		cfg->try_fmt.height = mf->height;
		cfg->try_fmt.code = mf->code;

		/* वापस शेष mbus frame क्रमmat updated with pad config */
		*mf = ov6650_def_fmt;
		mf->width = cfg->try_fmt.width;
		mf->height = cfg->try_fmt.height;
		mf->code = cfg->try_fmt.code;

	पूर्ण अन्यथा अणु
		/* apply new media bus क्रमmat code and frame size */
		पूर्णांक ret = ov6650_s_fmt(sd, mf);

		अगर (ret)
			वापस ret;

		/* वापस शेष क्रमmat updated with active size and code */
		*mf = ov6650_def_fmt;
		mf->width = priv->rect.width >> priv->half_scale;
		mf->height = priv->rect.height >> priv->half_scale;
		mf->code = priv->code;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ov6650_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index >= ARRAY_SIZE(ov6650_codes))
		वापस -EINVAL;

	code->code = ov6650_codes[code->index];
	वापस 0;
पूर्ण

अटल पूर्णांक ov6650_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *ival)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov6650 *priv = to_ov6650(client);

	ival->पूर्णांकerval = priv->tpf;

	dev_dbg(&client->dev, "Frame interval: %u/%u s\n",
		ival->पूर्णांकerval.numerator, ival->पूर्णांकerval.denominator);

	वापस 0;
पूर्ण

अटल पूर्णांक ov6650_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *ival)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov6650 *priv = to_ov6650(client);
	काष्ठा v4l2_fract *tpf = &ival->पूर्णांकerval;
	पूर्णांक भाग, ret;

	अगर (tpf->numerator == 0 || tpf->denominator == 0)
		भाग = 1;  /* Reset to full rate */
	अन्यथा
		भाग = (tpf->numerator * FRAME_RATE_MAX) / tpf->denominator;

	अगर (भाग == 0)
		भाग = 1;
	अन्यथा अगर (भाग > GET_CLKRC_DIV(CLKRC_DIV_MASK))
		भाग = GET_CLKRC_DIV(CLKRC_DIV_MASK);

	ret = ov6650_reg_rmw(client, REG_CLKRC, to_clkrc(भाग), CLKRC_DIV_MASK);
	अगर (!ret) अणु
		priv->tpf.numerator = भाग;
		priv->tpf.denominator = FRAME_RATE_MAX;

		*tpf = priv->tpf;
	पूर्ण

	वापस ret;
पूर्ण

/* Soft reset the camera. This has nothing to करो with the RESET pin! */
अटल पूर्णांक ov6650_reset(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;

	dev_dbg(&client->dev, "reset\n");

	ret = ov6650_reg_rmw(client, REG_COMA, COMA_RESET, 0);
	अगर (ret)
		dev_err(&client->dev,
			"An error occurred while entering soft reset!\n");

	वापस ret;
पूर्ण

/* program शेष रेजिस्टर values */
अटल पूर्णांक ov6650_prog_dflt(काष्ठा i2c_client *client, u8 clkrc)
अणु
	पूर्णांक ret;

	dev_dbg(&client->dev, "initializing\n");

	ret = ov6650_reg_ग_लिखो(client, REG_COMA, 0);	/* ~COMA_RESET */
	अगर (!ret)
		ret = ov6650_reg_ग_लिखो(client, REG_CLKRC, clkrc);
	अगर (!ret)
		ret = ov6650_reg_rmw(client, REG_COMB, 0, COMB_BAND_FILTER);

	वापस ret;
पूर्ण

अटल पूर्णांक ov6650_video_probe(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov6650 *priv = to_ov6650(client);
	स्थिर काष्ठा ov6650_xclk *xclk = शून्य;
	अचिन्हित दीर्घ rate;
	u8 pidh, pidl, midh, midl;
	पूर्णांक i, ret = 0;

	priv->clk = devm_clk_get(&client->dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		ret = PTR_ERR(priv->clk);
		dev_err(&client->dev, "clk request err: %d\n", ret);
		वापस ret;
	पूर्ण

	rate = clk_get_rate(priv->clk);
	क्रम (i = 0; rate && i < ARRAY_SIZE(ov6650_xclk); i++) अणु
		अगर (rate != ov6650_xclk[i].rate)
			जारी;

		xclk = &ov6650_xclk[i];
		dev_info(&client->dev, "using host default clock rate %lukHz\n",
			 rate / 1000);
		अवरोध;
	पूर्ण
	क्रम (i = 0; !xclk && i < ARRAY_SIZE(ov6650_xclk); i++) अणु
		ret = clk_set_rate(priv->clk, ov6650_xclk[i].rate);
		अगर (ret || clk_get_rate(priv->clk) != ov6650_xclk[i].rate)
			जारी;

		xclk = &ov6650_xclk[i];
		dev_info(&client->dev, "using negotiated clock rate %lukHz\n",
			 xclk->rate / 1000);
		अवरोध;
	पूर्ण
	अगर (!xclk) अणु
		dev_err(&client->dev, "unable to get supported clock rate\n");
		अगर (!ret)
			ret = -EINVAL;
		वापस ret;
	पूर्ण

	ret = ov6650_s_घातer(sd, 1);
	अगर (ret < 0)
		वापस ret;

	msleep(20);

	/*
	 * check and show product ID and manufacturer ID
	 */
	ret = ov6650_reg_पढ़ो(client, REG_PIDH, &pidh);
	अगर (!ret)
		ret = ov6650_reg_पढ़ो(client, REG_PIDL, &pidl);
	अगर (!ret)
		ret = ov6650_reg_पढ़ो(client, REG_MIDH, &midh);
	अगर (!ret)
		ret = ov6650_reg_पढ़ो(client, REG_MIDL, &midl);

	अगर (ret)
		जाओ करोne;

	अगर ((pidh != OV6650_PIDH) || (pidl != OV6650_PIDL)) अणु
		dev_err(&client->dev, "Product ID error 0x%02x:0x%02x\n",
				pidh, pidl);
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	dev_info(&client->dev,
		"ov6650 Product ID 0x%02x:0x%02x Manufacturer ID 0x%02x:0x%02x\n",
		pidh, pidl, midh, midl);

	ret = ov6650_reset(client);
	अगर (!ret)
		ret = ov6650_prog_dflt(client, xclk->clkrc);
	अगर (!ret) अणु
		काष्ठा v4l2_mbus_framefmt mf = ov6650_def_fmt;

		ret = ov6650_s_fmt(sd, &mf);
	पूर्ण
	अगर (!ret)
		ret = v4l2_ctrl_handler_setup(&priv->hdl);

करोne:
	ov6650_s_घातer(sd, 0);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov6550_ctrl_ops = अणु
	.g_अस्थिर_ctrl = ov6550_g_अस्थिर_ctrl,
	.s_ctrl = ov6550_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops ov6650_core_ops = अणु
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर		= ov6650_get_रेजिस्टर,
	.s_रेजिस्टर		= ov6650_set_रेजिस्टर,
#पूर्ण_अगर
	.s_घातer		= ov6650_s_घातer,
पूर्ण;

/* Request bus settings on camera side */
अटल पूर्णांक ov6650_get_mbus_config(काष्ठा v4l2_subdev *sd,
				  अचिन्हित पूर्णांक pad,
				  काष्ठा v4l2_mbus_config *cfg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u8 comj, comf;
	पूर्णांक ret;

	ret = ov6650_reg_पढ़ो(client, REG_COMJ, &comj);
	अगर (ret)
		वापस ret;

	ret = ov6650_reg_पढ़ो(client, REG_COMF, &comf);
	अगर (ret)
		वापस ret;

	cfg->flags = V4L2_MBUS_MASTER | V4L2_MBUS_DATA_ACTIVE_HIGH
		   | ((comj & COMJ_VSYNC_HIGH)  ? V4L2_MBUS_VSYNC_ACTIVE_HIGH
						: V4L2_MBUS_VSYNC_ACTIVE_LOW)
		   | ((comf & COMF_HREF_LOW)    ? V4L2_MBUS_HSYNC_ACTIVE_LOW
						: V4L2_MBUS_HSYNC_ACTIVE_HIGH)
		   | ((comj & COMJ_PCLK_RISING) ? V4L2_MBUS_PCLK_SAMPLE_RISING
						: V4L2_MBUS_PCLK_SAMPLE_FALLING);
	cfg->type = V4L2_MBUS_PARALLEL;

	वापस 0;
पूर्ण

/* Alter bus settings on camera side */
अटल पूर्णांक ov6650_set_mbus_config(काष्ठा v4l2_subdev *sd,
				  अचिन्हित पूर्णांक pad,
				  काष्ठा v4l2_mbus_config *cfg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret = 0;

	अगर (cfg->flags & V4L2_MBUS_PCLK_SAMPLE_RISING)
		ret = ov6650_reg_rmw(client, REG_COMJ, COMJ_PCLK_RISING, 0);
	अन्यथा अगर (cfg->flags & V4L2_MBUS_PCLK_SAMPLE_FALLING)
		ret = ov6650_reg_rmw(client, REG_COMJ, 0, COMJ_PCLK_RISING);
	अगर (ret)
		वापस ret;

	अगर (cfg->flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
		ret = ov6650_reg_rmw(client, REG_COMF, COMF_HREF_LOW, 0);
	अन्यथा अगर (cfg->flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
		ret = ov6650_reg_rmw(client, REG_COMF, 0, COMF_HREF_LOW);
	अगर (ret)
		वापस ret;

	अगर (cfg->flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH)
		ret = ov6650_reg_rmw(client, REG_COMJ, COMJ_VSYNC_HIGH, 0);
	अन्यथा अगर (cfg->flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
		ret = ov6650_reg_rmw(client, REG_COMJ, 0, COMJ_VSYNC_HIGH);
	अगर (ret)
		वापस ret;

	/*
	 * Update the configuration to report what is actually applied to
	 * the hardware.
	 */
	वापस ov6650_get_mbus_config(sd, pad, cfg);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov6650_video_ops = अणु
	.s_stream	= ov6650_s_stream,
	.g_frame_पूर्णांकerval = ov6650_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval = ov6650_s_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov6650_pad_ops = अणु
	.क्रमागत_mbus_code = ov6650_क्रमागत_mbus_code,
	.get_selection	= ov6650_get_selection,
	.set_selection	= ov6650_set_selection,
	.get_fmt	= ov6650_get_fmt,
	.set_fmt	= ov6650_set_fmt,
	.get_mbus_config = ov6650_get_mbus_config,
	.set_mbus_config = ov6650_set_mbus_config,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov6650_subdev_ops = अणु
	.core	= &ov6650_core_ops,
	.video	= &ov6650_video_ops,
	.pad	= &ov6650_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops ov6650_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = ov6650_video_probe,
पूर्ण;

/*
 * i2c_driver function
 */
अटल पूर्णांक ov6650_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *did)
अणु
	काष्ठा ov6650 *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&client->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	v4l2_i2c_subdev_init(&priv->subdev, client, &ov6650_subdev_ops);
	v4l2_ctrl_handler_init(&priv->hdl, 13);
	v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
	priv->स्वतःgain = v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	priv->gain = v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_GAIN, 0, 0x3f, 1, DEF_GAIN);
	priv->स्वतःwb = v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_AUTO_WHITE_BALANCE, 0, 1, 1, 1);
	priv->blue = v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_BLUE_BALANCE, 0, 0xff, 1, DEF_BLUE);
	priv->red = v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_RED_BALANCE, 0, 0xff, 1, DEF_RED);
	v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_SATURATION, 0, 0xf, 1, 0x8);
	v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_HUE, 0, HUE_MASK, 1, DEF_HUE);
	v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 0xff, 1, 0x80);
	priv->स्वतःexposure = v4l2_ctrl_new_std_menu(&priv->hdl,
			&ov6550_ctrl_ops, V4L2_CID_EXPOSURE_AUTO,
			V4L2_EXPOSURE_MANUAL, 0, V4L2_EXPOSURE_AUTO);
	priv->exposure = v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 0xff, 1, DEF_AECH);
	v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_GAMMA, 0, 0xff, 1, 0x12);

	priv->subdev.ctrl_handler = &priv->hdl;
	अगर (priv->hdl.error) अणु
		ret = priv->hdl.error;
		जाओ ectlhdlमुक्त;
	पूर्ण

	v4l2_ctrl_स्वतः_cluster(2, &priv->स्वतःgain, 0, true);
	v4l2_ctrl_स्वतः_cluster(3, &priv->स्वतःwb, 0, true);
	v4l2_ctrl_स्वतः_cluster(2, &priv->स्वतःexposure,
				V4L2_EXPOSURE_MANUAL, true);

	priv->rect.left	  = DEF_HSTRT << 1;
	priv->rect.top	  = DEF_VSTRT << 1;
	priv->rect.width  = W_CIF;
	priv->rect.height = H_CIF;

	/* Hardware शेष frame पूर्णांकerval */
	priv->tpf.numerator   = GET_CLKRC_DIV(DEF_CLKRC);
	priv->tpf.denominator = FRAME_RATE_MAX;

	priv->subdev.पूर्णांकernal_ops = &ov6650_पूर्णांकernal_ops;

	ret = v4l2_async_रेजिस्टर_subdev(&priv->subdev);
	अगर (!ret)
		वापस 0;
ectlhdlमुक्त:
	v4l2_ctrl_handler_मुक्त(&priv->hdl);

	वापस ret;
पूर्ण

अटल पूर्णांक ov6650_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ov6650 *priv = to_ov6650(client);

	v4l2_async_unरेजिस्टर_subdev(&priv->subdev);
	v4l2_ctrl_handler_मुक्त(&priv->hdl);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ov6650_id[] = अणु
	अणु "ov6650", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ov6650_id);

अटल काष्ठा i2c_driver ov6650_i2c_driver = अणु
	.driver = अणु
		.name = "ov6650",
	पूर्ण,
	.probe    = ov6650_probe,
	.हटाओ   = ov6650_हटाओ,
	.id_table = ov6650_id,
पूर्ण;

module_i2c_driver(ov6650_i2c_driver);

MODULE_DESCRIPTION("V4L2 subdevice driver for OmniVision OV6650 camera sensor");
MODULE_AUTHOR("Janusz Krzysztofik <jmkrzyszt@gmail.com");
MODULE_LICENSE("GPL v2");
