<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * TI K3 SoC info driver
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com
 */

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/regmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/sys_soc.h>

#घोषणा CTRLMMR_WKUP_JTAGID_REG		0
/*
 * Bits:
 *  31-28 VARIANT	Device variant
 *  27-12 PARTNO	Part number
 *  11-1  MFG		Indicates TI as manufacturer (0x17)
 *  1			Always 1
 */
#घोषणा CTRLMMR_WKUP_JTAGID_VARIANT_SHIFT	(28)
#घोषणा CTRLMMR_WKUP_JTAGID_VARIANT_MASK	GENMASK(31, 28)

#घोषणा CTRLMMR_WKUP_JTAGID_PARTNO_SHIFT	(12)
#घोषणा CTRLMMR_WKUP_JTAGID_PARTNO_MASK		GENMASK(27, 12)

#घोषणा CTRLMMR_WKUP_JTAGID_MFG_SHIFT		(1)
#घोषणा CTRLMMR_WKUP_JTAGID_MFG_MASK		GENMASK(11, 1)

#घोषणा CTRLMMR_WKUP_JTAGID_MFG_TI		0x17

अटल स्थिर काष्ठा k3_soc_id अणु
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *family_name;
पूर्ण k3_soc_ids[] = अणु
	अणु 0xBB5A, "AM65X" पूर्ण,
	अणु 0xBB64, "J721E" पूर्ण,
	अणु 0xBB6D, "J7200" पूर्ण,
	अणु 0xBB38, "AM64X" पूर्ण
पूर्ण;

अटल पूर्णांक
k3_chipinfo_partno_to_names(अचिन्हित पूर्णांक partno,
			    काष्ठा soc_device_attribute *soc_dev_attr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(k3_soc_ids); i++)
		अगर (partno == k3_soc_ids[i].id) अणु
			soc_dev_attr->family = k3_soc_ids[i].family_name;
			वापस 0;
		पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक k3_chipinfo_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा soc_device_attribute *soc_dev_attr;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा soc_device *soc_dev;
	काष्ठा regmap *regmap;
	u32 partno_id;
	u32 variant;
	u32 jtag_id;
	u32 mfg;
	पूर्णांक ret;

	regmap = device_node_to_regmap(node);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	ret = regmap_पढ़ो(regmap, CTRLMMR_WKUP_JTAGID_REG, &jtag_id);
	अगर (ret < 0)
		वापस ret;

	mfg = (jtag_id & CTRLMMR_WKUP_JTAGID_MFG_MASK) >>
	       CTRLMMR_WKUP_JTAGID_MFG_SHIFT;

	अगर (mfg != CTRLMMR_WKUP_JTAGID_MFG_TI) अणु
		dev_err(dev, "Invalid MFG SoC\n");
		वापस -ENODEV;
	पूर्ण

	variant = (jtag_id & CTRLMMR_WKUP_JTAGID_VARIANT_MASK) >>
		  CTRLMMR_WKUP_JTAGID_VARIANT_SHIFT;
	variant++;

	partno_id = (jtag_id & CTRLMMR_WKUP_JTAGID_PARTNO_MASK) >>
		 CTRLMMR_WKUP_JTAGID_PARTNO_SHIFT;

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr)
		वापस -ENOMEM;

	soc_dev_attr->revision = kaप्र_लिखो(GFP_KERNEL, "SR%x.0", variant);
	अगर (!soc_dev_attr->revision) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = k3_chipinfo_partno_to_names(partno_id, soc_dev_attr);
	अगर (ret) अणु
		dev_err(dev, "Unknown SoC JTAGID[0x%08X]\n", jtag_id);
		ret = -ENODEV;
		जाओ err_मुक्त_rev;
	पूर्ण

	node = of_find_node_by_path("/");
	of_property_पढ़ो_string(node, "model", &soc_dev_attr->machine);
	of_node_put(node);

	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev)) अणु
		ret = PTR_ERR(soc_dev);
		जाओ err_मुक्त_rev;
	पूर्ण

	dev_info(dev, "Family:%s rev:%s JTAGID[0x%08x] Detected\n",
		 soc_dev_attr->family,
		 soc_dev_attr->revision, jtag_id);

	वापस 0;

err_मुक्त_rev:
	kमुक्त(soc_dev_attr->revision);
err:
	kमुक्त(soc_dev_attr);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id k3_chipinfo_of_match[] = अणु
	अणु .compatible = "ti,am654-chipid", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver k3_chipinfo_driver = अणु
	.driver = अणु
		.name = "k3-chipinfo",
		.of_match_table = k3_chipinfo_of_match,
	पूर्ण,
	.probe = k3_chipinfo_probe,
पूर्ण;

अटल पूर्णांक __init k3_chipinfo_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&k3_chipinfo_driver);
पूर्ण
subsys_initcall(k3_chipinfo_init);
