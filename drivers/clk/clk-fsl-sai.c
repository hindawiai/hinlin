<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Freescale SAI BCLK as a generic घड़ी driver
 *
 * Copyright 2020 Michael Walle <michael@walle.cc>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

#घोषणा I2S_CSR		0x00
#घोषणा I2S_CR2		0x08
#घोषणा CSR_BCE_BIT	28
#घोषणा CR2_BCD		BIT(24)
#घोषणा CR2_DIV_SHIFT	0
#घोषणा CR2_DIV_WIDTH	8

काष्ठा fsl_sai_clk अणु
	काष्ठा clk_भागider भाग;
	काष्ठा clk_gate gate;
	spinlock_t lock;
पूर्ण;

अटल पूर्णांक fsl_sai_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fsl_sai_clk *sai_clk;
	काष्ठा clk_parent_data pdata = अणु .index = 0 पूर्ण;
	व्योम __iomem *base;
	काष्ठा clk_hw *hw;
	काष्ठा resource *res;

	sai_clk = devm_kzalloc(dev, माप(*sai_clk), GFP_KERNEL);
	अगर (!sai_clk)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	spin_lock_init(&sai_clk->lock);

	sai_clk->gate.reg = base + I2S_CSR;
	sai_clk->gate.bit_idx = CSR_BCE_BIT;
	sai_clk->gate.lock = &sai_clk->lock;

	sai_clk->भाग.reg = base + I2S_CR2;
	sai_clk->भाग.shअगरt = CR2_DIV_SHIFT;
	sai_clk->भाग.width = CR2_DIV_WIDTH;
	sai_clk->भाग.lock = &sai_clk->lock;

	/* set घड़ी direction, we are the BCLK master */
	ग_लिखोl(CR2_BCD, base + I2S_CR2);

	hw = devm_clk_hw_रेजिस्टर_composite_pdata(dev, dev->of_node->name,
						  &pdata, 1, शून्य, शून्य,
						  &sai_clk->भाग.hw,
						  &clk_भागider_ops,
						  &sai_clk->gate.hw,
						  &clk_gate_ops,
						  CLK_SET_RATE_GATE);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get, hw);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_fsl_sai_clk_ids[] = अणु
	अणु .compatible = "fsl,vf610-sai-clock" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_fsl_sai_clk_ids);

अटल काष्ठा platक्रमm_driver fsl_sai_clk_driver = अणु
	.probe = fsl_sai_clk_probe,
	.driver		= अणु
		.name	= "fsl-sai-clk",
		.of_match_table = of_fsl_sai_clk_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(fsl_sai_clk_driver);

MODULE_DESCRIPTION("Freescale SAI bitclock-as-a-clock driver");
MODULE_AUTHOR("Michael Walle <michael@walle.cc>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:fsl-sai-clk");
