<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/media/i2c/ccs/ccs-quirk.c
 *
 * Generic driver क्रम MIPI CCS/SMIA/SMIA++ compliant camera sensors
 *
 * Copyright (C) 2020 Intel Corporation
 * Copyright (C) 2011--2012 Nokia Corporation
 * Contact: Sakari Ailus <sakari.ailus@linux.पूर्णांकel.com>
 */

#समावेश <linux/delay.h>

#समावेश "ccs.h"
#समावेश "ccs-limits.h"

अटल पूर्णांक ccs_ग_लिखो_addr_8s(काष्ठा ccs_sensor *sensor,
			     स्थिर काष्ठा ccs_reg_8 *regs, पूर्णांक len)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	पूर्णांक rval;

	क्रम (; len > 0; len--, regs++) अणु
		rval = ccs_ग_लिखो_addr(sensor, regs->reg, regs->val);
		अगर (rval < 0) अणु
			dev_err(&client->dev,
				"error %d writing reg 0x%4.4x, val 0x%2.2x",
				rval, regs->reg, regs->val);
			वापस rval;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jt8ew9_limits(काष्ठा ccs_sensor *sensor)
अणु
	अगर (sensor->minfo.revision_number < 0x0300)
		sensor->frame_skip = 1;

	/* Below 24 gain करोesn't have effect at all, */
	/* but ~59 is needed क्रम full dynamic range */
	ccs_replace_limit(sensor, CCS_L_ANALOG_GAIN_CODE_MIN, 0, 59);
	ccs_replace_limit(sensor, CCS_L_ANALOG_GAIN_CODE_MAX, 0, 6000);

	वापस 0;
पूर्ण

अटल पूर्णांक jt8ew9_post_घातeron(काष्ठा ccs_sensor *sensor)
अणु
	अटल स्थिर काष्ठा ccs_reg_8 regs[] = अणु
		अणु 0x30a3, 0xd8 पूर्ण, /* Output port control : LVDS ports only */
		अणु 0x30ae, 0x00 पूर्ण, /* 0x0307 pll_multiplier maximum value on PLL input 9.6MHz ( 19.2MHz is भागided on pre_pll_भाग) */
		अणु 0x30af, 0xd0 पूर्ण, /* 0x0307 pll_multiplier maximum value on PLL input 9.6MHz ( 19.2MHz is भागided on pre_pll_भाग) */
		अणु 0x322d, 0x04 पूर्ण, /* Adjusting Processing Image Size to Scaler Toshiba Recommendation Setting */
		अणु 0x3255, 0x0f पूर्ण, /* Horizontal Noise Reduction Control Toshiba Recommendation Setting */
		अणु 0x3256, 0x15 पूर्ण, /* Horizontal Noise Reduction Control Toshiba Recommendation Setting */
		अणु 0x3258, 0x70 पूर्ण, /* Analog Gain Control Toshiba Recommendation Setting */
		अणु 0x3259, 0x70 पूर्ण, /* Analog Gain Control Toshiba Recommendation Setting */
		अणु 0x325f, 0x7c पूर्ण, /* Analog Gain Control Toshiba Recommendation Setting */
		अणु 0x3302, 0x06 पूर्ण, /* Pixel Reference Voltage Control Toshiba Recommendation Setting */
		अणु 0x3304, 0x00 पूर्ण, /* Pixel Reference Voltage Control Toshiba Recommendation Setting */
		अणु 0x3307, 0x22 पूर्ण, /* Pixel Reference Voltage Control Toshiba Recommendation Setting */
		अणु 0x3308, 0x8d पूर्ण, /* Pixel Reference Voltage Control Toshiba Recommendation Setting */
		अणु 0x331e, 0x0f पूर्ण, /* Black Hole Sun Correction Control Toshiba Recommendation Setting */
		अणु 0x3320, 0x30 पूर्ण, /* Black Hole Sun Correction Control Toshiba Recommendation Setting */
		अणु 0x3321, 0x11 पूर्ण, /* Black Hole Sun Correction Control Toshiba Recommendation Setting */
		अणु 0x3322, 0x98 पूर्ण, /* Black Hole Sun Correction Control Toshiba Recommendation Setting */
		अणु 0x3323, 0x64 पूर्ण, /* Black Hole Sun Correction Control Toshiba Recommendation Setting */
		अणु 0x3325, 0x83 पूर्ण, /* Read Out Timing Control Toshiba Recommendation Setting */
		अणु 0x3330, 0x18 पूर्ण, /* Read Out Timing Control Toshiba Recommendation Setting */
		अणु 0x333c, 0x01 पूर्ण, /* Read Out Timing Control Toshiba Recommendation Setting */
		अणु 0x3345, 0x2f पूर्ण, /* Black Hole Sun Correction Control Toshiba Recommendation Setting */
		अणु 0x33de, 0x38 पूर्ण, /* Horizontal Noise Reduction Control Toshiba Recommendation Setting */
		/* Taken from v03. No idea what the rest are. */
		अणु 0x32e0, 0x05 पूर्ण,
		अणु 0x32e1, 0x05 पूर्ण,
		अणु 0x32e2, 0x04 पूर्ण,
		अणु 0x32e5, 0x04 पूर्ण,
		अणु 0x32e6, 0x04 पूर्ण,

	पूर्ण;

	वापस ccs_ग_लिखो_addr_8s(sensor, regs, ARRAY_SIZE(regs));
पूर्ण

स्थिर काष्ठा ccs_quirk smiapp_jt8ew9_quirk = अणु
	.limits = jt8ew9_limits,
	.post_घातeron = jt8ew9_post_घातeron,
पूर्ण;

अटल पूर्णांक imx125es_post_घातeron(काष्ठा ccs_sensor *sensor)
अणु
	/* Taken from v02. No idea what the other two are. */
	अटल स्थिर काष्ठा ccs_reg_8 regs[] = अणु
		/*
		 * 0x3302: clk during frame blanking:
		 * 0x00 - HS mode, 0x01 - LP11
		 */
		अणु 0x3302, 0x01 पूर्ण,
		अणु 0x302d, 0x00 पूर्ण,
		अणु 0x3b08, 0x8c पूर्ण,
	पूर्ण;

	वापस ccs_ग_लिखो_addr_8s(sensor, regs, ARRAY_SIZE(regs));
पूर्ण

स्थिर काष्ठा ccs_quirk smiapp_imx125es_quirk = अणु
	.post_घातeron = imx125es_post_घातeron,
पूर्ण;

अटल पूर्णांक jt8ev1_limits(काष्ठा ccs_sensor *sensor)
अणु
	ccs_replace_limit(sensor, CCS_L_X_ADDR_MAX, 0, 4271);
	ccs_replace_limit(sensor, CCS_L_MIN_LINE_BLANKING_PCK_BIN, 0, 184);

	वापस 0;
पूर्ण

अटल पूर्णांक jt8ev1_post_घातeron(काष्ठा ccs_sensor *sensor)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	पूर्णांक rval;
	अटल स्थिर काष्ठा ccs_reg_8 regs[] = अणु
		अणु 0x3031, 0xcd पूर्ण, /* For digital binning (EQ_MONI) */
		अणु 0x30a3, 0xd0 पूर्ण, /* FLASH STROBE enable */
		अणु 0x3237, 0x00 पूर्ण, /* For control of pulse timing क्रम ADC */
		अणु 0x3238, 0x43 पूर्ण,
		अणु 0x3301, 0x06 पूर्ण, /* For analog bias क्रम sensor */
		अणु 0x3302, 0x06 पूर्ण,
		अणु 0x3304, 0x00 पूर्ण,
		अणु 0x3305, 0x88 पूर्ण,
		अणु 0x332a, 0x14 पूर्ण,
		अणु 0x332c, 0x6b पूर्ण,
		अणु 0x3336, 0x01 पूर्ण,
		अणु 0x333f, 0x1f पूर्ण,
		अणु 0x3355, 0x00 पूर्ण,
		अणु 0x3356, 0x20 पूर्ण,
		अणु 0x33bf, 0x20 पूर्ण, /* Adjust the FBC speed */
		अणु 0x33c9, 0x20 पूर्ण,
		अणु 0x33ce, 0x30 पूर्ण, /* Adjust the parameter क्रम logic function */
		अणु 0x33cf, 0xec पूर्ण, /* For Black sun */
		अणु 0x3328, 0x80 पूर्ण, /* Ugh. No idea what's this. */
	पूर्ण;
	अटल स्थिर काष्ठा ccs_reg_8 regs_96[] = अणु
		अणु 0x30ae, 0x00 पूर्ण, /* For control of ADC घड़ी */
		अणु 0x30af, 0xd0 पूर्ण,
		अणु 0x30b0, 0x01 पूर्ण,
	पूर्ण;

	rval = ccs_ग_लिखो_addr_8s(sensor, regs, ARRAY_SIZE(regs));
	अगर (rval < 0)
		वापस rval;

	चयन (sensor->hwcfg.ext_clk) अणु
	हाल 9600000:
		वापस ccs_ग_लिखो_addr_8s(sensor, regs_96,
				       ARRAY_SIZE(regs_96));
	शेष:
		dev_warn(&client->dev, "no MSRs for %d Hz ext_clk\n",
			 sensor->hwcfg.ext_clk);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक jt8ev1_pre_streamon(काष्ठा ccs_sensor *sensor)
अणु
	वापस ccs_ग_लिखो_addr(sensor, 0x3328, 0x00);
पूर्ण

अटल पूर्णांक jt8ev1_post_streamoff(काष्ठा ccs_sensor *sensor)
अणु
	पूर्णांक rval;

	/* Workaround: allows fast standby to work properly */
	rval = ccs_ग_लिखो_addr(sensor, 0x3205, 0x04);
	अगर (rval < 0)
		वापस rval;

	/* Wait क्रम 1 ms + one line => 2 ms is likely enough */
	usleep_range(2000, 2050);

	/* Restore it */
	rval = ccs_ग_लिखो_addr(sensor, 0x3205, 0x00);
	अगर (rval < 0)
		वापस rval;

	वापस ccs_ग_लिखो_addr(sensor, 0x3328, 0x80);
पूर्ण

अटल पूर्णांक jt8ev1_init(काष्ठा ccs_sensor *sensor)
अणु
	sensor->pll.flags |= CCS_PLL_FLAG_LANE_SPEED_MODEL |
		CCS_PLL_FLAG_LINK_DECOUPLED;
	sensor->pll.vt_lanes = 1;
	sensor->pll.op_lanes = sensor->pll.csi2.lanes;

	वापस 0;
पूर्ण

स्थिर काष्ठा ccs_quirk smiapp_jt8ev1_quirk = अणु
	.limits = jt8ev1_limits,
	.post_घातeron = jt8ev1_post_घातeron,
	.pre_streamon = jt8ev1_pre_streamon,
	.post_streamoff = jt8ev1_post_streamoff,
	.init = jt8ev1_init,
पूर्ण;

अटल पूर्णांक tcm8500md_limits(काष्ठा ccs_sensor *sensor)
अणु
	ccs_replace_limit(sensor, CCS_L_MIN_PLL_IP_CLK_FREQ_MHZ, 0, 2700000);

	वापस 0;
पूर्ण

स्थिर काष्ठा ccs_quirk smiapp_tcm8500md_quirk = अणु
	.limits = tcm8500md_limits,
पूर्ण;
