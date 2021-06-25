<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016 Broadcom
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश "spi-bcm-qspi.h"

अटल स्थिर काष्ठा of_device_id brcmstb_qspi_of_match[] = अणु
	अणु .compatible = "brcm,spi-brcmstb-qspi" पूर्ण,
	अणु .compatible = "brcm,spi-brcmstb-mspi" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, brcmstb_qspi_of_match);

अटल पूर्णांक brcmstb_qspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस bcm_qspi_probe(pdev, शून्य);
पूर्ण

अटल पूर्णांक brcmstb_qspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस bcm_qspi_हटाओ(pdev);
पूर्ण

अटल काष्ठा platक्रमm_driver brcmstb_qspi_driver = अणु
	.probe			= brcmstb_qspi_probe,
	.हटाओ			= brcmstb_qspi_हटाओ,
	.driver = अणु
		.name		= "brcmstb_qspi",
		.pm		= &bcm_qspi_pm_ops,
		.of_match_table = brcmstb_qspi_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(brcmstb_qspi_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Kamal Dasu");
MODULE_DESCRIPTION("Broadcom SPI driver for settop SoC");
