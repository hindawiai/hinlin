<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * adm9240.c	Part of lm_sensors, Linux kernel modules क्रम hardware
 *		monitoring
 *
 * Copyright (C) 1999	Froकरो Looijaard <froकरोl@dds.nl>
 *			Philip Edelbrock <phil@netroedge.com>
 * Copyright (C) 2003	Michiel Rook <michiel@grendelproject.nl>
 * Copyright (C) 2005	Grant Coady <gcoady.lk@gmail.com> with valuable
 *				guidance from Jean Delvare
 *
 * Driver supports	Analog Devices		ADM9240
 *			Dallas Semiconductor	DS1780
 *			National Semiconductor	LM81
 *
 * ADM9240 is the reference, DS1780 and LM81 are रेजिस्टर compatibles
 *
 * Voltage	Six inमाला_दो are scaled by chip, VID also reported
 * Temperature	Chip temperature to 0.5'C, maximum and max_hysteris
 * Fans		2 fans, low speed alarm, स्वतःmatic fan घड़ी भागider
 * Alarms	16-bit map of active alarms
 * Analog Out	0..1250 mV output
 *
 * Chassis Intrusion: clear CI latch with 'echo 0 > intrusion0_alarm'
 *
 * Test hardware: Intel SE440BX-2 desktop motherboard --Grant
 *
 * LM81 extended temp पढ़ोing not implemented
 */

#समावेश <linux/bits.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2c, 0x2d, 0x2e, 0x2f,
					I2C_CLIENT_END पूर्ण;

क्रमागत chips अणु adm9240, ds1780, lm81 पूर्ण;

/* ADM9240 रेजिस्टरs */
#घोषणा ADM9240_REG_MAN_ID		0x3e
#घोषणा ADM9240_REG_DIE_REV		0x3f
#घोषणा ADM9240_REG_CONFIG		0x40

#घोषणा ADM9240_REG_IN(nr)		(0x20 + (nr))   /* 0..5 */
#घोषणा ADM9240_REG_IN_MAX(nr)		(0x2b + (nr) * 2)
#घोषणा ADM9240_REG_IN_MIN(nr)		(0x2c + (nr) * 2)
#घोषणा ADM9240_REG_FAN(nr)		(0x28 + (nr))   /* 0..1 */
#घोषणा ADM9240_REG_FAN_MIN(nr)		(0x3b + (nr))
#घोषणा ADM9240_REG_INT(nr)		(0x41 + (nr))
#घोषणा ADM9240_REG_INT_MASK(nr)	(0x43 + (nr))
#घोषणा ADM9240_REG_TEMP		0x27
#घोषणा ADM9240_REG_TEMP_MAX(nr)	(0x39 + (nr)) /* 0, 1 = high, hyst */
#घोषणा ADM9240_REG_ANALOG_OUT		0x19
#घोषणा ADM9240_REG_CHASSIS_CLEAR	0x46
#घोषणा ADM9240_REG_VID_FAN_DIV		0x47
#घोषणा ADM9240_REG_I2C_ADDR		0x48
#घोषणा ADM9240_REG_VID4		0x49
#घोषणा ADM9240_REG_TEMP_CONF		0x4b

/* generalised scaling with पूर्णांकeger rounding */
अटल अंतरभूत पूर्णांक SCALE(दीर्घ val, पूर्णांक mul, पूर्णांक भाग)
अणु
	अगर (val < 0)
		वापस (val * mul - भाग / 2) / भाग;
	अन्यथा
		वापस (val * mul + भाग / 2) / भाग;
पूर्ण

/* adm9240 पूर्णांकernally scales voltage measurements */
अटल स्थिर u16 nom_mv[] = अणु 2500, 2700, 3300, 5000, 12000, 2700 पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक IN_FROM_REG(u8 reg, पूर्णांक n)
अणु
	वापस SCALE(reg, nom_mv[n], 192);
पूर्ण

अटल अंतरभूत u8 IN_TO_REG(अचिन्हित दीर्घ val, पूर्णांक n)
अणु
	val = clamp_val(val, 0, nom_mv[n] * 255 / 192);
	वापस SCALE(val, 192, nom_mv[n]);
पूर्ण

/* temperature range: -40..125, 127 disables temperature alarm */
अटल अंतरभूत s8 TEMP_TO_REG(दीर्घ val)
अणु
	val = clamp_val(val, -40000, 127000);
	वापस SCALE(val, 1, 1000);
पूर्ण

/* two fans, each with low fan speed limit */
अटल अंतरभूत अचिन्हित पूर्णांक FAN_FROM_REG(u8 reg, u8 भाग)
अणु
	अगर (!reg) /* error */
		वापस -1;

	अगर (reg == 255)
		वापस 0;

	वापस SCALE(1350000, 1, reg * भाग);
पूर्ण

/* analog out 0..1250mV */
अटल अंतरभूत u8 AOUT_TO_REG(अचिन्हित दीर्घ val)
अणु
	val = clamp_val(val, 0, 1250);
	वापस SCALE(val, 255, 1250);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक AOUT_FROM_REG(u8 reg)
अणु
	वापस SCALE(reg, 1250, 255);
पूर्ण

/* per client data */
काष्ठा adm9240_data अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा mutex update_lock;

	u8 fan_भाग[2];		/* rw	fan1_भाग, पढ़ो-only accessor */
	u8 vrm;			/* --	vrm set on startup, no accessor */
पूर्ण;

/* ग_लिखो new fan भाग, callers must hold data->update_lock */
अटल पूर्णांक adm9240_ग_लिखो_fan_भाग(काष्ठा adm9240_data *data, पूर्णांक channel, u8 fan_भाग)
अणु
	अचिन्हित पूर्णांक reg, old, shअगरt = (channel + 2) * 2;
	पूर्णांक err;

	err = regmap_पढ़ो(data->regmap, ADM9240_REG_VID_FAN_DIV, &reg);
	अगर (err < 0)
		वापस err;
	old = (reg >> shअगरt) & 3;
	reg &= ~(3 << shअगरt);
	reg |= (fan_भाग << shअगरt);
	err = regmap_ग_लिखो(data->regmap, ADM9240_REG_VID_FAN_DIV, reg);
	अगर (err < 0)
		वापस err;
	dev_dbg(data->dev,
		"fan%d clock divider changed from %lu to %lu\n",
		channel + 1, BIT(old), BIT(fan_भाग));

	वापस 0;
पूर्ण

/*
 * set fan speed low limit:
 *
 * - value is zero: disable fan speed low limit alarm
 *
 * - value is below fan speed measurement range: enable fan speed low
 *   limit alarm to be निश्चितed जबतक fan speed too slow to measure
 *
 * - otherwise: select fan घड़ी भागider to suit fan speed low limit,
 *   measurement code may adjust रेजिस्टरs to ensure fan speed पढ़ोing
 */
अटल पूर्णांक adm9240_fan_min_ग_लिखो(काष्ठा adm9240_data *data, पूर्णांक channel, दीर्घ val)
अणु
	u8 new_भाग;
	u8 fan_min;
	पूर्णांक err;

	mutex_lock(&data->update_lock);

	अगर (!val) अणु
		fan_min = 255;
		new_भाग = data->fan_भाग[channel];

		dev_dbg(data->dev, "fan%u low limit set disabled\n", channel + 1);
	पूर्ण अन्यथा अगर (val < 1350000 / (8 * 254)) अणु
		new_भाग = 3;
		fan_min = 254;

		dev_dbg(data->dev, "fan%u low limit set minimum %u\n",
			channel + 1, FAN_FROM_REG(254, BIT(new_भाग)));
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक new_min = 1350000 / val;

		new_भाग = 0;
		जबतक (new_min > 192 && new_भाग < 3) अणु
			new_भाग++;
			new_min /= 2;
		पूर्ण
		अगर (!new_min) /* keep > 0 */
			new_min++;

		fan_min = new_min;

		dev_dbg(data->dev, "fan%u low limit set fan speed %u\n",
			channel + 1, FAN_FROM_REG(new_min, BIT(new_भाग)));
	पूर्ण

	अगर (new_भाग != data->fan_भाग[channel]) अणु
		data->fan_भाग[channel] = new_भाग;
		adm9240_ग_लिखो_fan_भाग(data, channel, new_भाग);
	पूर्ण
	err = regmap_ग_लिखो(data->regmap, ADM9240_REG_FAN_MIN(channel), fan_min);

	mutex_unlock(&data->update_lock);

	वापस err;
पूर्ण

अटल sमाप_प्रकार cpu0_vid_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adm9240_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक regval;
	पूर्णांक err;
	u8 vid;

	err = regmap_पढ़ो(data->regmap, ADM9240_REG_VID_FAN_DIV, &regval);
	अगर (err < 0)
		वापस err;
	vid = regval & 0x0f;
	err = regmap_पढ़ो(data->regmap, ADM9240_REG_VID4, &regval);
	अगर (err < 0)
		वापस err;
	vid |= (regval & 1) << 4;
	वापस प्र_लिखो(buf, "%d\n", vid_from_reg(vid, data->vrm));
पूर्ण
अटल DEVICE_ATTR_RO(cpu0_vid);

अटल sमाप_प्रकार aout_output_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा adm9240_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक regval;
	पूर्णांक err;

	err = regmap_पढ़ो(data->regmap, ADM9240_REG_ANALOG_OUT, &regval);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%d\n", AOUT_FROM_REG(regval));
पूर्ण

अटल sमाप_प्रकार aout_output_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adm9240_data *data = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(data->regmap, ADM9240_REG_ANALOG_OUT, AOUT_TO_REG(val));
	वापस err < 0 ? err : count;
पूर्ण
अटल DEVICE_ATTR_RW(aout_output);

अटल काष्ठा attribute *adm9240_attrs[] = अणु
	&dev_attr_aout_output.attr,
	&dev_attr_cpu0_vid.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(adm9240);

/*** sensor chip detect and driver install ***/

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक adm9240_detect(काष्ठा i2c_client *new_client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = new_client->adapter;
	स्थिर अक्षर *name = "";
	पूर्णांक address = new_client->addr;
	u8 man_id, die_rev;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/* verअगरy chip: reg address should match i2c address */
	अगर (i2c_smbus_पढ़ो_byte_data(new_client, ADM9240_REG_I2C_ADDR) != address)
		वापस -ENODEV;

	/* check known chip manufacturer */
	man_id = i2c_smbus_पढ़ो_byte_data(new_client, ADM9240_REG_MAN_ID);
	अगर (man_id == 0x23)
		name = "adm9240";
	अन्यथा अगर (man_id == 0xda)
		name = "ds1780";
	अन्यथा अगर (man_id == 0x01)
		name = "lm81";
	अन्यथा
		वापस -ENODEV;

	/* successful detect, prपूर्णांक chip info */
	die_rev = i2c_smbus_पढ़ो_byte_data(new_client, ADM9240_REG_DIE_REV);
	dev_info(&adapter->dev, "found %s revision %u\n",
		 man_id == 0x23 ? "ADM9240" :
		 man_id == 0xda ? "DS1780" : "LM81", die_rev);

	strscpy(info->type, name, I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक adm9240_init_client(काष्ठा adm9240_data *data)
अणु
	अचिन्हित पूर्णांक regval;
	u8 conf, mode;
	पूर्णांक err;

	err = regmap_raw_पढ़ो(data->regmap, ADM9240_REG_CONFIG, &conf, 1);
	अगर (err < 0)
		वापस err;
	err = regmap_raw_पढ़ो(data->regmap, ADM9240_REG_TEMP_CONF, &mode, 1);
	अगर (err < 0)
		वापस err;
	mode &= 3;

	data->vrm = vid_which_vrm(); /* need this to report vid as mV */

	dev_info(data->dev, "Using VRM: %d.%d\n", data->vrm / 10,
		 data->vrm % 10);

	अगर (conf & 1) अणु /* measurement cycle running: report state */

		dev_info(data->dev, "status: config 0x%02x mode %u\n",
			 conf, mode);

	पूर्ण अन्यथा अणु /* cold start: खोलो limits beक्रमe starting chip */
		पूर्णांक i;

		क्रम (i = 0; i < 6; i++) अणु
			err = regmap_ग_लिखो(data->regmap,
					   ADM9240_REG_IN_MIN(i), 0);
			अगर (err < 0)
				वापस err;
			err = regmap_ग_लिखो(data->regmap,
					   ADM9240_REG_IN_MAX(i), 255);
			अगर (err < 0)
				वापस err;
		पूर्ण
		क्रम (i = 0; i < 2; i++) अणु
			err = regmap_ग_लिखो(data->regmap,
					   ADM9240_REG_FAN_MIN(i), 255);
			अगर (err < 0)
				वापस err;
		पूर्ण
		क्रम (i = 0; i < 2; i++) अणु
			err = regmap_ग_लिखो(data->regmap,
					   ADM9240_REG_TEMP_MAX(i), 127);
			अगर (err < 0)
				वापस err;
		पूर्ण

		/* start measurement cycle */
		err = regmap_ग_लिखो(data->regmap, ADM9240_REG_CONFIG, 1);
		अगर (err < 0)
			वापस err;

		dev_info(data->dev,
			 "cold start: config was 0x%02x mode %u\n", conf, mode);
	पूर्ण

	/* पढ़ो fan भागs */
	err = regmap_पढ़ो(data->regmap, ADM9240_REG_VID_FAN_DIV, &regval);
	अगर (err < 0)
		वापस err;
	data->fan_भाग[0] = (regval >> 4) & 3;
	data->fan_भाग[1] = (regval >> 6) & 3;
	वापस 0;
पूर्ण

अटल पूर्णांक adm9240_chip_पढ़ो(काष्ठा device *dev, u32 attr, दीर्घ *val)
अणु
	काष्ठा adm9240_data *data = dev_get_drvdata(dev);
	u8 regs[2];
	पूर्णांक err;

	चयन (attr) अणु
	हाल hwmon_chip_alarms:
		err = regmap_bulk_पढ़ो(data->regmap, ADM9240_REG_INT(0), &regs, 2);
		अगर (err < 0)
			वापस err;
		*val = regs[0] | regs[1] << 8;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adm9240_पूर्णांकrusion_पढ़ो(काष्ठा device *dev, u32 attr, दीर्घ *val)
अणु
	काष्ठा adm9240_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक regval;
	पूर्णांक err;

	चयन (attr) अणु
	हाल hwmon_पूर्णांकrusion_alarm:
		err = regmap_पढ़ो(data->regmap, ADM9240_REG_INT(1), &regval);
		अगर (err < 0)
			वापस err;
		*val = !!(regval & BIT(4));
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adm9240_पूर्णांकrusion_ग_लिखो(काष्ठा device *dev, u32 attr, दीर्घ val)
अणु
	काष्ठा adm9240_data *data = dev_get_drvdata(dev);
	पूर्णांक err;

	चयन (attr) अणु
	हाल hwmon_पूर्णांकrusion_alarm:
		अगर (val)
			वापस -EINVAL;
		err = regmap_ग_लिखो(data->regmap, ADM9240_REG_CHASSIS_CLEAR, 0x80);
		अगर (err < 0)
			वापस err;
		dev_dbg(data->dev, "chassis intrusion latch cleared\n");
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adm9240_in_पढ़ो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा adm9240_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक regval;
	पूर्णांक reg;
	पूर्णांक err;

	चयन (attr) अणु
	हाल hwmon_in_input:
		reg = ADM9240_REG_IN(channel);
		अवरोध;
	हाल hwmon_in_min:
		reg = ADM9240_REG_IN_MIN(channel);
		अवरोध;
	हाल hwmon_in_max:
		reg = ADM9240_REG_IN_MAX(channel);
		अवरोध;
	हाल hwmon_in_alarm:
		अगर (channel < 4) अणु
			reg = ADM9240_REG_INT(0);
		पूर्ण अन्यथा अणु
			reg = ADM9240_REG_INT(1);
			channel -= 4;
		पूर्ण
		err = regmap_पढ़ो(data->regmap, reg, &regval);
		अगर (err < 0)
			वापस err;
		*val = !!(regval & BIT(channel));
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	err = regmap_पढ़ो(data->regmap, reg, &regval);
	अगर (err < 0)
		वापस err;
	*val = IN_FROM_REG(regval, channel);
	वापस 0;
पूर्ण

अटल पूर्णांक adm9240_in_ग_लिखो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा adm9240_data *data = dev_get_drvdata(dev);
	पूर्णांक reg;

	चयन (attr) अणु
	हाल hwmon_in_min:
		reg = ADM9240_REG_IN_MIN(channel);
		अवरोध;
	हाल hwmon_in_max:
		reg = ADM9240_REG_IN_MAX(channel);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस regmap_ग_लिखो(data->regmap, reg, IN_TO_REG(val, channel));
पूर्ण

अटल पूर्णांक adm9240_fan_पढ़ो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा adm9240_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक regval;
	पूर्णांक err;

	चयन (attr) अणु
	हाल hwmon_fan_input:
		err = regmap_पढ़ो(data->regmap, ADM9240_REG_FAN(channel), &regval);
		अगर (err < 0)
			वापस err;
		अगर (regval == 255 && data->fan_भाग[channel] < 3) अणु
			/* adjust fan घड़ी भागider on overflow */
			err = adm9240_ग_लिखो_fan_भाग(data, channel,
						    ++data->fan_भाग[channel]);
			अगर (err)
				वापस err;
		पूर्ण
		*val = FAN_FROM_REG(regval, BIT(data->fan_भाग[channel]));
		अवरोध;
	हाल hwmon_fan_भाग:
		*val = BIT(data->fan_भाग[channel]);
		अवरोध;
	हाल hwmon_fan_min:
		err = regmap_पढ़ो(data->regmap, ADM9240_REG_FAN_MIN(channel), &regval);
		अगर (err < 0)
			वापस err;
		*val = FAN_FROM_REG(regval, BIT(data->fan_भाग[channel]));
		अवरोध;
	हाल hwmon_fan_alarm:
		err = regmap_पढ़ो(data->regmap, ADM9240_REG_INT(0), &regval);
		अगर (err < 0)
			वापस err;
		*val = !!(regval & BIT(channel + 6));
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adm9240_fan_ग_लिखो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा adm9240_data *data = dev_get_drvdata(dev);
	पूर्णांक err;

	चयन (attr) अणु
	हाल hwmon_fan_min:
		err = adm9240_fan_min_ग_लिखो(data, channel, val);
		अगर (err < 0)
			वापस err;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adm9240_temp_पढ़ो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा adm9240_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक regval;
	पूर्णांक err, temp;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		err = regmap_पढ़ो(data->regmap, ADM9240_REG_TEMP, &regval);
		अगर (err < 0)
			वापस err;
		temp = regval << 1;
		err = regmap_पढ़ो(data->regmap, ADM9240_REG_TEMP_CONF, &regval);
		अगर (err < 0)
			वापस err;
		temp |= regval >> 7;
		*val = sign_extend32(temp, 8) * 500;
		अवरोध;
	हाल hwmon_temp_max:
		err = regmap_पढ़ो(data->regmap, ADM9240_REG_TEMP_MAX(0), &regval);
		अगर (err < 0)
			वापस err;
		*val = (s8)regval * 1000;
		अवरोध;
	हाल hwmon_temp_max_hyst:
		err = regmap_पढ़ो(data->regmap, ADM9240_REG_TEMP_MAX(1), &regval);
		अगर (err < 0)
			वापस err;
		*val = (s8)regval * 1000;
		अवरोध;
	हाल hwmon_temp_alarm:
		err = regmap_पढ़ो(data->regmap, ADM9240_REG_INT(0), &regval);
		अगर (err < 0)
			वापस err;
		*val = !!(regval & BIT(4));
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adm9240_temp_ग_लिखो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा adm9240_data *data = dev_get_drvdata(dev);
	पूर्णांक reg;

	चयन (attr) अणु
	हाल hwmon_temp_max:
		reg = ADM9240_REG_TEMP_MAX(0);
		अवरोध;
	हाल hwmon_temp_max_hyst:
		reg = ADM9240_REG_TEMP_MAX(1);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस regmap_ग_लिखो(data->regmap, reg, TEMP_TO_REG(val));
पूर्ण

अटल पूर्णांक adm9240_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type, u32 attr,
			पूर्णांक channel, दीर्घ *val)
अणु
	चयन (type) अणु
	हाल hwmon_chip:
		वापस adm9240_chip_पढ़ो(dev, attr, val);
	हाल hwmon_पूर्णांकrusion:
		वापस adm9240_पूर्णांकrusion_पढ़ो(dev, attr, val);
	हाल hwmon_in:
		वापस adm9240_in_पढ़ो(dev, attr, channel, val);
	हाल hwmon_fan:
		वापस adm9240_fan_पढ़ो(dev, attr, channel, val);
	हाल hwmon_temp:
		वापस adm9240_temp_पढ़ो(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक adm9240_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type, u32 attr,
			 पूर्णांक channel, दीर्घ val)
अणु
	चयन (type) अणु
	हाल hwmon_पूर्णांकrusion:
		वापस adm9240_पूर्णांकrusion_ग_लिखो(dev, attr, val);
	हाल hwmon_in:
		वापस adm9240_in_ग_लिखो(dev, attr, channel, val);
	हाल hwmon_fan:
		वापस adm9240_fan_ग_लिखो(dev, attr, channel, val);
	हाल hwmon_temp:
		वापस adm9240_temp_ग_लिखो(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t adm9240_is_visible(स्थिर व्योम *_data, क्रमागत hwmon_sensor_types type,
				  u32 attr, पूर्णांक channel)
अणु
	umode_t mode = 0;

	चयन (type) अणु
	हाल hwmon_chip:
		चयन (attr) अणु
		हाल hwmon_chip_alarms:
			mode = 0444;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_पूर्णांकrusion:
		चयन (attr) अणु
		हाल hwmon_पूर्णांकrusion_alarm:
			mode = 0644;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp:
		हाल hwmon_temp_alarm:
			mode = 0444;
			अवरोध;
		हाल hwmon_temp_max:
		हाल hwmon_temp_max_hyst:
			mode = 0644;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_fan:
		चयन (attr) अणु
		हाल hwmon_fan_input:
		हाल hwmon_fan_भाग:
		हाल hwmon_fan_alarm:
			mode = 0444;
			अवरोध;
		हाल hwmon_fan_min:
			mode = 0644;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_input:
		हाल hwmon_in_alarm:
			mode = 0444;
			अवरोध;
		हाल hwmon_in_min:
		हाल hwmon_in_max:
			mode = 0644;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस mode;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops adm9240_hwmon_ops = अणु
	.is_visible = adm9240_is_visible,
	.पढ़ो = adm9240_पढ़ो,
	.ग_लिखो = adm9240_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *adm9240_info[] = अणु
	HWMON_CHANNEL_INFO(chip, HWMON_C_ALARMS),
	HWMON_CHANNEL_INFO(पूर्णांकrusion, HWMON_INTRUSION_ALARM),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST | HWMON_T_ALARM),
	HWMON_CHANNEL_INFO(in,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX | HWMON_I_ALARM),
	HWMON_CHANNEL_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_DIV | HWMON_F_ALARM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_DIV | HWMON_F_ALARM),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info adm9240_chip_info = अणु
	.ops = &adm9240_hwmon_ops,
	.info = adm9240_info,
पूर्ण;

अटल bool adm9240_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ADM9240_REG_IN(0) ... ADM9240_REG_IN(5):
	हाल ADM9240_REG_FAN(0) ... ADM9240_REG_FAN(1):
	हाल ADM9240_REG_INT(0) ... ADM9240_REG_INT(1):
	हाल ADM9240_REG_TEMP:
	हाल ADM9240_REG_TEMP_CONF:
	हाल ADM9240_REG_VID_FAN_DIV:
	हाल ADM9240_REG_VID4:
	हाल ADM9240_REG_ANALOG_OUT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config adm9240_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
	.अस्थिर_reg = adm9240_अस्थिर_reg,
पूर्ण;

अटल पूर्णांक adm9240_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा adm9240_data *data;
	पूर्णांक err;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->dev = dev;
	mutex_init(&data->update_lock);
	data->regmap = devm_regmap_init_i2c(client, &adm9240_regmap_config);
	अगर (IS_ERR(data->regmap))
		वापस PTR_ERR(data->regmap);

	err = adm9240_init_client(data);
	अगर (err < 0)
		वापस err;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, client->name, data,
							 &adm9240_chip_info,
							 adm9240_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adm9240_id[] = अणु
	अणु "adm9240", adm9240 पूर्ण,
	अणु "ds1780", ds1780 पूर्ण,
	अणु "lm81", lm81 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adm9240_id);

अटल काष्ठा i2c_driver adm9240_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "adm9240",
	पूर्ण,
	.probe_new	= adm9240_probe,
	.id_table	= adm9240_id,
	.detect		= adm9240_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(adm9240_driver);

MODULE_AUTHOR("Michiel Rook <michiel@grendelproject.nl>, "
		"Grant Coady <gcoady.lk@gmail.com> and others");
MODULE_DESCRIPTION("ADM9240/DS1780/LM81 driver");
MODULE_LICENSE("GPL");
