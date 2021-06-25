<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HiSilicon SoC reset code
 *
 * Copyright (c) 2014 HiSilicon Ltd.
 * Copyright (c) 2014 Linaro Ltd.
 *
 * Author: Haojian Zhuang <haojian.zhuang@linaro.org>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>

#समावेश <यंत्र/proc-fns.h>

अटल व्योम __iomem *base;
अटल u32 reboot_offset;

अटल पूर्णांक hisi_restart_handler(काष्ठा notअगरier_block *this,
				अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	ग_लिखोl_relaxed(0xdeadbeef, base + reboot_offset);

	जबतक (1)
		cpu_करो_idle();

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block hisi_restart_nb = अणु
	.notअगरier_call = hisi_restart_handler,
	.priority = 128,
पूर्ण;

अटल पूर्णांक hisi_reboot_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक err;

	base = of_iomap(np, 0);
	अगर (!base) अणु
		WARN(1, "failed to map base address");
		वापस -ENODEV;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "reboot-offset", &reboot_offset) < 0) अणु
		pr_err("failed to find reboot-offset property\n");
		iounmap(base);
		वापस -EINVAL;
	पूर्ण

	err = रेजिस्टर_restart_handler(&hisi_restart_nb);
	अगर (err) अणु
		dev_err(&pdev->dev, "cannot register restart handler (err=%d)\n",
			err);
		iounmap(base);
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id hisi_reboot_of_match[] = अणु
	अणु .compatible = "hisilicon,sysctrl" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hisi_reboot_of_match);

अटल काष्ठा platक्रमm_driver hisi_reboot_driver = अणु
	.probe = hisi_reboot_probe,
	.driver = अणु
		.name = "hisi-reboot",
		.of_match_table = hisi_reboot_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(hisi_reboot_driver);
