<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017, Linaro Ltd.

#समावेश <linux/regmap.h>
#समावेश <linux/slimbus.h>
#समावेश <linux/module.h>

#समावेश "internal.h"

अटल पूर्णांक regmap_slimbus_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा slim_device *sdev = context;

	वापस slim_ग_लिखो(sdev, *(u16 *)data, count - 2, (u8 *)data + 2);
पूर्ण

अटल पूर्णांक regmap_slimbus_पढ़ो(व्योम *context, स्थिर व्योम *reg, माप_प्रकार reg_size,
			       व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा slim_device *sdev = context;

	वापस slim_पढ़ो(sdev, *(u16 *)reg, val_size, val);
पूर्ण

अटल काष्ठा regmap_bus regmap_slimbus_bus = अणु
	.ग_लिखो = regmap_slimbus_ग_लिखो,
	.पढ़ो = regmap_slimbus_पढ़ो,
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_LITTLE,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_LITTLE,
पूर्ण;

अटल स्थिर काष्ठा regmap_bus *regmap_get_slimbus(काष्ठा slim_device *slim,
					स्थिर काष्ठा regmap_config *config)
अणु
	अगर (config->val_bits == 8 && config->reg_bits == 16)
		वापस &regmap_slimbus_bus;

	वापस ERR_PTR(-ENOTSUPP);
पूर्ण

काष्ठा regmap *__regmap_init_slimbus(काष्ठा slim_device *slimbus,
				     स्थिर काष्ठा regmap_config *config,
				     काष्ठा lock_class_key *lock_key,
				     स्थिर अक्षर *lock_name)
अणु
	स्थिर काष्ठा regmap_bus *bus = regmap_get_slimbus(slimbus, config);

	अगर (IS_ERR(bus))
		वापस ERR_CAST(bus);

	वापस __regmap_init(&slimbus->dev, bus, &slimbus->dev, config,
			     lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__regmap_init_slimbus);

काष्ठा regmap *__devm_regmap_init_slimbus(काष्ठा slim_device *slimbus,
					  स्थिर काष्ठा regmap_config *config,
					  काष्ठा lock_class_key *lock_key,
					  स्थिर अक्षर *lock_name)
अणु
	स्थिर काष्ठा regmap_bus *bus = regmap_get_slimbus(slimbus, config);

	अगर (IS_ERR(bus))
		वापस ERR_CAST(bus);

	वापस __devm_regmap_init(&slimbus->dev, bus, &slimbus, config,
				  lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__devm_regmap_init_slimbus);

MODULE_LICENSE("GPL v2");
