<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015, Samsung Electronics Co., Ltd.
 *
 * Author: Marek Szyprowski <m.szyprowski@samsung.com>
 *
 * Simple eMMC hardware reset provider
 */
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/reboot.h>

#समावेश <linux/mmc/host.h>

#समावेश "pwrseq.h"

काष्ठा mmc_pwrseq_emmc अणु
	काष्ठा mmc_pwrseq pwrseq;
	काष्ठा notअगरier_block reset_nb;
	काष्ठा gpio_desc *reset_gpio;
पूर्ण;

#घोषणा to_pwrseq_emmc(p) container_of(p, काष्ठा mmc_pwrseq_emmc, pwrseq)

अटल व्योम mmc_pwrseq_emmc_reset(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_pwrseq_emmc *pwrseq =  to_pwrseq_emmc(host->pwrseq);

	gpiod_set_value_cansleep(pwrseq->reset_gpio, 1);
	udelay(1);
	gpiod_set_value_cansleep(pwrseq->reset_gpio, 0);
	udelay(200);
पूर्ण

अटल पूर्णांक mmc_pwrseq_emmc_reset_nb(काष्ठा notअगरier_block *this,
				    अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	काष्ठा mmc_pwrseq_emmc *pwrseq = container_of(this,
					काष्ठा mmc_pwrseq_emmc, reset_nb);
	gpiod_set_value(pwrseq->reset_gpio, 1);
	udelay(1);
	gpiod_set_value(pwrseq->reset_gpio, 0);
	udelay(200);

	वापस NOTIFY_DONE;
पूर्ण

अटल स्थिर काष्ठा mmc_pwrseq_ops mmc_pwrseq_emmc_ops = अणु
	.reset = mmc_pwrseq_emmc_reset,
पूर्ण;

अटल पूर्णांक mmc_pwrseq_emmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_pwrseq_emmc *pwrseq;
	काष्ठा device *dev = &pdev->dev;

	pwrseq = devm_kzalloc(dev, माप(*pwrseq), GFP_KERNEL);
	अगर (!pwrseq)
		वापस -ENOMEM;

	pwrseq->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(pwrseq->reset_gpio))
		वापस PTR_ERR(pwrseq->reset_gpio);

	अगर (!gpiod_cansleep(pwrseq->reset_gpio)) अणु
		/*
		 * रेजिस्टर reset handler to ensure emmc reset also from
		 * emergency_reboot(), priority 255 is the highest priority
		 * so it will be executed beक्रमe any प्रणाली reboot handler.
		 */
		pwrseq->reset_nb.notअगरier_call = mmc_pwrseq_emmc_reset_nb;
		pwrseq->reset_nb.priority = 255;
		रेजिस्टर_restart_handler(&pwrseq->reset_nb);
	पूर्ण अन्यथा अणु
		dev_notice(dev, "EMMC reset pin tied to a sleepy GPIO driver; reset on emergency-reboot disabled\n");
	पूर्ण

	pwrseq->pwrseq.ops = &mmc_pwrseq_emmc_ops;
	pwrseq->pwrseq.dev = dev;
	pwrseq->pwrseq.owner = THIS_MODULE;
	platक्रमm_set_drvdata(pdev, pwrseq);

	वापस mmc_pwrseq_रेजिस्टर(&pwrseq->pwrseq);
पूर्ण

अटल पूर्णांक mmc_pwrseq_emmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_pwrseq_emmc *pwrseq = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_restart_handler(&pwrseq->reset_nb);
	mmc_pwrseq_unरेजिस्टर(&pwrseq->pwrseq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mmc_pwrseq_emmc_of_match[] = अणु
	अणु .compatible = "mmc-pwrseq-emmc",पूर्ण,
	अणु/* sentinel */पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, mmc_pwrseq_emmc_of_match);

अटल काष्ठा platक्रमm_driver mmc_pwrseq_emmc_driver = अणु
	.probe = mmc_pwrseq_emmc_probe,
	.हटाओ = mmc_pwrseq_emmc_हटाओ,
	.driver = अणु
		.name = "pwrseq_emmc",
		.of_match_table = mmc_pwrseq_emmc_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mmc_pwrseq_emmc_driver);
MODULE_LICENSE("GPL v2");
