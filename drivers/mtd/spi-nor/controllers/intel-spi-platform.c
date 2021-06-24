<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel PCH/PCU SPI flash platक्रमm driver.
 *
 * Copyright (C) 2016, Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "intel-spi.h"

अटल पूर्णांक पूर्णांकel_spi_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_spi_boardinfo *info;
	काष्ठा पूर्णांकel_spi *ispi;
	काष्ठा resource *mem;

	info = dev_get_platdata(&pdev->dev);
	अगर (!info)
		वापस -EINVAL;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ispi = पूर्णांकel_spi_probe(&pdev->dev, mem, info);
	अगर (IS_ERR(ispi))
		वापस PTR_ERR(ispi);

	platक्रमm_set_drvdata(pdev, ispi);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_spi_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_spi *ispi = platक्रमm_get_drvdata(pdev);

	वापस पूर्णांकel_spi_हटाओ(ispi);
पूर्ण

अटल काष्ठा platक्रमm_driver पूर्णांकel_spi_platक्रमm_driver = अणु
	.probe = पूर्णांकel_spi_platक्रमm_probe,
	.हटाओ = पूर्णांकel_spi_platक्रमm_हटाओ,
	.driver = अणु
		.name = "intel-spi",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(पूर्णांकel_spi_platक्रमm_driver);

MODULE_DESCRIPTION("Intel PCH/PCU SPI flash platform driver");
MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:intel-spi");
