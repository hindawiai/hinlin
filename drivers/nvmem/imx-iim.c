<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * i.MX IIM driver
 *
 * Copyright (c) 2017 Pengutronix, Michael Grzeschik <m.grzeschik@pengutronix.de>
 *
 * Based on the barebox iim driver,
 * Copyright (c) 2010 Baruch Siach <baruch@tkos.co.il>,
 *	Orex Computed Radiography
 */

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>

#घोषणा IIM_BANK_BASE(n)	(0x800 + 0x400 * (n))

काष्ठा imx_iim_drvdata अणु
	अचिन्हित पूर्णांक nregs;
पूर्ण;

काष्ठा iim_priv अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
पूर्ण;

अटल पूर्णांक imx_iim_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
			  व्योम *buf, माप_प्रकार bytes)
अणु
	काष्ठा iim_priv *iim = context;
	पूर्णांक i, ret;
	u8 *buf8 = buf;

	ret = clk_prepare_enable(iim->clk);
	अगर (ret)
		वापस ret;

	क्रम (i = offset; i < offset + bytes; i++) अणु
		पूर्णांक bank = i >> 5;
		पूर्णांक reg = i & 0x1f;

		*buf8++ = पढ़ोl(iim->base + IIM_BANK_BASE(bank) + reg * 4);
	पूर्ण

	clk_disable_unprepare(iim->clk);

	वापस 0;
पूर्ण

अटल काष्ठा imx_iim_drvdata imx27_drvdata = अणु
	.nregs = 2 * 32,
पूर्ण;

अटल काष्ठा imx_iim_drvdata imx25_imx31_imx35_drvdata = अणु
	.nregs = 3 * 32,
पूर्ण;

अटल काष्ठा imx_iim_drvdata imx51_drvdata = अणु
	.nregs = 4 * 32,
पूर्ण;

अटल काष्ठा imx_iim_drvdata imx53_drvdata = अणु
	.nregs = 4 * 32 + 16,
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx_iim_dt_ids[] = अणु
	अणु
		.compatible = "fsl,imx25-iim",
		.data = &imx25_imx31_imx35_drvdata,
	पूर्ण, अणु
		.compatible = "fsl,imx27-iim",
		.data = &imx27_drvdata,
	पूर्ण, अणु
		.compatible = "fsl,imx31-iim",
		.data = &imx25_imx31_imx35_drvdata,
	पूर्ण, अणु
		.compatible = "fsl,imx35-iim",
		.data = &imx25_imx31_imx35_drvdata,
	पूर्ण, अणु
		.compatible = "fsl,imx51-iim",
		.data = &imx51_drvdata,
	पूर्ण, अणु
		.compatible = "fsl,imx53-iim",
		.data = &imx53_drvdata,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_iim_dt_ids);

अटल पूर्णांक imx_iim_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iim_priv *iim;
	काष्ठा nvmem_device *nvmem;
	काष्ठा nvmem_config cfg = अणुपूर्ण;
	स्थिर काष्ठा imx_iim_drvdata *drvdata = शून्य;

	iim = devm_kzalloc(dev, माप(*iim), GFP_KERNEL);
	अगर (!iim)
		वापस -ENOMEM;

	iim->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(iim->base))
		वापस PTR_ERR(iim->base);

	drvdata = of_device_get_match_data(&pdev->dev);

	iim->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(iim->clk))
		वापस PTR_ERR(iim->clk);

	cfg.name = "imx-iim",
	cfg.पढ़ो_only = true,
	cfg.word_size = 1,
	cfg.stride = 1,
	cfg.reg_पढ़ो = imx_iim_पढ़ो,
	cfg.dev = dev;
	cfg.size = drvdata->nregs;
	cfg.priv = iim;

	nvmem = devm_nvmem_रेजिस्टर(dev, &cfg);

	वापस PTR_ERR_OR_ZERO(nvmem);
पूर्ण

अटल काष्ठा platक्रमm_driver imx_iim_driver = अणु
	.probe	= imx_iim_probe,
	.driver = अणु
		.name	= "imx-iim",
		.of_match_table = imx_iim_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(imx_iim_driver);

MODULE_AUTHOR("Michael Grzeschik <m.grzeschik@pengutronix.de>");
MODULE_DESCRIPTION("i.MX IIM driver");
MODULE_LICENSE("GPL v2");
