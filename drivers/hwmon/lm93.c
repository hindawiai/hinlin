<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lm93.c - Part of lm_sensors, Linux kernel modules क्रम hardware monitoring
 *
 * Author/Maपूर्णांकainer: Mark M. Hoffman <mhoffman@lightlink.com>
 *	Copyright (c) 2004 Utilitek Systems, Inc.
 *
 * derived in part from lm78.c:
 *	Copyright (c) 1998, 1999  Froकरो Looijaard <froकरोl@dds.nl>
 *
 * derived in part from lm85.c:
 *	Copyright (c) 2002, 2003 Philip Pokorny <ppokorny@penguincomputing.com>
 *	Copyright (c) 2003       Margit Schubert-While <margitsw@t-online.de>
 *
 * derived in part from w83l785ts.c:
 *	Copyright (c) 2003-2004 Jean Delvare <jdelvare@suse.de>
 *
 * Ported to Linux 2.6 by Eric J. Bowersox <ericb@aspsys.com>
 *	Copyright (c) 2005 Aspen Systems, Inc.
 *
 * Adapted to 2.6.20 by Carsten Emde <cbe@osadl.org>
 *	Copyright (c) 2006 Carsten Emde, Open Source Automation Development Lab
 *
 * Modअगरied क्रम मुख्यline पूर्णांकegration by Hans J. Koch <hjk@hansjkoch.de>
 *	Copyright (c) 2007 Hans J. Koch, Linutronix GmbH
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>

/* LM93 REGISTER ADDRESSES */

/* miscellaneous */
#घोषणा LM93_REG_MFR_ID			0x3e
#घोषणा LM93_REG_VER			0x3f
#घोषणा LM93_REG_STATUS_CONTROL		0xe2
#घोषणा LM93_REG_CONFIG			0xe3
#घोषणा LM93_REG_SLEEP_CONTROL		0xe4

/* alarm values start here */
#घोषणा LM93_REG_HOST_ERROR_1		0x48

/* voltage inमाला_दो: in1-in16 (nr => 0-15) */
#घोषणा LM93_REG_IN(nr)			(0x56 + (nr))
#घोषणा LM93_REG_IN_MIN(nr)		(0x90 + (nr) * 2)
#घोषणा LM93_REG_IN_MAX(nr)		(0x91 + (nr) * 2)

/* temperature inमाला_दो: temp1-temp4 (nr => 0-3) */
#घोषणा LM93_REG_TEMP(nr)		(0x50 + (nr))
#घोषणा LM93_REG_TEMP_MIN(nr)		(0x78 + (nr) * 2)
#घोषणा LM93_REG_TEMP_MAX(nr)		(0x79 + (nr) * 2)

/* temp[1-4]_स्वतः_boost (nr => 0-3) */
#घोषणा LM93_REG_BOOST(nr)		(0x80 + (nr))

/* #PROCHOT inमाला_दो: prochot1-prochot2 (nr => 0-1) */
#घोषणा LM93_REG_PROCHOT_CUR(nr)	(0x67 + (nr) * 2)
#घोषणा LM93_REG_PROCHOT_AVG(nr)	(0x68 + (nr) * 2)
#घोषणा LM93_REG_PROCHOT_MAX(nr)	(0xb0 + (nr))

/* fan tach inमाला_दो: fan1-fan4 (nr => 0-3) */
#घोषणा LM93_REG_FAN(nr)		(0x6e + (nr) * 2)
#घोषणा LM93_REG_FAN_MIN(nr)		(0xb4 + (nr) * 2)

/* pwm outमाला_दो: pwm1-pwm2 (nr => 0-1, reg => 0-3) */
#घोषणा LM93_REG_PWM_CTL(nr, reg)	(0xc8 + (reg) + (nr) * 4)
#घोषणा LM93_PWM_CTL1	0x0
#घोषणा LM93_PWM_CTL2	0x1
#घोषणा LM93_PWM_CTL3	0x2
#घोषणा LM93_PWM_CTL4	0x3

/* GPIO input state */
#घोषणा LM93_REG_GPI			0x6b

/* vid inमाला_दो: vid1-vid2 (nr => 0-1) */
#घोषणा LM93_REG_VID(nr)		(0x6c + (nr))

/* vccp1 & vccp2: VID relative inमाला_दो (nr => 0-1) */
#घोषणा LM93_REG_VCCP_LIMIT_OFF(nr)	(0xb2 + (nr))

/* temp[1-4]_स्वतः_boost_hyst */
#घोषणा LM93_REG_BOOST_HYST_12		0xc0
#घोषणा LM93_REG_BOOST_HYST_34		0xc1
#घोषणा LM93_REG_BOOST_HYST(nr)		(0xc0 + (nr)/2)

/* temp[1-4]_स्वतः_pwm_[min|hyst] */
#घोषणा LM93_REG_PWM_MIN_HYST_12	0xc3
#घोषणा LM93_REG_PWM_MIN_HYST_34	0xc4
#घोषणा LM93_REG_PWM_MIN_HYST(nr)	(0xc3 + (nr)/2)

/* prochot_override & prochot_पूर्णांकerval */
#घोषणा LM93_REG_PROCHOT_OVERRIDE	0xc6
#घोषणा LM93_REG_PROCHOT_INTERVAL	0xc7

/* temp[1-4]_स्वतः_base (nr => 0-3) */
#घोषणा LM93_REG_TEMP_BASE(nr)		(0xd0 + (nr))

/* temp[1-4]_स्वतः_offsets (step => 0-11) */
#घोषणा LM93_REG_TEMP_OFFSET(step)	(0xd4 + (step))

/* #PROCHOT & #VRDHOT PWM ramp control */
#घोषणा LM93_REG_PWM_RAMP_CTL		0xbf

/* miscellaneous */
#घोषणा LM93_REG_SFC1		0xbc
#घोषणा LM93_REG_SFC2		0xbd
#घोषणा LM93_REG_GPI_VID_CTL	0xbe
#घोषणा LM93_REG_SF_TACH_TO_PWM	0xe0

/* error masks */
#घोषणा LM93_REG_GPI_ERR_MASK	0xec
#घोषणा LM93_REG_MISC_ERR_MASK	0xed

/* LM93 REGISTER VALUES */
#घोषणा LM93_MFR_ID		0x73
#घोषणा LM93_MFR_ID_PROTOTYPE	0x72

/* LM94 REGISTER VALUES */
#घोषणा LM94_MFR_ID_2		0x7a
#घोषणा LM94_MFR_ID		0x79
#घोषणा LM94_MFR_ID_PROTOTYPE	0x78

/* SMBus capabilities */
#घोषणा LM93_SMBUS_FUNC_FULL (I2C_FUNC_SMBUS_BYTE_DATA | \
		I2C_FUNC_SMBUS_WORD_DATA | I2C_FUNC_SMBUS_BLOCK_DATA)
#घोषणा LM93_SMBUS_FUNC_MIN  (I2C_FUNC_SMBUS_BYTE_DATA | \
		I2C_FUNC_SMBUS_WORD_DATA)

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2c, 0x2d, 0x2e, I2C_CLIENT_END पूर्ण;

/* Insmod parameters */

अटल bool disable_block;
module_param(disable_block, bool, 0);
MODULE_PARM_DESC(disable_block,
	"Set to non-zero to disable SMBus block data transactions.");

अटल bool init;
module_param(init, bool, 0);
MODULE_PARM_DESC(init, "Set to non-zero to force chip initialization.");

अटल पूर्णांक vccp_limit_type[2] = अणु0, 0पूर्ण;
module_param_array(vccp_limit_type, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(vccp_limit_type, "Configures in7 and in8 limit modes.");

अटल पूर्णांक vid_agtl;
module_param(vid_agtl, पूर्णांक, 0);
MODULE_PARM_DESC(vid_agtl, "Configures VID pin input thresholds.");

/* Driver data */
अटल काष्ठा i2c_driver lm93_driver;

/* LM93 BLOCK READ COMMANDS */
अटल स्थिर काष्ठा अणु u8 cmd; u8 len; पूर्ण lm93_block_पढ़ो_cmds[12] = अणु
	अणु 0xf2,  8 पूर्ण,
	अणु 0xf3,  8 पूर्ण,
	अणु 0xf4,  6 पूर्ण,
	अणु 0xf5, 16 पूर्ण,
	अणु 0xf6,  4 पूर्ण,
	अणु 0xf7,  8 पूर्ण,
	अणु 0xf8, 12 पूर्ण,
	अणु 0xf9, 32 पूर्ण,
	अणु 0xfa,  8 पूर्ण,
	अणु 0xfb,  8 पूर्ण,
	अणु 0xfc, 16 पूर्ण,
	अणु 0xfd,  9 पूर्ण,
पूर्ण;

/*
 * ALARMS: SYSCTL क्रमmat described further below
 * REG: 64 bits in 8 रेजिस्टरs, as immediately below
 */
काष्ठा block1_t अणु
	u8 host_status_1;
	u8 host_status_2;
	u8 host_status_3;
	u8 host_status_4;
	u8 p1_prochot_status;
	u8 p2_prochot_status;
	u8 gpi_status;
	u8 fan_status;
पूर्ण;

/*
 * Client-specअगरic data
 */
काष्ठा lm93_data अणु
	काष्ठा i2c_client *client;

	काष्ठा mutex update_lock;
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	/* client update function */
	व्योम (*update)(काष्ठा lm93_data *, काष्ठा i2c_client *);

	अक्षर valid; /* !=0 अगर following fields are valid */

	/* रेजिस्टर values, arranged by block पढ़ो groups */
	काष्ठा block1_t block1;

	/*
	 * temp1 - temp4: unfiltered पढ़ोings
	 * temp1 - temp2: filtered पढ़ोings
	 */
	u8 block2[6];

	/* vin1 - vin16: पढ़ोings */
	u8 block3[16];

	/* prochot1 - prochot2: पढ़ोings */
	काष्ठा अणु
		u8 cur;
		u8 avg;
	पूर्ण block4[2];

	/* fan counts 1-4 => 14-bits, LE, *left* justअगरied */
	u16 block5[4];

	/* block6 has a lot of data we करोn't need */
	काष्ठा अणु
		u8 min;
		u8 max;
	पूर्ण temp_lim[4];

	/* vin1 - vin16: low and high limits */
	काष्ठा अणु
		u8 min;
		u8 max;
	पूर्ण block7[16];

	/* fan count limits 1-4 => same क्रमmat as block5 */
	u16 block8[4];

	/* pwm control रेजिस्टरs (2 pwms, 4 regs) */
	u8 block9[2][4];

	/* स्वतः/pwm base temp and offset temp रेजिस्टरs */
	काष्ठा अणु
		u8 base[4];
		u8 offset[12];
	पूर्ण block10;

	/* master config रेजिस्टर */
	u8 config;

	/* VID1 & VID2 => रेजिस्टर क्रमmat, 6-bits, right justअगरied */
	u8 vid[2];

	/* prochot1 - prochot2: limits */
	u8 prochot_max[2];

	/* vccp1 & vccp2 (in7 & in8): VID relative limits (रेजिस्टर क्रमmat) */
	u8 vccp_limits[2];

	/* GPIO input state (रेजिस्टर क्रमmat, i.e. inverted) */
	u8 gpi;

	/* #PROCHOT override (रेजिस्टर क्रमmat) */
	u8 prochot_override;

	/* #PROCHOT पूर्णांकervals (रेजिस्टर क्रमmat) */
	u8 prochot_पूर्णांकerval;

	/* Fan Boost Temperatures (रेजिस्टर क्रमmat) */
	u8 boost[4];

	/* Fan Boost Hysteresis (रेजिस्टर क्रमmat) */
	u8 boost_hyst[2];

	/* Temperature Zone Min. PWM & Hysteresis (रेजिस्टर क्रमmat) */
	u8 स्वतः_pwm_min_hyst[2];

	/* #PROCHOT & #VRDHOT PWM Ramp Control */
	u8 pwm_ramp_ctl;

	/* miscellaneous setup regs */
	u8 sfc1;
	u8 sfc2;
	u8 sf_tach_to_pwm;

	/*
	 * The two PWM CTL2  रेजिस्टरs can पढ़ो something other than what was
	 * last written क्रम the OVR_DC field (duty cycle override).  So, we
	 * save the user-commanded value here.
	 */
	u8 pwm_override[2];
पूर्ण;

/*
 * VID:	mV
 * REG: 6-bits, right justअगरied, *always* using Intel VRM/VRD 10
 */
अटल पूर्णांक LM93_VID_FROM_REG(u8 reg)
अणु
	वापस vid_from_reg((reg & 0x3f), 100);
पूर्ण

/* min, max, and nominal रेजिस्टर values, per channel (u8) */
अटल स्थिर u8 lm93_vin_reg_min[16] = अणु
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xae,
पूर्ण;
अटल स्थिर u8 lm93_vin_reg_max[16] = अणु
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xfa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd1,
पूर्ण;
/*
 * Values from the datasheet. They're here क्रम करोcumentation only.
 * अटल स्थिर u8 lm93_vin_reg_nom[16] = अणु
 * 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
 * 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x40, 0xc0,
 * पूर्ण;
 */

/* min, max, and nominal voltage पढ़ोings, per channel (mV)*/
अटल स्थिर अचिन्हित दीर्घ lm93_vin_val_min[16] = अणु
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 3000,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ lm93_vin_val_max[16] = अणु
	1236, 1236, 1236, 1600, 2000, 2000, 1600, 1600,
	4400, 6500, 3333, 2625, 1312, 1312, 1236, 3600,
पूर्ण;
/*
 * Values from the datasheet. They're here क्रम करोcumentation only.
 * अटल स्थिर अचिन्हित दीर्घ lm93_vin_val_nom[16] = अणु
 * 927,  927,  927, 1200, 1500, 1500, 1200, 1200,
 * 3300, 5000, 2500, 1969,  984,  984,  309, 3300,
 * पूर्ण;
 */

अटल अचिन्हित LM93_IN_FROM_REG(पूर्णांक nr, u8 reg)
अणु
	स्थिर दीर्घ uv_max = lm93_vin_val_max[nr] * 1000;
	स्थिर दीर्घ uv_min = lm93_vin_val_min[nr] * 1000;

	स्थिर दीर्घ slope = (uv_max - uv_min) /
		(lm93_vin_reg_max[nr] - lm93_vin_reg_min[nr]);
	स्थिर दीर्घ पूर्णांकercept = uv_min - slope * lm93_vin_reg_min[nr];

	वापस (slope * reg + पूर्णांकercept + 500) / 1000;
पूर्ण

/*
 * IN: mV, limits determined by channel nr
 * REG: scaling determined by channel nr
 */
अटल u8 LM93_IN_TO_REG(पूर्णांक nr, अचिन्हित val)
अणु
	/* range limit */
	स्थिर दीर्घ mv = clamp_val(val,
				  lm93_vin_val_min[nr], lm93_vin_val_max[nr]);

	/* try not to lose too much precision here */
	स्थिर दीर्घ uv = mv * 1000;
	स्थिर दीर्घ uv_max = lm93_vin_val_max[nr] * 1000;
	स्थिर दीर्घ uv_min = lm93_vin_val_min[nr] * 1000;

	/* convert */
	स्थिर दीर्घ slope = (uv_max - uv_min) /
		(lm93_vin_reg_max[nr] - lm93_vin_reg_min[nr]);
	स्थिर दीर्घ पूर्णांकercept = uv_min - slope * lm93_vin_reg_min[nr];

	u8 result = ((uv - पूर्णांकercept + (slope/2)) / slope);
	result = clamp_val(result,
			   lm93_vin_reg_min[nr], lm93_vin_reg_max[nr]);
	वापस result;
पूर्ण

/* vid in mV, upper == 0 indicates low limit, otherwise upper limit */
अटल अचिन्हित LM93_IN_REL_FROM_REG(u8 reg, पूर्णांक upper, पूर्णांक vid)
अणु
	स्थिर दीर्घ uv_offset = upper ? (((reg >> 4 & 0x0f) + 1) * 12500) :
				(((reg >> 0 & 0x0f) + 1) * -25000);
	स्थिर दीर्घ uv_vid = vid * 1000;
	वापस (uv_vid + uv_offset + 5000) / 10000;
पूर्ण

#घोषणा LM93_IN_MIN_FROM_REG(reg, vid)	LM93_IN_REL_FROM_REG((reg), 0, (vid))
#घोषणा LM93_IN_MAX_FROM_REG(reg, vid)	LM93_IN_REL_FROM_REG((reg), 1, (vid))

/*
 * vid in mV , upper == 0 indicates low limit, otherwise upper limit
 * upper also determines which nibble of the रेजिस्टर is वापसed
 * (the other nibble will be 0x0)
 */
अटल u8 LM93_IN_REL_TO_REG(अचिन्हित val, पूर्णांक upper, पूर्णांक vid)
अणु
	दीर्घ uv_offset = vid * 1000 - val * 10000;
	अगर (upper) अणु
		uv_offset = clamp_val(uv_offset, 12500, 200000);
		वापस (u8)((uv_offset /  12500 - 1) << 4);
	पूर्ण अन्यथा अणु
		uv_offset = clamp_val(uv_offset, -400000, -25000);
		वापस (u8)((uv_offset / -25000 - 1) << 0);
	पूर्ण
पूर्ण

/*
 * TEMP: 1/1000 degrees C (-128C to +127C)
 * REG: 1C/bit, two's complement
 */
अटल पूर्णांक LM93_TEMP_FROM_REG(u8 reg)
अणु
	वापस (s8)reg * 1000;
पूर्ण

#घोषणा LM93_TEMP_MIN (-128000)
#घोषणा LM93_TEMP_MAX (127000)

/*
 * TEMP: 1/1000 degrees C (-128C to +127C)
 * REG: 1C/bit, two's complement
 */
अटल u8 LM93_TEMP_TO_REG(दीर्घ temp)
अणु
	पूर्णांक ntemp = clamp_val(temp, LM93_TEMP_MIN, LM93_TEMP_MAX);
	ntemp += (ntemp < 0 ? -500 : 500);
	वापस (u8)(ntemp / 1000);
पूर्ण

/* Determine 4-bit temperature offset resolution */
अटल पूर्णांक LM93_TEMP_OFFSET_MODE_FROM_REG(u8 sfc2, पूर्णांक nr)
अणु
	/* mode: 0 => 1C/bit, nonzero => 0.5C/bit */
	वापस sfc2 & (nr < 2 ? 0x10 : 0x20);
पूर्ण

/*
 * This function is common to all 4-bit temperature offsets
 * reg is 4 bits right justअगरied
 * mode 0 => 1C/bit, mode !0 => 0.5C/bit
 */
अटल पूर्णांक LM93_TEMP_OFFSET_FROM_REG(u8 reg, पूर्णांक mode)
अणु
	वापस (reg & 0x0f) * (mode ? 5 : 10);
पूर्ण

#घोषणा LM93_TEMP_OFFSET_MIN  (0)
#घोषणा LM93_TEMP_OFFSET_MAX0 (150)
#घोषणा LM93_TEMP_OFFSET_MAX1 (75)

/*
 * This function is common to all 4-bit temperature offsets
 * वापसs 4 bits right justअगरied
 * mode 0 => 1C/bit, mode !0 => 0.5C/bit
 */
अटल u8 LM93_TEMP_OFFSET_TO_REG(पूर्णांक off, पूर्णांक mode)
अणु
	पूर्णांक factor = mode ? 5 : 10;

	off = clamp_val(off, LM93_TEMP_OFFSET_MIN,
		mode ? LM93_TEMP_OFFSET_MAX1 : LM93_TEMP_OFFSET_MAX0);
	वापस (u8)((off + factor/2) / factor);
पूर्ण

/* 0 <= nr <= 3 */
अटल पूर्णांक LM93_TEMP_AUTO_OFFSET_FROM_REG(u8 reg, पूर्णांक nr, पूर्णांक mode)
अणु
	/* temp1-temp2 (nr=0,1) use lower nibble */
	अगर (nr < 2)
		वापस LM93_TEMP_OFFSET_FROM_REG(reg & 0x0f, mode);

	/* temp3-temp4 (nr=2,3) use upper nibble */
	अन्यथा
		वापस LM93_TEMP_OFFSET_FROM_REG(reg >> 4 & 0x0f, mode);
पूर्ण

/*
 * TEMP: 1/10 degrees C (0C to +15C (mode 0) or +7.5C (mode non-zero))
 * REG: 1.0C/bit (mode 0) or 0.5C/bit (mode non-zero)
 * 0 <= nr <= 3
 */
अटल u8 LM93_TEMP_AUTO_OFFSET_TO_REG(u8 old, पूर्णांक off, पूर्णांक nr, पूर्णांक mode)
अणु
	u8 new = LM93_TEMP_OFFSET_TO_REG(off, mode);

	/* temp1-temp2 (nr=0,1) use lower nibble */
	अगर (nr < 2)
		वापस (old & 0xf0) | (new & 0x0f);

	/* temp3-temp4 (nr=2,3) use upper nibble */
	अन्यथा
		वापस (new << 4 & 0xf0) | (old & 0x0f);
पूर्ण

अटल पूर्णांक LM93_AUTO_BOOST_HYST_FROM_REGS(काष्ठा lm93_data *data, पूर्णांक nr,
		पूर्णांक mode)
अणु
	u8 reg;

	चयन (nr) अणु
	हाल 0:
		reg = data->boost_hyst[0] & 0x0f;
		अवरोध;
	हाल 1:
		reg = data->boost_hyst[0] >> 4 & 0x0f;
		अवरोध;
	हाल 2:
		reg = data->boost_hyst[1] & 0x0f;
		अवरोध;
	हाल 3:
	शेष:
		reg = data->boost_hyst[1] >> 4 & 0x0f;
		अवरोध;
	पूर्ण

	वापस LM93_TEMP_FROM_REG(data->boost[nr]) -
			LM93_TEMP_OFFSET_FROM_REG(reg, mode);
पूर्ण

अटल u8 LM93_AUTO_BOOST_HYST_TO_REG(काष्ठा lm93_data *data, दीर्घ hyst,
		पूर्णांक nr, पूर्णांक mode)
अणु
	u8 reg = LM93_TEMP_OFFSET_TO_REG(
			(LM93_TEMP_FROM_REG(data->boost[nr]) - hyst), mode);

	चयन (nr) अणु
	हाल 0:
		reg = (data->boost_hyst[0] & 0xf0) | (reg & 0x0f);
		अवरोध;
	हाल 1:
		reg = (reg << 4 & 0xf0) | (data->boost_hyst[0] & 0x0f);
		अवरोध;
	हाल 2:
		reg = (data->boost_hyst[1] & 0xf0) | (reg & 0x0f);
		अवरोध;
	हाल 3:
	शेष:
		reg = (reg << 4 & 0xf0) | (data->boost_hyst[1] & 0x0f);
		अवरोध;
	पूर्ण

	वापस reg;
पूर्ण

/*
 * PWM: 0-255 per sensors करोcumentation
 * REG: 0-13 as mapped below... right justअगरied
 */
क्रमागत pwm_freq अणु LM93_PWM_MAP_HI_FREQ, LM93_PWM_MAP_LO_FREQ पूर्ण;

अटल पूर्णांक lm93_pwm_map[2][16] = अणु
	अणु
		0x00, /*   0.00% */ 0x40, /*  25.00% */
		0x50, /*  31.25% */ 0x60, /*  37.50% */
		0x70, /*  43.75% */ 0x80, /*  50.00% */
		0x90, /*  56.25% */ 0xa0, /*  62.50% */
		0xb0, /*  68.75% */ 0xc0, /*  75.00% */
		0xd0, /*  81.25% */ 0xe0, /*  87.50% */
		0xf0, /*  93.75% */ 0xff, /* 100.00% */
		0xff, 0xff, /* 14, 15 are reserved and should never occur */
	पूर्ण,
	अणु
		0x00, /*   0.00% */ 0x40, /*  25.00% */
		0x49, /*  28.57% */ 0x52, /*  32.14% */
		0x5b, /*  35.71% */ 0x64, /*  39.29% */
		0x6d, /*  42.86% */ 0x76, /*  46.43% */
		0x80, /*  50.00% */ 0x89, /*  53.57% */
		0x92, /*  57.14% */ 0xb6, /*  71.43% */
		0xdb, /*  85.71% */ 0xff, /* 100.00% */
		0xff, 0xff, /* 14, 15 are reserved and should never occur */
	पूर्ण,
पूर्ण;

अटल पूर्णांक LM93_PWM_FROM_REG(u8 reg, क्रमागत pwm_freq freq)
अणु
	वापस lm93_pwm_map[freq][reg & 0x0f];
पूर्ण

/* round up to nearest match */
अटल u8 LM93_PWM_TO_REG(पूर्णांक pwm, क्रमागत pwm_freq freq)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 13; i++)
		अगर (pwm <= lm93_pwm_map[freq][i])
			अवरोध;

	/* can fall through with i==13 */
	वापस (u8)i;
पूर्ण

अटल पूर्णांक LM93_FAN_FROM_REG(u16 regs)
अणु
	स्थिर u16 count = le16_to_cpu(regs) >> 2;
	वापस count == 0 ? -1 : count == 0x3fff ? 0 : 1350000 / count;
पूर्ण

/*
 * RPM: (82.5 to 1350000)
 * REG: 14-bits, LE, *left* justअगरied
 */
अटल u16 LM93_FAN_TO_REG(दीर्घ rpm)
अणु
	u16 count, regs;

	अगर (rpm == 0) अणु
		count = 0x3fff;
	पूर्ण अन्यथा अणु
		rpm = clamp_val(rpm, 1, 1000000);
		count = clamp_val((1350000 + rpm) / rpm, 1, 0x3ffe);
	पूर्ण

	regs = count << 2;
	वापस cpu_to_le16(regs);
पूर्ण

/*
 * PWM FREQ: HZ
 * REG: 0-7 as mapped below
 */
अटल पूर्णांक lm93_pwm_freq_map[8] = अणु
	22500, 96, 84, 72, 60, 48, 36, 12
पूर्ण;

अटल पूर्णांक LM93_PWM_FREQ_FROM_REG(u8 reg)
अणु
	वापस lm93_pwm_freq_map[reg & 0x07];
पूर्ण

/* round up to nearest match */
अटल u8 LM93_PWM_FREQ_TO_REG(पूर्णांक freq)
अणु
	पूर्णांक i;
	क्रम (i = 7; i > 0; i--)
		अगर (freq <= lm93_pwm_freq_map[i])
			अवरोध;

	/* can fall through with i==0 */
	वापस (u8)i;
पूर्ण

/*
 * TIME: 1/100 seconds
 * REG: 0-7 as mapped below
 */
अटल पूर्णांक lm93_spinup_समय_map[8] = अणु
	0, 10, 25, 40, 70, 100, 200, 400,
पूर्ण;

अटल पूर्णांक LM93_SPINUP_TIME_FROM_REG(u8 reg)
अणु
	वापस lm93_spinup_समय_map[reg >> 5 & 0x07];
पूर्ण

/* round up to nearest match */
अटल u8 LM93_SPINUP_TIME_TO_REG(पूर्णांक समय)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 7; i++)
		अगर (समय <= lm93_spinup_समय_map[i])
			अवरोध;

	/* can fall through with i==8 */
	वापस (u8)i;
पूर्ण

#घोषणा LM93_RAMP_MIN 0
#घोषणा LM93_RAMP_MAX 75

अटल पूर्णांक LM93_RAMP_FROM_REG(u8 reg)
अणु
	वापस (reg & 0x0f) * 5;
पूर्ण

/*
 * RAMP: 1/100 seconds
 * REG: 50mS/bit 4-bits right justअगरied
 */
अटल u8 LM93_RAMP_TO_REG(पूर्णांक ramp)
अणु
	ramp = clamp_val(ramp, LM93_RAMP_MIN, LM93_RAMP_MAX);
	वापस (u8)((ramp + 2) / 5);
पूर्ण

/*
 * PROCHOT: 0-255, 0 => 0%, 255 => > 96.6%
 * REG: (same)
 */
अटल u8 LM93_PROCHOT_TO_REG(दीर्घ prochot)
अणु
	prochot = clamp_val(prochot, 0, 255);
	वापस (u8)prochot;
पूर्ण

/*
 * PROCHOT-INTERVAL: 73 - 37200 (1/100 seconds)
 * REG: 0-9 as mapped below
 */
अटल पूर्णांक lm93_पूर्णांकerval_map[10] = अणु
	73, 146, 290, 580, 1170, 2330, 4660, 9320, 18600, 37200,
पूर्ण;

अटल पूर्णांक LM93_INTERVAL_FROM_REG(u8 reg)
अणु
	वापस lm93_पूर्णांकerval_map[reg & 0x0f];
पूर्ण

/* round up to nearest match */
अटल u8 LM93_INTERVAL_TO_REG(दीर्घ पूर्णांकerval)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 9; i++)
		अगर (पूर्णांकerval <= lm93_पूर्णांकerval_map[i])
			अवरोध;

	/* can fall through with i==9 */
	वापस (u8)i;
पूर्ण

/*
 * GPIO: 0-255, GPIO0 is LSB
 * REG: inverted
 */
अटल अचिन्हित LM93_GPI_FROM_REG(u8 reg)
अणु
	वापस ~reg & 0xff;
पूर्ण

/*
 * alarm biपंचांगask definitions
 * The LM93 has nearly 64 bits of error status... I've pared that करोwn to
 * what I think is a useful subset in order to fit it पूर्णांकo 32 bits.
 *
 * Especially note that the #VRD_HOT alarms are missing because we provide
 * that inक्रमmation as values in another sysfs file.
 *
 * If libsensors is extended to support 64 bit values, this could be revisited.
 */
#घोषणा LM93_ALARM_IN1		0x00000001
#घोषणा LM93_ALARM_IN2		0x00000002
#घोषणा LM93_ALARM_IN3		0x00000004
#घोषणा LM93_ALARM_IN4		0x00000008
#घोषणा LM93_ALARM_IN5		0x00000010
#घोषणा LM93_ALARM_IN6		0x00000020
#घोषणा LM93_ALARM_IN7		0x00000040
#घोषणा LM93_ALARM_IN8		0x00000080
#घोषणा LM93_ALARM_IN9		0x00000100
#घोषणा LM93_ALARM_IN10		0x00000200
#घोषणा LM93_ALARM_IN11		0x00000400
#घोषणा LM93_ALARM_IN12		0x00000800
#घोषणा LM93_ALARM_IN13		0x00001000
#घोषणा LM93_ALARM_IN14		0x00002000
#घोषणा LM93_ALARM_IN15		0x00004000
#घोषणा LM93_ALARM_IN16		0x00008000
#घोषणा LM93_ALARM_FAN1		0x00010000
#घोषणा LM93_ALARM_FAN2		0x00020000
#घोषणा LM93_ALARM_FAN3		0x00040000
#घोषणा LM93_ALARM_FAN4		0x00080000
#घोषणा LM93_ALARM_PH1_ERR	0x00100000
#घोषणा LM93_ALARM_PH2_ERR	0x00200000
#घोषणा LM93_ALARM_SCSI1_ERR	0x00400000
#घोषणा LM93_ALARM_SCSI2_ERR	0x00800000
#घोषणा LM93_ALARM_DVDDP1_ERR	0x01000000
#घोषणा LM93_ALARM_DVDDP2_ERR	0x02000000
#घोषणा LM93_ALARM_D1_ERR	0x04000000
#घोषणा LM93_ALARM_D2_ERR	0x08000000
#घोषणा LM93_ALARM_TEMP1	0x10000000
#घोषणा LM93_ALARM_TEMP2	0x20000000
#घोषणा LM93_ALARM_TEMP3	0x40000000

अटल अचिन्हित LM93_ALARMS_FROM_REG(काष्ठा block1_t b1)
अणु
	अचिन्हित result;
	result  = b1.host_status_2 & 0x3f;

	अगर (vccp_limit_type[0])
		result |= (b1.host_status_4 & 0x10) << 2;
	अन्यथा
		result |= b1.host_status_2 & 0x40;

	अगर (vccp_limit_type[1])
		result |= (b1.host_status_4 & 0x20) << 2;
	अन्यथा
		result |= b1.host_status_2 & 0x80;

	result |= b1.host_status_3 << 8;
	result |= (b1.fan_status & 0x0f) << 16;
	result |= (b1.p1_prochot_status & 0x80) << 13;
	result |= (b1.p2_prochot_status & 0x80) << 14;
	result |= (b1.host_status_4 & 0xfc) << 20;
	result |= (b1.host_status_1 & 0x07) << 28;
	वापस result;
पूर्ण

#घोषणा MAX_RETRIES 5

अटल u8 lm93_पढ़ो_byte(काष्ठा i2c_client *client, u8 reg)
अणु
	पूर्णांक value, i;

	/* retry in हाल of पढ़ो errors */
	क्रम (i = 1; i <= MAX_RETRIES; i++) अणु
		value = i2c_smbus_पढ़ो_byte_data(client, reg);
		अगर (value >= 0) अणु
			वापस value;
		पूर्ण अन्यथा अणु
			dev_warn(&client->dev,
				 "lm93: read byte data failed, address 0x%02x.\n",
				 reg);
			mdelay(i + 3);
		पूर्ण

	पूर्ण

	/* <TODO> what to वापस in हाल of error? */
	dev_err(&client->dev, "lm93: All read byte retries failed!!\n");
	वापस 0;
पूर्ण

अटल पूर्णांक lm93_ग_लिखो_byte(काष्ठा i2c_client *client, u8 reg, u8 value)
अणु
	पूर्णांक result;

	/* <TODO> how to handle ग_लिखो errors? */
	result = i2c_smbus_ग_लिखो_byte_data(client, reg, value);

	अगर (result < 0)
		dev_warn(&client->dev,
			 "lm93: write byte data failed, 0x%02x at address 0x%02x.\n",
			 value, reg);

	वापस result;
पूर्ण

अटल u16 lm93_पढ़ो_word(काष्ठा i2c_client *client, u8 reg)
अणु
	पूर्णांक value, i;

	/* retry in हाल of पढ़ो errors */
	क्रम (i = 1; i <= MAX_RETRIES; i++) अणु
		value = i2c_smbus_पढ़ो_word_data(client, reg);
		अगर (value >= 0) अणु
			वापस value;
		पूर्ण अन्यथा अणु
			dev_warn(&client->dev,
				 "lm93: read word data failed, address 0x%02x.\n",
				 reg);
			mdelay(i + 3);
		पूर्ण

	पूर्ण

	/* <TODO> what to वापस in हाल of error? */
	dev_err(&client->dev, "lm93: All read word retries failed!!\n");
	वापस 0;
पूर्ण

अटल पूर्णांक lm93_ग_लिखो_word(काष्ठा i2c_client *client, u8 reg, u16 value)
अणु
	पूर्णांक result;

	/* <TODO> how to handle ग_लिखो errors? */
	result = i2c_smbus_ग_लिखो_word_data(client, reg, value);

	अगर (result < 0)
		dev_warn(&client->dev,
			 "lm93: write word data failed, 0x%04x at address 0x%02x.\n",
			 value, reg);

	वापस result;
पूर्ण

अटल u8 lm93_block_buffer[I2C_SMBUS_BLOCK_MAX];

/*
 * पढ़ो block data पूर्णांकo values, retry अगर not expected length
 * fbn => index to lm93_block_पढ़ो_cmds table
 * (Fixed Block Number - section 14.5.2 of LM93 datasheet)
 */
अटल व्योम lm93_पढ़ो_block(काष्ठा i2c_client *client, u8 fbn, u8 *values)
अणु
	पूर्णांक i, result = 0;

	क्रम (i = 1; i <= MAX_RETRIES; i++) अणु
		result = i2c_smbus_पढ़ो_block_data(client,
			lm93_block_पढ़ो_cmds[fbn].cmd, lm93_block_buffer);

		अगर (result == lm93_block_पढ़ो_cmds[fbn].len) अणु
			अवरोध;
		पूर्ण अन्यथा अणु
			dev_warn(&client->dev,
				 "lm93: block read data failed, command 0x%02x.\n",
				 lm93_block_पढ़ो_cmds[fbn].cmd);
			mdelay(i + 3);
		पूर्ण
	पूर्ण

	अगर (result == lm93_block_पढ़ो_cmds[fbn].len) अणु
		स_नकल(values, lm93_block_buffer,
		       lm93_block_पढ़ो_cmds[fbn].len);
	पूर्ण अन्यथा अणु
		/* <TODO> what to करो in हाल of error? */
	पूर्ण
पूर्ण

अटल काष्ठा lm93_data *lm93_update_device(काष्ठा device *dev)
अणु
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	स्थिर अचिन्हित दीर्घ पूर्णांकerval = HZ + (HZ / 2);

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + पूर्णांकerval) ||
		!data->valid) अणु

		data->update(data, client);
		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);
	वापस data;
पूर्ण

/* update routine क्रम data that has no corresponding SMBus block command */
अटल व्योम lm93_update_client_common(काष्ठा lm93_data *data,
				      काष्ठा i2c_client *client)
अणु
	पूर्णांक i;
	u8 *ptr;

	/* temp1 - temp4: limits */
	क्रम (i = 0; i < 4; i++) अणु
		data->temp_lim[i].min =
			lm93_पढ़ो_byte(client, LM93_REG_TEMP_MIN(i));
		data->temp_lim[i].max =
			lm93_पढ़ो_byte(client, LM93_REG_TEMP_MAX(i));
	पूर्ण

	/* config रेजिस्टर */
	data->config = lm93_पढ़ो_byte(client, LM93_REG_CONFIG);

	/* vid1 - vid2: values */
	क्रम (i = 0; i < 2; i++)
		data->vid[i] = lm93_पढ़ो_byte(client, LM93_REG_VID(i));

	/* prochot1 - prochot2: limits */
	क्रम (i = 0; i < 2; i++)
		data->prochot_max[i] = lm93_पढ़ो_byte(client,
				LM93_REG_PROCHOT_MAX(i));

	/* vccp1 - vccp2: VID relative limits */
	क्रम (i = 0; i < 2; i++)
		data->vccp_limits[i] = lm93_पढ़ो_byte(client,
				LM93_REG_VCCP_LIMIT_OFF(i));

	/* GPIO input state */
	data->gpi = lm93_पढ़ो_byte(client, LM93_REG_GPI);

	/* #PROCHOT override state */
	data->prochot_override = lm93_पढ़ो_byte(client,
			LM93_REG_PROCHOT_OVERRIDE);

	/* #PROCHOT पूर्णांकervals */
	data->prochot_पूर्णांकerval = lm93_पढ़ो_byte(client,
			LM93_REG_PROCHOT_INTERVAL);

	/* Fan Boost Temperature रेजिस्टरs */
	क्रम (i = 0; i < 4; i++)
		data->boost[i] = lm93_पढ़ो_byte(client, LM93_REG_BOOST(i));

	/* Fan Boost Temperature Hyst. रेजिस्टरs */
	data->boost_hyst[0] = lm93_पढ़ो_byte(client, LM93_REG_BOOST_HYST_12);
	data->boost_hyst[1] = lm93_पढ़ो_byte(client, LM93_REG_BOOST_HYST_34);

	/* Temperature Zone Min. PWM & Hysteresis रेजिस्टरs */
	data->स्वतः_pwm_min_hyst[0] =
			lm93_पढ़ो_byte(client, LM93_REG_PWM_MIN_HYST_12);
	data->स्वतः_pwm_min_hyst[1] =
			lm93_पढ़ो_byte(client, LM93_REG_PWM_MIN_HYST_34);

	/* #PROCHOT & #VRDHOT PWM Ramp Control रेजिस्टर */
	data->pwm_ramp_ctl = lm93_पढ़ो_byte(client, LM93_REG_PWM_RAMP_CTL);

	/* misc setup रेजिस्टरs */
	data->sfc1 = lm93_पढ़ो_byte(client, LM93_REG_SFC1);
	data->sfc2 = lm93_पढ़ो_byte(client, LM93_REG_SFC2);
	data->sf_tach_to_pwm = lm93_पढ़ो_byte(client,
			LM93_REG_SF_TACH_TO_PWM);

	/* ग_लिखो back alarm values to clear */
	क्रम (i = 0, ptr = (u8 *)(&data->block1); i < 8; i++)
		lm93_ग_लिखो_byte(client, LM93_REG_HOST_ERROR_1 + i, *(ptr + i));
पूर्ण

/* update routine which uses SMBus block data commands */
अटल व्योम lm93_update_client_full(काष्ठा lm93_data *data,
				    काष्ठा i2c_client *client)
अणु
	dev_dbg(&client->dev, "starting device update (block data enabled)\n");

	/* in1 - in16: values & limits */
	lm93_पढ़ो_block(client, 3, (u8 *)(data->block3));
	lm93_पढ़ो_block(client, 7, (u8 *)(data->block7));

	/* temp1 - temp4: values */
	lm93_पढ़ो_block(client, 2, (u8 *)(data->block2));

	/* prochot1 - prochot2: values */
	lm93_पढ़ो_block(client, 4, (u8 *)(data->block4));

	/* fan1 - fan4: values & limits */
	lm93_पढ़ो_block(client, 5, (u8 *)(data->block5));
	lm93_पढ़ो_block(client, 8, (u8 *)(data->block8));

	/* pmw control रेजिस्टरs */
	lm93_पढ़ो_block(client, 9, (u8 *)(data->block9));

	/* alarm values */
	lm93_पढ़ो_block(client, 1, (u8 *)(&data->block1));

	/* स्वतः/pwm रेजिस्टरs */
	lm93_पढ़ो_block(client, 10, (u8 *)(&data->block10));

	lm93_update_client_common(data, client);
पूर्ण

/* update routine which uses SMBus byte/word data commands only */
अटल व्योम lm93_update_client_min(काष्ठा lm93_data *data,
				   काष्ठा i2c_client *client)
अणु
	पूर्णांक i, j;
	u8 *ptr;

	dev_dbg(&client->dev, "starting device update (block data disabled)\n");

	/* in1 - in16: values & limits */
	क्रम (i = 0; i < 16; i++) अणु
		data->block3[i] =
			lm93_पढ़ो_byte(client, LM93_REG_IN(i));
		data->block7[i].min =
			lm93_पढ़ो_byte(client, LM93_REG_IN_MIN(i));
		data->block7[i].max =
			lm93_पढ़ो_byte(client, LM93_REG_IN_MAX(i));
	पूर्ण

	/* temp1 - temp4: values */
	क्रम (i = 0; i < 4; i++) अणु
		data->block2[i] =
			lm93_पढ़ो_byte(client, LM93_REG_TEMP(i));
	पूर्ण

	/* prochot1 - prochot2: values */
	क्रम (i = 0; i < 2; i++) अणु
		data->block4[i].cur =
			lm93_पढ़ो_byte(client, LM93_REG_PROCHOT_CUR(i));
		data->block4[i].avg =
			lm93_पढ़ो_byte(client, LM93_REG_PROCHOT_AVG(i));
	पूर्ण

	/* fan1 - fan4: values & limits */
	क्रम (i = 0; i < 4; i++) अणु
		data->block5[i] =
			lm93_पढ़ो_word(client, LM93_REG_FAN(i));
		data->block8[i] =
			lm93_पढ़ो_word(client, LM93_REG_FAN_MIN(i));
	पूर्ण

	/* pwm control रेजिस्टरs */
	क्रम (i = 0; i < 2; i++) अणु
		क्रम (j = 0; j < 4; j++) अणु
			data->block9[i][j] =
				lm93_पढ़ो_byte(client, LM93_REG_PWM_CTL(i, j));
		पूर्ण
	पूर्ण

	/* alarm values */
	क्रम (i = 0, ptr = (u8 *)(&data->block1); i < 8; i++) अणु
		*(ptr + i) =
			lm93_पढ़ो_byte(client, LM93_REG_HOST_ERROR_1 + i);
	पूर्ण

	/* स्वतः/pwm (base temp) रेजिस्टरs */
	क्रम (i = 0; i < 4; i++) अणु
		data->block10.base[i] =
			lm93_पढ़ो_byte(client, LM93_REG_TEMP_BASE(i));
	पूर्ण

	/* स्वतः/pwm (offset temp) रेजिस्टरs */
	क्रम (i = 0; i < 12; i++) अणु
		data->block10.offset[i] =
			lm93_पढ़ो_byte(client, LM93_REG_TEMP_OFFSET(i));
	पूर्ण

	lm93_update_client_common(data, client);
पूर्ण

/* following are the sysfs callback functions */
अटल sमाप_प्रकार in_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;

	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", LM93_IN_FROM_REG(nr, data->block3[nr]));
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in1_input, in, 0);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, in, 1);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, in, 2);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, in, 3);
अटल SENSOR_DEVICE_ATTR_RO(in5_input, in, 4);
अटल SENSOR_DEVICE_ATTR_RO(in6_input, in, 5);
अटल SENSOR_DEVICE_ATTR_RO(in7_input, in, 6);
अटल SENSOR_DEVICE_ATTR_RO(in8_input, in, 7);
अटल SENSOR_DEVICE_ATTR_RO(in9_input, in, 8);
अटल SENSOR_DEVICE_ATTR_RO(in10_input, in, 9);
अटल SENSOR_DEVICE_ATTR_RO(in11_input, in, 10);
अटल SENSOR_DEVICE_ATTR_RO(in12_input, in, 11);
अटल SENSOR_DEVICE_ATTR_RO(in13_input, in, 12);
अटल SENSOR_DEVICE_ATTR_RO(in14_input, in, 13);
अटल SENSOR_DEVICE_ATTR_RO(in15_input, in, 14);
अटल SENSOR_DEVICE_ATTR_RO(in16_input, in, 15);

अटल sमाप_प्रकार in_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	पूर्णांक vccp = nr - 6;
	दीर्घ rc, vid;

	अगर ((nr == 6 || nr == 7) && vccp_limit_type[vccp]) अणु
		vid = LM93_VID_FROM_REG(data->vid[vccp]);
		rc = LM93_IN_MIN_FROM_REG(data->vccp_limits[vccp], vid);
	पूर्ण अन्यथा अणु
		rc = LM93_IN_FROM_REG(nr, data->block7[nr].min);
	पूर्ण
	वापस प्र_लिखो(buf, "%ld\n", rc);
पूर्ण

अटल sमाप_प्रकार in_min_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक vccp = nr - 6;
	दीर्घ vid;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	अगर ((nr == 6 || nr == 7) && vccp_limit_type[vccp]) अणु
		vid = LM93_VID_FROM_REG(data->vid[vccp]);
		data->vccp_limits[vccp] = (data->vccp_limits[vccp] & 0xf0) |
				LM93_IN_REL_TO_REG(val, 0, vid);
		lm93_ग_लिखो_byte(client, LM93_REG_VCCP_LIMIT_OFF(vccp),
				data->vccp_limits[vccp]);
	पूर्ण अन्यथा अणु
		data->block7[nr].min = LM93_IN_TO_REG(nr, val);
		lm93_ग_लिखो_byte(client, LM93_REG_IN_MIN(nr),
				data->block7[nr].min);
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(in1_min, in_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(in2_min, in_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(in3_min, in_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(in4_min, in_min, 3);
अटल SENSOR_DEVICE_ATTR_RW(in5_min, in_min, 4);
अटल SENSOR_DEVICE_ATTR_RW(in6_min, in_min, 5);
अटल SENSOR_DEVICE_ATTR_RW(in7_min, in_min, 6);
अटल SENSOR_DEVICE_ATTR_RW(in8_min, in_min, 7);
अटल SENSOR_DEVICE_ATTR_RW(in9_min, in_min, 8);
अटल SENSOR_DEVICE_ATTR_RW(in10_min, in_min, 9);
अटल SENSOR_DEVICE_ATTR_RW(in11_min, in_min, 10);
अटल SENSOR_DEVICE_ATTR_RW(in12_min, in_min, 11);
अटल SENSOR_DEVICE_ATTR_RW(in13_min, in_min, 12);
अटल SENSOR_DEVICE_ATTR_RW(in14_min, in_min, 13);
अटल SENSOR_DEVICE_ATTR_RW(in15_min, in_min, 14);
अटल SENSOR_DEVICE_ATTR_RW(in16_min, in_min, 15);

अटल sमाप_प्रकार in_max_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	पूर्णांक vccp = nr - 6;
	दीर्घ rc, vid;

	अगर ((nr == 6 || nr == 7) && vccp_limit_type[vccp]) अणु
		vid = LM93_VID_FROM_REG(data->vid[vccp]);
		rc = LM93_IN_MAX_FROM_REG(data->vccp_limits[vccp], vid);
	पूर्ण अन्यथा अणु
		rc = LM93_IN_FROM_REG(nr, data->block7[nr].max);
	पूर्ण
	वापस प्र_लिखो(buf, "%ld\n", rc);
पूर्ण

अटल sमाप_प्रकार in_max_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक vccp = nr - 6;
	दीर्घ vid;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	अगर ((nr == 6 || nr == 7) && vccp_limit_type[vccp]) अणु
		vid = LM93_VID_FROM_REG(data->vid[vccp]);
		data->vccp_limits[vccp] = (data->vccp_limits[vccp] & 0x0f) |
				LM93_IN_REL_TO_REG(val, 1, vid);
		lm93_ग_लिखो_byte(client, LM93_REG_VCCP_LIMIT_OFF(vccp),
				data->vccp_limits[vccp]);
	पूर्ण अन्यथा अणु
		data->block7[nr].max = LM93_IN_TO_REG(nr, val);
		lm93_ग_लिखो_byte(client, LM93_REG_IN_MAX(nr),
				data->block7[nr].max);
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(in1_max, in_max, 0);
अटल SENSOR_DEVICE_ATTR_RW(in2_max, in_max, 1);
अटल SENSOR_DEVICE_ATTR_RW(in3_max, in_max, 2);
अटल SENSOR_DEVICE_ATTR_RW(in4_max, in_max, 3);
अटल SENSOR_DEVICE_ATTR_RW(in5_max, in_max, 4);
अटल SENSOR_DEVICE_ATTR_RW(in6_max, in_max, 5);
अटल SENSOR_DEVICE_ATTR_RW(in7_max, in_max, 6);
अटल SENSOR_DEVICE_ATTR_RW(in8_max, in_max, 7);
अटल SENSOR_DEVICE_ATTR_RW(in9_max, in_max, 8);
अटल SENSOR_DEVICE_ATTR_RW(in10_max, in_max, 9);
अटल SENSOR_DEVICE_ATTR_RW(in11_max, in_max, 10);
अटल SENSOR_DEVICE_ATTR_RW(in12_max, in_max, 11);
अटल SENSOR_DEVICE_ATTR_RW(in13_max, in_max, 12);
अटल SENSOR_DEVICE_ATTR_RW(in14_max, in_max, 13);
अटल SENSOR_DEVICE_ATTR_RW(in15_max, in_max, 14);
अटल SENSOR_DEVICE_ATTR_RW(in16_max, in_max, 15);

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", LM93_TEMP_FROM_REG(data->block2[nr]));
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp, 2);

अटल sमाप_प्रकार temp_min_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", LM93_TEMP_FROM_REG(data->temp_lim[nr].min));
पूर्ण

अटल sमाप_प्रकार temp_min_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_lim[nr].min = LM93_TEMP_TO_REG(val);
	lm93_ग_लिखो_byte(client, LM93_REG_TEMP_MIN(nr), data->temp_lim[nr].min);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_min, temp_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_min, temp_min, 2);

अटल sमाप_प्रकार temp_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", LM93_TEMP_FROM_REG(data->temp_lim[nr].max));
पूर्ण

अटल sमाप_प्रकार temp_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_lim[nr].max = LM93_TEMP_TO_REG(val);
	lm93_ग_लिखो_byte(client, LM93_REG_TEMP_MAX(nr), data->temp_lim[nr].max);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp_max, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp_max, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max, temp_max, 2);

अटल sमाप_प्रकार temp_स्वतः_base_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", LM93_TEMP_FROM_REG(data->block10.base[nr]));
पूर्ण

अटल sमाप_प्रकार temp_स्वतः_base_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->block10.base[nr] = LM93_TEMP_TO_REG(val);
	lm93_ग_लिखो_byte(client, LM93_REG_TEMP_BASE(nr), data->block10.base[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(temp1_स्वतः_base, temp_स्वतः_base, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_स्वतः_base, temp_स्वतः_base, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_स्वतः_base, temp_स्वतः_base, 2);

अटल sमाप_प्रकार temp_स्वतः_boost_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", LM93_TEMP_FROM_REG(data->boost[nr]));
पूर्ण

अटल sमाप_प्रकार temp_स्वतः_boost_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->boost[nr] = LM93_TEMP_TO_REG(val);
	lm93_ग_लिखो_byte(client, LM93_REG_BOOST(nr), data->boost[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(temp1_स्वतः_boost, temp_स्वतः_boost, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_स्वतः_boost, temp_स्वतः_boost, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_स्वतः_boost, temp_स्वतः_boost, 2);

अटल sमाप_प्रकार temp_स्वतः_boost_hyst_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	पूर्णांक mode = LM93_TEMP_OFFSET_MODE_FROM_REG(data->sfc2, nr);
	वापस प्र_लिखो(buf, "%d\n",
		       LM93_AUTO_BOOST_HYST_FROM_REGS(data, nr, mode));
पूर्ण

अटल sमाप_प्रकार temp_स्वतः_boost_hyst_store(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	/* क्रमce 0.5C/bit mode */
	data->sfc2 = lm93_पढ़ो_byte(client, LM93_REG_SFC2);
	data->sfc2 |= ((nr < 2) ? 0x10 : 0x20);
	lm93_ग_लिखो_byte(client, LM93_REG_SFC2, data->sfc2);
	data->boost_hyst[nr/2] = LM93_AUTO_BOOST_HYST_TO_REG(data, val, nr, 1);
	lm93_ग_लिखो_byte(client, LM93_REG_BOOST_HYST(nr),
			data->boost_hyst[nr/2]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(temp1_स्वतः_boost_hyst, temp_स्वतः_boost_hyst, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_स्वतः_boost_hyst, temp_स्वतः_boost_hyst, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_स्वतः_boost_hyst, temp_स्वतः_boost_hyst, 2);

अटल sमाप_प्रकार temp_स्वतः_offset_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *s_attr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = s_attr->index;
	पूर्णांक ofs = s_attr->nr;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	पूर्णांक mode = LM93_TEMP_OFFSET_MODE_FROM_REG(data->sfc2, nr);
	वापस प्र_लिखो(buf, "%d\n",
	       LM93_TEMP_AUTO_OFFSET_FROM_REG(data->block10.offset[ofs],
					      nr, mode));
पूर्ण

अटल sमाप_प्रकार temp_स्वतः_offset_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *s_attr = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = s_attr->index;
	पूर्णांक ofs = s_attr->nr;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	/* क्रमce 0.5C/bit mode */
	data->sfc2 = lm93_पढ़ो_byte(client, LM93_REG_SFC2);
	data->sfc2 |= ((nr < 2) ? 0x10 : 0x20);
	lm93_ग_लिखो_byte(client, LM93_REG_SFC2, data->sfc2);
	data->block10.offset[ofs] = LM93_TEMP_AUTO_OFFSET_TO_REG(
			data->block10.offset[ofs], val, nr, 1);
	lm93_ग_लिखो_byte(client, LM93_REG_TEMP_OFFSET(ofs),
			data->block10.offset[ofs]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_2_RW(temp1_स्वतः_offset1, temp_स्वतः_offset, 0, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_स्वतः_offset2, temp_स्वतः_offset, 1, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_स्वतः_offset3, temp_स्वतः_offset, 2, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_स्वतः_offset4, temp_स्वतः_offset, 3, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_स्वतः_offset5, temp_स्वतः_offset, 4, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_स्वतः_offset6, temp_स्वतः_offset, 5, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_स्वतः_offset7, temp_स्वतः_offset, 6, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_स्वतः_offset8, temp_स्वतः_offset, 7, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_स्वतः_offset9, temp_स्वतः_offset, 8, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_स्वतः_offset10, temp_स्वतः_offset, 9, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_स्वतः_offset11, temp_स्वतः_offset, 10, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_स्वतः_offset12, temp_स्वतः_offset, 11, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_स्वतः_offset1, temp_स्वतः_offset, 0, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_स्वतः_offset2, temp_स्वतः_offset, 1, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_स्वतः_offset3, temp_स्वतः_offset, 2, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_स्वतः_offset4, temp_स्वतः_offset, 3, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_स्वतः_offset5, temp_स्वतः_offset, 4, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_स्वतः_offset6, temp_स्वतः_offset, 5, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_स्वतः_offset7, temp_स्वतः_offset, 6, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_स्वतः_offset8, temp_स्वतः_offset, 7, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_स्वतः_offset9, temp_स्वतः_offset, 8, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_स्वतः_offset10, temp_स्वतः_offset, 9, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_स्वतः_offset11, temp_स्वतः_offset, 10, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_स्वतः_offset12, temp_स्वतः_offset, 11, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_स्वतः_offset1, temp_स्वतः_offset, 0, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_स्वतः_offset2, temp_स्वतः_offset, 1, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_स्वतः_offset3, temp_स्वतः_offset, 2, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_स्वतः_offset4, temp_स्वतः_offset, 3, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_स्वतः_offset5, temp_स्वतः_offset, 4, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_स्वतः_offset6, temp_स्वतः_offset, 5, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_स्वतः_offset7, temp_स्वतः_offset, 6, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_स्वतः_offset8, temp_स्वतः_offset, 7, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_स्वतः_offset9, temp_स्वतः_offset, 8, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_स्वतः_offset10, temp_स्वतः_offset, 9, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_स्वतः_offset11, temp_स्वतः_offset, 10, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_स्वतः_offset12, temp_स्वतः_offset, 11, 2);

अटल sमाप_प्रकार temp_स्वतः_pwm_min_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	u8 reg, ctl4;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	reg = data->स्वतः_pwm_min_hyst[nr/2] >> 4 & 0x0f;
	ctl4 = data->block9[nr][LM93_PWM_CTL4];
	वापस प्र_लिखो(buf, "%d\n", LM93_PWM_FROM_REG(reg, (ctl4 & 0x07) ?
				LM93_PWM_MAP_LO_FREQ : LM93_PWM_MAP_HI_FREQ));
पूर्ण

अटल sमाप_प्रकार temp_स्वतः_pwm_min_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 reg, ctl4;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	reg = lm93_पढ़ो_byte(client, LM93_REG_PWM_MIN_HYST(nr));
	ctl4 = lm93_पढ़ो_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL4));
	reg = (reg & 0x0f) |
		LM93_PWM_TO_REG(val, (ctl4 & 0x07) ?
				LM93_PWM_MAP_LO_FREQ :
				LM93_PWM_MAP_HI_FREQ) << 4;
	data->स्वतः_pwm_min_hyst[nr/2] = reg;
	lm93_ग_लिखो_byte(client, LM93_REG_PWM_MIN_HYST(nr), reg);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(temp1_स्वतः_pwm_min, temp_स्वतः_pwm_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_स्वतः_pwm_min, temp_स्वतः_pwm_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_स्वतः_pwm_min, temp_स्वतः_pwm_min, 2);

अटल sमाप_प्रकार temp_स्वतः_offset_hyst_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	पूर्णांक mode = LM93_TEMP_OFFSET_MODE_FROM_REG(data->sfc2, nr);
	वापस प्र_लिखो(buf, "%d\n", LM93_TEMP_OFFSET_FROM_REG(
					data->स्वतः_pwm_min_hyst[nr / 2], mode));
पूर्ण

अटल sमाप_प्रकार temp_स्वतः_offset_hyst_store(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 reg;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	/* क्रमce 0.5C/bit mode */
	data->sfc2 = lm93_पढ़ो_byte(client, LM93_REG_SFC2);
	data->sfc2 |= ((nr < 2) ? 0x10 : 0x20);
	lm93_ग_लिखो_byte(client, LM93_REG_SFC2, data->sfc2);
	reg = data->स्वतः_pwm_min_hyst[nr/2];
	reg = (reg & 0xf0) | (LM93_TEMP_OFFSET_TO_REG(val, 1) & 0x0f);
	data->स्वतः_pwm_min_hyst[nr/2] = reg;
	lm93_ग_लिखो_byte(client, LM93_REG_PWM_MIN_HYST(nr), reg);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(temp1_स्वतः_offset_hyst, temp_स्वतः_offset_hyst, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_स्वतः_offset_hyst, temp_स्वतः_offset_hyst, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_स्वतः_offset_hyst, temp_स्वतः_offset_hyst, 2);

अटल sमाप_प्रकार fan_input_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *s_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = s_attr->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", LM93_FAN_FROM_REG(data->block5[nr]));
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan_input, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan_input, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan3_input, fan_input, 2);
अटल SENSOR_DEVICE_ATTR_RO(fan4_input, fan_input, 3);

अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", LM93_FAN_FROM_REG(data->block8[nr]));
पूर्ण

अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->block8[nr] = LM93_FAN_TO_REG(val);
	lm93_ग_लिखो_word(client, LM93_REG_FAN_MIN(nr), data->block8[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(fan1_min, fan_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_min, fan_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan3_min, fan_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(fan4_min, fan_min, 3);

/*
 * some tedious bit-twiddling here to deal with the रेजिस्टर क्रमmat:
 *
 *	data->sf_tach_to_pwm: (tach to pwm mapping bits)
 *
 *		bit |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0
 *		     T4:P2 T4:P1 T3:P2 T3:P1 T2:P2 T2:P1 T1:P2 T1:P1
 *
 *	data->sfc2: (enable bits)
 *
 *		bit |  3  |  2  |  1  |  0
 *		       T4    T3    T2    T1
 */

अटल sमाप_प्रकार fan_smart_tach_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	दीर्घ rc = 0;
	पूर्णांक mapping;

	/* extract the relevant mapping */
	mapping = (data->sf_tach_to_pwm >> (nr * 2)) & 0x03;

	/* अगर there's a mapping and it's enabled */
	अगर (mapping && ((data->sfc2 >> nr) & 0x01))
		rc = mapping;
	वापस प्र_लिखो(buf, "%ld\n", rc);
पूर्ण

/*
 * helper function - must grab data->update_lock beक्रमe calling
 * fan is 0-3, indicating fan1-fan4
 */
अटल व्योम lm93_ग_लिखो_fan_smart_tach(काष्ठा i2c_client *client,
	काष्ठा lm93_data *data, पूर्णांक fan, दीर्घ value)
अणु
	/* insert the new mapping and ग_लिखो it out */
	data->sf_tach_to_pwm = lm93_पढ़ो_byte(client, LM93_REG_SF_TACH_TO_PWM);
	data->sf_tach_to_pwm &= ~(0x3 << fan * 2);
	data->sf_tach_to_pwm |= value << fan * 2;
	lm93_ग_लिखो_byte(client, LM93_REG_SF_TACH_TO_PWM, data->sf_tach_to_pwm);

	/* insert the enable bit and ग_लिखो it out */
	data->sfc2 = lm93_पढ़ो_byte(client, LM93_REG_SFC2);
	अगर (value)
		data->sfc2 |= 1 << fan;
	अन्यथा
		data->sfc2 &= ~(1 << fan);
	lm93_ग_लिखो_byte(client, LM93_REG_SFC2, data->sfc2);
पूर्ण

अटल sमाप_प्रकार fan_smart_tach_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	/* sanity test, ignore the ग_लिखो otherwise */
	अगर (val <= 2) अणु
		/* can't enable अगर pwm freq is 22.5KHz */
		अगर (val) अणु
			u8 ctl4 = lm93_पढ़ो_byte(client,
				LM93_REG_PWM_CTL(val - 1, LM93_PWM_CTL4));
			अगर ((ctl4 & 0x07) == 0)
				val = 0;
		पूर्ण
		lm93_ग_लिखो_fan_smart_tach(client, data, nr, val);
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(fan1_smart_tach, fan_smart_tach, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_smart_tach, fan_smart_tach, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan3_smart_tach, fan_smart_tach, 2);
अटल SENSOR_DEVICE_ATTR_RW(fan4_smart_tach, fan_smart_tach, 3);

अटल sमाप_प्रकार pwm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	u8 ctl2, ctl4;
	दीर्घ rc;

	ctl2 = data->block9[nr][LM93_PWM_CTL2];
	ctl4 = data->block9[nr][LM93_PWM_CTL4];
	अगर (ctl2 & 0x01) /* show user commanded value अगर enabled */
		rc = data->pwm_override[nr];
	अन्यथा /* show present h/w value अगर manual pwm disabled */
		rc = LM93_PWM_FROM_REG(ctl2 >> 4, (ctl4 & 0x07) ?
			LM93_PWM_MAP_LO_FREQ : LM93_PWM_MAP_HI_FREQ);
	वापस प्र_लिखो(buf, "%ld\n", rc);
पूर्ण

अटल sमाप_प्रकार pwm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 ctl2, ctl4;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	ctl2 = lm93_पढ़ो_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL2));
	ctl4 = lm93_पढ़ो_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL4));
	ctl2 = (ctl2 & 0x0f) | LM93_PWM_TO_REG(val, (ctl4 & 0x07) ?
			LM93_PWM_MAP_LO_FREQ : LM93_PWM_MAP_HI_FREQ) << 4;
	/* save user commanded value */
	data->pwm_override[nr] = LM93_PWM_FROM_REG(ctl2 >> 4,
			(ctl4 & 0x07) ?  LM93_PWM_MAP_LO_FREQ :
			LM93_PWM_MAP_HI_FREQ);
	lm93_ग_लिखो_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL2), ctl2);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(pwm1, pwm, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2, pwm, 1);

अटल sमाप_प्रकार pwm_enable_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	u8 ctl2;
	दीर्घ rc;

	ctl2 = data->block9[nr][LM93_PWM_CTL2];
	अगर (ctl2 & 0x01) /* manual override enabled ? */
		rc = ((ctl2 & 0xF0) == 0xF0) ? 0 : 1;
	अन्यथा
		rc = 2;
	वापस प्र_लिखो(buf, "%ld\n", rc);
पूर्ण

अटल sमाप_प्रकार pwm_enable_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 ctl2;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	ctl2 = lm93_पढ़ो_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL2));

	चयन (val) अणु
	हाल 0:
		ctl2 |= 0xF1; /* enable manual override, set PWM to max */
		अवरोध;
	हाल 1:
		ctl2 |= 0x01; /* enable manual override */
		अवरोध;
	हाल 2:
		ctl2 &= ~0x01; /* disable manual override */
		अवरोध;
	शेष:
		mutex_unlock(&data->update_lock);
		वापस -EINVAL;
	पूर्ण

	lm93_ग_लिखो_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL2), ctl2);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(pwm1_enable, pwm_enable, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_enable, pwm_enable, 1);

अटल sमाप_प्रकार pwm_freq_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	u8 ctl4;

	ctl4 = data->block9[nr][LM93_PWM_CTL4];
	वापस प्र_लिखो(buf, "%d\n", LM93_PWM_FREQ_FROM_REG(ctl4));
पूर्ण

/*
 * helper function - must grab data->update_lock beक्रमe calling
 * pwm is 0-1, indicating pwm1-pwm2
 * this disables smart tach क्रम all tach channels bound to the given pwm
 */
अटल व्योम lm93_disable_fan_smart_tach(काष्ठा i2c_client *client,
	काष्ठा lm93_data *data, पूर्णांक pwm)
अणु
	पूर्णांक mapping = lm93_पढ़ो_byte(client, LM93_REG_SF_TACH_TO_PWM);
	पूर्णांक mask;

	/* collapse the mapping पूर्णांकo a mask of enable bits */
	mapping = (mapping >> pwm) & 0x55;
	mask = mapping & 0x01;
	mask |= (mapping & 0x04) >> 1;
	mask |= (mapping & 0x10) >> 2;
	mask |= (mapping & 0x40) >> 3;

	/* disable smart tach according to the mask */
	data->sfc2 = lm93_पढ़ो_byte(client, LM93_REG_SFC2);
	data->sfc2 &= ~mask;
	lm93_ग_लिखो_byte(client, LM93_REG_SFC2, data->sfc2);
पूर्ण

अटल sमाप_प्रकार pwm_freq_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 ctl4;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	ctl4 = lm93_पढ़ो_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL4));
	ctl4 = (ctl4 & 0xf8) | LM93_PWM_FREQ_TO_REG(val);
	data->block9[nr][LM93_PWM_CTL4] = ctl4;
	/* ctl4 == 0 -> 22.5KHz -> disable smart tach */
	अगर (!ctl4)
		lm93_disable_fan_smart_tach(client, data, nr);
	lm93_ग_लिखो_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL4), ctl4);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(pwm1_freq, pwm_freq, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_freq, pwm_freq, 1);

अटल sमाप_प्रकार pwm_स्वतः_channels_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->block9[nr][LM93_PWM_CTL1]);
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_channels_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->block9[nr][LM93_PWM_CTL1] = clamp_val(val, 0, 255);
	lm93_ग_लिखो_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL1),
				data->block9[nr][LM93_PWM_CTL1]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_channels, pwm_स्वतः_channels, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_स्वतः_channels, pwm_स्वतः_channels, 1);

अटल sमाप_प्रकार pwm_स्वतः_spinup_min_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	u8 ctl3, ctl4;

	ctl3 = data->block9[nr][LM93_PWM_CTL3];
	ctl4 = data->block9[nr][LM93_PWM_CTL4];
	वापस प्र_लिखो(buf, "%d\n",
		       LM93_PWM_FROM_REG(ctl3 & 0x0f, (ctl4 & 0x07) ?
			LM93_PWM_MAP_LO_FREQ : LM93_PWM_MAP_HI_FREQ));
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_spinup_min_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 ctl3, ctl4;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	ctl3 = lm93_पढ़ो_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL3));
	ctl4 = lm93_पढ़ो_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL4));
	ctl3 = (ctl3 & 0xf0) | LM93_PWM_TO_REG(val, (ctl4 & 0x07) ?
			LM93_PWM_MAP_LO_FREQ :
			LM93_PWM_MAP_HI_FREQ);
	data->block9[nr][LM93_PWM_CTL3] = ctl3;
	lm93_ग_लिखो_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL3), ctl3);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_spinup_min, pwm_स्वतः_spinup_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_स्वतः_spinup_min, pwm_स्वतः_spinup_min, 1);

अटल sमाप_प्रकार pwm_स्वतः_spinup_समय_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", LM93_SPINUP_TIME_FROM_REG(
				data->block9[nr][LM93_PWM_CTL3]));
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_spinup_समय_store(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 ctl3;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	ctl3 = lm93_पढ़ो_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL3));
	ctl3 = (ctl3 & 0x1f) | (LM93_SPINUP_TIME_TO_REG(val) << 5 & 0xe0);
	data->block9[nr][LM93_PWM_CTL3] = ctl3;
	lm93_ग_लिखो_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL3), ctl3);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_spinup_समय, pwm_स्वतः_spinup_समय, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_स्वतः_spinup_समय, pwm_स्वतः_spinup_समय, 1);

अटल sमाप_प्रकार pwm_स्वतः_prochot_ramp_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n",
		       LM93_RAMP_FROM_REG(data->pwm_ramp_ctl >> 4 & 0x0f));
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_prochot_ramp_store(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 ramp;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	ramp = lm93_पढ़ो_byte(client, LM93_REG_PWM_RAMP_CTL);
	ramp = (ramp & 0x0f) | (LM93_RAMP_TO_REG(val) << 4 & 0xf0);
	lm93_ग_लिखो_byte(client, LM93_REG_PWM_RAMP_CTL, ramp);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(pwm_स्वतः_prochot_ramp);

अटल sमाप_प्रकार pwm_स्वतः_vrdhot_ramp_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n",
		       LM93_RAMP_FROM_REG(data->pwm_ramp_ctl & 0x0f));
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_vrdhot_ramp_store(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 ramp;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	ramp = lm93_पढ़ो_byte(client, LM93_REG_PWM_RAMP_CTL);
	ramp = (ramp & 0xf0) | (LM93_RAMP_TO_REG(val) & 0x0f);
	lm93_ग_लिखो_byte(client, LM93_REG_PWM_RAMP_CTL, ramp);
	mutex_unlock(&data->update_lock);
	वापस 0;
पूर्ण

अटल DEVICE_ATTR_RW(pwm_स्वतः_vrdhot_ramp);

अटल sमाप_प्रकार vid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", LM93_VID_FROM_REG(data->vid[nr]));
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(cpu0_vid, vid, 0);
अटल SENSOR_DEVICE_ATTR_RO(cpu1_vid, vid, 1);

अटल sमाप_प्रकार prochot_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->block4[nr].cur);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(prochot1, prochot, 0);
अटल SENSOR_DEVICE_ATTR_RO(prochot2, prochot, 1);

अटल sमाप_प्रकार prochot_avg_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->block4[nr].avg);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(prochot1_avg, prochot_avg, 0);
अटल SENSOR_DEVICE_ATTR_RO(prochot2_avg, prochot_avg, 1);

अटल sमाप_प्रकार prochot_max_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->prochot_max[nr]);
पूर्ण

अटल sमाप_प्रकार prochot_max_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->prochot_max[nr] = LM93_PROCHOT_TO_REG(val);
	lm93_ग_लिखो_byte(client, LM93_REG_PROCHOT_MAX(nr),
			data->prochot_max[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(prochot1_max, prochot_max, 0);
अटल SENSOR_DEVICE_ATTR_RW(prochot2_max, prochot_max, 1);

अटल स्थिर u8 prochot_override_mask[] = अणु 0x80, 0x40 पूर्ण;

अटल sमाप_प्रकार prochot_override_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n",
		(data->prochot_override & prochot_override_mask[nr]) ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार prochot_override_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	अगर (val)
		data->prochot_override |= prochot_override_mask[nr];
	अन्यथा
		data->prochot_override &= (~prochot_override_mask[nr]);
	lm93_ग_लिखो_byte(client, LM93_REG_PROCHOT_OVERRIDE,
			data->prochot_override);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(prochot1_override, prochot_override, 0);
अटल SENSOR_DEVICE_ATTR_RW(prochot2_override, prochot_override, 1);

अटल sमाप_प्रकार prochot_पूर्णांकerval_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	u8 पंचांगp;
	अगर (nr == 1)
		पंचांगp = (data->prochot_पूर्णांकerval & 0xf0) >> 4;
	अन्यथा
		पंचांगp = data->prochot_पूर्णांकerval & 0x0f;
	वापस प्र_लिखो(buf, "%d\n", LM93_INTERVAL_FROM_REG(पंचांगp));
पूर्ण

अटल sमाप_प्रकार prochot_पूर्णांकerval_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 पंचांगp;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	पंचांगp = lm93_पढ़ो_byte(client, LM93_REG_PROCHOT_INTERVAL);
	अगर (nr == 1)
		पंचांगp = (पंचांगp & 0x0f) | (LM93_INTERVAL_TO_REG(val) << 4);
	अन्यथा
		पंचांगp = (पंचांगp & 0xf0) | LM93_INTERVAL_TO_REG(val);
	data->prochot_पूर्णांकerval = पंचांगp;
	lm93_ग_लिखो_byte(client, LM93_REG_PROCHOT_INTERVAL, पंचांगp);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(prochot1_पूर्णांकerval, prochot_पूर्णांकerval, 0);
अटल SENSOR_DEVICE_ATTR_RW(prochot2_पूर्णांकerval, prochot_पूर्णांकerval, 1);

अटल sमाप_प्रकार prochot_override_duty_cycle_show(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						अक्षर *buf)
अणु
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->prochot_override & 0x0f);
पूर्ण

अटल sमाप_प्रकार prochot_override_duty_cycle_store(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->prochot_override = (data->prochot_override & 0xf0) |
					clamp_val(val, 0, 15);
	lm93_ग_लिखो_byte(client, LM93_REG_PROCHOT_OVERRIDE,
			data->prochot_override);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(prochot_override_duty_cycle);

अटल sमाप_प्रकार prochot_लघु_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", (data->config & 0x10) ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार prochot_लघु_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm93_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	अगर (val)
		data->config |= 0x10;
	अन्यथा
		data->config &= ~0x10;
	lm93_ग_लिखो_byte(client, LM93_REG_CONFIG, data->config);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(prochot_लघु);

अटल sमाप_प्रकार vrdhot_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक nr = (to_sensor_dev_attr(attr))->index;
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n",
		       data->block1.host_status_1 & (1 << (nr + 4)) ? 1 : 0);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(vrdhot1, vrdhot, 0);
अटल SENSOR_DEVICE_ATTR_RO(vrdhot2, vrdhot, 1);

अटल sमाप_प्रकार gpio_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", LM93_GPI_FROM_REG(data->gpi));
पूर्ण

अटल DEVICE_ATTR_RO(gpio);

अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा lm93_data *data = lm93_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", LM93_ALARMS_FROM_REG(data->block1));
पूर्ण

अटल DEVICE_ATTR_RO(alarms);

अटल काष्ठा attribute *lm93_attrs[] = अणु
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in7_input.dev_attr.attr,
	&sensor_dev_attr_in8_input.dev_attr.attr,
	&sensor_dev_attr_in9_input.dev_attr.attr,
	&sensor_dev_attr_in10_input.dev_attr.attr,
	&sensor_dev_attr_in11_input.dev_attr.attr,
	&sensor_dev_attr_in12_input.dev_attr.attr,
	&sensor_dev_attr_in13_input.dev_attr.attr,
	&sensor_dev_attr_in14_input.dev_attr.attr,
	&sensor_dev_attr_in15_input.dev_attr.attr,
	&sensor_dev_attr_in16_input.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in6_min.dev_attr.attr,
	&sensor_dev_attr_in7_min.dev_attr.attr,
	&sensor_dev_attr_in8_min.dev_attr.attr,
	&sensor_dev_attr_in9_min.dev_attr.attr,
	&sensor_dev_attr_in10_min.dev_attr.attr,
	&sensor_dev_attr_in11_min.dev_attr.attr,
	&sensor_dev_attr_in12_min.dev_attr.attr,
	&sensor_dev_attr_in13_min.dev_attr.attr,
	&sensor_dev_attr_in14_min.dev_attr.attr,
	&sensor_dev_attr_in15_min.dev_attr.attr,
	&sensor_dev_attr_in16_min.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,
	&sensor_dev_attr_in6_max.dev_attr.attr,
	&sensor_dev_attr_in7_max.dev_attr.attr,
	&sensor_dev_attr_in8_max.dev_attr.attr,
	&sensor_dev_attr_in9_max.dev_attr.attr,
	&sensor_dev_attr_in10_max.dev_attr.attr,
	&sensor_dev_attr_in11_max.dev_attr.attr,
	&sensor_dev_attr_in12_max.dev_attr.attr,
	&sensor_dev_attr_in13_max.dev_attr.attr,
	&sensor_dev_attr_in14_max.dev_attr.attr,
	&sensor_dev_attr_in15_max.dev_attr.attr,
	&sensor_dev_attr_in16_max.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_base.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_base.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_base.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_boost.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_boost.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_boost.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_boost_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_boost_hyst.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_boost_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_offset1.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_offset2.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_offset3.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_offset4.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_offset5.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_offset6.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_offset7.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_offset8.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_offset9.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_offset10.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_offset11.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_offset12.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_offset1.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_offset2.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_offset3.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_offset4.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_offset5.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_offset6.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_offset7.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_offset8.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_offset9.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_offset10.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_offset11.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_offset12.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_offset1.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_offset2.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_offset3.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_offset4.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_offset5.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_offset6.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_offset7.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_offset8.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_offset9.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_offset10.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_offset11.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_offset12.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_pwm_min.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_pwm_min.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_pwm_min.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_offset_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_offset_hyst.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_offset_hyst.dev_attr.attr,
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan4_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan3_min.dev_attr.attr,
	&sensor_dev_attr_fan4_min.dev_attr.attr,
	&sensor_dev_attr_fan1_smart_tach.dev_attr.attr,
	&sensor_dev_attr_fan2_smart_tach.dev_attr.attr,
	&sensor_dev_attr_fan3_smart_tach.dev_attr.attr,
	&sensor_dev_attr_fan4_smart_tach.dev_attr.attr,
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&sensor_dev_attr_pwm1_enable.dev_attr.attr,
	&sensor_dev_attr_pwm2_enable.dev_attr.attr,
	&sensor_dev_attr_pwm1_freq.dev_attr.attr,
	&sensor_dev_attr_pwm2_freq.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_channels.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_channels.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_spinup_min.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_spinup_min.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_spinup_समय.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_spinup_समय.dev_attr.attr,
	&dev_attr_pwm_स्वतः_prochot_ramp.attr,
	&dev_attr_pwm_स्वतः_vrdhot_ramp.attr,
	&sensor_dev_attr_cpu0_vid.dev_attr.attr,
	&sensor_dev_attr_cpu1_vid.dev_attr.attr,
	&sensor_dev_attr_prochot1.dev_attr.attr,
	&sensor_dev_attr_prochot2.dev_attr.attr,
	&sensor_dev_attr_prochot1_avg.dev_attr.attr,
	&sensor_dev_attr_prochot2_avg.dev_attr.attr,
	&sensor_dev_attr_prochot1_max.dev_attr.attr,
	&sensor_dev_attr_prochot2_max.dev_attr.attr,
	&sensor_dev_attr_prochot1_override.dev_attr.attr,
	&sensor_dev_attr_prochot2_override.dev_attr.attr,
	&sensor_dev_attr_prochot1_पूर्णांकerval.dev_attr.attr,
	&sensor_dev_attr_prochot2_पूर्णांकerval.dev_attr.attr,
	&dev_attr_prochot_override_duty_cycle.attr,
	&dev_attr_prochot_लघु.attr,
	&sensor_dev_attr_vrdhot1.dev_attr.attr,
	&sensor_dev_attr_vrdhot2.dev_attr.attr,
	&dev_attr_gpio.attr,
	&dev_attr_alarms.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(lm93);

अटल व्योम lm93_init_client(काष्ठा i2c_client *client)
अणु
	पूर्णांक i;
	u8 reg;

	/* configure VID pin input thresholds */
	reg = lm93_पढ़ो_byte(client, LM93_REG_GPI_VID_CTL);
	lm93_ग_लिखो_byte(client, LM93_REG_GPI_VID_CTL,
			reg | (vid_agtl ? 0x03 : 0x00));

	अगर (init) अणु
		/* enable #ALERT pin */
		reg = lm93_पढ़ो_byte(client, LM93_REG_CONFIG);
		lm93_ग_लिखो_byte(client, LM93_REG_CONFIG, reg | 0x08);

		/* enable ASF mode क्रम BMC status रेजिस्टरs */
		reg = lm93_पढ़ो_byte(client, LM93_REG_STATUS_CONTROL);
		lm93_ग_लिखो_byte(client, LM93_REG_STATUS_CONTROL, reg | 0x02);

		/* set sleep state to S0 */
		lm93_ग_लिखो_byte(client, LM93_REG_SLEEP_CONTROL, 0);

		/* unmask #VRDHOT and dynamic VCCP (अगर nec) error events */
		reg = lm93_पढ़ो_byte(client, LM93_REG_MISC_ERR_MASK);
		reg &= ~0x03;
		reg &= ~(vccp_limit_type[0] ? 0x10 : 0);
		reg &= ~(vccp_limit_type[1] ? 0x20 : 0);
		lm93_ग_लिखो_byte(client, LM93_REG_MISC_ERR_MASK, reg);
	पूर्ण

	/* start monitoring */
	reg = lm93_पढ़ो_byte(client, LM93_REG_CONFIG);
	lm93_ग_लिखो_byte(client, LM93_REG_CONFIG, reg | 0x01);

	/* spin until पढ़ोy */
	क्रम (i = 0; i < 20; i++) अणु
		msleep(10);
		अगर ((lm93_पढ़ो_byte(client, LM93_REG_CONFIG) & 0x80) == 0x80)
			वापस;
	पूर्ण

	dev_warn(&client->dev,
		 "timed out waiting for sensor chip to signal ready!\n");
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक lm93_detect(काष्ठा i2c_client *client, काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक mfr, ver;
	स्थिर अक्षर *name;

	अगर (!i2c_check_functionality(adapter, LM93_SMBUS_FUNC_MIN))
		वापस -ENODEV;

	/* detection */
	mfr = lm93_पढ़ो_byte(client, LM93_REG_MFR_ID);
	अगर (mfr != 0x01) अणु
		dev_dbg(&adapter->dev,
			"detect failed, bad manufacturer id 0x%02x!\n", mfr);
		वापस -ENODEV;
	पूर्ण

	ver = lm93_पढ़ो_byte(client, LM93_REG_VER);
	चयन (ver) अणु
	हाल LM93_MFR_ID:
	हाल LM93_MFR_ID_PROTOTYPE:
		name = "lm93";
		अवरोध;
	हाल LM94_MFR_ID_2:
	हाल LM94_MFR_ID:
	हाल LM94_MFR_ID_PROTOTYPE:
		name = "lm94";
		अवरोध;
	शेष:
		dev_dbg(&adapter->dev,
			"detect failed, bad version id 0x%02x!\n", ver);
		वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, name, I2C_NAME_SIZE);
	dev_dbg(&adapter->dev, "loading %s at %d, 0x%02x\n",
		client->name, i2c_adapter_id(client->adapter),
		client->addr);

	वापस 0;
पूर्ण

अटल पूर्णांक lm93_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा lm93_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक func;
	व्योम (*update)(काष्ठा lm93_data *, काष्ठा i2c_client *);

	/* choose update routine based on bus capabilities */
	func = i2c_get_functionality(client->adapter);
	अगर (((LM93_SMBUS_FUNC_FULL & func) == LM93_SMBUS_FUNC_FULL) &&
			(!disable_block)) अणु
		dev_dbg(dev, "using SMBus block data transactions\n");
		update = lm93_update_client_full;
	पूर्ण अन्यथा अगर ((LM93_SMBUS_FUNC_MIN & func) == LM93_SMBUS_FUNC_MIN) अणु
		dev_dbg(dev, "disabled SMBus block data transactions\n");
		update = lm93_update_client_min;
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "detect failed, smbus byte and/or word data not supported!\n");
		वापस -ENODEV;
	पूर्ण

	data = devm_kzalloc(dev, माप(काष्ठा lm93_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/* housekeeping */
	data->client = client;
	data->update = update;
	mutex_init(&data->update_lock);

	/* initialize the chip */
	lm93_init_client(client);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data,
							   lm93_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm93_id[] = अणु
	अणु "lm93", 0 पूर्ण,
	अणु "lm94", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm93_id);

अटल काष्ठा i2c_driver lm93_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "lm93",
	पूर्ण,
	.probe_new	= lm93_probe,
	.id_table	= lm93_id,
	.detect		= lm93_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(lm93_driver);

MODULE_AUTHOR("Mark M. Hoffman <mhoffman@lightlink.com>, "
		"Hans J. Koch <hjk@hansjkoch.de>");
MODULE_DESCRIPTION("LM93 driver");
MODULE_LICENSE("GPL");
