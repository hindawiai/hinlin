<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2004 Riअक्षरd Purdie
 *  Copyright (C) 2008 Dmitry Baryshkov
 *
 *  Based on Sharp's न_अंकD driver sharp_sl.c
 */

#समावेश <linux/genhd.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/sharpsl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>

काष्ठा sharpsl_nand अणु
	काष्ठा nand_controller	controller;
	काष्ठा nand_chip	chip;

	व्योम __iomem		*io;
पूर्ण;

अटल अंतरभूत काष्ठा sharpsl_nand *mtd_to_sharpsl(काष्ठा mtd_info *mtd)
अणु
	वापस container_of(mtd_to_nand(mtd), काष्ठा sharpsl_nand, chip);
पूर्ण

/* रेजिस्टर offset */
#घोषणा ECCLPLB		0x00	/* line parity 7 - 0 bit */
#घोषणा ECCLPUB		0x04	/* line parity 15 - 8 bit */
#घोषणा ECCCP		0x08	/* column parity 5 - 0 bit */
#घोषणा ECCCNTR		0x0C	/* ECC byte counter */
#घोषणा ECCCLRR		0x10	/* cleare ECC */
#घोषणा FLASHIO		0x14	/* Flash I/O */
#घोषणा FLASHCTL	0x18	/* Flash Control */

/* Flash control bit */
#घोषणा FLRYBY		(1 << 5)
#घोषणा FLCE1		(1 << 4)
#घोषणा FLWP		(1 << 3)
#घोषणा FLALE		(1 << 2)
#घोषणा FLCLE		(1 << 1)
#घोषणा FLCE0		(1 << 0)

/*
 *	hardware specअगरic access to control-lines
 *	ctrl:
 *	न_अंकD_CNE: bit 0 -> ! bit 0 & 4
 *	न_अंकD_CLE: bit 1 -> bit 1
 *	न_अंकD_ALE: bit 2 -> bit 2
 *
 */
अटल व्योम sharpsl_nand_hwcontrol(काष्ठा nand_chip *chip, पूर्णांक cmd,
				   अचिन्हित पूर्णांक ctrl)
अणु
	काष्ठा sharpsl_nand *sharpsl = mtd_to_sharpsl(nand_to_mtd(chip));

	अगर (ctrl & न_अंकD_CTRL_CHANGE) अणु
		अचिन्हित अक्षर bits = ctrl & 0x07;

		bits |= (ctrl & 0x01) << 4;

		bits ^= 0x11;

		ग_लिखोb((पढ़ोb(sharpsl->io + FLASHCTL) & ~0x17) | bits, sharpsl->io + FLASHCTL);
	पूर्ण

	अगर (cmd != न_अंकD_CMD_NONE)
		ग_लिखोb(cmd, chip->legacy.IO_ADDR_W);
पूर्ण

अटल पूर्णांक sharpsl_nand_dev_पढ़ोy(काष्ठा nand_chip *chip)
अणु
	काष्ठा sharpsl_nand *sharpsl = mtd_to_sharpsl(nand_to_mtd(chip));
	वापस !((पढ़ोb(sharpsl->io + FLASHCTL) & FLRYBY) == 0);
पूर्ण

अटल व्योम sharpsl_nand_enable_hwecc(काष्ठा nand_chip *chip, पूर्णांक mode)
अणु
	काष्ठा sharpsl_nand *sharpsl = mtd_to_sharpsl(nand_to_mtd(chip));
	ग_लिखोb(0, sharpsl->io + ECCCLRR);
पूर्ण

अटल पूर्णांक sharpsl_nand_calculate_ecc(काष्ठा nand_chip *chip,
				      स्थिर u_अक्षर * dat, u_अक्षर * ecc_code)
अणु
	काष्ठा sharpsl_nand *sharpsl = mtd_to_sharpsl(nand_to_mtd(chip));
	ecc_code[0] = ~पढ़ोb(sharpsl->io + ECCLPUB);
	ecc_code[1] = ~पढ़ोb(sharpsl->io + ECCLPLB);
	ecc_code[2] = (~पढ़ोb(sharpsl->io + ECCCP) << 2) | 0x03;
	वापस पढ़ोb(sharpsl->io + ECCCNTR) != 0;
पूर्ण

अटल पूर्णांक sharpsl_nand_correct_ecc(काष्ठा nand_chip *chip,
				    अचिन्हित अक्षर *buf,
				    अचिन्हित अक्षर *पढ़ो_ecc,
				    अचिन्हित अक्षर *calc_ecc)
अणु
	वापस ecc_sw_hamming_correct(buf, पढ़ो_ecc, calc_ecc,
				      chip->ecc.size, false);
पूर्ण

अटल पूर्णांक sharpsl_attach_chip(काष्ठा nand_chip *chip)
अणु
	अगर (chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
		वापस 0;

	chip->ecc.size = 256;
	chip->ecc.bytes = 3;
	chip->ecc.strength = 1;
	chip->ecc.hwctl = sharpsl_nand_enable_hwecc;
	chip->ecc.calculate = sharpsl_nand_calculate_ecc;
	chip->ecc.correct = sharpsl_nand_correct_ecc;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops sharpsl_ops = अणु
	.attach_chip = sharpsl_attach_chip,
पूर्ण;

/*
 * Main initialization routine
 */
अटल पूर्णांक sharpsl_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nand_chip *this;
	काष्ठा mtd_info *mtd;
	काष्ठा resource *r;
	पूर्णांक err = 0;
	काष्ठा sharpsl_nand *sharpsl;
	काष्ठा sharpsl_nand_platक्रमm_data *data = dev_get_platdata(&pdev->dev);

	अगर (!data) अणु
		dev_err(&pdev->dev, "no platform data!\n");
		वापस -EINVAL;
	पूर्ण

	/* Allocate memory क्रम MTD device काष्ठाure and निजी data */
	sharpsl = kzalloc(माप(काष्ठा sharpsl_nand), GFP_KERNEL);
	अगर (!sharpsl)
		वापस -ENOMEM;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(&pdev->dev, "no io memory resource defined!\n");
		err = -ENODEV;
		जाओ err_get_res;
	पूर्ण

	/* map physical address */
	sharpsl->io = ioremap(r->start, resource_size(r));
	अगर (!sharpsl->io) अणु
		dev_err(&pdev->dev, "ioremap to access Sharp SL NAND chip failed\n");
		err = -EIO;
		जाओ err_ioremap;
	पूर्ण

	/* Get poपूर्णांकer to निजी data */
	this = (काष्ठा nand_chip *)(&sharpsl->chip);

	nand_controller_init(&sharpsl->controller);
	sharpsl->controller.ops = &sharpsl_ops;
	this->controller = &sharpsl->controller;

	/* Link the निजी data with the MTD काष्ठाure */
	mtd = nand_to_mtd(this);
	mtd->dev.parent = &pdev->dev;
	mtd_set_ooblayout(mtd, data->ecc_layout);

	platक्रमm_set_drvdata(pdev, sharpsl);

	/*
	 * PXA initialize
	 */
	ग_लिखोb(पढ़ोb(sharpsl->io + FLASHCTL) | FLWP, sharpsl->io + FLASHCTL);

	/* Set address of न_अंकD IO lines */
	this->legacy.IO_ADDR_R = sharpsl->io + FLASHIO;
	this->legacy.IO_ADDR_W = sharpsl->io + FLASHIO;
	/* Set address of hardware control function */
	this->legacy.cmd_ctrl = sharpsl_nand_hwcontrol;
	this->legacy.dev_पढ़ोy = sharpsl_nand_dev_पढ़ोy;
	/* 15 us command delay समय */
	this->legacy.chip_delay = 15;
	this->badblock_pattern = data->badblock_pattern;

	/* Scan to find existence of the device */
	err = nand_scan(this, 1);
	अगर (err)
		जाओ err_scan;

	/* Register the partitions */
	mtd->name = "sharpsl-nand";

	err = mtd_device_parse_रेजिस्टर(mtd, data->part_parsers, शून्य,
					data->partitions, data->nr_partitions);
	अगर (err)
		जाओ err_add;

	/* Return happy */
	वापस 0;

err_add:
	nand_cleanup(this);

err_scan:
	iounmap(sharpsl->io);
err_ioremap:
err_get_res:
	kमुक्त(sharpsl);
	वापस err;
पूर्ण

/*
 * Clean up routine
 */
अटल पूर्णांक sharpsl_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sharpsl_nand *sharpsl = platक्रमm_get_drvdata(pdev);
	काष्ठा nand_chip *chip = &sharpsl->chip;
	पूर्णांक ret;

	/* Unरेजिस्टर device */
	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);

	/* Release resources */
	nand_cleanup(chip);

	iounmap(sharpsl->io);

	/* Free the driver's काष्ठाure */
	kमुक्त(sharpsl);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sharpsl_nand_driver = अणु
	.driver = अणु
		.name	= "sharpsl-nand",
	पूर्ण,
	.probe		= sharpsl_nand_probe,
	.हटाओ		= sharpsl_nand_हटाओ,
पूर्ण;

module_platक्रमm_driver(sharpsl_nand_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Richard Purdie <rpurdie@rpsys.net>");
MODULE_DESCRIPTION("Device specific logic for NAND flash on Sharp SL-C7xx Series");
