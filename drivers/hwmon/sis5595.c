<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sis5595.c - Part of lm_sensors, Linux kernel modules
 *	       क्रम hardware monitoring
 *
 * Copyright (C) 1998 - 2001 Froकरो Looijaard <froकरोl@dds.nl>,
 *			     Kyथघsti Mथअlkki <kmalkki@cc.hut.fi>, and
 *			     Mark D. Studebaker <mdsxyz123@yahoo.com>
 * Ported to Linux 2.6 by Aurelien Jarno <aurelien@aurel32.net> with
 * the help of Jean Delvare <jdelvare@suse.de>
 */

/*
 * SiS southbridge has a LM78-like chip पूर्णांकegrated on the same IC.
 * This driver is a customized copy of lm78.c
 *
 * Supports following revisions:
 *	Version		PCI ID		PCI Revision
 *	1		1039/0008	AF or less
 *	2		1039/0008	B0 or greater
 *
 *  Note: these chips contain a 0008 device which is incompatible with the
 *	 5595. We recognize these by the presence of the listed
 *	 "blacklist" PCI ID and refuse to load.
 *
 * NOT SUPPORTED	PCI ID		BLACKLIST PCI ID
 *	 540		0008		0540
 *	 550		0008		0550
 *	5513		0008		5511
 *	5581		0008		5597
 *	5582		0008		5597
 *	5597		0008		5597
 *	5598		0008		5597/5598
 *	 630		0008		0630
 *	 645		0008		0645
 *	 730		0008		0730
 *	 735		0008		0735
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

/*
 * If क्रमce_addr is set to anything dअगरferent from 0, we क्रमcibly enable
 * the device at the given address.
 */
अटल u16 क्रमce_addr;
module_param(क्रमce_addr, uलघु, 0);
MODULE_PARM_DESC(क्रमce_addr,
		 "Initialize the base address of the sensors");

अटल काष्ठा platक्रमm_device *pdev;

/* Many SIS5595 स्थिरants specअगरied below */

/* Length of ISA address segment */
#घोषणा SIS5595_EXTENT 8
/* PCI Config Registers */
#घोषणा SIS5595_BASE_REG 0x68
#घोषणा SIS5595_PIN_REG 0x7A
#घोषणा SIS5595_ENABLE_REG 0x7B

/* Where are the ISA address/data रेजिस्टरs relative to the base address */
#घोषणा SIS5595_ADDR_REG_OFFSET 5
#घोषणा SIS5595_DATA_REG_OFFSET 6

/* The SIS5595 रेजिस्टरs */
#घोषणा SIS5595_REG_IN_MAX(nr) (0x2b + (nr) * 2)
#घोषणा SIS5595_REG_IN_MIN(nr) (0x2c + (nr) * 2)
#घोषणा SIS5595_REG_IN(nr) (0x20 + (nr))

#घोषणा SIS5595_REG_FAN_MIN(nr) (0x3b + (nr))
#घोषणा SIS5595_REG_FAN(nr) (0x28 + (nr))

/*
 * On the first version of the chip, the temp रेजिस्टरs are separate.
 * On the second version,
 * TEMP pin is shared with IN4, configured in PCI रेजिस्टर 0x7A.
 * The रेजिस्टरs are the same as well.
 * OVER and HYST are really MAX and MIN.
 */

#घोषणा REV2MIN	0xb0
#घोषणा SIS5595_REG_TEMP	(((data->revision) >= REV2MIN) ? \
					SIS5595_REG_IN(4) : 0x27)
#घोषणा SIS5595_REG_TEMP_OVER	(((data->revision) >= REV2MIN) ? \
					SIS5595_REG_IN_MAX(4) : 0x39)
#घोषणा SIS5595_REG_TEMP_HYST	(((data->revision) >= REV2MIN) ? \
					SIS5595_REG_IN_MIN(4) : 0x3a)

#घोषणा SIS5595_REG_CONFIG 0x40
#घोषणा SIS5595_REG_ALARM1 0x41
#घोषणा SIS5595_REG_ALARM2 0x42
#घोषणा SIS5595_REG_FANDIV 0x47

/*
 * Conversions. Limit checking is only करोne on the TO_REG
 * variants.
 */

/*
 * IN: mV, (0V to 4.08V)
 * REG: 16mV/bit
 */
अटल अंतरभूत u8 IN_TO_REG(अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ nval = clamp_val(val, 0, 4080);
	वापस (nval + 8) / 16;
पूर्ण
#घोषणा IN_FROM_REG(val) ((val) *  16)

अटल अंतरभूत u8 FAN_TO_REG(दीर्घ rpm, पूर्णांक भाग)
अणु
	अगर (rpm <= 0)
		वापस 255;
	अगर (rpm > 1350000)
		वापस 1;
	वापस clamp_val((1350000 + rpm * भाग / 2) / (rpm * भाग), 1, 254);
पूर्ण

अटल अंतरभूत पूर्णांक FAN_FROM_REG(u8 val, पूर्णांक भाग)
अणु
	वापस val == 0 ? -1 : val == 255 ? 0 : 1350000 / (val * भाग);
पूर्ण

/*
 * TEMP: mC (-54.12C to +157.53C)
 * REG: 0.83C/bit + 52.12, two's complement
 */
अटल अंतरभूत पूर्णांक TEMP_FROM_REG(s8 val)
अणु
	वापस val * 830 + 52120;
पूर्ण
अटल अंतरभूत s8 TEMP_TO_REG(दीर्घ val)
अणु
	पूर्णांक nval = clamp_val(val, -54120, 157530) ;
	वापस nval < 0 ? (nval - 5212 - 415) / 830 : (nval - 5212 + 415) / 830;
पूर्ण

/*
 * FAN DIV: 1, 2, 4, or 8 (शेषs to 2)
 * REG: 0, 1, 2, or 3 (respectively) (शेषs to 1)
 */
अटल अंतरभूत u8 DIV_TO_REG(पूर्णांक val)
अणु
	वापस val == 8 ? 3 : val == 4 ? 2 : val == 1 ? 0 : 1;
पूर्ण
#घोषणा DIV_FROM_REG(val) (1 << (val))

/*
 * For each रेजिस्टरed chip, we need to keep some data in memory.
 * The काष्ठाure is dynamically allocated.
 */
काष्ठा sis5595_data अणु
	अचिन्हित लघु addr;
	स्थिर अक्षर *name;
	काष्ठा device *hwmon_dev;
	काष्ठा mutex lock;

	काष्ठा mutex update_lock;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */
	अक्षर maxins;		/* == 3 अगर temp enabled, otherwise == 4 */
	u8 revision;		/* Reg. value */

	u8 in[5];		/* Register value */
	u8 in_max[5];		/* Register value */
	u8 in_min[5];		/* Register value */
	u8 fan[2];		/* Register value */
	u8 fan_min[2];		/* Register value */
	s8 temp;		/* Register value */
	s8 temp_over;		/* Register value */
	s8 temp_hyst;		/* Register value */
	u8 fan_भाग[2];		/* Register encoding, shअगरted right */
	u16 alarms;		/* Register encoding, combined */
पूर्ण;

अटल काष्ठा pci_dev *s_bridge;	/* poपूर्णांकer to the (only) sis5595 */

अटल पूर्णांक sis5595_probe(काष्ठा platक्रमm_device *pdev);
अटल पूर्णांक sis5595_हटाओ(काष्ठा platक्रमm_device *pdev);

अटल पूर्णांक sis5595_पढ़ो_value(काष्ठा sis5595_data *data, u8 reg);
अटल व्योम sis5595_ग_लिखो_value(काष्ठा sis5595_data *data, u8 reg, u8 value);
अटल काष्ठा sis5595_data *sis5595_update_device(काष्ठा device *dev);
अटल व्योम sis5595_init_device(काष्ठा sis5595_data *data);

अटल काष्ठा platक्रमm_driver sis5595_driver = अणु
	.driver = अणु
		.name	= "sis5595",
	पूर्ण,
	.probe		= sis5595_probe,
	.हटाओ		= sis5595_हटाओ,
पूर्ण;

/* 4 Voltages */
अटल sमाप_प्रकार in_show(काष्ठा device *dev, काष्ठा device_attribute *da,
		       अक्षर *buf)
अणु
	काष्ठा sis5595_data *data = sis5595_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	वापस प्र_लिखो(buf, "%d\n", IN_FROM_REG(data->in[nr]));
पूर्ण

अटल sमाप_प्रकार in_min_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			   अक्षर *buf)
अणु
	काष्ठा sis5595_data *data = sis5595_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	वापस प्र_लिखो(buf, "%d\n", IN_FROM_REG(data->in_min[nr]));
पूर्ण

अटल sमाप_प्रकार in_max_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			   अक्षर *buf)
अणु
	काष्ठा sis5595_data *data = sis5595_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	वापस प्र_लिखो(buf, "%d\n", IN_FROM_REG(data->in_max[nr]));
पूर्ण

अटल sमाप_प्रकार in_min_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sis5595_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_min[nr] = IN_TO_REG(val);
	sis5595_ग_लिखो_value(data, SIS5595_REG_IN_MIN(nr), data->in_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार in_max_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sis5595_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_max[nr] = IN_TO_REG(val);
	sis5595_ग_लिखो_value(data, SIS5595_REG_IN_MAX(nr), data->in_max[nr]);
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

/* Temperature */
अटल sमाप_प्रकार temp1_input_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sis5595_data *data = sis5595_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp));
पूर्ण

अटल sमाप_प्रकार temp1_max_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा sis5595_data *data = sis5595_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_over));
पूर्ण

अटल sमाप_प्रकार temp1_max_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	काष्ठा sis5595_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_over = TEMP_TO_REG(val);
	sis5595_ग_लिखो_value(data, SIS5595_REG_TEMP_OVER, data->temp_over);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp1_max_hyst_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sis5595_data *data = sis5595_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", TEMP_FROM_REG(data->temp_hyst));
पूर्ण

अटल sमाप_प्रकार temp1_max_hyst_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sis5595_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_hyst = TEMP_TO_REG(val);
	sis5595_ग_लिखो_value(data, SIS5595_REG_TEMP_HYST, data->temp_hyst);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RO(temp1_input);
अटल DEVICE_ATTR_RW(temp1_max);
अटल DEVICE_ATTR_RW(temp1_max_hyst);

/* 2 Fans */
अटल sमाप_प्रकार fan_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			अक्षर *buf)
अणु
	काष्ठा sis5595_data *data = sis5595_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan[nr],
		DIV_FROM_REG(data->fan_भाग[nr])));
पूर्ण

अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			    अक्षर *buf)
अणु
	काष्ठा sis5595_data *data = sis5595_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	वापस प्र_लिखो(buf, "%d\n", FAN_FROM_REG(data->fan_min[nr],
		DIV_FROM_REG(data->fan_भाग[nr])));
पूर्ण

अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sis5595_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan_min[nr] = FAN_TO_REG(val, DIV_FROM_REG(data->fan_भाग[nr]));
	sis5595_ग_लिखो_value(data, SIS5595_REG_FAN_MIN(nr), data->fan_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार fan_भाग_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			    अक्षर *buf)
अणु
	काष्ठा sis5595_data *data = sis5595_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	वापस प्र_लिखो(buf, "%d\n", DIV_FROM_REG(data->fan_भाग[nr]));
पूर्ण

/*
 * Note: we save and restore the fan minimum here, because its value is
 * determined in part by the fan भागisor.  This follows the principle of
 * least surprise; the user करोesn't expect the fan minimum to change just
 * because the भागisor changed.
 */
अटल sमाप_प्रकार fan_भाग_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sis5595_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ min;
	पूर्णांक reg;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	min = FAN_FROM_REG(data->fan_min[nr],
			DIV_FROM_REG(data->fan_भाग[nr]));
	reg = sis5595_पढ़ो_value(data, SIS5595_REG_FANDIV);

	चयन (val) अणु
	हाल 1:
		data->fan_भाग[nr] = 0;
		अवरोध;
	हाल 2:
		data->fan_भाग[nr] = 1;
		अवरोध;
	हाल 4:
		data->fan_भाग[nr] = 2;
		अवरोध;
	हाल 8:
		data->fan_भाग[nr] = 3;
		अवरोध;
	शेष:
		dev_err(dev,
			"fan_div value %ld not supported. Choose one of 1, 2, 4 or 8!\n",
			val);
		mutex_unlock(&data->update_lock);
		वापस -EINVAL;
	पूर्ण

	चयन (nr) अणु
	हाल 0:
		reg = (reg & 0xcf) | (data->fan_भाग[nr] << 4);
		अवरोध;
	हाल 1:
		reg = (reg & 0x3f) | (data->fan_भाग[nr] << 6);
		अवरोध;
	पूर्ण
	sis5595_ग_लिखो_value(data, SIS5595_REG_FANDIV, reg);
	data->fan_min[nr] =
		FAN_TO_REG(min, DIV_FROM_REG(data->fan_भाग[nr]));
	sis5595_ग_लिखो_value(data, SIS5595_REG_FAN_MIN(nr), data->fan_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan1_min, fan_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan1_भाग, fan_भाग, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan2_min, fan_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan2_भाग, fan_भाग, 1);

/* Alarms */
अटल sमाप_प्रकार alarms_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा sis5595_data *data = sis5595_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->alarms);
पूर्ण
अटल DEVICE_ATTR_RO(alarms);

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			  अक्षर *buf)
अणु
	काष्ठा sis5595_data *data = sis5595_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(da)->index;
	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> nr) & 1);
पूर्ण
अटल SENSOR_DEVICE_ATTR_RO(in0_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_alarm, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_alarm, alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_alarm, alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_alarm, alarm, 15);
अटल SENSOR_DEVICE_ATTR_RO(fan1_alarm, alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(fan2_alarm, alarm, 7);
अटल SENSOR_DEVICE_ATTR_RO(temp1_alarm, alarm, 15);

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा sis5595_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%s\n", data->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल काष्ठा attribute *sis5595_attributes[] = अणु
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

	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan1_भाग.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan2_भाग.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,

	&dev_attr_alarms.attr,
	&dev_attr_name.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group sis5595_group = अणु
	.attrs = sis5595_attributes,
पूर्ण;

अटल काष्ठा attribute *sis5595_attributes_in4[] = अणु
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group sis5595_group_in4 = अणु
	.attrs = sis5595_attributes_in4,
पूर्ण;

अटल काष्ठा attribute *sis5595_attributes_temp1[] = अणु
	&dev_attr_temp1_input.attr,
	&dev_attr_temp1_max.attr,
	&dev_attr_temp1_max_hyst.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group sis5595_group_temp1 = अणु
	.attrs = sis5595_attributes_temp1,
पूर्ण;

/* This is called when the module is loaded */
अटल पूर्णांक sis5595_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;
	काष्ठा sis5595_data *data;
	काष्ठा resource *res;
	अक्षर val;

	/* Reserve the ISA region */
	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!devm_request_region(&pdev->dev, res->start, SIS5595_EXTENT,
				 sis5595_driver.driver.name))
		वापस -EBUSY;

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा sis5595_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	mutex_init(&data->lock);
	mutex_init(&data->update_lock);
	data->addr = res->start;
	data->name = "sis5595";
	platक्रमm_set_drvdata(pdev, data);

	/*
	 * Check revision and pin रेजिस्टरs to determine whether 4 or 5 voltages
	 */
	data->revision = s_bridge->revision;
	/* 4 voltages, 1 temp */
	data->maxins = 3;
	अगर (data->revision >= REV2MIN) अणु
		pci_पढ़ो_config_byte(s_bridge, SIS5595_PIN_REG, &val);
		अगर (!(val & 0x80))
			/* 5 voltages, no temps */
			data->maxins = 4;
	पूर्ण

	/* Initialize the SIS5595 chip */
	sis5595_init_device(data);

	/* A few vars need to be filled upon startup */
	क्रम (i = 0; i < 2; i++) अणु
		data->fan_min[i] = sis5595_पढ़ो_value(data,
					SIS5595_REG_FAN_MIN(i));
	पूर्ण

	/* Register sysfs hooks */
	err = sysfs_create_group(&pdev->dev.kobj, &sis5595_group);
	अगर (err)
		वापस err;
	अगर (data->maxins == 4) अणु
		err = sysfs_create_group(&pdev->dev.kobj, &sis5595_group_in4);
		अगर (err)
			जाओ निकास_हटाओ_files;
	पूर्ण अन्यथा अणु
		err = sysfs_create_group(&pdev->dev.kobj, &sis5595_group_temp1);
		अगर (err)
			जाओ निकास_हटाओ_files;
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(&pdev->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		जाओ निकास_हटाओ_files;
	पूर्ण

	वापस 0;

निकास_हटाओ_files:
	sysfs_हटाओ_group(&pdev->dev.kobj, &sis5595_group);
	sysfs_हटाओ_group(&pdev->dev.kobj, &sis5595_group_in4);
	sysfs_हटाओ_group(&pdev->dev.kobj, &sis5595_group_temp1);
	वापस err;
पूर्ण

अटल पूर्णांक sis5595_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sis5595_data *data = platक्रमm_get_drvdata(pdev);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	sysfs_हटाओ_group(&pdev->dev.kobj, &sis5595_group);
	sysfs_हटाओ_group(&pdev->dev.kobj, &sis5595_group_in4);
	sysfs_हटाओ_group(&pdev->dev.kobj, &sis5595_group_temp1);

	वापस 0;
पूर्ण

/* ISA access must be locked explicitly. */
अटल पूर्णांक sis5595_पढ़ो_value(काष्ठा sis5595_data *data, u8 reg)
अणु
	पूर्णांक res;

	mutex_lock(&data->lock);
	outb_p(reg, data->addr + SIS5595_ADDR_REG_OFFSET);
	res = inb_p(data->addr + SIS5595_DATA_REG_OFFSET);
	mutex_unlock(&data->lock);
	वापस res;
पूर्ण

अटल व्योम sis5595_ग_लिखो_value(काष्ठा sis5595_data *data, u8 reg, u8 value)
अणु
	mutex_lock(&data->lock);
	outb_p(reg, data->addr + SIS5595_ADDR_REG_OFFSET);
	outb_p(value, data->addr + SIS5595_DATA_REG_OFFSET);
	mutex_unlock(&data->lock);
पूर्ण

/* Called when we have found a new SIS5595. */
अटल व्योम sis5595_init_device(काष्ठा sis5595_data *data)
अणु
	u8 config = sis5595_पढ़ो_value(data, SIS5595_REG_CONFIG);
	अगर (!(config & 0x01))
		sis5595_ग_लिखो_value(data, SIS5595_REG_CONFIG,
				(config & 0xf7) | 0x01);
पूर्ण

अटल काष्ठा sis5595_data *sis5595_update_device(काष्ठा device *dev)
अणु
	काष्ठा sis5595_data *data = dev_get_drvdata(dev);
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) अणु

		क्रम (i = 0; i <= data->maxins; i++) अणु
			data->in[i] =
			    sis5595_पढ़ो_value(data, SIS5595_REG_IN(i));
			data->in_min[i] =
			    sis5595_पढ़ो_value(data,
					       SIS5595_REG_IN_MIN(i));
			data->in_max[i] =
			    sis5595_पढ़ो_value(data,
					       SIS5595_REG_IN_MAX(i));
		पूर्ण
		क्रम (i = 0; i < 2; i++) अणु
			data->fan[i] =
			    sis5595_पढ़ो_value(data, SIS5595_REG_FAN(i));
			data->fan_min[i] =
			    sis5595_पढ़ो_value(data,
					       SIS5595_REG_FAN_MIN(i));
		पूर्ण
		अगर (data->maxins == 3) अणु
			data->temp =
			    sis5595_पढ़ो_value(data, SIS5595_REG_TEMP);
			data->temp_over =
			    sis5595_पढ़ो_value(data, SIS5595_REG_TEMP_OVER);
			data->temp_hyst =
			    sis5595_पढ़ो_value(data, SIS5595_REG_TEMP_HYST);
		पूर्ण
		i = sis5595_पढ़ो_value(data, SIS5595_REG_FANDIV);
		data->fan_भाग[0] = (i >> 4) & 0x03;
		data->fan_भाग[1] = i >> 6;
		data->alarms =
		    sis5595_पढ़ो_value(data, SIS5595_REG_ALARM1) |
		    (sis5595_पढ़ो_value(data, SIS5595_REG_ALARM2) << 8);
		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

अटल स्थिर काष्ठा pci_device_id sis5595_pci_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_503) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, sis5595_pci_ids);

अटल पूर्णांक blacklist[] = अणु
	PCI_DEVICE_ID_SI_540,
	PCI_DEVICE_ID_SI_550,
	PCI_DEVICE_ID_SI_630,
	PCI_DEVICE_ID_SI_645,
	PCI_DEVICE_ID_SI_730,
	PCI_DEVICE_ID_SI_735,
	PCI_DEVICE_ID_SI_5511, /*
				* 5513 chip has the 0008 device but
				* that ID shows up in other chips so we
				* use the 5511 ID क्रम recognition
				*/
	PCI_DEVICE_ID_SI_5597,
	PCI_DEVICE_ID_SI_5598,
	0 पूर्ण;

अटल पूर्णांक sis5595_device_add(अचिन्हित लघु address)
अणु
	काष्ठा resource res = अणु
		.start	= address,
		.end	= address + SIS5595_EXTENT - 1,
		.name	= "sis5595",
		.flags	= IORESOURCE_IO,
	पूर्ण;
	पूर्णांक err;

	err = acpi_check_resource_conflict(&res);
	अगर (err)
		जाओ निकास;

	pdev = platक्रमm_device_alloc("sis5595", address);
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
	वापस err;
पूर्ण

अटल पूर्णांक sis5595_pci_probe(काष्ठा pci_dev *dev,
				       स्थिर काष्ठा pci_device_id *id)
अणु
	u16 address;
	u8 enable;
	पूर्णांक *i;

	क्रम (i = blacklist; *i != 0; i++) अणु
		काष्ठा pci_dev *d;
		d = pci_get_device(PCI_VENDOR_ID_SI, *i, शून्य);
		अगर (d) अणु
			dev_err(&d->dev,
				"Looked for SIS5595 but found unsupported device %.4x\n",
				*i);
			pci_dev_put(d);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	क्रमce_addr &= ~(SIS5595_EXTENT - 1);
	अगर (क्रमce_addr) अणु
		dev_warn(&dev->dev, "Forcing ISA address 0x%x\n", क्रमce_addr);
		pci_ग_लिखो_config_word(dev, SIS5595_BASE_REG, क्रमce_addr);
	पूर्ण

	अगर (PCIBIOS_SUCCESSFUL !=
	    pci_पढ़ो_config_word(dev, SIS5595_BASE_REG, &address)) अणु
		dev_err(&dev->dev, "Failed to read ISA address\n");
		वापस -ENODEV;
	पूर्ण

	address &= ~(SIS5595_EXTENT - 1);
	अगर (!address) अणु
		dev_err(&dev->dev,
			"Base address not set - upgrade BIOS or use force_addr=0xaddr\n");
		वापस -ENODEV;
	पूर्ण
	अगर (क्रमce_addr && address != क्रमce_addr) अणु
		/* करोesn't work क्रम some chips? */
		dev_err(&dev->dev, "Failed to force ISA address\n");
		वापस -ENODEV;
	पूर्ण

	अगर (PCIBIOS_SUCCESSFUL !=
	    pci_पढ़ो_config_byte(dev, SIS5595_ENABLE_REG, &enable)) अणु
		dev_err(&dev->dev, "Failed to read enable register\n");
		वापस -ENODEV;
	पूर्ण
	अगर (!(enable & 0x80)) अणु
		अगर ((PCIBIOS_SUCCESSFUL !=
		     pci_ग_लिखो_config_byte(dev, SIS5595_ENABLE_REG,
					   enable | 0x80))
		 || (PCIBIOS_SUCCESSFUL !=
		     pci_पढ़ो_config_byte(dev, SIS5595_ENABLE_REG, &enable))
		 || (!(enable & 0x80))) अणु
			/* करोesn't work क्रम some chips! */
			dev_err(&dev->dev, "Failed to enable HWM device\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (platक्रमm_driver_रेजिस्टर(&sis5595_driver)) अणु
		dev_dbg(&dev->dev, "Failed to register sis5595 driver\n");
		जाओ निकास;
	पूर्ण

	s_bridge = pci_dev_get(dev);
	/* Sets global pdev as a side effect */
	अगर (sis5595_device_add(address))
		जाओ निकास_unरेजिस्टर;

	/*
	 * Always वापस failure here.  This is to allow other drivers to bind
	 * to this pci device.  We करोn't really want to have control over the
	 * pci device, we only wanted to पढ़ो as few रेजिस्टर values from it.
	 */
	वापस -ENODEV;

निकास_unरेजिस्टर:
	pci_dev_put(dev);
	platक्रमm_driver_unरेजिस्टर(&sis5595_driver);
निकास:
	वापस -ENODEV;
पूर्ण

अटल काष्ठा pci_driver sis5595_pci_driver = अणु
	.name            = "sis5595",
	.id_table        = sis5595_pci_ids,
	.probe           = sis5595_pci_probe,
पूर्ण;

अटल पूर्णांक __init sm_sis5595_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&sis5595_pci_driver);
पूर्ण

अटल व्योम __निकास sm_sis5595_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&sis5595_pci_driver);
	अगर (s_bridge != शून्य) अणु
		platक्रमm_device_unरेजिस्टर(pdev);
		platक्रमm_driver_unरेजिस्टर(&sis5595_driver);
		pci_dev_put(s_bridge);
		s_bridge = शून्य;
	पूर्ण
पूर्ण

MODULE_AUTHOR("Aurelien Jarno <aurelien@aurel32.net>");
MODULE_DESCRIPTION("SiS 5595 Sensor device");
MODULE_LICENSE("GPL");

module_init(sm_sis5595_init);
module_निकास(sm_sis5595_निकास);
