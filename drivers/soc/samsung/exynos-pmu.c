<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2011-2014 Samsung Electronics Co., Ltd.
//		http://www.samsung.com/
//
// Exynos - CPU PMU(Power Management Unit) support

#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>

#समावेश <linux/soc/samsung/exynos-regs-pmu.h>
#समावेश <linux/soc/samsung/exynos-pmu.h>

#समावेश "exynos-pmu.h"

काष्ठा exynos_pmu_context अणु
	काष्ठा device *dev;
	स्थिर काष्ठा exynos_pmu_data *pmu_data;
पूर्ण;

व्योम __iomem *pmu_base_addr;
अटल काष्ठा exynos_pmu_context *pmu_context;

व्योम pmu_raw_ग_लिखोl(u32 val, u32 offset)
अणु
	ग_लिखोl_relaxed(val, pmu_base_addr + offset);
पूर्ण

u32 pmu_raw_पढ़ोl(u32 offset)
अणु
	वापस पढ़ोl_relaxed(pmu_base_addr + offset);
पूर्ण

व्योम exynos_sys_घातerकरोwn_conf(क्रमागत sys_घातerकरोwn mode)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर काष्ठा exynos_pmu_data *pmu_data;

	अगर (!pmu_context || !pmu_context->pmu_data)
		वापस;

	pmu_data = pmu_context->pmu_data;

	अगर (pmu_data->घातerकरोwn_conf)
		pmu_data->घातerकरोwn_conf(mode);

	अगर (pmu_data->pmu_config) अणु
		क्रम (i = 0; (pmu_data->pmu_config[i].offset != PMU_TABLE_END); i++)
			pmu_raw_ग_लिखोl(pmu_data->pmu_config[i].val[mode],
					pmu_data->pmu_config[i].offset);
	पूर्ण

	अगर (pmu_data->घातerकरोwn_conf_extra)
		pmu_data->घातerकरोwn_conf_extra(mode);
पूर्ण

/*
 * Split the data between ARM architectures because it is relatively big
 * and useless on other arch.
 */
#अगर_घोषित CONFIG_EXYNOS_PMU_ARM_DRIVERS
#घोषणा exynos_pmu_data_arm_ptr(data)	(&data)
#अन्यथा
#घोषणा exynos_pmu_data_arm_ptr(data)	शून्य
#पूर्ण_अगर

/*
 * PMU platक्रमm driver and devicetree bindings.
 */
अटल स्थिर काष्ठा of_device_id exynos_pmu_of_device_ids[] = अणु
	अणु
		.compatible = "samsung,exynos3250-pmu",
		.data = exynos_pmu_data_arm_ptr(exynos3250_pmu_data),
	पूर्ण, अणु
		.compatible = "samsung,exynos4210-pmu",
		.data = exynos_pmu_data_arm_ptr(exynos4210_pmu_data),
	पूर्ण, अणु
		.compatible = "samsung,exynos4412-pmu",
		.data = exynos_pmu_data_arm_ptr(exynos4412_pmu_data),
	पूर्ण, अणु
		.compatible = "samsung,exynos5250-pmu",
		.data = exynos_pmu_data_arm_ptr(exynos5250_pmu_data),
	पूर्ण, अणु
		.compatible = "samsung,exynos5410-pmu",
	पूर्ण, अणु
		.compatible = "samsung,exynos5420-pmu",
		.data = exynos_pmu_data_arm_ptr(exynos5420_pmu_data),
	पूर्ण, अणु
		.compatible = "samsung,exynos5433-pmu",
	पूर्ण, अणु
		.compatible = "samsung,exynos7-pmu",
	पूर्ण,
	अणु /*sentinel*/ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell exynos_pmu_devs[] = अणु
	अणु .name = "exynos-clkout", पूर्ण,
पूर्ण;

काष्ठा regmap *exynos_get_pmu_regmap(व्योम)
अणु
	काष्ठा device_node *np = of_find_matching_node(शून्य,
						      exynos_pmu_of_device_ids);
	अगर (np)
		वापस syscon_node_to_regmap(np);
	वापस ERR_PTR(-ENODEV);
पूर्ण
EXPORT_SYMBOL_GPL(exynos_get_pmu_regmap);

अटल पूर्णांक exynos_pmu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	pmu_base_addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pmu_base_addr))
		वापस PTR_ERR(pmu_base_addr);

	pmu_context = devm_kzalloc(&pdev->dev,
			माप(काष्ठा exynos_pmu_context),
			GFP_KERNEL);
	अगर (!pmu_context)
		वापस -ENOMEM;
	pmu_context->dev = dev;
	pmu_context->pmu_data = of_device_get_match_data(dev);

	अगर (pmu_context->pmu_data && pmu_context->pmu_data->pmu_init)
		pmu_context->pmu_data->pmu_init();

	platक्रमm_set_drvdata(pdev, pmu_context);

	ret = devm_mfd_add_devices(dev, PLATFORM_DEVID_NONE, exynos_pmu_devs,
				   ARRAY_SIZE(exynos_pmu_devs), शून्य, 0, शून्य);
	अगर (ret)
		वापस ret;

	अगर (devm_of_platक्रमm_populate(dev))
		dev_err(dev, "Error populating children, reboot and poweroff might not work properly\n");

	dev_dbg(dev, "Exynos PMU Driver probe done\n");
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver exynos_pmu_driver = अणु
	.driver  = अणु
		.name   = "exynos-pmu",
		.of_match_table = exynos_pmu_of_device_ids,
	पूर्ण,
	.probe = exynos_pmu_probe,
पूर्ण;

अटल पूर्णांक __init exynos_pmu_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&exynos_pmu_driver);

पूर्ण
postcore_initcall(exynos_pmu_init);
