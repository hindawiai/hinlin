<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * smsc47m1.c - Part of lm_sensors, Linux kernel modules
 *		क्रम hardware monitoring
 *
 * Supports the SMSC LPC47B27x, LPC47M10x, LPC47M112, LPC47M13x,
 * LPC47M14x, LPC47M15x, LPC47M192, LPC47M292 and LPC47M997
 * Super-I/O chips.
 *
 * Copyright (C) 2002 Mark D. Studebaker <mdsxyz123@yahoo.com>
 * Copyright (C) 2004-2007 Jean Delvare <jdelvare@suse.de>
 * Ported to Linux 2.6 by Gabriele Gorla <gorlik@yahoo.com>
 *			and Jean Delvare
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

अटल अचिन्हित लघु क्रमce_id;
module_param(क्रमce_id, uलघु, 0);
MODULE_PARM_DESC(क्रमce_id, "Override the detected device ID");

अटल काष्ठा platक्रमm_device *pdev;

#घोषणा DRVNAME "smsc47m1"
क्रमागत chips अणु smsc47m1, smsc47m2 पूर्ण;

/* Super-I/0 रेजिस्टरs and commands */

#घोषणा REG	0x2e	/* The रेजिस्टर to पढ़ो/ग_लिखो */
#घोषणा VAL	0x2f	/* The value to पढ़ो/ग_लिखो */

अटल अंतरभूत व्योम
superio_outb(पूर्णांक reg, पूर्णांक val)
अणु
	outb(reg, REG);
	outb(val, VAL);
पूर्ण

अटल अंतरभूत पूर्णांक
superio_inb(पूर्णांक reg)
अणु
	outb(reg, REG);
	वापस inb(VAL);
पूर्ण

/* logical device क्रम fans is 0x0A */
#घोषणा superio_select() superio_outb(0x07, 0x0A)

अटल अंतरभूत पूर्णांक
superio_enter(व्योम)
अणु
	अगर (!request_muxed_region(REG, 2, DRVNAME))
		वापस -EBUSY;

	outb(0x55, REG);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
superio_निकास(व्योम)
अणु
	outb(0xAA, REG);
	release_region(REG, 2);
पूर्ण

#घोषणा SUPERIO_REG_ACT		0x30
#घोषणा SUPERIO_REG_BASE	0x60
#घोषणा SUPERIO_REG_DEVID	0x20
#घोषणा SUPERIO_REG_DEVREV	0x21

/* Logical device रेजिस्टरs */

#घोषणा SMSC_EXTENT		0x80

/* nr is 0 or 1 in the macros below */
#घोषणा SMSC47M1_REG_ALARM		0x04
#घोषणा SMSC47M1_REG_TPIN(nr)		(0x34 - (nr))
#घोषणा SMSC47M1_REG_PPIN(nr)		(0x36 - (nr))
#घोषणा SMSC47M1_REG_FANDIV		0x58

अटल स्थिर u8 SMSC47M1_REG_FAN[3]		= अणु 0x59, 0x5a, 0x6b पूर्ण;
अटल स्थिर u8 SMSC47M1_REG_FAN_PRELOAD[3]	= अणु 0x5b, 0x5c, 0x6c पूर्ण;
अटल स्थिर u8 SMSC47M1_REG_PWM[3]		= अणु 0x56, 0x57, 0x69 पूर्ण;

#घोषणा SMSC47M2_REG_ALARM6		0x09
#घोषणा SMSC47M2_REG_TPIN1		0x38
#घोषणा SMSC47M2_REG_TPIN2		0x37
#घोषणा SMSC47M2_REG_TPIN3		0x2d
#घोषणा SMSC47M2_REG_PPIN3		0x2c
#घोषणा SMSC47M2_REG_FANDIV3		0x6a

#घोषणा MIN_FROM_REG(reg, भाग)		((reg) >= 192 ? 0 : \
					 983040 / ((192 - (reg)) * (भाग)))
#घोषणा FAN_FROM_REG(reg, भाग, preload)	((reg) <= (preload) || (reg) == 255 ? \
					 0 : \
					 983040 / (((reg) - (preload)) * (भाग)))
#घोषणा DIV_FROM_REG(reg)		(1 << (reg))
#घोषणा PWM_FROM_REG(reg)		(((reg) & 0x7E) << 1)
#घोषणा PWM_EN_FROM_REG(reg)		((~(reg)) & 0x01)
#घोषणा PWM_TO_REG(reg)			(((reg) >> 1) & 0x7E)

काष्ठा smsc47m1_data अणु
	अचिन्हित लघु addr;
	स्थिर अक्षर *name;
	क्रमागत chips type;
	काष्ठा device *hwmon_dev;

	काष्ठा mutex update_lock;
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */

	u8 fan[3];		/* Register value */
	u8 fan_preload[3];	/* Register value */
	u8 fan_भाग[3];		/* Register encoding, shअगरted right */
	u8 alarms;		/* Register encoding */
	u8 pwm[3];		/* Register value (bit 0 is disable) */
पूर्ण;

काष्ठा smsc47m1_sio_data अणु
	क्रमागत chips type;
	u8 activate;		/* Remember initial device state */
पूर्ण;

अटल अंतरभूत पूर्णांक smsc47m1_पढ़ो_value(काष्ठा smsc47m1_data *data, u8 reg)
अणु
	वापस inb_p(data->addr + reg);
पूर्ण

अटल अंतरभूत व्योम smsc47m1_ग_लिखो_value(काष्ठा smsc47m1_data *data, u8 reg,
		u8 value)
अणु
	outb_p(value, data->addr + reg);
पूर्ण

अटल काष्ठा smsc47m1_data *smsc47m1_update_device(काष्ठा device *dev,
		पूर्णांक init)
अणु
	काष्ठा smsc47m1_data *data = dev_get_drvdata(dev);

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2) || init) अणु
		पूर्णांक i, fan_nr;
		fan_nr = data->type == smsc47m2 ? 3 : 2;

		क्रम (i = 0; i < fan_nr; i++) अणु
			data->fan[i] = smsc47m1_पढ़ो_value(data,
				       SMSC47M1_REG_FAN[i]);
			data->fan_preload[i] = smsc47m1_पढ़ो_value(data,
					       SMSC47M1_REG_FAN_PRELOAD[i]);
			data->pwm[i] = smsc47m1_पढ़ो_value(data,
				       SMSC47M1_REG_PWM[i]);
		पूर्ण

		i = smsc47m1_पढ़ो_value(data, SMSC47M1_REG_FANDIV);
		data->fan_भाग[0] = (i >> 4) & 0x03;
		data->fan_भाग[1] = i >> 6;

		data->alarms = smsc47m1_पढ़ो_value(data,
			       SMSC47M1_REG_ALARM) >> 6;
		/* Clear alarms अगर needed */
		अगर (data->alarms)
			smsc47m1_ग_लिखो_value(data, SMSC47M1_REG_ALARM, 0xC0);

		अगर (fan_nr >= 3) अणु
			data->fan_भाग[2] = (smsc47m1_पढ़ो_value(data,
					    SMSC47M2_REG_FANDIV3) >> 4) & 0x03;
			data->alarms |= (smsc47m1_पढ़ो_value(data,
					 SMSC47M2_REG_ALARM6) & 0x40) >> 4;
			/* Clear alarm अगर needed */
			अगर (data->alarms & 0x04)
				smsc47m1_ग_लिखो_value(data,
						     SMSC47M2_REG_ALARM6,
						     0x40);
		पूर्ण

		data->last_updated = jअगरfies;
	पूर्ण

	mutex_unlock(&data->update_lock);
	वापस data;
पूर्ण

अटल sमाप_प्रकार fan_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा smsc47m1_data *data = smsc47m1_update_device(dev, 0);
	पूर्णांक nr = attr->index;
	/*
	 * This chip (stupidly) stops monitoring fan speed अगर PWM is
	 * enabled and duty cycle is 0%. This is fine अगर the monitoring
	 * and control concern the same fan, but troublesome अगर they are
	 * not (which could as well happen).
	 */
	पूर्णांक rpm = (data->pwm[nr] & 0x7F) == 0x00 ? 0 :
		  FAN_FROM_REG(data->fan[nr],
			       DIV_FROM_REG(data->fan_भाग[nr]),
			       data->fan_preload[nr]);
	वापस प्र_लिखो(buf, "%d\n", rpm);
पूर्ण

अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा smsc47m1_data *data = smsc47m1_update_device(dev, 0);
	पूर्णांक nr = attr->index;
	पूर्णांक rpm = MIN_FROM_REG(data->fan_preload[nr],
			       DIV_FROM_REG(data->fan_भाग[nr]));
	वापस प्र_लिखो(buf, "%d\n", rpm);
पूर्ण

अटल sमाप_प्रकार fan_भाग_show(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा smsc47m1_data *data = smsc47m1_update_device(dev, 0);
	वापस प्र_लिखो(buf, "%d\n", DIV_FROM_REG(data->fan_भाग[attr->index]));
पूर्ण

अटल sमाप_प्रकार fan_alarm_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक bitnr = to_sensor_dev_attr(devattr)->index;
	काष्ठा smsc47m1_data *data = smsc47m1_update_device(dev, 0);
	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> bitnr) & 1);
पूर्ण

अटल sमाप_प्रकार pwm_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा smsc47m1_data *data = smsc47m1_update_device(dev, 0);
	वापस प्र_लिखो(buf, "%d\n", PWM_FROM_REG(data->pwm[attr->index]));
पूर्ण

अटल sमाप_प्रकार pwm_en_show(काष्ठा device *dev,
			   काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा smsc47m1_data *data = smsc47m1_update_device(dev, 0);
	वापस प्र_लिखो(buf, "%d\n", PWM_EN_FROM_REG(data->pwm[attr->index]));
पूर्ण

अटल sमाप_प्रकार alarms_show(काष्ठा device *dev,
			   काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा smsc47m1_data *data = smsc47m1_update_device(dev, 0);
	वापस प्र_लिखो(buf, "%d\n", data->alarms);
पूर्ण

अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा smsc47m1_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = attr->index;
	दीर्घ rpmभाग;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	rpmभाग = val * DIV_FROM_REG(data->fan_भाग[nr]);

	अगर (983040 > 192 * rpmभाग || 2 * rpmभाग > 983040) अणु
		mutex_unlock(&data->update_lock);
		वापस -EINVAL;
	पूर्ण

	data->fan_preload[nr] = 192 - ((983040 + rpmभाग / 2) / rpmभाग);
	smsc47m1_ग_लिखो_value(data, SMSC47M1_REG_FAN_PRELOAD[nr],
			     data->fan_preload[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/*
 * Note: we save and restore the fan minimum here, because its value is
 * determined in part by the fan घड़ी भागider.  This follows the principle
 * of least surprise; the user करोesn't expect the fan minimum to change just
 * because the भागider changed.
 */
अटल sमाप_प्रकार fan_भाग_store(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा smsc47m1_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = attr->index;
	दीर्घ new_भाग;
	पूर्णांक err;
	दीर्घ पंचांगp;
	u8 old_भाग = DIV_FROM_REG(data->fan_भाग[nr]);

	err = kम_से_दीर्घ(buf, 10, &new_भाग);
	अगर (err)
		वापस err;

	अगर (new_भाग == old_भाग) /* No change */
		वापस count;

	mutex_lock(&data->update_lock);
	चयन (new_भाग) अणु
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
		mutex_unlock(&data->update_lock);
		वापस -EINVAL;
	पूर्ण

	चयन (nr) अणु
	हाल 0:
	हाल 1:
		पंचांगp = smsc47m1_पढ़ो_value(data, SMSC47M1_REG_FANDIV)
		      & ~(0x03 << (4 + 2 * nr));
		पंचांगp |= data->fan_भाग[nr] << (4 + 2 * nr);
		smsc47m1_ग_लिखो_value(data, SMSC47M1_REG_FANDIV, पंचांगp);
		अवरोध;
	हाल 2:
		पंचांगp = smsc47m1_पढ़ो_value(data, SMSC47M2_REG_FANDIV3) & 0xCF;
		पंचांगp |= data->fan_भाग[2] << 4;
		smsc47m1_ग_लिखो_value(data, SMSC47M2_REG_FANDIV3, पंचांगp);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	/* Preserve fan min */
	पंचांगp = 192 - (old_भाग * (192 - data->fan_preload[nr])
		     + new_भाग / 2) / new_भाग;
	data->fan_preload[nr] = clamp_val(पंचांगp, 0, 191);
	smsc47m1_ग_लिखो_value(data, SMSC47M1_REG_FAN_PRELOAD[nr],
			     data->fan_preload[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा smsc47m1_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = attr->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val < 0 || val > 255)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->pwm[nr] &= 0x81; /* Preserve additional bits */
	data->pwm[nr] |= PWM_TO_REG(val);
	smsc47m1_ग_लिखो_value(data, SMSC47M1_REG_PWM[nr],
			     data->pwm[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_en_store(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा smsc47m1_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val > 1)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->pwm[nr] &= 0xFE; /* preserve the other bits */
	data->pwm[nr] |= !val;
	smsc47m1_ग_लिखो_value(data, SMSC47M1_REG_PWM[nr],
			     data->pwm[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan1_min, fan_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan1_भाग, fan_भाग, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan1_alarm, fan_alarm, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm1, pwm, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm1_enable, pwm_en, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan2_min, fan_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan2_भाग, fan_भाग, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan2_alarm, fan_alarm, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm2, pwm, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_enable, pwm_en, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan3_input, fan, 2);
अटल SENSOR_DEVICE_ATTR_RW(fan3_min, fan_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(fan3_भाग, fan_भाग, 2);
अटल SENSOR_DEVICE_ATTR_RO(fan3_alarm, fan_alarm, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm3, pwm, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_enable, pwm_en, 2);

अटल DEVICE_ATTR_RO(alarms);

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute
			 *devattr, अक्षर *buf)
अणु
	काष्ठा smsc47m1_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", data->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल काष्ठा attribute *smsc47m1_attributes_fan1[] = अणु
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan1_भाग.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group smsc47m1_group_fan1 = अणु
	.attrs = smsc47m1_attributes_fan1,
पूर्ण;

अटल काष्ठा attribute *smsc47m1_attributes_fan2[] = अणु
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan2_भाग.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group smsc47m1_group_fan2 = अणु
	.attrs = smsc47m1_attributes_fan2,
पूर्ण;

अटल काष्ठा attribute *smsc47m1_attributes_fan3[] = अणु
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan3_min.dev_attr.attr,
	&sensor_dev_attr_fan3_भाग.dev_attr.attr,
	&sensor_dev_attr_fan3_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group smsc47m1_group_fan3 = अणु
	.attrs = smsc47m1_attributes_fan3,
पूर्ण;

अटल काष्ठा attribute *smsc47m1_attributes_pwm1[] = अणु
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm1_enable.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group smsc47m1_group_pwm1 = अणु
	.attrs = smsc47m1_attributes_pwm1,
पूर्ण;

अटल काष्ठा attribute *smsc47m1_attributes_pwm2[] = अणु
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&sensor_dev_attr_pwm2_enable.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group smsc47m1_group_pwm2 = अणु
	.attrs = smsc47m1_attributes_pwm2,
पूर्ण;

अटल काष्ठा attribute *smsc47m1_attributes_pwm3[] = अणु
	&sensor_dev_attr_pwm3.dev_attr.attr,
	&sensor_dev_attr_pwm3_enable.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group smsc47m1_group_pwm3 = अणु
	.attrs = smsc47m1_attributes_pwm3,
पूर्ण;

अटल काष्ठा attribute *smsc47m1_attributes[] = अणु
	&dev_attr_alarms.attr,
	&dev_attr_name.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group smsc47m1_group = अणु
	.attrs = smsc47m1_attributes,
पूर्ण;

अटल पूर्णांक __init smsc47m1_find(काष्ठा smsc47m1_sio_data *sio_data)
अणु
	u8 val;
	अचिन्हित लघु addr;
	पूर्णांक err;

	err = superio_enter();
	अगर (err)
		वापस err;

	val = क्रमce_id ? क्रमce_id : superio_inb(SUPERIO_REG_DEVID);

	/*
	 * SMSC LPC47M10x/LPC47M112/LPC47M13x (device id 0x59), LPC47M14x
	 * (device id 0x5F) and LPC47B27x (device id 0x51) have fan control.
	 * The LPC47M15x and LPC47M192 chips "with hardware monitoring block"
	 * can करो much more besides (device id 0x60).
	 * The LPC47M997 is unकरोcumented, but seems to be compatible with
	 * the LPC47M192, and has the same device id.
	 * The LPC47M292 (device id 0x6B) is somewhat compatible, but it
	 * supports a 3rd fan, and the pin configuration रेजिस्टरs are
	 * unक्रमtunately dअगरferent.
	 * The LPC47M233 has the same device id (0x6B) but is not compatible.
	 * We check the high bit of the device revision रेजिस्टर to
	 * dअगरferentiate them.
	 */
	चयन (val) अणु
	हाल 0x51:
		pr_info("Found SMSC LPC47B27x\n");
		sio_data->type = smsc47m1;
		अवरोध;
	हाल 0x59:
		pr_info("Found SMSC LPC47M10x/LPC47M112/LPC47M13x\n");
		sio_data->type = smsc47m1;
		अवरोध;
	हाल 0x5F:
		pr_info("Found SMSC LPC47M14x\n");
		sio_data->type = smsc47m1;
		अवरोध;
	हाल 0x60:
		pr_info("Found SMSC LPC47M15x/LPC47M192/LPC47M997\n");
		sio_data->type = smsc47m1;
		अवरोध;
	हाल 0x6B:
		अगर (superio_inb(SUPERIO_REG_DEVREV) & 0x80) अणु
			pr_debug("Found SMSC LPC47M233, unsupported\n");
			superio_निकास();
			वापस -ENODEV;
		पूर्ण

		pr_info("Found SMSC LPC47M292\n");
		sio_data->type = smsc47m2;
		अवरोध;
	शेष:
		superio_निकास();
		वापस -ENODEV;
	पूर्ण

	superio_select();
	addr = (superio_inb(SUPERIO_REG_BASE) << 8)
	      |  superio_inb(SUPERIO_REG_BASE + 1);
	अगर (addr == 0) अणु
		pr_info("Device address not set, will not use\n");
		superio_निकास();
		वापस -ENODEV;
	पूर्ण

	/*
	 * Enable only अगर address is set (needed at least on the
	 * Compaq Presario S4000NX)
	 */
	sio_data->activate = superio_inb(SUPERIO_REG_ACT);
	अगर ((sio_data->activate & 0x01) == 0) अणु
		pr_info("Enabling device\n");
		superio_outb(SUPERIO_REG_ACT, sio_data->activate | 0x01);
	पूर्ण

	superio_निकास();
	वापस addr;
पूर्ण

/* Restore device to its initial state */
अटल व्योम smsc47m1_restore(स्थिर काष्ठा smsc47m1_sio_data *sio_data)
अणु
	अगर ((sio_data->activate & 0x01) == 0) अणु
		अगर (!superio_enter()) अणु
			superio_select();
			pr_info("Disabling device\n");
			superio_outb(SUPERIO_REG_ACT, sio_data->activate);
			superio_निकास();
		पूर्ण अन्यथा अणु
			pr_warn("Failed to disable device\n");
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा CHECK		1
#घोषणा REQUEST		2

/*
 * This function can be used to:
 *  - test क्रम resource conflicts with ACPI
 *  - request the resources
 * We only allocate the I/O ports we really need, to minimize the risk of
 * conflicts with ACPI or with other drivers.
 */
अटल पूर्णांक __init smsc47m1_handle_resources(अचिन्हित लघु address,
					    क्रमागत chips type, पूर्णांक action,
					    काष्ठा device *dev)
अणु
	अटल स्थिर u8 ports_m1[] = अणु
		/* रेजिस्टर, region length */
		0x04, 1,
		0x33, 4,
		0x56, 7,
	पूर्ण;

	अटल स्थिर u8 ports_m2[] = अणु
		/* रेजिस्टर, region length */
		0x04, 1,
		0x09, 1,
		0x2c, 2,
		0x35, 4,
		0x56, 7,
		0x69, 4,
	पूर्ण;

	पूर्णांक i, ports_size, err;
	स्थिर u8 *ports;

	चयन (type) अणु
	हाल smsc47m1:
	शेष:
		ports = ports_m1;
		ports_size = ARRAY_SIZE(ports_m1);
		अवरोध;
	हाल smsc47m2:
		ports = ports_m2;
		ports_size = ARRAY_SIZE(ports_m2);
		अवरोध;
	पूर्ण

	क्रम (i = 0; i + 1 < ports_size; i += 2) अणु
		अचिन्हित लघु start = address + ports[i];
		अचिन्हित लघु len = ports[i + 1];

		चयन (action) अणु
		हाल CHECK:
			/* Only check क्रम conflicts */
			err = acpi_check_region(start, len, DRVNAME);
			अगर (err)
				वापस err;
			अवरोध;
		हाल REQUEST:
			/* Request the resources */
			अगर (!devm_request_region(dev, start, len, DRVNAME)) अणु
				dev_err(dev,
					"Region 0x%x-0x%x already in use!\n",
					start, start + len);
				वापस -EBUSY;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम smsc47m1_हटाओ_files(काष्ठा device *dev)
अणु
	sysfs_हटाओ_group(&dev->kobj, &smsc47m1_group);
	sysfs_हटाओ_group(&dev->kobj, &smsc47m1_group_fan1);
	sysfs_हटाओ_group(&dev->kobj, &smsc47m1_group_fan2);
	sysfs_हटाओ_group(&dev->kobj, &smsc47m1_group_fan3);
	sysfs_हटाओ_group(&dev->kobj, &smsc47m1_group_pwm1);
	sysfs_हटाओ_group(&dev->kobj, &smsc47m1_group_pwm2);
	sysfs_हटाओ_group(&dev->kobj, &smsc47m1_group_pwm3);
पूर्ण

अटल पूर्णांक __init smsc47m1_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा smsc47m1_sio_data *sio_data = dev_get_platdata(dev);
	काष्ठा smsc47m1_data *data;
	काष्ठा resource *res;
	पूर्णांक err;
	पूर्णांक fan1, fan2, fan3, pwm1, pwm2, pwm3;

	अटल स्थिर अक्षर * स्थिर names[] = अणु
		"smsc47m1",
		"smsc47m2",
	पूर्ण;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	err = smsc47m1_handle_resources(res->start, sio_data->type,
					REQUEST, dev);
	अगर (err < 0)
		वापस err;

	data = devm_kzalloc(dev, माप(काष्ठा smsc47m1_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->addr = res->start;
	data->type = sio_data->type;
	data->name = names[sio_data->type];
	mutex_init(&data->update_lock);
	platक्रमm_set_drvdata(pdev, data);

	/*
	 * If no function is properly configured, there's no poपूर्णांक in
	 * actually रेजिस्टरing the chip.
	 */
	pwm1 = (smsc47m1_पढ़ो_value(data, SMSC47M1_REG_PPIN(0)) & 0x05)
	       == 0x04;
	pwm2 = (smsc47m1_पढ़ो_value(data, SMSC47M1_REG_PPIN(1)) & 0x05)
	       == 0x04;
	अगर (data->type == smsc47m2) अणु
		fan1 = (smsc47m1_पढ़ो_value(data, SMSC47M2_REG_TPIN1)
			& 0x0d) == 0x09;
		fan2 = (smsc47m1_पढ़ो_value(data, SMSC47M2_REG_TPIN2)
			& 0x0d) == 0x09;
		fan3 = (smsc47m1_पढ़ो_value(data, SMSC47M2_REG_TPIN3)
			& 0x0d) == 0x0d;
		pwm3 = (smsc47m1_पढ़ो_value(data, SMSC47M2_REG_PPIN3)
			& 0x0d) == 0x08;
	पूर्ण अन्यथा अणु
		fan1 = (smsc47m1_पढ़ो_value(data, SMSC47M1_REG_TPIN(0))
			& 0x05) == 0x05;
		fan2 = (smsc47m1_पढ़ो_value(data, SMSC47M1_REG_TPIN(1))
			& 0x05) == 0x05;
		fan3 = 0;
		pwm3 = 0;
	पूर्ण
	अगर (!(fan1 || fan2 || fan3 || pwm1 || pwm2 || pwm3)) अणु
		dev_warn(dev, "Device not configured, will not use\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * Some values (fan min, घड़ी भागiders, pwm रेजिस्टरs) may be
	 * needed beक्रमe any update is triggered, so we better पढ़ो them
	 * at least once here. We करोn't usually करो it that way, but in
	 * this particular हाल, manually पढ़ोing 5 रेजिस्टरs out of 8
	 * करोesn't make much sense and we're better using the existing
	 * function.
	 */
	smsc47m1_update_device(dev, 1);

	/* Register sysfs hooks */
	अगर (fan1) अणु
		err = sysfs_create_group(&dev->kobj,
					 &smsc47m1_group_fan1);
		अगर (err)
			जाओ error_हटाओ_files;
	पूर्ण अन्यथा
		dev_dbg(dev, "Fan 1 not enabled by hardware, skipping\n");

	अगर (fan2) अणु
		err = sysfs_create_group(&dev->kobj,
					 &smsc47m1_group_fan2);
		अगर (err)
			जाओ error_हटाओ_files;
	पूर्ण अन्यथा
		dev_dbg(dev, "Fan 2 not enabled by hardware, skipping\n");

	अगर (fan3) अणु
		err = sysfs_create_group(&dev->kobj,
					 &smsc47m1_group_fan3);
		अगर (err)
			जाओ error_हटाओ_files;
	पूर्ण अन्यथा अगर (data->type == smsc47m2)
		dev_dbg(dev, "Fan 3 not enabled by hardware, skipping\n");

	अगर (pwm1) अणु
		err = sysfs_create_group(&dev->kobj,
					 &smsc47m1_group_pwm1);
		अगर (err)
			जाओ error_हटाओ_files;
	पूर्ण अन्यथा
		dev_dbg(dev, "PWM 1 not enabled by hardware, skipping\n");

	अगर (pwm2) अणु
		err = sysfs_create_group(&dev->kobj,
					 &smsc47m1_group_pwm2);
		अगर (err)
			जाओ error_हटाओ_files;
	पूर्ण अन्यथा
		dev_dbg(dev, "PWM 2 not enabled by hardware, skipping\n");

	अगर (pwm3) अणु
		err = sysfs_create_group(&dev->kobj,
					 &smsc47m1_group_pwm3);
		अगर (err)
			जाओ error_हटाओ_files;
	पूर्ण अन्यथा अगर (data->type == smsc47m2)
		dev_dbg(dev, "PWM 3 not enabled by hardware, skipping\n");

	err = sysfs_create_group(&dev->kobj, &smsc47m1_group);
	अगर (err)
		जाओ error_हटाओ_files;

	data->hwmon_dev = hwmon_device_रेजिस्टर(dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		जाओ error_हटाओ_files;
	पूर्ण

	वापस 0;

error_हटाओ_files:
	smsc47m1_हटाओ_files(dev);
	वापस err;
पूर्ण

अटल पूर्णांक __निकास smsc47m1_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा smsc47m1_data *data = platक्रमm_get_drvdata(pdev);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	smsc47m1_हटाओ_files(&pdev->dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver smsc47m1_driver = अणु
	.driver = अणु
		.name	= DRVNAME,
	पूर्ण,
	.हटाओ		= __निकास_p(smsc47m1_हटाओ),
पूर्ण;

अटल पूर्णांक __init smsc47m1_device_add(अचिन्हित लघु address,
				      स्थिर काष्ठा smsc47m1_sio_data *sio_data)
अणु
	काष्ठा resource res = अणु
		.start	= address,
		.end	= address + SMSC_EXTENT - 1,
		.name	= DRVNAME,
		.flags	= IORESOURCE_IO,
	पूर्ण;
	पूर्णांक err;

	err = smsc47m1_handle_resources(address, sio_data->type, CHECK, शून्य);
	अगर (err)
		जाओ निकास;

	pdev = platक्रमm_device_alloc(DRVNAME, address);
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

	err = platक्रमm_device_add_data(pdev, sio_data,
				       माप(काष्ठा smsc47m1_sio_data));
	अगर (err) अणु
		pr_err("Platform data allocation failed\n");
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

अटल पूर्णांक __init sm_smsc47m1_init(व्योम)
अणु
	पूर्णांक err;
	अचिन्हित लघु address;
	काष्ठा smsc47m1_sio_data sio_data;

	err = smsc47m1_find(&sio_data);
	अगर (err < 0)
		वापस err;
	address = err;

	/* Sets global pdev as a side effect */
	err = smsc47m1_device_add(address, &sio_data);
	अगर (err)
		वापस err;

	err = platक्रमm_driver_probe(&smsc47m1_driver, smsc47m1_probe);
	अगर (err)
		जाओ निकास_device;

	वापस 0;

निकास_device:
	platक्रमm_device_unरेजिस्टर(pdev);
	smsc47m1_restore(&sio_data);
	वापस err;
पूर्ण

अटल व्योम __निकास sm_smsc47m1_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&smsc47m1_driver);
	smsc47m1_restore(dev_get_platdata(&pdev->dev));
	platक्रमm_device_unरेजिस्टर(pdev);
पूर्ण

MODULE_AUTHOR("Mark D. Studebaker <mdsxyz123@yahoo.com>");
MODULE_DESCRIPTION("SMSC LPC47M1xx fan sensors driver");
MODULE_LICENSE("GPL");

module_init(sm_smsc47m1_init);
module_निकास(sm_smsc47m1_निकास);
