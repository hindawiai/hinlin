<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 Alexander Stein <alexander.stein@systec-electronic.com>
 *
 * The LM95245 is a sensor chip made by TI / National Semiconductor.
 * It reports up to two temperatures (its own plus an बाह्यal one).
 *
 * This driver is based on lm95241.c
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु
	0x18, 0x19, 0x29, 0x4c, 0x4d, I2C_CLIENT_END पूर्ण;

/* LM95245 रेजिस्टरs */
/* general रेजिस्टरs */
#घोषणा LM95245_REG_RW_CONFIG1		0x03
#घोषणा LM95245_REG_RW_CONVERS_RATE	0x04
#घोषणा LM95245_REG_W_ONE_SHOT		0x0F

/* diode configuration */
#घोषणा LM95245_REG_RW_CONFIG2		0xBF
#घोषणा LM95245_REG_RW_REMOTE_OFFH	0x11
#घोषणा LM95245_REG_RW_REMOTE_OFFL	0x12

/* status रेजिस्टरs */
#घोषणा LM95245_REG_R_STATUS1		0x02
#घोषणा LM95245_REG_R_STATUS2		0x33

/* limit रेजिस्टरs */
#घोषणा LM95245_REG_RW_REMOTE_OS_LIMIT		0x07
#घोषणा LM95245_REG_RW_LOCAL_OS_TCRIT_LIMIT	0x20
#घोषणा LM95245_REG_RW_REMOTE_TCRIT_LIMIT	0x19
#घोषणा LM95245_REG_RW_COMMON_HYSTERESIS	0x21

/* temperature चिन्हित */
#घोषणा LM95245_REG_R_LOCAL_TEMPH_S	0x00
#घोषणा LM95245_REG_R_LOCAL_TEMPL_S	0x30
#घोषणा LM95245_REG_R_REMOTE_TEMPH_S	0x01
#घोषणा LM95245_REG_R_REMOTE_TEMPL_S	0x10
/* temperature अचिन्हित */
#घोषणा LM95245_REG_R_REMOTE_TEMPH_U	0x31
#घोषणा LM95245_REG_R_REMOTE_TEMPL_U	0x32

/* id रेजिस्टरs */
#घोषणा LM95245_REG_R_MAN_ID		0xFE
#घोषणा LM95245_REG_R_CHIP_ID		0xFF

/* LM95245 specअगरic bitfields */
#घोषणा CFG_STOP		0x40
#घोषणा CFG_REMOTE_TCRIT_MASK	0x10
#घोषणा CFG_REMOTE_OS_MASK	0x08
#घोषणा CFG_LOCAL_TCRIT_MASK	0x04
#घोषणा CFG_LOCAL_OS_MASK	0x02

#घोषणा CFG2_OS_A0		0x40
#घोषणा CFG2_DIODE_FAULT_OS	0x20
#घोषणा CFG2_DIODE_FAULT_TCRIT	0x10
#घोषणा CFG2_REMOTE_TT		0x08
#घोषणा CFG2_REMOTE_FILTER_DIS	0x00
#घोषणा CFG2_REMOTE_FILTER_EN	0x06

/* conversation rate in ms */
#घोषणा RATE_CR0063	0x00
#घोषणा RATE_CR0364	0x01
#घोषणा RATE_CR1000	0x02
#घोषणा RATE_CR2500	0x03

#घोषणा STATUS1_ROS		0x10
#घोषणा STATUS1_DIODE_FAULT	0x04
#घोषणा STATUS1_RTCRIT		0x02
#घोषणा STATUS1_LOC		0x01

#घोषणा MANUFACTURER_ID		0x01
#घोषणा LM95235_REVISION	0xB1
#घोषणा LM95245_REVISION	0xB3

/* Client data (each client माला_लो its own) */
काष्ठा lm95245_data अणु
	काष्ठा regmap *regmap;
	काष्ठा mutex update_lock;
	पूर्णांक पूर्णांकerval;	/* in msecs */
पूर्ण;

/* Conversions */
अटल पूर्णांक temp_from_reg_अचिन्हित(u8 val_h, u8 val_l)
अणु
	वापस val_h * 1000 + val_l * 1000 / 256;
पूर्ण

अटल पूर्णांक temp_from_reg_चिन्हित(u8 val_h, u8 val_l)
अणु
	अगर (val_h & 0x80)
		वापस (val_h - 0x100) * 1000;
	वापस temp_from_reg_अचिन्हित(val_h, val_l);
पूर्ण

अटल पूर्णांक lm95245_पढ़ो_conversion_rate(काष्ठा lm95245_data *data)
अणु
	अचिन्हित पूर्णांक rate;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, LM95245_REG_RW_CONVERS_RATE, &rate);
	अगर (ret < 0)
		वापस ret;

	चयन (rate) अणु
	हाल RATE_CR0063:
		data->पूर्णांकerval = 63;
		अवरोध;
	हाल RATE_CR0364:
		data->पूर्णांकerval = 364;
		अवरोध;
	हाल RATE_CR1000:
		data->पूर्णांकerval = 1000;
		अवरोध;
	हाल RATE_CR2500:
	शेष:
		data->पूर्णांकerval = 2500;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lm95245_set_conversion_rate(काष्ठा lm95245_data *data, दीर्घ पूर्णांकerval)
अणु
	पूर्णांक ret, rate;

	अगर (पूर्णांकerval <= 63) अणु
		पूर्णांकerval = 63;
		rate = RATE_CR0063;
	पूर्ण अन्यथा अगर (पूर्णांकerval <= 364) अणु
		पूर्णांकerval = 364;
		rate = RATE_CR0364;
	पूर्ण अन्यथा अगर (पूर्णांकerval <= 1000) अणु
		पूर्णांकerval = 1000;
		rate = RATE_CR1000;
	पूर्ण अन्यथा अणु
		पूर्णांकerval = 2500;
		rate = RATE_CR2500;
	पूर्ण

	ret = regmap_ग_लिखो(data->regmap, LM95245_REG_RW_CONVERS_RATE, rate);
	अगर (ret < 0)
		वापस ret;

	data->पूर्णांकerval = पूर्णांकerval;
	वापस 0;
पूर्ण

अटल पूर्णांक lm95245_पढ़ो_temp(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			     दीर्घ *val)
अणु
	काष्ठा lm95245_data *data = dev_get_drvdata(dev);
	काष्ठा regmap *regmap = data->regmap;
	पूर्णांक ret, regl, regh, regvall, regvalh;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		regl = channel ? LM95245_REG_R_REMOTE_TEMPL_S :
				 LM95245_REG_R_LOCAL_TEMPL_S;
		regh = channel ? LM95245_REG_R_REMOTE_TEMPH_S :
				 LM95245_REG_R_LOCAL_TEMPH_S;
		ret = regmap_पढ़ो(regmap, regl, &regvall);
		अगर (ret < 0)
			वापस ret;
		ret = regmap_पढ़ो(regmap, regh, &regvalh);
		अगर (ret < 0)
			वापस ret;
		/*
		 * Local temp is always चिन्हित.
		 * Remote temp has both चिन्हित and अचिन्हित data.
		 * Use चिन्हित calculation क्रम remote अगर चिन्हित bit is set
		 * or अगर reported temperature is below चिन्हित limit.
		 */
		अगर (!channel || (regvalh & 0x80) || regvalh < 0x7f) अणु
			*val = temp_from_reg_चिन्हित(regvalh, regvall);
			वापस 0;
		पूर्ण
		ret = regmap_पढ़ो(regmap, LM95245_REG_R_REMOTE_TEMPL_U,
				  &regvall);
		अगर (ret < 0)
			वापस ret;
		ret = regmap_पढ़ो(regmap, LM95245_REG_R_REMOTE_TEMPH_U,
				  &regvalh);
		अगर (ret < 0)
			वापस ret;
		*val = temp_from_reg_अचिन्हित(regvalh, regvall);
		वापस 0;
	हाल hwmon_temp_max:
		ret = regmap_पढ़ो(regmap, LM95245_REG_RW_REMOTE_OS_LIMIT,
				  &regvalh);
		अगर (ret < 0)
			वापस ret;
		*val = regvalh * 1000;
		वापस 0;
	हाल hwmon_temp_crit:
		regh = channel ? LM95245_REG_RW_REMOTE_TCRIT_LIMIT :
				 LM95245_REG_RW_LOCAL_OS_TCRIT_LIMIT;
		ret = regmap_पढ़ो(regmap, regh, &regvalh);
		अगर (ret < 0)
			वापस ret;
		*val = regvalh * 1000;
		वापस 0;
	हाल hwmon_temp_max_hyst:
		ret = regmap_पढ़ो(regmap, LM95245_REG_RW_REMOTE_OS_LIMIT,
				  &regvalh);
		अगर (ret < 0)
			वापस ret;
		ret = regmap_पढ़ो(regmap, LM95245_REG_RW_COMMON_HYSTERESIS,
				  &regvall);
		अगर (ret < 0)
			वापस ret;
		*val = (regvalh - regvall) * 1000;
		वापस 0;
	हाल hwmon_temp_crit_hyst:
		regh = channel ? LM95245_REG_RW_REMOTE_TCRIT_LIMIT :
				 LM95245_REG_RW_LOCAL_OS_TCRIT_LIMIT;
		ret = regmap_पढ़ो(regmap, regh, &regvalh);
		अगर (ret < 0)
			वापस ret;
		ret = regmap_पढ़ो(regmap, LM95245_REG_RW_COMMON_HYSTERESIS,
				  &regvall);
		अगर (ret < 0)
			वापस ret;
		*val = (regvalh - regvall) * 1000;
		वापस 0;
	हाल hwmon_temp_type:
		ret = regmap_पढ़ो(regmap, LM95245_REG_RW_CONFIG2, &regvalh);
		अगर (ret < 0)
			वापस ret;
		*val = (regvalh & CFG2_REMOTE_TT) ? 1 : 2;
		वापस 0;
	हाल hwmon_temp_offset:
		ret = regmap_पढ़ो(regmap, LM95245_REG_RW_REMOTE_OFFL,
				  &regvall);
		अगर (ret < 0)
			वापस ret;
		ret = regmap_पढ़ो(regmap, LM95245_REG_RW_REMOTE_OFFH,
				  &regvalh);
		अगर (ret < 0)
			वापस ret;
		*val = temp_from_reg_चिन्हित(regvalh, regvall);
		वापस 0;
	हाल hwmon_temp_max_alarm:
		ret = regmap_पढ़ो(regmap, LM95245_REG_R_STATUS1, &regvalh);
		अगर (ret < 0)
			वापस ret;
		*val = !!(regvalh & STATUS1_ROS);
		वापस 0;
	हाल hwmon_temp_crit_alarm:
		ret = regmap_पढ़ो(regmap, LM95245_REG_R_STATUS1, &regvalh);
		अगर (ret < 0)
			वापस ret;
		*val = !!(regvalh & (channel ? STATUS1_RTCRIT : STATUS1_LOC));
		वापस 0;
	हाल hwmon_temp_fault:
		ret = regmap_पढ़ो(regmap, LM95245_REG_R_STATUS1, &regvalh);
		अगर (ret < 0)
			वापस ret;
		*val = !!(regvalh & STATUS1_DIODE_FAULT);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक lm95245_ग_लिखो_temp(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			      दीर्घ val)
अणु
	काष्ठा lm95245_data *data = dev_get_drvdata(dev);
	काष्ठा regmap *regmap = data->regmap;
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret, reg;

	चयन (attr) अणु
	हाल hwmon_temp_max:
		val = clamp_val(val / 1000, 0, 255);
		ret = regmap_ग_लिखो(regmap, LM95245_REG_RW_REMOTE_OS_LIMIT, val);
		वापस ret;
	हाल hwmon_temp_crit:
		reg = channel ? LM95245_REG_RW_REMOTE_TCRIT_LIMIT :
				LM95245_REG_RW_LOCAL_OS_TCRIT_LIMIT;
		val = clamp_val(val / 1000, 0, channel ? 255 : 127);
		ret = regmap_ग_लिखो(regmap, reg, val);
		वापस ret;
	हाल hwmon_temp_crit_hyst:
		mutex_lock(&data->update_lock);
		ret = regmap_पढ़ो(regmap, LM95245_REG_RW_LOCAL_OS_TCRIT_LIMIT,
				  &regval);
		अगर (ret < 0) अणु
			mutex_unlock(&data->update_lock);
			वापस ret;
		पूर्ण
		/* Clamp to reasonable range to prevent overflow */
		val = clamp_val(val, -1000000, 1000000);
		val = regval - val / 1000;
		val = clamp_val(val, 0, 31);
		ret = regmap_ग_लिखो(regmap, LM95245_REG_RW_COMMON_HYSTERESIS,
				   val);
		mutex_unlock(&data->update_lock);
		वापस ret;
	हाल hwmon_temp_offset:
		val = clamp_val(val, -128000, 127875);
		val = val * 256 / 1000;
		mutex_lock(&data->update_lock);
		ret = regmap_ग_लिखो(regmap, LM95245_REG_RW_REMOTE_OFFL,
				   val & 0xe0);
		अगर (ret < 0) अणु
			mutex_unlock(&data->update_lock);
			वापस ret;
		पूर्ण
		ret = regmap_ग_लिखो(regmap, LM95245_REG_RW_REMOTE_OFFH,
				   (val >> 8) & 0xff);
		mutex_unlock(&data->update_lock);
		वापस ret;
	हाल hwmon_temp_type:
		अगर (val != 1 && val != 2)
			वापस -EINVAL;
		ret = regmap_update_bits(regmap, LM95245_REG_RW_CONFIG2,
					 CFG2_REMOTE_TT,
					 val == 1 ? CFG2_REMOTE_TT : 0);
		वापस ret;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक lm95245_पढ़ो_chip(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			     दीर्घ *val)
अणु
	काष्ठा lm95245_data *data = dev_get_drvdata(dev);

	चयन (attr) अणु
	हाल hwmon_chip_update_पूर्णांकerval:
		*val = data->पूर्णांकerval;
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक lm95245_ग_लिखो_chip(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			      दीर्घ val)
अणु
	काष्ठा lm95245_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	चयन (attr) अणु
	हाल hwmon_chip_update_पूर्णांकerval:
		mutex_lock(&data->update_lock);
		ret = lm95245_set_conversion_rate(data, val);
		mutex_unlock(&data->update_lock);
		वापस ret;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक lm95245_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	चयन (type) अणु
	हाल hwmon_chip:
		वापस lm95245_पढ़ो_chip(dev, attr, channel, val);
	हाल hwmon_temp:
		वापस lm95245_पढ़ो_temp(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक lm95245_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			 u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	चयन (type) अणु
	हाल hwmon_chip:
		वापस lm95245_ग_लिखो_chip(dev, attr, channel, val);
	हाल hwmon_temp:
		वापस lm95245_ग_लिखो_temp(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t lm95245_temp_is_visible(स्थिर व्योम *data, u32 attr, पूर्णांक channel)
अणु
	चयन (attr) अणु
	हाल hwmon_temp_input:
	हाल hwmon_temp_max_alarm:
	हाल hwmon_temp_max_hyst:
	हाल hwmon_temp_crit_alarm:
	हाल hwmon_temp_fault:
		वापस 0444;
	हाल hwmon_temp_type:
	हाल hwmon_temp_max:
	हाल hwmon_temp_crit:
	हाल hwmon_temp_offset:
		वापस 0644;
	हाल hwmon_temp_crit_hyst:
		वापस (channel == 0) ? 0644 : 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल umode_t lm95245_is_visible(स्थिर व्योम *data,
				  क्रमागत hwmon_sensor_types type,
				  u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_chip:
		चयन (attr) अणु
		हाल hwmon_chip_update_पूर्णांकerval:
			वापस 0644;
		शेष:
			वापस 0;
		पूर्ण
	हाल hwmon_temp:
		वापस lm95245_temp_is_visible(data, attr, channel);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक lm95245_detect(काष्ठा i2c_client *new_client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = new_client->adapter;
	पूर्णांक address = new_client->addr;
	स्थिर अक्षर *name;
	पूर्णांक rev, id;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	id = i2c_smbus_पढ़ो_byte_data(new_client, LM95245_REG_R_MAN_ID);
	अगर (id != MANUFACTURER_ID)
		वापस -ENODEV;

	rev = i2c_smbus_पढ़ो_byte_data(new_client, LM95245_REG_R_CHIP_ID);
	चयन (rev) अणु
	हाल LM95235_REVISION:
		अगर (address != 0x18 && address != 0x29 && address != 0x4c)
			वापस -ENODEV;
		name = "lm95235";
		अवरोध;
	हाल LM95245_REVISION:
		name = "lm95245";
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, name, I2C_NAME_SIZE);
	वापस 0;
पूर्ण

अटल पूर्णांक lm95245_init_client(काष्ठा lm95245_data *data)
अणु
	पूर्णांक ret;

	ret = lm95245_पढ़ो_conversion_rate(data);
	अगर (ret < 0)
		वापस ret;

	वापस regmap_update_bits(data->regmap, LM95245_REG_RW_CONFIG1,
				  CFG_STOP, 0);
पूर्ण

अटल bool lm95245_is_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल LM95245_REG_RW_CONFIG1:
	हाल LM95245_REG_RW_CONVERS_RATE:
	हाल LM95245_REG_W_ONE_SHOT:
	हाल LM95245_REG_RW_CONFIG2:
	हाल LM95245_REG_RW_REMOTE_OFFH:
	हाल LM95245_REG_RW_REMOTE_OFFL:
	हाल LM95245_REG_RW_REMOTE_OS_LIMIT:
	हाल LM95245_REG_RW_LOCAL_OS_TCRIT_LIMIT:
	हाल LM95245_REG_RW_REMOTE_TCRIT_LIMIT:
	हाल LM95245_REG_RW_COMMON_HYSTERESIS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool lm95245_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल LM95245_REG_R_STATUS1:
	हाल LM95245_REG_R_STATUS2:
	हाल LM95245_REG_R_LOCAL_TEMPH_S:
	हाल LM95245_REG_R_LOCAL_TEMPL_S:
	हाल LM95245_REG_R_REMOTE_TEMPH_S:
	हाल LM95245_REG_R_REMOTE_TEMPL_S:
	हाल LM95245_REG_R_REMOTE_TEMPH_U:
	हाल LM95245_REG_R_REMOTE_TEMPL_U:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config lm95245_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.ग_लिखोable_reg = lm95245_is_ग_लिखोable_reg,
	.अस्थिर_reg = lm95245_is_अस्थिर_reg,
	.cache_type = REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *lm95245_info[] = अणु
	HWMON_CHANNEL_INFO(chip,
			   HWMON_C_UPDATE_INTERVAL),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_CRIT | HWMON_T_CRIT_HYST |
			   HWMON_T_CRIT_ALARM,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CRIT | HWMON_T_CRIT_HYST | HWMON_T_FAULT |
			   HWMON_T_MAX_ALARM | HWMON_T_CRIT_ALARM |
			   HWMON_T_TYPE | HWMON_T_OFFSET),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops lm95245_hwmon_ops = अणु
	.is_visible = lm95245_is_visible,
	.पढ़ो = lm95245_पढ़ो,
	.ग_लिखो = lm95245_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info lm95245_chip_info = अणु
	.ops = &lm95245_hwmon_ops,
	.info = lm95245_info,
पूर्ण;

अटल पूर्णांक lm95245_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा lm95245_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(काष्ठा lm95245_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->regmap = devm_regmap_init_i2c(client, &lm95245_regmap_config);
	अगर (IS_ERR(data->regmap))
		वापस PTR_ERR(data->regmap);

	mutex_init(&data->update_lock);

	/* Initialize the LM95245 chip */
	ret = lm95245_init_client(data);
	अगर (ret < 0)
		वापस ret;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, client->name,
							 data,
							 &lm95245_chip_info,
							 शून्य);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

/* Driver data (common to all clients) */
अटल स्थिर काष्ठा i2c_device_id lm95245_id[] = अणु
	अणु "lm95235", 0 पूर्ण,
	अणु "lm95245", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm95245_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused lm95245_of_match[] = अणु
	अणु .compatible = "national,lm95235" पूर्ण,
	अणु .compatible = "national,lm95245" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lm95245_of_match);

अटल काष्ठा i2c_driver lm95245_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "lm95245",
		.of_match_table = of_match_ptr(lm95245_of_match),
	पूर्ण,
	.probe_new	= lm95245_probe,
	.id_table	= lm95245_id,
	.detect		= lm95245_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(lm95245_driver);

MODULE_AUTHOR("Alexander Stein <alexander.stein@systec-electronic.com>");
MODULE_DESCRIPTION("LM95235/LM95245 sensor driver");
MODULE_LICENSE("GPL");
