<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * f71805f.c - driver क्रम the Fपूर्णांकek F71805F/FG and F71872F/FG Super-I/O
 *             chips पूर्णांकegrated hardware monitoring features
 * Copyright (C) 2005-2006  Jean Delvare <jdelvare@suse.de>
 *
 * The F71805F/FG is a LPC Super-I/O chip made by Fपूर्णांकek. It पूर्णांकegrates
 * complete hardware monitoring features: voltage, fan and temperature
 * sensors, and manual and स्वतःmatic fan speed control.
 *
 * The F71872F/FG is almost the same, with two more voltages monitored,
 * and 6 VID inमाला_दो.
 *
 * The F71806F/FG is essentially the same as the F71872F/FG. It even has
 * the same chip ID, so the driver can't dअगरferentiate between.
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

#घोषणा DRVNAME "f71805f"
क्रमागत kinds अणु f71805f, f71872f पूर्ण;

/*
 * Super-I/O स्थिरants and functions
 */

#घोषणा F71805F_LD_HWM		0x04

#घोषणा SIO_REG_LDSEL		0x07	/* Logical device select */
#घोषणा SIO_REG_DEVID		0x20	/* Device ID (2 bytes) */
#घोषणा SIO_REG_DEVREV		0x22	/* Device revision */
#घोषणा SIO_REG_MANID		0x23	/* Fपूर्णांकek ID (2 bytes) */
#घोषणा SIO_REG_FNSEL1		0x29	/* Multi Function Select 1 (F71872F) */
#घोषणा SIO_REG_ENABLE		0x30	/* Logical device enable */
#घोषणा SIO_REG_ADDR		0x60	/* Logical device address (2 bytes) */

#घोषणा SIO_FINTEK_ID		0x1934
#घोषणा SIO_F71805F_ID		0x0406
#घोषणा SIO_F71872F_ID		0x0341

अटल अंतरभूत पूर्णांक
superio_inb(पूर्णांक base, पूर्णांक reg)
अणु
	outb(reg, base);
	वापस inb(base + 1);
पूर्ण

अटल पूर्णांक
superio_inw(पूर्णांक base, पूर्णांक reg)
अणु
	पूर्णांक val;
	outb(reg++, base);
	val = inb(base + 1) << 8;
	outb(reg, base);
	val |= inb(base + 1);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम
superio_select(पूर्णांक base, पूर्णांक ld)
अणु
	outb(SIO_REG_LDSEL, base);
	outb(ld, base + 1);
पूर्ण

अटल अंतरभूत पूर्णांक
superio_enter(पूर्णांक base)
अणु
	अगर (!request_muxed_region(base, 2, DRVNAME))
		वापस -EBUSY;

	outb(0x87, base);
	outb(0x87, base);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
superio_निकास(पूर्णांक base)
अणु
	outb(0xaa, base);
	release_region(base, 2);
पूर्ण

/*
 * ISA स्थिरants
 */

#घोषणा REGION_LENGTH		8
#घोषणा ADDR_REG_OFFSET		5
#घोषणा DATA_REG_OFFSET		6

/*
 * Registers
 */

/* in nr from 0 to 10 (8-bit values) */
#घोषणा F71805F_REG_IN(nr)		(0x10 + (nr))
#घोषणा F71805F_REG_IN_HIGH(nr)		((nr) < 10 ? 0x40 + 2 * (nr) : 0x2E)
#घोषणा F71805F_REG_IN_LOW(nr)		((nr) < 10 ? 0x41 + 2 * (nr) : 0x2F)
/* fan nr from 0 to 2 (12-bit values, two रेजिस्टरs) */
#घोषणा F71805F_REG_FAN(nr)		(0x20 + 2 * (nr))
#घोषणा F71805F_REG_FAN_LOW(nr)		(0x28 + 2 * (nr))
#घोषणा F71805F_REG_FAN_TARGET(nr)	(0x69 + 16 * (nr))
#घोषणा F71805F_REG_FAN_CTRL(nr)	(0x60 + 16 * (nr))
#घोषणा F71805F_REG_PWM_FREQ(nr)	(0x63 + 16 * (nr))
#घोषणा F71805F_REG_PWM_DUTY(nr)	(0x6B + 16 * (nr))
/* temp nr from 0 to 2 (8-bit values) */
#घोषणा F71805F_REG_TEMP(nr)		(0x1B + (nr))
#घोषणा F71805F_REG_TEMP_HIGH(nr)	(0x54 + 2 * (nr))
#घोषणा F71805F_REG_TEMP_HYST(nr)	(0x55 + 2 * (nr))
#घोषणा F71805F_REG_TEMP_MODE		0x01
/* pwm/fan pwmnr from 0 to 2, स्वतः poपूर्णांक apnr from 0 to 2 */
/* map Fपूर्णांकek numbers to our numbers as follows: 9->0, 5->1, 1->2 */
#घोषणा F71805F_REG_PWM_AUTO_POINT_TEMP(pwmnr, apnr) \
					(0xA0 + 0x10 * (pwmnr) + (2 - (apnr)))
#घोषणा F71805F_REG_PWM_AUTO_POINT_FAN(pwmnr, apnr) \
					(0xA4 + 0x10 * (pwmnr) + \
						2 * (2 - (apnr)))

#घोषणा F71805F_REG_START		0x00
/* status nr from 0 to 2 */
#घोषणा F71805F_REG_STATUS(nr)		(0x36 + (nr))

/* inभागidual रेजिस्टर bits */
#घोषणा FAN_CTRL_DC_MODE		0x10
#घोषणा FAN_CTRL_LATCH_FULL		0x08
#घोषणा FAN_CTRL_MODE_MASK		0x03
#घोषणा FAN_CTRL_MODE_SPEED		0x00
#घोषणा FAN_CTRL_MODE_TEMPERATURE	0x01
#घोषणा FAN_CTRL_MODE_MANUAL		0x02

/*
 * Data काष्ठाures and manipulation thereof
 */

काष्ठा f71805f_स्वतः_poपूर्णांक अणु
	u8 temp[3];
	u16 fan[3];
पूर्ण;

काष्ठा f71805f_data अणु
	अचिन्हित लघु addr;
	स्थिर अक्षर *name;
	काष्ठा device *hwmon_dev;

	काष्ठा mutex update_lock;
	अक्षर valid;		/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */
	अचिन्हित दीर्घ last_limits;	/* In jअगरfies */

	/* Register values */
	u8 in[11];
	u8 in_high[11];
	u8 in_low[11];
	u16 has_in;
	u16 fan[3];
	u16 fan_low[3];
	u16 fan_target[3];
	u8 fan_ctrl[3];
	u8 pwm[3];
	u8 pwm_freq[3];
	u8 temp[3];
	u8 temp_high[3];
	u8 temp_hyst[3];
	u8 temp_mode;
	अचिन्हित दीर्घ alarms;
	काष्ठा f71805f_स्वतः_poपूर्णांक स्वतः_poपूर्णांकs[3];
पूर्ण;

काष्ठा f71805f_sio_data अणु
	क्रमागत kinds kind;
	u8 fnsel1;
पूर्ण;

अटल अंतरभूत दीर्घ in_from_reg(u8 reg)
अणु
	वापस reg * 8;
पूर्ण

/* The 2 least signअगरicant bits are not used */
अटल अंतरभूत u8 in_to_reg(दीर्घ val)
अणु
	अगर (val <= 0)
		वापस 0;
	अगर (val >= 2016)
		वापस 0xfc;
	वापस ((val + 16) / 32) << 2;
पूर्ण

/* in0 is करोwnscaled by a factor 2 पूर्णांकernally */
अटल अंतरभूत दीर्घ in0_from_reg(u8 reg)
अणु
	वापस reg * 16;
पूर्ण

अटल अंतरभूत u8 in0_to_reg(दीर्घ val)
अणु
	अगर (val <= 0)
		वापस 0;
	अगर (val >= 4032)
		वापस 0xfc;
	वापस ((val + 32) / 64) << 2;
पूर्ण

/* The 4 most signअगरicant bits are not used */
अटल अंतरभूत दीर्घ fan_from_reg(u16 reg)
अणु
	reg &= 0xfff;
	अगर (!reg || reg == 0xfff)
		वापस 0;
	वापस 1500000 / reg;
पूर्ण

अटल अंतरभूत u16 fan_to_reg(दीर्घ rpm)
अणु
	/*
	 * If the low limit is set below what the chip can measure,
	 * store the largest possible 12-bit value in the रेजिस्टरs,
	 * so that no alarm will ever trigger.
	 */
	अगर (rpm < 367)
		वापस 0xfff;
	वापस 1500000 / rpm;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pwm_freq_from_reg(u8 reg)
अणु
	अचिन्हित दीर्घ घड़ी = (reg & 0x80) ? 48000000UL : 1000000UL;

	reg &= 0x7f;
	अगर (reg == 0)
		reg++;
	वापस घड़ी / (reg << 8);
पूर्ण

अटल अंतरभूत u8 pwm_freq_to_reg(अचिन्हित दीर्घ val)
अणु
	अगर (val >= 187500)	/* The highest we can करो */
		वापस 0x80;
	अगर (val >= 1475)	/* Use 48 MHz घड़ी */
		वापस 0x80 | (48000000UL / (val << 8));
	अगर (val < 31)		/* The lowest we can करो */
		वापस 0x7f;
	अन्यथा			/* Use 1 MHz घड़ी */
		वापस 1000000UL / (val << 8);
पूर्ण

अटल अंतरभूत पूर्णांक pwm_mode_from_reg(u8 reg)
अणु
	वापस !(reg & FAN_CTRL_DC_MODE);
पूर्ण

अटल अंतरभूत दीर्घ temp_from_reg(u8 reg)
अणु
	वापस reg * 1000;
पूर्ण

अटल अंतरभूत u8 temp_to_reg(दीर्घ val)
अणु
	अगर (val <= 0)
		वापस 0;
	अगर (val >= 1000 * 0xff)
		वापस 0xff;
	वापस (val + 500) / 1000;
पूर्ण

/*
 * Device I/O access
 */

/* Must be called with data->update_lock held, except during initialization */
अटल u8 f71805f_पढ़ो8(काष्ठा f71805f_data *data, u8 reg)
अणु
	outb(reg, data->addr + ADDR_REG_OFFSET);
	वापस inb(data->addr + DATA_REG_OFFSET);
पूर्ण

/* Must be called with data->update_lock held, except during initialization */
अटल व्योम f71805f_ग_लिखो8(काष्ठा f71805f_data *data, u8 reg, u8 val)
अणु
	outb(reg, data->addr + ADDR_REG_OFFSET);
	outb(val, data->addr + DATA_REG_OFFSET);
पूर्ण

/*
 * It is important to पढ़ो the MSB first, because करोing so latches the
 * value of the LSB, so we are sure both bytes beदीर्घ to the same value.
 * Must be called with data->update_lock held, except during initialization
 */
अटल u16 f71805f_पढ़ो16(काष्ठा f71805f_data *data, u8 reg)
अणु
	u16 val;

	outb(reg, data->addr + ADDR_REG_OFFSET);
	val = inb(data->addr + DATA_REG_OFFSET) << 8;
	outb(++reg, data->addr + ADDR_REG_OFFSET);
	val |= inb(data->addr + DATA_REG_OFFSET);

	वापस val;
पूर्ण

/* Must be called with data->update_lock held, except during initialization */
अटल व्योम f71805f_ग_लिखो16(काष्ठा f71805f_data *data, u8 reg, u16 val)
अणु
	outb(reg, data->addr + ADDR_REG_OFFSET);
	outb(val >> 8, data->addr + DATA_REG_OFFSET);
	outb(++reg, data->addr + ADDR_REG_OFFSET);
	outb(val & 0xff, data->addr + DATA_REG_OFFSET);
पूर्ण

अटल काष्ठा f71805f_data *f71805f_update_device(काष्ठा device *dev)
अणु
	काष्ठा f71805f_data *data = dev_get_drvdata(dev);
	पूर्णांक nr, apnr;

	mutex_lock(&data->update_lock);

	/* Limit रेजिस्टरs cache is refreshed after 60 seconds */
	अगर (समय_after(jअगरfies, data->last_updated + 60 * HZ)
	 || !data->valid) अणु
		क्रम (nr = 0; nr < 11; nr++) अणु
			अगर (!(data->has_in & (1 << nr)))
				जारी;
			data->in_high[nr] = f71805f_पढ़ो8(data,
					    F71805F_REG_IN_HIGH(nr));
			data->in_low[nr] = f71805f_पढ़ो8(data,
					   F71805F_REG_IN_LOW(nr));
		पूर्ण
		क्रम (nr = 0; nr < 3; nr++) अणु
			data->fan_low[nr] = f71805f_पढ़ो16(data,
					    F71805F_REG_FAN_LOW(nr));
			data->fan_target[nr] = f71805f_पढ़ो16(data,
					       F71805F_REG_FAN_TARGET(nr));
			data->pwm_freq[nr] = f71805f_पढ़ो8(data,
					     F71805F_REG_PWM_FREQ(nr));
		पूर्ण
		क्रम (nr = 0; nr < 3; nr++) अणु
			data->temp_high[nr] = f71805f_पढ़ो8(data,
					      F71805F_REG_TEMP_HIGH(nr));
			data->temp_hyst[nr] = f71805f_पढ़ो8(data,
					      F71805F_REG_TEMP_HYST(nr));
		पूर्ण
		data->temp_mode = f71805f_पढ़ो8(data, F71805F_REG_TEMP_MODE);
		क्रम (nr = 0; nr < 3; nr++) अणु
			क्रम (apnr = 0; apnr < 3; apnr++) अणु
				data->स्वतः_poपूर्णांकs[nr].temp[apnr] =
					f71805f_पढ़ो8(data,
					F71805F_REG_PWM_AUTO_POINT_TEMP(nr,
									apnr));
				data->स्वतः_poपूर्णांकs[nr].fan[apnr] =
					f71805f_पढ़ो16(data,
					F71805F_REG_PWM_AUTO_POINT_FAN(nr,
								       apnr));
			पूर्ण
		पूर्ण

		data->last_limits = jअगरfies;
	पूर्ण

	/* Measurement रेजिस्टरs cache is refreshed after 1 second */
	अगर (समय_after(jअगरfies, data->last_updated + HZ)
	 || !data->valid) अणु
		क्रम (nr = 0; nr < 11; nr++) अणु
			अगर (!(data->has_in & (1 << nr)))
				जारी;
			data->in[nr] = f71805f_पढ़ो8(data,
				       F71805F_REG_IN(nr));
		पूर्ण
		क्रम (nr = 0; nr < 3; nr++) अणु
			data->fan[nr] = f71805f_पढ़ो16(data,
					F71805F_REG_FAN(nr));
			data->fan_ctrl[nr] = f71805f_पढ़ो8(data,
					     F71805F_REG_FAN_CTRL(nr));
			data->pwm[nr] = f71805f_पढ़ो8(data,
					F71805F_REG_PWM_DUTY(nr));
		पूर्ण
		क्रम (nr = 0; nr < 3; nr++) अणु
			data->temp[nr] = f71805f_पढ़ो8(data,
					 F71805F_REG_TEMP(nr));
		पूर्ण
		data->alarms = f71805f_पढ़ो8(data, F71805F_REG_STATUS(0))
			+ (f71805f_पढ़ो8(data, F71805F_REG_STATUS(1)) << 8)
			+ (f71805f_पढ़ो8(data, F71805F_REG_STATUS(2)) << 16);

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/*
 * Sysfs पूर्णांकerface
 */

अटल sमाप_प्रकार show_in0(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;

	वापस प्र_लिखो(buf, "%ld\n", in0_from_reg(data->in[nr]));
पूर्ण

अटल sमाप_प्रकार show_in0_max(काष्ठा device *dev, काष्ठा device_attribute
			    *devattr, अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;

	वापस प्र_लिखो(buf, "%ld\n", in0_from_reg(data->in_high[nr]));
पूर्ण

अटल sमाप_प्रकार show_in0_min(काष्ठा device *dev, काष्ठा device_attribute
			    *devattr, अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;

	वापस प्र_लिखो(buf, "%ld\n", in0_from_reg(data->in_low[nr]));
पूर्ण

अटल sमाप_प्रकार set_in0_max(काष्ठा device *dev, काष्ठा device_attribute
			   *devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71805f_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_high[nr] = in0_to_reg(val);
	f71805f_ग_लिखो8(data, F71805F_REG_IN_HIGH(nr), data->in_high[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार set_in0_min(काष्ठा device *dev, काष्ठा device_attribute
			   *devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71805f_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_low[nr] = in0_to_reg(val);
	f71805f_ग_लिखो8(data, F71805F_REG_IN_LOW(nr), data->in_low[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_in(काष्ठा device *dev, काष्ठा device_attribute *devattr,
		       अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;

	वापस प्र_लिखो(buf, "%ld\n", in_from_reg(data->in[nr]));
पूर्ण

अटल sमाप_प्रकार show_in_max(काष्ठा device *dev, काष्ठा device_attribute
			   *devattr, अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;

	वापस प्र_लिखो(buf, "%ld\n", in_from_reg(data->in_high[nr]));
पूर्ण

अटल sमाप_प्रकार show_in_min(काष्ठा device *dev, काष्ठा device_attribute
			   *devattr, अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;

	वापस प्र_लिखो(buf, "%ld\n", in_from_reg(data->in_low[nr]));
पूर्ण

अटल sमाप_प्रकार set_in_max(काष्ठा device *dev, काष्ठा device_attribute
			  *devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71805f_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_high[nr] = in_to_reg(val);
	f71805f_ग_लिखो8(data, F71805F_REG_IN_HIGH(nr), data->in_high[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार set_in_min(काष्ठा device *dev, काष्ठा device_attribute
			  *devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71805f_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->in_low[nr] = in_to_reg(val);
	f71805f_ग_लिखो8(data, F71805F_REG_IN_LOW(nr), data->in_low[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_fan(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;

	वापस प्र_लिखो(buf, "%ld\n", fan_from_reg(data->fan[nr]));
पूर्ण

अटल sमाप_प्रकार show_fan_min(काष्ठा device *dev, काष्ठा device_attribute
			    *devattr, अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;

	वापस प्र_लिखो(buf, "%ld\n", fan_from_reg(data->fan_low[nr]));
पूर्ण

अटल sमाप_प्रकार show_fan_target(काष्ठा device *dev, काष्ठा device_attribute
			       *devattr, अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;

	वापस प्र_लिखो(buf, "%ld\n", fan_from_reg(data->fan_target[nr]));
पूर्ण

अटल sमाप_प्रकार set_fan_min(काष्ठा device *dev, काष्ठा device_attribute
			   *devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71805f_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan_low[nr] = fan_to_reg(val);
	f71805f_ग_लिखो16(data, F71805F_REG_FAN_LOW(nr), data->fan_low[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार set_fan_target(काष्ठा device *dev, काष्ठा device_attribute
			      *devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71805f_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->fan_target[nr] = fan_to_reg(val);
	f71805f_ग_लिखो16(data, F71805F_REG_FAN_TARGET(nr),
			data->fan_target[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_pwm(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;

	वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)data->pwm[nr]);
पूर्ण

अटल sमाप_प्रकार show_pwm_enable(काष्ठा device *dev, काष्ठा device_attribute
			       *devattr, अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;
	पूर्णांक mode;

	चयन (data->fan_ctrl[nr] & FAN_CTRL_MODE_MASK) अणु
	हाल FAN_CTRL_MODE_SPEED:
		mode = 3;
		अवरोध;
	हाल FAN_CTRL_MODE_TEMPERATURE:
		mode = 2;
		अवरोध;
	शेष: /* MANUAL */
		mode = 1;
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", mode);
पूर्ण

अटल sमाप_प्रकार show_pwm_freq(काष्ठा device *dev, काष्ठा device_attribute
			     *devattr, अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;

	वापस प्र_लिखो(buf, "%lu\n", pwm_freq_from_reg(data->pwm_freq[nr]));
पूर्ण

अटल sमाप_प्रकार show_pwm_mode(काष्ठा device *dev, काष्ठा device_attribute
			     *devattr, अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;

	वापस प्र_लिखो(buf, "%d\n", pwm_mode_from_reg(data->fan_ctrl[nr]));
पूर्ण

अटल sमाप_प्रकार set_pwm(काष्ठा device *dev, काष्ठा device_attribute *devattr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71805f_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val > 255)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->pwm[nr] = val;
	f71805f_ग_लिखो8(data, F71805F_REG_PWM_DUTY(nr), data->pwm[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल काष्ठा attribute *f71805f_attr_pwm[];

अटल sमाप_प्रकार set_pwm_enable(काष्ठा device *dev, काष्ठा device_attribute
			      *devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71805f_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;
	u8 reg;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val < 1 || val > 3)
		वापस -EINVAL;

	अगर (val > 1) अणु /* Automatic mode, user can't set PWM value */
		अगर (sysfs_chmod_file(&dev->kobj, f71805f_attr_pwm[nr],
				     S_IRUGO))
			dev_dbg(dev, "chmod -w pwm%d failed\n", nr + 1);
	पूर्ण

	mutex_lock(&data->update_lock);
	reg = f71805f_पढ़ो8(data, F71805F_REG_FAN_CTRL(nr))
	    & ~FAN_CTRL_MODE_MASK;
	चयन (val) अणु
	हाल 1:
		reg |= FAN_CTRL_MODE_MANUAL;
		अवरोध;
	हाल 2:
		reg |= FAN_CTRL_MODE_TEMPERATURE;
		अवरोध;
	हाल 3:
		reg |= FAN_CTRL_MODE_SPEED;
		अवरोध;
	पूर्ण
	data->fan_ctrl[nr] = reg;
	f71805f_ग_लिखो8(data, F71805F_REG_FAN_CTRL(nr), reg);
	mutex_unlock(&data->update_lock);

	अगर (val == 1) अणु /* Manual mode, user can set PWM value */
		अगर (sysfs_chmod_file(&dev->kobj, f71805f_attr_pwm[nr],
				     S_IRUGO | S_IWUSR))
			dev_dbg(dev, "chmod +w pwm%d failed\n", nr + 1);
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार set_pwm_freq(काष्ठा device *dev, काष्ठा device_attribute
			    *devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71805f_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->pwm_freq[nr] = pwm_freq_to_reg(val);
	f71805f_ग_लिखो8(data, F71805F_REG_PWM_FREQ(nr), data->pwm_freq[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_pwm_स्वतः_poपूर्णांक_temp(काष्ठा device *dev,
					काष्ठा device_attribute *devattr,
					अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	पूर्णांक pwmnr = attr->nr;
	पूर्णांक apnr = attr->index;

	वापस प्र_लिखो(buf, "%ld\n",
		       temp_from_reg(data->स्वतः_poपूर्णांकs[pwmnr].temp[apnr]));
पूर्ण

अटल sमाप_प्रकार set_pwm_स्वतः_poपूर्णांक_temp(काष्ठा device *dev,
				       काष्ठा device_attribute *devattr,
				       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71805f_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	पूर्णांक pwmnr = attr->nr;
	पूर्णांक apnr = attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->स्वतः_poपूर्णांकs[pwmnr].temp[apnr] = temp_to_reg(val);
	f71805f_ग_लिखो8(data, F71805F_REG_PWM_AUTO_POINT_TEMP(pwmnr, apnr),
		       data->स्वतः_poपूर्णांकs[pwmnr].temp[apnr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_pwm_स्वतः_poपूर्णांक_fan(काष्ठा device *dev,
				       काष्ठा device_attribute *devattr,
				       अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	पूर्णांक pwmnr = attr->nr;
	पूर्णांक apnr = attr->index;

	वापस प्र_लिखो(buf, "%ld\n",
		       fan_from_reg(data->स्वतः_poपूर्णांकs[pwmnr].fan[apnr]));
पूर्ण

अटल sमाप_प्रकार set_pwm_स्वतः_poपूर्णांक_fan(काष्ठा device *dev,
				      काष्ठा device_attribute *devattr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71805f_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	पूर्णांक pwmnr = attr->nr;
	पूर्णांक apnr = attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->स्वतः_poपूर्णांकs[pwmnr].fan[apnr] = fan_to_reg(val);
	f71805f_ग_लिखो16(data, F71805F_REG_PWM_AUTO_POINT_FAN(pwmnr, apnr),
			data->स्वतः_poपूर्णांकs[pwmnr].fan[apnr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_temp(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;

	वापस प्र_लिखो(buf, "%ld\n", temp_from_reg(data->temp[nr]));
पूर्ण

अटल sमाप_प्रकार show_temp_max(काष्ठा device *dev, काष्ठा device_attribute
			     *devattr, अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;

	वापस प्र_लिखो(buf, "%ld\n", temp_from_reg(data->temp_high[nr]));
पूर्ण

अटल sमाप_प्रकार show_temp_hyst(काष्ठा device *dev, काष्ठा device_attribute
			      *devattr, अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;

	वापस प्र_लिखो(buf, "%ld\n", temp_from_reg(data->temp_hyst[nr]));
पूर्ण

अटल sमाप_प्रकार show_temp_type(काष्ठा device *dev, काष्ठा device_attribute
			      *devattr, अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;

	/* 3 is diode, 4 is thermistor */
	वापस प्र_लिखो(buf, "%u\n", (data->temp_mode & (1 << nr)) ? 3 : 4);
पूर्ण

अटल sमाप_प्रकार set_temp_max(काष्ठा device *dev, काष्ठा device_attribute
			    *devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71805f_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_high[nr] = temp_to_reg(val);
	f71805f_ग_लिखो8(data, F71805F_REG_TEMP_HIGH(nr), data->temp_high[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार set_temp_hyst(काष्ठा device *dev, काष्ठा device_attribute
			     *devattr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा f71805f_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक nr = attr->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_hyst[nr] = temp_to_reg(val);
	f71805f_ग_लिखो8(data, F71805F_REG_TEMP_HYST(nr), data->temp_hyst[nr]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार alarms_in_show(काष्ठा device *dev, काष्ठा device_attribute
			      *devattr, अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);

	वापस प्र_लिखो(buf, "%lu\n", data->alarms & 0x7ff);
पूर्ण

अटल sमाप_प्रकार alarms_fan_show(काष्ठा device *dev, काष्ठा device_attribute
			       *devattr, अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);

	वापस प्र_लिखो(buf, "%lu\n", (data->alarms >> 16) & 0x07);
पूर्ण

अटल sमाप_प्रकार alarms_temp_show(काष्ठा device *dev, काष्ठा device_attribute
				*devattr, अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);

	वापस प्र_लिखो(buf, "%lu\n", (data->alarms >> 11) & 0x07);
पूर्ण

अटल sमाप_प्रकार show_alarm(काष्ठा device *dev, काष्ठा device_attribute
			  *devattr, अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = f71805f_update_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक bitnr = attr->index;

	वापस प्र_लिखो(buf, "%lu\n", (data->alarms >> bitnr) & 1);
पूर्ण

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute
			 *devattr, अक्षर *buf)
अणु
	काष्ठा f71805f_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", data->name);
पूर्ण

अटल SENSOR_DEVICE_ATTR(in0_input, S_IRUGO, show_in0, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(in0_max, S_IRUGO | S_IWUSR,
			  show_in0_max, set_in0_max, 0);
अटल SENSOR_DEVICE_ATTR(in0_min, S_IRUGO | S_IWUSR,
			  show_in0_min, set_in0_min, 0);
अटल SENSOR_DEVICE_ATTR(in1_input, S_IRUGO, show_in, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(in1_max, S_IRUGO | S_IWUSR,
			  show_in_max, set_in_max, 1);
अटल SENSOR_DEVICE_ATTR(in1_min, S_IRUGO | S_IWUSR,
			  show_in_min, set_in_min, 1);
अटल SENSOR_DEVICE_ATTR(in2_input, S_IRUGO, show_in, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(in2_max, S_IRUGO | S_IWUSR,
			  show_in_max, set_in_max, 2);
अटल SENSOR_DEVICE_ATTR(in2_min, S_IRUGO | S_IWUSR,
			  show_in_min, set_in_min, 2);
अटल SENSOR_DEVICE_ATTR(in3_input, S_IRUGO, show_in, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(in3_max, S_IRUGO | S_IWUSR,
			  show_in_max, set_in_max, 3);
अटल SENSOR_DEVICE_ATTR(in3_min, S_IRUGO | S_IWUSR,
			  show_in_min, set_in_min, 3);
अटल SENSOR_DEVICE_ATTR(in4_input, S_IRUGO, show_in, शून्य, 4);
अटल SENSOR_DEVICE_ATTR(in4_max, S_IRUGO | S_IWUSR,
			  show_in_max, set_in_max, 4);
अटल SENSOR_DEVICE_ATTR(in4_min, S_IRUGO | S_IWUSR,
			  show_in_min, set_in_min, 4);
अटल SENSOR_DEVICE_ATTR(in5_input, S_IRUGO, show_in, शून्य, 5);
अटल SENSOR_DEVICE_ATTR(in5_max, S_IRUGO | S_IWUSR,
			  show_in_max, set_in_max, 5);
अटल SENSOR_DEVICE_ATTR(in5_min, S_IRUGO | S_IWUSR,
			  show_in_min, set_in_min, 5);
अटल SENSOR_DEVICE_ATTR(in6_input, S_IRUGO, show_in, शून्य, 6);
अटल SENSOR_DEVICE_ATTR(in6_max, S_IRUGO | S_IWUSR,
			  show_in_max, set_in_max, 6);
अटल SENSOR_DEVICE_ATTR(in6_min, S_IRUGO | S_IWUSR,
			  show_in_min, set_in_min, 6);
अटल SENSOR_DEVICE_ATTR(in7_input, S_IRUGO, show_in, शून्य, 7);
अटल SENSOR_DEVICE_ATTR(in7_max, S_IRUGO | S_IWUSR,
			  show_in_max, set_in_max, 7);
अटल SENSOR_DEVICE_ATTR(in7_min, S_IRUGO | S_IWUSR,
			  show_in_min, set_in_min, 7);
अटल SENSOR_DEVICE_ATTR(in8_input, S_IRUGO, show_in, शून्य, 8);
अटल SENSOR_DEVICE_ATTR(in8_max, S_IRUGO | S_IWUSR,
			  show_in_max, set_in_max, 8);
अटल SENSOR_DEVICE_ATTR(in8_min, S_IRUGO | S_IWUSR,
			  show_in_min, set_in_min, 8);
अटल SENSOR_DEVICE_ATTR(in9_input, S_IRUGO, show_in0, शून्य, 9);
अटल SENSOR_DEVICE_ATTR(in9_max, S_IRUGO | S_IWUSR,
			  show_in0_max, set_in0_max, 9);
अटल SENSOR_DEVICE_ATTR(in9_min, S_IRUGO | S_IWUSR,
			  show_in0_min, set_in0_min, 9);
अटल SENSOR_DEVICE_ATTR(in10_input, S_IRUGO, show_in0, शून्य, 10);
अटल SENSOR_DEVICE_ATTR(in10_max, S_IRUGO | S_IWUSR,
			  show_in0_max, set_in0_max, 10);
अटल SENSOR_DEVICE_ATTR(in10_min, S_IRUGO | S_IWUSR,
			  show_in0_min, set_in0_min, 10);

अटल SENSOR_DEVICE_ATTR(fan1_input, S_IRUGO, show_fan, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(fan1_min, S_IRUGO | S_IWUSR,
			  show_fan_min, set_fan_min, 0);
अटल SENSOR_DEVICE_ATTR(fan1_target, S_IRUGO | S_IWUSR,
			  show_fan_target, set_fan_target, 0);
अटल SENSOR_DEVICE_ATTR(fan2_input, S_IRUGO, show_fan, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(fan2_min, S_IRUGO | S_IWUSR,
			  show_fan_min, set_fan_min, 1);
अटल SENSOR_DEVICE_ATTR(fan2_target, S_IRUGO | S_IWUSR,
			  show_fan_target, set_fan_target, 1);
अटल SENSOR_DEVICE_ATTR(fan3_input, S_IRUGO, show_fan, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(fan3_min, S_IRUGO | S_IWUSR,
			  show_fan_min, set_fan_min, 2);
अटल SENSOR_DEVICE_ATTR(fan3_target, S_IRUGO | S_IWUSR,
			  show_fan_target, set_fan_target, 2);

अटल SENSOR_DEVICE_ATTR(temp1_input, S_IRUGO, show_temp, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(temp1_max, S_IRUGO | S_IWUSR,
		    show_temp_max, set_temp_max, 0);
अटल SENSOR_DEVICE_ATTR(temp1_max_hyst, S_IRUGO | S_IWUSR,
		    show_temp_hyst, set_temp_hyst, 0);
अटल SENSOR_DEVICE_ATTR(temp1_type, S_IRUGO, show_temp_type, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(temp2_input, S_IRUGO, show_temp, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(temp2_max, S_IRUGO | S_IWUSR,
		    show_temp_max, set_temp_max, 1);
अटल SENSOR_DEVICE_ATTR(temp2_max_hyst, S_IRUGO | S_IWUSR,
		    show_temp_hyst, set_temp_hyst, 1);
अटल SENSOR_DEVICE_ATTR(temp2_type, S_IRUGO, show_temp_type, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(temp3_input, S_IRUGO, show_temp, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(temp3_max, S_IRUGO | S_IWUSR,
		    show_temp_max, set_temp_max, 2);
अटल SENSOR_DEVICE_ATTR(temp3_max_hyst, S_IRUGO | S_IWUSR,
		    show_temp_hyst, set_temp_hyst, 2);
अटल SENSOR_DEVICE_ATTR(temp3_type, S_IRUGO, show_temp_type, शून्य, 2);

/*
 * pwm (value) files are created पढ़ो-only, ग_लिखो permission is
 * then added or हटाओd dynamically as needed
 */
अटल SENSOR_DEVICE_ATTR(pwm1, S_IRUGO, show_pwm, set_pwm, 0);
अटल SENSOR_DEVICE_ATTR(pwm1_enable, S_IRUGO | S_IWUSR,
			  show_pwm_enable, set_pwm_enable, 0);
अटल SENSOR_DEVICE_ATTR(pwm1_freq, S_IRUGO | S_IWUSR,
			  show_pwm_freq, set_pwm_freq, 0);
अटल SENSOR_DEVICE_ATTR(pwm1_mode, S_IRUGO, show_pwm_mode, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(pwm2, S_IRUGO, show_pwm, set_pwm, 1);
अटल SENSOR_DEVICE_ATTR(pwm2_enable, S_IRUGO | S_IWUSR,
			  show_pwm_enable, set_pwm_enable, 1);
अटल SENSOR_DEVICE_ATTR(pwm2_freq, S_IRUGO | S_IWUSR,
			  show_pwm_freq, set_pwm_freq, 1);
अटल SENSOR_DEVICE_ATTR(pwm2_mode, S_IRUGO, show_pwm_mode, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(pwm3, S_IRUGO, show_pwm, set_pwm, 2);
अटल SENSOR_DEVICE_ATTR(pwm3_enable, S_IRUGO | S_IWUSR,
			  show_pwm_enable, set_pwm_enable, 2);
अटल SENSOR_DEVICE_ATTR(pwm3_freq, S_IRUGO | S_IWUSR,
			  show_pwm_freq, set_pwm_freq, 2);
अटल SENSOR_DEVICE_ATTR(pwm3_mode, S_IRUGO, show_pwm_mode, शून्य, 2);

अटल SENSOR_DEVICE_ATTR_2(pwm1_स्वतः_poपूर्णांक1_temp, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_temp, set_pwm_स्वतः_poपूर्णांक_temp,
			    0, 0);
अटल SENSOR_DEVICE_ATTR_2(pwm1_स्वतः_poपूर्णांक1_fan, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_fan, set_pwm_स्वतः_poपूर्णांक_fan,
			    0, 0);
अटल SENSOR_DEVICE_ATTR_2(pwm1_स्वतः_poपूर्णांक2_temp, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_temp, set_pwm_स्वतः_poपूर्णांक_temp,
			    0, 1);
अटल SENSOR_DEVICE_ATTR_2(pwm1_स्वतः_poपूर्णांक2_fan, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_fan, set_pwm_स्वतः_poपूर्णांक_fan,
			    0, 1);
अटल SENSOR_DEVICE_ATTR_2(pwm1_स्वतः_poपूर्णांक3_temp, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_temp, set_pwm_स्वतः_poपूर्णांक_temp,
			    0, 2);
अटल SENSOR_DEVICE_ATTR_2(pwm1_स्वतः_poपूर्णांक3_fan, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_fan, set_pwm_स्वतः_poपूर्णांक_fan,
			    0, 2);

अटल SENSOR_DEVICE_ATTR_2(pwm2_स्वतः_poपूर्णांक1_temp, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_temp, set_pwm_स्वतः_poपूर्णांक_temp,
			    1, 0);
अटल SENSOR_DEVICE_ATTR_2(pwm2_स्वतः_poपूर्णांक1_fan, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_fan, set_pwm_स्वतः_poपूर्णांक_fan,
			    1, 0);
अटल SENSOR_DEVICE_ATTR_2(pwm2_स्वतः_poपूर्णांक2_temp, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_temp, set_pwm_स्वतः_poपूर्णांक_temp,
			    1, 1);
अटल SENSOR_DEVICE_ATTR_2(pwm2_स्वतः_poपूर्णांक2_fan, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_fan, set_pwm_स्वतः_poपूर्णांक_fan,
			    1, 1);
अटल SENSOR_DEVICE_ATTR_2(pwm2_स्वतः_poपूर्णांक3_temp, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_temp, set_pwm_स्वतः_poपूर्णांक_temp,
			    1, 2);
अटल SENSOR_DEVICE_ATTR_2(pwm2_स्वतः_poपूर्णांक3_fan, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_fan, set_pwm_स्वतः_poपूर्णांक_fan,
			    1, 2);

अटल SENSOR_DEVICE_ATTR_2(pwm3_स्वतः_poपूर्णांक1_temp, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_temp, set_pwm_स्वतः_poपूर्णांक_temp,
			    2, 0);
अटल SENSOR_DEVICE_ATTR_2(pwm3_स्वतः_poपूर्णांक1_fan, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_fan, set_pwm_स्वतः_poपूर्णांक_fan,
			    2, 0);
अटल SENSOR_DEVICE_ATTR_2(pwm3_स्वतः_poपूर्णांक2_temp, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_temp, set_pwm_स्वतः_poपूर्णांक_temp,
			    2, 1);
अटल SENSOR_DEVICE_ATTR_2(pwm3_स्वतः_poपूर्णांक2_fan, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_fan, set_pwm_स्वतः_poपूर्णांक_fan,
			    2, 1);
अटल SENSOR_DEVICE_ATTR_2(pwm3_स्वतः_poपूर्णांक3_temp, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_temp, set_pwm_स्वतः_poपूर्णांक_temp,
			    2, 2);
अटल SENSOR_DEVICE_ATTR_2(pwm3_स्वतः_poपूर्णांक3_fan, S_IRUGO | S_IWUSR,
			    show_pwm_स्वतः_poपूर्णांक_fan, set_pwm_स्वतः_poपूर्णांक_fan,
			    2, 2);

अटल SENSOR_DEVICE_ATTR(in0_alarm, S_IRUGO, show_alarm, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(in1_alarm, S_IRUGO, show_alarm, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(in2_alarm, S_IRUGO, show_alarm, शून्य, 2);
अटल SENSOR_DEVICE_ATTR(in3_alarm, S_IRUGO, show_alarm, शून्य, 3);
अटल SENSOR_DEVICE_ATTR(in4_alarm, S_IRUGO, show_alarm, शून्य, 4);
अटल SENSOR_DEVICE_ATTR(in5_alarm, S_IRUGO, show_alarm, शून्य, 5);
अटल SENSOR_DEVICE_ATTR(in6_alarm, S_IRUGO, show_alarm, शून्य, 6);
अटल SENSOR_DEVICE_ATTR(in7_alarm, S_IRUGO, show_alarm, शून्य, 7);
अटल SENSOR_DEVICE_ATTR(in8_alarm, S_IRUGO, show_alarm, शून्य, 8);
अटल SENSOR_DEVICE_ATTR(in9_alarm, S_IRUGO, show_alarm, शून्य, 9);
अटल SENSOR_DEVICE_ATTR(in10_alarm, S_IRUGO, show_alarm, शून्य, 10);
अटल SENSOR_DEVICE_ATTR(temp1_alarm, S_IRUGO, show_alarm, शून्य, 11);
अटल SENSOR_DEVICE_ATTR(temp2_alarm, S_IRUGO, show_alarm, शून्य, 12);
अटल SENSOR_DEVICE_ATTR(temp3_alarm, S_IRUGO, show_alarm, शून्य, 13);
अटल SENSOR_DEVICE_ATTR(fan1_alarm, S_IRUGO, show_alarm, शून्य, 16);
अटल SENSOR_DEVICE_ATTR(fan2_alarm, S_IRUGO, show_alarm, शून्य, 17);
अटल SENSOR_DEVICE_ATTR(fan3_alarm, S_IRUGO, show_alarm, शून्य, 18);
अटल DEVICE_ATTR_RO(alarms_in);
अटल DEVICE_ATTR_RO(alarms_fan);
अटल DEVICE_ATTR_RO(alarms_temp);

अटल DEVICE_ATTR_RO(name);

अटल काष्ठा attribute *f71805f_attributes[] = अणु
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
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in6_max.dev_attr.attr,
	&sensor_dev_attr_in6_min.dev_attr.attr,
	&sensor_dev_attr_in7_input.dev_attr.attr,
	&sensor_dev_attr_in7_max.dev_attr.attr,
	&sensor_dev_attr_in7_min.dev_attr.attr,

	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan1_target.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_target.dev_attr.attr,
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan3_min.dev_attr.attr,
	&sensor_dev_attr_fan3_alarm.dev_attr.attr,
	&sensor_dev_attr_fan3_target.dev_attr.attr,

	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm1_enable.dev_attr.attr,
	&sensor_dev_attr_pwm1_mode.dev_attr.attr,
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&sensor_dev_attr_pwm2_enable.dev_attr.attr,
	&sensor_dev_attr_pwm2_mode.dev_attr.attr,
	&sensor_dev_attr_pwm3.dev_attr.attr,
	&sensor_dev_attr_pwm3_enable.dev_attr.attr,
	&sensor_dev_attr_pwm3_mode.dev_attr.attr,

	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_type.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_type.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp3_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp3_type.dev_attr.attr,

	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_fan.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक2_fan.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक3_fan.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक1_fan.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक2_fan.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक3_fan.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक1_fan.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक2_fan.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक3_temp.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक3_fan.dev_attr.attr,

	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,
	&sensor_dev_attr_in5_alarm.dev_attr.attr,
	&sensor_dev_attr_in6_alarm.dev_attr.attr,
	&sensor_dev_attr_in7_alarm.dev_attr.attr,
	&dev_attr_alarms_in.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_alarm.dev_attr.attr,
	&dev_attr_alarms_temp.attr,
	&dev_attr_alarms_fan.attr,

	&dev_attr_name.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group f71805f_group = अणु
	.attrs = f71805f_attributes,
पूर्ण;

अटल काष्ठा attribute *f71805f_attributes_optin[4][5] = अणु
	अणु
		&sensor_dev_attr_in4_input.dev_attr.attr,
		&sensor_dev_attr_in4_max.dev_attr.attr,
		&sensor_dev_attr_in4_min.dev_attr.attr,
		&sensor_dev_attr_in4_alarm.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_in8_input.dev_attr.attr,
		&sensor_dev_attr_in8_max.dev_attr.attr,
		&sensor_dev_attr_in8_min.dev_attr.attr,
		&sensor_dev_attr_in8_alarm.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_in9_input.dev_attr.attr,
		&sensor_dev_attr_in9_max.dev_attr.attr,
		&sensor_dev_attr_in9_min.dev_attr.attr,
		&sensor_dev_attr_in9_alarm.dev_attr.attr,
		शून्य
	पूर्ण, अणु
		&sensor_dev_attr_in10_input.dev_attr.attr,
		&sensor_dev_attr_in10_max.dev_attr.attr,
		&sensor_dev_attr_in10_min.dev_attr.attr,
		&sensor_dev_attr_in10_alarm.dev_attr.attr,
		शून्य
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा attribute_group f71805f_group_optin[4] = अणु
	अणु .attrs = f71805f_attributes_optin[0] पूर्ण,
	अणु .attrs = f71805f_attributes_optin[1] पूर्ण,
	अणु .attrs = f71805f_attributes_optin[2] पूर्ण,
	अणु .attrs = f71805f_attributes_optin[3] पूर्ण,
पूर्ण;

/*
 * We करोn't include pwm_freq files in the arrays above, because they must be
 * created conditionally (only अगर pwm_mode is 1 == PWM)
 */
अटल काष्ठा attribute *f71805f_attributes_pwm_freq[] = अणु
	&sensor_dev_attr_pwm1_freq.dev_attr.attr,
	&sensor_dev_attr_pwm2_freq.dev_attr.attr,
	&sensor_dev_attr_pwm3_freq.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group f71805f_group_pwm_freq = अणु
	.attrs = f71805f_attributes_pwm_freq,
पूर्ण;

/* We also need an indexed access to pwmN files to toggle writability */
अटल काष्ठा attribute *f71805f_attr_pwm[] = अणु
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&sensor_dev_attr_pwm3.dev_attr.attr,
पूर्ण;

/*
 * Device registration and initialization
 */

अटल व्योम f71805f_init_device(काष्ठा f71805f_data *data)
अणु
	u8 reg;
	पूर्णांक i;

	reg = f71805f_पढ़ो8(data, F71805F_REG_START);
	अगर ((reg & 0x41) != 0x01) अणु
		pr_debug("Starting monitoring operations\n");
		f71805f_ग_लिखो8(data, F71805F_REG_START, (reg | 0x01) & ~0x40);
	पूर्ण

	/*
	 * Fan monitoring can be disabled. If it is, we won't be polling
	 * the रेजिस्टर values, and won't create the related sysfs files.
	 */
	क्रम (i = 0; i < 3; i++) अणु
		data->fan_ctrl[i] = f71805f_पढ़ो8(data,
						  F71805F_REG_FAN_CTRL(i));
		/*
		 * Clear latch full bit, अन्यथा "speed mode" fan speed control
		 * करोesn't work
		 */
		अगर (data->fan_ctrl[i] & FAN_CTRL_LATCH_FULL) अणु
			data->fan_ctrl[i] &= ~FAN_CTRL_LATCH_FULL;
			f71805f_ग_लिखो8(data, F71805F_REG_FAN_CTRL(i),
				       data->fan_ctrl[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक f71805f_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा f71805f_sio_data *sio_data = dev_get_platdata(&pdev->dev);
	काष्ठा f71805f_data *data;
	काष्ठा resource *res;
	पूर्णांक i, err;

	अटल स्थिर अक्षर * स्थिर names[] = अणु
		"f71805f",
		"f71872f",
	पूर्ण;

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा f71805f_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!devm_request_region(&pdev->dev, res->start + ADDR_REG_OFFSET, 2,
				 DRVNAME)) अणु
		dev_err(&pdev->dev, "Failed to request region 0x%lx-0x%lx\n",
			(अचिन्हित दीर्घ)(res->start + ADDR_REG_OFFSET),
			(अचिन्हित दीर्घ)(res->start + ADDR_REG_OFFSET + 1));
		वापस -EBUSY;
	पूर्ण
	data->addr = res->start;
	data->name = names[sio_data->kind];
	mutex_init(&data->update_lock);

	platक्रमm_set_drvdata(pdev, data);

	/* Some voltage inमाला_दो depend on chip model and configuration */
	चयन (sio_data->kind) अणु
	हाल f71805f:
		data->has_in = 0x1ff;
		अवरोध;
	हाल f71872f:
		data->has_in = 0x6ef;
		अगर (sio_data->fnsel1 & 0x01)
			data->has_in |= (1 << 4); /* in4 */
		अगर (sio_data->fnsel1 & 0x02)
			data->has_in |= (1 << 8); /* in8 */
		अवरोध;
	पूर्ण

	/* Initialize the F71805F chip */
	f71805f_init_device(data);

	/* Register sysfs पूर्णांकerface files */
	err = sysfs_create_group(&pdev->dev.kobj, &f71805f_group);
	अगर (err)
		वापस err;
	अगर (data->has_in & (1 << 4)) अणु /* in4 */
		err = sysfs_create_group(&pdev->dev.kobj,
					 &f71805f_group_optin[0]);
		अगर (err)
			जाओ निकास_हटाओ_files;
	पूर्ण
	अगर (data->has_in & (1 << 8)) अणु /* in8 */
		err = sysfs_create_group(&pdev->dev.kobj,
					 &f71805f_group_optin[1]);
		अगर (err)
			जाओ निकास_हटाओ_files;
	पूर्ण
	अगर (data->has_in & (1 << 9)) अणु /* in9 (F71872F/FG only) */
		err = sysfs_create_group(&pdev->dev.kobj,
					 &f71805f_group_optin[2]);
		अगर (err)
			जाओ निकास_हटाओ_files;
	पूर्ण
	अगर (data->has_in & (1 << 10)) अणु /* in9 (F71872F/FG only) */
		err = sysfs_create_group(&pdev->dev.kobj,
					 &f71805f_group_optin[3]);
		अगर (err)
			जाओ निकास_हटाओ_files;
	पूर्ण
	क्रम (i = 0; i < 3; i++) अणु
		/* If control mode is PWM, create pwm_freq file */
		अगर (!(data->fan_ctrl[i] & FAN_CTRL_DC_MODE)) अणु
			err = sysfs_create_file(&pdev->dev.kobj,
						f71805f_attributes_pwm_freq[i]);
			अगर (err)
				जाओ निकास_हटाओ_files;
		पूर्ण
		/* If PWM is in manual mode, add ग_लिखो permission */
		अगर (data->fan_ctrl[i] & FAN_CTRL_MODE_MANUAL) अणु
			err = sysfs_chmod_file(&pdev->dev.kobj,
					       f71805f_attr_pwm[i],
					       S_IRUGO | S_IWUSR);
			अगर (err) अणु
				dev_err(&pdev->dev, "chmod +w pwm%d failed\n",
					i + 1);
				जाओ निकास_हटाओ_files;
			पूर्ण
		पूर्ण
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(&pdev->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		dev_err(&pdev->dev, "Class registration failed (%d)\n", err);
		जाओ निकास_हटाओ_files;
	पूर्ण

	वापस 0;

निकास_हटाओ_files:
	sysfs_हटाओ_group(&pdev->dev.kobj, &f71805f_group);
	क्रम (i = 0; i < 4; i++)
		sysfs_हटाओ_group(&pdev->dev.kobj, &f71805f_group_optin[i]);
	sysfs_हटाओ_group(&pdev->dev.kobj, &f71805f_group_pwm_freq);
	वापस err;
पूर्ण

अटल पूर्णांक f71805f_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा f71805f_data *data = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	sysfs_हटाओ_group(&pdev->dev.kobj, &f71805f_group);
	क्रम (i = 0; i < 4; i++)
		sysfs_हटाओ_group(&pdev->dev.kobj, &f71805f_group_optin[i]);
	sysfs_हटाओ_group(&pdev->dev.kobj, &f71805f_group_pwm_freq);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver f71805f_driver = अणु
	.driver = अणु
		.name	= DRVNAME,
	पूर्ण,
	.probe		= f71805f_probe,
	.हटाओ		= f71805f_हटाओ,
पूर्ण;

अटल पूर्णांक __init f71805f_device_add(अचिन्हित लघु address,
				     स्थिर काष्ठा f71805f_sio_data *sio_data)
अणु
	काष्ठा resource res = अणु
		.start	= address,
		.end	= address + REGION_LENGTH - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण;
	पूर्णांक err;

	pdev = platक्रमm_device_alloc(DRVNAME, address);
	अगर (!pdev) अणु
		err = -ENOMEM;
		pr_err("Device allocation failed\n");
		जाओ निकास;
	पूर्ण

	res.name = pdev->name;
	err = acpi_check_resource_conflict(&res);
	अगर (err)
		जाओ निकास_device_put;

	err = platक्रमm_device_add_resources(pdev, &res, 1);
	अगर (err) अणु
		pr_err("Device resource addition failed (%d)\n", err);
		जाओ निकास_device_put;
	पूर्ण

	err = platक्रमm_device_add_data(pdev, sio_data,
				       माप(काष्ठा f71805f_sio_data));
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

अटल पूर्णांक __init f71805f_find(पूर्णांक sioaddr, अचिन्हित लघु *address,
			       काष्ठा f71805f_sio_data *sio_data)
अणु
	पूर्णांक err;
	u16 devid;

	अटल स्थिर अक्षर * स्थिर names[] = अणु
		"F71805F/FG",
		"F71872F/FG or F71806F/FG",
	पूर्ण;

	err = superio_enter(sioaddr);
	अगर (err)
		वापस err;

	err = -ENODEV;
	devid = superio_inw(sioaddr, SIO_REG_MANID);
	अगर (devid != SIO_FINTEK_ID)
		जाओ निकास;

	devid = क्रमce_id ? क्रमce_id : superio_inw(sioaddr, SIO_REG_DEVID);
	चयन (devid) अणु
	हाल SIO_F71805F_ID:
		sio_data->kind = f71805f;
		अवरोध;
	हाल SIO_F71872F_ID:
		sio_data->kind = f71872f;
		sio_data->fnsel1 = superio_inb(sioaddr, SIO_REG_FNSEL1);
		अवरोध;
	शेष:
		pr_info("Unsupported Fintek device, skipping\n");
		जाओ निकास;
	पूर्ण

	superio_select(sioaddr, F71805F_LD_HWM);
	अगर (!(superio_inb(sioaddr, SIO_REG_ENABLE) & 0x01)) अणु
		pr_warn("Device not activated, skipping\n");
		जाओ निकास;
	पूर्ण

	*address = superio_inw(sioaddr, SIO_REG_ADDR);
	अगर (*address == 0) अणु
		pr_warn("Base address not set, skipping\n");
		जाओ निकास;
	पूर्ण
	*address &= ~(REGION_LENGTH - 1);	/* Ignore 3 LSB */

	err = 0;
	pr_info("Found %s chip at %#x, revision %u\n",
		names[sio_data->kind], *address,
		superio_inb(sioaddr, SIO_REG_DEVREV));

निकास:
	superio_निकास(sioaddr);
	वापस err;
पूर्ण

अटल पूर्णांक __init f71805f_init(व्योम)
अणु
	पूर्णांक err;
	अचिन्हित लघु address;
	काष्ठा f71805f_sio_data sio_data;

	अगर (f71805f_find(0x2e, &address, &sio_data)
	 && f71805f_find(0x4e, &address, &sio_data))
		वापस -ENODEV;

	err = platक्रमm_driver_रेजिस्टर(&f71805f_driver);
	अगर (err)
		जाओ निकास;

	/* Sets global pdev as a side effect */
	err = f71805f_device_add(address, &sio_data);
	अगर (err)
		जाओ निकास_driver;

	वापस 0;

निकास_driver:
	platक्रमm_driver_unरेजिस्टर(&f71805f_driver);
निकास:
	वापस err;
पूर्ण

अटल व्योम __निकास f71805f_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(pdev);
	platक्रमm_driver_unरेजिस्टर(&f71805f_driver);
पूर्ण

MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("F71805F/F71872F hardware monitoring driver");

module_init(f71805f_init);
module_निकास(f71805f_निकास);
