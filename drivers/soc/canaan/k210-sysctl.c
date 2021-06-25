<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2019 Christoph Hellwig.
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 */
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/clk.h>
#समावेश <यंत्र/soc.h>

#समावेश <soc/canaan/k210-sysctl.h>

अटल पूर्णांक k210_sysctl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा clk *pclk;
	पूर्णांक ret;

	dev_info(dev, "K210 system controller\n");

	/* Get घातer bus घड़ी */
	pclk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(pclk))
		वापस dev_err_probe(dev, PTR_ERR(pclk),
				     "Get bus clock failed\n");

	ret = clk_prepare_enable(pclk);
	अगर (ret) अणु
		dev_err(dev, "Enable bus clock failed\n");
		वापस ret;
	पूर्ण

	/* Populate children */
	ret = devm_of_platक्रमm_populate(dev);
	अगर (ret)
		dev_err(dev, "Populate platform failed %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id k210_sysctl_of_match[] = अणु
	अणु .compatible = "canaan,k210-sysctl", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver k210_sysctl_driver = अणु
	.driver	= अणु
		.name		= "k210-sysctl",
		.of_match_table	= k210_sysctl_of_match,
	पूर्ण,
	.probe			= k210_sysctl_probe,
पूर्ण;
builtin_platक्रमm_driver(k210_sysctl_driver);

/*
 * System controller रेजिस्टरs base address and size.
 */
#घोषणा K210_SYSCTL_BASE_ADDR	0x50440000ULL
#घोषणा K210_SYSCTL_BASE_SIZE	0x1000

/*
 * This needs to be called very early during initialization, given that
 * PLL1 needs to be enabled to be able to use all SRAM.
 */
अटल व्योम __init k210_soc_early_init(स्थिर व्योम *fdt)
अणु
	व्योम __iomem *sysctl_base;

	sysctl_base = ioremap(K210_SYSCTL_BASE_ADDR, K210_SYSCTL_BASE_SIZE);
	अगर (!sysctl_base)
		panic("k210-sysctl: ioremap failed");

	k210_clk_early_init(sysctl_base);

	iounmap(sysctl_base);
पूर्ण
SOC_EARLY_INIT_DECLARE(k210_soc, "canaan,kendryte-k210", k210_soc_early_init);
