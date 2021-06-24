<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pwm-fan.c - Hwmon driver क्रम fans connected to PWM lines.
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Author: Kamil Debski <k.debski@samsung.com>
 */

#समावेश <linux/hwmon.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/thermal.h>
#समावेश <linux/समयr.h>

#घोषणा MAX_PWM 255

काष्ठा pwm_fan_tach अणु
	पूर्णांक irq;
	atomic_t pulses;
	अचिन्हित पूर्णांक rpm;
	u8 pulses_per_revolution;
पूर्ण;

काष्ठा pwm_fan_ctx अणु
	काष्ठा mutex lock;
	काष्ठा pwm_device *pwm;
	काष्ठा pwm_state pwm_state;
	काष्ठा regulator *reg_en;

	पूर्णांक tach_count;
	काष्ठा pwm_fan_tach *tachs;
	kसमय_प्रकार sample_start;
	काष्ठा समयr_list rpm_समयr;

	अचिन्हित पूर्णांक pwm_value;
	अचिन्हित पूर्णांक pwm_fan_state;
	अचिन्हित पूर्णांक pwm_fan_max_state;
	अचिन्हित पूर्णांक *pwm_fan_cooling_levels;
	काष्ठा thermal_cooling_device *cdev;

	काष्ठा hwmon_chip_info info;
	काष्ठा hwmon_channel_info fan_channel;
पूर्ण;

अटल स्थिर u32 pwm_fan_channel_config_pwm[] = अणु
	HWMON_PWM_INPUT,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info pwm_fan_channel_pwm = अणु
	.type = hwmon_pwm,
	.config = pwm_fan_channel_config_pwm,
पूर्ण;

/* This handler assumes self resetting edge triggered पूर्णांकerrupt. */
अटल irqवापस_t pulse_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pwm_fan_tach *tach = dev_id;

	atomic_inc(&tach->pulses);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sample_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा pwm_fan_ctx *ctx = from_समयr(ctx, t, rpm_समयr);
	अचिन्हित पूर्णांक delta = kसमय_ms_delta(kसमय_get(), ctx->sample_start);
	पूर्णांक i;

	अगर (delta) अणु
		क्रम (i = 0; i < ctx->tach_count; i++) अणु
			काष्ठा pwm_fan_tach *tach = &ctx->tachs[i];
			पूर्णांक pulses;

			pulses = atomic_पढ़ो(&tach->pulses);
			atomic_sub(pulses, &tach->pulses);
			tach->rpm = (अचिन्हित पूर्णांक)(pulses * 1000 * 60) /
				(tach->pulses_per_revolution * delta);
		पूर्ण

		ctx->sample_start = kसमय_get();
	पूर्ण

	mod_समयr(&ctx->rpm_समयr, jअगरfies + HZ);
पूर्ण

अटल पूर्णांक  __set_pwm(काष्ठा pwm_fan_ctx *ctx, अचिन्हित दीर्घ pwm)
अणु
	अचिन्हित दीर्घ period;
	पूर्णांक ret = 0;
	काष्ठा pwm_state *state = &ctx->pwm_state;

	mutex_lock(&ctx->lock);
	अगर (ctx->pwm_value == pwm)
		जाओ निकास_set_pwm_err;

	period = state->period;
	state->duty_cycle = DIV_ROUND_UP(pwm * (period - 1), MAX_PWM);
	state->enabled = pwm ? true : false;

	ret = pwm_apply_state(ctx->pwm, state);
	अगर (!ret)
		ctx->pwm_value = pwm;
निकास_set_pwm_err:
	mutex_unlock(&ctx->lock);
	वापस ret;
पूर्ण

अटल व्योम pwm_fan_update_state(काष्ठा pwm_fan_ctx *ctx, अचिन्हित दीर्घ pwm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ctx->pwm_fan_max_state; ++i)
		अगर (pwm < ctx->pwm_fan_cooling_levels[i + 1])
			अवरोध;

	ctx->pwm_fan_state = i;
पूर्ण

अटल पूर्णांक pwm_fan_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			 u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा pwm_fan_ctx *ctx = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (val < 0 || val > MAX_PWM)
		वापस -EINVAL;

	ret = __set_pwm(ctx, val);
	अगर (ret)
		वापस ret;

	pwm_fan_update_state(ctx, val);
	वापस 0;
पूर्ण

अटल पूर्णांक pwm_fan_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा pwm_fan_ctx *ctx = dev_get_drvdata(dev);

	चयन (type) अणु
	हाल hwmon_pwm:
		*val = ctx->pwm_value;
		वापस 0;

	हाल hwmon_fan:
		*val = ctx->tachs[channel].rpm;
		वापस 0;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t pwm_fan_is_visible(स्थिर व्योम *data,
				  क्रमागत hwmon_sensor_types type,
				  u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_pwm:
		वापस 0644;

	हाल hwmon_fan:
		वापस 0444;

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hwmon_ops pwm_fan_hwmon_ops = अणु
	.is_visible = pwm_fan_is_visible,
	.पढ़ो = pwm_fan_पढ़ो,
	.ग_लिखो = pwm_fan_ग_लिखो,
पूर्ण;

/* thermal cooling device callbacks */
अटल पूर्णांक pwm_fan_get_max_state(काष्ठा thermal_cooling_device *cdev,
				 अचिन्हित दीर्घ *state)
अणु
	काष्ठा pwm_fan_ctx *ctx = cdev->devdata;

	अगर (!ctx)
		वापस -EINVAL;

	*state = ctx->pwm_fan_max_state;

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_fan_get_cur_state(काष्ठा thermal_cooling_device *cdev,
				 अचिन्हित दीर्घ *state)
अणु
	काष्ठा pwm_fan_ctx *ctx = cdev->devdata;

	अगर (!ctx)
		वापस -EINVAL;

	*state = ctx->pwm_fan_state;

	वापस 0;
पूर्ण

अटल पूर्णांक
pwm_fan_set_cur_state(काष्ठा thermal_cooling_device *cdev, अचिन्हित दीर्घ state)
अणु
	काष्ठा pwm_fan_ctx *ctx = cdev->devdata;
	पूर्णांक ret;

	अगर (!ctx || (state > ctx->pwm_fan_max_state))
		वापस -EINVAL;

	अगर (state == ctx->pwm_fan_state)
		वापस 0;

	ret = __set_pwm(ctx, ctx->pwm_fan_cooling_levels[state]);
	अगर (ret) अणु
		dev_err(&cdev->device, "Cannot set pwm!\n");
		वापस ret;
	पूर्ण

	ctx->pwm_fan_state = state;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops pwm_fan_cooling_ops = अणु
	.get_max_state = pwm_fan_get_max_state,
	.get_cur_state = pwm_fan_get_cur_state,
	.set_cur_state = pwm_fan_set_cur_state,
पूर्ण;

अटल पूर्णांक pwm_fan_of_get_cooling_data(काष्ठा device *dev,
				       काष्ठा pwm_fan_ctx *ctx)
अणु
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक num, i, ret;

	अगर (!of_find_property(np, "cooling-levels", शून्य))
		वापस 0;

	ret = of_property_count_u32_elems(np, "cooling-levels");
	अगर (ret <= 0) अणु
		dev_err(dev, "Wrong data!\n");
		वापस ret ? : -EINVAL;
	पूर्ण

	num = ret;
	ctx->pwm_fan_cooling_levels = devm_kसुस्मृति(dev, num, माप(u32),
						   GFP_KERNEL);
	अगर (!ctx->pwm_fan_cooling_levels)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u32_array(np, "cooling-levels",
					 ctx->pwm_fan_cooling_levels, num);
	अगर (ret) अणु
		dev_err(dev, "Property 'cooling-levels' cannot be read!\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		अगर (ctx->pwm_fan_cooling_levels[i] > MAX_PWM) अणु
			dev_err(dev, "PWM fan state[%d]:%d > %d\n", i,
				ctx->pwm_fan_cooling_levels[i], MAX_PWM);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ctx->pwm_fan_max_state = num - 1;

	वापस 0;
पूर्ण

अटल व्योम pwm_fan_regulator_disable(व्योम *data)
अणु
	regulator_disable(data);
पूर्ण

अटल व्योम pwm_fan_pwm_disable(व्योम *__ctx)
अणु
	काष्ठा pwm_fan_ctx *ctx = __ctx;

	ctx->pwm_state.enabled = false;
	pwm_apply_state(ctx->pwm, &ctx->pwm_state);
	del_समयr_sync(&ctx->rpm_समयr);
पूर्ण

अटल पूर्णांक pwm_fan_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pwm_fan_ctx *ctx;
	काष्ठा device *hwmon;
	पूर्णांक ret;
	स्थिर काष्ठा hwmon_channel_info **channels;
	u32 *fan_channel_config;
	पूर्णांक channel_count = 1;	/* We always have a PWM channel. */
	पूर्णांक i;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	mutex_init(&ctx->lock);

	ctx->pwm = devm_of_pwm_get(dev, dev->of_node, शून्य);
	अगर (IS_ERR(ctx->pwm))
		वापस dev_err_probe(dev, PTR_ERR(ctx->pwm), "Could not get PWM\n");

	platक्रमm_set_drvdata(pdev, ctx);

	ctx->reg_en = devm_regulator_get_optional(dev, "fan");
	अगर (IS_ERR(ctx->reg_en)) अणु
		अगर (PTR_ERR(ctx->reg_en) != -ENODEV)
			वापस PTR_ERR(ctx->reg_en);

		ctx->reg_en = शून्य;
	पूर्ण अन्यथा अणु
		ret = regulator_enable(ctx->reg_en);
		अगर (ret) अणु
			dev_err(dev, "Failed to enable fan supply: %d\n", ret);
			वापस ret;
		पूर्ण
		ret = devm_add_action_or_reset(dev, pwm_fan_regulator_disable,
					       ctx->reg_en);
		अगर (ret)
			वापस ret;
	पूर्ण

	ctx->pwm_value = MAX_PWM;

	pwm_init_state(ctx->pwm, &ctx->pwm_state);

	/*
	 * __set_pwm assumes that MAX_PWM * (period - 1) fits पूर्णांकo an अचिन्हित
	 * दीर्घ. Check this here to prevent the fan running at a too low
	 * frequency.
	 */
	अगर (ctx->pwm_state.period > अच_दीर्घ_उच्च / MAX_PWM + 1) अणु
		dev_err(dev, "Configured period too big\n");
		वापस -EINVAL;
	पूर्ण

	/* Set duty cycle to maximum allowed and enable PWM output */
	ret = __set_pwm(ctx, MAX_PWM);
	अगर (ret) अणु
		dev_err(dev, "Failed to configure PWM: %d\n", ret);
		वापस ret;
	पूर्ण
	समयr_setup(&ctx->rpm_समयr, sample_समयr, 0);
	ret = devm_add_action_or_reset(dev, pwm_fan_pwm_disable, ctx);
	अगर (ret)
		वापस ret;

	ctx->tach_count = platक्रमm_irq_count(pdev);
	अगर (ctx->tach_count < 0)
		वापस dev_err_probe(dev, ctx->tach_count,
				     "Could not get number of fan tachometer inputs\n");
	dev_dbg(dev, "%d fan tachometer inputs\n", ctx->tach_count);

	अगर (ctx->tach_count) अणु
		channel_count++;	/* We also have a FAN channel. */

		ctx->tachs = devm_kसुस्मृति(dev, ctx->tach_count,
					  माप(काष्ठा pwm_fan_tach),
					  GFP_KERNEL);
		अगर (!ctx->tachs)
			वापस -ENOMEM;

		ctx->fan_channel.type = hwmon_fan;
		fan_channel_config = devm_kसुस्मृति(dev, ctx->tach_count + 1,
						  माप(u32), GFP_KERNEL);
		अगर (!fan_channel_config)
			वापस -ENOMEM;
		ctx->fan_channel.config = fan_channel_config;
	पूर्ण

	channels = devm_kसुस्मृति(dev, channel_count + 1,
				माप(काष्ठा hwmon_channel_info *), GFP_KERNEL);
	अगर (!channels)
		वापस -ENOMEM;

	channels[0] = &pwm_fan_channel_pwm;

	क्रम (i = 0; i < ctx->tach_count; i++) अणु
		काष्ठा pwm_fan_tach *tach = &ctx->tachs[i];
		u32 ppr = 2;

		tach->irq = platक्रमm_get_irq(pdev, i);
		अगर (tach->irq == -EPROBE_DEFER)
			वापस tach->irq;
		अगर (tach->irq > 0) अणु
			ret = devm_request_irq(dev, tach->irq, pulse_handler, 0,
					       pdev->name, tach);
			अगर (ret) अणु
				dev_err(dev,
					"Failed to request interrupt: %d\n",
					ret);
				वापस ret;
			पूर्ण
		पूर्ण

		of_property_पढ़ो_u32_index(dev->of_node,
					   "pulses-per-revolution",
					   i,
					   &ppr);
		tach->pulses_per_revolution = ppr;
		अगर (!tach->pulses_per_revolution) अणु
			dev_err(dev, "pulses-per-revolution can't be zero.\n");
			वापस -EINVAL;
		पूर्ण

		fan_channel_config[i] = HWMON_F_INPUT;

		dev_dbg(dev, "tach%d: irq=%d, pulses_per_revolution=%d\n",
			i, tach->irq, tach->pulses_per_revolution);
	पूर्ण

	अगर (ctx->tach_count > 0) अणु
		ctx->sample_start = kसमय_get();
		mod_समयr(&ctx->rpm_समयr, jअगरfies + HZ);

		channels[1] = &ctx->fan_channel;
	पूर्ण

	ctx->info.ops = &pwm_fan_hwmon_ops;
	ctx->info.info = channels;

	hwmon = devm_hwmon_device_रेजिस्टर_with_info(dev, "pwmfan",
						     ctx, &ctx->info, शून्य);
	अगर (IS_ERR(hwmon)) अणु
		dev_err(dev, "Failed to register hwmon device\n");
		वापस PTR_ERR(hwmon);
	पूर्ण

	ret = pwm_fan_of_get_cooling_data(dev, ctx);
	अगर (ret)
		वापस ret;

	ctx->pwm_fan_state = ctx->pwm_fan_max_state;
	अगर (IS_ENABLED(CONFIG_THERMAL)) अणु
		cdev = devm_thermal_of_cooling_device_रेजिस्टर(dev,
			dev->of_node, "pwm-fan", ctx, &pwm_fan_cooling_ops);
		अगर (IS_ERR(cdev)) अणु
			ret = PTR_ERR(cdev);
			dev_err(dev,
				"Failed to register pwm-fan as cooling device: %d\n",
				ret);
			वापस ret;
		पूर्ण
		ctx->cdev = cdev;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_fan_disable(काष्ठा device *dev)
अणु
	काष्ठा pwm_fan_ctx *ctx = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (ctx->pwm_value) अणु
		/* keep ctx->pwm_state unmodअगरied क्रम pwm_fan_resume() */
		काष्ठा pwm_state state = ctx->pwm_state;

		state.duty_cycle = 0;
		state.enabled = false;
		ret = pwm_apply_state(ctx->pwm, &state);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (ctx->reg_en) अणु
		ret = regulator_disable(ctx->reg_en);
		अगर (ret) अणु
			dev_err(dev, "Failed to disable fan supply: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pwm_fan_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	pwm_fan_disable(&pdev->dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pwm_fan_suspend(काष्ठा device *dev)
अणु
	वापस pwm_fan_disable(dev);
पूर्ण

अटल पूर्णांक pwm_fan_resume(काष्ठा device *dev)
अणु
	काष्ठा pwm_fan_ctx *ctx = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (ctx->reg_en) अणु
		ret = regulator_enable(ctx->reg_en);
		अगर (ret) अणु
			dev_err(dev, "Failed to enable fan supply: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (ctx->pwm_value == 0)
		वापस 0;

	वापस pwm_apply_state(ctx->pwm, &ctx->pwm_state);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(pwm_fan_pm, pwm_fan_suspend, pwm_fan_resume);

अटल स्थिर काष्ठा of_device_id of_pwm_fan_match[] = अणु
	अणु .compatible = "pwm-fan", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_pwm_fan_match);

अटल काष्ठा platक्रमm_driver pwm_fan_driver = अणु
	.probe		= pwm_fan_probe,
	.shutकरोwn	= pwm_fan_shutकरोwn,
	.driver	= अणु
		.name		= "pwm-fan",
		.pm		= &pwm_fan_pm,
		.of_match_table	= of_pwm_fan_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pwm_fan_driver);

MODULE_AUTHOR("Kamil Debski <k.debski@samsung.com>");
MODULE_ALIAS("platform:pwm-fan");
MODULE_DESCRIPTION("PWM FAN driver");
MODULE_LICENSE("GPL");
