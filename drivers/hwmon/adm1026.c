<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * adm1026.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *	       monitoring
 * Copyright (C) 2002, 2003  Philip Pokorny <ppokorny@penguincomputing.com>
 * Copyright (C) 2004 Justin Thiessen <jthiessen@penguincomputing.com>
 *
 * Chip details at:
 *
 * <https://www.onsemi.com/PowerSolutions/product.करो?id=ADM1026>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2c, 0x2d, 0x2e, I2C_CLIENT_END पूर्ण;

अटल पूर्णांक gpio_input[17] = अणु -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1 पूर्ण;
अटल पूर्णांक gpio_output[17] = अणु -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1 पूर्ण;
अटल पूर्णांक gpio_inverted[17] = अणु -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1 पूर्ण;
अटल पूर्णांक gpio_normal[17] = अणु -1, -1, -1, -1, -1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1, -1, -1, -1 पूर्ण;
अटल पूर्णांक gpio_fan[8] = अणु -1, -1, -1, -1, -1, -1, -1, -1 पूर्ण;
module_param_array(gpio_input, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(gpio_input, "List of GPIO pins (0-16) to program as inputs");
module_param_array(gpio_output, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(gpio_output,
		 "List of GPIO pins (0-16) to program as outputs");
module_param_array(gpio_inverted, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(gpio_inverted,
		 "List of GPIO pins (0-16) to program as inverted");
module_param_array(gpio_normal, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(gpio_normal,
		 "List of GPIO pins (0-16) to program as normal/non-inverted");
module_param_array(gpio_fan, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(gpio_fan, "List of GPIO pins (0-7) to program as fan tachs");

/* Many ADM1026 स्थिरants specअगरied below */

/* The ADM1026 रेजिस्टरs */
#घोषणा ADM1026_REG_CONFIG1	0x00
#घोषणा CFG1_MONITOR		0x01
#घोषणा CFG1_INT_ENABLE		0x02
#घोषणा CFG1_INT_CLEAR		0x04
#घोषणा CFG1_AIN8_9		0x08
#घोषणा CFG1_THERM_HOT		0x10
#घोषणा CFG1_DAC_AFC		0x20
#घोषणा CFG1_PWM_AFC		0x40
#घोषणा CFG1_RESET		0x80

#घोषणा ADM1026_REG_CONFIG2	0x01
/* CONFIG2 controls FAN0/GPIO0 through FAN7/GPIO7 */

#घोषणा ADM1026_REG_CONFIG3	0x07
#घोषणा CFG3_GPIO16_ENABLE	0x01
#घोषणा CFG3_CI_CLEAR		0x02
#घोषणा CFG3_VREF_250		0x04
#घोषणा CFG3_GPIO16_सूची		0x40
#घोषणा CFG3_GPIO16_POL		0x80

#घोषणा ADM1026_REG_E2CONFIG	0x13
#घोषणा E2CFG_READ		0x01
#घोषणा E2CFG_WRITE		0x02
#घोषणा E2CFG_ERASE		0x04
#घोषणा E2CFG_ROM		0x08
#घोषणा E2CFG_CLK_EXT		0x80

/*
 * There are 10 general analog inमाला_दो and 7 dedicated inमाला_दो
 * They are:
 *    0 - 9  =  AIN0 - AIN9
 *       10  =  Vbat
 *       11  =  3.3V Standby
 *       12  =  3.3V Main
 *       13  =  +5V
 *       14  =  Vccp (CPU core voltage)
 *       15  =  +12V
 *       16  =  -12V
 */
अटल u16 ADM1026_REG_IN[] = अणु
		0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
		0x36, 0x37, 0x27, 0x29, 0x26, 0x2a,
		0x2b, 0x2c, 0x2d, 0x2e, 0x2f
	पूर्ण;
अटल u16 ADM1026_REG_IN_MIN[] = अणु
		0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d,
		0x5e, 0x5f, 0x6d, 0x49, 0x6b, 0x4a,
		0x4b, 0x4c, 0x4d, 0x4e, 0x4f
	पूर्ण;
अटल u16 ADM1026_REG_IN_MAX[] = अणु
		0x50, 0x51, 0x52, 0x53, 0x54, 0x55,
		0x56, 0x57, 0x6c, 0x41, 0x6a, 0x42,
		0x43, 0x44, 0x45, 0x46, 0x47
	पूर्ण;

/*
 * Temperatures are:
 *    0 - Internal
 *    1 - External 1
 *    2 - External 2
 */
अटल u16 ADM1026_REG_TEMP[] = अणु 0x1f, 0x28, 0x29 पूर्ण;
अटल u16 ADM1026_REG_TEMP_MIN[] = अणु 0x69, 0x48, 0x49 पूर्ण;
अटल u16 ADM1026_REG_TEMP_MAX[] = अणु 0x68, 0x40, 0x41 पूर्ण;
अटल u16 ADM1026_REG_TEMP_TMIN[] = अणु 0x10, 0x11, 0x12 पूर्ण;
अटल u16 ADM1026_REG_TEMP_THERM[] = अणु 0x0d, 0x0e, 0x0f पूर्ण;
अटल u16 ADM1026_REG_TEMP_OFFSET[] = अणु 0x1e, 0x6e, 0x6f पूर्ण;

#घोषणा ADM1026_REG_FAN(nr)		(0x38 + (nr))
#घोषणा ADM1026_REG_FAN_MIN(nr)		(0x60 + (nr))
#घोषणा ADM1026_REG_FAN_DIV_0_3		0x02
#घोषणा ADM1026_REG_FAN_DIV_4_7		0x03

#घोषणा ADM1026_REG_DAC			0x04
#घोषणा ADM1026_REG_PWM			0x05

#घोषणा ADM1026_REG_GPIO_CFG_0_3	0x08
#घोषणा ADM1026_REG_GPIO_CFG_4_7	0x09
#घोषणा ADM1026_REG_GPIO_CFG_8_11	0x0a
#घोषणा ADM1026_REG_GPIO_CFG_12_15	0x0b
/* CFG_16 in REG_CFG3 */
#घोषणा ADM1026_REG_GPIO_STATUS_0_7	0x24
#घोषणा ADM1026_REG_GPIO_STATUS_8_15	0x25
/* STATUS_16 in REG_STATUS4 */
#घोषणा ADM1026_REG_GPIO_MASK_0_7	0x1c
#घोषणा ADM1026_REG_GPIO_MASK_8_15	0x1d
/* MASK_16 in REG_MASK4 */

#घोषणा ADM1026_REG_COMPANY		0x16
#घोषणा ADM1026_REG_VERSTEP		0x17
/* These are the recognized values क्रम the above regs */
#घोषणा ADM1026_COMPANY_ANALOG_DEV	0x41
#घोषणा ADM1026_VERSTEP_GENERIC		0x40
#घोषणा ADM1026_VERSTEP_ADM1026		0x44

#घोषणा ADM1026_REG_MASK1		0x18
#घोषणा ADM1026_REG_MASK2		0x19
#घोषणा ADM1026_REG_MASK3		0x1a
#घोषणा ADM1026_REG_MASK4		0x1b

#घोषणा ADM1026_REG_STATUS1		0x20
#घोषणा ADM1026_REG_STATUS2		0x21
#घोषणा ADM1026_REG_STATUS3		0x22
#घोषणा ADM1026_REG_STATUS4		0x23

#घोषणा ADM1026_FAN_ACTIVATION_TEMP_HYST -6
#घोषणा ADM1026_FAN_CONTROL_TEMP_RANGE	20
#घोषणा ADM1026_PWM_MAX			255

/*
 * Conversions. Rounding and limit checking is only करोne on the TO_REG
 * variants. Note that you should be a bit careful with which arguments
 * these macros are called: arguments may be evaluated more than once.
 */

/*
 * IN are scaled according to built-in resistors.  These are the
 *   voltages corresponding to 3/4 of full scale (192 or 0xc0)
 *   NOTE: The -12V input needs an additional factor to account
 *      क्रम the Vref pullup resistor.
 *      NEG12_OFFSET = SCALE * Vref / V-192 - Vref
 *                   = 13875 * 2.50 / 1.875 - 2500
 *                   = 16000
 *
 * The values in this table are based on Table II, page 15 of the
 *    datasheet.
 */
अटल पूर्णांक adm1026_scaling[] = अणु /* .001 Volts */
		2250, 2250, 2250, 2250, 2250, 2250,
		1875, 1875, 1875, 1875, 3000, 3330,
		3330, 4995, 2250, 12000, 13875
	पूर्ण;
#घोषणा NEG12_OFFSET  16000
#घोषणा SCALE(val, from, to) (((val)*(to) + ((from)/2))/(from))
#घोषणा INS_TO_REG(n, val)	\
		SCALE(clamp_val(val, 0, 255 * adm1026_scaling[n] / 192), \
		      adm1026_scaling[n], 192)
#घोषणा INS_FROM_REG(n, val) (SCALE(val, 192, adm1026_scaling[n]))

/*
 * FAN speed is measured using 22.5kHz घड़ी and counts क्रम 2 pulses
 *   and we assume a 2 pulse-per-rev fan tach संकेत
 *      22500 kHz * 60 (sec/min) * 2 (pulse) / 2 (pulse/rev) == 1350000
 */
#घोषणा FAN_TO_REG(val, भाग)  ((val) <= 0 ? 0xff : \
				clamp_val(1350000 / ((val) * (भाग)), \
					      1, 254))
#घोषणा FAN_FROM_REG(val, भाग) ((val) == 0 ? -1 : (val) == 0xff ? 0 : \
				1350000 / ((val) * (भाग)))
#घोषणा DIV_FROM_REG(val) (1 << (val))
#घोषणा DIV_TO_REG(val) ((val) >= 8 ? 3 : (val) >= 4 ? 2 : (val) >= 2 ? 1 : 0)

/* Temperature is reported in 1 degC increments */
#घोषणा TEMP_TO_REG(val) DIV_ROUND_CLOSEST(clamp_val(val, -128000, 127000), \
					   1000)
#घोषणा TEMP_FROM_REG(val) ((val) * 1000)
#घोषणा OFFSET_TO_REG(val) DIV_ROUND_CLOSEST(clamp_val(val, -128000, 127000), \
					     1000)
#घोषणा OFFSET_FROM_REG(val) ((val) * 1000)

#घोषणा PWM_TO_REG(val) (clamp_val(val, 0, 255))
#घोषणा PWM_FROM_REG(val) (val)

#घोषणा PWM_MIN_TO_REG(val) ((val) & 0xf0)
#घोषणा PWM_MIN_FROM_REG(val) (((val) & 0xf0) + ((val) >> 4))

/*
 * Analog output is a voltage, and scaled to millivolts.  The datasheet
 *   indicates that the DAC could be used to drive the fans, but in our
 *   example board (Arima HDAMA) it isn't connected to the fans at all.
 */
#घोषणा DAC_TO_REG(val) DIV_ROUND_CLOSEST(clamp_val(val, 0, 2500) * 255, \
					  2500)
#घोषणा DAC_FROM_REG(val) (((val) * 2500) / 255)

/*
 * Chip sampling rates
 *
 * Some sensors are not updated more frequently than once per second
 *    so it करोesn't make sense to पढ़ो them more often than that.
 *    We cache the results and वापस the saved data अगर the driver
 *    is called again beक्रमe a second has elapsed.
 *
 * Also, there is signअगरicant configuration data क्रम this chip
 *    So, we keep the config data up to date in the cache
 *    when it is written and only sample it once every 5 *minutes*
 */
#घोषणा ADM1026_DATA_INTERVAL		(1 * HZ)
#घोषणा ADM1026_CONFIG_INTERVAL		(5 * 60 * HZ)

/*
 * We allow क्रम multiple chips in a single प्रणाली.
 *
 * For each रेजिस्टरed ADM1026, we need to keep state inक्रमmation
 * at client->data. The adm1026_data काष्ठाure is dynamically
 * allocated, when a new client काष्ठाure is allocated.
 */

काष्ठा pwm_data अणु
	u8 pwm;
	u8 enable;
	u8 स्वतः_pwm_min;
पूर्ण;

काष्ठा adm1026_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा attribute_group *groups[3];

	काष्ठा mutex update_lock;
	पूर्णांक valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_पढ़ोing;	/* In jअगरfies */
	अचिन्हित दीर्घ last_config;	/* In jअगरfies */

	u8 in[17];		/* Register value */
	u8 in_max[17];		/* Register value */
	u8 in_min[17];		/* Register value */
	s8 temp[3];		/* Register value */
	s8 temp_min[3];		/* Register value */
	s8 temp_max[3];		/* Register value */
	s8 temp_पंचांगin[3];	/* Register value */
	s8 temp_crit[3];	/* Register value */
	s8 temp_offset[3];	/* Register value */
	u8 fan[8];		/* Register value */
	u8 fan_min[8];		/* Register value */
	u8 fan_भाग[8];		/* Decoded value */
	काष्ठा pwm_data pwm1;	/* Pwm control values */
	u8 vrm;			/* VRM version */
	u8 analog_out;		/* Register value (DAC) */
	दीर्घ alarms;		/* Register encoding, combined */
	दीर्घ alarm_mask;	/* Register encoding, combined */
	दीर्घ gpio;		/* Register encoding, combined */
	दीर्घ gpio_mask;		/* Register encoding, combined */
	u8 gpio_config[17];	/* Decoded value */
	u8 config1;		/* Register value */
	u8 config2;		/* Register value */
	u8 config3;		/* Register value */
पूर्ण;

अटल पूर्णांक adm1026_पढ़ो_value(काष्ठा i2c_client *client, u8 reg)
अणु
	पूर्णांक res;

	अगर (reg < 0x80) अणु
		/* "RAM" locations */
		res = i2c_smbus_पढ़ो_byte_data(client, reg) & 0xff;
	पूर्ण अन्यथा अणु
		/* EEPROM, करो nothing */
		res = 0;
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक adm1026_ग_लिखो_value(काष्ठा i2c_client *client, u8 reg, पूर्णांक value)
अणु
	पूर्णांक res;

	अगर (reg < 0x80) अणु
		/* "RAM" locations */
		res = i2c_smbus_ग_लिखो_byte_data(client, reg, value);
	पूर्ण अन्यथा अणु
		/* EEPROM, करो nothing */
		res = 0;
	पूर्ण
	वापस res;
पूर्ण

अटल काष्ठा adm1026_data *adm1026_update_device(काष्ठा device *dev)
अणु
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक i;
	दीर्घ value, alarms, gpio;

	mutex_lock(&data->update_lock);
	अगर (!data->valid
	    || समय_after(jअगरfies,
			  data->last_पढ़ोing + ADM1026_DATA_INTERVAL)) अणु
		/* Things that change quickly */
		dev_dbg(&client->dev, "Reading sensor values\n");
		क्रम (i = 0; i <= 16; ++i) अणु
			data->in[i] =
			    adm1026_पढ़ो_value(client, ADM1026_REG_IN[i]);
		पूर्ण

		क्रम (i = 0; i <= 7; ++i) अणु
			data->fan[i] =
			    adm1026_पढ़ो_value(client, ADM1026_REG_FAN(i));
		पूर्ण

		क्रम (i = 0; i <= 2; ++i) अणु
			/*
			 * NOTE: temp[] is s8 and we assume 2's complement
			 *   "conversion" in the assignment
			 */
			data->temp[i] =
			    adm1026_पढ़ो_value(client, ADM1026_REG_TEMP[i]);
		पूर्ण

		data->pwm1.pwm = adm1026_पढ़ो_value(client,
			ADM1026_REG_PWM);
		data->analog_out = adm1026_पढ़ो_value(client,
			ADM1026_REG_DAC);
		/* GPIO16 is MSbit of alarms, move it to gpio */
		alarms = adm1026_पढ़ो_value(client, ADM1026_REG_STATUS4);
		gpio = alarms & 0x80 ? 0x0100 : 0; /* GPIO16 */
		alarms &= 0x7f;
		alarms <<= 8;
		alarms |= adm1026_पढ़ो_value(client, ADM1026_REG_STATUS3);
		alarms <<= 8;
		alarms |= adm1026_पढ़ो_value(client, ADM1026_REG_STATUS2);
		alarms <<= 8;
		alarms |= adm1026_पढ़ो_value(client, ADM1026_REG_STATUS1);
		data->alarms = alarms;

		/* Read the GPIO values */
		gpio |= adm1026_पढ़ो_value(client,
			ADM1026_REG_GPIO_STATUS_8_15);
		gpio <<= 8;
		gpio |= adm1026_पढ़ो_value(client,
			ADM1026_REG_GPIO_STATUS_0_7);
		data->gpio = gpio;

		data->last_पढ़ोing = jअगरfies;
	पूर्ण	/* last_पढ़ोing */

	अगर (!data->valid ||
	    समय_after(jअगरfies, data->last_config + ADM1026_CONFIG_INTERVAL)) अणु
		/* Things that करोn't change often */
		dev_dbg(&client->dev, "Reading config values\n");
		क्रम (i = 0; i <= 16; ++i) अणु
			data->in_min[i] = adm1026_पढ़ो_value(client,
				ADM1026_REG_IN_MIN[i]);
			data->in_max[i] = adm1026_पढ़ो_value(client,
				ADM1026_REG_IN_MAX[i]);
		पूर्ण

		value = adm1026_पढ़ो_value(client, ADM1026_REG_FAN_DIV_0_3)
			| (adm1026_पढ़ो_value(client, ADM1026_REG_FAN_DIV_4_7)
			<< 8);
		क्रम (i = 0; i <= 7; ++i) अणु
			data->fan_min[i] = adm1026_पढ़ो_value(client,
				ADM1026_REG_FAN_MIN(i));
			data->fan_भाग[i] = DIV_FROM_REG(value & 0x03);
			value >>= 2;
		पूर्ण

		क्रम (i = 0; i <= 2; ++i) अणु
			/*
			 * NOTE: temp_xxx[] are s8 and we assume 2's
			 *    complement "conversion" in the assignment
			 */
			data->temp_min[i] = adm1026_पढ़ो_value(client,
				ADM1026_REG_TEMP_MIN[i]);
			data->temp_max[i] = adm1026_पढ़ो_value(client,
				ADM1026_REG_TEMP_MAX[i]);
			data->temp_पंचांगin[i] = adm1026_पढ़ो_value(client,
				ADM1026_REG_TEMP_TMIN[i]);
			data->temp_crit[i] = adm1026_पढ़ो_value(client,
				ADM1026_REG_TEMP_THERM[i]);
			data->temp_offset[i] = adm1026_पढ़ो_value(client,
				ADM1026_REG_TEMP_OFFSET[i]);
		पूर्ण

		/* Read the STATUS/alarm masks */
		alarms = adm1026_पढ़ो_value(client, ADM1026_REG_MASK4);
		gpio = alarms & 0x80 ? 0x0100 : 0; /* GPIO16 */
		alarms = (alarms & 0x7f) << 8;
		alarms |= adm1026_पढ़ो_value(client, ADM1026_REG_MASK3);
		alarms <<= 8;
		alarms |= adm1026_पढ़ो_value(client, ADM1026_REG_MASK2);
		alarms <<= 8;
		alarms |= adm1026_पढ़ो_value(client, ADM1026_REG_MASK1);
		data->alarm_mask = alarms;

		/* Read the GPIO values */
		gpio |= adm1026_पढ़ो_value(client,
			ADM1026_REG_GPIO_MASK_8_15);
		gpio <<= 8;
		gpio |= adm1026_पढ़ो_value(client, ADM1026_REG_GPIO_MASK_0_7);
		data->gpio_mask = gpio;

		/* Read various values from CONFIG1 */
		data->config1 = adm1026_पढ़ो_value(client,
			ADM1026_REG_CONFIG1);
		अगर (data->config1 & CFG1_PWM_AFC) अणु
			data->pwm1.enable = 2;
			data->pwm1.स्वतः_pwm_min =
				PWM_MIN_FROM_REG(data->pwm1.pwm);
		पूर्ण
		/* Read the GPIO config */
		data->config2 = adm1026_पढ़ो_value(client,
			ADM1026_REG_CONFIG2);
		data->config3 = adm1026_पढ़ो_value(client,
			ADM1026_REG_CONFIG3);
		data->gpio_config[16] = (data->config3 >> 6) & 0x03;

		value = 0;
		क्रम (i = 0; i <= 15; ++i) अणु
			अगर ((i & 0x03) == 0) अणु
				value = adm1026_पढ़ो_value(client,
					    ADM1026_REG_GPIO_CFG_0_3 + i/4);
			पूर्ण
			data->gpio_config[i] = value & 0x03;
			value >>= 2;
		पूर्ण

		data->last_config = jअगरfies;
	पूर्ण	/* last_config */

	data->valid = 1;
	mutex_unlock(&data->update_lock);
	वापस data;
पूर्ण

अटल sमाप_प्रकार in_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", INS_FROM_REG(nr, data->in[nr]));
पूर्ण
अटल sमाप_प्रकार in_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", INS_FROM_REG(nr, data->in_min[nr]));
पूर्ण
अटल sमाप_प्रकार in_min_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_min[nr] = INS_TO_REG(nr, val);
	adm1026_ग_लिखो_value(client, ADM1026_REG_IN_MIN[nr], data->in_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
अटल sमाप_प्रकार in_max_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", INS_FROM_REG(nr, data->in_max[nr]));
पूर्ण
अटल sमाप_प्रकार in_max_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_max[nr] = INS_TO_REG(nr, val);
	adm1026_ग_लिखो_value(client, ADM1026_REG_IN_MAX[nr], data->in_max[nr]);
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
अटल SENSOR_DEVICE_ATTR_RO(in8_input, in, 8);
अटल SENSOR_DEVICE_ATTR_RW(in8_min, in_min, 8);
अटल SENSOR_DEVICE_ATTR_RW(in8_max, in_max, 8);
अटल SENSOR_DEVICE_ATTR_RO(in9_input, in, 9);
अटल SENSOR_DEVICE_ATTR_RW(in9_min, in_min, 9);
अटल SENSOR_DEVICE_ATTR_RW(in9_max, in_max, 9);
अटल SENSOR_DEVICE_ATTR_RO(in10_input, in, 10);
अटल SENSOR_DEVICE_ATTR_RW(in10_min, in_min, 10);
अटल SENSOR_DEVICE_ATTR_RW(in10_max, in_max, 10);
अटल SENSOR_DEVICE_ATTR_RO(in11_input, in, 11);
अटल SENSOR_DEVICE_ATTR_RW(in11_min, in_min, 11);
अटल SENSOR_DEVICE_ATTR_RW(in11_max, in_max, 11);
अटल SENSOR_DEVICE_ATTR_RO(in12_input, in, 12);
अटल SENSOR_DEVICE_ATTR_RW(in12_min, in_min, 12);
अटल SENSOR_DEVICE_ATTR_RW(in12_max, in_max, 12);
अटल SENSOR_DEVICE_ATTR_RO(in13_input, in, 13);
अटल SENSOR_DEVICE_ATTR_RW(in13_min, in_min, 13);
अटल SENSOR_DEVICE_ATTR_RW(in13_max, in_max, 13);
अटल SENSOR_DEVICE_ATTR_RO(in14_input, in, 14);
अटल SENSOR_DEVICE_ATTR_RW(in14_min, in_min, 14);
अटल SENSOR_DEVICE_ATTR_RW(in14_max, in_max, 14);
अटल SENSOR_DEVICE_ATTR_RO(in15_input, in, 15);
अटल SENSOR_DEVICE_ATTR_RW(in15_min, in_min, 15);
अटल SENSOR_DEVICE_ATTR_RW(in15_max, in_max, 15);

अटल sमाप_प्रकार in16_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", INS_FROM_REG(16, data->in[16]) -
		NEG12_OFFSET);
पूर्ण
अटल sमाप_प्रकार in16_min_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", INS_FROM_REG(16, data->in_min[16])
		- NEG12_OFFSET);
पूर्ण
अटल sमाप_प्रकार in16_min_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_min[16] = INS_TO_REG(16,
				      clamp_val(val, पूर्णांक_न्यून,
						पूर्णांक_उच्च - NEG12_OFFSET) +
				      NEG12_OFFSET);
	adm1026_ग_लिखो_value(client, ADM1026_REG_IN_MIN[16], data->in_min[16]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
अटल sमाप_प्रकार in16_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", INS_FROM_REG(16, data->in_max[16])
			- NEG12_OFFSET);
पूर्ण
अटल sमाप_प्रकार in16_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_max[16] = INS_TO_REG(16,
				      clamp_val(val, पूर्णांक_न्यून,
						पूर्णांक_उच्च - NEG12_OFFSET) +
				      NEG12_OFFSET);
	adm1026_ग_लिखो_value(client, ADM1026_REG_IN_MAX[16], data->in_max[16]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in16_input, in16, 16);
अटल SENSOR_DEVICE_ATTR_RW(in16_min, in16_min, 16);
अटल SENSOR_DEVICE_ATTR_RW(in16_max, in16_max, 16);

/* Now add fan पढ़ो/ग_लिखो functions */

अटल sमाप_प्रकार fan_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan[nr],
		data->fan_भाग[nr]));
पूर्ण
अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan_min[nr],
		data->fan_भाग[nr]));
पूर्ण
अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan_min[nr] = FAN_TO_REG(val, data->fan_भाग[nr]);
	adm1026_ग_लिखो_value(client, ADM1026_REG_FAN_MIN(nr),
		data->fan_min[nr]);
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
अटल SENSOR_DEVICE_ATTR_RO(fan5_input, fan, 4);
अटल SENSOR_DEVICE_ATTR_RW(fan5_min, fan_min, 4);
अटल SENSOR_DEVICE_ATTR_RO(fan6_input, fan, 5);
अटल SENSOR_DEVICE_ATTR_RW(fan6_min, fan_min, 5);
अटल SENSOR_DEVICE_ATTR_RO(fan7_input, fan, 6);
अटल SENSOR_DEVICE_ATTR_RW(fan7_min, fan_min, 6);
अटल SENSOR_DEVICE_ATTR_RO(fan8_input, fan, 7);
अटल SENSOR_DEVICE_ATTR_RW(fan8_min, fan_min, 7);

/* Adjust fan_min to account क्रम new fan भागisor */
अटल व्योम fixup_fan_min(काष्ठा device *dev, पूर्णांक fan, पूर्णांक old_भाग)
अणु
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक new_min;
	पूर्णांक new_भाग = data->fan_भाग[fan];

	/* 0 and 0xff are special.  Don't adjust them */
	अगर (data->fan_min[fan] == 0 || data->fan_min[fan] == 0xff)
		वापस;

	new_min = data->fan_min[fan] * old_भाग / new_भाग;
	new_min = clamp_val(new_min, 1, 254);
	data->fan_min[fan] = new_min;
	adm1026_ग_लिखो_value(client, ADM1026_REG_FAN_MIN(fan), new_min);
पूर्ण

/* Now add fan_भाग पढ़ो/ग_लिखो functions */
अटल sमाप_प्रकार fan_भाग_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->fan_भाग[nr]);
पूर्ण
अटल sमाप_प्रकार fan_भाग_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक orig_भाग, new_भाग;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	new_भाग = DIV_TO_REG(val);

	mutex_lock(&data->update_lock);
	orig_भाग = data->fan_भाग[nr];
	data->fan_भाग[nr] = DIV_FROM_REG(new_भाग);

	अगर (nr < 4) अणु /* 0 <= nr < 4 */
		adm1026_ग_लिखो_value(client, ADM1026_REG_FAN_DIV_0_3,
				    (DIV_TO_REG(data->fan_भाग[0]) << 0) |
				    (DIV_TO_REG(data->fan_भाग[1]) << 2) |
				    (DIV_TO_REG(data->fan_भाग[2]) << 4) |
				    (DIV_TO_REG(data->fan_भाग[3]) << 6));
	पूर्ण अन्यथा अणु /* 3 < nr < 8 */
		adm1026_ग_लिखो_value(client, ADM1026_REG_FAN_DIV_4_7,
				    (DIV_TO_REG(data->fan_भाग[4]) << 0) |
				    (DIV_TO_REG(data->fan_भाग[5]) << 2) |
				    (DIV_TO_REG(data->fan_भाग[6]) << 4) |
				    (DIV_TO_REG(data->fan_भाग[7]) << 6));
	पूर्ण

	अगर (data->fan_भाग[nr] != orig_भाग)
		fixup_fan_min(dev, nr, orig_भाग);

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(fan1_भाग, fan_भाग, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_भाग, fan_भाग, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan3_भाग, fan_भाग, 2);
अटल SENSOR_DEVICE_ATTR_RW(fan4_भाग, fan_भाग, 3);
अटल SENSOR_DEVICE_ATTR_RW(fan5_भाग, fan_भाग, 4);
अटल SENSOR_DEVICE_ATTR_RW(fan6_भाग, fan_भाग, 5);
अटल SENSOR_DEVICE_ATTR_RW(fan7_भाग, fan_भाग, 6);
अटल SENSOR_DEVICE_ATTR_RW(fan8_भाग, fan_भाग, 7);

/* Temps */
अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp[nr]));
पूर्ण
अटल sमाप_प्रकार temp_min_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_min[nr]));
पूर्ण
अटल sमाप_प्रकार temp_min_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_min[nr] = TEMP_TO_REG(val);
	adm1026_ग_लिखो_value(client, ADM1026_REG_TEMP_MIN[nr],
		data->temp_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
अटल sमाप_प्रकार temp_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_max[nr]));
पूर्ण
अटल sमाप_प्रकार temp_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_max[nr] = TEMP_TO_REG(val);
	adm1026_ग_लिखो_value(client, ADM1026_REG_TEMP_MAX[nr],
		data->temp_max[nr]);
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

अटल sमाप_प्रकार temp_offset_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_offset[nr]));
पूर्ण
अटल sमाप_प्रकार temp_offset_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_offset[nr] = TEMP_TO_REG(val);
	adm1026_ग_लिखो_value(client, ADM1026_REG_TEMP_OFFSET[nr],
		data->temp_offset[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(temp1_offset, temp_offset, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_offset, temp_offset, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_offset, temp_offset, 2);

अटल sमाप_प्रकार temp_स्वतः_poपूर्णांक1_temp_hyst_show(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(
		ADM1026_FAN_ACTIVATION_TEMP_HYST + data->temp_पंचांगin[nr]));
पूर्ण
अटल sमाप_प्रकार temp_स्वतः_poपूर्णांक2_temp_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_पंचांगin[nr] +
		ADM1026_FAN_CONTROL_TEMP_RANGE));
पूर्ण
अटल sमाप_प्रकार temp_स्वतः_poपूर्णांक1_temp_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_पंचांगin[nr]));
पूर्ण
अटल sमाप_प्रकार temp_स्वतः_poपूर्णांक1_temp_store(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_पंचांगin[nr] = TEMP_TO_REG(val);
	adm1026_ग_लिखो_value(client, ADM1026_REG_TEMP_TMIN[nr],
		data->temp_पंचांगin[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(temp1_स्वतः_poपूर्णांक1_temp, temp_स्वतः_poपूर्णांक1_temp, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp1_स्वतः_poपूर्णांक1_temp_hyst,
			     temp_स्वतः_poपूर्णांक1_temp_hyst, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp1_स्वतः_poपूर्णांक2_temp, temp_स्वतः_poपूर्णांक2_temp, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_स्वतः_poपूर्णांक1_temp, temp_स्वतः_poपूर्णांक1_temp, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp2_स्वतः_poपूर्णांक1_temp_hyst,
			     temp_स्वतः_poपूर्णांक1_temp_hyst, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp2_स्वतः_poपूर्णांक2_temp, temp_स्वतः_poपूर्णांक2_temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_स्वतः_poपूर्णांक1_temp, temp_स्वतः_poपूर्णांक1_temp, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp3_स्वतः_poपूर्णांक1_temp_hyst,
			     temp_स्वतः_poपूर्णांक1_temp_hyst, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp3_स्वतः_poपूर्णांक2_temp, temp_स्वतः_poपूर्णांक2_temp, 2);

अटल sमाप_प्रकार show_temp_crit_enable(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", (data->config1 & CFG1_THERM_HOT) >> 4);
पूर्ण
अटल sमाप_प्रकार set_temp_crit_enable(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val > 1)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->config1 = (data->config1 & ~CFG1_THERM_HOT) | (val << 4);
	adm1026_ग_लिखो_value(client, ADM1026_REG_CONFIG1, data->config1);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(temp1_crit_enable, 0644, show_temp_crit_enable,
		   set_temp_crit_enable);
अटल DEVICE_ATTR(temp2_crit_enable, 0644, show_temp_crit_enable,
		   set_temp_crit_enable);
अटल DEVICE_ATTR(temp3_crit_enable, 0644, show_temp_crit_enable,
		   set_temp_crit_enable);

अटल sमाप_प्रकार temp_crit_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_crit[nr]));
पूर्ण
अटल sमाप_प्रकार temp_crit_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_crit[nr] = TEMP_TO_REG(val);
	adm1026_ग_लिखो_value(client, ADM1026_REG_TEMP_THERM[nr],
		data->temp_crit[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(temp1_crit, temp_crit, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_crit, temp_crit, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_crit, temp_crit, 2);

अटल sमाप_प्रकार analog_out_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", DAC_FROM_REG(data->analog_out));
पूर्ण
अटल sमाप_प्रकार analog_out_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->analog_out = DAC_TO_REG(val);
	adm1026_ग_लिखो_value(client, ADM1026_REG_DAC, data->analog_out);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(analog_out);

अटल sमाप_प्रकार cpu0_vid_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	पूर्णांक vid = (data->gpio >> 11) & 0x1f;

	dev_dbg(dev, "Setting VID from GPIO11-15.\n");
	वापस प्र_लिखो(buf, "%d\n", vid_from_reg(vid, data->vrm));
पूर्ण

अटल DEVICE_ATTR_RO(cpu0_vid);

अटल sमाप_प्रकार vrm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", data->vrm);
पूर्ण

अटल sमाप_प्रकार vrm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
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
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", data->alarms);
पूर्ण

अटल DEVICE_ATTR_RO(alarms);

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	वापस प्र_लिखो(buf, "%ld\n", (data->alarms >> bitnr) & 1);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp2_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp3_alarm, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(in9_alarm, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(in11_alarm, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(in12_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(in13_alarm, alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(in14_alarm, alarm, 5);
अटल SENSOR_DEVICE_ATTR_RO(in15_alarm, alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(in16_alarm, alarm, 7);
अटल SENSOR_DEVICE_ATTR_RO(in0_alarm, alarm, 8);
अटल SENSOR_DEVICE_ATTR_RO(in1_alarm, alarm, 9);
अटल SENSOR_DEVICE_ATTR_RO(in2_alarm, alarm, 10);
अटल SENSOR_DEVICE_ATTR_RO(in3_alarm, alarm, 11);
अटल SENSOR_DEVICE_ATTR_RO(in4_alarm, alarm, 12);
अटल SENSOR_DEVICE_ATTR_RO(in5_alarm, alarm, 13);
अटल SENSOR_DEVICE_ATTR_RO(in6_alarm, alarm, 14);
अटल SENSOR_DEVICE_ATTR_RO(in7_alarm, alarm, 15);
अटल SENSOR_DEVICE_ATTR_RO(fan1_alarm, alarm, 16);
अटल SENSOR_DEVICE_ATTR_RO(fan2_alarm, alarm, 17);
अटल SENSOR_DEVICE_ATTR_RO(fan3_alarm, alarm, 18);
अटल SENSOR_DEVICE_ATTR_RO(fan4_alarm, alarm, 19);
अटल SENSOR_DEVICE_ATTR_RO(fan5_alarm, alarm, 20);
अटल SENSOR_DEVICE_ATTR_RO(fan6_alarm, alarm, 21);
अटल SENSOR_DEVICE_ATTR_RO(fan7_alarm, alarm, 22);
अटल SENSOR_DEVICE_ATTR_RO(fan8_alarm, alarm, 23);
अटल SENSOR_DEVICE_ATTR_RO(temp1_alarm, alarm, 24);
अटल SENSOR_DEVICE_ATTR_RO(in10_alarm, alarm, 25);
अटल SENSOR_DEVICE_ATTR_RO(in8_alarm, alarm, 26);

अटल sमाप_प्रकार alarm_mask_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", data->alarm_mask);
पूर्ण
अटल sमाप_प्रकार alarm_mask_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ mask;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->alarm_mask = val & 0x7fffffff;
	mask = data->alarm_mask
		| (data->gpio_mask & 0x10000 ? 0x80000000 : 0);
	adm1026_ग_लिखो_value(client, ADM1026_REG_MASK1,
		mask & 0xff);
	mask >>= 8;
	adm1026_ग_लिखो_value(client, ADM1026_REG_MASK2,
		mask & 0xff);
	mask >>= 8;
	adm1026_ग_लिखो_value(client, ADM1026_REG_MASK3,
		mask & 0xff);
	mask >>= 8;
	adm1026_ग_लिखो_value(client, ADM1026_REG_MASK4,
		mask & 0xff);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(alarm_mask);

अटल sमाप_प्रकार gpio_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", data->gpio);
पूर्ण
अटल sमाप_प्रकार gpio_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ gpio;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->gpio = val & 0x1ffff;
	gpio = data->gpio;
	adm1026_ग_लिखो_value(client, ADM1026_REG_GPIO_STATUS_0_7, gpio & 0xff);
	gpio >>= 8;
	adm1026_ग_लिखो_value(client, ADM1026_REG_GPIO_STATUS_8_15, gpio & 0xff);
	gpio = ((gpio >> 1) & 0x80) | (data->alarms >> 24 & 0x7f);
	adm1026_ग_लिखो_value(client, ADM1026_REG_STATUS4, gpio & 0xff);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(gpio);

अटल sमाप_प्रकार gpio_mask_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", data->gpio_mask);
पूर्ण
अटल sमाप_प्रकार gpio_mask_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ mask;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->gpio_mask = val & 0x1ffff;
	mask = data->gpio_mask;
	adm1026_ग_लिखो_value(client, ADM1026_REG_GPIO_MASK_0_7, mask & 0xff);
	mask >>= 8;
	adm1026_ग_लिखो_value(client, ADM1026_REG_GPIO_MASK_8_15, mask & 0xff);
	mask = ((mask >> 1) & 0x80) | (data->alarm_mask >> 24 & 0x7f);
	adm1026_ग_लिखो_value(client, ADM1026_REG_MASK1, mask & 0xff);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(gpio_mask);

अटल sमाप_प्रकार pwm1_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", PWM_FROM_REG(data->pwm1.pwm));
पूर्ण

अटल sमाप_प्रकार pwm1_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	अगर (data->pwm1.enable == 1) अणु
		दीर्घ val;
		पूर्णांक err;

		err = kम_से_दीर्घ(buf, 10, &val);
		अगर (err)
			वापस err;

		mutex_lock(&data->update_lock);
		data->pwm1.pwm = PWM_TO_REG(val);
		adm1026_ग_लिखो_value(client, ADM1026_REG_PWM, data->pwm1.pwm);
		mutex_unlock(&data->update_lock);
	पूर्ण
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp1_स्वतः_poपूर्णांक1_pwm_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->pwm1.स्वतः_pwm_min);
पूर्ण

अटल sमाप_प्रकार temp1_स्वतः_poपूर्णांक1_pwm_store(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->pwm1.स्वतः_pwm_min = clamp_val(val, 0, 255);
	अगर (data->pwm1.enable == 2) अणु /* apply immediately */
		data->pwm1.pwm = PWM_TO_REG((data->pwm1.pwm & 0x0f) |
			PWM_MIN_TO_REG(data->pwm1.स्वतः_pwm_min));
		adm1026_ग_लिखो_value(client, ADM1026_REG_PWM, data->pwm1.pwm);
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp1_स्वतः_poपूर्णांक2_pwm_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", ADM1026_PWM_MAX);
पूर्ण

अटल sमाप_प्रकार pwm1_enable_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adm1026_data *data = adm1026_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->pwm1.enable);
पूर्ण

अटल sमाप_प्रकार pwm1_enable_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm1026_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक old_enable;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val >= 3)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	old_enable = data->pwm1.enable;
	data->pwm1.enable = val;
	data->config1 = (data->config1 & ~CFG1_PWM_AFC)
			| ((val == 2) ? CFG1_PWM_AFC : 0);
	adm1026_ग_लिखो_value(client, ADM1026_REG_CONFIG1, data->config1);
	अगर (val == 2) अणु /* apply pwm1_स्वतः_pwm_min to pwm1 */
		data->pwm1.pwm = PWM_TO_REG((data->pwm1.pwm & 0x0f) |
			PWM_MIN_TO_REG(data->pwm1.स्वतः_pwm_min));
		adm1026_ग_लिखो_value(client, ADM1026_REG_PWM, data->pwm1.pwm);
	पूर्ण अन्यथा अगर (!((old_enable == 1) && (val == 1))) अणु
		/* set pwm to safe value */
		data->pwm1.pwm = 255;
		adm1026_ग_लिखो_value(client, ADM1026_REG_PWM, data->pwm1.pwm);
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* enable PWM fan control */
अटल DEVICE_ATTR_RW(pwm1);
अटल DEVICE_ATTR(pwm2, 0644, pwm1_show, pwm1_store);
अटल DEVICE_ATTR(pwm3, 0644, pwm1_show, pwm1_store);
अटल DEVICE_ATTR_RW(pwm1_enable);
अटल DEVICE_ATTR(pwm2_enable, 0644, pwm1_enable_show,
		   pwm1_enable_store);
अटल DEVICE_ATTR(pwm3_enable, 0644, pwm1_enable_show,
		   pwm1_enable_store);
अटल DEVICE_ATTR_RW(temp1_स्वतः_poपूर्णांक1_pwm);
अटल DEVICE_ATTR(temp2_स्वतः_poपूर्णांक1_pwm, 0644,
		   temp1_स्वतः_poपूर्णांक1_pwm_show, temp1_स्वतः_poपूर्णांक1_pwm_store);
अटल DEVICE_ATTR(temp3_स्वतः_poपूर्णांक1_pwm, 0644,
		   temp1_स्वतः_poपूर्णांक1_pwm_show, temp1_स्वतः_poपूर्णांक1_pwm_store);

अटल DEVICE_ATTR_RO(temp1_स्वतः_poपूर्णांक2_pwm);
अटल DEVICE_ATTR(temp2_स्वतः_poपूर्णांक2_pwm, 0444, temp1_स्वतः_poपूर्णांक2_pwm_show,
		   शून्य);
अटल DEVICE_ATTR(temp3_स्वतः_poपूर्णांक2_pwm, 0444, temp1_स्वतः_poपूर्णांक2_pwm_show,
		   शून्य);

अटल काष्ठा attribute *adm1026_attributes[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in1_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in5_alarm.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in6_max.dev_attr.attr,
	&sensor_dev_attr_in6_min.dev_attr.attr,
	&sensor_dev_attr_in6_alarm.dev_attr.attr,
	&sensor_dev_attr_in7_input.dev_attr.attr,
	&sensor_dev_attr_in7_max.dev_attr.attr,
	&sensor_dev_attr_in7_min.dev_attr.attr,
	&sensor_dev_attr_in7_alarm.dev_attr.attr,
	&sensor_dev_attr_in10_input.dev_attr.attr,
	&sensor_dev_attr_in10_max.dev_attr.attr,
	&sensor_dev_attr_in10_min.dev_attr.attr,
	&sensor_dev_attr_in10_alarm.dev_attr.attr,
	&sensor_dev_attr_in11_input.dev_attr.attr,
	&sensor_dev_attr_in11_max.dev_attr.attr,
	&sensor_dev_attr_in11_min.dev_attr.attr,
	&sensor_dev_attr_in11_alarm.dev_attr.attr,
	&sensor_dev_attr_in12_input.dev_attr.attr,
	&sensor_dev_attr_in12_max.dev_attr.attr,
	&sensor_dev_attr_in12_min.dev_attr.attr,
	&sensor_dev_attr_in12_alarm.dev_attr.attr,
	&sensor_dev_attr_in13_input.dev_attr.attr,
	&sensor_dev_attr_in13_max.dev_attr.attr,
	&sensor_dev_attr_in13_min.dev_attr.attr,
	&sensor_dev_attr_in13_alarm.dev_attr.attr,
	&sensor_dev_attr_in14_input.dev_attr.attr,
	&sensor_dev_attr_in14_max.dev_attr.attr,
	&sensor_dev_attr_in14_min.dev_attr.attr,
	&sensor_dev_attr_in14_alarm.dev_attr.attr,
	&sensor_dev_attr_in15_input.dev_attr.attr,
	&sensor_dev_attr_in15_max.dev_attr.attr,
	&sensor_dev_attr_in15_min.dev_attr.attr,
	&sensor_dev_attr_in15_alarm.dev_attr.attr,
	&sensor_dev_attr_in16_input.dev_attr.attr,
	&sensor_dev_attr_in16_max.dev_attr.attr,
	&sensor_dev_attr_in16_min.dev_attr.attr,
	&sensor_dev_attr_in16_alarm.dev_attr.attr,
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_भाग.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan2_भाग.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan3_भाग.dev_attr.attr,
	&sensor_dev_attr_fan3_min.dev_attr.attr,
	&sensor_dev_attr_fan3_alarm.dev_attr.attr,
	&sensor_dev_attr_fan4_input.dev_attr.attr,
	&sensor_dev_attr_fan4_भाग.dev_attr.attr,
	&sensor_dev_attr_fan4_min.dev_attr.attr,
	&sensor_dev_attr_fan4_alarm.dev_attr.attr,
	&sensor_dev_attr_fan5_input.dev_attr.attr,
	&sensor_dev_attr_fan5_भाग.dev_attr.attr,
	&sensor_dev_attr_fan5_min.dev_attr.attr,
	&sensor_dev_attr_fan5_alarm.dev_attr.attr,
	&sensor_dev_attr_fan6_input.dev_attr.attr,
	&sensor_dev_attr_fan6_भाग.dev_attr.attr,
	&sensor_dev_attr_fan6_min.dev_attr.attr,
	&sensor_dev_attr_fan6_alarm.dev_attr.attr,
	&sensor_dev_attr_fan7_input.dev_attr.attr,
	&sensor_dev_attr_fan7_भाग.dev_attr.attr,
	&sensor_dev_attr_fan7_min.dev_attr.attr,
	&sensor_dev_attr_fan7_alarm.dev_attr.attr,
	&sensor_dev_attr_fan8_input.dev_attr.attr,
	&sensor_dev_attr_fan8_भाग.dev_attr.attr,
	&sensor_dev_attr_fan8_min.dev_attr.attr,
	&sensor_dev_attr_fan8_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_offset.dev_attr.attr,
	&sensor_dev_attr_temp2_offset.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_poपूर्णांक1_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_poपूर्णांक1_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp2_crit.dev_attr.attr,
	&dev_attr_temp1_crit_enable.attr,
	&dev_attr_temp2_crit_enable.attr,
	&dev_attr_cpu0_vid.attr,
	&dev_attr_vrm.attr,
	&dev_attr_alarms.attr,
	&dev_attr_alarm_mask.attr,
	&dev_attr_gpio.attr,
	&dev_attr_gpio_mask.attr,
	&dev_attr_pwm1.attr,
	&dev_attr_pwm2.attr,
	&dev_attr_pwm3.attr,
	&dev_attr_pwm1_enable.attr,
	&dev_attr_pwm2_enable.attr,
	&dev_attr_pwm3_enable.attr,
	&dev_attr_temp1_स्वतः_poपूर्णांक1_pwm.attr,
	&dev_attr_temp2_स्वतः_poपूर्णांक1_pwm.attr,
	&dev_attr_temp1_स्वतः_poपूर्णांक2_pwm.attr,
	&dev_attr_temp2_स्वतः_poपूर्णांक2_pwm.attr,
	&dev_attr_analog_out.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adm1026_group = अणु
	.attrs = adm1026_attributes,
पूर्ण;

अटल काष्ठा attribute *adm1026_attributes_temp3[] = अणु
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp3_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_offset.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_poपूर्णांक1_temp_hyst.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_temp3_crit.dev_attr.attr,
	&dev_attr_temp3_crit_enable.attr,
	&dev_attr_temp3_स्वतः_poपूर्णांक1_pwm.attr,
	&dev_attr_temp3_स्वतः_poपूर्णांक2_pwm.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adm1026_group_temp3 = अणु
	.attrs = adm1026_attributes_temp3,
पूर्ण;

अटल काष्ठा attribute *adm1026_attributes_in8_9[] = अणु
	&sensor_dev_attr_in8_input.dev_attr.attr,
	&sensor_dev_attr_in8_max.dev_attr.attr,
	&sensor_dev_attr_in8_min.dev_attr.attr,
	&sensor_dev_attr_in8_alarm.dev_attr.attr,
	&sensor_dev_attr_in9_input.dev_attr.attr,
	&sensor_dev_attr_in9_max.dev_attr.attr,
	&sensor_dev_attr_in9_min.dev_attr.attr,
	&sensor_dev_attr_in9_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adm1026_group_in8_9 = अणु
	.attrs = adm1026_attributes_in8_9,
पूर्ण;

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक adm1026_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक address = client->addr;
	पूर्णांक company, verstep;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		/* We need to be able to करो byte I/O */
		वापस -ENODEV;
	पूर्ण

	/* Now, we करो the reमुख्यing detection. */

	company = adm1026_पढ़ो_value(client, ADM1026_REG_COMPANY);
	verstep = adm1026_पढ़ो_value(client, ADM1026_REG_VERSTEP);

	dev_dbg(&adapter->dev,
		"Detecting device at %d,0x%02x with COMPANY: 0x%02x and VERSTEP: 0x%02x\n",
		i2c_adapter_id(client->adapter), client->addr,
		company, verstep);

	/* Determine the chip type. */
	dev_dbg(&adapter->dev, "Autodetecting device at %d,0x%02x...\n",
		i2c_adapter_id(adapter), address);
	अगर (company == ADM1026_COMPANY_ANALOG_DEV
	    && verstep == ADM1026_VERSTEP_ADM1026) अणु
		/* Analog Devices ADM1026 */
	पूर्ण अन्यथा अगर (company == ADM1026_COMPANY_ANALOG_DEV
		&& (verstep & 0xf0) == ADM1026_VERSTEP_GENERIC) अणु
		dev_err(&adapter->dev,
			"Unrecognized stepping 0x%02x. Defaulting to ADM1026.\n",
			verstep);
	पूर्ण अन्यथा अगर ((verstep & 0xf0) == ADM1026_VERSTEP_GENERIC) अणु
		dev_err(&adapter->dev,
			"Found version/stepping 0x%02x. Assuming generic ADM1026.\n",
			verstep);
	पूर्ण अन्यथा अणु
		dev_dbg(&adapter->dev, "Autodetection failed\n");
		/* Not an ADM1026... */
		वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, "adm1026", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल व्योम adm1026_prपूर्णांक_gpio(काष्ठा i2c_client *client)
अणु
	काष्ठा adm1026_data *data = i2c_get_clientdata(client);
	पूर्णांक i;

	dev_dbg(&client->dev, "GPIO config is:\n");
	क्रम (i = 0; i <= 7; ++i) अणु
		अगर (data->config2 & (1 << i)) अणु
			dev_dbg(&client->dev, "\t%sGP%s%d\n",
				data->gpio_config[i] & 0x02 ? "" : "!",
				data->gpio_config[i] & 0x01 ? "OUT" : "IN",
				i);
		पूर्ण अन्यथा अणु
			dev_dbg(&client->dev, "\tFAN%d\n", i);
		पूर्ण
	पूर्ण
	क्रम (i = 8; i <= 15; ++i) अणु
		dev_dbg(&client->dev, "\t%sGP%s%d\n",
			data->gpio_config[i] & 0x02 ? "" : "!",
			data->gpio_config[i] & 0x01 ? "OUT" : "IN",
			i);
	पूर्ण
	अगर (data->config3 & CFG3_GPIO16_ENABLE) अणु
		dev_dbg(&client->dev, "\t%sGP%s16\n",
			data->gpio_config[16] & 0x02 ? "" : "!",
			data->gpio_config[16] & 0x01 ? "OUT" : "IN");
	पूर्ण अन्यथा अणु
		/* GPIO16 is THERM */
		dev_dbg(&client->dev, "\tTHERM\n");
	पूर्ण
पूर्ण

अटल व्योम adm1026_fixup_gpio(काष्ठा i2c_client *client)
अणु
	काष्ठा adm1026_data *data = i2c_get_clientdata(client);
	पूर्णांक i;
	पूर्णांक value;

	/* Make the changes requested. */
	/*
	 * We may need to unlock/stop monitoring or soft-reset the
	 *    chip beक्रमe we can make changes.  This hasn't been
	 *    tested much.  FIXME
	 */

	/* Make outमाला_दो */
	क्रम (i = 0; i <= 16; ++i) अणु
		अगर (gpio_output[i] >= 0 && gpio_output[i] <= 16)
			data->gpio_config[gpio_output[i]] |= 0x01;
		/* अगर GPIO0-7 is output, it isn't a FAN tach */
		अगर (gpio_output[i] >= 0 && gpio_output[i] <= 7)
			data->config2 |= 1 << gpio_output[i];
	पूर्ण

	/* Input overrides output */
	क्रम (i = 0; i <= 16; ++i) अणु
		अगर (gpio_input[i] >= 0 && gpio_input[i] <= 16)
			data->gpio_config[gpio_input[i]] &= ~0x01;
		/* अगर GPIO0-7 is input, it isn't a FAN tach */
		अगर (gpio_input[i] >= 0 && gpio_input[i] <= 7)
			data->config2 |= 1 << gpio_input[i];
	पूर्ण

	/* Inverted */
	क्रम (i = 0; i <= 16; ++i) अणु
		अगर (gpio_inverted[i] >= 0 && gpio_inverted[i] <= 16)
			data->gpio_config[gpio_inverted[i]] &= ~0x02;
	पूर्ण

	/* Normal overrides inverted */
	क्रम (i = 0; i <= 16; ++i) अणु
		अगर (gpio_normal[i] >= 0 && gpio_normal[i] <= 16)
			data->gpio_config[gpio_normal[i]] |= 0x02;
	पूर्ण

	/* Fan overrides input and output */
	क्रम (i = 0; i <= 7; ++i) अणु
		अगर (gpio_fan[i] >= 0 && gpio_fan[i] <= 7)
			data->config2 &= ~(1 << gpio_fan[i]);
	पूर्ण

	/* Write new configs to रेजिस्टरs */
	adm1026_ग_लिखो_value(client, ADM1026_REG_CONFIG2, data->config2);
	data->config3 = (data->config3 & 0x3f)
			| ((data->gpio_config[16] & 0x03) << 6);
	adm1026_ग_लिखो_value(client, ADM1026_REG_CONFIG3, data->config3);
	क्रम (i = 15, value = 0; i >= 0; --i) अणु
		value <<= 2;
		value |= data->gpio_config[i] & 0x03;
		अगर ((i & 0x03) == 0) अणु
			adm1026_ग_लिखो_value(client,
					ADM1026_REG_GPIO_CFG_0_3 + i/4,
					value);
			value = 0;
		पूर्ण
	पूर्ण

	/* Prपूर्णांक the new config */
	adm1026_prपूर्णांक_gpio(client);
पूर्ण

अटल व्योम adm1026_init_client(काष्ठा i2c_client *client)
अणु
	पूर्णांक value, i;
	काष्ठा adm1026_data *data = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "Initializing device\n");
	/* Read chip config */
	data->config1 = adm1026_पढ़ो_value(client, ADM1026_REG_CONFIG1);
	data->config2 = adm1026_पढ़ो_value(client, ADM1026_REG_CONFIG2);
	data->config3 = adm1026_पढ़ो_value(client, ADM1026_REG_CONFIG3);

	/* Inक्रमm user of chip config */
	dev_dbg(&client->dev, "ADM1026_REG_CONFIG1 is: 0x%02x\n",
		data->config1);
	अगर ((data->config1 & CFG1_MONITOR) == 0) अणु
		dev_dbg(&client->dev,
			"Monitoring not currently enabled.\n");
	पूर्ण
	अगर (data->config1 & CFG1_INT_ENABLE) अणु
		dev_dbg(&client->dev,
			"SMBALERT interrupts are enabled.\n");
	पूर्ण
	अगर (data->config1 & CFG1_AIN8_9) अणु
		dev_dbg(&client->dev,
			"in8 and in9 enabled. temp3 disabled.\n");
	पूर्ण अन्यथा अणु
		dev_dbg(&client->dev,
			"temp3 enabled.  in8 and in9 disabled.\n");
	पूर्ण
	अगर (data->config1 & CFG1_THERM_HOT) अणु
		dev_dbg(&client->dev,
			"Automatic THERM, PWM, and temp limits enabled.\n");
	पूर्ण

	अगर (data->config3 & CFG3_GPIO16_ENABLE) अणु
		dev_dbg(&client->dev,
			"GPIO16 enabled.  THERM pin disabled.\n");
	पूर्ण अन्यथा अणु
		dev_dbg(&client->dev,
			"THERM pin enabled.  GPIO16 disabled.\n");
	पूर्ण
	अगर (data->config3 & CFG3_VREF_250)
		dev_dbg(&client->dev, "Vref is 2.50 Volts.\n");
	अन्यथा
		dev_dbg(&client->dev, "Vref is 1.82 Volts.\n");
	/* Read and pick apart the existing GPIO configuration */
	value = 0;
	क्रम (i = 0; i <= 15; ++i) अणु
		अगर ((i & 0x03) == 0) अणु
			value = adm1026_पढ़ो_value(client,
					ADM1026_REG_GPIO_CFG_0_3 + i / 4);
		पूर्ण
		data->gpio_config[i] = value & 0x03;
		value >>= 2;
	पूर्ण
	data->gpio_config[16] = (data->config3 >> 6) & 0x03;

	/* ... and then prपूर्णांक it */
	adm1026_prपूर्णांक_gpio(client);

	/*
	 * If the user asks us to reprogram the GPIO config, then
	 * करो it now.
	 */
	अगर (gpio_input[0] != -1 || gpio_output[0] != -1
		|| gpio_inverted[0] != -1 || gpio_normal[0] != -1
		|| gpio_fan[0] != -1) अणु
		adm1026_fixup_gpio(client);
	पूर्ण

	/*
	 * WE INTENTIONALLY make no changes to the limits,
	 *   offsets, pwms, fans and zones.  If they were
	 *   configured, we करोn't want to mess with them.
	 *   If they weren't, the शेष is 100% PWM, no
	 *   control and will suffice until 'sensors -s'
	 *   can be run by the user.  We DO set the शेष
	 *   value क्रम pwm1.स्वतः_pwm_min to its maximum
	 *   so that enabling स्वतःmatic pwm fan control
	 *   without first setting a value क्रम pwm1.स्वतः_pwm_min
	 *   will not result in potentially dangerous fan speed decrease.
	 */
	data->pwm1.स्वतः_pwm_min = 255;
	/* Start monitoring */
	value = adm1026_पढ़ो_value(client, ADM1026_REG_CONFIG1);
	/* Set MONITOR, clear पूर्णांकerrupt acknowledge and s/w reset */
	value = (value | CFG1_MONITOR) & (~CFG1_INT_CLEAR & ~CFG1_RESET);
	dev_dbg(&client->dev, "Setting CONFIG to: 0x%02x\n", value);
	data->config1 = value;
	adm1026_ग_लिखो_value(client, ADM1026_REG_CONFIG1, value);

	/* initialize fan_भाग[] to hardware शेषs */
	value = adm1026_पढ़ो_value(client, ADM1026_REG_FAN_DIV_0_3) |
		(adm1026_पढ़ो_value(client, ADM1026_REG_FAN_DIV_4_7) << 8);
	क्रम (i = 0; i <= 7; ++i) अणु
		data->fan_भाग[i] = DIV_FROM_REG(value & 0x03);
		value >>= 2;
	पूर्ण
पूर्ण

अटल पूर्णांक adm1026_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा adm1026_data *data;

	data = devm_kzalloc(dev, माप(काष्ठा adm1026_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	data->client = client;
	mutex_init(&data->update_lock);

	/* Set the VRM version */
	data->vrm = vid_which_vrm();

	/* Initialize the ADM1026 chip */
	adm1026_init_client(client);

	/* sysfs hooks */
	data->groups[0] = &adm1026_group;
	अगर (data->config1 & CFG1_AIN8_9)
		data->groups[1] = &adm1026_group_in8_9;
	अन्यथा
		data->groups[1] = &adm1026_group_temp3;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, data->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adm1026_id[] = अणु
	अणु "adm1026", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adm1026_id);

अटल काष्ठा i2c_driver adm1026_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "adm1026",
	पूर्ण,
	.probe_new	= adm1026_probe,
	.id_table	= adm1026_id,
	.detect		= adm1026_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(adm1026_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Philip Pokorny <ppokorny@penguincomputing.com>, "
	      "Justin Thiessen <jthiessen@penguincomputing.com>");
MODULE_DESCRIPTION("ADM1026 driver");
