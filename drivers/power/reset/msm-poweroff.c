<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/reboot.h>
#समावेश <linux/pm.h>

अटल व्योम __iomem *msm_ps_hold;
अटल पूर्णांक deनिश्चित_pshold(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			   व्योम *data)
अणु
	ग_लिखोl(0, msm_ps_hold);
	mdelay(10000);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block restart_nb = अणु
	.notअगरier_call = deनिश्चित_pshold,
	.priority = 128,
पूर्ण;

अटल व्योम करो_msm_घातeroff(व्योम)
अणु
	deनिश्चित_pshold(&restart_nb, 0, शून्य);
पूर्ण

अटल पूर्णांक msm_restart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *mem;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	msm_ps_hold = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(msm_ps_hold))
		वापस PTR_ERR(msm_ps_hold);

	रेजिस्टर_restart_handler(&restart_nb);

	pm_घातer_off = करो_msm_घातeroff;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_msm_restart_match[] = अणु
	अणु .compatible = "qcom,pshold", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_msm_restart_match);

अटल काष्ठा platक्रमm_driver msm_restart_driver = अणु
	.probe = msm_restart_probe,
	.driver = अणु
		.name = "msm-restart",
		.of_match_table = of_match_ptr(of_msm_restart_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init msm_restart_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&msm_restart_driver);
पूर्ण
device_initcall(msm_restart_init);
