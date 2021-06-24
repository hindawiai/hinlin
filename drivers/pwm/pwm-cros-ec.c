<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Expose a PWM controlled by the ChromeOS EC to the host processor.
 *
 * Copyright (C) 2016 Google, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>

/**
 * काष्ठा cros_ec_pwm_device - Driver data क्रम EC PWM
 *
 * @dev: Device node
 * @ec: Poपूर्णांकer to EC device
 * @chip: PWM controller chip
 */
काष्ठा cros_ec_pwm_device अणु
	काष्ठा device *dev;
	काष्ठा cros_ec_device *ec;
	काष्ठा pwm_chip chip;
पूर्ण;

/**
 * काष्ठा cros_ec_pwm - per-PWM driver data
 * @duty_cycle: cached duty cycle
 */
काष्ठा cros_ec_pwm अणु
	u16 duty_cycle;
पूर्ण;

अटल अंतरभूत काष्ठा cros_ec_pwm_device *pwm_to_cros_ec_pwm(काष्ठा pwm_chip *c)
अणु
	वापस container_of(c, काष्ठा cros_ec_pwm_device, chip);
पूर्ण

अटल पूर्णांक cros_ec_pwm_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा cros_ec_pwm *channel;

	channel = kzalloc(माप(*channel), GFP_KERNEL);
	अगर (!channel)
		वापस -ENOMEM;

	pwm_set_chip_data(pwm, channel);

	वापस 0;
पूर्ण

अटल व्योम cros_ec_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा cros_ec_pwm *channel = pwm_get_chip_data(pwm);

	kमुक्त(channel);
पूर्ण

अटल पूर्णांक cros_ec_pwm_set_duty(काष्ठा cros_ec_device *ec, u8 index, u16 duty)
अणु
	काष्ठा अणु
		काष्ठा cros_ec_command msg;
		काष्ठा ec_params_pwm_set_duty params;
	पूर्ण __packed buf;
	काष्ठा ec_params_pwm_set_duty *params = &buf.params;
	काष्ठा cros_ec_command *msg = &buf.msg;

	स_रखो(&buf, 0, माप(buf));

	msg->version = 0;
	msg->command = EC_CMD_PWM_SET_DUTY;
	msg->insize = 0;
	msg->outsize = माप(*params);

	params->duty = duty;
	params->pwm_type = EC_PWM_TYPE_GENERIC;
	params->index = index;

	वापस cros_ec_cmd_xfer_status(ec, msg);
पूर्ण

अटल पूर्णांक cros_ec_pwm_get_duty(काष्ठा cros_ec_device *ec, u8 index)
अणु
	काष्ठा अणु
		काष्ठा cros_ec_command msg;
		जोड़ अणु
			काष्ठा ec_params_pwm_get_duty params;
			काष्ठा ec_response_pwm_get_duty resp;
		पूर्ण;
	पूर्ण __packed buf;
	काष्ठा ec_params_pwm_get_duty *params = &buf.params;
	काष्ठा ec_response_pwm_get_duty *resp = &buf.resp;
	काष्ठा cros_ec_command *msg = &buf.msg;
	पूर्णांक ret;

	स_रखो(&buf, 0, माप(buf));

	msg->version = 0;
	msg->command = EC_CMD_PWM_GET_DUTY;
	msg->insize = माप(*resp);
	msg->outsize = माप(*params);

	params->pwm_type = EC_PWM_TYPE_GENERIC;
	params->index = index;

	ret = cros_ec_cmd_xfer_status(ec, msg);
	अगर (ret < 0)
		वापस ret;

	वापस resp->duty;
पूर्ण

अटल पूर्णांक cros_ec_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			     स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा cros_ec_pwm_device *ec_pwm = pwm_to_cros_ec_pwm(chip);
	काष्ठा cros_ec_pwm *channel = pwm_get_chip_data(pwm);
	u16 duty_cycle;
	पूर्णांक ret;

	/* The EC won't let us change the period */
	अगर (state->period != EC_PWM_MAX_DUTY)
		वापस -EINVAL;

	अगर (state->polarity != PWM_POLARITY_NORMAL)
		वापस -EINVAL;

	/*
	 * EC करोesn't separate the concept of duty cycle and enabled, but
	 * kernel करोes. Translate.
	 */
	duty_cycle = state->enabled ? state->duty_cycle : 0;

	ret = cros_ec_pwm_set_duty(ec_pwm->ec, pwm->hwpwm, duty_cycle);
	अगर (ret < 0)
		वापस ret;

	channel->duty_cycle = state->duty_cycle;

	वापस 0;
पूर्ण

अटल व्योम cros_ec_pwm_get_state(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
				  काष्ठा pwm_state *state)
अणु
	काष्ठा cros_ec_pwm_device *ec_pwm = pwm_to_cros_ec_pwm(chip);
	काष्ठा cros_ec_pwm *channel = pwm_get_chip_data(pwm);
	पूर्णांक ret;

	ret = cros_ec_pwm_get_duty(ec_pwm->ec, pwm->hwpwm);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "error getting initial duty: %d\n", ret);
		वापस;
	पूर्ण

	state->enabled = (ret > 0);
	state->period = EC_PWM_MAX_DUTY;

	/*
	 * Note that "disabled" and "duty cycle == 0" are treated the same. If
	 * the cached duty cycle is not zero, used the cached duty cycle. This
	 * ensures that the configured duty cycle is kept across a disable and
	 * enable operation and aव्योमs potentially confusing consumers.
	 *
	 * For the हाल of the initial hardware पढ़ोout, channel->duty_cycle
	 * will be 0 and the actual duty cycle पढ़ो from the EC is used.
	 */
	अगर (ret == 0 && channel->duty_cycle > 0)
		state->duty_cycle = channel->duty_cycle;
	अन्यथा
		state->duty_cycle = ret;
पूर्ण

अटल काष्ठा pwm_device *
cros_ec_pwm_xlate(काष्ठा pwm_chip *pc, स्थिर काष्ठा of_phandle_args *args)
अणु
	काष्ठा pwm_device *pwm;

	अगर (args->args[0] >= pc->npwm)
		वापस ERR_PTR(-EINVAL);

	pwm = pwm_request_from_chip(pc, args->args[0], शून्य);
	अगर (IS_ERR(pwm))
		वापस pwm;

	/* The EC won't let us change the period */
	pwm->args.period = EC_PWM_MAX_DUTY;

	वापस pwm;
पूर्ण

अटल स्थिर काष्ठा pwm_ops cros_ec_pwm_ops = अणु
	.request = cros_ec_pwm_request,
	.मुक्त = cros_ec_pwm_मुक्त,
	.get_state	= cros_ec_pwm_get_state,
	.apply		= cros_ec_pwm_apply,
	.owner		= THIS_MODULE,
पूर्ण;

/*
 * Determine the number of supported PWMs. The EC करोes not वापस the number
 * of PWMs it supports directly, so we have to पढ़ो the pwm duty cycle क्रम
 * subsequent channels until we get an error.
 */
अटल पूर्णांक cros_ec_num_pwms(काष्ठा cros_ec_device *ec)
अणु
	पूर्णांक i, ret;

	/* The index field is only 8 bits */
	क्रम (i = 0; i <= U8_MAX; i++) अणु
		ret = cros_ec_pwm_get_duty(ec, i);
		/*
		 * We look क्रम SUCCESS, INVALID_COMMAND, or INVALID_PARAM
		 * responses; everything अन्यथा is treated as an error.
		 * The EC error codes map to -EOPNOTSUPP and -EINVAL,
		 * so check क्रम those.
		 */
		चयन (ret) अणु
		हाल -EOPNOTSUPP:	/* invalid command */
			वापस -ENODEV;
		हाल -EINVAL:		/* invalid parameter */
			वापस i;
		शेष:
			अगर (ret < 0)
				वापस ret;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस U8_MAX;
पूर्ण

अटल पूर्णांक cros_ec_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cros_ec_device *ec = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा cros_ec_pwm_device *ec_pwm;
	काष्ठा pwm_chip *chip;
	पूर्णांक ret;

	अगर (!ec) अणु
		dev_err(dev, "no parent EC device\n");
		वापस -EINVAL;
	पूर्ण

	ec_pwm = devm_kzalloc(dev, माप(*ec_pwm), GFP_KERNEL);
	अगर (!ec_pwm)
		वापस -ENOMEM;
	chip = &ec_pwm->chip;
	ec_pwm->ec = ec;

	/* PWM chip */
	chip->dev = dev;
	chip->ops = &cros_ec_pwm_ops;
	chip->of_xlate = cros_ec_pwm_xlate;
	chip->of_pwm_n_cells = 1;
	ret = cros_ec_num_pwms(ec);
	अगर (ret < 0) अणु
		dev_err(dev, "Couldn't find PWMs: %d\n", ret);
		वापस ret;
	पूर्ण
	chip->npwm = ret;
	dev_dbg(dev, "Probed %u PWMs\n", chip->npwm);

	ret = pwmchip_add(chip);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot register PWM: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ec_pwm);

	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_pwm_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा cros_ec_pwm_device *ec_pwm = platक्रमm_get_drvdata(dev);
	काष्ठा pwm_chip *chip = &ec_pwm->chip;

	वापस pwmchip_हटाओ(chip);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id cros_ec_pwm_of_match[] = अणु
	अणु .compatible = "google,cros-ec-pwm" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cros_ec_pwm_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver cros_ec_pwm_driver = अणु
	.probe = cros_ec_pwm_probe,
	.हटाओ = cros_ec_pwm_हटाओ,
	.driver = अणु
		.name = "cros-ec-pwm",
		.of_match_table = of_match_ptr(cros_ec_pwm_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(cros_ec_pwm_driver);

MODULE_ALIAS("platform:cros-ec-pwm");
MODULE_DESCRIPTION("ChromeOS EC PWM driver");
MODULE_LICENSE("GPL v2");
