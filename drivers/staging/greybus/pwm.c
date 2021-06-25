<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PWM Greybus driver.
 *
 * Copyright 2014 Google Inc.
 * Copyright 2014 Linaro Ltd.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pwm.h>
#समावेश <linux/greybus.h>

#समावेश "gbphy.h"

काष्ठा gb_pwm_chip अणु
	काष्ठा gb_connection	*connection;
	u8			pwm_max;	/* max pwm number */

	काष्ठा pwm_chip		chip;
	काष्ठा pwm_chip		*pwm;
पूर्ण;
#घोषणा pwm_chip_to_gb_pwm_chip(chip) \
	container_of(chip, काष्ठा gb_pwm_chip, chip)


अटल पूर्णांक gb_pwm_count_operation(काष्ठा gb_pwm_chip *pwmc)
अणु
	काष्ठा gb_pwm_count_response response;
	पूर्णांक ret;

	ret = gb_operation_sync(pwmc->connection, GB_PWM_TYPE_PWM_COUNT,
				शून्य, 0, &response, माप(response));
	अगर (ret)
		वापस ret;
	pwmc->pwm_max = response.count;
	वापस 0;
पूर्ण

अटल पूर्णांक gb_pwm_activate_operation(काष्ठा gb_pwm_chip *pwmc,
				     u8 which)
अणु
	काष्ठा gb_pwm_activate_request request;
	काष्ठा gbphy_device *gbphy_dev;
	पूर्णांक ret;

	अगर (which > pwmc->pwm_max)
		वापस -EINVAL;

	request.which = which;

	gbphy_dev = to_gbphy_dev(pwmc->chip.dev);
	ret = gbphy_runसमय_get_sync(gbphy_dev);
	अगर (ret)
		वापस ret;

	ret = gb_operation_sync(pwmc->connection, GB_PWM_TYPE_ACTIVATE,
				&request, माप(request), शून्य, 0);

	gbphy_runसमय_put_स्वतःsuspend(gbphy_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_pwm_deactivate_operation(काष्ठा gb_pwm_chip *pwmc,
				       u8 which)
अणु
	काष्ठा gb_pwm_deactivate_request request;
	काष्ठा gbphy_device *gbphy_dev;
	पूर्णांक ret;

	अगर (which > pwmc->pwm_max)
		वापस -EINVAL;

	request.which = which;

	gbphy_dev = to_gbphy_dev(pwmc->chip.dev);
	ret = gbphy_runसमय_get_sync(gbphy_dev);
	अगर (ret)
		वापस ret;

	ret = gb_operation_sync(pwmc->connection, GB_PWM_TYPE_DEACTIVATE,
				&request, माप(request), शून्य, 0);

	gbphy_runसमय_put_स्वतःsuspend(gbphy_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_pwm_config_operation(काष्ठा gb_pwm_chip *pwmc,
				   u8 which, u32 duty, u32 period)
अणु
	काष्ठा gb_pwm_config_request request;
	काष्ठा gbphy_device *gbphy_dev;
	पूर्णांक ret;

	अगर (which > pwmc->pwm_max)
		वापस -EINVAL;

	request.which = which;
	request.duty = cpu_to_le32(duty);
	request.period = cpu_to_le32(period);

	gbphy_dev = to_gbphy_dev(pwmc->chip.dev);
	ret = gbphy_runसमय_get_sync(gbphy_dev);
	अगर (ret)
		वापस ret;

	ret = gb_operation_sync(pwmc->connection, GB_PWM_TYPE_CONFIG,
				&request, माप(request), शून्य, 0);

	gbphy_runसमय_put_स्वतःsuspend(gbphy_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_pwm_set_polarity_operation(काष्ठा gb_pwm_chip *pwmc,
					 u8 which, u8 polarity)
अणु
	काष्ठा gb_pwm_polarity_request request;
	काष्ठा gbphy_device *gbphy_dev;
	पूर्णांक ret;

	अगर (which > pwmc->pwm_max)
		वापस -EINVAL;

	request.which = which;
	request.polarity = polarity;

	gbphy_dev = to_gbphy_dev(pwmc->chip.dev);
	ret = gbphy_runसमय_get_sync(gbphy_dev);
	अगर (ret)
		वापस ret;

	ret = gb_operation_sync(pwmc->connection, GB_PWM_TYPE_POLARITY,
				&request, माप(request), शून्य, 0);

	gbphy_runसमय_put_स्वतःsuspend(gbphy_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_pwm_enable_operation(काष्ठा gb_pwm_chip *pwmc,
				   u8 which)
अणु
	काष्ठा gb_pwm_enable_request request;
	काष्ठा gbphy_device *gbphy_dev;
	पूर्णांक ret;

	अगर (which > pwmc->pwm_max)
		वापस -EINVAL;

	request.which = which;

	gbphy_dev = to_gbphy_dev(pwmc->chip.dev);
	ret = gbphy_runसमय_get_sync(gbphy_dev);
	अगर (ret)
		वापस ret;

	ret = gb_operation_sync(pwmc->connection, GB_PWM_TYPE_ENABLE,
				&request, माप(request), शून्य, 0);
	अगर (ret)
		gbphy_runसमय_put_स्वतःsuspend(gbphy_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_pwm_disable_operation(काष्ठा gb_pwm_chip *pwmc,
				    u8 which)
अणु
	काष्ठा gb_pwm_disable_request request;
	काष्ठा gbphy_device *gbphy_dev;
	पूर्णांक ret;

	अगर (which > pwmc->pwm_max)
		वापस -EINVAL;

	request.which = which;

	ret = gb_operation_sync(pwmc->connection, GB_PWM_TYPE_DISABLE,
				&request, माप(request), शून्य, 0);

	gbphy_dev = to_gbphy_dev(pwmc->chip.dev);
	gbphy_runसमय_put_स्वतःsuspend(gbphy_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक gb_pwm_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा gb_pwm_chip *pwmc = pwm_chip_to_gb_pwm_chip(chip);

	वापस gb_pwm_activate_operation(pwmc, pwm->hwpwm);
पूर्ण;

अटल व्योम gb_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा gb_pwm_chip *pwmc = pwm_chip_to_gb_pwm_chip(chip);

	अगर (pwm_is_enabled(pwm))
		dev_warn(chip->dev, "freeing PWM device without disabling\n");

	gb_pwm_deactivate_operation(pwmc, pwm->hwpwm);
पूर्ण

अटल पूर्णांक gb_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			 पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा gb_pwm_chip *pwmc = pwm_chip_to_gb_pwm_chip(chip);

	वापस gb_pwm_config_operation(pwmc, pwm->hwpwm, duty_ns, period_ns);
पूर्ण;

अटल पूर्णांक gb_pwm_set_polarity(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			       क्रमागत pwm_polarity polarity)
अणु
	काष्ठा gb_pwm_chip *pwmc = pwm_chip_to_gb_pwm_chip(chip);

	वापस gb_pwm_set_polarity_operation(pwmc, pwm->hwpwm, polarity);
पूर्ण;

अटल पूर्णांक gb_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा gb_pwm_chip *pwmc = pwm_chip_to_gb_pwm_chip(chip);

	वापस gb_pwm_enable_operation(pwmc, pwm->hwpwm);
पूर्ण;

अटल व्योम gb_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा gb_pwm_chip *pwmc = pwm_chip_to_gb_pwm_chip(chip);

	gb_pwm_disable_operation(pwmc, pwm->hwpwm);
पूर्ण;

अटल स्थिर काष्ठा pwm_ops gb_pwm_ops = अणु
	.request = gb_pwm_request,
	.मुक्त = gb_pwm_मुक्त,
	.config = gb_pwm_config,
	.set_polarity = gb_pwm_set_polarity,
	.enable = gb_pwm_enable,
	.disable = gb_pwm_disable,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक gb_pwm_probe(काष्ठा gbphy_device *gbphy_dev,
			स्थिर काष्ठा gbphy_device_id *id)
अणु
	काष्ठा gb_connection *connection;
	काष्ठा gb_pwm_chip *pwmc;
	काष्ठा pwm_chip *pwm;
	पूर्णांक ret;

	pwmc = kzalloc(माप(*pwmc), GFP_KERNEL);
	अगर (!pwmc)
		वापस -ENOMEM;

	connection = gb_connection_create(gbphy_dev->bundle,
					  le16_to_cpu(gbphy_dev->cport_desc->id),
					  शून्य);
	अगर (IS_ERR(connection)) अणु
		ret = PTR_ERR(connection);
		जाओ निकास_pwmc_मुक्त;
	पूर्ण

	pwmc->connection = connection;
	gb_connection_set_data(connection, pwmc);
	gb_gbphy_set_data(gbphy_dev, pwmc);

	ret = gb_connection_enable(connection);
	अगर (ret)
		जाओ निकास_connection_destroy;

	/* Query number of pwms present */
	ret = gb_pwm_count_operation(pwmc);
	अगर (ret)
		जाओ निकास_connection_disable;

	pwm = &pwmc->chip;

	pwm->dev = &gbphy_dev->dev;
	pwm->ops = &gb_pwm_ops;
	pwm->base = -1;			/* Allocate base dynamically */
	pwm->npwm = pwmc->pwm_max + 1;

	ret = pwmchip_add(pwm);
	अगर (ret) अणु
		dev_err(&gbphy_dev->dev,
			"failed to register PWM: %d\n", ret);
		जाओ निकास_connection_disable;
	पूर्ण

	gbphy_runसमय_put_स्वतःsuspend(gbphy_dev);
	वापस 0;

निकास_connection_disable:
	gb_connection_disable(connection);
निकास_connection_destroy:
	gb_connection_destroy(connection);
निकास_pwmc_मुक्त:
	kमुक्त(pwmc);
	वापस ret;
पूर्ण

अटल व्योम gb_pwm_हटाओ(काष्ठा gbphy_device *gbphy_dev)
अणु
	काष्ठा gb_pwm_chip *pwmc = gb_gbphy_get_data(gbphy_dev);
	काष्ठा gb_connection *connection = pwmc->connection;
	पूर्णांक ret;

	ret = gbphy_runसमय_get_sync(gbphy_dev);
	अगर (ret)
		gbphy_runसमय_get_noresume(gbphy_dev);

	pwmchip_हटाओ(&pwmc->chip);
	gb_connection_disable(connection);
	gb_connection_destroy(connection);
	kमुक्त(pwmc);
पूर्ण

अटल स्थिर काष्ठा gbphy_device_id gb_pwm_id_table[] = अणु
	अणु GBPHY_PROTOCOL(GREYBUS_PROTOCOL_PWM) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(gbphy, gb_pwm_id_table);

अटल काष्ठा gbphy_driver pwm_driver = अणु
	.name		= "pwm",
	.probe		= gb_pwm_probe,
	.हटाओ		= gb_pwm_हटाओ,
	.id_table	= gb_pwm_id_table,
पूर्ण;

module_gbphy_driver(pwm_driver);
MODULE_LICENSE("GPL v2");
