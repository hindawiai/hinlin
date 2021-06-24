<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Samsung S5K6AAFX SXGA 1/6" 1.3M CMOS Image Sensor
 * with embedded SoC ISP.
 *
 * Copyright (C) 2011, Samsung Electronics Co., Ltd.
 * Sylwester Nawrocki <s.nawrocki@samsung.com>
 *
 * Based on a driver authored by Dongsoo Nathaniel Kim.
 * Copyright (C) 2009, Dongsoo Nathaniel Kim <करोngsoo45.kim@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/media.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/i2c/s5k6aa.h>

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

#घोषणा DRIVER_NAME			"S5K6AA"

/* The token to indicate array termination */
#घोषणा S5K6AA_TERM			0xffff
#घोषणा S5K6AA_OUT_WIDTH_DEF		640
#घोषणा S5K6AA_OUT_HEIGHT_DEF		480
#घोषणा S5K6AA_WIN_WIDTH_MAX		1280
#घोषणा S5K6AA_WIN_HEIGHT_MAX		1024
#घोषणा S5K6AA_WIN_WIDTH_MIN		8
#घोषणा S5K6AA_WIN_HEIGHT_MIN		8

/*
 * H/W रेजिस्टर Interface (0xD0000000 - 0xD0000FFF)
 */
#घोषणा AHB_MSB_ADDR_PTR		0xfcfc
#घोषणा GEN_REG_OFFSH			0xd000
#घोषणा REG_CMDWR_ADDRH			0x0028
#घोषणा REG_CMDWR_ADDRL			0x002a
#घोषणा REG_CMDRD_ADDRH			0x002c
#घोषणा REG_CMDRD_ADDRL			0x002e
#घोषणा REG_CMDBUF0_ADDR		0x0f12
#घोषणा REG_CMDBUF1_ADDR		0x0f10

/*
 * Host S/W Register पूर्णांकerface (0x70000000 - 0x70002000)
 * The value of the two most signअगरicant address bytes is 0x7000,
 * (HOST_SWIF_OFFS_H). The रेजिस्टर addresses below specअगरy 2 LSBs.
 */
#घोषणा HOST_SWIF_OFFSH			0x7000

/* Initialization parameters */
/* Master घड़ी frequency in KHz */
#घोषणा REG_I_INCLK_FREQ_L		0x01b8
#घोषणा REG_I_INCLK_FREQ_H		0x01ba
#घोषणा  MIN_MCLK_FREQ_KHZ		6000U
#घोषणा  MAX_MCLK_FREQ_KHZ		27000U
#घोषणा REG_I_USE_NPVI_CLOCKS		0x01c6
#घोषणा REG_I_USE_NMIPI_CLOCKS		0x01c8

/* Clock configurations, n = 0..2. REG_I_* frequency unit is 4 kHz. */
#घोषणा REG_I_OPCLK_4KHZ(n)		((n) * 6 + 0x01cc)
#घोषणा REG_I_MIN_OUTRATE_4KHZ(n)	((n) * 6 + 0x01ce)
#घोषणा REG_I_MAX_OUTRATE_4KHZ(n)	((n) * 6 + 0x01d0)
#घोषणा  SYS_PLL_OUT_FREQ		(48000000 / 4000)
#घोषणा  PCLK_FREQ_MIN			(24000000 / 4000)
#घोषणा  PCLK_FREQ_MAX			(48000000 / 4000)
#घोषणा REG_I_INIT_PARAMS_UPDATED	0x01e0
#घोषणा REG_I_ERROR_INFO		0x01e2

/* General purpose parameters */
#घोषणा REG_USER_BRIGHTNESS		0x01e4
#घोषणा REG_USER_CONTRAST		0x01e6
#घोषणा REG_USER_SATURATION		0x01e8
#घोषणा REG_USER_SHARPBLUR		0x01ea

#घोषणा REG_G_SPEC_EFFECTS		0x01ee
#घोषणा REG_G_ENABLE_PREV		0x01f0
#घोषणा REG_G_ENABLE_PREV_CHG		0x01f2
#घोषणा REG_G_NEW_CFG_SYNC		0x01f8
#घोषणा REG_G_PREVZOOM_IN_WIDTH		0x020a
#घोषणा REG_G_PREVZOOM_IN_HEIGHT	0x020c
#घोषणा REG_G_PREVZOOM_IN_XOFFS		0x020e
#घोषणा REG_G_PREVZOOM_IN_YOFFS		0x0210
#घोषणा REG_G_INPUTS_CHANGE_REQ		0x021a
#घोषणा REG_G_ACTIVE_PREV_CFG		0x021c
#घोषणा REG_G_PREV_CFG_CHG		0x021e
#घोषणा REG_G_PREV_OPEN_AFTER_CH	0x0220
#घोषणा REG_G_PREV_CFG_ERROR		0x0222

/* Preview control section. n = 0...4. */
#घोषणा PREG(n, x)			((n) * 0x26 + x)
#घोषणा REG_P_OUT_WIDTH(n)		PREG(n, 0x0242)
#घोषणा REG_P_OUT_HEIGHT(n)		PREG(n, 0x0244)
#घोषणा REG_P_FMT(n)			PREG(n, 0x0246)
#घोषणा REG_P_MAX_OUT_RATE(n)		PREG(n, 0x0248)
#घोषणा REG_P_MIN_OUT_RATE(n)		PREG(n, 0x024a)
#घोषणा REG_P_PVI_MASK(n)		PREG(n, 0x024c)
#घोषणा REG_P_CLK_INDEX(n)		PREG(n, 0x024e)
#घोषणा REG_P_FR_RATE_TYPE(n)		PREG(n, 0x0250)
#घोषणा  FR_RATE_DYNAMIC		0
#घोषणा  FR_RATE_FIXED			1
#घोषणा  FR_RATE_FIXED_ACCURATE		2
#घोषणा REG_P_FR_RATE_Q_TYPE(n)		PREG(n, 0x0252)
#घोषणा  FR_RATE_Q_BEST_FRRATE		1 /* Binning enabled */
#घोषणा  FR_RATE_Q_BEST_QUALITY		2 /* Binning disabled */
/* Frame period in 0.1 ms units */
#घोषणा REG_P_MAX_FR_TIME(n)		PREG(n, 0x0254)
#घोषणा REG_P_MIN_FR_TIME(n)		PREG(n, 0x0256)
/* Conversion to REG_P_[MAX/MIN]_FR_TIME value; __t: समय in us */
#घोषणा  US_TO_FR_TIME(__t)		((__t) / 100)
#घोषणा  S5K6AA_MIN_FR_TIME		33300  /* us */
#घोषणा  S5K6AA_MAX_FR_TIME		650000 /* us */
#घोषणा  S5K6AA_MAX_HIGHRES_FR_TIME	666    /* x100 us */
/* The below 5 रेजिस्टरs are क्रम "device correction" values */
#घोषणा REG_P_COLORTEMP(n)		PREG(n, 0x025e)
#घोषणा REG_P_PREV_MIRROR(n)		PREG(n, 0x0262)

/* Extended image property controls */
/* Exposure समय in 10 us units */
#घोषणा REG_SF_USR_EXPOSURE_L		0x03c6
#घोषणा REG_SF_USR_EXPOSURE_H		0x03c8
#घोषणा REG_SF_USR_EXPOSURE_CHG		0x03ca
#घोषणा REG_SF_USR_TOT_GAIN		0x03cc
#घोषणा REG_SF_USR_TOT_GAIN_CHG		0x03ce
#घोषणा REG_SF_RGAIN			0x03d0
#घोषणा REG_SF_RGAIN_CHG		0x03d2
#घोषणा REG_SF_GGAIN			0x03d4
#घोषणा REG_SF_GGAIN_CHG		0x03d6
#घोषणा REG_SF_BGAIN			0x03d8
#घोषणा REG_SF_BGAIN_CHG		0x03da
#घोषणा REG_SF_FLICKER_QUANT		0x03dc
#घोषणा REG_SF_FLICKER_QUANT_CHG	0x03de

/* Output पूर्णांकerface (parallel/MIPI) setup */
#घोषणा REG_OIF_EN_MIPI_LANES		0x03fa
#घोषणा REG_OIF_EN_PACKETS		0x03fc
#घोषणा REG_OIF_CFG_CHG			0x03fe

/* Auto-algorithms enable mask */
#घोषणा REG_DBG_AUTOALG_EN		0x0400
#घोषणा  AALG_ALL_EN_MASK		(1 << 0)
#घोषणा  AALG_AE_EN_MASK		(1 << 1)
#घोषणा  AALG_DIVLEI_EN_MASK		(1 << 2)
#घोषणा  AALG_WB_EN_MASK		(1 << 3)
#घोषणा  AALG_FLICKER_EN_MASK		(1 << 5)
#घोषणा  AALG_FIT_EN_MASK		(1 << 6)
#घोषणा  AALG_WRHW_EN_MASK		(1 << 7)

/* Firmware revision inक्रमmation */
#घोषणा REG_FW_APIVER			0x012e
#घोषणा  S5K6AAFX_FW_APIVER		0x0001
#घोषणा REG_FW_REVISION			0x0130

/* For now we use only one user configuration रेजिस्टर set */
#घोषणा S5K6AA_MAX_PRESETS		1

अटल स्थिर अक्षर * स्थिर s5k6aa_supply_names[] = अणु
	"vdd_core",	/* Digital core supply 1.5V (1.4V to 1.6V) */
	"vdda",		/* Analog घातer supply 2.8V (2.6V to 3.0V) */
	"vdd_reg",	/* Regulator input घातer 1.8V (1.7V to 1.9V)
			   or 2.8V (2.6V to 3.0) */
	"vddio",	/* I/O supply 1.8V (1.65V to 1.95V)
			   or 2.8V (2.5V to 3.1V) */
पूर्ण;
#घोषणा S5K6AA_NUM_SUPPLIES ARRAY_SIZE(s5k6aa_supply_names)

क्रमागत s5k6aa_gpio_id अणु
	STBY,
	RST,
	GPIO_NUM,
पूर्ण;

काष्ठा s5k6aa_regval अणु
	u16 addr;
	u16 val;
पूर्ण;

काष्ठा s5k6aa_pixfmt अणु
	u32 code;
	u32 colorspace;
	/* REG_P_FMT(x) रेजिस्टर value */
	u16 reg_p_fmt;
पूर्ण;

काष्ठा s5k6aa_preset अणु
	/* output pixel क्रमmat and resolution */
	काष्ठा v4l2_mbus_framefmt mbus_fmt;
	u8 clk_id;
	u8 index;
पूर्ण;

काष्ठा s5k6aa_ctrls अणु
	काष्ठा v4l2_ctrl_handler handler;
	/* Auto / manual white balance cluster */
	काष्ठा v4l2_ctrl *awb;
	काष्ठा v4l2_ctrl *gain_red;
	काष्ठा v4l2_ctrl *gain_blue;
	काष्ठा v4l2_ctrl *gain_green;
	/* Mirror cluster */
	काष्ठा v4l2_ctrl *hflip;
	काष्ठा v4l2_ctrl *vflip;
	/* Auto exposure / manual exposure and gain cluster */
	काष्ठा v4l2_ctrl *स्वतः_exp;
	काष्ठा v4l2_ctrl *exposure;
	काष्ठा v4l2_ctrl *gain;
पूर्ण;

काष्ठा s5k6aa_पूर्णांकerval अणु
	u16 reg_fr_समय;
	काष्ठा v4l2_fract पूर्णांकerval;
	/* Maximum rectangle क्रम the पूर्णांकerval */
	काष्ठा v4l2_frmsize_discrete size;
पूर्ण;

काष्ठा s5k6aa अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;

	क्रमागत v4l2_mbus_type bus_type;
	u8 mipi_lanes;

	पूर्णांक (*s_घातer)(पूर्णांक enable);
	काष्ठा regulator_bulk_data supplies[S5K6AA_NUM_SUPPLIES];
	काष्ठा s5k6aa_gpio gpio[GPIO_NUM];

	/* बाह्यal master घड़ी frequency */
	अचिन्हित दीर्घ mclk_frequency;
	/* ISP पूर्णांकernal master घड़ी frequency */
	u16 clk_fop;
	/* output pixel घड़ी frequency range */
	u16 pclk_fmin;
	u16 pclk_fmax;

	अचिन्हित पूर्णांक inv_hflip:1;
	अचिन्हित पूर्णांक inv_vflip:1;

	/* protects the काष्ठा members below */
	काष्ठा mutex lock;

	/* sensor matrix scan winकरोw */
	काष्ठा v4l2_rect ccd_rect;

	काष्ठा s5k6aa_ctrls ctrls;
	काष्ठा s5k6aa_preset presets[S5K6AA_MAX_PRESETS];
	काष्ठा s5k6aa_preset *preset;
	स्थिर काष्ठा s5k6aa_पूर्णांकerval *fiv;

	अचिन्हित पूर्णांक streaming:1;
	अचिन्हित पूर्णांक apply_cfg:1;
	अचिन्हित पूर्णांक apply_crop:1;
	अचिन्हित पूर्णांक घातer;
पूर्ण;

अटल काष्ठा s5k6aa_regval s5k6aa_analog_config[] = अणु
	/* Analog settings */
	अणु 0x112a, 0x0000 पूर्ण, अणु 0x1132, 0x0000 पूर्ण,
	अणु 0x113e, 0x0000 पूर्ण, अणु 0x115c, 0x0000 पूर्ण,
	अणु 0x1164, 0x0000 पूर्ण, अणु 0x1174, 0x0000 पूर्ण,
	अणु 0x1178, 0x0000 पूर्ण, अणु 0x077a, 0x0000 पूर्ण,
	अणु 0x077c, 0x0000 पूर्ण, अणु 0x077e, 0x0000 पूर्ण,
	अणु 0x0780, 0x0000 पूर्ण, अणु 0x0782, 0x0000 पूर्ण,
	अणु 0x0784, 0x0000 पूर्ण, अणु 0x0786, 0x0000 पूर्ण,
	अणु 0x0788, 0x0000 पूर्ण, अणु 0x07a2, 0x0000 पूर्ण,
	अणु 0x07a4, 0x0000 पूर्ण, अणु 0x07a6, 0x0000 पूर्ण,
	अणु 0x07a8, 0x0000 पूर्ण, अणु 0x07b6, 0x0000 पूर्ण,
	अणु 0x07b8, 0x0002 पूर्ण, अणु 0x07ba, 0x0004 पूर्ण,
	अणु 0x07bc, 0x0004 पूर्ण, अणु 0x07be, 0x0005 पूर्ण,
	अणु 0x07c0, 0x0005 पूर्ण, अणु S5K6AA_TERM, 0 पूर्ण,
पूर्ण;

/* TODO: Add RGB888 and Bayer क्रमmat */
अटल स्थिर काष्ठा s5k6aa_pixfmt s5k6aa_क्रमmats[] = अणु
	अणु MEDIA_BUS_FMT_YUYV8_2X8,	V4L2_COLORSPACE_JPEG,	5 पूर्ण,
	/* range 16-240 */
	अणु MEDIA_BUS_FMT_YUYV8_2X8,	V4L2_COLORSPACE_REC709,	6 पूर्ण,
	अणु MEDIA_BUS_FMT_RGB565_2X8_BE,	V4L2_COLORSPACE_JPEG,	0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा s5k6aa_पूर्णांकerval s5k6aa_पूर्णांकervals[] = अणु
	अणु 1000, अणु10000, 1000000पूर्ण, अणु1280, 1024पूर्ण पूर्ण, /* 10 fps */
	अणु 666,  अणु15000, 1000000पूर्ण, अणु1280, 1024पूर्ण पूर्ण, /* 15 fps */
	अणु 500,  अणु20000, 1000000पूर्ण, अणु1280, 720पूर्ण पूर्ण,  /* 20 fps */
	अणु 400,  अणु25000, 1000000पूर्ण, अणु640, 480पूर्ण पूर्ण,   /* 25 fps */
	अणु 333,  अणु33300, 1000000पूर्ण, अणु640, 480पूर्ण पूर्ण,   /* 30 fps */
पूर्ण;

#घोषणा S5K6AA_INTERVAL_DEF_INDEX 1 /* 15 fps */

अटल अंतरभूत काष्ठा v4l2_subdev *ctrl_to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा s5k6aa, ctrls.handler)->sd;
पूर्ण

अटल अंतरभूत काष्ठा s5k6aa *to_s5k6aa(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा s5k6aa, sd);
पूर्ण

/* Set initial values क्रम all preview presets */
अटल व्योम s5k6aa_presets_data_init(काष्ठा s5k6aa *s5k6aa)
अणु
	काष्ठा s5k6aa_preset *preset = &s5k6aa->presets[0];
	पूर्णांक i;

	क्रम (i = 0; i < S5K6AA_MAX_PRESETS; i++) अणु
		preset->mbus_fmt.width	= S5K6AA_OUT_WIDTH_DEF;
		preset->mbus_fmt.height	= S5K6AA_OUT_HEIGHT_DEF;
		preset->mbus_fmt.code	= s5k6aa_क्रमmats[0].code;
		preset->index		= i;
		preset->clk_id		= 0;
		preset++;
	पूर्ण

	s5k6aa->fiv = &s5k6aa_पूर्णांकervals[S5K6AA_INTERVAL_DEF_INDEX];
	s5k6aa->preset = &s5k6aa->presets[0];
पूर्ण

अटल पूर्णांक s5k6aa_i2c_पढ़ो(काष्ठा i2c_client *client, u16 addr, u16 *val)
अणु
	u8 wbuf[2] = अणुaddr >> 8, addr & 0xFFपूर्ण;
	काष्ठा i2c_msg msg[2];
	u8 rbuf[2];
	पूर्णांक ret;

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].len = 2;
	msg[0].buf = wbuf;

	msg[1].addr = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = 2;
	msg[1].buf = rbuf;

	ret = i2c_transfer(client->adapter, msg, 2);
	*val = be16_to_cpu(*((__be16 *)rbuf));

	v4l2_dbg(3, debug, client, "i2c_read: 0x%04X : 0x%04x\n", addr, *val);

	वापस ret == 2 ? 0 : ret;
पूर्ण

अटल पूर्णांक s5k6aa_i2c_ग_लिखो(काष्ठा i2c_client *client, u16 addr, u16 val)
अणु
	u8 buf[4] = अणुaddr >> 8, addr & 0xFF, val >> 8, val & 0xFFपूर्ण;

	पूर्णांक ret = i2c_master_send(client, buf, 4);
	v4l2_dbg(3, debug, client, "i2c_write: 0x%04X : 0x%04x\n", addr, val);

	वापस ret == 4 ? 0 : ret;
पूर्ण

/* The command रेजिस्टर ग_लिखो, assumes Command_Wr_addH = 0x7000. */
अटल पूर्णांक s5k6aa_ग_लिखो(काष्ठा i2c_client *c, u16 addr, u16 val)
अणु
	पूर्णांक ret = s5k6aa_i2c_ग_लिखो(c, REG_CMDWR_ADDRL, addr);
	अगर (ret)
		वापस ret;
	वापस s5k6aa_i2c_ग_लिखो(c, REG_CMDBUF0_ADDR, val);
पूर्ण

/* The command रेजिस्टर पढ़ो, assumes Command_Rd_addH = 0x7000. */
अटल पूर्णांक s5k6aa_पढ़ो(काष्ठा i2c_client *client, u16 addr, u16 *val)
अणु
	पूर्णांक ret = s5k6aa_i2c_ग_लिखो(client, REG_CMDRD_ADDRL, addr);
	अगर (ret)
		वापस ret;
	वापस s5k6aa_i2c_पढ़ो(client, REG_CMDBUF0_ADDR, val);
पूर्ण

अटल पूर्णांक s5k6aa_ग_लिखो_array(काष्ठा v4l2_subdev *sd,
			      स्थिर काष्ठा s5k6aa_regval *msg)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	u16 addr_incr = 0;
	पूर्णांक ret = 0;

	जबतक (msg->addr != S5K6AA_TERM) अणु
		अगर (addr_incr != 2)
			ret = s5k6aa_i2c_ग_लिखो(client, REG_CMDWR_ADDRL,
					       msg->addr);
		अगर (ret)
			अवरोध;
		ret = s5k6aa_i2c_ग_लिखो(client, REG_CMDBUF0_ADDR, msg->val);
		अगर (ret)
			अवरोध;
		/* Assume that msg->addr is always less than 0xfffc */
		addr_incr = (msg + 1)->addr - msg->addr;
		msg++;
	पूर्ण

	वापस ret;
पूर्ण

/* Configure the AHB high address bytes क्रम GTG रेजिस्टरs access */
अटल पूर्णांक s5k6aa_set_ahb_address(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret = s5k6aa_i2c_ग_लिखो(client, AHB_MSB_ADDR_PTR, GEN_REG_OFFSH);
	अगर (ret)
		वापस ret;
	ret = s5k6aa_i2c_ग_लिखो(client, REG_CMDRD_ADDRH, HOST_SWIF_OFFSH);
	अगर (ret)
		वापस ret;
	वापस s5k6aa_i2c_ग_लिखो(client, REG_CMDWR_ADDRH, HOST_SWIF_OFFSH);
पूर्ण

/**
 * s5k6aa_configure_pixel_घड़ीs - apply ISP मुख्य घड़ी/PLL configuration
 * @s5k6aa: poपूर्णांकer to &काष्ठा s5k6aa describing the device
 *
 * Configure the पूर्णांकernal ISP PLL क्रम the required output frequency.
 * Locking: called with s5k6aa.lock mutex held.
 */
अटल पूर्णांक s5k6aa_configure_pixel_घड़ीs(काष्ठा s5k6aa *s5k6aa)
अणु
	काष्ठा i2c_client *c = v4l2_get_subdevdata(&s5k6aa->sd);
	अचिन्हित दीर्घ fmclk = s5k6aa->mclk_frequency / 1000;
	u16 status;
	पूर्णांक ret;

	अगर (WARN(fmclk < MIN_MCLK_FREQ_KHZ || fmclk > MAX_MCLK_FREQ_KHZ,
		 "Invalid clock frequency: %ld\n", fmclk))
		वापस -EINVAL;

	s5k6aa->pclk_fmin = PCLK_FREQ_MIN;
	s5k6aa->pclk_fmax = PCLK_FREQ_MAX;
	s5k6aa->clk_fop = SYS_PLL_OUT_FREQ;

	/* External input घड़ी frequency in kHz */
	ret = s5k6aa_ग_लिखो(c, REG_I_INCLK_FREQ_H, fmclk >> 16);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(c, REG_I_INCLK_FREQ_L, fmclk & 0xFFFF);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(c, REG_I_USE_NPVI_CLOCKS, 1);
	/* Internal PLL frequency */
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(c, REG_I_OPCLK_4KHZ(0), s5k6aa->clk_fop);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(c, REG_I_MIN_OUTRATE_4KHZ(0),
				   s5k6aa->pclk_fmin);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(c, REG_I_MAX_OUTRATE_4KHZ(0),
				   s5k6aa->pclk_fmax);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(c, REG_I_INIT_PARAMS_UPDATED, 1);
	अगर (!ret)
		ret = s5k6aa_पढ़ो(c, REG_I_ERROR_INFO, &status);

	वापस ret ? ret : (status ? -EINVAL : 0);
पूर्ण

/* Set horizontal and vertical image flipping */
अटल पूर्णांक s5k6aa_set_mirror(काष्ठा s5k6aa *s5k6aa, पूर्णांक horiz_flip)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&s5k6aa->sd);
	पूर्णांक index = s5k6aa->preset->index;

	अचिन्हित पूर्णांक vflip = s5k6aa->ctrls.vflip->val ^ s5k6aa->inv_vflip;
	अचिन्हित पूर्णांक flip = (horiz_flip ^ s5k6aa->inv_hflip) | (vflip << 1);

	वापस s5k6aa_ग_लिखो(client, REG_P_PREV_MIRROR(index), flip);
पूर्ण

/* Configure स्वतः/manual white balance and R/G/B gains */
अटल पूर्णांक s5k6aa_set_awb(काष्ठा s5k6aa *s5k6aa, पूर्णांक awb)
अणु
	काष्ठा i2c_client *c = v4l2_get_subdevdata(&s5k6aa->sd);
	काष्ठा s5k6aa_ctrls *ctrls = &s5k6aa->ctrls;
	u16 reg;

	पूर्णांक ret = s5k6aa_पढ़ो(c, REG_DBG_AUTOALG_EN, &reg);

	अगर (!ret && !awb) अणु
		ret = s5k6aa_ग_लिखो(c, REG_SF_RGAIN, ctrls->gain_red->val);
		अगर (!ret)
			ret = s5k6aa_ग_लिखो(c, REG_SF_RGAIN_CHG, 1);
		अगर (ret)
			वापस ret;

		ret = s5k6aa_ग_लिखो(c, REG_SF_GGAIN, ctrls->gain_green->val);
		अगर (!ret)
			ret = s5k6aa_ग_लिखो(c, REG_SF_GGAIN_CHG, 1);
		अगर (ret)
			वापस ret;

		ret = s5k6aa_ग_लिखो(c, REG_SF_BGAIN, ctrls->gain_blue->val);
		अगर (!ret)
			ret = s5k6aa_ग_लिखो(c, REG_SF_BGAIN_CHG, 1);
	पूर्ण
	अगर (!ret) अणु
		reg = awb ? reg | AALG_WB_EN_MASK : reg & ~AALG_WB_EN_MASK;
		ret = s5k6aa_ग_लिखो(c, REG_DBG_AUTOALG_EN, reg);
	पूर्ण

	वापस ret;
पूर्ण

/* Program FW with exposure समय, 'exposure' in us units */
अटल पूर्णांक s5k6aa_set_user_exposure(काष्ठा i2c_client *client, पूर्णांक exposure)
अणु
	अचिन्हित पूर्णांक समय = exposure / 10;

	पूर्णांक ret = s5k6aa_ग_लिखो(client, REG_SF_USR_EXPOSURE_L, समय & 0xffff);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(client, REG_SF_USR_EXPOSURE_H, समय >> 16);
	अगर (ret)
		वापस ret;
	वापस s5k6aa_ग_लिखो(client, REG_SF_USR_EXPOSURE_CHG, 1);
पूर्ण

अटल पूर्णांक s5k6aa_set_user_gain(काष्ठा i2c_client *client, पूर्णांक gain)
अणु
	पूर्णांक ret = s5k6aa_ग_लिखो(client, REG_SF_USR_TOT_GAIN, gain);
	अगर (ret)
		वापस ret;
	वापस s5k6aa_ग_लिखो(client, REG_SF_USR_TOT_GAIN_CHG, 1);
पूर्ण

/* Set स्वतः/manual exposure and total gain */
अटल पूर्णांक s5k6aa_set_स्वतः_exposure(काष्ठा s5k6aa *s5k6aa, पूर्णांक value)
अणु
	काष्ठा i2c_client *c = v4l2_get_subdevdata(&s5k6aa->sd);
	अचिन्हित पूर्णांक exp_समय = s5k6aa->ctrls.exposure->val;
	u16 स्वतः_alg;

	पूर्णांक ret = s5k6aa_पढ़ो(c, REG_DBG_AUTOALG_EN, &स्वतः_alg);
	अगर (ret)
		वापस ret;

	v4l2_dbg(1, debug, c, "man_exp: %d, auto_exp: %d, a_alg: 0x%x\n",
		 exp_समय, value, स्वतः_alg);

	अगर (value == V4L2_EXPOSURE_AUTO) अणु
		स्वतः_alg |= AALG_AE_EN_MASK | AALG_DIVLEI_EN_MASK;
	पूर्ण अन्यथा अणु
		ret = s5k6aa_set_user_exposure(c, exp_समय);
		अगर (ret)
			वापस ret;
		ret = s5k6aa_set_user_gain(c, s5k6aa->ctrls.gain->val);
		अगर (ret)
			वापस ret;
		स्वतः_alg &= ~(AALG_AE_EN_MASK | AALG_DIVLEI_EN_MASK);
	पूर्ण

	वापस s5k6aa_ग_लिखो(c, REG_DBG_AUTOALG_EN, स्वतः_alg);
पूर्ण

अटल पूर्णांक s5k6aa_set_anti_flicker(काष्ठा s5k6aa *s5k6aa, पूर्णांक value)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&s5k6aa->sd);
	u16 स्वतः_alg;
	पूर्णांक ret;

	ret = s5k6aa_पढ़ो(client, REG_DBG_AUTOALG_EN, &स्वतः_alg);
	अगर (ret)
		वापस ret;

	अगर (value == V4L2_CID_POWER_LINE_FREQUENCY_AUTO) अणु
		स्वतः_alg |= AALG_FLICKER_EN_MASK;
	पूर्ण अन्यथा अणु
		स्वतः_alg &= ~AALG_FLICKER_EN_MASK;
		/* The V4L2_CID_LINE_FREQUENCY control values match
		 * the रेजिस्टर values */
		ret = s5k6aa_ग_लिखो(client, REG_SF_FLICKER_QUANT, value);
		अगर (ret)
			वापस ret;
		ret = s5k6aa_ग_लिखो(client, REG_SF_FLICKER_QUANT_CHG, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस s5k6aa_ग_लिखो(client, REG_DBG_AUTOALG_EN, स्वतः_alg);
पूर्ण

अटल पूर्णांक s5k6aa_set_colorfx(काष्ठा s5k6aa *s5k6aa, पूर्णांक val)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&s5k6aa->sd);
	अटल स्थिर काष्ठा v4l2_control colorfx[] = अणु
		अणु V4L2_COLORFX_NONE,	 0 पूर्ण,
		अणु V4L2_COLORFX_BW,	 1 पूर्ण,
		अणु V4L2_COLORFX_NEGATIVE, 2 पूर्ण,
		अणु V4L2_COLORFX_SEPIA,	 3 पूर्ण,
		अणु V4L2_COLORFX_SKY_BLUE, 4 पूर्ण,
		अणु V4L2_COLORFX_SKETCH,	 5 पूर्ण,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(colorfx); i++) अणु
		अगर (colorfx[i].id == val)
			वापस s5k6aa_ग_लिखो(client, REG_G_SPEC_EFFECTS,
					    colorfx[i].value);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक s5k6aa_preview_config_status(काष्ठा i2c_client *client)
अणु
	u16 error = 0;
	पूर्णांक ret = s5k6aa_पढ़ो(client, REG_G_PREV_CFG_ERROR, &error);

	v4l2_dbg(1, debug, client, "error: 0x%x (%d)\n", error, ret);
	वापस ret ? ret : (error ? -EINVAL : 0);
पूर्ण

अटल पूर्णांक s5k6aa_get_pixfmt_index(काष्ठा s5k6aa *s5k6aa,
				   काष्ठा v4l2_mbus_framefmt *mf)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(s5k6aa_क्रमmats); i++)
		अगर (mf->colorspace == s5k6aa_क्रमmats[i].colorspace &&
		    mf->code == s5k6aa_क्रमmats[i].code)
			वापस i;
	वापस 0;
पूर्ण

अटल पूर्णांक s5k6aa_set_output_framefmt(काष्ठा s5k6aa *s5k6aa,
				      काष्ठा s5k6aa_preset *preset)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&s5k6aa->sd);
	पूर्णांक fmt_index = s5k6aa_get_pixfmt_index(s5k6aa, &preset->mbus_fmt);
	पूर्णांक ret;

	ret = s5k6aa_ग_लिखो(client, REG_P_OUT_WIDTH(preset->index),
			   preset->mbus_fmt.width);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(client, REG_P_OUT_HEIGHT(preset->index),
				   preset->mbus_fmt.height);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(client, REG_P_FMT(preset->index),
				   s5k6aa_क्रमmats[fmt_index].reg_p_fmt);
	वापस ret;
पूर्ण

अटल पूर्णांक s5k6aa_set_input_params(काष्ठा s5k6aa *s5k6aa)
अणु
	काष्ठा i2c_client *c = v4l2_get_subdevdata(&s5k6aa->sd);
	काष्ठा v4l2_rect *r = &s5k6aa->ccd_rect;
	पूर्णांक ret;

	ret = s5k6aa_ग_लिखो(c, REG_G_PREVZOOM_IN_WIDTH, r->width);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(c, REG_G_PREVZOOM_IN_HEIGHT, r->height);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(c, REG_G_PREVZOOM_IN_XOFFS, r->left);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(c, REG_G_PREVZOOM_IN_YOFFS, r->top);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(c, REG_G_INPUTS_CHANGE_REQ, 1);
	अगर (!ret)
		s5k6aa->apply_crop = 0;

	वापस ret;
पूर्ण

/**
 * s5k6aa_configure_video_bus - configure the video output पूर्णांकerface
 * @s5k6aa: poपूर्णांकer to &काष्ठा s5k6aa describing the device
 * @bus_type: video bus type: parallel or MIPI-CSI
 * @nlanes: number of MIPI lanes to be used (MIPI-CSI only)
 *
 * Note: Only parallel bus operation has been tested.
 */
अटल पूर्णांक s5k6aa_configure_video_bus(काष्ठा s5k6aa *s5k6aa,
				      क्रमागत v4l2_mbus_type bus_type, पूर्णांक nlanes)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&s5k6aa->sd);
	u16 cfg = 0;
	पूर्णांक ret;

	/*
	 * TODO: The sensor is supposed to support BT.601 and BT.656
	 * but there is nothing indicating how to चयन between both
	 * in the datasheet. For now शेष BT.601 पूर्णांकerface is assumed.
	 */
	अगर (bus_type == V4L2_MBUS_CSI2_DPHY)
		cfg = nlanes;
	अन्यथा अगर (bus_type != V4L2_MBUS_PARALLEL)
		वापस -EINVAL;

	ret = s5k6aa_ग_लिखो(client, REG_OIF_EN_MIPI_LANES, cfg);
	अगर (ret)
		वापस ret;
	वापस s5k6aa_ग_लिखो(client, REG_OIF_CFG_CHG, 1);
पूर्ण

/* This function should be called when चयनing to new user configuration set*/
अटल पूर्णांक s5k6aa_new_config_sync(काष्ठा i2c_client *client, पूर्णांक समयout,
				  पूर्णांक cid)
अणु
	अचिन्हित दीर्घ end = jअगरfies + msecs_to_jअगरfies(समयout);
	u16 reg = 1;
	पूर्णांक ret;

	ret = s5k6aa_ग_लिखो(client, REG_G_ACTIVE_PREV_CFG, cid);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(client, REG_G_PREV_CFG_CHG, 1);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(client, REG_G_NEW_CFG_SYNC, 1);
	अगर (समयout == 0)
		वापस ret;

	जबतक (ret >= 0 && समय_is_after_jअगरfies(end)) अणु
		ret = s5k6aa_पढ़ो(client, REG_G_NEW_CFG_SYNC, &reg);
		अगर (!reg)
			वापस 0;
		usleep_range(1000, 5000);
	पूर्ण
	वापस ret ? ret : -ETIMEDOUT;
पूर्ण

/**
 * s5k6aa_set_prev_config - ग_लिखो user preview रेजिस्टर set
 * @s5k6aa: poपूर्णांकer to &काष्ठा s5k6aa describing the device
 * @preset: s5kaa preset to be applied
 *
 * Configure output resolution and color क्रमmat, pixel घड़ी
 * frequency range, device frame rate type and frame period range.
 */
अटल पूर्णांक s5k6aa_set_prev_config(काष्ठा s5k6aa *s5k6aa,
				  काष्ठा s5k6aa_preset *preset)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&s5k6aa->sd);
	पूर्णांक idx = preset->index;
	u16 frame_rate_q;
	पूर्णांक ret;

	अगर (s5k6aa->fiv->reg_fr_समय >= S5K6AA_MAX_HIGHRES_FR_TIME)
		frame_rate_q = FR_RATE_Q_BEST_FRRATE;
	अन्यथा
		frame_rate_q = FR_RATE_Q_BEST_QUALITY;

	ret = s5k6aa_set_output_framefmt(s5k6aa, preset);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(client, REG_P_MAX_OUT_RATE(idx),
				   s5k6aa->pclk_fmax);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(client, REG_P_MIN_OUT_RATE(idx),
				   s5k6aa->pclk_fmin);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(client, REG_P_CLK_INDEX(idx),
				   preset->clk_id);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(client, REG_P_FR_RATE_TYPE(idx),
				   FR_RATE_DYNAMIC);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(client, REG_P_FR_RATE_Q_TYPE(idx),
				   frame_rate_q);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(client, REG_P_MAX_FR_TIME(idx),
				   s5k6aa->fiv->reg_fr_समय + 33);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(client, REG_P_MIN_FR_TIME(idx),
				   s5k6aa->fiv->reg_fr_समय - 33);
	अगर (!ret)
		ret = s5k6aa_new_config_sync(client, 250, idx);
	अगर (!ret)
		ret = s5k6aa_preview_config_status(client);
	अगर (!ret)
		s5k6aa->apply_cfg = 0;

	v4l2_dbg(1, debug, client, "Frame interval: %d +/- 3.3ms. (%d)\n",
		 s5k6aa->fiv->reg_fr_समय, ret);
	वापस ret;
पूर्ण

/**
 * s5k6aa_initialize_isp - basic ISP MCU initialization
 * @sd: poपूर्णांकer to V4L2 sub-device descriptor
 *
 * Configure AHB addresses क्रम रेजिस्टरs पढ़ो/ग_लिखो; configure PLLs क्रम
 * required output pixel घड़ी. The ISP घातer supply needs to be alपढ़ोy
 * enabled, with an optional H/W reset.
 * Locking: called with s5k6aa.lock mutex held.
 */
अटल पूर्णांक s5k6aa_initialize_isp(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा s5k6aa *s5k6aa = to_s5k6aa(sd);
	पूर्णांक ret;

	s5k6aa->apply_crop = 1;
	s5k6aa->apply_cfg = 1;
	msleep(100);

	ret = s5k6aa_set_ahb_address(client);
	अगर (ret)
		वापस ret;
	ret = s5k6aa_configure_video_bus(s5k6aa, s5k6aa->bus_type,
					 s5k6aa->mipi_lanes);
	अगर (ret)
		वापस ret;
	ret = s5k6aa_ग_लिखो_array(sd, s5k6aa_analog_config);
	अगर (ret)
		वापस ret;
	msleep(20);

	वापस s5k6aa_configure_pixel_घड़ीs(s5k6aa);
पूर्ण

अटल पूर्णांक s5k6aa_gpio_set_value(काष्ठा s5k6aa *priv, पूर्णांक id, u32 val)
अणु
	अगर (!gpio_is_valid(priv->gpio[id].gpio))
		वापस 0;
	gpio_set_value(priv->gpio[id].gpio, !!val);
	वापस 1;
पूर्ण

अटल पूर्णांक s5k6aa_gpio_निश्चित(काष्ठा s5k6aa *priv, पूर्णांक id)
अणु
	वापस s5k6aa_gpio_set_value(priv, id, priv->gpio[id].level);
पूर्ण

अटल पूर्णांक s5k6aa_gpio_deनिश्चित(काष्ठा s5k6aa *priv, पूर्णांक id)
अणु
	वापस s5k6aa_gpio_set_value(priv, id, !priv->gpio[id].level);
पूर्ण

अटल पूर्णांक __s5k6aa_घातer_on(काष्ठा s5k6aa *s5k6aa)
अणु
	पूर्णांक ret;

	ret = regulator_bulk_enable(S5K6AA_NUM_SUPPLIES, s5k6aa->supplies);
	अगर (ret)
		वापस ret;
	अगर (s5k6aa_gpio_deनिश्चित(s5k6aa, STBY))
		usleep_range(150, 200);

	अगर (s5k6aa->s_घातer)
		ret = s5k6aa->s_घातer(1);
	usleep_range(4000, 5000);

	अगर (s5k6aa_gpio_deनिश्चित(s5k6aa, RST))
		msleep(20);

	वापस ret;
पूर्ण

अटल पूर्णांक __s5k6aa_घातer_off(काष्ठा s5k6aa *s5k6aa)
अणु
	पूर्णांक ret;

	अगर (s5k6aa_gpio_निश्चित(s5k6aa, RST))
		usleep_range(100, 150);

	अगर (s5k6aa->s_घातer) अणु
		ret = s5k6aa->s_घातer(0);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (s5k6aa_gpio_निश्चित(s5k6aa, STBY))
		usleep_range(50, 100);
	s5k6aa->streaming = 0;

	वापस regulator_bulk_disable(S5K6AA_NUM_SUPPLIES, s5k6aa->supplies);
पूर्ण

/*
 * V4L2 subdev core and video operations
 */
अटल पूर्णांक s5k6aa_set_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा s5k6aa *s5k6aa = to_s5k6aa(sd);
	पूर्णांक ret = 0;

	mutex_lock(&s5k6aa->lock);

	अगर (s5k6aa->घातer == !on) अणु
		अगर (on) अणु
			ret = __s5k6aa_घातer_on(s5k6aa);
			अगर (!ret)
				ret = s5k6aa_initialize_isp(sd);
		पूर्ण अन्यथा अणु
			ret = __s5k6aa_घातer_off(s5k6aa);
		पूर्ण

		अगर (!ret)
			s5k6aa->घातer += on ? 1 : -1;
	पूर्ण

	mutex_unlock(&s5k6aa->lock);

	अगर (!on || ret || s5k6aa->घातer != 1)
		वापस ret;

	वापस v4l2_ctrl_handler_setup(sd->ctrl_handler);
पूर्ण

अटल पूर्णांक __s5k6aa_stream(काष्ठा s5k6aa *s5k6aa, पूर्णांक enable)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&s5k6aa->sd);
	पूर्णांक ret = 0;

	ret = s5k6aa_ग_लिखो(client, REG_G_ENABLE_PREV, enable);
	अगर (!ret)
		ret = s5k6aa_ग_लिखो(client, REG_G_ENABLE_PREV_CHG, 1);
	अगर (!ret)
		s5k6aa->streaming = enable;

	वापस ret;
पूर्ण

अटल पूर्णांक s5k6aa_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा s5k6aa *s5k6aa = to_s5k6aa(sd);
	पूर्णांक ret = 0;

	mutex_lock(&s5k6aa->lock);

	अगर (s5k6aa->streaming == !on) अणु
		अगर (!ret && s5k6aa->apply_cfg)
			ret = s5k6aa_set_prev_config(s5k6aa, s5k6aa->preset);
		अगर (s5k6aa->apply_crop)
			ret = s5k6aa_set_input_params(s5k6aa);
		अगर (!ret)
			ret = __s5k6aa_stream(s5k6aa, !!on);
	पूर्ण
	mutex_unlock(&s5k6aa->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक s5k6aa_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा s5k6aa *s5k6aa = to_s5k6aa(sd);

	mutex_lock(&s5k6aa->lock);
	fi->पूर्णांकerval = s5k6aa->fiv->पूर्णांकerval;
	mutex_unlock(&s5k6aa->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक __s5k6aa_set_frame_पूर्णांकerval(काष्ठा s5k6aa *s5k6aa,
				       काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा v4l2_mbus_framefmt *mbus_fmt = &s5k6aa->preset->mbus_fmt;
	स्थिर काष्ठा s5k6aa_पूर्णांकerval *fiv = &s5k6aa_पूर्णांकervals[0];
	अचिन्हित पूर्णांक err, min_err = अच_पूर्णांक_उच्च;
	अचिन्हित पूर्णांक i, fr_समय;

	अगर (fi->पूर्णांकerval.denominator == 0)
		वापस -EINVAL;

	fr_समय = fi->पूर्णांकerval.numerator * 10000 / fi->पूर्णांकerval.denominator;

	क्रम (i = 0; i < ARRAY_SIZE(s5k6aa_पूर्णांकervals); i++) अणु
		स्थिर काष्ठा s5k6aa_पूर्णांकerval *iv = &s5k6aa_पूर्णांकervals[i];

		अगर (mbus_fmt->width > iv->size.width ||
		    mbus_fmt->height > iv->size.height)
			जारी;

		err = असल(iv->reg_fr_समय - fr_समय);
		अगर (err < min_err) अणु
			fiv = iv;
			min_err = err;
		पूर्ण
	पूर्ण
	s5k6aa->fiv = fiv;

	v4l2_dbg(1, debug, &s5k6aa->sd, "Changed frame interval to %d us\n",
		 fiv->reg_fr_समय * 100);
	वापस 0;
पूर्ण

अटल पूर्णांक s5k6aa_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा s5k6aa *s5k6aa = to_s5k6aa(sd);
	पूर्णांक ret;

	v4l2_dbg(1, debug, sd, "Setting %d/%d frame interval\n",
		 fi->पूर्णांकerval.numerator, fi->पूर्णांकerval.denominator);

	mutex_lock(&s5k6aa->lock);
	ret = __s5k6aa_set_frame_पूर्णांकerval(s5k6aa, fi);
	s5k6aa->apply_cfg = 1;

	mutex_unlock(&s5k6aa->lock);
	वापस ret;
पूर्ण

/*
 * V4L2 subdev pad level and video operations
 */
अटल पूर्णांक s5k6aa_क्रमागत_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie)
अणु
	काष्ठा s5k6aa *s5k6aa = to_s5k6aa(sd);
	स्थिर काष्ठा s5k6aa_पूर्णांकerval *fi;
	पूर्णांक ret = 0;

	अगर (fie->index >= ARRAY_SIZE(s5k6aa_पूर्णांकervals))
		वापस -EINVAL;

	v4l_bound_align_image(&fie->width, S5K6AA_WIN_WIDTH_MIN,
			      S5K6AA_WIN_WIDTH_MAX, 1,
			      &fie->height, S5K6AA_WIN_HEIGHT_MIN,
			      S5K6AA_WIN_HEIGHT_MAX, 1, 0);

	mutex_lock(&s5k6aa->lock);
	fi = &s5k6aa_पूर्णांकervals[fie->index];
	अगर (fie->width > fi->size.width || fie->height > fi->size.height)
		ret = -EINVAL;
	अन्यथा
		fie->पूर्णांकerval = fi->पूर्णांकerval;
	mutex_unlock(&s5k6aa->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक s5k6aa_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->index >= ARRAY_SIZE(s5k6aa_क्रमmats))
		वापस -EINVAL;

	code->code = s5k6aa_क्रमmats[code->index].code;
	वापस 0;
पूर्ण

अटल पूर्णांक s5k6aa_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	पूर्णांक i = ARRAY_SIZE(s5k6aa_क्रमmats);

	अगर (fse->index > 0)
		वापस -EINVAL;

	जबतक (--i)
		अगर (fse->code == s5k6aa_क्रमmats[i].code)
			अवरोध;

	fse->code = s5k6aa_क्रमmats[i].code;
	fse->min_width  = S5K6AA_WIN_WIDTH_MIN;
	fse->max_width  = S5K6AA_WIN_WIDTH_MAX;
	fse->max_height = S5K6AA_WIN_HEIGHT_MIN;
	fse->min_height = S5K6AA_WIN_HEIGHT_MAX;

	वापस 0;
पूर्ण

अटल काष्ठा v4l2_rect *
__s5k6aa_get_crop_rect(काष्ठा s5k6aa *s5k6aa, काष्ठा v4l2_subdev_pad_config *cfg,
		       क्रमागत v4l2_subdev_क्रमmat_whence which)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस &s5k6aa->ccd_rect;

	WARN_ON(which != V4L2_SUBDEV_FORMAT_TRY);
	वापस v4l2_subdev_get_try_crop(&s5k6aa->sd, cfg, 0);
पूर्ण

अटल व्योम s5k6aa_try_क्रमmat(काष्ठा s5k6aa *s5k6aa,
			      काष्ठा v4l2_mbus_framefmt *mf)
अणु
	अचिन्हित पूर्णांक index;

	v4l_bound_align_image(&mf->width, S5K6AA_WIN_WIDTH_MIN,
			      S5K6AA_WIN_WIDTH_MAX, 1,
			      &mf->height, S5K6AA_WIN_HEIGHT_MIN,
			      S5K6AA_WIN_HEIGHT_MAX, 1, 0);

	अगर (mf->colorspace != V4L2_COLORSPACE_JPEG &&
	    mf->colorspace != V4L2_COLORSPACE_REC709)
		mf->colorspace = V4L2_COLORSPACE_JPEG;

	index = s5k6aa_get_pixfmt_index(s5k6aa, mf);

	mf->colorspace	= s5k6aa_क्रमmats[index].colorspace;
	mf->code	= s5k6aa_क्रमmats[index].code;
	mf->field	= V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक s5k6aa_get_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा s5k6aa *s5k6aa = to_s5k6aa(sd);
	काष्ठा v4l2_mbus_framefmt *mf;

	स_रखो(fmt->reserved, 0, माप(fmt->reserved));

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
		fmt->क्रमmat = *mf;
		वापस 0;
	पूर्ण

	mutex_lock(&s5k6aa->lock);
	fmt->क्रमmat = s5k6aa->preset->mbus_fmt;
	mutex_unlock(&s5k6aa->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक s5k6aa_set_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा s5k6aa *s5k6aa = to_s5k6aa(sd);
	काष्ठा s5k6aa_preset *preset = s5k6aa->preset;
	काष्ठा v4l2_mbus_framefmt *mf;
	काष्ठा v4l2_rect *crop;
	पूर्णांक ret = 0;

	mutex_lock(&s5k6aa->lock);
	s5k6aa_try_क्रमmat(s5k6aa, &fmt->क्रमmat);

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		crop = v4l2_subdev_get_try_crop(sd, cfg, 0);
	पूर्ण अन्यथा अणु
		अगर (s5k6aa->streaming) अणु
			ret = -EBUSY;
		पूर्ण अन्यथा अणु
			mf = &preset->mbus_fmt;
			crop = &s5k6aa->ccd_rect;
			s5k6aa->apply_cfg = 1;
		पूर्ण
	पूर्ण

	अगर (ret == 0) अणु
		काष्ठा v4l2_subdev_frame_पूर्णांकerval fiv = अणु
			.पूर्णांकerval = अणु0, 1पूर्ण
		पूर्ण;

		*mf = fmt->क्रमmat;
		/*
		 * Make sure the crop winकरोw is valid, i.e. its size is
		 * greater than the output winकरोw, as the ISP supports
		 * only करोwn-scaling.
		 */
		crop->width = clamp_t(अचिन्हित पूर्णांक, crop->width, mf->width,
				      S5K6AA_WIN_WIDTH_MAX);
		crop->height = clamp_t(अचिन्हित पूर्णांक, crop->height, mf->height,
				       S5K6AA_WIN_HEIGHT_MAX);
		crop->left = clamp_t(अचिन्हित पूर्णांक, crop->left, 0,
				     S5K6AA_WIN_WIDTH_MAX - crop->width);
		crop->top  = clamp_t(अचिन्हित पूर्णांक, crop->top, 0,
				     S5K6AA_WIN_HEIGHT_MAX - crop->height);

		/* Reset to minimum possible frame पूर्णांकerval */
		ret = __s5k6aa_set_frame_पूर्णांकerval(s5k6aa, &fiv);
	पूर्ण
	mutex_unlock(&s5k6aa->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक s5k6aa_get_selection(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा s5k6aa *s5k6aa = to_s5k6aa(sd);
	काष्ठा v4l2_rect *rect;

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	स_रखो(sel->reserved, 0, माप(sel->reserved));

	mutex_lock(&s5k6aa->lock);
	rect = __s5k6aa_get_crop_rect(s5k6aa, cfg, sel->which);
	sel->r = *rect;
	mutex_unlock(&s5k6aa->lock);

	v4l2_dbg(1, debug, sd, "Current crop rectangle: (%d,%d)/%dx%d\n",
		 rect->left, rect->top, rect->width, rect->height);

	वापस 0;
पूर्ण

अटल पूर्णांक s5k6aa_set_selection(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_selection *sel)
अणु
	काष्ठा s5k6aa *s5k6aa = to_s5k6aa(sd);
	काष्ठा v4l2_mbus_framefmt *mf;
	अचिन्हित पूर्णांक max_x, max_y;
	काष्ठा v4l2_rect *crop_r;

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	mutex_lock(&s5k6aa->lock);
	crop_r = __s5k6aa_get_crop_rect(s5k6aa, cfg, sel->which);

	अगर (sel->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		mf = &s5k6aa->preset->mbus_fmt;
		s5k6aa->apply_crop = 1;
	पूर्ण अन्यथा अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
	पूर्ण
	v4l_bound_align_image(&sel->r.width, mf->width,
			      S5K6AA_WIN_WIDTH_MAX, 1,
			      &sel->r.height, mf->height,
			      S5K6AA_WIN_HEIGHT_MAX, 1, 0);

	max_x = (S5K6AA_WIN_WIDTH_MAX - sel->r.width) & ~1;
	max_y = (S5K6AA_WIN_HEIGHT_MAX - sel->r.height) & ~1;

	sel->r.left = clamp_t(अचिन्हित पूर्णांक, sel->r.left, 0, max_x);
	sel->r.top  = clamp_t(अचिन्हित पूर्णांक, sel->r.top, 0, max_y);

	*crop_r = sel->r;

	mutex_unlock(&s5k6aa->lock);

	v4l2_dbg(1, debug, sd, "Set crop rectangle: (%d,%d)/%dx%d\n",
		 crop_r->left, crop_r->top, crop_r->width, crop_r->height);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops s5k6aa_pad_ops = अणु
	.क्रमागत_mbus_code		= s5k6aa_क्रमागत_mbus_code,
	.क्रमागत_frame_size	= s5k6aa_क्रमागत_frame_size,
	.क्रमागत_frame_पूर्णांकerval	= s5k6aa_क्रमागत_frame_पूर्णांकerval,
	.get_fmt		= s5k6aa_get_fmt,
	.set_fmt		= s5k6aa_set_fmt,
	.get_selection		= s5k6aa_get_selection,
	.set_selection		= s5k6aa_set_selection,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops s5k6aa_video_ops = अणु
	.g_frame_पूर्णांकerval	= s5k6aa_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval	= s5k6aa_s_frame_पूर्णांकerval,
	.s_stream		= s5k6aa_s_stream,
पूर्ण;

/*
 * V4L2 subdev controls
 */

अटल पूर्णांक s5k6aa_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = ctrl_to_sd(ctrl);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	काष्ठा s5k6aa *s5k6aa = to_s5k6aa(sd);
	पूर्णांक idx, err = 0;

	v4l2_dbg(1, debug, sd, "ctrl: 0x%x, value: %d\n", ctrl->id, ctrl->val);

	mutex_lock(&s5k6aa->lock);
	/*
	 * If the device is not घातered up by the host driver करो
	 * not apply any controls to H/W at this समय. Instead
	 * the controls will be restored right after घातer-up.
	 */
	अगर (s5k6aa->घातer == 0)
		जाओ unlock;
	idx = s5k6aa->preset->index;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		err = s5k6aa_set_awb(s5k6aa, ctrl->val);
		अवरोध;

	हाल V4L2_CID_BRIGHTNESS:
		err = s5k6aa_ग_लिखो(client, REG_USER_BRIGHTNESS, ctrl->val);
		अवरोध;

	हाल V4L2_CID_COLORFX:
		err = s5k6aa_set_colorfx(s5k6aa, ctrl->val);
		अवरोध;

	हाल V4L2_CID_CONTRAST:
		err = s5k6aa_ग_लिखो(client, REG_USER_CONTRAST, ctrl->val);
		अवरोध;

	हाल V4L2_CID_EXPOSURE_AUTO:
		err = s5k6aa_set_स्वतः_exposure(s5k6aa, ctrl->val);
		अवरोध;

	हाल V4L2_CID_HFLIP:
		err = s5k6aa_set_mirror(s5k6aa, ctrl->val);
		अगर (err)
			अवरोध;
		err = s5k6aa_ग_लिखो(client, REG_G_PREV_CFG_CHG, 1);
		अवरोध;

	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		err = s5k6aa_set_anti_flicker(s5k6aa, ctrl->val);
		अवरोध;

	हाल V4L2_CID_SATURATION:
		err = s5k6aa_ग_लिखो(client, REG_USER_SATURATION, ctrl->val);
		अवरोध;

	हाल V4L2_CID_SHARPNESS:
		err = s5k6aa_ग_लिखो(client, REG_USER_SHARPBLUR, ctrl->val);
		अवरोध;

	हाल V4L2_CID_WHITE_BALANCE_TEMPERATURE:
		err = s5k6aa_ग_लिखो(client, REG_P_COLORTEMP(idx), ctrl->val);
		अगर (err)
			अवरोध;
		err = s5k6aa_ग_लिखो(client, REG_G_PREV_CFG_CHG, 1);
		अवरोध;
	पूर्ण
unlock:
	mutex_unlock(&s5k6aa->lock);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops s5k6aa_ctrl_ops = अणु
	.s_ctrl	= s5k6aa_s_ctrl,
पूर्ण;

अटल पूर्णांक s5k6aa_log_status(काष्ठा v4l2_subdev *sd)
अणु
	v4l2_ctrl_handler_log_status(sd->ctrl_handler, sd->name);
	वापस 0;
पूर्ण

#घोषणा V4L2_CID_RED_GAIN	(V4L2_CTRL_CLASS_CAMERA | 0x1001)
#घोषणा V4L2_CID_GREEN_GAIN	(V4L2_CTRL_CLASS_CAMERA | 0x1002)
#घोषणा V4L2_CID_BLUE_GAIN	(V4L2_CTRL_CLASS_CAMERA | 0x1003)

अटल स्थिर काष्ठा v4l2_ctrl_config s5k6aa_ctrls[] = अणु
	अणु
		.ops	= &s5k6aa_ctrl_ops,
		.id	= V4L2_CID_RED_GAIN,
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.name	= "Gain, Red",
		.min	= 0,
		.max	= 256,
		.def	= 127,
		.step	= 1,
	पूर्ण, अणु
		.ops	= &s5k6aa_ctrl_ops,
		.id	= V4L2_CID_GREEN_GAIN,
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.name	= "Gain, Green",
		.min	= 0,
		.max	= 256,
		.def	= 127,
		.step	= 1,
	पूर्ण, अणु
		.ops	= &s5k6aa_ctrl_ops,
		.id	= V4L2_CID_BLUE_GAIN,
		.type	= V4L2_CTRL_TYPE_INTEGER,
		.name	= "Gain, Blue",
		.min	= 0,
		.max	= 256,
		.def	= 127,
		.step	= 1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक s5k6aa_initialize_ctrls(काष्ठा s5k6aa *s5k6aa)
अणु
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &s5k6aa_ctrl_ops;
	काष्ठा s5k6aa_ctrls *ctrls = &s5k6aa->ctrls;
	काष्ठा v4l2_ctrl_handler *hdl = &ctrls->handler;

	पूर्णांक ret = v4l2_ctrl_handler_init(hdl, 16);
	अगर (ret)
		वापस ret;
	/* Auto white balance cluster */
	ctrls->awb = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_AUTO_WHITE_BALANCE,
				       0, 1, 1, 1);
	ctrls->gain_red = v4l2_ctrl_new_custom(hdl, &s5k6aa_ctrls[0], शून्य);
	ctrls->gain_green = v4l2_ctrl_new_custom(hdl, &s5k6aa_ctrls[1], शून्य);
	ctrls->gain_blue = v4l2_ctrl_new_custom(hdl, &s5k6aa_ctrls[2], शून्य);
	v4l2_ctrl_स्वतः_cluster(4, &ctrls->awb, 0, false);

	ctrls->hflip = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_HFLIP, 0, 1, 1, 0);
	ctrls->vflip = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_cluster(2, &ctrls->hflip);

	ctrls->स्वतः_exp = v4l2_ctrl_new_std_menu(hdl, ops,
				V4L2_CID_EXPOSURE_AUTO,
				V4L2_EXPOSURE_MANUAL, 0, V4L2_EXPOSURE_AUTO);
	/* Exposure समय: x 1 us */
	ctrls->exposure = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_EXPOSURE,
					    0, 6000000U, 1, 100000U);
	/* Total gain: 256 <=> 1x */
	ctrls->gain = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_GAIN,
					0, 256, 1, 256);
	v4l2_ctrl_स्वतः_cluster(3, &ctrls->स्वतः_exp, 0, false);

	v4l2_ctrl_new_std_menu(hdl, ops, V4L2_CID_POWER_LINE_FREQUENCY,
			       V4L2_CID_POWER_LINE_FREQUENCY_AUTO, 0,
			       V4L2_CID_POWER_LINE_FREQUENCY_AUTO);

	v4l2_ctrl_new_std_menu(hdl, ops, V4L2_CID_COLORFX,
			       V4L2_COLORFX_SKY_BLUE, ~0x6f, V4L2_COLORFX_NONE);

	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_WHITE_BALANCE_TEMPERATURE,
			  0, 256, 1, 0);

	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_SATURATION, -127, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_BRIGHTNESS, -127, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_CONTRAST, -127, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_SHARPNESS, -127, 127, 1, 0);

	अगर (hdl->error) अणु
		ret = hdl->error;
		v4l2_ctrl_handler_मुक्त(hdl);
		वापस ret;
	पूर्ण

	s5k6aa->sd.ctrl_handler = hdl;
	वापस 0;
पूर्ण

/*
 * V4L2 subdev पूर्णांकernal operations
 */
अटल पूर्णांक s5k6aa_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_mbus_framefmt *क्रमmat = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, 0);
	काष्ठा v4l2_rect *crop = v4l2_subdev_get_try_crop(sd, fh->pad, 0);

	क्रमmat->colorspace = s5k6aa_क्रमmats[0].colorspace;
	क्रमmat->code = s5k6aa_क्रमmats[0].code;
	क्रमmat->width = S5K6AA_OUT_WIDTH_DEF;
	क्रमmat->height = S5K6AA_OUT_HEIGHT_DEF;
	क्रमmat->field = V4L2_FIELD_NONE;

	crop->width = S5K6AA_WIN_WIDTH_MAX;
	crop->height = S5K6AA_WIN_HEIGHT_MAX;
	crop->left = 0;
	crop->top = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक s5k6aa_check_fw_revision(काष्ठा s5k6aa *s5k6aa)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&s5k6aa->sd);
	u16 api_ver = 0, fw_rev = 0;

	पूर्णांक ret = s5k6aa_set_ahb_address(client);

	अगर (!ret)
		ret = s5k6aa_पढ़ो(client, REG_FW_APIVER, &api_ver);
	अगर (!ret)
		ret = s5k6aa_पढ़ो(client, REG_FW_REVISION, &fw_rev);
	अगर (ret) अणु
		v4l2_err(&s5k6aa->sd, "FW revision check failed!\n");
		वापस ret;
	पूर्ण

	v4l2_info(&s5k6aa->sd, "FW API ver.: 0x%X, FW rev.: 0x%X\n",
		  api_ver, fw_rev);

	वापस api_ver == S5K6AAFX_FW_APIVER ? 0 : -ENODEV;
पूर्ण

अटल पूर्णांक s5k6aa_रेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा s5k6aa *s5k6aa = to_s5k6aa(sd);
	पूर्णांक ret;

	mutex_lock(&s5k6aa->lock);
	ret = __s5k6aa_घातer_on(s5k6aa);
	अगर (!ret) अणु
		msleep(100);
		ret = s5k6aa_check_fw_revision(s5k6aa);
		__s5k6aa_घातer_off(s5k6aa);
	पूर्ण
	mutex_unlock(&s5k6aa->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops s5k6aa_subdev_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = s5k6aa_रेजिस्टरed,
	.खोलो = s5k6aa_खोलो,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops s5k6aa_core_ops = अणु
	.s_घातer = s5k6aa_set_घातer,
	.log_status = s5k6aa_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops s5k6aa_subdev_ops = अणु
	.core = &s5k6aa_core_ops,
	.pad = &s5k6aa_pad_ops,
	.video = &s5k6aa_video_ops,
पूर्ण;

/*
 * GPIO setup
 */

अटल पूर्णांक s5k6aa_configure_gpios(काष्ठा s5k6aa *s5k6aa,
				  स्थिर काष्ठा s5k6aa_platक्रमm_data *pdata)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&s5k6aa->sd);
	स्थिर काष्ठा s5k6aa_gpio *gpio;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	s5k6aa->gpio[STBY].gpio = -EINVAL;
	s5k6aa->gpio[RST].gpio  = -EINVAL;

	gpio = &pdata->gpio_stby;
	अगर (gpio_is_valid(gpio->gpio)) अणु
		flags = (gpio->level ? GPIOF_OUT_INIT_HIGH : GPIOF_OUT_INIT_LOW)
		      | GPIOF_EXPORT;
		ret = devm_gpio_request_one(&client->dev, gpio->gpio, flags,
					    "S5K6AA_STBY");
		अगर (ret < 0)
			वापस ret;

		s5k6aa->gpio[STBY] = *gpio;
	पूर्ण

	gpio = &pdata->gpio_reset;
	अगर (gpio_is_valid(gpio->gpio)) अणु
		flags = (gpio->level ? GPIOF_OUT_INIT_HIGH : GPIOF_OUT_INIT_LOW)
		      | GPIOF_EXPORT;
		ret = devm_gpio_request_one(&client->dev, gpio->gpio, flags,
					    "S5K6AA_RST");
		अगर (ret < 0)
			वापस ret;

		s5k6aa->gpio[RST] = *gpio;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s5k6aa_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा s5k6aa_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा v4l2_subdev *sd;
	काष्ठा s5k6aa *s5k6aa;
	पूर्णांक i, ret;

	अगर (pdata == शून्य) अणु
		dev_err(&client->dev, "Platform data not specified\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->mclk_frequency == 0) अणु
		dev_err(&client->dev, "MCLK frequency not specified\n");
		वापस -EINVAL;
	पूर्ण

	s5k6aa = devm_kzalloc(&client->dev, माप(*s5k6aa), GFP_KERNEL);
	अगर (!s5k6aa)
		वापस -ENOMEM;

	mutex_init(&s5k6aa->lock);

	s5k6aa->mclk_frequency = pdata->mclk_frequency;
	s5k6aa->bus_type = pdata->bus_type;
	s5k6aa->mipi_lanes = pdata->nlanes;
	s5k6aa->s_घातer	= pdata->set_घातer;
	s5k6aa->inv_hflip = pdata->horiz_flip;
	s5k6aa->inv_vflip = pdata->vert_flip;

	sd = &s5k6aa->sd;
	v4l2_i2c_subdev_init(sd, client, &s5k6aa_subdev_ops);
	/* Static name; NEVER use in new drivers! */
	strscpy(sd->name, DRIVER_NAME, माप(sd->name));

	sd->पूर्णांकernal_ops = &s5k6aa_subdev_पूर्णांकernal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	s5k6aa->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&sd->entity, 1, &s5k6aa->pad);
	अगर (ret)
		वापस ret;

	ret = s5k6aa_configure_gpios(s5k6aa, pdata);
	अगर (ret)
		जाओ out_err;

	क्रम (i = 0; i < S5K6AA_NUM_SUPPLIES; i++)
		s5k6aa->supplies[i].supply = s5k6aa_supply_names[i];

	ret = devm_regulator_bulk_get(&client->dev, S5K6AA_NUM_SUPPLIES,
				 s5k6aa->supplies);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to get regulators\n");
		जाओ out_err;
	पूर्ण

	ret = s5k6aa_initialize_ctrls(s5k6aa);
	अगर (ret)
		जाओ out_err;

	s5k6aa_presets_data_init(s5k6aa);

	s5k6aa->ccd_rect.width = S5K6AA_WIN_WIDTH_MAX;
	s5k6aa->ccd_rect.height	= S5K6AA_WIN_HEIGHT_MAX;
	s5k6aa->ccd_rect.left = 0;
	s5k6aa->ccd_rect.top = 0;

	वापस 0;

out_err:
	media_entity_cleanup(&s5k6aa->sd.entity);
	वापस ret;
पूर्ण

अटल पूर्णांक s5k6aa_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	media_entity_cleanup(&sd->entity);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id s5k6aa_id[] = अणु
	अणु DRIVER_NAME, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, s5k6aa_id);


अटल काष्ठा i2c_driver s5k6aa_i2c_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME
	पूर्ण,
	.probe		= s5k6aa_probe,
	.हटाओ		= s5k6aa_हटाओ,
	.id_table	= s5k6aa_id,
पूर्ण;

module_i2c_driver(s5k6aa_i2c_driver);

MODULE_DESCRIPTION("Samsung S5K6AA(FX) SXGA camera driver");
MODULE_AUTHOR("Sylwester Nawrocki <s.nawrocki@samsung.com>");
MODULE_LICENSE("GPL");
