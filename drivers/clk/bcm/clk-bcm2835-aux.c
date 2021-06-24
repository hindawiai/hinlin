<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2015 Broadcom
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <dt-bindings/घड़ी/bcm2835-aux.h>

#घोषणा BCM2835_AUXIRQ		0x00
#घोषणा BCM2835_AUXENB		0x04

अटल पूर्णांक bcm2835_aux_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा clk_hw_onecell_data *onecell;
	स्थिर अक्षर *parent;
	काष्ठा clk *parent_clk;
	व्योम __iomem *reg, *gate;

	parent_clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(parent_clk))
		वापस PTR_ERR(parent_clk);
	parent = __clk_get_name(parent_clk);

	reg = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	onecell = devm_kदो_स्मृति(dev,
			       काष्ठा_size(onecell, hws,
					   BCM2835_AUX_CLOCK_COUNT),
			       GFP_KERNEL);
	अगर (!onecell)
		वापस -ENOMEM;
	onecell->num = BCM2835_AUX_CLOCK_COUNT;

	gate = reg + BCM2835_AUXENB;
	onecell->hws[BCM2835_AUX_CLOCK_UART] =
		clk_hw_रेजिस्टर_gate(dev, "aux_uart", parent, 0, gate, 0, 0, शून्य);

	onecell->hws[BCM2835_AUX_CLOCK_SPI1] =
		clk_hw_रेजिस्टर_gate(dev, "aux_spi1", parent, 0, gate, 1, 0, शून्य);

	onecell->hws[BCM2835_AUX_CLOCK_SPI2] =
		clk_hw_रेजिस्टर_gate(dev, "aux_spi2", parent, 0, gate, 2, 0, शून्य);

	वापस of_clk_add_hw_provider(pdev->dev.of_node, of_clk_hw_onecell_get,
				      onecell);
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm2835_aux_clk_of_match[] = अणु
	अणु .compatible = "brcm,bcm2835-aux", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm2835_aux_clk_of_match);

अटल काष्ठा platक्रमm_driver bcm2835_aux_clk_driver = अणु
	.driver = अणु
		.name = "bcm2835-aux-clk",
		.of_match_table = bcm2835_aux_clk_of_match,
	पूर्ण,
	.probe          = bcm2835_aux_clk_probe,
पूर्ण;
builtin_platक्रमm_driver(bcm2835_aux_clk_driver);

MODULE_AUTHOR("Eric Anholt <eric@anholt.net>");
MODULE_DESCRIPTION("BCM2835 auxiliary peripheral clock driver");
MODULE_LICENSE("GPL");
