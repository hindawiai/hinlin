<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  pc87360.c - Part of lm_sensors, Linux kernel modules
 *              क्रम hardware monitoring
 *  Copyright (C) 2004, 2007 Jean Delvare <jdelvare@suse.de>
 *
 *  Copied from smsc47m1.c:
 *  Copyright (C) 2002 Mark D. Studebaker <mdsxyz123@yahoo.com>
 *
 *  Supports the following chips:
 *
 *  Chip        #vin    #fan    #pwm    #temp   devid
 *  PC87360     -       2       2       -       0xE1
 *  PC87363     -       2       2       -       0xE8
 *  PC87364     -       3       3       -       0xE4
 *  PC87365     11      3       3       2       0xE5
 *  PC87366     11      3       3       3-4     0xE9
 *
 *  This driver assumes that no more than one chip is present, and one of
 *  the standard Super-I/O addresses is used (0x2E/0x2F or 0x4E/0x4F).
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

अटल u8 devid;
अटल काष्ठा platक्रमm_device *pdev;
अटल अचिन्हित लघु extra_isa[3];
अटल u8 confreg[4];

अटल पूर्णांक init = 1;
module_param(init, पूर्णांक, 0);
MODULE_PARM_DESC(init,
"Chip initialization level:\n"
" 0: None\n"
"*1: Forcibly enable internal voltage and temperature channels, except in9\n"
" 2: Forcibly enable all voltage and temperature channels, except in9\n"
" 3: Forcibly enable all voltage and temperature channels, including in9");

अटल अचिन्हित लघु क्रमce_id;
module_param(क्रमce_id, uलघु, 0);
MODULE_PARM_DESC(क्रमce_id, "Override the detected device ID");

/*
 * Super-I/O रेजिस्टरs and operations
 */

#घोषणा DEV	0x07	/* Register: Logical device select */
#घोषणा DEVID	0x20	/* Register: Device ID */
#घोषणा ACT	0x30	/* Register: Device activation */
#घोषणा BASE	0x60	/* Register: Base address */

#घोषणा FSCM	0x09	/* Logical device: fans */
#घोषणा VLM	0x0d	/* Logical device: voltages */
#घोषणा TMS	0x0e	/* Logical device: temperatures */
#घोषणा LDNI_MAX 3
अटल स्थिर u8 logdev[LDNI_MAX] = अणु FSCM, VLM, TMS पूर्ण;

#घोषणा LD_FAN		0
#घोषणा LD_IN		1
#घोषणा LD_TEMP		2

अटल अंतरभूत व्योम superio_outb(पूर्णांक sioaddr, पूर्णांक reg, पूर्णांक val)
अणु
	outb(reg, sioaddr);
	outb(val, sioaddr + 1);
पूर्ण

अटल अंतरभूत पूर्णांक superio_inb(पूर्णांक sioaddr, पूर्णांक reg)
अणु
	outb(reg, sioaddr);
	वापस inb(sioaddr + 1);
पूर्ण

अटल अंतरभूत व्योम superio_निकास(पूर्णांक sioaddr)
अणु
	outb(0x02, sioaddr);
	outb(0x02, sioaddr + 1);
पूर्ण

/*
 * Logical devices
 */

#घोषणा PC87360_EXTENT		0x10
#घोषणा PC87365_REG_BANK	0x09
#घोषणा NO_BANK			0xff

/*
 * Fan रेजिस्टरs and conversions
 */

/* nr has to be 0 or 1 (PC87360/87363) or 2 (PC87364/87365/87366) */
#घोषणा PC87360_REG_PRESCALE(nr)	(0x00 + 2 * (nr))
#घोषणा PC87360_REG_PWM(nr)		(0x01 + 2 * (nr))
#घोषणा PC87360_REG_FAN_MIN(nr)		(0x06 + 3 * (nr))
#घोषणा PC87360_REG_FAN(nr)		(0x07 + 3 * (nr))
#घोषणा PC87360_REG_FAN_STATUS(nr)	(0x08 + 3 * (nr))

#घोषणा FAN_FROM_REG(val, भाग)		((val) == 0 ? 0 : \
					 480000 / ((val) * (भाग)))
#घोषणा FAN_TO_REG(val, भाग)		((val) <= 100 ? 0 : \
					 480000 / ((val) * (भाग)))
#घोषणा FAN_DIV_FROM_REG(val)		(1 << (((val) >> 5) & 0x03))
#घोषणा FAN_STATUS_FROM_REG(val)	((val) & 0x07)

#घोषणा FAN_CONFIG_MONITOR(val, nr)	(((val) >> (2 + (nr) * 3)) & 1)
#घोषणा FAN_CONFIG_CONTROL(val, nr)	(((val) >> (3 + (nr) * 3)) & 1)
#घोषणा FAN_CONFIG_INVERT(val, nr)	(((val) >> (4 + (nr) * 3)) & 1)

#घोषणा PWM_FROM_REG(val, inv)		((inv) ? 255 - (val) : (val))
अटल अंतरभूत u8 PWM_TO_REG(पूर्णांक val, पूर्णांक inv)
अणु
	अगर (inv)
		val = 255 - val;
	अगर (val < 0)
		वापस 0;
	अगर (val > 255)
		वापस 255;
	वापस val;
पूर्ण

/*
 * Voltage रेजिस्टरs and conversions
 */

#घोषणा PC87365_REG_IN_CONVRATE		0x07
#घोषणा PC87365_REG_IN_CONFIG		0x08
#घोषणा PC87365_REG_IN			0x0B
#घोषणा PC87365_REG_IN_MIN		0x0D
#घोषणा PC87365_REG_IN_MAX		0x0C
#घोषणा PC87365_REG_IN_STATUS		0x0A
#घोषणा PC87365_REG_IN_ALARMS1		0x00
#घोषणा PC87365_REG_IN_ALARMS2		0x01
#घोषणा PC87365_REG_VID			0x06

#घोषणा IN_FROM_REG(val, ref)		(((val) * (ref) + 128) / 256)
#घोषणा IN_TO_REG(val, ref)		((val) < 0 ? 0 : \
					 (val) * 256 >= (ref) * 255 ? 255 : \
					 ((val) * 256 + (ref) / 2) / (ref))

/*
 * Temperature रेजिस्टरs and conversions
 */

#घोषणा PC87365_REG_TEMP_CONFIG		0x08
#घोषणा PC87365_REG_TEMP		0x0B
#घोषणा PC87365_REG_TEMP_MIN		0x0D
#घोषणा PC87365_REG_TEMP_MAX		0x0C
#घोषणा PC87365_REG_TEMP_CRIT		0x0E
#घोषणा PC87365_REG_TEMP_STATUS		0x0A
#घोषणा PC87365_REG_TEMP_ALARMS		0x00

#घोषणा TEMP_FROM_REG(val)		((val) * 1000)
#घोषणा TEMP_TO_REG(val)		((val) < -55000 ? -55 : \
					 (val) > 127000 ? 127 : \
					 (val) < 0 ? ((val) - 500) / 1000 : \
					 ((val) + 500) / 1000)

/*
 * Device data
 */

काष्ठा pc87360_data अणु
	स्थिर अक्षर *name;
	काष्ठा device *hwmon_dev;
	काष्ठा mutex lock;
	काष्ठा mutex update_lock;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	पूर्णांक address[3];

	u8 fannr, innr, tempnr;

	u8 fan[3];		/* Register value */
	u8 fan_min[3];		/* Register value */
	u8 fan_status[3];	/* Register value */
	u8 pwm[3];		/* Register value */
	u16 fan_conf;		/* Configuration रेजिस्टर values, combined */

	u16 in_vref;		/* 1 mV/bit */
	u8 in[14];		/* Register value */
	u8 in_min[14];		/* Register value */
	u8 in_max[14];		/* Register value */
	u8 in_crit[3];		/* Register value */
	u8 in_status[14];	/* Register value */
	u16 in_alarms;		/* Register values, combined, masked */
	u8 vid_conf;		/* Configuration रेजिस्टर value */
	u8 vrm;
	u8 vid;			/* Register value */

	s8 temp[3];		/* Register value */
	s8 temp_min[3];		/* Register value */
	s8 temp_max[3];		/* Register value */
	s8 temp_crit[3];	/* Register value */
	u8 temp_status[3];	/* Register value */
	u8 temp_alarms;		/* Register value, masked */
पूर्ण;

/*
 * Functions declaration
 */

अटल पूर्णांक pc87360_probe(काष्ठा platक्रमm_device *pdev);
अटल पूर्णांक pc87360_हटाओ(काष्ठा platक्रमm_device *pdev);

अटल पूर्णांक pc87360_पढ़ो_value(काष्ठा pc87360_data *data, u8 ldi, u8 bank,
			      u8 reg);
अटल व्योम pc87360_ग_लिखो_value(काष्ठा pc87360_data *data, u8 ldi, u8 bank,
				u8 reg, u8 value);
अटल व्योम pc87360_init_device(काष्ठा platक्रमm_device *pdev,
				पूर्णांक use_thermistors);
अटल काष्ठा pc87360_data *pc87360_update_device(काष्ठा device *dev);

/*
 * Driver data
 */

अटल काष्ठा platक्रमm_driver pc87360_driver = अणु
	.driver = अणु
		.name	= "pc87360",
	पूर्ण,
	.probe		= pc87360_probe,
	.हटाओ		= pc87360_हटाओ,
पूर्ण;

/*
 * Sysfs stuff
 */

अटल sमाप_प्रकार fan_input_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", FAN_FROM_REG(data->fan[attr->index],
		       FAN_DIV_FROM_REG(data->fan_status[attr->index])));
पूर्ण
अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", FAN_FROM_REG(data->fan_min[attr->index],
		       FAN_DIV_FROM_REG(data->fan_status[attr->index])));
पूर्ण
अटल sमाप_प्रकार fan_भाग_show(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n",
		       FAN_DIV_FROM_REG(data->fan_status[attr->index]));
पूर्ण
अटल sमाप_प्रकार fan_status_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n",
		       FAN_STATUS_FROM_REG(data->fan_status[attr->index]));
पूर्ण
अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = dev_get_drvdata(dev);
	दीर्घ fan_min;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &fan_min);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	fan_min = FAN_TO_REG(fan_min,
			     FAN_DIV_FROM_REG(data->fan_status[attr->index]));

	/* If it wouldn't fit, change घड़ी भागisor */
	जबतक (fan_min > 255
	    && (data->fan_status[attr->index] & 0x60) != 0x60) अणु
		fan_min >>= 1;
		data->fan[attr->index] >>= 1;
		data->fan_status[attr->index] += 0x20;
	पूर्ण
	data->fan_min[attr->index] = fan_min > 255 ? 255 : fan_min;
	pc87360_ग_लिखो_value(data, LD_FAN, NO_BANK,
			    PC87360_REG_FAN_MIN(attr->index),
			    data->fan_min[attr->index]);

	/* Write new भागider, preserve alarm bits */
	pc87360_ग_लिखो_value(data, LD_FAN, NO_BANK,
			    PC87360_REG_FAN_STATUS(attr->index),
			    data->fan_status[attr->index] & 0xF9);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल काष्ठा sensor_device_attribute fan_input[] = अणु
	SENSOR_ATTR_RO(fan1_input, fan_input, 0),
	SENSOR_ATTR_RO(fan2_input, fan_input, 1),
	SENSOR_ATTR_RO(fan3_input, fan_input, 2),
पूर्ण;
अटल काष्ठा sensor_device_attribute fan_status[] = अणु
	SENSOR_ATTR_RO(fan1_status, fan_status, 0),
	SENSOR_ATTR_RO(fan2_status, fan_status, 1),
	SENSOR_ATTR_RO(fan3_status, fan_status, 2),
पूर्ण;
अटल काष्ठा sensor_device_attribute fan_भाग[] = अणु
	SENSOR_ATTR_RO(fan1_भाग, fan_भाग, 0),
	SENSOR_ATTR_RO(fan2_भाग, fan_भाग, 1),
	SENSOR_ATTR_RO(fan3_भाग, fan_भाग, 2),
पूर्ण;
अटल काष्ठा sensor_device_attribute fan_min[] = अणु
	SENSOR_ATTR_RW(fan1_min, fan_min, 0),
	SENSOR_ATTR_RW(fan2_min, fan_min, 1),
	SENSOR_ATTR_RW(fan3_min, fan_min, 2),
पूर्ण;

#घोषणा FAN_UNIT_ATTRS(X)		\
अणु	&fan_input[X].dev_attr.attr,	\
	&fan_status[X].dev_attr.attr,	\
	&fan_भाग[X].dev_attr.attr,	\
	&fan_min[X].dev_attr.attr,	\
	शून्य				\
पूर्ण

अटल sमाप_प्रकार pwm_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n",
		       PWM_FROM_REG(data->pwm[attr->index],
				    FAN_CONFIG_INVERT(data->fan_conf,
						      attr->index)));
पूर्ण
अटल sमाप_प्रकार pwm_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->pwm[attr->index] = PWM_TO_REG(val,
			      FAN_CONFIG_INVERT(data->fan_conf, attr->index));
	pc87360_ग_लिखो_value(data, LD_FAN, NO_BANK, PC87360_REG_PWM(attr->index),
			    data->pwm[attr->index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल काष्ठा sensor_device_attribute pwm[] = अणु
	SENSOR_ATTR_RW(pwm1, pwm, 0),
	SENSOR_ATTR_RW(pwm2, pwm, 1),
	SENSOR_ATTR_RW(pwm3, pwm, 2),
पूर्ण;

अटल काष्ठा attribute *pc8736x_fan_attr[][5] = अणु
	FAN_UNIT_ATTRS(0),
	FAN_UNIT_ATTRS(1),
	FAN_UNIT_ATTRS(2)
पूर्ण;

अटल स्थिर काष्ठा attribute_group pc8736x_fan_attr_group[] = अणु
	अणु .attrs = pc8736x_fan_attr[0], पूर्ण,
	अणु .attrs = pc8736x_fan_attr[1], पूर्ण,
	अणु .attrs = pc8736x_fan_attr[2], पूर्ण,
पूर्ण;

अटल sमाप_प्रकार in_input_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", IN_FROM_REG(data->in[attr->index],
		       data->in_vref));
पूर्ण
अटल sमाप_प्रकार in_min_show(काष्ठा device *dev,
			   काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", IN_FROM_REG(data->in_min[attr->index],
		       data->in_vref));
पूर्ण
अटल sमाप_प्रकार in_max_show(काष्ठा device *dev,
			   काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", IN_FROM_REG(data->in_max[attr->index],
		       data->in_vref));
पूर्ण
अटल sमाप_प्रकार in_status_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", data->in_status[attr->index]);
पूर्ण
अटल sमाप_प्रकार in_min_store(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_min[attr->index] = IN_TO_REG(val, data->in_vref);
	pc87360_ग_लिखो_value(data, LD_IN, attr->index, PC87365_REG_IN_MIN,
			    data->in_min[attr->index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
अटल sमाप_प्रकार in_max_store(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_max[attr->index] = IN_TO_REG(val,
			       data->in_vref);
	pc87360_ग_लिखो_value(data, LD_IN, attr->index, PC87365_REG_IN_MAX,
			    data->in_max[attr->index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल काष्ठा sensor_device_attribute in_input[] = अणु
	SENSOR_ATTR_RO(in0_input, in_input, 0),
	SENSOR_ATTR_RO(in1_input, in_input, 1),
	SENSOR_ATTR_RO(in2_input, in_input, 2),
	SENSOR_ATTR_RO(in3_input, in_input, 3),
	SENSOR_ATTR_RO(in4_input, in_input, 4),
	SENSOR_ATTR_RO(in5_input, in_input, 5),
	SENSOR_ATTR_RO(in6_input, in_input, 6),
	SENSOR_ATTR_RO(in7_input, in_input, 7),
	SENSOR_ATTR_RO(in8_input, in_input, 8),
	SENSOR_ATTR_RO(in9_input, in_input, 9),
	SENSOR_ATTR_RO(in10_input, in_input, 10),
पूर्ण;
अटल काष्ठा sensor_device_attribute in_status[] = अणु
	SENSOR_ATTR_RO(in0_status, in_status, 0),
	SENSOR_ATTR_RO(in1_status, in_status, 1),
	SENSOR_ATTR_RO(in2_status, in_status, 2),
	SENSOR_ATTR_RO(in3_status, in_status, 3),
	SENSOR_ATTR_RO(in4_status, in_status, 4),
	SENSOR_ATTR_RO(in5_status, in_status, 5),
	SENSOR_ATTR_RO(in6_status, in_status, 6),
	SENSOR_ATTR_RO(in7_status, in_status, 7),
	SENSOR_ATTR_RO(in8_status, in_status, 8),
	SENSOR_ATTR_RO(in9_status, in_status, 9),
	SENSOR_ATTR_RO(in10_status, in_status, 10),
पूर्ण;
अटल काष्ठा sensor_device_attribute in_min[] = अणु
	SENSOR_ATTR_RW(in0_min, in_min, 0),
	SENSOR_ATTR_RW(in1_min, in_min, 1),
	SENSOR_ATTR_RW(in2_min, in_min, 2),
	SENSOR_ATTR_RW(in3_min, in_min, 3),
	SENSOR_ATTR_RW(in4_min, in_min, 4),
	SENSOR_ATTR_RW(in5_min, in_min, 5),
	SENSOR_ATTR_RW(in6_min, in_min, 6),
	SENSOR_ATTR_RW(in7_min, in_min, 7),
	SENSOR_ATTR_RW(in8_min, in_min, 8),
	SENSOR_ATTR_RW(in9_min, in_min, 9),
	SENSOR_ATTR_RW(in10_min, in_min, 10),
पूर्ण;
अटल काष्ठा sensor_device_attribute in_max[] = अणु
	SENSOR_ATTR_RW(in0_max, in_max, 0),
	SENSOR_ATTR_RW(in1_max, in_max, 1),
	SENSOR_ATTR_RW(in2_max, in_max, 2),
	SENSOR_ATTR_RW(in3_max, in_max, 3),
	SENSOR_ATTR_RW(in4_max, in_max, 4),
	SENSOR_ATTR_RW(in5_max, in_max, 5),
	SENSOR_ATTR_RW(in6_max, in_max, 6),
	SENSOR_ATTR_RW(in7_max, in_max, 7),
	SENSOR_ATTR_RW(in8_max, in_max, 8),
	SENSOR_ATTR_RW(in9_max, in_max, 9),
	SENSOR_ATTR_RW(in10_max, in_max, 10),
पूर्ण;

/* (temp & vin) channel status रेजिस्टर alarm bits (pdf sec.11.5.12) */
#घोषणा CHAN_ALM_MIN	0x02	/* min limit crossed */
#घोषणा CHAN_ALM_MAX	0x04	/* max limit exceeded */
#घोषणा TEMP_ALM_CRIT	0x08	/* temp crit exceeded (temp only) */

/*
 * show_in_min/max_alarm() पढ़ोs data from the per-channel status
 * रेजिस्टर (sec 11.5.12), not the vin event status रेजिस्टरs (sec
 * 11.5.2) that (legacy) show_in_alarm() resds (via data->in_alarms)
 */

अटल sमाप_प्रकार in_min_alarm_show(काष्ठा device *dev,
				 काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	अचिन्हित nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%u\n", !!(data->in_status[nr] & CHAN_ALM_MIN));
पूर्ण
अटल sमाप_प्रकार in_max_alarm_show(काष्ठा device *dev,
				 काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	अचिन्हित nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%u\n", !!(data->in_status[nr] & CHAN_ALM_MAX));
पूर्ण

अटल काष्ठा sensor_device_attribute in_min_alarm[] = अणु
	SENSOR_ATTR_RO(in0_min_alarm, in_min_alarm, 0),
	SENSOR_ATTR_RO(in1_min_alarm, in_min_alarm, 1),
	SENSOR_ATTR_RO(in2_min_alarm, in_min_alarm, 2),
	SENSOR_ATTR_RO(in3_min_alarm, in_min_alarm, 3),
	SENSOR_ATTR_RO(in4_min_alarm, in_min_alarm, 4),
	SENSOR_ATTR_RO(in5_min_alarm, in_min_alarm, 5),
	SENSOR_ATTR_RO(in6_min_alarm, in_min_alarm, 6),
	SENSOR_ATTR_RO(in7_min_alarm, in_min_alarm, 7),
	SENSOR_ATTR_RO(in8_min_alarm, in_min_alarm, 8),
	SENSOR_ATTR_RO(in9_min_alarm, in_min_alarm, 9),
	SENSOR_ATTR_RO(in10_min_alarm, in_min_alarm, 10),
पूर्ण;
अटल काष्ठा sensor_device_attribute in_max_alarm[] = अणु
	SENSOR_ATTR_RO(in0_max_alarm, in_max_alarm, 0),
	SENSOR_ATTR_RO(in1_max_alarm, in_max_alarm, 1),
	SENSOR_ATTR_RO(in2_max_alarm, in_max_alarm, 2),
	SENSOR_ATTR_RO(in3_max_alarm, in_max_alarm, 3),
	SENSOR_ATTR_RO(in4_max_alarm, in_max_alarm, 4),
	SENSOR_ATTR_RO(in5_max_alarm, in_max_alarm, 5),
	SENSOR_ATTR_RO(in6_max_alarm, in_max_alarm, 6),
	SENSOR_ATTR_RO(in7_max_alarm, in_max_alarm, 7),
	SENSOR_ATTR_RO(in8_max_alarm, in_max_alarm, 8),
	SENSOR_ATTR_RO(in9_max_alarm, in_max_alarm, 9),
	SENSOR_ATTR_RO(in10_max_alarm, in_max_alarm, 10),
पूर्ण;

#घोषणा VIN_UNIT_ATTRS(X) \
	&in_input[X].dev_attr.attr,	\
	&in_status[X].dev_attr.attr,	\
	&in_min[X].dev_attr.attr,	\
	&in_max[X].dev_attr.attr,	\
	&in_min_alarm[X].dev_attr.attr,	\
	&in_max_alarm[X].dev_attr.attr

अटल sमाप_प्रकार cpu0_vid_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", vid_from_reg(data->vid, data->vrm));
पूर्ण
अटल DEVICE_ATTR_RO(cpu0_vid);

अटल sमाप_प्रकार vrm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा pc87360_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%u\n", data->vrm);
पूर्ण
अटल sमाप_प्रकार vrm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pc87360_data *data = dev_get_drvdata(dev);
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

अटल sमाप_प्रकार alarms_in_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", data->in_alarms);
पूर्ण
अटल DEVICE_ATTR_RO(alarms_in);

अटल काष्ठा attribute *pc8736x_vin_attr_array[] = अणु
	VIN_UNIT_ATTRS(0),
	VIN_UNIT_ATTRS(1),
	VIN_UNIT_ATTRS(2),
	VIN_UNIT_ATTRS(3),
	VIN_UNIT_ATTRS(4),
	VIN_UNIT_ATTRS(5),
	VIN_UNIT_ATTRS(6),
	VIN_UNIT_ATTRS(7),
	VIN_UNIT_ATTRS(8),
	VIN_UNIT_ATTRS(9),
	VIN_UNIT_ATTRS(10),
	&dev_attr_cpu0_vid.attr,
	&dev_attr_vrm.attr,
	&dev_attr_alarms_in.attr,
	शून्य
पूर्ण;
अटल स्थिर काष्ठा attribute_group pc8736x_vin_group = अणु
	.attrs = pc8736x_vin_attr_array,
पूर्ण;

अटल sमाप_प्रकार therm_input_show(काष्ठा device *dev,
				काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", IN_FROM_REG(data->in[attr->index],
		       data->in_vref));
पूर्ण
अटल sमाप_प्रकार therm_min_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", IN_FROM_REG(data->in_min[attr->index],
		       data->in_vref));
पूर्ण
अटल sमाप_प्रकार therm_max_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", IN_FROM_REG(data->in_max[attr->index],
		       data->in_vref));
पूर्ण
अटल sमाप_प्रकार therm_crit_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", IN_FROM_REG(data->in_crit[attr->index-11],
		       data->in_vref));
पूर्ण
अटल sमाप_प्रकार therm_status_show(काष्ठा device *dev,
				 काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", data->in_status[attr->index]);
पूर्ण

अटल sमाप_प्रकार therm_min_store(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_min[attr->index] = IN_TO_REG(val, data->in_vref);
	pc87360_ग_लिखो_value(data, LD_IN, attr->index, PC87365_REG_TEMP_MIN,
			    data->in_min[attr->index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार therm_max_store(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_max[attr->index] = IN_TO_REG(val, data->in_vref);
	pc87360_ग_लिखो_value(data, LD_IN, attr->index, PC87365_REG_TEMP_MAX,
			    data->in_max[attr->index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
अटल sमाप_प्रकार therm_crit_store(काष्ठा device *dev,
				काष्ठा device_attribute *devattr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_crit[attr->index-11] = IN_TO_REG(val, data->in_vref);
	pc87360_ग_लिखो_value(data, LD_IN, attr->index, PC87365_REG_TEMP_CRIT,
			    data->in_crit[attr->index-11]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/*
 * the +11 term below reflects the fact that VLM units 11,12,13 are
 * used in the chip to measure voltage across the thermistors
 */
अटल काष्ठा sensor_device_attribute therm_input[] = अणु
	SENSOR_ATTR_RO(temp4_input, therm_input, 0 + 11),
	SENSOR_ATTR_RO(temp5_input, therm_input, 1 + 11),
	SENSOR_ATTR_RO(temp6_input, therm_input, 2 + 11),
पूर्ण;
अटल काष्ठा sensor_device_attribute therm_status[] = अणु
	SENSOR_ATTR_RO(temp4_status, therm_status, 0 + 11),
	SENSOR_ATTR_RO(temp5_status, therm_status, 1 + 11),
	SENSOR_ATTR_RO(temp6_status, therm_status, 2 + 11),
पूर्ण;
अटल काष्ठा sensor_device_attribute therm_min[] = अणु
	SENSOR_ATTR_RW(temp4_min, therm_min, 0 + 11),
	SENSOR_ATTR_RW(temp5_min, therm_min, 1 + 11),
	SENSOR_ATTR_RW(temp6_min, therm_min, 2 + 11),
पूर्ण;
अटल काष्ठा sensor_device_attribute therm_max[] = अणु
	SENSOR_ATTR_RW(temp4_max, therm_max, 0 + 11),
	SENSOR_ATTR_RW(temp5_max, therm_max, 1 + 11),
	SENSOR_ATTR_RW(temp6_max, therm_max, 2 + 11),
पूर्ण;
अटल काष्ठा sensor_device_attribute therm_crit[] = अणु
	SENSOR_ATTR_RW(temp4_crit, therm_crit, 0 + 11),
	SENSOR_ATTR_RW(temp5_crit, therm_crit, 1 + 11),
	SENSOR_ATTR_RW(temp6_crit, therm_crit, 2 + 11),
पूर्ण;

/*
 * show_therm_min/max_alarm() पढ़ोs data from the per-channel voltage
 * status रेजिस्टर (sec 11.5.12)
 */

अटल sमाप_प्रकार therm_min_alarm_show(काष्ठा device *dev,
				    काष्ठा device_attribute *devattr,
				    अक्षर *buf)
अणु
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	अचिन्हित nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%u\n", !!(data->in_status[nr] & CHAN_ALM_MIN));
पूर्ण
अटल sमाप_प्रकार therm_max_alarm_show(काष्ठा device *dev,
				    काष्ठा device_attribute *devattr,
				    अक्षर *buf)
अणु
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	अचिन्हित nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%u\n", !!(data->in_status[nr] & CHAN_ALM_MAX));
पूर्ण
अटल sमाप_प्रकार therm_crit_alarm_show(काष्ठा device *dev,
				     काष्ठा device_attribute *devattr,
				     अक्षर *buf)
अणु
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	अचिन्हित nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%u\n", !!(data->in_status[nr] & TEMP_ALM_CRIT));
पूर्ण

अटल काष्ठा sensor_device_attribute therm_min_alarm[] = अणु
	SENSOR_ATTR_RO(temp4_min_alarm, therm_min_alarm, 0 + 11),
	SENSOR_ATTR_RO(temp5_min_alarm, therm_min_alarm, 1 + 11),
	SENSOR_ATTR_RO(temp6_min_alarm, therm_min_alarm, 2 + 11),
पूर्ण;
अटल काष्ठा sensor_device_attribute therm_max_alarm[] = अणु
	SENSOR_ATTR_RO(temp4_max_alarm, therm_max_alarm, 0 + 11),
	SENSOR_ATTR_RO(temp5_max_alarm, therm_max_alarm, 1 + 11),
	SENSOR_ATTR_RO(temp6_max_alarm, therm_max_alarm, 2 + 11),
पूर्ण;
अटल काष्ठा sensor_device_attribute therm_crit_alarm[] = अणु
	SENSOR_ATTR_RO(temp4_crit_alarm, therm_crit_alarm, 0 + 11),
	SENSOR_ATTR_RO(temp5_crit_alarm, therm_crit_alarm, 1 + 11),
	SENSOR_ATTR_RO(temp6_crit_alarm, therm_crit_alarm, 2 + 11),
पूर्ण;

#घोषणा THERM_UNIT_ATTRS(X) \
	&therm_input[X].dev_attr.attr,	\
	&therm_status[X].dev_attr.attr,	\
	&therm_min[X].dev_attr.attr,	\
	&therm_max[X].dev_attr.attr,	\
	&therm_crit[X].dev_attr.attr,	\
	&therm_min_alarm[X].dev_attr.attr, \
	&therm_max_alarm[X].dev_attr.attr, \
	&therm_crit_alarm[X].dev_attr.attr

अटल काष्ठा attribute *pc8736x_therm_attr_array[] = अणु
	THERM_UNIT_ATTRS(0),
	THERM_UNIT_ATTRS(1),
	THERM_UNIT_ATTRS(2),
	शून्य
पूर्ण;
अटल स्थिर काष्ठा attribute_group pc8736x_therm_group = अणु
	.attrs = pc8736x_therm_attr_array,
पूर्ण;

अटल sमाप_प्रकार temp_input_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp[attr->index]));
पूर्ण

अटल sमाप_प्रकार temp_min_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_min[attr->index]));
पूर्ण

अटल sमाप_प्रकार temp_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_max[attr->index]));
पूर्ण

अटल sमाप_प्रकार temp_crit_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n",
		       TEMP_FROM_REG(data->temp_crit[attr->index]));
पूर्ण

अटल sमाप_प्रकार temp_status_show(काष्ठा device *dev,
				काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->temp_status[attr->index]);
पूर्ण

अटल sमाप_प्रकार temp_min_store(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_min[attr->index] = TEMP_TO_REG(val);
	pc87360_ग_लिखो_value(data, LD_TEMP, attr->index, PC87365_REG_TEMP_MIN,
			    data->temp_min[attr->index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_max[attr->index] = TEMP_TO_REG(val);
	pc87360_ग_लिखो_value(data, LD_TEMP, attr->index, PC87365_REG_TEMP_MAX,
			    data->temp_max[attr->index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_crit_store(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा pc87360_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_crit[attr->index] = TEMP_TO_REG(val);
	pc87360_ग_लिखो_value(data, LD_TEMP, attr->index, PC87365_REG_TEMP_CRIT,
			    data->temp_crit[attr->index]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल काष्ठा sensor_device_attribute temp_input[] = अणु
	SENSOR_ATTR_RO(temp1_input, temp_input, 0),
	SENSOR_ATTR_RO(temp2_input, temp_input, 1),
	SENSOR_ATTR_RO(temp3_input, temp_input, 2),
पूर्ण;
अटल काष्ठा sensor_device_attribute temp_status[] = अणु
	SENSOR_ATTR_RO(temp1_status, temp_status, 0),
	SENSOR_ATTR_RO(temp2_status, temp_status, 1),
	SENSOR_ATTR_RO(temp3_status, temp_status, 2),
पूर्ण;
अटल काष्ठा sensor_device_attribute temp_min[] = अणु
	SENSOR_ATTR_RW(temp1_min, temp_min, 0),
	SENSOR_ATTR_RW(temp2_min, temp_min, 1),
	SENSOR_ATTR_RW(temp3_min, temp_min, 2),
पूर्ण;
अटल काष्ठा sensor_device_attribute temp_max[] = अणु
	SENSOR_ATTR_RW(temp1_max, temp_max, 0),
	SENSOR_ATTR_RW(temp2_max, temp_max, 1),
	SENSOR_ATTR_RW(temp3_max, temp_max, 2),
पूर्ण;
अटल काष्ठा sensor_device_attribute temp_crit[] = अणु
	SENSOR_ATTR_RW(temp1_crit, temp_crit, 0),
	SENSOR_ATTR_RW(temp2_crit, temp_crit, 1),
	SENSOR_ATTR_RW(temp3_crit, temp_crit, 2),
पूर्ण;

अटल sमाप_प्रकार alarms_temp_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", data->temp_alarms);
पूर्ण

अटल DEVICE_ATTR_RO(alarms_temp);

/*
 * show_temp_min/max_alarm() पढ़ोs data from the per-channel status
 * रेजिस्टर (sec 12.3.7), not the temp event status रेजिस्टरs (sec
 * 12.3.2) that show_temp_alarm() पढ़ोs (via data->temp_alarms)
 */

अटल sमाप_प्रकार temp_min_alarm_show(काष्ठा device *dev,
				   काष्ठा device_attribute *devattr,
				   अक्षर *buf)
अणु
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	अचिन्हित nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%u\n", !!(data->temp_status[nr] & CHAN_ALM_MIN));
पूर्ण

अटल sमाप_प्रकार temp_max_alarm_show(काष्ठा device *dev,
				   काष्ठा device_attribute *devattr,
				   अक्षर *buf)
अणु
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	अचिन्हित nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%u\n", !!(data->temp_status[nr] & CHAN_ALM_MAX));
पूर्ण

अटल sमाप_प्रकार temp_crit_alarm_show(काष्ठा device *dev,
				    काष्ठा device_attribute *devattr,
				    अक्षर *buf)
अणु
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	अचिन्हित nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%u\n", !!(data->temp_status[nr] & TEMP_ALM_CRIT));
पूर्ण

अटल काष्ठा sensor_device_attribute temp_min_alarm[] = अणु
	SENSOR_ATTR_RO(temp1_min_alarm, temp_min_alarm, 0),
	SENSOR_ATTR_RO(temp2_min_alarm, temp_min_alarm, 1),
	SENSOR_ATTR_RO(temp3_min_alarm, temp_min_alarm, 2),
पूर्ण;

अटल काष्ठा sensor_device_attribute temp_max_alarm[] = अणु
	SENSOR_ATTR_RO(temp1_max_alarm, temp_max_alarm, 0),
	SENSOR_ATTR_RO(temp2_max_alarm, temp_max_alarm, 1),
	SENSOR_ATTR_RO(temp3_max_alarm, temp_max_alarm, 2),
पूर्ण;

अटल काष्ठा sensor_device_attribute temp_crit_alarm[] = अणु
	SENSOR_ATTR_RO(temp1_crit_alarm, temp_crit_alarm, 0),
	SENSOR_ATTR_RO(temp2_crit_alarm, temp_crit_alarm, 1),
	SENSOR_ATTR_RO(temp3_crit_alarm, temp_crit_alarm, 2),
पूर्ण;

#घोषणा TEMP_FAULT	0x40	/* खोलो diode */
अटल sमाप_प्रकार temp_fault_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pc87360_data *data = pc87360_update_device(dev);
	अचिन्हित nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%u\n", !!(data->temp_status[nr] & TEMP_FAULT));
पूर्ण
अटल काष्ठा sensor_device_attribute temp_fault[] = अणु
	SENSOR_ATTR_RO(temp1_fault, temp_fault, 0),
	SENSOR_ATTR_RO(temp2_fault, temp_fault, 1),
	SENSOR_ATTR_RO(temp3_fault, temp_fault, 2),
पूर्ण;

#घोषणा TEMP_UNIT_ATTRS(X)			\
अणु	&temp_input[X].dev_attr.attr,		\
	&temp_status[X].dev_attr.attr,		\
	&temp_min[X].dev_attr.attr,		\
	&temp_max[X].dev_attr.attr,		\
	&temp_crit[X].dev_attr.attr,		\
	&temp_min_alarm[X].dev_attr.attr,	\
	&temp_max_alarm[X].dev_attr.attr,	\
	&temp_crit_alarm[X].dev_attr.attr,	\
	&temp_fault[X].dev_attr.attr,		\
	शून्य					\
पूर्ण

अटल काष्ठा attribute *pc8736x_temp_attr[][10] = अणु
	TEMP_UNIT_ATTRS(0),
	TEMP_UNIT_ATTRS(1),
	TEMP_UNIT_ATTRS(2)
पूर्ण;

अटल स्थिर काष्ठा attribute_group pc8736x_temp_attr_group[] = अणु
	अणु .attrs = pc8736x_temp_attr[0] पूर्ण,
	अणु .attrs = pc8736x_temp_attr[1] पूर्ण,
	अणु .attrs = pc8736x_temp_attr[2] पूर्ण
पूर्ण;

अटल sमाप_प्रकार name_show(काष्ठा device *dev,
			काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pc87360_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%s\n", data->name);
पूर्ण

अटल DEVICE_ATTR_RO(name);

/*
 * Device detection, registration and update
 */

अटल पूर्णांक __init pc87360_find(पूर्णांक sioaddr, u8 *devid,
			       अचिन्हित लघु *addresses)
अणु
	u16 val;
	पूर्णांक i;
	पूर्णांक nrdev; /* logical device count */

	/* No superio_enter */

	/* Identअगरy device */
	val = क्रमce_id ? क्रमce_id : superio_inb(sioaddr, DEVID);
	चयन (val) अणु
	हाल 0xE1: /* PC87360 */
	हाल 0xE8: /* PC87363 */
	हाल 0xE4: /* PC87364 */
		nrdev = 1;
		अवरोध;
	हाल 0xE5: /* PC87365 */
	हाल 0xE9: /* PC87366 */
		nrdev = 3;
		अवरोध;
	शेष:
		superio_निकास(sioaddr);
		वापस -ENODEV;
	पूर्ण
	/* Remember the device id */
	*devid = val;

	क्रम (i = 0; i < nrdev; i++) अणु
		/* select logical device */
		superio_outb(sioaddr, DEV, logdev[i]);

		val = superio_inb(sioaddr, ACT);
		अगर (!(val & 0x01)) अणु
			pr_info("Device 0x%02x not activated\n", logdev[i]);
			जारी;
		पूर्ण

		val = (superio_inb(sioaddr, BASE) << 8)
		    | superio_inb(sioaddr, BASE + 1);
		अगर (!val) अणु
			pr_info("Base address not set for device 0x%02x\n",
				logdev[i]);
			जारी;
		पूर्ण

		addresses[i] = val;

		अगर (i == 0) अणु /* Fans */
			confreg[0] = superio_inb(sioaddr, 0xF0);
			confreg[1] = superio_inb(sioaddr, 0xF1);

			pr_debug("Fan %d: mon=%d ctrl=%d inv=%d\n", 1,
				 (confreg[0] >> 2) & 1, (confreg[0] >> 3) & 1,
				 (confreg[0] >> 4) & 1);
			pr_debug("Fan %d: mon=%d ctrl=%d inv=%d\n", 2,
				 (confreg[0] >> 5) & 1, (confreg[0] >> 6) & 1,
				 (confreg[0] >> 7) & 1);
			pr_debug("Fan %d: mon=%d ctrl=%d inv=%d\n", 3,
				 confreg[1] & 1, (confreg[1] >> 1) & 1,
				 (confreg[1] >> 2) & 1);
		पूर्ण अन्यथा अगर (i == 1) अणु /* Voltages */
			/* Are we using thermistors? */
			अगर (*devid == 0xE9) अणु /* PC87366 */
				/*
				 * These रेजिस्टरs are not logical-device
				 * specअगरic, just that we won't need them अगर
				 * we करोn't use the VLM device
				 */
				confreg[2] = superio_inb(sioaddr, 0x2B);
				confreg[3] = superio_inb(sioaddr, 0x25);

				अगर (confreg[2] & 0x40) अणु
					pr_info("Using thermistors for temperature monitoring\n");
				पूर्ण
				अगर (confreg[3] & 0xE0) अणु
					pr_info("VID inputs routed (mode %u)\n",
						confreg[3] >> 5);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	superio_निकास(sioaddr);
	वापस 0;
पूर्ण

अटल व्योम pc87360_हटाओ_files(काष्ठा device *dev)
अणु
	पूर्णांक i;

	device_हटाओ_file(dev, &dev_attr_name);
	device_हटाओ_file(dev, &dev_attr_alarms_temp);
	क्रम (i = 0; i < ARRAY_SIZE(pc8736x_temp_attr_group); i++)
		sysfs_हटाओ_group(&dev->kobj, &pc8736x_temp_attr_group[i]);
	क्रम (i = 0; i < ARRAY_SIZE(pc8736x_fan_attr_group); i++) अणु
		sysfs_हटाओ_group(&pdev->dev.kobj, &pc8736x_fan_attr_group[i]);
		device_हटाओ_file(dev, &pwm[i].dev_attr);
	पूर्ण
	sysfs_हटाओ_group(&dev->kobj, &pc8736x_therm_group);
	sysfs_हटाओ_group(&dev->kobj, &pc8736x_vin_group);
पूर्ण

अटल पूर्णांक pc87360_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	काष्ठा pc87360_data *data;
	पूर्णांक err = 0;
	स्थिर अक्षर *name;
	पूर्णांक use_thermistors = 0;
	काष्ठा device *dev = &pdev->dev;

	data = devm_kzalloc(dev, माप(काष्ठा pc87360_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	चयन (devid) अणु
	शेष:
		name = "pc87360";
		data->fannr = 2;
		अवरोध;
	हाल 0xe8:
		name = "pc87363";
		data->fannr = 2;
		अवरोध;
	हाल 0xe4:
		name = "pc87364";
		data->fannr = 3;
		अवरोध;
	हाल 0xe5:
		name = "pc87365";
		data->fannr = extra_isa[0] ? 3 : 0;
		data->innr = extra_isa[1] ? 11 : 0;
		data->tempnr = extra_isa[2] ? 2 : 0;
		अवरोध;
	हाल 0xe9:
		name = "pc87366";
		data->fannr = extra_isa[0] ? 3 : 0;
		data->innr = extra_isa[1] ? 14 : 0;
		data->tempnr = extra_isa[2] ? 3 : 0;
		अवरोध;
	पूर्ण

	data->name = name;
	mutex_init(&data->lock);
	mutex_init(&data->update_lock);
	platक्रमm_set_drvdata(pdev, data);

	क्रम (i = 0; i < LDNI_MAX; i++) अणु
		data->address[i] = extra_isa[i];
		अगर (data->address[i]
		 && !devm_request_region(dev, extra_isa[i], PC87360_EXTENT,
					 pc87360_driver.driver.name)) अणु
			dev_err(dev,
				"Region 0x%x-0x%x already in use!\n",
				extra_isa[i], extra_isa[i]+PC87360_EXTENT-1);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* Retrieve the fans configuration from Super-I/O space */
	अगर (data->fannr)
		data->fan_conf = confreg[0] | (confreg[1] << 8);

	/*
	 * Use the correct reference voltage
	 * Unless both the VLM and the TMS logical devices agree to
	 * use an बाह्यal Vref, the पूर्णांकernal one is used.
	 */
	अगर (data->innr) अणु
		i = pc87360_पढ़ो_value(data, LD_IN, NO_BANK,
				       PC87365_REG_IN_CONFIG);
		अगर (data->tempnr) अणु
			i &= pc87360_पढ़ो_value(data, LD_TEMP, NO_BANK,
						PC87365_REG_TEMP_CONFIG);
		पूर्ण
		data->in_vref = (i&0x02) ? 3025 : 2966;
		dev_dbg(dev, "Using %s reference voltage\n",
			(i&0x02) ? "external" : "internal");

		data->vid_conf = confreg[3];
		data->vrm = vid_which_vrm();
	पूर्ण

	/* Fan घड़ी भागiders may be needed beक्रमe any data is पढ़ो */
	क्रम (i = 0; i < data->fannr; i++) अणु
		अगर (FAN_CONFIG_MONITOR(data->fan_conf, i))
			data->fan_status[i] = pc87360_पढ़ो_value(data,
					      LD_FAN, NO_BANK,
					      PC87360_REG_FAN_STATUS(i));
	पूर्ण

	अगर (init > 0) अणु
		अगर (devid == 0xe9 && data->address[1]) /* PC87366 */
			use_thermistors = confreg[2] & 0x40;

		pc87360_init_device(pdev, use_thermistors);
	पूर्ण

	/* Register all-or-nothing sysfs groups */

	अगर (data->innr) अणु
		err = sysfs_create_group(&dev->kobj, &pc8736x_vin_group);
		अगर (err)
			जाओ error;
	पूर्ण

	अगर (data->innr == 14) अणु
		err = sysfs_create_group(&dev->kobj, &pc8736x_therm_group);
		अगर (err)
			जाओ error;
	पूर्ण

	/* create device attr-files क्रम varying sysfs groups */

	अगर (data->tempnr) अणु
		क्रम (i = 0; i < data->tempnr; i++) अणु
			err = sysfs_create_group(&dev->kobj,
						 &pc8736x_temp_attr_group[i]);
			अगर (err)
				जाओ error;
		पूर्ण
		err = device_create_file(dev, &dev_attr_alarms_temp);
		अगर (err)
			जाओ error;
	पूर्ण

	क्रम (i = 0; i < data->fannr; i++) अणु
		अगर (FAN_CONFIG_MONITOR(data->fan_conf, i)) अणु
			err = sysfs_create_group(&dev->kobj,
						 &pc8736x_fan_attr_group[i]);
			अगर (err)
				जाओ error;
		पूर्ण
		अगर (FAN_CONFIG_CONTROL(data->fan_conf, i)) अणु
			err = device_create_file(dev, &pwm[i].dev_attr);
			अगर (err)
				जाओ error;
		पूर्ण
	पूर्ण

	err = device_create_file(dev, &dev_attr_name);
	अगर (err)
		जाओ error;

	data->hwmon_dev = hwmon_device_रेजिस्टर(dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		जाओ error;
	पूर्ण
	वापस 0;

error:
	pc87360_हटाओ_files(dev);
	वापस err;
पूर्ण

अटल पूर्णांक pc87360_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pc87360_data *data = platक्रमm_get_drvdata(pdev);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	pc87360_हटाओ_files(&pdev->dev);

	वापस 0;
पूर्ण

/*
 * ldi is the logical device index
 * bank is क्रम voltages and temperatures only
 */
अटल पूर्णांक pc87360_पढ़ो_value(काष्ठा pc87360_data *data, u8 ldi, u8 bank,
			      u8 reg)
अणु
	पूर्णांक res;

	mutex_lock(&(data->lock));
	अगर (bank != NO_BANK)
		outb_p(bank, data->address[ldi] + PC87365_REG_BANK);
	res = inb_p(data->address[ldi] + reg);
	mutex_unlock(&(data->lock));

	वापस res;
पूर्ण

अटल व्योम pc87360_ग_लिखो_value(काष्ठा pc87360_data *data, u8 ldi, u8 bank,
				u8 reg, u8 value)
अणु
	mutex_lock(&(data->lock));
	अगर (bank != NO_BANK)
		outb_p(bank, data->address[ldi] + PC87365_REG_BANK);
	outb_p(value, data->address[ldi] + reg);
	mutex_unlock(&(data->lock));
पूर्ण

/* (temp & vin) channel conversion status रेजिस्टर flags (pdf sec.11.5.12) */
#घोषणा CHAN_CNVRTD	0x80	/* new data पढ़ोy */
#घोषणा CHAN_ENA	0x01	/* enabled channel (temp or vin) */
#घोषणा CHAN_ALM_ENA	0x10	/* propagate to alarms-reg ?? (chk val!) */
#घोषणा CHAN_READY	(CHAN_ENA|CHAN_CNVRTD) /* sample पढ़ोy mask */

#घोषणा TEMP_OTS_OE	0x20	/* OTS Output Enable */
#घोषणा VIN_RW1C_MASK	(CHAN_READY|CHAN_ALM_MAX|CHAN_ALM_MIN)   /* 0x87 */
#घोषणा TEMP_RW1C_MASK	(VIN_RW1C_MASK|TEMP_ALM_CRIT|TEMP_FAULT) /* 0xCF */

अटल व्योम pc87360_init_device(काष्ठा platक्रमm_device *pdev,
				पूर्णांक use_thermistors)
अणु
	काष्ठा pc87360_data *data = platक्रमm_get_drvdata(pdev);
	पूर्णांक i, nr;
	स्थिर u8 init_in[14] = अणु 2, 2, 2, 2, 2, 2, 2, 1, 1, 3, 1, 2, 2, 2 पूर्ण;
	स्थिर u8 init_temp[3] = अणु 2, 2, 1 पूर्ण;
	u8 reg;

	अगर (init >= 2 && data->innr) अणु
		reg = pc87360_पढ़ो_value(data, LD_IN, NO_BANK,
					 PC87365_REG_IN_CONVRATE);
		dev_info(&pdev->dev,
			 "VLM conversion set to 1s period, 160us delay\n");
		pc87360_ग_लिखो_value(data, LD_IN, NO_BANK,
				    PC87365_REG_IN_CONVRATE,
				    (reg & 0xC0) | 0x11);
	पूर्ण

	nr = data->innr < 11 ? data->innr : 11;
	क्रम (i = 0; i < nr; i++) अणु
		reg = pc87360_पढ़ो_value(data, LD_IN, i,
					 PC87365_REG_IN_STATUS);
		dev_dbg(&pdev->dev, "bios in%d status:0x%02x\n", i, reg);
		अगर (init >= init_in[i]) अणु
			/* Forcibly enable voltage channel */
			अगर (!(reg & CHAN_ENA)) अणु
				dev_dbg(&pdev->dev, "Forcibly enabling in%d\n",
					i);
				pc87360_ग_लिखो_value(data, LD_IN, i,
						    PC87365_REG_IN_STATUS,
						    (reg & 0x68) | 0x87);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * We can't blindly trust the Super-I/O space configuration bit,
	 * most BIOS won't set it properly
	 */
	dev_dbg(&pdev->dev, "bios thermistors:%d\n", use_thermistors);
	क्रम (i = 11; i < data->innr; i++) अणु
		reg = pc87360_पढ़ो_value(data, LD_IN, i,
					 PC87365_REG_TEMP_STATUS);
		use_thermistors = use_thermistors || (reg & CHAN_ENA);
		/* thermistors are temp[4-6], measured on vin[11-14] */
		dev_dbg(&pdev->dev, "bios temp%d_status:0x%02x\n", i-7, reg);
	पूर्ण
	dev_dbg(&pdev->dev, "using thermistors:%d\n", use_thermistors);

	i = use_thermistors ? 2 : 0;
	क्रम (; i < data->tempnr; i++) अणु
		reg = pc87360_पढ़ो_value(data, LD_TEMP, i,
					 PC87365_REG_TEMP_STATUS);
		dev_dbg(&pdev->dev, "bios temp%d_status:0x%02x\n", i + 1, reg);
		अगर (init >= init_temp[i]) अणु
			/* Forcibly enable temperature channel */
			अगर (!(reg & CHAN_ENA)) अणु
				dev_dbg(&pdev->dev,
					"Forcibly enabling temp%d\n", i + 1);
				pc87360_ग_लिखो_value(data, LD_TEMP, i,
						    PC87365_REG_TEMP_STATUS,
						    0xCF);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (use_thermistors) अणु
		क्रम (i = 11; i < data->innr; i++) अणु
			अगर (init >= init_in[i]) अणु
				/*
				 * The pin may alपढ़ोy be used by thermal
				 * diodes
				 */
				reg = pc87360_पढ़ो_value(data, LD_TEMP,
				      (i - 11) / 2, PC87365_REG_TEMP_STATUS);
				अगर (reg & CHAN_ENA) अणु
					dev_dbg(&pdev->dev,
			"Skipping temp%d, pin already in use by temp%d\n",
						i - 7, (i - 11) / 2);
					जारी;
				पूर्ण

				/* Forcibly enable thermistor channel */
				reg = pc87360_पढ़ो_value(data, LD_IN, i,
							 PC87365_REG_IN_STATUS);
				अगर (!(reg & CHAN_ENA)) अणु
					dev_dbg(&pdev->dev,
						"Forcibly enabling temp%d\n",
						i - 7);
					pc87360_ग_लिखो_value(data, LD_IN, i,
						PC87365_REG_TEMP_STATUS,
						(reg & 0x60) | 0x8F);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (data->innr) अणु
		reg = pc87360_पढ़ो_value(data, LD_IN, NO_BANK,
					 PC87365_REG_IN_CONFIG);
		dev_dbg(&pdev->dev, "bios vin-cfg:0x%02x\n", reg);
		अगर (reg & CHAN_ENA) अणु
			dev_dbg(&pdev->dev,
				"Forcibly enabling monitoring (VLM)\n");
			pc87360_ग_लिखो_value(data, LD_IN, NO_BANK,
					    PC87365_REG_IN_CONFIG,
					    reg & 0xFE);
		पूर्ण
	पूर्ण

	अगर (data->tempnr) अणु
		reg = pc87360_पढ़ो_value(data, LD_TEMP, NO_BANK,
					 PC87365_REG_TEMP_CONFIG);
		dev_dbg(&pdev->dev, "bios temp-cfg:0x%02x\n", reg);
		अगर (reg & CHAN_ENA) अणु
			dev_dbg(&pdev->dev,
				"Forcibly enabling monitoring (TMS)\n");
			pc87360_ग_लिखो_value(data, LD_TEMP, NO_BANK,
					    PC87365_REG_TEMP_CONFIG,
					    reg & 0xFE);
		पूर्ण

		अगर (init >= 2) अणु
			/* Chip config as करोcumented by National Semi. */
			pc87360_ग_लिखो_value(data, LD_TEMP, 0xF, 0xA, 0x08);
			/*
			 * We voluntarily omit the bank here, in हाल the
			 * sequence itself matters. It shouldn't be a problem,
			 * since nobody अन्यथा is supposed to access the
			 * device at that poपूर्णांक.
			 */
			pc87360_ग_लिखो_value(data, LD_TEMP, NO_BANK, 0xB, 0x04);
			pc87360_ग_लिखो_value(data, LD_TEMP, NO_BANK, 0xC, 0x35);
			pc87360_ग_लिखो_value(data, LD_TEMP, NO_BANK, 0xD, 0x05);
			pc87360_ग_लिखो_value(data, LD_TEMP, NO_BANK, 0xE, 0x05);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pc87360_स्वतःभाग(काष्ठा device *dev, पूर्णांक nr)
अणु
	काष्ठा pc87360_data *data = dev_get_drvdata(dev);
	u8 old_min = data->fan_min[nr];

	/* Increase घड़ी भागider अगर needed and possible */
	अगर ((data->fan_status[nr] & 0x04) /* overflow flag */
	 || (data->fan[nr] >= 224)) अणु /* next to overflow */
		अगर ((data->fan_status[nr] & 0x60) != 0x60) अणु
			data->fan_status[nr] += 0x20;
			data->fan_min[nr] >>= 1;
			data->fan[nr] >>= 1;
			dev_dbg(dev,
				"Increasing clock divider to %d for fan %d\n",
				FAN_DIV_FROM_REG(data->fan_status[nr]), nr + 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Decrease घड़ी भागider अगर possible */
		जबतक (!(data->fan_min[nr] & 0x80) /* min "nails" भागider */
		 && data->fan[nr] < 85 /* bad accuracy */
		 && (data->fan_status[nr] & 0x60) != 0x00) अणु
			data->fan_status[nr] -= 0x20;
			data->fan_min[nr] <<= 1;
			data->fan[nr] <<= 1;
			dev_dbg(dev,
				"Decreasing clock divider to %d for fan %d\n",
				FAN_DIV_FROM_REG(data->fan_status[nr]),
				nr + 1);
		पूर्ण
	पूर्ण

	/* Write new fan min अगर it changed */
	अगर (old_min != data->fan_min[nr]) अणु
		pc87360_ग_लिखो_value(data, LD_FAN, NO_BANK,
				    PC87360_REG_FAN_MIN(nr),
				    data->fan_min[nr]);
	पूर्ण
पूर्ण

अटल काष्ठा pc87360_data *pc87360_update_device(काष्ठा device *dev)
अणु
	काष्ठा pc87360_data *data = dev_get_drvdata(dev);
	u8 i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ * 2) || !data->valid) अणु
		dev_dbg(dev, "Data update\n");

		/* Fans */
		क्रम (i = 0; i < data->fannr; i++) अणु
			अगर (FAN_CONFIG_MONITOR(data->fan_conf, i)) अणु
				data->fan_status[i] =
					pc87360_पढ़ो_value(data, LD_FAN,
					NO_BANK, PC87360_REG_FAN_STATUS(i));
				data->fan[i] = pc87360_पढ़ो_value(data, LD_FAN,
					       NO_BANK, PC87360_REG_FAN(i));
				data->fan_min[i] = pc87360_पढ़ो_value(data,
						   LD_FAN, NO_BANK,
						   PC87360_REG_FAN_MIN(i));
				/* Change घड़ी भागider अगर needed */
				pc87360_स्वतःभाग(dev, i);
				/* Clear bits and ग_लिखो new भागider */
				pc87360_ग_लिखो_value(data, LD_FAN, NO_BANK,
						    PC87360_REG_FAN_STATUS(i),
						    data->fan_status[i]);
			पूर्ण
			अगर (FAN_CONFIG_CONTROL(data->fan_conf, i))
				data->pwm[i] = pc87360_पढ़ो_value(data, LD_FAN,
					       NO_BANK, PC87360_REG_PWM(i));
		पूर्ण

		/* Voltages */
		क्रम (i = 0; i < data->innr; i++) अणु
			data->in_status[i] = pc87360_पढ़ो_value(data, LD_IN, i,
					     PC87365_REG_IN_STATUS);
			/* Clear bits */
			pc87360_ग_लिखो_value(data, LD_IN, i,
					    PC87365_REG_IN_STATUS,
					    data->in_status[i]);
			अगर ((data->in_status[i] & CHAN_READY) == CHAN_READY) अणु
				data->in[i] = pc87360_पढ़ो_value(data, LD_IN,
					      i, PC87365_REG_IN);
			पूर्ण
			अगर (data->in_status[i] & CHAN_ENA) अणु
				data->in_min[i] = pc87360_पढ़ो_value(data,
						  LD_IN, i,
						  PC87365_REG_IN_MIN);
				data->in_max[i] = pc87360_पढ़ो_value(data,
						  LD_IN, i,
						  PC87365_REG_IN_MAX);
				अगर (i >= 11)
					data->in_crit[i-11] =
						pc87360_पढ़ो_value(data, LD_IN,
						i, PC87365_REG_TEMP_CRIT);
			पूर्ण
		पूर्ण
		अगर (data->innr) अणु
			data->in_alarms = pc87360_पढ़ो_value(data, LD_IN,
					  NO_BANK, PC87365_REG_IN_ALARMS1)
					| ((pc87360_पढ़ो_value(data, LD_IN,
					    NO_BANK, PC87365_REG_IN_ALARMS2)
					    & 0x07) << 8);
			data->vid = (data->vid_conf & 0xE0) ?
				    pc87360_पढ़ो_value(data, LD_IN,
				    NO_BANK, PC87365_REG_VID) : 0x1F;
		पूर्ण

		/* Temperatures */
		क्रम (i = 0; i < data->tempnr; i++) अणु
			data->temp_status[i] = pc87360_पढ़ो_value(data,
					       LD_TEMP, i,
					       PC87365_REG_TEMP_STATUS);
			/* Clear bits */
			pc87360_ग_लिखो_value(data, LD_TEMP, i,
					    PC87365_REG_TEMP_STATUS,
					    data->temp_status[i]);
			अगर ((data->temp_status[i] & CHAN_READY) == CHAN_READY) अणु
				data->temp[i] = pc87360_पढ़ो_value(data,
						LD_TEMP, i,
						PC87365_REG_TEMP);
			पूर्ण
			अगर (data->temp_status[i] & CHAN_ENA) अणु
				data->temp_min[i] = pc87360_पढ़ो_value(data,
						    LD_TEMP, i,
						    PC87365_REG_TEMP_MIN);
				data->temp_max[i] = pc87360_पढ़ो_value(data,
						    LD_TEMP, i,
						    PC87365_REG_TEMP_MAX);
				data->temp_crit[i] = pc87360_पढ़ो_value(data,
						     LD_TEMP, i,
						     PC87365_REG_TEMP_CRIT);
			पूर्ण
		पूर्ण
		अगर (data->tempnr) अणु
			data->temp_alarms = pc87360_पढ़ो_value(data, LD_TEMP,
					    NO_BANK, PC87365_REG_TEMP_ALARMS)
					    & 0x3F;
		पूर्ण

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

अटल पूर्णांक __init pc87360_device_add(अचिन्हित लघु address)
अणु
	काष्ठा resource res[3];
	पूर्णांक err, i, res_count;

	pdev = platक्रमm_device_alloc("pc87360", address);
	अगर (!pdev) अणु
		err = -ENOMEM;
		pr_err("Device allocation failed\n");
		जाओ निकास;
	पूर्ण

	स_रखो(res, 0, 3 * माप(काष्ठा resource));
	res_count = 0;
	क्रम (i = 0; i < 3; i++) अणु
		अगर (!extra_isa[i])
			जारी;
		res[res_count].start = extra_isa[i];
		res[res_count].end = extra_isa[i] + PC87360_EXTENT - 1;
		res[res_count].name = "pc87360";
		res[res_count].flags = IORESOURCE_IO;

		err = acpi_check_resource_conflict(&res[res_count]);
		अगर (err)
			जाओ निकास_device_put;

		res_count++;
	पूर्ण

	err = platक्रमm_device_add_resources(pdev, res, res_count);
	अगर (err) अणु
		pr_err("Device resources addition failed (%d)\n", err);
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
	वापस err;
पूर्ण

अटल पूर्णांक __init pc87360_init(व्योम)
अणु
	पूर्णांक err, i;
	अचिन्हित लघु address = 0;

	अगर (pc87360_find(0x2e, &devid, extra_isa)
	 && pc87360_find(0x4e, &devid, extra_isa)) अणु
		pr_warn("PC8736x not detected, module not inserted\n");
		वापस -ENODEV;
	पूर्ण

	/* Arbitrarily pick one of the addresses */
	क्रम (i = 0; i < 3; i++) अणु
		अगर (extra_isa[i] != 0x0000) अणु
			address = extra_isa[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (address == 0x0000) अणु
		pr_warn("No active logical device, module not inserted\n");
		वापस -ENODEV;
	पूर्ण

	err = platक्रमm_driver_रेजिस्टर(&pc87360_driver);
	अगर (err)
		जाओ निकास;

	/* Sets global pdev as a side effect */
	err = pc87360_device_add(address);
	अगर (err)
		जाओ निकास_driver;

	वापस 0;

 निकास_driver:
	platक्रमm_driver_unरेजिस्टर(&pc87360_driver);
 निकास:
	वापस err;
पूर्ण

अटल व्योम __निकास pc87360_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(pdev);
	platक्रमm_driver_unरेजिस्टर(&pc87360_driver);
पूर्ण


MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("PC8736x hardware monitor");
MODULE_LICENSE("GPL");

module_init(pc87360_init);
module_निकास(pc87360_निकास);
