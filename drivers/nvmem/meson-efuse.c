<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Amlogic Meson GX eFuse Driver
 *
 * Copyright (c) 2016 Endless Computers, Inc.
 * Author: Carlo Caione <carlo@endlessm.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/firmware/meson/meson_sm.h>

अटल पूर्णांक meson_efuse_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
			    व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा meson_sm_firmware *fw = context;

	वापस meson_sm_call_पढ़ो(fw, (u8 *)val, bytes, SM_EFUSE_READ, offset,
				  bytes, 0, 0, 0);
पूर्ण

अटल पूर्णांक meson_efuse_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक offset,
			     व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा meson_sm_firmware *fw = context;

	वापस meson_sm_call_ग_लिखो(fw, (u8 *)val, bytes, SM_EFUSE_WRITE, offset,
				   bytes, 0, 0, 0);
पूर्ण

अटल स्थिर काष्ठा of_device_id meson_efuse_match[] = अणु
	अणु .compatible = "amlogic,meson-gxbb-efuse", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_efuse_match);

अटल पूर्णांक meson_efuse_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा meson_sm_firmware *fw;
	काष्ठा device_node *sm_np;
	काष्ठा nvmem_device *nvmem;
	काष्ठा nvmem_config *econfig;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक size;
	पूर्णांक ret;

	sm_np = of_parse_phandle(pdev->dev.of_node, "secure-monitor", 0);
	अगर (!sm_np) अणु
		dev_err(&pdev->dev, "no secure-monitor node\n");
		वापस -ENODEV;
	पूर्ण

	fw = meson_sm_get(sm_np);
	of_node_put(sm_np);
	अगर (!fw)
		वापस -EPROBE_DEFER;

	clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get efuse gate");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable gate");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev,
				       (व्योम(*)(व्योम *))clk_disable_unprepare,
				       clk);
	अगर (ret) अणु
		dev_err(dev, "failed to add disable callback");
		वापस ret;
	पूर्ण

	अगर (meson_sm_call(fw, SM_EFUSE_USER_MAX, &size, 0, 0, 0, 0, 0) < 0) अणु
		dev_err(dev, "failed to get max user");
		वापस -EINVAL;
	पूर्ण

	econfig = devm_kzalloc(dev, माप(*econfig), GFP_KERNEL);
	अगर (!econfig)
		वापस -ENOMEM;

	econfig->dev = dev;
	econfig->name = dev_name(dev);
	econfig->stride = 1;
	econfig->word_size = 1;
	econfig->reg_पढ़ो = meson_efuse_पढ़ो;
	econfig->reg_ग_लिखो = meson_efuse_ग_लिखो;
	econfig->size = size;
	econfig->priv = fw;

	nvmem = devm_nvmem_रेजिस्टर(&pdev->dev, econfig);

	वापस PTR_ERR_OR_ZERO(nvmem);
पूर्ण

अटल काष्ठा platक्रमm_driver meson_efuse_driver = अणु
	.probe = meson_efuse_probe,
	.driver = अणु
		.name = "meson-efuse",
		.of_match_table = meson_efuse_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_efuse_driver);

MODULE_AUTHOR("Carlo Caione <carlo@endlessm.com>");
MODULE_DESCRIPTION("Amlogic Meson GX NVMEM driver");
MODULE_LICENSE("GPL v2");
