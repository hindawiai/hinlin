<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spmi.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of_platक्रमm.h>

#घोषणा PMIC_REV2		0x101
#घोषणा PMIC_REV3		0x102
#घोषणा PMIC_REV4		0x103
#घोषणा PMIC_TYPE		0x104
#घोषणा PMIC_SUBTYPE		0x105

#घोषणा PMIC_TYPE_VALUE		0x51

#घोषणा COMMON_SUBTYPE		0x00
#घोषणा PM8941_SUBTYPE		0x01
#घोषणा PM8841_SUBTYPE		0x02
#घोषणा PM8019_SUBTYPE		0x03
#घोषणा PM8226_SUBTYPE		0x04
#घोषणा PM8110_SUBTYPE		0x05
#घोषणा PMA8084_SUBTYPE		0x06
#घोषणा PMI8962_SUBTYPE		0x07
#घोषणा PMD9635_SUBTYPE		0x08
#घोषणा PM8994_SUBTYPE		0x09
#घोषणा PMI8994_SUBTYPE		0x0a
#घोषणा PM8916_SUBTYPE		0x0b
#घोषणा PM8004_SUBTYPE		0x0c
#घोषणा PM8909_SUBTYPE		0x0d
#घोषणा PM8950_SUBTYPE		0x10
#घोषणा PMI8950_SUBTYPE		0x11
#घोषणा PM8998_SUBTYPE		0x14
#घोषणा PMI8998_SUBTYPE		0x15
#घोषणा PM8005_SUBTYPE		0x18
#घोषणा PM660L_SUBTYPE		0x1A
#घोषणा PM660_SUBTYPE		0x1B

अटल स्थिर काष्ठा of_device_id pmic_spmi_id_table[] = अणु
	अणु .compatible = "qcom,spmi-pmic", .data = (व्योम *)COMMON_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pm8941",    .data = (व्योम *)PM8941_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pm8841",    .data = (व्योम *)PM8841_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pm8019",    .data = (व्योम *)PM8019_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pm8226",    .data = (व्योम *)PM8226_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pm8110",    .data = (व्योम *)PM8110_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pma8084",   .data = (व्योम *)PMA8084_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pmi8962",   .data = (व्योम *)PMI8962_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pmd9635",   .data = (व्योम *)PMD9635_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pm8994",    .data = (व्योम *)PM8994_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pmi8994",   .data = (व्योम *)PMI8994_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pm8916",    .data = (व्योम *)PM8916_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pm8004",    .data = (व्योम *)PM8004_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pm8909",    .data = (व्योम *)PM8909_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pm8950",    .data = (व्योम *)PM8950_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pmi8950",   .data = (व्योम *)PMI8950_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pm8998",    .data = (व्योम *)PM8998_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pmi8998",   .data = (व्योम *)PMI8998_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pm8005",    .data = (व्योम *)PM8005_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pm660l",    .data = (व्योम *)PM660L_SUBTYPE पूर्ण,
	अणु .compatible = "qcom,pm660",     .data = (व्योम *)PM660_SUBTYPE पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम pmic_spmi_show_revid(काष्ठा regmap *map, काष्ठा device *dev)
अणु
	अचिन्हित पूर्णांक rev2, minor, major, type, subtype;
	स्थिर अक्षर *name = "unknown";
	पूर्णांक ret, i;

	ret = regmap_पढ़ो(map, PMIC_TYPE, &type);
	अगर (ret < 0)
		वापस;

	अगर (type != PMIC_TYPE_VALUE)
		वापस;

	ret = regmap_पढ़ो(map, PMIC_SUBTYPE, &subtype);
	अगर (ret < 0)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(pmic_spmi_id_table); i++) अणु
		अगर (subtype == (अचिन्हित दीर्घ)pmic_spmi_id_table[i].data)
			अवरोध;
	पूर्ण

	अगर (i != ARRAY_SIZE(pmic_spmi_id_table))
		name = pmic_spmi_id_table[i].compatible;

	ret = regmap_पढ़ो(map, PMIC_REV2, &rev2);
	अगर (ret < 0)
		वापस;

	ret = regmap_पढ़ो(map, PMIC_REV3, &minor);
	अगर (ret < 0)
		वापस;

	ret = regmap_पढ़ो(map, PMIC_REV4, &major);
	अगर (ret < 0)
		वापस;

	/*
	 * In early versions of PM8941 and PM8226, the major revision number
	 * started incrementing from 0 (eg 0 = v1.0, 1 = v2.0).
	 * Increment the major revision number here अगर the chip is an early
	 * version of PM8941 or PM8226.
	 */
	अगर ((subtype == PM8941_SUBTYPE || subtype == PM8226_SUBTYPE) &&
	    major < 0x02)
		major++;

	अगर (subtype == PM8110_SUBTYPE)
		minor = rev2;

	dev_dbg(dev, "%x: %s v%d.%d\n", subtype, name, major, minor);
पूर्ण

अटल स्थिर काष्ठा regmap_config spmi_regmap_config = अणु
	.reg_bits	= 16,
	.val_bits	= 8,
	.max_रेजिस्टर	= 0xffff,
	.fast_io	= true,
पूर्ण;

अटल पूर्णांक pmic_spmi_probe(काष्ठा spmi_device *sdev)
अणु
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_spmi_ext(sdev, &spmi_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* Only the first slave id क्रम a PMIC contains this inक्रमmation */
	अगर (sdev->usid % 2 == 0)
		pmic_spmi_show_revid(regmap, &sdev->dev);

	वापस devm_of_platक्रमm_populate(&sdev->dev);
पूर्ण

MODULE_DEVICE_TABLE(of, pmic_spmi_id_table);

अटल काष्ठा spmi_driver pmic_spmi_driver = अणु
	.probe = pmic_spmi_probe,
	.driver = अणु
		.name = "pmic-spmi",
		.of_match_table = pmic_spmi_id_table,
	पूर्ण,
पूर्ण;
module_spmi_driver(pmic_spmi_driver);

MODULE_DESCRIPTION("Qualcomm SPMI PMIC driver");
MODULE_ALIAS("spmi:spmi-pmic");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Josh Cartwright <joshc@codeaurora.org>");
MODULE_AUTHOR("Stanimir Varbanov <svarbanov@mm-sol.com>");
