<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 - 2016 Samsung Electronics Co., Ltd.
 *
 * Authors: Inha Song <ideal.song@samsung.com>
 *          Sylwester Nawrocki <s.nawrocki@samsung.com>
 *
 * Samsung Exynos SoC series Low Power Audio Subप्रणाली driver.
 *
 * This module provides regmap क्रम the Top SFR region and instantiates
 * devices क्रम IP blocks like DMAC, I2S, UART.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/soc/samsung/exynos-regs-pmu.h>
#समावेश <linux/types.h>

/* LPASS Top रेजिस्टर definitions */
#घोषणा SFR_LPASS_CORE_SW_RESET		0x08
#घोषणा  LPASS_SB_SW_RESET		BIT(11)
#घोषणा  LPASS_UART_SW_RESET		BIT(10)
#घोषणा  LPASS_PCM_SW_RESET		BIT(9)
#घोषणा  LPASS_I2S_SW_RESET		BIT(8)
#घोषणा  LPASS_WDT1_SW_RESET		BIT(4)
#घोषणा  LPASS_WDT0_SW_RESET		BIT(3)
#घोषणा  LPASS_TIMER_SW_RESET		BIT(2)
#घोषणा  LPASS_MEM_SW_RESET		BIT(1)
#घोषणा  LPASS_DMA_SW_RESET		BIT(0)

#घोषणा SFR_LPASS_INTR_CA5_MASK		0x48
#घोषणा SFR_LPASS_INTR_CPU_MASK		0x58
#घोषणा  LPASS_INTR_APM			BIT(9)
#घोषणा  LPASS_INTR_MIF			BIT(8)
#घोषणा  LPASS_INTR_TIMER		BIT(7)
#घोषणा  LPASS_INTR_DMA			BIT(6)
#घोषणा  LPASS_INTR_GPIO		BIT(5)
#घोषणा  LPASS_INTR_I2S			BIT(4)
#घोषणा  LPASS_INTR_PCM			BIT(3)
#घोषणा  LPASS_INTR_SLIMBUS		BIT(2)
#घोषणा  LPASS_INTR_UART		BIT(1)
#घोषणा  LPASS_INTR_SFR			BIT(0)

काष्ठा exynos_lpass अणु
	/* poपूर्णांकer to the LPASS TOP regmap */
	काष्ठा regmap *top;
	काष्ठा clk *sfr0_clk;
पूर्ण;

अटल व्योम exynos_lpass_core_sw_reset(काष्ठा exynos_lpass *lpass, पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक val = 0;

	regmap_पढ़ो(lpass->top, SFR_LPASS_CORE_SW_RESET, &val);

	val &= ~mask;
	regmap_ग_लिखो(lpass->top, SFR_LPASS_CORE_SW_RESET, val);

	usleep_range(100, 150);

	val |= mask;
	regmap_ग_लिखो(lpass->top, SFR_LPASS_CORE_SW_RESET, val);
पूर्ण

अटल व्योम exynos_lpass_enable(काष्ठा exynos_lpass *lpass)
अणु
	clk_prepare_enable(lpass->sfr0_clk);

	/* Unmask SFR, DMA and I2S पूर्णांकerrupt */
	regmap_ग_लिखो(lpass->top, SFR_LPASS_INTR_CA5_MASK,
		     LPASS_INTR_SFR | LPASS_INTR_DMA | LPASS_INTR_I2S);

	regmap_ग_लिखो(lpass->top, SFR_LPASS_INTR_CPU_MASK,
		     LPASS_INTR_SFR | LPASS_INTR_DMA | LPASS_INTR_I2S |
		     LPASS_INTR_UART);

	exynos_lpass_core_sw_reset(lpass, LPASS_I2S_SW_RESET);
	exynos_lpass_core_sw_reset(lpass, LPASS_DMA_SW_RESET);
	exynos_lpass_core_sw_reset(lpass, LPASS_MEM_SW_RESET);
	exynos_lpass_core_sw_reset(lpass, LPASS_UART_SW_RESET);
पूर्ण

अटल व्योम exynos_lpass_disable(काष्ठा exynos_lpass *lpass)
अणु
	/* Mask any unmasked IP पूर्णांकerrupt sources */
	regmap_ग_लिखो(lpass->top, SFR_LPASS_INTR_CPU_MASK, 0);
	regmap_ग_लिखो(lpass->top, SFR_LPASS_INTR_CA5_MASK, 0);

	clk_disable_unprepare(lpass->sfr0_clk);
पूर्ण

अटल स्थिर काष्ठा regmap_config exynos_lpass_reg_conf = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0xfc,
	.fast_io	= true,
पूर्ण;

अटल पूर्णांक exynos_lpass_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा exynos_lpass *lpass;
	व्योम __iomem *base_top;
	काष्ठा resource *res;

	lpass = devm_kzalloc(dev, माप(*lpass), GFP_KERNEL);
	अगर (!lpass)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base_top = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base_top))
		वापस PTR_ERR(base_top);

	lpass->sfr0_clk = devm_clk_get(dev, "sfr0_ctrl");
	अगर (IS_ERR(lpass->sfr0_clk))
		वापस PTR_ERR(lpass->sfr0_clk);

	lpass->top = regmap_init_mmio(dev, base_top,
					&exynos_lpass_reg_conf);
	अगर (IS_ERR(lpass->top)) अणु
		dev_err(dev, "LPASS top regmap initialization failed\n");
		वापस PTR_ERR(lpass->top);
	पूर्ण

	platक्रमm_set_drvdata(pdev, lpass);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	exynos_lpass_enable(lpass);

	वापस devm_of_platक्रमm_populate(dev);
पूर्ण

अटल पूर्णांक exynos_lpass_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_lpass *lpass = platक्रमm_get_drvdata(pdev);

	exynos_lpass_disable(lpass);
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		exynos_lpass_disable(lpass);
	regmap_निकास(lpass->top);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_lpass_suspend(काष्ठा device *dev)
अणु
	काष्ठा exynos_lpass *lpass = dev_get_drvdata(dev);

	exynos_lpass_disable(lpass);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_lpass_resume(काष्ठा device *dev)
अणु
	काष्ठा exynos_lpass *lpass = dev_get_drvdata(dev);

	exynos_lpass_enable(lpass);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops lpass_pm_ops = अणु
	SET_RUNTIME_PM_OPS(exynos_lpass_suspend, exynos_lpass_resume, शून्य)
	SET_LATE_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				     pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_lpass_of_match[] = अणु
	अणु .compatible = "samsung,exynos5433-lpass" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_lpass_of_match);

अटल काष्ठा platक्रमm_driver exynos_lpass_driver = अणु
	.driver = अणु
		.name		= "exynos-lpass",
		.pm		= &lpass_pm_ops,
		.of_match_table	= exynos_lpass_of_match,
	पूर्ण,
	.probe	= exynos_lpass_probe,
	.हटाओ	= exynos_lpass_हटाओ,
पूर्ण;
module_platक्रमm_driver(exynos_lpass_driver);

MODULE_DESCRIPTION("Samsung Low Power Audio Subsystem driver");
MODULE_LICENSE("GPL v2");
