<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dme1737.c - Driver क्रम the SMSC DME1737, Asus A8000, SMSC SCH311x, SCH5027,
 *             and SCH5127 Super-I/O chips पूर्णांकegrated hardware monitoring
 *             features.
 * Copyright (c) 2007, 2008, 2009, 2010 Juerg Haefliger <juergh@gmail.com>
 *
 * This driver is an I2C/ISA hybrid, meaning that it uses the I2C bus to access
 * the chip रेजिस्टरs अगर a DME1737, A8000, or SCH5027 is found and the ISA bus
 * अगर a SCH311x or SCH5127 chip is found. Both types of chips have very
 * similar hardware monitoring capabilities but dअगरfer in the way they can be
 * accessed.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

/* ISA device, अगर found */
अटल काष्ठा platक्रमm_device *pdev;

/* Module load parameters */
अटल bool क्रमce_start;
module_param(क्रमce_start, bool, 0);
MODULE_PARM_DESC(क्रमce_start, "Force the chip to start monitoring inputs");

अटल अचिन्हित लघु क्रमce_id;
module_param(क्रमce_id, uलघु, 0);
MODULE_PARM_DESC(क्रमce_id, "Override the detected device ID");

अटल bool probe_all_addr;
module_param(probe_all_addr, bool, 0);
MODULE_PARM_DESC(probe_all_addr,
		 "Include probing of non-standard LPC addresses");

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु0x2c, 0x2d, 0x2e, I2C_CLIENT_ENDपूर्ण;

क्रमागत chips अणु dme1737, sch5027, sch311x, sch5127 पूर्ण;

#घोषणा	DO_REPORT "Please report to the driver maintainer."

/* ---------------------------------------------------------------------
 * Registers
 *
 * The sensors are defined as follows:
 *
 * Voltages                          Temperatures
 * --------                          ------------
 * in0   +5VTR (+5V stdby)           temp1   Remote diode 1
 * in1   Vccp  (proc core)           temp2   Internal temp
 * in2   VCC   (पूर्णांकernal +3.3V)      temp3   Remote diode 2
 * in3   +5V
 * in4   +12V
 * in5   VTR   (+3.3V stby)
 * in6   Vbat
 * in7   Vtrip (sch5127 only)
 *
 * --------------------------------------------------------------------- */

/* Voltages (in) numbered 0-7 (ix) */
#घोषणा DME1737_REG_IN(ix)		((ix) < 5 ? 0x20 + (ix) : \
					 (ix) < 7 ? 0x94 + (ix) : \
						    0x1f)
#घोषणा DME1737_REG_IN_MIN(ix)		((ix) < 5 ? 0x44 + (ix) * 2 \
						  : 0x91 + (ix) * 2)
#घोषणा DME1737_REG_IN_MAX(ix)		((ix) < 5 ? 0x45 + (ix) * 2 \
						  : 0x92 + (ix) * 2)

/* Temperatures (temp) numbered 0-2 (ix) */
#घोषणा DME1737_REG_TEMP(ix)		(0x25 + (ix))
#घोषणा DME1737_REG_TEMP_MIN(ix)	(0x4e + (ix) * 2)
#घोषणा DME1737_REG_TEMP_MAX(ix)	(0x4f + (ix) * 2)
#घोषणा DME1737_REG_TEMP_OFFSET(ix)	((ix) == 0 ? 0x1f \
						   : 0x1c + (ix))

/*
 * Voltage and temperature LSBs
 * The LSBs (4 bits each) are stored in 5 रेजिस्टरs with the following layouts:
 *    IN_TEMP_LSB(0) = [in5, in6]
 *    IN_TEMP_LSB(1) = [temp3, temp1]
 *    IN_TEMP_LSB(2) = [in4, temp2]
 *    IN_TEMP_LSB(3) = [in3, in0]
 *    IN_TEMP_LSB(4) = [in2, in1]
 *    IN_TEMP_LSB(5) = [res, in7]
 */
#घोषणा DME1737_REG_IN_TEMP_LSB(ix)	(0x84 + (ix))
अटल स्थिर u8 DME1737_REG_IN_LSB[] = अणु3, 4, 4, 3, 2, 0, 0, 5पूर्ण;
अटल स्थिर u8 DME1737_REG_IN_LSB_SHL[] = अणु4, 4, 0, 0, 0, 0, 4, 4पूर्ण;
अटल स्थिर u8 DME1737_REG_TEMP_LSB[] = अणु1, 2, 1पूर्ण;
अटल स्थिर u8 DME1737_REG_TEMP_LSB_SHL[] = अणु4, 4, 0पूर्ण;

/* Fans numbered 0-5 (ix) */
#घोषणा DME1737_REG_FAN(ix)		((ix) < 4 ? 0x28 + (ix) * 2 \
						  : 0xa1 + (ix) * 2)
#घोषणा DME1737_REG_FAN_MIN(ix)		((ix) < 4 ? 0x54 + (ix) * 2 \
						  : 0xa5 + (ix) * 2)
#घोषणा DME1737_REG_FAN_OPT(ix)		((ix) < 4 ? 0x90 + (ix) \
						  : 0xb2 + (ix))
#घोषणा DME1737_REG_FAN_MAX(ix)		(0xb4 + (ix)) /* only क्रम fan[4-5] */

/* PWMs numbered 0-2, 4-5 (ix) */
#घोषणा DME1737_REG_PWM(ix)		((ix) < 3 ? 0x30 + (ix) \
						  : 0xa1 + (ix))
#घोषणा DME1737_REG_PWM_CONFIG(ix)	(0x5c + (ix)) /* only क्रम pwm[0-2] */
#घोषणा DME1737_REG_PWM_MIN(ix)		(0x64 + (ix)) /* only क्रम pwm[0-2] */
#घोषणा DME1737_REG_PWM_FREQ(ix)	((ix) < 3 ? 0x5f + (ix) \
						  : 0xa3 + (ix))
/*
 * The layout of the ramp rate रेजिस्टरs is dअगरferent from the other pwm
 * रेजिस्टरs. The bits क्रम the 3 PWMs are stored in 2 रेजिस्टरs:
 *    PWM_RR(0) = [OFF3, OFF2,  OFF1,  RES,   RR1E, RR1-2, RR1-1, RR1-0]
 *    PWM_RR(1) = [RR2E, RR2-2, RR2-1, RR2-0, RR3E, RR3-2, RR3-1, RR3-0]
 */
#घोषणा DME1737_REG_PWM_RR(ix)		(0x62 + (ix)) /* only क्रम pwm[0-2] */

/* Thermal zones 0-2 */
#घोषणा DME1737_REG_ZONE_LOW(ix)	(0x67 + (ix))
#घोषणा DME1737_REG_ZONE_ABS(ix)	(0x6a + (ix))
/*
 * The layout of the hysteresis रेजिस्टरs is dअगरferent from the other zone
 * रेजिस्टरs. The bits क्रम the 3 zones are stored in 2 रेजिस्टरs:
 *    ZONE_HYST(0) = [H1-3,  H1-2,  H1-1, H1-0, H2-3, H2-2, H2-1, H2-0]
 *    ZONE_HYST(1) = [H3-3,  H3-2,  H3-1, H3-0, RES,  RES,  RES,  RES]
 */
#घोषणा DME1737_REG_ZONE_HYST(ix)	(0x6d + (ix))

/*
 * Alarm रेजिस्टरs and bit mapping
 * The 3 8-bit alarm रेजिस्टरs will be concatenated to a single 32-bit
 * alarm value [0, ALARM3, ALARM2, ALARM1].
 */
#घोषणा DME1737_REG_ALARM1		0x41
#घोषणा DME1737_REG_ALARM2		0x42
#घोषणा DME1737_REG_ALARM3		0x83
अटल स्थिर u8 DME1737_BIT_ALARM_IN[] = अणु0, 1, 2, 3, 8, 16, 17, 18पूर्ण;
अटल स्थिर u8 DME1737_BIT_ALARM_TEMP[] = अणु4, 5, 6पूर्ण;
अटल स्थिर u8 DME1737_BIT_ALARM_FAN[] = अणु10, 11, 12, 13, 22, 23पूर्ण;

/* Miscellaneous रेजिस्टरs */
#घोषणा DME1737_REG_DEVICE		0x3d
#घोषणा DME1737_REG_COMPANY		0x3e
#घोषणा DME1737_REG_VERSTEP		0x3f
#घोषणा DME1737_REG_CONFIG		0x40
#घोषणा DME1737_REG_CONFIG2		0x7f
#घोषणा DME1737_REG_VID			0x43
#घोषणा DME1737_REG_TACH_PWM		0x81

/* ---------------------------------------------------------------------
 * Misc defines
 * --------------------------------------------------------------------- */

/* Chip identअगरication */
#घोषणा DME1737_COMPANY_SMSC	0x5c
#घोषणा DME1737_VERSTEP		0x88
#घोषणा DME1737_VERSTEP_MASK	0xf8
#घोषणा SCH311X_DEVICE		0x8c
#घोषणा SCH5027_VERSTEP		0x69
#घोषणा SCH5127_DEVICE		0x8e

/* Device ID values (global configuration रेजिस्टर index 0x20) */
#घोषणा DME1737_ID_1	0x77
#घोषणा DME1737_ID_2	0x78
#घोषणा SCH3112_ID	0x7c
#घोषणा SCH3114_ID	0x7d
#घोषणा SCH3116_ID	0x7f
#घोषणा SCH5027_ID	0x89
#घोषणा SCH5127_ID	0x86

/* Length of ISA address segment */
#घोषणा DME1737_EXTENT	2

/* chip-dependent features */
#घोषणा HAS_TEMP_OFFSET		(1 << 0)		/* bit 0 */
#घोषणा HAS_VID			(1 << 1)		/* bit 1 */
#घोषणा HAS_ZONE3		(1 << 2)		/* bit 2 */
#घोषणा HAS_ZONE_HYST		(1 << 3)		/* bit 3 */
#घोषणा HAS_PWM_MIN		(1 << 4)		/* bit 4 */
#घोषणा HAS_FAN(ix)		(1 << ((ix) + 5))	/* bits 5-10 */
#घोषणा HAS_PWM(ix)		(1 << ((ix) + 11))	/* bits 11-16 */
#घोषणा HAS_IN7			(1 << 17)		/* bit 17 */

/* ---------------------------------------------------------------------
 * Data काष्ठाures and manipulation thereof
 * --------------------------------------------------------------------- */

काष्ठा dme1737_data अणु
	काष्ठा i2c_client *client;	/* क्रम I2C devices only */
	काष्ठा device *hwmon_dev;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक addr;		/* क्रम ISA devices only */

	काष्ठा mutex update_lock;
	पूर्णांक valid;			/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_update;	/* in jअगरfies */
	अचिन्हित दीर्घ last_vbat;	/* in jअगरfies */
	क्रमागत chips type;
	स्थिर पूर्णांक *in_nominal;		/* poपूर्णांकer to IN_NOMINAL array */

	u8 vid;
	u8 pwm_rr_en;
	u32 has_features;

	/* Register values */
	u16 in[8];
	u8  in_min[8];
	u8  in_max[8];
	s16 temp[3];
	s8  temp_min[3];
	s8  temp_max[3];
	s8  temp_offset[3];
	u8  config;
	u8  config2;
	u8  vrm;
	u16 fan[6];
	u16 fan_min[6];
	u8  fan_max[2];
	u8  fan_opt[6];
	u8  pwm[6];
	u8  pwm_min[3];
	u8  pwm_config[3];
	u8  pwm_acz[3];
	u8  pwm_freq[6];
	u8  pwm_rr[2];
	s8  zone_low[3];
	s8  zone_असल[3];
	u8  zone_hyst[2];
	u32 alarms;
पूर्ण;

/* Nominal voltage values */
अटल स्थिर पूर्णांक IN_NOMINAL_DME1737[] = अणु5000, 2250, 3300, 5000, 12000, 3300,
					 3300पूर्ण;
अटल स्थिर पूर्णांक IN_NOMINAL_SCH311x[] = अणु2500, 1500, 3300, 5000, 12000, 3300,
					 3300पूर्ण;
अटल स्थिर पूर्णांक IN_NOMINAL_SCH5027[] = अणु5000, 2250, 3300, 1125, 1125, 3300,
					 3300पूर्ण;
अटल स्थिर पूर्णांक IN_NOMINAL_SCH5127[] = अणु2500, 2250, 3300, 1125, 1125, 3300,
					 3300, 1500पूर्ण;
#घोषणा IN_NOMINAL(type)	((type) == sch311x ? IN_NOMINAL_SCH311x : \
				 (type) == sch5027 ? IN_NOMINAL_SCH5027 : \
				 (type) == sch5127 ? IN_NOMINAL_SCH5127 : \
				 IN_NOMINAL_DME1737)

/*
 * Voltage input
 * Voltage inमाला_दो have 16 bits resolution, limit values have 8 bits
 * resolution.
 */
अटल अंतरभूत पूर्णांक IN_FROM_REG(पूर्णांक reg, पूर्णांक nominal, पूर्णांक res)
अणु
	वापस (reg * nominal + (3 << (res - 3))) / (3 << (res - 2));
पूर्ण

अटल अंतरभूत पूर्णांक IN_TO_REG(दीर्घ val, पूर्णांक nominal)
अणु
	val = clamp_val(val, 0, 255 * nominal / 192);
	वापस DIV_ROUND_CLOSEST(val * 192, nominal);
पूर्ण

/*
 * Temperature input
 * The रेजिस्टर values represent temperatures in 2's complement notation from
 * -127 degrees C to +127 degrees C. Temp inमाला_दो have 16 bits resolution, limit
 * values have 8 bits resolution.
 */
अटल अंतरभूत पूर्णांक TEMP_FROM_REG(पूर्णांक reg, पूर्णांक res)
अणु
	वापस (reg * 1000) >> (res - 8);
पूर्ण

अटल अंतरभूत पूर्णांक TEMP_TO_REG(दीर्घ val)
अणु
	val = clamp_val(val, -128000, 127000);
	वापस DIV_ROUND_CLOSEST(val, 1000);
पूर्ण

/* Temperature range */
अटल स्थिर पूर्णांक TEMP_RANGE[] = अणु2000, 2500, 3333, 4000, 5000, 6666, 8000,
				 10000, 13333, 16000, 20000, 26666, 32000,
				 40000, 53333, 80000पूर्ण;

अटल अंतरभूत पूर्णांक TEMP_RANGE_FROM_REG(पूर्णांक reg)
अणु
	वापस TEMP_RANGE[(reg >> 4) & 0x0f];
पूर्ण

अटल पूर्णांक TEMP_RANGE_TO_REG(दीर्घ val, पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 15; i > 0; i--) अणु
		अगर (val > (TEMP_RANGE[i] + TEMP_RANGE[i - 1] + 1) / 2)
			अवरोध;
	पूर्ण

	वापस (reg & 0x0f) | (i << 4);
पूर्ण

/*
 * Temperature hysteresis
 * Register layout:
 *    reg[0] = [H1-3, H1-2, H1-1, H1-0, H2-3, H2-2, H2-1, H2-0]
 *    reg[1] = [H3-3, H3-2, H3-1, H3-0, xxxx, xxxx, xxxx, xxxx]
 */
अटल अंतरभूत पूर्णांक TEMP_HYST_FROM_REG(पूर्णांक reg, पूर्णांक ix)
अणु
	वापस (((ix == 1) ? reg : reg >> 4) & 0x0f) * 1000;
पूर्ण

अटल अंतरभूत पूर्णांक TEMP_HYST_TO_REG(पूर्णांक temp, दीर्घ hyst, पूर्णांक ix, पूर्णांक reg)
अणु
	hyst = clamp_val(hyst, temp - 15000, temp);
	hyst = DIV_ROUND_CLOSEST(temp - hyst, 1000);

	वापस (ix == 1) ? (reg & 0xf0) | hyst : (reg & 0x0f) | (hyst << 4);
पूर्ण

/* Fan input RPM */
अटल अंतरभूत पूर्णांक FAN_FROM_REG(पूर्णांक reg, पूर्णांक tpc)
अणु
	अगर (tpc)
		वापस tpc * reg;
	अन्यथा
		वापस (reg == 0 || reg == 0xffff) ? 0 : 90000 * 60 / reg;
पूर्ण

अटल अंतरभूत पूर्णांक FAN_TO_REG(दीर्घ val, पूर्णांक tpc)
अणु
	अगर (tpc) अणु
		वापस clamp_val(val / tpc, 0, 0xffff);
	पूर्ण अन्यथा अणु
		वापस (val <= 0) ? 0xffff :
			clamp_val(90000 * 60 / val, 0, 0xfffe);
	पूर्ण
पूर्ण

/*
 * Fan TPC (tach pulse count)
 * Converts a रेजिस्टर value to a TPC multiplier or वापसs 0 अगर the tachometer
 * is configured in legacy (non-tpc) mode
 */
अटल अंतरभूत पूर्णांक FAN_TPC_FROM_REG(पूर्णांक reg)
अणु
	वापस (reg & 0x20) ? 0 : 60 >> (reg & 0x03);
पूर्ण

/*
 * Fan type
 * The type of a fan is expressed in number of pulses-per-revolution that it
 * emits
 */
अटल अंतरभूत पूर्णांक FAN_TYPE_FROM_REG(पूर्णांक reg)
अणु
	पूर्णांक edge = (reg >> 1) & 0x03;

	वापस (edge > 0) ? 1 << (edge - 1) : 0;
पूर्ण

अटल अंतरभूत पूर्णांक FAN_TYPE_TO_REG(दीर्घ val, पूर्णांक reg)
अणु
	पूर्णांक edge = (val == 4) ? 3 : val;

	वापस (reg & 0xf9) | (edge << 1);
पूर्ण

/* Fan max RPM */
अटल स्थिर पूर्णांक FAN_MAX[] = अणु0x54, 0x38, 0x2a, 0x21, 0x1c, 0x18, 0x15, 0x12,
			      0x11, 0x0f, 0x0eपूर्ण;

अटल पूर्णांक FAN_MAX_FROM_REG(पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 10; i > 0; i--) अणु
		अगर (reg == FAN_MAX[i])
			अवरोध;
	पूर्ण

	वापस 1000 + i * 500;
पूर्ण

अटल पूर्णांक FAN_MAX_TO_REG(दीर्घ val)
अणु
	पूर्णांक i;

	क्रम (i = 10; i > 0; i--) अणु
		अगर (val > (1000 + (i - 1) * 500))
			अवरोध;
	पूर्ण

	वापस FAN_MAX[i];
पूर्ण

/*
 * PWM enable
 * Register to enable mapping:
 * 000:  2  fan on zone 1 स्वतः
 * 001:  2  fan on zone 2 स्वतः
 * 010:  2  fan on zone 3 स्वतः
 * 011:  0  fan full on
 * 100: -1  fan disabled
 * 101:  2  fan on hottest of zones 2,3 स्वतः
 * 110:  2  fan on hottest of zones 1,2,3 स्वतः
 * 111:  1  fan in manual mode
 */
अटल अंतरभूत पूर्णांक PWM_EN_FROM_REG(पूर्णांक reg)
अणु
	अटल स्थिर पूर्णांक en[] = अणु2, 2, 2, 0, -1, 2, 2, 1पूर्ण;

	वापस en[(reg >> 5) & 0x07];
पूर्ण

अटल अंतरभूत पूर्णांक PWM_EN_TO_REG(पूर्णांक val, पूर्णांक reg)
अणु
	पूर्णांक en = (val == 1) ? 7 : 3;

	वापस (reg & 0x1f) | ((en & 0x07) << 5);
पूर्ण

/*
 * PWM स्वतः channels zone
 * Register to स्वतः channels zone mapping (ACZ is a bitfield with bit x
 * corresponding to zone x+1):
 * 000: 001  fan on zone 1 स्वतः
 * 001: 010  fan on zone 2 स्वतः
 * 010: 100  fan on zone 3 स्वतः
 * 011: 000  fan full on
 * 100: 000  fan disabled
 * 101: 110  fan on hottest of zones 2,3 स्वतः
 * 110: 111  fan on hottest of zones 1,2,3 स्वतः
 * 111: 000  fan in manual mode
 */
अटल अंतरभूत पूर्णांक PWM_ACZ_FROM_REG(पूर्णांक reg)
अणु
	अटल स्थिर पूर्णांक acz[] = अणु1, 2, 4, 0, 0, 6, 7, 0पूर्ण;

	वापस acz[(reg >> 5) & 0x07];
पूर्ण

अटल अंतरभूत पूर्णांक PWM_ACZ_TO_REG(दीर्घ val, पूर्णांक reg)
अणु
	पूर्णांक acz = (val == 4) ? 2 : val - 1;

	वापस (reg & 0x1f) | ((acz & 0x07) << 5);
पूर्ण

/* PWM frequency */
अटल स्थिर पूर्णांक PWM_FREQ[] = अणु11, 15, 22, 29, 35, 44, 59, 88,
			       15000, 20000, 30000, 25000, 0, 0, 0, 0पूर्ण;

अटल अंतरभूत पूर्णांक PWM_FREQ_FROM_REG(पूर्णांक reg)
अणु
	वापस PWM_FREQ[reg & 0x0f];
पूर्ण

अटल पूर्णांक PWM_FREQ_TO_REG(दीर्घ val, पूर्णांक reg)
अणु
	पूर्णांक i;

	/* the first two हालs are special - stupid chip design! */
	अगर (val > 27500) अणु
		i = 10;
	पूर्ण अन्यथा अगर (val > 22500) अणु
		i = 11;
	पूर्ण अन्यथा अणु
		क्रम (i = 9; i > 0; i--) अणु
			अगर (val > (PWM_FREQ[i] + PWM_FREQ[i - 1] + 1) / 2)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस (reg & 0xf0) | i;
पूर्ण

/*
 * PWM ramp rate
 * Register layout:
 *    reg[0] = [OFF3,  OFF2,  OFF1,  RES,   RR1-E, RR1-2, RR1-1, RR1-0]
 *    reg[1] = [RR2-E, RR2-2, RR2-1, RR2-0, RR3-E, RR3-2, RR3-1, RR3-0]
 */
अटल स्थिर u8 PWM_RR[] = अणु206, 104, 69, 41, 26, 18, 10, 5पूर्ण;

अटल अंतरभूत पूर्णांक PWM_RR_FROM_REG(पूर्णांक reg, पूर्णांक ix)
अणु
	पूर्णांक rr = (ix == 1) ? reg >> 4 : reg;

	वापस (rr & 0x08) ? PWM_RR[rr & 0x07] : 0;
पूर्ण

अटल पूर्णांक PWM_RR_TO_REG(दीर्घ val, पूर्णांक ix, पूर्णांक reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 7; i++) अणु
		अगर (val > (PWM_RR[i] + PWM_RR[i + 1] + 1) / 2)
			अवरोध;
	पूर्ण

	वापस (ix == 1) ? (reg & 0x8f) | (i << 4) : (reg & 0xf8) | i;
पूर्ण

/* PWM ramp rate enable */
अटल अंतरभूत पूर्णांक PWM_RR_EN_FROM_REG(पूर्णांक reg, पूर्णांक ix)
अणु
	वापस PWM_RR_FROM_REG(reg, ix) ? 1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक PWM_RR_EN_TO_REG(दीर्घ val, पूर्णांक ix, पूर्णांक reg)
अणु
	पूर्णांक en = (ix == 1) ? 0x80 : 0x08;

	वापस val ? reg | en : reg & ~en;
पूर्ण

/*
 * PWM min/off
 * The PWM min/off bits are part of the PMW ramp rate रेजिस्टर 0 (see above क्रम
 * the रेजिस्टर layout).
 */
अटल अंतरभूत पूर्णांक PWM_OFF_FROM_REG(पूर्णांक reg, पूर्णांक ix)
अणु
	वापस (reg >> (ix + 5)) & 0x01;
पूर्ण

अटल अंतरभूत पूर्णांक PWM_OFF_TO_REG(पूर्णांक val, पूर्णांक ix, पूर्णांक reg)
अणु
	वापस (reg & ~(1 << (ix + 5))) | ((val & 0x01) << (ix + 5));
पूर्ण

/* ---------------------------------------------------------------------
 * Device I/O access
 *
 * ISA access is perक्रमmed through an index/data रेजिस्टर pair and needs to
 * be रक्षित by a mutex during runसमय (not required क्रम initialization).
 * We use data->update_lock क्रम this and need to ensure that we acquire it
 * beक्रमe calling dme1737_पढ़ो or dme1737_ग_लिखो.
 * --------------------------------------------------------------------- */

अटल u8 dme1737_पढ़ो(स्थिर काष्ठा dme1737_data *data, u8 reg)
अणु
	काष्ठा i2c_client *client = data->client;
	s32 val;

	अगर (client) अणु /* I2C device */
		val = i2c_smbus_पढ़ो_byte_data(client, reg);

		अगर (val < 0) अणु
			dev_warn(&client->dev,
				 "Read from register 0x%02x failed! %s\n",
				 reg, DO_REPORT);
		पूर्ण
	पूर्ण अन्यथा अणु /* ISA device */
		outb(reg, data->addr);
		val = inb(data->addr + 1);
	पूर्ण

	वापस val;
पूर्ण

अटल s32 dme1737_ग_लिखो(स्थिर काष्ठा dme1737_data *data, u8 reg, u8 val)
अणु
	काष्ठा i2c_client *client = data->client;
	s32 res = 0;

	अगर (client) अणु /* I2C device */
		res = i2c_smbus_ग_लिखो_byte_data(client, reg, val);

		अगर (res < 0) अणु
			dev_warn(&client->dev,
				 "Write to register 0x%02x failed! %s\n",
				 reg, DO_REPORT);
		पूर्ण
	पूर्ण अन्यथा अणु /* ISA device */
		outb(reg, data->addr);
		outb(val, data->addr + 1);
	पूर्ण

	वापस res;
पूर्ण

अटल काष्ठा dme1737_data *dme1737_update_device(काष्ठा device *dev)
अणु
	काष्ठा dme1737_data *data = dev_get_drvdata(dev);
	पूर्णांक ix;
	u8 lsb[6];

	mutex_lock(&data->update_lock);

	/* Enable a Vbat monitoring cycle every 10 mins */
	अगर (समय_after(jअगरfies, data->last_vbat + 600 * HZ) || !data->valid) अणु
		dme1737_ग_लिखो(data, DME1737_REG_CONFIG, dme1737_पढ़ो(data,
						DME1737_REG_CONFIG) | 0x10);
		data->last_vbat = jअगरfies;
	पूर्ण

	/* Sample रेजिस्टर contents every 1 sec */
	अगर (समय_after(jअगरfies, data->last_update + HZ) || !data->valid) अणु
		अगर (data->has_features & HAS_VID) अणु
			data->vid = dme1737_पढ़ो(data, DME1737_REG_VID) &
				0x3f;
		पूर्ण

		/* In (voltage) रेजिस्टरs */
		क्रम (ix = 0; ix < ARRAY_SIZE(data->in); ix++) अणु
			/*
			 * Voltage inमाला_दो are stored as 16 bit values even
			 * though they have only 12 bits resolution. This is
			 * to make it consistent with the temp inमाला_दो.
			 */
			अगर (ix == 7 && !(data->has_features & HAS_IN7))
				जारी;
			data->in[ix] = dme1737_पढ़ो(data,
					DME1737_REG_IN(ix)) << 8;
			data->in_min[ix] = dme1737_पढ़ो(data,
					DME1737_REG_IN_MIN(ix));
			data->in_max[ix] = dme1737_पढ़ो(data,
					DME1737_REG_IN_MAX(ix));
		पूर्ण

		/* Temp रेजिस्टरs */
		क्रम (ix = 0; ix < ARRAY_SIZE(data->temp); ix++) अणु
			/*
			 * Temp inमाला_दो are stored as 16 bit values even
			 * though they have only 12 bits resolution. This is
			 * to take advantage of implicit conversions between
			 * रेजिस्टर values (2's complement) and temp values
			 * (चिन्हित decimal).
			 */
			data->temp[ix] = dme1737_पढ़ो(data,
					DME1737_REG_TEMP(ix)) << 8;
			data->temp_min[ix] = dme1737_पढ़ो(data,
					DME1737_REG_TEMP_MIN(ix));
			data->temp_max[ix] = dme1737_पढ़ो(data,
					DME1737_REG_TEMP_MAX(ix));
			अगर (data->has_features & HAS_TEMP_OFFSET) अणु
				data->temp_offset[ix] = dme1737_पढ़ो(data,
						DME1737_REG_TEMP_OFFSET(ix));
			पूर्ण
		पूर्ण

		/*
		 * In and temp LSB रेजिस्टरs
		 * The LSBs are latched when the MSBs are पढ़ो, so the order in
		 * which the रेजिस्टरs are पढ़ो (MSB first, then LSB) is
		 * important!
		 */
		क्रम (ix = 0; ix < ARRAY_SIZE(lsb); ix++) अणु
			अगर (ix == 5 && !(data->has_features & HAS_IN7))
				जारी;
			lsb[ix] = dme1737_पढ़ो(data,
					DME1737_REG_IN_TEMP_LSB(ix));
		पूर्ण
		क्रम (ix = 0; ix < ARRAY_SIZE(data->in); ix++) अणु
			अगर (ix == 7 && !(data->has_features & HAS_IN7))
				जारी;
			data->in[ix] |= (lsb[DME1737_REG_IN_LSB[ix]] <<
					DME1737_REG_IN_LSB_SHL[ix]) & 0xf0;
		पूर्ण
		क्रम (ix = 0; ix < ARRAY_SIZE(data->temp); ix++) अणु
			data->temp[ix] |= (lsb[DME1737_REG_TEMP_LSB[ix]] <<
					DME1737_REG_TEMP_LSB_SHL[ix]) & 0xf0;
		पूर्ण

		/* Fan रेजिस्टरs */
		क्रम (ix = 0; ix < ARRAY_SIZE(data->fan); ix++) अणु
			/*
			 * Skip पढ़ोing रेजिस्टरs अगर optional fans are not
			 * present
			 */
			अगर (!(data->has_features & HAS_FAN(ix)))
				जारी;
			data->fan[ix] = dme1737_पढ़ो(data,
					DME1737_REG_FAN(ix));
			data->fan[ix] |= dme1737_पढ़ो(data,
					DME1737_REG_FAN(ix) + 1) << 8;
			data->fan_min[ix] = dme1737_पढ़ो(data,
					DME1737_REG_FAN_MIN(ix));
			data->fan_min[ix] |= dme1737_पढ़ो(data,
					DME1737_REG_FAN_MIN(ix) + 1) << 8;
			data->fan_opt[ix] = dme1737_पढ़ो(data,
					DME1737_REG_FAN_OPT(ix));
			/* fan_max exists only क्रम fan[5-6] */
			अगर (ix > 3) अणु
				data->fan_max[ix - 4] = dme1737_पढ़ो(data,
					DME1737_REG_FAN_MAX(ix));
			पूर्ण
		पूर्ण

		/* PWM रेजिस्टरs */
		क्रम (ix = 0; ix < ARRAY_SIZE(data->pwm); ix++) अणु
			/*
			 * Skip पढ़ोing रेजिस्टरs अगर optional PWMs are not
			 * present
			 */
			अगर (!(data->has_features & HAS_PWM(ix)))
				जारी;
			data->pwm[ix] = dme1737_पढ़ो(data,
					DME1737_REG_PWM(ix));
			data->pwm_freq[ix] = dme1737_पढ़ो(data,
					DME1737_REG_PWM_FREQ(ix));
			/* pwm_config and pwm_min exist only क्रम pwm[1-3] */
			अगर (ix < 3) अणु
				data->pwm_config[ix] = dme1737_पढ़ो(data,
						DME1737_REG_PWM_CONFIG(ix));
				data->pwm_min[ix] = dme1737_पढ़ो(data,
						DME1737_REG_PWM_MIN(ix));
			पूर्ण
		पूर्ण
		क्रम (ix = 0; ix < ARRAY_SIZE(data->pwm_rr); ix++) अणु
			data->pwm_rr[ix] = dme1737_पढ़ो(data,
						DME1737_REG_PWM_RR(ix));
		पूर्ण

		/* Thermal zone रेजिस्टरs */
		क्रम (ix = 0; ix < ARRAY_SIZE(data->zone_low); ix++) अणु
			/* Skip पढ़ोing रेजिस्टरs अगर zone3 is not present */
			अगर ((ix == 2) && !(data->has_features & HAS_ZONE3))
				जारी;
			/* sch5127 zone2 रेजिस्टरs are special */
			अगर ((ix == 1) && (data->type == sch5127)) अणु
				data->zone_low[1] = dme1737_पढ़ो(data,
						DME1737_REG_ZONE_LOW(2));
				data->zone_असल[1] = dme1737_पढ़ो(data,
						DME1737_REG_ZONE_ABS(2));
			पूर्ण अन्यथा अणु
				data->zone_low[ix] = dme1737_पढ़ो(data,
						DME1737_REG_ZONE_LOW(ix));
				data->zone_असल[ix] = dme1737_पढ़ो(data,
						DME1737_REG_ZONE_ABS(ix));
			पूर्ण
		पूर्ण
		अगर (data->has_features & HAS_ZONE_HYST) अणु
			क्रम (ix = 0; ix < ARRAY_SIZE(data->zone_hyst); ix++) अणु
				data->zone_hyst[ix] = dme1737_पढ़ो(data,
						DME1737_REG_ZONE_HYST(ix));
			पूर्ण
		पूर्ण

		/* Alarm रेजिस्टरs */
		data->alarms = dme1737_पढ़ो(data,
						DME1737_REG_ALARM1);
		/*
		 * Bit 7 tells us अगर the other alarm रेजिस्टरs are non-zero and
		 * thereक्रमe also need to be पढ़ो
		 */
		अगर (data->alarms & 0x80) अणु
			data->alarms |= dme1737_पढ़ो(data,
						DME1737_REG_ALARM2) << 8;
			data->alarms |= dme1737_पढ़ो(data,
						DME1737_REG_ALARM3) << 16;
		पूर्ण

		/*
		 * The ISA chips require explicit clearing of alarm bits.
		 * Don't worry, an alarm will come back अगर the condition
		 * that causes it still exists
		 */
		अगर (!data->client) अणु
			अगर (data->alarms & 0xff0000)
				dme1737_ग_लिखो(data, DME1737_REG_ALARM3, 0xff);
			अगर (data->alarms & 0xff00)
				dme1737_ग_लिखो(data, DME1737_REG_ALARM2, 0xff);
			अगर (data->alarms & 0xff)
				dme1737_ग_लिखो(data, DME1737_REG_ALARM1, 0xff);
		पूर्ण

		data->last_update = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/* ---------------------------------------------------------------------
 * Voltage sysfs attributes
 * ix = [0-7]
 * --------------------------------------------------------------------- */

#घोषणा SYS_IN_INPUT	0
#घोषणा SYS_IN_MIN	1
#घोषणा SYS_IN_MAX	2
#घोषणा SYS_IN_ALARM	3

अटल sमाप_प्रकार show_in(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	काष्ठा dme1737_data *data = dme1737_update_device(dev);
	काष्ठा sensor_device_attribute_2
		*sensor_attr_2 = to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	पूर्णांक res;

	चयन (fn) अणु
	हाल SYS_IN_INPUT:
		res = IN_FROM_REG(data->in[ix], data->in_nominal[ix], 16);
		अवरोध;
	हाल SYS_IN_MIN:
		res = IN_FROM_REG(data->in_min[ix], data->in_nominal[ix], 8);
		अवरोध;
	हाल SYS_IN_MAX:
		res = IN_FROM_REG(data->in_max[ix], data->in_nominal[ix], 8);
		अवरोध;
	हाल SYS_IN_ALARM:
		res = (data->alarms >> DME1737_BIT_ALARM_IN[ix]) & 0x01;
		अवरोध;
	शेष:
		res = 0;
		dev_dbg(dev, "Unknown function %d.\n", fn);
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", res);
पूर्ण

अटल sमाप_प्रकार set_in(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dme1737_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2
		*sensor_attr_2 = to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	चयन (fn) अणु
	हाल SYS_IN_MIN:
		data->in_min[ix] = IN_TO_REG(val, data->in_nominal[ix]);
		dme1737_ग_लिखो(data, DME1737_REG_IN_MIN(ix),
			      data->in_min[ix]);
		अवरोध;
	हाल SYS_IN_MAX:
		data->in_max[ix] = IN_TO_REG(val, data->in_nominal[ix]);
		dme1737_ग_लिखो(data, DME1737_REG_IN_MAX(ix),
			      data->in_max[ix]);
		अवरोध;
	शेष:
		dev_dbg(dev, "Unknown function %d.\n", fn);
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* ---------------------------------------------------------------------
 * Temperature sysfs attributes
 * ix = [0-2]
 * --------------------------------------------------------------------- */

#घोषणा SYS_TEMP_INPUT			0
#घोषणा SYS_TEMP_MIN			1
#घोषणा SYS_TEMP_MAX			2
#घोषणा SYS_TEMP_OFFSET			3
#घोषणा SYS_TEMP_ALARM			4
#घोषणा SYS_TEMP_FAULT			5

अटल sमाप_प्रकार show_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा dme1737_data *data = dme1737_update_device(dev);
	काष्ठा sensor_device_attribute_2
		*sensor_attr_2 = to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	पूर्णांक res;

	चयन (fn) अणु
	हाल SYS_TEMP_INPUT:
		res = TEMP_FROM_REG(data->temp[ix], 16);
		अवरोध;
	हाल SYS_TEMP_MIN:
		res = TEMP_FROM_REG(data->temp_min[ix], 8);
		अवरोध;
	हाल SYS_TEMP_MAX:
		res = TEMP_FROM_REG(data->temp_max[ix], 8);
		अवरोध;
	हाल SYS_TEMP_OFFSET:
		res = TEMP_FROM_REG(data->temp_offset[ix], 8);
		अवरोध;
	हाल SYS_TEMP_ALARM:
		res = (data->alarms >> DME1737_BIT_ALARM_TEMP[ix]) & 0x01;
		अवरोध;
	हाल SYS_TEMP_FAULT:
		res = (((u16)data->temp[ix] & 0xff00) == 0x8000);
		अवरोध;
	शेष:
		res = 0;
		dev_dbg(dev, "Unknown function %d.\n", fn);
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", res);
पूर्ण

अटल sमाप_प्रकार set_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dme1737_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2
		*sensor_attr_2 = to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	चयन (fn) अणु
	हाल SYS_TEMP_MIN:
		data->temp_min[ix] = TEMP_TO_REG(val);
		dme1737_ग_लिखो(data, DME1737_REG_TEMP_MIN(ix),
			      data->temp_min[ix]);
		अवरोध;
	हाल SYS_TEMP_MAX:
		data->temp_max[ix] = TEMP_TO_REG(val);
		dme1737_ग_लिखो(data, DME1737_REG_TEMP_MAX(ix),
			      data->temp_max[ix]);
		अवरोध;
	हाल SYS_TEMP_OFFSET:
		data->temp_offset[ix] = TEMP_TO_REG(val);
		dme1737_ग_लिखो(data, DME1737_REG_TEMP_OFFSET(ix),
			      data->temp_offset[ix]);
		अवरोध;
	शेष:
		dev_dbg(dev, "Unknown function %d.\n", fn);
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* ---------------------------------------------------------------------
 * Zone sysfs attributes
 * ix = [0-2]
 * --------------------------------------------------------------------- */

#घोषणा SYS_ZONE_AUTO_CHANNELS_TEMP	0
#घोषणा SYS_ZONE_AUTO_POINT1_TEMP_HYST	1
#घोषणा SYS_ZONE_AUTO_POINT1_TEMP	2
#घोषणा SYS_ZONE_AUTO_POINT2_TEMP	3
#घोषणा SYS_ZONE_AUTO_POINT3_TEMP	4

अटल sमाप_प्रकार show_zone(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा dme1737_data *data = dme1737_update_device(dev);
	काष्ठा sensor_device_attribute_2
		*sensor_attr_2 = to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	पूर्णांक res;

	चयन (fn) अणु
	हाल SYS_ZONE_AUTO_CHANNELS_TEMP:
		/* check config2 क्रम non-standard temp-to-zone mapping */
		अगर ((ix == 1) && (data->config2 & 0x02))
			res = 4;
		अन्यथा
			res = 1 << ix;
		अवरोध;
	हाल SYS_ZONE_AUTO_POINT1_TEMP_HYST:
		res = TEMP_FROM_REG(data->zone_low[ix], 8) -
		      TEMP_HYST_FROM_REG(data->zone_hyst[ix == 2], ix);
		अवरोध;
	हाल SYS_ZONE_AUTO_POINT1_TEMP:
		res = TEMP_FROM_REG(data->zone_low[ix], 8);
		अवरोध;
	हाल SYS_ZONE_AUTO_POINT2_TEMP:
		/* pwm_freq holds the temp range bits in the upper nibble */
		res = TEMP_FROM_REG(data->zone_low[ix], 8) +
		      TEMP_RANGE_FROM_REG(data->pwm_freq[ix]);
		अवरोध;
	हाल SYS_ZONE_AUTO_POINT3_TEMP:
		res = TEMP_FROM_REG(data->zone_असल[ix], 8);
		अवरोध;
	शेष:
		res = 0;
		dev_dbg(dev, "Unknown function %d.\n", fn);
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", res);
पूर्ण

अटल sमाप_प्रकार set_zone(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dme1737_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2
		*sensor_attr_2 = to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	दीर्घ val;
	पूर्णांक temp;
	पूर्णांक err;
	u8 reg;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	चयन (fn) अणु
	हाल SYS_ZONE_AUTO_POINT1_TEMP_HYST:
		/* Refresh the cache */
		data->zone_low[ix] = dme1737_पढ़ो(data,
						  DME1737_REG_ZONE_LOW(ix));
		/* Modअगरy the temp hyst value */
		temp = TEMP_FROM_REG(data->zone_low[ix], 8);
		reg = dme1737_पढ़ो(data, DME1737_REG_ZONE_HYST(ix == 2));
		data->zone_hyst[ix == 2] = TEMP_HYST_TO_REG(temp, val, ix, reg);
		dme1737_ग_लिखो(data, DME1737_REG_ZONE_HYST(ix == 2),
			      data->zone_hyst[ix == 2]);
		अवरोध;
	हाल SYS_ZONE_AUTO_POINT1_TEMP:
		data->zone_low[ix] = TEMP_TO_REG(val);
		dme1737_ग_लिखो(data, DME1737_REG_ZONE_LOW(ix),
			      data->zone_low[ix]);
		अवरोध;
	हाल SYS_ZONE_AUTO_POINT2_TEMP:
		/* Refresh the cache */
		data->zone_low[ix] = dme1737_पढ़ो(data,
						  DME1737_REG_ZONE_LOW(ix));
		/*
		 * Modअगरy the temp range value (which is stored in the upper
		 * nibble of the pwm_freq रेजिस्टर)
		 */
		temp = TEMP_FROM_REG(data->zone_low[ix], 8);
		val = clamp_val(val, temp, temp + 80000);
		reg = dme1737_पढ़ो(data, DME1737_REG_PWM_FREQ(ix));
		data->pwm_freq[ix] = TEMP_RANGE_TO_REG(val - temp, reg);
		dme1737_ग_लिखो(data, DME1737_REG_PWM_FREQ(ix),
			      data->pwm_freq[ix]);
		अवरोध;
	हाल SYS_ZONE_AUTO_POINT3_TEMP:
		data->zone_असल[ix] = TEMP_TO_REG(val);
		dme1737_ग_लिखो(data, DME1737_REG_ZONE_ABS(ix),
			      data->zone_असल[ix]);
		अवरोध;
	शेष:
		dev_dbg(dev, "Unknown function %d.\n", fn);
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* ---------------------------------------------------------------------
 * Fan sysfs attributes
 * ix = [0-5]
 * --------------------------------------------------------------------- */

#घोषणा SYS_FAN_INPUT	0
#घोषणा SYS_FAN_MIN	1
#घोषणा SYS_FAN_MAX	2
#घोषणा SYS_FAN_ALARM	3
#घोषणा SYS_FAN_TYPE	4

अटल sमाप_प्रकार show_fan(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा dme1737_data *data = dme1737_update_device(dev);
	काष्ठा sensor_device_attribute_2
		*sensor_attr_2 = to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	पूर्णांक res;

	चयन (fn) अणु
	हाल SYS_FAN_INPUT:
		res = FAN_FROM_REG(data->fan[ix],
				   ix < 4 ? 0 :
				   FAN_TPC_FROM_REG(data->fan_opt[ix]));
		अवरोध;
	हाल SYS_FAN_MIN:
		res = FAN_FROM_REG(data->fan_min[ix],
				   ix < 4 ? 0 :
				   FAN_TPC_FROM_REG(data->fan_opt[ix]));
		अवरोध;
	हाल SYS_FAN_MAX:
		/* only valid क्रम fan[5-6] */
		res = FAN_MAX_FROM_REG(data->fan_max[ix - 4]);
		अवरोध;
	हाल SYS_FAN_ALARM:
		res = (data->alarms >> DME1737_BIT_ALARM_FAN[ix]) & 0x01;
		अवरोध;
	हाल SYS_FAN_TYPE:
		/* only valid क्रम fan[1-4] */
		res = FAN_TYPE_FROM_REG(data->fan_opt[ix]);
		अवरोध;
	शेष:
		res = 0;
		dev_dbg(dev, "Unknown function %d.\n", fn);
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", res);
पूर्ण

अटल sमाप_प्रकार set_fan(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dme1737_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2
		*sensor_attr_2 = to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	चयन (fn) अणु
	हाल SYS_FAN_MIN:
		अगर (ix < 4) अणु
			data->fan_min[ix] = FAN_TO_REG(val, 0);
		पूर्ण अन्यथा अणु
			/* Refresh the cache */
			data->fan_opt[ix] = dme1737_पढ़ो(data,
						DME1737_REG_FAN_OPT(ix));
			/* Modअगरy the fan min value */
			data->fan_min[ix] = FAN_TO_REG(val,
					FAN_TPC_FROM_REG(data->fan_opt[ix]));
		पूर्ण
		dme1737_ग_लिखो(data, DME1737_REG_FAN_MIN(ix),
			      data->fan_min[ix] & 0xff);
		dme1737_ग_लिखो(data, DME1737_REG_FAN_MIN(ix) + 1,
			      data->fan_min[ix] >> 8);
		अवरोध;
	हाल SYS_FAN_MAX:
		/* Only valid क्रम fan[5-6] */
		data->fan_max[ix - 4] = FAN_MAX_TO_REG(val);
		dme1737_ग_लिखो(data, DME1737_REG_FAN_MAX(ix),
			      data->fan_max[ix - 4]);
		अवरोध;
	हाल SYS_FAN_TYPE:
		/* Only valid क्रम fan[1-4] */
		अगर (!(val == 1 || val == 2 || val == 4)) अणु
			count = -EINVAL;
			dev_warn(dev,
				 "Fan type value %ld not supported. Choose one of 1, 2, or 4.\n",
				 val);
			जाओ निकास;
		पूर्ण
		data->fan_opt[ix] = FAN_TYPE_TO_REG(val, dme1737_पढ़ो(data,
					DME1737_REG_FAN_OPT(ix)));
		dme1737_ग_लिखो(data, DME1737_REG_FAN_OPT(ix),
			      data->fan_opt[ix]);
		अवरोध;
	शेष:
		dev_dbg(dev, "Unknown function %d.\n", fn);
	पूर्ण
निकास:
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* ---------------------------------------------------------------------
 * PWM sysfs attributes
 * ix = [0-4]
 * --------------------------------------------------------------------- */

#घोषणा SYS_PWM				0
#घोषणा SYS_PWM_FREQ			1
#घोषणा SYS_PWM_ENABLE			2
#घोषणा SYS_PWM_RAMP_RATE		3
#घोषणा SYS_PWM_AUTO_CHANNELS_ZONE	4
#घोषणा SYS_PWM_AUTO_PWM_MIN		5
#घोषणा SYS_PWM_AUTO_POINT1_PWM		6
#घोषणा SYS_PWM_AUTO_POINT2_PWM		7

अटल sमाप_प्रकार show_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा dme1737_data *data = dme1737_update_device(dev);
	काष्ठा sensor_device_attribute_2
		*sensor_attr_2 = to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	पूर्णांक res;

	चयन (fn) अणु
	हाल SYS_PWM:
		अगर (PWM_EN_FROM_REG(data->pwm_config[ix]) == 0)
			res = 255;
		अन्यथा
			res = data->pwm[ix];
		अवरोध;
	हाल SYS_PWM_FREQ:
		res = PWM_FREQ_FROM_REG(data->pwm_freq[ix]);
		अवरोध;
	हाल SYS_PWM_ENABLE:
		अगर (ix >= 3)
			res = 1; /* pwm[5-6] hard-wired to manual mode */
		अन्यथा
			res = PWM_EN_FROM_REG(data->pwm_config[ix]);
		अवरोध;
	हाल SYS_PWM_RAMP_RATE:
		/* Only valid क्रम pwm[1-3] */
		res = PWM_RR_FROM_REG(data->pwm_rr[ix > 0], ix);
		अवरोध;
	हाल SYS_PWM_AUTO_CHANNELS_ZONE:
		/* Only valid क्रम pwm[1-3] */
		अगर (PWM_EN_FROM_REG(data->pwm_config[ix]) == 2)
			res = PWM_ACZ_FROM_REG(data->pwm_config[ix]);
		अन्यथा
			res = data->pwm_acz[ix];
		अवरोध;
	हाल SYS_PWM_AUTO_PWM_MIN:
		/* Only valid क्रम pwm[1-3] */
		अगर (PWM_OFF_FROM_REG(data->pwm_rr[0], ix))
			res = data->pwm_min[ix];
		अन्यथा
			res = 0;
		अवरोध;
	हाल SYS_PWM_AUTO_POINT1_PWM:
		/* Only valid क्रम pwm[1-3] */
		res = data->pwm_min[ix];
		अवरोध;
	हाल SYS_PWM_AUTO_POINT2_PWM:
		/* Only valid क्रम pwm[1-3] */
		res = 255; /* hard-wired */
		अवरोध;
	शेष:
		res = 0;
		dev_dbg(dev, "Unknown function %d.\n", fn);
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", res);
पूर्ण

अटल काष्ठा attribute *dme1737_pwm_chmod_attr[];
अटल व्योम dme1737_chmod_file(काष्ठा device*, काष्ठा attribute*, umode_t);

अटल sमाप_प्रकार set_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dme1737_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2
		*sensor_attr_2 = to_sensor_dev_attr_2(attr);
	पूर्णांक ix = sensor_attr_2->index;
	पूर्णांक fn = sensor_attr_2->nr;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	चयन (fn) अणु
	हाल SYS_PWM:
		data->pwm[ix] = clamp_val(val, 0, 255);
		dme1737_ग_लिखो(data, DME1737_REG_PWM(ix), data->pwm[ix]);
		अवरोध;
	हाल SYS_PWM_FREQ:
		data->pwm_freq[ix] = PWM_FREQ_TO_REG(val, dme1737_पढ़ो(data,
						DME1737_REG_PWM_FREQ(ix)));
		dme1737_ग_लिखो(data, DME1737_REG_PWM_FREQ(ix),
			      data->pwm_freq[ix]);
		अवरोध;
	हाल SYS_PWM_ENABLE:
		/* Only valid क्रम pwm[1-3] */
		अगर (val < 0 || val > 2) अणु
			count = -EINVAL;
			dev_warn(dev,
				 "PWM enable %ld not supported. Choose one of 0, 1, or 2.\n",
				 val);
			जाओ निकास;
		पूर्ण
		/* Refresh the cache */
		data->pwm_config[ix] = dme1737_पढ़ो(data,
						DME1737_REG_PWM_CONFIG(ix));
		अगर (val == PWM_EN_FROM_REG(data->pwm_config[ix])) अणु
			/* Bail out अगर no change */
			जाओ निकास;
		पूर्ण
		/* Do some housekeeping अगर we are currently in स्वतः mode */
		अगर (PWM_EN_FROM_REG(data->pwm_config[ix]) == 2) अणु
			/* Save the current zone channel assignment */
			data->pwm_acz[ix] = PWM_ACZ_FROM_REG(
							data->pwm_config[ix]);
			/* Save the current ramp rate state and disable it */
			data->pwm_rr[ix > 0] = dme1737_पढ़ो(data,
						DME1737_REG_PWM_RR(ix > 0));
			data->pwm_rr_en &= ~(1 << ix);
			अगर (PWM_RR_EN_FROM_REG(data->pwm_rr[ix > 0], ix)) अणु
				data->pwm_rr_en |= (1 << ix);
				data->pwm_rr[ix > 0] = PWM_RR_EN_TO_REG(0, ix,
							data->pwm_rr[ix > 0]);
				dme1737_ग_लिखो(data,
					      DME1737_REG_PWM_RR(ix > 0),
					      data->pwm_rr[ix > 0]);
			पूर्ण
		पूर्ण
		/* Set the new PWM mode */
		चयन (val) अणु
		हाल 0:
			/* Change permissions of pwm[ix] to पढ़ो-only */
			dme1737_chmod_file(dev, dme1737_pwm_chmod_attr[ix],
					   S_IRUGO);
			/* Turn fan fully on */
			data->pwm_config[ix] = PWM_EN_TO_REG(0,
							data->pwm_config[ix]);
			dme1737_ग_लिखो(data, DME1737_REG_PWM_CONFIG(ix),
				      data->pwm_config[ix]);
			अवरोध;
		हाल 1:
			/* Turn on manual mode */
			data->pwm_config[ix] = PWM_EN_TO_REG(1,
							data->pwm_config[ix]);
			dme1737_ग_लिखो(data, DME1737_REG_PWM_CONFIG(ix),
				      data->pwm_config[ix]);
			/* Change permissions of pwm[ix] to पढ़ो-ग_लिखोable */
			dme1737_chmod_file(dev, dme1737_pwm_chmod_attr[ix],
					   S_IRUGO | S_IWUSR);
			अवरोध;
		हाल 2:
			/* Change permissions of pwm[ix] to पढ़ो-only */
			dme1737_chmod_file(dev, dme1737_pwm_chmod_attr[ix],
					   S_IRUGO);
			/*
			 * Turn on स्वतः mode using the saved zone channel
			 * assignment
			 */
			data->pwm_config[ix] = PWM_ACZ_TO_REG(
							data->pwm_acz[ix],
							data->pwm_config[ix]);
			dme1737_ग_लिखो(data, DME1737_REG_PWM_CONFIG(ix),
				      data->pwm_config[ix]);
			/* Enable PWM ramp rate अगर previously enabled */
			अगर (data->pwm_rr_en & (1 << ix)) अणु
				data->pwm_rr[ix > 0] = PWM_RR_EN_TO_REG(1, ix,
						dme1737_पढ़ो(data,
						DME1737_REG_PWM_RR(ix > 0)));
				dme1737_ग_लिखो(data,
					      DME1737_REG_PWM_RR(ix > 0),
					      data->pwm_rr[ix > 0]);
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SYS_PWM_RAMP_RATE:
		/* Only valid क्रम pwm[1-3] */
		/* Refresh the cache */
		data->pwm_config[ix] = dme1737_पढ़ो(data,
						DME1737_REG_PWM_CONFIG(ix));
		data->pwm_rr[ix > 0] = dme1737_पढ़ो(data,
						DME1737_REG_PWM_RR(ix > 0));
		/* Set the ramp rate value */
		अगर (val > 0) अणु
			data->pwm_rr[ix > 0] = PWM_RR_TO_REG(val, ix,
							data->pwm_rr[ix > 0]);
		पूर्ण
		/*
		 * Enable/disable the feature only अगर the associated PWM
		 * output is in स्वतःmatic mode.
		 */
		अगर (PWM_EN_FROM_REG(data->pwm_config[ix]) == 2) अणु
			data->pwm_rr[ix > 0] = PWM_RR_EN_TO_REG(val > 0, ix,
							data->pwm_rr[ix > 0]);
		पूर्ण
		dme1737_ग_लिखो(data, DME1737_REG_PWM_RR(ix > 0),
			      data->pwm_rr[ix > 0]);
		अवरोध;
	हाल SYS_PWM_AUTO_CHANNELS_ZONE:
		/* Only valid क्रम pwm[1-3] */
		अगर (!(val == 1 || val == 2 || val == 4 ||
		      val == 6 || val == 7)) अणु
			count = -EINVAL;
			dev_warn(dev,
				 "PWM auto channels zone %ld not supported. Choose one of 1, 2, 4, 6, "
				 "or 7.\n", val);
			जाओ निकास;
		पूर्ण
		/* Refresh the cache */
		data->pwm_config[ix] = dme1737_पढ़ो(data,
						DME1737_REG_PWM_CONFIG(ix));
		अगर (PWM_EN_FROM_REG(data->pwm_config[ix]) == 2) अणु
			/*
			 * PWM is alपढ़ोy in स्वतः mode so update the temp
			 * channel assignment
			 */
			data->pwm_config[ix] = PWM_ACZ_TO_REG(val,
						data->pwm_config[ix]);
			dme1737_ग_लिखो(data, DME1737_REG_PWM_CONFIG(ix),
				      data->pwm_config[ix]);
		पूर्ण अन्यथा अणु
			/*
			 * PWM is not in स्वतः mode so we save the temp
			 * channel assignment क्रम later use
			 */
			data->pwm_acz[ix] = val;
		पूर्ण
		अवरोध;
	हाल SYS_PWM_AUTO_PWM_MIN:
		/* Only valid क्रम pwm[1-3] */
		/* Refresh the cache */
		data->pwm_min[ix] = dme1737_पढ़ो(data,
						DME1737_REG_PWM_MIN(ix));
		/*
		 * There are only 2 values supported क्रम the स्वतः_pwm_min
		 * value: 0 or स्वतः_poपूर्णांक1_pwm. So अगर the temperature drops
		 * below the स्वतः_poपूर्णांक1_temp_hyst value, the fan either turns
		 * off or runs at स्वतः_poपूर्णांक1_pwm duty-cycle.
		 */
		अगर (val > ((data->pwm_min[ix] + 1) / 2)) अणु
			data->pwm_rr[0] = PWM_OFF_TO_REG(1, ix,
						dme1737_पढ़ो(data,
						DME1737_REG_PWM_RR(0)));
		पूर्ण अन्यथा अणु
			data->pwm_rr[0] = PWM_OFF_TO_REG(0, ix,
						dme1737_पढ़ो(data,
						DME1737_REG_PWM_RR(0)));
		पूर्ण
		dme1737_ग_लिखो(data, DME1737_REG_PWM_RR(0),
			      data->pwm_rr[0]);
		अवरोध;
	हाल SYS_PWM_AUTO_POINT1_PWM:
		/* Only valid क्रम pwm[1-3] */
		data->pwm_min[ix] = clamp_val(val, 0, 255);
		dme1737_ग_लिखो(data, DME1737_REG_PWM_MIN(ix),
			      data->pwm_min[ix]);
		अवरोध;
	शेष:
		dev_dbg(dev, "Unknown function %d.\n", fn);
	पूर्ण
निकास:
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* ---------------------------------------------------------------------
 * Miscellaneous sysfs attributes
 * --------------------------------------------------------------------- */

अटल sमाप_प्रकार vrm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा dme1737_data *data = i2c_get_clientdata(client);

	वापस प्र_लिखो(buf, "%d\n", data->vrm);
पूर्ण

अटल sमाप_प्रकार vrm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dme1737_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val > 255)
		वापस -EINVAL;

	data->vrm = val;
	वापस count;
पूर्ण

अटल sमाप_प्रकार cpu0_vid_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dme1737_data *data = dme1737_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", vid_from_reg(data->vid, data->vrm));
पूर्ण

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा dme1737_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", data->name);
पूर्ण

/* ---------------------------------------------------------------------
 * Sysfs device attribute defines and काष्ठाs
 * --------------------------------------------------------------------- */

/* Voltages 0-7 */

#घोषणा SENSOR_DEVICE_ATTR_IN(ix) \
अटल SENSOR_DEVICE_ATTR_2(in##ix##_input, S_IRUGO, \
	show_in, शून्य, SYS_IN_INPUT, ix); \
अटल SENSOR_DEVICE_ATTR_2(in##ix##_min, S_IRUGO | S_IWUSR, \
	show_in, set_in, SYS_IN_MIN, ix); \
अटल SENSOR_DEVICE_ATTR_2(in##ix##_max, S_IRUGO | S_IWUSR, \
	show_in, set_in, SYS_IN_MAX, ix); \
अटल SENSOR_DEVICE_ATTR_2(in##ix##_alarm, S_IRUGO, \
	show_in, शून्य, SYS_IN_ALARM, ix)

SENSOR_DEVICE_ATTR_IN(0);
SENSOR_DEVICE_ATTR_IN(1);
SENSOR_DEVICE_ATTR_IN(2);
SENSOR_DEVICE_ATTR_IN(3);
SENSOR_DEVICE_ATTR_IN(4);
SENSOR_DEVICE_ATTR_IN(5);
SENSOR_DEVICE_ATTR_IN(6);
SENSOR_DEVICE_ATTR_IN(7);

/* Temperatures 1-3 */

#घोषणा SENSOR_DEVICE_ATTR_TEMP(ix) \
अटल SENSOR_DEVICE_ATTR_2(temp##ix##_input, S_IRUGO, \
	show_temp, शून्य, SYS_TEMP_INPUT, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(temp##ix##_min, S_IRUGO | S_IWUSR, \
	show_temp, set_temp, SYS_TEMP_MIN, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(temp##ix##_max, S_IRUGO | S_IWUSR, \
	show_temp, set_temp, SYS_TEMP_MAX, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(temp##ix##_offset, S_IRUGO, \
	show_temp, set_temp, SYS_TEMP_OFFSET, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(temp##ix##_alarm, S_IRUGO, \
	show_temp, शून्य, SYS_TEMP_ALARM, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(temp##ix##_fault, S_IRUGO, \
	show_temp, शून्य, SYS_TEMP_FAULT, ix-1)

SENSOR_DEVICE_ATTR_TEMP(1);
SENSOR_DEVICE_ATTR_TEMP(2);
SENSOR_DEVICE_ATTR_TEMP(3);

/* Zones 1-3 */

#घोषणा SENSOR_DEVICE_ATTR_ZONE(ix) \
अटल SENSOR_DEVICE_ATTR_2(zone##ix##_स्वतः_channels_temp, S_IRUGO, \
	show_zone, शून्य, SYS_ZONE_AUTO_CHANNELS_TEMP, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(zone##ix##_स्वतः_poपूर्णांक1_temp_hyst, S_IRUGO, \
	show_zone, set_zone, SYS_ZONE_AUTO_POINT1_TEMP_HYST, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(zone##ix##_स्वतः_poपूर्णांक1_temp, S_IRUGO, \
	show_zone, set_zone, SYS_ZONE_AUTO_POINT1_TEMP, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(zone##ix##_स्वतः_poपूर्णांक2_temp, S_IRUGO, \
	show_zone, set_zone, SYS_ZONE_AUTO_POINT2_TEMP, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(zone##ix##_स्वतः_poपूर्णांक3_temp, S_IRUGO, \
	show_zone, set_zone, SYS_ZONE_AUTO_POINT3_TEMP, ix-1)

SENSOR_DEVICE_ATTR_ZONE(1);
SENSOR_DEVICE_ATTR_ZONE(2);
SENSOR_DEVICE_ATTR_ZONE(3);

/* Fans 1-4 */

#घोषणा SENSOR_DEVICE_ATTR_FAN_1TO4(ix) \
अटल SENSOR_DEVICE_ATTR_2(fan##ix##_input, S_IRUGO, \
	show_fan, शून्य, SYS_FAN_INPUT, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(fan##ix##_min, S_IRUGO | S_IWUSR, \
	show_fan, set_fan, SYS_FAN_MIN, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(fan##ix##_alarm, S_IRUGO, \
	show_fan, शून्य, SYS_FAN_ALARM, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(fan##ix##_type, S_IRUGO | S_IWUSR, \
	show_fan, set_fan, SYS_FAN_TYPE, ix-1)

SENSOR_DEVICE_ATTR_FAN_1TO4(1);
SENSOR_DEVICE_ATTR_FAN_1TO4(2);
SENSOR_DEVICE_ATTR_FAN_1TO4(3);
SENSOR_DEVICE_ATTR_FAN_1TO4(4);

/* Fans 5-6 */

#घोषणा SENSOR_DEVICE_ATTR_FAN_5TO6(ix) \
अटल SENSOR_DEVICE_ATTR_2(fan##ix##_input, S_IRUGO, \
	show_fan, शून्य, SYS_FAN_INPUT, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(fan##ix##_min, S_IRUGO | S_IWUSR, \
	show_fan, set_fan, SYS_FAN_MIN, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(fan##ix##_alarm, S_IRUGO, \
	show_fan, शून्य, SYS_FAN_ALARM, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(fan##ix##_max, S_IRUGO | S_IWUSR, \
	show_fan, set_fan, SYS_FAN_MAX, ix-1)

SENSOR_DEVICE_ATTR_FAN_5TO6(5);
SENSOR_DEVICE_ATTR_FAN_5TO6(6);

/* PWMs 1-3 */

#घोषणा SENSOR_DEVICE_ATTR_PWM_1TO3(ix) \
अटल SENSOR_DEVICE_ATTR_2(pwm##ix, S_IRUGO, \
	show_pwm, set_pwm, SYS_PWM, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(pwm##ix##_freq, S_IRUGO, \
	show_pwm, set_pwm, SYS_PWM_FREQ, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(pwm##ix##_enable, S_IRUGO, \
	show_pwm, set_pwm, SYS_PWM_ENABLE, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(pwm##ix##_ramp_rate, S_IRUGO, \
	show_pwm, set_pwm, SYS_PWM_RAMP_RATE, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(pwm##ix##_स्वतः_channels_zone, S_IRUGO, \
	show_pwm, set_pwm, SYS_PWM_AUTO_CHANNELS_ZONE, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(pwm##ix##_स्वतः_pwm_min, S_IRUGO, \
	show_pwm, set_pwm, SYS_PWM_AUTO_PWM_MIN, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(pwm##ix##_स्वतः_poपूर्णांक1_pwm, S_IRUGO, \
	show_pwm, set_pwm, SYS_PWM_AUTO_POINT1_PWM, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(pwm##ix##_स्वतः_poपूर्णांक2_pwm, S_IRUGO, \
	show_pwm, शून्य, SYS_PWM_AUTO_POINT2_PWM, ix-1)

SENSOR_DEVICE_ATTR_PWM_1TO3(1);
SENSOR_DEVICE_ATTR_PWM_1TO3(2);
SENSOR_DEVICE_ATTR_PWM_1TO3(3);

/* PWMs 5-6 */

#घोषणा SENSOR_DEVICE_ATTR_PWM_5TO6(ix) \
अटल SENSOR_DEVICE_ATTR_2(pwm##ix, S_IRUGO, \
	show_pwm, set_pwm, SYS_PWM, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(pwm##ix##_freq, S_IRUGO, \
	show_pwm, set_pwm, SYS_PWM_FREQ, ix-1); \
अटल SENSOR_DEVICE_ATTR_2(pwm##ix##_enable, S_IRUGO, \
	show_pwm, शून्य, SYS_PWM_ENABLE, ix-1)

SENSOR_DEVICE_ATTR_PWM_5TO6(5);
SENSOR_DEVICE_ATTR_PWM_5TO6(6);

/* Misc */

अटल DEVICE_ATTR_RW(vrm);
अटल DEVICE_ATTR_RO(cpu0_vid);
अटल DEVICE_ATTR_RO(name);   /* क्रम ISA devices */

/*
 * This काष्ठा holds all the attributes that are always present and need to be
 * created unconditionally. The attributes that need modअगरication of their
 * permissions are created पढ़ो-only and ग_लिखो permissions are added or हटाओd
 * on the fly when required
 */
अटल काष्ठा attribute *dme1737_attr[] = अणु
	/* Voltages */
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in1_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,
	&sensor_dev_attr_in5_alarm.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in6_min.dev_attr.attr,
	&sensor_dev_attr_in6_max.dev_attr.attr,
	&sensor_dev_attr_in6_alarm.dev_attr.attr,
	/* Temperatures */
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_fault.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp3_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_fault.dev_attr.attr,
	/* Zones */
	&sensor_dev_attr_zone1_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_zone1_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_zone1_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_zone1_स्वतः_channels_temp.dev_attr.attr,
	&sensor_dev_attr_zone2_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_zone2_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_zone2_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_zone2_स्वतः_channels_temp.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dme1737_group = अणु
	.attrs = dme1737_attr,
पूर्ण;

/*
 * The following काष्ठा holds temp offset attributes, which are not available
 * in all chips. The following chips support them:
 * DME1737, SCH311x
 */
अटल काष्ठा attribute *dme1737_temp_offset_attr[] = अणु
	&sensor_dev_attr_temp1_offset.dev_attr.attr,
	&sensor_dev_attr_temp2_offset.dev_attr.attr,
	&sensor_dev_attr_temp3_offset.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dme1737_temp_offset_group = अणु
	.attrs = dme1737_temp_offset_attr,
पूर्ण;

/*
 * The following काष्ठा holds VID related attributes, which are not available
 * in all chips. The following chips support them:
 * DME1737
 */
अटल काष्ठा attribute *dme1737_vid_attr[] = अणु
	&dev_attr_vrm.attr,
	&dev_attr_cpu0_vid.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dme1737_vid_group = अणु
	.attrs = dme1737_vid_attr,
पूर्ण;

/*
 * The following काष्ठा holds temp zone 3 related attributes, which are not
 * available in all chips. The following chips support them:
 * DME1737, SCH311x, SCH5027
 */
अटल काष्ठा attribute *dme1737_zone3_attr[] = अणु
	&sensor_dev_attr_zone3_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_zone3_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_zone3_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_zone3_स्वतः_channels_temp.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dme1737_zone3_group = अणु
	.attrs = dme1737_zone3_attr,
पूर्ण;


/*
 * The following काष्ठा holds temp zone hysteresis related attributes, which
 * are not available in all chips. The following chips support them:
 * DME1737, SCH311x
 */
अटल काष्ठा attribute *dme1737_zone_hyst_attr[] = अणु
	&sensor_dev_attr_zone1_स्वतः_poपूर्णांक1_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_zone2_स्वतः_poपूर्णांक1_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_zone3_स्वतः_poपूर्णांक1_temp_hyst.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dme1737_zone_hyst_group = अणु
	.attrs = dme1737_zone_hyst_attr,
पूर्ण;

/*
 * The following काष्ठा holds voltage in7 related attributes, which
 * are not available in all chips. The following chips support them:
 * SCH5127
 */
अटल काष्ठा attribute *dme1737_in7_attr[] = अणु
	&sensor_dev_attr_in7_input.dev_attr.attr,
	&sensor_dev_attr_in7_min.dev_attr.attr,
	&sensor_dev_attr_in7_max.dev_attr.attr,
	&sensor_dev_attr_in7_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dme1737_in7_group = अणु
	.attrs = dme1737_in7_attr,
पूर्ण;

/*
 * The following काष्ठाs hold the PWM attributes, some of which are optional.
 * Their creation depends on the chip configuration which is determined during
 * module load.
 */
अटल काष्ठा attribute *dme1737_pwm1_attr[] = अणु
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm1_freq.dev_attr.attr,
	&sensor_dev_attr_pwm1_enable.dev_attr.attr,
	&sensor_dev_attr_pwm1_ramp_rate.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_channels_zone.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute *dme1737_pwm2_attr[] = अणु
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&sensor_dev_attr_pwm2_freq.dev_attr.attr,
	&sensor_dev_attr_pwm2_enable.dev_attr.attr,
	&sensor_dev_attr_pwm2_ramp_rate.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_channels_zone.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute *dme1737_pwm3_attr[] = अणु
	&sensor_dev_attr_pwm3.dev_attr.attr,
	&sensor_dev_attr_pwm3_freq.dev_attr.attr,
	&sensor_dev_attr_pwm3_enable.dev_attr.attr,
	&sensor_dev_attr_pwm3_ramp_rate.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_channels_zone.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute *dme1737_pwm5_attr[] = अणु
	&sensor_dev_attr_pwm5.dev_attr.attr,
	&sensor_dev_attr_pwm5_freq.dev_attr.attr,
	&sensor_dev_attr_pwm5_enable.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute *dme1737_pwm6_attr[] = अणु
	&sensor_dev_attr_pwm6.dev_attr.attr,
	&sensor_dev_attr_pwm6_freq.dev_attr.attr,
	&sensor_dev_attr_pwm6_enable.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dme1737_pwm_group[] = अणु
	अणु .attrs = dme1737_pwm1_attr पूर्ण,
	अणु .attrs = dme1737_pwm2_attr पूर्ण,
	अणु .attrs = dme1737_pwm3_attr पूर्ण,
	अणु .attrs = शून्य पूर्ण,
	अणु .attrs = dme1737_pwm5_attr पूर्ण,
	अणु .attrs = dme1737_pwm6_attr पूर्ण,
पूर्ण;

/*
 * The following काष्ठा holds स्वतः PWM min attributes, which are not available
 * in all chips. Their creation depends on the chip type which is determined
 * during module load.
 */
अटल काष्ठा attribute *dme1737_स्वतः_pwm_min_attr[] = अणु
	&sensor_dev_attr_pwm1_स्वतः_pwm_min.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_pwm_min.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_pwm_min.dev_attr.attr,
पूर्ण;

/*
 * The following काष्ठाs hold the fan attributes, some of which are optional.
 * Their creation depends on the chip configuration which is determined during
 * module load.
 */
अटल काष्ठा attribute *dme1737_fan1_attr[] = अणु
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan1_type.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute *dme1737_fan2_attr[] = अणु
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_type.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute *dme1737_fan3_attr[] = अणु
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan3_min.dev_attr.attr,
	&sensor_dev_attr_fan3_alarm.dev_attr.attr,
	&sensor_dev_attr_fan3_type.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute *dme1737_fan4_attr[] = अणु
	&sensor_dev_attr_fan4_input.dev_attr.attr,
	&sensor_dev_attr_fan4_min.dev_attr.attr,
	&sensor_dev_attr_fan4_alarm.dev_attr.attr,
	&sensor_dev_attr_fan4_type.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute *dme1737_fan5_attr[] = अणु
	&sensor_dev_attr_fan5_input.dev_attr.attr,
	&sensor_dev_attr_fan5_min.dev_attr.attr,
	&sensor_dev_attr_fan5_alarm.dev_attr.attr,
	&sensor_dev_attr_fan5_max.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute *dme1737_fan6_attr[] = अणु
	&sensor_dev_attr_fan6_input.dev_attr.attr,
	&sensor_dev_attr_fan6_min.dev_attr.attr,
	&sensor_dev_attr_fan6_alarm.dev_attr.attr,
	&sensor_dev_attr_fan6_max.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dme1737_fan_group[] = अणु
	अणु .attrs = dme1737_fan1_attr पूर्ण,
	अणु .attrs = dme1737_fan2_attr पूर्ण,
	अणु .attrs = dme1737_fan3_attr पूर्ण,
	अणु .attrs = dme1737_fan4_attr पूर्ण,
	अणु .attrs = dme1737_fan5_attr पूर्ण,
	अणु .attrs = dme1737_fan6_attr पूर्ण,
पूर्ण;

/*
 * The permissions of the following zone attributes are changed to पढ़ो-
 * ग_लिखोable अगर the chip is *not* locked. Otherwise they stay पढ़ो-only.
 */
अटल काष्ठा attribute *dme1737_zone_chmod_attr[] = अणु
	&sensor_dev_attr_zone1_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_zone1_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_zone1_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_zone2_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_zone2_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_zone2_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dme1737_zone_chmod_group = अणु
	.attrs = dme1737_zone_chmod_attr,
पूर्ण;


/*
 * The permissions of the following zone 3 attributes are changed to पढ़ो-
 * ग_लिखोable अगर the chip is *not* locked. Otherwise they stay पढ़ो-only.
 */
अटल काष्ठा attribute *dme1737_zone3_chmod_attr[] = अणु
	&sensor_dev_attr_zone3_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_zone3_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_zone3_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dme1737_zone3_chmod_group = अणु
	.attrs = dme1737_zone3_chmod_attr,
पूर्ण;

/*
 * The permissions of the following PWM attributes are changed to पढ़ो-
 * ग_लिखोable अगर the chip is *not* locked and the respective PWM is available.
 * Otherwise they stay पढ़ो-only.
 */
अटल काष्ठा attribute *dme1737_pwm1_chmod_attr[] = अणु
	&sensor_dev_attr_pwm1_freq.dev_attr.attr,
	&sensor_dev_attr_pwm1_enable.dev_attr.attr,
	&sensor_dev_attr_pwm1_ramp_rate.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_channels_zone.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute *dme1737_pwm2_chmod_attr[] = अणु
	&sensor_dev_attr_pwm2_freq.dev_attr.attr,
	&sensor_dev_attr_pwm2_enable.dev_attr.attr,
	&sensor_dev_attr_pwm2_ramp_rate.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_channels_zone.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute *dme1737_pwm3_chmod_attr[] = अणु
	&sensor_dev_attr_pwm3_freq.dev_attr.attr,
	&sensor_dev_attr_pwm3_enable.dev_attr.attr,
	&sensor_dev_attr_pwm3_ramp_rate.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_channels_zone.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute *dme1737_pwm5_chmod_attr[] = अणु
	&sensor_dev_attr_pwm5.dev_attr.attr,
	&sensor_dev_attr_pwm5_freq.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute *dme1737_pwm6_chmod_attr[] = अणु
	&sensor_dev_attr_pwm6.dev_attr.attr,
	&sensor_dev_attr_pwm6_freq.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group dme1737_pwm_chmod_group[] = अणु
	अणु .attrs = dme1737_pwm1_chmod_attr पूर्ण,
	अणु .attrs = dme1737_pwm2_chmod_attr पूर्ण,
	अणु .attrs = dme1737_pwm3_chmod_attr पूर्ण,
	अणु .attrs = शून्य पूर्ण,
	अणु .attrs = dme1737_pwm5_chmod_attr पूर्ण,
	अणु .attrs = dme1737_pwm6_chmod_attr पूर्ण,
पूर्ण;

/*
 * Pwm[1-3] are पढ़ो-ग_लिखोable अगर the associated pwm is in manual mode and the
 * chip is not locked. Otherwise they are पढ़ो-only.
 */
अटल काष्ठा attribute *dme1737_pwm_chmod_attr[] = अणु
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&sensor_dev_attr_pwm3.dev_attr.attr,
पूर्ण;

/* ---------------------------------------------------------------------
 * Super-IO functions
 * --------------------------------------------------------------------- */

अटल अंतरभूत व्योम dme1737_sio_enter(पूर्णांक sio_cip)
अणु
	outb(0x55, sio_cip);
पूर्ण

अटल अंतरभूत व्योम dme1737_sio_निकास(पूर्णांक sio_cip)
अणु
	outb(0xaa, sio_cip);
पूर्ण

अटल अंतरभूत पूर्णांक dme1737_sio_inb(पूर्णांक sio_cip, पूर्णांक reg)
अणु
	outb(reg, sio_cip);
	वापस inb(sio_cip + 1);
पूर्ण

अटल अंतरभूत व्योम dme1737_sio_outb(पूर्णांक sio_cip, पूर्णांक reg, पूर्णांक val)
अणु
	outb(reg, sio_cip);
	outb(val, sio_cip + 1);
पूर्ण

/* ---------------------------------------------------------------------
 * Device initialization
 * --------------------------------------------------------------------- */

अटल पूर्णांक dme1737_i2c_get_features(पूर्णांक, काष्ठा dme1737_data*);

अटल व्योम dme1737_chmod_file(काष्ठा device *dev,
			       काष्ठा attribute *attr, umode_t mode)
अणु
	अगर (sysfs_chmod_file(&dev->kobj, attr, mode)) अणु
		dev_warn(dev, "Failed to change permissions of %s.\n",
			 attr->name);
	पूर्ण
पूर्ण

अटल व्योम dme1737_chmod_group(काष्ठा device *dev,
				स्थिर काष्ठा attribute_group *group,
				umode_t mode)
अणु
	काष्ठा attribute **attr;

	क्रम (attr = group->attrs; *attr; attr++)
		dme1737_chmod_file(dev, *attr, mode);
पूर्ण

अटल व्योम dme1737_हटाओ_files(काष्ठा device *dev)
अणु
	काष्ठा dme1737_data *data = dev_get_drvdata(dev);
	पूर्णांक ix;

	क्रम (ix = 0; ix < ARRAY_SIZE(dme1737_fan_group); ix++) अणु
		अगर (data->has_features & HAS_FAN(ix)) अणु
			sysfs_हटाओ_group(&dev->kobj,
					   &dme1737_fan_group[ix]);
		पूर्ण
	पूर्ण

	क्रम (ix = 0; ix < ARRAY_SIZE(dme1737_pwm_group); ix++) अणु
		अगर (data->has_features & HAS_PWM(ix)) अणु
			sysfs_हटाओ_group(&dev->kobj,
					   &dme1737_pwm_group[ix]);
			अगर ((data->has_features & HAS_PWM_MIN) && ix < 3) अणु
				sysfs_हटाओ_file(&dev->kobj,
						dme1737_स्वतः_pwm_min_attr[ix]);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (data->has_features & HAS_TEMP_OFFSET)
		sysfs_हटाओ_group(&dev->kobj, &dme1737_temp_offset_group);
	अगर (data->has_features & HAS_VID)
		sysfs_हटाओ_group(&dev->kobj, &dme1737_vid_group);
	अगर (data->has_features & HAS_ZONE3)
		sysfs_हटाओ_group(&dev->kobj, &dme1737_zone3_group);
	अगर (data->has_features & HAS_ZONE_HYST)
		sysfs_हटाओ_group(&dev->kobj, &dme1737_zone_hyst_group);
	अगर (data->has_features & HAS_IN7)
		sysfs_हटाओ_group(&dev->kobj, &dme1737_in7_group);
	sysfs_हटाओ_group(&dev->kobj, &dme1737_group);

	अगर (!data->client)
		sysfs_हटाओ_file(&dev->kobj, &dev_attr_name.attr);
पूर्ण

अटल पूर्णांक dme1737_create_files(काष्ठा device *dev)
अणु
	काष्ठा dme1737_data *data = dev_get_drvdata(dev);
	पूर्णांक err, ix;

	/* Create a name attribute क्रम ISA devices */
	अगर (!data->client) अणु
		err = sysfs_create_file(&dev->kobj, &dev_attr_name.attr);
		अगर (err)
			जाओ निकास;
	पूर्ण

	/* Create standard sysfs attributes */
	err = sysfs_create_group(&dev->kobj, &dme1737_group);
	अगर (err)
		जाओ निकास_हटाओ;

	/* Create chip-dependent sysfs attributes */
	अगर (data->has_features & HAS_TEMP_OFFSET) अणु
		err = sysfs_create_group(&dev->kobj,
					 &dme1737_temp_offset_group);
		अगर (err)
			जाओ निकास_हटाओ;
	पूर्ण
	अगर (data->has_features & HAS_VID) अणु
		err = sysfs_create_group(&dev->kobj, &dme1737_vid_group);
		अगर (err)
			जाओ निकास_हटाओ;
	पूर्ण
	अगर (data->has_features & HAS_ZONE3) अणु
		err = sysfs_create_group(&dev->kobj, &dme1737_zone3_group);
		अगर (err)
			जाओ निकास_हटाओ;
	पूर्ण
	अगर (data->has_features & HAS_ZONE_HYST) अणु
		err = sysfs_create_group(&dev->kobj, &dme1737_zone_hyst_group);
		अगर (err)
			जाओ निकास_हटाओ;
	पूर्ण
	अगर (data->has_features & HAS_IN7) अणु
		err = sysfs_create_group(&dev->kobj, &dme1737_in7_group);
		अगर (err)
			जाओ निकास_हटाओ;
	पूर्ण

	/* Create fan sysfs attributes */
	क्रम (ix = 0; ix < ARRAY_SIZE(dme1737_fan_group); ix++) अणु
		अगर (data->has_features & HAS_FAN(ix)) अणु
			err = sysfs_create_group(&dev->kobj,
						 &dme1737_fan_group[ix]);
			अगर (err)
				जाओ निकास_हटाओ;
		पूर्ण
	पूर्ण

	/* Create PWM sysfs attributes */
	क्रम (ix = 0; ix < ARRAY_SIZE(dme1737_pwm_group); ix++) अणु
		अगर (data->has_features & HAS_PWM(ix)) अणु
			err = sysfs_create_group(&dev->kobj,
						 &dme1737_pwm_group[ix]);
			अगर (err)
				जाओ निकास_हटाओ;
			अगर ((data->has_features & HAS_PWM_MIN) && (ix < 3)) अणु
				err = sysfs_create_file(&dev->kobj,
						dme1737_स्वतः_pwm_min_attr[ix]);
				अगर (err)
					जाओ निकास_हटाओ;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Inक्रमm अगर the device is locked. Otherwise change the permissions of
	 * selected attributes from पढ़ो-only to पढ़ो-ग_लिखोable.
	 */
	अगर (data->config & 0x02) अणु
		dev_info(dev,
			 "Device is locked. Some attributes will be read-only.\n");
	पूर्ण अन्यथा अणु
		/* Change permissions of zone sysfs attributes */
		dme1737_chmod_group(dev, &dme1737_zone_chmod_group,
				    S_IRUGO | S_IWUSR);

		/* Change permissions of chip-dependent sysfs attributes */
		अगर (data->has_features & HAS_TEMP_OFFSET) अणु
			dme1737_chmod_group(dev, &dme1737_temp_offset_group,
					    S_IRUGO | S_IWUSR);
		पूर्ण
		अगर (data->has_features & HAS_ZONE3) अणु
			dme1737_chmod_group(dev, &dme1737_zone3_chmod_group,
					    S_IRUGO | S_IWUSR);
		पूर्ण
		अगर (data->has_features & HAS_ZONE_HYST) अणु
			dme1737_chmod_group(dev, &dme1737_zone_hyst_group,
					    S_IRUGO | S_IWUSR);
		पूर्ण

		/* Change permissions of PWM sysfs attributes */
		क्रम (ix = 0; ix < ARRAY_SIZE(dme1737_pwm_chmod_group); ix++) अणु
			अगर (data->has_features & HAS_PWM(ix)) अणु
				dme1737_chmod_group(dev,
						&dme1737_pwm_chmod_group[ix],
						S_IRUGO | S_IWUSR);
				अगर ((data->has_features & HAS_PWM_MIN) &&
				    ix < 3) अणु
					dme1737_chmod_file(dev,
						dme1737_स्वतः_pwm_min_attr[ix],
						S_IRUGO | S_IWUSR);
				पूर्ण
			पूर्ण
		पूर्ण

		/* Change permissions of pwm[1-3] अगर in manual mode */
		क्रम (ix = 0; ix < 3; ix++) अणु
			अगर ((data->has_features & HAS_PWM(ix)) &&
			    (PWM_EN_FROM_REG(data->pwm_config[ix]) == 1)) अणु
				dme1737_chmod_file(dev,
						dme1737_pwm_chmod_attr[ix],
						S_IRUGO | S_IWUSR);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

निकास_हटाओ:
	dme1737_हटाओ_files(dev);
निकास:
	वापस err;
पूर्ण

अटल पूर्णांक dme1737_init_device(काष्ठा device *dev)
अणु
	काष्ठा dme1737_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ix;
	u8 reg;

	/* Poपूर्णांक to the right nominal voltages array */
	data->in_nominal = IN_NOMINAL(data->type);

	data->config = dme1737_पढ़ो(data, DME1737_REG_CONFIG);
	/* Inक्रमm अगर part is not monitoring/started */
	अगर (!(data->config & 0x01)) अणु
		अगर (!क्रमce_start) अणु
			dev_err(dev,
				"Device is not monitoring. Use the force_start load parameter to override.\n");
			वापस -EFAULT;
		पूर्ण

		/* Force monitoring */
		data->config |= 0x01;
		dme1737_ग_लिखो(data, DME1737_REG_CONFIG, data->config);
	पूर्ण
	/* Inक्रमm अगर part is not पढ़ोy */
	अगर (!(data->config & 0x04)) अणु
		dev_err(dev, "Device is not ready.\n");
		वापस -EFAULT;
	पूर्ण

	/*
	 * Determine which optional fan and pwm features are enabled (only
	 * valid क्रम I2C devices)
	 */
	अगर (client) अणु   /* I2C chip */
		data->config2 = dme1737_पढ़ो(data, DME1737_REG_CONFIG2);
		/* Check अगर optional fan3 input is enabled */
		अगर (data->config2 & 0x04)
			data->has_features |= HAS_FAN(2);

		/*
		 * Fan4 and pwm3 are only available अगर the client's I2C address
		 * is the शेष 0x2e. Otherwise the I/Os associated with
		 * these functions are used क्रम addr enable/select.
		 */
		अगर (client->addr == 0x2e)
			data->has_features |= HAS_FAN(3) | HAS_PWM(2);

		/*
		 * Determine which of the optional fan[5-6] and pwm[5-6]
		 * features are enabled. For this, we need to query the runसमय
		 * रेजिस्टरs through the Super-IO LPC पूर्णांकerface. Try both
		 * config ports 0x2e and 0x4e.
		 */
		अगर (dme1737_i2c_get_features(0x2e, data) &&
		    dme1737_i2c_get_features(0x4e, data)) अणु
			dev_warn(dev,
				 "Failed to query Super-IO for optional features.\n");
		पूर्ण
	पूर्ण

	/* Fan[1-2] and pwm[1-2] are present in all chips */
	data->has_features |= HAS_FAN(0) | HAS_FAN(1) | HAS_PWM(0) | HAS_PWM(1);

	/* Chip-dependent features */
	चयन (data->type) अणु
	हाल dme1737:
		data->has_features |= HAS_TEMP_OFFSET | HAS_VID | HAS_ZONE3 |
			HAS_ZONE_HYST | HAS_PWM_MIN;
		अवरोध;
	हाल sch311x:
		data->has_features |= HAS_TEMP_OFFSET | HAS_ZONE3 |
			HAS_ZONE_HYST | HAS_PWM_MIN | HAS_FAN(2) | HAS_PWM(2);
		अवरोध;
	हाल sch5027:
		data->has_features |= HAS_ZONE3;
		अवरोध;
	हाल sch5127:
		data->has_features |= HAS_FAN(2) | HAS_PWM(2) | HAS_IN7;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dev_info(dev,
		 "Optional features: pwm3=%s, pwm5=%s, pwm6=%s, fan3=%s, fan4=%s, fan5=%s, fan6=%s.\n",
		 (data->has_features & HAS_PWM(2)) ? "yes" : "no",
		 (data->has_features & HAS_PWM(4)) ? "yes" : "no",
		 (data->has_features & HAS_PWM(5)) ? "yes" : "no",
		 (data->has_features & HAS_FAN(2)) ? "yes" : "no",
		 (data->has_features & HAS_FAN(3)) ? "yes" : "no",
		 (data->has_features & HAS_FAN(4)) ? "yes" : "no",
		 (data->has_features & HAS_FAN(5)) ? "yes" : "no");

	reg = dme1737_पढ़ो(data, DME1737_REG_TACH_PWM);
	/* Inक्रमm अगर fan-to-pwm mapping dअगरfers from the शेष */
	अगर (client && reg != 0xa4) अणु   /* I2C chip */
		dev_warn(dev,
			 "Non-standard fan to pwm mapping: fan1->pwm%d, fan2->pwm%d, fan3->pwm%d, fan4->pwm%d. %s\n",
			 (reg & 0x03) + 1, ((reg >> 2) & 0x03) + 1,
			 ((reg >> 4) & 0x03) + 1, ((reg >> 6) & 0x03) + 1,
			 DO_REPORT);
	पूर्ण अन्यथा अगर (!client && reg != 0x24) अणु   /* ISA chip */
		dev_warn(dev,
			 "Non-standard fan to pwm mapping: fan1->pwm%d, fan2->pwm%d, fan3->pwm%d. %s\n",
			 (reg & 0x03) + 1, ((reg >> 2) & 0x03) + 1,
			 ((reg >> 4) & 0x03) + 1, DO_REPORT);
	पूर्ण

	/*
	 * Switch pwm[1-3] to manual mode अगर they are currently disabled and
	 * set the duty-cycles to 0% (which is identical to the PWMs being
	 * disabled).
	 */
	अगर (!(data->config & 0x02)) अणु
		क्रम (ix = 0; ix < 3; ix++) अणु
			data->pwm_config[ix] = dme1737_पढ़ो(data,
						DME1737_REG_PWM_CONFIG(ix));
			अगर ((data->has_features & HAS_PWM(ix)) &&
			    (PWM_EN_FROM_REG(data->pwm_config[ix]) == -1)) अणु
				dev_info(dev,
					 "Switching pwm%d to manual mode.\n",
					 ix + 1);
				data->pwm_config[ix] = PWM_EN_TO_REG(1,
							data->pwm_config[ix]);
				dme1737_ग_लिखो(data, DME1737_REG_PWM(ix), 0);
				dme1737_ग_लिखो(data,
					      DME1737_REG_PWM_CONFIG(ix),
					      data->pwm_config[ix]);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Initialize the शेष PWM स्वतः channels zone (acz) assignments */
	data->pwm_acz[0] = 1;	/* pwm1 -> zone1 */
	data->pwm_acz[1] = 2;	/* pwm2 -> zone2 */
	data->pwm_acz[2] = 4;	/* pwm3 -> zone3 */

	/* Set VRM */
	अगर (data->has_features & HAS_VID)
		data->vrm = vid_which_vrm();

	वापस 0;
पूर्ण

/* ---------------------------------------------------------------------
 * I2C device detection and registration
 * --------------------------------------------------------------------- */

अटल काष्ठा i2c_driver dme1737_i2c_driver;

अटल पूर्णांक dme1737_i2c_get_features(पूर्णांक sio_cip, काष्ठा dme1737_data *data)
अणु
	पूर्णांक err = 0, reg;
	u16 addr;

	dme1737_sio_enter(sio_cip);

	/*
	 * Check device ID
	 * We currently know about two kinds of DME1737 and SCH5027.
	 */
	reg = क्रमce_id ? क्रमce_id : dme1737_sio_inb(sio_cip, 0x20);
	अगर (!(reg == DME1737_ID_1 || reg == DME1737_ID_2 ||
	      reg == SCH5027_ID)) अणु
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	/* Select logical device A (runसमय रेजिस्टरs) */
	dme1737_sio_outb(sio_cip, 0x07, 0x0a);

	/* Get the base address of the runसमय रेजिस्टरs */
	addr = (dme1737_sio_inb(sio_cip, 0x60) << 8) |
		dme1737_sio_inb(sio_cip, 0x61);
	अगर (!addr) अणु
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	/*
	 * Read the runसमय रेजिस्टरs to determine which optional features
	 * are enabled and available. Bits [3:2] of रेजिस्टरs 0x43-0x46 are set
	 * to '10' अगर the respective feature is enabled.
	 */
	अगर ((inb(addr + 0x43) & 0x0c) == 0x08) /* fan6 */
		data->has_features |= HAS_FAN(5);
	अगर ((inb(addr + 0x44) & 0x0c) == 0x08) /* pwm6 */
		data->has_features |= HAS_PWM(5);
	अगर ((inb(addr + 0x45) & 0x0c) == 0x08) /* fan5 */
		data->has_features |= HAS_FAN(4);
	अगर ((inb(addr + 0x46) & 0x0c) == 0x08) /* pwm5 */
		data->has_features |= HAS_PWM(4);

निकास:
	dme1737_sio_निकास(sio_cip);

	वापस err;
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक dme1737_i2c_detect(काष्ठा i2c_client *client,
			      काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा device *dev = &adapter->dev;
	u8 company, verstep = 0;
	स्थिर अक्षर *name;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	company = i2c_smbus_पढ़ो_byte_data(client, DME1737_REG_COMPANY);
	verstep = i2c_smbus_पढ़ो_byte_data(client, DME1737_REG_VERSTEP);

	अगर (company == DME1737_COMPANY_SMSC &&
	    verstep == SCH5027_VERSTEP) अणु
		name = "sch5027";
	पूर्ण अन्यथा अगर (company == DME1737_COMPANY_SMSC &&
		   (verstep & DME1737_VERSTEP_MASK) == DME1737_VERSTEP) अणु
		name = "dme1737";
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	dev_info(dev, "Found a %s chip at 0x%02x (rev 0x%02x).\n",
		 verstep == SCH5027_VERSTEP ? "SCH5027" : "DME1737",
		 client->addr, verstep);
	strlcpy(info->type, name, I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id dme1737_id[];

अटल पूर्णांक dme1737_i2c_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा dme1737_data *data;
	काष्ठा device *dev = &client->dev;
	पूर्णांक err;

	data = devm_kzalloc(dev, माप(काष्ठा dme1737_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	data->type = i2c_match_id(dme1737_id, client)->driver_data;
	data->client = client;
	data->name = client->name;
	mutex_init(&data->update_lock);

	/* Initialize the DME1737 chip */
	err = dme1737_init_device(dev);
	अगर (err) अणु
		dev_err(dev, "Failed to initialize device.\n");
		वापस err;
	पूर्ण

	/* Create sysfs files */
	err = dme1737_create_files(dev);
	अगर (err) अणु
		dev_err(dev, "Failed to create sysfs files.\n");
		वापस err;
	पूर्ण

	/* Register device */
	data->hwmon_dev = hwmon_device_रेजिस्टर(dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		dev_err(dev, "Failed to register device.\n");
		err = PTR_ERR(data->hwmon_dev);
		जाओ निकास_हटाओ;
	पूर्ण

	वापस 0;

निकास_हटाओ:
	dme1737_हटाओ_files(dev);
	वापस err;
पूर्ण

अटल पूर्णांक dme1737_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा dme1737_data *data = i2c_get_clientdata(client);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	dme1737_हटाओ_files(&client->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id dme1737_id[] = अणु
	अणु "dme1737", dme1737 पूर्ण,
	अणु "sch5027", sch5027 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, dme1737_id);

अटल काष्ठा i2c_driver dme1737_i2c_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		.name = "dme1737",
	पूर्ण,
	.probe_new = dme1737_i2c_probe,
	.हटाओ = dme1737_i2c_हटाओ,
	.id_table = dme1737_id,
	.detect = dme1737_i2c_detect,
	.address_list = normal_i2c,
पूर्ण;

/* ---------------------------------------------------------------------
 * ISA device detection and registration
 * --------------------------------------------------------------------- */

अटल पूर्णांक __init dme1737_isa_detect(पूर्णांक sio_cip, अचिन्हित लघु *addr)
अणु
	पूर्णांक err = 0, reg;
	अचिन्हित लघु base_addr;

	dme1737_sio_enter(sio_cip);

	/*
	 * Check device ID
	 * We currently know about SCH3112, SCH3114, SCH3116, and SCH5127
	 */
	reg = क्रमce_id ? क्रमce_id : dme1737_sio_inb(sio_cip, 0x20);
	अगर (!(reg == SCH3112_ID || reg == SCH3114_ID || reg == SCH3116_ID ||
	      reg == SCH5127_ID)) अणु
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	/* Select logical device A (runसमय रेजिस्टरs) */
	dme1737_sio_outb(sio_cip, 0x07, 0x0a);

	/* Get the base address of the runसमय रेजिस्टरs */
	base_addr = (dme1737_sio_inb(sio_cip, 0x60) << 8) |
		     dme1737_sio_inb(sio_cip, 0x61);
	अगर (!base_addr) अणु
		pr_err("Base address not set\n");
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	/*
	 * Access to the hwmon रेजिस्टरs is through an index/data रेजिस्टर
	 * pair located at offset 0x70/0x71.
	 */
	*addr = base_addr + 0x70;

निकास:
	dme1737_sio_निकास(sio_cip);
	वापस err;
पूर्ण

अटल पूर्णांक __init dme1737_isa_device_add(अचिन्हित लघु addr)
अणु
	काष्ठा resource res = अणु
		.start	= addr,
		.end	= addr + DME1737_EXTENT - 1,
		.name	= "dme1737",
		.flags	= IORESOURCE_IO,
	पूर्ण;
	पूर्णांक err;

	err = acpi_check_resource_conflict(&res);
	अगर (err)
		जाओ निकास;

	pdev = platक्रमm_device_alloc("dme1737", addr);
	अगर (!pdev) अणु
		pr_err("Failed to allocate device\n");
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण

	err = platक्रमm_device_add_resources(pdev, &res, 1);
	अगर (err) अणु
		pr_err("Failed to add device resource (err = %d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	err = platक्रमm_device_add(pdev);
	अगर (err) अणु
		pr_err("Failed to add device (err = %d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	वापस 0;

निकास_device_put:
	platक्रमm_device_put(pdev);
	pdev = शून्य;
निकास:
	वापस err;
पूर्ण

अटल पूर्णांक dme1737_isa_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u8 company, device;
	काष्ठा resource *res;
	काष्ठा dme1737_data *data;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक err;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!devm_request_region(dev, res->start, DME1737_EXTENT, "dme1737")) अणु
		dev_err(dev, "Failed to request region 0x%04x-0x%04x.\n",
			(अचिन्हित लघु)res->start,
			(अचिन्हित लघु)res->start + DME1737_EXTENT - 1);
		वापस -EBUSY;
	पूर्ण

	data = devm_kzalloc(dev, माप(काष्ठा dme1737_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->addr = res->start;
	platक्रमm_set_drvdata(pdev, data);

	/* Skip chip detection अगर module is loaded with क्रमce_id parameter */
	चयन (क्रमce_id) अणु
	हाल SCH3112_ID:
	हाल SCH3114_ID:
	हाल SCH3116_ID:
		data->type = sch311x;
		अवरोध;
	हाल SCH5127_ID:
		data->type = sch5127;
		अवरोध;
	शेष:
		company = dme1737_पढ़ो(data, DME1737_REG_COMPANY);
		device = dme1737_पढ़ो(data, DME1737_REG_DEVICE);

		अगर ((company == DME1737_COMPANY_SMSC) &&
		    (device == SCH311X_DEVICE)) अणु
			data->type = sch311x;
		पूर्ण अन्यथा अगर ((company == DME1737_COMPANY_SMSC) &&
			   (device == SCH5127_DEVICE)) अणु
			data->type = sch5127;
		पूर्ण अन्यथा अणु
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (data->type == sch5127)
		data->name = "sch5127";
	अन्यथा
		data->name = "sch311x";

	/* Initialize the mutex */
	mutex_init(&data->update_lock);

	dev_info(dev, "Found a %s chip at 0x%04x\n",
		 data->type == sch5127 ? "SCH5127" : "SCH311x", data->addr);

	/* Initialize the chip */
	err = dme1737_init_device(dev);
	अगर (err) अणु
		dev_err(dev, "Failed to initialize device.\n");
		वापस err;
	पूर्ण

	/* Create sysfs files */
	err = dme1737_create_files(dev);
	अगर (err) अणु
		dev_err(dev, "Failed to create sysfs files.\n");
		वापस err;
	पूर्ण

	/* Register device */
	data->hwmon_dev = hwmon_device_रेजिस्टर(dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		dev_err(dev, "Failed to register device.\n");
		err = PTR_ERR(data->hwmon_dev);
		जाओ निकास_हटाओ_files;
	पूर्ण

	वापस 0;

निकास_हटाओ_files:
	dme1737_हटाओ_files(dev);
	वापस err;
पूर्ण

अटल पूर्णांक dme1737_isa_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dme1737_data *data = platक्रमm_get_drvdata(pdev);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	dme1737_हटाओ_files(&pdev->dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver dme1737_isa_driver = अणु
	.driver = अणु
		.name = "dme1737",
	पूर्ण,
	.probe = dme1737_isa_probe,
	.हटाओ = dme1737_isa_हटाओ,
पूर्ण;

/* ---------------------------------------------------------------------
 * Module initialization and cleanup
 * --------------------------------------------------------------------- */

अटल पूर्णांक __init dme1737_init(व्योम)
अणु
	पूर्णांक err;
	अचिन्हित लघु addr;

	err = i2c_add_driver(&dme1737_i2c_driver);
	अगर (err)
		जाओ निकास;

	अगर (dme1737_isa_detect(0x2e, &addr) &&
	    dme1737_isa_detect(0x4e, &addr) &&
	    (!probe_all_addr ||
	     (dme1737_isa_detect(0x162e, &addr) &&
	      dme1737_isa_detect(0x164e, &addr)))) अणु
		/* Return 0 अगर we didn't find an ISA device */
		वापस 0;
	पूर्ण

	err = platक्रमm_driver_रेजिस्टर(&dme1737_isa_driver);
	अगर (err)
		जाओ निकास_del_i2c_driver;

	/* Sets global pdev as a side effect */
	err = dme1737_isa_device_add(addr);
	अगर (err)
		जाओ निकास_del_isa_driver;

	वापस 0;

निकास_del_isa_driver:
	platक्रमm_driver_unरेजिस्टर(&dme1737_isa_driver);
निकास_del_i2c_driver:
	i2c_del_driver(&dme1737_i2c_driver);
निकास:
	वापस err;
पूर्ण

अटल व्योम __निकास dme1737_निकास(व्योम)
अणु
	अगर (pdev) अणु
		platक्रमm_device_unरेजिस्टर(pdev);
		platक्रमm_driver_unरेजिस्टर(&dme1737_isa_driver);
	पूर्ण

	i2c_del_driver(&dme1737_i2c_driver);
पूर्ण

MODULE_AUTHOR("Juerg Haefliger <juergh@gmail.com>");
MODULE_DESCRIPTION("DME1737 sensors");
MODULE_LICENSE("GPL");

module_init(dme1737_init);
module_निकास(dme1737_निकास);
