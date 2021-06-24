<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 * Author: Tomasz Figa <t.figa@samsung.com>
 *
 * Clock driver क्रम Exynos घड़ी output
 */

#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>

#घोषणा EXYNOS_CLKOUT_NR_CLKS		1
#घोषणा EXYNOS_CLKOUT_PARENTS		32

#घोषणा EXYNOS_PMU_DEBUG_REG		0xa00
#घोषणा EXYNOS_CLKOUT_DISABLE_SHIFT	0
#घोषणा EXYNOS_CLKOUT_MUX_SHIFT		8
#घोषणा EXYNOS4_CLKOUT_MUX_MASK		0xf
#घोषणा EXYNOS5_CLKOUT_MUX_MASK		0x1f

काष्ठा exynos_clkout अणु
	काष्ठा clk_gate gate;
	काष्ठा clk_mux mux;
	spinlock_t slock;
	व्योम __iomem *reg;
	काष्ठा device_node *np;
	u32 pmu_debug_save;
	काष्ठा clk_hw_onecell_data data;
पूर्ण;

काष्ठा exynos_clkout_variant अणु
	u32 mux_mask;
पूर्ण;

अटल स्थिर काष्ठा exynos_clkout_variant exynos_clkout_exynos4 = अणु
	.mux_mask	= EXYNOS4_CLKOUT_MUX_MASK,
पूर्ण;

अटल स्थिर काष्ठा exynos_clkout_variant exynos_clkout_exynos5 = अणु
	.mux_mask	= EXYNOS5_CLKOUT_MUX_MASK,
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_clkout_ids[] = अणु
	अणु
		.compatible = "samsung,exynos3250-pmu",
		.data = &exynos_clkout_exynos4,
	पूर्ण, अणु
		.compatible = "samsung,exynos4210-pmu",
		.data = &exynos_clkout_exynos4,
	पूर्ण, अणु
		.compatible = "samsung,exynos4412-pmu",
		.data = &exynos_clkout_exynos4,
	पूर्ण, अणु
		.compatible = "samsung,exynos5250-pmu",
		.data = &exynos_clkout_exynos5,
	पूर्ण, अणु
		.compatible = "samsung,exynos5410-pmu",
		.data = &exynos_clkout_exynos5,
	पूर्ण, अणु
		.compatible = "samsung,exynos5420-pmu",
		.data = &exynos_clkout_exynos5,
	पूर्ण, अणु
		.compatible = "samsung,exynos5433-pmu",
		.data = &exynos_clkout_exynos5,
	पूर्ण, अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_clkout_ids);

/*
 * Device will be instantiated as child of PMU device without its own
 * device node.  Thereक्रमe match compatibles against parent.
 */
अटल पूर्णांक exynos_clkout_match_parent_dev(काष्ठा device *dev, u32 *mux_mask)
अणु
	स्थिर काष्ठा exynos_clkout_variant *variant;
	स्थिर काष्ठा of_device_id *match;

	अगर (!dev->parent) अणु
		dev_err(dev, "not instantiated from MFD\n");
		वापस -EINVAL;
	पूर्ण

	match = of_match_device(exynos_clkout_ids, dev->parent);
	अगर (!match) अणु
		dev_err(dev, "cannot match parent device\n");
		वापस -EINVAL;
	पूर्ण
	variant = match->data;

	*mux_mask = variant->mux_mask;

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_clkout_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर अक्षर *parent_names[EXYNOS_CLKOUT_PARENTS];
	काष्ठा clk *parents[EXYNOS_CLKOUT_PARENTS];
	काष्ठा exynos_clkout *clkout;
	पूर्णांक parent_count, ret, i;
	u32 mux_mask;

	clkout = devm_kzalloc(&pdev->dev,
			      काष्ठा_size(clkout, data.hws, EXYNOS_CLKOUT_NR_CLKS),
			      GFP_KERNEL);
	अगर (!clkout)
		वापस -ENOMEM;

	ret = exynos_clkout_match_parent_dev(&pdev->dev, &mux_mask);
	अगर (ret)
		वापस ret;

	clkout->np = pdev->dev.of_node;
	अगर (!clkout->np) अणु
		/*
		 * pdev->dev.parent was checked by exynos_clkout_match_parent_dev()
		 * so it is not शून्य.
		 */
		clkout->np = pdev->dev.parent->of_node;
	पूर्ण

	platक्रमm_set_drvdata(pdev, clkout);

	spin_lock_init(&clkout->slock);

	parent_count = 0;
	क्रम (i = 0; i < EXYNOS_CLKOUT_PARENTS; ++i) अणु
		अक्षर name[] = "clkoutXX";

		snम_लिखो(name, माप(name), "clkout%d", i);
		parents[i] = of_clk_get_by_name(clkout->np, name);
		अगर (IS_ERR(parents[i])) अणु
			parent_names[i] = "none";
			जारी;
		पूर्ण

		parent_names[i] = __clk_get_name(parents[i]);
		parent_count = i + 1;
	पूर्ण

	अगर (!parent_count)
		वापस -EINVAL;

	clkout->reg = of_iomap(clkout->np, 0);
	अगर (!clkout->reg) अणु
		ret = -ENODEV;
		जाओ clks_put;
	पूर्ण

	clkout->gate.reg = clkout->reg + EXYNOS_PMU_DEBUG_REG;
	clkout->gate.bit_idx = EXYNOS_CLKOUT_DISABLE_SHIFT;
	clkout->gate.flags = CLK_GATE_SET_TO_DISABLE;
	clkout->gate.lock = &clkout->slock;

	clkout->mux.reg = clkout->reg + EXYNOS_PMU_DEBUG_REG;
	clkout->mux.mask = mux_mask;
	clkout->mux.shअगरt = EXYNOS_CLKOUT_MUX_SHIFT;
	clkout->mux.lock = &clkout->slock;

	clkout->data.hws[0] = clk_hw_रेजिस्टर_composite(शून्य, "clkout",
				parent_names, parent_count, &clkout->mux.hw,
				&clk_mux_ops, शून्य, शून्य, &clkout->gate.hw,
				&clk_gate_ops, CLK_SET_RATE_PARENT
				| CLK_SET_RATE_NO_REPARENT);
	अगर (IS_ERR(clkout->data.hws[0])) अणु
		ret = PTR_ERR(clkout->data.hws[0]);
		जाओ err_unmap;
	पूर्ण

	clkout->data.num = EXYNOS_CLKOUT_NR_CLKS;
	ret = of_clk_add_hw_provider(clkout->np, of_clk_hw_onecell_get, &clkout->data);
	अगर (ret)
		जाओ err_clk_unreg;

	वापस 0;

err_clk_unreg:
	clk_hw_unरेजिस्टर(clkout->data.hws[0]);
err_unmap:
	iounmap(clkout->reg);
clks_put:
	क्रम (i = 0; i < EXYNOS_CLKOUT_PARENTS; ++i)
		अगर (!IS_ERR(parents[i]))
			clk_put(parents[i]);

	dev_err(&pdev->dev, "failed to register clkout clock\n");

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_clkout_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_clkout *clkout = platक्रमm_get_drvdata(pdev);

	of_clk_del_provider(clkout->np);
	clk_hw_unरेजिस्टर(clkout->data.hws[0]);
	iounmap(clkout->reg);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_clkout_suspend(काष्ठा device *dev)
अणु
	काष्ठा exynos_clkout *clkout = dev_get_drvdata(dev);

	clkout->pmu_debug_save = पढ़ोl(clkout->reg + EXYNOS_PMU_DEBUG_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_clkout_resume(काष्ठा device *dev)
अणु
	काष्ठा exynos_clkout *clkout = dev_get_drvdata(dev);

	ग_लिखोl(clkout->pmu_debug_save, clkout->reg + EXYNOS_PMU_DEBUG_REG);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(exynos_clkout_pm_ops, exynos_clkout_suspend,
			 exynos_clkout_resume);

अटल काष्ठा platक्रमm_driver exynos_clkout_driver = अणु
	.driver = अणु
		.name = "exynos-clkout",
		.of_match_table = exynos_clkout_ids,
		.pm = &exynos_clkout_pm_ops,
	पूर्ण,
	.probe = exynos_clkout_probe,
	.हटाओ = exynos_clkout_हटाओ,
पूर्ण;
module_platक्रमm_driver(exynos_clkout_driver);

MODULE_AUTHOR("Krzysztof Kozlowski <krzk@kernel.org>");
MODULE_AUTHOR("Tomasz Figa <tomasz.figa@gmail.com>");
MODULE_DESCRIPTION("Samsung Exynos clock output driver");
MODULE_LICENSE("GPL");
