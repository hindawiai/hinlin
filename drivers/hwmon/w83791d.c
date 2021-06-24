<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * w83791d.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *	       monitoring
 *
 * Copyright (C) 2006-2007 Charles Spirakis <bezaur@gmail.com>
 */

/*
 * Supports following chips:
 *
 * Chip		#vin	#fanin	#pwm	#temp	wchipid	vendid	i2c	ISA
 * w83791d	10	5	5	3	0x71	0x5ca3	yes	no
 *
 * The w83791d chip appears to be part way between the 83781d and the
 * 83792d. Thus, this file is derived from both the w83792d.c and
 * w83781d.c files.
 *
 * The w83791g chip is the same as the w83791d but lead-मुक्त.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/jअगरfies.h>

#घोषणा NUMBER_OF_VIN		10
#घोषणा NUMBER_OF_FANIN		5
#घोषणा NUMBER_OF_TEMPIN	3
#घोषणा NUMBER_OF_PWM		5

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2c, 0x2d, 0x2e, 0x2f,
						I2C_CLIENT_END पूर्ण;

/* Insmod parameters */

अटल अचिन्हित लघु क्रमce_subclients[4];
module_param_array(क्रमce_subclients, लघु, शून्य, 0);
MODULE_PARM_DESC(क्रमce_subclients,
		 "List of subclient addresses: {bus, clientaddr, subclientaddr1, subclientaddr2}");

अटल bool reset;
module_param(reset, bool, 0);
MODULE_PARM_DESC(reset, "Set to one to force a hardware chip reset");

अटल bool init;
module_param(init, bool, 0);
MODULE_PARM_DESC(init, "Set to one to force extra software initialization");

/* The W83791D रेजिस्टरs */
अटल स्थिर u8 W83791D_REG_IN[NUMBER_OF_VIN] = अणु
	0x20,			/* VCOREA in DataSheet */
	0x21,			/* VINR0 in DataSheet */
	0x22,			/* +3.3VIN in DataSheet */
	0x23,			/* VDD5V in DataSheet */
	0x24,			/* +12VIN in DataSheet */
	0x25,			/* -12VIN in DataSheet */
	0x26,			/* -5VIN in DataSheet */
	0xB0,			/* 5VSB in DataSheet */
	0xB1,			/* VBAT in DataSheet */
	0xB2			/* VINR1 in DataSheet */
पूर्ण;

अटल स्थिर u8 W83791D_REG_IN_MAX[NUMBER_OF_VIN] = अणु
	0x2B,			/* VCOREA High Limit in DataSheet */
	0x2D,			/* VINR0 High Limit in DataSheet */
	0x2F,			/* +3.3VIN High Limit in DataSheet */
	0x31,			/* VDD5V High Limit in DataSheet */
	0x33,			/* +12VIN High Limit in DataSheet */
	0x35,			/* -12VIN High Limit in DataSheet */
	0x37,			/* -5VIN High Limit in DataSheet */
	0xB4,			/* 5VSB High Limit in DataSheet */
	0xB6,			/* VBAT High Limit in DataSheet */
	0xB8			/* VINR1 High Limit in DataSheet */
पूर्ण;
अटल स्थिर u8 W83791D_REG_IN_MIN[NUMBER_OF_VIN] = अणु
	0x2C,			/* VCOREA Low Limit in DataSheet */
	0x2E,			/* VINR0 Low Limit in DataSheet */
	0x30,			/* +3.3VIN Low Limit in DataSheet */
	0x32,			/* VDD5V Low Limit in DataSheet */
	0x34,			/* +12VIN Low Limit in DataSheet */
	0x36,			/* -12VIN Low Limit in DataSheet */
	0x38,			/* -5VIN Low Limit in DataSheet */
	0xB5,			/* 5VSB Low Limit in DataSheet */
	0xB7,			/* VBAT Low Limit in DataSheet */
	0xB9			/* VINR1 Low Limit in DataSheet */
पूर्ण;
अटल स्थिर u8 W83791D_REG_FAN[NUMBER_OF_FANIN] = अणु
	0x28,			/* FAN 1 Count in DataSheet */
	0x29,			/* FAN 2 Count in DataSheet */
	0x2A,			/* FAN 3 Count in DataSheet */
	0xBA,			/* FAN 4 Count in DataSheet */
	0xBB,			/* FAN 5 Count in DataSheet */
पूर्ण;
अटल स्थिर u8 W83791D_REG_FAN_MIN[NUMBER_OF_FANIN] = अणु
	0x3B,			/* FAN 1 Count Low Limit in DataSheet */
	0x3C,			/* FAN 2 Count Low Limit in DataSheet */
	0x3D,			/* FAN 3 Count Low Limit in DataSheet */
	0xBC,			/* FAN 4 Count Low Limit in DataSheet */
	0xBD,			/* FAN 5 Count Low Limit in DataSheet */
पूर्ण;

अटल स्थिर u8 W83791D_REG_PWM[NUMBER_OF_PWM] = अणु
	0x81,			/* PWM 1 duty cycle रेजिस्टर in DataSheet */
	0x83,			/* PWM 2 duty cycle रेजिस्टर in DataSheet */
	0x94,			/* PWM 3 duty cycle रेजिस्टर in DataSheet */
	0xA0,			/* PWM 4 duty cycle रेजिस्टर in DataSheet */
	0xA1,			/* PWM 5 duty cycle रेजिस्टर in DataSheet */
पूर्ण;

अटल स्थिर u8 W83791D_REG_TEMP_TARGET[3] = अणु
	0x85,			/* PWM 1 target temperature क्रम temp 1 */
	0x86,			/* PWM 2 target temperature क्रम temp 2 */
	0x96,			/* PWM 3 target temperature क्रम temp 3 */
पूर्ण;

अटल स्थिर u8 W83791D_REG_TEMP_TOL[2] = अणु
	0x87,			/* PWM 1/2 temperature tolerance */
	0x97,			/* PWM 3 temperature tolerance */
पूर्ण;

अटल स्थिर u8 W83791D_REG_FAN_CFG[2] = अणु
	0x84,			/* FAN 1/2 configuration */
	0x95,			/* FAN 3 configuration */
पूर्ण;

अटल स्थिर u8 W83791D_REG_FAN_DIV[3] = अणु
	0x47,			/* contains FAN1 and FAN2 Divisor */
	0x4b,			/* contains FAN3 Divisor */
	0x5C,			/* contains FAN4 and FAN5 Divisor */
पूर्ण;

#घोषणा W83791D_REG_BANK		0x4E
#घोषणा W83791D_REG_TEMP2_CONFIG	0xC2
#घोषणा W83791D_REG_TEMP3_CONFIG	0xCA

अटल स्थिर u8 W83791D_REG_TEMP1[3] = अणु
	0x27,			/* TEMP 1 in DataSheet */
	0x39,			/* TEMP 1 Over in DataSheet */
	0x3A,			/* TEMP 1 Hyst in DataSheet */
पूर्ण;

अटल स्थिर u8 W83791D_REG_TEMP_ADD[2][6] = अणु
	अणु0xC0,			/* TEMP 2 in DataSheet */
	 0xC1,			/* TEMP 2(0.5 deg) in DataSheet */
	 0xC5,			/* TEMP 2 Over High part in DataSheet */
	 0xC6,			/* TEMP 2 Over Low part in DataSheet */
	 0xC3,			/* TEMP 2 Thyst High part in DataSheet */
	 0xC4पूर्ण,			/* TEMP 2 Thyst Low part in DataSheet */
	अणु0xC8,			/* TEMP 3 in DataSheet */
	 0xC9,			/* TEMP 3(0.5 deg) in DataSheet */
	 0xCD,			/* TEMP 3 Over High part in DataSheet */
	 0xCE,			/* TEMP 3 Over Low part in DataSheet */
	 0xCB,			/* TEMP 3 Thyst High part in DataSheet */
	 0xCCपूर्ण			/* TEMP 3 Thyst Low part in DataSheet */
पूर्ण;

#घोषणा W83791D_REG_BEEP_CONFIG		0x4D

अटल स्थिर u8 W83791D_REG_BEEP_CTRL[3] = अणु
	0x56,			/* BEEP Control Register 1 */
	0x57,			/* BEEP Control Register 2 */
	0xA3,			/* BEEP Control Register 3 */
पूर्ण;

#घोषणा W83791D_REG_GPIO		0x15
#घोषणा W83791D_REG_CONFIG		0x40
#घोषणा W83791D_REG_VID_FANDIV		0x47
#घोषणा W83791D_REG_DID_VID4		0x49
#घोषणा W83791D_REG_WCHIPID		0x58
#घोषणा W83791D_REG_CHIPMAN		0x4F
#घोषणा W83791D_REG_PIN			0x4B
#घोषणा W83791D_REG_I2C_SUBADDR		0x4A

#घोषणा W83791D_REG_ALARM1 0xA9	/* realसमय status रेजिस्टर1 */
#घोषणा W83791D_REG_ALARM2 0xAA	/* realसमय status रेजिस्टर2 */
#घोषणा W83791D_REG_ALARM3 0xAB	/* realसमय status रेजिस्टर3 */

#घोषणा W83791D_REG_VBAT		0x5D
#घोषणा W83791D_REG_I2C_ADDR		0x48

/*
 * The SMBus locks itself. The Winbond W83791D has a bank select रेजिस्टर
 * (index 0x4e), but the driver only accesses रेजिस्टरs in bank 0. Since
 * we करोn't switch banks, we don't need any special code to handle
 * locking access between bank चयनes
 */
अटल अंतरभूत पूर्णांक w83791d_पढ़ो(काष्ठा i2c_client *client, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल अंतरभूत पूर्णांक w83791d_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 value)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

/*
 * The analog voltage inमाला_दो have 16mV LSB. Since the sysfs output is
 * in mV as would be measured on the chip input pin, need to just
 * multiply/भागide by 16 to translate from/to रेजिस्टर values.
 */
#घोषणा IN_TO_REG(val)		(clamp_val((((val) + 8) / 16), 0, 255))
#घोषणा IN_FROM_REG(val)	((val) * 16)

अटल u8 fan_to_reg(दीर्घ rpm, पूर्णांक भाग)
अणु
	अगर (rpm == 0)
		वापस 255;
	rpm = clamp_val(rpm, 1, 1000000);
	वापस clamp_val((1350000 + rpm * भाग / 2) / (rpm * भाग), 1, 254);
पूर्ण

#घोषणा FAN_FROM_REG(val, भाग)	((val) == 0 ? -1 : \
				((val) == 255 ? 0 : \
					1350000 / ((val) * (भाग))))

/* क्रम temp1 which is 8-bit resolution, LSB = 1 degree Celsius */
#घोषणा TEMP1_FROM_REG(val)	((val) * 1000)
#घोषणा TEMP1_TO_REG(val)	((val) <= -128000 ? -128 : \
				 (val) >= 127000 ? 127 : \
				 (val) < 0 ? ((val) - 500) / 1000 : \
				 ((val) + 500) / 1000)

/*
 * क्रम temp2 and temp3 which are 9-bit resolution, LSB = 0.5 degree Celsius
 * Assumes the top 8 bits are the पूर्णांकegral amount and the bottom 8 bits
 * are the fractional amount. Since we only have 0.5 degree resolution,
 * the bottom 7 bits will always be zero
 */
#घोषणा TEMP23_FROM_REG(val)	((val) / 128 * 500)
#घोषणा TEMP23_TO_REG(val)	(DIV_ROUND_CLOSEST(clamp_val((val), -128000, \
						   127500), 500) * 128)

/* क्रम thermal cruise target temp, 7-bits, LSB = 1 degree Celsius */
#घोषणा TARGET_TEMP_TO_REG(val)	DIV_ROUND_CLOSEST(clamp_val((val), 0, 127000), \
						  1000)

/* क्रम thermal cruise temp tolerance, 4-bits, LSB = 1 degree Celsius */
#घोषणा TOL_TEMP_TO_REG(val)	DIV_ROUND_CLOSEST(clamp_val((val), 0, 15000), \
						  1000)

#घोषणा BEEP_MASK_TO_REG(val)		((val) & 0xffffff)
#घोषणा BEEP_MASK_FROM_REG(val)		((val) & 0xffffff)

#घोषणा DIV_FROM_REG(val)		(1 << (val))

अटल u8 भाग_प्रकारo_reg(पूर्णांक nr, दीर्घ val)
अणु
	पूर्णांक i;

	/* fan भागisors max out at 128 */
	val = clamp_val(val, 1, 128) >> 1;
	क्रम (i = 0; i < 7; i++) अणु
		अगर (val == 0)
			अवरोध;
		val >>= 1;
	पूर्ण
	वापस (u8) i;
पूर्ण

काष्ठा w83791d_data अणु
	काष्ठा device *hwmon_dev;
	काष्ठा mutex update_lock;

	अक्षर valid;			/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	/* array of 2 poपूर्णांकers to subclients */
	काष्ठा i2c_client *lm75[2];

	/* volts */
	u8 in[NUMBER_OF_VIN];		/* Register value */
	u8 in_max[NUMBER_OF_VIN];	/* Register value */
	u8 in_min[NUMBER_OF_VIN];	/* Register value */

	/* fans */
	u8 fan[NUMBER_OF_FANIN];	/* Register value */
	u8 fan_min[NUMBER_OF_FANIN];	/* Register value */
	u8 fan_भाग[NUMBER_OF_FANIN];	/* Register encoding, shअगरted right */

	/* Temperature sensors */

	s8 temp1[3];		/* current, over, thyst */
	s16 temp_add[2][3];	/* fixed poपूर्णांक value. Top 8 bits are the
				 * पूर्णांकegral part, bottom 8 bits are the
				 * fractional part. We only use the top
				 * 9 bits as the resolution is only
				 * to the 0.5 degree C...
				 * two sensors with three values
				 * (cur, over, hyst)
				 */

	/* PWMs */
	u8 pwm[5];		/* pwm duty cycle */
	u8 pwm_enable[3];	/* pwm enable status क्रम fan 1-3
				 * (fan 4-5 only support manual mode)
				 */

	u8 temp_target[3];	/* pwm 1-3 target temperature */
	u8 temp_tolerance[3];	/* pwm 1-3 temperature tolerance */

	/* Misc */
	u32 alarms;		/* realसमय status रेजिस्टर encoding,combined */
	u8 beep_enable;		/* Global beep enable */
	u32 beep_mask;		/* Mask off specअगरic beeps */
	u8 vid;			/* Register encoding, combined */
	u8 vrm;			/* hwmon-vid */
पूर्ण;

अटल पूर्णांक w83791d_probe(काष्ठा i2c_client *client);
अटल पूर्णांक w83791d_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info);
अटल पूर्णांक w83791d_हटाओ(काष्ठा i2c_client *client);

अटल पूर्णांक w83791d_पढ़ो(काष्ठा i2c_client *client, u8 reg);
अटल पूर्णांक w83791d_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 value);
अटल काष्ठा w83791d_data *w83791d_update_device(काष्ठा device *dev);

#अगर_घोषित DEBUG
अटल व्योम w83791d_prपूर्णांक_debug(काष्ठा w83791d_data *data, काष्ठा device *dev);
#पूर्ण_अगर

अटल व्योम w83791d_init_client(काष्ठा i2c_client *client);

अटल स्थिर काष्ठा i2c_device_id w83791d_id[] = अणु
	अणु "w83791d", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, w83791d_id);

अटल काष्ठा i2c_driver w83791d_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name = "w83791d",
	पूर्ण,
	.probe_new	= w83791d_probe,
	.हटाओ		= w83791d_हटाओ,
	.id_table	= w83791d_id,
	.detect		= w83791d_detect,
	.address_list	= normal_i2c,
पूर्ण;

/* following are the sysfs callback functions */
#घोषणा show_in_reg(reg) \
अटल sमाप_प्रकार show_##reg(काष्ठा device *dev, काष्ठा device_attribute *attr, \
			अक्षर *buf) \
अणु \
	काष्ठा sensor_device_attribute *sensor_attr = \
						to_sensor_dev_attr(attr); \
	काष्ठा w83791d_data *data = w83791d_update_device(dev); \
	पूर्णांक nr = sensor_attr->index; \
	वापस प्र_लिखो(buf, "%d\n", IN_FROM_REG(data->reg[nr])); \
पूर्ण

show_in_reg(in);
show_in_reg(in_min);
show_in_reg(in_max);

#घोषणा store_in_reg(REG, reg) \
अटल sमाप_प्रकार store_in_##reg(काष्ठा device *dev, \
				काष्ठा device_attribute *attr, \
				स्थिर अक्षर *buf, माप_प्रकार count) \
अणु \
	काष्ठा sensor_device_attribute *sensor_attr = \
						to_sensor_dev_attr(attr); \
	काष्ठा i2c_client *client = to_i2c_client(dev); \
	काष्ठा w83791d_data *data = i2c_get_clientdata(client); \
	पूर्णांक nr = sensor_attr->index; \
	अचिन्हित दीर्घ val; \
	पूर्णांक err = kम_से_अदीर्घ(buf, 10, &val); \
	अगर (err) \
		वापस err; \
	mutex_lock(&data->update_lock); \
	data->in_##reg[nr] = IN_TO_REG(val); \
	w83791d_ग_लिखो(client, W83791D_REG_IN_##REG[nr], data->in_##reg[nr]); \
	mutex_unlock(&data->update_lock); \
	 \
	वापस count; \
पूर्ण
store_in_reg(MIN, min);
store_in_reg(MAX, max);

अटल काष्ठा sensor_device_attribute sda_in_input[] = अणु
	SENSOR_ATTR(in0_input, S_IRUGO, show_in, शून्य, 0),
	SENSOR_ATTR(in1_input, S_IRUGO, show_in, शून्य, 1),
	SENSOR_ATTR(in2_input, S_IRUGO, show_in, शून्य, 2),
	SENSOR_ATTR(in3_input, S_IRUGO, show_in, शून्य, 3),
	SENSOR_ATTR(in4_input, S_IRUGO, show_in, शून्य, 4),
	SENSOR_ATTR(in5_input, S_IRUGO, show_in, शून्य, 5),
	SENSOR_ATTR(in6_input, S_IRUGO, show_in, शून्य, 6),
	SENSOR_ATTR(in7_input, S_IRUGO, show_in, शून्य, 7),
	SENSOR_ATTR(in8_input, S_IRUGO, show_in, शून्य, 8),
	SENSOR_ATTR(in9_input, S_IRUGO, show_in, शून्य, 9),
पूर्ण;

अटल काष्ठा sensor_device_attribute sda_in_min[] = अणु
	SENSOR_ATTR(in0_min, S_IWUSR | S_IRUGO, show_in_min, store_in_min, 0),
	SENSOR_ATTR(in1_min, S_IWUSR | S_IRUGO, show_in_min, store_in_min, 1),
	SENSOR_ATTR(in2_min, S_IWUSR | S_IRUGO, show_in_min, store_in_min, 2),
	SENSOR_ATTR(in3_min, S_IWUSR | S_IRUGO, show_in_min, store_in_min, 3),
	SENSOR_ATTR(in4_min, S_IWUSR | S_IRUGO, show_in_min, store_in_min, 4),
	SENSOR_ATTR(in5_min, S_IWUSR | S_IRUGO, show_in_min, store_in_min, 5),
	SENSOR_ATTR(in6_min, S_IWUSR | S_IRUGO, show_in_min, store_in_min, 6),
	SENSOR_ATTR(in7_min, S_IWUSR | S_IRUGO, show_in_min, store_in_min, 7),
	SENSOR_ATTR(in8_min, S_IWUSR | S_IRUGO, show_in_min, store_in_min, 8),
	SENSOR_ATTR(in9_min, S_IWUSR | S_IRUGO, show_in_min, store_in_min, 9),
पूर्ण;

अटल काष्ठा sensor_device_attribute sda_in_max[] = अणु
	SENSOR_ATTR(in0_max, S_IWUSR | S_IRUGO, show_in_max, store_in_max, 0),
	SENSOR_ATTR(in1_max, S_IWUSR | S_IRUGO, show_in_max, store_in_max, 1),
	SENSOR_ATTR(in2_max, S_IWUSR | S_IRUGO, show_in_max, store_in_max, 2),
	SENSOR_ATTR(in3_max, S_IWUSR | S_IRUGO, show_in_max, store_in_max, 3),
	SENSOR_ATTR(in4_max, S_IWUSR | S_IRUGO, show_in_max, store_in_max, 4),
	SENSOR_ATTR(in5_max, S_IWUSR | S_IRUGO, show_in_max, store_in_max, 5),
	SENSOR_ATTR(in6_max, S_IWUSR | S_IRUGO, show_in_max, store_in_max, 6),
	SENSOR_ATTR(in7_max, S_IWUSR | S_IRUGO, show_in_max, store_in_max, 7),
	SENSOR_ATTR(in8_max, S_IWUSR | S_IRUGO, show_in_max, store_in_max, 8),
	SENSOR_ATTR(in9_max, S_IWUSR | S_IRUGO, show_in_max, store_in_max, 9),
पूर्ण;


अटल sमाप_प्रकार show_beep(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr =
						to_sensor_dev_attr(attr);
	काष्ठा w83791d_data *data = w83791d_update_device(dev);
	पूर्णांक bitnr = sensor_attr->index;

	वापस प्र_लिखो(buf, "%d\n", (data->beep_mask >> bitnr) & 1);
पूर्ण

अटल sमाप_प्रकार store_beep(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr =
						to_sensor_dev_attr(attr);
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83791d_data *data = i2c_get_clientdata(client);
	पूर्णांक bitnr = sensor_attr->index;
	पूर्णांक bytenr = bitnr / 8;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	val = val ? 1 : 0;

	mutex_lock(&data->update_lock);

	data->beep_mask &= ~(0xff << (bytenr * 8));
	data->beep_mask |= w83791d_पढ़ो(client, W83791D_REG_BEEP_CTRL[bytenr])
		<< (bytenr * 8);

	data->beep_mask &= ~(1 << bitnr);
	data->beep_mask |= val << bitnr;

	w83791d_ग_लिखो(client, W83791D_REG_BEEP_CTRL[bytenr],
		(data->beep_mask >> (bytenr * 8)) & 0xff);

	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_alarm(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr =
						to_sensor_dev_attr(attr);
	काष्ठा w83791d_data *data = w83791d_update_device(dev);
	पूर्णांक bitnr = sensor_attr->index;

	वापस प्र_लिखो(buf, "%d\n", (data->alarms >> bitnr) & 1);
पूर्ण

/*
 * Note: The biपंचांगask क्रम the beep enable/disable is dअगरferent than
 * the biपंचांगask क्रम the alarm.
 */
अटल काष्ठा sensor_device_attribute sda_in_beep[] = अणु
	SENSOR_ATTR(in0_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 0),
	SENSOR_ATTR(in1_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 13),
	SENSOR_ATTR(in2_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 2),
	SENSOR_ATTR(in3_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 3),
	SENSOR_ATTR(in4_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 8),
	SENSOR_ATTR(in5_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 9),
	SENSOR_ATTR(in6_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 10),
	SENSOR_ATTR(in7_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 16),
	SENSOR_ATTR(in8_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 17),
	SENSOR_ATTR(in9_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 14),
पूर्ण;

अटल काष्ठा sensor_device_attribute sda_in_alarm[] = अणु
	SENSOR_ATTR(in0_alarm, S_IRUGO, show_alarm, शून्य, 0),
	SENSOR_ATTR(in1_alarm, S_IRUGO, show_alarm, शून्य, 1),
	SENSOR_ATTR(in2_alarm, S_IRUGO, show_alarm, शून्य, 2),
	SENSOR_ATTR(in3_alarm, S_IRUGO, show_alarm, शून्य, 3),
	SENSOR_ATTR(in4_alarm, S_IRUGO, show_alarm, शून्य, 8),
	SENSOR_ATTR(in5_alarm, S_IRUGO, show_alarm, शून्य, 9),
	SENSOR_ATTR(in6_alarm, S_IRUGO, show_alarm, शून्य, 10),
	SENSOR_ATTR(in7_alarm, S_IRUGO, show_alarm, शून्य, 19),
	SENSOR_ATTR(in8_alarm, S_IRUGO, show_alarm, शून्य, 20),
	SENSOR_ATTR(in9_alarm, S_IRUGO, show_alarm, शून्य, 14),
पूर्ण;

#घोषणा show_fan_reg(reg) \
अटल sमाप_प्रकार show_##reg(काष्ठा device *dev, काष्ठा device_attribute *attr, \
				अक्षर *buf) \
अणु \
	काष्ठा sensor_device_attribute *sensor_attr = \
						to_sensor_dev_attr(attr); \
	काष्ठा w83791d_data *data = w83791d_update_device(dev); \
	पूर्णांक nr = sensor_attr->index; \
	वापस प्र_लिखो(buf, "%d\n", \
		FAN_FROM_REG(data->reg[nr], DIV_FROM_REG(data->fan_भाग[nr]))); \
पूर्ण

show_fan_reg(fan);
show_fan_reg(fan_min);

अटल sमाप_प्रकार store_fan_min(काष्ठा device *dev, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83791d_data *data = i2c_get_clientdata(client);
	पूर्णांक nr = sensor_attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan_min[nr] = fan_to_reg(val, DIV_FROM_REG(data->fan_भाग[nr]));
	w83791d_ग_लिखो(client, W83791D_REG_FAN_MIN[nr], data->fan_min[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_fan_भाग(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा w83791d_data *data = w83791d_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", DIV_FROM_REG(data->fan_भाग[nr]));
पूर्ण

/*
 * Note: we save and restore the fan minimum here, because its value is
 * determined in part by the fan भागisor.  This follows the principle of
 * least surprise; the user करोesn't expect the fan minimum to change just
 * because the भागisor changed.
 */
अटल sमाप_प्रकार store_fan_भाग(काष्ठा device *dev, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83791d_data *data = i2c_get_clientdata(client);
	पूर्णांक nr = sensor_attr->index;
	अचिन्हित दीर्घ min;
	u8 पंचांगp_fan_भाग;
	u8 fan_भाग_reg;
	u8 vbat_reg;
	पूर्णांक indx = 0;
	u8 keep_mask = 0;
	u8 new_shअगरt = 0;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	/* Save fan_min */
	min = FAN_FROM_REG(data->fan_min[nr], DIV_FROM_REG(data->fan_भाग[nr]));

	mutex_lock(&data->update_lock);
	data->fan_भाग[nr] = भाग_प्रकारo_reg(nr, val);

	चयन (nr) अणु
	हाल 0:
		indx = 0;
		keep_mask = 0xcf;
		new_shअगरt = 4;
		अवरोध;
	हाल 1:
		indx = 0;
		keep_mask = 0x3f;
		new_shअगरt = 6;
		अवरोध;
	हाल 2:
		indx = 1;
		keep_mask = 0x3f;
		new_shअगरt = 6;
		अवरोध;
	हाल 3:
		indx = 2;
		keep_mask = 0xf8;
		new_shअगरt = 0;
		अवरोध;
	हाल 4:
		indx = 2;
		keep_mask = 0x8f;
		new_shअगरt = 4;
		अवरोध;
#अगर_घोषित DEBUG
	शेष:
		dev_warn(dev, "store_fan_div: Unexpected nr seen: %d\n", nr);
		count = -EINVAL;
		जाओ err_निकास;
#पूर्ण_अगर
	पूर्ण

	fan_भाग_reg = w83791d_पढ़ो(client, W83791D_REG_FAN_DIV[indx])
			& keep_mask;
	पंचांगp_fan_भाग = (data->fan_भाग[nr] << new_shअगरt) & ~keep_mask;

	w83791d_ग_लिखो(client, W83791D_REG_FAN_DIV[indx],
				fan_भाग_reg | पंचांगp_fan_भाग);

	/* Bit 2 of fans 0-2 is stored in the vbat रेजिस्टर (bits 5-7) */
	अगर (nr < 3) अणु
		keep_mask = ~(1 << (nr + 5));
		vbat_reg = w83791d_पढ़ो(client, W83791D_REG_VBAT)
				& keep_mask;
		पंचांगp_fan_भाग = (data->fan_भाग[nr] << (3 + nr)) & ~keep_mask;
		w83791d_ग_लिखो(client, W83791D_REG_VBAT,
				vbat_reg | पंचांगp_fan_भाग);
	पूर्ण

	/* Restore fan_min */
	data->fan_min[nr] = fan_to_reg(min, DIV_FROM_REG(data->fan_भाग[nr]));
	w83791d_ग_लिखो(client, W83791D_REG_FAN_MIN[nr], data->fan_min[nr]);

#अगर_घोषित DEBUG
err_निकास:
#पूर्ण_अगर
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल काष्ठा sensor_device_attribute sda_fan_input[] = अणु
	SENSOR_ATTR(fan1_input, S_IRUGO, show_fan, शून्य, 0),
	SENSOR_ATTR(fan2_input, S_IRUGO, show_fan, शून्य, 1),
	SENSOR_ATTR(fan3_input, S_IRUGO, show_fan, शून्य, 2),
	SENSOR_ATTR(fan4_input, S_IRUGO, show_fan, शून्य, 3),
	SENSOR_ATTR(fan5_input, S_IRUGO, show_fan, शून्य, 4),
पूर्ण;

अटल काष्ठा sensor_device_attribute sda_fan_min[] = अणु
	SENSOR_ATTR(fan1_min, S_IWUSR | S_IRUGO,
			show_fan_min, store_fan_min, 0),
	SENSOR_ATTR(fan2_min, S_IWUSR | S_IRUGO,
			show_fan_min, store_fan_min, 1),
	SENSOR_ATTR(fan3_min, S_IWUSR | S_IRUGO,
			show_fan_min, store_fan_min, 2),
	SENSOR_ATTR(fan4_min, S_IWUSR | S_IRUGO,
			show_fan_min, store_fan_min, 3),
	SENSOR_ATTR(fan5_min, S_IWUSR | S_IRUGO,
			show_fan_min, store_fan_min, 4),
पूर्ण;

अटल काष्ठा sensor_device_attribute sda_fan_भाग[] = अणु
	SENSOR_ATTR(fan1_भाग, S_IWUSR | S_IRUGO,
			show_fan_भाग, store_fan_भाग, 0),
	SENSOR_ATTR(fan2_भाग, S_IWUSR | S_IRUGO,
			show_fan_भाग, store_fan_भाग, 1),
	SENSOR_ATTR(fan3_भाग, S_IWUSR | S_IRUGO,
			show_fan_भाग, store_fan_भाग, 2),
	SENSOR_ATTR(fan4_भाग, S_IWUSR | S_IRUGO,
			show_fan_भाग, store_fan_भाग, 3),
	SENSOR_ATTR(fan5_भाग, S_IWUSR | S_IRUGO,
			show_fan_भाग, store_fan_भाग, 4),
पूर्ण;

अटल काष्ठा sensor_device_attribute sda_fan_beep[] = अणु
	SENSOR_ATTR(fan1_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 6),
	SENSOR_ATTR(fan2_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 7),
	SENSOR_ATTR(fan3_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 11),
	SENSOR_ATTR(fan4_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 21),
	SENSOR_ATTR(fan5_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 22),
पूर्ण;

अटल काष्ठा sensor_device_attribute sda_fan_alarm[] = अणु
	SENSOR_ATTR(fan1_alarm, S_IRUGO, show_alarm, शून्य, 6),
	SENSOR_ATTR(fan2_alarm, S_IRUGO, show_alarm, शून्य, 7),
	SENSOR_ATTR(fan3_alarm, S_IRUGO, show_alarm, शून्य, 11),
	SENSOR_ATTR(fan4_alarm, S_IRUGO, show_alarm, शून्य, 21),
	SENSOR_ATTR(fan5_alarm, S_IRUGO, show_alarm, शून्य, 22),
पूर्ण;

/* पढ़ो/ग_लिखो PWMs */
अटल sमाप_प्रकार show_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा w83791d_data *data = w83791d_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", data->pwm[nr]);
पूर्ण

अटल sमाप_प्रकार store_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83791d_data *data = i2c_get_clientdata(client);
	पूर्णांक nr = sensor_attr->index;
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->pwm[nr] = clamp_val(val, 0, 255);
	w83791d_ग_लिखो(client, W83791D_REG_PWM[nr], data->pwm[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल काष्ठा sensor_device_attribute sda_pwm[] = अणु
	SENSOR_ATTR(pwm1, S_IWUSR | S_IRUGO,
			show_pwm, store_pwm, 0),
	SENSOR_ATTR(pwm2, S_IWUSR | S_IRUGO,
			show_pwm, store_pwm, 1),
	SENSOR_ATTR(pwm3, S_IWUSR | S_IRUGO,
			show_pwm, store_pwm, 2),
	SENSOR_ATTR(pwm4, S_IWUSR | S_IRUGO,
			show_pwm, store_pwm, 3),
	SENSOR_ATTR(pwm5, S_IWUSR | S_IRUGO,
			show_pwm, store_pwm, 4),
पूर्ण;

अटल sमाप_प्रकार show_pwmenable(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा w83791d_data *data = w83791d_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", data->pwm_enable[nr] + 1);
पूर्ण

अटल sमाप_प्रकार store_pwmenable(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83791d_data *data = i2c_get_clientdata(client);
	पूर्णांक nr = sensor_attr->index;
	अचिन्हित दीर्घ val;
	u8 reg_cfg_पंचांगp;
	u8 reg_idx = 0;
	u8 val_shअगरt = 0;
	u8 keep_mask = 0;

	पूर्णांक ret = kम_से_अदीर्घ(buf, 10, &val);

	अगर (ret || val < 1 || val > 3)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->pwm_enable[nr] = val - 1;
	चयन (nr) अणु
	हाल 0:
		reg_idx = 0;
		val_shअगरt = 2;
		keep_mask = 0xf3;
		अवरोध;
	हाल 1:
		reg_idx = 0;
		val_shअगरt = 4;
		keep_mask = 0xcf;
		अवरोध;
	हाल 2:
		reg_idx = 1;
		val_shअगरt = 2;
		keep_mask = 0xf3;
		अवरोध;
	पूर्ण

	reg_cfg_पंचांगp = w83791d_पढ़ो(client, W83791D_REG_FAN_CFG[reg_idx]);
	reg_cfg_पंचांगp = (reg_cfg_पंचांगp & keep_mask) |
					data->pwm_enable[nr] << val_shअगरt;

	w83791d_ग_लिखो(client, W83791D_REG_FAN_CFG[reg_idx], reg_cfg_पंचांगp);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण
अटल काष्ठा sensor_device_attribute sda_pwmenable[] = अणु
	SENSOR_ATTR(pwm1_enable, S_IWUSR | S_IRUGO,
			show_pwmenable, store_pwmenable, 0),
	SENSOR_ATTR(pwm2_enable, S_IWUSR | S_IRUGO,
			show_pwmenable, store_pwmenable, 1),
	SENSOR_ATTR(pwm3_enable, S_IWUSR | S_IRUGO,
			show_pwmenable, store_pwmenable, 2),
पूर्ण;

/* For Smart Fan I / Thermal Cruise */
अटल sमाप_प्रकार show_temp_target(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा w83791d_data *data = w83791d_update_device(dev);
	पूर्णांक nr = sensor_attr->index;
	वापस प्र_लिखो(buf, "%d\n", TEMP1_FROM_REG(data->temp_target[nr]));
पूर्ण

अटल sमाप_प्रकार store_temp_target(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83791d_data *data = i2c_get_clientdata(client);
	पूर्णांक nr = sensor_attr->index;
	दीर्घ val;
	u8 target_mask;

	अगर (kम_से_दीर्घ(buf, 10, &val))
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->temp_target[nr] = TARGET_TEMP_TO_REG(val);
	target_mask = w83791d_पढ़ो(client,
				W83791D_REG_TEMP_TARGET[nr]) & 0x80;
	w83791d_ग_लिखो(client, W83791D_REG_TEMP_TARGET[nr],
				data->temp_target[nr] | target_mask);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल काष्ठा sensor_device_attribute sda_temp_target[] = अणु
	SENSOR_ATTR(temp1_target, S_IWUSR | S_IRUGO,
			show_temp_target, store_temp_target, 0),
	SENSOR_ATTR(temp2_target, S_IWUSR | S_IRUGO,
			show_temp_target, store_temp_target, 1),
	SENSOR_ATTR(temp3_target, S_IWUSR | S_IRUGO,
			show_temp_target, store_temp_target, 2),
पूर्ण;

अटल sमाप_प्रकार show_temp_tolerance(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा w83791d_data *data = w83791d_update_device(dev);
	पूर्णांक nr = sensor_attr->index;
	वापस प्र_लिखो(buf, "%d\n", TEMP1_FROM_REG(data->temp_tolerance[nr]));
पूर्ण

अटल sमाप_प्रकार store_temp_tolerance(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83791d_data *data = i2c_get_clientdata(client);
	पूर्णांक nr = sensor_attr->index;
	अचिन्हित दीर्घ val;
	u8 target_mask;
	u8 reg_idx = 0;
	u8 val_shअगरt = 0;
	u8 keep_mask = 0;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	चयन (nr) अणु
	हाल 0:
		reg_idx = 0;
		val_shअगरt = 0;
		keep_mask = 0xf0;
		अवरोध;
	हाल 1:
		reg_idx = 0;
		val_shअगरt = 4;
		keep_mask = 0x0f;
		अवरोध;
	हाल 2:
		reg_idx = 1;
		val_shअगरt = 0;
		keep_mask = 0xf0;
		अवरोध;
	पूर्ण

	mutex_lock(&data->update_lock);
	data->temp_tolerance[nr] = TOL_TEMP_TO_REG(val);
	target_mask = w83791d_पढ़ो(client,
			W83791D_REG_TEMP_TOL[reg_idx]) & keep_mask;
	w83791d_ग_लिखो(client, W83791D_REG_TEMP_TOL[reg_idx],
			(data->temp_tolerance[nr] << val_shअगरt) | target_mask);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल काष्ठा sensor_device_attribute sda_temp_tolerance[] = अणु
	SENSOR_ATTR(temp1_tolerance, S_IWUSR | S_IRUGO,
			show_temp_tolerance, store_temp_tolerance, 0),
	SENSOR_ATTR(temp2_tolerance, S_IWUSR | S_IRUGO,
			show_temp_tolerance, store_temp_tolerance, 1),
	SENSOR_ATTR(temp3_tolerance, S_IWUSR | S_IRUGO,
			show_temp_tolerance, store_temp_tolerance, 2),
पूर्ण;

/* पढ़ो/ग_लिखो the temperature1, includes measured value and limits */
अटल sमाप_प्रकार show_temp1(काष्ठा device *dev, काष्ठा device_attribute *devattr,
				अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा w83791d_data *data = w83791d_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP1_FROM_REG(data->temp1[attr->index]));
पूर्ण

अटल sमाप_प्रकार store_temp1(काष्ठा device *dev, काष्ठा device_attribute *devattr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83791d_data *data = i2c_get_clientdata(client);
	पूर्णांक nr = attr->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp1[nr] = TEMP1_TO_REG(val);
	w83791d_ग_लिखो(client, W83791D_REG_TEMP1[nr], data->temp1[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/* पढ़ो/ग_लिखो temperature2-3, includes measured value and limits */
अटल sमाप_प्रकार show_temp23(काष्ठा device *dev, काष्ठा device_attribute *devattr,
				अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा w83791d_data *data = w83791d_update_device(dev);
	पूर्णांक nr = attr->nr;
	पूर्णांक index = attr->index;
	वापस प्र_लिखो(buf, "%d\n", TEMP23_FROM_REG(data->temp_add[nr][index]));
पूर्ण

अटल sमाप_प्रकार store_temp23(काष्ठा device *dev,
				काष्ठा device_attribute *devattr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83791d_data *data = i2c_get_clientdata(client);
	दीर्घ val;
	पूर्णांक err;
	पूर्णांक nr = attr->nr;
	पूर्णांक index = attr->index;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_add[nr][index] = TEMP23_TO_REG(val);
	w83791d_ग_लिखो(client, W83791D_REG_TEMP_ADD[nr][index * 2],
				data->temp_add[nr][index] >> 8);
	w83791d_ग_लिखो(client, W83791D_REG_TEMP_ADD[nr][index * 2 + 1],
				data->temp_add[nr][index] & 0x80);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल काष्ठा sensor_device_attribute_2 sda_temp_input[] = अणु
	SENSOR_ATTR_2(temp1_input, S_IRUGO, show_temp1, शून्य, 0, 0),
	SENSOR_ATTR_2(temp2_input, S_IRUGO, show_temp23, शून्य, 0, 0),
	SENSOR_ATTR_2(temp3_input, S_IRUGO, show_temp23, शून्य, 1, 0),
पूर्ण;

अटल काष्ठा sensor_device_attribute_2 sda_temp_max[] = अणु
	SENSOR_ATTR_2(temp1_max, S_IRUGO | S_IWUSR,
			show_temp1, store_temp1, 0, 1),
	SENSOR_ATTR_2(temp2_max, S_IRUGO | S_IWUSR,
			show_temp23, store_temp23, 0, 1),
	SENSOR_ATTR_2(temp3_max, S_IRUGO | S_IWUSR,
			show_temp23, store_temp23, 1, 1),
पूर्ण;

अटल काष्ठा sensor_device_attribute_2 sda_temp_max_hyst[] = अणु
	SENSOR_ATTR_2(temp1_max_hyst, S_IRUGO | S_IWUSR,
			show_temp1, store_temp1, 0, 2),
	SENSOR_ATTR_2(temp2_max_hyst, S_IRUGO | S_IWUSR,
			show_temp23, store_temp23, 0, 2),
	SENSOR_ATTR_2(temp3_max_hyst, S_IRUGO | S_IWUSR,
			show_temp23, store_temp23, 1, 2),
पूर्ण;

/*
 * Note: The biपंचांगask क्रम the beep enable/disable is dअगरferent than
 * the biपंचांगask क्रम the alarm.
 */
अटल काष्ठा sensor_device_attribute sda_temp_beep[] = अणु
	SENSOR_ATTR(temp1_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 4),
	SENSOR_ATTR(temp2_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 5),
	SENSOR_ATTR(temp3_beep, S_IWUSR | S_IRUGO, show_beep, store_beep, 1),
पूर्ण;

अटल काष्ठा sensor_device_attribute sda_temp_alarm[] = अणु
	SENSOR_ATTR(temp1_alarm, S_IRUGO, show_alarm, शून्य, 4),
	SENSOR_ATTR(temp2_alarm, S_IRUGO, show_alarm, शून्य, 5),
	SENSOR_ATTR(temp3_alarm, S_IRUGO, show_alarm, शून्य, 13),
पूर्ण;

/* get realसमय status of all sensors items: voltage, temp, fan */
अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा w83791d_data *data = w83791d_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", data->alarms);
पूर्ण

अटल DEVICE_ATTR_RO(alarms);

/* Beep control */

#घोषणा GLOBAL_BEEP_ENABLE_SHIFT	15
#घोषणा GLOBAL_BEEP_ENABLE_MASK		(1 << GLOBAL_BEEP_ENABLE_SHIFT)

अटल sमाप_प्रकार show_beep_enable(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83791d_data *data = w83791d_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->beep_enable);
पूर्ण

अटल sमाप_प्रकार show_beep_mask(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83791d_data *data = w83791d_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", BEEP_MASK_FROM_REG(data->beep_mask));
पूर्ण


अटल sमाप_प्रकार store_beep_mask(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83791d_data *data = i2c_get_clientdata(client);
	पूर्णांक i;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);

	/*
	 * The beep_enable state overrides any enabling request from
	 * the masks
	 */
	data->beep_mask = BEEP_MASK_TO_REG(val) & ~GLOBAL_BEEP_ENABLE_MASK;
	data->beep_mask |= (data->beep_enable << GLOBAL_BEEP_ENABLE_SHIFT);

	val = data->beep_mask;

	क्रम (i = 0; i < 3; i++) अणु
		w83791d_ग_लिखो(client, W83791D_REG_BEEP_CTRL[i], (val & 0xff));
		val >>= 8;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार store_beep_enable(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83791d_data *data = i2c_get_clientdata(client);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);

	data->beep_enable = val ? 1 : 0;

	/* Keep the full mask value in sync with the current enable */
	data->beep_mask &= ~GLOBAL_BEEP_ENABLE_MASK;
	data->beep_mask |= (data->beep_enable << GLOBAL_BEEP_ENABLE_SHIFT);

	/*
	 * The global control is in the second beep control रेजिस्टर
	 * so only need to update that रेजिस्टर
	 */
	val = (data->beep_mask >> 8) & 0xff;

	w83791d_ग_लिखो(client, W83791D_REG_BEEP_CTRL[1], val);

	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल काष्ठा sensor_device_attribute sda_beep_ctrl[] = अणु
	SENSOR_ATTR(beep_enable, S_IRUGO | S_IWUSR,
			show_beep_enable, store_beep_enable, 0),
	SENSOR_ATTR(beep_mask, S_IRUGO | S_IWUSR,
			show_beep_mask, store_beep_mask, 1)
पूर्ण;

/* cpu voltage regulation inक्रमmation */
अटल sमाप_प्रकार cpu0_vid_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83791d_data *data = w83791d_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", vid_from_reg(data->vid, data->vrm));
पूर्ण

अटल DEVICE_ATTR_RO(cpu0_vid);

अटल sमाप_प्रकार vrm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा w83791d_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", data->vrm);
पूर्ण

अटल sमाप_प्रकार vrm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा w83791d_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	/*
	 * No lock needed as vrm is पूर्णांकernal to the driver
	 * (not पढ़ो from a chip रेजिस्टर) and so is not
	 * updated in w83791d_update_device()
	 */

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val > 255)
		वापस -EINVAL;

	data->vrm = val;
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(vrm);

#घोषणा IN_UNIT_ATTRS(X) \
	&sda_in_input[X].dev_attr.attr,	\
	&sda_in_min[X].dev_attr.attr,	\
	&sda_in_max[X].dev_attr.attr,	\
	&sda_in_beep[X].dev_attr.attr,	\
	&sda_in_alarm[X].dev_attr.attr

#घोषणा FAN_UNIT_ATTRS(X) \
	&sda_fan_input[X].dev_attr.attr,	\
	&sda_fan_min[X].dev_attr.attr,		\
	&sda_fan_भाग[X].dev_attr.attr,		\
	&sda_fan_beep[X].dev_attr.attr,		\
	&sda_fan_alarm[X].dev_attr.attr

#घोषणा TEMP_UNIT_ATTRS(X) \
	&sda_temp_input[X].dev_attr.attr,	\
	&sda_temp_max[X].dev_attr.attr,		\
	&sda_temp_max_hyst[X].dev_attr.attr,	\
	&sda_temp_beep[X].dev_attr.attr,	\
	&sda_temp_alarm[X].dev_attr.attr

अटल काष्ठा attribute *w83791d_attributes[] = अणु
	IN_UNIT_ATTRS(0),
	IN_UNIT_ATTRS(1),
	IN_UNIT_ATTRS(2),
	IN_UNIT_ATTRS(3),
	IN_UNIT_ATTRS(4),
	IN_UNIT_ATTRS(5),
	IN_UNIT_ATTRS(6),
	IN_UNIT_ATTRS(7),
	IN_UNIT_ATTRS(8),
	IN_UNIT_ATTRS(9),
	FAN_UNIT_ATTRS(0),
	FAN_UNIT_ATTRS(1),
	FAN_UNIT_ATTRS(2),
	TEMP_UNIT_ATTRS(0),
	TEMP_UNIT_ATTRS(1),
	TEMP_UNIT_ATTRS(2),
	&dev_attr_alarms.attr,
	&sda_beep_ctrl[0].dev_attr.attr,
	&sda_beep_ctrl[1].dev_attr.attr,
	&dev_attr_cpu0_vid.attr,
	&dev_attr_vrm.attr,
	&sda_pwm[0].dev_attr.attr,
	&sda_pwm[1].dev_attr.attr,
	&sda_pwm[2].dev_attr.attr,
	&sda_pwmenable[0].dev_attr.attr,
	&sda_pwmenable[1].dev_attr.attr,
	&sda_pwmenable[2].dev_attr.attr,
	&sda_temp_target[0].dev_attr.attr,
	&sda_temp_target[1].dev_attr.attr,
	&sda_temp_target[2].dev_attr.attr,
	&sda_temp_tolerance[0].dev_attr.attr,
	&sda_temp_tolerance[1].dev_attr.attr,
	&sda_temp_tolerance[2].dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group w83791d_group = अणु
	.attrs = w83791d_attributes,
पूर्ण;

/*
 * Separate group of attributes क्रम fan/pwm 4-5. Their pins can also be
 * in use क्रम GPIO in which हाल their sysfs-पूर्णांकerface should not be made
 * available
 */
अटल काष्ठा attribute *w83791d_attributes_fanpwm45[] = अणु
	FAN_UNIT_ATTRS(3),
	FAN_UNIT_ATTRS(4),
	&sda_pwm[3].dev_attr.attr,
	&sda_pwm[4].dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group w83791d_group_fanpwm45 = अणु
	.attrs = w83791d_attributes_fanpwm45,
पूर्ण;

अटल पूर्णांक w83791d_detect_subclients(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा w83791d_data *data = i2c_get_clientdata(client);
	पूर्णांक address = client->addr;
	पूर्णांक i, id;
	u8 val;

	id = i2c_adapter_id(adapter);
	अगर (क्रमce_subclients[0] == id && क्रमce_subclients[1] == address) अणु
		क्रम (i = 2; i <= 3; i++) अणु
			अगर (क्रमce_subclients[i] < 0x48 ||
			    क्रमce_subclients[i] > 0x4f) अणु
				dev_err(&client->dev,
					"invalid subclient "
					"address %d; must be 0x48-0x4f\n",
					क्रमce_subclients[i]);
				वापस -ENODEV;
			पूर्ण
		पूर्ण
		w83791d_ग_लिखो(client, W83791D_REG_I2C_SUBADDR,
					(क्रमce_subclients[2] & 0x07) |
					((क्रमce_subclients[3] & 0x07) << 4));
	पूर्ण

	val = w83791d_पढ़ो(client, W83791D_REG_I2C_SUBADDR);
	अगर (!(val & 0x08))
		data->lm75[0] = devm_i2c_new_dummy_device(&client->dev, adapter,
							  0x48 + (val & 0x7));
	अगर (!(val & 0x80)) अणु
		अगर (!IS_ERR(data->lm75[0]) &&
				((val & 0x7) == ((val >> 4) & 0x7))) अणु
			dev_err(&client->dev,
				"duplicate addresses 0x%x, "
				"use force_subclient\n",
				data->lm75[0]->addr);
			वापस -ENODEV;
		पूर्ण
		data->lm75[1] = devm_i2c_new_dummy_device(&client->dev, adapter,
							  0x48 + ((val >> 4) & 0x7));
	पूर्ण

	वापस 0;
पूर्ण


/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक w83791d_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक val1, val2;
	अचिन्हित लघु address = client->addr;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	अगर (w83791d_पढ़ो(client, W83791D_REG_CONFIG) & 0x80)
		वापस -ENODEV;

	val1 = w83791d_पढ़ो(client, W83791D_REG_BANK);
	val2 = w83791d_पढ़ो(client, W83791D_REG_CHIPMAN);
	/* Check क्रम Winbond ID अगर in bank 0 */
	अगर (!(val1 & 0x07)) अणु
		अगर ((!(val1 & 0x80) && val2 != 0xa3) ||
		    ((val1 & 0x80) && val2 != 0x5c)) अणु
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	/*
	 * If Winbond chip, address of chip and W83791D_REG_I2C_ADDR
	 * should match
	 */
	अगर (w83791d_पढ़ो(client, W83791D_REG_I2C_ADDR) != address)
		वापस -ENODEV;

	/* We want bank 0 and Venकरोr ID high byte */
	val1 = w83791d_पढ़ो(client, W83791D_REG_BANK) & 0x78;
	w83791d_ग_लिखो(client, W83791D_REG_BANK, val1 | 0x80);

	/* Verअगरy it is a Winbond w83791d */
	val1 = w83791d_पढ़ो(client, W83791D_REG_WCHIPID);
	val2 = w83791d_पढ़ो(client, W83791D_REG_CHIPMAN);
	अगर (val1 != 0x71 || val2 != 0x5c)
		वापस -ENODEV;

	strlcpy(info->type, "w83791d", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक w83791d_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा w83791d_data *data;
	काष्ठा device *dev = &client->dev;
	पूर्णांक i, err;
	u8 has_fanpwm45;

#अगर_घोषित DEBUG
	पूर्णांक val1;
	val1 = w83791d_पढ़ो(client, W83791D_REG_DID_VID4);
	dev_dbg(dev, "Device ID version: %d.%d (0x%02x)\n",
			(val1 >> 5) & 0x07, (val1 >> 1) & 0x0f, val1);
#पूर्ण_अगर

	data = devm_kzalloc(&client->dev, माप(काष्ठा w83791d_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	err = w83791d_detect_subclients(client);
	अगर (err)
		वापस err;

	/* Initialize the chip */
	w83791d_init_client(client);

	/*
	 * If the fan_भाग is changed, make sure there is a rational
	 * fan_min in place
	 */
	क्रम (i = 0; i < NUMBER_OF_FANIN; i++)
		data->fan_min[i] = w83791d_पढ़ो(client, W83791D_REG_FAN_MIN[i]);

	/* Register sysfs hooks */
	err = sysfs_create_group(&client->dev.kobj, &w83791d_group);
	अगर (err)
		वापस err;

	/* Check अगर pins of fan/pwm 4-5 are in use as GPIO */
	has_fanpwm45 = w83791d_पढ़ो(client, W83791D_REG_GPIO) & 0x10;
	अगर (has_fanpwm45) अणु
		err = sysfs_create_group(&client->dev.kobj,
					 &w83791d_group_fanpwm45);
		अगर (err)
			जाओ error4;
	पूर्ण

	/* Everything is पढ़ोy, now रेजिस्टर the working device */
	data->hwmon_dev = hwmon_device_रेजिस्टर(dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		जाओ error5;
	पूर्ण

	वापस 0;

error5:
	अगर (has_fanpwm45)
		sysfs_हटाओ_group(&client->dev.kobj, &w83791d_group_fanpwm45);
error4:
	sysfs_हटाओ_group(&client->dev.kobj, &w83791d_group);
	वापस err;
पूर्ण

अटल पूर्णांक w83791d_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा w83791d_data *data = i2c_get_clientdata(client);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	sysfs_हटाओ_group(&client->dev.kobj, &w83791d_group);

	वापस 0;
पूर्ण

अटल व्योम w83791d_init_client(काष्ठा i2c_client *client)
अणु
	काष्ठा w83791d_data *data = i2c_get_clientdata(client);
	u8 पंचांगp;
	u8 old_beep;

	/*
	 * The dअगरference between reset and init is that reset
	 * करोes a hard reset of the chip via index 0x40, bit 7,
	 * but init simply क्रमces certain रेजिस्टरs to have "sane"
	 * values. The hope is that the BIOS has करोne the right
	 * thing (which is why the शेष is reset=0, init=0),
	 * but अगर not, reset is the hard hammer and init
	 * is the soft mallet both of which are trying to whack
	 * things पूर्णांकo place...
	 * NOTE: The data sheet makes a distinction between
	 * "power on defaults" and "reset by MR". As far as I can tell,
	 * the hard reset माला_दो everything पूर्णांकo a घातer-on state so I'm
	 * not sure what "reset by MR" means or how it can happen.
	 */
	अगर (reset || init) अणु
		/* keep some BIOS settings when we... */
		old_beep = w83791d_पढ़ो(client, W83791D_REG_BEEP_CONFIG);

		अगर (reset) अणु
			/* ... reset the chip and ... */
			w83791d_ग_लिखो(client, W83791D_REG_CONFIG, 0x80);
		पूर्ण

		/* ... disable घातer-on abnormal beep */
		w83791d_ग_लिखो(client, W83791D_REG_BEEP_CONFIG, old_beep | 0x80);

		/* disable the global beep (not करोne by hard reset) */
		पंचांगp = w83791d_पढ़ो(client, W83791D_REG_BEEP_CTRL[1]);
		w83791d_ग_लिखो(client, W83791D_REG_BEEP_CTRL[1], पंचांगp & 0xef);

		अगर (init) अणु
			/* Make sure monitoring is turned on क्रम add-ons */
			पंचांगp = w83791d_पढ़ो(client, W83791D_REG_TEMP2_CONFIG);
			अगर (पंचांगp & 1) अणु
				w83791d_ग_लिखो(client, W83791D_REG_TEMP2_CONFIG,
					पंचांगp & 0xfe);
			पूर्ण

			पंचांगp = w83791d_पढ़ो(client, W83791D_REG_TEMP3_CONFIG);
			अगर (पंचांगp & 1) अणु
				w83791d_ग_लिखो(client, W83791D_REG_TEMP3_CONFIG,
					पंचांगp & 0xfe);
			पूर्ण

			/* Start monitoring */
			पंचांगp = w83791d_पढ़ो(client, W83791D_REG_CONFIG) & 0xf7;
			w83791d_ग_लिखो(client, W83791D_REG_CONFIG, पंचांगp | 0x01);
		पूर्ण
	पूर्ण

	data->vrm = vid_which_vrm();
पूर्ण

अटल काष्ठा w83791d_data *w83791d_update_device(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83791d_data *data = i2c_get_clientdata(client);
	पूर्णांक i, j;
	u8 reg_array_पंचांगp[3];
	u8 vbat_reg;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + (HZ * 3))
			|| !data->valid) अणु
		dev_dbg(dev, "Starting w83791d device update\n");

		/* Update the voltages measured value and limits */
		क्रम (i = 0; i < NUMBER_OF_VIN; i++) अणु
			data->in[i] = w83791d_पढ़ो(client,
						W83791D_REG_IN[i]);
			data->in_max[i] = w83791d_पढ़ो(client,
						W83791D_REG_IN_MAX[i]);
			data->in_min[i] = w83791d_पढ़ो(client,
						W83791D_REG_IN_MIN[i]);
		पूर्ण

		/* Update the fan counts and limits */
		क्रम (i = 0; i < NUMBER_OF_FANIN; i++) अणु
			/* Update the Fan measured value and limits */
			data->fan[i] = w83791d_पढ़ो(client,
						W83791D_REG_FAN[i]);
			data->fan_min[i] = w83791d_पढ़ो(client,
						W83791D_REG_FAN_MIN[i]);
		पूर्ण

		/* Update the fan भागisor */
		क्रम (i = 0; i < 3; i++) अणु
			reg_array_पंचांगp[i] = w83791d_पढ़ो(client,
						W83791D_REG_FAN_DIV[i]);
		पूर्ण
		data->fan_भाग[0] = (reg_array_पंचांगp[0] >> 4) & 0x03;
		data->fan_भाग[1] = (reg_array_पंचांगp[0] >> 6) & 0x03;
		data->fan_भाग[2] = (reg_array_पंचांगp[1] >> 6) & 0x03;
		data->fan_भाग[3] = reg_array_पंचांगp[2] & 0x07;
		data->fan_भाग[4] = (reg_array_पंचांगp[2] >> 4) & 0x07;

		/*
		 * The fan भागisor क्रम fans 0-2 get bit 2 from
		 * bits 5-7 respectively of vbat रेजिस्टर
		 */
		vbat_reg = w83791d_पढ़ो(client, W83791D_REG_VBAT);
		क्रम (i = 0; i < 3; i++)
			data->fan_भाग[i] |= (vbat_reg >> (3 + i)) & 0x04;

		/* Update PWM duty cycle */
		क्रम (i = 0; i < NUMBER_OF_PWM; i++) अणु
			data->pwm[i] =  w83791d_पढ़ो(client,
						W83791D_REG_PWM[i]);
		पूर्ण

		/* Update PWM enable status */
		क्रम (i = 0; i < 2; i++) अणु
			reg_array_पंचांगp[i] = w83791d_पढ़ो(client,
						W83791D_REG_FAN_CFG[i]);
		पूर्ण
		data->pwm_enable[0] = (reg_array_पंचांगp[0] >> 2) & 0x03;
		data->pwm_enable[1] = (reg_array_पंचांगp[0] >> 4) & 0x03;
		data->pwm_enable[2] = (reg_array_पंचांगp[1] >> 2) & 0x03;

		/* Update PWM target temperature */
		क्रम (i = 0; i < 3; i++) अणु
			data->temp_target[i] = w83791d_पढ़ो(client,
				W83791D_REG_TEMP_TARGET[i]) & 0x7f;
		पूर्ण

		/* Update PWM temperature tolerance */
		क्रम (i = 0; i < 2; i++) अणु
			reg_array_पंचांगp[i] = w83791d_पढ़ो(client,
					W83791D_REG_TEMP_TOL[i]);
		पूर्ण
		data->temp_tolerance[0] = reg_array_पंचांगp[0] & 0x0f;
		data->temp_tolerance[1] = (reg_array_पंचांगp[0] >> 4) & 0x0f;
		data->temp_tolerance[2] = reg_array_पंचांगp[1] & 0x0f;

		/* Update the first temperature sensor */
		क्रम (i = 0; i < 3; i++) अणु
			data->temp1[i] = w83791d_पढ़ो(client,
						W83791D_REG_TEMP1[i]);
		पूर्ण

		/* Update the rest of the temperature sensors */
		क्रम (i = 0; i < 2; i++) अणु
			क्रम (j = 0; j < 3; j++) अणु
				data->temp_add[i][j] =
					(w83791d_पढ़ो(client,
					W83791D_REG_TEMP_ADD[i][j * 2]) << 8) |
					w83791d_पढ़ो(client,
					W83791D_REG_TEMP_ADD[i][j * 2 + 1]);
			पूर्ण
		पूर्ण

		/* Update the realसमय status */
		data->alarms =
			w83791d_पढ़ो(client, W83791D_REG_ALARM1) +
			(w83791d_पढ़ो(client, W83791D_REG_ALARM2) << 8) +
			(w83791d_पढ़ो(client, W83791D_REG_ALARM3) << 16);

		/* Update the beep configuration inक्रमmation */
		data->beep_mask =
			w83791d_पढ़ो(client, W83791D_REG_BEEP_CTRL[0]) +
			(w83791d_पढ़ो(client, W83791D_REG_BEEP_CTRL[1]) << 8) +
			(w83791d_पढ़ो(client, W83791D_REG_BEEP_CTRL[2]) << 16);

		/* Extract global beep enable flag */
		data->beep_enable =
			(data->beep_mask >> GLOBAL_BEEP_ENABLE_SHIFT) & 0x01;

		/* Update the cpu voltage inक्रमmation */
		i = w83791d_पढ़ो(client, W83791D_REG_VID_FANDIV);
		data->vid = i & 0x0f;
		data->vid |= (w83791d_पढ़ो(client, W83791D_REG_DID_VID4) & 0x01)
				<< 4;

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

#अगर_घोषित DEBUG
	w83791d_prपूर्णांक_debug(data, dev);
#पूर्ण_अगर

	वापस data;
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम w83791d_prपूर्णांक_debug(काष्ठा w83791d_data *data, काष्ठा device *dev)
अणु
	पूर्णांक i = 0, j = 0;

	dev_dbg(dev, "======Start of w83791d debug values======\n");
	dev_dbg(dev, "%d set of Voltages: ===>\n", NUMBER_OF_VIN);
	क्रम (i = 0; i < NUMBER_OF_VIN; i++) अणु
		dev_dbg(dev, "vin[%d] is:     0x%02x\n", i, data->in[i]);
		dev_dbg(dev, "vin[%d] min is: 0x%02x\n", i, data->in_min[i]);
		dev_dbg(dev, "vin[%d] max is: 0x%02x\n", i, data->in_max[i]);
	पूर्ण
	dev_dbg(dev, "%d set of Fan Counts/Divisors: ===>\n", NUMBER_OF_FANIN);
	क्रम (i = 0; i < NUMBER_OF_FANIN; i++) अणु
		dev_dbg(dev, "fan[%d] is:     0x%02x\n", i, data->fan[i]);
		dev_dbg(dev, "fan[%d] min is: 0x%02x\n", i, data->fan_min[i]);
		dev_dbg(dev, "fan_div[%d] is: 0x%02x\n", i, data->fan_भाग[i]);
	पूर्ण

	/*
	 * temperature math is चिन्हित, but only prपूर्णांक out the
	 * bits that matter
	 */
	dev_dbg(dev, "%d set of Temperatures: ===>\n", NUMBER_OF_TEMPIN);
	क्रम (i = 0; i < 3; i++)
		dev_dbg(dev, "temp1[%d] is: 0x%02x\n", i, (u8) data->temp1[i]);
	क्रम (i = 0; i < 2; i++) अणु
		क्रम (j = 0; j < 3; j++) अणु
			dev_dbg(dev, "temp_add[%d][%d] is: 0x%04x\n", i, j,
				(u16) data->temp_add[i][j]);
		पूर्ण
	पूर्ण

	dev_dbg(dev, "Misc Information: ===>\n");
	dev_dbg(dev, "alarm is:     0x%08x\n", data->alarms);
	dev_dbg(dev, "beep_mask is: 0x%08x\n", data->beep_mask);
	dev_dbg(dev, "beep_enable is: %d\n", data->beep_enable);
	dev_dbg(dev, "vid is: 0x%02x\n", data->vid);
	dev_dbg(dev, "vrm is: 0x%02x\n", data->vrm);
	dev_dbg(dev, "=======End of w83791d debug values========\n");
	dev_dbg(dev, "\n");
पूर्ण
#पूर्ण_अगर

module_i2c_driver(w83791d_driver);

MODULE_AUTHOR("Charles Spirakis <bezaur@gmail.com>");
MODULE_DESCRIPTION("W83791D driver");
MODULE_LICENSE("GPL");
