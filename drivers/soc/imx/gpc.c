<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2015-2017 Pengutronix, Lucas Stach <kernel@pengutronix.de>
 * Copyright 2011-2013 Freescale Semiconductor, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा GPC_CNTR		0x000

#घोषणा GPC_PGC_CTRL_OFFS	0x0
#घोषणा GPC_PGC_PUPSCR_OFFS	0x4
#घोषणा GPC_PGC_PDNSCR_OFFS	0x8
#घोषणा GPC_PGC_SW2ISO_SHIFT	0x8
#घोषणा GPC_PGC_SW_SHIFT	0x0

#घोषणा GPC_PGC_PCI_PDN		0x200
#घोषणा GPC_PGC_PCI_SR		0x20c

#घोषणा GPC_PGC_GPU_PDN		0x260
#घोषणा GPC_PGC_GPU_PUPSCR	0x264
#घोषणा GPC_PGC_GPU_PDNSCR	0x268
#घोषणा GPC_PGC_GPU_SR		0x26c

#घोषणा GPC_PGC_DISP_PDN	0x240
#घोषणा GPC_PGC_DISP_SR		0x24c

#घोषणा GPU_VPU_PUP_REQ		BIT(1)
#घोषणा GPU_VPU_PDN_REQ		BIT(0)

#घोषणा GPC_CLK_MAX		7

#घोषणा PGC_DOMAIN_FLAG_NO_PD		BIT(0)

काष्ठा imx_pm_करोमुख्य अणु
	काष्ठा generic_pm_करोमुख्य base;
	काष्ठा regmap *regmap;
	काष्ठा regulator *supply;
	काष्ठा clk *clk[GPC_CLK_MAX];
	पूर्णांक num_clks;
	अचिन्हित पूर्णांक reg_offs;
	चिन्हित अक्षर cntr_pdn_bit;
	अचिन्हित पूर्णांक ipg_rate_mhz;
पूर्ण;

अटल अंतरभूत काष्ठा imx_pm_करोमुख्य *
to_imx_pm_करोमुख्य(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	वापस container_of(genpd, काष्ठा imx_pm_करोमुख्य, base);
पूर्ण

अटल पूर्णांक imx6_pm_करोमुख्य_घातer_off(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा imx_pm_करोमुख्य *pd = to_imx_pm_करोमुख्य(genpd);
	पूर्णांक iso, iso2sw;
	u32 val;

	/* Read ISO and ISO2SW घातer करोwn delays */
	regmap_पढ़ो(pd->regmap, pd->reg_offs + GPC_PGC_PDNSCR_OFFS, &val);
	iso = val & 0x3f;
	iso2sw = (val >> 8) & 0x3f;

	/* Gate off करोमुख्य when घातered करोwn */
	regmap_update_bits(pd->regmap, pd->reg_offs + GPC_PGC_CTRL_OFFS,
			   0x1, 0x1);

	/* Request GPC to घातer करोwn करोमुख्य */
	val = BIT(pd->cntr_pdn_bit);
	regmap_update_bits(pd->regmap, GPC_CNTR, val, val);

	/* Wait ISO + ISO2SW IPG घड़ी cycles */
	udelay(DIV_ROUND_UP(iso + iso2sw, pd->ipg_rate_mhz));

	अगर (pd->supply)
		regulator_disable(pd->supply);

	वापस 0;
पूर्ण

अटल पूर्णांक imx6_pm_करोमुख्य_घातer_on(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा imx_pm_करोमुख्य *pd = to_imx_pm_करोमुख्य(genpd);
	पूर्णांक i, ret;
	u32 val, req;

	अगर (pd->supply) अणु
		ret = regulator_enable(pd->supply);
		अगर (ret) अणु
			pr_err("%s: failed to enable regulator: %d\n",
			       __func__, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Enable reset घड़ीs क्रम all devices in the करोमुख्य */
	क्रम (i = 0; i < pd->num_clks; i++)
		clk_prepare_enable(pd->clk[i]);

	/* Gate off करोमुख्य when घातered करोwn */
	regmap_update_bits(pd->regmap, pd->reg_offs + GPC_PGC_CTRL_OFFS,
			   0x1, 0x1);

	/* Request GPC to घातer up करोमुख्य */
	req = BIT(pd->cntr_pdn_bit + 1);
	regmap_update_bits(pd->regmap, GPC_CNTR, req, req);

	/* Wait क्रम the PGC to handle the request */
	ret = regmap_पढ़ो_poll_समयout(pd->regmap, GPC_CNTR, val, !(val & req),
				       1, 50);
	अगर (ret)
		pr_err("powerup request on domain %s timed out\n", genpd->name);

	/* Wait क्रम reset to propagate through peripherals */
	usleep_range(5, 10);

	/* Disable reset घड़ीs क्रम all devices in the करोमुख्य */
	क्रम (i = 0; i < pd->num_clks; i++)
		clk_disable_unprepare(pd->clk[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_pgc_get_घड़ीs(काष्ठा device *dev, काष्ठा imx_pm_करोमुख्य *करोमुख्य)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; ; i++) अणु
		काष्ठा clk *clk = of_clk_get(dev->of_node, i);
		अगर (IS_ERR(clk))
			अवरोध;
		अगर (i >= GPC_CLK_MAX) अणु
			dev_err(dev, "more than %d clocks\n", GPC_CLK_MAX);
			ret = -EINVAL;
			जाओ clk_err;
		पूर्ण
		करोमुख्य->clk[i] = clk;
	पूर्ण
	करोमुख्य->num_clks = i;

	वापस 0;

clk_err:
	जबतक (i--)
		clk_put(करोमुख्य->clk[i]);

	वापस ret;
पूर्ण

अटल व्योम imx_pgc_put_घड़ीs(काष्ठा imx_pm_करोमुख्य *करोमुख्य)
अणु
	पूर्णांक i;

	क्रम (i = करोमुख्य->num_clks - 1; i >= 0; i--)
		clk_put(करोमुख्य->clk[i]);
पूर्ण

अटल पूर्णांक imx_pgc_parse_dt(काष्ठा device *dev, काष्ठा imx_pm_करोमुख्य *करोमुख्य)
अणु
	/* try to get the करोमुख्य supply regulator */
	करोमुख्य->supply = devm_regulator_get_optional(dev, "power");
	अगर (IS_ERR(करोमुख्य->supply)) अणु
		अगर (PTR_ERR(करोमुख्य->supply) == -ENODEV)
			करोमुख्य->supply = शून्य;
		अन्यथा
			वापस PTR_ERR(करोमुख्य->supply);
	पूर्ण

	/* try to get all घड़ीs needed क्रम reset propagation */
	वापस imx_pgc_get_घड़ीs(dev, करोमुख्य);
पूर्ण

अटल पूर्णांक imx_pgc_घातer_करोमुख्य_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_pm_करोमुख्य *करोमुख्य = pdev->dev.platक्रमm_data;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	/* अगर this PD is associated with a DT node try to parse it */
	अगर (dev->of_node) अणु
		ret = imx_pgc_parse_dt(dev, करोमुख्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* initially घातer on the करोमुख्य */
	अगर (करोमुख्य->base.घातer_on)
		करोमुख्य->base.घातer_on(&करोमुख्य->base);

	अगर (IS_ENABLED(CONFIG_PM_GENERIC_DOMAINS)) अणु
		pm_genpd_init(&करोमुख्य->base, शून्य, false);
		ret = of_genpd_add_provider_simple(dev->of_node, &करोमुख्य->base);
		अगर (ret)
			जाओ genpd_err;
	पूर्ण

	device_link_add(dev, dev->parent, DL_FLAG_AUTOREMOVE_CONSUMER);

	वापस 0;

genpd_err:
	pm_genpd_हटाओ(&करोमुख्य->base);
	imx_pgc_put_घड़ीs(करोमुख्य);

	वापस ret;
पूर्ण

अटल पूर्णांक imx_pgc_घातer_करोमुख्य_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_pm_करोमुख्य *करोमुख्य = pdev->dev.platक्रमm_data;

	अगर (IS_ENABLED(CONFIG_PM_GENERIC_DOMAINS)) अणु
		of_genpd_del_provider(pdev->dev.of_node);
		pm_genpd_हटाओ(&करोमुख्य->base);
		imx_pgc_put_घड़ीs(करोमुख्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id imx_pgc_घातer_करोमुख्य_id[] = अणु
	अणु "imx-pgc-power-domain"पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver imx_pgc_घातer_करोमुख्य_driver = अणु
	.driver = अणु
		.name = "imx-pgc-pd",
	पूर्ण,
	.probe = imx_pgc_घातer_करोमुख्य_probe,
	.हटाओ = imx_pgc_घातer_करोमुख्य_हटाओ,
	.id_table = imx_pgc_घातer_करोमुख्य_id,
पूर्ण;
builtin_platक्रमm_driver(imx_pgc_घातer_करोमुख्य_driver)

#घोषणा GPC_PGC_DOMAIN_ARM	0
#घोषणा GPC_PGC_DOMAIN_PU	1
#घोषणा GPC_PGC_DOMAIN_DISPLAY	2
#घोषणा GPC_PGC_DOMAIN_PCI	3

अटल काष्ठा genpd_घातer_state imx6_pm_करोमुख्य_pu_state = अणु
	.घातer_off_latency_ns = 25000,
	.घातer_on_latency_ns = 2000000,
पूर्ण;

अटल काष्ठा imx_pm_करोमुख्य imx_gpc_करोमुख्यs[] = अणु
	[GPC_PGC_DOMAIN_ARM] = अणु
		.base = अणु
			.name = "ARM",
			.flags = GENPD_FLAG_ALWAYS_ON,
		पूर्ण,
	पूर्ण,
	[GPC_PGC_DOMAIN_PU] = अणु
		.base = अणु
			.name = "PU",
			.घातer_off = imx6_pm_करोमुख्य_घातer_off,
			.घातer_on = imx6_pm_करोमुख्य_घातer_on,
			.states = &imx6_pm_करोमुख्य_pu_state,
			.state_count = 1,
		पूर्ण,
		.reg_offs = 0x260,
		.cntr_pdn_bit = 0,
	पूर्ण,
	[GPC_PGC_DOMAIN_DISPLAY] = अणु
		.base = अणु
			.name = "DISPLAY",
			.घातer_off = imx6_pm_करोमुख्य_घातer_off,
			.घातer_on = imx6_pm_करोमुख्य_घातer_on,
		पूर्ण,
		.reg_offs = 0x240,
		.cntr_pdn_bit = 4,
	पूर्ण,
	[GPC_PGC_DOMAIN_PCI] = अणु
		.base = अणु
			.name = "PCI",
			.घातer_off = imx6_pm_करोमुख्य_घातer_off,
			.घातer_on = imx6_pm_करोमुख्य_घातer_on,
		पूर्ण,
		.reg_offs = 0x200,
		.cntr_pdn_bit = 6,
	पूर्ण,
पूर्ण;

काष्ठा imx_gpc_dt_data अणु
	पूर्णांक num_करोमुख्यs;
	bool err009619_present;
	bool err006287_present;
पूर्ण;

अटल स्थिर काष्ठा imx_gpc_dt_data imx6q_dt_data = अणु
	.num_करोमुख्यs = 2,
	.err009619_present = false,
	.err006287_present = false,
पूर्ण;

अटल स्थिर काष्ठा imx_gpc_dt_data imx6qp_dt_data = अणु
	.num_करोमुख्यs = 2,
	.err009619_present = true,
	.err006287_present = false,
पूर्ण;

अटल स्थिर काष्ठा imx_gpc_dt_data imx6sl_dt_data = अणु
	.num_करोमुख्यs = 3,
	.err009619_present = false,
	.err006287_present = true,
पूर्ण;

अटल स्थिर काष्ठा imx_gpc_dt_data imx6sx_dt_data = अणु
	.num_करोमुख्यs = 4,
	.err009619_present = false,
	.err006287_present = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx_gpc_dt_ids[] = अणु
	अणु .compatible = "fsl,imx6q-gpc", .data = &imx6q_dt_data पूर्ण,
	अणु .compatible = "fsl,imx6qp-gpc", .data = &imx6qp_dt_data पूर्ण,
	अणु .compatible = "fsl,imx6sl-gpc", .data = &imx6sl_dt_data पूर्ण,
	अणु .compatible = "fsl,imx6sx-gpc", .data = &imx6sx_dt_data पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा regmap_range yes_ranges[] = अणु
	regmap_reg_range(GPC_CNTR, GPC_CNTR),
	regmap_reg_range(GPC_PGC_PCI_PDN, GPC_PGC_PCI_SR),
	regmap_reg_range(GPC_PGC_GPU_PDN, GPC_PGC_GPU_SR),
	regmap_reg_range(GPC_PGC_DISP_PDN, GPC_PGC_DISP_SR),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table access_table = अणु
	.yes_ranges	= yes_ranges,
	.n_yes_ranges	= ARRAY_SIZE(yes_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config imx_gpc_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.rd_table = &access_table,
	.wr_table = &access_table,
	.max_रेजिस्टर = 0x2ac,
	.fast_io = true,
पूर्ण;

अटल काष्ठा generic_pm_करोमुख्य *imx_gpc_onecell_करोमुख्यs[] = अणु
	&imx_gpc_करोमुख्यs[GPC_PGC_DOMAIN_ARM].base,
	&imx_gpc_करोमुख्यs[GPC_PGC_DOMAIN_PU].base,
पूर्ण;

अटल काष्ठा genpd_onecell_data imx_gpc_onecell_data = अणु
	.करोमुख्यs = imx_gpc_onecell_करोमुख्यs,
	.num_करोमुख्यs = 2,
पूर्ण;

अटल पूर्णांक imx_gpc_old_dt_init(काष्ठा device *dev, काष्ठा regmap *regmap,
			       अचिन्हित पूर्णांक num_करोमुख्यs)
अणु
	काष्ठा imx_pm_करोमुख्य *करोमुख्य;
	पूर्णांक i, ret;

	क्रम (i = 0; i < num_करोमुख्यs; i++) अणु
		करोमुख्य = &imx_gpc_करोमुख्यs[i];
		करोमुख्य->regmap = regmap;
		करोमुख्य->ipg_rate_mhz = 66;

		अगर (i == 1) अणु
			करोमुख्य->supply = devm_regulator_get(dev, "pu");
			अगर (IS_ERR(करोमुख्य->supply))
				वापस PTR_ERR(करोमुख्य->supply);

			ret = imx_pgc_get_घड़ीs(dev, करोमुख्य);
			अगर (ret)
				जाओ clk_err;

			करोमुख्य->base.घातer_on(&करोमुख्य->base);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_करोमुख्यs; i++)
		pm_genpd_init(&imx_gpc_करोमुख्यs[i].base, शून्य, false);

	अगर (IS_ENABLED(CONFIG_PM_GENERIC_DOMAINS)) अणु
		ret = of_genpd_add_provider_onecell(dev->of_node,
						    &imx_gpc_onecell_data);
		अगर (ret)
			जाओ genpd_err;
	पूर्ण

	वापस 0;

genpd_err:
	क्रम (i = 0; i < num_करोमुख्यs; i++)
		pm_genpd_हटाओ(&imx_gpc_करोमुख्यs[i].base);
	imx_pgc_put_घड़ीs(&imx_gpc_करोमुख्यs[GPC_PGC_DOMAIN_PU]);
clk_err:
	वापस ret;
पूर्ण

अटल पूर्णांक imx_gpc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *of_id =
			of_match_device(imx_gpc_dt_ids, &pdev->dev);
	स्थिर काष्ठा imx_gpc_dt_data *of_id_data = of_id->data;
	काष्ठा device_node *pgc_node;
	काष्ठा regmap *regmap;
	व्योम __iomem *base;
	पूर्णांक ret;

	pgc_node = of_get_child_by_name(pdev->dev.of_node, "pgc");

	/* bail out अगर DT too old and करोesn't provide the necessary info */
	अगर (!of_property_पढ़ो_bool(pdev->dev.of_node, "#power-domain-cells") &&
	    !pgc_node)
		वापस 0;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio_clk(&pdev->dev, शून्य, base,
					   &imx_gpc_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(&pdev->dev, "failed to init regmap: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/*
	 * Disable PU घातer करोwn by runसमय PM अगर ERR009619 is present.
	 *
	 * The PRE घड़ी will be छोड़ोd क्रम several cycles when turning on the
	 * PU करोमुख्य LDO from घातer करोwn state. If PRE is in use at that समय,
	 * the IPU/PRG cannot get the correct display data from the PRE.
	 *
	 * This is not a concern when the whole प्रणाली enters suspend state, so
	 * it's safe to घातer करोwn PU in this हाल.
	 */
	अगर (of_id_data->err009619_present)
		imx_gpc_करोमुख्यs[GPC_PGC_DOMAIN_PU].base.flags |=
				GENPD_FLAG_RPM_ALWAYS_ON;

	/* Keep DISP always on अगर ERR006287 is present */
	अगर (of_id_data->err006287_present)
		imx_gpc_करोमुख्यs[GPC_PGC_DOMAIN_DISPLAY].base.flags |=
				GENPD_FLAG_ALWAYS_ON;

	अगर (!pgc_node) अणु
		ret = imx_gpc_old_dt_init(&pdev->dev, regmap,
					  of_id_data->num_करोमुख्यs);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		काष्ठा imx_pm_करोमुख्य *करोमुख्य;
		काष्ठा platक्रमm_device *pd_pdev;
		काष्ठा device_node *np;
		काष्ठा clk *ipg_clk;
		अचिन्हित पूर्णांक ipg_rate_mhz;
		पूर्णांक करोमुख्य_index;

		ipg_clk = devm_clk_get(&pdev->dev, "ipg");
		अगर (IS_ERR(ipg_clk))
			वापस PTR_ERR(ipg_clk);
		ipg_rate_mhz = clk_get_rate(ipg_clk) / 1000000;

		क्रम_each_child_of_node(pgc_node, np) अणु
			ret = of_property_पढ़ो_u32(np, "reg", &करोमुख्य_index);
			अगर (ret) अणु
				of_node_put(np);
				वापस ret;
			पूर्ण
			अगर (करोमुख्य_index >= of_id_data->num_करोमुख्यs)
				जारी;

			pd_pdev = platक्रमm_device_alloc("imx-pgc-power-domain",
							करोमुख्य_index);
			अगर (!pd_pdev) अणु
				of_node_put(np);
				वापस -ENOMEM;
			पूर्ण

			ret = platक्रमm_device_add_data(pd_pdev,
						       &imx_gpc_करोमुख्यs[करोमुख्य_index],
						       माप(imx_gpc_करोमुख्यs[करोमुख्य_index]));
			अगर (ret) अणु
				platक्रमm_device_put(pd_pdev);
				of_node_put(np);
				वापस ret;
			पूर्ण
			करोमुख्य = pd_pdev->dev.platक्रमm_data;
			करोमुख्य->regmap = regmap;
			करोमुख्य->ipg_rate_mhz = ipg_rate_mhz;

			pd_pdev->dev.parent = &pdev->dev;
			pd_pdev->dev.of_node = np;

			ret = platक्रमm_device_add(pd_pdev);
			अगर (ret) अणु
				platक्रमm_device_put(pd_pdev);
				of_node_put(np);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx_gpc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *pgc_node;
	पूर्णांक ret;

	pgc_node = of_get_child_by_name(pdev->dev.of_node, "pgc");

	/* bail out अगर DT too old and करोesn't provide the necessary info */
	अगर (!of_property_पढ़ो_bool(pdev->dev.of_node, "#power-domain-cells") &&
	    !pgc_node)
		वापस 0;

	/*
	 * If the old DT binding is used the toplevel driver needs to
	 * de-रेजिस्टर the घातer करोमुख्यs
	 */
	अगर (!pgc_node) अणु
		of_genpd_del_provider(pdev->dev.of_node);

		ret = pm_genpd_हटाओ(&imx_gpc_करोमुख्यs[GPC_PGC_DOMAIN_PU].base);
		अगर (ret)
			वापस ret;
		imx_pgc_put_घड़ीs(&imx_gpc_करोमुख्यs[GPC_PGC_DOMAIN_PU]);

		ret = pm_genpd_हटाओ(&imx_gpc_करोमुख्यs[GPC_PGC_DOMAIN_ARM].base);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver imx_gpc_driver = अणु
	.driver = अणु
		.name = "imx-gpc",
		.of_match_table = imx_gpc_dt_ids,
	पूर्ण,
	.probe = imx_gpc_probe,
	.हटाओ = imx_gpc_हटाओ,
पूर्ण;
builtin_platक्रमm_driver(imx_gpc_driver)
