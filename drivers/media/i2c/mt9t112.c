<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mt9t112 Camera Driver
 *
 * Copyright (C) 2018 Jacopo Mondi <jacopo+renesas@jmondi.org>
 *
 * Copyright (C) 2009 Renesas Solutions Corp.
 * Kuninori Morimoto <morimoto.kuninori@renesas.com>
 *
 * Based on ov772x driver, mt9m111 driver,
 *
 * Copyright (C) 2008 Kuninori Morimoto <morimoto.kuninori@renesas.com>
 * Copyright (C) 2008, Robert Jarzmik <robert.jarzmik@मुक्त.fr>
 * Copyright 2006-7 Jonathan Corbet <corbet@lwn.net>
 * Copyright (C) 2008 Magnus Damm
 * Copyright (C) 2008, Guennadi Liakhovetski <kernel@pengutronix.de>
 *
 * TODO: This driver lacks support क्रम frame rate control due to missing
 *	 रेजिस्टर level करोcumentation and suitable hardware क्रम testing.
 *	 v4l-utils compliance tools will report errors.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <linux/videodev2.h>

#समावेश <media/i2c/mt9t112.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-image-sizes.h>
#समावेश <media/v4l2-subdev.h>

/* you can check PLL/घड़ी info */
/* #घोषणा EXT_CLOCK 24000000 */

/************************************************************************
 *			macro
 ***********************************************************************/
/*
 * frame size
 */
#घोषणा MAX_WIDTH   2048
#घोषणा MAX_HEIGHT  1536

/*
 * macro of पढ़ो/ग_लिखो
 */
#घोषणा ECHECKER(ret, x)		\
	करो अणु				\
		(ret) = (x);		\
		अगर ((ret) < 0)		\
			वापस (ret);	\
	पूर्ण जबतक (0)

#घोषणा mt9t112_reg_ग_लिखो(ret, client, a, b) \
	ECHECKER(ret, __mt9t112_reg_ग_लिखो(client, a, b))
#घोषणा mt9t112_mcu_ग_लिखो(ret, client, a, b) \
	ECHECKER(ret, __mt9t112_mcu_ग_लिखो(client, a, b))

#घोषणा mt9t112_reg_mask_set(ret, client, a, b, c) \
	ECHECKER(ret, __mt9t112_reg_mask_set(client, a, b, c))
#घोषणा mt9t112_mcu_mask_set(ret, client, a, b, c) \
	ECHECKER(ret, __mt9t112_mcu_mask_set(client, a, b, c))

#घोषणा mt9t112_reg_पढ़ो(ret, client, a) \
	ECHECKER(ret, __mt9t112_reg_पढ़ो(client, a))

/*
 * Logical address
 */
#घोषणा _VAR(id, offset, base)	(base | (id & 0x1f) << 10 | (offset & 0x3ff))
#घोषणा VAR(id, offset)  _VAR(id, offset, 0x0000)
#घोषणा VAR8(id, offset) _VAR(id, offset, 0x8000)

/************************************************************************
 *			काष्ठा
 ***********************************************************************/
काष्ठा mt9t112_क्रमmat अणु
	u32 code;
	क्रमागत v4l2_colorspace colorspace;
	u16 fmt;
	u16 order;
पूर्ण;

काष्ठा mt9t112_priv अणु
	काष्ठा v4l2_subdev		 subdev;
	काष्ठा mt9t112_platक्रमm_data	*info;
	काष्ठा i2c_client		*client;
	काष्ठा v4l2_rect		 frame;
	काष्ठा clk			*clk;
	काष्ठा gpio_desc		*standby_gpio;
	स्थिर काष्ठा mt9t112_क्रमmat	*क्रमmat;
	पूर्णांक				 num_क्रमmats;
	bool				 init_करोne;
पूर्ण;

/************************************************************************
 *			supported क्रमmat
 ***********************************************************************/

अटल स्थिर काष्ठा mt9t112_क्रमmat mt9t112_cfmts[] = अणु
	अणु
		.code		= MEDIA_BUS_FMT_UYVY8_2X8,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.fmt		= 1,
		.order		= 0,
	पूर्ण, अणु
		.code		= MEDIA_BUS_FMT_VYUY8_2X8,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.fmt		= 1,
		.order		= 1,
	पूर्ण, अणु
		.code		= MEDIA_BUS_FMT_YUYV8_2X8,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.fmt		= 1,
		.order		= 2,
	पूर्ण, अणु
		.code		= MEDIA_BUS_FMT_YVYU8_2X8,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.fmt		= 1,
		.order		= 3,
	पूर्ण, अणु
		.code		= MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.fmt		= 8,
		.order		= 2,
	पूर्ण, अणु
		.code		= MEDIA_BUS_FMT_RGB565_2X8_LE,
		.colorspace	= V4L2_COLORSPACE_SRGB,
		.fmt		= 4,
		.order		= 2,
	पूर्ण,
पूर्ण;

/************************************************************************
 *			general function
 ***********************************************************************/
अटल काष्ठा mt9t112_priv *to_mt9t112(स्थिर काष्ठा i2c_client *client)
अणु
	वापस container_of(i2c_get_clientdata(client),
			    काष्ठा mt9t112_priv,
			    subdev);
पूर्ण

अटल पूर्णांक __mt9t112_reg_पढ़ो(स्थिर काष्ठा i2c_client *client, u16 command)
अणु
	काष्ठा i2c_msg msg[2];
	u8 buf[2];
	पूर्णांक ret;

	command = swab16(command);

	msg[0].addr  = client->addr;
	msg[0].flags = 0;
	msg[0].len   = 2;
	msg[0].buf   = (u8 *)&command;

	msg[1].addr  = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len   = 2;
	msg[1].buf   = buf;

	/*
	 * If वापस value of this function is < 0, it means error, अन्यथा,
	 * below 16bit is valid data.
	 */
	ret = i2c_transfer(client->adapter, msg, 2);
	अगर (ret < 0)
		वापस ret;

	स_नकल(&ret, buf, 2);

	वापस swab16(ret);
पूर्ण

अटल पूर्णांक __mt9t112_reg_ग_लिखो(स्थिर काष्ठा i2c_client *client,
			       u16 command, u16 data)
अणु
	काष्ठा i2c_msg msg;
	u8 buf[4];
	पूर्णांक ret;

	command = swab16(command);
	data = swab16(data);

	स_नकल(buf + 0, &command, 2);
	स_नकल(buf + 2, &data,    2);

	msg.addr  = client->addr;
	msg.flags = 0;
	msg.len   = 4;
	msg.buf   = buf;

	/*
	 * i2c_transfer वापस message length, but this function should
	 * वापस 0 अगर correct हाल.
	 */
	ret = i2c_transfer(client->adapter, &msg, 1);

	वापस ret >= 0 ? 0 : ret;
पूर्ण

अटल पूर्णांक __mt9t112_reg_mask_set(स्थिर काष्ठा i2c_client *client,
				  u16  command, u16  mask, u16  set)
अणु
	पूर्णांक val = __mt9t112_reg_पढ़ो(client, command);

	अगर (val < 0)
		वापस val;

	val &= ~mask;
	val |= set & mask;

	वापस __mt9t112_reg_ग_लिखो(client, command, val);
पूर्ण

/* mcu access */
अटल पूर्णांक __mt9t112_mcu_पढ़ो(स्थिर काष्ठा i2c_client *client, u16 command)
अणु
	पूर्णांक ret;

	ret = __mt9t112_reg_ग_लिखो(client, 0x098E, command);
	अगर (ret < 0)
		वापस ret;

	वापस __mt9t112_reg_पढ़ो(client, 0x0990);
पूर्ण

अटल पूर्णांक __mt9t112_mcu_ग_लिखो(स्थिर काष्ठा i2c_client *client,
			       u16 command, u16 data)
अणु
	पूर्णांक ret;

	ret = __mt9t112_reg_ग_लिखो(client, 0x098E, command);
	अगर (ret < 0)
		वापस ret;

	वापस __mt9t112_reg_ग_लिखो(client, 0x0990, data);
पूर्ण

अटल पूर्णांक __mt9t112_mcu_mask_set(स्थिर काष्ठा i2c_client *client,
				  u16  command, u16  mask, u16  set)
अणु
	पूर्णांक val = __mt9t112_mcu_पढ़ो(client, command);

	अगर (val < 0)
		वापस val;

	val &= ~mask;
	val |= set & mask;

	वापस __mt9t112_mcu_ग_लिखो(client, command, val);
पूर्ण

अटल पूर्णांक mt9t112_reset(स्थिर काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;

	mt9t112_reg_mask_set(ret, client, 0x001a, 0x0001, 0x0001);
	usleep_range(1000, 5000);
	mt9t112_reg_mask_set(ret, client, 0x001a, 0x0001, 0x0000);

	वापस ret;
पूर्ण

#अगर_अघोषित EXT_CLOCK
#घोषणा CLOCK_INFO(a, b)
#अन्यथा
#घोषणा CLOCK_INFO(a, b) mt9t112_घड़ी_info(a, b)
अटल पूर्णांक mt9t112_घड़ी_info(स्थिर काष्ठा i2c_client *client, u32 ext)
अणु
	पूर्णांक m, n, p1, p2, p3, p4, p5, p6, p7;
	u32 vco, clk;
	अक्षर *enable;

	ext /= 1000; /* kbyte order */

	mt9t112_reg_पढ़ो(n, client, 0x0012);
	p1 = n & 0x000f;
	n = n >> 4;
	p2 = n & 0x000f;
	n = n >> 4;
	p3 = n & 0x000f;

	mt9t112_reg_पढ़ो(n, client, 0x002a);
	p4 = n & 0x000f;
	n = n >> 4;
	p5 = n & 0x000f;
	n = n >> 4;
	p6 = n & 0x000f;

	mt9t112_reg_पढ़ो(n, client, 0x002c);
	p7 = n & 0x000f;

	mt9t112_reg_पढ़ो(n, client, 0x0010);
	m = n & 0x00ff;
	n = (n >> 8) & 0x003f;

	enable = ((ext < 6000) || (ext > 54000)) ? "X" : "";
	dev_dbg(&client->dev, "EXTCLK          : %10u K %s\n", ext, enable);

	vco = 2 * m * ext / (n + 1);
	enable = ((vco < 384000) || (vco > 768000)) ? "X" : "";
	dev_dbg(&client->dev, "VCO             : %10u K %s\n", vco, enable);

	clk = vco / (p1 + 1) / (p2 + 1);
	enable = (clk > 96000) ? "X" : "";
	dev_dbg(&client->dev, "PIXCLK          : %10u K %s\n", clk, enable);

	clk = vco / (p3 + 1);
	enable = (clk > 768000) ? "X" : "";
	dev_dbg(&client->dev, "MIPICLK         : %10u K %s\n", clk, enable);

	clk = vco / (p6 + 1);
	enable = (clk > 96000) ? "X" : "";
	dev_dbg(&client->dev, "MCU CLK         : %10u K %s\n", clk, enable);

	clk = vco / (p5 + 1);
	enable = (clk > 54000) ? "X" : "";
	dev_dbg(&client->dev, "SOC CLK         : %10u K %s\n", clk, enable);

	clk = vco / (p4 + 1);
	enable = (clk > 70000) ? "X" : "";
	dev_dbg(&client->dev, "Sensor CLK      : %10u K %s\n", clk, enable);

	clk = vco / (p7 + 1);
	dev_dbg(&client->dev, "External sensor : %10u K\n", clk);

	clk = ext / (n + 1);
	enable = ((clk < 2000) || (clk > 24000)) ? "X" : "";
	dev_dbg(&client->dev, "PFD             : %10u K %s\n", clk, enable);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mt9t112_set_a_frame_size(स्थिर काष्ठा i2c_client *client,
				    u16 width, u16 height)
अणु
	पूर्णांक ret;
	u16 wstart = (MAX_WIDTH - width) / 2;
	u16 hstart = (MAX_HEIGHT - height) / 2;

	/* (Context A) Image Width/Height. */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(26, 0), width);
	mt9t112_mcu_ग_लिखो(ret, client, VAR(26, 2), height);

	/* (Context A) Output Width/Height. */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 43), 8 + width);
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 45), 8 + height);

	/* (Context A) Start Row/Column. */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 2), 4 + hstart);
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 4), 4 + wstart);

	/* (Context A) End Row/Column. */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 6), 11 + height + hstart);
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 8), 11 + width  + wstart);

	mt9t112_mcu_ग_लिखो(ret, client, VAR8(1, 0), 0x06);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9t112_set_pll_भागiders(स्थिर काष्ठा i2c_client *client,
				    u8 m, u8 n, u8 p1, u8 p2, u8 p3, u8 p4,
				    u8 p5, u8 p6, u8 p7)
अणु
	पूर्णांक ret;
	u16 val;

	/* N/M */
	val = (n << 8) | (m << 0);
	mt9t112_reg_mask_set(ret, client, 0x0010, 0x3fff, val);

	/* P1/P2/P3 */
	val = ((p3 & 0x0F) << 8) | ((p2 & 0x0F) << 4) | ((p1 & 0x0F) << 0);
	mt9t112_reg_mask_set(ret, client, 0x0012, 0x0fff, val);

	/* P4/P5/P6 */
	val = (0x7 << 12) | ((p6 & 0x0F) <<  8) | ((p5 & 0x0F) <<  4) |
	      ((p4 & 0x0F) <<  0);
	mt9t112_reg_mask_set(ret, client, 0x002A, 0x7fff, val);

	/* P7 */
	val = (0x1 << 12) | ((p7 & 0x0F) <<  0);
	mt9t112_reg_mask_set(ret, client, 0x002C, 0x100f, val);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9t112_init_pll(स्थिर काष्ठा i2c_client *client)
अणु
	काष्ठा mt9t112_priv *priv = to_mt9t112(client);
	पूर्णांक data, i, ret;

	mt9t112_reg_mask_set(ret, client, 0x0014, 0x003, 0x0001);

	/* PLL control: BYPASS PLL = 8517. */
	mt9t112_reg_ग_लिखो(ret, client, 0x0014, 0x2145);

	/* Replace these रेजिस्टरs when new timing parameters are generated. */
	mt9t112_set_pll_भागiders(client,
				 priv->info->भागider.m, priv->info->भागider.n,
				 priv->info->भागider.p1, priv->info->भागider.p2,
				 priv->info->भागider.p3, priv->info->भागider.p4,
				 priv->info->भागider.p5, priv->info->भागider.p6,
				 priv->info->भागider.p7);

	/*
	 * TEST_BYPASS  on
	 * PLL_ENABLE   on
	 * SEL_LOCK_DET on
	 * TEST_BYPASS  off
	 */
	mt9t112_reg_ग_लिखो(ret, client, 0x0014, 0x2525);
	mt9t112_reg_ग_लिखो(ret, client, 0x0014, 0x2527);
	mt9t112_reg_ग_लिखो(ret, client, 0x0014, 0x3427);
	mt9t112_reg_ग_लिखो(ret, client, 0x0014, 0x3027);

	mdelay(10);

	/*
	 * PLL_BYPASS off
	 * Reference घड़ी count
	 * I2C Master Clock Divider
	 */
	mt9t112_reg_ग_लिखो(ret, client, 0x0014, 0x3046);
	/* JPEG initialization workaround */
	mt9t112_reg_ग_लिखो(ret, client, 0x0016, 0x0400);
	mt9t112_reg_ग_लिखो(ret, client, 0x0022, 0x0190);
	mt9t112_reg_ग_लिखो(ret, client, 0x3B84, 0x0212);

	/* External sensor घड़ी is PLL bypass. */
	mt9t112_reg_ग_लिखो(ret, client, 0x002E, 0x0500);

	mt9t112_reg_mask_set(ret, client, 0x0018, 0x0002, 0x0002);
	mt9t112_reg_mask_set(ret, client, 0x3B82, 0x0004, 0x0004);

	/* MCU disabled. */
	mt9t112_reg_mask_set(ret, client, 0x0018, 0x0004, 0x0004);

	/* Out of standby. */
	mt9t112_reg_mask_set(ret, client, 0x0018, 0x0001, 0);

	mdelay(50);

	/*
	 * Standby Workaround
	 * Disable Secondary I2C Pads
	 */
	mt9t112_reg_ग_लिखो(ret, client, 0x0614, 0x0001);
	mdelay(1);
	mt9t112_reg_ग_लिखो(ret, client, 0x0614, 0x0001);
	mdelay(1);
	mt9t112_reg_ग_लिखो(ret, client, 0x0614, 0x0001);
	mdelay(1);
	mt9t112_reg_ग_लिखो(ret, client, 0x0614, 0x0001);
	mdelay(1);
	mt9t112_reg_ग_लिखो(ret, client, 0x0614, 0x0001);
	mdelay(1);
	mt9t112_reg_ग_लिखो(ret, client, 0x0614, 0x0001);
	mdelay(1);

	/* Poll to verअगरy out of standby. Must Poll this bit. */
	क्रम (i = 0; i < 100; i++) अणु
		mt9t112_reg_पढ़ो(data, client, 0x0018);
		अगर (!(data & 0x4000))
			अवरोध;

		mdelay(10);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mt9t112_init_setting(स्थिर काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;

	/* Adaptive Output Clock (A) */
	mt9t112_mcu_mask_set(ret, client, VAR(26, 160), 0x0040, 0x0000);

	/* Read Mode (A) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 12), 0x0024);

	/* Fine Correction (A) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 15), 0x00CC);

	/* Fine IT Min (A) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 17), 0x01f1);

	/* Fine IT Max Margin (A) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 19), 0x00fF);

	/* Base Frame Lines (A) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 29), 0x032D);

	/* Min Line Length (A) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 31), 0x073a);

	/* Line Length (A) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 37), 0x07d0);

	/* Adaptive Output Clock (B) */
	mt9t112_mcu_mask_set(ret, client, VAR(27, 160), 0x0040, 0x0000);

	/* Row Start (B) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 74), 0x004);

	/* Column Start (B) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 76), 0x004);

	/* Row End (B) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 78), 0x60B);

	/* Column End (B) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 80), 0x80B);

	/* Fine Correction (B) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 87), 0x008C);

	/* Fine IT Min (B) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 89), 0x01F1);

	/* Fine IT Max Margin (B) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 91), 0x00FF);

	/* Base Frame Lines (B) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 101), 0x0668);

	/* Min Line Length (B) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 103), 0x0AF0);

	/* Line Length (B) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 109), 0x0AF0);

	/*
	 * Flicker Detection रेजिस्टरs.
	 * This section should be replaced whenever new timing file is
	 * generated. All the following रेजिस्टरs need to be replaced.
	 * Following रेजिस्टरs are generated from Register Wizard but user can
	 * modअगरy them. For detail see स्वतः flicker detection tuning.
	 */

	/* FD_FDPERIOD_SELECT */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(8, 5), 0x01);

	/* PRI_B_CONFIG_FD_ALGO_RUN */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(27, 17), 0x0003);

	/* PRI_A_CONFIG_FD_ALGO_RUN */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(26, 17), 0x0003);

	/*
	 * AFD range detection tuning रेजिस्टरs.
	 */

	/* Search_f1_50 */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 165), 0x25);

	/* Search_f2_50 */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 166), 0x28);

	/* Search_f1_60 */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 167), 0x2C);

	/* Search_f2_60 */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 168), 0x2F);

	/* Period_50Hz (A) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 68), 0xBA);

	/* Secret रेजिस्टर by Aptina. */
	/* Period_50Hz (A MSB) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 303), 0x00);

	/* Period_60Hz (A) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 69), 0x9B);

	/* Secret रेजिस्टर by Aptina. */
	/* Period_60Hz (A MSB) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 301), 0x00);

	/* Period_50Hz (B) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 140), 0x82);

	/* Secret रेजिस्टर by Aptina. */
	/* Period_50Hz (B) MSB */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 304), 0x00);

	/* Period_60Hz (B) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 141), 0x6D);

	/* Secret रेजिस्टर by Aptina. */
	/* Period_60Hz (B) MSB */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 302), 0x00);

	/* FD Mode */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(8, 2), 0x10);

	/* Stat_min */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(8, 9), 0x02);

	/* Stat_max */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(8, 10), 0x03);

	/* Min_amplitude */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(8, 12), 0x0A);

	/* RX FIFO Watermark (A) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 70), 0x0014);

	/* RX FIFO Watermark (B) */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(18, 142), 0x0014);

	/* MCLK: 16MHz
	 * PCLK: 73MHz
	 * CorePixCLK: 36.5 MHz
	 */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 0x0044), 133);
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 0x0045), 110);
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 0x008c), 130);
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 0x008d), 108);

	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 0x00A5), 27);
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 0x00a6), 30);
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 0x00a7), 32);
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(18, 0x00a8), 35);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9t112_स्वतः_focus_setting(स्थिर काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;

	mt9t112_mcu_ग_लिखो(ret, client, VAR(12, 13),	0x000F);
	mt9t112_mcu_ग_लिखो(ret, client, VAR(12, 23),	0x0F0F);
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(1, 0),	0x06);

	mt9t112_reg_ग_लिखो(ret, client, 0x0614, 0x0000);

	mt9t112_mcu_ग_लिखो(ret, client, VAR8(1, 0),	0x05);
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(12, 2),	0x02);
	mt9t112_mcu_ग_लिखो(ret, client, VAR(12, 3),	0x0002);
	mt9t112_mcu_ग_लिखो(ret, client, VAR(17, 3),	0x8001);
	mt9t112_mcu_ग_लिखो(ret, client, VAR(17, 11),	0x0025);
	mt9t112_mcu_ग_लिखो(ret, client, VAR(17, 13),	0x0193);
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(17, 33),	0x18);
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(1, 0),	0x05);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9t112_स्वतः_focus_trigger(स्थिर काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;

	mt9t112_mcu_ग_लिखो(ret, client, VAR8(12, 25), 0x01);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9t112_init_camera(स्थिर काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;

	ECHECKER(ret, mt9t112_reset(client));
	ECHECKER(ret, mt9t112_init_pll(client));
	ECHECKER(ret, mt9t112_init_setting(client));
	ECHECKER(ret, mt9t112_स्वतः_focus_setting(client));

	mt9t112_reg_mask_set(ret, client, 0x0018, 0x0004, 0);

	/* Analog setting B.*/
	mt9t112_reg_ग_लिखो(ret, client, 0x3084, 0x2409);
	mt9t112_reg_ग_लिखो(ret, client, 0x3092, 0x0A49);
	mt9t112_reg_ग_लिखो(ret, client, 0x3094, 0x4949);
	mt9t112_reg_ग_लिखो(ret, client, 0x3096, 0x4950);

	/*
	 * Disable adaptive घड़ी.
	 * PRI_A_CONFIG_JPEG_OB_TX_CONTROL_VAR
	 * PRI_B_CONFIG_JPEG_OB_TX_CONTROL_VAR
	 */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(26, 160), 0x0A2E);
	mt9t112_mcu_ग_लिखो(ret, client, VAR(27, 160), 0x0A2E);

	/*
	 * Configure Status in Status_beक्रमe_length Format and enable header.
	 * PRI_B_CONFIG_JPEG_OB_TX_CONTROL_VAR
	 */
	mt9t112_mcu_ग_लिखो(ret, client, VAR(27, 144), 0x0CB4);

	/*
	 * Enable JPEG in context B.
	 * PRI_B_CONFIG_JPEG_OB_TX_CONTROL_VAR
	 */
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(27, 142), 0x01);

	/* Disable Dac_TXLO. */
	mt9t112_reg_ग_लिखो(ret, client, 0x316C, 0x350F);

	/* Set max slew rates. */
	mt9t112_reg_ग_लिखो(ret, client, 0x1E, 0x777);

	वापस ret;
पूर्ण

/************************************************************************
 *			v4l2_subdev_core_ops
 ***********************************************************************/

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक mt9t112_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक                ret;

	reg->size = 2;
	mt9t112_reg_पढ़ो(ret, client, reg->reg);

	reg->val = (__u64)ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9t112_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			      स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक ret;

	mt9t112_reg_ग_लिखो(ret, client, reg->reg, reg->val);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mt9t112_घातer_on(काष्ठा mt9t112_priv *priv)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	अगर (priv->standby_gpio) अणु
		gpiod_set_value(priv->standby_gpio, 0);
		msleep(100);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt9t112_घातer_off(काष्ठा mt9t112_priv *priv)
अणु
	clk_disable_unprepare(priv->clk);
	अगर (priv->standby_gpio) अणु
		gpiod_set_value(priv->standby_gpio, 1);
		msleep(100);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt9t112_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9t112_priv *priv = to_mt9t112(client);

	वापस on ? mt9t112_घातer_on(priv) :
		    mt9t112_घातer_off(priv);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops mt9t112_subdev_core_ops = अणु
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर	= mt9t112_g_रेजिस्टर,
	.s_रेजिस्टर	= mt9t112_s_रेजिस्टर,
#पूर्ण_अगर
	.s_घातer	= mt9t112_s_घातer,
पूर्ण;

/************************************************************************
 *			v4l2_subdev_video_ops
 **********************************************************************/
अटल पूर्णांक mt9t112_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9t112_priv *priv = to_mt9t112(client);
	पूर्णांक ret = 0;

	अगर (!enable) अणु
		/* FIXME
		 *
		 * If user selected large output size, and used it दीर्घ समय,
		 * mt9t112 camera will be very warm.
		 *
		 * But current driver can not stop mt9t112 camera.
		 * So, set small size here to solve this problem.
		 */
		mt9t112_set_a_frame_size(client, VGA_WIDTH, VGA_HEIGHT);
		वापस ret;
	पूर्ण

	अगर (!priv->init_करोne) अणु
		u16 param = MT9T112_FLAG_PCLK_RISING_EDGE & priv->info->flags ?
			    0x0001 : 0x0000;

		ECHECKER(ret, mt9t112_init_camera(client));

		/* Invert PCLK (Data sampled on falling edge of pixclk). */
		mt9t112_reg_ग_लिखो(ret, client, 0x3C20, param);

		mdelay(5);

		priv->init_करोne = true;
	पूर्ण

	mt9t112_mcu_ग_लिखो(ret, client, VAR(26, 7), priv->क्रमmat->fmt);
	mt9t112_mcu_ग_लिखो(ret, client, VAR(26, 9), priv->क्रमmat->order);
	mt9t112_mcu_ग_लिखो(ret, client, VAR8(1, 0), 0x06);

	mt9t112_set_a_frame_size(client, priv->frame.width, priv->frame.height);

	ECHECKER(ret, mt9t112_स्वतः_focus_trigger(client));

	dev_dbg(&client->dev, "format : %d\n", priv->क्रमmat->code);
	dev_dbg(&client->dev, "size   : %d x %d\n",
		priv->frame.width,
		priv->frame.height);

	CLOCK_INFO(client, EXT_CLOCK);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9t112_set_params(काष्ठा mt9t112_priv *priv,
			      स्थिर काष्ठा v4l2_rect *rect,
			      u32 code)
अणु
	पूर्णांक i;

	/*
	 * get color क्रमmat
	 */
	क्रम (i = 0; i < priv->num_क्रमmats; i++)
		अगर (mt9t112_cfmts[i].code == code)
			अवरोध;

	अगर (i == priv->num_क्रमmats)
		वापस -EINVAL;

	priv->frame = *rect;

	/*
	 * frame size check
	 */
	v4l_bound_align_image(&priv->frame.width, 0, MAX_WIDTH, 0,
			      &priv->frame.height, 0, MAX_HEIGHT, 0, 0);

	priv->क्रमmat = mt9t112_cfmts + i;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9t112_get_selection(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9t112_priv *priv = to_mt9t112(client);

	अगर (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = MAX_WIDTH;
		sel->r.height = MAX_HEIGHT;
		वापस 0;
	हाल V4L2_SEL_TGT_CROP:
		sel->r = priv->frame;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mt9t112_set_selection(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9t112_priv *priv = to_mt9t112(client);
	स्थिर काष्ठा v4l2_rect *rect = &sel->r;

	अगर (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE ||
	    sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	वापस mt9t112_set_params(priv, rect, priv->क्रमmat->code);
पूर्ण

अटल पूर्णांक mt9t112_get_fmt(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9t112_priv *priv = to_mt9t112(client);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	mf->width	= priv->frame.width;
	mf->height	= priv->frame.height;
	mf->colorspace	= priv->क्रमmat->colorspace;
	mf->code	= priv->क्रमmat->code;
	mf->field	= V4L2_FIELD_NONE;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9t112_s_fmt(काष्ठा v4l2_subdev *sd,
			 काष्ठा v4l2_mbus_framefmt *mf)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9t112_priv *priv = to_mt9t112(client);
	काष्ठा v4l2_rect rect = अणु
		.width = mf->width,
		.height = mf->height,
		.left = priv->frame.left,
		.top = priv->frame.top,
	पूर्ण;
	पूर्णांक ret;

	ret = mt9t112_set_params(priv, &rect, mf->code);

	अगर (!ret)
		mf->colorspace = priv->क्रमmat->colorspace;

	वापस ret;
पूर्ण

अटल पूर्णांक mt9t112_set_fmt(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *mf = &क्रमmat->क्रमmat;
	काष्ठा mt9t112_priv *priv = to_mt9t112(client);
	पूर्णांक i;

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	क्रम (i = 0; i < priv->num_क्रमmats; i++)
		अगर (mt9t112_cfmts[i].code == mf->code)
			अवरोध;

	अगर (i == priv->num_क्रमmats) अणु
		mf->code = MEDIA_BUS_FMT_UYVY8_2X8;
		mf->colorspace = V4L2_COLORSPACE_JPEG;
	पूर्ण अन्यथा अणु
		mf->colorspace = mt9t112_cfmts[i].colorspace;
	पूर्ण

	v4l_bound_align_image(&mf->width, 0, MAX_WIDTH, 0,
			      &mf->height, 0, MAX_HEIGHT, 0, 0);

	mf->field = V4L2_FIELD_NONE;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस mt9t112_s_fmt(sd, mf);
	cfg->try_fmt = *mf;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9t112_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा mt9t112_priv *priv = to_mt9t112(client);

	अगर (code->pad || code->index >= priv->num_क्रमmats)
		वापस -EINVAL;

	code->code = mt9t112_cfmts[code->index].code;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops mt9t112_subdev_video_ops = अणु
	.s_stream	= mt9t112_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops mt9t112_subdev_pad_ops = अणु
	.क्रमागत_mbus_code	= mt9t112_क्रमागत_mbus_code,
	.get_selection	= mt9t112_get_selection,
	.set_selection	= mt9t112_set_selection,
	.get_fmt	= mt9t112_get_fmt,
	.set_fmt	= mt9t112_set_fmt,
पूर्ण;

/************************************************************************
 *			i2c driver
 ***********************************************************************/
अटल स्थिर काष्ठा v4l2_subdev_ops mt9t112_subdev_ops = अणु
	.core	= &mt9t112_subdev_core_ops,
	.video	= &mt9t112_subdev_video_ops,
	.pad	= &mt9t112_subdev_pad_ops,
पूर्ण;

अटल पूर्णांक mt9t112_camera_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा mt9t112_priv *priv = to_mt9t112(client);
	स्थिर अक्षर          *devname;
	पूर्णांक                  chipid;
	पूर्णांक		     ret;

	ret = mt9t112_s_घातer(&priv->subdev, 1);
	अगर (ret < 0)
		वापस ret;

	/* Check and show chip ID. */
	mt9t112_reg_पढ़ो(chipid, client, 0x0000);

	चयन (chipid) अणु
	हाल 0x2680:
		devname = "mt9t111";
		priv->num_क्रमmats = 1;
		अवरोध;
	हाल 0x2682:
		devname = "mt9t112";
		priv->num_क्रमmats = ARRAY_SIZE(mt9t112_cfmts);
		अवरोध;
	शेष:
		dev_err(&client->dev, "Product ID error %04x\n", chipid);
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	dev_info(&client->dev, "%s chip ID %04x\n", devname, chipid);

करोne:
	mt9t112_s_घातer(&priv->subdev, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9t112_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *did)
अणु
	काष्ठा mt9t112_priv *priv;
	पूर्णांक ret;

	अगर (!client->dev.platक्रमm_data) अणु
		dev_err(&client->dev, "mt9t112: missing platform data!\n");
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(&client->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->info = client->dev.platक्रमm_data;
	priv->init_करोne = false;

	v4l2_i2c_subdev_init(&priv->subdev, client, &mt9t112_subdev_ops);

	priv->clk = devm_clk_get(&client->dev, "extclk");
	अगर (PTR_ERR(priv->clk) == -ENOENT) अणु
		priv->clk = शून्य;
	पूर्ण अन्यथा अगर (IS_ERR(priv->clk)) अणु
		dev_err(&client->dev, "Unable to get clock \"extclk\"\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	priv->standby_gpio = devm_gpiod_get_optional(&client->dev, "standby",
						     GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->standby_gpio)) अणु
		dev_err(&client->dev, "Unable to get gpio \"standby\"\n");
		वापस PTR_ERR(priv->standby_gpio);
	पूर्ण

	ret = mt9t112_camera_probe(client);
	अगर (ret)
		वापस ret;

	वापस v4l2_async_रेजिस्टर_subdev(&priv->subdev);
पूर्ण

अटल पूर्णांक mt9t112_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा mt9t112_priv *priv = to_mt9t112(client);

	clk_disable_unprepare(priv->clk);
	v4l2_async_unरेजिस्टर_subdev(&priv->subdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mt9t112_id[] = अणु
	अणु "mt9t112", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mt9t112_id);

अटल काष्ठा i2c_driver mt9t112_i2c_driver = अणु
	.driver = अणु
		.name = "mt9t112",
	पूर्ण,
	.probe    = mt9t112_probe,
	.हटाओ   = mt9t112_हटाओ,
	.id_table = mt9t112_id,
पूर्ण;

module_i2c_driver(mt9t112_i2c_driver);

MODULE_DESCRIPTION("V4L2 driver for MT9T111/MT9T112 camera sensor");
MODULE_AUTHOR("Kuninori Morimoto");
MODULE_LICENSE("GPL v2");
