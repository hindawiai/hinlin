<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Rockchip IO Voltage Doमुख्य driver
 *
 * Copyright 2014 MunकरोReader S.L.
 * Copyright 2014 Google, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा MAX_SUPPLIES		16

/*
 * The max voltage क्रम 1.8V and 3.3V come from the Rockchip datasheet under
 * "Recommended Operating Conditions" क्रम "Digital GPIO".   When the typical
 * is 3.3V the max is 3.6V.  When the typical is 1.8V the max is 1.98V.
 *
 * They are used like this:
 * - If the voltage on a rail is above the "1.8" voltage (1.98V) we'll tell the
 *   SoC we're at 3.3.
 * - If the voltage on a rail is above the "3.3" voltage (3.6V) we'll consider
 *   that to be an error.
 */
#घोषणा MAX_VOLTAGE_1_8		1980000
#घोषणा MAX_VOLTAGE_3_3		3600000

#घोषणा PX30_IO_VSEL			0x180
#घोषणा PX30_IO_VSEL_VCCIO6_SRC		BIT(0)
#घोषणा PX30_IO_VSEL_VCCIO6_SUPPLY_NUM	1

#घोषणा RK3288_SOC_CON2			0x24c
#घोषणा RK3288_SOC_CON2_FLASH0		BIT(7)
#घोषणा RK3288_SOC_FLASH_SUPPLY_NUM	2

#घोषणा RK3328_SOC_CON4			0x410
#घोषणा RK3328_SOC_CON4_VCCIO2		BIT(7)
#घोषणा RK3328_SOC_VCCIO2_SUPPLY_NUM	1

#घोषणा RK3368_SOC_CON15		0x43c
#घोषणा RK3368_SOC_CON15_FLASH0		BIT(14)
#घोषणा RK3368_SOC_FLASH_SUPPLY_NUM	2

#घोषणा RK3399_PMUGRF_CON0		0x180
#घोषणा RK3399_PMUGRF_CON0_VSEL		BIT(8)
#घोषणा RK3399_PMUGRF_VSEL_SUPPLY_NUM	9

काष्ठा rockchip_ioकरोमुख्य;

काष्ठा rockchip_ioकरोमुख्य_soc_data अणु
	पूर्णांक grf_offset;
	स्थिर अक्षर *supply_names[MAX_SUPPLIES];
	व्योम (*init)(काष्ठा rockchip_ioकरोमुख्य *iod);
पूर्ण;

काष्ठा rockchip_ioकरोमुख्य_supply अणु
	काष्ठा rockchip_ioकरोमुख्य *iod;
	काष्ठा regulator *reg;
	काष्ठा notअगरier_block nb;
	पूर्णांक idx;
पूर्ण;

काष्ठा rockchip_ioकरोमुख्य अणु
	काष्ठा device *dev;
	काष्ठा regmap *grf;
	स्थिर काष्ठा rockchip_ioकरोमुख्य_soc_data *soc_data;
	काष्ठा rockchip_ioकरोमुख्य_supply supplies[MAX_SUPPLIES];
पूर्ण;

अटल पूर्णांक rockchip_ioकरोमुख्य_ग_लिखो(काष्ठा rockchip_ioकरोमुख्य_supply *supply,
				   पूर्णांक uV)
अणु
	काष्ठा rockchip_ioकरोमुख्य *iod = supply->iod;
	u32 val;
	पूर्णांक ret;

	/* set value bit */
	val = (uV > MAX_VOLTAGE_1_8) ? 0 : 1;
	val <<= supply->idx;

	/* apply hiword-mask */
	val |= (BIT(supply->idx) << 16);

	ret = regmap_ग_लिखो(iod->grf, iod->soc_data->grf_offset, val);
	अगर (ret)
		dev_err(iod->dev, "Couldn't write to GRF\n");

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_ioकरोमुख्य_notअगरy(काष्ठा notअगरier_block *nb,
				    अचिन्हित दीर्घ event,
				    व्योम *data)
अणु
	काष्ठा rockchip_ioकरोमुख्य_supply *supply =
			container_of(nb, काष्ठा rockchip_ioकरोमुख्य_supply, nb);
	पूर्णांक uV;
	पूर्णांक ret;

	/*
	 * According to Rockchip it's important to keep the SoC IO करोमुख्य
	 * higher than (or equal to) the बाह्यal voltage.  That means we need
	 * to change it beक्रमe बाह्यal voltage changes happen in the हाल
	 * of an increase.
	 *
	 * Note that in the "pre" change we pick the max possible voltage that
	 * the regulator might end up at (the client requests a range and we
	 * करोn't know क्रम certain the exact voltage).  Right now we rely on the
	 * slop in MAX_VOLTAGE_1_8 and MAX_VOLTAGE_3_3 to save us अगर clients
	 * request something like a max of 3.6V when they really want 3.3V.
	 * We could attempt to come up with better rules अगर this fails.
	 */
	अगर (event & REGULATOR_EVENT_PRE_VOLTAGE_CHANGE) अणु
		काष्ठा pre_voltage_change_data *pvc_data = data;

		uV = max_t(अचिन्हित दीर्घ, pvc_data->old_uV, pvc_data->max_uV);
	पूर्ण अन्यथा अगर (event & (REGULATOR_EVENT_VOLTAGE_CHANGE |
			    REGULATOR_EVENT_ABORT_VOLTAGE_CHANGE)) अणु
		uV = (अचिन्हित दीर्घ)data;
	पूर्ण अन्यथा अणु
		वापस NOTIFY_OK;
	पूर्ण

	dev_dbg(supply->iod->dev, "Setting to %d\n", uV);

	अगर (uV > MAX_VOLTAGE_3_3) अणु
		dev_err(supply->iod->dev, "Voltage too high: %d\n", uV);

		अगर (event == REGULATOR_EVENT_PRE_VOLTAGE_CHANGE)
			वापस NOTIFY_BAD;
	पूर्ण

	ret = rockchip_ioकरोमुख्य_ग_लिखो(supply, uV);
	अगर (ret && event == REGULATOR_EVENT_PRE_VOLTAGE_CHANGE)
		वापस NOTIFY_BAD;

	dev_dbg(supply->iod->dev, "Setting to %d done\n", uV);
	वापस NOTIFY_OK;
पूर्ण

अटल व्योम px30_ioकरोमुख्य_init(काष्ठा rockchip_ioकरोमुख्य *iod)
अणु
	पूर्णांक ret;
	u32 val;

	/* अगर no VCCIO6 supply we should leave things alone */
	अगर (!iod->supplies[PX30_IO_VSEL_VCCIO6_SUPPLY_NUM].reg)
		वापस;

	/*
	 * set vccio6 ioकरोमुख्य to also use this framework
	 * instead of a special gpio.
	 */
	val = PX30_IO_VSEL_VCCIO6_SRC | (PX30_IO_VSEL_VCCIO6_SRC << 16);
	ret = regmap_ग_लिखो(iod->grf, PX30_IO_VSEL, val);
	अगर (ret < 0)
		dev_warn(iod->dev, "couldn't update vccio6 ctrl\n");
पूर्ण

अटल व्योम rk3288_ioकरोमुख्य_init(काष्ठा rockchip_ioकरोमुख्य *iod)
अणु
	पूर्णांक ret;
	u32 val;

	/* अगर no flash supply we should leave things alone */
	अगर (!iod->supplies[RK3288_SOC_FLASH_SUPPLY_NUM].reg)
		वापस;

	/*
	 * set flash0 ioकरोमुख्य to also use this framework
	 * instead of a special gpio.
	 */
	val = RK3288_SOC_CON2_FLASH0 | (RK3288_SOC_CON2_FLASH0 << 16);
	ret = regmap_ग_लिखो(iod->grf, RK3288_SOC_CON2, val);
	अगर (ret < 0)
		dev_warn(iod->dev, "couldn't update flash0 ctrl\n");
पूर्ण

अटल व्योम rk3328_ioकरोमुख्य_init(काष्ठा rockchip_ioकरोमुख्य *iod)
अणु
	पूर्णांक ret;
	u32 val;

	/* अगर no vccio2 supply we should leave things alone */
	अगर (!iod->supplies[RK3328_SOC_VCCIO2_SUPPLY_NUM].reg)
		वापस;

	/*
	 * set vccio2 ioकरोमुख्य to also use this framework
	 * instead of a special gpio.
	 */
	val = RK3328_SOC_CON4_VCCIO2 | (RK3328_SOC_CON4_VCCIO2 << 16);
	ret = regmap_ग_लिखो(iod->grf, RK3328_SOC_CON4, val);
	अगर (ret < 0)
		dev_warn(iod->dev, "couldn't update vccio2 vsel ctrl\n");
पूर्ण

अटल व्योम rk3368_ioकरोमुख्य_init(काष्ठा rockchip_ioकरोमुख्य *iod)
अणु
	पूर्णांक ret;
	u32 val;

	/* अगर no flash supply we should leave things alone */
	अगर (!iod->supplies[RK3368_SOC_FLASH_SUPPLY_NUM].reg)
		वापस;

	/*
	 * set flash0 ioकरोमुख्य to also use this framework
	 * instead of a special gpio.
	 */
	val = RK3368_SOC_CON15_FLASH0 | (RK3368_SOC_CON15_FLASH0 << 16);
	ret = regmap_ग_लिखो(iod->grf, RK3368_SOC_CON15, val);
	अगर (ret < 0)
		dev_warn(iod->dev, "couldn't update flash0 ctrl\n");
पूर्ण

अटल व्योम rk3399_pmu_ioकरोमुख्य_init(काष्ठा rockchip_ioकरोमुख्य *iod)
अणु
	पूर्णांक ret;
	u32 val;

	/* अगर no pmu io supply we should leave things alone */
	अगर (!iod->supplies[RK3399_PMUGRF_VSEL_SUPPLY_NUM].reg)
		वापस;

	/*
	 * set pmu io ioकरोमुख्य to also use this framework
	 * instead of a special gpio.
	 */
	val = RK3399_PMUGRF_CON0_VSEL | (RK3399_PMUGRF_CON0_VSEL << 16);
	ret = regmap_ग_लिखो(iod->grf, RK3399_PMUGRF_CON0, val);
	अगर (ret < 0)
		dev_warn(iod->dev, "couldn't update pmu io iodomain ctrl\n");
पूर्ण

अटल स्थिर काष्ठा rockchip_ioकरोमुख्य_soc_data soc_data_px30 = अणु
	.grf_offset = 0x180,
	.supply_names = अणु
		शून्य,
		"vccio6",
		"vccio1",
		"vccio2",
		"vccio3",
		"vccio4",
		"vccio5",
		"vccio-oscgpi",
	पूर्ण,
	.init = px30_ioकरोमुख्य_init,
पूर्ण;

अटल स्थिर काष्ठा rockchip_ioकरोमुख्य_soc_data soc_data_px30_pmu = अणु
	.grf_offset = 0x100,
	.supply_names = अणु
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		"pmuio1",
		"pmuio2",
	पूर्ण,
पूर्ण;

/*
 * On the rk3188 the io-करोमुख्यs are handled by a shared रेजिस्टर with the
 * lower 8 bits being still being continuing drive-strength settings.
 */
अटल स्थिर काष्ठा rockchip_ioकरोमुख्य_soc_data soc_data_rk3188 = अणु
	.grf_offset = 0x104,
	.supply_names = अणु
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		"ap0",
		"ap1",
		"cif",
		"flash",
		"vccio0",
		"vccio1",
		"lcdc0",
		"lcdc1",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_ioकरोमुख्य_soc_data soc_data_rk3228 = अणु
	.grf_offset = 0x418,
	.supply_names = अणु
		"vccio1",
		"vccio2",
		"vccio3",
		"vccio4",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_ioकरोमुख्य_soc_data soc_data_rk3288 = अणु
	.grf_offset = 0x380,
	.supply_names = अणु
		"lcdc",		/* LCDC_VDD */
		"dvp",		/* DVPIO_VDD */
		"flash0",	/* FLASH0_VDD (emmc) */
		"flash1",	/* FLASH1_VDD (sdio1) */
		"wifi",		/* APIO3_VDD  (sdio0) */
		"bb",		/* APIO5_VDD */
		"audio",	/* APIO4_VDD */
		"sdcard",	/* SDMMC0_VDD (sdmmc) */
		"gpio30",	/* APIO1_VDD */
		"gpio1830",	/* APIO2_VDD */
	पूर्ण,
	.init = rk3288_ioकरोमुख्य_init,
पूर्ण;

अटल स्थिर काष्ठा rockchip_ioकरोमुख्य_soc_data soc_data_rk3328 = अणु
	.grf_offset = 0x410,
	.supply_names = अणु
		"vccio1",
		"vccio2",
		"vccio3",
		"vccio4",
		"vccio5",
		"vccio6",
		"pmuio",
	पूर्ण,
	.init = rk3328_ioकरोमुख्य_init,
पूर्ण;

अटल स्थिर काष्ठा rockchip_ioकरोमुख्य_soc_data soc_data_rk3368 = अणु
	.grf_offset = 0x900,
	.supply_names = अणु
		शून्य,		/* reserved */
		"dvp",		/* DVPIO_VDD */
		"flash0",	/* FLASH0_VDD (emmc) */
		"wifi",		/* APIO2_VDD (sdio0) */
		शून्य,
		"audio",	/* APIO3_VDD */
		"sdcard",	/* SDMMC0_VDD (sdmmc) */
		"gpio30",	/* APIO1_VDD */
		"gpio1830",	/* APIO4_VDD (gpujtag) */
	पूर्ण,
	.init = rk3368_ioकरोमुख्य_init,
पूर्ण;

अटल स्थिर काष्ठा rockchip_ioकरोमुख्य_soc_data soc_data_rk3368_pmu = अणु
	.grf_offset = 0x100,
	.supply_names = अणु
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		"pmu",	        /*PMU IO करोमुख्य*/
		"vop",	        /*LCDC IO करोमुख्य*/
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_ioकरोमुख्य_soc_data soc_data_rk3399 = अणु
	.grf_offset = 0xe640,
	.supply_names = अणु
		"bt656",		/* APIO2_VDD */
		"audio",		/* APIO5_VDD */
		"sdmmc",		/* SDMMC0_VDD */
		"gpio1830",		/* APIO4_VDD */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rockchip_ioकरोमुख्य_soc_data soc_data_rk3399_pmu = अणु
	.grf_offset = 0x180,
	.supply_names = अणु
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		"pmu1830",		/* PMUIO2_VDD */
	पूर्ण,
	.init = rk3399_pmu_ioकरोमुख्य_init,
पूर्ण;

अटल स्थिर काष्ठा rockchip_ioकरोमुख्य_soc_data soc_data_rv1108 = अणु
	.grf_offset = 0x404,
	.supply_names = अणु
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		शून्य,
		"vccio1",
		"vccio2",
		"vccio3",
		"vccio5",
		"vccio6",
	पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा rockchip_ioकरोमुख्य_soc_data soc_data_rv1108_pmu = अणु
	.grf_offset = 0x104,
	.supply_names = अणु
		"pmu",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_ioकरोमुख्य_match[] = अणु
	अणु
		.compatible = "rockchip,px30-io-voltage-domain",
		.data = (व्योम *)&soc_data_px30
	पूर्ण,
	अणु
		.compatible = "rockchip,px30-pmu-io-voltage-domain",
		.data = (व्योम *)&soc_data_px30_pmu
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3188-io-voltage-domain",
		.data = &soc_data_rk3188
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3228-io-voltage-domain",
		.data = &soc_data_rk3228
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3288-io-voltage-domain",
		.data = &soc_data_rk3288
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3328-io-voltage-domain",
		.data = &soc_data_rk3328
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3368-io-voltage-domain",
		.data = &soc_data_rk3368
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3368-pmu-io-voltage-domain",
		.data = &soc_data_rk3368_pmu
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3399-io-voltage-domain",
		.data = &soc_data_rk3399
	पूर्ण,
	अणु
		.compatible = "rockchip,rk3399-pmu-io-voltage-domain",
		.data = &soc_data_rk3399_pmu
	पूर्ण,
	अणु
		.compatible = "rockchip,rv1108-io-voltage-domain",
		.data = &soc_data_rv1108
	पूर्ण,
	अणु
		.compatible = "rockchip,rv1108-pmu-io-voltage-domain",
		.data = &soc_data_rv1108_pmu
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rockchip_ioकरोमुख्य_match);

अटल पूर्णांक rockchip_ioकरोमुख्य_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा rockchip_ioकरोमुख्य *iod;
	काष्ठा device *parent;
	पूर्णांक i, ret = 0;

	अगर (!np)
		वापस -ENODEV;

	iod = devm_kzalloc(&pdev->dev, माप(*iod), GFP_KERNEL);
	अगर (!iod)
		वापस -ENOMEM;

	iod->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, iod);

	match = of_match_node(rockchip_ioकरोमुख्य_match, np);
	iod->soc_data = match->data;

	parent = pdev->dev.parent;
	अगर (parent && parent->of_node) अणु
		iod->grf = syscon_node_to_regmap(parent->of_node);
	पूर्ण अन्यथा अणु
		dev_dbg(&pdev->dev, "falling back to old binding\n");
		iod->grf = syscon_regmap_lookup_by_phandle(np, "rockchip,grf");
	पूर्ण

	अगर (IS_ERR(iod->grf)) अणु
		dev_err(&pdev->dev, "couldn't find grf regmap\n");
		वापस PTR_ERR(iod->grf);
	पूर्ण

	क्रम (i = 0; i < MAX_SUPPLIES; i++) अणु
		स्थिर अक्षर *supply_name = iod->soc_data->supply_names[i];
		काष्ठा rockchip_ioकरोमुख्य_supply *supply = &iod->supplies[i];
		काष्ठा regulator *reg;
		पूर्णांक uV;

		अगर (!supply_name)
			जारी;

		reg = devm_regulator_get_optional(iod->dev, supply_name);
		अगर (IS_ERR(reg)) अणु
			ret = PTR_ERR(reg);

			/* If a supply wasn't specified, that's OK */
			अगर (ret == -ENODEV)
				जारी;
			अन्यथा अगर (ret != -EPROBE_DEFER)
				dev_err(iod->dev, "couldn't get regulator %s\n",
					supply_name);
			जाओ unreg_notअगरy;
		पूर्ण

		/* set initial correct value */
		uV = regulator_get_voltage(reg);

		/* must be a regulator we can get the voltage of */
		अगर (uV < 0) अणु
			dev_err(iod->dev, "Can't determine voltage: %s\n",
				supply_name);
			ret = uV;
			जाओ unreg_notअगरy;
		पूर्ण

		अगर (uV > MAX_VOLTAGE_3_3) अणु
			dev_crit(iod->dev,
				 "%d uV is too high. May damage SoC!\n",
				 uV);
			ret = -EINVAL;
			जाओ unreg_notअगरy;
		पूर्ण

		/* setup our supply */
		supply->idx = i;
		supply->iod = iod;
		supply->reg = reg;
		supply->nb.notअगरier_call = rockchip_ioकरोमुख्य_notअगरy;

		ret = rockchip_ioकरोमुख्य_ग_लिखो(supply, uV);
		अगर (ret) अणु
			supply->reg = शून्य;
			जाओ unreg_notअगरy;
		पूर्ण

		/* रेजिस्टर regulator notअगरier */
		ret = regulator_रेजिस्टर_notअगरier(reg, &supply->nb);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"regulator notifier request failed\n");
			supply->reg = शून्य;
			जाओ unreg_notअगरy;
		पूर्ण
	पूर्ण

	अगर (iod->soc_data->init)
		iod->soc_data->init(iod);

	वापस 0;

unreg_notअगरy:
	क्रम (i = MAX_SUPPLIES - 1; i >= 0; i--) अणु
		काष्ठा rockchip_ioकरोमुख्य_supply *io_supply = &iod->supplies[i];

		अगर (io_supply->reg)
			regulator_unरेजिस्टर_notअगरier(io_supply->reg,
						      &io_supply->nb);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_ioकरोमुख्य_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rockchip_ioकरोमुख्य *iod = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = MAX_SUPPLIES - 1; i >= 0; i--) अणु
		काष्ठा rockchip_ioकरोमुख्य_supply *io_supply = &iod->supplies[i];

		अगर (io_supply->reg)
			regulator_unरेजिस्टर_notअगरier(io_supply->reg,
						      &io_supply->nb);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rockchip_ioकरोमुख्य_driver = अणु
	.probe   = rockchip_ioकरोमुख्य_probe,
	.हटाओ  = rockchip_ioकरोमुख्य_हटाओ,
	.driver  = अणु
		.name  = "rockchip-iodomain",
		.of_match_table = rockchip_ioकरोमुख्य_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rockchip_ioकरोमुख्य_driver);

MODULE_DESCRIPTION("Rockchip IO-domain driver");
MODULE_AUTHOR("Heiko Stuebner <heiko@sntech.de>");
MODULE_AUTHOR("Doug Anderson <dianders@chromium.org>");
MODULE_LICENSE("GPL v2");
