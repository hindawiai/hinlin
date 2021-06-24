<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2016, Fuzhou Rockchip Electronics Co., Ltd
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/reboot-mode.h>

काष्ठा syscon_reboot_mode अणु
	काष्ठा regmap *map;
	काष्ठा reboot_mode_driver reboot;
	u32 offset;
	u32 mask;
पूर्ण;

अटल पूर्णांक syscon_reboot_mode_ग_लिखो(काष्ठा reboot_mode_driver *reboot,
				    अचिन्हित पूर्णांक magic)
अणु
	काष्ठा syscon_reboot_mode *syscon_rbm;
	पूर्णांक ret;

	syscon_rbm = container_of(reboot, काष्ठा syscon_reboot_mode, reboot);

	ret = regmap_update_bits(syscon_rbm->map, syscon_rbm->offset,
				 syscon_rbm->mask, magic);
	अगर (ret < 0)
		dev_err(reboot->dev, "update reboot mode bits failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक syscon_reboot_mode_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा syscon_reboot_mode *syscon_rbm;

	syscon_rbm = devm_kzalloc(&pdev->dev, माप(*syscon_rbm), GFP_KERNEL);
	अगर (!syscon_rbm)
		वापस -ENOMEM;

	syscon_rbm->reboot.dev = &pdev->dev;
	syscon_rbm->reboot.ग_लिखो = syscon_reboot_mode_ग_लिखो;
	syscon_rbm->mask = 0xffffffff;

	syscon_rbm->map = syscon_node_to_regmap(pdev->dev.parent->of_node);
	अगर (IS_ERR(syscon_rbm->map))
		वापस PTR_ERR(syscon_rbm->map);

	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "offset",
	    &syscon_rbm->offset))
		वापस -EINVAL;

	of_property_पढ़ो_u32(pdev->dev.of_node, "mask", &syscon_rbm->mask);

	ret = devm_reboot_mode_रेजिस्टर(&pdev->dev, &syscon_rbm->reboot);
	अगर (ret)
		dev_err(&pdev->dev, "can't register reboot mode\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id syscon_reboot_mode_of_match[] = अणु
	अणु .compatible = "syscon-reboot-mode" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, syscon_reboot_mode_of_match);

अटल काष्ठा platक्रमm_driver syscon_reboot_mode_driver = अणु
	.probe = syscon_reboot_mode_probe,
	.driver = अणु
		.name = "syscon-reboot-mode",
		.of_match_table = syscon_reboot_mode_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(syscon_reboot_mode_driver);

MODULE_AUTHOR("Andy Yan <andy.yan@rock-chips.com");
MODULE_DESCRIPTION("SYSCON reboot mode driver");
MODULE_LICENSE("GPL v2");
