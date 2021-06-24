<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019 Xilinx, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/firmware/xlnx-zynqmp.h>

#घोषणा SILICON_REVISION_MASK 0xF

काष्ठा zynqmp_nvmem_data अणु
	काष्ठा device *dev;
	काष्ठा nvmem_device *nvmem;
पूर्ण;

अटल पूर्णांक zynqmp_nvmem_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
			     व्योम *val, माप_प्रकार bytes)
अणु
	पूर्णांक ret;
	पूर्णांक idcode, version;
	काष्ठा zynqmp_nvmem_data *priv = context;

	ret = zynqmp_pm_get_chipid(&idcode, &version);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(priv->dev, "Read chipid val %x %x\n", idcode, version);
	*(पूर्णांक *)val = version & SILICON_REVISION_MASK;

	वापस 0;
पूर्ण

अटल काष्ठा nvmem_config econfig = अणु
	.name = "zynqmp-nvmem",
	.owner = THIS_MODULE,
	.word_size = 1,
	.size = 1,
	.पढ़ो_only = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id zynqmp_nvmem_match[] = अणु
	अणु .compatible = "xlnx,zynqmp-nvmem-fw", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, zynqmp_nvmem_match);

अटल पूर्णांक zynqmp_nvmem_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा zynqmp_nvmem_data *priv;

	priv = devm_kzalloc(dev, माप(काष्ठा zynqmp_nvmem_data), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	econfig.dev = dev;
	econfig.reg_पढ़ो = zynqmp_nvmem_पढ़ो;
	econfig.priv = priv;

	priv->nvmem = devm_nvmem_रेजिस्टर(dev, &econfig);

	वापस PTR_ERR_OR_ZERO(priv->nvmem);
पूर्ण

अटल काष्ठा platक्रमm_driver zynqmp_nvmem_driver = अणु
	.probe = zynqmp_nvmem_probe,
	.driver = अणु
		.name = "zynqmp-nvmem",
		.of_match_table = zynqmp_nvmem_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(zynqmp_nvmem_driver);

MODULE_AUTHOR("Michal Simek <michal.simek@xilinx.com>, Nava kishore Manne <navam@xilinx.com>");
MODULE_DESCRIPTION("ZynqMP NVMEM driver");
MODULE_LICENSE("GPL");
