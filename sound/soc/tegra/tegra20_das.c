<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tegra20_das.c - Tegra20 DAS driver
 *
 * Author: Stephen Warren <swarren@nvidia.com>
 * Copyright (C) 2010 - NVIDIA, Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/soc.h>
#समावेश "tegra20_das.h"

#घोषणा DRV_NAME "tegra20-das"

अटल काष्ठा tegra20_das *das;

अटल अंतरभूत व्योम tegra20_das_ग_लिखो(u32 reg, u32 val)
अणु
	regmap_ग_लिखो(das->regmap, reg, val);
पूर्ण

अटल अंतरभूत u32 tegra20_das_पढ़ो(u32 reg)
अणु
	u32 val;

	regmap_पढ़ो(das->regmap, reg, &val);
	वापस val;
पूर्ण

पूर्णांक tegra20_das_connect_dap_to_dac(पूर्णांक dap, पूर्णांक dac)
अणु
	u32 addr;
	u32 reg;

	अगर (!das)
		वापस -ENODEV;

	addr = TEGRA20_DAS_DAP_CTRL_SEL +
		(dap * TEGRA20_DAS_DAP_CTRL_SEL_STRIDE);
	reg = dac << TEGRA20_DAS_DAP_CTRL_SEL_DAP_CTRL_SEL_P;

	tegra20_das_ग_लिखो(addr, reg);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra20_das_connect_dap_to_dac);

पूर्णांक tegra20_das_connect_dap_to_dap(पूर्णांक dap, पूर्णांक otherdap, पूर्णांक master,
				   पूर्णांक sdata1rx, पूर्णांक sdata2rx)
अणु
	u32 addr;
	u32 reg;

	अगर (!das)
		वापस -ENODEV;

	addr = TEGRA20_DAS_DAP_CTRL_SEL +
		(dap * TEGRA20_DAS_DAP_CTRL_SEL_STRIDE);
	reg = (otherdap << TEGRA20_DAS_DAP_CTRL_SEL_DAP_CTRL_SEL_P) |
		(!!sdata2rx << TEGRA20_DAS_DAP_CTRL_SEL_DAP_SDATA2_TX_RX_P) |
		(!!sdata1rx << TEGRA20_DAS_DAP_CTRL_SEL_DAP_SDATA1_TX_RX_P) |
		(!!master << TEGRA20_DAS_DAP_CTRL_SEL_DAP_MS_SEL_P);

	tegra20_das_ग_लिखो(addr, reg);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra20_das_connect_dap_to_dap);

पूर्णांक tegra20_das_connect_dac_to_dap(पूर्णांक dac, पूर्णांक dap)
अणु
	u32 addr;
	u32 reg;

	अगर (!das)
		वापस -ENODEV;

	addr = TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL +
		(dac * TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL_STRIDE);
	reg = dap << TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL_DAC_CLK_SEL_P |
		dap << TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL_DAC_SDATA1_SEL_P |
		dap << TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL_DAC_SDATA2_SEL_P;

	tegra20_das_ग_लिखो(addr, reg);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra20_das_connect_dac_to_dap);

#घोषणा LAST_REG(name) \
	(TEGRA20_DAS_##name + \
	 (TEGRA20_DAS_##name##_STRIDE * (TEGRA20_DAS_##name##_COUNT - 1)))

अटल bool tegra20_das_wr_rd_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (reg <= LAST_REG(DAP_CTRL_SEL))
		वापस true;
	अगर ((reg >= TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL) &&
	    (reg <= LAST_REG(DAC_INPUT_DATA_CLK_SEL)))
		वापस true;

	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config tegra20_das_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = LAST_REG(DAC_INPUT_DATA_CLK_SEL),
	.ग_लिखोable_reg = tegra20_das_wr_rd_reg,
	.पढ़ोable_reg = tegra20_das_wr_rd_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक tegra20_das_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *regs;
	पूर्णांक ret = 0;

	अगर (das)
		वापस -ENODEV;

	das = devm_kzalloc(&pdev->dev, माप(काष्ठा tegra20_das), GFP_KERNEL);
	अगर (!das) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	das->dev = &pdev->dev;

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs)) अणु
		ret = PTR_ERR(regs);
		जाओ err;
	पूर्ण

	das->regmap = devm_regmap_init_mmio(&pdev->dev, regs,
					    &tegra20_das_regmap_config);
	अगर (IS_ERR(das->regmap)) अणु
		dev_err(&pdev->dev, "regmap init failed\n");
		ret = PTR_ERR(das->regmap);
		जाओ err;
	पूर्ण

	ret = tegra20_das_connect_dap_to_dac(TEGRA20_DAS_DAP_ID_1,
					     TEGRA20_DAS_DAP_SEL_DAC1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't set up DAS DAP connection\n");
		जाओ err;
	पूर्ण
	ret = tegra20_das_connect_dac_to_dap(TEGRA20_DAS_DAC_ID_1,
					     TEGRA20_DAS_DAC_SEL_DAP1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't set up DAS DAC connection\n");
		जाओ err;
	पूर्ण

	ret = tegra20_das_connect_dap_to_dac(TEGRA20_DAS_DAP_ID_3,
					     TEGRA20_DAS_DAP_SEL_DAC3);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't set up DAS DAP connection\n");
		जाओ err;
	पूर्ण
	ret = tegra20_das_connect_dac_to_dap(TEGRA20_DAS_DAC_ID_3,
					     TEGRA20_DAS_DAC_SEL_DAP3);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't set up DAS DAC connection\n");
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, das);

	वापस 0;

err:
	das = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक tegra20_das_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (!das)
		वापस -ENODEV;

	das = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra20_das_of_match[] = अणु
	अणु .compatible = "nvidia,tegra20-das", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra20_das_driver = अणु
	.probe = tegra20_das_probe,
	.हटाओ = tegra20_das_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = tegra20_das_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra20_das_driver);

MODULE_AUTHOR("Stephen Warren <swarren@nvidia.com>");
MODULE_DESCRIPTION("Tegra20 DAS driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DEVICE_TABLE(of, tegra20_das_of_match);
