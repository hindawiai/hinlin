<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OmniVision OV96xx Camera Driver
 *
 * Copyright (C) 2009 Marek Vasut <marek.vasut@gmail.com>
 *
 * Based on ov772x camera driver:
 *
 * Copyright (C) 2008 Renesas Solutions Corp.
 * Kuninori Morimoto <morimoto.kuninori@renesas.com>
 *
 * Based on ov7670 and soc_camera_platक्रमm driver,
 * transition from soc_camera to pxa_camera based on mt9m111
 *
 * Copyright 2006-7 Jonathan Corbet <corbet@lwn.net>
 * Copyright (C) 2008 Magnus Damm
 * Copyright (C) 2008, Guennadi Liakhovetski <kernel@pengutronix.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-event.h>

#समावेश <linux/gpio/consumer.h>

#समावेश "ov9640.h"

#घोषणा to_ov9640_sensor(sd)	container_of(sd, काष्ठा ov9640_priv, subdev)

/* शेष रेजिस्टर setup */
अटल स्थिर काष्ठा ov9640_reg ov9640_regs_dflt[] = अणु
	अणु OV9640_COM5,	OV9640_COM5_SYSCLK | OV9640_COM5_LONGEXP पूर्ण,
	अणु OV9640_COM6,	OV9640_COM6_OPT_BLC | OV9640_COM6_ADBLC_BIAS |
			OV9640_COM6_FMT_RST | OV9640_COM6_ADBLC_OPTEN पूर्ण,
	अणु OV9640_PSHFT,	OV9640_PSHFT_VAL(0x01) पूर्ण,
	अणु OV9640_ACOM,	OV9640_ACOM_2X_ANALOG | OV9640_ACOM_RSVD पूर्ण,
	अणु OV9640_TSLB,	OV9640_TSLB_YUYV_UYVY पूर्ण,
	अणु OV9640_COM16,	OV9640_COM16_RB_AVG पूर्ण,

	/* Gamma curve P */
	अणु 0x6c, 0x40 पूर्ण,	अणु 0x6d, 0x30 पूर्ण,	अणु 0x6e, 0x4b पूर्ण,	अणु 0x6f, 0x60 पूर्ण,
	अणु 0x70, 0x70 पूर्ण,	अणु 0x71, 0x70 पूर्ण,	अणु 0x72, 0x70 पूर्ण,	अणु 0x73, 0x70 पूर्ण,
	अणु 0x74, 0x60 पूर्ण,	अणु 0x75, 0x60 पूर्ण,	अणु 0x76, 0x50 पूर्ण,	अणु 0x77, 0x48 पूर्ण,
	अणु 0x78, 0x3a पूर्ण,	अणु 0x79, 0x2e पूर्ण,	अणु 0x7a, 0x28 पूर्ण,	अणु 0x7b, 0x22 पूर्ण,

	/* Gamma curve T */
	अणु 0x7c, 0x04 पूर्ण,	अणु 0x7d, 0x07 पूर्ण,	अणु 0x7e, 0x10 पूर्ण,	अणु 0x7f, 0x28 पूर्ण,
	अणु 0x80, 0x36 पूर्ण,	अणु 0x81, 0x44 पूर्ण,	अणु 0x82, 0x52 पूर्ण,	अणु 0x83, 0x60 पूर्ण,
	अणु 0x84, 0x6c पूर्ण,	अणु 0x85, 0x78 पूर्ण,	अणु 0x86, 0x8c पूर्ण,	अणु 0x87, 0x9e पूर्ण,
	अणु 0x88, 0xbb पूर्ण,	अणु 0x89, 0xd2 पूर्ण,	अणु 0x8a, 0xe6 पूर्ण,
पूर्ण;

/* Configurations
 * NOTE: क्रम YUV, alter the following रेजिस्टरs:
 *		COM12 |= OV9640_COM12_YUV_AVG
 *
 *	 क्रम RGB, alter the following रेजिस्टरs:
 *		COM7  |= OV9640_COM7_RGB
 *		COM13 |= OV9640_COM13_RGB_AVG
 *		COM15 |= proper RGB color encoding mode
 */
अटल स्थिर काष्ठा ov9640_reg ov9640_regs_qqcअगर[] = अणु
	अणु OV9640_CLKRC,	OV9640_CLKRC_DPLL_EN | OV9640_CLKRC_DIV(0x0f) पूर्ण,
	अणु OV9640_COM1,	OV9640_COM1_QQFMT | OV9640_COM1_HREF_2SKIP पूर्ण,
	अणु OV9640_COM4,	OV9640_COM4_QQ_VP | OV9640_COM4_RSVD पूर्ण,
	अणु OV9640_COM7,	OV9640_COM7_QCIF पूर्ण,
	अणु OV9640_COM12,	OV9640_COM12_RSVD पूर्ण,
	अणु OV9640_COM13,	OV9640_COM13_GAMMA_RAW | OV9640_COM13_MATRIX_EN पूर्ण,
	अणु OV9640_COM15,	OV9640_COM15_OR_10F0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov9640_reg ov9640_regs_qqvga[] = अणु
	अणु OV9640_CLKRC,	OV9640_CLKRC_DPLL_EN | OV9640_CLKRC_DIV(0x07) पूर्ण,
	अणु OV9640_COM1,	OV9640_COM1_QQFMT | OV9640_COM1_HREF_2SKIP पूर्ण,
	अणु OV9640_COM4,	OV9640_COM4_QQ_VP | OV9640_COM4_RSVD पूर्ण,
	अणु OV9640_COM7,	OV9640_COM7_QVGA पूर्ण,
	अणु OV9640_COM12,	OV9640_COM12_RSVD पूर्ण,
	अणु OV9640_COM13,	OV9640_COM13_GAMMA_RAW | OV9640_COM13_MATRIX_EN पूर्ण,
	अणु OV9640_COM15,	OV9640_COM15_OR_10F0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov9640_reg ov9640_regs_qcअगर[] = अणु
	अणु OV9640_CLKRC,	OV9640_CLKRC_DPLL_EN | OV9640_CLKRC_DIV(0x07) पूर्ण,
	अणु OV9640_COM4,	OV9640_COM4_QQ_VP | OV9640_COM4_RSVD पूर्ण,
	अणु OV9640_COM7,	OV9640_COM7_QCIF पूर्ण,
	अणु OV9640_COM12,	OV9640_COM12_RSVD पूर्ण,
	अणु OV9640_COM13,	OV9640_COM13_GAMMA_RAW | OV9640_COM13_MATRIX_EN पूर्ण,
	अणु OV9640_COM15,	OV9640_COM15_OR_10F0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov9640_reg ov9640_regs_qvga[] = अणु
	अणु OV9640_CLKRC,	OV9640_CLKRC_DPLL_EN | OV9640_CLKRC_DIV(0x03) पूर्ण,
	अणु OV9640_COM4,	OV9640_COM4_QQ_VP | OV9640_COM4_RSVD पूर्ण,
	अणु OV9640_COM7,	OV9640_COM7_QVGA पूर्ण,
	अणु OV9640_COM12,	OV9640_COM12_RSVD पूर्ण,
	अणु OV9640_COM13,	OV9640_COM13_GAMMA_RAW | OV9640_COM13_MATRIX_EN पूर्ण,
	अणु OV9640_COM15,	OV9640_COM15_OR_10F0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov9640_reg ov9640_regs_cअगर[] = अणु
	अणु OV9640_CLKRC,	OV9640_CLKRC_DPLL_EN | OV9640_CLKRC_DIV(0x03) पूर्ण,
	अणु OV9640_COM3,	OV9640_COM3_VP पूर्ण,
	अणु OV9640_COM7,	OV9640_COM7_CIF पूर्ण,
	अणु OV9640_COM12,	OV9640_COM12_RSVD पूर्ण,
	अणु OV9640_COM13,	OV9640_COM13_GAMMA_RAW | OV9640_COM13_MATRIX_EN पूर्ण,
	अणु OV9640_COM15,	OV9640_COM15_OR_10F0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov9640_reg ov9640_regs_vga[] = अणु
	अणु OV9640_CLKRC,	OV9640_CLKRC_DPLL_EN | OV9640_CLKRC_DIV(0x01) पूर्ण,
	अणु OV9640_COM3,	OV9640_COM3_VP पूर्ण,
	अणु OV9640_COM7,	OV9640_COM7_VGA पूर्ण,
	अणु OV9640_COM12,	OV9640_COM12_RSVD पूर्ण,
	अणु OV9640_COM13,	OV9640_COM13_GAMMA_RAW | OV9640_COM13_MATRIX_EN पूर्ण,
	अणु OV9640_COM15,	OV9640_COM15_OR_10F0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov9640_reg ov9640_regs_sxga[] = अणु
	अणु OV9640_CLKRC,	OV9640_CLKRC_DPLL_EN | OV9640_CLKRC_DIV(0x01) पूर्ण,
	अणु OV9640_COM3,	OV9640_COM3_VP पूर्ण,
	अणु OV9640_COM7,	0 पूर्ण,
	अणु OV9640_COM12,	OV9640_COM12_RSVD पूर्ण,
	अणु OV9640_COM13,	OV9640_COM13_GAMMA_RAW | OV9640_COM13_MATRIX_EN पूर्ण,
	अणु OV9640_COM15,	OV9640_COM15_OR_10F0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov9640_reg ov9640_regs_yuv[] = अणु
	अणु OV9640_MTX1,	0x58 पूर्ण,
	अणु OV9640_MTX2,	0x48 पूर्ण,
	अणु OV9640_MTX3,	0x10 पूर्ण,
	अणु OV9640_MTX4,	0x28 पूर्ण,
	अणु OV9640_MTX5,	0x48 पूर्ण,
	अणु OV9640_MTX6,	0x70 पूर्ण,
	अणु OV9640_MTX7,	0x40 पूर्ण,
	अणु OV9640_MTX8,	0x40 पूर्ण,
	अणु OV9640_MTX9,	0x40 पूर्ण,
	अणु OV9640_MTXS,	0x0f पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ov9640_reg ov9640_regs_rgb[] = अणु
	अणु OV9640_MTX1,	0x71 पूर्ण,
	अणु OV9640_MTX2,	0x3e पूर्ण,
	अणु OV9640_MTX3,	0x0c पूर्ण,
	अणु OV9640_MTX4,	0x33 पूर्ण,
	अणु OV9640_MTX5,	0x72 पूर्ण,
	अणु OV9640_MTX6,	0x00 पूर्ण,
	अणु OV9640_MTX7,	0x2b पूर्ण,
	अणु OV9640_MTX8,	0x66 पूर्ण,
	अणु OV9640_MTX9,	0xd2 पूर्ण,
	अणु OV9640_MTXS,	0x65 पूर्ण,
पूर्ण;

अटल स्थिर u32 ov9640_codes[] = अणु
	MEDIA_BUS_FMT_UYVY8_2X8,
	MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE,
	MEDIA_BUS_FMT_RGB565_2X8_LE,
पूर्ण;

/* पढ़ो a रेजिस्टर */
अटल पूर्णांक ov9640_reg_पढ़ो(काष्ठा i2c_client *client, u8 reg, u8 *val)
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
अटल पूर्णांक ov9640_reg_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 val)
अणु
	पूर्णांक ret;
	u8 _val;
	अचिन्हित अक्षर data[2] = अणु reg, val पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr	= client->addr,
		.flags	= 0,
		.len	= 2,
		.buf	= data,
	पूर्ण;

	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed writing register 0x%02x!\n", reg);
		वापस ret;
	पूर्ण

	/* we have to पढ़ो the रेजिस्टर back ... no idea why, maybe HW bug */
	ret = ov9640_reg_पढ़ो(client, reg, &_val);
	अगर (ret)
		dev_err(&client->dev,
			"Failed reading back register 0x%02x!\n", reg);

	वापस 0;
पूर्ण


/* Read a रेजिस्टर, alter its bits, ग_लिखो it back */
अटल पूर्णांक ov9640_reg_rmw(काष्ठा i2c_client *client, u8 reg, u8 set, u8 unset)
अणु
	u8 val;
	पूर्णांक ret;

	ret = ov9640_reg_पढ़ो(client, reg, &val);
	अगर (ret) अणु
		dev_err(&client->dev,
			"[Read]-Modify-Write of register %02x failed!\n", reg);
		वापस ret;
	पूर्ण

	val |= set;
	val &= ~unset;

	ret = ov9640_reg_ग_लिखो(client, reg, val);
	अगर (ret)
		dev_err(&client->dev,
			"Read-Modify-[Write] of register %02x failed!\n", reg);

	वापस ret;
पूर्ण

/* Soft reset the camera. This has nothing to करो with the RESET pin! */
अटल पूर्णांक ov9640_reset(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;

	ret = ov9640_reg_ग_लिखो(client, OV9640_COM7, OV9640_COM7_SCCB_RESET);
	अगर (ret)
		dev_err(&client->dev,
			"An error occurred while entering soft reset!\n");

	वापस ret;
पूर्ण

/* Start/Stop streaming from the device */
अटल पूर्णांक ov9640_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	वापस 0;
पूर्ण

/* Set status of additional camera capabilities */
अटल पूर्णांक ov9640_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा ov9640_priv *priv = container_of(ctrl->handler,
						काष्ठा ov9640_priv, hdl);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&priv->subdev);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_VFLIP:
		अगर (ctrl->val)
			वापस ov9640_reg_rmw(client, OV9640_MVFP,
					      OV9640_MVFP_V, 0);
		वापस ov9640_reg_rmw(client, OV9640_MVFP, 0, OV9640_MVFP_V);
	हाल V4L2_CID_HFLIP:
		अगर (ctrl->val)
			वापस ov9640_reg_rmw(client, OV9640_MVFP,
					      OV9640_MVFP_H, 0);
		वापस ov9640_reg_rmw(client, OV9640_MVFP, 0, OV9640_MVFP_H);
	पूर्ण

	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक ov9640_get_रेजिस्टर(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;
	u8 val;

	अगर (reg->reg & ~0xff)
		वापस -EINVAL;

	reg->size = 1;

	ret = ov9640_reg_पढ़ो(client, reg->reg, &val);
	अगर (ret)
		वापस ret;

	reg->val = (__u64)val;

	वापस 0;
पूर्ण

अटल पूर्णांक ov9640_set_रेजिस्टर(काष्ठा v4l2_subdev *sd,
				स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	अगर (reg->reg & ~0xff || reg->val & ~0xff)
		वापस -EINVAL;

	वापस ov9640_reg_ग_लिखो(client, reg->reg, reg->val);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ov9640_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा ov9640_priv *priv = to_ov9640_sensor(sd);
	पूर्णांक ret = 0;

	अगर (on) अणु
		gpiod_set_value(priv->gpio_घातer, 1);
		usleep_range(1000, 2000);
		ret = clk_prepare_enable(priv->clk);
		usleep_range(1000, 2000);
		gpiod_set_value(priv->gpio_reset, 0);
	पूर्ण अन्यथा अणु
		gpiod_set_value(priv->gpio_reset, 1);
		usleep_range(1000, 2000);
		clk_disable_unprepare(priv->clk);
		usleep_range(1000, 2000);
		gpiod_set_value(priv->gpio_घातer, 0);
	पूर्ण

	वापस ret;
पूर्ण

/* select nearest higher resolution क्रम capture */
अटल व्योम ov9640_res_roundup(u32 *width, u32 *height)
अणु
	अचिन्हित पूर्णांक i;
	क्रमागत अणु QQCIF, QQVGA, QCIF, QVGA, CIF, VGA, SXGA पूर्ण;
	अटल स्थिर u32 res_x[] = अणु 88, 160, 176, 320, 352, 640, 1280 पूर्ण;
	अटल स्थिर u32 res_y[] = अणु 72, 120, 144, 240, 288, 480, 960 पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(res_x); i++) अणु
		अगर (res_x[i] >= *width && res_y[i] >= *height) अणु
			*width = res_x[i];
			*height = res_y[i];
			वापस;
		पूर्ण
	पूर्ण

	*width = res_x[SXGA];
	*height = res_y[SXGA];
पूर्ण

/* Prepare necessary रेजिस्टर changes depending on color encoding */
अटल व्योम ov9640_alter_regs(u32 code,
			      काष्ठा ov9640_reg_alt *alt)
अणु
	चयन (code) अणु
	शेष:
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
		alt->com12	= OV9640_COM12_YUV_AVG;
		alt->com13	= OV9640_COM13_Y_DELAY_EN |
					OV9640_COM13_YUV_DLY(0x01);
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE:
		alt->com7	= OV9640_COM7_RGB;
		alt->com13	= OV9640_COM13_RGB_AVG;
		alt->com15	= OV9640_COM15_RGB_555;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB565_2X8_LE:
		alt->com7	= OV9640_COM7_RGB;
		alt->com13	= OV9640_COM13_RGB_AVG;
		alt->com15	= OV9640_COM15_RGB_565;
		अवरोध;
	पूर्ण
पूर्ण

/* Setup रेजिस्टरs according to resolution and color encoding */
अटल पूर्णांक ov9640_ग_लिखो_regs(काष्ठा i2c_client *client, u32 width,
		u32 code, काष्ठा ov9640_reg_alt *alts)
अणु
	स्थिर काष्ठा ov9640_reg	*ov9640_regs, *matrix_regs;
	अचिन्हित पूर्णांक		ov9640_regs_len, matrix_regs_len;
	अचिन्हित पूर्णांक		i;
	पूर्णांक			ret;
	u8			val;

	/* select रेजिस्टर configuration क्रम given resolution */
	चयन (width) अणु
	हाल W_QQCIF:
		ov9640_regs	= ov9640_regs_qqcअगर;
		ov9640_regs_len	= ARRAY_SIZE(ov9640_regs_qqcअगर);
		अवरोध;
	हाल W_QQVGA:
		ov9640_regs	= ov9640_regs_qqvga;
		ov9640_regs_len	= ARRAY_SIZE(ov9640_regs_qqvga);
		अवरोध;
	हाल W_QCIF:
		ov9640_regs	= ov9640_regs_qcअगर;
		ov9640_regs_len	= ARRAY_SIZE(ov9640_regs_qcअगर);
		अवरोध;
	हाल W_QVGA:
		ov9640_regs	= ov9640_regs_qvga;
		ov9640_regs_len	= ARRAY_SIZE(ov9640_regs_qvga);
		अवरोध;
	हाल W_CIF:
		ov9640_regs	= ov9640_regs_cअगर;
		ov9640_regs_len	= ARRAY_SIZE(ov9640_regs_cअगर);
		अवरोध;
	हाल W_VGA:
		ov9640_regs	= ov9640_regs_vga;
		ov9640_regs_len	= ARRAY_SIZE(ov9640_regs_vga);
		अवरोध;
	हाल W_SXGA:
		ov9640_regs	= ov9640_regs_sxga;
		ov9640_regs_len	= ARRAY_SIZE(ov9640_regs_sxga);
		अवरोध;
	शेष:
		dev_err(&client->dev, "Failed to select resolution!\n");
		वापस -EINVAL;
	पूर्ण

	/* select color matrix configuration क्रम given color encoding */
	अगर (code == MEDIA_BUS_FMT_UYVY8_2X8) अणु
		matrix_regs	= ov9640_regs_yuv;
		matrix_regs_len	= ARRAY_SIZE(ov9640_regs_yuv);
	पूर्ण अन्यथा अणु
		matrix_regs	= ov9640_regs_rgb;
		matrix_regs_len	= ARRAY_SIZE(ov9640_regs_rgb);
	पूर्ण

	/* ग_लिखो रेजिस्टर settings पूर्णांकo the module */
	क्रम (i = 0; i < ov9640_regs_len; i++) अणु
		val = ov9640_regs[i].val;

		चयन (ov9640_regs[i].reg) अणु
		हाल OV9640_COM7:
			val |= alts->com7;
			अवरोध;
		हाल OV9640_COM12:
			val |= alts->com12;
			अवरोध;
		हाल OV9640_COM13:
			val |= alts->com13;
			अवरोध;
		हाल OV9640_COM15:
			val |= alts->com15;
			अवरोध;
		पूर्ण

		ret = ov9640_reg_ग_लिखो(client, ov9640_regs[i].reg, val);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* ग_लिखो color matrix configuration पूर्णांकo the module */
	क्रम (i = 0; i < matrix_regs_len; i++) अणु
		ret = ov9640_reg_ग_लिखो(client, matrix_regs[i].reg,
				       matrix_regs[i].val);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* program शेष रेजिस्टर values */
अटल पूर्णांक ov9640_prog_dflt(काष्ठा i2c_client *client)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(ov9640_regs_dflt); i++) अणु
		ret = ov9640_reg_ग_लिखो(client, ov9640_regs_dflt[i].reg,
				       ov9640_regs_dflt[i].val);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* रुको क्रम the changes to actually happen, 140ms are not enough yet */
	msleep(150);

	वापस 0;
पूर्ण

/* set the क्रमmat we will capture in */
अटल पूर्णांक ov9640_s_fmt(काष्ठा v4l2_subdev *sd,
			काष्ठा v4l2_mbus_framefmt *mf)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा ov9640_reg_alt alts = अणु0पूर्ण;
	पूर्णांक ret;

	ov9640_alter_regs(mf->code, &alts);

	ov9640_reset(client);

	ret = ov9640_prog_dflt(client);
	अगर (ret)
		वापस ret;

	वापस ov9640_ग_लिखो_regs(client, mf->width, mf->code, &alts);
पूर्ण

अटल पूर्णांक ov9640_set_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	ov9640_res_roundup(&mf->width, &mf->height);

	mf->field = V4L2_FIELD_NONE;

	चयन (mf->code) अणु
	हाल MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE:
	हाल MEDIA_BUS_FMT_RGB565_2X8_LE:
		mf->colorspace = V4L2_COLORSPACE_SRGB;
		अवरोध;
	शेष:
		mf->code = MEDIA_BUS_FMT_UYVY8_2X8;
		fallthrough;
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
		mf->colorspace = V4L2_COLORSPACE_JPEG;
		अवरोध;
	पूर्ण

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस ov9640_s_fmt(sd, mf);

	cfg->try_fmt = *mf;

	वापस 0;
पूर्ण

अटल पूर्णांक ov9640_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index >= ARRAY_SIZE(ov9640_codes))
		वापस -EINVAL;

	code->code = ov9640_codes[code->index];

	वापस 0;
पूर्ण

अटल पूर्णांक ov9640_get_selection(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_selection *sel)
अणु
	अगर (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस -EINVAL;

	sel->r.left = 0;
	sel->r.top = 0;
	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
	हाल V4L2_SEL_TGT_CROP:
		sel->r.width = W_SXGA;
		sel->r.height = H_SXGA;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ov9640_video_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov9640_priv *priv = to_ov9640_sensor(sd);
	u8		pid, ver, midh, midl;
	स्थिर अक्षर	*devname;
	पूर्णांक		ret;

	ret = ov9640_s_घातer(&priv->subdev, 1);
	अगर (ret < 0)
		वापस ret;

	/*
	 * check and show product ID and manufacturer ID
	 */

	ret = ov9640_reg_पढ़ो(client, OV9640_PID, &pid);
	अगर (!ret)
		ret = ov9640_reg_पढ़ो(client, OV9640_VER, &ver);
	अगर (!ret)
		ret = ov9640_reg_पढ़ो(client, OV9640_MIDH, &midh);
	अगर (!ret)
		ret = ov9640_reg_पढ़ो(client, OV9640_MIDL, &midl);
	अगर (ret)
		जाओ करोne;

	चयन (VERSION(pid, ver)) अणु
	हाल OV9640_V2:
		devname		= "ov9640";
		priv->revision	= 2;
		अवरोध;
	हाल OV9640_V3:
		devname		= "ov9640";
		priv->revision	= 3;
		अवरोध;
	शेष:
		dev_err(&client->dev, "Product ID error %x:%x\n", pid, ver);
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	dev_info(&client->dev, "%s Product ID %0x:%0x Manufacturer ID %x:%x\n",
		 devname, pid, ver, midh, midl);

	ret = v4l2_ctrl_handler_setup(&priv->hdl);

करोne:
	ov9640_s_घातer(&priv->subdev, 0);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops ov9640_ctrl_ops = अणु
	.s_ctrl = ov9640_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops ov9640_core_ops = अणु
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर		= ov9640_get_रेजिस्टर,
	.s_रेजिस्टर		= ov9640_set_रेजिस्टर,
#पूर्ण_अगर
	.s_घातer		= ov9640_s_घातer,
पूर्ण;

/* Request bus settings on camera side */
अटल पूर्णांक ov9640_get_mbus_config(काष्ठा v4l2_subdev *sd,
				  अचिन्हित पूर्णांक pad,
				  काष्ठा v4l2_mbus_config *cfg)
अणु
	cfg->flags = V4L2_MBUS_PCLK_SAMPLE_RISING | V4L2_MBUS_MASTER |
		V4L2_MBUS_VSYNC_ACTIVE_HIGH | V4L2_MBUS_HSYNC_ACTIVE_HIGH |
		V4L2_MBUS_DATA_ACTIVE_HIGH;
	cfg->type = V4L2_MBUS_PARALLEL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops ov9640_video_ops = अणु
	.s_stream	= ov9640_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops ov9640_pad_ops = अणु
	.क्रमागत_mbus_code = ov9640_क्रमागत_mbus_code,
	.get_selection	= ov9640_get_selection,
	.set_fmt	= ov9640_set_fmt,
	.get_mbus_config = ov9640_get_mbus_config,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops ov9640_subdev_ops = अणु
	.core	= &ov9640_core_ops,
	.video	= &ov9640_video_ops,
	.pad	= &ov9640_pad_ops,
पूर्ण;

/*
 * i2c_driver function
 */
अटल पूर्णांक ov9640_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *did)
अणु
	काष्ठा ov9640_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&client->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->gpio_घातer = devm_gpiod_get(&client->dev, "Camera power",
					  GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->gpio_घातer)) अणु
		ret = PTR_ERR(priv->gpio_घातer);
		वापस ret;
	पूर्ण

	priv->gpio_reset = devm_gpiod_get(&client->dev, "Camera reset",
					  GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->gpio_reset)) अणु
		ret = PTR_ERR(priv->gpio_reset);
		वापस ret;
	पूर्ण

	v4l2_i2c_subdev_init(&priv->subdev, client, &ov9640_subdev_ops);

	v4l2_ctrl_handler_init(&priv->hdl, 2);
	v4l2_ctrl_new_std(&priv->hdl, &ov9640_ctrl_ops,
			  V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&priv->hdl, &ov9640_ctrl_ops,
			  V4L2_CID_HFLIP, 0, 1, 1, 0);

	अगर (priv->hdl.error) अणु
		ret = priv->hdl.error;
		जाओ ectrlinit;
	पूर्ण

	priv->subdev.ctrl_handler = &priv->hdl;

	priv->clk = devm_clk_get(&client->dev, "mclk");
	अगर (IS_ERR(priv->clk)) अणु
		ret = PTR_ERR(priv->clk);
		जाओ ectrlinit;
	पूर्ण

	ret = ov9640_video_probe(client);
	अगर (ret)
		जाओ ectrlinit;

	priv->subdev.dev = &client->dev;
	ret = v4l2_async_रेजिस्टर_subdev(&priv->subdev);
	अगर (ret)
		जाओ ectrlinit;

	वापस 0;

ectrlinit:
	v4l2_ctrl_handler_मुक्त(&priv->hdl);

	वापस ret;
पूर्ण

अटल पूर्णांक ov9640_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा ov9640_priv *priv = to_ov9640_sensor(sd);

	v4l2_async_unरेजिस्टर_subdev(&priv->subdev);
	v4l2_ctrl_handler_मुक्त(&priv->hdl);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ov9640_id[] = अणु
	अणु "ov9640", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ov9640_id);

अटल काष्ठा i2c_driver ov9640_i2c_driver = अणु
	.driver = अणु
		.name = "ov9640",
	पूर्ण,
	.probe    = ov9640_probe,
	.हटाओ   = ov9640_हटाओ,
	.id_table = ov9640_id,
पूर्ण;

module_i2c_driver(ov9640_i2c_driver);

MODULE_DESCRIPTION("OmniVision OV96xx CMOS Image Sensor driver");
MODULE_AUTHOR("Marek Vasut <marek.vasut@gmail.com>");
MODULE_LICENSE("GPL v2");
