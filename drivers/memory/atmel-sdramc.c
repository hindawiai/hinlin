<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aपंचांगel (Multi-port DDR-)SDRAM Controller driver
 *
 * Author: Alexandre Belloni <alexandre.belloni@मुक्त-electrons.com>
 *
 * Copyright (C) 2014 Aपंचांगel
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा at91_ramc_caps अणु
	bool has_ddrck;
	bool has_mpddr_clk;
पूर्ण;

अटल स्थिर काष्ठा at91_ramc_caps at91rm9200_caps = अणु पूर्ण;

अटल स्थिर काष्ठा at91_ramc_caps at91sam9g45_caps = अणु
	.has_ddrck = 1,
	.has_mpddr_clk = 0,
पूर्ण;

अटल स्थिर काष्ठा at91_ramc_caps sama5d3_caps = अणु
	.has_ddrck = 1,
	.has_mpddr_clk = 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_ramc_of_match[] = अणु
	अणु .compatible = "atmel,at91rm9200-sdramc", .data = &at91rm9200_caps, पूर्ण,
	अणु .compatible = "atmel,at91sam9260-sdramc", .data = &at91rm9200_caps, पूर्ण,
	अणु .compatible = "atmel,at91sam9g45-ddramc", .data = &at91sam9g45_caps, पूर्ण,
	अणु .compatible = "atmel,sama5d3-ddramc", .data = &sama5d3_caps, पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक aपंचांगel_ramc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा at91_ramc_caps *caps;
	काष्ठा clk *clk;

	caps = of_device_get_match_data(&pdev->dev);

	अगर (caps->has_ddrck) अणु
		clk = devm_clk_get(&pdev->dev, "ddrck");
		अगर (IS_ERR(clk))
			वापस PTR_ERR(clk);
		clk_prepare_enable(clk);
	पूर्ण

	अगर (caps->has_mpddr_clk) अणु
		clk = devm_clk_get(&pdev->dev, "mpddr");
		अगर (IS_ERR(clk)) अणु
			pr_err("AT91 RAMC: couldn't get mpddr clock\n");
			वापस PTR_ERR(clk);
		पूर्ण
		clk_prepare_enable(clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aपंचांगel_ramc_driver = अणु
	.probe		= aपंचांगel_ramc_probe,
	.driver		= अणु
		.name	= "atmel-ramc",
		.of_match_table = aपंचांगel_ramc_of_match,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(aपंचांगel_ramc_driver);
