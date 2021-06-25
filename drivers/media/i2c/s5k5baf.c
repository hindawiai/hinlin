<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Samsung S5K5BAF UXGA 1/5" 2M CMOS Image Sensor
 * with embedded SoC ISP.
 *
 * Copyright (C) 2013, Samsung Electronics Co., Ltd.
 * Andrzej Hajda <a.hajda@samsung.com>
 *
 * Based on S5K6AA driver authored by Sylwester Nawrocki
 * Copyright (C) 2013, Samsung Electronics Co., Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/media.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_graph.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/v4l2-fwnode.h>

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

#घोषणा S5K5BAF_DRIVER_NAME		"s5k5baf"
#घोषणा S5K5BAF_DEFAULT_MCLK_FREQ	24000000U
#घोषणा S5K5BAF_CLK_NAME		"mclk"

#घोषणा S5K5BAF_FW_खाताNAME		"s5k5baf-cfg.bin"
#घोषणा S5K5BAF_FW_TAG			"SF00"
#घोषणा S5K5BAG_FW_TAG_LEN		2
#घोषणा S5K5BAG_FW_MAX_COUNT		16

#घोषणा S5K5BAF_CIS_WIDTH		1600
#घोषणा S5K5BAF_CIS_HEIGHT		1200
#घोषणा S5K5BAF_WIN_WIDTH_MIN		8
#घोषणा S5K5BAF_WIN_HEIGHT_MIN		8
#घोषणा S5K5BAF_GAIN_RED_DEF		127
#घोषणा S5K5BAF_GAIN_GREEN_DEF		95
#घोषणा S5K5BAF_GAIN_BLUE_DEF		180
/* Default number of MIPI CSI-2 data lanes used */
#घोषणा S5K5BAF_DEF_NUM_LANES		1

#घोषणा AHB_MSB_ADDR_PTR		0xfcfc

/*
 * Register पूर्णांकerface pages (the most signअगरicant word of the address)
 */
#घोषणा PAGE_IF_HW			0xd000
#घोषणा PAGE_IF_SW			0x7000

/*
 * H/W रेजिस्टर Interface (PAGE_IF_HW)
 */
#घोषणा REG_SW_LOAD_COMPLETE		0x0014
#घोषणा REG_CMDWR_PAGE			0x0028
#घोषणा REG_CMDWR_ADDR			0x002a
#घोषणा REG_CMDRD_PAGE			0x002c
#घोषणा REG_CMDRD_ADDR			0x002e
#घोषणा REG_CMD_BUF			0x0f12
#घोषणा REG_SET_HOST_INT		0x1000
#घोषणा REG_CLEAR_HOST_INT		0x1030
#घोषणा REG_PATTERN_SET			0x3100
#घोषणा REG_PATTERN_WIDTH		0x3118
#घोषणा REG_PATTERN_HEIGHT		0x311a
#घोषणा REG_PATTERN_PARAM		0x311c

/*
 * S/W रेजिस्टर पूर्णांकerface (PAGE_IF_SW)
 */

/* Firmware revision inक्रमmation */
#घोषणा REG_FW_APIVER			0x012e
#घोषणा  S5K5BAF_FW_APIVER		0x0001
#घोषणा REG_FW_REVISION			0x0130
#घोषणा REG_FW_SENSOR_ID		0x0152

/* Initialization parameters */
/* Master घड़ी frequency in KHz */
#घोषणा REG_I_INCLK_FREQ_L		0x01b8
#घोषणा REG_I_INCLK_FREQ_H		0x01ba
#घोषणा  MIN_MCLK_FREQ_KHZ		6000U
#घोषणा  MAX_MCLK_FREQ_KHZ		48000U
#घोषणा REG_I_USE_NPVI_CLOCKS		0x01c6
#घोषणा  NPVI_CLOCKS			1
#घोषणा REG_I_USE_NMIPI_CLOCKS		0x01c8
#घोषणा  NMIPI_CLOCKS			1
#घोषणा REG_I_BLOCK_INTERNAL_PLL_CALC	0x01ca

/* Clock configurations, n = 0..2. REG_I_* frequency unit is 4 kHz. */
#घोषणा REG_I_OPCLK_4KHZ(n)		((n) * 6 + 0x01cc)
#घोषणा REG_I_MIN_OUTRATE_4KHZ(n)	((n) * 6 + 0x01ce)
#घोषणा REG_I_MAX_OUTRATE_4KHZ(n)	((n) * 6 + 0x01d0)
#घोषणा  SCLK_PVI_FREQ			24000
#घोषणा  SCLK_MIPI_FREQ			48000
#घोषणा  PCLK_MIN_FREQ			6000
#घोषणा  PCLK_MAX_FREQ			48000
#घोषणा REG_I_USE_REGS_API		0x01de
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
#घोषणा REG_G_PREVREQ_IN_WIDTH		0x01fa
#घोषणा REG_G_PREVREQ_IN_HEIGHT		0x01fc
#घोषणा REG_G_PREVREQ_IN_XOFFS		0x01fe
#घोषणा REG_G_PREVREQ_IN_YOFFS		0x0200
#घोषणा REG_G_PREVZOOM_IN_WIDTH		0x020a
#घोषणा REG_G_PREVZOOM_IN_HEIGHT	0x020c
#घोषणा REG_G_PREVZOOM_IN_XOFFS		0x020e
#घोषणा REG_G_PREVZOOM_IN_YOFFS		0x0210
#घोषणा REG_G_INPUTS_CHANGE_REQ		0x021a
#घोषणा REG_G_ACTIVE_PREV_CFG		0x021c
#घोषणा REG_G_PREV_CFG_CHG		0x021e
#घोषणा REG_G_PREV_OPEN_AFTER_CH	0x0220
#घोषणा REG_G_PREV_CFG_ERROR		0x0222
#घोषणा  CFG_ERROR_RANGE		0x0b
#घोषणा REG_G_PREV_CFG_BYPASS_CHANGED	0x022a
#घोषणा REG_G_ACTUAL_P_FR_TIME		0x023a
#घोषणा REG_G_ACTUAL_P_OUT_RATE		0x023c
#घोषणा REG_G_ACTUAL_C_FR_TIME		0x023e
#घोषणा REG_G_ACTUAL_C_OUT_RATE		0x0240

/* Preview control section. n = 0...4. */
#घोषणा PREG(n, x)			((n) * 0x26 + x)
#घोषणा REG_P_OUT_WIDTH(n)		PREG(n, 0x0242)
#घोषणा REG_P_OUT_HEIGHT(n)		PREG(n, 0x0244)
#घोषणा REG_P_FMT(n)			PREG(n, 0x0246)
#घोषणा REG_P_MAX_OUT_RATE(n)		PREG(n, 0x0248)
#घोषणा REG_P_MIN_OUT_RATE(n)		PREG(n, 0x024a)
#घोषणा REG_P_PVI_MASK(n)		PREG(n, 0x024c)
#घोषणा  PVI_MASK_MIPI			0x52
#घोषणा REG_P_CLK_INDEX(n)		PREG(n, 0x024e)
#घोषणा  CLK_PVI_INDEX			0
#घोषणा  CLK_MIPI_INDEX			NPVI_CLOCKS
#घोषणा REG_P_FR_RATE_TYPE(n)		PREG(n, 0x0250)
#घोषणा  FR_RATE_DYNAMIC		0
#घोषणा  FR_RATE_FIXED			1
#घोषणा  FR_RATE_FIXED_ACCURATE		2
#घोषणा REG_P_FR_RATE_Q_TYPE(n)		PREG(n, 0x0252)
#घोषणा  FR_RATE_Q_DYNAMIC		0
#घोषणा  FR_RATE_Q_BEST_FRRATE		1 /* Binning enabled */
#घोषणा  FR_RATE_Q_BEST_QUALITY		2 /* Binning disabled */
/* Frame period in 0.1 ms units */
#घोषणा REG_P_MAX_FR_TIME(n)		PREG(n, 0x0254)
#घोषणा REG_P_MIN_FR_TIME(n)		PREG(n, 0x0256)
#घोषणा  S5K5BAF_MIN_FR_TIME		333  /* x100 us */
#घोषणा  S5K5BAF_MAX_FR_TIME		6500 /* x100 us */
/* The below 5 रेजिस्टरs are क्रम "device correction" values */
#घोषणा REG_P_SATURATION(n)		PREG(n, 0x0258)
#घोषणा REG_P_SHARP_BLUR(n)		PREG(n, 0x025a)
#घोषणा REG_P_GLAMOUR(n)		PREG(n, 0x025c)
#घोषणा REG_P_COLORTEMP(n)		PREG(n, 0x025e)
#घोषणा REG_P_GAMMA_INDEX(n)		PREG(n, 0x0260)
#घोषणा REG_P_PREV_MIRROR(n)		PREG(n, 0x0262)
#घोषणा REG_P_CAP_MIRROR(n)		PREG(n, 0x0264)
#घोषणा REG_P_CAP_ROTATION(n)		PREG(n, 0x0266)

/* Extended image property controls */
/* Exposure समय in 10 us units */
#घोषणा REG_SF_USR_EXPOSURE_L		0x03bc
#घोषणा REG_SF_USR_EXPOSURE_H		0x03be
#घोषणा REG_SF_USR_EXPOSURE_CHG		0x03c0
#घोषणा REG_SF_USR_TOT_GAIN		0x03c2
#घोषणा REG_SF_USR_TOT_GAIN_CHG		0x03c4
#घोषणा REG_SF_RGAIN			0x03c6
#घोषणा REG_SF_RGAIN_CHG		0x03c8
#घोषणा REG_SF_GGAIN			0x03ca
#घोषणा REG_SF_GGAIN_CHG		0x03cc
#घोषणा REG_SF_BGAIN			0x03ce
#घोषणा REG_SF_BGAIN_CHG		0x03d0
#घोषणा REG_SF_WBGAIN_CHG		0x03d2
#घोषणा REG_SF_FLICKER_QUANT		0x03d4
#घोषणा REG_SF_FLICKER_QUANT_CHG	0x03d6

/* Output पूर्णांकerface (parallel/MIPI) setup */
#घोषणा REG_OIF_EN_MIPI_LANES		0x03f2
#घोषणा REG_OIF_EN_PACKETS		0x03f4
#घोषणा  EN_PACKETS_CSI2		0xc3
#घोषणा REG_OIF_CFG_CHG			0x03f6

/* Auto-algorithms enable mask */
#घोषणा REG_DBG_AUTOALG_EN		0x03f8
#घोषणा  AALG_ALL_EN			BIT(0)
#घोषणा  AALG_AE_EN			BIT(1)
#घोषणा  AALG_DIVLEI_EN			BIT(2)
#घोषणा  AALG_WB_EN			BIT(3)
#घोषणा  AALG_USE_WB_FOR_ISP		BIT(4)
#घोषणा  AALG_FLICKER_EN		BIT(5)
#घोषणा  AALG_FIT_EN			BIT(6)
#घोषणा  AALG_WRHW_EN			BIT(7)

/* Poपूर्णांकers to color correction matrices */
#घोषणा REG_PTR_CCM_HORIZON		0x06d0
#घोषणा REG_PTR_CCM_INCANDESCENT	0x06d4
#घोषणा REG_PTR_CCM_WARM_WHITE		0x06d8
#घोषणा REG_PTR_CCM_COOL_WHITE		0x06dc
#घोषणा REG_PTR_CCM_DL50		0x06e0
#घोषणा REG_PTR_CCM_DL65		0x06e4
#घोषणा REG_PTR_CCM_OUTDOOR		0x06ec

#घोषणा REG_ARR_CCM(n)			(0x2800 + 36 * (n))

अटल स्थिर अक्षर * स्थिर s5k5baf_supply_names[] = अणु
	"vdda",		/* Analog घातer supply 2.8V (2.6V to 3.0V) */
	"vddreg",	/* Regulator input घातer supply 1.8V (1.7V to 1.9V)
			   or 2.8V (2.6V to 3.0) */
	"vddio",	/* I/O घातer supply 1.8V (1.65V to 1.95V)
			   or 2.8V (2.5V to 3.1V) */
पूर्ण;
#घोषणा S5K5BAF_NUM_SUPPLIES ARRAY_SIZE(s5k5baf_supply_names)

काष्ठा s5k5baf_gpio अणु
	पूर्णांक gpio;
	पूर्णांक level;
पूर्ण;

क्रमागत s5k5baf_gpio_id अणु
	STBY,
	RST,
	NUM_GPIOS,
पूर्ण;

#घोषणा PAD_CIS 0
#घोषणा PAD_OUT 1
#घोषणा NUM_CIS_PADS 1
#घोषणा NUM_ISP_PADS 2

काष्ठा s5k5baf_pixfmt अणु
	u32 code;
	u32 colorspace;
	/* REG_P_FMT(x) रेजिस्टर value */
	u16 reg_p_fmt;
पूर्ण;

काष्ठा s5k5baf_ctrls अणु
	काष्ठा v4l2_ctrl_handler handler;
	काष्ठा अणु /* Auto / manual white balance cluster */
		काष्ठा v4l2_ctrl *awb;
		काष्ठा v4l2_ctrl *gain_red;
		काष्ठा v4l2_ctrl *gain_blue;
	पूर्ण;
	काष्ठा अणु /* Mirror cluster */
		काष्ठा v4l2_ctrl *hflip;
		काष्ठा v4l2_ctrl *vflip;
	पूर्ण;
	काष्ठा अणु /* Auto exposure / manual exposure and gain cluster */
		काष्ठा v4l2_ctrl *स्वतः_exp;
		काष्ठा v4l2_ctrl *exposure;
		काष्ठा v4l2_ctrl *gain;
	पूर्ण;
पूर्ण;

क्रमागत अणु
	S5K5BAF_FW_ID_PATCH,
	S5K5BAF_FW_ID_CCM,
	S5K5BAF_FW_ID_CIS,
पूर्ण;

काष्ठा s5k5baf_fw अणु
	u16 count;
	काष्ठा अणु
		u16 id;
		u16 offset;
	पूर्ण seq[];
पूर्ण;

काष्ठा s5k5baf अणु
	काष्ठा s5k5baf_gpio gpios[NUM_GPIOS];
	क्रमागत v4l2_mbus_type bus_type;
	u8 nlanes;
	काष्ठा regulator_bulk_data supplies[S5K5BAF_NUM_SUPPLIES];

	काष्ठा clk *घड़ी;
	u32 mclk_frequency;

	काष्ठा s5k5baf_fw *fw;

	काष्ठा v4l2_subdev cis_sd;
	काष्ठा media_pad cis_pad;

	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pads[NUM_ISP_PADS];

	/* protects the काष्ठा members below */
	काष्ठा mutex lock;

	पूर्णांक error;

	काष्ठा v4l2_rect crop_sink;
	काष्ठा v4l2_rect compose;
	काष्ठा v4l2_rect crop_source;
	/* index to s5k5baf_क्रमmats array */
	पूर्णांक pixfmt;
	/* actual frame पूर्णांकerval in 100us */
	u16 fiv;
	/* requested frame पूर्णांकerval in 100us */
	u16 req_fiv;
	/* cache क्रम REG_DBG_AUTOALG_EN रेजिस्टर */
	u16 स्वतः_alg;

	काष्ठा s5k5baf_ctrls ctrls;

	अचिन्हित पूर्णांक streaming:1;
	अचिन्हित पूर्णांक apply_cfg:1;
	अचिन्हित पूर्णांक apply_crop:1;
	अचिन्हित पूर्णांक valid_स्वतः_alg:1;
	अचिन्हित पूर्णांक घातer;
पूर्ण;

अटल स्थिर काष्ठा s5k5baf_pixfmt s5k5baf_क्रमmats[] = अणु
	अणु MEDIA_BUS_FMT_VYUY8_2X8,	V4L2_COLORSPACE_JPEG,	5 पूर्ण,
	/* range 16-240 */
	अणु MEDIA_BUS_FMT_VYUY8_2X8,	V4L2_COLORSPACE_REC709,	6 पूर्ण,
	अणु MEDIA_BUS_FMT_RGB565_2X8_BE,	V4L2_COLORSPACE_JPEG,	0 पूर्ण,
पूर्ण;

अटल काष्ठा v4l2_rect s5k5baf_cis_rect = अणु
	0, 0, S5K5BAF_CIS_WIDTH, S5K5BAF_CIS_HEIGHT
पूर्ण;

/* Setfile contains set of I2C command sequences. Each sequence has its ID.
 * setfile क्रमmat:
 *	u8 magic[4];
 *	u16 count;		number of sequences
 *	काष्ठा अणु
 *		u16 id;		sequence id
 *		u16 offset;	sequence offset in data array
 *	पूर्ण seq[count];
 *	u16 data[*];		array containing sequences
 *
 */
अटल पूर्णांक s5k5baf_fw_parse(काष्ठा device *dev, काष्ठा s5k5baf_fw **fw,
			    माप_प्रकार count, स्थिर __le16 *data)
अणु
	काष्ठा s5k5baf_fw *f;
	u16 *d, i, *end;
	पूर्णांक ret;

	अगर (count < S5K5BAG_FW_TAG_LEN + 1) अणु
		dev_err(dev, "firmware file too short (%zu)\n", count);
		वापस -EINVAL;
	पूर्ण

	ret = स_भेद(data, S5K5BAF_FW_TAG, S5K5BAG_FW_TAG_LEN * माप(u16));
	अगर (ret != 0) अणु
		dev_err(dev, "invalid firmware magic number\n");
		वापस -EINVAL;
	पूर्ण

	data += S5K5BAG_FW_TAG_LEN;
	count -= S5K5BAG_FW_TAG_LEN;

	d = devm_kसुस्मृति(dev, count, माप(u16), GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;

	क्रम (i = 0; i < count; ++i)
		d[i] = le16_to_cpu(data[i]);

	f = (काष्ठा s5k5baf_fw *)d;
	अगर (count < 1 + 2 * f->count) अणु
		dev_err(dev, "invalid firmware header (count=%d size=%zu)\n",
			f->count, 2 * (count + S5K5BAG_FW_TAG_LEN));
		वापस -EINVAL;
	पूर्ण
	end = d + count;
	d += 1 + 2 * f->count;

	क्रम (i = 0; i < f->count; ++i) अणु
		अगर (f->seq[i].offset + d <= end)
			जारी;
		dev_err(dev, "invalid firmware header (seq=%d)\n", i);
		वापस -EINVAL;
	पूर्ण

	*fw = f;

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *ctrl_to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा s5k5baf, ctrls.handler)->sd;
पूर्ण

अटल अंतरभूत bool s5k5baf_is_cis_subdev(काष्ठा v4l2_subdev *sd)
अणु
	वापस sd->entity.function == MEDIA_ENT_F_CAM_SENSOR;
पूर्ण

अटल अंतरभूत काष्ठा s5k5baf *to_s5k5baf(काष्ठा v4l2_subdev *sd)
अणु
	अगर (s5k5baf_is_cis_subdev(sd))
		वापस container_of(sd, काष्ठा s5k5baf, cis_sd);
	अन्यथा
		वापस container_of(sd, काष्ठा s5k5baf, sd);
पूर्ण

अटल u16 s5k5baf_i2c_पढ़ो(काष्ठा s5k5baf *state, u16 addr)
अणु
	काष्ठा i2c_client *c = v4l2_get_subdevdata(&state->sd);
	__be16 w, r;
	u16 res;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = c->addr, .flags = 0,
		  .len = 2, .buf = (u8 *)&w पूर्ण,
		अणु .addr = c->addr, .flags = I2C_M_RD,
		  .len = 2, .buf = (u8 *)&r पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	अगर (state->error)
		वापस 0;

	w = cpu_to_be16(addr);
	ret = i2c_transfer(c->adapter, msg, 2);
	res = be16_to_cpu(r);

	v4l2_dbg(3, debug, c, "i2c_read: 0x%04x : 0x%04x\n", addr, res);

	अगर (ret != 2) अणु
		v4l2_err(c, "i2c_read: error during transfer (%d)\n", ret);
		state->error = ret;
	पूर्ण
	वापस res;
पूर्ण

अटल व्योम s5k5baf_i2c_ग_लिखो(काष्ठा s5k5baf *state, u16 addr, u16 val)
अणु
	u8 buf[4] = अणु addr >> 8, addr & 0xFF, val >> 8, val & 0xFF पूर्ण;
	काष्ठा i2c_client *c = v4l2_get_subdevdata(&state->sd);
	पूर्णांक ret;

	अगर (state->error)
		वापस;

	ret = i2c_master_send(c, buf, 4);
	v4l2_dbg(3, debug, c, "i2c_write: 0x%04x : 0x%04x\n", addr, val);

	अगर (ret != 4) अणु
		v4l2_err(c, "i2c_write: error during transfer (%d)\n", ret);
		state->error = ret;
	पूर्ण
पूर्ण

अटल u16 s5k5baf_पढ़ो(काष्ठा s5k5baf *state, u16 addr)
अणु
	s5k5baf_i2c_ग_लिखो(state, REG_CMDRD_ADDR, addr);
	वापस s5k5baf_i2c_पढ़ो(state, REG_CMD_BUF);
पूर्ण

अटल व्योम s5k5baf_ग_लिखो(काष्ठा s5k5baf *state, u16 addr, u16 val)
अणु
	s5k5baf_i2c_ग_लिखो(state, REG_CMDWR_ADDR, addr);
	s5k5baf_i2c_ग_लिखो(state, REG_CMD_BUF, val);
पूर्ण

अटल व्योम s5k5baf_ग_लिखो_arr_seq(काष्ठा s5k5baf *state, u16 addr,
				  u16 count, स्थिर u16 *seq)
अणु
	काष्ठा i2c_client *c = v4l2_get_subdevdata(&state->sd);
	__be16 buf[65];

	s5k5baf_i2c_ग_लिखो(state, REG_CMDWR_ADDR, addr);
	अगर (state->error)
		वापस;

	v4l2_dbg(3, debug, c, "i2c_write_seq(count=%d): %*ph\n", count,
		 min(2 * count, 64), seq);

	buf[0] = cpu_to_be16(REG_CMD_BUF);

	जबतक (count > 0) अणु
		पूर्णांक n = min_t(पूर्णांक, count, ARRAY_SIZE(buf) - 1);
		पूर्णांक ret, i;

		क्रम (i = 1; i <= n; ++i)
			buf[i] = cpu_to_be16(*seq++);

		i *= 2;
		ret = i2c_master_send(c, (अक्षर *)buf, i);
		अगर (ret != i) अणु
			v4l2_err(c, "i2c_write_seq: error during transfer (%d)\n", ret);
			state->error = ret;
			अवरोध;
		पूर्ण

		count -= n;
	पूर्ण
पूर्ण

#घोषणा s5k5baf_ग_लिखो_seq(state, addr, seq...) \
	s5k5baf_ग_लिखो_arr_seq(state, addr, माप((अक्षर[])अणु seq पूर्ण), \
			      (स्थिर u16 [])अणु seq पूर्ण)

/* add items count at the beginning of the list */
#घोषणा NSEQ(seq...) माप((अक्षर[])अणु seq पूर्ण), seq

/*
 * s5k5baf_ग_लिखो_nseq() - Writes sequences of values to sensor memory via i2c
 * @nseq: sequence of u16 words in क्रमmat:
 *	(N, address, value[1]...value[N-1])*,0
 * Ex.:
 *	u16 seq[] = अणु NSEQ(0x4000, 1, 1), NSEQ(0x4010, 640, 480), 0 पूर्ण;
 *	ret = s5k5baf_ग_लिखो_nseq(c, seq);
 */
अटल व्योम s5k5baf_ग_लिखो_nseq(काष्ठा s5k5baf *state, स्थिर u16 *nseq)
अणु
	पूर्णांक count;

	जबतक ((count = *nseq++)) अणु
		u16 addr = *nseq++;
		--count;

		s5k5baf_ग_लिखो_arr_seq(state, addr, count, nseq);
		nseq += count;
	पूर्ण
पूर्ण

अटल व्योम s5k5baf_synchronize(काष्ठा s5k5baf *state, पूर्णांक समयout, u16 addr)
अणु
	अचिन्हित दीर्घ end = jअगरfies + msecs_to_jअगरfies(समयout);
	u16 reg;

	s5k5baf_ग_लिखो(state, addr, 1);
	करो अणु
		reg = s5k5baf_पढ़ो(state, addr);
		अगर (state->error || !reg)
			वापस;
		usleep_range(5000, 10000);
	पूर्ण जबतक (समय_is_after_jअगरfies(end));

	v4l2_err(&state->sd, "timeout on register synchronize (%#x)\n", addr);
	state->error = -ETIMEDOUT;
पूर्ण

अटल u16 *s5k5baf_fw_get_seq(काष्ठा s5k5baf *state, u16 seq_id)
अणु
	काष्ठा s5k5baf_fw *fw = state->fw;
	u16 *data;
	पूर्णांक i;

	अगर (fw == शून्य)
		वापस शून्य;

	data = &fw->seq[0].id + 2 * fw->count;

	क्रम (i = 0; i < fw->count; ++i) अणु
		अगर (fw->seq[i].id == seq_id)
			वापस data + fw->seq[i].offset;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम s5k5baf_hw_patch(काष्ठा s5k5baf *state)
अणु
	u16 *seq = s5k5baf_fw_get_seq(state, S5K5BAF_FW_ID_PATCH);

	अगर (seq)
		s5k5baf_ग_लिखो_nseq(state, seq);
पूर्ण

अटल व्योम s5k5baf_hw_set_घड़ीs(काष्ठा s5k5baf *state)
अणु
	अचिन्हित दीर्घ mclk = state->mclk_frequency / 1000;
	u16 status;
	अटल स्थिर u16 nseq_clk_cfg[] = अणु
		NSEQ(REG_I_USE_NPVI_CLOCKS,
		  NPVI_CLOCKS, NMIPI_CLOCKS, 0,
		  SCLK_PVI_FREQ / 4, PCLK_MIN_FREQ / 4, PCLK_MAX_FREQ / 4,
		  SCLK_MIPI_FREQ / 4, PCLK_MIN_FREQ / 4, PCLK_MAX_FREQ / 4),
		NSEQ(REG_I_USE_REGS_API, 1),
		0
	पूर्ण;

	s5k5baf_ग_लिखो_seq(state, REG_I_INCLK_FREQ_L, mclk & 0xffff, mclk >> 16);
	s5k5baf_ग_लिखो_nseq(state, nseq_clk_cfg);

	s5k5baf_synchronize(state, 250, REG_I_INIT_PARAMS_UPDATED);
	status = s5k5baf_पढ़ो(state, REG_I_ERROR_INFO);
	अगर (!state->error && status) अणु
		v4l2_err(&state->sd, "error configuring PLL (%d)\n", status);
		state->error = -EINVAL;
	पूर्ण
पूर्ण

/* set custom color correction matrices क्रम various illuminations */
अटल व्योम s5k5baf_hw_set_ccm(काष्ठा s5k5baf *state)
अणु
	u16 *seq = s5k5baf_fw_get_seq(state, S5K5BAF_FW_ID_CCM);

	अगर (seq)
		s5k5baf_ग_लिखो_nseq(state, seq);
पूर्ण

/* CIS sensor tuning, based on unकरोcumented android driver code */
अटल व्योम s5k5baf_hw_set_cis(काष्ठा s5k5baf *state)
अणु
	u16 *seq = s5k5baf_fw_get_seq(state, S5K5BAF_FW_ID_CIS);

	अगर (!seq)
		वापस;

	s5k5baf_i2c_ग_लिखो(state, REG_CMDWR_PAGE, PAGE_IF_HW);
	s5k5baf_ग_लिखो_nseq(state, seq);
	s5k5baf_i2c_ग_लिखो(state, REG_CMDWR_PAGE, PAGE_IF_SW);
पूर्ण

अटल व्योम s5k5baf_hw_sync_cfg(काष्ठा s5k5baf *state)
अणु
	s5k5baf_ग_लिखो(state, REG_G_PREV_CFG_CHG, 1);
	अगर (state->apply_crop) अणु
		s5k5baf_ग_लिखो(state, REG_G_INPUTS_CHANGE_REQ, 1);
		s5k5baf_ग_लिखो(state, REG_G_PREV_CFG_BYPASS_CHANGED, 1);
	पूर्ण
	s5k5baf_synchronize(state, 500, REG_G_NEW_CFG_SYNC);
पूर्ण
/* Set horizontal and vertical image flipping */
अटल व्योम s5k5baf_hw_set_mirror(काष्ठा s5k5baf *state)
अणु
	u16 flip = state->ctrls.vflip->val | (state->ctrls.vflip->val << 1);

	s5k5baf_ग_लिखो(state, REG_P_PREV_MIRROR(0), flip);
	अगर (state->streaming)
		s5k5baf_hw_sync_cfg(state);
पूर्ण

अटल व्योम s5k5baf_hw_set_alg(काष्ठा s5k5baf *state, u16 alg, bool enable)
अणु
	u16 cur_alg, new_alg;

	अगर (!state->valid_स्वतः_alg)
		cur_alg = s5k5baf_पढ़ो(state, REG_DBG_AUTOALG_EN);
	अन्यथा
		cur_alg = state->स्वतः_alg;

	new_alg = enable ? (cur_alg | alg) : (cur_alg & ~alg);

	अगर (new_alg != cur_alg)
		s5k5baf_ग_लिखो(state, REG_DBG_AUTOALG_EN, new_alg);

	अगर (state->error)
		वापस;

	state->valid_स्वतः_alg = 1;
	state->स्वतः_alg = new_alg;
पूर्ण

/* Configure स्वतः/manual white balance and R/G/B gains */
अटल व्योम s5k5baf_hw_set_awb(काष्ठा s5k5baf *state, पूर्णांक awb)
अणु
	काष्ठा s5k5baf_ctrls *ctrls = &state->ctrls;

	अगर (!awb)
		s5k5baf_ग_लिखो_seq(state, REG_SF_RGAIN,
				  ctrls->gain_red->val, 1,
				  S5K5BAF_GAIN_GREEN_DEF, 1,
				  ctrls->gain_blue->val, 1,
				  1);

	s5k5baf_hw_set_alg(state, AALG_WB_EN, awb);
पूर्ण

/* Program FW with exposure समय, 'exposure' in us units */
अटल व्योम s5k5baf_hw_set_user_exposure(काष्ठा s5k5baf *state, पूर्णांक exposure)
अणु
	अचिन्हित पूर्णांक समय = exposure / 10;

	s5k5baf_ग_लिखो_seq(state, REG_SF_USR_EXPOSURE_L,
			  समय & 0xffff, समय >> 16, 1);
पूर्ण

अटल व्योम s5k5baf_hw_set_user_gain(काष्ठा s5k5baf *state, पूर्णांक gain)
अणु
	s5k5baf_ग_लिखो_seq(state, REG_SF_USR_TOT_GAIN, gain, 1);
पूर्ण

/* Set स्वतः/manual exposure and total gain */
अटल व्योम s5k5baf_hw_set_स्वतः_exposure(काष्ठा s5k5baf *state, पूर्णांक value)
अणु
	अगर (value == V4L2_EXPOSURE_AUTO) अणु
		s5k5baf_hw_set_alg(state, AALG_AE_EN | AALG_DIVLEI_EN, true);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक exp_समय = state->ctrls.exposure->val;

		s5k5baf_hw_set_user_exposure(state, exp_समय);
		s5k5baf_hw_set_user_gain(state, state->ctrls.gain->val);
		s5k5baf_hw_set_alg(state, AALG_AE_EN | AALG_DIVLEI_EN, false);
	पूर्ण
पूर्ण

अटल व्योम s5k5baf_hw_set_anti_flicker(काष्ठा s5k5baf *state, पूर्णांक v)
अणु
	अगर (v == V4L2_CID_POWER_LINE_FREQUENCY_AUTO) अणु
		s5k5baf_hw_set_alg(state, AALG_FLICKER_EN, true);
	पूर्ण अन्यथा अणु
		/* The V4L2_CID_LINE_FREQUENCY control values match
		 * the रेजिस्टर values */
		s5k5baf_ग_लिखो_seq(state, REG_SF_FLICKER_QUANT, v, 1);
		s5k5baf_hw_set_alg(state, AALG_FLICKER_EN, false);
	पूर्ण
पूर्ण

अटल व्योम s5k5baf_hw_set_colorfx(काष्ठा s5k5baf *state, पूर्णांक val)
अणु
	अटल स्थिर u16 colorfx[] = अणु
		[V4L2_COLORFX_NONE] = 0,
		[V4L2_COLORFX_BW] = 1,
		[V4L2_COLORFX_NEGATIVE] = 2,
		[V4L2_COLORFX_SEPIA] = 3,
		[V4L2_COLORFX_SKY_BLUE] = 4,
		[V4L2_COLORFX_SKETCH] = 5,
	पूर्ण;

	s5k5baf_ग_लिखो(state, REG_G_SPEC_EFFECTS, colorfx[val]);
पूर्ण

अटल पूर्णांक s5k5baf_find_pixfmt(काष्ठा v4l2_mbus_framefmt *mf)
अणु
	पूर्णांक i, c = -1;

	क्रम (i = 0; i < ARRAY_SIZE(s5k5baf_क्रमmats); i++) अणु
		अगर (mf->colorspace != s5k5baf_क्रमmats[i].colorspace)
			जारी;
		अगर (mf->code == s5k5baf_क्रमmats[i].code)
			वापस i;
		अगर (c < 0)
			c = i;
	पूर्ण
	वापस (c < 0) ? 0 : c;
पूर्ण

अटल पूर्णांक s5k5baf_clear_error(काष्ठा s5k5baf *state)
अणु
	पूर्णांक ret = state->error;

	state->error = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक s5k5baf_hw_set_video_bus(काष्ठा s5k5baf *state)
अणु
	u16 en_pkts;

	अगर (state->bus_type == V4L2_MBUS_CSI2_DPHY)
		en_pkts = EN_PACKETS_CSI2;
	अन्यथा
		en_pkts = 0;

	s5k5baf_ग_लिखो_seq(state, REG_OIF_EN_MIPI_LANES,
			  state->nlanes, en_pkts, 1);

	वापस s5k5baf_clear_error(state);
पूर्ण

अटल u16 s5k5baf_get_cfg_error(काष्ठा s5k5baf *state)
अणु
	u16 err = s5k5baf_पढ़ो(state, REG_G_PREV_CFG_ERROR);
	अगर (err)
		s5k5baf_ग_लिखो(state, REG_G_PREV_CFG_ERROR, 0);
	वापस err;
पूर्ण

अटल व्योम s5k5baf_hw_set_fiv(काष्ठा s5k5baf *state, u16 fiv)
अणु
	s5k5baf_ग_लिखो(state, REG_P_MAX_FR_TIME(0), fiv);
	s5k5baf_hw_sync_cfg(state);
पूर्ण

अटल व्योम s5k5baf_hw_find_min_fiv(काष्ठा s5k5baf *state)
अणु
	u16 err, fiv;
	पूर्णांक n;

	fiv = s5k5baf_पढ़ो(state,  REG_G_ACTUAL_P_FR_TIME);
	अगर (state->error)
		वापस;

	क्रम (n = 5; n > 0; --n) अणु
		s5k5baf_hw_set_fiv(state, fiv);
		err = s5k5baf_get_cfg_error(state);
		अगर (state->error)
			वापस;
		चयन (err) अणु
		हाल CFG_ERROR_RANGE:
			++fiv;
			अवरोध;
		हाल 0:
			state->fiv = fiv;
			v4l2_info(&state->sd,
				  "found valid frame interval: %d00us\n", fiv);
			वापस;
		शेष:
			v4l2_err(&state->sd,
				 "error setting frame interval: %d\n", err);
			state->error = -EINVAL;
		पूर्ण
	पूर्ण
	v4l2_err(&state->sd, "cannot find correct frame interval\n");
	state->error = -दुस्फल;
पूर्ण

अटल व्योम s5k5baf_hw_validate_cfg(काष्ठा s5k5baf *state)
अणु
	u16 err;

	err = s5k5baf_get_cfg_error(state);
	अगर (state->error)
		वापस;

	चयन (err) अणु
	हाल 0:
		state->apply_cfg = 1;
		वापस;
	हाल CFG_ERROR_RANGE:
		s5k5baf_hw_find_min_fiv(state);
		अगर (!state->error)
			state->apply_cfg = 1;
		वापस;
	शेष:
		v4l2_err(&state->sd,
			 "error setting format: %d\n", err);
		state->error = -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम s5k5baf_rescale(काष्ठा v4l2_rect *r, स्थिर काष्ठा v4l2_rect *v,
			    स्थिर काष्ठा v4l2_rect *n,
			    स्थिर काष्ठा v4l2_rect *d)
अणु
	r->left = v->left * n->width / d->width;
	r->top = v->top * n->height / d->height;
	r->width = v->width * n->width / d->width;
	r->height = v->height * n->height / d->height;
पूर्ण

अटल पूर्णांक s5k5baf_hw_set_crop_rects(काष्ठा s5k5baf *state)
अणु
	काष्ठा v4l2_rect *p, r;
	u16 err;
	पूर्णांक ret;

	p = &state->crop_sink;
	s5k5baf_ग_लिखो_seq(state, REG_G_PREVREQ_IN_WIDTH, p->width, p->height,
			  p->left, p->top);

	s5k5baf_rescale(&r, &state->crop_source, &state->crop_sink,
			&state->compose);
	s5k5baf_ग_लिखो_seq(state, REG_G_PREVZOOM_IN_WIDTH, r.width, r.height,
			  r.left, r.top);

	s5k5baf_synchronize(state, 500, REG_G_INPUTS_CHANGE_REQ);
	s5k5baf_synchronize(state, 500, REG_G_PREV_CFG_BYPASS_CHANGED);
	err = s5k5baf_get_cfg_error(state);
	ret = s5k5baf_clear_error(state);
	अगर (ret < 0)
		वापस ret;

	चयन (err) अणु
	हाल 0:
		अवरोध;
	हाल CFG_ERROR_RANGE:
		/* retry crop with frame पूर्णांकerval set to max */
		s5k5baf_hw_set_fiv(state, S5K5BAF_MAX_FR_TIME);
		err = s5k5baf_get_cfg_error(state);
		ret = s5k5baf_clear_error(state);
		अगर (ret < 0)
			वापस ret;
		अगर (err) अणु
			v4l2_err(&state->sd,
				 "crop error on max frame interval: %d\n", err);
			state->error = -EINVAL;
		पूर्ण
		s5k5baf_hw_set_fiv(state, state->req_fiv);
		s5k5baf_hw_validate_cfg(state);
		अवरोध;
	शेष:
		v4l2_err(&state->sd, "crop error: %d\n", err);
		वापस -EINVAL;
	पूर्ण

	अगर (!state->apply_cfg)
		वापस 0;

	p = &state->crop_source;
	s5k5baf_ग_लिखो_seq(state, REG_P_OUT_WIDTH(0), p->width, p->height);
	s5k5baf_hw_set_fiv(state, state->req_fiv);
	s5k5baf_hw_validate_cfg(state);

	वापस s5k5baf_clear_error(state);
पूर्ण

अटल व्योम s5k5baf_hw_set_config(काष्ठा s5k5baf *state)
अणु
	u16 reg_fmt = s5k5baf_क्रमmats[state->pixfmt].reg_p_fmt;
	काष्ठा v4l2_rect *r = &state->crop_source;

	s5k5baf_ग_लिखो_seq(state, REG_P_OUT_WIDTH(0),
			  r->width, r->height, reg_fmt,
			  PCLK_MAX_FREQ >> 2, PCLK_MIN_FREQ >> 2,
			  PVI_MASK_MIPI, CLK_MIPI_INDEX,
			  FR_RATE_FIXED, FR_RATE_Q_DYNAMIC,
			  state->req_fiv, S5K5BAF_MIN_FR_TIME);
	s5k5baf_hw_sync_cfg(state);
	s5k5baf_hw_validate_cfg(state);
पूर्ण


अटल व्योम s5k5baf_hw_set_test_pattern(काष्ठा s5k5baf *state, पूर्णांक id)
अणु
	s5k5baf_i2c_ग_लिखो(state, REG_PATTERN_WIDTH, 800);
	s5k5baf_i2c_ग_लिखो(state, REG_PATTERN_HEIGHT, 511);
	s5k5baf_i2c_ग_लिखो(state, REG_PATTERN_PARAM, 0);
	s5k5baf_i2c_ग_लिखो(state, REG_PATTERN_SET, id);
पूर्ण

अटल व्योम s5k5baf_gpio_निश्चित(काष्ठा s5k5baf *state, पूर्णांक id)
अणु
	काष्ठा s5k5baf_gpio *gpio = &state->gpios[id];

	gpio_set_value(gpio->gpio, gpio->level);
पूर्ण

अटल व्योम s5k5baf_gpio_deनिश्चित(काष्ठा s5k5baf *state, पूर्णांक id)
अणु
	काष्ठा s5k5baf_gpio *gpio = &state->gpios[id];

	gpio_set_value(gpio->gpio, !gpio->level);
पूर्ण

अटल पूर्णांक s5k5baf_घातer_on(काष्ठा s5k5baf *state)
अणु
	पूर्णांक ret;

	ret = regulator_bulk_enable(S5K5BAF_NUM_SUPPLIES, state->supplies);
	अगर (ret < 0)
		जाओ err;

	ret = clk_set_rate(state->घड़ी, state->mclk_frequency);
	अगर (ret < 0)
		जाओ err_reg_dis;

	ret = clk_prepare_enable(state->घड़ी);
	अगर (ret < 0)
		जाओ err_reg_dis;

	v4l2_dbg(1, debug, &state->sd, "clock frequency: %ld\n",
		 clk_get_rate(state->घड़ी));

	s5k5baf_gpio_deनिश्चित(state, STBY);
	usleep_range(50, 100);
	s5k5baf_gpio_deनिश्चित(state, RST);
	वापस 0;

err_reg_dis:
	regulator_bulk_disable(S5K5BAF_NUM_SUPPLIES, state->supplies);
err:
	v4l2_err(&state->sd, "%s() failed (%d)\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक s5k5baf_घातer_off(काष्ठा s5k5baf *state)
अणु
	पूर्णांक ret;

	state->streaming = 0;
	state->apply_cfg = 0;
	state->apply_crop = 0;

	s5k5baf_gpio_निश्चित(state, RST);
	s5k5baf_gpio_निश्चित(state, STBY);

	अगर (!IS_ERR(state->घड़ी))
		clk_disable_unprepare(state->घड़ी);

	ret = regulator_bulk_disable(S5K5BAF_NUM_SUPPLIES,
					state->supplies);
	अगर (ret < 0)
		v4l2_err(&state->sd, "failed to disable regulators\n");

	वापस 0;
पूर्ण

अटल व्योम s5k5baf_hw_init(काष्ठा s5k5baf *state)
अणु
	s5k5baf_i2c_ग_लिखो(state, AHB_MSB_ADDR_PTR, PAGE_IF_HW);
	s5k5baf_i2c_ग_लिखो(state, REG_CLEAR_HOST_INT, 0);
	s5k5baf_i2c_ग_लिखो(state, REG_SW_LOAD_COMPLETE, 1);
	s5k5baf_i2c_ग_लिखो(state, REG_CMDRD_PAGE, PAGE_IF_SW);
	s5k5baf_i2c_ग_लिखो(state, REG_CMDWR_PAGE, PAGE_IF_SW);
पूर्ण

/*
 * V4L2 subdev core and video operations
 */

अटल व्योम s5k5baf_initialize_data(काष्ठा s5k5baf *state)
अणु
	state->pixfmt = 0;
	state->req_fiv = 10000 / 15;
	state->fiv = state->req_fiv;
	state->valid_स्वतः_alg = 0;
पूर्ण

अटल पूर्णांक s5k5baf_load_setfile(काष्ठा s5k5baf *state)
अणु
	काष्ठा i2c_client *c = v4l2_get_subdevdata(&state->sd);
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;

	ret = request_firmware(&fw, S5K5BAF_FW_खाताNAME, &c->dev);
	अगर (ret < 0) अणु
		dev_warn(&c->dev, "firmware file (%s) not loaded\n",
			 S5K5BAF_FW_खाताNAME);
		वापस ret;
	पूर्ण

	ret = s5k5baf_fw_parse(&c->dev, &state->fw, fw->size / 2,
			       (__le16 *)fw->data);

	release_firmware(fw);

	वापस ret;
पूर्ण

अटल पूर्णांक s5k5baf_set_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा s5k5baf *state = to_s5k5baf(sd);
	पूर्णांक ret = 0;

	mutex_lock(&state->lock);

	अगर (state->घातer != !on)
		जाओ out;

	अगर (on) अणु
		अगर (state->fw == शून्य)
			s5k5baf_load_setfile(state);

		s5k5baf_initialize_data(state);
		ret = s5k5baf_घातer_on(state);
		अगर (ret < 0)
			जाओ out;

		s5k5baf_hw_init(state);
		s5k5baf_hw_patch(state);
		s5k5baf_i2c_ग_लिखो(state, REG_SET_HOST_INT, 1);
		s5k5baf_hw_set_घड़ीs(state);

		ret = s5k5baf_hw_set_video_bus(state);
		अगर (ret < 0)
			जाओ out;

		s5k5baf_hw_set_cis(state);
		s5k5baf_hw_set_ccm(state);

		ret = s5k5baf_clear_error(state);
		अगर (!ret)
			state->घातer++;
	पूर्ण अन्यथा अणु
		s5k5baf_घातer_off(state);
		state->घातer--;
	पूर्ण

out:
	mutex_unlock(&state->lock);

	अगर (!ret && on)
		ret = v4l2_ctrl_handler_setup(&state->ctrls.handler);

	वापस ret;
पूर्ण

अटल व्योम s5k5baf_hw_set_stream(काष्ठा s5k5baf *state, पूर्णांक enable)
अणु
	s5k5baf_ग_लिखो_seq(state, REG_G_ENABLE_PREV, enable, 1);
पूर्ण

अटल पूर्णांक s5k5baf_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	काष्ठा s5k5baf *state = to_s5k5baf(sd);
	पूर्णांक ret;

	mutex_lock(&state->lock);

	अगर (state->streaming == !!on) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (on) अणु
		s5k5baf_hw_set_config(state);
		ret = s5k5baf_hw_set_crop_rects(state);
		अगर (ret < 0)
			जाओ out;
		s5k5baf_hw_set_stream(state, 1);
		s5k5baf_i2c_ग_लिखो(state, 0xb0cc, 0x000b);
	पूर्ण अन्यथा अणु
		s5k5baf_hw_set_stream(state, 0);
	पूर्ण
	ret = s5k5baf_clear_error(state);
	अगर (!ret)
		state->streaming = !state->streaming;

out:
	mutex_unlock(&state->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक s5k5baf_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा s5k5baf *state = to_s5k5baf(sd);

	mutex_lock(&state->lock);
	fi->पूर्णांकerval.numerator = state->fiv;
	fi->पूर्णांकerval.denominator = 10000;
	mutex_unlock(&state->lock);

	वापस 0;
पूर्ण

अटल व्योम s5k5baf_set_frame_पूर्णांकerval(काष्ठा s5k5baf *state,
				       काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा v4l2_fract *i = &fi->पूर्णांकerval;

	अगर (fi->पूर्णांकerval.denominator == 0)
		state->req_fiv = S5K5BAF_MAX_FR_TIME;
	अन्यथा
		state->req_fiv = clamp_t(u32,
					 i->numerator * 10000 / i->denominator,
					 S5K5BAF_MIN_FR_TIME,
					 S5K5BAF_MAX_FR_TIME);

	state->fiv = state->req_fiv;
	अगर (state->apply_cfg) अणु
		s5k5baf_hw_set_fiv(state, state->req_fiv);
		s5k5baf_hw_validate_cfg(state);
	पूर्ण
	*i = (काष्ठा v4l2_fract)अणु state->fiv, 10000 पूर्ण;
	अगर (state->fiv == state->req_fiv)
		v4l2_info(&state->sd, "frame interval changed to %d00us\n",
			  state->fiv);
पूर्ण

अटल पूर्णांक s5k5baf_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	काष्ठा s5k5baf *state = to_s5k5baf(sd);

	mutex_lock(&state->lock);
	s5k5baf_set_frame_पूर्णांकerval(state, fi);
	mutex_unlock(&state->lock);
	वापस 0;
पूर्ण

/*
 * V4L2 subdev pad level and video operations
 */
अटल पूर्णांक s5k5baf_क्रमागत_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie)
अणु
	अगर (fie->index > S5K5BAF_MAX_FR_TIME - S5K5BAF_MIN_FR_TIME ||
	    fie->pad != PAD_CIS)
		वापस -EINVAL;

	v4l_bound_align_image(&fie->width, S5K5BAF_WIN_WIDTH_MIN,
			      S5K5BAF_CIS_WIDTH, 1,
			      &fie->height, S5K5BAF_WIN_HEIGHT_MIN,
			      S5K5BAF_CIS_HEIGHT, 1, 0);

	fie->पूर्णांकerval.numerator = S5K5BAF_MIN_FR_TIME + fie->index;
	fie->पूर्णांकerval.denominator = 10000;

	वापस 0;
पूर्ण

अटल पूर्णांक s5k5baf_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (code->pad == PAD_CIS) अणु
		अगर (code->index > 0)
			वापस -EINVAL;
		code->code = MEDIA_BUS_FMT_FIXED;
		वापस 0;
	पूर्ण

	अगर (code->index >= ARRAY_SIZE(s5k5baf_क्रमmats))
		वापस -EINVAL;

	code->code = s5k5baf_क्रमmats[code->index].code;
	वापस 0;
पूर्ण

अटल पूर्णांक s5k5baf_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	पूर्णांक i;

	अगर (fse->index > 0)
		वापस -EINVAL;

	अगर (fse->pad == PAD_CIS) अणु
		fse->code = MEDIA_BUS_FMT_FIXED;
		fse->min_width = S5K5BAF_CIS_WIDTH;
		fse->max_width = S5K5BAF_CIS_WIDTH;
		fse->min_height = S5K5BAF_CIS_HEIGHT;
		fse->max_height = S5K5BAF_CIS_HEIGHT;
		वापस 0;
	पूर्ण

	i = ARRAY_SIZE(s5k5baf_क्रमmats);
	जबतक (--i)
		अगर (fse->code == s5k5baf_क्रमmats[i].code)
			अवरोध;
	fse->code = s5k5baf_क्रमmats[i].code;
	fse->min_width = S5K5BAF_WIN_WIDTH_MIN;
	fse->max_width = S5K5BAF_CIS_WIDTH;
	fse->max_height = S5K5BAF_WIN_HEIGHT_MIN;
	fse->min_height = S5K5BAF_CIS_HEIGHT;

	वापस 0;
पूर्ण

अटल व्योम s5k5baf_try_cis_क्रमmat(काष्ठा v4l2_mbus_framefmt *mf)
अणु
	mf->width = S5K5BAF_CIS_WIDTH;
	mf->height = S5K5BAF_CIS_HEIGHT;
	mf->code = MEDIA_BUS_FMT_FIXED;
	mf->colorspace = V4L2_COLORSPACE_JPEG;
	mf->field = V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक s5k5baf_try_isp_क्रमmat(काष्ठा v4l2_mbus_framefmt *mf)
अणु
	पूर्णांक pixfmt;

	v4l_bound_align_image(&mf->width, S5K5BAF_WIN_WIDTH_MIN,
			      S5K5BAF_CIS_WIDTH, 1,
			      &mf->height, S5K5BAF_WIN_HEIGHT_MIN,
			      S5K5BAF_CIS_HEIGHT, 1, 0);

	pixfmt = s5k5baf_find_pixfmt(mf);

	mf->colorspace = s5k5baf_क्रमmats[pixfmt].colorspace;
	mf->code = s5k5baf_क्रमmats[pixfmt].code;
	mf->field = V4L2_FIELD_NONE;

	वापस pixfmt;
पूर्ण

अटल पूर्णांक s5k5baf_get_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा s5k5baf *state = to_s5k5baf(sd);
	स्थिर काष्ठा s5k5baf_pixfmt *pixfmt;
	काष्ठा v4l2_mbus_framefmt *mf;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad);
		fmt->क्रमmat = *mf;
		वापस 0;
	पूर्ण

	mf = &fmt->क्रमmat;
	अगर (fmt->pad == PAD_CIS) अणु
		s5k5baf_try_cis_क्रमmat(mf);
		वापस 0;
	पूर्ण
	mf->field = V4L2_FIELD_NONE;
	mutex_lock(&state->lock);
	pixfmt = &s5k5baf_क्रमmats[state->pixfmt];
	mf->width = state->crop_source.width;
	mf->height = state->crop_source.height;
	mf->code = pixfmt->code;
	mf->colorspace = pixfmt->colorspace;
	mutex_unlock(&state->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक s5k5baf_set_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_pad_config *cfg,
			  काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा v4l2_mbus_framefmt *mf = &fmt->क्रमmat;
	काष्ठा s5k5baf *state = to_s5k5baf(sd);
	स्थिर काष्ठा s5k5baf_pixfmt *pixfmt;
	पूर्णांक ret = 0;

	mf->field = V4L2_FIELD_NONE;

	अगर (fmt->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		*v4l2_subdev_get_try_क्रमmat(sd, cfg, fmt->pad) = *mf;
		वापस 0;
	पूर्ण

	अगर (fmt->pad == PAD_CIS) अणु
		s5k5baf_try_cis_क्रमmat(mf);
		वापस 0;
	पूर्ण

	mutex_lock(&state->lock);

	अगर (state->streaming) अणु
		mutex_unlock(&state->lock);
		वापस -EBUSY;
	पूर्ण

	state->pixfmt = s5k5baf_try_isp_क्रमmat(mf);
	pixfmt = &s5k5baf_क्रमmats[state->pixfmt];
	mf->code = pixfmt->code;
	mf->colorspace = pixfmt->colorspace;
	mf->width = state->crop_source.width;
	mf->height = state->crop_source.height;

	mutex_unlock(&state->lock);
	वापस ret;
पूर्ण

क्रमागत selection_rect अणु R_CIS, R_CROP_SINK, R_COMPOSE, R_CROP_SOURCE, R_INVALID पूर्ण;

अटल क्रमागत selection_rect s5k5baf_get_sel_rect(u32 pad, u32 target)
अणु
	चयन (target) अणु
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		वापस pad ? R_COMPOSE : R_CIS;
	हाल V4L2_SEL_TGT_CROP:
		वापस pad ? R_CROP_SOURCE : R_CROP_SINK;
	हाल V4L2_SEL_TGT_COMPOSE_BOUNDS:
		वापस pad ? R_INVALID : R_CROP_SINK;
	हाल V4L2_SEL_TGT_COMPOSE:
		वापस pad ? R_INVALID : R_COMPOSE;
	शेष:
		वापस R_INVALID;
	पूर्ण
पूर्ण

अटल पूर्णांक s5k5baf_is_bound_target(u32 target)
अणु
	वापस target == V4L2_SEL_TGT_CROP_BOUNDS ||
		target == V4L2_SEL_TGT_COMPOSE_BOUNDS;
पूर्ण

अटल पूर्णांक s5k5baf_get_selection(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	क्रमागत selection_rect rtype;
	काष्ठा s5k5baf *state = to_s5k5baf(sd);

	rtype = s5k5baf_get_sel_rect(sel->pad, sel->target);

	चयन (rtype) अणु
	हाल R_INVALID:
		वापस -EINVAL;
	हाल R_CIS:
		sel->r = s5k5baf_cis_rect;
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	अगर (sel->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		अगर (rtype == R_COMPOSE)
			sel->r = *v4l2_subdev_get_try_compose(sd, cfg, sel->pad);
		अन्यथा
			sel->r = *v4l2_subdev_get_try_crop(sd, cfg, sel->pad);
		वापस 0;
	पूर्ण

	mutex_lock(&state->lock);
	चयन (rtype) अणु
	हाल R_CROP_SINK:
		sel->r = state->crop_sink;
		अवरोध;
	हाल R_COMPOSE:
		sel->r = state->compose;
		अवरोध;
	हाल R_CROP_SOURCE:
		sel->r = state->crop_source;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (s5k5baf_is_bound_target(sel->target)) अणु
		sel->r.left = 0;
		sel->r.top = 0;
	पूर्ण
	mutex_unlock(&state->lock);

	वापस 0;
पूर्ण

/* bounds range [start, start+len) to [0, max) and aligns to 2 */
अटल व्योम s5k5baf_bound_range(u32 *start, u32 *len, u32 max)
अणु
	अगर (*len > max)
		*len = max;
	अगर (*start + *len > max)
		*start = max - *len;
	*start &= ~1;
	*len &= ~1;
	अगर (*len < S5K5BAF_WIN_WIDTH_MIN)
		*len = S5K5BAF_WIN_WIDTH_MIN;
पूर्ण

अटल व्योम s5k5baf_bound_rect(काष्ठा v4l2_rect *r, u32 width, u32 height)
अणु
	s5k5baf_bound_range(&r->left, &r->width, width);
	s5k5baf_bound_range(&r->top, &r->height, height);
पूर्ण

अटल व्योम s5k5baf_set_rect_and_adjust(काष्ठा v4l2_rect **rects,
					क्रमागत selection_rect first,
					काष्ठा v4l2_rect *v)
अणु
	काष्ठा v4l2_rect *r, *br;
	क्रमागत selection_rect i = first;

	*rects[first] = *v;
	करो अणु
		r = rects[i];
		br = rects[i - 1];
		s5k5baf_bound_rect(r, br->width, br->height);
	पूर्ण जबतक (++i != R_INVALID);
	*v = *rects[first];
पूर्ण

अटल bool s5k5baf_cmp_rect(स्थिर काष्ठा v4l2_rect *r1,
			     स्थिर काष्ठा v4l2_rect *r2)
अणु
	वापस !स_भेद(r1, r2, माप(*r1));
पूर्ण

अटल पूर्णांक s5k5baf_set_selection(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_pad_config *cfg,
				 काष्ठा v4l2_subdev_selection *sel)
अणु
	अटल क्रमागत selection_rect rtype;
	काष्ठा s5k5baf *state = to_s5k5baf(sd);
	काष्ठा v4l2_rect **rects;
	पूर्णांक ret = 0;

	rtype = s5k5baf_get_sel_rect(sel->pad, sel->target);
	अगर (rtype == R_INVALID || s5k5baf_is_bound_target(sel->target))
		वापस -EINVAL;

	/* allow only scaling on compose */
	अगर (rtype == R_COMPOSE) अणु
		sel->r.left = 0;
		sel->r.top = 0;
	पूर्ण

	अगर (sel->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		rects = (काष्ठा v4l2_rect * []) अणु
				&s5k5baf_cis_rect,
				v4l2_subdev_get_try_crop(sd, cfg, PAD_CIS),
				v4l2_subdev_get_try_compose(sd, cfg, PAD_CIS),
				v4l2_subdev_get_try_crop(sd, cfg, PAD_OUT)
			पूर्ण;
		s5k5baf_set_rect_and_adjust(rects, rtype, &sel->r);
		वापस 0;
	पूर्ण

	rects = (काष्ठा v4l2_rect * []) अणु
			&s5k5baf_cis_rect,
			&state->crop_sink,
			&state->compose,
			&state->crop_source
		पूर्ण;
	mutex_lock(&state->lock);
	अगर (state->streaming) अणु
		/* adjust sel->r to aव्योम output resolution change */
		अगर (rtype < R_CROP_SOURCE) अणु
			अगर (sel->r.width < state->crop_source.width)
				sel->r.width = state->crop_source.width;
			अगर (sel->r.height < state->crop_source.height)
				sel->r.height = state->crop_source.height;
		पूर्ण अन्यथा अणु
			sel->r.width = state->crop_source.width;
			sel->r.height = state->crop_source.height;
		पूर्ण
	पूर्ण
	s5k5baf_set_rect_and_adjust(rects, rtype, &sel->r);
	अगर (!s5k5baf_cmp_rect(&state->crop_sink, &s5k5baf_cis_rect) ||
	    !s5k5baf_cmp_rect(&state->compose, &s5k5baf_cis_rect))
		state->apply_crop = 1;
	अगर (state->streaming)
		ret = s5k5baf_hw_set_crop_rects(state);
	mutex_unlock(&state->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops s5k5baf_cis_pad_ops = अणु
	.क्रमागत_mbus_code		= s5k5baf_क्रमागत_mbus_code,
	.क्रमागत_frame_size	= s5k5baf_क्रमागत_frame_size,
	.get_fmt		= s5k5baf_get_fmt,
	.set_fmt		= s5k5baf_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops s5k5baf_pad_ops = अणु
	.क्रमागत_mbus_code		= s5k5baf_क्रमागत_mbus_code,
	.क्रमागत_frame_size	= s5k5baf_क्रमागत_frame_size,
	.क्रमागत_frame_पूर्णांकerval	= s5k5baf_क्रमागत_frame_पूर्णांकerval,
	.get_fmt		= s5k5baf_get_fmt,
	.set_fmt		= s5k5baf_set_fmt,
	.get_selection		= s5k5baf_get_selection,
	.set_selection		= s5k5baf_set_selection,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops s5k5baf_video_ops = अणु
	.g_frame_पूर्णांकerval	= s5k5baf_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval	= s5k5baf_s_frame_पूर्णांकerval,
	.s_stream		= s5k5baf_s_stream,
पूर्ण;

/*
 * V4L2 subdev controls
 */

अटल पूर्णांक s5k5baf_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = ctrl_to_sd(ctrl);
	काष्ठा s5k5baf *state = to_s5k5baf(sd);
	पूर्णांक ret;

	v4l2_dbg(1, debug, sd, "ctrl: %s, value: %d\n", ctrl->name, ctrl->val);

	mutex_lock(&state->lock);

	अगर (state->घातer == 0)
		जाओ unlock;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUTO_WHITE_BALANCE:
		s5k5baf_hw_set_awb(state, ctrl->val);
		अवरोध;

	हाल V4L2_CID_BRIGHTNESS:
		s5k5baf_ग_लिखो(state, REG_USER_BRIGHTNESS, ctrl->val);
		अवरोध;

	हाल V4L2_CID_COLORFX:
		s5k5baf_hw_set_colorfx(state, ctrl->val);
		अवरोध;

	हाल V4L2_CID_CONTRAST:
		s5k5baf_ग_लिखो(state, REG_USER_CONTRAST, ctrl->val);
		अवरोध;

	हाल V4L2_CID_EXPOSURE_AUTO:
		s5k5baf_hw_set_स्वतः_exposure(state, ctrl->val);
		अवरोध;

	हाल V4L2_CID_HFLIP:
		s5k5baf_hw_set_mirror(state);
		अवरोध;

	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		s5k5baf_hw_set_anti_flicker(state, ctrl->val);
		अवरोध;

	हाल V4L2_CID_SATURATION:
		s5k5baf_ग_लिखो(state, REG_USER_SATURATION, ctrl->val);
		अवरोध;

	हाल V4L2_CID_SHARPNESS:
		s5k5baf_ग_लिखो(state, REG_USER_SHARPBLUR, ctrl->val);
		अवरोध;

	हाल V4L2_CID_WHITE_BALANCE_TEMPERATURE:
		s5k5baf_ग_लिखो(state, REG_P_COLORTEMP(0), ctrl->val);
		अगर (state->apply_cfg)
			s5k5baf_hw_sync_cfg(state);
		अवरोध;

	हाल V4L2_CID_TEST_PATTERN:
		s5k5baf_hw_set_test_pattern(state, ctrl->val);
		अवरोध;
	पूर्ण
unlock:
	ret = s5k5baf_clear_error(state);
	mutex_unlock(&state->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops s5k5baf_ctrl_ops = अणु
	.s_ctrl	= s5k5baf_s_ctrl,
पूर्ण;

अटल स्थिर अक्षर * स्थिर s5k5baf_test_pattern_menu[] = अणु
	"Disabled",
	"Blank",
	"Bars",
	"Gradients",
	"Textile",
	"Textile2",
	"Squares"
पूर्ण;

अटल पूर्णांक s5k5baf_initialize_ctrls(काष्ठा s5k5baf *state)
अणु
	स्थिर काष्ठा v4l2_ctrl_ops *ops = &s5k5baf_ctrl_ops;
	काष्ठा s5k5baf_ctrls *ctrls = &state->ctrls;
	काष्ठा v4l2_ctrl_handler *hdl = &ctrls->handler;
	पूर्णांक ret;

	ret = v4l2_ctrl_handler_init(hdl, 16);
	अगर (ret < 0) अणु
		v4l2_err(&state->sd, "cannot init ctrl handler (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* Auto white balance cluster */
	ctrls->awb = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_AUTO_WHITE_BALANCE,
				       0, 1, 1, 1);
	ctrls->gain_red = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_RED_BALANCE,
					    0, 255, 1, S5K5BAF_GAIN_RED_DEF);
	ctrls->gain_blue = v4l2_ctrl_new_std(hdl, ops, V4L2_CID_BLUE_BALANCE,
					     0, 255, 1, S5K5BAF_GAIN_BLUE_DEF);
	v4l2_ctrl_स्वतः_cluster(3, &ctrls->awb, 0, false);

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

	v4l2_ctrl_new_std_menu_items(hdl, ops, V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(s5k5baf_test_pattern_menu) - 1,
				     0, 0, s5k5baf_test_pattern_menu);

	अगर (hdl->error) अणु
		v4l2_err(&state->sd, "error creating controls (%d)\n",
			 hdl->error);
		ret = hdl->error;
		v4l2_ctrl_handler_मुक्त(hdl);
		वापस ret;
	पूर्ण

	state->sd.ctrl_handler = hdl;
	वापस 0;
पूर्ण

/*
 * V4L2 subdev पूर्णांकernal operations
 */
अटल पूर्णांक s5k5baf_खोलो(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh)
अणु
	काष्ठा v4l2_mbus_framefmt *mf;

	mf = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, PAD_CIS);
	s5k5baf_try_cis_क्रमmat(mf);

	अगर (s5k5baf_is_cis_subdev(sd))
		वापस 0;

	mf = v4l2_subdev_get_try_क्रमmat(sd, fh->pad, PAD_OUT);
	mf->colorspace = s5k5baf_क्रमmats[0].colorspace;
	mf->code = s5k5baf_क्रमmats[0].code;
	mf->width = s5k5baf_cis_rect.width;
	mf->height = s5k5baf_cis_rect.height;
	mf->field = V4L2_FIELD_NONE;

	*v4l2_subdev_get_try_crop(sd, fh->pad, PAD_CIS) = s5k5baf_cis_rect;
	*v4l2_subdev_get_try_compose(sd, fh->pad, PAD_CIS) = s5k5baf_cis_rect;
	*v4l2_subdev_get_try_crop(sd, fh->pad, PAD_OUT) = s5k5baf_cis_rect;

	वापस 0;
पूर्ण

अटल पूर्णांक s5k5baf_check_fw_revision(काष्ठा s5k5baf *state)
अणु
	u16 api_ver = 0, fw_rev = 0, s_id = 0;
	पूर्णांक ret;

	api_ver = s5k5baf_पढ़ो(state, REG_FW_APIVER);
	fw_rev = s5k5baf_पढ़ो(state, REG_FW_REVISION) & 0xff;
	s_id = s5k5baf_पढ़ो(state, REG_FW_SENSOR_ID);
	ret = s5k5baf_clear_error(state);
	अगर (ret < 0)
		वापस ret;

	v4l2_info(&state->sd, "FW API=%#x, revision=%#x sensor_id=%#x\n",
		  api_ver, fw_rev, s_id);

	अगर (api_ver != S5K5BAF_FW_APIVER) अणु
		v4l2_err(&state->sd, "FW API version not supported\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s5k5baf_रेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा s5k5baf *state = to_s5k5baf(sd);
	पूर्णांक ret;

	ret = v4l2_device_रेजिस्टर_subdev(sd->v4l2_dev, &state->cis_sd);
	अगर (ret < 0)
		v4l2_err(sd, "failed to register subdev %s\n",
			 state->cis_sd.name);
	अन्यथा
		ret = media_create_pad_link(&state->cis_sd.entity, PAD_CIS,
					       &state->sd.entity, PAD_CIS,
					       MEDIA_LNK_FL_IMMUTABLE |
					       MEDIA_LNK_FL_ENABLED);
	वापस ret;
पूर्ण

अटल व्योम s5k5baf_unरेजिस्टरed(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा s5k5baf *state = to_s5k5baf(sd);
	v4l2_device_unरेजिस्टर_subdev(&state->cis_sd);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_ops s5k5baf_cis_subdev_ops = अणु
	.pad	= &s5k5baf_cis_pad_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops s5k5baf_cis_subdev_पूर्णांकernal_ops = अणु
	.खोलो = s5k5baf_खोलो,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops s5k5baf_subdev_पूर्णांकernal_ops = अणु
	.रेजिस्टरed = s5k5baf_रेजिस्टरed,
	.unरेजिस्टरed = s5k5baf_unरेजिस्टरed,
	.खोलो = s5k5baf_खोलो,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops s5k5baf_core_ops = अणु
	.s_घातer = s5k5baf_set_घातer,
	.log_status = v4l2_ctrl_subdev_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops s5k5baf_subdev_ops = अणु
	.core = &s5k5baf_core_ops,
	.pad = &s5k5baf_pad_ops,
	.video = &s5k5baf_video_ops,
पूर्ण;

अटल पूर्णांक s5k5baf_configure_gpios(काष्ठा s5k5baf *state)
अणु
	अटल स्थिर अक्षर * स्थिर name[] = अणु "S5K5BAF_STBY", "S5K5BAF_RST" पूर्ण;
	काष्ठा i2c_client *c = v4l2_get_subdevdata(&state->sd);
	काष्ठा s5k5baf_gpio *g = state->gpios;
	पूर्णांक ret, i;

	क्रम (i = 0; i < NUM_GPIOS; ++i) अणु
		पूर्णांक flags = GPIOF_सूची_OUT;
		अगर (g[i].level)
			flags |= GPIOF_INIT_HIGH;
		ret = devm_gpio_request_one(&c->dev, g[i].gpio, flags, name[i]);
		अगर (ret < 0) अणु
			v4l2_err(c, "failed to request gpio %s\n", name[i]);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s5k5baf_parse_gpios(काष्ठा s5k5baf_gpio *gpios, काष्ठा device *dev)
अणु
	अटल स्थिर अक्षर * स्थिर names[] = अणु
		"stbyn-gpios",
		"rstn-gpios",
	पूर्ण;
	काष्ठा device_node *node = dev->of_node;
	क्रमागत of_gpio_flags flags;
	पूर्णांक ret, i;

	क्रम (i = 0; i < NUM_GPIOS; ++i) अणु
		ret = of_get_named_gpio_flags(node, names[i], 0, &flags);
		अगर (ret < 0) अणु
			dev_err(dev, "no %s GPIO pin provided\n", names[i]);
			वापस ret;
		पूर्ण
		gpios[i].gpio = ret;
		gpios[i].level = !(flags & OF_GPIO_ACTIVE_LOW);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s5k5baf_parse_device_node(काष्ठा s5k5baf *state, काष्ठा device *dev)
अणु
	काष्ठा device_node *node = dev->of_node;
	काष्ठा device_node *node_ep;
	काष्ठा v4l2_fwnode_endpoपूर्णांक ep = अणु .bus_type = 0 पूर्ण;
	पूर्णांक ret;

	अगर (!node) अणु
		dev_err(dev, "no device-tree node provided\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "clock-frequency",
				   &state->mclk_frequency);
	अगर (ret < 0) अणु
		state->mclk_frequency = S5K5BAF_DEFAULT_MCLK_FREQ;
		dev_info(dev, "using default %u Hz clock frequency\n",
			 state->mclk_frequency);
	पूर्ण

	ret = s5k5baf_parse_gpios(state->gpios, dev);
	अगर (ret < 0)
		वापस ret;

	node_ep = of_graph_get_next_endpoपूर्णांक(node, शून्य);
	अगर (!node_ep) अणु
		dev_err(dev, "no endpoint defined at node %pOF\n", node);
		वापस -EINVAL;
	पूर्ण

	ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(node_ep), &ep);
	of_node_put(node_ep);
	अगर (ret)
		वापस ret;

	state->bus_type = ep.bus_type;

	चयन (state->bus_type) अणु
	हाल V4L2_MBUS_CSI2_DPHY:
		state->nlanes = ep.bus.mipi_csi2.num_data_lanes;
		अवरोध;
	हाल V4L2_MBUS_PARALLEL:
		अवरोध;
	शेष:
		dev_err(dev, "unsupported bus in endpoint defined at node %pOF\n",
			node);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s5k5baf_configure_subdevs(काष्ठा s5k5baf *state,
				     काष्ठा i2c_client *c)
अणु
	काष्ठा v4l2_subdev *sd;
	पूर्णांक ret;

	sd = &state->cis_sd;
	v4l2_subdev_init(sd, &s5k5baf_cis_subdev_ops);
	sd->owner = THIS_MODULE;
	v4l2_set_subdevdata(sd, state);
	snम_लिखो(sd->name, माप(sd->name), "S5K5BAF-CIS %d-%04x",
		 i2c_adapter_id(c->adapter), c->addr);

	sd->पूर्णांकernal_ops = &s5k5baf_cis_subdev_पूर्णांकernal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	state->cis_pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&sd->entity, NUM_CIS_PADS, &state->cis_pad);
	अगर (ret < 0)
		जाओ err;

	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, c, &s5k5baf_subdev_ops);
	snम_लिखो(sd->name, माप(sd->name), "S5K5BAF-ISP %d-%04x",
		 i2c_adapter_id(c->adapter), c->addr);

	sd->पूर्णांकernal_ops = &s5k5baf_subdev_पूर्णांकernal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	state->pads[PAD_CIS].flags = MEDIA_PAD_FL_SINK;
	state->pads[PAD_OUT].flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_V4L2_SUBDEV_UNKNOWN;
	ret = media_entity_pads_init(&sd->entity, NUM_ISP_PADS, state->pads);

	अगर (!ret)
		वापस 0;

	media_entity_cleanup(&state->cis_sd.entity);
err:
	dev_err(&c->dev, "cannot init media entity %s\n", sd->name);
	वापस ret;
पूर्ण

अटल पूर्णांक s5k5baf_configure_regulators(काष्ठा s5k5baf *state)
अणु
	काष्ठा i2c_client *c = v4l2_get_subdevdata(&state->sd);
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < S5K5BAF_NUM_SUPPLIES; i++)
		state->supplies[i].supply = s5k5baf_supply_names[i];

	ret = devm_regulator_bulk_get(&c->dev, S5K5BAF_NUM_SUPPLIES,
				      state->supplies);
	अगर (ret < 0)
		v4l2_err(c, "failed to get regulators\n");
	वापस ret;
पूर्ण

अटल पूर्णांक s5k5baf_probe(काष्ठा i2c_client *c)
अणु
	काष्ठा s5k5baf *state;
	पूर्णांक ret;

	state = devm_kzalloc(&c->dev, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	mutex_init(&state->lock);
	state->crop_sink = s5k5baf_cis_rect;
	state->compose = s5k5baf_cis_rect;
	state->crop_source = s5k5baf_cis_rect;

	ret = s5k5baf_parse_device_node(state, &c->dev);
	अगर (ret < 0)
		वापस ret;

	ret = s5k5baf_configure_subdevs(state, c);
	अगर (ret < 0)
		वापस ret;

	ret = s5k5baf_configure_gpios(state);
	अगर (ret < 0)
		जाओ err_me;

	ret = s5k5baf_configure_regulators(state);
	अगर (ret < 0)
		जाओ err_me;

	state->घड़ी = devm_clk_get(state->sd.dev, S5K5BAF_CLK_NAME);
	अगर (IS_ERR(state->घड़ी)) अणु
		ret = -EPROBE_DEFER;
		जाओ err_me;
	पूर्ण

	ret = s5k5baf_घातer_on(state);
	अगर (ret < 0) अणु
		ret = -EPROBE_DEFER;
		जाओ err_me;
	पूर्ण
	s5k5baf_hw_init(state);
	ret = s5k5baf_check_fw_revision(state);

	s5k5baf_घातer_off(state);
	अगर (ret < 0)
		जाओ err_me;

	ret = s5k5baf_initialize_ctrls(state);
	अगर (ret < 0)
		जाओ err_me;

	ret = v4l2_async_रेजिस्टर_subdev(&state->sd);
	अगर (ret < 0)
		जाओ err_ctrl;

	वापस 0;

err_ctrl:
	v4l2_ctrl_handler_मुक्त(state->sd.ctrl_handler);
err_me:
	media_entity_cleanup(&state->sd.entity);
	media_entity_cleanup(&state->cis_sd.entity);
	वापस ret;
पूर्ण

अटल पूर्णांक s5k5baf_हटाओ(काष्ठा i2c_client *c)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(c);
	काष्ठा s5k5baf *state = to_s5k5baf(sd);

	v4l2_async_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(sd->ctrl_handler);
	media_entity_cleanup(&sd->entity);

	sd = &state->cis_sd;
	v4l2_device_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id s5k5baf_id[] = अणु
	अणु S5K5BAF_DRIVER_NAME, 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, s5k5baf_id);

अटल स्थिर काष्ठा of_device_id s5k5baf_of_match[] = अणु
	अणु .compatible = "samsung,s5k5baf" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, s5k5baf_of_match);

अटल काष्ठा i2c_driver s5k5baf_i2c_driver = अणु
	.driver = अणु
		.of_match_table = s5k5baf_of_match,
		.name = S5K5BAF_DRIVER_NAME
	पूर्ण,
	.probe_new	= s5k5baf_probe,
	.हटाओ		= s5k5baf_हटाओ,
	.id_table	= s5k5baf_id,
पूर्ण;

module_i2c_driver(s5k5baf_i2c_driver);

MODULE_DESCRIPTION("Samsung S5K5BAF(X) UXGA camera driver");
MODULE_AUTHOR("Andrzej Hajda <a.hajda@samsung.com>");
MODULE_LICENSE("GPL v2");
