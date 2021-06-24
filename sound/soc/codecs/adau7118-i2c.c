<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Analog Devices ADAU7118 8 channel PDM-to-I2S/TDM Converter driver over I2C
//
// Copyright 2019 Analog Devices Inc.

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश "adau7118.h"

अटल स्थिर काष्ठा reg_शेष adau7118_reg_शेषs[] = अणु
	अणु ADAU7118_REG_VENDOR_ID, 0x41 पूर्ण,
	अणु ADAU7118_REG_DEVICE_ID1, 0x71 पूर्ण,
	अणु ADAU7118_REG_DEVICE_ID2, 0x18 पूर्ण,
	अणु ADAU7118_REG_REVISION_ID, 0x00 पूर्ण,
	अणु ADAU7118_REG_ENABLES, 0x3F पूर्ण,
	अणु ADAU7118_REG_DEC_RATIO_CLK_MAP, 0xC0 पूर्ण,
	अणु ADAU7118_REG_HPF_CONTROL, 0xD0 पूर्ण,
	अणु ADAU7118_REG_SPT_CTRL1, 0x41 पूर्ण,
	अणु ADAU7118_REG_SPT_CTRL2, 0x00 पूर्ण,
	अणु ADAU7118_REG_SPT_CX(0), 0x01 पूर्ण,
	अणु ADAU7118_REG_SPT_CX(1), 0x11 पूर्ण,
	अणु ADAU7118_REG_SPT_CX(2), 0x21 पूर्ण,
	अणु ADAU7118_REG_SPT_CX(3), 0x31 पूर्ण,
	अणु ADAU7118_REG_SPT_CX(4), 0x41 पूर्ण,
	अणु ADAU7118_REG_SPT_CX(5), 0x51 पूर्ण,
	अणु ADAU7118_REG_SPT_CX(6), 0x61 पूर्ण,
	अणु ADAU7118_REG_SPT_CX(7), 0x71 पूर्ण,
	अणु ADAU7118_REG_DRIVE_STRENGTH, 0x2a पूर्ण,
	अणु ADAU7118_REG_RESET, 0x00 पूर्ण,
पूर्ण;

अटल bool adau7118_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (reg == ADAU7118_REG_RESET);
पूर्ण


अटल स्थिर काष्ठा regmap_config adau7118_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.reg_शेषs = adau7118_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(adau7118_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
	.max_रेजिस्टर = ADAU7118_REG_RESET,
	.अस्थिर_reg = adau7118_अस्थिर,
पूर्ण;

अटल पूर्णांक adau7118_probe_i2c(काष्ठा i2c_client *i2c,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *map;

	map = devm_regmap_init_i2c(i2c, &adau7118_regmap_config);
	अगर (IS_ERR(map)) अणु
		dev_err(&i2c->dev, "Failed to init regmap %ld\n", PTR_ERR(map));
		वापस PTR_ERR(map);
	पूर्ण

	वापस adau7118_probe(&i2c->dev, map, false);
पूर्ण

अटल स्थिर काष्ठा of_device_id adau7118_of_match[] = अणु
	अणु .compatible = "adi,adau7118" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adau7118_of_match);

अटल स्थिर काष्ठा i2c_device_id adau7118_id[] = अणु
	अणु"adau7118", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adau7118_id);

अटल काष्ठा i2c_driver adau7118_driver = अणु
	.driver = अणु
		.name = "adau7118",
		.of_match_table = adau7118_of_match,
	पूर्ण,
	.probe = adau7118_probe_i2c,
	.id_table = adau7118_id,
पूर्ण;
module_i2c_driver(adau7118_driver);

MODULE_AUTHOR("Nuno Sa <nuno.sa@analog.com>");
MODULE_DESCRIPTION("ADAU7118 8 channel PDM-to-I2S/TDM Converter driver over I2C");
MODULE_LICENSE("GPL");
