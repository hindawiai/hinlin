<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Actions Semi Owl Smart Power System (SPS)
 *
 * Copyright 2012 Actions Semi Inc.
 * Author: Actions Semi, Inc.
 *
 * Copyright (c) 2017 Andreas Fथअrber
 */

#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/soc/actions/owl-sps.h>
#समावेश <dt-bindings/घातer/owl-s500-घातergate.h>
#समावेश <dt-bindings/घातer/owl-s700-घातergate.h>
#समावेश <dt-bindings/घातer/owl-s900-घातergate.h>

काष्ठा owl_sps_करोमुख्य_info अणु
	स्थिर अक्षर *name;
	पूर्णांक pwr_bit;
	पूर्णांक ack_bit;
	अचिन्हित पूर्णांक genpd_flags;
पूर्ण;

काष्ठा owl_sps_info अणु
	अचिन्हित num_करोमुख्यs;
	स्थिर काष्ठा owl_sps_करोमुख्य_info *करोमुख्यs;
पूर्ण;

काष्ठा owl_sps अणु
	काष्ठा device *dev;
	स्थिर काष्ठा owl_sps_info *info;
	व्योम __iomem *base;
	काष्ठा genpd_onecell_data genpd_data;
	काष्ठा generic_pm_करोमुख्य *करोमुख्यs[];
पूर्ण;

#घोषणा to_owl_pd(gpd) container_of(gpd, काष्ठा owl_sps_करोमुख्य, genpd)

काष्ठा owl_sps_करोमुख्य अणु
	काष्ठा generic_pm_करोमुख्य genpd;
	स्थिर काष्ठा owl_sps_करोमुख्य_info *info;
	काष्ठा owl_sps *sps;
पूर्ण;

अटल पूर्णांक owl_sps_set_घातer(काष्ठा owl_sps_करोमुख्य *pd, bool enable)
अणु
	u32 pwr_mask, ack_mask;

	ack_mask = BIT(pd->info->ack_bit);
	pwr_mask = BIT(pd->info->pwr_bit);

	वापस owl_sps_set_pg(pd->sps->base, pwr_mask, ack_mask, enable);
पूर्ण

अटल पूर्णांक owl_sps_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा owl_sps_करोमुख्य *pd = to_owl_pd(करोमुख्य);

	dev_dbg(pd->sps->dev, "%s power on", pd->info->name);

	वापस owl_sps_set_घातer(pd, true);
पूर्ण

अटल पूर्णांक owl_sps_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा owl_sps_करोमुख्य *pd = to_owl_pd(करोमुख्य);

	dev_dbg(pd->sps->dev, "%s power off", pd->info->name);

	वापस owl_sps_set_घातer(pd, false);
पूर्ण

अटल पूर्णांक owl_sps_init_करोमुख्य(काष्ठा owl_sps *sps, पूर्णांक index)
अणु
	काष्ठा owl_sps_करोमुख्य *pd;

	pd = devm_kzalloc(sps->dev, माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस -ENOMEM;

	pd->info = &sps->info->करोमुख्यs[index];
	pd->sps = sps;

	pd->genpd.name = pd->info->name;
	pd->genpd.घातer_on = owl_sps_घातer_on;
	pd->genpd.घातer_off = owl_sps_घातer_off;
	pd->genpd.flags = pd->info->genpd_flags;
	pm_genpd_init(&pd->genpd, शून्य, false);

	sps->genpd_data.करोमुख्यs[index] = &pd->genpd;

	वापस 0;
पूर्ण

अटल पूर्णांक owl_sps_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा owl_sps_info *sps_info;
	काष्ठा owl_sps *sps;
	पूर्णांक i, ret;

	अगर (!pdev->dev.of_node) अणु
		dev_err(&pdev->dev, "no device node\n");
		वापस -ENODEV;
	पूर्ण

	match = of_match_device(pdev->dev.driver->of_match_table, &pdev->dev);
	अगर (!match || !match->data) अणु
		dev_err(&pdev->dev, "unknown compatible or missing data\n");
		वापस -EINVAL;
	पूर्ण

	sps_info = match->data;

	sps = devm_kzalloc(&pdev->dev,
			   काष्ठा_size(sps, करोमुख्यs, sps_info->num_करोमुख्यs),
			   GFP_KERNEL);
	अगर (!sps)
		वापस -ENOMEM;

	sps->base = of_io_request_and_map(pdev->dev.of_node, 0, "owl-sps");
	अगर (IS_ERR(sps->base)) अणु
		dev_err(&pdev->dev, "failed to map sps registers\n");
		वापस PTR_ERR(sps->base);
	पूर्ण

	sps->dev = &pdev->dev;
	sps->info = sps_info;
	sps->genpd_data.करोमुख्यs = sps->करोमुख्यs;
	sps->genpd_data.num_करोमुख्यs = sps_info->num_करोमुख्यs;

	क्रम (i = 0; i < sps_info->num_करोमुख्यs; i++) अणु
		ret = owl_sps_init_करोमुख्य(sps, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = of_genpd_add_provider_onecell(pdev->dev.of_node, &sps->genpd_data);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add provider (%d)", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा owl_sps_करोमुख्य_info s500_sps_करोमुख्यs[] = अणु
	[S500_PD_VDE] = अणु
		.name = "VDE",
		.pwr_bit = 0,
		.ack_bit = 16,
	पूर्ण,
	[S500_PD_VCE_SI] = अणु
		.name = "VCE_SI",
		.pwr_bit = 1,
		.ack_bit = 17,
	पूर्ण,
	[S500_PD_USB2_1] = अणु
		.name = "USB2_1",
		.pwr_bit = 2,
		.ack_bit = 18,
	पूर्ण,
	[S500_PD_CPU2] = अणु
		.name = "CPU2",
		.pwr_bit = 5,
		.ack_bit = 21,
		.genpd_flags = GENPD_FLAG_ALWAYS_ON,
	पूर्ण,
	[S500_PD_CPU3] = अणु
		.name = "CPU3",
		.pwr_bit = 6,
		.ack_bit = 22,
		.genpd_flags = GENPD_FLAG_ALWAYS_ON,
	पूर्ण,
	[S500_PD_DMA] = अणु
		.name = "DMA",
		.pwr_bit = 8,
		.ack_bit = 12,
	पूर्ण,
	[S500_PD_DS] = अणु
		.name = "DS",
		.pwr_bit = 9,
		.ack_bit = 13,
	पूर्ण,
	[S500_PD_USB3] = अणु
		.name = "USB3",
		.pwr_bit = 10,
		.ack_bit = 14,
	पूर्ण,
	[S500_PD_USB2_0] = अणु
		.name = "USB2_0",
		.pwr_bit = 11,
		.ack_bit = 15,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा owl_sps_info s500_sps_info = अणु
	.num_करोमुख्यs = ARRAY_SIZE(s500_sps_करोमुख्यs),
	.करोमुख्यs = s500_sps_करोमुख्यs,
पूर्ण;

अटल स्थिर काष्ठा owl_sps_करोमुख्य_info s700_sps_करोमुख्यs[] = अणु
	[S700_PD_VDE] = अणु
		.name = "VDE",
		.pwr_bit = 0,
	पूर्ण,
	[S700_PD_VCE_SI] = अणु
		.name = "VCE_SI",
		.pwr_bit = 1,
	पूर्ण,
	[S700_PD_USB2_1] = अणु
		.name = "USB2_1",
		.pwr_bit = 2,
	पूर्ण,
	[S700_PD_HDE] = अणु
		.name = "HDE",
		.pwr_bit = 7,
	पूर्ण,
	[S700_PD_DMA] = अणु
		.name = "DMA",
		.pwr_bit = 8,
	पूर्ण,
	[S700_PD_DS] = अणु
		.name = "DS",
		.pwr_bit = 9,
	पूर्ण,
	[S700_PD_USB3] = अणु
		.name = "USB3",
		.pwr_bit = 10,
	पूर्ण,
	[S700_PD_USB2_0] = अणु
		.name = "USB2_0",
		.pwr_bit = 11,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा owl_sps_info s700_sps_info = अणु
	.num_करोमुख्यs = ARRAY_SIZE(s700_sps_करोमुख्यs),
	.करोमुख्यs = s700_sps_करोमुख्यs,
पूर्ण;

अटल स्थिर काष्ठा owl_sps_करोमुख्य_info s900_sps_करोमुख्यs[] = अणु
	[S900_PD_GPU_B] = अणु
		.name = "GPU_B",
		.pwr_bit = 3,
	पूर्ण,
	[S900_PD_VCE] = अणु
		.name = "VCE",
		.pwr_bit = 4,
	पूर्ण,
	[S900_PD_SENSOR] = अणु
		.name = "SENSOR",
		.pwr_bit = 5,
	पूर्ण,
	[S900_PD_VDE] = अणु
		.name = "VDE",
		.pwr_bit = 6,
	पूर्ण,
	[S900_PD_HDE] = अणु
		.name = "HDE",
		.pwr_bit = 7,
	पूर्ण,
	[S900_PD_USB3] = अणु
		.name = "USB3",
		.pwr_bit = 8,
	पूर्ण,
	[S900_PD_DDR0] = अणु
		.name = "DDR0",
		.pwr_bit = 9,
	पूर्ण,
	[S900_PD_DDR1] = अणु
		.name = "DDR1",
		.pwr_bit = 10,
	पूर्ण,
	[S900_PD_DE] = अणु
		.name = "DE",
		.pwr_bit = 13,
	पूर्ण,
	[S900_PD_न_अंकD] = अणु
		.name = "NAND",
		.pwr_bit = 14,
	पूर्ण,
	[S900_PD_USB2_H0] = अणु
		.name = "USB2_H0",
		.pwr_bit = 15,
	पूर्ण,
	[S900_PD_USB2_H1] = अणु
		.name = "USB2_H1",
		.pwr_bit = 16,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा owl_sps_info s900_sps_info = अणु
	.num_करोमुख्यs = ARRAY_SIZE(s900_sps_करोमुख्यs),
	.करोमुख्यs = s900_sps_करोमुख्यs,
पूर्ण;

अटल स्थिर काष्ठा of_device_id owl_sps_of_matches[] = अणु
	अणु .compatible = "actions,s500-sps", .data = &s500_sps_info पूर्ण,
	अणु .compatible = "actions,s700-sps", .data = &s700_sps_info पूर्ण,
	अणु .compatible = "actions,s900-sps", .data = &s900_sps_info पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver owl_sps_platक्रमm_driver = अणु
	.probe = owl_sps_probe,
	.driver = अणु
		.name = "owl-sps",
		.of_match_table = owl_sps_of_matches,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init owl_sps_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&owl_sps_platक्रमm_driver);
पूर्ण
postcore_initcall(owl_sps_init);
