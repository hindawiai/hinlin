<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Exynos Generic घातer करोमुख्य support.
//
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
//		http://www.samsung.com
//
// Implementation of Exynos specअगरic घातer करोमुख्य control which is used in
// conjunction with runसमय-pm. Support क्रम both device-tree and non-device-tree
// based घातer करोमुख्य support is included.

#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>

काष्ठा exynos_pm_करोमुख्य_config अणु
	/* Value क्रम LOCAL_PWR_CFG and STATUS fields क्रम each करोमुख्य */
	u32 local_pwr_cfg;
पूर्ण;

/*
 * Exynos specअगरic wrapper around the generic घातer करोमुख्य
 */
काष्ठा exynos_pm_करोमुख्य अणु
	व्योम __iomem *base;
	bool is_off;
	काष्ठा generic_pm_करोमुख्य pd;
	u32 local_pwr_cfg;
पूर्ण;

अटल पूर्णांक exynos_pd_घातer(काष्ठा generic_pm_करोमुख्य *करोमुख्य, bool घातer_on)
अणु
	काष्ठा exynos_pm_करोमुख्य *pd;
	व्योम __iomem *base;
	u32 समयout, pwr;
	अक्षर *op;

	pd = container_of(करोमुख्य, काष्ठा exynos_pm_करोमुख्य, pd);
	base = pd->base;

	pwr = घातer_on ? pd->local_pwr_cfg : 0;
	ग_लिखोl_relaxed(pwr, base);

	/* Wait max 1ms */
	समयout = 10;

	जबतक ((पढ़ोl_relaxed(base + 0x4) & pd->local_pwr_cfg) != pwr) अणु
		अगर (!समयout) अणु
			op = (घातer_on) ? "enable" : "disable";
			pr_err("Power domain %s %s failed\n", करोमुख्य->name, op);
			वापस -ETIMEDOUT;
		पूर्ण
		समयout--;
		cpu_relax();
		usleep_range(80, 100);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_pd_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	वापस exynos_pd_घातer(करोमुख्य, true);
पूर्ण

अटल पूर्णांक exynos_pd_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	वापस exynos_pd_घातer(करोमुख्य, false);
पूर्ण

अटल स्थिर काष्ठा exynos_pm_करोमुख्य_config exynos4210_cfg = अणु
	.local_pwr_cfg		= 0x7,
पूर्ण;

अटल स्थिर काष्ठा exynos_pm_करोमुख्य_config exynos5433_cfg = अणु
	.local_pwr_cfg		= 0xf,
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_pm_करोमुख्य_of_match[] = अणु
	अणु
		.compatible = "samsung,exynos4210-pd",
		.data = &exynos4210_cfg,
	पूर्ण, अणु
		.compatible = "samsung,exynos5433-pd",
		.data = &exynos5433_cfg,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *exynos_get_करोमुख्य_name(काष्ठा device_node *node)
अणु
	स्थिर अक्षर *name;

	अगर (of_property_पढ़ो_string(node, "label", &name) < 0)
		name = kbasename(node->full_name);
	वापस kstrdup_स्थिर(name, GFP_KERNEL);
पूर्ण

अटल पूर्णांक exynos_pd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा exynos_pm_करोमुख्य_config *pm_करोमुख्य_cfg;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा of_phandle_args child, parent;
	काष्ठा exynos_pm_करोमुख्य *pd;
	पूर्णांक on, ret;

	pm_करोमुख्य_cfg = of_device_get_match_data(dev);
	pd = devm_kzalloc(dev, माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस -ENOMEM;

	pd->pd.name = exynos_get_करोमुख्य_name(np);
	अगर (!pd->pd.name)
		वापस -ENOMEM;

	pd->base = of_iomap(np, 0);
	अगर (!pd->base) अणु
		kमुक्त_स्थिर(pd->pd.name);
		वापस -ENODEV;
	पूर्ण

	pd->pd.घातer_off = exynos_pd_घातer_off;
	pd->pd.घातer_on = exynos_pd_घातer_on;
	pd->local_pwr_cfg = pm_करोमुख्य_cfg->local_pwr_cfg;

	on = पढ़ोl_relaxed(pd->base + 0x4) & pd->local_pwr_cfg;

	pm_genpd_init(&pd->pd, शून्य, !on);
	ret = of_genpd_add_provider_simple(np, &pd->pd);

	अगर (ret == 0 && of_parse_phandle_with_args(np, "power-domains",
				      "#power-domain-cells", 0, &parent) == 0) अणु
		child.np = np;
		child.args_count = 0;

		अगर (of_genpd_add_subकरोमुख्य(&parent, &child))
			pr_warn("%pOF failed to add subdomain: %pOF\n",
				parent.np, child.np);
		अन्यथा
			pr_info("%pOF has as child subdomain: %pOF.\n",
				parent.np, child.np);
	पूर्ण

	pm_runसमय_enable(dev);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver exynos_pd_driver = अणु
	.probe	= exynos_pd_probe,
	.driver	= अणु
		.name		= "exynos-pd",
		.of_match_table	= exynos_pm_करोमुख्य_of_match,
		.suppress_bind_attrs = true,
	पूर्ण
पूर्ण;

अटल __init पूर्णांक exynos4_pm_init_घातer_करोमुख्य(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&exynos_pd_driver);
पूर्ण
core_initcall(exynos4_pm_init_घातer_करोमुख्य);
