<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2008, 2010 Davide Rizzo <elpa.rizzo@gmail.com>
 *
 * The LM95241 is a sensor chip made by National Semiconductors.
 * It reports up to three temperatures (its own plus up to two बाह्यal ones).
 * Complete datasheet can be obtained from National's website at:
 *   http://www.national.com/ds.cgi/LM/LM95241.pdf
 */

#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

#घोषणा DEVNAME "lm95241"

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु
	0x19, 0x2a, 0x2b, I2C_CLIENT_END पूर्ण;

/* LM95241 रेजिस्टरs */
#घोषणा LM95241_REG_R_MAN_ID		0xFE
#घोषणा LM95241_REG_R_CHIP_ID		0xFF
#घोषणा LM95241_REG_R_STATUS		0x02
#घोषणा LM95241_REG_RW_CONFIG		0x03
#घोषणा LM95241_REG_RW_REM_FILTER	0x06
#घोषणा LM95241_REG_RW_TRUTHERM		0x07
#घोषणा LM95241_REG_W_ONE_SHOT		0x0F
#घोषणा LM95241_REG_R_LOCAL_TEMPH	0x10
#घोषणा LM95241_REG_R_REMOTE1_TEMPH	0x11
#घोषणा LM95241_REG_R_REMOTE2_TEMPH	0x12
#घोषणा LM95241_REG_R_LOCAL_TEMPL	0x20
#घोषणा LM95241_REG_R_REMOTE1_TEMPL	0x21
#घोषणा LM95241_REG_R_REMOTE2_TEMPL	0x22
#घोषणा LM95241_REG_RW_REMOTE_MODEL	0x30

/* LM95241 specअगरic bitfields */
#घोषणा CFG_STOP	BIT(6)
#घोषणा CFG_CR0076	0x00
#घोषणा CFG_CR0182	BIT(4)
#घोषणा CFG_CR1000	BIT(5)
#घोषणा CFG_CR2700	(BIT(4) | BIT(5))
#घोषणा CFG_CRMASK	(BIT(4) | BIT(5))
#घोषणा R1MS_MASK	BIT(0)
#घोषणा R2MS_MASK	BIT(2)
#घोषणा R1DF_MASK	BIT(1)
#घोषणा R2DF_MASK	BIT(2)
#घोषणा R1FE_MASK	BIT(0)
#घोषणा R2FE_MASK	BIT(2)
#घोषणा R1DM		BIT(0)
#घोषणा R2DM		BIT(1)
#घोषणा TT1_SHIFT	0
#घोषणा TT2_SHIFT	4
#घोषणा TT_OFF		0
#घोषणा TT_ON		1
#घोषणा TT_MASK		7
#घोषणा NATSEMI_MAN_ID	0x01
#घोषणा LM95231_CHIP_ID	0xA1
#घोषणा LM95241_CHIP_ID	0xA4

अटल स्थिर u8 lm95241_reg_address[] = अणु
	LM95241_REG_R_LOCAL_TEMPH,
	LM95241_REG_R_LOCAL_TEMPL,
	LM95241_REG_R_REMOTE1_TEMPH,
	LM95241_REG_R_REMOTE1_TEMPL,
	LM95241_REG_R_REMOTE2_TEMPH,
	LM95241_REG_R_REMOTE2_TEMPL
पूर्ण;

/* Client data (each client माला_लो its own) */
काष्ठा lm95241_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	अचिन्हित दीर्घ last_updated;	/* in jअगरfies */
	अचिन्हित दीर्घ पूर्णांकerval;		/* in milli-seconds */
	अक्षर valid;		/* zero until following fields are valid */
	/* रेजिस्टरs values */
	u8 temp[ARRAY_SIZE(lm95241_reg_address)];
	u8 status, config, model, trutherm;
पूर्ण;

/* Conversions */
अटल पूर्णांक temp_from_reg_चिन्हित(u8 val_h, u8 val_l)
अणु
	s16 val_hl = (val_h << 8) | val_l;
	वापस val_hl * 1000 / 256;
पूर्ण

अटल पूर्णांक temp_from_reg_अचिन्हित(u8 val_h, u8 val_l)
अणु
	u16 val_hl = (val_h << 8) | val_l;
	वापस val_hl * 1000 / 256;
पूर्ण

अटल काष्ठा lm95241_data *lm95241_update_device(काष्ठा device *dev)
अणु
	काष्ठा lm95241_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated
		       + msecs_to_jअगरfies(data->पूर्णांकerval)) ||
	    !data->valid) अणु
		पूर्णांक i;

		dev_dbg(dev, "Updating lm95241 data.\n");
		क्रम (i = 0; i < ARRAY_SIZE(lm95241_reg_address); i++)
			data->temp[i]
			  = i2c_smbus_पढ़ो_byte_data(client,
						     lm95241_reg_address[i]);

		data->status = i2c_smbus_पढ़ो_byte_data(client,
							LM95241_REG_R_STATUS);
		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

अटल पूर्णांक lm95241_पढ़ो_chip(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			     दीर्घ *val)
अणु
	काष्ठा lm95241_data *data = dev_get_drvdata(dev);

	चयन (attr) अणु
	हाल hwmon_chip_update_पूर्णांकerval:
		*val = data->पूर्णांकerval;
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक lm95241_पढ़ो_temp(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			     दीर्घ *val)
अणु
	काष्ठा lm95241_data *data = lm95241_update_device(dev);

	चयन (attr) अणु
	हाल hwmon_temp_input:
		अगर (!channel || (data->config & BIT(channel - 1)))
			*val = temp_from_reg_चिन्हित(data->temp[channel * 2],
						data->temp[channel * 2 + 1]);
		अन्यथा
			*val = temp_from_reg_अचिन्हित(data->temp[channel * 2],
						data->temp[channel * 2 + 1]);
		वापस 0;
	हाल hwmon_temp_min:
		अगर (channel == 1)
			*val = (data->config & R1DF_MASK) ? -128000 : 0;
		अन्यथा
			*val = (data->config & R2DF_MASK) ? -128000 : 0;
		वापस 0;
	हाल hwmon_temp_max:
		अगर (channel == 1)
			*val = (data->config & R1DF_MASK) ? 127875 : 255875;
		अन्यथा
			*val = (data->config & R2DF_MASK) ? 127875 : 255875;
		वापस 0;
	हाल hwmon_temp_type:
		अगर (channel == 1)
			*val = (data->model & R1MS_MASK) ? 1 : 2;
		अन्यथा
			*val = (data->model & R2MS_MASK) ? 1 : 2;
		वापस 0;
	हाल hwmon_temp_fault:
		अगर (channel == 1)
			*val = !!(data->status & R1DM);
		अन्यथा
			*val = !!(data->status & R2DM);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक lm95241_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	चयन (type) अणु
	हाल hwmon_chip:
		वापस lm95241_पढ़ो_chip(dev, attr, channel, val);
	हाल hwmon_temp:
		वापस lm95241_पढ़ो_temp(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक lm95241_ग_लिखो_chip(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			      दीर्घ val)
अणु
	काष्ठा lm95241_data *data = dev_get_drvdata(dev);
	पूर्णांक convrate;
	u8 config;
	पूर्णांक ret;

	mutex_lock(&data->update_lock);

	चयन (attr) अणु
	हाल hwmon_chip_update_पूर्णांकerval:
		config = data->config & ~CFG_CRMASK;
		अगर (val < 130) अणु
			convrate = 76;
			config |= CFG_CR0076;
		पूर्ण अन्यथा अगर (val < 590) अणु
			convrate = 182;
			config |= CFG_CR0182;
		पूर्ण अन्यथा अगर (val < 1850) अणु
			convrate = 1000;
			config |= CFG_CR1000;
		पूर्ण अन्यथा अणु
			convrate = 2700;
			config |= CFG_CR2700;
		पूर्ण
		data->पूर्णांकerval = convrate;
		data->config = config;
		ret = i2c_smbus_ग_लिखो_byte_data(data->client,
						LM95241_REG_RW_CONFIG, config);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक lm95241_ग_लिखो_temp(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			      दीर्घ val)
अणु
	काष्ठा lm95241_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;

	mutex_lock(&data->update_lock);

	चयन (attr) अणु
	हाल hwmon_temp_min:
		अगर (channel == 1) अणु
			अगर (val < 0)
				data->config |= R1DF_MASK;
			अन्यथा
				data->config &= ~R1DF_MASK;
		पूर्ण अन्यथा अणु
			अगर (val < 0)
				data->config |= R2DF_MASK;
			अन्यथा
				data->config &= ~R2DF_MASK;
		पूर्ण
		data->valid = 0;
		ret = i2c_smbus_ग_लिखो_byte_data(client, LM95241_REG_RW_CONFIG,
						data->config);
		अवरोध;
	हाल hwmon_temp_max:
		अगर (channel == 1) अणु
			अगर (val <= 127875)
				data->config |= R1DF_MASK;
			अन्यथा
				data->config &= ~R1DF_MASK;
		पूर्ण अन्यथा अणु
			अगर (val <= 127875)
				data->config |= R2DF_MASK;
			अन्यथा
				data->config &= ~R2DF_MASK;
		पूर्ण
		data->valid = 0;
		ret = i2c_smbus_ग_लिखो_byte_data(client, LM95241_REG_RW_CONFIG,
						data->config);
		अवरोध;
	हाल hwmon_temp_type:
		अगर (val != 1 && val != 2) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (channel == 1) अणु
			data->trutherm &= ~(TT_MASK << TT1_SHIFT);
			अगर (val == 1) अणु
				data->model |= R1MS_MASK;
				data->trutherm |= (TT_ON << TT1_SHIFT);
			पूर्ण अन्यथा अणु
				data->model &= ~R1MS_MASK;
				data->trutherm |= (TT_OFF << TT1_SHIFT);
			पूर्ण
		पूर्ण अन्यथा अणु
			data->trutherm &= ~(TT_MASK << TT2_SHIFT);
			अगर (val == 1) अणु
				data->model |= R2MS_MASK;
				data->trutherm |= (TT_ON << TT2_SHIFT);
			पूर्ण अन्यथा अणु
				data->model &= ~R2MS_MASK;
				data->trutherm |= (TT_OFF << TT2_SHIFT);
			पूर्ण
		पूर्ण
		ret = i2c_smbus_ग_लिखो_byte_data(client,
						LM95241_REG_RW_REMOTE_MODEL,
						data->model);
		अगर (ret < 0)
			अवरोध;
		ret = i2c_smbus_ग_लिखो_byte_data(client, LM95241_REG_RW_TRUTHERM,
						data->trutherm);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक lm95241_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			 u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	चयन (type) अणु
	हाल hwmon_chip:
		वापस lm95241_ग_लिखो_chip(dev, attr, channel, val);
	हाल hwmon_temp:
		वापस lm95241_ग_लिखो_temp(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t lm95241_is_visible(स्थिर व्योम *data,
				  क्रमागत hwmon_sensor_types type,
				  u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_chip:
		चयन (attr) अणु
		हाल hwmon_chip_update_पूर्णांकerval:
			वापस 0644;
		पूर्ण
		अवरोध;
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
			वापस 0444;
		हाल hwmon_temp_fault:
			वापस 0444;
		हाल hwmon_temp_min:
		हाल hwmon_temp_max:
		हाल hwmon_temp_type:
			वापस 0644;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक lm95241_detect(काष्ठा i2c_client *new_client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = new_client->adapter;
	स्थिर अक्षर *name;
	पूर्णांक mfg_id, chip_id;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	mfg_id = i2c_smbus_पढ़ो_byte_data(new_client, LM95241_REG_R_MAN_ID);
	अगर (mfg_id != NATSEMI_MAN_ID)
		वापस -ENODEV;

	chip_id = i2c_smbus_पढ़ो_byte_data(new_client, LM95241_REG_R_CHIP_ID);
	चयन (chip_id) अणु
	हाल LM95231_CHIP_ID:
		name = "lm95231";
		अवरोध;
	हाल LM95241_CHIP_ID:
		name = "lm95241";
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	/* Fill the i2c board info */
	strlcpy(info->type, name, I2C_NAME_SIZE);
	वापस 0;
पूर्ण

अटल व्योम lm95241_init_client(काष्ठा i2c_client *client,
				काष्ठा lm95241_data *data)
अणु
	data->पूर्णांकerval = 1000;
	data->config = CFG_CR1000;
	data->trutherm = (TT_OFF << TT1_SHIFT) | (TT_OFF << TT2_SHIFT);

	i2c_smbus_ग_लिखो_byte_data(client, LM95241_REG_RW_CONFIG, data->config);
	i2c_smbus_ग_लिखो_byte_data(client, LM95241_REG_RW_REM_FILTER,
				  R1FE_MASK | R2FE_MASK);
	i2c_smbus_ग_लिखो_byte_data(client, LM95241_REG_RW_TRUTHERM,
				  data->trutherm);
	i2c_smbus_ग_लिखो_byte_data(client, LM95241_REG_RW_REMOTE_MODEL,
				  data->model);
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *lm95241_info[] = अणु
	HWMON_CHANNEL_INFO(chip,
			   HWMON_C_UPDATE_INTERVAL),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
			   HWMON_T_TYPE | HWMON_T_FAULT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
			   HWMON_T_TYPE | HWMON_T_FAULT),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops lm95241_hwmon_ops = अणु
	.is_visible = lm95241_is_visible,
	.पढ़ो = lm95241_पढ़ो,
	.ग_लिखो = lm95241_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info lm95241_chip_info = अणु
	.ops = &lm95241_hwmon_ops,
	.info = lm95241_info,
पूर्ण;

अटल पूर्णांक lm95241_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा lm95241_data *data;
	काष्ठा device *hwmon_dev;

	data = devm_kzalloc(dev, माप(काष्ठा lm95241_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/* Initialize the LM95241 chip */
	lm95241_init_client(client, data);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, client->name,
							   data,
							   &lm95241_chip_info,
							   शून्य);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

/* Driver data (common to all clients) */
अटल स्थिर काष्ठा i2c_device_id lm95241_id[] = अणु
	अणु "lm95231", 0 पूर्ण,
	अणु "lm95241", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm95241_id);

अटल काष्ठा i2c_driver lm95241_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= DEVNAME,
	पूर्ण,
	.probe_new	= lm95241_probe,
	.id_table	= lm95241_id,
	.detect		= lm95241_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(lm95241_driver);

MODULE_AUTHOR("Davide Rizzo <elpa.rizzo@gmail.com>");
MODULE_DESCRIPTION("LM95231/LM95241 sensor driver");
MODULE_LICENSE("GPL");
