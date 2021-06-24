<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * w83792d.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *	       monitoring
 * Copyright (C) 2004, 2005 Winbond Electronics Corp.
 *			    Shane Huang,
 *			    Ruकरोlf Marek <r.marek@assembler.cz>
 *
 * Note:
 * 1. This driver is only क्रम 2.6 kernel, 2.4 kernel need a dअगरferent driver.
 * 2. This driver is only क्रम Winbond W83792D C version device, there
 *     are also some motherboards with B version W83792D device. The
 *     calculation method to in6-in7(measured value, limits) is a little
 *     dअगरferent between C and B version. C or B version can be identअगरied
 *     by CR[0x49h].
 */

/*
 * Supports following chips:
 *
 * Chip		#vin	#fanin	#pwm	#temp	wchipid	vendid	i2c	ISA
 * w83792d	9	7	7	3	0x7a	0x5ca3	yes	no
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/jअगरfies.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2c, 0x2d, 0x2e, 0x2f,
						I2C_CLIENT_END पूर्ण;

/* Insmod parameters */

अटल अचिन्हित लघु क्रमce_subclients[4];
module_param_array(क्रमce_subclients, लघु, शून्य, 0);
MODULE_PARM_DESC(क्रमce_subclients,
		 "List of subclient addresses: {bus, clientaddr, subclientaddr1, subclientaddr2}");

अटल bool init;
module_param(init, bool, 0);
MODULE_PARM_DESC(init, "Set to one to force chip initialization");

/* The W83792D रेजिस्टरs */
अटल स्थिर u8 W83792D_REG_IN[9] = अणु
	0x20,	/* Vcore A in DataSheet */
	0x21,	/* Vcore B in DataSheet */
	0x22,	/* VIN0 in DataSheet */
	0x23,	/* VIN1 in DataSheet */
	0x24,	/* VIN2 in DataSheet */
	0x25,	/* VIN3 in DataSheet */
	0x26,	/* 5VCC in DataSheet */
	0xB0,	/* 5VSB in DataSheet */
	0xB1	/* VBAT in DataSheet */
पूर्ण;
#घोषणा W83792D_REG_LOW_BITS1 0x3E  /* Low Bits I in DataSheet */
#घोषणा W83792D_REG_LOW_BITS2 0x3F  /* Low Bits II in DataSheet */
अटल स्थिर u8 W83792D_REG_IN_MAX[9] = अणु
	0x2B,	/* Vcore A High Limit in DataSheet */
	0x2D,	/* Vcore B High Limit in DataSheet */
	0x2F,	/* VIN0 High Limit in DataSheet */
	0x31,	/* VIN1 High Limit in DataSheet */
	0x33,	/* VIN2 High Limit in DataSheet */
	0x35,	/* VIN3 High Limit in DataSheet */
	0x37,	/* 5VCC High Limit in DataSheet */
	0xB4,	/* 5VSB High Limit in DataSheet */
	0xB6	/* VBAT High Limit in DataSheet */
पूर्ण;
अटल स्थिर u8 W83792D_REG_IN_MIN[9] = अणु
	0x2C,	/* Vcore A Low Limit in DataSheet */
	0x2E,	/* Vcore B Low Limit in DataSheet */
	0x30,	/* VIN0 Low Limit in DataSheet */
	0x32,	/* VIN1 Low Limit in DataSheet */
	0x34,	/* VIN2 Low Limit in DataSheet */
	0x36,	/* VIN3 Low Limit in DataSheet */
	0x38,	/* 5VCC Low Limit in DataSheet */
	0xB5,	/* 5VSB Low Limit in DataSheet */
	0xB7	/* VBAT Low Limit in DataSheet */
पूर्ण;
अटल स्थिर u8 W83792D_REG_FAN[7] = अणु
	0x28,	/* FAN 1 Count in DataSheet */
	0x29,	/* FAN 2 Count in DataSheet */
	0x2A,	/* FAN 3 Count in DataSheet */
	0xB8,	/* FAN 4 Count in DataSheet */
	0xB9,	/* FAN 5 Count in DataSheet */
	0xBA,	/* FAN 6 Count in DataSheet */
	0xBE	/* FAN 7 Count in DataSheet */
पूर्ण;
अटल स्थिर u8 W83792D_REG_FAN_MIN[7] = अणु
	0x3B,	/* FAN 1 Count Low Limit in DataSheet */
	0x3C,	/* FAN 2 Count Low Limit in DataSheet */
	0x3D,	/* FAN 3 Count Low Limit in DataSheet */
	0xBB,	/* FAN 4 Count Low Limit in DataSheet */
	0xBC,	/* FAN 5 Count Low Limit in DataSheet */
	0xBD,	/* FAN 6 Count Low Limit in DataSheet */
	0xBF	/* FAN 7 Count Low Limit in DataSheet */
पूर्ण;
#घोषणा W83792D_REG_FAN_CFG 0x84	/* FAN Configuration in DataSheet */
अटल स्थिर u8 W83792D_REG_FAN_DIV[4] = अणु
	0x47,	/* contains FAN2 and FAN1 Divisor */
	0x5B,	/* contains FAN4 and FAN3 Divisor */
	0x5C,	/* contains FAN6 and FAN5 Divisor */
	0x9E	/* contains FAN7 Divisor. */
पूर्ण;
अटल स्थिर u8 W83792D_REG_PWM[7] = अणु
	0x81,	/* FAN 1 Duty Cycle, be used to control */
	0x83,	/* FAN 2 Duty Cycle, be used to control */
	0x94,	/* FAN 3 Duty Cycle, be used to control */
	0xA3,	/* FAN 4 Duty Cycle, be used to control */
	0xA4,	/* FAN 5 Duty Cycle, be used to control */
	0xA5,	/* FAN 6 Duty Cycle, be used to control */
	0xA6	/* FAN 7 Duty Cycle, be used to control */
पूर्ण;
#घोषणा W83792D_REG_BANK		0x4E
#घोषणा W83792D_REG_TEMP2_CONFIG	0xC2
#घोषणा W83792D_REG_TEMP3_CONFIG	0xCA

अटल स्थिर u8 W83792D_REG_TEMP1[3] = अणु
	0x27,	/* TEMP 1 in DataSheet */
	0x39,	/* TEMP 1 Over in DataSheet */
	0x3A,	/* TEMP 1 Hyst in DataSheet */
पूर्ण;

अटल स्थिर u8 W83792D_REG_TEMP_ADD[2][6] = अणु
	अणु 0xC0,		/* TEMP 2 in DataSheet */
	  0xC1,		/* TEMP 2(0.5 deg) in DataSheet */
	  0xC5,		/* TEMP 2 Over High part in DataSheet */
	  0xC6,		/* TEMP 2 Over Low part in DataSheet */
	  0xC3,		/* TEMP 2 Thyst High part in DataSheet */
	  0xC4 पूर्ण,	/* TEMP 2 Thyst Low part in DataSheet */
	अणु 0xC8,		/* TEMP 3 in DataSheet */
	  0xC9,		/* TEMP 3(0.5 deg) in DataSheet */
	  0xCD,		/* TEMP 3 Over High part in DataSheet */
	  0xCE,		/* TEMP 3 Over Low part in DataSheet */
	  0xCB,		/* TEMP 3 Thyst High part in DataSheet */
	  0xCC पूर्ण	/* TEMP 3 Thyst Low part in DataSheet */
पूर्ण;

अटल स्थिर u8 W83792D_REG_THERMAL[3] = अणु
	0x85,	/* SmartFanI: Fan1 target value */
	0x86,	/* SmartFanI: Fan2 target value */
	0x96	/* SmartFanI: Fan3 target value */
पूर्ण;

अटल स्थिर u8 W83792D_REG_TOLERANCE[3] = अणु
	0x87,	/* (bit3-0)SmartFan Fan1 tolerance */
	0x87,	/* (bit7-4)SmartFan Fan2 tolerance */
	0x97	/* (bit3-0)SmartFan Fan3 tolerance */
पूर्ण;

अटल स्थिर u8 W83792D_REG_POINTS[3][4] = अणु
	अणु 0x85,		/* SmartFanII: Fan1 temp poपूर्णांक 1 */
	  0xE3,		/* SmartFanII: Fan1 temp poपूर्णांक 2 */
	  0xE4,		/* SmartFanII: Fan1 temp poपूर्णांक 3 */
	  0xE5 पूर्ण,	/* SmartFanII: Fan1 temp poपूर्णांक 4 */
	अणु 0x86,		/* SmartFanII: Fan2 temp poपूर्णांक 1 */
	  0xE6,		/* SmartFanII: Fan2 temp poपूर्णांक 2 */
	  0xE7,		/* SmartFanII: Fan2 temp poपूर्णांक 3 */
	  0xE8 पूर्ण,	/* SmartFanII: Fan2 temp poपूर्णांक 4 */
	अणु 0x96,		/* SmartFanII: Fan3 temp poपूर्णांक 1 */
	  0xE9,		/* SmartFanII: Fan3 temp poपूर्णांक 2 */
	  0xEA,		/* SmartFanII: Fan3 temp poपूर्णांक 3 */
	  0xEB पूर्ण	/* SmartFanII: Fan3 temp poपूर्णांक 4 */
पूर्ण;

अटल स्थिर u8 W83792D_REG_LEVELS[3][4] = अणु
	अणु 0x88,		/* (bit3-0) SmartFanII: Fan1 Non-Stop */
	  0x88,		/* (bit7-4) SmartFanII: Fan1 Level 1 */
	  0xE0,		/* (bit7-4) SmartFanII: Fan1 Level 2 */
	  0xE0 पूर्ण,	/* (bit3-0) SmartFanII: Fan1 Level 3 */
	अणु 0x89,		/* (bit3-0) SmartFanII: Fan2 Non-Stop */
	  0x89,		/* (bit7-4) SmartFanII: Fan2 Level 1 */
	  0xE1,		/* (bit7-4) SmartFanII: Fan2 Level 2 */
	  0xE1 पूर्ण,	/* (bit3-0) SmartFanII: Fan2 Level 3 */
	अणु 0x98,		/* (bit3-0) SmartFanII: Fan3 Non-Stop */
	  0x98,		/* (bit7-4) SmartFanII: Fan3 Level 1 */
	  0xE2,		/* (bit7-4) SmartFanII: Fan3 Level 2 */
	  0xE2 पूर्ण	/* (bit3-0) SmartFanII: Fan3 Level 3 */
पूर्ण;

#घोषणा W83792D_REG_GPIO_EN		0x1A
#घोषणा W83792D_REG_CONFIG		0x40
#घोषणा W83792D_REG_VID_FANDIV		0x47
#घोषणा W83792D_REG_CHIPID		0x49
#घोषणा W83792D_REG_WCHIPID		0x58
#घोषणा W83792D_REG_CHIPMAN		0x4F
#घोषणा W83792D_REG_PIN			0x4B
#घोषणा W83792D_REG_I2C_SUBADDR		0x4A

#घोषणा W83792D_REG_ALARM1 0xA9		/* realसमय status रेजिस्टर1 */
#घोषणा W83792D_REG_ALARM2 0xAA		/* realसमय status रेजिस्टर2 */
#घोषणा W83792D_REG_ALARM3 0xAB		/* realसमय status रेजिस्टर3 */
#घोषणा W83792D_REG_CHASSIS 0x42	/* Bit 5: Case Open status bit */
#घोषणा W83792D_REG_CHASSIS_CLR 0x44	/* Bit 7: Case Open CLR_CHS/Reset bit */

/* control in0/in1 's limit modअगरiability */
#घोषणा W83792D_REG_VID_IN_B		0x17

#घोषणा W83792D_REG_VBAT		0x5D
#घोषणा W83792D_REG_I2C_ADDR		0x48

/*
 * Conversions. Rounding and limit checking is only करोne on the TO_REG
 * variants. Note that you should be a bit careful with which arguments
 * these macros are called: arguments may be evaluated more than once.
 * Fixing this is just not worth it.
 */
#घोषणा IN_FROM_REG(nr, val) (((nr) <= 1) ? ((val) * 2) : \
		((((nr) == 6) || ((nr) == 7)) ? ((val) * 6) : ((val) * 4)))
#घोषणा IN_TO_REG(nr, val) (((nr) <= 1) ? ((val) / 2) : \
		((((nr) == 6) || ((nr) == 7)) ? ((val) / 6) : ((val) / 4)))

अटल अंतरभूत u8
FAN_TO_REG(दीर्घ rpm, पूर्णांक भाग)
अणु
	अगर (rpm == 0)
		वापस 255;
	rpm = clamp_val(rpm, 1, 1000000);
	वापस clamp_val((1350000 + rpm * भाग / 2) / (rpm * भाग), 1, 254);
पूर्ण

#घोषणा FAN_FROM_REG(val, भाग)	((val) == 0   ? -1 : \
				((val) == 255 ? 0 : \
						1350000 / ((val) * (भाग))))

/* क्रम temp1 */
#घोषणा TEMP1_TO_REG(val)	(clamp_val(((val) < 0 ? (val) + 0x100 * 1000 \
						      : (val)) / 1000, 0, 0xff))
#घोषणा TEMP1_FROM_REG(val)	(((val) & 0x80 ? (val)-0x100 : (val)) * 1000)
/* क्रम temp2 and temp3, because they need additional resolution */
#घोषणा TEMP_ADD_FROM_REG(val1, val2) \
	((((val1) & 0x80 ? (val1)-0x100 \
		: (val1)) * 1000) + ((val2 & 0x80) ? 500 : 0))
#घोषणा TEMP_ADD_TO_REG_HIGH(val) \
	(clamp_val(((val) < 0 ? (val) + 0x100 * 1000 : (val)) / 1000, 0, 0xff))
#घोषणा TEMP_ADD_TO_REG_LOW(val)	((val%1000) ? 0x80 : 0x00)

#घोषणा DIV_FROM_REG(val)		(1 << (val))

अटल अंतरभूत u8
DIV_TO_REG(दीर्घ val)
अणु
	पूर्णांक i;
	val = clamp_val(val, 1, 128) >> 1;
	क्रम (i = 0; i < 7; i++) अणु
		अगर (val == 0)
			अवरोध;
		val >>= 1;
	पूर्ण
	वापस (u8)i;
पूर्ण

काष्ठा w83792d_data अणु
	काष्ठा device *hwmon_dev;

	काष्ठा mutex update_lock;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	/* array of 2 poपूर्णांकers to subclients */
	काष्ठा i2c_client *lm75[2];

	u8 in[9];		/* Register value */
	u8 in_max[9];		/* Register value */
	u8 in_min[9];		/* Register value */
	u16 low_bits;		/* Additional resolution to voltage in6-0 */
	u8 fan[7];		/* Register value */
	u8 fan_min[7];		/* Register value */
	u8 temp1[3];		/* current, over, thyst */
	u8 temp_add[2][6];	/* Register value */
	u8 fan_भाग[7];		/* Register encoding, shअगरted right */
	u8 pwm[7];		/* The 7 PWM outमाला_दो */
	u8 pwmenable[3];
	u32 alarms;		/* realसमय status रेजिस्टर encoding,combined */
	u8 chassis;		/* Chassis status */
	u8 thermal_cruise[3];	/* Smart FanI: Fan1,2,3 target value */
	u8 tolerance[3];	/* Fan1,2,3 tolerance(Smart Fan I/II) */
	u8 sf2_poपूर्णांकs[3][4];	/* Smart FanII: Fan1,2,3 temperature poपूर्णांकs */
	u8 sf2_levels[3][4];	/* Smart FanII: Fan1,2,3 duty cycle levels */
पूर्ण;

अटल पूर्णांक w83792d_probe(काष्ठा i2c_client *client);
अटल पूर्णांक w83792d_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info);
अटल पूर्णांक w83792d_हटाओ(काष्ठा i2c_client *client);
अटल काष्ठा w83792d_data *w83792d_update_device(काष्ठा device *dev);

#अगर_घोषित DEBUG
अटल व्योम w83792d_prपूर्णांक_debug(काष्ठा w83792d_data *data, काष्ठा device *dev);
#पूर्ण_अगर

अटल व्योम w83792d_init_client(काष्ठा i2c_client *client);

अटल स्थिर काष्ठा i2c_device_id w83792d_id[] = अणु
	अणु "w83792d", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, w83792d_id);

अटल काष्ठा i2c_driver w83792d_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name = "w83792d",
	पूर्ण,
	.probe_new	= w83792d_probe,
	.हटाओ		= w83792d_हटाओ,
	.id_table	= w83792d_id,
	.detect		= w83792d_detect,
	.address_list	= normal_i2c,
पूर्ण;

अटल अंतरभूत दीर्घ in_count_from_reg(पूर्णांक nr, काष्ठा w83792d_data *data)
अणु
	/* in7 and in8 करो not have low bits, but the क्रमmula still works */
	वापस (data->in[nr] << 2) | ((data->low_bits >> (2 * nr)) & 0x03);
पूर्ण

/*
 * The SMBus locks itself. The Winbond W83792D chip has a bank रेजिस्टर,
 * but the driver only accesses रेजिस्टरs in bank 0, so we करोn't have
 * to चयन banks and lock access between चयनes.
 */
अटल अंतरभूत पूर्णांक w83792d_पढ़ो_value(काष्ठा i2c_client *client, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल अंतरभूत पूर्णांक
w83792d_ग_लिखो_value(काष्ठा i2c_client *client, u8 reg, u8 value)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

/* following are the sysfs callback functions */
अटल sमाप_प्रकार show_in(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा w83792d_data *data = w83792d_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n",
		       IN_FROM_REG(nr, in_count_from_reg(nr, data)));
पूर्ण

#घोषणा show_in_reg(reg) \
अटल sमाप_प्रकार show_##reg(काष्ठा device *dev, काष्ठा device_attribute *attr, \
			अक्षर *buf) \
अणु \
	काष्ठा sensor_device_attribute *sensor_attr \
		= to_sensor_dev_attr(attr); \
	पूर्णांक nr = sensor_attr->index; \
	काष्ठा w83792d_data *data = w83792d_update_device(dev); \
	वापस प्र_लिखो(buf, "%ld\n", \
		       (दीर्घ)(IN_FROM_REG(nr, data->reg[nr]) * 4)); \
पूर्ण

show_in_reg(in_min);
show_in_reg(in_max);

#घोषणा store_in_reg(REG, reg) \
अटल sमाप_प्रकार store_in_##reg(काष्ठा device *dev, \
				काष्ठा device_attribute *attr, \
				स्थिर अक्षर *buf, माप_प्रकार count) \
अणु \
	काष्ठा sensor_device_attribute *sensor_attr \
			= to_sensor_dev_attr(attr); \
	पूर्णांक nr = sensor_attr->index; \
	काष्ठा i2c_client *client = to_i2c_client(dev); \
	काष्ठा w83792d_data *data = i2c_get_clientdata(client); \
	अचिन्हित दीर्घ val; \
	पूर्णांक err = kम_से_अदीर्घ(buf, 10, &val); \
	अगर (err) \
		वापस err; \
	mutex_lock(&data->update_lock); \
	data->in_##reg[nr] = clamp_val(IN_TO_REG(nr, val) / 4, 0, 255); \
	w83792d_ग_लिखो_value(client, W83792D_REG_IN_##REG[nr], \
			    data->in_##reg[nr]); \
	mutex_unlock(&data->update_lock); \
	 \
	वापस count; \
पूर्ण
store_in_reg(MIN, min);
store_in_reg(MAX, max);

#घोषणा show_fan_reg(reg) \
अटल sमाप_प्रकार show_##reg(काष्ठा device *dev, काष्ठा device_attribute *attr, \
			अक्षर *buf) \
अणु \
	काष्ठा sensor_device_attribute *sensor_attr \
			= to_sensor_dev_attr(attr); \
	पूर्णांक nr = sensor_attr->index - 1; \
	काष्ठा w83792d_data *data = w83792d_update_device(dev); \
	वापस प्र_लिखो(buf, "%d\n", \
		FAN_FROM_REG(data->reg[nr], DIV_FROM_REG(data->fan_भाग[nr]))); \
पूर्ण

show_fan_reg(fan);
show_fan_reg(fan_min);

अटल sमाप_प्रकार
store_fan_min(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index - 1;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83792d_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan_min[nr] = FAN_TO_REG(val, DIV_FROM_REG(data->fan_भाग[nr]));
	w83792d_ग_लिखो_value(client, W83792D_REG_FAN_MIN[nr],
				data->fan_min[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_fan_भाग(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा w83792d_data *data = w83792d_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", DIV_FROM_REG(data->fan_भाग[nr - 1]));
पूर्ण

/*
 * Note: we save and restore the fan minimum here, because its value is
 * determined in part by the fan भागisor.  This follows the principle of
 * least surprise; the user करोesn't expect the fan minimum to change just
 * because the भागisor changed.
 */
अटल sमाप_प्रकार
store_fan_भाग(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index - 1;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83792d_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ min;
	/*u8 reg;*/
	u8 fan_भाग_reg = 0;
	u8 पंचांगp_fan_भाग;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	/* Save fan_min */
	mutex_lock(&data->update_lock);
	min = FAN_FROM_REG(data->fan_min[nr],
			   DIV_FROM_REG(data->fan_भाग[nr]));

	data->fan_भाग[nr] = DIV_TO_REG(val);

	fan_भाग_reg = w83792d_पढ़ो_value(client, W83792D_REG_FAN_DIV[nr >> 1]);
	fan_भाग_reg &= (nr & 0x01) ? 0x8f : 0xf8;
	पंचांगp_fan_भाग = (nr & 0x01) ? (((data->fan_भाग[nr]) << 4) & 0x70)
					: ((data->fan_भाग[nr]) & 0x07);
	w83792d_ग_लिखो_value(client, W83792D_REG_FAN_DIV[nr >> 1],
					fan_भाग_reg | पंचांगp_fan_भाग);

	/* Restore fan_min */
	data->fan_min[nr] = FAN_TO_REG(min, DIV_FROM_REG(data->fan_भाग[nr]));
	w83792d_ग_लिखो_value(client, W83792D_REG_FAN_MIN[nr], data->fan_min[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* पढ़ो/ग_लिखो the temperature1, includes measured value and limits */

अटल sमाप_प्रकार show_temp1(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा w83792d_data *data = w83792d_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP1_FROM_REG(data->temp1[nr]));
पूर्ण

अटल sमाप_प्रकार store_temp1(काष्ठा device *dev, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83792d_data *data = i2c_get_clientdata(client);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp1[nr] = TEMP1_TO_REG(val);
	w83792d_ग_लिखो_value(client, W83792D_REG_TEMP1[nr],
		data->temp1[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* पढ़ो/ग_लिखो the temperature2-3, includes measured value and limits */

अटल sमाप_प्रकार show_temp23(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr
	  = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा w83792d_data *data = w83792d_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n",
		(दीर्घ)TEMP_ADD_FROM_REG(data->temp_add[nr][index],
			data->temp_add[nr][index+1]));
पूर्ण

अटल sमाप_प्रकार store_temp23(काष्ठा device *dev, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr
	  = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83792d_data *data = i2c_get_clientdata(client);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_add[nr][index] = TEMP_ADD_TO_REG_HIGH(val);
	data->temp_add[nr][index+1] = TEMP_ADD_TO_REG_LOW(val);
	w83792d_ग_लिखो_value(client, W83792D_REG_TEMP_ADD[nr][index],
		data->temp_add[nr][index]);
	w83792d_ग_लिखो_value(client, W83792D_REG_TEMP_ADD[nr][index+1],
		data->temp_add[nr][index+1]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* get realसमय status of all sensors items: voltage, temp, fan */
अटल sमाप_प्रकार
alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83792d_data *data = w83792d_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->alarms);
पूर्ण

अटल sमाप_प्रकार show_alarm(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा w83792d_data *data = w83792d_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", (data->alarms >> nr) & 1);
पूर्ण

अटल sमाप_प्रकार
show_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा w83792d_data *data = w83792d_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", (data->pwm[nr] & 0x0f) << 4);
पूर्ण

अटल sमाप_प्रकार
show_pwmenable(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index - 1;
	काष्ठा w83792d_data *data = w83792d_update_device(dev);
	दीर्घ pwm_enable_पंचांगp = 1;

	चयन (data->pwmenable[nr]) अणु
	हाल 0:
		pwm_enable_पंचांगp = 1; /* manual mode */
		अवरोध;
	हाल 1:
		pwm_enable_पंचांगp = 3; /*thermal cruise/Smart Fan I */
		अवरोध;
	हाल 2:
		pwm_enable_पंचांगp = 2; /* Smart Fan II */
		अवरोध;
	पूर्ण

	वापस प्र_लिखो(buf, "%ld\n", pwm_enable_पंचांगp);
पूर्ण

अटल sमाप_प्रकार
store_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83792d_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;
	val = clamp_val(val, 0, 255) >> 4;

	mutex_lock(&data->update_lock);
	val |= w83792d_पढ़ो_value(client, W83792D_REG_PWM[nr]) & 0xf0;
	data->pwm[nr] = val;
	w83792d_ग_लिखो_value(client, W83792D_REG_PWM[nr], data->pwm[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
store_pwmenable(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index - 1;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83792d_data *data = i2c_get_clientdata(client);
	u8 fan_cfg_पंचांगp, cfg1_पंचांगp, cfg2_पंचांगp, cfg3_पंचांगp, cfg4_पंचांगp;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val < 1 || val > 3)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	चयन (val) अणु
	हाल 1:
		data->pwmenable[nr] = 0; /* manual mode */
		अवरोध;
	हाल 2:
		data->pwmenable[nr] = 2; /* Smart Fan II */
		अवरोध;
	हाल 3:
		data->pwmenable[nr] = 1; /* thermal cruise/Smart Fan I */
		अवरोध;
	पूर्ण
	cfg1_पंचांगp = data->pwmenable[0];
	cfg2_पंचांगp = (data->pwmenable[1]) << 2;
	cfg3_पंचांगp = (data->pwmenable[2]) << 4;
	cfg4_पंचांगp = w83792d_पढ़ो_value(client, W83792D_REG_FAN_CFG) & 0xc0;
	fan_cfg_पंचांगp = ((cfg4_पंचांगp | cfg3_पंचांगp) | cfg2_पंचांगp) | cfg1_पंचांगp;
	w83792d_ग_लिखो_value(client, W83792D_REG_FAN_CFG, fan_cfg_पंचांगp);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_pwm_mode(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा w83792d_data *data = w83792d_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->pwm[nr] >> 7);
पूर्ण

अटल sमाप_प्रकार
store_pwm_mode(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83792d_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;
	अगर (val > 1)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->pwm[nr] = w83792d_पढ़ो_value(client, W83792D_REG_PWM[nr]);
	अगर (val) अणु			/* PWM mode */
		data->pwm[nr] |= 0x80;
	पूर्ण अन्यथा अणु			/* DC mode */
		data->pwm[nr] &= 0x7f;
	पूर्ण
	w83792d_ग_लिखो_value(client, W83792D_REG_PWM[nr], data->pwm[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
पूर्णांकrusion0_alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      अक्षर *buf)
अणु
	काष्ठा w83792d_data *data = w83792d_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->chassis);
पूर्ण

अटल sमाप_प्रकार
पूर्णांकrusion0_alarm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83792d_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	u8 reg;

	अगर (kम_से_अदीर्घ(buf, 10, &val) || val != 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	reg = w83792d_पढ़ो_value(client, W83792D_REG_CHASSIS_CLR);
	w83792d_ग_लिखो_value(client, W83792D_REG_CHASSIS_CLR, reg | 0x80);
	data->valid = 0;		/* Force cache refresh */
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* For Smart Fan I / Thermal Cruise */
अटल sमाप_प्रकार
show_thermal_cruise(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा w83792d_data *data = w83792d_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", (दीर्घ)data->thermal_cruise[nr-1]);
पूर्ण

अटल sमाप_प्रकार
store_thermal_cruise(काष्ठा device *dev, काष्ठा device_attribute *attr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index - 1;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83792d_data *data = i2c_get_clientdata(client);
	u8 target_पंचांगp = 0, target_mask = 0;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	target_पंचांगp = val;
	target_पंचांगp = target_पंचांगp & 0x7f;
	mutex_lock(&data->update_lock);
	target_mask = w83792d_पढ़ो_value(client,
					 W83792D_REG_THERMAL[nr]) & 0x80;
	data->thermal_cruise[nr] = clamp_val(target_पंचांगp, 0, 255);
	w83792d_ग_लिखो_value(client, W83792D_REG_THERMAL[nr],
		(data->thermal_cruise[nr]) | target_mask);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* For Smart Fan I/Thermal Cruise and Smart Fan II */
अटल sमाप_प्रकार
show_tolerance(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index;
	काष्ठा w83792d_data *data = w83792d_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", (दीर्घ)data->tolerance[nr-1]);
पूर्ण

अटल sमाप_प्रकार
store_tolerance(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	पूर्णांक nr = sensor_attr->index - 1;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83792d_data *data = i2c_get_clientdata(client);
	u8 tol_पंचांगp, tol_mask;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	tol_mask = w83792d_पढ़ो_value(client,
		W83792D_REG_TOLERANCE[nr]) & ((nr == 1) ? 0x0f : 0xf0);
	tol_पंचांगp = clamp_val(val, 0, 15);
	tol_पंचांगp &= 0x0f;
	data->tolerance[nr] = tol_पंचांगp;
	अगर (nr == 1)
		tol_पंचांगp <<= 4;
	w83792d_ग_लिखो_value(client, W83792D_REG_TOLERANCE[nr],
		tol_mask | tol_पंचांगp);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* For Smart Fan II */
अटल sमाप_प्रकार
show_sf2_poपूर्णांक(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr
	  = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा w83792d_data *data = w83792d_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", (दीर्घ)data->sf2_poपूर्णांकs[index-1][nr-1]);
पूर्ण

अटल sमाप_प्रकार
store_sf2_poपूर्णांक(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr
	  = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr - 1;
	पूर्णांक index = sensor_attr->index - 1;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83792d_data *data = i2c_get_clientdata(client);
	u8 mask_पंचांगp = 0;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->sf2_poपूर्णांकs[index][nr] = clamp_val(val, 0, 127);
	mask_पंचांगp = w83792d_पढ़ो_value(client,
					W83792D_REG_POINTS[index][nr]) & 0x80;
	w83792d_ग_लिखो_value(client, W83792D_REG_POINTS[index][nr],
		mask_पंचांगp|data->sf2_poपूर्णांकs[index][nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_sf2_level(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr
	  = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा w83792d_data *data = w83792d_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n",
			(((data->sf2_levels[index-1][nr]) * 100) / 15));
पूर्ण

अटल sमाप_प्रकार
store_sf2_level(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr
	  = to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index - 1;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83792d_data *data = i2c_get_clientdata(client);
	u8 mask_पंचांगp = 0, level_पंचांगp = 0;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->sf2_levels[index][nr] = clamp_val((val * 15) / 100, 0, 15);
	mask_पंचांगp = w83792d_पढ़ो_value(client, W83792D_REG_LEVELS[index][nr])
		& ((nr == 3) ? 0xf0 : 0x0f);
	अगर (nr == 3)
		level_पंचांगp = data->sf2_levels[index][nr];
	अन्यथा
		level_पंचांगp = data->sf2_levels[index][nr] << 4;
	w83792d_ग_लिखो_value(client, W83792D_REG_LEVELS[index][nr],
			    level_पंचांगp | mask_पंचांगp);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण


अटल पूर्णांक
w83792d_detect_subclients(काष्ठा i2c_client *new_client)
अणु
	पूर्णांक i, id;
	पूर्णांक address = new_client->addr;
	u8 val;
	काष्ठा i2c_adapter *adapter = new_client->adapter;
	काष्ठा w83792d_data *data = i2c_get_clientdata(new_client);

	id = i2c_adapter_id(adapter);
	अगर (क्रमce_subclients[0] == id && क्रमce_subclients[1] == address) अणु
		क्रम (i = 2; i <= 3; i++) अणु
			अगर (क्रमce_subclients[i] < 0x48 ||
			    क्रमce_subclients[i] > 0x4f) अणु
				dev_err(&new_client->dev,
					"invalid subclient address %d; must be 0x48-0x4f\n",
					क्रमce_subclients[i]);
				वापस -ENODEV;
			पूर्ण
		पूर्ण
		w83792d_ग_लिखो_value(new_client, W83792D_REG_I2C_SUBADDR,
					(क्रमce_subclients[2] & 0x07) |
					((क्रमce_subclients[3] & 0x07) << 4));
	पूर्ण

	val = w83792d_पढ़ो_value(new_client, W83792D_REG_I2C_SUBADDR);
	अगर (!(val & 0x08))
		data->lm75[0] = devm_i2c_new_dummy_device(&new_client->dev, adapter,
							  0x48 + (val & 0x7));
	अगर (!(val & 0x80)) अणु
		अगर (!IS_ERR(data->lm75[0]) &&
			((val & 0x7) == ((val >> 4) & 0x7))) अणु
			dev_err(&new_client->dev,
				"duplicate addresses 0x%x, use force_subclient\n",
				data->lm75[0]->addr);
			वापस -ENODEV;
		पूर्ण
		data->lm75[1] = devm_i2c_new_dummy_device(&new_client->dev, adapter,
							  0x48 + ((val >> 4) & 0x7));
	पूर्ण

	वापस 0;
पूर्ण

अटल SENSOR_DEVICE_ATTR(in0_input, S_IRUGO, show_in, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(in1_input, S_IRUGO, show_in, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(in2_input, S_IRUGO, show_in, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(in3_input, S_IRUGO, show_in, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(in4_input, S_IRUGO, show_in, शून्य, 4);
अटल SENSOR_DEVICE_ATTR(in5_input, S_IRUGO, show_in, शून्य, 5);
अटल SENSOR_DEVICE_ATTR(in6_input, S_IRUGO, show_in, शून्य, 6);
अटल SENSOR_DEVICE_ATTR(in7_input, S_IRUGO, show_in, शून्य, 7);
अटल SENSOR_DEVICE_ATTR(in8_input, S_IRUGO, show_in, शून्य, 8);
अटल SENSOR_DEVICE_ATTR(in0_min, S_IWUSR | S_IRUGO,
			show_in_min, store_in_min, 0);
अटल SENSOR_DEVICE_ATTR(in1_min, S_IWUSR | S_IRUGO,
			show_in_min, store_in_min, 1);
अटल SENSOR_DEVICE_ATTR(in2_min, S_IWUSR | S_IRUGO,
			show_in_min, store_in_min, 2);
अटल SENSOR_DEVICE_ATTR(in3_min, S_IWUSR | S_IRUGO,
			show_in_min, store_in_min, 3);
अटल SENSOR_DEVICE_ATTR(in4_min, S_IWUSR | S_IRUGO,
			show_in_min, store_in_min, 4);
अटल SENSOR_DEVICE_ATTR(in5_min, S_IWUSR | S_IRUGO,
			show_in_min, store_in_min, 5);
अटल SENSOR_DEVICE_ATTR(in6_min, S_IWUSR | S_IRUGO,
			show_in_min, store_in_min, 6);
अटल SENSOR_DEVICE_ATTR(in7_min, S_IWUSR | S_IRUGO,
			show_in_min, store_in_min, 7);
अटल SENSOR_DEVICE_ATTR(in8_min, S_IWUSR | S_IRUGO,
			show_in_min, store_in_min, 8);
अटल SENSOR_DEVICE_ATTR(in0_max, S_IWUSR | S_IRUGO,
			show_in_max, store_in_max, 0);
अटल SENSOR_DEVICE_ATTR(in1_max, S_IWUSR | S_IRUGO,
			show_in_max, store_in_max, 1);
अटल SENSOR_DEVICE_ATTR(in2_max, S_IWUSR | S_IRUGO,
			show_in_max, store_in_max, 2);
अटल SENSOR_DEVICE_ATTR(in3_max, S_IWUSR | S_IRUGO,
			show_in_max, store_in_max, 3);
अटल SENSOR_DEVICE_ATTR(in4_max, S_IWUSR | S_IRUGO,
			show_in_max, store_in_max, 4);
अटल SENSOR_DEVICE_ATTR(in5_max, S_IWUSR | S_IRUGO,
			show_in_max, store_in_max, 5);
अटल SENSOR_DEVICE_ATTR(in6_max, S_IWUSR | S_IRUGO,
			show_in_max, store_in_max, 6);
अटल SENSOR_DEVICE_ATTR(in7_max, S_IWUSR | S_IRUGO,
			show_in_max, store_in_max, 7);
अटल SENSOR_DEVICE_ATTR(in8_max, S_IWUSR | S_IRUGO,
			show_in_max, store_in_max, 8);
अटल SENSOR_DEVICE_ATTR_2(temp1_input, S_IRUGO, show_temp1, शून्य, 0, 0);
अटल SENSOR_DEVICE_ATTR_2(temp2_input, S_IRUGO, show_temp23, शून्य, 0, 0);
अटल SENSOR_DEVICE_ATTR_2(temp3_input, S_IRUGO, show_temp23, शून्य, 1, 0);
अटल SENSOR_DEVICE_ATTR_2(temp1_max, S_IRUGO | S_IWUSR,
			show_temp1, store_temp1, 0, 1);
अटल SENSOR_DEVICE_ATTR_2(temp2_max, S_IRUGO | S_IWUSR, show_temp23,
			store_temp23, 0, 2);
अटल SENSOR_DEVICE_ATTR_2(temp3_max, S_IRUGO | S_IWUSR, show_temp23,
			store_temp23, 1, 2);
अटल SENSOR_DEVICE_ATTR_2(temp1_max_hyst, S_IRUGO | S_IWUSR,
			show_temp1, store_temp1, 0, 2);
अटल SENSOR_DEVICE_ATTR_2(temp2_max_hyst, S_IRUGO | S_IWUSR,
			show_temp23, store_temp23, 0, 4);
अटल SENSOR_DEVICE_ATTR_2(temp3_max_hyst, S_IRUGO | S_IWUSR,
			show_temp23, store_temp23, 1, 4);
अटल DEVICE_ATTR_RO(alarms);
अटल SENSOR_DEVICE_ATTR(in0_alarm, S_IRUGO, show_alarm, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(in1_alarm, S_IRUGO, show_alarm, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(temp1_alarm, S_IRUGO, show_alarm, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(temp2_alarm, S_IRUGO, show_alarm, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(temp3_alarm, S_IRUGO, show_alarm, शून्य, 4);
अटल SENSOR_DEVICE_ATTR(fan1_alarm, S_IRUGO, show_alarm, शून्य, 5);
अटल SENSOR_DEVICE_ATTR(fan2_alarm, S_IRUGO, show_alarm, शून्य, 6);
अटल SENSOR_DEVICE_ATTR(fan3_alarm, S_IRUGO, show_alarm, शून्य, 7);
अटल SENSOR_DEVICE_ATTR(in2_alarm, S_IRUGO, show_alarm, शून्य, 8);
अटल SENSOR_DEVICE_ATTR(in3_alarm, S_IRUGO, show_alarm, शून्य, 9);
अटल SENSOR_DEVICE_ATTR(in4_alarm, S_IRUGO, show_alarm, शून्य, 10);
अटल SENSOR_DEVICE_ATTR(in5_alarm, S_IRUGO, show_alarm, शून्य, 11);
अटल SENSOR_DEVICE_ATTR(in6_alarm, S_IRUGO, show_alarm, शून्य, 12);
अटल SENSOR_DEVICE_ATTR(fan7_alarm, S_IRUGO, show_alarm, शून्य, 15);
अटल SENSOR_DEVICE_ATTR(in7_alarm, S_IRUGO, show_alarm, शून्य, 19);
अटल SENSOR_DEVICE_ATTR(in8_alarm, S_IRUGO, show_alarm, शून्य, 20);
अटल SENSOR_DEVICE_ATTR(fan4_alarm, S_IRUGO, show_alarm, शून्य, 21);
अटल SENSOR_DEVICE_ATTR(fan5_alarm, S_IRUGO, show_alarm, शून्य, 22);
अटल SENSOR_DEVICE_ATTR(fan6_alarm, S_IRUGO, show_alarm, शून्य, 23);
अटल DEVICE_ATTR_RW(पूर्णांकrusion0_alarm);
अटल SENSOR_DEVICE_ATTR(pwm1, S_IWUSR | S_IRUGO, show_pwm, store_pwm, 0);
अटल SENSOR_DEVICE_ATTR(pwm2, S_IWUSR | S_IRUGO, show_pwm, store_pwm, 1);
अटल SENSOR_DEVICE_ATTR(pwm3, S_IWUSR | S_IRUGO, show_pwm, store_pwm, 2);
अटल SENSOR_DEVICE_ATTR(pwm4, S_IWUSR | S_IRUGO, show_pwm, store_pwm, 3);
अटल SENSOR_DEVICE_ATTR(pwm5, S_IWUSR | S_IRUGO, show_pwm, store_pwm, 4);
अटल SENSOR_DEVICE_ATTR(pwm6, S_IWUSR | S_IRUGO, show_pwm, store_pwm, 5);
अटल SENSOR_DEVICE_ATTR(pwm7, S_IWUSR | S_IRUGO, show_pwm, store_pwm, 6);
अटल SENSOR_DEVICE_ATTR(pwm1_enable, S_IWUSR | S_IRUGO,
			show_pwmenable, store_pwmenable, 1);
अटल SENSOR_DEVICE_ATTR(pwm2_enable, S_IWUSR | S_IRUGO,
			show_pwmenable, store_pwmenable, 2);
अटल SENSOR_DEVICE_ATTR(pwm3_enable, S_IWUSR | S_IRUGO,
			show_pwmenable, store_pwmenable, 3);
अटल SENSOR_DEVICE_ATTR(pwm1_mode, S_IWUSR | S_IRUGO,
			show_pwm_mode, store_pwm_mode, 0);
अटल SENSOR_DEVICE_ATTR(pwm2_mode, S_IWUSR | S_IRUGO,
			show_pwm_mode, store_pwm_mode, 1);
अटल SENSOR_DEVICE_ATTR(pwm3_mode, S_IWUSR | S_IRUGO,
			show_pwm_mode, store_pwm_mode, 2);
अटल SENSOR_DEVICE_ATTR(pwm4_mode, S_IWUSR | S_IRUGO,
			show_pwm_mode, store_pwm_mode, 3);
अटल SENSOR_DEVICE_ATTR(pwm5_mode, S_IWUSR | S_IRUGO,
			show_pwm_mode, store_pwm_mode, 4);
अटल SENSOR_DEVICE_ATTR(pwm6_mode, S_IWUSR | S_IRUGO,
			show_pwm_mode, store_pwm_mode, 5);
अटल SENSOR_DEVICE_ATTR(pwm7_mode, S_IWUSR | S_IRUGO,
			show_pwm_mode, store_pwm_mode, 6);
अटल SENSOR_DEVICE_ATTR(tolerance1, S_IWUSR | S_IRUGO,
			show_tolerance, store_tolerance, 1);
अटल SENSOR_DEVICE_ATTR(tolerance2, S_IWUSR | S_IRUGO,
			show_tolerance, store_tolerance, 2);
अटल SENSOR_DEVICE_ATTR(tolerance3, S_IWUSR | S_IRUGO,
			show_tolerance, store_tolerance, 3);
अटल SENSOR_DEVICE_ATTR(thermal_cruise1, S_IWUSR | S_IRUGO,
			show_thermal_cruise, store_thermal_cruise, 1);
अटल SENSOR_DEVICE_ATTR(thermal_cruise2, S_IWUSR | S_IRUGO,
			show_thermal_cruise, store_thermal_cruise, 2);
अटल SENSOR_DEVICE_ATTR(thermal_cruise3, S_IWUSR | S_IRUGO,
			show_thermal_cruise, store_thermal_cruise, 3);
अटल SENSOR_DEVICE_ATTR_2(sf2_poपूर्णांक1_fan1, S_IRUGO | S_IWUSR,
			show_sf2_poपूर्णांक, store_sf2_poपूर्णांक, 1, 1);
अटल SENSOR_DEVICE_ATTR_2(sf2_poपूर्णांक2_fan1, S_IRUGO | S_IWUSR,
			show_sf2_poपूर्णांक, store_sf2_poपूर्णांक, 2, 1);
अटल SENSOR_DEVICE_ATTR_2(sf2_poपूर्णांक3_fan1, S_IRUGO | S_IWUSR,
			show_sf2_poपूर्णांक, store_sf2_poपूर्णांक, 3, 1);
अटल SENSOR_DEVICE_ATTR_2(sf2_poपूर्णांक4_fan1, S_IRUGO | S_IWUSR,
			show_sf2_poपूर्णांक, store_sf2_poपूर्णांक, 4, 1);
अटल SENSOR_DEVICE_ATTR_2(sf2_poपूर्णांक1_fan2, S_IRUGO | S_IWUSR,
			show_sf2_poपूर्णांक, store_sf2_poपूर्णांक, 1, 2);
अटल SENSOR_DEVICE_ATTR_2(sf2_poपूर्णांक2_fan2, S_IRUGO | S_IWUSR,
			show_sf2_poपूर्णांक, store_sf2_poपूर्णांक, 2, 2);
अटल SENSOR_DEVICE_ATTR_2(sf2_poपूर्णांक3_fan2, S_IRUGO | S_IWUSR,
			show_sf2_poपूर्णांक, store_sf2_poपूर्णांक, 3, 2);
अटल SENSOR_DEVICE_ATTR_2(sf2_poपूर्णांक4_fan2, S_IRUGO | S_IWUSR,
			show_sf2_poपूर्णांक, store_sf2_poपूर्णांक, 4, 2);
अटल SENSOR_DEVICE_ATTR_2(sf2_poपूर्णांक1_fan3, S_IRUGO | S_IWUSR,
			show_sf2_poपूर्णांक, store_sf2_poपूर्णांक, 1, 3);
अटल SENSOR_DEVICE_ATTR_2(sf2_poपूर्णांक2_fan3, S_IRUGO | S_IWUSR,
			show_sf2_poपूर्णांक, store_sf2_poपूर्णांक, 2, 3);
अटल SENSOR_DEVICE_ATTR_2(sf2_poपूर्णांक3_fan3, S_IRUGO | S_IWUSR,
			show_sf2_poपूर्णांक, store_sf2_poपूर्णांक, 3, 3);
अटल SENSOR_DEVICE_ATTR_2(sf2_poपूर्णांक4_fan3, S_IRUGO | S_IWUSR,
			show_sf2_poपूर्णांक, store_sf2_poपूर्णांक, 4, 3);
अटल SENSOR_DEVICE_ATTR_2(sf2_level1_fan1, S_IRUGO | S_IWUSR,
			show_sf2_level, store_sf2_level, 1, 1);
अटल SENSOR_DEVICE_ATTR_2(sf2_level2_fan1, S_IRUGO | S_IWUSR,
			show_sf2_level, store_sf2_level, 2, 1);
अटल SENSOR_DEVICE_ATTR_2(sf2_level3_fan1, S_IRUGO | S_IWUSR,
			show_sf2_level, store_sf2_level, 3, 1);
अटल SENSOR_DEVICE_ATTR_2(sf2_level1_fan2, S_IRUGO | S_IWUSR,
			show_sf2_level, store_sf2_level, 1, 2);
अटल SENSOR_DEVICE_ATTR_2(sf2_level2_fan2, S_IRUGO | S_IWUSR,
			show_sf2_level, store_sf2_level, 2, 2);
अटल SENSOR_DEVICE_ATTR_2(sf2_level3_fan2, S_IRUGO | S_IWUSR,
			show_sf2_level, store_sf2_level, 3, 2);
अटल SENSOR_DEVICE_ATTR_2(sf2_level1_fan3, S_IRUGO | S_IWUSR,
			show_sf2_level, store_sf2_level, 1, 3);
अटल SENSOR_DEVICE_ATTR_2(sf2_level2_fan3, S_IRUGO | S_IWUSR,
			show_sf2_level, store_sf2_level, 2, 3);
अटल SENSOR_DEVICE_ATTR_2(sf2_level3_fan3, S_IRUGO | S_IWUSR,
			show_sf2_level, store_sf2_level, 3, 3);
अटल SENSOR_DEVICE_ATTR(fan1_input, S_IRUGO, show_fan, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(fan2_input, S_IRUGO, show_fan, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(fan3_input, S_IRUGO, show_fan, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(fan4_input, S_IRUGO, show_fan, शून्य, 4);
अटल SENSOR_DEVICE_ATTR(fan5_input, S_IRUGO, show_fan, शून्य, 5);
अटल SENSOR_DEVICE_ATTR(fan6_input, S_IRUGO, show_fan, शून्य, 6);
अटल SENSOR_DEVICE_ATTR(fan7_input, S_IRUGO, show_fan, शून्य, 7);
अटल SENSOR_DEVICE_ATTR(fan1_min, S_IWUSR | S_IRUGO,
			show_fan_min, store_fan_min, 1);
अटल SENSOR_DEVICE_ATTR(fan2_min, S_IWUSR | S_IRUGO,
			show_fan_min, store_fan_min, 2);
अटल SENSOR_DEVICE_ATTR(fan3_min, S_IWUSR | S_IRUGO,
			show_fan_min, store_fan_min, 3);
अटल SENSOR_DEVICE_ATTR(fan4_min, S_IWUSR | S_IRUGO,
			show_fan_min, store_fan_min, 4);
अटल SENSOR_DEVICE_ATTR(fan5_min, S_IWUSR | S_IRUGO,
			show_fan_min, store_fan_min, 5);
अटल SENSOR_DEVICE_ATTR(fan6_min, S_IWUSR | S_IRUGO,
			show_fan_min, store_fan_min, 6);
अटल SENSOR_DEVICE_ATTR(fan7_min, S_IWUSR | S_IRUGO,
			show_fan_min, store_fan_min, 7);
अटल SENSOR_DEVICE_ATTR(fan1_भाग, S_IWUSR | S_IRUGO,
			show_fan_भाग, store_fan_भाग, 1);
अटल SENSOR_DEVICE_ATTR(fan2_भाग, S_IWUSR | S_IRUGO,
			show_fan_भाग, store_fan_भाग, 2);
अटल SENSOR_DEVICE_ATTR(fan3_भाग, S_IWUSR | S_IRUGO,
			show_fan_भाग, store_fan_भाग, 3);
अटल SENSOR_DEVICE_ATTR(fan4_भाग, S_IWUSR | S_IRUGO,
			show_fan_भाग, store_fan_भाग, 4);
अटल SENSOR_DEVICE_ATTR(fan5_भाग, S_IWUSR | S_IRUGO,
			show_fan_भाग, store_fan_भाग, 5);
अटल SENSOR_DEVICE_ATTR(fan6_भाग, S_IWUSR | S_IRUGO,
			show_fan_भाग, store_fan_भाग, 6);
अटल SENSOR_DEVICE_ATTR(fan7_भाग, S_IWUSR | S_IRUGO,
			show_fan_भाग, store_fan_भाग, 7);

अटल काष्ठा attribute *w83792d_attributes_fan[4][7] = अणु
	अणु
		&sensor_dev_attr_fan4_input.dev_attr.attr,
		&sensor_dev_attr_fan4_min.dev_attr.attr,
		&sensor_dev_attr_fan4_भाग.dev_attr.attr,
		&sensor_dev_attr_fan4_alarm.dev_attr.attr,
		&sensor_dev_attr_pwm4.dev_attr.attr,
		&sensor_dev_attr_pwm4_mode.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_fan5_input.dev_attr.attr,
		&sensor_dev_attr_fan5_min.dev_attr.attr,
		&sensor_dev_attr_fan5_भाग.dev_attr.attr,
		&sensor_dev_attr_fan5_alarm.dev_attr.attr,
		&sensor_dev_attr_pwm5.dev_attr.attr,
		&sensor_dev_attr_pwm5_mode.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_fan6_input.dev_attr.attr,
		&sensor_dev_attr_fan6_min.dev_attr.attr,
		&sensor_dev_attr_fan6_भाग.dev_attr.attr,
		&sensor_dev_attr_fan6_alarm.dev_attr.attr,
		&sensor_dev_attr_pwm6.dev_attr.attr,
		&sensor_dev_attr_pwm6_mode.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_fan7_input.dev_attr.attr,
		&sensor_dev_attr_fan7_min.dev_attr.attr,
		&sensor_dev_attr_fan7_भाग.dev_attr.attr,
		&sensor_dev_attr_fan7_alarm.dev_attr.attr,
		&sensor_dev_attr_pwm7.dev_attr.attr,
		&sensor_dev_attr_pwm7_mode.dev_attr.attr,
		शून्य
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा attribute_group w83792d_group_fan[4] = अणु
	अणु .attrs = w83792d_attributes_fan[0] पूर्ण,
	अणु .attrs = w83792d_attributes_fan[1] पूर्ण,
	अणु .attrs = w83792d_attributes_fan[2] पूर्ण,
	अणु .attrs = w83792d_attributes_fan[3] पूर्ण,
पूर्ण;

अटल काष्ठा attribute *w83792d_attributes[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in6_max.dev_attr.attr,
	&sensor_dev_attr_in6_min.dev_attr.attr,
	&sensor_dev_attr_in7_input.dev_attr.attr,
	&sensor_dev_attr_in7_max.dev_attr.attr,
	&sensor_dev_attr_in7_min.dev_attr.attr,
	&sensor_dev_attr_in8_input.dev_attr.attr,
	&sensor_dev_attr_in8_max.dev_attr.attr,
	&sensor_dev_attr_in8_min.dev_attr.attr,
	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,
	&sensor_dev_attr_in5_alarm.dev_attr.attr,
	&sensor_dev_attr_in6_alarm.dev_attr.attr,
	&sensor_dev_attr_in7_alarm.dev_attr.attr,
	&sensor_dev_attr_in8_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp3_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_alarm.dev_attr.attr,
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm1_mode.dev_attr.attr,
	&sensor_dev_attr_pwm1_enable.dev_attr.attr,
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&sensor_dev_attr_pwm2_mode.dev_attr.attr,
	&sensor_dev_attr_pwm2_enable.dev_attr.attr,
	&sensor_dev_attr_pwm3.dev_attr.attr,
	&sensor_dev_attr_pwm3_mode.dev_attr.attr,
	&sensor_dev_attr_pwm3_enable.dev_attr.attr,
	&dev_attr_alarms.attr,
	&dev_attr_पूर्णांकrusion0_alarm.attr,
	&sensor_dev_attr_tolerance1.dev_attr.attr,
	&sensor_dev_attr_thermal_cruise1.dev_attr.attr,
	&sensor_dev_attr_tolerance2.dev_attr.attr,
	&sensor_dev_attr_thermal_cruise2.dev_attr.attr,
	&sensor_dev_attr_tolerance3.dev_attr.attr,
	&sensor_dev_attr_thermal_cruise3.dev_attr.attr,
	&sensor_dev_attr_sf2_poपूर्णांक1_fan1.dev_attr.attr,
	&sensor_dev_attr_sf2_poपूर्णांक2_fan1.dev_attr.attr,
	&sensor_dev_attr_sf2_poपूर्णांक3_fan1.dev_attr.attr,
	&sensor_dev_attr_sf2_poपूर्णांक4_fan1.dev_attr.attr,
	&sensor_dev_attr_sf2_poपूर्णांक1_fan2.dev_attr.attr,
	&sensor_dev_attr_sf2_poपूर्णांक2_fan2.dev_attr.attr,
	&sensor_dev_attr_sf2_poपूर्णांक3_fan2.dev_attr.attr,
	&sensor_dev_attr_sf2_poपूर्णांक4_fan2.dev_attr.attr,
	&sensor_dev_attr_sf2_poपूर्णांक1_fan3.dev_attr.attr,
	&sensor_dev_attr_sf2_poपूर्णांक2_fan3.dev_attr.attr,
	&sensor_dev_attr_sf2_poपूर्णांक3_fan3.dev_attr.attr,
	&sensor_dev_attr_sf2_poपूर्णांक4_fan3.dev_attr.attr,
	&sensor_dev_attr_sf2_level1_fan1.dev_attr.attr,
	&sensor_dev_attr_sf2_level2_fan1.dev_attr.attr,
	&sensor_dev_attr_sf2_level3_fan1.dev_attr.attr,
	&sensor_dev_attr_sf2_level1_fan2.dev_attr.attr,
	&sensor_dev_attr_sf2_level2_fan2.dev_attr.attr,
	&sensor_dev_attr_sf2_level3_fan2.dev_attr.attr,
	&sensor_dev_attr_sf2_level1_fan3.dev_attr.attr,
	&sensor_dev_attr_sf2_level2_fan3.dev_attr.attr,
	&sensor_dev_attr_sf2_level3_fan3.dev_attr.attr,
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan1_भाग.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan2_भाग.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan3_min.dev_attr.attr,
	&sensor_dev_attr_fan3_भाग.dev_attr.attr,
	&sensor_dev_attr_fan3_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group w83792d_group = अणु
	.attrs = w83792d_attributes,
पूर्ण;

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक
w83792d_detect(काष्ठा i2c_client *client, काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक val1, val2;
	अचिन्हित लघु address = client->addr;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	अगर (w83792d_पढ़ो_value(client, W83792D_REG_CONFIG) & 0x80)
		वापस -ENODEV;

	val1 = w83792d_पढ़ो_value(client, W83792D_REG_BANK);
	val2 = w83792d_पढ़ो_value(client, W83792D_REG_CHIPMAN);
	/* Check क्रम Winbond ID अगर in bank 0 */
	अगर (!(val1 & 0x07)) अणु  /* is Bank0 */
		अगर ((!(val1 & 0x80) && val2 != 0xa3) ||
		    ((val1 & 0x80) && val2 != 0x5c))
			वापस -ENODEV;
	पूर्ण
	/*
	 * If Winbond chip, address of chip and W83792D_REG_I2C_ADDR
	 * should match
	 */
	अगर (w83792d_पढ़ो_value(client, W83792D_REG_I2C_ADDR) != address)
		वापस -ENODEV;

	/*  Put it now पूर्णांकo bank 0 and Venकरोr ID High Byte */
	w83792d_ग_लिखो_value(client,
			    W83792D_REG_BANK,
			    (w83792d_पढ़ो_value(client,
				W83792D_REG_BANK) & 0x78) | 0x80);

	/* Determine the chip type. */
	val1 = w83792d_पढ़ो_value(client, W83792D_REG_WCHIPID);
	val2 = w83792d_पढ़ो_value(client, W83792D_REG_CHIPMAN);
	अगर (val1 != 0x7a || val2 != 0x5c)
		वापस -ENODEV;

	strlcpy(info->type, "w83792d", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक
w83792d_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा w83792d_data *data;
	काष्ठा device *dev = &client->dev;
	पूर्णांक i, val1, err;

	data = devm_kzalloc(dev, माप(काष्ठा w83792d_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	err = w83792d_detect_subclients(client);
	अगर (err)
		वापस err;

	/* Initialize the chip */
	w83792d_init_client(client);

	/* A few vars need to be filled upon startup */
	क्रम (i = 0; i < 7; i++) अणु
		data->fan_min[i] = w83792d_पढ़ो_value(client,
					W83792D_REG_FAN_MIN[i]);
	पूर्ण

	/* Register sysfs hooks */
	err = sysfs_create_group(&dev->kobj, &w83792d_group);
	अगर (err)
		वापस err;

	/*
	 * Read GPIO enable रेजिस्टर to check अगर pins क्रम fan 4,5 are used as
	 * GPIO
	 */
	val1 = w83792d_पढ़ो_value(client, W83792D_REG_GPIO_EN);

	अगर (!(val1 & 0x40)) अणु
		err = sysfs_create_group(&dev->kobj, &w83792d_group_fan[0]);
		अगर (err)
			जाओ निकास_हटाओ_files;
	पूर्ण

	अगर (!(val1 & 0x20)) अणु
		err = sysfs_create_group(&dev->kobj, &w83792d_group_fan[1]);
		अगर (err)
			जाओ निकास_हटाओ_files;
	पूर्ण

	val1 = w83792d_पढ़ो_value(client, W83792D_REG_PIN);
	अगर (val1 & 0x40) अणु
		err = sysfs_create_group(&dev->kobj, &w83792d_group_fan[2]);
		अगर (err)
			जाओ निकास_हटाओ_files;
	पूर्ण

	अगर (val1 & 0x04) अणु
		err = sysfs_create_group(&dev->kobj, &w83792d_group_fan[3]);
		अगर (err)
			जाओ निकास_हटाओ_files;
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		जाओ निकास_हटाओ_files;
	पूर्ण

	वापस 0;

निकास_हटाओ_files:
	sysfs_हटाओ_group(&dev->kobj, &w83792d_group);
	क्रम (i = 0; i < ARRAY_SIZE(w83792d_group_fan); i++)
		sysfs_हटाओ_group(&dev->kobj, &w83792d_group_fan[i]);
	वापस err;
पूर्ण

अटल पूर्णांक
w83792d_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा w83792d_data *data = i2c_get_clientdata(client);
	पूर्णांक i;

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	sysfs_हटाओ_group(&client->dev.kobj, &w83792d_group);
	क्रम (i = 0; i < ARRAY_SIZE(w83792d_group_fan); i++)
		sysfs_हटाओ_group(&client->dev.kobj,
				   &w83792d_group_fan[i]);

	वापस 0;
पूर्ण

अटल व्योम
w83792d_init_client(काष्ठा i2c_client *client)
अणु
	u8 temp2_cfg, temp3_cfg, vid_in_b;

	अगर (init)
		w83792d_ग_लिखो_value(client, W83792D_REG_CONFIG, 0x80);

	/*
	 * Clear the bit6 of W83792D_REG_VID_IN_B(set it पूर्णांकo 0):
	 * W83792D_REG_VID_IN_B bit6 = 0: the high/low limit of
	 * vin0/vin1 can be modअगरied by user;
	 * W83792D_REG_VID_IN_B bit6 = 1: the high/low limit of
	 * vin0/vin1 स्वतः-updated, can NOT be modअगरied by user.
	 */
	vid_in_b = w83792d_पढ़ो_value(client, W83792D_REG_VID_IN_B);
	w83792d_ग_लिखो_value(client, W83792D_REG_VID_IN_B,
			    vid_in_b & 0xbf);

	temp2_cfg = w83792d_पढ़ो_value(client, W83792D_REG_TEMP2_CONFIG);
	temp3_cfg = w83792d_पढ़ो_value(client, W83792D_REG_TEMP3_CONFIG);
	w83792d_ग_लिखो_value(client, W83792D_REG_TEMP2_CONFIG,
				temp2_cfg & 0xe6);
	w83792d_ग_लिखो_value(client, W83792D_REG_TEMP3_CONFIG,
				temp3_cfg & 0xe6);

	/* Start monitoring */
	w83792d_ग_लिखो_value(client, W83792D_REG_CONFIG,
			    (w83792d_पढ़ो_value(client,
						W83792D_REG_CONFIG) & 0xf7)
			    | 0x01);
पूर्ण

अटल काष्ठा w83792d_data *w83792d_update_device(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83792d_data *data = i2c_get_clientdata(client);
	पूर्णांक i, j;
	u8 reg_array_पंचांगp[4], reg_पंचांगp;

	mutex_lock(&data->update_lock);

	अगर (समय_after
	    (jअगरfies - data->last_updated, (अचिन्हित दीर्घ) (HZ * 3))
	    || समय_beक्रमe(jअगरfies, data->last_updated) || !data->valid) अणु
		dev_dbg(dev, "Starting device update\n");

		/* Update the voltages measured value and limits */
		क्रम (i = 0; i < 9; i++) अणु
			data->in[i] = w83792d_पढ़ो_value(client,
						W83792D_REG_IN[i]);
			data->in_max[i] = w83792d_पढ़ो_value(client,
						W83792D_REG_IN_MAX[i]);
			data->in_min[i] = w83792d_पढ़ो_value(client,
						W83792D_REG_IN_MIN[i]);
		पूर्ण
		data->low_bits = w83792d_पढ़ो_value(client,
						W83792D_REG_LOW_BITS1) +
				 (w83792d_पढ़ो_value(client,
						W83792D_REG_LOW_BITS2) << 8);
		क्रम (i = 0; i < 7; i++) अणु
			/* Update the Fan measured value and limits */
			data->fan[i] = w83792d_पढ़ो_value(client,
						W83792D_REG_FAN[i]);
			data->fan_min[i] = w83792d_पढ़ो_value(client,
						W83792D_REG_FAN_MIN[i]);
			/* Update the PWM/DC Value and PWM/DC flag */
			data->pwm[i] = w83792d_पढ़ो_value(client,
						W83792D_REG_PWM[i]);
		पूर्ण

		reg_पंचांगp = w83792d_पढ़ो_value(client, W83792D_REG_FAN_CFG);
		data->pwmenable[0] = reg_पंचांगp & 0x03;
		data->pwmenable[1] = (reg_पंचांगp>>2) & 0x03;
		data->pwmenable[2] = (reg_पंचांगp>>4) & 0x03;

		क्रम (i = 0; i < 3; i++) अणु
			data->temp1[i] = w83792d_पढ़ो_value(client,
							W83792D_REG_TEMP1[i]);
		पूर्ण
		क्रम (i = 0; i < 2; i++) अणु
			क्रम (j = 0; j < 6; j++) अणु
				data->temp_add[i][j] = w83792d_पढ़ो_value(
					client, W83792D_REG_TEMP_ADD[i][j]);
			पूर्ण
		पूर्ण

		/* Update the Fan Divisor */
		क्रम (i = 0; i < 4; i++) अणु
			reg_array_पंचांगp[i] = w83792d_पढ़ो_value(client,
							W83792D_REG_FAN_DIV[i]);
		पूर्ण
		data->fan_भाग[0] = reg_array_पंचांगp[0] & 0x07;
		data->fan_भाग[1] = (reg_array_पंचांगp[0] >> 4) & 0x07;
		data->fan_भाग[2] = reg_array_पंचांगp[1] & 0x07;
		data->fan_भाग[3] = (reg_array_पंचांगp[1] >> 4) & 0x07;
		data->fan_भाग[4] = reg_array_पंचांगp[2] & 0x07;
		data->fan_भाग[5] = (reg_array_पंचांगp[2] >> 4) & 0x07;
		data->fan_भाग[6] = reg_array_पंचांगp[3] & 0x07;

		/* Update the realसमय status */
		data->alarms = w83792d_पढ़ो_value(client, W83792D_REG_ALARM1) +
			(w83792d_पढ़ो_value(client, W83792D_REG_ALARM2) << 8) +
			(w83792d_पढ़ो_value(client, W83792D_REG_ALARM3) << 16);

		/* Update CaseOpen status and it's CLR_CHS. */
		data->chassis = (w83792d_पढ़ो_value(client,
			W83792D_REG_CHASSIS) >> 5) & 0x01;

		/* Update Thermal Cruise/Smart Fan I target value */
		क्रम (i = 0; i < 3; i++) अणु
			data->thermal_cruise[i] =
				w83792d_पढ़ो_value(client,
				W83792D_REG_THERMAL[i]) & 0x7f;
		पूर्ण

		/* Update Smart Fan I/II tolerance */
		reg_पंचांगp = w83792d_पढ़ो_value(client, W83792D_REG_TOLERANCE[0]);
		data->tolerance[0] = reg_पंचांगp & 0x0f;
		data->tolerance[1] = (reg_पंचांगp >> 4) & 0x0f;
		data->tolerance[2] = w83792d_पढ़ो_value(client,
					W83792D_REG_TOLERANCE[2]) & 0x0f;

		/* Update Smart Fan II temperature poपूर्णांकs */
		क्रम (i = 0; i < 3; i++) अणु
			क्रम (j = 0; j < 4; j++) अणु
				data->sf2_poपूर्णांकs[i][j]
				  = w83792d_पढ़ो_value(client,
					W83792D_REG_POINTS[i][j]) & 0x7f;
			पूर्ण
		पूर्ण

		/* Update Smart Fan II duty cycle levels */
		क्रम (i = 0; i < 3; i++) अणु
			reg_पंचांगp = w83792d_पढ़ो_value(client,
						W83792D_REG_LEVELS[i][0]);
			data->sf2_levels[i][0] = reg_पंचांगp & 0x0f;
			data->sf2_levels[i][1] = (reg_पंचांगp >> 4) & 0x0f;
			reg_पंचांगp = w83792d_पढ़ो_value(client,
						W83792D_REG_LEVELS[i][2]);
			data->sf2_levels[i][2] = (reg_पंचांगp >> 4) & 0x0f;
			data->sf2_levels[i][3] = reg_पंचांगp & 0x0f;
		पूर्ण

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

#अगर_घोषित DEBUG
	w83792d_prपूर्णांक_debug(data, dev);
#पूर्ण_अगर

	वापस data;
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम w83792d_prपूर्णांक_debug(काष्ठा w83792d_data *data, काष्ठा device *dev)
अणु
	पूर्णांक i = 0, j = 0;
	dev_dbg(dev, "==========The following is the debug message...========\n");
	dev_dbg(dev, "9 set of Voltages: =====>\n");
	क्रम (i = 0; i < 9; i++) अणु
		dev_dbg(dev, "vin[%d] is: 0x%x\n", i, data->in[i]);
		dev_dbg(dev, "vin[%d] max is: 0x%x\n", i, data->in_max[i]);
		dev_dbg(dev, "vin[%d] min is: 0x%x\n", i, data->in_min[i]);
	पूर्ण
	dev_dbg(dev, "Low Bit1 is: 0x%x\n", data->low_bits & 0xff);
	dev_dbg(dev, "Low Bit2 is: 0x%x\n", data->low_bits >> 8);
	dev_dbg(dev, "7 set of Fan Counts and Duty Cycles: =====>\n");
	क्रम (i = 0; i < 7; i++) अणु
		dev_dbg(dev, "fan[%d] is: 0x%x\n", i, data->fan[i]);
		dev_dbg(dev, "fan[%d] min is: 0x%x\n", i, data->fan_min[i]);
		dev_dbg(dev, "pwm[%d]     is: 0x%x\n", i, data->pwm[i]);
	पूर्ण
	dev_dbg(dev, "3 set of Temperatures: =====>\n");
	क्रम (i = 0; i < 3; i++)
		dev_dbg(dev, "temp1[%d] is: 0x%x\n", i, data->temp1[i]);

	क्रम (i = 0; i < 2; i++) अणु
		क्रम (j = 0; j < 6; j++) अणु
			dev_dbg(dev, "temp_add[%d][%d] is: 0x%x\n", i, j,
							data->temp_add[i][j]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 7; i++)
		dev_dbg(dev, "fan_div[%d] is: 0x%x\n", i, data->fan_भाग[i]);

	dev_dbg(dev, "==========End of the debug message...================\n");
	dev_dbg(dev, "\n");
पूर्ण
#पूर्ण_अगर

module_i2c_driver(w83792d_driver);

MODULE_AUTHOR("Shane Huang (Winbond)");
MODULE_DESCRIPTION("W83792AD/D driver for linux-2.6");
MODULE_LICENSE("GPL");
