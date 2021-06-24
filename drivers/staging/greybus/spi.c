<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SPI bridge PHY driver.
 *
 * Copyright 2014-2016 Google Inc.
 * Copyright 2014-2016 Linaro Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/greybus.h>

#समावेश "gbphy.h"
#समावेश "spilib.h"

अटल काष्ठा spilib_ops *spilib_ops;

अटल पूर्णांक gb_spi_probe(काष्ठा gbphy_device *gbphy_dev,
			स्थिर काष्ठा gbphy_device_id *id)
अणु
	काष्ठा gb_connection *connection;
	पूर्णांक ret;

	connection = gb_connection_create(gbphy_dev->bundle,
					  le16_to_cpu(gbphy_dev->cport_desc->id),
					  शून्य);
	अगर (IS_ERR(connection))
		वापस PTR_ERR(connection);

	ret = gb_connection_enable(connection);
	अगर (ret)
		जाओ निकास_connection_destroy;

	ret = gb_spilib_master_init(connection, &gbphy_dev->dev, spilib_ops);
	अगर (ret)
		जाओ निकास_connection_disable;

	gb_gbphy_set_data(gbphy_dev, connection);

	gbphy_runसमय_put_स्वतःsuspend(gbphy_dev);
	वापस 0;

निकास_connection_disable:
	gb_connection_disable(connection);
निकास_connection_destroy:
	gb_connection_destroy(connection);

	वापस ret;
पूर्ण

अटल व्योम gb_spi_हटाओ(काष्ठा gbphy_device *gbphy_dev)
अणु
	काष्ठा gb_connection *connection = gb_gbphy_get_data(gbphy_dev);
	पूर्णांक ret;

	ret = gbphy_runसमय_get_sync(gbphy_dev);
	अगर (ret)
		gbphy_runसमय_get_noresume(gbphy_dev);

	gb_spilib_master_निकास(connection);
	gb_connection_disable(connection);
	gb_connection_destroy(connection);
पूर्ण

अटल स्थिर काष्ठा gbphy_device_id gb_spi_id_table[] = अणु
	अणु GBPHY_PROTOCOL(GREYBUS_PROTOCOL_SPI) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(gbphy, gb_spi_id_table);

अटल काष्ठा gbphy_driver spi_driver = अणु
	.name		= "spi",
	.probe		= gb_spi_probe,
	.हटाओ		= gb_spi_हटाओ,
	.id_table	= gb_spi_id_table,
पूर्ण;

module_gbphy_driver(spi_driver);
MODULE_LICENSE("GPL v2");
