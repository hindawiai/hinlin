<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2018-2019, Intel Corporation.
 *  Copyright (C) 2012 Freescale Semiconductor, Inc.
 *  Copyright (C) 2012 Linaro Ltd.
 *
 *  Based on syscon driver.
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/altera-sysmgr.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

/**
 * काष्ठा altr_sysmgr - Altera SOCFPGA System Manager
 * @regmap: the regmap used क्रम System Manager accesses.
 */
काष्ठा altr_sysmgr अणु
	काष्ठा regmap   *regmap;
पूर्ण;

अटल काष्ठा platक्रमm_driver altr_sysmgr_driver;

/**
 * s10_रक्षित_reg_ग_लिखो
 * Write to a रक्षित SMC रेजिस्टर.
 * @base: Base address of System Manager
 * @reg:  Address offset of रेजिस्टर
 * @val:  Value to ग_लिखो
 * Return: INTEL_SIP_SMC_STATUS_OK (0) on success
 *	   INTEL_SIP_SMC_REG_ERROR on error
 *	   INTEL_SIP_SMC_RETURN_UNKNOWN_FUNCTION अगर not supported
 */
अटल पूर्णांक s10_रक्षित_reg_ग_लिखो(व्योम *base,
				   अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा arm_smccc_res result;
	अचिन्हित दीर्घ sysmgr_base = (अचिन्हित दीर्घ)base;

	arm_smccc_smc(INTEL_SIP_SMC_REG_WRITE, sysmgr_base + reg,
		      val, 0, 0, 0, 0, 0, &result);

	वापस (पूर्णांक)result.a0;
पूर्ण

/**
 * s10_रक्षित_reg_पढ़ो
 * Read the status of a रक्षित SMC रेजिस्टर
 * @base: Base address of System Manager.
 * @reg:  Address of रेजिस्टर
 * @val:  Value पढ़ो.
 * Return: INTEL_SIP_SMC_STATUS_OK (0) on success
 *	   INTEL_SIP_SMC_REG_ERROR on error
 *	   INTEL_SIP_SMC_RETURN_UNKNOWN_FUNCTION अगर not supported
 */
अटल पूर्णांक s10_रक्षित_reg_पढ़ो(व्योम *base,
				  अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा arm_smccc_res result;
	अचिन्हित दीर्घ sysmgr_base = (अचिन्हित दीर्घ)base;

	arm_smccc_smc(INTEL_SIP_SMC_REG_READ, sysmgr_base + reg,
		      0, 0, 0, 0, 0, 0, &result);

	*val = (अचिन्हित पूर्णांक)result.a1;

	वापस (पूर्णांक)result.a0;
पूर्ण

अटल काष्ठा regmap_config altr_sysmgr_regmap_cfg = अणु
	.name = "altr_sysmgr",
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.fast_io = true,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

/**
 * altr_sysmgr_regmap_lookup_by_phandle
 * Find the sysmgr previous configured in probe() and वापस regmap property.
 * Return: regmap अगर found or error अगर not found.
 *
 * @np: Poपूर्णांकer to device's Device Tree node
 * @property: Device Tree property name which references the sysmgr
 */
काष्ठा regmap *altr_sysmgr_regmap_lookup_by_phandle(काष्ठा device_node *np,
						    स्थिर अक्षर *property)
अणु
	काष्ठा device *dev;
	काष्ठा altr_sysmgr *sysmgr;
	काष्ठा device_node *sysmgr_np;

	अगर (property)
		sysmgr_np = of_parse_phandle(np, property, 0);
	अन्यथा
		sysmgr_np = np;

	अगर (!sysmgr_np)
		वापस ERR_PTR(-ENODEV);

	dev = driver_find_device_by_of_node(&altr_sysmgr_driver.driver,
					    (व्योम *)sysmgr_np);
	of_node_put(sysmgr_np);
	अगर (!dev)
		वापस ERR_PTR(-EPROBE_DEFER);

	sysmgr = dev_get_drvdata(dev);

	वापस sysmgr->regmap;
पूर्ण
EXPORT_SYMBOL_GPL(altr_sysmgr_regmap_lookup_by_phandle);

अटल पूर्णांक sysmgr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा altr_sysmgr *sysmgr;
	काष्ठा regmap *regmap;
	काष्ठा resource *res;
	काष्ठा regmap_config sysmgr_config = altr_sysmgr_regmap_cfg;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	व्योम __iomem *base;

	sysmgr = devm_kzalloc(dev, माप(*sysmgr), GFP_KERNEL);
	अगर (!sysmgr)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENOENT;

	sysmgr_config.max_रेजिस्टर = resource_size(res) -
				     sysmgr_config.reg_stride;
	अगर (of_device_is_compatible(np, "altr,sys-mgr-s10")) अणु
		sysmgr_config.reg_पढ़ो = s10_रक्षित_reg_पढ़ो;
		sysmgr_config.reg_ग_लिखो = s10_रक्षित_reg_ग_लिखो;

		/* Need physical address क्रम SMCC call */
		regmap = devm_regmap_init(dev, शून्य,
					  (व्योम *)(uपूर्णांकptr_t)res->start,
					  &sysmgr_config);
	पूर्ण अन्यथा अणु
		base = devm_ioremap(dev, res->start, resource_size(res));
		अगर (!base)
			वापस -ENOMEM;

		sysmgr_config.max_रेजिस्टर = resource_size(res) - 3;
		regmap = devm_regmap_init_mmio(dev, base, &sysmgr_config);
	पूर्ण

	अगर (IS_ERR(regmap)) अणु
		pr_err("regmap init failed\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	sysmgr->regmap = regmap;

	platक्रमm_set_drvdata(pdev, sysmgr);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id altr_sysmgr_of_match[] = अणु
	अणु .compatible = "altr,sys-mgr" पूर्ण,
	अणु .compatible = "altr,sys-mgr-s10" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, altr_sysmgr_of_match);

अटल काष्ठा platक्रमm_driver altr_sysmgr_driver = अणु
	.probe =  sysmgr_probe,
	.driver = अणु
		.name = "altr,system_manager",
		.of_match_table = altr_sysmgr_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init altr_sysmgr_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&altr_sysmgr_driver);
पूर्ण
core_initcall(altr_sysmgr_init);

अटल व्योम __निकास altr_sysmgr_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&altr_sysmgr_driver);
पूर्ण
module_निकास(altr_sysmgr_निकास);

MODULE_AUTHOR("Thor Thayer <>");
MODULE_DESCRIPTION("SOCFPGA System Manager driver");
MODULE_LICENSE("GPL v2");
