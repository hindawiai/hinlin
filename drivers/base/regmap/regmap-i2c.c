<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Register map access API - I2C support
//
// Copyright 2011 Wolfson Microelectronics plc
//
// Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>

#समावेश <linux/regmap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>

#समावेश "internal.h"

अटल पूर्णांक regmap_smbus_byte_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				      अचिन्हित पूर्णांक *val)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	पूर्णांक ret;

	अगर (reg > 0xff)
		वापस -EINVAL;

	ret = i2c_smbus_पढ़ो_byte_data(i2c, reg);
	अगर (ret < 0)
		वापस ret;

	*val = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक regmap_smbus_byte_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				       अचिन्हित पूर्णांक val)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);

	अगर (val > 0xff || reg > 0xff)
		वापस -EINVAL;

	वापस i2c_smbus_ग_लिखो_byte_data(i2c, reg, val);
पूर्ण

अटल स्थिर काष्ठा regmap_bus regmap_smbus_byte = अणु
	.reg_ग_लिखो = regmap_smbus_byte_reg_ग_लिखो,
	.reg_पढ़ो = regmap_smbus_byte_reg_पढ़ो,
पूर्ण;

अटल पूर्णांक regmap_smbus_word_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				      अचिन्हित पूर्णांक *val)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	पूर्णांक ret;

	अगर (reg > 0xff)
		वापस -EINVAL;

	ret = i2c_smbus_पढ़ो_word_data(i2c, reg);
	अगर (ret < 0)
		वापस ret;

	*val = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक regmap_smbus_word_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				       अचिन्हित पूर्णांक val)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);

	अगर (val > 0xffff || reg > 0xff)
		वापस -EINVAL;

	वापस i2c_smbus_ग_लिखो_word_data(i2c, reg, val);
पूर्ण

अटल स्थिर काष्ठा regmap_bus regmap_smbus_word = अणु
	.reg_ग_लिखो = regmap_smbus_word_reg_ग_लिखो,
	.reg_पढ़ो = regmap_smbus_word_reg_पढ़ो,
पूर्ण;

अटल पूर्णांक regmap_smbus_word_पढ़ो_swapped(व्योम *context, अचिन्हित पूर्णांक reg,
					  अचिन्हित पूर्णांक *val)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	पूर्णांक ret;

	अगर (reg > 0xff)
		वापस -EINVAL;

	ret = i2c_smbus_पढ़ो_word_swapped(i2c, reg);
	अगर (ret < 0)
		वापस ret;

	*val = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक regmap_smbus_word_ग_लिखो_swapped(व्योम *context, अचिन्हित पूर्णांक reg,
					   अचिन्हित पूर्णांक val)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);

	अगर (val > 0xffff || reg > 0xff)
		वापस -EINVAL;

	वापस i2c_smbus_ग_लिखो_word_swapped(i2c, reg, val);
पूर्ण

अटल स्थिर काष्ठा regmap_bus regmap_smbus_word_swapped = अणु
	.reg_ग_लिखो = regmap_smbus_word_ग_लिखो_swapped,
	.reg_पढ़ो = regmap_smbus_word_पढ़ो_swapped,
पूर्ण;

अटल पूर्णांक regmap_i2c_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	पूर्णांक ret;

	ret = i2c_master_send(i2c, data, count);
	अगर (ret == count)
		वापस 0;
	अन्यथा अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस -EIO;
पूर्ण

अटल पूर्णांक regmap_i2c_gather_ग_लिखो(व्योम *context,
				   स्थिर व्योम *reg, माप_प्रकार reg_size,
				   स्थिर व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा i2c_msg xfer[2];
	पूर्णांक ret;

	/* If the I2C controller can't करो a gather tell the core, it
	 * will substitute in a linear ग_लिखो क्रम us.
	 */
	अगर (!i2c_check_functionality(i2c->adapter, I2C_FUNC_NOSTART))
		वापस -ENOTSUPP;

	xfer[0].addr = i2c->addr;
	xfer[0].flags = 0;
	xfer[0].len = reg_size;
	xfer[0].buf = (व्योम *)reg;

	xfer[1].addr = i2c->addr;
	xfer[1].flags = I2C_M_NOSTART;
	xfer[1].len = val_size;
	xfer[1].buf = (व्योम *)val;

	ret = i2c_transfer(i2c->adapter, xfer, 2);
	अगर (ret == 2)
		वापस 0;
	अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस -EIO;
पूर्ण

अटल पूर्णांक regmap_i2c_पढ़ो(व्योम *context,
			   स्थिर व्योम *reg, माप_प्रकार reg_size,
			   व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा i2c_msg xfer[2];
	पूर्णांक ret;

	xfer[0].addr = i2c->addr;
	xfer[0].flags = 0;
	xfer[0].len = reg_size;
	xfer[0].buf = (व्योम *)reg;

	xfer[1].addr = i2c->addr;
	xfer[1].flags = I2C_M_RD;
	xfer[1].len = val_size;
	xfer[1].buf = val;

	ret = i2c_transfer(i2c->adapter, xfer, 2);
	अगर (ret == 2)
		वापस 0;
	अन्यथा अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस -EIO;
पूर्ण

अटल स्थिर काष्ठा regmap_bus regmap_i2c = अणु
	.ग_लिखो = regmap_i2c_ग_लिखो,
	.gather_ग_लिखो = regmap_i2c_gather_ग_लिखो,
	.पढ़ो = regmap_i2c_पढ़ो,
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_BIG,
पूर्ण;

अटल पूर्णांक regmap_i2c_smbus_i2c_ग_लिखो(व्योम *context, स्थिर व्योम *data,
				      माप_प्रकार count)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);

	अगर (count < 1)
		वापस -EINVAL;

	--count;
	वापस i2c_smbus_ग_लिखो_i2c_block_data(i2c, ((u8 *)data)[0], count,
					      ((u8 *)data + 1));
पूर्ण

अटल पूर्णांक regmap_i2c_smbus_i2c_पढ़ो(व्योम *context, स्थिर व्योम *reg,
				     माप_प्रकार reg_size, व्योम *val,
				     माप_प्रकार val_size)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	पूर्णांक ret;

	अगर (reg_size != 1 || val_size < 1)
		वापस -EINVAL;

	ret = i2c_smbus_पढ़ो_i2c_block_data(i2c, ((u8 *)reg)[0], val_size, val);
	अगर (ret == val_size)
		वापस 0;
	अन्यथा अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस -EIO;
पूर्ण

अटल स्थिर काष्ठा regmap_bus regmap_i2c_smbus_i2c_block = अणु
	.ग_लिखो = regmap_i2c_smbus_i2c_ग_लिखो,
	.पढ़ो = regmap_i2c_smbus_i2c_पढ़ो,
	.max_raw_पढ़ो = I2C_SMBUS_BLOCK_MAX,
	.max_raw_ग_लिखो = I2C_SMBUS_BLOCK_MAX,
पूर्ण;

अटल पूर्णांक regmap_i2c_smbus_i2c_ग_लिखो_reg16(व्योम *context, स्थिर व्योम *data,
				      माप_प्रकार count)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);

	अगर (count < 2)
		वापस -EINVAL;

	count--;
	वापस i2c_smbus_ग_लिखो_i2c_block_data(i2c, ((u8 *)data)[0], count,
					      (u8 *)data + 1);
पूर्ण

अटल पूर्णांक regmap_i2c_smbus_i2c_पढ़ो_reg16(व्योम *context, स्थिर व्योम *reg,
				     माप_प्रकार reg_size, व्योम *val,
				     माप_प्रकार val_size)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	पूर्णांक ret, count, len = val_size;

	अगर (reg_size != 2)
		वापस -EINVAL;

	ret = i2c_smbus_ग_लिखो_byte_data(i2c, ((u16 *)reg)[0] & 0xff,
					((u16 *)reg)[0] >> 8);
	अगर (ret < 0)
		वापस ret;

	count = 0;
	करो अणु
		/* Current Address Read */
		ret = i2c_smbus_पढ़ो_byte(i2c);
		अगर (ret < 0)
			अवरोध;

		*((u8 *)val++) = ret;
		count++;
		len--;
	पूर्ण जबतक (len > 0);

	अगर (count == val_size)
		वापस 0;
	अन्यथा अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस -EIO;
पूर्ण

अटल स्थिर काष्ठा regmap_bus regmap_i2c_smbus_i2c_block_reg16 = अणु
	.ग_लिखो = regmap_i2c_smbus_i2c_ग_लिखो_reg16,
	.पढ़ो = regmap_i2c_smbus_i2c_पढ़ो_reg16,
	.max_raw_पढ़ो = I2C_SMBUS_BLOCK_MAX,
	.max_raw_ग_लिखो = I2C_SMBUS_BLOCK_MAX,
पूर्ण;

अटल स्थिर काष्ठा regmap_bus *regmap_get_i2c_bus(काष्ठा i2c_client *i2c,
					स्थिर काष्ठा regmap_config *config)
अणु
	अगर (i2c_check_functionality(i2c->adapter, I2C_FUNC_I2C))
		वापस &regmap_i2c;
	अन्यथा अगर (config->val_bits == 8 && config->reg_bits == 8 &&
		 i2c_check_functionality(i2c->adapter,
					 I2C_FUNC_SMBUS_I2C_BLOCK))
		वापस &regmap_i2c_smbus_i2c_block;
	अन्यथा अगर (config->val_bits == 8 && config->reg_bits == 16 &&
		i2c_check_functionality(i2c->adapter,
					I2C_FUNC_SMBUS_I2C_BLOCK))
		वापस &regmap_i2c_smbus_i2c_block_reg16;
	अन्यथा अगर (config->val_bits == 16 && config->reg_bits == 8 &&
		 i2c_check_functionality(i2c->adapter,
					 I2C_FUNC_SMBUS_WORD_DATA))
		चयन (regmap_get_val_endian(&i2c->dev, शून्य, config)) अणु
		हाल REGMAP_ENDIAN_LITTLE:
			वापस &regmap_smbus_word;
		हाल REGMAP_ENDIAN_BIG:
			वापस &regmap_smbus_word_swapped;
		शेष:		/* everything अन्यथा is not supported */
			अवरोध;
		पूर्ण
	अन्यथा अगर (config->val_bits == 8 && config->reg_bits == 8 &&
		 i2c_check_functionality(i2c->adapter,
					 I2C_FUNC_SMBUS_BYTE_DATA))
		वापस &regmap_smbus_byte;

	वापस ERR_PTR(-ENOTSUPP);
पूर्ण

काष्ठा regmap *__regmap_init_i2c(काष्ठा i2c_client *i2c,
				 स्थिर काष्ठा regmap_config *config,
				 काष्ठा lock_class_key *lock_key,
				 स्थिर अक्षर *lock_name)
अणु
	स्थिर काष्ठा regmap_bus *bus = regmap_get_i2c_bus(i2c, config);

	अगर (IS_ERR(bus))
		वापस ERR_CAST(bus);

	वापस __regmap_init(&i2c->dev, bus, &i2c->dev, config,
			     lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__regmap_init_i2c);

काष्ठा regmap *__devm_regmap_init_i2c(काष्ठा i2c_client *i2c,
				      स्थिर काष्ठा regmap_config *config,
				      काष्ठा lock_class_key *lock_key,
				      स्थिर अक्षर *lock_name)
अणु
	स्थिर काष्ठा regmap_bus *bus = regmap_get_i2c_bus(i2c, config);

	अगर (IS_ERR(bus))
		वापस ERR_CAST(bus);

	वापस __devm_regmap_init(&i2c->dev, bus, &i2c->dev, config,
				  lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__devm_regmap_init_i2c);

MODULE_LICENSE("GPL");
