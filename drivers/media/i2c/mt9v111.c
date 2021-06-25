<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * V4L2 sensor driver क्रम Aptina MT9V111 image sensor
 * Copyright (C) 2018 Jacopo Mondi <jacopo@jmondi.org>
 *
 * Based on mt9v032 driver
 * Copyright (C) 2010, Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 * Copyright (C) 2008, Guennadi Liakhovetski <kernel@pengutronix.de>
 *
 * Based on mt9v011 driver
 * Copyright (c) 2009 Mauro Carvalho Chehab <mchehab@kernel.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/v4l2-mediabus.h>
#समावेश <linux/module.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-image-sizes.h>
#समावेश <media/v4l2-subdev.h>

/*
 * MT9V111 is a 1/4-Inch CMOS digital image sensor with an पूर्णांकegrated
 * Image Flow Processing (IFP) engine and a sensor core loosely based on
 * MT9V011.
 *
 * The IFP can produce several output image क्रमmats from the sensor core
 * output. This driver currently supports only YUYV क्रमmat permutations.
 *
 * The driver allows manual frame rate control through s_frame_पूर्णांकerval subdev
 * operation or V4L2_CID_V/HBLANK controls, but it is known that the
 * स्वतः-exposure algorithm might modअगरy the programmed frame rate. While the
 * driver initially programs the sensor with स्वतः-exposure and
 * स्वतः-white-balancing enabled, it is possible to disable them and more
 * precisely control the frame rate.
 *
 * While it seems possible to inकाष्ठा the स्वतः-exposure control algorithm to
 * respect a programmed frame rate when adjusting the pixel पूर्णांकegration समय,
 * रेजिस्टरs controlling this feature are not करोcumented in the खुला
 * available sensor manual used to develop this driver (09005aef80e90084,
 * MT9V111_1.fm - Rev. G 1/05 EN).
 */

#घोषणा MT9V111_CHIP_ID_HIGH				0x82
#घोषणा MT9V111_CHIP_ID_LOW				0x3a

#घोषणा MT9V111_R01_ADDR_SPACE				0x01
#घोषणा MT9V111_R01_IFP					0x01
#घोषणा MT9V111_R01_CORE				0x04

#घोषणा MT9V111_IFP_R06_OPMODE_CTRL			0x06
#घोषणा		MT9V111_IFP_R06_OPMODE_CTRL_AWB_EN	BIT(1)
#घोषणा		MT9V111_IFP_R06_OPMODE_CTRL_AE_EN	BIT(14)
#घोषणा MT9V111_IFP_R07_IFP_RESET			0x07
#घोषणा		MT9V111_IFP_R07_IFP_RESET_MASK		BIT(0)
#घोषणा MT9V111_IFP_R08_OUTFMT_CTRL			0x08
#घोषणा		MT9V111_IFP_R08_OUTFMT_CTRL_FLICKER	BIT(11)
#घोषणा		MT9V111_IFP_R08_OUTFMT_CTRL_PCLK	BIT(5)
#घोषणा MT9V111_IFP_R3A_OUTFMT_CTRL2			0x3a
#घोषणा		MT9V111_IFP_R3A_OUTFMT_CTRL2_SWAP_CBCR	BIT(0)
#घोषणा		MT9V111_IFP_R3A_OUTFMT_CTRL2_SWAP_YC	BIT(1)
#घोषणा		MT9V111_IFP_R3A_OUTFMT_CTRL2_SWAP_MASK	GENMASK(2, 0)
#घोषणा MT9V111_IFP_RA5_HPAN				0xa5
#घोषणा MT9V111_IFP_RA6_HZOOM				0xa6
#घोषणा MT9V111_IFP_RA7_HOUT				0xa7
#घोषणा MT9V111_IFP_RA8_VPAN				0xa8
#घोषणा MT9V111_IFP_RA9_VZOOM				0xa9
#घोषणा MT9V111_IFP_RAA_VOUT				0xaa
#घोषणा MT9V111_IFP_DECIMATION_MASK			GENMASK(9, 0)
#घोषणा MT9V111_IFP_DECIMATION_FREEZE			BIT(15)

#घोषणा MT9V111_CORE_R03_WIN_HEIGHT			0x03
#घोषणा		MT9V111_CORE_R03_WIN_V_OFFS		2
#घोषणा MT9V111_CORE_R04_WIN_WIDTH			0x04
#घोषणा		MT9V111_CORE_R04_WIN_H_OFFS		114
#घोषणा MT9V111_CORE_R05_HBLANK				0x05
#घोषणा		MT9V111_CORE_R05_MIN_HBLANK		0x09
#घोषणा		MT9V111_CORE_R05_MAX_HBLANK		GENMASK(9, 0)
#घोषणा		MT9V111_CORE_R05_DEF_HBLANK		0x26
#घोषणा MT9V111_CORE_R06_VBLANK				0x06
#घोषणा		MT9V111_CORE_R06_MIN_VBLANK		0x03
#घोषणा		MT9V111_CORE_R06_MAX_VBLANK		GENMASK(11, 0)
#घोषणा		MT9V111_CORE_R06_DEF_VBLANK		0x04
#घोषणा MT9V111_CORE_R07_OUT_CTRL			0x07
#घोषणा		MT9V111_CORE_R07_OUT_CTRL_SAMPLE	BIT(4)
#घोषणा MT9V111_CORE_R09_PIXEL_INT			0x09
#घोषणा		MT9V111_CORE_R09_PIXEL_INT_MASK		GENMASK(11, 0)
#घोषणा MT9V111_CORE_R0D_CORE_RESET			0x0d
#घोषणा		MT9V111_CORE_R0D_CORE_RESET_MASK	BIT(0)
#घोषणा MT9V111_CORE_RFF_CHIP_VER			0xff

#घोषणा MT9V111_PIXEL_ARRAY_WIDTH			640
#घोषणा MT9V111_PIXEL_ARRAY_HEIGHT			480

#घोषणा MT9V111_MAX_CLKIN				27000000

/* The शेष sensor configuration at startup समय. */
अटल स्थिर काष्ठा v4l2_mbus_framefmt mt9v111_def_fmt = अणु
	.width		= 640,
	.height		= 480,
	.code		= MEDIA_BUS_FMT_UYVY8_2X8,
	.field		= V4L2_FIELD_NONE,
	.colorspace	= V4L2_COLORSPACE_SRGB,
	.ycbcr_enc	= V4L2_YCBCR_ENC_601,
	.quantization	= V4L2_QUANTIZATION_LIM_RANGE,
	.xfer_func	= V4L2_XFER_FUNC_SRGB,
पूर्ण;

काष्ठा mt9v111_dev अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *client;

	u8 addr_space;

	काष्ठा v4l2_subdev sd;
#अगर IS_ENABLED(CONFIG_MEDIA_CONTROLLER)
	काष्ठा media_pad pad;
#पूर्ण_अगर

	काष्ठा v4l2_ctrl *स्वतः_awb;
	काष्ठा v4l2_ctrl *स्वतः_exp;
	काष्ठा v4l2_ctrl *hblank;
	काष्ठा v4l2_ctrl *vblank;
	काष्ठा v4l2_ctrl_handler ctrls;

	/* Output image क्रमmat and sizes. */
	काष्ठा v4l2_mbus_framefmt fmt;
	अचिन्हित पूर्णांक fps;

	/* Protects घातer up/करोwn sequences. */
	काष्ठा mutex pwr_mutex;
	पूर्णांक pwr_count;

	/* Protects stream on/off sequences. */
	काष्ठा mutex stream_mutex;
	bool streaming;

	/* Flags to mark HW settings as not yet applied. */
	bool pending;

	/* Clock provider and प्रणाली घड़ी frequency. */
	काष्ठा clk *clk;
	u32 sysclk;

	काष्ठा gpio_desc *oe;
	काष्ठा gpio_desc *standby;
	काष्ठा gpio_desc *reset;
पूर्ण;

#घोषणा sd_to_mt9v111(__sd) container_of((__sd), काष्ठा mt9v111_dev, sd)

/*
 * mt9v111_mbus_fmt - List all media bus क्रमmats supported by the driver.
 *
 * Only list the media bus code here. The image sizes are मुक्तly configurable
 * in the pixel array sizes range.
 *
 * The desired frame पूर्णांकerval, in the supported frame पूर्णांकerval range, is
 * obtained by configuring blanking as the sensor करोes not have a PLL but
 * only a fixed घड़ी भागider that generates the output pixel घड़ी.
 */
अटल काष्ठा mt9v111_mbus_fmt अणु
	u32	code;
पूर्ण mt9v111_क्रमmats[] = अणु
	अणु
		.code	= MEDIA_BUS_FMT_UYVY8_2X8,
	पूर्ण,
	अणु
		.code	= MEDIA_BUS_FMT_YUYV8_2X8,
	पूर्ण,
	अणु
		.code	= MEDIA_BUS_FMT_VYUY8_2X8,
	पूर्ण,
	अणु
		.code	= MEDIA_BUS_FMT_YVYU8_2X8,
	पूर्ण,
पूर्ण;

अटल u32 mt9v111_frame_पूर्णांकervals[] = अणु5, 10, 15, 20, 30पूर्ण;

/*
 * mt9v111_frame_sizes - List sensor's supported resolutions.
 *
 * Resolution generated through decimation in the IFP block from the
 * full VGA pixel array.
 */
अटल काष्ठा v4l2_rect mt9v111_frame_sizes[] = अणु
	अणु
		.width	= 640,
		.height	= 480,
	पूर्ण,
	अणु
		.width	= 352,
		.height	= 288
	पूर्ण,
	अणु
		.width	= 320,
		.height	= 240,
	पूर्ण,
	अणु
		.width	= 176,
		.height	= 144,
	पूर्ण,
	अणु
		.width	= 160,
		.height	= 120,
	पूर्ण,
पूर्ण;

/* --- Device I/O access --- */

अटल पूर्णांक __mt9v111_पढ़ो(काष्ठा i2c_client *c, u8 reg, u16 *val)
अणु
	काष्ठा i2c_msg msg[2];
	__be16 buf;
	पूर्णांक ret;

	msg[0].addr = c->addr;
	msg[0].flags = 0;
	msg[0].len = 1;
	msg[0].buf = &reg;

	msg[1].addr = c->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = 2;
	msg[1].buf = (अक्षर *)&buf;

	ret = i2c_transfer(c->adapter, msg, 2);
	अगर (ret < 0) अणु
		dev_err(&c->dev, "i2c read transfer error: %d\n", ret);
		वापस ret;
	पूर्ण

	*val = be16_to_cpu(buf);

	dev_dbg(&c->dev, "%s: %x=%x\n", __func__, reg, *val);

	वापस 0;
पूर्ण

अटल पूर्णांक __mt9v111_ग_लिखो(काष्ठा i2c_client *c, u8 reg, u16 val)
अणु
	काष्ठा i2c_msg msg;
	u8 buf[3] = अणु 0 पूर्ण;
	पूर्णांक ret;

	buf[0] = reg;
	buf[1] = val >> 8;
	buf[2] = val & 0xff;

	msg.addr = c->addr;
	msg.flags = 0;
	msg.len = 3;
	msg.buf = (अक्षर *)buf;

	dev_dbg(&c->dev, "%s: %x = %x%x\n", __func__, reg, buf[1], buf[2]);

	ret = i2c_transfer(c->adapter, &msg, 1);
	अगर (ret < 0) अणु
		dev_err(&c->dev, "i2c write transfer error: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __mt9v111_addr_space_select(काष्ठा i2c_client *c, u16 addr_space)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(c);
	काष्ठा mt9v111_dev *mt9v111 = sd_to_mt9v111(sd);
	u16 val;
	पूर्णांक ret;

	अगर (mt9v111->addr_space == addr_space)
		वापस 0;

	ret = __mt9v111_ग_लिखो(c, MT9V111_R01_ADDR_SPACE, addr_space);
	अगर (ret)
		वापस ret;

	/* Verअगरy address space has been updated */
	ret = __mt9v111_पढ़ो(c, MT9V111_R01_ADDR_SPACE, &val);
	अगर (ret)
		वापस ret;

	अगर (val != addr_space)
		वापस -EINVAL;

	mt9v111->addr_space = addr_space;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v111_पढ़ो(काष्ठा i2c_client *c, u8 addr_space, u8 reg, u16 *val)
अणु
	पूर्णांक ret;

	/* Select रेजिस्टर address space first. */
	ret = __mt9v111_addr_space_select(c, addr_space);
	अगर (ret)
		वापस ret;

	ret = __mt9v111_पढ़ो(c, reg, val);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v111_ग_लिखो(काष्ठा i2c_client *c, u8 addr_space, u8 reg, u16 val)
अणु
	पूर्णांक ret;

	/* Select रेजिस्टर address space first. */
	ret = __mt9v111_addr_space_select(c, addr_space);
	अगर (ret)
		वापस ret;

	ret = __mt9v111_ग_लिखो(c, reg, val);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v111_update(काष्ठा i2c_client *c, u8 addr_space, u8 reg,
			  u16 mask, u16 val)
अणु
	u16 current_val;
	पूर्णांक ret;

	/* Select रेजिस्टर address space first. */
	ret = __mt9v111_addr_space_select(c, addr_space);
	अगर (ret)
		वापस ret;

	/* Read the current रेजिस्टर value, then update it. */
	ret = __mt9v111_पढ़ो(c, reg, &current_val);
	अगर (ret)
		वापस ret;

	current_val &= ~mask;
	current_val |= (val & mask);
	ret = __mt9v111_ग_लिखो(c, reg, current_val);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/* --- Sensor HW operations --- */

अटल पूर्णांक __mt9v111_घातer_on(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा mt9v111_dev *mt9v111 = sd_to_mt9v111(sd);
	पूर्णांक ret;

	ret = clk_prepare_enable(mt9v111->clk);
	अगर (ret)
		वापस ret;

	clk_set_rate(mt9v111->clk, mt9v111->sysclk);

	gpiod_set_value(mt9v111->standby, 0);
	usleep_range(500, 1000);

	gpiod_set_value(mt9v111->oe, 1);
	usleep_range(500, 1000);

	वापस 0;
पूर्ण

अटल पूर्णांक __mt9v111_घातer_off(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा mt9v111_dev *mt9v111 = sd_to_mt9v111(sd);

	gpiod_set_value(mt9v111->oe, 0);
	usleep_range(500, 1000);

	gpiod_set_value(mt9v111->standby, 1);
	usleep_range(500, 1000);

	clk_disable_unprepare(mt9v111->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __mt9v111_hw_reset(काष्ठा mt9v111_dev *mt9v111)
अणु
	अगर (!mt9v111->reset)
		वापस -EINVAL;

	gpiod_set_value(mt9v111->reset, 1);
	usleep_range(500, 1000);

	gpiod_set_value(mt9v111->reset, 0);
	usleep_range(500, 1000);

	वापस 0;
पूर्ण

अटल पूर्णांक __mt9v111_sw_reset(काष्ठा mt9v111_dev *mt9v111)
अणु
	काष्ठा i2c_client *c = mt9v111->client;
	पूर्णांक ret;

	/* Software reset core and IFP blocks. */

	ret = mt9v111_update(c, MT9V111_R01_CORE,
			     MT9V111_CORE_R0D_CORE_RESET,
			     MT9V111_CORE_R0D_CORE_RESET_MASK, 1);
	अगर (ret)
		वापस ret;
	usleep_range(500, 1000);

	ret = mt9v111_update(c, MT9V111_R01_CORE,
			     MT9V111_CORE_R0D_CORE_RESET,
			     MT9V111_CORE_R0D_CORE_RESET_MASK, 0);
	अगर (ret)
		वापस ret;
	usleep_range(500, 1000);

	ret = mt9v111_update(c, MT9V111_R01_IFP,
			     MT9V111_IFP_R07_IFP_RESET,
			     MT9V111_IFP_R07_IFP_RESET_MASK, 1);
	अगर (ret)
		वापस ret;
	usleep_range(500, 1000);

	ret = mt9v111_update(c, MT9V111_R01_IFP,
			     MT9V111_IFP_R07_IFP_RESET,
			     MT9V111_IFP_R07_IFP_RESET_MASK, 0);
	अगर (ret)
		वापस ret;
	usleep_range(500, 1000);

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v111_calc_frame_rate(काष्ठा mt9v111_dev *mt9v111,
				   काष्ठा v4l2_fract *tpf)
अणु
	अचिन्हित पूर्णांक fps = tpf->numerator ?
			   tpf->denominator / tpf->numerator :
			   tpf->denominator;
	अचिन्हित पूर्णांक best_dअगरf;
	अचिन्हित पूर्णांक frm_cols;
	अचिन्हित पूर्णांक row_pclk;
	अचिन्हित पूर्णांक best_fps;
	अचिन्हित पूर्णांक pclk;
	अचिन्हित पूर्णांक dअगरf;
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक hb;
	अचिन्हित पूर्णांक vb;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* Approximate to the बंदst supported frame पूर्णांकerval. */
	best_dअगरf = ~0L;
	क्रम (i = 0, idx = 0; i < ARRAY_SIZE(mt9v111_frame_पूर्णांकervals); i++) अणु
		dअगरf = असल(fps - mt9v111_frame_पूर्णांकervals[i]);
		अगर (dअगरf < best_dअगरf) अणु
			idx = i;
			best_dअगरf = dअगरf;
		पूर्ण
	पूर्ण
	fps = mt9v111_frame_पूर्णांकervals[idx];

	/*
	 * The sensor करोes not provide a PLL circuitry and pixel घड़ी is
	 * generated भागiding the master घड़ी source by two.
	 *
	 * Trow = (W + Hblank + 114) * 2 * (1 / SYSCLK)
	 * TFrame = Trow * (H + Vblank + 2)
	 *
	 * FPS = (SYSCLK / 2) / (Trow * (H + Vblank + 2))
	 *
	 * This boils करोwn to tune H and V blanks to best approximate the
	 * above equation.
	 *
	 * Test all available H/V blank values, until we reach the
	 * desired frame rate.
	 */
	best_fps = vb = hb = 0;
	pclk = DIV_ROUND_CLOSEST(mt9v111->sysclk, 2);
	row_pclk = MT9V111_PIXEL_ARRAY_WIDTH + 7 + MT9V111_CORE_R04_WIN_H_OFFS;
	frm_cols = MT9V111_PIXEL_ARRAY_HEIGHT + 7 + MT9V111_CORE_R03_WIN_V_OFFS;

	best_dअगरf = ~0L;
	क्रम (vb = MT9V111_CORE_R06_MIN_VBLANK;
	     vb < MT9V111_CORE_R06_MAX_VBLANK; vb++) अणु
		क्रम (hb = MT9V111_CORE_R05_MIN_HBLANK;
		     hb < MT9V111_CORE_R05_MAX_HBLANK; hb += 10) अणु
			अचिन्हित पूर्णांक t_frame = (row_pclk + hb) *
					       (frm_cols + vb);
			अचिन्हित पूर्णांक t_fps = DIV_ROUND_CLOSEST(pclk, t_frame);

			dअगरf = असल(fps - t_fps);
			अगर (dअगरf < best_dअगरf) अणु
				best_dअगरf = dअगरf;
				best_fps = t_fps;

				अगर (dअगरf == 0)
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (dअगरf == 0)
			अवरोध;
	पूर्ण

	ret = v4l2_ctrl_s_ctrl_पूर्णांक64(mt9v111->hblank, hb);
	अगर (ret)
		वापस ret;

	ret = v4l2_ctrl_s_ctrl_पूर्णांक64(mt9v111->vblank, vb);
	अगर (ret)
		वापस ret;

	tpf->numerator = 1;
	tpf->denominator = best_fps;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v111_hw_config(काष्ठा mt9v111_dev *mt9v111)
अणु
	काष्ठा i2c_client *c = mt9v111->client;
	अचिन्हित पूर्णांक ret;
	u16 outfmtctrl2;

	/* Force device reset. */
	ret = __mt9v111_hw_reset(mt9v111);
	अगर (ret == -EINVAL)
		ret = __mt9v111_sw_reset(mt9v111);
	अगर (ret)
		वापस ret;

	/* Configure पूर्णांकernal घड़ी sample rate. */
	ret = mt9v111->sysclk < DIV_ROUND_CLOSEST(MT9V111_MAX_CLKIN, 2) ?
				mt9v111_update(c, MT9V111_R01_CORE,
					MT9V111_CORE_R07_OUT_CTRL,
					MT9V111_CORE_R07_OUT_CTRL_SAMPLE, 1) :
				mt9v111_update(c, MT9V111_R01_CORE,
					MT9V111_CORE_R07_OUT_CTRL,
					MT9V111_CORE_R07_OUT_CTRL_SAMPLE, 0);
	अगर (ret)
		वापस ret;

	/*
	 * Configure output image क्रमmat components ordering.
	 *
	 * TODO: IFP block can also output several RGB permutations, we only
	 *	 support YUYV permutations at the moment.
	 */
	चयन (mt9v111->fmt.code) अणु
	हाल MEDIA_BUS_FMT_YUYV8_2X8:
			outfmtctrl2 = MT9V111_IFP_R3A_OUTFMT_CTRL2_SWAP_YC;
			अवरोध;
	हाल MEDIA_BUS_FMT_VYUY8_2X8:
			outfmtctrl2 = MT9V111_IFP_R3A_OUTFMT_CTRL2_SWAP_CBCR;
			अवरोध;
	हाल MEDIA_BUS_FMT_YVYU8_2X8:
			outfmtctrl2 = MT9V111_IFP_R3A_OUTFMT_CTRL2_SWAP_YC |
				      MT9V111_IFP_R3A_OUTFMT_CTRL2_SWAP_CBCR;
			अवरोध;
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
	शेष:
			outfmtctrl2 = 0;
			अवरोध;
	पूर्ण

	ret = mt9v111_update(c, MT9V111_R01_IFP, MT9V111_IFP_R3A_OUTFMT_CTRL2,
			     MT9V111_IFP_R3A_OUTFMT_CTRL2_SWAP_MASK,
			     outfmtctrl2);
	अगर (ret)
		वापस ret;

	/*
	 * Do not change शेष sensor's core configuration:
	 * output the whole 640x480 pixel array, skip 18 columns and 6 rows.
	 *
	 * Instead, control the output image size through IFP block.
	 *
	 * TODO: No zoom&pan support. Currently we control the output image
	 *	 size only through decimation, with no zoom support.
	 */
	ret = mt9v111_ग_लिखो(c, MT9V111_R01_IFP, MT9V111_IFP_RA5_HPAN,
			    MT9V111_IFP_DECIMATION_FREEZE);
	अगर (ret)
		वापस ret;

	ret = mt9v111_ग_लिखो(c, MT9V111_R01_IFP, MT9V111_IFP_RA8_VPAN,
			    MT9V111_IFP_DECIMATION_FREEZE);
	अगर (ret)
		वापस ret;

	ret = mt9v111_ग_लिखो(c, MT9V111_R01_IFP, MT9V111_IFP_RA6_HZOOM,
			    MT9V111_IFP_DECIMATION_FREEZE |
			    MT9V111_PIXEL_ARRAY_WIDTH);
	अगर (ret)
		वापस ret;

	ret = mt9v111_ग_लिखो(c, MT9V111_R01_IFP, MT9V111_IFP_RA9_VZOOM,
			    MT9V111_IFP_DECIMATION_FREEZE |
			    MT9V111_PIXEL_ARRAY_HEIGHT);
	अगर (ret)
		वापस ret;

	ret = mt9v111_ग_लिखो(c, MT9V111_R01_IFP, MT9V111_IFP_RA7_HOUT,
			    MT9V111_IFP_DECIMATION_FREEZE |
			    mt9v111->fmt.width);
	अगर (ret)
		वापस ret;

	ret = mt9v111_ग_लिखो(c, MT9V111_R01_IFP, MT9V111_IFP_RAA_VOUT,
			    mt9v111->fmt.height);
	अगर (ret)
		वापस ret;

	/* Apply controls to set स्वतः exp, स्वतः awb and timings */
	ret = v4l2_ctrl_handler_setup(&mt9v111->ctrls);
	अगर (ret)
		वापस ret;

	/*
	 * Set pixel पूर्णांकegration समय to the whole frame समय.
	 * This value controls the the shutter delay when running with AE
	 * disabled. If दीर्घer than frame समय, it affects the output
	 * frame rate.
	 */
	वापस mt9v111_ग_लिखो(c, MT9V111_R01_CORE, MT9V111_CORE_R09_PIXEL_INT,
			     MT9V111_PIXEL_ARRAY_HEIGHT);
पूर्ण

/* ---  V4L2 subdev operations --- */

अटल पूर्णांक mt9v111_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा mt9v111_dev *mt9v111 = sd_to_mt9v111(sd);
	पूर्णांक pwr_count;
	पूर्णांक ret = 0;

	mutex_lock(&mt9v111->pwr_mutex);

	/*
	 * Make sure we're transitioning from 0 to 1, or viceversa,
	 * beक्रमe actually changing the घातer state.
	 */
	pwr_count = mt9v111->pwr_count;
	pwr_count += on ? 1 : -1;
	अगर (pwr_count == !!on) अणु
		ret = on ? __mt9v111_घातer_on(sd) :
			   __mt9v111_घातer_off(sd);
		अगर (!ret)
			/* All went well, updated घातer counter. */
			mt9v111->pwr_count = pwr_count;

		mutex_unlock(&mt9v111->pwr_mutex);

		वापस ret;
	पूर्ण

	/*
	 * Update घातer counter to keep track of how many nested calls we
	 * received.
	 */
	WARN_ON(pwr_count < 0 || pwr_count > 1);
	mt9v111->pwr_count = pwr_count;

	mutex_unlock(&mt9v111->pwr_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9v111_s_stream(काष्ठा v4l2_subdev *subdev, पूर्णांक enable)
अणु
	काष्ठा mt9v111_dev *mt9v111 = sd_to_mt9v111(subdev);
	पूर्णांक ret;

	mutex_lock(&mt9v111->stream_mutex);

	अगर (mt9v111->streaming == enable) अणु
		mutex_unlock(&mt9v111->stream_mutex);
		वापस 0;
	पूर्ण

	ret = mt9v111_s_घातer(subdev, enable);
	अगर (ret)
		जाओ error_unlock;

	अगर (enable && mt9v111->pending) अणु
		ret = mt9v111_hw_config(mt9v111);
		अगर (ret)
			जाओ error_unlock;

		/*
		 * No need to update control here as far as only H/VBLANK are
		 * supported and immediately programmed to रेजिस्टरs in .s_ctrl
		 */

		mt9v111->pending = false;
	पूर्ण

	mt9v111->streaming = enable ? true : false;
	mutex_unlock(&mt9v111->stream_mutex);

	वापस 0;

error_unlock:
	mutex_unlock(&mt9v111->stream_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9v111_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_frame_पूर्णांकerval *ival)
अणु
	काष्ठा mt9v111_dev *mt9v111 = sd_to_mt9v111(sd);
	काष्ठा v4l2_fract *tpf = &ival->पूर्णांकerval;
	अचिन्हित पूर्णांक fps = tpf->numerator ?
			   tpf->denominator / tpf->numerator :
			   tpf->denominator;
	अचिन्हित पूर्णांक max_fps;

	अगर (!tpf->numerator)
		tpf->numerator = 1;

	mutex_lock(&mt9v111->stream_mutex);

	अगर (mt9v111->streaming) अणु
		mutex_unlock(&mt9v111->stream_mutex);
		वापस -EBUSY;
	पूर्ण

	अगर (mt9v111->fps == fps) अणु
		mutex_unlock(&mt9v111->stream_mutex);
		वापस 0;
	पूर्ण

	/* Make sure frame rate/image sizes स्थिरraपूर्णांकs are respected. */
	अगर (mt9v111->fmt.width < QVGA_WIDTH &&
	    mt9v111->fmt.height < QVGA_HEIGHT)
		max_fps = 90;
	अन्यथा अगर (mt9v111->fmt.width < CIF_WIDTH &&
		 mt9v111->fmt.height < CIF_HEIGHT)
		max_fps = 60;
	अन्यथा
		max_fps = mt9v111->sysclk <
				DIV_ROUND_CLOSEST(MT9V111_MAX_CLKIN, 2) ? 15 :
									  30;

	अगर (fps > max_fps) अणु
		mutex_unlock(&mt9v111->stream_mutex);
		वापस -EINVAL;
	पूर्ण

	mt9v111_calc_frame_rate(mt9v111, tpf);

	mt9v111->fps = fps;
	mt9v111->pending = true;

	mutex_unlock(&mt9v111->stream_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v111_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_frame_पूर्णांकerval *ival)
अणु
	काष्ठा mt9v111_dev *mt9v111 = sd_to_mt9v111(sd);
	काष्ठा v4l2_fract *tpf = &ival->पूर्णांकerval;

	mutex_lock(&mt9v111->stream_mutex);

	tpf->numerator = 1;
	tpf->denominator = mt9v111->fps;

	mutex_unlock(&mt9v111->stream_mutex);

	वापस 0;
पूर्ण

अटल काष्ठा v4l2_mbus_framefmt *__mt9v111_get_pad_क्रमmat(
					काष्ठा mt9v111_dev *mt9v111,
					काष्ठा v4l2_subdev_pad_config *cfg,
					अचिन्हित पूर्णांक pad,
					क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	चयन (which) अणु
	हाल V4L2_SUBDEV_FORMAT_TRY:
#अगर IS_ENABLED(CONFIG_VIDEO_V4L2_SUBDEV_API)
		वापस v4l2_subdev_get_try_क्रमmat(&mt9v111->sd, cfg, pad);
#अन्यथा
		वापस &cfg->try_fmt;
#पूर्ण_अगर
	हाल V4L2_SUBDEV_FORMAT_ACTIVE:
		वापस &mt9v111->fmt;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mt9v111_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad || code->index > ARRAY_SIZE(mt9v111_क्रमmats) - 1)
		वापस -EINVAL;

	code->code = mt9v111_क्रमmats[code->index].code;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v111_क्रमागत_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie)
अणु
	अचिन्हित पूर्णांक i;

	अगर (fie->pad || fie->index >= ARRAY_SIZE(mt9v111_frame_पूर्णांकervals))
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(mt9v111_frame_sizes); i++)
		अगर (fie->width == mt9v111_frame_sizes[i].width &&
		    fie->height == mt9v111_frame_sizes[i].height)
			अवरोध;

	अगर (i == ARRAY_SIZE(mt9v111_frame_sizes))
		वापस -EINVAL;

	fie->पूर्णांकerval.numerator = 1;
	fie->पूर्णांकerval.denominator = mt9v111_frame_पूर्णांकervals[fie->index];

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v111_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अगर (fse->pad || fse->index >= ARRAY_SIZE(mt9v111_frame_sizes))
		वापस -EINVAL;

	fse->min_width = mt9v111_frame_sizes[fse->index].width;
	fse->max_width = mt9v111_frame_sizes[fse->index].width;
	fse->min_height = mt9v111_frame_sizes[fse->index].height;
	fse->max_height = mt9v111_frame_sizes[fse->index].height;

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v111_get_क्रमmat(काष्ठा v4l2_subdev *subdev,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा mt9v111_dev *mt9v111 = sd_to_mt9v111(subdev);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	mutex_lock(&mt9v111->stream_mutex);
	क्रमmat->क्रमmat = *__mt9v111_get_pad_क्रमmat(mt9v111, cfg, क्रमmat->pad,
						   क्रमmat->which);
	mutex_unlock(&mt9v111->stream_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v111_set_क्रमmat(काष्ठा v4l2_subdev *subdev,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा mt9v111_dev *mt9v111 = sd_to_mt9v111(subdev);
	काष्ठा v4l2_mbus_framefmt new_fmt;
	काष्ठा v4l2_mbus_framefmt *__fmt;
	अचिन्हित पूर्णांक best_fit = ~0L;
	अचिन्हित पूर्णांक idx = 0;
	अचिन्हित पूर्णांक i;

	mutex_lock(&mt9v111->stream_mutex);
	अगर (mt9v111->streaming) अणु
		mutex_unlock(&mt9v111->stream_mutex);
		वापस -EBUSY;
	पूर्ण

	अगर (क्रमmat->pad) अणु
		mutex_unlock(&mt9v111->stream_mutex);
		वापस -EINVAL;
	पूर्ण

	/* Update mbus क्रमmat code and sizes. */
	क्रम (i = 0; i < ARRAY_SIZE(mt9v111_क्रमmats); i++) अणु
		अगर (क्रमmat->क्रमmat.code == mt9v111_क्रमmats[i].code) अणु
			new_fmt.code = mt9v111_क्रमmats[i].code;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(mt9v111_क्रमmats))
		new_fmt.code = mt9v111_क्रमmats[0].code;

	क्रम (i = 0; i < ARRAY_SIZE(mt9v111_frame_sizes); i++) अणु
		अचिन्हित पूर्णांक fit = असल(mt9v111_frame_sizes[i].width -
				       क्रमmat->क्रमmat.width) +
				   असल(mt9v111_frame_sizes[i].height -
				       क्रमmat->क्रमmat.height);
		अगर (fit < best_fit) अणु
			best_fit = fit;
			idx = i;

			अगर (fit == 0)
				अवरोध;
		पूर्ण
	पूर्ण
	new_fmt.width = mt9v111_frame_sizes[idx].width;
	new_fmt.height = mt9v111_frame_sizes[idx].height;

	/* Update the device (or pad) क्रमmat अगर it has changed. */
	__fmt = __mt9v111_get_pad_क्रमmat(mt9v111, cfg, क्रमmat->pad,
					 क्रमmat->which);

	/* Format hasn't changed, stop here. */
	अगर (__fmt->code == new_fmt.code &&
	    __fmt->width == new_fmt.width &&
	    __fmt->height == new_fmt.height)
		जाओ करोne;

	/* Update the क्रमmat and sizes, then  mark changes as pending. */
	__fmt->code = new_fmt.code;
	__fmt->width = new_fmt.width;
	__fmt->height = new_fmt.height;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		mt9v111->pending = true;

	dev_dbg(mt9v111->dev, "%s: mbus_code: %x - (%ux%u)\n",
		__func__, __fmt->code, __fmt->width, __fmt->height);

करोne:
	क्रमmat->क्रमmat = *__fmt;

	mutex_unlock(&mt9v111->stream_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक mt9v111_init_cfg(काष्ठा v4l2_subdev *subdev,
			    काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	cfg->try_fmt = mt9v111_def_fmt;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops mt9v111_core_ops = अणु
	.s_घातer		= mt9v111_s_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops mt9v111_video_ops = अणु
	.s_stream		= mt9v111_s_stream,
	.s_frame_पूर्णांकerval	= mt9v111_s_frame_पूर्णांकerval,
	.g_frame_पूर्णांकerval	= mt9v111_g_frame_पूर्णांकerval,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops mt9v111_pad_ops = अणु
	.init_cfg		= mt9v111_init_cfg,
	.क्रमागत_mbus_code		= mt9v111_क्रमागत_mbus_code,
	.क्रमागत_frame_size	= mt9v111_क्रमागत_frame_size,
	.क्रमागत_frame_पूर्णांकerval	= mt9v111_क्रमागत_frame_पूर्णांकerval,
	.get_fmt		= mt9v111_get_क्रमmat,
	.set_fmt		= mt9v111_set_क्रमmat,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops mt9v111_ops = अणु
	.core	= &mt9v111_core_ops,
	.video	= &mt9v111_video_ops,
	.pad	= &mt9v111_pad_ops,
पूर्ण;

#अगर IS_ENABLED(CONFIG_MEDIA_CONTROLLER)
अटल स्थिर काष्ठा media_entity_operations mt9v111_subdev_entity_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;
#पूर्ण_अगर

/* --- V4L2 ctrl --- */
अटल पूर्णांक mt9v111_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा mt9v111_dev *mt9v111 = container_of(ctrl->handler,
						   काष्ठा mt9v111_dev,
						   ctrls);
	पूर्णांक ret;

	mutex_lock(&mt9v111->pwr_mutex);
	/*
	 * If sensor is घातered करोwn, just cache new control values,
	 * no actual रेजिस्टर access.
	 */
	अगर (!mt9v111->pwr_count) अणु
		mt9v111->pending = true;
		mutex_unlock(&mt9v111->pwr_mutex);
		वापस 0;
	पूर्ण
	mutex_unlock(&mt9v111->pwr_mutex);

	/*
	 * Flickering control माला_लो disabled अगर both स्वतः exp and स्वतः awb
	 * are disabled too. If any of the two is enabled, enable it.
	 *
	 * Disabling flickering when ae and awb are off allows a more precise
	 * control of the programmed frame rate.
	 */
	अगर (mt9v111->स्वतः_exp->is_new || mt9v111->स्वतः_awb->is_new) अणु
		अगर (mt9v111->स्वतः_exp->val == V4L2_EXPOSURE_MANUAL &&
		    mt9v111->स्वतः_awb->val == V4L2_WHITE_BALANCE_MANUAL)
			ret = mt9v111_update(mt9v111->client, MT9V111_R01_IFP,
					     MT9V111_IFP_R08_OUTFMT_CTRL,
					     MT9V111_IFP_R08_OUTFMT_CTRL_FLICKER,
					     0);
		अन्यथा
			ret = mt9v111_update(mt9v111->client, MT9V111_R01_IFP,
					     MT9V111_IFP_R08_OUTFMT_CTRL,
					     MT9V111_IFP_R08_OUTFMT_CTRL_FLICKER,
					     1);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = -EINVAL;
	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		ret = mt9v111_update(mt9v111->client, MT9V111_R01_IFP,
				     MT9V111_IFP_R06_OPMODE_CTRL,
				     MT9V111_IFP_R06_OPMODE_CTRL_AWB_EN,
				     ctrl->val == V4L2_WHITE_BALANCE_AUTO ?
				     MT9V111_IFP_R06_OPMODE_CTRL_AWB_EN : 0);
		अवरोध;
	हाल V4L2_CID_EXPOSURE_AUTO:
		ret = mt9v111_update(mt9v111->client, MT9V111_R01_IFP,
				     MT9V111_IFP_R06_OPMODE_CTRL,
				     MT9V111_IFP_R06_OPMODE_CTRL_AE_EN,
				     ctrl->val == V4L2_EXPOSURE_AUTO ?
				     MT9V111_IFP_R06_OPMODE_CTRL_AE_EN : 0);
		अवरोध;
	हाल V4L2_CID_HBLANK:
		ret = mt9v111_update(mt9v111->client, MT9V111_R01_CORE,
				     MT9V111_CORE_R05_HBLANK,
				     MT9V111_CORE_R05_MAX_HBLANK,
				     mt9v111->hblank->val);
		अवरोध;
	हाल V4L2_CID_VBLANK:
		ret = mt9v111_update(mt9v111->client, MT9V111_R01_CORE,
				     MT9V111_CORE_R06_VBLANK,
				     MT9V111_CORE_R06_MAX_VBLANK,
				     mt9v111->vblank->val);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops mt9v111_ctrl_ops = अणु
	.s_ctrl = mt9v111_s_ctrl,
पूर्ण;

अटल पूर्णांक mt9v111_chip_probe(काष्ठा mt9v111_dev *mt9v111)
अणु
	पूर्णांक ret;
	u16 val;

	ret = __mt9v111_घातer_on(&mt9v111->sd);
	अगर (ret)
		वापस ret;

	ret = mt9v111_पढ़ो(mt9v111->client, MT9V111_R01_CORE,
			   MT9V111_CORE_RFF_CHIP_VER, &val);
	अगर (ret)
		जाओ घातer_off;

	अगर ((val >> 8) != MT9V111_CHIP_ID_HIGH &&
	    (val & 0xff) != MT9V111_CHIP_ID_LOW) अणु
		dev_err(mt9v111->dev,
			"Unable to identify MT9V111 chip: 0x%2x%2x\n",
			val >> 8, val & 0xff);
		ret = -EIO;
		जाओ घातer_off;
	पूर्ण

	dev_dbg(mt9v111->dev, "Chip identified: 0x%2x%2x\n",
		val >> 8, val & 0xff);

घातer_off:
	__mt9v111_घातer_off(&mt9v111->sd);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9v111_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा mt9v111_dev *mt9v111;
	काष्ठा v4l2_fract tpf;
	पूर्णांक ret;

	mt9v111 = devm_kzalloc(&client->dev, माप(*mt9v111), GFP_KERNEL);
	अगर (!mt9v111)
		वापस -ENOMEM;

	mt9v111->dev = &client->dev;
	mt9v111->client = client;

	mt9v111->clk = devm_clk_get(&client->dev, शून्य);
	अगर (IS_ERR(mt9v111->clk))
		वापस PTR_ERR(mt9v111->clk);

	mt9v111->sysclk = clk_get_rate(mt9v111->clk);
	अगर (mt9v111->sysclk > MT9V111_MAX_CLKIN)
		वापस -EINVAL;

	mt9v111->oe = devm_gpiod_get_optional(&client->dev, "enable",
					      GPIOD_OUT_LOW);
	अगर (IS_ERR(mt9v111->oe)) अणु
		dev_err(&client->dev, "Unable to get GPIO \"enable\": %ld\n",
			PTR_ERR(mt9v111->oe));
		वापस PTR_ERR(mt9v111->oe);
	पूर्ण

	mt9v111->standby = devm_gpiod_get_optional(&client->dev, "standby",
						   GPIOD_OUT_HIGH);
	अगर (IS_ERR(mt9v111->standby)) अणु
		dev_err(&client->dev, "Unable to get GPIO \"standby\": %ld\n",
			PTR_ERR(mt9v111->standby));
		वापस PTR_ERR(mt9v111->standby);
	पूर्ण

	mt9v111->reset = devm_gpiod_get_optional(&client->dev, "reset",
						 GPIOD_OUT_LOW);
	अगर (IS_ERR(mt9v111->reset)) अणु
		dev_err(&client->dev, "Unable to get GPIO \"reset\": %ld\n",
			PTR_ERR(mt9v111->reset));
		वापस PTR_ERR(mt9v111->reset);
	पूर्ण

	mutex_init(&mt9v111->pwr_mutex);
	mutex_init(&mt9v111->stream_mutex);

	v4l2_ctrl_handler_init(&mt9v111->ctrls, 5);

	mt9v111->स्वतः_awb = v4l2_ctrl_new_std(&mt9v111->ctrls,
					      &mt9v111_ctrl_ops,
					      V4L2_CID_AUTO_WHITE_BALANCE,
					      0, 1, 1,
					      V4L2_WHITE_BALANCE_AUTO);
	mt9v111->स्वतः_exp = v4l2_ctrl_new_std_menu(&mt9v111->ctrls,
						   &mt9v111_ctrl_ops,
						   V4L2_CID_EXPOSURE_AUTO,
						   V4L2_EXPOSURE_MANUAL,
						   0, V4L2_EXPOSURE_AUTO);
	mt9v111->hblank = v4l2_ctrl_new_std(&mt9v111->ctrls, &mt9v111_ctrl_ops,
					    V4L2_CID_HBLANK,
					    MT9V111_CORE_R05_MIN_HBLANK,
					    MT9V111_CORE_R05_MAX_HBLANK, 1,
					    MT9V111_CORE_R05_DEF_HBLANK);
	mt9v111->vblank = v4l2_ctrl_new_std(&mt9v111->ctrls, &mt9v111_ctrl_ops,
					    V4L2_CID_VBLANK,
					    MT9V111_CORE_R06_MIN_VBLANK,
					    MT9V111_CORE_R06_MAX_VBLANK, 1,
					    MT9V111_CORE_R06_DEF_VBLANK);

	/* PIXEL_RATE is fixed: just expose it to user space. */
	v4l2_ctrl_new_std(&mt9v111->ctrls, &mt9v111_ctrl_ops,
			  V4L2_CID_PIXEL_RATE, 0,
			  DIV_ROUND_CLOSEST(mt9v111->sysclk, 2), 1,
			  DIV_ROUND_CLOSEST(mt9v111->sysclk, 2));

	अगर (mt9v111->ctrls.error) अणु
		ret = mt9v111->ctrls.error;
		जाओ error_मुक्त_ctrls;
	पूर्ण
	mt9v111->sd.ctrl_handler = &mt9v111->ctrls;

	/* Start with शेष configuration: 640x480 UYVY. */
	mt9v111->fmt	= mt9v111_def_fmt;

	/* Re-calculate blankings क्रम 640x480@15fps. */
	mt9v111->fps		= 15;
	tpf.numerator		= 1;
	tpf.denominator		= mt9v111->fps;
	mt9v111_calc_frame_rate(mt9v111, &tpf);

	mt9v111->pwr_count	= 0;
	mt9v111->addr_space	= MT9V111_R01_IFP;
	mt9v111->pending	= true;

	v4l2_i2c_subdev_init(&mt9v111->sd, client, &mt9v111_ops);

#अगर IS_ENABLED(CONFIG_MEDIA_CONTROLLER)
	mt9v111->sd.flags	|= V4L2_SUBDEV_FL_HAS_DEVNODE;
	mt9v111->sd.entity.ops	= &mt9v111_subdev_entity_ops;
	mt9v111->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;

	mt9v111->pad.flags	= MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&mt9v111->sd.entity, 1, &mt9v111->pad);
	अगर (ret)
		जाओ error_मुक्त_entity;
#पूर्ण_अगर

	ret = mt9v111_chip_probe(mt9v111);
	अगर (ret)
		जाओ error_मुक्त_entity;

	ret = v4l2_async_रेजिस्टर_subdev(&mt9v111->sd);
	अगर (ret)
		जाओ error_मुक्त_entity;

	वापस 0;

error_मुक्त_entity:
#अगर IS_ENABLED(CONFIG_MEDIA_CONTROLLER)
	media_entity_cleanup(&mt9v111->sd.entity);
#पूर्ण_अगर

error_मुक्त_ctrls:
	v4l2_ctrl_handler_मुक्त(&mt9v111->ctrls);

	mutex_destroy(&mt9v111->pwr_mutex);
	mutex_destroy(&mt9v111->stream_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक mt9v111_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा mt9v111_dev *mt9v111 = sd_to_mt9v111(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);

#अगर IS_ENABLED(CONFIG_MEDIA_CONTROLLER)
	media_entity_cleanup(&sd->entity);
#पूर्ण_अगर

	v4l2_ctrl_handler_मुक्त(&mt9v111->ctrls);

	mutex_destroy(&mt9v111->pwr_mutex);
	mutex_destroy(&mt9v111->stream_mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mt9v111_of_match[] = अणु
	अणु .compatible = "aptina,mt9v111", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा i2c_driver mt9v111_driver = अणु
	.driver = अणु
		.name = "mt9v111",
		.of_match_table = mt9v111_of_match,
	पूर्ण,
	.probe_new	= mt9v111_probe,
	.हटाओ		= mt9v111_हटाओ,
पूर्ण;

module_i2c_driver(mt9v111_driver);

MODULE_DESCRIPTION("V4L2 sensor driver for Aptina MT9V111");
MODULE_AUTHOR("Jacopo Mondi <jacopo@jmondi.org>");
MODULE_LICENSE("GPL v2");
