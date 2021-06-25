<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2014 Linaro Ltd
 *
 * Author: Ulf Hansson <ulf.hansson@linaro.org>
 *
 *  Simple MMC घातer sequence management
 */
#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>
#समावेश <linux/property.h>

#समावेश <linux/mmc/host.h>

#समावेश "pwrseq.h"

काष्ठा mmc_pwrseq_simple अणु
	काष्ठा mmc_pwrseq pwrseq;
	bool clk_enabled;
	u32 post_घातer_on_delay_ms;
	u32 घातer_off_delay_us;
	काष्ठा clk *ext_clk;
	काष्ठा gpio_descs *reset_gpios;
पूर्ण;

#घोषणा to_pwrseq_simple(p) container_of(p, काष्ठा mmc_pwrseq_simple, pwrseq)

अटल व्योम mmc_pwrseq_simple_set_gpios_value(काष्ठा mmc_pwrseq_simple *pwrseq,
					      पूर्णांक value)
अणु
	काष्ठा gpio_descs *reset_gpios = pwrseq->reset_gpios;

	अगर (!IS_ERR(reset_gpios)) अणु
		अचिन्हित दीर्घ *values;
		पूर्णांक nvalues = reset_gpios->ndescs;

		values = biपंचांगap_alloc(nvalues, GFP_KERNEL);
		अगर (!values)
			वापस;

		अगर (value)
			biपंचांगap_fill(values, nvalues);
		अन्यथा
			biपंचांगap_zero(values, nvalues);

		gpiod_set_array_value_cansleep(nvalues, reset_gpios->desc,
					       reset_gpios->info, values);

		kमुक्त(values);
	पूर्ण
पूर्ण

अटल व्योम mmc_pwrseq_simple_pre_घातer_on(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_pwrseq_simple *pwrseq = to_pwrseq_simple(host->pwrseq);

	अगर (!IS_ERR(pwrseq->ext_clk) && !pwrseq->clk_enabled) अणु
		clk_prepare_enable(pwrseq->ext_clk);
		pwrseq->clk_enabled = true;
	पूर्ण

	mmc_pwrseq_simple_set_gpios_value(pwrseq, 1);
पूर्ण

अटल व्योम mmc_pwrseq_simple_post_घातer_on(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_pwrseq_simple *pwrseq = to_pwrseq_simple(host->pwrseq);

	mmc_pwrseq_simple_set_gpios_value(pwrseq, 0);

	अगर (pwrseq->post_घातer_on_delay_ms)
		msleep(pwrseq->post_घातer_on_delay_ms);
पूर्ण

अटल व्योम mmc_pwrseq_simple_घातer_off(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_pwrseq_simple *pwrseq = to_pwrseq_simple(host->pwrseq);

	mmc_pwrseq_simple_set_gpios_value(pwrseq, 1);

	अगर (pwrseq->घातer_off_delay_us)
		usleep_range(pwrseq->घातer_off_delay_us,
			2 * pwrseq->घातer_off_delay_us);

	अगर (!IS_ERR(pwrseq->ext_clk) && pwrseq->clk_enabled) अणु
		clk_disable_unprepare(pwrseq->ext_clk);
		pwrseq->clk_enabled = false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा mmc_pwrseq_ops mmc_pwrseq_simple_ops = अणु
	.pre_घातer_on = mmc_pwrseq_simple_pre_घातer_on,
	.post_घातer_on = mmc_pwrseq_simple_post_घातer_on,
	.घातer_off = mmc_pwrseq_simple_घातer_off,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mmc_pwrseq_simple_of_match[] = अणु
	अणु .compatible = "mmc-pwrseq-simple",पूर्ण,
	अणु/* sentinel */पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mmc_pwrseq_simple_of_match);

अटल पूर्णांक mmc_pwrseq_simple_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_pwrseq_simple *pwrseq;
	काष्ठा device *dev = &pdev->dev;

	pwrseq = devm_kzalloc(dev, माप(*pwrseq), GFP_KERNEL);
	अगर (!pwrseq)
		वापस -ENOMEM;

	pwrseq->ext_clk = devm_clk_get(dev, "ext_clock");
	अगर (IS_ERR(pwrseq->ext_clk) && PTR_ERR(pwrseq->ext_clk) != -ENOENT)
		वापस PTR_ERR(pwrseq->ext_clk);

	pwrseq->reset_gpios = devm_gpiod_get_array(dev, "reset",
							GPIOD_OUT_HIGH);
	अगर (IS_ERR(pwrseq->reset_gpios) &&
	    PTR_ERR(pwrseq->reset_gpios) != -ENOENT &&
	    PTR_ERR(pwrseq->reset_gpios) != -ENOSYS) अणु
		वापस PTR_ERR(pwrseq->reset_gpios);
	पूर्ण

	device_property_पढ़ो_u32(dev, "post-power-on-delay-ms",
				 &pwrseq->post_घातer_on_delay_ms);
	device_property_पढ़ो_u32(dev, "power-off-delay-us",
				 &pwrseq->घातer_off_delay_us);

	pwrseq->pwrseq.dev = dev;
	pwrseq->pwrseq.ops = &mmc_pwrseq_simple_ops;
	pwrseq->pwrseq.owner = THIS_MODULE;
	platक्रमm_set_drvdata(pdev, pwrseq);

	वापस mmc_pwrseq_रेजिस्टर(&pwrseq->pwrseq);
पूर्ण

अटल पूर्णांक mmc_pwrseq_simple_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmc_pwrseq_simple *pwrseq = platक्रमm_get_drvdata(pdev);

	mmc_pwrseq_unरेजिस्टर(&pwrseq->pwrseq);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mmc_pwrseq_simple_driver = अणु
	.probe = mmc_pwrseq_simple_probe,
	.हटाओ = mmc_pwrseq_simple_हटाओ,
	.driver = अणु
		.name = "pwrseq_simple",
		.of_match_table = mmc_pwrseq_simple_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mmc_pwrseq_simple_driver);
MODULE_LICENSE("GPL v2");
