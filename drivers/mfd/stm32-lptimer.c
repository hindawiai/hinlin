<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * STM32 Low-Power Timer parent driver.
 * Copyright (C) STMicroelectronics 2017
 * Author: Fabrice Gasnier <fabrice.gasnier@st.com>
 * Inspired by Benjamin Gaignard's sपंचांग32-समयrs driver
 */

#समावेश <linux/mfd/sपंचांग32-lpसमयr.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>

#घोषणा STM32_LPTIM_MAX_REGISTER	0x3fc

अटल स्थिर काष्ठा regmap_config sपंचांग32_lpसमयr_regmap_cfg = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = माप(u32),
	.max_रेजिस्टर = STM32_LPTIM_MAX_REGISTER,
	.fast_io = true,
पूर्ण;

अटल पूर्णांक sपंचांग32_lpसमयr_detect_encoder(काष्ठा sपंचांग32_lpसमयr *ddata)
अणु
	u32 val;
	पूर्णांक ret;

	/*
	 * Quadrature encoder mode bit can only be written and पढ़ो back when
	 * Low-Power Timer supports it.
	 */
	ret = regmap_update_bits(ddata->regmap, STM32_LPTIM_CFGR,
				 STM32_LPTIM_ENC, STM32_LPTIM_ENC);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(ddata->regmap, STM32_LPTIM_CFGR, &val);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(ddata->regmap, STM32_LPTIM_CFGR,
				 STM32_LPTIM_ENC, 0);
	अगर (ret)
		वापस ret;

	ddata->has_encoder = !!(val & STM32_LPTIM_ENC);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_lpसमयr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sपंचांग32_lpसमयr *ddata;
	काष्ठा resource *res;
	व्योम __iomem *mmio;
	पूर्णांक ret;

	ddata = devm_kzalloc(dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mmio = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(mmio))
		वापस PTR_ERR(mmio);

	ddata->regmap = devm_regmap_init_mmio_clk(dev, "mux", mmio,
						  &sपंचांग32_lpसमयr_regmap_cfg);
	अगर (IS_ERR(ddata->regmap))
		वापस PTR_ERR(ddata->regmap);

	ddata->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(ddata->clk))
		वापस PTR_ERR(ddata->clk);

	ret = sपंचांग32_lpसमयr_detect_encoder(ddata);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, ddata);

	वापस devm_of_platक्रमm_populate(&pdev->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id sपंचांग32_lpसमयr_of_match[] = अणु
	अणु .compatible = "st,stm32-lptimer", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_lpसमयr_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_lpसमयr_driver = अणु
	.probe = sपंचांग32_lpसमयr_probe,
	.driver = अणु
		.name = "stm32-lptimer",
		.of_match_table = sपंचांग32_lpसमयr_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_lpसमयr_driver);

MODULE_AUTHOR("Fabrice Gasnier <fabrice.gasnier@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32 Low-Power Timer");
MODULE_ALIAS("platform:stm32-lptimer");
MODULE_LICENSE("GPL v2");
