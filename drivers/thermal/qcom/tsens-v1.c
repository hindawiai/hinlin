<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019, Linaro Limited
 */

#समावेश <linux/bitops.h>
#समावेश <linux/regmap.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश "tsens.h"

/* ----- SROT ------ */
#घोषणा SROT_HW_VER_OFF	0x0000
#घोषणा SROT_CTRL_OFF		0x0004

/* ----- TM ------ */
#घोषणा TM_INT_EN_OFF				0x0000
#घोषणा TM_Sn_UPPER_LOWER_STATUS_CTRL_OFF	0x0004
#घोषणा TM_Sn_STATUS_OFF			0x0044
#घोषणा TM_TRDY_OFF				0x0084
#घोषणा TM_HIGH_LOW_INT_STATUS_OFF		0x0088
#घोषणा TM_HIGH_LOW_Sn_INT_THRESHOLD_OFF	0x0090

/* eeprom layout data क्रम msm8956/76 (v1) */
#घोषणा MSM8976_BASE0_MASK	0xff
#घोषणा MSM8976_BASE1_MASK	0xff
#घोषणा MSM8976_BASE1_SHIFT	8

#घोषणा MSM8976_S0_P1_MASK	0x3f00
#घोषणा MSM8976_S1_P1_MASK	0x3f00000
#घोषणा MSM8976_S2_P1_MASK	0x3f
#घोषणा MSM8976_S3_P1_MASK	0x3f000
#घोषणा MSM8976_S4_P1_MASK	0x3f00
#घोषणा MSM8976_S5_P1_MASK	0x3f00000
#घोषणा MSM8976_S6_P1_MASK	0x3f
#घोषणा MSM8976_S7_P1_MASK	0x3f000
#घोषणा MSM8976_S8_P1_MASK	0x1f8
#घोषणा MSM8976_S9_P1_MASK	0x1f8000
#घोषणा MSM8976_S10_P1_MASK	0xf8000000
#घोषणा MSM8976_S10_P1_MASK_1	0x1

#घोषणा MSM8976_S0_P2_MASK	0xfc000
#घोषणा MSM8976_S1_P2_MASK	0xfc000000
#घोषणा MSM8976_S2_P2_MASK	0xfc0
#घोषणा MSM8976_S3_P2_MASK	0xfc0000
#घोषणा MSM8976_S4_P2_MASK	0xfc000
#घोषणा MSM8976_S5_P2_MASK	0xfc000000
#घोषणा MSM8976_S6_P2_MASK	0xfc0
#घोषणा MSM8976_S7_P2_MASK	0xfc0000
#घोषणा MSM8976_S8_P2_MASK	0x7e00
#घोषणा MSM8976_S9_P2_MASK	0x7e00000
#घोषणा MSM8976_S10_P2_MASK	0x7e

#घोषणा MSM8976_S0_P1_SHIFT	8
#घोषणा MSM8976_S1_P1_SHIFT	20
#घोषणा MSM8976_S2_P1_SHIFT	0
#घोषणा MSM8976_S3_P1_SHIFT	12
#घोषणा MSM8976_S4_P1_SHIFT	8
#घोषणा MSM8976_S5_P1_SHIFT	20
#घोषणा MSM8976_S6_P1_SHIFT	0
#घोषणा MSM8976_S7_P1_SHIFT	12
#घोषणा MSM8976_S8_P1_SHIFT	3
#घोषणा MSM8976_S9_P1_SHIFT	15
#घोषणा MSM8976_S10_P1_SHIFT	27
#घोषणा MSM8976_S10_P1_SHIFT_1	0

#घोषणा MSM8976_S0_P2_SHIFT	14
#घोषणा MSM8976_S1_P2_SHIFT	26
#घोषणा MSM8976_S2_P2_SHIFT	6
#घोषणा MSM8976_S3_P2_SHIFT	18
#घोषणा MSM8976_S4_P2_SHIFT	14
#घोषणा MSM8976_S5_P2_SHIFT	26
#घोषणा MSM8976_S6_P2_SHIFT	6
#घोषणा MSM8976_S7_P2_SHIFT	18
#घोषणा MSM8976_S8_P2_SHIFT	9
#घोषणा MSM8976_S9_P2_SHIFT	21
#घोषणा MSM8976_S10_P2_SHIFT	1

#घोषणा MSM8976_CAL_SEL_MASK	0x3

#घोषणा MSM8976_CAL_DEGC_PT1	30
#घोषणा MSM8976_CAL_DEGC_PT2	120
#घोषणा MSM8976_SLOPE_FACTOR	1000
#घोषणा MSM8976_SLOPE_DEFAULT	3200

/* eeprom layout data क्रम qcs404/405 (v1) */
#घोषणा BASE0_MASK	0x000007f8
#घोषणा BASE1_MASK	0x0007f800
#घोषणा BASE0_SHIFT	3
#घोषणा BASE1_SHIFT	11

#घोषणा S0_P1_MASK	0x0000003f
#घोषणा S1_P1_MASK	0x0003f000
#घोषणा S2_P1_MASK	0x3f000000
#घोषणा S3_P1_MASK	0x000003f0
#घोषणा S4_P1_MASK	0x003f0000
#घोषणा S5_P1_MASK	0x0000003f
#घोषणा S6_P1_MASK	0x0003f000
#घोषणा S7_P1_MASK	0x3f000000
#घोषणा S8_P1_MASK	0x000003f0
#घोषणा S9_P1_MASK	0x003f0000

#घोषणा S0_P2_MASK	0x00000fc0
#घोषणा S1_P2_MASK	0x00fc0000
#घोषणा S2_P2_MASK_1_0	0xc0000000
#घोषणा S2_P2_MASK_5_2	0x0000000f
#घोषणा S3_P2_MASK	0x0000fc00
#घोषणा S4_P2_MASK	0x0fc00000
#घोषणा S5_P2_MASK	0x00000fc0
#घोषणा S6_P2_MASK	0x00fc0000
#घोषणा S7_P2_MASK_1_0	0xc0000000
#घोषणा S7_P2_MASK_5_2	0x0000000f
#घोषणा S8_P2_MASK	0x0000fc00
#घोषणा S9_P2_MASK	0x0fc00000

#घोषणा S0_P1_SHIFT	0
#घोषणा S0_P2_SHIFT	6
#घोषणा S1_P1_SHIFT	12
#घोषणा S1_P2_SHIFT	18
#घोषणा S2_P1_SHIFT	24
#घोषणा S2_P2_SHIFT_1_0	30

#घोषणा S2_P2_SHIFT_5_2	0
#घोषणा S3_P1_SHIFT	4
#घोषणा S3_P2_SHIFT	10
#घोषणा S4_P1_SHIFT	16
#घोषणा S4_P2_SHIFT	22

#घोषणा S5_P1_SHIFT	0
#घोषणा S5_P2_SHIFT	6
#घोषणा S6_P1_SHIFT	12
#घोषणा S6_P2_SHIFT	18
#घोषणा S7_P1_SHIFT	24
#घोषणा S7_P2_SHIFT_1_0	30

#घोषणा S7_P2_SHIFT_5_2	0
#घोषणा S8_P1_SHIFT	4
#घोषणा S8_P2_SHIFT	10
#घोषणा S9_P1_SHIFT	16
#घोषणा S9_P2_SHIFT	22

#घोषणा CAL_SEL_MASK	7
#घोषणा CAL_SEL_SHIFT	0

अटल व्योम compute_पूर्णांकercept_slope_8976(काष्ठा tsens_priv *priv,
			      u32 *p1, u32 *p2, u32 mode)
अणु
	पूर्णांक i;

	priv->sensor[0].slope = 3313;
	priv->sensor[1].slope = 3275;
	priv->sensor[2].slope = 3320;
	priv->sensor[3].slope = 3246;
	priv->sensor[4].slope = 3279;
	priv->sensor[5].slope = 3257;
	priv->sensor[6].slope = 3234;
	priv->sensor[7].slope = 3269;
	priv->sensor[8].slope = 3255;
	priv->sensor[9].slope = 3239;
	priv->sensor[10].slope = 3286;

	क्रम (i = 0; i < priv->num_sensors; i++) अणु
		priv->sensor[i].offset = (p1[i] * MSM8976_SLOPE_FACTOR) -
				(MSM8976_CAL_DEGC_PT1 *
				priv->sensor[i].slope);
	पूर्ण
पूर्ण

अटल पूर्णांक calibrate_v1(काष्ठा tsens_priv *priv)
अणु
	u32 base0 = 0, base1 = 0;
	u32 p1[10], p2[10];
	u32 mode = 0, lsb = 0, msb = 0;
	u32 *qfprom_cdata;
	पूर्णांक i;

	qfprom_cdata = (u32 *)qfprom_पढ़ो(priv->dev, "calib");
	अगर (IS_ERR(qfprom_cdata))
		वापस PTR_ERR(qfprom_cdata);

	mode = (qfprom_cdata[4] & CAL_SEL_MASK) >> CAL_SEL_SHIFT;
	dev_dbg(priv->dev, "calibration mode is %d\n", mode);

	चयन (mode) अणु
	हाल TWO_PT_CALIB:
		base1 = (qfprom_cdata[4] & BASE1_MASK) >> BASE1_SHIFT;
		p2[0] = (qfprom_cdata[0] & S0_P2_MASK) >> S0_P2_SHIFT;
		p2[1] = (qfprom_cdata[0] & S1_P2_MASK) >> S1_P2_SHIFT;
		/* This value is split over two रेजिस्टरs, 2 bits and 4 bits */
		lsb   = (qfprom_cdata[0] & S2_P2_MASK_1_0) >> S2_P2_SHIFT_1_0;
		msb   = (qfprom_cdata[1] & S2_P2_MASK_5_2) >> S2_P2_SHIFT_5_2;
		p2[2] = msb << 2 | lsb;
		p2[3] = (qfprom_cdata[1] & S3_P2_MASK) >> S3_P2_SHIFT;
		p2[4] = (qfprom_cdata[1] & S4_P2_MASK) >> S4_P2_SHIFT;
		p2[5] = (qfprom_cdata[2] & S5_P2_MASK) >> S5_P2_SHIFT;
		p2[6] = (qfprom_cdata[2] & S6_P2_MASK) >> S6_P2_SHIFT;
		/* This value is split over two रेजिस्टरs, 2 bits and 4 bits */
		lsb   = (qfprom_cdata[2] & S7_P2_MASK_1_0) >> S7_P2_SHIFT_1_0;
		msb   = (qfprom_cdata[3] & S7_P2_MASK_5_2) >> S7_P2_SHIFT_5_2;
		p2[7] = msb << 2 | lsb;
		p2[8] = (qfprom_cdata[3] & S8_P2_MASK) >> S8_P2_SHIFT;
		p2[9] = (qfprom_cdata[3] & S9_P2_MASK) >> S9_P2_SHIFT;
		क्रम (i = 0; i < priv->num_sensors; i++)
			p2[i] = ((base1 + p2[i]) << 2);
		fallthrough;
	हाल ONE_PT_CALIB2:
		base0 = (qfprom_cdata[4] & BASE0_MASK) >> BASE0_SHIFT;
		p1[0] = (qfprom_cdata[0] & S0_P1_MASK) >> S0_P1_SHIFT;
		p1[1] = (qfprom_cdata[0] & S1_P1_MASK) >> S1_P1_SHIFT;
		p1[2] = (qfprom_cdata[0] & S2_P1_MASK) >> S2_P1_SHIFT;
		p1[3] = (qfprom_cdata[1] & S3_P1_MASK) >> S3_P1_SHIFT;
		p1[4] = (qfprom_cdata[1] & S4_P1_MASK) >> S4_P1_SHIFT;
		p1[5] = (qfprom_cdata[2] & S5_P1_MASK) >> S5_P1_SHIFT;
		p1[6] = (qfprom_cdata[2] & S6_P1_MASK) >> S6_P1_SHIFT;
		p1[7] = (qfprom_cdata[2] & S7_P1_MASK) >> S7_P1_SHIFT;
		p1[8] = (qfprom_cdata[3] & S8_P1_MASK) >> S8_P1_SHIFT;
		p1[9] = (qfprom_cdata[3] & S9_P1_MASK) >> S9_P1_SHIFT;
		क्रम (i = 0; i < priv->num_sensors; i++)
			p1[i] = (((base0) + p1[i]) << 2);
		अवरोध;
	शेष:
		क्रम (i = 0; i < priv->num_sensors; i++) अणु
			p1[i] = 500;
			p2[i] = 780;
		पूर्ण
		अवरोध;
	पूर्ण

	compute_पूर्णांकercept_slope(priv, p1, p2, mode);
	kमुक्त(qfprom_cdata);

	वापस 0;
पूर्ण

अटल पूर्णांक calibrate_8976(काष्ठा tsens_priv *priv)
अणु
	पूर्णांक base0 = 0, base1 = 0, i;
	u32 p1[11], p2[11];
	पूर्णांक mode = 0, पंचांगp = 0;
	u32 *qfprom_cdata;

	qfprom_cdata = (u32 *)qfprom_पढ़ो(priv->dev, "calib");
	अगर (IS_ERR(qfprom_cdata))
		वापस PTR_ERR(qfprom_cdata);

	mode = (qfprom_cdata[4] & MSM8976_CAL_SEL_MASK);
	dev_dbg(priv->dev, "calibration mode is %d\n", mode);

	चयन (mode) अणु
	हाल TWO_PT_CALIB:
		base1 = (qfprom_cdata[2] & MSM8976_BASE1_MASK) >> MSM8976_BASE1_SHIFT;
		p2[0] = (qfprom_cdata[0] & MSM8976_S0_P2_MASK) >> MSM8976_S0_P2_SHIFT;
		p2[1] = (qfprom_cdata[0] & MSM8976_S1_P2_MASK) >> MSM8976_S1_P2_SHIFT;
		p2[2] = (qfprom_cdata[1] & MSM8976_S2_P2_MASK) >> MSM8976_S2_P2_SHIFT;
		p2[3] = (qfprom_cdata[1] & MSM8976_S3_P2_MASK) >> MSM8976_S3_P2_SHIFT;
		p2[4] = (qfprom_cdata[2] & MSM8976_S4_P2_MASK) >> MSM8976_S4_P2_SHIFT;
		p2[5] = (qfprom_cdata[2] & MSM8976_S5_P2_MASK) >> MSM8976_S5_P2_SHIFT;
		p2[6] = (qfprom_cdata[3] & MSM8976_S6_P2_MASK) >> MSM8976_S6_P2_SHIFT;
		p2[7] = (qfprom_cdata[3] & MSM8976_S7_P2_MASK) >> MSM8976_S7_P2_SHIFT;
		p2[8] = (qfprom_cdata[4] & MSM8976_S8_P2_MASK) >> MSM8976_S8_P2_SHIFT;
		p2[9] = (qfprom_cdata[4] & MSM8976_S9_P2_MASK) >> MSM8976_S9_P2_SHIFT;
		p2[10] = (qfprom_cdata[5] & MSM8976_S10_P2_MASK) >> MSM8976_S10_P2_SHIFT;

		क्रम (i = 0; i < priv->num_sensors; i++)
			p2[i] = ((base1 + p2[i]) << 2);
		fallthrough;
	हाल ONE_PT_CALIB2:
		base0 = qfprom_cdata[0] & MSM8976_BASE0_MASK;
		p1[0] = (qfprom_cdata[0] & MSM8976_S0_P1_MASK) >> MSM8976_S0_P1_SHIFT;
		p1[1] = (qfprom_cdata[0] & MSM8976_S1_P1_MASK) >> MSM8976_S1_P1_SHIFT;
		p1[2] = (qfprom_cdata[1] & MSM8976_S2_P1_MASK) >> MSM8976_S2_P1_SHIFT;
		p1[3] = (qfprom_cdata[1] & MSM8976_S3_P1_MASK) >> MSM8976_S3_P1_SHIFT;
		p1[4] = (qfprom_cdata[2] & MSM8976_S4_P1_MASK) >> MSM8976_S4_P1_SHIFT;
		p1[5] = (qfprom_cdata[2] & MSM8976_S5_P1_MASK) >> MSM8976_S5_P1_SHIFT;
		p1[6] = (qfprom_cdata[3] & MSM8976_S6_P1_MASK) >> MSM8976_S6_P1_SHIFT;
		p1[7] = (qfprom_cdata[3] & MSM8976_S7_P1_MASK) >> MSM8976_S7_P1_SHIFT;
		p1[8] = (qfprom_cdata[4] & MSM8976_S8_P1_MASK) >> MSM8976_S8_P1_SHIFT;
		p1[9] = (qfprom_cdata[4] & MSM8976_S9_P1_MASK) >> MSM8976_S9_P1_SHIFT;
		p1[10] = (qfprom_cdata[4] & MSM8976_S10_P1_MASK) >> MSM8976_S10_P1_SHIFT;
		पंचांगp = (qfprom_cdata[5] & MSM8976_S10_P1_MASK_1) << MSM8976_S10_P1_SHIFT_1;
		p1[10] |= पंचांगp;

		क्रम (i = 0; i < priv->num_sensors; i++)
			p1[i] = (((base0) + p1[i]) << 2);
		अवरोध;
	शेष:
		क्रम (i = 0; i < priv->num_sensors; i++) अणु
			p1[i] = 500;
			p2[i] = 780;
		पूर्ण
		अवरोध;
	पूर्ण

	compute_पूर्णांकercept_slope_8976(priv, p1, p2, mode);
	kमुक्त(qfprom_cdata);

	वापस 0;
पूर्ण

/* v1.x: msm8956,8976,qcs404,405 */

अटल काष्ठा tsens_features tsens_v1_feat = अणु
	.ver_major	= VER_1_X,
	.crit_पूर्णांक	= 0,
	.adc		= 1,
	.srot_split	= 1,
	.max_sensors	= 11,
पूर्ण;

अटल स्थिर काष्ठा reg_field tsens_v1_regfields[MAX_REGFIELDS] = अणु
	/* ----- SROT ------ */
	/* VERSION */
	[VER_MAJOR] = REG_FIELD(SROT_HW_VER_OFF, 28, 31),
	[VER_MINOR] = REG_FIELD(SROT_HW_VER_OFF, 16, 27),
	[VER_STEP]  = REG_FIELD(SROT_HW_VER_OFF,  0, 15),
	/* CTRL_OFFSET */
	[TSENS_EN]     = REG_FIELD(SROT_CTRL_OFF, 0,  0),
	[TSENS_SW_RST] = REG_FIELD(SROT_CTRL_OFF, 1,  1),
	[SENSOR_EN]    = REG_FIELD(SROT_CTRL_OFF, 3, 13),

	/* ----- TM ------ */
	/* INTERRUPT ENABLE */
	[INT_EN]     = REG_FIELD(TM_INT_EN_OFF, 0, 0),

	/* UPPER/LOWER TEMPERATURE THRESHOLDS */
	REG_FIELD_FOR_EACH_SENSOR11(LOW_THRESH,    TM_Sn_UPPER_LOWER_STATUS_CTRL_OFF,  0,  9),
	REG_FIELD_FOR_EACH_SENSOR11(UP_THRESH,     TM_Sn_UPPER_LOWER_STATUS_CTRL_OFF, 10, 19),

	/* UPPER/LOWER INTERRUPTS [CLEAR/STATUS] */
	REG_FIELD_FOR_EACH_SENSOR11(LOW_INT_CLEAR, TM_Sn_UPPER_LOWER_STATUS_CTRL_OFF, 20, 20),
	REG_FIELD_FOR_EACH_SENSOR11(UP_INT_CLEAR,  TM_Sn_UPPER_LOWER_STATUS_CTRL_OFF, 21, 21),
	[LOW_INT_STATUS_0] = REG_FIELD(TM_HIGH_LOW_INT_STATUS_OFF,  0,  0),
	[LOW_INT_STATUS_1] = REG_FIELD(TM_HIGH_LOW_INT_STATUS_OFF,  1,  1),
	[LOW_INT_STATUS_2] = REG_FIELD(TM_HIGH_LOW_INT_STATUS_OFF,  2,  2),
	[LOW_INT_STATUS_3] = REG_FIELD(TM_HIGH_LOW_INT_STATUS_OFF,  3,  3),
	[LOW_INT_STATUS_4] = REG_FIELD(TM_HIGH_LOW_INT_STATUS_OFF,  4,  4),
	[LOW_INT_STATUS_5] = REG_FIELD(TM_HIGH_LOW_INT_STATUS_OFF,  5,  5),
	[LOW_INT_STATUS_6] = REG_FIELD(TM_HIGH_LOW_INT_STATUS_OFF,  6,  6),
	[LOW_INT_STATUS_7] = REG_FIELD(TM_HIGH_LOW_INT_STATUS_OFF,  7,  7),
	[UP_INT_STATUS_0]  = REG_FIELD(TM_HIGH_LOW_INT_STATUS_OFF,  8,  8),
	[UP_INT_STATUS_1]  = REG_FIELD(TM_HIGH_LOW_INT_STATUS_OFF,  9,  9),
	[UP_INT_STATUS_2]  = REG_FIELD(TM_HIGH_LOW_INT_STATUS_OFF, 10, 10),
	[UP_INT_STATUS_3]  = REG_FIELD(TM_HIGH_LOW_INT_STATUS_OFF, 11, 11),
	[UP_INT_STATUS_4]  = REG_FIELD(TM_HIGH_LOW_INT_STATUS_OFF, 12, 12),
	[UP_INT_STATUS_5]  = REG_FIELD(TM_HIGH_LOW_INT_STATUS_OFF, 13, 13),
	[UP_INT_STATUS_6]  = REG_FIELD(TM_HIGH_LOW_INT_STATUS_OFF, 14, 14),
	[UP_INT_STATUS_7]  = REG_FIELD(TM_HIGH_LOW_INT_STATUS_OFF, 15, 15),

	/* NO CRITICAL INTERRUPT SUPPORT on v1 */

	/* Sn_STATUS */
	REG_FIELD_FOR_EACH_SENSOR11(LAST_TEMP,    TM_Sn_STATUS_OFF,  0,  9),
	REG_FIELD_FOR_EACH_SENSOR11(VALID,        TM_Sn_STATUS_OFF, 14, 14),
	/* xxx_STATUS bits: 1 == threshold violated */
	REG_FIELD_FOR_EACH_SENSOR11(MIN_STATUS,   TM_Sn_STATUS_OFF, 10, 10),
	REG_FIELD_FOR_EACH_SENSOR11(LOWER_STATUS, TM_Sn_STATUS_OFF, 11, 11),
	REG_FIELD_FOR_EACH_SENSOR11(UPPER_STATUS, TM_Sn_STATUS_OFF, 12, 12),
	/* No CRITICAL field on v1.x */
	REG_FIELD_FOR_EACH_SENSOR11(MAX_STATUS,   TM_Sn_STATUS_OFF, 13, 13),

	/* TRDY: 1=पढ़ोy, 0=in progress */
	[TRDY] = REG_FIELD(TM_TRDY_OFF, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा tsens_ops ops_generic_v1 = अणु
	.init		= init_common,
	.calibrate	= calibrate_v1,
	.get_temp	= get_temp_tsens_valid,
पूर्ण;

काष्ठा tsens_plat_data data_tsens_v1 = अणु
	.ops		= &ops_generic_v1,
	.feat		= &tsens_v1_feat,
	.fields	= tsens_v1_regfields,
पूर्ण;

अटल स्थिर काष्ठा tsens_ops ops_8976 = अणु
	.init		= init_common,
	.calibrate	= calibrate_8976,
	.get_temp	= get_temp_tsens_valid,
पूर्ण;

/* Valid क्रम both MSM8956 and MSM8976. */
काष्ठा tsens_plat_data data_8976 = अणु
	.num_sensors	= 11,
	.ops		= &ops_8976,
	.hw_ids		= (अचिन्हित पूर्णांक[])अणु0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10पूर्ण,
	.feat		= &tsens_v1_feat,
	.fields		= tsens_v1_regfields,
पूर्ण;
