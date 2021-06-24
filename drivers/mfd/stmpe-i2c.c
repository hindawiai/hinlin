<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ST Microelectronics MFD: sपंचांगpe's i2c client specअगरic driver
 *
 * Copyright (C) ST-Ericsson SA 2010
 * Copyright (C) ST Microelectronics SA 2011
 *
 * Author: Rabin Vincent <rabin.vincent@stericsson.com> क्रम ST-Ericsson
 * Author: Viresh Kumar <vireshk@kernel.org> क्रम ST Microelectronics
 */

#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/of_device.h>
#समावेश "stmpe.h"

अटल पूर्णांक i2c_reg_पढ़ो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg)
अणु
	काष्ठा i2c_client *i2c = sपंचांगpe->client;

	वापस i2c_smbus_पढ़ो_byte_data(i2c, reg);
पूर्ण

अटल पूर्णांक i2c_reg_ग_लिखो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 val)
अणु
	काष्ठा i2c_client *i2c = sपंचांगpe->client;

	वापस i2c_smbus_ग_लिखो_byte_data(i2c, reg, val);
पूर्ण

अटल पूर्णांक i2c_block_पढ़ो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 length, u8 *values)
अणु
	काष्ठा i2c_client *i2c = sपंचांगpe->client;

	वापस i2c_smbus_पढ़ो_i2c_block_data(i2c, reg, length, values);
पूर्ण

अटल पूर्णांक i2c_block_ग_लिखो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 length,
		स्थिर u8 *values)
अणु
	काष्ठा i2c_client *i2c = sपंचांगpe->client;

	वापस i2c_smbus_ग_लिखो_i2c_block_data(i2c, reg, length, values);
पूर्ण

अटल काष्ठा sपंचांगpe_client_info i2c_ci = अणु
	.पढ़ो_byte = i2c_reg_पढ़ो,
	.ग_लिखो_byte = i2c_reg_ग_लिखो,
	.पढ़ो_block = i2c_block_पढ़ो,
	.ग_लिखो_block = i2c_block_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांगpe_of_match[] = अणु
	अणु .compatible = "st,stmpe610", .data = (व्योम *)STMPE610, पूर्ण,
	अणु .compatible = "st,stmpe801", .data = (व्योम *)STMPE801, पूर्ण,
	अणु .compatible = "st,stmpe811", .data = (व्योम *)STMPE811, पूर्ण,
	अणु .compatible = "st,stmpe1600", .data = (व्योम *)STMPE1600, पूर्ण,
	अणु .compatible = "st,stmpe1601", .data = (व्योम *)STMPE1601, पूर्ण,
	अणु .compatible = "st,stmpe1801", .data = (व्योम *)STMPE1801, पूर्ण,
	अणु .compatible = "st,stmpe2401", .data = (व्योम *)STMPE2401, पूर्ण,
	अणु .compatible = "st,stmpe2403", .data = (व्योम *)STMPE2403, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांगpe_of_match);

अटल पूर्णांक
sपंचांगpe_i2c_probe(काष्ठा i2c_client *i2c, स्थिर काष्ठा i2c_device_id *id)
अणु
	क्रमागत sपंचांगpe_partnum partnum;
	स्थिर काष्ठा of_device_id *of_id;

	i2c_ci.data = (व्योम *)id;
	i2c_ci.irq = i2c->irq;
	i2c_ci.client = i2c;
	i2c_ci.dev = &i2c->dev;

	of_id = of_match_device(sपंचांगpe_of_match, &i2c->dev);
	अगर (!of_id) अणु
		/*
		 * This happens when the I2C ID matches the node name
		 * but no real compatible string has been given.
		 */
		dev_info(&i2c->dev, "matching on node name, compatible is preferred\n");
		partnum = id->driver_data;
	पूर्ण अन्यथा
		partnum = (क्रमागत sपंचांगpe_partnum)of_id->data;

	वापस sपंचांगpe_probe(&i2c_ci, partnum);
पूर्ण

अटल पूर्णांक sपंचांगpe_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा sपंचांगpe *sपंचांगpe = dev_get_drvdata(&i2c->dev);

	वापस sपंचांगpe_हटाओ(sपंचांगpe);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id sपंचांगpe_i2c_id[] = अणु
	अणु "stmpe610", STMPE610 पूर्ण,
	अणु "stmpe801", STMPE801 पूर्ण,
	अणु "stmpe811", STMPE811 पूर्ण,
	अणु "stmpe1600", STMPE1600 पूर्ण,
	अणु "stmpe1601", STMPE1601 पूर्ण,
	अणु "stmpe1801", STMPE1801 पूर्ण,
	अणु "stmpe2401", STMPE2401 पूर्ण,
	अणु "stmpe2403", STMPE2403 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sपंचांगpe_id);

अटल काष्ठा i2c_driver sपंचांगpe_i2c_driver = अणु
	.driver = अणु
		.name = "stmpe-i2c",
#अगर_घोषित CONFIG_PM
		.pm = &sपंचांगpe_dev_pm_ops,
#पूर्ण_अगर
		.of_match_table = sपंचांगpe_of_match,
	पूर्ण,
	.probe		= sपंचांगpe_i2c_probe,
	.हटाओ		= sपंचांगpe_i2c_हटाओ,
	.id_table	= sपंचांगpe_i2c_id,
पूर्ण;

अटल पूर्णांक __init sपंचांगpe_init(व्योम)
अणु
	वापस i2c_add_driver(&sपंचांगpe_i2c_driver);
पूर्ण
subsys_initcall(sपंचांगpe_init);

अटल व्योम __निकास sपंचांगpe_निकास(व्योम)
अणु
	i2c_del_driver(&sपंचांगpe_i2c_driver);
पूर्ण
module_निकास(sपंचांगpe_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("STMPE MFD I2C Interface Driver");
MODULE_AUTHOR("Rabin Vincent <rabin.vincent@stericsson.com>");
