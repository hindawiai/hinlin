<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright(c) 2020 Intel Corporation.

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>
#समावेश "internal.h"

अटल पूर्णांक regmap_sdw_mbq_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा device *dev = context;
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);
	पूर्णांक ret;

	ret = sdw_ग_लिखो_no_pm(slave, SDW_SDCA_MBQ_CTL(reg), (val >> 8) & 0xff);
	अगर (ret < 0)
		वापस ret;

	वापस sdw_ग_लिखो_no_pm(slave, reg, val & 0xff);
पूर्ण

अटल पूर्णांक regmap_sdw_mbq_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा device *dev = context;
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);
	पूर्णांक पढ़ो0;
	पूर्णांक पढ़ो1;

	पढ़ो0 = sdw_पढ़ो_no_pm(slave, reg);
	अगर (पढ़ो0 < 0)
		वापस पढ़ो0;

	पढ़ो1 = sdw_पढ़ो_no_pm(slave, SDW_SDCA_MBQ_CTL(reg));
	अगर (पढ़ो1 < 0)
		वापस पढ़ो1;

	*val = (पढ़ो1 << 8) | पढ़ो0;

	वापस 0;
पूर्ण

अटल काष्ठा regmap_bus regmap_sdw_mbq = अणु
	.reg_पढ़ो = regmap_sdw_mbq_पढ़ो,
	.reg_ग_लिखो = regmap_sdw_mbq_ग_लिखो,
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_LITTLE,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_LITTLE,
पूर्ण;

अटल पूर्णांक regmap_sdw_mbq_config_check(स्थिर काष्ठा regmap_config *config)
अणु
	/* MBQ-based controls are only 16-bits क्रम now */
	अगर (config->val_bits != 16)
		वापस -ENOTSUPP;

	/* Registers are 32 bits wide */
	अगर (config->reg_bits != 32)
		वापस -ENOTSUPP;

	अगर (config->pad_bits != 0)
		वापस -ENOTSUPP;

	वापस 0;
पूर्ण

काष्ठा regmap *__regmap_init_sdw_mbq(काष्ठा sdw_slave *sdw,
				     स्थिर काष्ठा regmap_config *config,
				     काष्ठा lock_class_key *lock_key,
				     स्थिर अक्षर *lock_name)
अणु
	पूर्णांक ret;

	ret = regmap_sdw_mbq_config_check(config);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस __regmap_init(&sdw->dev, &regmap_sdw_mbq,
			&sdw->dev, config, lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__regmap_init_sdw_mbq);

काष्ठा regmap *__devm_regmap_init_sdw_mbq(काष्ठा sdw_slave *sdw,
					  स्थिर काष्ठा regmap_config *config,
					  काष्ठा lock_class_key *lock_key,
					  स्थिर अक्षर *lock_name)
अणु
	पूर्णांक ret;

	ret = regmap_sdw_mbq_config_check(config);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस __devm_regmap_init(&sdw->dev, &regmap_sdw_mbq,
			&sdw->dev, config, lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__devm_regmap_init_sdw_mbq);

MODULE_DESCRIPTION("Regmap SoundWire MBQ Module");
MODULE_LICENSE("GPL");
