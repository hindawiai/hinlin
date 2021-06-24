<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics hts221 i2c driver
 *
 * Copyright 2016 STMicroelectronics Inc.
 *
 * Lorenzo Bianconi <lorenzo.bianconi@st.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>

#समावेश "hts221.h"

#घोषणा HTS221_I2C_AUTO_INCREMENT	BIT(7)

अटल स्थिर काष्ठा regmap_config hts221_i2c_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.ग_लिखो_flag_mask = HTS221_I2C_AUTO_INCREMENT,
	.पढ़ो_flag_mask = HTS221_I2C_AUTO_INCREMENT,
पूर्ण;

अटल पूर्णांक hts221_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i2c(client, &hts221_i2c_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Failed to register i2c regmap %ld\n",
			PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस hts221_probe(&client->dev, client->irq,
			    client->name, regmap);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id hts221_acpi_match[] = अणु
	अणु"SMO9100", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hts221_acpi_match);

अटल स्थिर काष्ठा of_device_id hts221_i2c_of_match[] = अणु
	अणु .compatible = "st,hts221", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hts221_i2c_of_match);

अटल स्थिर काष्ठा i2c_device_id hts221_i2c_id_table[] = अणु
	अणु HTS221_DEV_NAME पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, hts221_i2c_id_table);

अटल काष्ठा i2c_driver hts221_driver = अणु
	.driver = अणु
		.name = "hts221_i2c",
		.pm = &hts221_pm_ops,
		.of_match_table = hts221_i2c_of_match,
		.acpi_match_table = ACPI_PTR(hts221_acpi_match),
	पूर्ण,
	.probe = hts221_i2c_probe,
	.id_table = hts221_i2c_id_table,
पूर्ण;
module_i2c_driver(hts221_driver);

MODULE_AUTHOR("Lorenzo Bianconi <lorenzo.bianconi@st.com>");
MODULE_DESCRIPTION("STMicroelectronics hts221 i2c driver");
MODULE_LICENSE("GPL v2");
