<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 Samsung Electronics Co., Ltd.
 * Author: Marek Szyprowski <m.szyprowski@samsung.com>
 *
 * Common Clock Framework support क्रम Exynos4412 ISP module.
*/

#समावेश <dt-bindings/घड़ी/exynos4.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "clk.h"

/* Exynos4x12 specअगरic रेजिस्टरs, which beदीर्घ to ISP घातer करोमुख्य */
#घोषणा E4X12_DIV_ISP0		0x0300
#घोषणा E4X12_DIV_ISP1		0x0304
#घोषणा E4X12_GATE_ISP0		0x0800
#घोषणा E4X12_GATE_ISP1		0x0804

/*
 * Support क्रम CMU save/restore across प्रणाली suspends
 */
अटल काष्ठा samsung_clk_reg_dump *exynos4x12_save_isp;

अटल स्थिर अचिन्हित दीर्घ exynos4x12_clk_isp_save[] __initस्थिर = अणु
	E4X12_DIV_ISP0,
	E4X12_DIV_ISP1,
	E4X12_GATE_ISP0,
	E4X12_GATE_ISP1,
पूर्ण;

अटल काष्ठा samsung_भाग_घड़ी exynos4x12_isp_भाग_clks[] = अणु
	DIV(CLK_ISP_DIV_ISP0, "div_isp0", "aclk200", E4X12_DIV_ISP0, 0, 3),
	DIV(CLK_ISP_DIV_ISP1, "div_isp1", "aclk200", E4X12_DIV_ISP0, 4, 3),
	DIV(CLK_ISP_DIV_MCUISP0, "div_mcuisp0", "aclk400_mcuisp",
	    E4X12_DIV_ISP1, 4, 3),
	DIV(CLK_ISP_DIV_MCUISP1, "div_mcuisp1", "div_mcuisp0",
	    E4X12_DIV_ISP1, 8, 3),
	DIV(0, "div_mpwm", "div_isp1", E4X12_DIV_ISP1, 0, 3),
पूर्ण;

अटल काष्ठा samsung_gate_घड़ी exynos4x12_isp_gate_clks[] = अणु
	GATE(CLK_ISP_FIMC_ISP, "isp", "aclk200", E4X12_GATE_ISP0, 0, 0, 0),
	GATE(CLK_ISP_FIMC_DRC, "drc", "aclk200", E4X12_GATE_ISP0, 1, 0, 0),
	GATE(CLK_ISP_FIMC_FD, "fd", "aclk200", E4X12_GATE_ISP0, 2, 0, 0),
	GATE(CLK_ISP_FIMC_LITE0, "lite0", "aclk200", E4X12_GATE_ISP0, 3, 0, 0),
	GATE(CLK_ISP_FIMC_LITE1, "lite1", "aclk200", E4X12_GATE_ISP0, 4, 0, 0),
	GATE(CLK_ISP_MCUISP, "mcuisp", "aclk200", E4X12_GATE_ISP0, 5, 0, 0),
	GATE(CLK_ISP_GICISP, "gicisp", "aclk200", E4X12_GATE_ISP0, 7, 0, 0),
	GATE(CLK_ISP_SMMU_ISP, "smmu_isp", "aclk200", E4X12_GATE_ISP0, 8, 0, 0),
	GATE(CLK_ISP_SMMU_DRC, "smmu_drc", "aclk200", E4X12_GATE_ISP0, 9, 0, 0),
	GATE(CLK_ISP_SMMU_FD, "smmu_fd", "aclk200", E4X12_GATE_ISP0, 10, 0, 0),
	GATE(CLK_ISP_SMMU_LITE0, "smmu_lite0", "aclk200", E4X12_GATE_ISP0, 11,
	     0, 0),
	GATE(CLK_ISP_SMMU_LITE1, "smmu_lite1", "aclk200", E4X12_GATE_ISP0, 12,
	     0, 0),
	GATE(CLK_ISP_PPMUISPMX, "ppmuispmx", "aclk200", E4X12_GATE_ISP0, 20,
	     0, 0),
	GATE(CLK_ISP_PPMUISPX, "ppmuispx", "aclk200", E4X12_GATE_ISP0, 21,
	     0, 0),
	GATE(CLK_ISP_MCUCTL_ISP, "mcuctl_isp", "aclk200", E4X12_GATE_ISP0, 23,
	     0, 0),
	GATE(CLK_ISP_MPWM_ISP, "mpwm_isp", "aclk200", E4X12_GATE_ISP0, 24,
	     0, 0),
	GATE(CLK_ISP_I2C0_ISP, "i2c0_isp", "aclk200", E4X12_GATE_ISP0, 25,
	     0, 0),
	GATE(CLK_ISP_I2C1_ISP, "i2c1_isp", "aclk200", E4X12_GATE_ISP0, 26,
	     0, 0),
	GATE(CLK_ISP_MTCADC_ISP, "mtcadc_isp", "aclk200", E4X12_GATE_ISP0, 27,
	     0, 0),
	GATE(CLK_ISP_PWM_ISP, "pwm_isp", "aclk200", E4X12_GATE_ISP0, 28, 0, 0),
	GATE(CLK_ISP_WDT_ISP, "wdt_isp", "aclk200", E4X12_GATE_ISP0, 30, 0, 0),
	GATE(CLK_ISP_UART_ISP, "uart_isp", "aclk200", E4X12_GATE_ISP0, 31,
	     0, 0),
	GATE(CLK_ISP_ASYNCAXIM, "asyncaxim", "aclk200", E4X12_GATE_ISP1, 0,
	     0, 0),
	GATE(CLK_ISP_SMMU_ISPCX, "smmu_ispcx", "aclk200", E4X12_GATE_ISP1, 4,
	     0, 0),
	GATE(CLK_ISP_SPI0_ISP, "spi0_isp", "aclk200", E4X12_GATE_ISP1, 12,
	     0, 0),
	GATE(CLK_ISP_SPI1_ISP, "spi1_isp", "aclk200", E4X12_GATE_ISP1, 13,
	     0, 0),
पूर्ण;

अटल पूर्णांक __maybe_unused exynos4x12_isp_clk_suspend(काष्ठा device *dev)
अणु
	काष्ठा samsung_clk_provider *ctx = dev_get_drvdata(dev);

	samsung_clk_save(ctx->reg_base, exynos4x12_save_isp,
			 ARRAY_SIZE(exynos4x12_clk_isp_save));
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos4x12_isp_clk_resume(काष्ठा device *dev)
अणु
	काष्ठा samsung_clk_provider *ctx = dev_get_drvdata(dev);

	samsung_clk_restore(ctx->reg_base, exynos4x12_save_isp,
			    ARRAY_SIZE(exynos4x12_clk_isp_save));
	वापस 0;
पूर्ण

अटल पूर्णांक __init exynos4x12_isp_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा samsung_clk_provider *ctx;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा resource *res;
	व्योम __iomem *reg_base;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	reg_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(reg_base))
		वापस PTR_ERR(reg_base);

	exynos4x12_save_isp = samsung_clk_alloc_reg_dump(exynos4x12_clk_isp_save,
					ARRAY_SIZE(exynos4x12_clk_isp_save));
	अगर (!exynos4x12_save_isp)
		वापस -ENOMEM;

	ctx = samsung_clk_init(np, reg_base, CLK_NR_ISP_CLKS);
	ctx->dev = dev;

	platक्रमm_set_drvdata(pdev, ctx);

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	samsung_clk_रेजिस्टर_भाग(ctx, exynos4x12_isp_भाग_clks,
				 ARRAY_SIZE(exynos4x12_isp_भाग_clks));
	samsung_clk_रेजिस्टर_gate(ctx, exynos4x12_isp_gate_clks,
				  ARRAY_SIZE(exynos4x12_isp_gate_clks));

	samsung_clk_of_add_provider(np, ctx);
	pm_runसमय_put(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id exynos4x12_isp_clk_of_match[] = अणु
	अणु .compatible = "samsung,exynos4412-isp-clock", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops exynos4x12_isp_pm_ops = अणु
	SET_RUNTIME_PM_OPS(exynos4x12_isp_clk_suspend,
			   exynos4x12_isp_clk_resume, शून्य)
	SET_LATE_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				     pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver exynos4x12_isp_clk_driver __refdata = अणु
	.driver	= अणु
		.name = "exynos4x12-isp-clk",
		.of_match_table = exynos4x12_isp_clk_of_match,
		.suppress_bind_attrs = true,
		.pm = &exynos4x12_isp_pm_ops,
	पूर्ण,
	.probe = exynos4x12_isp_clk_probe,
पूर्ण;

अटल पूर्णांक __init exynos4x12_isp_clk_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&exynos4x12_isp_clk_driver);
पूर्ण
core_initcall(exynos4x12_isp_clk_init);
