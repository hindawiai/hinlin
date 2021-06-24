<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2015 Broadcom Corporation
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "brcmnand.h"

अटल स्थिर काष्ठा of_device_id brcmstb_nand_of_match[] = अणु
	अणु .compatible = "brcm,brcmnand" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, brcmstb_nand_of_match);

अटल पूर्णांक brcmstb_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस brcmnand_probe(pdev, शून्य);
पूर्ण

अटल काष्ठा platक्रमm_driver brcmstb_nand_driver = अणु
	.probe			= brcmstb_nand_probe,
	.हटाओ			= brcmnand_हटाओ,
	.driver = अणु
		.name		= "brcmstb_nand",
		.pm		= &brcmnand_pm_ops,
		.of_match_table = brcmstb_nand_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(brcmstb_nand_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Brian Norris");
MODULE_DESCRIPTION("NAND driver for Broadcom STB chips");
