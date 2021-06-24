<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lm85.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *	    monitoring
 * Copyright (c) 1998, 1999  Froकरो Looijaard <froकरोl@dds.nl>
 * Copyright (c) 2002, 2003  Philip Pokorny <ppokorny@penguincomputing.com>
 * Copyright (c) 2003        Margit Schubert-While <margitsw@t-online.de>
 * Copyright (c) 2004        Justin Thiessen <jthiessen@penguincomputing.com>
 * Copyright (C) 2007--2014  Jean Delvare <jdelvare@suse.de>
 *
 * Chip details at	      <http://www.national.com/ds/LM/LM85.pdf>
 */

#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/util_macros.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2c, 0x2d, 0x2e, I2C_CLIENT_END पूर्ण;

क्रमागत chips अणु
	lm85, lm96000,
	adm1027, adt7463, adt7468,
	emc6d100, emc6d102, emc6d103, emc6d103s
पूर्ण;

/* The LM85 रेजिस्टरs */

#घोषणा LM85_REG_IN(nr)			(0x20 + (nr))
#घोषणा LM85_REG_IN_MIN(nr)		(0x44 + (nr) * 2)
#घोषणा LM85_REG_IN_MAX(nr)		(0x45 + (nr) * 2)

#घोषणा LM85_REG_TEMP(nr)		(0x25 + (nr))
#घोषणा LM85_REG_TEMP_MIN(nr)		(0x4e + (nr) * 2)
#घोषणा LM85_REG_TEMP_MAX(nr)		(0x4f + (nr) * 2)

/* Fan speeds are LSB, MSB (2 bytes) */
#घोषणा LM85_REG_FAN(nr)		(0x28 + (nr) * 2)
#घोषणा LM85_REG_FAN_MIN(nr)		(0x54 + (nr) * 2)

#घोषणा LM85_REG_PWM(nr)		(0x30 + (nr))

#घोषणा LM85_REG_COMPANY		0x3e
#घोषणा LM85_REG_VERSTEP		0x3f

#घोषणा ADT7468_REG_CFG5		0x7c
#घोषणा ADT7468_OFF64			(1 << 0)
#घोषणा ADT7468_HFPWM			(1 << 1)
#घोषणा IS_ADT7468_OFF64(data)		\
	((data)->type == adt7468 && !((data)->cfg5 & ADT7468_OFF64))
#घोषणा IS_ADT7468_HFPWM(data)		\
	((data)->type == adt7468 && !((data)->cfg5 & ADT7468_HFPWM))

/* These are the recognized values क्रम the above regs */
#घोषणा LM85_COMPANY_NATIONAL		0x01
#घोषणा LM85_COMPANY_ANALOG_DEV		0x41
#घोषणा LM85_COMPANY_SMSC		0x5c
#घोषणा LM85_VERSTEP_LM85C		0x60
#घोषणा LM85_VERSTEP_LM85B		0x62
#घोषणा LM85_VERSTEP_LM96000_1		0x68
#घोषणा LM85_VERSTEP_LM96000_2		0x69
#घोषणा LM85_VERSTEP_ADM1027		0x60
#घोषणा LM85_VERSTEP_ADT7463		0x62
#घोषणा LM85_VERSTEP_ADT7463C		0x6A
#घोषणा LM85_VERSTEP_ADT7468_1		0x71
#घोषणा LM85_VERSTEP_ADT7468_2		0x72
#घोषणा LM85_VERSTEP_EMC6D100_A0        0x60
#घोषणा LM85_VERSTEP_EMC6D100_A1        0x61
#घोषणा LM85_VERSTEP_EMC6D102		0x65
#घोषणा LM85_VERSTEP_EMC6D103_A0	0x68
#घोषणा LM85_VERSTEP_EMC6D103_A1	0x69
#घोषणा LM85_VERSTEP_EMC6D103S		0x6A	/* Also known as EMC6D103:A2 */

#घोषणा LM85_REG_CONFIG			0x40

#घोषणा LM85_REG_ALARM1			0x41
#घोषणा LM85_REG_ALARM2			0x42

#घोषणा LM85_REG_VID			0x43

/* Automated FAN control */
#घोषणा LM85_REG_AFAN_CONFIG(nr)	(0x5c + (nr))
#घोषणा LM85_REG_AFAN_RANGE(nr)		(0x5f + (nr))
#घोषणा LM85_REG_AFAN_SPIKE1		0x62
#घोषणा LM85_REG_AFAN_MINPWM(nr)	(0x64 + (nr))
#घोषणा LM85_REG_AFAN_LIMIT(nr)		(0x67 + (nr))
#घोषणा LM85_REG_AFAN_CRITICAL(nr)	(0x6a + (nr))
#घोषणा LM85_REG_AFAN_HYST1		0x6d
#घोषणा LM85_REG_AFAN_HYST2		0x6e

#घोषणा ADM1027_REG_EXTEND_ADC1		0x76
#घोषणा ADM1027_REG_EXTEND_ADC2		0x77

#घोषणा EMC6D100_REG_ALARM3             0x7d
/* IN5, IN6 and IN7 */
#घोषणा EMC6D100_REG_IN(nr)             (0x70 + ((nr) - 5))
#घोषणा EMC6D100_REG_IN_MIN(nr)         (0x73 + ((nr) - 5) * 2)
#घोषणा EMC6D100_REG_IN_MAX(nr)         (0x74 + ((nr) - 5) * 2)
#घोषणा EMC6D102_REG_EXTEND_ADC1	0x85
#घोषणा EMC6D102_REG_EXTEND_ADC2	0x86
#घोषणा EMC6D102_REG_EXTEND_ADC3	0x87
#घोषणा EMC6D102_REG_EXTEND_ADC4	0x88

/*
 * Conversions. Rounding and limit checking is only करोne on the TO_REG
 * variants. Note that you should be a bit careful with which arguments
 * these macros are called: arguments may be evaluated more than once.
 */

/* IN are scaled according to built-in resistors */
अटल स्थिर पूर्णांक lm85_scaling[] = अणु  /* .001 Volts */
	2500, 2250, 3300, 5000, 12000,
	3300, 1500, 1800 /*EMC6D100*/
पूर्ण;
#घोषणा SCALE(val, from, to)	(((val) * (to) + ((from) / 2)) / (from))

#घोषणा INS_TO_REG(n, val)	\
		SCALE(clamp_val(val, 0, 255 * lm85_scaling[n] / 192), \
		      lm85_scaling[n], 192)

#घोषणा INSEXT_FROM_REG(n, val, ext)	\
		SCALE(((val) << 4) + (ext), 192 << 4, lm85_scaling[n])

#घोषणा INS_FROM_REG(n, val)	SCALE((val), 192, lm85_scaling[n])

/* FAN speed is measured using 90kHz घड़ी */
अटल अंतरभूत u16 FAN_TO_REG(अचिन्हित दीर्घ val)
अणु
	अगर (!val)
		वापस 0xffff;
	वापस clamp_val(5400000 / val, 1, 0xfffe);
पूर्ण
#घोषणा FAN_FROM_REG(val)	((val) == 0 ? -1 : (val) == 0xffff ? 0 : \
				 5400000 / (val))

/* Temperature is reported in .001 degC increments */
#घोषणा TEMP_TO_REG(val)	\
		DIV_ROUND_CLOSEST(clamp_val((val), -127000, 127000), 1000)
#घोषणा TEMPEXT_FROM_REG(val, ext)	\
		SCALE(((val) << 4) + (ext), 16, 1000)
#घोषणा TEMP_FROM_REG(val)	((val) * 1000)

#घोषणा PWM_TO_REG(val)			clamp_val(val, 0, 255)
#घोषणा PWM_FROM_REG(val)		(val)

/*
 * ZONEs have the following parameters:
 *    Limit (low) temp,           1. degC
 *    Hysteresis (below limit),   1. degC (0-15)
 *    Range of speed control,     .1 degC (2-80)
 *    Critical (high) temp,       1. degC
 *
 * FAN PWMs have the following parameters:
 *    Reference Zone,                 1, 2, 3, etc.
 *    Spinup समय,                    .05 sec
 *    PWM value at limit/low temp,    1 count
 *    PWM Frequency,                  1. Hz
 *    PWM is Min or OFF below limit,  flag
 *    Invert PWM output,              flag
 *
 * Some chips filter the temp, others the fan.
 *    Filter स्थिरant (or disabled)   .1 seconds
 */

/* These are the zone temperature range encodings in .001 degree C */
अटल स्थिर पूर्णांक lm85_range_map[] = अणु
	2000, 2500, 3300, 4000, 5000, 6600, 8000, 10000,
	13300, 16000, 20000, 26600, 32000, 40000, 53300, 80000
पूर्ण;

अटल पूर्णांक RANGE_TO_REG(दीर्घ range)
अणु
	वापस find_बंदst(range, lm85_range_map, ARRAY_SIZE(lm85_range_map));
पूर्ण
#घोषणा RANGE_FROM_REG(val)	lm85_range_map[(val) & 0x0f]

/* These are the PWM frequency encodings */
अटल स्थिर पूर्णांक lm85_freq_map[] = अणु /* 1 Hz */
	10, 15, 23, 30, 38, 47, 61, 94
पूर्ण;

अटल स्थिर पूर्णांक lm96000_freq_map[] = अणु /* 1 Hz */
	10, 15, 23, 30, 38, 47, 61, 94,
	22500, 24000, 25700, 25700, 27700, 27700, 30000, 30000
पूर्ण;

अटल स्थिर पूर्णांक adm1027_freq_map[] = अणु /* 1 Hz */
	11, 15, 22, 29, 35, 44, 59, 88
पूर्ण;

अटल पूर्णांक FREQ_TO_REG(स्थिर पूर्णांक *map,
		       अचिन्हित पूर्णांक map_size, अचिन्हित दीर्घ freq)
अणु
	वापस find_बंदst(freq, map, map_size);
पूर्ण

अटल पूर्णांक FREQ_FROM_REG(स्थिर पूर्णांक *map, अचिन्हित पूर्णांक map_size, u8 reg)
अणु
	वापस map[reg % map_size];
पूर्ण

/*
 * Since we can't use strings, I'm abusing these numbers
 *   to stand in क्रम the following meanings:
 *      1 -- PWM responds to Zone 1
 *      2 -- PWM responds to Zone 2
 *      3 -- PWM responds to Zone 3
 *     23 -- PWM responds to the higher temp of Zone 2 or 3
 *    123 -- PWM responds to highest of Zone 1, 2, or 3
 *      0 -- PWM is always at 0% (ie, off)
 *     -1 -- PWM is always at 100%
 *     -2 -- PWM responds to manual control
 */

अटल स्थिर पूर्णांक lm85_zone_map[] = अणु 1, 2, 3, -1, 0, 23, 123, -2 पूर्ण;
#घोषणा ZONE_FROM_REG(val)	lm85_zone_map[(val) >> 5]

अटल पूर्णांक ZONE_TO_REG(पूर्णांक zone)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= 7; ++i)
		अगर (zone == lm85_zone_map[i])
			अवरोध;
	अगर (i > 7)   /* Not found. */
		i = 3;  /* Always 100% */
	वापस i << 5;
पूर्ण

#घोषणा HYST_TO_REG(val)	clamp_val(((val) + 500) / 1000, 0, 15)
#घोषणा HYST_FROM_REG(val)	((val) * 1000)

/*
 * Chip sampling rates
 *
 * Some sensors are not updated more frequently than once per second
 *    so it करोesn't make sense to पढ़ो them more often than that.
 *    We cache the results and वापस the saved data अगर the driver
 *    is called again beक्रमe a second has elapsed.
 *
 * Also, there is signअगरicant configuration data क्रम this chip
 *    given the स्वतःmatic PWM fan control that is possible.  There
 *    are about 47 bytes of config data to only 22 bytes of actual
 *    पढ़ोings.  So, we keep the config data up to date in the cache
 *    when it is written and only sample it once every 1 *minute*
 */
#घोषणा LM85_DATA_INTERVAL  (HZ + HZ / 2)
#घोषणा LM85_CONFIG_INTERVAL  (1 * 60 * HZ)

/*
 * LM85 can स्वतःmatically adjust fan speeds based on temperature
 * This काष्ठाure encapsulates an entire Zone config.  There are
 * three zones (one क्रम each temperature input) on the lm85
 */
काष्ठा lm85_zone अणु
	s8 limit;	/* Low temp limit */
	u8 hyst;	/* Low limit hysteresis. (0-15) */
	u8 range;	/* Temp range, encoded */
	s8 critical;	/* "All fans ON" temp limit */
	u8 max_desired; /*
			 * Actual "max" temperature specअगरied.  Preserved
			 * to prevent "drift" as other स्वतःfan control
			 * values change.
			 */
पूर्ण;

काष्ठा lm85_स्वतःfan अणु
	u8 config;	/* Register value */
	u8 min_pwm;	/* Minimum PWM value, encoded */
	u8 min_off;	/* Min PWM or OFF below "limit", flag */
पूर्ण;

/*
 * For each रेजिस्टरed chip, we need to keep some data in memory.
 * The काष्ठाure is dynamically allocated.
 */
काष्ठा lm85_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा attribute_group *groups[6];
	स्थिर पूर्णांक *freq_map;
	अचिन्हित पूर्णांक freq_map_size;

	क्रमागत chips type;

	bool has_vid5;	/* true अगर VID5 is configured क्रम ADT7463 or ADT7468 */

	काष्ठा mutex update_lock;
	पूर्णांक valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_पढ़ोing;	/* In jअगरfies */
	अचिन्हित दीर्घ last_config;	/* In jअगरfies */

	u8 in[8];		/* Register value */
	u8 in_max[8];		/* Register value */
	u8 in_min[8];		/* Register value */
	s8 temp[3];		/* Register value */
	s8 temp_min[3];		/* Register value */
	s8 temp_max[3];		/* Register value */
	u16 fan[4];		/* Register value */
	u16 fan_min[4];		/* Register value */
	u8 pwm[3];		/* Register value */
	u8 pwm_freq[3];		/* Register encoding */
	u8 temp_ext[3];		/* Decoded values */
	u8 in_ext[8];		/* Decoded values */
	u8 vid;			/* Register value */
	u8 vrm;			/* VRM version */
	u32 alarms;		/* Register encoding, combined */
	u8 cfg5;		/* Config Register 5 on ADT7468 */
	काष्ठा lm85_स्वतःfan स्वतःfan[3];
	काष्ठा lm85_zone zone[3];
पूर्ण;

अटल पूर्णांक lm85_पढ़ो_value(काष्ठा i2c_client *client, u8 reg)
अणु
	पूर्णांक res;

	/* What size location is it? */
	चयन (reg) अणु
	हाल LM85_REG_FAN(0):  /* Read WORD data */
	हाल LM85_REG_FAN(1):
	हाल LM85_REG_FAN(2):
	हाल LM85_REG_FAN(3):
	हाल LM85_REG_FAN_MIN(0):
	हाल LM85_REG_FAN_MIN(1):
	हाल LM85_REG_FAN_MIN(2):
	हाल LM85_REG_FAN_MIN(3):
	हाल LM85_REG_ALARM1:	/* Read both bytes at once */
		res = i2c_smbus_पढ़ो_byte_data(client, reg) & 0xff;
		res |= i2c_smbus_पढ़ो_byte_data(client, reg + 1) << 8;
		अवरोध;
	शेष:	/* Read BYTE data */
		res = i2c_smbus_पढ़ो_byte_data(client, reg);
		अवरोध;
	पूर्ण

	वापस res;
पूर्ण

अटल व्योम lm85_ग_लिखो_value(काष्ठा i2c_client *client, u8 reg, पूर्णांक value)
अणु
	चयन (reg) अणु
	हाल LM85_REG_FAN(0):  /* Write WORD data */
	हाल LM85_REG_FAN(1):
	हाल LM85_REG_FAN(2):
	हाल LM85_REG_FAN(3):
	हाल LM85_REG_FAN_MIN(0):
	हाल LM85_REG_FAN_MIN(1):
	हाल LM85_REG_FAN_MIN(2):
	हाल LM85_REG_FAN_MIN(3):
	/* NOTE: ALARM is पढ़ो only, so not included here */
		i2c_smbus_ग_लिखो_byte_data(client, reg, value & 0xff);
		i2c_smbus_ग_लिखो_byte_data(client, reg + 1, value >> 8);
		अवरोध;
	शेष:	/* Write BYTE data */
		i2c_smbus_ग_लिखो_byte_data(client, reg, value);
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा lm85_data *lm85_update_device(काष्ठा device *dev)
अणु
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (!data->valid ||
	     समय_after(jअगरfies, data->last_पढ़ोing + LM85_DATA_INTERVAL)) अणु
		/* Things that change quickly */
		dev_dbg(&client->dev, "Reading sensor values\n");

		/*
		 * Have to पढ़ो extended bits first to "freeze" the
		 * more signअगरicant bits that are पढ़ो later.
		 * There are 2 additional resolution bits per channel and we
		 * have room क्रम 4, so we shअगरt them to the left.
		 */
		अगर (data->type == adm1027 || data->type == adt7463 ||
		    data->type == adt7468) अणु
			पूर्णांक ext1 = lm85_पढ़ो_value(client,
						   ADM1027_REG_EXTEND_ADC1);
			पूर्णांक ext2 =  lm85_पढ़ो_value(client,
						    ADM1027_REG_EXTEND_ADC2);
			पूर्णांक val = (ext1 << 8) + ext2;

			क्रम (i = 0; i <= 4; i++)
				data->in_ext[i] =
					((val >> (i * 2)) & 0x03) << 2;

			क्रम (i = 0; i <= 2; i++)
				data->temp_ext[i] =
					(val >> ((i + 4) * 2)) & 0x0c;
		पूर्ण

		data->vid = lm85_पढ़ो_value(client, LM85_REG_VID);

		क्रम (i = 0; i <= 3; ++i) अणु
			data->in[i] =
			    lm85_पढ़ो_value(client, LM85_REG_IN(i));
			data->fan[i] =
			    lm85_पढ़ो_value(client, LM85_REG_FAN(i));
		पूर्ण

		अगर (!data->has_vid5)
			data->in[4] = lm85_पढ़ो_value(client, LM85_REG_IN(4));

		अगर (data->type == adt7468)
			data->cfg5 = lm85_पढ़ो_value(client, ADT7468_REG_CFG5);

		क्रम (i = 0; i <= 2; ++i) अणु
			data->temp[i] =
			    lm85_पढ़ो_value(client, LM85_REG_TEMP(i));
			data->pwm[i] =
			    lm85_पढ़ो_value(client, LM85_REG_PWM(i));

			अगर (IS_ADT7468_OFF64(data))
				data->temp[i] -= 64;
		पूर्ण

		data->alarms = lm85_पढ़ो_value(client, LM85_REG_ALARM1);

		अगर (data->type == emc6d100) अणु
			/* Three more voltage sensors */
			क्रम (i = 5; i <= 7; ++i) अणु
				data->in[i] = lm85_पढ़ो_value(client,
							EMC6D100_REG_IN(i));
			पूर्ण
			/* More alarm bits */
			data->alarms |= lm85_पढ़ो_value(client,
						EMC6D100_REG_ALARM3) << 16;
		पूर्ण अन्यथा अगर (data->type == emc6d102 || data->type == emc6d103 ||
			   data->type == emc6d103s) अणु
			/*
			 * Have to पढ़ो LSB bits after the MSB ones because
			 * the पढ़ोing of the MSB bits has frozen the
			 * LSBs (backward from the ADM1027).
			 */
			पूर्णांक ext1 = lm85_पढ़ो_value(client,
						   EMC6D102_REG_EXTEND_ADC1);
			पूर्णांक ext2 = lm85_पढ़ो_value(client,
						   EMC6D102_REG_EXTEND_ADC2);
			पूर्णांक ext3 = lm85_पढ़ो_value(client,
						   EMC6D102_REG_EXTEND_ADC3);
			पूर्णांक ext4 = lm85_पढ़ो_value(client,
						   EMC6D102_REG_EXTEND_ADC4);
			data->in_ext[0] = ext3 & 0x0f;
			data->in_ext[1] = ext4 & 0x0f;
			data->in_ext[2] = ext4 >> 4;
			data->in_ext[3] = ext3 >> 4;
			data->in_ext[4] = ext2 >> 4;

			data->temp_ext[0] = ext1 & 0x0f;
			data->temp_ext[1] = ext2 & 0x0f;
			data->temp_ext[2] = ext1 >> 4;
		पूर्ण

		data->last_पढ़ोing = jअगरfies;
	पूर्ण  /* last_पढ़ोing */

	अगर (!data->valid ||
	     समय_after(jअगरfies, data->last_config + LM85_CONFIG_INTERVAL)) अणु
		/* Things that करोn't change often */
		dev_dbg(&client->dev, "Reading config values\n");

		क्रम (i = 0; i <= 3; ++i) अणु
			data->in_min[i] =
			    lm85_पढ़ो_value(client, LM85_REG_IN_MIN(i));
			data->in_max[i] =
			    lm85_पढ़ो_value(client, LM85_REG_IN_MAX(i));
			data->fan_min[i] =
			    lm85_पढ़ो_value(client, LM85_REG_FAN_MIN(i));
		पूर्ण

		अगर (!data->has_vid5)  अणु
			data->in_min[4] = lm85_पढ़ो_value(client,
					  LM85_REG_IN_MIN(4));
			data->in_max[4] = lm85_पढ़ो_value(client,
					  LM85_REG_IN_MAX(4));
		पूर्ण

		अगर (data->type == emc6d100) अणु
			क्रम (i = 5; i <= 7; ++i) अणु
				data->in_min[i] = lm85_पढ़ो_value(client,
						EMC6D100_REG_IN_MIN(i));
				data->in_max[i] = lm85_पढ़ो_value(client,
						EMC6D100_REG_IN_MAX(i));
			पूर्ण
		पूर्ण

		क्रम (i = 0; i <= 2; ++i) अणु
			पूर्णांक val;

			data->temp_min[i] =
			    lm85_पढ़ो_value(client, LM85_REG_TEMP_MIN(i));
			data->temp_max[i] =
			    lm85_पढ़ो_value(client, LM85_REG_TEMP_MAX(i));

			data->स्वतःfan[i].config =
			    lm85_पढ़ो_value(client, LM85_REG_AFAN_CONFIG(i));
			val = lm85_पढ़ो_value(client, LM85_REG_AFAN_RANGE(i));
			data->pwm_freq[i] = val % data->freq_map_size;
			data->zone[i].range = val >> 4;
			data->स्वतःfan[i].min_pwm =
			    lm85_पढ़ो_value(client, LM85_REG_AFAN_MINPWM(i));
			data->zone[i].limit =
			    lm85_पढ़ो_value(client, LM85_REG_AFAN_LIMIT(i));
			data->zone[i].critical =
			    lm85_पढ़ो_value(client, LM85_REG_AFAN_CRITICAL(i));

			अगर (IS_ADT7468_OFF64(data)) अणु
				data->temp_min[i] -= 64;
				data->temp_max[i] -= 64;
				data->zone[i].limit -= 64;
				data->zone[i].critical -= 64;
			पूर्ण
		पूर्ण

		अगर (data->type != emc6d103s) अणु
			i = lm85_पढ़ो_value(client, LM85_REG_AFAN_SPIKE1);
			data->स्वतःfan[0].min_off = (i & 0x20) != 0;
			data->स्वतःfan[1].min_off = (i & 0x40) != 0;
			data->स्वतःfan[2].min_off = (i & 0x80) != 0;

			i = lm85_पढ़ो_value(client, LM85_REG_AFAN_HYST1);
			data->zone[0].hyst = i >> 4;
			data->zone[1].hyst = i & 0x0f;

			i = lm85_पढ़ो_value(client, LM85_REG_AFAN_HYST2);
			data->zone[2].hyst = i >> 4;
		पूर्ण

		data->last_config = jअगरfies;
	पूर्ण  /* last_config */

	data->valid = 1;

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/* 4 Fans */
अटल sमाप_प्रकार fan_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan[nr]));
पूर्ण

अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan_min[nr]));
पूर्ण

अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan_min[nr] = FAN_TO_REG(val);
	lm85_ग_लिखो_value(client, LM85_REG_FAN_MIN(nr), data->fan_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan1_min, fan_min, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan2_min, fan_min, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan3_input, fan, 2);
अटल SENSOR_DEVICE_ATTR_RW(fan3_min, fan_min, 2);
अटल SENSOR_DEVICE_ATTR_RO(fan4_input, fan, 3);
अटल SENSOR_DEVICE_ATTR_RW(fan4_min, fan_min, 3);

/* vid, vrm, alarms */

अटल sमाप_प्रकार cpu0_vid_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm85_data *data = lm85_update_device(dev);
	पूर्णांक vid;

	अगर (data->has_vid5) अणु
		/* 6-pin VID (VRM 10) */
		vid = vid_from_reg(data->vid & 0x3f, data->vrm);
	पूर्ण अन्यथा अणु
		/* 5-pin VID (VRM 9) */
		vid = vid_from_reg(data->vid & 0x1f, data->vrm);
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", vid);
पूर्ण

अटल DEVICE_ATTR_RO(cpu0_vid);

अटल sमाप_प्रकार vrm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%ld\n", (दीर्घ) data->vrm);
पूर्ण

अटल sमाप_प्रकार vrm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
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

अटल DEVICE_ATTR_RW(vrm);

अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", data->alarms);
पूर्ण

अटल DEVICE_ATTR_RO(alarms);

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> nr) & 1);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in0_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_alarm, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_alarm, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_alarm, alarm, 8);
अटल SENSOR_DEVICE_ATTR_RO(in5_alarm, alarm, 18);
अटल SENSOR_DEVICE_ATTR_RO(in6_alarm, alarm, 16);
अटल SENSOR_DEVICE_ATTR_RO(in7_alarm, alarm, 17);
अटल SENSOR_DEVICE_ATTR_RO(temp1_alarm, alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp1_fault, alarm, 14);
अटल SENSOR_DEVICE_ATTR_RO(temp2_alarm, alarm, 5);
अटल SENSOR_DEVICE_ATTR_RO(temp3_alarm, alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(temp3_fault, alarm, 15);
अटल SENSOR_DEVICE_ATTR_RO(fan1_alarm, alarm, 10);
अटल SENSOR_DEVICE_ATTR_RO(fan2_alarm, alarm, 11);
अटल SENSOR_DEVICE_ATTR_RO(fan3_alarm, alarm, 12);
अटल SENSOR_DEVICE_ATTR_RO(fan4_alarm, alarm, 13);

/* pwm */

अटल sमाप_प्रकार pwm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", PWM_FROM_REG(data->pwm[nr]));
पूर्ण

अटल sमाप_प्रकार pwm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->pwm[nr] = PWM_TO_REG(val);
	lm85_ग_लिखो_value(client, LM85_REG_PWM(nr), data->pwm[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_enable_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	पूर्णांक pwm_zone, enable;

	pwm_zone = ZONE_FROM_REG(data->स्वतःfan[nr].config);
	चयन (pwm_zone) अणु
	हाल -1:	/* PWM is always at 100% */
		enable = 0;
		अवरोध;
	हाल 0:		/* PWM is always at 0% */
	हाल -2:	/* PWM responds to manual control */
		enable = 1;
		अवरोध;
	शेष:	/* PWM in स्वतःmatic mode */
		enable = 2;
	पूर्ण
	वापस प्र_लिखो(buf, "%d\n", enable);
पूर्ण

अटल sमाप_प्रकार pwm_enable_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 config;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	चयन (val) अणु
	हाल 0:
		config = 3;
		अवरोध;
	हाल 1:
		config = 7;
		अवरोध;
	हाल 2:
		/*
		 * Here we have to choose arbitrarily one of the 5 possible
		 * configurations; I go क्रम the safest
		 */
		config = 6;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&data->update_lock);
	data->स्वतःfan[nr].config = lm85_पढ़ो_value(client,
		LM85_REG_AFAN_CONFIG(nr));
	data->स्वतःfan[nr].config = (data->स्वतःfan[nr].config & ~0xe0)
		| (config << 5);
	lm85_ग_लिखो_value(client, LM85_REG_AFAN_CONFIG(nr),
		data->स्वतःfan[nr].config);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_freq_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	पूर्णांक freq;

	अगर (IS_ADT7468_HFPWM(data))
		freq = 22500;
	अन्यथा
		freq = FREQ_FROM_REG(data->freq_map, data->freq_map_size,
				     data->pwm_freq[nr]);

	वापस प्र_लिखो(buf, "%d\n", freq);
पूर्ण

अटल sमाप_प्रकार pwm_freq_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	/*
	 * The ADT7468 has a special high-frequency PWM output mode,
	 * where all PWM outमाला_दो are driven by a 22.5 kHz घड़ी.
	 * This might confuse the user, but there's not much we can करो.
	 */
	अगर (data->type == adt7468 && val >= 11300) अणु	/* High freq. mode */
		data->cfg5 &= ~ADT7468_HFPWM;
		lm85_ग_लिखो_value(client, ADT7468_REG_CFG5, data->cfg5);
	पूर्ण अन्यथा अणु					/* Low freq. mode */
		data->pwm_freq[nr] = FREQ_TO_REG(data->freq_map,
						 data->freq_map_size, val);
		lm85_ग_लिखो_value(client, LM85_REG_AFAN_RANGE(nr),
				 (data->zone[nr].range << 4)
				 | data->pwm_freq[nr]);
		अगर (data->type == adt7468) अणु
			data->cfg5 |= ADT7468_HFPWM;
			lm85_ग_लिखो_value(client, ADT7468_REG_CFG5, data->cfg5);
		पूर्ण
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(pwm1, pwm, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm1_enable, pwm_enable, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm1_freq, pwm_freq, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2, pwm, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_enable, pwm_enable, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_freq, pwm_freq, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3, pwm, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_enable, pwm_enable, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_freq, pwm_freq, 2);

/* Voltages */

अटल sमाप_प्रकार in_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", INSEXT_FROM_REG(nr, data->in[nr],
						    data->in_ext[nr]));
पूर्ण

अटल sमाप_प्रकार in_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", INS_FROM_REG(nr, data->in_min[nr]));
पूर्ण

अटल sमाप_प्रकार in_min_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_min[nr] = INS_TO_REG(nr, val);
	lm85_ग_लिखो_value(client, LM85_REG_IN_MIN(nr), data->in_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार in_max_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", INS_FROM_REG(nr, data->in_max[nr]));
पूर्ण

अटल sमाप_प्रकार in_max_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_max[nr] = INS_TO_REG(nr, val);
	lm85_ग_लिखो_value(client, LM85_REG_IN_MAX(nr), data->in_max[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in0_input, in, 0);
अटल SENSOR_DEVICE_ATTR_RW(in0_min, in_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(in0_max, in_max, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_input, in, 1);
अटल SENSOR_DEVICE_ATTR_RW(in1_min, in_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(in1_max, in_max, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, in, 2);
अटल SENSOR_DEVICE_ATTR_RW(in2_min, in_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(in2_max, in_max, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, in, 3);
अटल SENSOR_DEVICE_ATTR_RW(in3_min, in_min, 3);
अटल SENSOR_DEVICE_ATTR_RW(in3_max, in_max, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, in, 4);
अटल SENSOR_DEVICE_ATTR_RW(in4_min, in_min, 4);
अटल SENSOR_DEVICE_ATTR_RW(in4_max, in_max, 4);
अटल SENSOR_DEVICE_ATTR_RO(in5_input, in, 5);
अटल SENSOR_DEVICE_ATTR_RW(in5_min, in_min, 5);
अटल SENSOR_DEVICE_ATTR_RW(in5_max, in_max, 5);
अटल SENSOR_DEVICE_ATTR_RO(in6_input, in, 6);
अटल SENSOR_DEVICE_ATTR_RW(in6_min, in_min, 6);
अटल SENSOR_DEVICE_ATTR_RW(in6_max, in_max, 6);
अटल SENSOR_DEVICE_ATTR_RO(in7_input, in, 7);
अटल SENSOR_DEVICE_ATTR_RW(in7_min, in_min, 7);
अटल SENSOR_DEVICE_ATTR_RW(in7_max, in_max, 7);

/* Temps */

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMPEXT_FROM_REG(data->temp[nr],
						     data->temp_ext[nr]));
पूर्ण

अटल sमाप_प्रकार temp_min_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_min[nr]));
पूर्ण

अटल sमाप_प्रकार temp_min_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (IS_ADT7468_OFF64(data))
		val += 64;

	mutex_lock(&data->update_lock);
	data->temp_min[nr] = TEMP_TO_REG(val);
	lm85_ग_लिखो_value(client, LM85_REG_TEMP_MIN(nr), data->temp_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_max[nr]));
पूर्ण

अटल sमाप_प्रकार temp_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (IS_ADT7468_OFF64(data))
		val += 64;

	mutex_lock(&data->update_lock);
	data->temp_max[nr] = TEMP_TO_REG(val);
	lm85_ग_लिखो_value(client, LM85_REG_TEMP_MAX(nr), data->temp_max[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp_max, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_min, temp_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp_max, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_min, temp_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max, temp_max, 2);

/* Automatic PWM control */

अटल sमाप_प्रकार pwm_स्वतः_channels_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", ZONE_FROM_REG(data->स्वतःfan[nr].config));
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_channels_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->स्वतःfan[nr].config = (data->स्वतःfan[nr].config & (~0xe0))
		| ZONE_TO_REG(val);
	lm85_ग_लिखो_value(client, LM85_REG_AFAN_CONFIG(nr),
		data->स्वतःfan[nr].config);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_pwm_min_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", PWM_FROM_REG(data->स्वतःfan[nr].min_pwm));
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_pwm_min_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->स्वतःfan[nr].min_pwm = PWM_TO_REG(val);
	lm85_ग_लिखो_value(client, LM85_REG_AFAN_MINPWM(nr),
		data->स्वतःfan[nr].min_pwm);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_pwm_minctl_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->स्वतःfan[nr].min_off);
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_pwm_minctl_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 पंचांगp;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->स्वतःfan[nr].min_off = val;
	पंचांगp = lm85_पढ़ो_value(client, LM85_REG_AFAN_SPIKE1);
	पंचांगp &= ~(0x20 << nr);
	अगर (data->स्वतःfan[nr].min_off)
		पंचांगp |= 0x20 << nr;
	lm85_ग_लिखो_value(client, LM85_REG_AFAN_SPIKE1, पंचांगp);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_channels, pwm_स्वतः_channels, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_pwm_min, pwm_स्वतः_pwm_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_pwm_minctl, pwm_स्वतः_pwm_minctl, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_स्वतः_channels, pwm_स्वतः_channels, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_स्वतः_pwm_min, pwm_स्वतः_pwm_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_स्वतः_pwm_minctl, pwm_स्वतः_pwm_minctl, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_स्वतः_channels, pwm_स्वतः_channels, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_स्वतः_pwm_min, pwm_स्वतः_pwm_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_स्वतः_pwm_minctl, pwm_स्वतः_pwm_minctl, 2);

/* Temperature settings क्रम स्वतःmatic PWM control */

अटल sमाप_प्रकार temp_स्वतः_temp_off_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->zone[nr].limit) -
		HYST_FROM_REG(data->zone[nr].hyst));
पूर्ण

अटल sमाप_प्रकार temp_स्वतः_temp_off_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक min;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	min = TEMP_FROM_REG(data->zone[nr].limit);
	data->zone[nr].hyst = HYST_TO_REG(min - val);
	अगर (nr == 0 || nr == 1) अणु
		lm85_ग_लिखो_value(client, LM85_REG_AFAN_HYST1,
			(data->zone[0].hyst << 4)
			| data->zone[1].hyst);
	पूर्ण अन्यथा अणु
		lm85_ग_लिखो_value(client, LM85_REG_AFAN_HYST2,
			(data->zone[2].hyst << 4));
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_स्वतः_temp_min_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->zone[nr].limit));
पूर्ण

अटल sमाप_प्रकार temp_स्वतः_temp_min_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->zone[nr].limit = TEMP_TO_REG(val);
	lm85_ग_लिखो_value(client, LM85_REG_AFAN_LIMIT(nr),
		data->zone[nr].limit);

/* Update temp_स्वतः_max and temp_स्वतः_range */
	data->zone[nr].range = RANGE_TO_REG(
		TEMP_FROM_REG(data->zone[nr].max_desired) -
		TEMP_FROM_REG(data->zone[nr].limit));
	lm85_ग_लिखो_value(client, LM85_REG_AFAN_RANGE(nr),
		((data->zone[nr].range & 0x0f) << 4)
		| data->pwm_freq[nr]);

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_स्वतः_temp_max_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->zone[nr].limit) +
		RANGE_FROM_REG(data->zone[nr].range));
पूर्ण

अटल sमाप_प्रकार temp_स्वतः_temp_max_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक min;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	min = TEMP_FROM_REG(data->zone[nr].limit);
	data->zone[nr].max_desired = TEMP_TO_REG(val);
	data->zone[nr].range = RANGE_TO_REG(
		val - min);
	lm85_ग_लिखो_value(client, LM85_REG_AFAN_RANGE(nr),
		((data->zone[nr].range & 0x0f) << 4)
		| data->pwm_freq[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_स्वतः_temp_crit_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = lm85_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->zone[nr].critical));
पूर्ण

अटल sमाप_प्रकार temp_स्वतः_temp_crit_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा lm85_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->zone[nr].critical = TEMP_TO_REG(val);
	lm85_ग_लिखो_value(client, LM85_REG_AFAN_CRITICAL(nr),
		data->zone[nr].critical);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(temp1_स्वतः_temp_off, temp_स्वतः_temp_off, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_स्वतः_temp_min, temp_स्वतः_temp_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_स्वतः_temp_max, temp_स्वतः_temp_max, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_स्वतः_temp_crit, temp_स्वतः_temp_crit, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_स्वतः_temp_off, temp_स्वतः_temp_off, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_स्वतः_temp_min, temp_स्वतः_temp_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_स्वतः_temp_max, temp_स्वतः_temp_max, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_स्वतः_temp_crit, temp_स्वतः_temp_crit, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_स्वतः_temp_off, temp_स्वतः_temp_off, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_स्वतः_temp_min, temp_स्वतः_temp_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_स्वतः_temp_max, temp_स्वतः_temp_max, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_स्वतः_temp_crit, temp_स्वतः_temp_crit, 2);

अटल काष्ठा attribute *lm85_attributes[] = अणु
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan4_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan3_min.dev_attr.attr,
	&sensor_dev_attr_fan4_min.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_fan3_alarm.dev_attr.attr,
	&sensor_dev_attr_fan4_alarm.dev_attr.attr,

	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&sensor_dev_attr_pwm3.dev_attr.attr,
	&sensor_dev_attr_pwm1_enable.dev_attr.attr,
	&sensor_dev_attr_pwm2_enable.dev_attr.attr,
	&sensor_dev_attr_pwm3_enable.dev_attr.attr,
	&sensor_dev_attr_pwm1_freq.dev_attr.attr,
	&sensor_dev_attr_pwm2_freq.dev_attr.attr,
	&sensor_dev_attr_pwm3_freq.dev_attr.attr,

	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,

	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_fault.dev_attr.attr,
	&sensor_dev_attr_temp3_fault.dev_attr.attr,

	&sensor_dev_attr_pwm1_स्वतः_channels.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_channels.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_channels.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_pwm_min.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_pwm_min.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_pwm_min.dev_attr.attr,

	&sensor_dev_attr_temp1_स्वतः_temp_min.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_temp_min.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_temp_min.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_temp_max.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_temp_max.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_temp_max.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_temp_crit.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_temp_crit.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_temp_crit.dev_attr.attr,

	&dev_attr_vrm.attr,
	&dev_attr_cpu0_vid.attr,
	&dev_attr_alarms.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm85_group = अणु
	.attrs = lm85_attributes,
पूर्ण;

अटल काष्ठा attribute *lm85_attributes_minctl[] = अणु
	&sensor_dev_attr_pwm1_स्वतः_pwm_minctl.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_pwm_minctl.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_pwm_minctl.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm85_group_minctl = अणु
	.attrs = lm85_attributes_minctl,
पूर्ण;

अटल काष्ठा attribute *lm85_attributes_temp_off[] = अणु
	&sensor_dev_attr_temp1_स्वतः_temp_off.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_temp_off.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_temp_off.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm85_group_temp_off = अणु
	.attrs = lm85_attributes_temp_off,
पूर्ण;

अटल काष्ठा attribute *lm85_attributes_in4[] = अणु
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm85_group_in4 = अणु
	.attrs = lm85_attributes_in4,
पूर्ण;

अटल काष्ठा attribute *lm85_attributes_in567[] = अणु
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in7_input.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in6_min.dev_attr.attr,
	&sensor_dev_attr_in7_min.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,
	&sensor_dev_attr_in6_max.dev_attr.attr,
	&sensor_dev_attr_in7_max.dev_attr.attr,
	&sensor_dev_attr_in5_alarm.dev_attr.attr,
	&sensor_dev_attr_in6_alarm.dev_attr.attr,
	&sensor_dev_attr_in7_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm85_group_in567 = अणु
	.attrs = lm85_attributes_in567,
पूर्ण;

अटल व्योम lm85_init_client(काष्ठा i2c_client *client)
अणु
	पूर्णांक value;

	/* Start monitoring अगर needed */
	value = lm85_पढ़ो_value(client, LM85_REG_CONFIG);
	अगर (!(value & 0x01)) अणु
		dev_info(&client->dev, "Starting monitoring\n");
		lm85_ग_लिखो_value(client, LM85_REG_CONFIG, value | 0x01);
	पूर्ण

	/* Warn about unusual configuration bits */
	अगर (value & 0x02)
		dev_warn(&client->dev, "Device configuration is locked\n");
	अगर (!(value & 0x04))
		dev_warn(&client->dev, "Device is not ready\n");
पूर्ण

अटल पूर्णांक lm85_is_fake(काष्ठा i2c_client *client)
अणु
	/*
	 * Dअगरferenciate between real LM96000 and Winbond WPCD377I. The latter
	 * emulate the क्रमmer except that it has no hardware monitoring function
	 * so the पढ़ोings are always 0.
	 */
	पूर्णांक i;
	u8 in_temp, fan;

	क्रम (i = 0; i < 8; i++) अणु
		in_temp = i2c_smbus_पढ़ो_byte_data(client, 0x20 + i);
		fan = i2c_smbus_पढ़ो_byte_data(client, 0x28 + i);
		अगर (in_temp != 0x00 || fan != 0xff)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक lm85_detect(काष्ठा i2c_client *client, काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक address = client->addr;
	स्थिर अक्षर *type_name = शून्य;
	पूर्णांक company, verstep;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		/* We need to be able to करो byte I/O */
		वापस -ENODEV;
	पूर्ण

	/* Determine the chip type */
	company = lm85_पढ़ो_value(client, LM85_REG_COMPANY);
	verstep = lm85_पढ़ो_value(client, LM85_REG_VERSTEP);

	dev_dbg(&adapter->dev,
		"Detecting device at 0x%02x with COMPANY: 0x%02x and VERSTEP: 0x%02x\n",
		address, company, verstep);

	अगर (company == LM85_COMPANY_NATIONAL) अणु
		चयन (verstep) अणु
		हाल LM85_VERSTEP_LM85C:
			type_name = "lm85c";
			अवरोध;
		हाल LM85_VERSTEP_LM85B:
			type_name = "lm85b";
			अवरोध;
		हाल LM85_VERSTEP_LM96000_1:
		हाल LM85_VERSTEP_LM96000_2:
			/* Check क्रम Winbond WPCD377I */
			अगर (lm85_is_fake(client)) अणु
				dev_dbg(&adapter->dev,
					"Found Winbond WPCD377I, ignoring\n");
				वापस -ENODEV;
			पूर्ण
			type_name = "lm96000";
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (company == LM85_COMPANY_ANALOG_DEV) अणु
		चयन (verstep) अणु
		हाल LM85_VERSTEP_ADM1027:
			type_name = "adm1027";
			अवरोध;
		हाल LM85_VERSTEP_ADT7463:
		हाल LM85_VERSTEP_ADT7463C:
			type_name = "adt7463";
			अवरोध;
		हाल LM85_VERSTEP_ADT7468_1:
		हाल LM85_VERSTEP_ADT7468_2:
			type_name = "adt7468";
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (company == LM85_COMPANY_SMSC) अणु
		चयन (verstep) अणु
		हाल LM85_VERSTEP_EMC6D100_A0:
		हाल LM85_VERSTEP_EMC6D100_A1:
			/* Note: we can't tell a '100 from a '101 */
			type_name = "emc6d100";
			अवरोध;
		हाल LM85_VERSTEP_EMC6D102:
			type_name = "emc6d102";
			अवरोध;
		हाल LM85_VERSTEP_EMC6D103_A0:
		हाल LM85_VERSTEP_EMC6D103_A1:
			type_name = "emc6d103";
			अवरोध;
		हाल LM85_VERSTEP_EMC6D103S:
			type_name = "emc6d103s";
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!type_name)
		वापस -ENODEV;

	strlcpy(info->type, type_name, I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm85_id[];

अटल पूर्णांक lm85_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा lm85_data *data;
	पूर्णांक idx = 0;

	data = devm_kzalloc(dev, माप(काष्ठा lm85_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	अगर (client->dev.of_node)
		data->type = (क्रमागत chips)of_device_get_match_data(&client->dev);
	अन्यथा
		data->type = i2c_match_id(lm85_id, client)->driver_data;
	mutex_init(&data->update_lock);

	/* Fill in the chip specअगरic driver values */
	चयन (data->type) अणु
	हाल adm1027:
	हाल adt7463:
	हाल adt7468:
	हाल emc6d100:
	हाल emc6d102:
	हाल emc6d103:
	हाल emc6d103s:
		data->freq_map = adm1027_freq_map;
		data->freq_map_size = ARRAY_SIZE(adm1027_freq_map);
		अवरोध;
	हाल lm96000:
		data->freq_map = lm96000_freq_map;
		data->freq_map_size = ARRAY_SIZE(lm96000_freq_map);
		अवरोध;
	शेष:
		data->freq_map = lm85_freq_map;
		data->freq_map_size = ARRAY_SIZE(lm85_freq_map);
	पूर्ण

	/* Set the VRM version */
	data->vrm = vid_which_vrm();

	/* Initialize the LM85 chip */
	lm85_init_client(client);

	/* sysfs hooks */
	data->groups[idx++] = &lm85_group;

	/* minctl and temp_off exist on all chips except emc6d103s */
	अगर (data->type != emc6d103s) अणु
		data->groups[idx++] = &lm85_group_minctl;
		data->groups[idx++] = &lm85_group_temp_off;
	पूर्ण

	/*
	 * The ADT7463/68 have an optional VRM 10 mode where pin 21 is used
	 * as a sixth digital VID input rather than an analog input.
	 */
	अगर (data->type == adt7463 || data->type == adt7468) अणु
		u8 vid = lm85_पढ़ो_value(client, LM85_REG_VID);
		अगर (vid & 0x80)
			data->has_vid5 = true;
	पूर्ण

	अगर (!data->has_vid5)
		data->groups[idx++] = &lm85_group_in4;

	/* The EMC6D100 has 3 additional voltage inमाला_दो */
	अगर (data->type == emc6d100)
		data->groups[idx++] = &lm85_group_in567;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, data->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm85_id[] = अणु
	अणु "adm1027", adm1027 पूर्ण,
	अणु "adt7463", adt7463 पूर्ण,
	अणु "adt7468", adt7468 पूर्ण,
	अणु "lm85", lm85 पूर्ण,
	अणु "lm85b", lm85 पूर्ण,
	अणु "lm85c", lm85 पूर्ण,
	अणु "lm96000", lm96000 पूर्ण,
	अणु "emc6d100", emc6d100 पूर्ण,
	अणु "emc6d101", emc6d100 पूर्ण,
	अणु "emc6d102", emc6d102 पूर्ण,
	अणु "emc6d103", emc6d103 पूर्ण,
	अणु "emc6d103s", emc6d103s पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm85_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused lm85_of_match[] = अणु
	अणु
		.compatible = "adi,adm1027",
		.data = (व्योम *)adm1027
	पूर्ण,
	अणु
		.compatible = "adi,adt7463",
		.data = (व्योम *)adt7463
	पूर्ण,
	अणु
		.compatible = "adi,adt7468",
		.data = (व्योम *)adt7468
	पूर्ण,
	अणु
		.compatible = "national,lm85",
		.data = (व्योम *)lm85
	पूर्ण,
	अणु
		.compatible = "national,lm85b",
		.data = (व्योम *)lm85
	पूर्ण,
	अणु
		.compatible = "national,lm85c",
		.data = (व्योम *)lm85
	पूर्ण,
	अणु
		.compatible = "ti,lm96000",
		.data = (व्योम *)lm96000
	पूर्ण,
	अणु
		.compatible = "smsc,emc6d100",
		.data = (व्योम *)emc6d100
	पूर्ण,
	अणु
		.compatible = "smsc,emc6d101",
		.data = (व्योम *)emc6d100
	पूर्ण,
	अणु
		.compatible = "smsc,emc6d102",
		.data = (व्योम *)emc6d102
	पूर्ण,
	अणु
		.compatible = "smsc,emc6d103",
		.data = (व्योम *)emc6d103
	पूर्ण,
	अणु
		.compatible = "smsc,emc6d103s",
		.data = (व्योम *)emc6d103s
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lm85_of_match);

अटल काष्ठा i2c_driver lm85_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name   = "lm85",
		.of_match_table = of_match_ptr(lm85_of_match),
	पूर्ण,
	.probe_new	= lm85_probe,
	.id_table	= lm85_id,
	.detect		= lm85_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(lm85_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Philip Pokorny <ppokorny@penguincomputing.com>, "
	"Margit Schubert-While <margitsw@t-online.de>, "
	"Justin Thiessen <jthiessen@penguincomputing.com>");
MODULE_DESCRIPTION("LM85-B, LM85-C driver");
