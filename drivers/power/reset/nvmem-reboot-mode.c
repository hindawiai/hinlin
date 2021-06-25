<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) Vaisala Oyj. All rights reserved.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot-mode.h>

काष्ठा nvmem_reboot_mode अणु
	काष्ठा reboot_mode_driver reboot;
	काष्ठा nvmem_cell *cell;
पूर्ण;

अटल पूर्णांक nvmem_reboot_mode_ग_लिखो(काष्ठा reboot_mode_driver *reboot,
				    अचिन्हित पूर्णांक magic)
अणु
	पूर्णांक ret;
	काष्ठा nvmem_reboot_mode *nvmem_rbm;

	nvmem_rbm = container_of(reboot, काष्ठा nvmem_reboot_mode, reboot);

	ret = nvmem_cell_ग_लिखो(nvmem_rbm->cell, &magic, माप(magic));
	अगर (ret < 0)
		dev_err(reboot->dev, "update reboot mode bits failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक nvmem_reboot_mode_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा nvmem_reboot_mode *nvmem_rbm;

	nvmem_rbm = devm_kzalloc(&pdev->dev, माप(*nvmem_rbm), GFP_KERNEL);
	अगर (!nvmem_rbm)
		वापस -ENOMEM;

	nvmem_rbm->reboot.dev = &pdev->dev;
	nvmem_rbm->reboot.ग_लिखो = nvmem_reboot_mode_ग_लिखो;

	nvmem_rbm->cell = devm_nvmem_cell_get(&pdev->dev, "reboot-mode");
	अगर (IS_ERR(nvmem_rbm->cell)) अणु
		dev_err(&pdev->dev, "failed to get the nvmem cell reboot-mode\n");
		वापस PTR_ERR(nvmem_rbm->cell);
	पूर्ण

	ret = devm_reboot_mode_रेजिस्टर(&pdev->dev, &nvmem_rbm->reboot);
	अगर (ret)
		dev_err(&pdev->dev, "can't register reboot mode\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id nvmem_reboot_mode_of_match[] = अणु
	अणु .compatible = "nvmem-reboot-mode" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, nvmem_reboot_mode_of_match);

अटल काष्ठा platक्रमm_driver nvmem_reboot_mode_driver = अणु
	.probe = nvmem_reboot_mode_probe,
	.driver = अणु
		.name = "nvmem-reboot-mode",
		.of_match_table = nvmem_reboot_mode_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(nvmem_reboot_mode_driver);

MODULE_AUTHOR("Nandor Han <nandor.han@vaisala.com>");
MODULE_DESCRIPTION("NVMEM reboot mode driver");
MODULE_LICENSE("GPL");
