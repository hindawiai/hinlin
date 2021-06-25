<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pwrseq_sd8787.c - घातer sequence support क्रम Marvell SD8787 BT + Wअगरi chip
 *
 * Copyright (C) 2016 Matt Ranostay <matt@ranostay.consulting>
 *
 * Based on the original work pwrseq_simple.c
 *  Copyright (C) 2014 Linaro Ltd
 *  Author: Ulf Hansson <ulf.hansson@linaro.org>
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>

#समावेश <linux/mmc/host.h>

#समावेश "pwrseq.h"

काष्ठा mmc_pwrseq_sd8787 अणु
	काष्ठा mmc_pwrseq pwrseq;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा gpio_desc *pwrdn_gpio;
पूर्ण;

#घोषणा to_pwrseq_sd8787(p) container_of(p, काष्ठा mmc_pwrseq_sd8787, pwrseq)

अटल व्योम mmc_pwrseq_sd8787_pre_घातer_on(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_pwrseq_sd8787 *pwrseq = to_pwrseq_sd8787(host->pwrseq);

	gpiod_set_value_cansleep(pwrseq->reset_gpio, 1);

	msleep(300);
	gpiod_set_value_cansleep(pwrseq->pwrdn_gpio, 1);
पूर्ण

अटल व्योम mmc_pwrseq_sd8787_घातer_off(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_pwrseq_sd8787 *pwrseq = to_pwrseq_sd8787(host->pwrseq);

	gpiod_set_value_cansleep(pwrseq->pwrdn_gpio, 0);
	gpiod_set_value_cansleep(pwrseq->reset_gpio, 0);
पूर्ण

अटल स्थिर काष्ठा mmc_pwrseq_ops mmc_pwrseq_sd8787_ops = अणु
	.pre_घातer_on = mmc_pwrseq_sd8787_pre_घातer_on,
	.घातer_off = mmc_pwrseq_sd8787_घातer_off,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mmc_pwrseq_sd8787_of_match[] = अणु
	अणु .compatible = "mmc-pwrseq-sd8787",पूर्ण,
	अणु/* sentinel */पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mmc_pwrseq_sd8787_of_match);

अटल पूर्णांक mmc_pwrseq_sd8787_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_pwrseq_sd8787 *pwrseq;
	काष्ठा device *dev = &pdev->dev;

	pwrseq = devm_kzalloc(dev, माप(*pwrseq), GFP_KERNEL);
	अगर (!pwrseq)
		वापस -ENOMEM;

	pwrseq->pwrdn_gpio = devm_gpiod_get(dev, "powerdown", GPIOD_OUT_LOW);
	अगर (IS_ERR(pwrseq->pwrdn_gpio))
		वापस PTR_ERR(pwrseq->pwrdn_gpio);

	pwrseq->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(pwrseq->reset_gpio))
		वापस PTR_ERR(pwrseq->reset_gpio);

	pwrseq->pwrseq.dev = dev;
	pwrseq->pwrseq.ops = &mmc_pwrseq_sd8787_ops;
	pwrseq->pwrseq.owner = THIS_MODULE;
	platक्रमm_set_drvdata(pdev, pwrseq);

	वापस mmc_pwrseq_रेजिस्टर(&pwrseq->pwrseq);
पूर्ण

अटल पूर्णांक mmc_pwrseq_sd8787_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_pwrseq_sd8787 *pwrseq = platक्रमm_get_drvdata(pdev);

	mmc_pwrseq_unरेजिस्टर(&pwrseq->pwrseq);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mmc_pwrseq_sd8787_driver = अणु
	.probe = mmc_pwrseq_sd8787_probe,
	.हटाओ = mmc_pwrseq_sd8787_हटाओ,
	.driver = अणु
		.name = "pwrseq_sd8787",
		.of_match_table = mmc_pwrseq_sd8787_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mmc_pwrseq_sd8787_driver);
MODULE_LICENSE("GPL v2");
