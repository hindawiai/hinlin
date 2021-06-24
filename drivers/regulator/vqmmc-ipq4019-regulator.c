<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2019 Mantas Pucka <mantas@8devices.com>
// Copyright (c) 2019 Robert Marko <robert.marko@sartura.hr>
//
// Driver क्रम IPQ4019 SD/MMC controller's I/O LDO voltage regulator

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>

अटल स्थिर अचिन्हित पूर्णांक ipq4019_vmmc_voltages[] = अणु
	1500000, 1800000, 2500000, 3000000,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops ipq4019_regulator_voltage_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc vmmc_regulator = अणु
	.name		= "vmmcq",
	.ops		= &ipq4019_regulator_voltage_ops,
	.type		= REGULATOR_VOLTAGE,
	.owner		= THIS_MODULE,
	.volt_table	= ipq4019_vmmc_voltages,
	.n_voltages	= ARRAY_SIZE(ipq4019_vmmc_voltages),
	.vsel_reg	= 0,
	.vsel_mask	= 0x3,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ipq4019_vmmcq_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
पूर्ण;

अटल पूर्णांक ipq4019_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regulator_init_data *init_data;
	काष्ठा regulator_config cfg = अणुपूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा resource *res;
	काष्ठा regmap *rmap;
	व्योम __iomem *base;

	init_data = of_get_regulator_init_data(dev, dev->of_node,
					       &vmmc_regulator);
	अगर (!init_data)
		वापस -EINVAL;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	rmap = devm_regmap_init_mmio(dev, base, &ipq4019_vmmcq_regmap_config);
	अगर (IS_ERR(rmap))
		वापस PTR_ERR(rmap);

	cfg.dev = dev;
	cfg.init_data = init_data;
	cfg.of_node = dev->of_node;
	cfg.regmap = rmap;

	rdev = devm_regulator_रेजिस्टर(dev, &vmmc_regulator, &cfg);
	अगर (IS_ERR(rdev)) अणु
		dev_err(dev, "Failed to register regulator: %ld\n",
			PTR_ERR(rdev));
		वापस PTR_ERR(rdev);
	पूर्ण
	platक्रमm_set_drvdata(pdev, rdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id regulator_ipq4019_of_match[] = अणु
	अणु .compatible = "qcom,vqmmc-ipq4019-regulator", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ipq4019_regulator_driver = अणु
	.probe = ipq4019_regulator_probe,
	.driver = अणु
		.name = "vqmmc-ipq4019-regulator",
		.of_match_table = of_match_ptr(regulator_ipq4019_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ipq4019_regulator_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mantas Pucka <mantas@8devices.com>");
MODULE_DESCRIPTION("IPQ4019 VQMMC voltage regulator");
