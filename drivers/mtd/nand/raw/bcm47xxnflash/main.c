<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * BCM47XX न_अंकD flash driver
 *
 * Copyright (C) 2012 Rafaध Miधecki <zajec5@gmail.com>
 */

#समावेश "bcm47xxnflash.h"

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bcma/bcma.h>

MODULE_DESCRIPTION("NAND flash driver for BCMA bus");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rafaध Miधecki");

अटल स्थिर अक्षर *probes[] = अणु "bcm47xxpart", शून्य पूर्ण;

अटल पूर्णांक bcm47xxnflash_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcma_nflash *nflash = dev_get_platdata(&pdev->dev);
	काष्ठा bcm47xxnflash *b47n;
	काष्ठा mtd_info *mtd;
	पूर्णांक err = 0;

	b47n = devm_kzalloc(&pdev->dev, माप(*b47n), GFP_KERNEL);
	अगर (!b47n)
		वापस -ENOMEM;

	nand_set_controller_data(&b47n->nand_chip, b47n);
	mtd = nand_to_mtd(&b47n->nand_chip);
	mtd->dev.parent = &pdev->dev;
	b47n->cc = container_of(nflash, काष्ठा bcma_drv_cc, nflash);

	अगर (b47n->cc->core->bus->chipinfo.id == BCMA_CHIP_ID_BCM4706) अणु
		err = bcm47xxnflash_ops_bcm4706_init(b47n);
	पूर्ण अन्यथा अणु
		pr_err("Device not supported\n");
		err = -ENOTSUPP;
	पूर्ण
	अगर (err) अणु
		pr_err("Initialization failed: %d\n", err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, b47n);

	err = mtd_device_parse_रेजिस्टर(mtd, probes, शून्य, शून्य, 0);
	अगर (err) अणु
		pr_err("Failed to register MTD device: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm47xxnflash_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm47xxnflash *nflash = platक्रमm_get_drvdata(pdev);
	काष्ठा nand_chip *chip = &nflash->nand_chip;
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver bcm47xxnflash_driver = अणु
	.probe	= bcm47xxnflash_probe,
	.हटाओ = bcm47xxnflash_हटाओ,
	.driver = अणु
		.name = "bcma_nflash",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(bcm47xxnflash_driver);
