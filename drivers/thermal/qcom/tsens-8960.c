<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <linux/regmap.h>
#समावेश <linux/thermal.h>
#समावेश "tsens.h"

#घोषणा CONFIG_ADDR		0x3640
#घोषणा CONFIG_ADDR_8660	0x3620
/* CONFIG_ADDR biपंचांगasks */
#घोषणा CONFIG			0x9b
#घोषणा CONFIG_MASK		0xf
#घोषणा CONFIG_8660		1
#घोषणा CONFIG_SHIFT_8660	28
#घोषणा CONFIG_MASK_8660	(3 << CONFIG_SHIFT_8660)

#घोषणा CNTL_ADDR		0x3620
/* CNTL_ADDR biपंचांगasks */
#घोषणा EN			BIT(0)
#घोषणा SW_RST			BIT(1)

#घोषणा MEASURE_PERIOD		BIT(18)
#घोषणा SLP_CLK_ENA		BIT(26)
#घोषणा SLP_CLK_ENA_8660	BIT(24)
#घोषणा SENSOR0_SHIFT		3

#घोषणा THRESHOLD_ADDR		0x3624

#घोषणा INT_STATUS_ADDR		0x363c

#घोषणा S0_STATUS_OFF		0x3628
#घोषणा S1_STATUS_OFF		0x362c
#घोषणा S2_STATUS_OFF		0x3630
#घोषणा S3_STATUS_OFF		0x3634
#घोषणा S4_STATUS_OFF		0x3638
#घोषणा S5_STATUS_OFF		0x3664  /* Sensors 5-10 found on apq8064/msm8960 */
#घोषणा S6_STATUS_OFF		0x3668
#घोषणा S7_STATUS_OFF		0x366c
#घोषणा S8_STATUS_OFF		0x3670
#घोषणा S9_STATUS_OFF		0x3674
#घोषणा S10_STATUS_OFF		0x3678

/* Original slope - 350 to compensate mC to C inaccuracy */
अटल u32 tsens_msm8960_slope[] = अणु
			826, 826, 804, 826,
			761, 782, 782, 849,
			782, 849, 782
			पूर्ण;

अटल पूर्णांक suspend_8960(काष्ठा tsens_priv *priv)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक mask;
	काष्ठा regmap *map = priv->पंचांग_map;

	ret = regmap_पढ़ो(map, THRESHOLD_ADDR, &priv->ctx.threshold);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(map, CNTL_ADDR, &priv->ctx.control);
	अगर (ret)
		वापस ret;

	अगर (priv->num_sensors > 1)
		mask = SLP_CLK_ENA | EN;
	अन्यथा
		mask = SLP_CLK_ENA_8660 | EN;

	ret = regmap_update_bits(map, CNTL_ADDR, mask, 0);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक resume_8960(काष्ठा tsens_priv *priv)
अणु
	पूर्णांक ret;
	काष्ठा regmap *map = priv->पंचांग_map;

	ret = regmap_update_bits(map, CNTL_ADDR, SW_RST, SW_RST);
	अगर (ret)
		वापस ret;

	/*
	 * Separate CONFIG restore is not needed only क्रम 8660 as
	 * config is part of CTRL Addr and its restored as such
	 */
	अगर (priv->num_sensors > 1) अणु
		ret = regmap_update_bits(map, CONFIG_ADDR, CONFIG_MASK, CONFIG);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(map, THRESHOLD_ADDR, priv->ctx.threshold);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(map, CNTL_ADDR, priv->ctx.control);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक enable_8960(काष्ठा tsens_priv *priv, पूर्णांक id)
अणु
	पूर्णांक ret;
	u32 reg, mask = BIT(id);

	ret = regmap_पढ़ो(priv->पंचांग_map, CNTL_ADDR, &reg);
	अगर (ret)
		वापस ret;

	/* HARDWARE BUG:
	 * On platक्रमms with more than 6 sensors, all reमुख्यing sensors
	 * must be enabled together, otherwise undefined results are expected.
	 * (Sensor 6-7 disabled, Sensor 3 disabled...) In the original driver,
	 * all the sensors are enabled in one step hence this bug is not
	 * triggered.
	 */
	अगर (id > 5)
		mask = GENMASK(10, 6);

	mask <<= SENSOR0_SHIFT;

	/* Sensors alपढ़ोy enabled. Skip. */
	अगर ((reg & mask) == mask)
		वापस 0;

	ret = regmap_ग_लिखो(priv->पंचांग_map, CNTL_ADDR, reg | SW_RST);
	अगर (ret)
		वापस ret;

	reg |= MEASURE_PERIOD;

	अगर (priv->num_sensors > 1)
		reg |= mask | SLP_CLK_ENA | EN;
	अन्यथा
		reg |= mask | SLP_CLK_ENA_8660 | EN;

	ret = regmap_ग_लिखो(priv->पंचांग_map, CNTL_ADDR, reg);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम disable_8960(काष्ठा tsens_priv *priv)
अणु
	पूर्णांक ret;
	u32 reg_cntl;
	u32 mask;

	mask = GENMASK(priv->num_sensors - 1, 0);
	mask <<= SENSOR0_SHIFT;
	mask |= EN;

	ret = regmap_पढ़ो(priv->पंचांग_map, CNTL_ADDR, &reg_cntl);
	अगर (ret)
		वापस;

	reg_cntl &= ~mask;

	अगर (priv->num_sensors > 1)
		reg_cntl &= ~SLP_CLK_ENA;
	अन्यथा
		reg_cntl &= ~SLP_CLK_ENA_8660;

	regmap_ग_लिखो(priv->पंचांग_map, CNTL_ADDR, reg_cntl);
पूर्ण

अटल पूर्णांक calibrate_8960(काष्ठा tsens_priv *priv)
अणु
	पूर्णांक i;
	अक्षर *data;
	u32 p1[11];

	data = qfprom_पढ़ो(priv->dev, "calib");
	अगर (IS_ERR(data))
		data = qfprom_पढ़ो(priv->dev, "calib_backup");
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	क्रम (i = 0; i < priv->num_sensors; i++) अणु
		p1[i] = data[i];
		priv->sensor[i].slope = tsens_msm8960_slope[i];
	पूर्ण

	compute_पूर्णांकercept_slope(priv, p1, शून्य, ONE_PT_CALIB);

	kमुक्त(data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reg_field tsens_8960_regfields[MAX_REGFIELDS] = अणु
	/* ----- SROT ------ */
	/* No VERSION inक्रमmation */

	/* CNTL */
	[TSENS_EN]     = REG_FIELD(CNTL_ADDR,  0, 0),
	[TSENS_SW_RST] = REG_FIELD(CNTL_ADDR,  1, 1),
	/* 8960 has 5 sensors, 8660 has 11, we only handle 5 */
	[SENSOR_EN]    = REG_FIELD(CNTL_ADDR,  3, 7),

	/* ----- TM ------ */
	/* INTERRUPT ENABLE */
	/* NO INTERRUPT ENABLE */

	/* Single UPPER/LOWER TEMPERATURE THRESHOLD क्रम all sensors */
	[LOW_THRESH_0]   = REG_FIELD(THRESHOLD_ADDR,  0,  7),
	[UP_THRESH_0]    = REG_FIELD(THRESHOLD_ADDR,  8, 15),
	/* MIN_THRESH_0 and MAX_THRESH_0 are not present in the regfield
	 * Recycle CRIT_THRESH_0 and 1 to set the required regs to hardcoded temp
	 * MIN_THRESH_0 -> CRIT_THRESH_1
	 * MAX_THRESH_0 -> CRIT_THRESH_0
	 */
	[CRIT_THRESH_1]   = REG_FIELD(THRESHOLD_ADDR, 16, 23),
	[CRIT_THRESH_0]   = REG_FIELD(THRESHOLD_ADDR, 24, 31),

	/* UPPER/LOWER INTERRUPT [CLEAR/STATUS] */
	/* 1 == clear, 0 == normal operation */
	[LOW_INT_CLEAR_0]   = REG_FIELD(CNTL_ADDR,  9,  9),
	[UP_INT_CLEAR_0]    = REG_FIELD(CNTL_ADDR, 10, 10),

	/* NO CRITICAL INTERRUPT SUPPORT on 8960 */

	/* Sn_STATUS */
	[LAST_TEMP_0]  = REG_FIELD(S0_STATUS_OFF,  0,  7),
	[LAST_TEMP_1]  = REG_FIELD(S1_STATUS_OFF,  0,  7),
	[LAST_TEMP_2]  = REG_FIELD(S2_STATUS_OFF,  0,  7),
	[LAST_TEMP_3]  = REG_FIELD(S3_STATUS_OFF,  0,  7),
	[LAST_TEMP_4]  = REG_FIELD(S4_STATUS_OFF,  0,  7),
	[LAST_TEMP_5]  = REG_FIELD(S5_STATUS_OFF,  0,  7),
	[LAST_TEMP_6]  = REG_FIELD(S6_STATUS_OFF,  0,  7),
	[LAST_TEMP_7]  = REG_FIELD(S7_STATUS_OFF,  0,  7),
	[LAST_TEMP_8]  = REG_FIELD(S8_STATUS_OFF,  0,  7),
	[LAST_TEMP_9]  = REG_FIELD(S9_STATUS_OFF,  0,  7),
	[LAST_TEMP_10] = REG_FIELD(S10_STATUS_OFF, 0,  7),

	/* No VALID field on 8960 */
	/* TSENS_INT_STATUS bits: 1 == threshold violated */
	[MIN_STATUS_0] = REG_FIELD(INT_STATUS_ADDR, 0, 0),
	[LOWER_STATUS_0] = REG_FIELD(INT_STATUS_ADDR, 1, 1),
	[UPPER_STATUS_0] = REG_FIELD(INT_STATUS_ADDR, 2, 2),
	/* No CRITICAL field on 8960 */
	[MAX_STATUS_0] = REG_FIELD(INT_STATUS_ADDR, 3, 3),

	/* TRDY: 1=पढ़ोy, 0=in progress */
	[TRDY] = REG_FIELD(INT_STATUS_ADDR, 7, 7),
पूर्ण;

अटल स्थिर काष्ठा tsens_ops ops_8960 = अणु
	.init		= init_common,
	.calibrate	= calibrate_8960,
	.get_temp	= get_temp_common,
	.enable		= enable_8960,
	.disable	= disable_8960,
	.suspend	= suspend_8960,
	.resume		= resume_8960,
पूर्ण;

अटल काष्ठा tsens_features tsens_8960_feat = अणु
	.ver_major	= VER_0,
	.crit_पूर्णांक	= 0,
	.adc		= 1,
	.srot_split	= 0,
	.max_sensors	= 11,
पूर्ण;

काष्ठा tsens_plat_data data_8960 = अणु
	.num_sensors	= 11,
	.ops		= &ops_8960,
	.feat		= &tsens_8960_feat,
	.fields		= tsens_8960_regfields,
पूर्ण;
