<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2018 Samsung Electronics Co., Ltd.
// Author: Marek Szyprowski <m.szyprowski@samsung.com>
// Common Clock Framework support क्रम Exynos5 घातer-करोमुख्य dependent घड़ीs

#समावेश <linux/पन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "clk.h"
#समावेश "clk-exynos5-subcmu.h"

अटल काष्ठा samsung_clk_provider *ctx;
अटल स्थिर काष्ठा exynos5_subcmu_info **cmu;
अटल पूर्णांक nr_cmus;

अटल व्योम exynos5_subcmu_clk_save(व्योम __iomem *base,
				    काष्ठा exynos5_subcmu_reg_dump *rd,
				    अचिन्हित पूर्णांक num_regs)
अणु
	क्रम (; num_regs > 0; --num_regs, ++rd) अणु
		rd->save = पढ़ोl(base + rd->offset);
		ग_लिखोl((rd->save & ~rd->mask) | rd->value, base + rd->offset);
		rd->save &= rd->mask;
	पूर्ण
पूर्ण;

अटल व्योम exynos5_subcmu_clk_restore(व्योम __iomem *base,
				       काष्ठा exynos5_subcmu_reg_dump *rd,
				       अचिन्हित पूर्णांक num_regs)
अणु
	क्रम (; num_regs > 0; --num_regs, ++rd)
		ग_लिखोl((पढ़ोl(base + rd->offset) & ~rd->mask) | rd->save,
		       base + rd->offset);
पूर्ण

अटल व्योम exynos5_subcmu_defer_gate(काष्ठा samsung_clk_provider *ctx,
			      स्थिर काष्ठा samsung_gate_घड़ी *list, पूर्णांक nr_clk)
अणु
	जबतक (nr_clk--)
		samsung_clk_add_lookup(ctx, ERR_PTR(-EPROBE_DEFER), list++->id);
पूर्ण

/*
 * Pass the needed घड़ी provider context and रेजिस्टर sub-CMU घड़ीs
 *
 * NOTE: This function has to be called from the मुख्य, OF_CLK_DECLARE-
 * initialized घड़ी provider driver. This happens very early during boot
 * process. Then this driver, during core_initcall रेजिस्टरs two platक्रमm
 * drivers: one which binds to the same device-tree node as OF_CLK_DECLARE
 * driver and second, क्रम handling its per-करोमुख्य child-devices. Those
 * platक्रमm drivers are bound to their devices a bit later in arch_initcall,
 * when OF-core populates all device-tree nodes.
 */
व्योम exynos5_subcmus_init(काष्ठा samsung_clk_provider *_ctx, पूर्णांक _nr_cmus,
			  स्थिर काष्ठा exynos5_subcmu_info **_cmu)
अणु
	ctx = _ctx;
	cmu = _cmu;
	nr_cmus = _nr_cmus;

	क्रम (; _nr_cmus--; _cmu++) अणु
		exynos5_subcmu_defer_gate(ctx, (*_cmu)->gate_clks,
					  (*_cmu)->nr_gate_clks);
		exynos5_subcmu_clk_save(ctx->reg_base, (*_cmu)->suspend_regs,
					(*_cmu)->nr_suspend_regs);
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused exynos5_subcmu_suspend(काष्ठा device *dev)
अणु
	काष्ठा exynos5_subcmu_info *info = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->lock, flags);
	exynos5_subcmu_clk_save(ctx->reg_base, info->suspend_regs,
				info->nr_suspend_regs);
	spin_unlock_irqrestore(&ctx->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos5_subcmu_resume(काष्ठा device *dev)
अणु
	काष्ठा exynos5_subcmu_info *info = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->lock, flags);
	exynos5_subcmu_clk_restore(ctx->reg_base, info->suspend_regs,
				   info->nr_suspend_regs);
	spin_unlock_irqrestore(&ctx->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक __init exynos5_subcmu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा exynos5_subcmu_info *info = dev_get_drvdata(dev);

	pm_runसमय_set_suspended(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_get(dev);

	ctx->dev = dev;
	samsung_clk_रेजिस्टर_भाग(ctx, info->भाग_clks, info->nr_भाग_clks);
	samsung_clk_रेजिस्टर_gate(ctx, info->gate_clks, info->nr_gate_clks);
	ctx->dev = शून्य;

	pm_runसमय_put_sync(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops exynos5_subcmu_pm_ops = अणु
	SET_RUNTIME_PM_OPS(exynos5_subcmu_suspend,
			   exynos5_subcmu_resume, शून्य)
	SET_LATE_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				     pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver exynos5_subcmu_driver __refdata = अणु
	.driver	= अणु
		.name = "exynos5-subcmu",
		.suppress_bind_attrs = true,
		.pm = &exynos5_subcmu_pm_ops,
	पूर्ण,
	.probe = exynos5_subcmu_probe,
पूर्ण;

अटल पूर्णांक __init exynos5_clk_रेजिस्टर_subcmu(काष्ठा device *parent,
					 स्थिर काष्ठा exynos5_subcmu_info *info,
					      काष्ठा device_node *pd_node)
अणु
	काष्ठा of_phandle_args genpdspec = अणु .np = pd_node पूर्ण;
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret;

	pdev = platक्रमm_device_alloc("exynos5-subcmu", PLATFORM_DEVID_AUTO);
	अगर (!pdev)
		वापस -ENOMEM;

	pdev->dev.parent = parent;
	platक्रमm_set_drvdata(pdev, (व्योम *)info);
	of_genpd_add_device(&genpdspec, &pdev->dev);
	ret = platक्रमm_device_add(pdev);
	अगर (ret)
		platक्रमm_device_put(pdev);

	वापस ret;
पूर्ण

अटल पूर्णांक __init exynos5_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np;
	स्थिर अक्षर *name;
	पूर्णांक i;

	क्रम_each_compatible_node(np, शून्य, "samsung,exynos4210-pd") अणु
		अगर (of_property_पढ़ो_string(np, "label", &name) < 0)
			जारी;
		क्रम (i = 0; i < nr_cmus; i++)
			अगर (म_भेद(cmu[i]->pd_name, name) == 0)
				exynos5_clk_रेजिस्टर_subcmu(&pdev->dev,
							    cmu[i], np);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id exynos5_clk_of_match[] = अणु
	अणु .compatible = "samsung,exynos5250-clock", पूर्ण,
	अणु .compatible = "samsung,exynos5420-clock", पूर्ण,
	अणु .compatible = "samsung,exynos5800-clock", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver exynos5_clk_driver __refdata = अणु
	.driver	= अणु
		.name = "exynos5-clock",
		.of_match_table = exynos5_clk_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = exynos5_clk_probe,
पूर्ण;

अटल पूर्णांक __init exynos5_clk_drv_init(व्योम)
अणु
	platक्रमm_driver_रेजिस्टर(&exynos5_clk_driver);
	platक्रमm_driver_रेजिस्टर(&exynos5_subcmu_driver);
	वापस 0;
पूर्ण
core_initcall(exynos5_clk_drv_init);
