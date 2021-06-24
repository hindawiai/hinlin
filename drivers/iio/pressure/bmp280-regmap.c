<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश "bmp280.h"

अटल bool bmp180_is_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल BMP280_REG_CTRL_MEAS:
	हाल BMP280_REG_RESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool bmp180_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल BMP180_REG_OUT_XLSB:
	हाल BMP180_REG_OUT_LSB:
	हाल BMP180_REG_OUT_MSB:
	हाल BMP280_REG_CTRL_MEAS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

स्थिर काष्ठा regmap_config bmp180_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = BMP180_REG_OUT_XLSB,
	.cache_type = REGCACHE_RBTREE,

	.ग_लिखोable_reg = bmp180_is_ग_लिखोable_reg,
	.अस्थिर_reg = bmp180_is_अस्थिर_reg,
पूर्ण;
EXPORT_SYMBOL(bmp180_regmap_config);

अटल bool bmp280_is_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल BMP280_REG_CONFIG:
	हाल BMP280_REG_CTRL_HUMIDITY:
	हाल BMP280_REG_CTRL_MEAS:
	हाल BMP280_REG_RESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool bmp280_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल BMP280_REG_HUMIDITY_LSB:
	हाल BMP280_REG_HUMIDITY_MSB:
	हाल BMP280_REG_TEMP_XLSB:
	हाल BMP280_REG_TEMP_LSB:
	हाल BMP280_REG_TEMP_MSB:
	हाल BMP280_REG_PRESS_XLSB:
	हाल BMP280_REG_PRESS_LSB:
	हाल BMP280_REG_PRESS_MSB:
	हाल BMP280_REG_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

स्थिर काष्ठा regmap_config bmp280_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = BMP280_REG_HUMIDITY_LSB,
	.cache_type = REGCACHE_RBTREE,

	.ग_लिखोable_reg = bmp280_is_ग_लिखोable_reg,
	.अस्थिर_reg = bmp280_is_अस्थिर_reg,
पूर्ण;
EXPORT_SYMBOL(bmp280_regmap_config);
