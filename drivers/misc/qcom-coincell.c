<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2013, The Linux Foundation. All rights reserved.
 * Copyright (c) 2015, Sony Mobile Communications Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा qcom_coincell अणु
	काष्ठा device	*dev;
	काष्ठा regmap	*regmap;
	u32		base_addr;
पूर्ण;

#घोषणा QCOM_COINCELL_REG_RSET		0x44
#घोषणा QCOM_COINCELL_REG_VSET		0x45
#घोषणा QCOM_COINCELL_REG_ENABLE	0x46

#घोषणा QCOM_COINCELL_ENABLE		BIT(7)

अटल स्थिर पूर्णांक qcom_rset_map[] = अणु 2100, 1700, 1200, 800 पूर्ण;
अटल स्थिर पूर्णांक qcom_vset_map[] = अणु 2500, 3200, 3100, 3000 पूर्ण;
/* NOTE: क्रम pm8921 and others, voltage of 2500 is 16 (10000b), not 0 */

/* अगर enable==0, rset and vset are ignored */
अटल पूर्णांक qcom_coincell_chgr_config(काष्ठा qcom_coincell *chgr, पूर्णांक rset,
				     पूर्णांक vset, bool enable)
अणु
	पूर्णांक i, j, rc;

	/* अगर disabling, just करो that and skip other operations */
	अगर (!enable)
		वापस regmap_ग_लिखो(chgr->regmap,
			  chgr->base_addr + QCOM_COINCELL_REG_ENABLE, 0);

	/* find index क्रम current-limiting resistor */
	क्रम (i = 0; i < ARRAY_SIZE(qcom_rset_map); i++)
		अगर (rset == qcom_rset_map[i])
			अवरोध;

	अगर (i >= ARRAY_SIZE(qcom_rset_map)) अणु
		dev_err(chgr->dev, "invalid rset-ohms value %d\n", rset);
		वापस -EINVAL;
	पूर्ण

	/* find index क्रम अक्षरge voltage */
	क्रम (j = 0; j < ARRAY_SIZE(qcom_vset_map); j++)
		अगर (vset == qcom_vset_map[j])
			अवरोध;

	अगर (j >= ARRAY_SIZE(qcom_vset_map)) अणु
		dev_err(chgr->dev, "invalid vset-millivolts value %d\n", vset);
		वापस -EINVAL;
	पूर्ण

	rc = regmap_ग_लिखो(chgr->regmap,
			  chgr->base_addr + QCOM_COINCELL_REG_RSET, i);
	अगर (rc) अणु
		/*
		 * This is मुख्यly to flag a bad base_addr (reg) from dts.
		 * Other failures writing to the रेजिस्टरs should be
		 * extremely rare, or indicative of problems that
		 * should be reported अन्यथाwhere (eg. spmi failure).
		 */
		dev_err(chgr->dev, "could not write to RSET register\n");
		वापस rc;
	पूर्ण

	rc = regmap_ग_लिखो(chgr->regmap,
		chgr->base_addr + QCOM_COINCELL_REG_VSET, j);
	अगर (rc)
		वापस rc;

	/* set 'enable' रेजिस्टर */
	वापस regmap_ग_लिखो(chgr->regmap,
			    chgr->base_addr + QCOM_COINCELL_REG_ENABLE,
			    QCOM_COINCELL_ENABLE);
पूर्ण

अटल पूर्णांक qcom_coincell_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा qcom_coincell chgr;
	u32 rset = 0;
	u32 vset = 0;
	bool enable;
	पूर्णांक rc;

	chgr.dev = &pdev->dev;

	chgr.regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!chgr.regmap) अणु
		dev_err(chgr.dev, "Unable to get regmap\n");
		वापस -EINVAL;
	पूर्ण

	rc = of_property_पढ़ो_u32(node, "reg", &chgr.base_addr);
	अगर (rc)
		वापस rc;

	enable = !of_property_पढ़ो_bool(node, "qcom,charger-disable");

	अगर (enable) अणु
		rc = of_property_पढ़ो_u32(node, "qcom,rset-ohms", &rset);
		अगर (rc) अणु
			dev_err(chgr.dev,
				"can't find 'qcom,rset-ohms' in DT block");
			वापस rc;
		पूर्ण

		rc = of_property_पढ़ो_u32(node, "qcom,vset-millivolts", &vset);
		अगर (rc) अणु
			dev_err(chgr.dev,
			    "can't find 'qcom,vset-millivolts' in DT block");
			वापस rc;
		पूर्ण
	पूर्ण

	वापस qcom_coincell_chgr_config(&chgr, rset, vset, enable);
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_coincell_match_table[] = अणु
	अणु .compatible = "qcom,pm8941-coincell", पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, qcom_coincell_match_table);

अटल काष्ठा platक्रमm_driver qcom_coincell_driver = अणु
	.driver	= अणु
		.name		= "qcom-spmi-coincell",
		.of_match_table	= qcom_coincell_match_table,
	पूर्ण,
	.probe		= qcom_coincell_probe,
पूर्ण;

module_platक्रमm_driver(qcom_coincell_driver);

MODULE_DESCRIPTION("Qualcomm PMIC coincell charger driver");
MODULE_LICENSE("GPL v2");
