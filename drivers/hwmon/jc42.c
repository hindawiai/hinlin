<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * jc42.c - driver क्रम Jedec JC42.4 compliant temperature sensors
 *
 * Copyright (c) 2010  Ericsson AB.
 *
 * Derived from lm77.c by Andras BALI <drewie@मुक्तmail.hu>.
 *
 * JC42.4 compliant temperature sensors are typically used on memory modules.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु
	0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, I2C_CLIENT_END पूर्ण;

/* JC42 रेजिस्टरs. All रेजिस्टरs are 16 bit. */
#घोषणा JC42_REG_CAP		0x00
#घोषणा JC42_REG_CONFIG		0x01
#घोषणा JC42_REG_TEMP_UPPER	0x02
#घोषणा JC42_REG_TEMP_LOWER	0x03
#घोषणा JC42_REG_TEMP_CRITICAL	0x04
#घोषणा JC42_REG_TEMP		0x05
#घोषणा JC42_REG_MANID		0x06
#घोषणा JC42_REG_DEVICEID	0x07
#घोषणा JC42_REG_SMBUS		0x22 /* NXP and Aपंचांगel, possibly others? */

/* Status bits in temperature रेजिस्टर */
#घोषणा JC42_ALARM_CRIT_BIT	15
#घोषणा JC42_ALARM_MAX_BIT	14
#घोषणा JC42_ALARM_MIN_BIT	13

/* Configuration रेजिस्टर defines */
#घोषणा JC42_CFG_CRIT_ONLY	(1 << 2)
#घोषणा JC42_CFG_TCRIT_LOCK	(1 << 6)
#घोषणा JC42_CFG_EVENT_LOCK	(1 << 7)
#घोषणा JC42_CFG_SHUTDOWN	(1 << 8)
#घोषणा JC42_CFG_HYST_SHIFT	9
#घोषणा JC42_CFG_HYST_MASK	(0x03 << 9)

/* Capabilities */
#घोषणा JC42_CAP_RANGE		(1 << 2)

/* Manufacturer IDs */
#घोषणा ADT_MANID		0x11d4  /* Analog Devices */
#घोषणा ATMEL_MANID		0x001f  /* Aपंचांगel */
#घोषणा ATMEL_MANID2		0x1114	/* Aपंचांगel */
#घोषणा MAX_MANID		0x004d  /* Maxim */
#घोषणा IDT_MANID		0x00b3  /* IDT */
#घोषणा MCP_MANID		0x0054  /* Microchip */
#घोषणा NXP_MANID		0x1131  /* NXP Semiconductors */
#घोषणा ONS_MANID		0x1b09  /* ON Semiconductor */
#घोषणा STM_MANID		0x104a  /* ST Microelectronics */
#घोषणा GT_MANID		0x1c68	/* Giantec */
#घोषणा GT_MANID2		0x132d	/* Giantec, 2nd mfg ID */

/* SMBUS रेजिस्टर */
#घोषणा SMBUS_STMOUT		BIT(7)  /* SMBus समय-out, active low */

/* Supported chips */

/* Analog Devices */
#घोषणा ADT7408_DEVID		0x0801
#घोषणा ADT7408_DEVID_MASK	0xffff

/* Aपंचांगel */
#घोषणा AT30TS00_DEVID		0x8201
#घोषणा AT30TS00_DEVID_MASK	0xffff

#घोषणा AT30TSE004_DEVID	0x2200
#घोषणा AT30TSE004_DEVID_MASK	0xffff

/* Giantec */
#घोषणा GT30TS00_DEVID		0x2200
#घोषणा GT30TS00_DEVID_MASK	0xff00

#घोषणा GT34TS02_DEVID		0x3300
#घोषणा GT34TS02_DEVID_MASK	0xff00

/* IDT */
#घोषणा TSE2004_DEVID		0x2200
#घोषणा TSE2004_DEVID_MASK	0xff00

#घोषणा TS3000_DEVID		0x2900  /* Also matches TSE2002 */
#घोषणा TS3000_DEVID_MASK	0xff00

#घोषणा TS3001_DEVID		0x3000
#घोषणा TS3001_DEVID_MASK	0xff00

/* Maxim */
#घोषणा MAX6604_DEVID		0x3e00
#घोषणा MAX6604_DEVID_MASK	0xffff

/* Microchip */
#घोषणा MCP9804_DEVID		0x0200
#घोषणा MCP9804_DEVID_MASK	0xfffc

#घोषणा MCP9808_DEVID		0x0400
#घोषणा MCP9808_DEVID_MASK	0xfffc

#घोषणा MCP98242_DEVID		0x2000
#घोषणा MCP98242_DEVID_MASK	0xfffc

#घोषणा MCP98243_DEVID		0x2100
#घोषणा MCP98243_DEVID_MASK	0xfffc

#घोषणा MCP98244_DEVID		0x2200
#घोषणा MCP98244_DEVID_MASK	0xfffc

#घोषणा MCP9843_DEVID		0x0000	/* Also matches mcp9805 */
#घोषणा MCP9843_DEVID_MASK	0xfffe

/* NXP */
#घोषणा SE97_DEVID		0xa200
#घोषणा SE97_DEVID_MASK		0xfffc

#घोषणा SE98_DEVID		0xa100
#घोषणा SE98_DEVID_MASK		0xfffc

/* ON Semiconductor */
#घोषणा CAT6095_DEVID		0x0800	/* Also matches CAT34TS02 */
#घोषणा CAT6095_DEVID_MASK	0xffe0

#घोषणा CAT34TS02C_DEVID	0x0a00
#घोषणा CAT34TS02C_DEVID_MASK	0xfff0

#घोषणा CAT34TS04_DEVID		0x2200
#घोषणा CAT34TS04_DEVID_MASK	0xfff0

/* ST Microelectronics */
#घोषणा STTS424_DEVID		0x0101
#घोषणा STTS424_DEVID_MASK	0xffff

#घोषणा STTS424E_DEVID		0x0000
#घोषणा STTS424E_DEVID_MASK	0xfffe

#घोषणा STTS2002_DEVID		0x0300
#घोषणा STTS2002_DEVID_MASK	0xffff

#घोषणा STTS2004_DEVID		0x2201
#घोषणा STTS2004_DEVID_MASK	0xffff

#घोषणा STTS3000_DEVID		0x0200
#घोषणा STTS3000_DEVID_MASK	0xffff

अटल u16 jc42_hysteresis[] = अणु 0, 1500, 3000, 6000 पूर्ण;

काष्ठा jc42_chips अणु
	u16 manid;
	u16 devid;
	u16 devid_mask;
पूर्ण;

अटल काष्ठा jc42_chips jc42_chips[] = अणु
	अणु ADT_MANID, ADT7408_DEVID, ADT7408_DEVID_MASK पूर्ण,
	अणु ATMEL_MANID, AT30TS00_DEVID, AT30TS00_DEVID_MASK पूर्ण,
	अणु ATMEL_MANID2, AT30TSE004_DEVID, AT30TSE004_DEVID_MASK पूर्ण,
	अणु GT_MANID, GT30TS00_DEVID, GT30TS00_DEVID_MASK पूर्ण,
	अणु GT_MANID2, GT34TS02_DEVID, GT34TS02_DEVID_MASK पूर्ण,
	अणु IDT_MANID, TSE2004_DEVID, TSE2004_DEVID_MASK पूर्ण,
	अणु IDT_MANID, TS3000_DEVID, TS3000_DEVID_MASK पूर्ण,
	अणु IDT_MANID, TS3001_DEVID, TS3001_DEVID_MASK पूर्ण,
	अणु MAX_MANID, MAX6604_DEVID, MAX6604_DEVID_MASK पूर्ण,
	अणु MCP_MANID, MCP9804_DEVID, MCP9804_DEVID_MASK पूर्ण,
	अणु MCP_MANID, MCP9808_DEVID, MCP9808_DEVID_MASK पूर्ण,
	अणु MCP_MANID, MCP98242_DEVID, MCP98242_DEVID_MASK पूर्ण,
	अणु MCP_MANID, MCP98243_DEVID, MCP98243_DEVID_MASK पूर्ण,
	अणु MCP_MANID, MCP98244_DEVID, MCP98244_DEVID_MASK पूर्ण,
	अणु MCP_MANID, MCP9843_DEVID, MCP9843_DEVID_MASK पूर्ण,
	अणु NXP_MANID, SE97_DEVID, SE97_DEVID_MASK पूर्ण,
	अणु ONS_MANID, CAT6095_DEVID, CAT6095_DEVID_MASK पूर्ण,
	अणु ONS_MANID, CAT34TS02C_DEVID, CAT34TS02C_DEVID_MASK पूर्ण,
	अणु ONS_MANID, CAT34TS04_DEVID, CAT34TS04_DEVID_MASK पूर्ण,
	अणु NXP_MANID, SE98_DEVID, SE98_DEVID_MASK पूर्ण,
	अणु STM_MANID, STTS424_DEVID, STTS424_DEVID_MASK पूर्ण,
	अणु STM_MANID, STTS424E_DEVID, STTS424E_DEVID_MASK पूर्ण,
	अणु STM_MANID, STTS2002_DEVID, STTS2002_DEVID_MASK पूर्ण,
	अणु STM_MANID, STTS2004_DEVID, STTS2004_DEVID_MASK पूर्ण,
	अणु STM_MANID, STTS3000_DEVID, STTS3000_DEVID_MASK पूर्ण,
पूर्ण;

क्रमागत temp_index अणु
	t_input = 0,
	t_crit,
	t_min,
	t_max,
	t_num_temp
पूर्ण;

अटल स्थिर u8 temp_regs[t_num_temp] = अणु
	[t_input] = JC42_REG_TEMP,
	[t_crit] = JC42_REG_TEMP_CRITICAL,
	[t_min] = JC42_REG_TEMP_LOWER,
	[t_max] = JC42_REG_TEMP_UPPER,
पूर्ण;

/* Each client has this additional data */
काष्ठा jc42_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex	update_lock;	/* protect रेजिस्टर access */
	bool		extended;	/* true अगर extended range supported */
	bool		valid;
	अचिन्हित दीर्घ	last_updated;	/* In jअगरfies */
	u16		orig_config;	/* original configuration */
	u16		config;		/* current configuration */
	u16		temp[t_num_temp];/* Temperatures */
पूर्ण;

#घोषणा JC42_TEMP_MIN_EXTENDED	(-40000)
#घोषणा JC42_TEMP_MIN		0
#घोषणा JC42_TEMP_MAX		125000

अटल u16 jc42_temp_to_reg(दीर्घ temp, bool extended)
अणु
	पूर्णांक ntemp = clamp_val(temp,
			      extended ? JC42_TEMP_MIN_EXTENDED :
			      JC42_TEMP_MIN, JC42_TEMP_MAX);

	/* convert from 0.001 to 0.0625 resolution */
	वापस (ntemp * 2 / 125) & 0x1fff;
पूर्ण

अटल पूर्णांक jc42_temp_from_reg(s16 reg)
अणु
	reg = sign_extend32(reg, 12);

	/* convert from 0.0625 to 0.001 resolution */
	वापस reg * 125 / 2;
पूर्ण

अटल काष्ठा jc42_data *jc42_update_device(काष्ठा device *dev)
अणु
	काष्ठा jc42_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	काष्ठा jc42_data *ret = data;
	पूर्णांक i, val;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ) || !data->valid) अणु
		क्रम (i = 0; i < t_num_temp; i++) अणु
			val = i2c_smbus_पढ़ो_word_swapped(client, temp_regs[i]);
			अगर (val < 0) अणु
				ret = ERR_PTR(val);
				जाओ पात;
			पूर्ण
			data->temp[i] = val;
		पूर्ण
		data->last_updated = jअगरfies;
		data->valid = true;
	पूर्ण
पात:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक jc42_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		     u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा jc42_data *data = jc42_update_device(dev);
	पूर्णांक temp, hyst;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	चयन (attr) अणु
	हाल hwmon_temp_input:
		*val = jc42_temp_from_reg(data->temp[t_input]);
		वापस 0;
	हाल hwmon_temp_min:
		*val = jc42_temp_from_reg(data->temp[t_min]);
		वापस 0;
	हाल hwmon_temp_max:
		*val = jc42_temp_from_reg(data->temp[t_max]);
		वापस 0;
	हाल hwmon_temp_crit:
		*val = jc42_temp_from_reg(data->temp[t_crit]);
		वापस 0;
	हाल hwmon_temp_max_hyst:
		temp = jc42_temp_from_reg(data->temp[t_max]);
		hyst = jc42_hysteresis[(data->config & JC42_CFG_HYST_MASK)
						>> JC42_CFG_HYST_SHIFT];
		*val = temp - hyst;
		वापस 0;
	हाल hwmon_temp_crit_hyst:
		temp = jc42_temp_from_reg(data->temp[t_crit]);
		hyst = jc42_hysteresis[(data->config & JC42_CFG_HYST_MASK)
						>> JC42_CFG_HYST_SHIFT];
		*val = temp - hyst;
		वापस 0;
	हाल hwmon_temp_min_alarm:
		*val = (data->temp[t_input] >> JC42_ALARM_MIN_BIT) & 1;
		वापस 0;
	हाल hwmon_temp_max_alarm:
		*val = (data->temp[t_input] >> JC42_ALARM_MAX_BIT) & 1;
		वापस 0;
	हाल hwmon_temp_crit_alarm:
		*val = (data->temp[t_input] >> JC42_ALARM_CRIT_BIT) & 1;
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक jc42_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		      u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा jc42_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक dअगरf, hyst;
	पूर्णांक ret;

	mutex_lock(&data->update_lock);

	चयन (attr) अणु
	हाल hwmon_temp_min:
		data->temp[t_min] = jc42_temp_to_reg(val, data->extended);
		ret = i2c_smbus_ग_लिखो_word_swapped(client, temp_regs[t_min],
						   data->temp[t_min]);
		अवरोध;
	हाल hwmon_temp_max:
		data->temp[t_max] = jc42_temp_to_reg(val, data->extended);
		ret = i2c_smbus_ग_लिखो_word_swapped(client, temp_regs[t_max],
						   data->temp[t_max]);
		अवरोध;
	हाल hwmon_temp_crit:
		data->temp[t_crit] = jc42_temp_to_reg(val, data->extended);
		ret = i2c_smbus_ग_लिखो_word_swapped(client, temp_regs[t_crit],
						   data->temp[t_crit]);
		अवरोध;
	हाल hwmon_temp_crit_hyst:
		/*
		 * JC42.4 compliant chips only support four hysteresis values.
		 * Pick best choice and go from there.
		 */
		val = clamp_val(val, (data->extended ? JC42_TEMP_MIN_EXTENDED
						     : JC42_TEMP_MIN) - 6000,
				JC42_TEMP_MAX);
		dअगरf = jc42_temp_from_reg(data->temp[t_crit]) - val;
		hyst = 0;
		अगर (dअगरf > 0) अणु
			अगर (dअगरf < 2250)
				hyst = 1;	/* 1.5 degrees C */
			अन्यथा अगर (dअगरf < 4500)
				hyst = 2;	/* 3.0 degrees C */
			अन्यथा
				hyst = 3;	/* 6.0 degrees C */
		पूर्ण
		data->config = (data->config & ~JC42_CFG_HYST_MASK) |
				(hyst << JC42_CFG_HYST_SHIFT);
		ret = i2c_smbus_ग_लिखो_word_swapped(data->client,
						   JC42_REG_CONFIG,
						   data->config);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

अटल umode_t jc42_is_visible(स्थिर व्योम *_data, क्रमागत hwmon_sensor_types type,
			       u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा jc42_data *data = _data;
	अचिन्हित पूर्णांक config = data->config;
	umode_t mode = 0444;

	चयन (attr) अणु
	हाल hwmon_temp_min:
	हाल hwmon_temp_max:
		अगर (!(config & JC42_CFG_EVENT_LOCK))
			mode |= 0200;
		अवरोध;
	हाल hwmon_temp_crit:
		अगर (!(config & JC42_CFG_TCRIT_LOCK))
			mode |= 0200;
		अवरोध;
	हाल hwmon_temp_crit_hyst:
		अगर (!(config & (JC42_CFG_EVENT_LOCK | JC42_CFG_TCRIT_LOCK)))
			mode |= 0200;
		अवरोध;
	हाल hwmon_temp_input:
	हाल hwmon_temp_max_hyst:
	हाल hwmon_temp_min_alarm:
	हाल hwmon_temp_max_alarm:
	हाल hwmon_temp_crit_alarm:
		अवरोध;
	शेष:
		mode = 0;
		अवरोध;
	पूर्ण
	वापस mode;
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक jc42_detect(काष्ठा i2c_client *client, काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक i, config, cap, manid, devid;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	cap = i2c_smbus_पढ़ो_word_swapped(client, JC42_REG_CAP);
	config = i2c_smbus_पढ़ो_word_swapped(client, JC42_REG_CONFIG);
	manid = i2c_smbus_पढ़ो_word_swapped(client, JC42_REG_MANID);
	devid = i2c_smbus_पढ़ो_word_swapped(client, JC42_REG_DEVICEID);

	अगर (cap < 0 || config < 0 || manid < 0 || devid < 0)
		वापस -ENODEV;

	अगर ((cap & 0xff00) || (config & 0xf800))
		वापस -ENODEV;

	क्रम (i = 0; i < ARRAY_SIZE(jc42_chips); i++) अणु
		काष्ठा jc42_chips *chip = &jc42_chips[i];
		अगर (manid == chip->manid &&
		    (devid & chip->devid_mask) == chip->devid) अणु
			strlcpy(info->type, "jc42", I2C_NAME_SIZE);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *jc42_info[] = अणु
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MAX |
			   HWMON_T_CRIT | HWMON_T_MAX_HYST |
			   HWMON_T_CRIT_HYST | HWMON_T_MIN_ALARM |
			   HWMON_T_MAX_ALARM | HWMON_T_CRIT_ALARM),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops jc42_hwmon_ops = अणु
	.is_visible = jc42_is_visible,
	.पढ़ो = jc42_पढ़ो,
	.ग_लिखो = jc42_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info jc42_chip_info = अणु
	.ops = &jc42_hwmon_ops,
	.info = jc42_info,
पूर्ण;

अटल पूर्णांक jc42_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा jc42_data *data;
	पूर्णांक config, cap;

	data = devm_kzalloc(dev, माप(काष्ठा jc42_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	cap = i2c_smbus_पढ़ो_word_swapped(client, JC42_REG_CAP);
	अगर (cap < 0)
		वापस cap;

	data->extended = !!(cap & JC42_CAP_RANGE);

	अगर (device_property_पढ़ो_bool(dev, "smbus-timeout-disable")) अणु
		पूर्णांक smbus;

		/*
		 * Not all chips support this रेजिस्टर, but from a
		 * quick पढ़ो of various datasheets no chip appears
		 * incompatible with the below attempt to disable
		 * the समयout. And the whole thing is opt-in...
		 */
		smbus = i2c_smbus_पढ़ो_word_swapped(client, JC42_REG_SMBUS);
		अगर (smbus < 0)
			वापस smbus;
		i2c_smbus_ग_लिखो_word_swapped(client, JC42_REG_SMBUS,
					     smbus | SMBUS_STMOUT);
	पूर्ण

	config = i2c_smbus_पढ़ो_word_swapped(client, JC42_REG_CONFIG);
	अगर (config < 0)
		वापस config;

	data->orig_config = config;
	अगर (config & JC42_CFG_SHUTDOWN) अणु
		config &= ~JC42_CFG_SHUTDOWN;
		i2c_smbus_ग_लिखो_word_swapped(client, JC42_REG_CONFIG, config);
	पूर्ण
	data->config = config;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, "jc42",
							 data, &jc42_chip_info,
							 शून्य);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल पूर्णांक jc42_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा jc42_data *data = i2c_get_clientdata(client);

	/* Restore original configuration except hysteresis */
	अगर ((data->config & ~JC42_CFG_HYST_MASK) !=
	    (data->orig_config & ~JC42_CFG_HYST_MASK)) अणु
		पूर्णांक config;

		config = (data->orig_config & ~JC42_CFG_HYST_MASK)
		  | (data->config & JC42_CFG_HYST_MASK);
		i2c_smbus_ग_लिखो_word_swapped(client, JC42_REG_CONFIG, config);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक jc42_suspend(काष्ठा device *dev)
अणु
	काष्ठा jc42_data *data = dev_get_drvdata(dev);

	data->config |= JC42_CFG_SHUTDOWN;
	i2c_smbus_ग_लिखो_word_swapped(data->client, JC42_REG_CONFIG,
				     data->config);
	वापस 0;
पूर्ण

अटल पूर्णांक jc42_resume(काष्ठा device *dev)
अणु
	काष्ठा jc42_data *data = dev_get_drvdata(dev);

	data->config &= ~JC42_CFG_SHUTDOWN;
	i2c_smbus_ग_लिखो_word_swapped(data->client, JC42_REG_CONFIG,
				     data->config);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops jc42_dev_pm_ops = अणु
	.suspend = jc42_suspend,
	.resume = jc42_resume,
पूर्ण;

#घोषणा JC42_DEV_PM_OPS (&jc42_dev_pm_ops)
#अन्यथा
#घोषणा JC42_DEV_PM_OPS शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा i2c_device_id jc42_id[] = अणु
	अणु "jc42", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, jc42_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id jc42_of_ids[] = अणु
	अणु .compatible = "jedec,jc-42.4-temp", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, jc42_of_ids);
#पूर्ण_अगर

अटल काष्ठा i2c_driver jc42_driver = अणु
	.class		= I2C_CLASS_SPD | I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "jc42",
		.pm = JC42_DEV_PM_OPS,
		.of_match_table = of_match_ptr(jc42_of_ids),
	पूर्ण,
	.probe_new	= jc42_probe,
	.हटाओ		= jc42_हटाओ,
	.id_table	= jc42_id,
	.detect		= jc42_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(jc42_driver);

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("JC42 driver");
MODULE_LICENSE("GPL");
