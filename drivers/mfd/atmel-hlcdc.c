<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Free Electrons
 * Copyright (C) 2014 Aपंचांगel
 *
 * Author: Boris BREZILLON <boris.brezillon@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mfd/aपंचांगel-hlcdc.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा ATMEL_HLCDC_REG_MAX		(0x4000 - 0x4)

काष्ठा aपंचांगel_hlcdc_regmap अणु
	व्योम __iomem *regs;
	काष्ठा device *dev;
पूर्ण;

अटल स्थिर काष्ठा mfd_cell aपंचांगel_hlcdc_cells[] = अणु
	अणु
		.name = "atmel-hlcdc-pwm",
		.of_compatible = "atmel,hlcdc-pwm",
	पूर्ण,
	अणु
		.name = "atmel-hlcdc-dc",
		.of_compatible = "atmel,hlcdc-display-controller",
	पूर्ण,
पूर्ण;

अटल पूर्णांक regmap_aपंचांगel_hlcdc_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
					अचिन्हित पूर्णांक val)
अणु
	काष्ठा aपंचांगel_hlcdc_regmap *hregmap = context;

	अगर (reg <= ATMEL_HLCDC_DIS) अणु
		u32 status;
		पूर्णांक ret;

		ret = पढ़ोl_poll_समयout_atomic(hregmap->regs + ATMEL_HLCDC_SR,
						status,
						!(status & ATMEL_HLCDC_SIP),
						1, 100);
		अगर (ret) अणु
			dev_err(hregmap->dev,
				"Timeout! Clock domain synchronization is in progress!\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ग_लिखोl(val, hregmap->regs + reg);

	वापस 0;
पूर्ण

अटल पूर्णांक regmap_aपंचांगel_hlcdc_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				       अचिन्हित पूर्णांक *val)
अणु
	काष्ठा aपंचांगel_hlcdc_regmap *hregmap = context;

	*val = पढ़ोl(hregmap->regs + reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config aपंचांगel_hlcdc_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = ATMEL_HLCDC_REG_MAX,
	.reg_ग_लिखो = regmap_aपंचांगel_hlcdc_reg_ग_लिखो,
	.reg_पढ़ो = regmap_aपंचांगel_hlcdc_reg_पढ़ो,
	.fast_io = true,
पूर्ण;

अटल पूर्णांक aपंचांगel_hlcdc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_hlcdc_regmap *hregmap;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा aपंचांगel_hlcdc *hlcdc;
	काष्ठा resource *res;

	hregmap = devm_kzalloc(dev, माप(*hregmap), GFP_KERNEL);
	अगर (!hregmap)
		वापस -ENOMEM;

	hlcdc = devm_kzalloc(dev, माप(*hlcdc), GFP_KERNEL);
	अगर (!hlcdc)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hregmap->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(hregmap->regs))
		वापस PTR_ERR(hregmap->regs);

	hregmap->dev = &pdev->dev;

	hlcdc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (hlcdc->irq < 0)
		वापस hlcdc->irq;

	hlcdc->periph_clk = devm_clk_get(dev, "periph_clk");
	अगर (IS_ERR(hlcdc->periph_clk)) अणु
		dev_err(dev, "failed to get peripheral clock\n");
		वापस PTR_ERR(hlcdc->periph_clk);
	पूर्ण

	hlcdc->sys_clk = devm_clk_get(dev, "sys_clk");
	अगर (IS_ERR(hlcdc->sys_clk)) अणु
		dev_err(dev, "failed to get system clock\n");
		वापस PTR_ERR(hlcdc->sys_clk);
	पूर्ण

	hlcdc->slow_clk = devm_clk_get(dev, "slow_clk");
	अगर (IS_ERR(hlcdc->slow_clk)) अणु
		dev_err(dev, "failed to get slow clock\n");
		वापस PTR_ERR(hlcdc->slow_clk);
	पूर्ण

	hlcdc->regmap = devm_regmap_init(dev, शून्य, hregmap,
					 &aपंचांगel_hlcdc_regmap_config);
	अगर (IS_ERR(hlcdc->regmap))
		वापस PTR_ERR(hlcdc->regmap);

	dev_set_drvdata(dev, hlcdc);

	वापस devm_mfd_add_devices(dev, -1, aपंचांगel_hlcdc_cells,
				    ARRAY_SIZE(aपंचांगel_hlcdc_cells),
				    शून्य, 0, शून्य);
पूर्ण

अटल स्थिर काष्ठा of_device_id aपंचांगel_hlcdc_match[] = अणु
	अणु .compatible = "atmel,at91sam9n12-hlcdc" पूर्ण,
	अणु .compatible = "atmel,at91sam9x5-hlcdc" पूर्ण,
	अणु .compatible = "atmel,sama5d2-hlcdc" पूर्ण,
	अणु .compatible = "atmel,sama5d3-hlcdc" पूर्ण,
	अणु .compatible = "atmel,sama5d4-hlcdc" पूर्ण,
	अणु .compatible = "microchip,sam9x60-hlcdc" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_hlcdc_match);

अटल काष्ठा platक्रमm_driver aपंचांगel_hlcdc_driver = अणु
	.probe = aपंचांगel_hlcdc_probe,
	.driver = अणु
		.name = "atmel-hlcdc",
		.of_match_table = aपंचांगel_hlcdc_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(aपंचांगel_hlcdc_driver);

MODULE_ALIAS("platform:atmel-hlcdc");
MODULE_AUTHOR("Boris Brezillon <boris.brezillon@free-electrons.com>");
MODULE_DESCRIPTION("Atmel HLCDC driver");
MODULE_LICENSE("GPL v2");
