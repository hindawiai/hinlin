<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Register map access API - SCCB support

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश "internal.h"

/**
 * sccb_is_available - Check अगर the adapter supports SCCB protocol
 * @adap: I2C adapter
 *
 * Return true अगर the I2C adapter is capable of using SCCB helper functions,
 * false otherwise.
 */
अटल bool sccb_is_available(काष्ठा i2c_adapter *adap)
अणु
	u32 needed_funcs = I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_WRITE_BYTE_DATA;

	/*
	 * If we ever want support क्रम hardware करोing SCCB natively, we will
	 * पूर्णांकroduce a sccb_xfer() callback to काष्ठा i2c_algorithm and check
	 * क्रम it here.
	 */

	वापस (i2c_get_functionality(adap) & needed_funcs) == needed_funcs;
पूर्ण

/**
 * regmap_sccb_पढ़ो - Read data from SCCB slave device
 * @context: Device that will be पूर्णांकeracted with
 * @reg: Register to be पढ़ो from
 * @val: Poपूर्णांकer to store पढ़ो value
 *
 * This executes the 2-phase ग_लिखो transmission cycle that is followed by a
 * 2-phase पढ़ो transmission cycle, वापसing negative त्रुटि_सं अन्यथा zero on
 * success.
 */
अटल पूर्णांक regmap_sccb_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	पूर्णांक ret;
	जोड़ i2c_smbus_data data;

	i2c_lock_bus(i2c->adapter, I2C_LOCK_SEGMENT);

	ret = __i2c_smbus_xfer(i2c->adapter, i2c->addr, i2c->flags,
			       I2C_SMBUS_WRITE, reg, I2C_SMBUS_BYTE, शून्य);
	अगर (ret < 0)
		जाओ out;

	ret = __i2c_smbus_xfer(i2c->adapter, i2c->addr, i2c->flags,
			       I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &data);
	अगर (ret < 0)
		जाओ out;

	*val = data.byte;
out:
	i2c_unlock_bus(i2c->adapter, I2C_LOCK_SEGMENT);

	वापस ret;
पूर्ण

/**
 * regmap_sccb_ग_लिखो - Write data to SCCB slave device
 * @context: Device that will be पूर्णांकeracted with
 * @reg: Register to ग_लिखो to
 * @val: Value to be written
 *
 * This executes the SCCB 3-phase ग_लिखो transmission cycle, वापसing negative
 * त्रुटि_सं अन्यथा zero on success.
 */
अटल पूर्णांक regmap_sccb_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);

	वापस i2c_smbus_ग_लिखो_byte_data(i2c, reg, val);
पूर्ण

अटल काष्ठा regmap_bus regmap_sccb_bus = अणु
	.reg_ग_लिखो = regmap_sccb_ग_लिखो,
	.reg_पढ़ो = regmap_sccb_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा regmap_bus *regmap_get_sccb_bus(काष्ठा i2c_client *i2c,
					स्थिर काष्ठा regmap_config *config)
अणु
	अगर (config->val_bits == 8 && config->reg_bits == 8 &&
			sccb_is_available(i2c->adapter))
		वापस &regmap_sccb_bus;

	वापस ERR_PTR(-ENOTSUPP);
पूर्ण

काष्ठा regmap *__regmap_init_sccb(काष्ठा i2c_client *i2c,
				  स्थिर काष्ठा regmap_config *config,
				  काष्ठा lock_class_key *lock_key,
				  स्थिर अक्षर *lock_name)
अणु
	स्थिर काष्ठा regmap_bus *bus = regmap_get_sccb_bus(i2c, config);

	अगर (IS_ERR(bus))
		वापस ERR_CAST(bus);

	वापस __regmap_init(&i2c->dev, bus, &i2c->dev, config,
			     lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__regmap_init_sccb);

काष्ठा regmap *__devm_regmap_init_sccb(काष्ठा i2c_client *i2c,
				       स्थिर काष्ठा regmap_config *config,
				       काष्ठा lock_class_key *lock_key,
				       स्थिर अक्षर *lock_name)
अणु
	स्थिर काष्ठा regmap_bus *bus = regmap_get_sccb_bus(i2c, config);

	अगर (IS_ERR(bus))
		वापस ERR_CAST(bus);

	वापस __devm_regmap_init(&i2c->dev, bus, &i2c->dev, config,
				  lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__devm_regmap_init_sccb);

MODULE_LICENSE("GPL v2");
