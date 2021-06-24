<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright(c) 2015-17 Intel Corporation.

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश "internal.h"

अटल पूर्णांक regmap_sdw_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा device *dev = context;
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);

	वापस sdw_ग_लिखो_no_pm(slave, reg, val);
पूर्ण

अटल पूर्णांक regmap_sdw_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा device *dev = context;
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);
	पूर्णांक पढ़ो;

	पढ़ो = sdw_पढ़ो_no_pm(slave, reg);
	अगर (पढ़ो < 0)
		वापस पढ़ो;

	*val = पढ़ो;
	वापस 0;
पूर्ण

अटल काष्ठा regmap_bus regmap_sdw = अणु
	.reg_पढ़ो = regmap_sdw_पढ़ो,
	.reg_ग_लिखो = regmap_sdw_ग_लिखो,
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_LITTLE,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_LITTLE,
पूर्ण;

अटल पूर्णांक regmap_sdw_config_check(स्थिर काष्ठा regmap_config *config)
अणु
	/* All रेजिस्टर are 8-bits wide as per MIPI Soundwire 1.0 Spec */
	अगर (config->val_bits != 8)
		वापस -ENOTSUPP;

	/* Registers are 32 bits wide */
	अगर (config->reg_bits != 32)
		वापस -ENOTSUPP;

	अगर (config->pad_bits != 0)
		वापस -ENOTSUPP;

	वापस 0;
पूर्ण

काष्ठा regmap *__regmap_init_sdw(काष्ठा sdw_slave *sdw,
				 स्थिर काष्ठा regmap_config *config,
				 काष्ठा lock_class_key *lock_key,
				 स्थिर अक्षर *lock_name)
अणु
	पूर्णांक ret;

	ret = regmap_sdw_config_check(config);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस __regmap_init(&sdw->dev, &regmap_sdw,
			&sdw->dev, config, lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__regmap_init_sdw);

काष्ठा regmap *__devm_regmap_init_sdw(काष्ठा sdw_slave *sdw,
				      स्थिर काष्ठा regmap_config *config,
				      काष्ठा lock_class_key *lock_key,
				      स्थिर अक्षर *lock_name)
अणु
	पूर्णांक ret;

	ret = regmap_sdw_config_check(config);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस __devm_regmap_init(&sdw->dev, &regmap_sdw,
			&sdw->dev, config, lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__devm_regmap_init_sdw);

MODULE_DESCRIPTION("Regmap SoundWire Module");
MODULE_LICENSE("GPL v2");
