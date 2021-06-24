<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2007 PA Semi, Inc
 *
 * Author: Egor Martovetsky <egor@pasemi.com>
 * Maपूर्णांकained by: Olof Johansson <olof@lixom.net>
 *
 * Driver क्रम the PWRficient onchip न_अंकD flash पूर्णांकerface
 */

#अघोषित DEBUG

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/पन.स>

#घोषणा LBICTRL_LPCCTL_NR		0x00004000
#घोषणा CLE_PIN_CTL			15
#घोषणा ALE_PIN_CTL			14

अटल अचिन्हित पूर्णांक lpcctl;
अटल काष्ठा mtd_info *pasemi_nand_mtd;
अटल काष्ठा nand_controller controller;
अटल स्थिर अक्षर driver_name[] = "pasemi-nand";

अटल व्योम pasemi_पढ़ो_buf(काष्ठा nand_chip *chip, u_अक्षर *buf, पूर्णांक len)
अणु
	जबतक (len > 0x800) अणु
		स_नकल_fromio(buf, chip->legacy.IO_ADDR_R, 0x800);
		buf += 0x800;
		len -= 0x800;
	पूर्ण
	स_नकल_fromio(buf, chip->legacy.IO_ADDR_R, len);
पूर्ण

अटल व्योम pasemi_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर u_अक्षर *buf,
			     पूर्णांक len)
अणु
	जबतक (len > 0x800) अणु
		स_नकल_toio(chip->legacy.IO_ADDR_R, buf, 0x800);
		buf += 0x800;
		len -= 0x800;
	पूर्ण
	स_नकल_toio(chip->legacy.IO_ADDR_R, buf, len);
पूर्ण

अटल व्योम pasemi_hwcontrol(काष्ठा nand_chip *chip, पूर्णांक cmd,
			     अचिन्हित पूर्णांक ctrl)
अणु
	अगर (cmd == न_अंकD_CMD_NONE)
		वापस;

	अगर (ctrl & न_अंकD_CLE)
		out_8(chip->legacy.IO_ADDR_W + (1 << CLE_PIN_CTL), cmd);
	अन्यथा
		out_8(chip->legacy.IO_ADDR_W + (1 << ALE_PIN_CTL), cmd);

	/* Push out posted ग_लिखोs */
	eieio();
	inl(lpcctl);
पूर्ण

अटल पूर्णांक pasemi_device_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	वापस !!(inl(lpcctl) & LBICTRL_LPCCTL_NR);
पूर्ण

अटल पूर्णांक pasemi_attach_chip(काष्ठा nand_chip *chip)
अणु
	chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;

	अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_UNKNOWN)
		chip->ecc.algo = न_अंकD_ECC_ALGO_HAMMING;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops pasemi_ops = अणु
	.attach_chip = pasemi_attach_chip,
पूर्ण;

अटल पूर्णांक pasemi_nand_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device *dev = &ofdev->dev;
	काष्ठा pci_dev *pdev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा resource res;
	काष्ठा nand_chip *chip;
	पूर्णांक err = 0;

	err = of_address_to_resource(np, 0, &res);

	अगर (err)
		वापस -EINVAL;

	/* We only support one device at the moment */
	अगर (pasemi_nand_mtd)
		वापस -ENODEV;

	dev_dbg(dev, "pasemi_nand at %pR\n", &res);

	/* Allocate memory क्रम MTD device काष्ठाure and निजी data */
	chip = kzalloc(माप(काष्ठा nand_chip), GFP_KERNEL);
	अगर (!chip) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	controller.ops = &pasemi_ops;
	nand_controller_init(&controller);
	chip->controller = &controller;

	pasemi_nand_mtd = nand_to_mtd(chip);

	/* Link the निजी data with the MTD काष्ठाure */
	pasemi_nand_mtd->dev.parent = dev;

	chip->legacy.IO_ADDR_R = of_iomap(np, 0);
	chip->legacy.IO_ADDR_W = chip->legacy.IO_ADDR_R;

	अगर (!chip->legacy.IO_ADDR_R) अणु
		err = -EIO;
		जाओ out_mtd;
	पूर्ण

	pdev = pci_get_device(PCI_VENDOR_ID_PASEMI, 0xa008, शून्य);
	अगर (!pdev) अणु
		err = -ENODEV;
		जाओ out_ior;
	पूर्ण

	lpcctl = pci_resource_start(pdev, 0);
	pci_dev_put(pdev);

	अगर (!request_region(lpcctl, 4, driver_name)) अणु
		err = -EBUSY;
		जाओ out_ior;
	पूर्ण

	chip->legacy.cmd_ctrl = pasemi_hwcontrol;
	chip->legacy.dev_पढ़ोy = pasemi_device_पढ़ोy;
	chip->legacy.पढ़ो_buf = pasemi_पढ़ो_buf;
	chip->legacy.ग_लिखो_buf = pasemi_ग_लिखो_buf;
	chip->legacy.chip_delay = 0;

	/* Enable the following क्रम a flash based bad block table */
	chip->bbt_options = न_अंकD_BBT_USE_FLASH;

	/* Scan to find existence of the device */
	err = nand_scan(chip, 1);
	अगर (err)
		जाओ out_lpc;

	अगर (mtd_device_रेजिस्टर(pasemi_nand_mtd, शून्य, 0)) अणु
		dev_err(dev, "Unable to register MTD device\n");
		err = -ENODEV;
		जाओ out_cleanup_nand;
	पूर्ण

	dev_info(dev, "PA Semi NAND flash at %pR, control at I/O %x\n", &res,
		 lpcctl);

	वापस 0;

 out_cleanup_nand:
	nand_cleanup(chip);
 out_lpc:
	release_region(lpcctl, 4);
 out_ior:
	iounmap(chip->legacy.IO_ADDR_R);
 out_mtd:
	kमुक्त(chip);
 out:
	वापस err;
पूर्ण

अटल पूर्णांक pasemi_nand_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा nand_chip *chip;
	पूर्णांक ret;

	अगर (!pasemi_nand_mtd)
		वापस 0;

	chip = mtd_to_nand(pasemi_nand_mtd);

	/* Release resources, unरेजिस्टर device */
	ret = mtd_device_unरेजिस्टर(pasemi_nand_mtd);
	WARN_ON(ret);
	nand_cleanup(chip);

	release_region(lpcctl, 4);

	iounmap(chip->legacy.IO_ADDR_R);

	/* Free the MTD device काष्ठाure */
	kमुक्त(chip);

	pasemi_nand_mtd = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pasemi_nand_match[] =
अणु
	अणु
		.compatible   = "pasemi,localbus-nand",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, pasemi_nand_match);

अटल काष्ठा platक्रमm_driver pasemi_nand_driver =
अणु
	.driver = अणु
		.name = driver_name,
		.of_match_table = pasemi_nand_match,
	पूर्ण,
	.probe		= pasemi_nand_probe,
	.हटाओ		= pasemi_nand_हटाओ,
पूर्ण;

module_platक्रमm_driver(pasemi_nand_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Egor Martovetsky <egor@pasemi.com>");
MODULE_DESCRIPTION("NAND flash interface driver for PA Semi PWRficient");
