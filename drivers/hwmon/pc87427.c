<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  pc87427.c - hardware monitoring driver क्रम the
 *              National Semiconductor PC87427 Super-I/O chip
 *  Copyright (C) 2006, 2008, 2010  Jean Delvare <jdelvare@suse.de>
 *
 *  Supports the following chips:
 *
 *  Chip        #vin    #fan    #pwm    #temp   devid
 *  PC87427     -       8       4       6       0xF2
 *
 *  This driver assumes that no more than one chip is present.
 *  Only fans are fully supported so far. Temperatures are in पढ़ो-only
 *  mode, and voltages aren't supported at all.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/ioport.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>

अटल अचिन्हित लघु क्रमce_id;
module_param(क्रमce_id, uलघु, 0);
MODULE_PARM_DESC(क्रमce_id, "Override the detected device ID");

अटल काष्ठा platक्रमm_device *pdev;

#घोषणा DRVNAME "pc87427"

/*
 * The lock mutex protects both the I/O accesses (needed because the
 * device is using banked रेजिस्टरs) and the रेजिस्टर cache (needed to keep
 * the data in the रेजिस्टरs and the cache in sync at any समय).
 */
काष्ठा pc87427_data अणु
	काष्ठा device *hwmon_dev;
	काष्ठा mutex lock;
	पूर्णांक address[2];
	स्थिर अक्षर *name;

	अचिन्हित दीर्घ last_updated;	/* in jअगरfies */
	u8 fan_enabled;			/* bit vector */
	u16 fan[8];			/* रेजिस्टर values */
	u16 fan_min[8];			/* रेजिस्टर values */
	u8 fan_status[8];		/* रेजिस्टर values */

	u8 pwm_enabled;			/* bit vector */
	u8 pwm_स्वतः_ok;			/* bit vector */
	u8 pwm_enable[4];		/* रेजिस्टर values */
	u8 pwm[4];			/* रेजिस्टर values */

	u8 temp_enabled;		/* bit vector */
	s16 temp[6];			/* रेजिस्टर values */
	s8 temp_min[6];			/* रेजिस्टर values */
	s8 temp_max[6];			/* रेजिस्टर values */
	s8 temp_crit[6];		/* रेजिस्टर values */
	u8 temp_status[6];		/* रेजिस्टर values */
	u8 temp_type[6];		/* रेजिस्टर values */
पूर्ण;

काष्ठा pc87427_sio_data अणु
	अचिन्हित लघु address[2];
	u8 has_fanin;
	u8 has_fanout;
पूर्ण;

/*
 * Super-I/O रेजिस्टरs and operations
 */

#घोषणा SIOREG_LDSEL	0x07	/* Logical device select */
#घोषणा SIOREG_DEVID	0x20	/* Device ID */
#घोषणा SIOREG_CF2	0x22	/* Configuration 2 */
#घोषणा SIOREG_CF3	0x23	/* Configuration 3 */
#घोषणा SIOREG_CF4	0x24	/* Configuration 4 */
#घोषणा SIOREG_CF5	0x25	/* Configuration 5 */
#घोषणा SIOREG_CFB	0x2B	/* Configuration B */
#घोषणा SIOREG_CFC	0x2C	/* Configuration C */
#घोषणा SIOREG_CFD	0x2D	/* Configuration D */
#घोषणा SIOREG_ACT	0x30	/* Device activation */
#घोषणा SIOREG_MAP	0x50	/* I/O or memory mapping */
#घोषणा SIOREG_IOBASE	0x60	/* I/O base address */

अटल स्थिर u8 logdev[2] = अणु 0x09, 0x14 पूर्ण;
अटल स्थिर अक्षर *logdev_str[2] = अणु DRVNAME " FMC", DRVNAME " HMC" पूर्ण;
#घोषणा LD_FAN		0
#घोषणा LD_IN		1
#घोषणा LD_TEMP		1

अटल अंतरभूत पूर्णांक superio_enter(पूर्णांक sioaddr)
अणु
	अगर (!request_muxed_region(sioaddr, 2, DRVNAME))
		वापस -EBUSY;
	वापस 0;
पूर्ण

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
	release_region(sioaddr, 2);
पूर्ण

/*
 * Logical devices
 */

#घोषणा REGION_LENGTH		32
#घोषणा PC87427_REG_BANK	0x0f
#घोषणा BANK_FM(nr)		(nr)
#घोषणा BANK_FT(nr)		(0x08 + (nr))
#घोषणा BANK_FC(nr)		(0x10 + (nr) * 2)
#घोषणा BANK_TM(nr)		(nr)
#घोषणा BANK_VM(nr)		(0x08 + (nr))

/*
 * I/O access functions
 */

/* ldi is the logical device index */
अटल अंतरभूत पूर्णांक pc87427_पढ़ो8(काष्ठा pc87427_data *data, u8 ldi, u8 reg)
अणु
	वापस inb(data->address[ldi] + reg);
पूर्ण

/* Must be called with data->lock held, except during init */
अटल अंतरभूत पूर्णांक pc87427_पढ़ो8_bank(काष्ठा pc87427_data *data, u8 ldi,
				     u8 bank, u8 reg)
अणु
	outb(bank, data->address[ldi] + PC87427_REG_BANK);
	वापस inb(data->address[ldi] + reg);
पूर्ण

/* Must be called with data->lock held, except during init */
अटल अंतरभूत व्योम pc87427_ग_लिखो8_bank(काष्ठा pc87427_data *data, u8 ldi,
				       u8 bank, u8 reg, u8 value)
अणु
	outb(bank, data->address[ldi] + PC87427_REG_BANK);
	outb(value, data->address[ldi] + reg);
पूर्ण

/*
 * Fan रेजिस्टरs and conversions
 */

/* fan data रेजिस्टरs are 16-bit wide */
#घोषणा PC87427_REG_FAN			0x12
#घोषणा PC87427_REG_FAN_MIN		0x14
#घोषणा PC87427_REG_FAN_STATUS		0x10

#घोषणा FAN_STATUS_STALL		(1 << 3)
#घोषणा FAN_STATUS_LOSPD		(1 << 1)
#घोषणा FAN_STATUS_MONEN		(1 << 0)

/*
 * Dedicated function to पढ़ो all रेजिस्टरs related to a given fan input.
 * This saves us quite a few locks and bank selections.
 * Must be called with data->lock held.
 * nr is from 0 to 7
 */
अटल व्योम pc87427_पढ़ोall_fan(काष्ठा pc87427_data *data, u8 nr)
अणु
	पूर्णांक iobase = data->address[LD_FAN];

	outb(BANK_FM(nr), iobase + PC87427_REG_BANK);
	data->fan[nr] = inw(iobase + PC87427_REG_FAN);
	data->fan_min[nr] = inw(iobase + PC87427_REG_FAN_MIN);
	data->fan_status[nr] = inb(iobase + PC87427_REG_FAN_STATUS);
	/* Clear fan alarm bits */
	outb(data->fan_status[nr], iobase + PC87427_REG_FAN_STATUS);
पूर्ण

/*
 * The 2 LSB of fan speed रेजिस्टरs are used क्रम something dअगरferent.
 * The actual 2 LSB of the measurements are not available.
 */
अटल अंतरभूत अचिन्हित दीर्घ fan_from_reg(u16 reg)
अणु
	reg &= 0xfffc;
	अगर (reg == 0x0000 || reg == 0xfffc)
		वापस 0;
	वापस 5400000UL / reg;
पूर्ण

/* The 2 LSB of the fan speed limit रेजिस्टरs are not signअगरicant. */
अटल अंतरभूत u16 fan_to_reg(अचिन्हित दीर्घ val)
अणु
	अगर (val < 83UL)
		वापस 0xffff;
	अगर (val >= 1350000UL)
		वापस 0x0004;
	वापस ((1350000UL + val / 2) / val) << 2;
पूर्ण

/*
 * PWM रेजिस्टरs and conversions
 */

#घोषणा PC87427_REG_PWM_ENABLE		0x10
#घोषणा PC87427_REG_PWM_DUTY		0x12

#घोषणा PWM_ENABLE_MODE_MASK		(7 << 4)
#घोषणा PWM_ENABLE_CTLEN		(1 << 0)

#घोषणा PWM_MODE_MANUAL			(0 << 4)
#घोषणा PWM_MODE_AUTO			(1 << 4)
#घोषणा PWM_MODE_OFF			(2 << 4)
#घोषणा PWM_MODE_ON			(7 << 4)

/*
 * Dedicated function to पढ़ो all रेजिस्टरs related to a given PWM output.
 * This saves us quite a few locks and bank selections.
 * Must be called with data->lock held.
 * nr is from 0 to 3
 */
अटल व्योम pc87427_पढ़ोall_pwm(काष्ठा pc87427_data *data, u8 nr)
अणु
	पूर्णांक iobase = data->address[LD_FAN];

	outb(BANK_FC(nr), iobase + PC87427_REG_BANK);
	data->pwm_enable[nr] = inb(iobase + PC87427_REG_PWM_ENABLE);
	data->pwm[nr] = inb(iobase + PC87427_REG_PWM_DUTY);
पूर्ण

अटल अंतरभूत पूर्णांक pwm_enable_from_reg(u8 reg)
अणु
	चयन (reg & PWM_ENABLE_MODE_MASK) अणु
	हाल PWM_MODE_ON:
		वापस 0;
	हाल PWM_MODE_MANUAL:
	हाल PWM_MODE_OFF:
		वापस 1;
	हाल PWM_MODE_AUTO:
		वापस 2;
	शेष:
		वापस -EPROTO;
	पूर्ण
पूर्ण

अटल अंतरभूत u8 pwm_enable_to_reg(अचिन्हित दीर्घ val, u8 pwmval)
अणु
	चयन (val) अणु
	शेष:
		वापस PWM_MODE_ON;
	हाल 1:
		वापस pwmval ? PWM_MODE_MANUAL : PWM_MODE_OFF;
	हाल 2:
		वापस PWM_MODE_AUTO;
	पूर्ण
पूर्ण

/*
 * Temperature रेजिस्टरs and conversions
 */

#घोषणा PC87427_REG_TEMP_STATUS		0x10
#घोषणा PC87427_REG_TEMP		0x14
#घोषणा PC87427_REG_TEMP_MAX		0x18
#घोषणा PC87427_REG_TEMP_MIN		0x19
#घोषणा PC87427_REG_TEMP_CRIT		0x1a
#घोषणा PC87427_REG_TEMP_TYPE		0x1d

#घोषणा TEMP_STATUS_CHANEN		(1 << 0)
#घोषणा TEMP_STATUS_LOWFLG		(1 << 1)
#घोषणा TEMP_STATUS_HIGHFLG		(1 << 2)
#घोषणा TEMP_STATUS_CRITFLG		(1 << 3)
#घोषणा TEMP_STATUS_SENSERR		(1 << 5)
#घोषणा TEMP_TYPE_MASK			(3 << 5)

#घोषणा TEMP_TYPE_THERMISTOR		(1 << 5)
#घोषणा TEMP_TYPE_REMOTE_DIODE		(2 << 5)
#घोषणा TEMP_TYPE_LOCAL_DIODE		(3 << 5)

/*
 * Dedicated function to पढ़ो all रेजिस्टरs related to a given temperature
 * input. This saves us quite a few locks and bank selections.
 * Must be called with data->lock held.
 * nr is from 0 to 5
 */
अटल व्योम pc87427_पढ़ोall_temp(काष्ठा pc87427_data *data, u8 nr)
अणु
	पूर्णांक iobase = data->address[LD_TEMP];

	outb(BANK_TM(nr), iobase + PC87427_REG_BANK);
	data->temp[nr] = le16_to_cpu(inw(iobase + PC87427_REG_TEMP));
	data->temp_max[nr] = inb(iobase + PC87427_REG_TEMP_MAX);
	data->temp_min[nr] = inb(iobase + PC87427_REG_TEMP_MIN);
	data->temp_crit[nr] = inb(iobase + PC87427_REG_TEMP_CRIT);
	data->temp_type[nr] = inb(iobase + PC87427_REG_TEMP_TYPE);
	data->temp_status[nr] = inb(iobase + PC87427_REG_TEMP_STATUS);
	/* Clear fan alarm bits */
	outb(data->temp_status[nr], iobase + PC87427_REG_TEMP_STATUS);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक temp_type_from_reg(u8 reg)
अणु
	चयन (reg & TEMP_TYPE_MASK) अणु
	हाल TEMP_TYPE_THERMISTOR:
		वापस 4;
	हाल TEMP_TYPE_REMOTE_DIODE:
	हाल TEMP_TYPE_LOCAL_DIODE:
		वापस 3;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * We assume 8-bit thermal sensors; 9-bit thermal sensors are possible
 * too, but I have no idea how to figure out when they are used.
 */
अटल अंतरभूत दीर्घ temp_from_reg(s16 reg)
अणु
	वापस reg * 1000 / 256;
पूर्ण

अटल अंतरभूत दीर्घ temp_from_reg8(s8 reg)
अणु
	वापस reg * 1000;
पूर्ण

/*
 * Data पूर्णांकerface
 */

अटल काष्ठा pc87427_data *pc87427_update_device(काष्ठा device *dev)
अणु
	काष्ठा pc87427_data *data = dev_get_drvdata(dev);
	पूर्णांक i;

	mutex_lock(&data->lock);
	अगर (!समय_after(jअगरfies, data->last_updated + HZ)
	 && data->last_updated)
		जाओ करोne;

	/* Fans */
	क्रम (i = 0; i < 8; i++) अणु
		अगर (!(data->fan_enabled & (1 << i)))
			जारी;
		pc87427_पढ़ोall_fan(data, i);
	पूर्ण

	/* PWM outमाला_दो */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (!(data->pwm_enabled & (1 << i)))
			जारी;
		pc87427_पढ़ोall_pwm(data, i);
	पूर्ण

	/* Temperature channels */
	क्रम (i = 0; i < 6; i++) अणु
		अगर (!(data->temp_enabled & (1 << i)))
			जारी;
		pc87427_पढ़ोall_temp(data, i);
	पूर्ण

	data->last_updated = jअगरfies;

करोne:
	mutex_unlock(&data->lock);
	वापस data;
पूर्ण

अटल sमाप_प्रकार fan_input_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pc87427_data *data = pc87427_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%lu\n", fan_from_reg(data->fan[nr]));
पूर्ण

अटल sमाप_प्रकार fan_min_show(काष्ठा device *dev,
			    काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pc87427_data *data = pc87427_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%lu\n", fan_from_reg(data->fan_min[nr]));
पूर्ण

अटल sमाप_प्रकार fan_alarm_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pc87427_data *data = pc87427_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%d\n", !!(data->fan_status[nr]
				       & FAN_STATUS_LOSPD));
पूर्ण

अटल sमाप_प्रकार fan_fault_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pc87427_data *data = pc87427_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%d\n", !!(data->fan_status[nr]
				       & FAN_STATUS_STALL));
पूर्ण

अटल sमाप_प्रकार fan_min_store(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pc87427_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	अचिन्हित दीर्घ val;
	पूर्णांक iobase = data->address[LD_FAN];

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	mutex_lock(&data->lock);
	outb(BANK_FM(nr), iobase + PC87427_REG_BANK);
	/*
	 * The low speed limit रेजिस्टरs are पढ़ो-only जबतक monitoring
	 * is enabled, so we have to disable monitoring, then change the
	 * limit, and finally enable monitoring again.
	 */
	outb(0, iobase + PC87427_REG_FAN_STATUS);
	data->fan_min[nr] = fan_to_reg(val);
	outw(data->fan_min[nr], iobase + PC87427_REG_FAN_MIN);
	outb(FAN_STATUS_MONEN, iobase + PC87427_REG_FAN_STATUS);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan_input, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan_input, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan3_input, fan_input, 2);
अटल SENSOR_DEVICE_ATTR_RO(fan4_input, fan_input, 3);
अटल SENSOR_DEVICE_ATTR_RO(fan5_input, fan_input, 4);
अटल SENSOR_DEVICE_ATTR_RO(fan6_input, fan_input, 5);
अटल SENSOR_DEVICE_ATTR_RO(fan7_input, fan_input, 6);
अटल SENSOR_DEVICE_ATTR_RO(fan8_input, fan_input, 7);

अटल SENSOR_DEVICE_ATTR_RW(fan1_min, fan_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_min, fan_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan3_min, fan_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(fan4_min, fan_min, 3);
अटल SENSOR_DEVICE_ATTR_RW(fan5_min, fan_min, 4);
अटल SENSOR_DEVICE_ATTR_RW(fan6_min, fan_min, 5);
अटल SENSOR_DEVICE_ATTR_RW(fan7_min, fan_min, 6);
अटल SENSOR_DEVICE_ATTR_RW(fan8_min, fan_min, 7);

अटल SENSOR_DEVICE_ATTR_RO(fan1_alarm, fan_alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_alarm, fan_alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan3_alarm, fan_alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(fan4_alarm, fan_alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(fan5_alarm, fan_alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(fan6_alarm, fan_alarm, 5);
अटल SENSOR_DEVICE_ATTR_RO(fan7_alarm, fan_alarm, 6);
अटल SENSOR_DEVICE_ATTR_RO(fan8_alarm, fan_alarm, 7);

अटल SENSOR_DEVICE_ATTR_RO(fan1_fault, fan_fault, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_fault, fan_fault, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan3_fault, fan_fault, 2);
अटल SENSOR_DEVICE_ATTR_RO(fan4_fault, fan_fault, 3);
अटल SENSOR_DEVICE_ATTR_RO(fan5_fault, fan_fault, 4);
अटल SENSOR_DEVICE_ATTR_RO(fan6_fault, fan_fault, 5);
अटल SENSOR_DEVICE_ATTR_RO(fan7_fault, fan_fault, 6);
अटल SENSOR_DEVICE_ATTR_RO(fan8_fault, fan_fault, 7);

अटल काष्ठा attribute *pc87427_attributes_fan[8][5] = अणु
	अणु
		&sensor_dev_attr_fan1_input.dev_attr.attr,
		&sensor_dev_attr_fan1_min.dev_attr.attr,
		&sensor_dev_attr_fan1_alarm.dev_attr.attr,
		&sensor_dev_attr_fan1_fault.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_fan2_input.dev_attr.attr,
		&sensor_dev_attr_fan2_min.dev_attr.attr,
		&sensor_dev_attr_fan2_alarm.dev_attr.attr,
		&sensor_dev_attr_fan2_fault.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_fan3_input.dev_attr.attr,
		&sensor_dev_attr_fan3_min.dev_attr.attr,
		&sensor_dev_attr_fan3_alarm.dev_attr.attr,
		&sensor_dev_attr_fan3_fault.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_fan4_input.dev_attr.attr,
		&sensor_dev_attr_fan4_min.dev_attr.attr,
		&sensor_dev_attr_fan4_alarm.dev_attr.attr,
		&sensor_dev_attr_fan4_fault.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_fan5_input.dev_attr.attr,
		&sensor_dev_attr_fan5_min.dev_attr.attr,
		&sensor_dev_attr_fan5_alarm.dev_attr.attr,
		&sensor_dev_attr_fan5_fault.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_fan6_input.dev_attr.attr,
		&sensor_dev_attr_fan6_min.dev_attr.attr,
		&sensor_dev_attr_fan6_alarm.dev_attr.attr,
		&sensor_dev_attr_fan6_fault.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_fan7_input.dev_attr.attr,
		&sensor_dev_attr_fan7_min.dev_attr.attr,
		&sensor_dev_attr_fan7_alarm.dev_attr.attr,
		&sensor_dev_attr_fan7_fault.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_fan8_input.dev_attr.attr,
		&sensor_dev_attr_fan8_min.dev_attr.attr,
		&sensor_dev_attr_fan8_alarm.dev_attr.attr,
		&sensor_dev_attr_fan8_fault.dev_attr.attr,
		शून्य
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा attribute_group pc87427_group_fan[8] = अणु
	अणु .attrs = pc87427_attributes_fan[0] पूर्ण,
	अणु .attrs = pc87427_attributes_fan[1] पूर्ण,
	अणु .attrs = pc87427_attributes_fan[2] पूर्ण,
	अणु .attrs = pc87427_attributes_fan[3] पूर्ण,
	अणु .attrs = pc87427_attributes_fan[4] पूर्ण,
	अणु .attrs = pc87427_attributes_fan[5] पूर्ण,
	अणु .attrs = pc87427_attributes_fan[6] पूर्ण,
	अणु .attrs = pc87427_attributes_fan[7] पूर्ण,
पूर्ण;

/*
 * Must be called with data->lock held and pc87427_पढ़ोall_pwm() freshly
 * called
 */
अटल व्योम update_pwm_enable(काष्ठा pc87427_data *data, पूर्णांक nr, u8 mode)
अणु
	पूर्णांक iobase = data->address[LD_FAN];
	data->pwm_enable[nr] &= ~PWM_ENABLE_MODE_MASK;
	data->pwm_enable[nr] |= mode;
	outb(data->pwm_enable[nr], iobase + PC87427_REG_PWM_ENABLE);
पूर्ण

अटल sमाप_प्रकार pwm_enable_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pc87427_data *data = pc87427_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	पूर्णांक pwm_enable;

	pwm_enable = pwm_enable_from_reg(data->pwm_enable[nr]);
	अगर (pwm_enable < 0)
		वापस pwm_enable;
	वापस प्र_लिखो(buf, "%d\n", pwm_enable);
पूर्ण

अटल sमाप_प्रकार pwm_enable_store(काष्ठा device *dev,
				काष्ठा device_attribute *devattr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pc87427_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0 || val > 2)
		वापस -EINVAL;
	/* Can't go to automatic mode if it isn't configured */
	अगर (val == 2 && !(data->pwm_स्वतः_ok & (1 << nr)))
		वापस -EINVAL;

	mutex_lock(&data->lock);
	pc87427_पढ़ोall_pwm(data, nr);
	update_pwm_enable(data, nr, pwm_enable_to_reg(val, data->pwm[nr]));
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा pc87427_data *data = pc87427_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)data->pwm[nr]);
पूर्ण

अटल sमाप_प्रकार pwm_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pc87427_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;
	अचिन्हित दीर्घ val;
	पूर्णांक iobase = data->address[LD_FAN];
	u8 mode;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0 || val > 0xff)
		वापस -EINVAL;

	mutex_lock(&data->lock);
	pc87427_पढ़ोall_pwm(data, nr);
	mode = data->pwm_enable[nr] & PWM_ENABLE_MODE_MASK;
	अगर (mode != PWM_MODE_MANUAL && mode != PWM_MODE_OFF) अणु
		dev_notice(dev,
			   "Can't set PWM%d duty cycle while not in manual mode\n",
			   nr + 1);
		mutex_unlock(&data->lock);
		वापस -EPERM;
	पूर्ण

	/* We may have to change the mode */
	अगर (mode == PWM_MODE_MANUAL && val == 0) अणु
		/* Transition from Manual to Off */
		update_pwm_enable(data, nr, PWM_MODE_OFF);
		mode = PWM_MODE_OFF;
		dev_dbg(dev, "Switching PWM%d from %s to %s\n", nr + 1,
			"manual", "off");
	पूर्ण अन्यथा अगर (mode == PWM_MODE_OFF && val != 0) अणु
		/* Transition from Off to Manual */
		update_pwm_enable(data, nr, PWM_MODE_MANUAL);
		mode = PWM_MODE_MANUAL;
		dev_dbg(dev, "Switching PWM%d from %s to %s\n", nr + 1,
			"off", "manual");
	पूर्ण

	data->pwm[nr] = val;
	अगर (mode == PWM_MODE_MANUAL)
		outb(val, iobase + PC87427_REG_PWM_DUTY);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(pwm1_enable, pwm_enable, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2_enable, pwm_enable, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3_enable, pwm_enable, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm4_enable, pwm_enable, 3);

अटल SENSOR_DEVICE_ATTR_RW(pwm1, pwm, 0);
अटल SENSOR_DEVICE_ATTR_RW(pwm2, pwm, 1);
अटल SENSOR_DEVICE_ATTR_RW(pwm3, pwm, 2);
अटल SENSOR_DEVICE_ATTR_RW(pwm4, pwm, 3);

अटल काष्ठा attribute *pc87427_attributes_pwm[4][3] = अणु
	अणु
		&sensor_dev_attr_pwm1_enable.dev_attr.attr,
		&sensor_dev_attr_pwm1.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_pwm2_enable.dev_attr.attr,
		&sensor_dev_attr_pwm2.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_pwm3_enable.dev_attr.attr,
		&sensor_dev_attr_pwm3.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_pwm4_enable.dev_attr.attr,
		&sensor_dev_attr_pwm4.dev_attr.attr,
		शून्य
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा attribute_group pc87427_group_pwm[4] = अणु
	अणु .attrs = pc87427_attributes_pwm[0] पूर्ण,
	अणु .attrs = pc87427_attributes_pwm[1] पूर्ण,
	अणु .attrs = pc87427_attributes_pwm[2] पूर्ण,
	अणु .attrs = pc87427_attributes_pwm[3] पूर्ण,
पूर्ण;

अटल sमाप_प्रकार temp_input_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pc87427_data *data = pc87427_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%ld\n", temp_from_reg(data->temp[nr]));
पूर्ण

अटल sमाप_प्रकार temp_min_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pc87427_data *data = pc87427_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%ld\n", temp_from_reg8(data->temp_min[nr]));
पूर्ण

अटल sमाप_प्रकार temp_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pc87427_data *data = pc87427_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%ld\n", temp_from_reg8(data->temp_max[nr]));
पूर्ण

अटल sमाप_प्रकार temp_crit_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pc87427_data *data = pc87427_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%ld\n", temp_from_reg8(data->temp_crit[nr]));
पूर्ण

अटल sमाप_प्रकार temp_type_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pc87427_data *data = pc87427_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%u\n", temp_type_from_reg(data->temp_type[nr]));
पूर्ण

अटल sमाप_प्रकार temp_min_alarm_show(काष्ठा device *dev,
				   काष्ठा device_attribute *devattr,
				   अक्षर *buf)
अणु
	काष्ठा pc87427_data *data = pc87427_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%d\n", !!(data->temp_status[nr]
				       & TEMP_STATUS_LOWFLG));
पूर्ण

अटल sमाप_प्रकार temp_max_alarm_show(काष्ठा device *dev,
				   काष्ठा device_attribute *devattr,
				   अक्षर *buf)
अणु
	काष्ठा pc87427_data *data = pc87427_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%d\n", !!(data->temp_status[nr]
				       & TEMP_STATUS_HIGHFLG));
पूर्ण

अटल sमाप_प्रकार temp_crit_alarm_show(काष्ठा device *dev,
				    काष्ठा device_attribute *devattr,
				    अक्षर *buf)
अणु
	काष्ठा pc87427_data *data = pc87427_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%d\n", !!(data->temp_status[nr]
				       & TEMP_STATUS_CRITFLG));
पूर्ण

अटल sमाप_प्रकार temp_fault_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा pc87427_data *data = pc87427_update_device(dev);
	पूर्णांक nr = to_sensor_dev_attr(devattr)->index;

	वापस प्र_लिखो(buf, "%d\n", !!(data->temp_status[nr]
				       & TEMP_STATUS_SENSERR));
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp_input, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp_input, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp_input, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_input, temp_input, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp5_input, temp_input, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp6_input, temp_input, 5);

अटल SENSOR_DEVICE_ATTR_RO(temp1_min, temp_min, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_min, temp_min, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_min, temp_min, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_min, temp_min, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp5_min, temp_min, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp6_min, temp_min, 5);

अटल SENSOR_DEVICE_ATTR_RO(temp1_max, temp_max, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_max, temp_max, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_max, temp_max, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_max, temp_max, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp5_max, temp_max, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp6_max, temp_max, 5);

अटल SENSOR_DEVICE_ATTR_RO(temp1_crit, temp_crit, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_crit, temp_crit, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_crit, temp_crit, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_crit, temp_crit, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp5_crit, temp_crit, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp6_crit, temp_crit, 5);

अटल SENSOR_DEVICE_ATTR_RO(temp1_type, temp_type, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_type, temp_type, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_type, temp_type, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_type, temp_type, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp5_type, temp_type, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp6_type, temp_type, 5);

अटल SENSOR_DEVICE_ATTR_RO(temp1_min_alarm, temp_min_alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_min_alarm, temp_min_alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_min_alarm, temp_min_alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_min_alarm, temp_min_alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp5_min_alarm, temp_min_alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp6_min_alarm, temp_min_alarm, 5);

अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, temp_max_alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_max_alarm, temp_max_alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_max_alarm, temp_max_alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_max_alarm, temp_max_alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp5_max_alarm, temp_max_alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp6_max_alarm, temp_max_alarm, 5);

अटल SENSOR_DEVICE_ATTR_RO(temp1_crit_alarm, temp_crit_alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_crit_alarm, temp_crit_alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_crit_alarm, temp_crit_alarm, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_crit_alarm, temp_crit_alarm, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp5_crit_alarm, temp_crit_alarm, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp6_crit_alarm, temp_crit_alarm, 5);

अटल SENSOR_DEVICE_ATTR_RO(temp1_fault, temp_fault, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_fault, temp_fault, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_fault, temp_fault, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_fault, temp_fault, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp5_fault, temp_fault, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp6_fault, temp_fault, 5);

अटल काष्ठा attribute *pc87427_attributes_temp[6][10] = अणु
	अणु
		&sensor_dev_attr_temp1_input.dev_attr.attr,
		&sensor_dev_attr_temp1_min.dev_attr.attr,
		&sensor_dev_attr_temp1_max.dev_attr.attr,
		&sensor_dev_attr_temp1_crit.dev_attr.attr,
		&sensor_dev_attr_temp1_type.dev_attr.attr,
		&sensor_dev_attr_temp1_min_alarm.dev_attr.attr,
		&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
		&sensor_dev_attr_temp1_crit_alarm.dev_attr.attr,
		&sensor_dev_attr_temp1_fault.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_temp2_input.dev_attr.attr,
		&sensor_dev_attr_temp2_min.dev_attr.attr,
		&sensor_dev_attr_temp2_max.dev_attr.attr,
		&sensor_dev_attr_temp2_crit.dev_attr.attr,
		&sensor_dev_attr_temp2_type.dev_attr.attr,
		&sensor_dev_attr_temp2_min_alarm.dev_attr.attr,
		&sensor_dev_attr_temp2_max_alarm.dev_attr.attr,
		&sensor_dev_attr_temp2_crit_alarm.dev_attr.attr,
		&sensor_dev_attr_temp2_fault.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_temp3_input.dev_attr.attr,
		&sensor_dev_attr_temp3_min.dev_attr.attr,
		&sensor_dev_attr_temp3_max.dev_attr.attr,
		&sensor_dev_attr_temp3_crit.dev_attr.attr,
		&sensor_dev_attr_temp3_type.dev_attr.attr,
		&sensor_dev_attr_temp3_min_alarm.dev_attr.attr,
		&sensor_dev_attr_temp3_max_alarm.dev_attr.attr,
		&sensor_dev_attr_temp3_crit_alarm.dev_attr.attr,
		&sensor_dev_attr_temp3_fault.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_temp4_input.dev_attr.attr,
		&sensor_dev_attr_temp4_min.dev_attr.attr,
		&sensor_dev_attr_temp4_max.dev_attr.attr,
		&sensor_dev_attr_temp4_crit.dev_attr.attr,
		&sensor_dev_attr_temp4_type.dev_attr.attr,
		&sensor_dev_attr_temp4_min_alarm.dev_attr.attr,
		&sensor_dev_attr_temp4_max_alarm.dev_attr.attr,
		&sensor_dev_attr_temp4_crit_alarm.dev_attr.attr,
		&sensor_dev_attr_temp4_fault.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_temp5_input.dev_attr.attr,
		&sensor_dev_attr_temp5_min.dev_attr.attr,
		&sensor_dev_attr_temp5_max.dev_attr.attr,
		&sensor_dev_attr_temp5_crit.dev_attr.attr,
		&sensor_dev_attr_temp5_type.dev_attr.attr,
		&sensor_dev_attr_temp5_min_alarm.dev_attr.attr,
		&sensor_dev_attr_temp5_max_alarm.dev_attr.attr,
		&sensor_dev_attr_temp5_crit_alarm.dev_attr.attr,
		&sensor_dev_attr_temp5_fault.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_temp6_input.dev_attr.attr,
		&sensor_dev_attr_temp6_min.dev_attr.attr,
		&sensor_dev_attr_temp6_max.dev_attr.attr,
		&sensor_dev_attr_temp6_crit.dev_attr.attr,
		&sensor_dev_attr_temp6_type.dev_attr.attr,
		&sensor_dev_attr_temp6_min_alarm.dev_attr.attr,
		&sensor_dev_attr_temp6_max_alarm.dev_attr.attr,
		&sensor_dev_attr_temp6_crit_alarm.dev_attr.attr,
		&sensor_dev_attr_temp6_fault.dev_attr.attr,
		शून्य
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा attribute_group pc87427_group_temp[6] = अणु
	अणु .attrs = pc87427_attributes_temp[0] पूर्ण,
	अणु .attrs = pc87427_attributes_temp[1] पूर्ण,
	अणु .attrs = pc87427_attributes_temp[2] पूर्ण,
	अणु .attrs = pc87427_attributes_temp[3] पूर्ण,
	अणु .attrs = pc87427_attributes_temp[4] पूर्ण,
	अणु .attrs = pc87427_attributes_temp[5] पूर्ण,
पूर्ण;

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute
			 *devattr, अक्षर *buf)
अणु
	काष्ठा pc87427_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", data->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);


/*
 * Device detection, attach and detach
 */

अटल पूर्णांक pc87427_request_regions(काष्ठा platक्रमm_device *pdev,
					     पूर्णांक count)
अणु
	काष्ठा resource *res;
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_IO, i);
		अगर (!res) अणु
			dev_err(&pdev->dev, "Missing resource #%d\n", i);
			वापस -ENOENT;
		पूर्ण
		अगर (!devm_request_region(&pdev->dev, res->start,
					 resource_size(res), DRVNAME)) अणु
			dev_err(&pdev->dev,
				"Failed to request region 0x%lx-0x%lx\n",
				(अचिन्हित दीर्घ)res->start,
				(अचिन्हित दीर्घ)res->end);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pc87427_init_device(काष्ठा device *dev)
अणु
	काष्ठा pc87427_sio_data *sio_data = dev_get_platdata(dev);
	काष्ठा pc87427_data *data = dev_get_drvdata(dev);
	पूर्णांक i;
	u8 reg;

	/* The FMC module should be पढ़ोy */
	reg = pc87427_पढ़ो8(data, LD_FAN, PC87427_REG_BANK);
	अगर (!(reg & 0x80))
		dev_warn(dev, "%s module not ready!\n", "FMC");

	/* Check which fans are enabled */
	क्रम (i = 0; i < 8; i++) अणु
		अगर (!(sio_data->has_fanin & (1 << i)))	/* Not wired */
			जारी;
		reg = pc87427_पढ़ो8_bank(data, LD_FAN, BANK_FM(i),
					 PC87427_REG_FAN_STATUS);
		अगर (reg & FAN_STATUS_MONEN)
			data->fan_enabled |= (1 << i);
	पूर्ण

	अगर (!data->fan_enabled) अणु
		dev_dbg(dev, "Enabling monitoring of all fans\n");
		क्रम (i = 0; i < 8; i++) अणु
			अगर (!(sio_data->has_fanin & (1 << i)))	/* Not wired */
				जारी;
			pc87427_ग_लिखो8_bank(data, LD_FAN, BANK_FM(i),
					    PC87427_REG_FAN_STATUS,
					    FAN_STATUS_MONEN);
		पूर्ण
		data->fan_enabled = sio_data->has_fanin;
	पूर्ण

	/* Check which PWM outमाला_दो are enabled */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (!(sio_data->has_fanout & (1 << i)))	/* Not wired */
			जारी;
		reg = pc87427_पढ़ो8_bank(data, LD_FAN, BANK_FC(i),
					 PC87427_REG_PWM_ENABLE);
		अगर (reg & PWM_ENABLE_CTLEN)
			data->pwm_enabled |= (1 << i);

		/*
		 * We करोn't expose an पूर्णांकerface to reconfigure the स्वतःmatic
		 * fan control mode, so only allow to वापस to this mode अगर
		 * it was originally set.
		 */
		अगर ((reg & PWM_ENABLE_MODE_MASK) == PWM_MODE_AUTO) अणु
			dev_dbg(dev, "PWM%d is in automatic control mode\n",
				i + 1);
			data->pwm_स्वतः_ok |= (1 << i);
		पूर्ण
	पूर्ण

	/* The HMC module should be पढ़ोy */
	reg = pc87427_पढ़ो8(data, LD_TEMP, PC87427_REG_BANK);
	अगर (!(reg & 0x80))
		dev_warn(dev, "%s module not ready!\n", "HMC");

	/* Check which temperature channels are enabled */
	क्रम (i = 0; i < 6; i++) अणु
		reg = pc87427_पढ़ो8_bank(data, LD_TEMP, BANK_TM(i),
					 PC87427_REG_TEMP_STATUS);
		अगर (reg & TEMP_STATUS_CHANEN)
			data->temp_enabled |= (1 << i);
	पूर्ण
पूर्ण

अटल व्योम pc87427_हटाओ_files(काष्ठा device *dev)
अणु
	काष्ठा pc87427_data *data = dev_get_drvdata(dev);
	पूर्णांक i;

	device_हटाओ_file(dev, &dev_attr_name);
	क्रम (i = 0; i < 8; i++) अणु
		अगर (!(data->fan_enabled & (1 << i)))
			जारी;
		sysfs_हटाओ_group(&dev->kobj, &pc87427_group_fan[i]);
	पूर्ण
	क्रम (i = 0; i < 4; i++) अणु
		अगर (!(data->pwm_enabled & (1 << i)))
			जारी;
		sysfs_हटाओ_group(&dev->kobj, &pc87427_group_pwm[i]);
	पूर्ण
	क्रम (i = 0; i < 6; i++) अणु
		अगर (!(data->temp_enabled & (1 << i)))
			जारी;
		sysfs_हटाओ_group(&dev->kobj, &pc87427_group_temp[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक pc87427_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pc87427_sio_data *sio_data = dev_get_platdata(&pdev->dev);
	काष्ठा pc87427_data *data;
	पूर्णांक i, err, res_count;

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा pc87427_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->address[0] = sio_data->address[0];
	data->address[1] = sio_data->address[1];
	res_count = (data->address[0] != 0) + (data->address[1] != 0);

	err = pc87427_request_regions(pdev, res_count);
	अगर (err)
		वापस err;

	mutex_init(&data->lock);
	data->name = "pc87427";
	platक्रमm_set_drvdata(pdev, data);
	pc87427_init_device(&pdev->dev);

	/* Register sysfs hooks */
	err = device_create_file(&pdev->dev, &dev_attr_name);
	अगर (err)
		वापस err;
	क्रम (i = 0; i < 8; i++) अणु
		अगर (!(data->fan_enabled & (1 << i)))
			जारी;
		err = sysfs_create_group(&pdev->dev.kobj,
					 &pc87427_group_fan[i]);
		अगर (err)
			जाओ निकास_हटाओ_files;
	पूर्ण
	क्रम (i = 0; i < 4; i++) अणु
		अगर (!(data->pwm_enabled & (1 << i)))
			जारी;
		err = sysfs_create_group(&pdev->dev.kobj,
					 &pc87427_group_pwm[i]);
		अगर (err)
			जाओ निकास_हटाओ_files;
	पूर्ण
	क्रम (i = 0; i < 6; i++) अणु
		अगर (!(data->temp_enabled & (1 << i)))
			जारी;
		err = sysfs_create_group(&pdev->dev.kobj,
					 &pc87427_group_temp[i]);
		अगर (err)
			जाओ निकास_हटाओ_files;
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(&pdev->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		dev_err(&pdev->dev, "Class registration failed (%d)\n", err);
		जाओ निकास_हटाओ_files;
	पूर्ण

	वापस 0;

निकास_हटाओ_files:
	pc87427_हटाओ_files(&pdev->dev);
	वापस err;
पूर्ण

अटल पूर्णांक pc87427_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pc87427_data *data = platक्रमm_get_drvdata(pdev);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	pc87427_हटाओ_files(&pdev->dev);

	वापस 0;
पूर्ण


अटल काष्ठा platक्रमm_driver pc87427_driver = अणु
	.driver = अणु
		.name	= DRVNAME,
	पूर्ण,
	.probe		= pc87427_probe,
	.हटाओ		= pc87427_हटाओ,
पूर्ण;

अटल पूर्णांक __init pc87427_device_add(स्थिर काष्ठा pc87427_sio_data *sio_data)
अणु
	काष्ठा resource res[2] = अणु
		अणु .flags	= IORESOURCE_IO पूर्ण,
		अणु .flags	= IORESOURCE_IO पूर्ण,
	पूर्ण;
	पूर्णांक err, i, res_count;

	res_count = 0;
	क्रम (i = 0; i < 2; i++) अणु
		अगर (!sio_data->address[i])
			जारी;
		res[res_count].start = sio_data->address[i];
		res[res_count].end = sio_data->address[i] + REGION_LENGTH - 1;
		res[res_count].name = logdev_str[i];

		err = acpi_check_resource_conflict(&res[res_count]);
		अगर (err)
			जाओ निकास;

		res_count++;
	पूर्ण

	pdev = platक्रमm_device_alloc(DRVNAME, res[0].start);
	अगर (!pdev) अणु
		err = -ENOMEM;
		pr_err("Device allocation failed\n");
		जाओ निकास;
	पूर्ण

	err = platक्रमm_device_add_resources(pdev, res, res_count);
	अगर (err) अणु
		pr_err("Device resource addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	err = platक्रमm_device_add_data(pdev, sio_data,
				       माप(काष्ठा pc87427_sio_data));
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

अटल पूर्णांक __init pc87427_find(पूर्णांक sioaddr, काष्ठा pc87427_sio_data *sio_data)
अणु
	u16 val;
	u8 cfg, cfg_b;
	पूर्णांक i, err;

	err = superio_enter(sioaddr);
	अगर (err)
		वापस err;

	/* Identअगरy device */
	val = क्रमce_id ? क्रमce_id : superio_inb(sioaddr, SIOREG_DEVID);
	अगर (val != 0xf2) अणु	/* PC87427 */
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		sio_data->address[i] = 0;
		/* Select logical device */
		superio_outb(sioaddr, SIOREG_LDSEL, logdev[i]);

		val = superio_inb(sioaddr, SIOREG_ACT);
		अगर (!(val & 0x01)) अणु
			pr_info("Logical device 0x%02x not activated\n",
				logdev[i]);
			जारी;
		पूर्ण

		val = superio_inb(sioaddr, SIOREG_MAP);
		अगर (val & 0x01) अणु
			pr_warn("Logical device 0x%02x is memory-mapped, can't use\n",
				logdev[i]);
			जारी;
		पूर्ण

		val = (superio_inb(sioaddr, SIOREG_IOBASE) << 8)
		    | superio_inb(sioaddr, SIOREG_IOBASE + 1);
		अगर (!val) अणु
			pr_info("I/O base address not set for logical device 0x%02x\n",
				logdev[i]);
			जारी;
		पूर्ण
		sio_data->address[i] = val;
	पूर्ण

	/* No poपूर्णांक in loading the driver अगर everything is disabled */
	अगर (!sio_data->address[0] && !sio_data->address[1]) अणु
		err = -ENODEV;
		जाओ निकास;
	पूर्ण

	/* Check which fan inमाला_दो are wired */
	sio_data->has_fanin = (1 << 2) | (1 << 3);	/* FANIN2, FANIN3 */

	cfg = superio_inb(sioaddr, SIOREG_CF2);
	अगर (!(cfg & (1 << 3)))
		sio_data->has_fanin |= (1 << 0);	/* FANIN0 */
	अगर (!(cfg & (1 << 2)))
		sio_data->has_fanin |= (1 << 4);	/* FANIN4 */

	cfg = superio_inb(sioaddr, SIOREG_CFD);
	अगर (!(cfg & (1 << 0)))
		sio_data->has_fanin |= (1 << 1);	/* FANIN1 */

	cfg = superio_inb(sioaddr, SIOREG_CF4);
	अगर (!(cfg & (1 << 0)))
		sio_data->has_fanin |= (1 << 7);	/* FANIN7 */
	cfg_b = superio_inb(sioaddr, SIOREG_CFB);
	अगर (!(cfg & (1 << 1)) && (cfg_b & (1 << 3)))
		sio_data->has_fanin |= (1 << 5);	/* FANIN5 */
	cfg = superio_inb(sioaddr, SIOREG_CF3);
	अगर ((cfg & (1 << 3)) && !(cfg_b & (1 << 5)))
		sio_data->has_fanin |= (1 << 6);	/* FANIN6 */

	/* Check which fan outमाला_दो are wired */
	sio_data->has_fanout = (1 << 0);		/* FANOUT0 */
	अगर (cfg_b & (1 << 0))
		sio_data->has_fanout |= (1 << 3);	/* FANOUT3 */

	cfg = superio_inb(sioaddr, SIOREG_CFC);
	अगर (!(cfg & (1 << 4))) अणु
		अगर (cfg_b & (1 << 1))
			sio_data->has_fanout |= (1 << 1); /* FANOUT1 */
		अगर (cfg_b & (1 << 2))
			sio_data->has_fanout |= (1 << 2); /* FANOUT2 */
	पूर्ण

	/* FANOUT1 and FANOUT2 can each be routed to 2 dअगरferent pins */
	cfg = superio_inb(sioaddr, SIOREG_CF5);
	अगर (cfg & (1 << 6))
		sio_data->has_fanout |= (1 << 1);	/* FANOUT1 */
	अगर (cfg & (1 << 5))
		sio_data->has_fanout |= (1 << 2);	/* FANOUT2 */

निकास:
	superio_निकास(sioaddr);
	वापस err;
पूर्ण

अटल पूर्णांक __init pc87427_init(व्योम)
अणु
	पूर्णांक err;
	काष्ठा pc87427_sio_data sio_data;

	अगर (pc87427_find(0x2e, &sio_data)
	 && pc87427_find(0x4e, &sio_data))
		वापस -ENODEV;

	err = platक्रमm_driver_रेजिस्टर(&pc87427_driver);
	अगर (err)
		जाओ निकास;

	/* Sets global pdev as a side effect */
	err = pc87427_device_add(&sio_data);
	अगर (err)
		जाओ निकास_driver;

	वापस 0;

निकास_driver:
	platक्रमm_driver_unरेजिस्टर(&pc87427_driver);
निकास:
	वापस err;
पूर्ण

अटल व्योम __निकास pc87427_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(pdev);
	platक्रमm_driver_unरेजिस्टर(&pc87427_driver);
पूर्ण

MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("PC87427 hardware monitoring driver");
MODULE_LICENSE("GPL");

module_init(pc87427_init);
module_निकास(pc87427_निकास);
