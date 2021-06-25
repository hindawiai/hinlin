<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * w83781d.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *	       monitoring
 * Copyright (c) 1998 - 2001  Froकरो Looijaard <froकरोl@dds.nl>,
 *			      Philip Edelbrock <phil@netroedge.com>,
 *			      and Mark Studebaker <mdsxyz123@yahoo.com>
 * Copyright (c) 2007 - 2008  Jean Delvare <jdelvare@suse.de>
 */

/*
 * Supports following chips:
 *
 * Chip		#vin	#fanin	#pwm	#temp	wchipid	vendid	i2c	ISA
 * as99127f	7	3	0	3	0x31	0x12c3	yes	no
 * as99127f rev.2 (type_name = as99127f)	0x31	0x5ca3	yes	no
 * w83781d	7	3	0	3	0x10-1	0x5ca3	yes	yes
 * w83782d	9	3	2-4	3	0x30	0x5ca3	yes	yes
 * w83783s	5-6	3	2	1-2	0x40	0x5ca3	yes	no
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>

#अगर_घोषित CONFIG_ISA
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#पूर्ण_अगर

#समावेश "lm75.h"

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d,
						0x2e, 0x2f, I2C_CLIENT_END पूर्ण;

क्रमागत chips अणु w83781d, w83782d, w83783s, as99127f पूर्ण;

/* Insmod parameters */
अटल अचिन्हित लघु क्रमce_subclients[4];
module_param_array(क्रमce_subclients, लघु, शून्य, 0);
MODULE_PARM_DESC(क्रमce_subclients,
		 "List of subclient addresses: {bus, clientaddr, subclientaddr1, subclientaddr2}");

अटल bool reset;
module_param(reset, bool, 0);
MODULE_PARM_DESC(reset, "Set to one to reset chip on load");

अटल bool init = 1;
module_param(init, bool, 0);
MODULE_PARM_DESC(init, "Set to zero to bypass chip initialization");

/* Constants specअगरied below */

/* Length of ISA address segment */
#घोषणा W83781D_EXTENT			8

/* Where are the ISA address/data रेजिस्टरs relative to the base address */
#घोषणा W83781D_ADDR_REG_OFFSET		5
#घोषणा W83781D_DATA_REG_OFFSET		6

/* The device रेजिस्टरs */
/* in nr from 0 to 8 */
#घोषणा W83781D_REG_IN_MAX(nr)		((nr < 7) ? (0x2b + (nr) * 2) : \
						    (0x554 + (((nr) - 7) * 2)))
#घोषणा W83781D_REG_IN_MIN(nr)		((nr < 7) ? (0x2c + (nr) * 2) : \
						    (0x555 + (((nr) - 7) * 2)))
#घोषणा W83781D_REG_IN(nr)		((nr < 7) ? (0x20 + (nr)) : \
						    (0x550 + (nr) - 7))

/* fan nr from 0 to 2 */
#घोषणा W83781D_REG_FAN_MIN(nr)		(0x3b + (nr))
#घोषणा W83781D_REG_FAN(nr)		(0x28 + (nr))

#घोषणा W83781D_REG_BANK		0x4E
#घोषणा W83781D_REG_TEMP2_CONFIG	0x152
#घोषणा W83781D_REG_TEMP3_CONFIG	0x252
/* temp nr from 1 to 3 */
#घोषणा W83781D_REG_TEMP(nr)		((nr == 3) ? (0x0250) : \
					((nr == 2) ? (0x0150) : \
						     (0x27)))
#घोषणा W83781D_REG_TEMP_HYST(nr)	((nr == 3) ? (0x253) : \
					((nr == 2) ? (0x153) : \
						     (0x3A)))
#घोषणा W83781D_REG_TEMP_OVER(nr)	((nr == 3) ? (0x255) : \
					((nr == 2) ? (0x155) : \
						     (0x39)))

#घोषणा W83781D_REG_CONFIG		0x40

/* Interrupt status (W83781D, AS99127F) */
#घोषणा W83781D_REG_ALARM1		0x41
#घोषणा W83781D_REG_ALARM2		0x42

/* Real-समय status (W83782D, W83783S) */
#घोषणा W83782D_REG_ALARM1		0x459
#घोषणा W83782D_REG_ALARM2		0x45A
#घोषणा W83782D_REG_ALARM3		0x45B

#घोषणा W83781D_REG_BEEP_CONFIG		0x4D
#घोषणा W83781D_REG_BEEP_INTS1		0x56
#घोषणा W83781D_REG_BEEP_INTS2		0x57
#घोषणा W83781D_REG_BEEP_INTS3		0x453	/* not on W83781D */

#घोषणा W83781D_REG_VID_FANDIV		0x47

#घोषणा W83781D_REG_CHIPID		0x49
#घोषणा W83781D_REG_WCHIPID		0x58
#घोषणा W83781D_REG_CHIPMAN		0x4F
#घोषणा W83781D_REG_PIN			0x4B

/* 782D/783S only */
#घोषणा W83781D_REG_VBAT		0x5D

/* PWM 782D (1-4) and 783S (1-2) only */
अटल स्थिर u8 W83781D_REG_PWM[] = अणु 0x5B, 0x5A, 0x5E, 0x5F पूर्ण;
#घोषणा W83781D_REG_PWMCLK12		0x5C
#घोषणा W83781D_REG_PWMCLK34		0x45C

#घोषणा W83781D_REG_I2C_ADDR		0x48
#घोषणा W83781D_REG_I2C_SUBADDR		0x4A

/*
 * The following are unकरोcumented in the data sheets however we
 * received the inक्रमmation in an email from Winbond tech support
 */
/* Sensor selection - not on 781d */
#घोषणा W83781D_REG_SCFG1		0x5D
अटल स्थिर u8 BIT_SCFG1[] = अणु 0x02, 0x04, 0x08 पूर्ण;

#घोषणा W83781D_REG_SCFG2		0x59
अटल स्थिर u8 BIT_SCFG2[] = अणु 0x10, 0x20, 0x40 पूर्ण;

#घोषणा W83781D_DEFAULT_BETA		3435

/* Conversions */
#घोषणा IN_TO_REG(val)			clamp_val(((val) + 8) / 16, 0, 255)
#घोषणा IN_FROM_REG(val)		((val) * 16)

अटल अंतरभूत u8
FAN_TO_REG(दीर्घ rpm, पूर्णांक भाग)
अणु
	अगर (rpm == 0)
		वापस 255;
	rpm = clamp_val(rpm, 1, 1000000);
	वापस clamp_val((1350000 + rpm * भाग / 2) / (rpm * भाग), 1, 254);
पूर्ण

अटल अंतरभूत दीर्घ
FAN_FROM_REG(u8 val, पूर्णांक भाग)
अणु
	अगर (val == 0)
		वापस -1;
	अगर (val == 255)
		वापस 0;
	वापस 1350000 / (val * भाग);
पूर्ण

#घोषणा TEMP_TO_REG(val)		clamp_val((val) / 1000, -127, 128)
#घोषणा TEMP_FROM_REG(val)		((val) * 1000)

#घोषणा BEEP_MASK_FROM_REG(val, type)	((type) == as99127f ? \
					 (~(val)) & 0x7fff : (val) & 0xff7fff)
#घोषणा BEEP_MASK_TO_REG(val, type)	((type) == as99127f ? \
					 (~(val)) & 0x7fff : (val) & 0xff7fff)

#घोषणा DIV_FROM_REG(val)		(1 << (val))

अटल अंतरभूत u8
DIV_TO_REG(दीर्घ val, क्रमागत chips type)
अणु
	पूर्णांक i;
	val = clamp_val(val, 1,
			((type == w83781d || type == as99127f) ? 8 : 128)) >> 1;
	क्रम (i = 0; i < 7; i++) अणु
		अगर (val == 0)
			अवरोध;
		val >>= 1;
	पूर्ण
	वापस i;
पूर्ण

काष्ठा w83781d_data अणु
	काष्ठा i2c_client *client;
	काष्ठा device *hwmon_dev;
	काष्ठा mutex lock;
	क्रमागत chips type;

	/* For ISA device only */
	स्थिर अक्षर *name;
	पूर्णांक isa_addr;

	काष्ठा mutex update_lock;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	काष्ठा i2c_client *lm75[2];	/* क्रम secondary I2C addresses */
	/* array of 2 poपूर्णांकers to subclients */

	u8 in[9];		/* Register value - 8 & 9 क्रम 782D only */
	u8 in_max[9];		/* Register value - 8 & 9 क्रम 782D only */
	u8 in_min[9];		/* Register value - 8 & 9 क्रम 782D only */
	u8 fan[3];		/* Register value */
	u8 fan_min[3];		/* Register value */
	s8 temp;		/* Register value */
	s8 temp_max;		/* Register value */
	s8 temp_max_hyst;	/* Register value */
	u16 temp_add[2];	/* Register value */
	u16 temp_max_add[2];	/* Register value */
	u16 temp_max_hyst_add[2];	/* Register value */
	u8 fan_भाग[3];		/* Register encoding, shअगरted right */
	u8 vid;			/* Register encoding, combined */
	u32 alarms;		/* Register encoding, combined */
	u32 beep_mask;		/* Register encoding, combined */
	u8 pwm[4];		/* Register value */
	u8 pwm2_enable;		/* Boolean */
	u16 sens[3];		/*
				 * 782D/783S only.
				 * 1 = pentium diode; 2 = 3904 diode;
				 * 4 = thermistor
				 */
	u8 vrm;
पूर्ण;

अटल काष्ठा w83781d_data *w83781d_data_अगर_isa(व्योम);
अटल पूर्णांक w83781d_alias_detect(काष्ठा i2c_client *client, u8 chipid);

अटल पूर्णांक w83781d_पढ़ो_value(काष्ठा w83781d_data *data, u16 reg);
अटल पूर्णांक w83781d_ग_लिखो_value(काष्ठा w83781d_data *data, u16 reg, u16 value);
अटल काष्ठा w83781d_data *w83781d_update_device(काष्ठा device *dev);
अटल व्योम w83781d_init_device(काष्ठा device *dev);

/* following are the sysfs callback functions */
#घोषणा show_in_reg(reg) \
अटल sमाप_प्रकार show_##reg(काष्ठा device *dev, काष्ठा device_attribute *da, \
		अक्षर *buf) \
अणु \
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da); \
	काष्ठा w83781d_data *data = w83781d_update_device(dev); \
	वापस प्र_लिखो(buf, "%ld\n", \
		       (दीर्घ)IN_FROM_REG(data->reg[attr->index])); \
पूर्ण
show_in_reg(in);
show_in_reg(in_min);
show_in_reg(in_max);

#घोषणा store_in_reg(REG, reg) \
अटल sमाप_प्रकार store_in_##reg(काष्ठा device *dev, काष्ठा device_attribute \
		*da, स्थिर अक्षर *buf, माप_प्रकार count) \
अणु \
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da); \
	काष्ठा w83781d_data *data = dev_get_drvdata(dev); \
	पूर्णांक nr = attr->index; \
	अचिन्हित दीर्घ val; \
	पूर्णांक err = kम_से_अदीर्घ(buf, 10, &val); \
	अगर (err) \
		वापस err; \
	mutex_lock(&data->update_lock); \
	data->in_##reg[nr] = IN_TO_REG(val); \
	w83781d_ग_लिखो_value(data, W83781D_REG_IN_##REG(nr), \
			    data->in_##reg[nr]); \
	\
	mutex_unlock(&data->update_lock); \
	वापस count; \
पूर्ण
store_in_reg(MIN, min);
store_in_reg(MAX, max);

#घोषणा sysfs_in_offsets(offset) \
अटल SENSOR_DEVICE_ATTR(in##offset##_input, S_IRUGO, \
		show_in, शून्य, offset); \
अटल SENSOR_DEVICE_ATTR(in##offset##_min, S_IRUGO | S_IWUSR, \
		show_in_min, store_in_min, offset); \
अटल SENSOR_DEVICE_ATTR(in##offset##_max, S_IRUGO | S_IWUSR, \
		show_in_max, store_in_max, offset)

sysfs_in_offsets(0);
sysfs_in_offsets(1);
sysfs_in_offsets(2);
sysfs_in_offsets(3);
sysfs_in_offsets(4);
sysfs_in_offsets(5);
sysfs_in_offsets(6);
sysfs_in_offsets(7);
sysfs_in_offsets(8);

#घोषणा show_fan_reg(reg) \
अटल sमाप_प्रकार show_##reg(काष्ठा device *dev, काष्ठा device_attribute *da, \
		अक्षर *buf) \
अणु \
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da); \
	काष्ठा w83781d_data *data = w83781d_update_device(dev); \
	वापस प्र_लिखो(buf, "%ld\n", \
		FAN_FROM_REG(data->reg[attr->index], \
			DIV_FROM_REG(data->fan_भाग[attr->index]))); \
पूर्ण
show_fan_reg(fan);
show_fan_reg(fan_min);

अटल sमाप_प्रकार
store_fan_min(काष्ठा device *dev, काष्ठा device_attribute *da,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा w83781d_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan_min[nr] =
	    FAN_TO_REG(val, DIV_FROM_REG(data->fan_भाग[nr]));
	w83781d_ग_लिखो_value(data, W83781D_REG_FAN_MIN(nr),
			    data->fan_min[nr]);

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR(fan1_input, S_IRUGO, show_fan, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(fan1_min, S_IRUGO | S_IWUSR,
		show_fan_min, store_fan_min, 0);
अटल SENSOR_DEVICE_ATTR(fan2_input, S_IRUGO, show_fan, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(fan2_min, S_IRUGO | S_IWUSR,
		show_fan_min, store_fan_min, 1);
अटल SENSOR_DEVICE_ATTR(fan3_input, S_IRUGO, show_fan, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(fan3_min, S_IRUGO | S_IWUSR,
		show_fan_min, store_fan_min, 2);

#घोषणा show_temp_reg(reg) \
अटल sमाप_प्रकार show_##reg(काष्ठा device *dev, काष्ठा device_attribute *da, \
		अक्षर *buf) \
अणु \
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da); \
	काष्ठा w83781d_data *data = w83781d_update_device(dev); \
	पूर्णांक nr = attr->index; \
	अगर (nr >= 2) अणु	/* TEMP2 and TEMP3 */ \
		वापस प्र_लिखो(buf, "%d\n", \
			LM75_TEMP_FROM_REG(data->reg##_add[nr-2])); \
	पूर्ण अन्यथा अणु	/* TEMP1 */ \
		वापस प्र_लिखो(buf, "%ld\n", (दीर्घ)TEMP_FROM_REG(data->reg)); \
	पूर्ण \
पूर्ण
show_temp_reg(temp);
show_temp_reg(temp_max);
show_temp_reg(temp_max_hyst);

#घोषणा store_temp_reg(REG, reg) \
अटल sमाप_प्रकार store_temp_##reg(काष्ठा device *dev, \
		काष्ठा device_attribute *da, स्थिर अक्षर *buf, माप_प्रकार count) \
अणु \
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da); \
	काष्ठा w83781d_data *data = dev_get_drvdata(dev); \
	पूर्णांक nr = attr->index; \
	दीर्घ val; \
	पूर्णांक err = kम_से_दीर्घ(buf, 10, &val); \
	अगर (err) \
		वापस err; \
	mutex_lock(&data->update_lock); \
	 \
	अगर (nr >= 2) अणु	/* TEMP2 and TEMP3 */ \
		data->temp_##reg##_add[nr-2] = LM75_TEMP_TO_REG(val); \
		w83781d_ग_लिखो_value(data, W83781D_REG_TEMP_##REG(nr), \
				data->temp_##reg##_add[nr-2]); \
	पूर्ण अन्यथा अणु	/* TEMP1 */ \
		data->temp_##reg = TEMP_TO_REG(val); \
		w83781d_ग_लिखो_value(data, W83781D_REG_TEMP_##REG(nr), \
			data->temp_##reg); \
	पूर्ण \
	 \
	mutex_unlock(&data->update_lock); \
	वापस count; \
पूर्ण
store_temp_reg(OVER, max);
store_temp_reg(HYST, max_hyst);

#घोषणा sysfs_temp_offsets(offset) \
अटल SENSOR_DEVICE_ATTR(temp##offset##_input, S_IRUGO, \
		show_temp, शून्य, offset); \
अटल SENSOR_DEVICE_ATTR(temp##offset##_max, S_IRUGO | S_IWUSR, \
		show_temp_max, store_temp_max, offset); \
अटल SENSOR_DEVICE_ATTR(temp##offset##_max_hyst, S_IRUGO | S_IWUSR, \
		show_temp_max_hyst, store_temp_max_hyst, offset);

sysfs_temp_offsets(1);
sysfs_temp_offsets(2);
sysfs_temp_offsets(3);

अटल sमाप_प्रकार
cpu0_vid_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83781d_data *data = w83781d_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n", (दीर्घ) vid_from_reg(data->vid, data->vrm));
पूर्ण

अटल DEVICE_ATTR_RO(cpu0_vid);

अटल sमाप_प्रकार
vrm_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83781d_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%ld\n", (दीर्घ) data->vrm);
पूर्ण

अटल sमाप_प्रकार
vrm_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	  माप_प्रकार count)
अणु
	काष्ठा w83781d_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;
	data->vrm = clamp_val(val, 0, 255);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(vrm);

अटल sमाप_प्रकार
alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83781d_data *data = w83781d_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", data->alarms);
पूर्ण

अटल DEVICE_ATTR_RO(alarms);

अटल sमाप_प्रकार show_alarm(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा w83781d_data *data = w83781d_update_device(dev);
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> bitnr) & 1);
पूर्ण

/* The W83781D has a single alarm bit क्रम temp2 and temp3 */
अटल sमाप_प्रकार show_temp3_alarm(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83781d_data *data = w83781d_update_device(dev);
	पूर्णांक bitnr = (data->type == w83781d) ? 5 : 13;
	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> bitnr) & 1);
पूर्ण

अटल SENSOR_DEVICE_ATTR(in0_alarm, S_IRUGO, show_alarm, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(in1_alarm, S_IRUGO, show_alarm, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(in2_alarm, S_IRUGO, show_alarm, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(in3_alarm, S_IRUGO, show_alarm, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(in4_alarm, S_IRUGO, show_alarm, शून्य, 8);
अटल SENSOR_DEVICE_ATTR(in5_alarm, S_IRUGO, show_alarm, शून्य, 9);
अटल SENSOR_DEVICE_ATTR(in6_alarm, S_IRUGO, show_alarm, शून्य, 10);
अटल SENSOR_DEVICE_ATTR(in7_alarm, S_IRUGO, show_alarm, शून्य, 16);
अटल SENSOR_DEVICE_ATTR(in8_alarm, S_IRUGO, show_alarm, शून्य, 17);
अटल SENSOR_DEVICE_ATTR(fan1_alarm, S_IRUGO, show_alarm, शून्य, 6);
अटल SENSOR_DEVICE_ATTR(fan2_alarm, S_IRUGO, show_alarm, शून्य, 7);
अटल SENSOR_DEVICE_ATTR(fan3_alarm, S_IRUGO, show_alarm, शून्य, 11);
अटल SENSOR_DEVICE_ATTR(temp1_alarm, S_IRUGO, show_alarm, शून्य, 4);
अटल SENSOR_DEVICE_ATTR(temp2_alarm, S_IRUGO, show_alarm, शून्य, 5);
अटल SENSOR_DEVICE_ATTR(temp3_alarm, S_IRUGO, show_temp3_alarm, शून्य, 0);

अटल sमाप_प्रकार beep_mask_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83781d_data *data = w83781d_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n",
		       (दीर्घ)BEEP_MASK_FROM_REG(data->beep_mask, data->type));
पूर्ण

अटल sमाप_प्रकार
beep_mask_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा w83781d_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->beep_mask &= 0x8000; /* preserve beep enable */
	data->beep_mask |= BEEP_MASK_TO_REG(val, data->type);
	w83781d_ग_लिखो_value(data, W83781D_REG_BEEP_INTS1,
			    data->beep_mask & 0xff);
	w83781d_ग_लिखो_value(data, W83781D_REG_BEEP_INTS2,
			    (data->beep_mask >> 8) & 0xff);
	अगर (data->type != w83781d && data->type != as99127f) अणु
		w83781d_ग_लिखो_value(data, W83781D_REG_BEEP_INTS3,
				    ((data->beep_mask) >> 16) & 0xff);
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(beep_mask);

अटल sमाप_प्रकार show_beep(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा w83781d_data *data = w83781d_update_device(dev);
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	वापस प्र_लिखो(buf, "%u\n", (data->beep_mask >> bitnr) & 1);
पूर्ण

अटल sमाप_प्रकार
store_beep(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा w83781d_data *data = dev_get_drvdata(dev);
	पूर्णांक bitnr = to_sensor_dev_attr(attr)->index;
	u8 reg;
	अचिन्हित दीर्घ bit;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &bit);
	अगर (err)
		वापस err;

	अगर (bit & ~1)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	अगर (bit)
		data->beep_mask |= (1 << bitnr);
	अन्यथा
		data->beep_mask &= ~(1 << bitnr);

	अगर (bitnr < 8) अणु
		reg = w83781d_पढ़ो_value(data, W83781D_REG_BEEP_INTS1);
		अगर (bit)
			reg |= (1 << bitnr);
		अन्यथा
			reg &= ~(1 << bitnr);
		w83781d_ग_लिखो_value(data, W83781D_REG_BEEP_INTS1, reg);
	पूर्ण अन्यथा अगर (bitnr < 16) अणु
		reg = w83781d_पढ़ो_value(data, W83781D_REG_BEEP_INTS2);
		अगर (bit)
			reg |= (1 << (bitnr - 8));
		अन्यथा
			reg &= ~(1 << (bitnr - 8));
		w83781d_ग_लिखो_value(data, W83781D_REG_BEEP_INTS2, reg);
	पूर्ण अन्यथा अणु
		reg = w83781d_पढ़ो_value(data, W83781D_REG_BEEP_INTS3);
		अगर (bit)
			reg |= (1 << (bitnr - 16));
		अन्यथा
			reg &= ~(1 << (bitnr - 16));
		w83781d_ग_लिखो_value(data, W83781D_REG_BEEP_INTS3, reg);
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* The W83781D has a single beep bit क्रम temp2 and temp3 */
अटल sमाप_प्रकार show_temp3_beep(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83781d_data *data = w83781d_update_device(dev);
	पूर्णांक bitnr = (data->type == w83781d) ? 5 : 13;
	वापस प्र_लिखो(buf, "%u\n", (data->beep_mask >> bitnr) & 1);
पूर्ण

अटल SENSOR_DEVICE_ATTR(in0_beep, S_IRUGO | S_IWUSR,
			show_beep, store_beep, 0);
अटल SENSOR_DEVICE_ATTR(in1_beep, S_IRUGO | S_IWUSR,
			show_beep, store_beep, 1);
अटल SENSOR_DEVICE_ATTR(in2_beep, S_IRUGO | S_IWUSR,
			show_beep, store_beep, 2);
अटल SENSOR_DEVICE_ATTR(in3_beep, S_IRUGO | S_IWUSR,
			show_beep, store_beep, 3);
अटल SENSOR_DEVICE_ATTR(in4_beep, S_IRUGO | S_IWUSR,
			show_beep, store_beep, 8);
अटल SENSOR_DEVICE_ATTR(in5_beep, S_IRUGO | S_IWUSR,
			show_beep, store_beep, 9);
अटल SENSOR_DEVICE_ATTR(in6_beep, S_IRUGO | S_IWUSR,
			show_beep, store_beep, 10);
अटल SENSOR_DEVICE_ATTR(in7_beep, S_IRUGO | S_IWUSR,
			show_beep, store_beep, 16);
अटल SENSOR_DEVICE_ATTR(in8_beep, S_IRUGO | S_IWUSR,
			show_beep, store_beep, 17);
अटल SENSOR_DEVICE_ATTR(fan1_beep, S_IRUGO | S_IWUSR,
			show_beep, store_beep, 6);
अटल SENSOR_DEVICE_ATTR(fan2_beep, S_IRUGO | S_IWUSR,
			show_beep, store_beep, 7);
अटल SENSOR_DEVICE_ATTR(fan3_beep, S_IRUGO | S_IWUSR,
			show_beep, store_beep, 11);
अटल SENSOR_DEVICE_ATTR(temp1_beep, S_IRUGO | S_IWUSR,
			show_beep, store_beep, 4);
अटल SENSOR_DEVICE_ATTR(temp2_beep, S_IRUGO | S_IWUSR,
			show_beep, store_beep, 5);
अटल SENSOR_DEVICE_ATTR(temp3_beep, S_IRUGO,
			show_temp3_beep, store_beep, 13);
अटल SENSOR_DEVICE_ATTR(beep_enable, S_IRUGO | S_IWUSR,
			show_beep, store_beep, 15);

अटल sमाप_प्रकार
show_fan_भाग(काष्ठा device *dev, काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा w83781d_data *data = w83781d_update_device(dev);
	वापस प्र_लिखो(buf, "%ld\n",
		       (दीर्घ) DIV_FROM_REG(data->fan_भाग[attr->index]));
पूर्ण

/*
 * Note: we save and restore the fan minimum here, because its value is
 * determined in part by the fan भागisor.  This follows the principle of
 * least surprise; the user करोesn't expect the fan minimum to change just
 * because the भागisor changed.
 */
अटल sमाप_प्रकार
store_fan_भाग(काष्ठा device *dev, काष्ठा device_attribute *da,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा w83781d_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ min;
	पूर्णांक nr = attr->index;
	u8 reg;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);

	/* Save fan_min */
	min = FAN_FROM_REG(data->fan_min[nr],
			   DIV_FROM_REG(data->fan_भाग[nr]));

	data->fan_भाग[nr] = DIV_TO_REG(val, data->type);

	reg = (w83781d_पढ़ो_value(data, nr == 2 ?
				  W83781D_REG_PIN : W83781D_REG_VID_FANDIV)
		& (nr == 0 ? 0xcf : 0x3f))
	      | ((data->fan_भाग[nr] & 0x03) << (nr == 0 ? 4 : 6));
	w83781d_ग_लिखो_value(data, nr == 2 ?
			    W83781D_REG_PIN : W83781D_REG_VID_FANDIV, reg);

	/* w83781d and as99127f करोn't have extended भागisor bits */
	अगर (data->type != w83781d && data->type != as99127f) अणु
		reg = (w83781d_पढ़ो_value(data, W83781D_REG_VBAT)
		       & ~(1 << (5 + nr)))
		    | ((data->fan_भाग[nr] & 0x04) << (3 + nr));
		w83781d_ग_लिखो_value(data, W83781D_REG_VBAT, reg);
	पूर्ण

	/* Restore fan_min */
	data->fan_min[nr] = FAN_TO_REG(min, DIV_FROM_REG(data->fan_भाग[nr]));
	w83781d_ग_लिखो_value(data, W83781D_REG_FAN_MIN(nr), data->fan_min[nr]);

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR(fan1_भाग, S_IRUGO | S_IWUSR,
		show_fan_भाग, store_fan_भाग, 0);
अटल SENSOR_DEVICE_ATTR(fan2_भाग, S_IRUGO | S_IWUSR,
		show_fan_भाग, store_fan_भाग, 1);
अटल SENSOR_DEVICE_ATTR(fan3_भाग, S_IRUGO | S_IWUSR,
		show_fan_भाग, store_fan_भाग, 2);

अटल sमाप_प्रकार
show_pwm(काष्ठा device *dev, काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा w83781d_data *data = w83781d_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)data->pwm[attr->index]);
पूर्ण

अटल sमाप_प्रकार
pwm2_enable_show(काष्ठा device *dev, काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा w83781d_data *data = w83781d_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)data->pwm2_enable);
पूर्ण

अटल sमाप_प्रकार
store_pwm(काष्ठा device *dev, काष्ठा device_attribute *da, स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा w83781d_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->pwm[nr] = clamp_val(val, 0, 255);
	w83781d_ग_लिखो_value(data, W83781D_REG_PWM[nr], data->pwm[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
pwm2_enable_store(काष्ठा device *dev, काष्ठा device_attribute *da,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा w83781d_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	u32 reg;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);

	चयन (val) अणु
	हाल 0:
	हाल 1:
		reg = w83781d_पढ़ो_value(data, W83781D_REG_PWMCLK12);
		w83781d_ग_लिखो_value(data, W83781D_REG_PWMCLK12,
				    (reg & 0xf7) | (val << 3));

		reg = w83781d_पढ़ो_value(data, W83781D_REG_BEEP_CONFIG);
		w83781d_ग_लिखो_value(data, W83781D_REG_BEEP_CONFIG,
				    (reg & 0xef) | (!val << 4));

		data->pwm2_enable = val;
		अवरोध;

	शेष:
		mutex_unlock(&data->update_lock);
		वापस -EINVAL;
	पूर्ण

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR(pwm1, S_IRUGO | S_IWUSR, show_pwm, store_pwm, 0);
अटल SENSOR_DEVICE_ATTR(pwm2, S_IRUGO | S_IWUSR, show_pwm, store_pwm, 1);
अटल SENSOR_DEVICE_ATTR(pwm3, S_IRUGO | S_IWUSR, show_pwm, store_pwm, 2);
अटल SENSOR_DEVICE_ATTR(pwm4, S_IRUGO | S_IWUSR, show_pwm, store_pwm, 3);
/* only PWM2 can be enabled/disabled */
अटल DEVICE_ATTR_RW(pwm2_enable);

अटल sमाप_प्रकार
show_sensor(काष्ठा device *dev, काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा w83781d_data *data = w83781d_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)data->sens[attr->index]);
पूर्ण

अटल sमाप_प्रकार
store_sensor(काष्ठा device *dev, काष्ठा device_attribute *da,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा w83781d_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ val;
	u32 पंचांगp;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);

	चयन (val) अणु
	हाल 1:		/* PII/Celeron diode */
		पंचांगp = w83781d_पढ़ो_value(data, W83781D_REG_SCFG1);
		w83781d_ग_लिखो_value(data, W83781D_REG_SCFG1,
				    पंचांगp | BIT_SCFG1[nr]);
		पंचांगp = w83781d_पढ़ो_value(data, W83781D_REG_SCFG2);
		w83781d_ग_लिखो_value(data, W83781D_REG_SCFG2,
				    पंचांगp | BIT_SCFG2[nr]);
		data->sens[nr] = val;
		अवरोध;
	हाल 2:		/* 3904 */
		पंचांगp = w83781d_पढ़ो_value(data, W83781D_REG_SCFG1);
		w83781d_ग_लिखो_value(data, W83781D_REG_SCFG1,
				    पंचांगp | BIT_SCFG1[nr]);
		पंचांगp = w83781d_पढ़ो_value(data, W83781D_REG_SCFG2);
		w83781d_ग_लिखो_value(data, W83781D_REG_SCFG2,
				    पंचांगp & ~BIT_SCFG2[nr]);
		data->sens[nr] = val;
		अवरोध;
	हाल W83781D_DEFAULT_BETA:
		dev_warn(dev,
			 "Sensor type %d is deprecated, please use 4 instead\n",
			 W83781D_DEFAULT_BETA);
		fallthrough;
	हाल 4:		/* thermistor */
		पंचांगp = w83781d_पढ़ो_value(data, W83781D_REG_SCFG1);
		w83781d_ग_लिखो_value(data, W83781D_REG_SCFG1,
				    पंचांगp & ~BIT_SCFG1[nr]);
		data->sens[nr] = val;
		अवरोध;
	शेष:
		dev_err(dev, "Invalid sensor type %ld; must be 1, 2, or 4\n",
		       (दीर्घ) val);
		अवरोध;
	पूर्ण

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR(temp1_type, S_IRUGO | S_IWUSR,
	show_sensor, store_sensor, 0);
अटल SENSOR_DEVICE_ATTR(temp2_type, S_IRUGO | S_IWUSR,
	show_sensor, store_sensor, 1);
अटल SENSOR_DEVICE_ATTR(temp3_type, S_IRUGO | S_IWUSR,
	show_sensor, store_sensor, 2);

/*
 * Assumes that adapter is of I2C, not ISA variety.
 * OTHERWISE DON'T CALL THIS
 */
अटल पूर्णांक
w83781d_detect_subclients(काष्ठा i2c_client *new_client)
अणु
	पूर्णांक i, val1 = 0, id;
	पूर्णांक err;
	पूर्णांक address = new_client->addr;
	अचिन्हित लघु sc_addr[2];
	काष्ठा i2c_adapter *adapter = new_client->adapter;
	काष्ठा w83781d_data *data = i2c_get_clientdata(new_client);
	क्रमागत chips kind = data->type;
	पूर्णांक num_sc = 1;

	id = i2c_adapter_id(adapter);

	अगर (क्रमce_subclients[0] == id && क्रमce_subclients[1] == address) अणु
		क्रम (i = 2; i <= 3; i++) अणु
			अगर (क्रमce_subclients[i] < 0x48 ||
			    क्रमce_subclients[i] > 0x4f) अणु
				dev_err(&new_client->dev,
					"Invalid subclient address %d; must be 0x48-0x4f\n",
					क्रमce_subclients[i]);
				err = -EINVAL;
				जाओ ERROR_SC_1;
			पूर्ण
		पूर्ण
		w83781d_ग_लिखो_value(data, W83781D_REG_I2C_SUBADDR,
				(क्रमce_subclients[2] & 0x07) |
				((क्रमce_subclients[3] & 0x07) << 4));
		sc_addr[0] = क्रमce_subclients[2];
	पूर्ण अन्यथा अणु
		val1 = w83781d_पढ़ो_value(data, W83781D_REG_I2C_SUBADDR);
		sc_addr[0] = 0x48 + (val1 & 0x07);
	पूर्ण

	अगर (kind != w83783s) अणु
		num_sc = 2;
		अगर (क्रमce_subclients[0] == id &&
		    क्रमce_subclients[1] == address) अणु
			sc_addr[1] = क्रमce_subclients[3];
		पूर्ण अन्यथा अणु
			sc_addr[1] = 0x48 + ((val1 >> 4) & 0x07);
		पूर्ण
		अगर (sc_addr[0] == sc_addr[1]) अणु
			dev_err(&new_client->dev,
			       "Duplicate addresses 0x%x for subclients.\n",
			       sc_addr[0]);
			err = -EBUSY;
			जाओ ERROR_SC_2;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_sc; i++) अणु
		data->lm75[i] = i2c_new_dummy_device(adapter, sc_addr[i]);
		अगर (IS_ERR(data->lm75[i])) अणु
			dev_err(&new_client->dev,
				"Subclient %d registration at address 0x%x failed.\n",
				i, sc_addr[i]);
			err = PTR_ERR(data->lm75[i]);
			अगर (i == 1)
				जाओ ERROR_SC_3;
			जाओ ERROR_SC_2;
		पूर्ण
	पूर्ण

	वापस 0;

/* Unकरो inits in हाल of errors */
ERROR_SC_3:
	i2c_unरेजिस्टर_device(data->lm75[0]);
ERROR_SC_2:
ERROR_SC_1:
	वापस err;
पूर्ण

#घोषणा IN_UNIT_ATTRS(X)					\
	&sensor_dev_attr_in##X##_input.dev_attr.attr,		\
	&sensor_dev_attr_in##X##_min.dev_attr.attr,		\
	&sensor_dev_attr_in##X##_max.dev_attr.attr,		\
	&sensor_dev_attr_in##X##_alarm.dev_attr.attr,		\
	&sensor_dev_attr_in##X##_beep.dev_attr.attr

#घोषणा FAN_UNIT_ATTRS(X)					\
	&sensor_dev_attr_fan##X##_input.dev_attr.attr,		\
	&sensor_dev_attr_fan##X##_min.dev_attr.attr,		\
	&sensor_dev_attr_fan##X##_भाग.dev_attr.attr,		\
	&sensor_dev_attr_fan##X##_alarm.dev_attr.attr,		\
	&sensor_dev_attr_fan##X##_beep.dev_attr.attr

#घोषणा TEMP_UNIT_ATTRS(X)					\
	&sensor_dev_attr_temp##X##_input.dev_attr.attr,		\
	&sensor_dev_attr_temp##X##_max.dev_attr.attr,		\
	&sensor_dev_attr_temp##X##_max_hyst.dev_attr.attr,	\
	&sensor_dev_attr_temp##X##_alarm.dev_attr.attr,		\
	&sensor_dev_attr_temp##X##_beep.dev_attr.attr

अटल काष्ठा attribute *w83781d_attributes[] = अणु
	IN_UNIT_ATTRS(0),
	IN_UNIT_ATTRS(2),
	IN_UNIT_ATTRS(3),
	IN_UNIT_ATTRS(4),
	IN_UNIT_ATTRS(5),
	IN_UNIT_ATTRS(6),
	FAN_UNIT_ATTRS(1),
	FAN_UNIT_ATTRS(2),
	FAN_UNIT_ATTRS(3),
	TEMP_UNIT_ATTRS(1),
	TEMP_UNIT_ATTRS(2),
	&dev_attr_cpu0_vid.attr,
	&dev_attr_vrm.attr,
	&dev_attr_alarms.attr,
	&dev_attr_beep_mask.attr,
	&sensor_dev_attr_beep_enable.dev_attr.attr,
	शून्य
पूर्ण;
अटल स्थिर काष्ठा attribute_group w83781d_group = अणु
	.attrs = w83781d_attributes,
पूर्ण;

अटल काष्ठा attribute *w83781d_attributes_in1[] = अणु
	IN_UNIT_ATTRS(1),
	शून्य
पूर्ण;
अटल स्थिर काष्ठा attribute_group w83781d_group_in1 = अणु
	.attrs = w83781d_attributes_in1,
पूर्ण;

अटल काष्ठा attribute *w83781d_attributes_in78[] = अणु
	IN_UNIT_ATTRS(7),
	IN_UNIT_ATTRS(8),
	शून्य
पूर्ण;
अटल स्थिर काष्ठा attribute_group w83781d_group_in78 = अणु
	.attrs = w83781d_attributes_in78,
पूर्ण;

अटल काष्ठा attribute *w83781d_attributes_temp3[] = अणु
	TEMP_UNIT_ATTRS(3),
	शून्य
पूर्ण;
अटल स्थिर काष्ठा attribute_group w83781d_group_temp3 = अणु
	.attrs = w83781d_attributes_temp3,
पूर्ण;

अटल काष्ठा attribute *w83781d_attributes_pwm12[] = अणु
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&dev_attr_pwm2_enable.attr,
	शून्य
पूर्ण;
अटल स्थिर काष्ठा attribute_group w83781d_group_pwm12 = अणु
	.attrs = w83781d_attributes_pwm12,
पूर्ण;

अटल काष्ठा attribute *w83781d_attributes_pwm34[] = अणु
	&sensor_dev_attr_pwm3.dev_attr.attr,
	&sensor_dev_attr_pwm4.dev_attr.attr,
	शून्य
पूर्ण;
अटल स्थिर काष्ठा attribute_group w83781d_group_pwm34 = अणु
	.attrs = w83781d_attributes_pwm34,
पूर्ण;

अटल काष्ठा attribute *w83781d_attributes_other[] = अणु
	&sensor_dev_attr_temp1_type.dev_attr.attr,
	&sensor_dev_attr_temp2_type.dev_attr.attr,
	&sensor_dev_attr_temp3_type.dev_attr.attr,
	शून्य
पूर्ण;
अटल स्थिर काष्ठा attribute_group w83781d_group_other = अणु
	.attrs = w83781d_attributes_other,
पूर्ण;

/* No clean up is करोne on error, it's up to the caller */
अटल पूर्णांक
w83781d_create_files(काष्ठा device *dev, पूर्णांक kind, पूर्णांक is_isa)
अणु
	पूर्णांक err;

	err = sysfs_create_group(&dev->kobj, &w83781d_group);
	अगर (err)
		वापस err;

	अगर (kind != w83783s) अणु
		err = sysfs_create_group(&dev->kobj, &w83781d_group_in1);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (kind != as99127f && kind != w83781d && kind != w83783s) अणु
		err = sysfs_create_group(&dev->kobj, &w83781d_group_in78);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (kind != w83783s) अणु
		err = sysfs_create_group(&dev->kobj, &w83781d_group_temp3);
		अगर (err)
			वापस err;

		अगर (kind != w83781d) अणु
			err = sysfs_chmod_file(&dev->kobj,
				&sensor_dev_attr_temp3_alarm.dev_attr.attr,
				S_IRUGO | S_IWUSR);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (kind != w83781d && kind != as99127f) अणु
		err = sysfs_create_group(&dev->kobj, &w83781d_group_pwm12);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (kind == w83782d && !is_isa) अणु
		err = sysfs_create_group(&dev->kobj, &w83781d_group_pwm34);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (kind != as99127f && kind != w83781d) अणु
		err = device_create_file(dev,
					 &sensor_dev_attr_temp1_type.dev_attr);
		अगर (err)
			वापस err;
		err = device_create_file(dev,
					 &sensor_dev_attr_temp2_type.dev_attr);
		अगर (err)
			वापस err;
		अगर (kind != w83783s) अणु
			err = device_create_file(dev,
					&sensor_dev_attr_temp3_type.dev_attr);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक
w83781d_detect(काष्ठा i2c_client *client, काष्ठा i2c_board_info *info)
अणु
	पूर्णांक val1, val2;
	काष्ठा w83781d_data *isa = w83781d_data_अगर_isa();
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक address = client->addr;
	स्थिर अक्षर *client_name;
	क्रमागत venकरोr अणु winbond, asus पूर्ण vendid;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/*
	 * We block updates of the ISA device to minimize the risk of
	 * concurrent access to the same W83781D chip through dअगरferent
	 * पूर्णांकerfaces.
	 */
	अगर (isa)
		mutex_lock(&isa->update_lock);

	अगर (i2c_smbus_पढ़ो_byte_data(client, W83781D_REG_CONFIG) & 0x80) अणु
		dev_dbg(&adapter->dev,
			"Detection of w83781d chip failed at step 3\n");
		जाओ err_nodev;
	पूर्ण

	val1 = i2c_smbus_पढ़ो_byte_data(client, W83781D_REG_BANK);
	val2 = i2c_smbus_पढ़ो_byte_data(client, W83781D_REG_CHIPMAN);
	/* Check क्रम Winbond or Asus ID अगर in bank 0 */
	अगर (!(val1 & 0x07) &&
	    ((!(val1 & 0x80) && val2 != 0xa3 && val2 != 0xc3) ||
	     ((val1 & 0x80) && val2 != 0x5c && val2 != 0x12))) अणु
		dev_dbg(&adapter->dev,
			"Detection of w83781d chip failed at step 4\n");
		जाओ err_nodev;
	पूर्ण
	/*
	 * If Winbond SMBus, check address at 0x48.
	 * Asus करोesn't support, except क्रम as99127f rev.2
	 */
	अगर ((!(val1 & 0x80) && val2 == 0xa3) ||
	    ((val1 & 0x80) && val2 == 0x5c)) अणु
		अगर (i2c_smbus_पढ़ो_byte_data(client, W83781D_REG_I2C_ADDR)
		    != address) अणु
			dev_dbg(&adapter->dev,
				"Detection of w83781d chip failed at step 5\n");
			जाओ err_nodev;
		पूर्ण
	पूर्ण

	/* Put it now पूर्णांकo bank 0 and Venकरोr ID High Byte */
	i2c_smbus_ग_लिखो_byte_data(client, W83781D_REG_BANK,
		(i2c_smbus_पढ़ो_byte_data(client, W83781D_REG_BANK)
		 & 0x78) | 0x80);

	/* Get the venकरोr ID */
	val2 = i2c_smbus_पढ़ो_byte_data(client, W83781D_REG_CHIPMAN);
	अगर (val2 == 0x5c)
		vendid = winbond;
	अन्यथा अगर (val2 == 0x12)
		vendid = asus;
	अन्यथा अणु
		dev_dbg(&adapter->dev,
			"w83781d chip vendor is neither Winbond nor Asus\n");
		जाओ err_nodev;
	पूर्ण

	/* Determine the chip type. */
	val1 = i2c_smbus_पढ़ो_byte_data(client, W83781D_REG_WCHIPID);
	अगर ((val1 == 0x10 || val1 == 0x11) && vendid == winbond)
		client_name = "w83781d";
	अन्यथा अगर (val1 == 0x30 && vendid == winbond)
		client_name = "w83782d";
	अन्यथा अगर (val1 == 0x40 && vendid == winbond && address == 0x2d)
		client_name = "w83783s";
	अन्यथा अगर (val1 == 0x31)
		client_name = "as99127f";
	अन्यथा
		जाओ err_nodev;

	अगर (val1 <= 0x30 && w83781d_alias_detect(client, val1)) अणु
		dev_dbg(&adapter->dev,
			"Device at 0x%02x appears to be the same as ISA device\n",
			address);
		जाओ err_nodev;
	पूर्ण

	अगर (isa)
		mutex_unlock(&isa->update_lock);

	strlcpy(info->type, client_name, I2C_NAME_SIZE);

	वापस 0;

 err_nodev:
	अगर (isa)
		mutex_unlock(&isa->update_lock);
	वापस -ENODEV;
पूर्ण

अटल व्योम w83781d_हटाओ_files(काष्ठा device *dev)
अणु
	sysfs_हटाओ_group(&dev->kobj, &w83781d_group);
	sysfs_हटाओ_group(&dev->kobj, &w83781d_group_in1);
	sysfs_हटाओ_group(&dev->kobj, &w83781d_group_in78);
	sysfs_हटाओ_group(&dev->kobj, &w83781d_group_temp3);
	sysfs_हटाओ_group(&dev->kobj, &w83781d_group_pwm12);
	sysfs_हटाओ_group(&dev->kobj, &w83781d_group_pwm34);
	sysfs_हटाओ_group(&dev->kobj, &w83781d_group_other);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id w83781d_ids[];

अटल पूर्णांक w83781d_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा w83781d_data *data;
	पूर्णांक err;

	data = devm_kzalloc(dev, माप(काष्ठा w83781d_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->lock);
	mutex_init(&data->update_lock);

	data->type = i2c_match_id(w83781d_ids, client)->driver_data;
	data->client = client;

	/* attach secondary i2c lm75-like clients */
	err = w83781d_detect_subclients(client);
	अगर (err)
		वापस err;

	/* Initialize the chip */
	w83781d_init_device(dev);

	/* Register sysfs hooks */
	err = w83781d_create_files(dev, data->type, 0);
	अगर (err)
		जाओ निकास_हटाओ_files;

	data->hwmon_dev = hwmon_device_रेजिस्टर(dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		जाओ निकास_हटाओ_files;
	पूर्ण

	वापस 0;

 निकास_हटाओ_files:
	w83781d_हटाओ_files(dev);
	i2c_unरेजिस्टर_device(data->lm75[0]);
	i2c_unरेजिस्टर_device(data->lm75[1]);
	वापस err;
पूर्ण

अटल पूर्णांक
w83781d_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा w83781d_data *data = i2c_get_clientdata(client);
	काष्ठा device *dev = &client->dev;

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	w83781d_हटाओ_files(dev);

	i2c_unरेजिस्टर_device(data->lm75[0]);
	i2c_unरेजिस्टर_device(data->lm75[1]);

	वापस 0;
पूर्ण

अटल पूर्णांक
w83781d_पढ़ो_value_i2c(काष्ठा w83781d_data *data, u16 reg)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक res, bank;
	काष्ठा i2c_client *cl;

	bank = (reg >> 8) & 0x0f;
	अगर (bank > 2)
		/* चयन banks */
		i2c_smbus_ग_लिखो_byte_data(client, W83781D_REG_BANK,
					  bank);
	अगर (bank == 0 || bank > 2) अणु
		res = i2c_smbus_पढ़ो_byte_data(client, reg & 0xff);
	पूर्ण अन्यथा अणु
		/* चयन to subclient */
		cl = data->lm75[bank - 1];
		/* convert from ISA to LM75 I2C addresses */
		चयन (reg & 0xff) अणु
		हाल 0x50:	/* TEMP */
			res = i2c_smbus_पढ़ो_word_swapped(cl, 0);
			अवरोध;
		हाल 0x52:	/* CONFIG */
			res = i2c_smbus_पढ़ो_byte_data(cl, 1);
			अवरोध;
		हाल 0x53:	/* HYST */
			res = i2c_smbus_पढ़ो_word_swapped(cl, 2);
			अवरोध;
		हाल 0x55:	/* OVER */
		शेष:
			res = i2c_smbus_पढ़ो_word_swapped(cl, 3);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (bank > 2)
		i2c_smbus_ग_लिखो_byte_data(client, W83781D_REG_BANK, 0);

	वापस res;
पूर्ण

अटल पूर्णांक
w83781d_ग_लिखो_value_i2c(काष्ठा w83781d_data *data, u16 reg, u16 value)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक bank;
	काष्ठा i2c_client *cl;

	bank = (reg >> 8) & 0x0f;
	अगर (bank > 2)
		/* चयन banks */
		i2c_smbus_ग_लिखो_byte_data(client, W83781D_REG_BANK,
					  bank);
	अगर (bank == 0 || bank > 2) अणु
		i2c_smbus_ग_लिखो_byte_data(client, reg & 0xff,
					  value & 0xff);
	पूर्ण अन्यथा अणु
		/* चयन to subclient */
		cl = data->lm75[bank - 1];
		/* convert from ISA to LM75 I2C addresses */
		चयन (reg & 0xff) अणु
		हाल 0x52:	/* CONFIG */
			i2c_smbus_ग_लिखो_byte_data(cl, 1, value & 0xff);
			अवरोध;
		हाल 0x53:	/* HYST */
			i2c_smbus_ग_लिखो_word_swapped(cl, 2, value);
			अवरोध;
		हाल 0x55:	/* OVER */
			i2c_smbus_ग_लिखो_word_swapped(cl, 3, value);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (bank > 2)
		i2c_smbus_ग_लिखो_byte_data(client, W83781D_REG_BANK, 0);

	वापस 0;
पूर्ण

अटल व्योम
w83781d_init_device(काष्ठा device *dev)
अणु
	काष्ठा w83781d_data *data = dev_get_drvdata(dev);
	पूर्णांक i, p;
	पूर्णांक type = data->type;
	u8 पंचांगp;

	अगर (reset && type != as99127f) अणु /*
					  * this resets रेजिस्टरs we करोn't have
					  * करोcumentation क्रम on the as99127f
					  */
		/*
		 * Resetting the chip has been the शेष क्रम a दीर्घ समय,
		 * but it causes the BIOS initializations (fan घड़ी भागiders,
		 * thermal sensor types...) to be lost, so it is now optional.
		 * It might even go away अगर nobody reports it as being useful,
		 * as I see very little reason why this would be needed at
		 * all.
		 */
		dev_info(dev,
			 "If reset=1 solved a problem you were having, please report!\n");

		/* save these रेजिस्टरs */
		i = w83781d_पढ़ो_value(data, W83781D_REG_BEEP_CONFIG);
		p = w83781d_पढ़ो_value(data, W83781D_REG_PWMCLK12);
		/*
		 * Reset all except Watchकरोg values and last conversion values
		 * This sets fan-भागs to 2, among others
		 */
		w83781d_ग_लिखो_value(data, W83781D_REG_CONFIG, 0x80);
		/*
		 * Restore the रेजिस्टरs and disable घातer-on abnormal beep.
		 * This saves FAN 1/2/3 input/output values set by BIOS.
		 */
		w83781d_ग_लिखो_value(data, W83781D_REG_BEEP_CONFIG, i | 0x80);
		w83781d_ग_लिखो_value(data, W83781D_REG_PWMCLK12, p);
		/*
		 * Disable master beep-enable (reset turns it on).
		 * Inभागidual beep_mask should be reset to off but क्रम some
		 * reason disabling this bit helps some people not get beeped
		 */
		w83781d_ग_लिखो_value(data, W83781D_REG_BEEP_INTS2, 0);
	पूर्ण

	/*
	 * Disable घातer-on abnormal beep, as advised by the datasheet.
	 * Alपढ़ोy करोne अगर reset=1.
	 */
	अगर (init && !reset && type != as99127f) अणु
		i = w83781d_पढ़ो_value(data, W83781D_REG_BEEP_CONFIG);
		w83781d_ग_लिखो_value(data, W83781D_REG_BEEP_CONFIG, i | 0x80);
	पूर्ण

	data->vrm = vid_which_vrm();

	अगर ((type != w83781d) && (type != as99127f)) अणु
		पंचांगp = w83781d_पढ़ो_value(data, W83781D_REG_SCFG1);
		क्रम (i = 1; i <= 3; i++) अणु
			अगर (!(पंचांगp & BIT_SCFG1[i - 1])) अणु
				data->sens[i - 1] = 4;
			पूर्ण अन्यथा अणु
				अगर (w83781d_पढ़ो_value
				    (data,
				     W83781D_REG_SCFG2) & BIT_SCFG2[i - 1])
					data->sens[i - 1] = 1;
				अन्यथा
					data->sens[i - 1] = 2;
			पूर्ण
			अगर (type == w83783s && i == 2)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (init && type != as99127f) अणु
		/* Enable temp2 */
		पंचांगp = w83781d_पढ़ो_value(data, W83781D_REG_TEMP2_CONFIG);
		अगर (पंचांगp & 0x01) अणु
			dev_warn(dev,
				 "Enabling temp2, readings might not make sense\n");
			w83781d_ग_लिखो_value(data, W83781D_REG_TEMP2_CONFIG,
				पंचांगp & 0xfe);
		पूर्ण

		/* Enable temp3 */
		अगर (type != w83783s) अणु
			पंचांगp = w83781d_पढ़ो_value(data,
				W83781D_REG_TEMP3_CONFIG);
			अगर (पंचांगp & 0x01) अणु
				dev_warn(dev,
					 "Enabling temp3, readings might not make sense\n");
				w83781d_ग_लिखो_value(data,
					W83781D_REG_TEMP3_CONFIG, पंचांगp & 0xfe);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Start monitoring */
	w83781d_ग_लिखो_value(data, W83781D_REG_CONFIG,
			    (w83781d_पढ़ो_value(data,
						W83781D_REG_CONFIG) & 0xf7)
			    | 0x01);

	/* A few vars need to be filled upon startup */
	क्रम (i = 0; i < 3; i++) अणु
		data->fan_min[i] = w83781d_पढ़ो_value(data,
					W83781D_REG_FAN_MIN(i));
	पूर्ण

	mutex_init(&data->update_lock);
पूर्ण

अटल काष्ठा w83781d_data *w83781d_update_device(काष्ठा device *dev)
अणु
	काष्ठा w83781d_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) अणु
		dev_dbg(dev, "Starting device update\n");

		क्रम (i = 0; i <= 8; i++) अणु
			अगर (data->type == w83783s && i == 1)
				जारी;	/* 783S has no in1 */
			data->in[i] =
			    w83781d_पढ़ो_value(data, W83781D_REG_IN(i));
			data->in_min[i] =
			    w83781d_पढ़ो_value(data, W83781D_REG_IN_MIN(i));
			data->in_max[i] =
			    w83781d_पढ़ो_value(data, W83781D_REG_IN_MAX(i));
			अगर ((data->type != w83782d) && (i == 6))
				अवरोध;
		पूर्ण
		क्रम (i = 0; i < 3; i++) अणु
			data->fan[i] =
			    w83781d_पढ़ो_value(data, W83781D_REG_FAN(i));
			data->fan_min[i] =
			    w83781d_पढ़ो_value(data, W83781D_REG_FAN_MIN(i));
		पूर्ण
		अगर (data->type != w83781d && data->type != as99127f) अणु
			क्रम (i = 0; i < 4; i++) अणु
				data->pwm[i] =
				    w83781d_पढ़ो_value(data,
						       W83781D_REG_PWM[i]);
				/* Only W83782D on SMBus has PWM3 and PWM4 */
				अगर ((data->type != w83782d || !client)
				    && i == 1)
					अवरोध;
			पूर्ण
			/* Only PWM2 can be disabled */
			data->pwm2_enable = (w83781d_पढ़ो_value(data,
					     W83781D_REG_PWMCLK12) & 0x08) >> 3;
		पूर्ण

		data->temp = w83781d_पढ़ो_value(data, W83781D_REG_TEMP(1));
		data->temp_max =
		    w83781d_पढ़ो_value(data, W83781D_REG_TEMP_OVER(1));
		data->temp_max_hyst =
		    w83781d_पढ़ो_value(data, W83781D_REG_TEMP_HYST(1));
		data->temp_add[0] =
		    w83781d_पढ़ो_value(data, W83781D_REG_TEMP(2));
		data->temp_max_add[0] =
		    w83781d_पढ़ो_value(data, W83781D_REG_TEMP_OVER(2));
		data->temp_max_hyst_add[0] =
		    w83781d_पढ़ो_value(data, W83781D_REG_TEMP_HYST(2));
		अगर (data->type != w83783s) अणु
			data->temp_add[1] =
			    w83781d_पढ़ो_value(data, W83781D_REG_TEMP(3));
			data->temp_max_add[1] =
			    w83781d_पढ़ो_value(data,
					       W83781D_REG_TEMP_OVER(3));
			data->temp_max_hyst_add[1] =
			    w83781d_पढ़ो_value(data,
					       W83781D_REG_TEMP_HYST(3));
		पूर्ण
		i = w83781d_पढ़ो_value(data, W83781D_REG_VID_FANDIV);
		data->vid = i & 0x0f;
		data->vid |= (w83781d_पढ़ो_value(data,
					W83781D_REG_CHIPID) & 0x01) << 4;
		data->fan_भाग[0] = (i >> 4) & 0x03;
		data->fan_भाग[1] = (i >> 6) & 0x03;
		data->fan_भाग[2] = (w83781d_पढ़ो_value(data,
					W83781D_REG_PIN) >> 6) & 0x03;
		अगर ((data->type != w83781d) && (data->type != as99127f)) अणु
			i = w83781d_पढ़ो_value(data, W83781D_REG_VBAT);
			data->fan_भाग[0] |= (i >> 3) & 0x04;
			data->fan_भाग[1] |= (i >> 4) & 0x04;
			data->fan_भाग[2] |= (i >> 5) & 0x04;
		पूर्ण
		अगर (data->type == w83782d) अणु
			data->alarms = w83781d_पढ़ो_value(data,
						W83782D_REG_ALARM1)
				     | (w83781d_पढ़ो_value(data,
						W83782D_REG_ALARM2) << 8)
				     | (w83781d_पढ़ो_value(data,
						W83782D_REG_ALARM3) << 16);
		पूर्ण अन्यथा अगर (data->type == w83783s) अणु
			data->alarms = w83781d_पढ़ो_value(data,
						W83782D_REG_ALARM1)
				     | (w83781d_पढ़ो_value(data,
						W83782D_REG_ALARM2) << 8);
		पूर्ण अन्यथा अणु
			/*
			 * No real-समय status रेजिस्टरs, fall back to
			 * पूर्णांकerrupt status रेजिस्टरs
			 */
			data->alarms = w83781d_पढ़ो_value(data,
						W83781D_REG_ALARM1)
				     | (w83781d_पढ़ो_value(data,
						W83781D_REG_ALARM2) << 8);
		पूर्ण
		i = w83781d_पढ़ो_value(data, W83781D_REG_BEEP_INTS2);
		data->beep_mask = (i << 8) +
		    w83781d_पढ़ो_value(data, W83781D_REG_BEEP_INTS1);
		अगर ((data->type != w83781d) && (data->type != as99127f)) अणु
			data->beep_mask |=
			    w83781d_पढ़ो_value(data,
					       W83781D_REG_BEEP_INTS3) << 16;
		पूर्ण
		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id w83781d_ids[] = अणु
	अणु "w83781d", w83781d, पूर्ण,
	अणु "w83782d", w83782d, पूर्ण,
	अणु "w83783s", w83783s, पूर्ण,
	अणु "as99127f", as99127f पूर्ण,
	अणु /* LIST END */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, w83781d_ids);

अटल काष्ठा i2c_driver w83781d_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name = "w83781d",
	पूर्ण,
	.probe_new	= w83781d_probe,
	.हटाओ		= w83781d_हटाओ,
	.id_table	= w83781d_ids,
	.detect		= w83781d_detect,
	.address_list	= normal_i2c,
पूर्ण;

/*
 * ISA related code
 */
#अगर_घोषित CONFIG_ISA

/* ISA device, अगर found */
अटल काष्ठा platक्रमm_device *pdev;

अटल अचिन्हित लघु isa_address = 0x290;

/*
 * I2C devices get this name attribute स्वतःmatically, but क्रम ISA devices
 * we must create it by ourselves.
 */
अटल sमाप_प्रकार
name_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा w83781d_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%s\n", data->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल काष्ठा w83781d_data *w83781d_data_अगर_isa(व्योम)
अणु
	वापस pdev ? platक्रमm_get_drvdata(pdev) : शून्य;
पूर्ण

/* Returns 1 अगर the I2C chip appears to be an alias of the ISA chip */
अटल पूर्णांक w83781d_alias_detect(काष्ठा i2c_client *client, u8 chipid)
अणु
	काष्ठा w83781d_data *isa;
	पूर्णांक i;

	अगर (!pdev)	/* No ISA chip */
		वापस 0;

	isa = platक्रमm_get_drvdata(pdev);

	अगर (w83781d_पढ़ो_value(isa, W83781D_REG_I2C_ADDR) != client->addr)
		वापस 0;	/* Address करोesn't match */
	अगर (w83781d_पढ़ो_value(isa, W83781D_REG_WCHIPID) != chipid)
		वापस 0;	/* Chip type करोesn't match */

	/*
	 * We compare all the limit रेजिस्टरs, the config रेजिस्टर and the
	 * पूर्णांकerrupt mask रेजिस्टरs
	 */
	क्रम (i = 0x2b; i <= 0x3d; i++) अणु
		अगर (w83781d_पढ़ो_value(isa, i) !=
		    i2c_smbus_पढ़ो_byte_data(client, i))
			वापस 0;
	पूर्ण
	अगर (w83781d_पढ़ो_value(isa, W83781D_REG_CONFIG) !=
	    i2c_smbus_पढ़ो_byte_data(client, W83781D_REG_CONFIG))
		वापस 0;
	क्रम (i = 0x43; i <= 0x46; i++) अणु
		अगर (w83781d_पढ़ो_value(isa, i) !=
		    i2c_smbus_पढ़ो_byte_data(client, i))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक
w83781d_पढ़ो_value_isa(काष्ठा w83781d_data *data, u16 reg)
अणु
	पूर्णांक word_sized, res;

	word_sized = (((reg & 0xff00) == 0x100)
		      || ((reg & 0xff00) == 0x200))
	    && (((reg & 0x00ff) == 0x50)
		|| ((reg & 0x00ff) == 0x53)
		|| ((reg & 0x00ff) == 0x55));
	अगर (reg & 0xff00) अणु
		outb_p(W83781D_REG_BANK,
		       data->isa_addr + W83781D_ADDR_REG_OFFSET);
		outb_p(reg >> 8,
		       data->isa_addr + W83781D_DATA_REG_OFFSET);
	पूर्ण
	outb_p(reg & 0xff, data->isa_addr + W83781D_ADDR_REG_OFFSET);
	res = inb_p(data->isa_addr + W83781D_DATA_REG_OFFSET);
	अगर (word_sized) अणु
		outb_p((reg & 0xff) + 1,
		       data->isa_addr + W83781D_ADDR_REG_OFFSET);
		res =
		    (res << 8) + inb_p(data->isa_addr +
				       W83781D_DATA_REG_OFFSET);
	पूर्ण
	अगर (reg & 0xff00) अणु
		outb_p(W83781D_REG_BANK,
		       data->isa_addr + W83781D_ADDR_REG_OFFSET);
		outb_p(0, data->isa_addr + W83781D_DATA_REG_OFFSET);
	पूर्ण
	वापस res;
पूर्ण

अटल व्योम
w83781d_ग_लिखो_value_isa(काष्ठा w83781d_data *data, u16 reg, u16 value)
अणु
	पूर्णांक word_sized;

	word_sized = (((reg & 0xff00) == 0x100)
		      || ((reg & 0xff00) == 0x200))
	    && (((reg & 0x00ff) == 0x53)
		|| ((reg & 0x00ff) == 0x55));
	अगर (reg & 0xff00) अणु
		outb_p(W83781D_REG_BANK,
		       data->isa_addr + W83781D_ADDR_REG_OFFSET);
		outb_p(reg >> 8,
		       data->isa_addr + W83781D_DATA_REG_OFFSET);
	पूर्ण
	outb_p(reg & 0xff, data->isa_addr + W83781D_ADDR_REG_OFFSET);
	अगर (word_sized) अणु
		outb_p(value >> 8,
		       data->isa_addr + W83781D_DATA_REG_OFFSET);
		outb_p((reg & 0xff) + 1,
		       data->isa_addr + W83781D_ADDR_REG_OFFSET);
	पूर्ण
	outb_p(value & 0xff, data->isa_addr + W83781D_DATA_REG_OFFSET);
	अगर (reg & 0xff00) अणु
		outb_p(W83781D_REG_BANK,
		       data->isa_addr + W83781D_ADDR_REG_OFFSET);
		outb_p(0, data->isa_addr + W83781D_DATA_REG_OFFSET);
	पूर्ण
पूर्ण

/*
 * The SMBus locks itself, usually, but nothing may access the Winbond between
 * bank चयनes. ISA access must always be locked explicitly!
 * We ignore the W83781D BUSY flag at this moment - it could lead to deadlocks,
 * would slow करोwn the W83781D access and should not be necessary.
 * There are some ugly typecasts here, but the good news is - they should
 * nowhere अन्यथा be necessary!
 */
अटल पूर्णांक
w83781d_पढ़ो_value(काष्ठा w83781d_data *data, u16 reg)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक res;

	mutex_lock(&data->lock);
	अगर (client)
		res = w83781d_पढ़ो_value_i2c(data, reg);
	अन्यथा
		res = w83781d_पढ़ो_value_isa(data, reg);
	mutex_unlock(&data->lock);
	वापस res;
पूर्ण

अटल पूर्णांक
w83781d_ग_लिखो_value(काष्ठा w83781d_data *data, u16 reg, u16 value)
अणु
	काष्ठा i2c_client *client = data->client;

	mutex_lock(&data->lock);
	अगर (client)
		w83781d_ग_लिखो_value_i2c(data, reg, value);
	अन्यथा
		w83781d_ग_लिखो_value_isa(data, reg, value);
	mutex_unlock(&data->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक
w83781d_isa_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err, reg;
	काष्ठा w83781d_data *data;
	काष्ठा resource *res;

	/* Reserve the ISA region */
	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!devm_request_region(&pdev->dev,
				 res->start + W83781D_ADDR_REG_OFFSET, 2,
				 "w83781d"))
		वापस -EBUSY;

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा w83781d_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	mutex_init(&data->lock);
	data->isa_addr = res->start;
	platक्रमm_set_drvdata(pdev, data);

	reg = w83781d_पढ़ो_value(data, W83781D_REG_WCHIPID);
	चयन (reg) अणु
	हाल 0x30:
		data->type = w83782d;
		data->name = "w83782d";
		अवरोध;
	शेष:
		data->type = w83781d;
		data->name = "w83781d";
	पूर्ण

	/* Initialize the W83781D chip */
	w83781d_init_device(&pdev->dev);

	/* Register sysfs hooks */
	err = w83781d_create_files(&pdev->dev, data->type, 1);
	अगर (err)
		जाओ निकास_हटाओ_files;

	err = device_create_file(&pdev->dev, &dev_attr_name);
	अगर (err)
		जाओ निकास_हटाओ_files;

	data->hwmon_dev = hwmon_device_रेजिस्टर(&pdev->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		जाओ निकास_हटाओ_files;
	पूर्ण

	वापस 0;

 निकास_हटाओ_files:
	w83781d_हटाओ_files(&pdev->dev);
	device_हटाओ_file(&pdev->dev, &dev_attr_name);
	वापस err;
पूर्ण

अटल पूर्णांक
w83781d_isa_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा w83781d_data *data = platक्रमm_get_drvdata(pdev);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	w83781d_हटाओ_files(&pdev->dev);
	device_हटाओ_file(&pdev->dev, &dev_attr_name);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver w83781d_isa_driver = अणु
	.driver = अणु
		.name = "w83781d",
	पूर्ण,
	.probe = w83781d_isa_probe,
	.हटाओ = w83781d_isa_हटाओ,
पूर्ण;

/* वापस 1 अगर a supported chip is found, 0 otherwise */
अटल पूर्णांक __init
w83781d_isa_found(अचिन्हित लघु address)
अणु
	पूर्णांक val, save, found = 0;
	पूर्णांक port;

	/*
	 * Some boards declare base+0 to base+7 as a PNP device, some base+4
	 * to base+7 and some base+5 to base+6. So we better request each port
	 * inभागidually क्रम the probing phase.
	 */
	क्रम (port = address; port < address + W83781D_EXTENT; port++) अणु
		अगर (!request_region(port, 1, "w83781d")) अणु
			pr_debug("Failed to request port 0x%x\n", port);
			जाओ release;
		पूर्ण
	पूर्ण

#घोषणा REALLY_SLOW_IO
	/*
	 * We need the समयouts क्रम at least some W83781D-like
	 * chips. But only अगर we पढ़ो 'undefined' रेजिस्टरs.
	 */
	val = inb_p(address + 1);
	अगर (inb_p(address + 2) != val
	 || inb_p(address + 3) != val
	 || inb_p(address + 7) != val) अणु
		pr_debug("Detection failed at step %d\n", 1);
		जाओ release;
	पूर्ण
#अघोषित REALLY_SLOW_IO

	/*
	 * We should be able to change the 7 LSB of the address port. The
	 * MSB (busy flag) should be clear initially, set after the ग_लिखो.
	 */
	save = inb_p(address + W83781D_ADDR_REG_OFFSET);
	अगर (save & 0x80) अणु
		pr_debug("Detection failed at step %d\n", 2);
		जाओ release;
	पूर्ण
	val = ~save & 0x7f;
	outb_p(val, address + W83781D_ADDR_REG_OFFSET);
	अगर (inb_p(address + W83781D_ADDR_REG_OFFSET) != (val | 0x80)) अणु
		outb_p(save, address + W83781D_ADDR_REG_OFFSET);
		pr_debug("Detection failed at step %d\n", 3);
		जाओ release;
	पूर्ण

	/* We found a device, now see अगर it could be a W83781D */
	outb_p(W83781D_REG_CONFIG, address + W83781D_ADDR_REG_OFFSET);
	val = inb_p(address + W83781D_DATA_REG_OFFSET);
	अगर (val & 0x80) अणु
		pr_debug("Detection failed at step %d\n", 4);
		जाओ release;
	पूर्ण
	outb_p(W83781D_REG_BANK, address + W83781D_ADDR_REG_OFFSET);
	save = inb_p(address + W83781D_DATA_REG_OFFSET);
	outb_p(W83781D_REG_CHIPMAN, address + W83781D_ADDR_REG_OFFSET);
	val = inb_p(address + W83781D_DATA_REG_OFFSET);
	अगर ((!(save & 0x80) && (val != 0xa3))
	 || ((save & 0x80) && (val != 0x5c))) अणु
		pr_debug("Detection failed at step %d\n", 5);
		जाओ release;
	पूर्ण
	outb_p(W83781D_REG_I2C_ADDR, address + W83781D_ADDR_REG_OFFSET);
	val = inb_p(address + W83781D_DATA_REG_OFFSET);
	अगर (val < 0x03 || val > 0x77) अणु	/* Not a valid I2C address */
		pr_debug("Detection failed at step %d\n", 6);
		जाओ release;
	पूर्ण

	/* The busy flag should be clear again */
	अगर (inb_p(address + W83781D_ADDR_REG_OFFSET) & 0x80) अणु
		pr_debug("Detection failed at step %d\n", 7);
		जाओ release;
	पूर्ण

	/* Determine the chip type */
	outb_p(W83781D_REG_BANK, address + W83781D_ADDR_REG_OFFSET);
	save = inb_p(address + W83781D_DATA_REG_OFFSET);
	outb_p(save & 0xf8, address + W83781D_DATA_REG_OFFSET);
	outb_p(W83781D_REG_WCHIPID, address + W83781D_ADDR_REG_OFFSET);
	val = inb_p(address + W83781D_DATA_REG_OFFSET);
	अगर ((val & 0xfe) == 0x10	/* W83781D */
	 || val == 0x30)		/* W83782D */
		found = 1;

	अगर (found)
		pr_info("Found a %s chip at %#x\n",
			val == 0x30 ? "W83782D" : "W83781D", (पूर्णांक)address);

 release:
	क्रम (port--; port >= address; port--)
		release_region(port, 1);
	वापस found;
पूर्ण

अटल पूर्णांक __init
w83781d_isa_device_add(अचिन्हित लघु address)
अणु
	काष्ठा resource res = अणु
		.start	= address,
		.end	= address + W83781D_EXTENT - 1,
		.name	= "w83781d",
		.flags	= IORESOURCE_IO,
	पूर्ण;
	पूर्णांक err;

	pdev = platक्रमm_device_alloc("w83781d", address);
	अगर (!pdev) अणु
		err = -ENOMEM;
		pr_err("Device allocation failed\n");
		जाओ निकास;
	पूर्ण

	err = platक्रमm_device_add_resources(pdev, &res, 1);
	अगर (err) अणु
		pr_err("Device resource addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	err = platक्रमm_device_add(pdev);
	अगर (err) अणु
		pr_err("Device addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	वापस 0;

 निकास_device_put:
	platक्रमm_device_put(pdev);
 निकास:
	pdev = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक __init
w83781d_isa_रेजिस्टर(व्योम)
अणु
	पूर्णांक res;

	अगर (w83781d_isa_found(isa_address)) अणु
		res = platक्रमm_driver_रेजिस्टर(&w83781d_isa_driver);
		अगर (res)
			जाओ निकास;

		/* Sets global pdev as a side effect */
		res = w83781d_isa_device_add(isa_address);
		अगर (res)
			जाओ निकास_unreg_isa_driver;
	पूर्ण

	वापस 0;

निकास_unreg_isa_driver:
	platक्रमm_driver_unरेजिस्टर(&w83781d_isa_driver);
निकास:
	वापस res;
पूर्ण

अटल व्योम
w83781d_isa_unरेजिस्टर(व्योम)
अणु
	अगर (pdev) अणु
		platक्रमm_device_unरेजिस्टर(pdev);
		platक्रमm_driver_unरेजिस्टर(&w83781d_isa_driver);
	पूर्ण
पूर्ण
#अन्यथा /* !CONFIG_ISA */

अटल काष्ठा w83781d_data *w83781d_data_अगर_isa(व्योम)
अणु
	वापस शून्य;
पूर्ण

अटल पूर्णांक
w83781d_alias_detect(काष्ठा i2c_client *client, u8 chipid)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
w83781d_पढ़ो_value(काष्ठा w83781d_data *data, u16 reg)
अणु
	पूर्णांक res;

	mutex_lock(&data->lock);
	res = w83781d_पढ़ो_value_i2c(data, reg);
	mutex_unlock(&data->lock);

	वापस res;
पूर्ण

अटल पूर्णांक
w83781d_ग_लिखो_value(काष्ठा w83781d_data *data, u16 reg, u16 value)
अणु
	mutex_lock(&data->lock);
	w83781d_ग_लिखो_value_i2c(data, reg, value);
	mutex_unlock(&data->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक __init
w83781d_isa_रेजिस्टर(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम
w83781d_isa_unरेजिस्टर(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ISA */

अटल पूर्णांक __init
sensors_w83781d_init(व्योम)
अणु
	पूर्णांक res;

	/*
	 * We रेजिस्टर the ISA device first, so that we can skip the
	 * registration of an I2C पूर्णांकerface to the same device.
	 */
	res = w83781d_isa_रेजिस्टर();
	अगर (res)
		जाओ निकास;

	res = i2c_add_driver(&w83781d_driver);
	अगर (res)
		जाओ निकास_unreg_isa;

	वापस 0;

 निकास_unreg_isa:
	w83781d_isa_unरेजिस्टर();
 निकास:
	वापस res;
पूर्ण

अटल व्योम __निकास
sensors_w83781d_निकास(व्योम)
अणु
	w83781d_isa_unरेजिस्टर();
	i2c_del_driver(&w83781d_driver);
पूर्ण

MODULE_AUTHOR("Frodo Looijaard <frodol@dds.nl>, "
	      "Philip Edelbrock <phil@netroedge.com>, "
	      "and Mark Studebaker <mdsxyz123@yahoo.com>");
MODULE_DESCRIPTION("W83781D driver");
MODULE_LICENSE("GPL");

module_init(sensors_w83781d_init);
module_निकास(sensors_w83781d_निकास);
