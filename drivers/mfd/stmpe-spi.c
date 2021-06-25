<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ST Microelectronics MFD: sपंचांगpe's spi client specअगरic driver
 *
 * Copyright (C) ST Microelectronics SA 2011
 *
 * Author: Viresh Kumar <vireshk@kernel.org> क्रम ST Microelectronics
 */

#समावेश <linux/spi/spi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/types.h>
#समावेश "stmpe.h"

#घोषणा READ_CMD	(1 << 7)

अटल पूर्णांक spi_reg_पढ़ो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg)
अणु
	काष्ठा spi_device *spi = sपंचांगpe->client;
	पूर्णांक status = spi_w8r16(spi, reg | READ_CMD);

	वापस (status < 0) ? status : status >> 8;
पूर्ण

अटल पूर्णांक spi_reg_ग_लिखो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 val)
अणु
	काष्ठा spi_device *spi = sपंचांगpe->client;
	u16 cmd = (val << 8) | reg;

	वापस spi_ग_लिखो(spi, (स्थिर u8 *)&cmd, 2);
पूर्ण

अटल पूर्णांक spi_block_पढ़ो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 length, u8 *values)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < length; i++) अणु
		ret = spi_reg_पढ़ो(sपंचांगpe, reg + i);
		अगर (ret < 0)
			वापस ret;
		*(values + i) = ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spi_block_ग_लिखो(काष्ठा sपंचांगpe *sपंचांगpe, u8 reg, u8 length,
		स्थिर u8 *values)
अणु
	पूर्णांक ret = 0, i;

	क्रम (i = length; i > 0; i--, reg++) अणु
		ret = spi_reg_ग_लिखो(sपंचांगpe, reg, *(values + i - 1));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम spi_init(काष्ठा sपंचांगpe *sपंचांगpe)
अणु
	काष्ठा spi_device *spi = sपंचांगpe->client;

	spi->bits_per_word = 8;

	/* This रेजिस्टर is only present क्रम sपंचांगpe811 */
	अगर (sपंचांगpe->variant->id_val == 0x0811)
		spi_reg_ग_लिखो(sपंचांगpe, STMPE811_REG_SPI_CFG, spi->mode);

	अगर (spi_setup(spi) < 0)
		dev_dbg(&spi->dev, "spi_setup failed\n");
पूर्ण

अटल काष्ठा sपंचांगpe_client_info spi_ci = अणु
	.पढ़ो_byte = spi_reg_पढ़ो,
	.ग_लिखो_byte = spi_reg_ग_लिखो,
	.पढ़ो_block = spi_block_पढ़ो,
	.ग_लिखो_block = spi_block_ग_लिखो,
	.init = spi_init,
पूर्ण;

अटल पूर्णांक
sपंचांगpe_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);

	/* करोn't exceed max specअगरied rate - 1MHz - Limitation of STMPE */
	अगर (spi->max_speed_hz > 1000000) अणु
		dev_dbg(&spi->dev, "f(sample) %d KHz?\n",
				(spi->max_speed_hz/1000));
		वापस -EINVAL;
	पूर्ण

	spi_ci.irq = spi->irq;
	spi_ci.client = spi;
	spi_ci.dev = &spi->dev;

	वापस sपंचांगpe_probe(&spi_ci, id->driver_data);
पूर्ण

अटल पूर्णांक sपंचांगpe_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा sपंचांगpe *sपंचांगpe = spi_get_drvdata(spi);

	वापस sपंचांगpe_हटाओ(sपंचांगpe);
पूर्ण

अटल स्थिर काष्ठा of_device_id sपंचांगpe_spi_of_match[] = अणु
	अणु .compatible = "st,stmpe610", पूर्ण,
	अणु .compatible = "st,stmpe801", पूर्ण,
	अणु .compatible = "st,stmpe811", पूर्ण,
	अणु .compatible = "st,stmpe1601", पूर्ण,
	अणु .compatible = "st,stmpe2401", पूर्ण,
	अणु .compatible = "st,stmpe2403", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांगpe_spi_of_match);

अटल स्थिर काष्ठा spi_device_id sपंचांगpe_spi_id[] = अणु
	अणु "stmpe610", STMPE610 पूर्ण,
	अणु "stmpe801", STMPE801 पूर्ण,
	अणु "stmpe811", STMPE811 पूर्ण,
	अणु "stmpe1601", STMPE1601 पूर्ण,
	अणु "stmpe2401", STMPE2401 पूर्ण,
	अणु "stmpe2403", STMPE2403 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, sपंचांगpe_id);

अटल काष्ठा spi_driver sपंचांगpe_spi_driver = अणु
	.driver = अणु
		.name	= "stmpe-spi",
		.of_match_table = of_match_ptr(sपंचांगpe_spi_of_match),
#अगर_घोषित CONFIG_PM
		.pm	= &sपंचांगpe_dev_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.probe		= sपंचांगpe_spi_probe,
	.हटाओ		= sपंचांगpe_spi_हटाओ,
	.id_table	= sपंचांगpe_spi_id,
पूर्ण;

अटल पूर्णांक __init sपंचांगpe_init(व्योम)
अणु
	वापस spi_रेजिस्टर_driver(&sपंचांगpe_spi_driver);
पूर्ण
subsys_initcall(sपंचांगpe_init);

अटल व्योम __निकास sपंचांगpe_निकास(व्योम)
अणु
	spi_unरेजिस्टर_driver(&sपंचांगpe_spi_driver);
पूर्ण
module_निकास(sपंचांगpe_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("STMPE MFD SPI Interface Driver");
MODULE_AUTHOR("Viresh Kumar <vireshk@kernel.org>");
