<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * w83793.c - Linux kernel driver क्रम hardware monitoring
 * Copyright (C) 2006 Winbond Electronics Corp.
 *	      Yuan Mu
 *	      Ruकरोlf Marek <r.marek@assembler.cz>
 * Copyright (C) 2009-2010 Sven Anders <anders@anduras.de>, ANDURAS AG.
 *		Watchकरोg driver part
 *		(Based partially on fschmd driver,
 *		 Copyright 2007-2008 by Hans de Goede)
 */

/*
 * Supports following chips:
 *
 * Chip	#vin	#fanin	#pwm	#temp	wchipid	vendid	i2c	ISA
 * w83793	10	12	8	6	0x7b	0x5ca3	yes	no
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
#समावेश <linux/fs.h>
#समावेश <linux/watchकरोg.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kref.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/jअगरfies.h>

/* Default values */
#घोषणा WATCHDOG_TIMEOUT 2	/* 2 minute शेष समयout */

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
MODULE_PARM_DESC(reset, "Set to 1 to reset chip, not recommended");

अटल पूर्णांक समयout = WATCHDOG_TIMEOUT;	/* शेष समयout in minutes */
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout,
	"Watchdog timeout in minutes. 2<= timeout <=255 (default="
				__MODULE_STRING(WATCHDOG_TIMEOUT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

/*
 * Address 0x00, 0x0d, 0x0e, 0x0f in all three banks are reserved
 * as ID, Bank Select रेजिस्टरs
 */
#घोषणा W83793_REG_BANKSEL		0x00
#घोषणा W83793_REG_VENDORID		0x0d
#घोषणा W83793_REG_CHIPID		0x0e
#घोषणा W83793_REG_DEVICEID		0x0f

#घोषणा W83793_REG_CONFIG		0x40
#घोषणा W83793_REG_MFC			0x58
#घोषणा W83793_REG_FANIN_CTRL		0x5c
#घोषणा W83793_REG_FANIN_SEL		0x5d
#घोषणा W83793_REG_I2C_ADDR		0x0b
#घोषणा W83793_REG_I2C_SUBADDR		0x0c
#घोषणा W83793_REG_VID_INA		0x05
#घोषणा W83793_REG_VID_INB		0x06
#घोषणा W83793_REG_VID_LATCHA		0x07
#घोषणा W83793_REG_VID_LATCHB		0x08
#घोषणा W83793_REG_VID_CTRL		0x59

#घोषणा W83793_REG_WDT_LOCK		0x01
#घोषणा W83793_REG_WDT_ENABLE		0x02
#घोषणा W83793_REG_WDT_STATUS		0x03
#घोषणा W83793_REG_WDT_TIMEOUT		0x04

अटल u16 W83793_REG_TEMP_MODE[2] = अणु 0x5e, 0x5f पूर्ण;

#घोषणा TEMP_READ	0
#घोषणा TEMP_CRIT	1
#घोषणा TEMP_CRIT_HYST	2
#घोषणा TEMP_WARN	3
#घोषणा TEMP_WARN_HYST	4
/*
 * only crit and crit_hyst affect real-समय alarm status
 * current crit crit_hyst warn warn_hyst
 */
अटल u16 W83793_REG_TEMP[][5] = अणु
	अणु0x1c, 0x78, 0x79, 0x7a, 0x7bपूर्ण,
	अणु0x1d, 0x7c, 0x7d, 0x7e, 0x7fपूर्ण,
	अणु0x1e, 0x80, 0x81, 0x82, 0x83पूर्ण,
	अणु0x1f, 0x84, 0x85, 0x86, 0x87पूर्ण,
	अणु0x20, 0x88, 0x89, 0x8a, 0x8bपूर्ण,
	अणु0x21, 0x8c, 0x8d, 0x8e, 0x8fपूर्ण,
पूर्ण;

#घोषणा W83793_REG_TEMP_LOW_BITS	0x22

#घोषणा W83793_REG_BEEP(index)		(0x53 + (index))
#घोषणा W83793_REG_ALARM(index)		(0x4b + (index))

#घोषणा W83793_REG_CLR_CHASSIS		0x4a	/* SMI MASK4 */
#घोषणा W83793_REG_IRQ_CTRL		0x50
#घोषणा W83793_REG_OVT_CTRL		0x51
#घोषणा W83793_REG_OVT_BEEP		0x52

#घोषणा IN_READ				0
#घोषणा IN_MAX				1
#घोषणा IN_LOW				2
अटल स्थिर u16 W83793_REG_IN[][3] = अणु
	/* Current, High, Low */
	अणु0x10, 0x60, 0x61पूर्ण,	/* Vcore A	*/
	अणु0x11, 0x62, 0x63पूर्ण,	/* Vcore B	*/
	अणु0x12, 0x64, 0x65पूर्ण,	/* Vtt		*/
	अणु0x14, 0x6a, 0x6bपूर्ण,	/* VSEN1	*/
	अणु0x15, 0x6c, 0x6dपूर्ण,	/* VSEN2	*/
	अणु0x16, 0x6e, 0x6fपूर्ण,	/* +3VSEN	*/
	अणु0x17, 0x70, 0x71पूर्ण,	/* +12VSEN	*/
	अणु0x18, 0x72, 0x73पूर्ण,	/* 5VDD		*/
	अणु0x19, 0x74, 0x75पूर्ण,	/* 5VSB		*/
	अणु0x1a, 0x76, 0x77पूर्ण,	/* VBAT		*/
पूर्ण;

/* Low Bits of Vcore A/B Vtt Read/High/Low */
अटल स्थिर u16 W83793_REG_IN_LOW_BITS[] = अणु 0x1b, 0x68, 0x69 पूर्ण;
अटल u8 scale_in[] = अणु 2, 2, 2, 16, 16, 16, 8, 24, 24, 16 पूर्ण;
अटल u8 scale_in_add[] = अणु 0, 0, 0, 0, 0, 0, 0, 150, 150, 0 पूर्ण;

#घोषणा W83793_REG_FAN(index)		(0x23 + 2 * (index))	/* High byte */
#घोषणा W83793_REG_FAN_MIN(index)	(0x90 + 2 * (index))	/* High byte */

#घोषणा W83793_REG_PWM_DEFAULT		0xb2
#घोषणा W83793_REG_PWM_ENABLE		0x207
#घोषणा W83793_REG_PWM_UPTIME		0xc3	/* Unit in 0.1 second */
#घोषणा W83793_REG_PWM_DOWNTIME		0xc4	/* Unit in 0.1 second */
#घोषणा W83793_REG_TEMP_CRITICAL	0xc5

#घोषणा PWM_DUTY			0
#घोषणा PWM_START			1
#घोषणा PWM_NONSTOP			2
#घोषणा PWM_STOP_TIME			3
#घोषणा W83793_REG_PWM(index, nr)	(((nr) == 0 ? 0xb3 : \
					 (nr) == 1 ? 0x220 : 0x218) + (index))

/* bit field, fan1 is bit0, fan2 is bit1 ... */
#घोषणा W83793_REG_TEMP_FAN_MAP(index)	(0x201 + (index))
#घोषणा W83793_REG_TEMP_TOL(index)	(0x208 + (index))
#घोषणा W83793_REG_TEMP_CRUISE(index)	(0x210 + (index))
#घोषणा W83793_REG_PWM_STOP_TIME(index)	(0x228 + (index))
#घोषणा W83793_REG_SF2_TEMP(index, nr)	(0x230 + ((index) << 4) + (nr))
#घोषणा W83793_REG_SF2_PWM(index, nr)	(0x238 + ((index) << 4) + (nr))

अटल अंतरभूत अचिन्हित दीर्घ FAN_FROM_REG(u16 val)
अणु
	अगर ((val >= 0xfff) || (val == 0))
		वापस	0;
	वापस 1350000UL / val;
पूर्ण

अटल अंतरभूत u16 FAN_TO_REG(दीर्घ rpm)
अणु
	अगर (rpm <= 0)
		वापस 0x0fff;
	वापस clamp_val((1350000 + (rpm >> 1)) / rpm, 1, 0xffe);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ TIME_FROM_REG(u8 reg)
अणु
	वापस reg * 100;
पूर्ण

अटल अंतरभूत u8 TIME_TO_REG(अचिन्हित दीर्घ val)
अणु
	वापस clamp_val((val + 50) / 100, 0, 0xff);
पूर्ण

अटल अंतरभूत दीर्घ TEMP_FROM_REG(s8 reg)
अणु
	वापस reg * 1000;
पूर्ण

अटल अंतरभूत s8 TEMP_TO_REG(दीर्घ val, s8 min, s8 max)
अणु
	वापस clamp_val((val + (val < 0 ? -500 : 500)) / 1000, min, max);
पूर्ण

काष्ठा w83793_data अणु
	काष्ठा i2c_client *lm75[2];
	काष्ठा device *hwmon_dev;
	काष्ठा mutex update_lock;
	अक्षर valid;			/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */
	अचिन्हित दीर्घ last_nonअस्थिर;	/* In jअगरfies, last समय we update the
					 * nonअस्थिर रेजिस्टरs
					 */

	u8 bank;
	u8 vrm;
	u8 vid[2];
	u8 in[10][3];		/* Register value, पढ़ो/high/low */
	u8 in_low_bits[3];	/* Additional resolution क्रम VCore A/B Vtt */

	u16 has_fan;		/* Only fan1- fan5 has own pins */
	u16 fan[12];		/* Register value combine */
	u16 fan_min[12];	/* Register value combine */

	s8 temp[6][5];		/* current, crit, crit_hyst,warn, warn_hyst */
	u8 temp_low_bits;	/* Additional resolution TD1-TD4 */
	u8 temp_mode[2];	/* byte 0: Temp D1-D4 mode each has 2 bits
				 * byte 1: Temp R1,R2 mode, each has 1 bit
				 */
	u8 temp_critical;	/* If reached all fan will be at full speed */
	u8 temp_fan_map[6];	/* Temp controls which pwm fan, bit field */

	u8 has_pwm;
	u8 has_temp;
	u8 has_vid;
	u8 pwm_enable;		/* Register value, each Temp has 1 bit */
	u8 pwm_upसमय;		/* Register value */
	u8 pwm_करोwnसमय;	/* Register value */
	u8 pwm_शेष;		/* All fan शेष pwm, next घातeron valid */
	u8 pwm[8][3];		/* Register value */
	u8 pwm_stop_समय[8];
	u8 temp_cruise[6];

	u8 alarms[5];		/* realसमय status रेजिस्टरs */
	u8 beeps[5];
	u8 beep_enable;
	u8 tolerance[3];	/* Temp tolerance(Smart Fan I/II) */
	u8 sf2_pwm[6][7];	/* Smart FanII: Fan duty cycle */
	u8 sf2_temp[6][7];	/* Smart FanII: Temp level poपूर्णांक */

	/* watchकरोg */
	काष्ठा i2c_client *client;
	काष्ठा mutex watchकरोg_lock;
	काष्ठा list_head list; /* member of the watchकरोg_data_list */
	काष्ठा kref kref;
	काष्ठा miscdevice watchकरोg_miscdev;
	अचिन्हित दीर्घ watchकरोg_is_खोलो;
	अक्षर watchकरोg_expect_बंद;
	अक्षर watchकरोg_name[10]; /* must be unique to aव्योम sysfs conflict */
	अचिन्हित पूर्णांक watchकरोg_caused_reboot;
	पूर्णांक watchकरोg_समयout; /* watchकरोg समयout in minutes */
पूर्ण;

/*
 * Somewhat ugly :( global data poपूर्णांकer list with all devices, so that
 * we can find our device data as when using misc_रेजिस्टर. There is no
 * other method to get to one's device data from the खोलो file-op and
 * क्रम usage in the reboot notअगरier callback.
 */
अटल LIST_HEAD(watchकरोg_data_list);

/* Note this lock not only protect list access, but also data.kref access */
अटल DEFINE_MUTEX(watchकरोg_data_mutex);

/*
 * Release our data काष्ठा when we're detached from the i2c client *and* all
 * references to our watchकरोg device are released
 */
अटल व्योम w83793_release_resources(काष्ठा kref *ref)
अणु
	काष्ठा w83793_data *data = container_of(ref, काष्ठा w83793_data, kref);
	kमुक्त(data);
पूर्ण

अटल u8 w83793_पढ़ो_value(काष्ठा i2c_client *client, u16 reg);
अटल पूर्णांक w83793_ग_लिखो_value(काष्ठा i2c_client *client, u16 reg, u8 value);
अटल पूर्णांक w83793_probe(काष्ठा i2c_client *client);
अटल पूर्णांक w83793_detect(काष्ठा i2c_client *client,
			 काष्ठा i2c_board_info *info);
अटल पूर्णांक w83793_हटाओ(काष्ठा i2c_client *client);
अटल व्योम w83793_init_client(काष्ठा i2c_client *client);
अटल व्योम w83793_update_nonअस्थिर(काष्ठा device *dev);
अटल काष्ठा w83793_data *w83793_update_device(काष्ठा device *dev);

अटल स्थिर काष्ठा i2c_device_id w83793_id[] = अणु
	अणु "w83793", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, w83793_id);

अटल काष्ठा i2c_driver w83793_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		   .name = "w83793",
	पूर्ण,
	.probe_new	= w83793_probe,
	.हटाओ		= w83793_हटाओ,
	.id_table	= w83793_id,
	.detect		= w83793_detect,
	.address_list	= normal_i2c,
पूर्ण;

अटल sमाप_प्रकार
vrm_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83793_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", data->vrm);
पूर्ण

अटल sमाप_प्रकार
show_vid(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83793_data *data = w83793_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक index = sensor_attr->index;

	वापस प्र_लिखो(buf, "%d\n", vid_from_reg(data->vid[index], data->vrm));
पूर्ण

अटल sमाप_प्रकार
vrm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा w83793_data *data = dev_get_drvdata(dev);
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

#घोषणा ALARM_STATUS			0
#घोषणा BEEP_ENABLE			1
अटल sमाप_प्रकार
show_alarm_beep(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83793_data *data = w83793_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index >> 3;
	पूर्णांक bit = sensor_attr->index & 0x07;
	u8 val;

	अगर (nr == ALARM_STATUS) अणु
		val = (data->alarms[index] >> (bit)) & 1;
	पूर्ण अन्यथा अणु		/* BEEP_ENABLE */
		val = (data->beeps[index] >> (bit)) & 1;
	पूर्ण

	वापस प्र_लिखो(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार
store_beep(काष्ठा device *dev, काष्ठा device_attribute *attr,
	   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83793_data *data = i2c_get_clientdata(client);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक index = sensor_attr->index >> 3;
	पूर्णांक shअगरt = sensor_attr->index & 0x07;
	u8 beep_bit = 1 << shअगरt;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val > 1)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->beeps[index] = w83793_पढ़ो_value(client, W83793_REG_BEEP(index));
	data->beeps[index] &= ~beep_bit;
	data->beeps[index] |= val << shअगरt;
	w83793_ग_लिखो_value(client, W83793_REG_BEEP(index), data->beeps[index]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_beep_enable(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83793_data *data = w83793_update_device(dev);
	वापस प्र_लिखो(buf, "%u\n", (data->beep_enable >> 1) & 0x01);
पूर्ण

अटल sमाप_प्रकार
store_beep_enable(काष्ठा device *dev, काष्ठा device_attribute *attr,
		  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83793_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	अगर (val > 1)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->beep_enable = w83793_पढ़ो_value(client, W83793_REG_OVT_BEEP)
			    & 0xfd;
	data->beep_enable |= val << 1;
	w83793_ग_लिखो_value(client, W83793_REG_OVT_BEEP, data->beep_enable);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* Write 0 to clear chassis alarm */
अटल sमाप_प्रकार
store_chassis_clear(काष्ठा device *dev,
		    काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
		    माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83793_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	u8 reg;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;
	अगर (val)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	reg = w83793_पढ़ो_value(client, W83793_REG_CLR_CHASSIS);
	w83793_ग_लिखो_value(client, W83793_REG_CLR_CHASSIS, reg | 0x80);
	data->valid = 0;		/* Force cache refresh */
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

#घोषणा FAN_INPUT			0
#घोषणा FAN_MIN				1
अटल sमाप_प्रकार
show_fan(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा w83793_data *data = w83793_update_device(dev);
	u16 val;

	अगर (nr == FAN_INPUT)
		val = data->fan[index] & 0x0fff;
	अन्यथा
		val = data->fan_min[index] & 0x0fff;

	वापस प्र_लिखो(buf, "%lu\n", FAN_FROM_REG(val));
पूर्ण

अटल sमाप_प्रकार
store_fan_min(काष्ठा device *dev, काष्ठा device_attribute *attr,
	      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक index = sensor_attr->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83793_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;
	val = FAN_TO_REG(val);

	mutex_lock(&data->update_lock);
	data->fan_min[index] = val;
	w83793_ग_लिखो_value(client, W83793_REG_FAN_MIN(index),
			   (val >> 8) & 0xff);
	w83793_ग_लिखो_value(client, W83793_REG_FAN_MIN(index) + 1, val & 0xff);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	काष्ठा w83793_data *data = w83793_update_device(dev);
	u16 val;
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;

	अगर (nr == PWM_STOP_TIME)
		val = TIME_FROM_REG(data->pwm_stop_समय[index]);
	अन्यथा
		val = (data->pwm[index][nr] & 0x3f) << 2;

	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार
store_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
	  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83793_data *data = i2c_get_clientdata(client);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	अगर (nr == PWM_STOP_TIME) अणु
		val = TIME_TO_REG(val);
		data->pwm_stop_समय[index] = val;
		w83793_ग_लिखो_value(client, W83793_REG_PWM_STOP_TIME(index),
				   val);
	पूर्ण अन्यथा अणु
		val = clamp_val(val, 0, 0xff) >> 2;
		data->pwm[index][nr] =
		    w83793_पढ़ो_value(client, W83793_REG_PWM(index, nr)) & 0xc0;
		data->pwm[index][nr] |= val;
		w83793_ग_लिखो_value(client, W83793_REG_PWM(index, nr),
							data->pwm[index][nr]);
	पूर्ण

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_temp(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा w83793_data *data = w83793_update_device(dev);
	दीर्घ temp = TEMP_FROM_REG(data->temp[index][nr]);

	अगर (nr == TEMP_READ && index < 4) अणु	/* Only TD1-TD4 have low bits */
		पूर्णांक low = ((data->temp_low_bits >> (index * 2)) & 0x03) * 250;
		temp += temp > 0 ? low : -low;
	पूर्ण
	वापस प्र_लिखो(buf, "%ld\n", temp);
पूर्ण

अटल sमाप_प्रकार
store_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
	   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83793_data *data = i2c_get_clientdata(client);
	दीर्घ पंचांगp;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &पंचांगp);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp[index][nr] = TEMP_TO_REG(पंचांगp, -128, 127);
	w83793_ग_लिखो_value(client, W83793_REG_TEMP[index][nr],
			   data->temp[index][nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/*
 * TD1-TD4
 * each has 4 mode:(2 bits)
 * 0:	Stop monitor
 * 1:	Use पूर्णांकernal temp sensor(शेष)
 * 2:	Reserved
 * 3:	Use sensor in Intel CPU and get result by PECI
 *
 * TR1-TR2
 * each has 2 mode:(1 bit)
 * 0:	Disable temp sensor monitor
 * 1:	To enable temp sensors monitor
 */

/* 0 disable, 6 PECI */
अटल u8 TO_TEMP_MODE[] = अणु 0, 0, 0, 6 पूर्ण;

अटल sमाप_प्रकार
show_temp_mode(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83793_data *data = w83793_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक index = sensor_attr->index;
	u8 mask = (index < 4) ? 0x03 : 0x01;
	u8 shअगरt = (index < 4) ? (2 * index) : (index - 4);
	u8 पंचांगp;
	index = (index < 4) ? 0 : 1;

	पंचांगp = (data->temp_mode[index] >> shअगरt) & mask;

	/* क्रम the पूर्णांकernal sensor, found out अगर diode or thermistor */
	अगर (पंचांगp == 1)
		पंचांगp = index == 0 ? 3 : 4;
	अन्यथा
		पंचांगp = TO_TEMP_MODE[पंचांगp];

	वापस प्र_लिखो(buf, "%d\n", पंचांगp);
पूर्ण

अटल sमाप_प्रकार
store_temp_mode(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83793_data *data = i2c_get_clientdata(client);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक index = sensor_attr->index;
	u8 mask = (index < 4) ? 0x03 : 0x01;
	u8 shअगरt = (index < 4) ? (2 * index) : (index - 4);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	/* transक्रमm the sysfs पूर्णांकerface values पूर्णांकo table above */
	अगर ((val == 6) && (index < 4)) अणु
		val -= 3;
	पूर्ण अन्यथा अगर ((val == 3 && index < 4)
		|| (val == 4 && index >= 4)) अणु
		/* transक्रमm diode or thermistor पूर्णांकo पूर्णांकernal enable */
		val = !!val;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	index = (index < 4) ? 0 : 1;
	mutex_lock(&data->update_lock);
	data->temp_mode[index] =
	    w83793_पढ़ो_value(client, W83793_REG_TEMP_MODE[index]);
	data->temp_mode[index] &= ~(mask << shअगरt);
	data->temp_mode[index] |= val << shअगरt;
	w83793_ग_लिखो_value(client, W83793_REG_TEMP_MODE[index],
							data->temp_mode[index]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

#घोषणा SETUP_PWM_DEFAULT		0
#घोषणा SETUP_PWM_UPTIME		1	/* Unit in 0.1s */
#घोषणा SETUP_PWM_DOWNTIME		2	/* Unit in 0.1s */
#घोषणा SETUP_TEMP_CRITICAL		3
अटल sमाप_प्रकार
show_sf_setup(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	काष्ठा w83793_data *data = w83793_update_device(dev);
	u32 val = 0;

	अगर (nr == SETUP_PWM_DEFAULT)
		val = (data->pwm_शेष & 0x3f) << 2;
	अन्यथा अगर (nr == SETUP_PWM_UPTIME)
		val = TIME_FROM_REG(data->pwm_upसमय);
	अन्यथा अगर (nr == SETUP_PWM_DOWNTIME)
		val = TIME_FROM_REG(data->pwm_करोwnसमय);
	अन्यथा अगर (nr == SETUP_TEMP_CRITICAL)
		val = TEMP_FROM_REG(data->temp_critical & 0x7f);

	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार
store_sf_setup(काष्ठा device *dev, काष्ठा device_attribute *attr,
	       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83793_data *data = i2c_get_clientdata(client);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	अगर (nr == SETUP_PWM_DEFAULT) अणु
		data->pwm_शेष =
		    w83793_पढ़ो_value(client, W83793_REG_PWM_DEFAULT) & 0xc0;
		data->pwm_शेष |= clamp_val(val, 0, 0xff) >> 2;
		w83793_ग_लिखो_value(client, W83793_REG_PWM_DEFAULT,
							data->pwm_शेष);
	पूर्ण अन्यथा अगर (nr == SETUP_PWM_UPTIME) अणु
		data->pwm_upसमय = TIME_TO_REG(val);
		data->pwm_upसमय += data->pwm_upसमय == 0 ? 1 : 0;
		w83793_ग_लिखो_value(client, W83793_REG_PWM_UPTIME,
							data->pwm_upसमय);
	पूर्ण अन्यथा अगर (nr == SETUP_PWM_DOWNTIME) अणु
		data->pwm_करोwnसमय = TIME_TO_REG(val);
		data->pwm_करोwnसमय += data->pwm_करोwnसमय == 0 ? 1 : 0;
		w83793_ग_लिखो_value(client, W83793_REG_PWM_DOWNTIME,
							data->pwm_करोwnसमय);
	पूर्ण अन्यथा अणु		/* SETUP_TEMP_CRITICAL */
		data->temp_critical =
		    w83793_पढ़ो_value(client, W83793_REG_TEMP_CRITICAL) & 0x80;
		data->temp_critical |= TEMP_TO_REG(val, 0, 0x7f);
		w83793_ग_लिखो_value(client, W83793_REG_TEMP_CRITICAL,
							data->temp_critical);
	पूर्ण

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/*
 * Temp SmartFan control
 * TEMP_FAN_MAP
 * Temp channel control which pwm fan, bitfield, bit 0 indicate pwm1...
 * It's possible two or more temp channels control the same fan, w83793
 * always prefers to pick the most critical request and applies it to
 * the related Fan.
 * It's possible one fan is not in any mapping of 6 temp channels, this
 * means the fan is manual mode
 *
 * TEMP_PWM_ENABLE
 * Each temp channel has its own SmartFan mode, and temp channel
 * control fans that are set by TEMP_FAN_MAP
 * 0:	SmartFanII mode
 * 1:	Thermal Cruise Mode
 *
 * TEMP_CRUISE
 * Target temperature in thermal cruise mode, w83793 will try to turn
 * fan speed to keep the temperature of target device around this
 * temperature.
 *
 * TEMP_TOLERANCE
 * If Temp higher or lower than target with this tolerance, w83793
 * will take actions to speed up or slow करोwn the fan to keep the
 * temperature within the tolerance range.
 */

#घोषणा TEMP_FAN_MAP			0
#घोषणा TEMP_PWM_ENABLE			1
#घोषणा TEMP_CRUISE			2
#घोषणा TEMP_TOLERANCE			3
अटल sमाप_प्रकार
show_sf_ctrl(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा w83793_data *data = w83793_update_device(dev);
	u32 val;

	अगर (nr == TEMP_FAN_MAP) अणु
		val = data->temp_fan_map[index];
	पूर्ण अन्यथा अगर (nr == TEMP_PWM_ENABLE) अणु
		/* +2 to transक्रमm पूर्णांकo 2 and 3 to conक्रमm with sysfs पूर्णांकf */
		val = ((data->pwm_enable >> index) & 0x01) + 2;
	पूर्ण अन्यथा अगर (nr == TEMP_CRUISE) अणु
		val = TEMP_FROM_REG(data->temp_cruise[index] & 0x7f);
	पूर्ण अन्यथा अणु		/* TEMP_TOLERANCE */
		val = data->tolerance[index >> 1] >> ((index & 0x01) ? 4 : 0);
		val = TEMP_FROM_REG(val & 0x0f);
	पूर्ण
	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार
store_sf_ctrl(काष्ठा device *dev, काष्ठा device_attribute *attr,
	      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83793_data *data = i2c_get_clientdata(client);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	अगर (nr == TEMP_FAN_MAP) अणु
		val = clamp_val(val, 0, 255);
		w83793_ग_लिखो_value(client, W83793_REG_TEMP_FAN_MAP(index), val);
		data->temp_fan_map[index] = val;
	पूर्ण अन्यथा अगर (nr == TEMP_PWM_ENABLE) अणु
		अगर (val == 2 || val == 3) अणु
			data->pwm_enable =
			    w83793_पढ़ो_value(client, W83793_REG_PWM_ENABLE);
			अगर (val - 2)
				data->pwm_enable |= 1 << index;
			अन्यथा
				data->pwm_enable &= ~(1 << index);
			w83793_ग_लिखो_value(client, W83793_REG_PWM_ENABLE,
							data->pwm_enable);
		पूर्ण अन्यथा अणु
			mutex_unlock(&data->update_lock);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (nr == TEMP_CRUISE) अणु
		data->temp_cruise[index] =
		    w83793_पढ़ो_value(client, W83793_REG_TEMP_CRUISE(index));
		data->temp_cruise[index] &= 0x80;
		data->temp_cruise[index] |= TEMP_TO_REG(val, 0, 0x7f);

		w83793_ग_लिखो_value(client, W83793_REG_TEMP_CRUISE(index),
						data->temp_cruise[index]);
	पूर्ण अन्यथा अणु		/* TEMP_TOLERANCE */
		पूर्णांक i = index >> 1;
		u8 shअगरt = (index & 0x01) ? 4 : 0;
		data->tolerance[i] =
		    w83793_पढ़ो_value(client, W83793_REG_TEMP_TOL(i));

		data->tolerance[i] &= ~(0x0f << shअगरt);
		data->tolerance[i] |= TEMP_TO_REG(val, 0, 0x0f) << shअगरt;
		w83793_ग_लिखो_value(client, W83793_REG_TEMP_TOL(i),
							data->tolerance[i]);
	पूर्ण

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_sf2_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा w83793_data *data = w83793_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", (data->sf2_pwm[index][nr] & 0x3f) << 2);
पूर्ण

अटल sमाप_प्रकार
store_sf2_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
	      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83793_data *data = i2c_get_clientdata(client);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;
	val = clamp_val(val, 0, 0xff) >> 2;

	mutex_lock(&data->update_lock);
	data->sf2_pwm[index][nr] =
	    w83793_पढ़ो_value(client, W83793_REG_SF2_PWM(index, nr)) & 0xc0;
	data->sf2_pwm[index][nr] |= val;
	w83793_ग_लिखो_value(client, W83793_REG_SF2_PWM(index, nr),
						data->sf2_pwm[index][nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_sf2_temp(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा w83793_data *data = w83793_update_device(dev);

	वापस प्र_लिखो(buf, "%ld\n",
		       TEMP_FROM_REG(data->sf2_temp[index][nr] & 0x7f));
पूर्ण

अटल sमाप_प्रकार
store_sf2_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
	       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83793_data *data = i2c_get_clientdata(client);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;
	val = TEMP_TO_REG(val, 0, 0x7f);

	mutex_lock(&data->update_lock);
	data->sf2_temp[index][nr] =
	    w83793_पढ़ो_value(client, W83793_REG_SF2_TEMP(index, nr)) & 0x80;
	data->sf2_temp[index][nr] |= val;
	w83793_ग_लिखो_value(client, W83793_REG_SF2_TEMP(index, nr),
					     data->sf2_temp[index][nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/* only Vcore A/B and Vtt have additional 2 bits precision */
अटल sमाप_प्रकार
show_in(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा w83793_data *data = w83793_update_device(dev);
	u16 val = data->in[index][nr];

	अगर (index < 3) अणु
		val <<= 2;
		val += (data->in_low_bits[nr] >> (index * 2)) & 0x3;
	पूर्ण
	/* voltage inमाला_दो 5VDD and 5VSB needs 150mV offset */
	val = val * scale_in[index] + scale_in_add[index];
	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार
store_in(काष्ठा device *dev, काष्ठा device_attribute *attr,
	 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83793_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;
	val = (val + scale_in[index] / 2) / scale_in[index];

	mutex_lock(&data->update_lock);
	अगर (index > 2) अणु
		/* fix the limit values of 5VDD and 5VSB to ALARM mechanism */
		अगर (nr == 1 || nr == 2)
			val -= scale_in_add[index] / scale_in[index];
		val = clamp_val(val, 0, 255);
	पूर्ण अन्यथा अणु
		val = clamp_val(val, 0, 0x3FF);
		data->in_low_bits[nr] =
		    w83793_पढ़ो_value(client, W83793_REG_IN_LOW_BITS[nr]);
		data->in_low_bits[nr] &= ~(0x03 << (2 * index));
		data->in_low_bits[nr] |= (val & 0x03) << (2 * index);
		w83793_ग_लिखो_value(client, W83793_REG_IN_LOW_BITS[nr],
						     data->in_low_bits[nr]);
		val >>= 2;
	पूर्ण
	data->in[index][nr] = val;
	w83793_ग_लिखो_value(client, W83793_REG_IN[index][nr],
							data->in[index][nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

#घोषणा NOT_USED			-1

#घोषणा SENSOR_ATTR_IN(index)						\
	SENSOR_ATTR_2(in##index##_input, S_IRUGO, show_in, शून्य,	\
		IN_READ, index),					\
	SENSOR_ATTR_2(in##index##_max, S_IRUGO | S_IWUSR, show_in,	\
		store_in, IN_MAX, index),				\
	SENSOR_ATTR_2(in##index##_min, S_IRUGO | S_IWUSR, show_in,	\
		store_in, IN_LOW, index),				\
	SENSOR_ATTR_2(in##index##_alarm, S_IRUGO, show_alarm_beep,	\
		शून्य, ALARM_STATUS, index + ((index > 2) ? 1 : 0)),	\
	SENSOR_ATTR_2(in##index##_beep, S_IWUSR | S_IRUGO,		\
		show_alarm_beep, store_beep, BEEP_ENABLE,		\
		index + ((index > 2) ? 1 : 0))

#घोषणा SENSOR_ATTR_FAN(index)						\
	SENSOR_ATTR_2(fan##index##_alarm, S_IRUGO, show_alarm_beep,	\
		शून्य, ALARM_STATUS, index + 17),			\
	SENSOR_ATTR_2(fan##index##_beep, S_IWUSR | S_IRUGO,		\
		show_alarm_beep, store_beep, BEEP_ENABLE, index + 17),	\
	SENSOR_ATTR_2(fan##index##_input, S_IRUGO, show_fan,		\
		शून्य, FAN_INPUT, index - 1),				\
	SENSOR_ATTR_2(fan##index##_min, S_IWUSR | S_IRUGO,		\
		show_fan, store_fan_min, FAN_MIN, index - 1)

#घोषणा SENSOR_ATTR_PWM(index)						\
	SENSOR_ATTR_2(pwm##index, S_IWUSR | S_IRUGO, show_pwm,		\
		store_pwm, PWM_DUTY, index - 1),			\
	SENSOR_ATTR_2(pwm##index##_nonstop, S_IWUSR | S_IRUGO,		\
		show_pwm, store_pwm, PWM_NONSTOP, index - 1),		\
	SENSOR_ATTR_2(pwm##index##_start, S_IWUSR | S_IRUGO,		\
		show_pwm, store_pwm, PWM_START, index - 1),		\
	SENSOR_ATTR_2(pwm##index##_stop_समय, S_IWUSR | S_IRUGO,	\
		show_pwm, store_pwm, PWM_STOP_TIME, index - 1)

#घोषणा SENSOR_ATTR_TEMP(index)						\
	SENSOR_ATTR_2(temp##index##_type, S_IRUGO | S_IWUSR,		\
		show_temp_mode, store_temp_mode, NOT_USED, index - 1),	\
	SENSOR_ATTR_2(temp##index##_input, S_IRUGO, show_temp,		\
		शून्य, TEMP_READ, index - 1),				\
	SENSOR_ATTR_2(temp##index##_max, S_IRUGO | S_IWUSR, show_temp,	\
		store_temp, TEMP_CRIT, index - 1),			\
	SENSOR_ATTR_2(temp##index##_max_hyst, S_IRUGO | S_IWUSR,	\
		show_temp, store_temp, TEMP_CRIT_HYST, index - 1),	\
	SENSOR_ATTR_2(temp##index##_warn, S_IRUGO | S_IWUSR, show_temp,	\
		store_temp, TEMP_WARN, index - 1),			\
	SENSOR_ATTR_2(temp##index##_warn_hyst, S_IRUGO | S_IWUSR,	\
		show_temp, store_temp, TEMP_WARN_HYST, index - 1),	\
	SENSOR_ATTR_2(temp##index##_alarm, S_IRUGO,			\
		show_alarm_beep, शून्य, ALARM_STATUS, index + 11),	\
	SENSOR_ATTR_2(temp##index##_beep, S_IWUSR | S_IRUGO,		\
		show_alarm_beep, store_beep, BEEP_ENABLE, index + 11),	\
	SENSOR_ATTR_2(temp##index##_स्वतः_channels_pwm,			\
		S_IRUGO | S_IWUSR, show_sf_ctrl, store_sf_ctrl,		\
		TEMP_FAN_MAP, index - 1),				\
	SENSOR_ATTR_2(temp##index##_pwm_enable, S_IWUSR | S_IRUGO,	\
		show_sf_ctrl, store_sf_ctrl, TEMP_PWM_ENABLE,		\
		index - 1),						\
	SENSOR_ATTR_2(thermal_cruise##index, S_IRUGO | S_IWUSR,		\
		show_sf_ctrl, store_sf_ctrl, TEMP_CRUISE, index - 1),	\
	SENSOR_ATTR_2(tolerance##index, S_IRUGO | S_IWUSR, show_sf_ctrl,\
		store_sf_ctrl, TEMP_TOLERANCE, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक1_pwm, S_IRUGO | S_IWUSR, \
		show_sf2_pwm, store_sf2_pwm, 0, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक2_pwm, S_IRUGO | S_IWUSR, \
		show_sf2_pwm, store_sf2_pwm, 1, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक3_pwm, S_IRUGO | S_IWUSR, \
		show_sf2_pwm, store_sf2_pwm, 2, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक4_pwm, S_IRUGO | S_IWUSR, \
		show_sf2_pwm, store_sf2_pwm, 3, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक5_pwm, S_IRUGO | S_IWUSR, \
		show_sf2_pwm, store_sf2_pwm, 4, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक6_pwm, S_IRUGO | S_IWUSR, \
		show_sf2_pwm, store_sf2_pwm, 5, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक7_pwm, S_IRUGO | S_IWUSR, \
		show_sf2_pwm, store_sf2_pwm, 6, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक1_temp, S_IRUGO | S_IWUSR,\
		show_sf2_temp, store_sf2_temp, 0, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक2_temp, S_IRUGO | S_IWUSR,\
		show_sf2_temp, store_sf2_temp, 1, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक3_temp, S_IRUGO | S_IWUSR,\
		show_sf2_temp, store_sf2_temp, 2, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक4_temp, S_IRUGO | S_IWUSR,\
		show_sf2_temp, store_sf2_temp, 3, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक5_temp, S_IRUGO | S_IWUSR,\
		show_sf2_temp, store_sf2_temp, 4, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक6_temp, S_IRUGO | S_IWUSR,\
		show_sf2_temp, store_sf2_temp, 5, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक7_temp, S_IRUGO | S_IWUSR,\
		show_sf2_temp, store_sf2_temp, 6, index - 1)

अटल काष्ठा sensor_device_attribute_2 w83793_sensor_attr_2[] = अणु
	SENSOR_ATTR_IN(0),
	SENSOR_ATTR_IN(1),
	SENSOR_ATTR_IN(2),
	SENSOR_ATTR_IN(3),
	SENSOR_ATTR_IN(4),
	SENSOR_ATTR_IN(5),
	SENSOR_ATTR_IN(6),
	SENSOR_ATTR_IN(7),
	SENSOR_ATTR_IN(8),
	SENSOR_ATTR_IN(9),
	SENSOR_ATTR_FAN(1),
	SENSOR_ATTR_FAN(2),
	SENSOR_ATTR_FAN(3),
	SENSOR_ATTR_FAN(4),
	SENSOR_ATTR_FAN(5),
	SENSOR_ATTR_PWM(1),
	SENSOR_ATTR_PWM(2),
	SENSOR_ATTR_PWM(3),
पूर्ण;

अटल काष्ठा sensor_device_attribute_2 w83793_temp[] = अणु
	SENSOR_ATTR_TEMP(1),
	SENSOR_ATTR_TEMP(2),
	SENSOR_ATTR_TEMP(3),
	SENSOR_ATTR_TEMP(4),
	SENSOR_ATTR_TEMP(5),
	SENSOR_ATTR_TEMP(6),
पूर्ण;

/* Fan6-Fan12 */
अटल काष्ठा sensor_device_attribute_2 w83793_left_fan[] = अणु
	SENSOR_ATTR_FAN(6),
	SENSOR_ATTR_FAN(7),
	SENSOR_ATTR_FAN(8),
	SENSOR_ATTR_FAN(9),
	SENSOR_ATTR_FAN(10),
	SENSOR_ATTR_FAN(11),
	SENSOR_ATTR_FAN(12),
पूर्ण;

/* Pwm4-Pwm8 */
अटल काष्ठा sensor_device_attribute_2 w83793_left_pwm[] = अणु
	SENSOR_ATTR_PWM(4),
	SENSOR_ATTR_PWM(5),
	SENSOR_ATTR_PWM(6),
	SENSOR_ATTR_PWM(7),
	SENSOR_ATTR_PWM(8),
पूर्ण;

अटल काष्ठा sensor_device_attribute_2 w83793_vid[] = अणु
	SENSOR_ATTR_2(cpu0_vid, S_IRUGO, show_vid, शून्य, NOT_USED, 0),
	SENSOR_ATTR_2(cpu1_vid, S_IRUGO, show_vid, शून्य, NOT_USED, 1),
पूर्ण;
अटल DEVICE_ATTR_RW(vrm);

अटल काष्ठा sensor_device_attribute_2 sda_single_files[] = अणु
	SENSOR_ATTR_2(पूर्णांकrusion0_alarm, S_IWUSR | S_IRUGO, show_alarm_beep,
		      store_chassis_clear, ALARM_STATUS, 30),
	SENSOR_ATTR_2(beep_enable, S_IWUSR | S_IRUGO, show_beep_enable,
		      store_beep_enable, NOT_USED, NOT_USED),
	SENSOR_ATTR_2(pwm_शेष, S_IWUSR | S_IRUGO, show_sf_setup,
		      store_sf_setup, SETUP_PWM_DEFAULT, NOT_USED),
	SENSOR_ATTR_2(pwm_upसमय, S_IWUSR | S_IRUGO, show_sf_setup,
		      store_sf_setup, SETUP_PWM_UPTIME, NOT_USED),
	SENSOR_ATTR_2(pwm_करोwnसमय, S_IWUSR | S_IRUGO, show_sf_setup,
		      store_sf_setup, SETUP_PWM_DOWNTIME, NOT_USED),
	SENSOR_ATTR_2(temp_critical, S_IWUSR | S_IRUGO, show_sf_setup,
		      store_sf_setup, SETUP_TEMP_CRITICAL, NOT_USED),
पूर्ण;

अटल व्योम w83793_init_client(काष्ठा i2c_client *client)
अणु
	अगर (reset)
		w83793_ग_लिखो_value(client, W83793_REG_CONFIG, 0x80);

	/* Start monitoring */
	w83793_ग_लिखो_value(client, W83793_REG_CONFIG,
			   w83793_पढ़ो_value(client, W83793_REG_CONFIG) | 0x01);
पूर्ण

/*
 * Watchकरोg routines
 */

अटल पूर्णांक watchकरोg_set_समयout(काष्ठा w83793_data *data, पूर्णांक समयout)
अणु
	अचिन्हित पूर्णांक mसमयout;
	पूर्णांक ret;

	mसमयout = DIV_ROUND_UP(समयout, 60);

	अगर (mसमयout > 255)
		वापस -EINVAL;

	mutex_lock(&data->watchकरोg_lock);
	अगर (!data->client) अणु
		ret = -ENODEV;
		जाओ leave;
	पूर्ण

	data->watchकरोg_समयout = mसमयout;

	/* Set Timeout value (in Minutes) */
	w83793_ग_लिखो_value(data->client, W83793_REG_WDT_TIMEOUT,
			   data->watchकरोg_समयout);

	ret = mसमयout * 60;

leave:
	mutex_unlock(&data->watchकरोg_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक watchकरोg_get_समयout(काष्ठा w83793_data *data)
अणु
	पूर्णांक समयout;

	mutex_lock(&data->watchकरोg_lock);
	समयout = data->watchकरोg_समयout * 60;
	mutex_unlock(&data->watchकरोg_lock);

	वापस समयout;
पूर्ण

अटल पूर्णांक watchकरोg_trigger(काष्ठा w83793_data *data)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&data->watchकरोg_lock);
	अगर (!data->client) अणु
		ret = -ENODEV;
		जाओ leave;
	पूर्ण

	/* Set Timeout value (in Minutes) */
	w83793_ग_लिखो_value(data->client, W83793_REG_WDT_TIMEOUT,
			   data->watchकरोg_समयout);

leave:
	mutex_unlock(&data->watchकरोg_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक watchकरोg_enable(काष्ठा w83793_data *data)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&data->watchकरोg_lock);
	अगर (!data->client) अणु
		ret = -ENODEV;
		जाओ leave;
	पूर्ण

	/* Set initial समयout */
	w83793_ग_लिखो_value(data->client, W83793_REG_WDT_TIMEOUT,
			   data->watchकरोg_समयout);

	/* Enable Soft Watchकरोg */
	w83793_ग_लिखो_value(data->client, W83793_REG_WDT_LOCK, 0x55);

leave:
	mutex_unlock(&data->watchकरोg_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक watchकरोg_disable(काष्ठा w83793_data *data)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&data->watchकरोg_lock);
	अगर (!data->client) अणु
		ret = -ENODEV;
		जाओ leave;
	पूर्ण

	/* Disable Soft Watchकरोg */
	w83793_ग_लिखो_value(data->client, W83793_REG_WDT_LOCK, 0xAA);

leave:
	mutex_unlock(&data->watchकरोg_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक watchकरोg_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा w83793_data *pos, *data = शून्य;
	पूर्णांक watchकरोg_is_खोलो;

	/*
	 * We get called from drivers/अक्षर/misc.c with misc_mtx hold, and we
	 * call misc_रेजिस्टर() from  w83793_probe() with watchकरोg_data_mutex
	 * hold, as misc_रेजिस्टर() takes the misc_mtx lock, this is a possible
	 * deadlock, so we use mutex_trylock here.
	 */
	अगर (!mutex_trylock(&watchकरोg_data_mutex))
		वापस -ERESTARTSYS;
	list_क्रम_each_entry(pos, &watchकरोg_data_list, list) अणु
		अगर (pos->watchकरोg_miscdev.minor == iminor(inode)) अणु
			data = pos;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Check, अगर device is alपढ़ोy खोलो */
	watchकरोg_is_खोलो = test_and_set_bit(0, &data->watchकरोg_is_खोलो);

	/*
	 * Increase data reference counter (अगर not alपढ़ोy करोne).
	 * Note we can never not have found data, so we करोn't check क्रम this
	 */
	अगर (!watchकरोg_is_खोलो)
		kref_get(&data->kref);

	mutex_unlock(&watchकरोg_data_mutex);

	/* Check, अगर device is alपढ़ोy खोलो and possibly issue error */
	अगर (watchकरोg_is_खोलो)
		वापस -EBUSY;

	/* Enable Soft Watchकरोg */
	watchकरोg_enable(data);

	/* Store poपूर्णांकer to data पूर्णांकo filp's निजी data */
	filp->निजी_data = data;

	वापस stream_खोलो(inode, filp);
पूर्ण

अटल पूर्णांक watchकरोg_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा w83793_data *data = filp->निजी_data;

	अगर (data->watchकरोg_expect_बंद) अणु
		watchकरोg_disable(data);
		data->watchकरोg_expect_बंद = 0;
	पूर्ण अन्यथा अणु
		watchकरोg_trigger(data);
		dev_crit(&data->client->dev,
			"unexpected close, not stopping watchdog!\n");
	पूर्ण

	clear_bit(0, &data->watchकरोg_is_खोलो);

	/* Decrease data reference counter */
	mutex_lock(&watchकरोg_data_mutex);
	kref_put(&data->kref, w83793_release_resources);
	mutex_unlock(&watchकरोg_data_mutex);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार watchकरोg_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
	माप_प्रकार count, loff_t *offset)
अणु
	sमाप_प्रकार ret;
	काष्ठा w83793_data *data = filp->निजी_data;

	अगर (count) अणु
		अगर (!nowayout) अणु
			माप_प्रकार i;

			/* Clear it in हाल it was set with a previous ग_लिखो */
			data->watchकरोg_expect_बंद = 0;

			क्रम (i = 0; i != count; i++) अणु
				अक्षर c;
				अगर (get_user(c, buf + i))
					वापस -EFAULT;
				अगर (c == 'V')
					data->watchकरोg_expect_बंद = 1;
			पूर्ण
		पूर्ण
		ret = watchकरोg_trigger(data);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस count;
पूर्ण

अटल दीर्घ watchकरोg_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			   अचिन्हित दीर्घ arg)
अणु
	काष्ठा watchकरोg_info ident = अणु
		.options = WDIOF_KEEPALIVEPING |
			   WDIOF_SETTIMEOUT |
			   WDIOF_CARDRESET,
		.identity = "w83793 watchdog"
	पूर्ण;

	पूर्णांक val, ret = 0;
	काष्ठा w83793_data *data = filp->निजी_data;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		अगर (!nowayout)
			ident.options |= WDIOF_MAGICCLOSE;
		अगर (copy_to_user((व्योम __user *)arg, &ident, माप(ident)))
			ret = -EFAULT;
		अवरोध;

	हाल WDIOC_GETSTATUS:
		val = data->watchकरोg_caused_reboot ? WDIOF_CARDRESET : 0;
		ret = put_user(val, (पूर्णांक __user *)arg);
		अवरोध;

	हाल WDIOC_GETBOOTSTATUS:
		ret = put_user(0, (पूर्णांक __user *)arg);
		अवरोध;

	हाल WDIOC_KEEPALIVE:
		ret = watchकरोg_trigger(data);
		अवरोध;

	हाल WDIOC_GETTIMEOUT:
		val = watchकरोg_get_समयout(data);
		ret = put_user(val, (पूर्णांक __user *)arg);
		अवरोध;

	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(val, (पूर्णांक __user *)arg)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		ret = watchकरोg_set_समयout(data, val);
		अगर (ret > 0)
			ret = put_user(ret, (पूर्णांक __user *)arg);
		अवरोध;

	हाल WDIOC_SETOPTIONS:
		अगर (get_user(val, (पूर्णांक __user *)arg)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (val & WDIOS_DISABLECARD)
			ret = watchकरोg_disable(data);
		अन्यथा अगर (val & WDIOS_ENABLECARD)
			ret = watchकरोg_enable(data);
		अन्यथा
			ret = -EINVAL;

		अवरोध;
	शेष:
		ret = -ENOTTY;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations watchकरोg_fops = अणु
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.खोलो = watchकरोg_खोलो,
	.release = watchकरोg_बंद,
	.ग_लिखो = watchकरोg_ग_लिखो,
	.unlocked_ioctl = watchकरोg_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
पूर्ण;

/*
 *	Notअगरier क्रम प्रणाली करोwn
 */

अटल पूर्णांक watchकरोg_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
			       व्योम *unused)
अणु
	काष्ठा w83793_data *data = शून्य;

	अगर (code == SYS_DOWN || code == SYS_HALT) अणु

		/* Disable each रेजिस्टरed watchकरोg */
		mutex_lock(&watchकरोg_data_mutex);
		list_क्रम_each_entry(data, &watchकरोg_data_list, list) अणु
			अगर (data->watchकरोg_miscdev.minor)
				watchकरोg_disable(data);
		पूर्ण
		mutex_unlock(&watchकरोg_data_mutex);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/*
 *	The WDT needs to learn about soft shutकरोwns in order to
 *	turn the समयbomb रेजिस्टरs off.
 */

अटल काष्ठा notअगरier_block watchकरोg_notअगरier = अणु
	.notअगरier_call = watchकरोg_notअगरy_sys,
पूर्ण;

/*
 * Init / हटाओ routines
 */

अटल पूर्णांक w83793_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा w83793_data *data = i2c_get_clientdata(client);
	काष्ठा device *dev = &client->dev;
	पूर्णांक i, पंचांगp;

	/* Unरेजिस्टर the watchकरोg (अगर रेजिस्टरed) */
	अगर (data->watchकरोg_miscdev.minor) अणु
		misc_deरेजिस्टर(&data->watchकरोg_miscdev);

		अगर (data->watchकरोg_is_खोलो) अणु
			dev_warn(&client->dev,
				"i2c client detached with watchdog open! "
				"Stopping watchdog.\n");
			watchकरोg_disable(data);
		पूर्ण

		mutex_lock(&watchकरोg_data_mutex);
		list_del(&data->list);
		mutex_unlock(&watchकरोg_data_mutex);

		/* Tell the watchकरोg code the client is gone */
		mutex_lock(&data->watchकरोg_lock);
		data->client = शून्य;
		mutex_unlock(&data->watchकरोg_lock);
	पूर्ण

	/* Reset Configuration Register to Disable Watch Dog Registers */
	पंचांगp = w83793_पढ़ो_value(client, W83793_REG_CONFIG);
	w83793_ग_लिखो_value(client, W83793_REG_CONFIG, पंचांगp & ~0x04);

	unरेजिस्टर_reboot_notअगरier(&watchकरोg_notअगरier);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);

	क्रम (i = 0; i < ARRAY_SIZE(w83793_sensor_attr_2); i++)
		device_हटाओ_file(dev,
				   &w83793_sensor_attr_2[i].dev_attr);

	क्रम (i = 0; i < ARRAY_SIZE(sda_single_files); i++)
		device_हटाओ_file(dev, &sda_single_files[i].dev_attr);

	क्रम (i = 0; i < ARRAY_SIZE(w83793_vid); i++)
		device_हटाओ_file(dev, &w83793_vid[i].dev_attr);
	device_हटाओ_file(dev, &dev_attr_vrm);

	क्रम (i = 0; i < ARRAY_SIZE(w83793_left_fan); i++)
		device_हटाओ_file(dev, &w83793_left_fan[i].dev_attr);

	क्रम (i = 0; i < ARRAY_SIZE(w83793_left_pwm); i++)
		device_हटाओ_file(dev, &w83793_left_pwm[i].dev_attr);

	क्रम (i = 0; i < ARRAY_SIZE(w83793_temp); i++)
		device_हटाओ_file(dev, &w83793_temp[i].dev_attr);

	/* Decrease data reference counter */
	mutex_lock(&watchकरोg_data_mutex);
	kref_put(&data->kref, w83793_release_resources);
	mutex_unlock(&watchकरोg_data_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
w83793_detect_subclients(काष्ठा i2c_client *client)
अणु
	पूर्णांक i, id;
	पूर्णांक address = client->addr;
	u8 पंचांगp;
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा w83793_data *data = i2c_get_clientdata(client);

	id = i2c_adapter_id(adapter);
	अगर (क्रमce_subclients[0] == id && क्रमce_subclients[1] == address) अणु
		क्रम (i = 2; i <= 3; i++) अणु
			अगर (क्रमce_subclients[i] < 0x48
			    || क्रमce_subclients[i] > 0x4f) अणु
				dev_err(&client->dev,
					"invalid subclient "
					"address %d; must be 0x48-0x4f\n",
					क्रमce_subclients[i]);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		w83793_ग_लिखो_value(client, W83793_REG_I2C_SUBADDR,
				   (क्रमce_subclients[2] & 0x07) |
				   ((क्रमce_subclients[3] & 0x07) << 4));
	पूर्ण

	पंचांगp = w83793_पढ़ो_value(client, W83793_REG_I2C_SUBADDR);
	अगर (!(पंचांगp & 0x08))
		data->lm75[0] = devm_i2c_new_dummy_device(&client->dev, adapter,
							  0x48 + (पंचांगp & 0x7));
	अगर (!(पंचांगp & 0x80)) अणु
		अगर (!IS_ERR(data->lm75[0])
		    && ((पंचांगp & 0x7) == ((पंचांगp >> 4) & 0x7))) अणु
			dev_err(&client->dev,
				"duplicate addresses 0x%x, "
				"use force_subclients\n", data->lm75[0]->addr);
			वापस -ENODEV;
		पूर्ण
		data->lm75[1] = devm_i2c_new_dummy_device(&client->dev, adapter,
							  0x48 + ((पंचांगp >> 4) & 0x7));
	पूर्ण

	वापस 0;
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक w83793_detect(काष्ठा i2c_client *client,
			 काष्ठा i2c_board_info *info)
अणु
	u8 पंचांगp, bank, chip_id;
	काष्ठा i2c_adapter *adapter = client->adapter;
	अचिन्हित लघु address = client->addr;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	bank = i2c_smbus_पढ़ो_byte_data(client, W83793_REG_BANKSEL);

	पंचांगp = bank & 0x80 ? 0x5c : 0xa3;
	/* Check Winbond venकरोr ID */
	अगर (पंचांगp != i2c_smbus_पढ़ो_byte_data(client, W83793_REG_VENDORID)) अणु
		pr_debug("w83793: Detection failed at check vendor id\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * If Winbond chip, address of chip and W83793_REG_I2C_ADDR
	 * should match
	 */
	अगर ((bank & 0x07) == 0
	 && i2c_smbus_पढ़ो_byte_data(client, W83793_REG_I2C_ADDR) !=
	    (address << 1)) अणु
		pr_debug("w83793: Detection failed at check i2c addr\n");
		वापस -ENODEV;
	पूर्ण

	/* Determine the chip type now */
	chip_id = i2c_smbus_पढ़ो_byte_data(client, W83793_REG_CHIPID);
	अगर (chip_id != 0x7b)
		वापस -ENODEV;

	strlcpy(info->type, "w83793", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक w83793_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	अटल स्थिर पूर्णांक watchकरोg_minors[] = अणु
		WATCHDOG_MINOR, 212, 213, 214, 215
	पूर्ण;
	काष्ठा w83793_data *data;
	पूर्णांक i, पंचांगp, val, err;
	पूर्णांक files_fan = ARRAY_SIZE(w83793_left_fan) / 7;
	पूर्णांक files_pwm = ARRAY_SIZE(w83793_left_pwm) / 5;
	पूर्णांक files_temp = ARRAY_SIZE(w83793_temp) / 6;

	data = kzalloc(माप(काष्ठा w83793_data), GFP_KERNEL);
	अगर (!data) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण

	i2c_set_clientdata(client, data);
	data->bank = i2c_smbus_पढ़ो_byte_data(client, W83793_REG_BANKSEL);
	mutex_init(&data->update_lock);
	mutex_init(&data->watchकरोg_lock);
	INIT_LIST_HEAD(&data->list);
	kref_init(&data->kref);

	/*
	 * Store client poपूर्णांकer in our data काष्ठा क्रम watchकरोg usage
	 * (where the client is found through a data ptr instead of the
	 * otherway around)
	 */
	data->client = client;

	err = w83793_detect_subclients(client);
	अगर (err)
		जाओ मुक्त_mem;

	/* Initialize the chip */
	w83793_init_client(client);

	/*
	 * Only fan 1-5 has their own input pins,
	 * Pwm 1-3 has their own pins
	 */
	data->has_fan = 0x1f;
	data->has_pwm = 0x07;
	पंचांगp = w83793_पढ़ो_value(client, W83793_REG_MFC);
	val = w83793_पढ़ो_value(client, W83793_REG_FANIN_CTRL);

	/* check the function of pins 49-56 */
	अगर (पंचांगp & 0x80) अणु
		data->has_vid |= 0x2;	/* has VIDB */
	पूर्ण अन्यथा अणु
		data->has_pwm |= 0x18;	/* pwm 4,5 */
		अगर (val & 0x01) अणु	/* fan 6 */
			data->has_fan |= 0x20;
			data->has_pwm |= 0x20;
		पूर्ण
		अगर (val & 0x02) अणु	/* fan 7 */
			data->has_fan |= 0x40;
			data->has_pwm |= 0x40;
		पूर्ण
		अगर (!(पंचांगp & 0x40) && (val & 0x04)) अणु	/* fan 8 */
			data->has_fan |= 0x80;
			data->has_pwm |= 0x80;
		पूर्ण
	पूर्ण

	/* check the function of pins 37-40 */
	अगर (!(पंचांगp & 0x29))
		data->has_vid |= 0x1;	/* has VIDA */
	अगर (0x08 == (पंचांगp & 0x0c)) अणु
		अगर (val & 0x08)	/* fan 9 */
			data->has_fan |= 0x100;
		अगर (val & 0x10)	/* fan 10 */
			data->has_fan |= 0x200;
	पूर्ण
	अगर (0x20 == (पंचांगp & 0x30)) अणु
		अगर (val & 0x20)	/* fan 11 */
			data->has_fan |= 0x400;
		अगर (val & 0x40)	/* fan 12 */
			data->has_fan |= 0x800;
	पूर्ण

	अगर ((पंचांगp & 0x01) && (val & 0x04)) अणु	/* fan 8, second location */
		data->has_fan |= 0x80;
		data->has_pwm |= 0x80;
	पूर्ण

	पंचांगp = w83793_पढ़ो_value(client, W83793_REG_FANIN_SEL);
	अगर ((पंचांगp & 0x01) && (val & 0x08)) अणु	/* fan 9, second location */
		data->has_fan |= 0x100;
	पूर्ण
	अगर ((पंचांगp & 0x02) && (val & 0x10)) अणु	/* fan 10, second location */
		data->has_fan |= 0x200;
	पूर्ण
	अगर ((पंचांगp & 0x04) && (val & 0x20)) अणु	/* fan 11, second location */
		data->has_fan |= 0x400;
	पूर्ण
	अगर ((पंचांगp & 0x08) && (val & 0x40)) अणु	/* fan 12, second location */
		data->has_fan |= 0x800;
	पूर्ण

	/* check the temp1-6 mode, ignore क्रमmer AMDSI selected inमाला_दो */
	पंचांगp = w83793_पढ़ो_value(client, W83793_REG_TEMP_MODE[0]);
	अगर (पंचांगp & 0x01)
		data->has_temp |= 0x01;
	अगर (पंचांगp & 0x04)
		data->has_temp |= 0x02;
	अगर (पंचांगp & 0x10)
		data->has_temp |= 0x04;
	अगर (पंचांगp & 0x40)
		data->has_temp |= 0x08;

	पंचांगp = w83793_पढ़ो_value(client, W83793_REG_TEMP_MODE[1]);
	अगर (पंचांगp & 0x01)
		data->has_temp |= 0x10;
	अगर (पंचांगp & 0x02)
		data->has_temp |= 0x20;

	/* Register sysfs hooks */
	क्रम (i = 0; i < ARRAY_SIZE(w83793_sensor_attr_2); i++) अणु
		err = device_create_file(dev,
					 &w83793_sensor_attr_2[i].dev_attr);
		अगर (err)
			जाओ निकास_हटाओ;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(w83793_vid); i++) अणु
		अगर (!(data->has_vid & (1 << i)))
			जारी;
		err = device_create_file(dev, &w83793_vid[i].dev_attr);
		अगर (err)
			जाओ निकास_हटाओ;
	पूर्ण
	अगर (data->has_vid) अणु
		data->vrm = vid_which_vrm();
		err = device_create_file(dev, &dev_attr_vrm);
		अगर (err)
			जाओ निकास_हटाओ;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sda_single_files); i++) अणु
		err = device_create_file(dev, &sda_single_files[i].dev_attr);
		अगर (err)
			जाओ निकास_हटाओ;

	पूर्ण

	क्रम (i = 0; i < 6; i++) अणु
		पूर्णांक j;
		अगर (!(data->has_temp & (1 << i)))
			जारी;
		क्रम (j = 0; j < files_temp; j++) अणु
			err = device_create_file(dev,
						&w83793_temp[(i) * files_temp
								+ j].dev_attr);
			अगर (err)
				जाओ निकास_हटाओ;
		पूर्ण
	पूर्ण

	क्रम (i = 5; i < 12; i++) अणु
		पूर्णांक j;
		अगर (!(data->has_fan & (1 << i)))
			जारी;
		क्रम (j = 0; j < files_fan; j++) अणु
			err = device_create_file(dev,
					   &w83793_left_fan[(i - 5) * files_fan
								+ j].dev_attr);
			अगर (err)
				जाओ निकास_हटाओ;
		पूर्ण
	पूर्ण

	क्रम (i = 3; i < 8; i++) अणु
		पूर्णांक j;
		अगर (!(data->has_pwm & (1 << i)))
			जारी;
		क्रम (j = 0; j < files_pwm; j++) अणु
			err = device_create_file(dev,
					   &w83793_left_pwm[(i - 3) * files_pwm
								+ j].dev_attr);
			अगर (err)
				जाओ निकास_हटाओ;
		पूर्ण
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		जाओ निकास_हटाओ;
	पूर्ण

	/* Watchकरोg initialization */

	/* Register boot notअगरier */
	err = रेजिस्टर_reboot_notअगरier(&watchकरोg_notअगरier);
	अगर (err != 0) अणु
		dev_err(&client->dev,
			"cannot register reboot notifier (err=%d)\n", err);
		जाओ निकास_devunreg;
	पूर्ण

	/*
	 * Enable Watchकरोg रेजिस्टरs.
	 * Set Configuration Register to Enable Watch Dog Registers
	 * (Bit 2) = XXXX, X1XX.
	 */
	पंचांगp = w83793_पढ़ो_value(client, W83793_REG_CONFIG);
	w83793_ग_लिखो_value(client, W83793_REG_CONFIG, पंचांगp | 0x04);

	/* Set the शेष watchकरोg समयout */
	data->watchकरोg_समयout = समयout;

	/* Check, अगर last reboot was caused by watchकरोg */
	data->watchकरोg_caused_reboot =
	  w83793_पढ़ो_value(data->client, W83793_REG_WDT_STATUS) & 0x01;

	/* Disable Soft Watchकरोg during initialiation */
	watchकरोg_disable(data);

	/*
	 * We take the data_mutex lock early so that watchकरोg_खोलो() cannot
	 * run when misc_रेजिस्टर() has completed, but we've not yet added
	 * our data to the watchकरोg_data_list (and set the शेष समयout)
	 */
	mutex_lock(&watchकरोg_data_mutex);
	क्रम (i = 0; i < ARRAY_SIZE(watchकरोg_minors); i++) अणु
		/* Register our watchकरोg part */
		snम_लिखो(data->watchकरोg_name, माप(data->watchकरोg_name),
			"watchdog%c", (i == 0) ? '\0' : ('0' + i));
		data->watchकरोg_miscdev.name = data->watchकरोg_name;
		data->watchकरोg_miscdev.fops = &watchकरोg_fops;
		data->watchकरोg_miscdev.minor = watchकरोg_minors[i];

		err = misc_रेजिस्टर(&data->watchकरोg_miscdev);
		अगर (err == -EBUSY)
			जारी;
		अगर (err) अणु
			data->watchकरोg_miscdev.minor = 0;
			dev_err(&client->dev,
				"Registering watchdog chardev: %d\n", err);
			अवरोध;
		पूर्ण

		list_add(&data->list, &watchकरोg_data_list);

		dev_info(&client->dev,
			"Registered watchdog chardev major 10, minor: %d\n",
			watchकरोg_minors[i]);
		अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(watchकरोg_minors)) अणु
		data->watchकरोg_miscdev.minor = 0;
		dev_warn(&client->dev,
			 "Couldn't register watchdog chardev (due to no free minor)\n");
	पूर्ण

	mutex_unlock(&watchकरोg_data_mutex);

	वापस 0;

	/* Unरेजिस्टर hwmon device */

निकास_devunreg:

	hwmon_device_unरेजिस्टर(data->hwmon_dev);

	/* Unरेजिस्टर sysfs hooks */

निकास_हटाओ:
	क्रम (i = 0; i < ARRAY_SIZE(w83793_sensor_attr_2); i++)
		device_हटाओ_file(dev, &w83793_sensor_attr_2[i].dev_attr);

	क्रम (i = 0; i < ARRAY_SIZE(sda_single_files); i++)
		device_हटाओ_file(dev, &sda_single_files[i].dev_attr);

	क्रम (i = 0; i < ARRAY_SIZE(w83793_vid); i++)
		device_हटाओ_file(dev, &w83793_vid[i].dev_attr);

	क्रम (i = 0; i < ARRAY_SIZE(w83793_left_fan); i++)
		device_हटाओ_file(dev, &w83793_left_fan[i].dev_attr);

	क्रम (i = 0; i < ARRAY_SIZE(w83793_left_pwm); i++)
		device_हटाओ_file(dev, &w83793_left_pwm[i].dev_attr);

	क्रम (i = 0; i < ARRAY_SIZE(w83793_temp); i++)
		device_हटाओ_file(dev, &w83793_temp[i].dev_attr);
मुक्त_mem:
	kमुक्त(data);
निकास:
	वापस err;
पूर्ण

अटल व्योम w83793_update_nonअस्थिर(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83793_data *data = i2c_get_clientdata(client);
	पूर्णांक i, j;
	/*
	 * They are somewhat "stable" रेजिस्टरs, and to update them every समय
	 * takes so much समय, it's just not worthy. Update them in a दीर्घ
	 * पूर्णांकerval to aव्योम exception.
	 */
	अगर (!(समय_after(jअगरfies, data->last_nonअस्थिर + HZ * 300)
	      || !data->valid))
		वापस;
	/* update voltage limits */
	क्रम (i = 1; i < 3; i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(data->in); j++) अणु
			data->in[j][i] =
			    w83793_पढ़ो_value(client, W83793_REG_IN[j][i]);
		पूर्ण
		data->in_low_bits[i] =
		    w83793_पढ़ो_value(client, W83793_REG_IN_LOW_BITS[i]);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(data->fan_min); i++) अणु
		/* Update the Fan measured value and limits */
		अगर (!(data->has_fan & (1 << i)))
			जारी;
		data->fan_min[i] =
		    w83793_पढ़ो_value(client, W83793_REG_FAN_MIN(i)) << 8;
		data->fan_min[i] |=
		    w83793_पढ़ो_value(client, W83793_REG_FAN_MIN(i) + 1);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(data->temp_fan_map); i++) अणु
		अगर (!(data->has_temp & (1 << i)))
			जारी;
		data->temp_fan_map[i] =
		    w83793_पढ़ो_value(client, W83793_REG_TEMP_FAN_MAP(i));
		क्रम (j = 1; j < 5; j++) अणु
			data->temp[i][j] =
			    w83793_पढ़ो_value(client, W83793_REG_TEMP[i][j]);
		पूर्ण
		data->temp_cruise[i] =
		    w83793_पढ़ो_value(client, W83793_REG_TEMP_CRUISE(i));
		क्रम (j = 0; j < 7; j++) अणु
			data->sf2_pwm[i][j] =
			    w83793_पढ़ो_value(client, W83793_REG_SF2_PWM(i, j));
			data->sf2_temp[i][j] =
			    w83793_पढ़ो_value(client,
					      W83793_REG_SF2_TEMP(i, j));
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(data->temp_mode); i++)
		data->temp_mode[i] =
		    w83793_पढ़ो_value(client, W83793_REG_TEMP_MODE[i]);

	क्रम (i = 0; i < ARRAY_SIZE(data->tolerance); i++) अणु
		data->tolerance[i] =
		    w83793_पढ़ो_value(client, W83793_REG_TEMP_TOL(i));
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(data->pwm); i++) अणु
		अगर (!(data->has_pwm & (1 << i)))
			जारी;
		data->pwm[i][PWM_NONSTOP] =
		    w83793_पढ़ो_value(client, W83793_REG_PWM(i, PWM_NONSTOP));
		data->pwm[i][PWM_START] =
		    w83793_पढ़ो_value(client, W83793_REG_PWM(i, PWM_START));
		data->pwm_stop_समय[i] =
		    w83793_पढ़ो_value(client, W83793_REG_PWM_STOP_TIME(i));
	पूर्ण

	data->pwm_शेष = w83793_पढ़ो_value(client, W83793_REG_PWM_DEFAULT);
	data->pwm_enable = w83793_पढ़ो_value(client, W83793_REG_PWM_ENABLE);
	data->pwm_upसमय = w83793_पढ़ो_value(client, W83793_REG_PWM_UPTIME);
	data->pwm_करोwnसमय = w83793_पढ़ो_value(client, W83793_REG_PWM_DOWNTIME);
	data->temp_critical =
	    w83793_पढ़ो_value(client, W83793_REG_TEMP_CRITICAL);
	data->beep_enable = w83793_पढ़ो_value(client, W83793_REG_OVT_BEEP);

	क्रम (i = 0; i < ARRAY_SIZE(data->beeps); i++)
		data->beeps[i] = w83793_पढ़ो_value(client, W83793_REG_BEEP(i));

	data->last_nonअस्थिर = jअगरfies;
पूर्ण

अटल काष्ठा w83793_data *w83793_update_device(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83793_data *data = i2c_get_clientdata(client);
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (!(समय_after(jअगरfies, data->last_updated + HZ * 2)
	      || !data->valid))
		जाओ END;

	/* Update the voltages measured value and limits */
	क्रम (i = 0; i < ARRAY_SIZE(data->in); i++)
		data->in[i][IN_READ] =
		    w83793_पढ़ो_value(client, W83793_REG_IN[i][IN_READ]);

	data->in_low_bits[IN_READ] =
	    w83793_पढ़ो_value(client, W83793_REG_IN_LOW_BITS[IN_READ]);

	क्रम (i = 0; i < ARRAY_SIZE(data->fan); i++) अणु
		अगर (!(data->has_fan & (1 << i)))
			जारी;
		data->fan[i] =
		    w83793_पढ़ो_value(client, W83793_REG_FAN(i)) << 8;
		data->fan[i] |=
		    w83793_पढ़ो_value(client, W83793_REG_FAN(i) + 1);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(data->temp); i++) अणु
		अगर (!(data->has_temp & (1 << i)))
			जारी;
		data->temp[i][TEMP_READ] =
		    w83793_पढ़ो_value(client, W83793_REG_TEMP[i][TEMP_READ]);
	पूर्ण

	data->temp_low_bits =
	    w83793_पढ़ो_value(client, W83793_REG_TEMP_LOW_BITS);

	क्रम (i = 0; i < ARRAY_SIZE(data->pwm); i++) अणु
		अगर (data->has_pwm & (1 << i))
			data->pwm[i][PWM_DUTY] =
			    w83793_पढ़ो_value(client,
					      W83793_REG_PWM(i, PWM_DUTY));
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(data->alarms); i++)
		data->alarms[i] =
		    w83793_पढ़ो_value(client, W83793_REG_ALARM(i));
	अगर (data->has_vid & 0x01)
		data->vid[0] = w83793_पढ़ो_value(client, W83793_REG_VID_INA);
	अगर (data->has_vid & 0x02)
		data->vid[1] = w83793_पढ़ो_value(client, W83793_REG_VID_INB);
	w83793_update_nonअस्थिर(dev);
	data->last_updated = jअगरfies;
	data->valid = 1;

END:
	mutex_unlock(&data->update_lock);
	वापस data;
पूर्ण

/*
 * Ignore the possibility that somebody change bank outside the driver
 * Must be called with data->update_lock held, except during initialization
 */
अटल u8 w83793_पढ़ो_value(काष्ठा i2c_client *client, u16 reg)
अणु
	काष्ठा w83793_data *data = i2c_get_clientdata(client);
	u8 res;
	u8 new_bank = reg >> 8;

	new_bank |= data->bank & 0xfc;
	अगर (data->bank != new_bank) अणु
		अगर (i2c_smbus_ग_लिखो_byte_data
		    (client, W83793_REG_BANKSEL, new_bank) >= 0)
			data->bank = new_bank;
		अन्यथा अणु
			dev_err(&client->dev,
				"set bank to %d failed, fall back "
				"to bank %d, read reg 0x%x error\n",
				new_bank, data->bank, reg);
			res = 0x0;	/* पढ़ो 0x0 from the chip */
			जाओ END;
		पूर्ण
	पूर्ण
	res = i2c_smbus_पढ़ो_byte_data(client, reg & 0xff);
END:
	वापस res;
पूर्ण

/* Must be called with data->update_lock held, except during initialization */
अटल पूर्णांक w83793_ग_लिखो_value(काष्ठा i2c_client *client, u16 reg, u8 value)
अणु
	काष्ठा w83793_data *data = i2c_get_clientdata(client);
	पूर्णांक res;
	u8 new_bank = reg >> 8;

	new_bank |= data->bank & 0xfc;
	अगर (data->bank != new_bank) अणु
		res = i2c_smbus_ग_लिखो_byte_data(client, W83793_REG_BANKSEL,
						new_bank);
		अगर (res < 0) अणु
			dev_err(&client->dev,
				"set bank to %d failed, fall back "
				"to bank %d, write reg 0x%x error\n",
				new_bank, data->bank, reg);
			जाओ END;
		पूर्ण
		data->bank = new_bank;
	पूर्ण

	res = i2c_smbus_ग_लिखो_byte_data(client, reg & 0xff, value);
END:
	वापस res;
पूर्ण

module_i2c_driver(w83793_driver);

MODULE_AUTHOR("Yuan Mu, Sven Anders");
MODULE_DESCRIPTION("w83793 driver");
MODULE_LICENSE("GPL");
