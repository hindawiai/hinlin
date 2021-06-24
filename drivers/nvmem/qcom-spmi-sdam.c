<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017, 2020-2021, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/regmap.h>

#घोषणा SDAM_MEM_START			0x40
#घोषणा REGISTER_MAP_ID			0x40
#घोषणा REGISTER_MAP_VERSION		0x41
#घोषणा SDAM_SIZE			0x44
#घोषणा SDAM_PBS_TRIG_SET		0xE5
#घोषणा SDAM_PBS_TRIG_CLR		0xE6

काष्ठा sdam_chip अणु
	काष्ठा regmap			*regmap;
	काष्ठा nvmem_config		sdam_config;
	अचिन्हित पूर्णांक			base;
	अचिन्हित पूर्णांक			size;
पूर्ण;

/* पढ़ो only रेजिस्टर offsets */
अटल स्थिर u8 sdam_ro_map[] = अणु
	REGISTER_MAP_ID,
	REGISTER_MAP_VERSION,
	SDAM_SIZE
पूर्ण;

अटल bool sdam_is_valid(काष्ठा sdam_chip *sdam, अचिन्हित पूर्णांक offset,
				माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक sdam_mem_end = SDAM_MEM_START + sdam->size - 1;

	अगर (!len)
		वापस false;

	अगर (offset >= SDAM_MEM_START && offset <= sdam_mem_end
				&& (offset + len - 1) <= sdam_mem_end)
		वापस true;
	अन्यथा अगर ((offset == SDAM_PBS_TRIG_SET || offset == SDAM_PBS_TRIG_CLR)
				&& (len == 1))
		वापस true;

	वापस false;
पूर्ण

अटल bool sdam_is_ro(अचिन्हित पूर्णांक offset, माप_प्रकार len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sdam_ro_map); i++)
		अगर (offset <= sdam_ro_map[i] && (offset + len) > sdam_ro_map[i])
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक sdam_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
				माप_प्रकार bytes)
अणु
	काष्ठा sdam_chip *sdam = priv;
	काष्ठा device *dev = sdam->sdam_config.dev;
	पूर्णांक rc;

	अगर (!sdam_is_valid(sdam, offset, bytes)) अणु
		dev_err(dev, "Invalid SDAM offset %#x len=%zd\n",
			offset, bytes);
		वापस -EINVAL;
	पूर्ण

	rc = regmap_bulk_पढ़ो(sdam->regmap, sdam->base + offset, val, bytes);
	अगर (rc < 0)
		dev_err(dev, "Failed to read SDAM offset %#x len=%zd, rc=%d\n",
						offset, bytes, rc);

	वापस rc;
पूर्ण

अटल पूर्णांक sdam_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
				माप_प्रकार bytes)
अणु
	काष्ठा sdam_chip *sdam = priv;
	काष्ठा device *dev = sdam->sdam_config.dev;
	पूर्णांक rc;

	अगर (!sdam_is_valid(sdam, offset, bytes)) अणु
		dev_err(dev, "Invalid SDAM offset %#x len=%zd\n",
			offset, bytes);
		वापस -EINVAL;
	पूर्ण

	अगर (sdam_is_ro(offset, bytes)) अणु
		dev_err(dev, "Invalid write offset %#x len=%zd\n",
			offset, bytes);
		वापस -EINVAL;
	पूर्ण

	rc = regmap_bulk_ग_लिखो(sdam->regmap, sdam->base + offset, val, bytes);
	अगर (rc < 0)
		dev_err(dev, "Failed to write SDAM offset %#x len=%zd, rc=%d\n",
						offset, bytes, rc);

	वापस rc;
पूर्ण

अटल पूर्णांक sdam_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdam_chip *sdam;
	काष्ठा nvmem_device *nvmem;
	अचिन्हित पूर्णांक val;
	पूर्णांक rc;

	sdam = devm_kzalloc(&pdev->dev, माप(*sdam), GFP_KERNEL);
	अगर (!sdam)
		वापस -ENOMEM;

	sdam->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!sdam->regmap) अणु
		dev_err(&pdev->dev, "Failed to get regmap handle\n");
		वापस -ENXIO;
	पूर्ण

	rc = of_property_पढ़ो_u32(pdev->dev.of_node, "reg", &sdam->base);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Failed to get SDAM base, rc=%d\n", rc);
		वापस -EINVAL;
	पूर्ण

	rc = regmap_पढ़ो(sdam->regmap, sdam->base + SDAM_SIZE, &val);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Failed to read SDAM_SIZE rc=%d\n", rc);
		वापस -EINVAL;
	पूर्ण
	sdam->size = val * 32;

	sdam->sdam_config.dev = &pdev->dev;
	sdam->sdam_config.name = "spmi_sdam";
	sdam->sdam_config.id = NVMEM_DEVID_AUTO;
	sdam->sdam_config.owner = THIS_MODULE;
	sdam->sdam_config.stride = 1;
	sdam->sdam_config.word_size = 1;
	sdam->sdam_config.reg_पढ़ो = sdam_पढ़ो;
	sdam->sdam_config.reg_ग_लिखो = sdam_ग_लिखो;
	sdam->sdam_config.priv = sdam;

	nvmem = devm_nvmem_रेजिस्टर(&pdev->dev, &sdam->sdam_config);
	अगर (IS_ERR(nvmem)) अणु
		dev_err(&pdev->dev,
			"Failed to register SDAM nvmem device rc=%ld\n",
			PTR_ERR(nvmem));
		वापस -ENXIO;
	पूर्ण
	dev_dbg(&pdev->dev,
		"SDAM base=%#x size=%u registered successfully\n",
		sdam->base, sdam->size);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sdam_match_table[] = अणु
	अणु .compatible = "qcom,spmi-sdam" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver sdam_driver = अणु
	.driver = अणु
		.name = "qcom,spmi-sdam",
		.of_match_table = sdam_match_table,
	पूर्ण,
	.probe		= sdam_probe,
पूर्ण;

अटल पूर्णांक __init sdam_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sdam_driver);
पूर्ण
subsys_initcall(sdam_init);

अटल व्योम __निकास sdam_निकास(व्योम)
अणु
	वापस platक्रमm_driver_unरेजिस्टर(&sdam_driver);
पूर्ण
module_निकास(sdam_निकास);

MODULE_DESCRIPTION("QCOM SPMI SDAM driver");
MODULE_LICENSE("GPL v2");
