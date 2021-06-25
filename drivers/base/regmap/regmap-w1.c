<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Register map access API - W1 (1-Wire) support
//
// Copyright (c) 2017 Radioavionica Corporation
// Author: Alex A. Mihaylov <minimumlaw@rambler.ru>

#समावेश <linux/regmap.h>
#समावेश <linux/module.h>
#समावेश <linux/w1.h>

#समावेश "internal.h"

#घोषणा W1_CMD_READ_DATA	0x69
#घोषणा W1_CMD_WRITE_DATA	0x6C

/*
 * 1-Wire slaves रेजिस्टरs with addess 8 bit and data 8 bit
 */

अटल पूर्णांक w1_reg_a8_v8_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा device *dev = context;
	काष्ठा w1_slave *sl = container_of(dev, काष्ठा w1_slave, dev);
	पूर्णांक ret = 0;

	अगर (reg > 255)
		वापस -EINVAL;

	mutex_lock(&sl->master->bus_mutex);
	अगर (!w1_reset_select_slave(sl)) अणु
		w1_ग_लिखो_8(sl->master, W1_CMD_READ_DATA);
		w1_ग_लिखो_8(sl->master, reg);
		*val = w1_पढ़ो_8(sl->master);
	पूर्ण अन्यथा अणु
		ret = -ENODEV;
	पूर्ण
	mutex_unlock(&sl->master->bus_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक w1_reg_a8_v8_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा device *dev = context;
	काष्ठा w1_slave *sl = container_of(dev, काष्ठा w1_slave, dev);
	पूर्णांक ret = 0;

	अगर (reg > 255)
		वापस -EINVAL;

	mutex_lock(&sl->master->bus_mutex);
	अगर (!w1_reset_select_slave(sl)) अणु
		w1_ग_लिखो_8(sl->master, W1_CMD_WRITE_DATA);
		w1_ग_लिखो_8(sl->master, reg);
		w1_ग_लिखो_8(sl->master, val);
	पूर्ण अन्यथा अणु
		ret = -ENODEV;
	पूर्ण
	mutex_unlock(&sl->master->bus_mutex);

	वापस ret;
पूर्ण

/*
 * 1-Wire slaves रेजिस्टरs with addess 8 bit and data 16 bit
 */

अटल पूर्णांक w1_reg_a8_v16_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				अचिन्हित पूर्णांक *val)
अणु
	काष्ठा device *dev = context;
	काष्ठा w1_slave *sl = container_of(dev, काष्ठा w1_slave, dev);
	पूर्णांक ret = 0;

	अगर (reg > 255)
		वापस -EINVAL;

	mutex_lock(&sl->master->bus_mutex);
	अगर (!w1_reset_select_slave(sl)) अणु
		w1_ग_लिखो_8(sl->master, W1_CMD_READ_DATA);
		w1_ग_लिखो_8(sl->master, reg);
		*val = w1_पढ़ो_8(sl->master);
		*val |= w1_पढ़ो_8(sl->master)<<8;
	पूर्ण अन्यथा अणु
		ret = -ENODEV;
	पूर्ण
	mutex_unlock(&sl->master->bus_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक w1_reg_a8_v16_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				अचिन्हित पूर्णांक val)
अणु
	काष्ठा device *dev = context;
	काष्ठा w1_slave *sl = container_of(dev, काष्ठा w1_slave, dev);
	पूर्णांक ret = 0;

	अगर (reg > 255)
		वापस -EINVAL;

	mutex_lock(&sl->master->bus_mutex);
	अगर (!w1_reset_select_slave(sl)) अणु
		w1_ग_लिखो_8(sl->master, W1_CMD_WRITE_DATA);
		w1_ग_लिखो_8(sl->master, reg);
		w1_ग_लिखो_8(sl->master, val & 0x00FF);
		w1_ग_लिखो_8(sl->master, val>>8 & 0x00FF);
	पूर्ण अन्यथा अणु
		ret = -ENODEV;
	पूर्ण
	mutex_unlock(&sl->master->bus_mutex);

	वापस ret;
पूर्ण

/*
 * 1-Wire slaves रेजिस्टरs with addess 16 bit and data 16 bit
 */

अटल पूर्णांक w1_reg_a16_v16_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				अचिन्हित पूर्णांक *val)
अणु
	काष्ठा device *dev = context;
	काष्ठा w1_slave *sl = container_of(dev, काष्ठा w1_slave, dev);
	पूर्णांक ret = 0;

	अगर (reg > 65535)
		वापस -EINVAL;

	mutex_lock(&sl->master->bus_mutex);
	अगर (!w1_reset_select_slave(sl)) अणु
		w1_ग_लिखो_8(sl->master, W1_CMD_READ_DATA);
		w1_ग_लिखो_8(sl->master, reg & 0x00FF);
		w1_ग_लिखो_8(sl->master, reg>>8 & 0x00FF);
		*val = w1_पढ़ो_8(sl->master);
		*val |= w1_पढ़ो_8(sl->master)<<8;
	पूर्ण अन्यथा अणु
		ret = -ENODEV;
	पूर्ण
	mutex_unlock(&sl->master->bus_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक w1_reg_a16_v16_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				अचिन्हित पूर्णांक val)
अणु
	काष्ठा device *dev = context;
	काष्ठा w1_slave *sl = container_of(dev, काष्ठा w1_slave, dev);
	पूर्णांक ret = 0;

	अगर (reg > 65535)
		वापस -EINVAL;

	mutex_lock(&sl->master->bus_mutex);
	अगर (!w1_reset_select_slave(sl)) अणु
		w1_ग_लिखो_8(sl->master, W1_CMD_WRITE_DATA);
		w1_ग_लिखो_8(sl->master, reg & 0x00FF);
		w1_ग_लिखो_8(sl->master, reg>>8 & 0x00FF);
		w1_ग_लिखो_8(sl->master, val & 0x00FF);
		w1_ग_लिखो_8(sl->master, val>>8 & 0x00FF);
	पूर्ण अन्यथा अणु
		ret = -ENODEV;
	पूर्ण
	mutex_unlock(&sl->master->bus_mutex);

	वापस ret;
पूर्ण

/*
 * Various types of supported bus addressing
 */

अटल काष्ठा regmap_bus regmap_w1_bus_a8_v8 = अणु
	.reg_पढ़ो = w1_reg_a8_v8_पढ़ो,
	.reg_ग_लिखो = w1_reg_a8_v8_ग_लिखो,
पूर्ण;

अटल काष्ठा regmap_bus regmap_w1_bus_a8_v16 = अणु
	.reg_पढ़ो = w1_reg_a8_v16_पढ़ो,
	.reg_ग_लिखो = w1_reg_a8_v16_ग_लिखो,
पूर्ण;

अटल काष्ठा regmap_bus regmap_w1_bus_a16_v16 = अणु
	.reg_पढ़ो = w1_reg_a16_v16_पढ़ो,
	.reg_ग_लिखो = w1_reg_a16_v16_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा regmap_bus *regmap_get_w1_bus(काष्ठा device *w1_dev,
					स्थिर काष्ठा regmap_config *config)
अणु
	अगर (config->reg_bits == 8 && config->val_bits == 8)
		वापस &regmap_w1_bus_a8_v8;

	अगर (config->reg_bits == 8 && config->val_bits == 16)
		वापस &regmap_w1_bus_a8_v16;

	अगर (config->reg_bits == 16 && config->val_bits == 16)
		वापस &regmap_w1_bus_a16_v16;

	वापस ERR_PTR(-ENOTSUPP);
पूर्ण

काष्ठा regmap *__regmap_init_w1(काष्ठा device *w1_dev,
				 स्थिर काष्ठा regmap_config *config,
				 काष्ठा lock_class_key *lock_key,
				 स्थिर अक्षर *lock_name)
अणु

	स्थिर काष्ठा regmap_bus *bus = regmap_get_w1_bus(w1_dev, config);

	अगर (IS_ERR(bus))
		वापस ERR_CAST(bus);

	वापस __regmap_init(w1_dev, bus, w1_dev, config,
			 lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__regmap_init_w1);

काष्ठा regmap *__devm_regmap_init_w1(काष्ठा device *w1_dev,
				 स्थिर काष्ठा regmap_config *config,
				 काष्ठा lock_class_key *lock_key,
				 स्थिर अक्षर *lock_name)
अणु

	स्थिर काष्ठा regmap_bus *bus = regmap_get_w1_bus(w1_dev, config);

	अगर (IS_ERR(bus))
		वापस ERR_CAST(bus);

	वापस __devm_regmap_init(w1_dev, bus, w1_dev, config,
				 lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__devm_regmap_init_w1);

MODULE_LICENSE("GPL");
