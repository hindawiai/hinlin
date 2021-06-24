<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Device driver क्रम Hi6421 PMIC
 *
 * Copyright (c) <2011-2014> HiSilicon Technologies Co., Ltd.
 *              http://www.hisilicon.com
 * Copyright (c) <2013-2017> Linaro Ltd.
 *              https://www.linaro.org
 *
 * Author: Guoकरोng Xu <guoकरोng.xu@linaro.org>
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/hi6421-pmic.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

अटल स्थिर काष्ठा mfd_cell hi6421_devs[] = अणु
	अणु .name = "hi6421-regulator", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell hi6421v530_devs[] = अणु
	अणु .name = "hi6421v530-regulator", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config hi6421_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 8,
	.max_रेजिस्टर = HI6421_REG_TO_BUS_ADDR(HI6421_REG_MAX),
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_hi6421_pmic_match[] = अणु
	अणु
		.compatible = "hisilicon,hi6421-pmic",
		.data = (व्योम *)HI6421
	पूर्ण,
	अणु
		.compatible = "hisilicon,hi6421v530-pmic",
		.data = (व्योम *)HI6421_V530
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_hi6421_pmic_match);

अटल पूर्णांक hi6421_pmic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hi6421_pmic *pmic;
	काष्ठा resource *res;
	स्थिर काष्ठा of_device_id *id;
	स्थिर काष्ठा mfd_cell *subdevs;
	क्रमागत hi6421_type type;
	व्योम __iomem *base;
	पूर्णांक n_subdevs, ret;

	id = of_match_device(of_hi6421_pmic_match, &pdev->dev);
	अगर (!id)
		वापस -EINVAL;
	type = (क्रमागत hi6421_type)id->data;

	pmic = devm_kzalloc(&pdev->dev, माप(*pmic), GFP_KERNEL);
	अगर (!pmic)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	pmic->regmap = devm_regmap_init_mmio_clk(&pdev->dev, शून्य, base,
						 &hi6421_regmap_config);
	अगर (IS_ERR(pmic->regmap)) अणु
		dev_err(&pdev->dev, "Failed to initialise Regmap: %ld\n",
						PTR_ERR(pmic->regmap));
		वापस PTR_ERR(pmic->regmap);
	पूर्ण

	platक्रमm_set_drvdata(pdev, pmic);

	चयन (type) अणु
	हाल HI6421:
		/* set over-current protection debounce 8ms */
		regmap_update_bits(pmic->regmap, HI6421_OCP_DEB_CTRL_REG,
				(HI6421_OCP_DEB_SEL_MASK
				 | HI6421_OCP_EN_DEBOUNCE_MASK
				 | HI6421_OCP_AUTO_STOP_MASK),
				(HI6421_OCP_DEB_SEL_8MS
				 | HI6421_OCP_EN_DEBOUNCE_ENABLE));

		subdevs = hi6421_devs;
		n_subdevs = ARRAY_SIZE(hi6421_devs);
		अवरोध;
	हाल HI6421_V530:
		subdevs = hi6421v530_devs;
		n_subdevs = ARRAY_SIZE(hi6421v530_devs);
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unknown device type %d\n",
						(अचिन्हित पूर्णांक)type);
		वापस -EINVAL;
	पूर्ण

	ret = devm_mfd_add_devices(&pdev->dev, PLATFORM_DEVID_NONE,
				   subdevs, n_subdevs, शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to add child devices: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hi6421_pmic_driver = अणु
	.driver = अणु
		.name = "hi6421_pmic",
		.of_match_table = of_hi6421_pmic_match,
	पूर्ण,
	.probe	= hi6421_pmic_probe,
पूर्ण;
module_platक्रमm_driver(hi6421_pmic_driver);

MODULE_AUTHOR("Guodong Xu <guodong.xu@linaro.org>");
MODULE_DESCRIPTION("Hi6421 PMIC driver");
MODULE_LICENSE("GPL v2");
