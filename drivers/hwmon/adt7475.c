<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * adt7475 - Thermal sensor driver क्रम the ADT7475 chip and derivatives
 * Copyright (C) 2007-2008, Advanced Micro Devices, Inc.
 * Copyright (C) 2008 Jordan Crouse <jordan@cosmicpenguin.net>
 * Copyright (C) 2008 Hans de Goede <hdegoede@redhat.com>
 * Copyright (C) 2009 Jean Delvare <jdelvare@suse.de>
 *
 * Derived from the lm83 driver by Jean Delvare
 */

#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/err.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/of.h>
#समावेश <linux/util_macros.h>

/* Indexes क्रम the sysfs hooks */

#घोषणा INPUT		0
#घोषणा MIN		1
#घोषणा MAX		2
#घोषणा CONTROL		3
#घोषणा OFFSET		3
#घोषणा AUTOMIN		4
#घोषणा THERM		5
#घोषणा HYSTERSIS	6

/*
 * These are unique identअगरiers क्रम the sysfs functions - unlike the
 * numbers above, these are not also indexes पूर्णांकo an array
 */

#घोषणा ALARM		9
#घोषणा FAULT		10

/* 7475 Common Registers */

#घोषणा REG_DEVREV2		0x12	/* ADT7490 only */

#घोषणा REG_VTT			0x1E	/* ADT7490 only */
#घोषणा REG_EXTEND3		0x1F	/* ADT7490 only */

#घोषणा REG_VOLTAGE_BASE	0x20
#घोषणा REG_TEMP_BASE		0x25
#घोषणा REG_TACH_BASE		0x28
#घोषणा REG_PWM_BASE		0x30
#घोषणा REG_PWM_MAX_BASE	0x38

#घोषणा REG_DEVID		0x3D
#घोषणा REG_VENDID		0x3E
#घोषणा REG_DEVID2		0x3F

#घोषणा REG_CONFIG1		0x40

#घोषणा REG_STATUS1		0x41
#घोषणा REG_STATUS2		0x42

#घोषणा REG_VID			0x43	/* ADT7476 only */

#घोषणा REG_VOLTAGE_MIN_BASE	0x44
#घोषणा REG_VOLTAGE_MAX_BASE	0x45

#घोषणा REG_TEMP_MIN_BASE	0x4E
#घोषणा REG_TEMP_MAX_BASE	0x4F

#घोषणा REG_TACH_MIN_BASE	0x54

#घोषणा REG_PWM_CONFIG_BASE	0x5C

#घोषणा REG_TEMP_TRANGE_BASE	0x5F

#घोषणा REG_ENHANCE_ACOUSTICS1	0x62
#घोषणा REG_ENHANCE_ACOUSTICS2	0x63

#घोषणा REG_PWM_MIN_BASE	0x64

#घोषणा REG_TEMP_TMIN_BASE	0x67
#घोषणा REG_TEMP_THERM_BASE	0x6A

#घोषणा REG_REMOTE1_HYSTERSIS	0x6D
#घोषणा REG_REMOTE2_HYSTERSIS	0x6E

#घोषणा REG_TEMP_OFFSET_BASE	0x70

#घोषणा REG_CONFIG2		0x73

#घोषणा REG_EXTEND1		0x76
#घोषणा REG_EXTEND2		0x77

#घोषणा REG_CONFIG3		0x78
#घोषणा REG_CONFIG5		0x7C
#घोषणा REG_CONFIG4		0x7D

#घोषणा REG_STATUS4		0x81	/* ADT7490 only */

#घोषणा REG_VTT_MIN		0x84	/* ADT7490 only */
#घोषणा REG_VTT_MAX		0x86	/* ADT7490 only */

#घोषणा VID_VIDSEL		0x80	/* ADT7476 only */

#घोषणा CONFIG2_ATTN		0x20

#घोषणा CONFIG3_SMBALERT	0x01
#घोषणा CONFIG3_THERM		0x02

#घोषणा CONFIG4_PINFUNC		0x03
#घोषणा CONFIG4_MAXDUTY		0x08
#घोषणा CONFIG4_ATTN_IN10	0x30
#घोषणा CONFIG4_ATTN_IN43	0xC0

#घोषणा CONFIG5_TWOSCOMP	0x01
#घोषणा CONFIG5_TEMPOFFSET	0x02
#घोषणा CONFIG5_VIDGPIO		0x10	/* ADT7476 only */

/* ADT7475 Settings */

#घोषणा ADT7475_VOLTAGE_COUNT	5	/* Not counting Vtt */
#घोषणा ADT7475_TEMP_COUNT	3
#घोषणा ADT7475_TACH_COUNT	4
#घोषणा ADT7475_PWM_COUNT	3

/* Macro to पढ़ो the रेजिस्टरs */

#घोषणा adt7475_पढ़ो(reg) i2c_smbus_पढ़ो_byte_data(client, (reg))

/* Macros to easily index the रेजिस्टरs */

#घोषणा TACH_REG(idx) (REG_TACH_BASE + ((idx) * 2))
#घोषणा TACH_MIN_REG(idx) (REG_TACH_MIN_BASE + ((idx) * 2))

#घोषणा PWM_REG(idx) (REG_PWM_BASE + (idx))
#घोषणा PWM_MAX_REG(idx) (REG_PWM_MAX_BASE + (idx))
#घोषणा PWM_MIN_REG(idx) (REG_PWM_MIN_BASE + (idx))
#घोषणा PWM_CONFIG_REG(idx) (REG_PWM_CONFIG_BASE + (idx))

#घोषणा VOLTAGE_REG(idx) (REG_VOLTAGE_BASE + (idx))
#घोषणा VOLTAGE_MIN_REG(idx) (REG_VOLTAGE_MIN_BASE + ((idx) * 2))
#घोषणा VOLTAGE_MAX_REG(idx) (REG_VOLTAGE_MAX_BASE + ((idx) * 2))

#घोषणा TEMP_REG(idx) (REG_TEMP_BASE + (idx))
#घोषणा TEMP_MIN_REG(idx) (REG_TEMP_MIN_BASE + ((idx) * 2))
#घोषणा TEMP_MAX_REG(idx) (REG_TEMP_MAX_BASE + ((idx) * 2))
#घोषणा TEMP_TMIN_REG(idx) (REG_TEMP_TMIN_BASE + (idx))
#घोषणा TEMP_THERM_REG(idx) (REG_TEMP_THERM_BASE + (idx))
#घोषणा TEMP_OFFSET_REG(idx) (REG_TEMP_OFFSET_BASE + (idx))
#घोषणा TEMP_TRANGE_REG(idx) (REG_TEMP_TRANGE_BASE + (idx))

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2c, 0x2d, 0x2e, I2C_CLIENT_END पूर्ण;

क्रमागत chips अणु adt7473, adt7475, adt7476, adt7490 पूर्ण;

अटल स्थिर काष्ठा i2c_device_id adt7475_id[] = अणु
	अणु "adt7473", adt7473 पूर्ण,
	अणु "adt7475", adt7475 पूर्ण,
	अणु "adt7476", adt7476 पूर्ण,
	अणु "adt7490", adt7490 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adt7475_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused adt7475_of_match[] = अणु
	अणु
		.compatible = "adi,adt7473",
		.data = (व्योम *)adt7473
	पूर्ण,
	अणु
		.compatible = "adi,adt7475",
		.data = (व्योम *)adt7475
	पूर्ण,
	अणु
		.compatible = "adi,adt7476",
		.data = (व्योम *)adt7476
	पूर्ण,
	अणु
		.compatible = "adi,adt7490",
		.data = (व्योम *)adt7490
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adt7475_of_match);

काष्ठा adt7475_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;

	अचिन्हित दीर्घ measure_updated;
	bool valid;

	u8 config2;
	u8 config4;
	u8 config5;
	u8 has_voltage;
	u8 bypass_attn;		/* Bypass voltage attenuator */
	u8 has_pwm2:1;
	u8 has_fan4:1;
	u8 has_vid:1;
	u32 alarms;
	u16 voltage[3][6];
	u16 temp[7][3];
	u16 tach[2][4];
	u8 pwm[4][3];
	u8 range[3];
	u8 pwmctl[3];
	u8 pwmchan[3];
	u8 enh_acoustics[2];

	u8 vid;
	u8 vrm;
	स्थिर काष्ठा attribute_group *groups[9];
पूर्ण;

अटल काष्ठा i2c_driver adt7475_driver;
अटल काष्ठा adt7475_data *adt7475_update_device(काष्ठा device *dev);
अटल व्योम adt7475_पढ़ो_hystersis(काष्ठा i2c_client *client);
अटल व्योम adt7475_पढ़ो_pwm(काष्ठा i2c_client *client, पूर्णांक index);

/* Given a temp value, convert it to रेजिस्टर value */

अटल अंतरभूत u16 temp2reg(काष्ठा adt7475_data *data, दीर्घ val)
अणु
	u16 ret;

	अगर (!(data->config5 & CONFIG5_TWOSCOMP)) अणु
		val = clamp_val(val, -64000, 191000);
		ret = (val + 64500) / 1000;
	पूर्ण अन्यथा अणु
		val = clamp_val(val, -128000, 127000);
		अगर (val < -500)
			ret = (256500 + val) / 1000;
		अन्यथा
			ret = (val + 500) / 1000;
	पूर्ण

	वापस ret << 2;
पूर्ण

/* Given a रेजिस्टर value, convert it to a real temp value */

अटल अंतरभूत पूर्णांक reg2temp(काष्ठा adt7475_data *data, u16 reg)
अणु
	अगर (data->config5 & CONFIG5_TWOSCOMP) अणु
		अगर (reg >= 512)
			वापस (reg - 1024) * 250;
		अन्यथा
			वापस reg * 250;
	पूर्ण अन्यथा
		वापस (reg - 256) * 250;
पूर्ण

अटल अंतरभूत पूर्णांक tach2rpm(u16 tach)
अणु
	अगर (tach == 0 || tach == 0xFFFF)
		वापस 0;

	वापस (90000 * 60) / tach;
पूर्ण

अटल अंतरभूत u16 rpm2tach(अचिन्हित दीर्घ rpm)
अणु
	अगर (rpm == 0)
		वापस 0;

	वापस clamp_val((90000 * 60) / rpm, 1, 0xFFFF);
पूर्ण

/* Scaling factors क्रम voltage inमाला_दो, taken from the ADT7490 datasheet */
अटल स्थिर पूर्णांक adt7473_in_scaling[ADT7475_VOLTAGE_COUNT + 1][2] = अणु
	अणु 45, 94 पूर्ण,	/* +2.5V */
	अणु 175, 525 पूर्ण,	/* Vccp */
	अणु 68, 71 पूर्ण,	/* Vcc */
	अणु 93, 47 पूर्ण,	/* +5V */
	अणु 120, 20 पूर्ण,	/* +12V */
	अणु 45, 45 पूर्ण,	/* Vtt */
पूर्ण;

अटल अंतरभूत पूर्णांक reg2volt(पूर्णांक channel, u16 reg, u8 bypass_attn)
अणु
	स्थिर पूर्णांक *r = adt7473_in_scaling[channel];

	अगर (bypass_attn & (1 << channel))
		वापस DIV_ROUND_CLOSEST(reg * 2250, 1024);
	वापस DIV_ROUND_CLOSEST(reg * (r[0] + r[1]) * 2250, r[1] * 1024);
पूर्ण

अटल अंतरभूत u16 volt2reg(पूर्णांक channel, दीर्घ volt, u8 bypass_attn)
अणु
	स्थिर पूर्णांक *r = adt7473_in_scaling[channel];
	दीर्घ reg;

	अगर (bypass_attn & (1 << channel))
		reg = DIV_ROUND_CLOSEST(volt * 1024, 2250);
	अन्यथा
		reg = DIV_ROUND_CLOSEST(volt * r[1] * 1024,
					(r[0] + r[1]) * 2250);
	वापस clamp_val(reg, 0, 1023) & (0xff << 2);
पूर्ण

अटल पूर्णांक adt7475_पढ़ो_word(काष्ठा i2c_client *client, पूर्णांक reg)
अणु
	पूर्णांक val1, val2;

	val1 = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (val1 < 0)
		वापस val1;
	val2 = i2c_smbus_पढ़ो_byte_data(client, reg + 1);
	अगर (val2 < 0)
		वापस val2;

	वापस val1 | (val2 << 8);
पूर्ण

अटल व्योम adt7475_ग_लिखो_word(काष्ठा i2c_client *client, पूर्णांक reg, u16 val)
अणु
	i2c_smbus_ग_लिखो_byte_data(client, reg + 1, val >> 8);
	i2c_smbus_ग_लिखो_byte_data(client, reg, val & 0xFF);
पूर्ण

अटल sमाप_प्रकार voltage_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा adt7475_data *data = adt7475_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	अचिन्हित लघु val;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	चयन (sattr->nr) अणु
	हाल ALARM:
		वापस प्र_लिखो(buf, "%d\n",
			       (data->alarms >> sattr->index) & 1);
	शेष:
		val = data->voltage[sattr->nr][sattr->index];
		वापस प्र_लिखो(buf, "%d\n",
			       reg2volt(sattr->index, val, data->bypass_attn));
	पूर्ण
पूर्ण

अटल sमाप_प्रकार voltage_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु

	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा adt7475_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित अक्षर reg;
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val))
		वापस -EINVAL;

	mutex_lock(&data->lock);

	data->voltage[sattr->nr][sattr->index] =
				volt2reg(sattr->index, val, data->bypass_attn);

	अगर (sattr->index < ADT7475_VOLTAGE_COUNT) अणु
		अगर (sattr->nr == MIN)
			reg = VOLTAGE_MIN_REG(sattr->index);
		अन्यथा
			reg = VOLTAGE_MAX_REG(sattr->index);
	पूर्ण अन्यथा अणु
		अगर (sattr->nr == MIN)
			reg = REG_VTT_MIN;
		अन्यथा
			reg = REG_VTT_MAX;
	पूर्ण

	i2c_smbus_ग_लिखो_byte_data(client, reg,
				  data->voltage[sattr->nr][sattr->index] >> 2);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा adt7475_data *data = adt7475_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक out;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	चयन (sattr->nr) अणु
	हाल HYSTERSIS:
		mutex_lock(&data->lock);
		out = data->temp[sattr->nr][sattr->index];
		अगर (sattr->index != 1)
			out = (out >> 4) & 0xF;
		अन्यथा
			out = (out & 0xF);
		/*
		 * Show the value as an असलolute number tied to
		 * THERM
		 */
		out = reg2temp(data, data->temp[THERM][sattr->index]) -
			out * 1000;
		mutex_unlock(&data->lock);
		अवरोध;

	हाल OFFSET:
		/*
		 * Offset is always 2's complement, regardless of the
		 * setting in CONFIG5
		 */
		mutex_lock(&data->lock);
		out = (s8)data->temp[sattr->nr][sattr->index];
		अगर (data->config5 & CONFIG5_TEMPOFFSET)
			out *= 1000;
		अन्यथा
			out *= 500;
		mutex_unlock(&data->lock);
		अवरोध;

	हाल ALARM:
		out = (data->alarms >> (sattr->index + 4)) & 1;
		अवरोध;

	हाल FAULT:
		/* Note - only क्रम remote1 and remote2 */
		out = !!(data->alarms & (sattr->index ? 0x8000 : 0x4000));
		अवरोध;

	शेष:
		/* All other temp values are in the configured क्रमmat */
		out = reg2temp(data, data->temp[sattr->nr][sattr->index]);
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", out);
पूर्ण

अटल sमाप_प्रकार temp_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा adt7475_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित अक्षर reg = 0;
	u8 out;
	पूर्णांक temp;
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val))
		वापस -EINVAL;

	mutex_lock(&data->lock);

	/* We need the config रेजिस्टर in all हालs क्रम temp <-> reg conv. */
	data->config5 = adt7475_पढ़ो(REG_CONFIG5);

	चयन (sattr->nr) अणु
	हाल OFFSET:
		अगर (data->config5 & CONFIG5_TEMPOFFSET) अणु
			val = clamp_val(val, -63000, 127000);
			out = data->temp[OFFSET][sattr->index] = val / 1000;
		पूर्ण अन्यथा अणु
			val = clamp_val(val, -63000, 64000);
			out = data->temp[OFFSET][sattr->index] = val / 500;
		पूर्ण
		अवरोध;

	हाल HYSTERSIS:
		/*
		 * The value will be given as an असलolute value, turn it
		 * पूर्णांकo an offset based on THERM
		 */

		/* Read fresh THERM and HYSTERSIS values from the chip */
		data->temp[THERM][sattr->index] =
			adt7475_पढ़ो(TEMP_THERM_REG(sattr->index)) << 2;
		adt7475_पढ़ो_hystersis(client);

		temp = reg2temp(data, data->temp[THERM][sattr->index]);
		val = clamp_val(val, temp - 15000, temp);
		val = (temp - val) / 1000;

		अगर (sattr->index != 1) अणु
			data->temp[HYSTERSIS][sattr->index] &= 0xF0;
			data->temp[HYSTERSIS][sattr->index] |= (val & 0xF) << 4;
		पूर्ण अन्यथा अणु
			data->temp[HYSTERSIS][sattr->index] &= 0x0F;
			data->temp[HYSTERSIS][sattr->index] |= (val & 0xF);
		पूर्ण

		out = data->temp[HYSTERSIS][sattr->index];
		अवरोध;

	शेष:
		data->temp[sattr->nr][sattr->index] = temp2reg(data, val);

		/*
		 * We मुख्यtain an extra 2 digits of precision क्रम simplicity
		 * - shअगरt those back off beक्रमe writing the value
		 */
		out = (u8) (data->temp[sattr->nr][sattr->index] >> 2);
	पूर्ण

	चयन (sattr->nr) अणु
	हाल MIN:
		reg = TEMP_MIN_REG(sattr->index);
		अवरोध;
	हाल MAX:
		reg = TEMP_MAX_REG(sattr->index);
		अवरोध;
	हाल OFFSET:
		reg = TEMP_OFFSET_REG(sattr->index);
		अवरोध;
	हाल AUTOMIN:
		reg = TEMP_TMIN_REG(sattr->index);
		अवरोध;
	हाल THERM:
		reg = TEMP_THERM_REG(sattr->index);
		अवरोध;
	हाल HYSTERSIS:
		अगर (sattr->index != 2)
			reg = REG_REMOTE1_HYSTERSIS;
		अन्यथा
			reg = REG_REMOTE2_HYSTERSIS;

		अवरोध;
	पूर्ण

	i2c_smbus_ग_लिखो_byte_data(client, reg, out);

	mutex_unlock(&data->lock);
	वापस count;
पूर्ण

/* Assuming CONFIG6[SLOW] is 0 */
अटल स्थिर पूर्णांक ad7475_st_map[] = अणु
	37500, 18800, 12500, 7500, 4700, 3100, 1600, 800,
पूर्ण;

अटल sमाप_प्रकार temp_st_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा adt7475_data *data = dev_get_drvdata(dev);
	दीर्घ val;

	चयन (sattr->index) अणु
	हाल 0:
		val = data->enh_acoustics[0] & 0xf;
		अवरोध;
	हाल 1:
		val = (data->enh_acoustics[1] >> 4) & 0xf;
		अवरोध;
	हाल 2:
	शेष:
		val = data->enh_acoustics[1] & 0xf;
		अवरोध;
	पूर्ण

	अगर (val & 0x8)
		वापस प्र_लिखो(buf, "%d\n", ad7475_st_map[val & 0x7]);
	अन्यथा
		वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार temp_st_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा adt7475_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित अक्षर reg;
	पूर्णांक shअगरt, idx;
	uदीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	चयन (sattr->index) अणु
	हाल 0:
		reg = REG_ENHANCE_ACOUSTICS1;
		shअगरt = 0;
		idx = 0;
		अवरोध;
	हाल 1:
		reg = REG_ENHANCE_ACOUSTICS2;
		shअगरt = 0;
		idx = 1;
		अवरोध;
	हाल 2:
	शेष:
		reg = REG_ENHANCE_ACOUSTICS2;
		shअगरt = 4;
		idx = 1;
		अवरोध;
	पूर्ण

	अगर (val > 0) अणु
		val = find_बंदst_descending(val, ad7475_st_map,
					      ARRAY_SIZE(ad7475_st_map));
		val |= 0x8;
	पूर्ण

	mutex_lock(&data->lock);

	data->enh_acoustics[idx] &= ~(0xf << shअगरt);
	data->enh_acoustics[idx] |= (val << shअगरt);

	i2c_smbus_ग_लिखो_byte_data(client, reg, data->enh_acoustics[idx]);

	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

/*
 * Table of स्वतःrange values - the user will ग_लिखो the value in millidegrees,
 * and we'll convert it
 */
अटल स्थिर पूर्णांक स्वतःrange_table[] = अणु
	2000, 2500, 3330, 4000, 5000, 6670, 8000,
	10000, 13330, 16000, 20000, 26670, 32000, 40000,
	53330, 80000
पूर्ण;

अटल sमाप_प्रकार poपूर्णांक2_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा adt7475_data *data = adt7475_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक out, val;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	mutex_lock(&data->lock);
	out = (data->range[sattr->index] >> 4) & 0x0F;
	val = reg2temp(data, data->temp[AUTOMIN][sattr->index]);
	mutex_unlock(&data->lock);

	वापस प्र_लिखो(buf, "%d\n", val + स्वतःrange_table[out]);
पूर्ण

अटल sमाप_प्रकार poपूर्णांक2_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adt7475_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक temp;
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val))
		वापस -EINVAL;

	mutex_lock(&data->lock);

	/* Get a fresh copy of the needed रेजिस्टरs */
	data->config5 = adt7475_पढ़ो(REG_CONFIG5);
	data->temp[AUTOMIN][sattr->index] =
		adt7475_पढ़ो(TEMP_TMIN_REG(sattr->index)) << 2;
	data->range[sattr->index] =
		adt7475_पढ़ो(TEMP_TRANGE_REG(sattr->index));

	/*
	 * The user will ग_लिखो an असलolute value, so subtract the start poपूर्णांक
	 * to figure the range
	 */
	temp = reg2temp(data, data->temp[AUTOMIN][sattr->index]);
	val = clamp_val(val, temp + स्वतःrange_table[0],
		temp + स्वतःrange_table[ARRAY_SIZE(स्वतःrange_table) - 1]);
	val -= temp;

	/* Find the nearest table entry to what the user wrote */
	val = find_बंदst(val, स्वतःrange_table, ARRAY_SIZE(स्वतःrange_table));

	data->range[sattr->index] &= ~0xF0;
	data->range[sattr->index] |= val << 4;

	i2c_smbus_ग_लिखो_byte_data(client, TEMP_TRANGE_REG(sattr->index),
				  data->range[sattr->index]);

	mutex_unlock(&data->lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार tach_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा adt7475_data *data = adt7475_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक out;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	अगर (sattr->nr == ALARM)
		out = (data->alarms >> (sattr->index + 10)) & 1;
	अन्यथा
		out = tach2rpm(data->tach[sattr->nr][sattr->index]);

	वापस प्र_लिखो(buf, "%d\n", out);
पूर्ण

अटल sमाप_प्रकार tach_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु

	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा adt7475_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	mutex_lock(&data->lock);

	data->tach[MIN][sattr->index] = rpm2tach(val);

	adt7475_ग_लिखो_word(client, TACH_MIN_REG(sattr->index),
			   data->tach[MIN][sattr->index]);

	mutex_unlock(&data->lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा adt7475_data *data = adt7475_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", data->pwm[sattr->nr][sattr->index]);
पूर्ण

अटल sमाप_प्रकार pwmchan_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा adt7475_data *data = adt7475_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", data->pwmchan[sattr->index]);
पूर्ण

अटल sमाप_प्रकार pwmctrl_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा adt7475_data *data = adt7475_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", data->pwmctl[sattr->index]);
पूर्ण

अटल sमाप_प्रकार pwm_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु

	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा adt7475_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित अक्षर reg = 0;
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val))
		वापस -EINVAL;

	mutex_lock(&data->lock);

	चयन (sattr->nr) अणु
	हाल INPUT:
		/* Get a fresh value क्रम CONTROL */
		data->pwm[CONTROL][sattr->index] =
			adt7475_पढ़ो(PWM_CONFIG_REG(sattr->index));

		/*
		 * If we are not in manual mode, then we shouldn't allow
		 * the user to set the pwm speed
		 */
		अगर (((data->pwm[CONTROL][sattr->index] >> 5) & 7) != 7) अणु
			mutex_unlock(&data->lock);
			वापस count;
		पूर्ण

		reg = PWM_REG(sattr->index);
		अवरोध;

	हाल MIN:
		reg = PWM_MIN_REG(sattr->index);
		अवरोध;

	हाल MAX:
		reg = PWM_MAX_REG(sattr->index);
		अवरोध;
	पूर्ण

	data->pwm[sattr->nr][sattr->index] = clamp_val(val, 0, 0xFF);
	i2c_smbus_ग_लिखो_byte_data(client, reg,
				  data->pwm[sattr->nr][sattr->index]);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार stall_disable_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा adt7475_data *data = dev_get_drvdata(dev);

	u8 mask = BIT(5 + sattr->index);

	वापस प्र_लिखो(buf, "%d\n", !!(data->enh_acoustics[0] & mask));
पूर्ण

अटल sमाप_प्रकार stall_disable_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा adt7475_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	u8 mask = BIT(5 + sattr->index);

	अगर (kम_से_दीर्घ(buf, 10, &val))
		वापस -EINVAL;

	mutex_lock(&data->lock);

	data->enh_acoustics[0] &= ~mask;
	अगर (val)
		data->enh_acoustics[0] |= mask;

	i2c_smbus_ग_लिखो_byte_data(client, REG_ENHANCE_ACOUSTICS1,
				  data->enh_acoustics[0]);

	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

/* Called by set_pwmctrl and set_pwmchan */

अटल पूर्णांक hw_set_pwm(काष्ठा i2c_client *client, पूर्णांक index,
		      अचिन्हित पूर्णांक pwmctl, अचिन्हित पूर्णांक pwmchan)
अणु
	काष्ठा adt7475_data *data = i2c_get_clientdata(client);
	दीर्घ val = 0;

	चयन (pwmctl) अणु
	हाल 0:
		val = 0x03;	/* Run at full speed */
		अवरोध;
	हाल 1:
		val = 0x07;	/* Manual mode */
		अवरोध;
	हाल 2:
		चयन (pwmchan) अणु
		हाल 1:
			/* Remote1 controls PWM */
			val = 0x00;
			अवरोध;
		हाल 2:
			/* local controls PWM */
			val = 0x01;
			अवरोध;
		हाल 4:
			/* remote2 controls PWM */
			val = 0x02;
			अवरोध;
		हाल 6:
			/* local/remote2 control PWM */
			val = 0x05;
			अवरोध;
		हाल 7:
			/* All three control PWM */
			val = 0x06;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	data->pwmctl[index] = pwmctl;
	data->pwmchan[index] = pwmchan;

	data->pwm[CONTROL][index] &= ~0xE0;
	data->pwm[CONTROL][index] |= (val & 7) << 5;

	i2c_smbus_ग_लिखो_byte_data(client, PWM_CONFIG_REG(index),
				  data->pwm[CONTROL][index]);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार pwmchan_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा adt7475_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक r;
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val))
		वापस -EINVAL;

	mutex_lock(&data->lock);
	/* Read Modअगरy Write PWM values */
	adt7475_पढ़ो_pwm(client, sattr->index);
	r = hw_set_pwm(client, sattr->index, data->pwmctl[sattr->index], val);
	अगर (r)
		count = r;
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार pwmctrl_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा adt7475_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक r;
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val))
		वापस -EINVAL;

	mutex_lock(&data->lock);
	/* Read Modअगरy Write PWM values */
	adt7475_पढ़ो_pwm(client, sattr->index);
	r = hw_set_pwm(client, sattr->index, val, data->pwmchan[sattr->index]);
	अगर (r)
		count = r;
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

/* List of frequencies क्रम the PWM */
अटल स्थिर पूर्णांक pwmfreq_table[] = अणु
	11, 14, 22, 29, 35, 44, 58, 88, 22500
पूर्ण;

अटल sमाप_प्रकार pwmfreq_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा adt7475_data *data = adt7475_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	पूर्णांक idx;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);
	idx = clamp_val(data->range[sattr->index] & 0xf, 0,
			ARRAY_SIZE(pwmfreq_table) - 1);

	वापस प्र_लिखो(buf, "%d\n", pwmfreq_table[idx]);
पूर्ण

अटल sमाप_प्रकार pwmfreq_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			     माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा adt7475_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक out;
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val))
		वापस -EINVAL;

	out = find_बंदst(val, pwmfreq_table, ARRAY_SIZE(pwmfreq_table));

	mutex_lock(&data->lock);

	data->range[sattr->index] =
		adt7475_पढ़ो(TEMP_TRANGE_REG(sattr->index));
	data->range[sattr->index] &= ~0xf;
	data->range[sattr->index] |= out;

	i2c_smbus_ग_लिखो_byte_data(client, TEMP_TRANGE_REG(sattr->index),
				  data->range[sattr->index]);

	mutex_unlock(&data->lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार pwm_use_poपूर्णांक2_pwm_at_crit_show(काष्ठा device *dev,
					काष्ठा device_attribute *devattr,
					अक्षर *buf)
अणु
	काष्ठा adt7475_data *data = adt7475_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", !!(data->config4 & CONFIG4_MAXDUTY));
पूर्ण

अटल sमाप_प्रकार pwm_use_poपूर्णांक2_pwm_at_crit_store(काष्ठा device *dev,
					काष्ठा device_attribute *devattr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adt7475_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val))
		वापस -EINVAL;
	अगर (val != 0 && val != 1)
		वापस -EINVAL;

	mutex_lock(&data->lock);
	data->config4 = i2c_smbus_पढ़ो_byte_data(client, REG_CONFIG4);
	अगर (val)
		data->config4 |= CONFIG4_MAXDUTY;
	अन्यथा
		data->config4 &= ~CONFIG4_MAXDUTY;
	i2c_smbus_ग_लिखो_byte_data(client, REG_CONFIG4, data->config4);
	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार vrm_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा adt7475_data *data = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", (पूर्णांक)data->vrm);
पूर्ण

अटल sमाप_प्रकार vrm_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adt7475_data *data = dev_get_drvdata(dev);
	दीर्घ val;

	अगर (kम_से_दीर्घ(buf, 10, &val))
		वापस -EINVAL;
	अगर (val < 0 || val > 255)
		वापस -EINVAL;
	data->vrm = val;

	वापस count;
पूर्ण

अटल sमाप_प्रकार cpu0_vid_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा adt7475_data *data = adt7475_update_device(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", vid_from_reg(data->vid, data->vrm));
पूर्ण

अटल SENSOR_DEVICE_ATTR_2_RO(in0_input, voltage, INPUT, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in0_max, voltage, MAX, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in0_min, voltage, MIN, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(in0_alarm, voltage, ALARM, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(in1_input, voltage, INPUT, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in1_max, voltage, MAX, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in1_min, voltage, MIN, 1);
अटल SENSOR_DEVICE_ATTR_2_RO(in1_alarm, voltage, ALARM, 1);
अटल SENSOR_DEVICE_ATTR_2_RO(in2_input, voltage, INPUT, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(in2_max, voltage, MAX, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(in2_min, voltage, MIN, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(in2_alarm, voltage, ALARM, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(in3_input, voltage, INPUT, 3);
अटल SENSOR_DEVICE_ATTR_2_RW(in3_max, voltage, MAX, 3);
अटल SENSOR_DEVICE_ATTR_2_RW(in3_min, voltage, MIN, 3);
अटल SENSOR_DEVICE_ATTR_2_RO(in3_alarm, voltage, ALARM, 3);
अटल SENSOR_DEVICE_ATTR_2_RO(in4_input, voltage, INPUT, 4);
अटल SENSOR_DEVICE_ATTR_2_RW(in4_max, voltage, MAX, 4);
अटल SENSOR_DEVICE_ATTR_2_RW(in4_min, voltage, MIN, 4);
अटल SENSOR_DEVICE_ATTR_2_RO(in4_alarm, voltage, ALARM, 8);
अटल SENSOR_DEVICE_ATTR_2_RO(in5_input, voltage, INPUT, 5);
अटल SENSOR_DEVICE_ATTR_2_RW(in5_max, voltage, MAX, 5);
अटल SENSOR_DEVICE_ATTR_2_RW(in5_min, voltage, MIN, 5);
अटल SENSOR_DEVICE_ATTR_2_RO(in5_alarm, voltage, ALARM, 31);
अटल SENSOR_DEVICE_ATTR_2_RO(temp1_input, temp, INPUT, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(temp1_alarm, temp, ALARM, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(temp1_fault, temp, FAULT, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_max, temp, MAX, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_min, temp, MIN, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_offset, temp, OFFSET, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_स्वतः_poपूर्णांक1_temp, temp, AUTOMIN, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_स्वतः_poपूर्णांक2_temp, poपूर्णांक2, 0, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_crit, temp, THERM, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_crit_hyst, temp, HYSTERSIS, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(temp1_smoothing, temp_st, 0, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_input, temp, INPUT, 1);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_alarm, temp, ALARM, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_max, temp, MAX, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_min, temp, MIN, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_offset, temp, OFFSET, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_स्वतः_poपूर्णांक1_temp, temp, AUTOMIN, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_स्वतः_poपूर्णांक2_temp, poपूर्णांक2, 0, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_crit, temp, THERM, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_crit_hyst, temp, HYSTERSIS, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(temp2_smoothing, temp_st, 0, 1);
अटल SENSOR_DEVICE_ATTR_2_RO(temp3_input, temp, INPUT, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(temp3_alarm, temp, ALARM, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(temp3_fault, temp, FAULT, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_max, temp, MAX, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_min, temp, MIN, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_offset, temp, OFFSET, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_स्वतः_poपूर्णांक1_temp, temp, AUTOMIN, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_स्वतः_poपूर्णांक2_temp, poपूर्णांक2, 0, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_crit, temp, THERM, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_crit_hyst, temp, HYSTERSIS, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(temp3_smoothing, temp_st, 0, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(fan1_input, tach, INPUT, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(fan1_min, tach, MIN, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(fan1_alarm, tach, ALARM, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(fan2_input, tach, INPUT, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(fan2_min, tach, MIN, 1);
अटल SENSOR_DEVICE_ATTR_2_RO(fan2_alarm, tach, ALARM, 1);
अटल SENSOR_DEVICE_ATTR_2_RO(fan3_input, tach, INPUT, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(fan3_min, tach, MIN, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(fan3_alarm, tach, ALARM, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(fan4_input, tach, INPUT, 3);
अटल SENSOR_DEVICE_ATTR_2_RW(fan4_min, tach, MIN, 3);
अटल SENSOR_DEVICE_ATTR_2_RO(fan4_alarm, tach, ALARM, 3);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm1, pwm, INPUT, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm1_freq, pwmfreq, INPUT, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm1_enable, pwmctrl, INPUT, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm1_स्वतः_channels_temp, pwmchan, INPUT, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm1_स्वतः_poपूर्णांक1_pwm, pwm, MIN, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm1_स्वतः_poपूर्णांक2_pwm, pwm, MAX, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm1_stall_disable, stall_disable, 0, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm2, pwm, INPUT, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm2_freq, pwmfreq, INPUT, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm2_enable, pwmctrl, INPUT, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm2_स्वतः_channels_temp, pwmchan, INPUT, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm2_स्वतः_poपूर्णांक1_pwm, pwm, MIN, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm2_स्वतः_poपूर्णांक2_pwm, pwm, MAX, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm2_stall_disable, stall_disable, 0, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm3, pwm, INPUT, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm3_freq, pwmfreq, INPUT, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm3_enable, pwmctrl, INPUT, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm3_स्वतः_channels_temp, pwmchan, INPUT, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm3_स्वतः_poपूर्णांक1_pwm, pwm, MIN, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm3_स्वतः_poपूर्णांक2_pwm, pwm, MAX, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(pwm3_stall_disable, stall_disable, 0, 2);

/* Non-standard name, might need revisiting */
अटल DEVICE_ATTR_RW(pwm_use_poपूर्णांक2_pwm_at_crit);

अटल DEVICE_ATTR_RW(vrm);
अटल DEVICE_ATTR_RO(cpu0_vid);

अटल काष्ठा attribute *adt7475_attrs[] = अणु
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in1_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_fault.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_offset.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_temp1_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_smoothing.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp2_offset.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_temp2_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_temp2_crit.dev_attr.attr,
	&sensor_dev_attr_temp2_crit_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_smoothing.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_fault.dev_attr.attr,
	&sensor_dev_attr_temp3_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp3_offset.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_poपूर्णांक1_temp.dev_attr.attr,
	&sensor_dev_attr_temp3_स्वतः_poपूर्णांक2_temp.dev_attr.attr,
	&sensor_dev_attr_temp3_crit.dev_attr.attr,
	&sensor_dev_attr_temp3_crit_hyst.dev_attr.attr,
	&sensor_dev_attr_temp3_smoothing.dev_attr.attr,
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan2_min.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan3_min.dev_attr.attr,
	&sensor_dev_attr_fan3_alarm.dev_attr.attr,
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm1_freq.dev_attr.attr,
	&sensor_dev_attr_pwm1_enable.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_channels_temp.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm1_stall_disable.dev_attr.attr,
	&sensor_dev_attr_pwm3.dev_attr.attr,
	&sensor_dev_attr_pwm3_freq.dev_attr.attr,
	&sensor_dev_attr_pwm3_enable.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_channels_temp.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm3_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm3_stall_disable.dev_attr.attr,
	&dev_attr_pwm_use_poपूर्णांक2_pwm_at_crit.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *fan4_attrs[] = अणु
	&sensor_dev_attr_fan4_input.dev_attr.attr,
	&sensor_dev_attr_fan4_min.dev_attr.attr,
	&sensor_dev_attr_fan4_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *pwm2_attrs[] = अणु
	&sensor_dev_attr_pwm2.dev_attr.attr,
	&sensor_dev_attr_pwm2_freq.dev_attr.attr,
	&sensor_dev_attr_pwm2_enable.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_channels_temp.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक1_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm2_स्वतः_poपूर्णांक2_pwm.dev_attr.attr,
	&sensor_dev_attr_pwm2_stall_disable.dev_attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *in0_attrs[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in0_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *in3_attrs[] = अणु
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *in4_attrs[] = अणु
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *in5_attrs[] = अणु
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in5_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *vid_attrs[] = अणु
	&dev_attr_cpu0_vid.attr,
	&dev_attr_vrm.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adt7475_attr_group = अणु .attrs = adt7475_attrs पूर्ण;
अटल स्थिर काष्ठा attribute_group fan4_attr_group = अणु .attrs = fan4_attrs पूर्ण;
अटल स्थिर काष्ठा attribute_group pwm2_attr_group = अणु .attrs = pwm2_attrs पूर्ण;
अटल स्थिर काष्ठा attribute_group in0_attr_group = अणु .attrs = in0_attrs पूर्ण;
अटल स्थिर काष्ठा attribute_group in3_attr_group = अणु .attrs = in3_attrs पूर्ण;
अटल स्थिर काष्ठा attribute_group in4_attr_group = अणु .attrs = in4_attrs पूर्ण;
अटल स्थिर काष्ठा attribute_group in5_attr_group = अणु .attrs = in5_attrs पूर्ण;
अटल स्थिर काष्ठा attribute_group vid_attr_group = अणु .attrs = vid_attrs पूर्ण;

अटल पूर्णांक adt7475_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक vendid, devid, devid2;
	स्थिर अक्षर *name;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	vendid = adt7475_पढ़ो(REG_VENDID);
	devid2 = adt7475_पढ़ो(REG_DEVID2);
	अगर (vendid != 0x41 ||		/* Analog Devices */
	    (devid2 & 0xf8) != 0x68)
		वापस -ENODEV;

	devid = adt7475_पढ़ो(REG_DEVID);
	अगर (devid == 0x73)
		name = "adt7473";
	अन्यथा अगर (devid == 0x75 && client->addr == 0x2e)
		name = "adt7475";
	अन्यथा अगर (devid == 0x76)
		name = "adt7476";
	अन्यथा अगर ((devid2 & 0xfc) == 0x6c)
		name = "adt7490";
	अन्यथा अणु
		dev_dbg(&adapter->dev,
			"Couldn't detect an ADT7473/75/76/90 part at "
			"0x%02x\n", (अचिन्हित पूर्णांक)client->addr);
		वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, name, I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक adt7475_update_limits(काष्ठा i2c_client *client)
अणु
	काष्ठा adt7475_data *data = i2c_get_clientdata(client);
	पूर्णांक i;
	पूर्णांक ret;

	ret = adt7475_पढ़ो(REG_CONFIG4);
	अगर (ret < 0)
		वापस ret;
	data->config4 = ret;

	ret = adt7475_पढ़ो(REG_CONFIG5);
	अगर (ret < 0)
		वापस ret;
	data->config5 = ret;

	क्रम (i = 0; i < ADT7475_VOLTAGE_COUNT; i++) अणु
		अगर (!(data->has_voltage & (1 << i)))
			जारी;
		/* Adjust values so they match the input precision */
		ret = adt7475_पढ़ो(VOLTAGE_MIN_REG(i));
		अगर (ret < 0)
			वापस ret;
		data->voltage[MIN][i] = ret << 2;

		ret = adt7475_पढ़ो(VOLTAGE_MAX_REG(i));
		अगर (ret < 0)
			वापस ret;
		data->voltage[MAX][i] = ret << 2;
	पूर्ण

	अगर (data->has_voltage & (1 << 5)) अणु
		ret = adt7475_पढ़ो(REG_VTT_MIN);
		अगर (ret < 0)
			वापस ret;
		data->voltage[MIN][5] = ret << 2;

		ret = adt7475_पढ़ो(REG_VTT_MAX);
		अगर (ret < 0)
			वापस ret;
		data->voltage[MAX][5] = ret << 2;
	पूर्ण

	क्रम (i = 0; i < ADT7475_TEMP_COUNT; i++) अणु
		/* Adjust values so they match the input precision */
		ret = adt7475_पढ़ो(TEMP_MIN_REG(i));
		अगर (ret < 0)
			वापस ret;
		data->temp[MIN][i] = ret << 2;

		ret = adt7475_पढ़ो(TEMP_MAX_REG(i));
		अगर (ret < 0)
			वापस ret;
		data->temp[MAX][i] = ret << 2;

		ret = adt7475_पढ़ो(TEMP_TMIN_REG(i));
		अगर (ret < 0)
			वापस ret;
		data->temp[AUTOMIN][i] = ret << 2;

		ret = adt7475_पढ़ो(TEMP_THERM_REG(i));
		अगर (ret < 0)
			वापस ret;
		data->temp[THERM][i] = ret << 2;

		ret = adt7475_पढ़ो(TEMP_OFFSET_REG(i));
		अगर (ret < 0)
			वापस ret;
		data->temp[OFFSET][i] = ret;
	पूर्ण
	adt7475_पढ़ो_hystersis(client);

	क्रम (i = 0; i < ADT7475_TACH_COUNT; i++) अणु
		अगर (i == 3 && !data->has_fan4)
			जारी;
		ret = adt7475_पढ़ो_word(client, TACH_MIN_REG(i));
		अगर (ret < 0)
			वापस ret;
		data->tach[MIN][i] = ret;
	पूर्ण

	क्रम (i = 0; i < ADT7475_PWM_COUNT; i++) अणु
		अगर (i == 1 && !data->has_pwm2)
			जारी;
		ret = adt7475_पढ़ो(PWM_MAX_REG(i));
		अगर (ret < 0)
			वापस ret;
		data->pwm[MAX][i] = ret;

		ret = adt7475_पढ़ो(PWM_MIN_REG(i));
		अगर (ret < 0)
			वापस ret;
		data->pwm[MIN][i] = ret;
		/* Set the channel and control inक्रमmation */
		adt7475_पढ़ो_pwm(client, i);
	पूर्ण

	ret = adt7475_पढ़ो(TEMP_TRANGE_REG(0));
	अगर (ret < 0)
		वापस ret;
	data->range[0] = ret;

	ret = adt7475_पढ़ो(TEMP_TRANGE_REG(1));
	अगर (ret < 0)
		वापस ret;
	data->range[1] = ret;

	ret = adt7475_पढ़ो(TEMP_TRANGE_REG(2));
	अगर (ret < 0)
		वापस ret;
	data->range[2] = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक set_property_bit(स्थिर काष्ठा i2c_client *client, अक्षर *property,
			    u8 *config, u8 bit_index)
अणु
	u32 prop_value = 0;
	पूर्णांक ret = of_property_पढ़ो_u32(client->dev.of_node, property,
					&prop_value);

	अगर (!ret) अणु
		अगर (prop_value)
			*config |= (1 << bit_index);
		अन्यथा
			*config &= ~(1 << bit_index);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक load_attenuators(स्थिर काष्ठा i2c_client *client, पूर्णांक chip,
			    काष्ठा adt7475_data *data)
अणु
	पूर्णांक ret;

	अगर (chip == adt7476 || chip == adt7490) अणु
		set_property_bit(client, "adi,bypass-attenuator-in0",
				 &data->config4, 4);
		set_property_bit(client, "adi,bypass-attenuator-in1",
				 &data->config4, 5);
		set_property_bit(client, "adi,bypass-attenuator-in3",
				 &data->config4, 6);
		set_property_bit(client, "adi,bypass-attenuator-in4",
				 &data->config4, 7);

		ret = i2c_smbus_ग_लिखो_byte_data(client, REG_CONFIG4,
						data->config4);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (chip == adt7473 || chip == adt7475) अणु
		set_property_bit(client, "adi,bypass-attenuator-in1",
				 &data->config2, 5);

		ret = i2c_smbus_ग_लिखो_byte_data(client, REG_CONFIG2,
						data->config2);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adt7475_set_pwm_polarity(काष्ठा i2c_client *client)
अणु
	u32 states[ADT7475_PWM_COUNT];
	पूर्णांक ret, i;
	u8 val;

	ret = of_property_पढ़ो_u32_array(client->dev.of_node,
					 "adi,pwm-active-state", states,
					 ARRAY_SIZE(states));
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ADT7475_PWM_COUNT; i++) अणु
		ret = adt7475_पढ़ो(PWM_CONFIG_REG(i));
		अगर (ret < 0)
			वापस ret;
		val = ret;
		अगर (states[i])
			val &= ~BIT(4);
		अन्यथा
			val |= BIT(4);

		ret = i2c_smbus_ग_लिखो_byte_data(client, PWM_CONFIG_REG(i), val);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adt7475_probe(काष्ठा i2c_client *client)
अणु
	क्रमागत chips chip;
	अटल स्थिर अक्षर * स्थिर names[] = अणु
		[adt7473] = "ADT7473",
		[adt7475] = "ADT7475",
		[adt7476] = "ADT7476",
		[adt7490] = "ADT7490",
	पूर्ण;

	काष्ठा adt7475_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक i, ret = 0, revision, group_num = 0;
	u8 config3;
	स्थिर काष्ठा i2c_device_id *id = i2c_match_id(adt7475_id, client);

	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	mutex_init(&data->lock);
	data->client = client;
	i2c_set_clientdata(client, data);

	अगर (client->dev.of_node)
		chip = (क्रमागत chips)of_device_get_match_data(&client->dev);
	अन्यथा
		chip = id->driver_data;

	/* Initialize device-specअगरic values */
	चयन (chip) अणु
	हाल adt7476:
		data->has_voltage = 0x0e;	/* in1 to in3 */
		revision = adt7475_पढ़ो(REG_DEVID2) & 0x07;
		अवरोध;
	हाल adt7490:
		data->has_voltage = 0x3e;	/* in1 to in5 */
		revision = adt7475_पढ़ो(REG_DEVID2) & 0x03;
		अगर (revision == 0x03)
			revision += adt7475_पढ़ो(REG_DEVREV2);
		अवरोध;
	शेष:
		data->has_voltage = 0x06;	/* in1, in2 */
		revision = adt7475_पढ़ो(REG_DEVID2) & 0x07;
	पूर्ण

	config3 = adt7475_पढ़ो(REG_CONFIG3);
	/* Pin PWM2 may alternatively be used क्रम ALERT output */
	अगर (!(config3 & CONFIG3_SMBALERT))
		data->has_pwm2 = 1;
	/* Meaning of this bit is inverted क्रम the ADT7473-1 */
	अगर (id->driver_data == adt7473 && revision >= 1)
		data->has_pwm2 = !data->has_pwm2;

	data->config4 = adt7475_पढ़ो(REG_CONFIG4);
	/* Pin TACH4 may alternatively be used क्रम THERM */
	अगर ((data->config4 & CONFIG4_PINFUNC) == 0x0)
		data->has_fan4 = 1;

	/*
	 * THERM configuration is more complex on the ADT7476 and ADT7490,
	 * because 2 dअगरferent pins (TACH4 and +2.5 Vin) can be used क्रम
	 * this function
	 */
	अगर (id->driver_data == adt7490) अणु
		अगर ((data->config4 & CONFIG4_PINFUNC) == 0x1 &&
		    !(config3 & CONFIG3_THERM))
			data->has_fan4 = 1;
	पूर्ण
	अगर (id->driver_data == adt7476 || id->driver_data == adt7490) अणु
		अगर (!(config3 & CONFIG3_THERM) ||
		    (data->config4 & CONFIG4_PINFUNC) == 0x1)
			data->has_voltage |= (1 << 0);		/* in0 */
	पूर्ण

	/*
	 * On the ADT7476, the +12V input pin may instead be used as VID5,
	 * and VID pins may alternatively be used as GPIO
	 */
	अगर (id->driver_data == adt7476) अणु
		u8 vid = adt7475_पढ़ो(REG_VID);
		अगर (!(vid & VID_VIDSEL))
			data->has_voltage |= (1 << 4);		/* in4 */

		data->has_vid = !(adt7475_पढ़ो(REG_CONFIG5) & CONFIG5_VIDGPIO);
	पूर्ण

	/* Voltage attenuators can be bypassed, globally or inभागidually */
	data->config2 = adt7475_पढ़ो(REG_CONFIG2);
	ret = load_attenuators(client, chip, data);
	अगर (ret)
		dev_warn(&client->dev, "Error configuring attenuator bypass\n");

	अगर (data->config2 & CONFIG2_ATTN) अणु
		data->bypass_attn = (0x3 << 3) | 0x3;
	पूर्ण अन्यथा अणु
		data->bypass_attn = ((data->config4 & CONFIG4_ATTN_IN10) >> 4) |
				    ((data->config4 & CONFIG4_ATTN_IN43) >> 3);
	पूर्ण
	data->bypass_attn &= data->has_voltage;

	/*
	 * Call adt7475_पढ़ो_pwm क्रम all pwm's as this will reprogram any
	 * pwm's which are disabled to manual mode with 0% duty cycle
	 */
	क्रम (i = 0; i < ADT7475_PWM_COUNT; i++)
		adt7475_पढ़ो_pwm(client, i);

	ret = adt7475_set_pwm_polarity(client);
	अगर (ret && ret != -EINVAL)
		dev_warn(&client->dev, "Error configuring pwm polarity\n");

	/* Start monitoring */
	चयन (chip) अणु
	हाल adt7475:
	हाल adt7476:
		i2c_smbus_ग_लिखो_byte_data(client, REG_CONFIG1,
					  adt7475_पढ़ो(REG_CONFIG1) | 0x01);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	data->groups[group_num++] = &adt7475_attr_group;

	/* Features that can be disabled inभागidually */
	अगर (data->has_fan4) अणु
		data->groups[group_num++] = &fan4_attr_group;
	पूर्ण
	अगर (data->has_pwm2) अणु
		data->groups[group_num++] = &pwm2_attr_group;
	पूर्ण
	अगर (data->has_voltage & (1 << 0)) अणु
		data->groups[group_num++] = &in0_attr_group;
	पूर्ण
	अगर (data->has_voltage & (1 << 3)) अणु
		data->groups[group_num++] = &in3_attr_group;
	पूर्ण
	अगर (data->has_voltage & (1 << 4)) अणु
		data->groups[group_num++] = &in4_attr_group;
	पूर्ण
	अगर (data->has_voltage & (1 << 5)) अणु
		data->groups[group_num++] = &in5_attr_group;
	पूर्ण
	अगर (data->has_vid) अणु
		data->vrm = vid_which_vrm();
		data->groups[group_num] = &vid_attr_group;
	पूर्ण

	/* रेजिस्टर device with all the acquired attributes */
	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&client->dev,
							   client->name, data,
							   data->groups);

	अगर (IS_ERR(hwmon_dev)) अणु
		ret = PTR_ERR(hwmon_dev);
		वापस ret;
	पूर्ण

	dev_info(&client->dev, "%s device, revision %d\n",
		 names[id->driver_data], revision);
	अगर ((data->has_voltage & 0x11) || data->has_fan4 || data->has_pwm2)
		dev_info(&client->dev, "Optional features:%s%s%s%s%s\n",
			 (data->has_voltage & (1 << 0)) ? " in0" : "",
			 (data->has_voltage & (1 << 4)) ? " in4" : "",
			 data->has_fan4 ? " fan4" : "",
			 data->has_pwm2 ? " pwm2" : "",
			 data->has_vid ? " vid" : "");
	अगर (data->bypass_attn)
		dev_info(&client->dev, "Bypassing attenuators on:%s%s%s%s\n",
			 (data->bypass_attn & (1 << 0)) ? " in0" : "",
			 (data->bypass_attn & (1 << 1)) ? " in1" : "",
			 (data->bypass_attn & (1 << 3)) ? " in3" : "",
			 (data->bypass_attn & (1 << 4)) ? " in4" : "");

	/* Limits and settings, should never change update more than once */
	ret = adt7475_update_limits(client);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver adt7475_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "adt7475",
		.of_match_table = of_match_ptr(adt7475_of_match),
	पूर्ण,
	.probe_new	= adt7475_probe,
	.id_table	= adt7475_id,
	.detect		= adt7475_detect,
	.address_list	= normal_i2c,
पूर्ण;

अटल व्योम adt7475_पढ़ो_hystersis(काष्ठा i2c_client *client)
अणु
	काष्ठा adt7475_data *data = i2c_get_clientdata(client);

	data->temp[HYSTERSIS][0] = (u16) adt7475_पढ़ो(REG_REMOTE1_HYSTERSIS);
	data->temp[HYSTERSIS][1] = data->temp[HYSTERSIS][0];
	data->temp[HYSTERSIS][2] = (u16) adt7475_पढ़ो(REG_REMOTE2_HYSTERSIS);
पूर्ण

अटल व्योम adt7475_पढ़ो_pwm(काष्ठा i2c_client *client, पूर्णांक index)
अणु
	काष्ठा adt7475_data *data = i2c_get_clientdata(client);
	अचिन्हित पूर्णांक v;

	data->pwm[CONTROL][index] = adt7475_पढ़ो(PWM_CONFIG_REG(index));

	/*
	 * Figure out the पूर्णांकernal value क्रम pwmctrl and pwmchan
	 * based on the current settings
	 */
	v = (data->pwm[CONTROL][index] >> 5) & 7;

	अगर (v == 3)
		data->pwmctl[index] = 0;
	अन्यथा अगर (v == 7)
		data->pwmctl[index] = 1;
	अन्यथा अगर (v == 4) अणु
		/*
		 * The fan is disabled - we करोn't want to
		 * support that, so change to manual mode and
		 * set the duty cycle to 0 instead
		 */
		data->pwm[INPUT][index] = 0;
		data->pwm[CONTROL][index] &= ~0xE0;
		data->pwm[CONTROL][index] |= (7 << 5);

		i2c_smbus_ग_लिखो_byte_data(client, PWM_CONFIG_REG(index),
					  data->pwm[INPUT][index]);

		i2c_smbus_ग_लिखो_byte_data(client, PWM_CONFIG_REG(index),
					  data->pwm[CONTROL][index]);

		data->pwmctl[index] = 1;
	पूर्ण अन्यथा अणु
		data->pwmctl[index] = 2;

		चयन (v) अणु
		हाल 0:
			data->pwmchan[index] = 1;
			अवरोध;
		हाल 1:
			data->pwmchan[index] = 2;
			अवरोध;
		हाल 2:
			data->pwmchan[index] = 4;
			अवरोध;
		हाल 5:
			data->pwmchan[index] = 6;
			अवरोध;
		हाल 6:
			data->pwmchan[index] = 7;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक adt7475_update_measure(काष्ठा device *dev)
अणु
	काष्ठा adt7475_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u16 ext;
	पूर्णांक i;
	पूर्णांक ret;

	ret = adt7475_पढ़ो(REG_STATUS2);
	अगर (ret < 0)
		वापस ret;
	data->alarms = ret << 8;

	ret = adt7475_पढ़ो(REG_STATUS1);
	अगर (ret < 0)
		वापस ret;
	data->alarms |= ret;

	ret = adt7475_पढ़ो(REG_EXTEND2);
	अगर (ret < 0)
		वापस ret;

	ext = (ret << 8);

	ret = adt7475_पढ़ो(REG_EXTEND1);
	अगर (ret < 0)
		वापस ret;

	ext |= ret;

	क्रम (i = 0; i < ADT7475_VOLTAGE_COUNT; i++) अणु
		अगर (!(data->has_voltage & (1 << i)))
			जारी;
		ret = adt7475_पढ़ो(VOLTAGE_REG(i));
		अगर (ret < 0)
			वापस ret;
		data->voltage[INPUT][i] =
			(ret << 2) |
			((ext >> (i * 2)) & 3);
	पूर्ण

	क्रम (i = 0; i < ADT7475_TEMP_COUNT; i++) अणु
		ret = adt7475_पढ़ो(TEMP_REG(i));
		अगर (ret < 0)
			वापस ret;
		data->temp[INPUT][i] =
			(ret << 2) |
			((ext >> ((i + 5) * 2)) & 3);
	पूर्ण

	अगर (data->has_voltage & (1 << 5)) अणु
		ret = adt7475_पढ़ो(REG_STATUS4);
		अगर (ret < 0)
			वापस ret;
		data->alarms |= ret << 24;

		ret = adt7475_पढ़ो(REG_EXTEND3);
		अगर (ret < 0)
			वापस ret;
		ext = ret;

		ret = adt7475_पढ़ो(REG_VTT);
		अगर (ret < 0)
			वापस ret;
		data->voltage[INPUT][5] = ret << 2 |
			((ext >> 4) & 3);
	पूर्ण

	क्रम (i = 0; i < ADT7475_TACH_COUNT; i++) अणु
		अगर (i == 3 && !data->has_fan4)
			जारी;
		ret = adt7475_पढ़ो_word(client, TACH_REG(i));
		अगर (ret < 0)
			वापस ret;
		data->tach[INPUT][i] = ret;
	पूर्ण

	/* Updated by hw when in स्वतः mode */
	क्रम (i = 0; i < ADT7475_PWM_COUNT; i++) अणु
		अगर (i == 1 && !data->has_pwm2)
			जारी;
		ret = adt7475_पढ़ो(PWM_REG(i));
		अगर (ret < 0)
			वापस ret;
		data->pwm[INPUT][i] = ret;
	पूर्ण

	अगर (data->has_vid) अणु
		ret = adt7475_पढ़ो(REG_VID);
		अगर (ret < 0)
			वापस ret;
		data->vid = ret & 0x3f;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा adt7475_data *adt7475_update_device(काष्ठा device *dev)
अणु
	काष्ठा adt7475_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	mutex_lock(&data->lock);

	/* Measurement values update every 2 seconds */
	अगर (समय_after(jअगरfies, data->measure_updated + HZ * 2) ||
	    !data->valid) अणु
		ret = adt7475_update_measure(dev);
		अगर (ret) अणु
			data->valid = false;
			mutex_unlock(&data->lock);
			वापस ERR_PTR(ret);
		पूर्ण
		data->measure_updated = jअगरfies;
		data->valid = true;
	पूर्ण

	mutex_unlock(&data->lock);

	वापस data;
पूर्ण

module_i2c_driver(adt7475_driver);

MODULE_AUTHOR("Advanced Micro Devices, Inc");
MODULE_DESCRIPTION("adt7475 driver");
MODULE_LICENSE("GPL");
