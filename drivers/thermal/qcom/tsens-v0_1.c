<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश "tsens.h"

/* ----- SROT ------ */
#घोषणा SROT_CTRL_OFF 0x0000

/* ----- TM ------ */
#घोषणा TM_INT_EN_OFF				0x0000
#घोषणा TM_Sn_UPPER_LOWER_STATUS_CTRL_OFF	0x0004
#घोषणा TM_Sn_STATUS_OFF			0x0030
#घोषणा TM_TRDY_OFF				0x005c

/* eeprom layout data क्रम 8916 */
#घोषणा MSM8916_BASE0_MASK	0x0000007f
#घोषणा MSM8916_BASE1_MASK	0xfe000000
#घोषणा MSM8916_BASE0_SHIFT	0
#घोषणा MSM8916_BASE1_SHIFT	25

#घोषणा MSM8916_S0_P1_MASK	0x00000f80
#घोषणा MSM8916_S1_P1_MASK	0x003e0000
#घोषणा MSM8916_S2_P1_MASK	0xf8000000
#घोषणा MSM8916_S3_P1_MASK	0x000003e0
#घोषणा MSM8916_S4_P1_MASK	0x000f8000

#घोषणा MSM8916_S0_P2_MASK	0x0001f000
#घोषणा MSM8916_S1_P2_MASK	0x07c00000
#घोषणा MSM8916_S2_P2_MASK	0x0000001f
#घोषणा MSM8916_S3_P2_MASK	0x00007c00
#घोषणा MSM8916_S4_P2_MASK	0x01f00000

#घोषणा MSM8916_S0_P1_SHIFT	7
#घोषणा MSM8916_S1_P1_SHIFT	17
#घोषणा MSM8916_S2_P1_SHIFT	27
#घोषणा MSM8916_S3_P1_SHIFT	5
#घोषणा MSM8916_S4_P1_SHIFT	15

#घोषणा MSM8916_S0_P2_SHIFT	12
#घोषणा MSM8916_S1_P2_SHIFT	22
#घोषणा MSM8916_S2_P2_SHIFT	0
#घोषणा MSM8916_S3_P2_SHIFT	10
#घोषणा MSM8916_S4_P2_SHIFT	20

#घोषणा MSM8916_CAL_SEL_MASK	0xe0000000
#घोषणा MSM8916_CAL_SEL_SHIFT	29

/* eeprom layout data क्रम 8939 */
#घोषणा MSM8939_BASE0_MASK	0x000000ff
#घोषणा MSM8939_BASE1_MASK	0xff000000
#घोषणा MSM8939_BASE0_SHIFT	0
#घोषणा MSM8939_BASE1_SHIFT	24

#घोषणा MSM8939_S0_P1_MASK	0x000001f8
#घोषणा MSM8939_S1_P1_MASK	0x001f8000
#घोषणा MSM8939_S2_P1_MASK_0_4	0xf8000000
#घोषणा MSM8939_S2_P1_MASK_5	0x00000001
#घोषणा MSM8939_S3_P1_MASK	0x00001f80
#घोषणा MSM8939_S4_P1_MASK	0x01f80000
#घोषणा MSM8939_S5_P1_MASK	0x00003f00
#घोषणा MSM8939_S6_P1_MASK	0x03f00000
#घोषणा MSM8939_S7_P1_MASK	0x0000003f
#घोषणा MSM8939_S8_P1_MASK	0x0003f000
#घोषणा MSM8939_S9_P1_MASK	0x07e00000

#घोषणा MSM8939_S0_P2_MASK	0x00007e00
#घोषणा MSM8939_S1_P2_MASK	0x07e00000
#घोषणा MSM8939_S2_P2_MASK	0x0000007e
#घोषणा MSM8939_S3_P2_MASK	0x0007e000
#घोषणा MSM8939_S4_P2_MASK	0x7e000000
#घोषणा MSM8939_S5_P2_MASK	0x000fc000
#घोषणा MSM8939_S6_P2_MASK	0xfc000000
#घोषणा MSM8939_S7_P2_MASK	0x00000fc0
#घोषणा MSM8939_S8_P2_MASK	0x00fc0000
#घोषणा MSM8939_S9_P2_MASK_0_4	0xf8000000
#घोषणा MSM8939_S9_P2_MASK_5	0x00002000

#घोषणा MSM8939_S0_P1_SHIFT	3
#घोषणा MSM8939_S1_P1_SHIFT	15
#घोषणा MSM8939_S2_P1_SHIFT_0_4	27
#घोषणा MSM8939_S2_P1_SHIFT_5	0
#घोषणा MSM8939_S3_P1_SHIFT	7
#घोषणा MSM8939_S4_P1_SHIFT	19
#घोषणा MSM8939_S5_P1_SHIFT	8
#घोषणा MSM8939_S6_P1_SHIFT	20
#घोषणा MSM8939_S7_P1_SHIFT	0
#घोषणा MSM8939_S8_P1_SHIFT	12
#घोषणा MSM8939_S9_P1_SHIFT	21

#घोषणा MSM8939_S0_P2_SHIFT	9
#घोषणा MSM8939_S1_P2_SHIFT	21
#घोषणा MSM8939_S2_P2_SHIFT	1
#घोषणा MSM8939_S3_P2_SHIFT	13
#घोषणा MSM8939_S4_P2_SHIFT	25
#घोषणा MSM8939_S5_P2_SHIFT	14
#घोषणा MSM8939_S6_P2_SHIFT	26
#घोषणा MSM8939_S7_P2_SHIFT	6
#घोषणा MSM8939_S8_P2_SHIFT	18
#घोषणा MSM8939_S9_P2_SHIFT_0_4	27
#घोषणा MSM8939_S9_P2_SHIFT_5	13

#घोषणा MSM8939_CAL_SEL_MASK	0x7
#घोषणा MSM8939_CAL_SEL_SHIFT	0

/* eeprom layout data क्रम 8974 */
#घोषणा BASE1_MASK		0xff
#घोषणा S0_P1_MASK		0x3f00
#घोषणा S1_P1_MASK		0xfc000
#घोषणा S2_P1_MASK		0x3f00000
#घोषणा S3_P1_MASK		0xfc000000
#घोषणा S4_P1_MASK		0x3f
#घोषणा S5_P1_MASK		0xfc0
#घोषणा S6_P1_MASK		0x3f000
#घोषणा S7_P1_MASK		0xfc0000
#घोषणा S8_P1_MASK		0x3f000000
#घोषणा S8_P1_MASK_BKP		0x3f
#घोषणा S9_P1_MASK		0x3f
#घोषणा S9_P1_MASK_BKP		0xfc0
#घोषणा S10_P1_MASK		0xfc0
#घोषणा S10_P1_MASK_BKP		0x3f000
#घोषणा CAL_SEL_0_1		0xc0000000
#घोषणा CAL_SEL_2		0x40000000
#घोषणा CAL_SEL_SHIFT		30
#घोषणा CAL_SEL_SHIFT_2		28

#घोषणा S0_P1_SHIFT		8
#घोषणा S1_P1_SHIFT		14
#घोषणा S2_P1_SHIFT		20
#घोषणा S3_P1_SHIFT		26
#घोषणा S5_P1_SHIFT		6
#घोषणा S6_P1_SHIFT		12
#घोषणा S7_P1_SHIFT		18
#घोषणा S8_P1_SHIFT		24
#घोषणा S9_P1_BKP_SHIFT		6
#घोषणा S10_P1_SHIFT		6
#घोषणा S10_P1_BKP_SHIFT	12

#घोषणा BASE2_SHIFT		12
#घोषणा BASE2_BKP_SHIFT		18
#घोषणा S0_P2_SHIFT		20
#घोषणा S0_P2_BKP_SHIFT		26
#घोषणा S1_P2_SHIFT		26
#घोषणा S2_P2_BKP_SHIFT		6
#घोषणा S3_P2_SHIFT		6
#घोषणा S3_P2_BKP_SHIFT		12
#घोषणा S4_P2_SHIFT		12
#घोषणा S4_P2_BKP_SHIFT		18
#घोषणा S5_P2_SHIFT		18
#घोषणा S5_P2_BKP_SHIFT		24
#घोषणा S6_P2_SHIFT		24
#घोषणा S7_P2_BKP_SHIFT		6
#घोषणा S8_P2_SHIFT		6
#घोषणा S8_P2_BKP_SHIFT		12
#घोषणा S9_P2_SHIFT		12
#घोषणा S9_P2_BKP_SHIFT		18
#घोषणा S10_P2_SHIFT		18
#घोषणा S10_P2_BKP_SHIFT	24

#घोषणा BASE2_MASK		0xff000
#घोषणा BASE2_BKP_MASK		0xfc0000
#घोषणा S0_P2_MASK		0x3f00000
#घोषणा S0_P2_BKP_MASK		0xfc000000
#घोषणा S1_P2_MASK		0xfc000000
#घोषणा S1_P2_BKP_MASK		0x3f
#घोषणा S2_P2_MASK		0x3f
#घोषणा S2_P2_BKP_MASK		0xfc0
#घोषणा S3_P2_MASK		0xfc0
#घोषणा S3_P2_BKP_MASK		0x3f000
#घोषणा S4_P2_MASK		0x3f000
#घोषणा S4_P2_BKP_MASK		0xfc0000
#घोषणा S5_P2_MASK		0xfc0000
#घोषणा S5_P2_BKP_MASK		0x3f000000
#घोषणा S6_P2_MASK		0x3f000000
#घोषणा S6_P2_BKP_MASK		0x3f
#घोषणा S7_P2_MASK		0x3f
#घोषणा S7_P2_BKP_MASK		0xfc0
#घोषणा S8_P2_MASK		0xfc0
#घोषणा S8_P2_BKP_MASK		0x3f000
#घोषणा S9_P2_MASK		0x3f000
#घोषणा S9_P2_BKP_MASK		0xfc0000
#घोषणा S10_P2_MASK		0xfc0000
#घोषणा S10_P2_BKP_MASK		0x3f000000

#घोषणा BKP_SEL			0x3
#घोषणा BKP_REDUN_SEL		0xe0000000
#घोषणा BKP_REDUN_SHIFT		29

#घोषणा BIT_APPEND		0x3

/* eeprom layout data क्रम mdm9607 */
#घोषणा MDM9607_BASE0_MASK	0x000000ff
#घोषणा MDM9607_BASE1_MASK	0x000ff000
#घोषणा MDM9607_BASE0_SHIFT	0
#घोषणा MDM9607_BASE1_SHIFT	12

#घोषणा MDM9607_S0_P1_MASK	0x00003f00
#घोषणा MDM9607_S1_P1_MASK	0x03f00000
#घोषणा MDM9607_S2_P1_MASK	0x0000003f
#घोषणा MDM9607_S3_P1_MASK	0x0003f000
#घोषणा MDM9607_S4_P1_MASK	0x0000003f

#घोषणा MDM9607_S0_P2_MASK	0x000fc000
#घोषणा MDM9607_S1_P2_MASK	0xfc000000
#घोषणा MDM9607_S2_P2_MASK	0x00000fc0
#घोषणा MDM9607_S3_P2_MASK	0x00fc0000
#घोषणा MDM9607_S4_P2_MASK	0x00000fc0

#घोषणा MDM9607_S0_P1_SHIFT	8
#घोषणा MDM9607_S1_P1_SHIFT	20
#घोषणा MDM9607_S2_P1_SHIFT	0
#घोषणा MDM9607_S3_P1_SHIFT	12
#घोषणा MDM9607_S4_P1_SHIFT	0

#घोषणा MDM9607_S0_P2_SHIFT	14
#घोषणा MDM9607_S1_P2_SHIFT	26
#घोषणा MDM9607_S2_P2_SHIFT	6
#घोषणा MDM9607_S3_P2_SHIFT	18
#घोषणा MDM9607_S4_P2_SHIFT	6

#घोषणा MDM9607_CAL_SEL_MASK	0x00700000
#घोषणा MDM9607_CAL_SEL_SHIFT	20

अटल पूर्णांक calibrate_8916(काष्ठा tsens_priv *priv)
अणु
	पूर्णांक base0 = 0, base1 = 0, i;
	u32 p1[5], p2[5];
	पूर्णांक mode = 0;
	u32 *qfprom_cdata, *qfprom_csel;

	qfprom_cdata = (u32 *)qfprom_पढ़ो(priv->dev, "calib");
	अगर (IS_ERR(qfprom_cdata))
		वापस PTR_ERR(qfprom_cdata);

	qfprom_csel = (u32 *)qfprom_पढ़ो(priv->dev, "calib_sel");
	अगर (IS_ERR(qfprom_csel)) अणु
		kमुक्त(qfprom_cdata);
		वापस PTR_ERR(qfprom_csel);
	पूर्ण

	mode = (qfprom_csel[0] & MSM8916_CAL_SEL_MASK) >> MSM8916_CAL_SEL_SHIFT;
	dev_dbg(priv->dev, "calibration mode is %d\n", mode);

	चयन (mode) अणु
	हाल TWO_PT_CALIB:
		base1 = (qfprom_cdata[1] & MSM8916_BASE1_MASK) >> MSM8916_BASE1_SHIFT;
		p2[0] = (qfprom_cdata[0] & MSM8916_S0_P2_MASK) >> MSM8916_S0_P2_SHIFT;
		p2[1] = (qfprom_cdata[0] & MSM8916_S1_P2_MASK) >> MSM8916_S1_P2_SHIFT;
		p2[2] = (qfprom_cdata[1] & MSM8916_S2_P2_MASK) >> MSM8916_S2_P2_SHIFT;
		p2[3] = (qfprom_cdata[1] & MSM8916_S3_P2_MASK) >> MSM8916_S3_P2_SHIFT;
		p2[4] = (qfprom_cdata[1] & MSM8916_S4_P2_MASK) >> MSM8916_S4_P2_SHIFT;
		क्रम (i = 0; i < priv->num_sensors; i++)
			p2[i] = ((base1 + p2[i]) << 3);
		fallthrough;
	हाल ONE_PT_CALIB2:
		base0 = (qfprom_cdata[0] & MSM8916_BASE0_MASK);
		p1[0] = (qfprom_cdata[0] & MSM8916_S0_P1_MASK) >> MSM8916_S0_P1_SHIFT;
		p1[1] = (qfprom_cdata[0] & MSM8916_S1_P1_MASK) >> MSM8916_S1_P1_SHIFT;
		p1[2] = (qfprom_cdata[0] & MSM8916_S2_P1_MASK) >> MSM8916_S2_P1_SHIFT;
		p1[3] = (qfprom_cdata[1] & MSM8916_S3_P1_MASK) >> MSM8916_S3_P1_SHIFT;
		p1[4] = (qfprom_cdata[1] & MSM8916_S4_P1_MASK) >> MSM8916_S4_P1_SHIFT;
		क्रम (i = 0; i < priv->num_sensors; i++)
			p1[i] = (((base0) + p1[i]) << 3);
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
	kमुक्त(qfprom_csel);

	वापस 0;
पूर्ण

अटल पूर्णांक calibrate_8939(काष्ठा tsens_priv *priv)
अणु
	पूर्णांक base0 = 0, base1 = 0, i;
	u32 p1[10], p2[10];
	पूर्णांक mode = 0;
	u32 *qfprom_cdata;
	u32 cdata[6];

	qfprom_cdata = (u32 *)qfprom_पढ़ो(priv->dev, "calib");
	अगर (IS_ERR(qfprom_cdata))
		वापस PTR_ERR(qfprom_cdata);

	/* Mapping between qfprom nvmem and calibration data */
	cdata[0] = qfprom_cdata[12];
	cdata[1] = qfprom_cdata[13];
	cdata[2] = qfprom_cdata[0];
	cdata[3] = qfprom_cdata[1];
	cdata[4] = qfprom_cdata[22];
	cdata[5] = qfprom_cdata[21];

	mode = (cdata[0] & MSM8939_CAL_SEL_MASK) >> MSM8939_CAL_SEL_SHIFT;
	dev_dbg(priv->dev, "calibration mode is %d\n", mode);

	चयन (mode) अणु
	हाल TWO_PT_CALIB:
		base1 = (cdata[3] & MSM8939_BASE1_MASK) >> MSM8939_BASE1_SHIFT;
		p2[0] = (cdata[0] & MSM8939_S0_P2_MASK) >> MSM8939_S0_P2_SHIFT;
		p2[1] = (cdata[0] & MSM8939_S1_P2_MASK) >> MSM8939_S1_P2_SHIFT;
		p2[2] = (cdata[1] & MSM8939_S2_P2_MASK) >> MSM8939_S2_P2_SHIFT;
		p2[3] = (cdata[1] & MSM8939_S3_P2_MASK) >> MSM8939_S3_P2_SHIFT;
		p2[4] = (cdata[1] & MSM8939_S4_P2_MASK) >> MSM8939_S4_P2_SHIFT;
		p2[5] = (cdata[2] & MSM8939_S5_P2_MASK) >> MSM8939_S5_P2_SHIFT;
		p2[6] = (cdata[2] & MSM8939_S6_P2_MASK) >> MSM8939_S6_P2_SHIFT;
		p2[7] = (cdata[3] & MSM8939_S7_P2_MASK) >> MSM8939_S7_P2_SHIFT;
		p2[8] = (cdata[3] & MSM8939_S8_P2_MASK) >> MSM8939_S8_P2_SHIFT;
		p2[9] = (cdata[4] & MSM8939_S9_P2_MASK_0_4) >> MSM8939_S9_P2_SHIFT_0_4;
		p2[9] |= ((cdata[5] & MSM8939_S9_P2_MASK_5) >> MSM8939_S9_P2_SHIFT_5) << 5;
		क्रम (i = 0; i < priv->num_sensors; i++)
			p2[i] = (base1 + p2[i]) << 2;
		fallthrough;
	हाल ONE_PT_CALIB2:
		base0 = (cdata[2] & MSM8939_BASE0_MASK) >> MSM8939_BASE0_SHIFT;
		p1[0] = (cdata[0] & MSM8939_S0_P1_MASK) >> MSM8939_S0_P1_SHIFT;
		p1[1] = (cdata[0] & MSM8939_S1_P1_MASK) >> MSM8939_S1_P1_SHIFT;
		p1[2] = (cdata[0] & MSM8939_S2_P1_MASK_0_4) >> MSM8939_S2_P1_SHIFT_0_4;
		p1[2] |= ((cdata[1] & MSM8939_S2_P1_MASK_5) >> MSM8939_S2_P1_SHIFT_5) << 5;
		p1[3] = (cdata[1] & MSM8939_S3_P1_MASK) >> MSM8939_S3_P1_SHIFT;
		p1[4] = (cdata[1] & MSM8939_S4_P1_MASK) >> MSM8939_S4_P1_SHIFT;
		p1[5] = (cdata[2] & MSM8939_S5_P1_MASK) >> MSM8939_S5_P1_SHIFT;
		p1[6] = (cdata[2] & MSM8939_S6_P1_MASK) >> MSM8939_S6_P1_SHIFT;
		p1[7] = (cdata[3] & MSM8939_S7_P1_MASK) >> MSM8939_S7_P1_SHIFT;
		p1[8] = (cdata[3] & MSM8939_S8_P1_MASK) >> MSM8939_S8_P1_SHIFT;
		p1[9] = (cdata[4] & MSM8939_S9_P1_MASK) >> MSM8939_S9_P1_SHIFT;
		क्रम (i = 0; i < priv->num_sensors; i++)
			p1[i] = ((base0) + p1[i]) << 2;
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

अटल पूर्णांक calibrate_8974(काष्ठा tsens_priv *priv)
अणु
	पूर्णांक base1 = 0, base2 = 0, i;
	u32 p1[11], p2[11];
	पूर्णांक mode = 0;
	u32 *calib, *bkp;
	u32 calib_redun_sel;

	calib = (u32 *)qfprom_पढ़ो(priv->dev, "calib");
	अगर (IS_ERR(calib))
		वापस PTR_ERR(calib);

	bkp = (u32 *)qfprom_पढ़ो(priv->dev, "calib_backup");
	अगर (IS_ERR(bkp)) अणु
		kमुक्त(calib);
		वापस PTR_ERR(bkp);
	पूर्ण

	calib_redun_sel =  bkp[1] & BKP_REDUN_SEL;
	calib_redun_sel >>= BKP_REDUN_SHIFT;

	अगर (calib_redun_sel == BKP_SEL) अणु
		mode = (calib[4] & CAL_SEL_0_1) >> CAL_SEL_SHIFT;
		mode |= (calib[5] & CAL_SEL_2) >> CAL_SEL_SHIFT_2;

		चयन (mode) अणु
		हाल TWO_PT_CALIB:
			base2 = (bkp[2] & BASE2_BKP_MASK) >> BASE2_BKP_SHIFT;
			p2[0] = (bkp[2] & S0_P2_BKP_MASK) >> S0_P2_BKP_SHIFT;
			p2[1] = (bkp[3] & S1_P2_BKP_MASK);
			p2[2] = (bkp[3] & S2_P2_BKP_MASK) >> S2_P2_BKP_SHIFT;
			p2[3] = (bkp[3] & S3_P2_BKP_MASK) >> S3_P2_BKP_SHIFT;
			p2[4] = (bkp[3] & S4_P2_BKP_MASK) >> S4_P2_BKP_SHIFT;
			p2[5] = (calib[4] & S5_P2_BKP_MASK) >> S5_P2_BKP_SHIFT;
			p2[6] = (calib[5] & S6_P2_BKP_MASK);
			p2[7] = (calib[5] & S7_P2_BKP_MASK) >> S7_P2_BKP_SHIFT;
			p2[8] = (calib[5] & S8_P2_BKP_MASK) >> S8_P2_BKP_SHIFT;
			p2[9] = (calib[5] & S9_P2_BKP_MASK) >> S9_P2_BKP_SHIFT;
			p2[10] = (calib[5] & S10_P2_BKP_MASK) >> S10_P2_BKP_SHIFT;
			fallthrough;
		हाल ONE_PT_CALIB:
		हाल ONE_PT_CALIB2:
			base1 = bkp[0] & BASE1_MASK;
			p1[0] = (bkp[0] & S0_P1_MASK) >> S0_P1_SHIFT;
			p1[1] = (bkp[0] & S1_P1_MASK) >> S1_P1_SHIFT;
			p1[2] = (bkp[0] & S2_P1_MASK) >> S2_P1_SHIFT;
			p1[3] = (bkp[0] & S3_P1_MASK) >> S3_P1_SHIFT;
			p1[4] = (bkp[1] & S4_P1_MASK);
			p1[5] = (bkp[1] & S5_P1_MASK) >> S5_P1_SHIFT;
			p1[6] = (bkp[1] & S6_P1_MASK) >> S6_P1_SHIFT;
			p1[7] = (bkp[1] & S7_P1_MASK) >> S7_P1_SHIFT;
			p1[8] = (bkp[2] & S8_P1_MASK_BKP) >> S8_P1_SHIFT;
			p1[9] = (bkp[2] & S9_P1_MASK_BKP) >> S9_P1_BKP_SHIFT;
			p1[10] = (bkp[2] & S10_P1_MASK_BKP) >> S10_P1_BKP_SHIFT;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		mode = (calib[1] & CAL_SEL_0_1) >> CAL_SEL_SHIFT;
		mode |= (calib[3] & CAL_SEL_2) >> CAL_SEL_SHIFT_2;

		चयन (mode) अणु
		हाल TWO_PT_CALIB:
			base2 = (calib[2] & BASE2_MASK) >> BASE2_SHIFT;
			p2[0] = (calib[2] & S0_P2_MASK) >> S0_P2_SHIFT;
			p2[1] = (calib[2] & S1_P2_MASK) >> S1_P2_SHIFT;
			p2[2] = (calib[3] & S2_P2_MASK);
			p2[3] = (calib[3] & S3_P2_MASK) >> S3_P2_SHIFT;
			p2[4] = (calib[3] & S4_P2_MASK) >> S4_P2_SHIFT;
			p2[5] = (calib[3] & S5_P2_MASK) >> S5_P2_SHIFT;
			p2[6] = (calib[3] & S6_P2_MASK) >> S6_P2_SHIFT;
			p2[7] = (calib[4] & S7_P2_MASK);
			p2[8] = (calib[4] & S8_P2_MASK) >> S8_P2_SHIFT;
			p2[9] = (calib[4] & S9_P2_MASK) >> S9_P2_SHIFT;
			p2[10] = (calib[4] & S10_P2_MASK) >> S10_P2_SHIFT;
			fallthrough;
		हाल ONE_PT_CALIB:
		हाल ONE_PT_CALIB2:
			base1 = calib[0] & BASE1_MASK;
			p1[0] = (calib[0] & S0_P1_MASK) >> S0_P1_SHIFT;
			p1[1] = (calib[0] & S1_P1_MASK) >> S1_P1_SHIFT;
			p1[2] = (calib[0] & S2_P1_MASK) >> S2_P1_SHIFT;
			p1[3] = (calib[0] & S3_P1_MASK) >> S3_P1_SHIFT;
			p1[4] = (calib[1] & S4_P1_MASK);
			p1[5] = (calib[1] & S5_P1_MASK) >> S5_P1_SHIFT;
			p1[6] = (calib[1] & S6_P1_MASK) >> S6_P1_SHIFT;
			p1[7] = (calib[1] & S7_P1_MASK) >> S7_P1_SHIFT;
			p1[8] = (calib[1] & S8_P1_MASK) >> S8_P1_SHIFT;
			p1[9] = (calib[2] & S9_P1_MASK);
			p1[10] = (calib[2] & S10_P1_MASK) >> S10_P1_SHIFT;
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (mode) अणु
	हाल ONE_PT_CALIB:
		क्रम (i = 0; i < priv->num_sensors; i++)
			p1[i] += (base1 << 2) | BIT_APPEND;
		अवरोध;
	हाल TWO_PT_CALIB:
		क्रम (i = 0; i < priv->num_sensors; i++) अणु
			p2[i] += base2;
			p2[i] <<= 2;
			p2[i] |= BIT_APPEND;
		पूर्ण
		fallthrough;
	हाल ONE_PT_CALIB2:
		क्रम (i = 0; i < priv->num_sensors; i++) अणु
			p1[i] += base1;
			p1[i] <<= 2;
			p1[i] |= BIT_APPEND;
		पूर्ण
		अवरोध;
	शेष:
		क्रम (i = 0; i < priv->num_sensors; i++)
			p2[i] = 780;
		p1[0] = 502;
		p1[1] = 509;
		p1[2] = 503;
		p1[3] = 509;
		p1[4] = 505;
		p1[5] = 509;
		p1[6] = 507;
		p1[7] = 510;
		p1[8] = 508;
		p1[9] = 509;
		p1[10] = 508;
		अवरोध;
	पूर्ण

	compute_पूर्णांकercept_slope(priv, p1, p2, mode);
	kमुक्त(calib);
	kमुक्त(bkp);

	वापस 0;
पूर्ण

अटल पूर्णांक calibrate_9607(काष्ठा tsens_priv *priv)
अणु
	पूर्णांक base, i;
	u32 p1[5], p2[5];
	पूर्णांक mode = 0;
	u32 *qfprom_cdata;

	qfprom_cdata = (u32 *)qfprom_पढ़ो(priv->dev, "calib");
	अगर (IS_ERR(qfprom_cdata))
		वापस PTR_ERR(qfprom_cdata);

	mode = (qfprom_cdata[2] & MDM9607_CAL_SEL_MASK) >> MDM9607_CAL_SEL_SHIFT;
	dev_dbg(priv->dev, "calibration mode is %d\n", mode);

	चयन (mode) अणु
	हाल TWO_PT_CALIB:
		base = (qfprom_cdata[2] & MDM9607_BASE1_MASK) >> MDM9607_BASE1_SHIFT;
		p2[0] = (qfprom_cdata[0] & MDM9607_S0_P2_MASK) >> MDM9607_S0_P2_SHIFT;
		p2[1] = (qfprom_cdata[0] & MDM9607_S1_P2_MASK) >> MDM9607_S1_P2_SHIFT;
		p2[2] = (qfprom_cdata[1] & MDM9607_S2_P2_MASK) >> MDM9607_S2_P2_SHIFT;
		p2[3] = (qfprom_cdata[1] & MDM9607_S3_P2_MASK) >> MDM9607_S3_P2_SHIFT;
		p2[4] = (qfprom_cdata[2] & MDM9607_S4_P2_MASK) >> MDM9607_S4_P2_SHIFT;
		क्रम (i = 0; i < priv->num_sensors; i++)
			p2[i] = ((base + p2[i]) << 2);
		fallthrough;
	हाल ONE_PT_CALIB2:
		base = (qfprom_cdata[0] & MDM9607_BASE0_MASK);
		p1[0] = (qfprom_cdata[0] & MDM9607_S0_P1_MASK) >> MDM9607_S0_P1_SHIFT;
		p1[1] = (qfprom_cdata[0] & MDM9607_S1_P1_MASK) >> MDM9607_S1_P1_SHIFT;
		p1[2] = (qfprom_cdata[1] & MDM9607_S2_P1_MASK) >> MDM9607_S2_P1_SHIFT;
		p1[3] = (qfprom_cdata[1] & MDM9607_S3_P1_MASK) >> MDM9607_S3_P1_SHIFT;
		p1[4] = (qfprom_cdata[2] & MDM9607_S4_P1_MASK) >> MDM9607_S4_P1_SHIFT;
		क्रम (i = 0; i < priv->num_sensors; i++)
			p1[i] = ((base + p1[i]) << 2);
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

/* v0.1: 8916, 8939, 8974, 9607 */

अटल काष्ठा tsens_features tsens_v0_1_feat = अणु
	.ver_major	= VER_0_1,
	.crit_पूर्णांक	= 0,
	.adc		= 1,
	.srot_split	= 1,
	.max_sensors	= 11,
पूर्ण;

अटल स्थिर काष्ठा reg_field tsens_v0_1_regfields[MAX_REGFIELDS] = अणु
	/* ----- SROT ------ */
	/* No VERSION inक्रमmation */

	/* CTRL_OFFSET */
	[TSENS_EN]     = REG_FIELD(SROT_CTRL_OFF, 0,  0),
	[TSENS_SW_RST] = REG_FIELD(SROT_CTRL_OFF, 1,  1),

	/* ----- TM ------ */
	/* INTERRUPT ENABLE */
	[INT_EN] = REG_FIELD(TM_INT_EN_OFF, 0, 0),

	/* UPPER/LOWER TEMPERATURE THRESHOLDS */
	REG_FIELD_FOR_EACH_SENSOR11(LOW_THRESH,    TM_Sn_UPPER_LOWER_STATUS_CTRL_OFF,  0,  9),
	REG_FIELD_FOR_EACH_SENSOR11(UP_THRESH,     TM_Sn_UPPER_LOWER_STATUS_CTRL_OFF, 10, 19),

	/* UPPER/LOWER INTERRUPTS [CLEAR/STATUS] */
	REG_FIELD_FOR_EACH_SENSOR11(LOW_INT_CLEAR, TM_Sn_UPPER_LOWER_STATUS_CTRL_OFF, 20, 20),
	REG_FIELD_FOR_EACH_SENSOR11(UP_INT_CLEAR,  TM_Sn_UPPER_LOWER_STATUS_CTRL_OFF, 21, 21),

	/* NO CRITICAL INTERRUPT SUPPORT on v0.1 */

	/* Sn_STATUS */
	REG_FIELD_FOR_EACH_SENSOR11(LAST_TEMP,    TM_Sn_STATUS_OFF,  0,  9),
	/* No VALID field on v0.1 */
	/* xxx_STATUS bits: 1 == threshold violated */
	REG_FIELD_FOR_EACH_SENSOR11(MIN_STATUS,   TM_Sn_STATUS_OFF, 10, 10),
	REG_FIELD_FOR_EACH_SENSOR11(LOWER_STATUS, TM_Sn_STATUS_OFF, 11, 11),
	REG_FIELD_FOR_EACH_SENSOR11(UPPER_STATUS, TM_Sn_STATUS_OFF, 12, 12),
	/* No CRITICAL field on v0.1 */
	REG_FIELD_FOR_EACH_SENSOR11(MAX_STATUS,   TM_Sn_STATUS_OFF, 13, 13),

	/* TRDY: 1=पढ़ोy, 0=in progress */
	[TRDY] = REG_FIELD(TM_TRDY_OFF, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा tsens_ops ops_8916 = अणु
	.init		= init_common,
	.calibrate	= calibrate_8916,
	.get_temp	= get_temp_common,
पूर्ण;

काष्ठा tsens_plat_data data_8916 = अणु
	.num_sensors	= 5,
	.ops		= &ops_8916,
	.hw_ids		= (अचिन्हित पूर्णांक [])अणु0, 1, 2, 4, 5 पूर्ण,

	.feat		= &tsens_v0_1_feat,
	.fields	= tsens_v0_1_regfields,
पूर्ण;

अटल स्थिर काष्ठा tsens_ops ops_8939 = अणु
	.init		= init_common,
	.calibrate	= calibrate_8939,
	.get_temp	= get_temp_common,
पूर्ण;

काष्ठा tsens_plat_data data_8939 = अणु
	.num_sensors	= 10,
	.ops		= &ops_8939,
	.hw_ids		= (अचिन्हित पूर्णांक [])अणु 0, 1, 2, 4, 5, 6, 7, 8, 9, 10 पूर्ण,

	.feat		= &tsens_v0_1_feat,
	.fields	= tsens_v0_1_regfields,
पूर्ण;

अटल स्थिर काष्ठा tsens_ops ops_8974 = अणु
	.init		= init_common,
	.calibrate	= calibrate_8974,
	.get_temp	= get_temp_common,
पूर्ण;

काष्ठा tsens_plat_data data_8974 = अणु
	.num_sensors	= 11,
	.ops		= &ops_8974,
	.feat		= &tsens_v0_1_feat,
	.fields	= tsens_v0_1_regfields,
पूर्ण;

अटल स्थिर काष्ठा tsens_ops ops_9607 = अणु
	.init		= init_common,
	.calibrate	= calibrate_9607,
	.get_temp	= get_temp_common,
पूर्ण;

काष्ठा tsens_plat_data data_9607 = अणु
	.num_sensors	= 5,
	.ops		= &ops_9607,
	.hw_ids		= (अचिन्हित पूर्णांक [])अणु 0, 1, 2, 3, 4 पूर्ण,
	.feat		= &tsens_v0_1_feat,
	.fields	= tsens_v0_1_regfields,
पूर्ण;
