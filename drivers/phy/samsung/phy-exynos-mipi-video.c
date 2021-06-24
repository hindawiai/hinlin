<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung S5P/Exynos SoC series MIPI CSIS/DSIM DPHY driver
 *
 * Copyright (C) 2013,2016 Samsung Electronics Co., Ltd.
 * Author: Sylwester Nawrocki <s.nawrocki@samsung.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/soc/samsung/exynos-regs-pmu.h>
#समावेश <linux/mfd/syscon.h>

क्रमागत exynos_mipi_phy_id अणु
	EXYNOS_MIPI_PHY_ID_NONE = -1,
	EXYNOS_MIPI_PHY_ID_CSIS0,
	EXYNOS_MIPI_PHY_ID_DSIM0,
	EXYNOS_MIPI_PHY_ID_CSIS1,
	EXYNOS_MIPI_PHY_ID_DSIM1,
	EXYNOS_MIPI_PHY_ID_CSIS2,
	EXYNOS_MIPI_PHYS_NUM
पूर्ण;

क्रमागत exynos_mipi_phy_regmap_id अणु
	EXYNOS_MIPI_REGMAP_PMU,
	EXYNOS_MIPI_REGMAP_DISP,
	EXYNOS_MIPI_REGMAP_CAM0,
	EXYNOS_MIPI_REGMAP_CAM1,
	EXYNOS_MIPI_REGMAPS_NUM
पूर्ण;

काष्ठा mipi_phy_device_desc अणु
	पूर्णांक num_phys;
	पूर्णांक num_regmaps;
	स्थिर अक्षर *regmap_names[EXYNOS_MIPI_REGMAPS_NUM];
	काष्ठा exynos_mipi_phy_desc अणु
		क्रमागत exynos_mipi_phy_id	coupled_phy_id;
		u32 enable_val;
		अचिन्हित पूर्णांक enable_reg;
		क्रमागत exynos_mipi_phy_regmap_id enable_map;
		u32 resetn_val;
		अचिन्हित पूर्णांक resetn_reg;
		क्रमागत exynos_mipi_phy_regmap_id resetn_map;
	पूर्ण phys[EXYNOS_MIPI_PHYS_NUM];
पूर्ण;

अटल स्थिर काष्ठा mipi_phy_device_desc s5pv210_mipi_phy = अणु
	.num_regmaps = 1,
	.regmap_names = अणु"syscon"पूर्ण,
	.num_phys = 4,
	.phys = अणु
		अणु
			/* EXYNOS_MIPI_PHY_ID_CSIS0 */
			.coupled_phy_id = EXYNOS_MIPI_PHY_ID_DSIM0,
			.enable_val = EXYNOS4_PHY_ENABLE,
			.enable_reg = EXYNOS4_MIPI_PHY_CONTROL(0),
			.enable_map = EXYNOS_MIPI_REGMAP_PMU,
			.resetn_val = EXYNOS4_MIPI_PHY_SRESETN,
			.resetn_reg = EXYNOS4_MIPI_PHY_CONTROL(0),
			.resetn_map = EXYNOS_MIPI_REGMAP_PMU,
		पूर्ण, अणु
			/* EXYNOS_MIPI_PHY_ID_DSIM0 */
			.coupled_phy_id = EXYNOS_MIPI_PHY_ID_CSIS0,
			.enable_val = EXYNOS4_PHY_ENABLE,
			.enable_reg = EXYNOS4_MIPI_PHY_CONTROL(0),
			.enable_map = EXYNOS_MIPI_REGMAP_PMU,
			.resetn_val = EXYNOS4_MIPI_PHY_MRESETN,
			.resetn_reg = EXYNOS4_MIPI_PHY_CONTROL(0),
			.resetn_map = EXYNOS_MIPI_REGMAP_PMU,
		पूर्ण, अणु
			/* EXYNOS_MIPI_PHY_ID_CSIS1 */
			.coupled_phy_id = EXYNOS_MIPI_PHY_ID_DSIM1,
			.enable_val = EXYNOS4_PHY_ENABLE,
			.enable_reg = EXYNOS4_MIPI_PHY_CONTROL(1),
			.enable_map = EXYNOS_MIPI_REGMAP_PMU,
			.resetn_val = EXYNOS4_MIPI_PHY_SRESETN,
			.resetn_reg = EXYNOS4_MIPI_PHY_CONTROL(1),
			.resetn_map = EXYNOS_MIPI_REGMAP_PMU,
		पूर्ण, अणु
			/* EXYNOS_MIPI_PHY_ID_DSIM1 */
			.coupled_phy_id = EXYNOS_MIPI_PHY_ID_CSIS1,
			.enable_val = EXYNOS4_PHY_ENABLE,
			.enable_reg = EXYNOS4_MIPI_PHY_CONTROL(1),
			.enable_map = EXYNOS_MIPI_REGMAP_PMU,
			.resetn_val = EXYNOS4_MIPI_PHY_MRESETN,
			.resetn_reg = EXYNOS4_MIPI_PHY_CONTROL(1),
			.resetn_map = EXYNOS_MIPI_REGMAP_PMU,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mipi_phy_device_desc exynos5420_mipi_phy = अणु
	.num_regmaps = 1,
	.regmap_names = अणु"syscon"पूर्ण,
	.num_phys = 5,
	.phys = अणु
		अणु
			/* EXYNOS_MIPI_PHY_ID_CSIS0 */
			.coupled_phy_id = EXYNOS_MIPI_PHY_ID_DSIM0,
			.enable_val = EXYNOS4_PHY_ENABLE,
			.enable_reg = EXYNOS5420_MIPI_PHY_CONTROL(0),
			.enable_map = EXYNOS_MIPI_REGMAP_PMU,
			.resetn_val = EXYNOS4_MIPI_PHY_SRESETN,
			.resetn_reg = EXYNOS5420_MIPI_PHY_CONTROL(0),
			.resetn_map = EXYNOS_MIPI_REGMAP_PMU,
		पूर्ण, अणु
			/* EXYNOS_MIPI_PHY_ID_DSIM0 */
			.coupled_phy_id = EXYNOS_MIPI_PHY_ID_CSIS0,
			.enable_val = EXYNOS4_PHY_ENABLE,
			.enable_reg = EXYNOS5420_MIPI_PHY_CONTROL(0),
			.enable_map = EXYNOS_MIPI_REGMAP_PMU,
			.resetn_val = EXYNOS4_MIPI_PHY_MRESETN,
			.resetn_reg = EXYNOS5420_MIPI_PHY_CONTROL(0),
			.resetn_map = EXYNOS_MIPI_REGMAP_PMU,
		पूर्ण, अणु
			/* EXYNOS_MIPI_PHY_ID_CSIS1 */
			.coupled_phy_id = EXYNOS_MIPI_PHY_ID_DSIM1,
			.enable_val = EXYNOS4_PHY_ENABLE,
			.enable_reg = EXYNOS5420_MIPI_PHY_CONTROL(1),
			.enable_map = EXYNOS_MIPI_REGMAP_PMU,
			.resetn_val = EXYNOS4_MIPI_PHY_SRESETN,
			.resetn_reg = EXYNOS5420_MIPI_PHY_CONTROL(1),
			.resetn_map = EXYNOS_MIPI_REGMAP_PMU,
		पूर्ण, अणु
			/* EXYNOS_MIPI_PHY_ID_DSIM1 */
			.coupled_phy_id = EXYNOS_MIPI_PHY_ID_CSIS1,
			.enable_val = EXYNOS4_PHY_ENABLE,
			.enable_reg = EXYNOS5420_MIPI_PHY_CONTROL(1),
			.enable_map = EXYNOS_MIPI_REGMAP_PMU,
			.resetn_val = EXYNOS4_MIPI_PHY_MRESETN,
			.resetn_reg = EXYNOS5420_MIPI_PHY_CONTROL(1),
			.resetn_map = EXYNOS_MIPI_REGMAP_PMU,
		पूर्ण, अणु
			/* EXYNOS_MIPI_PHY_ID_CSIS2 */
			.coupled_phy_id = EXYNOS_MIPI_PHY_ID_NONE,
			.enable_val = EXYNOS4_PHY_ENABLE,
			.enable_reg = EXYNOS5420_MIPI_PHY_CONTROL(2),
			.enable_map = EXYNOS_MIPI_REGMAP_PMU,
			.resetn_val = EXYNOS4_MIPI_PHY_SRESETN,
			.resetn_reg = EXYNOS5420_MIPI_PHY_CONTROL(2),
			.resetn_map = EXYNOS_MIPI_REGMAP_PMU,
		पूर्ण,
	पूर्ण,
पूर्ण;

#घोषणा EXYNOS5433_SYSREG_DISP_MIPI_PHY		0x100C
#घोषणा EXYNOS5433_SYSREG_CAM0_MIPI_DPHY_CON	0x1014
#घोषणा EXYNOS5433_SYSREG_CAM1_MIPI_DPHY_CON	0x1020

अटल स्थिर काष्ठा mipi_phy_device_desc exynos5433_mipi_phy = अणु
	.num_regmaps = 4,
	.regmap_names = अणु
		"samsung,pmu-syscon",
		"samsung,disp-sysreg",
		"samsung,cam0-sysreg",
		"samsung,cam1-sysreg"
	पूर्ण,
	.num_phys = 5,
	.phys = अणु
		अणु
			/* EXYNOS_MIPI_PHY_ID_CSIS0 */
			.coupled_phy_id = EXYNOS_MIPI_PHY_ID_DSIM0,
			.enable_val = EXYNOS4_PHY_ENABLE,
			.enable_reg = EXYNOS4_MIPI_PHY_CONTROL(0),
			.enable_map = EXYNOS_MIPI_REGMAP_PMU,
			.resetn_val = BIT(0),
			.resetn_reg = EXYNOS5433_SYSREG_CAM0_MIPI_DPHY_CON,
			.resetn_map = EXYNOS_MIPI_REGMAP_CAM0,
		पूर्ण, अणु
			/* EXYNOS_MIPI_PHY_ID_DSIM0 */
			.coupled_phy_id = EXYNOS_MIPI_PHY_ID_CSIS0,
			.enable_val = EXYNOS4_PHY_ENABLE,
			.enable_reg = EXYNOS4_MIPI_PHY_CONTROL(0),
			.enable_map = EXYNOS_MIPI_REGMAP_PMU,
			.resetn_val = BIT(0),
			.resetn_reg = EXYNOS5433_SYSREG_DISP_MIPI_PHY,
			.resetn_map = EXYNOS_MIPI_REGMAP_DISP,
		पूर्ण, अणु
			/* EXYNOS_MIPI_PHY_ID_CSIS1 */
			.coupled_phy_id = EXYNOS_MIPI_PHY_ID_NONE,
			.enable_val = EXYNOS4_PHY_ENABLE,
			.enable_reg = EXYNOS4_MIPI_PHY_CONTROL(1),
			.enable_map = EXYNOS_MIPI_REGMAP_PMU,
			.resetn_val = BIT(1),
			.resetn_reg = EXYNOS5433_SYSREG_CAM0_MIPI_DPHY_CON,
			.resetn_map = EXYNOS_MIPI_REGMAP_CAM0,
		पूर्ण, अणु
			/* EXYNOS_MIPI_PHY_ID_DSIM1 */
			.coupled_phy_id = EXYNOS_MIPI_PHY_ID_NONE,
			.enable_val = EXYNOS4_PHY_ENABLE,
			.enable_reg = EXYNOS4_MIPI_PHY_CONTROL(1),
			.enable_map = EXYNOS_MIPI_REGMAP_PMU,
			.resetn_val = BIT(1),
			.resetn_reg = EXYNOS5433_SYSREG_DISP_MIPI_PHY,
			.resetn_map = EXYNOS_MIPI_REGMAP_DISP,
		पूर्ण, अणु
			/* EXYNOS_MIPI_PHY_ID_CSIS2 */
			.coupled_phy_id = EXYNOS_MIPI_PHY_ID_NONE,
			.enable_val = EXYNOS4_PHY_ENABLE,
			.enable_reg = EXYNOS4_MIPI_PHY_CONTROL(2),
			.enable_map = EXYNOS_MIPI_REGMAP_PMU,
			.resetn_val = BIT(0),
			.resetn_reg = EXYNOS5433_SYSREG_CAM1_MIPI_DPHY_CON,
			.resetn_map = EXYNOS_MIPI_REGMAP_CAM1,
		पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा exynos_mipi_video_phy अणु
	काष्ठा regmap *regmaps[EXYNOS_MIPI_REGMAPS_NUM];
	पूर्णांक num_phys;
	काष्ठा video_phy_desc अणु
		काष्ठा phy *phy;
		अचिन्हित पूर्णांक index;
		स्थिर काष्ठा exynos_mipi_phy_desc *data;
	पूर्ण phys[EXYNOS_MIPI_PHYS_NUM];
	spinlock_t slock;
पूर्ण;

अटल पूर्णांक __set_phy_state(स्थिर काष्ठा exynos_mipi_phy_desc *data,
			   काष्ठा exynos_mipi_video_phy *state, अचिन्हित पूर्णांक on)
अणु
	काष्ठा regmap *enable_map = state->regmaps[data->enable_map];
	काष्ठा regmap *resetn_map = state->regmaps[data->resetn_map];

	spin_lock(&state->slock);

	/* disable in PMU sysreg */
	अगर (!on && data->coupled_phy_id >= 0 &&
	    state->phys[data->coupled_phy_id].phy->घातer_count == 0)
		regmap_update_bits(enable_map, data->enable_reg,
				   data->enable_val, 0);
	/* PHY reset */
	अगर (on)
		regmap_update_bits(resetn_map, data->resetn_reg,
				   data->resetn_val, data->resetn_val);
	अन्यथा
		regmap_update_bits(resetn_map, data->resetn_reg,
				   data->resetn_val, 0);
	/* enable in PMU sysreg */
	अगर (on)
		regmap_update_bits(enable_map, data->enable_reg,
				   data->enable_val, data->enable_val);

	spin_unlock(&state->slock);

	वापस 0;
पूर्ण

#घोषणा to_mipi_video_phy(desc) \
	container_of((desc), काष्ठा exynos_mipi_video_phy, phys[(desc)->index])

अटल पूर्णांक exynos_mipi_video_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा video_phy_desc *phy_desc = phy_get_drvdata(phy);
	काष्ठा exynos_mipi_video_phy *state = to_mipi_video_phy(phy_desc);

	वापस __set_phy_state(phy_desc->data, state, 1);
पूर्ण

अटल पूर्णांक exynos_mipi_video_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा video_phy_desc *phy_desc = phy_get_drvdata(phy);
	काष्ठा exynos_mipi_video_phy *state = to_mipi_video_phy(phy_desc);

	वापस __set_phy_state(phy_desc->data, state, 0);
पूर्ण

अटल काष्ठा phy *exynos_mipi_video_phy_xlate(काष्ठा device *dev,
					काष्ठा of_phandle_args *args)
अणु
	काष्ठा exynos_mipi_video_phy *state = dev_get_drvdata(dev);

	अगर (WARN_ON(args->args[0] >= state->num_phys))
		वापस ERR_PTR(-ENODEV);

	वापस state->phys[args->args[0]].phy;
पूर्ण

अटल स्थिर काष्ठा phy_ops exynos_mipi_video_phy_ops = अणु
	.घातer_on	= exynos_mipi_video_phy_घातer_on,
	.घातer_off	= exynos_mipi_video_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक exynos_mipi_video_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा mipi_phy_device_desc *phy_dev;
	काष्ठा exynos_mipi_video_phy *state;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा phy_provider *phy_provider;
	अचिन्हित पूर्णांक i;

	phy_dev = of_device_get_match_data(dev);
	अगर (!phy_dev)
		वापस -ENODEV;

	state = devm_kzalloc(dev, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	क्रम (i = 0; i < phy_dev->num_regmaps; i++) अणु
		state->regmaps[i] = syscon_regmap_lookup_by_phandle(np,
						phy_dev->regmap_names[i]);
		अगर (IS_ERR(state->regmaps[i]))
			वापस PTR_ERR(state->regmaps[i]);
	पूर्ण
	state->num_phys = phy_dev->num_phys;
	spin_lock_init(&state->slock);

	dev_set_drvdata(dev, state);

	क्रम (i = 0; i < state->num_phys; i++) अणु
		काष्ठा phy *phy = devm_phy_create(dev, शून्य,
						  &exynos_mipi_video_phy_ops);
		अगर (IS_ERR(phy)) अणु
			dev_err(dev, "failed to create PHY %d\n", i);
			वापस PTR_ERR(phy);
		पूर्ण

		state->phys[i].phy = phy;
		state->phys[i].index = i;
		state->phys[i].data = &phy_dev->phys[i];
		phy_set_drvdata(phy, &state->phys[i]);
	पूर्ण

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev,
					exynos_mipi_video_phy_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id exynos_mipi_video_phy_of_match[] = अणु
	अणु
		.compatible = "samsung,s5pv210-mipi-video-phy",
		.data = &s5pv210_mipi_phy,
	पूर्ण, अणु
		.compatible = "samsung,exynos5420-mipi-video-phy",
		.data = &exynos5420_mipi_phy,
	पूर्ण, अणु
		.compatible = "samsung,exynos5433-mipi-video-phy",
		.data = &exynos5433_mipi_phy,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_mipi_video_phy_of_match);

अटल काष्ठा platक्रमm_driver exynos_mipi_video_phy_driver = अणु
	.probe	= exynos_mipi_video_phy_probe,
	.driver = अणु
		.of_match_table	= exynos_mipi_video_phy_of_match,
		.name  = "exynos-mipi-video-phy",
		.suppress_bind_attrs = true,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(exynos_mipi_video_phy_driver);

MODULE_DESCRIPTION("Samsung S5P/Exynos SoC MIPI CSI-2/DSI PHY driver");
MODULE_AUTHOR("Sylwester Nawrocki <s.nawrocki@samsung.com>");
MODULE_LICENSE("GPL v2");
