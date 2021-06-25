<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * न_अंकD Flash Controller Device Driver क्रम DT
 *
 * Copyright तऊ 2011, Picochip.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश "denali.h"

काष्ठा denali_dt अणु
	काष्ठा denali_controller controller;
	काष्ठा clk *clk;	/* core घड़ी */
	काष्ठा clk *clk_x;	/* bus पूर्णांकerface घड़ी */
	काष्ठा clk *clk_ecc;	/* ECC circuit घड़ी */
	काष्ठा reset_control *rst;	/* core reset */
	काष्ठा reset_control *rst_reg;	/* रेजिस्टर reset */
पूर्ण;

काष्ठा denali_dt_data अणु
	अचिन्हित पूर्णांक revision;
	अचिन्हित पूर्णांक caps;
	अचिन्हित पूर्णांक oob_skip_bytes;
	स्थिर काष्ठा nand_ecc_caps *ecc_caps;
पूर्ण;

न_अंकD_ECC_CAPS_SINGLE(denali_socfpga_ecc_caps, denali_calc_ecc_bytes,
		     512, 8, 15);
अटल स्थिर काष्ठा denali_dt_data denali_socfpga_data = अणु
	.caps = DENALI_CAP_HW_ECC_FIXUP,
	.oob_skip_bytes = 2,
	.ecc_caps = &denali_socfpga_ecc_caps,
पूर्ण;

न_अंकD_ECC_CAPS_SINGLE(denali_uniphier_v5a_ecc_caps, denali_calc_ecc_bytes,
		     1024, 8, 16, 24);
अटल स्थिर काष्ठा denali_dt_data denali_uniphier_v5a_data = अणु
	.caps = DENALI_CAP_HW_ECC_FIXUP |
		DENALI_CAP_DMA_64BIT,
	.oob_skip_bytes = 8,
	.ecc_caps = &denali_uniphier_v5a_ecc_caps,
पूर्ण;

न_अंकD_ECC_CAPS_SINGLE(denali_uniphier_v5b_ecc_caps, denali_calc_ecc_bytes,
		     1024, 8, 16);
अटल स्थिर काष्ठा denali_dt_data denali_uniphier_v5b_data = अणु
	.revision = 0x0501,
	.caps = DENALI_CAP_HW_ECC_FIXUP |
		DENALI_CAP_DMA_64BIT,
	.oob_skip_bytes = 8,
	.ecc_caps = &denali_uniphier_v5b_ecc_caps,
पूर्ण;

अटल स्थिर काष्ठा of_device_id denali_nand_dt_ids[] = अणु
	अणु
		.compatible = "altr,socfpga-denali-nand",
		.data = &denali_socfpga_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-denali-nand-v5a",
		.data = &denali_uniphier_v5a_data,
	पूर्ण,
	अणु
		.compatible = "socionext,uniphier-denali-nand-v5b",
		.data = &denali_uniphier_v5b_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, denali_nand_dt_ids);

अटल पूर्णांक denali_dt_chip_init(काष्ठा denali_controller *denali,
			       काष्ठा device_node *chip_np)
अणु
	काष्ठा denali_chip *dchip;
	u32 bank;
	पूर्णांक nsels, i, ret;

	nsels = of_property_count_u32_elems(chip_np, "reg");
	अगर (nsels < 0)
		वापस nsels;

	dchip = devm_kzalloc(denali->dev, काष्ठा_size(dchip, sels, nsels),
			     GFP_KERNEL);
	अगर (!dchip)
		वापस -ENOMEM;

	dchip->nsels = nsels;

	क्रम (i = 0; i < nsels; i++) अणु
		ret = of_property_पढ़ो_u32_index(chip_np, "reg", i, &bank);
		अगर (ret)
			वापस ret;

		dchip->sels[i].bank = bank;

		nand_set_flash_node(&dchip->chip, chip_np);
	पूर्ण

	वापस denali_chip_init(denali, dchip);
पूर्ण

अटल पूर्णांक denali_dt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा denali_dt *dt;
	स्थिर काष्ठा denali_dt_data *data;
	काष्ठा denali_controller *denali;
	काष्ठा device_node *np;
	पूर्णांक ret;

	dt = devm_kzalloc(dev, माप(*dt), GFP_KERNEL);
	अगर (!dt)
		वापस -ENOMEM;
	denali = &dt->controller;

	data = of_device_get_match_data(dev);
	अगर (WARN_ON(!data))
		वापस -EINVAL;

	denali->revision = data->revision;
	denali->caps = data->caps;
	denali->oob_skip_bytes = data->oob_skip_bytes;
	denali->ecc_caps = data->ecc_caps;

	denali->dev = dev;
	denali->irq = platक्रमm_get_irq(pdev, 0);
	अगर (denali->irq < 0)
		वापस denali->irq;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "denali_reg");
	denali->reg = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(denali->reg))
		वापस PTR_ERR(denali->reg);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "nand_data");
	denali->host = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(denali->host))
		वापस PTR_ERR(denali->host);

	dt->clk = devm_clk_get(dev, "nand");
	अगर (IS_ERR(dt->clk))
		वापस PTR_ERR(dt->clk);

	dt->clk_x = devm_clk_get(dev, "nand_x");
	अगर (IS_ERR(dt->clk_x))
		वापस PTR_ERR(dt->clk_x);

	dt->clk_ecc = devm_clk_get(dev, "ecc");
	अगर (IS_ERR(dt->clk_ecc))
		वापस PTR_ERR(dt->clk_ecc);

	dt->rst = devm_reset_control_get_optional_shared(dev, "nand");
	अगर (IS_ERR(dt->rst))
		वापस PTR_ERR(dt->rst);

	dt->rst_reg = devm_reset_control_get_optional_shared(dev, "reg");
	अगर (IS_ERR(dt->rst_reg))
		वापस PTR_ERR(dt->rst_reg);

	ret = clk_prepare_enable(dt->clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(dt->clk_x);
	अगर (ret)
		जाओ out_disable_clk;

	ret = clk_prepare_enable(dt->clk_ecc);
	अगर (ret)
		जाओ out_disable_clk_x;

	denali->clk_rate = clk_get_rate(dt->clk);
	denali->clk_x_rate = clk_get_rate(dt->clk_x);

	/*
	 * Deनिश्चित the रेजिस्टर reset, and the core reset in this order.
	 * Deनिश्चितing the core reset जबतक the रेजिस्टर reset is निश्चितed
	 * will cause unpredictable behavior in the controller.
	 */
	ret = reset_control_deनिश्चित(dt->rst_reg);
	अगर (ret)
		जाओ out_disable_clk_ecc;

	ret = reset_control_deनिश्चित(dt->rst);
	अगर (ret)
		जाओ out_निश्चित_rst_reg;

	/*
	 * When the reset is deनिश्चितed, the initialization sequence is kicked
	 * (bootstrap process). The driver must रुको until it finished.
	 * Otherwise, it will result in unpredictable behavior.
	 */
	usleep_range(200, 1000);

	ret = denali_init(denali);
	अगर (ret)
		जाओ out_निश्चित_rst;

	क्रम_each_child_of_node(dev->of_node, np) अणु
		ret = denali_dt_chip_init(denali, np);
		अगर (ret) अणु
			of_node_put(np);
			जाओ out_हटाओ_denali;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, dt);

	वापस 0;

out_हटाओ_denali:
	denali_हटाओ(denali);
out_निश्चित_rst:
	reset_control_निश्चित(dt->rst);
out_निश्चित_rst_reg:
	reset_control_निश्चित(dt->rst_reg);
out_disable_clk_ecc:
	clk_disable_unprepare(dt->clk_ecc);
out_disable_clk_x:
	clk_disable_unprepare(dt->clk_x);
out_disable_clk:
	clk_disable_unprepare(dt->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक denali_dt_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा denali_dt *dt = platक्रमm_get_drvdata(pdev);

	denali_हटाओ(&dt->controller);
	reset_control_निश्चित(dt->rst);
	reset_control_निश्चित(dt->rst_reg);
	clk_disable_unprepare(dt->clk_ecc);
	clk_disable_unprepare(dt->clk_x);
	clk_disable_unprepare(dt->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver denali_dt_driver = अणु
	.probe		= denali_dt_probe,
	.हटाओ		= denali_dt_हटाओ,
	.driver		= अणु
		.name	= "denali-nand-dt",
		.of_match_table	= denali_nand_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(denali_dt_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jamie Iles");
MODULE_DESCRIPTION("DT driver for Denali NAND controller");
