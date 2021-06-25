<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * i2c driver क्रम hmc5843/5843/5883/5883l/5983
 *
 * Split from hmc5843.c
 * Copyright (C) Josef Gajdusek <atx@atx.name>
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/triggered_buffer.h>

#समावेश "hmc5843.h"

अटल स्थिर काष्ठा regmap_range hmc5843_पढ़ोable_ranges[] = अणु
	regmap_reg_range(0, HMC5843_ID_END),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table hmc5843_पढ़ोable_table = अणु
	.yes_ranges = hmc5843_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(hmc5843_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range hmc5843_writable_ranges[] = अणु
	regmap_reg_range(0, HMC5843_MODE_REG),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table hmc5843_writable_table = अणु
	.yes_ranges = hmc5843_writable_ranges,
	.n_yes_ranges = ARRAY_SIZE(hmc5843_writable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range hmc5843_अस्थिर_ranges[] = अणु
	regmap_reg_range(HMC5843_DATA_OUT_MSB_REGS, HMC5843_STATUS_REG),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table hmc5843_अस्थिर_table = अणु
	.yes_ranges = hmc5843_अस्थिर_ranges,
	.n_yes_ranges = ARRAY_SIZE(hmc5843_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config hmc5843_i2c_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.rd_table = &hmc5843_पढ़ोable_table,
	.wr_table = &hmc5843_writable_table,
	.अस्थिर_table = &hmc5843_अस्थिर_table,

	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक hmc5843_i2c_probe(काष्ठा i2c_client *cli,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap = devm_regmap_init_i2c(cli,
			&hmc5843_i2c_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस hmc5843_common_probe(&cli->dev,
			regmap,
			id->driver_data, id->name);
पूर्ण

अटल पूर्णांक hmc5843_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस hmc5843_common_हटाओ(&client->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id hmc5843_id[] = अणु
	अणु "hmc5843", HMC5843_ID पूर्ण,
	अणु "hmc5883", HMC5883_ID पूर्ण,
	अणु "hmc5883l", HMC5883L_ID पूर्ण,
	अणु "hmc5983", HMC5983_ID पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, hmc5843_id);

अटल स्थिर काष्ठा of_device_id hmc5843_of_match[] = अणु
	अणु .compatible = "honeywell,hmc5843", .data = (व्योम *)HMC5843_ID पूर्ण,
	अणु .compatible = "honeywell,hmc5883", .data = (व्योम *)HMC5883_ID पूर्ण,
	अणु .compatible = "honeywell,hmc5883l", .data = (व्योम *)HMC5883L_ID पूर्ण,
	अणु .compatible = "honeywell,hmc5983", .data = (व्योम *)HMC5983_ID पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hmc5843_of_match);

अटल काष्ठा i2c_driver hmc5843_driver = अणु
	.driver = अणु
		.name	= "hmc5843",
		.pm	= HMC5843_PM_OPS,
		.of_match_table = hmc5843_of_match,
	पूर्ण,
	.id_table	= hmc5843_id,
	.probe		= hmc5843_i2c_probe,
	.हटाओ		= hmc5843_i2c_हटाओ,
पूर्ण;
module_i2c_driver(hmc5843_driver);

MODULE_AUTHOR("Josef Gajdusek <atx@atx.name>");
MODULE_DESCRIPTION("HMC5843/5883/5883L/5983 i2c driver");
MODULE_LICENSE("GPL");
