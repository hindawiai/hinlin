<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Oxक्रमd Semiconductor OXNAS न_अंकD driver

 * Copyright (C) 2016 Neil Armstrong <narmstrong@baylibre.com>
 * Heavily based on plat_nand.c :
 * Author: Vitaly Wool <vitalywool@gmail.com>
 * Copyright (C) 2013 Ma Haijun <mahaijuns@gmail.com>
 * Copyright (C) 2012 John Crispin <blogic@खोलोwrt.org>
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/reset.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/of.h>

/* Nand commands */
#घोषणा OXNAS_न_अंकD_CMD_ALE		BIT(18)
#घोषणा OXNAS_न_अंकD_CMD_CLE		BIT(19)

#घोषणा OXNAS_न_अंकD_MAX_CHIPS	1

काष्ठा oxnas_nand_ctrl अणु
	काष्ठा nand_controller base;
	व्योम __iomem *io_base;
	काष्ठा clk *clk;
	काष्ठा nand_chip *chips[OXNAS_न_अंकD_MAX_CHIPS];
	अचिन्हित पूर्णांक nchips;
पूर्ण;

अटल uपूर्णांक8_t oxnas_nand_पढ़ो_byte(काष्ठा nand_chip *chip)
अणु
	काष्ठा oxnas_nand_ctrl *oxnas = nand_get_controller_data(chip);

	वापस पढ़ोb(oxnas->io_base);
पूर्ण

अटल व्योम oxnas_nand_पढ़ो_buf(काष्ठा nand_chip *chip, u8 *buf, पूर्णांक len)
अणु
	काष्ठा oxnas_nand_ctrl *oxnas = nand_get_controller_data(chip);

	ioपढ़ो8_rep(oxnas->io_base, buf, len);
पूर्ण

अटल व्योम oxnas_nand_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर u8 *buf,
				 पूर्णांक len)
अणु
	काष्ठा oxnas_nand_ctrl *oxnas = nand_get_controller_data(chip);

	ioग_लिखो8_rep(oxnas->io_base, buf, len);
पूर्ण

/* Single CS command control */
अटल व्योम oxnas_nand_cmd_ctrl(काष्ठा nand_chip *chip, पूर्णांक cmd,
				अचिन्हित पूर्णांक ctrl)
अणु
	काष्ठा oxnas_nand_ctrl *oxnas = nand_get_controller_data(chip);

	अगर (ctrl & न_अंकD_CLE)
		ग_लिखोb(cmd, oxnas->io_base + OXNAS_न_अंकD_CMD_CLE);
	अन्यथा अगर (ctrl & न_अंकD_ALE)
		ग_लिखोb(cmd, oxnas->io_base + OXNAS_न_अंकD_CMD_ALE);
पूर्ण

/*
 * Probe क्रम the न_अंकD device.
 */
अटल पूर्णांक oxnas_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *nand_np;
	काष्ठा oxnas_nand_ctrl *oxnas;
	काष्ठा nand_chip *chip;
	काष्ठा mtd_info *mtd;
	काष्ठा resource *res;
	पूर्णांक count = 0;
	पूर्णांक err = 0;
	पूर्णांक i;

	/* Allocate memory क्रम the device काष्ठाure (and zero it) */
	oxnas = devm_kzalloc(&pdev->dev, माप(*oxnas),
			     GFP_KERNEL);
	अगर (!oxnas)
		वापस -ENOMEM;

	nand_controller_init(&oxnas->base);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	oxnas->io_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(oxnas->io_base))
		वापस PTR_ERR(oxnas->io_base);

	oxnas->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(oxnas->clk))
		oxnas->clk = शून्य;

	/* Only a single chip node is supported */
	count = of_get_child_count(np);
	अगर (count > 1)
		वापस -EINVAL;

	err = clk_prepare_enable(oxnas->clk);
	अगर (err)
		वापस err;

	device_reset_optional(&pdev->dev);

	क्रम_each_child_of_node(np, nand_np) अणु
		chip = devm_kzalloc(&pdev->dev, माप(काष्ठा nand_chip),
				    GFP_KERNEL);
		अगर (!chip) अणु
			err = -ENOMEM;
			जाओ err_release_child;
		पूर्ण

		chip->controller = &oxnas->base;

		nand_set_flash_node(chip, nand_np);
		nand_set_controller_data(chip, oxnas);

		mtd = nand_to_mtd(chip);
		mtd->dev.parent = &pdev->dev;
		mtd->priv = chip;

		chip->legacy.cmd_ctrl = oxnas_nand_cmd_ctrl;
		chip->legacy.पढ़ो_buf = oxnas_nand_पढ़ो_buf;
		chip->legacy.पढ़ो_byte = oxnas_nand_पढ़ो_byte;
		chip->legacy.ग_लिखो_buf = oxnas_nand_ग_लिखो_buf;
		chip->legacy.chip_delay = 30;

		/* Scan to find existence of the device */
		err = nand_scan(chip, 1);
		अगर (err)
			जाओ err_release_child;

		err = mtd_device_रेजिस्टर(mtd, शून्य, 0);
		अगर (err)
			जाओ err_cleanup_nand;

		oxnas->chips[oxnas->nchips++] = chip;
	पूर्ण

	/* Exit अगर no chips found */
	अगर (!oxnas->nchips) अणु
		err = -ENODEV;
		जाओ err_clk_unprepare;
	पूर्ण

	platक्रमm_set_drvdata(pdev, oxnas);

	वापस 0;

err_cleanup_nand:
	nand_cleanup(chip);
err_release_child:
	of_node_put(nand_np);

	क्रम (i = 0; i < oxnas->nchips; i++) अणु
		chip = oxnas->chips[i];
		WARN_ON(mtd_device_unरेजिस्टर(nand_to_mtd(chip)));
		nand_cleanup(chip);
	पूर्ण

err_clk_unprepare:
	clk_disable_unprepare(oxnas->clk);
	वापस err;
पूर्ण

अटल पूर्णांक oxnas_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा oxnas_nand_ctrl *oxnas = platक्रमm_get_drvdata(pdev);
	काष्ठा nand_chip *chip;
	पूर्णांक i;

	क्रम (i = 0; i < oxnas->nchips; i++) अणु
		chip = oxnas->chips[i];
		WARN_ON(mtd_device_unरेजिस्टर(nand_to_mtd(chip)));
		nand_cleanup(chip);
	पूर्ण

	clk_disable_unprepare(oxnas->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id oxnas_nand_match[] = अणु
	अणु .compatible = "oxsemi,ox820-nand" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, oxnas_nand_match);

अटल काष्ठा platक्रमm_driver oxnas_nand_driver = अणु
	.probe	= oxnas_nand_probe,
	.हटाओ	= oxnas_nand_हटाओ,
	.driver	= अणु
		.name		= "oxnas_nand",
		.of_match_table = oxnas_nand_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(oxnas_nand_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_DESCRIPTION("Oxnas NAND driver");
MODULE_ALIAS("platform:oxnas_nand");
