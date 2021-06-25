<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * A hwmon driver क्रम the Analog Devices ADT7462
 * Copyright (C) 2008 IBM
 *
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/log2.h>
#समावेश <linux/slab.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x58, 0x5C, I2C_CLIENT_END पूर्ण;

/* ADT7462 रेजिस्टरs */
#घोषणा ADT7462_REG_DEVICE			0x3D
#घोषणा ADT7462_REG_VENDOR			0x3E
#घोषणा ADT7462_REG_REVISION			0x3F

#घोषणा ADT7462_REG_MIN_TEMP_BASE_ADDR		0x44
#घोषणा ADT7462_REG_MIN_TEMP_MAX_ADDR		0x47
#घोषणा ADT7462_REG_MAX_TEMP_BASE_ADDR		0x48
#घोषणा ADT7462_REG_MAX_TEMP_MAX_ADDR		0x4B
#घोषणा ADT7462_REG_TEMP_BASE_ADDR		0x88
#घोषणा ADT7462_REG_TEMP_MAX_ADDR		0x8F

#घोषणा ADT7462_REG_FAN_BASE_ADDR		0x98
#घोषणा ADT7462_REG_FAN_MAX_ADDR		0x9F
#घोषणा ADT7462_REG_FAN2_BASE_ADDR		0xA2
#घोषणा ADT7462_REG_FAN2_MAX_ADDR		0xA9
#घोषणा ADT7462_REG_FAN_ENABLE			0x07
#घोषणा ADT7462_REG_FAN_MIN_BASE_ADDR		0x78
#घोषणा ADT7462_REG_FAN_MIN_MAX_ADDR		0x7F

#घोषणा ADT7462_REG_CFG2			0x02
#घोषणा		ADT7462_FSPD_MASK		0x20

#घोषणा ADT7462_REG_PWM_BASE_ADDR		0xAA
#घोषणा ADT7462_REG_PWM_MAX_ADDR		0xAD
#घोषणा	ADT7462_REG_PWM_MIN_BASE_ADDR		0x28
#घोषणा ADT7462_REG_PWM_MIN_MAX_ADDR		0x2B
#घोषणा ADT7462_REG_PWM_MAX			0x2C
#घोषणा ADT7462_REG_PWM_TEMP_MIN_BASE_ADDR	0x5C
#घोषणा ADT7462_REG_PWM_TEMP_MIN_MAX_ADDR	0x5F
#घोषणा ADT7462_REG_PWM_TEMP_RANGE_BASE_ADDR	0x60
#घोषणा ADT7462_REG_PWM_TEMP_RANGE_MAX_ADDR	0x63
#घोषणा	ADT7462_PWM_HYST_MASK			0x0F
#घोषणा	ADT7462_PWM_RANGE_MASK			0xF0
#घोषणा		ADT7462_PWM_RANGE_SHIFT		4
#घोषणा ADT7462_REG_PWM_CFG_BASE_ADDR		0x21
#घोषणा ADT7462_REG_PWM_CFG_MAX_ADDR		0x24
#घोषणा		ADT7462_PWM_CHANNEL_MASK	0xE0
#घोषणा		ADT7462_PWM_CHANNEL_SHIFT	5

#घोषणा ADT7462_REG_PIN_CFG_BASE_ADDR		0x10
#घोषणा ADT7462_REG_PIN_CFG_MAX_ADDR		0x13
#घोषणा		ADT7462_PIN7_INPUT		0x01	/* cfg0 */
#घोषणा		ADT7462_DIODE3_INPUT		0x20
#घोषणा		ADT7462_DIODE1_INPUT		0x40
#घोषणा		ADT7462_VID_INPUT		0x80
#घोषणा		ADT7462_PIN22_INPUT		0x04	/* cfg1 */
#घोषणा		ADT7462_PIN21_INPUT		0x08
#घोषणा		ADT7462_PIN19_INPUT		0x10
#घोषणा		ADT7462_PIN15_INPUT		0x20
#घोषणा		ADT7462_PIN13_INPUT		0x40
#घोषणा		ADT7462_PIN8_INPUT		0x80
#घोषणा		ADT7462_PIN23_MASK		0x03
#घोषणा		ADT7462_PIN23_SHIFT		0
#घोषणा		ADT7462_PIN26_MASK		0x0C	/* cfg2 */
#घोषणा		ADT7462_PIN26_SHIFT		2
#घोषणा		ADT7462_PIN25_MASK		0x30
#घोषणा		ADT7462_PIN25_SHIFT		4
#घोषणा		ADT7462_PIN24_MASK		0xC0
#घोषणा		ADT7462_PIN24_SHIFT		6
#घोषणा		ADT7462_PIN26_VOLT_INPUT	0x08
#घोषणा		ADT7462_PIN25_VOLT_INPUT	0x20
#घोषणा		ADT7462_PIN28_SHIFT		4	/* cfg3 */
#घोषणा		ADT7462_PIN28_VOLT		0x5

#घोषणा ADT7462_REG_ALARM1			0xB8
#घोषणा	ADT7462_LT_ALARM			0x02
#घोषणा		ADT7462_R1T_ALARM		0x04
#घोषणा		ADT7462_R2T_ALARM		0x08
#घोषणा		ADT7462_R3T_ALARM		0x10
#घोषणा ADT7462_REG_ALARM2			0xBB
#घोषणा		ADT7462_V0_ALARM		0x01
#घोषणा		ADT7462_V1_ALARM		0x02
#घोषणा		ADT7462_V2_ALARM		0x04
#घोषणा		ADT7462_V3_ALARM		0x08
#घोषणा		ADT7462_V4_ALARM		0x10
#घोषणा		ADT7462_V5_ALARM		0x20
#घोषणा		ADT7462_V6_ALARM		0x40
#घोषणा		ADT7462_V7_ALARM		0x80
#घोषणा ADT7462_REG_ALARM3			0xBC
#घोषणा		ADT7462_V8_ALARM		0x08
#घोषणा		ADT7462_V9_ALARM		0x10
#घोषणा		ADT7462_V10_ALARM		0x20
#घोषणा		ADT7462_V11_ALARM		0x40
#घोषणा		ADT7462_V12_ALARM		0x80
#घोषणा ADT7462_REG_ALARM4			0xBD
#घोषणा		ADT7462_F0_ALARM		0x01
#घोषणा		ADT7462_F1_ALARM		0x02
#घोषणा		ADT7462_F2_ALARM		0x04
#घोषणा		ADT7462_F3_ALARM		0x08
#घोषणा		ADT7462_F4_ALARM		0x10
#घोषणा		ADT7462_F5_ALARM		0x20
#घोषणा		ADT7462_F6_ALARM		0x40
#घोषणा		ADT7462_F7_ALARM		0x80
#घोषणा ADT7462_ALARM1				0x0000
#घोषणा ADT7462_ALARM2				0x0100
#घोषणा ADT7462_ALARM3				0x0200
#घोषणा ADT7462_ALARM4				0x0300
#घोषणा ADT7462_ALARM_REG_SHIFT			8
#घोषणा ADT7462_ALARM_FLAG_MASK			0x0F

#घोषणा ADT7462_TEMP_COUNT		4
#घोषणा ADT7462_TEMP_REG(x)		(ADT7462_REG_TEMP_BASE_ADDR + ((x) * 2))
#घोषणा ADT7462_TEMP_MIN_REG(x)		(ADT7462_REG_MIN_TEMP_BASE_ADDR + (x))
#घोषणा ADT7462_TEMP_MAX_REG(x)		(ADT7462_REG_MAX_TEMP_BASE_ADDR + (x))
#घोषणा TEMP_FRAC_OFFSET		6

#घोषणा ADT7462_FAN_COUNT		8
#घोषणा ADT7462_REG_FAN_MIN(x)		(ADT7462_REG_FAN_MIN_BASE_ADDR + (x))

#घोषणा ADT7462_PWM_COUNT		4
#घोषणा ADT7462_REG_PWM(x)		(ADT7462_REG_PWM_BASE_ADDR + (x))
#घोषणा ADT7462_REG_PWM_MIN(x)		(ADT7462_REG_PWM_MIN_BASE_ADDR + (x))
#घोषणा ADT7462_REG_PWM_TMIN(x)		\
	(ADT7462_REG_PWM_TEMP_MIN_BASE_ADDR + (x))
#घोषणा ADT7462_REG_PWM_TRANGE(x)	\
	(ADT7462_REG_PWM_TEMP_RANGE_BASE_ADDR + (x))

#घोषणा ADT7462_PIN_CFG_REG_COUNT	4
#घोषणा ADT7462_REG_PIN_CFG(x)		(ADT7462_REG_PIN_CFG_BASE_ADDR + (x))
#घोषणा ADT7462_REG_PWM_CFG(x)		(ADT7462_REG_PWM_CFG_BASE_ADDR + (x))

#घोषणा ADT7462_ALARM_REG_COUNT		4

/*
 * The chip can measure 13 dअगरferent voltage sources:
 *
 * 1. +12V1 (pin 7)
 * 2. Vccp1/+2.5V/+1.8V/+1.5V (pin 23)
 * 3. +12V3 (pin 22)
 * 4. +5V (pin 21)
 * 5. +1.25V/+0.9V (pin 19)
 * 6. +2.5V/+1.8V (pin 15)
 * 7. +3.3v (pin 13)
 * 8. +12V2 (pin 8)
 * 9. Vbatt/FSB_Vtt (pin 26)
 * A. +3.3V/+1.2V1 (pin 25)
 * B. Vccp2/+2.5V/+1.8V/+1.5V (pin 24)
 * C. +1.5V ICH (only अगर BOTH pin 28/29 are set to +1.5V)
 * D. +1.5V 3GPIO (only अगर BOTH pin 28/29 are set to +1.5V)
 *
 * Each of these 13 has a factor to convert raw to voltage.  Even better,
 * the pins can be connected to other sensors (tach/gpio/hot/etc), which
 * makes the bookkeeping tricky.
 *
 * Some, but not all, of these voltages have low/high limits.
 */
#घोषणा ADT7462_VOLT_COUNT	13

#घोषणा ADT7462_VENDOR		0x41
#घोषणा ADT7462_DEVICE		0x62
/* datasheet only mentions a revision 4 */
#घोषणा ADT7462_REVISION	0x04

/* How often करो we reपढ़ो sensors values? (In jअगरfies) */
#घोषणा SENSOR_REFRESH_INTERVAL	(2 * HZ)

/* How often करो we reपढ़ो sensor limit values? (In jअगरfies) */
#घोषणा LIMIT_REFRESH_INTERVAL	(60 * HZ)

/* datasheet says to भागide this number by the fan पढ़ोing to get fan rpm */
#घोषणा FAN_PERIOD_TO_RPM(x)	((90000 * 60) / (x))
#घोषणा FAN_RPM_TO_PERIOD	FAN_PERIOD_TO_RPM
#घोषणा FAN_PERIOD_INVALID	65535
#घोषणा FAN_DATA_VALID(x)	((x) && (x) != FAN_PERIOD_INVALID)

#घोषणा MASK_AND_SHIFT(value, prefix)	\
	(((value) & prefix##_MASK) >> prefix##_SHIFT)

काष्ठा adt7462_data अणु
	काष्ठा i2c_client	*client;
	काष्ठा mutex		lock;
	अक्षर			sensors_valid;
	अक्षर			limits_valid;
	अचिन्हित दीर्घ		sensors_last_updated;	/* In jअगरfies */
	अचिन्हित दीर्घ		limits_last_updated;	/* In jअगरfies */

	u8			temp[ADT7462_TEMP_COUNT];
				/* bits 6-7 are quarter pieces of temp */
	u8			temp_frac[ADT7462_TEMP_COUNT];
	u8			temp_min[ADT7462_TEMP_COUNT];
	u8			temp_max[ADT7462_TEMP_COUNT];
	u16			fan[ADT7462_FAN_COUNT];
	u8			fan_enabled;
	u8			fan_min[ADT7462_FAN_COUNT];
	u8			cfg2;
	u8			pwm[ADT7462_PWM_COUNT];
	u8			pin_cfg[ADT7462_PIN_CFG_REG_COUNT];
	u8			voltages[ADT7462_VOLT_COUNT];
	u8			volt_max[ADT7462_VOLT_COUNT];
	u8			volt_min[ADT7462_VOLT_COUNT];
	u8			pwm_min[ADT7462_PWM_COUNT];
	u8			pwm_पंचांगin[ADT7462_PWM_COUNT];
	u8			pwm_trange[ADT7462_PWM_COUNT];
	u8			pwm_max;	/* only one per chip */
	u8			pwm_cfg[ADT7462_PWM_COUNT];
	u8			alarms[ADT7462_ALARM_REG_COUNT];
पूर्ण;

/*
 * 16-bit रेजिस्टरs on the ADT7462 are low-byte first.  The data sheet says
 * that the low byte must be पढ़ो beक्रमe the high byte.
 */
अटल अंतरभूत पूर्णांक adt7462_पढ़ो_word_data(काष्ठा i2c_client *client, u8 reg)
अणु
	u16 foo;
	foo = i2c_smbus_पढ़ो_byte_data(client, reg);
	foo |= ((u16)i2c_smbus_पढ़ो_byte_data(client, reg + 1) << 8);
	वापस foo;
पूर्ण

/* For some reason these रेजिस्टरs are not contiguous. */
अटल पूर्णांक ADT7462_REG_FAN(पूर्णांक fan)
अणु
	अगर (fan < 4)
		वापस ADT7462_REG_FAN_BASE_ADDR + (2 * fan);
	वापस ADT7462_REG_FAN2_BASE_ADDR + (2 * (fan - 4));
पूर्ण

/* Voltage रेजिस्टरs are scattered everywhere */
अटल पूर्णांक ADT7462_REG_VOLT_MAX(काष्ठा adt7462_data *data, पूर्णांक which)
अणु
	चयन (which) अणु
	हाल 0:
		अगर (!(data->pin_cfg[0] & ADT7462_PIN7_INPUT))
			वापस 0x7C;
		अवरोध;
	हाल 1:
		वापस 0x69;
	हाल 2:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN22_INPUT))
			वापस 0x7F;
		अवरोध;
	हाल 3:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN21_INPUT))
			वापस 0x7E;
		अवरोध;
	हाल 4:
		अगर (!(data->pin_cfg[0] & ADT7462_DIODE3_INPUT))
			वापस 0x4B;
		अवरोध;
	हाल 5:
		अगर (!(data->pin_cfg[0] & ADT7462_DIODE1_INPUT))
			वापस 0x49;
		अवरोध;
	हाल 6:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN13_INPUT))
			वापस 0x68;
		अवरोध;
	हाल 7:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN8_INPUT))
			वापस 0x7D;
		अवरोध;
	हाल 8:
		अगर (!(data->pin_cfg[2] & ADT7462_PIN26_VOLT_INPUT))
			वापस 0x6C;
		अवरोध;
	हाल 9:
		अगर (!(data->pin_cfg[2] & ADT7462_PIN25_VOLT_INPUT))
			वापस 0x6B;
		अवरोध;
	हाल 10:
		वापस 0x6A;
	हाल 11:
		अगर (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOLT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			वापस 0x50;
		अवरोध;
	हाल 12:
		अगर (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOLT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			वापस 0x4C;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ADT7462_REG_VOLT_MIN(काष्ठा adt7462_data *data, पूर्णांक which)
अणु
	चयन (which) अणु
	हाल 0:
		अगर (!(data->pin_cfg[0] & ADT7462_PIN7_INPUT))
			वापस 0x6D;
		अवरोध;
	हाल 1:
		वापस 0x72;
	हाल 2:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN22_INPUT))
			वापस 0x6F;
		अवरोध;
	हाल 3:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN21_INPUT))
			वापस 0x71;
		अवरोध;
	हाल 4:
		अगर (!(data->pin_cfg[0] & ADT7462_DIODE3_INPUT))
			वापस 0x47;
		अवरोध;
	हाल 5:
		अगर (!(data->pin_cfg[0] & ADT7462_DIODE1_INPUT))
			वापस 0x45;
		अवरोध;
	हाल 6:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN13_INPUT))
			वापस 0x70;
		अवरोध;
	हाल 7:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN8_INPUT))
			वापस 0x6E;
		अवरोध;
	हाल 8:
		अगर (!(data->pin_cfg[2] & ADT7462_PIN26_VOLT_INPUT))
			वापस 0x75;
		अवरोध;
	हाल 9:
		अगर (!(data->pin_cfg[2] & ADT7462_PIN25_VOLT_INPUT))
			वापस 0x74;
		अवरोध;
	हाल 10:
		वापस 0x73;
	हाल 11:
		अगर (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOLT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			वापस 0x76;
		अवरोध;
	हाल 12:
		अगर (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOLT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			वापस 0x77;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ADT7462_REG_VOLT(काष्ठा adt7462_data *data, पूर्णांक which)
अणु
	चयन (which) अणु
	हाल 0:
		अगर (!(data->pin_cfg[0] & ADT7462_PIN7_INPUT))
			वापस 0xA3;
		अवरोध;
	हाल 1:
		वापस 0x90;
	हाल 2:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN22_INPUT))
			वापस 0xA9;
		अवरोध;
	हाल 3:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN21_INPUT))
			वापस 0xA7;
		अवरोध;
	हाल 4:
		अगर (!(data->pin_cfg[0] & ADT7462_DIODE3_INPUT))
			वापस 0x8F;
		अवरोध;
	हाल 5:
		अगर (!(data->pin_cfg[0] & ADT7462_DIODE1_INPUT))
			वापस 0x8B;
		अवरोध;
	हाल 6:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN13_INPUT))
			वापस 0x96;
		अवरोध;
	हाल 7:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN8_INPUT))
			वापस 0xA5;
		अवरोध;
	हाल 8:
		अगर (!(data->pin_cfg[2] & ADT7462_PIN26_VOLT_INPUT))
			वापस 0x93;
		अवरोध;
	हाल 9:
		अगर (!(data->pin_cfg[2] & ADT7462_PIN25_VOLT_INPUT))
			वापस 0x92;
		अवरोध;
	हाल 10:
		वापस 0x91;
	हाल 11:
		अगर (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOLT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			वापस 0x94;
		अवरोध;
	हाल 12:
		अगर (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOLT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			वापस 0x95;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* Provide labels क्रम sysfs */
अटल स्थिर अक्षर *voltage_label(काष्ठा adt7462_data *data, पूर्णांक which)
अणु
	चयन (which) अणु
	हाल 0:
		अगर (!(data->pin_cfg[0] & ADT7462_PIN7_INPUT))
			वापस "+12V1";
		अवरोध;
	हाल 1:
		चयन (MASK_AND_SHIFT(data->pin_cfg[1], ADT7462_PIN23)) अणु
		हाल 0:
			वापस "Vccp1";
		हाल 1:
			वापस "+2.5V";
		हाल 2:
			वापस "+1.8V";
		हाल 3:
			वापस "+1.5V";
		पूर्ण
		fallthrough;
	हाल 2:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN22_INPUT))
			वापस "+12V3";
		अवरोध;
	हाल 3:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN21_INPUT))
			वापस "+5V";
		अवरोध;
	हाल 4:
		अगर (!(data->pin_cfg[0] & ADT7462_DIODE3_INPUT)) अणु
			अगर (data->pin_cfg[1] & ADT7462_PIN19_INPUT)
				वापस "+0.9V";
			वापस "+1.25V";
		पूर्ण
		अवरोध;
	हाल 5:
		अगर (!(data->pin_cfg[0] & ADT7462_DIODE1_INPUT)) अणु
			अगर (data->pin_cfg[1] & ADT7462_PIN19_INPUT)
				वापस "+1.8V";
			वापस "+2.5V";
		पूर्ण
		अवरोध;
	हाल 6:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN13_INPUT))
			वापस "+3.3V";
		अवरोध;
	हाल 7:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN8_INPUT))
			वापस "+12V2";
		अवरोध;
	हाल 8:
		चयन (MASK_AND_SHIFT(data->pin_cfg[2], ADT7462_PIN26)) अणु
		हाल 0:
			वापस "Vbatt";
		हाल 1:
			वापस "FSB_Vtt";
		पूर्ण
		अवरोध;
	हाल 9:
		चयन (MASK_AND_SHIFT(data->pin_cfg[2], ADT7462_PIN25)) अणु
		हाल 0:
			वापस "+3.3V";
		हाल 1:
			वापस "+1.2V1";
		पूर्ण
		अवरोध;
	हाल 10:
		चयन (MASK_AND_SHIFT(data->pin_cfg[2], ADT7462_PIN24)) अणु
		हाल 0:
			वापस "Vccp2";
		हाल 1:
			वापस "+2.5V";
		हाल 2:
			वापस "+1.8V";
		हाल 3:
			वापस "+1.5";
		पूर्ण
		fallthrough;
	हाल 11:
		अगर (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOLT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			वापस "+1.5V ICH";
		अवरोध;
	हाल 12:
		अगर (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOLT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			वापस "+1.5V 3GPIO";
		अवरोध;
	पूर्ण
	वापस "N/A";
पूर्ण

/* Multipliers are actually in uV, not mV. */
अटल पूर्णांक voltage_multiplier(काष्ठा adt7462_data *data, पूर्णांक which)
अणु
	चयन (which) अणु
	हाल 0:
		अगर (!(data->pin_cfg[0] & ADT7462_PIN7_INPUT))
			वापस 62500;
		अवरोध;
	हाल 1:
		चयन (MASK_AND_SHIFT(data->pin_cfg[1], ADT7462_PIN23)) अणु
		हाल 0:
			अगर (data->pin_cfg[0] & ADT7462_VID_INPUT)
				वापस 12500;
			वापस 6250;
		हाल 1:
			वापस 13000;
		हाल 2:
			वापस 9400;
		हाल 3:
			वापस 7800;
		पूर्ण
		fallthrough;
	हाल 2:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN22_INPUT))
			वापस 62500;
		अवरोध;
	हाल 3:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN21_INPUT))
			वापस 26000;
		अवरोध;
	हाल 4:
		अगर (!(data->pin_cfg[0] & ADT7462_DIODE3_INPUT)) अणु
			अगर (data->pin_cfg[1] & ADT7462_PIN19_INPUT)
				वापस 4690;
			वापस 6500;
		पूर्ण
		अवरोध;
	हाल 5:
		अगर (!(data->pin_cfg[0] & ADT7462_DIODE1_INPUT)) अणु
			अगर (data->pin_cfg[1] & ADT7462_PIN15_INPUT)
				वापस 9400;
			वापस 13000;
		पूर्ण
		अवरोध;
	हाल 6:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN13_INPUT))
			वापस 17200;
		अवरोध;
	हाल 7:
		अगर (!(data->pin_cfg[1] & ADT7462_PIN8_INPUT))
			वापस 62500;
		अवरोध;
	हाल 8:
		चयन (MASK_AND_SHIFT(data->pin_cfg[2], ADT7462_PIN26)) अणु
		हाल 0:
			वापस 15600;
		हाल 1:
			वापस 6250;
		पूर्ण
		अवरोध;
	हाल 9:
		चयन (MASK_AND_SHIFT(data->pin_cfg[2], ADT7462_PIN25)) अणु
		हाल 0:
			वापस 17200;
		हाल 1:
			वापस 6250;
		पूर्ण
		अवरोध;
	हाल 10:
		चयन (MASK_AND_SHIFT(data->pin_cfg[2], ADT7462_PIN24)) अणु
		हाल 0:
			वापस 6250;
		हाल 1:
			वापस 13000;
		हाल 2:
			वापस 9400;
		हाल 3:
			वापस 7800;
		पूर्ण
		fallthrough;
	हाल 11:
	हाल 12:
		अगर (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOLT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			वापस 7800;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक temp_enabled(काष्ठा adt7462_data *data, पूर्णांक which)
अणु
	चयन (which) अणु
	हाल 0:
	हाल 2:
		वापस 1;
	हाल 1:
		अगर (data->pin_cfg[0] & ADT7462_DIODE1_INPUT)
			वापस 1;
		अवरोध;
	हाल 3:
		अगर (data->pin_cfg[0] & ADT7462_DIODE3_INPUT)
			वापस 1;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *temp_label(काष्ठा adt7462_data *data, पूर्णांक which)
अणु
	चयन (which) अणु
	हाल 0:
		वापस "local";
	हाल 1:
		अगर (data->pin_cfg[0] & ADT7462_DIODE1_INPUT)
			वापस "remote1";
		अवरोध;
	हाल 2:
		वापस "remote2";
	हाल 3:
		अगर (data->pin_cfg[0] & ADT7462_DIODE3_INPUT)
			वापस "remote3";
		अवरोध;
	पूर्ण
	वापस "N/A";
पूर्ण

/* Map Trange रेजिस्टर values to mC */
#घोषणा NUM_TRANGE_VALUES	16
अटल स्थिर पूर्णांक trange_values[NUM_TRANGE_VALUES] = अणु
	2000,
	2500,
	3300,
	4000,
	5000,
	6700,
	8000,
	10000,
	13300,
	16000,
	20000,
	26700,
	32000,
	40000,
	53300,
	80000
पूर्ण;

अटल पूर्णांक find_trange_value(पूर्णांक trange)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_TRANGE_VALUES; i++)
		अगर (trange_values[i] == trange)
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल काष्ठा adt7462_data *adt7462_update_device(काष्ठा device *dev)
अणु
	काष्ठा adt7462_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ local_jअगरfies = jअगरfies;
	पूर्णांक i;

	mutex_lock(&data->lock);
	अगर (समय_beक्रमe(local_jअगरfies, data->sensors_last_updated +
		SENSOR_REFRESH_INTERVAL)
		&& data->sensors_valid)
		जाओ no_sensor_update;

	क्रम (i = 0; i < ADT7462_TEMP_COUNT; i++) अणु
		/*
		 * Reading the fractional रेजिस्टर locks the पूर्णांकegral
		 * रेजिस्टर until both have been पढ़ो.
		 */
		data->temp_frac[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7462_TEMP_REG(i));
		data->temp[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7462_TEMP_REG(i) + 1);
	पूर्ण

	क्रम (i = 0; i < ADT7462_FAN_COUNT; i++)
		data->fan[i] = adt7462_पढ़ो_word_data(client,
						ADT7462_REG_FAN(i));

	data->fan_enabled = i2c_smbus_पढ़ो_byte_data(client,
					ADT7462_REG_FAN_ENABLE);

	क्रम (i = 0; i < ADT7462_PWM_COUNT; i++)
		data->pwm[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7462_REG_PWM(i));

	क्रम (i = 0; i < ADT7462_PIN_CFG_REG_COUNT; i++)
		data->pin_cfg[i] = i2c_smbus_पढ़ो_byte_data(client,
				ADT7462_REG_PIN_CFG(i));

	क्रम (i = 0; i < ADT7462_VOLT_COUNT; i++) अणु
		पूर्णांक reg = ADT7462_REG_VOLT(data, i);
		अगर (!reg)
			data->voltages[i] = 0;
		अन्यथा
			data->voltages[i] = i2c_smbus_पढ़ो_byte_data(client,
								     reg);
	पूर्ण

	data->alarms[0] = i2c_smbus_पढ़ो_byte_data(client, ADT7462_REG_ALARM1);
	data->alarms[1] = i2c_smbus_पढ़ो_byte_data(client, ADT7462_REG_ALARM2);
	data->alarms[2] = i2c_smbus_पढ़ो_byte_data(client, ADT7462_REG_ALARM3);
	data->alarms[3] = i2c_smbus_पढ़ो_byte_data(client, ADT7462_REG_ALARM4);

	data->sensors_last_updated = local_jअगरfies;
	data->sensors_valid = 1;

no_sensor_update:
	अगर (समय_beक्रमe(local_jअगरfies, data->limits_last_updated +
		LIMIT_REFRESH_INTERVAL)
		&& data->limits_valid)
		जाओ out;

	क्रम (i = 0; i < ADT7462_TEMP_COUNT; i++) अणु
		data->temp_min[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7462_TEMP_MIN_REG(i));
		data->temp_max[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7462_TEMP_MAX_REG(i));
	पूर्ण

	क्रम (i = 0; i < ADT7462_FAN_COUNT; i++)
		data->fan_min[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7462_REG_FAN_MIN(i));

	क्रम (i = 0; i < ADT7462_VOLT_COUNT; i++) अणु
		पूर्णांक reg = ADT7462_REG_VOLT_MAX(data, i);
		data->volt_max[i] =
			(reg ? i2c_smbus_पढ़ो_byte_data(client, reg) : 0);

		reg = ADT7462_REG_VOLT_MIN(data, i);
		data->volt_min[i] =
			(reg ? i2c_smbus_पढ़ो_byte_data(client, reg) : 0);
	पूर्ण

	क्रम (i = 0; i < ADT7462_PWM_COUNT; i++) अणु
		data->pwm_min[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7462_REG_PWM_MIN(i));
		data->pwm_पंचांगin[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7462_REG_PWM_TMIN(i));
		data->pwm_trange[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7462_REG_PWM_TRANGE(i));
		data->pwm_cfg[i] = i2c_smbus_पढ़ो_byte_data(client,
						ADT7462_REG_PWM_CFG(i));
	पूर्ण

	data->pwm_max = i2c_smbus_पढ़ो_byte_data(client, ADT7462_REG_PWM_MAX);

	data->cfg2 = i2c_smbus_पढ़ो_byte_data(client, ADT7462_REG_CFG2);

	data->limits_last_updated = local_jअगरfies;
	data->limits_valid = 1;

out:
	mutex_unlock(&data->lock);
	वापस data;
पूर्ण

अटल sमाप_प्रकार temp_min_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);

	अगर (!temp_enabled(data, attr->index))
		वापस प्र_लिखो(buf, "0\n");

	वापस प्र_लिखो(buf, "%d\n", 1000 * (data->temp_min[attr->index] - 64));
पूर्ण

अटल sमाप_प्रकार temp_min_store(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp) || !temp_enabled(data, attr->index))
		वापस -EINVAL;

	temp = clamp_val(temp, -64000, 191000);
	temp = DIV_ROUND_CLOSEST(temp, 1000) + 64;

	mutex_lock(&data->lock);
	data->temp_min[attr->index] = temp;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7462_TEMP_MIN_REG(attr->index),
				  temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);

	अगर (!temp_enabled(data, attr->index))
		वापस प्र_लिखो(buf, "0\n");

	वापस प्र_लिखो(buf, "%d\n", 1000 * (data->temp_max[attr->index] - 64));
पूर्ण

अटल sमाप_प्रकार temp_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp) || !temp_enabled(data, attr->index))
		वापस -EINVAL;

	temp = clamp_val(temp, -64000, 191000);
	temp = DIV_ROUND_CLOSEST(temp, 1000) + 64;

	mutex_lock(&data->lock);
	data->temp_max[attr->index] = temp;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7462_TEMP_MAX_REG(attr->index),
				  temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);
	u8 frac = data->temp_frac[attr->index] >> TEMP_FRAC_OFFSET;

	अगर (!temp_enabled(data, attr->index))
		वापस प्र_लिखो(buf, "0\n");

	वापस प्र_लिखो(buf, "%d\n", 1000 * (data->temp[attr->index] - 64) +
				     250 * frac);
पूर्ण

अटल sमाप_प्रकार temp_label_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);

	वापस प्र_लिखो(buf, "%s\n", temp_label(data, attr->index));
पूर्ण

अटल sमाप_प्रकार volt_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);
	पूर्णांक x = voltage_multiplier(data, attr->index);

	x *= data->volt_max[attr->index];
	x /= 1000; /* convert from uV to mV */

	वापस प्र_लिखो(buf, "%d\n", x);
पूर्ण

अटल sमाप_प्रकार volt_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक x = voltage_multiplier(data, attr->index);
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp) || !x)
		वापस -EINVAL;

	temp = clamp_val(temp, 0, 255 * x / 1000);
	temp *= 1000; /* convert mV to uV */
	temp = DIV_ROUND_CLOSEST(temp, x);

	mutex_lock(&data->lock);
	data->volt_max[attr->index] = temp;
	i2c_smbus_ग_लिखो_byte_data(client,
				  ADT7462_REG_VOLT_MAX(data, attr->index),
				  temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार volt_min_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);
	पूर्णांक x = voltage_multiplier(data, attr->index);

	x *= data->volt_min[attr->index];
	x /= 1000; /* convert from uV to mV */

	वापस प्र_लिखो(buf, "%d\n", x);
पूर्ण

अटल sमाप_प्रकार volt_min_store(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक x = voltage_multiplier(data, attr->index);
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp) || !x)
		वापस -EINVAL;

	temp = clamp_val(temp, 0, 255 * x / 1000);
	temp *= 1000; /* convert mV to uV */
	temp = DIV_ROUND_CLOSEST(temp, x);

	mutex_lock(&data->lock);
	data->volt_min[attr->index] = temp;
	i2c_smbus_ग_लिखो_byte_data(client,
				  ADT7462_REG_VOLT_MIN(data, attr->index),
				  temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार voltage_show(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);
	पूर्णांक x = voltage_multiplier(data, attr->index);

	x *= data->voltages[attr->index];
	x /= 1000; /* convert from uV to mV */

	वापस प्र_लिखो(buf, "%d\n", x);
पूर्ण

अटल sमाप_प्रकार voltage_label_show(काष्ठा device *dev,
				  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);

	वापस प्र_लिखो(buf, "%s\n", voltage_label(data, attr->index));
पूर्ण

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);
	पूर्णांक reg = attr->index >> ADT7462_ALARM_REG_SHIFT;
	पूर्णांक mask = attr->index & ADT7462_ALARM_FLAG_MASK;

	अगर (data->alarms[reg] & mask)
		वापस प्र_लिखो(buf, "1\n");
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल पूर्णांक fan_enabled(काष्ठा adt7462_data *data, पूर्णांक fan)
अणु
	वापस data->fan_enabled & (1 << fan);
पूर्ण

अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);
	u16 temp;

	/* Only the MSB of the min fan period is stored... */
	temp = data->fan_min[attr->index];
	temp <<= 8;

	अगर (!fan_enabled(data, attr->index) ||
	    !FAN_DATA_VALID(temp))
		वापस प्र_लिखो(buf, "0\n");

	वापस प्र_लिखो(buf, "%d\n", FAN_PERIOD_TO_RPM(temp));
पूर्ण

अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp) || !temp ||
	    !fan_enabled(data, attr->index))
		वापस -EINVAL;

	temp = FAN_RPM_TO_PERIOD(temp);
	temp >>= 8;
	temp = clamp_val(temp, 1, 255);

	mutex_lock(&data->lock);
	data->fan_min[attr->index] = temp;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7462_REG_FAN_MIN(attr->index),
				  temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार fan_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);

	अगर (!fan_enabled(data, attr->index) ||
	    !FAN_DATA_VALID(data->fan[attr->index]))
		वापस प्र_लिखो(buf, "0\n");

	वापस प्र_लिखो(buf, "%d\n",
		       FAN_PERIOD_TO_RPM(data->fan[attr->index]));
पूर्ण

अटल sमाप_प्रकार क्रमce_pwm_max_show(काष्ठा device *dev,
				  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा adt7462_data *data = adt7462_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", (data->cfg2 & ADT7462_FSPD_MASK ? 1 : 0));
पूर्ण

अटल sमाप_प्रकार क्रमce_pwm_max_store(काष्ठा device *dev,
				   काष्ठा device_attribute *devattr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adt7462_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;
	u8 reg;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	mutex_lock(&data->lock);
	reg = i2c_smbus_पढ़ो_byte_data(client, ADT7462_REG_CFG2);
	अगर (temp)
		reg |= ADT7462_FSPD_MASK;
	अन्यथा
		reg &= ~ADT7462_FSPD_MASK;
	data->cfg2 = reg;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7462_REG_CFG2, reg);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->pwm[attr->index]);
पूर्ण

अटल sमाप_प्रकार pwm_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	temp = clamp_val(temp, 0, 255);

	mutex_lock(&data->lock);
	data->pwm[attr->index] = temp;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7462_REG_PWM(attr->index), temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_max_show(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा adt7462_data *data = adt7462_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->pwm_max);
पूर्ण

अटल sमाप_प्रकार pwm_max_store(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adt7462_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	temp = clamp_val(temp, 0, 255);

	mutex_lock(&data->lock);
	data->pwm_max = temp;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7462_REG_PWM_MAX, temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_min_show(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->pwm_min[attr->index]);
पूर्ण

अटल sमाप_प्रकार pwm_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	temp = clamp_val(temp, 0, 255);

	mutex_lock(&data->lock);
	data->pwm_min[attr->index] = temp;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7462_REG_PWM_MIN(attr->index),
				  temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_hyst_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", 1000 *
		      (data->pwm_trange[attr->index] & ADT7462_PWM_HYST_MASK));
पूर्ण

अटल sमाप_प्रकार pwm_hyst_store(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	temp = clamp_val(temp, 0, 15000);
	temp = DIV_ROUND_CLOSEST(temp, 1000);

	/* package things up */
	temp &= ADT7462_PWM_HYST_MASK;
	temp |= data->pwm_trange[attr->index] & ADT7462_PWM_RANGE_MASK;

	mutex_lock(&data->lock);
	data->pwm_trange[attr->index] = temp;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7462_REG_PWM_TRANGE(attr->index),
				  temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_पंचांगax_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);

	/* पंचांगax = पंचांगin + trange */
	पूर्णांक trange = trange_values[data->pwm_trange[attr->index] >>
				   ADT7462_PWM_RANGE_SHIFT];
	पूर्णांक पंचांगin = (data->pwm_पंचांगin[attr->index] - 64) * 1000;

	वापस प्र_लिखो(buf, "%d\n", पंचांगin + trange);
पूर्ण

अटल sमाप_प्रकार pwm_पंचांगax_store(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक temp;
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक पंचांगin, trange_value;
	दीर्घ trange;

	अगर (kम_से_दीर्घ(buf, 10, &trange))
		वापस -EINVAL;

	/* trange = पंचांगax - पंचांगin */
	पंचांगin = (data->pwm_पंचांगin[attr->index] - 64) * 1000;
	trange_value = find_trange_value(trange - पंचांगin);
	अगर (trange_value < 0)
		वापस trange_value;

	temp = trange_value << ADT7462_PWM_RANGE_SHIFT;
	temp |= data->pwm_trange[attr->index] & ADT7462_PWM_HYST_MASK;

	mutex_lock(&data->lock);
	data->pwm_trange[attr->index] = temp;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7462_REG_PWM_TRANGE(attr->index),
				  temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_पंचांगin_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", 1000 * (data->pwm_पंचांगin[attr->index] - 64));
पूर्ण

अटल sमाप_प्रकार pwm_पंचांगin_store(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	temp = clamp_val(temp, -64000, 191000);
	temp = DIV_ROUND_CLOSEST(temp, 1000) + 64;

	mutex_lock(&data->lock);
	data->pwm_पंचांगin[attr->index] = temp;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7462_REG_PWM_TMIN(attr->index),
				  temp);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);
	पूर्णांक cfg = data->pwm_cfg[attr->index] >> ADT7462_PWM_CHANNEL_SHIFT;

	चयन (cfg) अणु
	हाल 4: /* off */
		वापस प्र_लिखो(buf, "0\n");
	हाल 7: /* manual */
		वापस प्र_लिखो(buf, "1\n");
	शेष: /* स्वतःmatic */
		वापस प्र_लिखो(buf, "2\n");
	पूर्ण
पूर्ण

अटल व्योम set_pwm_channel(काष्ठा i2c_client *client,
			    काष्ठा adt7462_data *data,
			    पूर्णांक which,
			    पूर्णांक value)
अणु
	पूर्णांक temp = data->pwm_cfg[which] & ~ADT7462_PWM_CHANNEL_MASK;
	temp |= value << ADT7462_PWM_CHANNEL_SHIFT;

	mutex_lock(&data->lock);
	data->pwm_cfg[which] = temp;
	i2c_smbus_ग_लिखो_byte_data(client, ADT7462_REG_PWM_CFG(which), temp);
	mutex_unlock(&data->lock);
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_store(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	चयन (temp) अणु
	हाल 0: /* off */
		set_pwm_channel(client, data, attr->index, 4);
		वापस count;
	हाल 1: /* manual */
		set_pwm_channel(client, data, attr->index, 7);
		वापस count;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_temp_show(काष्ठा device *dev,
				  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = adt7462_update_device(dev);
	पूर्णांक channel = data->pwm_cfg[attr->index] >> ADT7462_PWM_CHANNEL_SHIFT;

	चयन (channel) अणु
	हाल 0: /* temp[1234] only */
	हाल 1:
	हाल 2:
	हाल 3:
		वापस प्र_लिखो(buf, "%d\n", (1 << channel));
	हाल 5: /* temp1 & temp4  */
		वापस प्र_लिखो(buf, "9\n");
	हाल 6:
		वापस प्र_लिखो(buf, "15\n");
	शेष:
		वापस प्र_लिखो(buf, "0\n");
	पूर्ण
पूर्ण

अटल पूर्णांक cvt_स्वतः_temp(पूर्णांक input)
अणु
	अगर (input == 0xF)
		वापस 6;
	अगर (input == 0x9)
		वापस 5;
	अगर (input < 1 || !is_घातer_of_2(input))
		वापस -EINVAL;
	वापस ilog2(input);
पूर्ण

अटल sमाप_प्रकार pwm_स्वतः_temp_store(काष्ठा device *dev,
				   काष्ठा device_attribute *devattr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adt7462_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ temp;

	अगर (kम_से_दीर्घ(buf, 10, &temp))
		वापस -EINVAL;

	temp = cvt_स्वतः_temp(temp);
	अगर (temp < 0)
		वापस temp;

	set_pwm_channel(client, data, attr->index, temp);

	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp_max, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp_max, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max, temp_max, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp4_max, temp_max, 3);

अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_min, temp_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_min, temp_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp4_min, temp_min, 3);

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_input, temp, 3);

अटल SENSOR_DEVICE_ATTR_RO(temp1_label, temp_label, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_label, temp_label, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_label, temp_label, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_label, temp_label, 3);

अटल SENSOR_DEVICE_ATTR_RO(temp1_alarm, alarm,
			     ADT7462_ALARM1 | ADT7462_LT_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(temp2_alarm, alarm,
			     ADT7462_ALARM1 | ADT7462_R1T_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(temp3_alarm, alarm,
			     ADT7462_ALARM1 | ADT7462_R2T_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(temp4_alarm, alarm,
			     ADT7462_ALARM1 | ADT7462_R3T_ALARM);

अटल SENSOR_DEVICE_ATTR_RW(in1_max, volt_max, 0);
अटल SENSOR_DEVICE_ATTR_RW(in2_max, volt_max, 1);
अटल SENSOR_DEVICE_ATTR_RW(in3_max, volt_max, 2);
अटल SENSOR_DEVICE_ATTR_RW(in4_max, volt_max, 3);
अटल SENSOR_DEVICE_ATTR_RW(in5_max, volt_max, 4);
अटल SENSOR_DEVICE_ATTR_RW(in6_max, volt_max, 5);
अटल SENSOR_DEVICE_ATTR_RW(in7_max, volt_max, 6);
अटल SENSOR_DEVICE_ATTR_RW(in8_max, volt_max, 7);
अटल SENSOR_DEVICE_ATTR_RW(in9_max, volt_max, 8);
अटल SENSOR_DEVICE_ATTR_RW(in10_max, volt_max, 9);
अटल SENSOR_DEVICE_ATTR_RW(in11_max, volt_max, 10);
अटल SENSOR_DEVICE_ATTR_RW(in12_max, volt_max, 11);
अटल SENSOR_DEVICE_ATTR_RW(in13_max, volt_max, 12);

अटल SENSOR_DEVICE_ATTR_RW(in1_min, volt_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(in2_min, volt_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(in3_min, volt_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(in4_min, volt_min, 3);
अटल SENSOR_DEVICE_ATTR_RW(in5_min, volt_min, 4);
अटल SENSOR_DEVICE_ATTR_RW(in6_min, volt_min, 5);
अटल SENSOR_DEVICE_ATTR_RW(in7_min, volt_min, 6);
अटल SENSOR_DEVICE_ATTR_RW(in8_min, volt_min, 7);
अटल SENSOR_DEVICE_ATTR_RW(in9_min, volt_min, 8);
अटल SENSOR_DEVICE_ATTR_RW(in10_min, volt_min, 9);
अटल SENSOR_DEVICE_ATTR_RW(in11_min, volt_min, 10);
अटल SENSOR_DEVICE_ATTR_RW(in12_min, volt_min, 11);
अटल SENSOR_DEVICE_ATTR_RW(in13_min, volt_min, 12);

अटल SENSOR_DEVICE_ATTR_RO(in1_input, voltage, 0);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, voltage, 1);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, voltage, 2);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, voltage, 3);
अटल SENSOR_DEVICE_ATTR_RO(in5_input, voltage, 4);
अटल SENSOR_DEVICE_ATTR_RO(in6_input, voltage, 5);
अटल SENSOR_DEVICE_ATTR_RO(in7_input, voltage, 6);
अटल SENSOR_DEVICE_ATTR_RO(in8_input, voltage, 7);
अटल SENSOR_DEVICE_ATTR_RO(in9_input, voltage, 8);
अटल SENSOR_DEVICE_ATTR_RO(in10_input, voltage, 9);
अटल SENSOR_DEVICE_ATTR_RO(in11_input, voltage, 10);
अटल SENSOR_DEVICE_ATTR_RO(in12_input, voltage, 11);
अटल SENSOR_DEVICE_ATTR_RO(in13_input, voltage, 12);

अटल SENSOR_DEVICE_ATTR_RO(in1_label, voltage_label, 0);
अटल SENSOR_DEVICE_ATTR_RO(in2_label, voltage_label, 1);
अटल SENSOR_DEVICE_ATTR_RO(in3_label, voltage_label, 2);
अटल SENSOR_DEVICE_ATTR_RO(in4_label, voltage_label, 3);
अटल SENSOR_DEVICE_ATTR_RO(in5_label, voltage_label, 4);
अटल SENSOR_DEVICE_ATTR_RO(in6_label, voltage_label, 5);
अटल SENSOR_DEVICE_ATTR_RO(in7_label, voltage_label, 6);
अटल SENSOR_DEVICE_ATTR_RO(in8_label, voltage_label, 7);
अटल SENSOR_DEVICE_ATTR_RO(in9_label, voltage_label, 8);
अटल SENSOR_DEVICE_ATTR_RO(in10_label, voltage_label, 9);
अटल SENSOR_DEVICE_ATTR_RO(in11_label, voltage_label, 10);
अटल SENSOR_DEVICE_ATTR_RO(in12_label, voltage_label, 11);
अटल SENSOR_DEVICE_ATTR_RO(in13_label, voltage_label, 12);

अटल SENSOR_DEVICE_ATTR_RO(in1_alarm, alarm,
			     ADT7462_ALARM2 | ADT7462_V0_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(in2_alarm, alarm,
			     ADT7462_ALARM2 | ADT7462_V7_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(in3_alarm, alarm,
			     ADT7462_ALARM2 | ADT7462_V2_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(in4_alarm, alarm,
			     ADT7462_ALARM2 | ADT7462_V6_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(in5_alarm, alarm,
			     ADT7462_ALARM2 | ADT7462_V5_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(in6_alarm, alarm,
			     ADT7462_ALARM2 | ADT7462_V4_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(in7_alarm, alarm,
			     ADT7462_ALARM2 | ADT7462_V3_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(in8_alarm, alarm,
			     ADT7462_ALARM2 | ADT7462_V1_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(in9_alarm, alarm,
			     ADT7462_ALARM3 | ADT7462_V10_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(in10_alarm, alarm,
			     ADT7462_ALARM3 | ADT7462_V9_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(in11_alarm, alarm,
			     ADT7462_ALARM3 | ADT7462_V8_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(in12_alarm, alarm,
			     ADT7462_ALARM3 | ADT7462_V11_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(in13_alarm, alarm,
			     ADT7462_ALARM3 | ADT7462_V12_ALARM);

अटल SENSOR_DEVICE_ATTR_RW(fan1_min, fan_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_min, fan_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan3_min, fan_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(fan4_min, fan_min, 3);
अटल SENSOR_DEVICE_ATTR_RW(fan5_min, fan_min, 4);
अटल SENSOR_DEVICE_ATTR_RW(fan6_min, fan_min, 5);
अटल SENSOR_DEVICE_ATTR_RW(fan7_min, fan_min, 6);
अटल SENSOR_DEVICE_ATTR_RW(fan8_min, fan_min, 7);

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan3_input, fan, 2);
अटल SENSOR_DEVICE_ATTR_RO(fan4_input, fan, 3);
अटल SENSOR_DEVICE_ATTR_RO(fan5_input, fan, 4);
अटल SENSOR_DEVICE_ATTR_RO(fan6_input, fan, 5);
अटल SENSOR_DEVICE_ATTR_RO(fan7_input, fan, 6);
अटल SENSOR_DEVICE_ATTR_RO(fan8_input, fan, 7);

अटल SENSOR_DEVICE_ATTR_RO(fan1_alarm, alarm,
			     ADT7462_ALARM4 | ADT7462_F0_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(fan2_alarm, alarm,
			     ADT7462_ALARM4 | ADT7462_F1_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(fan3_alarm, alarm,
			     ADT7462_ALARM4 | ADT7462_F2_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(fan4_alarm, alarm,
			     ADT7462_ALARM4 | ADT7462_F3_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(fan5_alarm, alarm,
			     ADT7462_ALARM4 | ADT7462_F4_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(fan6_alarm, alarm,
			     ADT7462_ALARM4 | ADT7462_F5_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(fan7_alarm, alarm,
			     ADT7462_ALARM4 | ADT7462_F6_ALARM);
अटल SENSOR_DEVICE_ATTR_RO(fan8_alarm, alarm,
			     ADT7462_ALARM4 | ADT7462_F7_ALARM);

अटल SENSOR_DEVICE_ATTR_RW(क्रमce_pwm_max, क्रमce_pwm_max, 0);

अटल SENSOR_DEVICE_ATTR_RW(pwm1, pwm, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2, pwm, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3, pwm, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm4, pwm, 3);

अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_poपूर्णांक1_pwm, pwm_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_स्वतः_poपूर्णांक1_pwm, pwm_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_स्वतः_poपूर्णांक1_pwm, pwm_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm4_स्वतः_poपूर्णांक1_pwm, pwm_min, 3);

अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_poपूर्णांक2_pwm, pwm_max, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_स्वतः_poपूर्णांक2_pwm, pwm_max, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_स्वतः_poपूर्णांक2_pwm, pwm_max, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm4_स्वतः_poपूर्णांक2_pwm, pwm_max, 3);

अटल SENSOR_DEVICE_ATTR_RW(temp1_स्वतः_poपूर्णांक1_hyst, pwm_hyst, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_स्वतः_poपूर्णांक1_hyst, pwm_hyst, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_स्वतः_poपूर्णांक1_hyst, pwm_hyst, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp4_स्वतः_poपूर्णांक1_hyst, pwm_hyst, 3);

अटल SENSOR_DEVICE_ATTR_RW(temp1_स्वतः_poपूर्णांक2_hyst, pwm_hyst, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_स्वतः_poपूर्णांक2_hyst, pwm_hyst, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_स्वतः_poपूर्णांक2_hyst, pwm_hyst, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp4_स्वतः_poपूर्णांक2_hyst, pwm_hyst, 3);

अटल SENSOR_DEVICE_ATTR_RW(temp1_स्वतः_poपूर्णांक1_temp, pwm_पंचांगin, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_स्वतः_poपूर्णांक1_temp, pwm_पंचांगin, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_स्वतः_poपूर्णांक1_temp, pwm_पंचांगin, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp4_स्वतः_poपूर्णांक1_temp, pwm_पंचांगin, 3);

अटल SENSOR_DEVICE_ATTR_RW(temp1_स्वतः_poपूर्णांक2_temp, pwm_पंचांगax, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_स्वतः_poपूर्णांक2_temp, pwm_पंचांगax, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_स्वतः_poपूर्णांक2_temp, pwm_पंचांगax, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp4_स्वतः_poपूर्णांक2_temp, pwm_पंचांगax, 3);

अटल SENSOR_DEVICE_ATTR_RW(pwm1_enable, pwm_स्वतः, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_enable, pwm_स्वतः, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_enable, pwm_स्वतः, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm4_enable, pwm_स्वतः, 3);

अटल SENSOR_DEVICE_ATTR_RW(pwm1_स्वतः_channels_temp, pwm_स्वतः_temp, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_स्वतः_channels_temp, pwm_स्वतः_temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_स्वतः_channels_temp, pwm_स्वतः_temp, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm4_स्वतः_channels_temp, pwm_स्वतः_temp, 3);

अटल काष्ठा attribute *adt7462_attrs[] = अणु
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp4_max.dev_attr.attr,

	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp4_min.dev_attr.attr,

	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp4_input.dev_attr.attr,

	&sensor_dev_attr_temp1_label.dev_attr.attr,
	&sensor_dev_attr_temp2_label.dev_attr.attr,
	&sensor_dev_attr_temp3_label.dev_attr.attr,
	&sensor_dev_attr_temp4_label.dev_attr.attr,

	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_alarm.dev_attr.attr,
	&sensor_dev_attr_temp4_alarm.dev_attr.attr,

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

	&sensor_dev_attr_in1_label.dev_attr.attr,
	&sensor_dev_attr_in2_label.dev_attr.attr,
	&sensor_dev_attr_in3_label.dev_attr.attr,
	&sensor_dev_attr_in4_label.dev_attr.attr,
	&sensor_dev_attr_in5_label.dev_attr.attr,
	&sensor_dev_attr_in6_label.dev_attr.attr,
	&sensor_dev_attr_in7_label.dev_attr.attr,
	&sensor_dev_attr_in8_label.dev_attr.attr,
	&sensor_dev_attr_in9_label.dev_attr.attr,
	&sensor_dev_attr_in10_label.dev_attr.attr,
	&sensor_dev_attr_in11_label.dev_attr.attr,
	&sensor_dev_attr_in12_label.dev_attr.attr,
	&sensor_dev_attr_in13_label.dev_attr.attr,

	&sensor_dev_attr_in1_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,
	&sensor_dev_attr_in5_alarm.dev_attr.attr,
	&sensor_dev_attr_in6_alarm.dev_attr.attr,
	&sensor_dev_attr_in7_alarm.dev_attr.attr,
	&sensor_dev_attr_in8_alarm.dev_attr.attr,
	&sensor_dev_attr_in9_alarm.dev_attr.attr,
	&sensor_dev_attr_in10_alarm.dev_attr.attr,
	&sensor_dev_attr_in11_alarm.dev_attr.attr,
	&sensor_dev_attr_in12_alarm.dev_attr.attr,
	&sensor_dev_attr_in13_alarm.dev_attr.attr,

	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan3_min.dev_attr.attr,
	&sensor_dev_attr_fan4_min.dev_attr.attr,
	&sensor_dev_attr_fan5_min.dev_attr.attr,
	&sensor_dev_attr_fan6_min.dev_attr.attr,
	&sensor_dev_attr_fan7_min.dev_attr.attr,
	&sensor_dev_attr_fan8_min.dev_attr.attr,

	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan4_input.dev_attr.attr,
	&sensor_dev_attr_fan5_input.dev_attr.attr,
	&sensor_dev_attr_fan6_input.dev_attr.attr,
	&sensor_dev_attr_fan7_input.dev_attr.attr,
	&sensor_dev_attr_fan8_input.dev_attr.attr,

	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_fan3_alarm.dev_attr.attr,
	&sensor_dev_attr_fan4_alarm.dev_attr.attr,
	&sensor_dev_attr_fan5_alarm.dev_attr.attr,
	&sensor_dev_attr_fan6_alarm.dev_attr.attr,
	&sensor_dev_attr_fan7_alarm.dev_attr.attr,
	&sensor_dev_attr_fan8_alarm.dev_attr.attr,

	&sensor_dev_attr_क्रमce_pwm_max.dev_attr.attr,
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&sensor_dev_attr_pwm3.dev_attr.attr,
	&sensor_dev_attr_pwm4.dev_attr.attr,

	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm4_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,

	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm4_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,

	&sensor_dev_attr_temp1_स्वतः_poपूर्णांक1_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_poपूर्णांक1_hyst.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_poपूर्णांक1_hyst.dev_attr.attr,
	&sensor_dev_attr_temp4_स्वतः_poपूर्णांक1_hyst.dev_attr.attr,

	&sensor_dev_attr_temp1_स्वतः_poपूर्णांक2_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_poपूर्णांक2_hyst.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_poपूर्णांक2_hyst.dev_attr.attr,
	&sensor_dev_attr_temp4_स्वतः_poपूर्णांक2_hyst.dev_attr.attr,

	&sensor_dev_attr_temp1_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_temp4_स्वतः_poपूर्णांक1_temp.dev_attr.attr,

	&sensor_dev_attr_temp1_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_temp4_स्वतः_poपूर्णांक2_temp.dev_attr.attr,

	&sensor_dev_attr_pwm1_enable.dev_attr.attr,
	&sensor_dev_attr_pwm2_enable.dev_attr.attr,
	&sensor_dev_attr_pwm3_enable.dev_attr.attr,
	&sensor_dev_attr_pwm4_enable.dev_attr.attr,

	&sensor_dev_attr_pwm1_स्वतः_channels_temp.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_channels_temp.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_channels_temp.dev_attr.attr,
	&sensor_dev_attr_pwm4_स्वतः_channels_temp.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(adt7462);

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक adt7462_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक venकरोr, device, revision;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	venकरोr = i2c_smbus_पढ़ो_byte_data(client, ADT7462_REG_VENDOR);
	अगर (venकरोr != ADT7462_VENDOR)
		वापस -ENODEV;

	device = i2c_smbus_पढ़ो_byte_data(client, ADT7462_REG_DEVICE);
	अगर (device != ADT7462_DEVICE)
		वापस -ENODEV;

	revision = i2c_smbus_पढ़ो_byte_data(client, ADT7462_REG_REVISION);
	अगर (revision != ADT7462_REVISION)
		वापस -ENODEV;

	strlcpy(info->type, "adt7462", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक adt7462_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा adt7462_data *data;
	काष्ठा device *hwmon_dev;

	data = devm_kzalloc(dev, माप(काष्ठा adt7462_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->lock);

	dev_info(&client->dev, "%s chip found\n", client->name);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data,
							   adt7462_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adt7462_id[] = अणु
	अणु "adt7462", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adt7462_id);

अटल काष्ठा i2c_driver adt7462_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "adt7462",
	पूर्ण,
	.probe_new	= adt7462_probe,
	.id_table	= adt7462_id,
	.detect		= adt7462_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(adt7462_driver);

MODULE_AUTHOR("Darrick J. Wong <darrick.wong@oracle.com>");
MODULE_DESCRIPTION("ADT7462 driver");
MODULE_LICENSE("GPL");
