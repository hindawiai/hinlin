<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com/
//

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा TI_UFS_SS_CTRL		0x4
#घोषणा TI_UFS_SS_RST_N_PCS	BIT(0)
#घोषणा TI_UFS_SS_CLK_26MHZ	BIT(4)

अटल पूर्णांक ti_j721e_ufs_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	अचिन्हित दीर्घ clk_rate;
	व्योम __iomem *regbase;
	काष्ठा clk *clk;
	u32 reg = 0;
	पूर्णांक ret;

	regbase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regbase))
		वापस PTR_ERR(regbase);

	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		जाओ disable_pm;
	पूर्ण

	/* Select MPHY refclk frequency */
	clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		dev_err(dev, "Cannot claim MPHY clock.\n");
		जाओ clk_err;
	पूर्ण
	clk_rate = clk_get_rate(clk);
	अगर (clk_rate == 26000000)
		reg |= TI_UFS_SS_CLK_26MHZ;
	devm_clk_put(dev, clk);

	/*  Take UFS slave device out of reset */
	reg |= TI_UFS_SS_RST_N_PCS;
	ग_लिखोl(reg, regbase + TI_UFS_SS_CTRL);

	ret = of_platक्रमm_populate(pdev->dev.of_node, शून्य, शून्य,
				   dev);
	अगर (ret) अणु
		dev_err(dev, "failed to populate child nodes %d\n", ret);
		जाओ clk_err;
	पूर्ण

	वापस ret;

clk_err:
	pm_runसमय_put_sync(dev);
disable_pm:
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक ti_j721e_ufs_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	of_platक्रमm_depopulate(&pdev->dev);
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_j721e_ufs_of_match[] = अणु
	अणु
		.compatible = "ti,j721e-ufs",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ti_j721e_ufs_driver = अणु
	.probe	= ti_j721e_ufs_probe,
	.हटाओ	= ti_j721e_ufs_हटाओ,
	.driver	= अणु
		.name   = "ti-j721e-ufs",
		.of_match_table = ti_j721e_ufs_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ti_j721e_ufs_driver);

MODULE_AUTHOR("Vignesh Raghavendra <vigneshr@ti.com>");
MODULE_DESCRIPTION("TI UFS host controller glue driver");
MODULE_LICENSE("GPL v2");
