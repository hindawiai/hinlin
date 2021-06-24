<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic न_अंकD driver
 *
 * Author: Vitaly Wool <vitalywool@gmail.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/platnand.h>

काष्ठा plat_nand_data अणु
	काष्ठा nand_controller	controller;
	काष्ठा nand_chip	chip;
	व्योम __iomem		*io_base;
पूर्ण;

अटल पूर्णांक plat_nand_attach_chip(काष्ठा nand_chip *chip)
अणु
	chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;

	अगर (chip->ecc.algo == न_अंकD_ECC_ALGO_UNKNOWN)
		chip->ecc.algo = न_अंकD_ECC_ALGO_HAMMING;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops plat_nand_ops = अणु
	.attach_chip = plat_nand_attach_chip,
पूर्ण;

/*
 * Probe क्रम the न_अंकD device.
 */
अटल पूर्णांक plat_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platक्रमm_nand_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा plat_nand_data *data;
	काष्ठा mtd_info *mtd;
	काष्ठा resource *res;
	स्थिर अक्षर **part_types;
	पूर्णांक err = 0;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "platform_nand_data is missing\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->chip.nr_chips < 1) अणु
		dev_err(&pdev->dev, "invalid number of chips specified\n");
		वापस -EINVAL;
	पूर्ण

	/* Allocate memory क्रम the device काष्ठाure (and zero it) */
	data = devm_kzalloc(&pdev->dev, माप(काष्ठा plat_nand_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->controller.ops = &plat_nand_ops;
	nand_controller_init(&data->controller);
	data->chip.controller = &data->controller;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	data->io_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(data->io_base))
		वापस PTR_ERR(data->io_base);

	nand_set_flash_node(&data->chip, pdev->dev.of_node);
	mtd = nand_to_mtd(&data->chip);
	mtd->dev.parent = &pdev->dev;

	data->chip.legacy.IO_ADDR_R = data->io_base;
	data->chip.legacy.IO_ADDR_W = data->io_base;
	data->chip.legacy.cmd_ctrl = pdata->ctrl.cmd_ctrl;
	data->chip.legacy.dev_पढ़ोy = pdata->ctrl.dev_पढ़ोy;
	data->chip.legacy.select_chip = pdata->ctrl.select_chip;
	data->chip.legacy.ग_लिखो_buf = pdata->ctrl.ग_लिखो_buf;
	data->chip.legacy.पढ़ो_buf = pdata->ctrl.पढ़ो_buf;
	data->chip.legacy.chip_delay = pdata->chip.chip_delay;
	data->chip.options |= pdata->chip.options;
	data->chip.bbt_options |= pdata->chip.bbt_options;

	platक्रमm_set_drvdata(pdev, data);

	/* Handle any platक्रमm specअगरic setup */
	अगर (pdata->ctrl.probe) अणु
		err = pdata->ctrl.probe(pdev);
		अगर (err)
			जाओ out;
	पूर्ण

	/* Scan to find existence of the device */
	err = nand_scan(&data->chip, pdata->chip.nr_chips);
	अगर (err)
		जाओ out;

	part_types = pdata->chip.part_probe_types;

	err = mtd_device_parse_रेजिस्टर(mtd, part_types, शून्य,
					pdata->chip.partitions,
					pdata->chip.nr_partitions);

	अगर (!err)
		वापस err;

	nand_cleanup(&data->chip);
out:
	अगर (pdata->ctrl.हटाओ)
		pdata->ctrl.हटाओ(pdev);
	वापस err;
पूर्ण

/*
 * Remove a न_अंकD device.
 */
अटल पूर्णांक plat_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_nand_data *data = platक्रमm_get_drvdata(pdev);
	काष्ठा platक्रमm_nand_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा nand_chip *chip = &data->chip;
	पूर्णांक ret;

	ret = mtd_device_unरेजिस्टर(nand_to_mtd(chip));
	WARN_ON(ret);
	nand_cleanup(chip);
	अगर (pdata->ctrl.हटाओ)
		pdata->ctrl.हटाओ(pdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id plat_nand_match[] = अणु
	अणु .compatible = "gen_nand" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, plat_nand_match);

अटल काष्ठा platक्रमm_driver plat_nand_driver = अणु
	.probe	= plat_nand_probe,
	.हटाओ	= plat_nand_हटाओ,
	.driver	= अणु
		.name		= "gen_nand",
		.of_match_table = plat_nand_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(plat_nand_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vitaly Wool");
MODULE_DESCRIPTION("Simple generic NAND driver");
MODULE_ALIAS("platform:gen_nand");
